# New Year Domino

## 题目描述

Celebrating the new year, many people post videos of falling dominoes; Here's a list of them: https://www.youtube.com/results?search\_query=New+Years+Dominos

User ainta, who lives in a 2D world, is going to post a video as well.

There are $ n $ dominoes on a 2D Cartesian plane. $ i $ -th domino ( $ 1<=i<=n $ ) can be represented as a line segment which is parallel to the $ y $ -axis and whose length is $ l_{i} $ . The lower point of the domino is on the $ x $ -axis. Let's denote the $ x $ -coordinate of the $ i $ -th domino as $ p_{i} $ . Dominoes are placed one after another, so $ p_{1}&lt;p_{2}&lt;...&lt;p_{n-1}&lt;p_{n} $ holds.

User ainta wants to take a video of falling dominoes. To make dominoes fall, he can push a single domino to the right. Then, the domino will fall down drawing a circle-shaped orbit until the line segment totally overlaps with the x-axis.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/1cd8bce76e7268e84c7286ca2b5288f25521c70b.png)Also, if the $ s $ -th domino touches the $ t $ -th domino while falling down, the $ t $ -th domino will also fall down towards the right, following the same procedure above. Domino $ s $ touches domino $ t $ if and only if the segment representing $ s $ and $ t $ intersects.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/3f86ba9201ab03c6c9c4c879a8ca9ea2e8677f8f.png)See the picture above. If he pushes the leftmost domino to the right, it falls down, touching dominoes (A), (B) and (C). As a result, dominoes (A), (B), (C) will also fall towards the right. However, domino (D) won't be affected by pushing the leftmost domino, but eventually it will fall because it is touched by domino (C) for the first time.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/73c30bfd9b8a146d5c8d1eb8ad442e5fc6ef6a23.png)The picture above is an example of falling dominoes. Each red circle denotes a touch of two dominoes.

User ainta has $ q $ plans of posting the video. $ j $ -th of them starts with pushing the $ x_{j} $ -th domino, and lasts until the $ y_{j} $ -th domino falls. But sometimes, it could be impossible to achieve such plan, so he has to lengthen some dominoes. It costs one dollar to increase the length of a single domino by $ 1 $ . User ainta wants to know, for each plan, the minimum cost needed to achieve it. Plans are processed independently, i. e. if domino's length is increased in some plan, it doesn't affect its length in other plans. Set of dominos that will fall except $ x_{j} $ -th domino and $ y_{j} $ -th domino doesn't matter, but the initial push should be on domino $ x_{j} $ .

## 说明/提示

Consider the example. The dominoes are set like the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/69189c949bbf1e3980e2fd50301d969359a4096f.png)Let's take a look at the 4th plan. To make the 6th domino fall by pushing the 2nd domino, the length of the 3rd domino (whose x-coordinate is 4) should be increased by 1, and the 5th domino (whose x-coordinate is 9) should be increased by 1 (other option is to increase 4th domino instead of 5th also by 1). Then, the dominoes will fall like in the picture below. Each cross denotes a touch between two dominoes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/6a17a43a3d05b4fceb521113b22deae344f88b4a.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/a58f494f30ab4662cf64a0b15656a9dc77793371.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/b71e767b3c7cf778590e571800dc614fef82da50.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/c0207539620df6be43ff32b6c6c47fe615cfd5fd.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/8f6e8505e7e0c11feeece111e6108210f04cb5d4.png)

## 样例 #1

### 输入

```
6
1 5
3 3
4 4
9 2
10 1
12 1
4
1 2
2 4
2 5
2 6
```

### 输出

```
0
1
1
2
```

# 题解

## 作者：7KByte (赞：6)

这里提供一个比洛谷和$\texttt{Codeforces}$题解更好写并且更快的做法。

我们发现推倒第 $i$ 个杆子，一定会在杆子 $next_i$ 处停止。

那么我们从点 $i$ 向点 $next_{i}$ 连边，最后的结果一定是一棵树。注意如果$i$后面的杆子全部倒了则向虚点 $0$ 连边。

那么我们可以倍增优化一下，$f[i][j]$ 表示从第$i$个节点的第$2^j$个祖先，$g[i][j]$表示从节点 $i$ 到节点 $f[i][j]$ 需要的最小花费。

不难在 $\rm O(N\log N)$ 时间内预处理出，并在 $\log N$时间内完成单次查询，时空复杂度$\rm O((N+M)\log N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,m,p[N],l[N],fa[N][20],mx[N],f[N][20];
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d",&p[i],&l[i]);
	scanf("%d",&m);fa[n][0]=0;int t=log2(n);
	pre(i,n-1,1){
		int cur=i+1;mx[i]=max(mx[i],p[i]+l[i]);
		while(cur&&p[cur]<=p[i]+l[i])mx[i]=max(mx[i],mx[cur]),cur=fa[cur][0];
		fa[i][0]=cur;f[i][0]=p[cur]-mx[i];
	}
	rep(i,1,t)rep(x,1,n)f[x][i]=f[x][i-1]+f[fa[x][i-1]][i-1],fa[x][i]=fa[fa[x][i-1]][i-1];
	while(m--){
		int l,r;scanf("%d%d",&l,&r);
		if(fa[l][0]>r)printf("0\n");
		else {
			int ans=0;
			pre(i,t,0)if(fa[l][i]&&fa[l][i]<=r)ans+=f[l][i],l=fa[l][i];
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：UperFicial (赞：2)

> [**CF500E New Year Domino**](https://www.luogu.com.cn/problem/CF500E)

> [不一定更好的阅读体验](https://www.cnblogs.com/UperFicial/p/16775823.html)。

upd：题目连接挂错了。

考虑题目的本质就是，将 $[l,r]$ 多米诺骨牌推倒之后，空位的数量。

这其实是不全面的，因为假若一个骨牌倒在区间 $[3,4]$，另一个骨牌位于 $5$，看似覆盖了所有的区间，实际上第一个骨牌并不能推倒第二个骨牌，所以说需要将每一个骨牌左端点 $+1$。

那么我们可以将左端点降序排序，$\texttt{one-pointer}$ 插入线段，这样就变成了一个区间推平，区间求和的问题，由于值域为 $10^9$ 级别，可以考虑用动态开点线段树维护。

放一个比较清晰的代码：

```cpp
const int MAXN(2e5+10);

int n,m;

struct node{int x,l;};
node a[MAXN];

struct ask{int l,r,id;};
ask q[MAXN];

inline bool cmp(ask x,ask y){return x.l>y.l;}

struct Segment_Tree
{
	struct T{int ls,rs,val;bool tag;};
	T tree[MAXN*30];

	int num;

	inline int lc(int p){return tree[p].ls;}
	inline int rc(int p){return tree[p].rs;}

	inline void push_up(int u)
	{
		tree[u].val=tree[lc(u)].val+tree[rc(u)].val;
		return;
	}

	inline void lazy_tag(int&u,int l,int r)
	{
		if(!u) u=++num;
		tree[u].tag=true,tree[u].val=r-l+1;
		return;
	}

	inline void push_down(int u,int l,int r)
	{
		if(!tree[u].tag) return;
		int mid=(l+r)>>1;
		lazy_tag(tree[u].ls,l,mid),lazy_tag(tree[u].rs,mid+1,r);
		tree[u].tag=false;
		return;
	}

	inline void update(int&u,int l,int r,int ln,int rn)
	{
		if(!u) u=++num;
		if(ln<=l&&r<=rn)
		{
			lazy_tag(u,l,r);
			return;
		}
		push_down(u,l,r);
		int mid=(l+r)>>1;
		if(ln<=mid) update(tree[u].ls,l,mid,ln,rn);
		if(rn>mid) update(tree[u].rs,mid+1,r,ln,rn);
		push_up(u);
		return; 
	}

	inline int query(int u,int l,int r,int ln,int rn)
	{
		int res(0);
		if(!u) return 0;
		if(ln<=l&&r<=rn) return tree[u].val;
		push_down(u,l,r);
		int mid=(l+r)>>1;
		if(ln<=mid) res+=query(lc(u),l,mid,ln,rn);
		if(rn>mid) res+=query(rc(u),mid+1,r,ln,rn);
		return res;
	}
};
Segment_Tree seg;
int rt,output[MAXN];

int main()
{
    n=read();
    int minn=INF;
    rep(i,1,n) a[i].x=read(),a[i].l=read(),minn=Min(minn,a[i].x);
    rep(i,1,n) a[i].x-=minn;
    m=read();
    rep(i,1,m) q[i].l=read(),q[i].r=read(),q[i].id=i;
    sort(q+1,q+1+m,cmp);
    int p(n+1);
    rep(i,1,m)
    {
    	while(p>q[i].l)
    	{
    		--p;
    		seg.update(rt,1,INF,a[p].x+1,a[p].x+a[p].l);
    	}
    	output[q[i].id]=a[q[i].r].x-a[q[i].l].x-seg.query(rt,1,INF,a[q[i].l].x+1,a[q[i].r].x);
    }
    rep(i,1,m) printf("%d\n",output[i]);
    return 0;
}
/*
Date : 2022/10/10
Author : UperFicial
Start coding at : 14:40
finish debugging at : 15:05
*/
```

---

## 作者：Adove (赞：2)

我们先对某个询问单独分析

发现对于区间$(l,r)$询问的答案就是将骨牌全推倒后，未被覆盖的区间长度之和

这个可以离散化后用线段树维护

然而我们仍然发现，左边的骨牌不该对右边的区间询问造成影响

我们按照询问左端点从大到小排序，逐个添加骨牌即可

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1<<18;

int n,m,mx;
int siz[MAXN<<1];
int tree[MAXN<<2];
bool tag[MAXN<<2];
int ans[MAXN];
struct rpg{
	int x,y,id;
}a[MAXN<<1],b[MAXN];

int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}

bool cmp1(rpg a,rpg b){return a.x<b.x;}
bool cmp2(rpg a,rpg b){return a.id<b.id;}
bool cmp3(rpg a,rpg b){return a.x>b.x;}
void build(int k,int l,int r)
{
	if(l==r){tree[k]=siz[l];return;}
	int i=k<<1,mid=l+r>>1;
	build(i,l,mid);build(i|1,mid+1,r);
	tree[k]=tree[i]+tree[i|1];
	return;
}

void ctag(int k,int l,int r,int le,int ri)
{
	if(tag[k]) return;
	if(le<=l&&r<=ri){tree[k]=0;tag[k]=1;return;}
	int i=k<<1,mid=l+r>>1;
	if(le<=mid) ctag(i,l,mid,le,ri);
	if(mid<ri) ctag(i|1,mid+1,r,le,ri);
	tree[k]=tree[i]+tree[i|1];
	if(!tree[k]) tag[k]=1;
	return;
}

int query(int k,int l,int r,int le,int ri)
{
	if(tag[k]) return 0;
	if(le<=l&&r<=ri) return tree[k];
	int i=k<<1,mid=l+r>>1,sum=0;
	if(le<=mid) sum+=query(i,l,mid,le,ri);
	if(mid<ri) sum+=query(i|1,mid+1,r,le,ri);
	return sum;
}

int main()
{
	n=read();
	for(int i=1;i<=n;++i) a[i].x=read(),a[i+n].x=read()+a[i].x,a[i].id=i,a[i+n].id=i+n;
	sort(a+1,a+(n<<1)+1,cmp1);a[1].y=1;
	for(int i=2;i<=n<<1;++i){
		if(a[i].x==a[i-1].x){a[i].y=a[i-1].y;continue;}
		a[i].y=a[i-1].y+1;siz[a[i-1].y]=a[i].x-a[i-1].x;
	}mx=a[n<<1].y;
	sort(a+1,a+(n<<1)+1,cmp2);
	m=read();
	for(int i=1;i<=m;++i) b[i].x=read(),b[i].y=read(),b[i].id=i;
	build(1,1,mx);
	sort(b+1,b+m+1,cmp3);
	int ct=n;
	for(int i=1;i<=m;++i){
		while(ct>=b[i].x){
			ctag(1,1,mx,a[ct].y,a[ct+n].y-1);
			--ct;
		}ans[b[i].id]=query(1,1,mx,a[b[i].x].y,a[b[i].y].y-1);
	}for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：hegm (赞：1)

比较简单的一道题目，提供一种更优复杂度并且简单的写法。

我们考虑离线下来，对于所有询问的 $R$ 进行排序。

我们每次考虑前 $i$ 个骨牌，统计每个骨牌最少需要花费多少才能碰到当前的 $i$ 骨牌，同时统计在碰到 $i$ 的情况下会落到的位置 $x$。

容易发现，有许多骨牌是落到的位置 $x$ 是相同的，那么我们把它们用并查集记录下来。

还有一个性质是：从 $1$ 到 $i$ 的 $x$ 是单调不增的，我们可以用单调栈维护，具体的我们每次加入 $i$ 的时候需要进行两步操作。

1. 把 $x$ 小于 $i$ 位置的骨牌花费代价提升至 $i$ 位置，可以用懒标记对并查集进行整体加法，并且将他们的 $x$ 提升至 $i$ 倒下的位置。

2. 把 $x$ 大于 $i$ 位置但是 小于 $i$ 倒下位置的骨牌的 $x$ 更新为 $i$ 的倒下位置。

最后把在 $i$ 经过这些操作的骨牌和 $i$ 放在同一个并查集里即可。

查询的时候直接访问并查集并且处理懒标记。

排序可以用桶排，并查集复杂度可以做到 $n \alpha(n)$.

跑起来飞快，最优解就是这么做的。

### CODE
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define make make_pair
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int fa[N],w[N],x[N],l[N],q,L[N],R[N],r[N],tot,ans[N],n;
vector<int> v[N];
stack<int> t;
inline pair<int,int> find(int x)
{
	if(fa[x]==x)return make(x,0);
	pair<int,int> s=find(fa[x]);
	fa[x]=s.fi;w[x]+=s.se;s.se=w[x];
	return s;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		x[i]=read();
		l[i]=read();
		fa[i]=i;
	}
	q=read();
	for(int i=1;i<=q;i++)
	{
		L[i]=read();
		R[i]=read();
		v[R[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		while(t.size()&&r[t.top()]<=x[i])
		{
			int s=t.top();t.pop();
			w[s]+=x[i]-r[s];
			fa[s]=i;
		}
		while(t.size()&&r[t.top()]<=x[i]+l[i])
		{
			int s=t.top();t.pop();
			fa[s]=i;
		}
		t.push(i);
		r[i]=x[i]+l[i];
		for(int x:v[i])
		{
			find(L[x]);
			ans[x]=w[L[x]]+w[fa[L[x]]];
		}
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：翼德天尊 (赞：1)

第一个想法是把 $r$ 的答案式列出来：
$$
ans_r=\min_{i=l}^r(\max(x_r-(x_i+l_i),0)+ans_i)
$$
其中 $ans_i$ 为推倒第 $i$ 个骨牌需要的最小代价。但发现这个并不好做。

另一个想法是找到连边关系，即对于每个骨牌预处理出其倒下后能推倒的最右侧骨牌以及推到的位置，形成数轴上的一条线段，则最终 $[l,r]$ 内一定形成若干线段覆盖的形式，答案为未被线段覆盖区间的长度之和。

套路倍增维护以每个位置为起点跳 $2^i$ 条线段后抵达的位置以及代价即可。

预处理部分可以通过线段树来做，维护个区间查询和单点修改即可。时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const int M=20;
int n,q,p[N],len[N],val[N][M],ne[N][M];
struct SegTree{
    int maxn[N<<2];
    void pushup(int i){
        maxn[i]=max(maxn[i<<1],maxn[i<<1|1]);
    }
    void modify(int i,int l,int r,int pos,int k){
        if (l==r){
            maxn[i]=k;
            return;
        }
        int mid=l+r>>1;
        if (pos<=mid) modify(i<<1,l,mid,pos,k);
        else modify(i<<1|1,mid+1,r,pos,k);
        pushup(i);
    }
    int query(int i,int l,int r,int ql,int qr){
        if (ql<=l&&r<=qr) return maxn[i];
        int mid=l+r>>1;
        if (qr<=mid) return query(i<<1,l,mid,ql,qr);
        if (mid<ql) return query(i<<1|1,mid+1,r,ql,qr);
        return max(query(i<<1,l,mid,ql,qr),query(i<<1|1,mid+1,r,ql,qr));
    }
}T;
int read(){
    int w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    n=read();
    for (int i=1;i<=n;i++){
        p[i]=read(),len[i]=read();
    }
    p[n+1]=2e9+1;
    for (int i=n;i>=1;i--){
        int nex=upper_bound(p+1,p+2+n,p[i]+len[i])-p;
        if (nex==n+1) val[i][0]=0,ne[i][0]=0,T.modify(1,1,n,i,p[i]+len[i]);
        else{
            int to=max(T.query(1,1,n,i,nex-1),p[i]+len[i]);
            nex=upper_bound(p+1,p+2+n,p[i]+len[i])-p;
            if (nex==n+1) val[i][0]=0,ne[i][0]=0;
            else val[i][0]=p[nex]-to,ne[i][0]=nex;
            T.modify(1,1,n,i,to);
        }
    }
    for (int j=1;j<=19;j++)
        for (int i=1;i<=n;i++)
            ne[i][j]=ne[ne[i][j-1]][j-1],val[i][j]=val[i][j-1]+val[ne[i][j-1]][j-1];
    int q=read();
    while (q--){
        // cout<<"-------------- : "<<q<<"\n";
        int l=read(),r=read(),ans=0;
        for (int j=19;j>=0;j--)
            if (ne[l][j]!=0&&ne[l][j]<=r){
                // cout<<l<<" "<<j<<" "<<ne[l][j]<<" "<<val[l][j]<<"\n";
                ans+=val[l][j],l=ne[l][j];
            }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：yizhiming (赞：1)

## 题目大意

$n$ 个多米诺骨牌，每个骨牌有两个值 $x_i,h_i$ 表示每个骨牌的坐标和高度，第 $i$ 个骨牌被推倒后，所有满足 $x_j \leq x_i+h_i$ 的骨牌 $j$ 也会被推倒，多次询问，问如果推倒第 $x$ 个骨牌，最少需要花费多少代价才能推倒第 $y$ 个骨牌。

代价定义：可以将任意一个骨牌的高度增加 $1$，花费 $1$ 的代价。

## 题意转换

每次查询下标在 $[l,r]$ 的线段所覆盖的区间中的 $0$ 的个数。我们可以发现，对于每次查询推倒 $l$ 骨牌，那么 $[1,l-1]$ 这些骨牌，就不应该对当前查询有所影响。

所以我们可以考虑将每次查询按左端点从大到小排序，并记一个时间戳，每次判断一下时间戳与查询区间的左端点即可。

## 做法

我们可以用线段树来进行区间覆盖 $1$，区间查询 $0$ 的数量，但是由于值域 $[1,10^9]$，普通线段树难以支持，所以我们用动态开点值域线段树（貌似离散化也可以，但是动态开点真的是暴力美学）。

我们每次插入一个新线段，那么则将区间 $[x_i+1,x_i+h_i]$ 这个区间赋为 $1$。注意要 $+1$，因为每个骨牌自己的坐标不能直接赋为 $1$，必须要由上一个骨牌更新过来才行。

一些必须要加的优化：

查询时，如果当前节点的 $tag$（区间赋值标记）为 $1$，那么说明其子区间所有的值都被赋为 $1$，所以 $0$ 的数量为 $0$，直接返回 $0$ 即可。

对于每个骨牌，要将其坐标全部减去最小的坐标，防止 MLE。

其它的一些细节可以看下代码，写的时候注意一下就好。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
int read(){
	int x=0,f=1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch = getchar();}
	while(ch>='0'&&ch<='9'){x = x*10+ch-'0';ch = getchar();}
	return x*f;
}
const int N = 2e5+5;
struct aaa{
	int lc,rc,sum,tag;
}node[N*40];
int tot=0;
void pushup(int u){
	node[u].sum = node[node[u].lc].sum+node[node[u].rc].sum;
}
void lazy_tag(int u,int l,int r){
	node[u].tag = 1;
	node[u].sum = r-l+1;
}
void pushdown(int u,int l,int r){
	int mid = (l+r)/2;
	if(node[u].lc==0){
		node[u].lc = ++tot;
	}
	if(node[u].rc==0){
		node[u].rc = ++tot;
	}
	lazy_tag(node[u].lc,l,mid);
	lazy_tag(node[u].rc,mid+1,r);
	node[u].tag = 0;
}
void ins(int &u,int l,int r,int ll,int rr){
	if(ll>rr){
		return;
	}
	if(!u){
		u = ++tot;
	}
	if(l==ll&&r==rr){
		lazy_tag(u,l,r);
		return; 
	}
	if(node[u].tag){
		pushdown(u,l,r);
	}
	int mid = (l+r)/2;
	if(rr<=mid){
		ins(node[u].lc,l,mid,ll,rr);
	}else if(ll>mid){
		ins(node[u].rc,mid+1,r,ll,rr);
	}else{
		ins(node[u].lc,l,mid,ll,mid);
		ins(node[u].rc,mid+1,r,mid+1,rr);
	}
	pushup(u);
}
int query(int u,int l,int r,int ll,int rr){
	if(!u){//查询的优化1 
		return r-l+1;
	}
	if(l==ll&&r==rr){
		return r-l+1-node[u].sum;
	}
	if(node[u].tag){//查询的优化2 
		return 0;
	}
	int mid = (l+r)/2;
	if(rr<=mid){
		return query(node[u].lc,l,mid,ll,rr);
	}else if(ll>mid){
		return query(node[u].rc,mid+1,r,ll,rr);
	}else{
		return query(node[u].lc,l,mid,ll,mid)+query(node[u].rc,mid+1,r,mid+1,rr);
	}
}
int n,m;
struct aa{
	int x,h,id;
	bool operator<(const aa&u)const{//骨牌和查询的内容和排序方式差不多 
		return x<u.x;//所以查询按-x加入到数组中方便排序 
	}
}line[N],in[N];
int rt;
int maxn = -1,minn = 1e9;
int ans[N];
int main(){
	n = read();
	int u,v;
	for(int i=1;i<=n;i++){
		line[i].x = read();line[i].h = read();
		minn = min(minn,line[i].x);
	}
	for(int i=1;i<=n;i++){//重点优化 
		line[i].x = line[i].x-minn+1;
	}
	sort(line+1,line+1+n);

	m = read();
	for(int i=1;i<=m;i++){
		in[i].x = -read();in[i].h = read();in[i].id = i;
		maxn = max(maxn,-in[i].x);
	}
	for(int i=n;i>=maxn;i--){//初始骨牌要先加入进去 
		ins(rt,1,1e9,line[i].x+1,min(line[i].x+line[i].h,int(1e9)));
	}
	sort(in+1,in+1+m);
	int k=0;
	for(int i=1;i<=m;i++){
		while(maxn>-in[i].x){
			maxn--;
			ins(rt,1,1e9,line[maxn].x+1,min(line[maxn].x+line[maxn].h,int(1e9)));
		}
		ans[in[i].id] = query(rt,1,1e9,line[-in[i].x].x,line[in[i].h].x)-query(rt,1,1e9,line[-in[i].x].x,line[-in[i].x].x);
		//减去后面那个是为了防止，推倒了骨牌l,但是骨牌l的坐标值为0导致多算了一个0 
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}

```

后记，突然发现查询的时候直接查左端点加一到右端点就好。

---

