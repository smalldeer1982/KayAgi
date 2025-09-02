# [ABC150D] Semi Common Multiple

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc150/tasks/abc150_d

長さ $ N $ の偶数からなる正の整数列 $ A=\ {a_1,a_2,...,a_N} $ と、整数 $ M $ が与えられます。

任意の $ k(1\ \leq\ k\ \leq\ N) $ に対して以下の条件を満たす正の整数 $ X $ を $ A $ の「半公倍数」と定義します。

- $ X=\ a_k\ \times\ (p+0.5) $ を満たす負でない整数 $ p $ が存在する。

$ 1 $ 以上 $ M $ 以下の整数のうちの $ A $ の半公倍数の個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^9 $
- $ 2\ \leq\ a_i\ \leq\ 10^9 $
- $ a_i $ は偶数である。
- 入力は全て整数である。

### Sample Explanation 1

\- $ 15\ =\ 6\ \times\ 2.5 $ - $ 15\ =\ 10\ \times\ 1.5 $ - $ 45\ =\ 6\ \times\ 7.5 $ - $ 45\ =\ 10\ \times\ 4.5 $ より、$ 15,45 $ は $ A $ の半公倍数です。$ 1 $ 以上 $ 50 $ 以下の整数に他に $ A $ の半公倍数はないので、答えは $ 2 $ となります。

### Sample Explanation 2

答えが $ 0 $ の場合もあります。

## 样例 #1

### 输入

```
2 50
6 10```

### 输出

```
2```

## 样例 #2

### 输入

```
3 100
14 22 40```

### 输出

```
0```

## 样例 #3

### 输入

```
5 1000000000
6 6 2 6 2```

### 输出

```
166666667```

# 题解

## 作者：Tx_Lcy (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/AT4882)
## 思路
先化简一下柿子。

$X=a_i \times (p+0.5)=\frac{a_i}{2}+a_i \times p$。

$X=\frac{a_i}{2} \times (1+2p),\ p \in N$。

显然，$2p+1$ 是一个**正奇数**。

又因为 $X$ 对于**所有** $a_i$ 都满足，我们不妨**设 $a_i$ 的最小公倍数为 $B$**，那么 $X=\frac{B}{2} \times(1+2p)$。

我们不妨再次变换一下形式，令 $X=\frac{B}{2}+Bp=Bp+ \frac{B}{2}$，我们发现这是一个**一次函数**，又因为 $1 \le X \le M$，我们把 $X=M$ 带入原式，得 $M=Bp+\frac{B}{2}$，$p=\frac{M- \frac{B}{2} }{B}$。

又因为 $0 \le p$，所以一共可以取 $\left\lfloor\dfrac{M- \frac{B}{2} }{B}+1\right\rfloor$ 个 $p$，每个 $p$ 又对应了一个唯一的 $X$，所以 $sum_X=\left\lfloor\dfrac{M- \frac{B}{2} }{B}+1\right\rfloor$。

**但是，我们上面还有一个条件 $2p+1$ 是正奇数没用呢！**

$X=\frac{a_i}{2} \times (1+2p)$，设 $b_i=\frac{a_i}{2}$，设 $b_i$ 的最大公约数为 $B_1$，显然 $B_1=\frac{B}{2}$。$2p+1= \frac{X}{b_i}$，显然 $2p+1$ 是奇数，那么 $\frac{X}{b_i}$ 也要是奇数，**也就是 $\frac{B_1}{b_i}$ 要是奇数**，如果是偶数，那么显然无解。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=1e6+10;
int a[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    int now=1;
    for (rint i=1;i<=n;++i) cin>>a[i],now=lcm(now,a[i]);
    for (rint i=1;i<=n;++i)
        if (((now/2)/(a[i]/2))%2==0) return cout<<"0\n",0;
    cout<<(int)((m-(now/2.0))/now+1)<<'\n';
    return 0;
}

```


---

## 作者：watcher_YBH (赞：4)

# 题目：
求出所有在 $1 \sim m$ 范围内的“半公倍数”有多少个。
# 思路：
所谓半公倍数，就是 $x = a_i \times (p+0.5)$，其中满足 $p$ 为整数。

但如果我们将所有的式子两边同时乘 $2$，我们便可得知 $2x = a_i \times (2 p + 1)$，则 $p + 0.5$ 就变成了整数，所以 $2x$ 为所有 $a_i$ 的整数倍，即所有数的公倍数。

因为我们要求出满足要求的 $x$ 有多少个，则其他的数一定是最小 $x$ 的倍数，并且是奇数倍（因为在等式中左边的 $x$ 乘多少，右边也得跟着乘多少，而 $a_i$ 不变，则乘的这个数一定会乘在 $p+0.5$ 上，但 $p+0.5$ 的倍数也必须是 $p+0.5$ 的形式，所以满足要求的 $x$ 一定是最小 $x$ 的奇数倍）。

但是，如果 $\frac{2x}{a_i}$ 为偶数，那么 $p$ 就一定不是整数，所以这种情况下，就直接输出 $0$，并推出程序。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define max(a,b) ((a)>(b)?a:b)
#define min(a,b) ((a)<(b)?a:b)
using namespace std;
const int MAX = 1e5+5;
int n,m;
int a[MAX];
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int lcm(int a,int b){return a*b/gcd(a,b);}
signed main(){
	cin>>n>>m;
	int lc1 = 1;
	for(int i = 1; i<=n; i++)
		cin>>a[i],lc1 = lcm(lc1,a[i]);// 求出所有数的公倍数，即2x
	for(int i = 1; i<=n; i++)
        if((lc1/a[i])%2 == 0)// 如果2x/a[i]为偶数，那么p就不为整数，所以输出0
            cout<<0,exit(0);
	int lc = lc1/2,ans = 0;// lc为半公倍数，即x（并且此时x为最小半公倍数） 
	for(int i = 1; i*lc<=m; i+=2) ans++;// 看看有几个奇数倍x在1~m之间 
	cout<<ans;
	return 0;
}
```


---

## 作者：极寒神冰 (赞：3)

$X$是$A$的半公倍数的条件重新定义如下:

- 对于任意的$k(1\leq k\leq N)$都有一个满足$X=\frac{a_k}{2}\times (2p+1)$的非负整数$p$

由于$X$是$\frac{a_k}{2}$的奇数倍，因此可以分为以下两个条件

- 对于任意的$k(1\leq k\leq N)$,$X$是$ \frac{a_k}{2}$的倍数
- 对于任意的$k(1\leq k\leq N)$,$X$可以被$2$整除的次数与$\frac{a_k}{2}$可以被$2$整除的次数相同

所以当存在$i$,$j$,$a_i$可被$2$整除的次数与$a_j$可被$2$整除的次数不同时，显然不存在一个合法的$X$

考虑何时不存在这样的$i$,$j$特判掉即可

令$\frac{a_1}{2},\frac{a_2}{2},...,\frac{a_N}{2}$的最小公倍数为$T$，显然所有$T$的奇数倍就是满足条件的$X$

注:以上大部分翻译自官方题解pdf

或者直接考虑有两种数字时，直接观察"半公倍数"

如果是$[6,10]$时,则变为$3$的奇数倍和$5$的奇数倍，并替换为原数的最小公倍数,并且$15$的奇数倍是一个条件.

而如果是$[6,8]$,则变为$3$的奇数倍和$4$的奇数倍，但可以发现这显然是不兼容的，依次类推.

- 当$a$和$b$被$2$整除的次数不同时:无解
- 当$a$和$b$被$2$整除的次数相同时:取最小公倍数替换


---

## 作者：洛璟 (赞：3)

## Solution:

我们看到这道题的时候，也许是毫无思路的，但这很正常，因为我也是。

考虑推规律。

我们会发现，当 $p=0$ 时，所有数都为原来的 $\frac{1}{2}$；

我们也会想到，如果没有这个0.5，这就是一道简单的求最小公倍数的题目。

那么我们对于枚举一个区间内的最小公倍数是如何枚举的？从他们的最小公倍数开始枚举，直到超过范围。

那么我们也考虑相同的想法，但是由于0.5的存在，我们这个需要自己手动推规律（不过貌似另外的题解已经给出了证明公式……），我们可以从所有的数的0.5倍的数字的最小公倍数开始枚举，每次加上原来给定的数字的最小公倍数，我们不难发现每一次得到的数字，就是题目所要求的 $X$。

#### example:

```
input:
3 50
2 6 10

```

我们来模拟一下

$2 \times 0.5=1$ ， $2\times 1.5=3$ …… $2\times12.5=45$……

$6\times0.5=3$ ，$6\times 1.5=9$……

其实枚举到这里，应该也就有人明白了，和原来的求最小公倍数相比，这道题的差距在于枚举的起点不同，后面仍然是每次加上给定的数字，也就是与求最小公倍数没有区别。

再回到上面的例子，我们会发现，他们三个数的最小公倍数是30，而他们除2得到的数字的最小公倍数为15，而他们按照题意得出的$X$，是45。

好，规律出来了，接下来我们只需要用一个简单的等差数列公式，就可以求出这个区间内的 $X$ 的个数，也就是说，我们所要求的 $X$ 就是从原数除2之后的最小公倍数开始，每次加上原数的最小公倍数的数字。

-----
考虑答案为0的情况。

我们可以发现，$X=a_{i}\times(p+0.5)$，由$a_{i}$为偶数，变换原式，得到$X=\frac{1}{2}a_{i} \times (2p+1)$ 由于 $p$ 是一个自然数，我们不难得出，$2p+1$ 必然是一个奇数，那么，一旦出现 $2p+1$ 为偶数的情况，证明此数列必然是无解的了。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long g = 1, qaq = 1;
int n, m;
int a[100010];
int gcd(int x, int y)
{
    return x % y == 0 ? y : gcd(y, x % y);
}
long long lcm(long long x, long long y)
{
    return x * y / gcd(x, y);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1;i <= n;i++)
    {
        scanf("%d", &a[i]);
        g = lcm(a[i], g);
        qaq = lcm(a[i] >> 1, qaq);
    }
    for (int i = 1;i <= n;i++)
    {
        if (qaq / (a[i] / 2) % 2 == 0)//特判p为奇数还是偶数
        {
            cout << 0;
            return 0;
        }
    }
    long long ans = (m - g / 2) / g + 1;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
这道题其实不难，也不用化简式子。我们令 $p=0$，求一次半公倍数，得到的就是最小的半公倍数，一直扩大这个数就行了。只要一个数乘一个奇数，那么还会是一个奇数。那么答案就为:
```cpp
for(int i=1;i*lcm<=m;i+=2)
	++ans;
```
其中 $lcm$ 表示最小的半公倍数。这里还有坑，当 $lcm\div(a_i\div2)\bmod2=1$ 时，$p$ 就不为整数，不满足条件，答案就为零。
# Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[114514];
int l=1;
int n,m;
int ans;
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i],a[i]/=2;
	for(int i=1;i<=n;i++)
	{
		l=l*a[i]/__gcd(l,a[i]);
		if(l>m)
		{
			cout<<0;
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
		if((l/a[i])%2==0)
		{
			cout<<0;
			return 0;
		}
	for(int i=1;i*l<=m;i+=2)
		++ans;
	cout<<ans;
}
```


---

## 作者：Ranmantic_Tea (赞：1)

这个题的可能情况太毒瘤了。

我们考虑这些半公倍数。

我们可以得知的是这些半公倍数是公倍数的一半的倍数。但是偶数倍不行，因为显然的是偶数倍会使得商为整数，这是不合法的。

我们考虑将这个最小的半公倍数求出来，即公倍数的一半。

所以我们先求出最小公倍数。

蒟蒻不会用函数，所以介绍用最大公因数求。

```cpp
gcd=__gcd(sum,a[i]),sum=sum*a[i]/gcd；
```

~~非常简便~~。

当然你也可以和楼上一样用自带的函数 $\operatorname{lcm}$。

接下来我们就可以直接得出答案。

因为范围要小于 $k$，所以我们选取小于的数，而且保证为半公倍数的奇数倍，所以要向上取整。

好了，毒瘤来了。

我们只是贪心的考虑着我们一定可以找到答案。

但是有没有不可能的情况呢。

可以知道的是答案一定是公倍数一半的奇数倍。

我们就需要判断这个东西难道真的合法吗？

我们从公倍数入手，如果他不满足公倍数，有的数有可能不可以满足整除，也就不能满足 $0.5$ 这个部分。

那一半呢?同样，这是满足 $0.5$ 的条件。

最后考虑到选部分的时候。就发生了问题。

不排除一些数会因为除以了二，依然为整数倍的关系，一些数不为。

我们考虑解决，要满足 $0.5$ 的条件我们只能够除以 $2$。

但是！

除以二之后，原本为整数的数就变成了小数，原本为小数的数就变成了整数。

但是！

有没有可能全部都没有那个 $0.5$ 呢？

我们考虑整数倍关系中的公倍数一半的奇数倍一定是整数才可以形成。

那么，公倍数中一定存在一个质因子为 $2$。这个 $2$ 一定是在这些数当中的质因子转过来的。

所以，必然有的数成倍数关系时，有的数不是。


即！

# 无解！！！

蒟蒻最近遇到最最最难搞的题目！

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
#define mid (l+r)>>1
//
//
//
using namespace std;
inline ll read() {
	ll f=0,t=0;
	char c=getchar();
	while(!isdigit(c)) t|=(c=='-'),c=getchar();
	while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
	return t?-f:f;
}
inline void out(ll x) {
	if(x<0) putchar('-');
	if(x>9) out(x/10);
	putchar('0'+x%10);
}
ll a[100005],tmp[100005];
int main() {
	ll n=read(),k=read();
	tmp[1]=a[1]=read();
	ll gcd=a[1],sum=a[1];
	ll MX=1;
	FOR(i,2,n) tmp[i]=a[i]=read(),gcd=__gcd(sum,a[i]),sum=sum*a[i]/gcd;
	MX=sum;
	MX/=2;
	FOR(i,1,n) if(MX%a[i]==0) return cout<<'0',0;
	cout<<k/MX/2+((k/MX)%2==1?1:0);
	return 0;
}
/*
*/

```
——end——

---

## 作者：_edge_ (赞：1)

为啥没有 exCRT 的题解呀，个人认为 exCRT 不是更好想么。

首先我们需要知道求啥，求的是 $1 \le X \le m$，同时满足 $X=A_i \times x_i + B_i$，转换一下就变成了 $X \equiv B_i \pmod {A_i}$。

这个东西我们可以直接用 exCRT 进行合并。

具体的我们举出两个例子 $A_1 \times x_1 + B_1 = A_2 \times x_2 + B_2$，然后移项 $A_1 \times x_1 - A_2 \times x_2 = B_2 - B_1$，然后可以直接上 exgcd 解二元一次方程。

注意，这里如果 $B$ 超过了 $m$ 那么答案是 $0$，否则有溢出的风险。

同理 $A$ 如果超过 $m$，那么答案就是 $1$ 或者 $0$。

注意点细节就可以了。

```cpp
#include <iostream>
#include <cstdio>
#define int __int128
using namespace std;
const int INF=1e5+5;
int n,a[INF],b[INF],A,B,xx,yy,cc,m;
int read() {
        char ch=getchar(); int x=0,f=1;
        while (ch<'0' || ch>'9') {if (ch=='-') f=-1; ch=getchar();}
        while (ch>='0' && ch<='9') {x=(x<<1)+(x<<3)+(ch^48); ch=getchar();}
        return x*f;
}
void write(int x) {
        if (x<0) {putchar('-'); x=-x;}
        if (x>9) write(x/10);
        putchar(x%10+'0');
        return;
}
int exgcd(int x,int y) {
        if (!y) {xx=cc/x; yy=0; return x;}
        int t=exgcd(y,x%y);
        int tmp=xx; xx=yy; yy=tmp-x/y*yy;
        return t;
}
signed main()
{
//		freopen("78.txt","r",stdin);
        n=read();m=read();
        for (int i=1; i<=n; i++) {
        	int x=0;x=read();
//            a[i]=read(); b[i]=read();
			b[i]=x/2;a[i]=x;
        }
        A=a[1]; B=b[1];int K=0,K1=0;
        for (int i=2; i<=n; i++) {
                cc=b[i]-B; int tt=exgcd(A,a[i]);
                if (cc%tt) {cout<<"0\n"; return 0;}
                // write(xx); putchar(' ');
                int Mod=a[i]/tt;
                int ans1=(xx%Mod+Mod)%Mod;
                int ans=B+ans1*A;
                A=A*a[i]/tt; B=ans;
                if (A>m) K=1;
				if (B>m) K1=1;
                // write(A); putchar(' ');
                // write(ans); putchar(' ');
                // write(B); putchar('\n');
        }
        if (K1) {cout<<"0\n"; return 0;}
		if (m-B<0) {cout<<"0\n"; return 0;}
		if (m-B==0) {cout<<"1\n"; return 0;}
        if (!K) write((m-B+A-1)/A);
        else write(1);
        putchar('\n');
        return 0;
}
```


---

## 作者：STARSczy (赞：1)

# 思路：
我们可以求出这 $n$ 个数的最小公倍数 $lcm$，从 $\frac{lcm}{2}$ 开始，每次加 $lcm$ ，求出有多少个数，即 $ans=\sum\limits_{i=0}^{\frac{lcm}{2}+i\times lcm \le m}1$。但是，由于 $X=a_i\times(p+0.5)$，根据式子可得 $X=\frac{a_i}{2}\times(2p+1)$，其中，$2p+1$ 是个奇数，$a_i$ 为偶数，因此 $\frac{a_i}{2}$ 为整数，所以我们还需判断 $lcm \div a_i$ 是否为奇数。若为偶数，直接输出 $0$；若为奇数，则输出 $ans$。 

# 代码：
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int maxn=1e6+10;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}

inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}

int n=read(),m=read(),_lcm,ans,a[maxn];

signed main(){
	for(int i=1;i<=n;++i) a[i]=read();
	_lcm=a[1];
	for(int i=2;i<=n;++i) _lcm=_lcm/__gcd(_lcm,a[i])*a[i];//求最小公倍数
	for(int i=1;i<=n;i++) if((_lcm/a[i])%2==0) return cout<<0,0;//判断是否符合条件
	write((m+_lcm/2)/_lcm);//输出答案
	return 0;
}
```

---

## 作者：lilong (赞：0)

考虑求出最小的 $X$。有了这个 $X$ 后，答案显然为 $\lceil \dfrac{ \lfloor \dfrac{M}{X} \rfloor }{2} \rceil$。大胆推测 $X$ 与 $\operatorname{lcm}(a_1,a_2,\cdots,a_N)$ 有关。记 $l=\operatorname{lcm}(a_1,a_2,\cdots,a_N)$，如果存在非负整数 $k$，使得对于每个 $\dfrac{l}{a_i}$，都能表示成 $2^k \times d$ 的形式（$d$ 为任意正奇数），那么 $X=\dfrac{l}{2^{k+1}}$（把原来的 $2$ 消去之外还要再除以 $2$ 才能出现 $0.5$）。

说明一下，如果不存在这样的 $k$，那么用 $X$ 除以 $a_i$ 时会出现结果为整数的情况（即 $X$ 分解后 $2$ 的个数不少于 $a_i$ 时），此时答案显然为 $0$。

时间复杂度 $O(n \log A)$，其中 $A$ 为值域上限。


```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

int n,m,a[1000001],b[101],flag,lc,ans,g,cnt,ti;

int gc( int x , int y )
{
	if( y == 0 ) return x;
	return gc( y , x % y );
}

signed main()
{
	cin >> n >> m;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i];
	lc = a[1];
	for( int i = 2 ; i <= n ; i ++ )
		lc = lc * a[i] / gc( lc , a[i] );
	for( int i = 1 ; i <= n ; i ++ )
	{
		a[i] = lc / a[i];
		cnt = 0;
		while( a[i] % 2 == 0 ) a[i] /= 2,cnt ++;		
		b[cnt] ++;
	}
	ti = 1;
	for( int i = 0 ; i <= 34 ; i ++ )
	{
		ti *= 2;
		if( b[i] == n )
		{
			lc = lc / ti;
			ans = m / lc;
			ans = ans / 2 + ans % 2;
			cout << ans;
			return 0;
		}
		
	}
	cout << 0;
	return 0;
}
```

---

## 作者：_7Mr (赞：0)

# 思路
首先我们可以先把数组去重。~~其实好像没有必要~~。

接下来我们考虑如何去求，我们直接去枚举显然会超时，那么我们考虑从半公倍数入手，半公倍数顾名思义，公倍数的一半，那么我们就可以将半公倍数算出来记为 $lcm$。因为 $X=a_i \times (p+0.5)$ 所以如果半公倍数除以每一个 $a_i$ 是一个偶数那么就不符合上述条件，所以答案就为 $0$。不然我们每次增大这个 $lcm$ 直到超过范围。最后输出答案就行了。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define INF INT_MAX
using namespace std;
const int maxn=1e5+5;
int n,m,ans;
int a[maxn],sum[maxn];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);//去重，其实没有必要
	int cnt=0;
	a[0]=-1;
	for(int i=1;i<=n;i++) {
		if(a[i]!=a[i-1]){
			sum[++cnt]=a[i];
			sum[cnt]/=2;
		}
	}
	int lcm=-1;
	for(int i=1;i<=cnt;i++){//半公倍数
		if(lcm==-1) lcm=sum[i];
		else lcm=lcm*sum[i]/__gcd(lcm,sum[i]);
	}
	for(int i=1; i<=cnt; i++){//特殊判断
		if(sum[i]/2!=0 && lcm/sum[i]%2==0){
			cout<<0<<endl;
			return 0;
		}
	}
	cout<<max(0ll,(m/lcm+(m/lcm%2))/2)<<endl;//输出答案
    return 0;
}


```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc150_d)

#### 思路
暴力把每个满足条件的数打印出来，可以发现一个规律，除第一个数外，其他每一个数都是前一个数加上一个固定的数，不难发现这就是这 $n$ 个数的最小公倍数。于是想到暴力找到第一个满足条件的数，在看 $m$ 减去这个数后有几个这 $n$ 个数的最小公倍数即可。

**code**

```
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[100010],b[100010],o,l,l1,ans,k,pp,c = 1;
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%lld",&a[i]);
	sort(a + 1,a + 1 + n);
	for(int i = 1;i <= n;++i) if(a[i] != a[i + 1]) b[++o] = a[i];//去重 
	sort(b + 1,b + 1 + o);
	l = b[o] / 2; l1 = b[o];//先使这个数是最大的数 * (p + 0.5)，优化 
	for(int i = 1;i <= o;++i)  c = lcm(c,b[i]);//求最小公倍数 
	for(int i = l;i <= m;i += l1)
	{
		k = 0;
		for(int j = 1;j <= o;++j)
		{
			if(i < b[j] / 2 || (i - b[j] / 2) % b[j] != 0) 
			{
				k = 1;
				break;
			}
		}
		if(!k)//找到了 
		{
			ans++;
			if(c < m) ans += (m - i) / c;//公式求剩下的 
			break;
		}
	}
	printf("%lld",ans);
	return 0;
}

```


---

