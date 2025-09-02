# [POI 2020/2021 R1] Gang Biciaków / 布茨帮

## 题目背景

**题目译自 [XXVIII Olimpiada Informatyczna – I etap](https://sio2.mimuw.edu.pl/c/oi28-1/dashboard/) [Gang Biciaków](https://sio2.mimuw.edu.pl/c/oi28-1/p/gan/)。**

## 题目描述

Bajtazar 在一家货运公司工作，他目前的工作是将建筑材料从 Bajtocji 的首都运输到附近城镇的商店。在 Bajtocji，有 $n$ 座城市（编号从 $1$ 到 $n$），这些城市通过 $n-1$ 条道路相互连接。每条道路上都有一个加油站。

Bajtazar 一天的工作是这样的：他从首都（编号为 $1$ 的城市）出发，沿着最短路径到达城市 $x$，再原路返回。

Bajtazara 的儿子 Bitek 非常喜欢加油站里卖的玩具狗。玩具狗一共有 $m$ 种（编号从 $1$ 到 $m$），但每个加油站只提供一种玩具狗，因此收集玩具狗并非一件轻松的事情。

现在给出 Bajtazara 每天前往的目的地，他想要知道他的儿子这天能够获得多少种玩具狗。麻烦的是，每个加油站里售卖的玩具狗的种类会发生变化，你能帮助他解决这个难题吗？


## 说明/提示

【样例解释1】：

![pp5XLWV.png](https://s1.ax1x.com/2023/04/05/pp5XLWV.png)

注意该样例中存在一次修改操作，使得第二条道路上的加油站售卖的玩具狗的种类从 $2$ 变成了 $1$。

【数据范围】：

所有测试点均满足：$2 \leq n \leq 10^5$，$1 \leq m,z \leq 1.5 \times 10^5$，且至少存在一个 $\texttt{Z}$ 操作。

| 子任务编号 | 约束| 分值|
|:-:|:-:| :-: |
| $1$| $n,m,z \leq 100$| $7$  |
| $2$| $n,z \leq 2 \times 10^3$| $9$  |
|$3$ | 只有 $\texttt{Z}$ 类型操作| $9 $  |
| $4$| $m \leq 15$|$15$|
|$5$|道路 $i$ 连接城市 $i$ 和城市 $i+1$| $11$ |
| $6$ | 刚开始时，每个加油站售卖的玩具狗类型都是 $1$，在后续的 $\texttt{B}$ 类型操作中，玩具狗的类型会被更改为除 $1$ 之外的任意类型 | $13$ |
| $7$| 无附加约束| $36$ |

## 样例 #1

### 输入

```
6 3 5
1 2 3
1 3 2
3 4 3
5 3 1
6 4 2
Z 5
Z 6
B 2 1
Z 5
Z 6```

### 输出

```
2
2
1
3```

## 样例 #2

### 输入

```
8 4 20
1 2 3
8 2 4
6 4 2
1 6 1
3 4 3
4 5 2
7 4 1
Z 2
Z 3
Z 4
Z 5
Z 6
Z 7
Z 8
B 4 4
B 3 3
B 7 4
B 2 3
Z 2
Z 3
Z 4
Z 5
Z 6
Z 7
Z 8
B 3 4
Z 7```

### 输出

```
1
3
2
2
1
2
2
1
2
2
3
1
2
1
1```

# 题解

## 作者：dream10 (赞：1)

简单做个贡献，笔者写的时候洛谷上只有一篇题解。直接进入主题。

### 根号分治

受到 $m$ 较小和一条链性质的启发，发现一个颜色次数多可以直接开数据结构统计，次数少可以找到关键点，于是根号分治。

具体地，对于一个出现次数比较少的颜色，如果一个点被在另外一个点的子树里就去掉它，然后这些就是关键点，用数据结构维护；出现次数较多的点，就单独开数据结构维护。询问就遍历这些数据结构。

至于优化，就是可以询问离线，找到有潜力变大的颜色，就不用动态分配多少颜色了。

还有就是询问和修改的次数不等，可以值域分块。

还是过不去，但是有意义。$O(n\sqrt{n}\log n)$

https://www.luogu.com.cn/record/220532398


### 带修莫队

阅读理解。

两个信息，dfs 序列右端点，和时间，莫队即可，是一个根号。$O(n\sqrt{n})$

https://github.com/mrugacz95/oi28/blob/master/gan/gan.cpp

### 根号重构

重构完进行dfs，遇到询问把可以造成影响的造成影响。$O(n\sqrt{n})$

https://www.luogu.com/article/xt3aitra

---

## 作者：zzzyyyyhhhhh (赞：1)

感觉此解法不是正解，需要大力卡常才能通过。

树上数颜色想到树分块（设置关键点的那种）。维护到每个关键点每种颜色的出现次数和根到每个关键点的颜色数，查询时暴力向上跳到最近的一个关键点，用关键点的颜色数加上路径上未在根到关键点路径上出现过的颜色数，修改时修改影响到的关键点的颜色数和颜色种类即可。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5+100,M = 1.5e5+1;
namespace  rorrurorror
{
	const int MAXBUF=1<<20;
	char buf[MAXBUF],*p1=buf,*p2=buf;
	char pbuf[MAXBUF],*pp=pbuf;
	inline char getc(){return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,MAXBUF,stdin),p1==p2)?EOF:*p1++;}
	inline void ri(int &x){x=0;char c=getc();while(!isdigit(c))c=getc();while(isdigit(c))x=x*10+(c^48),c=getc();}
	inline void putc(char c){(pp==pbuf+MAXBUF)&&(fwrite(pbuf,1,MAXBUF,stdout),pp=pbuf),*pp++=c;}
	inline void print_final(){fwrite(pbuf,1,pp-pbuf,stdout),pp=pbuf;}
	inline void wi(int x){if(x>9)wi(x/10);putc(x%10^48);}
}
using rorrurorror::ri;
using rorrurorror::wi;
using rorrurorror::getc;
using rorrurorror::putc;
using rorrurorror::print_final;
struct edge{int t,w,pos;};
vector<edge> a[N];
int n,m,qq;
bool key[N],tt[M];
int cnttmp[M],dep[N],mxdep[N],f[N];
int blo,cnt[300][M],ans[N],tot,be[N],rb[N],bg[N],ke[N],ed[N],to[N];
int tmp[N];
inline void dfs0(int x,int fa)
{
	mxdep[x]=dep[x];
	edge i;
	for(int j=0;j<a[x].size();j++)
	{
		i=a[x][j];
		if(i.t==fa)continue;
		f[i.t]=x;
		to[i.t]=i.w;
		ke[i.pos]=i.t;
		dep[i.t]=dep[x]+1;
		dfs0(i.t,x);
		mxdep[x]=max(mxdep[x],mxdep[i.t]);
	}
	if(dep[x]%blo==0&&mxdep[x]-dep[x]>=blo)key[x]=1;
}
inline void dfs(int x,int fa)
{
	bg[x]=tot+1;
	if(key[x])memcpy(cnt[be[x]=++tot],cnttmp,sizeof(int)*(m+1)),rb[tot]=x;
	edge i;
	for(int j=0;j<a[x].size();j++)
	{
		i=a[x][j];
		if(i.t==fa)continue;
		cnttmp[i.w]++;
		ans[i.t]=ans[x];
		if(cnttmp[i.w]==1)ans[i.t]++;
		dfs(i.t,x);
		cnttmp[i.w]--;
	}
	ed[x]=tot;
}
inline int get(int x)
{
	tot=0;
	while(!key[x])
	{
		if(!tt[to[x]])tmp[++tot]=to[x],tt[to[x]]=1;
		x=f[x];
	}
	int res=ans[x];
	for(int i=1;i<=tot;i++)
	{
		if(!cnt[be[x]][tmp[i]])res++;
		tt[tmp[i]]=0;
	}
	return res;
}
inline void ea(int x,int tp)
{
	for(int i=bg[x];i<=ed[x];i++)
	{
		cnt[i][tp]--;
		if(!cnt[i][tp])ans[rb[i]]--;
	}
}
inline void ad(int x,int tp)
{
	for(int i=bg[x];i<=ed[x];i++)
	{
		cnt[i][tp]++;
		if(cnt[i][tp]==1)ans[rb[i]]++;
	}
}
signed main()
{
	ri(n),ri(m),ri(qq);
	blo=sqrt(n)*1.21+1;
	int x,y,z;
	char op;
	for(int i=1;i<n;i++)ri(x),ri(y),ri(z),a[x].push_back({y,z,i}),a[y].push_back({x,z,i});
	dfs0(1,0);
	key[1]=1;
	dfs(1,0);
	while(qq--)
	{
		op=getc();
		while(op!='Z'&&op!='B')op=getc();
		if(op=='Z')
		{
			ri(x);
			get(x);
			wi(get(x)),putc('\n');
		}
		else
		{
			ri(x),ri(y);
			if(y==to[ke[x]])continue;
			ea(ke[x],to[ke[x]]);
			to[ke[x]]=y;
			ad(ke[x],to[ke[x]]);
		}
	}
	print_final();
}
```

---

