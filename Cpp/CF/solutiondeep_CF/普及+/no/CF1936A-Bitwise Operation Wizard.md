# 题目信息

# Bitwise Operation Wizard

## 题目描述

This is an interactive problem.

There is a secret sequence $ p_0, p_1, \ldots, p_{n-1} $ , which is a permutation of $ \{0,1,\ldots,n-1\} $ .

You need to find any two indices $ i $ and $ j $ such that $ p_i \oplus p_j $ is maximized, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

To do this, you can ask queries. Each query has the following form: you pick arbitrary indices $ a $ , $ b $ , $ c $ , and $ d $ ( $ 0 \le a,b,c,d < n $ ). Next, the jury calculates $ x = (p_a \mid p_b) $ and $ y = (p_c \mid p_d) $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). Finally, you receive the result of comparison between $ x $ and $ y $ . In other words, you are told if $ x < y $ , $ x > y $ , or $ x = y $ .

Please find any two indices $ i $ and $ j $ ( $ 0 \le i,j < n $ ) such that $ p_i \oplus p_j $ is maximum among all such pairs, using at most $ 3n $ queries. If there are multiple pairs of indices satisfying the condition, you may output any one of them.

## 说明/提示

In the first test case, the hidden permutation is $ p=[0,3,1,2] $ .

For the query "? 0 2 3 1", the jury return "&lt;" because $ (p_0 \mid p_2) = (0 \mid 1) =1 < (p_3 \mid p_1) = (2 \mid 3) = 3 $ .

For the query "? 1 1 2 3", the jury return "=" because $ (p_1 \mid p_1) = (3\mid 3)= 3 = (p_2 \mid p_3) = (1 \mid 2)=3 $ .

For the query "? 1 2 0 3", the jury return "&gt;" because $ (p_1 \mid p_2) = (3 \mid 1) = 3 > (p_0 \mid p_3) = (0\mid 2)=2 $ .

The answer $ i = 3 $ and $ j = 2 $ is valid: $ (p_3 \oplus p_2) = (2 \oplus 1) = 3 $ is indeed equal to the maximum possible value of $ p_i \oplus p_j $ . Another valid answer would be $ i=0 $ and $ j=1 $ . As the number of queries does not exceed $ 3n=12 $ , the answer is considered correct.

In the second test case, $ n = 2 $ , so $ p $ is either $ [0, 1] $ or $ [1, 0] $ . In any case, $ p_0 \oplus p_1 = 1 $ is maximum possible.

## 样例 #1

### 输入

```
2
4

&lt;

=

&gt;

2```

### 输出

```
? 0 2 3 1

? 1 1 2 3

? 1 2 0 3

! 3 2

! 0 1```

# AI分析结果

### 题目内容重写

#### 题目描述

这是一个交互题。

有一个秘密序列 $ p_0, p_1, \ldots, p_{n-1} $，它是 $ \{0,1,\ldots,n-1\} $ 的一个排列。

你需要找到任意两个索引 $ i $ 和 $ j $，使得 $ p_i \oplus p_j $ 最大化，其中 $ \oplus $ 表示 [按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

为此，你可以进行查询。每个查询的形式如下：你选择任意索引 $ a $、$ b $、$ c $ 和 $ d $（$ 0 \le a,b,c,d < n $）。然后，裁判计算 $ x = (p_a \mid p_b) $ 和 $ y = (p_c \mid p_d) $，其中 $ | $ 表示 [按位或操作](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。最后，你会收到 $ x $ 和 $ y $ 的比较结果。换句话说，你会被告知 $ x < y $、$ x > y $ 或 $ x = y $。

请找到任意两个索引 $ i $ 和 $ j $（$ 0 \le i,j < n $），使得 $ p_i \oplus p_j $ 在所有这样的对中最大，且最多使用 $ 3n $ 次查询。如果有多个索引对满足条件，你可以输出其中任意一个。

### 算法分类

位运算、构造

### 题解分析与结论

本题的核心是通过位运算（按位或和按位异或）来找到使异或值最大的两个数。由于是交互题，查询次数有限制（最多 $3n$ 次），因此需要高效的算法来找到答案。

#### 题解对比

1. **Wf_yjqd 的题解**：
   - **思路**：首先通过 $n-1$ 次查询找到最大值 $n-1$ 的位置，然后通过 $n-1$ 次查询找到与 $n-1$ 按位或最大的数，最后在这些数中找到最小的数，即为与 $n-1$ 异或最大的数。
   - **亮点**：思路清晰，代码简洁，查询次数控制在 $3n$ 次以内。
   - **评分**：5星

2. **Missa 的题解**：
   - **思路**：同样先找到最大值 $n-1$ 的位置，然后通过按位或找到与 $n-1$ 异或最大的数。
   - **亮点**：代码实现较为简洁，逻辑清晰。
   - **评分**：4星

3. **Coinred001 的题解**：
   - **思路**：通过按位或的性质，找到与 $n-1$ 异或最大的数，并在这些数中找到最小的数。
   - **亮点**：详细解释了按位或和按位异或的性质，代码实现较为清晰。
   - **评分**：4星

#### 最优关键思路

1. **找到最大值 $n-1$ 的位置**：通过 $n-1$ 次查询，比较每个数与当前最大值的按位或，找到最大值的位置。
2. **找到与 $n-1$ 异或最大的数**：通过按位或的性质，找到与 $n-1$ 按位或最大的数，并在这些数中找到最小的数，即为与 $n-1$ 异或最大的数。

#### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4+26;
int T,n,mx,mn,st[maxn],top;
char s[26],res;
inline char Q(int a,int b,int c,int d){
    printf("? %d %d %d %d\n",a,b,c,d);
    fflush(stdout);
    scanf("%s",s);
    return s[0];
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        mx=0;
        for(int i=1;i<n;i++)
            mx=(Q(mx,mx,i,i)=='<'?i:mx);
        st[top=1]=mx;
        for(int i=0;i<n;i++)
            if(i!=mx){
                if((res=Q(i,mx,st[top],mx))=='=')
                    st[++top]=i;
                else if(res=='>')
                    st[top=1]=i;
            }
        mn=st[1];
        for(int i=2;i<=top;i++)
            mn=(Q(mn,mn,st[i],st[i])=='>'?st[i]:mn);
        printf("! %d %d\n",mx,mn);
        fflush(stdout);
    }
    return 0;
}
```

#### 拓展思路

本题的关键在于利用按位或和按位异或的性质，通过有限的查询次数找到最大值和与之异或最大的数。类似的问题可以考察其他位运算的性质，如按位与、按位取反等。

#### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)

这些题目都涉及到通过有限的操作次数找到特定的解，适合进一步练习位运算和交互题的解题思路。

---
处理用时：42.76秒