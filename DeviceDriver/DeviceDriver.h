#pragma once
#include "FlashMemoryDevice.h"
#include <stdexcept>
class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void checkReadValue(long address, int firstread);
    void write(long address, int data);

    void writebeforecheck(long address);

protected:
    FlashMemoryDevice* m_hardware;
private:
    const int CONTINUE_READ_CNT = 4; 

};

