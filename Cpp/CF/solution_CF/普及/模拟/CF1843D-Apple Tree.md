# Apple Tree

## 题目描述

Timofey has an apple tree growing in his garden; it is a rooted tree of $ n $ vertices with the root in vertex $ 1 $ (the vertices are numbered from $ 1 $ to $ n $ ). A tree is a connected graph without loops and multiple edges.

This tree is very unusual — it grows with its root upwards. However, it's quite normal for programmer's trees.

The apple tree is quite young, so only two apples will grow on it. Apples will grow in certain vertices (these vertices may be the same). After the apples grow, Timofey starts shaking the apple tree until the apples fall. Each time Timofey shakes the apple tree, the following happens to each of the apples:

Let the apple now be at vertex $ u $ .

- If a vertex $ u $ has a child, the apple moves to it (if there are several such vertices, the apple can move to any of them).
- Otherwise, the apple falls from the tree.

It can be shown that after a finite time, both apples will fall from the tree.

Timofey has $ q $ assumptions in which vertices apples can grow. He assumes that apples can grow in vertices $ x $ and $ y $ , and wants to know the number of pairs of vertices ( $ a $ , $ b $ ) from which apples can fall from the tree, where $ a $ — the vertex from which an apple from vertex $ x $ will fall, $ b $ — the vertex from which an apple from vertex $ y $ will fall. Help him do this.

## 说明/提示

In the first example:

- For the first assumption, there are two possible pairs of vertices from which apples can fall from the tree: $ (4, 4), (5, 4) $ .
- For the second assumption there are also two pairs: $ (5, 4), (5, 5) $ .
- For the third assumption there is only one pair: $ (4, 4) $ .
- For the fourth assumption, there are $ 4 $ pairs: $ (4, 4), (4, 5), (5, 4), (5, 5) $ .

 ![](https://espresso.codeforces.com/7c6d16e8362e76df883e925d30296fb28360d590.png) Tree from the first example.For the second example, there are $ 4 $ of possible pairs of vertices from which apples can fall: $ (2, 3), (2, 2), (3, 2), (3, 3) $ . For the second assumption, there is only one possible pair: $ (2, 3) $ . For the third assumption, there are two pairs: $ (3, 2), (3, 3) $ .

## 样例 #1

### 输入

```
2
5
1 2
3 4
5 3
3 2
4
3 4
5 1
4 4
1 3
3
1 2
1 3
3
1 1
2 3
3 1```

### 输出

```
2
2
1
4
4
1
2```

## 样例 #2

### 输入

```
2
5
5 1
1 2
2 3
4 3
2
5 5
5 1
5
3 2
5 3
2 1
4 2
3
4 3
2 1
4 2```

### 输出

```
1
2
1
4
2```

# 题解

## 作者：Dream__Sky (赞：3)

题意简述：

提莫菲在他的花园里种了一棵苹果树；它是一棵有 $n$ 个顶点的有根树，根在顶点 $1$（顶点的编号从 $1$ 到 $n$）。给出的图没有重边与自环。


这棵苹果树相当年轻，所以只有两个苹果会在上面生长。苹果会在某些顶点上生长（这些顶点可能是相同的）。苹果长出来后，提莫菲开始摇晃苹果树，直到苹果掉下来。每次提莫菲摇动苹果树时，每个苹果都会发生以下情况：

设苹果现在在顶点 $u$。如果顶点 $u$ 有一个子节点，苹果就会移动到它那里（如果有几个这样的顶点，苹果可以移动到其中任何一个）。否则，苹果会从树上掉下来。

提莫菲有 $q$ 个假设，苹果可以在哪些顶点生长。他假设苹果可以在顶点 $x$ 和 $y$ 中生长，并想知道苹果可以从树上掉下来的顶点对 $(a,b)$ 的数量、其中 $a$ 为顶点 $x$ 的苹果会落下的顶点，$b$ 为顶点 $y$ 的苹果会落下的顶点。帮助他做到这一点。

分析：

这是一道树形 DP。

设 $f_i$ 为 $i$ 号节点能落下的顶点的个数，那么转移方程为： 

$$f_i=\sum f_j $$  

其中 $j$ 是 $i$ 的儿子。

我们还要考虑一种特殊情况，当这个点本来就是会使苹果下落的顶点时, 

$$f_i=1$$

那我们如何判断这是不是回使苹果落下的顶点呢？

我们可以建立一个数组来存每个顶点的度，当度为 $1$ 时，这个顶点就是会使苹果下落的顶点（根节点除外）。

知道了这个以后，我们可以用深搜来遍历整个树。

根据乘法原理，顶点对的个数就等于 $f_x \times f_y$。

附代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,T,du[200010],a[200010],Q;
bool p[200010]; 
vector<int> v[200010];
int dfs(int x,int f)//x代表当前遍历的点，f代表父节点
{
	if(du[x]==1&&x!=1) {a[x]=1;return a[x];}//如果这个顶点会使苹果下落，注意要排除根节点
	for(int i=0;i<v[x].size();i++)//遍历当前顶点的连边
	{
		if(v[x][i]==f) continue; //不能再次访问父节点
		a[x]+=dfs(v[x][i],x);//转移方程
	}
	return a[x];
}
signed main()
{
	cin>>T;//T组数据
	while(T--)
	{
		memset(du,0,sizeof du);
		memset(a,0,sizeof a);
		cin>>n;
		for(int i=1;i<=n;i++) v[i].clear();//多测要清空
		
		for(int i=1;i<n;i++)
		{
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);//建图
			du[x]++,du[y]++;//x与y点的度
		}
		dfs(1,1);//深搜
		cin>>Q;//Q个假设
		while(Q--)
		{
			int x,y;
			cin>>x>>y;
			cout<<a[x]*a[y]<<"\n";
		}
	}
	return 0;
}


```


---

## 作者：Coffee_zzz (赞：2)

### 分析

我们可以把要求的满足条件的 $(a,b)$ 的数量看成满足条件的 $a$ 的数量与满足条件的 $b$ 的数量的乘积。

我们知道，如果苹果初始时生长在节点 $u$ 处，那么只可能从以 $u$ 为根的子树中的叶子结点掉下，也就是说方案数为以 $u$ 为根的子树中叶子结点的个数。

那么我们只需要维护以每个节点为根的子树中叶子结点的个数 $val_u$，查询时输出 $val_x\times val_y$ 即可。

注意 $(2\times10^5)^2$ 会超出 `int` 的存储范围，需要开 `long long`。同时不要忘了多测清空。

### 代码

```c++
#define int long long
const int N=2e5+5;
int n,head[N],to[N<<1],nxt[N<<1],val[N<<1],deg[N<<1],cnt;
void add(int u,int v){
	++cnt;
	to[cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
	deg[u]++;
}
void dfs(int u,int f){
	int v;
	if(deg[u]==1&&f!=0){
		val[u]=1;
		return;
	}
	for(int i=head[u];i;i=nxt[i]){
		v=to[i];
		if(v==f) continue;
		dfs(v,u);
		val[u]=val[u]+val[v];
	}
}
void solve(){
	int u,v,q;
	n=read();
	for(int i=1;i<n;i++) u=read(),v=read(),add(u,v),add(v,u);
	dfs(1,0);
	q=read();
	for(int i=1;i<=q;i++) u=read(),v=read(),cout<<val[u]*val[v]<<endl;
	for(int i=1;i<=n;i++) head[i]=0;
	for(int i=1;i<=n*2;i++) to[i]=nxt[i]=val[i]=deg[i]=0;
	cnt=0;
}
```

---

## 作者：Wf_yjqd (赞：2)

被 hacker 整服了，就这么个题也非得让我加快读。。

------------

显然，题意为求两个点各自为根的子树叶子结点个数的乘积。

考虑如何求任意一个，显然树上 dp 板子。

$dp_i$ 表示以 $i$ 为根的子树叶子结点个数。

则 $dp_i=\sum\limits_{j\in Son_i} dp_j$，其中 $Son_i$ 为 $i$ 的儿子结点集合。

对于 $x$ 和 $y$ 的一组询问，输出 $dp_i\times dp_j$。

复杂度 $\operatorname{O}(n)$（完全不理解为啥会被 hack 成 TLE）。

------------

所以还得加个快读优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=4e5+84;
ll xx,ff;
char c;
inline ll read(){
    xx=0;
    ff=1;
    c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            ff=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        xx=xx*10+c-'0';
        c=getchar();
    }
    return xx*ff;
}
inline void print(ll x){
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
    return ;
}
struct Edge{
    ll to,ne;
}e[maxn];
ll T,n,q,x,y,ecnt,head[maxn],f[maxn];
inline void add(ll u,ll v){
    e[ecnt]={v,head[u]};
    head[u]=ecnt++;
    return ;
}
inline void dfs(ll x,ll fa){
    for(ll i=head[x];i;i=e[i].ne){
        if(e[i].to==fa)
            continue;
        dfs(e[i].to,x);
        f[x]+=f[e[i].to];
    }
    if(!f[x])
        f[x]=1;
    return ;
}
int main(){
    T=read();
    while(T--){
        memset(head,0,sizeof(head));
        memset(f,0,sizeof(f));
        ecnt=1;
        n=read();
        for(ll i=1;i<n;i++){
            x=read();
            y=read();
            add(x,y);
            add(y,x);
        }
        dfs(1,0);
        q=read();
        while(q--){
            x=read();
            y=read();
            print(f[x]*f[y]);
            putchar('\n');
        }
    }
    return 0;
}
```


---

## 作者：Auto_Accepted (赞：2)

## 题意：
有一棵二叉苹果树，每一时间在 $i$ 号节点的苹果会掉到 $i$ 的儿子上。如果 $i$ 是叶子节点，那么这个苹果就会从 $i$ 号节点上掉下来。

现在有 $q$ 次询问，每次询问给定两个数 $(x,y)$，表示在 $x$ 点与 $y$ 点各有一个苹果。询问这两个苹果有几种方式掉下来。（两种掉落方式不同当且仅当苹果掉落的节点编号不同）
## 题解：

树形 dp。

令 $dp_i$ 表示第 $i$ 个节点有多少种方式掉下来。

若 $i$ 是叶子节点，则 $dp_i=1$。

否则 $dp_i$ 为 $\sum dp_v\ (fa[v] = i)$。

使用 dfs 转移即可。

最后输出 $dp[x]\times dp[y]$ 即可。

## 代码：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , son[1000005] , dp[1000005];
vector <int> a[1000005];
inline void dfs(int now , int fa = -1){
	if(a[now].size() == 1 && a[now][0] == fa){
		dp[now] = 1;
		return ;
	}
	for(int i = 0;i < a[now].size();i++){
		int v = a[now][i];
		if(v != fa){
			dfs(v , now);
			dp[now] += dp[v];
		}
	}
}
signed main() {
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		int u , v;
		for(int i = 1;i <= n;i++){
			a[i].clear();
			dp[i] = 0;
		}
		for(int i = 1;i < n;i++){
			cin >> u >> v;
			a[u].push_back(v);
			a[v].push_back(u);
		}
		dfs(1);
		int q;
		cin >> q;
		while(q--){
			int x , y;
			cin >> x >> y;
			cout << dp[x] * dp[y] << endl;
		}
	}
	return 0;
}
```


---

## 作者：zhuweiqi (赞：1)

很裸的树形 dp。

思路：从父节点到子节点的顺序进行树形 dp，用 $f_i$ 表示编号为 $i$ 的苹果有几种掉落的地点（即以它为根节点的子树内有多少个叶子节点）：如果它本身是叶子节点，那么 $f_i=1$；否则 $f_i=$ 它的所有子节点的 $f_i$ 之和。对于每个询问的结果即为 $f_x\times f_y$。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[200002];
bool book[200002];
long long f[200002];
void dg(int x){
	book[x]=1;
	f[x]=0;
	for(auto it:v[x]){
		if(book[it]==0){
			dg(it);
			f[x]+=f[it];
		}
	}
	if(f[x]==0) f[x]=1;
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,x,y;
		cin>>n;
		for(int i=1;i<=n;i++){
			book[i]=0;
			v[i].clear();
		}
		for(int i=1;i<n;i++){
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		dg(1);
		int q;
		cin>>q;
		while(q--){
			cin>>x>>y;
			cout<<f[x]*f[y]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：rainygame (赞：1)

这道题就是一个树上 DFS。

我们设 $s_i$ 为第 $i$ 个结点及下面有多少个叶子结点。那么显然叶子结点的 $s$ 为 $1$，非叶子结点的 $s$ 就是其所有孩子结点的 $s$ 之和。

这里我们从 $1$ 开始往下搜，直到碰到了底再回来，最后回到 $1$。

对于每个询问，根据乘法原理，答案就是 $s_u\times s_v$。

注意事项：

- 不开 `long long` 见祖宗。
- 多测不清空，罚时两行泪。
- 不要用 `memset`！

考场代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for1(i, s, t) for (int i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
#define gc() getchar()
#define pc(x) putchar(x);
#define sp pc(' ');
#define el pc('\n');
#define Yes printf("YES");
#define No printf("NO");
#define err assert(0);
const int MAXN(2e5+1);
//const ll MOD(1e9+7);

ll re(){
	ll x(0), f(1);
	char ch;
	while ((ch = gc()) < 48) f = ch == '-' ? -1 : 1;
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = gc()) > 47);
	return x * f;
}

void uwr(ll x){
	ll tmp(x/10);
	if (tmp) uwr(tmp);
	pc(x-(tmp<<1)-(tmp<<3)^48);
}

void wr(ll x){
	if (x < 0){
		pc('-');
		x = -x;
	}
	uwr(x);
}

int n, q, u, v;
ll siz[MAXN];
vector<int> e[MAXN];

void dfs(int x, int fa){
	int flag(1);
	for3(i, e[x]){
		if (i != fa){
			dfs(i, x);
			siz[x] += siz[i];
			flag = 0;
		}
	}
	if (flag) siz[x] = 1;
}

void solve(){
	n = re();
//	memset(siz, 0, (n+1)<<3);
	for1(i, 1, n){
		e[i].clear();
		siz[i] = 0;
	}
	for1(i, 1, n-1){
		u = re();
		v = re();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	
	q = re();
	while (q--){
		u = re();
		v = re();
		wr(siz[u]*siz[v]);
		el
	}
}

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	int t(1);
	t = re();
	while (t--){
		solve();
//		el
	}

	return 0;
}

```


---

## 作者：ForMyDream (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1843D)

### 题意：
给定一棵树，求 $x$ 子树叶子节点与 $y$ 子树叶子节点可能出现的组合方案数。

### 求解：
跑 dfs 求子树中叶子节点的个数

- dfs 是先判断是否为叶子节点，$siz_x$ 为 $1$ 代表 $x$ 是叶子节点；

- dfs2 是统计叶子节点的个数。

### 答案统计：

简单的乘法原理。    
设 $u$ 的子树中叶子节点的个数为 $a$ 个，$v$ 的子树中叶子节点的个数为 $b$ 个，答案即 $a \times b$。

### 注意事项：
**如果您 WA on #8，请注意**   
6 月 20 号的比赛真的是 long long 场，B 题和 C 题都用的是 long long；当时调 D 题一直是 WA on #8，最后 6 分钟猛然醒悟，**开了 long long**，通过了本题。

下面通过特殊数据计算 long long 的必要性。    
构造这样一组数据，节点数为 $2 \times 10^5$ 其中 $1$ 为根节点，$2$ 到 $2 \times 10^5$ 号节点都是 $1$ 的子节点（即均为叶子节点），使要查询的子树为：$1$ 节点的子树和 $1$ 节点的子树，求出叶子节点个数再相乘，答案为 $199999 \times 199999 = 39,999,600,001$，显然大于 $2147483647$，所以 int 无法储存。
```cpp
#include<iostream>
#include<cstring>
#define maxn 200001
using namespace std;
struct Edge{ int v,nxt; }edge[maxn<<1];
int n,t,x,y,cnt,head[maxn],dep[maxn],siz[maxn],q;
long long lvs[maxn];
void add(int u,int v){ edge[++cnt].v=v,edge[cnt].nxt=head[u],head[u]=cnt; }
void dfs(int u,int fa){
	siz[u]=1;
	for (int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if (v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int fa){
	if (siz[u]==1) lvs[u]=1;
	for (int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if (v==fa) continue;
		dfs2(v,u);
		lvs[u]+=lvs[v];
	}
}
int main(){
	cin>>t;
	while (t--){
		cin>>n; int u,v;
		for (int i=1;i<n;i++){
			cin>>u>>v; add(u,v); add(v,u);
		}
		dfs(1,0);
		dfs2(1,0);
		cin>>q;
		for (int i=1;i<=q;i++){
			cin>>x>>y;
			cout<<lvs[x]*lvs[y]<<endl;
		}
		for (int i=1;i<=2*n;i++){
			edge[i].v=0,edge[i].nxt=0;
		}
		for (int i=1;i<=n;i++) head[i]=0,lvs[i]=0,siz[i]=0,dep[i]=0;
		cnt=0;
	}
	return 0;
}
```
2023 年 6 月 24 日

---

## 作者：sunkuangzheng (赞：1)

写题十分钟，读题半小时——没有好翻译软件的痛。

**【题目大意】**

给定根为 $1$ 的树，每次询问问子树 $u$ 和子树 $v$ 内叶子节点个数的乘积。

**【题目分析】**

dfs 扫一遍统计出叶子节点数量，完事。

注意多测清空和开 `long long`。

具体实现看代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,q;
struct edge{
	int to,nxt;
}e[500005];int cnt,head[500005],siz[500005];
void add(int u,int v){
	e[++cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
void dfs(int u,int fa){
	bool flag = 0;
	for(int i = head[u];i;i = e[i].nxt){
		int v = e[i].to;if(v == fa) continue;
		flag = 1;
		dfs(v,u);
		siz[u] += siz[v]; 
	}
	if(!flag) siz[u] = 1;
}
signed main(){
    cin >> t;
    while(t --){
    	cin >> n;
    	cnt = 0;
    	for(int i = 1;i < n;i ++){
    		int x,y;cin >> x >> y;add(x,y);add(y,x);
		}
		dfs(1,0);
		cin >> q;
		while(q --){
			int x,y;cin >> x >> y;
			cout << (siz[x] * siz[y]) << endl;
		}
		for(int i = 1;i <= n;i ++) head[i] = siz[i] = 0;
	}
	return 0;
}


```

---

## 作者：XSean (赞：1)

# D：Apple Tree

[Problem - D - Codeforces](https://codeforces.com/contest/1843/problem/D)

## 基本思路：

思路：记录每一个节点都有多少个叶子节点 `sum[u]`，询问时输出 `sum[x] * sum[y]` 即可。dfs 求每个节点的叶子节点的个数：若一个节点没有儿子，则 `sum[u] = 1`，然后回溯即可。

细节：

1. $(2\times10^5)^2$ 是大于整型的最大值的，所以最后计算答案开 `long long`。

**时间复杂度：$O(N)$**。

## 代码实现：

核心代码：

```cpp
void dfs(int u, int f){
	int F = 0;
	Ede(i, u){
		int v = e[i];
		if(v == f) continue;
		F = 1;
		dfs(v, u);
		sum[u] += sum[v];
	}
	if(!F) sum[u] = 1;
}
```

**[完整代码](https://codeforces.com/contest/1843/submission/210496596)**

---

## 作者：ran_qwq (赞：0)

给你一棵根为 $1$ 的 $n$ 个节点的树。有两个苹果，分别从 $x,y$ 往下落，每次如果有子节点会落到任意一个，否则会掉下来。问可能的掉下来的位置点对 $(a,b)$ 的对数。

---
结合样例可知，如果苹果从 $x$ 落下，则会落到以 $x$ 为根的子树的任意一个叶子节点。一个节点下面的叶子节点个数就是它的所有子节点下面的叶子节点个数之和。设以 $u$ 为根的子树的叶子节点个数 $son_u$，则 $son_u=\sum\limits_vson_v$（$v$ 是 $u$ 的子节点）。答案就是 $son_x\times son_y$。

```cpp
void dfs(int u,int fa)
{
	if(n==1||u!=1&&G[u].size()==1) {son[u]=1;return;}
	for(int v:G[u])
	{
		if(v==fa) continue;
		dfs(v,u),son[u]+=son[v];
	}
}
void solve()
{
	n=read();for(int i=1;i<=n;i++) son[i]=0,G[i].clear();
	for(int i=1,x,y;i<n;i++) x=read(),y=read(),G[x].push_back(y),G[y].push_back(x);
	dfs(1,0),q=read();for(int i=1,x,y;i<=q;i++) x=read(),y=read(),write(son[x]*son[y],"\n");
}
```

---

