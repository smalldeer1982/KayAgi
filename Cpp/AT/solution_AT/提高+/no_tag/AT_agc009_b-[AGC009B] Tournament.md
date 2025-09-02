# [AGC009B] Tournament

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jrex2017/tasks/agc009_b

$ N $ 人の人が大会に出場しました。この大会はトーナメント形式であり、$ N-1 $ 回の試合が行われました。 諸事情により、このトーナメントは全参加者に平等に組まれているとは限りません。 すなわち、各人に対し、優勝するために必要なその人が勝者となるような試合数が等しいとは限りません。 トーナメントの構造は、正式には問題文の末尾で定義されます。

各試合では必ず片方の人が勝者、もう片方の人が敗者となり、最後まで負けなかった $ 1 $ 人が優勝となります。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc009_b/60b2a9eae65eb70a75e8c33bcbb94cf7111ee45a.png)図: トーナメントの例

 

人には $ 1 $ から $ N $ までの番号がついており、$ 1 $ 番の人が優勝し、優勝者以外の人 $ i(2\ ≦\ i\ ≦\ N) $ は人 $ a_i $ との試合で負けました。

トーナメントの深さとは、すべての人に対する、その人が優勝するために必要な、その人が勝者となるような試合数の最大値です。

トーナメントの深さとしてありうる最小の値を求めてください。

トーナメントの構造の正式な定義は以下の通りです。$ i $ 回目の試合では、

- あらかじめ決められた、まだ試合をしていない $ 2 $ 人の人
- あらかじめ決められたまだ試合をしていない人 $ 1 $ 人と、あらかじめ決められた $ j(j\ <\ i) $ に対する、$ j $ 回目の試合の勝者
- あらかじめ決められた $ j,k(j,k\ <\ i,\ j\ ≠\ k) $ に対する、$ j $ 回目の試合の勝者と $ k $ 回目の試合の勝者

のうちのいずれかの $ 2 $ 人が試合を行います。このような構造であって、どのように試合結果を決めても、すでに一度試合に負けた人が再び試合をすることのないようなものをトーナメントと呼びます。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ a_i\ ≦\ N(2\ ≦\ i\ ≦\ N) $
- 入力の試合結果と合致するようなトーナメントが存在する

### Sample Explanation 1

次のような試合結果が条件を満たします。 - $ 1 $ 回目の試合では、人 $ 4 $ と 人 $ 5 $ が対戦し、人 $ 4 $ が勝つ - $ 2 $ 回目の試合では、人 $ 2 $ と 人 $ 4 $ が対戦し、人 $ 2 $ が勝つ - $ 3 $ 回目の試合では、人 $ 1 $ と 人 $ 3 $ が対戦し、人 $ 1 $ が勝つ - $ 4 $ 回目の試合では、人 $ 1 $ と 人 $ 2 $ が対戦し、人 $ 1 $ が勝つ !\[783f7be9c88350e31963edba8a958879.png\](https://atcoder.jp/img/agc009/783f7be9c88350e31963edba8a958879.png) このトーナメントは、人 $ 5 $ が優勝するためには $ 3 $ 回勝利する必要があるので、深さ $ 3 $ のトーナメントとなります。 逆に、深さ $ 2 $ 以下の条件を満たすトーナメントは存在しないので、$ 3 $ を出力します。

## 样例 #1

### 输入

```
5
1
1
2
4```

### 输出

```
3```

## 样例 #2

### 输入

```
7
1
2
1
3
1
4```

### 输出

```
3```

## 样例 #3

### 输入

```
4
4
4
1```

### 输出

```
3```

# 题解

## 作者：BigJoker (赞：2)

# Solution

考虑树形 DP。

将赢家作为父亲，输家作为儿子，就可以得到一棵树。（~~感觉这意思曲解起来好奇怪啊~~）

令 $f_i$ 为 $i$ 号选手打败他需要的人所用的最少层数。

令 $s$ 为 $i$ 的子节点。

并且所有的 $f_s$ 已经从小到大排好了序。

那么：

$f_i\gets \max\{f_i,f_s\}+1$

$f_i$ 是实时更新的，最后输出就好了。

# Code

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
const int N=1e5+5;
int n,x,ans,a[N],us[N];
vector<int>win[N],fac[N];
void DFS(int pos){
	for(re int i=0;i<win[pos].size();i++) DFS(win[pos][i]),fac[pos].push_back(us[win[pos][i]]);
	sort(fac[pos].begin(),fac[pos].end());
	for(re int i=0;i<win[pos].size();i++) us[pos]=max(us[pos],fac[pos][i])+1; 
}
int main(){
	scanf("%d",&n);
	for(re int i=2;i<=n;i++) scanf("%d",&a[i]),win[a[i]].push_back(i);
	DFS(1);
	printf("%d",us[1]);
	return 0;
}
```

---

## 作者：WorldMachine (赞：1)

比较好想的树形 dp。

输者向打败他的人连边，形成了一棵有根树。设 $f_u$ 表示 $u$ 要赢所需的最小场数。$u$ 可以以任意顺序击败它的儿子，当加入一个儿子 $v$ 时有：
$$
f_u\leftarrow\max(f_u,f_v)+1
$$
贪心，将所有儿子按照 $f$ 从小到大排序即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, f[N];
vector<int> G[N];
void dfs(int u) {
	for (int v : G[u]) dfs(v);
	sort(G[u].begin(), G[u].end(), [](int x, int y) { return f[x] < f[y]; });
	for (int v : G[u]) f[u] = max(f[u], f[v]) + 1;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 2, f; i <= n; i++) cin >> f, G[f].emplace_back(i);
	dfs(1), cout << f[1];
}
```

---

## 作者：SunsetLake (赞：1)

## 思路

注意到每个人（除了 $1$ 号）都会被淘汰一次，那么我们对每个被淘汰的人连一条有向边指向淘汰他的人，就会形成一个 DAG。考虑在 DAG 上做 dp。

把比赛看成很多层（像样例解释的图一样），每个人在每一层只能参加一场比赛，设 $f_i$ 表示第 $i$ 个人参加的最后一场比赛的最小层数，那么答案就是 $f_1$。

转移直接 $f_u \gets \max\{f_v + 1\}$，其中 $(v,u) \in E$。意思是 $u$ 必须和每个 $v$ 都打一场，最后一场就是最大的 $f_v$ 了。但是你会发现一个问题，$f_v$ 可能会有相同的数。而要求是在每一层一个人只能参赛一次。因此不能直接转移，需要把所有 $f_v + 1$ 先拿出来排序，将重复的一直 $+1$ 直到没有重复的数，这时的最大值即为 $f_u$。

实现时去看相邻两个数中有多少空位即可。复杂度 $O(n \log n)$。

## code


```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
int n,d[N],f[N];
vector<int>p[N];
vector<int>e[N];
queue<int>q;
int main(){
	cin >> n;
	for(int i = 2;i <= n;++ i){
		int x;
		cin >> x;
		e[i].pb(x);
		d[x] ++;
	}
	for(int i = 1;i <= n;++ i)
		if(!d[i]) q.push(i),f[i] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		if(p[u].size()){
			sort(p[u].begin(),p[u].end());
			int lst = 0,sum = 0;
			for(int i = 1;i < p[u].size();++ i){
				if(p[u][i] != p[u][i - 1]){
					int nw = p[u][i] - p[u][i - 1] - 1;
					lst += sum;
					lst -= nw;lst = max(lst,0);
					sum = 0;
				}
				else sum ++;
			}
			lst += sum;
			f[u] = p[u].back() + lst;
		}
		for(auto v : e[u]){
			p[v].pb(f[u] + 1);
			if(!-- d[v]) q.push(v);
		}
	}
	cout << f[1];
	return 0;
}

```

---

## 作者：Butterfly_qwq (赞：0)

首先，我们把比赛树建出来。

把所有父亲等于自己的点删掉，这个点的儿子全部变成父亲的儿子。

然后我们发现现在一个点的父亲就是淘汰这个点的人，证明显然。

于是树形 dp。

先设叶子节点高度为 $0$。

考虑将这个点还原。

有一个很明显的性质是：把所有父亲等于自己的点删掉的话，每个点最多只有 $1$ 个儿子。

显然我们可以给他的儿子排个序，于是 $dp_u=\max\limits_{i=1}^{cnt_u}dp_{son_{u,i}}+i$。

其中 $dp_i$ 表示 $i$ 的高度，$cnt_i$ 表示 $i$ 的儿子个数，$son_{i,j}$ 表示排序过后 $i$ 的第 $j$ 个儿子。

我们要尽可能的让答案小，那么按儿子的高度从大到小排序即可。

众所周知，[代码](https://atcoder.jp/contests/agc009/submissions/57623339)放题解里会不美观，所以请点链接查看。

---

## 作者：Antiluna (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc009_b)

模拟赛没做出来，joker。

当时想的是按照题目的图片建树，然后求深度。

但是这样是错误的。

因为要赢的场数最多，所以应该让深度更多，所以要按照“赢家当父亲，输家当儿子”的方式建树。

在求深度时需要从小到大排序。

一个需要注意的地方：在每次 dfs 时进行 ``v.clear()`` 是错误的，原因是 ``clear`` 函数仅仅是删除元素，并不会改变 ``begin()`` 和 ``end()`` 的位置，可以考虑使用 ``delete``。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,first[2000010],ct,dp[2000010];
struct node
{
	int to,next;
}tr[2000010];
void add(int x,int y)
{
	tr[++ct].to=y;
	tr[ct].next=first[x];
	first[x]=ct;
}
void dfs(int u,int fa)
{
	vector<int>tmp;
	for(int i=first[u];i;i=tr[i].next)
	{
		int v=tr[i].to;
		if(v==fa)continue;
		dfs(v,u);
		tmp.push_back(dp[v]);
	}
	sort(tmp.begin(),tmp.end());
	for(int i=0;i<tmp.size();i++)dp[u]=max(dp[u],tmp[i])+1;
}
signed main()
{
	scanf("%lld",bitand n);
	for(int i=2;i<=n;i++)scanf("%lld",bitand x),add(i,x),add(x,i);
	dfs(1,0);
	printf("%lld",dp[1]);
	return 0;
}
```

---

## 作者：win114514 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Al-lA/p/17763339.html)

### 思路

考虑树形 $\text{dp}$。

我们将每个人与把自己淘汰的人连边。

得到一颗以一为根的树。

由于我们需要求出必须赢的场数最多的那位选手，至少要赢多少场。

考虑最多的限制。

可以使用树型动态规划。

每一次两个人比赛的代价为：

$$dp_i=\max(dp_i,dp_j)+1$$

这样就达成了最多的限制。

考虑至少的条件。

我们容易发现其中一项一直都是 $dp_i$。

那么我们容易想到将 $dp_j$ 从小到大排序，就完成了最少的条件。

### Code

[AC记录](https://atcoder.jp/contests/jrex2017/submissions/46498013)

---

## 作者：_Flame_ (赞：0)

## 思路

很明显，将每一组给出的互有输赢的两方之间连边，赢的人为父亲，输的人为儿子，所有人之间的关系会形成一棵以 $1$ 为根的树。

设 $dp_i$ 为到第 $i$ 个点时的最大深度，则 $dp_i=\max (dp_i,dp_{son})+1$，其中 $son$ 为节点 $i$ 的儿子，具体实现时就排一下序取最大的值即可。

## Code

```cpp

#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=301000;
const int maxm=110;
const int mod=1e9+7;
const int inf=1e18;

int n;
int a[maxn];

int dp[maxn];

struct edge{
	int to,nxt;
}e[maxn<<2];

int head[maxn],tot;

void add(int u,int v){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	head[u]=tot;
}

void dfs(int u,int fa){
	vector<int> s;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs(v,u);
			s.push_back(dp[v]);
		}
	}
	sort(s.begin(),s.end());
	for(int i=0;i<s.size();i++){
		dp[u]=max(dp[u],s[i])+1;
	}
}

void solve(){
	n=read();
	for(int i=2;i<=n;i++){
		int x=read();
		add(i,x);
		add(x,i);
	}
	dfs(1,0);
	write(dp[1]);
	puts("");
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}



```

---

## 作者：Unnamed114514 (赞：0)

思路：树形 dp

对于一棵树，我们要求助这个树的所有子树的深度。贪心地，先挑战深度大的，再挑战深度小的，然后我们就可以得到这个子树的深度，具体思路可以采用树形 dp 实现，时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int f=0,res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		f|=(ch=='-');
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return f?-res:res;
}
const int maxn=1e5+5;
int n,a[maxn],dp[maxn],siz[maxn];
vector<int> _[maxn];
inline bool cmp(int a,int b){
	return dp[a]>dp[b];
}
inline void dfs(int u){
	if(siz[u]==0)
		return;
	for(int i=0;i<siz[u];++i)
		dfs(_[u][i]);
	sort(_[u].begin(),_[u].end(),cmp);
	for(int i=0;i<siz[u];++i)
		dp[u]=max(dp[u],dp[_[u][i]]+i+1);
}
int main(){
	n=read();
	for(int i=2;i<=n;++i){
		a[i]=read();
		_[a[i]].push_back(i);
		++siz[a[i]];
	}
	dfs(1);
	printf("%d\n",dp[1]);
	return 0;
} 
```

---

## 作者：tuliwei (赞：0)

**题意有毒**  
这题其实是要建一个像题目中给的图那样的东西，使最大深度最小  

我们将 A被B淘汰 视作A像B连一条父边，然后我们就得到了一棵树  
接下来对于每一个节点只要先处理出它所有儿子的答案，然后将这些儿子按其对应的答案从小到大排一遍序，依次 $ f[u] = max(f[u] + 1, f[son] + 1) $ ($u$为该节点，枚举son) 就好了

代码：
```cpp
#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fi first
#define se second
#define N 200005

using namespace std;
typedef pair<int,int> Pair;

inline int input() {
	int x; char ch; while (!isdigit(ch = getchar()));
	for (x = ch ^ 48; isdigit(ch = getchar()); x = x * 10 + (ch ^ 48));
	return x;
}

int n, fa[N], f[N];
vector<int> T[N];

inline bool cmp(int x, int y) { return f[x] < f[y]; }

void dfs(int u) {
	for (int v : T[u]) dfs(v); //处理所有儿子的答案
	sort(T[u].begin(), T[u].end(), cmp); //排序
	for (int v : T[u]) f[u] = max(f[u], f[v]) + 1; //转移
}

int main() {
//	freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
//	freopen("debug", "w", stderr);

	n = input();
	for (int i = 2; i <= n; ++i)
		fa[i] = input(), T[fa[i]].push_back(i);

	dfs(1);
	printf("%d\n", f[1]);
	return 0;
}
```

---

## 作者：Ebola (赞：0)

### 假做法

建一个$n$个点的图，连边$(i+1,x_i)$，然后按拓扑序遍历全图（显然这是一个内向树形图），对于每个点$u$，按$kruskal$重构树的方式将$u$与它指向的点合并，然后答案就是重构树的深度

结果：$53$分

### 真·题解

非常简单的一个树形$dp$

首先不难想到，每个点$u$的子节点引领一棵子树，然后这些子树与$u$的连接方式一定是这样：有一个长度为$s$的链，$s$是$u$的子节点数量，链上点一开始都是没有右儿子的，然后底端那个点的左儿子是$u$，然后将上面提到的这些子树分配给链的右儿子。不难想到一个贪心：深度大的子树尽量作为链的更顶端点的右儿子。所以将子树的深度从大到小排个序，$dep_k$表示第$k$大的深度，那么$u$的深度就是$max\{dep_k+k\}$

最后的答案就是$1$的深度

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

inline void upmax(int &x,const int &y){if(y>x) x=y;}

const int N=100010;
struct Edge{int to,next;} e[N];
int h[N],sum=0,n;
int fa[N],f[N],c[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	int cnt=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next) dfs(e[tmp].to);
	for(int tmp=h[u];tmp;tmp=e[tmp].next) c[++cnt]=f[e[tmp].to];
	sort(c+1,c+1+cnt);
	for(int i=1;i<=cnt;i++)
		upmax(f[u],c[i]+cnt-i+1);
}

int main()
{
	n=read();
	for(int i=2;i<=n;i++)
	{
		fa[i]=read();
		add_edge(fa[i],i);
	}
	dfs(1);
	printf("%d\n",f[1]);
	return 0;
}
```



---

