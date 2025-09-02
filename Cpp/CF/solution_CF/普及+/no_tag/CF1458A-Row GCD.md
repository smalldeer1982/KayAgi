# Row GCD

## 题目描述

You are given two positive integer sequences $ a_1, \ldots, a_n $ and $ b_1, \ldots, b_m $ . For each $ j = 1, \ldots, m $ find the greatest common divisor of $ a_1 + b_j, \ldots, a_n + b_j $ .

## 样例 #1

### 输入

```
4 4
1 25 121 169
1 2 7 23```

### 输出

```
2 3 8 24```

# 题解

## 作者：dead_X (赞：7)

## 思路
首先我们都知道辗转相除法。

$$\gcd(x,y)=\gcd(x,y-x)\ (x<y)$$

然后这题做完了。

我们先将 $a$ 排序，然后注意到 $\gcd(a_i+b_j,a_{i+1}+b_j)=\gcd(a_i+b_j,a_{i+1}-a_i)$，于是只需要求 $a_1+b_j$ 和所有的 $a_{i+1}-a_i$ 的 $\gcd$ 即可。
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003],b[1000003];
signed main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; i++) a[i]=read();
	if(n==1)
	{
		for(int x;m--;) x=read(),printf("%lld ",x+a[1]);
		return 0;
	}
	sort(a+1,a+n+1);
	int t=a[2]-a[1];
	for(int i=3; i<=n; i++) t=__gcd(t,a[i]-a[i-1]);
	for(int x;m--;) x=read(),printf("%lld ",__gcd(x+a[1],t));
	return 0;
}
```

---

## 作者：wgyhm (赞：5)

# [Codeforces Round #691](https://codeforces.ml/contest/1459) C. Row GCD

### 题目大意

给定长度为 $n$ 的正整数序列 $a$，$m$ 次询问，对于每次询问，需要回答：

$\gcd(a_1+b_i,a_2+b_i,a_3+b_i,...,a_n+b_i),1\le i\le m$。

### 思路

根据辗转相除法~~人类智慧~~，易得：

$\gcd(x,y)=\gcd(x,y-x)$

推广一下：

$\gcd(a_1,a_2,a_3,a_4,a_5,...,a_n)$

$=\gcd(a_1,a_2-a_1,a_3-a_2,a_4-a_3,a_5-a_4,...,a_{n}-a_{n-1})$

所以：

$\gcd(a_1+b_i,a_2+b_i,a_3+b_i,...,a_n+b_i)$

$=\gcd(a_1+b_i,(a_2+b_i)-(a_1+b_i),(a_3+b_i)-(a_2+b_i),...,(a_{n}+b_i)-(a_{n-1}+b_i))$

$=\gcd(a_1+b_i,a_2-a_1,a_3-a_2,...,a_{n}-a_{n-1})$

$=\gcd(a_1+b_i,\gcd(a_2-a_1,a_3-a_2,...,a_{n}-a_{n-1}))$

预处理出 $\gcd(a_2-a_1,a_3-a_2,...,a_{n}-a_{n-1})$。

记得特判 $n=1$ 的情况。

由于差分可能导致出现负数，所以最后要输出绝对值。

```cpp
#include<bits/stdc++.h>
#define maxn 200005
#define rg register 
#define int long long
#define ull unsigned long long
#define put() putchar('\n')
using namespace std;
inline void read(int &x){
	int f=1;x=0;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
	x*=f;
}
int a[maxn],b[maxn];
inline int gcd(int x,int y){return !y?x:gcd(y,x%y);}
signed main(){
	rg int T,n,ans,m,i;
	read(n);read(m);
	if (n==1){
		read(a[1]);
		for (i=1;i<=m;i++) read(b[i]),printf("%lld ",a[1]+b[i]);
		return 0;
	}
	for (i=1;i<=n;i++) read(a[i]);
	for (i=n;i>=2;i--) a[i]=a[i]-a[i-1];
	int sum=a[2];
	for (i=3;i<=n;i++) sum=gcd(sum,a[i]);
	for (i=1;i<=m;i++){
		read(b[i]);
		printf("%lld ",abs(gcd(a[1]+b[i],sum)));
	}
	return 0;
}
```

类似的题(需要一定的ds基础)：[P2086 [NOI2012]魔幻棋盘](https://www.luogu.com.cn/problem/solution/P2086)



---

## 作者：__ikun__horro__ (赞：2)

众所周知：

$\gcd(a,b)=\gcd(a,b-a)$

------

证明：

设 $\gcd(a,b)=g$ 。则 $a\mod g=0$；且 $b\mod g=0$。可以得出 $(b-a)\mod g=0$。所以 $(a,b-a)$ 和 $(b,b-a)$ 都有公因数 $g$。

可是有可能 $(a,b-a)$ 和 $(b,b-a)$ 的最大公因数比 $g$ 大。所以可以假设 $gcd(a,b-a)=c'>c$。

那么 $a\mod c'=0$，$(b-a)\mod c'=0$，且 $(b-a)\mod c'=b\mod c'-a\mod c'$，可以得出 $b\mod c'=0$。

那么 $\gcd(a,b)=c'>c$，与原来矛盾。$(b,b-a)$ 同理。

故得证。

------

知道这个就简单了，题目让我们求 $\gcd(a_1+b_i,a_2+b_i,a_3+b_i,\dots,a_n+b_i)$，我们可以把 $2\sim n$ 项都减去第 $1$ 项，就变成了 $\gcd(a_1+b_i,a_2-a_1,a_3-a_1,\dots,a_n-a_1)$。可以发现第 $2\sim n$ 项都是不变的，可以预处理出 $2\sim n$ 项的最大公因数，然后枚举 $b_i$ 输出即可。

------

AC Code:

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
int n, m, a[200005], b[200005];
int gcd(int x, int y) {
	return y ? gcd(y, x % y) : x;
}
signed main() {
	//freopen("equipment.in", "r", stdin);
	//freopen("equipment.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) cin >> b[i];
	if (n == 1) {
		for (int i = 1; i <= m; i++) {
			cout << a[1] + b[i] << " ";
		}
		return 0;
	}
	sort(a + 1, a + n + 1);
	int c = a[2] - a[1];
	for (int i = 2; i <= n; i++) c = gcd(c, a[i] - a[1]);
	for (int i = 1; i <= m; i++) cout << gcd(a[1] + b[i], c) << " ";
	return 0;
}
```

这道题刚好是我们班模拟赛的题目，真不戳~

---

## 作者：Dementor (赞：2)

## 题解 CF1458A 【Row GCD】

首先，我们观察一下式子：

$$\gcd (a_1 + b_i, a_2 + b_i, ..., a_n + b_i)$$

发现对每个 $a_i$ 加上的数都是一样的，想想看 $\gcd$ 的计算方法中，有什么步骤是跟这个能扯上关系的。

发现我们是怎么写 $\gcd$ 的？

```cpp
long long gcd (long long a, long long b) {
	if (b == 0) return a;
	else return gcd (b, a % b);
}
```

其中的 $a \% b$ 其实就相当于一个 **减法** 的过程。

而 $x + y - (z + y) = x - z$ 能把 $y$ 去掉。

仿照这个，我们可以将 $a_i + b_k$ 和 $a_j + b_k$ 的 $\gcd$ 中都有的 $b_k$ 这个元素消掉，而剩下的就是一个定值：

$$\forall i, j , \gcd (a_i - a_j)$$

其实这个东西不用 $O (n ^ 2)$。就取 $n$ 个计算就好了。

你排个序，然后算这个 $\gcd$ ，之后呢对于每一个 $b$ ，假设算出来的是 $GCD$ ，那输出 $\gcd (a_1 + b, GCD)$ 就好了。

code

```cpp
#include <bits/stdc++.h> // saving code
using namespace std;
const int N = 200010;
long long a[N], b[N];
int n, m;
long long gcd (long long a, long long b) {
	if (b == 0) return a;
	else return gcd (b, a % b);
}
int main () {
	scanf ("%d %d", &n, &m);
	for (int i=1;i<=n;i++) scanf ("%lld", &a[i]);
	for (int i=1;i<=m;i++) scanf ("%lld", &b[i]);
	sort (a + 1, a + n + 1);
	if (n == 1) {
		for (int i=1;i<=m;i++) printf ("%lld\n", b[i] + a[n]);
		return 0;
	}
	long long GCD = 0, tmp = a[1];
//	cout << "att : " << gcd (3, 4) << " " << gcd (4, 3) << endl;
	for (int i=2;i<=n;i++) GCD = gcd (a[i] - tmp, GCD), tmp = a[i];
//	cout << GCD << endl;
	for (int i=1;i<=m;i++) {
		printf ("%lld\n", gcd (a[1] + b[i], GCD));
	}
	return 0;
}
```

---

## 作者：Warriors_Cat (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF1458A)。

> 题意：给两个序列 $a_1, ... a_n$ 和 $b_1, ... b_m$。对于每个 $i \in [1, m]$，求出 $\gcd(a_1 + b_i, a_2 + b_i, ..., a_n + b_i)$。

---

### $Solution:$

考虑 $\gcd$ 的一个变式：$\gcd(x, y) = \gcd(x, y - x)(x \le y)$。

于是原式就可以转化为：$\gcd(a_1 + b_i, a_2 - a_1, a_3 - a_2, ..., a_n - a_{n - 1})$。

先预处理 $x = \gcd(a_2 - a_1, a_3 - a_2,... a_n - a_{n - 1})$，对于每个 $i$，直接求出 $\gcd(a_1 + b_i, x)$ 即可。

over，时间复杂度为 $O(n \log a_i)$。

---

### $Code:$

以下为赛时代码。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define int long long
#define fi first
#define se second
#define y1 y_csyakioi_1
#define y0 y_csyakioi_0
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 200010;
int n, m, a[N], b[N], c[N];
inline int gcd(int x, int y){ return y == 0 ? x : gcd(y, x % y); }
inline void work(){
	n = read(); m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= m; ++i) b[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i) c[i] = a[i] - a[i - 1];
	int ans = c[2];
	for(int i = 2; i <= n; ++i) ans = gcd(ans, c[i]);
	for(int i = 1; i <= m; ++i) printf("%lld ", gcd(ans, b[i] + a[1]));
}
signed main(){
	int t = 1; while(t--) work();
	return 0;
}
```


---

## 作者：tzc_wk (赞：2)

考虑 $\operatorname{gcd}$ 的另一种计算方式，$\operatorname{gcd}(a_1,a_2,\dots,a_n)=\operatorname{gcd}(a_1,a_2-a_1,a_3-a_2,\dots,a_n-a_{n-1})$，那么就有 $\operatorname{gcd}(a_1+x,a_2+x,\dots,a_n+x)=\operatorname{gcd}(a_1+x,a_2-a_1,a_3-a_2,\dots,a_n-a_{n-1})$，预处理出 $G=\operatorname{gcd}(a_2-a_1,a_3-a_2,\dots,a_n-a_{n-1})$，然后对于每组询问，输出 $\operatorname{gcd}(G,a_1+b_j)$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
template<typename T>
void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){
		if(c=='-') neg=-1;
		c=getchar();
	}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2e5;
int n,qu;
ll a[MAXN+5],b[MAXN+5],gcd;
signed main(){
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++) gcd=__gcd(gcd,a[i+1]-a[i]);
	for(int i=1;i<=qu;i++){
		ll x;scanf("%lld",&x);
		printf("%lld ",__gcd(gcd,a[1]+x));
	}
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：1)

## 分析
将 $a$ 数组从小到大排序

设 $gcd(a_1+b_j,a_2+b_j...a_n+b_j)=k$

那么必定会有 $a_1+b_j=c_1 \times k$

$a_2+b_j=c_2 \times k$

$a_n+b_j=c_n \times k$

其中 $c_1 \leq c_2 \leq ... \leq c_n$

我们会发现 $(a_i+b_j)-(a_{i+1}+b+j)=(c_i-c_{i-1}) \times k$

即 $a_i-a_{i-1}=(c_i-c_{i-1}) \times k$

所以 $k$ 一定是 $a_2-a_1,a_3-a_2...a_n-a_{n-1}$ 的公因数

我们提前预处理这个东西

然后每次求的时候和 $a_1+b_j$ 取一个 $gcd$ 即可

注意特判 $n=1$ 和相等的情况
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define rg register
inline long long read(){
	rg long long x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1LL)+(x<<3LL)+(ch^48LL);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=2e5+5;
int n,m;
long long a[maxn],b[maxn],now,ans;
long long gcd(long long aa,long long bb){
	if(bb==0) return aa;
	return gcd(bb,aa%bb);
}
int main(){
	n=read(),m=read();
	for(rg int i=1;i<=n;i++) a[i]=read();
	for(rg int i=1;i<=m;i++) b[i]=read();
	std::sort(a+1,a+1+n);
	if(n==1){
		for(rg int i=1;i<=m;i++){
			printf("%lld\n",a[1]+b[i]);
		}
	} else {
		now=a[2]-a[1];
		for(rg int i=3;i<=n;i++){
			if(now==0) now=a[i]-a[i-1];
			else now=gcd(now,a[i]-a[i-1]);
		}
		for(rg int i=1;i<=m;i++){
			if(now==0) ans=a[1]+b[i];
			else ans=gcd(now,a[1]+b[i]);
			printf("%lld ",ans);
		}
		printf("\n");
	}
	return 0; 
}

```

---

## 作者：ZCETHAN (赞：0)

## C-[Row GCD](https://www.luogu.com.cn/problem/CF1458A)
我承认，考场上看到$\color{Red}{10^{18}}$就吓坏了。
其实很简单（就是坑多）。
考虑其特性，gcd中每一项都加上了一个相同的数，每次都重算是不现实的，因此，如果能预处理，那再好不过了。于是，gcd的性质中有一条能把加上的数刚好减去。
$$\gcd(a,b)=\gcd(a-b,b)$$
```
设g=gcd(a,b)
则ab可以表示为
a=x*g,b=y*g
则a-b=(x-y)*g
已知x与y互质，可得 x-y与y也互质(见下)
所以gcd(a-b,b)=g=gcd(a,b)

已知x与y互质，假设 x-y与y不互质
则有
x-y=a*k,y=b*k,k>1
所以,x=(a+b)*k
得gcd(x,y)=k>1，与条件不符
```
证明过程放在这里，~~便于越来越菜的我之后回来复习~~。
所以，对于式子
$$\gcd(a_1+b,a_2+b,\dots,a_n+b)$$
可以将前两项拿出来看看，就是$\gcd(a_1+1,a_2+1)=\gcd(a_1-a_2,a_2+1)$
所以，整个式子就变成了如下的鸭子：
$$\gcd(a_1-a_2,a_2-a_3,\dots,a_{n-1}-a_n,a_n+b)$$
所以对于每个b，只要先预处理出前面的一坨，就可以$O(log1e18)$，解决。
$\color{Red}{WA,REpoints:}$
注意，要先将a从大到小

要特判n=1和前面的一坨gcd=0的情况。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1<<30
using namespace std;
const int MAXN=2e5+10;
ll gcd(ll x,ll y){return x%y==0?y:gcd(y,x%y);}
ll a[MAXN],b[MAXN];
bool cmp(ll x,ll y){return x>y;}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
	sort(a+1,a+1+n,cmp);
	ll gd=0;
	for(int i=1;i<n;i++){
		if(a[i]-a[i+1]==0) continue;//0不要参与gcd的运算，小心nan
		if(gd==0) gd=a[i]-a[i+1];
		gd=gcd(gd,a[i]-a[i+1]);
	}
	for(int i=1;i<=m;i++){
		if(n==1||gd==0) printf("%lld ",a[n]+b[i]);
		else printf("%lld ",gcd(gd,a[n]+b[i]));
	}
}
```


---

## 作者：sysong (赞：0)

# 题解CF1458A Row GCD

### 题目描述

---

给出两个正整数序列 $a_1, \ldots, a_n$ 和 $b_1, \ldots, b_m$。

对于每个 $j = 1 , \ldots , m$ 求出 $\gcd(a_1 + b_j, \ldots, a_n + b_j)$ 。

---

### $Solution$

---

首先想到暴力做法：枚举每个 $i = 1 , \ldots , n$ ，求出对应的答案，但是显然超时。

那么考虑优化。

我们可以想到这个式子：$\gcd(a + k , b + k) = \gcd(a + k , b + k - (a + k)) = \gcd(a + k , b - a)$。

那么对于题目所求的答案也可以预处理出数组 $a$ 的差分（**绝对值**）的最大公约数，再对于每一个 $b_j$ 直接求解。

设 $g$ 为 $\gcd(a_2 - a_1 , \ldots , a_n - a_{n-1})$答案即为 $\gcd(a_1 + b_j , g)$

对于那个绝对值，我们可以排序，也可以直接调用`abs`函数。

**注意：用 $long \ long$**

---

### $C++ \quad Code$

---

```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
#define int long long
using namespace std;

inline int rd(){
	R int x=0;R char c=gc();//,f=1
	while(c>'9'||c<'0')c=gc();//{if(c=='-')f=-1;
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;//*f
}

int n,m,a[200010],g,k;

inline int gcd(int a,int b){
	while(b)
		a%=b,swap(a,b);
	return a;
}									// gcd 也可以写成递归形式，可能更简短一点

signed main(){
	n=rd(),m=rd();
	if(n==1){						// 如果 n=1，差分会出错，最好单独处理，最大公约数即为本身
		R int s=rd();
		for(R int i=1;i<=m;i++)
			printf("%lld%c",s+rd(),i==m?'\n':' ');
		return 0;
	}
	for(R int i=0;i<n;i++)a[i]=rd();
	g=abs(a[1]-a[0]);
	for(R int i=2;i<n;i++)g=gcd(g,abs(a[i]-a[i-1]));
	for(R int i=1;i<=m;i++)
		printf("%lld%c",gcd(g,a[0]+rd()),i==m?'\n':' ');
	return 0;
}

```

---



***by jsntsys***

$2020.12.20$

---

