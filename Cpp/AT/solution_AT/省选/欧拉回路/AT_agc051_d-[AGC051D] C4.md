# [AGC051D] C4

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc051/tasks/agc051_d

以下の無向グラフにおいて、$ S $ から $ S $ へのウォークであって辺 $ ST $, $ TU $, $ UV $, $ VS $ をそれぞれ $ a $, $ b $, $ c $, $ d $ 回通るもの (向きは不問) の数を $ 998,244,353 $ で割った余りを求めてください。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc051_d/648da6e8de7f6ac243febb92657c094616c7b1d5.png)

## 说明/提示

### 注記

$ S $ から $ S $ へのウォークとは、頂点の列 $ v_0\ =\ S,\ v_1,\ \ldots,\ v_k\ =\ S $ であって、各 $ i\ (0\ \leq\ i\ <\ k) $ について $ v_i $ と $ v_{i+1} $ を結ぶ辺があるものをいいます。 $ 2 $ つのウォークは、列として異なるときに異なるとみなされます。

### 制約

- $ 1\ \leq\ a,\ b,\ c,\ d\ \leq\ 500,000 $
- 入力中の全ての値は整数である。

### Sample Explanation 1

条件を満たすウォークは $ 10 $ 個あり、その一例は $ S $ $ \rightarrow $ $ T $ $ \rightarrow $ $ U $ $ \rightarrow $ $ V $ $ \rightarrow $ $ U $ $ \rightarrow $ $ T $ $ \rightarrow $ $ S $ $ \rightarrow $ $ V $ $ \rightarrow $ $ S $ です。

## 样例 #1

### 输入

```
2 2 2 2```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2 3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
470000 480000 490000 500000```

### 输出

```
712808431```

# 题解

## 作者：jun头吉吉 (赞：12)

## 题意
四个点的无向图，$1-2,2-3,3-4,4-1$ 之间分别有无向边。

现在给出每条边经过数量分别是 $A,B,C,D$，求从 $1$ 开始的回路数量。

$A,B,C,D\le 5\times10^5$

## 题解

欧拉回路计数嘛，度数不是偶数就可以输出 $0$ 了。

然后无向图我不会但是有向图我会啊。有 BEST 定理：

>对于有向图 $G=(V,E)$，图的欧拉回路数量 $ec(G)$ 为：
>$$ec(G)=t_s(G)\prod_{v\in V}(\deg_v-1)!$$
>其中 $t_s(G)$ 表示以任意一点为根的外向树数量。

因此如果我们变成有向边就能做了。

不妨设 $1\to 2,2\to 3,3\to 4,4\to 1$ 的次数分别为 $a,b,c,d$，那么 $2\to 1,3\to2,4\to3,1\to4$ 就分别为 $A-a,B-b,C-c,D-d$。因为出度和入度相等所以 $a$ 固定后 $b,c,d$ 也固定了，只需要枚举 $a$ 即可。

然后有向边，我们可以 $\mathcal O(1)$ 得到 $ec(G)$，但是还不能统计进答案。考虑两点

- BEST定理给出的是无起点欧拉回路条数，我们要求得是有起点，所以要乘上 $deg_1$ 表示从 $1$ 出来第一步走了哪条边
- 每种边实际上是不作区分的，所以要乘上 $1/(a!b!c!d!(A-a)!(B-b)!(C-c)!(D-d)!)$

然后累加进答案即可。复杂度 $\mathcal O(A)$。

## 代码
```cpp
const int N=1e6+10;
int A,B,C,D;mint fac[N],ifac[N],ans;
inline mint calc(mint _12,mint _23,mint _34,mint _14){
	mint _43=C-_34,_32=B-_23;
	return _12*_23*_34+_14*_12*_23+_14*_43*_12+_14*_43*_32;
}
signed main(){
	fac[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
	ifac[N-1]=1/fac[N-1];for(int i=N-1;i;i--)ifac[i-1]=ifac[i]*i;
	read(A,B,C,D);
	if((A&1)!=(B&1)||(B&1)!=(C&1)||(C&1)!=(D&1))return writeln(0),0;
	for(int a=0;a<=A;a++){
		int b=(B-A+2*a)/2,c=(C-B+2*b)/2,d=(D-C+2*c)/2;
		if(!(0<=b&&b<=B&&0<=c&&c<=C&&0<=d&&d<=D))continue;
		int deg1=a+D-d,deg2=b+A-a,deg3=c+B-b,deg4=d+C-c;
		ans+=calc(a,b,c,D-d)*fac[deg1-1]*fac[deg2-1]*fac[deg3-1]*fac[deg4-1]
			*ifac[a]*ifac[A-a]*ifac[b]*ifac[B-b]*ifac[c]*ifac[C-c]*ifac[d]*ifac[D-d]*deg1;
	}
	writeln(ans.x);
}
```

---

## 作者：UnyieldingTrilobite (赞：4)

（官方题解搬运工。）

首先注意到原图是一个二分图，从 S 走到 S 一定是偶数步。出于简化情况的考虑，我们不妨对相邻两步压缩起来考虑（类似于 SVU 这样，一次走两步）。这样一来，每一个压缩的起点和终点都只能是 S 或 U，而中间只能是 T 或 V。

容易发现，我们本质只有三大类：

1. 穿过 T

STU，UTS。

2. 穿过 V

SVU，UVS。

3. 原地返回

STS，SVS（这两个是 S 支类），UTU，UVU（这两个是 U 支类）。

让我们不妨枚举第一种情况出现的次数 $i$ 和第二种情况出现的次数 $j$，来看看它对答案的贡献有多少。

（这里我们记 $C(x,y)=\binom{x+y}{x}=\frac{(x+y)!}{x!y!}$，**注意这不是常见的组合数记号**。同理记 $C(x,y,z)$。对于不合法的情况，假定这个 $C$ 记号一律返回零。）

我们发现：第三种情况并不会改变当前位置，所以可以先行固定前两种操作的顺序，然后把第三种操作塞进去。我们又发现，第一种情况和第二种情况本质上位移是一样的，而且当两个第一/二类操作相邻时，它们的型号（指 STU 还是 UTS）是唯一的。我们还发现，第三种情况（的两大支类）的出现次数是可以通过 $i$ 和 $j$ 算出来的。

如此一来，我们便可以对于给定的这一组 $i$ 和 $j$ 计算出对于答案的贡献：

$$C(i,j)C(\frac{i+j}2,\frac{a-i}2,\frac{d-j}2)C(\frac{i+j}2-1,\frac{b-i}2,\frac{c-j}2)$$

对 $i,j$ 求和并简单展开亿下（官解这一步有锅，我这里修掉了）：

$$(\frac{a+d}2)!(\frac{b+c}2-1)!\sum_{i,j}\frac{(i+j)!}{(\frac{i+j}2)!(\frac{i+j}2-1)!}\times\frac1{i!(\frac{a-i}2)!(\frac{b-i}2)!}\times\frac1{j!(\frac{c-j}2)!(\frac{d-j}2)!}$$

那么就可以卷积处理了。注意如果 $a,b,c,d$ 不全同奇偶那么答案一定是零。

代码非常短。其中用到了 atcoder lib。

```cpp
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef modint998244353 mint;
constexpr int N = 1e6 + 9;
int a, b, c, d;
mint fac[N], ifc[N], ans;
void init_fac() {
  fac[0] = 1;
  for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i;
  ifc[N - 1] = fac[N - 1].inv();
  for (int i = N - 1; i; --i) ifc[i - 1] = ifc[i] * i;
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> a >> b >> c >> d;
  if (((a ^ b) | (b ^ c) | (c ^ d)) & 1) return cout << 0 << endl, 0;
  init_fac();
  int fn = min(a, b) + 1, gn = min(c, d) + 1;
  vector<mint> f(fn), g(gn);
  for (int i = (a & 1); i < fn; i += 2)
    f[i] = ifc[i] * ifc[(a - i) >> 1] * ifc[(b - i) >> 1];
  for (int i = (c & 1); i < gn; i += 2)
    g[i] = ifc[i] * ifc[(c - i) >> 1] * ifc[(d - i) >> 1];
  vector<mint> h = convolution(f, g);
  for (int i = 2; i < fn + gn - 1; i += 2)
    ans += fac[i] * ifc[i >> 1] * ifc[(i >> 1) - 1] * h[i];
  ans *= fac[(a + d) >> 1] * fac[((b + c) >> 1) - 1];
  return cout << ans.val() << endl, 0;
}
```

---

## 作者：ty_mxzhn (赞：2)

热知识：无向图欧拉回路计数是 NP 问题。

考虑将无向图转成有向图。枚举 $AB$ 这种边的正向个数，确定完这个以后图上的每一种边都知道自己各个方向的数量，图变成有向图。

使用 BEST 定理即可。但是还要做两点调整。

1. **因为 BEST 定理是无起点的**。为了消除无起点的分歧，答案需要乘上 $A$ 点的度数。和一般我们所想的不一样，这个消除分歧的意思是，在环上面选择一个和 $A$ 相连的边，它的可以确定方向，知道方向就知道了整个环的位置具体是在哪个 $A$，是往环的哪边走。 
2. 将选择边方案考虑进去，因为无向边不做区分。

如果一开始原图就没有欧拉回路记得输出 $0$。

提供一个 BEST 定理：

> $\displaystyle f(G)=t_{\mathrm{out}}(G)\prod_{i=1}^4 (d_{\mathrm{out}}(i) -1)$


其中 $d_{\mathrm{out}}(i)$ 是 $i$ 点的出度。由此定理可以知道一个欧拉图的 $t_{\mathrm{out}}(G,i)$ 是相等的。

$t_{\mathrm{out}}(G,i)$ 是以 $i$ 为根的外向生成树个数。可以使用矩阵树定理在 $O(n^3)$ 时间复杂度内解决。

---

## 作者：EuphoricStar (赞：2)

下文的点 $1, 2, 3, 4$ 对应原题面中的 $S, T, U, V$。

直接对无向图欧拉回路计数不太好做。考虑给边定向。枚举有 $i$ 条边是从 $1$ 到 $2$ 的。那么 $2 \to 1$ 有 $a - i$ 条边。由于这个图必须满足每个点的入度等于出度，设 $j$ 条 $2 \to 3$ 的边，$b - j$ 条 $3 \to 2$ 的边，那么我们有 $a - i + j = i + b - j$。解得 $j = i + \frac{b - a}{2}$。同理有 $k = j + \frac{c - b}{2}$ 条 $3 \to 4$ 的边，$l = k + \frac{d - c}{2}$ 条 $4 \to 1$ 的边。

这样我们就将题目的无向图转化成了有向图。在这个图上做欧拉回路计数。可以考虑 BEST 定理，有向欧拉图的本质不同欧拉回路数量（循环同构视为本质相同，每条边互相区分）为：

$$T \prod\limits_{i = 1}^n (out_i - 1)!$$

其中 $T$ 为图的外向生成树个数（注意到有向欧拉图以每个点为根的外向生成树个数相等），$out_i$ 为 $i$ 点的出度。

这题要求欧拉回路从 $1$ 出发和结束。每一条欧拉回路 $1$ 都出现了 $out_1$ 次，把循环同构的加上，所以答案乘上 $out_1$。注意这题每条同方向的边互不区分，所以答案乘上 $\frac{1}{i! (a - i)! j! (b - j)! k! (c - k)! l! (d - l)!}$ 即可。

时间复杂度 $O(a + b + c + d)$。

注意判一些无解的情况，比如 $i, j, k, l$ 不在范围内。

[code](https://atcoder.jp/contests/agc051/submissions/49326998)

---

## 作者：_HCl_ (赞：2)

非常好的一道矩阵树定理练习题。

# AGC051D C4 题解

**题意简述**

四个点连成一个环，现在从点 $S$ 出发，要求每条边恰好经过指定次数，询问这样的回路数。

**思路引导**

我们可以考虑将某一条边，拆成好几条边，重边的数量就是经过的次数。这样我们就转换成了求**从 $S$ 出发的 Euler 回路数**。

不难想到用 BEST 定理处理：

$$ec(G)=t^{root}(G)\prod_{v\in V}(deg_v-1)!$$

但是 BEST 定理只对于有向图适用，因此我们要把无向图转换为有向图去做。

对于 $a$ 条 $e_{ST}$，我们可以把它拆成 $x_a$ 条 $e_{S\rightarrow T}$ 和 $(a-x_a)$ 条 $e_{T\rightarrow S}$。

又由于 Euler 回路（入度等于出度）的性质，观察 $T$ 点，有：

$$x_a+b-x_b=a-x_a+x_b\Rightarrow x_b=x_a+\frac{b-a}{2}$$

同理也可以推出 $x_c$ 和 $x_d$。

对于 $t^{root}(G)$，我们可以 $\mathcal{O}(1)$ 求解。我们先列出它的出度 Laplace 矩阵：

$$\begin{aligned}L^{out}&=D^{out}-A\\&=\begin{bmatrix}x_a+d-x_d&0&0&0\\0&x_b+a-x_a&0&0\\0&0&x_c+b-x_b&0\\0&0&0&x_d+c-x_c\end{bmatrix}-\begin{bmatrix}0&x_a&0&d-x_d\\a-x_a&0&x_b&0\\0&b-x_b&0&x_c\\x_d&0&c-x_c&0\end{bmatrix}\\&=\begin{bmatrix}x_a+d-x_d&-x_a&0&x_d-d\\x_a-a&x_b+a-x_a&-x_b&0\\0&x_b-b&x_c+b-x_b&-x_c\\-x_d&0&x_c-c&x_d+c-x_c\end{bmatrix}\end{aligned}$$

然后我们假设以 $S$ 为根，将 Laplace 矩阵去掉第一行第一列的子矩阵求行列式：

$$\begin{aligned}t^{root}(G,S)&=\det \begin{bmatrix}x_b+a-x_a&-x_b&0\\x_b-b&x_c+b-x_b&-x_c\\0&x_c-c&x_d+c-x_c\end{bmatrix}\\&=(x_b+a-x_a)(x_c+b-x_b)(x_d+c-x_c)-(-x_b)(x_b-b)(x_d+c-x_c)-(-x_c)(x_c-c)(x_b+a-x_a)\\&=x_ax_bx_c+(d-x_d)x_ax_b+(d-x_d)(c-x_c)(b-x_b)+(d-x_d)(c-x_c)x_a\end{aligned}$$

还要注意的是，BEST 定理给出的 Euler 回路是无源的，而题目要求的回路是有源的，因此还需要乘上 $S$ 的出度 $deg_S$，以确定第一步走哪条边。另外，重边都是相同的，所以答案还需要再除以 $\prod_{e\in \{a,b,c,d \}} x_e!(e-x_e)!$。

最终答案就是：

$$\frac{deg_S\cdot ec(G)}{\prod_{e\in \{a,b,c,d \}} x_e!(e-x_e)!}$$

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,d;
const int MOD=998244353;
int fac[1000001],inv[1000001];
void init(){//预处理出阶乘和逆元
	fac[0]=fac[1]=inv[1]=inv[0]=1;
	for(int i=2;i<=600000;++i)inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(int i=2;i<=600000;++i)fac[i]=fac[i-1]*i%MOD,inv[i]=inv[i]*inv[i-1]%MOD;
}
int check(){//判断 Euler 回路是否存在
	if((a&1)!=(b&1))return 1;
	if((b&1)!=(c&1))return 1;
	if((c&1)!=(d&1))return 1;
	return 0;
}
int check2(int i,int j,int k){//判断有向边的分配是否合法
	if(i<0||i>b)return 1;
	if(j<0||j>c)return 1;
	if(k<0||k>d)return 1;
	return 0;
}
int t(int ST,int TU,int UV,int VS){//计算 t^{root}(G)
	int SV=d-VS,UT=b-TU,VU=c-UV;
	int tmp=ST*TU*UV%MOD + SV*ST*TU%MOD + SV*VU*UT%MOD + SV*VU*ST%MOD;
	return tmp%MOD;
}
signed main(){
	cin>>a>>b>>c>>d;
	init();
	if(check()){
		cout<<0;
		return 0;
	}
	int ans=0;
	for(int xa=0;xa<=a;++xa){
		int xb=xa+(b-a)/2,xc=xb+(c-b)/2,xd=xc+(d-c)/2;
		if(check2(xb,xc,xd))continue;
		int deg_s=d+xa-xd,deg_t=a+xb-xa,deg_u=b+xc-xb,deg_v=c+xd-xc;
		int tmp=(fac[deg_s-1]*fac[deg_t-1]%MOD)*(fac[deg_u-1]*fac[deg_v-1]%MOD)%MOD;
		int itmp1=(inv[xa]*inv[a-xa]%MOD)*(inv[xb]*inv[b-xb]%MOD)%MOD;
		int itmp2=(inv[xc]*inv[c-xc]%MOD)*(inv[xd]*inv[d-xd]%MOD)%MOD;
		int itmp=itmp1*itmp2%MOD;
		ans=(ans+t(xa,xb,xc,xd)*deg_s%MOD*tmp%MOD*itmp%MOD)%MOD;
	}
	cout<<ans;
}
```

---

## 作者：zifanwang (赞：1)

考虑确定每条边有多少条正向的和反向的，然后直接 BEST 定理求。

考虑存在欧拉回路的条件，每个点的入边个数需要和出边个数相等，那么只需要枚举 $(1,2)$ 的个数便可以确定其它每种边的条数，直接做即可。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 1000003
#define md 998244353
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int a,b,c,d,c1,c2,c3,c4,d1,d2,d3,d4;
ll ans,f[5][5],fac[mxn],ifac[mxn];
ll power(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
int solve(){
	return (f[1][1]*f[2][2]%md*f[3][3]-f[1][1]*f[2][3]%md*f[3][2]-f[1][2]*f[2][1]%md*f[3][3]+f[1][2]*f[2][3]%md*f[3][1]+f[1][3]*f[2][1]%md*f[3][2]-f[1][3]*f[2][2]%md*f[3][1])%md;
}
signed main(){
	cin>>a>>b>>c>>d;
	fac[0]=1;
	rep(i,1,1000000)fac[i]=fac[i-1]*i%md;
	ifac[1000000]=power(fac[1000000],md-2);
	drep(i,1000000,1)ifac[i-1]=ifac[i]*i%md;
	rep(i,0,a){
		c1=i,d1=a-i;
		if((d1-c1+b)&1)continue;
		d2=(d1-c1+b)>>1,c2=b-d2;
		if((d2-c2+c)&1)continue;
		d3=(d2-c2+c)>>1,c3=c-d3;
		if((d3-c3+d)&1)continue;
		d4=(d3-c3+d)>>1,c4=d-d4;
		if(c4+d1!=d4+c1)continue;
		if(c1<0||c1>a||c2<0||c2>b||c3<0||c3>c||c4<0||c4>d)continue;
		memset(f,0,sizeof(f));
		f[1][2]=-c2,f[2][1]=-d2;
		f[2][3]=-c3,f[3][2]=-d3;
		f[1][1]=c2+d1,f[2][2]=c3+d2,f[3][3]=c4+d3;
		ans=(ans+solve()*fac[c1+d4-1]%md*fac[c2+d1-1]%md*fac[c3+d2-1]%md*fac[c4+d3-1]%md
			*ifac[c1]%md*ifac[d1]%md*ifac[c2]%md*ifac[d2]%md*ifac[c3]%md*ifac[d3]%md*ifac[c4]%md*ifac[d4]%md*(c1+d4))%md;
	}
	cout<<(ans+md)%md;
	return 0;
}
```

---

## 作者：AsiraeM (赞：1)

把每条边拆成 $v_{i}$ 条边，相当于求从 $1$ 出发的欧拉回路数量。  

这个问题在有向图上可以使用 BEST 定理求解：  
$$ec(G)=t^{root}(G,k)\prod_{u \in V}(deg(u)-1)!$$
其中 $t^{root}(G,k)$ 是在图 $G$ 中以 $k$ 为根的所有根向树形图（即所有的边全部指向父亲）个数（可以证明对于欧拉图的任意两个结点 $k,k'$，有 $t^{root}(G,k)=t^{root}(G,k')$），  
$ec(G)$ 是图的欧拉回路数量，$deg(u)$ 是 $u$ 的度数。  

可以先给边定向，枚举有多少条边是从 $1$ 到 $2$ 的，  
根据欧拉图的性质，即每个结点入度等于出度，求出所有边的方向。  
图中只有四个点，直接枚举树的形态，$O(1)$ 算出 $t^{root}(G,k)$。  

因为 BEST 定理求出的其实是无起点的欧拉回路条数，而本题中要求从 $1$ 出发，所以要乘上起点的度数（从起点出来时走了哪条边）。  

最后因为每条边拆成的 $v_{i}$ 条边本质上是 $2$ 条边（正向与反向），需要去重，  
设这 $8$ 种边每种有 $v'_i$ 条，答案需要除以 $\prod (v'_i!)$。

一些小细节：  
首先要判断是不是欧拉图（如果不是则答案为 $0$）；  
其次要判断每个方向的边的数量是否小于 $0$ 或大于 $v_i$。  

代码：
```cpp
//Talk is cheap.Show me the code.
#include<bits/stdc++.h>
namespace xcy{
const int MAXN=500005;
typedef long long ll;
const ll MOD=998244353;
ll fac[MAXN+5],inv[MAXN+5],a,ra[2],b,rb[2],c,rc[2],d,rd[2],i,j,ans;

inline void fread(ll &X){X=0;char C=getchar();while(!isdigit(C))C=getchar();while(isdigit(C))X=(X<<1)+(X<<3)+(C^48),C=getchar();}
inline void fout(ll X){if(X<0)putchar('-'),X=-X;if(!X){putchar('0'),putchar(' ');return;}char C[25]{};int Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(' ');}

int mian()
{
	for(i=2,fac[1]=fac[0]=inv[1]=inv[0]=1;i<=MAXN;++i)inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(i=2;i<=MAXN;++i)fac[i]=i*fac[i-1]%MOD,inv[i]=inv[i]*inv[i-1]%MOD;
	fread(a),fread(b),fread(c),fread(d);
	if(((a+b)|(b+c)|(c+d)|(d+a))&1){puts("0");return 0;}
	for(ra[0]=0;ra[0]<=a;++ra[0])
	{
		ra[1]=a-ra[0];
		rb[0]=(b-a)/2+ra[0];rb[1]=b-rb[0];
		rc[0]=(c-b)/2+rb[0];rc[1]=c-rc[0];
		rd[0]=(d-c)/2+rc[0];rd[1]=d-rd[0];
		if(ra[0]<0||ra[1]<0||rb[0]<0||rb[1]<0||rc[0]<0||rc[1]<0||rd[0]<0||rd[1]<0)continue;
		ans=(ans+(ra[0]*rb[0]*rc[0]%MOD+ra[0]*rb[0]*rd[1]%MOD+ra[0]*rc[1]*rd[1]%MOD+rb[1]*rc[1]*rd[1]%MOD)%MOD
				*fac[ra[0]+rd[1]-1]%MOD*fac[rb[0]+ra[1]-1]%MOD*fac[rc[0]+rb[1]-1]%MOD*fac[rd[0]+rc[1]-1]%MOD*(ra[0]+rd[1])%MOD
				*inv[ra[0]]%MOD*inv[ra[1]]%MOD*inv[rb[0]]%MOD*inv[rb[1]]%MOD*inv[rc[0]]%MOD*inv[rc[1]]%MOD*inv[rd[0]]%MOD*inv[rd[1]]%MOD)%MOD; 
	}
	fout(ans);
    return 0;
}}
int main(){return xcy::mian();}

```


---

