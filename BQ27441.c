//*******************************************************************//
// File: BQ27441.c                                                   //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: Interfacing with Battery Fuel Gauge                  //
//                                                                   //
//*******************************************************************//


#include "BQ27441.h"

// Configures the design capacity of the connected battery.

void BQ27441_setCapacity(uint16_t capacity) {
    // Write to STATE subclass (82) of BQ27441 extended memory.
    // Offset 0x0A (10)
    // Design capacity is a 2-byte piece of data - MSB first
    uint8_t capMSB = capacity >> 8;
    uint8_t capLSB = capacity & 0x00FF;
    uint8_t capacityData[2] = {capMSB, capLSB};
    BQ27441_writeExtendedData(BQ27441_ID_STATE, 10, capacityData, 2);
}

/*****************************************************************************
 ********************** Battery Characteristics Functions ********************
 *****************************************************************************/

// Reads and returns the battery voltage

uint16_t BQ27441_voltage(void) {
    return BQ27441_readWord(BQ27441_COMMAND_VOLTAGE);
}

// Reads and returns the specified current measurement

int16_t BQ27441_current(char current_measure_type) {
    int16_t current = 0;
    switch (current_measure_type) {
        case 1: //AVG
            current = (int16_t) BQ27441_readWord(BQ27441_COMMAND_AVG_CURRENT);
            break;
        case 2: //STBY
            current = (int16_t) BQ27441_readWord(BQ27441_COMMAND_STDBY_CURRENT);
            break;
        case 3: //MAX
            current = (int16_t) BQ27441_readWord(BQ27441_COMMAND_MAX_CURRENT);
            break;
    }

    return current;
}

// Reads and returns the specified capacity measurement

uint16_t BQ27441_capacity(char capacity_measure_type) {
    uint16_t capacity = 0;
    switch (capacity_measure_type) {
        case 1://REMAIN
            return BQ27441_readWord(BQ27441_COMMAND_REM_CAPACITY);
            break;
        case 2://FULL:
            return BQ27441_readWord(BQ27441_COMMAND_FULL_CAPACITY);
            break;
        case 3://AVAIL:
            capacity = BQ27441_readWord(BQ27441_COMMAND_NOM_CAPACITY);
            break;
        case 4://AVAIL_FULL:
            capacity = BQ27441_readWord(BQ27441_COMMAND_AVAIL_CAPACITY);
            break;
        case 5://REMAIN_F:
            capacity = BQ27441_readWord(BQ27441_COMMAND_REM_CAP_FIL);
            break;
        case 6://REMAIN_UF:
            capacity = BQ27441_readWord(BQ27441_COMMAND_REM_CAP_UNFL);
            break;
        case 7://FULL_F:
            capacity = BQ27441_readWord(BQ27441_COMMAND_FULL_CAP_FIL);
            break;
        case 8://FULL_UF:
            capacity = BQ27441_readWord(BQ27441_COMMAND_FULL_CAP_UNFL);
            break;
        case 9://DESIGN:
            capacity = BQ27441_readWord(BQ27441_EXTENDED_CAPACITY);
    }

    return capacity;
}

// Reads and returns measured average power

int16_t BQ27441_power(void) {
    return (int16_t) BQ27441_readWord(BQ27441_COMMAND_AVG_POWER);
}

// Reads and returns specified state of charge measurement

uint16_t BQ27441_soc(char soc_measure_type) {
    uint16_t socRet = 0;
    switch (soc_measure_type) {
        case 1://FILTERED:
            socRet = BQ27441_readWord(BQ27441_COMMAND_SOC);
            break;
        case 2://UNFILTERED:
            socRet = BQ27441_readWord(BQ27441_COMMAND_SOC_UNFL);
            break;
    }

    return socRet;
}

// Reads and returns specified state of health measurement

uint8_t BQ27441_soh(char soh_measure_type) {
    uint16_t sohRaw = BQ27441_readWord(BQ27441_COMMAND_SOH);
    uint8_t sohStatus = sohRaw >> 8;
    uint8_t sohPercent = sohRaw & 0x00FF;

    if (soh_measure_type == 1)
        return sohPercent;
    else
        return sohStatus;
}

// Reads and returns specified temperature measurement

uint16_t BQ27441_temperature(char temp_measure_type) {
    uint16_t temp = 0;
    switch (temp_measure_type) {
        case 1://BATTERY:
            temp = BQ27441_readWord(BQ27441_COMMAND_TEMP);
            break;
        case 2://INTERNAL_TEMP:
            temp = BQ27441_readWord(BQ27441_COMMAND_INT_TEMP);
            break;
    }
    return temp;
}

/*****************************************************************************
 *************************** Control Sub-Commands ****************************
 *****************************************************************************/

// Read the device type - should be 0x0421

uint16_t BQ27441_deviceType(void) {
    return BQ27441_readControlWord(BQ27441_CONTROL_DEVICE_TYPE);
}

// Enter configuration mode - set userControl if calling from an Arduino sketch
// and you want control over when to exitConfig

void BQ27441_enterConfig(uint8_t userControl) {
    if (userControl) 
        _userConfigControl = 1;
    
    if (BQ27441_sealed()) {
        _sealFlag = 1;
        BQ27441_unseal(); // Must be unsealed before making changes
    }
    BQ27441_executeControlWord(BQ27441_CONTROL_SET_CFGUPDATE);

}

// Exit configuration mode with the option to perform a resimulation

void BQ27441_exitConfig(uint8_t resim) {
    // There are two methods for exiting config mode:
    //    1. Execute the EXIT_CFGUPDATE command
    //    2. Execute the SOFT_RESET command
    // EXIT_CFGUPDATE exits config mode _without_ an OCV (open-circuit voltage)
    // measurement, and without resimulating to update unfiltered-SoC and SoC.
    // If a new OCV measurement or resimulation is desired, SOFT_RESET or
    // EXIT_RESIM should be used to exit config mode.
    if (resim) 
        BQ27441_softReset();
    else
        BQ27441_executeControlWord(BQ27441_CONTROL_EXIT_CFGUPDATE);
    
}

// Read the flags() command

uint16_t BQ27441_flags(void) {
    return BQ27441_readWord(BQ27441_COMMAND_FLAGS);
}

// Read the CONTROL_STATUS subcommand of control()

uint16_t BQ27441_status(void) {
    return BQ27441_readControlWord(BQ27441_CONTROL_STATUS);
}

/***************************** Private Functions *****************************/

// Check if the BQ27441-G1A is sealed or not.

uint16_t BQ27441_sealed(void) {
    uint16_t stat = BQ27441_status();
    return stat & BQ27441_STATUS_SS;
}

// Seal the BQ27441-G1A

void BQ27441_seal(void) {
     BQ27441_readControlWord(BQ27441_CONTROL_SEALED);
}

// UNseal the BQ27441-G1A

uint8_t BQ27441_unseal(void) {
    // To unseal the BQ27441, write the key to the control
    // command. Then immediately write the same key to control again.
    if (BQ27441_readControlWord(BQ27441_UNSEAL_KEY)) {
        return BQ27441_readControlWord(BQ27441_UNSEAL_KEY);
    }
    return 0;
}

// Read the 16-bit opConfig register from extended data

uint16_t BQ27441_opConfig(void) {
    return BQ27441_readWord(BQ27441_EXTENDED_OPCONFIG);
}

// Write the 16-bit opConfig register in extended data

void BQ27441BQ27441_writeOpConfig(uint16_t value) {
    uint8_t opConfigMSB = value >> 8;
    uint8_t opConfigLSB = value & 0x00FF;
    uint8_t opConfigData[2] = {opConfigMSB, opConfigLSB};

    // OpConfig register location: BQ27441_ID_REGISTERS id, offset 0
    BQ27441_writeExtendedData(BQ27441_ID_REGISTERS, 0, opConfigData, 2);
}

// Issue a soft-reset to the BQ27441-G1A

void BQ27441_softReset(void) {
     BQ27441_executeControlWord(BQ27441_CONTROL_SOFT_RESET);
}

// Read a 16-bit command word from the BQ27441-G1A

uint16_t BQ27441_readWord(uint16_t subAddress) {
    uint8_t data[2];
    BQ27441_i2cReadBytes(subAddress, data, 2);
    return ((uint16_t) data[1] << 8) | data[0];
}

// Read a 16-bit subcommand() from the BQ27441-G1A's control()

uint16_t BQ27441_readControlWord(uint16_t function) {
    uint8_t subCommandMSB = (function >> 8);
    uint8_t subCommandLSB = (function & 0x00FF);
    uint8_t command[2] = {subCommandLSB, subCommandMSB};
    uint8_t data[2] = {0, 0};

    BQ27441_i2cWriteBytes((uint8_t) 0, command, 2);

    BQ27441_i2cReadBytes((uint8_t) 0, data, 2); 
    
    return ((uint16_t) data[1] << 8) | data[0];

}

// Execute a subcommand() from the BQ27441-G1A's control()

void BQ27441_executeControlWord(uint16_t function) {
    uint8_t subCommandMSB = (function >> 8);
    uint8_t subCommandLSB = (function & 0x00FF);
    uint8_t command[2] = {subCommandLSB, subCommandMSB};
    uint8_t data[2] = {0, 0};

    BQ27441_i2cWriteBytes((uint8_t) 0, command, 2);
    

    
}

/*****************************************************************************
 ************************** Extended Data Commands ***************************
 *****************************************************************************/

// Issue a BlockDataControl() command to enable BlockData access

uint8_t BQ27441_blockDataControl(void) {
    uint8_t enableByte = 0x00;
    BQ27441_i2cWriteBytes(BQ27441_EXTENDED_CONTROL, &enableByte, 1);
    return 1;
}

// Issue a DataClass() command to set the data class to be accessed

uint8_t BQ27441_blockDataClass(uint8_t id) {
     BQ27441_i2cWriteBytes(BQ27441_EXTENDED_DATACLASS, &id, 1);
     return 1;
}

// Issue a DataBlock() command to set the data block to be accessed

void BQ27441_blockDataOffset(uint8_t offset) {
    BQ27441_i2cWriteBytes(BQ27441_EXTENDED_DATABLOCK, &offset, 1);
}

// Read the current checksum using BlockDataCheckSum()

uint8_t BQ27441_blockDataChecksum(void) {
    uint8_t csum;
    BQ27441_i2cReadBytes(BQ27441_EXTENDED_CHECKSUM, &csum, 1);
    return csum;
}

// Use BlockData() to read a byte from the loaded extended data

uint8_t BQ27441_readBlockData(uint8_t offset) {
    uint8_t ret;
    uint8_t address = offset + BQ27441_EXTENDED_BLOCKDATA;
    BQ27441_i2cReadBytes(address, &ret, 1);
    return ret;
}

// Use BlockData() to write a byte to an offset of the loaded data

void BQ27441_writeBlockData(uint8_t offset, uint8_t data) {
    uint8_t address = offset + BQ27441_EXTENDED_BLOCKDATA;
    BQ27441_i2cWriteBytes(address, &data, 1);
}

// Read all 32 bytes of the loaded extended data and compute a 
// checksum based on the values.

uint8_t BQ27441_computeBlockChecksum(void) {
    uint8_t data[32],i;
    BQ27441_i2cReadBytes(BQ27441_EXTENDED_BLOCKDATA, data, 32);

    uint8_t csum = 0;
    for ( i = 0; i < 32; i++) {
        csum += data[i];
    }
    csum = 255 - csum;

    return csum;
}

// Use the BlockDataCheckSum() command to write a checksum value

void BQ27441_writeBlockChecksum(uint8_t csum) {
    BQ27441_i2cWriteBytes(BQ27441_EXTENDED_CHECKSUM, &csum, 1);
}

// Read a byte from extended data specifying a class ID and position offset

uint8_t BQ27441_readExtendedData(uint8_t classID, uint8_t offset) {
    uint8_t retData = 0;
    if (!_userConfigControl) 
        BQ27441_enterConfig(0);

    if (!BQ27441_blockDataControl()) // // enable block data memory control
        return 0; // Return false if enable fails
    if (!BQ27441_blockDataClass(classID)) // Write class ID using DataBlockClass()
        return 0;

    BQ27441_blockDataOffset(offset / 32); // Write 32-bit block offset (usually 0)

    BQ27441_computeBlockChecksum(); // Compute checksum going in
    uint8_t oldCsum = BQ27441_blockDataChecksum();
    retData = BQ27441_readBlockData(offset % 32); // Read from offset (limit to 0-31)

    if (!_userConfigControl) 
        BQ27441_exitConfig(1);

    return retData;
}

// Write a specified number of bytes to extended data specifying a 
// class ID, position offset.

uint8_t BQ27441_writeExtendedData(uint8_t classID, uint8_t offset, uint8_t * data, uint8_t len) {
    if (len > 32)
        return 0;

    if (!_userConfigControl) 
        BQ27441_enterConfig(0);

    if (!BQ27441_blockDataControl()) // // enable block data memory control
        return 0; // Return false if enable fails
    if (!BQ27441_blockDataClass(classID)) // Write class ID using DataBlockClass()
        return 0;

    BQ27441_blockDataOffset(offset / 32); // Write 32-bit block offset (usually 0)
    BQ27441_computeBlockChecksum(); // Compute checksum going in
    uint8_t oldCsum = BQ27441_blockDataChecksum();

    // Write data bytes:
    uint8_t i;
    for (i = 0; i < len; i++) {
        // Write to offset, mod 32 if offset is greater than 32
        // The blockDataOffset above sets the 32-bit block
        BQ27441_writeBlockData((offset % 32) + i, data[i]);
    }

    // Write new checksum using BlockDataChecksum (0x60)
    uint8_t newCsum = BQ27441_computeBlockChecksum(); // Compute the new checksum
    BQ27441_writeBlockChecksum(newCsum);

    if (!_userConfigControl) 
        BQ27441_exitConfig(1);

    return 1;
}

/*****************************************************************************
 ************************ I2C Read and Write Routines ************************
 *****************************************************************************/

// Read a specified number of bytes over I2C at a given subAddress
void BQ27441_i2cReadBytes(uint8_t subAddress, uint8_t * dest, uint8_t count) {
    
    uint8_t i;
    I2C_1_Repeated_Read(_deviceAddress, subAddress, count);

    for(i = 0; i < count; i++) 
        dest[i] = Recieve_Buffer[i];
    
    
}

// Write a specified number of bytes over I2C to a given subAddress
void BQ27441_i2cWriteBytes(uint8_t subAddress, uint8_t * src, uint8_t count) {
    
     I2C_1_Repeated_Write(_deviceAddress, subAddress, src, count);
 }
    //*END FILE**********************************************************//