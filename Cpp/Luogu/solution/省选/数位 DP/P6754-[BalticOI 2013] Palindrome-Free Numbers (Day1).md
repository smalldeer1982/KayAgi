# [BalticOI 2013] Palindrome-Free Numbers (Day1)

## 题目描述

我们定义回文串为正着读反着读都一样的数字串，如果一个数字串的一个长度大于 $1$ 的子串也为回文串的话，那么我们也定义这个数字串为回文串。

顾名思义，不是回文串的数字串为非回文串。

给定 $a,b$，求区间 $[a,b]$ 中有多少个数字串为非回文串。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$0 \le a \le b \le 10^{18}$。    
对于其中的 $25\%$ 的数据，$b-a \le 10^5$。

#### 说明

翻译自 [BalticOI 2013 Day1 B Palindrome-Free Numbers](https://boi.cses.fi/files/boi2013_day1.pdf)。

## 样例 #1

### 输入

```
123 321```

### 输出

```
153```

## 样例 #2

### 输入

```
123456789 987654321```

### 输出

```
167386971```

# 题解

## 作者：EuphoricStar (赞：15)

~~我只会发屑题的题解实锤了~~

## 思路

一道非常基础的数位 dp，不知道为什么是紫题。

首先要知道一个非常重要的性质：如果一个字符串不含有长度大于 $1$ 的回文子串，那么这个字符串的**每个字符**都不会和**前两个字符**相同。

于是记搜时我们添加两个状态 $\text{pre1}$ 和 $\text{pre2}$，表示当前数位的前两个数字，往下搜的时候判断一下当前数位是否不等于 $\text{pre1}$ 和 $\text{pre2}$。初始时设 $\text{pre1}$ 和 $\text{pre2}$ 为 $-1$，表示没有前两位。注意判断状态是否访问过时 $\text{pre1}$ 和 $\text{pre2}$ 要 $+1$，否则 $-1$ 可能会越界。还有一点要注意：$\text{pre1}$ 转移时，如果当前数位为前导零，则要设为 $-1$ 而不是 $0$，否则会 WA 78pts。

之后就是套模板了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll l, r, f[25][15][15], a[25];

ll dfs(ll pos, bool limit, bool lead, ll pre1, ll pre2) {
	if (!pos) {
		return 1;
	}
	ll ans = 0;
	if (!limit && !lead && f[pos][pre1 + 1][pre2 + 1] != -1) {
		return f[pos][pre1 + 1][pre2 + 1];
	}
	ll up = limit ? a[pos] : 9;
	for (ll i = 0; i <= up; ++i) {
		if (i != pre1 && i != pre2) {
			ans += dfs(pos - 1, limit && i == up, lead && !i, (!lead || i) ? i : -1, pre1);
		}
	}
	if (!limit && !lead) {
		f[pos][pre1 + 1][pre2 + 1] = ans;
	}
	return ans;
}

ll solve(ll x) {
	ll cnt = 0;
	while (x) {
		a[++cnt] = x % 10;
		x /= 10;
	}
	memset(f, -1, sizeof(f));
	return dfs(cnt, 1, 1, -1, -1);
}

int main() {
	scanf("%lld%lld", &l, &r);
	printf("%lld", solve(r) - solve(l - 1));
	return 0;
}
```


---

## 作者：Exber (赞：12)

## 题意
- #### 求 $[l,r]$ 中有多少个数字串不包含长度大于 `1` 的回文子串。

## 做法
数位 dp。~~真就不知道为啥大家都写递归版的。~~

很容易发现，如果某位上的数字和它前一位或者它前两位上的数字相同，就会构成一个回文子串。例如 `12313`，最后的一个 `3` 和它前两位上的数字相同，于是构成了一个回文子串。

于是考虑用三维数组来表示状态，$dp_{i,j,k}$ 表示长度为 $i$，首位为 $k$ 且第二位为 $j$ 的非回文子串数（有前导 `0`）。定好了状态表示，状态转移方程便呼之欲出了，$dp_{i,j,k}=\sum\limits_{i=1}^ndp_{i-1,l,j} | 0\le j,k,l\le9$ 且 $j\ne k\ne l$。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

long long dp[1005][15][15],a[1005];

inline void _dp(int x) // 求出所有长度小于等于 x 的不含回文子串的数字串的个数 
{
	for(int i=0;i<=9;i++) // 所有一位数都是 
	{
		dp[1][0][i]=1;
	}
	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++) // 求出所有两位数 
		{
			if(i==j) // 如果两位相同，例如 11，则是回文数字串 
			{
				continue;
			}
			dp[2][i][j]=1;
		}
	}
	for(int i=3;i<=x;i++)
	{
		for(int j=0;j<=9;j++)
		{
			for(int k=0;k<=9;k++)
			{
				for(int l=0;l<=9;l++) // 求出三位及以上的数 
				{
					if(l==k||l==j||j==k) // 不能和前一位或者前两位相同 
					{
						continue;
					}
					dp[i][k][l]+=dp[i-1][j][k];
				}
			}
		}
	}
}

inline long long sum(long long x)
{
	if(x<10) // 一位数特判
	{
		return x+1;
	}
	int len=0;
	long long tmp=x;
	while(tmp)
	{
		a[++len]=tmp%10;
		tmp/=10;
	}
	long long res=10;
	for(int k=2;k<len;k++)
	{
		for(int i=0;i<=9;i++)
		{
			for(int j=1;j<=9;j++) // 加上所有位数小于 len 的数 
			{
				if(i==j)
				{
					continue;
				}
				res+=dp[k][i][j];
			}
		}
	}
	int lst1=-1,lst2=-1; // 前一位、前两位 
	bool flag=true; // x 的前 len-1 位数字串本身是否不含回文子串 
	for(int k=len;k>=2;k--) // 枚举每一位 
	{
		for(int j=0;j<a[k];j++) // 不能跑满 
		{
			if(k==len&&j==0) // 首位不能为 0 
			{
				continue;
			}
			for(int i=0;i<=9;i++)
			{
				if(i==j||j==lst1||j==lst2||i==lst1) // 如果构成了回文子串 
				{
					continue;
				}
				res+=dp[k][i][j];
			}
		}
		if(a[k]==lst1||a[k]==lst2) // 如果这一位和前两位构成了回文子串 
		{
			flag=false;
			break;
		}
		lst2=lst1;
		lst1=a[k];
	}
	if(flag) // 如果 x 的前 len-1 位数字串本身不含回文子串 
	{
		for(int i=0;i<=a[1];i++) // 判断最后一位，顺带把 x 本身也判断了 
		{
			if(i!=lst1&&i!=lst2)
			{
				res++;
			}
		}
	}
	return res;
}

int main()
{
	long long l,r;
	scanf("%lld%lld",&l,&r); // 读入 
	_dp(25); // 预处理 
	printf("%lld\n",sum(r)-sum(l-1)); // 前缀和 
	return 0;
}
```


---

## 作者：WarningQAQ (赞：4)

## 分析：
这道题看着像是**manacher（马拉车）**，但其实是**数位dp**。

+ 如果某个数上的某一位与它的上一位相同，则这个数肯定是个**回文数**。
+ 同理，如果某个数上的某一位与它的上上一位相同，则这个数肯定也是个**回文数**。

**数位dp**时要注意前导0的判断。

时间复杂度大概是 $O(\log(n)\times10)$ 。

## 代码：
```cpp
#include "cstdio"
#define W 20
#define E 11
#define int long long
namespace IAKIOI {
const signed L = 1 << 20 | 1;
char buffer[L], *S, *TT;
#define getchar() ((S == TT && (TT = (S = buffer) + fread(buffer, 1, L, stdin), S == TT)) ? EOF : *S++)
inline void read(auto &x) {
    x = 0;
    bool f = false;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            f = true;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = x * 10 + s - '0';
        s = getchar();
    }
    f ? -x : x;
}
inline void write(auto x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
}  // namespace IAKIOI
using namespace IAKIOI;
int pow[W];
inline void getnxt(int &last1, int &last2, int v) {
    if (last1 == 10)
        last1 = v;
    else
        last2 = last1, last1 = v;
}
inline bool judge(int &last1, int &last2, int v) { return v != last1 && v != last2; }
int dp[E][E][W][2];
bool v[E][E][W][2];
inline int work(int last1, int last2, int n, int tmp) {
    if (!n)
        return 1;
    if (v[last1][last2][n][tmp])
        return dp[last1][last2][n][tmp];
    int l1, l2, vis, tot = 0;
    v[last1][last2][n][tmp] = 1;
    for (int i = 0; i <= 9; ++i) {
        vis = (tmp || i) ? 1 : 0;
        l1 = last1;
        l2 = last2;
        if (vis && !judge(l1, l2, i))
            continue;
        if (vis)
            getnxt(l1, l2, i);
        tot += work(l1, l2, n - 1, vis);
    }
    return dp[last1][last2][n][tmp] = tot;
}
inline int solve(int n) {
    int ans = 0, x, last1 = 10, last2 = 10, l1, l2, tmp;
    bool ok = false;
    for (int i = 18; i >= 0; --i)
        if ((x = n / pow[i] % 10) || ok) {
            for (int j = 0; j < x; ++j) {
                tmp = (ok || j) ? 1 : 0;
                l1 = last1, l2 = last2;
                if (tmp && !judge(l1, l2, j))
                    continue;
                if (tmp)
                    getnxt(l1, l2, j);
                ans += work(l1, l2, i, tmp);
            }
            ok = 1;
            if (!judge(last1, last2, x))
                break;
            getnxt(last1, last2, x);
        }
    return ans;
}
signed main() {
    for (int i = pow[0] = 1; i <= 18; ++i) pow[i] = pow[i - 1] * 10;
    int l, r;
    read(l), read(r);
    write(solve(r + 1) - solve(l));
    return 0;
}

```
------------
###### 楼上大佬的代码比我简单好多QAQ

---

## 作者：Ginger_he (赞：3)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/15837884.html)
# 题目描述
给定 $a,b$，求区间 $[a,b]$ 中有多少个不含长度大于一的回文子串的数字串。
# 题解
还是比较套路的数位 dp。我们传五个参数 $k,x,y,p,q$ 进入 dfs，分别表示枚举到第 $k$ 位，前两位为 $x$，前一位为 $y$，是否为前导 $0$，以及这一位填的数有没有限制，用 $f$ 数组记忆化即可。  
下面来简要说明一下如何判断非回文串。不妨设回文串为 $s_1s_2...s_n$，接下来进行分类讨论：若 $n$ 为奇数，令 $m=\dfrac{n+1}{2}$，则 $s_{m-1}s_ms_{m+1}$ 必为回文串；若 $n$ 为偶数，令 $m=\dfrac{n}{2}$，则 $s_ms_{m+1}$ 必为回文串。因此我们在填到第 $x$ 位时，只需要判断它与第 $x-1$ 位和第 $x-2$ 位是否相等即可。
## 注意
我们把填前导 $0$ 的位置设为 $-1$，这样会更加方便，但是 $x$ 和 $y$ 为 $-1$ 的时候不能进行记忆化。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int len,a[20];
ll l,r,f[20][10][10];
ll dfs(int k,int x,int y,int p,int q)
{
	if(!k)
		return 1;
	if(!p&&!q&&x!=-1&&y!=-1&&f[k][x][y]!=-1)
		return f[k][x][y];
	int z=q?a[k]:9;
	ll res=0;
	for(int i=0;i<=z;i++)
	{
		if(i==x||i==y)
			continue;
		res+=dfs(k-1,y,(p&&!i)?-1:i,p&&!i,q&&(i==z));
	}
	if(!p&&!q&&x!=-1&&y!=-1)
		f[k][x][y]=res;
	return res;
}
ll divide(ll x)
{
	len=0;
	while(x)
	{
		a[++len]=x%10;
		x/=10;
	}
	return dfs(len,-1,-1,1,1);
}
int main()
{
	memset(f,-1,sizeof(f));
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",divide(r)-divide(l-1));
	return 0;
}
```


---

## 作者：JK_LOVER (赞：3)

## 题意
求出所有 $[L..R]$ 的数字，满足其中子串没有回文串。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p6754)
## 分析
回文串的性质还是挺简单的。

- 长度为奇数的回文串，那么一定会有一个数等于前第二个数。

- 长度为偶数的回文串，那么一定会有一个数等于前一个数。

那么把最小回文节都判掉的串，子串一定不是回文串。那么我们只需要做个数位 $dp$ 就好了。时间复杂度为 $O(\log n\times 10)$ 。

- 细节注意处理前导零，这表明了这个数是否开始。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long 
LL len,a[20],f[20][12][12];
LL dfs(int now,int last,int Last,int limit,int st){
	if(now <= 0) return 1;
	if(!st && !limit && f[now][last][Last] != -1) return f[now][last][Last];
	int x = limit ? a[now] : 9;
	LL ans = 0;
	for(int i = 0;i <= x;i++) {
		if(i == last || i == Last) continue;
		ans += dfs(now-1,(!i&&st)?-1:Last,(!i&&st)?-1:i,limit&&(i==a[now]),st&&(i==0));
	}
	if(!st && !limit) f[now][last][Last] = ans;
	return ans;
}
int main()
{
	memset(f,-1,sizeof(f));
	LL A,B;
	cin >> A >> B;
	A--;
	while(A) {
		a[++len] = A%10;A/=10;
	}
	LL L = dfs(len,-1,-1,1,1);
	len = 0;
	memset(a,0,sizeof(a));
	memset(f,-1,sizeof(f));
	while(B) {
		a[++len] = B%10;B/=10;
	}
	LL R = dfs(len,-1,-1,1,1);
	cout << R - L << endl;
	return 0;
}

```


---

## 作者：chlchl (赞：2)

双倍经验：[P3413](https://www.luogu.com.cn/problem/P3413)（然鹅我那题还没过）。

## 题意简述
给定 $l,r$，问 $\lbrack l,r\rbrack$ 中有几个数不含长度大于 $1$ 的回文子串。

## 做法
明显数位 DP。

如果要判断一个数有没有回文子串，只需要判断这个数的每一位是否与其前两位相同（这个可以自己想想，因为回文无非就是 $xx$ 和 $xyx$ 的形式）。

所以我们设计 $f_{len,op,lst1,lst2}$ 表示当前搜到第 $len$ 位，数的类型是 $op$（数位 DP 的经典），上两个数分别是 $lst1,lst2$ 的非回文数。

转移时，如果当前的数等于 $lst1$ 或 $lst2$ 就跳过，否则往下搜。

但是这样只有 $79$（或者 $78$）分。因为没有考虑前导零的情况。比如说 $090$ 这个数，我们在算的时候把它认为是回文的，但实际上 $90$ 是一个非回文数。

解决方案就是分是否是前导零，分别递归。具体可以看代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 18 + 10;
ll l, r, dgt[N], f[N][2][13][13];

ll dp(int len, int op, int is0, ll lst1, ll lst2){//注意传多一个前导零的参数 
	if(!len)	return 1;//能到这的肯定都是合法的 
	if(!is0 && f[len][op][lst1][lst2] != -1)	return f[len][op][lst1][lst2];
	ll cnt = 0; int k = (op ? dgt[len] : 9);
	for(int d=0;d<=k;d++){
		if((d == lst1 || d == lst2))	continue;
		if(is0 && d == 0)	cnt += dp(len - 1, op & (d == k), 1, lst1, lst2);
		//如果是前导零，继续传lst1，lst2，而不要把 0 传进去，以免少算 
		else	cnt += dp(len - 1, op & (d == k), 0, d, lst1); //否则正常传参 
	}
	if(!is0)	f[len][op][lst1][lst2] = cnt;
	return cnt;
}

ll solve(ll x){
	int len = 0;
	do	dgt[++len] = x % 10;
	while(x /= 10);
	memset(f, -1, sizeof(f));
	return dp(len, 1, 1, 10, 10);
}

int main(){
	scanf("%lld%lld", &l, &r);
	printf("%lld\n", solve(r) - solve(l - 1));
	return 0;
}
```


---

## 作者：Dr_Gilbert (赞：2)

# P6754 Solution
【题目大意】定义全为数字，且存在一个长度不小于$2$ 的字串是回文串的数字串为回文串。求 $[l,r]$ 内非回文串的个数。

如果你学过数位DP，那么应该可以发现本题是一道数位DP的题目。

不难发现，虽然题目的限制中提到长度不小于 $2$ 的回文串，但事实上只需要考虑长度为 $2$ 或 $3$ 的回文串即可，因为它们分别是长度为偶数的回文串和长度为奇数的回文串的最基本单位。即使是如题目新定义的回文串，也必然包含这种最小单位。

考虑题目限制设计状态。首先已处理的长度和是否满足题目的限制条件一定要加入。由于需要判断长度为 $2$ 或 $3$ 的字串是否为回文串，所以也容易想到把前两位的数字设计进状态。但这样就会出现一个问题，那就是有可能错误地把数字串的前导零也算作回文串，所以在判断是否为回文串时判断是否为前导零即可。于是我们将前两位是否为前导零也加进状态。

所以设计 $dp[pos][a][b][qda][qdb][pal]$，有状态转移：
$$
dp[pos][a][b][qda][qdb][pal]=\sum_{i=1}^{maxn} dp[pos][i][a][qda'][qdb'][pal']
$$
其中，$qda$ 表示 $a$ 是否为前导零，$qdb$ 表示 $b$ 是否为前导零，$pal$ 表示是否为回文串。当 $pos=0$ 时，说明数字已填完，答案即为最终的 $pal$。当 $lim$ 为真时，$maxn=num[pos]$，否则为 $9$。（$num$ 表示最大值的各个数位）。$pal$ 和 $pal'$，$qda$ 和 $qda'$ 等之间的关系可以自行推理或参考代码，不再赘述。

事实上，数位DP是舍弃了一些数字中对求解没有帮助的信息，聚焦于有用状态进行转移的一类DP问题。代码实现参考：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[20][11][11][2][2][2];
int num[20];
int dfs(int pos, int a, int b, bool pal, bool qda, bool qdb, bool lim){
	if (!pos) return pal;
	if (!lim&&dp[pos][a][b][pal][qda][qdb]!=-1){
		return dp[pos][a][b][pal][qda][qdb];
	}
	int maxn=lim?num[pos]:9;
	int ret=0;
	for (int i=0;i<=maxn;i++){
		ret+=dfs(pos-1,i,a,pal||(i==a&&!qda)||(i==b&&!qdb),qda&&(i==0),qdb&&(a==0),lim&&(i==maxn));
	}
	if (!lim) dp[pos][a][b][pal][qda][qdb]=ret;
	return ret;
}
int work(int x){
	int len=0;
	while (x){
		num[++len]=x%10;
		x/=10;
	}
	memset(dp,0xff,sizeof(dp));
	return dfs(len,0,0,0,1,1,1);
}
signed main(){
	int l,r;
	cin>>l>>r;
	int tmp=work(r)-work(l-1);
	int ans=r-l+1-tmp;
	cout<<ans;
	return 0;
}
```

PS:本题有一道双倍经验题，要求的是回文串的个数，但数据范围更大一些，不过也大同小异，可以做一做：[P3413 SAC#1 - 萌数](https://www.luogu.com.cn/problem/P3413)

---

## 作者：Suzt_ilymtics (赞：2)

 [传送门](https://www.luogu.com.cn/problem/P6754)

### 简述题意：
定义回文串为正着读反着读都一样的数字串，如果一个数字串的一个长度大于 $1$ 的子串也为回文串的话，那么我们也定义这个数字串为回文串。

所以不是回文串的数字为**非回文串**，求区间 $[l, r]$ 内有多少个**非回文串** ,数据范围： $0 \le l \le r \le 10^{18}$

### Solution:

设 $f[i][j][k]$ 表示长度为 $i$ 最高位为 $j$ 次高位为 $k$ 的非回文串的个数

因为只要满足子串是回文数它就是回文串，所以判断比较的时候只需要与前两位数比较就好啦

转移方程：

$$f[i][j][k] = \sum_{k != j\ \And\And\ j != l\ \And\And\ l != k}f[i - 1][k][l]$$

实际意义：表示区间 $[jk000\cdots,jk999\cdots]$ 的非回文数的和

对于求 $ans_{l, r}$ 可以转化为 $ans_{1, r} - ans_{1, l - 1}$

求 $ans_{l,r}$ 时的策略：

设 $len$ 为 $r$ 的位数，$a[len]$ 中存 $r$ 的每一位

1、对于所有长度小于 $len$ 的 $f$ ， $ans += \sum_{1 \le j \le 9}^{2 \le i \le len - 1} f[i][j][k](0 \le k \le 9)$

2、对于长度小于等于 $len$ 位且最高位小于 $a[i]$ 的 $f$，$ans += f[i][j][k] (0 \le k \le 9)$ ，加的过程中注意判断此时是否是非回文串

3、因为 $2$ 枚举不到最后的个位数，所以要在最后单独判断一遍

### Code

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#define LL long long

using namespace std;
const int MAXN = 1010;

LL read(){
	LL s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') w = -1; ch = getchar();	}
	while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
	return s * w;
} 

char l[MAXN], r[MAXN];
LL f[MAXN][13][13];
LL a[MAXN];

void init(){
	for(int i = 2; i <= 1001; ++i){
		for(int j = 0; j <= 9; ++j){
			for(int k = 0; k <= 9; ++k){
				if(j == k) continue;//如果相邻两个元素一样，那么一定是回文串，直接跳过 
				for(int a = 0; a <= 9; ++a){
					if(j != a && a != k)//如果不是2回文也不是3回文 
						f[i][j][k] += f[i - 1][k][a];
				}
				if(i == 2) f[i][j][k]++;//如果长度为2，一定不是 
			}
		}
	}
}
 
LL solve(char s[]){
	memset(a, 0, sizeof(a));
	LL tot = 0;
	bool t = 1;
	int len = strlen(s);
	LL ans = 0, last1 = -1, last2 = -1, sum = 0;
	for(int i = len; i >= 1; --i){
		a[i] = s[len - i] - '0';//把个位放前面 
		sum = (sum << 1) + (sum << 3) + a[i];//
	}
	if(len == 1) return sum + 1;//如果长度为1，那么不用判断了 
	ans += 10;//算上长度为1的那10个数 
	for(int i = 2; i < len; ++i){//老套路把满着的先加上 
		for(int j = 1; j <= 9; ++j){
			for(int k = 0; k <= 9; ++k){
				ans = ans + f[i][j][k];
			}
		}
	}
	for(int i = len; i >= 2; i--){
		for(int j = 0; j < a[i]; ++j){
			if(i == len && j == 0) continue;//首位是0就跳过
			for(int k = 0; k <= 9; ++k){
				if(last1 != j && last2 != j && j != k && last1 != k){
					ans = ans + f[i][j][k];
				} 
			} 
		}
		if(last1 == a[i] || last2 == a[i]) {//上一位和上两位 
			t = 0; break;
		} 
		last2 = last1, last1 = a[i];//更新 
	}
	if(t) {//如果没有中途退出 
		for(int i = 0; i <= a[1]; ++i){//最后一位剩下的那一点 
			if(i != last1 && i != last2) ans++;
		}
	}
	return ans;
}

int main()
{
	init();
	cin >> l >> r;
	LL ans = solve(r) - solve(l);
	int t = strlen(l), flag = 0;
	for(int i = 1; i < t; ++i){
		if(l[i] == l[i - 1] || (l[i] == l[i - 2] && i > 1)) {
			flag = 1;
			break;
		}
	}
	if(!flag) ans++;
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：fanypcd (赞：2)

[P6754 [BalticOI 2013 Day1] Palindrome-Free Numbers](https://www.luogu.com.cn/problem/P6754)

需要一点思维的数位 DP，题目中将回文串的判定改简单了的。

在这篇题解中，我们称题目中定义的**回文串**为**伪回文串**，而**正着读反着读都一样的数字串**为**真回文串**。

假设有一个**真回文串  S**。

- 如果 **S** 的长度为奇数，则 **S** 中一定存在一个长度为 3 的字串 **S'**，且 **S'** 也是**真回文串**。

- 如果 **S** 的长度为偶数，则 **S** 中一定存在一个长度为 2 的字串 **S'**，且 **S'** 也是**真回文串**。

由上可知，如果一个字符串 **S** 是 **伪回文串** ，当且仅当 **S** 中存在长度为 2 或 3 的**真回文串**。

这样在枚举数位的时候就只需要记录当前位的前两位分别是什么就好了。

------

然后就是数位 DP 的基本套路了。

显然问题满足区间减法性质，

即记 $query(l,r)$ 为区间 $[l,r]$ 的答案，那么有 $query(l,r)=query(1,r)-query(1,l-1)$

这样我们只需要考虑区间 $[1,n]$ 的答案。

我们设计这样一个函数 dfs(pos, l1, l2, ck, isl, zero) 表示在枚举到 pos 位并且状态为后面这么多参数的答案。

其中：

- pos: 当前枚举到的位数
- l1: 往前一位的数
- l2: 往前两位的数
- ck: 之前的枚举是否出现了长度为 2 或 3 的**真回文串**
- isl: 之前的枚举是否到达了枚举的极限（对于每一位都是这样）
- zero: 现在的枚举有无前导零

设计好状态后，显然结束标识是（ cnt 表示总共需要枚举的位数）。

```cpp
if(pos == cnt + 1)
{
    return ck;
}
```

然后可以记忆化来减少枚举次数。

```cpp
if(f[pos][l1][l2][ck][isl])
{
    return f[pos][l1][l2][ck][isl];
}
```

接下来就是确定这一位能枚举到的上界，记为 r （ bits[i] 里面存储的是 n 的第 i 位）

同时将需要求解的变量地址赋给 ans 以便在循环中节约长度。

```cpp
int &ans = f[pos][l1][l2][ck][isl], r = (isl ? bits[pos] : 9);
```

然后用变量 k 枚举这一位所有可能的填法，并累计答案。

这里我调了好久，因为如果有前导零且 k 正好是 0 的话，这一位也得算作前导零中。

也就是应该 ```(zero && !k) ? 10 : k``` 而不是 ```k``` 。

```cpp
for(int k = 0; k <= r; k++)
{
    ans += dfs(pos + 1, (zero && !k) ? 10 : k, l1, ck || (k == l1) || (k == l2), isl && (k == r), zero && !k);
}
```

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int bits[105], cnt;
int f[25][15][15][2][2];
int dfs(int pos, int l1, int l2, int ck, int isl, int zero)
{
	if(pos == cnt + 1)
	{
		return ck;
	}
	if(f[pos][l1][l2][ck][isl])
	{
		return f[pos][l1][l2][ck][isl];
	}
	int &ans = f[pos][l1][l2][ck][isl], r = (isl ? bits[pos] : 9);
	for(int k = 0; k <= r; k++)
	{
		ans += dfs(pos + 1, (zero && !k) ? 10 : k, l1, ck || (k == l1) || (k == l2), isl && (k == r), zero && !k);
	}
	return ans;
}
int query(int x)
{
	cnt = 0;
	while(x)
	{
		bits[++cnt] = x % 10;
		x /= 10;
	}
	reverse(bits + 1, bits + cnt + 1);
	memset(f, 0, sizeof(f));
	return dfs(1, 10, 10, 0, 1, 1);
}
signed main()
{
	int l, r;
	scanf("%lld%lld", &l, &r);
	printf("%lld", (r - l + 1) - (query(r) - query(l - 1)));
	return 0;
}
```



---

## 作者：daniEl_lElE (赞：1)

数位 dp。

## 思路

首先如果一个串包含一个回文串，那么必定会包含一个长度为 $2$ 或 $3$ 的回文串。

我们可以转化为求有多少数不包含长度为 $2$ 或 $3$ 的回文串。此时只需要记录一下前一位，前两位的数 $last_1,last_2$，我们在转移时枚举第 $i$ 位选择的数 $j$ 时只需要判断 $j\not=last_1,last_2$ 即可。

于是就做完啦！

嗯其实没有，主要问题是恶心很多数位 dp 问题的前导零。这里，前导零并不造成回文串。所以我们还得枚举最高位，限制最高位不能放 $0$。

等下，不会真有人枚举最高位是 $1\sim 9$ 了吧。考虑到我们要做的只是限制不为 $0$，而我们刚才说了，要求新的一位不是 $last_1$ 或 $last_2$，那么我们 dfs 的时候只需要设 $last_2=0$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f[21][11][11];
int a[21],n;
int dfs(int now,int lst1,int lst2,int tp){
	if(now==0){
		return 1;
	}
	if(!tp&&f[now][lst1][lst2]!=-1){
		return f[now][lst1][lst2];
	}
	if(tp){
		int ans=0;
		for(int i=0;i<a[now];i++){
			if(i!=lst1&&i!=lst2){
				ans+=dfs(now-1,lst2,i,0);
			}
		}
		if(a[now]!=lst1&&a[now]!=lst2) ans+=dfs(now-1,lst2,a[now],1);
		return ans;
	}
	else{
		f[now][lst1][lst2]=0;
		for(int i=0;i<10;i++){
			if(i!=lst1&&i!=lst2){
				f[now][lst1][lst2]+=dfs(now-1,lst2,i,0);
			}
		}
		return f[now][lst1][lst2];
	}
}
int count(int s){
	if(!s) return 0;
	if(s<10) return s;
	n=0;
	while(s){
		a[++n]=s%10;
		s/=10;
	}
	int ans=dfs(n,0,10,1);
	for(int i=n-1;i>=1;i--){
		ans+=dfs(i,0,10,0);
	}
	return ans;
}
signed main(){
	int a,b;
	cin>>a>>b;
	memset(f,-1,sizeof(f));
	cout<<count(b)-count(a-1);
	return 0;
} 
```

---

## 作者：Fishing_Boat (赞：1)

~~又是一道数位 DP 的水紫~~

首先，不难发现，一个数中只要有一个数字和其前一个数字或再前面一个数字相同，那么这个数就一定是回文串。那么我们在搜索时就可以记录上一位数字以及上上位数字，不过需要注意前导零，可以再开一个变量来记录。

核心代码：
```cpp
ll dfs(ll pos,ll lim,ll zer,ll l1,ll l2){
/* pos 记录枚举到哪一位了，
lim 记录有没有达到上限，
zer 记录前导零，
l1 记录上一位数字，
l2 记录上上位数字。
如果是是前导零则记为 -1。
*/
	if(!pos) return 1;
	if(dp[pos][lim][zer][l1+1][l2+1]!=-1) return dp[pos][lim][zer][l1+1][l2+1];
	ll up=lim?a[pos]:9,res=0;
	for(int i=0;i<=up;i++){
		if(zer&&!i) res+=dfs(pos-1,0,1,-1,l1); //特判前导零
		else if(l1!=i&&l2!=i) res+=dfs(pos-1,lim&&(i==up),0,i,l1);
	}
	return dp[pos][lim][zer][l1+1][l2+1]=res;
}
```

做完这道题建议再做一下 [P4124 [CQOI2016]手机号码](https://www.luogu.com.cn/problem/P4124)，[P3413 SAC#1 - 萌数](https://www.luogu.com.cn/problem/P3413)，这三道题个人感觉挺像的，萌数甚至就是这道题的高精度版。

---

## 作者：Feyn (赞：1)

同是记忆化搜索，既然大家都是正着来（即是寻找不是回文数的数），那我就分享一下反着来（寻找是回文数的数）的做法吧——

因为当时学数位DP的时候老师告诉我，数位DP是用来寻找具有某些特殊性质的数，~~又不是用来寻找不具有某种性质的数，虽然这都差不多啊~~~~
### 闲言少叙，书归正传：
#### 如何搜索呢？
首先要解决的是什么样的数是题目中所谓的“回文串”？

试想一下，一个传统意义上的回文串会有什么特点？

很简单，那就是具有一个中心。

这个中心有什么特殊性质吗？

有。那就是：

- 如果回文串（传统的）长度为偶数，那么它中间的两个数一定相同。

- 如果回文串长度为奇数，那么它中点两端的数一定相同，也就是中点后面的数一定等于它（指的是“中点后面的数”）前面第二个数。

翻译过来就是，传统回文串里一定有一个元素，它要么等于它前面那个元素，要么等于它前面的前面那个元素。

题目里所谓的回文串显然也具有这种性质。

那就简单了啊。

代码（[AC记录](https://www.luogu.com.cn/record/48118087)）：
```cpp
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
const int N=21;
const int M=11;

inline void read(int &wh){
	wh=0;int f=1;char w=getchar();
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w>='0'&&w<='9'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int a[N],dp[N][M][M][2][2][2];
int dfs(int wh,int last,int llast,bool same,bool ok,bool ever){
	if(wh==0)return ok;
	if(dp[wh][last+1][llast+1][same][ok][ever]>-1){
		return dp[wh][last+1][llast+1][same][ok][ever];
	}
	int end=same?a[wh]:9,an=0;
	for(int i=0;i<=end;i++){
		bool th=ok;
		if(ever){
			if(i==last||i==llast)th=true;
		}
		an+=dfs(wh-1,(ever||i!=0)?i:-1,last,same&&i==a[wh],th,ever||i!=0);
	}
	return dp[wh][last+1][llast+1][same][ok][ever]=an;
}
int work(int wh){
	if(wh<0)return 0;
	memset(dp,-1,sizeof(dp));
	int len=0,an=0;
	while(wh){
		a[++len]=wh%10;
		wh/=10;
	}
	return dfs(len,-1,-1,true,false,false);
}

signed main(){
	
	int s1,s2;
	read(s1);read(s2);
	printf("%lld",(s2-s1+1)-(work(s2)-work(s1-1)));
	
	return 0;
}
```


备注：

- 由于本蒟蒻太懒懒得判断，所以把所有状态都加到了记忆化数组里，~~这样做是十分浪费空间的！切勿模仿！~~
- 码风奇特，大佬尽请原谅，如有错误之处不吝赐教~~

---

## 作者：Register_int (赞：0)

首先转化题目条件。由于所有大于长度大于 $1$ 的回文串中，都包含长度为 $2$ 或 $3$ 的回文串。所以条件转化为：任意一位都不能与前两位中的其中一位相等。  
答案很明显了，记录前两位进行数位 dp 即可。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dp[20][11][11];

char a[20];

int k;

ll dfs(int p, int pr1, int pr2, bool lim, bool lead) {
	if (p == k) return 1;
	if (!lim && !lead && ~dp[p][pr1 + 1][pr2 + 1]) return dp[p][pr1 + 1][pr2 + 1];
	int n = lim ? a[p] ^ '0' : 9;
	ll res = 0;
	for (int i = 0; i <= n; i++) {
		if (i == pr1 || i == pr2) continue;
		res += dfs(p + 1, (!lead || i) ? i : -1, pr1, lim && i == n, lead && !i);
	}
	if (!lim && !lead) dp[p][pr1 + 1][pr2 + 1] = res;
	return res;
}

inline 
ll solve(ll n) {
	if (n < 0) return 0;
	memset(dp, 0xff, sizeof dp);
	sprintf(a, "%lld", n), k = strlen(a);
	return dfs(0, -1, -1, 1, 1);
}

ll l, r;

int main() {
	scanf("%lld%lld", &l, &r);
	printf("%lld", solve(r) - solve(l - 1));
}
```

---

