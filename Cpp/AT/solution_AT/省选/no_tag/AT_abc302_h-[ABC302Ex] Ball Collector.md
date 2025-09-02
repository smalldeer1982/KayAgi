# [ABC302Ex] Ball Collector

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_h

$ N $ 頂点の木があります。$ i(1\ \le\ i\ \le\ N-1) $ 本目の辺は、頂点 $ U_i $ と $ V_i $ を結ぶ無向辺です。頂点 $ i(1\ \le\ i\ \le\ N) $ には、$ A_i $ が書かれたボールと $ B_i $ が書かれたボールが $ 1 $ 個ずつあります。

$ v\ =\ 2,3,\dots,N $ に対して、以下の問題を解いてください。(各問題は独立です。)

- 頂点 $ 1 $ から頂点 $ v $ まで最短経路で移動します。このとき、通った各頂点(頂点 $ 1,v $ も含む)において、ボールを $ 1 $ 個ずつ選んで取ります。最終的に持っているボールに書かれている整数の種類数の最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i,B_i\ \le\ N $
- 与えられるグラフは木である。
- 入力は全て整数である。
 
### Sample Explanation 1

例えば、$ v=4 $ のときは通る頂点は $ 1,2,3,4 $ であり、それぞれ $ A_1,B_2,B_3,B_4(=1,3,1,2) $ が書かれているボールを選ぶと種類数が $ 3 $ となり、これが最大となります。

## 样例 #1

### 输入

```
4
1 2
2 3
3 1
1 2
1 2
2 3
3 4```

### 输出

```
2 3 3```

## 样例 #2

### 输入

```
10
2 5
2 2
8 8
4 3
6 10
8 1
9 10
1 7
9 3
5 10
9 3
1 9
3 6
4 1
3 8
10 9
5 4
7 2
9 7```

### 输出

```
4 3 2 3 4 3 4 2 3```

# 题解

## 作者：myyyIisq2R (赞：6)

容易想到的是把相互制约的 $A_i$ 与 $B_i$ 连边，需要考虑的是怎么把图上的信息转化成答案。
其实手模样例就可以发现，如果连出了一个树，那么答案便是 $siz - 1$，否则答案是 $siz$。

证明：
 
- **树的答案是 $cnt = siz - 1$：**
  树有根，树的根和它若干直系子节点会连边。若取了根它的直系子节点便不能取，必然不优，不妨舍去根。

  剩下的所有点都是可取的，因为其余节点都有一条连向父亲。为什么这样是对的，首先所有根的直系子节点会在和根的限制关系中取到，那么这些子节点在和它们的子节点的限制中就不需要取了，就可以取到它们的子节点。以此类推到叶子节点，都可取，即答案为 $siz-1$ 恰为边数。
- **图的答案是 $siz$：**
  图，也就是非树的情况下，至少会有一个环。考虑基环树的情况，处理基环树可以很自然想到断环成链，就可以转化成刚才树的情况，即 $siz-1$，又因为我们断掉了一条边删掉了根，现在加上这条边，理同上显然可以取根，那么所有的点都可取了。基环如此，多环亦然。

接下来考虑实现。
注意到 $n \le 2 \times 10^5$，时间复杂度应该是 $O(nlogn)$，那么就需要在 $O(logn)$ 内完成断边，加边，统计边数量操作，可以用到并查集。要断边，就要用到可撤销并查集的科技，其实就是分离的时候重新将父亲给到自己，并且给原来的父亲减掉自己的信息。
合并就启发式合并即可。注意不要路径压缩！因为要断边就需要保留原始父节点信息。

还有一些比较妙的细节，合并时需要判断是树还是图。我们分类讨论一下：
- 树：答案是 $cnt$，$cnt = siz - 1$ 即 $cnt < siz$.
- 图：答案是 $siz$，$cnt \ge siz$.

**综上，答案是 $\min(siz,cnt)$**

注意拆开必然需要倒着还原，那么就需要一个栈来存加边顺序，还有加边类型（加的是图内边还是联通边），按类型还原，所有的撤销操作都和加边操作倒过来（顺序和增减）。
```cpp

inline int find(int u)
{
	if(f[u] == u) return u;
	return find(f[u]);
}
struct NODE
{
	int op,x,y;
}st[N];
int nowans{};
void link(int x,int y)
{
	x = find(x),y = find(y);
	if(x == y)
	{
		nowans -= min(cnt[x],siz[x]);
		cnt[x]++;
		nowans += min(cnt[x],siz[x]);
		st[++tot] = {0,x,x};	
	}
	else
	{
		nowans -= min(cnt[x],siz[x]);
		nowans -= min(cnt[y],siz[y]);
		if(siz[x]<siz[y]) x^=y^=x^=y;
		f[y] = x;
		siz[x] += siz[y];cnt[x] += cnt[y]+ 1;//connect
		nowans += min(cnt[x],siz[x]);
		st[++tot] = {1,x,y};
	}
}
void reset()
{
	int op = st[tot].op,x = st[tot].x,y = st[tot--].y;
	if(op == 0)
	{
		nowans -= min(cnt[x],siz[x]);
		cnt[x]--;
		nowans += min(cnt[x],siz[x]);
	}
	else
	{
		nowans -= min(cnt[x],siz[x]);
		f[y] = y;
		siz[x] -= siz[y],cnt[x] -= cnt[y] + 1;
		nowans += min(cnt[x],siz[x]);
		nowans += min(cnt[y],siz[y]); 
	}
	
}
int ans[N];
void dfs1(int u,int fa)
{
	link(a[u],b[u]);
	ans[u] = nowans;
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs1(v,u);
	}
	reset();
}
signed main()
{
	#ifdef LOCAL
	freopen("in.in","r",stdin);
	#endif
	int n = read();
	for(int i{1};i<=n;i++) 
	{
		a[i] = read(),b[i] =read();
		f[a[i]] = a[i],f[b[i]] = b[i];
		siz[a[i]] = 1,siz[b[i]] = 1;
		cnt[a[i]] = 0,cnt[b[i]] = 0;
	}
	for(int i{1};i<n;i++)
	{
		int u = read(), v = read();
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	for(int i{2};i<=n;i++) write(ans[i]),putchar(' ');
	return 0;
}
```

---

## 作者：Purslane (赞：5)

# Solution

先考虑给定了 $a$ 和 $b$ 怎么做。

我们把 $a_i$ 和 $b_i$ 连边，会得到一个图。

考虑这个图的每个连通块。如果不管自环的话，这个连通块至少是一棵树。

假设边数正好等于点数减一，那么这是一棵树。我们以任意一个点作为根，让每条边都选它的儿子，就可以做到理论最大值边数。否则必定有环（重边和自环也是环），我们取这个环中某条边的某个端点为根，把这条边去掉，再做同样的操作，然后让这条边选根就可以做到理论最大值点数。因此每个连通块最大值就是 $\min\{\text{点数},\text{边数}\}$。

然后在 DFS 的过程中维护可撤销并查集即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,res[MAXN],ans,a[MAXN],b[MAXN],fa[MAXN],sze[MAXN],edge[MAXN];
vector<int> G[MAXN];
int find(int k) {
	if(fa[k]==k) return k;
	return find(fa[k]);	
}
void merge(int u,int v,stack<pair<int,pair<int,pair<int,int>>>> &st,int &ans) {
	u=find(u),v=find(v);
	st.push({u,{fa[u],{sze[u],edge[u]}}});
	st.push({v,{fa[v],{sze[v],edge[v]}}});
	if(u==v) {
		edge[u]++;
		if(edge[u]==sze[u]) ans++;
		return ;
	}
	if(sze[u]<sze[v]) swap(u,v);
	ans-=min(sze[u],edge[u]),ans-=min(sze[v],edge[v]);
	fa[v]=u,sze[u]+=sze[v],edge[u]+=edge[v]+1;
	ans+=min(sze[u],edge[u]);
	return ;
}
void dfs(int u,int f) {
	stack<pair<int,pair<int,pair<int,int>>>> st; int tmpans=ans;
	merge(a[u],b[u],st,ans);
	res[u]=ans;
	for(auto v:G[u]) if(v!=f) dfs(v,u);
	while(!st.empty()) {
		auto pr=st.top(); st.pop();
		fa[pr.first]=pr.second.first;
		sze[pr.first]=pr.second.second.first;
		edge[pr.first]=pr.second.second.second;	
	}
	ans=tmpans;
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i]>>b[i];
	ffor(i,1,n-1) {int u,v; cin>>u>>v; G[u].push_back(v),G[v].push_back(u);} 
	ffor(i,1,n) fa[i]=i,sze[i]=1,edge[i]=0;
	dfs(1,0);
	ffor(i,2,n) cout<<res[i]<<' ';
	return 0;
}
```

---

## 作者：鱼跃于渊 (赞：3)

感觉这题的套路见过很多次了。  

## 做法  

对于这种二者之间选一个并且不同点之间的选择会互相影响的题目，我们可以套路地将二者连边，转化成一个图上问题。  
首先我们考虑如果只有单次询问怎么做。  
我们设图上第 $i$ 个连通块的点数为 $d_i$，边数为 $b_i$，不难发现，这个连通块内可以对答案产生 $\min(d_i,b_i)$ 的贡献，证明：  
1. 若 $b_i=d_i-1$，发现这就是一棵树，显然我们最多只能选择 $b_i$ 个点，所以产生的贡献为 $b_i$。  
2. 若 $b_i\ge d_i$，发现现在的图由若干个环和链组成，显然环上的点都可以选到，所以链上至少有一个点已经在环里选到了，那么自然链上剩余的点也都可以选到，所以产生的贡献为 $d_i$。  

综上所述，一个连通块产生的贡献为 $\min(d_i,b_i)$。  

考虑如何解决多组询问。  
可以想到对题目中给定的树跑一遍 dfs，进入一个结点就加入一条边，离开一个结点就删除这条边，但问题在于如何动态维护连通块。  
我们可以使用可撤销并查集，顾名思义，这个并查集支持撤销**上一个操作**。  
于是这题就做完了。  

## 代码  

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define epb emplace_back
const int N=2e5+5;
struct node{
	int a,b,id;
}p[N];
int n,sum,ans[N];
int fa[N],siz[N],cnt[N];
vector <int> e[N];
stack <node> st;
void init(int x){
	fa[x]=x;siz[x]=1;cnt[x]=0;
}
int find(int x){
	return fa[x]==x?x:find(fa[x]);
}
int get(int x){
	return min(siz[x],cnt[x]);
}
void merge(int u,int v){
	u=find(u);v=find(v);
	if(u==v){
		sum-=get(u);
		cnt[u]++;
		sum+=get(u);
		st.push({u,u,0});
	}
	else{
		sum-=get(u)+get(v);
		if(siz[u]<siz[v]) swap(u,v);
		fa[v]=u;
		siz[u]+=siz[v];cnt[u]+=cnt[v]+1;
		sum+=get(u);
		st.push({u,v,1});
	}
}
void split(){
	int u=st.top().a,v=st.top().b,op=st.top().id;
	st.pop();
	if(!op){
		sum-=get(u);
		cnt[u]--;
		sum+=get(u);
	}
	else{
		sum-=get(u);
		fa[v]=v;
		siz[u]-=siz[v];cnt[u]-=cnt[v]+1;
		sum+=get(u)+get(v);
	}
}
void dfs(int u,int fa){
	merge(p[u].a,p[u].b);
	ans[u]=sum;
	for(auto v:e[u])
		if(v!=fa) dfs(v,u);
	split();
}
signed main(){
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1,a,b;i<=n;i++){
		cin>>a>>b;
		p[i]={a,b,i};
		init(a);init(b);
	}
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].epb(v);e[v].epb(u);
	}
	dfs(1,0);
	per(i,2,n) cout<<ans[i]<<" \n"[i==n];
	return 0;
}

```

---

## 作者：Southern_Dynasty (赞：3)

首先我们考虑 $v$ 固定怎么做。实际上就是 [ARC111B](https://www.luogu.com.cn/problem/AT_arc111_b)。

考虑建图，对每个 $(a_i,b_i)$ 建一条无向边，那么问题就变成了：对于每条边都要选择它以及其连接的一个点，最大化选出的点数。

很明显可以对每个连通块分开考虑。

记当前连通块的点数为 $V$，边数为 $E$。那么有结论：该连通块对答案的贡献为 $\min(V,E)$。

考虑证明。由于是连通块，所以 $E$ 最小为 $V-1$（树）。接下来我们根据 $V$ 和 $E$ 的关系分类讨论：

- $E=V-1$。此时连通块为一棵树。随便钦定一个点为根，然后每条边选儿子，这样就可以选掉除了根节点外的所有点，答案为 $V-1=E=\min(V,E)$。很明显选出来的点数不可能比选的边数还多，所以这是对的。

- $E\ge V$。这个时候必然能给每个点都选出一条边，答案为 $V=\min(V,E)$。

这样我们就证完了。

具体实现的时候使用并查集，维护连通块内点数、边数，合并时分类讨论即可。

[Code](https://atcoder.jp/contests/arc111/submissions/41653755)


接下来考虑树上的每个点，我们在 DFS 的时候把当前点 $u$ 加入连通块中并计算答案，搜索完 $u$ 时再消除 $u$ 对答案的影响即可。

怎么消除影响？使用可撤销并查集，将每次合并压入栈中，撤销时取出栈中信息并复原即可。

注意此时并查集**不能使用路径压缩**，因为这样会破坏树的结构。使用启发式合并即可。时间复杂度 $O(n\log n)$，可以通过此题。

[Code](https://atcoder.jp/contests/abc302/submissions/41654526)


---

## 作者：AzureHair (赞：1)

因为学会了这道题感觉整个人豁然开朗，故来发一篇题解纪念一下。

简明题意：求根节点到其余每个节点路径上每个点两数中选一个的最大数字种类数。

由于路径是唯一的，所以该问题可以转化为给定一个数列，每个位置两个数中选一个，求最大数字种类数。

二选一这种二元关系触动了人们的 DNA，所以能够想到可以试图建边解决，发现对于二选一的两数连边后，意义就是一条边连接的两点只能选一个，那么最终就会形成一个奇怪的森林，如果对于一个连通块内有 $n$ 个点 $n-1$ 条边，那么对于这个连通块就可以选择 $n-1$ 种数字，具体就是每条边都选择儿子节点即可。如果一个连通块内有 $n$ 个点 $n$ 条边或者更多，那么对于一个基环树必定能够全选，证明类似上面树的，在此不再赘述，所以只需维护到每个节点的并查集即可，注意并查集需要同时维护边，所以一个可撤销并查集碾过去即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200010],b[200010],head[200010],fa[200010],num[200010],siz[200010],ans=0,cnt=0,top=0,ans1[200010];
bool flag[200010];
pair<int,int> st[200010];
struct node
{
	int next,to;
}e[400010];
void add(int from,int to)
{
	e[++cnt].next=head[from];
	e[cnt].to=to;
	head[from]=cnt;
}
int find(int x)
{
	if(x==fa[x])return x;
	else return find(fa[x]);
}
void addd(int x,int y)
{
	int xx=find(x),yy=find(y);top++;
	if(xx==yy)
	{
		if(num[xx]==siz[xx]-1)
		{
			ans++;flag[top]=1;//flag是记录是否有ans变化
		}
		num[xx]++;
		st[top]=make_pair(-1,xx);//记录操作用于撤销
	}
	else
	{
		if(siz[xx]>siz[yy])
		{
			swap(xx,yy);
		}
		if(num[xx]==siz[xx]-1||num[yy]==siz[yy]-1)
		{
			ans++;flag[top]=1;
		}
		fa[xx]=yy;
		siz[yy]+=siz[xx];
		num[yy]+=num[xx]+1;
		st[top]=make_pair(xx,yy);
	}
}
void cx(int x)
{
	if(st[x].first==-1)
	{
		num[st[x].second]--;
	}
	else 
	{
		fa[st[x].first]=st[x].first;//关键的撤销操作，将操作反过来做即可
		siz[st[x].second]-=siz[st[x].first];
		num[st[x].second]-=num[st[x].first]+1;
	}
	if(flag[x])ans--;
	flag[x]=0;st[x]=make_pair(0,0);
}
void dfs(int x,int fa)
{
	int now=top;
	addd(a[x],b[x]);
	ans1[x]=ans;
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==fa)continue;
		dfs(to,x);
	}
	while(top>now)cx(top--);
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&b[i]);
	}
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;siz[i]=1;
	}
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	for(int i=2;i<=n;i++)
	{
		cout<<ans1[i]<<" ";
	}
	return 0;
}
```


---

## 作者：CJerryR (赞：1)

### ABC302Ex

**翻译**

我们有一棵 $N$ 个节点的树，先输入 $N$ 行每行两个数表示 $i$ 号节点上面的两颗球 $a_i$ 和 $b_i$，再有 $N-1$ 行输入，每行两个数表示第 $j$ 条边连接节点 $u_j$ 和 $v_j$。在 $k$ 节点到根节点的最短路上的每个节点上的两个球，可以任选其一，请问对于每个节点能够选择的最多不同的气球上的数字有多少？

**解题思路**

在树上 dfs 经过的节点上的两个球，我们连一条边放在并查集中，当并查集中某个集合的连接次数大于等于拥有的节点个数时这个树上的所有节点上的数都可以取到，如果连接次数小于拥有的节点个数，那么这棵树上能取到的节点个数是 $siz_i-1$。

需要注意的是在树上 dfs 的同时使用并查集，需要撤销连边，因此并查集不能使用路径压缩，但是在本题的数据范围下一定要使用按秩合并，否则就会像我一样被卡飞。

代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int MAXN = 2e5 + 6;
inline int read() {//快读
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch >'9') {
        if (ch == '-')w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch - '0');
        ch = getchar();
    }
    return x * w;
}
inline void write(int& x)
{
    if (x == 0) { putchar('0'); return; }
    if (x < 0) { putchar('-'); x = -x; }
    if (x < 10) { putchar(x + '0'); return; }
    short num = 0; char c[30];
    while (x) c[++num] = (x % 10) + 48, x /= 10;
    while (num) putchar(c[num--]);
}
bool flag[MAXN];//是否一定能取到
int a[MAXN], b[MAXN];//两个球
vector<int> e[MAXN];//存图
int fa[MAXN], siz[MAXN];//并查集（按秩合并）
int n, num;//节点总数 num
int ans[MAXN];//每个节点答案
int findfa(int x) {//不路径压缩
    return x == fa[x] ? x : findfa(fa[x]);
}
void dfs(int now, int faa) {
    ans[now] = num;
    for (auto nxt : e[now]) {
        if (nxt == faa)continue;
        int fau = findfa(a[nxt]), fav = findfa(b[nxt]);
        if (siz[fau] < siz[fav])swap(fau, fav);
        if (fau == fav) {
            if (!flag[fau]) {
                num++;
                flag[fau] = 1;
                dfs(nxt, now);
                flag[fau] = 0;
                num--;
            }
            else
                dfs(nxt, now);
        }
        else {
            int nsiz = siz[fau];
            int flu = flag[fau], flv = flag[fav];
            fa[fav] = fau;
            siz[fau] += siz[fav];
            flag[fau] = flu | flv;
            if (!flu || !flv)num++;

            dfs(nxt, now);

            fa[fav] = fav;
            siz[fau] = nsiz;
            flag[fav] = flv;
            flag[fau] = flu;
            if (!flu || !flv)num--;
        }
    }
}
signed main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read(); b[i] = read();
        fa[i] = i; siz[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        int u = read(), v = read();
        e[u].pb(v);
        e[v].pb(u);
    }
    //初始化根节点
    num = 1;
    int nu = a[1], nv = b[1];
    if (nu == nv) flag[nu] = 1;
    else fa[nv] = nu, siz[nu] += siz[nv];

    dfs(1, 0);

    for (int i = 2; i <= n; i++) {
        write(ans[i]);
        putchar(' ');
    }
    return (1 ^ 0 ^ 1);
}
```

---

## 作者：云浅知处 (赞：1)

简单题。

考虑一组询问咋做，把每个 $(A_i,B_i)$ 看成一条边建图，显然答案是点数减去是树的连通块个数。

如何维护形态为树的连通块个数？可以用并查集维护，对每个连通块额外维护连通块内边数即可。

树上咋做？dfs 一遍，用可撤销并查集维护即可。$O(N\log N)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}

const int N=2e5+5;
pair<int,int>stk[N];
int top=0,num[N];
bool tag[N];
#define fi first
#define se second
#define mk make_pair

int fa[N],sz[N],ans=0;
int find(int x){return x==fa[x]?x:find(fa[x]);}
void adde(int x,int y){
	x=find(x),y=find(y),top++;
	if(x==y){
		if(num[x]==sz[x]-1)ans++,tag[top]=1;
		num[x]++,stk[top]=mk(-1,x);
	}
	else{
		if(sz[x]>sz[y])swap(x,y);
		if(num[x]==sz[x]-1||num[y]==sz[y]-1)ans++,tag[top]=1;
		sz[y]+=sz[x],fa[x]=y,stk[top]=mk(x,y);
		num[y]+=num[x]+1;
	}
}
void undo(int id){
	if(stk[id].fi==-1)num[stk[id].se]--;
	else{int x=stk[id].fi,y=stk[id].se;fa[x]=x,sz[y]-=sz[x],num[y]-=num[x]+1;}
	if(tag[id])ans--;
	tag[id]=0,stk[id]=mk(0,0);
}

int Ans[N],a[N],b[N],n;
vector<int>G[N];
void dfs(int u,int fa){
	int cur=top;
	adde(a[u],b[u]);
	Ans[u]=ans;
	for(int v:G[u])if(v!=fa)dfs(v,u);
	while(top>cur)undo(top--);
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif

	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=2;i<=n;i++){int u=read(),v=read();G[u].emplace_back(v),G[v].emplace_back(u);}
	for(int i=1;i<=n;i++)sz[i]=1,fa[i]=i;
	dfs(1,0);
	for(int i=2;i<=n;i++)cout<<Ans[i]<<' ';

	return 0;
}
```

---

## 作者：Corzica (赞：0)

考虑诸如此类的二元组    $(a,b),(b,c),(c,d)...$   在第一个二元组确定选 $b$ 之后，后几个二元组的选择也唯一确定了。
这启发我们将二元组的两元素连边，当一条边上的元素被其他二元组选择时，这条边只能选择另一个元素，从而类似地向其他边扩展。

我们可以作出这种图，观察其不同形态下的答案（下面仅考虑图为连通图的子问题）。

#### Case 1 树
显然，此种情况下的答案上界为边数，我们令每一条边都选择深度较为深的元素，便可构造出答案。
#### Case 2 非树
这种情况下，答案上界为点数。因为图非树，故定有一环，将图简化为边数与点数相同的情况，将此时环上任意一条边断开，令此断开边选择的元素为根，随后执行 Part1 的操作，便可构造出答案为点数的情况。


------------
我们选择可删除的并查集来维护上面的过程，代码比较丑，就不放了。

---

## 作者：JWRuixi (赞：0)

~~/se /se /se~~

### 题意

给定一棵 $n$ 个点的树，每个点有两个球 $(a_i,b_i)$。对于 $v=2,\dots,n$，求在 $1$ 到 $v$ 的路径上每个点取一个球，最多能取得多少种不同的球。

$n \le 2 \times 10^5,1 \le (a_i,b_i) \le n$。

### 分析

先考虑对于一条路径怎么做，把路径抽出来，抽象成一个数组。如果对于 $1 \le i \le m$，$a_i$ 和 $b_i$ 连边，一条边只能取一段，那么一个连通块的答案显然是 $\min(E,V)$。

考虑这怎么放到树上，加边操作很好做，上个并查集解决问题；关键在于删除，显然树上的点先进先出，那么可以套一个可撤销并查集（**注意不带路径压缩**）。哇，你做完了（~~当然你还要码一码~~）！

复杂度 $\mathcal O(n\log n)$。

### Code

提交记录：<https://atcoder.jp/contests/abc302/submissions/43494342>。

---

## 作者：DE_aemmprty (赞：0)

## 1 题目大意

### 1.1 题面大意

给定一棵树，对于每一个 $x(2 \leq x \leq n)$，当第 $i$ 个顶点的权值可以在 $a_i, b_i$ 中选择一个时，求出从 $1$ 到 $x$ 的**最短路径**上不同权值的个数。

具体可以看 LG 翻译，我觉得很到位。

### 1.2 数据范围

对于 $100\%$ 的数据：

- $2 \leq n \leq 2 \times 10^5$
- $1 \leq a_i, b_i \leq n$

## 2 解法分析

### 2.1 链的情况

原题看上去比较复杂，我们先考虑链的情况。

发现 $a_i$ 和 $b_i$ 并不大，于是就有一个比较朴素的想法。我们可以从 $1$ 开始，搜索这条链。当搜到顶点 $i$ 时，将 $a_i$ 和 $b_i$ 连接起来。这可以用并查集来维护。

然后，对于每个连通块，设这个连通块顶点个数为 $x$, 边的数量为 $y$，则有三种情况。

1. $x < y$，此时对答案的贡献显然是 $x$。

2. 连通块构成一棵树。此时，这个连通块对此点答案的贡献为 $x - 1$。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/igqpyrtf.png)

3. 连通块构成一个基环树。此时，这个连通块对此点答案的贡献为 $x$。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6f4l5bba.png)

于是，只需维护一下答案，即可完成这种情况。

### 2.2 普遍情况

我们再来考虑一棵树。我们发现，这个并查集竟然需要进行撤销操作。本来以为要用平衡树了，但是我们发现，这个撤销，只是针对当前的最后一次合并的撤销。所以，我们只需做一个简单的还原即可。这被叫做**可撤销并查集**。但是注意，显而易见，可撤销并查集是**不能做路径压缩的**。

所以发现，其实主要的思维难度都在一条链的情况上。

**注意：并查集需要加按秩合并的优化，不然会 TLE 的很惨。**

## AC Code

```cpp
# include <bits/stdc++.h>
using namespace std;

# define int long long
# define f(i,a,b) for(int i = a; i <= b; i ++)
# define g(i,b,a) for(int i = b; i >= a; i --)
# define CI const int

CI maxn = 2e5 + 7;

int n;
int a[maxn], b[maxn];
int u, v;
vector <int> to[maxn];
int fa[maxn], sz[maxn], p[maxn], r[maxn];

void init(){
    f (i, 1, n){
        fa[i] = i;
        sz[i] = 1;
        p[i] = 0;
        r[i] = 1;
    }
}

int find(int x){ return fa[x] == x ? x : (find(fa[x]));}

int ans[maxn];

void dfs(int u, int ff){
    int x = find(a[u]), y = find(b[u]);
    if (r[x] <= r[y])
        swap(x, y);
    ans[u] = ans[ff];
    ans[u] -= min(sz[x], p[x]);
    int tmp = r[x];
    if (x != y){
        ans[u] -= min(sz[y], p[y]);
        fa[y] = x;
        sz[x] += sz[y];
        p[x] += p[y];
        r[x] += (r[x] == r[y]);
    }
    p[x] ++;
    ans[u] += min(sz[x], p[x]);
    for (int v : to[u]) if (v != ff) dfs(v, u);
    p[x] --;
    if (x != y){
        fa[y] = y;
        sz[x] -= sz[y];
        p[x] -= p[y];
        r[x] = tmp;
    }
}

signed main(){
    cin >> n;
    f (i, 1, n)
        cin >> a[i] >> b[i];
    f (i, 1, n - 1){
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    init();
    dfs(1, 0);
    f (i, 2, n)
        printf("%lld ", ans[i]);
    system("pause");
    return 0;
}
```

---

## 作者：Register_int (赞：0)

这个二分图匹配今年见三次了 ![](//图.tk/j)![](//图.tk/j)![](//图.tk/j) 出烂了 ![](//图.tk/j)![](//图.tk/j)![](//图.tk/j)

直接将选不同数做成二度点最大二分图匹配，做法就是左点改成边，答案为新图中每个连通块内的 $\min(E,V)$ 之和。搞个并查集维护即可。

题目要求求出 $2\sim n$ 的所有答案，直接开个可撤销并查集上树遍历，时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct edge {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int p[MAXN], rk[MAXN], s[MAXN], c[MAXN];

struct node {
	int x, y, ts, tc, w, t;
} q[MAXN]; int cnt, res;

int find(int k) {
	return k == p[k] ? k : find(p[k]);
}

inline 
void merge(int x, int y) {
	if (rk[x = find(x)] > rk[y = find(y)]) swap(x, y);
	if (x == y) {
		q[++cnt] = { x, y, s[x], c[x], res, 0 };
		if (c[x] < s[x]) res++, c[x] = s[x] + 1;
		return ;
	}
	q[++cnt] = { x, y, s[y], c[y], res, rk[x] == rk[y] };
	res -= min(s[x], c[x]) + min(s[y], c[y]);
	p[x] = y, rk[x] == rk[y] && rk[y]++, s[y] += s[x], c[y] += c[x] + 1;
	res += min(s[y], c[y]);
}

inline 
void undo() {
	int x = q[cnt].x, y = q[cnt].y, t = q[cnt].t; res = q[cnt].w;
	p[x] = x, s[y] = q[cnt].ts, c[y] = q[cnt].tc, cnt--;
}

int a[MAXN], b[MAXN], ans[MAXN];

inline 
void dfs(int u, int f) {
	merge(a[u], b[u]), ans[u] = res;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (v == f) continue; dfs(v, u);
	}
	undo();
}

int n;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) p[i] = i, s[i] = 1;
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0);
	for (int i = 2; i <= n; i++) printf("%d ", ans[i]);
}
```

---

## 作者：EuphoricStar (赞：0)

考虑如果只询问一次怎么做。连边 $(a_i, b_i)$，对于每个连通块分别考虑。这是 [ARC111B](https://www.luogu.com.cn/problem/AT_arc111_b)，如果一个连通块是树，肯定有一个点不能被选；否则有环，一定能构造一种方案，使得每个点都被选。

那么现在对于每个点都要求，考虑 dfs 时合并当前的 $(a_u, b_u)$，并且使用可撤销并查集。具体而言，把每次的修改都压进栈里，退出一个点就把这些修改全部复原。**注意不要路径压缩，使用按秩合并。**

[code](https://atcoder.jp/contests/abc302/submissions/41580304)

---

## 作者：XiaoQuQu (赞：0)

[可能更美观的阅读体验](https://blog.tboj.cn/blog/3)。

首先我们分析一下，如果我们已经知道了要走哪些点，我们可以怎么做。

考虑将 $a_i,b_i$ 之间连边，发现题目可以被转化为给定一个图，要求对于每条边将其一个顶点染色，问最多能将多少个点染色。

于是我们对于每个连通块分开来考虑。对于一个连通块，注意到我们不能将每个顶点染色当且仅当这个连通块是树，且此时可以染色的定点数量为连通块大小减一，如下：

1. 如果当前连通块是树，则我们可以固定一个点作为根节点，其余所有非根节点，用它连向父亲的那条边对他进行染色。
2. 如果当前连通块不是树，则我们可以求出他的一个生成树，以一个在环中的节点作为根节点，以 (1) 的方案将这个连通块除了这个根节点以外的点染色，接下来用这个环上的与根节点连接的非树边将这个根节点染色。

所以问题就被我们转换成了，需要维护每个连通块是否为树，并且维护答案。因为要求最短路径，所以我们可以在给定的树上以节点 $1$ 为根进行 DFS，于是从 $1$ 到 $x$ 的最短路径就是链上的点。问题就进一步转换成：每次需要在图中加入一条边 $a_i,b_i$，询问有多少个连通块与其中有多少个是树。发现可撤销并查集可以做到：在合并/撤销的时候维护一下每个连通块里的边的数量，最终根据边的数量与点的数量判断是否为树即可。

最终时间复杂度 $O(n \log n)$，其中 $\log n$ 是可撤销并查集的复杂度。

```cpp
const int MAXN = 4e5 + 5;
int n, fa[MAXN], a[MAXN], b[MAXN], sz[MAXN], ecnt[MAXN], now, ans[MAXN];
stack<pair<int, int>> st;
vector<int> T[MAXN];

int find(int x) {
	if (fa[x] == x) return x;
	else return find(fa[x]);
}

void merge(int u, int v) {
	if (sz[v] > sz[u]) swap(u, v);
	st.push(make_pair(u, v));
	fa[v] = u;
	sz[u] += sz[v];
	ecnt[u] += ecnt[v] + 1;
}

void undo() {
	int u = st.top().first, v = st.top().second;
	st.pop();
	fa[v] = v;
	ecnt[u] -= ecnt[v] + 1;
	sz[u] -= sz[v];
}

void dfs(int x, int fat) {
	int f1 = find(a[x]), f2 = find(b[x]);
	bool merged = false;
	int add = 0;
	if (f1 == f2) {
		ecnt[f1]++;
		if (sz[f1] == ecnt[f1]) now++, add = 1;
	}
	else {
		if (!(ecnt[f1] >= sz[f1] && ecnt[f2] >= sz[f2])) {
			now++;
			add = 1;
		}
		merge(f1, f2);
		merged = true;
	}
	if (x != 1) ans[x] = now;
	for (auto u:T[x]) {
		if (u == fat) continue;
		dfs(u, x);
	}
	if (merged) undo();
	else ecnt[f1]--;
	now -= add;
}

void work() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i];
	}
	for (int u, v, i = 1; i < n; ++i) {
		cin >> u >> v;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	dfs(1, 0);
	for (int i = 2; i <= n; ++i) cout << ans[i] << ' ';
	cout << endl;
}
```



---

