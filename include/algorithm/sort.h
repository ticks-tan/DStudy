#pragma once
#include <vector>
#include "print_tool.h"

template <typename Tp>
void PrintArray(std::vector<Tp>& array)
{
    std::cout << "[ ";
    auto len = array.size();
    for (size_t i = 0; i < len; ++i) {
        std::cout << "{:>4} "_fmt(array[i]);
    }
    std::cout << "]\n";
}

// 选择排序
void SelectSort(std::vector<int>& vec);

// 冒泡排序
void MubbleSort(std::vector<int>& vec);

// 插入排序
void InsertSort(std::vector<int>& vec);

// 归并排序
void MergeSort(std::vector<int>& vec, size_t start, size_t end);
inline void MergeSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "MergeSort Before: ";
    PrintArray(vec);
#endif
    if (vec.size() > 1) {
        MergeSort(vec, 0, vec.size() - 1);
    }
#if __DEBUG__
    std::cout << "MergeSort After: ";
    PrintArray(vec);
#endif
}

// 桶排序（每个桶元素数量，默认最多10个）
void BucketSort(std::vector<int>& vec, size_t oneBucketCount = 10);

// 计数排序
void CountingSort(std::vector<int>& vec);

// 基数排序
void RadixSort(std::vector<int>& vec);

// 快速排序
void QuickSort(std::vector<int>& vec, size_t start, size_t end);
inline void QuickSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "QucikSort Before: ";
    PrintArray(vec);
#endif
    if (vec.size() > 1) {
        QuickSort(vec, 0, vec.size() - 1);
    }
#if __DEBUG__
    std::cout << "QucikSort After: ";
    PrintArray(vec);
#endif
}

// 希尔排序
void ShellSort(std::vector<int>& vec);

// 堆排序
void HeapSort(std::vector<int>& vec);