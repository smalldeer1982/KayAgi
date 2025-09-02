# Fence

## 题目描述

There is a fence in front of Polycarpus's home. The fence consists of $ n $ planks of the same width which go one after another from left to right. The height of the $ i $ -th plank is $ h_{i} $ meters, distinct planks can have distinct heights.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF363B/89891f9a8aa0dbd268db12cc4f373a8fc8629b6b.png)Fence for $ n=7 $ and $ h=[1,2,6,1,1,7,1] $ Polycarpus has bought a posh piano and is thinking about how to get it into the house. In order to carry out his plan, he needs to take exactly $ k $ consecutive planks from the fence. Higher planks are harder to tear off the fence, so Polycarpus wants to find such $ k $ consecutive planks that the sum of their heights is minimal possible.

Write the program that finds the indexes of $ k $ consecutive planks with minimal total height. Pay attention, the fence is not around Polycarpus's home, it is in front of home (in other words, the fence isn't cyclic).

## 说明/提示

In the sample, your task is to find three consecutive planks with the minimum sum of heights. In the given case three planks with indexes 3, 4 and 5 have the required attribute, their total height is 8.

## 样例 #1

### 输入

```
7 3
1 2 6 1 1 7 1
```

### 输出

```
3
```

# 题解

## 作者：L_zaa_L (赞：6)

## 分析
首先暴力肯定不行（因为时间复杂度为 $O(nk)$），看到了区间和，我就可以明白了：只要找到最小就行了。后来研究了一下，发现由 $[i,i+k-1]$ 变为 $[i+1,i+k]$ 只需加上 $a_{i+k}$,再减去 $a_{i}$。于是我们可以用两个数来储存 $i$ 与 $i+k$（就简称头和尾了），当遇到区间和小的时候，记录开头就可以了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1500005],minn=INT_MAX,x;
int main(){
	int n,m;
	cin>>n>>m;
	int h=1,t=m,qjh=0;//h 为头，t 为尾
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) qjh+=a[i];//给区间和定初值 
	while(t<=n){
		if(qjh<minn){
			minn=qjh;//求最小的区间和 
			x=h;//记录起始位置 
		}
		qjh-=a[h]; 
		t++;
		h++;
		qjh+=a[t];//向后推进 
	}
	cout<<x;
	return 0;
} 
```



---

## 作者：_JF_ (赞：4)

## CF363B Fence

**思路：模拟+前缀和**

前缀和简单介绍：

设 $sum[i]$ 表示前 $i$ 个数的和，就有：

```
sum[i]=sum[i-1]+a[i]
```
其中 $a[i]$ 表示输入的数据。

所以在前缀和的基础上，这个题就十分简单了。

我们从 $m$ 开始枚举（节省时间），依次枚举长度为 $m$ 的所有区间的和即可。

而在判断的时候要注意，我们算的是 $[i-m+1,i]$ 的和，所以根据前缀和，我们判断的应该是

```
sum[i]-sum[i-m]
```

最后要注意 $Minn$ 的值一定要大！


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1500005],sum[1500005];
signed main()
{
	int x;
	int minn=INT_MAX;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i],sum[i]=sum[i-1]+a[i];
	for(int i=m;i<=n;i++)
	{
		if(sum[i]-sum[i-m]<minn)
			minn=sum[i]-sum[i-m],x=i-m+1;
	}
	cout<<x<<endl;
}
```




---

## 作者：Fozz_1024 (赞：0)

## 思路

数据范围告诉我们，朴素的暴力是肯定会超时的。

所以我们要使用~~优雅的暴力~~ —— **前缀和**。

前缀和简单介绍：

我用 $ sum[i] $ 数组记录数列 $a$ 第 $1$ 项至第 $i$ 项的和，即：

```cpp
sum[i]=a[1]+a[2]+...+a[i]
```

如果设子区间的左端点下标为 $l$，右端点下标为 $r$ 则有：


```cpp
sum[l]=a[1]+a[2]+...+a[l]
sum[l]=a[1]+a[2]+...+a[l-1]+a[l]+...+a[r]
```

则第 $l$ 项至 $r$ 项的和可以表示为：

```cpp
a[l]+a[l+1]+...+a[r]=sum[r]-sum[l-1]
```

这样查询子区间和的时间复杂度就可以降为 $ O(1)$ 。

因为在本题中区间长度固定为 $k$，所以我们只需枚举区间起点 $l$ 即可，右端点下标则可以用 $l+k-1$ 表示。


## ACcode
```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int ans,n,k,num,sum[1000100],minn=1e9;

int main()
{
	scanf ("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
	{
		scanf ("%d",&num);
	    sum[i]=sum[i-1]+num;//前缀和预处理 
	}
	for (int i=1;i<=n-k+1;i++)//枚举区间起点 ，注意循环结束条件 
	{
		if(sum[i+k-1]-sum[i-1]<minn)//O(1)求出区间和并进行比较 
		{
			ans=i;//更新答案 
			minn=sum[i+k-1]-sum[i-1];//更新最小值 
		}
	}
	
	printf("%d",ans);
	
	return 0;
}
```


---

## 作者：正负君 (赞：0)


# CF363B Fence 题解

## 思路

一看到“区间”就可以立马想到**前缀和**。  

前缀和可以简单理解为「数列的前项的和」，是一种重要的预处理方式，能大大降低查询的时间复杂度。  
C++ 标准库中实现了前缀和函数 [std::partial_sum](https://zh.cppreference.com/w/cpp/algorithm/partial_sum)，定义于头文件  `<numeric>` 中。

设 $partial$ 为前缀和数组，那么 $partial_2=h_1+h_2$，同理可得 $partial_n=h_1+h_2+h_3+ \cdots +h_{n-1}+h_n$。

如果我们想求 $h_x+h_{x+1}+ \cdots +h_{y-1}+h_y$ 的值，我们只需要求出 $partial_y-partial_{x-1}$ 即可。

剩下的就简单了，直接枚举即可，建立 $min$，表示遍历到现在**区间和**最小的；建立 $ans$，表示区间和最小的**起始位置**。

## 代码

接下来放出~~你们最爱的完整~~代码：    

我们需要把 $min$ 初始化为 $\infty$（$2^{31}-1$）。

我们为了~~节省空间~~，所以把 $h$ 数组和前缀和**合并成**一个数组。

记得要把 $h_0$ 初始化为 $0$ 因为不初始化为 $0$ 的话，第一次 for 循环会出现垃圾数据！

注意如果找到比当前更小的区间和， $ans$ 值要设为 $i-j+1$，注意 $1$ 这个偏移量。

```cpp
#include<iostream>
using namespace std;
int n,k,ans;
int main()
{
  cin>>n>>k;
  int min=2147483647;
  int h[n+1];
  h[0]=0;        //h[0] 初始化
  for(int i=1; i<=n; i++)
  {
    cin>>h[i];
    h[i]+=h[i-1];//前缀和
  }
  for(int i=k; i<=n; i++)
  {              //枚举
    if(h[i]-h[i-k]<min)
    {
      min=h[i]-h[i-k];
      ans=i-k+1;  
    }
  }
  cout<<ans<<endl;
  return 0;     //完美地结束啦！
}
```

希望这篇题解对你有帮助。

---

## 作者：Fr0sTy (赞：0)

### 题意简述
------------
给定一个长为 $n$ 的序列，要求截取一段长度为 $k$ 的连续子序列，使这段子序列的和最小。

### 解题思路
------------
如果每次都去枚举这个数之后 $k$ 个数的和再进行比较，那么时间复杂度就会飙升到 $O(n^2)$。

数据要求 $1 \leqslant n \leqslant 1.5 \times 10^5$，肯定过不了。

所以可以想到用**前缀和**优化。

这里用一维数组前缀和，具体代码如下：
``` cpp
for(int i=1;i<=n;i++) scanf("%d",&sum[i]);
for(int i=1;i<=n;i++) sum[i]+=sum[i-1];
```
这里的 $sum$ 数组就表示前缀和。这里也用 $sum$ 数组来输入。

那么区间的和就可以表示为 $sum_{i+k-1} - sum_{i-1}$ 。

即 `sum[i+k-1]-sum[i-1]`。

如果这个区间和小于目前最小值 $minn$，那么将 $minn$ 更新。

### 代码实现
------------
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sum[1000005],minn=INT_MAX,ans=INT_MIN;
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&sum[i]);
	for(int i=1;i<=n;i++) sum[i]+=sum[i-1];
	for(int i=1;i<=n-k+1;i++) {
		if(sum[i+k-1]-sum[i-1]<minn) {
			minn=sum[i+k-1]-sum[i-1];
			ans=i;
		}
	}
	if(k==n) printf("1");
	else printf("%d",ans);
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：0)

直接暴力枚举每一个区间和显然会超时。

考虑用前缀和优化暴力。

每次枚举区间的右端点，通过题目给出的 $k$ 计算区间的左端点，然后用前缀和计算出区间和，与当前最小区间和比较并更新最小区间和以及最小区间的左端点（起始位置）。

$Code$:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001],k,ans=2147483647,x;
//ans记录当前区间和的最小值,x记录该区间的左端点(即起始位置)
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i],a[i]+=a[i-1];//前缀和
    for(int i=k;i<=n;i++)
        if(a[i]-a[i-k]<ans) 
            ans=a[i]-a[i-k],x=i-k+1;//前缀和计算区间和
            //i为区间右端点,i-k+1为区间左端点
    cout<<x;
    return 0;
}

---

## 作者：formkiller (赞：0)

估计是道div.3的送分题

稍加思索就可以得出，$[i,i+k-1]$和$[i+1,i+k]$这两段区间的区间和的公共部分为$[i+1,i+k-1]$，他们的唯一的差别就在$a_i$和$a_{i+k}$

既然如此,如果我们已经知道了$[i,i+k-1]$的区间和，只需将减去$a_i$即得到了$[i+1,i+k-1]$，再加上$a_{i+k}$就得到了$[i+1,i+k]$的区间和，同时更新答案即可

对于初始的$[1,k]$只需要暴力求出即可

## **Code**
```
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

#define LL long long
#define is(a) (a>='0'&&a<='9')

using namespace std;

int N,k,a[(int)4e5+50],ans;

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	read(N); read(k);
	for (int i = 1; i <= N; ++i) read(a[i]),a[i]+=a[i-1];
	ans=1;
	for (int i = 2; i <= N-k+1; ++i) 
		if (a[i+k-1]-a[i-1]<a[ans+k-1]-a[ans-1]) ans=i;
	cout << ans << endl;
	return 0;
}
```




---

