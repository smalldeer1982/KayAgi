# Court Blue (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is not guaranteed that $ n=m $ , and the time limit is higher. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Flamm wins, $ \gcd(1,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 1\cdot2+4\cdot5=22 $ .

## 样例 #1

### 输入

```
8
3 4 2 5
4 4 1 4
6 6 2 2
7 9 2 3
8 9 9 1
2 7 1 4
5 9 1 4
5 6 6 7```

### 输出

```
22
17
18
37
77
30
41
59```

## 样例 #2

### 输入

```
2
3082823 20000000 1341 331
20000000 20000000 3 5```

### 输出

```
10754065643
159999991```

## 样例 #3

### 输入

```
1
139 1293 193 412```

### 输出

```
559543```

# 题解

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2002F2)

**题目大意**

> 给定两个变量 $x,y$ 初始为 $0$，每次操作选择其中一个 $+1$，要求始终保证：$x\in[0,n],y\in[0,m],\gcd(x,y)\le 1$，求可能的最大 $px+qy$。
>
> 数据范围：$n,m\le 2\times 10^7$。

**思路分析**

打表观察，可以发现当 $x,y$ 较小的时候，几乎总是有合法的构造，因此可以假设 $n-x<B$ 或 $m-y<B$ 的 $(x,y)$ 总是能被生成。

然后直接 dp 即可，$f_{i,j}$ 表示 $x=n-i,y=m-j$ 是否能得到。

时间复杂度 $\mathcal O(B^2\log V)$，取 $B=120$ 能通过此题。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int L=120;
bool f[L+5][L+5];
int bgcd(int x,int y) {
	if(!x||!y||x==y) return x|y;
	if(~x&1) return y&1?bgcd(x>>1,y):(bgcd(x>>1,y>>1)<<1);
	return y&1?(x<y?bgcd((y-x)>>1,x):bgcd((x-y)>>1,y)):bgcd(x,y>>1);
}
void solve() {
	int n,m,a,b;
	scanf("%d%d%d%d",&n,&m,&a,&b);
	memset(f,0,sizeof(f));
	int u=max(1,n-L),v=max(1,m-L);
	ll ans=0;
	for(int i=0;i<=n-u;++i) for(int j=0;j<=m-v;++j) {
		if(!i||!j) f[i][j]=1;
		else if(bgcd(i+u,j+v)<=1) f[i][j]=f[i-1][j]|f[i][j-1];
		if(f[i][j]) ans=max(ans,1ll*a*(i+u)+1ll*b*(j+v));
	}
	printf("%lld\n",ans);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

