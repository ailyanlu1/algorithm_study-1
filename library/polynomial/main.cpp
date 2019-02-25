#include <iostream>

using namespace std;

#define TEST(ModuleName)    extern void test##ModuleName(void); \
                            test##ModuleName()

int main(void) {
    TEST(FFT);
    TEST(MultPoly);
    TEST(MultPolyMod);
    TEST(Convolution);
    TEST(NTT);
    TEST(FactorialMod);
    TEST(RootFindingLaguerre);
}
