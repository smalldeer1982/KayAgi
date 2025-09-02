# [ARC161C] Dyed by Majority (Odd Tree)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc161/tasks/arc161_c

$ N $ 頂点の木が与えられます． 頂点には $ 1 $ から $ N $ までの番号が付いており，$ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます． また，すべての頂点について，**接続する辺の本数は奇数**です．

与えられた木の各頂点を黒 ( `B` ) か白 ( `W` ) のいずれかの色で塗ります． このとき，「各頂点の色（ `B` または `W` ）を頂点の番号順に並べて得られる文字列」を**色の列**と呼びます．

色の列 $ S $ が与えられます． すべての頂点に色が塗られた状態で以下の操作を $ 1 $ 回行った結果，色の列が $ S $ となることがあり得るかどうかを判定し，あり得るなら操作を行う前の色の列として適切なものを $ 1 $ つ求めてください．

**操作:** 各頂点 $ k\ =\ 1,\ 2,\ \dots,\ N $ に対して，辺で結ばれた頂点の色のうち過半数を占めるものを $ C_k $ とする． すべての頂点について同時に，頂点 $ k $ の色を $ C_k $ に塗り替える．

$ T $ 個のテストケースが与えられるので，それぞれについて答えてください．

## 说明/提示

### 制約

- $ T\ \geq\ 1 $
- $ N\ \geq\ 2 $
- $ 1 $ つの入力に含まれるテストケースについて，$ N $ の総和は $ 2\ \times\ 10^5 $ 以下である．
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N\ (1\ \leq\ i\ \leq\ N\ -\ 1) $
- 与えられる辺 $ (A_i,\ B_i)\ (1\ \leq\ i\ \leq\ N\ -\ 1) $ は木をなす．
- 各頂点 $ k\ (1\ \leq\ k\ \leq\ N) $ は $ A_i,\ B_i\ (1\ \leq\ i\ \leq\ N\ -\ 1) $ として**合計奇数回**現れる．
- $ S $ は `B`, `W` からなる長さ $ N $ の文字列である．
 
### Sample Explanation 1

$ 1 $ つ目のテストケースについて，操作を行う前の色の列が `WBBW` であったとします． このとき， - 頂点 $ 1 $ について，辺で結ばれた頂点 $ 2,\ 3,\ 4 $ の色はそれぞれ `B`, `B`, `W` であり，過半数を占めるのは $ C_1\ =\ {} $`B`， - 頂点 $ 2 $ について，辺で結ばれた頂点 $ 1 $ の色は `W` であり，過半数を占めるのは $ C_2\ =\ {} $`W`， - 頂点 $ 3 $ について，辺で結ばれた頂点 $ 1 $ の色は `W` であり，過半数を占めるのは $ C_3\ =\ {} $`W`， - 頂点 $ 4 $ について，辺で結ばれた頂点 $ 1 $ の色は `W` であり，過半数を占めるのは $ C_4\ =\ {} $`W` となります． したがって，操作後の色の列は `BWWW` となり，条件を満たします． 同様に，操作前の色の列が `WBBB`, `WBWB`, `WWBB` であった場合にも，操作後の色の列は `BWWW` となり，これらのうちどれを出力しても正答と見なされます。 $ 2 $ つ目のテストケースについて，入力された木において操作を行った結果，色の列が `BBWW` となることはあり得ません．

## 样例 #1

### 输入

```
2
4
1 2
1 3
1 4
BWWW
4
1 2
1 3
1 4
BBWW```

### 输出

```
WBBW
-1```

# 题解

## 作者：良心WA题人 (赞：4)

## 前言

简单题，基本上就是一个模拟的过程。不太理解为什么比 $D$ 过的少，可能大家比较会猜结论？

## 题意

给定一棵树，要求你给每个点确定一个颜色（两个中的一个
），使得最后将每个点变成与其相邻的点中颜色数量更多的一个颜色后为给定的颜色序列。

## 思路

首先一个比较明显的点就是叶子只会影响它的父亲，所以直接将叶子钦定为父亲的颜色即可，而叶子只会被父亲影响，所以叶子的父亲必须确定为叶子的颜色。

那么现在我们已经确定了一些的颜色，我们可以直接把影响考虑到上面的点并删去这些点，这时我们又有了新的叶节点，又可以再进行类似的处理。那么，这个问题就变得平凡了。

具体的，我们可以考虑一个点的所有儿子，先将孩子中能够确定的颜色确定了，然后再将无所谓的所有儿子确定为自己的颜色。若最终自己的颜色和另一种颜色数量相同，则将父亲设为自己的颜色，否则父亲为不确定的颜色。最后别忘记若根节点无法确定则随机设一个颜色。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
vector<int>g[NN];
char s[NN],col[NN];
bool dfs(int u,int fa)
{
	int cnt=0;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa)
			continue;
		if(!dfs(v,u))
			return false;
		if(!col[v])
			col[v]=s[u];
		if(col[v]==s[u])
			cnt++;
	}
	if(cnt<g[u].size()/2)
		return false;
	if(cnt==g[u].size()/2)
	{
		if(!fa||col[fa]&&col[fa]!=s[u])
			return false;
		col[fa]=s[u];
	}
	return true;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			g[i].clear();
			col[i]='\0';
		}
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		scanf("%s",s+1);
		if(!dfs(1,0))
		{
			puts("-1");
			continue;
		}
		if(!col[1])
			col[1]='B';
		for(int i=1;i<=n;i++)
			putchar(col[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：luohanzhao (赞：3)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_arc161_c)

[ATC题目传送门](https://atcoder.jp/contests/arc161/tasks/arc161_c)

赛场上多测清空清错了...

考虑贪心。我们发现一个点可能有很多个儿子结点，但最多只会有一个父亲结点。所以我们可以把点的形态大体上分为三类：

1. 叶子结点（只有父亲结点没有儿子结点）；
1. 根结点（没有父亲结点只有儿子结点）；
1. 其他结点（有父亲结点且有儿子结点）。

对于一个叶子结点来说，它的最终颜色由它的父亲决定，所以我们可以给它的父亲上传一个需求，表示它需要它的父亲是这个颜色。

对于一个其他结点来说，它的颜色大体上由它的儿子结点决定，但当儿子结点的两种颜色数量相等时，也要向它的父亲上传一个需求，表示它需要它的父亲是这个颜色。

对于根结点来说，它的颜色完全由它的儿子结点决定，无法再向上上传需求。

我们发现叶子结点可以看做是其他结点 **儿子结点的两种颜色数量相等** 的情况，根结点由于一定有奇数个结点，所以不存在 **儿子结点的两种颜色数量相等** 的情况。所以我们可以把三种情况合三为一。

对于一个点，若是它的儿子没有需求的话，那么我们贪心地把它的初始颜色设为它父亲节点的最终颜色，这样做首先儿子不会有问题，其次还可以尽可能地满足父亲的需求。

时间复杂度 $O(N)$。

### CODE

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
const int N = 5e5 + 5;
int n, ok, col[N], tag[N], ans[N];
char a[N];
inline int read()
{
    int x(0), f(1); char ch(getchar());
    while(!isdigit(ch))f = (ch == '-'? -1: f), ch = getchar();
    while( isdigit(ch))x = x * 10 + ch - '0' , ch = getchar();
    return x * f;
}
int head[N], cnt, son[N], cnt_node[N][2];
int ask[N][2];
struct edge{int v, nxt;}e[N << 1];
void adde(int x, int y)
{
    e[++cnt] = {y, head[x]}, head[x] = cnt;
    e[++cnt] = {x, head[y]}, head[y] = cnt;
}
void dfs(int u, int f)
{
    for(int i(head[u]); i; i = e[i].nxt)
    {
        int v(e[i].v);
        if(v == f)continue;
        son[u]++, dfs(v, u);
    }
    if(cnt_node[u][col[u]] * 2  <  son[u])return void(ok = 0);//算上他父亲也不行
    if(cnt_node[u][col[u]] * 2  == son[u])ask[f][col[u]]++;//上传需求
    if(ask[u][1] && ask[u][0])return void(ok = 0);//它不能同时拥有两种颜色
    if(ask[u][1] || ask[u][0])ans[u] = (ask[u][1] != 0);//满足儿子的需求
    else ans[u] = col[f];//若没有需求，贪心地改为父亲的最终颜色
    cnt_node[f][ans[u]]++;//计数器++
}
void init()
{
    ok = 1, cnt = 0;
    for(int i(1); i <=n; i++)
        col[i] = ans[i] = son[i] = head[i] = 0,
        cnt_node[i][0] = cnt_node[i][1] = 0,
        ask[i][0] = ask[i][1] = 0;
}
signed main()
{
    for(int t(read()); t; t--)
    {
        init();
        n = read();
        for(int i(1); i < n; i++)adde(read(), read());
        scanf("%s", a + 1);
        for(int i(1); i <= n; i++)col[i] = (a[i] == 'W');
        dfs(1, 0);
        if(!ok){cout << "-1\n"; continue;}
        for(int i(1); i <= n; i++)cout << (ans[i] == 1? "W": "B");
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

贪心，从深往浅色，优先满足儿子的需求。

我们给节点定义两种状态：固定和不固定。

令与节点 $u$ 直连的点个数为 $siz_u$，节点 $u$ 的直连儿子中颜色与 $u$ 期望颜色相同的点个数为 $cnt_u$。

当一个节点 $u$ 的颜色不直接由其父亲的颜色决定时，它就是不固定的，即只考虑其儿子的颜色就能使其染上它的期望颜色（即 $cnt_u>\lfloor \frac{siz_u}{2}\rfloor$）；否则，它就是固定的，父亲的颜色可以直接决定它的颜色（即 $cnt_u=\lfloor \frac{siz_u}{2}\rfloor$）。

叶子节点只与其父亲相连，所以父亲的颜色必须是它的期望颜色。

当一个节点处于固定状态时，我们贪心地将它父亲的颜色染为它的期望颜色，当然，如果它父亲已经被染过颜色，且和自己的期望颜色不同的话，那就无解了。

注意根节点不固定的情况，这时候给它随便染一个颜色即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back

#define N 202502
// #define int long long

int t,n;
char a[N];
vector<int>e[N];
char ans[N];

inline bool dfs(int k,int fa){
    int siz=e[k].size(),cnt=0;

    for(int x:e[k]){
        if(x==fa){
            continue;
        }

        if(!dfs(x,k)){
            return 0;
        }

        if(!ans[x]){
            ans[x]=a[k];
        }

        if(ans[x]==a[k]){
            cnt++;
        }
    }

    if(cnt<siz/2){
        return 0;
    }

    if(cnt==siz/2){
        if(!fa||(ans[fa]&&ans[fa]!=a[k])){
            return 0;
        }

        ans[fa]=a[k];
    }

    return 1;
}

inline void sol(){
    cin>>n;

    int u,v;

    rep(i,1,n){
        e[i].clear();
    }

    rep(i,1,n-1){
        cin>>u>>v;
        e[u].pb(v);
        e[v].pb(u);
    }

    rep(i,1,n){
        ans[i]=0;

        cin>>a[i];
    }

    if(dfs(1,0)){
        if(!ans[1]){
            ans[1]='B';
        }

        rep(i,1,n){
            cout<<ans[i];
        }
        cout<<"\n";
    }
    else{
        cout<<"-1\n";
    }
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>t;
    while(t--){
        sol();
    }

    return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

可以用 ARC156_C 一样的方式，直接剥叶子。

我们找到一个非一度点来作为根（当然点数为 $2$ 时你要特判）。不难发现 $n>2$ 时一定存在一个点其度数不为 $1$。

发现叶子节点已经将其父亲节点的初始颜色给确定了，通过这个性质继续往下想。

一个节点可能会有两种情况：初始颜色已被确定或未被确定，不难发现如果一个点初始颜色未被确定，直接将其初始颜色钦定为父亲节点的目标颜色一定不劣。

想想初始颜色在钦定之前就被确定可能是发生了什么，必然是儿子节点为了达到其目标颜色而确认父亲。

所以直接 DFS 一次就行了。

```cpp
#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N=2e5+10;
int T,n,col[N],fg,c[N],rt;char x;
vector < int > v[N];

inline void Set(int x,int y){
	if(c[x]==-1||c[x]==y) c[x]=y;
	else fg=1;
}
void dfs(int x,int y){
	if((int)v[x].size()==1){Set(y,col[x]);return ;}
	int c0=0,c1=0;
	for(int i:v[x]){
		if(i==y) continue;
		dfs(i,x);if(!~c[i]) c[i]=col[x];
		c0+=!c[i];c1+=c[i];
	}
	if(c0==c1) Set(y,col[x]);
	else if((c0<c1)^col[x]) fg=1;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;memset(c,-1,sizeof(c));
	while(T--){
		cin>>n;fg=0;
		for(int i=1,x,y;i<n;++i){cin>>x>>y;v[x].emplace_back(y);v[y].emplace_back(x);}
		for(int i=1;i<=n;++i){cin>>x;col[i]=(x=='B');}
		if(n==2){
			for(int i=2;i;--i) cout<<(col[i]?'B':'W');
		}else {
			rt=0;for(int i=1;i<=n;++i) if((int)v[i].size()>=2) rt=i;
			dfs(rt,0);
			if(fg) cout<<"-1";
			else {for(int i=1;i<=n;++i) cout<<(c[i]?'B':'W');}
		}
		for(int i=1;i<=n;++i) v[i].clear(),c[i]=-1;
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

记 $0$ 为 W，$1$ 为 B。

考虑贪心的遍历，用 dfs 函数返回 $0/1/2$ 代表这个点必须选 $0$，必须选 $1$，没有限制，然后每次遍历 $u$ 的所有儿子后把 $u$ 的所有没有限制的儿子的颜色改为 $u$ 的颜色，然后判断与 $u$ 相连 $0/1$ 颜色的节点数量是否相等来决定父亲节点的颜色。

时间 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = ll; using i64 = ll; using i128 = __int128_t;
using namespace std;
const i32 N = 1e6 + 5;
i32 n, u, v, ok, flg[N];
char col[N];
string s;
vec G[N];
fn bool dfs(i32 u, i32 fa) {
  i32 cnt = 0;
  for (i32 v : G[u]) {
    if (v == fa) continue;
    if (!dfs(v, u)) return 0;
    if (!col[v]) col[v] = s[u];
    if (col[v] == s[u]) cnt++;
  }
  if (cnt < (G[u].size() >> 1)) return 0;
  if (cnt == (G[u].size() >> 1)) {
    if (!fa || col[fa] && col[fa] != s[u]) return 0;
    col[fa] = s[u];
  }
  return 1;
}
fv sol() {
  cin >> n;
  rep (i, 1, n) G[i].clear(), col[i] = '\0';
  rep (i, 1, n - 1) cin >> u >> v, G[u].pb(v), G[v].pb(u);
  cin >> s; s = " " + s;
  if (!dfs(1, 0)) return (void)(cout << "-1\n");
  if (!col[1]) col[1] = 'B';
  rep (i, 1, n) cout << col[i];
  cout << "\n";
}
int main() {
  i32 T = 1;
  cin >> T;
  while (T--) sol();
}
```

---

## 作者：CrTsIr400 (赞：0)

## [[ARC161C] Dyed by Majority (Odd Tree)](https://www.luogu.com.cn/problem/AT_arc161_c)

很好玩。

首先叶子节点的所有父亲的**初始颜色**一定是和叶子的**目标颜色**相等的。若不相等请输出 $-1$。

类似的，我们把所有叶子的初始颜色设成其父亲节点的初始颜色。

于是我们确定了最后两层的颜色，其中所有叶子节点都可以丢弃了。

这就是此题的突破口。

---

想想对于其他层有没有类似的做法。

先把颜色设为**三种状态**，$-1$ 表示不确定，还有 $0$ 和 $1$。

比如 $p$ 节点的初始颜色先别管它，管管它子节点的颜色，先把确定的算上，不确定的强制赋为目标颜色。

然后如果子节点中目标颜色不够，那么就把它的父亲节点设为目标颜色；够了就填不确定。

如果还不够，那么就输出 $-1$。

---

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(auto i(a),_ei(b);i<=_ei;++i)
#define gch(w) for(;w(CH);CH=getchar())
using I=int;using V=void;using LL=long long;I FL,CH;LL in(){LL a(0);FL=1;gch(!isdigit)FL=(CH=='-')?-1:1;gch(isdigit)a=a*10+CH-'0';return a*FL; }using namespace std;
const I N=2e5+10;
vector<I>e[N];
I n;
bool ansis;
I b[N],op[N];
V dfs(I x,I fa=0){I cnt[2]={},opX=op[x];
	for(I y:e[x])if(y^fa){
		dfs(y,x);if(~b[y])++cnt[b[y]];}
	for(I y:e[x])if(y^fa){
		if(b[y]==-1)b[y]=opX,++cnt[opX];}
	if(cnt[opX]<cnt[!opX])ansis=0;
	if(cnt[opX]==cnt[!opX]&&fa){I&fx=b[fa];
		if(fx!=-1&&fx!=opX)ansis=0;
		fx=opX;}
}I main(){I T=in();
	while(T--){
		n=in();fo(i,1,n)e[i].clear(),e[i].shrink_to_fit(),b[i]=-1;
		fo(i,2,n){I x=in(),y=in();
			e[x].push_back(y);e[y].push_back(x);}
		fo(i,1,n){gch(!isalpha);
			op[i]=(CH=='B')?1:0;
			CH=getchar();}
		ansis=1;dfs(1);
		if(!ansis)puts("-1");
		else{fo(i,1,n)putchar(b[i]?'B':'W');
		puts("");}
	}
	return 0;
}
```



---

