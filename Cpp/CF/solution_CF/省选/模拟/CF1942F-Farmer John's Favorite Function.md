# Farmer John's Favorite Function

## 题目描述

[ΩΩPARTS - Camellia](https://soundcloud.com/user-838515264/camellia-parts-ooparts)

⠀



Farmer John has an array $ a $ of length $ n $ . He also has a function $ f $ with the following recurrence:

- $ f(1) = \sqrt{a_1} $ ;
- For all $ i > 1 $ , $ f(i) = \sqrt{f(i-1)+a_i} $ .

Note that $ f(i) $ is not necessarily an integer.

He plans to do $ q $ updates to the array. Each update, he gives you two integers $ k $ and $ x $ and he wants you to set $ a_k = x $ . After each update, he wants to know $ \lfloor f(n) \rfloor $ , where $ \lfloor t \rfloor $ denotes the value of $ t $ rounded down to the nearest integer.

## 说明/提示

In the first test case, the array after the first update is $ [4, 14, 0, 7, 6] $ . The values of $ f $ are:

- $ f(1)=2 $ ;
- $ f(2)=4 $ ;
- $ f(3)=2 $ ;
- $ f(4)=3 $ ;
- $ f(5)=3 $ .

Since $ \lfloor f(5) \rfloor = 3 $ , we output $ 3 $ .

The array after the second update is $ [3, 14, 0, 7, 6] $ . The values of $ f $ , rounded to $ 6 $ decimal places, are:

- $ f(1)\approx 1.732051 $ ;
- $ f(2)\approx 3.966365 $ ;
- $ f(3)\approx 1.991573 $ ;
- $ f(4)\approx 2.998595 $ ;
- $ f(5)\approx 2.999766 $ .

Since $ \lfloor f(5) \rfloor = 2 $ , we output $ 2 $ .

## 样例 #1

### 输入

```
5 6
0 14 0 7 6
1 4
1 3
2 15
4 1
5 2
5 8```

### 输出

```
3
2
3
2
1
3```

## 样例 #2

### 输入

```
15 10
3364 1623 5435 7 6232 245 7903 3880 9738 577 4598 1868 1112 8066 199
14 4284
14 8066
6 92
6 245
2 925
2 1623
5 176
5 6232
3 1157
3 5435```

### 输出

```
16
17
16
17
16
17
16
17
16
17```

## 样例 #3

### 输入

```
2 2
386056082462833225 923951085408043421
1 386056082462833225
1 386056082462833224```

### 输出

```
961223744
961223743```

## 样例 #4

### 输入

```
13 10
31487697732100 446330174221392699 283918145228010533 619870471872432389 11918456891794188 247842810542459080 140542974216802552 698742782599365547 533363381213535498 92488084424940128 401887157851719898 128798321287952855 137376848358184069
3 283918145228010532
3 283918145228010533
1 2183728930312
13 1000000000000000000
10 1000000000000000000
9 1000000000000000000
8 1000000000000000000
7 1000000000000000000
6 1000000000000000000
5 1000000000000000000```

### 输出

```
370643829
370643830
370643829
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000```

# 题解

## 作者：快乐的大童 (赞：12)

### 题意简述
定义 $f_i=\sqrt{f_{i-1}+a_i},f_0=0$。

有 $q$ 次操作，每次操作单点修改一个 $a_i$ 的值，每次修改后求 $\lfloor f_n\rfloor$ 的值。

$n,q\le 2\times10^5,0\le a_i\le 10^{18}$。

### 分析
发现这个 $f_i$ 不是整数非常不利于我们做题，考虑将它变成整数。

令新的 $f'_i=\lfloor f_i\rfloor$，这样的话 $f'_{i+1}=\lfloor\sqrt{f'_i+a_{i+1}}\rfloor=\lfloor\sqrt{f_i-x+a_{i+1}}\rfloor(0\le x<1)$，但是我们发现这个 $x$ 不会影响 $f'_{i+1}=\lfloor\sqrt{f'_i+a_{i+1}}\rfloor$ 的取值，因为 $f'_i+a_{i+1}$ 是整数，加上了 $x$ 也只是改变了小数部分，对整数部分没有影响，所以有 $\lfloor\sqrt{f'_i+a_{i+1}}\rfloor=\lfloor\sqrt{f_i+a_{i+1}}\rfloor$，故 $f'_i=f_i$，$f_i$ 就转化成整数了。下文的 $f_i$ 采用的是新定义，下文的 $f'_i$ 的意义也和此处不同。

直觉发现根号这个东西数字缩小的非常快，通过手玩计算器可以发现 $10^{18}$ 在取六次根号后下取整的值就变成了 $1$，由此当 $n\ge 6$ 时，$a_1$ 的改变只会使 $f_n$ 的值至多变化 $1$。保险起见我把这个阈值开到了 $10$。

考虑如何处理单点修改。将原序列分块，设一个块维护的区间为 $[l,r]$，块内维护 $f_i$ 表示当 $f_{l-1}=0$ 时，$f_r$ 的取值；维护 $g_i$ 表示当 $f_{l-1}\ge g_i$ 时 $f_i$ 的值将会增长 $1$（根据第二个结论，$f_i$ 的值只会至多增长 $1$）。

$f_i$ 的值直接递推就好，求解 $g_i$ 考虑逆推，假设最终的 $f'_r=f_r+1$，$f'_{r-1}$ 的值可以由 $f_r^{'2}-a_r$ 求出，以此类推直到推出 $f'_{l-1}$ 的值，求出的 $f'_{l-1}$ 就是 $g_i$ 的值了。当然你可以二分答案以多一个 log 的代价求出。

每次修改暴力计算块内信息即可，查询的话直接递推，设计算前 $i-1$ 个块后的答案为 $ans$，若 $ans\ge g_i$，则 $ans=f_i+1$，否则 $ans=f_i$。

时间复杂度 $O(n\sqrt n)$，视 $n,q$ 同阶。

注意分块时有可能块长小于阈值（此时第二个结论不成立），对于这种块暴力计算即可。

[code](https://codeforces.com/contest/1942/submission/254977629)

---

## 作者：rui_er (赞：9)

萌萌 F 题，上大分。

首先，如下定义 $g(i)$：

- $g(1)=\lfloor\sqrt{a_1}\rfloor$；
- 对于所有 $i > 1$，$g(i)=\lfloor\sqrt{g(i-1)+a_i}\rfloor$。

也就是将 $f(i)$ 的每一步运算后都向下取整。注意到 $\lfloor f(i)\rfloor=g(i)$ 恒成立，于是我们只需要转而求每次修改后 $g(n)$ 的值，避免了浮点数运算。

将询问离线，对时间轴（操作序列）维护数据结构，按空间轴（序列 $a_i$）下标从小到大扫描线。每扫描到一个新的下标 $i$，需要做的操作是将每个时刻的 $g$ 加上对应时刻修改后的 $a_i$，然后将每个时刻的 $g$ 开根号下取整。因此，数据结构需要支持 $n+q$ 次区间加操作和 $n$ 次全局开根号下取整操作，并在最后输出每个位置的值。

可以使用势能线段树维护：每个节点维护区间最小值、最大值、区间加法标记。区间加操作是平凡的，全局开根号下取整操作直接暴力递归，直到 $mx-mn=\lfloor\sqrt{mx}\rfloor-\lfloor\sqrt{mn}\rfloor$，此时打区间加法标记即可。也可以使用分块等维护。

```cpp
// Problem: F. Farmer John's Favorite Function
// Contest: Codeforces - CodeTON Round 8 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1942/problem/F
// Memory Limit: 256 MB
// Time Limit: 5000 ms
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

const ll N = 2e5 + 5;

ll n, m, a[N], qk[N], qx[N];
vector<tuple<ll, ll>> qs[N];

inline ll mysqrt(ll x) {
    ll k = sqrtl(x);
    while(k * k > x) --k;
    while((k + 1) * (k + 1) <= x) ++k;
    return k;
}

struct SegTree {
    ll mx[N << 2], mn[N << 2], tag[N << 2];
    #define lc(u) (u << 1)
    #define rc(u) (u << 1 | 1)
    void pushup(ll u) {
        mx[u] = max(mx[lc(u)], mx[rc(u)]);
        mn[u] = min(mn[lc(u)], mn[rc(u)]);
    }
    void pushdown(ll u) {
        tag[lc(u)] += tag[u];
        tag[rc(u)] += tag[u];
        mx[lc(u)] += tag[u];
        mx[rc(u)] += tag[u];
        mn[lc(u)] += tag[u];
        mn[rc(u)] += tag[u];
        tag[u] = 0;
    }
    void rangeadd(ll u, ll l, ll r, ll ql, ll qr, ll k) {
        if(ql > qr) return;
        if(ql <= l && r <= qr) {
            tag[u] += k;
            mx[u] += k;
            mn[u] += k;
            return;
        }
        pushdown(u);
        ll mid = (l + r) >> 1;
        if(ql <= mid) rangeadd(lc(u), l, mid, ql, qr, k);
        if(qr > mid) rangeadd(rc(u), mid + 1, r, ql, qr, k);
        pushup(u);
    }
    void rangesqrt(ll u, ll l, ll r, ll ql, ll qr) {
        if(ql > qr) return;
        if(l == r) {
            mx[u] = mn[u] = mysqrt(mx[u]);
            return;
        }
        if(ql <= l && r <= qr && mx[u] - mn[u] == mysqrt(mx[u]) - mysqrt(mn[u])) {
            ll diff = mysqrt(mx[u]) - mx[u];
            tag[u] += diff;
            mx[u] += diff;
            mn[u] += diff;
            return;
        }
        pushdown(u);
        ll mid = (l + r) >> 1;
        if(ql <= mid) rangesqrt(lc(u), l, mid, ql, qr);
        if(qr > mid) rangesqrt(rc(u), mid + 1, r, ql, qr);
        pushup(u);
    }
    void print(ll u, ll l, ll r, char ENDPRINT = '\n') {
        if(l == r) {
            cout << mx[u] << ENDPRINT;
            return;
        }
        pushdown(u);
        ll mid = (l + r) >> 1;
        print(lc(u), l, mid, ENDPRINT);
        print(rc(u), mid + 1, r, ENDPRINT);
        pushup(u);
    }
    #undef lc
    #undef rc
}sgt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, m) cin >> qk[i] >> qx[i];
    rep(i, 1, m) qs[qk[i]].emplace_back(qx[i], i);
    rep(i, 1, n) {
        ll lstval = a[i], lstkey = 1;
        for(auto [val, key] : qs[i]) {
            sgt.rangeadd(1, 1, m, lstkey, key - 1, lstval);
            lstval = val;
            lstkey = key;
        }
        sgt.rangeadd(1, 1, m, lstkey, m, lstval);
        // sgt.print(1, 1, m, ' '); cout << endl;
        sgt.rangesqrt(1, 1, m, 1, m);
        // sgt.print(1, 1, m, ' '); cout << endl;
    }
    sgt.print(1, 1, m);
    return 0;
}
```

---

## 作者：IceKylin (赞：3)

提供一种时间复杂度为 $\mathcal{O}(n+q\log n + q\log\log V)$ 的在线做法。

截至目前，笔者做法为 CF [严格次优解](https://codeforces.com/contest/1942/submission/310995137)，卡不动了...

考虑函数 $f_i(x) = \big\lfloor \sqrt{f_{i-1}(x) + a_i}\big\rfloor$，对于两个不同的初始值 $l, r$，迭代 $\mathcal{O}(\log\log V)$ 次后两者之差至多为一，势能分析是容易证明的。

这启示我们将序列分成若干长度为 $B = \mathcal{O}(\log\log V)$ 的块，考虑自变量 $x$ 迭代 $B$ 次后的函数 $\mathcal{F}$，由上文可知 $\mathcal{F_i}(x) = v_i + [x\ge k_i]$，其中 $v_i, k_i$ 的值均可以暴力得到。

容易想到所有 $\mathcal{F}$ 构成半群，所以使用支持单点修改，全局半群信息查询的数据结构即可。

实现使用了非递归线段树。注意到最后一个块并非总是完整的，可以将整个序列向后平移直至其完整，这与原题是等价的。

以上。

---

## 作者：MaxBlazeResFire (赞：3)

本题最重要的 $\rm Observation：$直接把 $f_i$ 定义成 $\displaystyle\lfloor\sqrt{f_{i-1}+a_i}\rfloor$ 答案直接就是正确的。这样所有 $f$ 就都是整数了。

注意到对一个数 $a_i$ 的修改会在 $i+6$ 处被稀释到 $1$ 以下。于是把序列按照 $6$ 分块。对于一个块 $[l,r]$，记 $v_i$ 表示当 $a_{l-1}=0$ 时 $\displaystyle\lfloor f(r)\rfloor$ 的值，记 $c_i$ 表示最小的 $v$ 使得当 $a_{l-1}=v$ 时 $\lfloor f(r)\rfloor=v_i+1$，不难发现一定存在这样的**整数** $v$，可以二分求得。把每个块当成一个单元放在线段树上维护，单点修改时，可以先暴力二分出对应块的 $v$ 和 $c$，然后对于每一个单元的区间，都有对应的 $v$ 和 $c$，直接维护即可，上推函数复杂度 $O(1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

const int INF = 8000000000000000000ll;

int n,q,a[MAXN],bel[MAXN],st[MAXN],ed[MAXN],Bcnt;

struct node{ int L,R,v,c; }T[MAXN << 2];

inline node operator *( node A , node B ){
	node C; C.L = A.L,C.R = B.R;
	if( A.v >= B.c ) C.v = B.v + 1;
	else C.v = B.v;
	if( A.v < B.c - 1 || A.v >= B.c ) C.c = INF;
	else C.c = A.c;
	return C;
}

inline void update( int t ){
	T[t].v = 0;
	int L = st[T[t].L],R = ed[T[t].R];
	for( int i = L ; i <= R ; i ++ ) T[t].v += a[i],T[t].v = (int)sqrtl( T[t].v );
	int l = 0,r = INF / 8,ans = -1;
	while( l <= r ){
		int mid = ( l + r ) >> 1;
		int res = mid;
		for( int i = L ; i <= R ; i ++ ) res += a[i],res = (int)sqrtl( res );
		if( res > T[t].v ) ans = mid,r = mid - 1;
		else l = mid + 1; 
	}
	if( ans == -1 ) T[t].c = INF;
	else T[t].c = ans;
}

void build( int t , int l , int r ){
	T[t].L = l,T[t].R = r;
	if( l == r ){ update( t ); return; }
	int mid = ( l + r ) >> 1;
	build( t * 2 , l , mid ),build( t * 2 + 1 , mid + 1 , r );
	T[t] = T[t * 2] * T[t * 2 + 1];
}

void modify( int t , int l , int r , int x ){
	if( l == r ){ update( t ); return; }
	int mid = ( l + r ) >> 1;
	if( x <= mid ) modify( t * 2 , l , mid , x );
	else modify( t * 2 + 1 , mid + 1 , r , x );
	T[t] = T[t * 2] * T[t * 2 + 1];
}

signed main(){
	scanf("%lld%lld",&n,&q); int tmp = 0; while( n % 6 != 0 ) n ++,tmp ++;
	for( int i = tmp + 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]);
	for( int i = 1 ; i <= n ; i ++ ) bel[i] = ( i - 1 ) / 6 + 1; Bcnt = bel[n];
	for( int i = 1 ; i <= n ; i ++ ) ed[bel[i]] = i;
	for( int i = n ; i >= 1 ; i -- ) st[bel[i]] = i;
	build( 1 , 1 , Bcnt );
	for( int i = 1 ; i <= q ; i ++ ){
		int x,k; scanf("%lld%lld",&x,&k); x += tmp;
		a[x] = k;
		modify( 1 , 1 , Bcnt , bel[x] );
		printf("%lld\n",T[1].v);
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

考虑一些复杂度带根号的做法。

考虑分块，对于一个块，我们需要处理出一个数经过这个块会变成哪个数。以下假设块长 $\ge 10$（最后一个块块长可能 $< 10$，暴力处理即可）。

观察这个递推式 $f_i = \left\lfloor\sqrt{f_{i - 1} + a_i}\right\rfloor$，发现对于一开始传进去 $0$ 和传进去 $10^{18}$，经过足够多（$\ge 10$ 个，应该能更少）的数，最后得到的 $f_i$ 最多相差 $1$。证明显然，因为有一个根号，每次会让 $\Delta$ 开根，进行 $\log \log V$ 次 $\Delta$ 就会变成 $1$。

设传进去 $0$ 得到 $x$，传进去 $10^{18}$ 得到 $y$。若 $x = y$ 那么已经完成了。否则 $x + 1 = y$，我们需要求出这个分界点，即求出 $z$ 使得传进去 $z$ 得到 $x$，传进去 $z + 1$ 得到 $y$。考虑有 $f_i^2 \le f_{i - 1} + a_i \le (f_i + 1)^2 - 1$，所以我们用 $x$ 倒推，倒推的同时维护 $f_i$ 的上界即可。

修改就重构所在块，询问扫一遍所有块，维护经过一段前缀的块后的 $f_i$ 的值即可。

时间复杂度 $O(n + m \sqrt{n})$。

[code](https://codeforces.com/problemset/submission/1942/254983426)

---

## 作者：Sharpsmile (赞：0)

# 题解：CF1942F Farmer John's Favorite Function



VP 的时候偶然想到了一些做法。基于神秘的东西（）看了看题解区貌似没有我这样 ~~魔怔~~ 的做法。

首先因为并没有发现直接对 $f(i)$ 下取整是对的，所以我去掉根号的方式是二分最终的答案，然后倒着做这个 check。

比如我们令 $f_n\geq x$，那么根据定义 $\sqrt{f_{n-1}+a_n}\geq x$。也就等价于 $f_{n-1}\geq x^2-a_n$。那么我们做的其实就是每次令 $x\rightarrow x^2-a_n, n\rightarrow n-1$。

那么什么时候我们可以进行当前条件是否合法的判定？我们一直递归的做这件事情，如果过程中出现了 $x\leq 0$ 那么一定合法。否则不合法。这东西可以 $O(n)$ 的做 check 了。

但是我们可以加入强有力的剪枝：当 $x>10^9$ 的时候，因为后面的 $x$ 一定全都 $>10^9$。所以一定不合法！这个看上去可能没啥用处，但是后面确实有用。

然后不知道干啥了，我们不妨大力分块。 思考如何快速求出一个 $x$ 经过一段操作后的结果。

对每个块我们维护两个值 $mn,mx$，分别表示当进入这个块的 $x\leq mn$ 的时候，在这个块里一定会出现 $x\leq 0$ 的时候。当 $x\geq mx$ 的时候，这个块里一定会出现 $x>10 ^9$ 的时候。

现在我们要解决 $mn<x<mx$ 的情况了。这个时候怎么办？我们直接对于这个区间里的所有 $x$ 维护他经过这个块之后会变成什么！这个为什么是对的？因为对于 $mn+1$，他一定会走到头而满足过程中时刻 $x\geq 1$，而当初始的 $x$ 变为 $mn+1$ 的时候，对第一次操作后的 $x$ 至少产生 $+1$ 的影响，第二次操作后的 $x$ 至少产生 $+2$ 的影响，然后依次是 $+4,+16,+256\cdots $。所以大约 $\log \log 10^ 9$ 次就会达到 $10^9$ ！

所以当我们的一块长度超过 $10$ 的时候，我们就一定有 $mx\leq mn+1$。所以对于这样的块，我们只用维护一个值就可以了，在更改一个位置的值的时候把这个块的 $mn,mx$ 二分出来，然后如果 $mx>mn+1$ 的话，就把 $x=mn+1$ 暴力跑一次得到结果即可。 

貌似我们这么做更新一块的复杂度是 $O(B\log V)$ 的？但是注意到只有当二分的值大约在 $mn+1$ 左右的时候我们才有跑满的可能性，所以这个东西常数小的离谱（也有可能可以直接证明没有那个 $\log$ ？我不大会）。

然后因为是在分块，所以大部分时候都满足 $B\geq 10$。除了最后一个块。这个很好解决，最后一个块如果比较小我们跑暴力遍历即可。

然后最后的求答案我们就二分 $x$，然后每个块依次 check。这部分看似是 $\frac{n}{B}\log V$ 的，但是实际上所有不等于第一个块的 $mn+1$ 的数都在第一个块被剪掉了（当 $n$ 较小的时候可能第一个块比较小所以可能没被剪掉，但是这种情况要求 $n\leq 10$ 甚至更小，不考虑他）。所以实际只有 $x=mn+1$ 的时候可能跑到 $O(\frac{n}{B})$  的 check。所以这里的复杂度是 $O(\frac{n}{B})$ 的。

然后理论上貌似 $B=\sqrt{\frac{n}{\log V}}$ 的时候理论上是最优的，但是因为常数真的很小，所以我直接令 $B=500$ 然后就过了，最大的点貌似跑了 1.2s+。 

代码写的很丑，不挂了。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1942F)

**题目大意**

> 给定 $a_1\sim a_n$，定义 $f_0=0,f_i=\sqrt{f_{i-1}+a_i}$，$q$ 次单点修改 $a_i$，修改后输出 $\lfloor\sqrt {f_n}\rfloor$。
>
> 数据范围：$n,q\le 2\times 10^5$。

**思路分析**

观察到记 $g_i=\lfloor\sqrt{f_i}\rfloor$，那么 $g_i=\lfloor\sqrt{g_{i-1}+a_i}\rfloor$，依然成立，可以用数学归纳法证明。

然后就可以扫描线了，离线下来对时间轴维护线段树，遍历 $i=1\sim n$，动态维护 $f_i$ 在第 $1\sim q$ 次操作后的值。

那么 $f_{i-1}\to f_i$ 可以看成加上 $a_i$ 后开根下取整，注意到 $a_i$ 的取值在 $1\sim q$ 次操作中可以看成均摊 $\mathcal O(n+q)$ 个区间，因此直接线段树暴力维护区间加全局开根即可。

采用势能线段树，维护区间最小值，最大值，当 $\sqrt{\max}-\max=\sqrt{\min}-\min$ 时转成区间差，容易分析时间复杂度依然是单 $\log$ 的。

时间复杂度 $\mathcal O((n+q)\log q)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
ll sqr(ll x) {
	ll y=sqrtl(x);
	while(y*y>x) --y;
	while((y+1)*(y+1)<=x) ++y;
	return y;
}
ll a[MAXN];
int n,q,lst[MAXN];
vector <array<ll,3>> op[MAXN];
struct SegmentTree {
	ll mx[MAXN<<2],mn[MAXN<<2],tg[MAXN<<2];
	void adt(int p,ll k) { mx[p]+=k,mn[p]+=k,tg[p]+=k; }
	void psu(int p) { mn[p]=min(mn[p<<1],mn[p<<1|1]),mx[p]=max(mx[p<<1],mx[p<<1|1]); }
	void psd(int p) { adt(p<<1,tg[p]),adt(p<<1|1,tg[p]),tg[p]=0; }
	void add(int ul,int ur,ll k,int l=1,int r=q,int p=1) {
		if(ul<=l&&r<=ur) return adt(p,k);
		int mid=(l+r)>>1; psd(p);
		if(ul<=mid) add(ul,ur,k,l,mid,p<<1);
		if(mid<ur) add(ul,ur,k,mid+1,r,p<<1|1);
		psu(p);
	}
	void gsqr(int l=1,int r=q,int p=1) {
		ll k=mx[p]-sqr(mx[p]);
		if(l==r||k==mn[p]-sqr(mn[p])) return adt(p,-k);
		int mid=(l+r)>>1; psd(p);
		gsqr(l,mid,p<<1),gsqr(mid+1,r,p<<1|1),psu(p);
	}
	void out(int l=1,int r=q,int p=1) {
		if(l==r) return printf("%lld\n",mx[p]),void();
		int mid=(l+r)>>1; psd(p);
		out(l,mid,p<<1),out(mid+1,r,p<<1|1);
	}
}	T;
signed main() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),lst[i]=1;
	int k; ll x;
	scanf("%d%lld",&k,&x),a[k]=x;
	for(int i=2;i<=q;++i) {
		scanf("%d%lld",&k,&x);
		op[k].push_back({lst[k],i-1,a[k]});
		a[k]=x,lst[k]=i;
	}
	for(int i=1;i<=n;++i) op[i].push_back({lst[i],q,a[i]});
	for(int i=1;i<=n;++i) {
		for(auto z:op[i]) T.add(z[0],z[1],z[2]);
		T.gsqr();
	}
	T.out();
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1942F)

考虑分块。

当块长足够大（$\log \log V$）的时候，那么输入的 $f(l - 1)$ 就不会对 $f(r)$ 产生太大的影响（最多 $1$）。

我们可以分为长为 $B$ 的块 $(b \ge 6)$，单点修改时，设 $f(l - 1) = 0$ 时该块答案为 $b$，可以发现，无论怎么修改 $f(l - 1)$ 的值答案都不会超过 $b + 1$。

所以我们可以二分出一个值 $x'$ 使得 $\ge x$ 的数得出的答案都是 $b + 1$。这样是 $O(B \log^2 V)$ 的复杂度。

这个复杂度不能接受。我们发现，我们可以逆着来，用答案是 $b+1$ 的时候来逆推，当大于 $10^{18}$ 就 `break` 掉。

这样的复杂度就是 $O(B)$，加上求 $B$ 的复杂度就是 $O(B \log V)$。

查询的时候暴力推每一块，每一次判断输出的是 $b$ 还是 $b + 1$。时间复杂度 $O(\frac{n}{B})$。

注意，最后一块可能小于 $B$。所以最后一块可以直接暴力算，复杂度 $O(B \log V)$。

查询复杂度 $O(m(\frac{n}{B} + B \log V))$，修改复杂度 $O(m(B \log V))$，理论 $B$ 值 $\sqrt{\frac{n}{\log V}}$，实际上由于 $O(B \log V)$ 部分常数比较大，$B$ 值需要再除 $2$ 或 $4$。

还有，建议手写 `sqrt` 函数，否则可能会导致一些神秘的 $\mathrm{WA}$。（或许也能提升一些效率？）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace FastIO{
    char OutputDevide = ' ';
    template<typename T>inline void read(T& x){T f=1;x = 0;char ch = getchar();while(ch<'0'||ch >'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();x*=f;}
    template<typename T,typename ... Args>inline void read(T& x,Args& ...args){read(x),read(args...);}
    template<typename T>inline void write(T x){if(x<0){putchar('-'),write(-x);return;}if(x/10)write(x/10);putchar(x%10+48);}
    template<typename T,typename ... Args>inline void write(T x,Args ...args){write(x),putchar(OutputDevide),write(args...);}
};
using FastIO::read, FastIO::write;

const int N = 2e5 + 5, sqN = N;
int bl, block[N], n, q;
ll a[N], b[sqN], x[sqN];

ll _sqrt( ll x ){
    ll l = 1, r = 1e9 + 5, mid, ans;
    while( l <= r ){
        mid = ( l + r ) >> 1;
        if( mid * mid <= x ) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

ll calc( ll x, int block ){
    for( int i = ( block - 1 ) * bl + 1; i <= block * bl; ++i )
        x = _sqrt( x + a[i] );
    return x;
}

ll calc2( ll x, int block ){
    for( int i = block * bl; i > ( block - 1 ) * bl; --i ){
        if( x >= 1e9 + 5 ) return 1e18 + 1;
        x = x * x - a[i];
        if( x <= 0 ) return 0;
    }
    return x;
}

void prework(){
    for( int i = 1; i < block[n]; ++i ){
        b[i] = calc( 0ll, i );
        x[i] = calc2( b[i] + 1, i );
        if( x[i] == 0 ) x[i] = 1e18 + 1;
    }
}

void update( int block ){
    b[block] = calc( 0ll, block );
    x[block] = calc2( b[block] + 1, block );
}

ll query(){
    ll x = 0;
    for( int i = 1; i < block[n]; ++i )
        if( x >= ::x[i] ) x = b[i] + 1; 
        else x = b[i];
    for( int i = ( block[n] - 1 ) * bl + 1; i <= n; ++i )
        x = _sqrt( x + a[i] );
    return x;
}

int main(){
    read( n, q );
    bl = sqrt( n / log2( 1e9 ) ) / 4;
    if( bl < 6 ) bl = 6;
    //bl = 6;
    for( int i = 1; i <= n; ++i ) read( a[i] ), block[i] = ( i - 1 ) / bl + 1;
    prework();
    while( q-- ){
        ll k, x;
        read( k, x );
        a[k] = x;
        if( block[k] != block[n] ) update( block[k] );
        write( query() );puts( "" );
    }
    return 0;
}
```

---

## 作者：hyman00 (赞：0)

### 题意

你有长度为 $n$ 的序列 $\set{a_i}$，根据它可以构造 $\set{b_i}$，其中 $b_1=\sqrt{a_1}$，$b_i=\sqrt{b_{i-1}+a_i}(2\le i\le n)$。

$q$ 次修改，每次令 $a_x=y$，并求 $\left\lfloor b_n\right \rfloor$。

$1\le n,q\le 2\times 10^5,0\le a_i\le 10^{18}$ 

### 做法

先考虑不修改怎么做。

很显然任何用浮点数直接存储的方法都不行，只要构造 `1 2 2 2 ...` 的数据，答案就无限接近 `2` 但小于 `2`。

由于题目求的是下取整，考虑二分答案，判断是否有 $b_n\ge x$，进而可以推出 $b_{n-1}\ge x^2-a_n$，从后往前递推即可。如果有某一时刻 $x'\le 0$ 或者 $x'>10^9$（上界可以证明不可能有 $b_i\ge 10^9+1$），就直接可以结束，最后如果 $x'\le0$ 则有 $b_n\ge x$。

回到原问题，考虑修改操作。

发现一个数开 $O(\log\log V)$ 次根号就很接近 $1$，因此如果不在最结尾处修改对答案的影响非常小。

考虑分块，每 $B$ 个分为一块，不够可以开头补零。对于一个块，只需记录一开始带入的 $x$ 和得到的 $x'$ 的关系，容易发现 $B$ 不过于小的时候 $x'$ 的可能取值是 $O(1)$ 的。

查询答案直接二分，从后往前一次在块里查询，是 $O(\frac NB\log V)$ 的，修改对指定块重构，是 $O(B\log V)$ 的，取 $B=\sqrt N$ 可以达到 $O((N+Q)\sqrt N\log V)$ 的。

看起来很慢？但是不到 `600ms`，因为其实没有 $\log$ 因子，基本上所有情况都在开头就 `break` 掉了，是 $O((N+Q)\sqrt N)$ 的。

看起来区间信息可以合并？确实可以，但是由于对块长有限制，只能底层分为长 `20` 的块，并建线段树，但是难写。

### 赛时代码

赛时没有将散块补零，而是直接暴力扫的。

```c++
const int N=200005,B=450,C=450;
const int LIM=2000000000;
//块长=B,块数=C 
int n,q,a[N];
struct BL{
	int len;
	int t[B];
	vector<pii>num;
	il int cr(int x){
		for(int i=len-1;i>=0;i--){
			if(x>=LIM)re LIM;
			if(x<=0)re 0;
			x=x*x-t[i];
		}
		if(x>=LIM)re LIM;
		if(x<=0)re 0;
		re x;
	}
	il void build(){
		int l=0,r=1001000000;
		while(l<r){
			int mid=(l+r+1)>>1;
			int tt=cr(mid);
			if(tt<=0)l=mid;
			else r=mid-1;
		}
		num.clear();
		num.pb({l,0});
		int tt=cr(++l);
		num.pb({l,tt});
		while(tt<LIM){
			tt=cr(++l);
			num.pb({l,tt});
		}
//		cout<<"build:\n";
//		for(pii i:num)cout<<i.F<<" "<<i.S<<"\n";
	}
	il void upd(int a,int x){
		t[a]=x;
		build();
	}
	il int calc(int x){
		if(x<=num[0].F)re 0;
		if(x>=num[sz(num)-1].F)re LIM;
		if(x==num[1].F)re num[1].S;
		re num[2].S;
	}
}b[C];
void calc(){
	int l=-1,r=1001000000;
//	rep(i,n)cout<<a[i]<<" ";cout<<"\n";
	while(l<r){
		int mid=(l+r+1)>>1;
		int x=mid;
//		cout<<"	mid = "<<mid<<"\n";
		for(int i=n-1;i>=n/B*B;i--){
//			cout<<i<<" : "<<x<<"\n";
			if(x>=LIM){
				x=LIM;
				break;
			}
			if(x<=0){
				x=0;
				break;
			}
			x=x*x-a[i];
		}
		for(int i=n/B-1;i>=0;i--){
			if(x>=LIM){
				x=LIM;
				break;
			}
			if(x<=0){
				x=0;
				break;
			}
			x=b[i].calc(x);
		}
		if(x<=0)l=mid;
		else r=mid-1;
	}
	cout<<l<<"\n"; 
}
void run(){
	cout<<fixed<<setprecision(10);
	cin>>n>>q;
	rep(i,n)cin>>a[i];
	rep(i,n/B){
		b[i].len=B;
		rep(j,B)b[i].t[j]=a[i*B+j];
		b[i].build();
	}
	rep(i,q){
		int x,y;
		cin>>x>>y;
		x--;
		a[x]=y;
		if(x/B<n/B)b[x/B].upd(x%B,y);
		calc();
	}
}
```

---

## 作者：wukaichen888 (赞：0)

萌萌尺子，上大分。

首先，观察这个式子，发现 $a_i$ 经过多次根号无法对靠后的 $f_i$ 造成 $>1$ 的贡献。

考虑以 $K=10$ 为块长分块，单点修则在块内暴力，外层用线段树维护。

每个块内维护 $f_{l-1}=0$ 时 $f_r$ 的值 $val$，$f_{l-1}$ 的最小值 $need$ 使 $f_r$ 增加 $1$。

线段树上也同理维护 $val$，$need$，合并子节点时：

- $val_{lc}\ge need_{rc}$，$val_k\gets val_{rc}+1$，$need_k\gets\inf$，因为 $lc$ 无法贡献 $2$。

- $val_{lc}+1=need_{rc}$，$val_k\gets val_{rc}$，$need_k\gets need_{lc}$。

- 否则，$val_k\gets val_{rc}$，$need_k\gets\inf$。

细节：保证最后一个块长度为 $K$。

复杂度：$O(nK\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+5,inf=4e18;
ll n,q,K=10,rev[N],a[N],pos[N],L[N],R[N],len;
ll msqrt(ll x){
	for(ll i=sqrt(x)+3ll;;i--)
		if(i*i<=x) return i;
}
struct node{ll val,ned;}tree[N];
#define lc k<<1
#define rc k<<1|1
#define ls lc,l,mid
#define rs rc,mid+1,r
void pushup(int k){
	if(tree[lc].val>=tree[rc].ned){
		tree[k].val=tree[rc].val+1;
		tree[k].ned=inf;
	}
	else{
		tree[k].val=tree[rc].val;
		if(tree[lc].val+1==tree[rc].ned)
			tree[k].ned=tree[lc].ned;
		else
			tree[k].ned=inf;
	}
}
void build(int k){
	ll l=L[rev[k]],r=R[rev[k]]; tree[k].val=0;
	for(ll i=l;i<=r;i++) tree[k].val=msqrt(tree[k].val+a[i]);
	tree[k].ned=tree[k].val+1;
	for(ll i=r;i>=l;i--){
		if(inf/tree[k].ned<=tree[k].ned){
			tree[k].ned=inf;
			return ;
		}
		tree[k].ned=tree[k].ned*tree[k].ned-a[i];
	}
}
void pre(int k,int l,int r){
	if(l==r){
		rev[k]=l;
		build(k);
		return ;
	}
	int mid=l+r>>1;
	pre(ls);pre(rs);
	pushup(k);
}
void change(int k,int l,int r,int x){
	if(l==r){
		build(k);
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) change(ls,x);
	else change(rs,x);
	pushup(k);
}
int main(){
	scanf("%lld%lld",&n,&q);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	len=(n-1)/K+1;
	for(ll i=1;i<=n;i++) pos[i]=len-(n-i)/K;
	for(ll i=1;i<=n;i++) R[pos[i]]=i;
	for(ll i=n;i;i--) L[pos[i]]=i;
	pre(1,1,len);
	ll x,y;
	while(q--){
		scanf("%lld%lld",&x,&y);a[x]=y;
		change(1,1,len,pos[x]);
		printf("%lld\n",tree[1].val);
	}
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

无脑分块保平安。

根据 $y = \sqrt x$ 的凸性，$\sqrt {x+a} - \sqrt{y+a} \le \sqrt x - \sqrt y$，如果 $x \ge y$、$a \ge 0$。

因此我们可以发现，根号的层数比较大的时候，不同的数带进去会非常接近。尝试略微分个块。

但是注意到因为有“取整”这一操作，以及根号的特性，在比较长的区间中，$a$ 和 $b$ 带进去操作的结果可能并不一样，但他们至多差 $1$。因此记录一下断点是否存在，如果存在在哪即可。

复杂度 $O(n \sqrt n)$。注意到块重构是比较耗时间的，所以缩短块长。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,q,k,a[MAXN],len=200,bl[MAXN],L[MAXN],R[MAXN],mval[MAXN],lim[MAXN];
int c_sqrt(int v) {
	int ans=sqrt(v);
	if(ans==0) return ans;
	while((ans+1)*(ans+1)<=v) ans++;
	while(ans*ans>v) ans--;	
	return ans;
}
void rebuild(int id) {
	int mn=0,mx=2000000000000000000;
	roff(i,R[id],L[id]) mn=c_sqrt(a[i]+mn),mx=c_sqrt(a[i]+mx);
	if(mx==mn) return mval[id]=mn,lim[id]=-1,void();
	lim[id]=mx,mval[id]=mn;
	ffor(i,L[id],R[id]) lim[id]=lim[id]*lim[id]-a[i];
	return ;
}
int calc(int id,int oval) {
	if(id==k) {
		roff(i,R[id],L[id]) oval=c_sqrt(oval+a[i]);
		return oval;
	}
	if(lim[id]==-1) return mval[id];
	return (oval>=lim[id])?mval[id]+1:mval[id];
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q,k=n/len;
	ffor(i,1,n) cin>>a[n-i+1];
	ffor(i,1,k) L[i]=R[i-1]+1,R[i]=i*len;
	if(R[k]<n) ++k,L[k]=R[k-1]+1,R[k]=n;
	ffor(i,1,k) ffor(j,L[i],R[i]) bl[j]=i; 
	ffor(i,1,k) rebuild(i);
	ffor(i,1,q) {
		int pos,x;
		cin>>pos>>x,a[n-pos+1]=x,rebuild(bl[n-pos+1]);
		int ans=0;
		roff(j,k,1) ans=calc(j,ans);
		cout<<ans<<'\n';
	}
	return 0;
}
```

这个信息很能用线段树维护，不过摆了，直接贴一个赛时代码上去。

---

