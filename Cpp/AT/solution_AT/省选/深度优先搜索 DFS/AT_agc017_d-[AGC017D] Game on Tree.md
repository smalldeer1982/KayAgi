# [AGC017D] Game on Tree

## 题目描述

有一棵 $N$ 个节点的树，节点标号为 $1,2,⋯,N$，边用 $(x_i,y_i)$表示。 Alice 和 Bob 在这棵树上玩一个游戏，Alice先手，两人轮流操作：


选择一条树上存在的边，把它断开使树变成两个连通块。然后把不包含 $1$ 号点的联通块删除


当一个玩家不能操作时输，你需要算出：假如两人都按最优策略操作，谁将获胜。

## 说明/提示

$1 \leq N \leq 100000$

$1\leq x_i,y_i \leq N$

保证给出的是一棵树

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
4 5```

### 输出

```
Alice```

## 样例 #2

### 输入

```
5
1 2
2 3
1 4
4 5```

### 输出

```
Bob```

## 样例 #3

### 输入

```
6
1 2
2 4
5 1
6 3
3 2```

### 输出

```
Alice```

## 样例 #4

### 输入

```
7
1 2
3 7
4 6
2 3
2 4
1 5```

### 输出

```
Bob```

# 题解

## 作者：_lbw_ (赞：20)

怎么都没有一点解释的，看不起 SG 函数？？

我们发现这题是一个 DAG 博弈论问题，考虑 SG 函数。

我们设 $u$ 子树博弈后的 SG 函数为 $f_u$，$u$ 子树的 DAG 为 $g_u$。

考虑对于 $u$ 计算 $f_u$。

对于每个 $v,s.t\ \exists(u,v)$，都看作是一个子 DAG，同时我们每时每刻都可以直接把 $(u,v)$ 这条边割掉，于是新建一个节点，将 $g_v$ 中的每一个节点都连向 $0$ 得到 $g'_v$，于是 $g'_v$ 里的每个点 SG 值应当都加上 $1$，于是 $g'_v$ 的 SG 值 $f'_v=f_v+1$ 。

我们知道很多 DAG 拼一起 SG 值是它们的异或和，于是 $f_u=\oplus_{(u,v)=1}(f_v+1)$。

做完了。

---

## 作者：小粉兔 (赞：20)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC017.html](https://www.cnblogs.com/PinkRabbit/p/AGC017.html)。

我们考虑根只有一个孩子的情况：显然 Alice 把这条边断掉即可赢得游戏。

如果有两个孩子呢：那就是谁先把其中一条边断掉谁就输掉游戏，然后就可以看成两个子树的子问题。

如果两棵子树的 SG 值相同，则 Alice 输掉游戏，Bob 赢得游戏。

如果有三个孩子呢？我的思路到这里就卡住了。

最后我是观察了如果三棵子树都是往下挂的链的情况：这完全等价于 Nim 游戏。  
而且对于一般的三子树情况或者更多子树的情况我完全没有思路。

根据 Nim 游戏的结论，我只能猜测整棵树的 SG 值应该等于每棵子树的 SG 值**加上** $\boldsymbol{1}$ **后**的异或和。

对着样例验证发现没错，交上去 AC 了。那么这个结论要如何证明呢？

我们注意到，如果有 $k$ 棵子树，那么我们可以把根节点复制 $k$ 份，每个根节点只下接一棵子树。

这样就分成了独立的 $k$ 个游戏，而每个游戏中，根节点只有一棵子树。显然原树的 SG 值等于这些子游戏的 SG 值的异或和。

但是对于根节点只有一个孩子的游戏，它的 SG 值又如何求出呢——已经无法分解成更小的游戏了。

但我们可以证明这样一个结论：对于根节点只有一个孩子的游戏，其 SG 值为其子树的 SG 值加上 $1$。

我们可以这样证明：如果直接断开了根与其子树相连的边，则下一状态的 SG 值为 $0$。  
否则，也就是断开了子树内的边，此时仍然满足根节点只有一个孩子，而且问题规模更小。  
结合数学归纳法，我们可以证明原树可以转移到每个子树能转移到的状态的 SG 值加 $1$ 的状态，从而证明此结论。

所以只要对这棵树做一次 DFS 即可，某棵树的 SG 值为其所有子树的 SG 值加 $1$ 后的异或和。

```cpp
#include <cstdio>
#include <vector>

const int MN = 100005;

int N;
std::vector<int> G[MN];

int DFS(int u, int p) {
	int ret = 0;
	for (int v : G[u]) if (v != p) ret ^= DFS(v, u) + 1;
	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 1, x, y; i < N; ++i)
		scanf("%d%d", &x, &y),
		G[x].push_back(y),
		G[y].push_back(x);
	puts(DFS(1, 0) ? "Alice" : "Bob");
	return 0;
}
```

---

## 作者：hellolin (赞：6)

You can view the [English version](https://www.luogu.com/article/2ejrb30r) of this solution.

题中的操作可以理解为有根树上选择一个子树删除（不能删整棵树），转化成 DAG 博弈，我们考虑设 $\operatorname{SG}(x)$ 为以 $x$ 为根的子树的 SG 值。

合理猜测 $\operatorname{SG}(x) = \begin{cases}
0 & x \text{ has no son}\\
\operatorname{xor}_{y \text{ is a son of } x} \operatorname{SG}(y) + 1 & \text{otherwise}
\end{cases}$，下证这个结论。

1. $x$ 没有儿子，显然 SG 值为 $0$。
2. $x$ 有一个儿子，设它是 $y$，此时我们证明 $\operatorname{SG}(x)=\operatorname{SG}(y)+1$：
   - 删除以 $y$ 为根的子树，显然 SG 值为 $0$。
   - 删除其他子树，显然这个子树在以 $y$ 为根的子树内，使用数学归纳法，$y$ 子树内剩余部分的 SG 值中 $0, 1, \dots, \operatorname{SG}(y) - 1$ 均出现，则 $\operatorname{SG}(x)=\operatorname{mex}(1, 2, \dots, \operatorname{SG}(y))=\operatorname{SG}(y)+1$。
3. $x$ 有多个儿子，此时把 $x$ 的儿子们断成若干部分，根据 SG 定理计算异或值即可。

一遍 DFS 即可求出最终答案。

---

## 作者：littlebug (赞：5)

## Solution

根据 SG 函数的[基本定理](https://oi-wiki.org/math/game-theory/impartial-game/#有向图游戏与-sg-函数)，我们可以把根节点拆开，拆成其子树个数个根节点，从而构成了一个 DAG，所以可以得出根节点的 SG 值为**以其为根的**所有子树的 SG 值的异或和。

考虑如何计算只有一个子树的根节点的 SG 值。

回到题面上来，一次操作是删一条边，等价于删掉任意一个子树。我们考虑如果删除与根节点相连的那条边，很显然 SG 值为 $0$（因为没有任何边可删了）。而如果我们删子树内部的边，就相当于这颗子树（**不包括根节点**）的 SG 值了，不过注意，我们从根节点到子树的这条边还没有算进去，所以应该为子树的 SG 值**加一**。

所以以根节点为根的子树的 SG 值为不包括根节点的子树的 SG 值 $+1$。

那么我们可以得到转移方程：$SG(u) = \bigoplus \limits _{v \in u.son} (SG(v)+1)$。

dfs 即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define pb emplace_back
#define int long long
#define il inline
using namespace std;

const int MAXN=1e5+5;
int n,sg[MAXN];
vector <int> p[MAXN];

il void dfs(int u,int ufa)
{
	for(auto i:p[u])
	{
		if(i==ufa) continue;
		dfs(i,u);
		sg[u]^=sg[i]+1;
	}
}

signed main()
{
	ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);

	cin>>n;
	int x,y;
	for(int i=1;i<n;++i) cin>>x>>y,p[x].pb(y),p[y].pb(x);
	
	dfs(1,0);
	cout<<(sg[1] ? "Alice" : "Bob");

	return 0;
}
```

---

## 作者：ezoixx130 (赞：4)

首先这很明显是一道博弈题。

按照经典套路，博弈题不是sg函数就是人类智慧。

这道题往sg函数上想很快就能想到这就是个树上nim游戏。

每个节点的sg函数值就是所有儿子的sg函数值+1的异或和。

最后判断根节点的sg函数值是否为0就可以了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010

vector<int> edge[MAXN];
int n,sg[MAXN],u,v;

void dfs(int u,int fa)
{
    sg[u]=0;
    for(auto v : edge[u])
    {
        if(v==fa)continue;
        dfs(v,u);
        sg[u]^=sg[v]+1;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    puts(sg[1]?"Alice":"Bob");
}
```

---

## 作者：teylnol_evteyl (赞：3)

设 $f_u$ 表示以 $u$ 为根的子树中固定节点 $u$ 的 $sg$ 函数，因为每棵子树加上节点 $u$ 都是独立的局面，根据 sg 定理，$f_u$ 等于每棵子树加上节点 $u$ 构成的树固定节点 $u$ 的局面的 sg 函数异或和。

差不多长这个样子：

```
    u         u          u
   / \       /            \
  o   o =   o      xor     o
 / \       / \
o   o     o  o
```

对于子节点 $v$，这样局面的 $sg$ 函数等于 $f_v+1$。归纳法证明：

- 如果子树只有一个节点，则 $f_v=0$ 而 $sg$ 函数等于 $1$。
- 如果子树有多个节点，可以通过割掉 $u$ 到 $v$ 的边到达 $sg$ 函数是 $0$ 的局面，而割掉其它边到达的局面的 $sg$ 函数是子树割掉这条边的 $sg$ 函数加 $1$，所以这个局面的 $sg$ 函数应该等于 $f_v+1$。

所以，$f_u=\oplus f_v+1$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n;
int la[N], ne[N * 2], en[N * 2], idx;
int sg[N];

void add(int a, int b)
{
	ne[ ++ idx] = la[a];
	la[a] = idx;
	en[idx] = b;
}
void dfs(int u, int fa)
{
	for(int i = la[u]; i; i = ne[i])
	{
		int v = en[i];
		if(v != fa)
		{
			dfs(v, u);
			sg[u] ^= sg[v] + 1;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i ++ )
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	dfs(1, 0);
	puts(sg[1] ? "Alice" : "Bob");
	return 0;
}
```

---

## 作者：Ebola (赞：3)


讲真这种在国内OI界早已被奉为经典的题，拿出来比赛，不是纯粹欺负外国人吗……

经典结论：树上节点的sg值等于所有每个子树sg值加1的异或和

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
int h[N],sum=0,n;

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

int dfs(int u,int fa)
{
    int res=0;
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(e[tmp].to!=fa) res^=dfs(e[tmp].to,u)+1;
    return res;
}

int main()
{
    int u,v;n=read();
    for(int i=1;i<n;i++)
    {
        u=read();v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    puts(dfs(1,0)?"Alice":"Bob");
    return 0;
}
```



---

## 作者：Mirasycle (赞：2)

一个状态可以表示为 $(s_1,s_2,s_3....)$ 每个 $s$ 表示 $u$ 的一个子树，多状态所以这是多个有向图。

所以 $u$ 的 SG 是所有子节点 SG 的异或吗？

其实不是，因为本题是在边上面操作，可以类比 NIM 博弈，这其实是一个**关于边的 NIM 博弈，而不是关于点的**。

$v$ 到 $u$ 还有一条边，所以其实是子节点的 SG 函数值加一再全部异或起来。

从边博弈的角度就可以很轻松简洁地证明这个问题，而不是有的题解的玄学角度。

时间复杂度 $O(n)$。



```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=2e5+10;
vector<int> G[maxn];
int dfs(int u,int fa){
	int res=0;
	for(auto v:G[u])
		if(v!=fa) res^=(dfs(v,u)+1);
	return res;
}
int main(){
	int n; cin>>n;
	for(int i=1;i<=n-1;i++){
		int u,v; cin>>u>>v;
		G[u].push_back(v); G[v].push_back(u); 
	}
	if(dfs(1,0)) cout<<"Alice";
	else cout<<"Bob";
	return 0;
}
```

---

## 作者：ダ月 (赞：2)

操作等价删除一棵子树。

结论 $1$：对于一棵树 $T$，其 $SG$ 函数为 $SG(T)$，将其根节点加入一个父亲，生成了一棵新的树为 $T'$，那么 $SG(T')=SG(T)+1$。

证明：

对于由一个结点构成的树 $T$，$SG(T)$ 值显然为 $0$。

记树 $T$，先钦定它为一条树链，有子树 $T_i$，所以 $SG(T)=\operatorname{mex}\{SG(T_i),0\}$，那么它根节点增加一个父亲以后，$SG(T')=\operatorname{mex}\{SG(T),SG(T_i),0\}$，归纳一下，就可以的到上面这个结论。

若树 $T$ 不是一条链，那么归纳同理。

然后跑一个树形 dp 就行了。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd(x) push_back(x)
#define all(x) x.begin(),x.end()
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10);}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
}
//==============================================================================
const int N=2e5+10;
int SG[N];
vector<int> a[N];
int n;
void dfs(int x,int F){
	for(auto y:a[x]){
		if(y==F)continue;
		dfs(y,x);
		SG[x]^=SG[y]+1;
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		a[x].pd(y);
		a[y].pd(x);
	}dfs(1,0);
	puts(SG[1]?"Alice":"Bob");
	return 0;
}



```


---

## 作者：1saunoya (赞：2)

对于一棵树 $T$，$sg(T) = \oplus_{S \in T} sg(S)$。


考虑一颗树 $S \in T$。


令 $T$ 的儿子数量为 $SIZE(T)$。

那么我们复制 $SIZE(T)$ 个 $T'$。

发现现在的情况等价于有 $SIZE(T)$ 棵树，每个根都是 $T'$ 连着 $S \in T$。

然后 $sg$ 值显然可以直接异或起来。

考虑一下叶子节点就做完了。

人类智慧。


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
const int N = 2e5 + 5;
vector<unordered_set<int> > g;
int dfs(int u,int p){
	int sg = 0;
	for(auto v:g[u]){
		if(v==p)continue;
		sg ^= dfs(v, u) + 1;
	}
	return sg;
}

int main() {
	int n;
	rd(n);
	g.resize(n);
	rp(i,n-1){
		int x,y;
		rd(x);
		rd(y);
		--x;
		--y;
		g[x].insert(y);
		g[y].insert(x);
	}
	pts(dfs(0,-1)?"Alice":"Bob");
	return 0;
}
```

---

## 作者：QcpyWcpyQ (赞：1)

根据 SG 函数的性质，若目标求出一颗子树的 SG 值，则只需要知道一颗子树带上与根连接的一条孤立边的 SG 值。

前者由后者得到。考虑后者如何有前者得到即可得到仅关于子树 SG 值之间的递推式。

记一棵树为 $T$，根带上一条孤立边后为 $T^{\prime}$，其等价于将 $T$ 的根与一个新建虚点相连，以虚点为根的树的 SG 值。那么有性质：$SG\left(T^{\prime}\right)=SG\left(T\right)+1$。证明是容易的，因此可以知道子树之间 SG 值的转移：

$$
SG\left(u\right)=\oplus_{u\to v}\left(SG(v)+1\right)
$$

这个性质称为克朗原理（Colon’s Principle）。

---

## 作者：___Furina___ (赞：1)

### 题意简述：
无……
### 题解：
一道很不错的博弈论思维题，一开始可能会难以理解，希望这篇题解能够答疑解惑。

在做这道题之前，首先要先知道一个有关[有向图博弈](https://oi-wiki.org/math/game-theory/impartial-game/)的关键点：

> 对于由 $n$ 个有向图游戏组成的组合游戏，设它们的起点分别为 $s_1, s_2, \ldots, s_n$，则有定理：**当且仅当** $\operatorname{SG}(s_1) \oplus \operatorname{SG}(s_2) \oplus \ldots \oplus \operatorname{SG}(s_n) \neq 0$ 时，这个游戏是先手必胜的。同时，这是这一个组合游戏的游戏状态 $x$ 的 $\operatorname{SG}$ 值（节选自 OI-wiki）。

知道这些以后，便可以开始来考虑这道题了。

首先，我们容易发现，这道题中的胜负关系是和 $1$ 号节点相连接的所有子树的形态有关。

于是，受 $\operatorname{SG}$ 函数影响，我们不妨把这个游戏分割成若干个子游戏，也就是 $1$ 号点的每一棵子树都分开来考虑，并将每个子树的根与 $1$ 号点相连。

很显然，每一个子游戏都是有向图游戏，根据有向图游戏的知识，我们不妨假设每一棵子树的 $\operatorname{SG}$ 值求出来，再将 $\operatorname{SG}$ 值异或起来，根据定义，**当且仅当**异或值为 $0$ 时先手必败。

现在我们来考虑如何求出每一棵子树的 $\operatorname{SG}$ 值，下面使用归纳法求解：

- 叶节点的 $\operatorname{SG}$ 值为 $0$（先手必败）；
- 现在沿着连接叶节点的边向根走，假设目前的结点为 $x$，它有 $y_1,y_2,\ldots,y_k$ 的叶子节点，根据 $\operatorname{SG}$ 值的定义，有：

$$\operatorname{SG}(x)=\operatorname{mex}\{\operatorname{SG}(y_1), \operatorname{SG}(y_2), \ldots, \operatorname{SG}(y_k)\}$$
容易推出，$\operatorname{SG}(x)=1$；
- 再次归纳，如果删了 $x$ 结点的**子树内**的一条边，是不是相当于整个子树变小了，但是 $\operatorname{SG}(x)$ 值仍不为 $0$；如果删了 $x$ 结点到其父亲的边呢？很明显，$\operatorname{SG}(x)$ 变成了 $0$；
- 又根据 $\operatorname{SG}$ 的定义，如果 $\operatorname{SG}(x)$ 不为 $0$，那**从 $x$ 的子结点**出发形成的子游戏的 $\operatorname{SG}$ 值一定包含了 $0\sim \operatorname{SG}(x)-1$ 的所有数；
- 综上所述，**操作完一步**后的子游戏的 $\operatorname{SG}$ 值可以是 $0\sim \operatorname{SG}(x)$ 中的任何数；
- 根据刚刚那个式子，可以得到这个有向图子游戏传递给父亲的的 $\operatorname{SG}$ 值为 $\operatorname{SG}(x)+1$，从而得出结论。

那么，代码只要通过 DFS 求出每个子树的 $\operatorname{SG}$ 值就可以了，记得加上 $1$。

### 代码：
```cpp
#include<bits/stdc++.h>
#define N 100010
#define I_love_Furina return//码风可爱！
#define forever 0
#define foreverr 1
#define Endl endl
#define endl '\n'
#define FIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
//#define int long long
using namespace std;
int n,T,m,cnt,son[N],head[N],num,pr[N],rt;
struct edge{int to,nxt;}a[N<<1];
inline void add(int u,int v){a[++num].to=v,a[num].nxt=head[u],head[u]=num,pr[u]++;}
int dfs(int x,int fa){
	int res=0;
	for(int i=head[x];i;i=a[i].nxt)
        if(a[i].to!=fa)res^=(dfs(a[i].to,x)+1);//结论
	I_love_Furina res;
}
signed main(){
	IOS;//FIO("");
	cin>>n;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,add(u,v),add(v,u);
	cout<<(dfs(1,0)?"Alice":"Bob");
	I_love_Furina forever;
}
```
感觉树上博弈论用到 $\operatorname{SG}(x)=\bigoplus\limits_{v\in son(x)}(\operatorname{SG}(v)+1)$ 很多，证明也不是很好写，网上也没什么资料，差不多用自己的方式去理解的，如有偏差，还请指出。

如果有不理解的地方也可以来找我？

---

## 作者：DengDuck (赞：1)

我们考虑根为 $u$ 的情况的 $\text {SG}_u$ 值怎么求，发现可以对于每条与孩子的链接分别考虑再异或起来。

用小粉兔的话说就是将树根复制多份，使问题变成多个游戏，每个游戏保证树根只有一个孩子。

然后根据定理可以异或起来，这个是比较基础的。

对于每个链接，我们可以选子树的边或者链接的边，如果是选链接的边，则转移到 $\text {SG}$ 值为 $0$ 的状态。

否则，我们选子树里的边，设儿子的 $\text {SG}$ 值为 $\text{SG}_v$，则断了边后子树的 $\text {SG}$ 值肯定会变化为 $[0,\text {SG}_v-1]$ 的某一项。

我们只能猜一手结论。

我们用个数学归纳法，设子树 $\text {SG}$ 值为 $[1,x-1]$ 时满足 $\text {SG}_u=\text {SG}_v+1$。

如果 $\text{SG}$ 值为 $0$ 就是只可以断链接边的情况，得 $\text{SG}$ 值为 $1$，说明在边界我们的假设成立。 

对于 $\text{SG}$ 值为 $x$ 的情况，我们发现我们现在断边之后，对于子树的 $\text{SG}$ 值，我们必然会转换成 $[0,x-1]$ 其中的一种情况，根据前面的假设，我们转移到了 $[1,x]$ 的状态。

由于 $0$ 是存在的，所以 $\text {SG}_u=\text {SG}_v+1$。

于是按上文所述异或起来即可。

得公式：

$$
\text {SG}_u=\bigoplus_{v\in uson}(\text {SG}_v+1)
$$

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
LL n,x,y,sg[N];
vector<LL>v[N];
void dfs(LL x,LL f)
{
	for(LL i:v[x])
	{
		if(i==f)continue;
		dfs(i,x);
		sg[x]^=sg[i]+1;
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n-1;i++)
	{
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	if(sg[1])
	{
		puts("Alice");
	}
	else
	{
		puts("Bob");
	}
}
```

---

## 作者：AC_love (赞：1)

我们考虑这样一个问题：如果以这棵树的根节点的每个儿子为根的子树都是一条链应该怎么做。

此时我们发现：每次只能对其中一条链下手，我们可以断掉这条链的一部分。最后谁断掉了最后一条链就获胜了。

显然此时问题就转化成了 Nim 游戏，直接把每条链上可以操作的边数全部异或起来就是答案。

那么我们就可以把每棵子树都视为一条链，链的长度就是子树的 SG 函数值。

问题转化为怎么求每棵子树的 SG 值。

不难发现每棵子树的 SG 值就是所有以该子树的根节点的儿子为根的子树的 SG 值加一再异或起来。而单独一个点的 SG 值显然为 $0$。

那么我们直接从根往下 DFS 即可。

代码实现如下：

```cpp
const int N = 214514;
int n;
vector <int> e[N]; 

int dfs(int st, int fa)
{
	int res = 0;
	for(int i = 0; i < e[st].size(); i = i + 1)
	{
		int ed = e[st][i];
		if(ed == fa)
			continue;
		res ^= (dfs(ed, st) + 1);
	}
	return res;
}

signed main()
{
	n = read();
	for(int i = 1; i <= n - 1; i = i + 1)
	{
		int st, ed;
		st = read();
		ed = read();
		e[st].push_back(ed);
		e[ed].push_back(st);
	}
	cout << (dfs(1, 0) ? "Alice" : "Bob");
	return 0;
}
```

---

