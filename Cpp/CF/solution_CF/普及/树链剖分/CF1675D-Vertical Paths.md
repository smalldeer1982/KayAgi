# Vertical Paths

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Vertices are numbered from $ 1 $ to $ n $ . Any vertex can be the root of a tree.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root.

The tree is specified by an array of parents $ p $ containing $ n $ numbers: $ p_i $ is a parent of the vertex with the index $ i $ . The parent of a vertex $ u $ is a vertex that is the next vertex on the shortest path from $ u $ to the root. For example, on the simple path from $ 5 $ to $ 3 $ (the root), the next vertex would be $ 1 $ , so the parent of $ 5 $ is $ 1 $ .

The root has no parent, so for it, the value of $ p_i $ is $ i $ (the root is the only vertex for which $ p_i=i $ ).

Find such a set of paths that:

- each vertex belongs to exactly one path, each path can contain one or more vertices;
- in each path each next vertex — is a son of the current vertex (that is, paths always lead down — from parent to son);
- number of paths is minimal.

For example, if $ n=5 $ and $ p=[3, 1, 3, 3, 1] $ , then the tree can be divided into three paths:

1. $ 3 \rightarrow 1 \rightarrow 5 $ (path of $ 3 $ vertices),
2. $ 4 $ (path of $ 1 $ vertices).
3. $ 2 $ (path of $ 1 $ vertices).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1675D/b196ebd17b672e4b5d378bdd713910bded65862b.png)Example of splitting a root tree into three paths for $ n=5 $ , the root of the tree — node $ 3 $ .

## 样例 #1

### 输入

```
6
5
3 1 3 3 1
4
1 1 4 1
7
1 1 2 3 4 5 6
1
1
6
4 4 4 4 1 2
4
2 2 2 2```

### 输出

```
3
3
3 1 5
1
2
1
4

2
2
1 2
2
4 3

1
7
1 2 3 4 5 6 7

1
1
1

3
3
4 1 5
2
2 6
1
3

3
2
2 1
1
3
1
4```

# 题解

## 作者：宝硕 (赞：6)

更好的阅读体验：[https://oi.baoshuo.ren/solutions/codeforces-1675d/](https://oi.baoshuo.ren/solutions/codeforces-1675d/?utm_source=luogu.com.cn&utm_medium=solution-codeforces-1675d)

2022-05-19 更新：感谢 @fast_photon 指出本文中描述不恰当之处，现已修正。

## 思路

看到这道题的样例说明之后第一眼想到的是树链剖分（图源 [OI Wiki](https://oi-wiki.org/graph/hld/)）：

![](https://arina.loli.net/2022/05/08/Bx1MKGfRwZita5c.png)

按照这样剖出来的答案显然是对的。

再看看样例会发现一个很显然的结论：最小路径数一定是叶子节点数。

可以使用深度优先搜索，遇到分叉的时候就新开其他路径，同时挑选一个方向继续当前路径，这样出来的答案一定是最优的。

具体实现可以看代码。

## 代码

```cpp
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
const char endl = '\n';

const int N = 2e5 + 5;

int t, n, fa[N], root, ans_cnt;
std::vector<int> g[N], ans[N];

void dfs(int u, int fa, int cnt) {
    if (g[u].size() == 1) {  // 是否是叶子节点
        ans[cnt].push_back(u);
        return;
    }

    ans[cnt].push_back(u);

    bool f = false;

    for (int v : g[u]) {
        if (v == fa) continue;

        if (!f) {
            dfs(v, u, cnt);
            f = true;
        } else {
            dfs(v, u, ++ans_cnt);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    cin >> t;

    while (t--) {
        root = 0;
        ans_cnt = 1;

        cin >> n;

        for (int i = 1; i <= n; i++) {
            cin >> fa[i];

            if (fa[i] == i) root = i;

            g[i].push_back(fa[i]);
            g[fa[i]].push_back(i);
        }

        dfs(root, root, 1);

        for (int i = 1; i <= n; i++) {
            g[i].clear();
        }

        cout << ans_cnt << endl;
        for (int i = 1; i <= ans_cnt; i++) {
            cout << ans[i].size() << endl;
            for (int x : ans[i]) {
                cout << x << ' ';
            }
            cout << endl;

            ans[i].clear();
        }
        cout << endl;
    }

    return 0;
}
```


---

## 作者：ryanright (赞：5)

## Description

有一个 $n$ 个结点的有根树。现在要把它树链剖分，要求每个结点只属于一条树链，链必须要从祖先到后代，且树链的数量最少。如果有多种方案，输出任意一种。

## Solution

从非叶子结点出发的每一条树链，我们都毫不犹豫地下到叶子结点，这样就可以最小化树链数量了，因为这样做，树链的数量等于叶子结点的数目。树链的数目不可能比这更少了。

在实现过程中，我们从叶子结点往上推，一直推到根结点或是已经加入某个树链的结点，并倒序输出路径即可。

## Code

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int fa[200005], path[200005];
bool vis[200005],leaf[200005];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(vis, 0, sizeof(vis));
		memset(leaf, 1, sizeof(leaf));
		int n, ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &fa[i]);
			if (fa[i] != i)
				leaf[fa[i]] = 0;
		}
		for (int i = 1; i <= n; i++)
			if (leaf[i])
				ans++;
		printf("%d\n", ans);
		for (int i = 1; i <= n; i++)
			if (leaf[i]) {
				int now = i, len = 0;
				while (!vis[now]) {
					path[++len] = now;
					vis[now] = 1;
					if (fa[now] == now)
						break;
					now = fa[now];
				}
				printf("%d\n", len);
				for (int i = len; i >= 1; i--)
					printf("%d ", path[i]);
				puts("");
			}
		puts("");
	}
	return 0;
}
```

---

## 作者：Engulf (赞：5)

对整棵树进行**轻重链剖分**，通过第一次 dfs 求出每个节点的**重儿子**，再通过第二次 dfs 保存每条路径。每次都优先遍历重儿子，所以能够保证剖出的链总数最小。

坑点 1：只有一个节点时，dfs 会失效（没有重儿子），这种情况直接输出自己即可。

坑点 2：做多了 cf 题的就会知道 cf 经常卡直接对**整个数组**无脑 `memset` 的，所以在初始化是时仅需清零使用过的即可。

```cpp
// author: TMJYH09
// create time: 2022/05/05 23:08:43
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int N = 2e5 + 10;
struct edge{
    int to,nxt;
}e[N<<1];
int head[N],idx;
void add(int x,int y){
    e[++idx]={y,head[x]};
    head[x]=idx;
}
vector <int> path[N<<1];
int root,n;

int son[N],fa[N],siz[N];
int top[N],dfn;

void init(){
    for(int i=1;i<=dfn;i++)path[i].clear();
    for(int i=1;i<=n;i++)son[i]=0,fa[i]=0,siz[i]=0,top[i]=0,head[i]=0;//初始化要注意，第一次就是 memset 导致 TLE
    idx=dfn=0;
}

void dfs1(int u,int f){
    fa[u]=f;
    siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v!=f){
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]]){
                son[u]=v;
            }
        }
    }
}
void dfs2(int u,int tp){
    top[u]=tp;
    if(u==tp)++dfn;
    path[dfn].push_back(u);
    if(!son[u])return;
    dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v!=fa[u]&&v!=son[u])dfs2(v,v);
    }
}

void solve(){
    init();
    int x;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        if(i==x)root=x;
        else add(x,i),add(i,x);
    }
    if(n==1){
        cout<<1<<endl<<1<<endl<<x<<endl<<endl;return;
    }
    dfs1(root,0);
    dfs2(root,root);
    cout<<dfn<<endl;
    for(int i=1;i<=dfn;i++){
        cout<<path[i].size()<<endl;
        for(auto &j:path[i])cout<<j<<' ';
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int _;cin>>_;while(_--)solve();
    return 0;
}
```

---

## 作者：chenguanxing (赞：2)

# 题意

[传送门](https://www.luogu.com.cn/problem/CF1675D)


找叶子节点即可。

叶子节点是没有父亲，所以只要在父亲数组中找没出现过的数即可（记得特判 $n=1$ 的情况）

因为覆盖整个图要把所有的叶子节点覆盖，所以最少路径数就是叶子节点个数。

怎么找路径呢？

从每个叶子节点向上搜，打上标记，并反向输出即可。

如果找到已经标记过的点，直接跳出。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n;
int a[200000+25];
int yezi[200000+25];
int ans;
int tempi,top;
int lujing[200000+25];
bool used[200000+25];
int tong[200000+25];
signed main(){
	cin >> t;
	while(t --){
		cin >> n;
		ans = 0;
		memset(yezi, 0, sizeof(yezi));
		memset(used, 0, sizeof(used));
		memset(tong, 0, sizeof(tong));//记得初始化 
		for(int i = 1; i <= n; i ++){
			cin >> a[i];
			tong[a[i]] ++;//用桶记录
		}
		for(int i = 1 ;i <= n; i ++){
			if(tong[i] == 0){
				ans ++;
				yezi[i] = 1;//找没出现过的点 
			}
		}
		if(n == 1){
			ans = 1;
			yezi[1] = 1;//特判
		}
		cout << ans << '\n';
		for(int i = 1; i <= n; i ++){
			if(yezi[i]){
				tempi = i, top = 0;
				while(! used[tempi]){
					lujing[++top] = tempi;
					used[tempi] = 1;//打上标记
					tempi = a[tempi];//往上找节点 
				}
				cout << top << '\n';
			for(int i = top; i >= 1; i --){
				cout << lujing[i] << ' ';
			}
				cout << '\n';
			}
		}
		cout << '\n';
	}
	return 0;
}
```




---

## 作者：Yun_Mengxi (赞：2)

## 题意

[传送门](https://www.luogu.com.cn/problem/CF1675D)

## 分析

因为题目要求最少路径，所以可以想到，每条路径需要占用尽量多的点，于是可以使用树链剖分，求出每条重链，随后输出就可以了，关于树链剖分可以参考[模板的题解](/problem/solution/P3384)。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int n;
int f[200005];
vector<int> s[200005];
int root;
int son[200005];
int fat[200005];
int vis[200005];
vector<int> shulian[200005];
int cnt = 0;
void dfs(int u) {
  if (!s[u].size()) return;
  int maxx = s[s[u][0]].size(), maxi = s[u][0];
  vis[s[u][0]] = 1, dfs(s[u][0]);
  for (int i = 1; i < s[u].size(); i++) {
    if (!vis[s[u][i]]) vis[s[u][i]] = 1, dfs(s[u][i]);
    if (s[s[u][i]].size() >= maxx) {
      maxx = s[s[u][i]].size();
      maxi = s[u][i];
    }
  }
  son[u] = maxi;
  fat[maxi] = fat[u];
}
void dfs2(int u) {
  if (!u || vis[u]) return;
  vis[u] = 1;
  shulian[cnt].push_back(u);
  dfs2(son[u]);
}
void mian() {
  cin >> n;
  for (int i = 1; i <= cnt; i++) {
    shulian[i].clear();
  }
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    s[i].clear();
    fat[i] = i;
    vis[i] = 0;
    son[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    cin >> f[i];
    if (f[i] == i) {
      root = i;
    } else {
      s[f[i]].push_back(i);
    }
  }
  dfs(root);
  fill(vis + 1, vis + n + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (fat[i] == i) {
      ++cnt;
      dfs2(i);
    }
  }
  cout << cnt << endl;
  for (int i = 1; i <= cnt; i++) {
    cout << shulian[i].size() << endl;
    for (int j = 0; j < shulian[i].size(); j++) {
      cout << shulian[i][j] << " ";
    }
    cout << endl;
  }
}
int main() {
  cin >> t;
  while (t--) {
    mian();
  }
  return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：2)

我们可以从题目看出，一条路径只能向下走，也就是说，如果想要所有的点都走一遍的话，我们就必须把所有的叶子节点覆盖，也就是路径数等于叶子节点数。

那么我们就可以直接从每一个叶子节点往上搜，边搜边打标记，如果要是搜到了之前打过标记的点的话，我们就直接退出输出当前点的路径即可。

由于题目给出了每一个点的父节点，那么我们就可以把所有出现过的点标记为不是叶子节点，剩下的就都是叶子节点了。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define N 200100
using namespace std;
int t,n,ans,fa[N],stk[N],vis[N],ye[N];
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}
signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++)ye[i]=1,vis[i]=0;
		ans=0;
		for(int i=1;i<=n;i++)
		{
			fa[i]=read();
			if(fa[i]!=i)ye[fa[i]]=0;
		}
		for(int i=1;i<=n;i++)if(ye[i])ans++;
		cout<<ans<<endl;
		for(int i=1;i<=n;i++)
        {
            if(ye[i])
            {
                int now=i,len=0;
                while(!vis[now])
                {
                    stk[++len]=now;
                    vis[now]=1;
                    if(fa[now]==now)break;
                    now=fa[now];
                }
                cout<<len<<endl;
                for(int i=len;i>=1;i--)cout<<stk[i]<<" ";
                cout<<endl;
            }
        }
        cout<<endl;
	}
    return 0;
}
```

---

## 作者：xuhanxi_dada117 (赞：1)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF1675D)

# 前置芝士

## 树链剖分

很明显，题目想让我们把树剖分成一根根链。

顾名思义，这就是树剖。

## 重链剖分

### 重儿子

儿子中子树大小最大的儿子。

### 重边

父节点与重儿子的连边。

### 重链

重边连接成的链。

**重链剖分旨在把树分成很多重链。**

+ 一棵树的重链数量等于其叶节点数量。

# 解法

直接对树做重链剖分即可。

对每根链：按照顺序输出。

**多测一定要清空！！**

时间复杂度 $\Theta(T\times n)$。

# 代码

```cpp
//个人认为码风不错
#include<bits/stdc++.h>
#define N 200010
using namespace std;
int _,n,nE,rt,hd[N],son[N],top[N],sz[N],p[N],bx[N],gu[N],cnt=0;
vector<int> Chain[N];
struct edge{
	int to,nxt;
}e[N+N];
void add(int u,int v){
	e[++nE]=(edge){v,hd[u]};
	hd[u]=nE;
}
void dfs_son(int x,int fa){//求重儿子
	sz[x]=1;son[x]=0;
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa) continue;
		dfs_son(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]]||sz[y]==sz[son[x]]&&y<son[x])
			son[x]=y;
	}
}
void dfs_top(int x,int fa){//求链顶
	if(son[fa]==x) top[x]=top[fa];
	else top[x]=x;
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa) continue;
		dfs_top(y,x);
	}
}
void sfs(int x,int fa){//按照顺序添加链
	if(!bx[top[x]]) gu[top[x]]=++cnt;
	Chain[gu[top[x]]].push_back(x);
	++bx[top[x]];
	if(!son[x]) return;
	sfs(son[x],x);//采用重儿子优先搜索
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==son[x]||y==fa) continue;
		sfs(y,x);
	}
}
void init(){//初始化
	for(int i=1;i<=cnt;++i) Chain[i].clear();
	for(int i=1;i<=n;++i) hd[i]=son[i]=top[i]=e[i].nxt=e[i].to=p[i]=bx[i]=0;
	nE=cnt=0;
}
int main(){
	scanf("%d",&_);
	while(_--){
		scanf("%d",&n);
		init();
		for(int i=1;i<=n;++i){
			scanf("%d",&p[i]);
			if(i==p[i]) rt=i;
			else add(i,p[i]),add(p[i],i);
		}
		if(n==1){//特判 n=1
			printf("1\n1\n%d\n\n",rt);
			continue;
		}
		dfs_son(rt,0);
		dfs_top(rt,rt);
		sfs(rt,0);
		printf("%d\n",cnt);
		for(int i=1;i<=cnt;++i){//输出答案
			printf("%d\n",Chain[i].size());
			for(int j=0;j<Chain[i].size();++j){
				printf("%d ",Chain[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/108653041)

---

## 作者：Hooch (赞：0)

### 题目大意

给定一棵无根的、有 $n$ 个节点的树，现在要求你把它分成 $m$ 个路径，使得 $m$ 最小，路径 $V=\{a_1,a_2,a_3\cdots a_k\}$ 的定义如下：

+ $a_i$ 一定是 $a_{i+1}$ 的父亲节点。

+ $a_i$ 不属于任何两个路径，只属于一条。

+ 所有路径包含了所有节点。

请输出最小的 $m$ 和每个 $V$ 的大小和所有元素。

### 基本思路

我们首先发现，根据题意，每个路径一定是一条链。

那么我们可以看一个简单的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1j9jx7nm.png)

这时 $1$ 为根节点，我们可以发现一个性质：

无论怎样分，根节点都会跟有且只有一棵子树的其中一条路径合起来。

有了这个性质，我们就将这个根节点加入它的一棵子树的路径吗，这道题就能被解决了。

### 代码实现

我们从上述思路中发现，一个根节点的路径是由它的一棵子树合并而来的。于是我们用栈来储存：

+ 每次遇到一个节点，就将其放入栈中。

+ 若这个路径已经合并到了尽头，那么就一直弹栈，弹到根节点为止。

坑点：这道题的输出顺序是要求从一个 $V$ 的 $a_1$ 一直输出到 $a_k$，所以栈的输出顺序是正好相反的，我们只需要在输出的时候反向输出就行了。

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
using namespace std;
const int N = 2e5 + 5;
int n, root, ans; vector <int> G[N];
vector <int> k[N];
stack <int> st;
inline void dfs(int x, int f, bool o) {
	st.push(x); bool flg = 0;
	rep1(_, 0, (int)G[x].size() - 1) {
		int v = G[x][_];
		if (v == f) continue;
		dfs(v, x, flg);
		flg = 1;
	}
	if (o) {
		++ans;
		while (st.top() != x) {
			k[ans].push_back(st.top());
			st.pop();
		}
		k[ans].push_back(x); st.pop();
	}
}
signed main(void) {
	ios::sync_with_stdio(false);
	int t; cin >> t; while (t--) {
		cin >> n; ans = 0;
		while (st.size()) st.pop(); rep1(i, 1, n) k[i].clear();
		rep1(i, 1, n) G[i].clear();
		rep1(i, 1, n) {
			int p; cin >> p;
			if (p != i) G[p].push_back(i), G[i].push_back(p);
			else root = i;
		}
		dfs(root, -1, 1);
		cout << ans << endl;
		rep1(i, 1, ans) {
			cout << k[i].size() << endl;
			reverse(k[i].begin(), k[i].end());
			rep1(j, 0, (int)k[i].size() - 1) {
				cout << k[i][j] << ' ';
			} cout << endl;
		} cout << endl;
	}
}
```

---

