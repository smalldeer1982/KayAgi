# [USACO21FEB] Counting Graphs P

## 题目描述

Bessie 有一个连通无向图 $G$。$G$ 有 $N$ 个编号为 $1\ldots N$ 的结点，以及 $M$ 条边（$1\le N\le 10^2, N-1\le M\le \frac{N^2+N}{2}$）。$G$ 有可能包含自环（一个结点连到自身的边），但不包含重边（连接同一对结点的多条边）。

令 $f_G(a,b)$ 为一个布尔函数，对于每一个 $1\le a\le N$ 和 $0\le b$，如果存在一条从结点 $1$ 到结点 $a$ 的路径恰好经过了 $b$ 条边，则函数值为真，否则为假。如果一条边被经过了多次，则这条边会被计算相应的次数。

Elsie 想要复制 Bessie。具体地说，她想要构造一个无向图 $G'$，使得对于所有的 $a$ 和 $b$，均有 $f_{G'}(a,b)=f_G(a,b)$。

你的工作是计算 Elsie 可以构造的图 $G'$ 的数量，对 $10^9+7$ 取模。与 $G$ 一样，$G'$ 可以包含自环而不能包含重边（这意味着对于 $N$ 个有标号结点共有 $2^{\frac{N^2+N}{2}}$ 个不同的图）。

每个输入包含 $T$（$1\le T\le \frac{10^5}{4}$）组独立的测试用例。保证所有测试用例中的 $N^2$ 之和不超过 $10^5$。

## 说明/提示

#### 样例 1 解释：

在第一个测试用例中，$G'$ 可以等于 $G$，或以下两个图之一：

```
5 4
1 2
1 4
3 4
3 5
```

```
5 5
1 2
2 3
1 4
3 4
3 5
```

#### 样例 2 解释：

有一些较大的测试用例。确保你的答案对 $10^9+7$ 取模。注意倒数第二个测试用例的答案为 $2^{45}\pmod{10^9+7}$。

#### 测试点性质：


 - 对于另外 $5\%$ 的数据，满足 $N\le 5$。
 - 对于另外 $10\%$ 的数据，满足 $M=N-1$。
 - 对于另外 $30\%$ 的数据，如果并非对于所有的 $b$ 均有 $f_G(x,b)=f_G(y,b)$，则存在 $b$ 使得 $f_G(x,b)$ 为真且 $f_G(y,b)$ 为假。
 - 对于另外 $45\%$ 的数据，没有额外限制。

供题：Benjamin Qi


## 样例 #1

### 输入

```
1

5 4
1 2
2 3
1 4
3 5```

### 输出

```
3```

## 样例 #2

### 输入

```
7

4 6
1 2
2 3
3 4
1 3
2 4
1 4

5 5
1 2
2 3
3 4
4 5
1 5

5 7
1 2
1 3
1 5
2 4
3 3
3 4
4 5

6 6
1 2
2 3
3 4
4 5
5 6
6 6

6 7
1 2
2 3
1 3
1 4
4 5
5 6
1 6

10 10
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10

22 28
1 2
2 3
3 4
4 5
5 6
6 7
1 7
1 8
3 9
8 10
10 11
10 12
10 13
10 14
11 15
12 16
13 17
14 18
9 15
9 16
9 17
9 18
15 19
19 20
15 20
16 21
21 22
16 22```

### 输出

```
45
35
11
1
15
371842544
256838540```

# 题解

## 作者：约瑟夫用脑玩 (赞：14)

部分借鉴了自己[P7417](https://www.luogu.com.cn/problem/P7417)的题解，相较于[_Enthalpy](https://www.luogu.com.cn/user/42156)的题解补充了每个转移每一步的解释。

首先特判二分图，不多赘述。

沿用[P7417](https://www.luogu.com.cn/problem/P7417)的定义，设一个点的奇最短路和偶最短路二元组为 $(x,y)$，且保证 $x<y$。

导致 $(x,y)$ 的方式仍然是：

1. 有另一个点奇偶最短路分别为 $(x-1,y-1)$，并连了一条边。
1. 有两个点分别为①$(x-1,y+1)$ 和②$(x+1,y-1)$，都连了一条边。注意当 $x+1=y$ 时，有 $(x+1,y-1)=(y-1,x+1)=(x,y)$。

解释：方式二中①的第一维保证较小最短路为 $x$，②第二维保证了较大最短路为 $y$，而他们的其他维由于与 $(x,y)$ 的点有直接连边故最大都只能 +1。

------------


先按照 $x+y$ 为第一层阶段进行 DP，那么按方式一满足点的最短路是容易的，只用从上一阶段连边即可。

又因为方式二需要同阶段前后连边，于是再按 $x$ 为第二层阶段依次考虑。

而每个点要么按方式一满足，要么按方式二，要么两种都有，显然我们需要考虑只按方式二满足最短路的点对状态的影响，因为涉及到前后**都必须**连边。

设 $f_{x,y,p}$ 表示当前 DP 到 $(x,y)$ 的二元组，并且有 $p$ 个点还需要下一个状态连边，仅按方式二来满足最短路的方案。

那么我们通过枚举只按方式一满足最短路的点的个数来转移，设有 $q$ 个这种点，二元组 $(x,y)$ 的点总共有 $s1$ 个，二元组 $(x-1,y-1)$ 有 $s2$ 个，那么转移为：

$f_{x,y,p}=\sum_{q=0}^{s1-p}\binom{s1-q}{p}(2^{s2}-1)^{s1-p}g_{x,y,q}$

解释：

- $\binom{s1-q}{p}$：选点的方案系数，这里表示从 $s1-q$ 个不是 只按方式一满足 的点中选出 $p$ 个点只按方式二转移。
- $(2^{s2}-1)^{s1-p}$：连边的方案系数，不是 只按方式二满足 的点都需要方式一满足，每个点与 $(x-1,y-1)$ 的点至少连一条边。
- $g_{x,y,q}$：辅助转移数组，表示有 $s1-q$ 个点都有 $(x-1,y+1)$ 连边而来的方案。

------------


接下来考虑转移 $g_{x,y,p}$，枚举上一次状态有多少个点需要当前状态回连边，设有 $q$ 个这种点，二元组 $(x,y)$ 的点总共有 $s1$ 个，二元组 $(x-1,y+1)$ 有 $s2$ 个，那么转移为：

$g_{x,y,p}=\binom{s1}{p}\sum_{q=0}^{s2}h_{s2,q,s1-p}f_{x-1,y+1,q}$

解释：

- $\binom{s1}{p}$：选点的方案系数，从 $s1$ 个点中钦定 $p$ 个。
- $h_{s2,q,s1-p}$：转移系数，表示在大小为 $s2$ 的集合和大小为 $s1-p$ 的集合之间连边，保证 $s2$ 中的 $q$ 个点和大小为 $s1-p$ 的集合度数至少为 $1$ 的方案。

------------


考虑处理出 $h_{i,j,k}$，可以使用容斥，钦定有 $p$ 个 $j$ 中的点没有出度：

$h_{i,j,k}=\sum_{p=0}^j(-1)^p\binom{j}{p}(2^{i-p}-1)^k$

解释：

- $\binom{j}{p}$：选点的方案系数，从 $j$ 个点中钦定 $p$ 个。
- $(2^{i-p}-1)^k$：连边的方案系数，$k$ 个点中的每个与 $i-p$ 个未被钦定的点至少连一条边。

------------


至此 DP 转移完毕，考虑统计答案，如果二元组恰为 $(x,y=x+1)$，则可以有点需要下一个状态连边，仅按方式二来满足最短路，这样的点可以以同类连边的方式消化掉，设二元组 $(x,x+1)$ 的点总共有 $s$ 个，贡献为：

$\sum_{i=0}^sT_{s,i}f_{x,x+1,i}$

解释：$T_{s,i}$：大小为 $s$ 的二元组集合中 $i$ 个点会通过同类连边消化掉的方案。

------------


预处理 $T_{i,j}$，可以使用容斥，钦定有 $k$ 个点度数为 $0$：

$T_{i,j}=\sum_{k=0}^j(-1)^k\binom{j}{k}2^{\frac{(i-k)(i-k+1)}{2}}$

解释：

- $(-1)^k\binom{j}{k}$：容斥系数和钦定选点的方案系数
- $2^{\frac{(i-k)(i-k+1)}{2}}$：除去钦定的 $k$ 个点随意连边的方案数。

------------

如果二元组不为 $(x,x+1\neq y)$，则不能有点需要下一个状态连边，贡献为 $f_{x,y,0}$。

把上述的公式拼起来就是一份[代码](https://www.luogu.com.cn/paste/5mrfthyi)了。

注意由于奇偶最短路最长可能出现 $2n$，涉及到二元组的数组及清空要开两倍。

Upd：修了公式里的小问题和语言表述，并补充了代码。

Upd：修了一下代码，将公式中的表述和代码中的变量整理统一了一下。

Upd：补充解释。

Upd：修改了之前不规范的地方。

---

## 作者：feecle6418 (赞：9)

怎么没有中文题解啊，写一篇好了

# [USACO21FEB] Counting Graphs P

## Declarations

定义 $d$ 为到某个点的最短路，$d'$ 为到某个点，奇偶性与 $d$ 不同的最短路。显然 $n$ 个数对 $(d,d')$ 确定了所有 $f_G(u,k)$ 的值。

用 $S(a,b)$ 表示 $d=a,d'=b$ 的点的集合。

将边分为三类：

- 一类，$(d-1,d'-1)\to (d,d')$
- 二类，$(d+1,d'-1)\to (d,d')$
- 三类，$(d,d+1)\to (d,d+1)$

注意到所有边一定属于三类之一。

设 $f(a,b,x)$ 表示已经 dp 到了 $(a,b)$，已经确定了所有 $a'+b'<a+b$ 或 $a'+b'=a+b$ 且 $a'<a$ 的点间连边情况，此时 $(a,b)$ 中还留下了 $x$ 个接口（即需要后面的往回连上的点数），的方案数。

设 $g(a,b,x)$ 定义同上，只是在 $g$ 上，我们目前只确定了二类边，并且 $S(a,b)$ 中恰有 $x$ 个点没有得到二类边的方案数。

## Calculating g()

$$
g(a,b,x)=\binom {|S(a,b)|}x \sum_{y=0}^{|S(a-1,b+1)|} f(a-1,b+1,y) F(|S(a-1,b+1)|,y,|S(a,b)|-x)
$$

其中 $F(U,x,y)$ 表示在一个大小为 $U$ 的集合和一个大小为 $y$ 的集合之间连边，使得前一个集合中 $1\sim x$，后一个集合中所有点的度数都至少为 $1$ 的方案数。可以容斥计算 $F$：
$$
F(U,x,y)=\sum_{i=0}^x(-1)^i\binom xi(2^{U-i}-1)^y
$$

## Calculating f()

$$
f(a,b,x)=\sum_{y=0}^{|S(a,b)|} \binom {|S(a,b)|-y}{x}g(a,b,y) (2^{|S(a-1,b-1)|}-1)^{|S(a,b)|-x}
$$

## Calculating the answer

我们只需求每一个连续段的结果之积。

若某层最后一个节点形如 $(d,d+1)$，最后留出 $k$ 个接口等价于要在这 $k$ 个点之间连边，使得每个点的度数都至少为 $1$。这个方案数可以容斥算（注意可以连自环）：
$$
G(k)=\sum_{i=0}^k (-1)^i\binom ki2^{\frac {(|S(d,d+1)|-i)(|S(d,d+1)|-i+1)}2}
$$
这时总答案等于
$$
\sum_{i=0}^{|S(d,d+1)|} f(d,d+1,i)G(i)
$$
否则最后一个节点就不能有接口，直接乘上 $f(a,b,0)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int dis[205],n,m,ans,f[205][205][105],g[205][205][105],C[205][205],pw2[205][205],pw[40005],sum[205];
vector<int> G[205];
struct Pair{
	int x,y;
}a[205];
int Power(int x,int y){
	int ret=1;
	while(y) {
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
const bool operator <(const Pair x,const Pair y){
	if(x.x+x.y!=y.x+y.y)return x.x+x.y<y.x+y.y;
	return x.x<y.x;
}
const bool operator ==(const Pair x,const Pair y){
	return !(x<y)&&!(y<x);
}
void upd(int &x,int y){
	x=(x+y)%mod;
}
int F(int U,int x,int y){
	int ret=0;
	for(int i=0,f=1;i<=x;i++,f=mod-f)upd(ret,1ll*f*C[x][i]%mod*pw2[U-i][y]%mod);
	return ret;
}
void Solve(){
	scanf("%d%d",&n,&m),ans=1;
	for(int i=0;i<=2*n;i++)dis[i]=0x3f3f3f3f,G[i].clear();
	for(int i=0;i<=2*n;i++)for(int j=0;j<=2*n;j++)for(int k=0;k<=n;k++)f[i][j][k]=g[i][j][k]=0;
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v+n),G[v+n].push_back(u),G[u+n].push_back(v),G[v].push_back(u+n);
	}
	queue<int> q;
	q.push(1),dis[1]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int y:G[x])if(dis[y]>dis[x]+1)dis[y]=dis[x]+1,q.push(y);
	}
	if(dis[1+n]==0x3f3f3f3f){
		for(int i=0;i<=n;i++)sum[i]=0;
		for(int i=1;i<=n;i++)sum[min(dis[i],dis[i+n])]++;
		for(int i=1;i<=n;i++)ans=1ll*ans*Power(Power(2,sum[i-1])-1,sum[i])%mod;
		return cout<<ans<<'\n',void();
	}
	for(int i=1;i<=n;i++)a[i]={min(dis[i],dis[i+n]),max(dis[i],dis[i+n])};
	sort(a+1,a+n+1);
	map<Pair,int> s;
	for(int i=1;i<=n;i++){
		int j=i-1;
		while(a[j+1]==a[i]&&j<n)j++;
		s[a[i]]=j-i+1;
		int p=a[i].x,q=a[i].y,S=j-i+1,T=s[{p-1,q+1}],O=s[{p-1,q-1}];
		if(!T)g[p][q][(i==1?0:S)]=1;
		else {
			for(int x=0;x<=S;x++)
				for(int y=0;y<=T;y++)
					upd(g[p][q][x],1ll*f[p-1][q+1][y]*F(T,y,S-x)%mod*C[S][x]%mod);
		}
		for(int x=0;x<=S;x++){
			for(int y=0;x+y<=S;y++)
				upd(f[p][q][x],1ll*C[S-y][x]*g[p][q][y]%mod*pw2[O][S-x]%mod);
		}
		if(j==n||a[j+1].x!=p+1||a[j+1].y!=q-1){
			if(p+1!=q)ans=1ll*ans*f[p][q][0]%mod;
			else {
				int tmp=0;
				for(int i=0;i<=S;i++)
					for(int j=0,o=1;j<=i;j++,o=mod-o)
						upd(tmp,1ll*o*C[i][j]%mod*pw[(S-j)*(S-j+1)/2]%mod*f[p][q][i]%mod);
				ans=1ll*ans*tmp%mod;
			}
		}
		i=j;
	}
	cout<<ans<<'\n';
}
int main(){
	for(int i=0;i<=200;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		for(int j=0;j<=200;j++)pw2[i][j]=Power(Power(2,i)-1,j);
	}
	for(int i=0;i<=40000;i++)pw[i]=Power(2,i);
	int t;
	scanf("%d",&t);
	while(t--)Solve();
	return 0;
}
```

---

## 作者：ღꦿ࿐ (赞：4)

无脑做法，解构主义。


首先路径不要求是简单的所以可以通过反复走一条边使得路径长度 $+2$。存在长度为 $x$ 的路径意味着一定存在长度为 $x+2$ 的路径，所以我们只关心一个点的奇最短路和偶最短路。

如果原图是一个二分图，那么每个点要么只存在奇路径要么只存在偶路径，所以只关心最短路。按照 $dis_i$ 分层后，每个点连接到上一层即可，答案为 $n-1$。

接下来只考虑原图不是二分图的情况：令到该点的最短路长度为 $x_i$，与最短路径奇偶不同的最短路长度为 $y_i$，我们需要使得新图所有 $(x_i,y_i)$ 和原图相同。

首先有一条边连接的 $(x_u,y_u),(x_v,y_v)$ 一定有 $|x_u-x_v|\leq 1 ,|y_u-y_v| \leq 1$，否则可以用较小者去更新较大者。


所以一个点  $(x,y)$ 只可能和 $(x\pm 1,y\pm 1)$ 连边（当然 $x=y-1$ 时 $(x+1,y-1)$ 为 $(x,y)$ 自己）。


考察一组 $(x,y)$ 的由来，由最短路的构成，一定满足以下两种情况之一：

- 从 $(x-1,y-1)$ 转移来。 
- 从 $(x-1,y+1)$ 得到 $x$，从 $(x+1,y-1)$ 得到 $y$（当 $x=y-1$ 时 $(x+1,y-1)$ 为 $(x,y)$ 自己）。

$(x+1,y+1)$ 可连可不连（对于这个点来说）。


特殊情况是 $x=0$ 即 $1$ 号点不需要向  $(x-1,y+1)$ 连边。

然后接下来的思路很妙：考虑前面二分图按照 $dis$ 分层，而现在难以按照 $dis$ 分层了，分层的目的是为了将原图分成若干个相对较为独立的部分，现在考虑按照  $x+y$ 分层，于是现在只需要考虑每层向上一层连当边和向这一层的左右连的边。


称 $(x-1,y-1)$ 为 $(x,y)$ 的“上面”，$(x-1,y+1)$ 为“左边”，$(x+1,y-1)$ 为“右边”，每个点要么连上面，要么同时连左右（右可能是自环）。

接下来考虑一层一层做。

考虑每层的样子一定形如有若干段，如果不是末尾可以连接自环的段的话一定两个端点都可以向上连。如果末尾可以连接自环那么末尾可能不能向上。（因为这些 $(x,y)$ 是由原图求出来的，所以一定存在一种合法的构造，不会存在一个点上面左右都不能连接），如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/naebrbl9.png)

考虑处理每层的每段。

这个限制每个点连接到父亲或左和右侧，就不太好按过程处理，考虑按结果处理：

最终每坨点 $a_i$ 中有 $b_i$ 个没有连接到了上面，我们要求一定连接到了左右，其它 $a_i-b_i$ 个点连接到了上面（连接到的方案数为 $2^{c_i}-1$，其中 $c_i$ 表示上面那坨的点数，这些点不要求连接到左右。

则这段的方案数为（显然要求 $b_1=0$，因为它们无法向左连）：

$$
\sum_{b_i\leq a_i,\forall c_i=0,b_i=a_i} \prod_{i=1} ^n\big((2^{c_i}-1)^{a_i-b_i}\binom {a_i} {b_i}\big)\times\prod_{i=1}^{n-1} f(a_i,b_i,a_{i+1},b_{i+1})
$$

如果这个段末尾的这坨点为 $(x,x+1)$ 即可以内部连边的点，那么我们不要求 $b_n=0$，否则我们要求 $b_n=0$。

其中 $f(n,x,m,y)$ 表示对两坨点连边的方案数，其中第一坨点有 $n$ 个，有 $x$ 个必须连边，第二坨点有 $m$ 个，有 $y$ 个必须连边的方案数。

$f$ 的计算是简单容斥：枚举两边分别有几个不合法。

$$

f(n,m,x,y)=\sum_{i=0}^x\sum_{j=0}^y \binom x i \binom y j 2^{(n-i)(m-j)}\times (-1)^{i+j}

$$ 

可以直接 $O(xy)$ 计算，简单粗暴。

上面那个式子的项相对独立，最多只有相邻两项的相关量。所以可以直接 dp 出来： $dp_{i,j}$ 表示目前处理到了 $1$ 到 $i$，且 $b_i=j$ 的方案数，转移很简单，枚举 $dp_{i-1,v}$ 转移过来并乘上 $f(cnt_{i-1},v,cnt_i,j)$ 即可了。

特殊的是当最右边的点可以内部连边的时候我们需要额外乘上最右边连自环的方案数，假设 $b_n=x$，（即我们有 $x$ 个点必须连边，其它无所谓）需要乘上的额外方案数为 $g(x)$，其中。

这个也是容斥算：枚举钦定几个点不连边。

$$
g(x) = \sum_{i=0}^{cnt}(-1)^{i}\binom {cnt} i \times 2^{\frac{(cnt-i)(cnt-i+1)}{2}}
$$

这段的答案就是 $\sum g(x)\times dp_{n,x}$。所有段互不影响，答案求积。

直接做复杂度 $O(n^4)$ 可以通过。

---

优化：

其实 $f$ 的计算可以被优化：

$$
\begin{aligned}
&=\sum_{i=0}^x\sum_{j=0}^y \binom x i \binom y j 2^{(n-i)(m-j)}\times (-1)^{i+j}\\
&=\sum_{i=0}^x(-1)^i\binom x i 2^{(n-i)m}\sum_{j=0}^{y}\binom y j (-2^{-(n-i)})^{j} 1^{y-j}\\
&=\sum_{i=0}^x(-1)^i\binom x i 2^{(n-i)m}(-2^{-(n-i)}+1)^{y}
\end{aligned} 
$$

就可以 $O(n^3)$ 了。

---

继续优化：

考虑每次确定状态之后再算 $f$ 很没必要（先定义再容斥），不如直接边 dp 边容斥。考虑容斥非法点的数量，每个非法点只能连左右中的一者不能连父亲，每加入一个非法点带来 $-1$ 的系数。


令 $dp_{i,j}$ 表示第 $i$ 坨点，有 $j$ 个点可以向后连边的容斥系数之和，考虑 $dp_{i-1,c}$ 向 $dp_{i,j}$ 转移 的系数，$cnt-j$ 个点被钦定为不合法，不能向右连边，且必须向左连边（这样它们才不能向右连边）。

然后考虑可以向右连边的 $j$ 个点，就是枚举 $t$ 个钦定不合法的点且没有向左边连边，没有被钦定的点可以向左边任意连边。如下：

$$
\begin{aligned}
&\binom{cnt} j\Big((-1)(2^{c}-1)\Big)^{cnt-j}\sum_{t=0}^{j}\binom {j}{t}\times (-1)^{t}\times(2^{c+v})^{j-t} \\
=&\binom{cnt} j(1-2^c)^{cnt-j}(2^{c+v}-1)^{j}

\end{aligned}
$$

时间复杂度 $O(n^2)$。






---

## 作者：Nasaepa (赞：2)

注意到对于 $\forall a,b$ 当 $f_G(a,b)$ 成立时，$f_G(a,b+2)$ 一定成立。且 $b \bmod 2 = (b+2) \bmod 2$，因此本题和奇偶有关。

我们只需要关心每个点的奇偶最短路就行了。先用 bfs 跑出每个点的奇偶最短路，对于点 $i$，设 $x_i$ 为其奇偶最短路中较小的一条，$y_i$ 为其中较大的一条。显然要么所有点都没有 $y_i$，要么所有点都有 $y_i$。没有 $y_i$ 的情况为二分图，此时需要特判。

在二分图中，设距离为 $x$ 的点共有 $num_x$ 个，则每个距离为 $x$ 的点都可以和 $[1,num_{x-1}]$ 个距离为 $x-1$ 的点连边，则答案为：

$$
\prod_{i=1}^{n}(2^{num_{i-1}}-1)^{num_i}
$$

好了，该考虑一般图了。对于 $(x,y)$，我们需要保证一个点至少有一条连向左边的边和一条连向上面的边，连接这种边的过程定义为**维护点**，邻接的两个点横纵坐标的绝对差不能超过 $1$，有如下连边方案：

1. 将边连接到 $(x-1,y-1)$ 即左上角。称为 1 类边。
2. 将边连接到 $(x-1,y+1)$ 和 $(x+1,y-1)$ 即左下角和右上角。称为 2 类边。
3. 当 $x + 1 = y$ 时可以通过内部点自行连边构造合法方案。称为 3 类边。

定义 $f_{x,y,p}$ 为 $(x,y)$ 位置有 $p$ 个点仅通过 2 类边被维护，并定义 $g_{x,y,p}$ 为 $(x,y)$ 位置前 $s_1 - p$ 个点可以从右上角的点使得其 $x$ 可以被维护的方案数，$s_1$ 为 $(x,y)$ 位置点的数量，$s_2$ 为 $(x-1,y-1)$ 位置点的数量。转移方程显然，为：

$$
f_{x,y,p} = \sum_{q=0}^{s1-p} \binom{s_1}{q}\binom{s_1 - q}{p}(2^{s_2-1}-1)^{s_1-p}g_{x,y,q}
$$

对 $f$ 数组的转移方程进行解释：

* 枚举有 $q$ 个点只能通过 1 类边维护，则有 $s_1-p$ 个点需要通过 1 类边维护，有 $s_1-q$ 个点需要通过 2 类边维护。
* $\binom{s_1}{q}\binom{s_1 - q}{p}$： 从 $s_1$ 个点中选择 $q$ 个点，选完再选 $p$ 个点。
* $(2^{s_2}-1)^{s_1-p}$：$s_1-p$ 个点每个点都可以选择左上角的 $[1,s_2]$ 个点连边。

此时需要考虑 $g$ 数组的转移。设置 $s_3$ 为右上角点的数量，$h_{i,j,k}$ 为一个大小为 $i$ 的集合和一个大小为 $k$ 的集合连无向边使大小为 $i$ 的集合的**前** $j$ **个元素**和大小为 $k$ 的集合的**所有元素**都有度的方案数。显然：

$$
g_{x,y,p} = \sum_{q=0}^{s_3}h_{s_3,q,s_1-p}f_{x-1,y+1,q} \\
h_{i,j,k} = \sum_{s = 0}^{j}(-1)^{s}\binom{j}{s}(2^{i-s}-1)^k
$$

注意需要特判 $s_3$ 为 $0$ 的情况，当为 $1$ 号点时，其它值均为 $0$，$g_{x,y,0} = 1$ 否则 $g_{x,y,s_1} = 1$。

对 $h$ 数组的算式进行解释：

* $s$ 表示前 $j$ 个元素至少有 $s$ 个点的度数为 $0$。
* $(-1)^{s}\binom{j}{s}$：容斥系数。
* $(2^{i-s}-1)^k$：集合中至少 $s$ 个元素度数为 $0$ 时连边的方案数。

此时还要考虑计算答案。考虑从每一条连续可以互相维护的点组成的线中 $x$ 最大的点进行转移，这些点称为**转移点**。转移点需要特判 $x+1$ 是否为 $y$。如果否，则对答案的贡献为 $f_{x,y,0}$，如果是，则贡献如下：

$$
\sum_{j = 0}^{s_1}t_{s_1,j}f_{x,y,j}
$$

其中 $t_{i,j}$ 表示在 $i$ 个点的集合中相互连边，保证前 $j$ 个点的度数不为 $0$ 的方案数。容斥一下就行了，值如下：

$$
t_{i,j} = \sum_{k=0}^{j}(-1)^k\binom{j}{k}2^{\frac{(i-k)(i-k+1)}{2}}
$$

对 $t$ 数组的算式进行解释：

* $k$ 表示有至少 $k$ 个度数为 $0$ 的点。
* $(-1)^k\binom{j}{k}$：容斥系数。
* $2^{\frac{(i-k)(i-k+1)}{2}}$：表示图中最多有 $\frac{(i-k)(i-k+1)}{2}$ 条边，连边方案数为 $2^{\frac{(i-k)(i-k+1)}{2}}$。

预处理 $h$ 数组和 $t$ 数组，把上述过程跑一边，最后把所有贡献乘起来就是可以输出答案了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
#define N 110
#define P 210
#define M 40010
const ll mod = 1000000007;
ll c[P][P];
// int s[P][P];// 每个位置的数量
ll pt[40010];
int T,n,m,u,dn,v,x,y;
ll ans;
int num[N];
namespace graph{
    int head[N],nxt[M],to[M];
    int cnt_edge;
    inline void connect_head(const int &x,const int &y){
        ++cnt_edge;
        nxt[cnt_edge] = head[x];
        to[cnt_edge] = y;
        head[x] = cnt_edge;
    }
}
using namespace graph;
pii vn[N];
inline bool cmp(const pii &n1,const pii &n2){
    if(n1.first + n1.second != n2.first + n2.second)return n1.first + n1.second < n2.first + n2.second;
    return n1.first < n2.first;
}
ll qp[N][N];
int dis[2][N];// 最短路
ll t[N][N];
ll f[P][P][N];
ll h[N][N][N];
ll g[P][P][N];
struct node{int x,p;node(const int &x_ = 0,const int &p_ = 0){x = x_,p = p_;}}q[N<<1],*front,*tail;
// 奇数偶数最短路
inline void bfs(){
    front = tail = q;
    *(tail++) = node(1,0);
    dis[0][1] = 0;
    int x,p;
    while(front != tail){
        x = front->x,p = front->p,++front;
        for(int edg = head[x];edg;edg = nxt[edg]){
            const int &v = to[edg];
            if(dis[!p][v] != INF)continue;
            dis[!p][v] = dis[p][x] + 1;
            *(tail++) = node(v,!p);
        }
    }
}

// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    // 预处理出数组
    c[0][0] = 1;
    for(int i = 1;i <= 100;++i){
        c[i][0] = 1;
        for(int j = 1;j <= i;++j){
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
        }
    }
    // pt[i] 表示 2^i
    pt[0] = 1;for(int i = 1;i <= 40000;++i)pt[i] = (pt[i-1]<<1)%mod;
    ll bn;
    for(int i = 0;i <= 100;++i){
        for(int j = 0;j <= i;++j){
            bn = 1;
            for(int k = 0;k <= j;++k){
                t[i][j] = (t[i][j] + (bn*c[j][k]+mod) % mod * pt[(i-k)*(i-k+1)>>1]) % mod;
                bn = -bn;
            }
        }
    }
    // 预处理 qp 数组用来优化，qp[i][j] = (2^i - 1) ^ j
    for(int i = 0;i <= 100;++i){
        qp[i][0] = 1;
        for(int j = 1;j <= 100;++j){
            qp[i][j] = (qp[i][j-1] * (pt[i]-1)) % mod;
        }
    }
    ll tmp = 0;
    for(int i = 0;i <= 100;++i){
        for(int j = 0;j <= i;++j){
            for(int k = 0;k <= 100;++k){
                tmp = 0,bn = 1;
                for(int s = 0;s <= j;++s){
                    tmp = (tmp + (bn*c[j][s]+mod)%mod*qp[i-s][k])%mod;
                    bn = -bn;
                }
                h[i][j][k] = tmp;
            }
        }
    }
    cin >> T;
    while(T--){
        cin >> n >> m;
        dn = (n<<1);
        // 清空图
        memset(head,0,(n<<2)+20),cnt_edge = 0;
        while(m--){
            cin >> u >> v;
            connect_head(u,v),connect_head(v,u);
        }
        // 维护奇数偶数最短路
        memset(dis[0],0x3f,(n<<2)+20),memset(dis[1],0x3f,(n<<2)+20);
        bfs();
        bool flag = 0;
        for(int i = 1;i <= n;++i){
            if(dis[0][i] > dis[1][i])swap(dis[0][i],dis[1][i]);
            vn[i] = {dis[0][i],dis[1][i]};
            if(dis[1][i] == INF)flag = 1;
        }
        // 处理二分图
        if(flag){
            memset(num,0,(n<<2)+20),ans = 1;
            for(int i = 1;i <= n;++i)++num[dis[0][i]];// 想办法建立图
            for(int i = 1;i <= n;++i)ans = ans * qp[num[i-1]][num[i]] % mod;
            cout << ans << '\n';
            continue;
        }
        map<pii,int> s;
        // 每个位置都有奇偶最短路，按照斜线一条一条处理
        sort(vn+1,vn+n+1,cmp);
        // 重置数组
        for(int i = 0;i <= dn;++i)for(int j = 0;j <= dn;++j){
            for(int k = 0;k <= n;++k){
                f[i][j][k] = g[i][j][k] = 0;
            }
        }
        ans = 1;
        int r,s1,s2,s3;
        for(int i = 1;i <= n;i = r){
            x = vn[i].first,y = vn[i].second;
            r = i,s1 = 0;
            while(r <= n && vn[r] == vn[i])++r,++s1;
            s[make_pair(x,y)] = s1;
            // 取不到就返回 0
            s2 = s[make_pair(x-1,y-1)];
            s3 = s[make_pair(x-1,y+1)];

            // 处理 g 数组
            if(!s3)g[x][y][i==1?0:s1] = 1;
            else{
                for(int p = 0;p <= s1;++p){
                    tmp = 0;
                    for(int q = 0;q <= s3;++q)tmp = (tmp + h[s3][q][s1-p]*f[x-1][y+1][q]) % mod;
                    g[x][y][p] = tmp;
                }
            }
            // 处理 f 数组
            for(int p = 0;p <= s1;++p){
                tmp = 0;
                for(int q = 0;q <= s1 - p;++q){
                    tmp += (c[s1-q][p] * c[s1][q] % mod)*qp[s2][s1-p] % mod*g[x][y][q];tmp %= mod;
                }
                f[x][y][p] = tmp;
            }
            // 维护 ans
            if(vn[r].second == y - 1 && r <= n && vn[r].first == x+1)continue;
            if(x + 1 == y){
                tmp = 0;
                for(int j = 0;j <= s1;++j)tmp = (tmp + t[s1][j] * f[x][y][j]) % mod;
                ans = ans * tmp % mod;
                continue;
            }
            ans = (ans * f[x][y][0]) % mod;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：nullqtr_pwp (赞：1)

由于 $f_G(a,b)$ 可以走重边，所以我们只关心奇最短路以及偶最短路。

判掉一下每个点只有奇数路径或偶数路径，即二分图，可以直接最短路树，在两题都需要特判掉。

本题的重点在于确认 $G'$ 的结构。考虑 $(x_i,y_i)$ 为不同奇偶的最短路数对，要求 $x_i<y_i$。对于原图的 $(x_i,y_i)$，将每个点拆成两个奇偶性的点之后跑 BFS 就可以 $O(m)$ 求。

注意到相邻边的 $x,y$ 都的差值都 $\leq 1$，否则可以更新掉。

考虑能得出这样的图的连边形态：

- $(x_i,y_i)$ 与 $(x_i-1,y_i-1)$ 相连。
- $(x_i,y_i)$ 与 $(x_i-1,y_i+1)$，$(x_i+1,y_i-1)$ 相连。
- 注意到 $x_i+1=y_i$ 的点可以直接连 $(y_i,y_i-1)=(x_i,y_i)$ 以及 $(x_i-1,x_i)$。

考虑：
- 连 $(x-1,y-1)$ 为向上。
- 连 $(x-1,y+1)$ 为向前。
- 连 $(x+1,y-1)$ 为向后。

那么一个点，要么有向上的，要么同时存在向前向后的。

同样考虑按照 $(x+y,x)$ 分层，考虑 dp。

我们发现往 $x+y-2$ 的点连的限制很自由，但是同一层的连通性要求很强，所以要在 $(x,y)$ 这种链做死一点的 dp。

令 $f_{x,y,p}$ 表示考虑到点对 $(x,y)$，有 $p$ 个点向后连边的合法方案数。且这 $p$ 个点 不能 向上连的方案数（也就是说只能通过连前后来满足的有 $p$ 个点）

考虑有 $cnt$ 个 $(x,y)$。

枚举 $0\leq q\leq cnt-p$ 个点没有同时往前后连，只能往上。考虑往前的 $(x-1,y-1)$ 有 $k$ 个。有以下贡献：

$$\sum_{q=0}^{cnt-p}\begin{pmatrix}
 cnt-p\\
q
\end{pmatrix} (2^k-1)^{cnt-p}g_{x,y,q}$$

其中 $g_{x,y,q}$ 表示 $(x,y)$ 的点有 $cnt-q$ 个点往前驱状态 $(x-1,y+1)$ 连边能连上的状态。

令 $k$ 为 $(x-1,y+1)$ 的数量。

考虑怎么求 $g_{x,y,p}$。枚举 $q$ 个 $(x-1,y+1)$ 的点到 $(x,y)$ 有边，那么有以下贡献：

$$\begin{pmatrix}
 cnt\\
p
\end{pmatrix} \sum_{q=0}^{k}h_{k,q,p}f_{x-1,y+1,q}$$

令 $h_{i,j,k}$ 表示二分图连边方案数，满足：$|L|=i,|R|=k$，并且 $L$ 中确定的 $j$ 个点存在连边，$R$ 中所有点都有连边的方案数。

可以使用连通图计数容斥的技巧。钦定 $L$ 的 $p$ 个点没有连边。考虑贡献系数：

$$\sum_{p=0}^{j}\begin{pmatrix}
 j\\
p
\end{pmatrix}(-1)^{p}(2^{i-p}-1)^k$$

$h$ 可以 $O(n^4)$ 预处理。

这样你就可以在正确的时间复杂度处理出 $f_{x,y,i}$。

考虑统计答案，如果将可能连边的连边，形成链，每一层就是若干条链，考虑在链尾计数保证不重不漏：

也就是考虑 不存在后继 $(x+1,y-1)$ 的所有点，进行统计。

注意到 $x+1=y$ 时可以互相消作为向后连的点。

- 不满足 $x+1=y$ 时考虑直接乘上 $f_{x,y,0}$。

否则，考虑向后连的就是互相连，考虑有 $p$ 个点，那么这个等价于不存在孤立点，随便容斥下就行了。

总时间复杂度 $O(n^4)$。

---

