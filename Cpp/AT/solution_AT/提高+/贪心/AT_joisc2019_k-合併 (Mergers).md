# 合併 (Mergers)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2019/tasks/joisc2019_k



# 题解

## 作者：ycy1124 (赞：7)

### 前置知识
[边双缩点](https://blog.csdn.net/weixin_73113801/article/details/130911664)。
### 题意
有 $n$ 个城市，他们之间有 $n-1$ 条道路，这些道路将所有城市连城一棵树。每个城市还属于一个州，当两个城市之间有道路连接或者属于同一个州，我们称他们为联通的。现在要求你将最少的州合并，使得任意去掉一条道路之后，整个图依旧联通。
### 思路
由于是去掉一条边之后图还要依旧联通，不难想到可以先用 Tarjan 对图进行边双缩点，由于相同的州内的城市之间两两连边，所以他们在缩点之后一定是在同一个点内的。然后对于每两个州的合并，其实就是给缩点后的图上的任意两点之间连一条边，使得任意一条边被去掉后整个图依旧联通。显然，连边的最优方案为给两个叶子节点之间连边，答案为 $\frac{s+1}{2}$（$s$ 为缩点之后图上叶子节点的个数）。
### 实现细节
由于给任意两个州之内的城市连边是 $\mathcal{O}( n^2 )$ 的，所以我们将同一个州之内的城市连成一个环，这样可以在不干扰缩点的正确性的情况下减少复杂度。

假如你和我一样使用的是 dfs 求叶子节点，对于第一个 dfs 到的节点需要特判。

当所有城市都在一个州内的时候直接输出 $0$。
### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn (int)1e6+1
using namespace std;
void read(int &x){//快读
	char ch=getchar();
	x=0;
	int f=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-f;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-48;
		ch=getchar();
	}
}
struct qwq{
	int to,w;
};
vector<qwq>a[Maxn];//缩点前的图
int n;
int idx=0;
int dfn[Maxn],low[Maxn];//tarjan
int color[Maxn];//州
int js=0,tot=0;
int las[Maxn],one[Maxn];
bool bj[Maxn],vis[Maxn];
int fa[Maxn];
void dfs(int p,int w){//tarjan求边双
	dfn[p]=low[p]=++idx;
	for(auto it:a[p]){
		if(!dfn[it.to]){
			fa[it.to]=p;
			dfs(it.to,it.w);
			low[p]=min(low[p],low[it.to]);
			if(low[it.to]>dfn[p]){
				bj[it.to]=1;
			}
		}
		else if(it.w!=(w^1)){
			low[p]=min(dfn[it.to],low[p]);
		}
	}
}
void Tarjan(){
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			dfs(i,0);
		}
	}
}
int Color[Maxn];
vector<int>t[Maxn];
void Dfs(int p){//缩点
	vis[p]=1;
	Color[p]=tot;
	for(auto it:a[p]){
		if(Color[it.to]!=Color[p]&&Color[it.to]!=0){
			t[Color[it.to]].push_back({Color[p]});
			t[Color[p]].push_back({Color[it.to]});
		}
		if((bj[p]&&fa[p]==it.to)||(bj[it.to]&&fa[it.to]==p)||vis[it.to]){
			continue;
		}
		Dfs(it.to);
	}
}
int ans=0;
bool Vis[Maxn];
void DFS(int p){//求叶子节点
	Vis[p]=1;
	int vvis=0;
	for(auto it:t[p]){
		if(!Vis[it]){
			++vvis;
			DFS(it);
		}
	}
	if(vvis<1+(p==1)){
		++ans;
	}
}
int main(){
	int k;
	read(n);
	read(k);
	for(int i=1;i<n;i++){
		int u,v;
		read(u);
		read(v);
		++js;
		a[u].push_back({v,js<<1});
		a[v].push_back({u,js<<1|1});
	}
	for(int i=1;i<=n;i++){
		read(color[i]);
	}
	for(int i=1;i<=n;i++){
		if(one[color[i]]==0){
			one[color[i]]=i;
		}
		else{
			++js;
			a[las[color[i]]].push_back({i,js<<1});
			a[i].push_back({las[color[i]],js<<1|1});
		}
		las[color[i]]=i;
	}
	for(int i=1;i<=n;i++){
		if(las[color[i]]!=one[color[i]]){
			++js;
			a[las[color[i]]].push_back({one[color[i]],js<<1});
			a[one[color[i]]].push_back({las[color[i]],js<<1|1});
		}
	}
	Tarjan();
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			++tot;
			Dfs(i);
		}
	}
	if(tot==1){//特判
		printf("0");
		return 0;
	} 
	DFS(1);
	printf("%d",(ans+1)/2);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/180065871)。

---

## 作者：CJZJC (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_joisc2019_k)

## 前言

联考题，被初一的我切了。看到题解区里没有 Tarjan 做法，于是来补一篇 Tarjan 题解。

## 分析

因为相同州的城市不会分裂，所以可以给相同州的成市连边（注意不是两两连边，连成一个环就行），发现把国家分成两个部分就相当于断掉一条道路。那么如果整个国家就是一个边双连通分量，就不可能分裂。

于是我们可以先给图边双连通分量缩点，可以发现缩点后两个点中城市所属的州一定不相同。合并两个州的操作相当于在缩点后给两个点连边。然后就可以用经典的答案统计法了：设缩点后度数为 $1$ 的节点有 $s$ 个，则需要连的边数为 $\lceil \frac{s}{2} \rceil$ 个。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
int n, K, a[N], hd[N], ikun[N], nxt[N * 7], to[N * 7], tot = 1, fa[N], dep[N], dfn[N], low[N], pre[N], idx, c[N], sum, mkp[N], ans;
bool bri[N * 7], vis[N];
inline void add(int u, int v)
{
    tot++;
    nxt[tot] = hd[u];
    to[tot] = v;
    hd[u] = tot;
}
inline void tarjan(int x, int frm) // 跑 Tarjan，找割边
{
    dfn[x] = ++idx;
    low[x] = idx;
    for (int i = hd[x]; i; i = nxt[i])
    {
        int y = to[i];
        if (i == frm || (i ^ 1) == frm) // 注意重边！
        {
            continue;
        }
        if (!dfn[y])
        {
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x])
            {
                bri[i] = 1;
                bri[i ^ 1] = 1;
            }
        }
        else
        {
            low[x] = min(low[x], dfn[y]);
        }
    }
}
inline void dfs(int x) // 找到割边后缩点
{
    c[x] = sum;
    for (int i = hd[x]; i; i = nxt[i])
    {
        if (bri[i] || bri[i ^ 1])
        {
            continue;
        }
        int y = to[i];
        if (!c[y])
        {
            dfs(y);
        }
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> K;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++) // 读入所属州并连边
    {
        cin >> a[i];
        ikun[a[i]] = i;
        if (pre[a[i]])
        {
            add(i, pre[a[i]]);
            add(pre[a[i]], i);
        }
        pre[a[i]] = i;
        fa[i] = i;
        dep[i] = 1;
    }
    for (int i = 1; i <= n; i++) // 要连成环
    {
        if (pre[i])
        {
            add(pre[i], ikun[i]);
            add(ikun[i], pre[i]);
        }
    }
    tarjan(1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (!c[i])
        {
            sum++;
            dfs(i);
        }
    }
    if (sum == 1)
    {
        cout << 0;
        return 0;
    }
    ans = sum;
    for (int i = 1; i <= n; i++)
    {
        for (int j = hd[i]; j; j = nxt[j])
        {
            int k = to[j];
            if (c[i] != c[k])
            {
                if (mkp[c[i]] && (mkp[c[i]] != c[k])) // 判断点的度数是否为 1
                {
                    if (!vis[c[i]])
                    {
                        ans--;
                        vis[c[i]] = 1;
                    }
                }
                if (mkp[c[k]] && (mkp[c[k]] != c[i]))
                {
                    if (!vis[c[k]])
                    {
                        ans--;
                        vis[c[k]] = 1;
                    }
                }
                mkp[c[i]] = c[k];
                mkp[c[k]] = c[i];
            }
        }
    }
    cout << (ans + 1) / 2;
    return 0;
}
```

---

## 作者：Y204335 (赞：3)

# AT\_joisc2019\_k 合併 (Mergers)

## 题目大意

有一颗 $n$ 个点的树，每个点有一个属性。

**定义**当任意断掉一条边后，同一属性的点**只存在于**分出的两颗子树中的一个，则称当前是**可分裂的**。

问通过合并两个属性，**最少**多少次可以让当前的树**不可分裂**。

也就是问通过合并最少多少次属性，使得不管怎么断哪一条边，**同一属性的点在两颗分出的子树中都有**。

## 题目分析

看到删任意一条边，可以尝试往边双连通分量上想。把同一属性的点看作**可以互相到达**，那么不可分裂也就是在删任意一条边后，这个图**仍然联通**。

将相同属性的点连边（只要连成环即可，不用一一连边），然后跑 tarjan 求双连通分量并缩点，此时就会剩下**一颗树**，合并操作就变成了**在树上加边**（因为同一属性的点必然会缩在同一个点，所以不用担心无法合并的问题）。题目就变成了在树上加边，使得这棵树边双连通，求**加的最少边数**。

显然，一棵树上的两个叶子结点连边**必然出现环**，只要将叶子结点两两连边（如果为奇数还要多连一条），那么必然变成边双连通，且此时**加的边数最少**（可以证明如果连边中没有连叶子结点，那么叶子结点必然无法边双连通，一定更劣），所以答案就是 $\left\lceil\frac{sum_{\text{叶子结点}}}{2}\right \rceil$。

时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define fir first
#define sec second
#define ll long long
using namespace std;
const int N = 1e6 + 10;
int n, c[N], cnt, dfn[N], low[N], esc[N], lst[N], ans, k;
vector<pair<int, int>> d[N];
vector<int> d2[N];
unordered_map<int, bool> ma;
int read()
{
    char ch = getchar();
    int f = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        f = f * 10 + ch - '0', ch = getchar();
    return f;
}
void write(int x)
{
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
void init()
{
    n = read();
    k = read();
    cnt = 0;
    for (int i = 1; i <= n - 1; i++) {
        int u = read(), v = read();
        d[u].push_back({ v, ++cnt });
        d[v].push_back({ u, cnt });
    }
    for (int i = 1; i <= n; i++) {
        c[i] = read();
        if (lst[c[i]]) {
            d[i].push_back({ lst[c[i]], ++cnt });
            d[lst[c[i]]].push_back({ i, cnt });
        }
        lst[c[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (lst[c[i]] && lst[c[i]] != i) {
            d[lst[c[i]]].push_back({ i, ++cnt });
            d[i].push_back({ lst[c[i]], cnt });
            lst[c[i]] = 0;
        }
    }
}
void tar(int nw, int fa)
{
    dfn[nw] = low[nw] = ++cnt;
    int k = 0;
    for (auto i : d[nw]) {
        if (i.fir == fa && !k) {
            k = 1;
            continue;
        }
        if (dfn[i.fir]) {
            low[nw] = min(dfn[i.fir], low[nw]);
        } else {
            tar(i.fir, nw);
            low[nw] = min(low[i.fir], low[nw]);
        }
        if (low[i.fir] > dfn[nw]) {
            ma[i.sec] = 1;
        }
    }
}
void dfs(int nw)
{
    esc[nw] = cnt;
    for (auto i : d[nw]) {
        if (esc[i.fir] && ma.count(i.sec)) {
            d2[cnt].push_back(esc[i.fir]);
            d2[esc[i.fir]].push_back(cnt);
        }
        if (esc[i.fir] || ma.count(i.sec))
            continue;
        dfs(i.fir);
    }
}
int main()
{
    init();
    cnt = 0;
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tar(1, 0);
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!esc[i]) {
            cnt++;
            dfs(i);
        }
    }
    for (int i = 1; i <= cnt; i++) {
        if (d2[i].size() == 1)
            ans++;
    }
    write(ans / 2 + (ans & 1));
    return 0;
}
```

---

## 作者：鱼跃于渊 (赞：3)

## 题意

> 给出一颗有 $n$ 个点的树，每个点有一个颜色。  
> 对于相同颜色的点之间两两连边，求最少需要多少次颜色合并使整张图变成一个边双。  

## 解法

我们首先连上所有的树边，为了满足题目条件，再在所有相同颜色的点之间连边。  
两两连边是 $O(n^2)$ 的，显然不行，事实上我们只需要将相同颜色的点连成一条链或菊花图即可。  
对这张图跑一遍边双，可以得到一棵树，且原图中相同颜色的点在树中都被所成了一个点。  
此时的颜色合并可以看作是在树上两点之间连边，则问题转化为最少需要连多少条边才能使这棵树变成一个边双。  
这实际上等价于在树上选定最少的路径使每个结点都至少被一条路径所覆盖，也就是[这道题](https://www.luogu.com.cn/problem/P2860)。  
根据该题结论，设 $x$ 为叶子结点数量，则答案为 $\lceil\dfrac{x}{2}\rceil$。  
时间复杂度为 $O(n)$，可以通过此题。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define all(x,l,r) &(x)[l],&(x)[r]+1
const int N=5e5+5;
struct edge{
    int v,nxt;
}e[N<<2];
int cnt=1,head[N],vis[N<<2];
int n,c[N],tub[N];
int tot,dfn[N],low[N];
int top,st[N];
int dcnt,dcc[N],deg[N];
void add(int u,int v){
    e[++cnt]={v,head[u]};
    head[u]=cnt;
    e[++cnt]={u,head[v]};
    head[v]=cnt;
}
void tarjan(int u,int ed){
    dfn[u]=low[u]=++tot;
    st[++top]=u;
    for(int i=head[u],v;i;i=e[i].nxt) if((i^1)!=ed){
        if(!dfn[v=e[i].v]){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v]){
                dcnt++;vis[i>>1]=1;
                do dcc[st[top]]=dcnt;
                while(st[top--]!=v);
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
}
void main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>c[0];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        add(u,v);
    }
    per(i,1,n){
        cin>>c[i];
        if(tub[c[i]]) add(tub[c[i]],i);
        else tub[c[i]]=i;
    }
    per(i,1,n) if(!dfn[i]) tarjan(i,0);
    for(int i=1;i<2*n;i++) if(vis[i]){
        deg[dcc[e[i*2].v]]++;
        deg[dcc[e[i*2+1].v]]++;
    }
    cout<<(count(all(deg,0,dcnt),1)+1)/2<<'\n';
}}
signed main(){
    fisher::main();
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# JOISC2019K 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2019_k)

**题目大意**

> 给定一棵 $n$ 个点的树，每个点有颜色，定义一条边是分裂的当且仅当删掉这条边后形成了的两个连通块没有公共的颜色。
>
> 每次操作可以更改某类颜色的所有点变成另一个颜色，求让整棵树的边都不是分裂的的最小操作次数。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

先求出所有分裂的边，然后把不分裂的边缩起来，形成了一棵新的树，每次操作相当于选定两个点，把对应的路径上的分裂边变成不分裂的。

然后变成选若干路径覆盖整棵树，这是经典结论，设 $k$ 为叶子数量，答案为 $\left\lceil\dfrac k2\right\rceil$。

求分裂的边直接树上差分，把同色点之间的路径用树上差分打标记设成不分裂的。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
vector <int> G[MAXN],C[MAXN];
int col[MAXN],fa[MAXN][20],dep[MAXN],cnt[MAXN],deg[MAXN];
inline void dfs0(int u,int fz) {
	fa[u][0]=fz,dep[u]=dep[fz]+1;
	for(int k=1;k<20;++k) fa[u][k]=fa[fa[u][k-1]][k-1];
	for(int v:G[u]) if(v^fz) dfs0(v,u);
}
inline void dfs1(int u,int fz) {
	for(int v:G[u]) if(v^fz) dfs1(v,u),cnt[u]+=cnt[v];
}
inline void dfs2(int u,int fz,int c) {
	for(int v:G[u]) if(v^fz) {
		if(!cnt[v]) ++deg[c],++deg[v],dfs2(v,u,v);
		else dfs2(v,u,c);
	}
}
inline int LCA(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	for(int k=19;~k;--k) if(dep[fa[u][k]]>=dep[v]) u=fa[u][k];
	if(u==v) return u;
	for(int k=19;~k;--k) if(fa[u][k]^fa[v][k]) u=fa[u][k],v=fa[v][k];
	return fa[u][0];
}
signed main() {
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=n;++i) scanf("%d",&col[i]),C[col[i]].push_back(i);
	dfs0(1,0);
	for(int i=1;i<=k;++i) {
		for(int j=1;j<(int)C[i].size();++j) {
			++cnt[C[i][0]],++cnt[C[i][j]],cnt[LCA(C[i][0],C[i][j])]-=2; 
		}
	}
	dfs1(1,0),dfs2(1,0,1);
	int ans=0;
	for(int i=1;i<=n;++i) if(!cnt[i]&&deg[i]==1) ++ans;
	printf("%d\n",(ans+1)/2);
	return 0;
}
```



---

## 作者：Y_QWQ_Y (赞：2)

### 前置芝士
[边双连通分量&点双连通分量](https://blog.csdn.net/a_forever_dream/article/details/103019013)。
### 题意简化
对于同一个洲的城市，我们可以将他们两两连边，求至少要合并多少个州才能使得整张图为边双。

### 解题思路
连好边之后对图缩边双，容易知道缩完之后原图变成了一棵树，原图中每个州的所有点被缩在新图中的同一个点上。这个时候，合并一个州就相当于给树上的两点连边。

于是，问题就被我们转化成了：在给定的树上增加最少的边使得原树形成一个点双。

这时再对问题进行转化，就变成了：求选定最少的边使得所有的点都至少被已选择的一条边覆盖。设有 $x$ 个叶子节点，那么答案就是 $\lceil\frac{x}{2}\rceil$。

解释：最优情况下，选一条边，从一个叶子节点到另一个叶子节点（这条边先从叶子节点 $a$ 出发到达根 $root$，再从根 $root$ 出发到达另一个叶子节点 $b$），总共有 $\lceil\frac{x}{2}\rceil$ 条这样的路径，并且这样的路径一定可以覆盖整棵树。（理解不了建议自己画图理解一下）

显然，我们并不需要对同一个州的点两两连边，只需要保证它们在同一个连通块内即可，所以我们可以把它们连成一个环，就不会超时。
### 代码实现
实现的细节详见注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
int n, k, c[N], la[N], fi[N], cn = 1, h[N], dfn[N], low[N], s[N], top, scc[N], cnt, num, d[N], u[N], v[N], ans;
//c[i] 记录 i 属于哪个州；
//la[] 和 fi[] 用来把相同州的城市连成环；
//h[] 和 cn 是链式前向星；
//dfs[] 和 low[] 用来计算边双连通分量；
//s[] 和 top 是 Tarjan 中的栈；
//scc[i] 表示 i 属于的边双连通分量；
//cnt 记录边双连通分量的个数；d[i] 记录 i 的度，用来计算叶子节点数量；
//u[] 和 v[] 是离线下来的边；
//ans 是叶子结点的数量。
//以上一定要认真看，不然你很难看得懂代码。
bool vis[N];//Tarjan 时记录节点是否在栈内。
struct Edge{int v, nxt;}e[N << 1];
void add (int a, int b)
{
	e[++ cn].nxt = h[a];
	e[cn].v = b;
	h[a] = cn;
}
void Tarjan (int d, int fa)//Tarjan 求边双连通分量的模板。
{
	dfn[d] = low[d] = ++ num;
	s[++ top] = d;
	vis[d] = 1;
	for (int i = h[d]; i; i = e[i].nxt)
	{
		int y = e[i].v;
		if ((i ^ 1) == fa)continue;
		if (! dfn[y])
		{
			Tarjan (y, i);
			low[d] = min (low[d], low[y]);
		}
		else if (vis[y])low[d] = min (low[d], dfn[y]);
	}
	if (low[d] == dfn[d])
	{
		int p = -1;
		++ cnt;
		while (p != d)
		{
			p = s[top --];
			scc[p] = cnt;//记录边双联通分量。
			vis[p] = 0;
		}
	}
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n >> k;
    for (int i = 1; i < n; ++ i)cin >> u[i] >> v[i];//把边离线下来。
	for (int i = 1; i <= n; ++ i)
	{
		cin >> c[i];
		if (la[c[i]])add (i, la[c[i]]), add (la[c[i]], i);//把相同州的城市连成环。
		else fi[c[i]] = i;
		la[c[i]] = i;
	}
	for (int i = 1; i <= k; ++ i)if (la[i] != fi[i] && la[i])add (fi[i], la[i]), add (la[i], fi[i]);//首尾要连边。
	for (int i = 1; i < n; ++ i)if (c[u[i]] != c[v[i]])add (u[i], v[i]), add (v[i], u[i]);//对于相同州的城市已经构成环，不需要连边。
	for (int i = 1; i <= n; ++ i)if (! dfn[i])Tarjan (i, 0);//缩边双联通分量。
	for (int i = 1; i < n; ++ i)if (scc[u[i]] != scc[v[i]])++ d[scc[u[i]]], ++ d[scc[v[i]]];//对于新图中不同点的连边，记录度数。
	for (int i = 1; i <= cnt; ++ i)ans += (d[i] == 1);//记录叶子节点数量。
	cout << (ans + 1) / 2;//在除以 k 时加上 k-1 就相当于向上取整。
	return 0;
}
```

---

## 作者：晴空一鹤 (赞：2)

提供一种不用边双的做法。

找出所有去掉父亲边后不合法的子树，如果存在亲子关系把所有父亲去掉，显然是可以一遍 dfs 求出来的。答案就是子树个数除以二向上取整。

证明考虑上下界分析。下界是显然的，上界我们每次选两个 lca 尽量高的子树合并，如果最后剩了一个直接与根合并就行了。

但注意到有时候会出问题。在 $n$ 为偶数时如果存在一个节点拥有所有的不合法子树，我们就要多一次与根的操作，直接判断即可。

---

## 作者：M_CI (赞：1)

### Part 0. 前言

模考题，想到了做法但是没去打，直到考试结束才知道想对了，遗憾离场，大悲。

---

### Part 1. 思路

显然的，同一州内的所有城市都是不可分裂的，因为我们不可以把一个州劈成几部分，我们可以将其看作一个点。

对于整个岛国，如果这些点（州）与这些边（高速公路）组成的图就是一个 e-DCC（边双连通分量），则必不可分裂。所以我们的目标即为让图变为一个 e-DCC。

我们 Tarjan 求图中的 e-DCC 并缩点。此时，图中能分裂的点，即为度数为 $1$ 的点，因为此时我们把它的唯一连边切断，图就不连通了。

我们可以将这样的点两个一组连边，图即连通。设这样的点有 $k$ 个，答案似乎就是 $\frac{k}{2}$ 了。

且慢！如果有偶数个点，则结论正确。但是，如果有奇数个点，连完后必剩一点还是度数为 $1$，图仍可分裂。我们再连一条边，把它与其余任一点相连即可。所以答案即为 $\lceil \frac{k}{2} \rceil$。

是不是和[某奶牛题](https://www.luogu.com.cn/problem/P2860)一模一样？

---

### Part 2. 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,k,a[1000010],u[1000010],v[1000010],in[1000010];
int tt=1,to[2000010],nx[2000010],hd[1000010];
int rs,dfn[1000010],low[1000010];
int rt,dcc[1000010];
stack<int> s;

void add (int u,int v) {
	to[++tt]=v;
	nx[tt]=hd[u];
	hd[u]=tt;
}

void tarjan (int u,int f) {
	dfn[u]=low[u]=++rs;
	s.push (u);
	for (int i=hd[u];i;i=nx[i]) {
		int v=to[i];
		if (!dfn[v]) {
			tarjan (v,i);
			low[u]=min (low[u],low[v]);
		} else if (i^(f^1)) low[u]=min (low[u],dfn[v]);
	}
	if (dfn[u]==low[u]) {
		dcc[u]=++rt;
		while (s.top ()^u) {
			dcc[s.top ()]=rt;
			s.pop ();
		}
		s.pop ();
	}
}

signed main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie(0); 
	cin>> n>> k;
	for (int i=1;i<n;i++)
		cin>> u[i]>> v[i];
	for (int i=1;i<=n;i++) cin>> a[i];
	for (int i=1;i<n;i++) {
		add (a[u[i]],a[v[i]]);
		add (a[v[i]],a[u[i]]);
	}
	for (int i=1;i<=k;i++)
		if (!dfn[i])
			tarjan (i,0);
	for (int i=1;i<n;i++)
		if (dcc[a[u[i]]]!=dcc[a[v[i]]]) {
			in[dcc[a[u[i]]]]++;
			in[dcc[a[v[i]]]]++;
		}
	int ans=0;
	for (int i=1;i<=rt;i++)
		ans+=(in[i]==1);
	cout<< (ans+1)/2;
	return 0;
}
```

---

### Part 3. 后记

总结：下次模考遇到这种板子题必须先开先做，拿分最重要。

完。

---

## 作者：Dovish (赞：0)

## 题解
我们不妨称每个城市所属的州为这个点的颜色。

首先，我们考虑题目中“可分裂的”的实质是什么：存在一条边，使得割掉这条边之后两个连通块的点的颜色集合没有交集。我们不妨称这样的边为关键边。

显然，我们容易发现，对于同一个颜色集合中的任意两点之间路径上的所有边都不是关键边。

我们可以将被关键边分开的若干个连通块缩点，并将这些点之间由关键边相连形成一颗新的树形结构。根据上文，我们合并两个连通块各自的某一颜色等价于将这两点在新树上的路径上的所有关键边变为非关键边。我们要做的就是覆盖整颗树。

于是做法就呼之欲出了，先建虚树染色，然后缩点，答案就是 $\lceil\frac{新树的叶子个数}{2}\rceil$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
#define lc (u<<1)
#define rc (u<<1|1)
#define pii pair<int,int>
#define pdd pair<double,double>
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
#define fst first
#define sed second
using namespace std;
const int N=5e5+10,M=1e6+10,inf=1e9,mod=1e9+7;
const double eps=1e-9;
struct sx
{
	int next,to,val;
}e[N<<1];
int head[N],tot=1,n,m,cf[N],ans;
void add(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
vector<int>q[N];
int dfn[N],rev[N],res;
int sz[N],wson[N],deep[N],st[N],f[N];
void dfs(int u,int fa)
{
	f[u]=fa;
	deep[u]=deep[fa]+1;
	sz[u]=1;
	dfn[u]=++res;
	rev[res]=u;
	edge(i,u)
	if(e[i].to!=fa)
	{
		int v=e[i].to;
		dfs(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[wson[u]])wson[u]=v;
	}
}
void df5(int u,int fa,int st_)
{
	st[u]=st_;
	if(wson[u])df5(wson[u],u,st_);
	edge(i,u)
	if(e[i].to!=fa&&e[i].to!=wson[u])
	{
		int v=e[i].to;
		df5(v,u,v);
	}
}
int LCA(int u,int v)
{
	int fx=st[u],fy=st[v];
	if(fx==fy)return deep[u]<deep[v]?u:v;
	if(deep[fx]>deep[fy])return LCA(f[fx],v);
	else return LCA(u,f[fy]);
}
bool cmp(int a,int b)
{
	return dfn[a]<dfn[b];
}
void Taged(int u,int v)
{
	int lca=LCA(u,v);
	if(lca!=u&&lca!=v)
	{
		cf[u]++;
		cf[v]++;
		cf[lca]-=2;
	}
	else 
	{
		cf[lca]--;
		if(u!=lca)cf[u]++;
		else cf[v]++;
	}
}
void take_cf(int u,int fa)
{
	edge(i,u)
	if(e[i].to!=fa)
	{
		int v=e[i].to;
		take_cf(v,u);
		cf[u]+=cf[v];
		if(cf[v])e[i].val=e[i^1].val=1;
	}
}
bool vis[N];
void getans(int u)
{
	int tag=0;
	queue<int>q;
	q.push(u);
	vis[u]=1;
	while(q.size())
	{
		int u=q.front();
		q.pop();
		edge(i,u)
		{
			int v=e[i].to;
			if(e[i].val)
			{
				if(vis[v])continue;
				vis[v]=1;
				q.push(v);
			}
			else tag++;
		}
	}
	if(tag==1)ans++;//叶子 
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	rep(i,2,n)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	df5(1,0,1);
	rep(i,1,n)
	{
		int u;
		cin>>u;
		q[u].pb(i);
	}
	rep(i,1,m)
	{
		sort(q[i].begin(),q[i].end(),cmp);
		int len=q[i].size();
		rep(j,1,len-1)
		Taged(q[i][j-1],q[i][j]);
	}
	take_cf(1,0);
	rep(i,1,n)
	if(!vis[i])
	getans(i);
	cout<<(ans+1)/2<<'\n';
}
```

---

## 作者：Graphcity (赞：0)

注意到给所有城市进行 X/Y 的分组，相当于选择一条边断开。问题变成了找到所有断开后符合条件的边。

考虑给每个城市一个哈希值，这个值要满足所有州的城市哈希值异或和为零。一条边被断开符合条件当且仅当子树中所有点哈希值异或和为零。

然后给这棵树缩点，只保留符合条件的边，其它边全部缩起来。接下来我们证明：**如果图中有 $k$ 个叶子（度数为 $1$ 的结点），那么至多合并 $\lceil\dfrac{k}{2}\rceil$ 次就能满足题目最终的要求。** 

合并两个点能够让两个点之间的边都符合最终要求。所以合并时我们尽量选择叶子结点，让每次满足的边数尽量多。所以我们至少合并$\lceil\dfrac{k}{2}\rceil$ 次。

设叶子结点权值为 1，其它结点权值为 0，然后找到这棵树的带权重心，以它为根求出 dfs 序。让 dfs 序在前 $\lfloor \dfrac{k}{2}\rfloor$ 小的叶子结点向它后面 $\lfloor\dfrac{k}{2}\rfloor$ 位的叶子合并。如果最后剩下一个叶子结点就让它和根连边。注意到重心的每一棵子树叶子结点都不超过 $\lfloor\dfrac{k}{2}\rfloor$ 个，所以合并时的 LCA 一定是根结点，最终一定覆盖了根结点到每个叶子的链，也就是整棵树。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,dx[Maxn+5],chk[Maxn+5],deg[Maxn+5],s;
ull h[Maxn+5],col[Maxn+5],sum[Maxn+5];
mt19937_64 rnd(time(0));
vector<int> v[Maxn+5];

inline void dfs(int x,int f)
{
    sum[x]=h[x];
    for(auto y:v[x]) if(y!=f) dfs(y,x),sum[x]^=sum[y];
}
inline void dfs1(int x,int f,int k)
{
    col[x]=k;
    for(auto y:v[x]) if(y!=f)
        {if(chk[y]) dfs1(y,x,++s); else dfs1(y,x,k);}
}

int main()
{
    n=read(),m=read();
    For(i,1,n-1)
    {
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a);
    }
    For(i,1,n) dx[i]=read(),h[i]=rnd(),col[dx[i]]^=h[i];
    For(i,1,n) h[i]^=col[dx[i]],col[dx[i]]=0;
    dfs(1,0);
    For(i,1,n) chk[i]=(sum[i]==0);
    s=1,dfs1(1,0,1);
    For(i,1,n) for(auto j:v[i]) if(col[i]!=col[j]) deg[col[i]]++;
    int cnt=0;
    For(i,1,s) cnt+=(deg[i]==1);
    if(cnt<=1) cout<<0<<endl;
    else cout<<(cnt+1)/2<<endl;
    return 0;
}
```

---

