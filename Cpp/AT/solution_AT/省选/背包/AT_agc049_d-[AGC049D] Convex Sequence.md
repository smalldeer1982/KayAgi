# [AGC049D] Convex Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc049/tasks/agc049_d

整数 $ N $ と $ M $ が与えられます． 長さ $ N $ の非負整数列 $ (A_1,A_2,\ldots,A_N) $ であって，次の条件を満たすものの個数を$ \bmod\ (10^9+7) $ で求めてください．

- $ A_1+A_2+\ldots\ +A_N\ =\ M $
- すべての $ i $ ($ 2\ \leq\ i\ \leq\ N-1 $) について，$ 2\ A_i\ \leq\ A_{i-1}\ +\ A_{i+1} $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- 入力はすべて整数である．

### Sample Explanation 1

以下の $ 7 $ 個の数列が条件を満たします． - $ 0,0,3 $ - $ 0,1,2 $ - $ 1,0,2 $ - $ 1,1,1 $ - $ 2,0,1 $ - $ 2,1,0 $ - $ 3,0,0 $

## 样例 #1

### 输入

```
3 3```

### 输出

```
7```

## 样例 #2

### 输入

```
10 100```

### 输出

```
10804516```

## 样例 #3

### 输入

```
10000 100000```

### 输出

```
694681734```

# 题解

## 作者：yanghanyv (赞：11)

## 题意
若非负数列 $A$ 中任意 $i(2 \leq i \leq N-1)$ ，都有 $2A_i \leq A_{i-1} + A_{i+1}$，则称 $A$ 为凸数列。  
问长为 $N$ ，且数列中所有项的和为 $M$ 的凸数列有多少个，答案对 $10^9+7$ 取模。

## 分析
我们可以把**最靠左**的最小值的位置叫做数列的顶点。  
为了方便，我们先讨论顶点固定在最左端的情况。  
### 顶点在最左端
我们先假设这个数列全是 $0$，此时是一个凸数列，我们不断在顶点右侧(不包括顶点)的位置加值，使得这个数列更“陡”，最终和达到 $M$，且仍为凸数列。  
可以把在右侧的加值的操作分成若干次，每一次看作对一个区间 $[i,N](i > 1)$**（注意 $i$ 不能等于 $1$）**做加法，其中 $A_j(j \in [i,N])$ 加上了 $j-i+1$。手动模拟一下，发现这样构造的数列**恰好满足凸数列的条件**。  
所以我们只要对所有区间做**完全背包**就好了，时间复杂度为 $O(NM)$，但我们发现**只有做一次区间加值小于等于 $M$ 的区间对我们有用**，而这样的区间只有 $O(\sqrt{M})$ 个，复杂度可以优化到 $O(M\sqrt{M})$。  
所以这样就做完了？  
其实不是，我们可以在数列的和较小时，可以把数列整体抬高使得和为 $M$，这些情况也要考虑，我们只要在完全背包的初始化时做一点改动就可以了。
### 顶点在其它位置
我们可以让顶点从最左端向右移动，在移动过程中，左边会增加 $O(\sqrt{M})$ 个需要考虑加值的区间，右边会减少 $O(\sqrt{M})$ 个需要考虑加值的区间，我们只要**动态地加入和删除做背包的物品**就行了。总复杂度仍是 $O(M\sqrt{M})$，注意这里 $\sqrt{M}$ 的含义并不简单，这个复杂度需要小证一下。  
设 $f_i$ 为数列和为 $i$ 时的方案数，答案就是顶点在所有位置时的 $f_M$ 的和。  
所以这样就做完了？  
其实不是，不要忘了我们一开始对顶点的定义，顶点是**最靠左**的最小值的位置，所以我们要保证顶点左边的数一定都比顶点上的数大，也就是说**数列最左端到顶点左侧的区间至少加值一次**，因此最后的答案是所有位置的 $f_{M-S_{i-1}}$ 的和，其中 $S_i$ 表示区间 $[1,i]$ 加值一次会增加的总和。
### 两种情况合并
综上，我们就真的做完了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=460;
const int MOD=1e9+7;
int n,m,cnt,s[M],f[N],ans;
int Add(int a,int b){
	return (a+b)%MOD;
}
int Sub(int a,int b){
	return (a-b)%MOD;
}
int main(){
	scanf("%d%d",&n,&m);
	while(s[cnt]<=m){
		cnt++;
		s[cnt]=s[cnt-1]+cnt;
	}
	cnt--;//预处理出合法的加值区间长度
	for(int i=0;i<=m;i+=n){
		f[i]=1;
	}//初始化时考虑整体抬高
	for(int i=1;i<=min(cnt,n-1);i++){
		for(int j=s[i];j<=m;j++){
			f[j]=Add(f[j],f[j-s[i]]);//背包
		}
	}
	for(int i=1;i<=n;i++){
		if(i-1<=cnt){
			ans=Add(ans,f[m-s[i-1]]);//算答案
		}
		if(i<=cnt){
			for(int j=s[i];j<=m;j++){
				f[j]=Add(f[j],f[j-s[i]]);//加入新区间
			}
		}
		if(n-i<=cnt){
			for(int j=m;j>=s[n-i];j--){
				f[j]=Sub(f[j],f[j-s[n-i]]);//去掉旧区间
			}
		}
	}
	ans=(ans+MOD)%MOD;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：红黑树 (赞：8)

[可能更好的阅读体验](https://rbtr.ee/agc-049-d)

## [题意](https://atcoder.jp/contests/agc043/tasks/agc043_d)
给定 $n$ 和 $m$，问有多少个长度为 $n$ 的数组 $a$ 满足：

* $\sum a_i = m$
* 对于 $i \in \left(1, n\right)$，有 $2a_i \leq a_{i - 1} + a_{i + 1}$

答案对 $10^9 + 7$ 取模。

## 题解
假设在某一方案中第一个全局最小值出现的位置在 $p$，我们断言可以依照以下流程还原该方案。

1. 选择某个 $C$，令 $a$ 中的所有元素全部为 $C$。
2. 选择某个 $i < p$，给 $a_i, a_{i - 1}, \ldots, a_1$ 分别加上 $1, 2, 3, \ldots$。此操作可以重复任意次，或者一次也不做。
3. 选择某个 $i > p$，给 $a_i, a_{i + 1}, a_n$ 分别加上 $1, 2, 3, \ldots$。此操作可以重复任意次，或者一次也不做。

---
在固定 $p$ 时，我们将问题转换成了：

我们有任意多个值为 $n, 1, 3, 6, 10, \ldots$ 的数（出现 $n$ 是对应操作 $1$），求凑出和为 $m$ 有多少种方案。

可以在 $\mathcal O\left(m \sqrt m\right)$ 的时间下使用动态规划解决。

计算答案时，我们需要保证 $p$ 之前至少加过一次（注意我们 $p$ 是第一个全局最小值出现的位置），于是我们需要凑出的数实际上是 $m - p\left(p - 1\right) / 2$。

---
我们从小到大扫 $p$，每次重新跑 DP 是不可接受的。

我们发现这个 DP 是容易支持撤销的。于是每次增量更新即可。

最终时间复杂度为 $\mathcal O\left(n + m \sqrt m\right)$。

## 代码
```cpp
// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  constexpr tp mod = 1000000007;
  tp n, m; bin >> n >> m;
  vector<tp> f(m + 1);
  f[0] = 1;
  auto add = [&](tp x) -> void { gor(i, x, m) f[i] = (f[i] + f[i - x]) % mod; };
  auto rem = [&](tp x) -> void { gor(i, m, x) f[i] = (f[i] - f[i - x]) % mod; };
  if (n <= m) add(n);
  for (tp i = 1; i < n && i * (i + 1) / 2 <= m; ++i) add(i * (i + 1) / 2);
  tp tar = 0;
  gor(i, 1, n) {
    if (i * (i - 1) / 2 <= m) tar += f[m - i * (i - 1) / 2];
    if ((n - i) * (n - i + 1) / 2 <= m) rem((n - i) * (n - i + 1) / 2);
    if (i * (i + 1) / 2 <= m) add(i * (i + 1) / 2);
  }
  bin << ((tar % mod) + mod) % mod << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

## 作者：ty_mxzhn (赞：6)

很好的数数题。

注意到问题相当于差分递增，因为是背包形式考虑如何刻画。

可以先想到每次选择一个前缀造一个差分 $-1$，但是这样你造出来的序列不对。

那我每次选择一个顶点，左边是每次选择一个前缀减少差分（但是也要 $+1$），右边选择一个后缀增加差分。还可以全局 $+1$。

有效物品数量只有 $\sqrt{m}$ 个。这个东西复杂度显然是单次 $m\sqrt{m}$ 的，总复杂度 $m^2\sqrt{m}$。过不去。

背包插入删除应该没人不会吧！每次移动顶点，插入删除 $O(1)$ 个物品，时间复杂度 $O(m\sqrt{m})$。

---

## 作者：sanaka87 (赞：6)

复习的时候发现我当时的做法和全世界都不一样。分享一下。

枚举最小值和它的个数，那么剩下来就是 $2$ 个子问题，设 $f_{i,j}$ 表示 $i$ 个数，和为 $j$ 的方案数。显然 $i$ 是 $\sqrt m$ 级别的，我们求出这个以后就可以通过前缀和优化一样的操作算出答案。

考虑如何求 $f_{i,j}$。发现条件等价于差分数组单调。问题变成：求一个序列 $\{a_i\}$，满足序列长度为 $n'$，$\sum (Len-i)a_i=m'$，单调递增，对于所有 $i$ 满足：$a_i\leq a_{i+1}$。其实就等价于求 $\sum i a_i=m''$。

使用拆分数的经典 dp：动态维护一个序列，支持两个操作：

- 在开头加入一个新的 $1$。

- 全局每一个数都加上 $1$。

这样转移方程变成了：

```cpp
	for (int i=1;i<MAXN;i++){
		for (int j=1;j<MAXM;j++){
			if (j>=i) f[i][j]=(f[i][j]+f[i-1][j-i])%ljc;
			if (j>=i*(i+1)/2) f[i][j]=(f[i][j]+f[i][j-i*(i+1)/2])%ljc;
		}
	}
```

这样这道题就做完了。细节比较多。

完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 1000000007
using namespace std;
#define gc getchar
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int n,m;
const int MAXN=450,MAXM=100001;
int f[MAXN][MAXM],g[MAXN][MAXM],h[MAXN][MAXM]; 
signed main(){
	f[0][0]=1;
	for (int i=1;i<MAXN;i++){
		for (int j=1;j<MAXM;j++){
			if (j>=i) f[i][j]=(f[i][j]+f[i-1][j-i])%ljc;
			if (j>=i*(i+1)/2) f[i][j]=(f[i][j]+f[i][j-i*(i+1)/2])%ljc;
		}
	}
	g[0][0]=1;
	for (int i=1;i<MAXN;i++){
		for (int j=0;j<MAXM;j++){
			g[i][j]=(g[i-1][j]+f[i][j])%ljc;
		}
	}
	n=read(),m=read();
	int sqr=sqrt(2*m+2)+1;
	for (int i=0;i<MAXN;i++){
		for (int j=0;j<MAXM;j++){
			h[i][j]=((j-n>=0?h[i][j-n]:0)+g[i][j])%ljc;
		}
	}
	ll _=0;
	for (int i=0;i<=min(n-1,sqr);i++){
		for (int j=0;j<=m;j++){
			_=(_+1ll*f[i][j]*h[min(sqr,n-i-1)][m-j]%ljc)%ljc;
		}
	}
	cout<<_;
	return 0;
}
```

---

## 作者：liyixin0514 (赞：4)

# [[AGC049D] Convex Sequence](https://www.luogu.com.cn/problem/AT_agc049_d)

[也许更好的阅读体验](https://www.cnblogs.com/liyixin0514/p/18607302)

## 题意

题目写得很清楚。

## 思路

> 省流
>
> 做原凸包的二阶导数 $\{c_i\}$，有 $\sum_{k=1}^n \frac{k(k+1)}{2} c_k=M$。
>
> 枚举凸包最低点 $p$，钦定 $p$ 一定是最低点最左边的那个点，将 $[1,p]$ 归入左部，将 $[p+1,n]$ 归入右部。因此左部需要填 $p-1$ 个数，其中 $c_{p-1}$ 为正数。右部需要填 $n-p$ 个数。所有 $c_i$ 非负。
>
> 答案取生成函数的 $[x^m],[x^{m-n}],\cdots$。

可以使用生成函数来做。

第二个条件就是 $a_i-a_{i-1} \le a_{i+1}-a_i$，即 $\{ a_i \}$ 是下凸壳。

下凸壳这个要求不好处理。

我们先考虑只有右下凸壳的情况，即斜率非负。

对原数列做差分数组 $\{ b_i \}$，得到 $\{ b_i \}$ 单调不减。

然而单调不减依然不好维护，对 $\{ b_i \}$ 再做差分数组 $\{c_i\} $，要求 $c_i$ 非负。

然而 $\sum c_i$ 是未知的，我们只知道 $\sum a_i = M$，考虑推出 $\sum f_i c_i = M$。

$$
\begin{aligned}
M&=\sum_{i=1}^n a_i\\
&=\sum_{i=1}^n \sum_{j=1}^i b_i\\
&=\sum_{j=1}^n (n-j+1) b_j\\
&=\sum_{j=1}^n (n-j+1) \sum_{k=1}^j c_k\\
&=\sum_{k=1}^n \frac{(n-k+1)(n-k+2)}{2} c_k
\end{aligned}
$$

换元 $k:=n-k+1$。

$$\sum_{k=1}^n \frac{k(k+1)}{2} c_k=M$$

容易发现 $c_k$ 非 $0$ 的 $k$ 最大到 $\sqrt{M}$。思考一下发现这是符合直觉的。而 $k>\sqrt{M}$ 的 $c_k=0$。

写出生成函数：

每个 $c_{k}$ 可以取值 $[0,inf)$。对指数的贡献就是 $x^{\frac{k(k+1)}{2}\times c_k}$

$$
[x^M] F(x) = \prod_{k=1}^{\min(n,\sqrt{M})} \frac{1}{1-x^{\frac{k(k+1)}{2}}}
$$

这玩意只关心 $M$ 项，而且是 $\sqrt{M}$ 个多项式相乘，考虑递推求解。

定义 $t:=\frac{k(k+1)}{2},F(x)_n := \prod_{k=1}^{n} \frac{1}{1-x^{t}}$。

$$
\begin{aligned}
F(x)_n& = \frac{1}{1-x^t} F(x)_{n-1}\\
F(x)_n (1-x^t) &= F(x)_{n-1}\\
\end{aligned}
$$

对于每一项系数 $f_{n-1,i}$ 有 $f_{n,i} - f_{n,i-t} = f_{n-1,i}$。

因此得到递推式子 $f_{n,i} = f_{n-1,i} + f_{n,i-t}$。

由于多项式指数为负的系数总是零，因此无需讨论指数为负的情况。

因此可是通过 $O(M)$ 的时间从 $F(x)_{n-1} \to F(x)_n$。

总时间复杂度 $O(M \sqrt{M})$。

对于凸壳斜率正负都存在的情况，我们枚举凸壳最低点 $p$，左右分开算。

$$
[x^M] \prod_{k=1}^{\min(a,\sqrt{M})} \frac{1}{1-x^{\frac{k(k+1)}{2}}} \prod_{k=1}^{\min(n-a,\sqrt{M})} \frac{1}{1-x^{\frac{k(k+1)}{2}}}
$$

本质不同的情况只有 $O(\sqrt{M})$ 种，而且每次 $p$ 向右移 $1$ 的时候，相当于式子乘上或者除以 $\frac{1}{1-x^{\frac{k(k+1)}{2}}}$，可以类似上面 $O(M)$ 递推求出新的多项式。

乘上 $\frac{1}{1-x^t}$：$f_i' = f_i + f_{i-t}'$。

除以 $\frac{1}{1-x^t}$：$f_i' = f_i - f_{i-t}$。

然后答案取 $x_M$ 的系数。

实现的时候发现不好做，因为一个序列可能拥有多个最低点 $p$，因此会算重。

我的做法是钦定 $p$ 一定是最低点最左边的那个点。将 $[1,p]$ 归入左部，将 $[p+1,n]$ 归入右部，因此左部需要填 $p-1$ 个数，其中 $c_{p-1}$ 非零。右部需要填 $n-p$ 个数，没有额外限制。

还有一个问题是如果要保证原凸壳的二阶导数非负，就不可以算上最低点位置的二阶导数。因此会造成凸壳整体上移或者下移，二阶导数不变的情况。那么我们可以枚举上移的量，答案加上 $[x^m],[x^{m-n}],\cdots$。

## code

注意实际上 $k$ 的上界为 $O(\sqrt{2M})$，因为有 $\iint c_k \le M$。大概是这么写的吧。

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace ababab {
    constexpr int N=1e5+7,mod=1e9+7;
    int add(int a,int b) { return a+b>=mod ? a+b-mod : a+b; }
    void _add(int &a,int b) { a=add(a,b); }
    int n,m;
    int f[N<<1],_f[N<<1];
    int lim;
    int laa,lab;
    int ans;
    void solvemul(int t) {
        memcpy(_f,f,sizeof(f));
        rep(i,0,m<<1) f[i]=add(_f[i],i-t>=0?f[i-t]:0);
    }
    void solvediv(int t) {
        memcpy(_f,f,sizeof(f));
        rep(i,0,m<<1) f[i]=add(_f[i],i-t>=0?mod-_f[i-t]:0);
    }
    void solvechange(int t) {
        memcpy(_f,f,sizeof(f));
        rep(i,0,m<<1) f[i]=i+t<=(m<<1)?f[i+t]:0;
    }
    void solvechange2(int t) {
        memcpy(_f,f,sizeof(f));
        rep(i,0,m<<1) f[i]=i-t>=0?add(_f[i-t],f[i-t]):0;
    }
    void main() {
        sf("%d%d",&n,&m);
        f[0]=1;
        lim=ceil(sqrt(m))*2;
        lab=lim;
        rep(i,1,lim) solvemul(i*(i+1)/2);
        rep(a,1,min(n,lim+1)) {
            int b=n-a;
            int _a=a-1, _b=min(b,lim);
            if(laa!=_a) {
                rep(k,laa+1,_a) {
                    solvechange((k-1)*k/2);
                    solvechange2(k*(k+1)/2);
                }
                laa=_a;
            } 
            if(lab!=_b) {
                rep(k,_b+1,lab) solvediv(k*(k+1)/2);
                lab=_b;
            }
            for(int j=m;j>=0;j-=n) _add(ans,f[j]);
        }
        pf("%d\n",ans);
    }
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
    ababab :: main();
}
```

---

## 作者：happybob (赞：1)

题意：

给定正整数 $n,m$，求有多少正整数序列 $a_1,a_2,\cdots,a_n$，满足 $\sum \limits_{i=1}^n a_i = m$，且对于所有 $1 \leq i < n$，都有 $2a_i \leq a_{i-1}+a_{i+1}$，答案对 $10^9+7$ 取模。

$1 \leq n, m\leq 10^5$，时限 $2$ 秒。

解法：

考虑先将式子移项，等价于 $a_{i+1}-a_i \geq a_i - a_{i-1}$，即差分数组单调不降。

差分数组单调不降的序列显然是一个凸的单谷序列。考虑枚举最靠左的最小值所在位置，要求左侧每个数大于 $a_i$，右侧每个数大于等于 $a_i$，总和为 $m$ 的方案数，并不容易直接计算。常见技巧是考虑双射。将序列对应到一个唯一的生成方式，若生成方式和序列形成双射，对生成方式计数即可。考虑凸的本质。现在枚举的是 $a_i$。则我们必然可以发现，通过以下步骤可以唯一生成一个符合条件的序列：

1. 初始时，选择 $x \geq 0$ 且 $nx \leq m$，令所有 $a_i = x$。
2. 区间 $[1,i-1]$ 整体加一。
3. 进行若干次操作，操作之间无序，每次选择如下之一：
   - 选择 $j<i$，然后序列下标在范围 $[1,j]$ 内的数逆序加 $1,2,\cdots$ 的等差数列。
   - 选择 $j>i$，然后序列下标在范围 $[j,n]$ 内的数正序加 $1,2,\cdots$ 的等差数列。

容易发现操作可以唯一生成某个合法序列，而每个合法序列都通过差分唯一对应一个合法操作序列。现在问题转化为对合法的无序操作序列计数。显然，无序操作序列只和每种操作进行次数有关，操作长度为 $x$ 的区间只需要考虑总和 $\dfrac{x(x+1)}{2}$。在枚举 $i$ 的时候，$i \rightarrow i+1$ 只会影响两个区间，加入一个新区间和删除一个旧区间。维护带删背包。由于 $\dfrac{x(x+1)}{2} \leq m$，所以区间数量是 $O(\sqrt m)$ 级别的，总复杂度 $O(n \sqrt m)$，可以通过。

[Submission Link.](https://atcoder.jp/contests/agc049/submissions/60605080)

---

## 作者：ivyjiao (赞：0)

可撤销完全背包问题。

### 性质 $1$：

考虑什么数列能满足这个性质：

我们发现，如果出现一种情况，使得 $a_i>a_{i-1}$ 且 $a_i>a_{i-1}$，那么必然不符合性质。

也就是说，该数列不能有峰值，那么它只能是一个单谷数列。

### 性质 $2$：

容易发现，谷值在哪里并不重要。

那我们可以考虑枚举谷值出现的地方。

### 性质 $3$：

我们考虑一个特殊情况：假如谷值出现在 $1$，即函数单调不降。

那怎么加值才能保证构造出单调不降数列呢？

1. 令 $a$ 中元素全都加 $1$。
2. 选择一个 $i$，令 $j\in [i,n]$ 中的 $a_j$ 增加 $j-i$。

我们有任意多个值为 $n,1,3,6,10\cdots$（前者 $n$ 是操作 $1$，后者不能大于 $m$）的数，求和为 $m$ 有多少种方案？

转化为完全背包问题。

### 没有性质 $3$ 了，怎么办？

设当前谷点为 $c$。

2. 选择一个 $i(i\geq c)$，令 $j\in [i,n]$ 中的 $a_j$ 增加 $j-i$。
3. 选择一个 $i(i\leq c)$，令 $j\in [1,i]$ 中的 $a_j$ 增加 $i-j$。

发现二者实质相同，所以不对其进行修改。

我们发现至少要进行一次操作 $3$，所以我们在统计答案时加的是 $dp_{m-a_{i-1}}$。

该 $dp$ 是具有可撤销性的，我们在枚举每个峰值之后把 $n-i$ 这一层撤销掉就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1,p=1e9+7;
int n,m,a[N],dp[N],k,ans;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        a[i]=a[i-1]+i;
        if(a[i]>m){
            k=i-1;
            break;
        }
    }
    for(int i=0;i<=m;i+=n) dp[i]=1;
    for(int i=1;i<=min(k,n-1);i++) for(int j=a[i];j<=m;j++) (dp[j]+=dp[j-a[i]])%=p;
    for(int i=1;i<=n;i++){
        if(i-1<=k){
            (ans+=dp[m-a[i-1]])%=p;
            if(i<=k) for(int j=a[i];j<=m;j++) (dp[j]+=dp[j-a[i]])%=p;
        }
        if(n-i<=k) for(int j=m;j>=a[n-i];j--) (dp[j]-=dp[j-a[n-i]])%=p;
    }
    cout<<(ans+p)%p;
}
```

---

## 作者：int08 (赞：0)

## 前言
独立想出的做法，应该是题解区 sanaka87 的做法，稍微细讲一下。

"[_Am I overreacting_](https://music.163.com/song?id=2029506993&uct2=U2FsdGVkX19RV95y82pug30YX1h1Wd6s3cv6rRel3uk=)"
# Solution
首先题目第二条条件就是说这个序列是下凸的，换句话说差分数组应该是单调递增的。

尝试依此设计一个 DP，但是 $n,m$ 都是 $10^5$ 级别根本没法玩。

发现一个重要的事情，差分数组两端的非零段长度不会超过 $O(\sqrt m)$，也就是中间绝大部分差分数组为 $0$，是序列最小值，是较为平凡的。

我们考虑只对差分序列大于 $0$ 的段落进行 DP，发现这个 DP 数组可以代表序列的前边、后边，这样最后的答案就是用某种方法把两边拼起来。

### 设计 DP
由于差分数组单调递增，考虑经典的分拆数 DP 转移形式（设 $dp_{i,j}$ 表示长为 $i$ 的序列和为 $j$ 的方案数）：

1. 差分序列最前面加一个 $1$。
2. 整个差分序列加 $1$。

容易发现这两种方式可以凑出所有单调递增序列，它们对原序列总和的贡献分别为 $i+1,\frac{i(i+1)}{2}$。

于是直接转移即可。

### 合并

发现中间的平凡段落是可以影响总和的，这个很恶心，我们先假设序列最小值为 $0$。

此时 $dp_{il,jl},dp_{ir,jr}$ 两边能乘起来贡献答案的条件就是：$il+ir+1\le n,jl+jr=m$。

这个式子还是很好做的，我们对 $i$ 这一维做前缀和即可 $O(m\sqrt m)$ 求出。

问题是最小值不一定为 $0$，假设为 $x$，我们可以考虑对整个序列减去 $x$，跟前面的情况就一样了，换句话说，我们要对 $jl+jr=m,m-n,m-2n,m-3n,\dots$ 都求出答案，如果每次都暴力求，就炸胡了。

但其实不需要每次暴力求啊，我们枚举 $jl$，满足条件的 $jr$ 是 $m-jl,m-jl-n,m-jl-2n,m-jl-3n,\dots$，这是模 $n$ 同余的前缀和，改写一下前缀和数组的式子即可。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,i,j,dp[450][114514],sum[450][114514],ans,tong[114514];
#define mod 1000000007
signed main()
{
	cin>>n>>m;
	dp[0][0]=sum[0][0]=1;
	for(i=0;i<=446;i++)
		for(j=0;j<=100000;j++) if(dp[i][j])
		{
			if(j+i+1<=100000) (dp[i+1][j+i+1]+=dp[i][j])%=mod;
			if(i>0&&i*(i+1)/2+j<=100000) (dp[i][i*(i+1)/2+j]+=dp[i][j])%=mod;
		}
	for(i=1;i<=446;i++)
		for(j=0;j<=100000;j++) sum[i][j]=(sum[i-1][j]+dp[i][j])%mod;
	for(i=0;i<=min(n-1,446ll);i++)
	{
		int ri=min(n-1-i,446ll);
		memset(tong,0,sizeof tong);
		for(j=0;j<=m;j++)
		{
			(tong[j%n]+=dp[i][j])%=mod,(ans+=tong[j%n]*sum[ri][m-j])%=mod;
		}
	}
	cout<<ans;	
}
```
# The End.

---

## 作者：2008verser (赞：0)

来点不用撤销背包的做法。原理是类似的。

还是考虑这个凸，相当于是不断往前缀加 $i,\ldots,2,1$ 和往后缀加 $1,2,\ldots,i$。还有一种整体加 $1$，即总和加 $n$。

这个时候脑子里已经可以有一种 dp 了，比如把 ${\color{red}n},1,3,6,\ldots$ 视作 $O(\sqrt m)$ 个物品，重量总和为 $m$ 的某种方案数之类的。

约定长度指的是一次前/后缀加的区间长度 $x$，长为 $x$ 物品的重量是 $\frac12x(x+1)$。

对一个凸序列在它最左的最小值计数，记下标为 $i$。

先不考虑整体加的 $\color{red}n$，左侧的方案数就是长度小于等于 $i-1$ 且 $i-1$ 必选的背包。枚举左侧的重量总和是 $j$。

则右侧就是长度小于等于 $n-i$，重量总和 $m-j$ 的背包。

如果左右背包都有重量为 $\color{red}n$ 的物品，则合并起来会重复。于是只在右边算上即可。

即设 $f_{i,j}$ 表示长度小于等于 $i$ 的物品重量总和为 $j$ 的方案数。$g$ 则是在 $f$ 里加入长为 $n$ 的物品。答案即

$$
\sum_{i=1}^n\sum_{j=0}^m(f_{i-1,j}-f_{i-2,j})g_{n-i,m-j}
$$

长度这一维枚举到 $O(\sqrt m)$ 就可以结束了。时间复杂度 $O(m\sqrt m)$。

[AC 链接](https://atcoder.jp/contests/agc049/submissions/61091118)

---

## 作者：w9095 (赞：0)

[AT_agc049_d [AGC049D] Convex Sequence](https://www.luogu.com.cn/problem/AT_agc049_d)

模拟赛原题，纪念一下。补充了题解区做法的正确性证明。

限制 $1$ 不好满足，先不管它。限制 $2$ 移项可得 $a_{i}-a_{i-1}\le a_{i+1}-a_{i}$，即差分非严格单调递增，满足要求的序列为一个单谷序列。

我们考虑枚举最左侧的最小值的出现位置，先考虑在最左端的情况。

我们钦定序列最小值为 $0$，可以通过增加非最左侧的最小值的出现位置的元素的值来构造序列。具体的，我们每次选择一个区间 $[i,n](i\gt 1)$，把这个区间的数从左到右依次增加 $1,2\dots n-i+1$，这样增量区间的差分不减，原序列的差分也非严格单调递增，构造出来的序列显然满足限制 $2$。

接下来就是要证明所有满足要求的序列都可以由上述构造方式得到。这是易证的，钦定最小值之后，每一个合法的区间对应一个唯一的非严格单调递增的差分数组。注意到增量区间的差分实际上都是 $1$，每次操作后差分区间每个数加 $1$。我们从右往左一位一位操作，每次对于位置 $i$ 操作 $[i,n]$ 直到满足差分数组的限制，注意到这种情况下构造不出来的条件为存在递减的差分，由限制 $2$ 有差分非严格单调递增，矛盾，所以不会存在这种情况。

考虑到这种总和 $\le m$ 的段只会有 $O(\sqrt{m})$ 个，我们直接把这些段预处理出来做容量为 $m$ 的完全背包。这样，就满足了限制 $1$。

注意到最小值可以不为 $0$，但每次最小值的增加伴随着 $n$ 个元素一起增加，所以做背包的时候预处理出这种状态记为可行。

接下来考虑最左侧的最小值向右滑动。假设滑动前为 $i$，滑动后相当于背包里失去了 $[i+1,n]$ 这个元素，增加 $[1,i-1]$ 这个元素。注意到 $[1,i-1]$ 的贡献与后缀 $[n-i+2,n]$ 相同，不需要额外处理。由于统计方案数的背包是支持删除的，可以直接维护。

最后，再统计使最左侧的最小值向右滑动需要的操作的贡献即可，这同样是一个前缀，同上维护。

于是，我们得到了一个时间复杂度 $O(m\sqrt{m})$ 的算法，空间复杂度 $O(m)$ 的优秀算法。


```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,k=0,s[200000],f[200000],ans=0;
const long long mod=1e9+7;
int main()
{
	scanf("%lld%lld",&n,&m);
	while(s[k]<=m)k++,s[k]=s[k-1]+k;
	k--;
	for(int i=0;i<=m;i+=n)f[i]=1;
	for(int i=1;i<=min(k,n-1);i++)
	    for(int j=s[i];j<=m;j++)f[j]=(f[j]+f[j-s[i]])%mod;
	for(int i=1;i<=n;i++)
	    {
	    	if(i-1>k)break;
	    	ans=(ans+f[m-s[i-1]])%mod;
	    	for(int j=s[i];j<=m;j++)f[j]=(f[j]+f[j-s[i]])%mod;
	    	if(n-i<=k)for(int j=m;j>=s[n-i];j--)f[j]=(f[j]-f[j-s[n-i]])%mod;
		}
	printf("%lld\n",(ans%mod+mod)%mod);
	return 0;
} 
```

---

