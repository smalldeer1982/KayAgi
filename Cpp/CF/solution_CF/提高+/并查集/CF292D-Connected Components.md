# Connected Components

## 题目描述

We already know of the large corporation where Polycarpus works as a system administrator. The computer network there consists of $ n $ computers and $ m $ cables that connect some pairs of computers. In other words, the computer network can be represented as some non-directed graph with $ n $ nodes and $ m $ edges. Let's index the computers with integers from 1 to $ n $ , let's index the cables with integers from 1 to $ m $ .

Polycarpus was given an important task — check the reliability of his company's network. For that Polycarpus decided to carry out a series of $ k $ experiments on the computer network, where the $ i $ -th experiment goes as follows:

1. Temporarily disconnect the cables with indexes from $ l_{i} $ to $ r_{i} $ , inclusive (the other cables remain connected).
2. Count the number of connected components in the graph that is defining the computer network at that moment.
3. Re-connect the disconnected cables with indexes from $ l_{i} $ to $ r_{i} $ (that is, restore the initial network).

Help Polycarpus carry out all experiments and for each print the number of connected components in the graph that defines the computer network through the given experiment. Isolated vertex should be counted as single component.

## 样例 #1

### 输入

```
6 5
1 2
5 4
2 3
3 1
3 6
6
1 3
2 5
1 5
5 5
2 4
3 3
```

### 输出

```
4
5
6
3
4
2
```

# 题解

## 作者：Lily_White (赞：13)

这是一道并查集好题。

我们注意到，每次只是临时断开一些边，然后又把它们接回去了，因此我们没有必要每次都从头建一遍并查集。

这时前缀和的思想就派上用场了。我们维护**并查集的前后缀和**，找到被断开区间**左端点的上一个记录**，把它的前缀和与**右端点到最后的后缀和**相连就可以了。

这样，时间复杂度为$O(kn\log n)$或者$O(kn \alpha(n)$)，和原来的$O(km)$比有了很大的优化（因为$n$的范围只到$500$）。

代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 510;
const int MAXM = 10010; 
struct Disjoint_Set
{
	int fa[MAXN];
	int find(int x)
	{
		if (fa[x] == x)return x;
		return fa[x] = find(fa[x]);
	}
	void merge(int x, int y)
	{
		int xx = find(x), yy = find(y);
		if (xx > yy) swap(xx, yy);
		fa[yy] = xx;
	}
	Disjoint_Set(int n)
	{
		for (int i = 1; i <= n; i++)
			fa[i] = i;
	}
};
vector <Disjoint_Set> l, r;
int n, m;
pair <int, int> input[MAXM];
int main()
{
	cin >> n >> m;
	l.push_back(Disjoint_Set(n)), r.push_back(Disjoint_Set(n));
	for (int i = 1; i <= m; i++)
		cin >> input[i].first >> input[i].second;
	for (int i = 1, j = m; i <= m && j >= 1; i++, j--)
	{
		Disjoint_Set nowl = l.back(), nowr = r.back();
		nowl.merge(input[i].first, input[i].second);
		nowr.merge(input[j].first, input[j].second);
		l.push_back(nowl);
		r.push_back(nowr);
	}
	//luogu
	int q;
	cin >> q;
	while (q--)
	{
		int lbound, rbound;
		cin >> lbound >> rbound;
		Disjoint_Set lset = l[lbound - 1], rset = r[m - rbound];
		Disjoint_Set ans = lset;
		for (int i = 1; i <= n; i++)
			ans.merge(ans.fa[i], rset.fa[i]);
		int res = 0;
		for (int i = 1; i <= n; i++)
			if (ans.fa[i] == i)
				res++; 
		cout << res << endl;
	}
	return 0;
}
```

---

## 作者：gyh20 (赞：8)

提供一个在线，$O((m+q+n)\log m)$ 的做法。

是之前在讨论区讨论出来的这个问题。

我们将边复制两遍，将 $m$ 变成 $2m$，那么每一次询问不包含区间 $[l_i,r_i]$ 等价于每一次询问区间 $[r_i+1,l_i+m-1]$ 这一个区间的连通块个数。

记录 $pre_i$ 表示 $1\sim i-1$ 的所有边构成的生成树中，最靠前的，且在加入 $i$ 这条边形成的环上的边，这一步可以 LCT 维护。

答案可以表示为 $\sum\limits_{i=l}^r [pre_i<l]$，可以主席树维护。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
int ch[400002][2],val[400002],fa[400002],n,rev[400002],stk[400002],tp,mn[400002],f[400002],rt[400002],siz[8000002],ls[8000002],rs[8000002],tot,m,q,typ,a[400002],b[400002],s[400002],la;
inline int root(re int x){return x==f[x]?x:f[x]=root(f[x]);}
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
inline bool ir(re int x){return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;}
inline void Rev(re int x){rev[x]^=1;}
inline void pd(re int x){if(rev[x])swap(ch[x][0],ch[x][1]),Rev(ch[x][0]),Rev(ch[x][1]),rev[x]=0;}
inline void pu(re int x){
	mn[x]=x;
	if(val[mn[ch[x][0]]]<val[mn[x]])mn[x]=mn[ch[x][0]];
	if(val[mn[ch[x][1]]]<val[mn[x]])mn[x]=mn[ch[x][1]];
}
inline void rotate(re int x){
	re int y=fa[x],z=fa[y],R=(ch[y][1]==x);
	if(!ir(y))ch[z][ch[z][1]==y]=x;
	fa[x]=z,fa[y]=x,fa[ch[x][R^1]]=y,ch[y][R]=ch[x][R^1],ch[x][R^1]=y;
	pu(y),pu(x);
}
inline void splay(re int x){
	tp=0,stk[++tp]=x;
	for(re int y=x;!ir(y);y=fa[y])stk[++tp]=fa[y];
	for(re int i=tp;i;--i)pd(stk[i]);
	while(!ir(x)){
		re int y=fa[x],z=fa[y];
		if(!ir(y)){
			if((ch[z][1]==y)^(ch[y][1]==x))rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
inline void access(re int x){for(re int y=0;x;y=x,x=fa[x])splay(x),ch[x][1]=y,pu(x);}
inline void makeroot(re int x){access(x),splay(x),Rev(x);}
inline void split(re int x,re int y){makeroot(x),access(y),splay(y);}
inline void link(re int x,re int y){makeroot(x),fa[x]=y;}
inline void cut(re int x,re int y){split(x,y),ch[y][0]=0,fa[x]=0,pu(y);}
inline void ins(re int &p,re int q,re int l,re int r,re int x){
	if(!p)p=++tot;
	siz[p]=siz[q]+1;
	if(l==r)return;
	re int mid=l+r>>1;
	if(x<=mid)rs[p]=rs[q],ins(ls[p],ls[q],l,mid,x);
	else ls[p]=ls[q],ins(rs[p],rs[q],mid+1,r,x);
}
inline int ask(re int p,re int q,re int l,re int r,re int x){
	if(r<=x)return siz[p]-siz[q];
	re int mid=l+r>>1;
	if(x>mid)return siz[ls[p]]-siz[ls[q]]+ask(rs[p],rs[q],mid+1,r,x);
	else return ask(ls[p],ls[q],l,mid,x);
}
int main(){
	n=read(),m=read(),val[0]=1e9;
	for(re int i=1;i<=n;++i)f[i]=i,val[i]=1e9;
	for(re int i=1,x,y,pos;i<=m+m;++i){
		if(i<=m)a[i]=x=read(),b[i]=y=read();
		else a[i]=x=a[i-m],b[i]=y=b[i-m];
		val[i+n]=i,mn[i+n]=i+n;
		if(x==y){
			ins(rt[i],rt[i-1],0,m+m,m+m);continue;
		}
		if(root(x)^root(y))link(x,i+n),link(i+n,y),f[root(x)]=root(y);
		else{
			split(x,y),pos=mn[y];
			s[i]=pos-n,cut(pos,a[pos-n]),cut(pos,b[pos-n]);
			link(x,i+n),link(i+n,y);
		}
		ins(rt[i],rt[i-1],0,m+m,s[i]);
	}
	q=read();
	while(q--){
		re int y=read()+m-1,x=read()+1;
		printf("%d\n",n-ask(rt[y],rt[x-1],0,m+m,x-1));
	}
}
```


---

## 作者：封禁用户 (赞：8)

先介绍一种通过并查集的写法，每次通过循环把每条可用的边取出，然用并查集求出连通块数量。因为并查集的时间复杂度接近O（1），加上o3优化可以卡常数卡过去。时间：1872ms

代码：
```cpp
#pragma GCC optimize("Ofast",3,"inline")
#include<bits/stdc++.h>
using namespace std;
const int N=505,M=10005;
int n,m,k,x,y,sum;
int a[M],b[M],f[N];
int find(int x)
{
	if(x==f[x])
		return x;
	return f[x]=find(f[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&a[i],&b[i]);
	scanf("%d",&k);
	while(k--)
	{
		scanf("%d%d",&x,&y);
		for(int i=1;i<=n;i++)
			f[i]=i;
		sum=n;
		for(int i=1;i<x;i++)
		{
			if(find(a[i])!=find(b[i]))
			{
				f[f[a[i]]]=f[b[i]];
				sum--;
			}
		}
		for(int i=y+1;i<=m;i++)
		{
			if(find(a[i])!=find(b[i]))
			{
				f[f[a[i]]]=f[b[i]];
				sum--;
			}
		}
		printf("%d\n",sum);
	}
	return 0;
}

```

由于有大量重复计算，我们可以利用前缀和思想来优化。优化后时间仅310ms。

代码：
```cpp
#include<cstdio>
#include<cstring>
#define N 10005
int n,m,Q,l,r,x[N],y[N];
struct DSU{
	int f[505],c;
	int get(int x){return f[x]?f[x]=get(f[x]):x;}
	void Link(int x,int y){x=get(x),y=get(y); if (x!=y) f[x]=y,c++;}
}L[N],R[N],ans;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) scanf("%d%d",x+i,y+i),L[i]=L[i-1],L[i].Link(x[i],y[i]);
	for (int i=m;i;i--) R[i]=R[i+1],R[i].Link(x[i],y[i]);
	scanf("%d",&Q);
	while (Q--){
		scanf("%d%d",&l,&r); DSU ans=L[l-1];
		for (int i=1;i<=n;i++) if (R[r+1].f[i]) ans.Link(i,R[r+1].f[i]);
		printf("%d\n",n-ans.c);
		}
	return 0;
}

```

---

## 作者：Alarm5854 (赞：7)

这道题目的在线做法比较难想，所以要用离线做法。而且删边比加边要难维护，所以要化删边为加边，用并查集维护。

观察数据范围，发现 $n\le 500,m\le 10^4,k\le 2\times 10^4$，所以，可以用时间复杂度为 $O(m^2\log_2n)$ 的做法，实测最慢的点为 $1.37s$。这种做法是这样的：把 $k$ 个询问的 $l_i,r_i$ 都存下来，然后对于相同的 $l_i$ ，把 $r_i$ 和 $i$ 存入同一个 `vector` 中，按 $r_i$ 从大到小排序。

这些处理完之后，枚举 $l$，如果 $l$ 所在的 `vector` 不空，那么初始化 $fa$ 数组，然后合并 $[1,l-1]$ 的边的点。接下来合并后面部分即可。由于 $r_i$ 单调不增，所以该做法正确。

```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 500 + 7;
const int M = 2e4 + 7;
inline int read() {
	int x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
struct edge {
	int u, v; edge(int u = 0, int v = 0): u(u), v(v){}
} e[M];
struct node {
	int r, id; node(int r = 0, int id = 0): r(r), id(id){}
	friend bool operator <(node a, node b) {return a.r < b.r;}//从小到大排序，然后vec数组反着遍历等效于从大到小排序
};
vector<node> vec[M];
int n, m, k, res, f[N], l[M], r[M], ans[M];
int get(int x) {return x == f[x] ? x : f[x] = get(f[x]);}
void merge(int x, int y) {x = get(x), y = get(y); if (x != y) f[x] = y, --res;}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) e[i] = edge(read(), read());
	k = read();
	for (int i = 1; i <= k; ++i)
	l[i] = read(), r[i] = read(), vec[l[i]].push_back(node(r[i], i));
	for (int i = 1; i <= m; ++i) sort(vec[i].begin(), vec[i].end());
	for (int i = 1; i <= m; ++i) {
		if (vec[i].empty()) continue; res = n;
		for (int j = 1; j <= n; ++j) f[j] = j;
		for (int j = 1; j < i; ++j) merge(e[j].u, e[j].v);
		int det = m;
		while (!vec[i].empty()) {
			node u = vec[i].back();
			while (det > u.r) merge(e[det].u, e[det].v), --det;
			ans[u.id] = res; vec[i].pop_back();
		}
	}
	for (int i = 1; i <= k; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：cjZYZtcl (赞：3)

### 思路

考虑分块预处理。

$ans_{l,r}$ 表示一段 $l$ 个块的前缀与一段 $r$ 个块的后缀连边组成的图的连通块个数，$F_{l,r,x}$ 表示一段 $l$ 个块的前缀与一段 $r$ 个块的后缀连边组成的图中第 $x$ 个点的并查集状态。

预处理出这两个东西，复杂度 $O(\frac{m^2 \alpha(n)}{B})$ 。

对于一次询问，先从预处理数组中找到所需的状态，然后在这段前后缀的基础上用并查集扩展，复杂度 $O(k(\alpha(n)B+n))$ 。

取块长 $B = \sqrt{m}$ ，总时间复杂度 $O(\alpha(n)m\sqrt{m}+k(n+\alpha(n)\sqrt{m}))$ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int f[505], F[505], Fn[25][25][505], ans[25][25];

struct Edge {
    int x, y;
} edge[10005];

inline int read() {
    int x = 0, mm = 1;
    char ch = getchar();

    while (!isdigit(ch)) {
        if (ch == '-') mm = -1;
        ch = getchar();
    }

    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }

    return x * mm;
}

inline void write(int x) {
    if (x < 0) {
        putchar('-');
        write(-x);
        return;
    }
    
    if (x >= 10) write(x / 10);
    
    putchar(x % 10 + '0');
}

int gf(int x) {
    return (x == f[x]) ? x : (f[x] = gf(f[x]));
}

signed main() {
    int n = read(), m = read();

    for (int i = 1; i <= m; i++) {
        edge[i].x = read(), edge[i].y = read();
    }

    int len = 500;

    for (int i = 1; i <= n; i++) Fn[0][0][i] = f[i] = i;
    ans[0][0] = n;

    int now = n;

    for (int i = 1; i <= m; i++) {
        int x = edge[i].x, y = edge[i].y;
        int fx = gf(x), fy = gf(y);

        if (fx != fy) {
            f[fx] = fy;
            now--;
        }

        if (i % len == 0) {
            ans[i / len][0] = now;
            for (int j = 1; j <= n; j++) Fn[i / len][0][j] = F[j] = f[j];
            int Now = now;

            for (int j = m; j >= 1; j--) {
                x = edge[j].x, y = edge[j].y;
                fx = gf(x), fy = gf(y);

                if (fx != fy) {
                    f[fx] = fy;
                    Now--;
                }

                if ((m - j + 1) % len == 0) {
                    ans[i / len][(m - j + 1) / len] = Now;
                    for (int k = 1; k <= n; k++) Fn[i / len][(m - j + 1) / len][k] = f[k];
                }
            }

            for (int j = 1; j <= n; j++) f[j] = F[j];
        }
    }

    for (int i = 1; i <= n; i++) f[i] = i;

    now = n;

    for (int i = m; i >= 1; i--) {
        int x = edge[i].x, y = edge[i].y;
        int fx = gf(x), fy = gf(y);

        if (fx != fy) {
            f[fx] = fy;
            now--;
        }

        if ((m - i + 1) % len == 0) {
            ans[0][(m - i + 1) / len] = now;
            for (int j = 1; j <= n; j++) Fn[0][(m - i + 1) / len][j] = f[j];
        }
    }
    
    int q = read();

    while (q--) {
        int l = read() - 1, r = read() + 1;

        int L = l / len, R = (m - r + 1) / len;
        int cnt = ans[L][R];
        for (int i = 1; i <= n; i++) f[i] = Fn[L][R][i];

        int ll = L * len, rr = m - R * len + 1;

        while (ll < l) {
            ll++;
            int x = edge[ll].x, y = edge[ll].y;
            int fx = gf(x), fy = gf(y);

            if (fx != fy) {
                f[fx] = fy;
                cnt--;
            }
        }

        while (rr > r) {
            rr--;
            int x = edge[rr].x, y = edge[rr].y;
            int fx = gf(x), fy = gf(y);

            if (fx != fy) {
                f[fx] = fy;
                cnt--;
            }
        }

        write(cnt);
        putchar('\n');
    }
}
```

---

## 作者：Unnamed114514 (赞：2)

### Update

2022/12/13 修改了复杂度计算时没有乘上并查集的 $O(\log n)$ 的锅。

***

[Problem](https://www.luogu.com.cn/problem/CF292D)

[Solution](https://www.luogu.com.cn/blog/556362/solution-cf292d#)

回滚莫队勇夺最优解（好像没人用这个方法呢）

***

说句实话，现在使用只删不加的回滚比较少了，这就是一道好题。

我们可以将每条边的删除想成一个元素，这样就有 $m$ 个元素。

同时，考虑到添加一个边的删除不好维护，但是删除一条边的删除是很好维护的，于是可以想到自删不加的回滚莫队。

那么对于询问我们就可以直接用回滚的最基本的指针的移动就行了，删除边的删除，也就是添加边，可以用并查集维护。

注意一下左右端点在同一个块内的暴力：如果直接加入其它的边，那么时间复杂度就是 $O(km)$，可能可以过，但是如果常数稍微大一点就不行了。这时我们观察到 $n$ 比较小，于是呢，我们可以多开一个并查集，在每次左端点跳块的时候，把左端点所在块外的元素全部放进并查集，然后我们可以 $O(n)$ 地存储每个集合，然后再暴力查询完成后，我们再 $O(n)$ 复原。

时间复杂度 $O((m\sqrt{k}+kn)\log n)$，但是比其它代码快很多。（？

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int f=0,res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		f|=(ch=='-');
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return f?-res:res;
}
const int maxm=1e4+5,maxk=2e4+5;
int n,m,k,nowans,L,R,u[maxm],v[maxm],block[maxm],ans[maxk],l[maxm],r[maxm];
struct node{
	int l,r,id;
	inline bool operator <(const node &o) const{
		return block[l]<block[o.l]||(block[l]==block[o.l]&&r>o.r);
	}
}f[maxk];
struct Set{
	int fa[505];
	inline void Make(int n){
		for(int i=1;i<=n;++i)
			fa[i]=i;
	}
	int Find(int x){
		return fa[x]=(fa[x]==x?x:Find(fa[x]));
	}
	inline void Union(int u,int v){
		int x=Find(u),y=Find(v);
		fa[x]=y;
	}
}S,T;
inline void del(int t){
	S.Union(u[t],v[t]);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i)
		u[i]=read(),v[i]=read();
	k=read();
	for(int i=1;i<=k;++i)
		f[i]=node({read(),read(),i});
	int len=m/sqrt(k);
	for(int i=1;i<=(m+len-1)/len;++i){
		l[i]=(i-1)*len+1;
		r[i]=min(i*len,m);
		for(int j=l[i];j<=r[i];++j)
			block[j]=i;
	}
	sort(f+1,f+k+1);
	for(int i=1;i<=k;++i){
		if(block[f[i].l]!=block[f[i-1].l]){
			S.Make(n);
			T.Make(n);
			for(int j=1;j<=m;++j)
				if(j<l[block[f[i].l]]||j>r[block[f[i].l]])
					T.Union(u[j],v[j]);
			nowans=n;
			L=l[block[f[i].l]],R=m;
			for(int j=1;j<L;++j)
				S.Union(u[j],v[j]);
		}
		if(block[f[i].l]==block[f[i].r]){
			Set O=T;
			for(int j=l[block[f[i].l]];j<f[i].l;++j)
				O.Union(u[j],v[j]);
			for(int j=f[i].r+1;j<=r[block[f[i].r]];++j)
				O.Union(u[j],v[j]);
			for(int j=1;j<=n;++j)
				ans[f[i].id]+=(O.Find(j)==j);
			continue;
		}
		while(R>f[i].r)
			del(R--);
		Set O=S;
		int E=L;
		while(L<f[i].l)
			del(L++);
		for(int j=1;j<=n;++j)
			ans[f[i].id]+=(S.Find(j)==j);
		S=O,L=E;
	}
	for(int i=1;i<=k;++i)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：lytqwq (赞：2)

[更不好的体验（？）](https://www.cnblogs.com/lytqwq/p/15763769.html)


提供一个 $O(n^2+k)$ 的解法。

我们从左到右加边，发现其实大部分边都是 **无用的** ，因为它不能让联通分量的个数改变，发现 **有用的** 边只有 $O(n)$ 个，那么我们就记录下来有用的边的下标，从右到左加边的情况同理。

预处理前 $i$ 个有用边和后 $j$ 个有用边存在时的联通分量个数，可以做到 $O(n^2)$ ，每次询问就找最近的有用边就完了。

代码如下：

```cpp

// El Psy Kongroo

#include<bits/stdc++.h>
#define ll long long
#define PI pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define ui unsigned int
#define pb push_back
using namespace std;
const int N=10110,P=510;
int n,m,k,fa[N];
int usef[N],usef2[N];
vector<int> u1,u2;
void init(){for(int i=1;i<=n;i++)fa[i]=i;}
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
void join(int x,int y){
	int fx=find(x),fy=find(y);
	fa[fx]=fy;
}
PI edg[N];
int f[P][P];
int wz1[N],wz2[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&edg[i].fi,&edg[i].se);
	}
	init();
	int bef=0;
	u1.push_back(0);
	for(int i=1;i<=m;i++){
		wz1[i]=bef;
		if(find(edg[i].fi)!=find(edg[i].se)){
			join(edg[i].fi,edg[i].se);
			usef[i]=1;
			u1.push_back(i);
			bef++;
		}
	}
	init();
	bef=0;
	u2.push_back(0);
	for(int i=m;i>=1;i--){
		wz2[i]=bef;
		if(find(edg[i].fi)!=find(edg[i].se)){
			join(edg[i].fi,edg[i].se);
			usef2[i]=1;
			u2.push_back(i);
			bef++;
		}
	}
	int len=u1.size(),len2=u2.size();
	for(int i=0;i<len;i++){
		init();
		int ans=n;
		for(int o=1;o<=i;o++){
			join(edg[u1[o]].fi,edg[u1[o]].se);
			ans--;
		}
		for(int p=0;p<len2;p++){
			if(find(edg[u2[p]].fi)!=find(edg[u2[p]].se)){
				join(edg[u2[p]].fi,edg[u2[p]].se);
				ans--;
			}
			f[i][p]=ans;
		}
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",f[wz1[x]][wz2[y]]);
	}
	return 0;
}
```



---

## 作者：Plozia (赞：2)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/112261173)

这道题给各位一种与之前不一样的做法。

首先显然可以使用并查集维护连通块个数，但是我们知道并查集 **不支持删除**，而题目是 **区间询问**，所以：

**不支持删除+区间询问=回滚莫队！**

所以这道题可以用回滚莫队通过，没学过的可以看看 [这篇博文](https://blog.csdn.net/BWzhuzehao/article/details/110941270)。

那么对于这题，取块长 $block = n^{\frac{2}{3}}$，对所有询问进行离线排序之后我们按照回滚莫队的一般套路来处理。

但是：这道题又不是正宗的回滚莫队，因为并查集不支持删除，所以我们需要作一点变通：我们让右指针 $r$ 往回移而不是从块的右边往右移，**而且如果一个询问在块内，我们不需要单独暴力处理，直接一起处理。**

而且在块与块的转移之间，假设当前刚刚做完第 $i$ 块，那么我们就需要将 $[1,(i - 1) * block + 1]$ 里面的所有连边操作完成。因为 $n$ 只有 500，所以不会 TLE。

时间复杂度为 $O(m^{\frac{5}{3}}n)$，但常数稍微有一点大。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 500 + 10, MAXM = 1e4 + 10, MAXK = 2e4 + 10;
int n, m, k, ans[MAXK], fa2[MAXN], fa3[MAXN], total, ys[MAXM], block, x[MAXM], y[MAXM], bnum;
struct node
{
	int l, r, id;
}q[MAXK];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

bool cmp(const node &fir, const node &sec)
{
	if (ys[fir.l] ^ ys[sec.l]) return ys[fir.l] < ys[sec.l];
	return fir.r > sec.r;
}

int gffa3(int x) {return (fa3[x] == x) ? x : fa3[x] = gffa3(fa3[x]);}
void hbfa3(int r) {if (gffa3(x[r]) != gffa3(y[r])) fa3[fa3[x[r]]] = fa3[y[r]];}

int main()
{
	n = read(), m = read(); block = ceil(pow(m, 2.0 / 3.0)); bnum = ceil((double)m / block);
	for (int i = 1; i <= m; ++i) x[i] = read(), y[i] = read();
	for (int i = 1; i <= m; ++i) ys[i] = (i - 1) / block + 1;
	k = read();
	for (int i = 1; i <= k; ++i) q[i].l = read(), q[i].r = read(), q[i].id = i;
	for (int zzh = 1; zzh <= n; ++zzh) fa3[zzh] = zzh;
	sort(q + 1, q + k + 1, cmp);
	int j = 1;
	for (int i = 1; i <= bnum; ++i)
	{
		int l = (i - 1) * block + 1, r = m;
		while (j <= k)
		{
			if (ys[q[j].l] > i) break;
			while (r > q[j].r)
			{
				hbfa3(r--);
			}
			for (int zzh = 1; zzh <= n; ++zzh) fa2[zzh] = fa3[zzh];//复制一份
			while (l < q[j].l)
			{
				hbfa3(l++);
			}
			int total = 0;
			for (int zzh = 1; zzh <= n; ++zzh)
				if (gffa3(zzh) == zzh) total++;
			ans[q[j].id] += total;
			l = (i - 1) * block + 1;
			for (int zzh = 1; zzh <= n; ++zzh) fa3[zzh] = fa2[zzh];//回复数组
			j++;
		}
		for (int zzh = 1; zzh <= n; ++zzh) fa3[zzh] = zzh;
		for (int zzh = 1; zzh <= min(m, i * block); ++zzh) hbfa3(zzh);
	}
	for (int i = 1; i <= k; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：Pentiment (赞：1)

模拟赛时写了个暴力，光荣地 TLE 了；写了个分块，光荣地 WA 了。然后想了一下这不是板吗然后就 A 了。

题目就是让你保留 $[1,l-1]$ 和 $[r+1,m]$ 下标范围内的边。发现有一些边是多余的，产生贡献的至多只有 $n-1$ 条边，考虑求出下标最小生成树和下标最大生成树，只考虑在生成树里的边即可。时间复杂度 $\mathcal O(kn)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505, M = 10005;
int n, m, k, l, r, u[M], v[M], fa[N], siz[N], t[2], e[2][N], ans;
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
void merge(int x, int y) {
	x = get(x), y = get(y);
	if (x == y) return;
	if (siz[x] > siz[y]) swap(x, y);
	fa[x] = y, siz[y] += siz[x];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]);
	for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
	for (int i = 1, c = 0; i <= m; i++) {
		if (get(u[i]) == get(v[i])) continue;
		merge(u[i], v[i]), e[0][++t[0]] = i, c++;
		if (c == n - 1) break;
	}
	for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
	for (int i = m, c = 0; i >= 1; i--) {
		if (get(u[i]) == get(v[i])) continue;
		merge(u[i], v[i]), e[1][++t[1]] = i, c++;
		if (c == n - 1) break;
	}
	scanf("%d", &k);
	while (k--) {
		scanf("%d%d", &l, &r);
		for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
		for (int i = 1; i <= t[0]; i++) {
			if (e[0][i] >= l) break;
			merge(u[e[0][i]], v[e[0][i]]);
		}
		for (int i = 1; i <= t[1]; i++) {
			if (e[1][i] <= r) break;
			merge(u[e[1][i]], v[e[1][i]]);
		}
		ans = 0;
		for (int i = 1; i <= n; i++) if (fa[i] == i) ans++;
		printf("%d\n", ans);
	}
}
```

---

## 作者：Jerrywang09 (赞：1)

### 先说几句

绝对的恶评题。看看楼上都是我根本不懂的算法，那么我也来发一篇题解。

### 解题思路

瞧瞧这标题，不就是连通分量的意思吗？那么，这题肯定与图的连通性有关系。

我们使用边表进行建图。我们同时要存储每条边的编号，可以用 `pair<int, int>。`

对于每次询问，我们只需进行深搜，不走已经切断的边就行。

### 必备优化

如果这就完了，你会发现：

Time limit exceeded on test 16

因为算算时间复杂度，就感觉很悬。

#### 优化 $1$

深搜时，用变量记录第几次深搜，就不需反复清空 $vis$ 数组了。

#### 优化 $2$

全部使用全局变量。

#### 优化 $3$

使用 C 输入输出。

### 奉上代码

```cpp
// 292D Connected Components
#include <bits/stdc++.h>
#define SIZE 505
using namespace std;

vector<pair<int, int>> a[SIZE];
int vis[SIZE]={0};
int tmp=1;
int l, r;
int n, m, T, ltfl=0;

void dfs(int i)
{
	vis[i]=tmp;
	for(auto v:a[i])
	{
		if(l<=v.second && v.second<=r)
			continue;
		if(vis[v.first]!=tmp)
			dfs(v.first);
	}
}

signed main()
{
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		a[x].push_back({y, i});
		a[y].push_back({x, i});
	}
	
	scanf("%lld", &T);
	while(T--)
	{
		scanf("%d %d", &l, &r);
		ltfl=0;
		for(int i=1; i<=n; i++)
			if(vis[i]!=tmp)
			{
				ltfl++;
				dfs(i);
			}
		printf("%d\n", ltfl);
		tmp++;
	}

    return 0;
}
```

---

## 作者：limi_sanhua (赞：1)

思路同上

加一个判断从左往右还是从右往左的判断

那就更~~快乐~~快了

具体康代码与注释

No.1 之 9116ms
```cpp
#pragma GCC optimize("Ofast")
#include<cstdio>
#define u int
#define ri register int
#define NN 10005
#define I __inline__ __attribute__((always_inline))
inline char nc() {
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int in() {
	char ch=nc();ri sum(0);
	while(!(ch>='0'&&ch<='9'))ch=nc();
	while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
	return sum;
}
char f[10];
void out(const int& x) {
	ri tmp(x),s(0);
	while(tmp)f[s++] = tmp%10 + '0',tmp /= 10;
	while(s)putchar(f[--s]);
	putchar('\n');
}
u N,M,S;
struct node {
	u fa[505],num,a,b;
	u getfa(u x) {return !fa[x]?x:fa[x]=getfa(fa[x]);}
	void add(u x,u y) {
		u a=getfa(x),b=getfa(y);
		if(a!=b)fa[a]=b,++num;
	}
} ll[NN],*l=&ll[0],rr[NN],*r=&rr[0];
I void run(node *la,node *ra,u a,u b) {
	node anss=*(la+a),*ans=&anss;
	for(ri k=1; k<=N; ++k)
		if((ra+b)->fa[k])
			ans->add(k,(ra+b)->fa[k]);
	out(N-ans->num);
}
int main() {
	N=in(),M=in();
	for(node *i=l+1; i<=l+M; ++i) {
		*(i)=*(i-1);
		(i)->a=in(),(i)->b=in();
		(i)->add((i)->a,(i)->b);
	}
	for(ri i=1; i<=M; ++i) {
		*(r+i)=*(r+i-1);
		(r+i)->add((l+M-i+1)->a,(l+M-i+1)->b);
	}
	S=in();ri a,b;
	for(ri i=1; i<=S; ++i) {
		a=in(),b=in();
		if(a-1>M-b) run(l,r,a-1,M-b);//就这里判断a-1大一些还是M-b大一些，因为要尽量用前缀和中的数据加速 
		else run(r,l,M-b,a-1);
	}
}
```


---

## 作者：两年打铁 (赞：1)

我终于复读机式问问题搞过了这题。

感谢@fighter 巨佬的改错Orz。

读入每一条边以后，我们先从左到右做一遍合并，记录下每一次合并的状态，再从右往左做一遍合并，从左到右和从右往左都要记录。

然后对于每一个Li 和 Ri ，我们肯定要无视这一段区间给定的边的呀，

那就合并Li-1和Ri+1的两个状态，每次合并的数组的时候我们不能改到原来的数组上。

还有个坑点就是，我们每次查询这个点有没有被合并，我们不能依据它有没有在两个状态中被合并就判断，应该判断的是它有没有在合并后的数组里被合并，不然找父节点会爆栈。

“口胡容易代码难”（引用）

```
#include<bits/stdc++.h>
using namespace std;
void read(int &x)
{
    x=0;
    char ch=getchar();
    int pd=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            pd=-pd;
        }
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    x*=pd;
}
void write(const int &x)
{
    char f[100001];
    int s=0;
    int tmp=x;
    if(tmp==0)
    {
        putchar('0');
        return;
    }
    if(tmp<0)
    {
        tmp=-tmp;
        putchar('-');
    }
    while(tmp>0)
    {
        f[s++]=tmp%10+'0';
        tmp/=10;
    }
    while(s>0)
    {
        putchar(f[--s]);
    }
}

struct dd 
{
    int x,y;
}e[10010];
int getf(int x,int *fp)//搞一个指针我们就可以方便地直接在数组里找了
{
    return fp[x]==x?x:fp[x]=getf(fp[x],fp);
}
int n,m;
int kk;
int l,r;
int	fall[10010];
int ans;
int fl[10010][501],fr[10010][501];
//fl[i][j]记录的是前i条边后的并查集状态，fr就是后i条
int main()
{
    read(n);
    read(m);
    for(register int i=0;i<=n+1;++i)
    {
        fl[0][i]=fr[0][i]=fl[m+1][i]=fr[m+1][i]=i;
    }
    for(register int i=1;i<=m;++i)
    {
        read(e[i].x);
        read(e[i].y);
    }
    for(register int i=1;i<=m;++i)
    {
        for(register int j=1;j<=n;++j)
        {
            fl[i][j]=fl[i-1][j];
        }
        int aa=getf(e[i].x,fl[i]),bb=getf(e[i].y,fl[i]);
        if(aa!=bb)
        {
            fl[i][aa]=bb;
        }
    }
    //这两个就是合并
    for(register int i=m;i>=1;--i)
    {
        for(register int j=1;j<=n;++j)
        {
            fr[i][j]=fr[i+1][j];
        }
        int aa=getf(e[i].x,fr[i]),bb=getf(e[i].y,fr[i]);
        if(aa!=bb)
        {
            fr[i][aa]=bb;
        }
    }
    read(kk);
    while(kk--)
    {
        read(l);
        read(r);
        l--;
        r++;
        for(register int i=1;i<=n;++i)
        {
            fall[i]=fl[l][i];//fall数组就是记录Li-1   Ri+1状态合并后的
        }
        for(register int i=1;i<=n;++i)
        {
            int aa=getf(i,fall),bb=getf(i,fr[r]);
            if(getf(aa,fall)!=getf(bb,fall))
            //这是一个坑点，我就在这里被*爆了，一定要在合并后的数组里判
            {
                fall[aa]=bb;
            }
        }
        ans=0;
        for(register int i=1;i<=n;++i)
        {
            if(fall[i]==i)ans++;
        }
        write(ans);
        puts("");
    }
}
```

---

## 作者：BigJoker (赞：1)

# 0x00 思路

本蒟蒻刚看到此题时无任何思路，可仔细读了一下题目，并且看了一下时间限制，特别长，似乎可以使用暴力来做。

# 0x01 暴力

此题暴力不难，因为题目中明确告诉了你 $l$ 和 $r$ 边只是暂时删去，那么暂时删去就意味着我们不需要去连接这条边，所以我们枚举每一条边，只要不在删除的边的区间内，就连接这条边，连接完毕后统计一下连通块个数即可，当然尽量开一下 o3 优化。

# 0x02 代码

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dep(i,r,l) for(int i=r;i>=l;i--)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;
const int M=1e4+5;
const int N=5e2+5;
int n,m,k,f[N];
struct node{
	int l,r;
}a[M];
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
void unionSet(int x,int y){
	int l1=find(x),r1=find(y);
	if(l1!=r1) f[l1]=r1;
}
int main(){
	scanf("%d %d",&n,&m);
	rep(i,1,m) scanf("%d %d",&a[i].l,&a[i].r);
	scanf("%d",&k);
	rep(t,1,k){
		int ll,rr,ans=0;
		rep(i,1,n) f[i]=i;
		scanf("%d %d",&ll,&rr);
		rep(i,1,m){
			if(i==ll){
				i=rr;
				continue;
			}
			unionSet(a[i].l,a[i].r);
		}
		rep(i,1,n)
			if(f[i]==i) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：lgx57 (赞：0)

一道比较板的题。

先把询问离线存下来，然后用前缀和后缀处理并查集，一个一个加边即可。

注意：这种情况下需要将 $l$ 从小到大排，$r$ 从大到小排。

原因：右边加边是需要从第 $m$ 条边开始加的。

代码很好写，我写完没有 CE 没有 WA 交上去一遍过了。

[code](https://codeforces.com/contest/292/submission/290382526)

---

## 作者：dyc2022 (赞：0)

并查集裸题，并且提供一种在线做法。

考虑如何判断使用并查集判断连通块。对于每一次连边，将边所连接的两个节点所在集合合并。然后在最后判断有多少个集合即可。具体操作：将每个集合变成一棵树，寻找有多少个根节点。

带路径压缩的并查集查找：

```cpp
int find(int k)
{
	if(fa[k]==k)return k;
	return fa[k]=find(fa[k]);
}
```

合并集合：

```cpp
void un(int x,int y)
{
	fa[find(x)]=find(y);
}
```

具体代码流程：每次询问重置并查集，并且跳过 $[ll,rr]$ 区间的边，将其他的边连起来。最后求出有多少连通块，输出结果。

[AC](https://www.luogu.com.cn/record/137146946) 代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
#define N 502
#define M 10020
using namespace std;
int fa[N],n,m,T;
int l[M],r[M];
void init()
{
	for(int i=1;i<=n;i++)fa[i]=i;
}
int find(int k)
{
	if(fa[k]==k)return k;
	return fa[k]=find(fa[k]);
}
void un(int x,int y)
{
	fa[find(x)]=find(y);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&l[i],&r[i]);
	scanf("%d",&T);
	while(T--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		init();
		for(int i=1;i<=m;)
		{
			if(i==x)
			{
				i=y+1;
				continue;
			}
			un(l[i],r[i]);i++;
		}
		int cnt=0;
		for(int i=1;i<=n;i++)cnt+=(fa[i]==i);
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[你谷传送门](https://www.luogu.com.cn/problem/CF292D)

[原题传送门](http://codeforces.com/problemset/problem/292/D)
## 分析
首先一眼看到这个题，第一个想到的肯定是 ~~dfs 暴力~~每次询问时从左往右把边一条一条加进来，再从右往左加一遍，然后维护连通块个数。但是这样的复杂度显然是 $O(mk)$ 的。所以我们需要一些优化。

注意到在加边的时候有些边并不会改变连通块的个数。这些边我先称之为无用边。于是我们可以进行两次预处理，一次从左往右，一次从右往左。每次预处理的时候把所有无用边删去，只存非无用边的编号，放在另一个数组里。然后每次询问的时候就从两边暴力这个数组，像普通并查集一样加边、维护就好了。这样的复杂度一下就降到了 $O(nk\alpha(n))$，因为有用边不会超过 $n-1$ 条。

## 代码

```cpp
#include <iostream>
using namespace std;
struct edge {
    int u, v;
} es[10005];
int fids[10005], eids[10005]; // 两侧的有用边
int f[10005];
int n, m;
int ccnt;
inline void ini() {
    ccnt = n; // 初始连通块共 n 个
    for (int i = 1; i <= n; i++) f[i] = i;
}
int getf(int x) { return (f[x] == x ? x : f[x] = getf(f[x])); }
inline bool murge(int x, int y) {
    x = getf(x), y = getf(y);
    if (x != y) {
        f[x] = y;
        ccnt--;    // 一次成功合并会使连通块个数少1个
        return true; // 返回值为真说明成功进行了合并
    }
    return false; // 反之则没有发生合并
}
int fcnt, ecnt;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &es[i].u, &es[i].v);
    }
    ini();
    for (int i = 1; i <= m; i++) {    // 从左往右枚举
        if (murge(es[i].u, es[i].v)) // 是有用边
            fids[++fcnt] = i;     // 把编号存起来
    }
    ini();
    for (int i = m; i >= 1; i--) {    // 从右往左枚举
        if (murge(es[i].u, es[i].v)) // 是有用边
            eids[++ecnt] = i;     // 把编号存起来
    }
    int q;
    scanf("%d", &q);
    int l, r;
    for (int i = 1; i <= q; i++) {
        ini(); // 每次询问都需要初始化
        scanf("%d%d", &l, &r);
        for (int j = 1; fids[j] < l && j <= fcnt; j++) murge(es[fids[j]].u, es[fids[j]].v); // 从左往右暴力
        for (int j = 1; eids[j] > r && j <= ecnt; j++) murge(es[eids[j]].u, es[eids[j]].v); // 从右往左暴力
        printf("%d\n", ccnt);
    }
    return 0;
}
```

### 完结撒花~~~

---

## 作者：sto_5k_orz (赞：0)

感觉可以评黄。

首先，求联通块的个数可以考虑用并查集。

对于每一个联通块，必定有且仅有一个节点 $i$，满足 $rt_i=i$。

所以每一次，跳过 $l,r$ 做并查集即可。

总复杂度 $O(k(n+m\log n))$，卡卡常，显然可过 2s，CF 神机还是飞快滴。

由于是 CF，需要手开 O2 优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma g++ optimize(2)
#pragma g++ optimize(3)
#pragma g++ optimize("inline")
#pragma g++ optimize("Ofast")
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
namespace SlowIO{
    I int read() {
        int x = 0; char ch = gc();
        W(ch < '0' || ch > '9') ch = gc();
        W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
        return x;
    }
    I void Read(int &x) {x = read();}
    I void Read(int &x, int &y) {Read(x), Read(y);}
    I void write(int x) {
        if(x > 9) write(x / 10);
        pc(x % 10 + '0');
    }
    I void writeln(int x) {write(x); pc('\n');}
    I void Write(int x) {write(x); pc(' ');}
} using namespace SlowIO;
const int N = 505, M = 20005;
int rt[N], n, m, u[N], v[N];
I int find(int x) {return rt[x] == x ? x : rt[x] = find(rt[x]);}
// void merge(int a, int b) {rt[find(b)] = find(a);}
int main() {
    Read(n, m);
	for(int i = 1; i <= m; i++) Read(u[i], v[i]);
    int q; Read(q); W(q--) {
        int l, r; Read(l, r); int ans = 0;
        for(int i = 1; i <= n; i++) rt[i] = i;
        for(int i = 1; i <= m; i++) {
            if(i == l) {i = r; continue;}
            rt[find(v[i])] = find(u[i]);
        }
        for(int i = 1; i <= n; i++) if(rt[i] == i) ans++;
        writeln(ans);
    }
	return 0;
}
```

---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF292D)

## 题目分析

一道基于预处理的并查集暴力优化。

**暴力**：由于删边较难操作，考虑加边。

对于每一个询问，将要用到的边用并查集连上，直接统计连通块数量。复杂度 $O(mk)$。

**优化**：暴力的瓶颈在于每一个询问都要从空白开始连边，造成大量重复计算。

注意题目，删去的边的编号是连续的。设删去 $l\sim r$ 的边，则 $1\sim l-1$ 和 $r+1\sim m$ 的边可以提前预处理。

对于每个询问，合并下 $1\sim l-1$ 和 $r+1\sim m$ 的父亲信息，$O(n)$ 查询连通块数量即可。

复杂度 $O(nk)$。

**具体实现**：用结构体封装不同状态下的父亲信息和查找函数。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 505
#define M 10005
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, m, Q, X[M], Y[M];
struct Node
{
	int fa[N];
	inline int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
	inline void combine(int x, int y) {fa[find(x)] = find(y);}
} L[M], R[M];

int main()
{
	read(n); read(m);
	for (rei i = 1; i <= n; i++) L[0].fa[i] = R[m + 1].fa[i] = i;
	for (rei i = 1; i <= m; i++)
	{
		read(X[i]); read(Y[i]);
		for (rei j = 1; j <= n; j++) L[i].fa[j] = L[i - 1].fa[j];
		if (L[i].find(X[i]) == L[i].find(Y[i])) continue;
		L[i].combine(X[i], Y[i]);
	}
	for (rei i = m; i; i--)
	{
		for (rei j = 1; j <= n; j++) R[i].fa[j] = R[i + 1].fa[j];
		if (R[i].find(X[i]) == R[i].find(Y[i])) continue;
		R[i].combine(X[i], Y[i]);
	}
	read(Q);
	while (Q--)
	{
		int x, y, ret = 0; read(x); read(y);
		Node ans = L[x - 1];
		for (rei i = 1; i <= n; i++) if (ans.find(i) != R[y + 1].find(i)) ans.combine(i, R[y + 1].fa[i]);
		for (rei i = 1; i <= n; i++) if (ans.find(i) == i) ret++;
		printf("%d\n", ret);
	}
	return 0;
}
```


---

## 作者：Merc03 (赞：0)

## 知识

- 并查集

- 前缀和

## 思路

处理联通块个数，很容易想到并查集，但是题目要求删除操作，不好处理。

仔细观察我们发现，$n, m$ 并不大，那么考虑对建立新的并查集，边数很多，但点数也就是并查集大小只有 $n$，那么对边建立 $2 * m$ 个并查集， 通过合并前后缀并查集来实现，即对每一个不相同的 ${fa1}_i$ 和 ${fa2}_i$ 做一次 $merge()$。

复杂度 $O(nm)$。

请看代码。

## Code
```cpp
#include <bits/stdc++.h>
namespace input {
	template <typename Type>
	void read(Type &a) {
		register char ch = getchar();
		while(!isdigit(ch) && ch != '-') ch = getchar();
		bool F = (ch == '-'); a = F ? 0 : ch ^ 48;
		while(isdigit(ch = getchar())) a = (a << 3) + (a << 1) + (ch ^ 48);
		a = F ? -a : a;
	}
}
using input::read;
using namespace std;
const int N = 5e2 + 5;
const int M = 1e4 + 5;
int n, m, k, x[M], y[M];
struct ufs {
	int fa[N], siz[N], size;
	void init(int n) {
		size = n;
		for(int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1;
	}
	int root(int x) {
		return fa[x] == x ? x : fa[x] = root(fa[x]);
	}
	void merge(int x, int y) {
		x = root(x), y = root(y);
		if(x == y) return;
		if(siz[x] < siz[y]) swap(x, y);
		fa[y] = x, --size;
	}
} pre[M], suf[M], sol;
int main() {
	//freopen("1.in", "r", stdin);
	read(n), read(m);
	for(int i = 1; i <= m; ++i) read(x[i]), read(y[i]);
	pre[0].init(n), suf[m + 1].init(n);
	for(int i = 1; i <= m; ++i) pre[i] = pre[i - 1], pre[i].merge(x[i], y[i]);
	for(int i = m; i >= 1; --i) suf[i] = suf[i + 1], suf[i].merge(x[i], y[i]);
	read(k);
	for(int i = 1; i <= k; ++i) {
		int l, r; read(l), read(r);
		sol = pre[l - 1];
		for(int j = 1; j <= n; ++j) {
			sol.merge(sol.root(j), suf[r + 1].root(j));
			sol.merge(sol.root(j), suf[r + 1].root(j));
		}
		printf("%d\n", sol.size);
	}
	return 0;
}
```


---

