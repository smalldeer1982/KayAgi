# [ABC040D] 道路の老朽化対策について

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc040/tasks/abc040_d

ある国には $ N $ 個の都市があり、それぞれ $ 1 $ から $ N $ までの番号がつけられています。これらの都市間を結ぶ $ M $ 本の道路があり、$ i $ 本目の道路は都市 $ a_i $ と都市 $ b_i $ を結ぶもので、$ y_i $ 年に造られたものです。

この国の国民はとても心配性なので、あまりに古い道は事故の危険性が高いと考えて使わないことがあります。そこであなたは、この国の交通状況を調査することにしました。

$ Q $ 人の国民の情報が与えられます。$ j $ 人目の国民について、都市 $ v_j $ に住んでおり、造られた年が $ w_j $ 年以前 ($ w_j $ 年ちょうども含む) であるような道路を使わないことがわかっています。

それぞれの国民に対し、その人が住んでいる都市から道路のみを使って行き来できるような都市の個数を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 100,000 $
- $ 0\ ≦\ M\ ≦\ 200,000 $
- $ 1\ ≦\ a_i,b_i\ ≦\ N $
- $ a_i\ ≠\ b_i $
- $ 1\ ≦\ y_i\ ≦\ 200,000 $
- $ 1\ ≦\ Q\ ≦\ 100,000 $
- $ 1\ ≦\ v_j\ ≦\ N $
- $ 0\ ≦\ w_j\ ≦\ 200,000 $

### 部分点

- $ 50 $ 点分のテストケースでは、$ N\ ≦\ 1,000 $, $ M\ ≦\ 2,000 $, $ Q\ ≦\ 1,000 $ をみたす。

### Sample Explanation 1

$ Q $ 人それぞれの国民について、答えは以下のようになります。 - $ 1 $ 人目は都市 $ 1 $ に住んでおり、$ 2000 $ 年以前に造られた道を使いません。都市 $ 1 $ につながる唯一の道は $ 2000 $ 年に造られているので、都市 $ 1 $ 以外へ行くことができません。したがって答えは $ 1 $ となります。 - $ 2 $ 人目は都市 $ 1 $ に住んでおり、都市 $ 2 $ や $ 3 $ へ行くことができます。しかし、$ 1999 $ 年以前に造られた道を使わないので都市 $ 4 $ へ行くことはできません。したがって答えは $ 3 $ となります。 - $ 3 $ 人目は $ 1995 $ 年以前に造られた道を使いませんが、すべての道はそれより新しいため、すべての道をつかってすべての都市へ行くことができます。したがって答えは $ 5 $ となります。

### Sample Explanation 3

同じふたつの都市間を結ぶ道が $ 2 $ 本以上あることや、すべての道を使っても辿り着けない都市がありうることに注意してください。

## 样例 #1

### 输入

```
5 4
1 2 2000
2 3 2004
3 4 1999
4 5 2001
3
1 2000
1 1999
3 1995```

### 输出

```
1
3
5```

## 样例 #2

### 输入

```
4 5
1 2 2005
3 1 2001
3 4 2002
1 4 2004
4 2 2003
5
1 2003
2 2003
1 2001
3 2003
4 2004```

### 输出

```
3
3
4
1
1```

## 样例 #3

### 输入

```
4 5
1 2 10
1 2 1000
2 3 10000
2 3 100000
3 1 200000
4
1 0
2 10000
3 100000
4 0```

### 输出

```
3
3
2
1```

# 题解

## 作者：Wf_yjqd (赞：3)

## 前置知识：
[并查集](https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&tn=baidu&wd=%E5%B9%B6%E6%9F%A5%E9%9B%86)
## 题意：
$ n $ 个点，$ m $ 条边的无向图，给出每条边出现时间 $ y_i $。$ q $ 次询问，每次给出点 $ v_j $，和时间 $ w_j $，求出一个整数，表示从 $ v_j $ 出发，不经过出现时间 $ y_i \le w_j $ 的边，能到达的点的个数。
## 分析：
无向图的连通问题，想到用并查集，又想到可以离线处理建边，就成了并查集板子题。

根据时间将边和询问排序，依序连接两点，同时记录以 $ i $ 为根的树的大小，每次询问答案为 $ v_j $ 所在树的大小，及 $ v_j $ 祖先为根的树的大小。

最后按询问顺序输出答案即可。

可以不按质合并，总体复杂度不变，即 $ O(m \log m) $。
## code（含注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
struct Edge{//边
    int a,b,y;
    friend bool operator<(Edge xy,Edge zb){
        return xy.y>zb.y;//晚出现的在前
    }
}e[maxn];
struct Ask{//询问
    int v,w,i;
    friend bool operator<(Ask kn,Ask ai){
        return kn.w>ai.w;//与上相同
    }
}qq[maxn];
struct UF_Set{//并查集板子
    int fa[maxn],s[maxn];//某个前辈，树大小
    void init(int n){//初始化
        for(int i=1;i<=n;i++){
            fa[i]=i;
            s[i]=1;
        }
        return ;
    }
    int find(int ka){//寻找最终祖先
        return fa[ka]=ka==fa[ka]?ka:find(fa[ka]);
        /*相当于
        if(ka==fa[ka])
        	fa[ka]=ka;
        else
        	fa[ka]=find(fa[ka]);
        return fa[ka];
        */
    }
    void cnct(int xy,int zb){//连接
        int fxy=find(xy),fzb=find(zb);//找各自祖先
        if(fxy!=fzb){//相同不用连
            fa[fxy]=fzb;//认爹
            s[fzb]+=s[fxy];//统计树大小
        }
        return ;
    }
}s;
int n,m,q,j,ans[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].y);
    sort(e+1,e+m+1);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&qq[i].v,&qq[i].w);
        qq[i].i=i;
    }
    sort(qq+1,qq+q+1);
    j=1;
    s.init(n);
    for(int i=1;i<=q;i++){
        while(e[j].y>qq[i].w){//连边
            s.cnct(e[j].a,e[j].b);
            j++;
        }
        ans[qq[i].i]=s.s[s.find(qq[i].v)];//统计答案
    }
    for(int i=1;i<=q;i++)
        printf("%d\n",ans[i]);//原序输出
    return 0;
}
```


---

## 作者：残阳如血 (赞：1)

### $\textbf{Solution}$
统计连通性的问题，考虑**并查集**。

但是并查集只支持合并和查询，并不支持分裂。

如果在线处理这个问题，每个人的 $w$ 没有顺序关系，无法处理。

故考虑离线。

将所有边和人按照时间从大到小排序。

遍历每一个人，将其可以使用的道路加入并查集进行合并。

因为每个人的时间不增，所以每个人可以使用的道路是不减的，即并查集只有合并。

用一个指针（不是语法上的指针）维护当前加入的边，指针的下标不增。

总的时间复杂度为 $O(m\log m+q\log q)$，瓶颈在排序。

### $\textbf{Code}$

[record](https://atcoder.jp/contests/abc040/submissions/62486138)。

```cpp
#include <bits/stdc++.h>
const int N = 1e5 + 10, M = 2e5 + 10;

struct Edge {
	int u, v, t;
} e[M];

struct People {
	int id, p, t, ans;
} a[N];

int n, m, q, pos, fa[N], siz[N];
// siz 记录每个点的集合大小

void input() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1;
	for (int i = 1; i <= m; ++i)
		std::cin >> e[i].u >> e[i].v >> e[i].t;
	std::cin >> q;
	for (int i = 1; i <= q; ++i)
		std::cin >> a[i].p >> a[i].t, a[i].id = i;
}

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) fa[fx] = fy, siz[fy] += siz[fx];
}

int main() {
	input();
	
	std::sort(e + 1, e + m + 1, [](Edge x, Edge y){
		return x.t > y.t;
	}); // 按照时间排序
	std::sort(a + 1, a + q + 1, [](People x, People y){
		return x.t > y.t;
	}); // 按照时间排序
	
	for (int i = 1; i <= q; ++i) {
		while (pos < m && e[pos + 1].t > a[i].t) {
      // 加入边
			++pos;
			merge(e[pos].u, e[pos].v);
		}
		a[i].ans = siz[find(a[i].p)];
	}
	
	std::sort(a + 1, a + q + 1, [](People x, People y){
		return x.id < y.id;
	}); // 变回初始顺序
	
	for (int i = 1; i <= q; ++i)
		std::cout << a[i].ans << "\n";
	return 0;
}
```

---

## 作者：Hilaria (赞：1)

### 题意

[link](https://www.luogu.com.cn/problem/AT_abc040_d)

给你一个 $N$ 个点 $M$ 条边的图（相同两点间可能有多条边），每条边有一个权值。

现在有 $Q$ 个询问，每个询问给出两个数 $v_j$ 和 $w_j$，要求出从点 $v_j$ 开始，只能走边权大于 $w_j$ 的边，一共可以到达多少个点（包括当前点 $v_j$）。

我们可以把每个点的 $w_j$ 看做其点权，从点 $j$ 开始，只能走边权**大于**（没有等于！！）$j$ 的点权的边。

---

### 思路

对于每个询问，我们要求出从点 $v_j$ 开始，通过合法的边可以到达的点的个数，其实就是去掉不合法的边后，点 $v_j$ 所在的联通块的个数。

既然我们要维护每个联通块和其个数，那么我们可以用并查集来维护，记录每个点所属的联通块是哪个（用 $fa[i]$ 记录），还有每个联通块的数量（可以在合并时更新）。

然后我们对于每个询问都删除不合法的边，再更新相关联通块的信息？？很显然是不行的，不仅麻烦，而且时间复杂度也不对。

那既然删边不好搞，那就加边咯（保证只加不删，详见下文）。

先把所有询问按点权 $w_j$（年份限制）从大到小排序，每条边按边权（也就是年份）从大到小排序。

我们可以设两个变量 $i,j$，$i$ 指的是现在在算的排行第 $i$ 的那个询问（真实顺序可以开结构体记录），$j$ 指的是现在已经加边加到第 $j$ 条边（第 $j$ 条边还没加）。

一开始，图上没有边，所以每个点的 $fa$ 都是自己，然后不断加入合法的边。

从 $1\sim n$ 遍历 $i$（已排序），对于每一个询问 $i$，从当前加到的第 $j$ 条边开始继续加对于自己的年份合法的边。

为什么 $j$ 不用从头开始遍历查询呢，会不会前面有对于当前询问的点 $i$ 不合法的边？

不会。

- 证明

	首先，我们知道点 $i$ 只能走边权比自己的点权（年份限制）**要大**的边。

	然后经过排序后，点 $i-1$ 的点权一定比点 $i$ 的点权要大。

   而对于点 $i-1$ 合法的边，其边权一定比点 $i-1$ 的点权大。

	而因为点 $i-1$ 的点权一定比点 $i$ 的大，所以之前加的边的边权一定比当前点 $i$ 的点权大，对于点 $i$ 就一定是合法的边，证毕。

这么说有点抽象啊，我们用样例 $2$ 举个栗子。

```cpp
4 5
1 2 2005
3 1 2001
3 4 2002
1 4 2004
4 2 2003
5
1 2003
2 2003
1 2001
3 2003
4 2004
```
然后排序后就变成了酱紫。

```
( id 是原来的输入顺序)

边						询问

id:1  1 2 2005			id:5  4 2004
id:4  1 4 2004			id:1  1 2003
id:5  4 2 2003			id:2  2 2003
id:3  3 4 2002			id:4  3 2003
id:2  3 1 2001			id:3  1 2001

```

我们的 $i$ 在这，$j$ 在这。

```
( id 是原来的输入顺序)

    边						询问

j->  id:1  1 2 2005			id:5  4 2004   <-i
    id:4  1 4 2004			id:1  1 2003
    id:5  4 2 2003			id:2  2 2003
    id:3  3 4 2002			id:4  3 2003
    id:2  3 1 2001			id:3  1 2001

```
我们看 $j$ 这条边啊，非常符合这个 $i$ 点的点权（因为 $2005>2004$），那就把这条边加进图中。如果本来这条边的两个端点就在同一个联通块内就不管它了，否则并查集合并一下，并更新合并后联通块的点数。

然后 $j$ 往下遍历，到下一条边（$id$ 为 $4$ 的那个），发现这条边对于点 $i$ 不合法了（因为 $2004=2004$，要严格大于），那就跳出遍历 $j$ 的循环，但是 $j$ 要保留下来，下次继续从现在遍历到的这个 $j$ 开始遍历。然后总结一下点 $i$ 的答案（直接通过并查集找出点 $i$ 所在联通块的数量），然后继续往下遍历 $i$，直到算完所有询问为止。

时间复杂度 $O(m\log m)$ 。

- 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXX=2e5+10;

int n,m,q;
int fa[MAXX],num[MAXX];
int ans[MAXX];
struct Edge
{
	int from;
	int to;
	int val;
	bool operator<(const Edge &rhs) const
	{
		return val>rhs.val;
	}
}edges[MAXX];

struct People
{
	int id;
	int city;
	int val;
	bool operator<(const People &rhs) const
	{
		return val>rhs.val;
	}
}pep[MAXX];

void init()
{
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		num[i]=1;
	}
}

int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);	//路径压缩
}

void merge(int x,int y)			//合并
{
	int fax=find(x);
	int fay=find(y);
	if(fax==fay) return ;
	fa[fax]=fay;
	num[fay]+=num[fax];
	num[fax]=0;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&edges[i].from,&edges[i].to,&edges[i].val);
	}
	sort(edges+1,edges+1+m);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&pep[i].city,&pep[i].val);
		pep[i].id=i;
	}
	sort(pep+1,pep+1+q);
	init();
	int i=1,j=1;
	while(i<=q)
	{
		while(edges[j].val>pep[i].val&&j<=m)	//不断加边
		{
			merge(edges[j].from,edges[j].to);
			j++;
		}
		int fai=find(pep[i].city);
		ans[pep[i].id]=num[fai];
		i++;
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);

	return 0;
}
```


---

## 作者：卡卡卡卡卡卡 (赞：1)

## 分析：

当我们看到数据范围为 $1 \leq N \leq 100,000$，$0 \leq M \leq 200,000$ 时，我们大概可以认定代码的时间复杂度为 $O(M)$ 或者 $O(M\log M)$ 的。

题目询问的是连通块的点个数，我们考虑离线 DSU（并查集）来判断是否连通；

对于连通块的点个数，我们可以用一个 $son$ 数组来维护。

以时间从早到晚排序，保证只加边不删边。

时间复杂度：$O(M\log M)$。

详细内容看代码：

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,Q,fa[3000001],now=1,son[3000001],ans[3000001];
struct node
{
	int u,v,time,id;
}edge[3000001],q[3000001];
bool cmp(node a,node b)
{
	return a.time>b.time;
}//排序
int find(int x)
{
	if(x!=fa[x])return fa[x]=find(fa[x]);
	else return x;
}
void unionn(int a,int b)
{
	int A=find(a),B=find(b);
	if(A>B)swap(A,B);
	if(A!=B)son[B]+=son[A],son[A]=0;//连通块合并，点数相加，以小点为根
	fa[A]=B;
}//DSU
int query(int x)
{
	if(x!=fa[x])return query(fa[x]);
	else return son[x];
}//查询连通块的点数

int main()
{
    cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>edge[i].u>>edge[i].v>>edge[i].time;
	for(int i=1;i<=n;i++)fa[i]=i,son[i]=1;
	sort(edge+1,edge+1+m,cmp);//边排序
	cin>>Q;
	for(int i=1;i<=Q;i++)cin>>q[i].u>>q[i].time,q[i].id=i;
	sort(q+1,q+1+Q,cmp);
	for(int i=1;i<=Q;i++)
	{
        while(q[i].time<edge[now].time)
		{
			unionn(edge[now].u,edge[now].v);//加边操作
			now++;
		}
		ans[q[i].id]=query(q[i].u);//保留答案
	}
	for(int i=1;i<=Q;i++)cout<<ans[i]<<endl;
}
```



---

## 作者：technopolis_2085 (赞：1)

### [ABC040D] 道路の老朽化対策について 题解

分析：

先考虑暴力。

对于每一个询问，做一遍广搜即可。

代码很简单，这里不给出了。

正解：

我们发现询问之间没有关联，所以可以考虑离线处理。

因为每个人走的路的修建时间必须大于 $w_j$，所以我们可以把每一条边按照建造时间从大到小排序，并将询问按 $w_j$ 从大到小排序。

我们维护一个指针变量 $pt$。

对于第 $i$ 个询问，我们将所有建造时间大于 $w_i$ 的边连好，这时我们发现把每一条边按照建造时间从大到小排序可以避免重复加边，可以用 $pt$ 记录连到第几条边，每次秩序判断 $y_{pt}$ 和 $w_i$ 的大小即可。

对于连边这件事，可以用并查集维护，并维护每一个并查集的大小。

计算完答案后按照输入顺序排序回去就可以愉快地输出了。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+10;

struct edge{
	int u,v;
	int t;
};
edge e[maxn];
int fa[maxn];
int sz[maxn];

bool cmp1(edge i,edge j){
	return i.t>j.t;
}

struct query{
	int u;
	int t;
	int id;
	int ans;
};
query q[maxn];

bool cmp2(query i,query j){
	return i.t>j.t;
}

bool cmp3(query i,query j){
	return i.id<j.id;
}

int find(int x){
	if (fa[x]==x) return fa[x];
	fa[x]=find(fa[x]);
	return fa[x]; 
}
int n,m,k;

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		fa[i]=i;
		sz[i]=1;
	}
	
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].t);
	}
	
	sort(e+1,e+1+m,cmp1);
	
	scanf("%d",&k); 
	for (int i=1;i<=k;i++){
		scanf("%d%d",&q[i].u,&q[i].t);
		q[i].id=i;
	}
	
	sort(q+1,q+1+k,cmp2);
	
	int pt=1;
	for (int i=1;i<=k;i++){
		while (pt<=m&&e[pt].t>q[i].t){
			int u=e[pt].u,v=e[pt].v;
			int ta=find(u),tb=find(v);
			
			if (ta!=tb){
				fa[tb]=ta;
				sz[ta]+=sz[tb]; 
			}
			
			pt++;
		}
		
		int u=q[i].u;
		u=find(u);
		q[i].ans=sz[u];
	}
	
	sort(q+1,q+1+k,cmp3);
	
	for (int i=1;i<=k;i++) printf("%d\n",q[i].ans);
	return 0;
} 
```


---

## 作者：_AyachiNene (赞：1)

# 思路：
第一眼看这道题以为是可持久化并查集，但是观察一下发现根本没必要，没有要求强制在线，所以可以考虑离线。题目要求的是只通过时间戳大于询问的时间戳的边能到达的点数，这个东西明显是有单调性的，即时间戳大的询问能走的边，在时间戳更小的询问里肯定也能走，所以直接把询问离线下来，把询问和边的时间戳都按从大到小的顺序排序，再用并查集维护一下联通块大小，直接用双指针跑就行了。
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
struct node
{
	int x,y,t;
}e[114514<<1];      //边 
bool cmp1(node x,node y)
{
	return x.t>y.t;
}
struct query
{
	int x,t,id;
}que[114514<<1];      //询问 
bool cmp2(query x,query y)
{
	return x.t>y.t;
}
int n,m,q;
int f[114514<<1],siz[114514<<1];
int ans[114514<<1];
int find(int x)
{
	if(f[x]==x)
		return x;
	return f[x]=find(f[x]);
}                //并查集板子 
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		f[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++)
		e[i].x=read(),e[i].y=read(),e[i].t=read();
	q=read();
	for(int i=1;i<=q;i++)
		que[i].x=read(),que[i].t=read(),que[i].id=i;  //把询问离线下来 
	sort(e+1,e+m+1,cmp1);
	sort(que+1,que+q+1,cmp2);        //按时间戳从大到小排序 
	int cur=1;
	for(int i=1;i<=q;i++)
	{
		while(cur<=m&&e[cur].t>que[i].t)     //双指针 
		{
			int fx=find(e[cur].x);
			int fy=find(e[cur].y);
			if(fx!=fy)                 //合并 
			{
				f[fx]=fy;
				siz[fy]+=siz[fx];
			}
			++cur;
		}
		ans[que[i].id]=siz[find(que[i].x)];
	}
	for(int i=1;i<=q;i++)
		write(ans[i]),puts("");
}
```


---

## 作者：zhuweiqi (赞：1)

首先，大致地浏览一下题目的主要内容，$n$ 个点，$m$ 条边，$q$ 次询问，求连通块大小的问题，快速定位到并查集。

再考虑如何不重复合并，最好的方法是将询问按照其对时间年限的要求排序离线处理，即将第二个参数从大到小排序，因为这样一来，前面的询问可以用的道路肯定也能被后面的询问用，避免了重复合并浪费时间。

最后，考虑将道路按照建造年份从大到小排序，用双指针维护每次询问所能使用的新道路，合并道路两端城市的操作用计数并查集解决，那么本题的解题思路到此就结束啦（感兴趣的读者可以去做做 [P1197](https://www.luogu.com.cn/problem/P1197)，也是一道不错的并查集好题）。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2,M=2e5+2,Q=1e5+2;
int n,m,q;
struct edge{
	int x,y,z;
}s[M];
bool cmp(edge x,edge y){return x.z>y.z;}
struct node{
	int x,y,idx,ans;
}c[Q];
bool cmp1(node x,node y){return x.y>y.y;}
int f[N],cnt[N];
int find(int x){
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
void hb(int x,int y){
	if(find(x)==find(y)) return;
	cnt[f[y]]+=cnt[f[x]];
	f[f[x]]=f[y];
	return;
}
bool cmp2(node x,node y){return x.idx<y.idx;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&s[i].x,&s[i].y,&s[i].z);
	sort(s+1,s+1+m,cmp);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&c[i].x,&c[i].y);
		c[i].idx=i;
	}
	sort(c+1,c+1+q,cmp1);
	for(int i=1;i<=n;i++) f[i]=i,cnt[i]=1;
	int j=1;
	for(int i=1;i<=q;i++){
		while(j<=m && s[j].z>c[i].y){
			hb(s[j].x,s[j].y);
			j++;
		}
		c[i].ans=cnt[find(c[i].x)];
	}
	sort(c+1,c+1+q,cmp2);
	for(int i=1;i<=q;i++) printf("%d\n",c[i].ans);
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

非常 trick 的题，想到离线基本就做完了。

首先会想对于时间去分别维护个什么东西，但是时间太长了，肯定是比较困难的。然后你发现对于一次询问 $(v, w)$，它相当于在 $w$ 之后的道路形成的图上求连通块大小，这是 naive 的。然后你就想到了离线，把道路和询问按照年份排序之后维护并查集就做完了。细节是年份相同时询问在前。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
int n, m, Q;
struct Query { bool opt; int x, y, z, v, o; } q[N];
int ans[N];

namespace UnionSet {
	int f[N], siz[N];
	void init(int n) { for (int i = 1; i <= n; i++) f[i] = i, siz[i] = 1; }
	int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x != y) f[x] = y, siz[y] += siz[x];
	}
} using namespace UnionSet;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m; init(n);
	for (int i = 1; i <= m; i++) cin >> q[i].x >> q[i].y >> q[i].z, q[i].opt = 1;
	cin >> Q;
	for (int i = 1; i <= Q; i++) cin >> q[i + m].v >> q[i + m].z, q[i + m].o = i, q[i + m].opt = 0;
	sort(q + 1, q + m + Q + 1, [](Query x, Query y) { return x.z != y.z ? x.z > y.z : x.opt < y.opt; });
	for (int i = 1; i <= m + Q; i++) {
		if (q[i].opt) merge(q[i].x, q[i].y);
		else ans[q[i].o] = siz[find(q[i].v)];
	}
	for (int i = 1; i <= Q; i++) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

一道很经典的并查集离线题。

## Solution

### Idea

我们发现每一次都对于一个询问单独加边，时间复杂度肯定会爆炸。

于是我们思考：如何才能让加边的次数变少呢？

不难发现，我们的每一条边都有一个修建年份，并且修建在 $x$ 年的一定会被排斥 $y$ 年以前的使用，当且仅当 $y<x$ 时。

如果我们对于询问按照排斥年份从晚到早排序，把边按照修建时间从晚到早排序，则我们先加入的边一定不会被后面的询问排斥，因为显然越靠后的人所能接受的年份越早。

显然有一个要求：对于每一组询问只能添加修建年份更晚的边。如果我们按照排序，每一次更新，我们都只需在原有的基础上添加修建年份在 $w_{i-1}$ 与 $w_i$ 之间的边，就可以做到在不多不少的情况下恰好加 $n$ 次边。

注意因为排了序，所以要记录询问序号，然后最后统一输出。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=100005,M=200005;
int n,m;
struct node{
	int u,v,y;
	friend bool operator <(node _,node __){
		return _.y>__.y;
	}
}a[M];
struct ask{
	int x,y,id;
	friend bool operator <(ask _,ask __){
		return _.y>__.y;
	}
}e[N];
int fa[N],siz[N];
int findd(int now){
	if(fa[now]==now)return now;
	return fa[now]=findd(fa[now]);
}
void vnion(int u,int v){
	u=findd(u),v=findd(v);
	if(u==v)return;
	fa[u]=v;
	siz[v]+=siz[u];
}
int q,ans[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a[i].u,&a[i].v,&a[i].y);
	}
	sort(a+1,a+m+1);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&e[i].x,&e[i].y);
		e[i].id=i;
	}
	sort(e+1,e+q+1);
	for(int i=1,j=1;i<=q;i++){
		while(j<=m&&a[j].y>e[i].y){
			vnion(a[j].u,a[j].v);
			j++;
		}
		ans[e[i].id]=siz[findd(e[i].x)];
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

随机绿题的时候发现了这道水题。  
[传送门](https://www.luogu.com.cn/problem/AT_abc040_d)
## 解法
我们先考虑常规做法。   
对于每个询问，我们需要重新加边，这很麻烦。但是如果可以继承上一次的加边就很简单了。   
所以我们可以将加边和询问按照年份从大到小排序离线处理。   
那么如何计算答案呢？我们可以使用带权并查集维护它所在子树的大小。   
于是本题就做完了，复杂度 $O(q\log q)$，其实也就是排序的复杂度。    
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=2e5;
int n,m,fa[N+10],ans[N+10],q,siz[N+10];
struct node{
	int x;
	int y;
	int w;
}a[N+10];
struct que{
	int x;
	int w;
	int p;
}b[N+10];
il int find(int x){
	ret x==fa[x]?x:fa[x]=find(fa[x]);
}
il void join(int x,int y){
	int f1=find(x),f2=find(y);
	if(f1!=f2){
		fa[f1]=f2;
		siz[f2]+=siz[f1];
	}
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<int>();
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
	}
	m=read<int>();
	for(int i=1;i<=m;i++){
		a[i].x=read<int>();
		a[i].y=read<int>();
		a[i].w=read<int>();
	}
	sort(a+1,a+1+m,[](cst node& x,cst node& y){ret x.w>y.w;});
	q=read<int>();
	for(int i=1;i<=q;i++){
		b[i].x=read<int>();
		b[i].w=read<int>();
		b[i].p=i;
	}
	sort(b+1,b+1+q,[](cst que& x,cst que& y){ret x.w>y.w;});
	int p=1;
	for(int i=1;i<=q;i++){
		while(a[p].w>b[i].w&&p<=m){
			join(a[p].x,a[p].y);
			p++;
		}
		ans[b[i].p]=siz[find(b[i].x)];
	}
	for(int i=1;i<=q;i++){
		write(ans[i]);
		edl;
	}
	ret 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc040_d)

#### 思路

首先假设只有一个人，如何快速求出他能到那些城市？

很容易想到先把边按建造年份从大到小排序，把所有对于这个人来说可以走的路连起来，看他在的城市属于哪一个连通块，求出这个连通块的个数即可，**并查集**可以很好的解决这个问题。

我们现在已经知道如何求一个人的了，那如果是 $q$ 个人呢？我们可以把每个人按 $w_i$ 从大到小排序，按顺序对于每一个人编号赋为 $1∼n$，一条边如果在 $w_i$ 年后建造，那么这条边不仅编号为 $i$ 的人可以通过，编号为 $i + 1$ 到 $q$ 的人也一定可以通过，那么每条边最多就只用被加一遍了，就跟只有一个人一样了。

**code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int f[100010],n,m,q,o,ans[200010],z[200010];
int find(int x)
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
struct w
{
	int x,y,z;
}b[200010]; 
struct w1
{
	int x,y,id;
}c[200010]; 
bool cmp(w a,w b){return a.z > b.z;}
bool cmp1(w1 a,w1 b){return a.y > b.y;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) f[i] = i,z[i] = 1;
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].z);
	sort(b + 1,b + 1 + m,cmp);//对于边排序 
	scanf("%d",&q);
	for(int i = 1;i <= q;i++) scanf("%d%d",&c[i].x,&c[i].y),c[i].id = i;
	sort(c + 1,c + 1 + q,cmp1);//对于人排序 
	o = 1;
	for(int i = 1;i <= q;i++) 
	{
		for(;o <= m && b[o].z > c[i].y;o++) //把所有满足条件的加入进来 
			if(find(b[o].x) != find(b[o].y)) z[find(b[o].y)] += z[find(b[o].x)],z[find(b[o].x)] = 0,f[find(b[o].x)] = find(b[o].y);
		ans[c[i].id] = z[find(c[i].x)];
	} 
	for(int i = 1;i <= q;i++) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：maple_trees_112 (赞：0)

这道题不多说，熟悉图论的一眼就能看出是并查集。
不懂可以先看 [这](https://blog.csdn.net/qq_42388742/article/details/112464016)

这道题是个无向图联通，所以要用并查集，~~而且还是板子~~。

## 思路

由于这道题保证不删边，那么我们只需要用一个数组维护，再排序输出即可。

这道题其实算比较好的板子题，应因为他前面访问的路能走那么后面一定也可以，这样大大减少了时间复杂度，不会超时。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e7 + 10; 
long long n,m,mary,fa[maxn],tmp=1,sum[maxn],ans[maxn];
struct wdge
{
	int u,v,slute,id;
}w[maxn],q[maxn];
bool cmp(wdge a,wdge b)
{
	return a.slute > b.slute;
}
int find(int x)
{
	if(x != fa[x])
	{
		return fa[x] = find(fa[x]);
	}
	else 
	{
		return x;
	}
}
void unionn(int a,int b)
{
	int x = find(a);
	int y = find(b);
	if(x > y)
	{
		swap(x,y);
	}
	if(x != y)
	{
		sum[y] += sum[x];
		sum[x] = 0;
	}
	fa[x] = y;
}
int query(int x)
{
	if(x!=fa[x])return query(fa[x]);
	else return sum[x];
}

int main()
{
    std::cin>>n>>m;
	for(int i = 1;i <= m;i++)
	{
		std::cin>>w[i].u>>w[i].v>>w[i].slute;
	}
	for(int i = 1;i <= n;i++)
	{
		fa[i]=i;
		sum[i] = 1;
	}
	sort(w + 1,w + 1 + m,cmp);
	std::cin>>mary;
	for(int i = 1;i <= mary;i++)
	{
		std::cin>>q[i].u>>q[i].slute;
		q[i].id=i;
	}
	sort(q + 1,q + 1 + mary,cmp);
	for(int i = 1;i <= mary;i++)
	{
        while(q[i].slute < w[tmp].slute)
		{
			unionn(w[tmp].u,w[tmp].v);
			tmp++;
		}
		ans[q[i].id] = query(q[i].u);
	}
	for(int i = 1;i <= mary;i++)
	{
		std::cout<<ans[i]<<endl;
	}
	return 0;
}
```


---

