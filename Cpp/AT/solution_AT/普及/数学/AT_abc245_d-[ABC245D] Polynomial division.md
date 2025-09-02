# [ABC245D] Polynomial division

## 题目描述

现在有 $N$ 次多项式 $A（x）=A_Nx^N+A_{N-1}x^{N-1}+\cdots\ +A_1x+A_0$ 和 $M$ 次多项式 $B(x)=B_Mx^M+B_{M-1}x^{M-1}+\cdots\ +B_1x+B_0$。

其中，$A(x)、B(x)$ 中的每个系数都是绝对值小于等于 $100$ 的整数，并且最高的下一个系数不是 $0$。

定义它们的积为 $C(x)=A(x)B(x)=C_{N+M}x^{N+M}+C_{N+M-1}x^{N+M-1}+\cdots\ +C_1x+C_0$。

已知 $A_0,A_1,\ldots,\ A_N$ 和 $C_0,C_1,\ldots,\ C_{N+M}$，请求出 $B_0,B_1,\ldots,\ B_M$。

输入保证只有一种 $B_0,B_1,\ldots,\ B_M$。

## 说明/提示

- $ 1\leq N<100 $

- $ 1\leq M<100 $

- $ |A_i|\leq100 $

- $ |C_i|\leq10^6 $

- $ A_N\neq0 $

- $ C_{N+M}\neq0 $

- 满足条件的 $B_0,B_1,\ldots,\ B_M$ 只有一个

## 样例 #1

### 输入

```
1 2
2 1
12 14 8 2```

### 输出

```
6 4 2```

## 样例 #2

### 输入

```
1 1
100 1
10000 0 -1```

### 输出

```
100 -1```

# 题解

## 作者：wjr_jok (赞：2)

就一大除法。

用 $C$ 数组的每位除以 $A$ 数组的常数项，因为保证有解，所以只需要一直除，每次除法记得将所有影响到的项一起处理即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[101],b[101],c[201];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n+1;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n+m+1;i++){
		cin>>c[i];
	}
	for(int i=1;i<=m+1;i++){//从最后一位开始除
		b[m-i+2]=c[n+m-i+2]/a[n+1];
		for(int j=1;j<=n+1;j++){//更改除到的每一项
			c[n+m-i-j+3]-=b[m-i+2]*a[n-j+2];
		}
	}
	for(int i=1;i<=m+1;i++){
		cout<<b[i]<<" ";
	}
	return 0;
} 
```

---

## 作者：run_away (赞：2)

## 题意

给定多项式 $A$ 和 $C$，求 $C$ 除以 $A$ 的结果 $B$。

## 分析

先考虑用 $a_i$ 和 $b_j$ 表示 $c_{i+j}$，多项式乘法的朴素方法是把两式的每一位都乘起来，最后相加。

具体形式为

$$
\begin{array}{c}
c_{n+m}=a_{n}b_{m}\\
c_{n+m-1}=a_{n}b_{m-1}+a_{n-1}b_{m}\\
c_{n+m-2}=a_{n}b_{m-2}+a_{n-1}b_{m-1}+a_{n-2}b_{m}\\
\vdots\\
c_{0}=a_{0}b_{0}
\end{array}
$$

这串式子看起来没什么用，但仔细观察可以发现，其中 $a_i$ 和 $c_i$ 都是已知的，而后一个式子只比前一个多了一个未知数 $b_i$。如果我们知道 $b_{i+1}\sim b_{m}$ 的值，就可以求出 $b_{i}$。

带入式子，直接递推即可。事实上因为求的是 $B$，只需要循环到 $c_n$。

时间复杂度大概是 $O(n^2)$，可过。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll mod=1e9+7,maxn=4e5+5,maxt=505;
ll n,m,a[maxn],b[maxn],c[maxn];
inline void solve(){
    n=read(),m=read();
    for(ll i=0;i<=n;++i)a[i]=read();
    for(ll i=0;i<=n+m;++i)c[i]=read();
    for(ll i=n+m;i>=n;--i){
        ll sum=0;
        for(ll j=n-1;i-j<=m;--j){
            sum+=a[j]*b[i-j];
        }
        b[i-n]=(c[i]-sum)/a[n];
    }
    for(ll i=0;i<=m;++i)printf("%lld ",b[i]);
}
signed main(){
    ll t=1;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：1)

### 题意
有两个多项式 $A(x),B(x)$，其中 $A(x) = a_n x^n +a_{n-1}x^{n-1}+ \dots +a_1x+a_0$，$B(x) = b_m x^m +b_{m-1}x^{m-1}+ \dots +b_1x+b_0$。       
又有一个多项式 $C(x) = c_{n+m} x^{n+m} +c_{n+m-1}x^{n+m-1}+ \dots +c_1x+c_0$，它是由 $A(x)$ 和 $B(x)$ 相乘得到的。        
现给定 $a_0,a_2,\dots a_n$ 以及 $c_0,c_1,\dots c_{n+m}$
，求 $b_0,b_1,\dots b_m$。      
数据范围：
- $1 \le n < 100,1 \le m < 100$
- $|a_i|\le 100(0 \le i \le n),|c_i|\le 10^6(0 \le i \le n+m)$
- $a_n \neq 0,c_{n+m}\neq 0$

### 思路  
这个 $n$ 和 $m$ 都很小，所以直接暴力模拟。   
![](https://cdn.luogu.com.cn/upload/image_hosting/m4a4adj7.png)     
首先，所以通过 $a_{n}$ 和 $c_{n+m}$ 可以直接求出 $b_m=c_{n+m} \div a_n$。再把 $b_m$ 与 $A(x)$ 的各项相乘，作为我们得到的第一个式子，写在 $C(x)$ 的下面，与 $C(x)$ 的最高位对齐。   
可以类比为竖式除法，常数项是个位，一次项是十位，二次项是百位，以此类推。        
![](https://cdn.luogu.com.cn/upload/image_hosting/o5f0qlq7.png)      
把减掉的差写下来。此时最高位已被消除，所以写下来的共有 $m-1$ 项。      
继续重复上面的过程。由于我们的首要任务是消掉当前写下的式子的最高位，所以除出的商应以最高位为基准。   
![](https://cdn.luogu.com.cn/upload/image_hosting/la4wg2ob.png)      
直至除到最后一位为止。由于题面告诉我们 $B(x)$ 的系数是唯一的，所以不用考虑是否会有余数等各种七七八八的情况。        
### 代码
不开 long long 会见祖宗，我就是因为没开 long long 导致校内模拟赛由 $100$ 分挂成了 $75$ 分。
```cpp
#include<stdio.h>
long long n,m,a[105],b[105],c[105];
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=0;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=0;i<=n+m;i++) scanf("%lld",&c[i]);
    b[m]=c[n+m]/a[n];//求出最高位
    for(int i1=m-1,i2=n+m-1;i1>=0;i1--,i2--)
    //依次从高位往低位求商
    {
        long long num=c[i2];
        for(int j=i1+1;j<=m;j++) num-=b[j]*a[i2-j];
        //前面的商会与除数产生一些在当前数位上的量，
        //需要把它减掉，剩下的才是当前数位的商需要处理的最终量
        b[i1]=num/a[n];//以除数的最高位来处理
    }
    for(int i=0;i<=m;i++) printf("%lld ",b[i]);
}
```

---

## 作者：BLuemoon_ (赞：1)

## [ABC245D] Polynomial division

就是一个~~大模拟~~小模拟。。。

### 前置芝士：整式大除法

顾名思义，就是小学学过的竖式除法 ~~（虽然作者也还是在读 xxs）~~，只是加了字母。

例：$(x^3+5x^2+6x+8) \div (x+4)$

Step $0$： 把被除式和除式[降幂排列](https://baike.baidu.com/item/%E9%99%8D%E5%B9%82%E5%BC%8F/18881128?fr=aladdin)，这里已经排好。

Step $1$： 列竖式，真的只是列竖式。

![](https://cdn.luogu.com.cn/upload/image_hosting/rws42ex5.png)

Step $2$： 除式为两项，所以第一次取被除式前两项，$(x^3+5x^2) \div (x+4) = (x^2+4x^2)\cdots(x^2)$，商 $x^2$，余 $x^2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/t5tkt4yo.png)

Step $3$： 将 $6x$ 落下来。取被除式二、三项，$(x^2+6x) \div (x+4) = (x)\cdots(2x)$，商 $x$，余 $2x$。

![](https://cdn.luogu.com.cn/upload/image_hosting/u0monyhz.png)

Step $4$： 将 $8$ 落下来。取被除式最后两项，$(2x+8) \div (x+4) = (2)\cdots(0)$，商 $2$，余 $0$。除尽。

![](https://cdn.luogu.com.cn/upload/image_hosting/614k28ca.png)

好了，关于大除法的讲解就到这里，接下来开始看题。

+ 给定因式和积式，求另一个因式。

小学学过，当 $ab=c$ 时，$b=\frac{c}{a}$。所以，答案就是 $\frac{C(x)}{A(x)}$。然后就是大除法。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[205],b[205],c[205];
int main() 
{
  cin>>n>>m;
  for(int i=0;i<=n;i++)
    cin>>a[i];
  for(int i=0;i<=n+m;i++)
    cin>>c[i];
  for(int i=m;i>=0;i--) 
  {
    b[i]=c[i+n]/a[n];
    for(int j=0;j<=n;j++)
      c[i+j]-=b[i]*a[j];
  }
  for(int i=0;i<=m;i++)
    cout<<b[i]<<" ";
  cout<<"\n";
  return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/6jga7wef.png)

看在这个运势的份上，管理大大给个过吧。

---

## 作者：smartdevil (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc245_d)
## 题意：

给你多项式 $A$ 和 $C$，求相除的代数式 $B$。

## 思路：

大除法，[来自前辈的优质解析](https://blog.csdn.net/qq_37424623/article/details/121446565)。

## 正解：

套上多项式除法板子直接模拟就行，注意判断 $0$ 的情况。这题就结束了。

最后还要注意输出要按降幂排列。

---

## 作者：zcr0202 (赞：0)

## 题目大意

给你两个多项式的系数，求它们两个的商。

## 解题思路

前置知识：[多项式除法](https://blog.csdn.net/qq_37424623/article/details/121446565)。

按照多项式的除法直接模拟即可。

## Code

```
#include<bits/stdc++.h>
#define int long long
#define ready() ios::sync_with_stdio(0), cout.tie(0), cout.tie(0);
#define fre(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout);
#define up(i, a, b) for(int i = a; i <= b; i++)
#define down(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 5e5 + 5;
const int mod = 1e9 + 9;
int n, m;
int a[N], b[N], c[N];
signed main() {
    ready();
    cin >> n >> m;
    up(i, 0, n) {
        cin >> a[i];
    }
    up(i, 0, n + m) {
        cin >> c[i];
    }
    down(i, m, 0) {
        b[i] = c[i + n] / a[n];
        down(j, n, 0) {
            c[i + j] -= b[i] * a[j];
        }    
    }
    up(i, 0, m) {
        cout << b[i] << " ";
    }
    return 0;
}
```

---

## 作者：Anby_ (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/AT_abc245_d)。
### 思路
模拟大除法。  
### 大除法
首先，你得知道什么是多项式。  
#### 多项式的定义
- 线性空间 $V$ 上的 $k$ 次多项式为函数 $p\to V:\mathbb{R}$，且若 $\omega_1...\omega_n$ 为 $V*$ 的基，则存在 $a_{i_1}...a_{i_k}\in\mathbb{R}$。
- 对任意 $v\in V$有$p(v)=\displaystyle \sum_{j=1}^{k}a_{i_j}\omega^{i_j}(v)$。  
- ~~好像没学过多项式的应该看不懂吧~~。  

人话就是一个数列 $P$，满足 $P(x)=a_{n}x^{n}+a_{n-1}x^{n-1}+...+a_{2}x^{2}+a_{1}x+a_0$，则称它为**多项式**。
#### 大除法
简单的定义一下：
$\frac{A(x)}{B(x)}=C(x)+D(x)$，其中 $A(x)$ 被称为被除式，$B(x)$ 被称为除式，$C(x)$ 被称为商式，$D(x)$ 被称为余式。     
大除法的用途就是**列竖式计算多项式除法**。   
大除法就是依次找到**余项**最高项，将除式乘以最高项的系数再乘以余项最高项的次数与除式最高项次数的差。再与**乘过之后的余项做差**，形成新的余项。直接用文字讲十分的枯燥与乏味，于是我将放几张图片方便理解。   
比方说，我们要计算 $(2x^4+7x^3+8x^2+3x)\div(x^2+2x+1)$ 的值，我们就可以用大除法。
![](https://cdn.luogu.com.cn/upload/image_hosting/1grz7k23.png)

### 正解
已知多项式 $A(x)$ 和多项式 $C(x)$，让你求多项式（也可能是一项）$B(x)$ 的值。  
通过题目描述可以知道，多项式（也可能是单项式） $B(x)=\frac{A(x)}{C(x)}$，于是乎，题目就变成的模拟大除法。
### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=1e6+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*
5 6
1 1 4 5 1 4
2 1 9 8 4 5 1 2 2 3 4 0
*/
ll a[N],c[N],b[N],yushi[N],n,m;
int main(){
	cin>>n>>m;
	for(int i=n;i>=0;i--)scanf("%lld",a+i);
	for(int i=n+m;i>=0;i--)scanf("%lld",c+i);
	for(int i=0;i<=m;i++){
		ll sum=0;
		for(int j=i;j>=1;j--)sum+=a[j]*b[i-j];
		b[i]=(c[i]-sum)/a[0];
	}
	for(int i=m;i>=0;i--) printf("%lld ",b[i]);
	return 0;
}

```

---

## 作者：RainCQwQ (赞：0)

# ABC245D Solution
## 思路整理
这一道题主要考察多项式的除法运算（类似高精）。

我们的多项式除法就像正常的除法竖式，其他题解中已经详细讲解了这一个知识点，这里便不再累赘，就放一个百度百科链接吧：[Link](https://baike.baidu.com/item/%E5%A4%9A%E9%A1%B9%E5%BC%8F%E9%99%A4%E6%B3%95/2703247)。

然后可以想到，从最高位开始（当然，你如果从最低位也行），每次将第 $j$ 位减少 $a_j \times \Large{\frac{c_{i+N}}{a_N}}$（$i$ 是此时计算的 $b$ 数组的下标，$0 \le i \le M$；$0 \le j \le N$），$b_i = \Large{\frac{c_{i+N}}{a_N}}$。

## Code
```cpp
#include <iostream>
using namespace std;
#define MAXN 205
int a[MAXN],b[MAXN],c[MAXN];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n;i++) cin>>a[i];
	for(int i=0;i<=n+m;i++) cin>>c[i];
	for(int i=m;i>=0;i--)
	{
		b[i]=c[i+n]/a[n];
		for(int j=n;j>=0;j--)
			c[i+j]-=b[i]*a[j];
	}
    for(int i=0;i<=m;i++) cout<<b[i]<<" ";
	return 0;
}
```

---

## 作者：caiyuyang (赞：0)

这道题就是一个小模拟，但有很多细节需要注意，我调了整整 1 个半小时（或许是我太蒻了罢）

## 题意简述

依题意，有三多项式：

$$
A(x)=A_Nx^N+A_{N-1}x^{N-1}+\cdots\ +A_1x+A_0 \\
B(x)=B_Mx^M+B_{M-1}x^{M-1}+\cdots\ +B_1x+B_0 \\
C(x)=A(x)B(x)=C_{N+M}x^{N+M}+C_{N+M-1}x^{N+M-1}+\cdots\ +C_1x+C_0
$$

已知 $A(x)$，$C(x)$，求 $B(x)$

## 思路简述

即模拟多项式的除法的竖式，如图（以例一为例）：
![example](https://cdn.luogu.com.cn/upload/image_hosting/tziuhlpy.png)

通过观察可以发现，这道题的多项式除法是由以下步骤组成的：

1. 把被除式（$C(x)$）、除式（$A(x)$）按 $x$ 降幂排列；
2. 用当前被除式的第一项除以除式第一项，得到商式的第 $n$ 项；
3. 用商式第 $n$ 项乘以除式，像普通竖式乘法一样对齐，并相减；
4. 把减得的差当作新的被除式，再回到第 1 步，直到余式为零。

看不懂的可以借助图片理解。

## 重点注意

**一定**要按**降幂**排列（我就是因为这个卡了 1.5 个小时）

## ACode
```cpp
#include <cstdio>
#include <vector>

using namespace std;

int a[210], c[210]; /* A(x) 与 C(x) 的系数 */
vector<int> b;

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);

	for (int i = 0, x; i <= n; ++i)
		scanf("%d", &x), a[i] = x;
	for (int i = 0, x; i <= n + m; ++i)
		scanf("%d", &x), c[i] = x;
	
	for (int i = 0; i <= n / 2.0 - 0.5; ++i) /* 翻转数组a，c。因为输入是升幂排列的，要换成降幂 */
		swap(a[i], a[n - i]);
	for (int i = 0; i <= (n + m) / 2.0 - 0.5; ++i)
		swap(c[i], c[n + m - i]);
	
	for (int top = 0; top <= n + m; ++top) /* 主体部分，前文有讲，不做解释 */
	{
		int tmp = c[top] / a[0];
		b.push_back(tmp);
		for (int j = 0; j <= n && j + top <= n + m; ++j)
			c[j + top] -= a[j] * tmp;
	}
	while (!b.empty() && b.size() > m + 1) /* 防止后接零（形如100 -1 0） */
		b.pop_back();
	for (vector<int>::reverse_iterator i = b.rbegin(); i != b.rend(); ++i) /* 翻转输出（输入是升幂排列，而当前是降幂排列） */
		printf("%d ", *i);
	return 0;
}
```

---

## 作者：Superiority (赞：0)

# 思路

很显然可以发现此题为一个模拟，思考一下为什么是模拟？

通过定义 $C(x)=A(x)B(x)=C_{N+M}x^{N+M}+C_{N+M1}x^{N+M-1}+\cdots\ +C_1x+C_0$ 可以很显然的看出 $B(x)=C(x) \div A(x)$。接下来考虑如何计算这个 $C(x) \div A(x)$，有定义知 $A(x)=A_Nx^N+A_{N-1}x^{N-1}+\cdots\ +A_1x+A_0,C(x)=C_{N+M}x^{N+M}+C_{N+M1}x^{N+M-1}+\cdots\ +C_1x+C_0$ 很明显这是两个多项式，多项式相除可以直接模拟大除法，不会的小朋友[戳这里](https://baike.baidu.com/item/%E5%A4%9A%E9%A1%B9%E5%BC%8F%E9%99%A4%E6%B3%95/2703247?fromtitle=%E5%A4%A7%E9%99%A4%E6%B3%95&fromid=7844493&fr=aladdin)。

- 下标从 $0$ 开始。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define zjj long long
const int MAXN=1e6+5;//by cqbzbbd
int n,m;
int a[MAXN],b[MAXN],c[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=0;i<=n;i++){
		cin>>a[i];
	}
	for(int i=0;i<=n+m;i++){
		cin>>c[i];
	}
	for(int i=m;i>=0;i--) {
		b[i]=c[i+n]/a[n];
		for(int j=0;j<=n;j++)
			c[i+j]-=b[i]*a[j];
	}
	for(int i=0;i<=m;i++) cout<<b[i]<<" ";
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

题意：有三个多项式 $ A,B,C $，满足 $ A \times B=C $，现在给定 $ A,C $，求 $ B $。

因为本题数据范围很小所以实际上 $ \mathcal{O}(n^2) $ 时间复杂度的高精度除法可以通过，但我不会写高精度除法，于是套上了多项式除法板子。

多项式除法可以在 $ \mathcal{O}(n\log{n}) $ 的时间复杂度内求出两个多项式相除的结果，可以参考 [多项式除法](https://www.luogu.com.cn/problem/P4512)。

套上多项式除法板子之后注意负数和系数中出现零的情况特殊判断即可。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
#define LL long long
LL in() 
{
	char ch; LL x = 0, f = 1;
	while(!isdigit(ch = getchar()))(ch == '-') && (f = -f);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
	return x * f;
}
const int maxn = 4e5 + 10;
const long long mod = 998244353;
int len, r[maxn];
using std::vector;
LL ksm(LL x, LL y) 
{
	LL re = 1LL;
	while(y) 
	{
		if(y & 1) 
		re = re * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return re;
}
void FNTT(vector<int> &A, int flag) 
{
	A.resize(len);
	for(int i = 0; i < len; i++) 
	if(i < r[i]) 
	std::swap(A[i], A[r[i]]);
	for(int l = 1; l < len; l <<= 1) 
	{
		int w0 = ksm(3, (mod - 1) / (l << 1));
		for(int i = 0; i < len; i += (l << 1)) 
		{
			int w = 1, a0 = i, a1 = i + l;
			for(int k = 0; k < l; k++, a0++, a1++, w = 1LL * w * w0 % mod) {
				int tmp = 1LL * A[a1] * w % mod;
				A[a1] = ((A[a0] - tmp) % mod + mod) % mod;
				A[a0] = (A[a0] + tmp)  % mod;
			}
		}
	}
	if(!(~flag)) 
	{
		std::reverse(A.begin() + 1, A.end());
		int inv = ksm(len, mod - 2);
		for(int i = 0; i < len; i++) A[i] = 1LL * A[i] * inv % mod;
	}
}
vector<int> operator - (const vector<int> &A, const vector<int> &B)
{
	vector<int> ans;
	for(int i = 0; i < (int)std::min(A.size(), B.size()); i++) ans.push_back(A[i] - B[i]);
	if(A.size() < B.size()) for(int i = A.size(); i < (int)B.size(); i++) ans.push_back(-B[i]);
	if(A.size() > B.size()) for(int i = B.size(); i < (int)A.size(); i++) ans.push_back(A[i]);
	return ans;
}
vector<int> operator * (vector<int> A, vector<int> B) 
{
	int tot = A.size() + B.size() - 1;
	for(len = 1; len <= tot; len <<= 1);
	for(int i = 0; i < len; i++) 
	r[i] = (r[i >> 1] >> 1) | ((i & 1) * (len >> 1));
	FNTT(A, 1), FNTT(B, 1);
	vector<int> ans;
	for(int i = 0; i < len; i++) ans.push_back(1LL * A[i] * B[i] % mod);
	FNTT(ans, -1);
	ans.resize(tot);
	return ans;
}
vector<int> inv(const vector<int> &A) 
{
	if(A.size() == 1) 
	{
		vector<int> ans;
		ans.push_back(ksm(A[0], mod - 2));
		return ans;
	}
	int n = A.size(), _ = (n + 1) >> 1;
	vector<int> ans, B = A;
	B.resize(_);
	ans.push_back(2);
	B = inv(B);
	ans = B * (ans - A * B);
	ans.resize(n);
	return ans;
}
vector<int> rev(const vector<int> &A) 
{
	vector<int> B = A;
	std::reverse(B.begin(), B.end());
	return B;
}
void work(vector<int> f, vector<int> g) 
{
	int n = f.size() - 1, m = g.size() - 1;
	vector<int> ff = rev(f), gg = rev(g), s, y;
	ff.resize(n - m + 1), gg.resize(n - m + 1);
	s = ff * inv(gg);
	s.resize(n - m + 1);
	s = rev(s);
	vector<int> v = g * s;
	v.resize(m), f.resize(m), y.resize(m);
	for(int i = 0; i < m; i++) 
	y[i] = ((f[i] - v[i]) % mod + mod) % mod;
	for(int i = 0; i < n - m + 1; i++) 
    if(s[i]>=0&&s[i]<=9.9e8)
	printf("%d ", s[i]);
    else if(s[i]<0)
    printf("%d ", s[i]+mod);
    else
    printf("%d ", s[i]-mod);
}
int main() 
{
	int n = in(), m = in();
    m=n+m;
	vector<int> a, b;
	for(int i = 0; i <= n; i++) 
	a.push_back(in());
	for(int i = 0; i <= m; i++) 
	b.push_back(in());
    swap(a,b);
	work(a, b);
}
```


---

