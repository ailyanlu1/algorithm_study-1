#include <iostream>

using namespace std;

#define TEST(ModuleName)    extern void test##ModuleName(void); \
                            test##ModuleName()

int main(void) {
    TEST(CycleDetection);
    TEST(MergeableHeap);
    TEST(LargestRectangle);
    TEST(JumpPointerSparseTable);
    TEST(CountUniqueNumbers);
    TEST(MinStack);
    TEST(MinQueue);
    TEST(ReservoirSampling);
    TEST(ParallelBinarySearch);
    TEST(ParallelBinarySearchRecursive);
    TEST(SegmentMinValueFinder);
    TEST(CoverTime);
}
