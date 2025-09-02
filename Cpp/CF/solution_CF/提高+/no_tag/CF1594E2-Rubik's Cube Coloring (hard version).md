# Rubik's Cube Coloring (hard version)

## 题目描述

It is the hard version of the problem. The difference is that in this version, there are nodes with already chosen colors.

Theofanis is starving, and he wants to eat his favorite food, sheftalia. However, he should first finish his homework. Can you help him with this problem?

You have a perfect binary tree of $ 2^k - 1 $ nodes — a binary tree where all vertices $ i $ from $ 1 $ to $ 2^{k - 1} - 1 $ have exactly two children: vertices $ 2i $ and $ 2i + 1 $ . Vertices from $ 2^{k - 1} $ to $ 2^k - 1 $ don't have any children. You want to color its vertices with the $ 6 $ Rubik's cube colors (White, Green, Red, Blue, Orange and Yellow).

Let's call a coloring good when all edges connect nodes with colors that are neighboring sides in the Rubik's cube.

 ![](https://espresso.codeforces.com/81468de2d38e27a371abfa76db5ecd8938d6437a.png)![](https://espresso.codeforces.com/acbbacfbb22e480bc2bdcb3e0731504ff698a3f2.png)A picture of Rubik's cube and its 2D map.More formally:

- a white node can not be neighboring with white and yellow nodes;
- a yellow node can not be neighboring with white and yellow nodes;
- a green node can not be neighboring with green and blue nodes;
- a blue node can not be neighboring with green and blue nodes;
- a red node can not be neighboring with red and orange nodes;
- an orange node can not be neighboring with red and orange nodes;

However, there are $ n $ special nodes in the tree, colors of which are already chosen.

You want to calculate the number of the good colorings of the binary tree. Two colorings are considered different if at least one node is colored with a different color.

The answer may be too large, so output the answer modulo $ 10^9+7 $ .

## 说明/提示

In the picture below, you can see one of the correct colorings of the first test example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E2/dcebca3c4893383a751dc627ead5632c7d038ce7.png)

## 样例 #1

### 输入

```
3
2
5 orange
2 white```

### 输出

```
1024```

## 样例 #2

### 输入

```
2
2
1 white
2 white```

### 输出

```
0```

## 样例 #3

### 输入

```
10
3
1 blue
4 red
5 orange```

### 输出

```
328925088```

# 题解

## 作者：Graphcity (赞：4)

我们发现，这道题的树上结点数非常多（$2^k-1$ 个），但是关键结点数却很少（$2\times 10^3$ 个），不难想到可以建立一棵虚树跑 dp。

对于每个关键结点，它只会影响从根结点到它的链。我们把每个从根结点到关键结点的链提取出来，就建立了一棵虚树，这棵虚树的总结点数约为 $mk$，大概在 $10^5$ 范围。

设 $f(i,j)$ 表示在第 $i$ 个结点，颜色为 $j$ 的方案数，则有状态转移方程：

$$f(i,j)=\prod_{k\in \text{son}(i),l}f(k,l)$$

其中颜色 $j$ 和颜色 $l$ 可以放在相邻结点。对于关键结点，特判即可。

对于不在虚树上的结点，设他们共有 $s$ 个，它们对答案造成的贡献为 $4^s$ 个，与虚树上的答案乘起来就行了。

（赛时代码，马蜂可能有些混乱）

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define int long long
using namespace std;
typedef pair<int,int> Pair;
const int Maxn=1e6,Mod=1e9+7;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,k,s,col[26];
int f[Maxn+5][7],vis[Maxn+5],ch[Maxn+5][2];
vector<Pair> v;
vector<int> q;


inline void Init()
{
    col['w'-'a']=1;
    col['y'-'a']=2;
    col['g'-'a']=3;
    col['b'-'a']=4;
    col['r'-'a']=5;
    col['o'-'a']=6;
}
inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}
inline int Get(int x) {return lower_bound(q.begin(),q.end(),x)-q.begin()+1;}

inline void dfs(int x) // 动态规划
{
    if(!ch[x][0]) {f[x][vis[x]]=1; return;}
    if(ch[x][0]) dfs(ch[x][0]);
    if(ch[x][1]) dfs(ch[x][1]);
    For(i,1,6)
    {
        if(vis[x]>0 && i!=vis[x]) continue;
        int a1=0,a2=0;
        if(ch[x][0])
            For(j,1,6) if((i+1)/2!=(j+1)/2) a1=(a1+f[ch[x][0]][j])%Mod;
        if(ch[x][1])
            For(j,1,6) if((i+1)/2!=(j+1)/2) a2=(a2+f[ch[x][1]][j])%Mod;
        if(!ch[x][1]) f[x][i]=a1;
        else f[x][i]=a1*a2%Mod;
    }
}

signed main()
{
    Init();
    cin>>n>>k; s=(1ll<<n)-1ll;
    For(i,1,k)
    {
        int a; string b;
        cin>>a>>b;
        v.push_back(make_pair(a,col[b[0]-'a']));
    }
    q.push_back(1); // 建立虚树
    for(auto i:v)
    {
        int a=i.first;
        while(a) q.push_back(a),a/=2;
    }
    sort(q.begin(),q.end()),q.erase(unique(q.begin(),q.end()),q.end());
    for(auto i:v)
    {
        int a=i.first,b=i.second,ma=a;
        while(1)
        {
            int c=Get(a),d=Get(a/2);
            if(vis[c]!=0) break;
            vis[c]=-1;
            if(a==1) break;
            if(!ch[d][0]) ch[d][0]=c;
            else ch[d][1]=c;
            a/=2;
        }
        vis[Get(ma)]=b;
    }
    dfs(1);
    int all=0;
    For(i,1,6) all=(all+f[1][i])%Mod;
    int siz=q.size(); // 统计非虚树结点贡献
    siz=s-siz;
    cout<<all*Pow(4,siz)%Mod<<endl;
    return 0;
}
```

---

## 作者：ltdj (赞：3)

~~做出来了但是没交~~

--------------

### 题意


白色节点不能与白色和黄色节点相邻；

黄色节点不能与白色和黄色节点相邻；

绿色节点不能与绿色和蓝色节点相邻；

蓝色节点不能与绿色和蓝色节点相邻；

红色节点不能与红色和橙色节点相邻；

橙色节点不能与红色和橙色节点相邻；

------


据此给一个高为 $n$($n\leq60$) 的**完全二叉树**染色。求方案数:

不难推出公式：设$fi$表示以高度为i的树，确定根节点颜色，有多少方案，  $f_i=f_i^2*16$ (根节点确定， 每个子节点有4种可行颜色)

E2在E1的基础上，**有M($m\leq2000$)个点的的颜色已经给出**，求给其他点染色的方案数。

--------------

### 题解

我们先把E1的 $f_{i, j}$ 数组预处理出来(高度为i的树没有预给定颜色，且根节点颜色为j的方案数)

考虑直接dp：如果这个节点的子树中没有预定义节点，直接返回f数组，否则直接暴力dp

此时需要处理的节点个数为子树中包含预定义节点的节点个数，可以证明这样的点数量为 $O(nm)$ (每个预定义点都在叶子节点最大)

现在的问题是如何判断一个点是否包含预定义节点呢：
一种暴力的做法是直接枚举所有给出的点，求出高度进行判断。~~但是这样的复杂度多了nm的常数~~
考虑反过来，对于每个预定义点，把它的所有祖先的标记一下，不难想到，让节点编号每次除2就行。需要一个set维护，同时还需要一个map来记录颜色。

总复杂度 $O(nm\log(nm))$ 以及一个较大的常数

-----------
### 实现
~~赛时代码过丑抱歉~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>
#include <map>
#include <set>
#define int long long
using namespace std;

int read(){
	int num=0, flag=1; char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') flag=-1, c=getchar();
	while(isdigit(c)) num=1ll*num*10+c-'0', c=getchar();
	return num*flag; 
}

int readc(){
	char c=getchar();
	while(c<'a' || c>'z') c=getchar();
	return c;
}

void reads(){
	char c=getchar();
	while(c<'a' || c>'z') c=getchar();
	while(c>='a' && c<='z') c=getchar();
}

int checkColor(int a, int b){
	if(a > b) swap(a, b);
	if(a == b) return 1;
	if(a==4 && b==5) return 1;
	if(a==2 && b==3) return 1;
	if(a==0 && b==1) return 1;
	return 0;
}

const int N = 3055, M = 5e6;
const int mod = 1e9+7;
int T, n, m;
int r[M][6], sz=0;
set<int> st;
map<int, int> col;

int get(char s){
	if(s == 'w') return 0;
	if(s == 'y') return 1;
	if(s == 'g') return 2;
	if(s == 'b') return 3;
	if(s == 'r') return 4;
	return 5; 
}

int p[N], c;
int res[N][6];

int getlas(int id){
	int num = 0;
	while(id) num++, id>>=1;
	return n-num+1;
}

int cnt = 0;

int check(int id){
	return st.count(id);
}

int dp(int id, int h) {
	if(h == 1){
		
		int lres = (++sz)%M;
		if(col.count(id)) {
			for(int i=0; i<6; i++) r[lres][i] = 0;
			r[lres][col[id]] = 1;
			return lres;
		}else{
			for(int i=0; i<6; i++) r[lres][i] = 1;
			return lres;
		}
	}
	
	if(check(id)){
		int r1=dp(id*2, h-1), r2=dp(id*2+1, h-1);
		
		int lres = (++sz)%M;
		if(col.count(id)) {
			int i = col[id];
			for(int j=0; j<6; j++) r[lres][j]=0;
			
			for(int j=0; j<6; j++){
					for(int k=0; k<6; k++){
						if(checkColor(i, j) || checkColor(i, k)) continue;
						r[lres][i] += r[r1][j]*r[r2][k]%mod;
						r[lres][i] %= mod;
					}
			}
			
			return lres;
		}else{
			for(int j=0; j<6; j++) r[lres][j]=0;
			for(int i=0; i<6; i++){
				for(int j=0; j<6; j++){
					for(int k=0; k<6; k++){
						if(checkColor(i, j) || checkColor(i, k)) continue;
						r[lres][i] += r[r1][j]*r[r2][k]%mod;
						r[lres][i] %= mod;
					}
				}
			}
			return lres;
		}
		
	}else{
		int lres = (++sz)%M;
		for(int i=0; i<6; i++){
			r[lres][i] = res[h][i];
		}
		return lres;
	}
}

signed main(){
	n=read(), m=read();
	for(int i=1; i<=m; i++){
		p[i]=read();
		c=get(readc()); reads();
		
		int cur = p[i];
		while(cur) {
			if(!st.count(cur)) st.insert(cur);
			cur /= 2; 
		} 
		col[p[i]] = c;
	}
	
	int num = 1;
	for(int i=1; i<=n; i++){
		for(int j=0; j<6; j++) res[i][j] = num;
		num = (num*num%mod*16%mod); 
	}
	
	int x = dp(1, n);
	int ans = 0;
	for(int i=0; i<6; i++) ans = (ans + r[x][i]) % mod;
	cout << ans << endl;
	
	return 0;
}

```

---

## 作者：GaryH (赞：2)

# CF1594E1&E2 题解

一道树上的DP计数题。

先考虑 Easy Version ，我们发现，深度相同的满二叉树本质等价，故我们可以显然的写出一个DP式：

记 $dp_{i,col}$ 代表深度为 $i$ 的满二叉树，根节点颜色为 $col$ 的方案数，则有：

$dp_{i,col} = dp_{i-1,c1} \times dp_{i-1,c2}$ ，转移前提是颜色 $col,c1$ 以及 $col,c2$ 分别在魔方中相邻。

这个DP式足以通过 Easy Version ，但在 Hard Version 中，

这个式子无法将事先已选颜色的节点计算进去，故我们先考虑一种更暴力的DP方法，即：

记 $dp_{u,col}$ ，代表二叉树中第 $u$ 个点染了颜色 $col$ ，这棵以 $u$ 为根节点的子树的方案数，

则转移式为：$dp_{u,col} = dp_{ls(u),c1} \times dp_{rs(u),c2}$ ，转移前提是 $col,c1$ 以及 $col,c2$ 分别在魔方中相邻。

这个DP式可以通过限制节点上颜色的选取来计算事先已选颜色的节点，但直接这样计算会爆复杂度，

故我们需要优化这个做法。

我们注意到，在某一棵子树里，不存在某个节点事先已选好了颜色，

那么棵子树的方案数就是上面 Easy Version 中的DP值。

这个有什么用呢？我们来进一步探究 Easy Version 里DP式的性质。

我们发现，对任意一个颜色，与其相邻的颜色恰有 $4$ 种，所以上面DP状态中，不同的颜色并不影响DP值的大小，所以我们有：

 $\large dp_{1,col}=1$ ，

$\large dp_{i,col} =(4 \times dp_{i-1,col})^2$ .

两个式子。

我们记 $\large F_i = dp_{i,col} $ ，$\large T_i = 4^{2^i-2}$ ，

则有： $\large { {F_i} \over {T_i} } = { {16(F_{i-1})^2} \over {T_i} }$ .

我们发现，$\large \sqrt { {T_i} \over {16} } = 4^{2^{i-1}-2} = T_{i-1}$ ，

即：$\large { {F_i} \over {T_i} } = { {(F_{i-1})^2} \over {(T_{i-1})^2} }$ .

那我们再记 $\large P_i =  { {F_i} \over {T_i} } $ ，则我们有：

$\large P_1 = 1$ ，

$\large P_i = (P_{i-1})^2$ .

两个式子。

显然，上式里， $P_i$ 恒为 $1$ ，那么我们就得出了： $dp_{i,col}=F_i = T_i =4^{2^i-2} $ .

故 $dp_{i,col}$ 的值实际上等于 $4^{2^i-2}$ ，而一颗满二叉树的方案数，当根节点颜色确定后，也就是 $4^{2^i-2}$ 种。

那么，现在我们考虑这个值的另一种含义：我们发现，一棵深度为 $i$ 的满二叉树里，除去根节点，其余

节点还有 $2^i-2$ 个，而每一个节点都恰有 $4$ 种选择，故$dp_{i,col}$ 的值等于 $4^{2^i-2}$ .

所以，对于一个节点 $u$ ，若其子树中没有事先已选颜色的节点，则它恰有 $4$ 种染色方案，这个值是固定

的，那我们就不需要考虑这个节点，而是把最后的答案乘上这个 $4$ 的贡献。

那么，我们现在需要考虑的点，都必须满足以下限制条件：

对于一个要考虑的点 $v$ ，$v$ 所在子树中必须含有至少一个事先已选颜色的节点。

我们接下来计算，有哪些节点需要我们考虑。

我们发现，对于每个事先已选颜色的节点，其到根的路径上所有的点都需要考虑；

而不满足上述条件的点，则一定不需要考虑。而这样的点最多有 $nk$ 个，即二叉树的深度乘上

事先已选颜色节点的数量。

并且，我们设包含这些点的点集为 $S$ ，则 $S$ 中任意两点 $u,v$ ，都可以只走 $S$ 中的点相互到达。

这时我们发现，我们只需要把这些点拿出来跑一次树形DP，再将最后答案乘上 $4^{2^k-1-|S|}$ 即可。

复杂度主要体现在用map预处理上，是 $O(nklog(nk))$ 的。

**E1 code:**

```
#define int long long

const int N (104);
const int mod (1e9 + 7);

int f[N][10];

signed main() {
	rep (i, 1, 6) f[1][i] = 1ll;
	rep (i, 2, 80) rep (j, 1, 6) {
		int det = 1;
		if (j % 2 == 0) det = -1;
		rep (le, 1, 6) rep (ri, 1, 6) {
			if (le != j && le != j + det && ri != j && ri != j+det)
			f[i][j] = (f[i][j] + (f[i-1][le] * f[i-1][ri]) % mod) % mod;
		}
	}
	int x = read(), ans = 0;
	rep (i, 1, 6) ans = (ans + f[x][i]) % mod;
	cout << ans;
}
```

**E2 code:**

（参考了CF官解的代码）

```
#define int long long

const int N (1e6 + 10);
const int mod (1e9 + 7);

inline int ksm(int a, int b) {
	int res = 1ll;
	while (b) {
		if (b & 1ll) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod, b >>= 1ll;
	} return res;
}

int k,n;
int tot;
int col[N];
int dp[N][6];
vector < int > G[N];
map < int , int > buk, vl;
int color[6][6] = { {1, 2, 4, 5}, {0, 2, 3, 5}, {0, 1, 3, 4},
					{1, 2, 4, 5}, {0, 2, 3, 5}, {0, 1, 3, 4} };

inline int dfs(int u, int c) {
	if (col[u] != -1 && col[u] != c) return 0;
	if (dp[u][c] != -1) return dp[u][c];
	int res = 0, sum[2] = {0}, siz = G[u].size();
	rep (i, 0, 3) rep (j, 0, siz - 1) 
	  sum[j] += dfs(G[u][j], color[c][i]), sum[j] %= mod;
	if (G[u].empty()) sum[0] = sum[1] = 1;
	if ((int)(G[u].size()) == 1) sum[1] = 1;
	return dp[u][c] = res = sum[0] * sum[1] % mod;
}

signed main() {
	memset(col, -1, sizeof(col)), memset(dp, -1, sizeof(dp));
	k = read(), n = read();
	int rem = (1ll << k) - 1; map < string , int > val ;
	val["white"] = 0, val["yellow"] = 3, val["green"] = 4;
	val["blue"] = 1, val["red"] = 2, val["orange"] = 5;
	rep (i, 1, n) {
		int x = read(), u; string s; cin >> s, vl[x] = val[s], u = x;
		while (u >= 1 && !buk.count(u)) buk[u] = tot++, rem --, u >>= 1ll;
	}
	map < int , int > ::iterator p ;
	for (p = buk.begin(); p != buk.end(); p++) {
		int F = p -> fi, S = p -> se;
		if (vl.count(F)) col[S] = vl[F];
		if (buk.count(F << 1ll)) G[S].pb(buk[F << 1ll]);
		if (buk.count(F << 1ll | 1ll)) G[S].pb(buk[F << 1ll | 1ll]);
	}
	int res = ksm(4ll, rem), sum = 0;
	rep (c, 0, 5) sum += dfs(buk[1], c), sum %= mod;
	cout << res * sum % mod;
	return 0;
}
```



---

## 作者：vectorwyx (赞：2)

与 E1 不同的地方是 E2 先钦定了 $n$ 个结点的颜色，然后给其余点染色，问合法方案数。

为了方便，我们称一个结点为关键点，当且仅当它的颜色被钦定或它是某个被钦定点的祖先。由 E1，不难发现非关键点的贡献是平凡的 $4$，而关键点均在被钦定点到根的路径上。由于 $k$ 很小，所以关键点的数量不会很多，不妨保留所有关键点，这些关键点形成了一棵新树，我们在新得到的树上做树形 dp 即可，复杂度 $O(36kn)$。这和虚树有点相似，不过虚树是把关键点之间的路径缩了起来，这里则是保留了关键点之间的路径。

代码如下：
```cpp
#include<bits/stdc++.h>
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define sml(x,y) x=min(x,y)
#define big(x,y) x=max(x,y)
#define mk make_pair
#define pb push_back
#define int ll
#define ll long long
#define db double
using namespace std;
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}
inline int read(){ int x=0,f=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); } return x*f; }

const int N=1e6,qlr=1e9+7;
map<int,int> vis,f[10],head,g,dep;
int mp[N],tot;
struct Edge{
	int to,next;
	Edge(){}
	Edge(int x,int y){to=x,next=y;} 
}e[N];
int res,k;

void connect(int x,int y){
	e[++tot]=Edge(y,head[x]);
	head[x]=tot; 
}

void dfs(int x){
	if(g.count(x)) fo(i,1,6) f[i][x]=(i==mp[g[x]]);
	else fo(i,1,6) f[i][x]=1;
	for(int qwq=head[x];qwq;qwq=e[qwq].next){
		int p=e[qwq].to;
		dfs(p);
		fo(i,1,6){
			int sum=0;
			fo(j,1,6) if(i!=j&&i+j!=7) sum=(f[j][p]+sum)%qlr;
			f[i][x]=f[i][x]*sum%qlr;
		}
	}
}

int ksm(int x,int y){
	int ans=1,t=x;
	while(y){
		if(y&1) ans=ans*t%qlr;
		t=t*t%qlr;
		y>>=1;
	}
	return ans;
}

signed main(){
	k=read();int n=read();
	res=(1ll<<k)-2;
	mp['w']=1,mp['y']=6,mp['g']=2,mp['b']=5,mp['r']=3,mp['o']=4;
	fo(i,1,n){
		int x=read();
		string s;cin>>s;
		g[x]=s[0];
		for(int i=x;i>1&&!vis[i];i>>=1){
			vis[i]=1;
			res--;
			dep[i]++;
			connect(i>>1,i);
		}
	}
	dfs(1);int ans=0,x=ksm(4,res);
	fo(i,1,6) ans=(ans+f[i][1])%qlr;
	cout<<ans*x%qlr;
	return 0;
}
```


---

## 作者：SegTree (赞：1)

首先考虑一个朴素的树形 dp。用 $dp_{u,i}$ 表示结点 $u$ 颜色为 $i$ 时的方案数。

记 $d_i$ 表示选择颜色 $i$ 相邻结点不能选择的颜色集合。那么容易得到一个朴素的转移 $dp_{u,i}=\sum_{k1\notin d_i}dp_{2u,k1}\times \sum_{k2\notin d_i}dp_{2u+1,k_2}$。

显然，在结点 $u$ 子树内没有确定任何颜色的情况下对于任意的 $i$ 都可以用数学的方法计算出来。对于这颗子树，记它的深度为 $g$，确定根后每个结点都有 $4$ 种选法。也就是 $4^{siz_u-1}=4^{2^d-2}$，其中 $d$ 为这颗子树最深结点深度（根结点深度为 $1$ 的情况下）。直接输出这个式子乘上 $6$ 即可通过 E1。[E1 记录](https://codeforces.com/contest/1594/submission/219183925)。

那么，显然如果确定某个结点的颜色，那么受到影响的 $dp$ 值的结点只在根结点到这个结点的链上。对于这条链上用两个儿子结点的 $dp$ 值更新这个结点即可。注意对于确定颜色的结点 $u$ 会把 $k\ne col_u$ 的 $dp$ 值全部清零，故对于这样的结点从儿子合并上来之后还需要处理一下其他颜色的 $dp$ 值。这样就做完了本题。[E2 记录](https://codeforces.com/contest/1594/submission/219183991)。

---

## 作者：zesqwq (赞：1)

对于题解中时间复杂度为 $O(kmc^2)$，其中 $c$ 是颜色数，我提供一种复杂度为 $O(k^\epsilon c^3+mc^2)$ 的做法。

我们把答案拆成关键点和关键点到链上所有点的贡献和其它的贡献，其中第二部分是好算的，答案就是 $4^\text{点的个数}$。

对于第一部分，建立出虚树，这里的虚树指包含所有的 $m$ 个点和他们的 $\text{LCA}$ 的最小点集，显然虚树的点数是 $O(m)$ 的。

我们用 $f_{i,j}$ 表示第 $i$ 个点染色 $j$ 的方案数，用 $g(i,j)$ 表示颜色 $i, j$ 是否能相邻。那么对于 $i$ 的孩子 $v$，$f_{i,j} = f_{i,j}\sum_{g(j,k)}f_{v,k}$，我们发现转移中只有虚树上的点是可能不平凡的，其它的转移都是一样的，我们发现这个转移是一个乘上矩阵的形式，所以说虚树上点和点间的的那条链的转移可以用矩阵幂运算维护，预处理好这个矩阵的幂就可以做到 $O(k^\epsilon c^3+mc^2)$。

---

## 作者：Refined_heart (赞：1)

同时作为 $E1$ 题解了。

[$MyBlog$](https://www.cnblogs.com/h-lka/)

## 题目描述

给定 $2^n-1$ 个节点的完全二叉树，每个点有六种颜色，颜色有互斥性质，求所有合法的二叉树染色方案。

### Easy version

这个比较简单，但我也掉进坑里了）首先先手玩一下，看到样例 $n=3$ 的时候数字就那么大，绝对有什么次幂性质。

一个点的答案显然是六种。考虑不断向上合并，每一个节点可以选择六种颜色，所以我们考虑一种颜色再乘回去即可。

发现，对于选定一种颜色，两边均有四种颜色可以选，乘起来就是 $16$ 种，最后的答案必然形如 $6\times 4^{x}.$ 我们把手推的一些写下来：

$$0,2,6,14,30...$$

到这里规律也就很明显了，也可以给出严谨推导。设左右子树每种颜色的对应方案数为 $4^x,$ 则对于一种颜色，左侧右侧均有 $4^{x+1}$ 种可能，乘起来就是 $4^{2x+2}$ 种。

所以对于 $4$ 指数上的递推就搞定了。**但是注意，对于指数上面的取模，我们要对 $\varphi(p)=(10^9+6)$ 取模，这里利用欧拉定理**

于是简单版本就做完了。

### Hard version

树太大了，~~忍不了~~，怎么办？

发现有效的点只有两千个，算上把它们全部钩构造成完整结构的也不多，所以直接考虑建立虚树进行 $dp.$

显然的性质是只有其祖先有用，而由于是完全二叉树，所以祖先个数只有 $O(\log n)$ 个，于是点数就可以接受了。

同时我们也发现，这个不同于一般的虚树，这里我们建立一定是要把从这个点到根节点的一整条链全部建立出来的，因为它们都是必须点。**所以我们最后要 $dp$ 的树就是普通的树，但是其所有隐式节点，或者说没有被建立的节点，其值不受固定颜色点的干扰。**

考虑普通树怎么 $dp:$ 设 $f[x][1..3]$ 表示对应三种不同划分颜色对应的方案数。（三种是因为这题互斥性质两个颜色相对）

那么转移就是直接把两个子树乘起来。

那么现在考虑定初值。初值显然不受其他带颜色点影响，所以直接用第一问的方法，**取 $\frac{1}{6}$ 即可。**

知道初值咋求了，这 $dp$ 的方程也知道了，剩下的就是一个 $dfs$ 的事情了。

注意用 ```map<int,int>``` 一开始有一个数组忘记开 RE 了好几次

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
#define int long long
const int mod=1e9+7;
const db eps=1e-10;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline db Max(db x,db y){return x-y>eps?x:y;}
inline db Min(db x,db y){return x-y<eps?x:y;}
inline int Add(int x,int y,int M=mod){return (x+y)%M;}
inline int Mul(int x,int y,int M=mod){return 1ll*x*y%M;}
inline int Dec(int x,int y,int M=mod){return (x-y+M)%M;}
inline int Abs(int x){return x<0?-x:x;}
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
inline void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const int N=2e5+10;
int k,n;
int F[61];
string s;
typedef long long ll;
map<ll,ll>pa,col,lson,rson,f[4];
vector<ll>Node;
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=Mul(res,x);
		x=Mul(x,x);y>>=1;
	}
	return res;
}
inline int Getdep(int v){return log2(v)+1;}
void Treat(){
	for(auto v:Node){
		if(lson[v]||rson[v])continue;
		int Dep=k-Getdep(v)+1;
		if(col[v])f[col[v]][v]=Mul(1,qpow(4,F[Dep]));
		else for(int i=1;i<=3;++i)f[i][v]=Mul(2,qpow(4,F[Dep]));
	}
}
void DP(ll x){
	if(!lson[x]&&!rson[x])return;
	if(lson[x])DP(lson[x]);
	if(rson[x])DP(rson[x]);
	ll L1=f[1][lson[x]],L2=f[2][lson[x]],L3=f[3][lson[x]],R1=f[1][rson[x]],R2=f[2][rson[x]],R3=f[3][rson[x]];
	if(!lson[x]){L1=L2=L3=Mul(2,qpow(4,F[k-Getdep(x*2)+1]));}
	if(!rson[x]){R1=R2=R3=Mul(2,qpow(4,F[k-Getdep(x*2)+1]));}
	if(!col[x]){
		f[1][x]=Mul(2,Mul(Add(L2,L3),Add(R2,R3)));
		f[2][x]=Mul(2,Mul(Add(L1,L3),Add(R1,R3)));
		f[3][x]=Mul(2,Mul(Add(L2,L1),Add(R2,R1)));
	}
	else{
		if(col[x]==1)f[1][x]=Mul(Add(L2,L3),Add(R2,R3));
		if(col[x]==2)f[2][x]=Mul(Add(L1,L3),Add(R1,R3));
		if(col[x]==3)f[3][x]=Mul(Add(L2,L1),Add(R2,R1));
	}
}
signed main(){
 	freopen("My.out","r",stdin);
	k=read();
	F[1]=0;
	for(int i=2;i<=60;++i){
		F[i]=Add(F[i-1],1,mod-1);
		F[i]=Mul(F[i],2,mod-1);
	}
	n=read();
	for(int i=1;i<=n;++i){
		int pos=read();
		cin>>s;
		if(s=="orange"||s=="red")col[pos]=1;
		if(s=="white"||s=="yellow")col[pos]=2;
		if(s=="blue"||s=="green")col[pos]=3;
		while(pos){
			Node.emplace_back(pos);
			pa[pos]=pos/2;
			if(pos%2==0)lson[pos/2]=pos;
			else rson[pos/2]=pos;
			pos/=2;
		}
	}
	sort(Node.begin(),Node.end());
	ll root=1;
	Treat();
	DP(root);
	int res=Add(f[3][root],Add(f[1][root],f[2][root]));
	write(res);putchar('\n');
	return 0;
}
```


---

## 作者：pyiming (赞：0)

# 题意简述

给定一个有 $2^k - 1$ 个节点的完美二叉树，你需要用魔方的 $6$ 种颜色（白、绿、红、蓝、橙、黄）为其节点着色。着色需满足：任意两个相邻节点不能是同色或相邻颜色（例如，白色不能与白色或黄色相邻）。此外，树中有 $n$ 个节点的颜色已预先确定。求不同的良好着色方式的数量，模 $10^9+7$ 输出。

# 思路

令 $\text{c}$ 为颜色总数。

有个很容易想到的 $\text{dp}$，设 $f(i,j)$ 表示以 $i$ 为根的子树内，根结点 $i$ 的颜色为 $j$ 的方案数。转移时只需要枚举当前结点 $i$ 的颜色和子结点 $2i$ 和 $2i+1$ 的颜色，就可以在 $O(c^3)$ 的时间复杂度内完成转移，总时间复杂度为 $O(2^kc^3)$。

但是 $k$ 的范围达到了 $60$，显然是不可以接受的。

注意到如果没有任何的结点被预先确定（就是 $\text{E1}$），显然，对于高度相同的子树，其 $\text{dp}$ 值都是相同的。而预先确定的结点只对其祖先有影响，不难想到，对于同一高度的子树，且其子树内没有预先确定的结点，可以统一计算。如果是子树内有预先确定的结点就单独处理即可，这样的点最多有 $O(nk)$ 个，显然是可以接受的。

具体来说，高度为 $x$ 的子树的所有颜色的 $\text{dp}$ 值均为 $16^{2^{x-1}-1}$。而单独处理的结点就从下往上维护，由于其值域较大，遂采用 $\text{map}$ 存储。

时间复杂度为 $O(nkc^3\log n)$，该方法要注意**卡常**，笔者使用了快速取模得以通过。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
map<ll,ll> t;
map<pair<ll,ll>,ll> f;
set<ll> q;
struct Mod
{
    ll m, p;
    void init(int pp) { m = ((__int128)1 << 64) / pp; p = pp; }
    ll operator ()(ll x)
    {
        return x - ((__int128(x) * m) >> 64) * p;
    }
}z;

int main(){
    z.init(mod);
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    ll k,n;
    cin>>k>>n;
    for(int i=1;i<=n;i++){
        ll v;
        string s;
        cin>>v>>s;
        q.insert(v);
        if(s=="white"){
            t[v]=1;
        }
        else if(s=="green"){
            t[v]=2;
        }
        else if(s=="red"){
            t[v]=3;
        }
        else if(s=="yellow"){
            t[v]=4;
        }
        else if(s=="blue"){
            t[v]=5;
        }
        else{
            t[v]=6;
        }
    }
    if(k==1){
        if(t[1]){
            cout<<1<<"\n";
        }
        else{
            cout<<6<<"\n";
        }
        return 0;
    }
    ll now=k;
    ll res=1;
    while(!q.empty()){
        auto it=q.end();
        it--;
        ll temp=*it;
        while(temp<(1ll<<(now-2))){
            res=16*res%mod*res%mod;
            now--;
        }//k==1的情况要特判
        if(temp>=(1ll<<(k-1))){
            if(t[temp]){
                int _=t[temp];
                for(int i=1;i<=6;i++){
                    if(i==_){
                        f[{temp,i}]=1;
                    }
                    else{
                        f[{temp,i}]=-1;
                    }
                }
            }
            else{
                for(int i=1;i<=6;i++){
                    f[{temp,i}]=1;
                }
            }
        }
        else{
            if(t[temp]){
                int _=t[temp];
                for(int i=1;i<=6;i++){
                    if(i==_){
                        for(int j=1;j<=6;j++) if(j!=i&&j!=(i+2)%6+1){
                            for(int k=1;k<=6;k++) if(k!=i&&k!=(i+2)%6+1){
                                if(f[{temp<<1,j}]==-1||f[{temp<<1|1,k}]==-1){
                                    continue;
                                }
                                f[{temp,i}]=(f[{temp,i}]+(f[{temp<<1,j}]?f[{temp<<1,j}]:res)*(f[{temp<<1|1,k}]?f[{temp<<1|1,k}]:res)%mod)%mod;
                            }
                        }
                        if(f[{temp,i}]==0){
                            f[{temp,i}]=-1;
                        }
                    }
                    else{
                        f[{temp,i}]=-1;
                    }
                }
            }
            else{
                
                for(int i=1;i<=6;i++){
                    ll sum=0;
                    for(int j=1;j<=6;j++) if(j!=i&&j!=(i+2)%6+1){
                        for(int k=1;k<=6;k++) if(k!=i&&k!=(i+2)%6+1){
                            if(f[{temp<<1,j}]==-1||f[{temp<<1|1,k}]==-1){
                                continue;
                            }
                            sum=z.operator()(sum+z.operator()((f[{temp<<1,j}]?f[{temp<<1,j}]:res)*(f[{temp<<1|1,k}]?f[{temp<<1|1,k}]:res)));
                        }
                    }
                    if(sum==0){
                        f[{temp,i}]=-1;
                    }
                    else{
                        f[{temp,i}]=sum;
                    }
                }
            }
        }
        q.erase(temp);
        if(temp!=1) q.insert(temp>>1);
        // for(int i=1;i<=6;i++){
        //     cout<<f[{temp,i}]<<" ";
        // }
        // cout<<"\n";
    }
    // res=16*res%mod*res%mod;
    ll sum=0;
    for(int i=1;i<=6;i++){
        if(f[{1,i}]==-1){
            continue;
        }
        sum=(sum+f[{1,i}])%mod;
    }
    cout<<sum<<"\n";
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

考虑一个简单的 dp，设 $dp_{i,j}$ 表示在 $i$ 的子树内，点 $i$ 的颜色是 $j$ 的方案数，设 $s_i$ 表示颜色 $i$ 不能选的集合，那么：

$$dp_{i,j}=(\sum_{k\notin s_j}dp_{lson,k})\times(\sum_{k\notin s_j}dp_{rson,k})$$

这样 dp 肯定是过不去的。但是我们发现当一个节点 $i$ 的子树内没有被选中的点，那么这个节点的子树内对于每种颜色 $j$ 均有 $4^{size_i-1}$ 种选法，即 $dp_{i,j}=4^{size_i-1}$，这样我们就优化掉了很多状态，可以通过本题。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
#define ls (u<<1)
#define rs (u<<1|1)
using namespace std;
int k,n,v[2005],w[2005];
map<string,int>mp;
map<int,int>mpp,vis,cnt,dp[6];
string s;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
void dfs(int u,int dep){
	if(dep==k){
		for(int i=0;i<6;i++)dp[i][u]=1;
		if(vis[u])for(int i=0;i<6;i++)if(i!=mpp[u])dp[i][u]=0;
		return;
	}
	if(!cnt[u]){
		for(int i=0;i<6;i++)dp[i][u]=ksm(4,(1ll<<(k-dep+1))-2);
		return;
	}
	dfs(ls,dep+1),dfs(rs,dep+1);
	int a1=0,a2=0;
	for(int i=0;i<6;i++)a1+=dp[i][ls],a2+=dp[i][rs];
	dp[0][u]=(a1-dp[0][ls]-dp[1][ls]+mod+mod)%mod*(a2-dp[0][rs]-dp[1][rs]+mod+mod)%mod;
	dp[1][u]=(a1-dp[0][ls]-dp[1][ls]+mod+mod)%mod*(a2-dp[0][rs]-dp[1][rs]+mod+mod)%mod;
	dp[2][u]=(a1-dp[2][ls]-dp[3][ls]+mod+mod)%mod*(a2-dp[2][rs]-dp[3][rs]+mod+mod)%mod;
	dp[3][u]=(a1-dp[2][ls]-dp[3][ls]+mod+mod)%mod*(a2-dp[2][rs]-dp[3][rs]+mod+mod)%mod;
	dp[4][u]=(a1-dp[4][ls]-dp[5][ls]+mod+mod)%mod*(a2-dp[4][rs]-dp[5][rs]+mod+mod)%mod;
	dp[5][u]=(a1-dp[4][ls]-dp[5][ls]+mod+mod)%mod*(a2-dp[4][rs]-dp[5][rs]+mod+mod)%mod;
	if(vis[u]){
		for(int i=0;i<6;i++)if(i!=mpp[u])dp[i][u]=0;
	}
} 
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	mp["white"]=0,mp["yellow"]=1,mp["green"]=2,mp["blue"]=3,mp["red"]=4,mp["orange"]=5;
	cin>>k>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>s;
		w[i]=mp[s],mpp[v[i]]=w[i],vis[v[i]]=1;
		int now=v[i];
		while(now){
			cnt[now]++,now/=2;
		}
	}
	dfs(1,1);
	int ans=0;
	for(int i=0;i<6;i++)ans+=dp[i][1],ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：alvis (赞：0)

## Content

给一个深度为 $k$ 的满二叉树，用 $6$ 种颜色染色，使得染色方案符合以下规定。（根节点深度为 $1$）

规定：

- 如果一个节点是白色的，那么相邻节点不能是白色的或黄色的。
- 如果一个节点是黄色的，那么相邻节点不能是白色的或黄色的。
- 如果一个节点是绿色的，那么相邻节点不能是绿色的或蓝色的。
- 如果一个节点是蓝色的，那么相邻节点不能是绿色的或蓝色的。
- 如果一个节点是红色的，那么相邻节点不能是红色的或橙色的。
- 如果一个节点是橙色的，那么相邻节点不能是红色的或橙色的。

现给定 $n$ 个点的颜色，试求染色方案数。

$1\le k\le60,1\le n\le2\times10^3$

## Solution

很明显是一个 dp。

但是一共有 $2^{60}-1$ 个点，所以直接上 dp 肯定是不行的。

由 $\texttt{E1}$ 可知，一个非根节点，且周围没有染色的点对答案的贡献为 $4$。

观察题目性质，可以发现每一个被规定了颜色的点，都只会对他临近的点染色的方案数造成影响。

虽然树的点很多，但是有颜色的点只有 $2000$ 个，所以可以建立一棵虚树，在虚树上跑 dp。

建好了虚树，dp就很显然了。

设 $f_{i,j}$ 表示以第 $i$ 个虚树上的点为根的子树中染第 $j$ 种颜色的方案数。

则 $f_{i,j} = \prod\limits_{u\in son(i)}\sum\limits_{k\in col(j)}f_{u,k}$

其中 $son(i)$ 表示点 $i$ 儿子，$col(j)$ 表示不与 $j$ 冲突的颜色。

即将点 $i$ 的左右两儿子染各种可能颜色的方案数求和，然后两结果相乘。

直接树形dp，然后统计答案即可。

最后将不在虚树中的点的方案数乘到答案中即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e6+5, P = 1e9 + 7;
int n, k;
int f[N][7], vis[N];
int son[N][2];
vector<pair<int,int> > col;
vector<int> g;

int get_c(char c) {
	if(c == 'w') return 0;
	if(c == 'y') return 1;
	if(c == 'g') return 2;
	if(c == 'b') return 3;
	if(c == 'o') return 4;
	if(c == 'r') return 5;
	return 0;
}

//查询当前点在虚树中位置
int get(int x) {
	return lower_bound(g.begin(), g.end(), x) - g.begin() + 1;
}

//检查颜色是否冲突
bool check(int a, int b) {
	if(a > b) swap(a, b);
	if(a == b || a == 0 && b == 1 || a == 2 && b == 3 || a == 4 && b == 5) return true;
	return false;
}

//树形dp计算
void dfs(int u) {
	if(!son[u][0]) {
		f[u][vis[u]] = 1;
		return ;
	}
	if(son[u][0]) dfs(son[u][0]);
	if(son[u][1]) dfs(son[u][1]);
	for(int i = 0;i < 6;i ++) {
		int a = 0, b = 0;
		if(vis[u] >= 0 && vis[u] <= 5 && vis[u] != i) continue;
		for(int j = 0;j < 6;j ++) {
			if(check(i, j)) continue;
			if(son[u][0]) a = (a + f[son[u][0]][j]) % P;
			if(son[u][1]) b = (b + f[son[u][1]][j]) % P;
		}
		if(son[u][1]) f[u][i] = (a * b) % P;
		else f[u][i] = a % P;
	}
}
//快速幂计算不在虚树中点的方案
long long qmi(int a, int t) {
	long long sum = 1;
	while(t) {
		if(t & 1) sum = sum * a % P;
		a = a * a % P;
		t >>= 1;
	}
	return sum;
}

signed main() {
	memset(vis, -1, sizeof vis);
	cin >> k >> n;
	for(int i = 1;i <= n;i ++) {
		int a;
		string s;
		cin >> a >> s;
		col.push_back(make_pair(a, get_c(s[0])));
	}
   	//建立虚树
	g.push_back(1);
	for(int i = 0;i < col.size();i ++) {
		int j = col[i].first;
		while(j) g.push_back(j), j /= 2; 
	}
	sort(g.begin(), g.end());
	g.erase(unique(g.begin(), g.end()), g.end());
    	//处理出虚树上点的父子关系
	for(int i = 0;i < col.size();i ++) {
		int j = col[i].first, w = col[i].second;
		while(true) {
			int a = get(j), b = get(j / 2);
			if(vis[a] != -1) break;
			vis[a] = 10;
			if(j == 1) break;
			if(son[b][0]) son[b][1] = a;
			else son[b][0] = a;
			j /= 2; 
		}
		vis[get(col[i].first)] = w;
	}
    
	dfs(1);
	int ans = 0;
	for(int i = 0;i < 6;i ++) ans = (ans + f[1][i]) % P;
	cout << ans * qmi(4, (1ll<<k) - 1 - (int)g.size()) % P;
	return 0;
} 
```

---

## 作者：mzgwty (赞：0)

开 VP 的时候非常勇，建了一棵标准的虚树，并没有去把点到根路径上的所有点都加进去，然后就很难写（

这里我们记 orange 为 0，red 为 1，blue 为 2，green 为 3，white 为 4，yellow 为 5，这样相对的颜色异或起来为 1，处理起来方便一些

套路地记 $f_{u,i}$ 为以 $u$ 为根的子树中， $u$ 的颜色为 $i$ 的方案数

首先把所有的深度最大的关键节点找出来，对于这些节点我们有 $f_{u,c_u}=4^{size_u-1}$

然后把转移矩阵写出来

$$
\begin{bmatrix}
0~~0~~1~~1~~1~~1\\
0~~0~~1~~1~~1~~1\\
1~~1~~0~~0~~1~~1\\
1~~1~~0~~0~~1~~1\\
1~~1~~1~~1~~0~~0\\
1~~1~~1~~1~~0~~0
\end{bmatrix}
\times
\begin{bmatrix}
f_{u,0}\\
f_{u,1}\\
f_{u,2}\\
f_{u,3}\\
f_{u,4}\\
f_{u,5}\\
\end{bmatrix}
=
\begin{bmatrix}
f_{fa,0}\\
f_{fa,1}\\
f_{fa,2}\\
f_{fa,3}\\
f_{fa,4}\\
f_{fa,5}\\
\end{bmatrix}
$$

转移的时候预处理出转移矩阵的 $1$ 到 $k$ 次幂就行了

对于 $u$ 子树中那些既不在关键点到 $u$ 路径上，又不在关键点的子树内部的点，相当于是 easy version，乘上 $4^{cnt}$ 就行了

那么点按 dfs 序排应该怎么弄呢

对于节点 $u,v$，我们先把深度较大的跳到另一个点的深度，然后比较此时这两个数的大小，如果大小相同的话，就比较原来 $u,v$ 的深度就行了

这里的 dfs 序其实就是二叉树的前序遍历

代码不是很好写，大致如下

```cpp
#include<stdio.h>
#include<math.h> 
#include<string.h>
#include<algorithm> 
#include<vector>
#include<map>
using namespace std;
 
typedef long long ll;
 
inline int read() {
	int res=0,f=1;char ch;
	while(ch=getchar(),ch<'0'||ch>'9') if(ch=='-') f=-1;
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
 
inline ll readll() {
	ll res=0,f=1;char ch;
	while(ch=getchar(),ch<'0'||ch>'9') if(ch=='-') f=-1;
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
 
const int N=4005,P=1e9+7;
 
ll qpow(ll a,ll b) {
	ll ans=1;b%=(P-1);
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ans*=a)%=P;
	return ans;
}
 
char str[154];
 
struct node {
	ll id;int val;
	inline node (ll I=0,int V=0) : id(I),val(V) {}
}p[N];
 
int k,m,t;
 
inline int getlen(ll x) {
	int l=0;while(x) x>>=1,++l;
	return l;
}
 
inline bool cmp(node a,node b) {
	ll x=a.id,y=b.id;int la=getlen(x),lb=getlen(y);
	if(la<lb) {
		y>>=(lb-la);
		return x<=y;
	}
	else {
		x>>=(la-lb);
		return x<y;
	}
}
 
inline ll LCA(ll a,ll b) {
	int la=getlen(a),lb=getlen(b);
	if(la<lb) swap(a,b),swap(la,lb);
	while(la>lb) a>>=1,--la;
	while(a!=b) a>>=1,b>>=1;
	return a;
}
 
struct matrix {
	ll a[6][6];
	inline void clear() {
		for(int i=0;i<6;++i)
			for(int j=0;j<6;++j)
				a[i][j]=0;
	}
}tmp,base,I,ml,mr,tp[61];
 
inline matrix operator * (const matrix &a,const matrix &b) {
	tmp.clear();
	for(int i=0;i<6;++i)
		for(int k=0;k<6;++k)
			if(a.a[i][k])
				for(int j=0;j<6;++j)
					(tmp.a[i][j]+=a.a[i][k]*b.a[k][j]%P)%=P;
	return tmp;
}
 
struct Node {
	ll size,lc,rc,f[6],id;
	int c;
};
 
ll s[N];
 
map <ll,Node> w;
 
inline ll getsize(ll len) {return (2ll<<k-len)-1;}
 
void dfs(ll u) {
	w[u].size=getsize(getlen(u));
	if(w[u].lc) {
		ll lc=w[u].lc,rc=w[u].rc;
		if(lc) dfs(lc);if(rc) dfs(rc);
		int l1=getlen(lc)-getlen(u)-1,l2=getlen(rc)-getlen(u)-1;
		if(l1<0) l1=0;if(l2<0) l2=0;
		ll rem=qpow(4,w[u].size-1-w[lc].size-w[rc].size-l1-l2);
		ml=tp[l1],mr=tp[l2];
		for(int i=0;i<6;++i)
			if(w[u].c==6||w[u].c==i) {
				ll c1=0,c2=0;
				for(int j=0;j<6;++j)
					if((i^j)>1) {
						for(int k=0;k<6;++k) (c1+=ml.a[k][j]*w[lc].f[k]%P)%=P;
					}
				for(int j=0;j<6;++j)
					if((i^j)>1) {
						for(int k=0;k<6;++k) (c2+=mr.a[k][j]*w[rc].f[k]%P)%=P;
					}
				if(rc) w[u].f[i]=c1*c2%P*rem%P;
				else w[u].f[i]=c1*rem%P;
			}
	}
	else {
		for(int i=0;i<6;++i)
			if(w[u].c==6||w[u].c==i)
				w[u].f[i]=qpow(4,w[u].size-1);
	}
}
 
int main() {
	k=read(),m=read();
	for(int i=0;i<6;++i)
		for(int j=0;j<6;++j)
			I.a[i][j]=(i==j);
	for(int i=0;i<6;++i)
		for(int j=0;j<6;++j)
			base.a[i][j]=((i^j)>1);
	tp[0]=I;
	for(int i=1;i<=60;++i) tp[i]=tp[i-1]*base;
	for(int i=1;i<=m;++i) {
		ll x=readll();int c;scanf("%s",str);
		if(str[0]=='o') c=0;
		else if(str[0]=='r') c=1;
		else if(str[0]=='b') c=2;
		else if(str[0]=='g') c=3;
		else if(str[0]=='w') c=4;
		else c=5;
		p[i]=node(x,c),w[x].c=c;
	}
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<m;++i)
		if(p[i].id==p[i+1].id>>1&&p[i].val==p[i+1].val) return !printf("0");
		else if(p[i].id==p[i+1].id&&p[i].val!=p[i+1].val) return !printf("0");
	s[t=1]=1,w[1].c=6;
	for(int i=1;i<=m;++i) {
		if(p[i].id==s[t]) {w[s[t]].c=p[i].val;continue ;}
		if(LCA(s[t],p[i].id)==s[t]) {s[++t]=p[i].id;continue ;}
		while(t&&(t==1||LCA(s[t-1],p[i].id)!=s[t-1])) {
			if(!w[s[t-1]].lc) w[s[t-1]].lc=s[t];
			else w[s[t-1]].rc=s[t];
			--t;
		}
		ll lca=LCA(s[t],p[i].id);
		if(w[lca].lc) w[lca].rc=s[t];
		else w[lca].lc=s[t];
		if(lca!=s[t-1]) s[t]=lca,w[lca].c=6;
		else --t;
		s[++t]=p[i].id;
	}
	while(t) {
		if(w[s[t-1]].lc) w[s[t-1]].rc=s[t];
		else w[s[t-1]].lc=s[t];
		--t;
	}
	dfs(1);
	ll res=0;
	for(int i=0;i<6;++i) (res+=w[1].f[i])%=P;
	printf("%lld",res);
	return 0;
}
```

---

## 作者：WitheredZeal (赞：0)


## 题意  

有一棵深度为 $k$ 的满二叉树（根节点深度为 $1$）。  
你要用 $6$ 种颜色去染色，使得相邻节点颜色不同，并且也不会是魔方对面的两个面的颜色。  
具体来说：  
- 如果一个节点是白色的，那么相邻节点不能是白色的或黄色的。 
- 如果一个节点是黄色的，那么相邻节点不能是白色的或黄色的。 
- 如果一个节点是绿色的，那么相邻节点不能是绿色的或蓝色的。 
- 如果一个节点是蓝色的，那么相邻节点不能是绿色的或蓝色的。 
- 如果一个节点是红色的，那么相邻节点不能是红色的或橙色的。 
- 如果一个节点是橙色的，那么相邻节点不能是红色的或橙色的。 

现在已知了 $n$ 个节点的颜色信息（在 E1 中为 0），求给整棵树染色的方案数。  

## 题解  

[上接 E1 题解](https://www.luogu.com.cn/blog/FOOLISH-JUSTIN/solution-cf1594e1)  

我们考虑，如果一个点自身及所有后代都没有被钦定过颜色，那么他的贡献可以直接用公式来算。  
那么我们发现，不能用公式来算的颜色不超过 $nk$ 个。  
我们考虑计算出一个节点，钦定它是什么颜色，它的子树的染色方案数，并且用记忆化搜索。   

然后直接从儿子那里转移就行了，复杂度是 $O(c^3 nk)$，其中 $c=6$ 表示颜色数量。  
常数可能比较大，反正加上预编译命令能过。

## 代码

```cpp

#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#define rd(x) x=read()
#define wt(x) write(x)
#define endl "\n"
using namespace std;
const int N=2e6+5;
const int mod=1e9+7;
int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar('-');x=-x;}if(x>=10)write(x/10);putchar(x%10+'0');}
int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}

int n,m,k,ans,cnt;
unordered_map<int,int> Map;
int L(int x){for (int i=60;i>=0;i--) if (x>>i&1) return i;}
int G(int k){if (k==0) return 1;int t=(ksm(2,k,mod-1)-2+mod-1)%(mod-1);return ksm(4,t);}
bool chk(int x,int y){if (x==y || x+y==7) return 0;return 1;}
unordered_map<int,int> f[7];
unordered_map<int,int> v[7];
int F(int x,int y)
{
	if (v[y][x]) return f[y][x];
	int ret=0;
	if (!Map[x]) return G(k-L(x));
	if (Map[x]==7)
	{
		if (k-L(x)==1) return 1;
		for (int a=1;a<=6;a++) if (chk(a,y)) for (int b=1;b<=6;b++) if (chk(b,y)) ret=(ret+F(x*2,a)*F(x*2+1,b))%mod;
	} else 
	{
		if (Map[x]!=y) return 0;
		if (k-L(x)==1) return 1;
		for (int a=1;a<=6;a++) if (chk(a,y)) for (int b=1;b<=6;b++) if (chk(b,y)) ret=(ret+F(x*2,a)*F(x*2+1,b))%mod;
	}
	v[y][x]=1;
	return f[y][x]=ret;
}
char s[N];
void insert(int x,int c)
{
	if (x==0) return;
	if (Map[x]!=7 && Map[x]!=0 && Map[x]!=c && c!=7) {puts("0");exit(0);}
	if (!Map[x] || Map[x]==7) Map[x]=c;
	insert(x/2,7);
}
signed main()
{
	rd(k);rd(n);
	while (n--)
	{
		int x;rd(x);scanf("%s",s);
		if (s[0]=='w') insert(x,1);
		if (s[0]=='r') insert(x,2);
		if (s[0]=='g') insert(x,3);
		if (s[0]=='b') insert(x,4);
		if (s[0]=='o') insert(x,5);
		if (s[0]=='y') insert(x,6);
	}
	for (int i=1;i<=6;i++) ans+=F(1,i);
	cout<<ans%mod<<endl;
}
```

---

