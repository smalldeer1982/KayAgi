# Monsters and Potions

## 题目描述

有 $n$ 个位置排成一排，每个位置上有一个数 $a_i$。有 $m$ 个英雄，分布在所有数为 $0$ 的位置上，每个英雄有一个生命值。每个位置至多有一个英雄，但有可能没有英雄。

你需要选定一个位置作为集合点。并依次指定每个英雄（自己决定顺序）直接走到集合点。当一个英雄走入一个位置 $i$ 时，他的生命值会加上 $a_i$，并把这个位置上的数变为 $0$。特别的，生命值不能为负数（可以为 $0$）。

你需要找到一种方法，使得所有英雄都能够到达集合点。

## 样例 #1

### 输入

```
8 3
8 2
1 3
4 9
0 3 -5 0 -5 -4 -1 0
```

### 输出

```
6
3 1 2 ```

## 样例 #2

### 输入

```
1 1
1 1
0
```

### 输出

```
1
1 ```

## 样例 #3

### 输入

```
3 2
1 1
3 1
0 -5000 0
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
8 3
1 15
5 10
8 1
0 -5 -5 -5 0 -5 -5 0
```

### 输出

```
7
2 1 3 ```

# 题解

## 作者：Sword_K (赞：3)

默认英雄按位置排好序。

首先想到枚举集合点，然后考虑如何安排英雄的顺序。因为左右两边除了第一步谁先走以外相对独立，所以就只考虑一边。如果离集合点从近到远考虑英雄，那么能走就走是最优的策略。因为他既然能走，那何必让之后的英雄来冒这个风险呢？即留给了后面的英雄更大的机会走到集合点。于是朴素地枚举集合点，枚举英雄，模拟移动情况，复杂度 $O(n^3)$ 便足以通过此题。

但显然可以优化。可以发现模拟每个英雄的移动情况是重复计算的。而且可以发现每个英雄实际要“经历”的，是一段以他所在位置为起点，一段连续的区间。原问题可以转化成每个英雄代表一段极长的区间，问这些区间是否可以完整的覆盖第一个英雄到最后一个英雄。那么模拟预处理每个英雄的区间，可以做到 $O(n^2)$。

写完通过后，发现其实可以 $O(n)$。复杂度的瓶颈在于每个英雄都要预处理，于是考虑是否可以不处理完呢？答案是肯定的的。考虑把英雄走的过程转化成这样：第一个英雄开始往右边走，走到第二个英雄的地方，如果他现在的血量比第二个英雄大，就继续走，否则就让第二个英雄走，直到血量为 $0$。同时，最后一个英雄以类似的方式往左边走。稍微思考一下可以发现，这种移动方式是等价的，换英雄的过程其实就对应了让换上来的英雄先走。这样，就可以做到 $O(n)$。

---

## 作者：MattiaBinotto (赞：0)

## 思路

因为 $n$ 很小，考虑暴力枚举每个集合点，然后两侧显然是独立的，下文只考虑硬性在集合点右边的情况。

我们发现题面里有个很重要的话：**选择英雄后，英雄会一直走直到集合点**。

这样的话，设从左到右第 $x$ 个英雄被选择时，之前选择英雄的最大编号是 $y$，则 $x$ 就要走 $[y,x]$ 这段路上的所有怪物和药水。

所以我们可以直接设计一个 dp：我们直接从前到后枚举一个新英雄，这个新英雄走了上一个枚举英雄到这个英雄的所有路，而没有枚举到的英雄最后可以直接走回去。

这样的复杂度是 $O(n^2)$ 的，因此总复杂度为 $O(n^3)$，可以通过。

实现中涉及到英雄位置和中点分界线有一些小细节。

## 代码

```cpp
// Problem: G. Monsters and Potions
// Contest: Codeforces - 2018-2019 ICPC, NEERC, Southern Subregional Contest (Online Mirror, ACM-ICPC Rules, Teams Preferred)
// URL: https://codeforces.com/contest/1070/problem/G
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
//And in that light,I find deliverance.
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
bool vis[103];
int nxt[103];
int h[103],a[103];
bool f[103];
int id[103];
void dfs(int x)
{
	if(x==-1) return ;
	dfs(nxt[x]);
	printf("%d ",id[x]),vis[x]=0;
	return ;
}
signed main()
{
	int n=read(),m=read();
	int fir=n+1,lst=0,ava=0;
	for(int i=1; i<=m; ++i)
	{
		int x=read();
		vis[x]=1,h[x]=read(),id[x]=++ava;
		if(x<fir) fir=x;
		if(x>lst) lst=x;
	}
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=1; i<=n+1; ++i) 
	{
		memset(f,0,sizeof(f));
		bool f1=0,f2=0;
		for(int j=i-1; j>=1; --j) if(vis[j])
		for(int k=j,cur=h[j]; k<=i-1; ++k)
		{
			cur+=a[k];
			if(cur<0) break;
			if(k==i-1) {f[j]=1,nxt[j]=-1;break;}
			else if(f[k]) {f[j]=1,nxt[j]=k;break;}
		}
		for(int j=i; j<=n; ++j) if(vis[j])
		for(int k=j,cur=h[j]; k>=i; --k)
		{
			cur+=a[k];
			if(cur<0) break;
			if(k==i) {f[j]=1,nxt[j]=-1;break;}
			else if(f[k]) {f[j]=1,nxt[j]=k;break;}
		}
		if(fir<i) f1=f[fir]; else f1=1;
		if(lst>=i) f2=f[lst]; else f2=1;
		if(f1&&f2)
		{
			printf("%d\n",min(n,i));
			if(lst>=i) dfs(lst);
			if(fir<i) dfs(fir);
			for(int i=1; i<=n; ++i) if(vis[i]) printf("%d ",id[i]);
			puts("");
			return 0;
		}
	}
	puts("-1");
	return 0;
}
```

---

