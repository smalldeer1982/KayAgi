# Bear and Prime Numbers

## 题目描述

Recently, the bear started studying data structures and faced the following problem.

You are given a sequence of integers $ x_{1},x_{2},...,x_{n} $ of length $ n $ and $ m $ queries, each of them is characterized by two integers $ l_{i},r_{i} $ . Let's introduce $ f(p) $ to represent the number of such indexes $ k $ , that $ x_{k} $ is divisible by $ p $ . The answer to the query $ l_{i},r_{i} $ is the sum: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385C/835eb9f4aebf62a9178a923ec511d1ceb493d06f.png), where $ S(l_{i},r_{i}) $ is a set of prime numbers from segment $ [l_{i},r_{i}] $ (both borders are included in the segment).

Help the bear cope with the problem.

## 说明/提示

Consider the first sample. Overall, the first sample has 3 queries.

1. The first query $ l=2 $ , $ r=11 $ comes. You need to count $ f(2)+f(3)+f(5)+f(7)+f(11)=2+1+4+2+0=9 $ .
2. The second query comes $ l=3 $ , $ r=12 $ . You need to count $ f(3)+f(5)+f(7)+f(11)=1+4+2+0=7 $ .
3. The third query comes $ l=4 $ , $ r=4 $ . As this interval has no prime numbers, then the sum equals 0.

## 样例 #1

### 输入

```
6
5 5 7 10 14 15
3
2 11
3 12
4 4
```

### 输出

```
9
7
0
```

## 样例 #2

### 输入

```
7
2 3 5 7 11 4 8
2
8 10
2 123
```

### 输出

```
0
7
```

# 题解

## 作者：pythoner713 (赞：5)

虽然这道题有一个可怕的$2\le l_i\le r_i\le2\times10^9$数据范围，但留意数列中的每个数都不大于$10^7$，因此大于$10^7$的质数对答案是没有贡献的（小数不能被大数整除的嘛）。所以只需要求出对于质数$p\le10^7$的$f(p)$值就OK了。

另外注意到题目询问某个区间内的$f(p)$之和，这个可以用前缀和维护，具体步骤如下：

1.输入数列 $a$，统计每个数的出现次数（这里用cont[k]表示k在a中出现了几次，因为count是自带函数就只好用cont）

2.用欧拉筛筛出$10^7$以内的所有质数

3.对于每个质数$p_i$，枚举它的倍数，它所有的倍数在 $a$ 中出现次数之和即为$f(p_i)$的值，即：

$$f(p_i)=\sum_{k=1}^{10^7/p_i}\text{cont}[k\times p_i]$$

4.到这里预处理就完成啦。现在对于每次询问$[l,r]$，二分找到这个区间端点的两个质数$p_l,p_r$，然后输出$\text{sum}[r]-\text{sum}[l-1]$就好了。

```cpp
#include<bits/stdc++.h>
#define nb 1000010
using namespace std;

int n, m, cnt, a[nb], p[nb], t[nb], cont[nb * 10];
// 这里做了一下离散化处理，t[i] = f[p[i]]
bool vis[10 * nb];

void init(){
	for(int i = 2; i <= nb * 10; i++){ //欧拉筛 
		if(!vis[i]) p[++cnt] = i;
		for(int j = 1; j <= cnt && p[j] * i <= nb * 10; j++){
			vis[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
	for(int i = 1; i <= cnt; i++){
		for(int j = 1; j * p[i] <= nb * 10; j++){
			t[i] += cont[j * p[i]]; // 枚举p[i]的倍数 
		}
		t[i] += t[i - 1]; //求出 t 的前缀和 
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		cont[a[i]]++;
	}
	init();
	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		int l, r, L, R;
		scanf("%d %d", &l, &r);
		if(l > p[cnt]){ 
			printf("0\n");
			continue;
			//这里有个小细节：如果询问的区间超出10^7就直接返回0 
		}
		L = lower_bound(p + 1, p + cnt + 1, l) - p;
		R = upper_bound(p + 1, p + cnt + 1, r) - p - 1;
		printf("%d\n", t[R] - t[L - 1]);
	}
	return 0;
}
```


---

## 作者：liangbob (赞：2)

### CF385C 题解

一道比较简单的数论题。

思路也比较明显：预处理出范围内所有 $f(p)$ 的值，然后对于每次询问，计算 $l$ 到 $r$ 中质数 $p$ 的 $f(p)$ 值之和即可。

发现要求区间求和，而且不要求修改，考虑使用前缀和优化之。

现在问题就是怎么预处理出范围内所有 $f(p)$ 的值，

直接每个质数暴力求显然会超时，因此反过来做：枚举序列中每个数，对其分解质因数，对于每个不同的质因数 $p$，$f(p)$ 加一即可。

于是现在难点就在怎么分解出不同的质因数，传统的 $O(\sqrt{m})$ 的分解方法不可行。这里提供一种复杂度近似于 $O(\log_2 m)$ 的方法：

记待分解的数为 $t$，先预处理每个数的最小质因数 $u_i$，然后循环执行如下步骤直到 $u_t$ 为 $0$：

- $r=u_t$，则 $r$ 为本次分解出的质因数。

- 当 $r \mid t$ 时，将 $t$ 除以 $r$。

而对于 $u$ 的预处理，欧拉筛，埃氏筛均可。

然后做完！

#### 关键代码

这里有个细节：要对 $p$ 进行离散化。

1. 二分部分：找到第一个比 $s$ 小的质数的下标

```cpp

int lw_b(int s) //找到第一个比 s 小的质数的下标
{
	int l = 1, r = u;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(p[mid] <= s)	l = mid + 1;
		else r = mid - 1;
	} 
	return r;
}
```

2. 筛法部分：筛并且预处理

```cpp
memset(scz, true, sizeof(scz)); //初始化质数判断数组
scz[1] = 0; //1 不是质数
for(int i = 2;i <= 10000000;i++) //欧拉筛
{
	if(scz[i])
	{
		p[++u] = i;
		f[i] = u; //记录最小质因数
	}
	for(int j = 1;j <= u && i * p[j] <= 10000000;j++)
	{
		scz[i * p[j]] = 0;
		f[i * p[j]] = j; //记录最小质因数
		if(i % p[j] == 0) break;
	}
}  
```

3. 分解质因数与预处理

```cpp
for(int i = 1;i <= n;i++)
{
	int t;
	cin >> t;
	while(f[t]) //分解质因数
	{
		c[f[t]]++;
		int v = f[t];
		while(t % p[v] == 0) t /= p[v];
	}
}
for(int i = 1;i <= u;i++) c[i] += c[i - 1]; //前缀和
```

4. 询问处理部分

```cpp
int l, r;
cin >> l >> r;
int g = lower_bound(p + 1, p + u + 1, l) - p; //计算质数下标
int v = lw_b(r);
cout << c[v] - c[g - 1] << endl; //输出
```


---

## 作者：mulberror (赞：2)

## 题目大意
给你$n$个数$a_i$。  
$f(x)$表示能够被$x$的数的个数。  
其中$x$为质数。  
给你$m$个询问。    
每一个询问让你求解整个区间$i\in[l,r]$内的$f(i)$的和。  
## 题解
第一眼开题感觉没有什么想法。  
但是可以这样想一下。    
首先题目可以承受$nlogn$的时间复杂度。    
$nlogn$的复杂度，又跟质数有关，我们可以想到埃筛和欧筛，但是这一道题目不可以用欧筛，原因加下来会讲解。  
回忆一下欧筛和埃筛的特点。   
欧筛的时间复杂度近似$O(n)$，但是无法对于每一个合数求出最小的质数，他只能实现用一个质数筛掉最小他需要筛掉的合数。  
埃筛虽然时间复杂度比较高，但是可以将一个合数中的所有质因数都遍历一遍。    
模拟一下可以发现，在一个质数更新一个合数的时候，就说明这个合数是这个质数的$k$倍。  
就对我们的答案有贡献。  
但是很容易想到这种做法可能有问题。  
也就是质因数的$k$次方。  
但是不需要考虑这种问题。    
模拟一下，假设我们需要处理$49$这个数，那么$7$会更新$49$一次，但是$49$也会更新自己一次。答案依旧是对的。    
接下来就是询问的问题，这个只需要前缀和处理一下就可以了。    
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IOstream {
	#define gc getchar
	template <typename T>
	inline void read(T &x) {
		x = 0; T fl = 1; char c = 0;
		for (; c < '0' || c > '9'; c = gc())
			if (c == '-') fl = -1;
		for (; c >= '0' && c <= '9'; c = gc())
			x = (x << 1) + (x << 3) + (c ^ 48);
		x *= fl;
	}
	#undef gc
} using namespace IOstream;
const int N = 1e7 + 10;
bool isprime[N];
int d[N], sum[N];
int pcnt, n, m;
int main() {
	read(n);
	for (int i = 1, x; i <= n; i ++) read(x), d[x] ++; 
	for (int i = 2; i < N; i ++) {
		sum[i] = sum[i - 1];
		if (isprime[i]) continue;
		for (int j = 1; j * i < N; j ++) {
			sum[i] += d[j * i];  
			isprime[i * j] = 1; 
		}
	}
	read(m);
	while (m --) {
		int l, r; 
		read(l); read(r); 
		l --; 
		l = min(l, N - 2);
		r = min(r, N - 2);
		printf("%d\n", sum[r] - sum[l]);
	}
	return 0;
}
```

---

## 作者：da32s1da (赞：1)

暴力搞出$10^7$的素数，然后前缀和+二分回答询问
```
#include<cstdio>
#include<algorithm>
using namespace std;
inline void rad(int &_){
    static char ch;
    while(ch=getchar(),ch<'0'||ch>'9');_=ch-48;
    while(ch=getchar(),ch<='9'&&ch>='0')_=_*10+ch-48;
}
const int N=1e7+50;
int n,m,x,y,a[N],b[N/10];
bool vis[N];
int pri[N/10],cnt;
void pre(){
	pri[++cnt]=2;
	int qwq;
	for(int i=3;i<N;i+=2)
	if(!vis[i]){
		pri[++cnt]=i;qwq=i<<1;
		for(int j=i;j<N;j+=qwq)
		if(!vis[j])vis[j]=true;
	}
}
int main(){
	pre();rad(n);//搞出素数
	for(int i=1;i<=n;++i)rad(x),++a[x];
	for(int i=1;i<=cnt;++i)
	for(int j=pri[i];j<N;j+=pri[i])
	b[i]+=a[j];
	for(int i=1;i<=cnt;i++)b[i]+=b[i-1];
    //前缀和
	rad(m);
	for(int i=1;i<=m;++i){
		rad(x);rad(y);
		printf("%d\n",b[lower_bound(pri+1,pri+cnt+1,y+1)-pri-1]-b[lower_bound(pri+1,pri+cnt+1,x)-pri-1]);
        //二分质数，回答询问
	}
}
```

---

## 作者：longlong_int (赞：0)

既然 $f(p)$ 求的是 $x$ 序列中能被 $p$ 整除的个数，那我们不如就反向推导，枚举 $p$ 的倍数，然后 `f[p]++` 就可以了。

注意**枚举 $\textbf{\textit{p}}$ 的个数**。这是不是让你想到了筛法？没错。我们在筛出质数 $p$ 的同时计算 $f(p)$，后面加和时前缀和处理即可。

我用的是预处理大法，运行次数稳定在 $O(5 \times 10^7)$ 左右。

代码：

```cpp
#include <bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;

const int N = 1e7 + 10;
int arr[N], cnt[N], sum[N];
bool notprime[N];
ll f[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		cnt[arr[i]]++;
	}
	for (int i = 2; i <= N; i++)
	{
		if (notprime[i]) continue;
		for (int j = i; j <= N; j += i)
		{
			f[i] += cnt[j];
			notprime[j] = true;
		}
	}
	
	for (int i = 1; i <= N; i++) sum[i] = sum[i - 1] + f[i];

	int m;	
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int l, r;
		cin >> l >> r;
		l = min(l, N);
		r = min(r, N);
		cout << sum[r] - sum[l - 1] << endl;
	}
	return 0;
}

```

---

## 作者：ZLCT (赞：0)

# CF385C Bear and Prime Numbers
## 题目翻译
给定一个长度为 $n$ 的序列，定义 $f_p=\sum\limits_{i=1}^{n}[p|a_i]$。也就是序列中能被 $p$ 整除的个数。\
现在有 $Q$ 次询问，每次询问给定值域区间 $l,r$，问其中所有质数的 $f$ 值之和。
## solution
观察到无论是哪次询问，只要包含质数 $x$，那 $x$ 的贡献都一样。这就启示我们可以预处理出每个质数的贡献。\
但是枚举每一个质数并枚举每一个 $a_i$ 判断是否整除时间复杂度太大了，我们考虑优化。\
注意到其实每个数 $x$ 最多能被表示为不超过 $\log x$ 个质数的积，于是我们可以反过来用每个 $a_i$ 去找能贡献哪些质数 $p$。\
这里如果暴力枚举因数并暴力判断是否是质数，那么一个数复杂度是 $O(\sqrt{V}^2)=O(V)$，这是不能接受的。\
我们考虑进一步优化。\
由于 $x\le 10^7$，所以我们可以预处理出哪些是质数，这样复杂度可以少一个 $\sqrt{V}$。进一步我们在线性筛或者埃氏筛的时候可以预处理出 $x$ 的一个质因子，这样复杂度就可以变成 $\log V$。\
那么接下来我们考虑如何查询。\
这有两种方法，第一种就是直接线段树维护每一个质数的贡献，那么查询 $l,r$ 区间的贡献和即可。\
但是注意到我们没有修改操作，所以我们可以直接维护前缀和，令 $sum_i$ 表示前 $i$ 个质数的贡献，每次查询先在筛出来的质数中二分出 $l,r$ 区间最小和最大的质数，接下来前缀和查询即可。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+666;;
const int maxn=1e7;
int n,a[N],prime[N],sum[N],cnt,d[maxn+666],mp[maxn+666];
bool notprime[maxn+666];
void init(){
    notprime[1]=1;
    for(int i=2;i<=maxn;++i){
        if(!notprime[i]){
            prime[++cnt]=i;
            mp[i]=cnt;
            d[i]=i;
        }
        for(int j=1;j<=cnt&&prime[j]<=maxn/i;++j){
            notprime[prime[j]*i]=1;
            d[prime[j]*i]=prime[j];
            if(i%prime[j]==0)break;
        }
    }
}
void make(int x){
    while(x!=1){
        int dd=d[x];
        while(x%dd==0)x/=dd;
        sum[mp[dd]]++;
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        make(a[i]);
    }
    for(int i=1;i<=cnt;++i){
        sum[i]+=sum[i-1];
    }
    int Q;cin>>Q;
    while(Q--){
        int l,r;cin>>l>>r;
        if(l>maxn){
            cout<<0<<'\n';
            continue;
        }
        if(r>maxn)r=maxn;
        l=lower_bound(prime+1,prime+1+cnt,l)-prime-1;
        r=upper_bound(prime+1,prime+1+cnt,r)-prime-1;
        cout<<sum[r]-sum[l]<<'\n';
    }
    return 0;
}
```

---

## 作者：Terac (赞：0)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF385C)

## 题意

给出一个长度为 $n$ 的序列 $a$，定义 $f(p)=\sum\limits_{i=1}^n\left[p|a_i\right]$，$m$ 次询问，求 $\sum\limits_{i=l}^r f(i)\left[i\in\mathbf{Prime}\right]$。

数据范围：$1\le n\le10^6,1\le m\le 5\times 10^4,1\le a_i\le10^7,1\le l\le r\le2\times 10^9$

## 题解

令 $cnt_i=f(i)$。

因为 $a_i\le10^7$，所以 $l,r$ 超过这个范围便没意义了。

令 $mn_i=\min\{k\in\mathbf{Prime} \land k|i\}$，线性筛搞出来。

扫一遍原序列，每次令 $a_i\gets \frac{a_i}{mn_{a_i}}$，并加在 $cnt_{mn_{a_i}}$ 上，因为 $mn_{a_i}\ge2$，所以最多 $\log_{a_i}$ 次就除完，复杂度 $O(n\log a_i)$。

令 $sum_i=\sum\limits_{i=1}^i cnt_i$，查询 $\left[l,r\right]$ 答案即为 $sum_r-sum_{l-1}$。

时间复杂度 $O(n\log a_i+q)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, W = 1e7 + 10;
int prime[W], mn[W], cnt;
bitset<W> isp;
void sieve(int n) {
	mn[1] = isp[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!isp[i]) prime[++cnt] = i, mn[i] = i;
		for(int j = 1; j <= cnt && prime[j] * i <= n; j++) {
			isp[prime[j] * i] = 1;
			if(!(i % prime[j])) {
				mn[prime[j] * i] = prime[j];
				break;
			}
			mn[prime[j] * i] = prime[j];
		}
	}
}
int n, m;
ll f[W];
int main() {
	sieve(1e7);
	scanf("%d", &n);
	for(int i = 1, a; i <= n; i++) {
		scanf("%d", &a);
		while(a > 1) {
			int t = mn[a];
			f[t]++;
			while(!(a % t)) a /= t;
		}
	}
	for(int i = 1; i <= 1e7; i++)
		f[i] += f[i - 1];
	scanf("%d", &m);
	int l, r;
	while(m--) {
		scanf("%d%d", &l, &r);
		r = min(10000000, r);
		if(l > r) {
			puts("0");
			continue;
		}
		printf("%lld\n", f[r] - f[l - 1]);
	} 
	return 0;
} 
```


---

## 作者：TachibanaKanade (赞：0)

首先，显而易见地，埃氏筛筛出 $10^7$ 次方内所有的素数。

$l,r$ 那么大不用管，因为一个数一定不会整除比它大的数。

筛素数的同时顺带预处理出在 $a$ 数列中能被该数整除的数的个数，并维护前缀和

对于每次询问，可以前缀和 $O(1)$ 做。

然后就是题目的输入量比较大，对于大常数选手可能超时，最好用快读。

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 10;
int n, q, a, b, pr[maxn], C[maxn], t[maxn];
int ping(int x) { return x * x; }
namespace in{
    #ifdef faster
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    #else
    inline int getc(){return getchar();}
    #endif
    template <typename T>inline void read(T& t){
        t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
        while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
    }
    template <typename T, typename... Args> inline void read(T& t, Args&... args) { read(t); read(args...); }
}
signed main() {
    in::read(n);
    while (n--) {
        int tmp;
        in::read(tmp);
        t[tmp]++;
    }
    for (int i = 2; i < maxn; i++) {
        if (pr[i]) C[i] = C[i - 1];
        else {
            for (int j = 1; i * j < maxn; j++) {
                pr[i * j] = 1;
                C[i] += t[i * j];
            }
            C[i] += C[i - 1];
        }
    }
    in::read(q);
    while (q--) {
        in::read(a, b);
        printf("%d\n", (C[min(b, maxn - 10)] - C[min(a - 1, maxn  - 10)]));
    }
}
```


---

## 作者：泠小毒 (赞：0)

# Bear and Prime Numbers

给你一串数列a.对于一个质数p,定义函数f(p)=a数列中能被p整除的数的个数.给出m组询问l,r,询问[l,r]区间内所有素数p的f(p)之和.

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190429/)

## 解法

可以预处理出所有质数的答案，具体就是把a数列分解质因数

之后可以前缀和搞一下，O(1)询问即可，不知道楼上奆佬为什么要二分qwq

tips：l和r需要缩小成1e7的数量级，但是当l>maxx时，答案直接是0

## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,maxx,a[1000010],b[10000010],l,r,v[10000010],pr[1000010],cnt;
long long ans[10000010];
void get_prime(int s)
{
	for(int i=2;i<=s;i++)
	{
		if(!v[i])pr[++cnt]=i,v[i]=i;
		for(int j=1;j<=cnt;j++)
		{
			if(pr[j]>v[i]||s/pr[j]<i)break;
			v[i*pr[j]]=pr[j];
		}
	}
}
void calc(int s)
{
	while(s!=1)
	{
		ans[v[s]]++;
		int k=v[s];
		while(s%k==0&&k!=1)s/=k;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),maxx=max(maxx,a[i]);
	get_prime(maxx);
	for(int i=1;i<=n;i++)
		calc(a[i]);
	for(int i=1;i<=maxx;i++)ans[i]+=ans[i-1];
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&l,&r),r=min(r,maxx);
		if(l>r)puts("0");
		else printf("%lld\n",ans[r]-ans[l-1]);
	}
	return 0;
}
```

---

