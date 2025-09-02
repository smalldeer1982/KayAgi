# [IOI 2016] railroad

## 题目描述

Anna 在一个游乐园工作。她负责建造一个新的过山车铁路。她已经设计了影响过山车速度的 $n$ 个特殊的路段（方便起见标记为 $0$ 到 $n-1$）。现在 Anna 必须要把这些特殊的路段放在一起并提出一个过山车的最后设计。为了简化问题，你可以假设过山车的长度为零。

对于 $0$ 和 $n-1$ 之间的每个 $i$，这个特殊的路段 $i$ 具有如下两个性质：

- 当进入这个路段时，有一个速度限制：过山车的速度必须小于或等于 $s_i$ $\text{km/h}$（每小时千米）。

- 当离开这个路段时，过山车的速度刚好是 $t_i$ $\text{km/h}$，不管过山车进入该路段时的速度如何。

最后完成的过山车设计是一个以某种顺序包含这 $n$ 个特殊路段的单一铁路线。这 $n$ 个路段中的每一个应当被使用刚好一次。连续的路段之间用铁轨来连接。Anna 应该选择这 $n$ 个路段的顺序，然后确定每段铁轨的长度。铁轨的长度以米来衡量，可以是任意的非负整数（可以为零）。

两个特殊路段之间的每 $1$ 米铁轨可以将过山车的速度减慢 $1$ $\text{km/h}$。在这个过山车铁路的起点，过山车按照 Anna 选择的顺序进入第一个特殊路段时的速度是 $1$ $\text{km/h}$。

最后的设计还必须满足以下要求：

- 过山车在进入这些特殊路段时不能违反任一个速度限制。

- 过山车的速度在任意时刻为正。

你的任务是找出这些路段之间铁轨的最小可能总长度（这些路段之间铁轨总长度的最小值）。如果 $m=0$ 你只需要检查是否存在一个有效的过山车设计，使得每段铁轨的长度为零。

**举例**

```
4 1
1 7
4 3
5 8
6 6
```
在这个样例中有 $4$ 个特殊的路段。最好的解是按照 $0,3,1,2$ 的顺序构造，连接这些路段的铁轨长度分别是 $1,2,0$。下面给出过山车沿铁路铁轨的行驶方式：

- 最初过山车的速度是 $1$ km/h。

- 过山车由进入 $0$ 号路段开始行进。

- 过山车以 $7$ $\text{km/h}$ 的速度离开 00 号路段。

- 然后有一段长度为 $1$ $\text{m}$ 的铁轨。过山车在到达这段铁轨的末端时速度为 $6$ $\text{km/h}$。

- 过山车以 $6$ $\text{km/h}$ 的速度进入 $3$ 号路段并以相同的速度离开该路段。

- 在离开 $3$ 号路段后，过山车走过一段 $2$ $\text{m}$ 长的铁轨。速度降至 $4$ $\text{km/h}$。

- 过山车以 $4$ $\text{km/h}$ 的速度进入 $1$ 号路段，并且以 $3$ $\text{km/h}$ 的速度离开该路段。

- 离开 $1$ 号路段后，过山车立即进入 $2$ 号路段。

- 过山车离开 $2$ 号路段。其最终速度是 $8$ $\text{km/h}$。

路段之间的铁轨总长度：$1+2+0=3$。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 2 \times {10}^5$，$ 1 \le s_i \le 10^9$，$1 \le t_i \le 10^9$。

## 样例 #1

### 输入

```
4 1
1 7
4 3
5 8
6 6
```

### 输出

```
3
```

# 题解

## 作者：Leasier (赞：22)

[0htoAi](https://www.luogu.com.cn/user/335366) 的至理名言：任何看上去很需要脑子的题不会做就想想能不能**欧拉回路**。

~~但我觉得更重要的一点或许是：Stay motivated.~~

------------

- **减少情况**：为描述初始状态，考虑加上一个 $(+\infty, 1)$ 的路段。
- **转换条件**：注意到 $t_i$ 的限制是 $=$ 但 $s_i$ 的限制是 $\leq$，考虑把 $s_i$ 的限制改成**更强**的 $=$。遂考虑把原题的变速条件变为减速 $1$ 消耗 $1$ 的代价、加速不消耗代价。
- **建立模型**：我们每次变速要么是 $s_i \to t_i$、不消耗代价，要么是 $v + 1 \to v$、代价为 $1$，要么是 $v \to v + 1$、不消耗代价。又因为我们一定会经过所有 $s_i \to t_i$ 的变速过程，这让我们想到**欧拉通路**。这里我们需要走出一条从 $+\infty$ 出发、经过所有 $s_i \to t_i$ 的欧拉通路，且需要求出代价之和的最小值。
- **简化模型**：欧拉通路因为起点和终点的问题往往讨论起来比**欧拉回路**更为麻烦，又注意到从任何有效的点出发前往 $+\infty$ 都不需要任何代价，于是我们可以直接把前文所述的“欧拉通路”改为“欧拉回路”，答案不变。
- **分析性质**：在本题中，由于所有点都在一条链上，则任何一条回路跨过 $v \to v + 1$ 与 $v + 1 \to v$ 的次数恰好相等。首先不难差分出 $s_i \to t_i$ 跨过一段 $v \to v + 1$ 与 $v + 1 \to v$ 的次数之差，不妨设之为 $\text{diff}_v$。若 $\text{diff}_v < 0$，我们显然可以通过若干次无需代价的 $v \to v + 1$ 来抵消；若 $\text{diff}_v > 0$，我们只能通过若干次每次代价为 $1$ 的 $v + 1 \to v$ 来抵消。
- **查漏补缺**：注意到上面的分析并没有考虑到现在求出的“欧拉回路”实际上不连通的情况，此时我们需要若干条 $v \to v + 1, v + 1 \to v$ 来使之连通。加上所有的 $v + 1 \to v$ 跑一遍 MST 求出最小代价即可。

就实现而言，对 $s_i, t_i$ 离散化后即可完成上述所有操作。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef struct Edge_tag {
	int start;
	int end;
	int dis;
	Edge_tag(){}
	Edge_tag(int start_, int end_, int dis_){
		start = start_;
		end = end_;
		dis = dis_;
	}
} Edge;

int s[200007], t[200007], a[400007], root[400007], diff[400007];
Edge edge[400007];

bool operator <(const Edge a, const Edge b){
	return a.dis < b.dis;
}

inline void init(int n){
	for (int i = 1; i <= n; i++){
		root[i] = i;
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void merge(int x, int y){
	int x_root = get_root(x), y_root = get_root(y);
	if (x_root != y_root) root[x_root] = y_root;
}

int main(){
	int n, m, k = 0, cnt = 0;
	ll ans = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> s[i] >> t[i];
	}
	n++;
	s[n] = 0x7fffffff;
	t[n] = 1;
	for (int i = 1; i <= n; i++){
		a[++k] = s[i];
		a[++k] = t[i];
	}
	sort(a + 1, a + k + 1);
	k = unique(a + 1, a + k + 1) - a - 1;
	init(k);
	for (int i = 1; i <= n; i++){
		s[i] = lower_bound(a + 1, a + k + 1, s[i]) - a;
		t[i] = lower_bound(a + 1, a + k + 1, t[i]) - a;
		diff[s[i]]++;
		diff[t[i]]--;
		merge(s[i], t[i]);
	}
	for (int i = 1; i <= k; i++){
		diff[i] += diff[i - 1];
	}
	for (int i = 1; i < k; i++){
		if (diff[i] != 0){
			merge(i, i + 1);
			if (diff[i] > 0) ans += (ll)diff[i] * (a[i + 1] - a[i]);
		}
	}
	for (int i = 1; i < k; i++){
		if (get_root(i) != get_root(i + 1)) edge[++cnt] = Edge(i, i + 1, a[i + 1] - a[i]);
	}
	sort(edge + 1, edge + cnt + 1);
	for (int i = 1; i <= cnt; i++){
		int x_root = get_root(edge[i].start), y_root = get_root(edge[i].end);
		if (x_root != y_root){
			root[x_root] = y_root;
			ans += edge[i].dis;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：19)

图论好题。

首先简化一下题意：有 $n$ 个车站，进入车站的速度**不能高于 $s_i$**，出站后速度固定 $t_i$，可以用 $x$ 的代价使车速降低 $x$，排列车站使得代价最小。

我们考虑对于每个速度建一个点，车站……好像要连很多边，必然炸空间，不能这么搞。

我们略微转化一下题意：有 $n$ 个车站，进入车站的速度**必须恰好为 $s_i$**，出站后速度固定 $t_i$，可以用 $x$ 的代价使车速降低 $x$，**提速没有任何代价**，排列车站使得代价最小。

这样有了一个显然的模型：先离散化，对于每个速度建一个点，每个车站从 $s_i$ 到 $t_i$ 连边，接下来建一个虚点 $inf$，$inf$ 到 $1$ 连边，$inf-1$（也就是离散化之后的最大值）到 $inf$ 连边，然后相邻两点连双向边，正向的费用为 0，反向的费用为两点的速度差值。然后在这个图上跑最小哈密尔顿回路。

~~然后我们愉快的获得了一个 NPC 问题，就狗带了。~~

按照套路，我们考虑把哈密尔顿回路问题转化成欧拉回路问题。

想到可以先不连相邻两点之间的边，然后写一个算法实现**只添加必须要变速的边**，这样每个边都会走到，于是变成了一个图上添加权值和尽可能小的边使这个图变成欧拉回路的问题。

不难发现我们要添加相邻两点的边当且仅当**覆盖了这条边的向左的边和向右的边数量不一致**。而这个东西容易差分得到。如果向左的边多，那么我们添加的是若干条费用为 0 的加速边，没有贡献；如果向右的边多，我们添加若干条费用为两点速度差的边，这时计算贡献。

做完这个操作之后我们会得到若干个存在欧拉回路的联通块，这时原图还没有欧拉回路。我们还需要把联通块连起来，这个操作每次要连一条加速边一条减速边，因此每连一次代价是两点间速度差。

显然我们只会在相邻的联通块之间连边，否则一定不优，扫一遍加边，然后跑最小生成树即可。

最后还有一个坑是图中的单个点我们不需要连起来，但可能存在单个点有自环，这时需要特判。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define int long long
struct edge
{
    int x,y,w;
    edge(int x_,int y_,int w_):
        x(x_),y(y_),w(w_){}
    bool operator <(const edge &other) const
    {
        return w<other.w;
    }
};
vector<edge> v;
int n,m,bin[100001<<2],s[100001<<2],t[100001<<2],sum[100001<<2],node[100001<<2],cnt,ans;
bool vis[100001<<2];
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
int anc(int k)
{
    if(!bin[k])
        return k;
    return bin[k]=anc(bin[k]);
}
inline void link(int x,int y)
{
    x=anc(x);
    y=anc(y);
    if(x^y)
        bin[y]=x;
}
signed main()
{
    n=read(),m=read();
    for(register int i=1;i<=n;++i)
    {
        s[i]=read(),t[i]=read();
        node[++cnt]=s[i];
        node[++cnt]=t[i];
    }
    node[++cnt]=1e9+7;
    sort(node+1,node+cnt+1);
    cnt=unique(node+1,node+cnt+1)-node-1;
    s[++n]=1e9+7;
    t[n]=node[1];
    s[++n]=node[cnt-1];
    t[n]=1e9+7;
    for(register int i=1;i<=n;++i)
    {
        s[i]=lower_bound(node+1,node+cnt+1,s[i])-node;
        t[i]=lower_bound(node+1,node+cnt+1,t[i])-node;
        ++sum[s[i]];
        --sum[t[i]];
        vis[anc(s[i])]=1;
        if(s[i]^t[i])
            link(s[i],t[i]);
    }
    for(register int i=1;i<cnt;++i)
    {
        sum[i]+=sum[i-1];
        if(sum[i]>0)
            ans+=sum[i]*(node[i+1]-node[i]);
        if(sum[i])
        {
            link(i,i+1);
            vis[anc(i)]=1;
        }
    }
    for(register int i=1,j=1;i<=cnt;i=j)
    {
        j=i+1;
        while(j<=cnt&&!vis[anc(j)])
            ++j;
        if(j>cnt)
            break;
        if(anc(i)^anc(j))
            v.push_back(edge(anc(i),anc(j),node[j]-node[i]));
    }
    sort(v.begin(),v.end());
    for(register int i=0;i<(int)v.size();++i)
        if(anc(v[i].x)^anc(v[i].y))
        {
            ans+=v[i].w;
            link(v[i].x,v[i].y);
        }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Antarctica_Oabaijnaw (赞：1)

神仙题，我说的。

各位大佬都讲了这玩意要把问题转化成欧拉回路，这里主要讲的是一些细节问题，有些口水话，还望各位见谅。

首先发现 $\leq s_i$ $\text{km/h}$ 的条件很棘手，但是加速没有任何代价，于是强制规定**必须等于** $s_i$ $\text{km/h}$。

随后肯定需要将已知条件建模，每个车站从 $s_i$ 向 $t_i$ 连边，同时建一个虚点 inf，让 inf 向 1 连边，现在 $s_i$ 和 $t_i$ 中的最大值向 inf 连边，然后补一些边使整个图形成欧拉回路，问补上的那些边的边权之和最小是多少。

这就是正解思路了（前人之述备矣），但是初看肯定会一头雾水，所以画图理解一下，这题不画图就是石：

![样例，其中黑色的边是我们最初建的，其他颜色的边是补上的](https://cdn.luogu.com.cn/upload/image_hosting/n1ep5832.png?)

样例，其中黑色的边是我们最初建的，其他颜色的边是补上的。

解释一下：

- 以 $1$ $\text{km/h}$ 进入 $0$ 号路段，以 $7$ $\text{km/h}$ 的速度离开该路段（点 1 到点 7）
- 减速至 $6$ $\text{km/h}$，花费代价为 1（点 7 到点 6）
- 以 $6$ $\text{km/h}$ 进入 $3$ 号路段并以相同的速度离开该路段（点 6 到点 6 自环）
- 减速至 $4$ $\text{km/h}$，花费代价为 2（点 6 到点 4）
- 以 $4$ $\text{km/h}$ 进入 $1$ 号路段，以 $3$ $\text{km/h}$ 的速度离开该路段（点 4 到点 3）
- 提速至 $5$ $\text{km/h}$，**不花费代价**（点 3 到点 6）
- 以 $5$ $\text{km/h}$ 进入 $2$ 号路段，以 $8$ $\text{km/h}$ 的速度离开该路段（点 5 到点 8）
- 以 $8$ $\text{km/h}$ 进入第一条虚路段，以 $\text{inf\ km/h}$ 的速度离开该路段（点 8 到点 inf）
- 以 $\text{inf\ km/h}$ 进入第二条虚路段，以 $1$ $\text{km/h}$ 的速度离开该路段（点 inf 到点 1）
- 自此回到点 1，所有的边都只经过一次，形成欧拉回路

现在应该懂了吧。

然后，我们反过来研究一下如果图是欧拉回路会有什么性质。我们观察两个相邻的点，惊人的发现：对于所有横跨这两个节点（对于“横跨”，举例解释一下，比如 $0$ 号路段从点 1 到点 7，就横跨了 点 1 和 点 3 等）的边，加速的和减速的边数相等！

证明也是显然的，因为欧拉回路是每一条边都要经过的，这一次是通过加速边，下一次一定是过减速边，而由于是回路，所以去和回一一对应，次数一定相等。

于是可以差分处理每一对相邻的点覆盖的初始黑边数量，然后对每一对相邻的点补上加速边或减速边，就补成了上图**去掉绿边**的样子。由于边数差可能大于 1，所以有时得补多条边，差分的时候乘上边数就行了。

这时我们尴尬地发现，这个补过的图可能不连通！为了将图连通，我们用并查集处理连通块，对于每一对不在同一个连通块内的相邻的点，我们都可以补上一对双向边，就是图中的绿边。而不一定所有可以补的都要补上，所以用最小生成树（MST）处理一下。

然后因为 $s_i$ 和 $t_i$ 的值域很大要离散化一下，差不多就口胡完了。

代码就不贴注释了，上面已经讲得很明白了。

```cpp
#include<bits/stdc++.h>
#define int  long long
using namespace std;
int n,m,s[200005],t[200005],d[400005]; 
int fa[400005];
int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]); 
}
void join(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	fa[fx]=fy;
}
struct edge{
	int u,v,w;
	bool operator<(const edge &o)const{
		if(w==o.w&&u==o.u)return v<o.v;
		if(w==o.w)return u<o.u;
		return w<o.w;
	}
};
signed main(){
	cin>>n>>m;
	vector<int>l;
	for(int i=1;i<=n;i++)cin>>s[i]>>t[i],l.push_back(s[i]),l.push_back(t[i]);
	n++;
	s[n]=INT_MAX,t[n]=1;
	l.push_back(s[n]),l.push_back(t[n]);
	n++;
	s[n]=INT_MAX-1,t[n]=INT_MAX;
	l.push_back(s[n]),l.push_back(t[n]);
	sort(l.begin(),l.end());
	l.erase(unique(l.begin(),l.end()),l.end());
	for(int i=0;i<l.size();i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		s[i]=lower_bound(l.begin(),l.end(),s[i])-l.begin();
		t[i]=lower_bound(l.begin(),l.end(),t[i])-l.begin();
		d[s[i]]++;
		d[t[i]]--;
		join(s[i],t[i]);
	}
	int sum=0;
	for(int i=1;i<l.size();i++)d[i]+=d[i-1];
	for(int i=0;i<l.size()-1;i++){
		if(d[i]!=0)join(i,i+1);
		if(d[i]>0)sum+=(l[i+1]-l[i])*d[i];
	}
	vector<edge>edges;
	for(int i=1;i<l.size();i++){
		int fi=find(i-1),fii=find(i);
		if(fi!=fii)edges.push_back({i-1,i,l[i]-l[i-1]});
	}
	sort(edges.begin(),edges.end());
	for(auto x:edges){
		int fu=find(x.u),fv=find(x.v);
		if(fu==fv)continue;
		fa[fu]=fv;
		sum+=x.w;
	}
	cout<<sum<<endl;
}//Vive la Furina!
```

---

## 作者：Swordmaker (赞：1)

# P6168 [IOI 2016] railroad

# 前置知识

本题需要用到前缀和，离散化，并查集，最小生成树等。

# 初步尝试

一开始，我们会写一个简单的全排列搜索。
```
//时间复杂度为n!
void dfs(int tot)
{
	if(tot==n)
	{
		int v=a[1].t,cnt=0;
		for(int i=2;i<=n;i++)
		{
			if(v>a[way[i]].s) cnt=cnt+v-a[way[i]].s;
			v=a[way[i]].t;
		}
		ans=min(ans,cnt);
		return;
	}
	for(int i=2;i<=n;i++)
	{
		if(vis[i]) continue;
		vis[i]=true;
		way[tot+1]=i;
		dfs(tot+1);
		vis[i]=false;
	}
	return;
}
```
大概能拿到三四十分。

但这显然不是我们的目标。

# 改进优化

首先，因为 $s_i$ 和 $t_i$ 的范围很大，但是 $n$ 的数量却并没有那么大，就可以进行离散化。

然后，由于我们每次是从入口的速度进入，出口的速度驶出，如果直接处理点，并不是特别好做。所以可以从 $s_i$ 到 $t_i$ 连一条边。然后将点权转化为边权。

考虑优化：并不是所有的边都需要连上，由于代价只是在要减速的时候产生，于是只对需要进行减速的点进行连边。

再建一个虚点，权值为极大值，那么显然从这个点出发，可以到达任何一个点。于是，现在的问题就是对这个新图跑欧拉回路并使得所有的连通块都相连。

最后，就是对不同连通块求一棵最小生成树，那么这一棵最小生成树必然是所需铁轨长度的最小值。

# 警示

小心重边和自环！

# code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
const int inf=1e15+5;
struct node
{
	int u,v,w;
}e[N];
int n,m,cnt=0,ans=0,hzj=0;
int s[N],t[N],a[N],f[N],pre[N];
bool cmp(node c,node d)
{
	return c.w<d.w;
}
int find(int x)
{
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	if(fx==fy) return;
	f[fx]=fy;
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i]>>t[i];
		a[++cnt]=s[i];
		a[++cnt]=t[i];
	}
	n++;
	s[n]=inf,t[n]=1;
	a[++cnt]=s[n],a[++cnt]=t[n];
	sort(a+1,a+cnt+1);
	cnt=unique(a+1,a+cnt+1)-a-1;
	for(int i=1;i<=cnt;i++)
	{
		f[i]=i;
	}
	for(int i=1;i<=n;i++)
	{
		s[i]=lower_bound(a+1,a+cnt+1,s[i])-a;
		t[i]=lower_bound(a+1,a+cnt+1,t[i])-a;
		pre[s[i]+1]++;
		pre[t[i]+1]--;
		merge(s[i],t[i]);
	}
	for(int i=2;i<=cnt;i++)
	{
		pre[i]+=pre[i-1];
	}
	for(int i=2;i<=cnt;i++)
	{
		if(!pre[i]) continue;
		else if(pre[i]>0) ans+=pre[i]*(a[i]-a[i-1]);
		merge(i-1,i);
	}
	for(int i=2;i<=cnt;i++)
	{
		if(find(i)!=find(i-1)) e[++hzj]=node{i-1,i,a[i]-a[i-1]};
	}
	sort(e+1,e+hzj+1,cmp);
	for(int i=1;i<=hzj;i++)
	{
		int fx=find(e[i].u);
		int fy=find(e[i].v);
		if(fx!=fy)
		{
			f[fx]=fy;
			ans+=e[i].w;
		}
	}
	cout<<ans<<"\n";
	return 0; 
} 
```

---

## 作者：ningago (赞：1)

先考虑优化建图。在一条（代表速度的）数轴上，点 $x$ 向 $x+1$ 连 $0$ 权边，点 $x$ 向 $x-1$ 连 $1$ 权边。分别表示提速/降速的消耗，称其为普通边。

对于每个特殊铁轨，只需连 $s_i\to t_i$ 的 $0$ 权边即可，题目的要求是从任意点出发，任意点结束，且每条特殊边都被经过恰好 $1$ 次。

跑上下界最小费用可行流，可以获得和状压一个分的好成绩！

先钦定一下起点和终点，不难发现令起点为 $0$，终点为 $+\infty$ 是不影响答案的。现在的问题有点类似从 $0$ 到 $+\infty$ 欧拉路径，但普通边是可以经过零次/多次的。

考虑计算特殊边对每个点带来的 出度 $-$ 入度 的影响，在这条欧拉路径中，最终除了 $0,+\infty$，其它点的 出度 $-$ 入度 都应该 $=0$。

最开始需要从 $0$ 走到 $+\infty$，则每个 $(i,i+1)$ 普通边向右的经过次数都是 $1$，向左为 $0$。

对于一个 $t_i<s_i$ 的特殊边，数轴上 $[t_i,s_i]$ 这个区间内的普通边，向右的经过次数都会加一。

对于一个 $s_i<t_i$ 的特殊边，数轴上 $[s_i,t_i]$ 这个区间内的普通边，向右的经过次数都会抵消一，因为构成了若干个绕圈的环。如果向右的经过次数已经为 $0$，则向左的经过次数会加一。

记（矢量）$d_i$ 表示 $(i,i+1)$ 这条边被经过的次数（向右为正）。

若 $d_i<0$ 则必须要花费 $|d_i|$ 的代价。

考虑欧拉路径的性质：一欧拉路径若与一欧拉**回路**（在点上）相交，则其可合并为同一个欧拉路径。一欧拉回路若与一欧拉回路相交，则其可合并为同一个欧拉回路。

而由于度数守恒，对于每个 $(i,i+1)$，钦定此时这条边恰好被向左/右（与正负有关）走了 $|d_i|$ 次，带上特殊边，此时构成了一条欧拉路径和若干个欧拉回路。与欧拉路径（直接或间接）相交的所有回路都可以合并到欧拉路径上。

这样构造虽然代价最小，但有些欧拉回路与大欧拉路径是相离的（比如数据 $[1\to 5][3\to 4]$）。因为有 $d_i=0$ 的边存在，而它们可以造成一去一回的代价。

用最小生成树贪心合并欧拉回路即可，贪心地，最小生成树只用**在速度离散化后**考虑 $d_i=0$ 的相邻一段。

复杂度 $O(n\log n)$。

```cpp
#define N 400010
#define M 2000010
int n, s[N], t[N];
struct Lish
{
	int sta[N], top;
	void ins(int x) { sta[++top] = x; }
	void build() { std::sort(sta + 1, sta + 1 + top); top = std::unique(sta + 1, sta + 1 + top) - sta - 1; }
	int query(int x) { return std::lower_bound(sta + 1, sta + 1 + top, x) - sta; }
	int operator [] (int x) { return sta[x]; }
}X;
int d[N], fa[N]; int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }
pii sta[N]; int top;
ll plan_roller_coaster(std::vector<int> _s_, std::vector<int> _t_) {
	n = (int) _s_.size();
	for(int i = 1; i <= n; i++) s[i] = _s_[i - 1], X.ins(s[i]);
	for(int i = 1; i <= n; i++) t[i] = _t_[i - 1], X.ins(t[i]);
	X.ins(inf);
	X.build();
	auto merge = [&](int x, int y) -> void
	{
		x = Find(x), y = Find(y);
		fa[x] = y;
	};
	for(int i = 1; i <= n; i++) s[i] = X.query(s[i]), t[i] = X.query(t[i]);
	d[1]++, d[X.top]--;
	merge(1, X.top);
	for(int i = 1; i <= X.top; i++) fa[i] = i;
	for(int i = 1; i <= n; i++)
	{
		d[t[i]]++, d[s[i]]--;
		merge(s[i], t[i]);
	}
	ll ans = 0;
	for(int i = 1; i < X.top; i++)
	{
		d[i] += d[i - 1]; 
		if(d[i]) merge(i, i + 1);
		if(d[i] < 0) ans += 1ll * (-d[i]) * (X[i + 1] - X[i]);
	}
	for(int i = X.top - 1; i; i--) sta[++top] = mkp(X[i + 1] - X[i], i);
	std::sort(sta + 1, sta + 1 + top);
	for(int i = 1; i <= top; i++)
	{
		int x = Find(sta[i].se), y = Find(sta[i].se + 1);
		if(x != y) ans += sta[i].fi, fa[x] = y;
	}
	return ans;
}

```

---

## 作者：MiRaciss (赞：1)

第一步的转换就非常有含金量，考虑遍历完点是个类哈密尔顿回路问题，是难做的。但是我们可以把点转换成边！也就是从 $s_i$ 向 $t_i$ 连边。点数不能太多所以要离散化。这时候问题就变成把图补全成一个欧拉路！但是欧拉通路并不好处理，这是我们发现任何点到 $INF$ 都没有代价所以可以直接变成欧拉回路了。

然后来统计代价。题目所说是减速需要代价，那么反映成边就是我加一条 $i+1 \rightarrow i$ 的边就需要 $1$ 的代价。但是 $i \rightarrow i+1$ 反而不需要代价。这个离散化后遍历一下然后前缀和就可以求出来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int INF=2e9;
int s[200005],t[200005];
int tot=0;
int lsh[400005],sum[400005],pre[400005];
int ans=0,n,m;

int Find(int x){
	if(pre[x]!=x) pre[x]=Find(pre[x]);
	return pre[x];
}

struct zz{
	int x,y,w;
}q[400005];
bool operator <(zz x,zz y){ return x.w<y.w; }

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%lld%lld",&s[i],&t[i]),lsh[++tot]=s[i],lsh[++tot]=t[i];
	n++,s[n]=INF,t[n]=1;
	lsh[++tot]=s[n],lsh[++tot]=t[n];
	sort(lsh+1,lsh+tot+1);tot=unique(lsh+1,lsh+tot+1)-(lsh+1);
	for(int i=1;i<=n;i++) s[i]=lower_bound(lsh+1,lsh+tot+1,s[i])-lsh,t[i]=lower_bound(lsh+1,lsh+tot+1,t[i])-lsh;
	for(int i=1;i<=tot;i++) pre[i]=i;
	for(int i=1;i<=n;i++){
		sum[s[i]]++,sum[t[i]]--;
		if(Find(s[i])!=Find(t[i])) pre[Find(s[i])]=Find(t[i]);
	}
	for(int i=1;i<=tot;i++) sum[i]+=sum[i-1];
	for(int i=1;i<=tot;i++) if(sum[i]){
		if(sum[i]>0) ans+=sum[i]*(lsh[i+1]-lsh[i]);
		if(Find(i)!=Find(i+1)) pre[Find(i)]=Find(i+1);
	}
//	printf("%d\n",ans); 
	int cnt=0;
	for(int i=1;i<tot;i++) if(Find(i)!=Find(i+1)) q[++cnt]=(zz){i,i+1,lsh[i+1]-lsh[i]};
	sort(q+1,q+cnt+1);
	for(int i=1;i<=cnt;i++){
		int x=q[i].x,y=q[i].y,w=q[i].w;
		if(Find(x)==Find(y)) continue;
		pre[Find(x)]=Find(y),ans+=w;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Ydoc770 (赞：0)

### [P6168 \[IOI 2016\] railroad](https://www.luogu.com.cn/problem/P6168)

Hint：考虑增速不计代价，加强限制，并新增 $(inf,1)$ 的点连向起点，转化成欧拉回路。

如果题目没理解错那么思路应该就很清晰了。原题的小于等于限制太松，全部连边会炸空间，转换题意后代价不变。考虑直接把 $s_i,t_i$ 合并排序并离散化。原来 $s_i\rightarrow t_i$ 的边不变，代价为 $0$。现在我们要进行加边使图强连通，认为从左往右连边代价为 $0$，从右往左连边代价为速度之差。

一个重要的转化是排序之后的有向图存在欧拉回路当且仅当跨过每条相邻两点之间边向左和向右的边数相同。证明考虑如果边数不同，那么回路一定会无法遍历所有边，因为向左向右的边在欧拉回路中使一一配对的。那么向左向右边数之差可以差分 $O(n)$ 求得（注意差分一闭一开）。对于向右边数更多的要向左连边，相邻两点之间代价最小直接连肯定是最优的；对于向左边数更多的要向右连边但是根据转化题意边权不计所以不用考虑。

同时也要用并查集维护连通性。当加完上述边后，再扫一遍若相邻两点不连通则加入待选边集中，仿照 [P6628](https://www.luogu.com.cn/problem/P6628) 使用 Kruskal 生成树求得最小的连边代价使图连通。注意这里实际上是相邻两点互相连边，只不过向左边权不计所以总代价就是减速的代价。

时间复杂度 $O(n\log n)$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2.5e3 + 10, maxm = 3.2e6;
int n, m, ed;
ll sum, ans, d[maxn];

int tot;
struct Edge{int u, v, w;} e[maxm];
bool cmp(Edge x, Edge y) {return x.w < y.w;}

int fa[maxn], bel[maxn];
inline void init() {for(int i = 1; i <= n; i++) fa[i] = i; return;}
inline int findf(int u) {if(fa[u] == u) return u; else return fa[u] = findf(fa[u]);}
inline void merge(int u, int v) {int fu = findf(u), fv = findf(v); fa[fu] = fv; return;}

int main() {
	ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> ed; init();   
	for(int i = 1, u, v; i <= m; i++) cin >> u >> v, merge(u, v), d[u]++, d[v]++, sum += abs(u - v);
	
	for(int i = 1; i <= n; i++) bel[i] = findf(i);//每次统计答案继承必须走的边形成的连通块 
	for(int st = 1; st <= n; st++) {
		init(), ans = sum, tot = 0;
		merge(bel[st], bel[ed]), d[st]++, d[ed]++;
		for(int i = 1, lst = 0; i <= n; i++) if(d[i] & 1) {
			if(lst) {for(int j = lst; j < i; j++) merge(bel[j], bel[j + 1]), ans++; lst = 0;}
			else lst = i;//间隔加边 
		}
		for(int i = 1, lst = 0; i <= n; i++) if(d[i]) {
			if(lst && findf(bel[i]) != findf(bel[lst])) e[++tot] = (Edge){lst, i, i - lst};
			lst = i;
		} sort(e + 1, e + tot + 1, cmp);
		for(int i = 1; i <= tot; i++) {
			int u = e[i].u, v = e[i].v, w = e[i].w;
			if(findf(bel[u]) != findf(bel[v])) ans += 2 * w, merge(bel[u], bel[v]);
		} cout << ans << " ";
		d[st]--, d[ed]--;
	}
	
	return 0;
}
```

---

