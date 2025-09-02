# 【MX-X8-T1】「TAOI-3」幸运草

## 题目背景

原题链接：<https://oier.team/problems/X8B>。

---

> 那是，深藏的思念 \
> 那是，永恒的誓言 \
> 那是，真心的祈愿 \
> 那是，悔恨的心怀 \
> 那是，童年的约定——

终将改变之物，与永不改变之物。

## 题目描述

Anzu 有一个正整数数列 $a_1, \ldots, a_n$ 和一个整数 $x$。她可以进行至多一次操作，选择一对正整数 $1 \le l \le r \le n$，然后对于所有 $l \le i \le r$ 的正整数 $i$ 让 $a_i$ 变成 $x$。现在她想要知道，在这之后，数列里所有数的和最大是多少。

## 说明/提示

**【样例解释 #1】**

最优的策略是选择 $l=3$，$r=4$ 进行一次操作，此时数列变为 $[1,4,2,2,5]$，总和为 $14$。

**【样例解释 #2】**

最优的策略为选择 $l=1$，$r=7$ 进行一次操作。

**【样例解释 #3】**

最优的策略为不进行操作。

**【数据范围】**

对于 $30\%$ 的数据，$n \le 500$。

对于另外 $20\%$ 的数据，$n \le 3 \times 10^3$。

对于另外 $10\%$ 的数据，$x=0$。

对于所有数据，保证 $1 \le n \le 10^5$，$1 \le a_i \le 10^9$，$0 \le x \le 10^9$。

## 样例 #1

### 输入

```
5 2
1 4 1 1 5
```

### 输出

```
14
```

## 样例 #2

### 输入

```
7 3
1 1 4 5 1 4 1
```

### 输出

```
21
```

## 样例 #3

### 输入

```
1 197
251
```

### 输出

```
251```

# 题解

## 作者：yedalong (赞：14)

**在写这题之前，建议大家先看一下[这一道题](https://www.luogu.com.cn/problem/P1115)**  
相信大家发现此题与[这一道题](https://www.luogu.com.cn/problem/P1115)很像，唯一不同的就是此题加上了 $x$ 这一基准。
## 思路
那[这一道题](https://www.luogu.com.cn/problem/P1115)是怎么操作的呢？我们可以先从第一个数开始选，用一个变量存当前的和。当我们发现这个变量的值小于 $0$ 时，那还不如不选，我们就直接重新将变量赋值为 $0$ 即可。此外，还要有一个存答案的变量，在每一次存当前的和的变量值发生改变时，就更新最大值。  
讲得这么清楚，[这一道题](https://www.luogu.com.cn/problem/P1115)的代码也就很好写了，具体如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,sum,ans=-1e9;
int main(){
	cin>>n;
	for(int i = 1;i<=n;i++){
		cin>>x;
		sum+=x;
		ans=max(ans,sum);
		if(sum<0) sum=0;
	}
	cout<<ans;
	return 0;
}
```
回归正题，我们可以将 $x$ 减去此题的数列，接着进行上述的操作，最后只需输出答案加上原数组的和即可。
## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,x,t,ans,now,sum;
signed main(){
    cin>>n>>x;
    for(int i = 1;i<=n;i++){
        cin>>t;
        sum+=t;
        now+=x-t;//将这个值赋值为 x 就等价于贡献了 x-t
        ans=max(ans,now);
        if(now<0) now=0;
    }
    cout<<ans+sum;
    return 0;
}
```

---

## 作者：Helenty (赞：5)

### 解题思路

读完题目后不难发现题目可以转化成：

**找到一个子区间 $[l,r]$ 使得 $ \sum_{i=l}^{r} (x - a_i)$ 最大。**

而答案就是最大子数组和加上 $a$ 数组的总和即可。

---

本题建议评橙。

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005], n, x;
long long sum, maxn, t;
int main()
{
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) sum += a[i];
    maxn = sum;
    for (int i = 1; i <= n; ++i)
	{
        t += x - a[i];
        maxn = max(maxn, sum + t);
        if (t < 0) t = 0;
    }
    t = 0;
    for (int i = n; i >= 1; --i)
	{
        t += x - a[i];
        maxn = max(maxn, sum + t);
        if (t < 0) t = 0;
    }
    cout << maxn << endl;
    return 0;
}
```

---

## 作者：盐焗蛋 (赞：5)

由于很难（根本不能？）确定某段区间往双向拓展后是否有对答案贡献更大的修改区间，还想不到可解的贪心。不过使用类 [P1115](https://www.luogu.com.cn/problem/P1115) 的新手级 dp 就能很轻松找到最好的修改区间来解决本题。

### 解析部分

首先构造 $b_i=x-a_i$（即修改当前位置对答案的贡献），则要修改的区间 $[l,r]$ 为 $b$ 中**最大子段**时，即 $\sum\limits_{i=l}^{r}{(x-a_i)}$ 最大。进一步地，因为答案的变化只与修改的区间有关，此时 $\sum\limits_{i=1}^{n}{(x-a_i)}$ 也最大。

于是我们可以先找出 $b$ 中最大的子段，本题可以考虑用简单的 dp。把 $dp_i$ 定义为 $[1,i]$ 中以 $i$ 结尾的最大子段和。那么由于 $i$ 位置既可以承接末尾于 $i-1$ 位置的子段并对其延长，也可以另作一段的开头。得到转移方程：

$dp_i=\max(dp_{i-1}+b_i,b_i)$

然后在转移时，需要判断一下当前位置应该属于以上两者中哪一种情况，用变量 $l,r$ 实时更新当前最大子段的首尾，此时的 $l,r$ 同样也是 $[1,i]$ 中对答案贡献最大的修改区间 $[l,r]$，用前缀和维护实时求出如果修改该区间得到的答案（即原 $a$ 中 $[1,l-1]$，$[r+1,n]$ 再加上修改区间对答案的贡献： $x(r-l+1)$ 的和），对于所有可能的 $i$ 答案求出最大值。以 $O(n)$ 解决了本题。

### 代码部分

为了保全祖宗建议使用  `long long` 来实现本题。）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,x,l,r,ans,a[100005],f[100005],b[100005],dp[100005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i],f[i]=f[i-1]+a[i],b[i]=x-a[i];
	ans=f[n];//需要注意不修改的特殊情况
	for(int i=1;i<=n;i++){
		if(dp[i-1]+b[i]>b[i]){
			r=i;//事实上在过程中 r 一定等于 i
		}
		else l=r=i;
		dp[i]=max(dp[i-1]+b[i],b[i]);
		ans=max(ans,(r-l+1)*x+f[l-1]+f[n]-f[r]);
	}
	cout<<ans;
	return 0;
}
/*

*/
```

---

## 作者：zlqwq (赞：4)

题目说的简单一点就是选择 $l$ 和 $r$ 让这段区间都变成 $x$ 然后问你数组最大和。

显然，我们开一个数组，表示 $a_i$ 变成 $x$ 获得的贡献，然后我们求一遍最大子段和去加上 $a$ 数组的和即可。

当然，我们还要特判最大子段和数组全是负数的情况，这样的话输出 $a$ 数组的和即可。


```cpp
#include<iostream>
#define int long long
using namespace std;
int aa[100005];
int n,x;
int sum;
int a[100005];
int dp[100005];
signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>aa[i];
		sum+=aa[i]; 
		a[i]=x-aa[i];
	} 
	for(int i=1;i<=n;i++){
		dp[i]=max(a[i],dp[i-1]+a[i]);
	}
	int ans=-1e18;
	bool flag=0;
	for(int i=1;i<=n;i++){
		if(dp[i]>0)flag=1;
		ans=max(ans,dp[i]);
	}
	if(flag==1)
	cout<<sum+ans;
	else cout<<sum;
	return 0;
}
```

---

## 作者：UKE_Piu (赞：3)

## Task
给定一个正整数序列和一个整数 $x$，操作是任意选择一个非空区间，将这个区间理的数全部替换为 $x$。可以不操作，求这个序列和的最大值

## Solution
我们可以考虑修改一个值对总和的贡献，那么我们把原数列记为 $a$，贡献记为 $b$。

贡献：$ b_i=x-a_i$

如果我们选择了一个区间 $[l,r]$ 进行操作，那么最后的总和就是原来序列的和加上这个区间的贡献和，即：

$ \sum_{i=1}^n{a_i}+\sum_{i=l}^r{b_i}$

由于前面一项是定值，我们只需要求出 $\sum_{i=l}^r{b_i}$ 的最大值即可，这个就是 $b$ 上的最大子段和。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
const int N=1e5+5;
ll x,a[N],b[N];
ll ans,sum,f;
ll max(ll _A,ll _B){
	return _A>_B?_A:_B;
}
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i],b[i]=x-a[i];
	for(int i=1;i<=n;i++) 
	  f=max(f+b[i],b[i]),ans=max(ans,f);
	sum=max(sum,sum+ans);
	cout<<sum;
	return 0;
}
```

---

## 作者：Jerry_zpl (赞：2)

本题算法：动态规划，模拟。  
难度建议：橙。  
思路如下：
- 首先我们将一个编号区间 $[l,r]$ 里的数都变成 $x$，那么如果 $a_i>x$ 那么这个数 $a_i$ 肯定是不用变化的。所以我们就把比 $x$ 小的数变成 $x$ 就行了，那么和肯定是大于 $a$ 数组里所有的元素之和的。
- 我们可以用一个数组来记录 $x-a_i$ 的差，然后我们就可以求最大子段和。因为如果 $b_i$ 是正数就说明 $a_i<x$ 可以进行操作。因为区间必须是连续的，所以是子段和。
- 还有一种情况，可以不用操作。如果 $a$ 数组中所有的数都大于或等于 $x$ 那么可以不用操作，直接输出 $a$ 数组里所有的元素之和即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int a[maxn];
int b[maxn];
int dp[maxn];
//dp[i]表示以第i个数结尾的最大子段和
signed main()
{
	int n,x;
	cin>>n>>x;
	int ans=0;
	int mini=INT_MAX;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ans+=a[i];
		mini=min(mini,a[i]);
		b[i]=x-a[i];
	}
	if(x==0||x<=mini)
	{
		cout<<ans;
	    return 0;
	}
	dp[1]=b[1];
	int maxi=dp[1];
	for(int i=2;i<=n;i++)
	{
		dp[i]=max(dp[i-1]+b[i],b[i]);//要么让a[i]单独成子段，要么在上一个子段的基础上加上a[i],取最大值即可
		maxi=max(maxi,dp[i]);//答案不是dp[n],因为可以以子段可以以任意一个数结尾
	}
	cout<<ans+maxi;
	return 0;
}
```

---

## 作者：Getaway_Car_follower (赞：1)

一种 dp 做法。

我们设 $dp_{i,0}$ 为前 $i$ 个数中还没用过操作的最大值，$dp_{i,1}$ 为前 $i$ 个数中正在用操作的最大值，$dp_{i,2}$ 为前 $i$ 个数中已经用过操作的最大值。

那么就有转移方程：

$$dp_{i,0}=dp_{i-1,0}+a_i \\ dp_{i,1}=\max\{dp_{i-1,0},dp_{i-1,1}\}+x \\ dp_{i,2}=\max\{dp_{i-1,1},dp_{i-1,2}\}+a_i$$

最终答案为 $\max\{dp_{i,0},dp_{i,1},dp_{i,2}\}$。

---

## 作者：fish_love_cat (赞：1)

容易想到将 $a_i$ 同 $x$ 比较，相减后得到当前位更改所得贡献。求解一次修改的最优贡献即为求解贡献序列的最大子段和。

那么我们将原序列转为贡献序列后跑一遍最大子段和即可得到操作能增加的最大值。最大子段和做法参考 [P1115](https://www.luogu.com.cn/problem/P1115)。注意本题可以不进行操作。

不执行操作所得值加上操作增加值即为所求。

```cpp
#include<iostream>
#define int long long
using namespace std;
int a[100005],x,ans,sum;
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
        a[i]=m-a[i]; 
        x+=a[i];
        x=max(x,a[i]);
        ans=max(ans,x);
    }
    cout<<sum+ans;
    return 0;
}
```

建议评橙。

---

## 作者：封禁用户 (赞：0)

### 具体思路
只进行一次区间赋值，就要考虑赋值后的值带来的贡献，因此需要判断赋值区间内的数变为 $x$ 时对总和带来的影响。因此可再开一个数组 $c$ 用于记录 $a_i$ 与 $x$ 的差，那么就是求关于数组 $c$ 的一个最大子段和，然后与总和相加就是答案。如果操作后的答案比原总和小，可以选择不进行操作，我们只要把最大子段和的最优解下限设为 $0$ 即可。
### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define I_love_Foccarus return
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define deap(i,a,b) for(int i=a;i>=b;i--)
#define in(a) a=read()
#define fi first
#define se second
const int N = 3e5 + 5;
const int inf = INT_MAX;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	I_love_Foccarus x*f;
}
void fast() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int n,m,q;
int a[N],c[N],h,ans;
signed main() {
	//fast();
	in(n),in(m);
	rep(i,1,n)in(a[i]),c[i]=m-a[i],h+=a[i];
	int f=0;
	rep(i,1,n){
		f=max(f+c[i],c[i]);
		ans=max(ans,f);
	}
	cout<<ans+h;
	I_love_Foccarus 0;
}
```

---

## 作者：xuyifei0302 (赞：0)

读完题，我们可以发现，我们想要整个数列和最大，就需要使这个数列的增量尽量大。

那么，我们贪心一下，这个数列若要变换，则 $l$ 所对应的值一定要小于等于 $x$，否则答案会变劣。

然后，我们要想一下结尾。若到 $r$ 目前，总体的增量为负，那么我们就可以把 $sum$ 归零，因为即使后面有增量更大的，那么我们加上这一段也会使答案不优。

最后，从所有的增量中取最大值，再加上原值即可。

下面是代码环节：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, x, a[100005], sum, maxn;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> x;
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	bool p = false;
	for (int i = 1; i <= n; i ++) {
		if (!p) {
			if (a[i] <= x) {
				p = true;
				sum += x - a[i];
				maxn = max(maxn, sum);
			}
		} else {
			sum += x - a[i];
			maxn = max(maxn, sum);
			if (sum < 0) {
				p = false;
				sum = 0;
			}
		}
	}
	sum = 0;
	for (int i = 1; i <= n; i ++) {
		sum += a[i];
	}
	sum += maxn;
	cout << sum;
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P11642 题解

## 思路

考虑 DP，记 $f_i$ 为修改的右端点为 $i$ 所能对答案增加的贡献。

于是推出状态转移方程 $f_i = \max(f_{i-1} + x - a_i, x - a_i)$，最后的答案就是 $\max\limits_{i=1}^n f_i + \sum\limits_{i=1}^n a_i$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[++idx]=c,c=getchar();
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=100005;

int n,x,sum;
int a[N],b[N];
int f[N];

signed main() {
    read(n),read(x);
    _rep(i,1,n) read(a[i]),b[i]=x-a[i],sum+=a[i];
    _rep(i,1,n) f[i]=max(f[i-1]+b[i],b[i]);
    int ans=0;
    _rep(i,1,n) ans=max(ans,f[i]);
    write(ans+sum);
    return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 题意

给你一个数列 $a$，你可以选择一个区间，并让这个区间内的所有数都变为 $x$，问你这个数列里的最大和是多少？

## 思路

首先肯定不能暴力枚举左端点和右端点，但是我们可以记录 $x$ 与 $a_i$ 的差的和，并且求出最大值，最后输出数列的总和加上最大值即可。

## 代码

代码如下：


```cpp
#include <bits/stdc++.h>
#include <iostream>
using namespace std ;
#define int long long
#define rep( i , l , r ) for (int i = (l) ; i <= (r) ; i++)
#define per( i , r , l ) for (int i = (r) ; i >= (l) ; i--)
const int N = 1e5 + 10 ;
int n , x ;
int a[N] ;
int mx = 0 ;
int s[N];
int ans ;
int smbh ;
int sum ;
void solve (){
    cin >> n >> x ;
    rep (i , 1 , n){
        cin >> a[i] ;
        sum += a[i] ;
    }
    rep (i , 1 , n){
        int bh = x - a[i] ;
        smbh += bh ;
        mx = max (mx , smbh) ;
        if (smbh < 0){
            smbh = 0 ;
        }
    }
    cout << sum + mx ;
}

signed main (){
	int _ = 1 ;
	//cin >> _ ;
	while ( _-- ){solve () ;}
	return 0 ;
}
```

---

