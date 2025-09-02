# [COTS 2024] 双双决斗 Dvoboj

## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D1T1。$\texttt{2s,1G}$。

> Two pharaonic yellow lines turned into an eye...

## 题目描述

Jusuf 手里有 $N$ 张卡牌，从左到右编号为 $1$ 到 $N$。每张卡牌的力量为 $p_i$。由于 Jusuf 即将参加比赛，他想要在脑中想象战斗。有时候，他也会更改卡牌的力量值。Jusuf 总共会做 $Q$ 次操作，每个操作属于以下两种类型之一：

1. `1 i r`：Jusuf 将位于位置 $i$ 的卡牌的力量设为 $r$，即 $p_i\gets r$。

2. `2 l k`：Jusuf 在脑中想象一场战斗。这场战斗使用从第 $l,l+1,\cdots,l + 2^k − 1$ 张，共 $2^k$ 张卡牌。

    战斗将会进行 $k$ 轮。每轮中，Jusuf 将第 $(2i-1)$ 和第 $2i$ 张卡牌分成一组（例如第 $1$ 张和第 $2$ 张卡牌为一组）。
    
    对于每组卡牌，Jusuf 比较它们的力量。不妨设两张卡牌的力量分别为 $A$ 和 $B$，力量更大的卡牌将获胜，且获胜卡牌的力量变为 $|A − B|$，另一张卡牌被移除。特别地，如果 $A=B$，则这场战斗的结果无法确定，将会随机一张卡牌获胜，力量变为 $0$。
    
    注意到，在 $k$ 轮后，只会剩下一张卡牌，Jusuf 想要知道此时它的力量大小。

由于 Jusuf 只是在脑中想象战斗，所以实际上牌的数量不会改变，$p_i$ 也不会改变。


## 说明/提示


#### 样例解释

对于样例 $1$ 的第一个询问，有：

$$(\bold{\textcolor{red}{4}},8,\bold{\textcolor{red}{2}},0)\to (\bold{\textcolor{red}{4}},2)\to(2)$$

对于样例 $1$ 的第二个询问，有：

$$ (\bold{\textcolor{red}{8}},2)\to(6)$$

#### 数据范围

对于 $100\%$ 的数据，保证：

- $2\le N\le 200\, 000$，$1\le Q\le 200\, 000$；
- $0\le p_i\le 10^9$；
- $1\le i\le N$，$0\le r\le 10^9$；
- $1\le l\le N$，$1\le l+{2^k}-1\le N$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$   | $11$    | $N, Q \leq 1000$ |
| $2$    | $13$    | $N=2^k$ |
| $3$    | $16$    | $0\le p_i,r\le 1$ |
| $4$    | $17$    | 不含修改操作 |
| $5$    | $43$    | 无额外约束 |



## 样例 #1

### 输入

```
5 3
4 8 2 0 7
2 1 2
1 1 9
2 2 1```

### 输出

```
2
6```

## 样例 #2

### 输入

```
8 6
1 2 3 4 5 6 7 8
2 1 3
1 4 1
1 7 3
2 1 3
1 2 100
2 2 2```

### 输出

```
0
3
93```

## 样例 #3

### 输入

```
9 5
1 0 2 0 4 1 3 2 8
2 2 3
2 1 3
1 5 1
1 6 4
2 4 2```

### 输出

```
2
1
0```

# 题解

## 作者：xu_zhihao (赞：5)

#### 前言

- 只能说这题太模板了。

### 题目描述

- 什么？ $2^k$ 区间问题？那绝对得用 ST 表了。但很烦人的是这里有一个单点修改操作，若朴素 ST 表 $O(1)$ 查询，$O(n \log n)$ 修改，这复杂度是绝对过不了的。考虑均摊复杂度。

- 均摊复杂度可以使用根号分治。只用维护 $2^k\le \sqrt{N}$。区间查询使用递归求出未求部分，复杂度为 $O(\sqrt{N})$；单点修改复杂度为 $O(\sqrt{N})$。复杂度变为 $O(Q \sqrt{N})$。

**upd** 复杂度若有误请与我联系。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int st[200010][25];
int p[200010];
int s,t;
void Init(){
	for(int i=1;i<=n;i++){
		st[i][0]=p[i];
	}
	for(int j=1;j<=t;j++){
		for(int i=1;i<=n;i++)if(i+(1<<j)-1<=n){
			st[i][j]=abs(st[i][j-1]-st[i+(1<<(j-1))][j-1]);
		}
	}
	return;
}
int check(int l,int k){
	if(k<=t){
		return st[l][k];
	}
	int ans=abs(check(l,k-1)-check(l+(1<<(k-1)),k-1));
	return ans;
}
int Find(int l,int k){
	if(k<=t){
		int ans=st[l][k];
		return ans;
	}
	int ans=check(l,k);
	return ans;
}
void Work(int id,int r){
	st[id][0]=r;
	for(int j=1;j<=t;j++){
		int w=max(id-(1<<j)+1,1);
		for(int i=w;i<=id;i++)if(i+(1<<j)-1<=n){
			st[i][j]=abs(st[i][j-1]-st[i+(1<<(j-1))][j-1]);
		}
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
	}
	s=sqrt(n);
    t=log2(s);
	Init();
	while(q--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int i,r;
			scanf("%d%d",&i,&r);
			Work(i,r);
		}
		else{
			int l,k;
			scanf("%d%d",&l,&k);
			int ans=Find(l,k);
			printf("%d\n",ans);
		}
	}
	return 0;
} 
```

---

## 作者：oMin0 (赞：5)

这种东西为什么就紫了，建议降蓝。

## 分析

考虑不带修怎么做，发现可以直接倍增，维护每个 $[i,i+2^k-1]$ 区间的答案，记作 $f_{k,i}$。

那么本题要支持单点修，暴力套用上述做法后单点修对每个 $k$ 会影响到 $[u-2^k+1,u]$ 这段区间的 $f_{k,\_}$，即单次修改 $O(\sum\limits_{2^i\leq n} 2^i)=O(n)$，单次查询 $O(1)$。这显然不能接受，于是我们可以根分，只维护 $2^k\leq \sqrt n$ 的 $f_{k,i}$，查询时对 $len/\sqrt n$ 个数跑暴力，总复杂度变为 $O(q\sqrt n)$，可以通过本题。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;

int n,q,p[200005],op,u,v;
int sy[11][200005];
int nr[200005];

signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) sy[0][i]=p[i];
	for(int i=1;i<=9;i++) for(int j=1;j+(1<<i)-1<=n;j++) sy[i][j]=abs(sy[i-1][j]-sy[i-1][j+(1<<i-1)]);
	while(q--)
	{
		cin>>op>>u>>v;
		if(op==1)
		{
			p[u]=v; sy[0][u]=v;
			for(int i=1;i<=9;i++)
			{
				for(int j=max(1,u-(1<<i)+1);j<=u&&j+(1<<i)-1<=n;j++) sy[i][j]=abs(sy[i-1][j]-sy[i-1][j+(1<<i-1)]);
			}
		}
		else
		{
			if(v<=9) cout<<sy[v][u]<<endl;
			else
			{
				v-=9;
				for(int i=0;i<(1<<v);i++) nr[i]=sy[9][u+i*512];
				while(v) 
				{
					for(int i=0;i<(1<<v-1);i++) nr[i]=abs(nr[i*2]-nr[i*2+1]); v--;
				}
				cout<<nr[0]<<endl;
			}
		}
	}
}
```

---

## 作者：苏联小渣 (赞：4)

考虑不带修的思路，题目已经告诉你倍增了，设 $f_{i,j}$ 表示询问为 $(i,j)$ 的答案，显然有 $f_{i,j}=|f_{i,j-1}-f_{i+2^j-1,j-1}|$。

考虑修改，如果直接修改需要重构所有倍增数组，无法接受。所以我们可以考虑平衡复杂度，对于 $j \le B$ 的部分暴力重构，对于 $j > B$ 的部分在询问的时候查询。

对于暴力重构，只需要考虑 $[x,x-2^B+1]$ 这个区间，时间复杂度 $O(qB2^B)$。

对于查询，假设我们要查询 $f_{x,j}$，那么可以递归下去到 $f_{x,j-1}$ 和 $f_{x+2^j-1,j-1}$，如果 $j \le B$ 则可以直接给出答案。递归总次数是 $1+2+4+...+2^{j-B}$ 次，时间复杂度 $O(q2^{\log n-B})$。

取 $B=8$ 可以通过。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, q, op, x, y, a[200010];
ll f[200010][18];
ll dfs(int x, int y){
    if (y <= 8) return f[x][y];
    return abs(dfs(x, y-1) - dfs(x+(1<<y-1), y-1));
}
int main(){
    scanf ("%d%d", &n, &q);
    for (int i=1; i<=n; i++){
        scanf ("%d", &a[i]);
        f[i][0] = a[i];
    }
    for (int j=1; j<=17; j++){
        for (int i=1; i+(1<<j)-1<=n; i++){
            f[i][j] = abs(f[i][j-1] - f[i+(1<<j-1)][j-1]);
        }
    }
    for (int i=1; i<=q; i++){
        scanf ("%d%d%d", &op, &x, &y);
        if (op == 1){
            a[x] = f[x][0] = y;
            for (int j=1; j<=8; j++){
                for (int k=max(x-256, 1); k+(1<<j)-1<=n && k<=x; k++){
                    f[k][j] = abs(f[k][j-1] - f[k+(1<<j-1)][j-1]);
                }
            }
        }
        else{
            printf ("%lld\n", dfs(x, y));
        }
    }
    return 0;
}
```

---

## 作者：Arc0_FishyFool (赞：2)

这是我打校内模拟赛时见到的一道模板但是不错的 ST 表 + 根号分治题。（赞赏\
遗憾的是没能场切，可能是思维僵化不会根分导致的。（大悲

# 引入：从子任务看起：

## 子任务 1：

观察子任务 $1$，我们注意到 $N,Q\le 1000$，显然可以每次直接更改 $p_i$ 的值并暴力求解，总复杂度约 $O(NQ)$。\
暴力代码片段：

```cpp
for(int i=1;i<=q;++i){
	if(opt[i]&1){
		p[x[i]]=k[i];
	}
	else{
		int beg=x[i],nd=x[i]+(1<<k[i])-1;
		for(int j=beg;j<=nd;++j) que.push(p[j]);
		while(!que.empty()){
			int u=que.front();
			que.pop();
			if(que.empty()){
				cout<<u<<endl;
				break;
			}
			int v=que.front();
			que.pop();
			que.push(abs(u-v));
		}
	}
}
```

## 子任务 4：

我们注意到查询操作正好只与从 $l$ 开始的 $2^k$ 个元素相关，在没有修改的情况下，“不支持修改” 的 ST 表正好能大显神通，这启示我们用 ST 表预处理出所有情况的结果，**由于 ST 表预处理复杂度为** $O(N\log_2 N)$ **而查询复杂度仅** $O(1)$，对于子任务 $4$，此算法的复杂度为 $O(N\log_2 N+Q)$。\
无修改子任务代码片段：

```cpp
for(int i=0;i<=19;++i){
	for(int j=n+1-(1<<i);j>0;--j){
		if(!i) st[j][i]=p[j];
		else{
			int k=j+(1<<(i-1));
			st[j][i]=abs(st[j][i-1]-st[k][i-1]);
		}
	}
}
for(int i=1;i<=q;++i){
	cout<<st[x[i]][k[i]]<<endl;
}
```

# 重点：如何优化：

出于查询任务的特殊性，我暂且武断地认为，线段树维护是不现实的，ST 表仍然是目前的最优算法。\
然而，**ST 表本身修改是不优的**，单论修改序列中一个节点就会牵一发动全身，尤其是次数下标大的元素，因为涵盖范围广，基本上都会受到影响。\
我们先讨论 ST 表单点修改的时间复杂度具体是多少。\
单点修改第 $x$ 项元素，则对于每一个 $k$，维护区间 $[x,x+2^k-1]$ 和其他同长度、涵盖第 $x$ 项的 ST 表节点都会受影响，设 $T(x)$ 为 ST 表修改原序列第 $x$ 项的时间复杂度，我们可以粗略列出以下算式：  
$$T(x)=\sum_{k=0}^{\lfloor\log_2 N\rfloor}\min(2^k,N-2^k+1)\le\sum_{k=0}^{\lfloor\log_2 N\rfloor}2^k=2^{\lfloor\log_2 N\rfloor+1}-1 < 2N$$  
因此，ST 表单点修改的时间复杂度约为 $O(N)$。\
那么，我们现在发现当前算法的缺点在于修改的总复杂度为 $O(QN)$，怎么优化呢？\
其实只需要结合子任务 $1$、$4$ 的做法就好了。\
我们注意到，查询的复杂度仅为 $O(1)$，而且 ST 表的离线递推和支持在线的暴力模拟忽略复杂度区别是等效的：**我们能用预处理过的** $2^k$ **个 ST 表元素进行倍增算出答案，也能把他们直接用来暴力模拟求解答案，并不要求这些元素都是 ST 表中最底层的元素！**\
**因此，我们考虑牺牲部分查询复杂度换来更快的修改**。比如，把 ST 表的高楼拆了：减小 ST 表的静态维护范围，方便修改。同时，请暴力模拟算法“吃预制菜”：对于超出 ST 表维护范围的询问，将缩小过的 ST 表的顶层元素加入模拟算法求解。\
**仔细观察上文复杂度的算式，我们发现 ST 表修改本质上只和维护的最大指数相关**，假如我们修改的复杂度约为 $O(m)$，那么 ST 表顶层每个元素维护的区间长度约为 $m$，查询时就会有约 $\frac{N}{m}$ 个元素参与，即查询复杂度约为 $O(\frac{N}{m})$。\
因此，我们为均摊复杂度，将 $m$ 的值设在 $\sqrt N$ 左右，即用 ST 表维护长度不超过 $\sqrt N$ 的区间答案，然后用暴力模拟回答未预处理的询问，此时修改与查询的最坏复杂度都为 $O(\sqrt N)$，总复杂度大概 $O(N\log_2{\sqrt N}+Q\sqrt N)$，足以通过此题！

# ACcode：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,p[229028],st[229028][15],opt,x,k;
queue<int> que;
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		cin>>p[i];
		st[i][0]=p[i];
	}
	for(int i=1;i<12;++i){
		for(int j=1;j+(1<<i)-1<=n;++j) st[j][i]=abs(st[j][i-1]-st[j+(1<<(i-1))][i-1]);	
	}
	while(q--){
		cin>>opt>>x>>k;
		if(opt&1){
			p[x]=k;
			st[x][0]=k;
			for(int i=1;i<12;++i){
				for(int j=max(1,x-(1<<i)+1);j<=x&&j+(1<<i)-1<=n;++j) st[j][i]=abs(st[j][i-1]-st[j+(1<<(i-1))][i-1]);
			}
		}
		else{
			if(k<12){
				cout<<st[x][k]<<endl;
				continue;
			}
			k-=11;
			for(int i=0;i<(1<<k);++i) que.push(st[x+i*2048][11]);
			while(!que.empty()){
				int u=que.front();
				que.pop();
				if(que.empty()){
					cout<<u<<endl;
					break;
				}
				int v=que.front();
				que.pop();
				que.push(abs(u-v));
			}
		}
	}
	return 0;
}
```

---

## 作者：TH911 (赞：2)

> [题目传送门](https://www.luogu.com.cn/problem/P10680)

# 题意分析

首先注意到一个非常特殊的性质，区间查询形如 $\left[l,l+2^k-1\right]$，长度为 $2^k$。

其次，单点修改很简单，区间查询较为复杂。

所以，考虑使用相关数据结构和算法维护。

考虑 ST 表，这可以很好的维护长度为 $2^k$ 的区间信息。记 $\left[l,l+2^k-1\right]$ 的答案为 $\textit{st}_{l,k}$。在操作之前，使用普通 ST 表 $\mathcal O(n\log n)$ 预处理。

但是，ST 表是静态的，单点修改后重构的复杂度为 $\mathcal O(n)$。（并非 $\mathcal O(n\log n)$，设修改 $x$，则**信息包含 $x$ 的点的区间** $[x-2^i+1,x]$ 需要满足 $i\leq\log n$，数量即 $\mathcal O(1+2+4+\cdots+n)=\mathcal O(n)$。）

因此，考虑复杂度均摊，考虑分治。设块长 $2^B$，并进行**阈值分治**。

单点修改重构后，处理 $\textit{st}_{x,k}$ 时，我们仅处理 $k\leq B$ 的情况，复杂度 $\mathcal O\left(2^B\right)$。

查询时，设 $\textit{query}(x,k)$ 表示答案。

* 若 $\textit{query}(x,k)$ 满足 $k\leq B$，则直接查询 $\textit{st}_{x,k}$。

* 否则有：

  $$
  \textit{query}(x,k)=\vert\textit{query}(x,k-1)-\textit{query}(x+2^{k-1},k-1)\vert
  $$

  这样的复杂度是 $\mathcal O\left(\dfrac{n}{2^B}\right)$。

  因为考虑到会递归 $k-B$ 层，即 $\mathcal O(\log n-B)$ 层。每一层都是双分支，复杂度即 $\mathcal O\left(2^{\log n-B}\right)=\mathcal O\left(\dfrac n{2^B}\right)$。

取 $B=\mathcal O\left(\dfrac{1}{2}\log n\right)$，可得最优复杂度。总复杂度为 $\mathcal O\left(n\log n+q\sqrt n\right)$。

# AC 代码

```cpp
//#include<bits/stdc++.h>
#include<algorithm> 
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
typedef long long ll;
constexpr const int N=200000;
int n,a[N+1],st[N+1][__lg(N+1)+1];
int B;
void stPre(){
	for(int i=1;i<=n;i++){
		st[i][0]=a[i];
	}
	for(int i=1;(1<<i)<=n;i++){
		for(int x=1;x+(1<<i)-1<=n;x++){
			st[x][i]=abs(st[x][i-1]-st[x+(1<<i-1)][i-1]);
		}
	}
}
void change(int p,int r){
	st[p][0]=a[p]=r;
	for(int i=1;i<=B;i++){
		for(int x=max(p-(1<<i)+1,1);x<=p&&x+(1<<i)-1<=n;x++){
			st[x][i]=abs(st[x][i-1]-st[x+(1<<i-1)][i-1]);
		}
	}
}
int query(int l,int k){
	if(k<=B){
		return st[l][k];
	}else{
		return abs(query(l,k-1)-query(l+(1<<k-1),k-1));
	}
}
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	int q;
	cin>>n>>q;
	B=__lg(n)>>1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	stPre();
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		switch(op){
			case 1:
				change(x,y);
				break;
			case 2:
				cout<<query(x,y)<<'\n';
				break;
		}
	}
	
	cout.flush();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：jiangxinyang2012 (赞：1)

因为是选取 $2^k$ 张牌进行决斗，所以考虑 ST 表。

我们设 $f_{i,k}$ 表示的是从第 $i$ 张牌开始，连续 $2^k$ 张牌进行决斗，最终剩下的那张牌的力量大小。显然转移就是 $f_{i,k} = |f_{i,k-1}-f_{i+2^{k-1},k-1}|$。

但是发现修改时完全重构 st 表不太现实，所以考虑根号分治。设一个 $p = 10$，假设要修改的位置是 $x$，我们每次只修改 $k \le p$ 且 $i \le x \le i+2^k-1$ 的 $f_{i,k}$，剩下的先不管。

查询的时候，如果 $k \le p$，答案就是 $f_{i,k}$。否则，我们直接暴力搜索直到剩下的人小于等于 $2^p$ 时，返回 $f_{i,k}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 200005;
const int INF = 0x3f3f3f3f;
int a[N];
int f[N][20];
int p;
int cal(int x, int y) {
    if (y <= p) return f[x][y];
    return abs(cal(x, y - 1) - cal(x + (1 << (y - 1)), y - 1));
}
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int len = 1; 1 << len <= n; len++) {
        for (int i = 1; i + (1 << len) - 1 <= n; i++) {
            f[i][len] = abs(f[i][len - 1] - f[i + (1 << (len - 1))][len - 1]);
        }
    }
    p = 10;
    while (q--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            f[l][0] = r;
            a[l] = r;
            for (int len = 1; len <= p; len++) {
                for (int i = max(l - (1 << len) + 1, 1); i <= l && i + (1 << len) - 1 <= n; i++) {
                    f[i][len] = abs(f[i][len - 1] - f[i + (1 << (len - 1))][len - 1]);
                }
            }
        } else {
            if (r <= p) {
                printf("%d\n", f[l][r]);
            } else {
                printf("%d\n", cal(l, r));
            }
        }
    }
    return 0;
}

```

---

## 作者：HasNoName (赞：0)

### 思路
不难发现这是一道根号分治题。

考虑 `ST` 表。

但是 `ST` 表不支持修改操作，但可以很快的处理查询操作。

所以可以把修改和查询的复杂度均摊。

考虑到单点修改只会影响到线性的区间。

可以对于其中的 $\sqrt n$ 个区间暴力修改，剩下的 $\sqrt n$ 个区间等查询的时候在用时间去寻找。

复杂度是 $O(n\sqrt n)$ 的。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,L=10;
int st[N][L+5];
int get(int x,int y)//询问时暴力查询
{
	if(y<=10)return st[x][y];
	return abs(get(x,y-1)-get(x+(1<<(y-1)),y-1));
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,T;
	cin>>n>>T;
	for(int i=1;i<=n;i++)
		cin>>st[i][0];
	for(int j=1;j<=L;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=abs(st[i][j-1]-st[i+(1<<(j-1))][j-1]);//留下的卡牌
	while(T--)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)
		{
			st[x][0]=y;
			for(int j=1;j<=L;j++)
				for(int i=max(1,x-(1<<j)+1);i<=x;i++)
					if(i+(1<<j)-1<=n)st[i][j]=abs(st[i][j-1]-st[i+(1<<(j-1))][j-1]);//暴力修改sqrtn个区间
		}
		else
		{
			if(y<=10)cout<<st[x][y]<<'\n';
			else cout<<get(x,y)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：zhangxy__hp (赞：0)

考虑如果没有修改，用 ST 表就非常舒服。

考虑暴力修改，需要修改所有覆盖了这个位置的区间，时间复杂度是 $O(n)$ 的。

而如果只修改 $\frac{\log n}{2}$ 层，时间复杂度就是 $O(\sqrt{n})$ 的。查询时从上往下查，最多查到第 $\frac{\log n}{2}$ 层，时间复杂度就也是 $O(\sqrt{n})$ 的。于是就可以通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline

using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=2e5+5;
int n,m,blen,st[maxn][20];
il int Log(int x){
	if(x==1){
		return 0;
	}
	return Log(x>>1)+1;
}
il void upd(int l,int k){
	if(k==blen){
		return ;
	}
	if(l-(1<<k)>0){
		st[l-(1<<k)][k+1]=abs(st[l-(1<<k)][k]-st[l][k]);
		upd(l-(1<<k),k+1);
	}
	if(l+(1<<(k+1))-1<=n){
		st[l][k+1]=abs(st[l][k]-st[l+(1<<k)][k]);
		upd(l,k+1);
	}
}
il int query(int l,int k){
	if(k<=blen){
		return st[l][k];
	}
	return abs(query(l,k-1)-query(l+(1<<(k-1)),k-1));
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>st[i][0];
	}
	blen=Log(n)>>1;
	for(int j=1;j<=blen;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=abs(st[i][j-1]-st[i+(1<<(j-1))][j-1]);
		}
	}
	while(m--){
		int opt,l,k;
		cin>>opt>>l>>k;
		if(opt==1){
			st[l][0]=k;
			upd(l,0);
		}
		else{
			cout<<query(l,k)<<"\n";
		}
	}
	return 0;
}
}
int main(){return asbt::main();}
```

---

## 作者：wukaichen888 (赞：0)

小清新数据结构。

首先这个唐氏 $|A-B|$ 嵌套感觉不可维护，考虑暴力根号。

静态查询自然想到 st 表。

单点修改自然就是动态 st 表。

修改时暴力将包含这个点的信息暴力改。

将 st 表的长度维度限制在 $2^9=512$ 以内。

查询时尽量分长块，然后暴力合并即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
int n,q,a[N],b[1024],tree[4096],tot;
int f[10][N];
void work(int x){
	if(x>1) f[0][x-1]=abs(a[x-1]-a[x]);
	if(x<n) f[0][x]=abs(a[x]-a[x+1]);
	for(int i=1,len;i<=8;i++){
		len=(1<<(i+1));
		for(int l=max(1,x-len+1);l<=min(x,n-len+1);l++)
			f[i][l]=abs(f[i-1][l]-f[i-1][l+(1<<i)]);
	}
}
#define lc k<<1
#define rc k<<1|1
#define ls lc,l,mid
#define rs rc,mid+1,r
void get(int k,int l,int r){
	if(l==r){
		tree[k]=b[l];
		return ;
	}
	int mid=l+r>>1;
	get(ls);get(rs);
	tree[k]=abs(tree[lc]-tree[rc]);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) f[0][i]=abs(a[i]-a[i+1]);
	for(int i=1,len;i<=8;i++){
		len=(1<<(i+1));
		for(int l=1;l+len-1<=n;l++)
			f[i][l]=abs(f[i-1][l]-f[i-1][l+(1<<i)]);
	}
	int op,x,y,z;
	while(q--){
		scanf("%d%d%d",&op,&x,&y);
		if(op==1){
			a[x]=y;
			work(x);
		}
		else{
			tot=0;
			z=min(y-1,8);
			y=x+(1<<y)-1;
			for(int i=x;i<=y;i+=(1<<(z+1))) b[++tot]=f[z][i];
			get(1,1,tot);
			printf("%d\n",tree[1]);
		}
	}
	return 0;
}
```

---

