# Rubik's Cube Coloring (easy version)

## 题目描述

It is the easy version of the problem. The difference is that in this version, there are no nodes with already chosen colors.

Theofanis is starving, and he wants to eat his favorite food, sheftalia. However, he should first finish his homework. Can you help him with this problem?

You have a perfect binary tree of $ 2^k - 1 $ nodes — a binary tree where all vertices $ i $ from $ 1 $ to $ 2^{k - 1} - 1 $ have exactly two children: vertices $ 2i $ and $ 2i + 1 $ . Vertices from $ 2^{k - 1} $ to $ 2^k - 1 $ don't have any children. You want to color its vertices with the $ 6 $ Rubik's cube colors (White, Green, Red, Blue, Orange and Yellow).

Let's call a coloring good when all edges connect nodes with colors that are neighboring sides in the Rubik's cube.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/b0755608caf4588a1ceffdca8e2be827560017bc.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/c6ef9fa6fcd45f3211d7baf9a8cc69c074f640a9.png)A picture of Rubik's cube and its 2D map.More formally:

- a white node can not be neighboring with white and yellow nodes;
- a yellow node can not be neighboring with white and yellow nodes;
- a green node can not be neighboring with green and blue nodes;
- a blue node can not be neighboring with green and blue nodes;
- a red node can not be neighboring with red and orange nodes;
- an orange node can not be neighboring with red and orange nodes;

You want to calculate the number of the good colorings of the binary tree. Two colorings are considered different if at least one node is colored with a different color.

The answer may be too large, so output the answer modulo $ 10^9+7 $ .

## 说明/提示

In the picture below, you can see one of the correct colorings of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/dcebca3c4893383a751dc627ead5632c7d038ce7.png)

## 样例 #1

### 输入

```
3```

### 输出

```
24576```

## 样例 #2

### 输入

```
14```

### 输出

```
934234```

# 题解

## 作者：XL4453 (赞：4)

### 解题思路：

官方题解说的是用数学方法直接推导出方案数为 $6\times 4^{2^{k}-2}$，但是这一种做法似乎并不能很方便地拓展到这道题的加强版，所以介绍一种利用动态规划的方法求解。

由于没有颜色已经被限制，所以所有的颜色都是对称的，只需要求出任意一种颜色的方案数直接乘以 $6$ 就是总方案了。

设 $f_i$ 为某一种颜色在一颗高度为 $i$ 的满二叉树上的方案数，其中 $f_1$ 显然是 $1$。

对于 $f_{i+1}$ 这个值等于左右两个子树方案数相乘，由于这里的 $f_i$ 是每一种颜色的方案，所以还需要乘上 $16$ 作为不同颜色方案的搭配（左子树 $4$ 种可选颜色方案，右子树也是，乘法原理直接算）。

形式化地，有 $f_{i+1}=16\times f_i^2$，需要注意取模。


---
### 代码：
```cpp
#include<cstdio>
using namespace std;
long long n,MOD=1e9+7,f[65];
int main(){
	scanf("%d",&n);
	f[1]=1;
	for(int i=2;i<=n+1;i++){
		f[i]=(f[i-1]*f[i-1])%MOD*16%MOD;
	}
	printf("%lld",f[n]*6%MOD);
	return 0;
}
```


---

## 作者：vectorwyx (赞：1)

题意：给一棵深度为 $k$ 的满二叉树染色，同色和对色不能相邻（对色是指标准魔方相对两面的颜色），求方案数。

方法 $1$：树形 dp。令 $f(i,j)$ 表示深度为 $i$ 的满二叉树，且根结点颜色为 $j$ 时的方案数，转移时枚举左右子树的根结点染什么颜色。

代码如下：
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define int ll 
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%lld ",*(a+i));puts("");}

const int N=1e6+5,qlr=1e9+7;
int f[N][7];
//white:1 yellow:6
//green:2 blue:5
//red:3 orange:4

signed main(){
	int n=read();
	fo(i,1,6) f[1][i]=1;
	fo(i,2,n)
		fo(j,1,6)
			fo(k,1,6)if(j!=k&&j+k!=7)
				fo(w,1,6)if(j!=w&&j+w!=7)  f[i][j]=(f[i][j]+f[i-1][k]*f[i-1][w])%qlr;
	int ans=0;
	fo(i,1,6) ans=(ans+f[n][i])%qlr;
	cout<<ans;
	return 0;
}
/*
-------------------------------------------------
*/

```


方法 $2$：直接计数：根结点有 $6$ 种选择，根结点的颜色确定之后自顶向下依次染色，每个结点有且仅有 $4$ 种选择，因此答案为 $6\times 4^{2^{k}-2}$。

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

const int qlr=1e9+7;
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
	int k=read(),w=(1ll<<k)-2;
	cout<<6*ksm(4,w)%qlr;
	return 0;
}

```



---

## 作者：Huami360 (赞：1)

显然根节点有 $6$ 种方案，其余所有点都是 $4$ 种，互不干扰。
故答案为
$$6*4^{2^k-2}$$
输出即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
typedef long long ll;
const int MOD = 1e9 + 7;
int fast_pow(ll n, ll k){
	int ans = 1;
	while(k){
		if(k & 1) ans = ans * n % MOD;
		n = n * n % MOD;
		k >>= 1;
	}
	return ans;
}
ll ans;
int main(){
	scanf("%d", &n);
	ans = 6ll * fast_pow(4, (1ll<<n)-2) % MOD;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：GaryH (赞：0)

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

有一个公式：$6 \times 4^{2^k-2}$。  
解释就是，如果确定了父亲节点的颜色，那么这个节点的颜色只有 $4$ 种可能了。  
但是根节点没有父亲节点，所以还是有 $6$ 种可能。因此答案为 $6 \times 4 ^{2^k -2}$。  

代码不放了，注意幂次要对 $10^9+6$ 取模而不是 $10^9+7$。

---

## 作者：Refined_heart (赞：0)

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

## 作者：tZEROちゃん (赞：0)

### Solution

显然，对于第一个 node 你有 6 种选择，对于其他的 node 你有 4 种选择，所以答案就是 $6 \cdot 4 ^ {2^{k} - 2}$，然后就没了。

### Code

```python3
k = int(input())
print(6 * (pow(4, (pow(2, k) - 2), 1000000007)) % 1000000007)
```

---

