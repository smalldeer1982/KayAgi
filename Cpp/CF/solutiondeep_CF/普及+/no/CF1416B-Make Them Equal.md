# 题目信息

# Make Them Equal

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers, numbered from $ 1 $ to $ n $ . You can perform the following operation no more than $ 3n $ times:

1. choose three integers $ i $ , $ j $ and $ x $ ( $ 1 \le i, j \le n $ ; $ 0 \le x \le 10^9 $ );
2. assign $ a_i := a_i - x \cdot i $ , $ a_j := a_j + x \cdot i $ .

After each operation, all elements of the array should be non-negative.

Can you find a sequence of no more than $ 3n $ operations after which all elements of the array are equal?

## 样例 #1

### 输入

```
3
4
2 16 4 18
6
1 2 3 4 5 6
5
11 19 1 1 3```

### 输出

```
2
4 1 2
2 3 3
-1
4
1 2 4
2 4 5
2 3 3
4 5 1```

# AI分析结果

### 题目内容（中文重写）
# 使它们相等

## 题目描述
给定一个由 $n$ 个正整数组成的数组 $a$，数组元素编号从 $1$ 到 $n$。你可以执行不超过 $3n$ 次以下操作：
1. 选择三个整数 $i$、$j$ 和 $x$（$1 \le i, j \le n$；$0 \le x \le 10^9$）；
2. 令 $a_i := a_i - x \cdot i$，$a_j := a_j + x \cdot i$。

每次操作后，数组的所有元素都应为非负。

你能否找到一个不超过 $3n$ 次操作的序列，使得操作后数组的所有元素都相等？

## 样例 #1

### 输入
```
3
4
2 16 4 18
6
1 2 3 4 5 6
5
11 19 1 1 3
```

### 输出
```
2
4 1 2
2 3 3
-1
4
1 2 4
2 4 5
2 3 3
4 5 1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路基本一致，都是先判断数组元素总和能否被 $n$ 整除，若不能则无解，直接输出 -1；若能，则通过一系列操作将数组元素调整为相等。操作的关键在于利用 $i = 1$ 的特殊性，先将其他元素凑成其下标的倍数，再将其转移到 $a[1]$，最后将 $a[1]$ 的值平均分配给其他元素。

### 所选题解
- **AFOier（4星）**
    - **关键亮点**：思路清晰，对操作的正确性分析详细，代码简洁易懂。
- **Imiya（4星）**
    - **关键亮点**：对操作的正确性进行了严谨的数学证明，代码结构清晰。
- **Daniel_yao（4星）**
    - **关键亮点**：思路描述详细，代码使用了结构体和向量存储操作，可读性高。

### 重点代码及核心实现思想
以 AFOier 的题解为例：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100011];
int n, sum;
void solve() {
    scanf("%d", &n); sum = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    if(sum % n) {
        printf("-1\n");
        return;
    }
    sum /= n;
    cout << 3 * (n-1) << endl;
    for(int i = 2; i <= n; i++) {
        int x = a[i] % i;
        cout << 1 << " " << i << " " << (i - x) % i << endl;
        a[1] -= (i - x) % i; a[i] += (i - x) % i;
        cout << i << " " << 1 << " " << a[i] / i << endl;
        a[1] += a[i]; a[i] = 0; 
    }
    for(int i = 2; i <= n; i++) {
        cout << 1 << " " << i << " " << sum << endl;
        a[1] -= sum; a[i] += sum;
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}
```
核心实现思想：
1. 首先读取数组元素并计算总和，判断总和能否被 $n$ 整除，若不能则输出 -1。
2. 若能整除，计算平均值。
3. 对于 $i$ 从 $2$ 到 $n$，先将 $a[i]$ 补成 $i$ 的倍数，再将 $a[i]$ 转移到 $a[1]$。
4. 最后将 $a[1]$ 的值平均分配给 $a[2]$ 到 $a[n]$。

### 最优关键思路或技巧
- 利用 $i = 1$ 的特殊性，因为 $1$ 是所有自然数的因数，可以很方便地进行元素的调整。
- 先将其他元素凑成其下标的倍数，再转移到 $a[1]$，最后平均分配，保证操作次数不超过 $3n$ 次。

### 拓展思路
同类型题或类似算法套路：在构造类问题中，通常需要观察问题的特点，找到一些特殊的元素或操作，以此为突破口进行构造。例如，在一些数组元素调整问题中，可以利用某个特殊位置的元素来实现整体的平衡。

### 洛谷题目推荐
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)

### 个人心得摘录与总结
- **Daniel_yao**：没有第一眼看出来解法，通过分析操作的性质（总和不变）和 $i = 1$ 的自由度，逐步找到了解题思路。总结：遇到问题时，先分析问题的性质，找到关键的突破口，再逐步构建解题思路。

---
处理用时：33.63秒