# Water Quality System
- Autori: Alessia Libertucci, Michele Zenoni
- Corso: "Progettazione di Sistemi Operativi" 

## Descrizione
L’obiettivo del progetto è quello di dare un’indicazione sulle principali caratteristiche che determinano la potabilità dell’acqua in modo semplice e intuitivo; questo viene fatto attraverso la realizzazione di un sistema per la misurazione della qualità dell’acqua utilizzando tre diversi tipi di sensori: sensore del pH, sensore per il residuo fisso (anche noto come misura della ”durezza” dell’acqua) e sensore della torbidità sfruttando il microcontrollore STM32L053C8T6.

## Struttura del progetto
```bash
WaterQualitySystem:.
│   .cproject
│   .gitignore
│   .mxproject
│   .project
│   README.md
│   STM32L053C8TX_FLASH.ld
│   WaterQualitySystem Debug.launch
│   WaterQualitySystem.ioc
│
├───.settings
│       language.settings.xml
│       stm32cubeide.project.prefs
│
├───Core
│   ├───Components
│   │   ├───Common
│   │   │       accelero.h
│   │   │       audio.h
│   │   │       camera.h
│   │   │       epd.h
│   │   │       gyro.h
│   │   │       io.h
│   │   │       lcd.h
│   │   │       Release_Notes.html
│   │   │       ts.h
│   │   │       tsensor.h
│   │   │
│   │   └───gde021a1
│   │           gde021a1.c
│   │           gde021a1.h
│   │           Release_Notes.html
│   │
│   ├───Inc
│   │       fontsepd.h
│   │       main.h
│   │       picture.h
│   │       stm32l0538_discovery.h
│   │       stm32l0538_discovery_epd.h
│   │       stm32l0xx_hal_conf.h
│   │       stm32l0xx_it.h
│   │
│   ├───Src
│   │       font12epd.c
│   │       font16epd.c
│   │       font20epd.c
│   │       font8epd.c
│   │       main.c
│   │       stm32l0538_discovery.c
│   │       stm32l0538_discovery_epd.c
│   │       stm32l0xx_hal_msp.c
│   │       stm32l0xx_it.c
│   │       syscalls.c
│   │       sysmem.c
│   │       system_stm32l0xx.c
│   │
│   └───Startup
│           startup_stm32l053c8tx.s
│
├───Debug
│   │   makefile
│   │   objects.list
│   │   objects.mk
│   │   sources.mk
│   │   WaterQualitySystem.elf
│   │   WaterQualitySystem.list
│   │   WaterQualitySystem.map
│   │
│   ├───Core
│   │   ├───Components
│   │   │   └───gde021a1
│   │   │           gde021a1.d
│   │   │           gde021a1.o
│   │   │           gde021a1.su
│   │   │           subdir.mk
│   │   │
│   │   ├───Src
│   │   │       font12epd.d
│   │   │       font12epd.o
│   │   │       font12epd.su
│   │   │       font16epd.d
│   │   │       font16epd.o
│   │   │       font16epd.su
│   │   │       font20epd.d
│   │   │       font20epd.o
│   │   │       font20epd.su
│   │   │       font8epd.d
│   │   │       font8epd.o
│   │   │       font8epd.su
│   │   │       main.d
│   │   │       main.o
│   │   │       main.su
│   │   │       stm32l0538_discovery.d
│   │   │       stm32l0538_discovery.o
│   │   │       stm32l0538_discovery.su
│   │   │       stm32l0538_discovery_epd.d
│   │   │       stm32l0538_discovery_epd.o
│   │   │       stm32l0538_discovery_epd.su
│   │   │       stm32l0xx_hal_msp.d
│   │   │       stm32l0xx_hal_msp.o
│   │   │       stm32l0xx_hal_msp.su
│   │   │       stm32l0xx_it.d
│   │   │       stm32l0xx_it.o
│   │   │       stm32l0xx_it.su
│   │   │       subdir.mk
│   │   │       syscalls.d
│   │   │       syscalls.o
│   │   │       syscalls.su
│   │   │       sysmem.d
│   │   │       sysmem.o
│   │   │       sysmem.su
│   │   │       system_stm32l0xx.d
│   │   │       system_stm32l0xx.o
│   │   │       system_stm32l0xx.su
│   │   │
│   │   └───Startup
│   │           startup_stm32l053c8tx.d
│   │           startup_stm32l053c8tx.o
│   │           subdir.mk
│   │
│   └───Drivers
│       └───STM32L0xx_HAL_Driver
│           └───Src
│                   stm32l0xx_hal.d
│                   stm32l0xx_hal.o
│                   stm32l0xx_hal.su
│                   stm32l0xx_hal_adc.d
│                   stm32l0xx_hal_adc.o
│                   stm32l0xx_hal_adc.su
│                   stm32l0xx_hal_adc_ex.d
│                   stm32l0xx_hal_adc_ex.o
│                   stm32l0xx_hal_adc_ex.su
│                   stm32l0xx_hal_cortex.d
│                   stm32l0xx_hal_cortex.o
│                   stm32l0xx_hal_cortex.su
│                   stm32l0xx_hal_dma.d
│                   stm32l0xx_hal_dma.o
│                   stm32l0xx_hal_dma.su
│                   stm32l0xx_hal_exti.d
│                   stm32l0xx_hal_exti.o
│                   stm32l0xx_hal_exti.su
│                   stm32l0xx_hal_flash.d
│                   stm32l0xx_hal_flash.o
│                   stm32l0xx_hal_flash.su
│                   stm32l0xx_hal_flash_ex.d
│                   stm32l0xx_hal_flash_ex.o
│                   stm32l0xx_hal_flash_ex.su
│                   stm32l0xx_hal_flash_ramfunc.d
│                   stm32l0xx_hal_flash_ramfunc.o
│                   stm32l0xx_hal_flash_ramfunc.su
│                   stm32l0xx_hal_gpio.d
│                   stm32l0xx_hal_gpio.o
│                   stm32l0xx_hal_gpio.su
│                   stm32l0xx_hal_i2c.d
│                   stm32l0xx_hal_i2c.o
│                   stm32l0xx_hal_i2c.su
│                   stm32l0xx_hal_i2c_ex.d
│                   stm32l0xx_hal_i2c_ex.o
│                   stm32l0xx_hal_i2c_ex.su
│                   stm32l0xx_hal_pwr.d
│                   stm32l0xx_hal_pwr.o
│                   stm32l0xx_hal_pwr.su
│                   stm32l0xx_hal_pwr_ex.d
│                   stm32l0xx_hal_pwr_ex.o
│                   stm32l0xx_hal_pwr_ex.su
│                   stm32l0xx_hal_rcc.d
│                   stm32l0xx_hal_rcc.o
│                   stm32l0xx_hal_rcc.su
│                   stm32l0xx_hal_rcc_ex.d
│                   stm32l0xx_hal_rcc_ex.o
│                   stm32l0xx_hal_rcc_ex.su
│                   stm32l0xx_hal_spi.d
│                   stm32l0xx_hal_spi.o
│                   stm32l0xx_hal_spi.su
│                   subdir.mk
│
├───Docs
│       board-presentation.pdf
│       Carmine_Noviello_-_Mastering_STM32_v0_21.pdf
│       complete-board-manual-stm32l0x3.pdf
│       ePaper-application-stm32.pdf
│       errata-datasheet.pdf
│       PCC_Sequence.pcs
│       sequence_diagram.pdf
│       short-board-manual-stm32l053c8.pdf
│       Studio_di_fattibilita.pdf
│       um1775-discovery-kit-with-stm32l053c8-mcu-stmicroelectronics.pdf
│
├───Drivers
│   ├───CMSIS
│   │   │   LICENSE.txt
│   │   │
│   │   ├───Device
│   │   │   └───ST
│   │   │       └───STM32L0xx
│   │   │           │   License.md
│   │   │           │
│   │   │           └───Include
│   │   │                   stm32l053xx.h
│   │   │                   stm32l0xx.h
│   │   │                   system_stm32l0xx.h
│   │   │
│   │   └───Include
│   │           cmsis_armcc.h
│   │           cmsis_armclang.h
│   │           cmsis_compiler.h
│   │           cmsis_gcc.h
│   │           cmsis_iccarm.h
│   │           cmsis_version.h
│   │           core_armv8mbl.h
│   │           core_armv8mml.h
│   │           core_cm0.h
│   │           core_cm0plus.h
│   │           core_cm1.h
│   │           core_cm23.h
│   │           core_cm3.h
│   │           core_cm33.h
│   │           core_cm4.h
│   │           core_cm7.h
│   │           core_sc000.h
│   │           core_sc300.h
│   │           mpu_armv7.h
│   │           mpu_armv8.h
│   │           tz_context.h
│   │
│   └───STM32L0xx_HAL_Driver
│       │   License.md
│       │
│       ├───Inc
│       │   │   stm32l0xx_hal.h
│       │   │   stm32l0xx_hal_adc.h
│       │   │   stm32l0xx_hal_adc_ex.h
│       │   │   stm32l0xx_hal_cortex.h
│       │   │   stm32l0xx_hal_def.h
│       │   │   stm32l0xx_hal_dma.h
│       │   │   stm32l0xx_hal_exti.h
│       │   │   stm32l0xx_hal_flash.h
│       │   │   stm32l0xx_hal_flash_ex.h
│       │   │   stm32l0xx_hal_flash_ramfunc.h
│       │   │   stm32l0xx_hal_gpio.h
│       │   │   stm32l0xx_hal_gpio_ex.h
│       │   │   stm32l0xx_hal_i2c.h
│       │   │   stm32l0xx_hal_i2c_ex.h
│       │   │   stm32l0xx_hal_pwr.h
│       │   │   stm32l0xx_hal_pwr_ex.h
│       │   │   stm32l0xx_hal_rcc.h
│       │   │   stm32l0xx_hal_rcc_ex.h
│       │   │   stm32l0xx_hal_spi.h
│       │   │   stm32l0xx_ll_adc.h
│       │   │   stm32l0xx_ll_bus.h
│       │   │   stm32l0xx_ll_cortex.h
│       │   │   stm32l0xx_ll_crs.h
│       │   │   stm32l0xx_ll_dma.h
│       │   │   stm32l0xx_ll_exti.h
│       │   │   stm32l0xx_ll_gpio.h
│       │   │   stm32l0xx_ll_pwr.h
│       │   │   stm32l0xx_ll_rcc.h
│       │   │   stm32l0xx_ll_system.h
│       │   │   stm32l0xx_ll_utils.h
│       │   │
│       │   └───Legacy
│       │           stm32_hal_legacy.h
│       │
│       └───Src
│               stm32l0xx_hal.c
│               stm32l0xx_hal_adc.c
│               stm32l0xx_hal_adc_ex.c
│               stm32l0xx_hal_cortex.c
│               stm32l0xx_hal_dma.c
│               stm32l0xx_hal_exti.c
│               stm32l0xx_hal_flash.c
│               stm32l0xx_hal_flash_ex.c
│               stm32l0xx_hal_flash_ramfunc.c
│               stm32l0xx_hal_gpio.c
│               stm32l0xx_hal_i2c.c
│               stm32l0xx_hal_i2c_ex.c
│               stm32l0xx_hal_pwr.c
│               stm32l0xx_hal_pwr_ex.c
│               stm32l0xx_hal_rcc.c
│               stm32l0xx_hal_rcc_ex.c
│               stm32l0xx_hal_spi.c
│
└───Images
        Block_Diagram.drawio
        Block_Diagram.png
        compensation_voltage.png
        Demo_4pH.MOV
        Demo_4pH_no_audio.mp4
        Demo_7pH.MOV
        Demo_7pH_no_audio.mp4
        funzione_pH.png
        funzione_residuo_fisso.png
        funzione_torbidita.png
        interrupt_button_circuit.webp
        PCC_sequence.png
        Sequence_Diagram.drawio
        sequence_diagram.png
```
