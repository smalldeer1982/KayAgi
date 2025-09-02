# 「RdOI R1」冰淇淋游戏(play)

## 题目背景

又有新游戏可玩啦！

## 题目描述

小 T 发现最近市面上出现了一款游戏，这款游戏分为 $n$ 关，第 $i$ 关玩一次需要 $s_i$ 个体力，最多可以玩 $m_i$ 次第 $i$ 关。想玩第 $i$ 关，必须先玩第 $i-1$ 关至少一次，当然，玩第 $1$ 关不需要这个先决条件。

游戏规则是这样的（对于第 $i$ 关）：

一共有 $k_i$ 个冰淇淋排成一排，第 $j$ 个冰淇淋的美味度为 $y_{i,j}$，每次你需要选择一个冰淇淋吃掉，共吃 $k_i$ 次，在第 $j$ 次吃第 $l$ 个冰淇淋可以获得 $j\times y_{i,l}$ 分。

当然，要想吃冰淇淋可没有那么简单，你需要在第一次吃指定的第 $c_i$ 个冰淇淋，接下来每次只能吃已经吃完的段的两边的冰淇淋，比如第一次吃的是第 $2$ 个冰淇淋，第二次可以吃第 $1$ 个或第 $3$ 个（如果有的话）。

因为小 T 的脑子不太够计算这复杂的分数，所以他想求助你，在使用体力不超过 $t$ 的情况下，最多可以获得多少分数。

## 说明/提示

【样例解释】

样例1：

最优解为玩一次第一关再玩一次第二关。

第一关按照第 $2,3,4,1$ 个的顺序吃冰淇淋，可以获得 $2\times 1+4\times 2+1\times 3+3\times 4=2+8+3+12=25$ 的分数。

第二关按照第 $3,4,2,1$ 个的顺序吃冰淇淋，可以获得 $2\times 1+2\times 2+3\times 3+2\times 4=2+4+9+8=23$ 的分数。

所以最多可以获得 $25\times 1+23\times 1=48$ 的分数。

样例2：

最优解为玩两次第一关，一次第二关，一次第三关。

可以获得 $10000 \times 2+1 \times 1+2 \times 1=20003$ 的分数。

---

【数据范围】

对于 $10\%$ 的数据，$1 \le n \le 10 , 1 \le k_i,m_i,s_i,y_{i,j} \le 100 , 1 \le t \le 100$。

对于另外 $40\%$ 的数据，$1 \le n \le 100 , 1 \le k_i,m_i,s_i,y_{i,j} \le 100 , 1 \le t \le 10^4$。

对于 $100\%$ 的数据，$1 \le n \le 200 , 1 \le k_i,m_i,s_i,y_{i,j} \le 500,1 \le t \le 10^5,1\le c_i\le k_i$。

---

【说明/提示】

- 尝试理解样例

---

【文件读入读出】**（模拟，提交代码时不需使用）**

- 文件名：`play.cpp`
- 读入文件名：`play.in`
- 读出文件名：`play.out`

## 样例 #1

### 输入

```
2 20
9 1 4 2
3 2 4 1
11 2 4 3
2 3 2 2```

### 输出

```
48```

## 样例 #2

### 输入

```
3 20
9 2 1 1
10000
1 4 1 1
1
1 4 1 1
2```

### 输出

```
20003```

# 题解

## 作者：dead_X (赞：2)

## 前言
我是屑我是屑我是屑

我连多重背包01拆分都能写错

啊啊啊啊啊啊啊啊啊啊啊啊啊
## 思路
二合一题。

* 任务 $1$：计算一关的最大分数

一个很显然的 $dp$，我用了记忆化搜索实现。显然对于一个区间 $[l,r]$，**最后选的数**只能是 $a_l$ 或者 $a_r$，而最后选的数会创造 $r-l+1$ 的贡献。因此得到一个很显然的柿子：

$$dp_{i,j}=\max\{dp_{i+1,j}+a_i\times(j-i+1),dp_{i,j-1}+a_j\times (j-i+1)\}$$

* 任务 $2$：计算总分最大值

显然直接二进制分组多重背包即可。

一个小坑：这里的多重背包需要**将前面所有的都选至少一次**，所以 dp 的时候要先强制选一次，再自由选。

* 来讲一下我犯的 nt 错误：

* 大家都知道完全背包应该是 

```
for(int i=1; i<=mx; mx-=i,i<<=1) 做一次i个物品的完全背包;
做一次mx个物品的完全背包;
```

* 然后我写了个

```
for(int i=1; i<=mx; i<<=1) if(i&mx) 做一次i个物品的完全背包;
```

* 一定要记住二进制拆分的原理啊/kel
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int c,mx,m,sdt,a[503];
long long dp[503][503];
long long ans[100003][2],Ans=0;
long long dfs(int l,int r)
{
	if(l==sdt&&r==sdt) return a[sdt];
	if(dp[l][r]) return dp[l][r];
	if(l==sdt) return dp[l][r]=dfs(l,r-1)+a[r]*(r-l+1);
	if(r==sdt) return dp[l][r]=dfs(l+1,r)+a[l]*(r-l+1);
	return dp[l][r]=max(dfs(l,r-1)+a[r]*(r-l+1),dfs(l+1,r)+a[l]*(r-l+1));
}
signed main()
{
	int n=read(),t=read(),sum=0;
	for(int i=1; i<=n; i++)
	{
		c=read(),mx=read()-1,m=read(),sdt=read(),sum+=c;
		for(int j=1; j<=m; j++) a[j]=read();
		memset(dp,0,sizeof(dp));
		long long DP=dfs(1,m);
		//printf("> %lld\n",dp[1][m]);
		for(int j=0; j<min(sum,t+1); j++) ans[j][i&1]=-1000000000000000ll;
		for(int j=t; j>=sum; j--) ans[j][i&1]=ans[j-c][(i&1)^1]+DP;
		for(int j=1; j<=mx; mx-=j,j<<=1)
		{
			long long g=DP*j;
			int h=j*c;
			for(int k=t; k>=h; k--) ans[k][i&1]=max(ans[k][i&1],ans[k-h][i&1]+g);
		} 
		long long g=DP*mx;
		int h=mx*c;
		for(int k=t; k>=h; k--) ans[k][i&1]=max(ans[k][i&1],ans[k-h][i&1]+g); 
		for(int j=1; j<=t; j++) Ans=max(Ans,ans[j][i&1]);
	}
	printf("%lld\n",Ans);
	return 0;
}
```

---

