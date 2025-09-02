# [ABC322G] Two Kinds of Base

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc322/tasks/abc322_g

非負整数列 $ S=(S_1,S_2,\dots,S_k) $ と整数 $ a $ に対して、以下のように関数 $ f(S,a) $ を定義します。

- $ f(S,a)\ =\ \sum_{i=1}^{k}\ S_i\ \times\ a^{k\ -\ i} $
 
例えば、$ f((1,2,3),4)\ =\ 1\ \times\ 4^2\ +\ 2\ \times\ 4^1\ +\ 3\ \times\ 4^0\ =\ 27,f((1,1,1,1),10)\ =\ 1\ \times\ 10^3\ +\ 1\ \times\ 10^2\ +\ 1\ \times\ 10^1\ +\ 1\ \times\ 10^0\ =\ 1111 $ です。

正整数 $ N,X $ が与えられます。以下の条件を全て満たす非負整数列 $ S=(S_1,S_2,\dots,S_k) $ と正整数 $ a,b $ の組 $ (S,a,b) $ の個数を $ 998244353 $ で割ったあまりを求めてください。

- $ k\ \ge\ 1 $
- $ a,b\ \le\ N $
- $ S_1\ \neq\ 0 $
- $ S_i\ <\ \min(10,a,b)(1\ \le\ i\ \le\ k) $
- $ f(S,a)\ -\ f(S,b)\ =\ X $

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 10^9 $
- $ 1\ \le\ X\ \le\ 2\ \times\ 10^5 $
- 入力は全て整数
 
### Sample Explanation 1

$ (S,a,b)=((1,0),4,2),((1,1),4,2),((2,0),4,3),((2,1),4,3),((2,2),4,3) $ の $ 5 $ 通りが条件を満たします。

## 样例 #1

### 输入

```
4 2```

### 输出

```
5```

## 样例 #2

### 输入

```
9 30```

### 输出

```
31```

## 样例 #3

### 输入

```
322322322 200000```

### 输出

```
140058961```

# 题解

## 作者：rzh01014 (赞：5)

## [ABC322G](https://www.luogu.com.cn/problem/AT_abc322_g)
### 前言
MnZn第一次出题解。
### 题目描述
> 有个序列 $S=(S_1,S_2,S_3,…,S_n)$。   
定义函数 $f(S,a)=\sum\limits_{i=1}^{k}S_i \cdot a^{k-i}$。   
给定 $N,X$，求所有满足 $F(S,a,b)=X$ 的三元组数量。  
$F(S,a,b)=f(S,a)-f(S,b)$。

### 做法
定义 $F(S,a,b)$ 的结果为 $ans$，$ans=\sum\limits_{i=1}^{k}S_i \times(a^{k-i}-b^{k-i})$。  
对于 $a^{k}-b^{k}$，可以化成 $(a-b)\sum\limits_{i=0}^{k-1}a^{k-i-1}b^{i}$ 的形式，因此可以发现：$(a-b)|ans$。  
不难发现 $ans$ 是关于 $k$ 指数级增长的，故 $k$ 的范围不会很大，小于 $18$。
>证明如下：  
定义 $ans_i$ 为 $k=i$ 时的结果，令 $sum_i=\sum\limits_{j=1}^{i}(a-b)\times s_i \times b^{j-i}$。  
易发现 $ans_i=a \times ans_{i-1}-sum_i$。  

因为本题的 $k$ 的数据范围不大，因此可以分类讨论 $k$ 的范围。

- #### $k=2$ 的情况：
	可以考虑固定 $S_1$。在此之下，要满足 $a-b=\frac {X}{S_1}$。对于 $a,b,S_2$ 要满足：
	
	- $S_1 < b$
	- $a\leq N$
	- $S_2\leq \min(9,a,b)$    
	
	对于每一个 $b$，$a$ 是唯一确定的，因此只需要对所有的 $b$ 枚举并求和 $\min(10,b)$，其中 $S_1 < b \leq N-\frac{X}{S_1}$，可以在 $O(1)$ 的复杂度确定。
- #### $k \geq 3$ 的情况：
	由于 $S_1 \neq 0$，这代表 $a^{k-1}-b^{k-1} \leq X$。满足此条件的二元组 $(a,b)$，有 $620787$ 组。   
	前面已证 $a^{k-i}-b^{k-i}\equiv 0\pmod{a-b}$，此时令 $s=a-b$，由于需要 $a^2-b^2 \leq X$，把 $s=a-b$ 代入得 $s^2-2bs \leq X$。
	因此有 $X\log X$ 数量级的组合情况。  
	求解组合 $(a,b)$，最先想到的是动规，把计算 $S$ 的方案当作背包问题，每一件物品的代价为 $a^{k-i}-b^{k-i}$。   
	但枚举背包状态的复杂度是不能接受的，因此需要优化。   
	事实上满足条件的 $S$ 最多只有一个。
	>证明如下：   
	对于所有 $k\geq 1$，有 $a^{k}-b^{k}>(b-1)\sum\limits_{i=0}^{k-1}a^i-b^i$，该式可用归纳法证明。  
	因此在求答案时只能贪心地从 $S$ 中减去 $a^k-b^k$，故 $S$ 是唯一的，且存在性可以在 $O(\log X)$ 的时间内确定。
	
	因此在 $k\geq3$ 的情况可以在 $O(X\log^2X)$ 的时间内解决。又因 $k$ 很小，且满足条件的 $(a,b)$ 较少，因此复杂度是可以接受的。

因此该问题是由 $k=2$ 和 $k\geq 3$ 的情况加起来，总复杂度在 $O(X\log^2X)$ 级别。

### Code
```cpp
#include <bits/stdc++.h>
#define int long long
typedef long long ll;
using namespace std;
const int N=2e5+5,mod=998244353;
int n;
ll ans=0,x;
inline ll ksm(int x,ll y) {
	ll ret=1;
	while(y) {/*这里不能取模，此时是求a^k-b^k是否符合要求，若取模了会使答案不正确*/
		if(y&1) {
			ret=ret*x;
		}
		x=x*x;
		y>>=1;
	}
	return ret;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>x;
	for(int s=1; s<=sqrt(x); s++) {/*k=2的情况*/
		if(x%s) continue;
		if(s<10) {
			for(int a=s+1+(x/s); a<=n; a++) {
				int b=a-(x/s);
				if(b>=10) break;
				ans=(ans+b)%mod;
			}
			if(n-(x/s)>=10) ans=(ans+10*(n-(x/s)-9)%mod)%mod;
		}
		if(s*s!=x&&x/s<10) {
			for(int a=x/s+s+1; a<=n; a++) {
				int b=a-s;
				if(b>=10) break;
				ans=(ans+b)%mod;
			}
			if(n-s>=10) ans=(ans+10*(n-s-9)%mod)%mod;
		}
	}
	for(int k=3; k<=18; k++) {/*枚举k>2*/
		for(int a=1; a<=n; a++) {
			if(ksm(a,k-1)-ksm(a-1,k-1)>x) break;
			for(int s=1; s<a; s++) {
				int b=a-s;
				if(ksm(a,k-1)-ksm(b,k-1)>x) break;
				int v=x,flag=1;
				for(int i=1; i<k; i++) {
					int noww=ksm(a,k-i)-ksm(b,k-i);
					if(v/noww>=min(10ll,min(a,b))) {
						flag=0;
						break;
					}
					v=(v%noww);
				}
				if(flag&&!v) ans=(ans+min(10ll,min(a,b)))%mod;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：henrytb (赞：3)

观察到 $(a - b) \mid (a^k - b^k)$，又因为 $X = \sum_{i =  1}^{k}S_i(a^{k - i} - b^{k - i})$，每一项都是 $a - b$ 的倍数，因此可以枚举 $X$ 的约数 $a - b$。

枚举 $a - b$ 之后，$k = 2$ 的情况是容易的。只需要特殊处理 $\le 9$ 的 $b$ 即可。

对于 $k \ge 3$ 的情况，$a^2 - b^2 \le X$，这便允许了我们在可接受的复杂度内枚举 $a, b$。

知道 $a, b$ 以后，相当于要知道 $X$ 拆成 $a^k - b^k, a^{k - 1} - b^{k - 1}, \ldots, a - b$ 的方案数（当然最后还要考虑随意的 $a^0 - b^0 = 0$ 这一位）。我是乱搞哥，所以我使用了**背包**。背包复杂度肯定炸了，于是我用 `map` 存状态，每次只访问有用状态，然后跑得飞快啊！

不当乱搞哥的话，你会发现从大到小贪心地取就是唯一方案（或者没有方案）。简单证一下：

需证：

$$\forall k, a^k - b^k > (b - 1)\sum_{i = 0}^{k - 1} a^i - b^i$$

那么只需证

$$a^k > a^{k - 1}b - a^{k - 1} + (b - 1)\sum_{i = 0}^{k - 2} a^i - b^i$$

由于 $a > b$，那么 $a^k > a^{k - 1}b$，因此后边只需要 $< 0$ 即可得证，因此我们需要证

$$a^{k - 1} > (b - 1)\sum_{i = 0}^{k - 2} a^i - b^i$$

证一个充分条件

$$a^{k - 1} - b^{k - 1} > (b - 1)\sum_{i = 0}^{k - 2} a^i - b^i$$

即可。发现和需证的东西形式一致，因此可以归纳。

所以从大到小贪心取来判断就可以了！不需要背包。这样复杂度就很对了。

代码（背包乱搞）：

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 2e5 + 5;
const int mod = 998244353;
int n, x, ans = 0;
vector<int> tq;
map<int, int> f[35];
inline void calc(int d) {  // d = a - b
    if (n <= d) return;
    // k = 2
    rep(b, 1, 9) {
        int a = b + d;
        if (a > n) break;
        if (x / d >= b) continue;
        (ans += b) %= mod;
    }
    int rem = max(n - d - 9, 0ll);
    if (x / d < 10) (ans += rem * 10 % mod) %= mod;
    // er fen a^2 - b^2 <= x
    int l = 1, r = n - d;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if ((mid + d) * (mid + d) - mid * mid <= x) l = mid;
        else r = mid - 1;
    }
    if ((l + d) * (l + d) - l * l > x) return;
    int cnt = 0, sz = x / d;
    rep(b, 1, l) {
        int a = b + d;
        tq.clear(); cnt = 0;
        __int128 resa = a, resb = b, td = resa - resb; 
        while (td <= x) {
            tq.emplace_back(td / d); ++cnt;
            resa *= a; resb *= b; td = resa - resb;
        }
        reverse(tq.begin(), tq.end());
        rep(i, 1, cnt) f[i].clear();
        f[0][0] = 1;
        rep(i, 1, cnt) {
            for (auto &[j, res]: f[i - 1]) {
                int to = min(b, 10ll) - 1;
                rep(k, 0, to) {
                    int too = j + k * tq[i - 1];
                    if (too > sz) break;
                    f[i][too] = (f[i][too] + res) % mod; 
                }
            }
        }
        int res = f[cnt][sz];
        if (sz < min(b, 10ll)) (res += mod - 1) %= mod;
        // zv hz * min(b, 10)
        (ans += res * min(b, 10ll) % mod) %= mod;
    }
}
signed main() {
    scanf("%lld%lld", &n, &x);
    for (int d = 1; d * d <= x; ++d) {
        if (x % d == 0) {
            calc(d);
            if (d * d != x) calc(x / d);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Semorius (赞：3)

[也许更好的阅读体验](https://www.cnblogs.com/Semorius/p/17744863.html)


#### 思路

首先，可以把数列 $S$ 分别看做是 $k$ 位 $a$ 进制数和 $k$ 位 $b$ 进制数每一位上的值，记这两个数分别记作 $A$ 和 $B$。题目中的最后一个限制就等价于 $A-B=X$，其中 $X$ 是十进制意义下的。

显然 $f(S,a) - f(S,b) = \sum_{i=1}^{k} S_i \times (a^{k - i}-b^{k - i})$，由于 $X$ 为正整数，故 $a > b$。

所以上式的这一部分 $a^{k - i}-b^{k - i}$ 随 $i$ 增大单调递减，当 $i=k$ 时，$a^{0}-b^{0} = 0$，即 $S_k$ 的取值不会对 $A-B$ 的值产生影响。

考虑最朴素的做法，枚举 $k,a,b$，并构造一种合理的 $S$ 使得满足上述限制。可以证明，如果存在这样的一个 $S$，那么 $(S_1,S_2,\dots,S_{k-1})$ 是唯一的。

>证明：假设从 $i=1$ 开始依次填 $S_i$，设 $X'$ 表示 $X$ 减去 $S_1$ 至 $S_{i-1}$ 的总贡献后的值， $S_{i+1}$ 到 $S_k$ 能产生的最大贡献为 $C$，$S_i=1$ 时仅 $S_i$ 产生的贡献为 $D$。能得到：$D=a^{k-i}-b^{k-i}=(a-1)\times\sum_{j=i+1}^{k} a^{k-j}-(b-1)\times\sum_{j=i+1}^{k} b^{k-j} > (b-1)\times(\sum_{j=i+1}^{k} a^{k-j}-\times\sum_{j=i+1}^{k} b^{k-j})$。所以，当 $X'>C$ 时，只有 $S_i= \left \lfloor \frac{X'}{a^{k-i} - b^{k-i}}\right \rfloor $ 时才有可能满足条件。而当 $X'\le C$ 时，$S_i$ 只能等于 $0$。如此贪心地往下填 $S$ 的每一位，一直到 $S_{k-1}$，能确定一组唯一的 $(S_1,S_2,\dots,S_{k-1})$。

这样在固定 $k,a,b$ 的情况下可以 $O(k)$ 地统计答案，$k$ 的范围是 $O(\log X)$ 级别，但 $a,b$ 的范围却是与 $n$ 同阶的。

其实有效的 $a,b$ 远没有这么多。

由于 $S_1 \neq 0$，这等价于 $a^{k-1}-b^{k-1} \le X$，可以发现，当 $k \ge 3$ 时，满足这个条件的二元组 $(a,b)$ 是很少的（当 $N=10^9,X=2\times 10^5$ 时，只有 $620787$ 组），每一次可以用 $O(\log X)$ 的时间统计答案。

而当 $k = 2$ 时，$X = (a-b)\times S_1$，用 $O(\sqrt x)$ 的时间统计答案即可。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define l(x) x<<1
#define r(x) x<<1|1
#define mpr make_pair
//mt19937_64 ra(time(0) ^ (*new char));
const ll SIZE = 200005;
const ll mod = 998244353;
ll n, X, ans;

inline ll rd(){
	ll f = 1, x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f*x;
}

ll power(ll x, ll y){
	ll jl = 1;
	while(y){
		if(y & 1) jl = (jl * x);
		x = (x * x);
		y >>= 1;
	}
	return jl;
}

int main(){
	n = rd(), X = rd(); ll cnt = 0;
	for(ll i = 1; i*i <= X; i++){
		if(X%i == 0){
			if(i < 10){
				for(ll a = i+1+(X/i); a <= n; a++){
					ll b = a-(X/i);
					if(b >= 10) break;
					ans = (ans + min(10ll, b)) % mod;
				}
				if(n-(X/i) >= 10){
					ans = (ans + (10 * (n-(X/i)-10+1)) % mod) % mod;
				}
			}
			if(i != (X/i) && (X/i) < 10){
				for(ll a = (X/i)+1+i; a <= n; a++){
					ll b = a-i;
					if(b >= 10) break;
					ans = (ans + min(10ll, b)) % mod;
				}
				if(n-i >= 10){
					ans = (ans + (10 * (n-i-10+1)) % mod) % mod;
				}
			}
		}
	}
	for(ll k = 3; k <= 20; k++){
		for(ll a = 1; a <= n; a++){
			if(power(a, k-1)-power(a-1, k-1) > X) break;
			for(ll b = a-1; b >= 1; b--){
				if(power(a, k-1)-power(b, k-1) > X) break;
				ll jl = X; bool flag = 1;
				for(ll i = 1; i < k; i++){
					if(jl / (power(a, k-i)-power(b, k-i)) >= min(10ll, min(a, b))) flag = 0;
					jl = (jl % (power(a, k-i)-power(b, k-i)));
				}
				if(jl == 0 && flag){
					ans = (ans + min(10ll, min(a, b))) % mod;
				}
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：Filberte (赞：3)

官方题解/洛谷题解没看懂，这里提供一个偏向于数据点分治的思路。当 $k = 14$ 时，$3^{13}- 2^{13} > 2\times 10^5$，已经超过了 $X$ 的最大值，因此 $k < 14$。又 $x \ge 1$，所以 $k = 1$ 无解，只需计算出 $k = 2\sim12$ 的解就可以了。

### $k = 2$

相当于 $S$ 只有两个数，且对于答案有影响的只有 $S_1$，也就是说 $S_1(a - b) = X$，因此 $S_1\mid X$，直接枚举 $S_1$ 和 $S_0$，同时要满足 $S_1 \mid X$，又因为 $\max(S_1,S_0) < b < a \le N$，且 $a - b = \dfrac{X}{S_1}$，直接统计答案即可。

此情况的枚举量在 $10 \times 10 = 100$ 的级别。

### $k = 3$

注意到 $100001^3 - 100000^3 > 2\times 10^5$，因此 $a \le 10^5$，因为 $S_0$ 对答案无影响，所以枚举 $S_2,S_1$，再枚举 $a$，因为 $S_2(a^2-b^2) + S_1(a - b) = X$，解这个二次方程可以解出 $b$ 的值（得有正整数解，要注意判断一下）。在满足 $\max(S_2,S_1) < b < a$ 的情况下，$S_0$ 有 $\min(10,b)$ 种选法，把答案加上这个数就行了。

这个情况的枚举量在 $10 \times 10 \times 10^5 = 10^7$ 的级别。

### $k \ge 4$

同理可以分析出 $a \le 300$，先枚举 $S$ 的位数，然后枚举 $a$ 的值，再枚举 $b$ 的值，然后判断一下是否有一组解能满足这个条件即可，首先是要能凑出 $X$（从高往低位枚举，就像二进制拆位一样）要特判一下首位为 $0$ 的情况，最后依然是取 $S_0 < \min(10,b)$ 的解即可。

这个情况的枚举量远远达不到 $12 \times 300 \times 300 \times12 \times 12 = 1.5 \times 10^9$ 级别。但在分析时，我们时按照以 $2$ 和 $3$ 为进制来分析的，但实质上随着进制的增长，该进制下的位数缩减得很快，有许多状态不合法会提前退出，同时此算法常数很小，可以通过。



```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int solve2(int n, int x){
    int ret = 0;
    for(int m1 = 1;m1 < 10;m1++)
        for(int m2 = 0;m2 < 10;m2++) if(x % m1 == 0){
            ret = (ret + max(0LL, n - x / m1 - max(m1, m2))) % mod;
        }
 //   cout << ret << "\n";
    return ret;
}
int solve3(int n, int x){
    int ret = 0, mx = 100000;           
    for(int m2 = 1;m2 <= 9;m2++)
        for(int m1 = 0;m1 <= 9;m1++)
            for(int a = max(m1,m2) + 2;a <= min(n, mx);a++){ // max(m1,m2) < b < a <= min(n, mx)
                /*  m2(a^2-b^2) + m1(a-b) = X
                    -m2^2 b^2 - m1b + (m2a^2 + m1a - x) = 0
                */
                int delta = (m1 * m1) + 4 * m2  * (m2 * a * a + m1 * a - x);
                if(delta < 0) continue;
                int gd = round(sqrt(delta));
                if(gd * gd != delta || (m1 - gd) % (-2 * m2)) continue;
                int b = (m1 - gd) / (-2 * m2);      
                // 二次方程求解
                if(max(m2, m1) < b && b < a) ret = (ret + min(10LL, b)) % mod; //最后个位乱填，但是不能比 min(10,b) 大
            } 
 //   cout << ret << "\n";
    return ret;
}
int solve4up(int n, int x){
    int ret = 0, mx = 300;
    for(int len = 4;len <= 12;len++) // 3^13 - 2^13 > 2e5
        for(int a = 3;a <= min(n, mx);a++)
            for(int b = 2;b < a;b++){
                int t = x;bool flag = 1;
                for(int w = len - 1;w;w--){ //从高往低枚举每一位
                    bool ok = 1;
                    int big = 1, sma = 1;
                    for(int i = 1;i <= w;i++){
                        big *= a;
                        sma *= b;
                        if(big - sma > t){ok = 0;break;}
                    }
                    int c = big - sma;
                    int s = ok ? t / c : 0;
                    if(s >= min(10LL, b) || (w == len - 1 && !s)){flag = 0;break;}
                    t -= c * s;
                } //某一位
                if(!flag || t) continue;
                ret = (ret + min(10LL, b)) % mod;
            }
 //   cout << ret << "\n";
    return ret;
}
signed main(){
    int n, x;
    cin >> n >> x;
    cout << ((solve2(n, x) + solve3(n, x)) % mod + solve4up(n, x)) % mod;
    return 0;
}
```

---

## 作者：Zi_Gao (赞：2)

## 前言

没人写题解，研究了好久，来总结一下。正巧还没做过这种套路。

## 正文

### 0x00 题目分析

转化一下题目变成，给定了 $N,x$ 两个正整数，定义一个函数 $F\left(a,b,S\right)$，有：

$$F\left(a,b,S\right)=\sum_{i=0}^{k-1}S_i\times\left(a^{i}-b^{i}\right)$$

其中 $a,b$ 是两个正整数，满足 $a,b\le N,a\gt b$；$S$ 是一个下标 $0$ 起、元素个数为 $k$ 的数组，满足 $S_{k-1}\not=0$ 且 $0\leq S_{i}\lt\min\left(a,b,10\right)$。现在求对于 $a,b,S$ 使得 $F\left(a,b,S\right)=x$。

发现这玩意很像是一个特殊进制的数，不妨把 $i=0,1,\cdots,k-1$ 依次看做这个数的低位到高位，有一下性质符合和一个进制很像：

1. 随着 $S$ 的长度增长，$F$ 函数增长是指数级别的，即当 $S$ 的长度为 $k$ 时，$F\left(a,b,S\right)$ 函数是 $\mathcal{O}\left(a^k\right)$ 的。

2. 对于任意满足题目条件的 $S$，若 $x\gt0$，有 $F\left(a,b,S\right)\lt x\times\left(a^{k}-b^{k}\right)$。就像是进制填数一样，高位填的数一定是决定性的，后面永远追不上，证明显然拆开 $\left(a^{i}-b^{i}\right)$ 这一坨即可。

### 0x01 开始解题

根据第一条性质可得，对于任意会成为答案的 $k$，其级别是 $\mathcal{O}\left(\log x\right)$；根据第二条性质得，对于每一对确定的 $a,b,k$ 若存在解，只有唯一的 $S$ 能满足要求。

不妨考虑暴力枚举 $a,k$ 两个数，然后确定一个 $b$。那么对于一个 $b$，有一个基本的要求是 $a^{k-1}-b^{k-1}\leq x$ 不然最高位只能填 $0$，但是不能有前导 $0$，理性分析一下这个要求 $b^{k-1}\geq a^{k-1}-x$ 则，$b$ 下界是 $\mathcal{O}\left(a-\Delta\right)$ 的，而且 $\Delta$ 上界是 $\mathcal{O}\left(x^{\frac{1}{k-1}}\right)$，并且 $b\le a$ 反正这玩意小得很就对了，$b$ 取值范围大小肯定不超过根号。

这里枚举一下满足这些条件的 $a,b,k$ 就可以了最多枚举 $\mathcal{O}\left(n\sqrt{x}\right)$。接下来就是随便像是填一个其他进制的数一样把 $x$ 填进去，看能不能填下就可以了。

### 0x02 完了吗？

注意对于 $k=2$ 情况要特殊处理，由于 $i=0$ 时 $a^{i}-b^{i}$ 是 $0$，那么可以乱填；当 $i=1$ 时算出 $\left(a-b\right)\times S=x$ 的方案数即可。

其他情况，同样由于 $i=0$ 时 $a^{i}-b^{i}$ 是 $0$ 所以可以乱填，贡献答案有个系数注意计算。

最终时间复杂度 $\mathcal{O}\left(n\sqrt{x}\log^2 x\right)$，很多时候跑不满，常数很小。

### 0x03 代码实现

注意所谓乱填 $S_0$ 也不是乱填，要满足那几条条件。

AC CODE

``` cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

long long pw[200010][23];

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,k;
    register long long a,b,S;
    const long long mod=998244353;
    register long long res=0,tmp,now;
    long long n=read();
    long long x=read();

    //k=2
    for(S=1;S<=std::min(x,9ll);++S)
        if(!(x%S)){
            for(a=S+1+(x/S);a<=n;++a){//b<10
                b=a-x/S;
                if(b>=10) break;
                (res+=b)%=mod;
            }
            if(n-(x/S)>=10) (res+=10*(n-((x/S)+10)+1))%=mod;//b>=10   a in [x/S+10,n] , b in [10,...]
        }

    //otherwise
    for(a=1;a<=x;++a) pw[a][2]=a;
    for(k=3;k<=22;++k){
        for(a=1;a<=std::min(x-1,n);++a){
            tmp=1;
            for(i=1;i<k&&tmp<=(1e13);++i) tmp*=a;
            if(tmp>(1e13)) break;
            pw[a][k]=tmp;//pw[a][k] = a^(k-1) , f = pw[a][k]*S1+pw[a][k-1]*S2 ...
            for(b=a-1;b;--b){
                //check
                if(pw[a][k]-pw[b][k]>x) break;
                now=x;
                for(i=k;i>1;--i)//S{k-i+1} = now mod pw[a][i]-pw[b][i]
                    if(now/(pw[a][i]-pw[b][i])>=std::min(10ll,b)) goto loop;
                    else now%=pw[a][i]-pw[b][i];
                if(now) goto loop;
                (res+=std::min(10ll,b))%=mod;
                loop:;
            }
        }
    }

    print(res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 总结

抓住题目中这个东西“进制”这样的性质解题，熟悉套路。

p.s. 本文可能有笔误，看不懂得可以问我。

---

