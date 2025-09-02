# Fixed Points

## 题目描述

一个整数序列 $a1,a2,...,a_n$，一次操作，可以删除一个数，然后该数右侧的数向左移动一个单位。对于一个长度为 $n$ 的整数序列 $b_i$ ，求最少需要删除几个数后，会有至少 $k$ 个 $i$ 满足 $b_i=i$ 。

## 说明/提示

对于第一个测试数据，序列不满足所需条件，但可以通过删除第一个数来提供，序列为 $[1,2,3,4,5,6]$，有 $6$ 个数满足条件。

对于第二个测试数据，有两种方法：第一种是删除 $a_1$ 和 $a_3$ ；第二种是删除 $a_2$ 和 $a_3$ 。

## 样例 #1

### 输入

```
4
7 6
1 1 2 3 4 5 6
5 2
5 1 3 2 3
5 2
5 5 5 5 4
8 4
1 2 3 3 2 2 5 5```

### 输出

```
1
2
-1
2```

# 题解

## 作者：白鲟 (赞：14)

## 前言
啊啊啊啊啊为啥昨天我搞 F 去了根本没看 E……

刚刚开题秒解了……

## 题目分析
由于把前 $i$ 个数删到仅剩 $j$ 个数所删的代价是 $i-j$，且删除过后不具有后效性，设 $f_{i,j}$ 表示把前 $i$ 个数删到仅剩 $j$ 个数能获得的最大的 $i=a_i$ 个数，则 $f_{i,j}=\max(f_{i-1,j},f_{i-1,j-1}+[j=a_i])$，完成 DP 过程时间复杂度为 $\operatorname{O}(n^2)$。

在所有满足 $f_{i,j}\ge k$ 的 $i-j$ 取最小值即可。

## 代码
```cpp
#include<algorithm> 
#include<cstdio>
using namespace std;
const int maxn=2000;
int T,ans,n,k,a[maxn+1],f[maxn+1][maxn+1];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0x7f7f7f7f;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;++i)
			for(int j=1,maxx=0;j<=i;++j)
			{
				f[i][j]=max(f[i-1][j-1]+(j==a[i]),f[i-1][j]);
				if(f[i][j]>=k)
					ans=min(ans,i-j);
			}
		printf("%d\n",ans==0x7f7f7f7f?-1:ans);
	}
	return 0;
} 
```

---

## 作者：zhaoyp (赞：5)

# Solution
设 $dp_{i,j}$ 表示对原序列前 $i$ 个数，删除 $j$ 个数的最大收益。
 
考虑对第 $i$ 个数进行操作：

1. 若删除第 $i$ 个数，则有 $dp_{i,j} = dp_{i - 1,j - 1}$。
2. 若保留第 $i$ 个数，那么此时该数在修改后的序列中为第 $i - j$ 个数，则有 $dp_{i,j} = dp_{i - 1,j} + [a_i = i - j]$。

综上可得 $dp_{i,j} = \max\{dp_{i - 1,j - 1},dp_{i - 1,j} + [a_i = i - j]\}$，特别的 $dp_{i,0} = dp_{i - 1,0} + [a_i = i]$。

最后只要求最小的一个 $j$，满足 $dp_{n,j} \ge k$ 即可。

注意到 $dp_i$ 的值仅从 $dp_i$ 和 $dp_{i - 1}$ 转移来，便可用滚动数组滚掉一维，但注意 $j$ 要从大到小枚举。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,a[2005],dp[2005];
bool flag;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(dp,0,sizeof(dp));
		flag = 0;
		scanf("%d%d",&n,&k);	
		for(int i = 1;i <= n;i++)
			scanf("%d",&a[i]);
		for(int i = 1;i <= n;i++)
			for(int j = i;j >= 0;j--)
				dp[j] = max(dp[max(0,j - 1)],dp[j] + (int)(a[i] == i - j));
		for(int i = 0;i <= n;i++)
			if(dp[i] >= k)
			{
				printf("%d\n",i);
				flag = 1;
				break;
			}
		if(!flag) 
			puts("-1");
	} 
	return 0;
} 
```

---

## 作者：RedLycoris (赞：3)

这道题的一血，纪念一下

![](https://cdn.luogu.com.cn/upload/image_hosting/9esb4yqq.png)

---

观察一个数什么时候能对答案产生贡献。

从前往后数，如果在第 $i$ 个数之前，有 $j$ 个数被删除了，那么这个数现在的位置变成了 $i-j$，故当且仅当 $i-j = a_i$ 的时候会对答案产生贡献。

所以我们可以列出 dp 方程：

令 $dp_{i,j}$ 表示考虑到从前往后第 $i$ 个位置，在它之前已经删除了 $j$ 个数时，最大的答案。

可以得到如下的转移方程：

```
dp[i+1][j]=max(dp[i+1][j],dp[i][j]+(bool)(a[i]+j==i)); //保留这个数
dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]);           //删除这个数
```

完事了~

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
const int mxn=2002;
int n,k,a[mxn];
int dp[mxn][mxn];
inline void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=0;i<=n+1;++i)for(int j=0;j<=n+1;++j)dp[i][j]=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=n;++j){
			dp[i+1][j]=max(dp[i+1][j],dp[i][j]+(bool)(a[i]+j==i));
			dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]);
		}
	}
	for(int j=0;j<=n;++j){
		if(dp[n+1][j]>=k){
			cout<<j<<'\n';
			return;
		}
	}
	cout<<"-1\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;T=1;
	cin>>T;
	for(;T--;)solve();
}
```

---

## 作者：KSToki (赞：2)

题外话：果然是老年人手速，差一分钟 A 这题。
# 题目大意
给定一个长度为 $n$ 的数组 $a$，删除最少的数字，使得 $a_i=i$ 的数量至少为 $k$，若不能做到输出 $-1$。
# 题目分析
首先套路地令 $b[i]=a[i]-i$，若 $b[i]=0$ 表示其已归位，如果是个正数则其表示前面需要删多少个数才能让 $i$ 归位，如果 $b[i]$ 是个负数，显然这玩意没戏了。那么每次删除操作转化为了将其后所有的 $b[i]$ 减一。

求最小值的话这题二分没法判断，考虑 dp。这里 $n\le2000$，暗示使用 $O(n^2)$ 的做法，那么就可以设 $f[i][j]$ 为前 $i$ 个里删除 $j$ 个侯 $a_i=i$ 的数量最多是多少，转移就只有第 $i$ 个删或不删。若用 $c[i][j]$ 表示 $i$ 到 $n$ 中 $b[i]=j$ 的数量，那么可以得到状态转移方程为：
$$f[i][j]=max(f[i-1][j],f[i-1][j-1]-c[i][j-1]+c[i+1][j])$$
注意 $i$ 被删了，后一个应为 $i+1$。$c$ 显然可以通过后缀和 $O(n^2)$ 求出，那么总体复杂度为 $O(n^2)$。最后的答案扫一遍 $f[n]$，找到最小的 $i$ 使 $f[n][i]\geq k$ 即可。注意一下边界问题，主要是会用到 $0$。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,k,a[2001],b[2001],c[2001][2001],cnt,f[2001][2001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		k=read();
		for(R int i=0;i<=n;++i)
			for(R int j=0;j<=n;++j)
				c[i][j]=0;
		cnt=0;
		for(R int i=1;i<=n;++i)
		{
			a[i]=read();
			b[i]=i-a[i];
			if(b[i]>=0)
				++c[i][b[i]];
			if(b[i]==0)
				++cnt;
		}
		for(R int i=n-1;i;--i)
			for(R int j=0;j<=n;++j)
				c[i][j]+=c[i+1][j];
		for(R int i=0;i<=n;++i)
			f[i][0]=cnt;
		for(R int i=1;i<=n;++i)
			for(R int j=1;j<=i;++j)
				f[i][j]=max(f[i-1][j],f[i-1][j-1]-c[i][j-1]+(i<n?c[i+1][j]:0));
		for(R int i=0;i<=n;++i)
			if(f[n][i]>=k)
			{
				putint(i);
				goto over;
			}
		puts("-1");
		over:;
	}
	return 0;
}

```

---

## 作者：Mine_King (赞：1)

## Problem

[CF1551E Fixed Points](https://www.luogu.com.cn/problem/CF1551E)

**题目大意：**

给定一个长度为 $n$ 的序列 $a$，每次操作可以删除其中的一个数，并把其右侧的元素向左移动一位。问至少需要几次操作可以使得操作结束后的序列中有至少 $k$ 个位置 $i$ 满足 $a_i=i$。若无法满足要求，输出 `-1`。

## Solution

首先看起来就像 DP QwQ。然后，如果直接按照题意搞可能会比较麻烦，我们考虑换一个思维，设 $dp_{i,j}$ 表示前 $i$ 个数，删除 $j$ 个之后能匹配的最多位数。可以容易地得出状态转移方程：

$$dp_{i,j}=\max(dp_{i-1,j}+[a_i=i-j],dp_{i-1,j-1})$$

稍微解释下。$dp_{i-1,j}+[a_i=i-j]$ 表示不删第 $i$ 个数，那么前 $i-1$ 个中就已经删了 $j$ 个。$dp_{i-1,j-1}$ 表示删第 $i$ 个数，那么本来只删了 $j-1$ 个。  
另外若 $j=0$，那么此时第 $i$ 位肯定不会被删除，所以 $dp_{i,0}=dp_{i-1,0}+[a_i=i]$。  
那最后统计答案呢？我们只要在最后扫一遍，找到满足 $dp_{n,i} \ge k$ 的最小的 $i$ 即为答案。若找不到说明无解，输出 `-1` 即可。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int T,n,m,a[2005],dp[2005][2005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) dp[i][j]=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
		{
			dp[i][0]=dp[i-1][0]+(a[i]==i);
			for(int j=1;j<=i;j++)
				dp[i][j]=max(dp[i-1][j-1],dp[i-1][j]+(a[i]==i-j));
		}
		for(int i=0;i<=n;i++)
			if(dp[n][i]>=m){printf("%d\n",i);goto end;}
		puts("-1");
		end:;
	}
	return 0;
}
```

---

## 作者：Daniel_7216 (赞：0)

其实这道题就是 P1799 稍作变化，但本质上是相通的。第三、四段都是从以前的我写的题解里复制的（逃）……

题目大意：给你一个序列，要求你删除尽量少的数，使得在有至少 $k$ 个数满足 $A_i=i$。

转化一下题意，要使删除次数最少，那就要让删除后满足条件的数尽量多。所以就有一些思路了，先求出删除 $0$ 个数、$1$ 个数……一直到 $n$ 个数时最多可以有几个数在自己位置上，找到最小的删除次数使答案大于等于 $k$。我们考虑用 DP 求解。

用 $dp_{i,j}$ 表示前 $i$ 个数里删除正好 $j$ 个数最多有多少个数在自己位置上，为什么这么定义？因为我们就可以轻松推出当 $A_i = i - j$ 时它在自己位置上。

当 $j$ 为 $0$ 时直接继承 $dp_{i - 1,j}$，如果 $A_i$ 在自己的位置上就加一。当 $j$ 不为 $0$ 时同理，但是还可以选择不删除这个数，也就是在 $dp_{i-1,j-1}$ 和 $dp_{i - 1,j}+[A_i=i-j]$ 中选择最大值。

代码安排上：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring> 
using namespace std;
int n, k, T, i;
int a[2001], dp[2001][2001];
int main(){
	scanf("%d", &T);
	for (int x = 0; x < T; x++){
		memset(dp, 0, sizeof(dp));
		scanf("%d%d", &n, &k);
		for (i = 1; i <= n; i++){
			scanf("%d", &a[i]);
		}
		for (i = 1; i <= n; i++){
			for (int j = 0; j <= i; j++){
				if (j == 0){
				  	dp[i][j] = max(dp[i][j], dp[i - 1][j] + (a[i] == i - j));
				}else{
					dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j] + (a[i] == i - j));
				}
			}
		}
		for (i = 0; i <= n + 1; i++){
			if (dp[n][i] >= k){
				break;
			}
		}
		printf("%d\n", i <= n?i:-1);
	}
	return 0;
}
```

---

## 作者：little_sheep917 (赞：0)



> 一个整数序列 $a1,a2,...,a_n$ ，一次操作，可以删除一个数，然后该数右侧的数向左移动一个单位。对于一个长度为 $n$ 的整数序列 $b_i$ ，求最少需要删除几个数后，会有至少 $k$ 个 $i$ 满足 $b_i=i$ 。
>
> $1\leq t\leq 100$
>
> $1\leq k\leq n\leq 2000,\ 1\leq a_i\leq n,\ \sum n\leq 2000$

看到 $2\cdot 10^3$ 的范围，就想到应该是 $\mathrm O(n^2)$ 的做法 . 

考虑这样一个 $dp$ ，

$f(i,j)$ 代表到了第 $i$ 个数，一共删除了 $j$ 个数最多有多少个 $i$ 满足 $b_i=i$ .

转移方程为 :

1. 删掉当前这个数

   $f(i,j)\rightarrow f(i+1,j+1)$

2. 保留当前这个数

   - 如果 $a_{i+1}=i+1-j$ ，$f(i,j)+1\rightarrow f(i+1,j)$

     即 $a_{i+1}$ 对应着 $b_{i+1-j}$ . 

   - 否则， $f(i,j)\rightarrow f(i+1,j)$

最后从小到大枚举 $f(n-1,i)$ ，找到第一个 $f(n-1,i)\geq k$ 的 $i$ 即为答案 .

时间复杂度 : $\mathrm O(n^2)$

空间复杂度 : $\mathrm O(n^2)$

code

```c++
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k;
int a[2010];
int dp[2010][2010];
inline void upd(int &x,int y){
	x=max(x,y);
}
void solve(){
	cin>>n>>k;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n;i++)a[i]--;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			dp[i][j]=0;
		}
	}
	dp[0][0]=(a[0]==0);
	dp[0][1]=0;
	for(int i=0;i+1<n;i++){
		for(int j=0;j<=i+1;j++){
			upd(dp[i+1][j],dp[i][j]+(a[i+1]==i+1-j));
			upd(dp[i+1][j+1],dp[i][j]);
		}
	}
	int ans=-1;
	for(int i=0;i<=n;i++){
		if(dp[n-1][i]>=k){
			ans=i;
			break;
		}
	}
	cout<<ans<<endl;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
/*inline? ll or int? size? min max?*/
```

---

