# Nezzar and Board

## 题目描述

$ n $ distinct integers $ x_1,x_2,\ldots,x_n $ are written on the board. Nezzar can perform the following operation multiple times.

- Select two integers $ x,y $ (not necessarily distinct) on the board, and write down $ 2x-y $ . Note that you don't remove selected numbers.

Now, Nezzar wonders if it is possible to have his favorite number $ k $ on the board after applying above operation multiple times.

## 说明/提示

In the first test case, the number $ 1 $ is already on the board.

In the second test case, Nezzar could perform the following operations to write down $ k=0 $ on the board:

- Select $ x=3 $ and $ y=2 $ and write down $ 4 $ on the board.
- Select $ x=4 $ and $ y=7 $ and write down $ 1 $ on the board.
- Select $ x=1 $ and $ y=2 $ and write down $ 0 $ on the board.

In the third test case, it is impossible to have the number $ k = -1 $ on the board.

## 样例 #1

### 输入

```
6
2 1
1 2
3 0
2 3 7
2 -1
31415926 27182818
2 1000000000000000000
1 1000000000000000000
2 -1000000000000000000
-1000000000000000000 123
6 80
-5 -20 13 -14 -2 -11```

### 输出

```
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：fanfansann (赞：42)



整理的算法模板合集： [***ACM模板***](https://fanfansann.blog.csdn.net/article/details/105493218)

[可能会是更好的阅读体验（](https://fanfansann.blog.csdn.net/article/details/113655626)



## D - Nezzar and Board
 **Problem A Nezzar and Board**



我们在黑板上写了 $n$ 个数，$x_1,x_2,\cdots,x_n$。

我们可以无限此地使用一个操作：从黑板上的数字中选择两个数 $x$ 和 $y$ （$x$ 和 $y$ 可以是同一个数）将 $2x-y$ 写到黑板上去（$x$ 和 $y$ 还在）。求整数 $K$ 能否被写到黑板上去。

$1\le T\le10^5,1\le k,x_i\le10^{18}$.

**Solution**

**我这里不需要猜结论或者证明结论**，我的解法只需要**一步步按部就班地往后推就行了**。

首先我们知道每次可以选择两个数 $x$ 和 $y$ 得到 $2x-y$。

这个 $2x-y$ 看上去毫无头绪，因为一个乘以二，一个是本身，两个好像和 $x$ 与 $y$ 毫无关系。我们可以把它们拆开,得到 $x+(x-y)$。

逐渐好起来了，看上去有些头绪了，因为这里实际上表示的是从一个数 $x$ 开始，加上这个数与另一个数的差值，然后得到了一个新数。

我们可以模拟一下：

我们假设：

$x_i=x_j+(x_j-x_k)$

$x_a=x_i+(x_i-x_c)$

$x_b=x_a+(x_a-x_d)$

那么 $x_b$ 就可以表示为：

$x_b=x_j+(x_j-x_k)+(x_i-x_c)+(x_a-x_d)$

我们可以从特殊到一般，得到所有能写到黑板上的数的表达式（为了理解方便，看起来舒服，我们就设能写到黑板上的数为我们题目中想要我们来判断的 $K$）：

那么我们得到了一个表达式：

$x_i+\sum_{j,k}(x_j-x_k)=K$

其中 $j,k$ 可以是我们得到 $K$ 的途中使用的任意一个数的下标，甚至 $x_i$ 可以替换为任意一个 $x$ ，这一点我们下面再详细说明。

特别的，由于题目中特别说明了可以每次选的两个数 $x$ 和 $y$ 可以是同一个数（" **not necessarily distinct** "）所以我们这个表达式不仅可以表示新写到黑板上的数，还可以表示原来就在黑板上的数：$x=x+(x-x)$。

这样我们得到的这个表达式就可以表示所有的黑板上的数字了。

我们可以把左边的 $x_i$ 移到右边，这样两边的形式看上去统一一些，并且也不会影响答案的正确性。

即：

$$\sum_{j,k}(x_j-x_k)=K-x_i$$

其中， $x_i$ 可以换为 $x_1$ ，因为不管 $x_i$ 是谁，我们都可以移动到左边，变成正数 $x_i$，而黑板上的任意一个数都可以由 $x_1$ 通过两次操作得到，例如我们想由 $x_1$ 得到 $x_n$ :

**第一次操作：** 选择 $x_1$ 和 $x_n$ ，得到新数：$x_1+(x_1-x_n)$，写到黑板上。

**第二次操作：** 选择 $x_1$ 和 $x_1+(x_1-x_n)$ ，得到：$x_1+\{x_1-[x_1+(x_1-x_n)]\}=x_1+x_1 -x_1-x_1+x_n=x_n$

（实际上就是第一次是减去它们两个之间的差，那么我们减去这个差不就是加上这个差，也就得到了另一个数。）

同理我们也可以把式子里所有的 $x_k$ 换成 $x_1$。

为什么要换成 $x_1$ 呢，很显然如果还是当作 $x_i$，$x_k$ 来用的话，我们并不知道 $x_i$，$x_k$ 到底是谁 ~

而我们归为一类以后，只有一个变量 $j$ ，我们只需要一次 `for` 循环即可。

最终得：

$$\sum_{j}(x_j-x_1)=K-x_1$$


我们可以设 $a_i$ 表示 $x_i-x_1$，$y_i$ 表示方程的未知数

这样就可以把上述方程转化为一个好看的丢番图方程（线性方程）：

$$a_1y_1+a_2y_2+a_3y_3+\cdots+a_ny_n=K-x_1$$

实际意义就是我们选 $y_1$ 个$a_1$（$a_1=x_1-x_1$），$y_2$ 个 $a_2$（$a_2=x_2-x_1$），$\cdots$，凑成 $K-x_1$。（$y_i$ 可以为 $0$ 嘛）

我们只需要判断这个丢番图方程有解即可。若该方程有解，则说明最开始的式子 $x_i+\sum_{j,k}(x_j-x_k)=K$ 有解（我们全程所有的式子的含义都没有变化，只是形式上的改变），说明 $K$ 可以被通过题中所给的操作凑出来，也就是可以写到黑板上，也就是输出 `YES`。

判断丢番图方程有解，很容易想到裴蜀定理：

**设 $a,b$ 是不全为零的整数，则存在整数$x,y$，使得$ax+by =  \gcd(a,b)$。** 若$m$ 是 $\gcd(x,y)$ 的倍数，方程同样有解（很显然，因为我们只需要两边同时乘上倍数即可。） 

那么对于多个变量同样适用：

即：若 $K-x_1$ 是 $\gcd(x_1-x_1=0,x_2-x_1,x_3-x_1,\cdots,x_n-x1)$  的倍数，则该丢番图方程有解，即 $K$ 一定能够被凑出来写到黑板上，输出 `YES` 。


**Code**

非常简单的代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;
typedef long long ll;
typedef int itn;
const int N = 5e5 + 7, mod = 1e9 + 7;
const ll INF = 1e18 + 7;

ll x[N], n, m, t, k;

int main()
{ds
    scanf("%lld", &t);
    while(t -- ) {
        scanf("%lld%lld", &n, &k);
        for(int i = 1; i <= n; ++ i)
            scanf("%lld", &x[i]);
        ll gcd = 0;
        for(int i = 1; i <= n; ++ i)
            gcd = __gcd(x[i] - x[1], gcd);
        if((k - x[1]) % gcd == 0)
            puts("YES");
        else puts("NO");
    }
    return 0;
}

```

看懂了叭 ~ 超级清晰有没有 (●ˇ∀ˇ●) 我真棒（

点个赞呗![/kel](https://cdn.luogu.com.cn/upload/pic/62226.png)


---

## 作者：Fairicle (赞：8)

本文摘自我的 [妙妙题精选](https://www.luogu.com.cn/blog/Fairicle/yi-suo-ren-lei-sai-wei-ti).

### CF1477A

#### 题意

黑板上有 $x_1,x_2,...,x_n$ 等数，可以选择黑板上的两个数 $x,y$，并在黑板上写上 $2x-y$，求是否能在黑板上写出要求的数 $k$.

#### sol

结论：当 $x_1=0$ 时，当且仅当 $k$ 能被 $g=gcd(x_2,x_3,...,x_n)$ 整除时可行，否则不可行。

即**所有** $g$ 的倍数**都能被写在黑板上**（1）；且黑板上**所有数都是** $g$ 的倍数（2）。

证明（2）：对于所有的数有 $g|x,g|y$，故 $g|2x-y$，证毕。

证明（1）：首先当 $n=2$ 时即只有 $x_1,x_2$ 时显然成立。$(2\times 0-x_2=-x_2,2\times x_2-0=2x_2,2\times -x_2-0=-2x_2...)$，以此类推可发现 $kx_2,k\in Z$ 都能被写在黑板上。

换句话说，存在两个数 $x,y$ 且 $x=0$ 时，黑板上能够构造出 $y$ 的**所有倍数**。

考虑**归纳**，设 $n=p$ 时成立，则 $g_0=gcd(x_2,x_3,...x_p)$ 的所有倍数都被写在了黑板上。

根据贝祖定理，方程 $g_0s-x_{p+1}t=g\ (g=gcd(g_0,x_{p+1}))$ 必有整数解 $s=s_0+\dfrac{kx_{p+1}}{gcd(g_0,x_{p+1})},t=t_0-\dfrac{kg_0}{gcd(g_0,x_{p+1)}}(k\in Z)$。

我们已经知道 $g_0s$ 可以被写在黑板上，而 $x_{p+1}$ 的倍数又可以通过 $0,x_{p+1}$ 构造得出，且必然能求出某组解 $(s',t')$ 使得 $s',t'$ 不同时为奇数，那么就可以在黑板上写下 $g$，则可通过 $0,g$ 构造出所有 $g$ 的倍数。证毕。

如果 $x_1$ **不等于** $0$？那就把 $x_2,x_3,...,x_n,k$ **全都减去** $x_1$！

可以发现，原来两数为 $x,y$，现在为 $x-x_1,y-x_1$，可以得到 $2x-y-x_1$，也就是**所有数都偏移了一个** $x_1$，不会有影响！

看代码可能有更好的阅读体验：

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ri register int
#define ll long long

#define N 200010

ll t,n,k,a[N];

int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(ri i=1;i<=n;++i) cin>>a[i];
        for(ri i=2;i<=n;++i) a[i]-=a[1];
        ll g=abs(a[2]);
        for(ri i=3;i<=n;++i) g=__gcd(g,abs(a[i]));
        if((k-a[1])%g==0) puts("YES");
        else puts("NO");
    }
    return 0;
}
```


---

## 作者：Libra_ (赞：6)

## 题目 [CF1447A](https://codeforces.com/problemset/problem/1477/A)
黑板上有 $n$ 个数，每次任意选两个，在黑板上新写上 $2x-y$，问 $k$ 是否在黑板上出现。

## 分析
* $2x-y=x+(x-y)$ 这意味着，从 $x$ 或 $y$ 出发，差为 $x-y$ 的数都可以到达。

* 假设现在从 $0$ 出发，存在两个差 $d_1$ 和 $d_2$，那么 $d_1$ 和 $d_2$ 的个数可以取任意个，即只需满足 $t_1d_1+t_2d_2=k$ 即可。

* 根据[裴蜀定理](https://oi-wiki.org/math/number-theory/bezouts/)，当 $k \mid \gcd(d1,d2)$ 时有整数解。

* 若不从 $0$ 出发，而从 $x$ 出发，则只需满足 $k-x \mid \gcd(d1,d2) $ 即可。

## 代码
[我的代码](https://www.luogu.com.cn/paste/rzwhsjui)

---

## 作者：Lates (赞：2)

# 题意

> 有个大小为 $n$ 的整数集合，每次可以取出两个数 $x,y$，将 $2x-y$ 加入集合。问 $k$ 是否可能出现在集合中。

# 分析

对于取出的 $x,y$，有 $2x-y = x + (x-y)$。可以理解为，$x$ 生成了集合中某个与数 $y$，以 $x-y$ 为公差的等差数列。然此时有 对于每个数 $x$，有 $\mathcal{O(n)}$ 种差值。不能难想到排序，对于 $x < y < z$，有 $z-x = (z - y) + (y-x)$，那么总共 $\mathcal{O(n^2)}$ 种取值就可以用排序后相邻项的差值表示了。假设排序后数组为 $x_i$, 令 $y_i = x_i -x_{i-1} (i \ge 2)$，只需要判断对于每个不定方程 $x_i + \sum_{j=2}^{n} a_jy_j = k$，是否存在非负整数解。直接使用裴蜀定理，即需要满足 $(k-x_i) | \gcd\limits_{j=2}^{n}y_j$。

时间复杂度 $\mathcal{O(T n\log n)}$

```cpp
signed main(){
	int T=read();
	while(T--) {
		n=read(),k=read();
		for(int i=1;i<=n;++i) a[i] = read();
		sort(a+1,a+1+n);
		int g = -1, flag = 0;
		for(int i=2;i<=n;++i) {
			if(g==-1) g = a[i] - a[i-1];
			else g = gcd(g, a[i] - a[i-1]);
		}		
		for(int i=1;i<=n;++i) if((k - a[i] + g) % g == 0) flag = 1;
		if(flag) puts("Yes");
		else puts("No");
	}
	return 0;
}

```

---

## 作者：FutaRimeWoawaSete (赞：2)

真的没做出来……超级丢脸的（                   

是看了@Fairicle的题解的，所以证明方法是一样的，只不过我证的会潦草一些（


此题的结论是：若 $(k - a_1) \equiv 0 \pmod g$ 则可以把 $k$ 写上去，否则不行。其中 $g = gcd(a_2 - a_1 , a_3 - a_1 , ...... a_n - a_1)$  。                

我们规定 $a$ 序列里面的数和 $k$ 值均向左偏移 $a_1$ ，可以证明这和原问题等价。                      

我们首先有个很显的结论，即黑板上的数都是 $g$ 的倍数，因为每次选择的数 $g|x , g|y$ ，所以显然 $g | 2x - y $ 。  
            
~~这时候如果你在打 CF 的时候就可以瞎猜所有 $g$ 的倍数都会写上去然后过掉此题。~~              

接着我们考虑证另外一个结论：所有 $g$ 的倍数都能写上去。             

- 在 $n = 2$ 的情况下成立。         

- 运用数学归纳法，如果在 $n = p , g_0 = gcd(a_2 , a_3 , a_4 , …… a_p)$ 时成立，那么我们现在只要证明 $g = gcd(g_0 , a_{p + 1})$ 的所有倍数都能被写上去就行了，在 $a_1 = 0$ 的情况下即询问是否可以把 $g$ 给写上去。            
- 因为我们的 $g_0 , a_{p + 1} , 0$ 都在黑板上，所以我们可以把 $g_0 , a_{p + 1}$ 的所有倍数都给写出来。            

- 这之后就是解一个不定方程：$g_0x + a_{p + 1}y = g$ ，根据贝祖定理，这个方程存在一个两两不都为奇数的正整数解，即此时可以把 $g$ 写在黑板上，自然也能把所有 $g$ 的倍数写在黑板上，原结论得证。                

不得不说还是有一定思维难度，卡我这种数学盲人我也没有什么脾气。            
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 2e5 + 5;
long long n,m,a[Len];
inline long long gcd(long long x,long long y)
{
	if(!y) return x;
	return gcd(y , x % y);
}
inline long long Labs(long long x){return x < 0 ? -x : x;}
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%lld %lld",&n,&m);
		for(int i = 1 ; i <= n ; i ++) scanf("%lld",&a[i]);
		long long res = a[1];m -= res;
		for(int i = 1 ; i <= n ; i ++) a[i] -= res;
		res = Labs(a[2]);
		for(int i = 3 ; i <= n ; i ++) res = gcd(res , Labs(a[i]));
		if(!(m % res)) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：Meickol (赞：0)

数论好题。

对于新增的数 $2x−y$ 可以表示为 $x+(x−y)$。

举例子找规律，无非就几种情况：



### 情况一

假如选择的两个数都是原序列中的数，即一个是 $a$，另一个是 $b$。

因为两数类型相同，放置顺序无所谓，显然表示为 $a+(a-b)$。



### 情况二

假如选择的两个数中，一个是原序列中的数 $a$，另一个是新增加的数 $x+(x-y)$。

因为两数类型不同，需要考虑放置顺序，那么存在两种子情况：

- $a+\Bigg(a-\Big(x+(x-y) \Big)\Bigg)$
- $\Big(x+(x-y) \Big)+\Bigg( \Big(x+(x-y) \Big)-a \Bigg)$



第一种情况整理形式得 $a+(a-x)-(x-y)$。

第二种情况初步整理形式得 $\Big(x+(x-y) \Big)+\Bigg( (x-a)+(x-y) \Bigg)$，再次整理得 $x+2(x-y)+(x-a)$



### 情况三

假如选择的两个数都是新增加的数，即一个是 $x+(x-y)$，另一个是 $u+(u-v)$。

因为两数类型相同，放置顺序无所谓，表示为 $\Big(x+(x-y) \Big)+\Bigg( \Big(x+(x-y) \Big)-\Big(u+(u-v) \Big) \Bigg)$，初步整理得 $\Big(x+(x-y) \Big)+\Bigg( (x-u)+(x-y) -(u-v)  \Bigg)$，即 $x+(x-y) +(x-u)+(x-y) -(u-v)$



### 归纳总结

不难发现，以上三种情况，甚至对于更多类型的数组合的情况，比如 多次新增得到的叠加态的复杂形式的数 与 任意一种类型的数进行处理，其实得到的形式也是一样的。



都可以表示为一个原序列中的数加上若干个原序列中任意两数之差的形式。

形式化表示即：
$$
\large a_i + \sum_{j,k} (a_j-a_k)
$$


因此我们要判断最终黑板上能否写出 $k$，即判断 $\large a_i + \sum_{j,k} (a_j-a_k)=k$ 这个等式是否成立。

移项得：
$$
\large \sum_{j,k} (a_j-a_k)=k-a_i
$$
但是这样时间复杂度将达到 $O(n^2)$ 的量级，对于 $n \le 2 \times 10^5$ 显然不可以这样处理。

但其实我们直接求 $a_{i}-a_{i-1}$ 即可，因为 $a_{i}-a_{i-1}$ 通过线性组合可以表示出所有的 $a_j-a_{k}$。

令 $A_i=a_{i}-a_{i-1}$，于是等式可以转化为下述方程：
$$
\large x_2 \times A_2 + x_3 \times A_3 + \dots +x_{n} \times A_n=k-a_i
$$
其中 $x_i$ 表示对应项的系数。

关注 $\large x_2 \times A_2 + x_3 \times A_3 + \dots +x_{n} \times A_n$ 这个式子，不难想到裴蜀定理。

若方程有解即 $\gcd(A_2,A_3,\dots,A_n) \ |  \ k-a_i$。

至此问题便得到了解决，讲得很清楚了。



### 代码实现

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=2e5+5;
LL n,k;
LL a[N];
void solve(){
	cin>>n>>k;
	rep(i,1,n) cin>>a[i];
	LL d=0;
	rep(i,2,n){
		d=__gcd(d,abs(a[i]-a[i-1]));
	}
	rep(i,1,n) if((k-a[i])%d==0) return cout<<"YES",void();
	cout<<"NO";
}
```

---

## 作者：HappyJaPhy (赞：0)

# 题意
- 给出数列 $S=\{a_i\}$ 和整数 $k$，求是否能通过下面的操作使得 $k\in S$？
- 操作：选取 $x,y\in S$，将 $2x-y$ 加入 $S$ 中。

# 分析
- 观察操作可以发现，$2x-y$ 实际上就是数轴上 $y$ 关于 $x$ 的对称点，因此这个操作只与 $x$ 和 $y$ 在数轴上的相对位置有关，与具体位置（具体数值）无关。继续观察可以发现，如果 $0\in S$，那么就会有几个很好的性质：
1. 若 $x\in S$，那么 $n\cdot x\in S,n\in\mathbb{Z}$。
2. 若 $x,y\in S$，那么 $x+y\in S$。
- 为了可以利用这两条性质，我们可以将 $S$ 变化为 $S'=\{a_i-a_1\}$，并把 $k$ 减去 $a_1$（就相当于将数轴平移了）。此时 $0\in S'$，因此在无限次进行操作之后，得到的就是 $S'$ 的整线性组合 $S''=\{x|x=m\cdot\gcd(a_2,a_3,\cdots,a_n),m\in\mathbb{Z}\}$，判断 $k\in S''$ 即判断 $\gcd(a_2,a_3,\cdots,a_n)\mid k$，直接求解即可。

# AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n, k, a[N];

inline int read(int &x) {
	char ch = x = 0;
	int m = 1;
	while (ch < '0' || ch > '9') {
		ch = getchar();
		if (ch == '-') m *= -1;
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	x *= m;
	return x;
}

int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}

signed main() {
	int T;
	read(T);
	while (T--) {
		read(n), read(k);
		for (int i = 1; i <= n; i++) read(a[i]);
		sort(a + 1, a + 1 + n);
		for (int i = 2; i <= n; i++) a[i] -= a[1]; //平移数轴
		k -= a[1];
		if (k == 0) { //避免取余 k
			printf("YES\n");
			continue;
		}
		a[1] = 0;
		int g = a[2];
		for (int i = 3; i <= n; i++) g = gcd(g, a[i]); //求解 gcd
		if (k % g) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：wqst (赞：0)

大胆猜想，不要求证。

发现 $2x-y=x+x-y$，可以看做加上差。

而题目又对数的范围没有要求，感性理解一下，通过加加减减消去多余的东西我们可以任意操作差的个数。

根据裴蜀定理，只要 $\gcd|k$ 就可以构造，时间复杂度 $O(\sum n\log n+\sum\log x)$。

***code:***

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define For(i,x,y)for(i=x;i<=(y);i++)
ll a[200005];
ll read()
{
	ll A;
	bool K;
	char C;
	C=A=K=0;
	while(C<'0'||C>'9')K|=C=='-',C=getchar();
	while(C>'/'&&C<':')A=(A<<3)+(A<<1)+(C^48),C=getchar();
	return(K?-A:A);
}
ll gcd(ll _,ll __)
{
	return(!_?__:gcd(__%_,_));
}
int main()
{
	ll k,s;
	int t,n,i;
	t=read();
	while(t--)
	{
		n=read(),k=read();
		For(i,1,n)a[i]=read();
		sort(a+1,a+n+1);
		s=a[2]-a[1];
		For(i,2,n-1)s=gcd(s,a[i+1]-a[i]);
		For(i,1,n)
		if(!((a[i]-k)%s))break;
		puts((i>n?"NO":"YES"));
	}
	return 0;
}
```

---

