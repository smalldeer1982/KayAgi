# [BalticOI 2022] Art Collection (Day1)

## 题目描述

有一个值域 $[1,n]$ 的未知排列 $P$。你每次可以询问一个排列 $R$。交互库会返回满足在排列 $P$ 中 $i$ 出现在 $j$ 前面，在排列 $R$ 中 $i$ 出现在 $j$ 后面的有序对 $(i,j)$ 的数量。你需要猜出排列 $P$。

### 实现细节

你无需在程序开头引用头文件 `art.h`，你只需要在代码开头加入以下代码。

```cpp
#include <vector>
void answer(std::vector<int>);
int publish(std::vector<int>);
```

你需要实现一个函数 `void solve(int N)`，这个函数可以调用如下函数：

- `int publish(std::vector<int> R)`
    - 该函数可以向交互库询问排列 $R$，$R$ 应当是一个值域 $[1,n]$ 的排列。
    - 该函数至多能被调用 $4000$ 次。
- `void answer(std::vector<int> R)`
    - 该函数向交互库提交答案，表示你猜测的排列。
    - 你必须恰好调用该函数一次。

## 说明/提示

### 样例交互

考虑排列 $P$ 是 $\{1,3,2\}$。

样例中进行的交互如下：

|         调用         | 返回值 |               解释               |
| :------------------: | :----: | :------------------------------: |
| `publish({1, 2, 3})` |   1    |       合法有序对为 $(3,2)$       |
| `publish({2, 3, 1})` |   3    | 合法有序对为 $(1,3),(1,2),(3,2)$ |
| `answer({1, 3, 2})`  |        |        回答与正确答案相符        |

### 数据范围与提示

- 子任务 $1$ ($5$ 分)：$N \leq 6$
- 子任务 $2$ ($15$ 分)：$N \leq 40$
- 子任务 $3$ ($15$ 分)：$N \leq 250$
- 子任务 $4$ ($15$ 分)：$N \leq 444$
- 子任务 $5$ ($20$ 分)：$N \leq 2000$
- 子任务 $6$ ($30$ 分)：没有特殊限制

对于所有数据，满足 $2\leq N \leq 4000$

# 题解

## 作者：FFTotoro (赞：2)

考虑对于每个元素单独计算排名。假设我们现在要求 $x$ 在 $P$ 中的排名（设该排名为 $y$），可以考虑如下的询问构造：

- $R_1=\{x,\ldots\}$
- $R_2=\{\ldots,x\}$

其中两者 $\ldots$ 的部分需要是一样的；设 $\ldots$ 内部的贡献为 $\Delta$，即与 $x$ 无关的贡献。

根据题意，可以得出 $\mathrm{answer}(R_1)=y+\Delta$，$\mathrm{answer}(R_2)=N-y-1+\Delta$，于是 $y=\dfrac{\mathrm{answer}(R_1)-\mathrm{answer}(R_2)+N-1}{2}$。直接按这种方法对于每个元素构造两个排列可以做到 $2N$ 次询问，可获得 $70$ 分。

考虑压缩询问次数，即考虑合并一些元素的询问：观察到 $R_2$ 为 $R_1$ 向左循环位移一位得到的结果，于是令初始排列为 $\{1,2,\ldots,N\}$，每次将其向左循环位移一位继续询问，即可依次得出元素 $1,2,\ldots,N$ 的排名。

放代码（代码中的数组均为 $0$-indexed）：

```cpp
#include<bits/stdc++.h>
using namespace std;
void answer(vector<int>);
int publish(vector<int>);
void solve(int n){
  vector<int> a(n),r(n);
  for(int i=0;i<n;i++){
    vector<int> v;
    for(int j=i;j<n;j++)
      v.emplace_back(j+1);
    for(int j=0;j<i;j++)
      v.emplace_back(j+1);
    a[i]=publish(v);
  } // 循环位移构造询问
  for(int i=0;i<n;i++)
    r[a[i]-a[(i+1)%n]+n-1>>1]=i+1;
    // 计算排名并存入答案
  answer(r);
}
```

---

## 作者：shinzanmono (赞：0)

考虑以下两个询问：

- $\{1,2,\ldots,n\}$
- $\{2,\ldots,n,1\}$

设第一个询问返回的答案为 $x$，第二个询问返回的答案为 $y$，可以发现 $x$ 即为原排列中子序列 $(i,1)$ 的个数加上中间 $2,3,\ldots,n$ 的答案，第二个询问同理，设 $(i,1)$ 的个数为 $A$，$(1,i)$ 的个数为 $B$，则 $A+B=n-1,A-B=x-y$。可以求出 $A$，那么我们就确定了 $1$ 的位置，其他同理。

考虑询问以下序列：

- $\{1,2,\ldots,n\}$
- $\{2,\ldots,n,1\}$
- $\ \ \ \ \ \ \ \ \ \ \vdots$
- $\{n,1,\ldots,n-1\}$

我们发现相邻两个序列只有首尾不同，所以可以通过重复利用，达到 $n$ 次询问，即可通过本题。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
const int sz=4010;
void answer(std::vector<int>);
int publish(std::vector<int>);
int f[sz];
void solve(int N){
    std::vector<int>P(N);
    for(int i=1;i<=N;i++){
        std::vector<int>R;
        for(int j=i;j<=N;j++)R.push_back(j);
        for(int j=1;j<i;j++)R.push_back(j);
        f[i]=publish(R);
    }
    for(int i=1;i<=N;i++)P[(N+f[i]-f[i%N+1]-1)/2]=i;
    answer(P);
}
```

---

