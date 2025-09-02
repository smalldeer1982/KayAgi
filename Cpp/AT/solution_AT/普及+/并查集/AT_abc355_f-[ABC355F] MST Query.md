# [ABC355F] MST Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc355/tasks/abc355_f

頂点に $ 1 $ から $ N $ の番号が、辺に $ 1 $ から $ N-1 $ の番号が付いた $ N $ 頂点 $ N-1 $ 辺の重み付き無向連結グラフ $ G $ が与えられます。辺 $ i $ は頂点 $ a_i $ と頂点 $ b_i $ を結んでおり、その重みは $ c_i $ です。

$ Q $ 個のクエリが与えられるので順に処理してください。$ i $ 番目のクエリは以下で説明されます。

- 整数 $ u_i,v_i,w_i $ が与えられる。$ G $ の頂点 $ u_i,v_i $ の間に重み $ w_i $ の辺を追加する。その後、$ G $ の最小全域木に含まれる辺の重みの和を出力する。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\ \times\ 10^5 $
- $ 1\leq\ Q\leq\ 2\ \times\ 10^5 $
- $ 1\leq\ a_i\lt\ b_i\leq\ N $
- $ 1\leq\ u_i\lt\ v_i\leq\ N $
- $ 1\leq\ c_i,w_i\leq\ 10 $
- クエリを処理する前のグラフは連結
- 入力はすべて整数
 
### Sample Explanation 1

各クエリで辺を追加した後のグラフを示しています。最小全域木に含まれる辺は赤色で塗られています。 !\[\](https://img.atcoder.jp/abc355/4e83a6e54750f138ecada66dd93b2b67.png)

## 样例 #1

### 输入

```
4 4
1 2 6
2 3 5
2 4 4
1 3 3
1 2 3
1 4 10
3 4 1```

### 输出

```
12
10
10
7```

## 样例 #2

### 输入

```
8 6
1 8 8
1 6 10
1 5 8
2 6 6
6 7 6
1 3 9
2 4 7
1 3 4
1 6 7
3 4 6
1 5 1
7 8 4
3 5 3```

### 输出

```
49
46
45
38
34
33```

# 题解

## 作者：2022liaojianxiang (赞：18)

可以发现这道题中边的权值非常小，只有 $10$ 的取值范围。那么我们思考从这里找突破口。可以发现有一种非常快速的做法：我们建立 $10$ 个并查集，然后对于第 $i$ 个并查集存储所有权值 $x \le i$ 的边。并每次计算每一层的 Kruskal 同时得出当前这一层的连边情况。具体做法如下：

- 先建立 $10$ 个并查集，设置答案的值为 $10 \times (n-1)$ 表示刚开始假设最小生成树的 $(n-1)$ 条边全部都设成最大的值 $10$。

- 然后对于每一次操作，从当前这条边的权值所在的一层一直往上直到第 $9$ 层并查集（因为第 $10$ 层是最劣的且答案的值已是最劣，无需更新），每次对当前并查集进行加边操作（并查集中如果两者不同集合则加入，已同集合则没有必要）。

- 每上一层答案减去 $1$ 表示当前这条边多了 $1$ 的贡献（因为你在这个并查集中可能有贡献但到了上层有别的边会参入，但前面的贡献这条参入的边已经帮我们减过了，所以只需要一点点往上直到某个时刻没有贡献可以加了为止）

最后就可以轻松的只用 $700$ bytes 切掉这一题。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const long long N=1000009;
long long n,q,fa[10][N];
long long find(long long x,long long shu)
{
	if(fa[shu][x]==x) return x;
	else return fa[shu][x]=find(fa[shu][x],shu);
}
int main()
{
	scanf("%lld%lld",&n,&q);
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<10;j++)
			fa[j][i]=i;
	long long ans=10*(n-1);
	for(long long i=1;i<=n+q-1;i++)
	{
		long long x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		for(long long j=z;j<10;j++)
		{
			long long fx=find(x,j),fy=find(y,j);
			if(fx!=fy) {ans--,fa[j][fy]=fx;}
			else break;
		}
		if(i>=n) printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Iceturky (赞：12)

[Link](https://atcoder.jp/contests/abc355/tasks/abc355_f)

注意到边权范围极小。

考虑枚举边权，计算这种边对答案的贡献。

发现边权为 $1$ 的边会对其他所有的边产生影响，边权为 $2$ 的边会对边权大于等于 $2$ 的边产生影响。

影响直接用并查集处理。

具体的，建立 $10$ 个并查集，分别存储边权小于等于其下标的边构成的生成森林，顺便维护一下森林上边的数量和。

这样直接用边权小于等于 $x$ 的森林边数减去边权小于等于 $x-1$ 的森林的边数即为边权为 $x$ 的边产生贡献的数量。

code

```cpp
struct DSU{
	int fa[N],sum[N],cnt;
	void init(int n){
		for(int i=1;i<=n;i++)
			fa[i]=i,sum[i]=1;
		cnt=0;
	}
	int fd(int x){
		return fa[x]==x?x:fa[x]=fd(fa[x]);
	}
	void merge(int x,int y){
		x=fd(x),y=fd(y);
		if(x==y)
			return;
		if(sum[x]>sum[y])
			swap(x,y);
		fa[x]=y;
		sum[y]+=sum[x];
		cnt++;
	}
}D[13];

void add(int u,int v,int w){
	for(int i=w;i<=10;i++)
		D[i].merge(u,v);
}

signed main()
{
	int n=read(),q=read();
	for(int i=1;i<=10;i++)
		D[i].init(n);
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	while(q--){
		int u=read(),v=read(),w=read();
		add(u,v,w);
		int ans=D[1].cnt;
		for(int i=2;i<=10;i++)
			ans+=(D[i].cnt-D[i-1].cnt)*i;
		print(ans),pc('\n');
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：5)

没看到数据范围所以直接用 Lct 了。
# 思路：
考虑每次加一条边对答案的影响。以样例为例，先给个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/hyzsopsz.png)
本来这个图是个树，在 $1$ 和 $3$ 之间连边后，图中加粗的点构成了一个环，要让它重新成为一棵树，肯定是要在环上删掉一条边的，要想让最后的权值和最小，显然要删掉权值最大的边，即图中 $1$ 和 $2$ 之间的边。所以每次操作时，假设加的边为 $(u,v,w)$，只用把 $u$ 到 $v$ 路径上的最大值和 $w$ 比较，如果更优就重新连边就行了。要做的操作有删边，加边，查路径最大值，直接用 Lct 就行了。实现上，要维护路径最大边权，有一个技巧边转点，把每条边给开一个点，点权就是边权，在把这个点向 $u,v$ 连边就行了。
# Code:
打的唐氏范浩强实现 Lct 有一点慢，要卡下常，调下随机种子，多交几次就过了。

```
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m,k;
struct node
{
	int x,y,z,w;
};
namespace Elaina
{
	int stk[400005],top;
	struct fhq
	{
		int l,r,f,pre,tag,rnd;
		node val,maxn;
	}t[400005];
	inline node Max(node x,node y)
	{
		if(x.w<y.w) return y;
		return x;
	}
	inline int isroot(int p){return (t[t[p].f].l!=p&&t[t[p].f].r!=p)||!t[p].f;}
	inline void down(int p)
	{
		if(!t[p].tag) return;
		if(t[p].l) t[t[p].l].tag^=1;
		if(t[p].r) t[t[p].r].tag^=1;
		swap(t[p].l,t[p].r);
		t[p].tag=0;
	}
	inline void update(int p)
	{
		t[p].maxn=t[p].val;
		if(t[p].l) t[p].maxn=Max(t[p].maxn,t[t[p].l].maxn),t[t[p].l].f=p;
		if(t[p].r) t[p].maxn=Max(t[p].maxn,t[t[p].r].maxn),t[t[p].r].f=p;
	}
	int merge(int x,int y)
	{
		if(!x||!y) return x|y;
		down(x);down(y);
		if(t[x].rnd<t[y].rnd)
		{
			t[x].r=merge(t[x].r,y);
			update(x);
			return x;
		}
		else
		{
			t[y].l=merge(x,t[y].l);
			update(y);
			return y;
		}
	}
	void split(int p,int &x,int &y)
	{
		if(!top)
		{
			down(p);
			x=p;y=t[p].r;
			t[p].r=0;
			update(p);
			return;
		}
		int flag=stk[top--]^t[p].tag;
		down(p);
		if(!flag) x=p,split(t[p].r,t[p].r,y);
		else y=p,split(t[p].l,x,t[p].l);
		update(p);
	}
	inline int markroot(int p)
	{
		top=0;
		while(!isroot(p))
		{
			stk[++top]=(t[t[p].f].l==p);
			p=t[p].f;
		}
		return p;
	}
	inline int findroot(int p)
	{
		p=markroot(p);
		down(p);
		while(t[p].l) down(p=t[p].l);
		return p;
	}
	inline int access(int p)
	{
		int last=0;
		while(p)
		{
			int a,b;
			split(markroot(p),a,b);
			t[findroot(last)].pre=0;
			last=merge(a,last);
			t[findroot(b)].pre=p;
			p=t[findroot(last)].pre;
		}
		return last;
	}
	inline void makeroot(int p)
	{
		t[access(p)].tag^=1;
	}
	inline void link(int x,int y)
	{
		makeroot(x);
		t[x].pre=y;
	}
	inline void cut(int x,int y)
	{
		makeroot(x);
		access(y);access(x);
		t[y].pre=0;
	}
	inline node query(int x,int y)
	{
		makeroot(x);
		return t[access(y)].maxn;
	}
	inline void change(int x,int u,int v,int w)
	{
		makeroot(x);
		t[x].val=t[x].maxn=(node){u,x,v,w};
	}
}
using namespace Elaina;
int ans;
int main()
{
	srand(time(NULL));
	read(n,m);
	for(int i=1;i<=2*n;i++) t[i].rnd=rand();
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		read(u,v,w);
		link(u,n+i);link(v,n+i);
		change(n+i,u,v,w);
		ans+=w;
	}
	while(m--)
	{
		int u,v,w;
		read(u,v,w);
		node p=query(u,v);
		if(p.w>w)
		{
			ans+=w-p.w;
			cut(p.x,p.y);cut(p.y,p.z);
			link(u,p.y);link(p.y,v);
			change(p.y,u,v,w);
		}
		write(ans),putch('\n');
	}
	flush();
}
```

---

## 作者：ttq012 (赞：5)

ATcoder 最手的一集。

动态加边维护最小生成树，显然第一感就是 LCT。直接维护一下两个点之间的连通性和两个点之间边权最大的边是哪一条。如果对于一条插入的边，两个点没有连通，那么就连通一下；否则找到边权最大的那一条边并将那一条边替换为新加的那一条边即可。

---

## 作者：ran_qwq (赞：2)

值域巨小无比，考虑从此下手。

我们维护 $10$ 个并查集 $D_i$，$D_i$ 维护只通过边权 $\le i$ 的边图连通性。

首先初始状态 MST 边权和即为所有边相加。接着从小到大遍历每个并查集，如果遍历到 $i$ 时 $x$ 和 $y$ 连通，则表示 MST 中 $x$ 到 $y$ 的边权最大值为 $i$（满足单调性，$i-1$ 不连通，$i$ 连通）。如果 $z<i$ 则可以删去一条边权为 $i$ 的边，加上边权为 $z$ 的边，答案减去 $i-z$。

为什么这样是对的呢？首先 MST 中如果要加上 $x$ 和 $y$ 之间边权为 $z$ 的边，就必须删除且只删除一条原来的 MST 中 $x$ 到 $y$ 路径上的边，要让边权和最小就肯定选最大的删。

```cpp
int n,m,id,ans;
struct DSU {
	int fa[N];
	int fd(int x) {return x==fa[x]?x:fa[x]=fd(fa[x]);}
	void mg(int x,int y) {x=fd(x),y=fd(y); if(x==y) return; fa[x]=y;}
}D[11];
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=10;i++) for(int j=1;j<=n;j++) D[i].fa[j]=j;
	for(int i=1,x,y,z;i<n;i++) {
		x=rd(),y=rd(),z=rd(),ans+=z;
		for(int j=z;j<=10;j++) D[j].mg(x,y);
	}
	for(int x,y,z;m--;) {
		x=rd(),y=rd(),z=rd();
		for(int i=1;i<=10;i++) if(D[i].fd(x)==D[i].fd(y)) {ans-=max(i-z,0); break;}
		for(int i=z;i<=10;i++) D[i].mg(x,y);
		wr(ans,"\n");
	}
}
```

---

## 作者：fengzhaoyu (赞：2)

## 题意
凡是学了树的，都会想到最小生成树。说实话，挺板的。
## 思路
就是最小生成树，只不过有 $q$ 次访问。

- 建立 $10$ 个并查集，因为它的范围只有 $10$。

- 如果新加的边权大于原来此边的权值，就删除原来的，加入新的边权再并查集。

- 不过似乎加了一点动态规划，所以是绿题。
不会最小生成树的可以去看[这道题](https://www.luogu.com.cn/problem/P1551)。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;//我也不知道为什么自己开这么大
int n,q;
int ans;
vector<pair<int,int> >G[N];
struct edge{
	int fa[N];
	int find(int x){return x==fa[x]?x: (fa[x]=find(fa[x]));}
	inline void join(int x,int y){int f1=find(x),f2=find(y);if(f1!=f2)fa[f1]=f2;}
	inline bool sme(int x,int y){return find(x)==find(y);}
}e[11];

void add(int u,int v,int w){
	if(e[w].sme(u,v))return ;
	for(int i=w;i<=10;i++){
		if(e[i].sme(u,v)){
			ans-=i;
			ans+=w;
			break;
		}
		e[i].join(u,v);
	} 
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		G[w].push_back({u,v});
	}
	for(int i=1;i<=n;i++)e[0].fa[i]=i;
	for(int i=1;i<=10;i++){
		for(int j=1;j<=n;j++){
			e[i].fa[j]=e[i-1].fa[j];
		}
		for(auto t:G[i]){
			int u=t.first;
			int v=t.second;
			ans+=i;
			e[i].join(u,v);
		}
	}
	for(int i=1;i<=q;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		cout<<ans<<endl;
	} 
	return 0;
}
```
唉，第三题没审过，只能靠此题了，~~求管理员过~~。

---

## 作者：cheng2010 (赞：2)

# MST Query
## 思路
~~LCT模版。~~

发现，权值很小，可以用它做点文章，设 $cnt_{i}$ 为：权值 $\le i$ 的**边**的个数。明显可以用并查集维护。

推荐加上启发式合并优化一下。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+7;
int f[N][11],siz[N][11],cnt[11];
int n,m;
inline int Find(int i,int x)
{
	return x==f[x][i]?x:f[x][i]=Find(i,f[x][i]);
}
inline void merge(int i,int x,int y)
{
	int xx=Find(i,x);
	int yy=Find(i,y);
	if(xx!=yy)
	{
		if(siz[xx][i]>siz[yy][i])
		{
			swap(xx,yy);
		}
		f[xx][i]=yy;
		siz[yy][i]+=siz[xx][i];
		cnt[i]++;
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=10;j++)
		{
			f[i][j]=i;
			siz[i][j]=1;
		}
	}
	for(int i=1;i<=n-1;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		for(int j=z;j<=10;j++)
		{
			merge(j,x,y);
		}
	}
	while(m--)
	{
		int x,y,z;
		cin>>x>>y>>z;
		for(int i=z;i<=10;i++)
		{
			merge(i,x,y);
		}
		int ans=cnt[1];
	//	cout<<cnt[1]<<" ";
		for(int i=2;i<=10;i++)
		{
	//		cout<<cnt[i]<<" ";
			ans+=(cnt[i]-cnt[i-1])*i;
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：AK_400 (赞：2)

## 题意
给你一棵树，每次询问加一条边，查询最小生成树的边权和。
## 题解
动态求 `MST` 肯定 `LCT`。

维护链上最大权值和带有最大权值的节点，加边（设加一条端点为 $a$，$b$，权值为 $c$ 的边）时判断端点为 $a$，$b$ 的链上的最大权值是否比 $c$ 大，如果是，则删去这条链上边权最大的边，加入端点为 $a$，$b$ 的边即可。

边权只需要新开一个点，权值设为此边权，连到这条边的两端点即可。
## Code
```cpp
#include<bits/stdc++.h>
#define int  long long
using namespace std;
int lz[600005],vl[600005],fa[600005],ch[600005][2],id[600005],mx[600005];
void pu(int x){
    mx[x]=vl[x],id[x]=x;
    if(mx[ch[x][0]]>mx[x])mx[x]=mx[ch[x][0]],id[x]=id[ch[x][0]];
    if(mx[ch[x][1]]>mx[x])mx[x]=mx[ch[x][1]],id[x]=id[ch[x][1]];
    return;
}
void tr(int x){
    swap(ch[x][0],ch[x][1]);
    lz[x]^=1;
    return;
}
void pd(int x){
    if(!lz[x])return;
    if(ch[x][0])tr(ch[x][0]);
    if(ch[x][1])tr(ch[x][1]);
    lz[x]=0;
    return;
}
bool nr(int x){
    return ch[fa[x]][0]==x||ch[fa[x]][1]==x;
}
bool get(int x){
    return ch[fa[x]][1]==x;
}
void rot(int x){
    int y=fa[x],z=fa[y],c=get(x);
    if(nr(y))ch[z][get(y)]=x;
    fa[x]=z;
    ch[y][c]=ch[x][!c];
    if(ch[x][!c])fa[ch[x][!c]]=y;
    ch[x][!c]=y;
    fa[y]=x;
    pu(y);
    pu(x);
    return;
}
void upd(int x){
    if(nr(x))upd(fa[x]);
    pd(x);
    return;
}
void splay(int x){
    upd(x);
    for(int f=fa[x];nr(x);rot(x),f=fa[x])
        if(nr(f))rot(get(x)==get(f)?f:x);
    return;
}
int acs(int x){
    int p=0;
    for(;x;p=x,x=fa[p]){
        splay(x),ch[x][1]=p,pu(x);
    }
    return p;
}
void mkr(int x){
    acs(x),splay(x),tr(x);
    return;
}
int fr(int x){
    acs(x),splay(x),pd(x);
    while(ch[x][0])x=ch[x][0],pd(x);
    return  splay(x),x;
}
void split(int x,int y){
    mkr(x),acs(y),splay(y);
    return;
}
void link(int x,int y){
    mkr(x);
    if(fr(y)!=x)fa[x]=y;
    return;
}
bool chk(int x,int y){
    return fr(x)==fr(y);
}
int n,q,a,b,c,ans;
signed main() {
    ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=1;i<n;i++){
        cin>>a>>b>>c;
        vl[i+n]=c;
        link(a,i+n),link(b,i+n);
        ans+=c;
    }
    for(int i=1;i<=q;i++){
        cin>>a>>b>>c;
        split(a,b);int p=id[b];
        if(mx[b]<=c){
            cout<<ans<<endl;
            continue;
        }
        ans=ans-mx[b]+c;
        splay(p);
        fa[ch[p][0]]=fa[ch[p][1]]=0;
        vl[i+n+n]=c;
        link(a,i+n+n),link(b,i+n+n);
        cout<<ans<<endl;
    }
    return 0;
}   
```

---

## 作者：roger_yrj (赞：1)

考虑到这道题边权非常小。所以我们建 $10$ 个并查集。第 $i$ 个并查集表示当边权小于等于 $i$ 的边加进来后的连通情况。

每次加入一条边权为 $w$ 边时，看看这条边所连的两个连通块何时第一次被连通。假设当边权小于等于 $w'$ 的边加进来后第一次连通，那么就将这条连通的边换成新的边即可。答案减去 $(w'-w)$。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int f[20][N],n,q;
int find(int x,int y){
	if(f[y][x]==x)return x;
	return f[y][x]=find(f[y][x],y);
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)for(int j=1;j<=10;j++)f[j][i]=i;
	int ans=11*(n-1); 
	for(int k=1;k<n+q;k++){
		int x,y,z;
		cin>>x>>y>>z;
		for(int i=10;i>=z;i--){
			int u=find(x,i),v=find(y,i);
			if(u!=v)ans--,f[i][u]=v;
		}
		if(k>=n)cout<<ans<<"\n";
	}	
}
```

---

## 作者：Drest (赞：1)

# [ABC355F] MST Query 题解

[luogu](https://www.luogu.com.cn/problem/AT_abc355_f)
|
[atcoder](https://atcoder.jp/contests/abc355/tasks/abc355_f)

## 解题思路

由于边的权值很小，所以可以考虑贪心。

开 $10$ 个并查集，其中第 $i$ 个并查集代表边权 $\le i$ 的边都联通了哪些点。

用 `sum[]` 数组存储第 $i$ 个并查集**未连点的数量**，在查询时可以使用贪心从 $i = 1$ 跑到 $10$，此时仍需要连边的数量为 `sum[i - 1] - sum[i]`，计算其贡献即可（注意 `sum[0]` 应为 $n$）。

附上 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct dsu {
    int fa[N] {};
    int find(int x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        fa[y] = x;
        return true;
    }
    dsu() {
        for (int i = 0; i < N; i++)
            fa[i] = i;
    }
}tr[15];
int sum[15];
int n, q;
signed main() {
    cin >> n >> q;
    for (int i = 0; i <= 10; i++)
        sum[i] = n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        for (int j = w; j <= 10; j++) {
            sum[j] -= tr[j].merge(u, v);
        }
    }
    while (q--) {
        int u, v, w;
        cin >> u >> v >> w;
        for (int j = w; j <= 10; j++) {
            sum[j] -= tr[j].merge(u, v);
        }
        int ans = 0, lst = n;
        for (int j = 1; j <= 10; j++) {
            ans += j * (lst - sum[j]);
            lst = sum[j];
        }
        cout << ans << endl;
    }
    return 0;
}
``````

---

## 作者：yaaaaaan (赞：1)

### 思路
这道题我们观察题目范围，可知权值的范围很小。所以我们考虑枚举权值，计录这种权值的边对答案的变化 $dp_i$。

对于一条边，我们用并查集记录这条边加进去会不会构成环。

*   如果这条边**不会构成环**且**不在最小生成树**内，则加入这条边，变化量加上这条边的权值。

*   如果这条边**构成环**且**在最小生成树**内，则去掉这条边，变化量减去这条边的权值。

最后对 $dp$ 数组求一遍前缀和就是答案。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,q;
int a[500005],b[500005],c[500005],dp[500005];
int num[500005];
int fa[500005];
int find(int x)
{
	if(fa[x]==x) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
bool merge(int x,int y)
{
	int xx=find(x),yy=find(y);
	if(xx==yy) return false;
	if(num[xx]>num[yy]) swap(xx,yy);
	num[yy]+=num[xx];
	fa[xx]=yy;
	return true;
}
bool fl[500005];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n+q-1;i++)
	{
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=200005;j++) 
		{
			fa[j]=j;
			num[j]=1;
		}
		for(int j=1;j<=n+q-1;j++)
		{
			if(c[j]<=i)
			{
				if(merge(a[j],b[j]))
				{
					if(!fl[j])
					{
						fl[j]=1;
						dp[j]+=i;
					}
				}
				else
				{
					if(fl[j])
					{
						dp[j]-=i;
						fl[j]=0;
					}
				}
			}
		}
	}
	for(int i=1;i<=n+q-1;i++) dp[i]+=dp[i-1];
	for(int i=n;i<=n+q-1;i++)
	{
		cout<<dp[i]<<"\n";
	}
	return 0;
}



```

---

## 作者：gdf_yhm (赞：1)

[abc355f](https://www.luogu.com.cn/problem/AT_abc355_f)

~~直接贺 lct 维护 mst 的代码。~~

### 思路

观察到 $w_i\le 10$，考虑分开建 $10$ 个图表示边权小于等于 $i$ 的边组成的图。连并查集，记录当前图连了 $siz_i$ 条边。

可以发现第 $i-1$ 个图是第 $i$ 个图的子图。所以差分 $siz_i-siz_{i-1}$ 可以得到原图的最小生成树中边权为 $i$ 的边数。

复杂度 $O(n\max w_i)$。

### code

```cpp
int n,m;
int f[11][maxn],siz[11];
int fd(int id,int x){
	if(f[id][x]==x)return x;
	return f[id][x]=fd(id,f[id][x]);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=10;i++)for(int j=1;j<=n;j++)f[i][j]=j;
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		for(int j=w;j<=10;j++)if(fd(j,u)!=fd(j,v))f[j][fd(j,u)]=fd(j,v),siz[j]++;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		for(int j=w;j<=10;j++)if(fd(j,u)!=fd(j,v))f[j][fd(j,u)]=fd(j,v),siz[j]++;
		int ans=0;
		for(int j=1;j<=10;j++)ans+=(siz[j]-siz[j-1])*j;
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc355_f)   
没打，但是赛时看了一眼题，这个 F 怎么还出板子呢。    
## 题意
维护一个动态 MST。   
## 解法
一眼 LCT。   
我们注意到：在一棵树上，每次加入一条边会产生一个环。并且在这个环上删掉任意一条边它都又会变成一棵树。    
所以我们只需要用 LCT 维护最大值即可。每次用它和新加入的边权进行比较就行了。   
注意需要把边拆开。   
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=1e6;
int n,m,fa[N+10],ch[N+10][2],val[N+10],st[N+10],ans,pos[N+10];
DSU d;
bool tag[N+10];
il bool isroot(int x){
	int f=fa[x];
	ret ch[f][0]!=x&&ch[f][1]!=x;
}
il int which(int x){
	ret ch[fa[x]][1]==x;
}
il void update(int x){
	pos[x]=x;
	if(val[pos[ch[x][0]]]>val[pos[x]]){
		pos[x]=pos[ch[x][0]];
	}
	if(val[pos[ch[x][1]]]>val[pos[x]]){
		pos[x]=pos[ch[x][1]];
	}
}
il void rotate(int x){
    int y=fa[x],z=fa[y];
	int kx=which(x),ky=which(y),w=ch[x][kx^1];
	if(!isroot(y)){
		ch[z][ky]=x;
	}
	ch[x][kx^1]=y;
	ch[y][kx]=w;
	if(w){
		fa[w]=y;
	}
	fa[x]=z;
	fa[y]=x;
	update(y);
	update(x);
}
il void pushdown(int x){
	if(!tag[x]){
		ret;
	}
	tag[x]=0;
	tag[ch[x][0]]^=1;
	tag[ch[x][1]]^=1;
	_swap<int>(ch[x][0],ch[x][1]);
}
il void splay(int x){
    int y=x,z,siz=0;
	st[++siz]=y;
	while(!isroot(y)){
		y=fa[y];
		st[++siz]=y;
	}
	while(siz){
		pushdown(st[siz--]);
	}
	while(!isroot(x))
	{
		y=fa[x],z=fa[y];
		if(!isroot(y)){
			if((ch[y][0]==x)^(ch[z][0]==y)){
				rotate(x);
			}else{
				rotate(y);
			}
		}
		rotate(x);
	}
	update(x);
}
il void access(int x){
	int y=0;
	while(x){
		splay(x);
		ch[x][1]=y;
		update(x);
		y=x;
		x=fa[x];
	}
}
il void makeroot(int x){
	access(x);
	splay(x);
	tag[x]^=1;
}
il int findroot(int x){
	access(x);
	splay(x);
	while(ch[x][0]){
		pushdown(x);
		x=ch[x][0];
	}
	ret x;
}
il void link(int x,int y){
	makeroot(x);
	if(findroot(y)!=x){
		fa[x]=y;
		update(y);
	}
}
il void split(int x,int y){
	makeroot(x);
	access(y);
	splay(y);
}
il void cut(int x,int y){
	split(x,y);
	if(ch[y][0]==x){
		ch[y][0]=0;
		fa[x]=0;
		update(y);
	}
}
struct edge{
	int x,y,w;
}a[N+10];
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<int>();
	m=read<int>();
	d.Init(n+m+10);
	for(int i=1;i<n+m;i++){
		a[i].x=read<int>();a[i].y=read<int>();
		a[i].w=read<int>();
	}
	for(int i=1;i<n+m;i++){
		val[i+n]=a[i].w;
	}
	for(int i=1;i<n+m;i++){
		pos[i+n]=i;
	}
	for(int i=1;i<n+m;i++){
		int x=a[i].x,y=a[i].y;
		if(d.Check(x,y)){
			int p;
			split(x,y);
			p=pos[y];
			if(val[p]>a[i].w){
				cut(a[p-n].x,p);
				cut(p,a[p-n].y);
				ans-=a[p-n].w;
				link(x,i+n);
				link(i+n,y);
				ans+=a[i].w;
			}
		}else{
			d.Join(x,y);
			link(x,i+n);
			link(i+n,y);
			ans+=a[i].w;
		}
		if(i>n-1){
			write(ans);
			edl;
		}
	}
	ret 0;
}
```

---

## 作者：Otue (赞：1)

我用 LCT 花了 10min 切掉了这道题，但觉得很无趣。

于是注意到一个条件，$1\leq w_i\leq 10$。

考虑从边权入手维护最小生成树。$tr_i$ 维护边权小于等于 $i$ 的所有边构成的生成树的边的数量。

因为我们最小生成树从小到大加边，则意味着从边权 $1$ 开始考虑，一直到 $10$，每次加入是这个边权的边。如何每次快速加入？事实上，$tr_i-tr_{i-1}$ 就是边权 $i$ 加入的边数，证明显然。

复杂度 $O(10\times n)$。忽略并查集复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5;

int n, m;

struct edge {
	int cnt = 0;
	int p[N];
	void init() {
		_for(i, 1, n) p[i] = i;
	}
	int find(int x) {
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) p[fx] = fy, cnt++;
	}
}tr[12];

signed main() {
	cin >> n >> m;
	_for(i, 1, 10) tr[i].init();
	_for(i, 1, n - 1) {
		int u, v, w;
		cin >> u >> v >> w;
		_for(j, w, 10) tr[j].merge(u, v);
	}
	_for(i, 1, m) {
		int u, v, w;
		cin >> u >> v >> w;
		_for(j, w, 10) tr[j].merge(u, v);
		int res = tr[1].cnt;
		_for(j, 2, 10) res += (tr[j].cnt - tr[j - 1].cnt) * j;
		cout << res << endl;
	}
}
```

---

## 作者：Merge_all (赞：1)

### 思路：
- 通过**数据范围**可以发现：$c_{i},w_{i} \le 10$，所以我们可以考虑从**数值**下手。
- **先用一层循环单独枚举权值**。
- 要加入一条边，我们要判断 $u_{i}$ 和 $v_{i}$ **是否联通**，如果**不联通**且还**不在最小生成树中**的话，就要加入。若**联通**且**在最小生成树**中，就要去掉这一条边。
- 定义 $dp_{i}$ 是**上一轮到这一轮的变化量**，$flag_{i}$ 记录是第 $i$ 条边**是否在最小生成树中**。
- 最后输出答案之前需要将 $dp$ 数组进行**前缀和**。

### 代码：
```
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
const int N=500010;

int n,q;
int dp[N],a[N],b[N],c[N];
bool flag[N];
struct node{
	int f[N],deep[N];
	void init(){rep(i,1,n)f[i]=i,deep[i]=1;}
	int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
	bool merge_set(int x,int y){
		x=find(x),y=find(y);
		if(x==y) return 0;
		if(deep[x]>deep[y]) swap(x,y);
		f[y]=x;
		deep[y]+=deep[x];
		return true;
	}
}U;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	rep(i,1,n+q-1){
		cin>>a[i]>>b[i]>>c[i];
	}
	rep(v,1,10){
		U.init();
		rep(i,1,n+q-1){
			if(c[i]<=v){
				if(U.merge_set(a[i],b[i])){
					if(!flag[i]){
						flag[i]=1;
						dp[i]+=v;
					}
				}
				else{
					if(flag[i]){
						flag[i]=0;
						dp[i]-=v;
					}
				}
			}
			
		}
	}
	rep(i,1,n+q-1) dp[i]=dp[i-1]+dp[i];
	rep(i,n,n+q-1) cout<<dp[i]<<" ";
	return 0;
}
```

---

## 作者：Three_leaf (赞：0)

### 题面
给你一棵 $n$ 个点的带边权的树，有 $q$ 次询问，每次询问加一条带边权的边，输出当前的最小生成树的边权和。

### 思路
边权范围挺小的，只有十。考虑用 $10$ 个并查集维护一下每种边构成的森林，对于每个新加进来的边 $(u,v)$，显然对于一个 $u,v$ 不在一块的，我们都可以用这条边让他联通，在每个边加进来时算一下贡献就行了。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 200005 
using namespace std;
int f[11][Maxn];
int find(int x,int f[]) {
    if(x == f[x])return x;
    return f[x]=find(f[x],f);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)for(int j=1;j<11;j++)f[j][i]=i;
    int ans=(n-1)*10; n--;
    while(n--) {
    int u,v,w;cin>>u>>v>>w;
    for(int j=w;j<10;j++) {
        int fu=find(u,f[j]),fv=find(v,f[j]);
        if(fu != fv)ans--,f[j][fu]=fv;else break;
    } }
    while(q--) {
    int u,v,w;cin>>u>>v>>w;
    for(int j=w;j<10;j++) {
        int fu=find(u,f[j]),fv=find(v,f[j]);
        if(fu != fv)ans--,f[j][fu]=fv;else break;
    } cout<<ans<<"\n";} 
    return 0;
}
```

---

## 作者：Harry1000 (赞：0)

前置知识：[并查集](https://oi-wiki.org/ds/dsu/)  
备注：在此题解中，$m$ 表示边数。
# 题目大意
给你一个带有 $n$ 个点的树，又有 $q$ 次询问，每次询问给这个图加一条连接点 $x$ 与点 $y$，权值为 $z$ 的边，请输出每次增加边后这张图的最小生成树。
# 暴力
看到这道题，第一个想法就是暴力。  
每次加一条边后，重新给图做一次最小生成树，再输出答案。
时间复杂度为 $O(qm\log m)$，会超时。
# 优化
其实没有必要每次加入一条边以后重新给数组排序，只需要把这条边插入到对应的位置就可以了。  
时间复杂度为 $O(qm)$，有所优化，但仍然会超时。
# 正解
我们发现时间复杂度中的 $q$ 是不能省掉的，只能把 $m$ 替换成能够更小的数。  
观察题目，发现 $z\le10$，非常小，所以我们可以考虑关于 $z$ 的做法。  
当加入一条边时，有两种情况：要么替换成最小生成树里的另一条边，要么什么也没有发生。
当这条边替换成最小生成树里的另外一条边时，把这条边加入拥有要替换的边的图后会形成环，而且加入的边的权值比要替换的边的权值小。  
题目并没有让我们求出具体选了那些边，所以我们只需要求出要替换的边和加入的边的权值差，再用上一次的最小生成树减去这个值。  
因为我们要求权值差，所以我们可以建 $10$ 张图，编号为 $1\sim10$，编号为 $i$ 的图存储权值不大于 $i$ 的边，每次加入一条边后对允许这条边的权值加入的图进行遍历，用并查集查看插入这条边后这张图会不会形成环，如果形成了环，说明要替换的边的权值是这张图的编号，用这张图的编号减去加入那条边的权值就求出了要替换的边和加入的边的权值差，最后的答案就是用上一次的最小生成树减去这个值。  
时间复杂度为 $O(qz)$。
# 参考代码
```cpp
#include<bits/stdc++.h>
#define fo(i,x,y) for(int i=x;i<=y;i++)
using namespace std;
int f[11][200001];//建立10张图，用并查集检查两点之间是否成环 
int z(const int &x,const int y)//并查集 
{
	if(f[x][y]!=y)
		f[x][y]=z(x,f[x][y]);
	return f[x][y];
}
int main()
{
	int n,m,w,x,y,s=0;
	scanf("%d%d",&n,&m);
	fo(i,1,10)
	{
		fo(j,1,n)
			f[i][j]=j;
	}
	fo(i,1,n-1)
	{
		scanf("%d%d%d",&w,&x,&y);
		s+=y;//开始给出一棵树，无需做最小生成树 
		fo(j,y,10)
			f[j][z(j,w)]=z(j,x);//更新图 
	}
	fo(i,1,m)
	{
		scanf("%d%d%d",&w,&x,&y);
		fo(j,y,10)
		{
			if(z(j,w)==z(j,x))//判断是否构成环
			{
				s-=j-y;
				fo(k,y,j-1)//更新插入这条边后的图 
					f[k][z(k,w)]=z(k,x);
				break;
			}
		}
		printf("%d\n",s);
	}
	return 0;
}
```

---

## 作者：Butterfly_qwq (赞：0)

这道题主流做法有两种。

第一种：

注意到边权极小，可以统计边贡献，维护 $10$ 个并查集，但是我不太会，大家可以看看 [Iceturky 大佬的题解](https://www.luogu.com.cn/article/sq955qbo)。

第二种：

考虑我们把边权放到 $10^9$，那上一种方法不就寄了？

考虑 LCT，每加一条边 $(u,v,w)$ 就可以查询一下 $u$ 和 $v$ 这条链上的最大值，如果最大值比 $w$ 大把最大值 cut 掉，把我们这条边 link 上，否则什么也不干。

然后你发现 LCT 好像没办法处理边权问题，那么你可以当连一条 $(u,v,w)$ 的边时，创立一个点权为 $w$ 的点 $id$，然后连一条 $(u,id)$ 和一条 $(v,id)$。

然后由于这种方法太好想了，写的时候根本没看到边权范围，白打了一遍 LCT，然后成功没写完 E，赢！

[Code：](https://atcoder.jp/contests/abc355/submissions/53871665)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=600005;
int n,q,ans,mx[N],id[N],w[N],ch[N][2],fa[N],lazy[N];
struct edge
{
	int u,v,w;
}e[N];
bool isheavy(int u)
{
	return ch[fa[u]][0]==u||ch[fa[u]][1]==u;
}
void pushup(int u)
{
	mx[u]=w[u];id[u]=u;
	if(ch[u][0]&&mx[ch[u][0]]>mx[u])
	{
		mx[u]=mx[ch[u][0]];
		id[u]=id[ch[u][0]];
	}
	if(ch[u][1]&&mx[ch[u][1]]>mx[u])
	{
		mx[u]=mx[ch[u][1]];
		id[u]=id[ch[u][1]];
	}
}
void pushlazy(int u)
{
	if(u)
	{
		swap(ch[u][0],ch[u][1]);
		lazy[u]^=1;
	}
}
void pushdown(int u)
{
	if(lazy[u])
	{
		lazy[u]=0;
		pushlazy(ch[u][0]);
		pushlazy(ch[u][1]);
	}
}
void rotate(int u)
{
	int Fa,gfa,lr,son;
	Fa=fa[u];gfa=fa[Fa];lr=(ch[Fa][1]==u);son=ch[u][lr^1];
	if(isheavy(Fa))ch[gfa][ch[gfa][1]==Fa]=u;
	if(son)fa[son]=Fa;
	ch[u][lr^1]=Fa;
	ch[Fa][lr]=son;
	fa[Fa]=u;
	fa[u]=gfa;
	pushup(Fa);
	pushup(u);
}
int chain[N];
void splay(int u)
{
	int Fa=u,gfa,tot=1;
	chain[1]=u;
	while(isheavy(Fa))chain[++tot]=Fa=fa[Fa];
	while(tot)pushdown(chain[tot--]);
	while(isheavy(u))
	{
		Fa=fa[u];gfa=fa[Fa];
		if(isheavy(Fa))rotate((ch[Fa][0]==u)^(ch[gfa][0]==Fa)?u:Fa);
		rotate(u);
	}
	pushup(u);
}
void access(int u)
{
	int tmp=0;
	while(u)
	{
		splay(u);
		ch[u][1]=tmp;
		pushup(u);
		tmp=u;
		u=fa[u];
	}
}
void makeroot(int u)
{
	access(u);
	splay(u);
	pushlazy(u);
}
int findroot(int u)
{
	access(u);
	splay(u);
	while(ch[u][0])
	{
		pushdown(u);
		u=ch[u][0];
	}
	splay(u);
	return u;
}
void split(int u,int v)
{
	makeroot(u);
	access(v);
	splay(v);
}
void link(int u,int v)
{
	makeroot(u);
	fa[u]=v;
}
void cut(int u,int v)
{
	split(u,v);
	fa[u]=ch[v][0]=0;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<n;i++)
	{
		cin>>e[i].u>>e[i].v>>e[i].w;
		ans+=e[i].w;
		link(e[i].u,i+n);
		link(e[i].v,i+n);
		w[i+n]=e[i].w;
	}
	for(int i=1,u,v,w,k;i<=q;i++)
	{
		cin>>u>>v>>w;
		split(u,v);
		if(w>=mx[v])
		{
			cout<<ans<<'\n';
			continue;
		}
		ans-=mx[v];
		ans+=w;
		k=id[v];
		splay(u);
		cut(e[k-n].u,k);
		cut(e[k-n].v,k);
		link(u,i+2*n-1);
		link(v,i+2*n-1);
		::w[i+2*n-1]=w;
		e[i+n-1].u=u;
		e[i+n-1].v=v;
		cout<<ans<<'\n';
	}
}
```

---

## 作者：Pentiment (赞：0)

ABC 没活整了出板子是吧。

其实并不。

### Solution 1

当然就是我们可爱的 LCT 了。

加入一条边 $(u,v,w)$ 时，如果两个端点不连通，则将其加入 LCT；否则看 $u$ 到 $v$ 的路径上最大的边权 $w'$，如果 $w<w'$，则删去边权最大的边，将 $(u,v,w)$ 加入 LCT。

实现时由于 LCT 无法直接维护边权，我们将边权转点权，即新建一个权值为 $w$ 的点 $v'$，连接 $(u,v'),(v',v)$。

### Solution 2

我就想要基础做法怎么办。

注意到边权很小，不超过 $10$，考虑开 $10$ 个并查集，第 $i$ 个并查集维护只使用边权不大于 $i$ 的边时图的连通性，查询时找到 $i$ 最小的、使得图连通的并查集即可。

---

## 作者：Genius_Star (赞：0)

### 题意：

动态加边，求最小生成树的权值和。

### 思路：

简单题，考虑 LCT 维护最小生成树。

对于新加的边 $(u,v,w)$，会使得在最小生成树上 $u \to v$ 之间形成一个环。

则我们需要删掉环上任意一条边，使得生成树权值和更小。

令 $Max$ 表示原最小生成树上 $u \to v$ 路径上边权最大值，然后分情况讨论：

- 若 $w \ge Max$，则没必要加入这条边（不会使答案更优）。

- 否则 $w < Max$，则可以删掉 $Max$ 对应的这条边，将 $(u,v)$ 加入（使得权值和更小）。

时间复杂度为 $O((N+M) \log N)$。

~~代码屎山，就不放了。~~

---

