# [ABC233D] Count Interval

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc233/tasks/abc233_d

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ と、整数 $ K $ が与えられます。

$ A $ の連続部分列のうち、要素の和が $ K $ になるものはいくつありますか？  
 すなわち、以下の条件を全て満たす整数の組 $ (l,r) $ はいくつありますか？

- $ 1\leq\ l\leq\ r\leq\ N $
- $ \displaystyle\sum_{i=l}^{r}A_i\ =\ K $

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ |A_i|\ \leq\ 10^9 $
- $ |K|\ \leq\ 10^{15} $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ (l,r)=(1,2),(3,3),(2,6) $ の $ 3 $ 組が条件を満たします。

### Sample Explanation 2

条件を満たす $ (l,r) $ の組が $ 1 $ つも存在しないこともあります。

## 样例 #1

### 输入

```
6 5
8 -3 5 7 0 -4```

### 输出

```
3```

## 样例 #2

### 输入

```
2 -1000000000000000
1000000000 -1000000000```

### 输出

```
0```

# 题解

## 作者：loser_seele (赞：3)

很套路的题了，但是场上没调出来，寄。

人话题意：统计区间和为 $ K $ 的区间个数。一个简单的转化：首先预处理前缀和数组 $ sum $，则满足条件的区间为 $ s_r-s_{l-1}=K $。

直接暴力枚举两个区间端点的做法是 $ \mathcal{O}(n^2) $ 的，显然难以接受。于是可以考虑枚举右端点 $ r $，在计算答案时加上满足 $ s_{l-1}=s_r-K $ 的所有 $ l $ 的个数即可。发现问题转化为了统计 $ s_{i}=x $ 的个数，直接开一个 STL 的 unordered_map 即可解决。

时间复杂度 $ \mathcal{O}(n) $，可以通过。注意数据范围，需要开 long long 才能保证不越界。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
long long sum[200020];
long long a[200020];
unordered_map<long long,int>q;
int main()
{
	int n;
	long long k;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
	cin>>a[i];
	sum[i+1]=sum[i]+a[i];
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	q[sum[i-1]]++,ans+=q[sum[i]-k];
	cout<<ans;
}
```


---

## 作者：Jerry_heng (赞：1)

（一）

记录前缀和 $sum$，查找前缀和为 $sum-k$ 的个数。

由于常数过大，用 map 存储。

记得开 long long。


（二）

AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int>mp;
int n,k,sum,ans;
signed main(){
	cin>>n>>k;
	mp[0]=1;//注意
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		sum+=x;//记录前缀
		ans+=mp[sum-k];
		mp[sum]++;
	}
	cout<<ans;
}
```

---

## 作者：LBYYSM_123 (赞：0)

~~几乎是前缀和的模板题~~  
 题意为:   

    给定一个数组 a，问有多少个区间满足区间里所有的数的和是 k。


------------

很套路的题了，用前缀和。但只是单纯用前缀和统计区间的话时间复杂度爆表，所以我们可以单纯统计右端点就可以了。首先预处理前缀和数组 $ sum $，则满足条件的区间为 $ s_r-s_{l-1}=K $ 。于是可以考虑枚举右端点 $ r $，在计算答案时加上满足 $ s_{l-1}=s_r-K $ 的所有 $ l $ 的个数即可。发现问题转化为了统计 $ s_{i}=x $ 的个数。
  
代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long//注意数据范围，用宏定义将int定为long long。
using namespace std;
int a[200005],q[200005],ans=0;
map<int,int> p;
signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		q[i]=q[i-1]+a[i]; 
	}
	for(int i=1;i<=n;i++)
		p[q[i-1]]++,ans+=p[q[i]-k];
	cout<<ans;//输出
   /*复杂度从O(n^2)变为O（n）*/
	return 114514;
} 
```

---

## 作者：冷却心 (赞：0)

## 题意
给定一个长度为 $n$ 的数组 $A_1,A_2,A_3,\cdots,A_n$。

有多少个区间满足区间和为 $k$。

## 解法

因为是无修改的区间和，所以先前缀和一遍，前缀和数组为 $Pre_1,Pre_2,\cdots,Pre_n$。

暴力 $O(n^2)$ 思路为枚举 $l,r$，满足 $Pre_r-Pre_{l-1}=k$，答案就加一。

优化：

$Pre_r - Pre_{l - 1} = k$ 可以变化为 $Pre_r - k = Pre_{l - 1}$。

则枚举 $r$，以 $A_r$ 结尾的满足要求的区间个数就为满足 $l < r$ 且 $Pre_{l-1} = Pre_r - k$ 的 $l$ 的个数。

求个数可以用 `map` 实现。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin \
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0);
using namespace std;
const LL N = 2e5 + 10;
LL n, ans = 0, k, A[N], Pre[N];

map<LL, LL> mp;

int main(){
	Fcin;
	cin >> n >> k;
	for (LL i = 1; i <= n; i ++){
		cin >> A[i];
	}
	for (LL i = 1; i <= n; i ++){
		Pre[i] = Pre[i - 1] + A[i];
	}
	
	for (LL i = 1; i <= n; i ++){
		mp[Pre[i - 1]] ++;
		LL t = Pre[i] - k;
		ans += mp[t];
	}
	cout << ans;
	return 0;
}
```


---

## 作者：fish_love_cat (赞：0)

这不是前缀和嘛……

统计前缀和，但暴力显然会 TLE 的，考虑优化。我们把每一个前缀和作为区间的开头位置的上一格出现的数量统计在 ```map``` 里，以当前前缀和为结尾，减去 $k$ 得到开头位置减一的前缀和应是多少，然后在 ```map``` 中查询这一前缀和在前面出现了几次，每出现一次都可以和当前位置形成一个区间，所以 $ans$ 要加上这出现的数量。最后输出就能 [AC](https://www.luogu.com.cn/record/109864317) 了。

**贴代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005],ans;
map<long long,long long> mapp;
int main(){
    long long n,k;
    cin>>n>>k;
    for(long long i=1;i<=n;i++){
        cin>>a[i];
        a[i]+=a[i-1];
        //统计前缀和
    }
    for(long long i=1;i<=n;i++){
        mapp[a[i-1]]++;//注意！是统计每一个开头位置减一！
        ans+=mapp[a[i]-k];
        //计算
    }
    cout<<ans<<endl;
    return 0;
}
//别问为啥全用的long long，问就是作者没看数据范围-_-||
```

---

## 作者：chengning0909 (赞：0)

# abc 233 d

## 题意

请你求出在长度为 $N$ 的序列中有多少个字段的和为 $K$。

## 思路

首先，我们可以用前缀和来表示一个子段的和，也就是 $s_r - s_{l - 1}$。

所以题目的要求就是：

求出有多少对 $(l, r)$ ，使得 $s_r - s_{l - 1} = k$，也就是 $s_r = s_{l - 1} + k$。

所以就有这么一种方法：

枚举所有的区间，判断是否满足条件。

但是，这样很明显时间复杂度为 $O(n ^ 2)$，那么，应该如何优化呢？

对于 $i$ 来说，$s_{i - 1} + k$ 是一个定值，也就是说，只要提前算出在 $i$ 之后的 $s_{i - 1} + k$ 的数量即可。

---

