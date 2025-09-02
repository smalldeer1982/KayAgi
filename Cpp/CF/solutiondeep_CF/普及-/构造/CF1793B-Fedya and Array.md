# 题目信息

# Fedya and Array

## 题目描述

For his birthday recently Fedya was given an array $ a $ of $ n $ integers arranged in a circle, For each pair of neighboring numbers ( $ a_1 $ and $ a_2 $ , $ a_2 $ and $ a_3 $ , $ \ldots $ , $ a_{n - 1} $ and $ a_n $ , $ a_n $ and $ a_1 $ ) the absolute difference between them is equal to $ 1 $ .

Let's call a local maximum an element, which is greater than both of its neighboring elements. Also call a local minimum an element, which is less than both of its neighboring elements. Note, that elements $ a_1 $ and $ a_n $ are neighboring elements.

Unfortunately, Fedya lost an array, but he remembered in it the sum of local maximums $ x $ and the sum of local minimums $ y $ .

Given $ x $ and $ y $ , help Fedya find any matching array of minimum length.

## 说明/提示

In the first test case, the local maximums are the numbers at $ 3, 7 $ and $ 10 $ positions, and the local minimums are the numbers at $ 1, 6 $ and $ 8 $ positions. $ x = a_3 + a_7 + a_{10} = 2 + 0 + 1 = 3 $ , $ y = a_1 + a_6 + a_8 = 0 + (-1) + (-1) = -2 $ .

In the second test case, the local maximums are the numbers at $ 2 $ and $ 10 $ positions, and the local minimums are the numbers at $ 1 $ and $ 3 $ positions. $ x = a_2 + a_{10} = -1 + 5 = 4 $ , $ y = a_1 + a_3 = -2 + (-2) = -4 $ .

In the third test case, the local maximums are the numbers at $ 1 $ and $ 5 $ positions, and the local minimums are the numbers at $ 3 $ and $ 6 $ positions.

## 样例 #1

### 输入

```
4
3 -2
4 -4
2 -1
5 -3```

### 输出

```
10
0 1 2 1 0 -1 0 -1 0 1
16
-2 -1 -2 -1 0 1 2 3 4 5 4 3 2 1 0 -1 
6
1 0 -1 0 1 0
16
2 3 2 1 0 -1 0 -1 0 -1 0 1 2 1 0 1```

# AI分析结果

### 题目内容中文重写
# Fedya和数组

## 题目描述
最近，在Fedya生日时，他收到了一个由 $n$ 个整数组成的环形数组 $a$。对于每一对相邻的数（$a_1$ 和 $a_2$，$a_2$ 和 $a_3$，$\ldots$，$a_{n - 1}$ 和 $a_n$，$a_n$ 和 $a_1$），它们之间的绝对差值都等于 $1$。

我们把一个比它相邻的两个元素都大的元素称为局部最大值，把一个比它相邻的两个元素都小的元素称为局部最小值。注意，元素 $a_1$ 和 $a_n$ 是相邻元素。

不幸的是，Fedya 把数组弄丢了，但他记得数组中局部最大值的和为 $x$，局部最小值的和为 $y$。

给定 $x$ 和 $y$，请帮助 Fedya 找到满足条件的最小长度的数组。

## 说明/提示
在第一个测试用例中，局部最大值位于第 $3$、$7$ 和 $10$ 个位置，局部最小值位于第 $1$、$6$ 和 $8$ 个位置。$x = a_3 + a_7 + a_{10} = 2 + 0 + 1 = 3$，$y = a_1 + a_6 + a_8 = 0 + (-1) + (-1) = -2$。

在第二个测试用例中，局部最大值位于第 $2$ 和 $10$ 个位置，局部最小值位于第 $1$ 和 $3$ 个位置。$x = a_2 + a_{10} = -1 + 5 = 4$，$y = a_1 + a_3 = -2 + (-2) = -4$。

在第三个测试用例中，局部最大值位于第 $1$ 和 $5$ 个位置，局部最小值位于第 $3$ 和 $6$ 个位置。

## 样例 #1
### 输入
```
4
3 -2
4 -4
2 -1
5 -3
```
### 输出
```
10
0 1 2 1 0 -1 0 -1 0 1
16
-2 -1 -2 -1 0 1 2 3 4 5 4 3 2 1 0 -1 
6
1 0 -1 0 1 0
16
2 3 2 1 0 -1 0 -1 0 -1 0 1 2 1 0 1
```

### 综合分析与结论
这些题解的核心思路一致，都是先分析出局部最大值和局部最小值交替出现，且得出序列长度为 $2(x - y)$，然后采用简单的构造方式来生成满足条件的数组。
- **思路**：各题解都通过分析局部最大值和局部最小值的关系，推导出序列长度公式。部分题解通过图像化、数学推导等方式进行证明。
- **算法要点**：计算出序列长度 $2(x - y)$，构造数组时从 $x$ 递减到 $y$，再从 $y + 1$ 递增到 $x - 1$。
- **解决难点**：关键在于证明局部最大值和局部最小值交替出现，并推导出序列长度公式。部分题解通过图像化或逻辑推理解决了这一难点。

### 题解评分与选择
- **Nuyoah_awa**：5星。思路清晰，通过图形示例直观展示构造情况，代码简洁易懂。
- **寻逍遥2006**：4星。详细证明了局部最大值和局部最小值交替出现，逻辑严谨，但代码中使用自定义输入函数增加了复杂度。
- **_djc_**：4星。思路简洁明了，直接给出结论并进行构造，但代码中使用自定义输入函数。

### 最优关键思路或技巧
- **思维方式**：通过分析局部最大值和局部最小值的关系，将复杂的环形数组问题简化为简单的数学推导和构造问题。
- **代码实现技巧**：采用简单的循环从 $x$ 递减到 $y$，再从 $y + 1$ 递增到 $x - 1$ 来构造数组。

### 拓展思路
同类型题目可能会改变相邻元素的差值条件，或者增加其他限制，如数组元素的取值范围等。解题时仍可从分析局部最大值和局部最小值的关系入手，推导序列长度公式，再进行构造。

### 洛谷相似题目推荐
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)

### 个人心得摘录与总结
- **loser_seele**：提到赛时没做出来，指出题目未给出 $x - y$ 的范围，只有 $x - y \leq 10^5$ 时才满足条件限制。总结为在解题时要注意题目条件的完整性和边界情况。

### 重点代码
```cpp
// Nuyoah_awa的核心代码
#include <iostream>
#include <cstdio>
using namespace std;
long long x, y, T;
int main()
{
    cin >> T;
    while(T--)
    {
        cin >> x >> y;
        cout << (x - y) * 2 << endl;
        for(int i = 0;i < x - y;i++)
            cout << x - i << " ";
        for(int i = 0;i < x - y;i++)
            cout << y + i << " ";
        cout << endl;
    }
    return 0;
}
```
核心实现思想：先计算出序列长度 $(x - y) * 2$ 并输出，然后通过两个循环分别从 $x$ 递减到 $y$，再从 $y$ 递增到 $x - 1$ 输出数组元素。

---
处理用时：28.96秒