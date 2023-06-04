#include "algorithm/sort.h"
#include <ranges>

void SelectSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "SelectSort Before: ";
    PrintArray(vec);
#endif
    auto len = vec.size();
    for (int i = 0; i < len; ++i) {
        int min = i;
        for (int j = i + 1; j < len; ++j) {
            if (vec[j] < vec[min]) { min = j; }
        }
        std::swap(vec[i], vec[min]);
#if __DEBUG__
        std::cout << "SelectSort: ";
        PrintArray(vec);
#endif
    }
}

int arrayMinOrMax(std::vector<int>& vec, bool min)
{
    int v = vec[0];
    for (int i = 1; i < vec.size(); ++i) {
        if (min ? vec[i] < v : vec[i] > v) {
            v = vec[i];
        }
    }
    return v;
}

void MubbleSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "MubbleSort Before: ";
    PrintArray(vec);
#endif
    auto len = vec.size();
    // 添加标志进行优化
    bool flag = false;
    for (signed long i = len - 1; i > -1; --i) {
        flag = true;
        for (size_t j = 0; j < i; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                // 发生了交换
                flag = false;
            }
        }
#if __DEBUG__
        std::cout << "BubbleSort: ";
        PrintArray(vec);
#endif
        if (flag) { break; }
    }
}

void InsertSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "InsertSort Before: ";
    PrintArray(vec);
#endif
    int len = vec.size();
    for (int i = 1; i < len; ++i) {
        int v = vec[i];
        int j = i - 1;
        // 循环向前比较
        while (j >= 0) {
            if (vec[j] > v) {
                vec[j + 1] = vec[j];
                --j;
            } else {
                break;
            }
        }
        vec[j + 1] = v;
#if __DEBUG__
        std::cout << "InsertSort: ";
        PrintArray(vec);
#endif
    }
}

void MergeSort(std::vector<int>& vec, size_t start, size_t end)
{
    // 合并 [start,mid] 与 (mid, end] 两个区间序列
    auto Merge =
        [](std::vector<int>& vec, size_t start, size_t mid, size_t end) {
            std::vector<int> tmp;
            tmp.reserve(end - start + 1);
            size_t l = start;
            size_t r = mid + 1;
            while (l <= mid && r <= end) {
                if (vec[l] <= vec[r]) {
                    tmp.push_back(vec[l]);
                    l += 1;
                } else {
                    tmp.push_back(vec[r]);
                    r += 1;
                }
            }
            // 合并剩余序列
            if (l <= mid) {
                tmp.insert(tmp.end(),
                           vec.begin() + l, vec.begin() + mid + 1);
            } else {
                tmp.insert(tmp.end(),
                           vec.begin() + r, vec.begin() + end + 1);
            }
#if __DEBUG__
            std::cout << "Merge ({:>2}, {:>2}, {:>2}): "_fmt(start, mid, end);
            PrintArray(tmp);
#endif
            // 写入到原序列
            for (int i = start; i <= end; ++i) {
                vec[i] = tmp[i - start];
            }
        };
    if (start >= end) {
        return;
    }
    size_t mid = (start + end) / 2;
    // 递归左边
    MergeSort(vec, start, mid);
    // 递归右边序列
    MergeSort(vec, mid + 1, end);
    // 合并序列
    Merge(vec, start, mid, end);
}

void BucketSort(std::vector<int>& vec, size_t oneBucketCount)
{
#if __DEBUG__
    std::cout << "BucketSort Before: ";
    PrintArray(vec);
#endif
    // 获取最大最小值，方便划分桶范围
    int minVal = arrayMinOrMax(vec, true);
    int maxVal = arrayMinOrMax(vec, false);
    // 桶数量
    int bucketCount = (vec.size() / oneBucketCount) + 1;
    // 对于 [minVal, maxVal] 内元素，每个桶间元素间隔
    int perBucket = (maxVal - minVal + bucketCount) / bucketCount;
    std::vector<std::vector<int>> buckets(bucketCount);
    // 遍历序列，放入对应桶中
    for (int val : vec) {
        buckets[(val - minVal) / perBucket].push_back(val);
    }
    // 遍历每个桶，进行桶内排序(选择排序或其他排序)，再写入原序列中
    size_t index = 0;
    for (auto& bucket : buckets) {
        // 内部使用归并排序优化
        MergeSort(bucket);
#if __DEBUG__
        std::cout << "Bucket: ";
        PrintArray(bucket);
#endif
        for (int v : bucket) {
            vec[index++] = v;
        }
    }
#if __DEBUG__
    std::cout << "BucketSort After: ";
    PrintArray(vec);
#endif
}

void CountingSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "CountingSort Before: ";
    PrintArray(vec);
#endif
    int maxLen = arrayMinOrMax(vec, false) + 1;
    // 找出最大元素并构建计数表（可使用哈希表代替）
    std::vector<int> table(maxLen, 0);
    // 遍历序列计数
    for (int v : vec) {
        table[v] += 1;
    }
    // 根据计数重新赋值原序列
    size_t idx = 0;
    for (int i = 0; i < maxLen; ++i) {
        while (table[i] > 0) {
            vec[idx++] = i;
            table[i] -= 1;
        }
    }
#if __DEBUG__
    std::cout << "CountingSort After: ";
    PrintArray(vec);
#endif
}

// 只考虑了正整数情况
void RadixSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "RadixSort Before: ";
    PrintArray(vec);
#endif
    // 底数，用去取特定数位值
    long base = 1;
    // 取最大值，用于判断是否应该终止算法
    int maxVal = arrayMinOrMax(vec, false);
    while (base < maxVal) {
        // 创建十个桶
        std::vector<std::vector<int>> buckets(10);
        for (int val : vec) {
            // 插入到对应位的桶
            buckets[(val / base) % 10].push_back(val);
        }
        size_t idx = 0;
        for (auto& bucket : buckets) {
            for (int v : bucket) {
                vec[idx++] = v;
            }
        }
#if __DEBUG__
        std::cout << "RadixSort: ";
        PrintArray(vec);
#endif
        base *= 10;
    }
#if __DEBUG__
    std::cout << "RadixSort After: ";
    PrintArray(vec);
#endif
}

void QuickSort(std::vector<int>& vec, size_t start, size_t end)
{
    // 遍历给定范围序列，并区分基准值左边和右边
    auto quickBase = [](std::vector<int>& vec, size_t start, size_t end) {
        size_t base = start;  // 基准值
        size_t j = start + 1; // 记录最后的比base小或相等的元素位置
        for (size_t i = start + 1; i <= end; ++i) {
            if (vec[i] <= vec[base]) {
                // 遇到更小的，交换到前面
                std::swap(vec[j], vec[i]);
                // 此时j处元素与base处相同或者更小了，向后移动一个，方便下次交换
                j += 1;
            }
        }
        // 遍历完成，将基准值与最后出现的比基准值小或等于的元素交换
        // j - 1是因为我们进行了 j += 1操作
        std::swap(vec[base], vec[j - 1]);
        base = j - 1;
#if __DEBUG__
        std::cout << "QuickSort priv: {} : "_fmt(base);
        PrintArray(vec);
#endif
        return base;
    };
    if (start >= end) {
        return;
    }
    // 遍历后基准值位置
    size_t base = quickBase(vec, start, end);
    // 处理前半部分
    QuickSort(vec, start, base - 1);
    // 处理后半部分
    QuickSort(vec, base + 1, end);
}

void ShellSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "ShellSort Before: ";
    PrintArray(vec);
#endif
    // 计算增量，这里使用 gaps/3 计算
    size_t len = vec.size();
    long gaps = (len / 3) * 2;
    // 依次处理增量，增量为1为最后一趟
    while (gaps > 0) {
        // 对于每个增量，分别进行插入排序
        for (long i = gaps; i < len; ++i) {
            int val = vec[i];
            long j = i;
            while (j >= gaps) {
                if (vec[j - gaps] > val) {
                    vec[j] = vec[j - gaps];
                } else {
                    break;
                }
                j -= gaps;
            }
            vec[j] = val;
        }
#if __DEBUG__
        std::cout << "ShellSort gaps({}): "_fmt(gaps);
        PrintArray(vec);
#endif
        gaps /= 3;
    }
#if __DEBUG__
    std::cout << "ShellSort After: ";
    PrintArray(vec);
#endif
}

void HeapSort(std::vector<int>& vec)
{
#if __DEBUG__
    std::cout << "HeapSort Before: ";
    PrintArray(vec);
#endif
    // 堆顶元素不断下沉
    auto MaxHeapTopDown =
        [](std::vector<int>& heap, size_t root, size_t end) {
            // 计算左子节点
            size_t child = (root + 1) * 2 - 1;
            // 将堆顶元素不断下沉到合适位置
            while (child <= end) {
                // 右子节点比左子节点大
                if (child + 1 <= end && heap[child + 1] > heap[child]) {
                    child += 1;
                }
                // 子节点比父节点大
                if (heap[child] > heap[root]) {
                    std::swap(heap[child], heap[root]);
                    root = child;
                    child = (child + 1) * 2 - 1;
                } else {
                    break;
                }
            }
        };
    size_t root = 0, len = vec.size();
    // 构建大顶堆
    for (long i = (len - 1) / 2; i >= 0; --i) {
        MaxHeapTopDown(vec, i, len - 1);
    }
#if __DEBUG__
    std::cout << "MaxHeap: ";
    PrintArray(vec);
#endif
    // 不断交换堆顶与最后元素
    for (long i = len - 1; i > root; --i) {
        std::swap(vec[i], vec[root]);
        // 维护好剩余序列组成的大顶堆
        MaxHeapTopDown(vec, root, i - 1);
#if __DEBUG__
        std::cout << "HeapSort [{}-{}]: "_fmt(root, i - 1);
        PrintArray(vec);
#endif
    }
#if __DEBUG__
    std::cout << "HeapSort After: ";
    PrintArray(vec);
#endif
}