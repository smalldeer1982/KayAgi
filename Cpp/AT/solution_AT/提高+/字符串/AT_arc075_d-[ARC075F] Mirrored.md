# [ARC075F] Mirrored

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc075/tasks/arc075_d

正の整数 $ n $ に対し、$ n $ の十進表記（先頭に $ 0 $ を付けない）を左右に反転させて得られる整数を $ rev(n) $ と表記します。例えば、$ rev(123)\ =\ 321 $, $ rev(4000)\ =\ 4 $ です。

正の整数 $ D $ が与えられます。$ rev(N)\ =\ N\ +\ D $ であるような正の整数 $ N $ はいくつ存在するでしょうか？

## 说明/提示

### 制約

- $ D $ は整数である。
- $ 1\ <\ =\ D\ <\ 10^9 $

### Sample Explanation 1

$ rev(N)\ =\ N\ +\ 63 $ であるような正の整数 $ N $ は、$ N\ =\ 18,\ 29 $ の $ 2 $ 個存在します。

### Sample Explanation 2

$ rev(N)\ =\ N\ +\ 75 $ であるような正の整数 $ N $ は存在しません。

## 样例 #1

### 输入

```
63```

### 输出

```
2```

## 样例 #2

### 输入

```
75```

### 输出

```
0```

## 样例 #3

### 输入

```
864197532```

### 输出

```
1920```

# 题解

## 作者：ez_lcw (赞：18)

提供一种本校学长的更好的思路，可以应用到本题的加强版。

题意：给定正整数 $D$，求满足 $rev(N)=N+D$ 的正整数 $N$ 的个数。

设 $|x|$ 表示 $x$ 的位数。

我们先枚举 $N$ 的位数 $|N|=len$，因为这样我们就能确定 $N$ 翻转后的形态。

首先显然 $len$ 不能小于 $D$ 的位数。

在手摸竖式的过程中容易发现 $len$ 也不能大于 $D$ 的位数的两倍，当然也可以通过位值原理严谨证明。

同时要特判一下 $|D|=1$ 时 $len$ 不能为 $1$ 的情况，于是有枚举范围：$[\max(2,|D|),2|D|]$。

假设当前枚举 $|N|=len$。画出竖式，为了体现翻转带来的性质，我们考虑如图对所有位分成左半部分和右半部分，并如图编号：

![](https://cdn.luogu.com.cn/upload/image_hosting/kvhtgvgo.png)

从外往内确定 $N$ 的每一位，我们假设外 $i$ 位都已经确定好了，然后枚举枚举 $N$ 右半部分的第 $i+1$ 位为 $x$，然后判断左右第 $i+1$ 位是否合法。发现判断是否合法只跟右半部分第 $i+1$ 位是否有从它右边的第 $i$ 位收到进位、左半部分第 $i+1$ 位是否有给它左边的第 $i$ 位进位有关：

![](https://cdn.luogu.com.cn/upload/image_hosting/m74xjp1z.png)

所以我们设 $f(i,j,k)$ 表示已经考虑完 $N$ 左右两部分的前 $i$ 位（外 $i$ 位），左半部分第 $i$ 位是否有从第 $i+1$ 位收到进位的状态为 $j=0/1$，右半部分第 $i$ 位是否有给第 $i+1$ 位进位的状态为 $k=0/1$ 的填数方案数。

我们考虑从 $f(i,j,k)$ 向 $f(i+1,*,*)$ 转移：

如图，我们枚举 $N$ 右半部分的第 $i+1$ 位为 $x$，然后结合 $D$ 和 $k$ 计算出 $rev(N)$ 右半部分的第 $i+1$ 位为 $y$，再把 $x,y$ 代入左半部分第 $i+1$ 位并结合 $D$ 和 $j$ 检验是否满足条件，若合法，同时计算出这种情况下新的 $j'$ 和 $k'$，然后由 $f(i,j,k)$ 向 $f(i+1,j',k')$ 转移。

同时注意当 $i=1$ 时 $y$ 不能是 $0$，这样会导致 $N$ 有前导 $0$。

如何统计答案呢？

- 若 $len$ 为偶数，记 $m=\dfrac{len}{2}$，则 $|N|=len$ 时的答案即为 $f(m,0,0)+f(m,1,1)$；

- 若 $len$ 为奇数，记 $m=\left\lfloor\dfrac{len}{2}\right\rfloor$，那么我们先计算出 $f(m,*,*)$，此时还剩下中间那一位没有填，于是我们枚举 $j,k$，以及中间那一位的 $x$，判断是否满足进位条件（即合法），若满足则把 $f(m,j,k)$ 统计进答案。

也就是相当于把本来独立的左右两半部分拼凑在一起，有点像折半 DP。

总时间复杂度 $O(|D|^2)$，还会有枚举 $j,k,x$ 带来的常数，但总体上是跑不满的。校内 OJ 实测 $D\leq 10^{5000}$ 是秒出的。

~~然而本题只有 $\sout{D\leq 10^9}$。~~

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 10010

using namespace std;

namespace modular
{
	const int mod=1000000007;
	inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
	inline void Add(int &x,int y){x=(x+y>=mod?x+y-mod:x+y);}
}using namespace modular;

char D[N];
int lenD,d[N];
int ans,f[N][2][2];

void solve(int len)
{
	memset(f,0,sizeof(f));
	int m=(len>>1);
	f[0][0][0]=1;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<2;j++)
		{
			for(int k=0;k<2;k++)
			{
				if(!f[i][j][k]) continue;
				for(int x=0;x<10;x++)
				{
					int y=x+d[i+1]+k;
					bool kk=0;
					if(y>=10) kk=1,y-=10;
					if(!i&&!y) continue;
					if(y+d[len-i]==j*10+x) Add(f[i+1][0][kk],f[i][j][k]);
					if(y+d[len-i]+1==j*10+x) Add(f[i+1][1][kk],f[i][j][k]);
				}
			}
		}
	}
	if(len&1)
	{
		for(int j=0;j<2;j++)
		{
			for(int k=0;k<2;k++)
			{
				if(!f[m][j][k]) continue;
				for(int x=0;x<10;x++)
				{
					if(x+d[m+1]+k==x+j*10)
						Add(ans,f[m][j][k]);
				}
			}
		}
	}
	else Add(ans,add(f[m][0][0],f[m][1][1]));
}

int main()
{
	scanf("%s",D+1);
	lenD=strlen(D+1);
	for(int i=1;i<=lenD;i++)
		d[i]=(D[lenD-i+1]-'0');
	for(int i=max(2,lenD);i<=(lenD<<1);i++)
		solve(i);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：KaisuoShutong (赞：7)

AT2582 [ARC075D] Mirrored 题解。

首先枚举 $N$ 的位数 $L$。

以四位数为例。设 $N=\overline{abcd}$。

题給式子移项。

$$
999(d-a)+90(c-b)=D
$$

观察前面的系数。（以下是八位数的例子）

$$
\begin{aligned}
&9000\\
9&9900\\
99&9990\\
999&9999
\end{aligned}
$$

又根据 $0\le a,b,...\le 9$。

$$
-9\le d-a,c-b,...\le 9
$$
$$
9\times 99900+9\times 9000<1\times 999990
$$

是故各项系数之间是互不干扰的。（i.e. 最大的低位的小于最小的高位）

那么从高到低枚举，并给 $d-a,c-b,...$ 分配系数。

设当前系数为 $m$。满足 $d-a=\omega$ 的 $(a,d)$ 可以简单地预处理，其中 $\omega$ 为选定值。

此时，必须保证分完后剩余的 $D$ 满足 $-m<D<m$。

容易发现这样的系数分配方式至多两个。单次时间复杂度即为 $O(2^L)$。

特殊点：长度为偶数和长度为奇数略有不同；$a\neq0$，需特殊处理。

```cpp
int dfs(int x,int nw) {
	if(x==L/2) return !nw?1:0;int c=pw[L-1-x]-pw[x],ty=(nw%c+c)%c,
	w=ABS(nw-ty)/c,
	r=-9<=w&&w<=9?(!x?f2:f)[w]*dfs(x+1,ty):0;if(!ty) return r;
	ty-=c,w=ABS(nw-ty)/c,
	r=(r+(-9<=w&&w<=9?(!x?f2:f)[w]*dfs(x+1,ty):0));return r;
}
char arre;void Main() {
	cerr<<fixed<<setprecision(1)<<(((&arre)-(&arrs))/1024./1024.)<<'\n';
	D=read(),L=ceil(1.*log(D)/log(10))+9;
	pw[0]=1;for(int i=1;i<=L;i++) pw[i]=pw[i-1]*10;
	for(int i=0;i<10;i++) for(int j=0;j<10;j++) ++f[i-j],j?++f2[i-j]:0;
	int r=0;
	while(L) {
		r=(r+dfs(0,D)*(L&1?10:1)),--L;
	}cout<<r<<'\n';
}}signed main() {tomorinao::Main();return 0;}
```

---

## 作者：louhao088 (赞：6)

提供一种又好想又好写的做法。


------------


首先我们发现对应位置产生的贡献必然为 $z({10}^x-{10}^y)$ 。

这个 $x$  与 $y$ 和数的位数有关。所以我们可以枚举每种位数的数的答案。


------------

然后问题就变为对于一种位数的数，如何得到其答案数 。

我们很容易发现对于这些数，在每一位其产生的贡献必然只有两种。我们可以深搜解决。

那么为什么只有两种呢？

我们令搜到当前这一位之前贡献和与 $d$ 的差值为 $u$ 。那么我们这一次修改的贡献只有可能是第 1 个比 $u$  小的 $z({10}^x-{10}^y)$ ，与第 1 个比 $u$ 大的  $z({10}^x-{10}^y)$。因为我们发现这个贡献其实与倍增有所类似，高位上如果没取满，那么低位上全部取最大贡献也做不到。


而算答案只要每一位分开算，最后乘起来即可。

------------

能构成答案的数不会超过 $10^{18}$ ，因为超过这个数的话最小的贡献也会超过 $10^9$。 而对于每种位数我们只需枚举一半即可。

时间复杂度 $O(\log _{10}{n} 2^{\log_{10}n}) $  。


------------

代码如下（应该是最短解了吧）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,d,ans=0,pw[25],t,u;
void dfs(int x,int y,int res){
    if(x==t+1){if(!y)ans+=res;return;}int o=(x==1);
    if(y==0){dfs(x+1,y,res*(10-o));return ;}
    int p=u-x+1,z=9-o,id=0,g=pw[p-1]-pw[x-1];
    for(int k=z;k>=0;k--)if(y>=g*k){id=k;break;}
    dfs(x+1,y-g*id,res*(z-id+1));
    if(id!=z)dfs(x+1,g*(id+1)-y,res*(z-id));
}
signed main(){
    cin>>d;pw[0]=1;
    for(int i=1;i<=17;i++)pw[i]=pw[i-1]*10;
    for(int i=1;i<=18;i++)t=(i+1)/2,u=i,dfs(1,d,1);
	cout<<ans;return 0;
}

```



---

## 作者：Krimson (赞：5)

一种只用到了$dfs$的简单做法,唯一难的地方在于推式子吧~~也不算难~~ 


------------

按照套路,肯定是要把式子换成一边只有n,而另一边只有D的形式  
于是可以得到  
$rev(N)-N=D$  
考虑转换右边,可以得到式子  
$$
\begin{array}{lcl}

\because

\left\{\begin{aligned}

N&=a_0 \times 10^0+a_1 \times 10^1+\dots+a_x \times 10^x \\

rev(N)&=a_0 \times 10^x+a_1 \times 10^{x-1}+\dots+a_x \times 10^0 \\

\end{aligned}\right.\\

\\

\begin{aligned}

\therefore

rev(N)-N&=(10^x-10^0) \times a_0+\dots+(10^0-10^x) \times a_x \\

&=\left\{\begin{aligned}

9 \times \left[\ \begin{matrix}x\\\overbrace{11\dots1}\end{matrix}\times 10^0\times (a_0-a_x)+\dots+1\times 10^{\left\lfloor\frac{x}{2}\right\rfloor}\times(a_{\left\lfloor\frac{x}{2}\right\rfloor}-a_{\left\lceil\frac{x}{2}\right\rceil})\ \right], & \text {if $x $ is even} \\

9 \times \left[\ \begin{matrix}x\\\overbrace{11\dots1}\end{matrix}\times 10^0\times (a_0-a_x)+\dots+11\times 10^{\frac{x}{2}-1}\times(a_{\frac{x}{2}-1}-a_{\frac{x}{2}+1})\ \right], & \text {if $x $ is odd} \\

\end{aligned}\right.\\

\end{aligned}

\end{array}
$$
也就是说首先$D$要是9的倍数  
其次可以发现对于$10^0$项有贡献的只有$(a_0-a_n)$,  
去除掉$(a_0-a_n)$的贡献之后,对于第$10^1$有贡献的就只有$(a_1-a_{n-1})$  
.  
.  
.  
然后每一对$(a_i-a_{n-i})$，他们都是相互独立的,所以方案数是每一对项的可能方案的积  
接下来只需要确定$(a_i-a_{n-i})$就能确定ans了  


------------  
可以发现这是一个$n$元1次不等式  
如果D=729,先把它除以9,可以得到81  
而对81在n=3的时候可以得到方程  
$$
111(a_0-a_3)+10(a_1-a_2)=81
$$  
然后根据上面推到的性质可以得到  
$$
(a_0-a_3)=1
$$  
$$
10(a_0-a_3)+10(a_1-a_2)=80  
$$
$$
100(a_0-a_3)=0
$$  
### ???  
似乎不对劲,显然存在$(a_0-a_3)=1,(a_1-a_2)=-3$这一组解  
于是发现之前枚举的时候都是默认$(a_i-a_{n-i})$大于0的,实际上对于每一个位置,都存在两个可能的取值,即$x$和$10-x$  
然后就可以发现这个过程用dfs去暴力枚举取正数还是取负数可以很轻松的做到  
```cpp
ll check(int l, int now)
{
    if (now > l / 2)
    {
        for (ri i = (l + 1) / 2; i <= max(l, len); ++i)
        {
            if (res[i] < 0 && i != l)
            {
                res[i + 1]--;
                res[i] += 10;
            }
            if (res[i] > 9 && i != l)
            {
                res[i + 1]++;
                res[i] -= 10;
            }
            if (res[i])
                return 0;
        }
        ll use = 1;
        for (ri i = 0; i <= l / 2; ++i)
            use *= to(val[i], i);
        return use;
    }
    ll use = 0;
    val[now] = res[now];
    for (ri j = now; j < l - now; ++j)
    {
        res[j] -= val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    use += check(l, now + 1);
    for (ri j = now; j < l - now; ++j)
    {
        res[j] += val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    val[now] = res[now] - 10;
    for (ri j = now; j < l - now; ++j)
    {
        res[j] -= val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    use += check(l, now + 1);
    for (ri j = now; j < l - now; ++j)
    {
        res[j] += val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    return use;
}
```
其中的$to(i,j)$表示$(a_j-a_{n-j})$的值为$i$时候有多少种方案  
```cpp
ll to(int x, int id)
{
    if (id == 0)//记得前导0！
    {
        if (x >= 0)
            return 9 - x;
        else
            return 10 + x;
    }
    else
    {
        if (x >= 0)
            return 10 - x;
        else
            return 10 + x;
    }
}
```
最后只要取枚举$n$,不断地去解方程就好了  
至于上下界的问题,我是暴力搜到长度为25位,实际上可以少搜很多,但具体要搜到第几位我也不会证明~~太弱了~~  


------------
```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read()
{
    bool f = true;
    ll x = 0;
    register char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = false;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    if (f)
        return x;
    return ~(--x);
}
il void write(const ll &x)
{
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
il void print(const ll &x)
{
    x < 0 ? putchar('-'), write(~(x - 1)) : write(x);
    putchar('\n');
}
il int max(const int &a, const int &b) { return a > b ? a : b; }
il int min(const int &a, const int &b) { return a < b ? a : b; }
ll D;
const int MAXN = 50;
ll k[MAXN], fac[MAXN];
ll val[MAXN], res[MAXN], rem[MAXN];
int len;
ll to(int x, int id)
{
    if (id == 0)//记得前导0！
    {
        if (x >= 0)
            return 9 - x;
        else
            return 10 + x;
    }
    else
    {
        if (x >= 0)
            return 10 - x;
        else
            return 10 + x;
    }
}
/*
res[i]表示当前在方程组中第10^i这一项为多少  
val[i]表示(a[i]-a[n-i])的取值
*/
ll check(int l, int now)
{
    if (now > l / 2)
    {
        for (ri i = (l + 1) / 2; i <= max(l, len); ++i)
        {
            if (res[i] < 0 && i != l)
            {
                res[i + 1]--;
                res[i] += 10;
            }
            if (res[i] > 9 && i != l)
            {
                res[i + 1]++;
                res[i] -= 10;
            }
            if (res[i])
                return 0;
        }
        ll use = 1;
        for (ri i = 0; i <= l / 2; ++i)
            use *= to(val[i], i);
        return use;
    }
    ll use = 0;
    val[now] = res[now];
    for (ri j = now; j < l - now; ++j)
    {
        res[j] -= val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    use += check(l, now + 1);
    for (ri j = now; j < l - now; ++j)
    {
        res[j] += val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    val[now] = res[now] - 10;
    for (ri j = now; j < l - now; ++j)
    {
        res[j] -= val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    use += check(l, now + 1);
    for (ri j = now; j < l - now; ++j)
    {
        res[j] += val[now];
        if (res[j] < 0 && j != l)
        {
            res[j] += 10;
            res[j + 1]--;
        }
        else if (res[j] > 9 && j != l)
        {
            res[j] -= 10;
            res[j + 1]++;
        }
    }
    return use;
}
int main()
{
    D = read();
    if (D % 9)
    {
        print(0);
        return 0;
    }
    ll X = D / 9;
    while (X)
    {
        rem[len] = X % 10;
        X /= 10;
        if (X)
            ++len;
    }
    ll ans = 0;
    for (ri i = max(1, len - 1); i <= 24; ++i)
    {
        for (ri j = 0; j <= len; ++j)
        {
            res[j] = rem[j];
        }
        ans += check(i, 0);
    }
    print(ans);
    return 0;
}
```


---

## 作者：Ryo_Yamada (赞：3)

> 题意：给定 $D$，求满足 $\mathrm{rev}(N)=N+D$ 的 $N$ 的个数，$\mathrm{rev}(N)$ 表示十进制下将 $N$ 按位翻转并去掉前导 $0$ 后的数。

为了更清楚地表示，我们设 $|N|$ 为 $N$ 的位数。

由于是将 $N$ 翻转，我们直接将翻转前后的位置匹配算贡献。可以直接枚举 $|N|$，枚举每对的 高位减低位 的差，就能算出 $\mathrm{rev}(N) - N$ 的值，如果 $=D$ 将方案数计入答案即可。注意一些限制条件即可。这样的复杂度是 $19^{\lfloor \frac{|N|+1}{2} \rfloor}$。而这样就算我们吸氧，$|N|$ 也只能枚举到 $14$，会 WA 4 个点。而 $|N|$ 却是理论上 $\le 18$ 的，可以自己证一下。

由于我们写的是搜索，自然可以想想怎么剪枝。我们发现每对的贡献都形如 $99 \ldots 90 \ldots 00 \times c$，其中 $c$ 为高位减低位的差。更加具体地，如果当前高位距离最高位有 $k$ 个数位，贡献为 $(10^{|N|-2\times k} - 1) \times 10^k$。如果自己手推几个长度就能发现，由低到高贡献的跨度比每次 $\times 10$ 还要大。这也就有一个问题：我们枚举匹配出的对时，按贡献从高到低枚举，偏差很难由低位补足。也就是说，满足条件的差的序列很少。这时可行性剪枝效果非常出色。我们只需要在上述做法加一个可行性剪枝即可无压力通过。

$\text{Code}$：

```cpp
int d;
ll pw[20];
ll to[20][15];
ll suf[20][15];

ll dfs(int all, int nw, ll sum, ll res) {
	if(sum + suf[all][nw] < d || sum - suf[all][nw] > d) return 0;
	if(nw == (all >> 1)) {
		if(abs(d - sum) % (pw[all - nw] - pw[nw - 1]) || abs(d - sum) / (pw[all - nw] - pw[nw - 1]) > 9) return 0;
		int nd = (d - sum) / (pw[all - nw] - pw[nw - 1]);
		return res * (10 - abs(nd) - (nw == 1));
	}
	ll ret = 0;
	rep(i, -9, 9) {
		if(nw == 1 && i == -9) continue;
		ll nwp = (pw[all - nw] - pw[nw - 1]) * i;
		ret += dfs(all, nw + 1, sum + nwp, res * (10 - abs(i) - (nw == 1)));
	}
	return ret;
}

int main() {
	pw[0] = 1;
	rep(i, 1, 18) pw[i] = pw[i - 1] * 10;
	rep(i, 2, 18) rep(j, 1, (i >> 1)) to[i][j] = pw[i - j] - pw[j - 1];
	rep(i, 2, 18) per(j, (i >> 1), 1) suf[i][j] = suf[i][j + 1] + to[i][j] * 9;
	qread(d);
	ll ans = 0;
	rep(i, 2, 18) {
		if(i & 1) ans += 10 * dfs(i, 1, 0, 1);
		else ans += dfs(i, 1, 0, 1);
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：GFyyx (赞：3)

## 解题思路
DFS 剪枝。

## 推式子

设 $k$ 位数 $N=\overline{a_1 a_2 \dots a_k}$，则 $N=\sum_{i=0}^{k}{10^ia_i}$。

由题意得 $D=rev(N)-N$。

$D=\sum_{i=0}^{k}{(10^{k-i}-10^i)(a_{k-i}-a_i)}$。

设 $b_i=a_{k-i}-a_i$ 有 $b_i \in [-9,9]|b_i \in Z$。

故 $D=\sum_{i=0}^{\frac{k-1}{2}}{(10^{k-i}-10^i)b_i}$。

因为 $10^{k-i}-10^i > 9 \sum_{j=i-1}^{\frac{k-1}{2}}{10^{k-j}-10^j}$。

有 $-(10^{k-i}-10^i) < \dfrac{D}{b_i} < 10^{k-i}-10^i$。

枚举 $N$ 的位数 $k$ 和 $b_i$，将每一位 $b_i$ 的方案数相乘就是长度为 $k$ 时的方案数。

总时间复杂度为 $\Theta(k \times 2^k)$。

---

