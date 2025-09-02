# Liars and Serge

## 题目描述

There are $ n $ people, sitting in a line at the table. For each person we know that he always tells either the truth or lies.

Little Serge asked them: how many of you always tell the truth? Each of the people at the table knows everything (who is an honest person and who is a liar) about all the people at the table. The honest people are going to say the correct answer, the liars are going to say any integer from 1 to $ n $ , which is not the correct answer. Every liar chooses his answer, regardless of the other liars, so two distinct liars may give distinct answer.

Serge does not know any information about the people besides their answers to his question. He took a piece of paper and wrote $ n $ integers $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the answer of the $ i $ -th person in the row. Given this sequence, Serge determined that exactly $ k $ people sitting at the table apparently lie.

Serge wonders, how many variants of people's answers (sequences of answers $ a $ of length $ n $ ) there are where one can say that exactly $ k $ people sitting at the table apparently lie. As there can be rather many described variants of answers, count the remainder of dividing the number of the variants by $ 777777777 $ .

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
2
```

# 题解

## 作者：moonbowqwq (赞：5)

[题目链接](https://codeforces.com/problemset/problem/256/D)

第一次用打表法做题，写篇题解记一下。

## 题意简述

$n$ 个人坐成一排，编号为 $1$ 到 $n$，诚实的人说真话，虚伪的人说假话，每个人都知道场上几个人说真话，几个人说假话。

Little Serge 想要知道场上每个人的身份，对此他问每一个人一个问题。

一个编号为 $i$ 的人会回答一个数 $a_i$。如果这个人是诚实的，那么他会回答场上诚实的人的人数，如果这个人是虚伪的，那么他会随机回答一个 $1$ 到 $n$ 中的不是场上诚实人数的数。

现在 Little Serge 想知道有多少个可能的回答序列 $a$，使得 Little Serge 能够断定其中恰好有 $k$ 个人**一定**是虚伪的人（不包括不确定的），由于答案可能很大，请输出其对 $777777777$ 取模的结果。

数据范围与约定：$1\leq k \leq n\leq 2^8$，保证 $n$ 为 $2$ 的幂。

## 解题思路

首先，我们需要知道如何判断一个人是否**一定**是虚伪的。题目中有这样一句话：

> 如果这个人是诚实的，那么他会回答场上诚实的人的人数。

从这句话中我们可以发现，一个人可能是诚实的**当且仅当**包括他在内一共有 $a$ 个人回答了数字 $a$。

那么我们设 $f_{i,j,k}$ 表示当前状态 $i,j,k$ 下的符合要求的序列个数，其中 $i$ 表示一共有 $i$ 个人回答，$j$ 表示回答的数字范围为 $[i,j - 1]$，$k$ 表示有 $k$ 个人一定是虚伪的的。考虑如何进行转移，对于当前已知的状态 $f_{i,j,k}$，我们枚举回答数字 $j$ 的人的个数，对于当前枚举到的个数 $l (l \in [0,n - i])$，我们分两种情况来进行转移：

$$f_{i + l,j + 1,k} = f_{i + l,j + 1,k} + f_{i,j,k} \times \operatorname{C}_{l}^{i + l}(l = j)$$

$$f_{i + l,j + 1,k + l} = f_{i + l,j + 1,k + l} + f_{i,j,k} \times \operatorname{C}_{l}^{i + l}(l \not = j)$$

最后统计出来的结果便是 $f_{n,n + 1,k}$ 了，但由于该做法的复杂度是 $O(n^4)$，所以需要提前在本地预处理出答案来进行回答，也就是打表。

这边再补充说明一下转移方程中组合数的用途。由于我们需要求的是符合要求的序列的个数，而如果直接求 $f$ 得到的是符合要求的单调不降的序列个数，所以我们还需要求出其全排列个数。

那么该如何去求呢？对于当前的状态 $f_{i,j,k}$，假设当前有 $l$ 个人回答了数字 $j$，把原先序列中的元素看作是相同的，那么所组成的新序列的个数就为 $\operatorname{C}_{l}^{i + l}$。又由于原先序列的个数为 $f_{i,j,k}$，所以新序列的个数为 $f_{i,j,k} \times \operatorname{C}_{l}^{i + l}$。

对于组合数 $\operatorname{C}$，我们只需要通过递推来预处理出即可。

## 代码实现

这是打表用的代码：

```cpp
#include<bits/stdc++.h>

using namespace std;
const int MOD = 777777777,MN = 1 << 8;

int C[MN + 5][MN + 5];

int N,K;

int F[MN + 5][MN + 5][MN + 5];

void Init();
void Solve(int n);

int main(){
  Init();
  printf("{");
  for(int i = 0;i <= 8;++i){
    printf("{");
    int n = 1 << i;
    Solve(n);
    printf("%d",F[n][n + 1][0]);
    for(int k = 1;k <= n;++k)
      printf(",%d",F[n][n + 1][k]);
    printf(i == 8 ? "}" : "},");
  }
  printf("};");
  return 0;
}

void Init(){
  for(int i = 0;i <= MN;++i)
    C[i][0] = 1;
  C[1][1] = 1;
  for(int i = 2;i <= MN;++i)
    for(int j = 1;j <= i;++j)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
  return;
}

void Solve(int n){
  memset(F,0,sizeof(F));
  F[0][1][0] = 1;
  for(int i = 0;i <= n;++i)
    for(int j = 1;j <= n;++j)
      for(int k = 0;k <= i;++k){
	for(int cs = n - i;cs >= 0;--cs)
	  if(cs != j)
	    F[i + cs][j + 1][k + cs] = (F[i + cs][j + 1][k + cs] + (long long)F[i][j][k] * C[i + cs][cs] % MOD) % MOD;
	if(i + j <= n)
	  F[i + j][j + 1][k] = (F[i + j][j + 1][k] + (long long)F[i][j][k] * C[i + j][j] % MOD) % MOD;
      }
  return;
}
```

提交用的代码比较长我就放云剪贴板里了：[code](https://www.luogu.com.cn/paste/sw4wuz1n)。

---

