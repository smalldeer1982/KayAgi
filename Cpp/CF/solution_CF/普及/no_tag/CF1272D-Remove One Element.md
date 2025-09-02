# Remove One Element

## 题目描述

给出一个长度为$n$的序列  
你可以选择性地删除掉该序列中的一个元素，这样，最后的序列长度为$n-1$或$n$  
你需要求出，在选择性的删除操作后，该序列的 最长连续上升子序列的长度

## 说明/提示

$2 \le n \le 2 \cdot 10^5$，$1 \le a_i \le 10^9$  
感谢 @_Wolverine 提供的翻译

## 样例 #1

### 输入

```
5
1 2 5 3 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
6 5 4 3 2 4 3
```

### 输出

```
2
```

# 题解

## 作者：BINYU (赞：8)

### 思路
既然是求最长连续上升子段，那肯定用 DP （没的说）

最大值只可能是两种情况：删除一个或不删除
#### 如果不删除
就是最简单的最长连续上升子段（不是子序列）

状态转移方程(伪代码，无循环）：

```cpp
if(a[i] > a[i - 1])dp1[i] = dp1[i - 1] + 1;
else dp1[i] = 1;
if(a[i] < a[i + 1])dp2[i] = dp2[i + 1] + 1;
else dp2[i] = 1;
```

#### 如果删除（重点！！！）
枚举删除的数，如果删除 i 点，且剩下的能连续（即 $a[i - 1] < a[i + 1]$ ）就可以将以 $a[i - 1] $ 为结尾的最长连续上升子段与以 $a[i + 1] $ 为开头的最长连续上升子段接起来，长度为 $dp1[i - 1] + dp2[i + 1]$
### 注意事项 
1.是上升子段，不是不下降(如数组为：1 1 1 1，应输出1）

2.可以不删除(如数组为：1 2 3 4，应输出4）

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],dp1[200005],dp2[200005],ans;
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
		cin>>a[i];
	for(int i = 1;i <= n;i++)
		if(a[i] > a[i - 1])dp1[i] = dp1[i - 1] + 1;
		else dp1[i] = 1;
	for(int i = n;i >= 1;i--)
		if(a[i] < a[i + 1])dp2[i] = dp2[i + 1] + 1;
		else dp2[i] = 1;
	for(int i = 1;i <= n;i++)
	{
		if(a[i - 1] < a[i + 1])ans = max(ans,dp1[i - 1] + dp2[i + 1]);
		ans = max(ans,max(dp1[i],dp2[i]));
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：wmrqwq (赞：3)

# 题目链接

[CF1272D Remove One Element](https://www.luogu.com.cn/problem/CF1272D)

# 题意简述

给定一个长度为 $n$ 的序列，你需要求出**至多**删除一个数后的这个序列的最长上升子串。

# 解题思路

首先我们可以想一下这题的弱化版，给定一个长度为 $n$ 的序列，你需要求出**至多**删除一个数后的这个序列的最长上升子序列。

这题我们可以设 $dp_i$ 为到位置 $i$，所能得到的最长子序列，然后代码就很容易实现了。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[5010],dp[5010],ans;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],dp[i]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=i-1;j>=1;j--)
			if(a[i]>a[j])
				dp[i]=max(dp[j]+1,dp[i]);
		ans=max(ans,dp[i]);
	}
	cout<<ans;
	QwQ;
}
```

然后我们将这题加强一下，改为给定一个长度为 $n$ 的序列，你需要求出这个序列的最长上升子序列。

这时我们维护 $dp1_i$ 表示到第 $i$ 个数可以达到的最长子串（从 $1$ 开始），维护 $dp2_i$ 表示到第 $i$ 个数可以达到的最长子串（从 $n$ 开始），这样维护也是比较轻松的。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200010],dp1[200010],dp2[200010],ans;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
	forl(i,1,n)
	{
		if(a[i]>a[i-1])
			dp1[i]=dp1[i-1]+1;
		else
			dp1[i]=1;
	}
	forr(i,n,1)
	{
		if(a[i]<a[i+1])
			dp2[i]=dp2[i+1]+1;
		else
			dp2[i]=1;
	}
	forl(i,1,n)
	{
		ans=max({ans,dp1[i],dp2[i]});
		if(a[i]<a[i+1])	
			ans=max(ans,dp1[i]+dp2[i+1]);
	}
	cout<<ans;
	QwQ;
}
```

然后就是此题了，相信只要看懂上面的内容，应该都可以写出来的，我们直接多考虑一个不考虑中间的数的情况即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200010],dp1[200010],dp2[200010],ans;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
	forl(i,1,n)
	{
		if(a[i]>a[i-1])
			dp1[i]=dp1[i-1]+1;
		else
			dp1[i]=1;
	}
	forr(i,n,1)
	{
		if(a[i]<a[i+1])
			dp2[i]=dp2[i+1]+1;
		else
			dp2[i]=1;
	}
	forl(i,1,n)
	{
		ans=max({ans,dp1[i],dp2[i]});
		if(a[i]<a[i+2])	
			ans=max(ans,dp1[i]+dp2[i+2]);
	}
	cout<<ans;
	QwQ;
}
```

---

## 作者：quanjun (赞：3)

本题涉及算法：动态规划。  

首先这里有一个条件“你最多可以删除一个元素”，这个条件会造成我们很多的困扰，所以为了避免困扰，我们先尝试在没有这个条件的情况下解决问题。  

在我们没有删除元素的权限下，数组 $a$ 中的 $n$ 个元素是固定的，所以此时我们可以定义状态 $f[i]$ 表示以 $a[i]$ 结尾并且包含 $a[i]$ 的最长上升子串的长度，那么我们可以发现（设数组坐标从 $1$ 开始）：  

$f[1]=1$；  
当 $i \gt 1$ 时，  
- 如果 $a[i-1] < a[i]$ ，则 $f[i] = f[i-1]+1$
- 否则，$f[i]=1$

代码实现：  
```c++
f[1] = 1;
for (int i = 2; i <= n; i ++) {
    if (a[i-1] < a[i]) f[i] = f[i-1]+1;
    else f[i] = 1;
}
```

然后我们需要求的最长上升子串长度就是所有 $f[i]$ 中最大的那个。  
稍等一下，我们暂时还是不加上“你最多可以删除一个元素”这个条件。  
在加上这个条件之前，我们再定义一个状态 $g[i]$ 表示以 $a[i]$ 开头并且包含 $a[i]$ 的最长上升子串的长度，那么，我们可以得到状态转移方程：  

$g[n] = 1$；  
当 $i < n$ 时，
- 如果 $a[i] < a[i+1]$，则 $g[i] = g[i+1]+1$；
- 否则，$g[i] = 1$

代码实现（注意 $g[i]$ 需要从 $n$ 到 $1$ 反着推）：  
```c++
g[n] = 1;
for (int i = n-1; i >= 1; i --) {
    if (a[i] < a[i+1]) g[i] = g[i+1]+1;
    else g[i] = 1;
}
```

那么我们求完 $f[i]$ 和 $g[i]$ 之后呢，我们再来加回“你最多可以删除一个元素”这个条件。  

首先，如果我们不删除元素，那么答案就是所有 $f[i]$ 中的最大值，我们开一个变量 $ans = \max(f[i])$。  

其次，如果我们删除元素的坐标是 $i$ ，我们假设删除元素后的最长上升子串对应为 $a[l]$ 到 $a[r]，  
那么如果 $i$ 不满足 $l < i < r$ 的条件，那么我删或者不删 $a[i]$ 对我答案丝毫不影响（仍然是 $ans = \max(f[i])$）。

那么什么时候会对答案有影响呢？  
就是当 $1 < i < n$ 且 $a[i-1] < a[i+1]$ 的时候，我删除 $a[i]$ 能够使得 $f[i-1] + g[i+1] > ans$ 的时候，说明删除元素 $a[i]$ 达到了增长最长上升子串的效果，此时我们更新 $ans = f[i-1] + g[i+1]$ 。  

综上所述，答案应该是  
- $\max(f[i])$ （其中 $(1 \le i \le n)$）  
和  
- $\max(f[i-1]+g[i+1])$ （其中 $1 \lt i \lt n$）

的较大值。

实现代码如下：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200020;
int n, a[maxn], f[maxn], g[maxn], ans;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    f[1] = 1;
    for (int i = 2; i <= n; i ++) {
        if (a[i-1] < a[i]) f[i] = f[i-1]+1;
        else f[i] = 1;
    }
    g[n] = 1;
    for (int i = n-1; i >= 1; i --) {
        if (a[i] < a[i+1]) g[i] = g[i+1]+1;
        else g[i] = 1;
    }
    for (int i = 1; i <= n; i ++) ans = max(ans, f[i]);
    for (int i = 2; i < n; i ++) if (a[i-1] < a[i+1]) ans = max(ans, f[i-1] + g[i+1]);
    cout << ans << endl;
    return 0;
}
```



---

## 作者：_6_awa (赞：1)

题目大意：一个数组，现在可以删去一个数，求操作后最长连续子序列的长度

题目分析：我们发现，结果是肯定会从上一个数或者上两个数的状态继承过来的，所以一眼想到动态规划。

这里的状态有三种，一种是还未进行删数，一种是刚刚进行删数，一种是删完数。这里把后面两种当作一种来算（这一步后已经用过了删数的机会）。

怎么继承呢？很简单。当还未进行删数时，只能从上一步的“未进行删数的状态”继承过来，如果能连上就加上一，不能连上直接从头开始（即直接变成 $1$）。最后是已经删完数的状态。这里分两种，一种是现在进行删数，就可以跳越过上一个数直接继承前两个数的未删数的状态；那如果删完数就和未删数的情况一样了，从上一步中删完数的那一步进行继承。到底选哪一种呢？因为如果情况连续的越大对后面的结果就越有利，所以可以取 $\max$ 进行选择。

最后就是结果了。直接在这些数组中间选一个最大值即可。易错点，切记不要直接选择最后一个的状态，因为最长连续子序列可能没有到最后一个数！！

### AC Code:

```cpp
#include <iostream>
using namespace std;
int n,dp[200005][4],a[299999],ans;
int main()
{
    cin >> n;
    for(int i = 1;i <= n;i ++)cin >> a[i];
    for(int i = 1;i <= n;i ++)
    {
        if(a[i - 1] < a[i])dp[i][0] = dp[i - 1][0] + 1;
        else dp[i][0] = 1;//未进行删数
        if(a[i - 1] < a[i])dp[i][1] = dp[i - 1][1] + 1;
        else dp[i][1] = 1;//已经删过数
        if(i >= 3 && a[i - 2] < a[i])dp[i][1] = max(dp[i][1],dp[i - 2][0] + 1);//这一步进行删数。这里注意越界问题。
        ans = max(ans,max(dp[i][0],dp[i][1]));//结果对它们取max
    }
    cout << ans;//完美输出
}

---

## 作者：BYWYR (赞：1)

## $\texttt{Solution}$

一道简单的线性动态规划题。

定义状态 $dp_i$ 表示到第 $i$ 个数时并且包含 $a_i$ 的最大上升子序列和。

从头到尾扫一遍，从尾到头扫一遍，那么动态转移方程就是：

- 正着扫：

```cpp
if(a[i-1]<a[i]) 
	dp1[i]=dp1[i-1]+1;
else dp1[i]=1;
```

- 倒着扫：

```cpp
if(a[i+1]>a[i]) 
	dp2[i]=dp2[i+1]+1;
else dp2[i]=1;    
```



------------

但这显然没有解决题目中可以删除一个数的问题。

仔细思考一下，其实我们可以枚举删除第 $i$ 个数，只要满足 $a_{i-1}<a_{i+1}$，那么以第 $i-1$ 个数结尾的最大上升子序列就可以跟以第 $i+1$ 个数结尾的最大上升子序列接起来，从而得到更大长度的最大上升子序列。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[200005],dp1[200005],dp2[200005];
int ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i-1]<a[i]) 
			dp1[i]=dp1[i-1]+1;
		else dp1[i]=1;
	}//正着扫
	for(int i=n;i>=1;i--){
		if(a[i+1]>a[i]) 
			dp2[i]=dp2[i+1]+1;
		else dp2[i]=1; 
	}//正着扫
	for(int i=1;i<=n;i++){
		if(a[i-1]<a[i+1]) //如果第i-1个数比第i+1个数小，那么这两段最大上升子序列就可以接起来
			ans=max(ans,dp1[i-1]+dp2[i+1]);//记录答案
		ans=max(ans,max(dp1[i],dp2[i]));//不删除数，与答案进行比较
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：小恐 (赞：1)

一看就是一个动态规划问题。

可以设$dp_{i,j}$为以第$i$个数为结尾删掉$j$个数的最长连续上升子序列的长度。

设给定序列为$a$。

转移：
1. $j=0$且$a_i>a_{i-1}$时，$dp_{i,j}=dp_{i-1,j}+1$

2. $j=0$且$a_i\le a_{i-1}$时，$dp_{i,j}=1$

3. $j=1$且$a_i>a_{i-1}$时，$dp_{i,j}=dp_{i-1,j}+1$

4. $j=1$且$a_i\le a_{i-1}$时，$dp_{i,j}=1$

3. $j=1$且$a_i>a_{i-2}$时，$dp_{i,j}=\max(dp_{i,j},dp_{i-2,j-1}+1)$

由于对于每个$i$，下标要处理到$i-2$，方便起见给定序列为$a_i(2\le i\le n+1)$。

上代码：
```cpp
#include<stdio.h>
#include<iostream>
#define MAXN 200005
using namespace std;
int dp[MAXN][2],a[MAXN];
int ans;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=2;i<=n+1;++i)
		scanf("%d",a+i);
	for(int i=2;i<=n+1;++i)
	{
		if(a[i]>a[i-1])
			dp[i][0]=dp[i-1][0]+1;
		else
			dp[i][0]=1;
		if(a[i]>a[i-1])
			dp[i][1]=dp[i-1][1]+1;
		else
			dp[i][1]=1;
		if(a[i]>a[i-2])
		dp[i][1]=max(dp[i][1],dp[i-2][0]+1);
		ans=max(ans,dp[i][0]);
		ans=max(ans,dp[i][1]);
	}
	printf("%d",ans);
	return 0;
}
```
感谢阅读！

~~点个赞再走呗~~

---

## 作者：AmamiyaYuuko (赞：1)

这道题相当于是求一个可以删除一个元素的最长连续上升子序列长度。

那么我们只需要维护原序列中以当前位置结尾的最长连续上升子序列长度和以当前位置开始的最长连续上升子序列长度，然后从 $1$ 到 $n$ 枚举每一个点，更新答案即可。

设当前位置是 $i$，那么只有当 $a_i < a_{i + 2}$ 时才可以更新，这就等于是删除了第 $i + 1$ 个元素后的答案。

求出以当前位置结尾的最长连续上升子序列长度和以当前位置开始的最长连续上升子序列长度也很简单，设 $f_i$ 表示以第 $i$ 个元素结尾的最长连续上升子序列长度，$g_i$ 表示以第 $i$ 个元素开头的最大连续上升字序列长度。

那么：

```cpp
f[1] = g[n] = 1;
for (int i = 2; i <= n; ++i)
{
    if (a[i] > a[i - 1])    
    	f[i] = f[i - 1] + 1;
    else    
    	f[i] = 1;
}
for (int i = n - 1; i >= 1; --i)
{
    if (a[i] < a[i + 1])    
    	g[i] = g[i + 1] + 1;
    else
    	g[i] = 1;
}
```

就可以求出 $f$ 和 $g$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

int a[200010], f1[200010], f2[200010];
int n, ans = 1;

int main()
{
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    f1[1] = f2[n] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (a[i] > a[i - 1])    f1[i] = f1[i - 1] + 1;
        else    f1[i] = 1;
        ans = std::max(ans, f1[i]);
    }
    for (int i = n - 1; i >= 1; --i)
    {
        if (a[i] < a[i + 1])    f2[i] = f2[i + 1] + 1;
        else    f2[i] = 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] < a[i + 2])
            ans = std::max(f1[i] + f2[i + 2], ans);
    }  
    std::cout << ans << std::endl;
    return 0;
}
```

---

## 作者：Crasole (赞：0)

## 思路

一道线性 dp 题，首先我们先求出两个东西：

- 以 $i$ 为结尾的最长子串的长度。

- 以 $i$ 为起点的最长子串的长度。

我们令 $dpw_i$ 表示以 $i$ 为结尾的最长子串的长度，有两种情况：

- $a_i > a_{i - 1}$，能接上，$dpw_i = dpw_{i - 1} + 1$。

- $a_i \le a_{i - 1}$，接不上，$dpw_i = 1$。

我们令 $dpq_i$ 表示以 $i$ 为起点的最长子串的长度，有两种情况：

- $a_{i + 1} > a_i$，能接上，$dpq_i = dpq_{i + 1} + 1$。

- $a_{i + 1} \le a_i$，接不上，$dpq_i = 1$。

接着我们再枚举删除的数，如果 $a_{i - 1} < a_{i + 1}$，那么说明删掉 $a_i$ 这个数后能产生更长的子串，这个新串的长度就是 $dpw_{i - 1} + dpq_{i + 1}$。也有可能不删除 $a_i$ 的长度更长，那么答案就是 $dpw_i$ 和 $dpq_i$ 的最大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], dpw[N], dpq[N];
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	dpw[1] = 1;
	for(int i = 1; i <= n; i++)
		if(a[i] > a[i - 1]) dpw[i] = dpw[i - 1] + 1;
		else dpw[i] = 1;
	dpq[n] = 1;
	for(int i = n; i >= 1; i--)
		if(a[i + 1] > a[i]) dpq[i] = dpq[i + 1] + 1;
		else dpq[i] = 1; 
   //求出 dpw[i] 和 dpq[i]
	int ans = 0;
	for(int i = 1; i <= n; i++){
		if(a[i - 1] < a[i + 1])
			ans = max(ans, dpw[i - 1] + dpq[i + 1]);
		ans = max(ans, max(dpw[i], dpq[i]));
		//统计答案
   }	
   cout << ans;
}
```

---

## 作者：Erotate (赞：0)

在此提供一种不用动态规划的做法，时间复杂度也为 $O(n)$。

我们首先预处理出原来的序列里所有的连续上升子序列，并用数组记录每一个个元素属于哪个连续上升子序列。然后我们想想如何才能在删除一个元素的情况下创造出一个新的连续上升子序列。

显然，对于元素 $a_i$，当且仅当 $a_{i-1} < a_{i+1}$ 时,删除 $a_i$ 才能创造出一个新的连续上升子序列。

那么 $a_i,a_{i-1},a_{i+1}$，的关系有哪些呢？

1. $a_i$ 和 $a_{i-1}$ 属于同一个连续上升子序列，但 $a_i$ 和 $a_{i+1}$ 不属于同一个连续上升子序列。

2. $a_i$ 和 $a_{i+1}$ 属于同一个连续上升子序列，但 $a_i$ 和 $a_{i-1}$ 不属于同一个连续上升子序列。

3. $a_i$ 和 $a_{i-1}$ 不属于同一个连续上升子序列，$a_i$ 和 $a_{i+1}$ 也不属于同一个连续上升子序列。

3. $a_{i-1},a_i,a_{i+1}$ 都在同一个连续上升子序列里。

令 $bl_i$ 表示第 $i$ 个元素所属的连续上升子序列，$len_i$ 表示第 $i$ 个连续上升子序列的长度。

于是，分类讨论：

对于情况 1，新的连续上升子序列的长度为 $len_{bl_i}+len_{bl_{i+1}}-1$。

对于情况 2，新的连续上升子序列的长度为 $len_{bl_i}+len_{bl_{i-1}}-1$。

对于情况 3，新的连续上升子序列的长度为 $len_{bl_{i-1}}+len_{bl_{i+1}}$。

对于情况 4，新的连续上升子序列的长度为 $len_{bl_i}-1$。

那么，我们只需要枚举每一个元素，然后按照上面的结论分类讨论即可。

放个代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],bl[N],len[N],cnt=1,ans;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]>a[i-1]){
			bl[i]=cnt;
			len[cnt]++;
		}else{
			cnt++;
			ans=max(ans,len[cnt-1]);
			bl[i]=cnt;
			len[cnt]++;
		}
	}
	ans=max(ans,len[cnt]);
	if(ans==n){
		printf("%d",n);
		return 0;
	}
	for(int i=1;i<=n;++i){
		if(a[i-1]<a[i+1]){
			if(bl[i]==bl[i-1] && bl[i]!=bl[i+1]) ans=max(ans,len[bl[i]]+len[bl[i+1]]-1);
			else if(bl[i]==bl[i+1] && bl[i]!=bl[i-1]) ans=max(ans,len[bl[i]]+len[bl[i-1]]-1);
			else if(bl[i]!=bl[i+1] && bl[i]!=bl[i-1]) ans=max(ans,len[bl[i-1]]+len[bl[i+1]]);
			else ans=max(len[bl[i]]-1,ans);
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：0)

## 提示

这里的要求“最长连续上升子序列”指的的是最长上升子段！

## 思路

这道题要求的是 **至多** 删除一个。那么先考虑删除一个的情况。

假设删除 $i$ 位置，相当于把以 $i-1$ 为结尾的最长上升子段与以 $i+1$ 为开头的最长上升子段连了起来。所以我们用 $pre_i$ 表示以 $i$ 为开始的最长上升子段，$suf_i$ 表示以 $i$ 为结尾的最长上升子段。然后按照最长上升的子段推导就行了：

$pre_i$ 需要正推：若 $a_i \leq a_{i-1}$ 那么 $pre_i = 1$，否则 $pre_i = pre_{i-1} + 1$。

$suf_i$ 需要倒推：若 $a_i \geq a_{i+1}$ 那么 $suf_i = 1$，否则 $suf_i = suf_{i+1} + 1$。

最后，我们统计答案：

- 第一种是什么也不去掉，即对所有的 $pre_i$ 取 $\max$。

- 第二种是去掉一个：枚举删掉哪一个 $i$，当前答案就是 $suf_{i-1} + pre_{i+1}$，然后对所有的值取 $\max$。注意这个时候要保证 $a_{i-1} < a_{i+1}$。

最后输出答案即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005],pre[200005],suf[200005];
int main()
{
	int n; cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		if(a[i]>a[i-1]) suf[i]=suf[i-1]+1;
		else suf[i]=1;
	for(int i=n;i>=1;i--)
		if(a[i]<a[i+1]) pre[i]=pre[i+1]+1;
		else pre[i]=1;
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,pre[i]); // 不删去
	for(int i=1;i<=n;i++)
		if(a[i-1]<a[i+1]) ans=max(ans,suf[i-1]+pre[i+1]); // 删去一个数
	cout<<ans; // 答案
	return 0;
}
```

---

