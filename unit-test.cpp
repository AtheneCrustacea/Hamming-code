#include <unittest++/UnitTest++.h>
#include <coder.h>
SUITE (PolynomalTest){
    TEST(InvalidPolynomal){
        CHECK_THROW(coder cp(7,5), std::string);
    }
    TEST(ValidPolynomal_7_4){
        CHECK_EQUAL(0x7F,coder(7,4).encode(0xF));
    }
    TEST(ValidPolynomal_15_11){
        CHECK_EQUAL(0x7FFF,coder(15,11).encode(0x7FF));
    }
    TEST(ValidPolynomal_31_26){
        CHECK_EQUAL(0x7FFFFFFF,coder(31,26).encode(0x3FFFFFF));
    }
}
SUITE(encodeTest){
    TEST(InvalidNumber){
        CHECK_THROW(coder(7,4).encode(0xFF), std::string);
    }
    TEST(encodePolynomal_7_4){
        CHECK_EQUAL(0x7F,coder(7,4).encode(0xF));
    }
    TEST(encodePolynomal_15_11){
        CHECK_EQUAL(0x7FFF,coder(15,11).encode(0x7FF));
    }
    TEST(encodePolynomal_31_26){
        CHECK_EQUAL(0x7FFFFFFF,coder(31,26).encode(0x3FFFFFF));
    }
}
SUITE(decodeTest){
    TEST(InvalidNumber){
        CHECK_THROW(coder(7,4).decode(0xFF), std::string);
    }
    TEST(decodePolynomal_7_4){
        CHECK_EQUAL(0xF,coder(7,4).decode(0x7F));
    }
    TEST(decodePolynomal_15_11){
        CHECK_EQUAL(0x7FF,coder(15,11).decode(0x7FFF));
    }
    TEST(decodePolynomal_31_26){
        CHECK_EQUAL(0x3FFFFFF,coder(31,26).decode(0x7FFFFFFF));
    }
}
int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}
