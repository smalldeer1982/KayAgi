# Good Numbers (hard version)

## 题目描述

简单难度与困难难度的唯一差别是n的取值范围

现在给出一个定义：Good Number（下文以好数代替），好数是指可以变成3的**不同**次幂的加和的数

例如：

$30$ 是好数 $30=3^3+3^1$

$1$ 是好数 $1=3^0$

$12$ 是好数 $12=3^2+3^1$

$2$ 不是好数，因为$2=3^0+3^0$，不符合不同次幂的条件

$19$ 不是好数，例如$19=3^2+3^2+3^0=3^2+3^1+3^1+3^1+3^0$，不符合不同次幂的条件

$20$不是好数，同理不符合不同次幂的条件，无法把$20$分为$3$的不同次幂的加和

现在给你一些正整数$n$，对于每个$n$请你给出一个最小的$m$满足：①$m$是好数 ②$n≤m$

## 样例 #1

### 输入

```
8
1
2
6
13
14
3620
10000
1000000000000000000
```

### 输出

```
1
3
9
13
27
6561
19683
1350851717672992089
```

# 题解

## 作者：柳易辰 (赞：6)

## Start
最优解，$\text{0ms\ 0B}$。

此算法不加快读快写不加优化就吊打所有其它算法，空间时间都是完美的。  
&nbsp;
## 思路
很明显，这题有一个性质，$\sum^{x-1}_{i=0}3^i<3^x(x\neq0)$。

假设 $m_i$ 为 $m$ 的三进制从右往左第 $i$ 位上的值。

我们考虑**从左往右**处理，若当前处理到第 $i$ 位，且前面的值为 $m$，若 $m+\sum^{j-1}_{i=0}3^j<n$，那么 $m_i$ 一定为 $1$ 才能使 $m\geqslant n$。并且，这种处理顺序可以保证 $m$ 最小。  
&nbsp;
## 代码
```
#include <stdio.h>
typedef long long ll;
int q; ll n, p[40] = {1}, s[40] = {1}; 
int main()
{
	scanf("%d", &q);
	for (int i(1); i < 39; ++i) s[i] = s[i - 1] + (p[i] = p[i - 1] * 3);
	while (q--)
   	{
		scanf("%lld", &n); ll m(0);
		for (int i(39); i; --i) if (m + s[i - 1] < n) m += p[i];
		printf("%lld\n", m < n ? n : m);
	}
    return 0;
} 
```
其中 $p_i=3^i,s_i=\sum^{i}_{j=0}3^i$，这两个数组均是为了减小常数。

由于，$3^{37}<10^{18}<3^{38}$，故循环从 $38$ 到 $1$。

当 $i=0$ 时，上面代码会越界，所以将最后一位加入特判。即输出时 $m < n(m=n- 1)$ 输出 $n$ 即可。  
&nbsp;
## End

时间复杂度：$\mathcal{O}(q\log_3n)$

空间复杂度：$\mathcal{O}(2 \log_3n)$

~~询问数这么少根本体现不出本算法的优越性！~~

---

## 作者：Priori_Incantatem (赞：6)

hard version 正解：状态压缩 + 二分查找

看到题目中“每个 $3$ 的幂最多只能使用一次”，可以很容易想到用状态压缩来解决

对于每一个好的数（Good Number）$x$，可以将它用一个二进制数 $y$ 表示。其中，如果对应的二进制数的第 $i$ 位为 $1$，代表构成 $x$ 时使用了 $3^i$

这样，我们就将散落在区间中的好数集中了起来，二分查找大于等于 $n$ 的最小好数即可

时间复杂度：$\operatorname{O}((\log_2n)^2)$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const long long Maxn=50;
const long long n=39;
long long a[Maxn],m;
inline long long read()
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
long long get(long long x) // 计算二进制数x对应的好数
{
	long long ret=0;
	for(long long i=0;i<=n;++i)
	if((x>>i) & 1)ret+=a[i];
	return ret;
}
int main()
{
//	freopen("in.txt","r",stdin);
	a[0]=1;
	for(long long i=1;i<=n;++i)
	a[i]=a[i-1]*3;
	long long T=read();
	while(T--)
	{
		m=read();
		long long l=1,r=(1ll<<n)-1;
		while(l<r) // 二分
		{
			long long mid=(l+r)>>1;
			long long tmp=get(mid);
			if(tmp>=m)r=mid;
			else l=mid+1;
		}
		printf("%lld\n",get(l));
	}
	return 0;
}
```

---

## 作者：梧桐灯 (赞：3)

看到${10}^{18}$肯定是按位处理。

首先有这样一个结论：将一个数转化为3进制过后，如果某一位上有2，那么这个数一定是坏数。

因为一个数不能减去同一个3的次幂，所以这个结论显然成立。

考虑贪心做法：

将这个数转化为3进制，然后从高位往地位找到第一个是2的位，将这一位后面全部置为0，并将此位+1，再模拟一下进位。

这样贪心得出来的结果显然是大于此数最小的“好数”。

代码：

```cpp
#pragma GCC optimize(8)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
 
typedef long long ll;
ll n;
int a[100], v;
 
int main () {
	a[0] = 1;
	register int i;
	int Q; scanf ("%d", &Q);
	while (Q--) {
		memset (a, 0, sizeof (a));
		cin >> n;
		v = 0;
		while (n) {
			a[++v] = n % 3;
			n /= 3;
		} //转化进制
		int mx = 0;
		for (i = 1; i < 40; ++i) {
			if (a[i] > 1) mx = i;
		}
		ll ans = 0;
		if (!mx) {
			for (i = v; i; --i) ans = ans * 3 + a[i];
			cout << ans << '\n';
		} //如果这个数本来就是好数，直接输出即可
		else {
			for (i = 1; i <= mx; ++i) a[i] = 0; //比第一个2低的位置为0
			++a[mx + 1];
			for (i = mx + 1; i < 40; ++i) {
				if (a[i] > 1) {
					++a[i + 1];
					a[i] -= 2;
				} //模拟进位
			}
			for (i = 40; !a[i]; --i);
			while (i) ans = ans * 3 + a[i--];
			cout << ans << '\n';
		}
	}
	return 0;
}
```

---

## 作者：34ytw8ew7ft (赞：2)

这道题的主要的恐惧点还是我们一看到$n \le 10^{18}$就慌了，这个时候肯定不能按照常规处理思路了。怎么办？有经验的同学马上想到这肯定需要个$\log$级别的做法，那怎么做呢？

## 解法1

我们仔细思考条件，把 $m$ 表示为3的不同自然数次幂之和……等等，不就是把这个数搞成三进制吗！如果要满足不同的自然数次幂之和……不就是最后的3进制中不出现2吗！

经过上面的分析这个题就马上变得人畜无害了起来。怎么把2去掉？进位啊~怎么快速把2去掉还能使这个数尽可能的小？从左往右找到第一个2把它后面全变成0再进位啊！为什么要把后面全变成0？肯定是因为变成0小啊……如果进完位又有新的2产生怎么搞？如法炮制请。

## 解法2

感谢本校巨佬提供这个爆踩蒟蒻的思路！


设最高次项指数为$x$，那很显然可以得到：

$$3^x > \sum_{i=0}^{x-1} 3^i$$

于是我们可以考虑从$3^0$一直计和直到总和$\ge m$的时候停止，确定最高次项指数为$x$，再从高次项向低次项尝试删项，最后构造出的好数一定是尽可能小的。

## Code

下面是解法1的具体实现：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline ll read() 
{
    register ll x = 0 , ch = getchar(); 
    while( !isdigit( ch ) ) ch = getchar(); 
    while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();     
    return x; 
}
ll quick_power(ll a,ll b,ll modn)
{
    ll ans=1;
    while(b)
    {
        if(b%2)
            ans=ans*a%modn;
        a=a*a%modn;
        b=(b>>1);
    }
}
ll turtle_muti(ll ain,ll bin,ll modn)
{
    ll res=0;
    for(;bin;bin>>=1) 
    {
        if(bin&1)
            res=(res+ain)%modn;
        ain=(ain<<1)%modn;
    }
    return res;
}
/*------------------Coding Area------------------*/
const ll maxn=2e5+51;
ll num[maxn];
ll n,nlen,ans;

signed main()
{
    ll q=read();
    while(q--)
    {
        n=read();
        memset(num,0,sizeof(num));
        nlen=0,ans=0;
        while(n)
            num[++nlen]=n%3,n/=3;
        for(int i=nlen;i;--i)
            if(num[i]==2)
            {
                ll ptr=i+1;
                num[i]=0;
                for(int j=i-1;j;--j)
                    num[j]=0;
                while(num[ptr]==1)
                    num[ptr++]=0;
                num[ptr]=1,nlen=max(nlen,ptr);
            }
        for(int i=nlen;i;--i)
            ans=ans*3+num[i];
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Karry5307 (赞：1)

### 题意

有$q$组询问，每组询问给定$n$，要你求出一个最小的$m$使得$m\geq n$且$m$的三进制表示下没有$2$。

$\texttt{Data Range:}1\leq q\leq 10^3,1\leq n\leq 10^{18}$

### 题解

贪心好题。

mmp我做到这里然后就被拉去睡觉了，然后早上发现$\texttt{D1,D2,E}$很可做啊qwq，我的$\color{blue}\texttt{Expert}$啊！（其实是用小号打的）

首先第一步我已经说了，把它表示成三进制。

假设把$n$加上$k$能得到$p$。

如果$k$不足以使$n$的三进制表示中$2$所处的位置中的最高位发生进位，那么$p$是不符合要求的，因为那个$2$还是在那里。

于是我们可以模拟进位，把这一位以及低于他的位全部改成$0$，将比这这一位高且相邻的位加以。

由于这一位是$2$所处位置的最高位，所以比它还高的位只可能是$0$和$1$，加上$1$后是$1$和$2$。

万一加上$1$后又出现一个新的$2$的为怎么办呢？没关系，我们以这个数作为$n$，再来一遍，直到没有位置有$2$。

这里用一个例子来解释一下，比如$n=(1001111121021)_3$，首先找出$2$所处的位置中的最高位，然后模拟进位，得到$(1001111200000)_3$，发现还有一个位置$2$，就重新来，得到$(1001112000000)_3$，如此往复，直到没有位置为$2$。最终我们得到答案就是$(1010000000000)_3$。

这个操作其实是将$2$所处的位置中的最高位前面的连续的$1$全部改为$0$，而这一段$1$前面的$0$改为$1$，然后就完结撒花了qwq

时间复杂度$O(q\log n)$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51;
ll test,tot,kk,ptr,res;
ll num[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline void solve()
{
	kk=read();
	memset(num,0,sizeof(num)),tot=0,res=0;
	while(kk)
	{
		num[++tot]=kk%3,kk/=3;
	}
	for(register int i=tot;i;i--)
	{
		if(num[i]==2)
		{
			num[i]=0,ptr=i+1;
			for(register int j=i-1;j;j--)
			{
				num[j]=0;
			}
			while(num[ptr]==1)
			{
				num[ptr++]=0;
			}
			num[ptr]=1,tot=max(tot,ptr);
		}	
	} 
	for(register int i=tot;i;i--)
	{
		res=(res*3)+num[i];
	}
	printf("%lld\n",res);
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		solve();
	}
}
```

---

## 作者：big_news (赞：0)

简化题意：我们现在要在数列 $[3^0,3^1,3^2,...,3^k](3^k>n)$ 中选出一些数，使得它们的和 $⩾n$ ，并使得这个和最小。

考虑爆搜每一个位置上的数 选/不选。有 $2^{40}$ 近似于 $10^{18}$，因此直接这样做大概是 $O(q·2^{40})$ 的，肯定不行。

考虑怎么跑得更快。实际上上述枚举过程可以通过枚举二进制状态来实现，即用一个数字二进制位上的 $0/1$ 来表示数列某一项选不选。

假设我们当前二进制枚举的状态码为 $S$ ，那么实际上该状态码所对应的数值是单调的；换句话说，随着 $S$ 变大，其表示的那个数字也变大。

简单的 proof ，~~请理性偷税~~。
考虑把二进制数 $0100$ 变成 $0101$ （前者表示 $3^2$ ，后者表示 $3^2+3^0$） ，即在原来状态码的基础上加一位使其变大，此时其表示的数字一定变大，因为又多了新的一项。考虑把二进制数 $0100$ 变成 $1000$ （前者表示 $3^2$ ，后者表示 $3^3$），即右移原来状态码的某一位使其变大，此时其表示的数字也一定变大，因为有一项的次数$+1$。

那么也就是说现在枚举的数值具有单调性，那么为什么不二分呢？只需要二分查找出一个 $⩾n$ 的最小位置就好了，总复杂度 $O(qk)$，其中 $k$ 为常数，它大概是 $\log_2 2^{40}=40$。

代码:

Easy Version
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
int read(){
    int s=0,ne=1; char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne=-1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne; 
}
int q,n;
int Pow3(int x){
    int rec = 1,base = 3;
    while(x) {if(x & 1) rec *= base; base *= base; x >>= 1;}
    return rec;
}
int gen(int u){
    int g = 0;
    for(int i=0;i<14;i++) if(u & (1<<i)) g += Pow3(i);
    return g;
}
int main()
{
    q = read();
    while(q--){
        int n = read();
        for(int S = 0; S < (1<<14); S++)
            if(gen(S) >= n) {printf("%d\n",gen(S));break;}
    }
    return 0;
}
```

Hard Version
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

#define LL long long

LL read(){
    LL s=0,ne=1; char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne=-1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne; 
}

int q; LL n;

LL Pow3(int a){
    LL rec = 1,base = 3; 
    while(a) {if(a & 1) rec *= base; base *= base,a >>= 1;}
    return rec;
}
LL gen(LL u){
    LL g = 0;
    for(int i=0;i<40;i++) if(u & (1ll << i)) g += Pow3(i);
    return g;
}

int main()
{
    q = read();
    while(q--){
        n = read();
        LL l = 0,r = (1ll << 40);
        while(l < r){
            LL m = (l + r) >> 1;
            if(gen(m) >= n) r = m;
            else l = m + 1;
        }
        printf("%lld\n",gen((l + r) >> 1));
    }
    return 0;
}
```

---

## 作者：B_Qu1e7 (赞：0)

提供二分答案做法 ~~（掩盖考场上想复杂的实际情况）~~

预处理 ~~（指打表）~~ 出$3^i$，包括$>1e18$的第一个数$3^{38}$，在$1e18$内最多只有$39$个$3^i$。

开一个$long\ long$表示$N$的压缩状态（即二进制表示3的幂），末位代表$3^0$，倒数第二位代表$3^1$，……一共需要$39$位。

二分答案，$l=1,r=2^{40}-1$，每次取$mid$转换成实际代表的数字与$N$比较，更新左右，最后输出$l$即可。

```cpp
#include<cctype>
#include<cstdio>
#define R register
#define ll long long
int Q;
ll N,l,r,pow3[]={1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969,14348907,43046721,129140163,387420489,1162261467,3486784401,10460353203,31381059609,94143178827,282429536481,847288609443,2541865828329,7625597484987,22876792454961,68630377364883,205891132094649,617673396283947,1853020188851841,5559060566555523,16677181699666569,50031545098999707,150094635296999121,450283905890997363,1350851717672992089};
//3的幂
inline ll turnto(ll type)//状态转数字
{
	R int base=0;
	R ll mean=0;
	while(type)
	{
		if(type&1)
		{
			mean+=pow3[base];
		}
		type>>=1;
		++base;
	}
	return mean;
}
template<class T>inline void read(T &m)
{
	m=0;
	char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
	read(Q);
	while(Q--)
	{
		read(N);
		l=1,r=(1ll<<40)-1;//左右范围
		while(l<r)//二分答案
		{
			ll mid=((l+r)>>1);
			if(turnto(mid)<N)
			{
				l=mid+1;
			}
			else
			{
				r=mid;
			}
		}
		printf("%lld\n",turnto(l));
		//输出状态l所代表的数字即可
	}
}
```
主代码简洁，就是打$3^i$要花点时间

---

## 作者：CLer (赞：0)

## 题意
显然是要求出大于等于输入的最小三进制数
## 解法
先判断自身是否是三进制数显示只含有1或者0的数字，如果是的话直接输出就可以了，如果不是从当前位数开始,如果当前位的数字为2，就把这个位上的数字变成0，给高位进位，并且记录最高位的数字，把后面的数字清空成0，毕竟是进位了，后面再小也肯定比原本的数字大
```c++
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;
typedef long long ll;
ll digitx[100];
ll x, y;
int cnt = 0;

void trans(ll num) {//转化3进制 
	cnt = 0;
	while (num) {
		digitx[cnt++] = num % 3;
		num /= 3;
	}
}

void add(int st) {
	bool flag = 0;
	int jin = 0, c = 0;
	//jin 进位 c 最高位 
	for (int i = st; i < cnt; i++) {
		digitx[i] += jin;
		jin = 0;
		if (digitx[i] > 1) {
			digitx[i] = 0;
			jin = 1;
			c = i;
		}
	}
	
	for (int i = 0; i < c; i++) digitx[i] = 0;
	//把后面的数字清成0，尽可能小 
	if (jin) digitx[cnt++] = 1;
}

ll getans() {
	ll res = 0, bas = 1;
	for (int i = 0; i < cnt; i++, bas = bas * 3) {
		if (digitx[i])
			res = res + bas;
	}
	return res;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%I64d", &x);
		trans(x);
		bool adf = false;
		int st = -1;
		for (int i = 0; i < cnt; i++) 
			if (digitx[i] > 1) {//如果三进制数有 2  
				adf = true;
				st = i;
				break;
			}
		if (adf == true) {//就要把2都变成0，进位 
			add(st);
		}
		ll ans = getans();		
		printf("%I64d\n", ans);
	}
    return 0;
}
```


---

