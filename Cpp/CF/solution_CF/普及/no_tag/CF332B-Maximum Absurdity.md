# Maximum Absurdity

## 题目描述

Berland 的改革还在继续。例如，在昨天的议会会议上，Berland 议会通过了 $ n $ 项法律（每个法律都有一个从 1 到 $ n $ 的独立编号）。今天，这些法律已经放在 Berland 总统 G.W. Boosch 的桌上，等待签署。

这一次，Boosch 先生计划签署 $ 2k $ 项法律。他决定选择两个不重叠的、长度为 $ k $ 的整数段，并签署这两个段内的所有法律。具体来说，Boosch 先生会选择两个整数 $ a $ 和 $ b $ （满足 $ 1 \le a \le b \le n - k + 1 $ 且 $ b - a \ge k $），并签署在段 $ [a; a + k - 1] $ 和 $ [b; b + k - 1] $ 内的法律（包括边界）。

在做出决定时，Boosch 先生当然会考虑公众的意见。为了了解公众的看法，Allberland 公众意见研究中心 (APOSC) 进行了民意调查，并将结果汇总成一份报告交给总统。报告指出了每个法律在公众眼中的"荒谬值"。作为一位追求国家利益的领导者，Boosch 先生希望能签署总"荒谬值"最大的法律。请帮助他完成这一任务。

## 说明/提示

在第一个示例中，Boosch 先生签署了编号在 $ [1; 2] $ 和 $ [4; 5] $ 的法律。签署的法律总"荒谬值"是 $ 3 + 6 + 1 + 6 = 16 $。

在第二个示例中，Boosch 先生签署了编号在 $ [1; 2] $ 和 $ [3; 4] $ 的法律。签署的法律总"荒谬值"是 $ 1 + 1 + 1 + 1 = 4 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 2
3 6 1 1 6
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6 2
1 1 1 1 1 1
```

### 输出

```
1 3
```

# 题解

## 作者：_Tooler_Fu_ (赞：2)

一道简单的贪心题。

这题看似要枚举两个定长区间，实际上可以转化为枚举一个区间来做。

不妨先枚举右区间的左端点 $r_l$，不难发现，左区间的右端点总是落在区间 $\left[1,r_l\right]$ 内。

而我们要使答案最大，就要使左区间答案最大。

而这个最大值是可以通过左移线性求出来的。故我们可以 $O(n)$ 求出合法的两个区间的答案。

注意最后输出的是两个合法的左端点，而不是答案。

代码如下：

```	cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,x,y,z) for(long long i=x;i<=y;i+=z)
#define fd(i,x,y,z) for(long long i=x;i>=y;i-=z)
ll n,k;
ll ans=0,tot=0;
ll sum[200005];
ll mx[200005];
ll a[200005];
ll ot1,ot2;
int main(){
	scanf("%lld%lld",&n,&k);
	f(i,1,n,1){
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	mx[k]=sum[k];
	f(i,k+1,n-k+1,1){
		mx[i]=max(mx[i-1],sum[i]-sum[i-k]);
		if(ans<mx[i-1]+sum[i+k-1]-sum[i-1]){
			ot2=i;
		}
		ans=max(ans,mx[i-1]+sum[i+k-1]-sum[i-1]);
	}
	tot=ans-sum[ot2+k-1]+sum[ot2-1];
	f(i,k,ot2-1,1){
		if(sum[i]-sum[i-k]==tot){
			ot1=i-k+1;
			break;
		}
	}
	printf("%lld %lld\n",ot1,ot2);
	return 0;
}
```

---

## 作者：wunaidedanjuan (赞：1)

### 简化题意

给你一个编号为 $1 \sim n$ 的序列和编号对应的 $x_i$，从中找出两个**不重叠**且长度为 $k$ 的区间，使两个区间内 $x$ 总和最大；这两个区间的左端点分别为 $a$ 和 $b$，若有多种方案，输出 $a$ 值更小的方案；若仍有多种方案，输出 $b$ 值更小的方案。

### 思路分析

作为左区间的左端点，$a$ 取值时要注意给左区间和右区间留下足够的位置，又因为两个区间不重叠且长度均为 $k$，所以可以得到 $1\le a\le n-2k+1,a+k\le b\le n-k+1$。

接下来枚举 $a,b$ 即可。因为需求出区间和最大的方案，所以我们可以用数组 $ans[i]$ 来储存以 $i$ 为左端点的长度为 $k$ 的区间和，这样可以方便在枚举时判断 $a,b$ 取值是否最优。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ir6ns2l.png?x-oss-process=image/resize,m_lfit,h_200,w_300)

由上图可知，当区间左端点由 $i$ 右移至 $i+1$ 时，区间和需减去 $x_i$ 并加上 $x_{j+1}$。由此可以推出：$ans[i]=ans[i-1]-x[i-1]+x[i+k-1]$。

因为求的为两个区间总和最大，所以要分别考虑两个区间对总和的贡献。用 $sum$ 和 $sum1$ 分别记录区间总和和区间 $b$ 当前的最大值，枚举区间 $a,b$，因为要总和最大，所以当 $ans[b]>sum1$ 时，只更新 $sum1$ 取值并记录此时 $b$ 的取值但不更新 $b$ 的取值；当 $ans[i]+sum1>sum$ 时，更新 $a,b,sum$ 的取值。

枚举时防止 $a,b$ 重叠，我们可以倒序遍历，同时为了保证答案准确性，当此时区间和与最大值相等时也要更新取值（保证 $a,b$ 值最小）。

### 思路总结

- 计算左端点不同时长度为 $k$ 的区间和；

- 枚举 $a,b$；

### 代码呈现
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<vector>
#include<string>
#include<bitset>
#include<cctype>
#include<cstdlib>
#include<functional>
#include<istream>
#include<sstream>
#define int long long 
using namespace std;
const int N=200000,inf=0x3f3f;
int x[N],ans[N];
signed main()
{
	int n,k,a=1,b,bb,sum=0,sum1=0;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld",&x[i]);
	ans[a]=0;
	for(int i=1;i<=k;i++)//记录1~k的总荒谬值，即ans[1]的值 
		ans[a]+=x[i];
	for(int i=2;i<=n-k+1;i++)//计算ans[i]的值 
		ans[i]=ans[i-1]+x[i+k-1]-x[i-1];
	bb=a+k;
	for(int i=n-2*k+1;i>=1;i--)
	{
		if(ans[i+k]>=sum1)
		{
			bb=i+k;
			sum1=ans[bb];
		}
		if(ans[i]+sum1>=sum)
		{
			a=i;
			b=bb;
			sum=ans[a]+sum1;
		}
	} 
	printf("%lld %lld",a,b);
	return 0;
}
```

---

## 作者：czh___ (赞：0)

题意：有 $n$ 个数，找两个不相交的长度为 $k$ 的连续子区间，使得两子区间内元素和为最大。

思路：现对得到的数据进行处理，求出以每个位置为结尾的长度为 $k$ 的区间和，以及在该点之后最大的区间和及其位置，再进行遍历。

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int n,k,a[N],mx[N],sum[N],x[N],ans,ans1,ans2;
signed main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
        if(i>=k) 
			sum[i]-=a[i-k];
    }
    for(int i=n;i>=k;i--)
        if(sum[i]>=mx[i+1])
			x[i]=i,
            mx[i]=sum[i];
        else
            mx[i]=mx[i+1],
            x[i]=x[i+1];
    for(int i=k;i<=n;i++){
        int sm=sum[i]+mx[i+k];
        if(ans<sm){
			ans1=i-k+1;
            ans=sm;
            ans2=x[i+k]-k+1;
        }
    }
    printf("%lld %lld",ans1,ans2);
    return 0;
}
```


拜拜！

---

## 作者：lhs_chris (赞：0)

# 暴力思路
题目要我们找两个不重叠的区间，并使区间的值最大。那我们可以考虑使用双重循环搭配前缀和暴力求最大值。代码如下。
```cpp
for(int i=1;i<=n;i++)
{
	ll l=sum[i+k-1]-sum[i-1],maxx;
	for(int j=i+k;j<=n;j++)
	{
		maxx=l+sum[j+k-1]-sum[j-1];
		if(maxx>ans.sum)
		{
			ans.x=i;
			ans.y=j;
			ans.sum=maxx;
		}
	}
}
```
但是暴力的时间复杂度是一定会超时的。那我们考虑一下优化。
# 优化思路
我们可以思考一下如何把第二层循环给优化掉。我们可以用一个结构体数组 $maxx[i]$ 来记录 $i \sim n$ 的最大的区间值，并记录这个区间的起点。这样我们就把第二层循环给优化掉了。

最重要的**注意数据范围**。
# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll unsigned long long
#define lhs printf("\n");
using namespace std;
const int N=3e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
ll n,k;
ll a[N]; 
ll sum[N];
struct node
{
	ll num;
	int id;
}maxx[N];
struct nodee
{
	ll sum;
	ll x,y;
}ans;
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];//前缀和
	} 
	for(int i=n;i>=1;i--)
	{
		if(i+k-1>n)continue;
		ll l=sum[i+k-1]-sum[i-1];
    //更新最大值
		if(maxx[i+1].num>l)
		{
			maxx[i].num=maxx[i+1].num;
			maxx[i].id=maxx[i+1].id;
		}
		else
		{
			maxx[i].num=l;
			maxx[i].id=i;
		}
	} 
	for(int i=1;i<=n;i++)
	{
		if(i+k-1>n)continue;
		ll l=sum[i+k-1]-sum[i-1];
		ll r=maxx[i+k].num,rid=maxx[i+k].id;
		if(l+r>ans.sum)
		{
			ans.x=i;
			ans.y=rid;
			ans.sum=r+l;
		}
	} 
	printf("%lld %lld",ans.x,ans.y);
	return 0;
}
  ```

---

## 作者：sz_jinzikai (赞：0)

# 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF322B)

# 思路

最开始，想到了模拟，一看数据范围：$ 0<=r,g,b<=10^{9} $ ，模拟就被否认了

接着，我想到了一个稍微不无脑一点的思路：$ans = r / 3 + g / 3 + b / 3 + min ({r \bmod 3, g \bmod 3, b \bmod 3})$，接着，就有了一份 WA。打开了 [codeforces](https://codeforces.com/) 的评测列表，打开数据：

	8 8 9

于是，我根据三个数的余数进行排序，特判了第一个数是 $3$ 的倍数且第一个数不为 $0$，且剩下两个数除以 $3$ 的余数都是 $2$ 的情况时，答案 $ + 1$，这样就过了。

# 代码

```cpp

# include <bits/stdc++.h>
using namespace std;
int a[3], x;
bool cmp (int a, int b) {
	return a % 3 < b % 3; //根据余数从小到大排序
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> a[0] >> a[1] >> a[2];
	sort (a, a + 3, cmp); //这里别忘了加cmp！
	cout << a[0] / 3 + a[1] / 3 + a[2] / 3 + min ({a[0] % 3, a[1] % 3, a[2] % 3}) //正常情况下
	+ (a[0] && a[0] % 3 == 0 && a[1] % 3 == 2 && a[2] % 3 == 2); //特殊情况要 + 1
	return 0;
}

```

---

