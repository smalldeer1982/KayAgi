# [IOI 2013] wombats

## 题目描述

布里斯班被变异的袋熊占领，你必须带领大家去安全的地方。

布里斯班的道路像一个大网格，有 $R$ 条东西向的横向道路，从北向南依次编号为 $0,\cdots, (R - 1) $，有 $C$ 条南北向的纵向道路，从西向同东依次编号为 $0,\cdots, (C- 1)$ ，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/xyvkmhhp.png)

袋熊从北方入侵，人们逃向南方。人们可以在横向道路上双方向移动，但是在纵向道路上只能往南面安全的地方走。

横向道路 $P$ 和纵向道路 $Q$ 的交点表示为 $(P, Q)$ 。相邻 $2$ 个交点之间的道路线段上
有一些袋熊，且数目是随时间变化的。 你的任务是引导每个人从最北边（在横向道路 $0$ 上）的指定交点逃到最南端（在横向道路 $R - 1$ 上）的指定交点，路上经过
的袋熊最少。

首先会告诉你网格的规模以及每条道路线段上的袋熊的数量。然后给你一系列 $E$ 事件，每个事件是下列两者之一：
- 变化，表示有些道路线段上的袋熊数量发生变化；
- 逃离, 表示有些人已到达横向道路 $0$ 上指定交点，你必须给他们指出一条路，通往横向道路 $R - 1$ 上指定交点且路上遇到的袋熊最少。

**举例**

![](https://cdn.luogu.com.cn/upload/image_hosting/zn27laze.png)

上图所示的初始地图中有 $3$ 条横向道路 （$ R = 3$ ）和 $4$ 条纵向道路（$ C = 4$ ），每
条道路线段上的袋熊数目如线段上的标记所示。考虑下列事件：
- 一个人到达交点 $A = (0, 2)$ ,希望逃到交点 $B = (2, 1)$ 。如图上虚线所示，他最少需要经过 $2$ 只袋熊。
- 又一个人到达交点 $X = (0, 3)$ ，希望逃到交点 $Y = (2, 3)$ 。如图上虚线所示，他最少需要经过 $7$ 只袋熊。
- 发生 $2$ 个变化事件：纵向道路 $0$ 上最上面那条道路线段上的袋熊数目变为 $5 $，横向道路 $1$ 上中间那条道路线段上的袋熊数目变为 $6 $，见下图中圈出来的两个数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/agnx5ol9.png)

- 第3个人到达交点 $A = (0, 2)$ ，希望逃到交点 $B = (2, 1)$ ，现在他最少需要经过 $5$ 只袋熊，如图中虚线所示。

## 说明/提示

对于 $100\%$ 的数据，$2 \le R \le 5 \times 10^3$，$1 \le C \le 200$，最多 $500$ 个变化，最多 $2 \times 10^5$ 次询问，任意时刻一条道路上最多 $10^3$ 只袋熊。

## 样例 #1

### 输入

```
3 4
0 2 5
7 1 1
0 4 0
0 0 0 2
0 3 4 7
5
3 2 1
3 3 3
2 0 0 5
1 1 1 6
3 2 1
```

### 输出

```
2
7
5
```

# 题解

## 作者：Hanx16Kira (赞：11)

# [P5897 [IOI2013]wombats](https://www.luogu.com.cn/problem/P5897)

%你赛的 T4，写一下题解来加深记忆。~~在 NOIP 模拟赛里面放 IOI 的题，出题人真有你的（~~

考虑设计一种 DP 状态。定义 $f(s,t,i,j)$ 表示从 $s$ 行的第 $i$ 个到 $t$ 行 $j$ 个的最短距离，那么会发现这个状态是可以拆分成为两个等大的子问题 $f(s,m,i,k),f(m,t,k,i)(m=\displaystyle\frac {s + t}2)$ 进行解决，也就是说这个状态设计使得我们可以用线段树维护这一转移。

考虑怎么从 $f(s,m,i,k),f(m,t,k,i)$ 转移到 $f(s,t,i,j)$，可以直接枚举 $k$ 进行转移，这样的转移复杂度是 $\mathcal O(c^3)$ 的，需要优化。注意到这个状态是满足决策单调性的，证明很简单（如图所示，一目了然）：

![](https://cdn.luogu.com.cn/upload/image_hosting/fs6jo5e4.png)

假设 $f(s,t,i,j)$ 的决策点是 $p(i,j)$，那么一定有 $p(i-1,j)\le p(i,j)\le p(i,j+1)$，所以每次枚举 $k$ 只需要在 $[p(i-1,j),p(i,j+1)]$ 内枚举即可，时间复杂度均摊下来就少了一个 $c$，变成了 $\mathcal O(c^2)$。

这下就可以用线段树维护了，每次合并的复杂度是 $\mathcal O(c^2)$，建树的总时间复杂度就是 $\mathcal O(rc^2\log r)$，每次修改操作的时间复杂度是 $\mathcal O(c^2\log r)$，时间上应该可以过。

本以为这样就解决了，然后看到空间限制 256MB，这个做法的空间复杂度是 $\mathcal O(rc^2\log r)$ 的，极限数据下到了 $2\times 10^8$，稳稳的爆炸，因此还需要考虑怎么优化。

一个很巧妙的方式就是将线段树的叶子节点维护的区间长度变成一个阈值 $l$，而非原来的 $1$。这样做就类似分块的思想了，对于每一次修改，对叶子节点上的块进行暴力更改，然后对于整块之间的合并用线段树维护。这样可以大大减少线段树上的节点个数，从而减少了空间复杂度。

块内的暴力修改时间复杂度是 $\mathcal O(c^2l)$ 的，所以建树的总时间复杂度是 $\displaystyle\mathcal O(\frac rlc^2(\log \frac rl + l))$，每一次修改的时间复杂度是 $\mathcal O(c^2(\displaystyle\log\frac rl + l))$，空间复杂度与建树的时间复杂度同阶。实际测试中，$l=20$ 的时候可以取得比较不错的效果，在空间和时间的均衡上很不错。

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Hanx16qwq {
constexpr int _N = 5e3 + 5, _M = 2e2 + 5, _B = 1e3 + 5;
int len = 25, n, m, q;
int d[_N][_M], v[_N][_M];
int pos[_N + 5], bl[_B + 5], br[_B + 5], cnt;
int p[_M + 5][_M + 5];

class Node { // 线段树上节点的类
    public:
        int f[_M][_M]; // 上面的 f，只不过省略了 s 和 t

        Node() {memset(f, 0x3f, sizeof f);}

        void Update(int s, int t) { // 块内暴力
            for (int i = 1; i <= m; i++) {
                for (int j = i, res = 0; j <= m; j++, res += d[s][j - 1]) f[i][j] = res; // 向右
                for (int j = i, res = 0; j >= 1; j--, res += d[s][j]) f[i][j] = res; // 向左
                for (int j = 1; j <= m; j++) f[i][j] += v[s][j]; // 向下
                for (int k = s + 1; k <= t; k++) {
                    for (int j = 2; j <= m; j++) f[i][j] = min(f[i][j], f[i][j - 1] + d[k][j - 1]); // 向右
                    for (int j = m - 1; j ; j--) f[i][j] = min(f[i][j], f[i][j + 1] + d[k][j]); // 向左
                    for (int j = 1; j <= m; j++) f[i][j] += v[k][j]; // 向下
                }
            }
        }
}T[_B];

void Maintain(Node &res, Node a, Node b) { // 合并
    Node ans;
    for (int i = 1; i <= m; i++) // s 处的起点
        for (int j = m; j >= 1; j--) { // t 处的终点
            int st = p[i - 1][j] ? p[i - 1][j] : 1;
            int ed = p[i][j + 1] ? p[i][j + 1] : m;
            for (int k = st; k <= ed; k++) // 决策单调性
                if (ans.f[i][j] > a.f[i][k] + b.f[k][j])
                    ans.f[i][j] = a.f[i][k] + b.f[k][j], p[i][j] = k; // 记录决策点
        }
    res = ans;
}

#define LC (k << 1)
#define RC (k << 1 | 1)
#define mid ((l + r) >> 1)

void Build(int k, int l, int r) {
    if (l == r) return T[k].Update(bl[l], br[l]); // 叶子节点直接暴力做
    Build(LC, l, mid), Build(RC, mid + 1, r);
    Maintain(T[k], T[LC], T[RC]); // 合并
}

void Modify(int k, int l, int r, int p) {
    if (l == r && l == p) return T[k].Update(bl[l], br[l]); // 同上
    if (l > p || r < p) return;
    Modify(LC, l, mid, p), Modify(RC, mid + 1, r, p);
    Maintain(T[k], T[LC], T[RC]);
}

void main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++) cin >> d[i][j];
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++) cin >> v[i][j];
    cnt = (n - 1) / len + 1; // 总块数
    for (int i = 1; i <= cnt; i++)
        bl[i] = (i - 1) * len + 1, br[i] = min(i * len, n); // 预处理块的边界
    for (int i = 1; i <= cnt; i++)
        for (int j = bl[i]; j <= br[i]; j++) pos[j] = i; // 每个点所在的块编号（正常分块写法）
    Build(1, 1, cnt);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        static int opt, a, b;
        cin >> opt >> a >> b; a++, b++;
        if (opt == 1) {
            cin >> d[a][b];
            Modify(1, 1, cnt, pos[a]);
        } else if (opt == 2) {
            cin >> v[a][b];
            Modify(1, 1, cnt, pos[a]);
        } else {
            cout << T[1].f[a][b] << '\n'; // 答案就在线段树顶
        }
    }
}
}

signed main() {
    Hanx16qwq::main();
    return 0;
}
```

---

## 作者：lhm_ (赞：10)

发现行数比较大，列数比较小，考虑用线段树来维护行的情况，记录列对应的信息。

设 $f_{i,j}$ 在当前线段树节点维护的区间，从上边界 $i$ 位置到下边界 $j$ 位置的最小花费，为方便合并，实际处理的为跨过了下边界的最小花费。

每次像 $Floyd$ 一样合并的复杂度为 $O(m^3)$，所以要考虑优化。发现任意两条最优路径不会相交，因为如果相交，其中一条一定能调整为更优的路径。因此转移有决策单调性，这样每次合并的复杂度就为 $O(m^2)$ 了。

发现开不下线段树的空间。于是对行进行分块，对于每块进行 $O(nm^2)$ 的 $DP$ 来处理信息，线段树的叶子节点就是每个块。

设块大小为 $S$，修改次数为 $T$，询问次数为 $Q$，则时间复杂度为 $O(nm^2+Tm^2(\log\frac{n}{S}+S)+Q)$，空间复杂度为 $O(nm+\frac{n}{S}m^2)$。

```cpp
#include<bits/stdc++.h>
#define maxn 5010
#define maxm 210
#define maxt 1010
#define ls (cur<<1)
#define rs (cur<<1|1)
#define mid ((l+r)>>1)
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,q,S=20,root=1;
int bel[maxn],L[maxn],R[maxn],v1[maxn][maxm],v2[maxn][maxm],p[maxm][maxm];
struct node
{
    int f[maxm][maxm];
    node()
    {
        memset(f,0x3f,sizeof(f));
    }
    void get(int u,int d)
    {
        for(int i=1;i<=m;++i)
        {
            for(int j=i,v=0;j<=m;++j,v+=v1[u][j-1]) f[i][j]=v;
            for(int j=i,v=0;j;--j,v+=v1[u][j]) f[i][j]=v;
            for(int j=1;j<=m;++j) f[i][j]+=v2[u][j];
            for(int k=u+1;k<=d;++k)
            {
                for(int j=2;j<=m;++j) f[i][j]=min(f[i][j],f[i][j-1]+v1[k][j-1]);
                for(int j=m-1;j;--j) f[i][j]=min(f[i][j],f[i][j+1]+v1[k][j]);
                for(int j=1;j<=m;++j) f[i][j]+=v2[k][j];
            }
        }
    }
}t[maxt];
node operator +(const node &a,const node &b)
{
    node c;
    memset(p,0,sizeof(p));
    for(int i=1;i<=m;++i)
        for(int j=m;j;--j)
            for(int k=(p[i-1][j]?p[i-1][j]:1);k<=(p[i][j+1]?p[i][j+1]:m);++k)
                if(c.f[i][j]>a.f[i][k]+b.f[k][j])
                    c.f[i][j]=a.f[i][k]+b.f[k][j],p[i][j]=k;
    return c;
}
void build(int l,int r,int cur)
{
    if(l==r)
    {
        t[cur].get(L[l],R[l]);
        return;
    }
    build(l,mid,ls),build(mid+1,r,rs),t[cur]=t[ls]+t[rs];
}
void update(int l,int r,int pos,int cur)
{
    if(l==r)
    {
        t[cur].get(L[l],R[l]);
        return;
    }
    if(pos<=mid) update(l,mid,pos,ls);
    else update(mid+1,r,pos,rs);
    t[cur]=t[ls]+t[rs];
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i)
        for(int j=1;j<m;++j)
            read(v1[i][j]);
    for(int i=1;i<n;++i)
        for(int j=1;j<=m;++j)
            read(v2[i][j]);
    for(int i=1;i<=n;++i) bel[i]=(i-1)/S+1;
    for(int i=1;i<=bel[n];++i) L[i]=S*(i-1)+1,R[i]=S*i;
    R[bel[n]]=n,build(1,bel[n],root),read(q);
    while(q--)
    {
        int opt,x,y,v;
        read(opt),read(x),read(y),x++,y++;
        if(opt==1) read(v1[x][y]),update(1,bel[n],bel[x],root);
        if(opt==2) read(v2[x][y]),update(1,bel[n],bel[x],root);
        if(opt==3) printf("%d\n",t[root].f[x][y]);
    }
    return 0;
}
```

---

## 作者：qwaszx (赞：4)

原题时限20s，luogu一开始开的4s，但一开始的复杂度比较劣只能在6s左右跑出来所以就让神兔开8s了(

以列为下标建立线段树，维护区间内从最上面一行每个点到最下面一行每个点的最短路.暴力枚举中间点合并一次是$O(C^3)$的，总复杂度$O(RC^3+mC^3\log R+q)$，其中$m$是修改次数，$q$是询问次数.并不能跑过去.

考虑优化合并的过程，固定一个起点$S$之后可以发现随着终点的向右移动，转移点是单调的.这个很容易证明，只需要考虑两条路径不会交叉即可，因为如果交叉的话把交点之间的路径换一下会更优.

于是可以使用一个分治做到$O(C^2\log C)$合并，具体地，枚举一个起点，然后$solve(l,r,L,R)$表示用$[L,R]$转移$[l,r]$，然后转移$mid=(l+r)/2$，从$L$到$R$枚举找到最小的最优转移点$p$，分治$solve(l,mid-1,L,p)$和$solve(mid+1,r,p,R)$即可.

然而这还不是最优的，设$dis[i][j]$的转移点为$p[i][j]$，那么显然有$p[i-1][j]\leq p[i][j]\leq p[i][j+1]$，于是使用经典的二维决策单调性优化即可做到$O(C^2)$.这个做法是看了**糯米w**大爷的代码知道的，我本来不会二维的决策单调性优化

现在复杂度是$O(RC^2+mC^2\log R+q)$，时间上信仰一发就跑过去了(

然而空间上不行，线段树需要开一个至少$10000\times 200\times 200$的数组，明显开不下.这个时候考虑一个常用的套路就是线段树底层暴力做，当区间长度小于一个阈值的时候就暴力计算.这个阈值开到16即可，这个时候经试验只需要开到$1000\times 200\times 200$，可以承受.

然而暴力的姿势要正确，不能写成$O(len\cdot C^2\log{(C\cdot len)})$的，~~不然甚至会跑出110s的优秀时间~~.考虑一行一行转移，设$dis[i]$表示只从上一行的点转移到$i$的最短路，$s[i]$表示该行点$i$到点$1$的距离，那么这一行内的转移就是
$$
f[i]=\min\{dis[j]+|s[i]-s[j]|\}
$$
把绝对值按$i$和$j$的大小关系拆一下，然后就是个简单的$dp$，维护一下最小值即可$O(n)$完成.这样暴力计算的复杂度就优化成了$O(len\times C^2)$，跑得就比较快了.

现在复杂度大概是$O(RC^2+m(C^2\log R+16C^2)+q)$，实测跑大概3.5s左右，~~所以不用开大时限了~~.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int INF=1e9;
int a[1050][205][205],tdis[205],ds[5005][205],dh[5005][205],sdh[5005][205],ch[205][205],n,m,qn;
void pushup(int rot,int pos)
{
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			ch[i][j]=0;
	for(int i=1;i<=m;i++)
		for(int j=m;j>=1;j--)
		{
			int l=1,r=m,w=INF,t;
			if(ch[i-1][j])l=max(l,ch[i-1][j]);
			if(ch[i][j+1])r=min(r,ch[i][j+1]);
			for(int k=l;k<=r;k++)
				if((t=a[rot<<1][i][k]+ds[pos][k]+a[rot<<1|1][k][j])<w)w=t,ch[i][j]=k;
			a[rot][i][j]=w; 
		}
}
int abs1(int x){return x>0?x:-x;}
void calc(int f[205][205],int l,int r)
{
	for(int S=1;S<=m;S++)
	{
		for(int i=1;i<=m;i++)tdis[i]=abs1(sdh[l][i]-sdh[l][S]);
		for(int i=l+1;i<=r;i++)
		{
			for(int j=1;j<=m;j++)tdis[j]+=ds[i-1][j];
			int mi=tdis[1];
			for(int j=2;j<=m;j++)tdis[j]=min(tdis[j],mi+sdh[i][j]),mi=min(mi,tdis[j]-sdh[i][j]);
			mi=tdis[m]+sdh[i][m];
			for(int j=m-1;j>=1;j--)tdis[j]=min(tdis[j],mi-sdh[i][j]),mi=min(mi,tdis[j]+sdh[i][j]);
		}
//		int *z=f[S];
		for(int i=1;i<=m;i++)f[S][i]=tdis[i];
	}
}
void build(int rot,int lt,int rt)
{
	if(rt-lt<=16)
	{
		calc(a[rot],lt,rt);
		return;
	}
	int mid=(lt+rt)>>1;
	build(rot<<1,lt,mid),build(rot<<1|1,mid+1,rt);
	pushup(rot,mid);
}
void update(int rot,int lt,int rt,int q)
{
	if(rt-lt<=16)
	{
		calc(a[rot],lt,rt);
		return;
	}
	int mid=(lt+rt)>>1;
	if(q<=mid)update(rot<<1,lt,mid,q);
	else if(q>mid)update(rot<<1|1,mid+1,rt,q);
	pushup(rot,mid);
}
int main()
{
//	freopen("data.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)scanf("%d",&dh[i][j]),sdh[i][j+1]=sdh[i][j]+dh[i][j];
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)scanf("%d",&ds[i][j]);
	build(1,1,n);
	scanf("%d",&qn);
	for(int i=1,opt,x,y,z;i<=qn;i++)
	{
		scanf("%d%d%d",&opt,&x,&y),++x,++y;
		if(opt==3)printf("%d\n",a[1][x][y]);
		else 
		{
			scanf("%d",&z);
			if(opt==1)
			{
				int delta=z-dh[x][y];dh[x][y]=z;
				for(int j=y+1;j<=m;j++)sdh[x][j]+=delta;
				update(1,1,n,x);
			}
			else ds[x][y]=z,update(1,1,n,x);
		}
//		cout<<i<<endl;
	}
}
```

---

## 作者：_HCl_ (赞：2)

同学推荐我做的水黑，顺便水一篇题解。

# P5897 题解

**题意简述**

给定一张网格，动态维护边上的权值（权值非负），每次询问从第一行的点 $(1,x)$ 到最后一行的点 $(n,y)$ 的最短路。

**思路引导**

设 $f_{l,r,x,y}$ 表示从 $(l,x)$ 到 $(r,y)$ 的最短路（注意是越过 $(r,y)$ 的最短路，即还要算上 $(r,y)$ 下面的那条边）。注意到有 $f_{l,r,x,y}=\min(f_{l,k,x,p}+f_{k+1,r,p,y})$，也就是这个东西具有可合并性，因此考虑使用线段树进行维护。

我们可以在线段树的节点存一个矩阵 $f_{x,y}$，意义同上。不难发现这个合并的过程也是类似矩阵乘法的。另外还有一个可以优化的地方。我们发现 $f_{x,y}$ 的路径和 $f_{x+1,y}$ 的路径仅会在最后一行相交，否则其中的一条可以在交叉点后选择另一条成为更优解。因此这个东西具有决策单调性，矩阵乘法的复杂度可以被优化为 $\mathcal{O}(n^2)$。

但是这样的空间是开不下的。考虑到本题时间非常充裕，我们可以分块。即线段树被分到区间长度小于块长时就不继续分治，而是将其作为一个整块进行处理。如果块内的内容被修改，那就整块进行重构。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5,M=205;
int n,m;
int H[N][M],V[N][M],p[M][M];
int st[N],ed[N],bid[N],B;
struct matrix{
	int mat[M][M];
	matrix(){
		memset(mat,0x3f,sizeof(mat));
	}
}t[1005];
matrix operator *(matrix A,matrix B){
	matrix res;
	for(int i=1;i<=m;++i)p[0][i]=0,p[i][m+1]=m;
	for(int i=1;i<=m;++i){
		for(int j=m;j>=1;--j){
			for(int k=p[i-1][j];k<=p[i][j+1];++k){
				if(A.mat[i][k]+B.mat[k][j]<res.mat[i][j]){
					res.mat[i][j]=A.mat[i][k]+B.mat[k][j];
					p[i][j]=k;
				}
			}
		}
	}
	return res;
}
matrix getm(int x){
	matrix res;
	for(int i=1;i<=m;++i){
		res.mat[i][i]=0;
		int sum=0;
		for(int j=i+1;j<=m;++j){
			sum+=H[x][j-1];
			res.mat[i][j]=sum;
		}
		sum=0;
		for(int j=i-1;j>=1;j--){
			sum+=H[x][j];
			res.mat[i][j]=sum;
		}
		for(int j=1;j<=m;++j)res.mat[i][j]+=V[x][j];
	}
	return res;
}
void rebuild(int x){
	int s=st[x],e=ed[x];
	matrix tmp=getm(s);
	for(int i=s+1;i<=e;++i)tmp=tmp*getm(i);
	t[x]=tmp;
}
void build(int x,int l,int r){
	st[x]=l,ed[x]=r;
	if(r-l+1<=B){
		rebuild(x);
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x]=t[x<<1]*t[x<<1|1];
}
void update(int x,int l,int r,int pos){
	if(r-l+1<=B){
		rebuild(x);
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)update(x<<1,l,mid,pos);
	else update(x<<1|1,mid+1,r,pos);
	t[x]=t[x<<1]*t[x<<1|1];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<m;++j)scanf("%d",&H[i][j]);
	}
	for(int i=1;i<n;++i){
		for(int j=1;j<=m;++j)scanf("%d",&V[i][j]);
	}
	B=sqrt(n);
	build(1,1,n);
	int T;
	cin>>T;
	while(T--){
		int op,x,y,z;
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&x,&y,&z);
			x++,y++;
			H[x][y]=z;
			update(1,1,n,x);
		}else if(op==2){
			scanf("%d%d%d",&x,&y,&z);
			x++,y++;
			V[x][y]=z;
			update(1,1,n,x);
		}else{
			scanf("%d%d",&x,&y);
			x++,y++;
			cout<<t[1].mat[x][y]<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# P5897 题解

[Problem Links](https://www.luogu.com.cn/problem/P5897)

## **题目大意**

> 给定一个 $n\times m$ 的网格图，边有边权，移动时只能向左右或下方移动，支持如下两种操作。
>
> - 修改某条边变的边权，共 $C$ 次。
> - 询问从 $(1,x)\to (n,y)$ 的最短路，共 $Q$ 次。
>
> 数据范围：$n\le 5000,m\le 200,C\le 500,Q\le 2\times 10^5$。

## **思路分析**

显然考虑矩阵线段树维护，线段树上每个矩阵维护 $f_{i,j}$ 表示 $(l,i)\to (r,j)$ 的最短路，合并时做 $(\min,+)$ 矩阵乘法。

但这样预处理复杂度就是 $\mathcal O(nm^3\log n)$ 的，考虑优化，注意到 $f_{i,j}=\min\{fl_{i,k}+fr_{k,j}\}$，而转移式中的 $k$ 具有决策单调性，记最优的 $k$ 为 $o_{i,j}$，则有 $o_{i-1,j}\le o_{i,j}\le o_{i,j+1}$，此时矩阵乘法复杂度被优化到了 $\mathcal O(m^2)$。

但此时空间复杂度也是 $\mathcal O(nm^2)$ 的，无法接受，考虑分块以平衡，把连续 $B$ 行的状态压缩到线段树的一个叶子上，每次更新时用 $\mathcal O(Bm^2)$ 的暴力 dp 处理。

时间复杂度 $\mathcal O(nm^2\log n+C\times m^2(B+\log \dfrac nB)+Q)$，空间复杂度 $\mathcal O(\dfrac{nm^2}B)$。

取 $B=10\sim 20$ 均可。

## **代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5005,MAXM=205;
int n,m,q,Wrow[MAXN][MAXM],Wcol[MAXN][MAXM];
struct Info {
    int f[MAXM][MAXM];
    inline void Merge(const Info &X,const Info &Y) {
        static int o[MAXM][MAXM];
        memset(o,0,sizeof(o)),memset(f,0x3f,sizeof(f));
        for(int l=1;l<=m;++l) for(int r=m;r>=1;--r) {
            int L=o[l-1][r]?o[l-1][r]:1,R=o[l][r+1]?o[l][r+1]:m;
            for(int i=L;i<=R;++i) if(X.f[l][i]+Y.f[i][r]<f[l][r]) {
                f[l][r]=X.f[l][i]+Y.f[i][r],o[l][r]=i;
            }
        }
    }
    inline void Init(int x,int y) {
        for(int i=1;i<=m;++i) {
            for(int j=i,sum=0;j<=m;++j) f[i][j]=sum,sum+=Wcol[x][j];
            for(int j=i,sum=0;j>=1;--j) f[i][j]=sum,sum+=Wcol[x][j-1];
            for(int j=1;j<=m;++j) f[i][j]+=Wrow[x][j];
            for(int k=x+1;k<=y;++k) {
                for(int j=2;j<=m;++j) f[i][j]=min(f[i][j],f[i][j-1]+Wcol[k][j-1]);
                for(int j=m-1;j>=1;--j) f[i][j]=min(f[i][j],f[i][j+1]+Wcol[k][j]);
                for(int j=1;j<=m;++j) f[i][j]+=Wrow[k][j];
            }
        }
    }
};
const int B=10,MAXS=1005;
int siz=0,rt,ls[MAXS],rs[MAXS]; //segment Tree
Info tr[MAXS];
int bel[MAXN],lp[MAXN],rp[MAXN],cnt; //blocks
inline void Build(int l,int r,int &p) {
    p=++siz;
    if(l==r) return tr[p].Init(lp[l],rp[r]);
    int mid=(l+r)>>1;
    Build(l,mid,ls[p]),Build(mid+1,r,rs[p]);
    tr[p].Merge(tr[ls[p]],tr[rs[p]]);
}
inline void Modify(int u,int l,int r,int p) {
    if(l==r) return tr[p].Init(lp[u],rp[u]);
    int mid=(l+r)>>1;
    if(u<=mid) Modify(u,l,mid,ls[p]);
    else Modify(u,mid+1,r,rs[p]);
    tr[p].Merge(tr[ls[p]],tr[rs[p]]);
}
signed main() {
    freopen("kangaroo.in","r",stdin);
    freopen("kangaroo.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) for(int j=1;j<m;++j) scanf("%d",&Wcol[i][j]);
    for(int i=1;i<n;++i) for(int j=1;j<=m;++j) scanf("%d",&Wrow[i][j]);
    cnt=(n+B-1)/B;
    fill(lp+1,lp+cnt+1,n+1),fill(rp+1,rp+cnt+1,0);
    for(int i=1;i<=n;++i) {
        bel[i]=(i+B-1)/B;
        lp[bel[i]]=min(lp[bel[i]],i),rp[bel[i]]=max(rp[bel[i]],i);
    }
    Build(1,cnt,rt);
    scanf("%d",&q);
    while(q--) {
        int opt;
        scanf("%d",&opt);
        if(opt==1) {
            int i,j,v;
            scanf("%d%d%d",&i,&j,&v),++i,++j;
            Wcol[i][j]=v;
            Modify(bel[i],1,cnt,rt);
        }
        if(opt==2) {
            int i,j,v;
            scanf("%d%d%d",&i,&j,&v),++i,++j;
            Wrow[i][j]=v;
            Modify(bel[i],1,cnt,rt);
        }
        if(opt==3) {
            int x,y;
            scanf("%d%d",&x,&y),++x,++y;
            printf("%d\n",tr[1].f[x][y]);
        }
    }
    return 0;
}
```

---

## 作者：shinzanmono (赞：2)

# IOI 2013 袋熊

令 $n=R$，$m=C$，$T,Q$ 分别为修改个数和询问个数

首先我们观察到 $C$ 的范围较小，故我们在 $C$ 上~~乱搞~~找找性质。

定义 $dis_{s,x,t,y}(s<t)$ 为从 $s$ 行 $x$ 列到 $t$ 行 $y$ 列的最短路长度。

仔细想想，我们可以想到 $dis_{s,x,t,y}=\min_{i=s+1}^{t-1}\min_{j=1}^m(dis_{s,x,i,j}+dis_{i,j,t,y})$。这是一个 $O(n^3m^3)$ 的 dp 转移，空间复杂度就是 $O(n^2m^2)$，再加上合并和修改的话就直接复杂度爆炸~~顺便卡了评测~~，所以我们考虑优化。

首先，我们可以考虑线段树维护行数为 $[s,t]$ 的信息，这样我们可以将 dp 数组降下两维，于是我们定义 $f_{x,y}$ 为当前 $[s,t]$ 内 $dis_{s,x,t,y}$ 的值。这样空间复杂度就降到了 $O(nm^2)$，但是还是无法满足本题的要求。

于是我们考虑分块，每次修改时暴力修改整块的信息，然后在进行合并，设块长为 $s$，则空间复杂度降到了 $O(\frac{nm^2}s)$，取 $s=25$ 可以不炸空间。

然后我们考虑优化时间，对于整块的修改，我们可以考虑暴力转移，时间复杂度 $O(sm^2)$。我们总共要进行 $T$ 次暴力重构块，故总复杂度为 $O(Tsm^2)$。

然后我们优化合并，可以发现任意两条最优路径不会相交，因为如果相交，其中一条一定能调整为更优的路径。因此转移有决策单调性，这样每次合并的复杂度就为均摊 $O(m^2)$。

然后我们整理一下总的时间复杂度：

- 建树 $O(nm^2)$
- 修改 $O\left(Tm^2(s+\log\frac ns)\right)$
- 查询 $O(Q)$

最后将三个复杂度相加，代入最大值，求值大约在 $6\times10^8$，8s 可过。

附上代码：

```cpp
#include<iostream>
#include<algorithm>
const int sz=5010;
const int msz=210;
int n,m,q,col[sz][msz],row[sz][msz],bl[msz],br[msz],p[msz][msz],belong[sz];
struct ST{
    struct node{
        int f[msz][msz];
        void build(int l,int r){
            for(int i=1;i<=m;i++){
                for(int j=i,sum=0;j<=m;j++)f[i][j]=sum,sum+=col[l][j];
                for(int j=i,sum=0;j>=0;j--)f[i][j]=sum,sum+=col[l][j-1];
                for(int j=1;j<=m;j++)f[i][j]+=row[l][j];
                for(int k=l+1;k<=r;k++){
                    for(int j=2;j<=m;j++)
                        f[i][j]=std::min(f[i][j],f[i][j-1]+col[k][j-1]);
                    for(int j=m-1;j>=1;j--)
                        f[i][j]=std::min(f[i][j],f[i][j+1]+col[k][j]);
                    for(int j=1;j<=m;j++)f[i][j]+=row[k][j];
                }
            }
        }
        void merge(node a,node b){
            for(int i=1;i<=m;i++)std::fill(p[i]+1,p[i]+m+1,0);
            for(int i=1;i<=m;i++)std::fill(f[i]+1,f[i]+m+1,0x7fffffff);
            for(int i=1;i<=m;i++){
                for(int j=m;j>=0;j--){
                    int pl=p[i-1][j]!=0?p[i-1][j]:1;
                    int pr=p[i][j+1]!=0?p[i][j+1]:m;
                    for(int k=pl;k<=pr;k++)
                        if(a.f[i][k]+b.f[k][j]<f[i][j])
                            f[i][j]=a.f[i][k]+b.f[k][j],p[i][j]=k;
                }
            }
        }
    }tree[msz<<2];
    void build(int p,int ln,int rn){
        if(ln==rn)return tree[p].build(bl[ln],br[ln]);
        int mid=ln+rn>>1;
        build(p<<1,ln,mid);
        build(p<<1|1,mid+1,rn);
        tree[p].merge(tree[p<<1],tree[p<<1|1]);
    }
    void modify(int p,int ln,int rn,int pos){
        if(ln==rn)return tree[p].build(bl[ln],br[ln]);
        int mid=ln+rn>>1;
        if(pos<=mid)modify(p<<1,ln,mid,pos);
        else modify(p<<1|1,mid+1,rn,pos);
        tree[p].merge(tree[p<<1],tree[p<<1|1]);
    }
}st;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++)std::cin>>col[i][j];
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)std::cin>>row[i][j];
    int num=n/25;
    for(int i=1;i<=num;i++)
        bl[i]=br[i-1]+1,br[i]=i*25;
    if(br[num]!=n)++num,bl[num]=br[num-1]+1,br[num]=n;
    for(int i=1;i<=num;i++)
        for(int j=bl[i];j<=br[i];j++)belong[j]=i;
    st.build(1,1,num);
    std::cin>>q;
    while(q--){
        int op,x,y,w;
        std::cin>>op>>x>>y,x++,y++;
        if(op==3)std::cout<<st.tree[1].f[x][y]<<"\n";
        else{
            std::cin>>w;
            if(op==1)col[x][y]=w;
            else row[x][y]=w;
            st.modify(1,1,num,belong[x]);
        } 
    }
    return 0;
}
```

---

## 作者：ダブルリーチ (赞：2)

第一道黑 IOI，写一篇题解纪念一下。

下标从 $0$ 开始太不方便，考虑把下标全部增加 $1$，这样就能沿用我们习惯的标准了。

我们发现，虽然查询很多，但是修改很少。

虽然行数很多，但是列数很少。

这说明如果他把查询给放出来，我们必须瞬时进行回答。

如果只有询问，该怎么做？

我们假设 $f_{k,i,j}$ 表示**第一行**第 $i$ 列走到第 $k$ 行第 $j$ 列的最小步数。

我们假设只有一行。

那么对于每个起点 $i$，我们到终点 $j$ 就只能在这个行上走来走去。

显而易见地，每个点要么从它右边走过来，要么从它左边走过来。

考虑完了同一行的问题，该考虑一下向下怎么走了。

假设当前在第 $k$ 行。

首先我们可以给所有 $f$ 数组中第 $k$ 行的部分加上 $v_{k,j}$，代表他走完这行后直接走到第 $k+1$ 行去，**但是还没做好最终的决策**。注意：**此时第 $k$ 行已经做完了决策**。

然后现在我们到了第 $k+1$ 行，我们照样按照上一行的方式进行决策即可。

于是我们就解决了不带修的问题。

现在带修了，单点修改，全局查询。

那这就是线段树上的事了。

我们发现我们前面考虑的 $f_{i,j}$ 是针对每一列的，而行囊括了整个区间。

这意味着每一列的答案我们都有可能用到，但是我们只需要用针对所有行的。

这意味着，我们需要**快速**查询和列相关的答案。

所以我们在每一个线段树节点上都放一个 $f$ 数组！

我们考虑一个节点的 $f_{l,r,i,j}$ 表示**第 $l$ 行**第 $i$ 列走到**第 $r$ 行**第 $j$ 列的最小代价。

当然因为线段树自己就记录了区间，所以实际上 $l$ 和 $r$ 这两维可以不用记录。

在合并区间时，就用上面的方法解决。

但是这里有时间上的问题：我们上面的合并是 $c^2\times r$ 的。如果每次合并区间都按照我们这样合并，那么我们将无法忍受。

所以我们观察性质。

观察下面这张图，假设 $A$ 和 $B$ 都需要去 $C$。

![](https://cdn.luogu.com.cn/upload/image_hosting/cvt0gy5t.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果 $A$ 走了蓝色线路，那么 $B$ 肯定不可能走粉色线路。如果 $B$ 走了粉色线路，那么就意味着要走比 $A$ 更长的路。

那如果粉色线路的下半部分比蓝色线路的下半部分更短呢？

那于是问题来了，为什么 $A$ 不走粉色线路？

所以如果 $B$ 在 $A$ 右边，在合并区间时，他经过的**两个区间之间**的点不会在 $A$ 左边。

所以我们在合并区间时，在枚举当前起点 $i$ 和终点 $j$ 的决策点 $p_{i,j}$ 时，我们只需要跑 $[p_{i-1,j},p_{i,j+1}]$ 之间的点即可。

因此，我们在具体实现时， $j$ 得倒着来。

那么这个为什么就有用了呢？因为最坏的情况无非是 $p_{i,j}=j$。

那么时间复杂度就是 $\sum_{i=1}^c \sum_{j=1}^c p_{i,j+1}-p_{i-1,j}=\sum_{i=1}^n p_{i,n}-p_{1,i}\le n^2$。

不难发现，这个长得很像四边形不等式。

然后就可以把单次合并的时间复杂度降低到 $c^2$ 了。

于是我们也理解了修改操作只有 $500$ 次的原因：一次修改就得有这么大的复杂度。

然后你写完了线段树，会发现空间过不去。

所以得把比较小的空间分成一块，在这用最朴素的暴力进行合并。

这样空间可以除以一个常数，而对时间影响也不大。

所以这样每次查询时，我们只需要在根节点的 $f$ 数组上查询，单次查询的时间复杂度为 $O(1)$。

代码：

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid ((l+r)>>1)
#define ls (now<<1)
#define rs (now<<1|1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int B=5021,N=211,inf=0x3f3f3f3f,block=20;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int bel[B],le[B],ri[B],n,m,h[B][N],v[B][N],q;//把一堆行进行分块
/*
变成XXXXXXX
XXXXXXX

XXXXXXX
XXXXXXX这样
*/ 
struct node{//线段树节点 
	int f[N][N];//最上面的每一列到最下面的每一列的距离 
	node(){ms(f,0x3f);}
	void gen(int u,int d){//给你下界和上界，然后把上下界的所有都给导入进去 
		fs(i,1,m,1){//起点固定了是i 
			int val=0;fs(j,i,m,1) f[i][j]=val,val+=h[u][j];//横向道路gen出来，分别这是枚举起点和终点，就是枚举当前行的
			val=0;ft(j,i,1,-1) f[i][j]=val,val+=h[u][j-1];
			fs(j,1,m,1) f[i][j]+=v[u][j];//横着第一步往下开始走
			fs(cur,u+1,d,1){
				fs(j,2,m,1) f[i][j]=min(f[i][j],f[i][j-1]+h[cur][j-1]);//从左边走过来
				ft(j,m-1,1,-1) f[i][j]=min(f[i][j],f[i][j+1]+h[cur][j]);//从右边走过来
				fs(j,1,m,1) f[i][j]+=v[cur][j];//到了下一层 
			} 
		} 
	}
}tr[(B/block)*4]; 
int jcp[N][N];//每次决策的节点 
node pushup(node a,node b){//把B接到A下面去 
	node res;ms(jcp,0);
	fs(i,1,m,1){//固定了L，那这玩意就成为了一个序列DP 
		ft(j,m,1,-1){//反着来，为了先把jcp[i][j+1]给求出 
			int lef=jcp[i-1][j],rig=jcp[i][j+1];if(!rig) rig=m;if(!lef) lef=1;
			fs(k,lef,rig,1) if(res.f[i][j]>a.f[i][k]+b.f[k][j]) res.f[i][j]=a.f[i][k]+b.f[k][j],jcp[i][j]=k;
		}
	}
	return res;
}
void build(int l,int r,int now){
	if(l==r){
		tr[now].gen(le[l],ri[r]);//这个块扩充上去 
		return; 
	}
	build(l,mid,ls);build(mid+1,r,rs);
	tr[now]=pushup(tr[ls],tr[rs]);
}
void upd(int l,int r,int now,int pos){
	if(l==r){
		tr[now].gen(le[l],ri[r]);//remake
		return;
	} 
	if(pos<=mid) upd(l,mid,ls,pos);
	else upd(mid+1,r,rs,pos);
	tr[now]=pushup(tr[ls],tr[rs]);
} 
int main(){
	n=read(),m=read();
	fs(i,1,n,1) fs(j,1,m-1,1) h[i][j]=read();
	fs(i,1,n-1,1) fs(j,1,m,1) v[i][j]=read();
	fs(i,1,n,1) bel[i]=(i-1)/block+1; 
	fs(i,1,bel[n],1) le[i]=block*(i-1)+1,ri[i]=block*i;
	ri[bel[n]]=n;build(1,bel[n],1);
	q=read();
	while(q--){
		int op=read(),x=read()+1,y=read()+1,w;//单点修改，全局查询
		if(op!=3) w=read();
		if(op==3){printf("%d\n",tr[1].f[x][y]);continue;}
		if(op==1) h[x][y]=w;
		if(op==2) v[x][y]=w;//横着的，还是竖着的？
		upd(1,bel[n],1,bel[x]);//重新修改即可，因为他是在哪里取决于他的行，也同时记录了他到下一块的渠道 
	}
	return 0;
}
```

[后记](https://www.luogu.com.cn/paste/4540ozsb)，是一个小解密，如果解密出来可以私信我。

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18149531)

[P5897 [IOI2013] wombats](https://www.luogu.com.cn/problem/P5897)

有点恐怖。

首先 $R,C$ 很不平衡，考虑用一棵竖着的线段树维护较大的 $R$ 维，每个节点上需要存的是 $C\times C$ 的数组 $d$，$d_{i,j}$ 表示该节点的最上面一行第 $i$ 个到最下面一行第 $j$ 个的最短路。

因为已经处理好了左右儿子内部的最短路，所以只需要枚举 $mid$ 处经过了哪条边。这是一个 $(\min,+)$ 矩阵乘法，暴力做是 $\mathcal O(RC^3+mC^3\log R+q)$，直接爆了。

瓶颈在于合并的复杂度太高。经过观察发现其有决策单调性：

![1.png](https://s2.loli.net/2024/04/21/ANKHDMu3s1y2pU7.png)

如果红色和蓝色分别是 $A\rightarrow C$ 的最短路和 $B\rightarrow D$ 的最短路，则 $A\rightarrow D$ 的最短路一定在三条绿色的线中。假设最短路穿过了红线或者蓝线，则一定会穿过两次。在这两次穿过的点之间，一定是选择原先的最短路最优。所以满足决策单调性，可以用类似区间 DP 的方式做到 $\mathcal O(C^2)$。

但是这样空间会炸：$10000\times 200\times 200$ 个 `int` 肯定开不下。考虑经典卡空间方式：底层 $\log$ 分块，线段树的底层不递归到 $L=R$，而是在 $R-L+1\geq 16$ 的时候就停下来暴力求出上面的点到下面的点的最短路，复杂度还是不变，但是空间除了一只 $\log$，大概只需要开到 $1500\times 200\times 200$。

暴力也有一些细节，不能最暴力的跑最短路 $\mathcal O(16C^2\log(16C))$ 复杂度会爆掉。枚举每个起点，进行朴素 DP，下设 $c_{x,y}$ 表示枚举的起点到 $x,y$ 的最短路：

$$
\begin{aligned}
c_{x,y}&=c_{x-1,y}\\
\text{chkmax}&(c_{x,y},c_{x,y-1}+b_{x,y-1})\\
\text{chkmax}&(c_{x,y},c_{x,y+1}+b_{x,y})\\
\end{aligned}
$$

两个 $\text{chkmax}$ 操作只需要从左向右扫一遍，再从右向左扫一遍，这样一定不会错过最优解。

看起来比较吓人实际上是比较好写的。总时间复杂度是 $\mathcal O(RC^2+mC^2\log R+q)$。

```cpp
int cnt=1,n,m,q,a[5010][210],b[5010][210],p[210][210],c[201];
namespace Segment
{
	#define ls(x) t[x].ls
	#define rs(x) t[x].rs
	#define cost t[ls(x)].d[i][k]+t[rs(x)].d[k][j]+b[mid][k]
	struct{int ls,rs,d[201][201];}t[1510];
	inline void update(int x,int L,int R)
	{
		int mid=L+((R-L)>>1);memset(t[x].d,127,sizeof(t[x].d));
		for(int i=m;i>=1;--i)for(int j=1;j<=m;++j)
		{
			for(int k=p[i][j-1];k<=p[i+1][j];++k)
			if(Mmin(t[x].d[i][j],cost))p[i][j]=k;
		}
	}
	inline void calc(int x,int L,int R)
	{
		for(int i=1;i<=m;++i)
		{
			c[i]=0;
			for(int j=i-1;j>=1;--j)c[j]=c[j+1]+a[L][j];
			for(int j=i+1;j<=m;++j)c[j]=c[j-1]+a[L][j-1];
			for(int j=2;j<=R-L+1;++j)
			{
				for(int k=1;k<=m;++k)c[k]+=b[L+j-2][k];
				for(int k=2;k<=m;++k)Mmin(c[k],c[k-1]+a[L+j-1][k-1]);
				for(int k=m-1;k>=1;--k)Mmin(c[k],c[k+1]+a[L+j-1][k]);
			}
			memcpy(t[x].d[i],c,sizeof(c));
		}
	}
	void build(int p,int L,int R)
	{
		if(R-L+1<=16)return calc(p,L,R);
		int mid=L+((R-L)>>1);
		build(ls(p)=++cnt,L,mid),build(rs(p)=++cnt,mid+1,R),update(p,L,R);
	}
	void change(int p,int L,int R,int x)
	{
		if(!t[p].ls)return calc(p,L,R);
		int mid=L+((R-L)>>1);
		if(x<=mid)change(ls(p),L,mid,x);
		else change(rs(p),mid+1,R,x);
		update(p,L,R);
	}
}
using namespace Segment;
inline void mian()
{
	read(n,m);int opt,x,y,z;
	for(int i=1;i<=m;++i)p[i][m+1]=m,p[i][0]=1,p[m+1][i]=m,p[0][i]=1;
	for(int i=1;i<=n;++i)for(int j=1;j<m;++j)read(a[i][j]);
	for(int i=1;i<n;++i)for(int j=1;j<=m;++j)read(b[i][j]);
	build(1,1,n),read(q);
	while(q--)
	{
		read(opt,x,y),++x,++y;
		if(opt==1)read(z),a[x][y]=z,change(1,1,n,x);
		else if(opt==2)read(z),b[x][y]=z,change(1,1,n,x);
		else write(t[1].d[x][y],'\n');
	}
}
```

---

## 作者：zhongpeilin (赞：0)

首先，我们对于每次修改，想到一个 $O(n \times m ^ 2)$ 的暴力 dp，就是设 $dp_{i, j}$ 表示从最上方的 $i$ 到最下方的 $j$ 的最少经过熊的个数。又因为修改加询问可以拿线段树维护，所以这题通过线段树加 dp 来解决。  
**注：线段树的节点区间 $l \sim r$ 表示行在 $l \sim r$ 之间的答案**。  
那线段树怎么合并呢？这里我们为了方便，改设 $dp_{i, j}$ 表示线段树区间里从最上方 $i$ 到最下方 $j$ 之后，再向下走一下的最小代价。  
接下来我们有一个 $O(C^3)$ 的合并，就是枚举起点终点和中间的位置。这显然是不可接受的，考虑这个东西好像不能用其他的优化，那么考虑一下决策单调性能否优化，设 $p_{i, j}$ 表示 $i \to j$ 的转移，那么有：
$$p_{i - 1, j} \le p_{i, j} \le p_{i, j + 1}$$
因为如果 $p_{i-1, j} > p_{i, j}$ 那么他们在中间或更前一定有个交点，那么根据最优，就可将 $p_{i - 1, j} = p_{i, j}$ 且不劣。   
又由于线段树空间会爆炸，所以我们要均衡一下空间和时间，就将每 `25` 行为一个块，线段树叶子就是每个块，每次修改时就暴力该块中的值即可。  
如果令 $D$ 表示修改个数，$B$ 为块长，则时间复杂度为：$O(m^2 \times n + m^2 \times \frac{n}{B} + D \times B \times m^2 + D \times \log_2^\frac{n}{B} \times m ^ 2)$。  
有疑问的可以看代码 QWQ！  
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0;
	char op = getchar();
	while(op < '0' || op> '9') op = getchar();
	while(op >= '0' && op <= '9'){
		x = x * 10 + (op - '0');
		op = getchar();
	}
	return x;
}

const int B = 25;
int p[205][205];

struct Segment_Tree{
	int dp[205][205];
}tree[805];

int n, m, a[5005][205], b[5005][205];
int L[1005], R[1005];

void push_up(int u){
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			tree[u].dp[i][j] = 1e9;
	for(int i = 1; i <= m; i++){
		for(int j = m; j >= 1; j--){
			int fir = p[i - 1][j] ? p[i - 1][j] : 1; //决策单调性优化
			int sec = p[i][j + 1] ? p[i][j + 1] : m;
			
			for(int k = fir; k <= sec; k++){
				if(tree[u].dp[i][j] > tree[u << 1].dp[i][k] + tree[u << 1 | 1].dp[k][j]){
					tree[u].dp[i][j] = tree[u << 1].dp[i][k] + tree[u << 1 | 1].dp[k][j];
					p[i][j] = k; // record
				}
			}
		}
	}
}

void solve(int u, int l, int r){
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			tree[u].dp[i][j] = 1e9;
	for(int i = 1; i <= m; i++) tree[u].dp[i][i] = 0;
	for(int k = L[l]; k <= R[l]; k++){
		for(int i = 1; i <= m; i++){ //同行的相互更新
			for(int j = 2; j <= m; j++) tree[u].dp[i][j] = min(tree[u].dp[i][j], tree[u].dp[i][j - 1] + a[k][j - 1]);
			for(int j = m - 1; j >= 1; j--) tree[u].dp[i][j] = min(tree[u].dp[i][j], tree[u].dp[i][j + 1] + a[k][j]);
		}
		for(int i = 1; i <= m; i++){ //向下走一步
			for(int j = 1; j <= m; j++){
				tree[u].dp[i][j] += b[k][j];
			}
		}
	}
}

void build(int u, int l, int r){
	if(l == r){
		solve(u, l, r); //暴力求块内
		return ;
	}
	int mid = (l + r) / 2;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	push_up(u);
}

void change(int u, int l, int r, int pos){
	if(r < pos || pos < l) return;
	if(l == r){
		solve(u, l, r); //暴力
		return ;
	}
	int mid = (l + r) / 2;
	change(u << 1, l, mid, pos);
	change(u << 1 | 1, mid + 1, r, pos);
	push_up(u);
}
int main(){
	n = read(); m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < m; j++)
			a[i][j] = read();
	for(int i = 1; i < n; i++)
		for(int j = 1; j <= m; j++)
			b[i][j] = read();
	for(int i = 1; i <= n; i++){ //50一块
		if(L[(i - 1) / B + 1] == 0) L[(i - 1) / B + 1] = i;
		R[(i - 1) / B + 1] = i; 
	}
	int MAXN = (n - 1) / B + 1;
	build(1, 1, MAXN);
	
	int Q = read();
	while(Q--){
		int op, x, y;
		op = read(), x = read() + 1, y = read() + 1;
		if(op == 1){
			a[x][y] = read();
			change(1, 1, MAXN, (x - 1) / B + 1); 
		} else if(op == 2){
			b[x][y] = read();
			change(1, 1, MAXN, (x - 1) / B + 1);
		} else {
			printf("%d\n", tree[1].dp[x][y]); //全部的，就是答案
		}
	}
	return 0;
}

---

