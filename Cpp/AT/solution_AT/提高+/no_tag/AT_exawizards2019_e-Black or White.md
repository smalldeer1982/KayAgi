# Black or White

## 题目描述

[problemUrl]: https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_e

今日のすぬけ君のおやつは $ B $ 個の黒いチョコレートと $ W $ 個の白いチョコレートです。

すぬけ君は以下の手続きをチョコレートがなくなるまで繰り返します。

- 黒か白を等確率で選び、選んだ色のチョコレートが存在するなら $ 1 $ つ食べる。

$ 1 $ 以上 $ B+W $ 以下の各整数 $ i $ について、すぬけ君が $ i $ 番目に食べたチョコレートの色が黒である確率を求めてください。 これらの確率は有理数となることが示せます。これらを注記で述べるように modulo $ 10^{9}+7 $ で出力してください。

## 说明/提示

### 注記

有理数を出力する際は、まずその有理数を分数 $ \frac{y}{x} $ として表してください。ここで、$ x,\ y $ は整数であり、$ x $ は $ 10^9\ +\ 7 $ で割り切れてはなりません (この問題の制約下で、そのような表現は必ず可能です)。そして、$ xz\ \equiv\ y\ \pmod{10^9\ +\ 7} $ を満たすような $ 0 $ 以上 $ 10^9\ +\ 6 $ 以下の唯一の整数 $ z $ を出力してください。

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ B,W\ \leq\ 10^{5} $

### Sample Explanation 1

\- チョコレートを食べる順序としてありうるものは以下の $ 3 $ 通りで、そのような食べ方が生じる確率はそれぞれ $ \frac{1}{2},\ \frac{1}{4},\ \frac{1}{4} $ です。 - 白、黒、黒 - 黒、白、黒 - 黒、黒、白 - よって、$ 1 $ 番目、$ 2 $ 番目、$ 3 $ 番目に食べたチョコレートが黒である確率はそれぞれ $ \frac{1}{2},\frac{3}{4},\frac{3}{4} $ です。

### Sample Explanation 2

\- それぞれ $ \frac{1}{2},\frac{1}{2},\frac{5}{8},\frac{11}{16},\frac{11}{16} $ です。

## 样例 #1

### 输入

```
2 1```

### 输出

```
500000004
750000006
750000006```

## 样例 #2

### 输入

```
3 2```

### 输出

```
500000004
500000004
625000005
187500002
187500002```

## 样例 #3

### 输入

```
6 9```

### 输出

```
500000004
500000004
500000004
500000004
500000004
500000004
929687507
218750002
224609377
303710940
633300786
694091802
172485353
411682132
411682132```

# 题解

## 作者：rui_er (赞：2)

设 $P_b(k),P_w(k)$ 表示已经吃了 $k$ 块巧克力，把所有黑/白巧克力都吃光了的概率。枚举最后一块黑/白巧克力被吃的时间，容易得到：

$$
\begin{aligned}
P_b(k)&=\sum_{i=1}^k\frac{\binom{i-1}{b-1}}{2^i}\\
P_w(k)&=\sum_{i=1}^k\frac{\binom{i-1}{w-1}}{2^i}\\
\end{aligned}
$$

显然可以 $O(b+w)$ 递推出来。设 $P_a(k)=1-P_b(k)-P_w(k)$，则第 $k$ 个答案为 $P_w(k-1)+\frac{P_a(k-1)}{2}$。

```cpp
// Problem: Black or White
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_exawizards2019_e
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
    return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
    unsigned int x;
    Modint() = default;
    Modint(unsigned int x) : x(x) {}
    friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
    friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
    friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
    friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
    friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
    friend Modint operator/(Modint a, Modint b) {return a * ~b;}
    friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
    friend Modint operator~(Modint a) {return a ^ (mod - 2);}
    friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
    friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
    friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
    friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
    friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
    friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
    friend Modint& operator++(Modint& a) {return a += 1;}
    friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
    friend Modint& operator--(Modint& a) {return a -= 1;}
    friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
    friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
    friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<1000000007> mint;
const int N = 2e5 + 5, mod = 1000000007;
const mint inv2 = (mod + 1) / 2;

int b, w;
mint fac[N], ifac[N];

inline mint C(int n, int m) {
    if(n < 0 || m < 0 || n < m) return 0;
    return fac[n] * ifac[m] * ifac[n - m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> b >> w;
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    rep(i, 2, b + w) {
        fac[i] = fac[i - 1] * i;
        ifac[i] = (mod - mod / i) * ifac[mod % i];
    }
    rep(i, 2, b + w) ifac[i] *= ifac[i - 1];
    mint Pb = 0, Pw = 0, now = 1;
    rep(i, 0, b + w - 1) {
        Pb += C(i - 1, b - 1) * now;
        Pw += C(i - 1, w - 1) * now;
        mint Pa = 1 - Pb - Pw;
        cout << Pw + Pa * inv2 << endl;
        now *= inv2;
    }
    return 0;
}
```

---

## 作者：MadokaKaname (赞：0)

### 我甚至不知道这是什么比赛qaq


## 题目大意

有 $b$ 和 $w$ 两个数，每一次选择其中一个数减 1，直到两个数都变成 0。选择的规则如下：

如果两个数都大于 0，则等概率选择一个；

否则选择比 0 大的数。

求每一时刻取 1 的概率，对 $10^9+7$ 取模。
## solution

考虑将每一时刻时的状态分成 3 种：$b$ 和 $w$ 都有剩余，只剩下 $b$，只剩下 $w$。

第一种情况只需要将概率乘上 2 的逆元即可，但是概率比较难求。我们先放一边。

第二种和第三种求概率的本质是相同的，只不过答案只需加上第二种。

考虑第二种和第三种概率的求法。以第二种为例，发现取完的时刻为 $t$ 时的概率为 $\large f_i=\binom{t-1}{b-1}\times 2^t$，时刻为 $t$ 时取完的总概率即为 $\sum_{i=1}^{t}f_i$，递推即可。

显然求出后面两种概率的之后可以反推出第一种的概率。

时间复杂度 $O(b+w)$。

### code
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL n,i,j,k,m;
LL val[200005];
LL pow2[200005];
LL p1[200005],p2[200005];
const LL mod=1000000007;
void exgcd(LL a,LL b,LL &x,LL &y,LL &val){
	if(b==0){
		val=a;
		x=1;
		y=0;
	}
	else{
		exgcd(b,a%b,y,x,val);
		y-=x*(a/b);
	}
}
LL inv(LL x){
	LL tmp1=0,tmp2=0,tmp3=0;
	exgcd(x,mod,tmp1,tmp2,tmp3);
	return (tmp1%mod+mod)%mod;
}
LL C(LL x,LL y){
	return val[x]*inv(val[y])%mod*inv(val[x-y])%mod;
}
int main() {
	val[0]=1;
	pow2[0]=1;
	for(i=1;i<=200000;i++){
		val[i]=val[i-1]*i;
		pow2[i]=pow2[i-1]<<1ll;
		val[i]%=mod;
		pow2[i]%=mod;
	}
    scanf("%lld%lld",&n,&m);
    p1[m]=inv(pow2[m]);
	for(i=m+1;i<n+m;i++){
		p1[i]=p1[i-1]+C(i-1,m-1)*inv(pow2[i])%mod;
		p1[i]%=mod;
	}
	p2[n]=inv(pow2[n]);
	for(i=n+1;i<n+m;i++){
		p2[i]=p2[i-1]+C(i-1,n-1)*inv(pow2[i])%mod;
		p2[i]%=mod;
	}
    for(i=0;i<n+m;i++){
    	LL p=1,ans=0;
    	if(i>=m){
    		p-=p1[i];
    		p=(p%mod+mod)%mod;
    		ans+=p1[i];
		}
		if(i>=n){
			p-=p2[i];
			p=(p%mod+mod)%mod;
		}
		ans+=p*inv(2);
		printf("%lld\n",ans%mod);
	}
	return 0;
}

```






---

