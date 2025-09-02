# Ralph And His Magic Field

## 题目描述

Ralph has a magic field which is divided into $ n×m $ blocks. That is to say, there are $ n $ rows and $ m $ columns on the field. Ralph can put an integer in each block. However, the magic field doesn't always work properly. It works only if the product of integers in each row and each column equals to $ k $ , where $ k $ is either 1 or -1.

Now Ralph wants you to figure out the number of ways to put numbers in each block in such a way that the magic field works properly. Two ways are considered different if and only if there exists at least one block where the numbers in the first way and in the second way are different. You are asked to output the answer modulo $ 1000000007=10^{9}+7 $ .

Note that there is no range of the numbers to put in the blocks, but we can prove that the answer is not infinity.

## 说明/提示

In the first example the only way is to put -1 into the only block.

In the second example the only way is to put 1 into every block.

## 样例 #1

### 输入

```
1 1 -1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 3 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 3 -1
```

### 输出

```
16
```

# 题解

## 作者：liuyi0905 (赞：8)

### [CF894B Ralph And His Magic Field](/problem/CF894B)
在一个 $n\times m$ 的矩阵里，填上 $n\times m$ 个数，使每行每列上的数的积都得 $k$，输出总方案数对 $10^9+7$ 取模后的结果。

由于 $k$ 的取值范围只有可能是 $1$ 或 $-1$，所以矩阵中的数也只可能是 $1$ 或者 $-1$。再来观察，发现前 $n-1$ 行和 $m-1$ 列，都是可以随便填数，只需最后一行和最后一列改变它的最终取值。

下面举个例子：

当 $n=6,m=6,k=1$ 时：

$\begin{matrix}1&-1&-1&1&-1\\-1&-1&-1&1&-1\\1&-1&1&-1&1\\1&-1&-1&1&-1\\-1&-1&1&-1&1\\\end{matrix}$

如果第 $i$ 行的乘积为 $x$，就在最后一个数填上 $\frac{k}{x}$，列也做同样处理。所以根据乘法原理，我们就知道一共有 $2^{(n-1)\times(m-1)}$ 种填法。

最后就只需判断无解的情况了，如果 $|n-m|$ 是奇数，且 $k=-1$，也就是说，最后只有一行或一列调整乘积，但就算填了，也不能保证它自己那一列或行满足条件，所以这种情况无解。

还得注意 $2^{(n-1)(m-1)}$ 的值会很大，计算中途就会超出，所以要用**快速幂**来做，有兴趣的读者可以自行查找一些资料。

最后展示一下代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,k;
int power(int a,int b){//快速幂模版
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;//如果指数为奇数，答案就与相乘
		a=a*a%mod,b>>=1;//将b不断除以二，a不断相乘
	}
	return ans;
}
signed main(){
	cin>>n>>m>>k;
	if(abs(n-m)%2&&!~k)puts("0");//特判无解的情况
	else cout<<power(power(2,n-1),m-1);//输出答案
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：2)

## CF894B Ralph And His Magic Field 题解
### 思路：
由于 $k$ 的值只能为 $1$ 或 $-1$，要想让乘积为 $1$ 或 $-1$，方格内就只能填 $1$ 或 $-1$，而 $-1$ 的作用为改变乘积的正负，所以，前面 $(n-1)\times (m-1)$ 个格子可以随便填，最后一行和最后一列翻转正负即可。在有解的情况下，根据 [乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447?fr=ge_ala) 可以得知答案为 $2^{(n-1)(m-1)}$。

那什么时候无解呢？当 $n$ 和 $m$ 一奇一偶并且 $k=-1$ 时无解，因为我们在填坐标为 $(n,m)$ 的格子时会同时影响行和列，就有可能无解。
### 技巧：
因为无论是奇数减偶数还是偶数减奇数得到的结果都是奇数，于是我们可以判断当 $|n-m|\bmod 2=1$ 时 $n$ 和 $m$ 一奇一偶。
### 代码:
```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
#define int long long
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int mod=1e9+7;
int qpow(int a,int b)//快速幂模板
{
	int ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
signed main()
{
	int n,m,k;
	n=read();
	m=read();
	k=read();
	if(abs(n-m)%2==1&&k==-1)
	{
	    cout<<0;
	}
	else 
	{
	    cout<<qpow(qpow(2,n-1),m-1);
	}
	return 0;
}

---

## 作者：Epoch_L (赞：1)

# 题解
观察数据范围，发现 $k$ 的值只为 $1$ 或 $-1$，所以每行填的数只能是 $1$ 或 $-1$，而 $-1$ 又可以直接改变当前乘积的符号，所以，在矩阵 $(n-1,m-1)$ 中，填 $1$ 或 $-1$ 均可，然后在最后一行和最后一列填上 $1$ 或 $-1$ 使其乘积等于 $k$ 即可。

根据乘法原理，最后的答案即为 $2^{(n-1)(m-1)}$。

前面讨论的是有答案的情况，那么现在我们来讨论无解的情况，不难发现，当 $n$ 和 $m$ 为一奇一偶，且 $k=-1$ 时，无解，因为当我们在填最后一行和最后一列时，最右下角的数既会影响行也会影响列，所以有可能无解，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xc74y20g.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

此时 $k=-1$，无解。

# 注意
我们计算答案时要用两次乘方算，因为 $(n-1)(m-1)$ 会爆long long，由于指数较大，还要用到快速幂。

# Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
const int mod=1e9+7;
int get(int a,int b)//快速幂
{
	int ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
main()
{
	int n,m,k;
	read(n);
	read(m);
	read(k);
	if(abs(n-m)%2==1&&k==-1)cout<<0;//无解
	else cout<<get(get(2,n-1),m-1);
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

一发中最优解祭。

因为 $k=1/-1$，所以往里面填的整数一定是 $1/-1$。

我们可以左上 $(n-1)\times(m-1)$ 个格子乱填，最后一行或者一列用 $1/-1$ 翻转正负性即可，这个时候每行每列的最后一个元素是一定的。

所以一共 $2^{(n-1)(m-1)}$ 种方案。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace mystd {
	inline int read() {
	    int w = 1, q = 0;
	    char ch = ' ';
	    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	    if (ch == '-') w = -1, ch = getchar();
	    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
	    return w * q;
	}

	inline void write(int x) {
	    if (x < 0) {
	        x = ~(x - 1);
	        putchar('-');
	    }
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace mystd;

const int mod = 1e9 + 7;
int n, m, k;

int ksm(int p, int q) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod;
		q >>= 1;
	}
	return res;
}

signed main() {
	n = read();
	m = read();
	k = read();
	if (k == -1 && abs(n - m) % 2 == 1) puts("0"), exit(0);
	write(ksm(ksm(2, n - 1), m - 1));
	return 0;
}

```

---

## 作者：nofind (赞：1)

题意:https://www.luogu.org/problem/CF894B

结论题,发现一行/列的正负性只与最后一个数有关,因此方案数就是去掉最后一行和最后一列后随意摆放的方案数

需要判断无解:

当n和m一奇一偶并且k=-1时无解

不妨设n为奇数,m为偶数,那么从行来看每一行要有奇数个-1,此时-1的总数为偶数(奇数乘奇数为偶数),但是从列来看每一列要有奇数个-1,此时-1的总数为奇数(偶数乘奇数为奇数),相互矛盾

code:
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1000000007;
ll n,m,K;
inline ll power(ll x,ll k)
{
	ll res=1;
	while(k)
	{
		if(k&1)res=(res*x)%mod;
		x=(x*x)%mod;k>>=1;
	}
	return res%mod;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&K);
	if(K==-1&&((n+m)&1))puts("0");
	else printf("%lld",power(power(2LL,n-1),m-1)%mod);
	return 0;
} 
```




---

## 作者：Inker (赞：1)

由题意知：每个位置只有整数，k=1或-1，所以每个位置只有两种选择，即1或-1.

考虑若在每一行选出一行先不放，本行其余格子便可随便放，最后由这个格子调节正负，这是一定可行的，所以一行的方案数就是2的列数-1次方。

同理列也可以留一行调节，但有一种情况不合法，那就是行数加列数是一个奇数，此时若k=-1时，将必有一行或一列无法调为-1，所以方案数为0.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int mod = 1e9+7;
int k;
typedef long long dnt;
int mpow(int a,dnt b){
    int c=1;
    for(;b;b>>=1,a=1ll*a*a%mod){
        if( b & 1 ) c = 1ll*c*a%mod;
    }
    return c;
}
int main()
{
    dnt n,m;
    scanf("%lld%lld%d",&n,&m,&k);
    if((n+m)&1){
        if(k==-1){
            printf("0\n");return 0;
        }
    }
    int tmp=mpow(2,n-1)//防n*m爆long long，分开算。
    printf("%d\n",mpow(tmp,m-1));
    return 0;
}
```

---

## 作者：Hutao__ (赞：0)

## 思路
很明显，答案为 $2^{(n-1)(m-1)}$。
## 证明
对于每一个矩阵，很明显乘积不与前 $n-1$ 行和前 $m-1$ 列无关，因为改变这些地方的数据只会影响乘积的正负性，都可以改变第 $n$ 行和第 $m$ 列来改变正负性。

需要注意的是，当 $n$ 与 $m$ 的差为奇数且 $k \lt  0$ 时，要输出无解，因为这时你改变 ${(n,m)}$ 时，可能会同时改变一行一列的值。

## 代码

```cpp
//lgRMJ坏了，不保证此代码能通过本题
#include<bits/stdc++.h>
using namespace std;
const int K=1e9+7;
int n,m,k;
long long qpow(int x,int y){
	if(x==1||y==0){
		return 1;
	}
	long long t=qpow(x,y/2)%K;
	if(y&1){
		return (t*t*x)%K;
	}
	return (t*t)%K;
}
int main(){
	cin>>n>>m>>k;
	if(abs(n-m)%2==1&&k==-1)cout<<0;
	else cout<<qpow(qpow(2,n-1),m-1);
}
```

---

## 作者：saikrilll (赞：0)

做法：


1. 如果 $n$，$m$ 奇偶性不同，且 $k=-1$ 时，输出 $0$。
1. 否则考虑先任意枚举前 $n-1$ 行，前 $m-1$ 列的情况为 $2^{(n-1)(m-1)}$，其余位置填能使当前行或列乘积为 $-1$ 数，可以确定这些格子的填法被唯一确定。


对于上述第一种情况为何答案为 $0$？不妨看一组例子：


$n=5$，$m=4$，$k=-1$，假设我们当前前 $n-1$ 行，前 $m-1$  列的选择情况为：


| 1 | -1 | 1 |
| -----------: | -----------: | -----------: |
| -1 | 1 | -1 |
| -1 | -1 | -1 |
| 1 | 1 | -1 |


设乘积数列 $b_i$ 为 $\prod_{j=1}^{n-1} \ a_{j,i}$，$c_i$ 为 $\prod_{j=1}^{m-1} \ a_{i,j}$，则 $b=1,1,-1$, $c=-1,1,-1,-1$，由于矩阵先行乘再列乘与先列乘再行乘所得乘积一致，即意味着 $\prod_{i=1}^{m-1} \ b_i = \prod_{i=1}^{n-1} \ c_i$，而数组内元素只可能为 $-1$ 或 $1$，因此 $b_i$ 与 $c_i$ 内 $-1$ 的个数奇偶性相同，而我们要按第二种构造方式构造完成的矩阵为：


| 1 | -1 | 1 | 1 |
| -----------: | -----------: | -----------: | -----------: |
| -1 | 1 | -1 | -1 |
| -1 | -1 | -1 | 1 |
| 1 | 1 | -1 | 1 |
| -1 | -1 | 1 |  |


不难发现，$a_{n,i}=-b_{i}$，$a_{i,m}=c_{i}$，也就是填入的数等于恰好等于乘积数组的相反数，又因为 $b_i$ 与 $c_i$ 内 $-1$ 的个数奇偶性相同，由此可得 $a_{n,1}$ 到 $a_{n,m-1}$ 内 $-1$ 个数与 $a_{1,m}$ 到 $a_{n,m}$ 内 $-1$ 个数的差的奇偶性与 $|n-m|$ 的奇偶性相同，是奇数。


由此可得 $\prod_{i=1}^{m-1} \ a_{n,i}=- \prod_{i=1}^{n-1} \ a_{i,m}$，也就是：$a_{n,m}$ 无论填任何数，都有上述关系式成立，即第 $n$ 行与第 $m$ 列始终不同，也就违背了构造要求。由此情况1答案为 $0$。


本题代码：
```c
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll modd=1e9+7;
ll n,m; int k;

ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%modd;
		x=x*x%modd; y>>=1;
	}
	return res;
}
int main(){
	cin>>n>>m>>k;
	if(abs(n-m)%2==1&&k==-1)cout<<0;
	else{
		ll p=qpow((ll)2,n-1);
		cout<<qpow(p,m-1);
	}
	return 0;
} 
```

---

## 作者：DANIEL_x_ (赞：0)

## 思路：

不管前面 $(m-1) \times (n-1)$ 怎么放， 在最后一行或者最后一列可以摆放 $-1,1$，以达到正负性的要求。

所以只要答案不是无解，答案个数就是 $2^{(m-1) \times (n-1)}$ 个。

但是注意，一定要用快速幂，不能普通乘法。

无解情况：在 $k=-1$ 且 $n,m$ 一奇一偶的情况会无解。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int ksm(int a, int b, int p)
{
    a %= p;
    int ans = 1;
    while (b > 0)
    {
        if (b & 1)
            ans = (ans * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ans % p;
}
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    if (k == -1 && (n + m) % 2)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << ksm(2, ((n - 1) % (mod - 1)) * ((m - 1) % (mod - 1)), mod);
    }
}
signed main()
{
	solve();
	return 0;
}
```


---

## 作者：Hexarhy (赞：0)

### Preface

适合新手（指我）的计数题。

### Solution

其实想到核心就很简单了：**一行/列的正负号可以只由一个格子决定。** 于是我们可以保留最后一行和最后一列来调整结果，剩余的格子只需要在 $\pm 1$ 里随便选就好了。

因此答案就是：

$$2^{(n-1)(m-1)}$$

当然得分开成 $(2^{n-1})^{m-1}$ 算，指数会爆 `long long`，而且别算成了 $2^{n-1}\times 2^{m-1}$。

**但是**，最右下角的格子需要同时调整一行和一列的正负性，因此可能会出现无解的情况。手玩一下不难发现，当满足 $|n-m|$ 是奇数的时候，矩阵一定不能满足 $k=-1$，输出 $0$ 即可。

### Code

```cpp
int main()
{
	cin>>n>>m>>k;
	if(abs(n-m)&1 && k==-1)	ans=0;
	else	ans=qpow(qpow(2,n-1),m-1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：hao_zi6366 (赞：0)

## 题目分析
由题意可知：我们可以把棋盘分成 2 个部分：
![](https://cdn.luogu.com.cn/upload/image_hosting/503nqphj.png)


显然，在可以随便填的区域中存在 $2^{(m-1)(n-1)}$ 种情况，接着我们可以通过更改最后一行和最后一列来达到题目的要求。

但当 $k = 1$ 且 $m$，$n$ 的奇偶性不同时，存在无解情况，特判即可。

注意：由于题目中的值较大，要使用快速幂来完成计算。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define inf 0x7fffffff
typedef long long ll;

const long long p=1e9+7;	//模数
ll quickPow(ll a,ll b){		//快速幂
	ll res=1;
	while(b){
		if(b%2)res=(res*a)%p;
		a=(a%p*a%p)%p;
		b/=2;
	}
	return res;
}

int main(){
	/*freopen("xxx.in","r",stdin);
	freopen("xxx.out","w",stdout);*/
	std::ios::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);

    ll n,m,k;
    std::cin>>n>>m>>k;
    if(k==-1 && n%2!=m%2)std::cout<<0;	//特判无解
    else if(n<2 || m<2)std::cout<<1;	//特判只有一种解
    else std::cout<<quickPow((quickPow(2,n-1))%p,m-1)%p;	//计算答案
	return 0;
}
```

---

## 作者：shengheng (赞：0)

## 题意

Ralph 在他的 $n\times m$ 大小的魔法田地里。要在每个田格里填上一个整数并且使得每行每列的数的乘积都为 $k$。要输出总方案数取余 $10^9 +7$ 的结果。而且保证 $k$ 为 $1$ 或 $-1$！

## 思路

> 保证 $k=1$ 或者 $-1$。

那么矩阵的数也只会是 $1$ 或 $-1$。所以，在矩阵 $(n-1 , m-1)$ 中，$1$ 或 $-1$ 随便填。只在最后一行最后一列填上 $1$ 或者 $-1$，使总乘积为 $k$ 就可以了。

> 乘法原理：做一件事，完成它需要分成 $n$ 个步骤，做第一步有 $m_1$ 种不同的方法，做第二步有 $m_2$ 种不同的方法……做第 $n$ 有 $m_n$ 种不同的方法。那么完成这件事共有 $m_1 \times m_2 \times$……$\times m_n$ 种方法。

据乘法原理，一共 $2^{(n-1)(m-1)}$ 种。

**若 $|n-m|$ 不为偶数，且 $k$ 为 $-1$，无解。因为在调点 $(n,m)$ 时，同时影响行列。**

答案可能极大，所以快速幂是不可以少的。

## 代码

```cpp
#include<bits/stdc+++.h>
#define int long long//见祖宗啊！！！
using namespace std;
const int mod=1e9+7;//模的数
int n,m,k;
int pow(int a,int b){//这是快速幂，定“pow”没事
    int ans=1;//初始化1
    while(b){
        if(b%2==1)ans=ans*a%mod;//如果b为奇数，ans就乘
        a=a*a%mod;
        b*=2;
    }return ans;
}signed main(){
	ios::sync_with_stdio(false);//cin黑科技
	cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    if(abs(n-m)%2==1&&!~k)cout<<0;//无解
    else cout<<pow(pow(2,n-1),m-1);
    return 0;
}
```


---

