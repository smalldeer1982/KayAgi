# Minimum Possible LCM

## 题目描述

给定一个由 $n$ 个整数 $a_1, a_2, \dots, a_n$ 组成的数组 $a$。

你的任务是找到一对下标 $i, j$（$1 \le i < j \le n$），使得 $lcm(a_i, a_j)$ 的值尽可能小。

$lcm(x, y)$ 表示 $x$ 和 $y$ 的最小公倍数（即最小的正整数，能够被 $x$ 和 $y$ 同时整除）。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 4 8 3 6
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
5
5 2 11 3 7
```

### 输出

```
2 4
```

## 样例 #3

### 输入

```
6
2 5 10 1 10 2
```

### 输出

```
1 4
```

# 题解

## 作者：da32s1da (赞：11)

大概是。。蓝题难度？

考虑对于$1-10^7$，枚举每个数的倍数，然后选出两个最小的数，更新答案。

复杂度$O(n\ln n)$，大概在$1.8\times 10^8$左右，可过。

注意一开始用相同的数字更新一下答案

```cpp
#include<cstdio>
const int N=1e7+50;
typedef long long LL;
int n,x,vis[N],t1,t2,s1,s2;
LL ans;
int main(){
	scanf("%d",&n);ans=1e14;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(vis[x])if(ans>x)ans=x,t1=vis[x],t2=i;
        //相同的数更新下答案
		if(!vis[x])vis[x]=i;
	}
	for(int i=1;i<N;i++){
		if(i>=ans)break;//可能有点用的优化
		s1=s2=0;
		for(int j=i;j<N;j+=i){
			if(!vis[j])continue;
			if(!s1)s1=j,s2=vis[j];
			else{
				if(ans>1ll*s1*j/i)
				ans=1ll*s1*j/i,t1=s2,t2=vis[j];//取出两个最小的更新答案
				break;//后面的不可能更新答案
			}
		}
	}
	if(t1>t2)t1^=t2^=t1^=t2;
	printf("%d %d\n",t1,t2);
}
```

---

## 作者：一扶苏一 (赞：6)

[本场比赛题解](https://www.cnblogs.com/yifusuyi/p/10727303.html)

# G

## Description

给定一个长度为 $n$ 的序列 $a$，找出两个数，最小化他们的最小公倍数

## Limitation

$2~\leq~n~\leq~10^6$

$1~\leq~a_i~\leq~10^7$

## Solution

考虑式子

 $$x~\times~y~=~\gcd(x,~y)~\times~\text{lcm}(x,~y)$$

于是有

$$\text{lcm}(x,~y)~=~\frac{x~\times~y}{\gcd(x,~y)}$$

考虑由于值域在 $1e7$ 范围内，于是任意两数的 $\gcd$ 也在 $1e7$ 范围内。我们考虑枚举这个 $\gcd$，然后枚举 $\gcd$ 的倍数是否出现在给定的数列中，如果有两个以上的倍数出现在给定的数列中，则取最小的两个，求一下 $\text{lcm}$，看一下是否能更新答案。取最小的两个的原因是考虑上式中分母不变，分子越小则 $\text{lcm}$ 越小，于是取较小的更优。又由于 $1e7$ 范围内的 $\gcd$ 包含了所有的情况，于是这样的正确性是对的。

考虑如果枚举到 $x$，数列中出现最小的两个 $x$ 的倍数是 $y$ 和 $z$，若 $x$ 只是 $y$ 和 $z$ 的因数，但不是最大的怎么办：考虑枚举到 $\gcd(y,~z)$ 时依然可以更新答案，由于 $x < \gcd(y,~z)$，所以用 $x$ 求出的答案要大于用 $\gcd(y,~z)$ 求出的答案，错误的答案会被正确的更新掉。

于是枚举每个数的倍数单次复杂度 $O(\log N)$，于是总复杂度 $O(N~\log N)$，其中 $N$ 为值域。

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif

typedef long long int ll;

namespace IPT {
  const int L = 1000000;
  char buf[L], *front=buf, *end=buf;
  char GetChar() {
    if (front == end) {
      end = buf + fread(front = buf, 1, L, stdin);
      if (front == end) return -1;
    }
    return *(front++);
  }
}

template <typename T>
inline void qr(T &x) {
  char ch = IPT::GetChar(), lst = ' ';
  while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
  while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
  if (lst == '-') x = -x;
}

namespace OPT {
  char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
  if (x < 0) {x = -x, putchar('-');}
  int top=0;
  do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
  while (top) putchar(OPT::buf[top--]);
  if (pt) putchar(aft);
}

const int maxn = 1000009;
const int maxt = 10000009;
const int upceil = 10000000;

int n, x, y;
ll ans = ((-1ull) << 1) >> 1;
int id[maxt];

int main() {
  freopen("1.in", "r", stdin);
  qr(n);
  for (int i = 1, k; i <= n; ++i) {
    k = 0; qr(k);
    if (id[k] && k < ans) {
      ans = k; x = id[k]; y = i;
    }
    id[k] = i;
  }
  for (int i = 1; i <= upceil; ++i) {
    int a = 0;
    for (int j = i; j <= upceil; j += i) if (id[j]) {
      if (a == 0) {
        a = j;
      } else {
        ll lcm = 1ll * a * j / i;
        if (lcm < ans) {
          x = id[a]; y = id[j]; ans = lcm;
        }
      }
    }
  }
  if (x > y) std::swap(x, y);
  qw(x, ' ', true); qw(y, '\n', true);
  return 0;
}
```





---

## 作者：ifffer_2137 (赞：0)

比较简单的题，感觉不到蓝。
### 题意
给定一个长度为 $n$ 的序列 $a$，找出两个数的**位置**，最小化他们的最小公倍数。
### 分析
小学二年级就知道：
$$lcm(a,b)=\frac{ab}{\gcd(a,b)}$$
观察到值域比较小，所以我们考虑直接枚举 $\gcd(a,b)$，要让两个数的乘积尽量小，用桶维护序列，从小到大枚举 $\gcd(a,b)$ 的倍数，贪心取小比较一下的即可。

这样做不难发现复杂度是 $\mathcal O(n\ln n)$ 的。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define inf 1e18
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e6+5;
const int maxm=1e7+5;
int n,v;
int a[maxn],t[maxm];
long long mn;
int l,r;
int ans[2];
inline int max(int x,int y){
	return x>y?x:y;
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		v=max(v,a[i]);
		t[a[i]]++;
	}
	mn=inf;
	for(int i=1;i<=v;i++){
		int x=0,y=0;
		for(int j=i;j<=v;j+=i){
			if(t[j]){
				if(x){
					y=j;
					break;
				}else if(t[j]>=2){
					x=y=j;
					break;
				}else{
					x=j;
				}
			}
		}
		if(x&&y){
			if(1ll*x*y/i<mn){
				mn=1ll*x*y/i;
				l=x,r=y;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==l&&!ans[0]) ans[0]=i;
		else if(a[i]==r&&!ans[1]) ans[1]=i;
		if(ans[0]&&ans[1]) break;
	}
	if(ans[0]>ans[1]) swap(ans[0],ans[1]);
	cout<<ans[0]<<" "<<ans[1]<<endl;
	return 0;
}
```

---

## 作者：small_john (赞：0)

## 前言

这是蓝题？我都能做出来还是蓝题？

## 思路

首先发现值域只有 $10^7$，还给四秒，考虑一些时间复杂度 $O(V\ln V)$ 的做法（$V$ 表示值域）。

转换题目所求，$\operatorname{lcm}(x,y)=\frac{x\times y}{\operatorname{gcd}(x,y)}$，而两个数的最大公因数不超过两数的最大值，也就是 $10^7$。

那么就可以钦定一个数 $x$ 为最大公因数，枚举其倍数，求出倍数中第一小和第二小的在数列中的位置，然后计算答案即可。

众所周知枚举 $x$ 及其倍数的时间复杂度均摊后是 $O(V\ln V)$ 的，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
	putchar(10);
}
const int N = 1e7+5;
int n,a[N],p[N],_p[N],mn[N],_mn[N];
inline long long get(int x)
{
    return 1ll*a[mn[x]]*a[_mn[x]]/x;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    read(n);
    for(int i = 1,x;i<=n;i++)
    {
        read(a[i]),x = a[i];
        if(!p[x]) p[x] = i;
        else _p[x] = i;
    }
    for(int i = 1;i<N;i++)
        for(int j = i;j<N;j+=i)
            if(p[j])
            {
                if(!mn[i])
                {
                    mn[i] = p[j];
                    if(_p[j]) _mn[i] = _p[j];
                }
                else if(!_mn[i]) _mn[i] = p[j];
            }
    long long ans = 1;
    for(int i = 2;i<N;i++)
        if(mn[i]&&_mn[i]&&get(i)<get(ans))
            ans = i;
    int x = mn[ans],y = _mn[ans];
    if(x>y) swap(x,y);
    write(x),putchar(32),write(y);
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题目思路

我们考虑到对于两个数 $x, y$，它们的 LCM 为：

$$\frac{x \times y}{\gcd ( x, y )}$$

我们发现 GCD 我们是熟悉的，我们可以枚举两个数的最大公约数 $g$，然后去枚举它的 $\frac{V}{g}$ 个倍数，选取最小的两个一定是最优的，记录一下位置，微操一下就好了。

不难发现时间复杂度为调和级数，时间复杂度 $O(V \ln V)$，$4$ 秒钟明显可过。

## 题目代码

代码：

```cpp
#include <bits/stdc++.h>
 
using namespace std;

#define int long long
#define ull unsigned long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )
 
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
 
char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}
 
template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 1e7 + 5;

int n, ans = 1e18, maxn;
int a[N], b[N], posl, posr, ansl, ansr;

void Solve () {
	cin >> n;
	for ( int i = 1; i <= n; i ++ ) {
		int x;
		cin >> x;
		a[x] ++;
		b[i] = x;
		maxn = max ( maxn, x );
	}
	for ( int i = 1; i <= maxn; i ++ ) {
		int l = 0, r = 0;
		for ( int j = 1; j <= maxn / i; j ++ ) {
			if ( !l ) {
				if ( a[j * i] > 1 ) {
					l = j * i, r = j * i;
					break;
				}
				else if ( a[j * i] == 1 ) {
					l = j * i;
				}
			}
			else if ( !r ) {
				if ( a[j * i] > 0 ) {
					r = j * i;
				}
			}
		}
		if ( !l || !r ) {
			continue;
		}
		if ( l * r / i < ans ) {
			ans = l * r / i;
			posl = l, posr = r;
		}
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( b[i] == posl ) {
			ansl = i;
			break;
		}
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( b[i] == posr && i != ansl ) {
			ansr = i;
			break;
		}
	}
	cout << min ( ansl, ansr ) << " " << max ( ansl, ansr );
}
 
signed main () {
#ifdef judge
	freopen ( "test.in", "r", stdin );
	freopen ( "test.out", "w", stdout );
	freopen ( "test.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

