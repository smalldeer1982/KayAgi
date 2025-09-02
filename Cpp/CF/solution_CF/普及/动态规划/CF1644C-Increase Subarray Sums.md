# Increase Subarray Sums

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ integers. You are also given an integer value $ x $ .

Let $ f(k) $ be the maximum sum of a contiguous subarray of $ a $ after applying the following operation: add $ x $ to the elements on exactly $ k $ distinct positions. An empty subarray should also be considered, it has sum $ 0 $ .

Note that the subarray doesn't have to include all of the increased elements.

Calculate the maximum value of $ f(k) $ for all $ k $ from $ 0 $ to $ n $ independently.

## 说明/提示

In the first testcase, it doesn't matter which elements you add $ x $ to. The subarray with the maximum sum will always be the entire array. If you increase $ k $ elements by $ x $ , $ k \cdot x $ will be added to the sum.

In the second testcase:

- For $ k = 0 $ , the empty subarray is the best option.
- For $ k = 1 $ , it's optimal to increase the element at position $ 3 $ . The best sum becomes $ -1 + 5 = 4 $ for a subarray $ [3, 3] $ .
- For $ k = 2 $ , it's optimal to increase the element at position $ 3 $ and any other element. The best sum is still $ 4 $ for a subarray $ [3, 3] $ .
- For $ k = 3 $ , you have to increase all elements. The best sum becomes $ (-2 + 5) + (-7 + 5) + (-1 + 5) = 5 $ for a subarray $ [1, 3] $ .

## 样例 #1

### 输入

```
3
4 2
4 1 3 2
3 5
-2 -7 -1
10 2
-6 -1 -2 4 -6 -1 -4 4 -5 -4```

### 输出

```
10 12 14 16 18
0 4 4 5
4 6 6 7 7 7 7 8 8 8 8```

# 题解

## 作者：信息向阳花木 (赞：11)

可能是最详细的了（莫名自信）

若您看完这篇题解后觉得对您有帮助，那就点个赞吧！



------------
[题目传送门](https://www.luogu.com.cn/problem/CF1644C)

每次操作中的 $x$ 都是非负数，所以我们增加 **最大和的子段内的元素**，一定最优。


对于任意一个 $k$，增加的值是固定的（$k \times x$）于是，我们可以先算出，$a$ 的 **不同长度的** 最大子段和。这个我们可以用 **动态规划** 来做。（还有前缀和优化）

设 $s_i$ 表示 $a_1 + a_2 + a_3 + \ldots + a_i$ 的和，$f_i$ 表示 **长度为 $i$** 的最大子段和。那么动态转移方程就是：

$f_{j - i + 1} = \max\{s_j - s_{i -  1}\}$

很显然，这个表示的是：$a_i \sim a_j$ 的和。当然 $a_i \sim a_j$ 的长度是 $j - i + 1$。

当然，我们还要做一个 **后缀最大值**。

于是，$f_i$ 的定义又要发生变化了：$f_i$ 表示 **长度大于等于 $i$** 的最大子段和。

原因很简单，因为只要字段长度 $≥k$，就可以将字段中 $k$ 个不同的位置上的数加上 $x$。

最后，注意每次不是加 $k$ 个，而是加 $≤k$ 个，所以我们还要和 $f_{i - 1}$ 取一个 $\max$.



------------
好了，你们要的代码来了。
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int inf=1e9;
int n,t,x;
int s[5010],f[5010];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		for(int i=1;i<=n;i++){
			int a;
			cin>>a;
			s[i]=s[i-1]+a; 
		}
		for(int i=0;i<=n;i++) f[i]=-inf; //注意 a 中可能有负数。 
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
				f[j-i+1]=max(f[j-i+1],s[j]-s[i-1]);
		for(int i=n-1;i>=0;i--) f[i]=max(f[i],f[i+1]);
		for (int k=0;k<=n;k++){
			f[k]=max(f[k-1],f[k]+k*x); //注意这里一定要更新 f[k] 的值，因为后面还会用到它。
			cout<<f[k]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Terminator_SHH (赞：2)

## Solution
$n \leq 5000$ 证明 $O(n^2)$ 是可行的。

那么"将 $a$ 中 $k$ 个不同的位置上的数加上 $x$"  
等效于“在这个连续子串 $str$ 中加上 $k \times x$ 的最大值。”  

我们通过前缀和算出前面子串的和，通过 $for_{i,j}$ 扫描所有子串并加上 $k \times x$ 的最大值即可。  

答案为 $\max(ans,a_{j}-a_{j-i}+min(i,j) \times k)$ 。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxlen 5000
using namespace std;

int T,N,X;
int temp[maxlen+1],A[maxlen+1];

signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		memset(A,0,sizeof(A));
		memset(temp,-0x7f7f7f,sizeof(temp));
		scanf("%lld%lld",&N,&X);
      
		for(int i=1;i<=N;i++)
		{
			int a;
			scanf("%lld",&a);
			A[i]=A[i-1]+a;
		}
        
		temp[0]=0;
		for(int i=1;i<=N;i++)
		{
			for(int j=i;j<=N;j++)
				temp[i]=max(temp[i],A[j]-A[j-i]);
		}
		for(int i=0;i<=N;i++)
		{
			int ans=-1e9;
			for(int j=0;j<=N;j++)
				ans=max(temp[j]+min(i,j)*X,ans);
			printf("%lld ",ans);
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：zhongcy (赞：2)

[CF Problem](https://codeforces.com/problemset/problem/1644/C)

### Solution

------------

因为 $ x $ 是非负的，所以增加最大和的子段内的元素，是最佳的做法。显然，对于长度 $ k $，增加的值便为 $ k \cdot x $。因此，我们可以考虑先统计每个长度的最大子段和，再在最后统计答案。

于是我们就可以设 $ f_{i} $ 为长度为 $ i $ 的最大子段和。注意前缀和优化。

状态转移方程便为 
$$ f_{j-i+1}=\max(f_{j-i+1},pre_j-pre_{i-1}) $$
其中，$ i,j $ 为子段开始与结束的下标，$ pre_i $ 表示前 $ i $ 个数的和。

### Code

------------
时间复杂度 $ \Theta(Tn^2) $。

```cpp
#include<bits/stdc++.h>
#define N 5005
#define ll long long
#define inf LONG_LONG_MAX
using namespace std;
ll n,x;
ll a[N],pre[N],f[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll t;cin>>t; 
	while(t--)
	{
		cin>>n>>x;
		f[0]=-inf;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			pre[i]=pre[i-1]+a[i];//前缀和
			f[i]=-inf; //初始化
		}
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
				f[j-i+1]=max(f[j-i+1],pre[j]-pre[i-1]);//状态转移方程
		for(int i=n-1;i>=0;i--)
			f[i]=max(f[i],f[i+1]);
		for(int i=0;i<=n;i++)
		{
			f[i]=max(f[i-1],f[i]+i*x);//统计最后答案
			cout<<f[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：windflower (赞：2)

简要题意：  
>给定一个数组 a 和两个整数 x 和 k ，给定一个操作可以从数组中选取 i 个不同下标的数加上 x ，对于每一个 $i(0\le i\le k)$ 输出操作后最大连续子序列的最大值。  

先观察数据范围 $\sum n\le5000$ ，这说明可以用一个 $O(n^2)$ 的算法来解决。由于 x 非负，所以对于任意连续子序列，必定要尽可能地将 x 加到子序列内部才能使它最大。而一个子序列所能接纳的 x 的数量为 $\max(i,len)$ 。因此当子序列长度固定时，该操作对序列和的影响是固定的。故我们只需将数组 a 不同长度的连续子序列的最大值储存下来即可, 所求的答案即 $\max(sum_{len}+\max(i,len)\cdot x)(0 \le len \le n)$ 

附 AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[5005],f[5005],x,sum,ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		memset(f,-0x3f,sizeof(f));
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			sum=0;
			for(int j=1;j<=i;j++)sum+=a[j];
			for(int j=i;j<=n;j++){
				f[i]=max(f[i],sum);
				sum=sum+a[j+1]-a[j-i+1];
			}
		}
		for(int k=0;k<=n;k++){
			ans=0;
			for(int i=1;i<=k;i++)ans=max(ans,f[i]+i*x);
			for(int i=k+1;i<=n;i++)ans=max(ans,f[i]+k*x);
			printf("%d ",ans);
		}
		printf("\n");
	}
	return (0-0);
}
```


---

## 作者：_ajthreac_ (赞：1)

首先假设已经选出来了一段 $[l,r]$，由于 $x$ 非负，贪心地考虑会发现要尽量多地给区间内的数加 $x$。容易发现这时答案只与区间和与区间长度（一共累加了 $\min\{k,r-l+1\}$ 个 $x$）有关。

那么自然想到枚举区间长度，当长度固定时增量是固定的，也就是我们只需要考虑原序列长度为定值的最大子段和。

参考代码：
```cpp
const int N=5010;
int T,n,x,a[N],mx[N],sum[N];
signed main(){
  Read(T);
  while(T--){
    Read(n),Read(x);
    for(int i=1;i<=n;i++){
      Read(a[i]),sum[i]=sum[i-1]+a[i];
    }
    for(int l=1;l<=n;l++){
      mx[l]=-INF;
      for(int i=1;i+l-1<=n;i++){
        mx[l]=max(mx[l],sum[i+l-1]-sum[i-1]);
      }
    }
    for(int k=0;k<=n;k++){
      int mxx=0;
      for(int l=0;l<=n;l++)mxx=max(mxx,mx[l]+min(l,k)*x);
      printf("%lld ",mxx);
    }
    puts("");
  }
  KafuuChino HotoKokoa
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 思路

首先输入 $a$ 数列后，设 $s$ 数列，其中 $s[i]=\sum^{i}_{j=1}a[j]$，即前缀和。

然后，设 $f$ 数列，设 $f[i]$ 为长度为 $i$ 的子串最大和，即：

$$f[i]=\operatorname{max}^{n}_{j=i}(s[j]-s[j-i])$$

显而易见，$f[0]=0$。

最后我们求对 $k$ 个元素加 $x$ 的时候，我们要枚举一遍 $f$ 数组。很明显的，对于长度大于等于 $k$ 的数列，总和要加 $k\times x$；否则就加 $length \times x$。

形象的说：

$ans(k)=\operatorname{max}^{n}_{i=0}[f[i]+\operatorname{min}(i,k)\times x]$

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 5000
#define inf 0x3f3f3f3f
int t;
int n;
int x;
int a[max_n+2];
int s[max_n+2];
int f[max_n+2];
int ans;
int ma(int a,int b){
	return a>b?a:b;
}
int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1644C_2.in","r",stdin);
	freopen("CF1644C_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&x);
		memset(s,0,sizeof(s));
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			s[i]=s[i-1]+a[i];
		}
		f[0]=0;
		for(int i=1;i<=n;++i)f[i]=-inf;
		for(int p=1;p<=n;++p){
			for(int i=p;i<=n;++i)f[p]=ma(f[p],s[i]-s[i-p]);
		}
		for(int p=0;p<=n;++p){//x个数
			ans=0;
			for(int i=0;i<=n;++i)ans=ma(ans,f[i]+mi(i,p)*x);//长度
			printf("%d ",ans);
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/69929565)

**By dengziyue**

---

## 作者：清烛 (赞：0)

题意：给定一个序列 $a$ 和一个非负整数 $x$，令 $f(k)$ 为 对 $a$ 中的 $k$ 个不同元素都加上 $x$ 后，$a$ 的最大子段和。对于 $k\in[0,n]$ 求出 $f(k)$，$n\le 5000$，数据不会爆 `int`。

解法 1：基于经典的 $O(n)$ 最大子段和的 DP，令 $f_{i,j}$ 为强制选 $a_i$，对 $j$ 个元素加了 $x$ 后的最大子段和，则类比经典 dp 的转移，我们可以得到
$$
\begin{cases}
f_{i,0} = \max(f_{i-1,0},0)+a_i\\
f_{i,j} = \max(f_{i-1,j}+a_i,a_i,f_{i-1,j-1}+a_i+x,a_i+x)&1\le j\le i
\end{cases}
$$
记得输出答案的时候取前缀最大值，然后要和 $0$ 取 $\max$。

```cpp
const int maxn = 5005;
int a[maxn], n, x;
int f[maxn][maxn], ans[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n, x);
        FOR(i, 1, n) {
            read(a[i]);
            FOR(j, 0, n) f[i][j] = -2e9, ans[j] = 0;
        }
        f[0][0] = 0;
        FOR(i, 1, n) {
            f[i][0] = max(f[i - 1][0] + a[i], a[i]);
            FOR(j, 1, i) {
                f[i][j] = max(f[i - 1][j] + a[i], a[i], f[i - 1][j - 1] + a[i] + x, a[i] + x);
            }
            FOR(j, 0, i) chkmax(ans[j], f[i][j]);
        }
        FOR(i, 0, n) print(ans[i] = chkmax(ans[i], ans[i - 1]), ' ');
        putchar('\n');
    }
    return output(), 0;
}
```

解法 2：考虑贪心。既然要求 $f(k)$，那就求出所有长度至少为 $k$ 的子段和，取其最大值加上 $k\times x$ 即可。正确性：去除的子段长度一定要 $\ge k$ 才能给 $k$ 个位置加上 $x$。然后同样要对答案取前缀最大值。

```cpp
#define N 5005

int sum[N][N],a[N],ans[N],maxsum[N],n, x;

int main()
{
    int t;cin>>t;
    rep(kase,1,t)
    {
        cin>>n>>x;
        rep(i,1,n)cin>>a[i],sum[1][i]=sum[1][i-1]+a[i];
        rep(i,2,n)rep(j,i,n)sum[i][j]=sum[1][j]-sum[1][i-1];
        per(len,n,0)
        {
            maxsum[len]=-2e9;
            if(len>0) rep(i,1,n-len+1)chkmax(maxsum[len],sum[i][i+len-1]);
            if(len<n) chkmax(maxsum[len],maxsum[len+1]);
        }
        rep(k,0,n)ans[k]=max(maxsum[k]+k*x,0);
        rep(k,1,n)chkmax(ans[k],ans[k-1]);
        rep(k,0,n)cout<<ans[k]<<' ';
        cout<<'\n';
    }
    return 0;
}
```

> 声明，代码都是我写的，码风不一致是因为特殊原因。

---

