
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2015.3
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7z020clg400-1

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}



# CHANGE DESIGN NAME HERE
set design_name design_1

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "ERROR: Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      puts "INFO: Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   puts "INFO: Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   puts "INFO: Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   puts $errMsg
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set DDR [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddrx_rtl:1.0 DDR ]
  set FIXED_IO [ create_bd_intf_port -mode Master -vlnv xilinx.com:display_processing_system7:fixedio_rtl:1.0 FIXED_IO ]

  # Create ports
  set TTL_In [ create_bd_port -dir I TTL_In ]
  set clkin_n [ create_bd_port -dir I -type clk clkin_n ]
  set_property -dict [ list \
CONFIG.FREQ_HZ {250000000} \
 ] $clkin_n
  set clkin_p [ create_bd_port -dir I -type clk clkin_p ]
  set_property -dict [ list \
CONFIG.FREQ_HZ {250000000} \
 ] $clkin_p
  set din_n [ create_bd_port -dir I -from 12 -to 0 din_n ]
  set din_p [ create_bd_port -dir I -from 12 -to 0 din_p ]

  # Create instance: AA_0, and set properties
  set AA_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:AA:1.0 AA_0 ]

  # Create instance: AA_Integrator6Buf_0, and set properties
  set AA_Integrator6Buf_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:AA_Integrator6Buf:1.0 AA_Integrator6Buf_0 ]

  # Create instance: DFF_0, and set properties
  set DFF_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:DFF:1.0 DFF_0 ]

  # Create instance: DFF_Integrator6Buf_0, and set properties
  set DFF_Integrator6Buf_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:DFF_Integrator6Buf:1.0 DFF_Integrator6Buf_0 ]

  # Create instance: LPF_Integrator6buf_0, and set properties
  set LPF_Integrator6buf_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:LPF_Integrator6buf:1.0 LPF_Integrator6buf_0 ]

  # Create instance: MUX6_0, and set properties
  set MUX6_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:MUX6:1.0 MUX6_0 ]

  # Create instance: Master_Slave_Stream_v1_0_0, and set properties
  set Master_Slave_Stream_v1_0_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:Master_Slave_Stream_v1_0:1.0 Master_Slave_Stream_v1_0_0 ]

  # Create instance: TriggerV2_0, and set properties
  set TriggerV2_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:TriggerV2:1.0 TriggerV2_0 ]

  # Create instance: Trigger_original_smaller_0, and set properties
  set Trigger_original_smaller_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:Trigger_original_smaller:1.0 Trigger_original_smaller_0 ]

  # Create instance: axi_dma_0, and set properties
  set axi_dma_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0 ]
  set_property -dict [ list \
CONFIG.c_include_mm2s {0} \
CONFIG.c_include_sg {0} \
CONFIG.c_sg_include_stscntrl_strm {0} \
CONFIG.c_sg_length_width {18} \
 ] $axi_dma_0

  # Create instance: axi_gpio_0, and set properties
  set axi_gpio_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_0 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_0

  # Create instance: axi_gpio_1, and set properties
  set axi_gpio_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_1 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_1

  # Create instance: axi_gpio_2, and set properties
  set axi_gpio_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_2 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_2

  # Create instance: axi_gpio_3, and set properties
  set axi_gpio_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_3 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_3

  # Create instance: axi_gpio_4, and set properties
  set axi_gpio_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_4 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_4

  # Create instance: axi_gpio_5, and set properties
  set axi_gpio_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_5 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_5

  # Create instance: axi_gpio_6, and set properties
  set axi_gpio_6 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_6 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_6

  # Create instance: axi_gpio_7, and set properties
  set axi_gpio_7 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_7 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_7

  # Create instance: axi_gpio_8, and set properties
  set axi_gpio_8 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_8 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {12} \
 ] $axi_gpio_8

  # Create instance: axi_gpio_9, and set properties
  set axi_gpio_9 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_9 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {1} \
 ] $axi_gpio_9

  # Create instance: axi_gpio_10, and set properties
  set axi_gpio_10 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_10 ]
  set_property -dict [ list \
CONFIG.C_DOUT_DEFAULT {0x000022C4} \
CONFIG.C_GPIO_WIDTH {14} \
 ] $axi_gpio_10

  # Create instance: axi_gpio_11, and set properties
  set axi_gpio_11 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_11 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {1} \
 ] $axi_gpio_11

  # Create instance: axi_gpio_13, and set properties
  set axi_gpio_13 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_13 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {1} \
 ] $axi_gpio_13

  # Create instance: axi_gpio_14, and set properties
  set axi_gpio_14 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_14 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {3} \
 ] $axi_gpio_14

  # Create instance: axi_gpio_15, and set properties
  set axi_gpio_15 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_15 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {1} \
 ] $axi_gpio_15

  # Create instance: axi_gpio_16, and set properties
  set axi_gpio_16 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_16 ]

  # Create instance: axi_gpio_17, and set properties
  set axi_gpio_17 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_17 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {1} \
 ] $axi_gpio_17

  # Create instance: axi_gpio_18, and set properties
  set axi_gpio_18 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_18 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {1} \
 ] $axi_gpio_18

  # Create instance: axi_gpio_19, and set properties
  set axi_gpio_19 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_19 ]
  set_property -dict [ list \
CONFIG.C_GPIO_WIDTH {1} \
 ] $axi_gpio_19

  # Create instance: axi_mem_intercon, and set properties
  set axi_mem_intercon [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon ]
  set_property -dict [ list \
CONFIG.NUM_MI {1} \
 ] $axi_mem_intercon

  # Create instance: c_counter_binary_0, and set properties
  set c_counter_binary_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_counter_binary:12.0 c_counter_binary_0 ]
  set_property -dict [ list \
CONFIG.Output_Width {32} \
 ] $c_counter_binary_0

  # Create instance: c_shift_ram_0, and set properties
  set c_shift_ram_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_0 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {00000000000000000000000000000000} \
CONFIG.DefaultData {00000000000000000000000000000000} \
CONFIG.Depth {57} \
CONFIG.SyncInitVal {00000000000000000000000000000000} \
CONFIG.Width {32} \
 ] $c_shift_ram_0

  # Create instance: c_shift_ram_1, and set properties
  set c_shift_ram_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_1 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {00000000000000000000000000000000} \
CONFIG.DefaultData {00000000000000000000000000000000} \
CONFIG.Depth {57} \
CONFIG.SyncInitVal {00000000000000000000000000000000} \
CONFIG.Width {32} \
 ] $c_shift_ram_1

  # Create instance: c_shift_ram_2, and set properties
  set c_shift_ram_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_2 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {00000000000000000000000000000000} \
CONFIG.DefaultData {00000000000000000000000000000000} \
CONFIG.Depth {61} \
CONFIG.SyncInitVal {00000000000000000000000000000000} \
CONFIG.Width {32} \
 ] $c_shift_ram_2

  # Create instance: c_shift_ram_3, and set properties
  set c_shift_ram_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_3 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {00000000000000000000000000000000} \
CONFIG.DefaultData {00000000000000000000000000000000} \
CONFIG.Depth {20} \
CONFIG.SyncInitVal {00000000000000000000000000000000} \
CONFIG.Width {32} \
 ] $c_shift_ram_3

  # Create instance: c_shift_ram_4, and set properties
  set c_shift_ram_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_4 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {0} \
CONFIG.DefaultData {0} \
CONFIG.Depth {1} \
CONFIG.SyncInitVal {0} \
CONFIG.Width {1} \
 ] $c_shift_ram_4

  # Create instance: c_shift_ram_5, and set properties
  set c_shift_ram_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_5 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {0} \
CONFIG.DefaultData {0} \
CONFIG.Depth {1} \
CONFIG.SyncInitVal {0} \
CONFIG.Width {1} \
 ] $c_shift_ram_5

  # Create instance: c_shift_ram_6, and set properties
  set c_shift_ram_6 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_6 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {000000000000} \
CONFIG.DefaultData {000000000000} \
CONFIG.Depth {1} \
CONFIG.SyncInitVal {000000000000} \
CONFIG.Width {12} \
 ] $c_shift_ram_6

  # Create instance: c_shift_ram_7, and set properties
  set c_shift_ram_7 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_7 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {000000000000} \
CONFIG.DefaultData {000000000000} \
CONFIG.Depth {1} \
CONFIG.SyncInitVal {000000000000} \
CONFIG.Width {12} \
 ] $c_shift_ram_7

  # Create instance: c_shift_ram_8, and set properties
  set c_shift_ram_8 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_8 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {000000000000} \
CONFIG.DefaultData {000000000000} \
CONFIG.Depth {1} \
CONFIG.SyncInitVal {000000000000} \
CONFIG.Width {12} \
 ] $c_shift_ram_8

  # Create instance: c_shift_ram_9, and set properties
  set c_shift_ram_9 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_9 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {000000000000} \
CONFIG.DefaultData {000000000000} \
CONFIG.Depth {1} \
CONFIG.SyncInitVal {000000000000} \
CONFIG.Width {12} \
 ] $c_shift_ram_9

  # Create instance: c_shift_ram_10, and set properties
  set c_shift_ram_10 [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_shift_ram:12.0 c_shift_ram_10 ]
  set_property -dict [ list \
CONFIG.AsyncInitVal {0} \
CONFIG.DefaultData {0} \
CONFIG.Depth {1} \
CONFIG.SyncInitVal {0} \
CONFIG.Width {1} \
 ] $c_shift_ram_10

  # Create instance: capture_0, and set properties
  set capture_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:capture:1.0 capture_0 ]

  # Create instance: fit_timer_0, and set properties
  set fit_timer_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:fit_timer:2.0 fit_timer_0 ]

  # Create instance: gater_0, and set properties
  set gater_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:gater:1.0 gater_0 ]

  # Create instance: lpf_0, and set properties
  set lpf_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:lpf:1.0 lpf_0 ]

  # Create instance: mult_gen_0, and set properties
  set mult_gen_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mult_gen:12.0 mult_gen_0 ]
  set_property -dict [ list \
CONFIG.CcmImp {Dedicated_Multiplier} \
CONFIG.ClockEnable {true} \
CONFIG.ConstValue {655} \
CONFIG.MultType {Constant_Coefficient_Multiplier} \
CONFIG.OutputWidthHigh {31} \
CONFIG.PipeStages {4} \
CONFIG.PortAType {Unsigned} \
CONFIG.PortAWidth {32} \
CONFIG.SyncClear {false} \
CONFIG.Use_Custom_Output_Width {true} \
 ] $mult_gen_0

  # Create instance: mult_gen_1, and set properties
  set mult_gen_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mult_gen:12.0 mult_gen_1 ]
  set_property -dict [ list \
CONFIG.CcmImp {Dedicated_Multiplier} \
CONFIG.ConstValue {51552} \
CONFIG.MultType {Constant_Coefficient_Multiplier} \
CONFIG.OutputWidthHigh {47} \
CONFIG.PipeStages {4} \
CONFIG.PortAType {Unsigned} \
CONFIG.PortAWidth {32} \
 ] $mult_gen_1

  # Create instance: one_shot_0, and set properties
  set one_shot_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:one_shot:1.0 one_shot_0 ]

  # Create instance: processing_system7_0, and set properties
  set processing_system7_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0 ]
  set_property -dict [ list \
CONFIG.PCW_APU_CLK_RATIO_ENABLE {6:2:1} \
CONFIG.PCW_APU_PERIPHERAL_FREQMHZ {667} \
CONFIG.PCW_CPU_PERIPHERAL_CLKSRC {ARM PLL} \
CONFIG.PCW_CRYSTAL_PERIPHERAL_FREQMHZ {33.333333} \
CONFIG.PCW_DDR_PERIPHERAL_CLKSRC {DDR PLL} \
CONFIG.PCW_ENET0_ENET0_IO {MIO 16 .. 27} \
CONFIG.PCW_ENET0_GRP_MDIO_ENABLE {1} \
CONFIG.PCW_ENET0_GRP_MDIO_IO {MIO 52 .. 53} \
CONFIG.PCW_ENET0_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_ENET0_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_ENET0_PERIPHERAL_FREQMHZ {1000 Mbps} \
CONFIG.PCW_ENET0_RESET_ENABLE {0} \
CONFIG.PCW_EN_CLK0_PORT {1} \
CONFIG.PCW_EN_CLK1_PORT {1} \
CONFIG.PCW_EN_CLK2_PORT {0} \
CONFIG.PCW_EN_CLK3_PORT {0} \
CONFIG.PCW_EN_DDR {1} \
CONFIG.PCW_EN_RST0_PORT {1} \
CONFIG.PCW_EN_RST1_PORT {0} \
CONFIG.PCW_EN_RST2_PORT {0} \
CONFIG.PCW_EN_RST3_PORT {0} \
CONFIG.PCW_FCLK0_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_FCLK1_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_FCLK2_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_FCLK3_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_FCLK_CLK0_BUF {true} \
CONFIG.PCW_FCLK_CLK1_BUF {true} \
CONFIG.PCW_FCLK_CLK2_BUF {false} \
CONFIG.PCW_FCLK_CLK3_BUF {false} \
CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {100} \
CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ {125} \
CONFIG.PCW_FPGA2_PERIPHERAL_FREQMHZ {33.333333} \
CONFIG.PCW_FPGA3_PERIPHERAL_FREQMHZ {50} \
CONFIG.PCW_GPIO_EMIO_GPIO_ENABLE {0} \
CONFIG.PCW_GPIO_MIO_GPIO_ENABLE {1} \
CONFIG.PCW_GPIO_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_I2C0_I2C0_IO {MIO 10 .. 11} \
CONFIG.PCW_I2C0_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_I2C_RESET_ENABLE {0} \
CONFIG.PCW_IRQ_F2P_INTR {1} \
CONFIG.PCW_MIO_0_PULLUP {disabled} \
CONFIG.PCW_MIO_0_SLEW {slow} \
CONFIG.PCW_MIO_10_PULLUP {disabled} \
CONFIG.PCW_MIO_10_SLEW {slow} \
CONFIG.PCW_MIO_11_PULLUP {disabled} \
CONFIG.PCW_MIO_11_SLEW {slow} \
CONFIG.PCW_MIO_12_PULLUP {disabled} \
CONFIG.PCW_MIO_12_SLEW {slow} \
CONFIG.PCW_MIO_13_PULLUP {disabled} \
CONFIG.PCW_MIO_13_SLEW {slow} \
CONFIG.PCW_MIO_14_PULLUP {disabled} \
CONFIG.PCW_MIO_14_SLEW {slow} \
CONFIG.PCW_MIO_15_PULLUP {disabled} \
CONFIG.PCW_MIO_15_SLEW {slow} \
CONFIG.PCW_MIO_16_PULLUP {disabled} \
CONFIG.PCW_MIO_16_SLEW {slow} \
CONFIG.PCW_MIO_17_PULLUP {disabled} \
CONFIG.PCW_MIO_17_SLEW {slow} \
CONFIG.PCW_MIO_18_PULLUP {disabled} \
CONFIG.PCW_MIO_18_SLEW {slow} \
CONFIG.PCW_MIO_19_PULLUP {disabled} \
CONFIG.PCW_MIO_19_SLEW {slow} \
CONFIG.PCW_MIO_1_PULLUP {disabled} \
CONFIG.PCW_MIO_1_SLEW {slow} \
CONFIG.PCW_MIO_20_PULLUP {disabled} \
CONFIG.PCW_MIO_20_SLEW {slow} \
CONFIG.PCW_MIO_21_PULLUP {disabled} \
CONFIG.PCW_MIO_21_SLEW {slow} \
CONFIG.PCW_MIO_22_PULLUP {disabled} \
CONFIG.PCW_MIO_22_SLEW {slow} \
CONFIG.PCW_MIO_23_PULLUP {disabled} \
CONFIG.PCW_MIO_23_SLEW {slow} \
CONFIG.PCW_MIO_24_PULLUP {disabled} \
CONFIG.PCW_MIO_24_SLEW {slow} \
CONFIG.PCW_MIO_25_PULLUP {disabled} \
CONFIG.PCW_MIO_25_SLEW {slow} \
CONFIG.PCW_MIO_26_PULLUP {disabled} \
CONFIG.PCW_MIO_26_SLEW {slow} \
CONFIG.PCW_MIO_27_PULLUP {disabled} \
CONFIG.PCW_MIO_27_SLEW {slow} \
CONFIG.PCW_MIO_28_PULLUP {disabled} \
CONFIG.PCW_MIO_28_SLEW {slow} \
CONFIG.PCW_MIO_29_PULLUP {disabled} \
CONFIG.PCW_MIO_29_SLEW {slow} \
CONFIG.PCW_MIO_2_PULLUP {disabled} \
CONFIG.PCW_MIO_2_SLEW {slow} \
CONFIG.PCW_MIO_30_PULLUP {disabled} \
CONFIG.PCW_MIO_30_SLEW {slow} \
CONFIG.PCW_MIO_31_PULLUP {disabled} \
CONFIG.PCW_MIO_31_SLEW {slow} \
CONFIG.PCW_MIO_32_PULLUP {disabled} \
CONFIG.PCW_MIO_32_SLEW {slow} \
CONFIG.PCW_MIO_33_PULLUP {disabled} \
CONFIG.PCW_MIO_33_SLEW {slow} \
CONFIG.PCW_MIO_34_PULLUP {disabled} \
CONFIG.PCW_MIO_34_SLEW {slow} \
CONFIG.PCW_MIO_35_PULLUP {disabled} \
CONFIG.PCW_MIO_35_SLEW {slow} \
CONFIG.PCW_MIO_36_PULLUP {disabled} \
CONFIG.PCW_MIO_36_SLEW {slow} \
CONFIG.PCW_MIO_37_PULLUP {disabled} \
CONFIG.PCW_MIO_37_SLEW {slow} \
CONFIG.PCW_MIO_38_PULLUP {disabled} \
CONFIG.PCW_MIO_38_SLEW {slow} \
CONFIG.PCW_MIO_39_PULLUP {disabled} \
CONFIG.PCW_MIO_39_SLEW {slow} \
CONFIG.PCW_MIO_3_PULLUP {disabled} \
CONFIG.PCW_MIO_3_SLEW {slow} \
CONFIG.PCW_MIO_40_PULLUP {disabled} \
CONFIG.PCW_MIO_40_SLEW {slow} \
CONFIG.PCW_MIO_41_PULLUP {disabled} \
CONFIG.PCW_MIO_41_SLEW {slow} \
CONFIG.PCW_MIO_42_PULLUP {disabled} \
CONFIG.PCW_MIO_42_SLEW {slow} \
CONFIG.PCW_MIO_43_PULLUP {disabled} \
CONFIG.PCW_MIO_43_SLEW {slow} \
CONFIG.PCW_MIO_44_PULLUP {disabled} \
CONFIG.PCW_MIO_44_SLEW {slow} \
CONFIG.PCW_MIO_45_PULLUP {disabled} \
CONFIG.PCW_MIO_45_SLEW {slow} \
CONFIG.PCW_MIO_46_PULLUP {disabled} \
CONFIG.PCW_MIO_46_SLEW {slow} \
CONFIG.PCW_MIO_47_PULLUP {disabled} \
CONFIG.PCW_MIO_47_SLEW {slow} \
CONFIG.PCW_MIO_48_PULLUP {disabled} \
CONFIG.PCW_MIO_48_SLEW {slow} \
CONFIG.PCW_MIO_49_PULLUP {disabled} \
CONFIG.PCW_MIO_49_SLEW {slow} \
CONFIG.PCW_MIO_4_PULLUP {disabled} \
CONFIG.PCW_MIO_4_SLEW {slow} \
CONFIG.PCW_MIO_50_PULLUP {disabled} \
CONFIG.PCW_MIO_50_SLEW {slow} \
CONFIG.PCW_MIO_51_PULLUP {disabled} \
CONFIG.PCW_MIO_51_SLEW {slow} \
CONFIG.PCW_MIO_52_PULLUP {disabled} \
CONFIG.PCW_MIO_52_SLEW {slow} \
CONFIG.PCW_MIO_53_PULLUP {disabled} \
CONFIG.PCW_MIO_53_SLEW {slow} \
CONFIG.PCW_MIO_5_PULLUP {disabled} \
CONFIG.PCW_MIO_5_SLEW {slow} \
CONFIG.PCW_MIO_6_PULLUP {disabled} \
CONFIG.PCW_MIO_6_SLEW {slow} \
CONFIG.PCW_MIO_7_PULLUP {disabled} \
CONFIG.PCW_MIO_7_SLEW {slow} \
CONFIG.PCW_MIO_8_PULLUP {disabled} \
CONFIG.PCW_MIO_8_SLEW {slow} \
CONFIG.PCW_MIO_9_PULLUP {disabled} \
CONFIG.PCW_MIO_9_SLEW {slow} \
CONFIG.PCW_PACKAGE_NAME {clg400} \
CONFIG.PCW_PRESET_BANK0_VOLTAGE {LVCMOS 3.3V} \
CONFIG.PCW_PRESET_BANK1_VOLTAGE {LVCMOS 1.8V} \
CONFIG.PCW_QSPI_GRP_FBCLK_ENABLE {1} \
CONFIG.PCW_QSPI_GRP_FBCLK_IO {MIO 8} \
CONFIG.PCW_QSPI_GRP_SINGLE_SS_ENABLE {1} \
CONFIG.PCW_QSPI_GRP_SINGLE_SS_IO {MIO 1 .. 6} \
CONFIG.PCW_QSPI_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_QSPI_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_QSPI_PERIPHERAL_FREQMHZ {200} \
CONFIG.PCW_SD0_GRP_CD_ENABLE {1} \
CONFIG.PCW_SD0_GRP_CD_IO {MIO 46} \
CONFIG.PCW_SD0_GRP_WP_ENABLE {1} \
CONFIG.PCW_SD0_GRP_WP_IO {MIO 50} \
CONFIG.PCW_SD0_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_SD0_SD0_IO {MIO 40 .. 45} \
CONFIG.PCW_SDIO_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_SDIO_PERIPHERAL_FREQMHZ {50} \
CONFIG.PCW_TTC0_CLK0_PERIPHERAL_CLKSRC {CPU_1X} \
CONFIG.PCW_TTC0_CLK0_PERIPHERAL_FREQMHZ {111.111115} \
CONFIG.PCW_TTC0_CLK1_PERIPHERAL_CLKSRC {CPU_1X} \
CONFIG.PCW_TTC0_CLK1_PERIPHERAL_FREQMHZ {111.111115} \
CONFIG.PCW_TTC0_CLK2_PERIPHERAL_CLKSRC {CPU_1X} \
CONFIG.PCW_TTC0_CLK2_PERIPHERAL_FREQMHZ {111.111115} \
CONFIG.PCW_TTC0_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_TTC0_TTC0_IO {EMIO} \
CONFIG.PCW_UART1_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_UART1_UART1_IO {MIO 48 .. 49} \
CONFIG.PCW_UART_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_UART_PERIPHERAL_FREQMHZ {50} \
CONFIG.PCW_UIPARAM_ACT_DDR_FREQ_MHZ {533.333374} \
CONFIG.PCW_UIPARAM_DDR_BL {8} \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY0 {0.294} \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY1 {0.298} \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY2 {0.338} \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY3 {0.334} \
CONFIG.PCW_UIPARAM_DDR_BUS_WIDTH {32 Bit} \
CONFIG.PCW_UIPARAM_DDR_CLOCK_0_LENGTH_MM {39.7} \
CONFIG.PCW_UIPARAM_DDR_CLOCK_1_LENGTH_MM {39.7} \
CONFIG.PCW_UIPARAM_DDR_CLOCK_2_LENGTH_MM {54.14} \
CONFIG.PCW_UIPARAM_DDR_CLOCK_3_LENGTH_MM {54.14} \
CONFIG.PCW_UIPARAM_DDR_CWL {6} \
CONFIG.PCW_UIPARAM_DDR_DEVICE_CAPACITY {4096 MBits} \
CONFIG.PCW_UIPARAM_DDR_DQS_0_LENGTH_MM {50.05} \
CONFIG.PCW_UIPARAM_DDR_DQS_1_LENGTH_MM {50.43} \
CONFIG.PCW_UIPARAM_DDR_DQS_2_LENGTH_MM {50.10} \
CONFIG.PCW_UIPARAM_DDR_DQS_3_LENGTH_MM {50.01} \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 {-0.073} \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_1 {-0.072} \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_2 {0.024} \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_3 {0.023} \
CONFIG.PCW_UIPARAM_DDR_DQ_0_LENGTH_MM {49.59} \
CONFIG.PCW_UIPARAM_DDR_DQ_1_LENGTH_MM {51.74} \
CONFIG.PCW_UIPARAM_DDR_DQ_2_LENGTH_MM {50.32} \
CONFIG.PCW_UIPARAM_DDR_DQ_3_LENGTH_MM {48.55} \
CONFIG.PCW_UIPARAM_DDR_DRAM_WIDTH {16 Bits} \
CONFIG.PCW_UIPARAM_DDR_MEMORY_TYPE {DDR 3 (Low Voltage)} \
CONFIG.PCW_UIPARAM_DDR_PARTNO {MT41K256M16 RE-125} \
CONFIG.PCW_UIPARAM_DDR_SPEED_BIN {DDR3_1066F} \
CONFIG.PCW_UIPARAM_DDR_TRAIN_DATA_EYE {1} \
CONFIG.PCW_UIPARAM_DDR_TRAIN_READ_GATE {1} \
CONFIG.PCW_UIPARAM_DDR_TRAIN_WRITE_LEVEL {1} \
CONFIG.PCW_UIPARAM_DDR_T_FAW {40.0} \
CONFIG.PCW_UIPARAM_DDR_T_RAS_MIN {35.0} \
CONFIG.PCW_UIPARAM_DDR_T_RC {48.75} \
CONFIG.PCW_UIPARAM_DDR_USE_INTERNAL_VREF {1} \
CONFIG.PCW_USB0_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_USB0_PERIPHERAL_FREQMHZ {60} \
CONFIG.PCW_USB0_RESET_ENABLE {1} \
CONFIG.PCW_USB0_RESET_IO {MIO 7} \
CONFIG.PCW_USB0_USB0_IO {MIO 28 .. 39} \
CONFIG.PCW_USE_FABRIC_INTERRUPT {1} \
CONFIG.PCW_USE_M_AXI_GP0 {1} \
CONFIG.PCW_USE_M_AXI_GP1 {0} \
CONFIG.PCW_USE_S_AXI_HP0 {1} \
 ] $processing_system7_0

  # Create instance: processing_system7_0_axi_periph, and set properties
  set processing_system7_0_axi_periph [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 processing_system7_0_axi_periph ]
  set_property -dict [ list \
CONFIG.NUM_MI {21} \
 ] $processing_system7_0_axi_periph

  # Create instance: readout_0, and set properties
  set readout_0 [ create_bd_cell -type ip -vlnv rmdinc.com:user:readout:1.0 readout_0 ]

  # Create instance: rst_processing_system7_0_100M, and set properties
  set rst_processing_system7_0_100M [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 rst_processing_system7_0_100M ]

  # Create instance: util_vector_logic_0, and set properties
  set util_vector_logic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_0 ]
  set_property -dict [ list \
CONFIG.C_OPERATION {or} \
CONFIG.C_SIZE {1} \
 ] $util_vector_logic_0

  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [ list \
CONFIG.NUM_PORTS {2} \
 ] $xlconcat_0

  # Create instance: xlconcat_1, and set properties
  set xlconcat_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_1 ]
  set_property -dict [ list \
CONFIG.IN0_WIDTH {32} \
 ] $xlconcat_1

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property -dict [ list \
CONFIG.CONST_VAL {0} \
CONFIG.CONST_WIDTH {3} \
 ] $xlconstant_0

  # Create instance: xlconstant_1, and set properties
  set xlconstant_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_1 ]
  set_property -dict [ list \
CONFIG.CONST_VAL {0} \
 ] $xlconstant_1

  # Create interface connections
  connect_bd_intf_net -intf_net Master_Slave_Stream_v1_0_0_m00_axis [get_bd_intf_pins Master_Slave_Stream_v1_0_0/m00_axis] [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM]
  connect_bd_intf_net -intf_net S00_AXI_1 [get_bd_intf_pins processing_system7_0/M_AXI_GP0] [get_bd_intf_pins processing_system7_0_axi_periph/S00_AXI]
  connect_bd_intf_net -intf_net axi_dma_0_M_AXI_S2MM [get_bd_intf_pins axi_dma_0/M_AXI_S2MM] [get_bd_intf_pins axi_mem_intercon/S00_AXI]
  connect_bd_intf_net -intf_net axi_mem_intercon_M00_AXI [get_bd_intf_pins axi_mem_intercon/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP0]
  connect_bd_intf_net -intf_net processing_system7_0_DDR [get_bd_intf_ports DDR] [get_bd_intf_pins processing_system7_0/DDR]
  connect_bd_intf_net -intf_net processing_system7_0_FIXED_IO [get_bd_intf_ports FIXED_IO] [get_bd_intf_pins processing_system7_0/FIXED_IO]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M00_AXI [get_bd_intf_pins axi_dma_0/S_AXI_LITE] [get_bd_intf_pins processing_system7_0_axi_periph/M00_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M01_AXI [get_bd_intf_pins axi_gpio_0/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M01_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M02_AXI [get_bd_intf_pins axi_gpio_1/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M02_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M03_AXI [get_bd_intf_pins axi_gpio_2/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M03_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M04_AXI [get_bd_intf_pins axi_gpio_3/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M04_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M05_AXI [get_bd_intf_pins axi_gpio_4/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M05_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M06_AXI [get_bd_intf_pins axi_gpio_5/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M06_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M07_AXI [get_bd_intf_pins axi_gpio_6/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M07_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M08_AXI [get_bd_intf_pins axi_gpio_7/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M08_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M09_AXI [get_bd_intf_pins axi_gpio_8/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M09_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M10_AXI [get_bd_intf_pins axi_gpio_9/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M10_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M11_AXI [get_bd_intf_pins axi_gpio_10/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M11_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M12_AXI [get_bd_intf_pins axi_gpio_11/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M12_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M14_AXI [get_bd_intf_pins axi_gpio_13/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M14_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M15_AXI [get_bd_intf_pins axi_gpio_14/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M15_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M16_AXI [get_bd_intf_pins axi_gpio_15/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M16_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M17_AXI [get_bd_intf_pins axi_gpio_16/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M17_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M18_AXI [get_bd_intf_pins axi_gpio_17/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M18_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M19_AXI [get_bd_intf_pins axi_gpio_18/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M19_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M20_AXI [get_bd_intf_pins axi_gpio_19/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M20_AXI]

  # Create port connections
  connect_bd_net -net AA_0_dout [get_bd_pins AA_0/dout] [get_bd_pins DFF_0/AAvg] [get_bd_pins TriggerV2_0/AAvg] [get_bd_pins c_shift_ram_0/D] [get_bd_pins mult_gen_0/A] [get_bd_pins xlconcat_1/In0]
  connect_bd_net -net AA_Integrator6Buf_0_dout [get_bd_pins AA_Integrator6Buf_0/dout] [get_bd_pins readout_0/AA]
  connect_bd_net -net AA_Integrator6Buf_0_wrcnt [get_bd_pins AA_Integrator6Buf_0/wrcnt] [get_bd_pins axi_gpio_11/gpio_io_i]
  connect_bd_net -net DFF_0_dout [get_bd_pins DFF_0/dout] [get_bd_pins c_shift_ram_1/D]
  connect_bd_net -net DFF_Integrator6Buf_0_dout [get_bd_pins DFF_Integrator6Buf_0/dout] [get_bd_pins readout_0/DFF]
  connect_bd_net -net DFF_Integrator6Buf_0_rdcnt [get_bd_pins DFF_Integrator6Buf_0/rdcnt] [get_bd_pins axi_gpio_19/gpio_io_i]
  connect_bd_net -net DFF_Integrator6Buf_0_wrcnt [get_bd_pins DFF_Integrator6Buf_0/wrcnt] [get_bd_pins axi_gpio_13/gpio_io_i]
  connect_bd_net -net LPF_Integrator6buf_0_dout [get_bd_pins LPF_Integrator6buf_0/dout] [get_bd_pins readout_0/LPF]
  connect_bd_net -net MUX6_0_dout [get_bd_pins MUX6_0/dout] [get_bd_pins Master_Slave_Stream_v1_0_0/din]
  connect_bd_net -net MUX6_0_en_integration [get_bd_pins MUX6_0/en_integration] [get_bd_pins gater_0/off]
  connect_bd_net -net MUX6_0_logic_out [get_bd_pins MUX6_0/logic_out] [get_bd_pins Master_Slave_Stream_v1_0_0/wren]
  connect_bd_net -net TTL_In_1 [get_bd_ports TTL_In] [get_bd_pins LPF_Integrator6buf_0/ttl_in] [get_bd_pins one_shot_0/D]
  connect_bd_net -net TriggerV2_0_we [get_bd_pins TriggerV2_0/we] [get_bd_pins c_counter_binary_0/CLK]
  connect_bd_net -net Trigger_0_event_done [get_bd_pins Trigger_original_smaller_0/event_done] [get_bd_pins c_shift_ram_4/D] [get_bd_pins gater_0/rst1]
  connect_bd_net -net Trigger_0_we [get_bd_pins AA_Integrator6Buf_0/en] [get_bd_pins DFF_Integrator6Buf_0/en] [get_bd_pins LPF_Integrator6buf_0/en] [get_bd_pins MUX6_0/EN_A] [get_bd_pins MUX6_0/EN_B] [get_bd_pins MUX6_0/EN_C] [get_bd_pins MUX6_0/EN_D] [get_bd_pins Trigger_original_smaller_0/we]
  connect_bd_net -net Trigger_original_smaller_0_dout [get_bd_pins Trigger_original_smaller_0/dout] [get_bd_pins c_shift_ram_2/D]
  connect_bd_net -net axi_dma_0_s2mm_introut [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
  connect_bd_net -net axi_gpio_0_gpio_io_o [get_bd_pins axi_gpio_0/gpio_io_i] [get_bd_pins axi_gpio_0/gpio_io_o] [get_bd_pins c_shift_ram_6/D]
  connect_bd_net -net axi_gpio_10_gpio_io_o [get_bd_pins TriggerV2_0/threshold] [get_bd_pins Trigger_original_smaller_0/threshold] [get_bd_pins axi_gpio_10/gpio_io_i] [get_bd_pins axi_gpio_10/gpio_io_o]
  connect_bd_net -net axi_gpio_14_gpio_io_o [get_bd_pins MUX6_0/cntrl] [get_bd_pins axi_gpio_14/gpio_io_o]
  connect_bd_net -net axi_gpio_15_gpio_io_o [get_bd_pins axi_gpio_15/gpio_io_o] [get_bd_pins readout_0/cntrl]
  connect_bd_net -net axi_gpio_16_gpio_io_o [get_bd_pins Master_Slave_Stream_v1_0_0/FrameSize] [get_bd_pins axi_gpio_16/gpio_io_o]
  connect_bd_net -net axi_gpio_17_gpio_io_o [get_bd_pins Master_Slave_Stream_v1_0_0/En] [get_bd_pins axi_gpio_17/gpio_io_o]
  connect_bd_net -net axi_gpio_18_gpio_io_o [get_bd_pins axi_gpio_18/gpio_io_o] [get_bd_pins capture_0/wren]
  connect_bd_net -net axi_gpio_1_gpio_io_o [get_bd_pins axi_gpio_1/gpio_io_i] [get_bd_pins axi_gpio_1/gpio_io_o] [get_bd_pins c_shift_ram_7/D]
  connect_bd_net -net axi_gpio_2_gpio_io_o [get_bd_pins axi_gpio_2/gpio_io_i] [get_bd_pins axi_gpio_2/gpio_io_o] [get_bd_pins c_shift_ram_8/D]
  connect_bd_net -net axi_gpio_3_gpio_io_o [get_bd_pins axi_gpio_3/gpio_io_i] [get_bd_pins axi_gpio_3/gpio_io_o] [get_bd_pins c_shift_ram_9/D]
  connect_bd_net -net axi_gpio_4_gpio_io_o [get_bd_pins LPF_Integrator6buf_0/i1s] [get_bd_pins axi_gpio_4/gpio_io_i] [get_bd_pins axi_gpio_4/gpio_io_o]
  connect_bd_net -net axi_gpio_5_gpio_io_o [get_bd_pins LPF_Integrator6buf_0/i2s] [get_bd_pins axi_gpio_5/gpio_io_i] [get_bd_pins axi_gpio_5/gpio_io_o]
  connect_bd_net -net axi_gpio_6_gpio_io_o [get_bd_pins LPF_Integrator6buf_0/i3s] [get_bd_pins axi_gpio_6/gpio_io_i] [get_bd_pins axi_gpio_6/gpio_io_o]
  connect_bd_net -net axi_gpio_7_gpio_io_o [get_bd_pins DFF_Integrator6Buf_0/i1s] [get_bd_pins axi_gpio_7/gpio_io_i] [get_bd_pins axi_gpio_7/gpio_io_o]
  connect_bd_net -net axi_gpio_8_gpio_io_o [get_bd_pins DFF_Integrator6Buf_0/i2s] [get_bd_pins axi_gpio_8/gpio_io_i] [get_bd_pins axi_gpio_8/gpio_io_o]
  connect_bd_net -net axi_gpio_9_gpio_io_o [get_bd_pins axi_gpio_9/gpio_io_o] [get_bd_pins c_shift_ram_5/D]
  connect_bd_net -net c_counter_binary_0_Q [get_bd_pins AA_Integrator6Buf_0/TotCounts] [get_bd_pins c_counter_binary_0/Q]
  connect_bd_net -net c_shift_ram_0_Q [get_bd_pins AA_Integrator6Buf_0/din] [get_bd_pins MUX6_0/A] [get_bd_pins c_shift_ram_0/Q]
  connect_bd_net -net c_shift_ram_10_Q [get_bd_pins MUX6_0/EN_E] [get_bd_pins c_shift_ram_10/Q]
  connect_bd_net -net c_shift_ram_1_Q [get_bd_pins DFF_Integrator6Buf_0/din] [get_bd_pins MUX6_0/C] [get_bd_pins c_shift_ram_1/Q]
  connect_bd_net -net c_shift_ram_2_Q [get_bd_pins MUX6_0/D] [get_bd_pins c_shift_ram_2/Q]
  connect_bd_net -net c_shift_ram_3_Q [get_bd_pins LPF_Integrator6buf_0/din] [get_bd_pins MUX6_0/B] [get_bd_pins c_shift_ram_3/Q]
  connect_bd_net -net c_shift_ram_4_Q [get_bd_pins AA_Integrator6Buf_0/rst] [get_bd_pins DFF_Integrator6Buf_0/rst] [get_bd_pins LPF_Integrator6buf_0/rst] [get_bd_pins c_shift_ram_4/Q]
  connect_bd_net -net c_shift_ram_6_Q [get_bd_pins AA_Integrator6Buf_0/i1s] [get_bd_pins c_shift_ram_6/Q]
  connect_bd_net -net c_shift_ram_7_Q [get_bd_pins AA_Integrator6Buf_0/i2s] [get_bd_pins c_shift_ram_7/Q]
  connect_bd_net -net c_shift_ram_8_Q [get_bd_pins AA_Integrator6Buf_0/i3s] [get_bd_pins c_shift_ram_8/Q]
  connect_bd_net -net c_shift_ram_9_Q [get_bd_pins AA_Integrator6Buf_0/i4s] [get_bd_pins c_shift_ram_9/Q]
  connect_bd_net -net capture_0_clkout [get_bd_pins AA_0/clk] [get_bd_pins AA_Integrator6Buf_0/clk] [get_bd_pins DFF_0/clk] [get_bd_pins DFF_Integrator6Buf_0/clk] [get_bd_pins LPF_Integrator6buf_0/clk] [get_bd_pins MUX6_0/clk] [get_bd_pins Master_Slave_Stream_v1_0_0/wrclk] [get_bd_pins TriggerV2_0/clk] [get_bd_pins Trigger_original_smaller_0/clk] [get_bd_pins c_shift_ram_0/CLK] [get_bd_pins c_shift_ram_1/CLK] [get_bd_pins c_shift_ram_10/CLK] [get_bd_pins c_shift_ram_2/CLK] [get_bd_pins c_shift_ram_3/CLK] [get_bd_pins c_shift_ram_4/CLK] [get_bd_pins c_shift_ram_5/CLK] [get_bd_pins capture_0/clkout] [get_bd_pins gater_0/clk] [get_bd_pins lpf_0/clk] [get_bd_pins mult_gen_0/CLK] [get_bd_pins mult_gen_1/CLK] [get_bd_pins one_shot_0/clk] [get_bd_pins readout_0/clk]
  connect_bd_net -net capture_0_dout [get_bd_pins AA_0/din] [get_bd_pins capture_0/dout]
  connect_bd_net -net capture_0_load [get_bd_pins AA_0/en] [get_bd_pins DFF_0/en] [get_bd_pins capture_0/load] [get_bd_pins lpf_0/load]
  connect_bd_net -net clkin_n_1 [get_bd_ports clkin_n] [get_bd_pins capture_0/clkin_n]
  connect_bd_net -net clkin_p_1 [get_bd_ports clkin_p] [get_bd_pins capture_0/clkin_p]
  connect_bd_net -net din_n_1 [get_bd_ports din_n] [get_bd_pins capture_0/din_n]
  connect_bd_net -net din_p_1 [get_bd_ports din_p] [get_bd_pins capture_0/din_p]
  connect_bd_net -net fit_timer_0_Interrupt [get_bd_pins fit_timer_0/Interrupt] [get_bd_pins xlconcat_0/In1]
  connect_bd_net -net gater_0_rst [get_bd_pins Master_Slave_Stream_v1_0_0/rst] [get_bd_pins gater_0/rst]
  connect_bd_net -net lpf_0_CE_O [get_bd_pins lpf_0/CE_O] [get_bd_pins mult_gen_0/CE]
  connect_bd_net -net lpf_0_L_n1 [get_bd_pins lpf_0/L_n1] [get_bd_pins mult_gen_1/A]
  connect_bd_net -net lpf_0_dout [get_bd_pins c_shift_ram_3/D] [get_bd_pins lpf_0/dout]
  connect_bd_net -net memReset_0_rst [get_bd_pins AA_Integrator6Buf_0/clr] [get_bd_pins DFF_Integrator6Buf_0/clr] [get_bd_pins LPF_Integrator6buf_0/clr] [get_bd_pins c_shift_ram_5/Q] [get_bd_pins gater_0/rst2]
  connect_bd_net -net mult_gen_0_P [get_bd_pins lpf_0/P1] [get_bd_pins mult_gen_0/P]
  connect_bd_net -net mult_gen_1_P [get_bd_pins lpf_0/P2] [get_bd_pins mult_gen_1/P]
  connect_bd_net -net one_shot_0_Q [get_bd_pins LPF_Integrator6buf_0/ttl_on] [get_bd_pins one_shot_0/Q] [get_bd_pins util_vector_logic_0/Op1]
  connect_bd_net -net one_shot_0_Qn [get_bd_pins LPF_Integrator6buf_0/ttl_off] [get_bd_pins one_shot_0/Qn] [get_bd_pins util_vector_logic_0/Op2]
  connect_bd_net -net processing_system7_0_FCLK_CLK0 [get_bd_pins Master_Slave_Stream_v1_0_0/m00_axis_aclk] [get_bd_pins Master_Slave_Stream_v1_0_0/s00_axis_aclk] [get_bd_pins axi_dma_0/m_axi_s2mm_aclk] [get_bd_pins axi_dma_0/s_axi_lite_aclk] [get_bd_pins axi_gpio_0/s_axi_aclk] [get_bd_pins axi_gpio_1/s_axi_aclk] [get_bd_pins axi_gpio_10/s_axi_aclk] [get_bd_pins axi_gpio_11/s_axi_aclk] [get_bd_pins axi_gpio_13/s_axi_aclk] [get_bd_pins axi_gpio_14/s_axi_aclk] [get_bd_pins axi_gpio_15/s_axi_aclk] [get_bd_pins axi_gpio_16/s_axi_aclk] [get_bd_pins axi_gpio_17/s_axi_aclk] [get_bd_pins axi_gpio_18/s_axi_aclk] [get_bd_pins axi_gpio_19/s_axi_aclk] [get_bd_pins axi_gpio_2/s_axi_aclk] [get_bd_pins axi_gpio_3/s_axi_aclk] [get_bd_pins axi_gpio_4/s_axi_aclk] [get_bd_pins axi_gpio_5/s_axi_aclk] [get_bd_pins axi_gpio_6/s_axi_aclk] [get_bd_pins axi_gpio_7/s_axi_aclk] [get_bd_pins axi_gpio_8/s_axi_aclk] [get_bd_pins axi_gpio_9/s_axi_aclk] [get_bd_pins axi_mem_intercon/ACLK] [get_bd_pins axi_mem_intercon/M00_ACLK] [get_bd_pins axi_mem_intercon/S00_ACLK] [get_bd_pins c_shift_ram_6/CLK] [get_bd_pins c_shift_ram_7/CLK] [get_bd_pins c_shift_ram_8/CLK] [get_bd_pins c_shift_ram_9/CLK] [get_bd_pins fit_timer_0/Clk] [get_bd_pins processing_system7_0/FCLK_CLK0] [get_bd_pins processing_system7_0/M_AXI_GP0_ACLK] [get_bd_pins processing_system7_0/S_AXI_HP0_ACLK] [get_bd_pins processing_system7_0_axi_periph/ACLK] [get_bd_pins processing_system7_0_axi_periph/M00_ACLK] [get_bd_pins processing_system7_0_axi_periph/M01_ACLK] [get_bd_pins processing_system7_0_axi_periph/M02_ACLK] [get_bd_pins processing_system7_0_axi_periph/M03_ACLK] [get_bd_pins processing_system7_0_axi_periph/M04_ACLK] [get_bd_pins processing_system7_0_axi_periph/M05_ACLK] [get_bd_pins processing_system7_0_axi_periph/M06_ACLK] [get_bd_pins processing_system7_0_axi_periph/M07_ACLK] [get_bd_pins processing_system7_0_axi_periph/M08_ACLK] [get_bd_pins processing_system7_0_axi_periph/M09_ACLK] [get_bd_pins processing_system7_0_axi_periph/M10_ACLK] [get_bd_pins processing_system7_0_axi_periph/M11_ACLK] [get_bd_pins processing_system7_0_axi_periph/M12_ACLK] [get_bd_pins processing_system7_0_axi_periph/M13_ACLK] [get_bd_pins processing_system7_0_axi_periph/M14_ACLK] [get_bd_pins processing_system7_0_axi_periph/M15_ACLK] [get_bd_pins processing_system7_0_axi_periph/M16_ACLK] [get_bd_pins processing_system7_0_axi_periph/M17_ACLK] [get_bd_pins processing_system7_0_axi_periph/M18_ACLK] [get_bd_pins processing_system7_0_axi_periph/M19_ACLK] [get_bd_pins processing_system7_0_axi_periph/M20_ACLK] [get_bd_pins processing_system7_0_axi_periph/S00_ACLK] [get_bd_pins rst_processing_system7_0_100M/slowest_sync_clk]
  connect_bd_net -net processing_system7_0_FCLK_CLK1 [get_bd_pins DFF_Integrator6Buf_0/timer_clk] [get_bd_pins processing_system7_0/FCLK_CLK1]
  connect_bd_net -net processing_system7_0_FCLK_RESET0_N [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins rst_processing_system7_0_100M/ext_reset_in]
  connect_bd_net -net readout_0_dout [get_bd_pins MUX6_0/E] [get_bd_pins readout_0/dout]
  connect_bd_net -net readout_0_en_a [get_bd_pins AA_Integrator6Buf_0/rden] [get_bd_pins readout_0/en_a]
  connect_bd_net -net readout_0_en_d [get_bd_pins DFF_Integrator6Buf_0/rden] [get_bd_pins readout_0/en_d]
  connect_bd_net -net readout_0_en_l [get_bd_pins LPF_Integrator6buf_0/rden] [get_bd_pins readout_0/en_l]
  connect_bd_net -net readout_0_we [get_bd_pins c_shift_ram_10/D] [get_bd_pins readout_0/we]
  connect_bd_net -net rst_processing_system7_0_100M_interconnect_aresetn [get_bd_pins axi_mem_intercon/ARESETN] [get_bd_pins processing_system7_0_axi_periph/ARESETN] [get_bd_pins rst_processing_system7_0_100M/interconnect_aresetn]
  connect_bd_net -net rst_processing_system7_0_100M_peripheral_aresetn [get_bd_pins Master_Slave_Stream_v1_0_0/m00_axis_aresetn] [get_bd_pins Master_Slave_Stream_v1_0_0/s00_axis_aresetn] [get_bd_pins axi_dma_0/axi_resetn] [get_bd_pins axi_gpio_0/s_axi_aresetn] [get_bd_pins axi_gpio_1/s_axi_aresetn] [get_bd_pins axi_gpio_10/s_axi_aresetn] [get_bd_pins axi_gpio_11/s_axi_aresetn] [get_bd_pins axi_gpio_13/s_axi_aresetn] [get_bd_pins axi_gpio_14/s_axi_aresetn] [get_bd_pins axi_gpio_15/s_axi_aresetn] [get_bd_pins axi_gpio_16/s_axi_aresetn] [get_bd_pins axi_gpio_17/s_axi_aresetn] [get_bd_pins axi_gpio_18/s_axi_aresetn] [get_bd_pins axi_gpio_19/s_axi_aresetn] [get_bd_pins axi_gpio_2/s_axi_aresetn] [get_bd_pins axi_gpio_3/s_axi_aresetn] [get_bd_pins axi_gpio_4/s_axi_aresetn] [get_bd_pins axi_gpio_5/s_axi_aresetn] [get_bd_pins axi_gpio_6/s_axi_aresetn] [get_bd_pins axi_gpio_7/s_axi_aresetn] [get_bd_pins axi_gpio_8/s_axi_aresetn] [get_bd_pins axi_gpio_9/s_axi_aresetn] [get_bd_pins axi_mem_intercon/M00_ARESETN] [get_bd_pins axi_mem_intercon/S00_ARESETN] [get_bd_pins fit_timer_0/Rst] [get_bd_pins processing_system7_0_axi_periph/M00_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M01_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M02_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M03_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M04_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M05_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M06_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M07_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M08_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M09_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M10_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M11_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M12_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M13_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M14_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M15_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M16_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M17_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M18_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M19_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M20_ARESETN] [get_bd_pins processing_system7_0_axi_periph/S00_ARESETN] [get_bd_pins rst_processing_system7_0_100M/peripheral_aresetn]
  connect_bd_net -net util_vector_logic_0_Res [get_bd_pins util_vector_logic_0/Res] [get_bd_pins xlconcat_1/In1]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins processing_system7_0/IRQ_F2P] [get_bd_pins xlconcat_0/dout]
  connect_bd_net -net xlconcat_1_dout [get_bd_pins Trigger_original_smaller_0/AAvg] [get_bd_pins xlconcat_1/dout]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins capture_0/cntrl_bits] [get_bd_pins xlconstant_0/dout]
  connect_bd_net -net xlconstant_1_dout [get_bd_pins Master_Slave_Stream_v1_0_0/Axi_En] [get_bd_pins xlconstant_1/dout]

  # Create address segments
  create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces axi_dma_0/Data_S2MM] [get_bd_addr_segs processing_system7_0/S_AXI_HP0/HP0_DDR_LOWOCM] SEG_processing_system7_0_HP0_DDR_LOWOCM
  create_bd_addr_seg -range 0x10000 -offset 0x40400000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_dma_0/S_AXI_LITE/Reg] SEG_axi_dma_0_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41200000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_0/S_AXI/Reg] SEG_axi_gpio_0_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41220000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_10/S_AXI/Reg] SEG_axi_gpio_10_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41230000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_11/S_AXI/Reg] SEG_axi_gpio_11_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41250000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_13/S_AXI/Reg] SEG_axi_gpio_13_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41260000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_14/S_AXI/Reg] SEG_axi_gpio_14_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41270000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_15/S_AXI/Reg] SEG_axi_gpio_15_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41280000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_16/S_AXI/Reg] SEG_axi_gpio_16_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41290000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_17/S_AXI/Reg] SEG_axi_gpio_17_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x412A0000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_18/S_AXI/Reg] SEG_axi_gpio_18_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41330000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_19/S_AXI/Reg] SEG_axi_gpio_19_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41210000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_1/S_AXI/Reg] SEG_axi_gpio_1_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x412B0000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_2/S_AXI/Reg] SEG_axi_gpio_2_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x412C0000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_3/S_AXI/Reg] SEG_axi_gpio_3_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x412D0000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_4/S_AXI/Reg] SEG_axi_gpio_4_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x412E0000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_5/S_AXI/Reg] SEG_axi_gpio_5_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x412F0000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_6/S_AXI/Reg] SEG_axi_gpio_6_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41300000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_7/S_AXI/Reg] SEG_axi_gpio_7_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41310000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_8/S_AXI/Reg] SEG_axi_gpio_8_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x41320000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_9/S_AXI/Reg] SEG_axi_gpio_9_Reg

  # Perform GUI Layout
  regenerate_bd_layout -layout_string {
   guistr: "# # String gsaved with Nlview 6.5.5  2015-06-26 bk=1.3371 VDI=38 GEI=35 GUI=JA:1.6
#  -string -flagsOSRD
preplace port DDR -pg 1 -y 1640 -defaultsOSRD
preplace port clkin_p -pg 1 -y 2470 -defaultsOSRD
preplace port TTL_In -pg 1 -y 1900 -defaultsOSRD
preplace port FIXED_IO -pg 1 -y 1660 -defaultsOSRD
preplace port clkin_n -pg 1 -y 2490 -defaultsOSRD
preplace portBus din_n -pg 1 -y 2550 -defaultsOSRD
preplace portBus din_p -pg 1 -y 2530 -defaultsOSRD
preplace inst c_shift_ram_4 -pg 1 -lvl 7 -y 1960 -defaultsOSRD
preplace inst axi_gpio_10 -pg 1 -lvl 14 -y 1310 -defaultsOSRD
preplace inst axi_gpio_8 -pg 1 -lvl 14 -y 1160 -defaultsOSRD
preplace inst MUX6_0 -pg 1 -lvl 11 -y 2220 -defaultsOSRD
preplace inst DFF_Integrator6Buf_0 -pg 1 -lvl 8 -y 2200 -defaultsOSRD
preplace inst c_shift_ram_5 -pg 1 -lvl 7 -y 2430 -defaultsOSRD
preplace inst axi_gpio_11 -pg 1 -lvl 14 -y 1600 -defaultsOSRD
preplace inst axi_gpio_9 -pg 1 -lvl 14 -y 2590 -defaultsOSRD
preplace inst axi_dma_0 -pg 1 -lvl 14 -y 2430 -defaultsOSRD
preplace inst TriggerV2_0 -pg 1 -lvl 6 -y 1970 -defaultsOSRD
preplace inst AA_Integrator6Buf_0 -pg 1 -lvl 8 -y 1520 -defaultsOSRD
preplace inst xlconstant_0 -pg 1 -lvl 1 -y 2600 -defaultsOSRD
preplace inst rst_processing_system7_0_100M -pg 1 -lvl 12 -y 1830 -defaultsOSRD
preplace inst gater_0 -pg 1 -lvl 12 -y 2100 -defaultsOSRD
preplace inst c_shift_ram_6 -pg 1 -lvl 7 -y 1180 -defaultsOSRD
preplace inst xlconstant_1 -pg 1 -lvl 12 -y 1950 -defaultsOSRD
preplace inst capture_0 -pg 1 -lvl 2 -y 2510 -defaultsOSRD
preplace inst c_shift_ram_7 -pg 1 -lvl 7 -y 1300 -defaultsOSRD
preplace inst axi_gpio_13 -pg 1 -lvl 14 -y 1430 -defaultsOSRD
preplace inst LPF_Integrator6buf_0 -pg 1 -lvl 8 -y 1890 -defaultsOSRD
preplace inst c_shift_ram_10 -pg 1 -lvl 10 -y 2170 -defaultsOSRD
preplace inst fit_timer_0 -pg 1 -lvl 14 -y 2700 -defaultsOSRD
preplace inst c_shift_ram_8 -pg 1 -lvl 7 -y 1440 -defaultsOSRD
preplace inst axi_gpio_14 -pg 1 -lvl 14 -y 1840 -defaultsOSRD
preplace inst Trigger_original_smaller_0 -pg 1 -lvl 6 -y 2090 -defaultsOSRD
preplace inst xlconcat_0 -pg 1 -lvl 15 -y 2460 -defaultsOSRD
preplace inst util_vector_logic_0 -pg 1 -lvl 4 -y 2430 -defaultsOSRD
preplace inst mult_gen_0 -pg 1 -lvl 5 -y 2240 -defaultsOSRD
preplace inst c_shift_ram_9 -pg 1 -lvl 7 -y 1540 -defaultsOSRD
preplace inst axi_gpio_15 -pg 1 -lvl 14 -y 1020 -defaultsOSRD
preplace inst axi_gpio_0 -pg 1 -lvl 14 -y 60 -defaultsOSRD
preplace inst xlconcat_1 -pg 1 -lvl 5 -y 2420 -defaultsOSRD
preplace inst mult_gen_1 -pg 1 -lvl 5 -y 2100 -defaultsOSRD
preplace inst c_counter_binary_0 -pg 1 -lvl 7 -y 1630 -defaultsOSRD
preplace inst axi_gpio_16 -pg 1 -lvl 14 -y 1960 -defaultsOSRD
preplace inst axi_gpio_1 -pg 1 -lvl 14 -y 180 -defaultsOSRD
preplace inst one_shot_0 -pg 1 -lvl 3 -y 2430 -defaultsOSRD
preplace inst axi_gpio_17 -pg 1 -lvl 14 -y 2100 -defaultsOSRD
preplace inst axi_gpio_2 -pg 1 -lvl 14 -y 300 -defaultsOSRD
preplace inst readout_0 -pg 1 -lvl 9 -y 2160 -defaultsOSRD
preplace inst axi_gpio_18 -pg 1 -lvl 14 -y 2810 -defaultsOSRD
preplace inst axi_gpio_3 -pg 1 -lvl 14 -y 420 -defaultsOSRD
preplace inst c_shift_ram_0 -pg 1 -lvl 7 -y 1830 -defaultsOSRD
preplace inst axi_gpio_19 -pg 1 -lvl 14 -y 2260 -defaultsOSRD
preplace inst axi_gpio_4 -pg 1 -lvl 14 -y 540 -defaultsOSRD
preplace inst Master_Slave_Stream_v1_0_0 -pg 1 -lvl 13 -y 2010 -defaultsOSRD
preplace inst c_shift_ram_1 -pg 1 -lvl 7 -y 2300 -defaultsOSRD
preplace inst axi_gpio_5 -pg 1 -lvl 14 -y 660 -defaultsOSRD
preplace inst lpf_0 -pg 1 -lvl 6 -y 2250 -defaultsOSRD
preplace inst c_shift_ram_2 -pg 1 -lvl 10 -y 2300 -defaultsOSRD
preplace inst axi_mem_intercon -pg 1 -lvl 15 -y 1750 -defaultsOSRD
preplace inst axi_gpio_6 -pg 1 -lvl 14 -y 780 -defaultsOSRD
preplace inst AA_0 -pg 1 -lvl 4 -y 2300 -defaultsOSRD
preplace inst processing_system7_0_axi_periph -pg 1 -lvl 13 -y 950 -defaultsOSRD
preplace inst processing_system7_0 -pg 1 -lvl 16 -y 1730 -defaultsOSRD
preplace inst c_shift_ram_3 -pg 1 -lvl 7 -y 2060 -defaultsOSRD
preplace inst axi_gpio_7 -pg 1 -lvl 14 -y 900 -defaultsOSRD
preplace inst DFF_0 -pg 1 -lvl 6 -y 2380 -defaultsOSRD
preplace netloc axi_gpio_6_gpio_io_o 1 7 8 1580 1710 NJ 1710 NJ 1710 NJ 1710 NJ 1710 NJ 1710 NJ 1710 3950
preplace netloc axi_gpio_14_gpio_io_o 1 10 5 2410 2380 NJ 2200 NJ 2200 NJ 2190 3880
preplace netloc processing_system7_0_axi_periph_M08_AXI 1 13 1 3450
preplace netloc DFF_Integrator6Buf_0_wrcnt 1 8 7 1850 1680 NJ 1680 NJ 1680 NJ 1670 NJ 1670 NJ 1680 3880
preplace netloc c_shift_ram_0_Q 1 7 4 1460 2370 NJ 2360 NJ 2360 NJ
preplace netloc util_vector_logic_0_Res 1 4 1 N
preplace netloc processing_system7_0_FIXED_IO 1 16 1 NJ
preplace netloc processing_system7_0_axi_periph_M17_AXI 1 13 1 3430
preplace netloc axi_gpio_1_gpio_io_o 1 6 9 1250 1240 NJ 1240 NJ 1490 NJ 1490 NJ 1490 NJ 1490 NJ 1490 NJ 1240 3910
preplace netloc fit_timer_0_Interrupt 1 14 1 3970
preplace netloc xlconcat_1_dout 1 5 1 940
preplace netloc clkin_p_1 1 0 2 NJ 2470 NJ
preplace netloc MUX6_0_dout 1 11 2 2640 2000 NJ
preplace netloc AA_Integrator6Buf_0_wrcnt 1 8 7 1870 1690 NJ 1690 NJ 1690 NJ 1680 NJ 1680 NJ 1690 3870
preplace netloc xlconcat_0_dout 1 15 1 4320
preplace netloc axi_gpio_3_gpio_io_o 1 6 9 1230 1370 NJ 1360 NJ 1510 NJ 1510 NJ 1510 NJ 1510 NJ 1510 NJ 1510 3900
preplace netloc axi_gpio_18_gpio_io_o 1 1 14 140 2400 NJ 2510 NJ 2510 NJ 2510 NJ 2510 NJ 2510 NJ 2510 NJ 2520 NJ 2520 NJ 2520 NJ 2520 NJ 2520 NJ 2520 3870
preplace netloc processing_system7_0_axi_periph_M18_AXI 1 13 1 3410
preplace netloc axi_gpio_9_gpio_io_o 1 6 9 1250 2370 NJ 2400 NJ 2400 NJ 2400 NJ 2400 NJ 2400 NJ 2340 NJ 2340 3880
preplace netloc processing_system7_0_axi_periph_M16_AXI 1 13 1 3470
preplace netloc mult_gen_0_P 1 5 1 N
preplace netloc processing_system7_0_axi_periph_M06_AXI 1 13 1 3430
preplace netloc processing_system7_0_DDR 1 16 1 NJ
preplace netloc MUX6_0_logic_out 1 11 2 2620 2010 NJ
preplace netloc c_counter_binary_0_Q 1 7 1 NJ
preplace netloc axi_gpio_17_gpio_io_o 1 12 3 3050 2180 NJ 2170 3870
preplace netloc c_shift_ram_7_Q 1 7 1 1470
preplace netloc din_n_1 1 0 2 NJ 2550 NJ
preplace netloc lpf_0_dout 1 6 1 1240
preplace netloc capture_0_clkout 1 2 11 390 2490 540 2230 730 2360 930 2450 1230 1890 1490 2330 1880 2310 2150 2110 2410 2040 2660 2020 NJ
preplace netloc Trigger_0_event_done 1 6 6 1250 2130 NJ 2050 NJ 2050 NJ 2050 NJ 2050 NJ
preplace netloc axi_gpio_10_gpio_io_o 1 5 10 970 1360 NJ 1360 NJ 1350 NJ 1500 NJ 1500 NJ 1500 NJ 1500 NJ 1500 NJ 1500 3870
preplace netloc xlconstant_1_dout 1 12 1 NJ
preplace netloc processing_system7_0_axi_periph_M05_AXI 1 13 1 3410
preplace netloc axi_gpio_16_gpio_io_o 1 12 3 3040 2170 NJ 2030 3870
preplace netloc readout_0_en_a 1 7 3 1590 1670 NJ 1650 2120
preplace netloc processing_system7_0_axi_periph_M20_AXI 1 13 1 3380
preplace netloc processing_system7_0_FCLK_RESET0_N 1 11 6 2660 1740 NJ 1740 NJ 1740 NJ 1880 NJ 1880 4740
preplace netloc axi_gpio_15_gpio_io_o 1 8 7 1930 1470 NJ 1470 NJ 1470 NJ 1470 NJ 1470 NJ 1090 3890
preplace netloc Trigger_original_smaller_0_dout 1 6 4 1210 2360 NJ 2360 NJ 2300 NJ
preplace netloc c_shift_ram_4_Q 1 7 1 1520
preplace netloc processing_system7_0_axi_periph_M10_AXI 1 13 1 3440
preplace netloc processing_system7_0_axi_periph_M03_AXI 1 13 1 3380
preplace netloc processing_system7_0_axi_periph_M02_AXI 1 13 1 3370
preplace netloc AA_Integrator6Buf_0_dout 1 8 1 1860
preplace netloc readout_0_en_d 1 7 3 1590 2350 NJ 2280 2110
preplace netloc processing_system7_0_axi_periph_M07_AXI 1 13 1 3440
preplace netloc readout_0_dout 1 9 2 2140 2370 NJ
preplace netloc lpf_0_L_n1 1 4 3 750 2160 NJ 2160 1200
preplace netloc c_shift_ram_2_Q 1 10 1 2360
preplace netloc din_p_1 1 0 2 NJ 2530 NJ
preplace netloc mult_gen_1_P 1 5 1 950
preplace netloc processing_system7_0_axi_periph_M09_AXI 1 13 1 3550
preplace netloc Trigger_0_we 1 6 5 1220 2120 1500 2060 NJ 2060 NJ 2060 2360
preplace netloc capture_0_dout 1 2 2 380 2300 NJ
preplace netloc processing_system7_0_axi_periph_M11_AXI 1 13 1 3540
preplace netloc DFF_Integrator6Buf_0_dout 1 8 1 1820
preplace netloc c_shift_ram_9_Q 1 7 1 1430
preplace netloc axi_dma_0_M_AXI_S2MM 1 14 1 3980
preplace netloc processing_system7_0_axi_periph_M19_AXI 1 13 1 3370
preplace netloc c_shift_ram_10_Q 1 10 1 2350
preplace netloc one_shot_0_Q 1 3 5 550 2490 NJ 2490 NJ 2490 NJ 2490 1470
preplace netloc processing_system7_0_axi_periph_M12_AXI 1 13 1 3520
preplace netloc processing_system7_0_axi_periph_M01_AXI 1 13 1 3350
preplace netloc capture_0_load 1 2 4 360 2370 550 2370 NJ 2350 970
preplace netloc gater_0_rst 1 12 1 3000
preplace netloc readout_0_en_l 1 7 3 1560 2340 NJ 2270 2120
preplace netloc processing_system7_0_FCLK_CLK0 1 6 11 1210 1680 NJ 1680 NJ 1660 NJ 1660 NJ 1660 2620 1690 3010 1770 3460 1760 4000 1870 4310 1870 4750
preplace netloc clkin_n_1 1 0 2 NJ 2490 NJ
preplace netloc processing_system7_0_FCLK_CLK1 1 7 10 1590 2070 NJ 2260 NJ 2230 NJ 2060 NJ 2190 NJ 2190 NJ 2180 NJ 2180 NJ 2180 4760
preplace netloc memReset_0_rst 1 7 5 1440 2410 NJ 2410 NJ 2410 NJ 2410 2660
preplace netloc rst_processing_system7_0_100M_interconnect_aresetn 1 12 3 3000 1750 NJ 1750 3990
preplace netloc processing_system7_0_axi_periph_M00_AXI 1 13 1 3480
preplace netloc c_shift_ram_8_Q 1 7 1 1450
preplace netloc axi_gpio_7_gpio_io_o 1 7 8 1550 1720 NJ 1720 NJ 1720 NJ 1720 NJ 1720 NJ 1720 NJ 1720 3940
preplace netloc MUX6_0_en_integration 1 11 1 2650
preplace netloc LPF_Integrator6buf_0_dout 1 8 1 1840
preplace netloc readout_0_we 1 9 1 2110
preplace netloc one_shot_0_Qn 1 3 5 530 2500 NJ 2500 NJ 2500 NJ 2500 1510
preplace netloc axi_gpio_5_gpio_io_o 1 7 8 1570 1700 NJ 1700 NJ 1700 NJ 1700 NJ 1700 NJ 1700 NJ 1700 3960
preplace netloc AA_0_dout 1 4 3 740 2310 960 1820 NJ
preplace netloc c_shift_ram_1_Q 1 7 4 1530 2390 NJ 2390 NJ 2390 NJ
preplace netloc processing_system7_0_axi_periph_M14_AXI 1 13 1 3510
preplace netloc lpf_0_CE_O 1 4 3 750 2170 NJ 2170 1190
preplace netloc axi_gpio_4_gpio_io_o 1 7 8 1590 1730 NJ 1730 NJ 1730 NJ 1730 NJ 1730 NJ 1730 NJ 1730 3970
preplace netloc Master_Slave_Stream_v1_0_0_m00_axis 1 13 1 3350
preplace netloc TTL_In_1 1 0 8 NJ 1900 NJ 1900 390 1900 NJ 1900 NJ 1900 NJ 1900 NJ 1900 NJ
preplace netloc DFF_0_dout 1 6 1 1240
preplace netloc xlconstant_0_dout 1 1 1 NJ
preplace netloc axi_mem_intercon_M00_AXI 1 15 1 4300
preplace netloc DFF_Integrator6Buf_0_rdcnt 1 8 7 1810 2290 NJ 2240 NJ 2390 NJ 2330 NJ 2330 NJ 2330 3870
preplace netloc axi_gpio_0_gpio_io_o 1 6 9 1210 1120 NJ 1120 NJ 1480 NJ 1480 NJ 1480 NJ 1480 NJ 1480 NJ 1230 3920
preplace netloc axi_gpio_8_gpio_io_o 1 7 8 1540 1690 NJ 1670 NJ 1670 NJ 1670 NJ 1660 NJ 1660 NJ 1670 3890
preplace netloc axi_dma_0_s2mm_introut 1 14 1 N
preplace netloc processing_system7_0_axi_periph_M15_AXI 1 13 1 3450
preplace netloc processing_system7_0_axi_periph_M04_AXI 1 13 1 3400
preplace netloc rst_processing_system7_0_100M_peripheral_aresetn 1 12 3 3030 1760 3360 1770 3990
preplace netloc axi_gpio_2_gpio_io_o 1 6 9 1250 1380 NJ 1370 NJ 1520 NJ 1520 NJ 1520 NJ 1520 NJ 1520 NJ 1520 3930
preplace netloc TriggerV2_0_we 1 6 1 1190
preplace netloc c_shift_ram_6_Q 1 7 1 1480
preplace netloc S00_AXI_1 1 12 5 3050 1530 NJ 1530 NJ 1530 NJ 1530 4760
preplace netloc c_shift_ram_3_Q 1 7 4 1450 2380 NJ 2380 NJ 2380 NJ
levelinfo -pg 1 0 80 250 460 640 840 1080 1340 1700 2020 2260 2510 2840 3200 3710 4150 4530 4780 -top 0 -bot 2880
",
}

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


