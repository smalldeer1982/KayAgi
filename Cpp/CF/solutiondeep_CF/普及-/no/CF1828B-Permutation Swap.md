# 题目信息

# Permutation Swap

## 题目描述

You are given an unsorted permutation $ p_1, p_2, \ldots, p_n $ . To sort the permutation, you choose a constant $ k $ ( $ k \ge 1 $ ) and do some operations on the permutation. In one operation, you can choose two integers $ i $ , $ j $ ( $ 1 \le j < i \le n $ ) such that $ i - j = k $ , then swap $ p_i $ and $ p_j $ .

What is the maximum value of $ k $ that you can choose to sort the given permutation?

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2, 3, 1, 5, 4] $ is a permutation, but $ [1, 2, 2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1, 3, 4] $ is also not a permutation ( $ n = 3 $ but there is $ 4 $ in the array).

An unsorted permutation $ p $ is a permutation such that there is at least one position $ i $ that satisfies $ p_i \ne i $ .

## 说明/提示

In the first test case, the maximum value of $ k $ you can choose is $ 1 $ . The operations used to sort the permutation are:

- Swap $ p_2 $ and $ p_1 $ ( $ 2 - 1 = 1 $ ) $ \rightarrow $ $ p = [1, 3, 2] $
- Swap $ p_2 $ and $ p_3 $ ( $ 3 - 2 = 1 $ ) $ \rightarrow $ $ p = [1, 2, 3] $

In the second test case, the maximum value of $ k $ you can choose is $ 2 $ . The operations used to sort the permutation are:

- Swap $ p_3 $ and $ p_1 $ ( $ 3 - 1 = 2 $ ) $ \rightarrow $ $ p = [1, 4, 3, 2] $
- Swap $ p_4 $ and $ p_2 $ ( $ 4 - 2 = 2 $ ) $ \rightarrow $ $ p = [1, 2, 3, 4] $

## 样例 #1

### 输入

```
7
3
3 1 2
4
3 4 1 2
7
4 2 6 7 5 3 1
9
1 6 7 4 9 2 3 8 5
6
1 5 3 4 2 6
10
3 10 5 2 9 6 7 8 1 4
11
1 11 6 4 8 3 7 5 9 10 2```

### 输出

```
1
2
3
4
3
2
3```

# AI分析结果

### 题目翻译
## 排列交换

### 题目描述
给定一个未排序的排列 $ p_1, p_2, \ldots, p_n $。为了对这个排列进行排序，你需要选择一个常数 $ k $（$ k \ge 1 $），并对该排列进行一些操作。在一次操作中，你可以选择两个整数 $ i $、$ j $（$ 1 \le j < i \le n $），使得 $ i - j = k $，然后交换 $ p_i $ 和 $ p_j $。

你能选择的 $ k $ 的最大值是多少，才能将给定的排列排序？

排列是一个由 $ n $ 个不同的整数组成的数组，这些整数的范围是从 $ 1 $ 到 $ n $，顺序任意。例如，$ [2, 3, 1, 5, 4] $ 是一个排列，但 $ [1, 2, 2] $ 不是排列（数字 $ 2 $ 在数组中出现了两次），$ [1, 3, 4] $ 也不是排列（$ n = 3 $，但数组中出现了 $ 4 $）。

未排序的排列 $ p $ 是指至少存在一个位置 $ i $，满足 $ p_i \ne i $ 的排列。

### 说明/提示
在第一个测试用例中，你能选择的 $ k $ 的最大值是 $ 1 $。用于对排列进行排序的操作如下：
- 交换 $ p_2 $ 和 $ p_1 $（$ 2 - 1 = 1 $）$ \rightarrow $ $ p = [1, 3, 2] $
- 交换 $ p_2 $ 和 $ p_3 $（$ 3 - 2 = 1 $）$ \rightarrow $ $ p = [1, 2, 3] $

在第二个测试用例中，你能选择的 $ k $ 的最大值是 $ 2 $。用于对排列进行排序的操作如下：
- 交换 $ p_3 $ 和 $ p_1 $（$ 3 - 1 = 2 $）$ \rightarrow $ $ p = [1, 4, 3, 2] $
- 交换 $ p_4 $ 和 $ p_2 $（$ 4 - 2 = 2 $）$ \rightarrow $ $ p = [1, 2, 3, 4] $

### 样例 #1
#### 输入
```
7
3
3 1 2
4
3 4 1 2
7
4 2 6 7 5 3 1
9
1 6 7 4 9 2 3 8 5
6
1 5 3 4 2 6
10
3 10 5 2 9 6 7 8 1 4
11
1 11 6 4 8 3 7 5 9 10 2
```
#### 输出
```
1
2
3
4
3
2
3
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路基本一致，都是通过计算每个元素当前位置与目标位置的差值的绝对值，然后求这些差值绝对值的最大公因数，这个最大公因数就是能使排列排序的最大的 $k$ 值。不同题解在代码实现上略有差异，部分使用了自定义的 `gcd` 函数，部分使用了 C++ 内置的 `__gcd` 函数，还有一个题解采用了枚举因数求交集的方法，但复杂度较高。

### 所选的题解
- **作者：glx123（4星）**
  - **关键亮点**：思路清晰，代码简洁，手动实现 `gcd` 函数，保证了代码的通用性。
  - **重点代码**：
```c
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
int main(){
    int t;
    scanf("%d",&t);
    int a[100005];
    while(t--){
        int n,ans=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            a[i]=abs(a[i]-i);
            ans=max(ans,a[i]);
        }
        for(int i=1;i<=n;i++){
            ans=gcd(ans,a[i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心实现思想**：先输入测试用例的数量，对于每个测试用例，输入排列的长度和排列元素，计算每个元素当前位置与目标位置的差值的绝对值，找出其中的最大值，然后通过 `gcd` 函数逐个求最大公因数，最终得到的最大公因数就是答案。

### 最优关键思路或技巧
对于每个元素 $p_i$，其当前位置 $i$ 与目标位置 $p_i$ 的差值的绝对值 $|p_i - i|$ 是关键，$k$ 必须是所有这些差值绝对值的因数，所以求这些差值绝对值的最大公因数就能得到最大的 $k$ 值。

### 可拓展之处
同类型题目可能会改变交换规则，或者增加其他限制条件，但核心思路仍然是分析元素的位置关系，找到满足条件的最大公因数或其他数学关系。类似的算法套路可以应用在其他需要分析元素位置移动的题目中。

### 推荐洛谷题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P2152 [SDOI2009] SuperGCD](https://www.luogu.com.cn/problem/P2152)

### 个人心得
- **作者：robinyqc**：提到赛时写了一个复杂度为 $O(n\sqrt n \log n)$ 的离谱做法，虽然复杂度较高，但相信 CF 现代计算机的速度，代码只跑了 358 ms。这表明在竞赛中可以根据实际情况选择合适的算法，同时也提醒我们要注意算法复杂度对程序运行时间的影响。 

---
处理用时：41.31秒