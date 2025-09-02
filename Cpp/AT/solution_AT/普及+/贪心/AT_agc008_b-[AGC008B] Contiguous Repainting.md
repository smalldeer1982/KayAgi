# [AGC008B] Contiguous Repainting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_b

$ N $ 個のマスが横一列に並んでいます。 左から $ i $ 番目のマスには整数 $ a_i $ が書かれています。

最初、すべてのマスは白色です。 すぬけ君は次の操作を好きな回数だけ繰り返します。

- 連続する $ K $ 個のマスを選び、それらすべてを白く塗るか、それらすべてを黒く塗る。 このとき、各マスの色は上書きされる。

すぬけ君が操作を終えた後、黒いマスに書かれた整数の総和がスコアになります。 考えられるスコアの最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =N\ <\ =10^5 $
- $ 1\ <\ =K\ <\ =N $
- $ a_i $ は整数である。
- $ |a_i|\ <\ =10^9 $

### Sample Explanation 1

左から $ 2 $, $ 3 $, $ 4 $ 番目のマスを黒く塗ればよいです。

### Sample Explanation 2

たとえば、次のように操作を行えばよいです。 - 左から $ 1 $, $ 2 $ 番目のマスを黒く塗る。 - 左から $ 3 $, $ 4 $ 番目のマスを黒く塗る。 - 左から $ 2 $, $ 3 $ 番目のマスを白く塗る。

## 样例 #1

### 输入

```
5 3
-10 10 -10 10 -10```

### 输出

```
10```

## 样例 #2

### 输入

```
4 2
10 -10 -10 10```

### 输出

```
20```

## 样例 #3

### 输入

```
1 1
-10```

### 输出

```
0```

## 样例 #4

### 输入

```
10 5
5 -4 -5 -8 -4 7 2 -4 0 7```

### 输出

```
17```

# 题解

## 作者：zljhenry (赞：6)

一道结论题。

考虑最后一次操作，一定会将一段长为 $k$ 的区间变成白色或黑色。

但是其余的操作，可以将其他的任何一个地方变成任意一种颜色。

所以只需要求 3 个值：区间和、区间之前所有正数的和、区间之后所有正数的和。

对于这个区间的值，如果为正数，就把他涂成黑色，如果为负数，就把他涂成白色。

CODE：

```cpp
// Problem: AT2264 [AGC008B] Contiguous Repalling
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2264
// Memory Limit: 250 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define M 100005
ll n,k;
ll ans=-1;
ll a[M];
ll sum1[M],sum2[M],sum3[M];
int main(){
	scanf("%lld%lld",&n,&k);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum1[i]=sum1[i-1]+(a[i]<0?0:a[i]);//区间之前所有正数的和
		sum3[i]=sum3[i-1]+a[i];//前缀和求区间的和
	}
	for(ll i=n;i>=1;i--) sum2[i]=sum2[i+1]+(a[i]<0?0:a[i]);//区间之后所有正数的和
	for(ll i=1;i<=n-k+1;i++){
		ll A=sum1[i-1];
		ll B=sum2[i+k];
		ll C=sum3[i+k-1]-sum3[i-1];
		//求出这3个值
		if(C<0) C=0;
		ans=max(ans,A+B+C);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Acheron_RBM (赞：2)

这题是很明显的贪心。

最后一次操作，一定会将一段长为 $k$ 的区间变成一样的颜色。

其余前后都可以是任何颜色。

我们要求值最大，所以可以把所有都染成黑色。

我们求出区间和、区间前缀和、区间后缀和。

然后暴力枚举长度为 $k$ 的区间，求出最大值即可。

```cpp
int main()
{
	long long n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		l[i]=l[i-1]+max(a[i],0ll);//前缀和 
		r[i]=r[i-1]+a[i];
	}
	for(int i=n;i>=1;i--)	
	{
		l1[i]=l1[i+1]+max(a[i],0ll);//后缀和 
	}
	for(int i=1;i<=n-k+1;i++)
	{
		ret=max(ret,l[i-1]+l1[i+k]+max(0ll,r[i+k-1]-r[i-1]));
	}
	cout<<ret;
	return 0;
}
```

---

## 作者：fish_love_cat (赞：1)

**思路：**

结论：除了一组连续的 $k$ 个位置，其他地方上的颜色是可以让我们随便填的。

举个栗子：我们设 $n=5,k=3$。

初始时：

```白白白白白```

如果要只把第 $4$ 个涂黑，首先需要把 $2,3,4$ 都涂了：

```白黑黑黑白```

然后把 $1,2,3$ 都涂成白色，覆盖掉：

```白白白黑白```

这样就成功了！多做几次，我们可以发现，通过覆盖的原理，除了那连续的会颜色一致外，其他地方想是啥颜色就可以是啥颜色。

---

如此，解法也就呼之欲出了。

我们遍历每一个长度为 $k$ 的区间，如果这一段的和比 $0$ 小，就不选涂白，否则就涂黑记录答案。不在这个区间内的可以乱涂，通过贪心的想法，不是负数就涂黑加进来，是负数就涂白不要了，这么做显然是最优的。

但如果每一种区间位置都要遍历一遍数组求答案，结局必然是会 T 的飞起，需要进行优化。

求区间和的值……这简直就是为了前缀和量身定做的情况！我们开两个前缀和数组，一个记录全部乱涂的前缀和，计算乱涂部分；一个记录全涂一个色的前缀和，计算长度为 $k$ 的那个区间的前缀和。

然后计算一下答案，把所有情况下的最大答案输出就可以了。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,qzh1[100005],qzh2[100005];
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        qzh1[i]=qzh1[i-1]+x;
        qzh2[i]=qzh2[i-1]+max(0,x);
        //记录前缀和，如果比0小（即负数）就置0，不对答案造成影响，相当于不选。
    }
    for(int i=1;i<=n-k+1;i++){
        ans=max(ans,max((long long)0,qzh1[i+k-1]-qzh1[i-1]/*k区间值如是负数，就置0，同样相当于不选。*/)+qzh2[n]-(qzh2[i+k-1]-qzh2[i-1])/*总的减去k区间，因为k区间在前面算过了，不可以乱涂*/);//核心！
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### ~~简单的~~一道前缀和友好题   
当看到这种操作问题时，不是 $\text{DP}$ 就是找规律(这种就是思维题)。      

这道题目明显属于后者。     

## 题目分析
~~如若说玩过涂色问题估计直接秒了~~       

一次次的操作太麻烦了！它的影响很不好处理，所以我们先考虑一下**怎样能让它只影响一个数**。      

有了极端想法，模拟几下不难发现：从两端往中间，挨个往里挪，这样我们就能任意选择**除了最后 $k$ 长度的区间之外的所有点了**。     

于是这道题就很简单，用三个数组分别统计前缀再 $O(n)$ 枚举最后的 $k$ 长度的区间就行(代码中有细节)。     

```cpp
#include<bits/stdc++.h>
#define int long long
const int QWQ=100005;
using namespace std; int ans;
int n,k,a[QWQ],p1[QWQ],p2[QWQ],p3[QWQ];
//p1代表最后区间的区间和
//p2代表区间的前面的非负数和
//p3代表区间的后面的非负数和
signed main(){
	scanf("%lld%lld",&n,&k);
	for (register int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	p1[0]=0,p2[n+1]=0,p3[n+1]=0;
	for (register int i=1;i<=n;i++){
		p1[i]=p1[i-1]+a[i];
    	//这一段无法修改，直接加
		p2[i]=p2[i-1]+max(a[i],0ll);
      	//因为我们能随意修改，我们自然不会让小于0的加进来
	} for (register int i=n;i>=1;i--)
		p3[i]=p3[i+1]+max(a[i],0ll);
       //同理p2
	for (register int i=0;i<=n-k;i++)
		ans=max(ans,p2[i]+p3[i+k+1]+max(p1[i+k]-p1[i],0ll));
       //后面的部分加前面的部分加上最后的部分
       //当然，如果最后的区间小于0我们就整体不选
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：saixingzhe (赞：1)

# 分析
最后一次操作，一定会将一段长为 $k$ 的区间变成白色或黑色。

其余前后都可以随便染色。

我们要求值最大，所以可以把所有都染成黑色。

我们求出区间和、区间前缀正数和、区间后缀正数和。

然后枚举长度为 $k$ 的区间，求出最大值即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,ans=-2147483647,a[100001],q[100001],h[100001],hq[100001]; 
int main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		q[i]=q[i-1]+max(a[i],(long long)0);
		hq[i]=hq[i-1]+a[i];
	}
	for(int i=n;i>=1;i--)	h[i]=h[i+1]+max(a[i],(long long)0);
	for(int i=1;i<=n-k+1;i++){
		ans=max(ans,q[i-1]+h[i+k]+max((long long)0,hq[i+k-1]-hq[i-1]));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT2264)
## 思路
不难想到，如果我们要选某个数 $a_i$，我们可以先把区间 $i,i+k-1$ 变成黑色，然后把区间 $i+1,i+k$ 变成白色，消除对于其它格子的影响。

然后考虑最后一次操作，显然必将连续的长度为 $k$ 的区间涂成黑色/白色，直接枚举这个区间，计算答案即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e5+10;
int s1[N],s2[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,k;cin>>n>>k;
    int ans=0;
    for (int i=1;i<=n;++i){
        cin>>s2[i];
        s1[i]=s1[i-1]+max(s2[i],0LL); 
        s2[i]+=s2[i-1];
    }
    for (int i=1;i+k-1<=n;++i){
        int j=i+k-1;
        ans=max(ans,s2[j]-s2[i-1]+s1[i-1]+s1[n]-s1[j]);
        ans=max(ans,s1[i-1]+s1[n]-s1[j]);
    }
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：Dimly_dust (赞：1)


### ~~**前缀和好题**~~

**题目大意**

给你一个长度为 $N(N≤10^5)$ 的序列 $a$（$∣a_i∣≤10^9$）和一个整数 $K(K\leq N)$，一开始每个数都是白色的，每次可以将这个序列中的连续$K$个数涂成白色或黑色。

你可以进行任意次操作，最后将黑色的数加起来，问最大的和是多少。

**思路**

不论怎么涂，最后总会有一段连续的 $K$ 个数是同种颜色（最后一次涂的 $K$ 个数），除去这些数，其他的数你可以任意设置它们的颜色（例如： $N=5$,$K=3$，$a=1,2,3,4,5$我想把$a_4=4$ 涂成黑色，就先把$ a_{2,3,4}$ 涂黑，再把 $a_{1,2,3}$ 涂白即可）。

于是直接枚举序列中的连续 $K$ 个数，把除了这 $K$ 个数之外所有的正数涂黑，再看这 $K$ 个数涂白（和为负数）还是涂黑（和为正数），统计答案。

**Code**:

```
#include<cstdio>
#include<algorithm>
using namespace std;

#define MAXN 100000
int N,K;
int A[MAXN+5];
long long SumP[MAXN+5],Sum[MAXN+5];//分别是正数的前缀和、一共的前缀和

int main(){
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;i++){
        scanf("%d",&A[i]);
        Sum[i]=Sum[i-1]+A[i];
        SumP[i]=SumP[i-1]+(A[i]>0)*A[i];
    }
    long long Ans=0;
    for(int i=K;i<=N;i++){
        long long tmp=Sum[i]-Sum[i-K];//目前K个数的和
        tmp=(tmp>0)*tmp+SumP[i-K]+SumP[N]-SumP[i];//如果目前K个数的和为正数，就把他们涂黑
        Ans=max(Ans,tmp);
    }
    printf("%lld",Ans);
}
```


---

## 作者：_txb_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc008_b)

## 题意：
一开始所有格子为白色，可以把连续 $k$ 个数改为黑色或白色，最后让我们求黑色格子和的最大值。

## 思路：
肯定是黑色包含的是这一段的和大于 $0$ 的数，白色是这一段的和小于 $0$ 的数，如果最后的和是整数就输出，否则就输出 $0$。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,sum=0,x[100005],y[100005];//十年oi一场空，不开longlong见祖宗。 
int main()
{
	cin>>n>>k;//输入 
    for(int i=1;i<=n;i++)
	{
        cin>>y[i];
        x[i]=x[i-1];
        if(y[i]>0) x[i]+=y[i];//如果大于0就加入前缀和 
        y[i]+=y[i-1];
    }
    for(int i=1;i+k<=n+1;i++)//遍历数组 
	{
        int j=i+k-1;
        sum=max(sum,max(y[j]-y[i-1]+x[i-1]+x[n]-x[j],x[i-1]+x[n]-x[j]));//去出两种可能的大值 
    }
    cout<<sum;//输出 
    return 0;
}
```


---

## 作者：rabbitohh (赞：0)

注意到，若将 $[a,a+k-1]$ 涂黑，$[a+1,a+k]$ 涂白。那么就相当于只把 $a$ 这一个位置涂黑了。如果我们正着这么涂一遍，把值为正的位置全涂黑，再反着涂一遍，最后只剩下一个长度为 $k$ 的区间是白的，剩下的部分我们可以任意指定黑白。若把最后这个区间也涂黑，即可做到有一个长度为 $k$ 的区间是黑的，剩下的部分我们可以任意指定黑白。而最后一次操作后一定存在长度为 $k$ 的同色连续段。于是我们通过这两种操作就构造出了所有可能的最优解。枚举即可。  
Code：
```cpp
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
int qzh[N],zqzh[N];
int sum(int l,int r)
{
	if(l>r) return 0;
	return qzh[r]-qzh[l-1];
}
int zsum(int l,int r)
{
	if(l>r) return 0;
	return zqzh[r]-zqzh[l-1];
}
signed main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		qzh[i]=qzh[i-1]+a[i];
		if(a[i]>0) zqzh[i]=zqzh[i-1]+a[i];
		else zqzh[i]=zqzh[i-1];
	}
	int ans=0;
	for(int i=1;i+k-1<=n;i++)
	{
		ans=max(ans,zsum(1,i-1)+zsum(i+k,n)+sum(i,i+k-1));
		ans=max(ans,zsum(1,i-1)+zsum(i+k,n));
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：zhangzihang (赞：0)

## 题意分析

- 给定两个数 $n,k$，一共 $n$ 个格子，第 $i$ 个格子中的数为 $a_i$。
- 初始每个格子的颜色均为白色，每次可以选择任意长度为 $k$ 的区间，使其颜色全部变为黑色或白色。
- 求经过多次操作后黑色格子中的数之和最大为多少。

## 算法分析

在纸上经过多次模拟我们发现，我们可以将任意一个格子变成任意一种颜色，但是最后一次操作过后必然有连续 $k$ 个格子是黑色或者白色的，所以就是枚举所有长度为 $k$ 的区间，如果最后一次操作这个区间那么最大值就是，除去这个区间中的数以外剩下正数之和加上这个区间的区间和。稍微拿前缀和维护一下就好了。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
int a[MAXN],s[MAXN],l[MAXN],r[MAXN];
main(){
	int n,k;cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
		l[i]=l[i-1]+(a[i]>0?a[i]:0);
	}
	for(int i=n;i>=1;i--) r[i]=r[i+1]+(a[i]>0?a[i]:0);
	int ans=0;
	for(int i=1;i+k-1<=n;i++){
		int j=i+k-1;
		ans=max(ans,max(s[j]-s[i-1],0ll)+l[i-1]+r[j+1]);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：ECEG (赞：0)

# [AGC008B] Contiguous Repainting题解

## 分析

除了最后一次染色的那个长度为 $k$ 的区间以外的所有格子，都可以**任意确定颜色**（方法就是先贴着整个序列两侧用区间涂色，然后慢慢的吧涂色区间向中间挪，这样就可以一格一格地确定颜色）。

那么直要用**前缀和**处理一下，枚举这个最后涂色的区间即可。

```cpp
#include<bits/stdc++.h>
#define int long long//记得开longlong
using namespace std;
const int qwe=1e5+4;
int n,k,a[qwe],sum[qwe],sum2[qwe],ans;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		sum2[i]=sum2[i-1]+a[i];
		sum[i]=sum[i-1]+max(0LL,a[i]);//因为能随便确定颜色，所以小于0的，就为0 
	}
	for(int i=1;i+k-1<=n;++i)//i~i+k
		ans=max(ans,sum[n]-(sum[i+k-1]-sum[i-1])+max(0LL,sum2[i+k-1]-sum2[i-1]));//一样 
	cout<<ans;
	return 0;
}
```



---

## 作者：yazzkl (赞：0)

**表面一看是DP**

**可以发现：**除了最后一次染色的那个长度为k的区间以外的所有格子，都可以任意确定颜色

**方法：**先贴着整个序列两侧用区间涂色，然后慢慢地把涂色区间向中间挪，这样就可以一格一格地确定颜色

**实现：**那么只要用**前缀和**处理一下，枚举这个最后涂色的区间即可。

因此这题成了前缀和好题。。

```
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int a[N];
long long pre[N], suf[N], sum[N];
 
int main(){
	int n, k;
	long long ans;
	scanf("%d %d",&n,&k);
	for (int i = 1; i <= n; i++) scanf("%d",&a[i]);
	sum[0] = 0;
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	pre[0] = 0;
	for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + max(a[i], 0);
	suf[n + 1] = 0;
	for (int i = n; i >= 1; i--) suf[i] = suf[i + 1] + max(a[i], 0);
	ans = 0;        //枚举区间
	for (int i = 0; i <= n - k; i++)
		ans = max(ans, pre[i] + suf[i + k + 1] + max(sum[i + k] - sum[i], 0LL));
	printf("%lld\n", ans);
	return 0;
}

```

---

## 作者：zqh123b (赞：0)

[**洛谷传送门**](https://www.luogu.com.cn/problem/AT_agc008_b)

[**AtCoder 传送门**](https://atcoder.jp/contests/agc008/tasks/agc008_b)

[博客园食用更佳](https://www.luogu.com.cn/blog/zqh/atagc008b)

----

### 【题目描述】  
~~对不起，没有~~  
题面已经说的很清楚啦，我就~~懒得写了~~不再赘述了。  

### 【题目分析】  
1. 最多有多少个格子一定为 $1$？  

先简化一下，用 $1$ 表示黑，$0$ 表示白。

很简单，比如：
> $1$ $-3$ $-2$ $2$ $3$

就上面这个例子，若 $k = 3$，先让 $1$ 至 $3$ 号位为 $1$，再让 $3$ 至 $5$ 号位为 $1$。易得，有 $k - 1$ 个数字一定为 $1$。  
为了方便，我们去除最后一次操作，使**一定为 $1$ 的格子数正好为 $k$ 个**。  

2. 怎么计算答案？  

不难发现，对于每一段长度为 $k$ 的区间，答案都是**其左边的正数和加其右边的正数和加该区间内的数字和**。  

3. 怎样快速计算这一堆和？  

当然是**前缀和**！

开三个前缀和数组，预处理好数字和，左侧正数和，右侧正数和。  

预处理的时间复杂度为 $O(n)$，能使遍历时的时间复杂度从 $O(n^2)$ 降至 $O(n)$，整体时间复杂度为 $O(n)$，完全能过。

### 【避坑指南】  

不开 long long 见祖宗！！！  
不开 long long 见祖宗！！！  
不开 long long 见祖宗！！！  
（重要的事情说三遍）  

### 【完整代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
long long n,k,a[N];														//按题意
long long sum[N];															//简单前缀和
long long lsum[N],rsum[N];												//两端前缀和
int main(){
	cin>>n>>k;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
	}
	for(long long i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	for(long long i=1;i<=n;i++){
		lsum[i]=lsum[i-1];
		if(a[i]>0)lsum[i]+=a[i];									//贡献为负的不加
	}
	for(long long i=n;i>=1;i--){
		rsum[i]=rsum[i+1];
		if(a[i]>0)rsum[i]+=a[i];									//贡献为负的不加
	}
	long long ans=0;
	for(long long l=1;l+k-1<=n;l++){										//l+k-1即r，需保证在n以内
		long long r=l+k-1;
		ans=max(ans,max(sum[r]-sum[l-1],0ll)+lsum[l-1]+rsum[r+1]);	//计算当前最大值
	}
	cout<<ans<<endl;
	return 0;
}
```

### 【AC 记录】  
[AC 记录](https://www.luogu.com.cn/record/128631360)

感谢各位阅读完本篇题解，请大家留下一个小红心吧！

---

