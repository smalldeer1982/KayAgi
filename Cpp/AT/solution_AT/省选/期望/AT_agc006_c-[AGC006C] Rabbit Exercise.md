# [AGC006C] Rabbit Exercise

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc006/tasks/agc006_c

$ N $ 匹のうさぎがいます。 うさぎ達は $ 1 $ から $ N $ まで番号が振られています。 最初、うさぎ $ i $ は数直線上の座標 $ x_i $ にいます。

うさぎ達は体操をすることにしました。 $ 1 $ セット分の体操は、次のような合計 $ M $ 回のジャンプからなります。 $ j $ 回目のジャンプでは、うさぎ $ a_j $ ($ 2\ <\ =a_j\ <\ =N-1 $) がジャンプします。 このとき、うさぎ $ a_j-1 $ かうさぎ $ a_j+1 $ のどちらかが等確率で選ばれ（これをうさぎ $ x $ とします）、うさぎ $ a_j $ はうさぎ $ x $ に関して対称な座標へジャンプします。

以上の合計 $ M $ 回のジャンプを $ 1 $ セット分の体操として、うさぎ達は $ K $ セット分の体操を続けて繰り返します。 各うさぎについて、最終的な座標の期待値を求めてください。

## 说明/提示

### 制約

- $ 3\ <\ =N\ <\ =10^5 $
- $ x_i $ は整数である。
- $ |x_i|\ <\ =10^9 $
- $ 1\ <\ =M\ <\ =10^5 $
- $ 2\ <\ =a_j\ <\ =N-1 $
- $ 1\ <\ =K\ <\ =10^{18} $

### Sample Explanation 1

うさぎ $ 2 $ がジャンプします。 うさぎ $ 1 $ に関して対称な座標へジャンプすると、座標 $ -2 $ へ移動します。 うさぎ $ 3 $ に関して対称な座標へジャンプすると、座標 $ 4 $ へ移動します。 よって、うさぎ $ 2 $ の最終的な座標の期待値は $ 0.5×(-2)+0.5×4=1.0 $ です。

### Sample Explanation 2

$ x_i $ は相異なるとは限りません。

## 样例 #1

### 输入

```
3
-1 0 2
1 1
2```

### 输出

```
-1.0
1.0
2.0```

## 样例 #2

### 输入

```
3
1 -1 1
2 2
2 2```

### 输出

```
1.0
-1.0
1.0```

## 样例 #3

### 输入

```
5
0 1 3 6 10
3 10
2 3 4```

### 输出

```
0.0
3.0
7.0
8.0
10.0```

# 题解

## 作者：yybyyb (赞：20)

无论怎么样任何一个点每次操作一定是变成$2a_{x-1}(a_{x+1})-a_x$。设$f_x$表示$x$这个点当前的期望，假设当前点要进行依次变换，那么期望为$\frac{1}{2}((2f_{x-1}-f_x)+(2f_{x+1}-f_x))=f_{x+1}+f_{x-1}-f_x$。

好的，然后进行$K$轮就不会了。怎么办呢？(当然是点开题解了啊)。闲着无聊来差分一下，设$d_i=f_i-f_{i-1}$，那么执行完一次操作之后：$d_i=(f_{i-1}+f_{i+1}-f_i)-f_{i-1}=f_{i+1}-f_i$，$d_{i+1}=f_{i+1}-(f_{i-1}+f_{i+1}-f_i)=f_i-f_{i-1}$。

好啊，一次操作等价于交换$d_i,d_{i+1}$，那么我们只要记录一下做完一轮操作之后$d_i$都到哪里去了，然后就可以倍增了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long
#define MAX 100100
inline int read()
{
	int x=0;bool t=false;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')t=true,ch=getchar();
	while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
	return t?-x:x;
}
int n,x[MAX],m,d[MAX],ans[MAX],tmp[MAX];ll K;
double a[MAX];
int main()
{
	n=read();
	for(int i=1;i<=n;++i)x[i]=read();
	m=read();cin>>K;
	for(int i=1;i<=n;++i)d[i]=i,ans[i]=i;
	for(int i=1;i<=m;++i)
	{
		int x=read();
		swap(d[x],d[x+1]);
	}
	while(K)
	{
		if(K&1)
		{
			for(int i=1;i<=n;++i)tmp[i]=ans[d[i]];
			for(int i=1;i<=n;++i)ans[i]=tmp[i];
		}
		for(int i=1;i<=n;++i)tmp[i]=d[d[i]];
		for(int i=1;i<=n;++i)d[i]=tmp[i];
		K>>=1;
	}
	for(int i=1;i<=n;++i)a[i]=x[ans[i]]-x[ans[i]-1];
	for(int i=1;i<=n;++i)printf("%.1lf\n",a[i]+=a[i-1]);
	return 0;
}
```



---

## 作者：Kinandra (赞：6)

标签: 期望, 差分, 置换.

我们首先考虑一次跳跃对于答案的影响, 显然只改变跳跃的兔子的答案, 设这只兔子坐标为 $y$ , 跳跃后为 $y'$, 与其相邻的两只兔子坐标分别为 $x, z$, 我们考虑三元组 $(x,y,z)$ 的变化情况.

那么一次跳跃之后会转移到 $(x, 2x-y, z)$ 或 $(x, 2z-y, z)$ , 所以 $E(y')=\frac{E(2x-y)+E(2z-y)}{2}=E(x)+E(z)-E(y)$ , 那么我们只要实时维护好 $E$ 就行了.

然而暴力的 $O(mk)$ 做法并不可取, 我们容易感觉到 $k$ 轮操作必然会有某种循环的形式在其中, 需要发现更多性质来找到这种循环.

根据上面的推导一次操作会使 $(x, y, z)$ 变成 $(x, x+z-y, z)$, 这个看起来毫无规律, 观察发现三元组差分之后会有美妙的形式: $(x, y-x, z-y)$ 变成 $(x, z-y, y-x)$ , 等价于交换第二, 三个元素.

于是差分后一次加减操作变成了一个交换操作, 多次交换操作可以用轮换的形式表示, 我们用轮换表示出一轮操作的结果, 如果有了解过关于置换的知识就可以很简单的解决本题了, 不赘述.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, m;
long long x[200005], k;
int a[200005], nx[200005];
int res[200005], vis[200005], st[200005], top;
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) x[i] = read(), nx[i] = i;
    for (int i = n; i >= 1; --i) x[i] -= x[i - 1];
    m = read(), scanf("%lld", &k);
    for (int i = 1; i <= m; ++i) a[i] = read();
    for (int j = 1; j <= m; ++j) swap(nx[a[j]], nx[a[j] + 1]);

    for (int i = 1, j; i <= n; ++i) {
        if (vis[i]) continue;
        st[top = vis[i] = 1] = i, j = nx[i];
        while (j != i) st[++top] = j, j = nx[j], vis[j] = 1;
        for (j = 1; j <= top; ++j) res[st[j]] = st[(j + k - 1) % top + 1];
    }
    long long t = 0;
    for (int i = 1; i <= n; ++i) t += x[res[i]], printf("%lld.0\n", t);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：AsunderSquall (赞：4)

# 前言

本题目前有 $5$ 篇题解，其中三篇是带 $\log$ 的，两篇是线性的，但是这两篇感觉讲的都不是很清楚，所以我来写一篇题解。  

# 题意

有 $n$ 个点，坐标分别为 $x_1,x_2\cdots x_n$。  
有一个大操作，分为 $m$ 个小操作。  
第 $i$ 个小操作选择第 $a_i(2\le a_i \le n-1)$ 个点，然后等概率的选取 编号为 $a_i+1$ 或者 编号为 $a_i-1$ 的点，关于它进行第 $a_i$ 个点的对称操作。  
总共进行 $k$ 次大操作。  
最后，求每个点最终坐标的期望。

# 题解
首先设选中的点为 $a$，那么它期望的新位置为 $\dfrac{(2x_{a+1}-x_a)+(2x_{a-1}-x_a)}{2}=x_{a+1}+x_{a-1}-x_a$  
然后根据期望的可加性，我们可以直接得出 $E_a'=E_{a+1}+E_{a-1}-E_a$  

然后看到这个有加有减的式子，而且把系数相加减发现是 $1$，考虑差分数组。  

令 $E_a=\sum_{i=1}^a d_i$  
只有 $d_i$ 和 $d_{i+1}$ 发生变化。  
$E_{a}=E_{a-1}+d_i,E_{a+1}=E_{a-1}+d_i+d_{i+1}$  
则 $Ea'=E_{a-1}+d_{i+1}$   
然后可以推出 $d_i'=d_{i+1},d_{i+1}'=d_i$  
也就是说，每次操作实际上是把 $d_i$ 和 $d_{i+1}$ 换了个位置。  

那么我们记录一下一次大操作之后 $d_i$ 跑到了第几个位置，显然这是一个置换（排列）。  
然后我们求这个置换的 $k$ 次方。 

这个可以倍增，用类似快速幂的东西来做。  
但是我们可以做到线性。  

具体来说，先把置换拆成若干个循环，求出这些循环的大小，那么这些位置实际要移动的其实就是 $k \bmod size$ 位。找到起点移到的位置，然后递推就行了。

代码：
```cpp
#include<bits/stdc++.h>
#define rd(x) x=read()
#define int long long
using namespace std;
const int mod=998244353;
const int N=2e6+5;
inline int read(){int x=0,f=1;char ch=getchar();while((ch>'9' || ch<'0')){if(ch=='-') f=-1;ch=getchar();}while('0'<=ch && ch<='9') x=x*10+(ch^48),ch=getchar();return x*f;}
inline int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=ret*x%mod;x=x*x%mod;y>>=1;}return ret;}
int n,m,k,t;
int a[N],x[N],d[N];
int p[N],v[N],q[N];
signed main()
{
    rd(n);
    for (int i=1;i<=n;i++) rd(x[i]);
    rd(m);rd(k);
    for (int i=1;i<=m;i++) rd(a[i]);
    for (int i=1;i<=n;i++) d[i]=x[i]-x[i-1];
    for (int i=1;i<=n;i++) p[i]=i;
    for (int i=1;i<=m;i++) swap(p[a[i]],p[a[i]+1]);
    for (int i=1;i<=n;i++) if (!v[i])
    {
        int j=i,sz=0;
        while (!v[j]) v[j]=1,j=p[j],sz++;
        int step=k%sz;j=i;
        while (step--) j=p[j];
        int s=i;while (sz--) q[s]=j,s=p[s],j=p[j];
    }
    for (int i=1;i<=n;i++) x[i]=d[q[i]];
    for (int i=1;i<=n;i++) x[i]=x[i-1]+x[i];
    for (int i=1;i<=n;i++) printf("%lld.0\n",x[i]);//这个保留小数真的好诈骗好无聊啊
}
```

---

## 作者：sky_of_war (赞：3)

同步更新于我的博客：[AGC006C](https://www.skyofwar.net/2019/04/18/agc006c.html)

# Description
有$n$只兔子站在数轴上。为了方便，将这些兔子标号为$1\ldots n$。第$i$只兔子的初始位置为$a_i$。
现在这些兔子会按照下面的规则做若干套体操。每一套体操由$m$次跳跃组成；在第$j$次跳跃的时候，第$c_j(2\leqslant c_j\leqslant n-1) $只兔子会等概率随机选择第$c_j-1$或$c_j+1$只兔子中的一只（不妨设选择了第$x$只兔子），然后跳当前位置到关于第$x$只兔子对称的点。
这些兔子会按顺序做$k$套相同的体操。现在请你求出，每一只兔子做完$k$套体操之后最终位置坐标的期望值。
$n,m\leqslant 100000,k\leqslant {10}^{18}$
# Solution
首先我们有一个十分暴力的做法：对于每次操作，有
$$ a_x=\frac{1}{2}(2a_{x-1}-a_x)+\frac{1}{2}(2a_{x+1}-a_x)=a_{x-1}+a_{x+1}-a_x $$
那么不妨来找找规律。
假设有三个数$a_1,a_2,a_3$，$c_1=2$，变换后得到$a_1,a_1+a_3-a_2,a_3$。差分一下：
$$ \begin{aligned} a_1,a_2,a_3&\rightarrow a_1,a_2-a_1,a_3-a_2\\ a_1,a_1+a_3-a_2,a_3&\rightarrow a_1,a_3-a_2,a_2-a_1 \end{aligned} $$
相当于把$a_{c_1},a_{c_1+1}$交换了一下。也就是说，兔子$i$跳跃之后，它与兔子$i-1$的期望距离会与兔子$i+1$交换。
所以可以直接把$m$次操作看成$m$个交换，做完这些操作看成$1$到$n$的置换。把整个置换拆成很多个轮换，直接在每个轮换上面走$k$步就行了。时间复杂度：$\mathcal O(n+m)$

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
typedef long long ll;
template <class T>
inline void _read(T &x)
{
    x = 0;
    char t = getchar();
    while (!isdigit(t) && t != '-') t = getchar();
    if (t == '-')
    {
        _read(x);
        x *= -1;
        return ;
    }
    while (isdigit(t))
    {
        x = x * 10 + t - '0';
        t = getchar();
    }
}
template <class T>
inline void _read(T &a, T &b)  { _read(a), _read(b); } 
ll a[MAXN], id[MAXN], st[MAXN], n, m, k, vis[MAXN], ans[MAXN];
int main(int argc, char **argv)
{
    _read(n);
    for (int i = 1; i <= n; ++i) _read(a[i]), id[i] = i;
    for (int i = n; i ; --i) a[i] -= a[i - 1];
    _read(m, k);
    for (int i = 1, x; i <= m; ++i) _read(x), swap(id[x], id[x + 1]);
    for (int i = 1; i <= n; ++i)
    {
        if (!vis[i])
        {
            int  top = 0;
            for (int j = i; !vis[j]; j = id[j]) st[++top] = j, vis[j] = 1;
            for (int j = 1; j <= top; ++j) ans[st[j]] = a[st[(k + j - 1) % top + 1]];
        }
    }
    for (int i = 1; i <= n; ++i) ans[i] += ans[i - 1], printf("%lld\n", ans[i]);
    return 0;
}
```

---

## 作者：worldvanquisher (赞：2)

考虑每个点进行一次操作会变成什么。假如说这个点是 $x_i$，那么把它关于它左边的某个点 $y$ 对称后的坐标就是 $y-(x_i-y)=2y-x_i$。把它关于它右边的某个点 $y$ 对称后的坐标就是 $y+(y-x_i)=2y-x_i$。

发现两个的公式一样。于是对一个点进行操作后坐标的期望就会变成：$\dfrac{2x_{a_{i}-1}-x_{a_i}+2x_{a_{i}+1}-x_{a_i}}{2}=x_{a_{i}-1}+x_{a_{i}+1}-x_{a_i}$。

做过 NOIP2021 T3 的都熟悉这个操作，就是交换差分。具体的，原来的数列是：

原序列：$a_{i-1}\ \ \ \ \ \ \ \ \ \ \ \ a_{i}\ \ \ \ \ \ \ \ \ \ \ \ a_{i+1}$  
差分：$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ a_i-a_{i-1}\ a_{i+1}-a_i$

现在我们对 $a_i$ 进行操作，使其变成 $a_{i-1}+a_{i+1}-a_i$ ：

原序列：$a_{i-1}\ \ \ \ \ \ \ \ \ \ \ \ a_{i-1}+a_{i+1}-a_i\ \ \ \ \ \ \ \ \ \ \ \ a_{i+1}$  
差分：$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ a_{i+1}-a_{i}\ \ \ \ \ \ \ \ \ \ \ \ a_{i}-a_{i-1}$

再不行可以手算验证。于是我们对于原来的操作序列中的某个操作 $a_i$ 就可以变成交换差分序列中 $a_i$ 和 $a_i+1$ 位置的值。根据期望的线性性，我们只需要不断进行操作即可得到最终的期望。

我们把差分序列的顺序看做一个排列，初始为 $1\dots n$。这样一次操作就是交换两个相邻的数。暴力处理一遍操作序列得到序列 $p$ ，然后问题就是怎么对初始序列进行 $k$ 次这样的变换。

一个套路是快速幂。具体地，一次操作可以看做把 $i$ 位置上的值变成 $p_i$ 位置上的值。然后我们发现这个操作是可以倍增处理的，于是可以用类似快速幂的方法解决。

放个代码。记得开 long long。
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
int n,m,x[100010],a[100010],p[100010],ans[100010],tmp[100010];
long long k;
void qpow(int a[],long long b){
    while(b){
        if(b&1){
            for(int i=1;i<=n;i++)tmp[i]=ans[p[i]];
            for(int i=1;i<=n;i++)ans[i]=tmp[i];
        }
        for(int i=1;i<=n;i++)tmp[i]=p[p[i]];
        for(int i=1;i<=n;i++)p[i]=tmp[i];
        b>>=1;
    }
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&x[i]),p[i]=ans[i]=i;
    scanf("%lld%lld",&m,&k);
    for(int i=1;i<=m;i++){
        scanf("%lld",&a[i]);
        swap(p[a[i]],p[a[i]+1]);
    }
    qpow(p,k);
    for(int i=1;i<=n;i++)a[i]=x[i]-x[i-1];
    for(int i=1;i<=n;i++)tmp[i]=a[ans[i]];
    for(int i=1;i<=n;i++)a[i]=tmp[i];
    for(int i=1;i<=n;i++)x[i]=x[i-1]+a[i];
    for(int i=1;i<=n;i++)printf("%lld.0\n",x[i]);
    return 0;
}
```

---

## 作者：_Felix (赞：2)

设 $i$ 位置的期望是 $f_i$

（以下部分中，加'表示操作后的值）

注意到每次操作$i$，$f'_i = f_{i-1}+f_{i+1}-f_i$，时间复杂度 $O(mk)$。

移项发现 $f'_i-f_{i-1}=f_{i+1}-f_i$，$f_{i+1}-f'_i=f_i-f_{i-1}$，设$d_i=d_{i+1}-d_i$，则 $d'_i=d_{i+1}, d'_{i+1}=d_i$，相当于交换$d_i$ 与 $d_{i+1}$。每一轮相当于一个置换，然后倍增，大概是对一个置换快速幂。


---

## 作者：Cesare (赞：2)

# $Rabbit$ $Exercise$

## $Description$

![](https://s2.ax1x.com/2019/04/07/AhO97F.png)



## $Solution$

又是一道经典套路题。

首先考虑 $50pts$ 的做法。

可以发现跳到左边的贡献是 $2\times c_{j - 1} - c_j$ ，右边的贡献 $2\times c_{j + 1} - c_j$ ，所以期望就是 

$$\frac{(2 \times c_{j - 1} + 2 \times c_{j + 1} - 2 \times c_j)}{2}$$

即

$$c_{j - 1} + c_{j + 1} - c_j$$

所以暴力就是做 $mk$ 次这个东西即可。

然后考虑正解。

此时，就要用到一种经典套路。

我们考虑先做一次差分，设 

$$f_i = a_i - a_{i - 1}$$

然后我们发现，把 $c_j$ 插到 $c_{j - 1}$ 与 $c_{j +1}$ 改变位置就相当于交换 $c_j$ 与 $c_{j + 1}$ 。

然后就非常巧妙的实现了跳来跳去的一次操作。

然后我们考虑先把每个能交换的位置都交换一次，即跳一次，相当于初始化。

之后再倍增的跳，跳完之后可以很方便的把 $a_i$ 加回去，就是每一位的答案。

为什么可以这么做呢 $?$ 

首先，倍增的正确性是显然的。

然后，由于我们先使用了~~经典套路~~差分来使插入操作转变成了交换操作。

所以，就巧妙地实现了题目的要求。



## $Code:$

```cpp
#include<bits/stdc++.h>
//#include<tr1/unordered_map>
//#include"Bignum/bignum.h"
//#define lll bignum
#define ls(x) ( x << 1 )
#define rs(x) ( x << 1 | 1 )
//#define mid ( ( l + r ) >> 1 )
#define lowbit(x) ( x & -x )
#define debug(x) (cout << "#x = " << x << endl)
#define re register
#define For(i, j, k) for(re int i = (j); i <= (k); i++)
#define foR(i, j, k) for(re int i = (j); i >= (k); i--)
#define Cross(i, j, k) for(re int i = (j); i; i = (k))
using namespace std;
typedef long long ll;
const ll N = 100011;
const ll p = 998244353;
const ll inf = 0x3f3f3f3f3f3f;

ll n, m, k, x, res = 0, a[N], b[N], c[N], B[N];

namespace IO {

	#define dd ch = getchar()
	inline ll read() {
		ll x = 0; bool f = 0; char dd;
		for (; !isdigit (ch); dd) f ^= (ch == '-');
		for (; isdigit (ch); dd)  x = (x << 3) + (x << 1) + (ch ^ 48);
		return f? -x: x;
	}
	#undef dd

	inline void write( ll x ) {
		if ( x < 0 ) putchar ( '-' ), x = -x;
		if ( x > 9 ) write ( x / 10 ); putchar ( x % 10 | 48 );
	}

	inline void wrn ( ll x ) { write (x); putchar ( ' ' ); }

	inline void wln ( ll x ) { write (x); putchar ( '\n' ); }

	inline void wlnn ( ll x, ll y ) { wrn (x), wln (y); }

}

using namespace IO;

inline void Redouble ( ll x ) {
	for (; x; x >>= 1) {
		if (x & 1) {
			For ( i, 1, n ) B[i] = a[b[i]]; 
			For ( i, 1, n ) a[i] = B[i];
		}
		For ( i, 1, n ) B[i] = b[b[i]];
		For ( i, 1, n ) b[i] = B[i];
	}
}

int main() 
{
//	freopen("qwq.in", "r", stdin);
//	freopen("qwq.out", "w", stdout);
	n = read(); 
	For ( i, 1, n ) 
		a[i] = (read() + p) % p, b[i] = i;
	foR ( i, n, 1 ) a[i] = a[i] - a[i - 1];
	m = read(), k = read();
	For ( i, 1, m ) x = read(), swap ( b[x], b[x + 1] );
	Redouble (k);
	For ( i, 1, n ) 
		res = (res + a[i] + p) % p, wln (res);
	return 0;
}

/*
3
-1 0 2
1 1
2

998244352
1
2
*/

```

[题目链接](<https://www.luogu.org/problemnew/show/AT2164>)

---

## 作者：zhiyangfan (赞：1)

推销一下 AGC006 的博客：[qwq](https://www.luogu.com.cn/blog/i-am-zhiyangfan/atcoder-grand-contest-006-bu-ti-zong-jie)（
### 题意
一行上面有 $n$ 只兔子，分别从 $1$ 到 $n$ 编号，编号为 $i$ 的兔子初始位置为 $x_i$。兔子们要执行一段操作。一段操作以一个长为 $m$ 的操作序列 $a$ 描述，其中 $a_i(2\le a_i\le n-1)$ 表示这次操作由兔子 $a_i$ 执行，它会等概率选择兔子 $a_i-1$ 和 $a_i+1$ 中的一个，并跳到以它为对称中心和现在的位置中心对称的位置。现在给出初始位置和兔子们执行这段操作的次数 $k$，求出所有兔子最终的期望位置。($3\le n\le10^5,|x_i|\in\{x\in \mathbb{Z}||x|\le10^9\},1\le m\le10^5,1\le k\le10^{18}$)

### 题解
首先有一个显然的结论，也就是执行完一个操作后，$a_i$ 号兔子所在期望位置就会变为：
$$E(a_i)=\dfrac{1}{2}(2E(a_i-1)-E(a_i))+\dfrac{1}{2}(2E(a_i+1)-E(a_i))$$

但如果直接按照这个式子递推，您将会收获一个 $\tt TLE$ 和 5 分钟的罚时。所以我们考虑变一变这个式子，稍微合并一下有：
$$E(a_i)=E(a_i-1)+E(a_i+1)-E(a_i)$$

好了如果你没有灵光乍现这题也就到此为止了，但如果你发现原序列的差分序列在这样一次操作后会有很神奇的变化，这题也就到此为止了，如果我们令 $d_i=E(a_i)-E(a_i-1)$，则有：
$$d_i=E(a_i)-E(a_i-1)=E(a_i+1)-E(a_i)$$
$$d_{i+1}=E(a_i+1)-E(a_i)=E(a_i)-E(a_i-1)$$

可以观察到，$d_i$ 和 $d_{i+1}$ 在一次操作的前后交换了位置，利用这个性质，我们可以求出一段操作后，差分序列的每个位置会跑到哪去，注意到执行 $k$ 次其实是个循环的过程，所以我们就可以找到循环节直接做了。这个循环节其实可以理解为置换环的大小，比如每次操作有 $1\rightarrow2,2\rightarrow4,4\rightarrow1$，则置换环如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/oult3tr1.png)

每次操作其实就是在置换环上走一步。求置换环的部分用个栈记录一下就好了，具体实现见代码，时间复杂度 $\mathcal{O}(m+n)$。
```cpp
#include <cstdio>
#include <algorithm>
const int N = 1e5 + 10;
int id[N], vis[N], st[N], tp; double x[N], d[N], dd[N]; 
int main()
{
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) 
        scanf("%lf", &x[i]), d[i] = x[i] - x[i - 1], id[i] = i;
    int m; long long k; scanf("%d%lld", &m, &k); int now = 0;
    for (int i = 1, a; i <= m; ++i) scanf("%d", &a), std::swap(id[a], id[a + 1]);
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i]) continue; tp = 0;
        for (int j = i; !vis[j]; j = id[j]) vis[j] = 1, st[++tp] = j;
        for (int j = 1; j <= tp; ++j) dd[st[j]] = d[st[(k + j - 1) % tp + 1]];
    }
    for (int i = 1; i <= n; ++i) dd[i] += dd[i - 1];
    for (int i = 1; i <= n; ++i) printf("%.1lf\n", dd[i]); return 0;
}
```

---

## 作者：0xyz (赞：0)

- 给定 $n$ 只兔子原本所在的位置 $x_1\sim x_n$，每一轮会有 $m$ 只兔子同时移动，第 $i$ 只兔子编号是 $a_i$，它会等概率移动到 $2x_{a_i-1}-x_{a_i}$ 和 $2x_{a_i+1}-x_{a_i}$ 这两个位置中的一个。求进行 $k$ 轮后所有 $n$ 只兔子最终位置的期望。

由于期望的可加性，我们有 $E'_{i}=\frac{1}{2}(2E_{i-1}-E_i+2E_{i+1}-E_i)=E_{i-1}+E_{i+1}-E_i$。我们发现这个式子下标连续，所以考虑差分。令 $E_i=\sum\limits_{j=1}\limits^{i}d_{j}$，那么我们有 $E'_i=\sum\limits_{j=1}\limits^{i-1}d_j+d_{i+1}$。从而我们可以看做 $d_i$ 和 $d_{i+1}$ 进行了交换，这样在只考虑一次移动时只有 $E_i$ 发生改变。

那么，对于一轮的操作，其实就是一堆 $d$ 进行了 $m$ 次交换。我们预处理出一轮的 $d$ 交换的情况，是一个关于 $n$ 的排列的置换。我们对于每一个部分预处理出周期，然后暴力处理周期之外的部分即可。

时间复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=100010;
ll n,m,k,x[_],d[_],e[_],p[_],q[_],v[_];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>x[i],d[i]=x[i]-x[i-1],p[i]=q[i]=i;
	cin>>m>>k;
	for(ll i=1,a;i<=m;i++)cin>>a,swap(p[a],p[a+1]);
	for(ll i=1;i<=n;i++)
		if(!v[i]){
			ll s=1,t=i;v[i]=1;
			for(ll j=p[i];j!=i;j=p[j])s++,v[j]=1;
			for(ll j=k%s;j;j--)q[t]=p[q[t]];
			for(ll j=i;p[j]!=i;j=p[j])q[p[j]]=p[q[j]];
		}
	for(ll i=1;i<=n;i++)e[i]=d[q[i]];
	for(ll i=1;i<=n;i++)e[i]+=e[i-1],cout<<e[i]<<'\n';
	return 0;
} 
```

---

## 作者：ezoixx130 (赞：0)

考虑跳第 $i$ 个点的时候，如果往左跳会跳到 $a_{i-1}-(a_{i}-a_{i-1})$ 即 $2a_{i-1}-a_i$ 的位置上，如果往右跳会跳到 $a_{i+1}+(a_{i+1}-a_i)$ 即 $2a_{i+1}-a_i$ 的位置上。

所以对 $i$ 个点进行操作的话，期望位置会变成 $\large \frac{2a_{i-1}-a_i+2a_{i+1}-a_i}{2}$ 即 $\large a_{i-1}-a_i+a_{i+1}$。

但是这种操作不好维护，因为你要做 $10^{18}$ 轮这样的操作，暴力处理显然不是正解。

如果将期望序列差分，考虑对 $i$ 进行操作的时候，设原本第 $i-1,i,i+1$ 号点的位置期望分别为 $a,b,c$，那么差分序列为 $b-a,c-b$。对 $i$ 号点进行完操作以后，期望序列变为 $a,a-b+c,c$，差分序列为 $c-b,b-a$。也就是说，对一个点进行操作等价于在期望的差分序列上交换两个数。

那么这样就好维护多了，因为这样的一轮操作相当于对差分序列进行一个置换。要做 $10^{18}$ 轮这样的操作，对置换进行快速幂即可。

时间复杂度：$O(n\log k)$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010

int n,m,a[MAXN],ans[MAXN],res[MAXN],tmp[MAXN];
long long k;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=1;i<n;++i)ans[i]=i;
	scanf("%d%lld",&m,&k);
	for(int i=1;i<=m;++i)
	{
		int x;
		scanf("%d",&x);
		swap(ans[x],ans[x-1]);
	}
	for(int i=1;i<n;++i)res[i]=i;
	while(k)
	{
		if(k&1)
			for(int i=1;i<n;++i)res[i]=ans[res[i]];
		for(int i=1;i<n;++i)tmp[i]=ans[ans[i]];
		for(int i=1;i<n;++i)ans[i]=tmp[i];
		k>>=1;
	}
	long long sum=a[1];
	for(int i=1;i<=n;++i)
	{
		printf("%lld.0\n",sum);
		sum+=a[res[i]+1]-a[res[i]];
	}
}
```

---

