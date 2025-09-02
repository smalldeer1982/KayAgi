# Welcome to Lunatic City

## 题目描述

M 国由 $n$ 个城市，$n-1$ 条双向高速铁路组成。其中的 $n$ 个城市可经过铁路互相抵达。

由于 M 国有着最顶尖的科技，为了加快交通速度，它可以在铁路上放置若干的互相配对的传送门，但总对数不超过 $L$。当一个列车在一条铁轨上运行时，每当它遇到一个传送门，就会进行传送。每个传送门分为正面与反面，列车从正面进入传送门时就会从与这个传送门配对的传送门的正面出来，从反面进入就从反面出来。传送门可以设立在一条铁路中间的任何地方。（如果对这一段描述有问题可以参考样例解释）

同时由于 M 国有着最高速的列车，列车的行驶时间仅消耗在停靠。于是从城市 $i$ 到城市 $j$ 的距离 $dis(i,j)$ 定义为列车所经过的城市数（包含终点但不包含起点）。

现在 M 国设立了 $m$ 个重要城市 $x_1,x_2,\dots,x_m$，请通过合理放置不超过 $L$ 对传送门使得 M 国的首都 $1$ 号城市到这些城市的距离和最小，即最小化 $\sum_{i=1}^mdis(1,x_i)$，并构造方案。同时放置的传送门必须保证城市间仍互相可达。

（由于 spj 的某些特性，请不要在一条铁路上放超过 $L$ 个传送门，否则会被判断为 WA）

## 说明/提示

### 样例解释

对于样例的第二组数据，树的形态及传送门的放置方式如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/l0r5x9l0.png)

其中红色门编号为 $1$，绿色编号为 $2$，蓝色编号为 $3$，紫色编号为 $4$。箭头表示传送门的正面所朝的方向。加粗的点表示重要城市。

其中 $1$ 号城市到 $5$ 号城市的最短路径如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/0bwhu6ct.png)

首先由 $1$ 号城市出发，进入红色传送门的正面到达 $3$ 号城市。

![](https://cdn.luogu.com.cn/upload/image_hosting/rgq415ni.png)

随后从 $3$ 号城市出发，从绿色传送门的正面进入，到达 $3-5$ 这条路上绿色与蓝色传送门中间的一段铁路上，再从蓝色传送门正面进入，到达 $2-3$ 这条路中蓝色与红色传送门中间的一段铁路上，再由红色传送门的背面进入，最终到达 $2$ 号城市。

![](https://cdn.luogu.com.cn/upload/image_hosting/xm1qefmr.png)

最后再从紫色传送门的正面进入，最终到达 $5$ 号城市。中途除去 $1$ 号城市分别经过了 $3,2,5$ 号城市，于是在这种传送门的放置方式下 $dis(1,5)=3$。

同时有 $dis(1,4)=2$，可以证明不存在让 $dis(1,4)+dis(1,5)$ 更小的放置方案。

### 数据范围

**本题采用捆绑测试**

| 子任务编号 | 分值 | 特殊限制 |
| :----------: | :----------: | :----------: |
| $0$ | $15$ | $n\le 9$，$L=100$ |
| $1$ | $10$ | $m=n-1$，$L=5n$ |
| $2$ | $20$ | $n\le 70$ 且 $n>30$ 的数据不超过五组，$L=n^2$ |
| $3$ | $20$ | $n\le 1000$ 且 $n>100$ 的数据不超过五组，$L=100n$ |
| $4$ | $30$ | $L=5n$ |
| $5$ | $5$ | $L=n$ |

对于所有数据，保证 $1\le T\le 100$，$1\le n\le 10^5$，$1\le \sum n\le 5\times 10^5$，$0\le m<n$，$2\le x_i\le n$，$x_i$ 互不相同。

## 样例 #1

### 输入

```
2
4 3 100
1 2
2 3
3 4
2 3 4
5 2 100
1 2
2 3
3 4
3 5
4 5```

### 输出

```
6
0
0
0
5
1 1 0
3 4 0 3 1 1 1
1 2 0
3 2 1 3 0 4 1```

# 题解

## 作者：Kubic (赞：8)

stO sgygd Orz

这是一个我自己编的做法，不知道和 std 是否一样。

乍一看这道题的传送门和一大堆奇怪的限制一点思路都没有。

我们先来分析一下建立一对传送门实际上会发生什么。

可以发现，在 $(u_1,v_1)$ 上和 $(u_2,v_2)$ 上建立一对传送门相当于断开 $(u_1,v_1)$ 和 $(u_2,v_2)$，并连接 $(u_1,u_2)$ 和 $(v_2,v_2)$。

显然上面的操作不会改变每个点的度数，并且弱于每次交换两个点的父亲。由于题目要求最终每个点都要能够到达，所以最终状态也必须是一棵树。

注意：这里交换两个点的父亲可能会在过程中产生环，但这并不重要，只要保证最终是一棵树即可。

显然如果新树中每个点的度数都与原树一样，那么一定可以达到这个状态。

现在我们的目标就是使得新树中所有关键点的深度之和最小。

先考虑一个暴力做法。

把所有的点（除了根节点）按照度数从大到小排序。如果某个关键点与非关键点度数一样，那么关键点排在前面。

我们需要考虑的是新树中所有关键点和根节点形成的虚树。

显然虚树中所有非关键节点一定处于一个前缀中（也就是尽量大），否则肯定不优。

我们枚举这个前缀，然后贪心地把所有虚树中的节点按照度数从大到小依次加入，每次选择一个深度最浅的还没连满的点连上去。这样一定是最优的（感性理解）。

注意：如果有至少一个点不在虚树中，则需要保证连完之后至少还剩一个点没有连满，否则就不合法了。

至此我们就得到了一个 $O(n^2)$ 做法。

那么如何优化它呢？

我们把每次加入一个节点改为每次加入一层节点。

如果当前加入的这一层的所有点度数都 $\ge 2$，那么这一层的度数总和至少是上一层的 $2$ 倍。

而所有点的度数和是 $O(n)$ 的，也就是说，这样的层数不会超过 $O(\log n)$！

在枚举完所有这样的层之后，剩下的点的度数就都 $\le 1$ 了，可以直接 $O(1)$ 特判掉。

利用这种做法就可以 $O(\log n)$ 地算出某一个前缀的答案。构造方案时只需要记录答案最优的前缀，然后再 $O(n)$ 模拟一遍之前的做法即可。

时间复杂度 $O(n\log n)$。

参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define LIM 1000005
#define ll long long
#define pb push_back
#define gc() (P1==P2 && (P2=(P1=buf)+fread(buf,1,LIM,stdin),P1==P2)?EOF:*P1++)
const ll INF=1e18;char *P1,*P2,buf[LIM];
int T,n,m,c,nw,tmp,cnt,dg[N],fa[N],fe[N],fa1[N],z[N],z1[N],s[N],q[N];ll w,res,ans1;
bool tg[N],tg1[N];set<int> ps[N];struct Edge {int v,id;};vector<Edge> e[N];
struct Node {int x;bool tg;};vector<Node> ans[N];
int rd()
{
	int res=0;char c=0;while(!isdigit(c)) c=gc();
	while(isdigit(c)) res=res*10+c-48,c=gc();return res;
}
void print(int x) {if(x<10) {putchar(x+48);return;}print(x/10);putchar(x%10+48);return;}
bool cmp(int x,int y) {return dg[x]*2+tg1[x]==dg[y]*2+tg1[y]?x<y:dg[x]*2+tg1[x]<dg[y]*2+tg1[y];}
void f(int u,int v) {++nw;ans[fe[u]].pb((Node) {nw,tg[u]});ans[fe[v]].pb((Node) {nw,!tg[v]});}
void dfs(int u,int f)
{fa[u]=f;for(auto i:e[u]) if(i.v!=f) tg[i.v]=i.id<0,fe[i.v]=abs(i.id),++dg[u],dfs(i.v,u);}
ll slv1(int x,int d,int w1,int w2)
{
	int t;ll res=0;if(x<=w1) {return x<w1 || s[x]?1ll*x*d:INF;}
	res=1ll*w1*d;++d;x-=w1;w2+=s[x+w1]-s[x];if(!w2) return INF;
	while(1)
	{
		if(x<=w2) {return x<w2 || s[x]?res+1ll*x*d:INF;}
		res+=1ll*w2*d;++d;x-=w2;w2=s[x+w2]-s[x];if(dg[z1[x]]<2) break;
	}if(min(x,cnt)>=w2) return INF;t=x/w2;return res+1ll*(d*2+t-1)*t*w2/2+1ll*(d+t)*(x%w2);
}
void slv()
{
	n=rd();m=rd();c=rd();if(n==1) {puts("0");return;}nw=cnt=w=0;q[0]=2;q[1]=1;
	for(int i=1;i<=n;++i) dg[i]=fa1[i]=tg1[i]=0,z[i]=i,ps[i].clear(),e[i].clear(),ans[i].clear();
	for(int i=1,u,v;i<n;++i) u=rd(),v=rd(),e[u].pb((Edge) {v,i}),e[v].pb((Edge) {u,-i});
	for(int i=1;i<=m;++i) z1[i]=rd(),tg1[z1[i]]=1;dfs(1,0);
	
	sort(z+2,z+n+1,cmp);sort(z1+1,z1+m+1,cmp);for(int i=1;i<=m;++i) s[i]=s[i-1]+dg[z1[i]];
	for(int i=1;i<=m;++i) if(!dg[z1[i]]) ++cnt;tmp=n+1;ans1=slv1(m,1,dg[1],0);
	for(int i=n,t=m,d=1,w1=dg[1],w2=0;i>1;--i)
	{
		if(tg1[z[i]]) --t,w+=d;--w1;w2+=dg[z[i]];if(!w1) ++d,swap(w1,w2);
		res=w+(i>2?slv1(t,d,w1,w2):0);if(res<ans1) tmp=i,ans1=res;
	}for(int i=1;i<=dg[1];++i) q[++q[1]]=1;
	for(int i=n;i>1;--i) if(i>=tmp || tg1[z[i]])
	{fa1[z[i]]=q[q[0]++];for(int j=1;j<=dg[z[i]];++j) q[++q[1]]=z[i];}
	for(int i=n;i>1;--i) if(!fa1[z[i]])
	{fa1[z[i]]=q[q[0]++];for(int j=1;j<=dg[z[i]];++j) q[++q[1]]=z[i];}
	
	printf("%lld\n",ans1);for(int i=2;i<=n;++i) ps[fa[i]].insert(i);
	for(int i=2,t;i<=n;++i) if(fa[i]!=fa1[i])
	{
		t=*ps[fa1[i]].begin();ps[fa[i]].erase(i);
		f(i,t);ps[fa[t]].erase(t);ps[fa[i]].insert(t);swap(fa[i],fa[t]);
	}else ps[fa[i]].erase(i);
	for(int i=2;i<=n;++i) if(tg[i]) reverse(ans[fe[i]].begin(),ans[fe[i]].end());
	for(int i=1;i<n;++i)
	{
		print(ans[i].size());putchar(' ');
		for(auto j:ans[i]) print(j.x),putchar(' '),print(j.tg),putchar(' ');puts("");
	}
}
int main() {T=rd();while(T--) slv();return 0;}
```

---

