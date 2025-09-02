# ぽよぽよ

## 题目描述

在一条直线上，有 $ n $ 只名为ポヨクン的生物。第 $ i $ 只ポヨクン用长度为 $ l_i $ 的链子拴在位置 $ p_i $ 的柱子上。这意味着，第 $ i $ 只ポヨクン可以在从 $ p_i - l_i $ 到 $ p_i + l_i $ 之间的任何一个格子内自由移动。

当这些ポヨクン根据索引顺序从左到右各自占据不同的格子时，我们需要计算有多少种可能的配置。具体来说，我们需要统计满足以下条件的位置组合的数量：
1. $ x_i $ 是整数。
2. $ x_i $ 满足 $ p_i - l_i \leq x_i \leq p_i + l_i $。
3. 对于任意的 $ j $ 满足 $ 1 \leq j \leq n $，如果 $ i < j $，则 $ x_i < x_j $。

如果任何一种组合中至少有一只ポヨクン的位置不同，那么这两种组合就是不同的。

由于答案可能非常大，需要将答案对 $ 1,000,000,007 $ 取模，并输出该结果。

## 说明/提示

### 示例解释 1

对于給定的范围，ポヨクン有 $ -3 $, $ -2 $, $ -1 $, $ 0 $, $ 1 $, $ 2 $, $ 3 $ 共计 $ 7 $ 种可能的配置。

### 示例解释 2

对于给定的情况，可能的配置包括：$ (-3, -1) $, $ (-3, 0) $, $ (-3, 1) $, $ (-3, 2) $, $ (-3, 3) $, $ (-2, -1) $, $ (-2, 0) $, $ (-2, 1) $, $ (-2, 2) $, $ (-2, 3) $, $ (-1, 0) $, $ (-1, 1) $, $ (-1, 2) $, $ (-1, 3) $, $ (0, 1) $, $ (0, 2) $, $ (0, 3) $, $ (1, 2) $, $ (1, 3) $, $ (2, 3) $，总共有 $ 20 $ 种配置。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
0 3```

### 输出

```
7```

## 样例 #2

### 输入

```
2
0 3
1 2```

### 输出

```
20```

# 题解

## 作者：oyoham (赞：0)

### Problem
题目大意：  
给定两个长为 $n$ 的数组 $p,l$，求有多少个长为 $n$ 的序列满足 $\forall 1\le i \le n,\left|p_i-a_i\right|\le l_i$ 且 $\forall i<j,a_i<a_j$。  
输入时保证按照 $p$ 升序输入。
### Solution
考虑 $f_{i,j}$ 表示已选择前 $i$ 个数且 $a_i=j$ 的方案数，不难发现方程为：
$$ f_{i,j}=\sum\limits_{p_{i-1}-l_{i-1}\le k<j}f_{i-1,k}$$
但是题目中 $p$ 很大，$l$ 却很小，于是考虑优化状态 $f_{i,j}$ 表示已选择前 $i$ 个数且 $a_i=p_i+j$ 的方案数，不难发现方程为：
$$ f_{i,j}=\sum\limits_{p_{i-1}-l_{i-1}\le p_i-p_{i-1}+k<j}f_{i-1,k}$$  
注意，当 $p_i-p_{i-1}$ 过大时，可有如下转移：
$$ f_{i,j}=\sum\limits_{|k|\le l_{i-1}}f_{i-1,k}$$
综上，有：
$$ f_{i,j}=\sum\limits_{p_i-p_{i-1}+k<j,|k|\le l_{i-1}}f_{i-1,k}$$
再考虑前缀和优化，就能做到 $\Theta(n^2)$。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int n=read();
int p[1005],l[1005]; 
int dp[2][2005];
#define M 1002
#define L 1
#define R 2003ll
#define mod 1000000007
signed main(){
	for(int i=1;i<=n;i++){
		p[i]=read(),l[i]=read();
	}
	for(int i=M-l[1];i<=M+l[1];i++) dp[1][i]=1;
	for(int i=L;i<=R;i++) (dp[1][i]+=dp[1][i-1])%=mod;
	for(int j=2;j<=n;j++){
		for(int i=L;i<=R;i++) dp[j&1][i]=0;
		for(int i=M-l[j];i<=M+l[j];i++) dp[j&1][i]=dp[j&1^1][min(R,p[j]-p[j-1]+i-1)];
		for(int i=L;i<=R;i++) (dp[j&1][i]+=dp[j&1][i-1])%=mod;
	}
	write(dp[n&1][R]);putchar(10);
}
```

---

