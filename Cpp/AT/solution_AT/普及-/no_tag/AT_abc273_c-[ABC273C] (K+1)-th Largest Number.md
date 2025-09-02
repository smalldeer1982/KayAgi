# [ABC273C] (K+1)-th Largest Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc273/tasks/abc273_c

長さ $ N $ の数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます。 $ K\ =\ 0,\ 1,\ 2,\ \ldots,\ N-1 $ のそれぞれについて、下記の問題を解いてください。

> $ 1 $ 以上 $ N $ 以下の整数 $ i $ であって、次の条件を満たすものの個数を求めよ。
> 
> - $ A $ に含まれる整数のうち $ A_i $ より大きいものはちょうど $ K $ 種類である。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

例として、$ K\ =\ 2 $ の場合の問題の答えを以下で求めます。 - $ A_1\ =\ 2 $ に関して、$ A $ に含まれる整数のうち $ A_1 $ より大きいものは、$ 7,\ 8 $ の $ 2 $ 種類です。 - $ A_2\ =\ 7 $ に関して、$ A $ に含まれる整数のうち $ A_2 $ より大きいものは、$ 8 $ の $ 1 $ 種類です。 - $ A_3\ =\ 1 $ に関して、$ A $ に含まれる整数のうち $ A_3 $ より大きいものは、$ 2,\ 7,\ 8 $ の $ 3 $ 種類です。 - $ A_4\ =\ 8 $ に関して、$ A $ に含まれる整数のうち $ A_4 $ より大きいものは、$ 0 $ 種類です（存在しません）。 - $ A_5\ =\ 2 $ に関して、$ A $ に含まれる整数のうち $ A_5 $ より大きいものは、$ 7,\ 8 $ の $ 2 $ 種類です。 - $ A_6\ =\ 8 $ に関して、$ A $ に含まれる整数のうち $ A_6 $ より大きいものは、$ 0 $ 種類です（存在しません）。 よって、$ A $ に含まれる整数のうち$ A_i $ より大きいものがちょうど $ K\ =\ 2 $ 種類であるような $ i $ は、$ i\ =\ 1 $ と $ i\ =\ 5 $ の $ 2 $ つです。よって、$ K\ =\ 2 $ の場合の答えは $ 2 $ です。

## 样例 #1

### 输入

```
6
2 7 1 8 2 8```

### 输出

```
2
1
2
1
0
0```

## 样例 #2

### 输入

```
1
1```

### 输出

```
1```

## 样例 #3

### 输入

```
10
979861204 57882493 979861204 447672230 644706927 710511029 763027379 710511029 447672230 136397527```

### 输出

```
2
1
2
1
2
1
1
0
0
0```

# 题解

## 作者：Epoch_L (赞：1)

## C
求出对于每个 $k\in[0,k-1]$，有多少个数满足恰好有 $k$ **种**数大于它。
### Solution
先离散化后记为 $t_i$，设值域为 $len$，求出每个值是否对应有数，并求前缀和，记为 $s_i$，考虑每个数对答案的贡献，比它大的数的个数就是 $s_{len}-s_{t_i}$，将答案数组加上即可，具体见代码。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=2e5+7;
int a[N],b[N],t[N],s[N],ans[N],n,len;
void init(){
  for(int i=1;i<=n;i++)b[i]=a[i];
  sort(b+1,b+n+1);
  len=unique(b+1,b+n+1)-b-1;
  for(int i=1;i<=n;i++)
    t[i]=lower_bound(b+1,b+len+1,a[i])-b,s[t[i]]=1;
  for(int i=1;i<=len;i++)s[i]+=s[i-1];
}
main(){
  read(n);
  for(int i=1;i<=n;i++)read(a[i]);
  init();
  for(int i=1;i<=n;i++)
  	ans[s[len]-s[t[i]]]++;
  for(int i=0;i<n;i++)printf("%lld\n",ans[i]);
  return 0;
}
```

---

