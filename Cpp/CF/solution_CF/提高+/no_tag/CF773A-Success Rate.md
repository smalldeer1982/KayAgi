# Success Rate

## 题目描述

$\textsf{\textup{{\color{red}C}htholly}}$ 有一个 OJ。今天她发现她的提交次数是 $y$，通过次数是 $x$，因此她在 OJ 上的通过率是 $\frac{x}{y}$。

$\textsf{\textup{{\color{red}C}htholly}}$ 在 $[0,1]$ 区间内最喜欢的有理数是 $\frac{p}{q}$。于是她问了你一个问题：至少还要提交多少次代码，才能让通过率变为 $\frac{p}{q}$？

## 说明/提示

对于第一组测试数据，$\textsf{\textup{{\color{red}C}htholly}}$ 可以提交 $4$ 发 AC，通过率变为 $\frac{7}{14}$，也就是 $\frac{1}{2}$。

对于第二组测试数据，$\textsf{\textup{{\color{red}C}htholly}}$ 可以再提交 $10$ 发，其中 $2$ 发 AC，通过率变为 $\frac{9}{24}$，也就是 $\frac{3}{8}$。

对于第三组测试数据，通过率 $\frac{20}{70}$ 已经等于 $\frac{2}{7}$，不需要继续提交。

对于第四组测试数据，因为有未通过的提交记录，不可能使通过率等于 $1$。

## 样例 #1

### 输入

```
4
3 10 1 2
7 14 3 8
20 70 2 7
5 6 1 1
```

### 输出

```
4
10
0
-1
```

# 题解

## 作者：xzggzh1 (赞：3)

怎么题解里都是二分，这个可以不用二分而是直接 $O(1)$ 输出。

题意：

一共 $t$ 组数据,每组数据给出 $4$ 个整数 $x,y,p,q$ 。现在你一共提交了 $y$ 次，AC的次数是 $x$ 次。问你至少要再提交多少次，能让正确率刚好为    $\frac p{q}$。如果不可能，输出一行 $-1$ 。保证  $y>0,q>0$ ， $p$ 和 $q$ 互质。

---

直接考虑AC率是比较麻烦的，因为多了一次AC则多了一次提交，所以并不好直接算。

所以我们可以把AC率换算成 $\frac{\rm AC}{ \rm WA}$ 的值 ，然后计算要使
$\frac{\rm AC}{ \rm WA}$ 打到应有的值至少要多少次提交。

显然这个问题直接贪心就好了，考虑AC个数能使WA是整数的AC最少次数，然后计算即可。

对于无解的情况，只有全AC或全WA然后现有状况与输入不符合才会无解（原因留给读者自行思考）。

---

核心代码：

```cpp
while (t--) {
	int x, y, p, q;
	cin >> x >> y >> p >> q;
	if (p == 0) {
		cout << (x == 0 ? 0 : -1) << endl;
		continue;
	}
	if (p == q) {
		cout << (x == y ? 0 : -1) << endl;
		continue;
	}
	int t1 = (x + p - 1) / p;
	int t2 = ((y - x) + (q - p) - 1) / (q - p);
	cout << (q * 1LL * max(t1, t2) - y) << endl;
}
```

---

## 作者：Error_Eric (赞：2)

### 前言

哇蓝题！

### 正文

>题目大意:给定正整数 $x,y,p,q$,求最小正整数的 $y'$，使$\dfrac{x+x'}{y+y'}=\dfrac{p}{q}$($p$,$q$互质),其中 $0 \le x' \le y'$，如果没有，输出``-1`` 。


$\because \dfrac{x+x'}{y+y'}=\dfrac{p}{q}$

$\therefore $ 存在整数 $ k$,使 $k(x+x')=p , k(y+y')=q$

$\therefore\  kx+kx'=p , ky+ky'=q$

$\therefore x'=\dfrac{p-kx}{k} , y'=\dfrac{q-ky}{k}$

又$\because 0 \le x' \le y'$

$\therefore 0 \le\dfrac{p-kx}{k} \le\dfrac{q-ky}{k}$

$\therefore 0 \le p-kx \le q-ky$

我们现在要求最小的 $k$。

显然函数是单调的，我们选择二分法求 $k$ 。

```cpp

#include<iostream>
#include<algorithm>
#include<stdio.h>
long long x,y,ix,iy,p,q,t;
bool ok2(long long k){
	return k*q-y>=k*p-x and k*p-x>=0;//见分析部分
}
void solve(){
    long long l=1,r=0x7fffffff;//r取足够大即可
    while(l<r){
        long long mid=l+(r-l)/2;//取中间值（二分思路）
        if(ok2(mid)) r=mid;    //mid大于等于k最小值
        else l=mid+1;          //mid小于等于k最小值
    }
    printf("%lld\n",l==0x7fffffff?-1:l*q-y)//l*q-y=y';
} 
int main(){
    scanf("%lld",&t);//显然
    while(t--){//显然
        scanf("%lld%lld%lld%lld",&x,&y,&p,&q);//显然
        solve();//显然
    }
    return 0;
} 
```

---

## 作者：2018ljw (赞：1)

为什么都是二分啊...来一个 $\operatorname{exgcd}$ 的解法。

推导一下式子，假设我们提交 $a$ 发，其中有 $b$ 发通过。那么有 $\frac{x+a}{y+b}=\frac pq$，十字相乘得到 $qx+aq=py+bp$，移项可得 $aq+b(-p)=py-qx$。$p,q,py-qx$ 都是定的，所以可以利用 $\operatorname{exgcd}$ 求出一组无限制的 $a,b$。其中若无解则输出 $-1$。我们的答案即为所得的 $b$。

那么通解就是 $a+k(-p),b-kq$。取 $k$ 为负值即可得到通解 $a+kp,b+kq$。

限制为 $0\le a\le b$ 的前提下让 $b$ 尽量小，所以我们顺次进行。
1. 化成非负。这部分和模板题差不多，不做详细解释。无解条件：$b$ 化为非负后，$a<0$ 且 $y=0$。原因显然，无论如何操作 $a$ 都不可能在保证 $b$ 非负的前提下变为非负。根据我们的通解式和 $p,q$ 非负且合法可知 $a,b$ 应该同增同减。
2. $a\le b$。根据通解形式，$k$ 每增大 $1$，就能追上 $q-p$ 的差距，直接计算即可。无解条件：$a>b$ 且 $p\ge q$，原因显然。
3. $b$ 最小。还是从差距与非负两个角度入手，可以得出 $k\le\min{\frac ap,\frac bq,\frac{b-a}{q-p}}$（均下取整）。特别地，认为除以 $0$ 得到的结果为 $+\infty$。

然后？没了。需要注意的是 $py-qx$ 的级别是 $10^{18}$，扩欧求完一乘可能爆 `long long`，所以需要写 `int128` 或高精。

代码如下，代码中的 $a,b,c$ 是方程系数，$n,m$ 为方程的解。
```cpp
#include<bits/stdc++.h>
#define ns {printf("-1\n");continue;}//No Solution
#define i128 __int128_t
using namespace std;
i128 gcd(i128 x,i128 y){
	return y==0?x:gcd(y,x%y);
}
void exgcd(i128 x,i128 y,i128 &a,i128 &b){
	if(!y){
		a=1;b=0;
		return;
	}
	exgcd(y,x%y,a,b);
	i128 c=a;
	a=b;
	b=c-(x/y)*b;
}
i128 read(){
	i128 x=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();;
	return x;
}
void write(i128 x){
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
int main(){
	int t=read();
	i128 x,y,p,q;
	while(t--){
		x=read();y=read();p=read();q=read();
		//求解
		i128 a=q,b=-p,c=p*y-q*x;
		i128 r=gcd(a,b);
		if(c%r)ns;
		a/=r;b/=r;c/=r;
		i128 n,m;
		exgcd(a,b,n,m);
		n*=c;m*=c;
		//m 化为非负。
		//由于预设 b=-p，第二项系数为正，采用正常的通解求法。
		i128 dis=(m-a+1)/a;
		m-=a*dis;
		n+=b*dis;
		if(a<0)a=-a,b=-b;b=-b;
		//b 化为正、第二项系数变负。之后采用先前提到的通解求法。
		//n 化为非负。
		if(n<0){
			if(!b)ns;
			dis=(n-b+1)/b;
			m-=a*dis;
			n-=b*dis;
		}
		//追平 n,m 差距
		if(n>m){
			if(b>=a)ns;
			dis=a-b;
			i128 d2=n-m;
			d2=(d2+dis-1)/dis;
			m+=a*d2;
			n+=b*d2;
		}
		//最小化 m
		if(n>=0&&m>=0){
			dis=m-n;
			i128 d2=a-b;
			i128 mk;
			if(d2==0)mk=1ll<<30;
			else mk=dis/d2;
			if(b&&n/b<mk)mk=n/b;
			if(a&&m/a<mk)mk=m/a;
			m-=mk*a;
			n-=mk*b;
		}
		write(m);puts("");
	}
}
```

---

## 作者：WOWHandsome (赞：1)

**更详细的推导过程，求通过qaq**

我们知道，提交了 $y$ 次，AC 了 $x$ 次，正确率为 $x/y$。

此时，我们要再提交 $n$ 次，其中 AC $s$ 次才能满足正确率为 $p/q$。

那么，我们可以得出 $\frac{x+s}{y+n} = \frac{p}{q}$。

因为题目说明 $p,q$ 互质，我们可以设 $\frac{x+s}{y+n} = \frac{kp}{kq}$ ,

此时 $x+s=k \times p, \ y + n = k \times q$。

那么通过简单的移项可以得出，$x = k \times p -s, \ y = k \times q - n$。

如果 $k$ 越大，那么 $s,n$ 也越大。可以发现很明显的 **单调性**，联想到 **二分答案**。

还有最后一个问题：题目要求如果不可能，输出 $-1$。因为本题的 $k$ 是递增的，如果 $k$ 是无穷大，则判断不可能。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int t;
ll p, q, a, b;   // OI十年一场空，不开longlong见祖宗

bool check(ll mid)
{
	// 判定 
	return mid * b - q >= mid * a - p && mid * a - p >= 0;
}

int main()
{
	scanf("%d", &t);
	while (t--) { 
		scanf("%lld%lld%lld%lld", &p, &q, &a, &b);
		ll l = 0, r = 0x7fffffff;
		while (l < r) {  //二分答案
			ll mid = (l + r) / 2;
			if (check(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%lld\n", (l >= 0x7fffffff) ? (-1) : (l * b - q));  //如果l是无穷大，输出-1；否则输出答案
	}
	return 0;
} 
```

---

## 作者：djh123 (赞：1)

设加入$n$个提交，其中有$s$个是成功的，那么要满足$\frac{x+s}{y+n}=\frac{p}{q}$

由于$p,q$互质，我们可以设分母是$kq$，那么$n=kq-y,s=kp-x$。

显然可以二分$k$值的大小，要满足$n\ge s \ge 0$

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int uint;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair
#define rep(x, a, b) for(int x = (a); x <= (b); ++ x)
#define per(x, a, b) for(int x = (a); x >= (b); -- x)
#define rop(x, a, b) for(int x = (a); x < (b); ++ x)
#define por(x, a, b) for(int x = (a); x > (b); -- x)
#define forE(x, a) for(int x = head[a]; x; x = nxt[x])

#ifdef DEBUG
#define debug(x) cerr << #x << ": " << x << '\n'
#else
#define debug(x)
#endif

void open(const char *s){
    #ifdef DEBUG
    char str[100];
    sprintf(str,"%s.in",s);
    freopen(str,"r",stdin);
    sprintf(str,"%s.my",s);
    freopen(str,"w",stdout);
    #endif
}

const db eps = 1e-8;
const int inf = 0x3f3f3f3f;
const int Minf = 0x7f7f7f7f;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
const LL MINF = 0x7f7f7f7f7f7f7f7fll;

LL p, q, a, b; 
bool check(LL mid) { return mid * b - q >= mid * a - p && mid * a - p >= 0; }
int main() {
    int T; scanf("%d", &T);
    while(T --) {
        scanf("%I64d%I64d%I64d%I64d", &p, &q, &a, &b);
        LL l = 0, r = 2e9;
        while(l < r) {
            LL mid = (l + r) >> 1;
            if(check(mid)) r = mid;
            else l = mid + 1;
        }
        printf("%I64d\n", l >= 2000000000 ? -1 : l * b - q);
    }
}
    

```

---

## 作者：WerChange (赞：0)

（提供二分做法）
## 前言
听说是史上最简单蓝题，做了一下。
## 题意
已知 $x,y,p,q$，通过只让 $y$ 加 $1$ 或 $x,y$ 同时加 $1$，使得满足：
$$
\frac{x'}{y'}=\frac{p}{q}
$$
## 思考
目标状态为 $\frac{p}{q}$，考虑到这是个比值，自然 $\frac{x'}{y'}=\frac{kp}{kq}$。

明显地，这里的 $k$ 如果合法，那就一定有更小的 $k$。

所以考虑二分。

限制条件呢？

因为无论如何决策，$y$ 都会加 $1$；而 $x$ 不一定每一次决策都加 $1$。即 $\Delta y\geq \Delta x$。

所以保证 $\Delta x \leq \Delta y$ 就好了。即 $kp-x\leq kq-y$。

需要注意的是，有一点需要特判：

+ $p=0$ 时
    - $x> 0$，输出 $-1$
    - $x=0$，输出 $0$

## 代码
考虑到数据范围均小于 $10^9$，所以右端点不可以取太大，否则越界变成负数，右端点取 $10^{10}$，开个 `long long` 就好了。

code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

int x,y,p,q;

bool check(int md)
{
    return p*md-x<=q*md-y && p*md>=x;
}

void solve()
{
    scanf("%lld%lld%lld%lld",&x,&y,&p,&q);
    if(p==0)
    {
        if(x)
            puts("-1");
        else
            puts("0");
        return;
    }

    int l=1,r=1e10,mid,ans=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid))
            r=mid-1,ans=mid;
        else
            l=mid+1;
    }
    
    if(ans==-1)
        puts("-1");
    else
        printf("%lld\n",ans*q-y);
}

signed main()
{
    signed T;
    scanf("%d",&T);
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：analysis (赞：0)

真的是蓝题？这真的不是小学数学题？

我们是要求满足（其中 $a$ 为正确数，$b$ 为总数）

$$
\frac{x + a}{y + b} = \frac{p}{q}
$$

的最小 $b$。

我们可以先把右式的分子分母变化到与 $\frac{x}{y}$ 类似的大小。

```cpp
int bs1 = x / p + (x % p != 0);
int bs2 = y / q + (y % q != 0);
int bs = max(bs1,bs2);
pp = p * bs;
qq = q * bs;
```

然后判断，如果 $x$ 和 $pp$ 的差值小于 $y$ 和 $qq$ 的差值就可以输出了。

否则继续放大。

如果 $p \geq q$（其实就是 $p = q$），那么放大是无效的。

然后没了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
signed main()
{
    cin>>t;
    while(t--)
    {
        int x,y,p,q,pp,qq;
        cin>>x>>y>>p>>q;
        if(p == 0)
        {
            if(x != 0)cout<<-1<<'\n';
            else cout<<0<<'\n';
            continue;
        }
        int bs1 = x / p + (x % p != 0);
        int bs2 = y / q + (y % q != 0);
        int bs = max(bs1,bs2);
        pp = p * bs;
        qq = q * bs;
        if(pp - x > qq - y && p >= q)cout<<-1<<'\n';
        else if(pp - x > qq - y)
        {
            int cj = pp - x - qq + y;
            int num = cj / (q - p) + (cj % (q - p) != 0);
            pp += num * p;
            qq += num * q;
            cout<<qq - y<<'\n';
        }
        else cout<< qq - y <<'\n';
    }
}
```

---

