# Two Arrays and Sum of Functions

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

Let's define a function $ f(l, r) = \sum\limits_{l \le i \le r} a_i \cdot b_i $ .

Your task is to reorder the elements (choose an arbitrary order of elements) of the array $ b $ to minimize the value of $ \sum\limits_{1 \le l \le r \le n} f(l, r) $ . Since the answer can be very large, you have to print it modulo $ 998244353 $ . Note that you should minimize the answer but not its remainder.

## 样例 #1

### 输入

```
5
1 8 7 2 4
9 7 2 9 3
```

### 输出

```
646
```

## 样例 #2

### 输入

```
1
1000000
1000000
```

### 输出

```
757402647
```

## 样例 #3

### 输入

```
2
1 3
4 2
```

### 输出

```
20
```

# 题解

## 作者：Rex01 (赞：11)

## [CF1165E 题目传送门](https://www.luogu.com.cn/problem/CF1165E)

## 题目大意
给定两个长度均为 $n$ 的数组 $a$ 和数组 $b$，定义函数 $f(l, r) = \sum\limits_{i = l} ^ {r} (a_i \cdot b_i)$。你的任务是重新排列数组 $b$ 的元素，使 $f(l,r)$ 的值最小。更具体的解释：就是要求对于区间 $[1,n]$ 上所有子区间 $[l,r] (1 \leq l \leq r \leq n)$，函数 $f(l,r)$ 的总和的最小值。

## 解决思路
有题目中的公式可以推断出
$$
\begin{aligned}
f(l, r) &= \sum\limits_{i = l} ^ {r} (a_i \cdot b_i)\\
&= (a_l \cdot b_l) + (a_{l + 1} \cdot b_{l + 1}) + (a_{l + 2} \cdot b_{l + 2}) + \cdots + (a_r \cdot b_r)\\
&\because l=C_{i}^{1}, r=C_{n-i+1}^{1}\\
&\therefore C_{i}^{1} \cdot C_{n-i+1}^{1} = i \cdot (n - i + 1)\\
&\therefore \sum\limits_{i = l} ^ {n} [a_i \cdot b_i \cdot (n - i + 1) \cdot i]
\end{aligned}
$$
随后再把推导出的公式融入进代码即可。

## 代码展示
```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
const int mod = 998244353;
ll n, a[N], b[N], sum;

bool cmp(int a, int b)
{//从大到小排序函数
	return a > b; 
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i], a[i] *= (n - i + 1) * i;
	for(int i = 1; i <= n; i++)
		cin >> b[i];
	sort(a + 1, a + n + 1);//从小到大
	sort(b + 1, b + n + 1, cmp);//从大到小
	for(int i = 1;i <= n; i++)
	{
		sum %= mod;
		sum += a[i] % mod * b[i] % mod;
		sum %= mod;
	}
	cout << sum << endl;
	return 0;
}
```

---

## 作者：momo5440 (赞：6)

本质上来说这是道数学题（确信），用到了高中数学里的排序不等式不会的可以去看看这个[传送门](https://baike.baidu.com/item/排序不等式/7775728?fr=aladdin)，这是个非常厉害的不等式，用的好的话理论上来说高中很多不等式题都可以用它解决（可惜我不会用）但这题可以用到它，我们先设排完序的b数组为c数组（使其满足所求的值最小，具体方法一会再说）。

我们先看看每一组 _c[i]_ 与 _a[i]_ （ _a[i]_ 与题目中说的一样）对答案的贡献吧，换句话来说那些[l,r]包含了i，我们可以轻松得出1<=l<=i&&i<=r<=n，于是对于l来说他总共有i种选择，即1,2....i，而对于r来说他可以有n-i+1种选择，即i,i+1,i+2.....n。所以最终答案就是 

_∑a[i]×c[i]×(n-i+1)×i(1<=i<=n)_ 

下面便该考虑一个问题了，怎么把b数组变成c数组理论上来说应该是反序和最小，即最大的a对最小的b,第二大的a对第二小的b....但这题里a却不是a而是 _a[i]×i×(n-i+1)_ ，这是因为这些数的乘积是答案所需且不会变的，所以只能以 _a[i]×i×(n-i+1)_ 的大小来排序a数组，实现方式就是让a数组在其输入时乘以(n-i+1)×i。

大概就是这么多东西了，把代码贴上，有不懂的欢迎私信给我

顺便厚颜无耻的贴上我的博客[博客](https://www.luogu.org/blog/ailundeyugang/#)

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll cmp1(ll a,ll b){
	return a<b;
}
ll cmp2(ll a,ll b){
	return a>b;
}
ll a[maxn],b[maxn],n;
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]*=i*(n-i+1);
	}
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+1,cmp1);//正着排a 
	sort(b+1,b+n+1,cmp2);//反着排b 
	ll ans=0;
	for (int i=1;i<=n;i++){
		a[i]%=998244353;//注意这里也要%不然会爆掉 
		ans=(ans+a[i]*b[i])%998244353;
	}
	cout<<ans<<endl;
}
```


---

## 作者：OIerWu_829 (赞：6)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1165E) / [Codeforces 传送门](https://codeforces.com/problemset/problem/1165/E)

不难发现 $a_i$ 的贡献为 $a_i\times(n-i+1)\times i$，所以我们在输入的时候把 $a_i$ 乘上 $(n-i+1)\times i$，然后把 $a$ 数组从小到大排序，把 $b$ 从大到小排序，这样就可以形成差大积小，然后累加 $a_i\times b_i$ 就可以了。

**注意取模的问题，坑了我好久。**

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

using LL = long long;

const LL N = 2e5 + 5;
const LL mod = 998244353;

LL a[N], b[N];

int main()
{
	LL n;
	cin >> n;
	for (LL i = 1; i <= n; i++)
    {
		cin >> a[i];
        a[i] *= (n - i + 1) * i;
    }
	for (LL i = 1; i <= n; i++)
		cin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n, greater<LL>());
	LL ans = 0;
	for (LL i = 1; i <= n; i++)
		ans += a[i] % mod * b[i] % mod;
	cout << ans % mod;
    return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

考虑 $a_i$ 的贡献。对于 $l$，包含 $a_i$ 满足 $1 \le l \le i$；对于 $r$，包含 $a_i$ 满足 $i \le r \le n$。所以 $a_i$ 的贡献为 $a_i \times i \times (n-i+1) \times b_i$。其中 $a_i \times i \times (n-i+1)$ 一定，根据差大积小的原理，$a_i \times i \times (n-i+1)$ 按照从大到小匹配一个从小到大的 $b_i$，就能使贡献和最小。复杂度 $O(n\log n)$。

注：在 $a_i \times i \times (n-i+1)$ 的时候不要取模。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=2e5+10,p=998244353;
int n,a[N],b[N];
int sum;

il void solve(){
	n=read();
	for(re int i=1;i<=n;++i) a[i]=read(),a[i]=a[i]*i*(n-i+1);
	for(re int i=1;i<=n;++i) b[i]=read();
	sort(a+1,a+n+1);
	sort(b+1,b+n+1),reverse(b+1,b+n+1);
	for(re int i=1;i<=n;++i) sum=(sum+a[i]%p*b[i])%p;
	printf("%lld\n",sum);
	return ;
}

signed main(){
	int t=1;while(t--)
	solve();
	return 0;
}
```


---

## 作者：DennyQi (赞：1)

给出两个长度为$n$的序列$a$和$b$，定义$f(l,r)=\sum\limits_{l \leq i \leq r}a_i \cdot b_i$。求$\min\{\sum\limits_{1 \leq l \leq r \leq n}f(l,r)\}$。其中$n \leq 2 \cdot 10^5$。

要求的答案等价于$\min\{\sum\limits_{1 \leq l \leq r \leq n}\sum\limits_{l \leq i \leq r}a_i \cdot b_i\}$。于是我们考虑对于每一个位置$i$，$a_i \cdot b_i$会在答案中出现多少次。直接统计有些困难，我们不妨按照覆盖点$i$的区间右端点依次考虑。右端点为$i$时，左端点可以取$[1,i]$；右端点为$j$时，左端点可以取$[1,i]$……综上，左端点可以取$[1,i]$，右端点可以取$[i,n]$。因此能覆盖点$i$的区间共有$i \cdot (n-i+1)$个

因此答案可以用这种形式来表示：$\min\{\sum\limits_{1 \leq i \leq n}a_i \cdot b_i \cdot i \cdot (n-i+1)\}$

根据题目条件，除了$b_i$之外都为定值，不妨设$c_i=a_i \cdot i \cdot (n-i+1)$。则答案转化为$\min\{\sum\limits_{1 \leq i \leq n}c_i \cdot b_i\}$

关于两个序列两两相乘之和最小，有一个贪心的结论：对两序列从小到大排序$b_i$应当配对$c_{n-i+1}$。我有一个证明（不知道对不对，烦大佬指正）：

设有任意$a_i,a_j,b_p,b_q$（排序后的）满足$1 \leq i < j \leq n$，$1 \leq p < q \leq n$。有两种方案$A = a_i \cdot b_q + a_j \cdot b_p$，$B = a_i \cdot b_p + a_j \cdot b_q$，我们用作差法比较大小。$A-B=a_i \cdot (b_q-b_p) + a_j \cdot (b_p - b_q) = (a_i-a_j) \cdot (b_q - b_p)$，显然$a_i-a_j \leq 0, b_q-b_p \geq 0$，因此$A-B \leq 0$，因此$A \leq B$。于是无论对于哪种情况，选择$A$肯定不会不优，于是贪心结论成立。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define int long long
const int P = 998244353;
using namespace std;
const int N = 200010;
inline int read(){
	int x(0),w(1); char c = getchar();
	while(c^'-' && (c<'0' || c>'9')) c = getchar();
	if(c=='-') w = -1, c = getchar();
	while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
	return x*w;
}
int n,ans,a[N],b[N];
signed main(){
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read()*i*(n-i+1);
	for(int i = 1; i <= n; ++i) b[i] = read();
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i = 1; i <= n; ++i) ans = (ans + ((a[i]%P)*(b[n-i+1]%P)))%P;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1165E)

## 思路
首先我们可以计算一下 $i$ 会被选中多少次，显然只有在 $[l \leq i \leq r] = 1$ 时 $i$ 才会被选中，而此时 $l \in [1, i]$ 有 $i$ 种选择，$r \in [i, n]$ 有 $n - i + 1$ 种选择，那么 $i$ 就会被选择 $i \cdot (n - i + 1)$ 次，所以问题就变为 $\underset{i = 1}{\overset{n}{\sum}} i \cdot (n - i + 1) \cdot a_{i} \cdot b_{i}$ 的最小值是多少。

## 具体做法
首先令 $a_{i} = a_{i} \cdot i \cdot (n - i + 1)$，然后根据差小积大，将 $a$ 从小到大排序，$b$ 从大到小排序。

循环算出此时 $\underset{i = 1}{\overset{n}{\sum}} i \cdot (n - i + 1) \cdot a_{i} \cdot b_{i}$ 的值，并输出。

## AC Code
```cpp
/*
from:CF-1165E
difficulty:1600
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

const ll mod = 998244353;
const int maxn = 2e5 + 10;

int n;
ll a[maxn], b[maxn];

ll ans;

int main () {
	scanf("%i", &n);
	FOR (1, n, i) {
		scanf("%lld", &a[i]);
		
		a[i] = a[i]*(n - i + 1)*i;
	}
	FOR (1, n, i) {scanf("%lld", &b[i]);}
	
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1, greater<>());
	FOR (1, n, i) {ans = (ans + a[i]%mod*b[i]%mod)%mod;}
	
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

已知两个长度均为 $n$ 的数组 $a$ 和 $b$。

给定一个函数：$f(l, r) = \sum \limits_{l \le i \le r} a_i \cdot b_i$。

你的任务是对数组 $b$ 中的元素以任意的顺序重新排序，使 $\sum \limits_{1 \le l \le r \le n} f(l, r)$ 的值最小。

## 题目分析

我们首先进行化简，发现题目中要求的实质上就是最小化 $\sum\limits_{l=1}^{n} \sum\limits_{r=l}^{n} \sum\limits_{i=l}^{r} a_i \times b_i$。接下来，我们考虑每一个 $a_i \times b_i$ 的贡献，由上述和式可知，$a_i \times b_i$ 出现的次数等于包含 $i$ 的区间的个数，设包含 $i$ 的区间为 $[l,r]$。显然 $1 \leq l \leq i$ 且 $i \leq r \leq n$。则 $l$ 共有 $i$ 个，$r$ 共有 $n-i+1$ 个，由**乘法原理**可得，包含 $i$ 的区间共有 $i \times (n-i+1)$ 个。即 $a_i \times b_i$ 共计算了 $i \times (n-i+1)$ 次。

有了上述的推导，题目要最小化的和式便可以化简成 $\sum\limits_{i=1}^{n} i \times (n-i+1) \times a_i \times b_i$，由题目可得 $i \times (n-i+1) \times a_i$ 是不变的，所以我们可以令 $c_i=i \times (n-i+1) \times a_i$，题目便被转化成最小化 $\sum\limits_{i=1}^{n} c_i \times b_i$。

此时，我们引入**排序不等式**，它的内容如下：

>设有两个长度为 $n$ 的数列 $a$ 和 $b$，满足 $a$ 序列和 $b$ 序列单调不减，$c$ 序列是 $b$ 序列的乱序排列，则有：
>$$\sum\limits_{i=1}^{n} a_i \times b_{n-i+1} \leq \sum\limits_{i=1}^{n} a_i \times c_i \leq \sum\limits_{i=1}^{n} a_i \times b_i$$

有了排序不等式，解法就呼之欲出了，我们倒序排列序列 $c$，再升序排列序列 $b$，最后求 $\sum\limits_{i=1}^{n} c_i \times b_i$ 即可，由排序不等式可证，此时的答案就是最小的了。

## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int unsigned long long
const int N=2*1e5+10;
const long long mod=998244353;
int n,a[N],b[N],ans;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
	    if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
	    x=(x<<1)+(x<<3)+ch-48;
	    ch=getchar();
	}
	return x*f;
}
inline void write(int x)
{
    if(x<0)
	{
    	putchar('-');
		x=-x;
	}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
bool cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=read();
	}
	for(int i=1;i<=n;i++)
	{
		a[i]*=i*(n-i+1);
	}
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++)
	{
		a[i]%=mod;
		ans=(ans+a[i]*b[i])%mod;
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

考虑将第 $i$ 个点的被计入答案的次数，即为 $c_i=i \times (n-i+1)$，那么 第 $i$ 个点的贡献即为 $a_i \times b_i \times c_i$，因此可以将 $a,b$ 数组重排：将 $a_i \to a_i \times c_i$，并从小到大排序，将 $b$ 数组从大到小排序，相乘即为最小值（也就是将大的 $a_i \times c_i$ 乘小的 $b_i$，答案便最小）。

```cpp
	scanf("%lld",&n); 
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]=a[i]*i*(n-i+1); 
	sort(a+1,a+n+1); int ans=0; 
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]); 
	sort(b+1,b+n+1); 
	for(int i=n;i>=1;i--) ans=(ans+a[i]%Mod*b[i])%Mod; 
	printf("%lld\n",ans); return 0; 
```


---

## 作者：__zhuruirong__ (赞：0)

这是一道数学 + 思维题，还算简单。

## 算法分析

很显然，对于每个 $a_i$，应该配对一个对应的 $b_j$，使得 $a_i$ 在 $a$ 从大到小排序后的位置和 $b_j$ 从小到大排序后的位置相同。

然而，这样我们并不能 AC，因为我们还有个因素没考虑：每个 $a_i$ 累加的数量。在这个序列中，包含 $a_i$ 的区间有 $i\times(n-i+1)$ 个，所以只要在 $a_i$ 读入时，乘上个 $i\times(n-i+1)$，就能保证正确。

## 代码

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;

const int N = 1e6 + 10;
int n, a[N], b[N], ans;

signed main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] *= i * (n - i + 1);
    }
    for(int i = 1; i <= n; i++)
        cin >> b[i];
    sort(a + 1, a + n + 1, greater<int>());
    sort(b + 1, b + n + 1);
    for(int i = 1; i <= n; i++)
        ans = (ans % 998244353 + a[i] % 998244353 * b[i] % 998244353) % 998244353; // 少模不如多模%%%
    cout << ans << endl;

    return 0;
}

```

---

## 作者：_smart_stupid_ (赞：0)

# [题目](https://www.luogu.com.cn/problem/CF1165E)

这个题代码不难，主要是在纸上推理的过程有点麻烦。

## 思路：

事先计算好每个 $a_i$ 要被计算的次数，将 $a_i$ 乘上这个次数，最后将 $a$、$b$ 数组排序，一个正序，一个倒序，然后将 $a$、$b$ 数组每个项依次乘起来，加到答案里。

## 每一个 $a_i$ 要被计算多少次？

看下图，可以推出公式：

[![nUxP0.png](https://i.imgs.ovh/2023/11/16/nUxP0.png)](https://imgloc.com/image/nUxP0)

第 $i$ 个整数要被乘上 $i \times (n-i+1)$ 次。

## 为什么可以这么做？

对于 $a$、$b$、$c$、$d$ 四个整数，已知 $a < c$，$b < d$，可以证出 $(a \times b + c \times d) < (a \times c < b \times d)$，具体证明过程不再赘述。一个正序，一个倒序就是运用了这个定理，这样排序也使用了贪心的思想。

## 细节：

在 $a$ 数组的每个项乘上他要被计算的次数时，虽然不会爆 ```long long```，但是在乘上 $b$ 的相对元素时，就会爆，答案求原本的最大值，就在排序后把 $a_i$ 模上 $998244353$，就可以解决这个问题。

## AC Code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<list>
#include<set>
using namespace std;
int n;
long long a[200100],b[200100];
long long ans;
long long mod=998244353;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]=a[i]*i*(n-i+1);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) a[i]%=mod;
	for(int i=1;i<=n;i++){
		ans+=a[i]*b[n-i+1];
		ans%=mod;
	}
	printf("%lld",ans%mod);
	return 0;
}
```

---

## 作者：换个思路 (赞：0)

其实这题是个简单的思维题，让a数组的最大值乘以b数组的最小值就行。但要考虑a数组乘以b数组的次数。在因为a数组不会改变。所以就通过a数组乘以次数。那就可以推知a[i] * i * (n - i + 1)这个就是a数组和次数的乘积，让后再给a数组乘完后的数组排序就可。具体代码如下
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
long long n;
long long mod = 998244353;
vector<long long> a, b;
long long ans = 0;
int main(void) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		long long z; cin >> z;
		a.push_back(z * i * (n - i + 1));
	}
	for (int i = 1; i <= n; i++) {
		long long z; cin >> z;
		b.push_back(z);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	reverse(b.begin(), b.end());
	for (int i = 0; i < n; i++) {
		a[i] %= mod;
		ans = (ans + a[i] * b[i] % mod) % mod;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Frozencode (赞：0)

这题一眼**排序不等式**，第$i$个位置会贡献$i*(n-i+1)$次(乘法原理),于是写了个排$a[i]$之后再逆序排$b[i]$，两个乘起来再乘以贡献的次数，结果$WA\ Test\ 4$。

然后就发现哪里不对了，事实上$a[i]$位置是固定的，所以排序不等式中的$a[i]$应该是$a[i]*i*(n-i+1)$，这里需要特别注意的是，因为排序不等式中是要**最大的**配上**最小的**，所以在算排序不等式中的$a[i]$是**不能取模的！！！**（取模后最大的就不一定是最大的了，会$WA\ Test\ 5$），

然后我们就愉快的A了这道E题，不得不说这道题还是挺适合萌新练思维的QWQ


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
const ll mod=998244353;
ll n,a[maxn],b[maxn],sum;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i]=a[i]*i*(n-i+1);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)cin>>b[i];
	sort(b+1,b+n+1);
	reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		a[i]%=mod;
		sum+=a[i]*b[i];
		sum%=mod;
	}
	cout<<sum;
	return 0;
}
```


---

