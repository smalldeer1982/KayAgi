# 题目信息

# Alyona and Mex

## 题目描述

Someone gave Alyona an array containing $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ . In one operation, Alyona can choose any element of the array and decrease it, i.e. replace with any positive integer that is smaller than the current one. Alyona can repeat this operation as many times as she wants. In particular, she may not apply any operation to the array at all.

Formally, after applying some operations Alyona will get an array of $ n $ positive integers $ b_{1},b_{2},...,b_{n} $ such that $ 1<=b_{i}<=a_{i} $ for every $ 1<=i<=n $ . Your task is to determine the maximum possible value of mex of this array.

Mex of an array in this problem is the minimum positive integer that doesn't appear in this array. For example, mex of the array containing $ 1 $ , $ 3 $ and $ 4 $ is equal to $ 2 $ , while mex of the array containing $ 2 $ , $ 3 $ and $ 2 $ is equal to $ 1 $ .

## 说明/提示

In the first sample case if one will decrease the second element value to $ 2 $ and the fifth element value to $ 4 $ then the mex value of resulting array $ 1 $ $ 2 $ $ 3 $ $ 3 $ $ 4 $ will be equal to $ 5 $ .

To reach the answer to the second sample case one must not decrease any of the array elements.

## 样例 #1

### 输入

```
5
1 3 3 3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
2 1
```

### 输出

```
3
```

# AI分析结果

### 题目翻译
# Alyona和Mex

## 题目描述
有人给了阿廖娜一个包含 $n$ 个正整数 $a_{1},a_{2},\cdots,a_{n}$ 的数组。在一次操作中，阿廖娜可以选择数组中的任何一个元素并将其减小，即用任何小于当前元素的正整数替换它。阿廖娜可以根据需要多次重复此操作。特别地，她也可以完全不对数组进行任何操作。

形式上，在进行一些操作后，阿廖娜将得到一个包含 $n$ 个正整数的数组 $b_{1},b_{2},\cdots,b_{n}$，使得对于每个 $1\leq i\leq n$，都有 $1\leq b_{i}\leq a_{i}$。你的任务是确定这个数组的 mex 的最大可能值。

在这个问题中，数组的 mex 是不在该数组中出现的最小正整数。例如，包含 $1$、$3$ 和 $4$ 的数组的 mex 等于 $2$，而包含 $2$、$3$ 和 $2$ 的数组的 mex 等于 $1$。

## 说明/提示
在第一个样例中，如果将第二个元素的值减小到 $2$，将第五个元素的值减小到 $4$，那么得到的数组 $1$、$2$、$3$、$3$、$4$ 的 mex 值将等于 $5$。

为了得到第二个样例的答案，不能减小数组中的任何元素。

## 样例 #1
### 输入
```
5
1 3 3 3 6
```
### 输出
```
5
```

## 样例 #2
### 输入
```
2
2 1
```
### 输出
```
3
```

### 算法分类
贪心

### 综合分析与结论
- **思路对比**：三位作者思路一致，均是要使结果最大，就尽量凑出 $1, 2, 3, \cdots$ 这样的数列。
- **算法要点**：先对数组进行排序，然后遍历数组，当遇到大于等于当前目标值（初始为 1）的元素时，目标值加 1。
- **解决难点**：理解 mex 的定义以及如何通过操作数组得到最大的 mex 值。通过排序和贪心策略，优先使用较小的数去凑连续的正整数序列，从而解决问题。

### 题解评分
- **liuyifan**：3 星。思路有一定解释，但代码中使用万能头文件和树状数组模板等不必要内容，影响代码简洁性。
- **_YyD_**：3 星。思路有贪心证明，但代码中使用自定义循环宏，可能增加理解成本。
- **清清老大**：3 星。思路清晰，代码简洁，但缺乏必要注释。

由于所有题解均不足 4 星，以下给出通用建议与扩展思路：
- **通用建议**：在解题时，要准确理解题意，特别是像 mex 这种特殊定义。代码实现时尽量保持简洁，减少不必要的代码和注释，提高代码可读性。
- **扩展思路**：同类型题目可能会改变操作规则，例如增加操作次数限制、改变元素的操作方式等。类似算法套路还是基于贪心策略，优先满足局部最优，从而达到全局最优。

### 重点代码
```cpp
// 以清清老大的代码为例
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,ans = 1,a[121212];
    cin >> n;
    for(int i = 0;i < n;i ++)
    {
        cin >> a[i];
    }
    sort(a,a + n);
    for(int i = 0;i < n;i ++)
    {
        if(ans <= a[i])
        {
            ans ++;
        }
    }
    cout << ans;
}
```
**核心实现思想**：先读取数组元素，然后对数组进行排序，接着遍历数组，当当前元素大于等于目标值 `ans` 时，`ans` 加 1，最后输出 `ans`。

### 洛谷相似题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心策略，每次合并最小的两个果子。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：按照接水时间从小到大排序，计算总等待时间。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心选择结束时间最早的线段。

### 个人心得摘录与总结
- **liuyifan**：提到题目题意比较难读懂，理清题意后就很简单。总结：在做算法题时，准确理解题意是关键，要仔细分析题目中的各种条件和定义。 

---
处理用时：28.38秒