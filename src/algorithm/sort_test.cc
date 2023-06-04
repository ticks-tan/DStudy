#include "algorithm/sort.h"
#include <random>
#include <functional>

std::vector<int> g_array;

void RandomArray(size_t len, int min, int max)
{
    std::random_device rd{};
    std::mt19937_64 gen{rd()};
    std::uniform_int_distribution<int> ud{min, max};
    g_array.resize(len);
    for (int i = 0; i < len; ++i) {
        g_array[i] = ud(gen);
    }
}

void TestSelectSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test SelectSort");
    RandomArray(15, -100, 100);

    SelectSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestMubbleSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test MubbleSort");
    RandomArray(15, -10, 100);

    MubbleSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestInsertSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test InsertSort");
    RandomArray(15, -10, 100);

    InsertSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}
void TestMergeSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test MergeSort");
    RandomArray(15, -10, 100);

    MergeSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestBucketSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test BucketSort");
    RandomArray(15, -25, 100);

    BucketSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestCountingSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test CountingSort");
    RandomArray(15, 5, 100);

    CountingSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestRadixSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test RadixSort");
    RandomArray(15, 5, 100);

    RadixSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestQuickSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test QuickSort");
    RandomArray(15, -25, 100);

    QuickSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestShellSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test ShellSort");
    RandomArray(15, -25, 100);

    ShellSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

void TestHeapSort()
{
    std::cout << "{:-^100s}\n"_fmt("Test HeapSort");
    RandomArray(15, -25, 100);

    HeapSort(g_array);

    std::cout << "{:-^100c}\n"_fmt('-');
}

// struct Foo
// {
//     int data{10};
// };

int main()
{
    // TestSelectSort();
    // TestMubbleSort();
    // TestInsertSort();
    // TestMergeSort();
    // TestBucketSort();
    // TestCountingSort();
    // TestRadixSort();
    // TestQuickSort();
    // TestShellSort();
    TestHeapSort();

    // Foo f;
    // auto fun = std::bind(&Foo::data, std::placeholders::_1);
    // std::cout << "bind: " << fun(f) << "\n";
    // std::cout << "&Foo::*: " << f.*(&Foo::data) << "\n";
    // std::cout << "invoke: " << std::invoke(&Foo::data, f) << "\n";

    return 0;
}