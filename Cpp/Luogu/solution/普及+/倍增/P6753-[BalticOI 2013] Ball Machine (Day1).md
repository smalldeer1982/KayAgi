# [BalticOI 2013] Ball Machine (Day1)

## 题目描述

给定一棵树，在根节点放一些球，如果下方有空位，那么它就会往下滚到下面的节点，如果有多个节点选择，它会选择 **以其（即后文中提到的儿子节点）为根节点的子树中标号最小值最小** 的儿子节点。每个位置最多只能有一个球，如果已经有球了，则该位置的空位被占用。

从一个位置上拿走球，上面的球也会滚下来。

每次给定一些操作，分别为在根节点放若干个球，和把某个节点的球拿走，求最后的结果。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le N,Q \le 10^5$。     
对于其中 $25\%$ 的数据，每个节点的儿子节点数只可能为 $0$ 个或 $2$ 个，且所有叶子节点到根节点的距离相同。     
对于另外 $30\%$ 的数据，$opt=2$ 的操作输出的总为 $0$。  
对于另外 $40\%$ 的数据，只能一个 $opt=1$ 的操作。

#### 说明

翻译自 [BalticOI 2013 Day1 A Ball Machine](https://boi.cses.fi/files/boi2013_day1.pdf)。

## 样例 #1

### 输入

```
8 4
0
1
2
2
3
3
4
6
1 8
2 5
2 7
2 8```

### 输出

```
1
3
2
2```

# 题解

## 作者：lyhqwq (赞：6)

# Solution

一道水紫

首先考虑放球操作

观察到小球每次下落必然选择子树内编号最小的点所在的子树下落，所以我们可以先预处理出 $Min_u$ 表示以 $u$ 为根的子树内编号最小的节点。

之后将每个结点的出边按照 $Min$ 从小到大排序，预处理出 dfs 序，那么小球每次下落选择的一定是当前没有小球且 dfs 序最小的节点，可以用一个优先队列来维护。


接着考虑撤球操作，如果一个球被撤掉了，那么从这个节点到根的这条链上所有的球都会向下一个，所以可以倍增找到这条链上第一个没有球的结点，深度之差即为答案。

对于放球操作，每放一个球时间复杂度为 $O(\log n)$，因为总共最多放 $n+\dfrac{Q}{2}$ 个球，所以总的时间复杂度为 $O((n+Q)\log n)$，可以通过本题。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,Q,rt;
int vis[N];
int dfn[N],rnk[N],cnt;
int dep[N],f[N][18];
int Min[N];
vector<int> vec[N];
priority_queue<int,vector<int>,greater<int> > q;
bool cmp(int x,int y){
	return Min[x]<Min[y];
}
void dfs1(int u){
	Min[u]=u,dep[u]=dep[f[u][0]]+1;
	for(int i=1;i<=17;i++) f[u][i]=f[f[u][i-1]][i-1];
	for(int i=0;i<vec[u].size();i++){
		int v=vec[u][i];
		dfs1(v);
		Min[u]=min(Min[u],Min[v]);
	}
}
void dfs2(int u){
	for(int i=0;i<vec[u].size();i++){
		int v=vec[u][i];
		dfs2(v);
	}
	dfn[u]=++cnt,rnk[cnt]=u;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i][0]);
		if(!f[i][0]) rt=i;
		else vec[f[i][0]].push_back(i);
	}
	dfs1(rt);
	for(int i=1;i<=n;i++) sort(vec[i].begin(),vec[i].end(),cmp);
	dfs2(rt);
	for(int i=1;i<=n;i++) q.push(i);
	while(Q--){
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1){
			int ans=0; 
			for(int i=1;i<=x;i++){
				ans=q.top();
				q.pop();
				vis[rnk[ans]]=1;
			}
			printf("%d\n",rnk[ans]);
		}
		else{
			int ans=0,y=x;
			for(int i=17;~i;i--) if(vis[f[y][i]]) y=f[y][i];
			vis[y]=0;
			q.push(dfn[y]);
			printf("%d\n",dep[x]-dep[y]);
		}
	}
	return 0;
}

```


---

## 作者：NuoCarter (赞：4)

# 题解 P6753 【[BalticOI 2013 Day1] Ball Machine】

考试硬生生做了 3h....

一个没找出性质的菜鸡。。。

整个思路就是 **模拟**，但是带有优化

## 算法：倍增+重链剖分+线段树

###  对于 1 操作:

可以知道当一个球放在 x 上时，一定是将 x 的子树都放满后再放的 x ，

因为他的儿子是有放的先后之分的，

**所以考虑记录下最小编号的路径，再在这条路径上倍增**

那么整个一操作就可以分为下面三步：

假设答案为 $now$

1.从 $now$ 倍增跳到最小路径上 dep 最大的点上，使得这个点的子树（包括他自己）的可放置空间 $>= num $

将 $now$赋成这个点

2.扫描 $now$ 的所有出边（按照路径最小编号最小到大，这个可以通过一次树形DP处理出扫描顺序）,

如果这个出点 $y$ 的可放置位置 $<num$,那么 $num-y$子树内剩余的位置，并且将整个 $y$ 子树的子树变成 1

如果可放置位置$>=num$的话,直接使　now=y，并且 break;

3.一直重复这个过程，直到找到一个点使得它的可放置空间 $= num$

最后输出 这个点的编号

那么难点就来了，如何快速查找这个点可放置个数?

答案就是轻重链剖分，只需要
```cpp
query(seg[x],seg[x]+size[x]-1)
```
就可以获得整个子树有多少个位置已经放置过，

```cpp
size[x]-query(seg[x],seg[x]+size[x]-1)
```
就可以快速算出可放置位置了

复杂度$O(log^2n)$(看起来常数有点大，但是跑的飞快)

### 对于 2 操作
很容易想到，这个操作就是从这个点向根走，有多少个连续的 1 。将连续的1的个数 -1（减去自己）就是答案

最后将最上面的 1 删除就好了，这个用树剖就很好判断了.

复杂度因为有一个线段树，所以还是$O(\log^2n)$

这道题的细节如果用这个思路的话好多啊。。。

### 整体复杂度:$O(n \log^2n)$

一开始一个树形DP $O(n)$

对于一个点 x ，将 x 能到达的点按照这个点的子树最小值从小到大排序，因为一条边只会多出一个点,所以这个复杂度就是$O(n \log n)$

倍增复杂度也为$O(n \log n)$
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lc x<<1
#define rc x<<1|1
const int N=1e5+5,Q=1e5+5,LOG=18;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){f^=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch-'0');ch=getchar();}
	x=f?-x:x;
}
template <typename T>
inline void print(T x){
	if(x<0){putchar('-');x=-x; }
	if(x>9){print(x/10);}
	putchar(x%10+48);
}
int head[N],to[N],minn[N],Next[N],tot,n,q,root;
int fson[LOG][N],len[N];
int dep[N],fa[N],siz[N],son[N];
vector<pair<int,int> > edge[N];
inline bool cmp(pair<int,int> x,pair<int,int> y){return x.first<y.first;}
inline void add(int u,int v){to[++tot]=v;Next[tot]=head[u],head[u]=tot;}
inline void dfs1(int x,int f){
	dep[x]=dep[f]+1;siz[x]=1;fa[x]=f;minn[x]=x;
	for(register int i=head[x];i;i=Next[i]){
		int y=to[i];
		dfs1(y,x);
		siz[x]+=siz[y];minn[x]=min(minn[x],minn[y]);
		edge[x].push_back(make_pair(minn[y],y));
		if(siz[y]>siz[son[x]]){son[x]=y;}
	}
}
int top[N],seg[N],rev[N],dnt;
inline void dfs2(int x){
	top[x]=son[fa[x]]==x? top[fa[x]] : x;
	len[top[x]]++;
	seg[x]=++dnt;rev[dnt]=x;
	if(son[x]){dfs2(son[x]);}
	for(register int i=head[x];i;i=Next[i]){
		int y=to[i];
		if(y!=son[x]){dfs2(y);}
	}
}
struct seg_tree{
	int l,r,sum,lazy;
	#define l(x)	c[x].l
	#define r(x)	c[x].r
	#define sum(x)	c[x].sum
	#define lazy(x)	c[x].lazy
}c[N<<2];
inline void update(int x){sum(x)=sum(lc)+sum(rc);}
inline void build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l==r){return;}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	return;
}
inline void change(int x,int d){sum(x)=(r(x)-l(x)+1);lazy(x)=1;}
inline void push_down(int x){if(lazy(x)){change(lc,lazy(x));change(rc,lazy(x));lazy(x)=0;}}
inline void modify_1(int x,int l,int r,int d){
	if(l(x)>=l&&r(x)<=r){change(x,d);return;}
	push_down(x);
	int mid=(l(x)+r(x))>>1;
	if(mid>=l){modify_1(lc,l,r,d);}
	if(mid<r){modify_1(rc,l,r,d);}
	update(x);
	return;
}
inline void modify_2(int x,int l,int d){
	if(l(x)==r(x)){sum(x)+=d;return;}
	push_down(x);
	int mid=(l(x)+r(x))>>1;
	if(mid>=l){modify_2(lc,l,d);}
	else{modify_2(rc,l,d);}
	update(x);
	return;
}
inline int query(int x,int l,int r){
	if(l(x)>=l&&r(x)<=r){return sum(x);}
	push_down(x);
	int mid=(l(x)+r(x))>>1;
	int res=0;
	if(mid>=l){res+=query(lc,l,r);}
	if(mid<r){res+=query(rc,l,r);}
	return res;
}
inline int uptoroot(int x){
	int res=0,tep=0,last=0;
	while(top[x]!=root){
		tep=query(1,seg[top[x]],seg[x]);
		if(tep==seg[x]-seg[top[x]]+1){
			res+=tep;
			last=top[x];
			x=fa[top[x]];
		}
		else{break;}
	}
	tep=query(1,seg[top[x]],seg[x]);
	if(tep==0){modify_2(1,seg[last],-1);}
	else{res+=tep;modify_2(1,seg[x]-tep+1,-1);}
	return res-1;
}
int main(){
	read(n),read(q);
	for(register int i=1;i<=n;++i){
		int u;read(u);
		if(!u){root=i;}
		else{add(u,i);}
	}
	dfs1(root,0);
	dfs2(root);
	int lim=log2(n)+1;
	for(register int i=1;i<=n;++i){
		sort(edge[i].begin(),edge[i].end(),cmp);
		if(!edge[i].empty())	fson[0][i]=edge[i][0].second;
	}
	for(register int j=1;j<=lim;++j){for(register int i=1;i<=n;++i){fson[j][i]=fson[j-1][fson[j-1][i]];}}
	build(1,1,n);
	while(q--){
		int op,num;
		read(op),read(num);
		if(op==1){
			bool flag=false;
			int teproot=root;
			int now=teproot;
			while(!flag){
				now=teproot;
				if(siz[now]-query(1,seg[now],seg[now]+siz[now]-1)==num){flag=true;break;}
				for(register int i=lim;i>=0;--i){
					int y=fson[i][now];
					if(!y){continue;}
					if(siz[y]-query(1,seg[y],seg[y]+siz[y]-1)<num){continue;}
					else if(siz[y]-query(1,seg[y],seg[y]+siz[y]-1)==num){flag=true;now=y;break;}
					else{now=fson[i][now];}
				}
				for(register int i=0;i<edge[now].size();++i){
					int y=edge[now][i].second;
					int tep=query(1,seg[y],seg[y]+siz[y]-1);
					if(siz[y]-tep<num){
						num-=siz[y]-tep;
						modify_1(1,seg[y],seg[y]+siz[y]-1,1);
					}
					else{teproot=y;break;}	
				}	
			}
			print(now);putchar('\n');
			modify_1(1,seg[now],seg[now]+siz[now]-1,1);
		}
		else{print(uptoroot(num));putchar('\n');}
	
	}
	return 0;
} 
```

---

## 作者：3a51_ (赞：2)

考虑每一个球的放入，会有一个固定的顺序，比如下图的树：

![](https://cdn.luogu.com.cn/upload/image_hosting/wjfe0uly.png)

此时小球放入的顺序必定为 $1-3-2-4$ 。 思考后发现对于一个节点 $x$，考虑其全部子节点的子树。显然子树拥有最小的一定会往那里滚。不妨先用一个搜索算出每个节点的子树中的最小值。然后这个优先级绝对是对我们有用的，可以在用一次搜索算出来。

接下来考虑两种操作。对于操作 $1$，虽然有优先级但是枚举一遍还是会超时。所以可以用数据结构维护,我用的优先队列。

接着考虑操作 $2$，不难发现当取走小球 $x$ 时，若 $x$ 的父亲 $f_x$ 存在小球，则 $f_x$ 的子结点（除了 $x$ ）全都有小球。所以 $f_x$ 的小球必定会掉落在 $x$ 节点。此时情况就被转化成 $f_x$ 的小球被取走。所以可以直接枚举 $x$ 的祖先，但这样还会超时。考虑倍增，这样可以在 $\log n$ 的时间搞定操作 $2$ 。当小球 $x$ 的某个祖先 $p_x$ 被取走，需要将 $p_x$ 对应的优先级入队。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
int f[N][35],rt,s[N],n,m,I[N],now,cnt,vis[N],st=1,ed=n,D[N];
vector<int> v[N];
struct Node{
	int nxt,lst,id;
}l[N];
struct tele{
	int id,w;
}p[N];
int cmp(tele x,tele y){
	return x.w<y.w;
}
priority_queue<int,vector<int>,greater<int> > q;
void Predfs(int x){
	int mi=1e18;
	for(int i=0;i<v[x].size();i++){
		Predfs(v[x][i]);
		mi=min(mi,s[v[x][i]]);
	}
	s[x]=min(x,mi);
	return;
}
void dfs(int x){
	int kr=cnt+1;
	for(int i=0;i<v[x].size();i++){
		p[++cnt].id=v[x][i];
		p[cnt].w=s[v[x][i]];
	}
	sort(p+kr,p+cnt+1,cmp);
	int wy=cnt;
	for(int i=kr;i<=wy;i++) dfs(p[i].id);
	I[x]=++now;
	D[now]=x;
	q.push(now);
	return;
}
void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>f[i][0];
		if(!f[i][0]) rt=i;
		else v[f[i][0]].push_back(i);
	}
	for(int j=1;j<=25;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	Predfs(rt);
	dfs(rt);
	for(int i=1;i<=m;i++){
		int op,x;
		cin>>op>>x;
		if(op==1){
			int ans;
			for(int j=1;j<=x;j++){
				vis[D[q.top()]]=1;
				if(j==x) ans=D[q.top()];
				q.pop();
			}
			cout<<ans<<endl;
		}else{
			int ans=0;
			for(int j=25;j>=0;j--){
				if(vis[f[x][j]]==1){
					ans+=(1<<j);
					x=f[x][j];
				}
			}
			vis[x]=0;
			q.push(I[x]);
			cout<<ans<<endl;
		}
	}
}
signed main(){
	//freopen("ball.in","r",stdin);
	//freopen("ball.out","w",stdout);
	ios::sync_with_stdio(false);
	int _=1;
	//cin>>_;
	while(_--){
		Solve();
	}
	return 0;
}
```

---

## 作者：optimize_2 (赞：2)

这个做法是两只 $\log$ 的。

考场上没想到性质。

但是我找到了另一个性质。

看一眼题上说的顺序，优先滚到儿子节点，然后滚到当前节点，是不是很像 dfs 序？

只要先跑一遍 dfs，把以每个节点根节点的子树中标号最小值跑出来，然后再做一遍 dfs，根据这个值搜儿子确定 dfs 序即可。

## 操作一

放 $k$ 个球，所以要找出 dfs 序前 $k$ 小的没被放过的位置。

这个就是线段树二分。

## 操作二

找到一个点往上走第一个没被放过的位置。

倍增跳祖先，然后在线段树上查询。

二分一只 $\log$，线段树一只 $\log$，瓶颈在这里。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

inline int read() {
    char c; bool f = true;
    while (!isdigit(c = getchar())) f = c != '-';
    int x = c ^ 48;
    while (isdigit(c = getchar())) x = x * 10 + (c ^ 48);
    return f ? x : -x;
}

const int N = 100010;
const int p = 1000000007;

int n, rt, m, op, x;
int f[N], fa[N][18];
vector<int> g[N];

int dep[N];
inline void dfs1(int x) {
    f[x] = x;
    for (auto y : g[x]) {
        dep[y] = dep[x] + 1;
        dfs1(y);
        f[x] = min(f[x], f[y]);
    }
}

inline bool cmp(int x, int y) {
    return f[x] < f[y];
}

int tot, pos[N], inv[N];
inline void dfs2(int x) {
    if (!g[x].empty()) {
        sort(g[x].begin(), g[x].end(), cmp);
        for (auto y : g[x]) {
            dfs2(y);
        }
    }
    tot++;
    pos[x] = tot;
    inv[tot] = x;
}

inline void init() {
    for (int d = 1; d <= 17; d++) {
        for (int i = 1; i <= n; i++) {
            fa[i][d] = fa[fa[i][d - 1]][d - 1];
        }
    }
}

struct sgt {
    int t[N << 4];
    bool tag[N << 4];

    inline int ls(int x) { return x << 1; }
    inline int rs(int x) { return x << 1 | 1; }

    inline void pushup(int x) {
        t[x] = t[ls(x)] + t[rs(x)];
    }

    inline void pushdown(int x) {
        if (!tag[x]) { return; }
        tag[ls(x)] = tag[rs(x)] = 1;
        t[ls(x)] = t[rs(x)] = 0;
        tag[x] = 0;
        pushup(x);
    }

    inline void build(int x, int l, int r) {
        if (l == r) {
            t[x] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        pushup(x);
    }

    inline int option1(int x, int l, int r, int num) {
        if (l == r) {
            t[x] = 0;
            return l;
        }
        pushdown(x);
        int mid = (l + r) >> 1;
        int res = -1;
        if (t[ls(x)] >= num) {
            res = option1(ls(x), l, mid, num);
        } else {
            tag[ls(x)] = 1;
            num -= t[ls(x)];
            t[ls(x)] = 0;
            res = option1(rs(x), mid + 1, r, num);
        }
        pushup(x);
        return res;
    }

    inline void option2(int x, int l, int r, int p) {
        if (l == r) {
            t[x] = 1;
            return;
        }
        pushdown(x);
        int mid = (l + r) >> 1;
        if (p <= mid) { option2(ls(x), l, mid, p); }
        if (mid < p) { option2(rs(x), mid + 1, r, p); }
        pushup(x);
    }

    inline int query(int x, int l, int r, int p) {
        if (p == 0) { return 1; }
        if (l == r) {
            return t[x];
        }
        pushdown(x);
        int mid = (l + r) >> 1;
        if (p <= mid) { return query(ls(x), l, mid, p); }
        else { return query(rs(x), mid + 1, r, p); }
    }
} tr;

inline int remove(int x) {
    int y = x;
    for (int d = 17; d >= 0; d--) {
        if (!tr.query(1, 1, n, pos[fa[y][d]])) {
            y = fa[y][d];
        }
    }
    tr.option2(1, 1, n, pos[y]);
    return dep[x] - dep[y];
}

int main() {
    n = read(); m = read();
    for (int i = 1; i <= n; i++) {
        x = fa[i][0] = read();
        if (x == 0) {
            rt = i;
        } else {
            g[x].push_back(i);
        }
    }
    dfs1(rt);
    dfs2(rt);
    init();
    tr.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        op = read(); x = read();
        if (op == 1) {
            printf("%d\n", inv[tr.option1(1, 1, n, x)]);
        } else {
            printf("%d\n", remove(x));
        }
    }
}
```

---

## 作者：Star_Cried (赞：1)

## P6753 [BalticOI 2013 Day1] Ball Machine

### 题意

给你一个树，每次从根节点放一个求，如果其子节点有空这个球会向下滚，若有多个节点为空则找儿子中**以子树内编号的最小值**为优先级从小到大找第一个为空的位置滚。

有两种操作，第一种插入若干个球，输出最后一个球到的节点编号；第二种删除一个位置，此时若有可以向下滚的球那么这个球就会滚，输出有多少个球滚了。

保证数据合法。

### 思路

首先我们思考只有1操作的情况。

对于1操作，球加入的顺序为按照**以子树内编号的最小值**为优先级的后序遍历 dfs 序。我们得到了 40pts。

对于2操作，删掉一个球后答案一定是其所有祖先中有球的位置的个数。原因显然，因为删球前一定是最佳状态，即没有球能动，所以删掉这个球后只有其祖先会向下移动并且一定会向下移动。

发现祖先有球的段一定是连续的，于是我们就可以用倍增找到最浅的有球的祖先，并且顺便输出答案。

但是2操作后会把父亲节点删去。注意这时候删去的节点并非最后加入的点。而且下一次加入球时会找 dfs 序最小的。这时候我们就需要一些东西比如 stl 的 `vector` / `priority_queue` / `set` 进行维护了。

还有最最最重要的一点！对于操作1，我们是依次一个一个加入的，这样的时间复杂度为什么是正确的？

显然，因为每个2操作只会删 $1$ 个点，所以我们最多会插入 $n+q$ 个点。~~所以要什么重链剖分和线段树暴力就能过~~

### 实现

我用的是 vector 存储空节点来实现这个过程的。它的好处在于对于1操作删除是 $O(1)$ 的。不过插入必须用 `upper_bound` 和 `insert` 。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10;
	int n,Q;
	int fa[maxn][21],rt,dfn[maxn],tot,id[maxn],mn[maxn];
	bool vis[maxn];
	vector<int> q,G[maxn];
	void dfs1(int x){
		mn[x]=x;
		for(int i=0;i<G[x].size();i++)
			dfs1(G[x][i]),mn[x]=min(mn[x],mn[G[x][i]]);
	}
	inline bool cmp1(int a,int b){return mn[a]<mn[b];}
	void dfs(int x){
		for(int i=0;i<20;i++) fa[x][i+1]=fa[fa[x][i]][i];
		sort(G[x].begin(),G[x].end(),cmp1);
		for(int i=0;i<G[x].size();i++)
			dfs(G[x][i]);
		dfn[x]=++tot;
		id[tot]=x;
	}
	inline bool cmp(int a,int b){return dfn[a]>dfn[b];}
	inline void work(){
		n=read(),Q=read();
		for(int i=1;i<=n;i++){
			if((fa[i][0]=read())==0) rt=i;
			G[fa[i][0]].push_back(i);
		}
		dfs1(rt);
		dfs(rt);q.resize(n),q.clear();
		for(int i=n;i;i--) q.push_back(id[i]);
		while(Q--)
		if(read()==1){
			int num=read();
			while(--num)vis[q.back()]=1,q.pop_back();
			printf("%d\n",q.back());
			vis[q.back()]=1;q.pop_back();
		}else{
			int x=read();
			if(!vis[x]){puts("0");continue;}//数据合法，好像没用
			int f=x,ans=0;
			for(int i=20;~i;i--) if(vis[fa[f][i]])f=fa[f][i],ans|=(1<<i);
			vis[f]=0;
			q.insert(upper_bound(q.begin(),q.end(),f,cmp),f);
			printf("%d\n",ans);
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```

### 其他

强烈吐槽洛谷的翻译！一直以为是以直接相连节点的编号大小为优先级，结果是子树内的最小值……建议大家看原题面。



---

## 作者：Computer1828 (赞：1)

如果把样例里的树建出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/mptmqszr.png)

然后执行一次在节点 $1$ 放 $8$ 个球的操作，就会发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/dyrnksqs.png)

球落到的位置是这棵树的**后序遍历**。

以下，我们称一个点 $u$ 的后序遍历序为 $dfn[u]$。

不难想到用一个堆维护每个点的 $dfn$。对于操作 $1$，找到当前最小的 $dfn[u]$，然后把它踢出堆，并且标记一下这个点 $u$ 有球；对于操作 $2$，找到最上面的有球的节点 $v$，那么从 $v$ 到 $fa[u]$ 的节点的球都会落下来，然后节点 $v$ 就没有球了，把它丢进堆里并且标记一下这个点空就行了。

因为一个点的儿子可能不止两个，所以在预处理 $dfn$ 的时候，要先对它的儿子们编号进行排序。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,q,rt;
vector<int> a[N];
int d[N],dep[N],dfn[N],cnt;
int fa[N][21];
bool vis[N];
/*
d[u]:以u为根的子树中最小的节点编号
dep[u]:u到根的距离
dfn[u]:u在树的后序遍历中是第几个
vis[u]:u有没有球
fa[u][i]:u的2^i级祖先是谁 
*/
struct node{
	int x;
	bool operator <(const node &tmp) const{
		return dfn[x]>dfn[tmp.x];//按dfn进行从小到大排序
	}
};
priority_queue<node> que;
inline bool cmp(int x,int y){
	return d[x]<d[y];
}
inline void dfs(int u){
	d[u] = u;
	for(int i = 0;i<a[u].size();++i){
		int v = a[u][i];
		dfs(v);
		d[u] = min(d[u],d[v]);
	}
}

inline void bfs(int u){
	for(int i = 1;(1<<i)<=dep[u];++i) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int i = 0;i<a[u].size();++i){
		int v = a[u][i];
		dep[v] = dep[u]+1,fa[v][0] = u;
		bfs(v);
	}
	dfn[u] = ++cnt;
}
int main(){
	scanf("%d%d",&n,&q);
	int x;
	for(int i = 1;i<=n;++i){
		scanf("%d",&x);
		if(x == 0) rt = i;
		a[x].push_back(i);
	}
	dep[rt] = 1;
	dfs(rt);
	for(int i = 1;i<=n;++i) sort(a[i].begin(),a[i].end(),cmp);
	bfs(rt);
	for(int i = 1;i<=n;++i) que.push((node){i});
	int opt,num;
	while(q--){
		scanf("%d%d",&opt,&num);
		if(opt == 1){
			int tp;
			for(int i = 1;i<=num;++i){
				tp = que.top().x;
				que.pop();
				vis[tp] = true;
			}
			printf("%d\n",tp);
		}else{
			int tp = num;
			for(int i = 20;i>=0;--i){
				if(vis[fa[tp][i]]) tp = fa[tp][i];
			}
			vis[tp] = false;
			que.push((node){tp});
			printf("%d\n",dep[num]-dep[tp]);
		}
	}
	return 0;
}
```

---

## 作者：EricWan (赞：0)

很有意思的题，想法独特。

### 预处理

1. 对于一个树如果只作插入操作，他肯定有一个固定的插入顺序，我们叫它 $\text{p}_{1\dots n}$，设 $\text{p}_{\text{q}_i}=i$。我们可以这样求 $\text{p}_{1\dots n}$：遍历整棵树，设 $\text{minn}_i$ 为以 $i$ 为根的子树内最小的点权，对于每个节点的子节点，以 $\text{minn}_i$，为键字从小到大进行排序（遍历顺序），最后求后缀表达式即可。

2. 倍增处理祖先节点，设 $\text{anc}_{i,j}$ 为节点 $i$ 的 $2^j$ 级祖先（它是自己的 $0$ 级祖先，它的父亲是它的 $1$ 级祖先，以此类推）。规定根节点的父亲是 $0$ 号节点。

### 维护

设小根堆 $\text{pq}$ 维护当前所有空节点 $\text{emp}_{1\dots m}$ 的 $\text{q}_{\text{emp}_{1\dots m}}$，$\text{have}_i$ 记录 $i$ 节点点上是否有球。

### 操作：插入

设 $t$ 为 $\text{pq}$ 的顶，则这个球一定被插入在 $\text{p}_t$，更新 $\text{pq}$ 和 $\text{have}_t$ 即可。

### 操作：删除

倍增找最接近它的有球但是父节点是空的的祖先（形象的说：找到节点 $k$ 是 $num$ 的祖先，而且 $\text{have}_k=1,\ \text{have}_{\text{fa}_k}=0$），之后那个位置的球一定会随着下面的球往下落，更新 $\text{pq}$ 和 $\text{have}_k$ 即可。

[代码在这里！(11.4s)](https://www.luogu.com.cn/record/129023133)

---

## 作者：dgdyrkst (赞：0)

## 思路

观察题目，我们可以发现一些性质，比如说每次操作只会撤去 $1$ 个球。

这意味着我们可以一个一个地加入球，最多只会放入 $n+q$ 个球。

然后我们观察球放下之后会落到哪里：

+ 如果有多个节点选择，它会选择 __以其为根节点的子树中标号最小值最小__ 的儿子节点。

这启发我们对于每个点将它的所有儿子按照子树中的标号最小值排序。

接下来执行一次广义上的 __后序遍历__，即在离开每个节点时对其进行标号。

当然，遍历时要先走排序之后靠前的儿子节点。

很显然，这样进行标号之后，一个球被放下时就会落到标号最小的没有球的点上。

怎么维护？开一个小根堆存所有没有球的节点的标号就可以了。

这样我们就成功维护好了操作 $1$。

对于操作 $2$，我们也能发现，实际上就是某个叶子节点的深度最浅的有球的祖先变为没有球。

考虑倍增，维护每个节点的 $2^i$ 级祖先。

然后开一个 $vis$ 数组，标记每个节点有没有球，这样就能找到上文所提的那个点。

最后修改这个节点的信息并把它放到堆里就可以了。

时间复杂度 $O((n+q) \log n)$。

## 代码

以下为代码参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q,op,x,f[N][25],mint[N],root,wei[N],dui[N],tot;
bool vis[N];
vector<int> v[N];
priority_queue<int,vector<int>,greater<int>> pq;
bool cmp(int x,int y)
{
	return mint[x]<mint[y];
}
int dfs_pre(int now)
{
	for (int i=1;(1<<i)<=n;i++)
	{
		f[now][i]=f[f[now][i-1]][i-1];
	}
	for (int i=0;i<v[now].size();i++)
	{
		mint[now]=min(mint[now],dfs_pre(v[now][i]));
	}
	mint[now]=min(mint[now],now);
	return mint[now];
}
void dfs_wei(int now)
{
	sort(v[now].begin(),v[now].end(),cmp);
	for (int i=0;i<v[now].size();i++)
	{
		dfs_wei(v[now][i]);
	}
	wei[now]=++tot,dui[tot]=now,pq.push(wei[now]);
}
int get(int x)
{
	int ret=0;
	for (int i=20;i>=0;i--)
	{
		if (!vis[f[x][i]])continue;
		x=f[x][i];
		ret+=(1<<i);
	}
	vis[x]=0;
	pq.push(wei[x]);
	return ret;
}
int main()
{
	memset(mint,0x3f,sizeof(mint));
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&f[i][0]);
		if (f[i][0])v[f[i][0]].push_back(i);
		else root=i;
	}
	dfs_pre(root);
	dfs_wei(root);
	while (q--)
	{
		scanf("%d%d",&op,&x);
		if (op==1)
		{
			for (int i=1;i<=x;i++)
			{
				int now=pq.top();pq.pop();
				vis[dui[now]]=1;
				if (i==x)printf("%d\n",dui[now]);
			}
		}
		else
		{
			printf("%d\n",get(x));
		}
	}
	return 0;
}
```

---

## 作者：FXT1110011010OI (赞：0)

## 思路

容易发现，因为树的形状不会改变，所以落球顺序是固定的，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8rbobs55.png)

这棵树的落球顺序一定是 `5 8 6 3 7 4 2 1`。

于是，我们就可以按照以子树内编号的最小值为优先级的规则，进行 dfs，求出落球顺序 。

接着考虑两种操作：

对于操作 $1$，每放入一个球，只要找到 dfs 序中权值最小的空位填上即可，这里我用优先队列维护。

对于操作 $2$，假设当前要被移走的球在 $x$ 节点，则 $x$ 的所有有球的祖先节点都要下移一位，所以答案就是 $x$ 最上面的有球节点到 $x$ 节点的距离。可以先预处理出所有节点的层数，查询时用倍增求 $x$ 最上面的有球的节点，层数作差即是答案。

**代码中需要注意的几点**

* 注意优先队列和 dfs 优先级的排序方式不要漏写或搞混！
* 在我的代码 dfs 部分中，当前节点 $u$ 能够到达的下一个节点使用 `vector` 存储。注意这里如果定义全局数组，在递归时可能因为数组改动而错误，如果在 dfs 中定义数组，会 MLE。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int h[N], e[N], ne[N], idx;
int ball[N], cnt; // ball[i] 表示节点 i 在 dfs 序中的编号
int f[N][25]; // f[i][j] 表示从节点 i 往上走 2 ^ j 步的节点编号是多少
int mn[N], dep[N], len; // mn[i] 表示以 i 为根的子树中的节点编号最小值，dep[i] 表示节点 i 的层数
bool st[N]; // st[i] 表示节点 i 有没有球（0 表示没有，1 表示有）
struct cmp
{
    bool operator () (int x, int y)
    {
        return ball[x] > ball[y];
    }
};
priority_queue<int, vector<int>, cmp> ok;

bool cmp2(int x, int y)
{
    return mn[x] < mn[y];
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void init(int u)
{
    mn[u] = u;
    for (int i = 1; i <= 20; i ++ )
    {
        if (!f[u][i - 1]) break;
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dep[j] = dep[u] + 1;
        init(j);
        mn[u] = min(mn[u], mn[j]);
    }
}

void dfs(int u)
{
    vector<int> t;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        t.push_back(j);
    }
    sort(t.begin(), t.end(), cmp2);
    for (int i = 0; i < t.size(); i ++ ) dfs(t[i]);
    ball[u] = ++ cnt;
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    int root;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ )
    {
        int a;
        scanf("%d", &a);
        f[i][0] = a;
        if (!a) root = i;
        else add(a, i);
    }
    init(root);
    dfs(root);
    for (int i = 1; i <= n; i ++ ) ok.push(i);
    while (q -- )
    {
        int op, num;
        scanf("%d%d", &op, &num);
        if (op == 1)
        {
            int t;
            while (num -- )
            {
                t = ok.top();
                ok.pop();
                st[t] = true;
            }
            printf("%d\n", t);
        }
        else
        {
            int t = num;
            for (int i = 20; ~i; i -- )
            {
                if (st[f[t][i]]) t = f[t][i];
            }
            ok.push(t), st[t] = false;
            printf("%d\n", dep[num] - dep[t]);
        }
    }
    return 0;
}
```

---

## 作者：lzytag (赞：0)

## 来一发乱搞的单 log 题解

[题目传送门](https://www.luogu.com.cn/problem/P6753)

# Solution

看到这一题操作 $1$：“在根节点处放 $num$ 个球”的操作十分有趣，我们考虑如何快速处理操作 $1$。

首先我们发现，每一个操作 $2$ 只会拿走一个球，所以最终放球总数最多是 $n+m$ 个（最初有 $n$ 个空位，每个操作 $2$ 会增加一个空位，所以总空位个数为 $n+m$)。

于是我们就可以进一步考虑如何在 $O(\log n)$ 的复杂度内完成放入**一个**球的操作。

这时我们就要引出一个关键的结论：

**在放球操作中，放球的顺序是固定的。**

**也就是我们可以给每一个节点赋一个权值，每次放一个球，只要找到权值最小的空位，然后把球放入即可。这显然是可以通过 set 维护的。**

那这个赋的值是什么？为什么可以代表放球的顺序？又该怎么求呢？

这个值就是将一个节点所有出边按题目要求排好序后，所得树的后序遍历顺序。

（作者语文不好，可以结合代码理解）

```cpp
//用的是vector存边，便于排序
vector<int>e[MaxN];
int mn[MaxN],ccnt,d[MaxN];
bool mycmp(int x,int y)
{
	return mn[x] < mn[y];
}
void dfs(int u)//这一次dfs的作用是将边排序
{
	mn[u] = u;
	for(auto v:e[u]) dfs(v),mn[u] = min(mn[u],mn[v]);
	sort(e[u].begin(),e[u].end(),mycmp);
}
void dfs1(int u)
{
	for(auto v:e[u]) dfs1(v);
	d[u] = ++ccnt;//d[u]既是我们要求的取球顺序
}
```
这样我们就解决了第一和第三个问题，接下来就只剩下第二个问题需要解决了了。

~~感性理解一下~~，球滚落时，向下滚的顺序就是结束 dfs 访问的顺序。

这样我们就解决了操作 $1$。

至于操作 $2$ 就比较简单且套路了。我们只要维护节点的树上点权的前缀和，每次操作 $2$ 就找到一个节点 $num$ 最上面的有球的节点。我们可以用 dfs 序加差分加树状数组（也可以直接线段树）维护，用倍增实现跳节点的操作。

具体实现可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define zsj return
#define akioi 0
int read()
{
	int x;scanf("%d",&x);
	return x;
}
ll lread()
{
	ll x;scanf("%lld",&x);
	return x;
}
//file head over
#define MaxN 100005
#define pb push_back
//区间修改，单点查询，采用BIT+差分
//Qry(i)代表i在树上的前缀和 
#define pii pair<int,int>
#define fir first
#define sec second
#define mkp make_pair
int dfn[MaxN],cnt,tr[MaxN],ed[MaxN],ccnt,d[MaxN];
int f[MaxN][20],n,ans,rt,mn[MaxN];
vector<int>e[MaxN];
set< pii >st;
int lowbit(int x){return x&(-x);}
void Upd(int x,int y){for(;x <= n;x += lowbit(x)) tr[x] += y;}
int Qry(int x){int res = 0;for(;x;x-=lowbit(x)) res+=tr[x];return res;}
void dfs(int u)
{
	dfn[u] = ++cnt;
	mn[u] = u; 
	for(int i = 1;i <= 17;i++) f[u][i] = f[f[u][i-1]][i-1];
	for(auto v:e[u]) dfs(v),mn[u] = min(mn[u],mn[v]);
	ed[u] = cnt;
}
void ball(int u,int x)
{
	Upd(dfn[u],x);Upd(ed[u]+1,-x);ans = u;
	if(x == 1) st.erase(mkp(d[u],u));
	else st.insert(mkp(d[u],u));
}
void dfs1(int u)
{
	for(auto v:e[u]) dfs1(v);
	d[u] = ++ccnt;st.insert(mkp(ccnt,u));
}
bool mycmp(int x,int y)
{
	return mn[x] < mn[y];
}
int Get(int x,int y)
{
	for(int i = 17;i >= 0;i--)
		if((1<<i) <= y) x = f[x][i],y -= (1<<i);
	return x;
}
int main()
{
	n = read();int Q = read();
	for(int i = 1;i <= n;i++)
	{
		f[i][0] = read();
		if(f[i][0] == 0) rt = i;
		else e[f[i][0]].pb(i);
	}
	dfs(rt);
	for(int i = 1;i <= n;i++) sort(e[i].begin(),e[i].end(),mycmp);
	dfs1(rt);
	while(Q--)
	{
		int op = read(),x = read();
		if(op == 1)
		{
			while(x--)
			{
				pii u = *st.begin();
				ball(u.sec,1);
			}
			printf("%d\n",ans);
		}
		else
		{
			printf("%d\n",Qry(dfn[x])-1);
			int v = Get(x,Qry(dfn[x])-1);
			ball(v,-1); 
		}
	}
	return 0;
}
```
开了 $O2$，4.44s，可以说常数不小，但比树剖好写多了。

---

## 作者：xin700 (赞：0)

## [BalticOI 2013 Day1] Ball Machine

是一道不太难的紫题。

首先我们看到这个题目的操作感觉像是一个大型数据结构，但其实我们所要的操作其实完全不用这样。

如果我们使用线段树和树链剖分进行维护的话，那么其实复杂度是比较高的，但是也是可以过掉这个题目，但这不优秀。

分析一下，可以发现如果只有 $1$ 的时候我们的这个答案其实就是这个树的**后序遍历**。

再考虑加上 $2$ 操作之后的答案，其实这个的答案就是这个**被删去节点的所有祖先的数量**，那么我们就可以维护所有的空闲位置，之后每次使用**倍增**找到第一个空位的祖先，那么就是 $2$ 操作的答案。

那么 $1$ 操作自然就用一个`priority_queue`来维护了。

```cpp
#include<bits/stdc++.h>
using std::cout; using std::endl;
#define try(i,a,b) for(register int i=a;i<=b;++i)
#define throw(i,a,b) for(register int i=a;i>=b;--i)
#define go(i,x) for(register signed i=head[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
namespace xin_io
{
	#define file(x) FILE *FI = freopen(#x".in","r",stdin); FI = freopen(#x".out","w",stdout);
	#define sb(x) cout<<#x" = "<<x<<' '
	#define jb(x) cout<<#x" = "<<x<<endl
	#define debug cout<<"debug"<<endl
	#define gc() p1 == p2 and (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2) ? EOF : *p1 ++
	#define gec() getchar()
	#define scanf ak = scanf
	char buf[1<<20],*p1 = buf,*p2 = buf; using ll = long long; using ull = unsigned long long; int ak;
	class xin_stream{public:template<typename type>xin_stream &operator >> (type &s)
	{
		s = 0; register bool f = 0; register char ch = gc();
		while(!isdigit(ch)) f |= ch == '-',ch = gc();
		while( isdigit(ch)) s = (s << 1) + (s << 3) + (ch xor 48),ch = gc(); return s = f ? -s : s,*this;
	}}io;
}
using namespace xin_io; static const int maxn = 1e6+10,inf = 1e9+10;
// #define int long long
namespace xin
{
	std::vector <int> vec[maxn];
	int n,qnum,rt;
	int fa[maxn][21],tot;
	int minb[maxn],d[maxn],id[maxn],rk[maxn];
	bool vis[maxn];
	void dfs(int x)
	{
		minb[x] = x; d[x] = d[fa[x][0]] + 1;
		for(auto y : vec[x])
		{
			dfs(y);
			minb[x] = std::min(minb[x],minb[y]);
		}
	}
	void bfs(int x)
	{
		// std::queue<int>q; q.push(rt);
		// while(q.size())
		// {
		// 	register int x = q.front(); q.pop();
		// 	for(register int i=1;(1 << i)<=d[x];++i)
		// 		fa[x][i] = fa[fa[x][i-1]][i-1];
		// 	for(auto y : vec[x]) q.push(y);
		// }
		for(register int i=1;(1 << i)<=d[x];++i) fa[x][i] = fa[fa[x][i-1]][i-1];
		for(auto y : vec[x])
			bfs(y);
		id[x] = ++tot; rk[tot] = id[x];
	}
	class xin_data
	{
		private:
			friend bool operator < (xin_data x,xin_data y) {return id[x.x] > id[y.x];}
		public:
			int x; 
			xin_data(){}
			xin_data(int x):x(x){}
	};
	std::priority_queue<xin_data>q;
	inline short main()
	{
		io >> n >> qnum;
		try(i,1,n)
		{
			io >> fa[i][0];
			if(!fa[i][0]) rt = i;
			vec[fa[i][0]].push_back(i);
		}
		d[rt] = 1;dfs(rt); try(i,1,n)std::sort(vec[i].begin(),vec[i].end(),[](int x,int y){return minb[x] < minb[y];});
		bfs(rt); int ms = (int)log2(n)+1;
		try(i,1,n) q.push(xin_data(i));
		try(cse,1,qnum)
		{
			register int op,x; io >> op >> x;
			if(op == 1)
			{
				int temp;
				try(i,1,x)
				{
					temp = q.top().x; q.pop();
					vis[temp] = 1;
				}
				printf("%d\n",temp);
			}
			else
			{
				register int temp = x;
				throw(i,ms,0) if(vis[fa[temp][i]]) temp = fa[temp][i];
				vis[temp] = 0; q.push(xin_data(temp));
				printf("%d\n",d[x] - d[temp]);
			}
		}
		return 0;
	}
}
signed main() {return xin::main();}
```

---

