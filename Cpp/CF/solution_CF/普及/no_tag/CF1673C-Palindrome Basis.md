# Palindrome Basis

## 题目描述

You are given a positive integer $ n $ . Let's call some positive integer $ a $ without leading zeroes palindromic if it remains the same after reversing the order of its digits. Find the number of distinct ways to express $ n $ as a sum of positive palindromic integers. Two ways are considered different if the frequency of at least one palindromic integer is different in them. For example, $ 5=4+1 $ and $ 5=3+1+1 $ are considered different but $ 5=3+1+1 $ and $ 5=1+3+1 $ are considered the same.

Formally, you need to find the number of distinct multisets of positive palindromic integers the sum of which is equal to $ n $ .

Since the answer can be quite large, print it modulo $ 10^9+7 $ .

## 说明/提示

For the first testcase, there are $ 7 $ ways to partition $ 5 $ as a sum of positive palindromic integers:

- $ 5=1+1+1+1+1 $
- $ 5=1+1+1+2 $
- $ 5=1+2+2 $
- $ 5=1+1+3 $
- $ 5=2+3 $
- $ 5=1+4 $
- $ 5=5 $

For the second testcase, there are total $ 77 $ ways to partition $ 12 $ as a sum of positive integers but among them, the partitions $ 12=2+10 $ , $ 12=1+1+10 $ and $ 12=12 $ are not valid partitions of $ 12 $ as a sum of positive palindromic integers because $ 10 $ and $ 12 $ are not palindromic. So, there are $ 74 $ ways to partition $ 12 $ as a sum of positive palindromic integers.

## 样例 #1

### 输入

```
2
5
12```

### 输出

```
7
74```

# 题解

## 作者：JCLinux (赞：10)

**题目大意：**

给你一个正整数  $n$ 

问你一共有多少种方法把 $n$ 拆成回文数的加和。

**思路：**

把数拆成一系列数的和的方案数，听起来好熟悉啊。

这应该算是一个经典的动态规划问题了吧。

但这次要我们拆成的是回文数，那我们就预先筛选出从 $1$ 到 $40000$ 的所有回文数，把这些作为“物品”，往完全背包里面装。

我跑了一下，$1$ 到 $40004$ 一共有 $499$ 个回文数，$499*40000$

时间复杂度绰绰有余。

还有一点需要注意的是，这个题的 $t$ 组询问，没必要每一次询问都重新计算一遍，只需要预处理出 $1$ 到 $40000$ 的答案就好，每次询问 $O(1)$ 输出。

**上代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int t, n;
int dp[40005];
vector<int>hw;//存储的回文数
inline bool ish(int x)//判断是不是回文数
{
	vector<int> c;//记录数的每一位
	while(x)
	{
		c.push_back(x % 10);
		x /= 10;
	}
	for(int i = 0; i < (int)c.size(); i++) if(c[i] != c[ (int)c.size() - i - 1 ]) return false;
	return true;
}
void init()
{
	dp[0] = 1;
	for(int i = 1; i <= 40004; i++) if(ish(i)) hw.push_back(i);
	for(auto x : hw)
		for(int i = x; i <= 40004; i++)
			dp[i] = (dp[i] + dp[i - x]) % mod;
}
signed main()
{
	cin.sync_with_stdio(false);
	cin.tie(0);
	init();
	cin >> t;
	while(t--)
	{
		cin >> n;
		cout << dp[n] << '\n';
	}
}

```

**补充：**

如果你了解这种计数类的 dp，这道题应该不难。来看题解应该说明你可能不是很了解数的拆分的 dp

那接下来我就详细说一说这种类型的 dp 吧。

首先我们需要一个二维的 dp 数组。

$dp[i][j]$ 的含义是：用前 $i$  个数 组合成 $j$ 的方案数。

是不是和背包问题的转移方程有一点像。

紧接着，如果 $j$ 大于当前的回文数，那么，答案的组成就分成两部分：拿和不拿。

即： $dp[ i ][ j ] =  dp[ i ][ j-hw ] + dp[ i-1 ][ j ] $

$hw$ 的意思是回文数。

需要特别注意的地方是：等号后面第一个式子是 $i$ 而不是 $i-1$，因为每个回文数可以重复拿。如果每个回文数限定只能拿一次，那么就应该改成 $i-1$

至此，我们能够发现，这个转移方程和背包问题非常的类似，只不过背包问题是取最大，而这个计数问题是求和。


---

## 作者：wwwidk1234 (赞：2)

[洛谷题目传送门！](https://www.luogu.com.cn/problem/CF1673C)

[CodeForces 题目传送门！](https://codeforces.com/problemset/problem/1673/C)

[在我的博客上查看这篇文章？](https://wwwidk1234.github.io/)

前置知识：[背包类型动态规划](https://oi-wiki.org/dp/knapsack/)。

## 题目大意

给你一个正整数 $n$，找出将 $n$ 表示为正回文整数和的不同方式的数量。

## 题目分析

这是一道典型的**完全背包**问题，考虑使用**动态规划**求解。

可以把回文数打表写进程序里面，打表器稍后会给出。

设 $f_{i,j}$ 表示用前 $i$ 个回文数组成 $j$ 的方案数，状态转移方程如下：
$$
f_{i,j}=f_{i,j-a}+f_{i-1,j}
$$
加个滚动数组优化，方程就变成了：
$$
f_j=f_{j-a}+f_j
$$
最后输出答案即可。

## 解题过程

首先写个回文数打表的程序，如下：

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
inline int read()
{
	int suffm=0,sym=1;
	char chr=getchar();
	while(chr<'0'||chr>'9'){if(chr=='-') sym=-1;chr=getchar();}
	while(chr>='0'&&chr<='9'){suffm=(suffm<<3)+(suffm<<1)+(chr^48);chr=getchar();}
	return suffm*sym;
}
inline void write(int suffm)
{
	if(suffm<0){putchar('-');suffm=-suffm;}	
	if(suffm>9) write(suffm/10);
	putchar(suffm%10+48);
}
inline bool judge(int x) //判断x是不是回文数
{
	string s=to_string(x);
	const int len=s.length();
	for(int i=0,j=len-1;i<len&&j>=0;i++,j--)
		if(s[i]!=s[j]) return false;
	return true;
}
int cnt=1;
const int N=4e4+12;
signed main()
{
	printf("const int hw[]={1");
	for(int i=2;i<=N;i++)
	{
		if(judge(i)) {cnt++;printf(",%d",i);}
	}
	puts("}");
	cout<<"count="<<cnt<<endl;
	return 0;
}
//给CF1673C用的
```

把回文数写进程序之后，去写 DP。

```cpp
f[0]=1;
for(int i=0;i<HWS;i++)
	for(int j=hw[i];j<=MAXN;j++)
		f[j]=(f[j]+f[j-hw[i]])%mod;
```

然后输入数据每一个 $n$，输出对应的答案 $f(n)$ 即可。

```cpp
T=read();
while(T--) write(f[read()]),putchar('\n');
```

## 完整代码

因为回文数数组有点长，完整数据可运行回文数打表程序（上文已给出）获得。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int hw[]={1,2,3,4,5,......,39793,39893,39993,40004};
inline int read()
{
	int suffm=0,sym=1;
	char chr=getchar();
	while(chr<'0'||chr>'9'){if(chr=='-') sym=-1;chr=getchar();}
	while(chr>='0'&&chr<='9'){suffm=(suffm<<3)+(suffm<<1)+(chr^48);chr=getchar();}
	return suffm*sym;
}
inline void write(int suffm)
{
	if(suffm<0){putchar('-');suffm=-suffm;}	
	if(suffm>9) write(suffm/10);
	putchar(suffm%10+48);
}
int T;
const int mod=1e9+7;
const int MAXN=4e4+10;
const int HWS=499;
int f[MAXN];
signed main()
{
	f[0]=1;
	for(int i=0;i<HWS;i++)
		for(int j=hw[i];j<=MAXN;j++)
			f[j]=(f[j]+f[j-hw[i]])%mod;
	
	T=read();
	while(T--) write(f[read()]),putchar('\n');
	return 0;
}
```



---

## 作者：NFGase (赞：1)

这道题非常板，如你所见，大概思路是打表回文数加上完全背包求方案数，但是需要注意取余问题。

从英文题面上（题目翻译没有给出数据范围）可以看到 $1 \leq n \leq 4 \cdot 10 ^ {4}$，所以只要用完全背包来预处理这一范围即可。如果你还是不懂，可以去搜完全背包字样并学习该算法。

一些题解中的写法并不显然，所以我将代码写的更加贴近板子（虽然老师写的不显然）。

```cpp
#include <iostream>
#include <vector>
namespace io{
    template <typename T> inline void read(T& x){x = 0; bool f = false; char ch = getchar(); while(ch < '0' || ch > '9'){if(ch == '-') f = !f; ch = getchar();}while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();} x = (f ? -x : x); return;}
    template <typename T, typename... Args> inline void read(T& x, Args&...x_){read(x), read(x_...);}
    template <typename T> inline void put(T x){if(x < 0) putchar('-'), x = -x; if(x > 9) put(x / 10); putchar(x % 10 + '0'); return ;}
    template <typename T> inline void write(T x){put(x);}
    template <typename T, typename... Args> inline void write(T x, Args...x_){write(x), write(x_...);}
    inline void newb(){putchar(' ');}
    inline void newl(){puts("");}
}
namespace code{
    int t, dp[1000001];
    std::vector <int> vec;
    const int mod = 1e9 + 7;
    bool palin(std::string s){
        int len = s.length();
        for(int i = 0; i < len; i++) if(s[i] != s[len - i - 1]) return false;
        return true;
    }
    int main(){
        for(int i = 1; i <= 40000; i++) if(palin(std::to_string(i)) == true) vec.push_back(i);
        dp[0] = 1;
        for(int i = 0; i < vec.size(); i++) for(int j = vec[i]; j <= 40000; j++) dp[j] = (dp[j] + dp[j - vec[i]]) % mod;
        io::read(t);
        while(t--){
            int x;
            io::read(x);
            io::write(dp[x]);
            puts("");
        }
        return 0;
    }
}
int main(){
    code::main();
    return 0;
}
```

[记录](https://www.luogu.com.cn/record/140037937)

---

## 作者：yeshubo_qwq (赞：1)

思路：

首先求出所有回文数。

判断很简单，将这个数倒过来的数求出来，与原数判断是否相等即可。

然后背包预处理出 $1 \sim 40000$ 的方案数。

注意每个数可以用不止一次，要跑完全背包。

代码：

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int dp[40005],i,j,x,T,h[505],N;
bool check(int x){
	int y=x,z=0;
	while (x!=0) z=(z<<1)+(z<<3)+x%10,x/=10;
	return y==z;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for (i=1;i<=40000;i++)
		if (check(i)) h[++N]=i;
	dp[0]=1;
	for (i=1;i<=N;i++)
		for (j=h[i];j<=40000;j++)
			dp[j]=(dp[j]+dp[j-h[i]])%mod;
	cin>>T;
	while (T--) cin>>x,cout<<dp[x]<<'\n';
	return 0;
}
```


---

## 作者：Vct14 (赞：0)

duel 到了这题，写一发题解。

假设 $k$ 是一个可以由正回文整数之和的数，$h$ 是一个回文数，那么 $k+h$ 也是一个可以由正回文整数之和的数。

于是考虑 dp。设 $dp_i$ 表示用正回文整数之和表示 $i$ 的方法数，那么 $dp_i=dp_{i-h}+dp_i$，其中 $h$ 是回文数。

因此我们预处理出所有回文数，然后对于每一个回文数 $h$，都遍历 $dp$ 数组并使得 $dp_i$ 加上 $dp_{i-h}$，最后对于每一组询问直接 $O(1)$ 回答即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7;
const int N=4e4+5;
int dp[N],h[N];

bool ispal(int x){
	int num[7]={0};
	int ss=0;
	while(x){
		num[++ss]=x%10;
		x/=10;
	}
	for(int i=1; i<=ss; i++) if(num[i]!=num[ss-i+1]) return false;
	return true;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int s=0;dp[0]=1;
	for(int i=1; i<N; i++) if(ispal(i)) h[++s]=i;
	for(int c=1; c<=s; c++) for(int i=h[c]; i<N; i++) dp[i]=(dp[i]+dp[i-h[c]])%mod;
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		cout<<dp[n]<<"\n";
	}
	return 0;
}
```

---

## 作者：Lvlinxi2010 (赞：0)

题目要求我们求出将 $n$ 拆分为回文数的和的方案数，那提到拆分，我们就会想到动态规划中的背包问题，根据题意，一个回文数可以无限制的重复使用，那么这道题属于完全背包问题。

假设我们已经预处理好了回文数，那么 dp 部分就是完全背包的板子。
```cpp
f[0]=1;
FL(i,1,l){//这里的l是回文数的个数
	FL(j,a[i],MAXN-1){
		f[j]=(f[j]+f[j-a[i]])%mod;
	}
}
```
那么如何处理回文数呢？我们看到数据范围 $n(1\le n \le 40000)$，那么我们可以直接对 $1$ 到 $40000$ 的数进行预处理，拆位判断回文，再将结果保存起来即可。
```cpp
bool check(int x){
	int s[10],tot=0;
	while(x){
		s[++tot]=x%10;
		x/=10;
	} 
	FL(i,1,tot){
		if(s[i]!=s[tot-i+1]) return 0;
	}
	return 1;
}
```
最后对每组询问输出答案即可。

附上完整代码：
```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int mod = 1e9 + 7;
const int MAXN = 4e4 + 10;
int f[MAXN],a[MAXN],l=0;
bool check(int x){
	int s[10],tot=0;
	while(x){
		s[++tot]=x%10;
		x/=10;
	} 
	FL(i,1,tot){
		if(s[i]!=s[tot-i+1]) return 0;
	}
	return 1;
}
void calc(){
	FL(i,1,MAXN-1){
		if(check(i)){
			a[++l]=i;
		}
	}
	f[0]=1;
	FL(i,1,l){
		FL(j,a[i],MAXN-1){
			f[j]=(f[j]+f[j-a[i]])%mod;
		}
	}
}
int main(){
	int t;
	scanf("%d",&t);
	calc(); 
	while(t--){
		int n;
		scanf("%d",&n);
		printf("%d\n",f[n]);
	}
} 
```


---

## 作者：luogu_gza (赞：0)

复杂度 $O(\max\{ n\}+T)$。

考虑预处理出所有的回文数后，进行完全背包求方案数。

回文数怎么预处理呢？

我们考虑枚举回文数的位数，然后直接枚举对应位的数字。

$1$ 位回文数的形式为 `a`。

$2$ 位回文数的形式为 `aa`。

$3$ 位回文数的形式为 `aba`。

$4$ 位回文数的形式为 `abba`。

$5$ 位回文数的形式为 `abcba`。

定义：$f[i]$ 为 $n=i$ 时的答案。

转移方程：`f[j]+=f[j-a[i]]`，此处 $a$ 为所有的回文数。

答案： $f[n]$。

代码（有注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MT int TTT=R;while(TTT--)
#define pc putchar
#define R read()
#define fo(i,a,b) for(register int i=a;i<=b;i++)
#define rep(i,a,b) for(register int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
int read()
{
    int x=0;
    char ch=getchar();
    bool f=0;
    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f) x=-x;
    return x;                                       
}
template<typename T> inline void write(T x)
{
    if(x<0)
    {
        pc('-');
        x=-x;
    }
    if(x>9) write(x/10);
    pc(x%10+'0');
}
const int N=40010,mod=1e9+7;
int a[N],cnt;
int f[N];
signed main(){
    fo(i,1,9) a[++cnt]=i,a[++cnt]=11*i;//1位与2位回文数
    fo(i,1,9) fo(j,0,9) a[++cnt]=i*100+j*10+i,a[++cnt]=i*1000+j*100+j*10+i;//3位与4位回文数
    fo(i,1,9) fo(j,0,9) fo(k,0,9) a[++cnt]=i*10000+j*1000+k*100+j*10+i;//5位回文数
    f[0]=1;
    fo(i,1,cnt) if(a[i]!=0) fo(j,a[i],N-10) f[j]=(f[j]+f[j-a[i]])%mod;//背包
    MT
    {
        int n=R;
        write(f[n]),puts("");//O(1)的查询
    }
}
```

---

## 作者：RP_INT_MAX (赞：0)

## $\tt Solution$

背包 dp 典题。

考虑先打出 $4 \times 10^4$ 以内的回文数表。然后 dp。

设 $f(i)$ 表示将 $i$ 拆分成回文数的和的方案数。注意同一个回文数可以重复用。

然后就是完全背包板子。$f(i)=\sum f(i-num_j)$。

由于数据组数较大，先预处理 $4 \times 10^4$ 以内的答案，$O(1)$ 回答询问。

## $\tt Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
int t;
ll n,p[1100],ps,f[100010];
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	for(int i=1;i<10;++i) {
		p[++ps]=i; // 一位回文数
		p[++ps]=i*11; // 两位回文数
	}
	for(int i=1;i<10;++i)
		for(int j=0;j<10;++j) {
			p[++ps]=i*101+j*10; // 三位回文数
			p[++ps]=i*1001+j*110; // 四位回文数
		}
	for(int i=1;i<10;++i)
		for(int j=0;j<10;++j)
			for(int k=0;k<10;++k)
				p[++ps]=i*10001+j*1010+k*100; // 五位回文数
	sort(p+1,p+1+ps);
	f[0]=1;
	for(int i=1;i<=ps;++i)
		for(int j=p[i];j<100001;++j)
			(f[j]+=f[j-p[i]])%=mod;
	cin>>t;
	while(t--) {
		cin>>n;
		cout<<f[n]<<endl;
	}
	return 0;
}
```

---

## 作者：JS_TZ_ZHR (赞：0)

## 题意：

给定 $n$，求将 $n$ 拆分为回文数的和的方案数。方案不计顺序。

## 题解：

考虑到回文数的个数并不多，直接大力 dp。设 $f_{i,j}$ 表示讲 $i$ 拆分为回文数的和，并且最大的数是第 $j$ 小的回文数的方案数。对每个 $f_i$ 求前缀和 $pre_{i,j}=\sum\limits_{p=1}^{j}f_{i,p}$ 的话，$f_{i,j}$ 就等于 $pre_{i-a_j,j}$。这里 $a_j$ 指第 $j$ 小的回文数。

```cpp
#include<bits/stdc++.h>
#define N 40005
#define mod 1000000007
using namespace std;
int n,f[N][505],cnt,T,a[N],res[N],ans,pre[N][505];
bool check(int x){
	int sum[15],tot=0;
	while(x)sum[++tot]=x%10,x/=10;
	for(int i=1;i<=tot;i++)if(sum[i]!=sum[tot-i+1])return 0;
	return 1;
}
int main() {
	cin>>T;
	for(int i=1;i<=N;i++)if(check(i))a[++cnt]=i;
	for(int i=0;i<=cnt;i++)pre[0][i]=1;
	for(int i=1;i<=40000;i++){
		for(int j=1;j<=cnt&&a[j]<=i;j++)f[i][j]=pre[i-a[j]][j];
		for(int j=1;j<=cnt;j++)pre[i][j]=pre[i][j-1]+f[i][j],pre[i][j]%=mod;
		res[i]=pre[i][cnt];
	}
	while(T--){
		cin>>n;
		cout<<res[n]<<endl; 
	} 
}
```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1673C)

CF 也会出这种板子吗……

题意：多组数据，每次给定 $n$，求有多少种不同的拆分方式，把 $n$ 拆分成若干个回文数的和，答案对 $10^9+7$ 取模。

首先 $n \le 4 \times 10^4$，打表不难发现 $\le n$ 的回文数只有 $498$ 个。

然后问题转化为在一堆数里面凑出 $n$ 的方案数是多少。

计数不重不漏，设 $dp_i$ 表示凑出 $i$ 的方案数显然是无法转移的，转移过程中会重复计算。

设 $dp_{i,j}$ 表示只用前 $j$ 个回文数凑出 $i$ 的方案数，每次枚举所有回文数进行转移，于是有 $dp_{i,j}=dp_{i,j-1}+dp_{i-a_j,j}$。

为什么是 $dp_{i-a_j,j}$ 而不是 $dp_{i-a_j,j-1}$？显然如果是后者的话，那么转移的时候肯定会重复计算。

边界 $dp_{0,j}=1$。

时间复杂度 $O(498n)$。

```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
const int mod=1e9+7;
ll t,n,cnt;
int vis[35],pos[35];
ll a[1005],dp[40005][505];
queue<int> q;
bool check(int n)
{
	int sum=0,cnt=0,lsbl=n;
	while(n)
	{
		pos[++cnt]=n%10;
		n/=10;
	}
	for(ri i=1;i<=cnt;i++)
		sum+=pos[i]*pow(10,cnt-i);
	if(sum==lsbl)
		back 1;
	back 0;
}
int main()
{
	t=read();
	a[++cnt]=0;
	for(ri i=1;i<=40000;i++)
		if(check(i))
			a[++cnt]=i;
	for(ri i=1;i<=cnt;i++)
		dp[0][i]=1;
	for(ri i=1;i<=40000;i++)
		for(ri j=1;j<=cnt;j++)
		{
			if(i>=a[j])
				dp[i][j]=(dp[i][j]+dp[i-a[j]][j])%mod;
			dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
		}		
	while(t--)
	{
		ll ans=0;
		n=read();
		cout<<dp[n][cnt]<<"\n";
	}
	back 0;
}
```

---

## 作者：Arghariza (赞：0)

考虑预处理 $4\times 10^4$ 以内的答案。

打表发现 $4\times 10^4$ 以内的回文数只有不超过 $T=500$ 个。

于是考虑把这些回文数全部预处理出来，做一个背包就行了。

为了不算重，需要从小到大取或者从大往小取，然后 $dp_i\gets dp_{i-num_j}$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
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
using namespace std;
using namespace mystd;

const int mod = 1e9 + 7;
const int maxn = 4e4 + 400;
int T, n, tot, num[maxn], dp[maxn];
int t[10], tp;

bool ispad(int x) {
    tp = 0;
    while (x) t[++tp] = x % 10, x /= 10;
    for (int i = 1; i <= tp / 2; i++) {
        if (t[i] != t[tp - i + 1]) return 0;
    }
    return 1;
}

signed main() {
    for (int i = 1; i <= maxn - 1; i++) {
        if (ispad(i)) num[++tot] = i;
    }
    cout << tot << endl;
    dp[0] = 1;
    for (int i = 1; i <= tot; i++) {
        for (int j = num[i]; j <= maxn - 1; j++) {
            dp[j] = (dp[j] + dp[j - num[i]]) % mod;
        }
    }
    T = read();
    while (T--) {
        n = read();
        write(dp[n]);
        puts("");
    }
    return 0;
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
一道基础计数 dp。  
### Problem  
$T(T\leq 10^4)$ 次询问，每次给出一个正整数 $n (n\leq 4×10^4)$，求 $n$ 可被拆解成若干回文数之和形式的方案数。
### Solution  
我们看到这题就觉得回文数很少，于是我们打出一个 check 函数准备检查一下也方便后续处理：  
```cpp
bool check(int x){
	int p[6];int tot=0;
	while(x!=0){
		p[++tot]=(x%10);
		x/=10;
	}
	for(int i=1;i<=tot/2;i++){
		if(p[i]!=p[tot-i+1]){
			return false;
		}
	}
	return true;
}
```
这个函数可以检查 $x$ 是否为回文数。  
我们跑了一下 $4×10^4$ 范围的回文数，果不其然，只有 498 个，乘上一个 $n$ 是跑得过去的。  
由于有多组询问，但是 dp 只用做一遍，所以我们可以直接在程序开始的时候就把表刷好。  
至于具体的 dp 过程：  
众所周知，求组合需要限定一个最大值，这个最大值通常是这一步选择的数，之前选择的数不可超过这个最大值即可满足找到的排列是字典序最小的排列，也就是组合数。  
但是！  
我们发现 $n^2$ 的空间和时间开不下，由于我们只会选择回文数，将其离散化后编号开第二维空间就好了。  
code：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e4+10;
const int mod=1e9+7;
int dp[N][510];
ll sum[N];
vector <int> num;
int T;int n;
void init(){
	
}
bool check(int x){
	int p[6];int tot=0;
	while(x!=0){
		p[++tot]=(x%10);
		x/=10;
	}
	for(int i=1;i<=tot/2;i++){
		if(p[i]!=p[tot-i+1]){
			return false;
		}
	}
	return true;
}
void solve(){
	cin>>n;
	cout<<sum[n]<<endl;
}
int main(){
	for(int i=0;i<=500;i++)dp[0][i]=1;
	for(int i=1;i<=40000;i++){
		//cout<<i<<endl; 
		if(check(i)){
			num.push_back(i);
		}
		ll tot=0;
		for(int j=0;j<num.size();j++){
			tot+=dp[i-num[j]][j];
			tot%=mod;
			dp[i][j]=tot;
			//cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
		for(int j=num.size();j<=500;j++){
			dp[i][j]=dp[i][j-1];
		}
		sum[i]=tot;
		//cout<<endl;
	}
	//cout<<num.size()<<endl;
	//for(int i=1;i<=12;i++)cout<<sum[i]<<endl;
	cin>>T;
	while(T--)init(),solve();
	return 0;
}
```


---

