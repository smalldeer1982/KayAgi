# Greedy Merchants

## 题目描述

In ABBYY a wonderful Smart Beaver lives. This time, he began to study history. When he read about the Roman Empire, he became interested in the life of merchants.

The Roman Empire consisted of $ n $ cities numbered from $ 1 $ to $ n $ . It also had $ m $ bidirectional roads numbered from $ 1 $ to $ m $ . Each road connected two different cities. Any two cities were connected by no more than one road.

We say that there is a path between cities $ c_{1} $ and $ c_{2} $ if there exists a finite sequence of cities $ t_{1},t_{2},...,t_{p} $ $ (p>=1) $ such that:

- $ t_{1}=c_{1} $
- $ t_{p}=c_{2} $
- for any $ i $ $ (1<=i<p) $ , cities $ t_{i} $ and $ t_{i+1} $ are connected by a road

We know that there existed a path between any two cities in the Roman Empire.

In the Empire $ k $ merchants lived numbered from $ 1 $ to $ k $ . For each merchant we know a pair of numbers $ s_{i} $ and $ l_{i} $ , where $ s_{i} $ is the number of the city where this merchant's warehouse is, and $ l_{i} $ is the number of the city where his shop is. The shop and the warehouse could be located in different cities, so the merchants had to deliver goods from the warehouse to the shop.

Let's call a road important for the merchant if its destruction threatens to ruin the merchant, that is, without this road there is no path from the merchant's warehouse to his shop. Merchants in the Roman Empire are very greedy, so each merchant pays a tax (1 dinar) only for those roads which are important for him. In other words, each merchant pays $ d_{i} $ dinars of tax, where $ d_{i} $ ( $ d_{i}>=0 $ ) is the number of roads important for the $ i $ -th merchant.

The tax collection day came in the Empire. The Smart Beaver from ABBYY is very curious by nature, so he decided to count how many dinars each merchant had paid that day. And now he needs your help.

## 说明/提示

The given sample is illustrated in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178B1/4913bb025cb3137535b72c7a1543583701455251.png)Let's describe the result for the first merchant. The merchant's warehouse is located in city $ 1 $ and his shop is in city $ 5 $ . Let us note that if either road, $ (1,2) $ or $ (2,3) $ is destroyed, there won't be any path between cities $ 1 $ and $ 5 $ anymore. If any other road is destroyed, the path will be preserved. That's why for the given merchant the answer is $ 2 $ .

## 样例 #1

### 输入

```
7 8
1 2
2 3
3 4
4 5
5 6
5 7
3 5
4 7
4
1 5
2 4
2 6
4 7
```

### 输出

```
2
1
2
0
```

# 题解

## 作者：Isshiki·Iroha (赞：3)

# 题解
先说一下，这题应该评个蓝或紫差不多吧。

[题目传送门](https://www.luogu.com.cn/problem/CF178B1)

[更好的阅读体验](https://www.luogu.com.cn/blog/yousa22/solution-cf178b1)

**本题解更偏向对思路的讲解，所以不会对算法进行太对的讲解，请先去了解前置芝士**

### 前置芝士
[边双连通分量](https://www.luogu.com.cn/problem/P2860)

[LCA](https://www.luogu.com.cn/problem/P3379)

### 分析题目

看看题目意思:

对于一个点对 $(u,v)$，如果删去某条边会使得 $u$ 和 $v$ 不连通，那么称这条边对于点对 $(u,v)$ 是关键的。

删去一条边能不能连通？有没有想到什么？

**边双连通分量**

#### 定义
```cpp
若一个无向图中的去掉任意一条边都不会改变此图的连通性，即不
存在桥，则称作边双连通图。一个无向图中的每一个极大边双连通
子图称作此无向图的边双连通分量。
```

这不刚刚好符合此题要你求的东西吗？

也就是说：在同一个边双连通分量里面的点都没有关键边。换过来想，就是不在同一个边双连通分量里面的点都有关键边，就是有割边呗？

看看样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/xunvsj67.png)


这是找完边双连通分量之后的图:（颜色相同的点在一个边双连通分量，边的颜色是棕色说明是割边）


![](https://cdn.luogu.com.cn/upload/image_hosting/5du009a9.png)

方便你们看，我重新画了一份：

边双连通分量 $4$:对应 $1$

边双连通分量 $3$:对应 $2$

边双连通分量 $2$:对应 $3,4,5,7$

边双连通分量 $1$:对应 $5$

![](https://cdn.luogu.com.cn/upload/image_hosting/f1ze3ghe.png)

现在要求 $(1,4)$ 有几个关键边，不就是他们的路上有几条割边吗？咦，这是树，那不都是割边吗？咦，那不就是两点的距离吗？

想到这里，你应该已经懂了：

就是：Tarjan 找边双连通分量 -> 求 LCA(不会的自行学习)

又到了你们喜欢的代码环节了 157ms Rank 1：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace Mashiro {
    char buf[1<<18],*p1=buf,*p2=buf;
    inline int getc() {
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++;
    }
#define getc() getchar()
    template<typename T>inline void read(T& x) {
        x=0;int f=1;
        char ch=getc();
        while(!isdigit(ch)){if(ch=='-')f=~f+1;ch=getc();}
        while (isdigit (ch)) {x=(x<<3)+(x<<1)+(ch^48);ch=getc();}
        x*=f;
    }
    template <typename T,typename... Args> inline void read(T& x, Args&... args) {
        read(x);
        read(args...);
    }
    char buffer[1<<18];int p11=-1;const int p22=(1<<18)-1;
    inline void flush() {fwrite(buffer,1,p11+1,stdout),p11=-1;}
    inline void putc(const char &x) {if (p11==p22) flush();buffer[++p11]=x;}
    template<typename T>inline void write(T x) {
        static int buf[40],top=0;
        if(x<0)putc('-'),x=~x+1;
        while(x)buf[++top]=x%10,x/=10;
        if(top==0)buf[++top]=0;
        while (top) putc(buf[top--]^48);
        putc(' ');
        flush();
     }
     template <typename T,typename... Args> inline void write(T x, Args... args) {
         write(x);
         write(args...);
     }
}
template<typename T>
T Min(T a,T b){
    return a>b?b:a;
}
using namespace Mashiro;
const int maxn=1e5+10;
const int maxm=2e5+10;
const int LogN=20;
//All
int n,m,k;
//All

//Map
int head[maxn],tot=1;
struct node{
    int u,v,nxt;
}kano[maxm];
inline void add_kano(int u,int v){
    ++tot;
    kano[tot].nxt=head[u];
    kano[tot].u=u;
    kano[tot].v=v;
    head[u]=tot;
}
//Map

//Tarjan
int dfn[maxn],low[maxn],dfstime;
int Instack[maxn],St[maxn],top;
int scc_belong[maxn],scc_cnt;
int side_vis[maxn];
void Tarjan(int u){
    dfn[u]=low[u]=++dfstime;
    Instack[u]=1;
    St[++top]=u;
    for(int i(head[u]);i;i=kano[i].nxt){
        if(side_vis[i])continue;
        side_vis[i]=side_vis[i^1]=1;
        int v=kano[i].v;
        if(!dfn[v]){
            Tarjan(v);
            low[u]=Min(low[u],low[v]);
        }
        else if(Instack[v]){
            low[u]=Min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        int v;
        ++scc_cnt;
        do{
            v=St[top--];
            Instack[v]=0;
            scc_belong[v]=scc_cnt;
        }while(v!=u);
    }
}
//Tarjan

//Lca
int f[maxn][LogN+1],dep[maxn];
void dfs(int u,int fa){
    f[u][0]=fa;
    dep[u]=dep[fa]+1;
    for(int i(head[u]);i;i=kano[i].nxt){
        int v=kano[i].v;
        if(v==fa)continue;
        dfs(v,u);
    }
}
void Pre(){
    for(int i(1);i<=LogN;++i){
        for(int j(1);j<=n;++j){
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
}
inline int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i(LogN);i>=0;--i){
        if(dep[f[x][i]]>=dep[y]){
            x=f[x][i];
        }
    }
    if(x==y)return x;
    for(int i(LogN);i>=0;--i){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
inline int Dist(int x,int y){
    return dep[x]+dep[y]-(dep[lca(x,y)]<<1);
}
//Lca
int main() {
    read(n,m);
    for(int i(1),u,v;i<=m;++i){
        read(u,v);
        add_kano(u,v);
        add_kano(v,u);
    }
	Tarjan(1);
    memset(head,0,sizeof head);
    int ttot=tot;
    tot=0;
    for(int i(2),Tx,Ty;i<=ttot;i+=2){
        Tx=scc_belong[kano[i].u];
        Ty=scc_belong[kano[i].v];
        if(Tx==Ty)continue;
        add_kano(Tx,Ty);
        add_kano(Ty,Tx);
    }
    dfs(1,0);
    Pre();
    read(k);
    for(int i(1),x,y;i<=k;++i){
        read(x,y);
        x=scc_belong[x];
        y=scc_belong[y];
        write(Dist(x,y));
        //write(x,y);
        putc('\n');
    }
    return 0;
}

```


---

## 作者：LuomuQDM (赞：1)

### 说句闲话

随便找了道 CF 的题，没想到刚好有小同学 [蒟蒻·廖子阳](https://www.luogu.com.cn/user/539211) 的题解，于是心血来潮，自己写了一份代码，没想到一遍 A 了，就跑了 [30ms](https://www.luogu.com.cn/record/91666202)（远快于本题某自认很快题解）。

~~由于我励志找出小同学题解的缺点，下面的讲解部分内容是针对他的。~~

### 题意

将题意简单地翻译为 OIer 喜闻乐见的形式：一个 $n$ 个点 $m$ 条边的无向连通图中，求出多组点对之间的，所有路径中必经之路的条数。在 tarjan 算法中，这种边被称为“桥”。

因为当删除所谓“桥”后，所求点对的每条路径都缺少了此“桥”边，从而没有一条路径可以继续由点对其中一点到达另一点。

### 思路

显然，在一个双连通分量中，可以做到任意两点间不存在桥，所以我们先对原图进行缩点。

**缺点1**：这里我就要提出另外两篇题解的一个共同缺点了（虽然不能算错）。无向连通图的边是双向的（废话），所以由假定的根节点到达一条路径上时，若某一点指向了由根节点出发的其他路径，也是可以构成双连通分量的，所以 $\text{instack}$ 数组是无意义的。

缩完点后，因为原图是联通的，且环都被处理掉了，所以剩下的是一个树形图，图上留下的边也就是前面所说的“桥”了。那么两点间的桥有几条，也就是求当前树形图上两点（缩点后的两点）间边的条数。此时我们可以初始化一个数组 $deep$，$deep_i$ 表示从树形图中假定的根节点（因为是无根图，以 $1$ 作为根即可）到 $i$ 号节点间的路径条数（我代码里写的是路径条数 $+1$，其实没区别，下文简称 $d_i$）。计算 $a,b$ 节点间的“桥”数量，我们先求得 $a,b$ 缩点后的点编号 $color_a,color_b$（下文简称 $c_a,c_b$），和这缩点后这两点的最近公共祖先 $lca_{a,b}$。

$c_a$ 到 $c_b$ 的路径即为：$c_a\to lca_{a,b}\to c_b$，这两段的路径长度显然分别为：$d_{c_a}-d_{lca_{a,b}}$ 和 $d_{c_a}-d_{lca_{a,b}}$。

所以两点间的“桥”数量就是 $d_{c_a}+d_{c_b}-2\times d_{lca_{a,b}}$。

**缺点2**：小同学提到要特判缩点后连边出现重边，其实并不用。显然初始化 $d$ 和倍增数组 $f$ 树上每个点遍历一次就够了，所以定义一个 $visit$ 数组记录哪些点已经初始化过了就行。

### 代码

贴一份我自己的代码，里面包含了部分个人代码习惯。希望这篇题解对你有帮助。

```
#include<bits/stdc++.h>
#define N 100010
using namespace std;
inline int ri(){//快读。我习惯快读int用ri()，快读ll用rl()
	char c=getchar();int ans=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans=(ans<<3)+(ans<<1)+c-'0',c=getchar();
	return ans*f;
}
int head[N<<1],nxt[N<<1],to[N<<1],cnt=1;//前向星存边
bool v[N<<1];//记录哪些边已经走过了，具体用处下面会将
void ade(int u,int v){
	nxt[++cnt]=head[u],to[cnt]=v;
	head[u]=cnt;
}
int dfn[N],low[N],ct;
vector<int>p[N];//vector存缩完点之后的图，节约一点空间
int c[N],sum,s[N],h;
void tj(int x){
	dfn[x]=low[x]=++ct;
	s[++h]=x;//不需要instack！
	int y;
	for(int i=head[x];i;i=nxt[i]){
		if(v[i])continue;
		v[i]=v[i^1]=1;//i^1可以做到成对变换（2n->2n+1，2n+1->2n），
//无向图存边是成对储存的，这样我们把第一条边编号设为2，
//使用这种成对变换的方法就可以避免题目给出重边、自环对结果的影响
//虽然这题没有重边，但是我被坑过不少次，所以这种题都这么打准没错
		y=to[i];
		if(!dfn[y]){
			tj(y);
			low[x]=min(low[x],low[y]);
		}else low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		sum++;
		do{
			y=s[h--];
			c[y]=sum;
		}while(y!=x);
	}
}
bool vis[N];
int n,m,a,b;
int f[N][20],d[N];
void dfs(int x){
	vis[x]=1,d[x]=d[f[x][0]]+1;
	int y;
	for(int i=0;i<p[x].size();i++){
		y=p[x][i];
		if(vis[y])continue;
		f[y][0]=x;
		for(int j=1;f[f[y][j-1]][j-1];j++){
			f[y][j]=f[f[y][j-1]][j-1];
		}
		dfs(y);
	}
}
inline int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	for(int i=19;~i;i--){
		if(d[f[x][i]]>=d[y])x=f[x][i];
	}
	if(x==y)return x;
	for(int i=19;~i;i--){
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
signed main(){
	n=ri(),m=ri();
	for(int i=1;i<=m;i++){
		a=ri(),b=ri();
		ade(a,b),ade(b,a);
	}
	tj(1);
	int y;
	for(int i=1;i<=n;i++){
		for(int j=head[i];j;j=nxt[j]){
			y=to[j];
			if(c[i]==c[y])continue;
			p[c[i]].push_back(c[y]);
//不要搞错成c[i]->c[j]了（因为我在这死过）
			p[c[y]].push_back(c[i]);
		}
	}
	dfs(1);
	m=ri();
	while(m--){
		a=c[ri()],b=c[ri()];
		if(a==b)printf("0\n");
		else printf("%d\n",d[a]+d[b]-2*d[lca(a,b)]);
	}
	return 0;
}

```

---

## 作者：lzyqwq (赞：1)

这题就是让我们求从 $x$ 到 $y$ 经过了几条割边，所以我们可以用 `Tarjan` 进行边双缩点，然后缩出来的图就是一棵树，且树上的边全是割边，因此将问题转化为树上距离。

如何快速求树上距离？我们先指定一个根，搞出每个边双连通分量在树中的深度 $d$，然后求 $x$ 和 $y$ 所在边双连通分量（分别设为 $X$ 和 $Y$）的 `LCA`，最后的答案就是 $d_X-d_{LCA}+d_Y-d_{LCA}$。

注意，建缩点后的图要避免重边。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 1;
int n, m, k, dfn[N], low[N], ebc[N], cnt, sum, lg[N], d[N], f[20][N];
vector<int> g[N], e[N];
stack<int> s;
bool is[N];
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++cnt;
    s.push(x);
    is[x] = 1;
    for (int i : g[x]) {
        if (i != fa) {
            if (!dfn[i]) {
                tarjan(i, x);
                low[x] = min(low[x], low[i]);
            } else if (is[i]) {
                low[x] = min(low[x], dfn[i]);
            }
        }
    }
    if (dfn[x] == low[x]) {
        ++sum;
        while (1) {
            int p = s.top();
            s.pop();
            is[p] = 0;
            ebc[p] = sum;
            if (x == p) {
                break;
            }
        }
    }
}
void dfs(int x, int fa) {
    if (fa) {
        d[x] = d[fa] + 1;
        f[0][x] = fa;
        for (int i = 1; i <= lg[d[x]]; i++) {
            f[i][x] = f[i - 1][f[i - 1][x]];
        }
    }
    for (int i : e[x]) {
        if (i != fa) {
            dfs(i, x);
        }
    }
}
inline int lca(int x, int y) {
    if (d[x] < d[y]) {
        swap(x, y);
    }
    while (d[x] > d[y]) {
        x = f[lg[d[x] - d[y]]][x];
    }
    if (x == y) {
        return x;
    }
    for (int i = lg[d[x]]; i >= 0; i--) {
        if (f[i][x] != f[i][y]) {
            x = f[i][x];
            y = f[i][y];
        }
    }
    return f[0][x];
}
int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tarjan(1, 0);
    for (int i = 1; i <= n; i++) {
        lg[i] = log2(i);
        for (int j : g[i]) {
            if (ebc[i] < ebc[j]) {//判重边
                e[ebc[i]].push_back(ebc[j]);
                e[ebc[j]].push_back(ebc[i]);
            }
        }
    }
    dfs(1, 0);
    cin >> k;
    for (int i = 1, u, v, q; i <= k; i++) {
        cin >> u >> v;
        if (ebc[u] == ebc[v]) {//在同一个边双中
            cout << "0\n";
            continue;
        }
        q = lca(ebc[u], ebc[v]);
        cout << d[ebc[u]] + d[ebc[v]] - (d[q] << 1) << '\n';
    }
    return 0;
}
```


---

## 作者：Yexo (赞：0)

## 写在前面
由于「极其稳定」的洛谷 RMJ 系统和「延迟极低」的 CF 平台的功劳，导致我在 Luogu 上并没有 AC 记录，故在此附上 [CF 的 AC 记录](https://codeforces.com/contest/178/submission/275535294)。

在 LA 看见的这道题，发现很水，大喜过望。

## Solution

解题方向：边双连通分量，LCA。

具体思路：由于是无向图，设一个点对 $ (u, v) $，若有一条边删去后使 $ u $ 和 $ v $ 并不连通那必然是其割边，那么我们就可以用边双连通分量将整个图转化为一棵树，变成树上问题。

那么怎么来求割边数量呢？我们可以容易观察到，点对 $ (u, v) $ 的关键边数量就是其所属的双边连通分量之间路径上边的数量，那么就是求两点路径长，也就是 LCA 可以解决的问题。设 $ u, v $ 所在的边双连通分量分别为 $ i, j $，则对于每个点对答案为 $ dep_i + dep_j - dep_{lca} \times 2 $。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
vector<pair<int,int> > G[N]; //原图
int dfn[N],low[N];
int cnt,sum;
int belong[N];
stack<int> st;
vector<int> NG[N]; //新图
int dep[N];
void tarjan(int x,int edge){
    ++cnt;
    dfn[x]=low[x]=cnt;
    st.push(x);
    for(auto i:G[x]){
        if(i.second==(edge^1)) continue;
        if(!dfn[i.first]) tarjan(i.first,i.second),low[x]=min(low[x],low[i.first]);
        else low[x]=min(low[x],dfn[i.first]);
    }
    if(low[x]==dfn[x]){
        int t;
        sum++;
        do{
            t=st.top();
            st.pop();
            belong[t]=sum;
        }while(t!=x);
    }
}
int f[N][32];
void dfs(int x,int fa){
    dep[x]=dep[fa]+1;
    for(int i=1;(1<<i)<=dep[x];i++) f[x][i]=f[f[x][i-1]][i-1];
    for(auto i:NG[x]){
        if(i==fa) continue;
        f[i][0]=x;
        dfs(i,x);
    }
}
int query(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=__lg(n);i>=0;i--) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=__lg(n);i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back({v,i<<1});
        G[v].push_back({u,i<<1|1});
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i,0);
    }
    for(int i=1;i<=n;i++){
        for(auto j:G[i]){
            if(belong[i]!=belong[j.first]) NG[belong[i]].push_back(belong[j.first]);
        }
    }
    dfs(1,0);
    int k;
    scanf("%d",&k);
    while(k--){
        int u,v;
        scanf("%d%d",&u,&v);
        if(belong[u]==belong[v]){
            printf("0\n");
            continue;
        }
        int lca=query(belong[u],belong[v]);
        printf("%d\n",dep[belong[u]]+dep[belong[v]]-2*dep[lca]);
    }
}
```

---

## 作者：QWQ_123 (赞：0)

显然的，这个就是求两点之间有多少个割边。

因为对于边双中的边，不论删掉哪一条边，这个边双依旧联通。

所以将边双缩成一个点，最后就是一棵树，因为如果不是一棵树，那么一定还有边双。

让后剩余的边就是割边，然后就是求两点间的边的数量，树上前缀和差分即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int bel[N], dfn[N], low[N], dfn_idx, bel_idx;
bool st[N];
vector<pair<int, int>> e[N];
vector<pair<int, int>> e1[N], Edge;
int top[N], dfn1[N], fa[N], dep[N], son[N], sz[N], idx;

void tarjan(int u, int la = 0) {
	dfn[u] = low[u] = ++dfn_idx;
	// cout << u << ' ' << la << ' ' << dfn[u] << ' ' << low[u] << endl;

	for (auto [v, id] : e[u]) {
		if (id != (la ^ 1)) {
			if (!dfn[v]) {
				tarjan(v, id);
				if (dfn[u] < low[v]) st[id] = st[id ^ 1] = true;
				low[u] = min(low[u], low[v]);
			} else low[u] = min(low[u], dfn[v]);
		}
	}
}

void dfs(int u) {
	bel[u] = bel_idx;

	for (auto [v, id] : e[u]) {
		if (!bel[v] && !st[id]) dfs(v);
	}
}

void dfs1(int u, int f = 0) {
	fa[u] = f;
	dep[u] = dep[f] + 1;
	sz[u] = 1;

	for (auto [v, j] : e1[u]) {
		if (v != f) {
			dfs1(v, u);

			sz[u] += sz[v];
			if (!son[u] || sz[son[u]] < sz[v]) son[u] = v;
		}
	}
}

void dfs2(int u, int topf) {
	top[u] = topf;
	dfn1[u] = ++idx;

	if (son[u]) dfs2(son[u], topf);

	for (auto [v, j] : e1[u]) {
		if (fa[u] != v && v != son[u]) {
			dfs2(v, v);
		}
	}
}

int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}

	if (dep[u] > dep[v]) swap(u, v);

	return u;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		e[u].push_back({v, i << 1});
		e[v].push_back({u, i << 1 | 1});
		Edge.push_back({u, v});
	}

	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, 0);

	for (int i = 1; i <= n; ++i) if (!bel[i]) {
		++bel_idx;
		dfs(i);
	}


	for (auto [u, v] : Edge) {
		if (bel[u] != bel[v]) {
			e1[bel[u]].push_back({bel[v], bel[u]});
			e1[bel[v]].push_back({bel[u], bel[v]});
		}
	}

	dfs1(bel[1]);
	// if (n == 1300) return 0;
	dfs2(bel[1], bel[1]);


	int q; scanf("%d", &q);	

	for (int i = 1; i <= q; ++i) {
		int u, v; scanf("%d%d", &u, &v);

		printf("%d\n", dep[bel[u]] + dep[bel[v]] - 2 * dep[LCA(bel[u], bel[v])]);
	}

	return 0;
}
```

---

