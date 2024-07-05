
#include "gtest/gtest.h"  
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include<stdexcept>
#include<iostream>

using  namespace testing; 
using namespace std; 

class FlashMock :public FlashMemoryDevice {  
public:
	MOCK_METHOD(unsigned char, read, (long address) , (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};



TEST(TestCaseName, ReadFiveTimes) {	

	FlashMock mk;
	DeviceDriver devdrive(&mk);

	EXPECT_CALL(mk, read(0x55)).Times(5).WillRepeatedly(Return(0xff));
	
	devdrive.read(0x55);

}



TEST(TestCaseName, ReadWrongValueException) {

	FlashMock mk;
	DeviceDriver devdrive(&mk);
	EXPECT_CALL(mk, read(0x55))
		.Times(5)
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xDD));  


	EXPECT_THROW({ devdrive.read(0x55); }, std::exception);


}



TEST(TestCaseName, WriteBeforReadTest) {

	NiceMock<FlashMock> mk;
	DeviceDriver devdrive(&mk);
	EXPECT_CALL(mk, read )
		.Times(1)
		.WillRepeatedly(Return(0xff));

	devdrive.write(0xDD, 0x72);


}

TEST(TestCaseName, WriteExceptionTest) {

	NiceMock<FlashMock> mk;
	DeviceDriver devdrive(&mk);
	EXPECT_CALL(mk, read)
		.Times(1)
		.WillOnce(Return(0xDD));


	EXPECT_THROW({ devdrive.write(0xDD, 0x72); }, std::exception);


}