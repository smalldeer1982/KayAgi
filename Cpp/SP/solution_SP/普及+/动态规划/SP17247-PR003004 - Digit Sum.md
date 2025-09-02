# PR003004 - Digit Sum

## 题目描述

For a pair of integers a and b, the digit sum of the interval \[a,b\] is defined as the sum of all digits occurring in all numbers between (and including) a and b. For example, the digit sum of \[28, 31\] can be calculated as:

## 样例 #1

### 输入

```
3
0 10
28 31
1234 56789```

### 输出

```
46
28
1128600```

# 题解

## 作者：bmatrix (赞：3)

[题面](https://www.luogu.com.cn/problem/SP17247)

我的方法好像和大家都不一样诶，那我就写个题解吧。

### 约定：
记 $[a,b]$ 为区间 $[a,b]$ 中每个数的数字和的和，$[a,b)$ 为区间 $[a,b)$ 中每个数的数字和的和。

### 分析：
首先将区间问题转化为前缀和问题，即 $[a,b]=[0,b]-[0,a-1]=[0,b+1)-[0,a)$。

也就是说我们只需要能求出任意的 $[0,n]=[0,n+1)$ 就可以了。

下面考虑如何求 $[0,n)$。

### 求解：
不难发现，如果我们把 $n$ 的按每一位拆开，比如如果 $n=4325$，则显然有 $[0,4325)=[0,4000)+[4000,4300)+[4300,4320)+[4320,4325)$。

形式化地说，如果令 $n=\sum\limits_{i=0}^{\left\lfloor\lg n\right\rfloor}a_i10^i\,\,(a_i\in\mathbb N^*)$，则必然有：
$$[0,n)=\sum_{i=0}^{\left\lfloor\lg n\right\rfloor}[n-\sum_{j=0}^ia_i,n-\sum_{j=0}^{i-1}a_i)$$
~~（好像有点太形式化了）~~

我们考虑如何求 $[43000,43200)$：
$$\begin{aligned}
    [43000,43200)&=(4+3+0+0+0)+(4+3+0+0+1)+\dots+(4+3+1+9+9)
    \\&=2\times 100\times(4+3)+2\times(0+1+2+\dots99)+10\times(0+1)
    \\&=2\times 100\times(4+3)+2\times[0,100)+100\times[0,1]
\end{aligned}$$
我们发现，只要预处理求出 $\{a\},[0,10^i)$ 和 $[0,i]\,(0\le i\le 9)$，然后按从例子中发现的规律，从高往低挨位处理，就可以快速求出 $[0,n)$ 的值了。
### 代码：
代码中有更明确的计算方式，可能更好理解吧。
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s; i <= e; ++i)
#define per(i, s, e) for(int i = s; i >= e; --i)
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> pii;
ll pw10[20], g[10], s0[20]; // pw10[i]: 10的i次幂，g[i]: [0,i]或[0,i+1)，s0[i]: [0,10^i)
void init() {
    pw10[0] = 1;
    rep(i, 1, 15) pw10[i] = pw10[i - 1] * 10;
    rep(i, 1, 9) g[i] = g[i - 1] + i;
    s0[1] = 45;
    rep(i, 1, 15) s0[i] = s0[i - 1] * 10 + 45 * pw10[i - 1]; // [0,9]=45
}
ll calc(ll x) {
    ll dg[20] = {}, ans = 0, j = 0;
    while(x) {
        dg[j++] = x % 10;
        x /= 10;
    }
    ll s = 0;
    per(i, j, 1) { // 核心部分
        s += dg[i];
        ans += s * dg[i - 1] * pw10[i - 1];
        ans += dg[i - 1] * s0[i - 1];
        if(dg[i - 1]) ans += g[dg[i - 1] - 1] * pw10[i - 1];
    }
    return ans;
}
int main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    init();
    int t; cin >> t;
    while(t--) {
        ll a, b; cin >> a >> b;
        cout << calc(b + 1) - calc(a) << endl;
    }
    return 0;
}
```

---

## 作者：Link_Space (赞：2)

看到这道题的第一眼就知道这是一道毫无悬念的数位DP题，写法与大多数位DP写法都相同，相信做到这道题的大佬们都已经对数位DP十分熟悉了，我就不赘述了。

来思考一下这道题的本身，要求一个区间内所有数码的和，我们可以转化为分别求出0-9的数码个数，然后把每个数码乘上相应的值，最终就可以得到所有数码的和了，总的来说这道紫题还是比较水的。

以下是AC代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N = 100;
ll dp[N][100][100];//dp[i][j][k]表示以j为最高位的i位数含有多少个k数码
ll ksm(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res*=a;
		a*=a;
		b >>= 1;
	}
	return res;
}//快速幂板子
void init()
{
	for (int i = 0; i <= 9;i++)
		dp[1][i][i] = 1;
	for (int i = 2; i < N;i++)
	{
		for (int j = 0; j <= 9;j++)
		{
			for (int k = 0; k <= 9;k++)
			{
				for (int r = 0; r <= 9;r++)
				{
					dp[i][j][r] += dp[i - 1][k][r] ;//从次高位转移过来
				}
			}
			dp[i][j][j] += ksm(10, i - 1);//加上最高位的数码
		}
	}
}
ll make(ll n,ll search)//近乎模板的数位DP，n为范围，search为要找的数码
{
	ll digit[N];
	ll len = 0;
	memset(digit, 0, sizeof digit);
	while(n)
	{
		digit[++len] = n % 10;
		n/=10;
	}
	ll res = 0;
	for (int i =1;i<len;i++)
	{
		for (int j = 1; j <= 9;j++)
		{
			res += dp[i][j][search];
		}
	}//枚举位数不足len的数中含有多少个search数码
	for (int i = 1; i < digit[len];i++)
	{
		res += dp[len][i][search];//加上位数为len的数中的search数码
	}
	for (int i = len-1; i >= 1;i--)
	{
		ll x = digit[i];
		for (int j = 0; j < x;j++)
			res += dp[i][j][search];
		for (int j = len; j > i ;j--)
		{
			if(digit[j]==search)
				res += digit[i] * ksm(10, i - 1);
		}
	}
	return res;//返回所有search数码的数量
}
int main()
{
	init();
	int t;
	scanf("%d", &t);
	while(t--)
	{
		ll l,r;
		scanf("%lld%lld", &l, &r);
		ll ans = 0;
		for (int i = 1; i <= 9;i++)
		{
			ans+=(make(r+1, i) - make(l, i))*i;//累加答案即可
		}
		printf("%lld\n", ans);
	}
}
```


---

## 作者：Gokix (赞：2)

能做这个题，说明你已经在数位DP上有一定的造诣，那么开始吧。

如果我猜错了，你可以看下面这一部分。否则请直接跳转到147行。

## 给不会数位DP的初学者看的一部分:

例题：

找 $1-n$ 之间不含有 $1$ 的数。

$n \le 2^{63}-1$

------------

这暴力肯定跑不了几个分，$O(n)$ 都妥妥地T飞。

所以就有了数位DP。

思考把这个数拆开，放进 $a$ 数组里。

然后 $\operatorname{dfs}$ 记忆化搜索。

快的飞起。

------------

声明一下变量：$a[]$ 是被拆分的原数，$len$ 是搜索到当前第几位，$p$ 是是否搜到上限，$f[i]$ 表示 $i$ 位数中没有 $1$ 的数的个数 , $numlim$ 是当前搜索的上界。

```cpp
long long dfs(long long len,bool p)
{
	if(len==0)
	{
		return 1;
	}
	if(!p && f[len]!=-1)
	{
		return f[len][last];
	}
	long long numlim=p?a[len]:9,ans=0,i,j;
	for(i=0;i<=numlim;i++)
	{
		if(i!=1)
		{
			ans+=dfs(len-1,p&&i==numlim);
		}
	}
	if(!p)
	{
		f[len]=ans;
	}
	return ans;
}
long long calc(long long n)
{
	long long len=0;
	memset(a,0,sizeof(a));
	memset(f,-1,sizeof(f));
	while(n)
	{
		len++;
		a[len]=n%10;
		n/=10;
	}
	return dfs(len,1);
}
int main()
{
	long long i,j,u,v;
	cin>>n;
	u=calc(n);
	cout<<u<<endl;
	return 0;
}
```

学会了吧，开始下一题的介绍。

------------

## 前置题目

[AT1483](https://www.luogu.com.cn/problem/AT1483)

统计 $1-n$ 中出现了几个 $1$ 。

这种题与前面的题不同之处在于这是**统计有多少个** $\mathbf{1}$ ，而不是有多少个数字有 $1$。例如 $"11"$ 在原来的题中贡献是 $1$ ，而在本题中贡献是 $2$。

我们需要在 $\operatorname{dfs}$ 中新增一个变量 $sum$，表示现在有几个 $1$。

如果 $i=1$ ，我们在下一次的搜索中把 $sum+1$，否则不变。

然后就愉快地结束了:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long t,n,a[110],f[110][110];
long long dfs(long long len,long long sum,bool p)
{
	if(len==0)
	{
		return sum;
	}
	if(!p && f[len][sum]!=-1)
	{
		return f[len][sum];
	}
	long long numlim=p?a[len]:9,ans=0,i,j;
	for(i=0;i<=numlim;i++)
	{
		ans+=dfs(len-1,sum+(i==1),p && i==numlim);
	}
	if(!p)
	{
		f[len][sum]=ans;
	}
	return ans;
}
long long calc(long long n)
{
	long long len=0;
	memset(a,0,sizeof(a));
	memset(f,-1,sizeof(f));
	while(n)
	{
		len++;
		a[len]=n%10;
		n/=10;
	}
	return dfs(len,0,1);
}
int main()
{
	long long i,j,u,v;
	cin>>n;
	cout<<calc(n)<<endl;
	return 0;
}
```

------------

## 终于来到本题了

[SP17247](https://www.luogu.com.cn/problem/SP17247)

现在不只要统计 $1$ 了，$0-9$ 都要统计。

$1-9$ 都是一样的，问题就在于 $0$。

很明显，这题有前导0。会影响到0的统计。

注意 $000000000000000000$ 和 $0$，是一个数，所以你要特判一下。

引入一个变量 $zero$ 表示你当前搜到的值是否有一大堆的前导0，如果有一堆的前导0并且你现在搜到的 $i$ 也是0，那么 $sum$ 是不能变的。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long t,n,m,a[110],f[110][110],gx,zkw;
long long dfs(long long len,long long sum,bool zero,bool p)
{
	if(len==0)
	{
		return sum;
	}
	if(!p && f[len][sum]!=-1)
	{
		return f[len][sum];
	}
	long long numlim=p?a[len]:9,ans=0,i,j;
	for(i=0;i<=numlim;i++)
	{
		ans+=dfs(len-1,sum+((i||zero)&&(i==gx)),zero||i,p&&(i==numlim));//仔细理解一下这两句话
	}
	if(!p && zero)
	{
		f[len][sum]=ans;
	}
	return ans;
}
long long calc(long long n)
{
	long long len=0,i;
	memset(a,0,sizeof(a));
	memset(f,-1,sizeof(f));
	while(n)
	{
		len++;
		a[len]=n%10;
		n/=10;
	}
	return dfs(len,0,0,1);
}
int main()
{
	long long i,j,u,v,ans=0;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		ans=0;
		for(gx=0;gx<=9;gx++)
		{
			u=((calc(m)-calc(n-1)))*gx;
			ans=(ans+u);
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
```

------------

完结撒花！

---

## 作者：chihik (赞：1)

每个数的数字和的和其实就是所有数字与它出现次数的积的和。

那么对于 $0-9$ ，依次像 [P2602 [ZJOI2010]数字计数](https://www.luogu.com.cn/problem/P2602) 统计出现次数就可以了。

具体做法也很简单，记录前 $pos$ 位某个数字出现次数 $sum$，记忆化搜索即可通过。

最后附上双倍经验：[P4999 烦人的数学作业](https://www.luogu.com.cn/problem/P4999)

```cpp
#include <cstdio>
#include <cstring>
#define int long long

const int MAXN = 15;
int a[ MAXN + 5 ] , len , dp[ MAXN + 5 ][ MAXN + 5 ];

int dfs( int pos , int lead , int limit , int sum , int digt ) {
	if( pos == len + 1 ) return sum;
	if( ~dp[ pos ][ sum ] && !lead && !limit ) return dp[ pos ][ sum ];
    
	int Ans = 0 , Mbit = limit ? a[ len - pos + 1 ] : 9;
	for( int i = 0 ; i <= Mbit ; i ++ ) {
		if( lead && i == 0 ) Ans += dfs( pos + 1 , 1 , limit & ( i == Mbit ) , sum , digt );
        else                 Ans += dfs( pos + 1 , 0 , limit & ( i == Mbit ) , sum + ( i == digt ) , digt );
	}
	if( !lead && !limit ) dp[ pos ][ sum ] = Ans;
	return Ans;
}
int Solve( int digt , int x ) {
    if( x < 0 ) return 0;
	len = 0; for( ; x ; x /= 10 ) a[ ++ len ] = x % 10;
	memset( dp , -1 , sizeof( dp ) );
	return dfs( 1 , 1 , 1 , 0 , digt );
}

int t , l , r , Ans;
signed main( ) {
    scanf("%lld",&t);
    while( t -- ) {
        scanf("%lld %lld",&l,&r);
        Ans = 0;
        for( int i = 0 ; i <= 9 ; i ++ ) Ans += i * ( Solve( i , r ) - Solve( i , l - 1 ) );
        printf("%lld\n", Ans );
    }
	return 0;
} 
```


---

## 作者：封禁用户 (赞：0)

这道题和[那道题](https://www.luogu.com.cn/problem/P4999)一模一样……

## 分析

**【总体思路】**

我们在搜索函数中定义一个变量来存当前选择的数的总和。对于每一位的所有能够取到的值，都枚举一遍即可。注意的是，这道题并不需要判断是否含有前导零哦。当然，判断一下前导零也没有什么问题。

**【记忆化搜索】**

首先，在搜索函数中，我们需要定义以下几个变量：目前寻找的是第几位；目前的数字之和；能选择的数是否有上界。

函数如：
```
int dfs(int now,int ans,bool if_l)
```

其次，在特判一些情况时，我们直接套模板就行了，只需注意在最后一位时，我们返回的值是数字的总和，而不是别的。

最后，在枚举这一位选择的所有情况时，我们直接将原来的和加上这一位选定的值就行了。

最终函数如下：

```cpp
int dfs(int now,int ans,bool if_l)
{
	if(!now) return ans;//最后一位 
	else
	{
		if(!if_l&&f[now][ans]!=-1) return f[now][ans];//找过了 
		else
		{
			int ans_s=0,up=if_l?a[now]:9;
			for(int i=0;i<=up;i++)
				ans_s+=dfs(now-1,ans+i,if_l&&i==up);//累加ans的值 
			return if_l?ans_s:f[now][ans]=ans_s;
		}
	}
}
```

**【主函数】**

我们按照前缀和的思想进行寻找，输出就行。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=20,M=200;
int a[N],f[N][M];//位数不超过16，各位之和不超过9*15 
int l,r;
int dfs(int now,int ans,bool if_l)
{
	if(!now) return ans;
	else
	{
		if(!if_l&&f[now][ans]!=-1) return f[now][ans];
		else
		{
			int ans_s=0,up=if_l?a[now]:9;
			for(int i=0;i<=up;i++)
				ans_s+=dfs(now-1,ans+i,if_l&&i==up);
			return if_l?ans_s:f[now][ans]=ans_s;
		}
	}
}
int check(int x)
{
	memset(f,-1,sizeof(f));
	int len=0;
	while(x) a[++len]=x%10,x/=10;
	return dfs(len,0,1);
}
signed main()
{
	int t;cin>>t;
	while(t--)
	{
		cin>>l>>r;
		cout<<check(r)-check(l-1)<<endl;
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

**【题目分析】**

从多倍经验看过来的，~~惊讶的发现可以水题解。~~

这道题是数位 dp 模板题之一，我们边看代码边讲。

首先确定总体思路：一次性统计出十个数字的出现频率较难，因此我们分开处理每一个数字的出现次数。

- 第一部分 搜索

采取搜索的方式，`pos` 代表搜到了哪一位，`numi` 代表这一次选定的数字（参数 `k`）出现的次数，`lim` 表示当前位是否有限制（$1$ 表示有限制），`pre` 表示当前位是否为前导零（$1$ 表示是）。

```cpp
int dfs(int pos,int numi,bool lim,bool pre,int k){
	if(pos == 1) return numi;
	int up = lim ? num[pos-1]:9;
	int ans = 0;
	for(int i = 0;i <= up;i ++){
		ans += dfs(pos-1,numi + (k == 0?(!pre && i == k):(i == k)),(lim && i == up),(pre && i == 0),k);
	}
	return ans;
}
```
`up` 的含义是**当前枚举位的最高限制**，是为了让枚举的数字不超过给定数字。

`numi + (k == 0?(!pre && i == k):(i == k))` 的意思是如果我们在统计 $0$ 的数量，那么如果是前导零计数器就不能增加；否则只要这一位与统计的数字相等，计数器自增。

`(lim && i == up)` 是指如果之前有限制，并且这一位还与上界相等，那么限制依然存在。为什么用与运算而不用或运算？举个例子，我们的枚举上限是 $114514$，目前枚举到的是 $1045$，此时虽然 $5$ 这一位相等，但是不论以后怎么枚举，我们枚举的数字一定小于 $114514$。

`(pre && i == 0)` 是指如果这一位是前导零，并且枚举的还是 $0$，那么前导零状态就要延续。

至此本题的重点——搜索部分就写完了。

但是纯暴力搜索复杂度是不优的，因此我们需要采用**记忆化搜索**。

- 第二部分 记忆化搜索

我们直接选取 `dfs` 函数的参数当作状态，设 `f[pos][numi][lim][pre]` 表示艘至第 `pos` 位，当前数字出现了 `numi` 次，限制和前导零状态分别为 `lim` 和 `pre` 时的答案，初始化为 `-1`。在搜索函数中添加判断语句，如果当前状态下 $f \ne -1$，则直接返回该值。每次搜索完毕后，将答案赋给 $f$ 数组。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[15][15][2][2],num[15],n,l,r;
int dfs(int pos,int numi,bool lim,bool pre,int k){
	if(f[pos][numi][lim][pre] != -1) return f[pos][numi][lim][pre];
	if(pos == 1) return numi;
	int up = lim ? num[pos-1]:9;
	int ans = 0;
	for(int i = 0;i <= up;i ++){
		ans += dfs(pos-1,numi + (k == 0?(!pre && i == k):(i == k)),(lim && i == up),(pre && i == 0),k);
	}
	return f[pos][numi][lim][pre] = ans;
}
int work(int x,int k){
	memset(f,-1,sizeof(f));
	int u = 0;
	while(x){
		num[++u] = x % 10;
		x /= 10;
	}
	n = u;
	return dfs(n+1,0,1,1,k);
}

```

输出时，枚举 $0\sim 9$ 的数字，记数字 $i$ 出现的数量为 $g(i)$，则最后所求答案为 $\sum\limits^{9}_{i=1}i\times g(i)$。

结尾闲话：其实本题毫无统计数字 $0$ 的必要（

---

## 作者：fls233666 (赞：0)

首先我们发现，我们要求的数字和范围很大 $(0 \le a \le b \le 10^{15})$,直接暴力显然会爆掉。但是，从另一方面来看，我们要统计数字和的数字最多只有 $15$ 位。如果我们能按数位计算共享，则一定能快速得到答案。这时候就要使用**数位DP**了。

首先我们来设计状态。根据题意，我们可以设 $f(i,j,0/1)$ 表示当前已经计算了前 $i$ 位，数字和为 $j$，是否达到上边界。看起来这个状态就很合理，我们可以来考虑下一步了。

本来我们应该开始写转移方程了。但有一种更暴力的更简单直接的做法——**记忆化搜索**。根据我们设计得到的状态，我们记忆化搜索，搜到数位超过边界时返回数位和即可。于是有了以下搜索函数：

```cpp
ll work(int di,ll sum,bool ckmax){
	if(di==lmax)
		return sum; //搜到边界返回数字和
	if(f[di][sum][ckmax]!=-1)
		return f[di][sum][ckmax];  //搜过当前状态直接返回
	int top=ckmax?9:maxnum[di];  //判断边界
	f[di][sum][ckmax]=0;
	for(rgt i=0;i<=top;i++){
		f[di][sum][ckmax]=f[di][sum][ckmax]+work(di+1,sum+i,(i<top)||ckmax); //暴力枚举当前位该填的数字进行搜索
	} 
	return f[di][sum][ckmax];  //返回结果
}
```

再加上主函数的初始化，这题的代码就完成了。

另外，有以下两点需要提醒：

1. 题目要我们求的是 $[a,b]$ 内数字的数字和，而我们的搜索求的是 $[1,R]$ 的数字和。我们运用前缀和的知识，分别求出 $[1,b]$ 与 $[1,a-1]$ 两部分的数字和，相减即可得到答案；
2. 可以发现，题目要我们求的数字和的左边界 $a$ 是可以取到 $0$ 的。那么 $a-1$ 会变成 $-1$，导致代码出错。需要特判。

完整版代码放上：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define rgt register ll
using namespace std;

ll f[18][158][2];
ll ans,inl,inr;
ll maxnum[18],lmax;

ll work(int di,ll sum,bool ckmax){
	if(di==lmax)
		return sum; //搜到边界返回数字和
	if(f[di][sum][ckmax]!=-1)
		return f[di][sum][ckmax];  //搜过当前状态直接返回
	int top=ckmax?9:maxnum[di];  //判断边界
	f[di][sum][ckmax]=0;
	for(rgt i=0;i<=top;i++){
		f[di][sum][ckmax]=f[di][sum][ckmax]+work(di+1,sum+i,(i<top)||ckmax); //暴力枚举当前位该填的数字进行搜索
	} 
	return f[di][sum][ckmax];  //返回结果
}

int main(){
	int test;
	scanf("%d",&test);
	while(test--){
	scanf("%lld%lld",&inl,&inr);//数据读入
	
   inl--;
	lmax=0;
	for(rgt i=0;i<=16;i++)
		for(rgt j=0;j<=140;j++)
			for(rgt k=0;k<2;k++)
				f[i][j][k]=-1;
   //初始化f数组
   
	while(inr){
		maxnum[lmax]=inr%10;
		lmax++;
		inr/=10;
	}  //拆分边界数字用于搜索判断边界
	reverse(maxnum,maxnum+lmax);  //拆得的数字是反过来的，要翻转
    
	ans=work(0,0,false);//算 [1,b] 答案
	if(inl>=1){  //老特判了
    
		for(rgt i=0;i<=16;i++)
			for(rgt j=0;j<=140;j++)
				for(rgt k=0;k<2;k++)
					f[i][j][k]=-1;
		lmax=0;
		while(inl){
			maxnum[lmax]=inl%10;
			lmax++;
			inl/=10;
		}
		reverse(maxnum,maxnum+lmax); 
      //重新初始化和拆边界数字
        
		ans=ans-work(0,0,false);//算 [1,a-1] 答案并得到最终答案
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：cherubim (赞：0)

（竟然还有多倍经验可以交题解！）

分析题目：第一眼看到思维那当然就是暴力，直接枚举并写函数来分解每一个数，然后用一个数组乘起来统计最后输出。思路当然是简单的，可是一看这数据范围就给吓傻了QAQ

暴力不行，那就必须得用其他思路来写了

可是蒟蒻不会数位DP啊QAQ，这可怎么办呢

~~这时候就应该用数位DP的思想来混子了~~

数位dp其实就是两个部分。初始化、求解。那我们可以大致了解一下思路后，用一种稍微高一点的时间复杂度的方式按照数位dp的思路来枚举。

这个题要输出的答案我们可以发现是每一个数字出现的次数乘这个数字本身再相加的结果。求 $a$ 到 $b$ ，那么就用 $solve(b + 1) - solve(a）$ 来计算。

我们不妨可以设 $f[i][j][k]$ 表示第i位，最高位为j，k有多少个。
那么我们就可以用f数组来表示我们的每一个数位。

稍微分析一下就可以知道，第i位上k出现的次数为 $\sum\limits_{l=0}^ f[i-1][l][k] $ +这个数在i位上出现的次数 。 i-1 来继承上一位统计的这个数字出现的次数。那么，怎么计算这个数在这个数位出现了多少次呢?

简单分析一下：如果 $j < k$ 或 $j > k$ ，那就没有。

当 j==k时， 举个栗子，比如说 $[100,199]$ , 可以看出数字1肯定出现了100次，那么就可以推出：$f[i][j][j]+=10^{i-1}$。

那么接下来只要注意处理前导0的情况，按照位数依次统计就行了。


### CODE
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000010
#define INF 1<<30
#define mod 100000007

using namespace std;

int a,b;
int f[110][110][110]; 

int solve(int x,int num){
	int kkk[1000];
	int ans=0,len=0;
	memset(kkk,0,sizeof(kkk));
	while(x!=0){
		kkk[++len]=x%10;
		x/=10;
	}
	for(int i=1;i<len;i++){
		for(int j=1;j<=9;j++){
			ans+=f[i][j][num];
		}
	}
	
	for(int i=1;i<kkk[len];i++)  //统计位数与原数一样，但最高位较小的数，不能有前导零；
		ans+=f[len][i][num];
    for(int i=len-1;i>=1;i--){
    	int x_x=kkk[i];
    	for(int j=0;j<x_x;j++)
    		ans+=f[i][j][num];
		for(int j=len;j>i;j--)
			if(kkk[j]==num) ans+=kkk[i]*pow(10,i-1);
	}
	return ans;
}
signed main()
{
	//初始化
	for(int i=0;i<=9;i++) f[1][i][i]=1;
	for(int i=2;i<=100;i++){//总共的位数 
		for(int j=0;j<=9;j++){ //此位数 
			for(int l=0;l<=9;l++){//上位数 
				for(int r=0;r<=9;r++){ //统计 
					f[i][j][r]+=f[i-1][l][r]; 
				}
			}
			f[i][j][j]+=pow(10,i-1);
		}
	}
	 
	int T;
	cin>>T;
	while(T--){
		scanf("%lld %lld",&a,&b);
		int ans=0;
		for(int i=0;i<=9;i++)
			ans+=(solve(b+1,i)-solve(a,i))*i;	
		printf("%lld\n",ans);
	}
	
	return 0;
}
```



---

## 作者：hovny (赞：0)

## [题面](https://www.luogu.com.cn/problem/SP17247)

## 解题思路

**数位 $DP$**

### 分析

关于数的相关计算，很容易使人想到数位 $DP$，直接记搜即可

如何 $DP$？

众所周知，这里我们只要先把每个数拆成几个数字，然后 $dfs$ 的时候记录 $k,st,op$，分别表示当前是从最低位开始的第 $k$ 位，$st$ 表示当前已枚举的前几位的和，$op$ 表示是否前几位是否达到上界，开数组记忆化即可

### Warning

1、传值的时候注意 $long\ long$

2、注意数组 $st$ 那维的大小

## Code

```cpp
#include<bits/stdc++.h>
#define rgt register
#define rint rgt int
#define LL long long
#define rll rgt LL
#define inf 0x7f7f7f7f
using namespace std;
template<class K>inline bool cmax(K&a,const K&b){return (a<b)?a=b,1:0;}
template<class K>inline bool cmin(K&a,const K&b){return (a>b)?a=b,1:0;}
int num[19],t,nm,T;
LL f[19][191][2],l,r;
inline LL dfs(rint k,rint st,rint op) {
	if(!k) return st;
	if(~f[k][st][op]) return f[k][st][op];
	rint i,t=op?num[k]:9;rll res=0;
	for(i=0;i<=t;i++) res+=dfs(k-1,st+i,op&(i==t));
	return f[k][st][op]=res;
}
inline LL solve(rll c) {
	t=0;while(c) num[++t]=c%10,c/=10;
	memset(f,-1,sizeof(f));//记得初始化为0
	return dfs(t,0,1);
}
int main() {
	scanf("%d",&T);
	while(T--)
		scanf("%lld%lld",&l,&r),l=max(l-1,0ll),//不能为-1
		printf("%lld\n",solve(r)-solve(l));//差分
	return 0;
}
```



---

