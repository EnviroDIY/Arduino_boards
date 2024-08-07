# change forceupdate to 1 to update the fuses to factory default values specified below
if {[info exists forceupdate]} {
    puts $forceupdate
} else {
    set forceupdate 0
}

# if NOT forcing an updated (`set forceupdate 0`), set the size of the bootloader to protect here
# This size is given by the following formula (15-BOOTPROT)*8KB.
# 0x0F (15) for 0 kb protected
# 0x0D (13) for 16kb protected (the SAMD51 UF2 bootloader is 16kb)
# set bootprot 0x0D
if {[info exists bootprot]} {
    puts $bootprot
} else {
    set bootprot 0xF
}

#  Set up the Transport and Chip

source [find interface/cmsis-dap.cfg]
transport select swd

# chip name
set CHIPNAME samd51n19a

set _FLASHDRIVER atsame5

source [find target/atsame5x.cfg]


# The SAMD/E51 has 5 32-bit "fuses", aka User Rows, USER_WORD, or Configuration Bits
# BUT for the SAMD/E51 we need to write the whole 512 byte (4096 bit) user page at once.
set n_32bit_reads_page 132

# Default values for Fuse 0 (User Row / USER_WORD_0)
# ---- Brownout Detection - see SUPC.BOD33 register
# 0 BOD33 Disable, default = 0x1,  0b1 (enabled)
# 8:1 BOD33 Level, default = 0x1C, 0b00011100 << 1
# 10:9 BOD33 Action, default = 0x1, 0b01 << 9 (reset)
# 14:11 BOD33 Hysteresis, default = 0x2, b010 << 11
# 25:15 BOD12 Calibration Parameters - do not change, default = 0b10100110101 << 15
# ---- Boot protection!
# 29:26 NVM BOOTPROT, default = 0b1111 < 26
# 31:30 Reserved, Factory settings - do not change, default = 0b11 << 30
# Factory Default:
# 0xFE9A9239 = 0b11111110100110101001001000111001
# Changable Bits Mask (1 bits are user changable, 0 bits are reserved)
# 0x3C007FFF = 0b00111100000000000111111111111111
set v0 0xFE9A9239

# Default values for Fuse 1 ((User Row / USER_WORD_1)
# ---- SmartEEPROM - see NVMCTRL.SEESTAT
# 35:32 SBLK (Number of NVM Blocks composing a SmartEEPROM sector), default = 0x0
# 38:36 PSZ (SmartEEPROM Page Size), default = 0x0 << 4
# 39 RAM ECCDIS RAM ECC (Disable RAMECC), default = 0x1 << 7
# 47:40 Reserved Factory settings - do not change, default = 0b11111111 << 8
# ---- Watchdog Timer - see WDT.CTRLA, WDT.CONFIG, and  WDT.EWCTRL
# 48 WDT Enable WDT, default = 0x0, 0b0 << 16
# 49 WDT Always-On, default = 0x0, 0b0 << 17
# 53:50 WDT Period, default = 0xB, 0b1011 << 18
# 57:54 WDT Window, default = 0xB, 0b1011 << 22
# 61:58 WDT EWOFFSET (Early Warning Interrupt Time Offset), default = 0xB, 0b1011 << 26
# 62 WDT WEN (Window Mode Enable), default = 0x0, 0b0 << 30 (disabled)
# 63 Reserved Factory settings - do not change, default = 0b1 << 31
# Factory Default:
# 0xAEECFF80 = 0b10101110111011001111111110000000
# Changable Bits Mask (1 bits are user changable, 0 bits are reserved)
# 0x7FFF00FF = 0b01111111111111110000000011111111
set v1 0xAEECFF80
set v2 0xFFFFFFFF
# fuses[3] is for user use, so we don't change it.
set v3 0xFFFFFFFF
set v4 0x00804010

# initialize
init

# find other used scripts
set CPU_MAX_ADDRESS 0xFFFFFFFF
source [find bitsbytes.tcl]
source [find memory.tcl]

# 0x00804000 is the base address of Fuse 0 ((User Row / USER_WORD_0 / NVMCTRL_USER)
set fuse0 0x00804000
# 0x41004000 is the base address of the NVMCTRL peripheral (APB Base Address)
set nvmctrl 0x41004000

# (NVMCTRL_CTRLB_CMD_PBC) Page Buffer Clear
# Clears the page buffer.
set cmd_pbc 0x15
# (NVMCTRL_CTRLB_CMD_EP) Erase Page
# Only supported in the USER and AUX pages.
set cmd_ep 0x0
# (NVMCTRL_CTRLB_CMD_WQW) Write Quad Word
# Writes a 128-bit word at the location addressed by the ADDR register.
set cmd_wqw 0x4

# Helper procedure to send a commands to change values within the NVMCTRL
proc cmd {C} {
    global nvmctrl
    # Sent the command and the execution key needed to execute the command
    #   NVMCTRL_CTRLB is offset from NVMCTRL by 0x04
    #   0xA500 (0xA5<<8) is the NVMCTRL_CTRLB Execution Key [NOTE, CTRLB for SAMD51 CTRLA for SAMD21]
    memwrite16 [expr $nvmctrl + 0x04]  [expr 0xA500 | $C]
    # Wait for the status bit to be ready??
    # while (NVMCTRL->STATUS.bit.READY == 0) { }
}


puts "Reading Fuses"
# get the current values of the fuses
# Dynamically create a bunch of variables.
for { set x 0 } { $x < $n_32bit_reads_page } { set x [expr {$x + 1}]} {
    # Create the variable name (f#)
    set vn [format "f%d" $x]
    # Make it a global
    global $vn
    # Read the 32-bit memory to set the value
    set $vn [memread32 [expr $fuse0 + $x*4]]

    # puts $vn
    # puts [format 0x%x [expr $fuse0 + ($x*4)]]
    # puts [format 0x%x [subst $$vn]]
}

# print the current values of fuse 0
puts "Current Fuse 0:"
puts [format %x $f0]
show_normalize_bitfield $f0 29 26


puts "BOOTPROT Bit Read:"
set bootprot_read [format %x [expr ($f0 & 0b00111100000000000000000000000000)>>26]]
puts $bootprot_read
puts "BOOTPROT Bit Requested:"
puts [format %x $bootprot]


# Don't change anything unless force-update is set or the fuses are locked
set updatefuses 0
set start_remaining_fuses 1

# If we're forcing an update (re-writing all fuses to factory settings)
if { $forceupdate } then {
    set updatefuses 1
    # don't mess with fuse three, even here
    set v3 $f3
    # when "factory resetting" fuses,
    # we rewrite fuses 0-4 and then copy the rest from what they were
    set start_remaining_fuses 5
    puts "Updating fuses to factory settings"
} else {
    # if we're not re-writing all the fuses, just changing the protection size
    # check if the boot protection settings line up
    if { ($f0 & 0b00111100000000000000000000000000) != [expr $bootprot << 26] } then {
        # if the boot protection setting isn't what we want, we'll update fuses
        set updatefuses 1
        # clear the value of the bootprot portion of fuse 0
        set v0_p [expr $f0 & ~0b00111100000000000000000000000000]
        # set the value for fuse 0 the read value bitwise-or with the requested bootprot setting
        set v0 [expr $v0_p | $bootprot << 26]
    }
}

# set the value for the rest of the page to what we already read
# start with the next fuse after the last one we are setting
for { set x $start_remaining_fuses } { $x < $n_32bit_reads_page } { set x [expr {$x + 1}]} {
    # Create the variable names (v# and f#)
    set vn [format "v%d" $x]
    global $vn
    set fn [format "f%d" $x]
    # puts [format 0x%x [subst $$fn]]
    # Set the value back to what we read
    set $vn [subst $$fn]
}

if { $updatefuses } then {
    puts "*** Writing fuses! ***"

    for { set x 0 } { $x < 5 } { set x [expr {$x + 1}]} {
        # Create the variable name (f#)
        set vn_old [format "f%d" $x]
        set vn_new [format "v%d" $x]

        puts [format "Fuse %d Previous: 0x%x Writing: 0x%x" $x [subst $$vn_old] [subst $$vn_new]]
    }

    # get the current values of the Control A register
    # The Control A register is offset by 0x0 from the base address of NVMCTRL
    set ctla_old [memread16 [expr $nvmctrl + 0x0]]

    # set bits 5:4 to 0x0=0b00 to configure manual write mode for NVM
    set ctla_new [expr $ctla_old & 0b1111111111001111]

    # write new values to with manual write to control a
    memwrite16 [expr $nvmctrl + 0x0] $ctla_new

    # wait for NVM to be ready to accept a new command (NVMCTRL.STATUS) ??

    # Set the starting address of the registers which we're going to write to the offset of fuse 0
    # ie, write the address of fuse 0 to the ADDR register, itself located at NVMCTRL + NVMCTRL_ADDR
    #   0x14 is the offset of the NVMCTRL_ADDR register
    memwrite32 [expr $nvmctrl + 0x14] [expr $fuse0]

    # erase the user page starting at the address/offset of fuse 0
    cmd $cmd_ep
    # clear the user page buffer starting at the address/offset of fuse 0
    cmd $cmd_pbc

    # Write the entire page back in 32 bit chunks
    # set the offset from the first fuse
    set current_offset 0
    #loop through "quad-words" (ie, 4*32 bit writes)
    for { set x 0 } { $x < $n_32bit_reads_page } { set x [expr {$x + 4}]} {
        # Set the write variables
        set write_var0 [subst [format "v%d" [expr $x+0]]]
        set write_var1 [subst [format "v%d" [expr $x+1]]]
        set write_var2 [subst [format "v%d" [expr $x+2]]]
        set write_var3 [subst [format "v%d" [expr $x+3]]]


        set write_value0 [subst $$write_var0]
        set write_value1 [subst $$write_var1]
        set write_value2 [subst $$write_var2]
        set write_value3 [subst $$write_var3]

        # Set the write offsets
        set write_offset0 [expr $fuse0 + $x*4 + 0]
        set write_offset1 [expr $fuse0 + $x*4 + 4]
        set write_offset2 [expr $fuse0 + $x*4 + 8]
        set write_offset3 [expr $fuse0 + $x*4 + 12]

        # puts $write_var0
        # puts [format %x $write_offset0]
        # puts [format %x $write_value0]
        # puts $write_var1
        # puts [format %x $write_offset1]
        # puts [format %x $write_value1]
        # puts $write_var2
        # puts [format %x $write_offset2]
        # puts [format %x $write_value2]
        # puts $write_var3
        # puts [format %x $write_offset3]
        # puts [format %x $write_value3]

        # Write the values
        memwrite32 [expr $write_offset0] [expr $write_value0]
        memwrite32 [expr $write_offset1] [expr $write_value1]
        memwrite32 [expr $write_offset2] [expr $write_value2]
        memwrite32 [expr $write_offset3] [expr $write_value3]

        # Set the starting address of the registers which we're going to write current quad word
        memwrite32 [expr $nvmctrl + 0x14] [expr $write_offset0]

        # write the quad word
        cmd $cmd_wqw
    }

    # reset the chip to apply
    reset
}


puts "Reading Back Fuses"
# get the current values of the fuses
# Dynamically create a bunch of variables.
for { set x 0 } { $x < 5 } { set x [expr {$x + 1}]} {
    # Create the variable name (f#)
    set vn_old [format "f%d" $x]
    set vn_new [format "f%d_new" $x]
    # Make it a global
    # Read the 32-bit memory to set the value
    set $vn_new [memread32 [expr $fuse0 + $x*4]]

    puts [format "Fuse %d Previous: 0x%x New: 0x%x" $x [subst $$vn_old] [subst $$vn_new]]
}

# end the script
shutdown
