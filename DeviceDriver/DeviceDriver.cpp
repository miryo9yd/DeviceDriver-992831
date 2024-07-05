#include "DeviceDriver.h"
#include<vector>
#include <stdexcept>
using namespace std; 


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)  // App이 사용 하는 함수 -> H/W에 연결되서 read 호출 
{
    int firstread  = (int)(m_hardware->read(address));
    
    checkReadValue(address, firstread);

    return firstread;
}

void DeviceDriver::checkReadValue(long address, int firstread)
{
    for (int i = 0; i < CONTINUE_READ_CNT ; i++) {
        int checkvalue = (int)(m_hardware->read(address));
        if (firstread != checkvalue) throw std::exception();
    }
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    writebeforecheck(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::writebeforecheck(long address)
{
    int checkvalue = (int)(m_hardware->read(address));
    if (checkvalue != 0xff) throw std::exception();
}
