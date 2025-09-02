# Chips

## 题目描述

有$n$个棋子排成环状，标号为$1..n$

一开始每个棋子都是黑色或白色的。随后有$k$次操作。操作时，棋子变换的规则如下：我们考虑一个棋子本身以及与其相邻的两个棋子（共3个），如果其中白子占多数，那么这个棋子就变成白子，否则这个棋子就变成黑子。注意，对于每个棋子，在确定要变成什么颜色之后，并不会立即改变颜色，而是等到所有棋子确定变成什么颜色后，所有棋子才同时变换颜色。

对于一个棋子$i$，与其相邻的棋子是$i-1$和$i+1$。特别地，对于棋子$1$，与其相邻的棋子是$2$和$n$；对于棋子$n$，与其相邻的棋子是$1$和$n-1$。

如图是在$n=6$时进行的一次操作。

![图像](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1244F/954a54cba9c62be21723582b0f9fdfba14d8bb72.png)

给你$n$和初始时每个棋子的颜色，你需要求出在$k$次操作后每个棋子的颜色。


2. "WBWBWBW" $\rightarrow$ "WWBWBWW" $\rightarrow$ "WWWBWWW" $\rightarrow$ "WWWWWWW"

3. "BWBWBW" $\rightarrow$ "WBWBWB" $\rightarrow$ "BWBWBW" $\rightarrow$ "WBWBWB" $\rightarrow$ "BWBWBW"

## 样例 #1

### 输入

```
6 1
BWBBWW
```

### 输出

```
WBBBWW
```

## 样例 #2

### 输入

```
7 3
WBWBWBW
```

### 输出

```
WWWWWWW
```

## 样例 #3

### 输入

```
6 4
BWBWBW
```

### 输出

```
BWBWBW
```

# 题解

## 作者：AutumnKite (赞：8)

[题目传送门](http://codeforces.com/contest/1244/problem/F)

## 题意

有一个大小为 $n$ 的环，环上每个点有一个颜色（黑/白）。定义一次操作是，对于每个点 $i$，若他和他相邻的两个点中，白点多于黑点，则在新的环中， $i$ 变成白色，否则变为黑色。

求进行 $k$ 次操作后每个点的颜色。

$n\le 2\times 10^5,k\le 10^9$

## 题解

变色的条件相当于 $i$ 相邻两个点的颜色都与 $i$ 的颜色不同。对于一段长度 $\ge 2$ 的颜色相同的段，显然颜色是永远不会变的。只有这样的段之间的这些颜色交替改变的点的颜色会发生变化。例如 `WWWBWBWBWBBB` -> `WWWWBWBWBBBB` -> `WWWWWBWBBBBB` -> `WWWWWWBBBBBB`。

考虑中间的颜色交替改变的一段（如上例中 `BWBWBW`），发现每进行一次操作，两边的点会向两边的颜色相同的连续段合并，中间的点会改变颜色。记这样的段中某个点 $i$ 到两边颜色相同连续段的距离是 $a_i,b_i$，那么他会在第 $\min(a_i,b_i)$ 次操作被合并，颜色要看两边段的颜色和具体往哪边合并，被合并之后颜色就不会再变化，而在被合并之前颜色则是交替变化。所以只要根据 $k$ 和 $\min(a_i,b_i)$ 的大小进行讨论即可。

要注意的是，可能题目给定字符串的最前面一段和最后面一段是可以拼起来的，所以要对顺序进行一定的调整。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#define N 400005
int n, k, d, dis1[N], dis2[N];
char a[N], b[N];
bool check(){
	if (n & 1) return 0;
	for (register int i = 2; i <= n; ++i)
		if (a[i] == a[i - 1]) return 0;
	return 1;
}
int main(){
	scanf("%d%d%s", &n, &k, a + 1);
	if (check()){
		if (k & 1) std :: reverse(a + 1, a + 1 + n);
		return printf("%s", a + 1), 0;
	}
	for (register int i = 1; i <= n; ++i) a[n + i] = a[i];
	for (register int i = n + 2; i < (n << 1); ++i)
		if (a[i - 1] != a[i] && a[i] != a[i + 1]) continue;
		else{ d = i - 1; break; }
	if (!d) d = (n << 1) - 1;
	for (register int i = d - n + 1; i <= d; ++i)
		if (a[i - 1] != a[i] && a[i] != a[i + 1]) dis1[i] = dis1[i - 1] + 1;
		else dis1[i] = 0;
	for (register int i = d; i > d - n; --i)
		if (a[i - 1] != a[i] && a[i] != a[i + 1]) dis2[i] = dis2[i + 1] + 1;
		else dis2[i] = 0;
	for (register int i = d - n + 1; i <= d; ++i)
		if (a[i - 1] != a[i] && a[i] != a[i + 1])
			if (k >= std :: min(dis1[i], dis2[i]))
				if (dis1[i] < dis2[i]) b[i] = a[i - dis1[i]];
				else b[i] = a[i + dis2[i]];
			else b[i] = a[i] == 'B' && (k & 1) || (a[i] == 'W' && (k & 1 ^ 1)) ? 'W' : 'B';
		else b[i] = a[i];
	for (register int i = 1; i <= d - n; ++i) putchar(b[i + n]);
	for (register int i = d - n + 1; i <= n; ++i) putchar(b[i]);
}
```

---

## 作者：Soulist (赞：5)

~~通过别人知道的做法，所以不知道发出来好不好，但是太骚了所以还是要记一下（征求了别人同意~~

首先可以发现一个奇妙的性质：

$1):$ 假设某个点在第一轮操作时不需要改变，然后以后其均不需要改变

$2):$ 假设某个点在第$x$轮操作后不需要改变，那么其两边的点至少会在第$x+1$轮操作后不需要改变。

性质$1$比较显然，性质$2$则是因为这个点在第$x$轮才不需要改变的，所以在此之前，其必然位于一个$010101...$的串内，这样考虑后性质$2$便也可以发现了

所以可以将那么初始不需要改变的点加入集合，然后枚举其两边的点并拓展即可

将轮次限定在$k$轮之类即可

对于那么未被遍历到的点，那么其肯定每次操作后都会改成状态，所以额外统计一下其初始状态即可

复杂度$O(n)$

~~这样就可以为这道题摘掉大模拟sb题之类的称号了~~

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ; 
int n, m, vis[N], L[N], R[N] ; 
char s[N], w[N] ; 
queue<int> Q ; 
signed main()
{
	n = gi(), m = gi(), scanf("%s", s + 1 ), memset( vis, -1, sizeof(vis) ) ;
	rep( i, 1, n ) L[i] = i - 1, R[i] = i + 1, w[i] = s[i] ; L[1] = n, R[n] = 1 ; 
	rep( i, 1, n ) if( s[L[i]] == s[i] || s[R[i]] == s[i] ) vis[i] = 0, Q.push(i) ;
	while( !Q.empty() ) {
		int u = Q.front() ; Q.pop() ;
		if( vis[L[u]] == -1 ) vis[L[u]] = vis[u] + 1, Q.push(L[u]) ;
		if( vis[R[u]] == -1 ) vis[R[u]] = vis[u] + 1, Q.push(R[u]) ;
	}
	rep( i, 1, n ) {
		if( vis[i] > m || vis[i] == -1 ) ( m & 1 ) ? printf("%c", 'W' + 'B' - s[i] ) : printf("%c", s[i] ) ;
		else ( vis[i] & 1 ) ? printf("%c", 'W' + 'B' - s[i] ) : printf("%c", s[i] ) ;
	}
	return 0 ;
}

```

---

## 作者：叶ID (赞：1)

题目链接：[CF1244F Chips](https://www.luogu.org/problem/CF1244F)

【广告】[在个人博客食用](https://toxic2018.ml/1891/)风味更佳

****

### 题目描述

有$n$个棋子排成环状，标号为$1..n$

一开始每个棋子都是黑色或白色的。随后有$k$次操作。操作时，棋子变换的规则如下：我们考虑一个棋子本身以及与其相邻的两个棋子（共3个），如果其中白子占多数，那么这个棋子就变成白子，否则这个棋子就变成黑子。注意，对于每个棋子，在确定要变成什么颜色之后，并不会立即改变颜色，而是等到所有棋子确定变成什么颜色后，所有棋子才同时变换颜色。

对于一个棋子$i$，与其相邻的棋子是$i-1$和$i+1$。特别地，对于棋子$1$，与其相邻的棋子是$2$和$n$；对于棋子$n$，与其相邻的棋子是$1$和$n-1$。

如图是在$n=6$时进行的一次操作。

![图像](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1244F/954a54cba9c62be21723582b0f9fdfba14d8bb72.png)

给你$n$和初始时每个棋子的颜色，你需要求出在$k$次操作后每个棋子的颜色。

### 输入格式

第一行两个整数$n\ (3 \leq n \leq 2\cdot 10^5)$和$k\ (1 \leq k \leq 10^9)$，表示棋子总数与操作次数。

第二行是一个长度为$n$的，仅由字符$B$和$W$构成的字符串。如果第$i$个字符是$B$，表示第$i$个棋子位黑色，否则为白色。

### 输出格式

一行，长度为$n$的，仅由字符$B$和$W$构成的字符串，描述操作完成后每个棋子的颜色。

注意输出的顺序要和输入数据中的对应。

### 样例解释

1. 就是题目描述中举的那个例子

2. "WBWBWBW" $\rightarrow$ "WWBWBWW" $\rightarrow$ "WWWBWWW" $\rightarrow$ "WWWWWWW"

3. "BWBWBW" $\rightarrow$ "WBWBWB" $\rightarrow$ "BWBWBW" $\rightarrow$ "WBWBWB" $\rightarrow$ "BWBWBW"

****

### 提示

如果棋子数量是偶数，并且任意两个相邻棋子颜色不同，那么答案只和$k$的奇偶性有关。否则，棋子的状态将呈收敛趋势，最终达到一个“稳定状态”，不再改变。

### 重要的结论与证明

不难发现，随着不停地操作，我们可以将棋子的变化规律分为以下两类：

1. 如果棋子数是偶数，并且任意两个相邻棋子颜色不同，那么答案只和$k$的奇偶性有关。
2. 否则，棋子的状态将呈收敛趋势，最终达到一个“稳定状态”，不再改变。

理由？

对于第一类：显然，假设一开始状态是`BWBWBWBW...BWBW`，那么操作偶数次后，状态是 `BWBWBWBW...BWBW`，否则状态是 `WBWBWBWB...WBWB`。

对于第二类：

如果开始时就是“清一色”，那么必然已经是稳定状态。

否则我们根据颜色对这个棋子环划分“连通块”。比如下图：

![连通块划分](https://toxic2018.ml/wp-content/uploads/2019/10/b3e0b682c6ee9975b0ddd35c582f93cf.png)

（其中长度为1的连通块用一个小圆圈表示）

不难发现，如果一个棋子已经处于长度大于1的连通块中，那么在一次操作后其颜色不会改变，并且将仍然处于一个长度大于1的连通块中。

并且如果一个长度为1的连通块与一个长度大于1的连通块相邻，那么一次操作后，这个长度为1的连通块中的那个棋子就会变色，而与其相邻的，长度大于1的那个连通块却不会变色。那么，这个棋子就被加入到了与其相邻的连通块中。

这样，只要图中同时存在长度大于1（这个一定存在，否则就不是我们讨论的情况了）和等于1的连通块，每操作一次，其中长度等于1的连通块数量至少减少1。最终，一定会到达一个不存在长度等于1的连通块的状态。这就是“稳定状态”，到达这个状态后再进行操作，则没有棋子会再改变颜色。

### 解题方法

我们将所有长度为1的连通块提出来，构成连通块。为了防止混淆，我们称这种连通块为“相间区间”。

这句话可能有点晕，但是可以借助图片理解（蓝色表示构成的相间区间）：

![](https://toxic2018.ml/wp-content/uploads/2019/10/4c87b5303984e477c853ba38ca54a159.png)

根据上面的证明，每次操作时，只有相间区间中的棋子会且一定会改变颜色。相间区间中的棋子改变颜色后，其两端的（指区间中的两端）的棋子将不再属于相间区间。

设$dist_i$表示第$i$个棋子离其两侧的，长度大于1的连通块的距离中较小的一个。

从此处开始，用0表示白色，1表示黑色。

那么，当$k \leq dist_i$时，第$i$个棋子仍然属于间隔区间，其值为`val[i] ^ (k&1)`。否则，这个棋子已经被离其较近的一个长度大于1的连通块给“同化”了（如果两侧的连通块离这个棋子一样近，显然两侧的连通块颜色相同）。

### 实现细节

方便起见，先将棋子标号改为$0..n-1$。设`val[i]`表示棋子`(i%n+n)%n`的颜色。

首先，特判掉“棋子数是偶数，并且任意两个相邻棋子颜色不同”的情况。

然后，我们找到任意一个满足`val[i] = val[i-1]`的位置。

从这个位置开始顺时针扫一遍，记录每个相间区间内的棋子离左侧的，长度大于1的连通块的距离，以及其左侧的，长度大于1的连通块的颜色。

再从这个位置的前一个位置开始逆时针扫一遍，记录每个相间区间内的棋子右侧的，长度大于1的连通块的颜色。另外，判断每个相间区间内的棋子离右侧的，长度大于1的连通块的距离是否小于上一轮记录的距离。如果小于，将距离更新为当前距离的相反数（使用正负两种数，以便判断一个棋子是离左边的连通块更近还是离右边更近）

其他细节可以见代码。

****

```cpp
// status: [Accepted][unofficial]
// oj:     [Codeforces]

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int MAXN = 200001;
int n,k;
// 棋子的初始颜色
int arr[MAXN];
// 棋子离左右侧长度大于1的连通块更近的那个距离
int dist[MAXN];
// 棋子左侧长度大于1的连通块的颜色
int lc[MAXN];
// 棋子右侧长度大于1的连通块的颜色
int rc[MAXN];

signed main() {
    ios::sync_with_stdio(false);

    cin>>n>>k;

    // 读入
    for(int i=0;i<n;i++) {
        char c;
        cin>>c;
        if(c == 'B') arr[i] = 1;
    }

    // 特判
    bool flag1 = (n%2 == 0);
    if(flag1) for(int i=0;i<n;i++) {
        if(arr[0] ^ arr[i] ^ (i&1)) {flag1 = false;break;}
    }
    if(flag1) {
        cerr<<"I AK IOI"<<endl;
        for(int i=0;i<n;i++) {
            if(arr[i] ^ (k&1)) cout<<'B';
            else cout<<'W';
        }
        cout<<endl;
        exit(0);
    }

    // 找到开始位置
    int bg = 0;
    for(int i=0;i<n;i++) {
        if(i!=0 && arr[i-1] == arr[i]) {bg = i;break;}
    }
    bg += n;

    // 顺时针遍历
    int lastpos = 0;
    int lastcol = 0;
    for(int i=bg;i<bg+n;i++) {
        if(arr[(i-1) % n] != arr[i % n] && arr[i % n] != arr[(i+1) % n]) { // 判断是否相间区间
            dist[i % n] = i - lastpos;
            lc[i % n] = lastcol;
        }
        else {lastpos = i;lastcol = arr[i % n];dist[i % n] = 0;}
    }
    bg += n;
    for(int i=bg-1;i>=bg-n;i--) {
        if(arr[(i-1) % n] != arr[i % n] && arr[i % n] != arr[(i+1) % n]) { // 判断是否相间区间
            if(lastpos - i < dist[i % n]) {
                dist[i % n] = i - lastpos; // 更新距离
            }
            rc[i % n] = lastcol;
        }
        else {lastpos = i;lastcol = arr[i % n];}
    }

    // 输出
    for(int i=0;i<n;i++) {
        if(dist[i] == 0) {
            if(arr[i]) cout<<'B';
            else cout<<'W';
        }
        else if(dist[i] > 0) {
            if(k < dist[i]) {
                if(arr[i] ^ (k&1)) cout<<'B';
                else cout<<'W';
            }
            else {
                if(lc[i]) cout<<'B';
                else cout<<'W';
            }
        }
        else {
            if(k < -dist[i]) {
                if(arr[i] ^ (k&1)) cout<<'B';
                else cout<<'W';
            }
            else {
                if(rc[i]) cout<<'B';
                else cout<<'W';
            }
        }
    }
    cout<<endl;
}

```

评测记录：[R25183207](https://www.luogu.org/record/25183207)


---

## 作者：CYJian (赞：1)

这是一道sb模拟题。

首先我们发现，如果存在相邻两个位置颜色相同，那么两个位置都不会改变颜色了。

我们可以把这样的一段连续颜色相同的段称为 颜色块 。

那么我们就只需要考虑相邻两个颜色块之间的交错颜色相反的序列的变化就行了。

首先考虑两个颜色块相同的情况：当进行完足够长的时间后，中间的颜色一定都会变成两边的颜色块的颜色，然后手动模拟一下就可以发现，每过一个单位时间，两边的颜色块都会往中间扩张一格直到相连。然后中间就是以另一种颜色为起始的黑白交错的序列。

然后考虑两个颜色块不同的情况：还是考虑两边往中间扩展，显然当两边扩展到中间相遇后就不会再动了。那么仔细分析一下事实上和上面的情况大同小异。

然后再特判一下所有相邻的位置颜色都不同就行了。（这个怎么判详见样例3）

Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define FILE(Name) freopen(Name".in", "r", stdin), freopen(Name".out", "w", stdout)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

template<typename T> inline void chkmax(T&a, T b) { a = a > b ? a : b; }
template<typename T> inline void chkmin(T&a, T b) { a = a < b ? a : b; }
template<typename T> inline T gcd(T&a, T b) { return !b ? a : gcd(b, a % b); }
typedef unsigned uit;
typedef long long ll;
typedef double db;

// 看题目取用
// const int mod1 = 2999999; // for Hash
// const int mod2 = 4999999; // for Hash
// const int mod = 19491001;
// const int mod = 19260817;
// const int mod = 104857601;
// const int mod = 998244353;
// const int mod = 998244853;
// const int mod = 1004535809;
const int mod = 1000000007;

template<typename T>
const T Mod(T x) { return x >= mod * 2 ? x % mod : (x >= mod ? x - mod : x); }
template<typename T>
const void Add(T&a, T b) { a = Mod(a + b); }

const int MAXN = 400100;

char s[MAXN];
char t[MAXN];
int Block[MAXN];

int main() {
#ifndef ONLINE_JUDGE
	FILE("f");
#endif
	int n, k; gi(n); gi(k);
	gstr(s + 1);
	int st = n;
	for(int i = 1; i < n; i++)
		if(s[i] == s[i + 1]) {
			st = i;
			break;
		}
	if(s[1] != s[n] && st == n) {
		if(k & 1) 
			for(int i = 1; i <= n; i++) {
				if(s[i] == 'B') s[i] = 'W';
				else s[i] = 'B';
			}
		pstr(s + 1);
		return 0;
	}
	for(int i = 1; i <= n; i++) s[i + n] = s[i]; s[n * 2 + 1] = s[1], s[n * 2 + 2] = s[2];
	int Last = s[st], flag = 0, b; int ed = st + n - 1;
	for(int i = st + 1; i <= ed + 2; i++) {
		if(s[i] == s[i - 1]) {
			t[i] = t[i - 1] = s[i];
			if(flag) {
				if(Last == s[i]) {
					int l = b;
					int r = i - 2;
					int mi = min(k, (r - l + 2) >> 1);
					for(int j = 0; j < mi; j++)
						t[l + j] = t[r - j] = Last;
					for(int j = l + mi; j <= r - mi; j++)
						if(t[j - 1] == 'W') t[j] = 'B';
						else t[j] = 'W';
				} else {
					int l = b;
					int r = i - 2;
					int mi = min(k, (r - l + 1) >> 1);
					for(int j = 0; j < mi; j++)
						t[l + j] = Last, t[r - j] = s[i];
					for(int j = l + mi; j <= r - mi; j++)
						if(t[j - 1] == 'W') t[j] = 'B';
						else t[j] = 'W';
				}
			} flag = 0;
			Last = s[i];
		} else {
			if(s[i] != s[i + 1]) {
				if(!flag) {
					flag = 1;
					b = i;
				}
			}
		}
	}
	for(int i = st; i <= ed; i++)
		if(i > n) t[i - n] = t[i];
	t[n + 1] = 0;
	pstr(t + 1); pc('\n');
	return 0;
}
```

---

## 作者：Leap_Frog (赞：0)

### Description.
给定一个 0/1 环，每次一个点会变成它左右和它三个点的中位数。  
问变 $k$ 次后会变成什么样子。  

### Solution.
观察发现，如果有一个长度超过 $1$ 的子串，那它必定不会改变。  
所以我们只用考虑两段长度超过 $1$ 的子串中间夹着的 `...01010101...` 即可。  
手模发现，每次操作中，这中间的所有元素会 $\oplus1$，然后最左边和最右边和长度超过 $1$ 的子串合并。  
形象地说，就是长度超过 $1$ 的字串的“扩展”。  
所以我们直接找出这些摄乎长串之间的短串，每次模拟即可。  

### Coding.
**注意，以下代码实现复杂，请谨慎阅读**

```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
int n,L[200005],R[200005],ct,K;char ch[200005],tmp[200005];;
int main()
{
	read(n),read(K),scanf("%s",ch+1);int wh=0;
	for(int i=1;i<=n;i++) if(ch[i%n+1]==ch[i]) {wh=i;break;}
	if(!wh) {for(int i=1;i<=n;i++) putchar(K&1?ch[i]^21:ch[i]);return putchar('\n'),0;}
	for(int i=1;i<=n;i++) tmp[(i+n-wh)%n+1]=ch[i];
	ch[n+1]=tmp[1];for(int i=1;i<=n;i++) ch[i]=tmp[i];
	//for(int i=1;i<=n;i++) printf("%c",ch[i]);putchar('\n');
	for(int i=1,ls=1;i<=n;i++) if(ch[i+1]!=ch[i]) (ls^i?(L[++ct]=ls,R[ct]=i):0),ls=i+1;
	ch[1]!=ch[n]?L[++ct]=n+1:0;for(int i=1;i<ct;i++)
	{
		int ds=L[i+1]-R[i]-1;if(!ds) continue;
		//printf("%d %d\n",R[i],L[i+1]);
		if(K+K>=ds)
		{
			if(ds&1) {for(int j=R[i]+1;j<L[i+1];j++) ch[j]=ch[R[i]];continue;}
			for(int j=R[i]+1;j<L[i+1];j++) if(j<=R[i]+(ds>>1)) ch[j]=ch[R[i]];else ch[j]=ch[L[i+1]];
		}
		else
		{
			for(int j=R[i]+1;j<=R[i]+K;j++) ch[j]=ch[R[i]];
			for(int j=L[i+1]-K;j<L[i+1];j++) ch[j]=ch[L[i+1]];
			for(int j=R[i]+K+1;j<L[i+1]-K;j++) ch[j]=ch[j-1]^21;
		}
	}
	//for(int i=1;i<=n;i++) printf("%c",ch[i]);putchar('\n');
	for(int i=1;i<=n;i++) tmp[(i+wh-2)%n+1]=ch[i];
	for(int i=1;i<=n;i++) printf("%c",tmp[i]);
	return putchar('\n'),0;
}
```

---

## 作者：caidzh (赞：0)

~~F应该是整场比赛中比较难写的题了，所以这是一份口胡题解~~

下面定义$W$为$1$，$B$为$0$

考虑如果有两个$1$连在一起，那么这两个$1$就不会变了，$0$同理

那么我们接下来考虑用连续的$1$或$0$将整个环拆开来，注意到连续的$1$或$0$之间一定是形如$1010101...$这样的序列，序列之间肯定互不影响（这里思考一下），所以我们单独取出这样的序列，接下来我们考虑怎么计算这个序列的变化

通过手玩可以发现对于形如$(111)0101010(000)$的数列，经过一次操作后它会变成$(111)1010100(000)$，再经过一次它会变成$(111)1101000(000)$，发现了什么？经过一次操作整个序列就往内缩进一格，最终状态请读者自己脑补一下，**并且到了最终状态后整个序列将不会有任何变化**

正因如此，所以$k$再大也没有什么用，对复杂度有影响的仅仅只是$n$的大小

所以我们找出所有这样的序列单独拎出来搞即可，写的时候注意一系列细节和特判一系列情况

---

## 作者：xukuan (赞：0)

比赛里两道难题（CF）中较难的一道

我们发现一个性质：如果连续$k(k \geq 2)$个的颜色相同，那么他们的颜色就不会变

那么，会变的只是型如$\dots BWBWBW \dots$的。

每次变化，左右两端的会变成最终的颜色，其他中间的变成异色($B \rightarrow W,W \rightarrow B$)

那么我们直接模拟即可。

模拟的时间复杂度是$O(min(n,k))$

为什么？

对于每次操作（时间复杂度为$O(1)$），它一定会改变两个字符的值，同时每个字符至少改变一次。

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=200010;
string s;
ll n,k,lazy,v[N],Next[N],Prev[N];
struct node{
	ll p,type;
};
queue<node> p,q;

inline void pre(){
	for(ll l=0; l<n; l++){
        ll r=l;
        while(r+1<n&&s[r+1]==s[r]) r++;
        if(r-l+1>=2){
            for(ll i=l; i<=r; i++) v[i]=1;
            q.push(node{l,1});
            q.push(node{r,2});
            l=r;
        }
    }
    if(!v[0]&&!v[n-1]&&s[0]==s[n-1]){
    	q.push(node{n-1,1});
    	q.push(node{0,2});
    	v[0]=v[n-1]=1;
	}
}

int main(){

	ios::sync_with_stdio(0);

	cin>>n>>k;
	cin>>s;
	for(ll i=1; i<n; i++) Prev[i]=i-1; Prev[0]=n-1;
	for(ll i=0; i<n-1; i++) Next[i]=i+1; Next[n-1]=0;
	pre();
	for(ll i=1; i<=k; i++,lazy^=1){
		if(q.empty()) break;

		while(!q.empty()){
			node r=q.front(); q.pop();
			if(r.type==1){
				q.push(r);
				continue;
			}
			node l=q.front(); q.pop();
			ll L=l.p,R=r.p;
			if(Prev[L]!=R&&Prev[Prev[L]]!=R){
				ll Left=Prev[L],Right=Next[R];
				s[Right]=s[R]; v[Right]=1; p.push(node{Right,2});
				s[Left]=s[L]; v[Left]=1; p.push(node{Left,1});
			}
			else if(Prev[Prev[L]]==R){
				ll p=Prev[L]; v[p]=1;
				if(s[L]==s[R]) s[p]=s[L];
				else if(lazy) s[p]='B'+'W'-s[p];
			}
		}
		while(!p.empty()){
			q.push(p.front());
			p.pop();
		}
	}
	if(lazy){
		for(ll i=0; i<n; i++){
			if(!v[i]) s[i]='B'+'W'-s[i];
		}
	}
	cout<<s<<endl;
	return 0;
}
```

---

