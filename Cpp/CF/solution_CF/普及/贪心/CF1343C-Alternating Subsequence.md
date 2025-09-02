# Alternating Subsequence

## 题目描述

Recall that the sequence $ b $ is a a subsequence of the sequence $ a $ if $ b $ can be derived from $ a $ by removing zero or more elements without changing the order of the remaining elements. For example, if $ a=[1, 2, 1, 3, 1, 2, 1] $ , then possible subsequences are: $ [1, 1, 1, 1] $ , $ [3] $ and $ [1, 2, 1, 3, 1, 2, 1] $ , but not $ [3, 2, 3] $ and $ [1, 1,       1, 1, 2] $ .

You are given a sequence $ a $ consisting of $ n $ positive and negative elements (there is no zeros in the sequence).

Your task is to choose maximum by size (length) alternating subsequence of the given sequence (i.e. the sign of each next element is the opposite from the sign of the current element, like positive-negative-positive and so on or negative-positive-negative and so on). Among all such subsequences, you have to choose one which has the maximum sum of elements.

In other words, if the maximum length of alternating subsequence is $ k $ then your task is to find the maximum sum of elements of some alternating subsequence of length $ k $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, one of the possible answers is $ [1, 2, \underline{3}, \underline{-1}, -2] $ .

In the second test case of the example, one of the possible answers is $ [-1, -2, \underline{-1}, -3] $ .

In the third test case of the example, one of the possible answers is $ [\underline{-2}, 8, 3, \underline{8},       \underline{-4}, -15, \underline{5}, \underline{-2}, -3, \underline{1}] $ .

In the fourth test case of the example, one of the possible answers is $ [\underline{1}, \underline{-1000000000},       \underline{1}, \underline{-1000000000}, \underline{1}, \underline{-1000000000}] $ .

## 样例 #1

### 输入

```
4
5
1 2 3 -1 -2
4
-1 -2 -1 -3
10
-2 8 3 8 -4 -15 5 -2 -3 1
6
1 -1000000000 1 -1000000000 1 -1000000000```

### 输出

```
2
-1
6
-2999999997```

# 题解

## 作者：luminary3 (赞：6)

## DP算法
### 1.题目大意
就是 $T$ 组数据，每个数据一个 $n$ 和一个数组找出相邻两项异号并且长度最大、各项之和最大的子序列。
### 2.思路
看到这个题，首先可以想到[$B3637$ 最长上升子序列](https://www.luogu.com.cn/problem/B3637)这个题，只需要改一下中间 $dp[]$ 的转移方程，并把取最大改为求和，当然 $dp[i]$ 的意义也有改变。

$dp[i]$ 表示第 $i$ 个数应取的数。

转移方程：

($pos$ 表示 $dp$ 取到第几个数了)

如果$dp[pos]$ 和 $a[i]$ 是同号，则比较 $dp[pos]$ 与 $a[i]$ 的大小，取大的值。

如果$dp[pos]$ 和 $a[i]$ 是异号，则 $pos+1$,$dp[pos]$ 等于 $a[i]$。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N],n,dp[N],maxi=-1e9,T;
int main()
{
	cin>>T;
	while(T--)//T组数据
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			dp[i]=a[i];
		}
		dp[1]=a[1];
		int pos=1;//dp[]去到第几个数了
		for(int i=2;i<=n;i++)
		{
			if((a[i-1]<0&&a[i]<0)||(a[i-1]>0&&a[i]>0))//转移
				dp[pos]=max(dp[pos],a[i]);
			else
				dp[++pos]=a[i];
		}
		long long sum=0;//切记开long long
		for(int i=1;i<=pos;i++)
			sum+=dp[i];//求和
		cout<<sum<<"\n";
	}
	return 0;
}
```



---

## 作者：PanH (赞：5)

### 奇怪的DP题解增加了！
emmm......

看了很多大佬的贪心，自愧不如，我只好讲讲考场上写的~~又臭又长~~的DP。

记 $f[i][1/0]$ 为前 $i$ 位的最长序列长度,末尾一位为正数/负数，$g[i][1/0]$ 为前 $i$ 位最长序列的最大和,末尾为正数/负数。

$$f[i][1]=\max(f[i-1][0]+1,f[i-1][1]),f[i][0]=f[i-1][0](a[i]>0)$$
$$f[i][0]=\max(f[i-1][1]+1,f[i-1][0]),f[i][1]=f[i-1][1](a[i]<0)$$

应该很好理解，不懂可以看代码。在转移 $f$ 数组时顺带着转移一下 $g$ 数组就可以了，具体看代码。

code：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<class T> inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
int a[200005],f[200005][2],g[200005][2],n;
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n);
		for(int i=1;i<=n;i++)	f[i][0]=f[i][1]=0;
		for(int i=1;i<=n;i++)	read(a[i]);
		for(int i=1;i<=n;i++)
		{
			if(a[i]>0)	
			{
				if(f[i-1][1]>f[i-1][0]+1)
					f[i][1]=f[i-1][1],g[i][1]=g[i-1][1];
				else if(f[i-1][1]==f[i-1][0]+1)
					f[i][1]=f[i-1][1],g[i][1]=max(g[i-1][1],g[i-1][0]+a[i]);
				else
					f[i][1]=f[i-1][0]+1,g[i][1]=g[i-1][0]+a[i];
				f[i][0]=f[i-1][0],g[i][0]=g[i-1][0];
			}
			else
			{
				if(f[i-1][0]>f[i-1][1]+1)
					f[i][0]=f[i-1][0],g[i][0]=g[i-1][0];
				else if(f[i-1][0]==f[i-1][1]+1)
					f[i][0]=f[i-1][0],g[i][0]=max(g[i-1][0],g[i-1][1]+a[i]);
				else
					f[i][0]=f[i-1][1]+1,g[i][0]=g[i-1][1]+a[i];
				f[i][1]=f[i-1][1],g[i][1]=g[i-1][1];
			}
		}
		if(f[n][0]>f[n][1])	printf("%lld\n",g[n][0]);
		else if(f[n][0]==f[n][1])	printf("%lld\n",max(g[n][0],g[n][1]));
		else	printf("%lld\n",g[n][1]);
	}
}
```


---

## 作者：PersistentLife (赞：4)


题目中要选择的子序列可以理解为这样。

1. 在每两个异号的数中间插一个隔板。

2. 在被隔板分成的每一段中选一个数（默认 $a_0$ 和 $a_1$ 之间有一个隔板，$a_n$ 和 $a_{n+1}$ 之间有一个隔板，即使 $a_0$ 和 $a_n$ 不存在）。 

3. 要求这个子序列的和最大。

举个例子，原序列 $a$ 为 $[-2,3,1,-4,5,10,-3,-4,1,-4]$。

那么插隔板之后就是这样 $[-2$ $|$ $3,1$ $|$ $-4$ $|$ $5,10$ $|$ $-3,-4$ $|$ $1$ $|$ $-4]$，其中 $|$ 为隔板。

我们要使子序列和最大，那么每一段中就要选最大的数，如 $[\texttt{-2}$ $|$ $\texttt{3},1$ $|$ $\texttt{-4}$ $|$ $5,\texttt{10}$ $|$ $\texttt{-3},-4$ $|$ $\texttt{1}$ $|$ $\texttt{-4}]$，其中打印机字体 （`\texttt{number}`） 为最大值。

我们对于每一个 $t$ 去 $\Theta(n)$ 贪心扫一遍输出，复杂度为 $\Theta(nt)$，虽然看似承受不了，但是我们的常数很小，是可以过的。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int a[n+1];
		int maxx=0;
		long long ans=0;
		bool f=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(a[1]<0) f=1;
		maxx=a[1];
		for(int i=2;i<=n;i++)
		{
			if(a[i]>0&&f)
			{
				f=0;
				ans+=maxx;
				maxx=a[i];
			}
			else if(a[i]<0&&!f)
			{
				f=1;
				ans+=maxx;
				maxx=a[i];
			}
			else maxx=max(maxx,a[i]);
		}
		ans+=maxx;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：sycqwq (赞：2)

咋都是一些我看不懂的题解啊

发一篇不是dp的（或许？）

思路：

既然要长度最大，那么我们在每一个连续符号相同子序列的数中都要选出一个

又要和最大，那么就每一次挑选时都挑选每个连续符号相同中最大的数，就能A了这题

代码:

```cpp
#include<bits/stdc++.h>
#define inf 2147283647
#define int long long
using namespace std;
signed main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,a[200005],t=1;//t判断是不是正负
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        if(a[1]<0)//判断第一个数是正是负
            t=0;
            int ma=a[1];//最大值
        int s=0;
        for(int j=1;j<=n;j++)
        {
            int tp=a[j]>=0?1:0;//判断此数的正负
            if(tp==t)//和上一个一样就代表在一个连续同符号子序列里
            {
                ma=max(ma,a[j]);//记录最大值
            }
            else//符号变了，要加上了
            {
                t=t==0?1:0;//重置t
                s+=ma;//加上最大值
                ma=a[j];//重置max
            }
            
        }
        cout<<s+ma<<endl;//最后一个要加上
    }
    return 0;
}
```

---

## 作者：qinshi0308 (赞：1)

## 一、思路
老规矩，上来先讲讲思路。

首先，看看题，有没有感觉到有一种很熟悉的感觉？

没错，我看到题，马上就想到了**最长上升子序列**，并且，这道题使用的算法和最长上升子序列的算法一样：dp（又称为动态规划），[不知道的同学看这里！](http://oi-wiki.com/dp/basic/)

仔细读题后我们可以想到：首先，默认这个子序列 $b$ 的第 $1$ 项为原数列的第 $1$ 项，然后，从前往后依次便利原数列 $a$ ，**当 $a_i$ 与子序列的最后一项 $b_j$ 同号时**，因为题目要求输出最大的和，所以 $b_j=\max(a_i,b_j)$。**如果 $a_i$ 与子序列的最后一项不同号时**，将 $a_i$ 添加到 $b$ 的末尾。

重复以上操作，直到遍历完 $a$ 数组，再对 $b$ 进行求和，求出来的和即为问题的答案。

**注意：求和用的变量要开```long long```！不然会炸掉。**

## 二、代码
~~~cpp
# include <bits/stdc++.h>
using namespace std;
int arr[200010];//原数列，即为思路中的a数组
int dp[200010];//子序列，即为思路中的b数组
inline bool check(int x){//判断x的符号和函数，为正数返回1，为负数返回0
	if(x>0){
		return 1;
	}
	return 0;
}
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		int n;
		cin>>n;
		for(int j=0;j<n;j++){
			cin>>arr[j];
		}
		int len=1;
		dp[0]=arr[0];
		for(int j=1;j<n;j++){
			if(check(arr[j])==check(dp[len-1])){//判断两数是否同号
				dp[len-1]=max(dp[len-1],arr[j]);//同号，子序列的最后一项等于arr[i]和dp数组的最后一项中较大的一个。
			}else{
				dp[len++]=arr[j];//异号，将arr[i]添加到dp数组末尾
			}
		}
		long long ans=0;//记得开long long,不开会炸
		for(int j=0;j<len;j++){
			ans+=dp[j];
		}
		cout<<ans<<endl;
		fill(arr,arr+n,0);//多组数据记得清空数组
		fill(dp,dp+len,0);
	} 
	return 0;
}
~~~

---

## 作者：do_while_true (赞：1)

我们可以把这个序列根据正负性看做 $k$ 个正负不同的连续子序列，则我们想要选出序列长度最长，则这 $k$ 个序列一定都要选一个。如果我们想要选出和最大，只需要选择每一个序列的最大值就行了。

个人的实现方法比较麻烦，代码仅供参考。

###  [$\mathcal{Code}$](https://codeforces.ml/contest/1343/submission/77525487)

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：
给您一个序列，您要在其中选择若干个数使得：

- 相邻两数异号
- 长度最大，总和最大

我们可以牢牢抓住**长度且总和最大**，这一特性。  
说明我们必须在每一个连续的同号的子串中被迫选择最大的，以满足这一属性。 

例如，样例 $ 1,2,3,-1,2 $ 被我们分割成了 $ 1,2,3 $ 和 $ -1,-2 $ 两个子串，为满足最大从中选择 $ 3 $ 和 $ -1 $ 两个数。  

**本题涉及算法：贪心。** 

### Solution:    

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=2e5+50;
const int M=1e5+50;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll t,n;
ll a[N];

int main()
{
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;++i) a[i]=read();
		ll l=a[1]>0?1:-1,ans=0,maxn=a[1];
		for(int i=2;i<=n;++i){
			ll res=a[i]>0?1:-1;
			if(res==l) {
				maxn=max(maxn,a[i]);
			}else{
				ans+=maxn;
				maxn=a[i];
				l=res;
			}			
		}
		ans+=maxn;
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：CSP_Sept (赞：0)

思路差不多与其他题解相同，但实现方式不一样。

#### 前置定义

由于数列 $\{a_n\}$ 的最长正负交替序列的长度为 $k$，则把数列分为 $k$ 段，这 $k$ 段中的每一段里的数都是同号的，交替的两段是异号的。

#### 思路

我们只需要找到每一段里的最大值相加即可。

定义数组 $m_i$ 表示第 $i$ 段的最大值，定义函数 `N_f(a,b)` 用来判断 $a,b$ 是否异号，定义 $cnt$ 表示 $k$。

当然，每组数据都要把 $m$ 数组清零。

#### 代码 $\And$ 讲解

```cpp
#include <cstdio>
#include <cstring>//memset 函数需要包含的头文件

using namespace std;
int t;
typedef long long ll;
ll n,a[200010],m[200010];
bool N_f(ll a,ll b){
    return (a>0&&b<0)||(a<0&&b>0);
}
#define big(a,b) a>b?a:b//不使用内置的 max 函数, 加快速度
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%lld",&n);
        memset(m,0,sizeof(m));
        ll cnt=0,ans=0;
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            if(i==1) m[cnt]=a[i];//如果是第一个数则之间加入第一段, 第一段的最大值定为 a[1]
            else if(N_f(a[i],a[i-1])){//如果这个数与前面的数异号
                cnt++;//段数+1
                ans+=m[cnt-1];//ans 加上上一段的最大值
                m[cnt]=a[i];//统计
            }
            else{//否则
                m[cnt]=big(m[cnt],a[i]);//更新最大值
            }
        }
        printf("%lld\n",ans+m[cnt]);//由于 m[cnt] 是无法加到的，所以得另外加
    }
    return 0;
}
```

---

## 作者：小恐 (赞：0)

思路灰常简单：

因为首先要保证这个子序列最长，所以从前往后扫这个队列，把它分成若干段，每段符号都一样。~~显然~~，从每一段中选最大的加起来就是答案。

上代码：
```cpp
#include<stdio.h>
#include<iostream>//max函数要用
using namespace std;
int t,n,a,now;
long long ans;
bool flag;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		scanf("%d",&a);//先读进来一个数
		flag=a>0;//flag表示上一个数是否为正数
		now=a;//目前这一段只有一个a，所以最大值设成a
		ans=0;//答案，设成初值0
		for(int i=2;i<=n;++i)
		{
			scanf("%d",&a);
			if(a>0==flag)//如果和上一个数正负相同
				now=max(now,a);//取最大的
			else//不相同
			{
				ans+=now;//答案加上这一段最大值
				flag=!flag;//肯定是变了正负
				now=a;//设最大值初值
			}
		}
		ans+=now;//最后一段没处理，加上最大值
		printf("%lld\n",ans);//输出，记得开long long
	}
	return 0;
}
```
感谢阅读！~~点个赞再走呗！~~

---

