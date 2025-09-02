# K-periodic Garland

## 题目描述

You are given a garland consisting of $ n $ lamps. States of the lamps are represented by the string $ s $ of length $ n $ . The $ i $ -th character of the string $ s_i $ equals '0' if the $ i $ -th lamp is turned off or '1' if the $ i $ -th lamp is turned on. You are also given a positive integer $ k $ .

In one move, you can choose one lamp and change its state (i.e. turn it on if it is turned off and vice versa).

The garland is called $ k $ -periodic if the distance between each pair of adjacent turned on lamps is exactly $ k $ . Consider the case $ k=3 $ . Then garlands "00010010", "1001001", "00010" and "0" are good but garlands "00101001", "1000001" and "01001100" are not. Note that the garland is not cyclic, i.e. the first turned on lamp is not going after the last turned on lamp and vice versa.

Your task is to find the minimum number of moves you need to make to obtain $ k $ -periodic garland from the given one.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
9 2
010001010
9 3
111100000
7 4
1111111
10 3
1001110101
1 1
1
1 1
0```

### 输出

```
1
2
5
4
0
0```

# 题解

## 作者：H6_6Q (赞：9)

### 题目大意：
给你一个长度为 $n$ 的 $01$ 字符串，要求让这个字符串的每个 $1$ 字符之间的距离恰好都为 $k$ ，问至少要修改几个字符。

### 思路：
显然这是道 dp 题。

- $dp_{i ,0}$ 表示到第 $i$ 个字符为止，只让第 $i$ 位为 $1$，其余 $i-1$ 位均位 $0$ 时需要的操作次数。

- $dp_{i,1}$ 表示到第 $i$ 个字符为止，让第 $i$ 位为 $1$，且保证在这之前合法所需要的最少操作次数。

那显然，只要维护一个前缀和 $sum_i$ ，统计到第 $i-1$ 个字符位置 $1$ 的数量，那么：

$$dp_{i,0}=\begin{cases}sum_{i-1}\ \ \ \ \ \ (s_i=1)\\sum_{i-1}+1\ \ \ \ \ \ (s_i=0)\end{cases}$$

Ps: $s_i$ 表示字符串的第 $i$ 位所表示的字符。 

同时，我们也很容易推出另外一个转移式：

$$\mathop{dp_{i,1}}\limits_{i-k\ge1}=\begin{cases}\min(dp_{i-k,1},dp_{i-k,0}) + sum_{i-1}-sum_{i-k} \ \ \ \ \ \ (s_i=1)\\\min(dp_{i-k,1},dp_{i-k,0}) + sum_{i-1}-sum_{i-k}+1 \ \ \ \ \ \ (s_i=0)\end{cases}$$

这很好理解，只要保证第 $i-k$ 个位置为 $1$ 并将 $(i-k+1)\sim (i-1)$ 中的所有 $1$ 都设为 $0$ 即可，这步同样可以用前缀和维护。

最后计算答案的时候，将 $dp$ 数组从后往前扫一遍，每次在 $dp_{i,0}\;,\;dp_{i,1}$ 中取 $\min$ 。在扫的同时维护一个 $num$ 表示从 $(i+1) \sim n$ 这段中 $1$ 的数量，统计答案的时候要加上这个 $num$，意味着吧 $(i+1) \sim n$ 中所有的 $1$ 设为 $0$，防止出现不合法的情况。

时间复杂度：$\text{O}(n)$

### Code：
```
#include<bits/stdc++.h>

using namespace std;

int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

const int N=1e6+5,inf=0x7f7f7f7f;
int t,n,k,dp[N][2],sum[N],ans;
char s[N]; 

int main()
{
	memset(dp,0x7f,sizeof(dp));
    // 将 dp 数组初始化，将所有可能先设为不合法
	t=read();
	while(t--)
	{
		n=read();k=read();
		scanf("%s",s+1);
		for(int i=1;i<=n;++i)
        // 统计前缀和
			sum[i]=sum[i-1]+(s[i]-'0');
        ans=sum[n];  // 这里的意思是把答案初始化为：把所有的 1 都变成 0 所需要的操作次数
		for(int i=1;i<=n;++i)
		{
			dp[i][0]=sum[i-1];
            // dp[i][0] 的转移
			if(i-k>=1)
				dp[i][1]=min(dp[i-k][1]+sum[i-1]-sum[i-k],dp[i-k][0]+sum[i-1]-sum[i-k]);
            // dp[i][1] 的转移
			if(s[i]=='0')
			{
				if(dp[i][0]!=inf)
					dp[i][0]++;
				if(dp[i][1]!=inf)
					dp[i][1]++;
			}
				
		}
		int num=0;
        // 统计答案的时候维护一个 num，防止出现不合法情况
		for(int i=n;i>=1;--i)
		{
			ans=min(ans,min(dp[i][1]+num,dp[i][0]+num));
			if(s[i]=='1')
				num++;
		}
			
		for(int i=1;i<=n;++i)
        // 这是这题的一个坑点，直接 memset 会 T，必须手动清空
		{
			sum[i]=0;
			dp[i][0]=inf;
			dp[i][1]=inf;
		} 
		printf("%d\n",ans);
	}
	return 0;
} 

```


---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 1900}$
---
### 解题思路：

发现一共有 $k$ 个互不干扰的独立子问题，只要确定了其中的某一个就只能选择同类型的了。

然后发现转化后的问题就是让一个连续区间内的字符全都变成 $1$。

更换一下贡献的计算方式。先将所有的 $1$ 全都变成 $0$，然后考如果选择了一个原来是 $1$ 的变回去获得 $1$ 的价值，原来是 $0$ 消耗 $1$ 的代价。

这样就变成了给一个序列每一个位置上有一个价值，选出一段连续区间让其价值最大的经典问题了。

复杂度 $O(n)$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[1000006],k,ans,cnt,now;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		cnt=0;
		for(int i=1;i<=n;i++){
			scanf("%1d",&a[i]);
			cnt+=(a[i]==1);
		}
		ans=2147483647;
		for(int i=1;i<=k;i++){
			now=0;
			for(int j=i;j<=n;j+=k){
				if(a[j]==1)now++;
				else now--;
				if(now<0)now=0;
				ans=min(ans,cnt-now);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：蒟酱 (赞：2)

题意：给一个长度为 $n$ 的 01 字符串，要让这个字符串的每个 1 之间的距离恰好都为 $k$，请问至少要修改几个字符。

这里给出一种贪心做法：考虑一种万能方案，将所有字符串全部改成 0，这样就不会出现两个 1 之间的距离不是 $k$ 的情况，如果这么做修改数量就是字符串中 1 的个数。这里介绍一个 `std` 命名空间的函数 `std::count`，可以在线性时间内统计某个量的数量。~~但是用 for range 循环写法更短~~。

```cpp
for(i=0;i<s.length();i++)if(a[i]=='1')sum++;
for(auto it:s)if(it=='1')sum++;
sum=std::count(s.begin(),s.end(),'1');
```
接下来继续分析，发现所有 1 的出现肯定是聚在一起，不可能出现 2 段这种情况，否则就会不满足题意。考虑枚举第一个区间的位置 $i=[0,k-1]$，每次将指针 $j$ 右移 $k$ 位。如果 $s_j$ 是 0，那么必须变成 1，即 `cnt++`，否则代表刚刚 1 的数量多数了，即 `cnt--`，每次指针移动后与 $ans$ 取较小值，这样所有从最左端开始的区间就枚举完毕了。

但是还有以中间开始的情况，可以认为像前缀和一样，一条长区间割掉一条短区间。（~~你不会以为我要讲 dp 了吧~~）所以在每次指针转移时还有另一种方法：对之前进行的所有改变不作改变，即 `cnt=0` 。这样所有情况都会被考虑到。

~~还是代码~~
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<string>
std::string s;
using std::cin;using std::cout;
template<typename any>inline any min(any x,any y){return x<y?x:y;}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int i,j,n,m,T;
	cin>>T;
	while(T--){
		cin>>n>>m>>s;
		int sum=std::count(s.begin(),s.end(),'1'),ans=0x3f3f3f3f,cnt;
		for(i=0;i<m;i++)for(cnt=0,j=i;j<n;j+=m)
			cnt=min(s[j]=='1'?cnt-1:cnt+1,0),
			ans=min(ans,sum+cnt);
		cout<<ans<<'\n';
	}
	return 0;
}
```
关于时间复杂度：我自己测出来的结果比 dp 快不少。因为 $T$ 组数据最外层循环做 $T$ 次，中层循环 $k$ 次来枚举左端点，内层循环 $\dfrac{|s|}{k}$，全部乘起来就是 $O(T|s|)$ 和 dp 一模一样但是不仅不用 $f_{i,j}$ 而且常数很小自然而然比 dp 快了。

---

## 作者：harmis_yz (赞：1)

## 分析

考虑 DP。

定义状态函数 $f_i$ 表示处理完前 $i$ 个字符且第 $i$ 个字符为 $1$ 时的最小代价。则对于 $i$，有两种情况：

1. $i$ 不是第一个 $1$，则上一个 $1$ 的位置必定为 $i-k$。
2. $i$ 是第一个 $1$，没有上一个 $1$。

得到转移方程：$f_i = \min (f_{\max(0,i-k)}+w(\max(0,i-k),i-1),w(0,i-1))+[c_i \ne 1]$。其中 $w(l,r)$ 表示 $[l,r]$ 中 $1$ 个数量，也就是将区间全部变成 $0$ 的最小代价。

对于答案，枚举最后一个 $1$ 的位置，然后后面的 $1$ 全部变成 $0$。即 $ans= \min\limits_{i=0}^{n}f_i+w(i+1,n)$。


复杂度 $O(n)$。

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

const int N=1e6+10;
int n,k;
int f[N],s[N];
char c[N];

il int w(int l,int r){
	if(l>r) return 0;
	return s[r]-s[l-1];
}

il void solve(){
	n=rd,k=rd,scanf("%s",c+1);
	for(re int i=1;i<=n;++i) s[i]=s[i-1]+c[i]-'0';
	int ans=1e9+7;
	for(re int i=1;i<=n;++i)
		f[i]=min(f[max(0*1ll,i-k)]+w(max(0*1ll,i-k)+1,i-1),f[0]+w(1,i-1))+(c[i]!='1');
	for(re int i=0;i<=n;++i)
		ans=min(ans,f[i]+w(i+1,n));
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=rd;while(t--)
	solve();
	return 0;
}

```

---

## 作者：ivyjiao (赞：0)

模拟赛考了，来写一下。

首先字符串全 $0$ 显然答案是 $0$，这个在我这种做法中需要特判。

因为我的 dp 状态是 $dp_{i,0}$ 为第 $i$ 位为 $1$，前面都为 $0$ 至少要修改几个字符；$dp_{i,1}$ 为第 $i$ 位为 $1$，第 $i-k$ 位也为 $1$ 至少要修改几个字符，所以不会顾及全 $0$ 的情况。

对于 $dp_{i,0}$，显然有（$b_i=\sum_{j=1}^i a_j$）：

$$dp_{i,0} = \begin{cases}
  b_{i-1}+1 & a_i=0 \\
  b_{i-1} & a_i=1
\end{cases}$$

对于 $dp_{i,1}$，我们要把 $(i-k,i)$ 内的 $1$ 全部改成 $0$，显然要改 $b_{i-1}-b_{i-k}$ 次，所以有：

$$dp_{i,1} = \begin{cases}
  \min(dp_{i-k,0},dp_{i-k,1})+b_{i-1}-b_{i-k}+1 & a_i=0 \land i>k \\
  \min(dp_{i-k,0},dp_{i-k,1})+b_{i-1}-b_{i-k} & a_i=1 \land i>k \\
  \inf & i\leq k
\end{cases}$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1;
int t,n,k,a[N],b[N],dp[N][2],ans;
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cin>>t;
    while(t--){
        ans=1e6;
        cin>>n>>k>>s;
        for(int i=1;i<=n;i++) a[i]=s[i-1]-'0';
        for(int i=1;i<=n;i++) b[i]=b[i-1]+a[i];
        for(int i=1;i<=n;i++){
            dp[i][0]=b[i-1]+!a[i];
            dp[i][1]=1e7;
            if(i>k) dp[i][1]=min(dp[i][1],min(dp[i-k][0],dp[i-k][1])+b[i-1]-b[i-k]+!a[i]);
        }
        for(int i=1;i<=n;i++) ans=min(ans,min(dp[i][0],dp[i][1])+b[n]-b[i]);
        if(!b[n]) ans=0;
        cout<<ans<<endl;
    }
}
```

---

## 作者：_edge_ (赞：0)

提供一种可能不太一样的 DP 做法。

首先，我们把原始的字符串处理掉，开头的 $0$ 和结尾的 $0$ 都扔掉。

扔掉了以后，我们把取模 $k$ 的余数相同的数字都拿出来。

单独考虑每一个，对于一个余数来说，其他余数出现的 $1$ 必定是要删掉的。

这个可以直接统计答案。

考虑在当前这个余数内的字符串如何统计最小值。

我们发现，如果除去开头的 $0$ 和结尾的 $0$，其他都要是 $1$。

也就是他必须要长成 $0000011111100000$ 这样子的形式。

于是我们就设 $f_{i,j}$ 表示当前到达第 $i$ 位，目前是第 $j$ 段，总共有三段。

转移就是第一段到第二，第二到第三段。

然后就好了，总时间复杂度是 $O(n)$，但是常数略大。

```cpp
#include <iostream>
#include <cstdio>
#define pb push_back
using namespace std;
const int INF=1e6+5;
string s1,s2,s3[INF];
int n,k,P[INF],P1[INF],t,f[INF][5];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while (t--) {
		cin>>n>>k;s2.clear();
		for (int i=0;i<=k;i++) P[i]=P1[i]=0,s3[i].clear();
		cin>>s1;int l=0,r=s1.size()-1;
		while (s1[l]=='0') l++;
		while (s1[r]=='0') r--;
		for (int i=l;i<=r;i++)
			s2+=s1[i];
		int len=s2.size(),sum=0;
		for (int i=0;i<len;i++) {
			s3[i%k].pb(s2[i]);
			if (s2[i]=='1') sum++,P[i%k]++;
			else P1[i%k]++;
		}
		int ans=1e9;
		for (int i=0;i<k;i++) {
			int res=sum-P[i],len=s3[i].size();s3[i]=" "+s3[i];
			for (int j=1;j<=len;j++) {
				f[j][0]=f[j-1][0]+(s3[i][j]=='1');
				f[j][1]=min(f[j-1][0],f[j-1][1])+(s3[i][j]=='0');
				f[j][2]=min(f[j-1][1],f[j-1][2])+(s3[i][j]=='1');
			}
			res+=min(min(f[len][0],f[len][1]),f[len][2]);
			ans=min(ans,res);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：RemiliaScar1et (赞：0)

## CF1353E K-periodic Garland

[博客地址](https://www.cnblogs.com/IzayoiMiku/p/14646647.html)

由题意，每个位置上有且只有 $0/1$ 两种状态，且我们若是求出前缀和就能快速得出其中某一段中 $1$ 的个数。

首先看一下如果让我们构造怎么构造。我们要构造一个 $1$ 之间距离恰好为 $k$ 的序列，就是说位置上的状态每次转移到 $1$ ，都必须转移回到 $0$ ，在 $0$ 的状态呆 $k$ 次再转移回 $1$ 状态。

画出状态机如下：
![](https://img.imgdb.cn/item/6073920b8322e6675c6d6f54.png)

由这个图我们先得出一个暴力且错误的状态转移方程：

$f(i)=f(i-k)+sum(i-1)-sum(i-k)+[s_i=0]$，其中$f(i)$ 表示构造第一位是 $1$ 的序列需要改造的步数 ，$sum$ 是原来序列的前缀和，$s_i$ 是原序列。

这个东西为什么错误？因为我们不敢说第一位一定是 $1$，说不定答案的序列开头很长一段都是 $0$。我们首先想到，这个问题可以大力枚举前面 $0$ 的位数解决。假设我们把前 $i-1$ 位设为 $0$，第 $i$ 位设成 $1$ 的代价为 $g(i)$，我们很容易得到：$g(i)=sum(i-1)+[s_i=0]$。

我们修改状态 $f(i)$ 为到第 $i$ 位为 $1$ 时，前面均合法且至少有一个 $1$ 的最小代价。

那么我们可以得到状态转移方程：$f(i)=\min(\ f(i-k),\ g(i-k)\ )+sum(i-1)-sum(i-k)+[s_i=0]$。

我们的后缀仍然有可能全是 $0$ ，所以统计答案时，我们枚举构造序列长度 $i$ ，同时维护一个值 $z$ 表示将以 $i+1$ 为起点的后缀全部设为 $0$ 的代价。答案就是 $\text{Min}_{i=1}^n\min(\ f(i)\ ,\ g(i)\ )+z(i)$

个人感觉难度 绿-蓝

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=4e6+10;
int f[N],g[N],sum[N];
char str[N];

int main()
{
	int t; cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k>>(str+1);
		for(int i=0;i<=n;i++) f[i]=0x3f3f3f3f,sum[i]=0;
		for(int i=1;i<=n;i++)
			sum[i]=sum[i-1]+(str[i]-'0'), g[i]=sum[i-1]+int(str[i]=='0');
		for(int i=1;i<=n;i++)
			if(i>k) f[i]=min(f[i-k],g[i-k])+sum[i-1]-sum[i-k]+int(str[i]=='0');
		int ans=sum[n];
		for(int i=1;i<=n;i++)
			ans=min(ans,min(f[i],g[i])+sum[n]-sum[i]);
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：Michael1234 (赞：0)

本题可以使用动态规划的方法：

我们考虑 dp 状态：

$dp_{i,0}$ 表示将前 $i-1$ 位全部变成 $0$ 并且将第 $i$ 设为 $1$ 所需的代价。

$dp_{i,1}$ 表示将前 $i-1$ 位设为合法状态并且此时第 $i$ 位是 $1$ 所需的代价。

有转移方程：

$$dp_{i,0}=(\sum_{j=1}^{i}{[s_j=1]})+[s_i=0]$$

$$dp_{i,1}=\min(dp_{i-k,0},dp_{i-k,1})+(\sum_{j=i-k+1}^{i-1}{[s_j=1]})+[s_i=0]$$

最终答案为：

$$ans=\min_{i=1}^{n}{[(\sum_{j=i+1}^{j=n}{[s_j=1]})+\min(dp_{i,0},dp_{i,1})]}$$

可前缀和优化使得时间复杂度降为 $O(n)$。

即：

  $$sum_i=sum_{i-1}+s_i$$

---

