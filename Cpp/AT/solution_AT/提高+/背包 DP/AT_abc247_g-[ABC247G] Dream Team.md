# [ABC247G] Dream Team

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc247/tasks/abc247_g

$ N $ 人の競技プログラマがいます。  
 $ i $ 人目の競技プログラマは、所属大学が $ A_i $、得意分野が $ B_i $、強さが $ C_i $ です。

$ N $ 人のうちの何人かによって構成されるチームであって、次の条件をともに満たすものを**ドリームチーム**と呼びます。

- チームに属するどの $ 2 $ 人の所属大学も異なる
- チームに属するどの $ 2 $ 人の得意分野も異なる

構成可能なドリームチームの人数の最大値を $ k $ とします。各 $ i=1,2,\ldots,k $ について、次の問題を解いてください。

問題：ちょうど $ i $ 人で構成されるドリームチームについて、チームに所属する人の強さの合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3\times\ 10^4 $
- $ 1\ \leq\ A_i,B_i\ \leq\ 150 $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

\- ちょうど $ 1 $ 人で構成されるドリームチームは、$ 1 $ 人目の競技プログラマからなるとき強さの合計が $ 100 $ で最大になります。 - ちょうど $ 2 $ 人で構成されるドリームチームは、$ 2,3 $ 人目の競技プログラマからなるとき強さの合計が $ 11 $ で最大になります。 - ちょうど $ 3 $ 人で構成されるドリームチームを作ることはできません。

## 样例 #1

### 输入

```
3
1 1 100
1 20 10
2 1 1```

### 输出

```
2
100
11```

## 样例 #2

### 输入

```
10
1 4 142135623
2 6 457513110
3 1 622776601
5 1 961524227
2 2 360679774
2 4 494897427
3 7 416573867
5 2 915026221
1 7 320508075
5 3 851648071```

### 输出

```
4
961524227
1537802822
2032700249
2353208324```

# 题解

## 作者：igAC (赞：2)

# $\text{Description}$

~~闲话：$20\text{min}$ 切一道蓝色水网络流，好好好。~~

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc247_g)

[ATlink](https://atcoder.jp/contests/abc247/tasks/abc247_g)

简要题意（洛谷翻译）：

平面中有 $n$ 个点，坐标为 $(a_i,b_i)$，权值为 $c_i$。

对于每一行每一列最多只能选一个点，最大化选点个数 $k$ 并输出。

对于每个 $i,i=1,2……k$，最大化选出 $i$ 个点的权值和。

# $\text{Solution}$

最小费用最大流板子题。

对于交点所在的行列建边，流量为 $1$，费用为 $-c_i$。

在二分图上跑最小费用最大流，第 $i$ 次网络的费用就是选 $i$ 个点的分数。

最后答案要取负。

点数：$300$，边数：$n+300$。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define LLINF 1e18
#define int long long
#define N 305
#define M 50005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,s,t,head[N],tot=1,ans[N],cnt;
int dis[N],prevv[N],preve[N],mp[N][N];
bool vis[N];
struct Edge{
	int to,nxt;
	int val,cost;
}e[M];
void add_edge(int x,int y,int z,int cost){
	e[++tot].to=y;
	e[tot].val=z;
	e[tot].cost=cost;
	e[tot].nxt=head[x];
	head[x]=tot;
	e[++tot].to=x;
	e[tot].val=0;
	e[tot].cost=-cost;
	e[tot].nxt=head[y];
	head[y]=tot;
}
bool SPFA(){
	for(int i=s;i<=t;++i) dis[i]=LLINF;
	memset(vis,0,sizeof(vis));
	queue<int>q;
	q.push(s),dis[s]=0,vis[s]=true;
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=false;
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(e[i].val && dis[y]>dis[x]+e[i].cost){
				prevv[y]=x,preve[y]=i;
				dis[y]=dis[x]+e[i].cost;
				if(!vis[y]){
					q.push(y);
					vis[y]=true;
				}
			}
		}
	}
	return dis[t]!=LLINF;
}
int Dinic(){
	int cost=0;
	while(SPFA()){
		int res=LLINF;
		for(int i=t;i!=s;i=prevv[i]) res=min(res,e[preve[i]].val);
		for(int i=t;i!=s;i=prevv[i]){
			e[preve[i]].val-=res;
			e[preve[i]^1].val+=res;
		}
		cost+=res*dis[t];
		ans[++cnt]=cost;
	}
	return cost;
}
signed main(){
	n=150,m=read(),s=0,t=n+n+1;
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		mp[x][y]=max(mp[x][y],read());
	}
	for(int i=1;i<=n;++i) add_edge(s,i,1,0);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(mp[i][j]) add_edge(i,j+n,1,-mp[i][j]);
		}
	}
	for(int i=1;i<=n;++i) add_edge(i+n,t,1,0);
	Dinic();printf("%lld\n",cnt);
	for(int i=1;i<=cnt;++i) printf("%lld\n",-ans[i]);
	return 0;
}
```

---

## 作者：Scene (赞：1)

AT_abc247_g [ABC247G] Dream Team 题解

这道题和 [圆桌问题](https://www.luogu.com.cn/problem/P3254) 很像，只不过在原来的基础上加了价格。

将每个学校设置为一个点，并将其与源点连接，流量为 1，价格为 0，代表每个学校可以有一个人参加。

再将每个项目设置为一个点，并将其与汇点连接，流量为 1，价格为 0，代表每个项目可以有一个人参加。

若 $A$ 学校有一个人在 $B$ 项目上的分数为 $C$，则将 $A$ 学校的点向 $B$ 项目的点连一条流量为 1，价格为 $-C$ 的边。若这条边流量流完，则代表选择这个人参加，反之则代表这个人不参加。

记得建反向边，让操作可以反悔，保证正确性。

最后答案为费用取负。

#### 怎么满足题目中队伍中有 $x$ 个人的限制？

可以再加一个新源点，新源点向之前的源点连流量为 $x$，价格为 0 的边即可。

或者在写法上改一下，这样更简单。

---

## 作者：sunkuangzheng (赞：0)

$\textbf{ABC247G}$

> - 平面中有 $n$ 个点，坐标为 $(a_i,b_i)$，权值为 $c_i$。每一行每一列最多只能选一个点，最大化选点个数 $k$ 并输出。
> - 同时对于 $i \in [1,k]$，最大化选出 $i$ 个点的权值和。
> - $1 \le n \le 3 \cdot 10^4,1 \le a_i,b_i \le 150$。

对于一个点 $(x,y)$，如果选了它则第 $x$ 行第 $y$ 列都不能再选其它点，如果把第 $x$ 行向第 $y$ 列连边，这是一个**二分图最大匹配**模型。跑一遍最大流即可求出 $k$ 的值。

考虑第二问其实就是二分图最大权匹配，直接暴力跑 $k$ 遍费用流。令 $N = 300$，时间复杂度 $\mathcal O(N^3n)$，不知道能不能过。

使用 [acl 的费用流](https://atcoder.github.io/ac-library/production/document_en/mincostflow.html)，单次时间复杂度为 $\mathcal O(Nn \log n)$，总复杂度 $\mathcal O(N^2n\log n)$，可以通过。

```cpp
#include<bits/stdc++.h>
#include <atcoder/all>
using ll = long long;
const int N = 5e5+5;
const ll inf = 1e10;
using namespace std;
using namespace atcoder;
int T,n,a[N],b[N],c[N],s,ss,tt,x;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> a[i] >> b[i] >> c[i];
    auto build = [&](int lim){
        mcf_graph<int,ll> g(302);
        ss = 0,tt = 301;
        for(int i = 1;i <= 150;i ++) g.add_edge(ss,i,1,0),g.add_edge(i+150,tt,1,0);
        for(int i = 1;i <= n;i ++) g.add_edge(a[i],b[i]+150,1,inf - c[i]);
        return g.flow(ss,tt,lim);
    };
    cout << (x = build(1e9).first) << "\n";
    for(int i = 1;i <= x;i ++) cout << - build(i).second + inf * i << "\n";
}
```

---

