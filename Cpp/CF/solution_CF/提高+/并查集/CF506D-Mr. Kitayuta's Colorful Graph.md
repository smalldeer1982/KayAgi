# Mr. Kitayuta's Colorful Graph

## 题目描述

给出一个 $n$ 个点，$m$ 条边的无向图，每条边上是有颜色的。有 $q$ 组询问

对于第 $i$ 组询问，给出点对 $u_i,v_i$， 求有多少种颜色 $c$，满足存在至少一条从 $u_i$ 到 $v_i$ 的路径，使得该路径上的所有边的颜色均为 $c$。

## 说明/提示

$2 \le n \le 10^5$  
$1 \le m,q \le 10^5$  
$1\le x_i,y_i,u_i,v_i \le n$  
$1 \le c_i \le m$

## 样例 #1

### 输入

```
4 5
1 2 1
1 2 2
2 3 1
2 3 3
2 4 3
3
1 2
3 4
1 4
```

### 输出

```
2
1
0
```

## 样例 #2

### 输入

```
5 7
1 5 1
2 5 1
3 5 1
4 5 1
1 2 2
2 3 2
3 4 2
5
1 5
5 1
2 5
1 5
1 4
```

### 输出

```
1
1
1
1
2
```

# 题解

## 作者：henrytb (赞：13)

神仙题。

暴力+暴力=AC。

没错，先想出两个暴力，然后拼起来，你就 AC 了这道题。

**用分块来选择用哪个暴力，可能也是一种正解的做法。**

首先我们能想到最无脑的暴力 1 。

## 暴力 1

对于每种颜色建一个仅含有这一种颜色的边的图，然后用并查集判连通，扫一次所有询问统计贡献。

时间复杂度：首先 $\operatorname{O}(m)$ 的枚举颜色，然后 $\operatorname{O}(n\alpha(n))$ 的建图+并查集（其实建图可以不用，直接并查集就够了），再加上 $\operatorname{O}(q\alpha(n))$ 的处理询问。总时间复杂度 $\operatorname{O}(m\alpha(n)(n+q))$ 。

这显然是过不了这道题的，那么我们再来想另一个暴力。

## 暴力 2

其实只是对暴力 1 的一点修改。

对于每种颜色建一个仅含有这一种颜色的边的图，然后用并查集判连通，在每个连通块内枚举所有的点对 $(u,v)$ ，更新 $(u,v)$ 这个点对的贡献。

这个东西在连通块很小（连通块大小的平方小于 $q$ ）的时候会比暴力 1 更优一些。

时间复杂度：首先 $\operatorname{O}(m)$ 的枚举颜色，然后 $\operatorname{O}(n\alpha(n))$ 的建图+并查集（其实建图可以不用，直接并查集就够了），然后 $\operatorname{O}(n^2\alpha(n))$ 的算贡献。总时间复杂度 $\operatorname{O}(mn^2\alpha(n))$。

## 正解

那么，我们就想到：可不可以在连通块大小的平方小于 $q$ 的时候用暴力 2 ，而在连通块大小的平方大于 $q$ 的时候再用暴力 1 呢？

当然可以。

什么时候一个颜色的图中每个连通块大小的平方都小于 $q$ ？

在 该颜色边数 $<\sqrt{m}$ 的时候，所有这种颜色的所有连通块内点数的平方和不会超过 $n\sqrt n$ 。

于是，暴力 2 就可以胜任这部分的任务，复杂度 $\operatorname{O}(n\alpha(n)\sqrt n)$。

在 该颜色边数 $\ge\sqrt{m}$ 的时候，我们就可以用暴力 1 ，因为此时满足这种情况的颜色数量只会 $\le\sqrt m$。这样的话再扫一遍所有询问，复杂度是 $\operatorname{O}(\sqrt m(q\alpha(q)))$ 的。

这样，两个暴力拼起来，就打出了正解。

考虑实现统计答案时用 `map` 统计，复杂度应乘上 $\operatorname{O}(\log q)$。所以，总复杂度为：$\operatorname{O}((n\alpha(n)\sqrt n+\sqrt m(q\alpha(q)))\log q)$ 。

## Code

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=200005;
int n,m,q;
int num[N];
vector<pair<int,int> > e[N],qs;
map<pair<int,int>,int> ans,lst;
int f[N],sz[N],qto[N];
int find(int i) {return f[i]==i?i:f[i]=find(f[i]);}
void merge(int u,int v) {
    u=find(u);v=find(v);
    if(u!=v) {
        if(sz[u]>sz[v]) {
            f[v]=u;
            sz[u]+=sz[v];
        } else {
            f[u]=v;
            sz[v]+=sz[u];
        }
    }
}
void bao1(int co) {
    rep(i,1,n) f[i]=i,sz[i]=1;
    for(vector<pair<int,int> >::iterator ii=e[co].begin();ii!=e[co].end();++ii) {
        merge(ii->first,ii->second);
    }
    for(vector<pair<int,int> >::iterator ii=qs.begin();ii!=qs.end();++ii) {
        int u=ii->first,v=ii->second;
        u=find(u),v=find(v);
        if(u==v) {
            ++ans[make_pair(ii->first,ii->second)];
        }
    }
}
void bao2(int co) {
    int ps[N],tot=0;
    for(vector<pair<int,int> >::iterator ii=e[co].begin();ii!=e[co].end();++ii) {
        ps[++tot]=ii->first;
        ps[++tot]=ii->second;
    }
    sort(ps+1,ps+tot+1);
    tot=unique(ps+1,ps+tot+1)-ps-1;
    rep(i,1,tot) f[ps[i]]=ps[i],sz[ps[i]]=1;
    for(vector<pair<int,int> >::iterator ii=e[co].begin();ii!=e[co].end();++ii) {
        merge(ii->first,ii->second);
    }
    rep(i,1,tot) {
        rep(j,i+1,tot) {
            bool flg=0;
            int u=find(ps[i]),v=find(ps[j]);
            if(u==v) flg=1;
            if(flg&&ans.count(make_pair(ps[i],ps[j]))) {
                ans[make_pair(ps[i],ps[j])]++;
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,m) {
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        num[c]++;e[c].push_back(make_pair(min(u,v),max(u,v)));
    }
    scanf("%d",&q);
    int now=0;
    rep(i,1,q) {
        int u,v;
        scanf("%d%d",&u,&v);
        if(!ans.count(make_pair(min(u,v),max(u,v)))) {
            qs.push_back(make_pair(min(u,v),max(u,v)));
            ++now;
            lst[make_pair(min(u,v),max(u,v))]=now;
            qto[i]=now;
        }
        else qto[i]=lst[make_pair(min(u,v),max(u,v))];
        ans[make_pair(min(u,v),max(u,v))]=0;
    }
    rep(i,1,m) {
        if(num[i]) {
            if(num[i]>=sqrt(m)) {
                bao1(i);
            } else bao2(i);
        }
    }
    rep(i,1,q) {
        int u=qs[qto[i]-1].first,v=qs[qto[i]-1].second;
        printf("%d\n",ans[make_pair(u,v)]);
    }
    return 0;
}
```

---

## 作者：一念之间、、 (赞：4)

这里提供另外一种不同的做法： `bitset` +小型暴力

想到对于每个颜色连通块，如果询问点同时属于一个颜色连通块集合，则贡献+1。

想法是对于每个点找到属于的连通块，用 `bitset` 合并计算贡献。

发现颜色连通块个数可能达到 $m$ 级别为 $10^5$ ， `bitset` 开不下，考虑优化，一个简单的想法是对于数量较小的连通块可以暴力 $O(n^2)$ 使用 `map` 储存。

设连通块大小为 $s$ 

于是，当 $s\le10$ 的时候选择 $O(n^2)$ 处理出节点，放进 `map` ，剩下的 $s\ge 10^{5-1} = 10^4$ 使用 `bitset` 储存，复杂度 $10^2\times \log n+10^{5+4}/64$轻松跑过。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return*s++;}
//#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
bitset<10005>bit[100005];
map<pair<int,int>,int>mp;//n^2部分，总数不多 
const int xx=1e5+5;
int n,m,fa[xx],vis[xx];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
struct node{int a,b,c;bool operator<(const node&w)const{return c<w.c;};}e[xx];
vector<int>v[xx];
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)e[i].a=read(),e[i].b=read(),e[i].c=read();
	sort(e+1,e+m+1);
	int tt=0;
	for(int i=1;i<=m;i++)
	{
		int l=i,r=i;
		while(r<m&&e[r+1].c==e[r].c)r++;
		vector<int>use;
		for(int j=l;j<=r;j++)
		{
			if(!vis[e[j].a])use.push_back(e[j].a),vis[e[j].a]=1;
			if(!vis[e[j].b])use.push_back(e[j].b),vis[e[j].b]=1;
		}
		for(auto it:use)vis[it]=0,fa[it]=it;
		for(int j=l;j<=r;j++)fa[find(e[j].a)]=find(e[j].b);
		for(auto it:use)v[find(it)].push_back(it);
		for(auto it:use)
		{
			if(v[it].size())
			{
				if(v[it].size()<=10)
				{
					for(auto a:v[it])
					{
						for(auto b:v[it])
						{
							if(a>=b)continue;
							mp[make_pair(a,b)]++;
						}
					}
				}
				else 
				{
					tt++;
					for(auto a:v[it])bit[a][tt]=1;
				}
				v[it].clear();
			}
		}
		i=r;
	}
	int q=read();
	while(q--)
	{
		int a=read(),b=read();
		if(a>b)swap(a,b);
//		cout<<mp[make_pair(a,b)]<<"\n";
		cout<<mp[make_pair(a,b)]+(bit[a]&bit[b]).count()<<"\n";
	}
	return 0;
}
```


---

## 作者：ahawzlc (赞：4)

思路：并查集，对颜色边数采用分块思想， map 统计答案。

----

首先存下所有边，按照颜色排序，这样可以把同种颜色的边放到一起。同时离线询问。

接下来，我们每次选择一种颜色的边，统计这种颜色边的数量 `tot`，进行分类讨论。

1. $tot \ge \sqrt{n}$
2. $tot < \sqrt{n}$

对于第一种情况，出现这种情况的颜色数量不会超过 $\sqrt{n}$ 个。此时我们可以对于颜色边直接做并查集。然后扫一遍询问，如果询问的两个点在同一连通块，那么就会对答案产生 1 的贡献。

对于第二种情况，显然连通块内的点数不会超过 $n\sqrt{n}$ 个，那么我们在做完并查集之后，枚举该种颜色边所连接的点，如果这两个点在同一连通块，那么这对点会对答案产生贡献。

这里就出现了一个问题，点对上的答案怎么对询问的答案产生贡献？

可以考虑用 `map` 存储，建立一个 `pair<int,int>` 对 `int` 的映射，这样可以直接记录点对的贡献，最后在输出答案的时候加进去就可以了。

注意：
1. 因为 `pair` 是有序的，所以在存储时可以将点对 $(x,y)$ 处理成 $x<y$ 。
2. 在第二种情况里，颜色边所连接的点可能有重复，需要去重。

并查集使用路径压缩和按秩合并优化，复杂度 $O(\alpha(n))$ ， `map` 复杂度 $O(\log n)$ ， 分块复杂度 $O(n\sqrt n)$ ，由于并查集复杂度几乎可以不计，所以总复杂度约为 $O(n\sqrt n \log n)$ 。

Code:

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
#define mp make_pair
#define pi pair<int,int>
using namespace std;
const int N=100005;
inline int read() {
	int sum=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		sum=(sum<<3)+(sum<<1)+ch-'0';
		ch=getchar();
	}
	return sum*w;
}
int n,m,q,qx[N],qy[N],f[N],d[N],ans[N],tmp[N],siz;
struct node {
	int x,y,z;
	bool operator < (const node &a) const {
		return z<a.z;
	}
} e[N];
map<pi,int> p;
int find(int x) {//并查集
	return f[x]==x?x:f[x]=find(f[x]);
}
void merge(int x,int y) {
	x=find(x),y=find(y);
	if(x!=y) {
		if(d[x]<d[y]) swap(x,y);
		f[y]=x;
		if(d[x]==d[y]) d[x]++;
	}
}
int main() {
	n=read(),m=read();
	for(int i=1; i<=n; i++) f[i]=i;
	for(int i=1; i<=m; i++) {
		e[i].x=read(),e[i].y=read(),e[i].z=read();
		if(e[i].x>e[i].y) swap(e[i].x,e[i].y);//确保x<y 
	}
	sort(e+1,e+m+1);//按颜色排序 
	q=read();
	for(int i=1; i<=q; i++) {
		qx[i]=read(),qy[i]=read();
		if(qx[i]>qy[i]) swap(qx[i],qy[i]);//离线询问 
	}
	for(int i=1,j=1; i<=m; i=++j) {
		while(e[j].z==e[j+1].z) j++;//j的位置是最后一条该颜色的边 
		for(int k=i; k<=j; k++) merge(e[k].x,e[k].y);//做并查集 
		int tot=j-i+1; 
		if(tot<sqrt(m)) {//分块 
			siz=0;
			for(int k=i; k<=j; k++) tmp[++siz]=e[k].x,tmp[++siz]=e[k].y;//记录该颜色边所连接的点 
			sort(tmp+1,tmp+siz+1);
			siz=unique(tmp+1,tmp+siz+1)-tmp-1;//去重 
			for(int x=1; x<siz; x++)
				for(int y=x+1; y<=siz; y++)
					if(find(tmp[x])==find(tmp[y])) p[mp(tmp[x],tmp[y])]++;//在同一连通块，往点对上添加答案 
		} else for(int k=1; k<=q; k++) ans[k]+=(find(qx[k])==find(qy[k]));//直接扫询问统计答案 
		for(int k=i; k<=j; k++) f[e[k].x]=e[k].x,f[e[k].y]=e[k].y,d[e[k].x]=d[e[k].y]=0;//清空 
	}
	for(int i=1; i<=q; i++) {
		if(p.find(mp(qx[i],qy[i]))!=p.end()) ans[i]+=p[mp(qx[i],qy[i])];//统计点对对答案的贡献 
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

[弱化版](https://www.luogu.com.cn/problem/CF505B)

---

## 作者：Galex (赞：1)

更简单更暴力且复杂度**不那么劣**的做法。

首先一个很自然的想法是对于每个询问枚举颜色 $c$ 是否合法，但显然复杂度是承受不了的。

那么考虑一个优化：只枚举与 $u$ 相邻的边中存在的颜色 $c$。但是只要 $u$ 的度数很大而且与 $u$ 相关的询问很多还是会寄。

那么再考虑一个优化：遇到重复的询问显然不用再算一次，沿用之前的答案即可。这个优化看上去很智障，但其实已经可以做了。

设置阈值 $B$。对于一个询问 $u,v$，设 $deg(u)$ 为 $u$ 的度数，那么如果 $\min(deg(u),deg(v)) \le B$，则暴力做。这部分复杂度是 $O(nB)$。否则，我们发现 $deg(u)>B$ 的 $u$ 最多只有 $\frac n B$ 个，这意味着本质不同的 $u,v$ 至多只有 $\frac{n^2}{B^2}$ 个。对于每组 $u,v$ 暴力枚举 $c$ 即可做到 $O(\frac{n^3}{B^2})$。

于是我们得到了一个两部分复杂度分别为 $O(nB)$ 和 $O(\frac{n^3}{B^2})$ 的算法。平衡一下，取 $B=n^{\frac 2 3}$ 得到总复杂度为 $O(n^{\frac 5 3})$。

为避免空间复杂度爆炸，需要把询问按照颜色离线下来处理。

常数很小，代码很好写。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;

LL read() {
	LL s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

const int MAXN = 100005, B = 2000;

int n, m, q;
vector<pair<int, int> > e[MAXN];
vector<int> col[MAXN];
int idp[MAXN], bp[MAXN], cnt = 0;
int rec[1005][1005];

struct Node {
	int u, v, id;
};

vector<Node> qp[MAXN];
vector<Node> qr[MAXN];
int ans[MAXN];

vector<int> bin;
int fa[MAXN];

void init() {
	for (int i = 1; i <= n; i++)
		fa[i] = i;
}

void clr() {
	for (int x : bin)
		fa[x] = x;
	bin.clear();
}

int get(int x) {
	return x == fa[x] ? x : fa[x] = get(fa[x]);
}

void merge(int x, int y) {
	bin.push_back(x), bin.push_back(y);
	fa[get(x)] = get(y);
}

vector<int> cp[MAXN];

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read(), c = read();
		e[c].push_back(make_pair(x, y));
		col[x].push_back(c), col[y].push_back(c);
		cp[c].push_back(x), cp[c].push_back(y);
	}
	for (int i = 1; i <= m; i++) {
		if (cp[i].empty())
			continue;
		sort(cp[i].begin(), cp[i].end());
		cp[i].resize(unique(cp[i].begin(), cp[i].end()) - cp[i].begin());
	}
	for (int i = 1; i <= n; i++)
		if (col[i].size() > B)
			bp[++cnt] = i, idp[i] = cnt;
	// if (n == 100000)
	// 	cout << cnt << endl;
	init();
	for (int i = 1; i <= m; i++) {
		clr();
		for (pair<int, int> x : e[i])
			merge(x.first, x.second);
		for (int x : bin)
			fa[x] = get(x);
		for (int j = 1; j <= cnt; j++)
			for (int k = 1; k <= cnt; k++)
				rec[j][k] += fa[bp[j]] == fa[bp[k]];
	}
	q = read();
	for (int i = 1; i <= q; i++) {
		int u = read(), v = read();
		if (col[u].size() > col[v].size())
			swap(u, v);
		if (col[u].size() <= B)
			qp[u].push_back((Node){u, v, i});
		else
			ans[i] = rec[idp[u]][idp[v]];//, cout << u << ' ' << v << ' ' << i << endl;
	}
	for (int i = 1; i <= m; i++) {
		vector<Node> qr;
		for (int x : cp[i])
			for (Node j : qp[x])
				qr.push_back(j);
		clr();
		for (pair<int, int> x : e[i])
			merge(x.first, x.second);
		for (int x : bin)
			fa[x] = get(x);
		for (Node x : qr)
			ans[x.id] += fa[x.u] == fa[x.v];
	}
	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：ImALAS (赞：1)

看完题的第一反应是建虚树，然后发现这不是树。但这个思路是对的。对于每个颜色维护出其对应边所构成的子图，用并查集判断连通性即可。时间复杂度 $\mathcal O(qm)$。

考虑到颜色出现次数的总和是 $m$，这是根号分治的经典条件，并且我们容易得出一个预处理方法，因此考虑根号分治。

- 对于出现次数 $\lt \sqrt m$ 的颜色：建出子图后暴力枚举点对计算贡献，时间复杂度 $\mathcal O(m\sqrt m\alpha(n))$。
- 对于出现次数 $\ge \sqrt m$ 的颜色：显然这样的颜色只有 $\mathcal O(\sqrt m)$ 种，提前建出其对应的并查集，每次查询暴力统计即可 $\mathcal O(q\sqrt m\alpha(n))$。

总时间复杂度 $\mathcal O((m+q)\sqrt m\alpha(n))$，我的并查集被卡空间了所以最后写的离线，并且写的是可撤销并查集。所以实现是 $\mathcal O((m+q)\sqrt m\log n)$ 的。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fir first
#define sec second

using i64 = long long;
using pii = std::pair<int, int>;

const int maxn = 1e5 + 5, S = 320;
int n, m, q, id[maxn], col[maxn], cnt, b[maxn], tot, ans[maxn], Qu[maxn], Qv[maxn], pre[maxn], sz[maxn];
pii stk[maxn]; int tp;
std::vector<pii> G[maxn];
std::map<pii, int> mp;
bool vis[maxn], ins[maxn];

int find(int x) {
	while(x != pre[x]) x = pre[x];
	return x;
}
void merge(int x, int y) {
	x = find(x); y = find(y);
	if(x == y) return ;
	if(sz[x] > sz[y])
		std::swap(x, y);
	stk[++ tp] = {x, sz[y]};
	pre[x] = y; sz[y] += sz[x] == sz[y];
	return ;
}
void remove() {
	while(tp) {
		auto& [x, sy] = stk[tp --];
		sz[pre[x]] = sy; pre[x] = x;
	}
	return ;
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1;i <= m;++ i) {
		int u, v, c; scanf("%d %d %d", &u, &v, &c);
		G[c].pb(u, v);
	}
	for(int i = 1;i <= n;++ i)
		pre[i] = i, sz[i] = 1;
	for(int i = 1;i <= m;++ i) {
		if(G[i].size() < S) {
			tot = 0;
			for(auto& [u, v] : G[i]) {
				merge(u, v);
				if(!ins[u]) b[++ tot] = u;
				if(!ins[v]) b[++ tot] = v;
				ins[u] = ins[v] = true;
			}
			std::sort(b + 1, b + 1 + tot);
			for(int i = 1;i < tot;++ i)
				for(int j = i + 1;j <= tot;++ j)
					if(find(b[i]) == find(b[j]))
						++ mp[{b[i], b[j]}];
			for(int i = 1;i <= tot;++ i)
				ins[b[i]] = false;
			remove();
		}
	}
	scanf("%d", &q);
	for(int i = 1;i <= q;++ i) {
		scanf("%d %d", &Qu[i], &Qv[i]);
		if(Qu[i] > Qv[i])
			std::swap(Qu[i], Qv[i]);
		ans[i] = mp[{Qu[i], Qv[i]}];
	}
	for(int i = 1;i <= m;++ i) {
		if(G[i].size() < S)
			continue ;
		for(auto& [u, v] : G[i])
			merge(u, v);
		for(int j = 1;j <= q;++ j)
			if(find(Qu[j]) == find(Qv[j]))
				++ ans[j];
		remove();
	}
	for(int i = 1;i <= q;++ i)
		printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：intel_core (赞：1)

很明显，这个题应该不同颜色分开考虑。

一种显然的 $O(n^2)$ 暴力：对于一种颜色 $c$ ，把所有颜色为 $c$ 的边取出来，会形成若干个连通块；同一个连通块当中的点 $u,v$，$(u,v)$ 的答案 $+1$。

这种做法忽略了一个很关键的点：有 $k$ 条边的连通块至多只有 $k+1$ 个点，所以每一种颜色形成的有效连通块的大小总和最多是 $2\times 10^5$。

所有连通块的总大小被控制了，自然想到根号分治。

* 如果连通块的大小 $>\sqrt{m}$ ，那么记录连通块中的所有点。

* 如果连通块的大小 $\le \sqrt{m}$ ，那么暴力更新点对的答案。

第一种情况的大连通块最多只有 $\sqrt{m}$ 个，因此预处理复杂度 $O(m \sqrt{m})$；第二种情况，设连通块大小为 $x$ ，那么有复杂度 $O(\sum x) \le O(m \sqrt{m} \cdot T)$。

询问的时候，依次扫一遍所有大连通块中 $u,v$ 是否共存，再调用小连通块处理好的答案就行；不难发现单次查询复杂度 $O(\sqrt{m} \cdot T)$。

综上，复杂度 $O(m \sqrt{m} \cdot T)$ ，$T$ 为数据结构单次操作复杂度，使用 `STL::unordered_map` 即可做到 $O(m \sqrt{m})$ ，用 `STL::map` $O(m \sqrt{m} \log m)$ 也可以。

---

## 作者：FutaRimeWoawaSete (赞：1)

对于边的颜色的出现次数根号分治。                

如果一种颜色出现次数 $\leq \sqrt m$ 说明连出的图的大小在 $O(4m)$ 以内，并且分析总点对数会在 $\sqrt m$ 处取得最大值为 $O(4m \sqrt m)$。    

对于颜色出现次数 $> \sqrt m$ 的颜色只会有 $\Theta(\sqrt m)$ 种，直接用并查集连完后对 $q$ 个询问都回答一遍即可。              

用 map 把点对维护一下就是 $O((m + q) \sqrt m \log n)$ 了，个人比较憨只会每次并查集连完后回撤所有并查集就带 $\log n$ 了。

要卡常可以调阈值，或者把 map 的 pair 撤成一个整形啥的但是效果都没有不卡常的好。

```cpp
/*
考虑如何把n\sqrtn个(u,v)加到相应的(u,v)中去
不管了直接 map 算  
O(n \sqrt n \log n)
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,q,maxcol;
map<pair<int,int>,int> mp;
pair<int,int> pr;
struct NNode
{
	int u,v,w,p;
	NNode(){u = v = w = p = 0;}
	NNode(int U,int V,int W,int P){u = U , v = V , w = W , p = P;}
}ques[Len],stk[Len],pst;
int fa[Len],dep[Len],top,col[Len];
vector<NNode> v[Len];
void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i , dep[i] = 1;}
int findSet(int x){return fa[x] == x ? fa[x] : findSet(fa[x]);}
void unionSet(int x,int y)
{
	int u = findSet(x) , v = findSet(y);
	if(u == v) return;
	if(dep[u] < dep[v]) swap(u , v);
	stk[++ top] = NNode(u , v , fa[v] , dep[u]);
	fa[v] = u;
	dep[u] = max(dep[u] , dep[v] + 1);
}
void del(int x){fa[stk[top].v] = stk[top].w;dep[stk[top].u] = stk[top].p;}
int w;
void PP1(int Col)//对于大于等于 \sqrt m 的边 
{
	//makeSet(n);
	//for(int i = 1 ; i <= n ; i ++) printf("???%d %d\n",fa[i],dep[i]);
	top = 0;
	for(int j = 0 ; j < v[Col].size() ; j ++) unionSet(v[Col][j].u , v[Col][j].v);
	for(int i = 1 ; i <= q ; i ++) 
	{
		if(findSet(ques[i].u) == findSet(ques[i].v)) 
		{
		//	printf("%d %d %d\n",Col,ques[i].u,ques[i].v);
			ques[i].w ++;
		}
	}
	while(top) 
	{
		del(top);
		top --;
	}
} 
vector<int> FevPst;
void PP2(int Col)
{
	//makeSet(n);
	//for(int i = 1 ; i <= n ; i ++) printf("???%d %d\n",fa[i],dep[i]);
	FevPst.clear();
	top = 0;
	for(int j = 0 ; j < v[Col].size() ; j ++) 
	{
		unionSet(v[Col][j].u , v[Col][j].v);
		FevPst.push_back(v[Col][j].u) , FevPst.push_back(v[Col][j].v);
	}
	sort(FevPst.begin() , FevPst.end());
	FevPst.erase(unique(FevPst.begin() , FevPst.end()) , FevPst.end());
	for(int j = 0 ; j < FevPst.size() ; j ++)
		for(int k = j + 1 ; k < FevPst.size() ; k ++)//一定要注意小的在pair前面 
		{
			if(findSet(FevPst[j]) == findSet(FevPst[k]))
			{
				pr.first = FevPst[j] , pr.second = FevPst[k];
				mp[pr] ++;
			}
		}
	while(top) 
	{
		del(top);
		top --;
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		scanf("%d %d %d",&pst.u,&pst.v,&w);
		if(pst.u > pst.v) swap(pst.u , pst.v);
		maxcol = max(maxcol , w);
		col[w] ++;
		v[w].push_back(pst);
	}
	int t = sqrt(m);
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i ++) 
	{
		scanf("%d %d",&ques[i].u,&ques[i].v);
		if(ques[i].u > ques[i].v) swap(ques[i].u , ques[i].v);
	}
	makeSet(n);
	for(int i = 1 ; i <= maxcol ; i ++)
	{
		if(!col[i]) continue;
		if(col[i] >= t) PP1(i);
		else PP2(i);
	}
	for(int i = 1 ; i <= q ; i ++)
	{
		pr.first = ques[i].u , pr.second = ques[i].v;
		//printf("###%d %d\n",i,ques[i].w);
		printf("%d\n",ques[i].w + mp[pr]);
	}
	return 0;
}
```

---

## 作者：wsyhb (赞：1)

## 题意简述

给定一个 $n$ 个点 $m$ 条边的无向图，每条边有一个颜色，颜色编号 $\in [1,m]$。

再给定 $q$ 个询问，每次给出两个不同的点的编号 $u,v$，求有多少种颜色满足：只保留这种颜色的边时，$u$ 和 $v$ 连通。

**数据范围**：$2 \le n \le 10^5$，$1 \le m,q \le 10^5$。

## 题解

考虑颜色编号为 $i$ 的所有边组成的图，设有 $c_i$ 条边颜色为 $i$。

除去孤立点（没有连边的点），这个图中至多有 $c_i$ 个连通块。

由于 $\sum{c_i}=m$，则每种颜色的图中大小 $\ge 2$ 的连通块总共不超过 $m$ 个。

设大小 $\ge 2$ 的连通块总共有 $k$ 个，其中 $1 \le k \le m$。

我们将这些连通块依次编号为 $1$ 到 $k$，并**给连通块中的每个点打上该连通块编号的标记**。

使用**并查集**，我们可以预处理出每个点包含哪些标记。

------------

此时一个查询的答案就变为：$u$ 和 $v$ 有多少种公共的标记。

使用 **bitset** 即可做到 $O(\dfrac{qm}{\omega})$ 的时间复杂度，但请注意，此时空间复杂度为 $O(nm)$，编译都过不了。

由于 bitset 中有很多位置是空的，我们考虑**分块 + bitset**，即：**对于某一块，若存在位置不为空，就用一个 bitset 记录，否则无需记录**。

具体实现时，可用一个 vector 存储所有的 bitset，每一块只记录该块对应的 bitset 在 vector 中的下标即可（无需记录则将编号置为 $0$）。

------------

设块长为 $B$，则时间复杂度为 $O(m \cdot \dfrac{B}{\omega}+q \cdot \dfrac{m}{B} \cdot \dfrac{B}{\omega})$，空间复杂度为 $O(n \cdot \dfrac{m}{B}+m \cdot B)$。

取 $B=\sqrt{m}$ 可达到理论最好的时空复杂度，即：时间复杂度为 $O(\dfrac{qm}{\omega})$，空间复杂度为 $O((n+m)\sqrt{m})$。

P.S.

有的人可能会认为，时间比空间更重要，而理论时间复杂度随 $B$ 减小而减小，所以应该在空间能够接受的前提下，减小块长 $B$ 的大小。

但事实上，$B$ 根本就不能小多少（不然空间会爆），再加上减小 $B$ 并不会改变时间复杂度的瓶颈部分，在实际运行中比取 $B=\sqrt{m}$ 要慢。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
const int max_m=1e5+5;
vector<P> edge[max_m];
const int max_n=1e5+5;
int col[max_n],vis[max_n],fa[max_n],cnt_col;
int get_fa(int x)
{
	return fa[x]!=x?fa[x]=get_fa(fa[x]):x;
}
inline void merge(int x,int y)
{
	x=get_fa(x),y=get_fa(y);
	if(x!=y)
		fa[x]=y;
}
vector<int> c[max_n];
const int B=316;
bitset<B> now;
vector<bitset<B> > b(1);
const int max_B=316+5;
int id[max_n][max_B];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		edge[c].push_back(P(a,b));
	}
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=m;++i)
	{
		for(vector<P>::iterator it=edge[i].begin();it!=edge[i].end();++it)
			merge(it->first,it->second);
		for(vector<P>::iterator it=edge[i].begin();it!=edge[i].end();++it)
		{
			int u=it->first;
			if(vis[u]!=i)
			{
				if(!col[get_fa(u)])
					col[fa[u]]=++cnt_col;
				c[u].push_back(col[fa[u]]);
				vis[u]=i;
			}
			u=it->second;
			if(vis[u]!=i)
			{
				if(!col[get_fa(u)])
					col[fa[u]]=++cnt_col;
				c[u].push_back(col[fa[u]]);
				vis[u]=i;
			}
		}
		for(vector<P>::iterator it=edge[i].begin();it!=edge[i].end();++it)
		{
			int u=it->first;
			fa[u]=u,col[u]=0;
			u=it->second;
			fa[u]=u,col[u]=0;
		}
	}
	assert(cnt_col<=m);
	for(int i=1;i<=n;++i)
		for(int j=0;j<int(c[i].size());++j)
		{
			int k=(c[i][j]-1)/B;
			int L=k*B+1,R=(k+1)*B;
			now.reset();
			while(j<(int)c[i].size()&&c[i][j]>=L&&c[i][j]<=R)
				now[c[i][j++]-L]=true;
			b.push_back(now);
			id[i][k]=(int)b.size()-1;
			--j;
		}
	int q;
	scanf("%d",&q);
	int cnt_blocks=(n+B-1)/B;
	while(q--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		int ans=0;
		for(int i=0;i<=cnt_blocks-1;++i)
		{
			if(id[u][i]&&id[v][i])
				ans+=(b[id[u][i]]&b[id[v][i]]).count();
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Leeb (赞：0)

### 题意简述

[题面](https://www.luogu.com.cn/problem/CF506D)

给出一个无向图，每条边有颜色，每次询问两点间可以由多少种不同颜色的路径到达，要求路径上全是那一种颜色。

### 解题思路

直接开一个 `unordered_map`，维护每一个点对应颜色的并查集父亲。

然后考虑记忆化，对于每次询问，查找和这个点连边的所有颜色，查看它是否和另外一个点在这个颜色上连通。

时间复杂度：$\Theta(n\alpha n\sqrt{n})$。

- `unordered_map` 访问其中元素的值很慢，要用 `count` 函数，不然会 `TLE`。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define N 100005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
#define rs (x << 1 | 1)
#define pii pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, m, q;
unordered_map<int, int> fa[N], ans[N];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline int find(int x, int cor) {
    return fa[x][cor] == x ? x : fa[x][cor] = find(fa[x][cor], cor);
}
inline void merge(int x, int y, int cor) {
    if (!fa[x].count(cor)) fa[x][cor] = x;
    if (!fa[y].count(cor)) fa[y][cor] = y;
    x = find(x, cor), y = find(y, cor);
    if (x == y) return ;
    fa[x][cor] = y;
}
inline void init() {
    n = in(), m = in();
    for (int i = 1; i <= m; ++i) {
        int u = in(), v = in(), c = in();
        merge(u, v, c);
    }
}
inline void work() {    
    q = in();
    while (q--) {
        int u = in(), v = in();
        if (fa[u].size() > fa[v].size()) swap(u, v);
        if (ans[u].count(v)) {
            out(ans[u][v], '\n');
            continue;
        }
        int cnt = 0;
        for (auto x : fa[u]) 
            cnt += (fa[v].count(x.fir) && find(u, x.fir) == find(v, x.fir));
        ans[u][v] = cnt;
        out(ans[u][v], '\n');
    }
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```



---

## 作者：Zpair (赞：0)

按每个颜色分开，然后把每个颜色内部用并查集缩一下，然后就会有若干个连通块，把每个连通块里的点集合里加一个相同的值，则每个询问的答案就是求两个端点的集合交。

然后加若干的优化，比如相同的询问直接一起算，然后求集合交的时候遍历小的去查大的，然后发现它过了。

冷静分析一下，称一个点的颜色集合为其连边的颜色集合，然后一个询问的代价就是它两个集合大小的较小值。不妨假设每次询问都是 $B$ 的代价，然后设所有颜色集合 $\ge B$ 的点为关键点，则每次询问一定要在两个关键点之间。

因为 $n,m,q$ 同级所以下面都用 $N$ 来代替。

注意到所有点的颜色集合大小之和是 $O(N)$ 级别，也就是最多有 $\frac N B$ 个关键点，因为我们对询问去过重，所以最多有 $(\frac N B)^2$ 个询问，然后我们只能问 $N$ 个，所以时间复杂度为 $O(\min((\frac N B)^2,N)B)$ 的。

当 $(\frac N B)^2 \le N$ 时，有 $B^2 \ge N$，即 $B \ge \sqrt N$，此时时间复杂度为 $O((\frac N B)^2B)=O(\frac {N^2} B )\le O(N \sqrt N)$。

当 $(\frac N B)^2 > N$ 时，有 $B^2 < N$,即 $B < \sqrt N$，此时时间复杂度为 $O(NB) < O(N \sqrt N)$。

然后复杂度就对了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,q;
int fa[N];
vector<pair<int, int> > e[N];
unordered_set<int> p[N];
int idx[N],ans[N];
map<pair<int, int>, int> mp;
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)fa[x]=y;
}
int tot;
unordered_map<int, int> mpp;
unordered_set<int> s[N];
int u[N],v[N];
int main(){
	cin>>n>>m;
	int x,y,c;
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",&x,&y,&c);
		e[c].push_back({x,y});
		p[c].insert(x);
		p[c].insert(y);
	}
	cin>>q;
	for(int i=1;i<=q;++i){
		scanf("%d%d",&x,&y);
		u[i]=x,v[i]=y;
		if(!mp[{x,y}])mp[{x,y}]=i;
		else idx[i]=mp[{x,y}];
	}
	for(int i=1;i<=m;++i){
		for(int t:p[i])fa[t]=t;
		for(auto it:e[i])merge(it.first,it.second);
		for(int t:p[i]){
			int ft=find(t);
			if(!mpp[ft])mpp[ft]=++tot;
			s[t].insert(mpp[ft]);
		}
		mpp.clear();
	}
	for(int i=1;i<=q;++i){
		int x=u[i],y=v[i];
		if(!idx[i]){
			if(s[x].size()>s[y].size())
				swap(x,y);
			for(int t:s[x])
				if(s[y].find(t)!=s[y].end())
					ans[i]++;
		}
		else ans[i]=ans[idx[i]];
	}
	for(int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
}
```

---

