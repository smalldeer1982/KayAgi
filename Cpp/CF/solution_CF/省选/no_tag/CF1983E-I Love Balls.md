# I Love Balls

## 题目描述

Alice and Bob are playing a game. There are $ n $ balls, out of which $ k $ are special. Each ball has a value associated with it.

The players play turn by turn. In each turn, the player randomly picks a ball and adds the value of the ball to their score, which is $ 0 $ at the beginning of the game. The selected ball is removed from the game. If the ball was special, the same player takes the next turn if at least one ball is remaining. If the ball picked was not special, the next player plays their turn.

They play this game until no balls are remaining in the game. Alice plays first.

Find the expected score that both the players have at the end of the game modulo $ 10^9+7 $ .

Formally, let $ M = 10^9+7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, Alice's expected score is $ 45 $ , and Bob's is $ 30 $ at the end of the game.

## 样例 #1

### 输入

```
1
5 2
10 20 5 15 25```

### 输出

```
45 30```

## 样例 #2

### 输入

```
5
1 1
732507
2 2
5817860 5398510
5 1
2122894 4951549 2750585 7821535 3214167
8 4
1405323 5069867 6883092 6972029 328406 2478975 7628890 9973340
4 2
9662050 3566134 3996473 9872255```

### 输出

```
732507 0
11216370 0
810642660 210218077
722402997 318336932
349086489 678010430```

## 样例 #3

### 输入

```
5
3 3
1095611 8219204 7773462
2 1
8176490 2774103
3 1
9178636 5138057 3367761
12 9
7597698 6843019 2298534 1522386 4969588 1340345 3967362 9152890 6689668 9986080 4745473 7407325
10 5
6986368 2397882 5804127 6980694 3740836 3215836 5195724 3179261 4136769 4544231```

### 输出

```
17088277 0
6862348 4088245
677038671 340645790
36949997 29570371
725118051 321063684```

# 题解

## 作者：lfxxx (赞：23)

考虑将普通球排成一排，那么两人一定是交替的选择，此时 Alice 选出的普通球数量确定，用选的比例乘上普通球权值之和可以得到选出的普通球贡献期望。

将特殊球看成板子，插入普通球的空之中，因为首尾都可以放板子，所以一共有 $n-k+1$ 个空，然后每个空放的板子属于 Alice 或者 Bob 是确定的，算出 Alice 的空所占比例，再乘上特殊球权值之和即可算出特殊球贡献期望。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
int n,k;
const int maxn = 4e5+114;
int v[maxn],sumA,sumB;
int chA,chB;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
signed main(){
    int t;
    cin>>t;
    while(t--){
        sumA=sumB=chA=chB=0;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>v[i];
            if(i<=k) sumA=(sumA+v[i])%mod;
            else sumB=(sumB+v[i])%mod;
        }
        chA=ceil((n-k+1)*1.0/2);
        chB=ceil((n-k+1)/2);
        int ans=(int)ceil((n-k)*1.0/2)*qpow(n-k,mod-2)%mod*sumB%mod+chA*qpow(chA+chB,mod-2)%mod*sumA%mod;
        ans%=mod;
        cout<<ans<<' '<<(sumA+sumB+mod-ans)%mod<<'\n';
    }
    return 0;
}
```

---

## 作者：NaCly_Fish (赞：17)

我不会大眼找规律，我只会大力推式子。  
update：原本的做法太麻烦了，更新了一下。

首先有一个很经典的转化：取球的过程可以看作是 $n$ **个球提前排列好，然后依次去取**。这样显然是不影响题意的。  
然后我们还有个朴素的想法：取到每个普通球的概率都是相同的（对于特殊球也是一样）。

于是先手的答案可以表示为：
$$p_1S_1+p_2S_2$$
其中 $p_1$ 为先手取到 $1$ 号球的概率，$S_1$ 为所有特殊球的权值和；  
$p_2$ 为先手取到 $k+1$ 号球的概率，$S_2$ 为所有普通球的权值和。

对于先手来说，一个球能被取到，**当且仅当**「其前面特殊球数量的奇偶性」不等于「其位置的奇偶性」（位置从 $1$ 开始）。

于是我们可以列出式子：

$$n!p_1=\sum_{i=1}^n(i-1)!(n-i)!\sum_{j=0}^{i-1}\binom{k-1}{j}\binom{n-k}{i-1-j}[2 \mid (i-j+1)]$$
$$n!p_2=\sum_{i=1}^n(i-1)!(n-i)!\sum_{j=0}^{i-1}\binom{k}{j}\binom{n-k-1}{i-1-j}[2 \mid (i-j+1)]$$
然后考虑优化，对于 $p_1$ 来说，内层和式可以写为

$$\frac 12\sum_{j=0}^{i-1}\binom{k-1}{j}\binom{n-k}{i-1-j}(1+(-1)^{i-j+1})$$
$$=\frac 12\left( \binom{n-1}{i-1}+(-1)^{i+1}\color{red}\sum_{j=0}^{i-1}\binom{k-1}{j}\binom{n-k}{i-1-j}(-1)^j\color{clear}\right)$$
考虑列出红色部分的生成函数：
$$\begin{aligned}F_1(x)&=\sum_{i=1}^\infty x^i \sum_{j=0}^{i-1}\binom{k-1}{j}\binom{n-k}{i-1-j}(-1)^j \\ &=\sum_{j=0}^\infty \binom{k-1}{j}(-1)^j\sum_{i=j+1}^\infty\binom{n-k}{i-1-j}x^i \\ &= \sum_{j=0}^\infty \binom{k-1}{j}(-1)^j (1+x)^{n-k}x^{j+1} \\ &=x(1+x)^{n-k}(1-x)^{k-1}\end{aligned}$$
其显然 D-Finite，系数可以整式递推计算。同样对于 $p_2$ 的内层和式为：
$$\frac 12\left(\binom{n-1}{i-1}+(-1)^{i+1}\sum_{j=0}^{i-1}\binom kj\binom{n-k-1}{i-1-j}(-1)^j \right)$$
类似地也能得到：
$$F_2(x)=x(1+x)^{n-k-1}(1-x)^k$$
[参考代码](https://www.luogu.com.cn/paste/8p1nw5la)
****
有一个疑点，就是如何获取 $p_1$ 的封闭形式。实际上
$$\begin{aligned}n!p_1&=\sum_{i=1}^n(i-1)!(n-i)!\sum_{j=0}^{i-1}\binom{k-1}{i-1-j}\binom{n-k}{j}[2\mid j] \\ &=\sum_{j=0}^{n-k}[2\mid j]\sum_{i=j+1}^n \frac{(i-1)!(n-i)!(k-1)!(n-k)!}{(i-1-j)!(k-i+j)!j!(n-k-j)!} \\&=(k-1)!(n-k)!\sum_{j=0}^{n-k}[2\mid j]\sum_{i=j+1}^n\binom{i-1}{j}\binom{n-i}{n-k-j}\\ &=(k-1)!(n-k)!\sum_{j=0}^{n-k}[2\mid j]\binom{n}{n-k+1}\\&= \frac{n!}{n-k+1}\left\lfloor \frac{n-k+2}{2}\right\rfloor\end{aligned}$$
对于 $p_2$ 也是一样的推导方法。

可以看到，我们仅仅是把二项式系数拆开，进行了简单的变换，后续的推导就变得很简单了。

---

## 作者：Ether13 (赞：10)

题意：有 $n$ 个球，其中 $k$ 个是特殊球。每个球都有一个权值。

在每个回合中，当前的玩家随机挑选一个球，并将该球的价值加到自己的分数中，游戏开始时的分数为 $0$ ，被选中的球将从游戏中移除。如果选中的球是特殊球，且至少还有一个球，则由同一名玩家进行下一轮游戏。如果选中的球不是特殊球，则由下一位玩家进行下一轮游戏。没有球时游戏结束。

Alice 先手，求游戏结束时双方的期望得分，对 $10^9+7$ 取模。

做法：

先不考虑两名玩家，若只有一个玩家拿球，显然拿出的球是一个排列。

考虑每次换人都是非特殊球，则根据非特殊球将排列划分为 $n-k+1$ 段，其中前 $n-k$ 段每段最后都是一个非特殊球。那么这些非特殊球也是一个排列。注意到 $n-k$ 段中偶数位对 Bob 有贡献，奇数位对 Alice 有贡献。那么对于一个非特殊球，其对 Alice 有贡献的概率是 $\frac{\lceil\frac{n-k}{2}\rceil}{n-k}$ ，对 Bob 有贡献的概率是 $\frac{\lfloor\frac{n-k}{2}\rfloor}{n-k}$

对于特殊球，其有 $n-k+1$ 个位置可以放，则仍然是偶数位对 Bob 有贡献，奇数位对 Alice 有贡献。对 Alice 造成贡献的概率是 $\frac{\lceil\frac{n-k+1}{2}\rceil}{n-k+1}$，对 Bob 造成贡献的概率是 $\frac{\lfloor\frac{n-k+1}{2}\rfloor}{n-k+1}$。

那么期望直接用权值乘概率算即可。

核心代码如下：

```cpp
ll ea=0,eb=0,invn=qpow(n-k,MOD-2),invn1=qpow(n-k+1,MOD-2);
rep(i,k+1,n){
	ea=(ea+v[i]*((n-k+1)/2)%MOD*invn%MOD)%MOD;
	eb=(eb+v[i]*((n-k)/2)%MOD*invn%MOD)%MOD;
}
n=n-k;
rep(i,1,k){
	ea=(ea+v[i]*(n/2+1)%MOD*invn1%MOD)%MOD;
	eb=(eb+v[i]*((n+1)/2)%MOD*invn1%MOD)%MOD;
}
printf("%lld %lld\n",ea,eb);
```

---

## 作者：TTpandaS (赞：7)

分别考虑每个球的贡献。先将球分为普通球和特殊球两种情况考虑。

普通球一共 $n-k$ 个，那么在奇数位上的将由先手取走，概率为 $\dfrac{ \left \lceil \dfrac{n-k}{2} \right \rceil }{n-k}$，在偶数位由后手取走，概率为 $\dfrac{ \left \lfloor \dfrac{n-k}{2} \right \rfloor }{n-k}$。

特殊球一共 $k$ 个，需要将普通求分隔开，一共有 $n-k+1$ 个分隔点。同样的，在奇数位上的将由先手取走，概率为 $\dfrac{ \left \lceil \dfrac{n-k+1}{2} \right \rceil }{n-k+1}$，在偶数位由后手取走，概率为 $\dfrac{ \left \lfloor \dfrac{n-k+1}{2} \right \rfloor }{n-k+1}$。

期望就是概率乘上对应的结果就行了。

---

## 作者：Lavaloon (赞：4)

首先，双方的期望得分之和应为所有数的和。

证明如下：

- 对每一个样本点（可能的合法情况）来说，Alice 与 Bob 的得分之和一定为所有数的和。根据期望的定义式，两边都除以总方案数，因为除数是一样的，所以这个结论还是成立的。

于是我们直接来算 Alice 的答案。

这就是在说：把所有球随便排，**在每个一般球后面分段**，**奇数段** 和的期望。

比如下面就是一种方案，红色的是 Alice 的球，蓝色的是 Bob 的球，$\text{X}$ 是一般球，反之则是特殊球：

$\text{\color{red}{OOX}\color{blue}{OX}\color{red}{OOOX}\color{blue}{OO}}$

**注意结尾未必要有一般球，也可能是直接选完了，结束游戏。**

每一段由可能存在的一个一般球和若干个（可能为零） 个特殊球组成，这引导我们去拆贡献——奇数段和的期望，就是一般球贡献的期望与特殊球贡献的期望之和。

- 一个一般球会如何对答案造成贡献？无非就是放在了一个有一般球的奇数段的结尾。有一般球的段有 $n-k$ 个，有一般球的奇数段就是 $\lfloor  \dfrac{n-k+1}{2} \rfloor$ 个。于是一个一般球给 Alice 贡献的概率就是 $\dfrac{\lfloor  \dfrac{n-k+1}{2} \rfloor}{n-k}$。由期望的定义式，这一部分的贡献就是  $S_1\cdot\dfrac{\lfloor  \dfrac{n-k+1}{2} \rfloor}{n-k}$，$S_1$ 是一般球价值的和。
- 一个特殊球会如何对答案造成贡献？无非就是放在了一个奇数段的里面。这样的段有 $n-k+1$ 个（注意结尾未必要有一般球，这也算一段——即使它可能是空的），Alice 所拥有的这样的段就是 $\lfloor  \dfrac{n-k+2}{2} \rfloor$ 个。于是一个特殊球给 Alice 贡献的概率就是 $\dfrac{\lfloor  \dfrac{n-k+2}{2} \rfloor}{n-k+1}$。由期望的定义式，这一部分的贡献就是  $S_2\cdot\dfrac{\lfloor  \dfrac{n-k+2}{2} \rfloor}{n-k+1}$，$S_2$ 是特殊球价值的和。

由期望的定义，Alice 的答案就应该是两部分的和——
$$
S_1\cdot\dfrac{\lfloor  \dfrac{n-k+1}{2} \rfloor}{n-k}+S_2\cdot\dfrac{\lfloor  \dfrac{n-k+2}{2} \rfloor}{n-k+1}
$$
至此本题得到解决，复杂度 $\mathcal{O}(n+\log p)$，代码非常好写。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<unordered_map>
#include<vector>
#include<bitset>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<random>
#include<numeric>
#include<assert.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define lc (x<<1)
#define rc (x<<1|1)
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
#define cout (cerr<<">> ",cout)
const int Mx=500005,p=1e9+7;
int read(){
	char ch=getchar();
	int Alice=0,Aya=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') Aya=-Aya;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		Alice=(Alice<<3)+(Alice<<1)+(ch^48),ch=getchar();
	return (Aya==1?Alice:-Alice);
}
int n,k;
int a[Mx];
int Inv(int bas){
	int res=1,ex=p-2;
	while(ex){
		if(ex&1) res=res*bas%p;
		bas=bas*bas%p,ex>>=1;
	}
	return res;
}
int f[Mx];
void Solve(){
	n=read(),k=read();
	int s=0,t=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(i>k) s+=a[i];
		else t+=a[i];
	}
	s%=p,t%=p;
	int normal=(n-k+1)/2,;
	int ans=s*Inv(n-k)%p*normal%p;
	int d=(n-k+1+1)/2;
	int cnt=t*Inv(n-k+1)%p*d%p;
	ans=(ans+cnt%p)%p;
	int sna=(s+t-ans+p)%p;
	cout<<ans<<" "<<sna<<endl;
}
signed main(){
	int T=read();
	while(T--) Solve();
	return 0;
}

```

---

## 作者：MatrixGroup (赞：3)

## 题意

有 $n$ 个球，其中 $k$ 个是特殊的，每个球有价值。每次有人随机拿一个没拿过的球，如果是特殊的就继续拿，否则让另一个人拿。求先手和后手拿到所有球价值和的期望。

$\sum n\le 4\times10^5$

## 题解

只需要算先手拿到的期望，后手用总和减即可。首先特殊球的地位等同，非特殊球也是。不妨设所有特殊球的价值均为 $A$，非特殊球的价值均为 $B$。显然，一个球算到先手当且仅当它前面的非特殊球个数为偶数。枚举球的位置和其前面的非特殊球个数则有答案为

$$
\begin{array}{rl}
&\displaystyle A\sum_{i=1}^n\sum_{j=0}^{n-k}\dfrac{\binom{i-1}{j}\binom{n-i}{n-k-j}}{\binom{n}{k}}[j\equiv0\pmod2]+B\sum_{i=1}^n\sum_{j=0}^{n-k-1}\dfrac{\binom{i-1}{j}\binom{n-i}{n-k-j-1}}{\binom{n}{k}}[j\equiv0\pmod2]\\
=&\displaystyle \dfrac{A}{\binom nk}\sum_{j=0}^{n-k}[j\equiv0\pmod2]\sum_{i=1}^n\dbinom{i-1}{j}\dbinom{n-i}{n-k-j}+\dfrac{B}{\binom nk}\sum_{j=0}^{n-k-1}[j\equiv0\pmod2]\sum_{i=1}^n\dbinom{i-1}{j}\dbinom{n-i}{n-k-j-1}\\
=&\displaystyle \dfrac{A}{\binom nk}\sum_{j=0}^{n-k}[j\equiv0\pmod2]\dbinom{n}{n-k+1}+\dfrac{B}{\binom nk}\sum_{j=0}^{n-k-1}[j\equiv0\pmod2]\dbinom{n}{n-k}\\
=&\displaystyle \dfrac{kA}{n-k+1}\left\lfloor\dfrac{n-k+2}{2}\right\rfloor+\displaystyle B\left\lfloor\dfrac{n-k+1}{2}\right\rfloor
\end{array}
$$

---

## 作者：DrAlfred (赞：2)

摘要：数学，概率，期望

[传送门：https://www.luogu.com.cn/problem/CF1983E](https://www.luogu.com.cn/problem/CF1983E)

## 题意

Alice 和 Bob 在玩游戏。他们面前有 $n$ 个球，第 $i$ 个球的价值为 $v_i$，且前 $k$ 个球为“特殊球”，Alice 为先手。每一轮，Alice 或 Bob 会随机从剩余的球中选取一个球并把它取出，获得它的价值。如果这个球为特殊球，则下一轮的玩家不变，否则下一轮的玩家改变。问 Alice 和 Bob 各自得到的价值的期望对 $10^9 + 7$ 取模的值。

## 分析思路

首先我们考虑 Alice 和 Bob 拿球的序列，一定如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jmkd4qpl.png)

我们记普通球的个数为 $m$。记特殊球的价值和为 $s_s$，普通球的价值和为 $s_n$。

我们先计算 Alice 获得的价值的期望。首先考虑普通球。因为 Alice 为先手，我们可以发现在 $m$ 个普通球中，Alice 会拿走 $a = \lceil \frac{m}{2} \rceil$ 个，而 Bob 会拿走 $b = \lfloor \frac{m}{2} \rfloor$ 个。所以对于每个普通球 $i$，Alice 拿走的期望为 $v_i \times \frac{a}{a + b}$。

然后我们再来考虑特殊球。注意到特殊球可能存在的位置即为由普通球构成的 $m + 1$ 个连续段，且每个特殊球插入这些连续段可以看作是独立时间。在 $m + 1$ 个连续段中，会被 Alice 拿走的有 $c = \lceil \frac{m + 1}{2} \rceil$ 个，会被 Bob 拿走的有 $d = \lfloor \frac{m + 1}{2} \rfloor$ 个。所以对于每个特殊球 $i$，Alice 拿走的期望为 $v_i \times \frac{c}{c + d}$。

最后将两部分累加即可。Bob 拿走的期望等于总和减去 Alice 拿走的期望。时间复杂度 $O\left(n\right)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <int mod>
inline int64_t down(int64_t x) { return x >= mod ? x - mod : x; }
template <int mod>
struct ModInt {
    int64_t x;
    ModInt() = default;
    ModInt(int64_t x) : x((x % mod + mod) % mod) {}
    friend istream &operator>>(istream &in, ModInt &a) { return in >> a.x; }
    friend ostream &operator<<(ostream &out, ModInt a) { return out << a.x; }
    friend ModInt operator+(ModInt a, ModInt b) { return down<mod>(a.x + b.x); }
    friend ModInt operator-(ModInt a, ModInt b) { return down<mod>(a.x - b.x + mod); }
    friend ModInt operator*(ModInt a, ModInt b) { return (__int128)a.x * b.x % mod; }
    friend ModInt operator/(ModInt a, ModInt b) { return a * ~b; }
    friend ModInt operator^(ModInt a, long long b) {
        ModInt ans = 1;
        for (; b; b >>= 1, a *= a)
            if (b & 1) ans *= a;
        return ans;
    }
    friend ModInt operator~(ModInt a) { return a ^ (mod - 2); }
    friend ModInt operator-(ModInt a) { return down<mod>(mod - a.x); }
    friend ModInt &operator+=(ModInt &a, ModInt b) { return a = a + b; }
    friend ModInt &operator-=(ModInt &a, ModInt b) { return a = a - b; }
    friend ModInt &operator*=(ModInt &a, ModInt b) { return a = a * b; }
    friend ModInt &operator/=(ModInt &a, ModInt b) { return a = a / b; }
    friend ModInt &operator^=(ModInt &a, long long b) { return a = a ^ b; }
    friend ModInt &operator++(ModInt &a) { return a += 1; }
    friend ModInt operator++(ModInt &a, int) {
        ModInt x = a;
        a += 1;
        return x;
    }
    friend ModInt &operator--(ModInt &a) { return a -= 1; }
    friend ModInt operator--(ModInt &a, int) {
        ModInt x = a;
        a -= 1;
        return x;
    }
    friend bool operator==(ModInt a, ModInt b) { return a.x == b.x; }
    friend bool operator!=(ModInt a, ModInt b) { return !(a == b); }
};
using mint = ModInt<1000000007>;
inline void solve(void) {
    int n, k;
    cin >> n >> k;
    const int ns = n - k; // non_special count.
    std::vector<mint> v(n);
    for (auto &x : v) cin >> x;
    mint spec = accumulate(v.begin(), v.begin() + k, mint(0));   // ss
    mint non_spec = accumulate(v.begin() + k, v.end(), mint(0)); // sn
    mint spec_frac = mint(ns / 2 + 1) / (ns + 1);
    mint non_spec_frac = mint((ns + 1) / 2) / ns;
    mint alice = spec_frac * spec + non_spec_frac * non_spec;
    cout << alice << ' ' << spec + non_spec - alice << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    int t = 1;
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：不知名用户 (赞：1)

被 *2300 骗了，知道做法后发现很水。

### 题意

有 $n$ 个球，$k$ 个是特殊的，每个球有权值。两人轮流拿球，每轮随机剩余的球中选取一个球并把它取出。如果这个球为特殊球，则下一轮的玩家不变，否则下一轮的玩家改变。问先后手拿到的球的权值和的期望。

### 做法

显然我们只需要关心每个球先手取到的概率，概率乘上权值就是期望，先后手期望和为所有球的权值和。易知取到特殊球的概率都是一样的，取到非特殊球的概率也一样。

#### 我的思路

如果想直接看具体做法，请往下翻。

于是考虑对概率 DP。$f_{n,k},g_{n,k}$ 表示有 $n$ 个球，$k$ 个是特殊的，取到特殊球/非特殊球取到的概率。

转移：如果选到这个球后面就不用管了，再分取到特殊或非特殊这两种情况。非特殊要转换人所以概率 $p\to 1-p$。有转移方程：

$$
f_{n,k}=\frac1n+\frac{k-1}nf_{n-1,k-1}+\frac{n-k}n(1-f_{n-1,k})(0<k\le n)\\
g_{n,k}=\frac1n+\frac{k}nf_{n-1,k-1}+\frac{n-k-1}n(1-f_{n-1,k})(0\le k<n)
$$

打表代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
using lf = double;
const int N = 1010;
lf f[N][N], g[N][N];

int main()
{
	int n = 10, i, j;
	for(i=1;i<=n;i++) for(j=0;j<=i;j++)
	{
		if(j) f[i][j] = 1.0 / i + 1.0 * (j - 1) / i * f[i-1][j-1] + 1.0 * (i - j) / i * (1.0 - f[i-1][j]);
		if(j<i) g[i][j] = 1.0 / i + 1.0 * j / i * g[i-1][j-1] + 1.0 * (i - j - 1) / i * (1.0 - g[i-1][j]);
	}
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) printf("%.4lf%c", f[i][j], " \n"[j==n]);
	printf("\n");
	for(i=1;i<=n;i++) for(j=0;j<=n;j++) printf("%.4lf%c", g[i][j], " \n"[j==n]);
	return 0;
}
```

打表发现对角线上的数完全一样，即 $f(n,k)=f(n-1,k-1)$，删掉一个特殊球不影响概率！且 $f,g$ 可以通过平移实现重合！

#### 具体做法

发现删掉特殊球不影响选到某个球概率！（如果是选特殊球就删除了这个球以外的特殊球）刚刚打表就发现了这个性质。

证明：考虑最终操作序列，删掉选特殊球的操作是不影响先后手操作的，且选到某个球的概率就是这个球在所以操作序列中的出现频率。

我们现在只需要解决这两种问题：

- 一个特殊球和若干个非特殊球，取到特殊球的概率
- 若干个非特殊球，取到某个固定的球的概率

先解决第二个问题，设总共有 $n$ 个球，先手会取 $\lceil\frac n2\rceil$ 个球，显然每个球取到的概率是相等的，故取到某个球的概率为 $\frac{\lceil\frac n2\rceil}n$。

再看第一个问题，假设有 $n-1$ 个非特殊球，概率还是 $\frac{\lceil\frac n2\rceil}n$，因为取到这个球之后的操作不重要，所以这个球可以看作是普通球。打表 $f,g$ 可以通过平移重合也说明了这一点。计算答案的方法写在最上面了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 10, mod = 1e9 + 7;
int inv[N], f[N];

int Main()
{
	int n, k, i, s = 0, t, a, ans;
	scanf("%lld%lld", &n, &k);
	for(i=1;i<=k;i++) scanf("%lld", &a), s = (s + a) % mod;
	ans = s * f[n-k+1] % mod;
	t = s, s = 0;
	for(i=1;i<=n-k;i++) scanf("%lld", &a), s = (s + a) % mod;
	ans = (ans + s * f[n-k]) % mod, t = (t + s) % mod;;
	printf("%lld %lld\n", ans, (t-ans+mod)%mod);
	return 0;
}
signed main()
{
	int t, i;scanf("%lld", &t);
	for(i=2,inv[1]=1;i<=N-10;i++) inv[i] = (mod - mod / i) * inv[mod%i] % mod;
	for(i=1;i<=N-10;i++) if(i%2==0) f[i] = inv[2];else f[i] = (i / 2 + 1) * inv[i] % mod;
	while(t--) Main();
	return 0;
}
```

本人看出只用关心概率。对于非特殊球本人一眼看穿了特殊球是没用的，但是本人就是没看出来特殊球也是这样。还打表了。感觉有点绕弯路了。

---

## 作者：ax_by_c (赞：0)

$k=0$ 的情况可能有一定启发。

首先转求和，最后除以 $n!$。

考虑排成一排，容易发现排法和取法一一对应。

考虑对每个数计算贡献。对于非特殊位置，直接将特殊位置去掉后计算排在奇数位和偶数位的方案数。对于特殊位置，将其他特殊位置去掉后计算后面第一个非特殊位置排在奇数位和偶数位的方案数即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=1e9+7;
const int N=4e5+5;
ll ksm(ll a,ll b,ll p){
	a=a%p;
	ll r=1;
	while(b){
		if(b&1)r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r%p;
}
ll fac[N],inv[N];
void Init(int n){
	fac[0]=1;
	rep(i,1,n)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	per(i,n,1)inv[i-1]=inv[i]*i%mod;
}
ll C(int n,int m){
	if(n<m||n<0||m<0)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
ll ceildiv(ll x,ll y){
	return x/y+bool(x%y);
}
int n,k,a[N];
void slv(){
	scanf("%d %d",&n,&k);
	rep(i,1,n)scanf("%d",&a[i]);
	Init(n);
	ll ans1=0,ans2=0;
	rep(i,1,n){
		if(i<=k){
			ans1=(ans1+C(n,k-1)*fac[k-1]%mod*fac[n-k]%mod*ceildiv(n-k+1,2)%mod*a[i]%mod)%mod;
			ans2=(ans2+C(n,k-1)*fac[k-1]%mod*fac[n-k]%mod*((n-k+1)/2)%mod*a[i]%mod)%mod;
		}
		else{
			ans1=(ans1+C(n,k)*fac[k]%mod*ceildiv(n-k,2)%mod*fac[n-k-1]%mod*a[i]%mod)%mod;
			ans2=(ans2+C(n,k)*fac[k]%mod*((n-k)/2)%mod*fac[n-k-1]%mod*a[i]%mod)%mod;
		}
	}
	printf("%lld %lld\n",ans1*inv[n]%mod,ans2*inv[n]%mod);
}
void main(){
	int T=1;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：白鲟 (赞：0)

朴素的直觉是每个球归属两人的概率均非常接近 $\dfrac{1}{2}$，由此继续对每个球（事实上只需考虑每类球）归属两人的概率进行考虑。

若一个球归属 Alice，则在此之前摸到了偶数个非特殊球；反之则归属 Bob。进一步思考，摸球被分成了 $n-k+1$ 个段，除最后一段外，每段以一个非特殊球结尾，每个特殊球等概率地落在每段，而每个非特殊球等概率地落在前 $n-k$ 段，落在奇数段的球归属 Alice，反之则归属 Bob。

综上，特殊球归属 Alice 的概率是 $\dfrac{\left\lceil\dfrac{n-k+1}{2}\right\rceil}{n-k+1}$，非特殊球归属 Alice 的概率为 $\dfrac{\left\lceil\dfrac{n-k}{2}\right\rceil}{n-k}$，期望由此易得。
```cpp
#include <cstdio>
using ll = long long;
const int mod = 1e9 + 7;
int T, k, n, x, sum_special, sum_non, res_Alice, res_Bob;
int power(int base, int exponent) {
    int res = 1;
    while (exponent) {
        if (exponent & 1) {
            res = ((ll)res * base) % mod;
        }
        base = ((ll)base * base) % mod;
        exponent >>= 1;
    }
    return res;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        sum_special = sum_non = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            if (i <= k) {
                sum_special = (sum_special + x) % mod;
            }
            else {
                sum_non = (sum_non + x) % mod;
            }
        }
        res_Alice = ((ll)((n - k + 2) / 2) * power(n - k + 1, mod - 2) % mod * sum_special % mod + 
                     (ll)((n - k + 1) / 2) * power(n - k, mod - 2) % mod * sum_non % mod) % mod;
        res_Bob = ((ll)((n - k + 1) / 2) * power(n - k + 1, mod - 2) % mod * sum_special % mod + 
                   (ll)((n - k) / 2) * power(n - k, mod - 2) % mod * sum_non % mod) % mod;
        printf("%d %d\n", res_Alice, res_Bob);
    }
    return 0;
}
```

---

