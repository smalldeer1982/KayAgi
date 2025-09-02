# [AGC004D] Teleporter

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc004/tasks/agc004_d

高橋王国には $ N $ 個の町があります。 町は $ 1 $ から $ N $ まで番号が振られています。 町 $ 1 $ は首都です。

それぞれの町にはテレポーターが $ 1 $ 台ずつ設置されています。 町 $ i $ ($ 1\ <\ =i\ <\ =N $) のテレポーターの転送先は町 $ a_i $ ($ 1\ <\ =a_i\ <\ =N $) です。 **どの町から出発しても、テレポーターを何回か使うことで首都へ辿り着ける**ことが保証されます。

高橋王は正の整数 $ K $ が好きです。 わがままな高橋王は、いくつかのテレポーターの転送先を変え、次の条件が成り立つようにしたいと思っています。

- どの町から出発しても、テレポーターをちょうど $ K $ 回使うと、最終的に首都にいる。

条件が成り立つようにするためには、最少でいくつのテレポーターの転送先を変えればよいかを求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =N\ <\ =10^5 $
- $ 1\ <\ =a_i\ <\ =N $
- どの町から出発しても、テレポーターを何回か使うことで首都へ辿り着ける。
- $ 1\ <\ =K\ <\ =10^9 $

### Sample Explanation 1

テレポーターの転送先を $ a\ =\ (1，1，1) $ と変えればよいです。

### Sample Explanation 2

最初から条件が成り立っているので、テレポーターの転送先を変える必要はありません。

### Sample Explanation 3

例えば、テレポーターの転送先を $ a\ =\ (1，1，2，1，1，2，2，4) $ と変えればよいです。

## 样例 #1

### 输入

```
3 1
2 3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2
1 1 2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
8 2
4 1 2 3 1 2 3 4```

### 输出

```
3```

# 题解

## 作者：activeO (赞：13)

## 题意

给一个图，让你修改一些边的终点使得每个点走 $ k $ 次都是节点 $ 1 $。（每个点只有一条出边）

## 思路

首先可以发现 $ 1 $ 号节点一定要指向自己，不然如果对于 $ u $ 这个节点经过 $ v $，$ k $ 步到达 $ 1 $ 号点的话，$ v $ 就不会满足要求。

然后就是一个很简单的贪心过程：从叶节点开始，每 $ k $ 层的节点（这课子树的根节点不是 $ 1 $ 号点）都把这个根指向 $ 1 $ 号点，这样显然是最优的。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=1e5+5;
struct edge{
	int to,nxt;
}e[maxn<<1];
int head[maxn],len;
int n,k,a[maxn],ans=0;

inline void init(){
	memset(head,-1,sizeof(head));
	len=0;
}
void add(int u,int v){
	e[++len].to=v;
	e[len].nxt=head[u];
	head[u]=len;
}

int dfs(int u,int f,int dep){//贪心修边
	int res=dep;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		res=max(res,dfs(v,u,dep+1));
	}
	if(a[u]!=1&&res-dep==k-1){//k层
		ans++;
		return 0;
	}
	return res;
}

int main(){
	
	init();
	
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	if(a[1]!=1) ans=a[1]=1;//修改 1 号点终点
	
	for(int i=2;i<=n;i++){
		add(i,a[i]);
		add(a[i],i);
	}
	
	dfs(1,0,0);
	
	printf("%d\n",ans);
	
	return 0;
}
```


---

## 作者：ezoiLZH (赞：10)

## 题解：
这是一道挺有趣的题……

他要让任一点都在 $K$ 秒到首都，那首都肯定要自环，可以一直转 $K$ 秒。

那么剩下只有 $n-1$ 条边了，变成了一颗很漂亮的树。

那我们选一些电缆，把它换成连向1，也就是把原树分成几棵树，其中这几棵树的最大深度不能超过 $K-1$。（显然吧，如果距离短了可以在首都的自环上绕）

然后这就可以贪心了！……

## CODE：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int n,k,ans=0;
int tot=0,h[100005],a[100005];
struct Edge{
	int x,next;
}e[200005];

inline void add_edge(int x,int y){
	e[++tot].x=y;
	e[tot].next=h[x],h[x]=tot;
}

int dfs(int x,int deep){
	int ret=deep;
	for(int i=h[x];i;i=e[i].next)
		ret=max(ret,dfs(e[i].x,deep+1));
	if(a[x]!=1&&ret-deep==k-1)return ans++,0;
	else return ret;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	if(a[1]!=1)ans=a[1]=1;
	for(int i=2;i<=n;i++)add_edge(a[i],i);
	dfs(1,0),printf("%d",ans);
}
```

---

## 作者：LawrenceSivan (赞：9)

# AT2044 [AGC004D] Teleporter

## 前言

可能是比较简单的 AGC 题？

不过也比较妙。

## 题意：

>  有一个 $n$ 个点 $n$ 条边的有向连通图，边权都是 $1$，请你修改一些边的终点，使得对于任何一个点，都存在一条长度为 $k$ 的到达点 $1$ 的路径。

## sol

注意到 $k$ 很大但是 $n$ 的规模比较小，这说明次数是极有可能用不完的，于是我们需要在里面兜圈子。

对于所有的点，我们不大可能强行要求他们真的到 $1$ 号节点的距离是实打实的 $k$，于是我们只能要求首都有自环。

于是首先将 $1$ 号节点设置自环之后，你发现这个图就变成了一个内向基环树。

接下来你的任务就是限制环上扩展出去的树的深度要在 $k$ 之内。

于是你考虑建出反图，直接在反图上跑 dfs，找到深度超过 $k$ 的就把节点强行拉到 $1$ 号节点上去。

看似是一个非常正确且不错的思路，但是你稍加思考发现了这个问题：

如果我们按照这样的思路进行，那么可能会碰到当前一个节点恰好是距离为 $k$ ，于是你不需要进行改动，但是他后面的节点就都需要改动，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nxmvgi6r.png)

如果 $k=2$ ，那么 $x$ 点恰好满足条件，如果你现在不改动他，那么你就要被迫改动后面的所有的点，总改动是 $4$ （包含更改自环）。

但是如果你直接把 $x$ 扔到 $1$ 号节点去，那么后面的点就都不用改了，于是总次数 $2$ 次。

如果你想着这样的话似乎可以判断度数然后进行一些操作。

但这样似乎太麻烦了，我们考虑更简单的方法：

上面的内容启示我们需要递归到最底层自底向上考虑。

于是我们掏出数组 $dis$ 表示从叶子结点走了到当前节点的距离。

于是当 $dis=k-1$ 时意味着我们需要一次更改操作了。

关于 $dis$ 的转移，显然是 `dis[u]=max(dis[u],dis[v]+1)`

 之后有个小细节，如果一个节点 $u$ 拉到 $1$ 号节点，那么以 $u$ 为根的一整棵子树相当于都变成了 $1$ 号结点的子树，那么 $u$ 原来的父亲就相当于变成了现在的叶子节点。

$dis$ 数组如何处理？很简单，将 $dis[u]$ 置成 $-1$ 即可，这样经过上面的转移 $dis[fa[u]]$ 就会变成 $0$ 。

一切正常~

```cpp
//#define LawrenceSivan

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define INF 0x3f3f3f3f
#define re register

const int maxn=1e5+5;

int n,k,ans;

int head[maxn],to[maxn],nxt[maxn],cnt;

inline void add(int u,int v){
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}

int a[maxn],dis[maxn];

void dfs(int u,int f){
    for(re int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        dis[u]=max(dis[u],dis[v]+1);
    }
    if(dis[u]==k-1&&f>1&&a[u]^1){
        ans++,dis[u]=-1;
    }
}

namespace IO{
    
}

using namespace IO;

signed main() {
#ifdef LawrenceSivan
    freopen("aa.in","r", stdin);
    freopen("aa.out","w", stdout);
#endif  
    read(n,k);
    read(a[1]);
    ans+=a[1]!=1;
    for(re int i=2;i<=n;i++){
        read(a[i]);
        add(a[i],i);
    }

    dfs(1,0);

    write(ans),puts("");

    return 0;
}
```

---

## 作者：Ebola (赞：3)

### 题意

有一个n个点n条边的有向连通图，边权都是1，请你修改一些边的终点（不能修改边的起点），使得对于任何一个点，都存在一条长度为k的到达点1的路径（可以是非简单路径）

### 题解

考虑贪心

接下来为了表述方便，我们将“使得点p有一条长度为k的到达点1的路径”，称之为“搞点p”

首先想到，给定的图是一个基环内向树。容易想到，点1的出边必须要指向自己，所以一开始就先修改点1的出边，然后这个图就变成了一棵内向树，此时问题变成了：让所有点都存在一条长度不大于k的到达点1的简单路径。

那么我们建反边，然后一遍dfs得到所有点的深度（deep[1]=0），我们需要搞的点，就是深度大于k的点

考虑最深的那个点x。如果要搞到它，那么肯定要修改一个点p的出边，这个点p的条件是：深度小于等于deep[x]，大于deep[x]-k，并且位于x到根节点的路径上。那为了划算一些，我们肯定希望修改了p的出边之后，能搞到尽可能多的点，所以我们在所有满足条件的点p中，选择深度最小的那个，将它的出边指向1。然后将你选择的那个点深度设为1，并从你选择的那个点出发，往下做一遍dfs，重置子树中所有点的深度

所以我们可以每次都选择当前深度最大的点，然后按上面说的弄一遍，每弄一遍，答案就要加1

那么如何维护当前深度最大的点？

注意到深度最大的点必然是一个叶子节点，并且除非某一个节点在进行上述操作之后变成了叶子，否则那个节点是不在我们的讨论范围之内的。并且注意到一个事实：如果将每次进行操作的最深点排顺次排成一个序列，我们会发现序列中的点，它们的初始深度是递减的。那么一个简单的方法就是：将所有的点按深度从大到小排序，然后顺次枚举这些点，如果它是一个叶子，就进行上述操作，用deg[x]来表示x的入边数量，每次修改一个点的出边，要将出边原来指向的那个点的deg减去1，这样就能方便的判断某个点是不是叶子

注意到一个问题：我们修改一个点的出边，却并不能修改我们已经建好的图中的边，因为链式前向星不支持删边操作。这就会导致每次修改一个点的出边后进行dfs时，搜到一个已经不是它的子节点的点。虽然这不会影响正确性，但这会影响复杂度，极端情况下直接卡成n方。因此我们每修改一个点的出边，就对它打上done标记，以后搜的时候，一旦碰到有done标记的点，就直接返回。这样就保证了所有点只会被搜到一次，复杂度是O(n)的

假如你像我一样懒，不想定义sort的cmp函数，就直接三行桶排的话，那最终复杂度就是O(n)的。如果你用了sort，那你的复杂度是O(n log n)

然后本人因为热爱卡常，下面的代码里面有一个fread，所以代码看上去比较长……

```cpp
#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}

const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],n,K,sum=0;
int fa[N],deg[N],dep[N];
int c[N],id[N];
bool done[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	if(done[u]) return;
	for(int t=h[u];t;t=e[t].next)
	{
		dep[e[t].to]=dep[u]+1;
		dfs(e[t].to);
	}
}

int main()
{
	n=read();K=read();
	for(int i=1;i<=n;i++) fa[i]=read();
	for(int i=2;i<=n;i++)
	{
		add_edge(fa[i],i);//反向建图
		deg[fa[i]]++;
	}
	dfs(1);
	for(int i=1;i<=n;i++) c[dep[i]]++;
	for(int i=1;i<=n;i++) c[i]+=c[i-1];
	for(int i=1;i<=n;i++) id[c[dep[i]]--]=i;//三行桶排
	reverse(id+1,id+1+n);//上面排序是按深度从小到大的，现在要反转过来
	int ans=(fa[1]!=1);//如果fa[1]一开始不等于1，就要修改一次，让它等于1
	for(int i=1;i<=n;i++)
	{
		int x=id[i];
		if(deg[x]==0&&dep[x]>K)
		{
			int u=x;
			for(int j=1;j<K;j++) u=fa[u];
			ans++;dep[u]=1;dfs(u);
			deg[fa[u]]--;
			done[u]=1;//特别注意必须要有done标记
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：听取MLE声一片 (赞：3)

要注意的一点是题目中给定的是一棵基环树。

我们设节点 $1$ 为根节点。显然根节点要有一个自环，才能保证所有节点都能在 $k$ 步之内到达根节点。所以要直接把根节点连向自己，之前的边舍弃。如果初始时根节点是和自己连接，答案设为 $0$，否则设为 $1$。

然后我们就会获得一棵**树**。我们从根节点开始 dfs，对于当前节点，它的距离明显是所有儿子节点距离的最大值再加上一。如果这个值恰好比 $k$ 小一，说明这个点必须和根节点相连，然后此时距离要设为 $-1$，因为后面还要加，同时答案加一。

我们要从叶子往上传信息，而不是从根节点直接往下传，因为直接往下传可能会多走几步。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
int n,m,ans,dis[N],f[N];
vector<int> a[N];
void dfs(int u,int fa){
   for(int i=0;i<(int)a[u].size();i++){
        int v=a[u][i];
        dfs(v,u);
        dis[u]=max(dis[u],dis[v]+1);
    }
    if(dis[u]==m-1&&fa!=0&&f[u]!=1){
        ans++;
		dis[u]=-1;
    }
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		int j=read();
		f[i]=j;
		if(i==1){
			if(j==1)
				ans=0;
			else ans=1;
			continue;
		}
		a[j].push_back(i);
	}
	dfs(1,0);
	printf("%d",ans);
	return 0;
}

```

---

## 作者：PosVII (赞：2)

**前言**

------------

思维水题越做越少……

**思路**

------------

因为要传送 $k$ 次恰好到 $1$ 号城市，那么一定是 $1$ 号城市自环最优。同样的，数据范围明显说明存在自环。

将其视作一棵以 $1$ 为根的树，不难发现任意一点只要其离 $1$ 距离够近或者其祖先曾将边连向 $1$ 就不需改变。

最后特判 $1$ 是否自环。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,x,k,ans;
vector<int> to[MAXN];
bool vis[MAXN];
int dfs(int p,int dep) {
	int dth=dep;
	for(int i=to[p].size()-1;i>=0;--i) {
		dth=max(dth,dfs(to[p][i],dep+1));
	}
	if(dth-dep==k-1) {
		if(!vis[p]) {
			vis[p]=1;
			++ans;
		}
		return dep-1;
	}
	return dth;
}
int main() {
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;++i) {
		scanf("%d",&x);
		if(i!=1) to[x].push_back(i);
		if(x==1) vis[i]=1;
	}
	dfs(1,1);
	if(!vis[1]) ++ans;
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：邈云汉 (赞：1)

对每个点向从它能传送到的点连一条有向边，一共 $n$ 个点 $n$ 条边，构成一棵 **基环树**。（注意，这个东西在联赛考纲中哦）。

那个唯一的环是我们研究的重点。首先，有一条非常重要的解题性质（个人感觉好多联赛的题目的核心也就是性质分析），那就是环只能是 $1$ 的自环。证明一下也很容易，如果 $1$ 不在环上，那么从 $1$ 传送到的那个点就永远走不到 $1$，与题意矛盾，而如果环上还含有其它点，假设某一点能在 $k$ 步走到 $1$，则它在环上的前一个点和后一个点都不可能在 $k$ 步走到 $1$，因为环上的点不可能走出环（不然一个点就有多条出边了）。

然后图就转换为了一棵以 $1$ 为根的树（那个自环在程序实现的时候可以不管它）。显然，如果以某一个点（$1$ 除外）为根的子树中最深的点的深度等于 $k-1$，那么该点就必须与 $1$ 相连。这么做是最优的，因为在那种情况下，至少要动一个点，而我们只动了一个点。当然，做完之后，要把这个点向上返回的数值设为 $0$，形象地，这棵子树被砍掉了。

如果还是看不懂，详见代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,k,a[N],vis[N],ans,f[N];
int ver[N],Next[N],head[N],tot;
void add(int u,int v)
{
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot;
}
int dfs(int x)
{
	vis[x]=1;
	int res=1;
	for(int i=head[x];i;i=Next[i])
	{
		if(vis[ver[i]])continue;
		f[ver[i]]=x;
		res=max(res,dfs(ver[i])+1);
	}
	if(res>=k&&f[x]!=1&&x!=1)ans++,res=0;
	return res;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=2;i<=n;i++)add(a[i],i),add(i,a[i]);
	if(a[1]!=1)ans++;
	dfs(1);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Aw顿顿 (赞：1)

允许有自环这件事情的妙处在于，我可以大大弱化构造所需的条件。由于终点在 $1$，那我只需要构造一个在 $1$ 处的自环 $1\to 1$，之后就可以保证首都自己可以兜圈子 $k$ 遍。

而这也带来了好处：其他的城市只要在 $k$ 步及以内能到达 $1$，那接下来他们就只需要兜圈子即可，因此这样的构造是合法的。考虑对于每一个节点 $x$，如果它的子树中存在最深的点与它的距离为 $k-1$，那就不得不在 $x$ 与 $1$ 中连一条边了。

自下而上的处理是有效的，见代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,k,res,t[N];
int cnt,h[N];
struct edge{int v,w,nxt;}e[N];
void add(int u,int v){e[++cnt].v=v;e[cnt].nxt=h[u];h[u]=cnt;}
int dfs(int u,int dep){
	int mx=dep;
	for(int i=h[u];i;i=e[i].nxt)
		mx=max(mx,dfs(e[i].v,dep+1));
	if(mx-dep==k-1){
		if(t[u]!=1)t[u]=1,res++;
		return dep-1;
	}return mx;
}signed main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&t[i]);
		if(i!=1)add(t[i],i);
	}dfs(1,1);
	if(t[1]!=1)res++;//1号点自环
	printf("%d\n",res);
	return 0;
}
```

总结：有构造的感觉，对于方案怎么方便怎么来，特殊性质合理利用。

---

## 作者：ez_lcw (赞：1)

先不看 $1$ 号点连出去的那条边，那么剩下来的就是一棵内向树。

对于这棵树来说，发现那些与 $1$ 号点的距离小于 $k$ 的点来说，他们肯定需要一条 $1$ 号点的自环来满足条件，否则肯定有一些点无论怎么改都到达不了 $1$ 号点。

得到了这个结论，剩下的就很好搞了，我们从下往上贪心：一旦遇到以当前点 $u$ 为根的子树的最深的未被满足的点到自己的距离等于 $k-1$，我们就可以让 $u$ 向 $1$ 连一条边，然后这棵子树的点都能被满足。

至于过程一遍 $\texttt{dfs}$ 就好了，然后也有一些细节，详见代码：

```cpp
#include<bits/stdc++.h>

#define N 100010

using namespace std;

int n,k,ans,a[N];
int cnt,head[N],nxt[N],to[N];

void adde(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

int dfs(int u,int dep)
{
	int maxdep=dep;//维护以点 $u$ 为根的子树的最深的未被满足的点的深度
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		maxdep=max(maxdep,dfs(v,dep+1));
	}
	if(maxdep-dep==k-1)//如果最深点到当前点的距离为k
	{
		if(a[u]!=1)//注意如果原来有了连向1的边就不用统计进ans了
		{
			a[u]=1;
			ans++;
		}
		return dep-1;
	}
	return maxdep;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(i!=1) adde(a[i],i);
	}
	dfs(1,1);
	if(a[1]!=1) ans++;//1号点自环
	printf("%d\n",ans);
	return 0;
}
/*
6 2
2 1 1 3 3 4
*/
```

---

## 作者：1saunoya (赞：1)

考虑贪心。


他没说可以有自环，于是就可以有自环。

$1-1$。

然后我们只需要使得任何一个点到 $1$ **小于等于** $k$ 就行了。

直接贪心即可。


```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rp(i,y) for(int i=1;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define pr(i,y) for(int i=y;i>=1;i--)
#define sz(v) (int)v.size()
using namespace std;
const int SIZE=1<<26;
char gc[SIZE],*pgc=gc;
char pc[SIZE],*ppc=pc;
clock_t clk=clock();
struct flusher{
	flusher(){
#ifdef WHX_TXDY
		freopen("fuck.in","r",stdin);
#endif
		fread(gc,true,SIZE,stdin);
	}
	~flusher(){
		fwrite(pc,true,ppc-pc,stdout);
#ifdef WHX_TXDY
		std::cerr<<"TIME:"<<(clock()-clk)/1000.<<"s\n";
#endif
	}
}Flusher;
int _Neg=0;
template<class T>
void rd(T&x){
	x=_Neg=0;
	while(!isdigit(*pgc)){
		if((*pgc++)=='-'){
			_Neg=1;
		}
	}
	while(isdigit(*pgc)){
		x=x*10+*pgc++-48;
	}
	if(_Neg){
		x=-x;
	}
}
int _Stk[233],_Top=0;
template<class T>
void pt(T x,char c='\n'){
	if(x<0){
		*ppc++='-';
		x=-x;
	}
	do{
		_Stk[++_Top]=x%10;
		x/=10;
	}while(x);
	while(_Top){
		*ppc++=_Stk[_Top--]+48;
	}
	*ppc++=c;
}
void pts(const string&str){
	int len=sz(str);
	rep(i,0,len-1){
		*ppc++=str[i];
	}
	*ppc++='\n';
}
template<class T>
void cmax(T&x,const T&y){
	x=(x>y)?x:y;
}
template<class T>
void cmin(T&x,const T&y){
	x=(x<y)?x:y;
}
int n, k;
const int N = 1e5 + 1;
int fa[N];
int ans = 0;
vector<unordered_set<int> >g;
int dfs(int u,int d){
	int mxd = d;
	for (auto v : g[u]){
		cmax(mxd, dfs(v, d + 1));
	}
	if (mxd - d == k - 1) {
		if (fa[u] != 1) {
			fa[u] = 1;
			++ans;
		}
		return d - 1;
	} else {
		return mxd;
	}
}
int main() {
	rd(n);
	rd(k);
	g.resize(n + 1);
	rp(i,n){
		rd(fa[i]);
		if(i!=1){
			g[fa[i]].insert(i);
		}
	}
//	rp(i,n){
//		pt(fa[i], ' ');
//	} pts("");
	dfs(1,1);
	if(fa[1]!=1){
		++ans;
	}
	pt(ans);
	return 0;
}
```

---

## 作者：win114514 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Al-lA/p/17641502.html)。

简单贪心。

### 思路

可以发现一号节点必然连向自己。

由于题目中保证了最初每个点都可以到达一号节点。

那么我们发现改完一后，原图变成了一棵十分优美的树。

考虑在树上进行贪心。

我们贪心的从叶子结点往上走。

知道第 $k$ 个若还没要到 $1$，就直接连向一号节点。

这个贪心也比较容易理解。

实现也很简单。

### Code

[AC记录](https://atcoder.jp/contests/agc004/submissions/44685530)。

---

## 作者：Lyccrius (赞：0)

$1$ 号点自环，其它点贪心，不用多说。

讲一下为什么要从下往上贪心而从上往下是错的。

考虑这样一组数据：

```cpp
9 3
8 2
4 1 2 3 1 2 3 4
```

可以在[这里](https://csacademy.com/app/graph_editor/)生成图像查看。

从上往下贪心：
* $1$ 号点指向 $4$
* $8$ 号点距离为 $4$
* $9$ 号点距离为 $4$

答案为 $3$。

从下往上贪心：
* $1$ 号点指向 $4$
* $3$ 号点子树深度为 $2 = k - 1$

答案为 $2$。

为什么呢？

考虑一种情况，存在一条链上需要删除一条边，且删除该链上的任意一条边对于该链的答案影响都是等价的。

考虑删除一条边的贡献，可以对该边指向的（深度较低的）点子树内所有点产生影响。

那么既然这条链上必须要删除一条边，为了删除的总边数最小，应选择该边贡献最大化。

故应尽可能删除深度较低的边。

---

## 作者：little_cindy (赞：0)

### 题意简述
一张图，有 $n$ 个点，每一个点都有一个以它为起点的有向边，终点给定。求最少修改几条边，使得每个点到 $1$ 存在一条长度为 $k$ 的路径。

## 思路
要求每个点都能到达 $1$，显然和以 $1$ 为起点的边无关。那么剩余 $n-1$ 条边。都可达说明连通，那么除了以 $1$ 为起点的边必定是一棵树。一棵树上加一条边要使任何一个节点到根节点的距离为 $k$，那么这条边一定是一个自环，剩下的只要满足树的深度小于等于 $k$ 且都能到达 $1$ 即可。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
/*快读模板*/
template <typename T> inline void read(T& x) {
    x=0;T f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=x*f;
    return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
    read(x);
    read(arg...);
}
template <typename T>inline void write(T x) {
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
    write(x);
    putchar(' ');
    write(arg...);
}
/*正文*/
const int maxn=1e5+5;
int n,k,ans;
int tot,head[maxn],a[maxn];
struct node{
	int to,nxt;
}edge[maxn<<1];
void add(int x,int y){
    tot++;
	edge[tot].to=y;
	edge[tot].nxt=head[x];
    head[x]=tot;
    return;
}
int dfs(int cur,int d){
	int maxi=d;
	for(int i=head[cur];i;i=edge[i].nxt){
		maxi=max(maxi,dfs(edge[i].to,d+1));
    }
	if(a[cur]!=1&&maxi-d==k-1){
        ++ans;
        return 0;
    }
	return maxi;
}
int main(){
    read(n,k);
	for(int i=1;i<=n;i++){
        read(a[i]);
    }
	if(a[1]!=1){//不是自环，设为自环
        ans=a[1]=1;
    }
	for(int i=2;i<=n;i++){
        add(a[i],i);
    }
	dfs(1,0);//建一棵树
    write(ans);
    return 0;
}
```

---

