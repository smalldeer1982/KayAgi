# Black Widow

## 题目描述

Natalia Romanova is trying to test something on the new gun S.H.I.E.L.D gave her. In order to determine the result of the test, she needs to find the number of answers to a certain equation. The equation is of form:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/1d8b978fb9a12b135427c0c260993d6889a8fc0c.png)

Where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/7fca95146e6c9642c62830d4709435706988c675.png) represents logical OR and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/4298d47c0191af3c0a3103f431751061bc7e2362.png) represents logical exclusive OR (XOR), and $ v_{i,j} $ are some boolean variables or their negations. Natalia calls the left side of the equation a XNF formula. Each statement in brackets is called a clause, and $ v_{i,j} $ are called literals.

In the equation Natalia has, the left side is actually a 2-XNF-2 containing variables $ x_{1},x_{2},...,x_{m} $ and their negations. An XNF formula is 2-XNF-2 if:

1. For each $ 1<=i<=n $ , $ k_{i}<=2 $ , i.e. the size of each clause doesn't exceed two.
2. Each variable occurs in the formula at most two times (with negation and without negation in total). Please note that it's possible that a variable occurs twice but its negation doesn't occur in any clause (or vice versa).

Natalia is given a formula of $ m $ variables, consisting of $ n $ clauses. Please, make sure to check the samples in order to properly understand how the formula looks like.

Natalia is more into fight than theory, so she asked you to tell her the number of answers to this equation. More precisely, you need to find the number of ways to set $ x_{1},...,x_{m} $ with $ true $ and $ false $ (out of total of $ 2^{m} $ ways) so that the equation is satisfied. Since this number can be extremely large, you need to print the answer modulo $ 10^{9}+7 $ .

Please, note that some variable may appear twice in one clause, or not appear in the equation at all (but still, setting it to $ false $ or $ true $ gives different ways to set variables).

## 说明/提示

The equation in the first sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/8a7d0715aca7a7756df4c64309d02f2f1b4790fe.png)The equation in the second sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/e73ae748289a1c91c6e0a8548db01f380614ddbc.png)The equation in the third sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/bdaba6b1526d3afbd73f7d5f247c3b948989c742.png)

## 样例 #1

### 输入

```
6 7
2 4 -2
2 6 3
2 -7 1
2 -5 1
2 3 6
2 -2 -5
```

### 输出

```
48
```

## 样例 #2

### 输入

```
8 10
1 -5
2 4 -6
2 -2 -6
2 -7 9
2 10 -1
2 3 -1
2 -8 9
2 5 8
```

### 输出

```
544
```

## 样例 #3

### 输入

```
2 3
2 1 1
2 -3 3
```

### 输出

```
4
```

# 题解

## 作者：CYJian (赞：11)

考虑到 $x_i$ 和 $x_{-i}$ 一共只会出现最多两次。

我们就将每个表达式看成一个点，若某两个表达式存在 $x_i$ 或 $x_{-i}$，则将这两个表达式代表的点之间连一条边，边权为 $0/1$，表示两个表达式中， $x$ 的下标相同/不同。

不难发现，这样连出的东西一定是一堆环和链。环可以通过拆一条边变成链，成了链之后就没有后效性了，就可以考虑 dp 了。

考虑设状态 $f_{i,0/1,0/1}$ 表示，考虑到当前这个连通块的第 $i$ 个表达式，当前异或值为 $0/1$，第 $i-1$ 到第 $i$ 个表达式所共有的变量，在第 $i$ 个表达式中的值为 $0/1$ 的方案数。

转移不难考虑，就手动计算一下包括边权在内的 $8$ 种情况，算出表达式的取值以及对答案的贡献，手动转移就行了。

然后我们先考虑一些特殊一点的情况：（这里仅做整合，具体细节参见代码）

#### 一、一个表达式中同时有 $x_i$ 和 $x_{-i}$

不难发现，这个点一定对答案有一个 $1$ 的贡献。提前算好就行了。

#### 二、一个表达式中有两个 $x_i$ 或 $x_{-i}$

这样的表达式，我们就当它是只有一个的孤点就行了。（虽然不知道数据里头有没有这种情况）

#### 三、一条链的端点的表达式可能有一个只出现了一次的 $x_i$

这种情况，就考虑枚举开头那个 $x_i$ 是啥，在 $f_{1,0,x_i}$ 赋值为 $1$ 就行了。

然后对于结尾上，我们也可以枚举一下 $x_i$ 上是啥，手动算一下 $x_i$ 对最后一个位置的状态影响就行了。

#### 四、环拆链

随便选一条边，枚举 $x_i$ 的取值，然后类似第三条做就行了。

#### 五、一个点同时有两个只出现了一次的 $x_i$

不难发现，这个点有 $3$ 种情况为 $1$， $1$ 种情况为 $0$。

这个数值不难计算，但是可能在分析的时候漏了这种情况导致实现不好的情况下会算挂。

---

总之这题细节挺多，挺恶心人的，如果想不清楚可以参见代码。

$\rm Code$：

```cpp
const int MAXN = 100010;
const int mod = 1e9 + 7;

inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline void Add(int&x, int y) { x += y, x -= x >= mod ? mod : 0; }

int id[MAXN];
int sgn[MAXN];
int deg[MAXN];
int vis[MAXN];

int tot;
int to[MAXN << 1];
int ne[MAXN << 1];
int rv[MAXN << 1];
int fi[MAXN];
int dg[MAXN];

inline void Link(int u, int v, int w) {
	tot++;
	to[tot] = v;
	rv[tot] = w;
	ne[tot] = fi[u];
	fi[u] = tot;
}

inline void AddEdge(int u, int v, int w) {
	Link(u, v, w), Link(v, u, w), ++dg[u], ++dg[v];
}

int rev[MAXN];
int sta[MAXN];
int top;

inline void dfs(int x) {
	sta[++top] = x, vis[x] = 1;
	for(int i = fi[x]; i; i = ne[i]) {
		int u = to[i];
		if(vis[u]) continue;
		rev[top] = rv[i];
		dfs(u);
	}
}

int res[2];

int main() {
	int m = ri, n = ri, c0 = 0, c1 = 0;
	for(int i = 1; i <= m; i++) {
		int k = ri, x, y;
		if(k == 2) x = ri, y = ri;
		else x = ri;
		deg[i] = k;
		if(k == 2) {
			if(x == y) { c0++, vis[i] = 1, id[abs(x)] = i; continue; }
			if(x == -y) { c1++, vis[i] = 1, id[abs(x)] = i; continue; }
		}
		if(id[abs(x)]) AddEdge(i, id[abs(x)], (x < 0) ^ sgn[abs(x)]);
		else id[abs(x)] = i, sgn[abs(x)] = x < 0;
		if(k == 2) {
			if(id[abs(y)]) AddEdge(i, id[abs(y)], (y < 0) ^ sgn[abs(y)]);
			else id[abs(y)] = i, sgn[abs(y)] = y < 0;
		}
	} res[0] = 1;
	while(c0--) res[0] = res[1] = Mod(res[0] + res[1]);
	while(c1--) res[0] = Mod(res[0] << 1), res[1] = Mod(res[1] << 1), swap(res[0], res[1]);
	int mul = 1;
	for(int i = 1; i <= n; i++) if(!id[i]) mul = Mod(mul << 1);
	for(int i = 1; i <= m; i++) {
		if(vis[i]) continue;
		if(!dg[i]) {
			vis[i] = 1;
			if(deg[i] == 1) res[0] = res[1] = Mod(res[0] + res[1]);
			else {
				int tr0 = (res[0] + 3LL * res[1]) % mod;
				int tr1 = (3LL * res[0] + res[1]) % mod;
				res[0] = tr0, res[1] = tr1;
			}
		}
		if(dg[i] == 1) {
			top = 0, dfs(i);
			int r0 = 1, r1 = 0, r2 = 0, r3 = 0;
			if(deg[sta[1]] == 2) r2 = 1;
			for(int j = 1; j < top; j++) {
				int tr0, tr1, tr2, tr3;
				if(rev[j]) {
					tr0 = Mod(r1 + r3), tr1 = Mod(r0 + r2);
					tr2 = Mod(r0 + r3), tr3 = Mod(r1 + r2);
				} else {
					tr0 = Mod(r0 + r3), tr1 = Mod(r1 + r2);
					tr2 = Mod(r1 + r3), tr3 = Mod(r0 + r2);
				} r0 = tr0, r1 = tr1, r2 = tr2, r3 = tr3;
			}
			if(deg[sta[top]] == 2) Add(r2, Mod(r0 + r2)), Add(r3, Mod(r3 + r1));
			Add(r0, r3), Add(r1, r2);
			int tr0 = (1LL * r0 * res[0] + 1LL * r1 * res[1]) % mod;
			int tr1 = (1LL * r1 * res[0] + 1LL * r0 * res[1]) % mod;
			res[0] = tr0, res[1] = tr1;
		}
	}
	for(int i = 1; i <= m; i++) {
		if(vis[i]) continue;
		top = 0, dfs(i);
		int R0 = 0, R1 = 0, r0, r1, r2, r3, Rv = 0;
		for(int j = fi[sta[1]]; j; j = ne[j])
			if(to[j] == sta[top]) Rv = rv[j];
		r0 = 1, r1 = 0, r2 = 0, r3 = 0;
		for(int j = 1; j < top; j++) {
			int tr0, tr1, tr2, tr3;
			if(rev[j]) {
				tr0 = Mod(r1 + r3), tr1 = Mod(r0 + r2);
				tr2 = Mod(r0 + r3), tr3 = Mod(r1 + r2);
			} else {
				tr0 = Mod(r0 + r3), tr1 = Mod(r1 + r2);
				tr2 = Mod(r1 + r3), tr3 = Mod(r0 + r2);
			} r0 = tr0, r1 = tr1, r2 = tr2, r3 = tr3;
		}
		if(Rv) R0 = Mod(r1 + r3), R1 = Mod(r0 + r2);
		else R0 = Mod(r0 + r3), R1 = Mod(r1 + r2);
		r0 = 0, r1 = 0, r2 = 1, r3 = 0;
		for(int j = 1; j < top; j++) {
			int tr0, tr1, tr2, tr3;
			if(rev[j]) {
				tr0 = Mod(r1 + r3), tr1 = Mod(r0 + r2);
				tr2 = Mod(r0 + r3), tr3 = Mod(r1 + r2);
			} else {
				tr0 = Mod(r0 + r3), tr1 = Mod(r1 + r2);
				tr2 = Mod(r1 + r3), tr3 = Mod(r0 + r2);
			} r0 = tr0, r1 = tr1, r2 = tr2, r3 = tr3;
		}
		if(Rv) Add(R0, Mod(r0 + r3)), Add(R1, Mod(r1 + r2));
		else Add(R0, Mod(r1 + r3)), Add(R1, Mod(r0 + r2));
		int tr0 = (1LL * R0 * res[0] + 1LL * R1 * res[1]) % mod;
		int tr1 = (1LL * R1 * res[0] + 1LL * R0 * res[1]) % mod;
		res[0] = tr0, res[1] = tr1;
	} cout << 1LL * res[1] * mul % mod << endl;
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：3)

## 题目大意

给定 $m$ 个布尔变量 $x_i$，与 $n$ 个布尔表达式 $x_i$ 或者 $x_i \vee x_j$。如果 $i<0$，则 $x_i$ 表示 $x_{-i}$ 取反。$x_i$ 与 $x_{-i}$ 在表达式中一共最多出现 $2$ 次。问在 $2^m$ 次方种取值方式中，有多少种满足每个表达式的值异或起来为 $1$。

## 题目分析

水题。

这种一共出现 $2$ 次的条件容易让我们想到图论建模再套 dp。

把表达式当成点，两个表达式同时包含 $x_i$ 或是 $x_{-i}$，等同于存在一组约束关系，我们按这个约束关系连边，用边权为 $0/1$ 表示是值相同还是值相反。

所以最多出现两次说明每个 $x_i$ 最多连一条边，这就没那么复杂。而表达式最多包含两个变量，则其度数小于等于 $2$。说明图中仅存在链和环。

对于链，只需要从一个端点开始 dp，和序列 dp 一样，我们设状态 $f_{i,0/1,0/1}$ 表示处理到第 $i$ 个位置，与第 $i+1$ 相连的变量取了 $0/1$，前缀的异或值为 $0/1$ 的方案数，转移很简单，稍微分类讨论一下就行了。

对于环，就是很简单的套路，断环为链，枚举断掉的边对应的变量的取值，然后正常按链做，最后只统计最后一个的，符合断掉的那条边的约束关系的取值所对应的答案。

没了，复杂度 $O(n)$。

具体实现时要注意：自环单独处理，链要按照端点的表达式形式初始化与统计答案，表达式没有设计的变量由于没参与 dp，所以还会使答案乘 $2$。

真没了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for (int i = h[x], y = to[i]; i; i = nxt[i], y = to[i])
#define Pi pair<int, int>
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e5+5,mod=1e9+7;
using namespace std;
int n=read(),m=read(),h[N],to[N<<1],nxt[N<<1],w[N<<1],cnt=1,a[N],deg[N];
inline void add(int a,int b,int c){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c,deg[b]++;
}
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
bool vis[N],v[N];
vector<Pi >p[N];
int s[N],tp,val[N],fg[N][2],tot,f[N][2][2];//i-th,与i+1相连的取了 0/1, 当前总异或值为 0/1 
inline void dfs(int x){
	vis[x]=1;
	e(x)if(!vis[y])s[++tp]=y,val[tp]=w[i],dfs(y);
} 
//如果是环，return -1，否则，return 端点 
inline int dfs(int x,int fr){
	v[x]=1;
	e(x)if(i^fr^1){
		if(v[y])return -1;
		return dfs(y,i);
	} 
	return x;
}
inline void pre(){
	rep(i,1,tp)f[i][1][1]=f[i][1][0]=f[i][0][1]=f[i][0][0]=0;
}
inline void Dp(){
	rep(i,2,tp){
		f[i][0][0]=Add(f[i-1][1^val[i]][1],f[i-1][val[i]][0]);
		f[i][0][1]=Add(f[i-1][1^val[i]][0],f[i-1][val[i]][1]);
		f[i][1][0]=Add(f[i-1][1][1],f[i-1][0][1]);
		f[i][1][1]=Add(f[i-1][1][0],f[i-1][0][0]);
	}
}
inline void sol_circle(int x){
	tp=1,s[1]=x,dfs(x),tot++,pre();
	int k;
	e(x)if(y==s[tp])k=w[i];
	//取0
	f[1][0][0]=f[1][1][1]=1,Dp(); 
	fg[tot][1]=f[tp][k][1],fg[tot][0]=f[tp][k][0],pre();
	//取1 
	f[1][0][1]=f[1][1][1]=1,Dp(); 
	add(fg[tot][1],f[tp][k^1][1]),add(fg[tot][0],f[tp][k^1][0]); 
}
inline void sol_line(int x){
	tp=1,s[1]=x,dfs(x),tot++,pre();
	if(tp==1){
		if(!deg[x])fg[tot][0]=1,fg[tot][1]=1+(a[x]==2)*2;
		else {
			int k=w[h[x]];
			if(k==0)fg[tot][0]=fg[tot][1]=1;
			else fg[tot][1]=2;
		}
		return;
	}
	if(a[x]==1)f[1][0][0]=f[1][1][1]=1;
	else f[1][0][0]=1,f[1][0][1]=1,f[1][1][1]=2;
	Dp();
	fg[tot][1]=f[tp][0][1];
	fg[tot][0]=f[tp][0][0];
	if(a[s[tp]]==2)add(fg[tot][1],f[tp][1][1]),add(fg[tot][0],f[tp][1][0]);
}
inline void solve(int x){
	int s=dfs(x,0);
	if(s>0)sol_line(s);
	else sol_circle(x);
}
signed main(){
	repn(i){
		a[i]=read();
		int x=read(),y=0;
		if(a[i]==2)y=read();
		if(x>0)p[x].pb({i,1});
		else p[-x].pb({i,0});
		if(y>0)p[y].pb({i,1});
		if(y<0)p[-y].pb({i,0});
	}
	int ct=0;
	repm(i){
		int sz=p[i].size();
		if(sz==2)add(p[i][0].first,p[i][1].first,p[i][0].second^p[i][1].second),add(p[i][1].first,p[i][0].first,p[i][0].second^p[i][1].second);
		ct+=!sz;
	}
	repn(i)if(!vis[i])solve(i);
	int w0=fg[1][0],w1=fg[1][1],nx0,nx1;
	rep(i,2,tot){
		nx0=Add(mul(w0,fg[i][0]),mul(w1,fg[i][1]));
		nx1=Add(mul(w0,fg[i][1]),mul(w1,fg[i][0]));
		w0=nx0,w1=nx1;
	}
	rep(i,1,ct)Mul(w1,2);
	pf(w1);
	return 0;
}
```


---

## 作者：xht (赞：3)

> [CF704C Black Widow](https://codeforces.com/contest/704/problem/C)

## 题意

- 有 $m$ 个布尔变量 $x_{1\dots m}$，设 $x_{-i}=\neg x_{i}$。
- 给定 $n$ 个形如 $x_i$ 或 $x_i \operatorname{or} x_j$ 的表达式，保证 $x_i$ 和 $x_{-i}$ 在所有表达式中一共只会出现最多两次。
- 询问在 $2^m$ 种不同的取值方案中，有多少种方案使得所有表达式的值的异或为 $1$。
- $n,m \le 10^5$，答案对 $10^9+7$ 取模。

## 题解

将每个表达式看成一个点。定义一个点的值为这个点对应的表达式的值，一个连通块的值为连通块内点的值的异或，整个图的值为所有连通块的值的异或。我们要求的就是整个图的值为 $1$ 的方案数。

由于保证 $x_i$ 和 $x_{-i}$ 在所有表达式中一共只会出现最多两次，如果两个表达式存在相同的 $x_{|i|}$，则连一条边。

假设我们求出来了每个连通块的值为 $0/1$ 的方案数，那么 dp 一次即可求出整个图的值为 $0/1$ 的方案数：

> 设 $c_{i,0/1}$ 表示第 $i$ 个连通块值为 $0/1$ 的方案数。
>
> 设 $f_{i,0/1}$ 表示只考虑前 $i$ 个连通块，值为 $0/1$ 的方案数。
>
> 初始状态：$f_{0,0} = 1$。
>
> 目标状态：$f_{*,1}$。
>
> 转移：$f_{i,j} = f_{i-1,j} \times c_{i,0} + f_{i-1,j \operatorname{xor} 1} \times c_{i,1}$。

现在考虑如何对于每个连通块求 $c_{0/1}$。

注意到连出来的图一定由若干个连通块组成的，而连通块只有四种形态，我们分别考虑。

### 一个点的链

表达式形如 $x_i$，则 $c_{0} = c_1 = 1$。

表达式形如 $x_i \operatorname{or} x_j$，则 $c_0 = 1$，$c_1 = 3$。

### 一个点的环

表达式形如 $x_i \operatorname{or} x_i$，则 $c_0 = c_1 = 1$。

表达式形如 $x_i \operatorname{or} x_{-i}$，则 $c_0 = 0$，$c_1 = 2$。

### 至少两个点的链

这种形态下，链的两端对应的表达式可能形如 $x_i$，也可能形如 $x_i \operatorname{or} x_j$。

如果形如 $x_i$，我们可以把它当做 $x_i \operatorname{or} 0$ 看待，然后依然考虑 dp。

> 设第 $i$ 个点上的表达式为 $x_{p_i} \operatorname{or} x_{q_i}$，其中 $x_{|q_{i-1}|} = x_{|p_i|}$。
>
> 设 $g_{i,0/1,0/1}$ 表示只考虑前 $i$ 个点，值为 $0/1$，$x_{|q_i|} = 0/1$ 的方案数。
>
> 初始状态：对于 $x_{|p_1|}$ 的每种取值，$g_{0,0,x_{|p_1|}} = 1$。
>
> 目标状态：对于 $x_{|q_{*}|}$ 的每种取值，$c_0 \leftarrow g_{*,0,x_{|q_{*}|}}$，$c_1 \leftarrow g_{*,1,x_{|q_{*}|}}$。
>
> 转移：对于 $x_{|p_i|},x_{|q_i|}$ 的每种取值，$g_{i,(x_{p_i} \operatorname{or} x_{q_i}) \operatorname{xor} j,x_{|q_i|}} \leftarrow \sum_{j=0}^1 g_{i-1,j,x_{|p_i|}}$。

### 至少两个点的环

随便选一条边断开，转化成**至少两个点的链**的形态。

对于断开处的变量，枚举它的值 $w$ 为 $0/1$，然后把两端当做 $x_i \operatorname{or} w$ 看待。

然后用**至少两个点的链**的方法做即可。

## 代码

```cpp
const int N = 1e5 + 7;
int n, m, d[N], k, v[N];
vi a[N], b[N], e[N], s;
modint f[N][2], c[2], g[N][2][2], ans = 1;

void dfs(int x) {
	v[x] = k, s.pb(x);
	for (int y : e[x])
		if (!v[y]) dfs(y);
}

inline void dp(int l1, int r1, int l2, int r2) {
	int t = s.size();
	for (int i = 0; i <= t; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				g[i][j][k] = 0;
	for (int i = l1; i <= r1; i++) g[0][0][i] = 1;
	if (!a[s[0]][1] || (abs(a[s[0]][1]) != abs(a[s[1]][0]) && abs(a[s[0]][1]) != abs(a[s[1]][1]))) swap(a[s[0]][0], a[s[0]][1]);
	for (int i = 1; i < t; i++)
		if (abs(a[s[i]][0]) != abs(a[s[i-1]][1]))
			swap(a[s[i]][0], a[s[i]][1]);
	for (int i = 1; i <= t; i++) {
		int x = s[i-1];
		for (int p = 0; p < 2; p++)
			for (int q = 0; q < 2; q++)
				for (int j = 0; j < 2; j++)
					g[i][(((a[x][0]<0)^p)|((a[x][1]<0)^q))^j][q] += g[i-1][j][p];
	}
	for (int i = 0; i < 2; i++)
		for (int j = l2; j <= r2; j++)
			c[i] += g[t][i][j];
}

inline void solve(int o) {
	if (s.size() == 1u) {
		int x = s[0];
		if (a[x].size() == 1u) return c[0] = c[1] = 1, void();
		if (abs(a[x][0]) != abs(a[x][1])) return c[0] = 1, c[1] = 3, void();
		if (a[x][0] == a[x][1]) return c[0] = c[1] = 1, void();
		return c[0] = 0, c[1] = 2, void();
	}
	int rt = 0;
	for (int x : s)
		if (d[x] == 1) rt = x;
	c[0] = c[1] = 0;
	if (rt) {
		for (int x : s) v[x] = 0;
		s.clear(), dfs(rt);
		int x = s[0], l1 = 0, r1 = 1, l2 = 0, r2 = 1;
		if (a[x].size() == 1u) r1 = 0, a[x].pb(0);
		x = s.back();
		if (a[x].size() == 1u) r2 = 0, a[x].pb(0);
		return dp(l1, r1, l2, r2);
	}
	dp(0, 0, 0, 0), dp(1, 1, 1, 1);
}

int main() {
	rd(n), rd(m);
	for (int i = 1, o, x; i <= n; i++) {
		rd(o);
		while (o--) rd(x), a[i].pb(x), b[abs(x)].pb(i);
	}
	for (int i = 1; i <= m; i++)
		if (b[i].size() == 2u) {
			int x = b[i][0], y = b[i][1];
			e[x].pb(y), e[y].pb(x), ++d[x], ++d[y];
		} else if (!b[i].size()) ans *= 2;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		if (!v[i]) {
			s.clear(), ++k, dfs(i), solve(k);
			for (int j = 0; j < 2; j++)
				f[k][j] = f[k-1][j] * c[0] + f[k-1][j^1] * c[1];
		}
	ans *= f[k][1];
	print(ans);
	return 0;
}
```

---

## 作者：justin_cao (赞：3)

发现每个变量最多出现$2$次，那么考虑若将有等式关系的两个点之间连一条边，那么这张图一定是一堆单独的环和链，因为每个点的度数至多为$2$。

那么首先考虑链，可以设$f[i][0/1][0/1]$表示当前考虑到了第$i$个点，前一个的权值为$0/1$，当前涉及的等式的异或和为$0/1$的方案数，转移的话直接枚举$2^3$种情况转移即可。

环的话考虑先枚举起点的取值，然后做一遍跟上面一样的$dp$，然后再算方案数即可，也就相当于做两遍。

那么把环和链取$0$和$1$的方案数求出来最后综合再做一个$dp$合并即可。

这样就可以做完了，复杂度$O(n)$。

但是需要注意的是一个式子只有一个点和一个式子里的两个变量是同一个点的情况，这种情况直接给每个点记一个$val[i][0/1]$表示这个点选$0$和选$1$的附加权值，$dp$的时候顺便记一下即可。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define mod 1000000007
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m;
int val[maxn][2];
struct P{
    int to,a,b,id;
};
vector<P>e[maxn];
int cnt,col[maxn],cnt_edge,deg[maxn],cntx;
int f[maxn][2][2],g[maxn][2];
void add(int &x,int y)
{
    x=(x+y>=mod)?x+y-mod:x+y;
}
void dfs_chain(int x,int st)
{
    ++cntx;col[x]=cnt;
    if(x==st)  f[cntx][0][val[x][0]]=f[cntx][1][val[x][1]]=1;
    for(int i=0;i<e[x].size();i++)
    {
        P p=e[x][i];
        if(col[p.to])  continue;
        for(int j=0;j<2;j++)
          for(int k=0;k<2;k++)
            for(int l=0;l<2;l++) 
              add(f[cntx+1][l][k^((j^p.a)|(l^p.b))^val[p.to][l]],f[cntx][j][k]);
        dfs_chain(p.to,st);
    }
}
void init()
{
    for(int i=1;i<=cntx;i++)
      for(int j=0;j<2;j++)
        for(int k=0;k<2;k++)  f[i][j][k]=0;
}
int book[2][maxn];
void dfs_cir(int x,int st,int c)
{
    ++cntx;col[x]=cnt;
    if(x==st)  f[cntx][c][val[x][c]]=1;
    for(int i=0;i<e[x].size();i++)
    {
        P p=e[x][i];
        if(book[c][p.id])  continue;
        book[c][p.id]=1;
        if(p.to==st)
        {
            for(int j=0;j<2;j++)
            {
                for(int k=0;k<2;k++)
                {
                    int op=(k^((j^p.a)|(c^p.b)));
                    add(g[cnt][op],f[cntx][j][k]);
                }
            }
        }
        else{
            for(int j=0;j<2;j++)
              for(int k=0;k<2;k++)
                for(int l=0;l<2;l++)
                  add(f[cntx+1][l][k^((j^p.a)|(l^p.b))^val[p.to][l]],f[cntx][j][k]); 
            dfs_cir(p.to,st,c);      
        }
    }
}
int h[maxn][2];
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        int k=read();
        if(k==1)
        {
            int x=read();
            if(x<0)  val[-x][0]^=1;
            else     val[x][1]^=1;
        }
        else{
            int x=read(),y=read();
            if(abs(x)==abs(y))
            {
                if(x<0&&y<0)  val[abs(x)][0]^=1;
                else if(x>0&&y>0)  val[abs(x)][1]^=1;
                else val[abs(x)][0]^=1,val[abs(x)][1]^=1;
                continue;
            }
            ++cnt_edge;
            e[abs(x)].push_back((P){abs(y),(x<0),(y<0),cnt_edge});
            e[abs(y)].push_back((P){abs(x),(y<0),(x<0),cnt_edge});
            deg[abs(x)]++;deg[abs(y)]++;
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(!col[i]&&deg[i]<=1)
        {
            ++cnt;cntx=0;
            dfs_chain(i,i);
            g[cnt][0]=(f[cntx][0][0]+f[cntx][1][0])%mod;
            g[cnt][1]=(f[cntx][0][1]+f[cntx][1][1])%mod;
            init();
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(!col[i])
        {
            ++cnt;cntx=0;
            dfs_cir(i,i,0);
            init();cntx=0;
            dfs_cir(i,i,1);
            init();
        }
    }
    h[0][0]=1;
    for(int i=1;i<=cnt;i++)
      for(int j=0;j<2;j++)
        for(int k=0;k<2;k++)  add(h[i][j],1ll*h[i-1][k]*g[i][j^k]%mod);
    cout<<h[cnt][1]<<endl;
    return 0;
}
```

---

## 作者：tzc_wk (赞：2)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/704/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF704C)

~~u1s1 感觉这种题被评到 *2900 是因为细节太繁琐了，而不是题目本身的难度，所以我切掉这种题根本不能说明什么……~~

首先题目中有一个非常喜闻乐见的条件那就是 $k_i\le 2$，因此我们考虑将每个布尔型变量看作一个点，对于出现在同一组的两个布尔型变量 $x,y$ 连边 $(x,y)$，那么显然得到的图一定是一堆环、一堆链以及一堆孤立点。

考虑对于每个环及每个链分别跑一遍 DP。对于链我们就设 $dp_{i,j,k}$ 表示考虑到链上第 $i$ 个点，第 $i$ 个点对应的布尔变量的取值为 $j$，当前所有布尔表达式的值异或起来为 $k$ 的方案数，转移就枚举上一个布尔变量的值即可。对于环我们就多开一维 $dp_{i,j,k,fst}$，$fst$ 表示环上第一个数为 $fst$，然后我们最后就强制从 $j=fst$ 的 $dp$ 计算答案即可。最后再套一个大背包，$f_{i,j}$ 表示考虑到前 $i$ 个连通块（环+链），这些连通块中所有表达式异或起来为 $j$ 的方案数，这个同样可以 $\mathcal O(1)$ 转移，总复杂度线性。

程序大致框架就这么多，不过此题细节实在是太太太多了，如果能 1A 就真的是神仙了，这里列出几个容易犯的错误：

- 对于 $x_i\lor\lnot x_i$ 的表达式，不论 $x_i$ 取什么该表达式的值都是 $1$，我们考虑随时维护一个 $goal$ 变量表示我们最终希望所有布尔表达式异或起来是多少，初始 $goal=1$，我们每遇到一个这样的表达式都令 $goal\leftarrow goal\oplus 1$，最终输出 $f_{\text{连通块个数},goal}$ instead of $f_{\text{连通块个数},1}$ 即可。
- 对于 $x_i\lor x_i$ 或者 $\lnot x_i\lor\lnot x_i$ 的表达式，显然其等效于一个孤立点。对于每个孤立点，我们也可以将其看作一个连通块，$f_{i,0}=f_{i,1}=f_{i-1,0}+f_{i-1,1}$，其中 $i$ 为该孤立点对应的连通块的编号。
- 对于单一变量的布尔表达式，我们记录一个 $msk_i$，取值范围 $\{-1,0,1\}$，$msk_i=-1$ 表示 $i$ 以 $\lnot x_i$ 的形式计入答案，$msk_i=1$ 表示 $i$ 以 $x_i$ 的形式计入答案，$msk_i=0$ 表示 $i$ 不计入答案。显然我们每遇到一个单一变量的布尔表达式都可以 $\mathcal O(1)$ 更新 $msk_i$。最后对于所有对于图上的孤立点，若 $msk_i=\pm 1$，则我们可将其视作一个连通块，$f_{i,0}=f_{i,1}=f_{i-1,0}+f_{i-1,1}$。否则你这个变量爱取 $1$ 就取 $1$，爱取 $0$ 就取 $0$，对异或值没有任何影响，答案乘 $2$。
- 对于每条链，若其端点以单一变量的形式计入答案，即 $msk_i\ne 0$，以 $msk_i=1$ 为例，那么我们就在 $dp$ 时候令 $dp$ 初值为 $dp_{0,x_i,x_i}=1$ instead of $dp_{0,x_i,0}=1$ 即可；$msk_i=-1$ 就令 $dp_{0,x_i,\lnot x_i}=1$。结尾处也同理，就在根据结尾处的 $dp$ 值转移 $f_{i,j}$ 时稍微改几个细节即可。

总而言之是一道阿巴细节题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
const int MOD=1e9+7;
void add(int &x,int y){x+=y;if(x>=MOD) x-=MOD;}
int n,m,msk[MAXN+5],deg[MAXN+5];bool vis[MAXN+5];
int sgn(int x){return (x>0)?0:1;}
struct edge{
	int u,v,su,sv,id;
	edge(int _u,int _v,int _su,int _sv,int _id):u(_u),v(_v),su(_su),sv(_sv),id(_id){}
};
vector<edge> g[MAXN+5];
int f[MAXN+5][2];
vector<pair<int,pii> > ch;
void dfs(int x,int pre,int rt){
	vis[x]=1;
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i].v,sx=g[x][i].su,sy=g[x][i].sv,id=g[x][i].id;
		if(id==pre) continue;ch.pb(mp(y,mp(sx,sy)));
		if(y^rt){dfs(y,id,rt);return;}
	}
}
int main(){
	scanf("%d%d",&m,&n);int goal=1;
	memset(msk,-1,sizeof(msk));int mul=1;
	f[0][0]=1;int grp_n=0;
	for(int i=1;i<=m;i++){
		int k;scanf("%d",&k);
		if(k==1){
			int x;scanf("%d",&x);
			if(!~msk[abs(x)]) msk[abs(x)]=sgn(x);
			else{
				if(msk[abs(x)]^sgn(x)) goal^=1;
				msk[abs(x)]=-1;
			}
		} else {
			int u,v;scanf("%d%d",&u,&v);
			if(u==v){
				vis[abs(u)]=1;grp_n++;
				f[grp_n][0]=f[grp_n][1]=(f[grp_n-1][0]+f[grp_n-1][1])%MOD;
			} else if(u+v==0) goal^=1,vis[abs(u)]=1,mul=2ll*mul%MOD;
			else if(u+v!=0){
				g[abs(u)].pb(edge(abs(u),abs(v),sgn(u),sgn(v),i));
				g[abs(v)].pb(edge(abs(v),abs(u),sgn(v),sgn(u),i));
				deg[abs(u)]++;deg[abs(v)]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!deg[i]){
			if(!~msk[i]&&!vis[i]) mul=2ll*mul%MOD;
			else if(!vis[i]){
				grp_n++;
				f[grp_n][0]=f[grp_n][1]=(f[grp_n-1][0]+f[grp_n-1][1])%MOD;
			}
		} else if(deg[i]==1&&!vis[i]){
			ch.clear();ch.pb(mp(i,mp(0,0)));dfs(i,0,0);vector<int> dp[2][2];
			for(int j=0;j<2;j++) for(int k=0;k<2;k++) dp[j][k].resize(ch.size());
			if(~msk[i]) for(int j=0;j<2;j++) dp[j][j^msk[i]][0]=1;
			else for(int j=0;j<2;j++) dp[j][0][0]=1;
			for(int j=1;j<ch.size();j++){
				int su=ch[j].se.fi,sv=ch[j].se.se;
				for(int o=0;o<2;o++) for(int p=0;p<2;p++) for(int q=0;q<2;q++){
					add(dp[o][((p^su)|(o^sv))^q][j],dp[p][q][j-1]);
				}
			} grp_n++;int lst=ch.back().fi;
			for(int o=0;o<2;o++) for(int p=0;p<2;p++){
				int res=o;if(~msk[lst]) res^=(p^msk[lst]);
				add(f[grp_n][0],1ll*f[grp_n-1][res]*dp[p][o].back()%MOD);
				add(f[grp_n][1],1ll*f[grp_n-1][res^1]*dp[p][o].back()%MOD);
			}
//			printf("Group %d:\n",grp_n);
//			for(int j=0;j<ch.size();j++) printf("%d %d %d\n",ch[j].fi,ch[j].se.fi,ch[j].se.se);
//			for(int j=0;j<ch.size();j++) printf("%d %d %d %d\n",dp[0][0][j],dp[0][1][j],dp[1][0][j],dp[1][1][j]);
//			printf("%d %d %d\n",i,f[grp_n][0],f[grp_n][1]);
		}
	}
	for(int i=1;i<=n;i++) if(deg[i]==2&&!vis[i]){
		ch.clear();ch.pb(mp(i,mp(0,0)));dfs(i,0,i);vector<int> dp[2][2][2];
		for(int j=0;j<2;j++) for(int k=0;k<2;k++) for(int l=0;l<2;l++) dp[j][k][l].resize(ch.size());
		for(int j=0;j<2;j++) dp[j][0][j][0]=1;
		for(int j=1;j<ch.size();j++){
			int su=ch[j].se.fi,sv=ch[j].se.se;
			for(int o=0;o<2;o++) for(int p=0;p<2;p++)
				for(int q=0;q<2;q++) for(int r=0;r<2;r++){
					add(dp[o][((p^su)|(o^sv))^q][r][j],dp[p][q][r][j-1]);
				}
		} grp_n++;int lst=ch.back().fi;
		for(int o=0;o<2;o++) for(int p=0;p<2;p++){
			add(f[grp_n][0],1ll*f[grp_n-1][o]*dp[p][o][p].back()%MOD);
			add(f[grp_n][1],1ll*f[grp_n-1][o^1]*dp[p][o][p].back()%MOD);
		}
//		printf("Group %d:\n",grp_n);
//		for(int j=0;j<ch.size();j++) printf("%d %d %d\n",ch[j].fi,ch[j].se.fi,ch[j].se.se);
//		printf("%d %d %d\n",i,f[grp_n][0],f[grp_n][1]);
	}
	printf("%d\n",1ll*f[grp_n][goal]*mul%MOD);
	return 0;
}
/*
8 10
1 -5
2 4 -6
2 -2 -6
2 -7 9
2 10 -1
2 3 -1
2 -8 9
2 5 8
*/
```



---

