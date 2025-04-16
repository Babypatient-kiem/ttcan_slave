# Manikin CAN Driver

This repository provides a client and host side data-link driver for Time triggered CAN-bus.

## Functionality

This driver provides a very minimalistic barebones data-link layer implementation of Time Triggered CAN-bus. This means that this driver still has to be used with a CAN HAL/phy that allows data to be sent from and over the CAN-bus.

## Integration with your project

This project has a `config_ttcan.h` file, which has to be set-up correctly and inserted into your build.  


## Development

This project is currently developed with the IEC 62304 norm in mind, please check before submitting a pr. If the feature/bugfix you provide does meet the criteria and is within scope, you can look at the [software requirements document](docs/software_requirements.md) for that purpose.