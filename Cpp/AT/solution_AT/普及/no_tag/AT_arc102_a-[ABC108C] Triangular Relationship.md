# [ABC108C] Triangular Relationship

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc108/tasks/arc102_a

整数 $ N,K $ が与えられます。$ N $ 以下の正の整数の組 $ (a,b,c) $ であって、$ a+b,b+c,c+a $ がすべて $ K $ の倍数であるようなものの個数を求めてください。 ただし、$ a,b,c $ の順番を入れ替えただけの組も異なるものとして数えます。また、$ a,b,c $ の中に同じものがあっても構いません。

## 说明/提示

### 制約

- $ 1\ \leq\ N,K\ \leq\ 2\times\ 10^5 $
- $ N,K $ は整数である

### Sample Explanation 1

$ (1,1,1),(1,1,3),(1,3,1),(1,3,3),(2,2,2),(3,1,1),(3,1,3),(3,3,1),(3,3,3) $ が条件を満たします。

## 样例 #1

### 输入

```
3 2```

### 输出

```
9```

## 样例 #2

### 输入

```
5 3```

### 输出

```
1```

## 样例 #3

### 输入

```
31415 9265```

### 输出

```
27```

## 样例 #4

### 输入

```
35897 932```

### 输出

```
114191```

# 题解

## 作者：chinazhanghaoxun (赞：6)

## 题意

给定整数 $N$ 和 $K$，需要求出不大于 $N$ 的所有三元组满足 $a+b$，$a+c$ 和 $b+c$ 都是 $k$ 的倍数，且需要考虑顺序。
## 分析

根据题意，我们可以得到一些式子：
$$a+b=x\times k$$
$$a+c=y\times k$$
$$b+c=z\times k$$
接下来将这些式子相加，得到：
$$2\times(a+b+c)=(x+y+z)\times k$$
接下来，我们就要对 $K$ 进行奇偶性分类讨论。

- 如果 $K$ 为奇数，那么 $a$，$b$，$c$ 都需要是 $K$ 的倍数才行。又因为选的数字在 $N$ 之内，所以可能的情况有 $\lfloor \frac{N}{K} \rfloor$ 种，又要考虑顺序，所以有 ${\lfloor \frac{N}{K} \rfloor}^3$ 种可能的顺序。
- 如果 $K$ 为偶数，则 $\frac{K}{2}$ 就也是整数，那么就会多一些情况了，有：
  $$a=x_1\times K +\frac{K}{2}$$
  $$b=y_1\times K +\frac{K}{2}$$
  $$c=z_1\times K +\frac{K}{2}$$
这时式子中多了 $\frac{K}{2}$，情况数量也就还要比奇数增加 $((N+K/2)/K)^3$。
## 代码+注释

数据很大，要开 long long。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,k,ans=1;
	cin>>n>>k;
	ans=pow(n/k,3);//不管什么情况都会有这一部分
	if(k%2==0){ //是偶数还有额外的情况 
		ans+=pow((n+k/2)/k,3);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：qinyiyang2012 (赞：2)

### 思路分析
很明显，简单的暴力是 $O(N^3)$ 的，会挂掉。
正解的话咱们可以枚举 $b$，因为 $k|(a+b)$ 且 $k|(b+c)$，所以 $k|(a+2 \times b+c)$，又 $k|(a+c)$，所以 $k|2 \times b$，$a≡c$ $( \bmod $ $k)$。同理，$k|2 \times a$，$k|2 \times c$。最后看有多少个 $a$ 合法，则有多少个 $c$ 合法，累加求和即可。
说的比较晕，看代码吧。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//都开 long long 保险
ll n,k;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    ll ans=0;
    for(ll i=1;i<=n;i++){
    	if(2*i%k)continue;//判断 b 是否合法
    	ll a=(k-i%k)%k;//求出 a mod k的值
    	if(2*a%k)continue;//判断 a 是否合法
    	ll x=n%k,sum=0;
    	sum+=n/k;
  		if(x>=a&&a!=0)sum++;
      //求出有多少个合法值
  		ans+=sum*sum;//因为 a 与 c 同余且允许值相等，利用乘法原理累加求和
  	}
  	cout<<ans;
    return 0;
}
```
如有错误，请指出。

---

## 作者：_zuoqingyuan (赞：1)

# 思路分析

假设：

$$a\equiv x\pmod{k}$$

其中 $0\le x<k$，根据 $a+b\equiv 0\pmod{k}$，可得：

$$b\equiv k-x\pmod{k}$$

同理可得：

$$c\equiv x\pmod{k}$$

推到这里，就很好做了，设 $g_i$ 表示 $[1,n]$ 中模 $k$ 等于 $i$ 的数的个数，可以提前算出来，如果存在 $2\times i=k$，就令 $ans\gets ans+g_i\times g_i\times g_{k-i}$。

记得特判 $i=0$ 的情况。

好像可以 $O(1)$ 做，不过太懒了，没写。

# Code

```cpp
#include <iostream>
using namespace std;
const int N=1e5+10;
int n,k,a[N];
typedef long long ll;
ll ans;
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++){
		a[i%k]++;
	}
	for(int i=0;i<k;i++){
		if(2*i%k==0)ans+=1ll*a[i]*a[i]*a[((k-i)%k+k)%k];
	} 
	printf("%lld\n",ans);
	return 0;
}
```

如有错误，请指出。

---

## 作者：__hjwucj__ (赞：1)

# 题解：AT_arc102_a [ABC108C] Triangular Relationship

[题目传送门](https://www.luogu.com.cn/problem/AT_arc102_a)

## 思路

   我们先看一眼数据，$1 ≤ N,K ≤ 2 \times 10^5$，如果暴力一定会爆，所以，算法的时空复杂度一定是这几个：
   
$$O(n),O(k),O(n\times \log_n),O(k\times \log_k),O(1)$$

我选择了 $O(1)$ 。

**开始！！！**

因为 $a,b,c ≤ n$，所以我们假设 $a+b=k1 \times k$，$a+c=k2\times k$，$b+c=k3\times k$，$ans=k1+k2+k3$，$f=a+b+c$，因此就可以推出 $2f=k\times ans$。

现在我们来找一下 $k$ 的规律。

当 $k$ 为奇数时，$a,b,c$ 可以取 $1$ 到 $n$ 的所有数。当然，要确保是 $k$ 的倍数，于是答案就是 $⌊ \frac{k}{n} ⌋^3$ 。

当 $k$ 为偶数时，多出来了几种情况:

$$a=k1'\times k+\frac{k}{2}$$

$$b=k2'\times k+\frac{k}{2}$$

$$c=k3'\times k+\frac{k}{2}$$

于是我们就要加上 $\frac{n+\frac{k}{2}}{k}$ 。

完结了。。。

就这么简单！

## 代码参考

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace drest {
#define _fcfo friend const fast_io& operator
#define _io const fast_io& io
#define _gething1(_ch) (bool) ((_ch=getchar())==' '||_ch=='\n'||_ch=='\t'||_ch==4)
#define _gething2(_ch) (bool) ((_ch = getchar())<'0'||_ch>'9')
    /* code by Drest */
    const char* _website_ = "dresteam.online";
    using std::string;	using std::pair;	using std::map;		using std::set;
    using std::vector;	using std::queue;	using std::deque;   using std::priority_queue;
    using std::sort;    using std::swap;	using std::min;	    using std::max;
    using std::floor;   using std::ceil;    char _ch_;
    template<class T> T abs(const T & x) {return x < 0 ? -x : x;}
    class fast_io {
        template<class T> static const fast_io& input_integer(_io, T &x) {
            T f = 1, res;   while(_gething2(_ch_)) if(_ch_ == '-') f = -1; res = _ch_ ^ 48;
            while(!_gething2(_ch_)) res= (res << 1) + (res << 3) + (_ch_ ^ 48); x = res * f;	return io;
        }
        template<class T> static const fast_io& output_integer(_io, T &x)
        {if(x<0)putchar('-'); x = abs(x); if(x>9)io<<(T)(x/10); putchar(x%10+'0'); return io;}
        _fcfo >> (_io, bool &x) 	    {return input_integer(io, x);}
        _fcfo >> (_io, short &x) 		{return input_integer(io, x);}
        _fcfo >> (_io, int &x)     	    {return input_integer(io, x);}
        _fcfo >> (_io, long &x) 		{return input_integer(io, x);}
        _fcfo >> (_io, long long &x)	{return input_integer(io, x);}
        _fcfo >> (_io, __int128 &x)	    {return input_integer(io, x);}
        _fcfo << (_io, short x)		    {return output_integer(io, x);}
        _fcfo << (_io, int x)	    	{return output_integer(io, x);}
        _fcfo << (_io, long x)	    	{return output_integer(io, x);}
        _fcfo << (_io, long long x)  	{return output_integer(io, x);}
        _fcfo << (_io, __int128 x)   	{return output_integer(io, x);}
        _fcfo >> (_io, float &x)	    {scanf ("%f", &x);   return io;}
        _fcfo >> (_io, double &x)   	{scanf ("%lf", &x);  return io;}
        _fcfo << (_io, float x)      	{printf ("%f", x);   return io;}
        _fcfo << (_io, double x)     	{printf ("%lf", x);  return io;}
        _fcfo >> (_io, char &x) 	    {while (_gething1(x)) {}    return io;}
        _fcfo << (_io, char x)       	{putchar (x);	    return io;}
        _fcfo >> (_io, string &x)    	{while(_gething1 (_ch_)) {} x = _ch_; while (!_gething1(_ch_)) x += _ch_; return io;}
        _fcfo << (_io, string x)	  	{for(int i=0; i < x.size (); i++)putchar (x[i]); return io;}
        _fcfo >> (_io, char* &x)     	{string res; io >> res; x=&res[0]; return io;}
        _fcfo << (_io, char* x)	        {for (int i=0; i < strlen(x); i++) putchar (x[i]); return io;}
        public:
            fast_io& getline(string &x) {x = ""; while ((_ch_ = getchar ()) != '\n' && _ch_ != 4) x += _ch_; return *this;}
            fast_io& getline(char* &x)  {string res;     this->getline (res);     x = &res[0];	  return *this;}
    };
    fast_io io, cin, cout;  const char & endl = '\n';
}
#define cin io
#define cout io
#define endl '\n'
#define f first
#define s second
#define int long long
using namespace drest;
int n,k,ans,t;
signed main ()
{
	cin>>n>>k;
	ans=n/k;
	ans=pow (ans,3);
	if (k%2==0) t=(n+k/2)/k,t=pow (t,3),cout<<k+t;
		else cout<<ans;
	return 0;
}

```

---

## 作者：___cjy__ (赞：1)

# [ABC108C] Triangular Relationship 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc091_b)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-at-arc102-a)

### 题目大意：

找出不大于 $N$ 的正整数组成的三元组满足 $a+b$，$b+c$ 和 $c+a$ 均为 $K$ 的倍数的 $(a,b,c)$ 的数量。

### 正文：

来推一下式子

由题意得
$$a+b=x\times K$$
$$b+c=y\times K$$
$$c+a=z\times K$$

将三式相加，得
$$a+b+b+c+c+a=x\times K+y\times K+z\times K$$
$$2(a+b+c)=(x+y+z)\times K$$

显然，因为 $K$ 是一个正整数，我们便要根据 $K$ 的奇偶分类讨论。

- $K$ 为奇数时：

只要当 $a$，$b$，$c$ 都是 $K$ 的倍数时，就满足题意。因为在 $N$ 个数里有 $\lfloor\dfrac{N}{K}\rfloor$ 个符合要求的数，所以一共有 $\lfloor\dfrac{N}{K}\rfloor^3$ 种选择。

- $K$ 为偶数时：

当 $N$ 为偶数，显然，$\dfrac{K}{2}$ 是一个整数，于是便有了：

$$a=x_1\times K+\dfrac{K}{2}$$
$$b=y_1\times K+\dfrac{K}{2}$$
$$c=z_1\times K+\dfrac{K}{2}$$

的另外情况。因为在原来的基础上多了 $\dfrac{K}{2}$，所以便需要在奇数的基础上加上 $\lfloor\dfrac{N+\dfrac{K}{2}}{K}\rfloor^3$。

### AC Code：

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 205
#define INF 0x3f3f3f3f
#define bug printf(".....bug!.....\n");
#define max(a,b) a>b?a:b

using namespace std;

int n, k, ans = 0;

signed main(){
	cin >> n >> k;
	for(int b=k+1; b<=n; b++){
		ans += (n/b)*(b-k);
		ans += max(0, n%b-k+1);
		if(!k) ans--;
	}
	cout << ans;
	
	return 0;
} 
```

---

## 作者：YueYang1235 (赞：1)

$ a,b,c \leq n $

$ a + b = k1 \times K $

$ a + c = k2 \times K $

$ b + c = k3 \times K $

令 $ k = k1 + k2 + k3 $

令 $ r = a + b + c $

$ 2 \times r = k \times K $

讨论一下 $ K $ :

当 $ K $ 为奇数时， $ a $ , $ b $ , $ c $ 可以取 $ 1 $ 到 $ n $ 的所有数，当然咯，要确保是 $ K $ 的倍数，于是答案就是 $ \lfloor \dfrac{n}{k} \rfloor ^3 $ 

当 $ K $ 为偶数时，多出来了一种情况:

$ a = k4 \times K + K / 2 $

$ b = k5 \times K + K / 2 $

$ c = k6 \times K + K / 2 $

于是我们就要加上$ ( n + k / 2) / k $

```cpp
//code
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k;//要开long long 
ll ans,t;
int main(){
	scanf("%d%d",&n,&k);
	ans=n/k;
	ans=ans*ans*ans;
	if(k%2==0)t=(n+k/2)/k,t=t*t*t;
	cout<<ans+t;
	return 0;
}
```

一点点小建议：有些AT的题目样例重复了一遍，希望能修复一下


---

## 作者：Frictional (赞：0)

## 题意
给出整数 $N$ 和 $K$。找出不大于 $N$ 的正整数三元组 $(a,b,c)$ 满足 $a+b,a+c,b+c$ 都为 $K$ 的倍数，注意这里求的是三元组是排列数。

## 思路
首先，因为 $a+b,a+c,b+c$ 都为 $K$ 的倍数，所以 $(a+b)+(a+c)-(b+c)=a+b+a+c-b-c=2a$ 为 $K$ 的倍数，同理 $2b,2c$ 也都是 $K$ 的倍数。

我们根据 $K$ 的奇偶性来分别讨论。

1. 当 $K$ 为奇数时。因为 $2a,2b,2c$ 为 $K$ 的倍数，且 2 不是 $K$ 的倍数，所以 $a,b,c$ 一定是 $K$ 的倍数。再反过来证明，如果 $a,b,c$ 为 $K$ 的倍数时，显然 $a+b,a+c,b+c$ 都为 $K$ 的倍数。所以 $a,b,c$ 为 $K$ 的倍数与 $a+b,a+c,b+c$ 为 $K$ 的倍数这两个命题是互为充要条件的，所以两个命题的 $a,b,c$ 的取值范围是相同的，就不会出现多或少的情况了。所以 $a,b,c$ 可以取 $N$ 以内的，所有 $K$ 的倍数。方案数就有 $(\frac{N}{K})^3$。

2. 当 $K$ 为偶数时。因为 $2a,2b,2c$ 为 $K$ 的倍数，所以 $a,b,c$ 一定都是 $\frac{K}{2}$ 的倍数。又因为 $a+b,a+c,b+c$ 都为 $K$ 的倍数。所以 $a,b,c$ 要么都形如 $p\times K+\frac{K}{2}(p\in N)$ 的数，要么都是形如 $p\times K(p\in N)$ 的数。第一种情况每个数都有 $\frac{N+\frac{K}{2}}{K}$ 种可能，第二种情况每个数都有 $\frac{N}{K}$ 种取法，最后加起来就可以了。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define MP make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define debug(x) cerr<<#x<<'='<<x<<endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define gc getchar()
#define pc putchar
using namespace std;
inline int rd(){
    int x=0,f=1; 
    char ch=gc;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
    return x*f;
}
inline void wr(int x){
    if(x<0) x=-x;
    if(x>9) wr(x/10);
    pc((x%10)^48);
}       
int n,k;
int ans;
int two,tmp;
signed main() {
    n=rd(),k=rd();
    ans=(n/k)*(n/k)*(n/k);
    if(k%2==0){
        two=k/2;
        tmp=(n+two)/k;
        ans+=(tmp*tmp*tmp);
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：CodingOIer (赞：0)

这是一道 AtCoder 的 ABC108C Triangular Relationship 题目。

### 题目翻译

给定 $N$ 和 $K$，找出所有满足 $a+b,b+c,c+a$ 均为 $K$ 的倍数的 $(a,b,c)$，其中 $a,b,c$ 都是 $\le N$ 的正整数。$a,b,c$ 的顺序不同被看作不同的三元组，只要符合条件即可。

### 解题思路

因为 $a+b,b+c,c+a$ 均为 $K$ 的倍数，所以可以写成：

$$k|(a+b+c)$$

化简一下：

$$k|((a+b+c)+(a-b-c))$$

$$k|2a$$

因此 $a$ 一定是 $k$ 的倍数，在此的前提下，每一组 $(a,b,c)$ 一定如下所示：

$$(ak,bk,ck)$$

其中 $k|(a-b-c)$。因为 $1\leq a,b,c \leq n$，因此 $1\leq ak,bk,ck \leq nk$。

考虑枚举 $k$ 的倍数在 $1$ 到 $nk$ 范围内出现的次数，这里假设数值是 $p$（即 $p$ 个 $k$ 的倍数），那么其他两个数的范围就是 $(1-p)k$ 到 $(n-p)k$，这个范围推出来做一下就可以了。对于每种 $i$，$a$ 的范围是 $ik$ 到 $(i+1)k$ 之间，$a$ 的个数就是 $(n+(i+1)k)/k-(ik+k)/k$，也就是 $(n+ik)/k - i -1$。

求出 $a$ 的可能个数并且作一个平方即可。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
long long ans;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        int cnt1 = (n / k), cnt2 = (n - k * (i % k)) / k + 1;
        // cnt1是k的倍数的个数，cnt2是(i+k*k')=n的个数
        // cout << i << ' ' << cnt1 << ' ' << cnt2 << '\n';
        if (i % k == 0)
        {
            ans += 1LL * cnt1 * cnt1 * cnt1;
        }
        else
        {
            ans += 1LL * cnt1 * cnt1 * cnt2 + 1LL * cnt1 * cnt2 * cnt2;
        }
        // 这里就是直接套公式：a的范围是(i,j)，能够有abs(i-j)/k个a满足条件
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

发现 $n$ 不大，因此考虑枚举 $a$。三元组应该形如 $(i,pk-i,qk-i)$ 的形式，若满足 $b+c=(p+q)k-2i$ 是 $k$ 的倍数，则需要 $2i$ 是 $k$ 的倍数，满足这一条件时，统计 $p$ 的数量并平方就是此时 $i$ 对应的答案数。$p$ 应满足 $1\le pk-i\le n$，解不等式即可。


```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int main(void) {
    int n, k; long long ans = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) if (2 * i % k == 0) {
        int cnt = (n + i) / k - (i + k) / k + 1;
        ans += 1ll * cnt * cnt;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：BeetyX (赞：0)

既然a+b、b+c、a+c都是K的倍数，那么可以假设：

a+b=x1×K

a+c=x2×K

b+c=x3×K

则a+b+a+c+b+c=2(a+b+c)=(x1+x2+x3)×K

最终得到：**2(a+b+c)=(x1+x2+x3)×K** 

既然K是正整数，那么就需要分类讨论：

当K为奇数时，a，b，c这三个数可以随便取，但是需要是K的倍数。在n个数里有$\left\lfloor\dfrac{n}{K}\right\rfloor$个符合要求的数。既然是有3个数，每个都有$\left\lfloor\dfrac{n}{K}\right\rfloor$个数的选择，题目里也没说a，b，c不能相等，那么就是$\left\lfloor\dfrac{n}{K}\right\rfloor$³个选择。

当K为偶数时，情况就更多了：因为K为偶数，那么$\frac{K}{2}$也一定为整数，而且$\frac{K}{2}$+$\frac{}{2}$也一定为K的倍数。既然只要a+b、a+c、b+c为K的倍数，那么在原来的基础上又会增加了：

a=x4×K+$\frac{K}{2}$ 

b=x5×K+$\frac{K}{2}$

c=x6×K+$\frac{K}{2}$

所以在奇数的选择数中要加上$\frac{K}{2}$，每个数有$\dfrac{n+\dfrac{K}{2}}{K}$个选择，和奇数的情况一样，最后再加上个立方。

大致思路：if判断K为奇数还是偶数，然后输出相应的方案数。

代码如下
------------
```
#include<bits/stdc++.h>
using namespace std;
long long n,k;//有立方了，必须开long long
long long ans,ans1=0;
int main()
{
     cin>>n>>k;
     ans=n/k;
     ans=ans*ans*ans;//先算n/k的立方
     if(k%2==0)
     //然后在分类讨论，在这里只需要讨论k是否为偶数就可以了，因为奇数只需要直接输出
     {
     	ans1=(n+k/2)/k;//每个数的选择数
        ans1=ans1*ans1*ans1;//新增的选择数的立方
     }
	cout<<ans+ans1<<endl;//把最原来的选择数和新增的选择数相加后输出
	return 0;
}
```


---

