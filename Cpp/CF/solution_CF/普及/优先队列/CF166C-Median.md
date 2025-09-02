# Median

## 题目描述

A median in an array with the length of $ n $ is an element which occupies position number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/a3cce6c26f6207c41846eedd0e6a59cdcc521015.png) after we sort the elements in the non-decreasing order (the array elements are numbered starting with $ 1 $ ). A median of an array $ (2,6,1,2,3) $ is the number $ 2 $ , and a median of array $ (0,96,17,23) $ — the number $ 17 $ .

We define an expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/ff48225f7f772c08409f2d464b02c44cf20620e2.png) as the integer part of dividing number $ a $ by number $ b $ .

One day Vasya showed Petya an array consisting of $ n $ integers and suggested finding the array's median. Petya didn't even look at the array and said that it equals $ x $ . Petya is a very honest boy, so he decided to add several numbers to the given array so that the median of the resulting array would be equal to $ x $ .

Petya can add any integers from $ 1 $ to $ 10^{5} $ to the array, including the same numbers. Of course, he can add nothing to the array. If a number is added multiple times, then we should consider it the number of times it occurs. It is not allowed to delete of change initial numbers of the array.

While Petya is busy distracting Vasya, your task is to find the minimum number of elements he will need.

## 说明/提示

In the first sample we can add number $ 9 $ to array $ (10,20,30) $ . The resulting array $ (9,10,20,30) $ will have a median in position ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/087e5fa70c281cf5e7b5f392e766cd46089615e4.png), that is, $ 10 $ .

In the second sample you should add numbers $ 4 $ , $ 5 $ , $ 5 $ , $ 5 $ . The resulting array has median equal to $ 4 $ .

## 样例 #1

### 输入

```
3 10
10 20 30
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 4
1 2 3
```

### 输出

```
4
```

# 题解

## 作者：飞啾6373 (赞：2)

### 题意

给你一个序列和一个数，要求你在序列里加入一些数（越少越好），是给你的目标数成为该序列中的中位数。

求最少需要加入多少个数才能满足要求。

### 思路

思路很简单：只要先将序列从小到大排序，再判断序列中每一个等于目标中位数的变量最少需要增加几个数才能变为中位数，记录它们中的最小值即可。

小提示：由于题目中并没有说序列里是否包含目标中位数，因此需要判断一下。

### 代码

↓精华都在注释里啦

```
#include<bits/stdc++.h>
using namespace std;
int a[784];//n<=500,完全够用 
int main()
{
	int n,i,k,qwq=0,ans=0,q=2048;
	//ans存储最少需要增加数的个数 
	cin>>n>>k;//输入总数和目标中位数 
	for(i=1;i<=n;i++)
	{
		cin>>a[i];//输入序列中的每一个数 
		if(a[i]==k)qwq=1;//判断是否含有目标中位数，以变量qwq记录 
	}
	if(qwq==0)
	{
		n++;
		a[n]=k;
		ans=1;
		//如果序列中不含目标中位数，那么需要手动加入进去，更新ans 
	}
	sort(a+1,a+n+1);//从小到大排序 
	for(i=1;i<=n;i++)
	{
		if(a[i]==k)//如果枚举到的a[i]等于目标中位数，则更新最优答案
		{
			int x;
			x=abs((i-1)-(n-i));
			if(i-1<n-i)x--;
			q=min(q,x);
		}
		else if(a[i]>k)break;//如果当前的a[i]超过了目标中位数k，立即跳出循环以节省时间 
	}
	ans+=q;
	cout<<ans;//输出答案
	return 0;
}
```


---

## 作者：Lucifer_Bartholomew (赞：2)

# ~~枚举中间值~~
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[510];
int main()
{
	int n,k;
    scanf("%d%d",&n,&k);
    int tmp,ans=0;
    for(int i=0;i<n;++i)
		scanf("%d",&a[i]);
    sort(a,a+n);
    int l=lower_bound(a,a+n,k)-a,r=upper_bound(a,a+n,k)-a;
    int mid=(n-1)>>1;
    while(mid<l||mid>=r)
	{
        ++ans;
        ++r;
        mid=(++n-1)>>1;
    }
    printf("%d\n", ans);
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：TheSky233 (赞：1)

## Description

有 $n$ 个数，求出至少要添加几个数使得 $k$ 为整个序列的中位数。

## Analysis

### Lemma

- 直接往序列中添加 $k$ 是不劣的。

### Proof

1. 当序列中没有 $k$ 时，显然要添加 $k$。
2. 如果添加比 $k$ 小的，就相当于往连续一段 $k$ 的区间的最前面插入一个 $k$。
3. 如果添加比 $k$ 大的，就相当于往连续一段 $k$ 的区间的最后面插入一个 $k$。

### Solution

首先中位数要求序列有序，于是先使序列有序。

然后我们注意到极小的 $n$ 的范围：$1 \le n \le 500$，于是直接模拟插入，连续插入 $k$ 直至 $k$ 为中位数即可。

这里用的是 `std::vector` 来模拟插入过程，码量极少。

时间复杂度为 $\Theta(n^2)$，最劣情况为 $k < \min\{a_i\}$。

## Code

```cpp
int n,m,q,k,p=INT_MAX;
int a[N],b[N],f[N];
vector<int> v;

int median(){
    return v.at(v.size()/2);
}

void Solve(){
    v.pb(0);
    read(n,k);
    F(i,1,n) read(q),v.pb(q);
    sort(v.begin(),v.end());
    while(median()!=k) v.insert(lower_bound(v.begin(), v.end(), k), k);
    write(v.size()-n-1);
}
```

---

## 作者：shenbairui (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF166C)

### 题目大意

题目讲得很清楚了吧：有 $n$ 个数，加入几个数（越少越好），使得中位数为 $k$ 。

### 题目分析

先将序列从小到大排序，再判断序列中每一个等于目标中位数的变量最少需要增加几个数才能变为中位数，在记录最小值即可。但是你以为这就完了吗？
由于题目中并没有说序列里是否包含目标中位数，因此要特判。

### 代码实现！

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505],n,k,s,ans,q=2048;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==k) s=1;
	}
	if(s==0){//特判
		n++;
		a[n]=k;
		ans=1;
	}
	sort(a+1,a+n+1);//排序
	for(int i=1;i<=n;i++){//找中位数
		if(a[i]==k){
			int x;x=abs((i-1)-(n-i));
			if(i-1<n-i) x--;
			q=min(q,x);
		}
		else if(a[i]>k) break; 
	}
	ans+=q;
	cout<<ans;
	return 0;//好习惯
}
```

拜拜！下期见！

---

## 作者：cachejtt (赞：0)

### 题意
有 $n$ 个数，问向序列中最少加入几个数，才能使得中位数为 $k$。

$1 \le n \le 500,1 \le x \le 10^5$

### 思路
我们知道：一个数在数列的哪个位置，仅跟比它小的数的个数、等于它的数的个数与大于它的数的个数有关。我们设 $big$ 为序列中大于 $k$ 的数的个数；$small$ 为序列中小于 $k$ 的数的个数；$equal$ 为序列中等于 $k$ 的数的个数。

首先判断：当前的中位数是不是 $k$，如果是的话直接输出 $0$。

然后分为两种情况：

1. 当前的 $k$ 在数列里太小了，需要在前面加数
1. 当前的 $k$ 在数列里太大了，需要在后面加数

#### 第一种情况：

在序列前加上 $big-(small+equal)$ 个比 $k$ 小的数即可。

这时数列中位数前有 $small+equal-1+big-(small+equal)=big-1$个数；中位数后有 $big$ 个数，则 $k$ 即为中位数。

#### 第二种情况：

在序列后加上 $small-(big+equal)+1$ 个比 $k$ 大的数即可。

这时数列中位数前有 $small$ 个数；中位数后有 $big+equal-1+small-(big+equal)+1=small$ 个数，则 $k$ 为中位数。


由于这两种情况不可能同时成立，必有其中一个答案是负数，所以只需要输出时两个式子取一个最大值即可。

### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stack>
#include<cstdio>
#include<cmath>
#define rep(i, a, b) for (long long i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (long long i = (a); i >= (b); --i)
#define ll long long
using namespace std;
int n,k;
int a;
int big,small,equa;
int main(){
  std::ios::sync_with_stdio(0);
  cin>>n>>k;
  rep(i,1,n){
    cin>>a;
    if(a==k)equa++;
    if(a>k)big++;
    if(a<k)small++;
  }
  if(small+equa>=(n+1)/2 && small<(n+1)/2){//判断中位数是否被覆盖
    cout<<0<<endl;
    return 0;
  }
  else{
    cout<<max( big-(small+equa) , small-(big+equa-1))<<endl;
    return 0;
  }
  return 0;
}
```

---

## 作者：Edmundino (赞：0)

# 题意

给你 $n$ 个数，和一个 $k$，问你至少加多少个数，

使得 $k$ 为这 $n$  个数的中位数。

# 分析

这题我用了比较多的分类讨论。

第一个讨论是 $k $ 是否在这 $n $ 个数中。

如果不在， 在讨论：

当 $k$ 比最大的数大，那输出 $n+1$，

比最小的小 ，就输出 $n$。

我们要两个数 ：一个 $l$ 为 第一个大于或等于 $k$ 的数字的位置、

第二个数 $r$ 为第一个大于 $k$ 的数字的位置。

如果 $l==r$ 那说明 $k$ 不在此，要多花一步把 $k$ 加上。


现在判断这个数左边的数的个数和右边的个数差的绝对值。（已排好序）

但是还要注意： 如果右边的个数比左边的个数多， 那么你得到的绝对值还需要在减去一。


# 代码

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>

using namespace std;

const int N=500+50;

int n,k,a[N],s,l,r;

inline int read()
{
   int x=0,k=1;char c=getchar();
   while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
   while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
   return x*k;
}


int main()
{
   n=read();k=read();
   for(int i=1;i<=n;i++)
   {
      a[i]=read();
   }
   sort(a+1,a+1+n);
  l=lower_bound(a+1,a+n+1,k)-a;
  r=upper_bound(a+1,a+n+1,k)-a;
  if(l>n)
  {
    cout<<n+1;
    return 0;
  }
  if(r==1)
  {
     cout<<n;
     return 0;
  }
  int minx=9999999;
  for(int i=l;i<r;i++)
  {
     if((n-i)>(i-1)){minx=min(minx,(abs((n-i)-(i-1)))-1);}
     else{minx=min(minx,abs((n-i)-(i-1)));}
  }
  if(minx!=9999999)
  {
    cout<<minx;
    return 0;
  }
    int c = 1;
    l=r;
    n++;
    int id=(n-l)>(l-1);
    cout<<abs((n-l)-(l-1))+c-id;
}
```


---

