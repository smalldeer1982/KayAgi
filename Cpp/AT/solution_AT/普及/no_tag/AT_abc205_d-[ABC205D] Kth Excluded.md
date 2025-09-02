# [ABC205D] Kth Excluded

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc205/tasks/abc205_d

長さ $ N $ の正整数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ と $ Q $ 個のクエリが与えられます。

$ i\ \,\ (1\ \leq\ i\ \leq\ Q) $ 番目のクエリでは、正整数 $ K_i $ が与えられるので、$ A_1,\ A_2,\ \dots,\ A_N $ のいずれとも異なる正整数のうち、小さい方から数えて $ K_i $ 番目のものを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ A_1\ <\ A_2\ <\ \dots\ <\ A_N\ \leq\ 10^{18} $
- $ 1\ \leq\ K_i\ \leq\ 10^{18} $
- 入力は全て整数である。

### Sample Explanation 1

$ 3,\ 5,\ 6,\ 7 $ のいずれとも異なる正整数を小さい順に並べると $ 1,\ 2,\ 4,\ 8,\ 9,\ 10,\ 11,\ \dots $ となります。 小さい方から $ 2 $ 番目、$ 5 $ 番目、$ 3 $ 番目はそれぞれ $ 2,\ 9,\ 4 $ です。

## 样例 #1

### 输入

```
4 3
3 5 6 7
2
5
3```

### 输出

```
2
9
4```

## 样例 #2

### 输入

```
5 2
1 2 3 4 5
1
10```

### 输出

```
6
15```

# 题解

## 作者：NotNaLocker (赞：4)

## AT_abc205_d Kth Excluded 题解
### ~~几~~句闲话
> 纪念逝去的星期六。

一楼讲的挺好，我再来补充补充。
### 具体思路
首先看数据，$1 \leq A_i,K_i \leq 10^8$ 便知要开 `long long`，模拟肯定爆掉。so？

我们可以想到**二分**。

先来看看传统二分模板：
```cpp
int l=0,r=n;
while(l<r){
	int mid=(l+r)>>1;
	if(条件) l=mid+1;
	else r=mid-1;
}
```
再来看看这道题的二分模板：
```cpp
int l=0,r=n;
while(l<r){
	int mid=(l+r+1)>>1; //l+r需要加一以防下标为0。
	if(a[mid]-mid<k) l=mid;
	else r=mid-1;
}
```
在第 $4$ 行，因为 $A$ 单调递增，$mid$ 越大，$A_{mid}-mid$ 也越大。当这个值小于 $k$ 了，就不需要把 $mid$ 再往下分。最后输出时需要把值加上 $k$，评论区可以讨论讨论，~~本蒟蒻太蒟了~~。
### AC Coding
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[100005],k;
int bound(int x){
	int l=0,r=n;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(a[mid]-mid<k) l=mid;
		else r=mid-1;
	}
	return l;
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=q;i++){
		cin>>k;
		cout<<k+bound(k)<<endl;
	}
	return 0;
}
```
##  Thanks for watching.

---

## 作者：Light_Star_RPmax_AFO (赞：3)

# 思路——前缀和

### 前言

为了纪念 **长沙市一中** 第二次思维训练。

## 分析

看到找区间里的数，我们就不难想到可以使用前缀和记录每一个位置之前所有的不同于 $A$ 中所有数的正整数中数的个数，不难得出下式：

$$sum_i=sum_{i-1}+A_i-A_{i-1}-1$$

因为 $A$ 是单调递增的，所以我们可以直接使用二分查找到询问的 $k$ 在哪两个数之间这个区间，从而可以得出答案，下式：
$$a_x+k-sum_x$$

注：$x$ 为最后一个小于**不同于 $A$ 中所有数的正整数中数的个数**的数组下标。

# AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,t,a[100010],sum[100010];

signed main(){
	cin>>n>>t;
	for(int i = 1;i <= n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i]-a[i-1]-1;
	}
	while(t--){
		int k;
		cin>>k;
		int x=lower_bound(sum+1,sum+1+n,k)-sum-1;
		cout<<a[x]+k-sum[x]<<endl;
	}
}
/*
4 3
3 5 6 7
2
5
3
*/

---

## 作者：ryf_loser (赞：2)

#### 此题的简单题意是：

给定长度为 $N$ 的正整数序列  $A$

在第 $i$ 次查询中，得到正整数$k_{i}$，求比 $k_{i}$ 小且不在 $A$  中的正整数。

此题数据范围过大，模拟直接炸。

所以我们可以考虑到二分的做法，通过对已知数的二分找到最优解。

我们可以二分找最大的满足 $1 \sim i$ 中不包括 $a_{1} \sim a_{i}$ 小于 $k_{i}$ 的位置。

在枚举时，左指针从 0 开始枚举，右指针从 $n$ 开始枚举，无限接近于正确答案即可。

AC CODE

```cpp
#include<cstdio>
using namespace std;
int n,q;
long long a[100001],k;//十年 OI 一场空，不开 long long 见祖宗。
long long work(){//二分寻找最优解
	int l=0,r=n;
	while (l<r){
		int mid=(l+r+1)>>1;
		if (a[mid]-mid<k)l=mid;
		else r=mid-1;
	}
	return l;
}
int main () {
    scanf ("%d%d",&n,&q);
    for (int i=1;i<=n;i++)scanf ("%lld",&a[i]);
    while (q--){
    	scanf ("%lld",&k);
    	printf ("%lld\n",k+work());//输出
	}
    return 0;
}
```


---

## 作者：_GW_ (赞：1)

思路：看到 $ 1 \le N, Q \le 10^5 $ 要么线性要么带 $ \log $。

于是想到二分答案中包含了多少 $ A $ 数列中的数字。

怎么实现呢？观察到每次询问输入的数值是一定的，考虑从这个数值上下手。

于是重新开一个数组 $a$， $ a_i $ 表示 $ A_1 $ 到 $ A_i $ 这段区间中有多少不同于 $ A $ 数列中的数。

由于 $ A $ 数列是单调递增的，而 $ A_1 \sim A_i $ 这段区间的数字个数又是 $ A_i $ 个数字，所以 $ a_i $ 即为 $ A_i - i $。

最后二分即可。

不多说，上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=114514;
long long n,q,a[N],b[N],sum[N],ans,aa,cxk;
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>aa;
		a[i]=aa-i;//从1到A[i]中有多少不同于A数列中所有数的数
		//由于A数列是单调递增的，所以a[i]可直接取A[i](有多少个数)-i(A[1~i-1]肯定小于A[i]，所以要减去i，A[i+1~n]肯定大于A[i]，超出了范围，不被计算在内)。 
	} 
	while(q--)
	{
		cin>>cxk;
		int l=1,r=n,mid;
		while(l<=r)//二分，求在答案范围内的所有A数列中的数有多少个 
		{
			mid=(l+r)/2;
			if(a[mid]>=cxk) r=mid-1;
			else l=mid+1;
		}
		cout<<cxk+l-1<<endl;//由于l是取的mid+1，所以要减去1 
	}
	return 0;
}
```


---

## 作者：LBYYSM_123 (赞：1)

### 简单题意
对长度为 $N$ 的正整数序列 $A$ 进行 $Q$ 次查询，对每次查询中给定的 $K_i$ ，输出不在序列 $A$ 中 比 $K_i$ 小的正整数。
### 思路
**二分**。   
设 $a[i]$ 表示不包含 $a_1 \sim a_i$ 时，$a_i$ 左侧的从 $1$ 开始的数字个数，然后二分找最大的满足 $a[i]$  小于 $k$ 的位置。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,q,k;
    cin>>n>>q;
    int *a=(int*)malloc((n+1)*sizeof(int));//手动开辟数组 
    for(int i=1;i<=n;i++)
    	cin>>a[i];
    while (q--){
    	cin>>k;
    	int l=1,r=n,mid;
		while(l<=r){
			mid=(l+r)>>1;
			if(a[mid]-mid<k)
				l=mid+1;
			else 
				r=mid-1;//进行二分 
		}
    	cout<<k+l-1<<endl; //因为题目中要求求小于，所以要减1。
	}
    return 0;
}
```


---

## 作者：PineappleSummer (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc205_d)

题意很清楚，这里不再赘述。

读题发现序列是递增的，且询问第 $k$ 小数，考虑二分查找。

原序列为 $a$ 序列，第 $i$ 个数为 $a_i$，我们再统计一个 $b$ 序列，$b_i$ 表示在从 $1$ 到 $a_i$ 中不同于 $a$ 中所有数的正整数个数。$b$ 序列的得到方式为：$b_i=a_i-i$，代码如下：
```cpp
for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]),b[i]=a[i]-i;
```
对于每一次询问，查找不同于 $a$ 中所有数的正整数中第 $k$ 小的那个数。对 $b$ 序列进行二分查找，查找 $b$ 序列中第 $1$ 个大于等于 $k$ 的位置，代码为 `lower_bound(b,b+n+1,k)-b`，返回值 $x$ 有两种情况：

- $x$ 为 $n+1$。此时 $k$ 大于 $b$ 序列中每一个数，说明答案大于 $a_n$。因为 $a_n$ 后面没有在 $a$ 序列的正整数了，所以答案为 $a_n$ 后面第 $k-b_n$ 大的数，即 $a_n+(k-b_n)$。

- $x$ 不为 $n+1$。此时 $k$ 肯定小于等于 $b$ 序列中的某一个数，$k$ 位于 $b_{x-1}$ 与 $b_x$ 之间，那么答案肯定在 $a_{x-1}$ 与 $a_x$ 之间，答案为比 $a_x$ 小的数中从大到小排序第 $b_x-k+1$ 个数，即 $a_x-(b_x-k+1)$。 

代码如下：
```cpp
while(q--)
{
	ll k;
	scanf("%lld",&k);
	int x=lower_bound(b,b+n+1,k)-b;
	if(x==n+1) printf("%lld\n",a[n]+(k-b[n]));
	else printf("%lld\n",a[x]-(b[x]-k+1));
}
```

[完整代码](https://atcoder.jp/contests/abc205/submissions/44111098)

我的第 $1$ 篇黄题题解，有不足之处欢迎大家指出。

---

## 作者：Code_Select_You (赞：0)

# 此题思路：
注意到 $ 1\ \leq\ N,\ Q\ \leq\ 10^5 $，枚举的话时间复杂度为 $O(NQ)$，会TLE。

所以可以考虑二分，用 $f_i$ 表示 $1$ 到 $A_i$ 有多少个不同于 $A_1$ 到 $A_i$ 的数。

因为 $ 1\ \leq\ A_1\ <\ A_2\ <\ \dots\ <\ A_N$，所以可得出 $f_i=A_i-i$。

然后二分，使 $l$ 为满足 $f_l<k$ 中最大的数，不难得出结果便为 $k+l$。

## Code
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
long long k,a[100001],f[100001];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i){
        scanf("%lld",&a[i]);
        f[i]=a[i]-i;
    }
    for(int i=1;i<=q;++i){
        scanf("%lld",&k);
        int l=0,r=n+1,flag=0;
        while(l+1<r){
            flag=(l+r)/2;
            if(f[flag]>=k) r=flag;
            else l=flag;	
        }
        printf("%lld\n",k+l);
    }
}
```

---

## 作者：rzm120412 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc205_d)

这道题其实就是一道二分的**水题**。

我们首先看数据，发现一定要开
```cpp 
long long
```

此题 $mid$ 有些需要注意的地方：需要防止下标为0。

所以说。

```cpp
mid=(l+r+1)>>1
```
来防止下标为0。

此外因为 $A$ 单调递增所以最后输出要加上 $k$ 。

话不多说直接上代码。

**code**:

```cpp
#include <bits/stdc++.h>
using namespace std;
long long int n,q,a[100005],k;
int found(int x){//二分
   int l=0,r=n;
   while(l<r){
      int mid=(l+r+1)>>1;
      if(a[mid]-mid<k){
         l=mid;
      }else{
         r=mid-1;
      }
   }//模板稍做改动
	return l;
}
signed main(){
   cin>>n>>q;
   for(int i=1;i<=n;i++){
       cin>>a[i];
   }
   for(int i=1;i<=q;i++){
   	     cin>>k;
        cout<<k+found(k)<<"\n";
   }
   return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

## 分析
- 首先数据大小已经来到了 $10^5$ 级别，只能考虑线性或者 $\log$。
- 整个数列还具有单调性，那不就是二分吗？
## Solution
1. 二分答案中包含了多少 $A$ 数列中的数字。
2. 重新开一个数组 $a_i$ 表示 $A_1$ 到 $A_i$ 这段区间中有多少不同于 $A$  数列中的数。
3. $a_i-i$ 表示不包含 $a_1∼a_i$ 时，$a_i$ 左侧的从 $1$ 开始的数字个数，然后二分找最大的满足 $a_i-i$ 小于 $k$ 的位置。
4. 不难得到答案为 $p+lt$。
## Code
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define int long long
  const int N=1e5+5;
  int a[N],x,n,q;
  signed main()
  {
      cin>>n>>q;
      for(int i=1;i<=n;i++)
      {
          cin>>x;
          a[i]=x-i;
      }
      while(q--)
      {
          int lt=0,rt=n+1,p;//从下标0~n+1开始二分 
          cin>>p;
          while(lt+1<rt)
          {
              int mid=(lt+rt)>>1;
              if(a[mid]>=p)//找大了，右端点移到mid 
                  rt=mid;
              else//反之，左端点移到mid 
                  lt=mid;
          }
          cout<<p+lt<<"\n";
      }
      return 0;
  }
```


---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc205_d)

## Solution

观察数据，得知数组 $A$ 单调递增，并且要求排除 $A$ 数组中的数寻找第 $K$ 小的数，实际上就是二分数组 $A$，寻找 $A$ 中第一个小于 $K$ 的位置，因为寻找的是第 $K$ 小的位置，所以二分完后要加上 $K$。
题面中不包括 $K$，排除 $K$ 本身，即 $K-1$。

## Code 
```
// 2023/4/26 Accept__

#include <iostream>

using namespace std;

typedef long long ll;

const int kMaxN = 1e5 + 7;

ll n, q, a[kMaxN], k, s;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> k;
        ll l = 1, r = n, m;
        while (l <= r) {
            m = (l + r) / 2, (a[m] - m < k) ? (l = m + 1) : (r = m - 1);
        }
        cout << l + k - 1 << '\n';
    }

    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

### 题目大意

给定长度为 $N$ 的**正整数**序列 $A=(A_1,A_2,…,A_N)$ 和 $Q$ 次查询。

在第 $i$ 次查询中，给定正整数 $K_i$，求比  $K_i$ 小的且不在 $A$ 中的正整数。

### 思路

二分。

$ai-i$ 表示不包含 $a1 \sim ai$ 时，$ai$ 左侧的从 $1$ 开始的数字个数，然后二分找最大的满足 $ai-i$ 小于 $k$ 的位置。

### 代码

```cpp
#include<iostream>
using namespace std;
int n;
long long a[100005], idx[100005]; //数据有点大，开 long long。 
long long fid(long long x) //二分。 
{
    long long l=0,r=n;
    while(l<r)
	{
        long long m=(l+r+1)/2;
        if(a[m]-m<x) l=m;
        else r=m-1;
    }
    return l;
}
int main()
{
	int q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
    while(q--)
	{
        long long k;
        cin>>k;
        long long ans=fid(k); 
        cout<<k+ans<<endl;
    }
    return 0;
}

```


---

## 作者：loser_seele (赞：0)

部分内容参考官方题解。

首先，找到一个序列 $ C $，满足 $ C_i \leq A_i $ 且 $ C_i $ 不出现在序列 $ A $ 中。因为 $ A $ 满足严格单调递增，显然 $ C_i=A_i-i-1 $。

由于题目中保证了 $ A_1=1 $，接下来假设 $ A_0=0 $，不影响答案。

于是考虑二分，对第 $ K $ 小的数分类讨论：

如果 $ C_n < K $，则答案比 $ A_n $ 大，在区间 $ [1,A_n] $ 中有 $ C_n $ 个数满足条件，而比 $ A_n $ 大的所有数显然都满足条件，于是答案为 $ K-C_n+A_n $。

如果 $ C_n \geq K $，套用上面的思路，找到第一个 $ C_i \geq K $ 的下标，则答案一定比 $ A_{i-1} $ 大且小于 $ A_i $，所以区间 $ (A_{i-1},A_i) $ 之间的数一定都满足条件，不难得到答案为 $ K+A_i-C_i-1 $。

因为使用二分查找元素位置，所以总时间复杂度 $ \mathcal{O}(n+q\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e6+10;
vector<int>a,sum;
signed main() 
{
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        a.push_back(x);
    }
    for(int i=0;i<n;i++)
        sum.push_back(a[i]-i-1);
    while(q--) 
    {
        int k;
        cin>>k;
        int idx=lower_bound(sum.begin(),sum.end(),k)-sum.begin();
        if (idx==n) 
            cout<<a[n-1]+(k-sum[n-1]);
        else
            cout<<a[idx]-(sum[idx]-k+1);
        cout<<'\n';
    }
}
```


---

