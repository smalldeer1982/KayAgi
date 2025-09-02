# [ARC099F] Eating Symbols Hard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc099/tasks/arc099_d

高橋君は，いつも頭の中に，長さ $ 2\ \times\ 10^9\ +\ 1 $ の整数列 $ A\ =\ (A_{-10^9},\ A_{-10^9\ +\ 1},\ ...,\ A_{10^9\ -\ 1},\ A_{10^9}) $ と，整数 $ P $ を思い浮かべています．

はじめ，高橋君が思い浮かべている整数列 $ A $ のすべての要素は $ 0 $ です． また，整数 $ P $ の値は $ 0 $ です．

高橋君は，`+`, `-`, `>`, `<` の記号を食べると，それぞれ次のように思い浮かべている整数列 $ A $，整数 $ P $ が変化します：

- `+` を食べた場合，$ A_P $ の値が $ 1 $ 大きくなる．
- `-` を食べた場合，$ A_P $ の値が $ 1 $ 小さくなる．
- `>` を食べた場合，$ P $ の値が $ 1 $ 大きくなる．
- `<` を食べた場合，$ P $ の値が $ 1 $ 小さくなる．

高橋君は，長さ $ N $ の文字列 $ S $ を持っています．$ S $ の各文字は `+`, `-`, `>`, `<` の記号のいずれかです． 高橋君は，$ 1\ \leq\ i\ \leq\ j\ \leq\ N $ なる整数の組 $ (i,\ j) $ を選んで，$ S $ の $ i,\ i+1,\ ...,\ j $ 文字目の記号をこの順に食べました． 高橋君が記号を食べ終わった後，高橋君が思い浮かべている整数列 $ A $ は，高橋君が $ S $ のすべての記号を $ 1 $ 文字目から順に食べた場合と等しくなったといいます． このような $ (i,\ j) $ として考えられるものは何通りあるか求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250000 $
- $ |S|\ =\ N $
- $ S $ の各文字は `+`, `-`, `>`, `<` のいずれか

### Sample Explanation 1

高橋君が $ S $ のすべての記号を食べた場合，$ A_1\ =\ 1 $ で，$ A $ の他の要素はすべて $ 0 $ になります． $ A $ がこれと等しくなるような $ (i,\ j) $ は次の通りです： - $ (1,\ 5) $ - $ (2,\ 3) $ - $ (2,\ 4) $

### Sample Explanation 2

高橋君が $ S $ のすべての記号を食べた場合と $ P $ が異なっていてもかまわないことに注意してください．

## 样例 #1

### 输入

```
5
+>+<-```

### 输出

```
3```

## 样例 #2

### 输入

```
5
+>+-<```

### 输出

```
5```

## 样例 #3

### 输入

```
48
-+><<><><><>>>+-<<>->>><<><<-+<>><+<<>+><-+->><<```

### 输出

```
475```

# 题解

## 作者：pufanyi (赞：13)

考虑构造一波类似生成函数的东西 $f(x)=\sum_{i=-\infty}^{+\infty}A_ix^i$，另外还有一个指针 $g$，开始是 $g$ 指向 $0$ 位置，显然初始时 $f(x)=0$。

我们令 $f_i(x)$ 表示 $1\sim i$ 这一段子串操作所得到的 $f$ 值，$g_i$ 表示 $1\sim i$ 操作后的指针位置。考虑在末尾加入一个字符 $c$，如果 $c$ 是 `'+'` 或 `'-'`，那显然 $\begin{cases}f_i(x)=f_{i-1}(x)\pm x^{g_i}\\g_i=g_{i-1}\end{cases}$，同理如果 $c$ 是 `'<'` 或 `'>'`，那显然 $\begin{cases}f_i(x)=f_{i-1}(x)\\g_i=g_{i-1}\mp 1\end{cases}$。

如果要计算 $[l,r]$ 的 $f$ 值，不难发现就是 $\frac{f_r(x)-f_{l-1}(x)}{x^{g_{l-1}}}$。

于是我们要算的就是 $f_n(x)=\frac{f_r(x)-f_{l-1}(x)}{x^{g_{l-1}}}$，考虑随便选一个 $x$，算出这个多项式的值然后哈希一下即可。

---

## 作者：皎月半洒花 (赞：9)

（如果题解页面公式锅了可以选择去blog内看


这题数据奇水，水到我觉得这 $83$ 组数据就是在闹着玩的。谷这题唯一有代码的那篇题解，只要把第二组样例 `reverse` 一下就可以 `hack` 掉；我双哈希把俩模数写混了都能对 $71/83$。
_____

> 给定一个下标范围在 $[-\infty,\infty]$ 的数组。一开始指针在 $0$ 处。给定一段操作序列。求有多少个子序列的操作结果等价于整个序列的操作结果。操作有四种，左移/右移/某个位置$+1$/某个位置$-1$ 。
>
> $1\leq n\leq 250,000$

一拿到题首先考虑 $dp$ ，发现 $dp$ 不是很可做…

于是就发现，类似这种题目可以使用哈希。四种操作分别对应 $\times base^{-1}$、$\times base$、$+base$、$-base$ 。

考虑这样做如何去求某一段的哈希值。普通的求法原理如下：

对于每个 $p$ ，截止到 $p$ 的哈希值，如果将 $x$ 看做 $base$ 的一个等价，那么就是是

$$
\sum_{i=1}^ps_ix^{p-i}
$$

考虑将上式记作 $o(p)$ 。则片段 $[l,r]$ 的哈希值可以如此得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/2qkkg86r.png)

考虑如果整个串的哈希值为 $q$，那么需要统计的是 $o(r)-o(l-1)\cdot x^{r-l+1}=q$ 。考虑从前至后用 $map$ 完成这个过程。由于不知道右端点的信息，需要对原式进行变形，即：

$$\frac{q-o(r)}{x^r}=\frac{o(l-1)}{x^{l-1}}$$

这样就可以做到 $l,r$ 无关了。随便选前缀或者后缀统计就好了。

但是注意到本题有个额外限制，最后只需要结果相同而不需要指针位置相同。所以需要在一开始哈希时稍微处理一下即可（这也是那篇挂了的题解的挂点）。

```cpp
#define mkp make_pair
#define pll pair<LL, LL>

const LL B1 = 237ll ;
const LL B2 = 637ll ;
const int N = 300010 ;
const LL P1 = 998244353 ;
const LL P2 = 1004535809 ;

int n ;
LL ans ;
char s[N] ;
LL I1, I2 ;
LL g[N][2] ;
LL S[N], T[N] ;
map <pll, LL> buc ;

LL expow(LL a, LL b, LL p){
    LL ret = 1 ;
    while (b){
        if (b & 1)
            (ret *= a) %= p ;
        (a *= a) %= p ; b >>= 1 ;
    }
    return ret ;
}
int main(){
    cin >> n >> (s + 1) ;
    g[0][0] = g[0][1] = 1ll ;
    I1 = expow(B1, P1 - 2, P1) ;
    I2 = expow(B2, P2 - 2, P2) ;
    for (int i = 1 ; i <= n ; ++ i){
        if (s[i] == '-'){
            g[i][0] = g[i - 1][0] ;
            g[i][1] = g[i - 1][1] ;
            S[i] = (S[i - 1] - g[i][0] + P1) % P1 ;
            T[i] = (T[i - 1] - g[i][1] + P2) % P2 ;
        }
        if (s[i] == '+'){
            g[i][0] = g[i - 1][0] ;
            g[i][1] = g[i - 1][1] ;
            S[i] = (S[i - 1] + g[i][0]) % P1 ;
            T[i] = (T[i - 1] + g[i][1]) % P2 ;
        }
        if (s[i] == '<'){
            g[i][0] = g[i - 1][0] * I1 % P1 ;
            g[i][1] = g[i - 1][1] * I2 % P2 ;
            S[i] = S[i - 1] ; T[i] = T[i - 1] ;
        }
        if (s[i] == '>'){
            g[i][0] = g[i - 1][0] * B1 % P1 ;
            g[i][1] = g[i - 1][1] * B2 % P2 ;
            S[i] = S[i - 1] ; T[i] = T[i - 1] ;
        }
        ++ buc[mkp(S[i], T[i])] ;
    }
    ++ buc[mkp(0, 0)] ; LL x, y ;
    for (int i = 0 ; i < n ; ++ i){
        buc[mkp(S[i] , T[i])] -- ;
        x = (S[i] + S[n] * g[i][0] % P1) % P1 ;
        y = (T[i] + T[n] * g[i][1] % P2) % P2 ;
        ans += buc[mkp(x, y)] ;
    }
    cout << ans << endl ; return 0 ;
}

```




---

## 作者：pldzy (赞：5)

[AtC 传送门：F - Eating Symbols Hard ](https://atcoder.jp/contests/arc099/tasks/arc099_d)

双哈希 + 差分

## Solution

### 1

发现要想确定 $[l,r]$ 对序列 $A$ 的影响，必须得记录下 $S$ 中的所有子串对 $A$ 操作后的状态。进一步地，为了更好处理每一个 $[l,r]$，自然会想到使用差分的方法——记录下 $[1,i]\ (i \in [1,\left\vert S \right\vert])$。

但是上述想法暂时看起来仍有许多缺陷。注意到，我们的目的是**确定 $A$ 序列在不同情况下的状态**，所以这就引导我们要去使用哈希甚至双哈希进行维护或记录。

为什么哈希能实现上述的差分呢？其实，稍加思考即可发现，即 $h(i)$ 表示按照 $S$  的子序列 $[1,i]$ 对初始为 $0$ 的序列 $A$ 进行操作后 $A$ 序列的哈希值。那么 $h(r)-h(l-1)$ 实际上就是将前 $i-1$ 个操作造成的影响抵消掉。**因为真正对序列 $A$ 造成影响的操作就是对它元素进行加减，而对元素的加减操作显然是可以通过相减抵消的**。所以最终只留下第 $l$ 到 $r$ 个操作对序列的影响。

### 2

回过头来，题目要求统计的合法区间 $[l,r]$ 貌似就是满足 $h(r)-h(l-1)=h(n)$ 的区间。但是，这里忽略掉了一点，就是在 $h(r)-h(l-1)$ 后，这个差值相比 $h(n)$ 实质上会发生一个**在 $base$ 进制上的位移**。简单解释一下，统计 $[1,n]$ 区间的哈希值时，下标 $p$ 是从 $0$ 开始的，第一个操作乘上的进制是 $base^0$，然而，统计 $[l,r]$ 区间的哈希值时，下标 $p$ 经过了前 $l-1$ 次操作，不妨记 $P_i$ 表示第 $i$ 次操作时 $p$ 的下标，那么统计区间 $[l,r]$ 时第一次乘上进制的就是 $base^{P_{l}}$。

所以，为了消除后者比前者多出的从第 $0$ 位到第 $l - 1$ 位的位移，正确的柿子是 $\dfrac{h(r)-h(l-1)}{base^{P_{l-1}}} = h(n)$。

### 3

知道了如何判断某一子区间是否合法之后，再考虑如何将它放进代码里实现。

看到时间限制和 $\left\vert S \right\vert$ 的大小限制，发现统计时似乎只允许 $\mathcal{\text{O}}(n)$ 的复杂度。这就引导我们想到一个大概的统计方法：枚举 $l$ 遍历 $1$ 到 $\left\vert S \right\vert$，然后统计合法的区间右端点 $r$ 的数量。进一步地，这样一来 $h(n)$ 和 $h(l-1)$ 已知，根据推出的柿子就发现 $h(r)$ 已经被唯一确定了，即 $h(r)=h(n)\times base^{P_{l-1}} + h(l-1)$，所以一开始计算 $h(i)$ 的时候开一个 `map` 把它们按照哈希值统计数量即可。

至此，此题被完美解决， 复杂度可过。

### 4

还要再提一个代码实现的时候需要注意的点。题目中已述，$p$ 有可能为负数。那么此时乘上的进制就成了 $base^{-\left\vert p \right\vert}$，然后简单推一波柿子：$base^{-\left\vert p \right\vert}=(base^{-1})^{\left\vert p\right\vert}$。而 $base^{-1}$ 是什么？$base$ 在取模某个模数意义下的逆元。因为模数我们一定会设为一个素数，故直接用快速幂算出其逆元即可。

需要双哈希。


## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(register int i = a; i <= b; ++i)
typedef long long ll;
const int maxn = 250005;
const int mod1 = 1e9 + 7, mod2 = 998244353;
int n, p[maxn], bs = 121;
char c[maxn];
map<pair<int, int>, int> mp;
pair<int, int> hsh[maxn];
ll ans;

inline int pw(int x, int p, int mod){
	int res = 1;
	while(p){
		if(p & 1) 
			res = 1ll * res * x % mod;
		p /= 2, x = 1ll * x * x % mod;
	} return res;
}
inline pair<int, int> gh(int x, int y){
	int a, b; a = b = x;
	if(y < 0) 
		a = pw(a, mod1 - 2, mod1), b = pw(b, mod2 - 2, mod2), y *= -1; 
	return make_pair(pw(a, y, mod1), pw(b, y, mod2));
}

inline pair<int, int> add(pair<int, int> a, pair<int, int> b){
	return make_pair((a.first + b.first) % mod1, (a.second + b.second) % mod2);
}
inline pair<int, int> mns(pair<int, int> a, pair<int, int> b){
	return make_pair((a.first + mod1 - b.first) % mod1, (a.second + mod2 - b.second) % mod2);
}
inline pair<int, int> tim(pair<int, int> a, pair<int, int> b){
	return make_pair((1ll * a.first * b.first) % mod1, (1ll * a.second * b.second) % mod2);
}

int main(){
	scanf("%d", &n); 
	rep(i, 1, n){ 
		char c; cin >> c; 
		p[i] = p[i - 1];
		if(c == '+') hsh[i] = add(hsh[i - 1], gh(bs, p[i]));
		if(c == '-') hsh[i] = mns(hsh[i - 1], gh(bs, p[i]));
		if(c == '<') hsh[i] = hsh[i - 1], p[i] -= 1;
		if(c == '>') hsh[i] = hsh[i - 1], p[i] += 1;
		mp[hsh[i]] += 1;
	}
	rep(i, 1, n)
		ans += mp[add(hsh[i - 1], tim(hsh[n], gh(bs, p[i - 1])))], 
		mp[hsh[i]] -= 1;
	printf("%lld\n", ans);
	return 0;
}
```


------------
感谢阅读。

---

## 作者：lzk5627 (赞：3)

申请添加简要题意(被禁言了)

并且题面上的样例是错误的,markdown未显示

### 简要题意
你有一个初始为0的数组和一个初始在0的指针,范围可以看做无限

给出一个操作串,由 $<,>,+,-$ 组成,其中每个字符意义如下

* < 将指针左移一位

* \> 将指针右移一位

* \+ 将指针对应位置+1

* \- 将指针对应位置-1

求有多少个子串,使得执行完子串的操作后,数组和执行完整个串是一样的

### sol
考虑用hash来解决问题,从后往前扫过来,每个符号对应hash值得变化如下

* \< 乘以 $base^{-1}$
* \> 乘以 $base$
* \+ 加上 $base$
* \- 减去 $base$

使用双hash,用map维护即可

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int mod1=1e9+7;
const int P1=19260817;
const int P2=998244353;
const int mod2=1004535809;
#define ll long long
typedef pair<ll,ll>Pi;
ll fsp(ll x,int y){
	ll ans=1;
	while(y){
		if(y&1)	ans=ans*x%mod1;
		x=x*x%mod1,y>>=1;
	}
	return ans;
}
ll ksm(ll x,int y){
	ll ans=1;
	while(y){
		if(y&1)	ans=ans*x%mod2;
		x=x*x%mod2,y>>=1;
	}
	return ans;
}
char s[N];
map<Pi,int>ma;
ll n,l1,l2=1,r1,r2=1,ans,res1,res2,add1,add2,inv1,inv2;
int main(){
	scanf("%lld%s",&n,s+1);
	add1=fsp(P1,n);add2=ksm(P2,n);
	inv1=fsp(P1,mod1-2),inv2=ksm(P2,mod2-2);
	for(int i=n;i;i--){
		if(s[i]=='-'){
			res1=(res1-add1+mod1)%mod1;
			res2=(res2-add2+mod2)%mod2;
		}
		if(s[i]=='+'){
			res1=(res1+add1)%mod1;
			res2=(res2+add2)%mod2;
		}
		if(s[i]=='<'){
			res1=res1*inv1%mod1;
			res2=res2*inv2%mod2;
		}
		if(s[i]=='>'){
			res1=res1*P1%mod1;
			res2=res2*P2%mod2;
		}
	}
	for(int i=n;i;i--){
		ll k1=0,k2=0;
		if(s[i]=='-'){
			l1=(l1-add1+mod1)%mod1,k1=mod1-add1;
			r1=(r1-add2+mod2)%mod2,k2=mod2-add2;
		}
		if(s[i]=='<'){
			l1=l1*inv1%mod1,l2=l2*inv1%mod1;
			r1=r1*inv2%mod2,r2=r2*inv2%mod2;
		}
		if(s[i]=='>'){
			l1=l1*P1%mod1,l2=l2*P1%mod1;
			r1=r1*P2%mod2,r2=r2*P2%mod2;
		}
		if(s[i]=='+'){
			l1=(l1+add1)%mod1,k1=add1;
			r1=(r1+add2)%mod2,k2=add2;
		}
		++ma[Pi((k1-l1+mod1)*fsp(l2,mod1-2)%mod1,(k2-r1+mod2)*ksm(r2,mod2-2)%mod2)];
		ans+=ma[Pi((res1-l1+mod1)*fsp(l2,mod1-2)%mod1,(res2-r1+mod2)*ksm(r2,mod2-2)%mod2)];
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：xht (赞：1)

> [ARC099F Eating Symbols Hard](https://atcoder.jp/contests/arc099/tasks/arc099_d)

## 题意

- 有一个长度为 $2 \times 10^9 + 1$ 的整数序列 $a_{-10^9 \dots 10^9}$，和一个整数 $p$，一开始均为 $0$。
- 对于一个仅包含 `+-><` 的字符串，按顺序依次执行每个字符对应的操作，可以得到新的 $a$ 序列。
- 每个字符对应的操作如下：
  - `+`：$a_p$ 加上 $1$。
  - `-`：$a_p$ 减去 $1$。
  - `>`：$p$ 加上 $1$。
  - `<`：$p$ 减去 $1$。
- 现在有一个长度为 $n$ 的仅包含 `+-><` 的字符串 $s$，问有多少个 $s$ 的非空子串得到的 $a$ 序列与 $s$ 得到的 $a$ 序列一样。
- $n \le 2.5 \times 10^5$。

## 题解

首先对于 $a$ 显然可以 hash，hash 函数设为模意义下的 $\sum_{i=-10^9}^{10^9} a_ix^i$，其中 $x$ 是一个自己设定的 base，注意可能要多个 base/mod。

对于一个操作序列，我们可以得到其操作完后的 hash 值以及 $p$ 所在的位置 $(h,p)$，显然这个信息是可以合并的，$\operatorname{merge}((h_i,p_i), (h_j,p_j)) = (h_i + h_jx^{p_i}, p_i + p_j)$。

预处理出 $s$ 的每个前缀 $s[:i]$ 对应的 $(h_i,p_i)$，题目要求 $s$ 与 $s[i:j]$ 得到的 $h$ 相等，等价于 $s[:i-1] + s$ 与 $s[:j]$ 得到的 $h$ 相等，即 $h_{i-1} + h_{n}x^{p_{i-1}} = h_j$。

从左往右扫 $j$，用个 `map` 记录 $h_{i-1} + h_nx^{p_{i-1}}$ 的值的个数即可，时间复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 2.5e5 + 7, M = 2;
int n;
char s[N];
struct H {
	vector<modint> a;
	inline H() { a.resize(M); }
	inline modint &operator [] (int i) { return a[i]; }
	inline friend bool operator < (H x, H y) { return x.a < y.a; }
	inline friend H operator + (H x, H y) {
		for (int i = 0; i < M; i++) x[i] += y[i];
		return x;
	}
	inline friend H operator - (H x, H y) {
		for (int i = 0; i < M; i++) x[i] -= y[i];
		return x;
	}
	inline friend H operator * (H x, H y) {
		for (int i = 0; i < M; i++) x[i] *= y[i];
		return x;
	}
} a[N], x, y, h[N];
map<H, int> f;
ll ans;

int main() {
	srand(time(0));
	rd(n), rds(s, n);
	for (int i = 0; i < M; i++)
		a[0][i] = 1, x[i] = rdm(1, P - 1), y[i] = 1 / x[i];
	for (int i = 1; i <= n; i++)
		switch (s[i]) {
			case '+' : h[i] = h[i-1] + (a[i] = a[i-1]); break;
			case '-' : h[i] = h[i-1] - (a[i] = a[i-1]); break;
			case '>' : h[i] = h[i-1], a[i] = a[i-1] * x; break;
			case '<' : h[i] = h[i-1], a[i] = a[i-1] * y; break;
		}
	for (int i = 1; i <= n; i++) ++f[h[i-1]+h[n]*a[i-1]], ans += f[h[i]];
	print(ans);
	return 0;
}
```

---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/AT4163)

把一个符合要求的区间 $[l,r]$ 拆成 $[1,r]-[1,l-1]$。于是问题变成了找到一些结果相同的操作序列前缀。

$p$ 的移动，数组的修改……要维护的东西太多，我们难以直接对每个操作判断，唯一的可能的是**做完操作后判断结果**。

于是不妨把操作完后的序列哈希。记 $B,M$ 是选取的哈希底数，模数，$a$ 是操作完后的数组，那么其哈希值为

$$\sum_{i\in[-n,n]} a_iB^{i+n}\bmod M$$

对于样例 $1$，所有操作的结果为 $\{0,1,0,0,0\}$。画出它每次操作后的结果

$$\begin{cases}
1,0,0,0,0&p=0&\texttt{case 1}\\
1,0,0,0,0&p=1&\texttt{case 2}\\
1,1,0,0,0&p=1&\texttt{case 3}\\
1,1,0,0,0&p=0&\texttt{case 4}\\
0,1,0,0,0&p=0&\texttt{case 5}
\end{cases}$$

注意到：

+ $\texttt{case 1-5}$ 符合条件，说明 $[1,5]$ 是一组答案
+ $\texttt{case 2-4}$ 符合条件，说明 $[2,4]$ 是一组答案
+ $\texttt{case 2-3}$ 符合条件，说明 $[2,3]$ 是一组答案
+ $\texttt{case 3-4}$ 也符合条件，但它不是答案
+ $\texttt{case 3-3}$ 也符合条件，但它不是答案

猜想一个区间是否满足要求，不仅跟哈希值相等有关系，还和 $p$ 指针的位置有关系。比如 $\texttt{case 3-3}$，它的 $p$ 指针是从 $\tt 1$ 开始的才能满足条件，如果从 $0$ 开始，那么答案就会整体左移，从而不满足条件。

因此一个区间的运算结果，应该是 $[1,r]$ 的哈希值，减去 **移位** 后的 $[1,l]$ 的哈希值。

难点已经解决，剩下的就是用 `map` 作桶来统计答案了。

对了，单哈希冲突概率很大，建议双哈希。但是 $3817$ 这个数做哈希我认为是非常好的。

```cpp
using hsh = unsigned long long;

const int N = 2.5e5,M = N * 2 + 5;
const hsh base1 = 3817,BASE1 = 544144620;
const hsh base2 = 1738,BASE2 = 608251306;
const hsh mod1 = 1e9 + 7,mod2 = 998244353;

int n,m;
char s[N];

int pos[N];
hsh h1[N],h2[N],p1[M],P1[M],p2[M],P2[M],res1,res2;
map<pair<int,int>,int> H;

int main(){
	scanf("%d%s",&n,s + 1); m = n * 2;
	p1[0] = 1; rep(i,1,m) p1[i] = (p1[i - 1] * base1) % mod1;
	P1[0] = 1; rep(i,1,m) P1[i] = (P1[i - 1] * BASE1) % mod1;
	p2[0] = 1; rep(i,1,m) p2[i] = (p2[i - 1] * base2) % mod2;
	P2[0] = 1; rep(i,1,m) P2[i] = (P2[i - 1] * BASE2) % mod2;
	pos[0] = n;
	rep(i,1,n){
		pos[i] = pos[i - 1];
		if(s[i] == '>') pos[i] = pos[i - 1] + 1;
		if(s[i] == '<') pos[i] = pos[i - 1] - 1;
		if(s[i] == '+') (res1 += p1[pos[i]]) %= mod1;
		if(s[i] == '-') (res1 += mod1 - p1[pos[i]]) %= mod1;
		if(s[i] == '+') (res2 += p2[pos[i]]) %= mod2;
		if(s[i] == '-') (res2 += mod2 - p2[pos[i]]) %= mod2;
		h1[i] = res1; h2[i] = res2;
	}
	long long sum = 0;
	Rep(i,n - 1,0){
		++H[mp(h1[i + 1],h2[i + 1])];
		hsh v1 = pos[i] <= n ? P1[n - pos[i]] : p1[pos[i] - n];
		hsh v2 = pos[i] <= n ? P2[n - pos[i]] : p2[pos[i] - n];
		hsh u1 = (h1[i] + (res1 * v1 % mod1)) % mod1;
		hsh u2 = (h2[i] + (res2 * v2 % mod2)) % mod2;
		sum += H[mp(u1,u2)];
	}
	printf("%lld\n",sum);
	return 0;
}

---

## 作者：封禁用户 (赞：1)

看到大佬们都是用的生成函数什么的，那本蒟蒻就讲一个简单易懂的做法吧！

#### 思路



定义 $ h[i] $ 为经过 $ i $ 次操作后的数组的哈希值 , $ pos[i] $ 为经过 $ i $ 次操作的位置。

设 $ pos[0] = n$ ， 这样便不会越界。

那么对于每次操作 ：

左移 ：  $ pos[i] = pos[i - 1] - 1 $ ， $ h[i] = h[i - 1] $

左移 ： $ pos[i] = pos[i - 1] + 1 $ ， $ h[i] = h[i - 1] $

加 ： $ pos[i] = pos[i - 1] $ ， $ h[i] = h[i - 1] + m ^ { pos[i] } $ 

减 ： $ pos[i] = pos[i - 1] $ ， $ h[i] = h[i - 1] - m ^ { pos[i] } $ 

对于查询移个区间的h值 ， 不考虑左移右移：

$ l $ 到 $ r $ 的哈希值 = $ h[r] - h[l - 1]$

考虑左移右移 ， 若先不考虑 ， 则得出的值一定为移动了一段再做的 ， 只需考虑多出的数量或少的数量 ：

若 $ pos[l - 1] > n $ 则为多算了 $ pos[l - 1] - n $ 

$ l $ 到 $ r $ 的哈希值 = $ ( h[r] - h[l - 1] ) / m ^ { pos[l - 1] - n }$

若 $ pos[l - 1] < n $ 则为少算了 $ n - pos[l - 1] $ 

$ l $ 到 $ r $ 的哈希值 = $ ( h[r] - h[l - 1] ) * m ^ { pos[l - 1] - n }$

经过上面的一顿操作之后，我们发现我们已经可以求任意一段 $ l $ 到 $ r $ 的哈希值，此时只需求 ： 
有多少 $ l $ 和 $ r $ 可以使得 $ HASH[1,n] $ = $ HASH[l,r] $

可以枚举左端点 ， 此时知道了 $ pos[l - 1] $ 和 $ h[l - 1] $ ， 只需解方程即可 。

注意 ， 因为有乘号 ， 移项后会变为除号 ， 所以还需要逆元 。

#### 代码

必须要用双哈希才能过 qwq。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mp make_pair
#define m 131
#define p 19260817
#define sed 137
#define mod 998244353
#define pii pair<int,int>
const int N=500000+5;
int n,pos[N];
ll h1[N],pw1[N],h2[N],pw2[N],ans;
char s[N];
map<pii,int>vis;
ll qpow1(ll a,int b){
	ll sum=1;
	while(b){
		if(b&1)sum=sum*a%p;
		a=a*a%p;
		b>>=1;
	}
	return sum;
}
ll qpow2(ll a,int b){
	ll sum=1;
	while(b){
		if(b&1)sum=sum*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return sum;
}
ll inv1(ll a){
	return qpow1(a,p-2);	
}
ll inv2(ll a){
	return qpow2(a,mod-2);	
}
int main(){
	cin>>n;
	cin>>(s+1);
	h1[0]=0;
	h2[0]=0;
	pos[0]=n;
	pw1[0]=1;
	pw2[0]=1;
	for(int i=1;i<N;++i)pw1[i]=pw1[i-1]*m%p,pw2[i]=pw2[i-1]*sed%mod;
	for(int i=1;i<=n;++i){
		if(s[i]=='<')pos[i]=pos[i-1]-1,h1[i]=h1[i-1],h2[i]=h2[i-1];
		else if(s[i]=='>')pos[i]=pos[i-1]+1,h1[i]=h1[i-1],h2[i]=h2[i-1];	
		else if(s[i]=='+')pos[i]=pos[i-1],h1[i]=(h1[i-1]+pw1[pos[i]])%p,h1[i]=(h1[i-1]+pw1[pos[i]])%p,h2[i]=(h2[i-1]+pw2[pos[i]])%mod;
		else pos[i]=pos[i-1],h1[i]=(h1[i-1]-pw1[pos[i]]+p)%p,h2[i]=(h2[i-1]-pw2[pos[i]]+mod)%mod;
	}
	pii r=mp(h1[n],h2[n]);
	for(int i=n;i>=1;--i){
		++vis[mp(h1[i],h2[i])];
		if(pos[i-1]>n){
			ll v1=(pw1[pos[i-1]-n]*r.first%p+h1[i-1])%p;
			ll v2=(pw2[pos[i-1]-n]*r.second%mod+h2[i-1])%mod;
			ans+=vis[mp(v1,v2)];
		}
		else{
			ll v1=(inv1(pw1[n-pos[i-1]])*r.first%p+h1[i-1])%p;
			ll v2=(inv2(pw2[n-pos[i-1]])*r.second%mod+h2[i-1])%mod;
			ans+=vis[mp(v1,v2)];
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：逗逼领主 (赞：1)

设操作串为$S$, $a$为操作后的序列, 给操作串一个哈希值: 

$$
Hash(S)=(\sum_{i=-\infty}^{\infty}a[i]*X^i)\%mod
$$

其中$X$为随机数.

定义$g1(x)$为在哈希值为$x$的操作串前加上一个字符'+'后的哈希值, 易得$g1(x)=x+1$. 类似的, 定义$g2(x)$为前面加上字符'-'后的哈希值, $g3(x)$为前面加上字符'>'后的哈希值, $g4(x)$为前面加上字符'<'后的哈希值, 则有:
$$
g2(x)=x-1
$$

$$
g3(x)=x*(X^{-1})
$$

$$
g4(x)=x*X
$$

设$f_{a,b}(x)$为从哈希值$x$开始, 依次执行从$S$的第$a$个位置到$S$的第$b$个位置上的字符对应的$g$函数. 相应的, 设$g1^{-1}$, $g2^{-1}$, $g3^{-1}$, $g4^{-1}$ 为每个$g$函数的逆操作, $f_{a,b}^{-1}(x)$为从哈希值$x$开始, 依次执行从$S$的第$a$个位置到$S$的第$b$个位置上的字符对应的$g$函数的逆函数.

题目要求$f_{n,1}(0)=f_{j,i}(0)\ \ (j\geq i)$的$(i,j)$对的数量. 进行变换:
$$
f_{n,1}(0)=f_{j,i}(0)
$$

$$
f_{i,n}^{-1}(f_{n,1}(0))=f_{i,n}^{-1}(f_{j,i}(0))
$$

$$
f_{i,n}^{-1}(f_{n,1}(0))=f_{j+1,n}^{-1}(0)
$$

$f_{n,1}(0)$可以预先求出, 那么我们维护$v1(i)=f_{i,n}^{-1}(f_{n,1}(0))$, $v2(i)=f_{i+1,n}^{-1}(0)$, 用map查询$v1[i]==v2[j]$的$(i,j)$对的数量即可.

关于$f_{i,n}^{-1}$怎么维护. 注意到每个$g$函数都是形如$x=kx+b$的一次函数, 那么可以维护嵌套起来的总函数的$k$和$b$两个值, 每加入一个函数计算出新的$k$和$b$即可.

多取几个$X$避免冲突.

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int qpow(int x,int k)
{
    int r=1;
    while(k)
    {
        if(k&1)r=1ll*r*x%mod;
        k>>=1;x=1ll*x*x%mod;
    }
    return r;
}
int add(int x,int y){return x+y<mod?x+y:x+y-mod;}
int n;
char s[300300];

int X[6]={233,1919,114514,817,1001,9527};
int inv[6];
struct Node {
    int v[6];
    bool operator < (const Node &o)const{
        for(int i=0;i<6;++i)
            if(v[i]!=o.v[i])return v[i]<o.v[i];
        return 0;
    }
    void clear(){memset(v,0,sizeof(v));}
    void f(char c)
    {
        if(c=='+') for(int i=0;i<6;++i)v[i]=add(v[i],1);
        else if(c=='-') for(int i=0;i<6;++i)v[i]=add(v[i],mod-1);
        else if(c=='>') for(int i=0;i<6;++i)v[i]=1ll*v[i]*X[i]%mod;
        else if(c=='<') for(int i=0;i<6;++i)v[i]=1ll*v[i]*inv[i]%mod;
    }
};
map<Node,int>mp;
struct PNN{
    Node k,b;
    void clear() { for(int i=0;i<6;++i)k.v[i]=1,b.v[i]=0; }
    void f(char c)
    {
        if(c=='+')for(int i=0;i<6;++i)b.v[i]=add(b.v[i],mod-k.v[i]);
        else if(c=='-')for(int i=0;i<6;++i)b.v[i]=add(b.v[i],k.v[i]);
        else if(c=='>')for(int i=0;i<6;++i)k.v[i]=1ll*k.v[i]*inv[i]%mod;
        else if(c=='<')for(int i=0;i<6;++i)k.v[i]=1ll*k.v[i]*X[i]%mod;
    }
    Node calc(Node x)
    {
        Node res;
        for(int i=0;i<6;++i)
            res.v[i]=add(1ll*k.v[i]*x.v[i]%mod,b.v[i])%mod;
        return res;
    }
};
int main()
{
    for(int i=0;i<6;++i)inv[i]=qpow(X[i],mod-2);
    scanf("%d",&n);
    scanf("%s",s+1);
    Node C;C.clear();
    for(int i=n;i;--i)C.f(s[i]);
    Node o;o.clear();
    mp[o]++;
    PNN cur;cur.clear();
    long long ans=0;
    for(int i=n;i;--i)
    {
        cur.f(s[i]);
        Node tt=cur.calc(C);
        ans+=mp[cur.calc(C)];
        mp[cur.calc(o)]++;
    }
    printf("%lld\n",ans);
    return 0;
}

```





---

## 作者：WorldMachine (赞：0)

考虑哈希，令 $A_i$ 为执行操作 $[1,i]$ 后的序列，定义 $f_i$ 为：
$$
f_i=\sum_{j=-\infty}^{\infty}A_{i,j}\text{base}^j
$$
发现两个前缀的指针位置不同导致不能直接差分，设执行操作 $[1,i]$ 后的指针位置为 $g_i$，则执行操作 $[l,r]$ 后的实际哈希值为：
$$
h_{l,r}=\dfrac{f_r-f_{l-1}}{\text{base}^{g_{l-1}}}
$$
用 `map` 记录一下有多少 $[l,r]$ 满足 $h_{l,r}=f_n$ 即可。

要写双哈希，而且注意这题数据很水的，搞错模数都能过前面 $63$ 个点，导致我一度认为是我其它细节写错了……

---

## 作者：yinianxingkong (赞：0)

简洁的题解。

判断数组是否相同，哈希即可。

左移右移就是全局乘，增加减少就是全局减，维护全局标记。

最后定一求一，哈希表维护即可。

[代码](https://atcoder.jp/contests/arc099/submissions/56151423)。

---

## 作者：Little09 (赞：0)

考虑比较数组显然是不好做的，转化成 Hash 来做。注意到我们如果仅在 `+`，`-` 处计算对答案的贡献，那么每个移位就是把后面所有贡献乘 $bas$ 或 $bas^{-1}$。于是把字符串 reverse 一下，就变成了前面的乘 $bas$ 或 $bas^{-1}$。

于是每个字符串的权值可以这样计算：经过一个 `+` 或 `-` 的时候，就 $+1$ 或 $-1$；经过一个 `<` 或 `>` 的时候，就 $\times bas$ 或 $\times bas^{-1}$。再对大质数取模做 Hash。

假设 $[1,n]$ 权值是 $k$。考虑如何表示一个区间 $[l,r]$ 的权值。不妨假设初始值为 $x$，考虑做到 $l-1$ 的时候的值是 $ax+b$，做到 $r$ 的时候值是 $cx+d$，那么中间就是 $\times \dfrac ca+d-\dfrac{bc}a$。那么我们希望 $d-\dfrac{bc}a=k$，可以推出：

$$\frac{d-k}c=\frac ba$$

于是扫一下每个前缀统计贡献即可。双模 Hash。

```cpp
pii operator +(const pii &x,const pii &y)
{
	return mkp((x.fi+y.fi)%mod[0],(x.se+y.se)%mod[1]);
}
pii operator -(const pii &x,const pii &y)
{
	return mkp((x.fi+mod[0]-y.fi)%mod[0],(x.se+mod[1]-y.se)%mod[1]);
}
pii operator *(const pii &x,const pii &y)
{
	return mkp((x.fi*y.fi)%mod[0],(x.se*y.se)%mod[1]);
}
pii operator /(const pii &x,const ll &y)
{
	return mkp((x.fi*ksm(y,mod[0]-2,mod[0]))%mod[0],(x.se*ksm(y,mod[1]-2,mod[1]))%mod[1]);
}
pii operator /(const pii &x,const pii &y)
{
	return mkp((x.fi*ksm(y.fi,mod[0]-2,mod[0]))%mod[0],(x.se*ksm(y.se,mod[1]-2,mod[1]))%mod[1]);
}
pii s[N][2];
const ll bas=233,bas0=197078383,bas1=266094423;
map<pii,int>q;
ll ans;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	rep(i,1,n) cin >> a[i];
	reverse(a+1,a+n+1);
	s[0][0]=mkp(1,1);
	rep(i,1,n)
	{
		s[i][0]=s[i-1][0],s[i][1]=s[i-1][1];
		if (a[i]=='+') s[i][1]=s[i][1]+mkp(1,1);
		else if (a[i]=='-') s[i][1]=s[i][1]-mkp(1,1);
		else if (a[i]=='<') s[i][0]=s[i][0]*mkp(bas0,bas1),s[i][1]=s[i][1]*mkp(bas0,bas1);
		else if (a[i]=='>') s[i][0]=s[i][0]*mkp(bas,bas),s[i][1]=s[i][1]*mkp(bas,bas);
	}
	pii k=s[n][1];
	rep(i,0,n)
	{
		pii r=(s[i][1]-k)/s[i][0];
		ans+=q[r];
		q[s[i][1]/s[i][0]]++;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：orz_z (赞：0)

### AT4163 [ARC099D] Eating Symbols Hard

手玩数据，不难发现，这几种操作类似于子串哈希的过程。

区间操作序列判断相同更坚定了我们的想法，哈希解决问题。

考虑维护前缀哈希，一个区间 $[l,r]$ 的哈希值，应该是 $[1,r]$ 的哈希值，减去 $[1,l-1]$ 移位后的哈希值，移位顺便维护一下即可。

最后双或三哈希判断，开桶记录个数即可，时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(ll x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 250010 * 2;

const ll bs1 = 819, Bs1 = 783725420, md1 = 998244353, bs2 = 1989, Bs2 = 227249785, md2 = 999999607, bs3 = 1998, Bs3 = 582062931, md3 = 999967099;

ll n, As, pos[_];

ull r1, r2, r3, p1[_], P1[_], p2[_], P2[_], p3[_], P3[_], hs1[_], hs2[_], hs3[_];

char s[_];

map<tuple<int, int, int>, int> mp;

signed main()
{
	n = read();
	scanf("%s", s + 1);
	p1[0] = P1[0] = p2[0] = P2[0] = p3[0] = P3[0] = 1;
	for(int i = 1; i <= n * 2; ++i)
	{
		p1[i] = p1[i - 1] * bs1 % md1;
		P1[i] = P1[i - 1] * Bs1 % md1;
		p2[i] = p2[i - 1] * bs2 % md2;
		P2[i] = P2[i - 1] * Bs2 % md2;
		p3[i] = p3[i - 1] * bs3 % md3;
		P3[i] = P3[i - 1] * Bs3 % md3;
	}
	pos[0] = n;
	for(int i = 1; i <= n; ++i)
	{
		pos[i] = pos[i - 1];
		if(s[i] == '>') pos[i] = pos[i - 1] + 1;
		if(s[i] == '<') pos[i] = pos[i - 1] - 1;
		if(s[i] == '+')
		{
			r1 = (r1 + p1[pos[i]]) % md1;
			r2 = (r2 + p2[pos[i]]) % md2;
			r3 = (r3 + p3[pos[i]]) % md3;
		}
		if(s[i] == '-')
		{
			r1 = (r1 + md1 - p1[pos[i]]) % md1;
			r2 = (r2 + md2 - p2[pos[i]]) % md2;
			r3 = (r3 + md3 - p3[pos[i]]) % md3;
		}
		hs1[i] = r1, hs2[i] = r2, hs3[i] = r3;
	}
	for(int i = n - 1; i >= 0; --i)
	{
		mp[{hs1[i + 1], hs2[i + 1], hs3[i + 1]}]++;
		ull k1 = (hs1[i] + (r1 * ((pos[i] <= n) ? P1[n - pos[i]] : p1[pos[i] - n]) % md1)) % md1;
		ull k2 = (hs2[i] + (r2 * ((pos[i] <= n) ? P2[n - pos[i]] : p2[pos[i] - n]) % md2)) % md2;
		ull k3 = (hs3[i] + (r3 * ((pos[i] <= n) ? P3[n - pos[i]] : p3[pos[i] - n]) % md3)) % md3;
//		cout << k1 << " " << k2 << "\n";
		As += mp[{k1, k2, k3}];
	}
	write(As);
	return 0;
}
```



---

## 作者：ZhiYao (赞：0)

左移，右移，一些位置上增量，这些信息难以直接维护，这启发我们把操作序列更加形式化，也就是把这些操作附加在一个更容易维护的对象上，形式幂级数 / hash 在本题中是很好的选择。

令 $F = \sum_i A_i x^i$，$F_i$ 为执行操作 $1∼i$ 后 $F$ 的值。

现在考虑求执行操作 $l∼r$ 后的 $F$，这需要 $p_i$ 表示执行操作 $1∼i$ 后指针的位置。

此时 $F$ 的值等于$\frac{F_R - F_{l-1}}{x^{p_{l-1}}}$，给 $x$ 赋一个任意值，枚举 $l$，利用 $\text{map}$ 求出满足条件的 $r$ 即可。

---

