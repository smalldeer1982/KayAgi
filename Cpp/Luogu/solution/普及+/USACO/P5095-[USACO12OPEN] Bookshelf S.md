# [USACO12OPEN] Bookshelf S

## 题目描述

Farmer John 闲来无事的时候总喜欢坐下来看书。这些年来，他一共收集了 $N$ 本书（$1 \leq N \leq 2000$），他打算搭一个新的书架来装这些书。

每本书都有个宽度 $w_i$ 和高度 $h_i$，书必须按顺序来摆放（即同一层书架摆的书必须是连续的一个区间）。每层书架的总宽度不能超过 $L$（$1 \leq L \leq 10^9$），每层书架的高度等于这一层最高的书的高度，整个书架的高度等于每层书架的高度之和。

现在请你帮 FJ 求出书架高度的最小值。

## 说明/提示

第一层放第一本书，第二层放第二，三，四本书，第三层放第五本书，总高度为 $5+13+3=21$，可以证明不存在更优的方案。

## 样例 #1

### 输入

```
5 10
5 7
9 2
8 5
13 2
3 8```

### 输出

```
21```

# 题解

## 作者：_xbn (赞：17)

很显然此题要用动态规划，我们设 $f(i)$ 表示当前到第 $i$ 本书， 书架的最小高度。

接下来考虑转移，转移我们可以分两种情况讨论，第一，对于当前这本书，我们要新开一个书架，那么 $f(i) = f(i-1) + h(i)$，第二，我们选择把当前这本书插入之前的书架，那么我们就要知道前面书的最大高度，我们可以开一重循环寻找之前的最大高度，用它来更新当前状态 $f(i) = min(f(i),f(j-1) + maxn)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2002;
int n, m, p, k, ans, sum, tot, cnt, a[N], b[N], f[N], c[N], l;
int main()
{
	std::cin>> n >> l;
	for(int i = 1; i <= n; i++)
	{
		std::cin >> a[i] >> b[i];
		c[i] = c[i - 1] + b[i];
		f[i] = 1e9;
	}
	for(int i = 1; i <= n; i++)
	{
		f[i] = f[i - 1] + a[i];
		tot = a[i];
		for(int j = i - 1; j >= 1; j--)
		{
			if(c[i] - c[j - 1] > l)break;
			tot = max(tot, a[j]);
			f[i] = min(f[i], f[j - 1] + tot);
		}
	}
	cout << f[n];
	return 0;
}
```


---

## 作者：zhy137036 (赞：8)

这是一道 dp 题，~~别问我怎么想到的~~。

## 题意简述

- 有 $n$ 本书，第 $i$ 本书宽 $w_i$，高 $h_i$。
- 书排成一列，你需要把它分成几个区间，每个区间所有书的宽度之和不超过 $L$。
- 书架的高度为每个区间最高的书的高度之和。
- 求书架最小高度。

## 状态定义

将一列书分成几个区间，看起来像线性动态规划。

但是看数据范围，像是 $O(n^2)$ 的。可能转移还要 $O(n)$？

定义 $f_i$ 表示前 $i$ 本书放到书架上，书架的最低高度。

## 状态转移式

转移式就是问 $f_i$ 怎么算。

设倒数第二个区间的最后一本书是第 $j$ 本。  

那么 $\large f_i=f_j+\max\limits_{k=j+1}^ih_k$。

另外有个限定条件：$\large\sum\limits_{k=j+1}^iw_k\le L$。

于是可以枚举 $j$，算出结果。

## 优化

不过这样转移的复杂度就达到了 $O(n^2)$，怎么办？

不难发现 $j$ 越大越有可能满足限定条件，所以可以考虑从大到小枚举 $j$，不满足条件直接退出。

然而复杂度并没有改变。

实际上，可以在 $j$ 从大到小枚举的过程中维护 $\max\limits_{k=j+1}^ih_k$ 和 $\sum\limits_{k=j+1}^iw_k$，转移复杂度降到 $O(n)$。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,l,w[2010],h[2010],f[2010];
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++)
		cin>>h[i]>>w[i];
	for(int i=1;i<=n;i++){
		int mx=h[i],sum=w[i];//mx维护区间高度，sum维护区间宽度之和
		f[i]=f[i-1]+h[i];//先假设j=i-1，这是一定能满足限定条件的
		for(int j=i-2;j>=0;j--){
			sum+=w[j+1];//更新sum
			if(sum>l)break;//如果放不下了，退出
			mx=max(mx,h[j+1]);//更新mx
			f[i]=min(f[i],f[j]+mx);//转移
		}
	}
	cout<<f[n]<<endl;
	return 0;
}
```

---

## 作者：JK_LOVER (赞：6)

## 题意
给你一个长度为 $n$ 的序列。将其划分为多段。其中每一段要求 $\sum_{i=L}^R w[i] \le L$ ，$ans = \sum \max(h[j]) \ (L\le j\le R)$ 。 求出一个划分使 $ans$ 最小。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p5095)
## 分析
对于这样的最优性问题，一般考虑动态规划。先定义状态 $f[i]$ 的意义是以 $i$ 作为结尾，最小的高度。那么可以如下转移。
$$
f[i] = \min(f[i],f[j]+\max(h[k])) (j+1\le k \le \ \&\&\  \sum_{k=j+1}^i w[k]\le L)
$$
这样我们就可以得到第一份代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 2e3+100;
int n,L;
struct Book{
	int w,h;
}s[N];
int f[N],sum[N];
int main()
{
	n = read();L = read();
	for(int i = 1;i <= n;i++)
	{
		s[i].h = read();
		s[i].w = read();
		sum[i] = sum[i-1]+s[i].w;
	}
	memset(f,0x3f,sizeof(f));
	f[0] = 0;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 0;j <= i-1;j++)
		{
			int Sum = 0;
			for(int k = j+1;k <= i;k++) Sum += s[k].w;
			if(Sum <= L)
			{
				int mx = 0;
				for(int k = j+1;k <= i;k++)
				mx = max(mx,s[k].h);
				f[i] = min(f[i],f[j] + mx);	
			}
		}
	}
	cout<<f[n]<<endl;
	return 0;
}
```

不出意外 $60$ 分，超时了，这是一份 $O(n^3)$ 的代码。考虑如何优化。我们发现对于 $\sum w[i]$ 我们可以用前缀和维护。那么优化之后。就是这样：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 2e3+100;
int n,L;
struct Book{
	int w,h;
}s[N];
int f[N],sum[N];
int main()
{
	n = read();L = read();
	for(int i = 1;i <= n;i++)
	{
		s[i].h = read();
		s[i].w = read();
		sum[i] = sum[i-1]+s[i].w;
	}
	memset(f,0x3f,sizeof(f));
	f[0] = 0;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 0;j <= i-1;j++)
		{
			if(sum[i] - sum[j] <= L)
			{
				int mx = 0;
				for(int k = j+1;k <= i;k++)
				mx = max(mx,s[k].h);
				f[i] = min(f[i],f[j] + mx);	
			}
		}
	}
	cout<<f[n]<<endl;
	return 0;
}
```

 $70$ 分，但是我们可以发现这只是优化了一个循环，整个复杂度没有降低。我们是求 $\max(h[i])$ ，这是一个区间最值问题，考虑 $ST$ 表维护。那么复杂度可以降低为 $O(n^2)$ 。
## 代码

 ```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 2e3+100;
int n,L;
struct Book{
	int w,h;
}s[N];
int f[N],sum[N],st[21][N];
int ask(int l,int r)
{
	int k = log2(r-l+1);
	return max(st[k][l],st[k][r-(1<<k)+1]);
}
int main()
{
	n = read();L = read();
	for(int i = 1;i <= n;i++)
	{
		s[i].h = read();
		s[i].w = read();
		sum[i] = sum[i-1]+s[i].w;
		st[0][i] = s[i].h;
	}
	for(int j = 1;j <= 20;j++)
	{
		for(int i = 1;i + (1<<j) <= n + 1;i++)
		{
			st[j][i] = max(st[j-1][i],st[j-1][i+(1<<j-1)]);
		}
	}
	memset(f,0x3f,sizeof(f));
	f[0] = 0;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 0;j <= i-1;j++)
		{
			if(sum[i] - sum[j] <= L)
			{
				int mx = 0;
				mx = ask(j+1,i);
				f[i] = min(f[i],f[j] + mx);	
			}
		}
	}
	cout<<f[n]<<endl;
	return 0;
}
```


---

## 作者：Zhou_Wingay (赞：3)

### 思路：十分明显，这题用DP。

设：$f[i]$ 表示放前 $i$ 本书的最小高度，$j$ 表示最后一层第一本书的编号，$sum$ 表示当前这一层的宽度。

对于每一本书，我们应先考虑将它放置上一层的最后一个，即：
```cpp
f[i]=f[i-1]+a[i][0];
```
之后我们再枚举 $j$，考虑到时间复杂度，我们应反着循环，如果当前这一层已经装不下了，那在循环也没有意义，直接退出，即：
```cpp
for(j=i-1;j>=1;j--){
	sum+=a[j][1];
	if(sum>l){break;}
}
```
最后是转移方程 : $f[i]=f[j-1]+maxn$。（注：$j-1$ 表示上一层最后一个，$maxn$ 表示这一层最高的）

贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l;
int a[2005][2],f[2005];
int main(){
	int i,j;
	cin>>n>>l;
	for(i=1;i<=n;i++){cin>>a[i][0]>>a[i][1];}
	for(i=1;i<=n;i++){
		int maxn=a[i][0],sum=a[i][1];
		f[i]=f[i-1]+a[i][0];
		for(j=i-1;j>=1;j--){
			sum+=a[j][1];
			if(sum>l){break;}
			maxn=max(maxn,a[j][0]);
			f[i]=min(f[i],f[j-1]+maxn);
		}
	}
	cout<<f[n];
	return 0;
}
```


---

## 作者：Justinalx (赞：1)

# **1.前言**
这是道动态规划，应该都看得出来，~~虽然我看了半天才看明白题目~~，但我依旧顽强的做了出来（~~错了很多遍~~）。
# **2.题目意思及思路**
题意：给你两个数，以及书的高度和宽度。问你在每排宽度不超过指定宽度的情况下，书架高度最小为多少，每层高度为这一层最高书的宽度。

思路：我们设当前书本为 $i$，则 $f(i)$ 为到第 $i$ 本书时，书架的最小高度。我们用动态规划的思想。有两种情况。一：把当前这本书插入之前的书架。二：另开一层书架，把当前这本书放新开的书架。
     
动态转移方程为 $f(i)=min(f(i),f(j-1)+maxn)$。

**注意我们可以用前缀来加快速度，如下图。**
```cpp
        for (i=1; i<=n; i++)
	scanf("%d%d",&a[i],&b[i]),b[i]+=b[i-1];
```
**注意刚开始要赋初值，但最开始的那个位置要赋0。**
```cpp
	memset(f,63,sizeof(f));
	f[0]=0;
```
# **3.程序（仅供参考）**
只展示最重要的部分
```cpp
    for (j=i; j>=1; j--) {        //从当前这本书往前判断。
	if(b[i]-b[j-1]>m) break; //当宽度大于指定宽度时，退出。
 	ans=max(ans,a[j]);
        f[i]=min(f[i],f[j-1]+ans);
    }
```



---

## 作者：Dr_Gilbert (赞：1)

# P5095 [USACO12OPEN]Bookshelf S

题目大意：[传送门](https://www.luogu.com.cn/problem/P5095)

可以发现，本题是一道动态规划的题目。只用贪心无法考虑比较复杂的情况，也比较容易构造反例，就不再详细说明。

### Algorithm 1:

根据题意可以设 $dp[i][j]$ 表示处理完前 $i$ 本书，书架共有 $j$ 层时的最小总高度，由题意，得状态转移方程（$k$ 表示除了自己以外，再选择前面的 $k$ 本书共同组成一层）
$$
dp[i][j]=\min(dp[i-k-1][j-1]+\max(h[i-k-1]...h[i]))
$$
其中，维护最大值可以使用 ST 表，但最坏时间复杂度为 $O(n^3)$，超时。

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[2010][2010];
int st[2010][15];
int w[2010],h[2010],s[2010];
int log_2(int x){
    int cnt=0;
    while (x>1){
        x>>=1;
        cnt++;
    }
    return cnt;
}
int query(int l ,int r){
	int k=log_2(r-l);
	int ans=max(st[l][k],st[r-(1<<k)+1][k]);
	return ans;
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);cout.tie(nullptr);
	int n,l;
	cin>>n>>l;
	for (int i=1;i<=n;i++){
		cin>>h[i]>>w[i];
		st[i][0]=h[i];
		s[i]=s[i-1]+w[i];
	}
	for (int k=1;k<=13;k++){
		for (int i=1;i+(1<<k-1)<=n;i++){
			st[i][k]=max(st[i][k-1],st[i+(1<<k-1)][k-1]);
		}
	}
	memset(dp,0x7f,sizeof(dp));
	dp[0][0]=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=i;j++){
			for (int k=0;i-k>=1;k++){//可以单独成一层，从0开始
				if (s[i]-s[i-k-1]>l) break;
				dp[i][j]=min(dp[i][j],dp[i-k-1][j-1]+query(i-k,i));
			}
		}
	}
	int ans=0x7fffffff;
	for (int i=1;i<=n;i++) ans=min(ans,dp[n][i]);
	cout<<ans;
	return 0;
}
```

### Algorithm 2:

二维 DP 明显超时，考虑进行优化。一般可以考虑找到无用的状态并进行压缩，从而节省时间和空间。有些题解并没有详细说明为什么能二维改一维，说明一下。

结合求出最终答案的过程，发现最终答案只是可行的各状态（层数）中答案的最小值，也就是说，保存每个状态对答案可能并没有太大的作用。于是大胆地砍掉第二维，则有 $dp[i]$ 表示处理完第 $i$ 本书，分若干层，书架高度的最小值。修改后的状态转移方程并没有太大变化，为
$$
dp[i]=\min(dp[i-k-1]+\max(h[i-k-1]...h[i]))
$$
事实上，不难发现对于一个确定的子序列 $[l,r]$，让它们新成一层对答案的改变量也是确定的，所以转移的过程中，转移后的答案和一共用了几层并没有关系。砍掉 DP 的第二维后，转移的过程中只针对最优解转移，同时可以保证转移不出错，时间复杂度优化为 $O(n^2)$，可以获得 $100$ 分。代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[2010];
int st[2010][30];//事实上，由于本题转移的过程，ST表是负优化
int w[2010],h[2010],s[2010];
int log_2(int x){
    int cnt=0;
    while (x>1){
        x>>=1;
        cnt++;
    }
    return cnt;
}
int query(int l ,int r){
	int k=log_2(r-l);
	int ans=max(st[l][k],st[r-(1<<k)+1][k]);
	return ans;
} 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);cout.tie(nullptr);
	int n,l;
	cin>>n>>l;
	for (int i=1;i<=n;i++){
		cin>>h[i]>>w[i];
		st[i][0]=h[i];
		s[i]=s[i-1]+w[i];
	}
	for (int k=1;k<=20;k++){
		for (int i=1;i+(1<<k-1)<=n;i++){
            //在转移时枚举每个k时更新区间最大值即可，无需ST表
			st[i][k]=max(st[i][k-1],st[i+(1<<k-1)][k-1]);
		}
	}
	memset(dp,0x7f,sizeof(dp));//初值:其它为INF
	dp[0]=0;//初值:dp[0]=0
	for (int i=1;i<=n;i++){
		for (int k=0;i-k>=1;k++){
			if (s[i]-s[i-k-1]>l) break;
            //可以就在这里更新区间最大值
			dp[i]=min(dp[i],dp[i-k-1]+query(i-k,i));
		}
	}
	cout<<dp[n];
	return 0;
}
```



---

## 作者：haotian1234 (赞：1)

这是一道动规嘛
## 题意暗示
- 将所有书分成 $n$ 个区间，找到每个区间中高度最大的书，记为 $ma$ ，将所有 $n$ 个区间中的 $ma$ 相加，即为答案
## 题目分析
1. 分出的区间一定要尽可能的少，这样可以使 $ma$ 的数量减少，从而使答案更小，那么，这个区间内的总宽度就要尽可能的接近宽度上限 $L$ 。
1. 用 $f_i$ 记录放到第 $i$ 本书时，书架高度的最小值。用循环 $j$ 来枚举区间的头，$i$ 就是区间的尾，所以 $f_i$ 的值应该为  $f_i=\min(f_i,f_j-1+ma)$ 。
## 题目坑点
- 既然取最小值，那么 $f$ 数组肯定要初始化赋最大喽，而且 $f_0$ 还要赋成最小值0
- 可以用前缀和优化一下，记录在 $sum$ 数组里，防止超时。
- 不要忘了区间最大值初始化！

下面就上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,a[100100],b[100100],sum[100100],f[100100],ma,j;
int main(){
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]),sum[i]=sum[i-1]+b[i];//前缀和优化
	memset(f,63,sizeof(f));//初始化
	f[0]=0;//赋成最小值0
	for (i=1;i<=n;i++){
		ma=0;//区间最大值初始化
		for (j=i;j>=1;j--){
			if (sum[i]-sum[j-1]>m) break;//判断总宽度是否超过 L
			ma=max(ma,a[j]);
			f[i]=min(f[i],f[j-1]+ma);//取最小值
		}
	}
	printf("%d\n",f[n]);
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15244924.html)

## 题目大意

有 $N$ 本书，第 $i$ 本书宽 $w_i$，高 $h_i$。

我们需要将这些这些书分成几个区间，每个区间所有书的宽度之和不超过 $L$。

书架的高度为每个区间最高的书的高度之和，求书架最小高度。

## 题目分析

**我们令 $dp[i]$ 表示到第 $i$ 本书为止，书架的最小高度。**

对于每一个状态 $dp[i]$，都可能由两种方法转移而来：

1. 再开一个书架。此时有 

$$dp[i]=dp[i-1]+h[i]$$

$h[i]$ 表示每一本书的高度。

2. 插入之前的书架，那么当然需要知道前面数的最大高度，$O(N)$ 查找即可。有 

$$dp[i] = \min\{dp[i],dp[j-1]+\operatorname{maxsum}\}$$

$\operatorname{maxsum}$ 表示最大高度。


## 代码

```cpp
//2021/9/6

//2021/9/8

#include <iostream>

#include <cstdio>

#include <algorithm>

#define debug(c) cerr<<#c<<" = "<<c<<endl

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=100005;

int h[ma],w[ma],sum[ma],dp[ma];

int n,m;

int main(void)
{
	n=read(),m=read();
	
	for(register int i=1;i<=n;i++)
	{
		h[i]=read(),w[i]=read();
		
		sum[i]=sum[i-1]+w[i];
		
		dp[i]=(1<<29);	
	}
	
	for(register int i=1;i<=n;i++)
	{
		dp[i]=dp[i-1]+h[i];
		
		int tmp=h[i];
		
		for(register int j=i-1;j>=1 && sum[i]-sum[j-1]<=m;j--)
		{
			tmp=max(tmp,h[j]);
			
			dp[i]=min(dp[i],dp[j-1]+tmp);
		}
	}
	
	print(dp[n]);
	
	return 0;
}
```

---

## 作者：Xdl_rp (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P5095)

- 动态规划，用 $dp_i$ 表示将前 $i$ 本书放进书架，需要的书架的最小高度。
- 状态转移方程：$dp_i = min(dp[j-1] + max(h[j], h[j+1], ..., h[i]),dp_i)$ 且 $j<=i$ 且 $w_j + w_{j+1} + ... + w_i \le L$。（枚举 $j \le i$，将第 $j$ 本书到第 $i$ 本书放在同一层书架，其中 $w_j + w_{j+1} + ... + w_i$ 可以用前缀和）
- 时间复杂度 $O(n^2)$。

代码：
------------

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
struct book{
	int h, w;
}a[N];//结构体
int dp[N], sum[N];//dp数组和前缀和sum数组
int main() {
	int n, l;
	scanf("%d %d", &n, &l);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].h, &a[i].w);
		sum[i] = sum[i - 1] + a[i].w;//前缀和经典公式
	}
	memset(dp, 0x3f, sizeof(dp));//赋值成极大值
	dp[0] = 0;//但是dp[0]要赋值为0
	for (int i = 1; i <= n; i++) {
		int minn = a[i].h;//从第一个开始取最小值
		dp[i] = dp[i - 1] + a[i].h;//提前赋值
		for (int j = i - 1; j >= 1; j--) {
			if (sum[i] - sum[j - 1] > l) break;
			minn = max(minn, a[j].h);
			dp[i] = min(dp[j - 1] + minn, dp[i]);//状态转移方程
		}
	}
	printf("%d\n", dp[n]);//输出
	return 0;
}
```


---

