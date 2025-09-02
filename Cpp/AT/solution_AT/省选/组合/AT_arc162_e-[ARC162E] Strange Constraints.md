# [ARC162E] Strange Constraints

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc162/tasks/arc162_e

$ 1 $ 以上 $ N $ 以下の整数からなる長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。

$ 1 $ 以上 $ N $ 以下の整数からなる長さ $ N $ の数列 $ B=(B_1,B_2,\ldots,B_N) $ のうち、全ての $ i=1,2,\ldots,N $ に対して以下の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください。

- $ B $ の中に含まれる $ i $ の個数は $ A_i $ 個以下
- $ B $ の中に含まれる $ B_i $ の個数は $ A_i $ 個以下

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ A_i\ \leq\ N $
- 入力される数値は全て整数
 
### Sample Explanation 1

条件を満たす数列は以下の $ 10 $ 個です。 - $ (1,2,2) $ - $ (1,2,3) $ - $ (1,3,2) $ - $ (1,3,3) $ - $ (2,1,3) $ - $ (2,3,1) $ - $ (2,3,3) $ - $ (3,1,2) $ - $ (3,2,1) $ - $ (3,2,2) $

### Sample Explanation 2

条件を満たす数列は、$ 1 $ 以上 $ 4 $ 以下の整数からなる長さ $ 4 $ の数列全てで、その個数は $ 4^4=256 $ 個です。

### Sample Explanation 3

条件を満たす数列は、$ (1,2,3,4,5) $ を並び替えて得られる数列全てで、その個数は $ 5!=120 $ 個です。

### Sample Explanation 4

個数を $ 998244353 $ で割ったあまりを出力してください。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
10```

## 样例 #2

### 输入

```
4
4 4 4 4```

### 输出

```
256```

## 样例 #3

### 输入

```
5
1 1 1 1 1```

### 输出

```
120```

## 样例 #4

### 输入

```
14
6 5 14 3 6 7 3 11 11 2 3 7 8 10```

### 输出

```
628377683```

# 题解

## 作者：EuphoricStar (赞：10)

完全没有思路。但是其实不难的。

设 $d_i$ 为 $i$ 在 $B$ 中的出现次数，题目要求：

- $\forall i \in [1, n], d_i \le A_i$；
- 对于位置 $i$，$d_j \le A_i$ 的数 $j$ 可以被放到 $B_i$。

考虑按照 $d_i$ 从大到小 dp。设 $f_{i, j, k}$ 为，考虑到出现次数 $\ge i$ 的数，这些数一共有 $j$ 个，总共出现了 $k$ 次。

设 $C_i = \sum\limits_{j = 1}^n [A_j \ge i]$。$f_{i + 1} \to f_i$ 时，考虑枚举 $x$ 个数出现了 $i$ 次，那么这 $x$ 个数有 $\binom{C_i - j}{x}$ 种方案被确定。要把它们填进 $B$ 中，有 $\frac{(C_i - k)!}{(\prod\limits_{y = 1}^x i!) \times (C_i - k - ix)}$ 种方案（其实是一个多重组合数）。那么转移式子就是：

$$f_{i, j + x, k + ix} \gets f_{i + 1, j, k} \times \binom{C_i - j}{x} \times \frac{(C_i - k)!}{(\prod\limits_{y = 1}^x i!) \times (C_i - k - ix)!}$$

注意到 $j$ 和 $x$ 的上界最大是 $\left\lfloor\frac{n}{i}\right\rfloor$ 的，所以时间复杂度其实是 $O(n^3)$。

[code](https://atcoder.jp/contests/arc162/submissions/42774235)

---

## 作者：Demeanor_Roy (赞：10)

- 人生第一次独立写出 at 难度 $2700$ 以上的题，这必须记录一下。

------------

首先不难发现第一个限制是好解决的，麻烦的是第二个限制，它使我们无法以一个较好的顺序去考虑 $B$ 的形成，自然也无法计数。

套路地，我们考虑根据值域填数。但你发现这样直接填，无论是从大到小还是从小到大，都依旧无法 dp，分析其根本原因，是因为我们无法确定当前有多少个位置是可填的。

同样套路地，不妨考虑按限制从严格到宽松考虑。发现在本题中，就是按每个数实际在 $B$ 序列中出现的次数从大到小考虑，不难发现这样考虑前面的数所占的位置一定会减少后面的选择，事情变得美妙了起来。

思考 dp 过程中需要记录什么：当前考虑到的次数，值域上已经填过的数，已经填过的位置。于是我们用 $f(i,j,s)$ 分别表示前述状态，$suc_i$ 表示 $A$ 序列中大于等于 $i$ 的数的个数，同时枚举当前次数的数的种类数 $k$，有转移如下：

$$f(i,j,s) \leftarrow \dfrac{f(i+1,j-k,s-ki) \times {suc_i-s+ki \choose ki} \times (ki)! \times {suc_i -j + k \choose k}}{(i!)^k}$$

其中第一项组合数是选位置，阶乘是可重序列的排列数，第三项组合数是选所填数的种类。

乍一看这 dp 好像是 $O(n^4)$ 的，但不难发现枚举中 $j$ 与 $k$ 分别是 $\dfrac{n}{i}$  和 $\dfrac{s}{i}$ 级别的，所以时间复杂度是 $O(n^3)$ 的。

[代码](https://atcoder.jp/contests/arc162/submissions/45303193)

---

## 作者：BINYU (赞：5)

## 题意

给定一个长度为 $n$ 且值域为 $[1,n]$ 的数组 $a$，问存在多少个长度为 $n$ 的数组 $b$，满足以下条件：

1. $\forall i \in [1,n]$，$1 \le b_i \le n$；

2. $\forall i \in [1,n]$，$cnt_i \le a_i$；

2. $\forall i \in [1,n]$，$cnt_{b_i} \le a_i$；

其中 $cnt_i$ 为 $i$ 在 $b$ 数组中的出现次数。

## 思路

我们先考虑弱化版的问题：只有条件 1 和 3。

考虑对于 $i$ 和 $j$，若有 $cnt_i > cnt_j$，那么能填 $j$ 的位置构成的集合一定包含能填 $i$ 的位置的集合，所以，我们先填 $i$，再填 $j$ 是没有后效性的。

考虑设计 DP 状态 $dp_{i,j,k}$ 表示已经选了 $i$ 种数，最后一种数出现 $j$ 次，所有的数一共占了 $k$ 个位置，再定义$sum_i$ 表示 $a$ 数组中大于 $i$ 的位置的个数，转移就相当于给当前数选位置，一共有 $sum_j$ 个位置可选，但之前的数已经在里面占了 $k - j$ 个位置，所以还有 $sum_j - k + j$ 个位置可选，要选 $j$ 个，DP 转移方程为：

$$dp_{i,j,k} = \sum\limits_{j \le lstj \le k-j}{dp_{i-1,lstj,k-j}\times C_{sum_j-k+j}^{j}}$$

再考虑条件 2。

本质上就是对上面的每种数确定具体的值，对于第 $i$ 种数，只有 $a$ 数组中大于等于 $j$ 的下标可以选，一共有 $sum_j$ 个，先前选了 $i - 1$ 个，所以现在就是要在 $sum_j - i + 1$ 个位置中选 $1$ 个。

但在 $lstj = j$ 的转移中，这样选数会重复计算（前面确定的值和当前的交换后和原来的是一种方案）。考虑到选数只跟当前数的出现次数有关，考虑把出现次数相同的数合并起来算。

重新定义 DP 状态 $dp_{i,j,k}$ 表示现在考虑出现次数大于等于 $i$ 的数，一共有 $j$ 种，共占了 $k$ 个位置。

枚举出现次数 $i$ 和 满足 $cnt_j = i$ 的 $j$ 的个数与满足 $cnt_{lstj} > i$ 的 $lstj$ 的个数，以前占的总位置数 $k$。

对于位置上的数值的确定，我们可以先**有序**的选 $i\times j$ 个，然后把连续的 $i$ 个分成一组，填同一类数，发现对于组内的顺序是无关紧要的（它们最终填的数相同），所以再除以 $(i!)^j$ 就是确定当前选出位置具体数值的方案数。

DP 转移方程为:

$$dp_{i,j+lstj,k+i\times j} = \sum{dp_{i+1,lstj,k}\times{C_{sum_j-lst}^{j}}\times{\frac{A_{sum_i-k}^{i\times j}}{(i!)^j}}}$$

注意 $j$ 可以为 $0$，所以答案为：

$$\sum\limits_{0 \le j \le n}{dp_{1,i,n}}$$

空间上，我们可以用滚动数组滚掉 $i$，最后剩下来的就是 $O(n^2)$。

时间上，因为 $i \times j$ 是不会大于 $n$ 的，所以前两维的枚举一共枚举了 $\sum\limits{\left\lfloor{\frac{n}{i}}\right\rfloor}$，大约为 $O(n\log n)$，对于 $lst$ 和 $k$，我们可以在枚举时限制上下界减小常数，都远小于 $O(n)$，总的时间复杂度为 $O(n^3\log n)$，常数非常小。

---

## 作者：NATO (赞：2)

### 思路浅析：

考虑填入的数 $i$ 受到的限制。

发现即是不能超过 $a_i$ 以及它填入的所有位置 $S$ 中 $\min\limits_{k\in S} a_k$。


你枚举几个常见的转移顺序之后都不行：按位置顺序枚举填哪个数，按 $a_i$ 大小顺序填等。

考虑我们上面几个转移不行都是因为你始终需要具体位置来考虑一个数所有填入位置中最小的 $a$，考虑一种可以避免枚举具体位置的转移顺序。

容易发现我们知道了一个数 $i$ 的出现次数，就能够确定它能放在哪些位置，进而我们可以用一个组合数表示出其放的方案数。

于是我们确定了以枚举数的出现次数做为转移顺序，注意到我们从小到大枚举可以填数的位置会越来越少，而我们并不知道之前填的数中有哪些填在了当前可以填数的位置，而从大到小就没有这样的问题了。

于是我们设 $dp_{i,j}$ 表示已经用了 $i$ 种数，填了 $j$ 个位置的方案数，转移从大到小枚举当前数的出现次数 $x$（$dp'$ 表示已经考虑了 $\ge x+1$ 的出现1次数的结果，$sum_x$ 表示有多少个 $a\ge x$）：

$$dp_{i,j}=\sum\limits_{k=0}^{\frac{sum_x}{x}}\frac{(kx)!}{(x!)^k}C_{sum_x-(i-k),k}C_{sum_x-(j-kx),kx}dp'_{i-k,j-kx}$$

这玩意看起来是 $O(n^4)$ 的，但因为 $k$ 和 $i$ 的上界都是 $\frac{n}{i}$，实际复杂度是 $O(n^3)$ 的。

#### 参考代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353;
ll mol(ll x)
{
	return x>=MOD?x-MOD:x;
}
ll n,a[505];
ll dp[505][505],sum[505],f[505],inv[505][505];
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;b>>=1;
	}
	return res;
}
ll C(ll n,ll m)
{
	return f[n]*inv[m][1]%MOD*inv[n-m][1]%MOD;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	f[0]=1;
	for(ll i=1;i<=n;++i)cin>>a[i],++sum[a[i]],f[i]=f[i-1]*i%MOD,inv[i][0]=1;
	inv[n][1]=qpow(f[n],MOD-2);
	for(ll i=n-1;i>=0;--i)inv[i][1]=inv[i+1][1]*(i+1)%MOD;
	for(ll i=0;i<=n;++i)
		for(ll j=2;j<=n;++j)
			inv[i][j]=inv[i][j-1]*inv[i][1]%MOD;
	for(ll i=n;i;--i)sum[i]+=sum[i+1];
	dp[0][0]=1;
	for(ll i=n;i>=1;--i)
		for(ll j=n/(i+1);j>=0;--j)//枚举之前用了多少个数 
			for(ll l=sum[i+1];l>=j*(i+1);--l)
			for(ll k=1;k+j<=sum[i]&&k*i+l<=sum[i];++k)
				dp[j+k][k*i+l]=mol(dp[j+k][k*i+l]+dp[j][l]*C(sum[i]-j,k)%MOD*C(sum[i]-l,k*i)%MOD*f[k*i]%MOD*inv[i][k]%MOD);
	ll res=0;
	for(ll i=0;i<=n;++i)res=mol(res+dp[i][n]);
	cout<<res;
}
```

---

## 作者：BreakPlus (赞：1)

将值为 $x$ 的数填进 $B$ 里去，设一共填入 $c$ 个，约束条件等价于：

+ $c \le A_i$；
+ 对于任意填入 $x$ 的位置的位置 $j$，有 $c \le A_j$。

发现只考虑前者很容易，但是**后者**需要通过一种经典的计算方式来计算贡献（假设已经钦定了每一个 $c_x$）：

+ 将 $A_i$ 降序排序，并将每个值 $x$ 按 $c_x$ 降序排序。
+ 依次在 $B$ 中填入每个值 $x$。
+ 发现每次都只能填一个前缀（满足 $A_i \ge c_x$ 的 $i$ 构成一个前缀），并且这个前缀越来越长（$c_x$ 递减）。也就是说每次填数时，这个前缀中已经被填的位置数是固定的。
+ 令前缀长度为 $p$，之前一共填了 $c_0$ 个数，那么对答案的贡献就是 ${p-c_0 \choose c_x}$。

在上面的基础上，我们用类似的方法计算**前者**的贡献，求出将每个数的出现次数和这个数的值对应的方案数。

发现它能和上面类似的方法计算：对于每个 $c_x$ 若降序考虑，每次可以对应的 $x$ 也是一个越来越长的前缀。

计算方式被分析透后，DP 过程便是顺水推舟了。

$f(i,j,k)$ 表示考虑了所有出现次数 $\ge i$ 的，已经考虑了 $j$ 种数的出现次数（计算前者的贡献），当前的前缀已经填了 $k$ 个数（计算后者的贡献）。转移容易。

```cpp
const ll mod = 998244353;
inline ll read(){
	ll x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}

ll n,a[505],f[505][505][505],C[505][505];
ll Fac[505], Inv[505], pre[505][505];
void solve(){
	n=read();
	C[0][0]=1;
	for(ll i=1;i<=n;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	Fac[0]=1;
	for(ll i=1;i<=n;i++) Fac[i] = Fac[i-1] * i % mod;
	Inv[n] = qpow(Fac[n], mod-2);
	for(ll i=n-1;i>=0;i--) Inv[i] = Inv[i+1] * (i+1) % mod;

	for(ll i=0;i<=n;i++){
		for(ll j=0;j<=n;j++){
			pre[i][j] = qpow(Inv[i], j);
		}
	}
	for(ll i=1;i<=n;i++) a[i]=read();
	sort(a+1, a+n+1, greater<ll>());
	f[n+1][0][0] = 1;
	for(ll i=n;i>=1;i--){
		ll suf = 0;
		while(suf < n && a[suf+1] >= i) ++suf;
		for(ll j=0;j<=n/(i+1);j++){
			for(ll k=0;k<=suf;k++){
				for(ll l=0;l<=(suf-k)/i;l++){
					f[i][j+l][k+i*l]=(f[i][j+l][k+i*l]+f[i+1][j][k]*C[suf-k][i*l]%mod*C[suf-j][l]%mod*Fac[i*l]%mod*pre[i][l])%mod;
					if(f[i+1][j][k]*C[suf-k][i*l]%mod*C[suf-j][l]%mod*Fac[i*l]%mod*pre[i][l]){
					}
				}
			}
		}
	}
	ll ans = 0;
	for(ll i=0;i<=n;i++) ans += f[1][i][n];
	printf("%lld\n", ans % mod);
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc162_e)

**题目大意**

> 给定 $a_1\sim a_n$，求有多少 $b_1\sim b_n$ 满足：
>
> - $b_i\in [1,n]$，且 $i$ 和 $b_i$ 的出现次数均不超过 $a_i$。
>
> 数据范围：$n\le 500$。

**思路分析**

设 $\ge k$ 的 $a_i$ 有 $c_k$ 个。

显然要把同一个颜色一起插入，假设该颜色出现次数为 $p$，那么可选的值有 $c_p$ 种，位置也有 $c_p$ 个，这是容易的。

假如要插更多颜色，只要我们按出现次数从大到小插，那么每个被占用过的位置和值都在这 $c_p$ 个数里出现过，只要记录插的颜色数和大小和。

因此 $dp_{i,j,k}$ 表示出现次数 $\ge i$ 的颜色共有 $j$ 个，总占用空间为 $k$ 的方案数，转移时枚举出现次数为 $i$ 的颜色数 $x$，$dp_{i,j,k}\gets dp_{i+1,j+x,k+ix}$，系数是一堆组合数分配位置和值。

注意到 $ij\le n,ix\le  n$，因此枚举 $i,j,x$ 复杂度是 $\mathcal O(n^2)$ 的。

时间复杂度 $\mathcal O(n^3)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=505,MOD=998244353;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
int n,a[MAXN],c[MAXN]; //#a[k]>=i
ll fac[MAXN],ifac[MAXN],f[MAXN][MAXN],q[MAXN][MAXN];
ll C(ll x,ll y) { return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD; }
//f[i,j,k]: occ>=i, cnt=j, siz=k
//f[i+1,j,k] -> f[i,j+x,k+ix]*C(c[i]-j,x)*C(c[i]-k,ix)*q[ix][i]
signed main() {
	scanf("%d",&n);
	for(int i=fac[0]=ifac[0]=1;i<=n;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),++c[a[i]];
	for(int i=n;i>=1;--i) c[i]+=c[i+1];
	for(int i=1;i<=n;++i) {
		q[i][i]=1;
		for(int j=2*i;j<=n;j+=i) q[i][j]=q[i][j-i]*C(j,i)%MOD;
	}
	f[0][0]=1;
	for(int i=n;i>=1;--i) for(int j=min(n/(i+1),c[i+1]);~j;--j) for(int k=n;k>=(i+1)*j;--k) if(f[j][k]) {
		ll pw=1;
		for(int x=0,tj=j,tk=k;tk<=c[i];++x,++tj,tk+=i,pw=pw*ifac[i]%MOD) {
			f[tj][tk]=(f[tj][tk]+f[j][k]*C(c[i]-j,x)%MOD*C(c[i]-k,i*x)%MOD*q[i][i*x])%MOD;
		}
	}
	ll ans=0;
	for(int i=1;i<=n;++i) ans=(ans+f[i][n])%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

感觉有点萌啊，算了我更萌，真降智了。

难点在于脑筋要转弯，不要一头扎死在生成函数上边。

记 $i$ 在 $B$ 中出现了 $d_i$ 次，那么我们发现随着 $d_i$ 的变小，限制不断放宽，那么就可以考虑按 $d_i$ 从大到小 DP 了。

DP 状态：$dp_{i,j,k}$ 表示 $d_x\ge i$ 的数有 $j$ 个，它们总共出现了 $k$ 次的方案数。

记 $C_i=\sum\limits_{j=1}^n[A_j\ge i]$，也就是如果我们要放一个出现次数为 $i$ 的数，它有可能放的位置有多少。

枚举有 $x$ 个出现次数为 $i$ 的数，那么有 ${C_i-j\choose x}$ 个方案确定这些数（因为限制 $i$ 的出现次数小于等于 $A_i$），然后有 $\frac{(C_i-k)!}{(i!)^x(C_i-ix-k)!}$ 种方法放这些数，也就是一个多重集组合数，比较没有水平。

然后式子就是 $dp_{i+1,j,k}\times{C_i-j\choose x}\frac{(C_i-k)!}{(i!)^x(C_i-ix-k)!}\to dp_{i,j+x,k+ix}$。

然后发现这个复杂度是 $O(n^4)$？其实不是，因为 $j$ 和 $x$ 的上界是 $\lfloor\frac{n}{i}\rfloor$，所以是比较对的 $O(n^3)$。

具体的话可以想想 $\sum_{i=1}^{\infty}\frac{1}{i^2}=\frac{\pi^2}{6}=O(1)$，巴塞尔问题。

数组开得没水平可能会出事。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=510;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}p[N][N];

int n,A[N],cnt[N];

template < int Max >
struct Choose{
	modint frac[Max+10],inv[Max+10];
	Choose(){
		frac[0]=inv[0]=1;for(int i=1;i<=Max;++i) frac[i]=frac[i-1]*i;
		inv[Max]=frac[Max].inv();for(int i=Max-1;i;--i) inv[i]=inv[i+1]*(i+1);
	}
	modint operator ()(const int x,const int y){return x<y||y<0?0:frac[x]*inv[y]*inv[x-y];}
};

Choose < N > C;
vector < vector <  modint > > f[N];

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	for(int i=1;i<=n;++i) cin>>A[i],++cnt[A[i]];
	for(int i=n;i;--i) cnt[i]+=cnt[i+1];
	for(int i=1;i<=n+1;++i){
		f[i].resize(n/i+10);
		for(int j=0;j<=n/i+5;++j) f[i][j].resize(n+10);
	}
	f[n+1][0][0]=1;
	for(int i=1;i<=n;++i){
		p[i][0]=1;for(int j=1;j<=n;++j) p[i][j]=p[i][j-1]*C.inv[i];
	}
	for(int i=n;i;--i){
		for(int j=0;j<=n/(i+1);++j){
			for(int k=0;k<=cnt[i];++k){
				if(!f[i+1][j][k].val) continue;
				for(int x=0;x<=(n/i);++x){
					if(x+j>n||(i*x+k>cnt[i])) continue;
					f[i][j+x][k+i*x]+=f[i+1][j][k]*
					C(cnt[i]-j,x)*C.frac[cnt[i]-k]*C.inv[cnt[i]-i*x-k]*p[i][x];
				}
			}
		}
	}
	modint res=0;
	for(int i=1;i<=n;++i) res+=f[1][i][n];
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

记 $s_i$ 为 $i$ 在 $B$ 中出现次数。

按 $s_i$ 从大到小 dp，记 $f_{i,j,k}$ 代表考虑出现次数 $\ge i$ 的数，这些数有 $j$ 个，出现次数之和为 $k$。

记 $m_i$ 代表大于等于 $i$ 的 $A_i$ 个数，转移时，考虑枚举 $x$ 个数出现了 $i$ 次，这 $x$ 个数有 $\begin{pmatrix}
 m_i-j\\
x
\end{pmatrix}$ 种方案确定，填充方案为 $\begin{pmatrix}
 m_i - j\\
i,...,i,m_i - j - kx
\end{pmatrix}$，下面有 $x$ 个 $i$。

由于 $\sum\limits_1^{\infty} \dfrac{1}{i^2} = \dfrac{\pi^2}{6}$，所以时间复杂度为 $O(n^3)$。

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
using i16 = short; using i32 = int; using i64 = ll; using i128 = __int128_t;
using namespace std;
const int N = 5e2 + 5, mod = 998244353;
i32 fac[N], ifac[N]; 
fn i32 qkpow(i32 a, i32 b) {
  i32 ans = 1;
  for (; b; b >>= 1) {
    if (b & 1) ans = 1ll * ans * a % mod;
    a = 1ll * a * a % mod;
  }
  return ans;
}
fv init() {
  rep (i, fac[0] = ifac[0] = 1, N - 5) ifac[i] = qkpow(fac[i] = 1ll * fac[i - 1] * i % mod, mod - 2);
}
fn i32 C(i32 n, i32 m) {
  return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
i32 n, x, s[N], f[N][N][N];
int main() {
  init();
  cin >> n;
  rep (i, 1, n) cin >> x, s[x]++;
  drep (i, n, 1) s[i] += s[i + 1];
  f[n + 1][0][0] = 1;
  drep (i, n, 1) {
    rep (j, 0, min(n / (i + 1), s[i + 1])) {
      rep (k, 0, s[i + 1]) {
        if (!f[i + 1][j][k]) continue;
        i32 t = 1;
        rep (x, 0, min(n - j, (s[i] - k) / i)) {
          f[i][j + x][k + i * x] = (f[i][j + x][k + i * x] + 1ll * f[i + 1][j][k] * C(s[i] - j, x) % mod * fac[s[i] - k] % mod * ifac[s[i] - k - i * x] % mod * t % mod) % mod;
          t = 1ll * t * ifac[i] % mod; 
        }
      }
    }
  }
  i32 ans = 0;
  rep (i, 0, s[1]) ans = (ans + f[1][i][n]) % mod;
  cout << ans;
}
```

---

## 作者：Deamer (赞：0)

神仙提，赛时一点不会。

题目给了两个限制：

1. $cnt_i \le a_i$

2. $cnt_{b_i} \le a_i$

肯定要 dp，我们设 $f_{i,j,k}$ 表示现在填完了出现次数大于等于 $i$ 的数，一共 $j$ 种数，占了 $k$ 个位置。

为什么要从出现次数大的转移到小的呢，因为出现次数小的数能填的位置的集合一定包含出现次数大的数的位置集合，这样转移就没有后效性了。

把出现次数相同的数合并起来转移是因为，出现次数相同的数转移不分先后顺序，如果一个数一个数的填就会算重。

其实状态设计好了，转移就简单了。

我们设 $g_i = \sum [a_j \ge i]$。

转移时，枚举当前出现次数 $i$ 选 $p$ 种不同的数，由于限制 1 这个方案数是 $C_{g_i-j}^p$ 的。

然后 b 数组中多了 $i \times p$ 个数，考虑分配他们的位置，由于限制 2 ，合法的放置位置一共有 $g_i-k$ 个，我们在其中先有序的选 $i \times p$ 个位置，然后每连续的 $i$ 个分给一个数，然后由于每种数的不同位置没有顺序，再除掉每种数的重复，方案数就是 $\frac {A_{g_i-k}^{i \times p}} {(i!)^p}$。

然后转移柿子就有了：

$$f_{i,j+p,k+i \times p}=\sum f_{i+1,j,k} \times C_{g_i-j}^p \times \frac {A_{g_i-k}^{i \times p}} {(i!)^p} $$

注意 $j$ 和 $p$ 都能取到 $0$。

答案就是 $\sum_{i=0}^n f_{1,i,n}$。

观察到 $j$ 和 $p$ 的上界是 $\lfloor \frac{n}{i} \rfloor$，所以时间复杂度是 $n^3$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N=5e2+10;
const int mod=998244353;
int n;
int a[N];
int jc[N],inv[N];
int g[N];
int f[N][N][N];
int ans;

void Add(int &x,int y) { x=(x+y)%mod; }

int Fastpow(int x,int k){
    int ans=1;
    while(k){
        if(k&1) ans=ans*x%mod;
        x=x*x%mod;
        k>>=1;
    }
    return ans;
}

int C(int n,int m) { return jc[n]*inv[m]%mod*inv[n-m]%mod; }

int A(int n,int m) { return jc[n]*inv[n-m]%mod; }

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[j]>=i) g[i]++;
        }
    }
    jc[0]=1;
    for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
    inv[n]=Fastpow(jc[n],mod-2);
    for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
    f[n+1][0][0]=1;
    for(int i=n;i;i--){
        for(int j=0;j<=g[i+1] && (i+1)*j<=n;j++){
            for(int k=(i+1)*j;k<=n;k++){
                if(!f[i+1][j][k]) continue;
                int x=1;
                for(int p=0;p<=g[i]-j && i*p<=g[i]-k;p++){
                    Add(f[i][j+p][k+i*p],f[i+1][j][k]*C(g[i]-j,p)%mod*A(g[i]-k,i*p)%mod*x%mod);
                    x=x*inv[i]%mod;
                }
            }
        }
    }
    for(int i=0;i<=n;i++) Add(ans,f[1][i][n]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Komomo (赞：0)

发现不管按 $B$ 值域大小填还是按 $i$ 填，都无法合理的设计一个状态。但整题围绕着次数展开，令 $cnt_x$ 表示 $x$ 在方案中出现的次数，则对于两个数 $x,y$，若 $cnt_x>cnt_y$，则 $x$ 能填的集合 $y$ 一定能填。原因为考虑目前 $x$ 填的所有位置集合 $S$，$cnt_y<cnt_x\le \min\limits_{p\in S}\{A_p\}$。

于是我们令 $f(i,j,k)$ 表示填到 $cnt=i$，$j$ 种数，总个数为 $k$。枚举又新填了 $t$ 种数，则总和新增了 $it$ 个，考虑如何从 $f(i+1,j,k)$ 转移到 $f(i,j+t,k+it)$。

考虑**第一个条件**，对于选择的数 $x$ 需要满足 $i\le B_x$，令 $C_i$ 表示 $\sum\limits_{x=1}^n[i<B_x]$，则有 $C_i-j$ 种数可以填，这里的方案即为 $w_1=\dbinom{C_i-j}{t}$。

考虑**第二个条件**，同样可以填的位置数为 $C_i-k$，$t$ 种数每种要填 $i$ 个，方案数为 $w_2=\dbinom{C_i-k}{\underbrace{i,\cdots,i}_{\text{count}=t},C_i-k-it}$。

于是转移方程即为 $f(i, j+t, k+it)\leftarrow w_1w_2f(i+1,j,k)$，因为 $ij\le n$，$k,t$ 枚举上界为 $\mathcal O(n)$，一个很松的上界为 $\mathcal O(n^3\log n)$，但因为 $k,t$ 远远跑不满，所以很轻松就能跑过。

感觉状态是最难想的了。

---

## 作者：Leasier (赞：0)

感谢 [goujingyu](https://www.luogu.com.cn/user/266966) 的 hint。

------------

一个直观的想法是按 $A_i$ 单调递增 / 减排序依次讨论，但好像根本没法转移，因为我们对每个 $i$ 都关心其选择的最小 $A_j$，这一点在这种转移顺序中没能得到体现。

~~然后 gjy 给我说了 [CF1827A Counting Orders](https://www.luogu.com.cn/problem/CF1827A) 作为 hint。~~

参考 CF1827A 的解法，我们希望找到一个填数顺序，使得**填入一个数时，我们只关心此前被填的数字种数或数量等不难表出的信息，而不是具体填入了啥这种较为复杂的信息**。

对于一个 $i$ 而言，我们要求 $B_j = i$ 的 $j$ 数量 $\leq \min(A_i, A_j)$。

考虑按**最终每个数出现次数**的顺序填入，则：

- 设当前讨论出现次数为 $i$ 的数。
- 若要让 $j$ 出现 $i$ 次，则 $A_j \geq i$，且填入位置 $B_k = j$ 要满足 $A_k \geq i$。

从这个角度出发，我们关心的是：

- 设 $suf_i$ 表示满足 $A_j \geq i$ 的 $j$ 数量，则我们关心 $suf_i$。
- 在这 $suf_i$ 个数对应的 $j$ 中，有几个 $j$ 已经填入了 $B$。
- 在这 $suf_i$ 个数对应的 $k$ 中，有几个 $B_k$ 已经被填了。

于是我们关心的项都是“个数”状的信息，考虑 dp。

设 $dp_{i, j, k}$ 表示已经讨论了最终出现次数 $\geq i$ 的数，有 $j$ 种数已经填入了 $B$，有 $k$ 个 $B$ 中的位置已经被填的方案数。

转移是一个可重集排列，较为简单，略去。

时间复杂度看上去为 $O(n^4)$，但由于 $\displaystyle\sum_{i = 1}^{+\infty} \frac{1}{i^2} = \frac{\pi^2}{6}$ 为常数，时间复杂度实际上为 $O(n^3)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;
int suf[507];
ll fac[507], inv_fac[507], power[507], dp[507][507][507];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	fac[0] = 1;
	for (int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline ll comb(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int main(){
	int n;
	ll ans = 0;
	scanf("%d", &n);
	init(n);
	for (int i = 1; i <= n; i++){
		int a;
		scanf("%d", &a);
		suf[a]++;
	}
	for (int i = n; i >= 1; i--){
		suf[i] += suf[i + 1];
	}
	dp[n + 1][0][0] = 1;
	for (int i = n; i >= 1; i--){
		power[0] = 1;
		for (int j = 1; j <= suf[i]; j++){
			power[j] = power[j - 1] * inv_fac[i] % mod;
		}
		for (int j = 0; (i + 1) * j <= suf[i + 1]; j++){
			for (int k = (i + 1) * j; k <= suf[i + 1]; k++){
				for (int l = 0; j + l <= suf[i] && k + i * l <= suf[i]; l++){
					dp[i][j + l][k + i * l] = (dp[i][j + l][k + i * l] + dp[i + 1][j][k] * comb(suf[i] - j, l) % mod * (fac[suf[i] - k] * power[l] % mod * inv_fac[suf[i] - k - i * l] % mod) % mod) % mod;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++){
		ans = (ans + dp[1][i][n]) % mod;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [[ARC162E] Strange Constraints](https://www.luogu.com.cn/problem/AT_arc162_e)

比较难想的一道题。看完题目发现并没有什么思路，考虑将题目中的文字信息转换成式子之类的。

令 $d_i$ 表示 $i$ 在 $B$ 序列中的出现次数。题目要求：

$$\forall i \in [1,n],d_i \leq A_i$$

$$\text{对于位置}i,d_j \leq A_i \text{的} j \text{可以被放到} B_i$$

不难发现，$d_i$ 越小，可以选择的位置就越多，于是我们可以按照 $d_i$ 从大到小考虑每一个 $i$。令 $dp_{i,j,k}$ 表示考虑出现次数大于等于 $i$ 的数，有 $j$ 个，它们总共出现了 $k$ 次的方案数。

设 $b_i=\sum_{j=1}^n[A_j \geq i]$。转移的时候考虑在枚举到 $dp_{i+1}$ 的时候更新 $dp_i$。每次转移枚举 $x$ 个数各出现了 $i$ 次。那么这 $x$ 个数的选择方案为 $C_{b_i-j}^x$，把它们填到 $B$ 序列中的方案数为 $C_{b_i}^i \times C_{b_i-i}^i \times \dots \times C_{b_i-(x-1) \times i}^i=\frac {(b_i-k)!} {(i!)^x \times (b_i-k-i\times x)!}$。那么转移方程为 $dp_{i+1,j+x,k+i \times x} \longleftarrow dp_{i,j,k} \times C_{b_i-j}^x \times \frac {(b_i-k)!} {(i!)^x \times (b_i-k-i\times x)!}$。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=510,mod=998244353;
int n;
int a[N],b[N],fac[N],ifac[N];
int f[N][N][N];
inline int ksm(int a,int b)
{
    int res=1;
    while (b)
    {
        if (b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
inline int C(int n,int m)
{
    if (n<m||n<0||m<0) return 0;
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod; 
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("zsr.in","r",stdin);
    freopen("zsr.out","w",stdout);
#endif
    scanf("%lld",&n);
    fac[0]=1;
    for (int i=1;i<=n;++i) 
    {
        scanf("%lld",&a[i]);
        ++b[a[i]];
        fac[i]=fac[i-1]*i%mod;
    }
    ifac[n]=ksm(fac[n],mod-2);
    for (int i=n-1;i>=0;--i) ifac[i]=ifac[i+1]*(i+1)%mod;
    for (int i=n-1;i>=1;--i) b[i]+=b[i+1];
    f[n+1][0][0]=1;
    for (int i=n;i>=1;--i)
    {
        for (int j=0;j*(i+1)<=n&&j<=b[i+1];++j)
        {
            for (int k=0;k<=b[i+1];++k)
            {
                if (!f[i+1][j][k]) continue;
                int fc=1;
                for (int x=0;j+x<=n&&k+i*x<=b[i];++x)
                {
                    f[i][j+x][k+i*x]=(f[i][j+x][k+i*x]+f[i+1][j][k]*C(b[i]-j,x)%mod*fac[b[i]-k]%mod*fc%mod*ifac[b[i]-k-i*x]%mod)%mod;
                    fc=fc*ifac[i]%mod;
                }
            }
        }
    }
    int ans=0;
    for (int i=0;i<=b[1];++i) ans=(ans+f[1][i][n])%mod;
    printf("%lld\n",ans);
    return 0;
}
```


---

