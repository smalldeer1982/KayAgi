# [ABC345F] Many Lamps

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc345/tasks/abc345_f

頂点に $ 1 $ から $ N $ の、辺に $ 1 $ から $ M $ の番号がついた $ N $ 頂点 $ M $ 辺の単純グラフがあります。辺 $ i $ は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。  
 各頂点にはランプが $ 1 $ 個ずつ載っています。はじめ、全てのランプは消えています。

以下の操作を $ 0 $ 回以上 $ M $ 回以下行うことで、ランプがちょうど $ K $ 個ついた状態にできるかどうかを判定してください。

- 辺を $ 1 $ 本選ぶ。辺の両端点を $ u $, $ v $ とする。$ u,\ v $ に載っているランプの状態を反転させる。つまり、ランプがついていたら消して、消えていたらつける。
 
また、ちょうど $ K $ 個のランプがついた状態にすることが可能な場合は、そのような操作の手順を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min\left(\ 2\ \times\ 10^5,\ \frac{N(N-1)}{2}\ \right) $
- $ 0\ \leq\ K\ \leq\ N $
- $ 1\ \leq\ u_i\ \lt\ v_i\ \leq\ N $
- 入力で与えられるグラフは単純
- 入力される値は全て整数
 
### Sample Explanation 1

出力例に従って操作を行うと次のようになります。 - 辺 $ 3 $ を選ぶ。頂点 $ 2 $ と頂点 $ 4 $ に載っているランプをつける。 - 辺 $ 4 $ を選ぶ。頂点 $ 3 $ と頂点 $ 5 $ に載っているランプをつける。 - 辺 $ 5 $ を選ぶ。頂点 $ 1 $ に載っているランプをつけて、頂点 $ 5 $ に載っているランプを消す。 操作を全て終了した時点で頂点 $ 1,2,3,4 $ に載っているランプがついています。よってこの操作の手順は条件を満たしています。 条件を満たす操作の手順としては他に $ X\ =\ 4,\ (e_1,e_2,e_3,e_4)\ =\ (3,4,3,1) $ などが挙げられます。(同じ辺を $ 2 $ 回以上選んでもよいです。)

## 样例 #1

### 输入

```
5 5 4
1 2
1 3
2 4
3 5
1 5```

### 输出

```
Yes
3
3 4 5```

## 样例 #2

### 输入

```
5 5 5
1 2
1 3
2 4
3 5
1 5```

### 输出

```
No```

## 样例 #3

### 输入

```
10 10 6
2 5
2 6
3 5
3 8
4 6
4 8
5 9
6 7
6 10
7 9```

### 输出

```
Yes
3
10 9 6```

# 题解

## 作者：KingPowers (赞：10)

本文参考官方题解。

先摆上来几个结论：

- 最后点亮的灯一定是偶数个。

- 一个连通块内一定存在一种操作方式，使得点亮的灯数为不超过连通块点数的最大偶数。

对于第一个结论，考虑我们每次操作对灯数的影响：

- 两个灭的点亮，总数加 $2$。

- 一个关掉一个点亮，总数不变。

- 两个亮的关掉，总数减 $2$。

不难发现变化量全部为偶数。

对于第二个结论，我们直接给出一种构造：

- 对于一张连通图 $G$，任取其一棵生成树 $T$。

- 重复以下操作直到 $T$ 只剩下一个结点：

  - 选择 $T$ 中的任意一个叶子结点 $v$，并考虑连接 $v$ 与其父亲的边 $e$。
  
  - 如果 $v$ 没被点亮，对边 $e$ 进行操作。
  
  - 在 $T$ 中删除 $v$ 和 $e$。

不难发现，按照此构造方式，最终点亮的灯数一定为不超过连通块点数的最大偶数。

因此，我们只需要对每个连通块都按照上面给出的构造方式去点灯，就能得到最大的点亮数，如果最大的数量小于 $k$ 或者 $k$ 是奇数答案就是 `No`，否则直接输出答案即可。

上面的构造方式可以用 dfs 来简单实现。

[提交记录](https://atcoder.jp/contests/abc345/submissions/51365287)

---

## 作者：EuphoricStar (赞：5)

首先 $K$ 为奇数时无解。

然后图的每个连通块显然互相独立，分别考虑。

每个连通块随便求一棵生成树，自底向上操作。如果当前的 $K$ 有剩余，为了钦定 $u$ 是亮的，可能需要翻转 $u \to fa_u$ 的边。

这样操作一遍如果最后根不是亮的，说明连通块大小为奇数，我们显然只能做到让偶数盏灯亮，所以不用管它。

最后做完每个连通块后若 $K$ 还有剩余就无解。

求生成树我偷懒用了并查集，所以复杂度带个 $\log$。

[code](https://atcoder.jp/contests/abc345/submissions/51284780)

---

## 作者：Light_Tea (赞：5)

[题目](https://www.luogu.com.cn/problem/AT_abc345_f)

首先，在任何时刻，开着的灯都必定是偶数个，证明即考虑一次操作会让开着的灯的个数 +2，+0，-2。

那么 $k$ 为奇数则无解，偶数则可以尝试构造。

考虑并猜测将原图的一棵生成树提出来，~~猜测点数为偶的树必定有全都亮起的构造方案~~。

对于这棵生成树而言，我们先把所有树边都点亮，那么度数为奇的点将会亮起，度数为偶的点将会不亮，如果此时亮起的灯还不够，那么考虑将度数为偶的点两两配对，（如果亮起的灯够了就将奇度点两两配对即可），将他们路径上的树边全都再操作一遍（显然操作两遍等于没操作），这样路径中的点由于被两边的边改了两次，所以都没变，只有配对的两个点变了，达成目的。实际操作的时候树上打标记即可，两点 lca 到根的路径上每条边都会被操作两遍，所以事实上没有影响。

注意图并不联通，需要对每个联通块单独处理，并且点数为 $n$ 的连通图，比如 $n=7$，一定有点亮 $6$ 个的构造方案，但图不联通就不一定能了，计算的时候要判断一下能否找到足够的修改点，因为修改点是要在一个联通块里并且成对的。

![](https://cdn.luogu.com.cn/upload/image_hosting/fbqy5hzs.png)

比如这样，偶度点有三个，但不能找到一对偶度点点亮。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,m,k,bel[N],siz[N];
vector <int> g[N];
int Find(int x){return (bel[x]==x)?(x):(bel[x]=Find(bel[x]));}
bool Merge(int x,int y){
    int fx=Find(x), fy=Find(y); //if(siz[fx]>siz[fy]) swap(fx,fy);
    return (fx==fy)?(false):(bel[fx]=fy, true);
}
struct Edge{
    int v,id,nxt;
}e[N<<1];
int head[N],cnt_e=1;
void Add_Edge(int u,int v,int id){
    e[++cnt_e]={v,id,head[u]}, head[u]=cnt_e; e[++cnt_e]={u,id,head[v]}, head[v]=cnt_e;
}
bool ans[N],deg[N],tag[N];
void Dfs(int u,int fa){
    for(int i=head[u],v; v=e[i].v,i; i=e[i].nxt){
        if(v==fa) continue;
        Dfs(v,u);
        if(tag[v]) ans[e[i].id]^=1, tag[u]^=1;
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) bel[i]=i;
    for(int i=1;i<=m;i++){
        int u,v; scanf("%d%d",&u,&v);
        if(Merge(u,v)) Add_Edge(u,v,i), ans[i]=1, deg[u]^=1, deg[v]^=1;
    }
    if(k&1) return puts("No"), 0;
    for(int i=1;i<=n;i++) g[bel[i]=Find(i)].emplace_back(i);
    int cnt0=0, cnt1=0;
    for(int i=1;i<=n;i++) (deg[i]==1)?(cnt1++):(cnt0++);
    // printf("debug %d %d\n",cnt0,cnt1);
    if(cnt1>k){
        for(int i=1;i<=n;i++){
            if(bel[i]!=i) continue;
            int cnt=0;
            for(auto &x:g[i]) if(deg[x]==1) cnt++;
            cnt-=cnt&1; cnt=min(cnt,cnt1-k); cnt1-=cnt;
            for(auto &x:g[i]) if(deg[x]==1&&cnt) tag[x]=1, cnt--;
        }
        if(cnt1>k) return puts("No"), 0;
    }else{
        for(int i=1;i<=n;i++){
            if(bel[i]!=i) continue;
            int cnt=0;
            for(auto &x:g[i]) if(deg[x]==0) cnt++;
            cnt-=cnt&1; cnt=min(cnt,k-cnt1); k-=cnt;
            for(auto &x:g[i]) if(deg[x]==0&&cnt) tag[x]=1, cnt--;
        }
        if(k>cnt1) return puts("No"), 0;
    }
    for(int i=1;i<=n;i++) if(bel[i]==i) Dfs(i,0);
    int cnt_ans=0;
    for(int i=1;i<=m;i++) cnt_ans+=ans[i];
    printf("Yes\n%d\n",cnt_ans);
    for(int i=1;i<=m;i++) if(ans[i]) printf("%d ",i);
    return 0;
}
```

撒花

---

## 作者：Limie (赞：3)

考场上磕这题没磕出来，自闭了（

容易发现一次操作不会改变亮灯数量的奇偶性，所以只有在 $K$ 为偶数时才可能有解。

注意到操作 $(u,v)$ 和 $(v,w)$ 等价于直接操作 $(u,w)$。

所以对于一个大小为 $n$ 的连通块，最多有 $2 \left [ \frac{n}{2} \right ]$ 个灯亮。

于是你对于每个连通块求出最大总和，如果 $K$ 大于这个，那就没戏了。

发现不会构造。

先考虑如果要求亮的灯最多该怎么做，贪心一下可以得到这样的策略。

1. 对于一个点 $u$，先递归操作所有未遍历到的相邻顶点 $v$。

2. 对于每个 $v$，如果没亮就操作 $(u,v)$ 边。

如何证明这种操作方法可以使亮灯最多呢，发现如果将递归过程看成一颗生成树 $T$ 的遍历，则有：

1. 遍历完整棵树后除根节点外的所有点均亮着。

2. 根节点是否亮着取决于整棵树的大小 $n$，具体点说，$n$ 为奇数时，根节点不亮，否则亮。

~~可自行通过数学归纳法证明。~~

发现只要使亮灯数始终不超过 $K$ 即可得到操作序列。

```cpp
#include<bits/stdc++.h>
namespace Limie{
	#define x first
	#define y second
	using namespace std;
	typedef long long LL;
	typedef pair<int,int> PII;
	typedef unsigned long long ULL;
	typedef long double LD;
}
using namespace Limie;
int n,m,k,c;
vector<PII> g[200010];
bool st[200010],h[200010];
vector<int> ans;
void dfs(int u)
{
	st[u]=1;
	for(PII x:g[u]){
		int v=x.x,id=x.y;
		if(st[v])continue;
		dfs(v);
		if(c>=k)return;
		if(!h[v]){
			h[v]=1,c++;
			if(h[u])h[u]=0,c--;else h[u]=1,c++;
			ans.push_back(id);
			if(c>=k)return;
		}
	}
}
int main()
{
	int i;
	cin>>n>>m>>k;
	if(k%2==1)return puts("No"),0;
	for(i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		g[a].push_back({b,i}),g[b].push_back({a,i});
	}
	for(i=1;i<=n;i++)
		if(!st[i])dfs(i);
		
	if(c<k)return puts("No"),0;
	cout<<"Yes\n";
	cout<<ans.size()<<'\n';
	for(int x:ans)cout<<x<<' ';
}
```

---

## 作者：YXD123456789 (赞：2)

赛时没有看到 F，赛后和 dalao（[迭](https://www.luogu.com.cn/user/269085)）讨论了一会觉得思路对了。第二天写过的。

## 思路：
 
   毕竟是个可能无解的题，我们直接~~总司令（ bushi ）~~ 判断一下什么时候可能会无解，我们对于一条边相邻两点的情况讨论一共有三种情况：
	
   - 两点都是关闭的状态，点后会变成两点都是打开的状态，那么开的灯数就会 $ + 2 $。
    
  - 两点都是打开的状态，点后会变成两点都是关闭的状态，那么开的灯数就会 $ - 2 $。
    
  - 两点一个打开一个关闭，点后依然是一个打开，一个关闭，那么开的灯数不会发生改变。

并且初始状态开的灯数为 $ 0 $，所以我们的 $ k $ 为奇数的时候一定是不可行的。

   我们考虑一个图如果将其分为几个连通块时，这几个连通块之间实际上是互不影响的，所以我们只需要对于每一个连通块进行考虑即可。
	
   那么我们会发现这个通过将连通块选取一棵生成树，每一个结点只由连向它的父亲的边与连向它的儿子的边所影响，同时最底层的叶子结点只由它连向父亲的边所影响，所以我们点亮这个点就用这个点连向父亲结点的边所改变，如果这个点是打开的，那么就不需要将这条连向父亲的边选取，反之，则选取。
   
   由此，我们会发现只有根节点的点亮状态是无法通过选取连向父亲的边所改变的。这样我们便可以给出一个连通块中能选取到最大点数与如何选取到特定点数的构造方案。

   最后我们只需要将一个个连通块通过上述构造，并每次改变 $ k $ 值，直到 $ k = 0 $ 时，输出方案。

[code](https://atcoder.jp/contests/abc345/submissions/51488950)

---

## 作者：Creeper_l (赞：2)

> 题意：给定一个 $n$ 个点 $m$ 条边的无向图，每个点的初始颜色为 $0$。一次操作是将一条边的两个端点的颜色翻转。求是否能通过若干次操作使得最终有 $k$ 个颜色为 $1$ 的点。

首先考虑什么情况下无解。会发现每一次操作，颜色为 $1$ 的点的数量变化一定是 $[0,+2,-2]$ 中的一种，所以任何时候都一定是偶数。于是当 $k$ 为奇数的时候，一定无解。

对于 $k$ 不是奇数的情况，我们对于一个连通块进行考虑（可能有多个连通块，将贡献相加即可）。假设这个连通块有 $x$ 个点，我们先求出这个连通块的一颗生成树，那么有一个结论：一定有一种操作方式使得这颗生成树中最终有 $\lfloor \frac{x}{2} \rfloor \times 2$ 个颜色为 $1$ 的点。因为对于树上的一个点 $u$，假设它下面的点的颜色已经全部为 $1$ 了，那么一定通过控制 $u \to fa_u$ 这条边的操作与否使得 $u$ 这个点变为 $1$，所以除了根节点之外的所有点都一定能变为 $1$。而根节点能否变为 $1$ 取决于 $x$ 的奇偶性。

所以如果 $\sum \lfloor \frac{x}{2} \rfloor \times 2 \ge k$ 的话，最终有解。对于每一个连通块可以通过一次 $\text{dfs}$ 遍历得到具体的方案。否则无解。

---

## 作者：Kreado (赞：2)

[题目传送门](https://atcoder.jp/contests/abc345/tasks/abc345_f)。

对于每个边的翻转，它的两个点有这 $4$ 种可能：

- $(0,0)$ 翻转之后贡献加 $2$。
- $(0,1)$ 翻转之后贡献不变。 
- $(1,0)$ 翻转之后贡献不变。
- $(1,1)$ 翻转之后贡献减 $2$。

那么当 $k$ 为奇数的时候显然无解。

容易证明，图的答案和其生成树的答案是一样的，不妨将这张图转换成其生成树，对于树上的每个边，若其两个点的权值均为 $0$，对该边进行一次翻转操作，直到该树不存在 $(0,0)$ 权值，若操作过程中已经满足当前树的总权值为 $k$，输出当前方案，否则将权值为 $0$ 的点不断翻到其祖先处，直到它父亲为 $0$，将其翻转至 $(1,1)$，不断重复该操作，直到总权值为 $k$，停止操作。

树上前缀异或和即可，时间复杂度 $O((n+m)\log n)$。

---

## 作者：FL_sleake (赞：2)

### 解题思路

首先 $k$ 是奇数直接输出 `No`，因为无论如何操作不会改变亮着的灯的奇偶性。然后对于每个连通块其实我们可以分开考虑。对于每个连通块，强制把它看成一棵树。由于是连通块，所以钦定任何一个点是根然后进行 dfs 即可达到遍历树的效果。

连通块中点亮灯的方案是什么呢？由于我们将它看成一棵树，所以考虑从叶子节点往上点亮，直到点亮的灯数等于 $k$。当然如果始终无法等于 $k$ 则输出 `No`。通过这种方法点灯，只有根节点是否点亮不确定（其实取决于点数奇偶性，可以自己手推一下），其余点必定都可以点亮。这也是我们能点亮的灯的最大值。

~~其实思路别的题解讲的都挺清楚的，不过我没看到对我胃口的代码，所以来放一个算是比较简洁的代码吧。~~

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,vis[200010],flg[200010]={0},cnt=0;//flg 记录每个点是否点亮，cnt记录点亮点的个数
vector<int> G[200010],ans;
map<int,map<int,int> > id;//由于输出方案，所以记录每条边的编号
void dfs(int u){
	if(vis[u]) return;
	vis[u]=1;
	for(int v:G[u]){
		if(vis[v]) continue;
		dfs(v);//先跑到叶子节点，再回来点亮前面的点
		if(!flg[v]){
			if(!flg[u]&&cnt<k) cnt+=2,flg[u]=flg[v]=1,ans.push_back(id[u][v]);
			else if(flg[u]) flg[u]=0,flg[v]=1,ans.push_back(id[u][v]);
		}
	}
}
signed main(){
	cin>>n>>m>>k;
	if(k==0) return cout<<"Yes"<<endl<<"0"<<endl,0;
	if(k&1) return cout<<"No"<<endl,0;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		id[u][v]=id[v][u]=i;
	}
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
	if(cnt!=k) return cout<<"No"<<endl,0;
	cout<<"Yes"<<endl;
	cout<<ans.size()<<endl;
	for(int x:ans) cout<<x<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：MrPython (赞：1)

什么搞笑比赛，会 F 不会 DE。

---
贪就可以。

深搜到某个节点枚举它接的边时，如果自己没有点亮就激活这条边，总点亮的灯泡数增加 $2$。如果所有边都遍历了自己还是灭着的，就激活一次和父亲连的边，点亮自己熄灭父亲。由于父亲计入自己时一定点亮自己了，因此父亲必定是亮着的状态，因此点亮的灯泡数量不会变化。对每个连通块都搜一次，若剩 $1$ 个灯泡没有点亮输出 `No`（显然一次操作只有三种结果：灯泡数 $+2$，灯泡数不变，灯泡数 $-2$）。若点亮数量达到条件就按照记录下来的历史输出就好。
```
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
struct node{size_t next,id;};
void dfs(size_t p,size_t fa,size_t faid,size_t& k,vector<bool>& vis,vector<bool>& colored,vector<vector<node>> const& mp,vector<size_t>& ans){
    if (k==1){cout<<"No";exit(0);}
    if (k==0){
        cout<<"Yes\n"<<ans.size()<<'\n';
        for (size_t i:ans) cout<<i+1<<' ';
        exit(0);
    }
    vis[p]=true;
    for (node i:mp[p]) if (!vis[i.next]){
        if (!colored[p]){
            ans.push_back(i.id);
            if (!colored[i.next]) k-=2;
            colored[p]=colored[i.next]=true;
        }
        dfs(i.next,p,i.id,k,vis,colored,mp,ans);
    }
    if (!colored[p]&&~fa){
        ans.push_back(faid);
        colored[fa]=false;
    }
}
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m,k;cin>>n>>m>>k;
    vector<vector<node>> mp(n);
    for (size_t i=0;i<m;++i){
        size_t a,b;cin>>a>>b;--a,--b;
        mp[a].push_back({b,i}),mp[b].push_back({a,i});
    }
    vector<bool> vis(n),colored(n);
    vector<size_t> ans;
    for (size_t i=0;i<n;++i) if (!vis[i]) dfs(i,~0,~0,k,vis,colored,mp,ans);
    cout<<"No";
    return 0;
}
```

---

## 作者：5d0b799a9524b36a (赞：1)

感觉这场难度比之前的要高一点

## 题意

给定一个 $N$ 个点 $M$ 条边的图，初始时每个点上的灯都是“暗”的，你可以选中一条边并 switch 这条边连两个点的状态（0 变 1,1 变 0），求能否达到最后正好有 $K$ 个点上的灯亮着。

## 题解

我们考虑一条边的改变会发生什么
- 如果一条边 $(u,v)$ 中 $u,v$ 状态相同，那么 switch 后最终的亮灯数会 $±2$。
- 如果一条边 $(u,v)$ 中 $u,v$ 状态不同，那么 switch 后最终的亮灯数不变。

要么 $+2$，要么不变，所以亮灯数量一定是偶数个。那么如果 $k \neq 2m$ 时就可以直接 No 了。

显然一条边只能改变一个连通块内的亮灯，记其大小 $n$，考虑最多能够亮多少个，不难发现是 $2\left\lfloor\dfrac{n}{2}\right\rfloor$（即不超过 $n$ 的最大偶数），证明很简单，对于任意两个 $u,v$ 不亮，我们可以取一条他们之间的通路，依次 switch 这条路径上的所有边，发现这时 $u,v$ 都亮了，但路径上的所有点状态都不变。

对于所有连通块，我们把这个连通块内最多亮多少个算出来加起来就是 $K$ 的上界，那么我们就可以判断 Yes 和 No 了。

考虑如何求解方案，我们不妨考虑这样一个算法：

- 对于一个连通块，取出这个连通块的一棵生成树
- 在这棵树内我们任意选取一个叶子结点 $v$，并执行如下操作：
- - 如果 $v$ 已经亮了，则直接在树中删除 $v$ 以及 $(v,fa[v])$
- - 如果 $v$ 还没亮，则在树中 switch $(v,fa[v])$ 后删除 $v$ 以及 $(v,fa[v])$
- 重复上一步操作直到亮灯达到 $K$ 个。

显然一条边只会至多 switch 一次，且这个方法一定能自下而上地把点变成黑色，因此可以满足题目要求。

那么这题我们就解决了。

## Code

```cpp
int cur = 0;
for (int i = 1; i <= n; i++) if (!vst[i]) {
  while (!q.empty()) q.pop();
  DFS(i);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (fa[u] == 0) break;
    if (!lit[u]) {
      lit[u] ^= 1, lit[fa[u]] ^= 1;
      if (fa[u]) op.emplace_back(x(u, fa[u]));
      if (lit[u] == lit[fa[u]]) cur += 2;
    }
    --out[fa[u]];
    if (out[fa[u]] == 0 && fa[u]) q.push(fa[u]);
    if (cur == k) {
      print();
      return 0;
    }
  }
}
```

---

## 作者：subcrip (赞：0)

首先肯定是先建生成树森林。然后关于如何把树上的点全都配对（奇数的话除了某一个点），这里有一个比较无脑的办法：**直接在 DFS 序上配对相邻节点即可**。

为什么？我们可以计算一下这样做需要多少次操作：考虑 DFS 序上的相邻节点 $(u,v)$，如果二者之一是另一个的父亲，则只需翻转它们之间的边，也就是说进行一次操作；如果不是，则需要翻转它们之间路径上的所有边，而某条边在这种情况下被计入操作次数只可能是因为退出它下面的子树，这只会发生一次。所以总的操作次数不会超过 $O(m)$。

Code:

```cpp
void solve() {
    read(int, n, m, k);
    vector<pii> edges;
    unordered_map<pii, int, pair_hash> rev;
    for (int i = 0; i < m; ++i) {
        read(int, u, v);
        edges.emplace_back(u, v);
        rev[minmax(u, v)] = i;
    }

    quick_union qu(n + 1);
    adj(ch, n);
    for (auto&& [u, v] : edges) {
        if (qu.connected(u, v)) continue;
        qu.merge(u, v);
        edge(ch, u, v);
    }

    int rem = k;

    vector<int> res;

    {
        vector<int> fa(n + 1);
        vector<bool> vis(n + 1);
        vector<int> seq;
        auto dfs = [&] (auto dfs, int v, int pa) -> void {
            vis[v] = 1;
            fa[v] = pa;
            seq.emplace_back(v);
            for (auto&& u : ch[v]) {
                if (u == pa) continue;
                dfs(dfs, u, v);
            }
        };
        for (int i = 1; i <= n; ++i) {
            if (not vis[i]) {
                seq = {};
                dfs(dfs, i, 0);
                int m = seq.size();
                for (int j = 1; j < m; j += 2) {
                    if (rem <= 0) goto fi;
                    int u = seq[j - 1], v = seq[j];
                    int l = fa[v];
                    while (u != l) {
                        res.emplace_back(rev[minmax(u, fa[u])]);
                        u = fa[u];
                    }
                    while (v != l) {
                        res.emplace_back(rev[minmax(v, fa[v])]);
                        v = fa[v];
                    }
                    rem -= 2;
                }
            }
        }
    }

fi:
    if (rem != 0) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";
    cout << res.size() << '\n';
    transform(res.begin(), res.end(), res.begin(), expr(v + 1, int v));
    putvec(res);
}
```

---

## 作者：Ac_forever (赞：0)

# 题目大意
给定一张 $N$ 个点 $M$ 条边的无向图，每个点一开始都是黑色，一次操作可以选择一条边使它的两个端点颜色反转，问最后是否能剩下 $K$ 个点为白色，并构造方案。

# solution
由于一次操作要么可以增加两个白色，要么不变，所以只有当 $K$ 为偶数时才有解。

考虑对于每一个连通块构造生成树，然后用类似拓扑的方法，从叶子节点从下往上操作，凑出 $K$ 个白色。对于一个已经是白色的点，不操作。对于一个黑色的点，操作它白色数量只增不减，必然操作。

代码:
```cpp
#include<map>
#include<cstdio>
#include<cstring>
#define N 200001
using namespace std;
int n,m,k,em,e[N*2],ls[N*2],nx[N*2],in[N],fa[N],h[N*4],ans[N*4];
bool lab[N];
map<int,map<int,int>>bz;
void insert(int x,int y,int i){
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
	bz[x][y]=i;
}
void dfs(int x){
	lab[x]=1;
	for(int i=ls[x];i;i=nx[i])
		if(!lab[e[i]])in[x]++,fa[e[i]]=x,dfs(e[i]);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		insert(x,y,i);
		insert(y,x,i);
	}
	if(k%2==1){
		printf("No");
		return 0;
	}
	for(int i=1;i<=n;i++)
		if(!lab[i])dfs(i);
	int t=0,w=0;
	memset(lab,0,sizeof(lab));
	for(int i=1;i<=n;i++)
		if(in[i]==0)h[++w]=i;
	int sum=0;
	while(t<w){
		int x=h[++t];
		if(fa[x]==0)continue;
		if(sum==k){
			printf("Yes\n%d\n",ans[0]);
			for(int i=1;i<=ans[0];i++)printf("%d ",ans[i]);
			return 0;
		}
		if(lab[x]==0){
			ans[++ans[0]]=bz[x][fa[x]];
			lab[x]^=1,lab[fa[x]]^=1;
			sum+=lab[fa[x]]*2;
		}
		in[fa[x]]--;
		if(in[fa[x]]==0)h[++w]=fa[x];
	}
	if(sum==k){
		printf("Yes\n%d\n",ans[0]);
		for(int i=1;i<=ans[0];i++)printf("%d ",ans[i]);
		return 0;
	}
	printf("No");
}
```

---

## 作者：fydj (赞：0)

## 思路

如果 $K$ 是奇数，显然无解，接下来只考虑 $K$ 是偶数的情况。

这个图由一堆连通块组成，对每一个连通块单独考虑，```DFS``` 建出它的生成树，然后从深往浅构造。

```DFS``` 到点 $x$ 时，先往儿子深搜，搜完儿子以后考虑点 $x$ 和它的父亲 $f$ 的连边，如果点 $x$ 的灯是暗的，并且 $K>0$ 就选择这条树边。

看一下选择了这条树边后会发生什么。如果 $f$ 是暗的，那么选择完以后 $f$ 和 $x$ 就变成亮的，$K$ 减少二；反之 $f$ 变成暗的，$x$ 变成亮的，$K$ 不变。不管怎么样都不会让情况变劣。

就这样，一直处理到 $K=0$ 为止，然后就可以输出方案了。

为什么点 $x$ 是亮时不能选择它和 $f$ 的连边？这个时候，如果 $f$ 是亮的，$K$ 增加二；反之，$K$ 不变。不管怎么样都不会让情况变优，所以此时不应该选择这条连边。

## 代码

```cpp
const int N=400099,M=400099;
int n,m,K,x,y,fa[N]={},tof[N]={},list[M]={};
int em=1,e[M]={},ls[N]={},nx[M]={};
bool ind[M]={},on[N]={},gone[N]={};
void insert(int x,int y) { e[++em]=y,nx[em]=ls[x],ls[x]=em; e[++em]=x,nx[em]=ls[y],ls[y]=em; return ; }
void dfs(int x) {
	gone[x]=true;
	int i,y;
	for(i=ls[x],y=e[i];i;i=nx[i],y=e[i])
		if(!gone[y])
			fa[y]=x,tof[y]=i>>1,dfs(y);
	if(!fa[x]) return ;
	if(K&&!on[x]) {
		if(!on[fa[x]]) K-=2;
		ind[tof[x]]=true,on[x]^=1,on[fa[x]]^=1;
	}
	return ;
}
int main()
{
	int i;
	read(n,m,K); for(i=1;i<=m;++i) read(x,y),insert(x,y);
	if(K&1) { printf("No\n"); return 0; }
	for(i=1;i<=n;++i) if(!gone[i]) dfs(i);
	if(K) { printf("No\n"); return 0; }
	printf("Yes\n");
	for(i=1;i<=m;++i) if(ind[i]) list[++list[0]]=i;
	printf("%d\n",list[0]); for(i=1;i<=list[0];++i) printf("%d ",list[i]); printf("\n");
	return 0;
}
```

---

## 作者：CarroT1212 (赞：0)

构造题永远跟出题人对不上电波系列。

在和出题人对上电波后可以发现，如果我们将一条边数不为 $0$ 的路径上的边全部取反，那我们实际只反转了路径两端的点，中间的点全部取反了两次，没有变化。

也就是说，我们可以将图上连通的任意两个不同点取反。

然后就可以随便做了。首先 $k$ 为奇数显然无解。对于每个连通块，拉一棵生成树出来，设其大小为 $p$。接着在不超过 $k$ 的条件下随便在上面选最多 $\left\lfloor\frac{p}{2}\right\rfloor$ 对点将它们取反，显然根据上面的做法我们一定可以选出这么多点。树上差分统计一下连接这些点的路径覆盖了每条边多少次即可。最后输出覆盖次数为奇数的边。

```cpp
ll n,m,k,vis[N],cnt[N];
ll fa[N][K],dep[N],cf[N];
vector<pll> e[N],e1[N];
vector<ll> v,ans;
void dfs(ll p,ll f) {
	dep[p]=dep[f]+1,fa[p][0]=f,v.pb(p),vis[p]=1;
	for (ll i=1;i<K;i++) fa[p][i]=fa[fa[p][i-1]][i-1];
	for (pll i:e[p]) if (!vis[i.fi]) e1[p].pb(i),e1[i.fi].pb({p,i.se}),dfs(i.fi,p);
}
ll lca(ll x,ll y) {
	if (dep[x]<dep[y]) swap(x,y);
	for (ll i=K-1;~i;i--) if (dep[x]-dep[y]>=1ll<<i) x=fa[x][i];
	if (x==y) return x;
	for (ll i=K-1;~i;i--) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void dfs1(ll p,ll f) {
	for (pll i:e1[p]) if (i.fi!=f)
		dfs1(i.fi,p),cnt[i.se]=cf[i.fi],cf[p]+=cf[i.fi];
}
void mian() {
	scanf("%lld%lld%lld",&n,&m,&k);
	if (k&1) return cout<<"No",void();
	for (ll i=1,x,y;i<=m;i++) scanf("%lld%lld",&x,&y),e[x].pb({y,i}),e[y].pb({x,i});
	for (ll i=1;i<=n;i++) if (!vis[i]) {
		vector<ll>().swap(v),dfs(i,0);
		for (ll i=0;i*2+1<v.size()&&k;i++) cf[v[i*2]]++,cf[v[i*2+1]]++,cf[fa[lca(v[i*2],v[i*2+1])][0]]-=2,k-=2;
		dfs1(i,0);
	}
	if (k) cout<<"No";
	else {
		cout<<"Yes\n";
		for (ll i=1;i<=m;i++) if (cnt[i]&1) ans.pb(i);
		cout<<ans.size()<<"\n";
		for (ll i:ans) cout<<i<<" ";
	}
}
```

---

## 作者：RAYMOND_7 (赞：0)

题意简述：初始全部是白点，图上任意翻转边的端点使得恰好有 $K$ 个黑点。

---------------

依据DFS树的构造题。

通过观察发现如下性质：

- $K$ 为奇数无解。

- 若经过若干操作可达到黑点最大值为 $mx$ ，如果 $mx < K$ 无解。考虑变化的连续性即可证明。

- 其余情况均有解。

这种问题我们一般考虑在树上怎么做，显然是自下而上进行操作，策略是：尽量让儿子节点先变黑，因为父亲向上还有调整的余地。

具体的，如果儿子节点是白色的，我们就立刻进行翻转，否则不翻。

-----------------------------

那么DFS树上怎么做呢？

我们尝试忽略返祖边，发现也是正确的，理由是如果返祖边有意义，目标一定是将两个白点翻转为两个黑点，然而如果有存在祖孙关系的两个白点，也一定可以通过树上的路径进行调整使得答案更优，所以返祖边是无效的，换言之，我们可以只考虑树怎么做。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define PII pair<int,int>
#define x first
#define y second
#define For(i, l, r) for(int i = l; i <= r; i ++)
#define Rep(i, l, r) for(int i = l; i >= r; i --)

bool START;

void in(int &x)
{
    char c = getchar(); int op = 1;
    while(c > '9' || c < '0') op *= (c == '-' ? -1 : 1), c = getchar();
    for(x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0'; x *= op;
}

const int N = 2e5 + 50;

map<int, int> mp[N];
int n, m, a[N], now, K, e[N], ans;
vector<int> G[N];
bool vis[N];

void dfs(int u)
{
    if(vis[u]) return ;
    vis[u] = 1;
    for(int v : G[u])
    {
        if(vis[v]) continue;
        dfs(v);
        if(now < K) //调整过程
        {
            if(a[v]) continue;
            now -= a[u] + a[v];
            a[u] ^= 1; a[v] ^= 1;
            now += a[u] + a[v];
            e[++ ans] = mp[u][v];
        }
    }
}

bool ENDPOS = 0;
signed main()
{
    in(n); in(m); in(K);
    if(K & 1) {puts("No"); return 0;}
    For(i, 1, m)
    {
        int u, v; in(u); in(v); G[u].push_back(v); G[v].push_back(u); mp[u][v] = mp[v][u] = i;
    }
    For(i, 1, n) if(!vis[i]) dfs(i);
    if(now != K) {puts("No"); return 0;}
    puts("Yes");
    printf("%d\n", ans);
    For(i, 1, ans) printf("%d ", e[i]);puts("");
    cerr << (&ENDPOS - &START) * 1.0 / 1024 / 1024 << endl; return 0;
}

```

---

## 作者：紊莫 (赞：0)

首先，$k$ 为奇数时显然无解，因为每次操作不改变亮着的灯泡的奇偶性。

然后因为不保证图联通，所以考虑对每个联通子图分别计算贡献，我们有结论：一个大小为 $n$ 联通子图的答案至多是 $n \times \left \lfloor \dfrac{n}{2} \right \rfloor$（小于等于 $n$，最接近 $n$ 的偶数），且能取到这个范围以下的所有偶数。

为了求出方案，首先考虑比较特殊的情况，树。

我们可以直接自底向上的，依次填满每一层，具体的，我们对一个暗着的节点和他的父节点操作一次，这样可以把下面一层都填满。这样的操作显然也能得到所有合法的值。

代码比较好写，参考代码：

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
inline int rd(){
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9'){
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

typedef long long ll;
typedef pair<int, int> Pair;

const int N = 200005, M = (N << 1), inf = 1e16, mod = 1e9 + 7;
int n, m, k, val[N], us[N], f[N], siz[N], dfn[N], tot, FA[N];
vector<Pair> G[N];
void calc(int now, int fa) {
    dfn[now] = ++tot;
    if (k <= 0) return ;
    for (auto i : G[now]) {
        if (!dfn[i.first] && i.first != fa) {
            calc(i.first, now);
            if (k > 0 && !val[i.first]) {
                val[now] ^= 1, val[i.first] ^= 1;
                if (val[now] && val[i.first])
                    k -= 2;
                us[i.second] ^= 1;
            }
        }
    }
}
void solve(int now) {
    calc(now, 0);
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    if (k & 1) {
        cout << "No\n";
        return 0;
    }
    F(i, 1, m) {
        int u, v;
        cin >> u >> v;
        G[u].push_back({v, i});
        G[v].push_back({u, i});
    }
    F(i, 1, n) {
        if (!dfn[i]) {
            solve(i);
        }
    }
    if (k > 0) {
        cout << "No";
        return 0;
    }
    assert(k >= 0);
    int ANS = 0;
    F(i, 1, m) ANS += us[i];
    cout << "Yes\n" << ANS << '\n';
    F(i, 1, m) {
        if (us[i]) {
            cout << i << ' ';
        }
    }
    return 0;
}

```

---

## 作者：ollo (赞：0)

首先，我们显然不会重复操作。

然后，考虑一条边的操作会带来的贡献，显然有 $(1,1),(-1,-1),(1,-1)$ 三种，而它们的贡献均为偶数，所以只要 $k$ 为奇数一定无解。

那么考虑如何构造出一组可行解，首先考虑树的形态，我们可以从叶子往上做，当前节点为白就变，不难发现最终一定只有根会为原颜色。

考虑证明，一次操作要么是把儿子加入父亲弹出，要么是把父亲加入儿子弹出加入，贡献分别为 $0$ 和 $2$。所以黑色队列长度始终为偶数，则当且仅当树的大小为奇数时根才为原色。

不难发现图的状态平凡等价于树，只要随便拿一棵生成树即可。

 code:
 ```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int, int>

using namespace std;

const int N = 2e5 + 10, K = 250;

int n, m, k;
struct S{
	int u, v;
}e[N];
int tag[N], vis[N];
int fa[N], siz[N];
int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
vector<pii> g[N];
int stk[N], tot, ans, num;
bool light[N];

void dfs(int x, int f){
	for(pii v : g[x]){
		int y = v.first, d = v.second;
		if(y == f) continue;
		dfs(y, x);if(ans >= k) return ;
		if(light[y] == 0){stk[++tot] = d;ans++;if(!light[x])ans++;else ans--;light[x] ^= 1;light[y] ^= 1;}
	}
}

void S(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
	for(int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v;
	for(int i = 1; i <= m; i++){
		int u = e[i].u, v = e[i].v;
		int fu = find(e[i].u), fv = find(e[i].v);
		if(fu == fv) continue;
		if(siz[fu] < siz[fv]) swap(fu, fv);
		fa[fv] = fu;siz[fu] += siz[fv];g[u].push_back({v, i});g[v].push_back({u, i});
	}
	for(int i = 1; i <= n; i++) if(fa[i] == i) if(siz[i] % 2 == 1) num += siz[i] - 1;else num += siz[i];
	if(num < k||k%2!=0){cout << "No\n";return ;}
	for(int i = 1; i <= n; i++){
		if(fa[i] == i){
			dfs(i, 0);
		}
	}
	cout<<"Yes\n"<<tot<<'\n';
	for(int i = 1; i <= tot; i++) cout << stk[i]<<' ';
}

signed main(){int T = 1;
	while(T--) S();
	return 0;
}

```

---

## 作者：Phartial (赞：0)

给一个比较笨的做法。

首先显然 $K$ 是奇数时无解。

考虑原图中的任意一条简单路径，如果我们反转这条路径上每条边的选择情况（不选变成选，选变成不选），那么只有路径端点上的两个点的状态会被反转。

考虑对每个连通块拉一棵生成树，那么对于连通块里的任意两个未被点亮的点，我们反转其在生成树上的路径上每条边的选择情况即可点亮这两个点，重复进行此操作即可构造出所有有解的 $K$ 与其方案。

于是问题变成了树上路径反转，使用树上差分即可。

```cpp
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

const int kN = 2e5 + 2;

struct E {
  int x, i;
};
int n, m, k, f[kN], v[kN];
vector<E> e[kN];
vector<int> rl[kN], ans;

int F(int x) { return x == f[x] ? x : (f[x] = F(f[x])); }
void C(int x, int f) {
  for (E i : e[x]) {
    if (i.x != f) {
      C(i.x, x);
      if (v[i.x]) {
        ans.push_back(i.i);
      }
      v[x] ^= v[i.x];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k;
  if (k & 1) {
    cout << "No";
    return 0;
  }
  iota(f + 1, f + n + 1, 1);
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    if (F(x) != F(y)) {
      f[F(x)] = F(y);
      e[x].push_back({y, i}), e[y].push_back({x, i});
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (i == F(i)) {
      e[n + 1].push_back({i, 0});
    }
    rl[F(i)].push_back(i);
  }
  for (int i = 1; i <= n && k; ++i) {
    if (rl[i].size() & 1) {
      rl[i].pop_back();
    }
    for (int j : rl[i]) {
      v[j] ^= 1;
      if (!--k) {
        break;
      }
    }
  }
  if (k) {
    cout << "No";
    return 0;
  }
  C(n + 1, 0);
  cout << "Yes\n";
  cout << ans.size() << '\n';
  for (int i : ans) {
    cout << i << ' ';
  }
  return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](https://atcoder.jp/contests/abc345/tasks/abc345_f)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc345_f)
## 分析
首先 $k$ 为奇数时必然无解，因为此时相当于所有点的总操作次数为奇数，而这不可能。

先考虑图连通的情况。这样就相当于一张图里面有 $k$ 个点是染黑的，你要构造出这个局面。于是想如何染黑一个点而尽量不影响其他点。

首先我们可以发现操作的顺序是可以任意调换的，因为决定每个点最终颜色的是他的邻边被操作的总次数。而次数和操作顺序无关。所以一条边如果被操作奇数次，那等价于他被操作一次。如果被操作偶数次，那等价于没操作这条边。

我们考虑一种操作：选中一条路径，操作路径上的所有边。这样，受影响的只有路径的两个端点。可以认为路径上别的点没有被操作过。

于是我们考虑挑一个白点作为起点，然后对于每个黑点，我们把从起点到他的这条路径操作一遍。这样，由于黑点是偶数个，所以起点还是白的。而每个黑点都恰好会被影响一次。所以这样就构造出了想要的局面。

发现起点也可以是黑色的。此时起点之外还有奇数个黑点，所以对这些黑点都操作一次之后起点也是黑色的，而所有黑点也符合要求。

因此，我们只需要任意选出一个起点和 $k$ 个黑点，然后操作即可。具体的，我们考虑以起点为根拎一棵 dfs 生成树出来。方便起见，我们把前 $k$ 个遍历到的点染黑。然后可以发现每条边被操作的次数实际上就是子树中黑点的个数。这样我们就可以很快的求出每条边是否要被操作。

然后我们考虑图不联通的情况。首先考虑如何尽量多地染色某个连通块内的点。如果连通块里有偶数个点，那可以全染黑。否则就只把根留白。操作方法和图联通时的情况类似。

然后我们枚举每一个连通块。如果剩下的 $k$ 足够把当前连通块尽量多地染完，那就染完。否则转化为图联通时的情况。我们任挑 $k$ 个点染黑即可。

时间复杂度 $\mathcal{O}(n + m)$。

## 代码
```cpp
#include <iostream>
using namespace std;
struct Graph {
    int head[200005], nxt[400005], to[400005], id[400005], ecnt;
    void add(int u, int v, int x = 0) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt, id[ecnt] = x; }
} g1, g2;
int sz[200005];
bool vis[200005];
void dfs(int x) {
    sz[x] = 1;
    vis[x] = 1;
    for (int i = g1.head[x]; i; i = g1.nxt[i]) {
        int v = g1.to[i];
        if (!vis[v]) {
            dfs(v);
            g2.add(x, v, i >> 1);
            sz[x] += sz[v];
        }
    }
}
int ans[200005], acnt;
void dfs2(int x) {
    for (int i = g2.head[x]; i; i = g2.nxt[i]) {
        int v = g2.to[i];
        dfs2(v);
        if (sz[v] & 1) 
            ans[++acnt] = g2.id[i];
    }
}
int cmk[200005];
int k;
void mark(int x) {
    cmk[x] = (k != 0);
    k -= (k != 0);
    for (int i = g2.head[x]; i; i = g2.nxt[i]) {
        int v = g2.to[i];
        mark(v);
        cmk[x] += cmk[v];
        if (cmk[v] & 1) 
            ans[++acnt] = g2.id[i];
    }
}
int main() {
    g1.ecnt = 1;
    int n, m;
    cin >> n >> m >> k;
    if (k & 1) {
        cout << "No\n";
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g1.add(u, v);
        g1.add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
            if (sz[i] - (sz[i] & 1) <= k) {
                dfs2(i);
                k -= (sz[i] - (sz[i] & 1));
            } else {
                mark(i);
                k = 0;
            }
        }
    }
    if (!k) {
        cout << "Yes\n";
        cout << acnt << "\n";
        for (int i = 1; i <= acnt; i++) cout << ans[i] << " ";
    } else 
        cout << "No\n";
    return 0;
}
```

---

