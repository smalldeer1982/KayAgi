# [GDCPC 2023] X Equals Y

## 题目描述

对于正整数 $X$ 与 $b \geq 2$，定义 $f(X,b)$ 为一个描述了 $X$ 在 $b$ 进制表示下的序列，其中序列的第 $i$ 个元素表示 $X$ 在 $b$ 进制表示下从低到高第 $i$ 位的值。例如，$f(6, 2) = \{0, 1, 1\}$，而 $f(233, 17) = \{12, 13\}$。

给定的四个正整数 $x$，$y$，$A$ 和 $B$，请找到两个正整数 $a$ 和 $b$，同时满足：

- $2 \leq a \leq A$
- $2 \leq b \leq B$
- $f(x, a) = f(y, b)$

## 样例 #1

### 输入

```
6
1 1 1000 1000
1 2 1000 1000
3 11 1000 1000
157 291 5 6
157 291 3 6
10126 114514 789 12345```

### 输出

```
YES
2 2
NO
YES
2 10
YES
4 5
NO
YES
779 9478```

# 题解

## 作者：EuphoricStar (赞：5)

当时在 GDCPC 现场是这题首杀。20min 就会了，但是 2h 才有电脑写（

----

观察到至多 $50$ 组数据满足 $\max(x, y) > 10^6$，考虑一些根号做法。

当 $f(x, a)$ 的长度 $\ge 3$ 时，$a \le \sqrt{x}$，因此可以暴力做，先找出所有 $f(x, a)$，再找出所有 $f(y, b)$，套个 map 找相等。

当 $f(x, a)$ 的长度 $= 1$ 时，$x = y$，可以直接判掉。

当 $f(x, a)$ 的长度 $= 2$ 时，我们有：

- $\left\lfloor\frac{x}{a}\right\rfloor = \left\lfloor\frac{y}{b}\right\rfloor$
- $x \bmod a = y \bmod b$

后者等价于 $x - a \left\lfloor\frac{x}{a}\right\rfloor = y - b \left\lfloor\frac{y}{b}\right\rfloor$。设 $t = \left\lfloor\frac{x}{a}\right\rfloor = \left\lfloor\frac{y}{b}\right\rfloor$，那么有 $x - at = y - bt$，化简得 $b - a = \frac{y - x}{t}$。

整除分块套个 map 找到所有 $\left\lfloor\frac{x}{a}\right\rfloor$ 和 $\left\lfloor\frac{y}{b}\right\rfloor$ 相等的区间，设当 $a \in [l_1, r_1], b \in [l_2, r_2]$ 时，$t = \left\lfloor\frac{x}{a}\right\rfloor = \left\lfloor\frac{y}{b}\right\rfloor$。那么我们有 $b - a = \frac{y - x}{t}$。显然 $b - a \in [l_2 - r_1, l_1 - r_2]$，若这个满足就可以构造一组解了。

注意构造完解后要判断是否满足 $a > \sqrt{x} \land b > \sqrt{y}$，还有别忘了 $a, b$ 分别有 $A, B$ 的上界。

时间复杂度 $O(\sum \sqrt{\max(x, y)} \log \max(x, y))$。

```cpp
// Problem: J. X Equals Y
// Contest: Codeforces - The 2023 Guangdong Provincial Collegiate Programming Contest
// URL: https://codeforces.com/gym/104369/problem/J
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

ll X, Y, A, B;

inline ll mysqrt(ll x) {
	for (ll i = max((ll)sqrt(x) - 2, 0LL);; ++i) {
		if (i * i > x) {
			return i - 1;
		}
	}
}

void solve() {
	scanf("%lld%lld%lld%lld", &X, &Y, &A, &B);
	if (X == Y) {
		puts("YES\n2 2");
		return;
	}
	ll sx = mysqrt(X), sy = mysqrt(Y);
	map<ll, pii> M;
	for (ll i = 2, j; i <= X && i <= A; i = j + 1) {
		j = X / (X / i);
		M[X / i] = mkp(i, min(j, A));
	}
	for (ll i = 2, j; i <= Y && i <= B; i = j + 1) {
		j = Y / (Y / i);
		if (M.find(Y / i) == M.end()) {
			continue;
		}
		ll t = Y / i;
		ll l1 = M[t].fst, r1 = M[t].scd, l2 = i, r2 = min(j, B);
		if ((Y - X) % t) {
			continue;
		}
		ll d = (Y - X) / t;
		if (l2 - r1 <= d && d <= r2 - l1) {
			ll a = l1;
			ll b = a + d;
			if (b < l2) {
				ll p = l2 - b;
				a += p;
				b += p;
			}
			if (a > sx && b > sy) {
				printf("YES\n%lld %lld\n", a, b);
				return;
			}
		}
	}
	map< vector<ll>, ll > mp;
	for (ll a = 2; a <= A && a <= sx; ++a) {
		vector<ll> vc;
		ll x = X;
		while (x) {
			vc.pb(x % a);
			x /= a;
		}
		reverse(vc.begin(), vc.end());
		mp[vc] = a;
	}
	for (ll a = 2; a <= B && a <= sy; ++a) {
		vector<ll> vc;
		ll x = Y;
		while (x) {
			vc.pb(x % a);
			x /= a;
		}
		reverse(vc.begin(), vc.end());
		if (mp.find(vc) != mp.end()) {
			printf("YES\n%lld %lld\n", mp[vc], a);
			return;
		}
	}
	puts("NO");
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：MaxBlazeResFire (赞：0)

题意：给定 $X,Y$，要求找到 $a,b,len$，使得 $\displaystyle X=\sum_{i=0}^{len}f_ia^i,Y=\sum_{i=0}^{len}f_ib^i$。

特判掉 $X=Y$。

设序列长度 $len=2$，那么存在正整数 $p$，满足以下限制：

$\begin{cases}
2\leq a\leq A,2\leq b\leq B\\
X-ap=Y-bp\\
0\leq X-ap<a,0\leq Y-bp<b\\
a\leq X,b\leq Y
\end{cases}$

首先，$p<a$，有 $p<\sqrt X$，又 $p\mid(X-Y)$，故 $p$ 的范围实际只有 $1.5\times10^3$；

我们枚举一个 $p$，然后推亿下式子，从上面的 $10$ 个不等号推出 $a$ 的限制实际上为 $\displaystyle a\in(\max\{\frac{X}{p+1},\frac{Xp+X-Y}{p^2+p},2-\frac{Y-X}{p},\frac{p^2+X-Y}{p},p\},\min\{A,X,B-\frac{Y-X}{p},Y-\frac{Y-X}{p},\frac{X}{p}\}]$。从中任选一个 $a$ 都满足条件，若不存在则无解。这里的复杂度是试 $p$ 的复杂度也即 $O(\sqrt{X})$。

然后就是 $len \geq 3$ 的情况，这种情况下有 $a,b\leq\sqrt X$，先枚举 $a$ 预处理出每个序列 $f$，复杂度 $O(\sqrt X\log X)$，然后把这 $\sqrt X$ 个序列用类似字符串的方法哈希起来；再枚举 $b$，生成序列后看哈希表里有无相同序列即可。

故总复杂度是 $O(T\sqrt X\log X+T'\sqrt{X'}\log X')$，前半部分有 $X\leq 10^6$，而题目保证后半部分的数据组数 $T'\leq 50$，故复杂度正确。

注：参考代码中后半部分用双模哈希实现。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define mod1 1004535809
#define mod2 1000000007

int X,Y,A,B,swa;

inline bool solve2(){
	vector<int> factor;
	for( int p = 1 ; p * p < X ; p ++ )
		if( ( X - Y ) % p == 0 ) factor.emplace_back( p );
	for( int p : factor ){
		int L = max( X / ( p + 1 ) , ( X * p + X - Y ) / ( p * p + p ) );
		L = max( L , max( 2 + ( X - Y ) / p , ( p * p + X - Y ) / p ) );
		L = max( L , p ); L ++;
		int R = min( min( A , X ) , min( B + ( X - Y ) / p , Y + ( X - Y ) / p ) );
		R = min( R , X / p );
		if( L <= R ){
			int a = ( L + R ) >> 1,b = ( Y - X ) / p + a;
			if( swa ) swap( a , b );
			printf("YES\n%lld %lld\n",a,b);
			return 1;
		}
	}
	return 0;
}

map< pair<int,int> , int > M;

struct sequence{
	int Len,Rtag;
	vector<int> seq;
	sequence( int p = 0 ){ Rtag = p,seq = vector<int>(1),Len = 0; }
	inline pair<int,int> add_up(){
		int res1 = 0,x1 = 1,base1 = 10007,res2 = 0,x2 = 1,base2 = 109;
		for( int j = 1 ; j <= Len ; j ++ ) res1 = ( res1 + ( ( seq[j] + 23 ) * x1 ) % mod1 ) % mod1,x1 = x1 * base1 % mod1;
		for( int j = 1 ; j <= Len ; j ++ ) res2 = ( res2 + ( ( seq[j] + 37 ) * x2 ) % mod2 ) % mod2,x2 = x2 * base2 % mod2;
		return make_pair( res1 , res2 );
	}
};

vector<sequence> Sa,Sb;

inline bool solve3(){
	int lenA = 0,lenB = 0;
	Sa.clear(),Sb.clear(),M.clear();
	Sa.emplace_back( sequence() ),Sb.emplace_back( sequence() );
	for( int a = 2 ; a <= A && a * a <= X ; a ++ ){
		Sa.emplace_back( sequence( a ) ),lenA ++;
		int tmp = X;
		while( tmp ) Sa[lenA].Len ++,Sa[lenA].seq.emplace_back( tmp % a ),tmp /= a;
	}
	for( int b = 2 ; b <= B && b * b <= Y ; b ++ ){
		Sb.emplace_back( sequence( b ) ),lenB ++;
		int tmp = Y;
		while( tmp ) Sb[lenB].Len ++,Sb[lenB].seq.emplace_back( tmp % b ),tmp /= b;
	}
	for( int i = 1 ; i <= lenA ; i ++ ) M[Sa[i].add_up()] = Sa[i].Rtag;
	for( int i = 1 ; i <= lenB ; i ++ ){
		int tmp = M[Sb[i].add_up()];
		if( tmp ){
			int Ansa = tmp,Ansb = Sb[i].Rtag;
			if( swa ) swap( Ansa , Ansb );
			printf("YES\n%lld %lld\n",Ansa,Ansb);
			return 1;
		}
	}
	return 0;
}

inline void solve(){
	scanf("%lld%lld%lld%lld",&X,&Y,&A,&B);
	if( X == Y ){ printf("YES\n2 2\n"); return; }
	if( X < Y ) swap( X , Y ),swap( A , B ),swa = 1; else swa = 0;
	if( !solve2() ){ if( !solve3() ) printf("NO\n"); }
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

