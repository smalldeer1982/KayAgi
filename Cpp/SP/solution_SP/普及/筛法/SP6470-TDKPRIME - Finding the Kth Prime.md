# TDKPRIME - Finding the Kth Prime

## 题目描述

The problem statement is really simple. There are some queries. You are to give the answers.

## 样例 #1

### 输入

```
7
1
10
100
1000
10000
100000
1000000```

### 输出

```
2
29
541
7919
104729
1299709
15485863```

# 题解

## 作者：ADay (赞：4)

## 作为第一个$\mathcal{A}$了本题的人，我来发题解啦！
先吐槽一下译者，第5000000个质数也就不到$9 \times 10^7$...   
### 做法：
多组数据，考虑欧拉筛。   
不会的可以先去康康[P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)   
但是一个$bool$数组仿佛装不下那么多，所以我们用
### $Bitset!$
$Bitset$在时间和空间上都差不多比$bool$数组要好  
我们要用到以下$Bitset$函数：
- $.set()$:全设为1
- $.reset(x)$:把下标为$x$的设为0
- $.test(x)$:康康下标为$x$的是否为1  
### 然后再讲讲欧拉筛（关键点）
**每个合数都会被自己最小的质因数$\times$最大非自身因数筛掉，而又不再重复被筛**  
用代码实现，我们从2到$x$(边界)枚举$i$，若$ip.test(i)$（isprime），说明它没被筛掉，也就是说，它是质数，则放到$pr_{cnt++}$。   
然后枚举1~$cnt$的$j$,也就是筛的过程，把$pr_j$的$i$倍筛掉，但还要保证$i \times pr_j \leqslant x$,那么在循环条件加上即可。   
接着保证一个数不被重复筛，我们可以在$i \% pr_j=0$的时候$break$掉$j$的循环，因为此时$pr_j$是$i$的一个因数，所以$i$和$pr_{j+1}$并不是$i \times pr_{j+1}$的最小质因数和最大非自身因数，而$i \times pr_{j+1}$显然会在后面被筛掉（因为$i$会遍历到它的最大非自身因数）    
而又有多组数据，可以预处理
### 欧拉筛+$Bitset$的预处理代码：
```cpp
inline void init(int x)//x为边界,即最大
{
    ip.set();
    ip.reset(1);//上面讲的Bitset函数
    for(int i=2;i<=x;i++)//枚举i
    {
        if(ip.test(i))pr[cnt++]=i;
        for(int j=1;j<cnt&&i*pr[j]<=x;j++)//枚举j
        {
            ip.reset(i*pr[j]);
            if(i%pr[j]==0)break;//pr[j]是i因数时break
        }
    }
}
```
### 完整~~丑陋~~代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//快读
{
    int s=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        s=(s<<3)+(s<<1)+ch-48;
        ch=getchar();
    }
    return s*f;
}
inline void write(int x)//快写
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10^48);
}
const int N=5000000+5,NN=9e7+5;
int q,a,pr[N],cnt=1;
bitset<NN+5>ip;
inline void init(int x)//x为边界,即最大
{
    ip.set();
    ip.reset(1);//上面讲的Bitset函数
    for(int i=2;i<=x;i++)//枚举i
    {
        if(ip.test(i))pr[cnt++]=i;
        for(int j=1;j<cnt&&i*pr[j]<=x;j++)//枚举j
        {
            ip.reset(i*pr[j]);
            if(i%pr[j]==0)break;//pr[j]是i因数时break
        }
    }
}
int main()
{
	 q=read();
    init(NN);//多组数据预处理
    while(q--)
    {
        a=read();
        write(pr[a]);
        puts("");//换行
    }
    return 0;
}
```   
### 另一种方法：[这个网站](https://primes.utm.edu/primes/home.php)   
~~本题第一篇题解，求过~~

---

## 作者：Cold_Eyes_bystander (赞：2)

[双倍经验](https://www.luogu.com.cn/problem/P3383)。

[本人语文不好，表达不清楚，谅解](https://blog.csdn.net/qaqwqaqwq/article/details/123587336)。

我们把所有的质数筛出来，最后直接查询就行了。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N=1e8+1;
bitset<N> shu;
vector<int> ss;
int main()
{
    int t;
    cin>>t;
    int N1=N-1;
    shu[1]=shu[0]=1;
    for(int i=1;i<=N1;i++)
    {
        if(shu[i]==0) ss.push_back(i);
        for(int j=0;j<ss.size();j++)
        {
            if(i*ss[j]>N1) break;
            shu[i*ss[j]]=1;
            if(i%ss[j]==0) break;
        }
    }
    while(t--)
    {
        int q;
        cin>>q;
        cout<<ss[q-1]<<endl;
    }
    return 0;
}
```

---

## 作者：HohleFeuerwerke (赞：2)

### 前言

[TDKPRIME - Finding the Kth Prime](https://www.luogu.com.cn/problem/SP6470)。为啥没人做啊？

### 正文

线性筛，拿 bitset 优化一下就好。

```cpp
#include<bits/stdc++.h>
#define HohleFeuerwerke using namespace std
#pragma GCC optimize(3,"Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
//#define int long long
HohleFeuerwerke;
inline int read(){
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) s=s*10+c-'0';
	return s*f;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}
const int MAXN=1e8+5,MAXpi=5e6+5;
int tot,pri[MAXpi];
bitset<MAXN> ispri;
inline void init(){
	ispri[1]=true;
	for(int i=2;i<=MAXN-5;i++){
		if(!ispri[i]) pri[++tot]=i;
		for(int j=1;j<=tot&&i*pri[j]<=MAXN-5;j++){
			ispri[i*pri[j]]=true;
			if(i%pri[j]);
			else break;
		}
	}
}
inline void solve(){
	int T=read();
	while(T--){
		int n=read();
		write(pri[n]),puts("");
	}
}
signed main()
{
	init(),solve();
}
```

---

## 作者：封禁用户 (赞：1)

# Part 1
考虑判断每一个数是不是质数，时间复杂度 $\mathcal O(q\cdot k^{\small\frac32})$，显然无法通过本题。

代码就不放了，实现难度并不高。
# Part 2
还是考虑判断每一个数是不是质数，但是可以建一个数组存计算的第 $i$ 个质数是几，时间复杂度 $\small\mathcal O(k^{\frac32})$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,k,nowk,now=2,prime[5000001];//nowk 表示计算了几个质数，now 表示计算到几，prime[i] 表示第 i 个质数 
bool check(int x){//判断质数函数 
	int s=sqrt(x);
	for(int i=2;i<=s;i++)if(x%i==0)return 0;
	return 1;
}int main(){
	cin>>q;
	while(q--){
		cin>>k;
		if(k>nowk)for(;nowk<=k;now++)if(check(now))prime[++nowk]=now;//计算质数 
		cout<<prime[k]<<'\n';
	}return 0;
}
```
然而该代码对于样例的最后一个数，即 $10^6$，运行了很长的时间。

这个代码时间复杂度 $\mathcal O(k^{\small\frac32})$，而本题 $k\le5\times10^6$，显然也无法通过本题。
# Part 3
考虑使用[埃氏筛](https://oi-wiki.org//math/number-theory/sieve/#%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AD%9B%E6%B3%95)提前筛取质数，然后将每一个存入一个数组中。

用刚刚的代码计算出第 $5\times10^6$ 个质数，是 $86028121$，所以我们只要筛取 $1$ 到 $9\times10^7$ 的质数即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=9e7;
int q,k,pk,prime[5000001];bool p[n+100];//pk 表示已经有了几个质数，prime[i] 表示第 i 个质数，p[i] 表示 i 是否是质数 
int main(){
	memset(p,1,sizeof p);
	for(int i=2;i*i<=n;i++)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=0;//埃氏筛模版
	for(int i=2;pk<=5000000;i++)if(p[i])prime[++pk]=i;//将质数存入数组 
	cin>>q;
	while(q--)cin>>k,cout<<prime[k]<<'\n';
	return 0;
}
```

埃氏筛的复杂度为 $\mathcal O(n\log\log n)$，故该代码的复杂度为 $\mathcal O(k\log\log k+q)$，已经可以通过本题了。
# Part 4
如果想要让刚才的代码更快，可以使用 `bitset`，可以理解为自带 $\dfrac18$  常数的 `bool` 数组。

`p.set();` 等效于 `memset(p,1,sizeof p);`。

访问可以直接使用 `p[i]`。

详细用法见[这里](https://oi-wiki.org//lang/csl/bitset/)。

所以我们可以把刚才的代码改成这样：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=9e7;
int q,k,pk,prime[5000001];bitset<n+100>p;//pk 表示已经有了几个质数，prime[i] 表示第 i 个质数，p[i] 表示 i 是否是质数 
int main(){
	p.set();
	for(int i=2;i*i<=n;i++)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=0;//埃氏筛模版
	for(int i=2;pk<=5000000;i++)if(p[i])prime[++pk]=i;//将质数存入数组 
	cin>>q;
	while(q--)cin>>k,cout<<prime[k]<<'\n';
	return 0;
}
```
运行时间会比原来快一些。

---

## 作者：封禁用户 (赞：1)

hello! 鄙人又来写题解了！

题意：

找出第 $k$ 个大的质数。
#### 前置知识：

- 区间筛


我看大家都是用埃式筛的，于是就想用区间筛来解决此题。


### 区间筛：

如果你不知道区间筛，[看此](https://www.cnblogs.com/lipu123/p/12405132.html)。

设 $A$ 为分块的大小。

用这种算法可以将时间复杂度降到 $O(\sqrt{N} + A)$。

这比线筛不是快得多了吗？

code:

```

void update_sieve(int base) {
    int o = base % wheel_size;
    o = (o + ((o * 105) & 127) * wheel_size) >> 7;
    for (int i = 0, k; i < sieve_words; i += k, o = 0) {
        k = min(wheel_size - o, sieve_words - i);
        memcpy(sieve + i, pattern + o, sizeof(*pattern) * k);
    }
    if (base == 0) {
        sieve[0] |= mask[0];
        sieve[0] &= ~(mask[1] | mask[2] | mask[3] | mask[5] | mask[6]);
    }
    for (int i = 0; i < mcnt; ++i) {
        ll j = primes[i] * primes[i];
        if (j > base + sieve_span - 1) break;
        if (j > base) j = (j - base) >> 1;
        else {
            j = primes[i] - base % primes[i];
            if ((j & 1) == 0) j += primes[i];
            j >>= 1;
        }
        while (j < sieve_span >> 1) {
            mark(sieve, j);
            j += primes[i];
        }
    }
}
void pre_sieve() {
    for (int i = 0; i < (1048576 >> 7); ++i) sieve[i] = 0;
    for (int i = 3; i < 1024; i += 2) {
        if (test(sieve, i >> 1)) {
            for (int j = (i * i) >> 1; j < 1048576; j += i) mark(sieve, j);
        }
    }
    mcnt = 0;
    for (int i = 8; i < 1048576; ++i) {
        if (test(sieve, i)) primes[mcnt++] = (i << 1) + 1;
    }
    for (int i = 0; i < wheel_size; ++i) pattern[i] = 0;
    for (int i = 1; i < wheel_size * 64; i += 3) mark(pattern, i);
    for (int i = 2; i < wheel_size * 64; i += 5) mark(pattern, i);
    for (int i = 3; i < wheel_size * 64; i += 7) mark(pattern, i);
    for (int i = 5; i < wheel_size * 64; i += 11) mark(pattern, i);
    for (int i = 6; i < wheel_size * 64; i += 13) mark(pattern, i);
}
void segment_sieve(int base, int lim) {
    update_sieve(base);
    for (int i = 0; i < sieve_words; ++i) {
        ull o = ~sieve[i];
        while (o) {
            int p = __builtin_ctzll(o);
            int u = base + (i << 7) + (p << 1) + 1;
            if (u >= lim) break;
            all[pcnt++] = u;
            o -= o & ((~o) + 1);
        }
    }
}
void fast_sieve(int lim) {
    pre_sieve();  
    all[pcnt++] = 2;
    for (int base = 0; base < lim; base += sieve_span)
        segment_sieve(base, lim);
}
int main() {
    build_mask();
    fast_sieve(1e9);
    int m = rd();
    while (m--) {
        int n = rd();
        printf("%d\n", all[n - 1]);
    }
}
```




---

## 作者：qw1234321 (赞：0)

这不是大水题吗。

首先看到多测，怼上去一个筛质数模板，预处理一下，然后询问的时候 $\mathcal O(1)$ 回答即可。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
namespace things{
	il int rd(){
		int f = 1, x = 0;
		char ch = getchar();
		while(ch < '0' || ch > '9'){
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9'){
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		return x * f;
	}
	il int max(int x, int y){
		return std::max(x, y);
	}
	il int min(int a, int b){
		return std::min(a, b);
	}
}
using namespace things;
using namespace std;

const int N = 5e6 + 5, M = 1e4, S = 9e7;
int n, k, idx, prime[N];
bool p[S + 10];
stack<int> st;
queue<int> q;
vector<int> g;
bitset<M> bs;

void work(){
	cin >> n, cout << prime[n] << "\n";
}

signed main(){
	for (int i = 2; i * i <= S; i++) if (!p[i]) for (int j = i * i; j <= S; j += i) p[j] = 1;
	for (int i = 2; idx <= 5000000; i++) if (!p[i]) prime[++idx] = i;
	int t = 1;
	cin >> t;
	while(t--) work();
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 题意简述
有 $T$ 组数据，每组数据中给出 $k$，请求出第 $k$ 个质数。
## 开始解题！
首先当我们看到数据范围 $1 \le k \le 5000000$ 时，通过较为暴力的计算方法可以得知第 $5000000$ 个质数为 $86028121$，大约 $9 \times 10^ 7$ 左右。我们通过估计运行的空间，即可发现有可能会爆空间，由于线性筛中的 `vis` 数组每一项只有真或假两种取值，那么，我们就可以用同样只有真或假两种取值的 `bitset` 来完成。    
时间复杂度：$O(T+\dfrac{k}{w})$，可以通过。  
所以将 `vis` 数组的一些操作用 `bitset` 来代替即可 `AC`。
## 代码：
```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
const int maxn = 9e7 + 10;
const int maxm = 5e6 + 5;
bitset<maxn> vis;
int T, n, tot = 0, prime[maxm];
void work(int n) {
    vis[1] = true;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) prime[++tot] = i;
        for(int j = 1; j <= tot && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    work(5000000);
    cin >> T;
    while(T--) {
        cin >> n;
        cout << prime[n] << endl;
    }
}
```

---

## 作者：Fubaogege (赞：0)

#### 题目意思
找出第 $k$ 大的质数。
#### 算法
埃氏筛，区间筛，线性筛。  
总之就是筛法。
#### 思路
把线性筛的 $vis$ 函数改成 `bitset` 存，即可 AC。  

- `bitset::set()` 将整个设为真（`true`）。  
- `bitset::reset(x)` 将第 $x$ 个元素设为假（`false`）。
- `bitset::test(x)` 返回第 $x$ 个元素。

#### 注意
多组数据。
#### 代码
```c
for(int i=2;i<=n;i++){
	if(!a[i])f[r++]=i;
	for(int j=1;j<=r&&i*f[j]<=n;j++){
		a[i*f[j]]=1;
		if(i%f[j]==0)break;
	}
}
```

---

## 作者：Fubaogege (赞：0)

本题的数据还不到 `int`，我们不用担心溢出。

我们可以用**筛**。

- 设 $x$ 是一个合数，无论 $x$ 乘上哪个整数，也都是合数。
- 逐个筛去 $x$ 的倍数。

筛的代码：
```c
    int t=0;
    for(int i=2;i<=n-1;i++) {
    	if(!l[i])f[t++]=i;
        if(t==5000000)return;//最多5000000个 
        for (int j=0;j<t&&i*f[j]<n;j++) {
            l[i*f[j]]=1;if((i%f[j])==0)break;
        }
    }
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/SP6470)

[SPOJ 链接](https://www.spoj.com/problems/TDKPRIME/)

题目大意：

给你一个数 $k$（$1\leq k\leq5\cdot10^6$），让你求出第 $k$ 个质数。本题有 $Q$ 组数据。

思路：

这道题我们可以用[线性筛法](https://oiwiki.org/math/number-theory/sieve/#%E7%BA%BF%E6%80%A7%E7%AD%9B%E6%B3%95)来求解，只不过要使用 [```bitset```](https://oiwiki.org/lang/csl/bitset/) 来求解。

这一题我们只需要用三个 ```bitset``` 中的函数。

1. ```bitset::set()``` 表示将整个 ```bitset``` 中的成员都设为 ```true```。
1. ```bitset::reset(i)``` 表示将 ```bitset``` 中的第 $i$ 个元素设为 ```false```。
1. ```bitset::test(i)``` 表示返回 ```bitset``` 中的第 $i$ 个元素。

我们只需要把线性筛法模板中的 $vis$ 函数改用 ```bitset``` 类存，就可以 AC 这道题。

坑点：

1. 这一题的代码在 Windows 下的 Dev-C++ 上是运行不了的，我们可以使用在 NOI-Linux 下的 Code::Blocks 来进行调试。
1. 本题有 $Q$ 组数据！

上代码：
```cpp
#include <bitset>
#include <iostream>
using namespace std;

bitset<100000001> btst;
int cnt, prime[6000001];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    // 线性筛模板（预处理）
    btst.set();
    btst.reset(1);
    for (int i = 2; i <= 100000000; i++){
        if (btst.test(i)){
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= 100000000; j++){
            btst.reset(i * prime[j]);
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    int q;
    cin >> q;
    while (q--){// 多组数据
        int k;
        cin >> k;
        cout << prime[k] << "\n";
    }
    return 0;
}

```
后记：

本题不用开 ```long long```，第 $5000000$ 个质数也才是 $86028121$，远远没到 ```int``` 的最大值 $2147483647$。

---

## 作者：int233 (赞：0)

第 $5\times10^6$ 个质数也不到 $10^8$，线性筛可以AC。

这里我用的是 bitset 和 快读。

埃式筛大致思路就是找到一个质数，把他的倍数全部筛走。复杂度是 $O(n\log\log n)$ 的。

欧式筛就是优化埃式筛，不重复筛一个数。

Code:

```cpp
#include<iostream>
#include<bitset>
#include<cstdio>
using namespace std;
bitset<100000005> a;
int b[6000005],r;
inline int read(){
    int x(0),f(1);
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
}
void shai(int n){
	a[0]=a[1]=1;
	for(int i=2;i<=n;i++){
		if(!a[i]){
			b[++r]=i;
		}
		for(int j=1;j<=r&&i*b[j]<=n;j++){
			a[i*b[j]]=1;
			if(i%b[j]==0){
				break;
			}
		}
	}
}
int main(){
	int q,k;
	q=read();
	shai(100000000);
	while(q--){
		k=read();
		write(b[k]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

再次喜提最优解。

前置知识：[Wheel Factorization](https://www.luogu.com.cn/blog/Leasier/Wheel-Factorization)，是埃氏筛的优化。

于是这题就解决了，用筛法求出前 $ 5 \times 10^6 $ 个素数，然后直接输出即可。

至于这么做复杂度为什么是对的，根据素数个数的渐进估计 $ \frac{n}{\ln{n}} $，可以发现 $ n \leq 10^8 $，然后优化后的筛法时间复杂度为 $ \mathcal{O}(\frac{n}{\ln{k}}) $，于是可以通过。

代码是借鉴上面模板的，就不贴了。

做完之后可以尝试 [加强版](https://www.luogu.com.cn/problem/SP6489)。

---

## 作者：Insouciant21 (赞：0)

做这题之前可以先看 [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

本题 $1\leq k\leq 5\times10^6$ ，第 $5000000$ 个质数是 $86028121$ ，直接使用 `int` 。

鉴于本题 $1.46G$ 和 $1.26s$ 的时空限制和多组数据，使用筛法。

筛法：如果 $x$ 是合数，那么 $x$ 的倍数也一定是合数。将 $x$ 的倍数逐一筛去，具体可查 [Wiki](https://oi-wiki.org/math/sieve/)

AC 代码

```
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e8) + 1; // 86028121 < 10^8

int n, t, cnt;
bool numlist[maxn];
int prime[5000001];

void prepare(int n) { // 质数筛
    int cnt = 0;
    for (int i = 2; i < n; i++) {
        if (!numlist[i])
            prime[cnt++] = i;
        if (cnt == 5000000) // 筛到最多退出
            return;
        for (int j = 0; j < cnt && i * prime[j] < n; j++) {
            numlist[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> t;
    prepare(maxn);
    for (int i = 1; i <= t; i++) {
        cin >> n;
        cout << prime[n - 1] << endl;
    }
    return 0;
}
```

---

