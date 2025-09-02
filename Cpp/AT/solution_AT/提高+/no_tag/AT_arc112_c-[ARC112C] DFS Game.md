# [ARC112C] DFS Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc112/tasks/arc112_c

高橋くんと青木くんは $ n $ 頂点の根付き木を使ったゲームをします。 木の頂点には $ 1 $ から $ n $ の整数がふられています。 この木の根は頂点 $ 1 $ であり、$ v=2,\dots,n $ について、頂点 $ v $ の親は $ p_v $ です。 最初、各頂点にコインが $ 1 $ 枚ずつ置かれています。また、頂点 $ 1 $ にコマが置かれています。

高橋くんと青木くんは、高橋くんから始めて交互に、以下の操作を行います。

- コマの置かれている頂点にコインがある場合、そのコインを獲得し、手番を終える。
- コマの置かれている頂点にコインがない場合、以下のルールでコマを動かす (またはゲームを終える)。
  - コマが置かれている頂点の子のうち、コインが置かれている頂点が存在するときは、そのうちのいずれかの頂点を選んでその頂点にコマを動かし、手番を終える。
  - 存在しない場合、コマが置かれている頂点が根ならゲームを終える。そうでないとき、コマが置かれている頂点の親にコマを動かし、手番を終える。

高橋くんも青木くんも、自分が獲得するコインの枚数を最大にするために最適な行動をします。高橋くんが獲得するコインの枚数を求めてください。

## 说明/提示

### 制約

- $ 2\le\ n\ \le\ 10^5 $
- $ 1\le\ p_v\ \lt\ v $

### Sample Explanation 1

どちらのプレイヤーにも選択肢が与えられず、必ず以下のようにゲームが進むため、高橋くんがすべてのコインを獲得します。 - 高橋くんが頂点 $ 1 $ に置かれたコインを獲得する。 - 青木くんがコマを頂点 $ 2 $ に動かす。 - 高橋くんが頂点 $ 2 $ に置かれたコインを獲得する。 - 青木くんがコマを頂点 $ 3 $ に動かす。 - $ \vdots $ - 高橋くんが頂点 $ 10 $ に置かれたコインを獲得する。 - 青木くんがコマを頂点 $ 9 $ に動かす。 - 高橋くんがコマを頂点 $ 8 $ に動かす。 - 青木くんがコマを頂点 $ 7 $ に動かす。 - $ \vdots $ - 高橋くんがコマを頂点 $ 2 $ に動かす。 - 青木くんがコマを頂点 $ 1 $ に動かす。 - ゲームを終える。

### Sample Explanation 2

まず、高橋くんが頂点 $ 1 $ に置かれたコインを獲得します。 その後、青木くんは頂点 $ 2 $ か頂点 $ 5 $ のどちらかにコマを動かすことができます。 もし頂点 $ 2 $ に動かした場合、青木くんは最終的に頂点 $ 5 $ に置かれたコインのみを獲得します。 一方で、頂点 $ 5 $ に動かした場合、青木くんは最終的に頂点 $ 2,3,4 $ に置かれたコインを獲得します。 青木くんは自分が獲得するコインの枚数を最大にするために最適な行動をするため、コマを頂点 $ 5 $ に動かすことを選びます。 よって、高橋くんが獲得するコインは $ 2 $ 枚です。

## 样例 #1

### 输入

```
10
1 2 3 4 5 6 7 8 9```

### 输出

```
10```

## 样例 #2

### 输入

```
5
1 2 3 1```

### 输出

```
2```

## 样例 #3

### 输入

```
10
1 1 3 1 3 6 7 6 6```

### 输出

```
5```

# 题解

## 作者：ShanQing (赞：6)

傻逼 szc 不会人均 C 来补了。感谢[这位老哥](https://www.luogu.com.cn/article/t1wjkgnp)的题解。

DP+贪心好题。设 $f_u$ 表示先手得到了 $u$ 上的硬币，即下一步**决策权在后手**，然后子树 $u$ 内**先手**能获得的最大收益。

首先显然的是这个过程形如 dfs，也就是一个子树不走完不会出来。

对于一个孩子 $v$，如果后手进了子树 $v$，那么根据规则可以得出，刚进到节点 $v$ 时 $v$ 的硬币还是被先手拿走，决策权还是在后手。也就是先手能获得 $f_v$，后手则获得 $sz_v-f_v$。

但是从 $v$ 出来回到 $u$ 后的决策权值得讨论。手模可以发现如果 $sz_v$ 为奇数则出来后决策权交换。否则不变。

根据上面两条规则，将所有的子树分成三类：
1. $sz_v$ 为偶数，且 $f_v<sz_v-f_v$，即后手也就是决策者选了子树 $v$ 后的收益比先手多。

2. $sz_v$ 为偶数，且 $f_v \geqslant sz_v-f_v$，即后手也就是决策者选了子树 $v$ 后的收益比先手少。

3. $sz_v$ 为奇数，代表后手选了子树 $v$ 出来后会交换决策权。

首先考虑 1 类点。显然这对后手是有利的。所以最优策略的第一步是后手将 1 类点全选了。

 2 类点对后手是不利的。所以要尽可能避免。那后手肯定要试图将这个点推给先手。具体地，后手选 3 类点。但是先手肯定也不想要这个对他不利的点，所以无疑会继续选 3 类点将 2 类点的决策推给后手。以此类推不断推脱，最后 3 类点肯定会选完。此时的“后手”也就是决策者就不得不选走全部 2 类点。由此可以得出，2 类点由谁选已经确定了。考虑 3 类点个数的奇偶性即可。

接下来考虑选 3 类点。由上面可以得出，3 类点被两名玩家轮流选取。对于一名玩家，由于决策者得到的是 $sz_v-f_v$ 而对方是 $f_v$，所以最优策略显然是选取 $(sz_v-f_v)-f_v$ 尽可能大的点。即尽可能让对方少得到收益。所以直接对 $(sz_v-f_v)-f_v$ 排序然后模拟即可。

## code

```cpp
#include <bits/stdc++.h>
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=1e5+5,INF=2e9,mod=1e9+7;
int n,m;
vector<int> e[N];
int f[N],sz[N];

void dfs(int u) {
	sz[u]=f[u]=1;
	int tot=0,cnt=0;priority_queue<pii> q;
	for(auto to:e[u]) {
		dfs(to),tot^=(sz[to]&1),sz[u]+=sz[to];
	} 
	for(auto to:e[u]) {
		if(!(sz[to]&1)) {
			if(f[to]<sz[to]-f[to]||f[to]>=sz[to]-f[to]&&!tot) f[u]+=f[to];
			else f[u]+=sz[to]-f[to];
		}
		else q.push({sz[to]-2*f[to],f[to]});
	}
	while(!q.empty()) {
		if(!(cnt&1)) f[u]+=q.top().se;
		else f[u]+=q.top().fi+q.top().se;
		q.pop(),++cnt;
	}
}

int main()
{
	scanf("%d",&n);
	int v;
	for(int i=2;i<=n;++i) {
		scanf("%d",&v);
		e[v].emplace_back(i);
	}
	dfs(1);
	printf("%d\n",f[1]);
	return 0;
}
```

---

## 作者：iiiiiyang (赞：4)

[这篇博客的摘要好有意思](https://www.cnblogs.com/LittleTwoawa/p/17232451.html)

[题目链接](https://www.luogu.com.cn/problem/AT_arc112_c)

题目里面的注意点还是很多的，如果读错了题整个思路可能会一点都不对。首先是移动和选取硬币的操作是分开的，所以移动到了一个有硬币的节点，将是你的对手获得硬币。然后移动和拿取都是单次操作的，进行后就换人了。

如果要使总答案最优，那每个节点的决策都要最优。选择了一个节点就要决策完他的整个子树。因此考虑树形 DP，我们用儿子来推父亲，当决策一个节点的时候，他的子节点信息我们都已经知道。

设 $g_i$ 表示点 $i$ 的子树大小，$f_i$ 表示在当前节点先手能够得到的最多硬币，那么后手能够得到的最多硬币我们记为 $h_i = g_i - f_i$。

模拟几个小数据，假设一个人选择了当前的一个子节点 $i$ 进入，能够发现当 $g_i$ 为奇数时，回到 $i$ 的父亲后变成他的对手进行子节点的选择；当 $g_i$ 为偶数时，回到 $i$ 的父亲后仍为他自己选择下一个进入的子节点。

所以一个节点如果有奇数个 $g$ 为奇数的子节点，最后会交换决策权；偶数个 $g$ 为奇数的子节点，决策权不变。

我们对子节点的状态分类讨论，均假设为先手拿取了该节点 $i$ 的硬币，接下来该由后手决策进入哪个子节点 $j \in son_i$：

1. $g_j$ 为偶数且 $f_j < h_j$，那么对于后手来说这个节点肯定是有利的，因为他能拿得多，还能回来后继续操控局面，所以只要有这类节点，后手必定会选，此类节点的转移方程为 $f_i = f_i + f_j$。
2. $g_j$ 为偶数且 $f_j \geq h_j$，那么对于后手来说这个节点不是亏的就是没有贡献，所以会尽量避免选这类节点，此类节点的转移为 $f_i = f_i + h_j$。
3. $g_j$ 为奇数，注意到选择了这类节点后会交换决策权，所以后手会尽量选择优秀的节点，即能让他比对手拿得更多的节点，即 $h_i - f_i$ 尽可能大的节点。

所以整个游戏的流程至此我们能够确定下来了：先拿第一类节点，然后拿第三类节点。判断一下第三类节点总数的奇偶性，看选完第三类节点后会不会交换决策权，从而看第二类节点的贡献到底是给先手还是后手。

整个遍历流程是 $\mathcal O(n)$ 的复杂度，由于需要我们决策具体哪个第三类节点更优，这里选择使用优先队列，所以总复杂度为 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=100010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int n,x;
    vector<int> G[MAX];
    int siz[MAX],f[MAX];
    priority_queue<pii> q;
    
    inline void mian()
    {
    	read(n);
    	for(int i=2;i<=n;++i) read(x),G[x].eb(i);
    	
    	auto dfs=[&](auto dfs,int now)->void
    	{
    		siz[now]=1; int tot=0,cnt=0;
    		for(auto to:G[now]) dfs(dfs,to),siz[now]+=siz[to],tot^=siz[to]&1;
    		f[now]=1;
    		for(auto to:G[now])
    		{
    			if(siz[to]&1) q.emplace(mp(siz[to]-2*f[to],f[to]));
    			else
    			{
    				if(f[to]<siz[to]-f[to]||(f[to]>siz[to]-f[to]&&(!tot))) f[now]+=f[to];
    				else f[now]+=siz[to]-f[to];
				}
			}
			while(!q.empty()) {++cnt,f[now]+=q.top().se; if(!(cnt&1)) f[now]+=q.top().fi; q.pop();}
		};
		dfs(dfs,1);
		
		write(f[1],'\n');
	}
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::mian();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：AC_love (赞：2)

设 $f(i, 0 / 1)$ 表示在 $i$ 子树中，先手刚刚吃掉了 $i$ 号点的香蕉，此时轮到后手操作，先手 / 后手能吃到的香蕉数。

然后我们要先搞清楚一个问题：从 $i$ 走到 $i$ 的某棵子树，最后回到 $i$ 后，由谁操作。

考虑到：$i$ 的这棵子树每条边都被经过了两次（从上到下一次，从下到上一次），因此边数不影响子树操作数的奇偶性。

由于停留在每个节点都会吃一根香蕉，所以只有子树内节点个数决定了操作数的奇偶性。

如果子树内有偶数个节点，那么 $i$ 下去时谁先行，回到 $i$ 时仍然是谁先行。如果子树内有奇数个节点，那么 $i$ 下去时谁先行，回到 $i$ 时他就变成后走的人。

因此，如果子树内有偶数个节点，相当于后手走完子树回来仍然掌握主动权。反之则将主动权让给先手。

我们将子树分为几类讨论：

1. $sz_x$ 为偶数，且 $f(x, 0) \le f(x, 1)$。
2. $sz_x$ 为偶数，且 $f(x, 0) > f(x, 1)$。
3. $sz_x$ 为奇数。

对于 $1$ 类点，显然后手会全选到。

对于 $2$ 类点，两个人都不想选。

两个人都不想选 $2$ 类点，因此他们会轮流选 $3$ 类点，直到选完为止。最后轮到谁操作谁就会选完所有 $2$ 类点。

接下来考虑 $3$ 类点怎么选。

显然两个人会优先选 $f(x, 1) - f(x, 0)$ 最大的 $3$ 类点，排序之后轮流选即可。

一路转移上去，最后答案为 $f(1, 0)$。

[code](https://atcoder.jp/contests/arc112/submissions/59746825)

---

## 作者：Xy_top (赞：1)

一道简单的有趣分类讨论题。

很容易想到分先后手讨论，如果一个子树内节点的个数为偶数，那么谁操纵当前的节点进入这个子树，出来后继续做选择的还是他，反之也成立。

考虑用 DP 解决这个问题，设 $f_u$ 为以 $u$ 为根的子树，初始决策的人的期望得分，$g_u$ 为初始不决策的那个人的期望得分。当前的人会怎么决策呢，显然他会保留他的决策权，先去选择那些不会反转先后手状态的东西，如果这些东西里有 $v$ 使得 $f_v >g_v$，那么先把它选掉。

接着考虑 $f_v<g_v$ 又不会改变先后手状态的，显然的，选这个相当于先后手没变，反而拉近了决策者和对方的分数差，所以决策者一定不会这么傻，除了没有节点可供选择。

如果会反转先后手状态，那么还是先选 $f_v>g_v$ 的优，这十分显然，还有药选择 $f_v-g_v$ 最大的，使分数差进一步的拉开。

总结如下：

先选择不会改变先后手状态又是 $f_v>g_v$ 的点，然后选择会改变先后手状态的点，最后选择不会改变先后手状态的点又是 $f_v<g_v$ 的点。

过程中还是进行排序贪心。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n;
int f[100005], g[100005], sz[100005];
//f[u]：从 u 出发，先手的期望得分
//g[u]：从 u 出发，后手的期望得分
vector <int> G[100005];
struct Node {int x, y;};
bool cmp (Node n1, Node n2) {return n1.x - n1.y > n2.x - n2.y;}
void dfs (int u) {
	vector <Node> a[2];
	g[u] = sz[u] = 1;
	for (int v : G[u]) {
		dfs (v);
		sz[u] += sz[v];
		a[sz[v] & 1].push_back ({f[v], g[v]});
	}
	sort (a[0].begin (), a[0].end (), cmp);
	sort (a[1].begin (), a[1].end (), cmp);
	int l0 = 10000000;
	For (i, 0, (int) (a[0].size () ) - 1) {
		if (a[0][i].x >= a[0][i].y) {
			f[u] += a[0][i].x;
			g[u] += a[0][i].y;
		} else {
			l0 = i;
			break;
		}
	}
	bool fi = 1;
	For (i, 0, (int) (a[1].size () ) - 1) {
		if (fi) {
			f[u] += a[1][i].x;
			g[u] += a[1][i].y;
		} else {
			g[u] += a[1][i].x;
			f[u] += a[1][i].y;
		}
		fi = !fi;
	}
	For (i, l0, (int) (a[0].size () ) - 1) {
		if (fi) {
			f[u] += a[0][i].x;
			g[u] += a[0][i].y;
		} else {
			g[u] += a[0][i].x;
			f[u] += a[0][i].y;
		}
	}
}
void solve () {
	cin >> n;
	For (i, 2, n) {
		int x;
		cin >> x;
		G[x].push_back (i);
	}
	dfs (1);
	cout << g[1];
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：TLE_AK (赞：0)

一种或许更顺畅的思路？
### 题意
给一棵树与一颗在 $1$ 号点的棋子，alice 与 bob 轮流进行操作（设棋子在 $u$ 号节点）：
- 若 $u$ 号节点没有标记，$u$ 号节点打上标记并为操作者加一分。
- 否则，若 $u$ 号节点有没标记的儿子，可以选择一个转移。
- 否则，返回父亲，若此时 $u$ 已经为根，游戏结束。
## 思路
由于操作仅在选择去哪个儿子的时候是自由的，不如设选择去儿子的那方为先手，什么情况下先后手产生改变。

很容易发现，仅当去的儿子子树为奇数时才会变先后手，同时子树的结果不会被父亲改变。  
设 $dp_{i}$ 表示节点 $i$ 的子树内先手最多取到多少香蕉，$size_{i}$ 表示节点 $i$ 子树大小。  
有转移方程： 
- 当 $sz_v$ 为偶数，$dp_{v}>size_v-dp_{v}$，此时先手必定选择（反正先后不变）
- 当 $sz_v$ 为偶数，$dp_{v}<size_v-dp_{v}$，此时先手必定不选择（除非只能选这个，理由同上）
- 当 $sz_v$ 为奇数，此时选择 $dp_{v}-(size_{v}-dp_{v})$ 最大的节点，因为此时等同于一个零和博弈（更容易拉出差距），所以选这种。
然后 dp 时对儿子以 $dp_{v}-(size_{v}-dp_{v})$ 为关键字排序，其余直接计算即可。
### 代码
```
#include<bits/stdc++.h>
using namespace std;

namespace acac
{
	int dp[100010],sz[100010];
	
	struct node
	{
		int id,val;
	};
	
	bool cmp(node a,node b)
	{
		return a.val>b.val;
	}
	
	struct edge
	{
		int to,ne;
	}e[200010];
	int H[100010];
	int cnt;
	
	void add(int a,int b)
	{
		e[++cnt].to=b;
		e[cnt].ne=H[a];
		H[a]=cnt;
	}
	
	void dfs(int u,int fa)
	{
		sz[u]=1;
		vector<node>q;
		int bad=0,all=0;
		for(int i=H[u];i;i=e[i].ne)
		{
			int v=e[i].to;
			if(v==fa)continue;
			dfs(v,u);
			sz[u]+=sz[v];
			if(sz[v]&1)q.push_back({v,dp[v]*2-sz[v]});
			else if(sz[v]-dp[v]<dp[v])dp[u]+=dp[v];
			else bad+=dp[v],all+=sz[v];
		}
    //排序
		sort(q.begin(),q.end(),cmp);
    //先轮流选
		bool tf=1;
		for(int i=0;i<q.size();i++)
		{
			int v=q[i].id;
			if(tf)dp[u]+=dp[v];
			else dp[u]+=sz[v]-dp[v];
			tf^=1;
		}
    //处理第2种情况
		if(tf)dp[u]+=bad;
		else dp[u]+=all-bad;
	}

	int main()
	{
		int n;
		scanf("%d",&n);
		for(int i=2;i<=n;i++)
		{
			int a;
			scanf("%d",&a);
			add(a,i),add(i,a);
		}
		dfs(1,0);
        //贡献取反
		cout<<n-dp[1];
		return 0;
	}
}

int main()
{
	acac::main();
	return 0;
}
```

---

