# 辞書順で何番目？

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_k

長さ $ N $ の順列のうち、$ a $ は辞書順で何番目になるかを求めなさい。

ただし、答えは非常に大きくなるため、$ 1,000,000,007 $ で割った余りを出力しなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
54```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
1```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
5040```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
542869439```

# 题解

## 作者：_Kenma_ (赞：2)

# 解题报告

## 前言

不知道康托展开，独立切掉。

要是我提前知道是板子我就换题了。

还以为是什么好题……

## 思路分析

感觉不是很好 DP，考虑组合计数。

求这个排列的字典序排名，相当于求比它字典序小的排列有几个。

因为字典序是逐位比较的，所以计数应该逐位考虑。这样做是不重不漏的。

所以我们要对这样的排列计数：前 $i-1$ 位相同，在第 $i$ 位比这个排列小的排列数量。答案是每一位的答案之和。

考虑第 $i$ 位以后的位置，任意一个比 $a_i$ 小的数都可以被放在第 $i$ 位，第 $i$ 位以后的位置随意放，不影响答案。

设 $b_i$ 表示第 $i$ 位后面比 $a_i$ 小的数的个数，那么根据上面的组合意义，不难写出和式：

$$ans=\sum_{i=1}^{n} b_i\cdot (n-i)!$$

用树状数组求一下 $b$ 即可。总体复杂度 $O(n\log n)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,ans,a[1000005],fac[1000005];
#define lowbit(i) (i&(-i))
int c[1000005];
void modify(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=k;
	}
}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	ans=1;
	for(int i=n;i>=1;i--){
		ans=(ans+fac[n-i]*query(a[i])%mod)%mod;
		modify(a[i],1);
	}
	cout<<ans;
	return 0;
}
```

## 后记

事实证明有些算法是不需要学的。

提高 OI 水平还是应该以提高思维能力为主，学习新算法为辅。

---

## 作者：ZVitality (赞：1)

本蒟蒻发布的第一篇题解。(求通过)

### [题目传送门](https://www.luogu.com.cn/problem/AT2830)
解决这道题之前，我们必须先了解[康托展开](https://www.luogu.com.cn/blog/zzq6666666666/kang-tuo-zhankai),当然也可以在这里看。

---

先给一个简单的问题：

**$N$ 的序列中，求 $a$ 的字典序排列第几。($a$ 是 $N$ 的某一个全排列)**
- 如果我们使用暴力，我们可以用STL的 $next$_$permunitation()$ 函数，但这个函数的时间复杂度为 $O(n!)$ ，在加上它是STL的函数，自然运行起来是十分地慢。所以，如果你不想TLE或者爆零的话，你就要使用如下的算法——

## 康托展开!

它的做法是像这样的:

**把一个整数X展开为如下的形式：**

**$X$ = $a[n]$ × $(n - 1)!$ + $a[n - 1]$ × $a[n - 2]!$ + ... + $a[i]$   × $a[i - 1]!$ + ... + $a[2]$ × $1!$ + $a[1]$ × $0!$。**

其中 $a[i]$ 就是当前未出现过的元素中排在第几个。

~~总的来说，康托展开式还是十分有用的。~~

---

所以，参考代码如下：

```.cpp
#include <bits/stdc++.h>
using namespace std;

long long a[1000001];
long long Mod = 1000000007;

inline long long Read() {            //快读(不了解的自行模拟一下)
  long long x=0,f = 1;
  char c=getchar();
  for(; c<'0'&&c>'9'; c=getchar())
    if(c == '-')
      f = -1;
  for(; c<='9'&&c>='0'; c=getchar())
    x=(x<<1)+(x<<3)+c-'0';
  return x * f;
}

long long Cantor(int n) {            //康托展开代码
  long long used[1000001] = {0};     //用过的数，记得初始为0(想想是否可以优化)
  long long ans = 0;
  for(int i = n; i >= 1; i--) {
      int No = 0;
      used[a[n - i]] = true;
      for(int j = 0; j < a[n - i]; j++)//找未用过的数
        if(used[j])
          No++;
      ans = (ans + a[n - i] - No) * i % Mod;
  }
  return (ans + 1) % Mod;
}

int main() {
  long long N;
  N = Read();
  for(int i = 1; i <= N; i++)        //输入不解释
    scanf("%lld",&a[i]);
  cout << Cantor(N) << '\n';
  return 0;
}
```
**不过，这道题不用线段树或树状数组优化(寻找已用过的数)是解决不了的。所以，仅供参考，请自行优化。**

希望我的题解可以帮到你。

---

## 作者：happybob (赞：1)

传送门：[AT2830 辞書順で何番目？](https://www.luogu.com.cn/problem/AT2830)。

这个题根洛谷主题库的康托展开板子是一样的，只不过取模的数变成了 $10^9 + 7$。那么我们先给出计算公式：

$\large ans = (\sum_{i=1}^n S_{a_i} \times (n-i)!) + 1$

$\large S_{a_i} = \sum_{j=i}^n \begin{cases}0&a_j \ge a_i\\1&a_j<a_i \end{cases}$

第一个公式 $+1$ 的原因是前面只求出了全排列小于这个排列的个数，$+1$ 才能得到真正的排名。

紧接着考虑复杂度，暴力枚举复杂度 $O(n^2)$，明显过不了。考虑线段树维护，复杂度 $O(n \log n)$。

我们考虑将 $S_{a_i}$ 转化成区间和，我们考虑一开始将整个序列初始化为 $1$，每一次计算到一个数将这个数变成 $0$，用线段树维护就好了！

上代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define int long long

const int N = 1e5 + 5;
int a[N], n, mul[N], ans = 0;

constexpr int MOD()
{
	return 1000000007ll;
}

struct Node
{
	int l, r, sum;
};

Node tree[N << 2];

inline void push_up(int u)
{
	tree[u].sum = tree[u << 1ll].sum + tree[u << 1ll | 1ll].sum;
}

inline void build(int u, int l, int r)
{
	tree[u] = { l, r };
	if (l == r) tree[u].sum = 1;
	else
	{
		int mid = (l + r) >> 1;
		build(u << 1ll, l, mid);
		build(u << 1ll | 1ll, mid + 1, r);
		push_up(u);
	}
}

inline void modify(int u, int x, int v)
{
	if (tree[u].l == x && tree[u].r == x) tree[u].sum = v;
	else
	{
		int mid = (tree[u].l + tree[u].r) >> 1;
		if (x <= mid) modify(u << 1ll, x, v);
		else modify(u << 1ll | 1ll, x, v);
		push_up(u);
	}
}

inline int query(int u, int l, int r)
{
	if (tree[u].l >= l && tree[u].r <= r) return tree[u].sum;
	int mid = (tree[u].l + tree[u].r) >> 1, s = 0;
	if (l <= mid) s += query(u << 1ll, l, r);
	if (r > mid) s += query(u << 1ll | 1ll, l, r);
	return s;
}

signed main()
{
	scanf("%lld", &n);
	mul[0] = 1;
	for (int i = 1; i <= n; i++) mul[i] = mul[i - 1] * i % MOD();
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		ans += ((query(1, 1, a[i]) - 1) * mul[n - i] % MOD()) % MOD();
		ans %= MOD();
		modify(1, a[i], 0);
	}
	printf("%lld\n", (ans + 1) % MOD());
	return 0;
}
```


---

## 作者：王大神——A001 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT2830)

本题在洛谷上有[模板题。](https://www.luogu.com.cn/problem/P5367)

### 思路
本题用了康托展开。

康托展开表达式：$ans=1+\sum\limits_{i=1}^n A\lbrack i\rbrack\times(n-i)!$

康托展开的主要思想是将所有的情况按顺序编一个号，并用简便的算法快速找出它的顺序。

举个例子：1 4 2 3

还没有出现过的数（从小到大）：1 2 3 4

序列第一位是 1，在还没用过的序列中排第一个所以 $ans=ans+0\times3!$

还没有用过的数（从小到大）：2 3 4

序列第一位是 4，在还没用过的序列中排第三个所以 $ans=ans+2\times2!$

还没有用过的数（从小到大）：2 3

序列第一位是 2，在还没用过的序列中排第一个所以 $ans=ans+0\times1!$

还没有用过的数（从小到大）：3

序列第一位是 2，在还没用过的序列中排第一个所以 $ans=ans+0\times0!$

此时 $ans=4$，根据公式再加一即是结果。
#### 康托展开的查找
根据上面的例子，很多人会有疑惑为什么会出现阶乘？

其实是因为全排列问题，例如还剩 3 个数，有 3 个空共有 $3\times2\times1=6$ 种情况。

这也是前面提过的，为了给每种情况一种编号，而我们是通过从小到大的顺序进行编号的，那么我们可以
通过每一位的判断将这个位数之前的所有情况都算出来，就能知道当前的排名，在最后一位求完时，再加一就是当前排列的排名了。

讲得通俗一点就是，例如在自然数中，你要找到 100 这个数的排名，你可以通过所有可能的排序情况，先求出 99 的排名，最后再加 1 就是 100 的排名了。

所以通过每一位确定的数，求比当前序列已经确定的数组成的序列小的序列排名，最后加一就是当前序列的排名，这就是康托展开的求排序方法。

#### 实现查找当前数位上的数在未用过数的序列中的排名
方法一：通过平衡树找当前数排名，注意及时删点（`update`）。

方法二：通过树状数组找到当前数的排名（本篇题解的代码就是这个思路）。
#### 细节优化
- 即时取模。

- 注意数列中数的下标从 0 开始。

- [推荐一下洛谷日报的康托展开。](http://www.360doc.com/content/19/0707/10/5315_847201395.shtml)

### 代码
```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
long long tree[1000005];
int n;
int lowbit(int x){//树状数组快速找"儿子" 
	return x&-x;
}
void update(int x,int y){//更新 
	while(x<=n){
		tree[x]+=y;
		x+=lowbit(x);	
	}
}
long long query(int x){//查询排名 
	long long sum=0;
	while(x){
		sum+=tree[x];
		x-=lowbit(x);	
	}
	return sum;
}
const long long o_o=1e9+7;//取模 
long long k_t[1000005]={1,1};
int a[1000005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){//预处理阶乘 
		k_t[i]=(k_t[i-1]*i)%o_o;
		update(i,1);
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		ans=(ans+((query(a[i])-1)*k_t[n-i])%o_o)%o_o;//康托展开 
		update(a[i],-1);//更新排名 
	}
	printf("%lld",ans+1);
   return 0;
}
```


---

## 作者：迟暮天复明 (赞：1)

双倍经验日！


------------
我们可以通过题目的翻译，准确地知道这个题和[这个题](/problem/P5367)是一个题。这样就可以愉快地把代码抄过来了。

不过注意！模数是不一样的！这个题的模数是 $1e9+7$ 。

于是乎，这道题目就搞定了。

代码么，到[这里](/problem/solution/P5367)~~去抄一个好了~~，在这里提供一个有一百行都是快读快写的代码。

```cpp
#include<stdio.h>
#define reg register
#define ri reg int
#define rep(i, x, y) for(ri i = x; i <= y; ++i)
#define nrep(i, x, y) for(ri i = x; i >= y; --i)
#define DEBUG 1
#define ll long long
#define max(i, j) (i) > (j) ? (i) : (j)
#define min(i, j) (i) < (j) ? (i) : (j)
struct IO {
	#define MAXSIZE (1 << 20)
	#define isdigit(x) (x >= '0' && x <= '9')
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
	#if DEBUG
	#else
		IO() : p1(buf), p2(buf), pp(pbuf) {}
		~IO() {
			fwrite(pbuf, 1, pp - pbuf, stdout);
		}
	#endif
	inline char gc() {
		#if DEBUG
    		return getchar();
		#endif
    	if(p1 == p2)
			p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    	return p1 == p2 ? ' ' : *p1++;
	}
	inline bool blank(char ch) {
    	return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	template <class T>
	inline void read(T &x) {
    	register double tmp = 1;
    	register bool sign = 0;
    	x = 0;
    	register char ch = gc();
    	for(; !isdigit(ch); ch = gc())
    		if(ch == '-') sign = 1;
    	for(; isdigit(ch); ch = gc())
			x = x * 10 + (ch - '0');
    	if(ch == '.')
			for(ch = gc(); isdigit(ch); ch = gc())
        		tmp /= 10.0, x += tmp * (ch - '0');
    	if(sign) x = -x;
	}
	inline void read(char *s) {
		register char ch = gc();
		for(; blank(ch); ch = gc());
		for(; !blank(ch); ch = gc())
			*s++ = ch;
    	*s = 0;
	}
	inline void read(char &c) {
    	for(c = gc(); blank(c); c = gc());
	}
	inline void push(const char &c) {
		#if DEBUG
    		putchar(c);
		#else
    		if(pp - pbuf == MAXSIZE) {
				fwrite(pbuf, 1, MAXSIZE, stdout);
				pp = pbuf;
			}
    		*pp++ = c;
		#endif
	}
	template <class T>
	inline void write(T x) {
    	if(x < 0) {
			x = -x;
			push('-');
		}
    	static T sta[35];
    	T top = 0;
    	do {
			sta[top++] = x % 10;
			x /= 10;
    	}while(x);
    	while(top)
			push(sta[--top] + '0');
	}
	template <class T>
	inline void write(T x, char lastChar) {
    	write(x);
		push(lastChar);
	}
} io;

//以上快读快写,是从OI-WiKi上抄下来的.

long long tree[1000010];
int n, ans, mod = 1000000007;
int lowbit(int x) {return x & -x;}
void add(int x, long long num) {
    while(x <= n) {
        tree[x] += num;
        x += lowbit(x);
    }
}
long long query(int x) {
    long long ans = 0;
    while(x) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

//以上,是树状数组基本操作.

ll jc[1000010] = {1, 1};  //阶乘 
int a[1000010];  //数组 
int main() {
	io.read(n); 
	rep(i, 1, n) {  //预处理阶乘和树状数组
		jc[i] = (jc[i - 1] * i) % mod;
		add(i, 1);
	}
	rep(i, 1, n) {
		io.read(a[i]);
		ans = (ans + ((query(a[i]) - 1) * jc[n - i]) % mod) % mod;  //计算
		add(a[i], -1);  //把a[i]变为0
	}
	io.write(ans + 1, '\n');  //最后+1
    return 0;
}
```

---

## 作者：Shizaki_Crazy_Three (赞：0)

# [题目链接](https://www.luogu.com.cn/problem/AT_chokudai_S001_k)

[康托展开](https://www.luogu.com.cn/problem/P5367)板子题，题面几乎一模一样。

在这里展开讲一下，康托展开一般用于求排列的排名和构建哈希表时的空间压缩。

先给答案

$$
ans=1+\sum_{i=1}^{n} \sum_{j=i}^{n}\left [ a_{j}< a_{i} \right ] \times \left ( n-i \right ) !
$$

我们可以理解为固定前 $i-1$ 个数不动，在剩下的 $n-i+1$ 个数中选择一个小于 $a_{i}$ 的数，其余数可以随便排的方案，即字典序小于数列的方案数，累加起来，再因为排名是从 $1$ 开始，所以再加 $1$。然后用树状数组或线段树维护一下就做完了。
具体实现看代码，时间复杂度 $O(n\log_{}{n})$。

### code

```cpp
int n;
struct BIT{
	int t[N];
	inline void add(int x,int v){
		v%=mod;
		for(;x<=n;x+=lowbit(x)) t[x]=(t[x]+v)%mod;
	}
	inline int query(int x){
		int ans=0;
		for(;x;x-=lowbit(x)){
			ans=(ans+t[x])%mod;
		}
		return ans;
	}
}T;
int a[N];
int fac[N];
inline void solve(){
	read(n);
	for(int i=1;i<=n;++i) read(a[i]);
	fac[0]=1;
	for(int i=1;i<=n;++i) fac[i]=(1ll*fac[i-1]*i)%mod;
	int ans=1;
	for(int i=n;i>=1;--i){
		ans=(ans+1ll*fac[n-i]*T.query(a[i])%mod)%mod;
		T.add(a[i],1);
	}
	write(ans);
}
```

#### 扩展

还有逆康托展开，也可以学一下。

[例题](https://www.luogu.com.cn/problem/UVA11525)

---

