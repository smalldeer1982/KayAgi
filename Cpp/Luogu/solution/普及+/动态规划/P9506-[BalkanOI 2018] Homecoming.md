# [BalkanOI 2018] Homecoming

## 题目背景

翻译自 BalkanOI 2018 Day1 T2「Homecoming」；由于洛谷远慢于 loj，因此将时间限制从 300ms 调整至 500ms。

## 题目描述

有 $N$ 门课程，分别编号为 $0$ 到 $N-1$。如果你 pass 了课程 $i$，你可以拿到 $A _ i$ 美刀。  
有 $N$ 本教材，分别编号为 $0$ 到 $N-1$。$i$ 号教材的价格为 $B _ i$ 美刀。  
如果你要 pass 课程 $i$，你需要购买编号为 $i, (i+1) \bmod N, (i+2) \bmod N, \cdots, (i+K-1) \bmod N$ 的课本。$K$ 为给定的常数。  
你的目的是赚钱而非 pass 所有课程。请求出你最多能赚多少美刀。

## 交互过程

本题只支持 C++ 语言使用函数交互测评。**选手代码不需要也不能包含 `homecoming.h`，也不需要实现 `main` 函数。**

选手程序需要实现如下函数：

```
long long int solve(int N, int K, int *A, int *B);
```

在一次运行中这个函数可能会被调用多次。


## 样例

调用

```
solve(3, 2,
[40, 80, 100],
[140, 0, 20])
```

的返回值为 $60$。



## 说明/提示

### 数据范围及限制

令所有对 `solve` 函数的调用中 $N$ 的总和为 $S_N$，$NK$ 的总和为 $S_{NK}$。那么：

- $1\le K\le N\le 2\times 10^6$
- $1\le S_N\le 2\times 10^6$
- $0\le A_i,B_i\le 10^9$

详细子任务及附加限制如下表所示。

| 子任务编号 | 附加限制 | 分值 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $1\le S_N\le 500$ | $13$ |
| $2$ | $1\le S_N\le 5000$ | $18$ |
| $3$ | $1\le S_{NK}\le 2\times 10^6$ | $31$ |
| $4$ | 无附加限制 | $38$ |




# 题解

## 作者：Zhao_daodao (赞：4)

# solution
感觉接近一道板子题。

首先考虑一条链的情况。

定义 $dp_i$ 表示当前考虑到了第 $i$ 个课程，
定义 $cost_{i,j}$ 表示 $\sum\limits_{k=i}^{j}b_k$。

对于 $dp_i$ 有两种可能：

1. 买整一个课程，即 $\max_{1\le j<i}{dp_j}+cost(i+1,i+k-1)$。
2. 买一部分课程，即 $dp_{i-1}+b_{i+k-1}$。

正确性：如果买一部分课程，那么最优解一定可以全部不买，否则已经被 $dp_{i-1}$ 考虑到了。

此时有一个及其板的思路：钦定第一个买还是不买，因为 $k\le n$，所以之后的转移显然是正确的。

那么只用跑两种情况，即第一个课程选还是不选，就可以包含所有情况了。

只需要调整一下转移方程就行了。

最后的答案是 $\max_{i=1}^{n}dp_i$。

---

## 作者：liangbowen (赞：3)

[blog](https://www.cnblogs.com/liangbowen/p/17773256.html)。First solution /kx。

---

容易想到断环成链。然后 $dp_i$ 表示到第 $i$ 个位置所获的最多钱数。再维护 $dp_{1\le j<i}$ 的最大值 $mx_i$。

对于当前位置，要么用 $dp_{i-1}$（已经买过了 $i-1$ 所需买的课本）转移，要么用 $mx_{i-1}$（没买过 $i-1$）转移，实现方面前缀和即可，这个不难。

然后写一发交 loj，发现能获得 $40$ 左右的高分。这是因为你断环成链了，如果你第 $1$ 个位置选了，那么在整个数组最后几个位置，你要买的教材就会循环回去 $1$ 那里，但他们其实被买过了。

所以分类一下第一个位置选不选，然后跑两次 DP 即可。

[code](https://loj.ac/s/1915738)，时间复杂度 $O(n)$。


---

## 作者：cyngugugu (赞：1)

# 题目分析 

这一题很明显是一个 DP 题，定义 $dp_i$ 为第 $i$ 本书并购买能获得的最大钱数，由于 $dp_i$ 可能依赖 $i$ 前面的书，我们需要断环成链，再定义 $maxn_i$ 为 $dp_{1 \le j < i}$ 的最大值。

转移时要么从 $dp_{i-1}$ 转移（只需要买第 $i+k-1$ 本书就可以了），要么从 $maxn_{i-1}$ 转移（需要买所需的所有书），计算时可以用前缀和维护区间内书的价格。

但是如果直接这么计算会写挂，因为算到最后几个的时候如果你选了第 $1$ 个，它会重复计算 $1$ 至 $k$ 之间的书，而这些书你已经在选 $1$ 的时候计算过了，所以我们要分类讨论一下，两次 DP 一次选 $1$ ，一次不选。~~（剩下看不懂的可以看下面代码，有注释）~~

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define of(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const ll NN=(2e6+10)*2;
ll a[NN],b[NN],sum[NN];
ll f[NN],maxx[NN];
int aa[NN],bb[NN];
ll query(int l,int r){
	return sum[r]-sum[l-1];
}
long long int solve(int N, int K, int *A, int *B){
	ll ans=0;
	fo(i,1,N){
		a[i]=A[i-1];
		a[i+N]=a[i];
	}//因为在实际使用时，指针非常容易 RE ，可以直接在输入时替换为数组，随便断环成链。
	fo(i,1,N){
		b[i]=B[i-1];
		b[i+N]=b[i];
	}
	fo(i,1,N*2){
		sum[i]=sum[i-1]+b[i];
	}
	f[1]=a[1]-query(1,K);
	maxx[1]=-1e18;
	fo(i,2,N){
		if(i+K-1<=N){
			f[i]=max(f[i-1]-b[i+K-1],maxx[i-1]-query(i,i+K-1))+a[i];
		}//在 1 一定选的前提下， 1 到 k 的书会被直接购买，所以如果 i+k-1>n ，直接计算 i 到 n 就可以了
		else f[i]=max(f[i-1],maxx[i-1]-query(i,N))+a[i];
		maxx[i]=max(maxx[i-1],f[i-1]);
	}
	fo(i,1,N)ans=max(ans,f[i]);
	f[1]=-1e18;
	maxx[1]=0;
	fo(i,2,N){
		f[i]=max(f[i-1]-b[i+K-1],maxx[i-1]-query(i,i+K-1))+a[i];
		maxx[i]=max(maxx[i-1],f[i-1]);
	}
	fo(i,1,N)ans=max(ans,f[i]);
	return ans;
}
```

---

