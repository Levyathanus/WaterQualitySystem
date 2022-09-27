# Water Quality System
- Autori: Alessia Libertucci, Michele Zenoni
- Corso: "Progettazione di Sistemi Operativi" 

## Descrizione
L’obiettivo del progetto è quello di dare un’indicazione sulle principali caratteristiche che determinano la potabilità dell’acqua in modo semplice e intuitivo; questo viene fatto attraverso la realizzazione di un sistema per la misurazione della qualità dell’acqua utilizzando tre diversi tipi di sensori: sensore del pH, sensore per il residuo fisso (anche noto come misura della ”durezza” dell’acqua) e sensore della torbidità sfruttando il microcontrollore STM32L053C8T6.

## Struttura del progetto
```bash
WaterQualitySystem:.
├───.settings
├───Core
│   ├───Components
│   │   ├───Common
│   │   └───gde021a1
│   ├───Inc
│   ├───Src
│   └───Startup
├───Debug
│   ├───Core
│   │   ├───Components
│   │   │   └───gde021a1
│   │   ├───Src
│   │   └───Startup
│   └───Drivers
│       └───STM32L0xx_HAL_Driver
│           └───Src
├───Docs
├───Drivers
│   ├───CMSIS
│   │   ├───Device
│   │   │   └───ST
│   │   │       └───STM32L0xx
│   │   │           └───Include
│   │   └───Include
│   └───STM32L0xx_HAL_Driver
│       ├───Inc
│       │   └───Legacy
│       └───Src
└───Images
```
