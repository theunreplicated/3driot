#include <gtest\gtest.h>
#include "../window2/SysUtils_Load_Library.h"
#include "FreeTypeCheck.h"
#include "PhysicsTest.h"
#include "GeometryTest.h"
//http://stackoverflow.com/questions/531941/how-to-setup-google-c-testing-framework-gtest-on-visual-studio-2005
//@TODO: gmock-brauch dann wohl gtest net mehr	
int add(int n1,int  n2){

	return n1 + n2;
}
TEST(Factorial123Test, Zero00) {
	EXPECT_EQ(1, add(1,0));
}
TEST(SysUTils_LL, Init){
	SysUtils_Load_Library*sl = new SysUtils_Load_Library("ws2_32.dll");
	EXPECT_TRUE(sl->lib);

}

int main(int argc, char** argv){
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::getchar();
}