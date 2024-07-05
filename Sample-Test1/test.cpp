
#include "gtest/gtest.h"  // 비공식
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp" // 자체파일 순으로 
#include<stdexcept>
#include<iostream>
// TEST - Read 5 times & check value 
// Return read 시 값이 나온다 // 나오지
//
//1 Mock 생성
using  namespace testing; 
using namespace std; 

class FlashMock :public FlashMemoryDevice {  // 인터페이스를 상속 받는구나 ?
public:
	MOCK_METHOD(unsigned char, read, (long address) , (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};



TEST(TestCaseName, ReadFiveTimes) {	// stub  5회 read 호출시 pass

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