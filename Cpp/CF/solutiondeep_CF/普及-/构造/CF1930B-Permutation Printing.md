# 题目信息

# Permutation Printing

## 题目描述

You are given a positive integer $ n $ .

Find a permutation $ ^\dagger $ $ p $ of length $ n $ such that there do not exist two distinct indices $ i $ and $ j $ ( $ 1 \leq i, j < n $ ; $ i \neq j $ ) such that $ p_i $ divides $ p_j $ and $ p_{i+1} $ divides $ p_{j+1} $ .

Refer to the Notes section for some examples.

Under the constraints of this problem, it can be proven that at least one $ p $ exists.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ p=[4,1,2,3] $ is a valid permutation. However, the permutation $ p=[1,2,3,4] $ is not a valid permutation as we can choose $ i=1 $ and $ j=3 $ . Then $ p_1=1 $ divides $ p_3=3 $ and $ p_2=2 $ divides $ p_4=4 $ . Note that the permutation $ p=[3, 4, 2, 1] $ is also not a valid permutation as we can choose $ i=3 $ and $ j=2 $ . Then $ p_3=2 $ divides $ p_2=4 $ and $ p_4=1 $ divides $ p_3=2 $ .

In the second test case, $ p=[1,2,3] $ is a valid permutation. In fact, all $ 6 $ permutations of length $ 3 $ are valid.

## 样例 #1

### 输入

```
2
4
3```

### 输出

```
4 1 2 3
1 2 3```

# AI分析结果

### 题目中文重写
# 排列打印

## 题目描述
给定一个正整数 $n$。

找到一个长度为 $n$ 的排列 $p$，使得不存在两个不同的索引 $i$ 和 $j$（$1 \leq i, j < n$；$i \neq j$），满足 $p_i$ 整除 $p_j$ 且 $p_{i + 1}$ 整除 $p_{j + 1}$。

请参考注释部分获取一些示例。

在本题的约束条件下，可以证明至少存在一个这样的排列 $p$。

注：长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2, 3, 1, 5, 4]$ 是一个排列，但 $[1, 2, 2]$ 不是排列（数字 $2$ 在数组中出现了两次），$[1, 3, 4]$ 也不是排列（$n = 3$，但数组中出现了 $4$）。

## 说明/提示
在第一个测试用例中，$p = [4, 1, 2, 3]$ 是一个有效的排列。然而，排列 $p = [1, 2, 3, 4]$ 不是有效的排列，因为我们可以选择 $i = 1$ 和 $j = 3$。此时 $p_1 = 1$ 整除 $p_3 = 3$，且 $p_2 = 2$ 整除 $p_4 = 4$。注意，排列 $p = [3, 4, 2, 1]$ 也不是有效的排列，因为我们可以选择 $i = 3$ 和 $j = 2$。此时 $p_3 = 2$ 整除 $p_2 = 4$，且 $p_4 = 1$ 整除 $p_3 = 2$。

在第二个测试用例中，$p = [1, 2, 3]$ 是一个有效的排列。实际上，所有长度为 $3$ 的 $6$ 种排列都是有效的。

## 样例 #1
### 输入
```
2
4
3
```

### 输出
```
4 1 2 3
1 2 3
```

### 综合分析与结论
这些题解的核心思路基本一致，都是通过构造一个排列，使得奇数位上的数递增，偶数位上的数递减，且偶数位上的所有数均大于奇数位上的数，以此来满足不存在 $p_i$ 整除 $p_j$ 且 $p_{i + 1}$ 整除 $p_{j + 1}$ 的条件。

算法要点在于使用两个指针 $l$ 和 $r$，分别从 $1$ 和 $n$ 开始，交替输出 $l$ 和 $r$ 的值，并更新指针位置，直到 $l > r$。

解决的难点在于如何构造出满足条件的排列，通过分析发现让偶数位的数整体大于奇数位的数可以避免出现整除关系。

### 各题解评分
- **Kawaii_qiuw**：4星。思路清晰，代码简洁，但存在输出格式错误（`printf("/n");` 应改为 `printf("\n");`）。
- **__zyq_666_kpzc__**：3星。思路正确，但代码中 `l++` 位置不当，导致第一个数输出错误。
- **joker_opof_qaq**：4星。思路清晰，使用了快速读入输出，代码效率较高。
- **新哲**：4星。思路清晰，代码简洁易懂。
- **_Maverick_**：4星。思路清晰，代码简洁明了。
- **QingDeng_Star**：3星。思路正确，但代码中 `if(b - a == 1)` 的判断多余。
- **JOE_ZengYuQiao_0928**：4星。思路清晰，代码简洁。
- **liangkairui**：3星。思路正确，但使用数组存储结果，增加了空间复杂度。
- **王逸辰**：4星。思路清晰，代码简洁。
- **WhisperingWillow**：3星。思路独特，但没有给出完整代码，且特判情况未详细说明。
- **Jerry_heng**：3星。思路正确，但使用数组存储结果，增加了空间复杂度。
- **Hero_Broom**：4星。思路清晰，代码有注释，易于理解。

### 所选题解
- **Kawaii_qiuw（4星）**：关键亮点是思路清晰，代码简洁。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t, n;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int l = 1, r = n;
        while(l <= r)
        {
            printf("%d ", l);
            l++;
            if(l > r) break;
            printf("%d ", r);
            r--;
        }
        printf("\n"); // 修改输出格式
    }
    return 0;
}
```
核心实现思想：使用两个指针 $l$ 和 $r$ 分别从 $1$ 和 $n$ 开始，交替输出 $l$ 和 $r$ 的值，并更新指针位置，直到 $l > r$。

- **joker_opof_qaq（4星）**：关键亮点是使用了快速读入输出，代码效率较高。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
inline void write(int x) {
    if (x<0)x=-x,putchar('-');
    if (x>9)write(x/10);
    putchar(x%10+'0');
}
int main(){
    int t=read();
    while(t--){
        int l=1,r=read();
        while(l<=r){
            cout<<l++<<" ";
            if(l<=r)cout<<r--<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```
核心实现思想：与上一题解类似，只是使用了快速读入输出函数。

- **新哲（4星）**：关键亮点是思路清晰，代码简洁易懂。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T, l, r;
    cin >> T;
    while (T--)
    {
        l = 1;
        cin >> r;
        while (l <= r)
        {
            cout << l << " ";
            l++;
            if (l <= r) {
                cout << r << " ";
                r--;
            }
        }
        cout << "\n";
    }
    return 0;
}
```
核心实现思想：同样使用两个指针 $l$ 和 $r$ 交替输出值。

### 最优关键思路或技巧
通过分析题目条件，发现构造一个奇数位递增、偶数位递减且偶数位大于奇数位的排列可以满足要求，使用双指针法实现该排列的构造，代码简洁且效率高。

### 可拓展之处
同类型题可能会要求构造满足其他特定条件的排列，解题思路可以从分析条件入手，尝试找到一种规律或模式来构造排列。类似算法套路包括使用双指针、贪心算法等。

### 推荐题目
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：考察排列组合的构造和判断。
- [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)：经典的全排列生成问题。
- [P2370 yyy2015c01 的 U 盘](https://www.luogu.com.cn/problem/P2370)：涉及排列组合和条件判断。

### 个人心得
题解中未包含个人心得。

---
处理用时：42.18秒