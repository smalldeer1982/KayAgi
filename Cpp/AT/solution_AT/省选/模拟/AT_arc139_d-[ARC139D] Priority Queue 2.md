# [ARC139D] Priority Queue 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc139/tasks/arc139_d

要素数が $ N $ の整数の多重集合 $ A=\lbrace\ A_1,A_2,...,A_N\ \rbrace $ が与えられます。$ A $ の要素は全て $ 1 $ 以上 $ M $ 以下であることが保証されています。

以下の操作を $ K $ 回繰り返します。

- $ 1 $ 以上 $ M $ 以下の整数を選び、$ A $ に追加する。その後、$ A $ の中で $ X $ 番目に小さい値を $ 1 $ 個削除する。

$ A $ の中で $ X $ 番目に小さい値とは、$ A $ の要素を単調非減少になるように一列に並べたとき、先頭から $ X $ 番目にくる値のことです。

$ 1 $ 以上 $ M $ 以下の値を $ K $ 回選ぶ方法は $ M^K $ 通りありますが、その全てに対して操作終了後の $ A $ の要素の総和を求めたとします。これらの $ M^K $ 個の値の総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N,M,K\ \le\ 2000 $
- $ 1\ \le\ X\ \le\ N+1 $
- $ 1\ \le\ A_i\ \le\ M $
- 入力は全て整数である。

### Sample Explanation 1

初め $ A=\{1,3\} $ です。操作の例としては以下のようなものが考えられます。 - $ A $ に $ 4 $ を追加する。$ A=\{1,3,4\} $ となる。$ A $ の $ 1 $ 番目に小さい値を削除する。$ A=\{3,4\} $ となる。 - $ A $ に $ 3 $ を追加する。$ A=\{3,3,4\} $ となる。$ A $ の $ 1 $ 番目に小さい値を削除する。$ A=\{3,4\} $ となる。 この場合、操作後の $ A $ の要素の総和は $ 3+4=7 $ となります。

## 样例 #1

### 输入

```
2 4 2 1
1 3```

### 输出

```
99```

## 样例 #2

### 输入

```
5 9 6 3
3 7 1 9 9```

### 输出

```
15411789```

# 题解

## 作者：Phartial (赞：7)

上个世纪做过这题，然后今天比赛（abc295）出了道弱化没做出来，被 pty 喷了一遍后爬来写个题解/kk

首先这种期望/总和题都有个套路，就是通过另外一种角度来计算每个元素的贡献。对于此题，我们有：

$$
ans=\sum_{i=1}^mi\cdot c(=i)=\sum_{i=1}^mc(\ge i)
$$

其中 $c(P)$ 表示对于所有方案中的每个 $a_i$，满足条件 $P$ 的数的数量。

于是考虑枚举 $i$，则我们需要维护 $c(\ge i)$，对一次操作，设这次操作选出的数为 $v$，我们有：

- $v<i$：$c$ 不变。
- $v\ge i$：$c$ 加一。

而在每次操作后，由于我们还要删除第 $x$ 小的元素，所以还有：

- 操作完后，若 $n+1-c<x$，即 $c>n+1-x$，那么 $c$ 减一。

可以发现，$n+1-x$ 像一个界限，$c$ 如果超过了它就会被压回去，所以我们可以先忽略删除第 $x$ 小，在最后将 $c$ 和 $n+1-x$ 取 $\min$ 即可。

考虑对于 $k$ 次操作，其中有多少次操作将 $c$ 加了一，设加了 $p$ 次，那么方案数显然为 $(m-i+1)^p(i-1)^{k-p}\displaystyle{k\choose p}$（没加一的方案数 乘上 加一的方案数 乘上 $k$ 次操作中选出 $p$ 次操作的方案数）。

由于最后的 $c$ 可以直接计算得到，故直接累加答案即可。

一个细节：注意到减一最多减 $k$ 次，所以还要定一个下界。

时间复杂度 $O(m(n+k))$。

```cpp
#include <atcoder/all>
#include <iostream>

using namespace std;
using LL = atcoder::modint998244353;

const int kN = 2001;
const int kM = 998244353;

int n, m, k, x, a[kN];
LL ans, sc[kN], iv[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k >> x;
  iv[1] = 1;
  for (int i = 2; i <= k; ++i) {
    iv[i] = -LL(kM / i) * iv[kM % i];
  }
  sc[0] = 1;
  for (int p = 1; p <= k; ++p) {
    sc[p] = sc[p - 1] * (k - p + 1) * iv[p];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    int bc = 0;
    for (int j = 1; j <= n; ++j) {
      bc += a[j] >= i;
    }
    for (int p = 0; p <= k; ++p) {
      int c = max(bc + p - k, min(bc + p, n + 1 - x));
      ans += LL(i - 1).pow(k - p) * LL(m - i + 1).pow(p) * sc[p] * c;
    }
  }
  cout << ans.val();
  return 0;
}
```


---

## 作者：Rosabel (赞：4)

非常 Educational 的一道好题！

默认 $n,m,k$ 同阶。

直接考虑 dp，那么需要记录三维：第 $i$ 轮；升序排序第 $j$ 个元素；值为 $k$ 的方案数。这看起来非常的不友好。尽管转移可以均摊到 $\Theta(1)$，但是状态数是 $\Theta(n^3)$ 的。而且无法做到省略一些状态或者通过合并一些状态优化复杂度。这是不可行的。

我们注意到对于转移而言，特殊的转移一定与 $j$ 这维的 $x$ 有关，所以不妨猜测我们可以通过某种方法去优化这一维。而从轮数考虑的 dp 显然不可行，因为 $j$ 和 $k$ 是必须选的。

考虑到我们 dp 的初始约束在轮数这一维，我们不妨将我们先考虑的维度迁移到元素 rank 和 value。（很显然这两个是必须选的）。即设 $f(k,j)$ 表示最终 $\le k$ 的元素个数恰好为 $j$ 的方案数。发现固定 $k$ 之后 $i$ 和 $j$ 就可以进行冗余状态的合并了。状态设好之后接下来就是 trival 的。设 $g(k)$ 为初始 $a$ 状态 $\le k$ 的元素个数。考虑当 $j$ 在不同范围内的时候，一轮中可能对新的 $j$ 造成怎样的影响：

- $j\lt x-1$，下一轮若新增元素 $\le k$ 会对 $j+1$ 有 $k$ 的贡献；否则会对 $j$ 有 $K-k$ 的贡献。
- $j\gt x-1$，下一轮若新增元素 $\le k$，则恰好抵消本来要在 $[1,k]$ 区间删掉的一个，会对 $j$ 有 $k$ 的贡献；否则会对 $j-1$ 有 $K-k$ 的贡献。
- $j=x-1$，则无论如何下一个状态只会是 $j$，会对 $j$ 有 $K$ 的贡献。

然后可以发现对于 $j\neq x-1$ 时 $j$  的变化总量是固定的，所以可以 $\Theta(1)$ 进行计算（要预处理幂，如果你和我一样懒，那需要多带一只 $\log$）。当 $j=x-1$ 时，变化总量是不固定的，但是发现一旦到达 $x-1$ 时，后面的转移是平凡的，所以只需枚举到达 $x-1$ 的位置即可。单次查询 $\Theta(n)$。但是由于 $j$ 是固定的，所以这部分总复杂度是 $\Theta(n^2)$。加上前面一部分 $\Theta(n^2)$ 量级的 $\Theta(1)$ 查询，总复杂度 $\Theta(n^2)$。题解由于没有预处理幂，所以会多带一只 $\log$。

[code](https://atcoder.jp/contests/arc139/submissions/60953613)

给可爱的小妹妹点个赞吧 qwq

---

## 作者：Grisses (赞：2)

[题面](https://www.luogu.com.cn/problem/AT_arc139_d)

---

发现我们不好算到最后还剩些什么。

考虑计算 $\sum\limits_{i=1}^m\sum\limits_{j=1}^n[s_j\ge i]$，容易发现这和原式等价。

记 $b_i$ 表示 $s$ 中不小于 $i$ 的数的个数，每次删去第 $x$ 小的等价于将所有超过 $n-x+1$ 的地方减 1，加入 $k$ 等价于将 $b_{1,k}$ 都加 1。

发现最终的答案就是 $\sum b$。

考虑计算每一个位值的贡献，以下记 $x'=n-x+1$。

枚举每个位值被加了多少次，倘若最初 $b_i\le x'$，有 $b_i'=\min(b_i+j,x')$；如果最初 $b_i>x'$，有 $b_i'=\max(x,b_i+j-k)$。其中 $j$ 是第 $i$ 个位值被加的次数，$k$ 是总操作次数。

---
代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
#define db long double
using namespace std;
const int mod=998244353;
int n,m,k,x,a[2005];
int c[2005],inc[2005];
int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int C(int n,int m){
	return c[n]*inc[n-m]%mod*inc[m]%mod;
}
signed main()
{
	c[0]=1;
	for(int i=1;i<=2000;i++)c[i]=c[i-1]*i%mod;
	inc[2000]=fpow(c[2000],mod-2);
	for(int i=1999;i>=0;i--)inc[i]=inc[i+1]*(i+1)%mod;
	scanf("%lld%lld%lld%lld",&n,&m,&k,&x);
	x=n+1-x;
	for(int i=1,c;i<=n;i++)scanf("%lld",&c),a[c]++;
	for(int i=m;i>=1;i--)a[i]+=a[i+1];
	int ans=0;
	for(int i=1;i<=m;i++){
		int l=m-i+1,r=i-1;
		for(int j=0;j<=k;j++){
			if(a[i]<=x)ans=(ans+(min(x,a[i]+j)*C(k,j)%mod*fpow(l,j)%mod*fpow(r,k-j)%mod))%mod;
			else ans=(ans+(max(x,a[i]+j-k)*C(k,j)%mod*fpow(l,j)%mod*fpow(r,k-j)%mod))%mod;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：DJRzjl (赞：2)

显然，我们很难直接统计最后答案，对于这类计数，可以考虑将贡献分类拆开：

- 枚举 $t\in[1,m]$，统计每个 $t$ 在所有最终序列中出现次数之和；

结果发现一个序列中 $i$ 可以出现多次，可以被删除，还是不好做，于是考虑：

- 枚举 $t\in[1,m]$，统计在所有最终序列中**大于等于 $t$** 的数的数量之和。

不妨记 $c=\sum_i [a_i\ge t]$。考虑我们的 $k$ 次操作对 $c$ 的影响。

枚举 $k$ 次操作中有 $j$ 次插入了大于等于 $t$ 的数，分两种情况：

1. 若 $n-x+1 >c$，每选一个 $\ge t$ 的数会使得 $c+1$，否则 $c$ 不变。但 $c$ 最多加到 $n-x+1$，所以此时 $c'=\min(c+j,n-x+1)$。
2. 若 $n-x+1\le c$，类似地，每选一个 $<t$ 的数会使得 $c-1$，否则 $c$ 不变。此时 $c'=\max(c-(k-j),n-x+1)$。

综上，对于枚举的 $t,j$，对最终答案的贡献为 $c'\times\binom{k}{j}(m-t+1)^j(t-1)^{k-j}$。

时间复杂度 $O(mk)$（实现时注意 $\small 0^0=1$ 在处理前后缀幂时特判）。

---

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10,mod=998244353;

int fac[N],ifac[N];
int fpow(int a,int b){
	int ret=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ret=1ll*ret*a%mod;
	return ret;
}
void init(int n){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=fpow(fac[n],mod-2);
	for(int i=n;i>1;i--) ifac[i-1]=1ll*ifac[i]*i%mod;
}
int C(int n,int m){
	if(n<m||m<0) return 0;
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

int n,m,k,x,a[N],ans;

int main(){
	init(N-1);
	scanf("%d%d%d%d",&n,&m,&k,&x);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=m;i++){
		int c=0; for(int j=1;j<=n;j++) if(a[j]>=i) c++;
		int s=fpow(i-1,k),d=1ll*(m-i+1)*fpow(i-1,mod-2)%mod;
		if(n-x+1>c){
			if(i==1) ans=(ans+1ll*fpow(m-i+1,k)*min(c+k,n-x+1))%mod;
			else for(int t=0;t<=k;t++,s=1ll*s*d%mod)
				ans=(ans+1ll*s*C(k,t)%mod*min(c+t,n-x+1))%mod;
		}else{
			if(i==1) ans=(ans+1ll*fpow(m-i+1,k)*max(c,n-x+1))%mod;
			else for(int t=0;t<=k;t++,s=1ll*s*d%mod)
				ans=(ans+1ll*s*C(k,t)%mod*max(c-(k-t),n-x+1))%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：tzc_wk (赞：0)

首先我们考虑对每个 $x\in[1,m]$，计算最终期望有多少个数 $\le x$，显然求出这个之后就能算出答案。

我们设 $c$ 表示当前状态下 $\le x$ 的数的个数，考虑下一步 $c$ 会怎么变，那么显然是我们以 $\dfrac{x}{m}$ 的概率将 $c$ 加 $1$，如果 $c>X$，那么令 $c$ 减 $1$。

注意到 $|c-X|$ 是不会增的，也就是说如果一开始 $c\le X$，那么 $c$ 最多增加到 $X$，如果一开始 $c>X$，那么 $c$ 也最少减少到 $X+1$，也就是说如果一开始 $c\le X$，并且我们进行了 $t$ 次加一操作，那么最终 $c=\min(c+t,X)$。一开始 $c>X$ 的情况也是同理，使用一个简单的组合数计算答案即可。

时间复杂度 $O(nm)$。

---

