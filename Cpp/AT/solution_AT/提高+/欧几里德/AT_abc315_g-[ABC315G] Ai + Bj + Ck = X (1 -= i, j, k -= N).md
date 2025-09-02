# [ABC315G] Ai + Bj + Ck = X (1 <= i, j, k <= N)

## 题目描述

给定整数 $N, A, B, C, X$，请你求满足以下所有条件的整数三元组 $(i, j, k)$ 的个数。

- $1 \leq i, j, k \leq N$
- $Ai + Bj + Ck = X$

## 说明/提示

### 限制条件

- 输入均为整数。
- $1 \leq N \leq 10^6$
- $1 \leq A, B, C \leq 10^9$
- $1 \leq X \leq 3 \times 10^{15}$

### 样例解释 1

满足条件的三元组有以下 $3$ 个：

- $(1,2,2)$：$3 \times 1 + 1 \times 2 + 5 \times 2 = 15$
- $(2,4,1)$：$3 \times 2 + 1 \times 4 + 5 \times 1 = 15$
- $(3,1,1)$：$3 \times 3 + 1 \times 1 + 5 \times 1 = 15$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3 1 5 15```

### 输出

```
3```

## 样例 #2

### 输入

```
1 1 1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
100000 31415 92653 58979 1000000000```

### 输出

```
2896```

# 题解

## 作者：yzy1 (赞：18)

## 算法 1

考虑枚举 $i$．问题转化为：给定 $x$，找到满足 $B j + C k = x$ 的整数对 $j,k$ 数量．这个问题可以使用 exgcd 算法来解决．但是该做法在处理 $1 \le j,k \le N$ 的限制上时需要经过一些分类讨论，较为复杂．

## 算法 2

观察到如果确定 $i,j$ 后，至多存在一个 $k$ 可以满足条件．考虑把 $A i + B j + C k = X$ 转化为 $A i + B j = X - C k$．考虑用数据结构维护 $A i + B j$ 的值：首先枚举 $i$，此时需要给 $A i + B, A i + 2B, \dots, A i + N B$ 的地方全部加一，然后再枚举 $k$ 计算 $X - C k$ 位置的和．换句话说，本题需要的数据结构需要支持以下操作：

- 将一个区间内下标 $\bmod B$ 为给定值的位置加一．
- 单点查询．

考虑开 $B$ 棵动态开点线段树来维护它．注意到 $B$ 的数据范围非常大，而 $B$ 棵树中的大部分都是空树，我们直接再在外层用一个 map 动态维护树根编号即可．

这个做法的时空复杂度均为 $O(N \log X)$，由于本题的内存限制，无法开下如此多的线段树结点，我们需要优化空间．

## 算法 3

注意到本题中所有查询操作只会在修改操作之后出现，通常的做法是离线前缀和，但是本题中由于值域过大，需要进行离散化．比起离散化，本题还存在一个更为优雅的写法．注意到加法操作可差分，也就是转化为一个前缀加和一个前缀减．我们开两个 `std::vector` 记录加和减的下标并对其排序．查询的时候可以直接使用 `std::upper_bound` 查询下标小于等于它的有多少个，据此来得到答案．

该做法的时间复杂度为 $O(N \log N)$，空间复杂度为 $O(N)$，可以通过本题．

## 代码参考

最终，我们得到了一份极其简洁的代码：

```cpp
map<int, vector<ll>[2]> mp;
ll n, a, b, c, m;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> a >> b >> c >> m;
  re (i, n) {
    mp[i * a % b][0].push_back(i * a + b);
    mp[i * a % b][1].push_back(i * a + n * b + 1);
  }
  ll ans = 0;
  re (i, n) {
    if (m - i * c <= 0) break;
    auto &v = mp[(m - i * c) % b];
    ans += upper_bound(v[0].begin(), v[0].end(), m - i * c) - v[0].begin();
    ans -= upper_bound(v[1].begin(), v[1].end(), m - i * c) - v[1].begin();
  }
  cout << ans << '\n';
  return 0;
}
```


---

## 作者：_sunkuangzheng_ (赞：11)

纪念第一次赛时想到 G 正解。~~（虽然没调出来）~~

**【题目大意】**

给定 $n,a,b,c,k(n \le 10^6,a,b,c \le 10^9,k \le 10^{15})$，求满足 $1 \le x,y,z \le n,ax + by + cz = k$ 的数对 $(x,y,z)$ 数量。

**【题目分析】**

裸的 exgcd。由于 $n$ 不大，可以直接枚举 $x$ 的值，再 exgcd 计算方程 $by+cz = k-ax$ 的解数，累加答案即可。时间复杂度 $\mathcal O(n \log n)$。

下文默认你已经会了【模板】exgcd，并将使用类似的推导方法解方程 $ax+by = c$（$\gcd(a,b) = 1$）。注意这里变量名与上面不同。

设 exgcd 跑出来的解为 $x_1,y_1$，则通解可以表示为 $x = x_1 + kb,y = y_1 - ka$，其中 $k$ 为整数。

解不等式组：

$$\begin{cases}1 \le x_1 +kb \le n\\1 \le y_1 -kb \le n\end{cases}$$

得

$$\begin{cases}\lceil \dfrac{-x_1+1}{b}\rceil \le k \le \lfloor \dfrac{n-x_1}{b}\rfloor\\\lceil \dfrac{y_1-n}{a}\rceil \le k \le \lfloor \dfrac{y_1-1}{a}\rfloor\end{cases}$$

**请注意下取整和上取整的区别。**

那么将两个解集合并即可。

**【代码】**

代码实现上，要注意几个点：

- 本题卡 long double，上下取整必须使用 __int128。一个常见的 trick 是 $\lceil \dfrac{a}{b}\rceil = \lfloor \dfrac{a+b-1}{b}\rfloor$。

- 注意 C++ 中的除法运算符是**向零取整**，即 $-8 \div 3$ 的值在 C++ 中计算结果为 $-2$。因此需要特判被除数为负数时的上下取整细节。

- 记得全程开 __int128。推荐直接 define。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int __int128
int n,a,b,c,ax,ans;
long long nn,aa,bb,cc,xx;
void exgcd(int a,int b,int &x,int &y){
    if(!b) return x = 1,y = 0,void();
    exgcd(b,a % b,y,x);y = y - (a / b) * x;
}
int gcd(int a,int b){return (b ? gcd(b,a % b) : a);}
int solve(int a,int b,int c){
    int k = gcd(a,b), x,y;
    if(c % k || c <= 0) return 0;
    a /= k,b /= k,c /= k,exgcd(a,b,x,y),x *= c,y *= c;
    int l1 = (-x+1+b-1) / b,l2 = (y - n + a - 1) / a;
    if(-x + b < 0) l1 = (x - 1) / b * -1;
    if(y - n + a - 1 < 0) l2 = (-y + n) / a * -1;
    int r1 = (n - x) / b,r2 = (y - 1) / a;
    if(n - x < 0) r1 = (x - n + b - 1) / b * -1;
    if(y - 1 < 0) r2 = (1 - y + a - 1) / a * -1;
    int l = max(l1,l2),r = min(r1,r2);
    return max(r - l + 1,(int)0);
}
void write( int x ){
	if( x >= 10 ) write( x / 10 );	putchar( x % 10 + 48 );
}
signed main(){
    cin >> nn >> aa >> bb >> cc >> xx;
    n = nn,a = aa,b = bb,c = cc,ax = xx;
    for(int i = 1;i <= n;i ++) ans += solve(b,c,ax - a * i);
    write(ans);
}
```

---

## 作者：CarroT1212 (赞：3)

$N\le 10^6$，考虑枚举 $i$，于是得到 $Bj+Ck=X-Ai$，相当于是求这个二元一次方程的合法解（$1 \le j,k \le N$）个数，直接 exgcd 即可。不会可以参考 P5656 的题解区，大概就是整出一组特解，然后算出 $k\le n$ 时 $j$ 的最小正整数解和 $j\le n$ 时 $k$ 的最小正整数解中间隔了多少个解，细节可以看代码。只是 $X\le 3\times 10^{15}$，写法不好的话 long long 会爆，开个 __int128 应该就能过了。

记得多加几个 $1\le j,k \le N$ 的特判，不然会去世。赛时与 AC 只差一个求出 $1 \le k \le N$ 的特解后对 $j$ 的大小是否满足条件的特判，不然直接就上蓝了，大哭。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lll __int128
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
ll n,aa,bb,cc,xx,ans;
void exgcd(lll a,lll b,lll &x,lll &y) {
	if (b) exgcd(b,a%b,y,x),y-=a/b*x;
	else x=1,y=0; 
}
lll solve(ll yy) {
	if (yy<=0) return 0;
	lll a=bb,b=cc,c=yy,x,y,g,p,q,tmp; // 设 a=输入的 b，b=输入的 c，c=输入的 x - 输入的 a * 枚举的 i
	exgcd(a,b,x,y),g=__gcd(a,b); // 求 ax+by=gcd(a,b) 的特解
	if (c%g!=0) return 0;
	else {
		x*=c/g,y*=c/g,p=b/g,q=a/g;
		if (x<0) tmp=(-x)/p+1,x+=p*tmp,y-=q*tmp;
		else if (x>=0) tmp=(x-1)/p,x-=p*tmp,y+=q*tmp; // 先把 x 弄成最小正整数解
		if (y>0) { // 如果这时 y 也有正整数解
			if (y>n) tmp=(y-n-1)/q+1,y-=q*tmp,x+=p*tmp; // 使 y<=n
			if (x<1||x>n||y<1||y>n) return 0; // 赛时没加这句（大哭
			else return min((y-1)/q+1,(n-x)/p+1); // 看两组极限解中间隔了多少个
		}
	}
	return 0;
}
int main() {
    scanf("%lld%lld%lld%lld%lld",&n,&aa,&bb,&cc,&xx);
    for (ll i=1;i<=n;i++) ans+=(ll)solve(xx-aa*i);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：lzc0115 (赞：3)

## ABC315G
### 题目大意
**给定 $A$，$B$，$C$，$X$ 求有多少组 $(i, j, k)$ 满足下面两个条件。**
- $1\le i, j, k\le N$。
- $Ai+Bj+Ck=X$。

---

### 数据范围

- $1\le N \le 10^6$。
- $1\le A, B, C \le 10^9$。
- $1\le X \le 3 \times 10^{15}$。

---
### 前置知识 [扩展欧几里得](https://oi-wiki.org/math/number-theory/gcd/#%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95)
---
### 分析
考虑简化问题，如果没有 $Ck$ 这一项，即 $Ai + Bj = X$，这就是一道扩欧板子题。

观察数据范围 $N\le 10^6$，可以暴力枚举 $k$， 再统计有多少对 $(i, j)$ 满足 $Ai + Bj = X - Ck$ 即可。

时间复杂度 $O(N)$。

---

### 注意事项及说明

- 运算过程可能会爆 `long long`， 需要开 `__int128`，~~别问我怎么知道的~~。

- 只需在枚举前进行一次扩欧，故时间复杂度不带 $\log$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
typedef __int128 ll;

ll a, b, c, n, k, d, x, y, ans, x2, y2, mn, mx, ga, gb, z;
long long _n, _a, _b, _c, _k, _ans;

void exgcd(ll a, ll b){
  if(b == 0){
    x = 1, y = 0;
    d = a;
    return;
  } else exgcd(b, a % b);
  ll t = x;
  x = y;
  y = t - (a / b) * y;
}

int main(){
  cin >> _n >> _a >> _b >> _c >> _k;
  n = _n, a = _a, b = _b, c = _c, k = _k, z = 0;
  exgcd(a, b);
  ga = b / d, gb = a / d;
  for(long long i = 1; i <= n && k > c; i++){
    k -= c; \\ 枚举c的系数
    if(k % d) continue;
    x2 = x * (k / d), y2 = y * (k / d);
    x2 = (x2 % ga + ga - 1) % ga + 1; \\ x的最小解
    if(y2 > n) y2 = y2 - ((y2 - n - 1) / gb + 1) * gb;
    else y2 = n - (n - y2) % gb; \\ y的最大解
    mn = max(x2, (k - y2 * b) / a); \\ 满足要求的最小的x
    y2 = (y2 % gb + gb - 1) % gb + 1;
    if(x2 > n) x2 = x2 - ((x2 - n - 1) / ga + 1) * ga;
    else x2 = n - (n - x2) % ga;
    mx = min(x2, (k - y2 * b) / a); \\ 满足要求的最大的x
    if(mx >= mn) ans += max(z, (mx - mn) / ga + 1);
  }
  _ans = ans;
  cout << _ans;
  return 0;
}
```


---

## 作者：_lqs_ (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Nwayy/p/17648989.html)

题意：给定 $n,a,b,c,x$，求满足 $1 \le i,j,k \le n$ 且 $ai+bj+ck=x$ 的三元组 $(i,j,k)$ 的个数。$1 \le n \le 10^6$，$1 \le a,b,c \le 10^9$，$1 \le x \le 3 \times 10^{15}$。

考虑到 $n$ 只有 $10^6$ 级别，我们可以枚举 $i$ 来消掉 $ai$，这样就变成了求 $bj+ck=x-ai$ 的二元组 $(j,k)$ 的个数，这个是容易用扩欧求出的，求出来的 $j$ 和 $k$ 要调边界到 $[1,n]$ 内，比较麻烦，把 $j$ 调到区间的最小，把 $k$ 调到区间的最大，然后对各自的可变化量取个 $\min$ 即可。

ps：由于可能会炸所以要开 `__int128`。


感谢 [@YukinoYukinoshita](https://www.luogu.com.cn/user/316801 "@YukinoYukinoshita") 大佬帮调代码。

复杂度一个 $\log$。

```
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
__int128 n,m,i,j,ans,a,b,c,x,l,r;
__int128 gcd(__int128 a,__int128 b){
    if(b==0) return a;
    return gcd(b,a%b);
}
void exgcd(__int128 a,__int128 b,__int128 c){
    if(b==0){
        l=c/a,r=0;
        return;
    }
    exgcd(b,a%b,c);
    __int128 tmp=l;
    l=r,r=tmp-a/b*r;
}
inline __int128 read(){
    __int128 x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void write(__int128 x){
    if (x<0) putchar('-'),x=-x;
    if (x>9) write(x/10);
    putchar(x%10+'0');
}
signed main(){
    n=read(),a=read(),b=read(),c=read(),x=read();
    for(i=1;i<=n;i++){
        __int128 k=x-a*i,d=gcd(b,c);
        if(k%d!=0 || k<b+c) continue;
        exgcd(b,c,k);
        __int128 L=c/d,R=b/d;
        if(l>0) {l%=L;if(l==0) l+=L;}
        else {__int128 cnt=(-l)/L+1;l+=cnt*L;}
		if(l>n) continue;
        r=(k-b*l)/c;
        if(r<=0) continue;
        if(r>n){
            if((r-n)%R==0) r=n;
            else r=r-((r-n)/R+1)*R;
            l=(k-c*r)/b;
            if(l>n || r<=0) continue;
        }
        __int128 p1=0,p2=0;
        if(r%R==0) p1=r/R;
        else p1=r/R+1;
        p2=(n-l)/L+1;
        ans+=min(p1,p2);
    }
    write(ans);
    return 0;
}
```


---

## 作者：hsaht2426 (赞：1)

**前言**：

标签：类欧几里得算法

**正文**：

注意到可以枚举 $i$，转化为扩展欧几里得问题。

但是在计算中可能溢出，并且细节很多。

我们不妨使用类欧，简单容斥即可。

[赛时代码](https://atcoder.jp/contests/abc315/submissions/44760642)

---

## 作者：Creeper_l (赞：1)

原题链接：[ABC315G](https://www.luogu.com.cn/problem/AT_abc315_g)

前置知识：扩展欧几里得算法。如果还不会扩欧的话，建议先去做[这道题](https://www.luogu.com.cn/problem/P5656)。

## 题意

给定 $n,a,b,c,k$。求有多少个 $x,y,z(x,y,z \le n)$ 满足 $ax+by+cz=k$。

## 思路

首先看到题目给出的方程式：$ax+by+cz=k$。我们会发现很像扩欧板子中的：$ax+by=k$。只不过又多了一个参数 $c$。所以我们可以转化一下式子，将原式写为：$ax+by=k-cz$。这样我们就可以用 $O(n)$ 的时间复杂度枚举 $z$ 的值，然后每一次计算有多少个合法的 $x,y$ 就行了。

首先用扩欧求出 $ax+by=\gcd(a,b)$ 这个方程的特解。然后将这个方程的特解乘上 $(k-cz)\div \gcd(a,b)$ 就是方程 $ax+by=k-cz$ 的特解了。然后我们通过加减增量的方式可以求出此时 $x$ 的最小合法解和最大合法解。最后就可以计算出答案了。总时间复杂度 $O(n)$。

还有几个注意事项：

- 这道题需要开 int128，不然计算过程中可能会炸。

- 如果 $k-cz$ 不整除 $\gcd(a,b)$，那么方程直接无解。

- $x,y$ 的范围都是 $1 \le x,y \le n$，计算最大最小解的时候要注意。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
#define ll long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
int n,a,b,c,k,x,y,Ga,Gb,ans,nx,ny;
ll N,A,B,C,K,ANS;
inline int Exgcd(int a,int b,int &x,int &y)
{
	if(b == 0){x = 1,y = 0;return a;}
	int d = Exgcd(b,a % b,x,y);
	int z = x;x = y,y = z - (a / b) * y;
	return d;
}
signed main()
{
	scanf("%lld%lld%lld%lld%lld",&N,&A,&B,&C,&K);
	n = N,a = A,b = B,c = C,k = K;
	int d = Exgcd(a,b,x,y);
	Ga = b / d,Gb = a / d;
	for(re ll i = 1;i <= n && k > c;i++)
	{
		k -= c;
		if(k % d != 0) continue;
		int G = k / d,minx,maxx;
		nx = x * G,ny = y * G;
		nx = (nx % Ga + Ga - 1) % Ga + 1;
		if(ny <= n) ny = n - (n - ny) % Gb;
		else ny = ny - ((ny - n - 1) / Gb + 1) * Gb;
		minx = max(nx,(k - ny * b) / a);
		ny = (ny % Gb + Gb - 1) % Gb + 1;
		if(nx <= n) nx = n - (n - nx) % Ga;
		else nx = nx - ((nx - n - 1) / Ga + 1) * Ga;
		maxx = min(nx,(k - ny * b) / a);
		if(maxx >= minx) ans += (maxx - minx) / Ga + 1;
	}
	ANS = ans;
	printf("%lld",ANS);
	return 0;
}

```


---

## 作者：hjqhs (赞：0)

先枚举 $i$，然后方程就是 $Bj + Ck=X-Ai$，然后 exgcd 求出一组特解。尝试加特解约束到 $[1,N]$，如果可以则累加贡献。  
细节是真的多。
```cpp
// Problem: G - Ai + Bj + Ck = X (1 <= i, j, k <= N)
// Contest: AtCoder - KEYENCE Programming Contest 2023 Summer（AtCoder Beginner Contest 315）
// URL: https://atcoder.jp/contests/abc315/tasks/abc315_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Created Time: 2023-11-19 17:04:08
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define int __int128
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define per(i, a, b) for (int i = a; i >= b; -- i)

using namespace std;
typedef long long ll;

const int N = 100005;
const int INF = 0x3f3f3f3f;

ll n, a, b, c, x;
int ans;	

int exgcd (int a, int b,int& x,int& y) {
	int d = a;
	
	if (!b) {x = 1, y = 0;}
	else {
		d = exgcd (b, a % b, y, x);
		y -= a / b * x;
	}
	
	return d;
}

void write (int x) {
	if (x < 0) putchar ('-'), x = -x;
	if (x > 9) write(x / 10);
	// if (x == 0) return putchar('0'), void();
	putchar (x % 10 + '0');
	return;
}

void solve () {
	cin >> n >> a >> b >> c >> x;
	
	rep (i, 1, n) {
		if (i * a > x) break;
		
		int tx = x - i * a, ty = __gcd (b, c), tz;
		if (tx % ty) continue; 
		
		int xx, yy;
		exgcd (b, c, xx, yy);
		xx *= tx / ty, yy *= tx / ty;
		
		// cout << "debug" << xx << ' ' << yy << ' ' << tx << ' ' << ty << '\n';
		
		if (xx <= 0) tz = (-xx) / (c / ty) + 1, xx += c / ty * tz, yy -= b / ty * tz;
		if (yy <= 0) tz = (-yy) / (b / ty) + 1, xx -= c / ty * tz, yy += b / ty * tz;
		if (xx > n) tz = (xx - n) / (c / ty) + ( (xx - n) % (c / ty) != 0 ), xx -= c / ty * tz, yy += b / ty * tz;
		if (yy > n) tz = (yy - n) / (b / ty) + ( (yy - n) % (b / ty) != 0 ), xx += c / ty * tz, yy -= b / ty * tz;
		
		// cout << "debug" << tz << '\n';
		
		if (xx >= 1 && xx <= n && yy >= 1 && yy <= n) {
			int ta = min ( (n - xx) / (c / ty), (yy - 1) / (b / ty) );
			int tb = min ( (n - yy) / (b / ty), (xx - 1) / (c / ty) );
			// cout << i << ':' << ta << ' ' << tb << '\n';
			ans += ta + tb + 1; 
		}
		
		// write(ans);
		// cout << ans;
		
	}
	
	write(ans);
	// cout << ans;
	
	return;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	solve();
	
	return 0;
}
``

---

## 作者：DerrickLo (赞：0)

我们可以枚举 $i$，然后就原方程变成了 $bj+ck=x-ai$，使用 `exgcd` 即可，注意要把求出来的 $j$ 和 $k$ 处理一下，把 $j$ 和 $k$ 都尽量变成在 $[1,n]$ 之内的数，如果可以就将答案更新。

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
long long a,b,c,x,n;
int ans;
int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;
		y=0;
		return a;
	}
	int d=exgcd(b,a%b,x,y);
	int t=x;x=y,y=t-(a/b)*y;
	return d;
}
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0' && ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10+'0');return;}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	n=read(),a=read(),b=read(),c=read(),x=read();
	for(int i=1;i<=n;i++){
		if(i*a>x)break;
		int xx,yy;
		int nw=x-i*a,lll=__gcd(b,c);
		if(nw%lll)continue;
		exgcd(b,c,xx,yy);
		xx*=nw/lll,yy*=nw/lll;
		if(xx<=0){
			int nww=(-xx)/(c/lll)+1;//变大于0
			xx+=c/lll*nww;
			yy-=b/lll*nww;
		}
		if(yy<=0){
			int nww=(-yy)/(b/lll)+1;//变大于0
			xx-=c/lll*nww;
			yy+=b/lll*nww; 
		}
		if(xx>n){
			int nww=(xx-n)/(c/lll);//变小于等于n
			if((xx-n)%(c/lll)!=0)nww++;
			xx-=c/lll*nww;
			yy+=b/lll*nww;
		}
		if(yy>n){
			int nww=(yy-n)/(b/lll);//变小于等于n
			if((yy-n)%(b/lll)!=0)nww++;
			xx+=c/lll*nww;
			yy-=b/lll*nww;
		}
		if(xx<=n&&yy<=n&&yy>=1&&xx>=1){ 
			int xxx=xx,yyy=yy;
			ans++;
			int aa=min((n-xx)/(c/lll),(yy-1)/(b/lll));
			int bb=min((n-yy)/(b/lll),(xx-1)/(c/lll));
			ans+=aa+bb;//求有多少种
		}
	}
	write(ans);
	return 0;
}
```

---

## 作者：12345678hzx (赞：0)

这个蒟蒻第一次在赛时想到 G 的正解，可惜没调出来。

由于 $N \le 10^6$，且让我们求出形如 $Ai+Bj+Ck=X$ 的解的个数，观察这个式子，容易发现它很像 exgcd 的形式，考虑将问题转化。

注意到 $N$ 的范围很小，且一次 exgcd 的时间复杂度为 $\log$ 级别的，所以显然可以想到去枚举 $k$，将原等式转化为 $Ai+Bj=X-Ck$ 去求解，注意到等式右边是一个常量，符合 exgcd $ax+by=c$ 的形式，所以直接用 exgcd 去求出合法解的数量即可，时间复杂度为 $O(N\log N)$。

但是题目有一个限制是 $i,j,k\le N$，所以在用 exgcd 时要注意这个点。还有计算过程中可能会爆 `long long`，所以要开 `__int128`，且负数除法在 C++ 中是向 $0$ 取整，所以负数除法还要加一些特判，总之这题思路很好想，细节很恶心，这就是此题为什么能放在 G 题的原因。

---

