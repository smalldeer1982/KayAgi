# [ABC244G] Construct Good Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc244/tasks/abc244_g

$ N $ 個の頂点と $ M $ 本の辺からなる単純（自己ループおよび多重辺を持たない）かつ連結な無向グラフが与えられます。  
 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結びます。

下記の $ 2 $ つの条件をともに満たす整数列 $ (A_1,\ A_2,\ \ldots,\ A_k) $ を長さ $ k $ の**パス**と呼びます。

- すべての $ i\ =\ 1,\ 2,\ \dots,\ k $ について、$ 1\ \leq\ A_i\ \leq\ N $ 。
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ k-1 $ について、頂点 $ A_i $ と頂点 $ A_{i+1} $ は辺で直接結ばれている。

空列も長さ $ 0 $ のパスとみなします。

$ 0 $ と $ 1 $ のみからなる長さ $ N $ の文字列 $ S\ =\ s_1s_2\ldots\ s_N $ が与えられます。 パス $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_k) $ が下記を満たすとき、パス $ A $ を $ S $ に関する**良いパス**と呼びます。

- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、次を満たす。
  - $ s_i\ =\ 0 $ ならば、$ A $ に含まれる $ i $ の個数は偶数である。
  - $ s_i\ =\ 1 $ ならば、$ A $ に含まれる $ i $ の個数は奇数である。

この問題の制約下において、$ S $ に関する長さ $ 4N $ 以下の良いパスが少なくとも $ 1 $ つ存在することが示せます。 $ S $ に関する長さ $ 4N $ 以下の良いパスを $ 1 $ つ出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min\lbrace\ 2\ \times\ 10^5,\ \frac{N(N-1)}{2}\rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 与えられるグラフは単純かつ連結
- $ N,\ M,\ u_i,\ v_i $ は整数
- $ S $ は $ 0 $ と $ 1 $ のみからなる長さ $ N $ の文字列

### Sample Explanation 1

パス $ (2,\ 5,\ 6,\ 5,\ 6,\ 3,\ 1,\ 3,\ 6) $ は、長さが $ 4N $ 以下であり、 - 含まれる $ 1 $ の個数は奇数（ $ 1 $ 個） - 含まれる $ 2 $ の個数は奇数（ $ 1 $ 個） - 含まれる $ 3 $ の個数は偶数（ $ 2 $ 個） - 含まれる $ 4 $ の個数は偶数（ $ 0 $ 個） - 含まれる $ 5 $ の個数は偶数（ $ 2 $ 個） - 含まれる $ 6 $ の個数は奇数（ $ 3 $ 個） であるため、$ S\ =\ 110001 $ に関する良いパスです。

### Sample Explanation 2

空のパス $ () $ は、$ S\ =\ 000000 $ に関する良いパスです。 代わりにパス $ (1,\ 2,\ 3,\ 1,\ 2,\ 3) $ などを出力しても正解となります。

## 样例 #1

### 输入

```
6 6
6 3
2 5
4 2
1 3
6 5
3 2
110001```

### 输出

```
9
2 5 6 5 6 3 1 3 6```

## 样例 #2

### 输入

```
3 3
3 1
3 2
1 2
000```

### 输出

```
0```

# 题解

## 作者：Genius_Star (赞：2)

### 题意：

给定 $n$ 个点的无向图，每个点的颜色初始为 $0$ 或 $1$，经过一个点会使这个点的颜色 $\text{xor} \ 1$。

请构造出一条长度不超过 $4 \times n$ 的路径，使得每个点最后的颜色都为 $0$。

### 思路：

先考虑由图转化到树上做问题（即求一个生成树）

先想一下，如果当前点 $u$ 的颜色为 $1$，如何才可以让他转化为 $0$：

- 先走到他的 $fa_u$，将 $color_{fa_u} \ \text{xor} \ 1$，之后又走回到 $u$ 点，这样可以使得将点的颜色转化为 $0$。

那我们按照这样的思路，从 $1$ 号点开始走，搜每一个点，然后逐步回溯，回溯的时候如果当前颜色点的颜色为 $1$，则可以按照以上方法使得当前点的颜色化为 $0$。

这样我们会发现一个问题：点 $1$ 没有父亲，万一 $color_1=1$，怎么使得其颜色化为 $0$？

- 先走到他的任意一个点 $son_1$，之后 $color_{son_1}=1$ 了（因为在进行了上述操作后，除了 $1$ 其他点的颜色都化为 $0$ 了），然后再走回 $1$ 点，那 $color_1=0$ 了，之后再走到 $son_1$，将 $color_{son_1}=0$，之后就结束了。

这样的话我们最多的点数为 $3n+4$。

时间复杂度为：$O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,cnt=0;
char c;
ll fa[N],f[N],ans[N<<2ll];
vector<ll> E[N];
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
ll Find(ll x){
	if(x!=fa[x])
	  return fa[x]=Find(fa[x]);
	return fa[x];
}
void Union(ll x,ll y){
	x=Find(x),y=Find(y);
	fa[x]=y;
}
void dfs(ll u,ll fa){
	f[u]^=1ll;
	ans[++cnt]=u;
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		dfs(v,u);
		ans[++cnt]=u;
		f[u]^=1ll;
		if(f[v]){
			f[v]^=1;
			f[u]^=1;
			ans[++cnt]=v;
			ans[++cnt]=u;
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  fa[i]=i;
	for(int u,v,i=1;i<=m;i++){
		u=read(),v=read();
		if(Find(u)!=Find(v)){
			Union(u,v);
			add(u,v);
		}
	}
	for(int i=1;i<=n;i++){
		scanf("%c",&c);
		f[i]=c-'0';
	}
	dfs(1,0);
	if(f[1]){
		f[1]^=1ll;	
		for(auto v:E[1]){
			ans[++cnt]=v;
			ans[++cnt]=1ll;
			ans[++cnt]=v;
			break;
		}
	}
	write(cnt);
	putchar('\n');
	for(int i=1;i<=cnt;i++){
		write(ans[i]);
		putchar(' ');
	}
	return 0;
}
```


---

## 作者：igAC (赞：1)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc244_g)

[ATlink](https://atcoder.jp/contests/abc244/tasks/abc244_g)

简要题意：

给定一个 $n$ 个点 $m$ 条边的无向图，每个点都是黑色或白色（$1$ 表示黑色）。

经过一个点会使这个点的颜色发生改变。

请构造出一条长度不超过 $4n$ 的路径，使得每个点最后的颜色都为白色。

长度定义为路径经过的节点个数。

# $\text{Solution}$

很好的一道题捏。

有一个很常见的图论套路，求全图的一棵生成树，然后在生成树上做文章。

这道题也是一样，我们先求出原图的一颗生成树，且以 $1$ 为根。

![](https://cdn.luogu.com.cn/upload/image_hosting/gpxvd1bo.png)

这是样例剖出来的一棵生成树，我们考虑如何让一个节点变色。

假设我们在节点 $2$，我们要让节点 $4$ 变色，我们发现只要 $2 \to 4 \to 2$ 我们就可以让一个节点变色。

这就启发了正解：

令节点 $u$ 的父亲为 $fa_u$，要让节点 $u$ 变色，我们只需要执行 $fa_u \to u \to fa_u$ 的“反复横跳”操作。

我们从 $1$ 节点向下遍历每个节点，从叶子节点开始一层一层向上进行“反复横跳”操作。

最后只剩下 $1$ 节点可能没有被染成白色。

我们可以找它的儿子节点 $son$。

进行 $1 \to son \to 1 \to son$ 的操作，容易发现这样操作后 $1$ 会变色而 $son$ 不会变色。

那为什么这样的路径长度不会超过 $4n$ 呢？

向下遍历，每条边最多只会遍历两次。

而我们每个点也最多只会执行 $1$ 次“反复横跳”操作。

这样路径的长度就不会超过 $4n$ 了。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define INF 1e9
#define LLINF 1e18
#define ll long long
#define N 100005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
void print(int x){
	if(x<0) putchar('-'),x=~(x-1);
	if(x>9) print(x/10);
	putchar(x%10+48);
}
int n,m,s[N],fa[N];
int head[N],tot;
struct Edge{
	int to,nxt;
}e[N<<1];
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
bool same(int x,int y){return (find(x)==find(y));}
vector<int>ans;
void dfs(int x,int f){
	ans.push_back(x),s[x]^=1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		dfs(y,x);
		ans.push_back(x),s[x]^=1;
		if(s[y]){
			ans.push_back(y);
			ans.push_back(x);
			s[y]^=1,s[x]^=1;
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		if(!same(x,y)){
			merge(x,y);
			add_edge(x,y);
			add_edge(y,x);
		}
	}
	for(int i=1;i<=n;++i){
		char c;cin>>c;
		s[i]=c-48;
	}
	dfs(1,0);
	if(s[1]){
		int y=e[head[1]].to;
		ans.push_back(y),ans.push_back(1),ans.push_back(y);
	}
	printf("%d\n",ans.size());
	for(int x:ans) printf("%d ",x);
	return 0;
}
```

---

## 作者：RAND_MAX (赞：0)

刚拿到题目感觉无从下手，我们不妨将图转化成该图的最小生成树，不难证明对于答案两者等价。

很容易想到一种策略：每次遍历一个子节点 $i$，先使以 $i$ 为根的子树内除点 $i$ 外均满足条件，若是此时点 $i$ 也满足条件则跳回父节点，否则跳回父节点后再跳一个来回，可以使 $i$ 满足条件，递归处理即可。这样操作每条边最多访问两次，生成树共有 $N-1$ 条边，故答案序列长度不超过 $4N$。

若是根节点不满足条件，在最后一步不跳回根节点即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100010
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
int n,m,x,y,num[N];
bool b[N],vis[N];
vector<int>g[N],ans;
void dfs(int x,int fa)
{
	vis[x]=1,num[x]^=1,ans.push_back(x);
	for(int i:g[x])
	{
		if(vis[i]) continue;
		dfs(i,x);
		num[i]&=1;
		if(num[i]!=b[i]) num[i]^=1,num[x]^=1,ans.push_back(i),ans.push_back(x);
	}
	if(!fa&&num[x]!=b[x]) ans.pop_back();
	if(fa) ans.push_back(fa),num[fa]^=1;
}
signed main()
{
	n=R,m=R;
	while(m--) x=R,y=R,g[x].push_back(y),g[y].push_back(x);
	for(int i=1;i<=n;i++)
	{
		char xxx=getchar();
		while(xxx!='0'&&xxx!='1') xxx=getchar();
		b[i]=xxx-'0';
	}
	dfs(1,0);
	write(ans.size(),'\n');
	for(int i:ans) write(i,' ');
 	return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：0)

这种结论题还是要找切入点，再延伸成解法。  
观察到如果只有两个点，可以通过来回走染成任意颜色。  
举个例子：$00$ 到 $01$，可以走 $1 \to 2 \to 1$；$10$ 到 $01$，可以走 $1 \to 2$。  
然后根据这个性质，我们只要在图上建一个生成树，然后遍历整颗树，如果子节点 $v$ 需要修改，在回溯到其父节点 $u$ 时执行 $[u]\to v\to u$ 即可，方括号表示所在节点，已经加入答案序列。特别注意一下如果根节点 $1$ 需要修改，执行 $[1]\to son \to 1 \to son$。  
这样的话，遍历回溯一遍是 $2n$ 次，每次修改是 $2$ 次，最多 $n$ 次修改，显然总次数不会超过 $4n$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 998244353
#define fir first
#define sec second
#define pr pair<int,pair<int,int> >
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
int n,m,q[maxn],ans[maxn],cnt,cl[maxn];
vector<int>e[maxn];
char s[maxn];
int find(int fa)
{
	if(q[fa]==fa)return fa;
	return q[fa]=find(q[fa]);
}
void dfs(int u,int fa)
{
	ans[++cnt]=u,cl[u]++;//遍历
	for(int v:e[u])
	{
		if(v==fa)continue;
		dfs(v,u),ans[++cnt]=u,cl[u]++;//回溯
		if(cl[v]%2!=s[v]-'0')ans[++cnt]=v,ans[++cnt]=u,cl[u]++;//修改
	}
}
signed main()
{
	int x,y;
	n=read(),m=read();
	for(int i=1;i<=n;i++)q[i]=i;
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read();
		int b1=find(x),b2=find(y);
		if(b1!=b2)e[x].push_back(y),e[y].push_back(x),q[b1]=b2;//不连通则要加边
	}
	cin>>s+1,dfs(1,0);
	if(cl[1]%2!=s[1]-'0')ans[++cnt]=e[1][0],ans[++cnt]=1,ans[++cnt]=e[1][0];//特判1是否需要修改
	write(cnt),puts("");
	for(int i=1;i<=cnt;i++)write(ans[i]),putchar(' ');
    return 0;
}
```

---

## 作者：xzy090626 (赞：0)

这道题目一拿到无从下手。

那么我们可以主动增加一些特殊性质，比如找出原图的一棵生成树，猜测只需要 $n-1$ 条边即可。

然后可以按照 dfs 序遍历树。这样容易发现一般来说每个结点最多走 $3$ 次。

但是如何满足给定的奇/偶数条件呢？

我们可以在向上爬的过程中，如果当前点不满足条件，那么走到上方结点再回来，再走到上方结点，这样就把问题传到了上方去。虽然没有直接地解决问题，但是也有效地简化了问题。

那么就只需要解决 $1$ 号结点的问题了。我们知道，按照原本的遍历顺序是要回到最后的 $1$ 号结点的。那么只要不回去就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
using namespace std;
const int N = 1e6 + 7;
int n,m,cnt[N];
char s[N];
vector<int>a[N],ans;
void dfs(int x,int fa){
	cnt[x]++;
	ans.push_back(x);
	for(auto c:a[x]){
		if(cnt[c]) continue;
		dfs(c,x);
		ans.push_back(x);
		cnt[x]++;
	}
	if(cnt[x]%2!=s[x]-'0'){
		if(x==1) ans.pop_back();
		else{
			ans.push_back(fa);
			ans.push_back(x);
			cnt[fa]++;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	cin>>(s+1);
	dfs(1,0);
	cout<<ans.size()<<'\n';
	for(auto c:ans) cout<<c<<' ';
	return 0;
}
```
实现的时候注意到没必要真的求最小生成树，在 dfs 时判一下就行。

---

## 作者：TernaryTree (赞：0)

图比较难做，考虑跑出一棵生成树，只用上面的边。

显然先把每条边全用上，然后注意到每次可以将一条边经过的次数 $+2$，dfs 一遍就跑完了。这里 dfs 是子树经过次数满足题目条件下，从 $u$ 回到 $u$ 的方案构造；如果 dfs 完儿子 $u$ 不满足条件，就让 $fa\to u$ 这条边经过次数 $+2$，即，让原来的 $u$ 变为 $u\to fa\to u$。

最后 $1$ 可能不满足限制，因为 $1$ 没有父亲；但是实际上因为最后肯定会回到 $1$，所以把最后回到的那个 $1$ 去掉就行了。

首先一次正常跑的总个数是 $2n$，每次调整只会加 $2$ 个点，所以长度不超过 $4n$。

具体可以看代码实现。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e5 + 10;

int n, m;
vector<int> g[maxn];
int fa[maxn];
int c[maxn];
int a[maxn];
char ch;
vector<int> ans;

int find(int x) {
	return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

void dfs(int u, int fa) {
	ans.push_back(u);
	for (int v : g[u]) {
		if (v == fa) continue;
		dfs(v, u);
		ans.push_back(u);
	}
	if (u != 1 && (c[u] & 1) != a[u]) {
		c[fa]++, c[u]++;
		ans.push_back(fa);
		ans.push_back(u);
	}
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	c[1] = 1;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		if (find(u) != find(v)) {
			fa[find(u)] = find(v);
			g[u].push_back(v);
			g[v].push_back(u);
			c[u]++, c[v]++;
		}
	}
	for (int i = 1; i <= n; i++) cin >> ch, a[i] = ch - '0';
	dfs(1, 0);
	bool fl = (c[1] & 1) != a[1];
	cout << ans.size() - fl << endl;
	for (int i = 0; i + fl < ans.size(); i++) cout << ans[i] << " ";
	return 0;
}

```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

给定一张 $n$ 个点，$m$ 条边的无向图。

让你求出一条长度至多为 $4n$ 的路径，使得第 $i$ 个点经过的次数 $p_i\equiv s_i \pmod 2$。

**解法分析**

一道很好的构造题。

考虑一个很典的套路：先求出原图的生成树/生成森林，再在树上处理问题就好了。

考虑一个策略：每次在当前节点 $i$，显然要先处理完其每一个子树，使得其子树内每一个节点都满足条件，再递归回到它的父亲节点。

再考虑怎么才能令经过的次数 $p_i\equiv s_i\pmod 2$。

考虑一条路径 $a\to b\to a$，就可以使 $a$ 的一个相邻节点 $b$ 改变其经过次数的奇偶性。那么只需要 $i\to \text{fa}_i\to i$，就可以将 $i$ 的奇偶性改变。当 $i=\text{root}$ 时，随便找一个它的子节点完成该操作即可。

> Q：为什么这样生成的答案序列的长度不会超过 $4n$？
>
> A：因为有回溯操作的存在，每条边都会经过两次。因为还需要调整 $p_i$ 的奇偶性不等于 $s_i$ 的节点，需要额外经过 $2$ 个点。所以最后的总长度一定不会超过 $4n$。

时间复杂度为 $O(n)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mod 998244353
#define N 100005
ll n,m,fa[N],s[N],vis[N];
vector<ll> e[N],ans,sn[N];
void dfs(ll x,ll f){
	fa[x]=f,vis[x]=1;
	for(ll i:e[x]) if(!vis[i]) dfs(i,x),sn[x].pb(i);
}
void dfs1(ll x){
	ans.pb(x),s[x]^=1;
	for(ll i:sn[x]){
		dfs1(i);
		ans.pb(x),s[x]^=1;
		if(s[i]) ans.pb(i),ans.pb(x),s[x]^=1,s[i]^=1;
	}
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1,u,v;i<=m;i++){
		scanf("%lld%lld",&u,&v);
		e[u].pb(v),e[v].pb(u);
	}
	for(ll i=1;i<=n;i++) scanf("%1lld",&s[i]);
	dfs(1,0);
	dfs1(1);
	if(s[1]) ans.pb(sn[1][0]),ans.pb(1),ans.pb(sn[1][0]);
	printf("%d\n",ans.size());
	for(ll i:ans) printf("%lld ",i);
	printf("\n");
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

居然没人写题解。

首先考虑在一条链上怎么做。从链的一个顶点开始，往它的后继走。如果一个点的前驱不满足要求，就走去前驱再走回来。称之为调整操作。

这时候就会有一个问题：如果最后一个点没有办法调整怎么办？

事实上，最后一步会走到最后一个点，而这最后一步我们可以选择走或不走，这样判断一下就可以保证最后一个点满足条件了。

接下来推广到一棵树的情况。其实没啥区别。判断一下走了这个点之后要不要回溯，分讨一下即可。具体可以参考代码实现。

在图上跑出一棵生成树，进行以上操作即可。

这样的路径长度一定不超过 $4N$ 吗？

如果没有调整操作，因为有回溯的存在，路径最长 $2N$。每次调整会有 $2$ 步，每个点最多调整一次，所以最后长度不会超过 $4N$。

code：

```cpp
int n,m;
int tot,head[N];
char s[N];
bool vis[N];
struct node{
	int to,nxt,cw;
}e[M<<1];
vector<int> ans;
inline void add(int u,int v){
	e[++tot]={v,head[u],0};
	head[u]=tot;
}
int siz[N],son[N];
void init(int u,int f){
	siz[u]=1;
	vis[u]=true;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]){
			continue;
		}
		e[i].cw=1;
		init(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}//这里不一定要找重儿子，只是尽量使路径长度短而已，事实上随意找一个儿子即可
	}
}
int cnt[N];
void dfs(int u,int f,bool rt){//rt记录是否要回溯
	cnt[u]++;
	vis[u]=true;
	ans.push_back(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!e[i].cw||vis[v]||(!rt&&v==son[u])){
			continue;
		}
		dfs(v,u,1);
		ans.push_back(u);
		cnt[u]++;
	}
	if(rt){
		if((cnt[u]&1)!=s[u]-'0'){
			ans.push_back(f);
			ans.push_back(u);
			cnt[f]++;
			cnt[u]++;
		}//调整
	}else{
		if(!son[u]){
			return;
		}
		if((cnt[u]&1)!=s[u]-'0'){
			ans.push_back(son[u]);
			ans.push_back(u);
			cnt[son[u]]++;
			cnt[u]++;
		}//调整
		dfs(son[u],u,0);
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	scanf("%s",s+1);
	init(1,0);
	mems(vis,false);
	dfs(1,0,0);
	if((cnt[ans.back()]&1)!=s[ans.back()]-'0'){
		ans.pop_back();
	}//判断最后一步走不走以调整最后一个点
	printf("%d\n",(int)ans.size());
	for(int i:ans){
		printf("%d ",i);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

