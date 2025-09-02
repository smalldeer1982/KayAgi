# [PA 2022] Wielki Zderzacz Termionów

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 1 [Wielki Zderzacz Termionów](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/wzt/)**

Albert Bynstein 教授发现了一种新的基本粒子：热离子。如果他的实验成功，就可以在他的帮助下修建一个发电站，这样就可以解决 Byteland 的能源问题了。

这些粒子有三种类型，用红色，绿色和蓝色表示。这个名称与粒子实际的颜色或者光的波长无关，只是 Bynstein 教授用这些颜色的马克笔标记这些粒子。

红色和绿色的热离子可以发生反应，但只与另一个相同颜色的粒子发生反应。当两个红色热离子碰撞时，产生一个绿色热离子，并释放 $1$ 字节焦耳的能量。如果两个绿色热离子发生碰撞，就会产生一个红色热离子，同时释放 $1$ 字节焦耳的能量。

蓝色热离子不与其他热离子反应，但是它们是不稳定的。产生蓝热离子 $72$ 小时后，它会随机变成红热离子或绿热离子中的一个，变成任何离子都不会释放能量。

教授正在准备一个受控的实验反应。为此，他在实验室里准备了排成一排的 $n$ 个热离子。几天后，他打算把这些离子带到目前正在首都地下建造的大型热离子对撞机。到那时，所有的蓝色热离子都将变成红色或绿色热离子。

在对撞实验中，教授想进行一连串的反应，以产生 $n-1$ 字节焦耳的能量，并最后只留下一个热离子。每次反应可以选择相邻的两个热离子。所产生的热离子与左边和右边的热离子相邻，并能与它们发生进一步的反应。

问题是，当所有的蓝色热离子都发生变化时，有多大概率存在一个可行的反应序列。

你的任务是计算蓝色热离子有多少种变化方式（对 $10^9+7$ 取模）能使完整的反应序列进行下去。

此外，教授还会在他的实验室里对热离子的位置进行改变，每次都把一个热离子换成另一个（也许不会改变其类型）。在每一次这样的变化之后，也要计算出结果。

## 说明/提示

对于 $100\%$ 的数据，满足：

$1\le n\le 2 \times 10 ^ 5, 0\le q\le 10 ^ 5, 1\le k_i\le n$。

## 样例 #1

### 输入

```
5 3
NNCCZ
3 N
2 Z
1 Z
```

### 输出

```
3
5
3
1
```

# 题解

## 作者：songhongyi (赞：3)

这个性质让我回想起了某个 CF 的题了。

把红色离子当作 $1$，绿色离子当作 $2$，则每次合并后模 $3$ 不变。

因而如此转化后和模 $3$ 为 $1$ 或 $2$  是一个必要条件。但显然不是充分的。

但是经过手模后，发现貌似除了 $1212121$ 和 $2121212$ 这两种外，都可以构造出解来。

稍加思索，发现貌似确实是这样的。我们只需要证明肯定可以避开这种情况即可。

举例而言，生成 $21212$ 的前驱状态应该是 $211112$，而我们可以选择 $22112$ 避开这种情况。

注意到与具体的摆放位置无关，因此计数只需要考虑直接算，形如 $\binom n 1 + \binom n 4 + \binom n 7 \cdots$ 之类的。

算这个东西可以考虑 ~~带入单位根~~ $f_{i,0}=f_{i-1,1}+f_{i-1,2}$ 直接递推预处理。

谨防 $n=1$ corner case。

```cpp
//
// Problem: P9252 [PA 2022] Wielki Zderzacz Termionów
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9252
// Memory Limit: 512 MB
// Time Limit: 2000 ms

#include <iostream>
#include <string>
using namespace std;
const int pmod = 1e9 + 7;
int f[ 1000010 ][ 3 ];
int cnt[ 3 ][ 2 ];
int n;
int solve()
{
    if ( n == 1 )
    {
        if ( cnt[ 0 ][ 1 ] )
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    int t = abs( cnt[ 1 ][ 0 ] + cnt[ 1 ][ 1 ] - cnt[ 2 ][ 0 ] - cnt[ 2 ][ 1 ] ) % 3,
        s = cnt[ 0 ][ 0 ] + cnt[ 0 ][ 1 ];
    long long int ans = 0;
    if ( t != 0 )
    {
        ( ans += f[ s ][ 0 ] ) %= pmod;
    }
    if ( t != 1 )
    {
        ( ans += f[ s ][ 1 ] ) %= pmod;
    }
    if ( t != 2 )
    {
        ( ans += f[ s ][ 2 ] ) %= pmod;
    }
    if ( n & 1 )
    {
        if ( cnt[ 1 ][ 0 ] == 0 and cnt[ 2 ][ 1 ] == 0 )
        {
            ans--;
        }

        if ( cnt[ 1 ][ 1 ] == 0 and cnt[ 2 ][ 0 ] == 0 )
        {
            ans--;
        }
    }
    return ( ans + pmod ) % pmod;
}
int id( char c )
{
    if ( c == 'C' )
    {
        return 1;
    }
    if ( c == 'Z' )
    {
        return 2;
    }
    if ( c == 'N' )
    {
        return 0;
    }
}
int main()
{
    cin.tie( 0 );
    int m;
    cin >> n >> m;
    string str;
    cin >> str;
    str = " " + str;
    for ( int i = 1; i <= n; i++ )
    {
        cnt[ id( str[ i ] ) ][ i & 1 ]++;
    }
    f[ 0 ][ 0 ] = 1;
    for ( int i = 1; i <= n; i++ )
    {
        f[ i ][ 0 ] = ( f[ i - 1 ][ 1 ] + f[ i - 1 ][ 2 ] ) % pmod;
        f[ i ][ 1 ] = ( f[ i - 1 ][ 0 ] + f[ i - 1 ][ 2 ] ) % pmod;
        f[ i ][ 2 ] = ( f[ i - 1 ][ 1 ] + f[ i - 1 ][ 0 ] ) % pmod;
    }
    cout << solve() << '\n';
    while ( m-- )
    {
        int pos;
        char c;
        cin >> pos >> c;
        cnt[ id( str[ pos ] ) ][ pos & 1 ]--;
        str[ pos ] = c;
        cnt[ id( str[ pos ] ) ][ pos & 1 ]++;
        cout << solve() << '\n';
    }
}
```



---

## 作者：_•́へ•́╬_ (赞：3)

## 题面

有红绿蓝三种粒子。

相邻两个红粒子可以变成一个绿粒子，相邻两个绿粒子可以变成一个红粒子，一个蓝粒子会随机地变成一个红或绿粒子。

问有多大概率，存在一种方法使所有粒子变成一个粒子。

带修。

## 思路

考虑找一个有效优秀的判定条件。

$C+C=Z,Z+Z=C$ 让我想到了三进制加法，$1+1=2,2+2=1$。

转成三进制，加起来是三的倍数就不合法，否则就合法。

现在问题就是计数 `N` 的转化。

合法方案不好计数，计数不合法的。

假设现在有 $b$ 个 `C`，$c$ 个 `Z`，$d$ 个 `N`。
$$
\sum\limits_{i=0}^d[b+2c+d+i\equiv0\pmod 3]\times C_d^i
$$
记 $x=-b-c-c-d\mod 3$，上面那个式子是 $f(d,x)$。

根据杨辉三角，有 $f(d,x)=f(d-1,x)+f(d-1,x-1)$，因为 $0\leq x\leq 2$，直接预处理即可。

然后发现样例过不掉，发现有 `CZCZCZC` 和 `ZCZCZCZCZ` 酱紫的情况，去掉即可。注意不要去了 $n=1$ 和 $n$ 为偶数的情况。

-----

过了很久以后再来看这个题，发现前面写的很不严谨。解释一下为啥能直接去。

实际上不合法的序列有四种可能：`CZ`，`ZC`，`CZC`，`ZCZ`。

前两种和模 $3$ 余 $0$，肯定能考虑到。

后两种只需考虑原串长酱紫的情况。

可以证明如果是经过若干次操作之后变成酱紫，可以回退一步，最终可以成功。例：

```plain
czczc
zzzczc//回退
zcczc
zzzc
zcc
zz
c
```

## code

```cpp
#include<stdio.h>
#define mod 1000000007
#define N 200009
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,q,b,c,d,fac[N],inv[N],e,f,cc[N][3];char a[N];
inline long long ksm(long long a,int b)
{
	long long ans=1;
	for(;b;b>>=1,a*=a,a%=mod)if(b&1)ans*=a,ans%=mod;
	return ans;
}
inline int C(const int&n,const int&m)
{
	return n<m?0:(long long)(fac[n])*inv[m]%mod*inv[n-m]%mod;
}
inline void work()
{
	int x=(3-(b+c+c+d)%3)%3,ans=ksm(2,d)-cc[d][x];
	// for(int i=x;i<=d;i+=3)ans-=C(d,i),ans>>31&&(ans+=mod);
	if(n>1&&(n&1)&&e==b+c)--ans;
	if(n>1&&(n&1)&&f==b+c)--ans;
	ans>>31&&(ans+=mod);
	printf("%d\n",ans);
}
main()
{
	read(n);read(q);
	cc[0][0]=1;cc[0][1]=cc[0][2]=0;
	for(int i=1;i<=n;++i)
	{
		cc[i][0]=cc[i-1][0]+cc[i-1][2]-mod;cc[i][0]>>31&&(cc[i][0]+=mod);
		cc[i][1]=cc[i-1][0]+cc[i-1][1]-mod;cc[i][1]>>31&&(cc[i][1]+=mod);
		cc[i][2]=cc[i-1][1]+cc[i-1][2]-mod;cc[i][2]>>31&&(cc[i][2]+=mod);
	}
	for(int i=0;i<n;++i)o:switch(a[i]=nc())
	{
		case'C':++b;if(i&1)++e;else++f;break;
		case'Z':++c;if(i&1)++f;else++e;break;
		case'N':++d;break;
		default:goto o;
	}
	work();
	for(int u,v;q--;work())
	{
		read(u);v=nc();--u;
		switch(a[u])
		{
			case'C':--b;if(u&1)--e;else--f;break;
			case'Z':--c;if(u&1)--f;else--e;break;
			case'N':--d;break;
		}
		switch(a[u]=v)
		{
			case'C':++b;if(u&1)++e;else++f;break;
			case'Z':++c;if(u&1)++f;else++e;break;
			case'N':++d;break;
		}
	}
}
```



---

