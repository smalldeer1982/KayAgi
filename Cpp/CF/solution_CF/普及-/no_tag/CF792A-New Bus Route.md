# New Bus Route

## 题目描述

There are $ n $ cities situated along the main road of Berland. Cities are represented by their coordinates — integer numbers $ a_{1},a_{2},...,a_{n} $ . All coordinates are pairwise distinct.

It is possible to get from one city to another only by bus. But all buses and roads are very old, so the Minister of Transport decided to build a new bus route. The Minister doesn't want to spend large amounts of money — he wants to choose two cities in such a way that the distance between them is minimal possible. The distance between two cities is equal to the absolute value of the difference between their coordinates.

It is possible that there are multiple pairs of cities with minimal possible distance, so the Minister wants to know the quantity of such pairs.

Your task is to write a program that will calculate the minimal possible distance between two pairs of cities and the quantity of pairs which have this distance.

## 说明/提示

In the first example the distance between the first city and the fourth city is $ |4-6|=2 $ , and it is the only pair with this distance.

## 样例 #1

### 输入

```
4
6 -3 0 4
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
3
-2 0 2
```

### 输出

```
2 2
```

# 题解

## 作者：小恐 (赞：1)

一道大~~水~~题

先写一个暴力代码，就是枚举每两个数是否为最小值
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXN 200005
#define INF 0x7fffffff  //就是2147483647，int最大值 
using namespace std;
int a[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	int minn=INF;//最小值初始化要设成最大 
	int cnt=0;
	for(int i=1;i<n;++i)
		for(int j=i+1;j<=n;++j)
			if(abs(a[i]-a[j])==minn)//与当前最小值一样 
				++cnt;//个数增加1 
			else if(abs(a[i]-a[j])<minn)//比当前最小值还小 
				cnt=1,minn=abs(a[i]-a[j]);//更新最小值，个数为1（就是这对） 
	printf("%d %d\n",minn,cnt); 
	return 0;
}
```
完美TLE掉！（[TLE地址](https://www.luogu.com.cn/record/30093639)）

于是气愤地想到了应该先排个序，最小值肯定在相邻的两个数之间

由于懒得写快排（~~不会写~~）于是c++的福利sort来了

AC代码：
```cpp
#include<stdio.h>
#include<algorithm> //sort要用 
#define MAXN 200005
#define INF 0x7fffffff  //就是2147483647，int最大值 
using namespace std;
int a[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	int minn=INF;//最小值初始化要设成最大 
	int cnt=0;
	sort(a+1,a+1+n);//c++福利
	for(int i=1;i<n;++i)
		if(minn==a[i+1]-a[i])//与当前最小值一样 
			++cnt;//个数增加1 
		else if(minn>a[i+1]-a[i])//比当前最小值还小 
			cnt=1,minn=a[i+1]-a[i];//更新最小值，个数为1（就是这对）
	printf("%d %d\n",minn,cnt); 
	return 0;
}
```
终于AC了（[AC地址](https://www.luogu.com.cn/record/30094291)）

~~本蒟蒻第二篇题解，求过~~

---

## 作者：Irrigate (赞：0)

### **读题：**
给定n个整数，选出两个数，使得它们差的绝对值最小，输出这个绝对值，并输出差的绝对值是这个数的数对个数.


------------

### **思路：**
因为要差的绝对值最小，所以先排序，排完后计算相邻两个数的差，打擂台找出最小值，然后再次循环找出数对个数，输出即可。


------------

### **变量表示：**
整数的个数用 n表示，整数用 a数组读入,min表示最小的绝对值,cnt是数对个数。


------------

### **上代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100000];
int main()
{
    int n,cnt=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    int min=a[2]-a[1];
    for(int i=2;i<n;i++)
        if(a[i+1]-a[i]<min)
            min=a[i+1]-a[i];
    cout<<min<<" ";
    for(int i=1;i<n;i++)
        if(a[i+1]-a[i]==min)
            cnt++;
    cout<<cnt;
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n$ 的数列 $a_1,a_2,a_3,...,a_n$，求这个序列当中差的绝对值最小的数对并求出这样的数对的个数。

**数据范围：$2\leqslant n\leqslant 2\times 10^5,-10^9\leqslant a_i\leqslant 10^9$。**
## Solution
先把这个数对排序，然后一个一个去比较得到差的绝对值的最小值，最后再去一个一个比较看差的绝对值的最小值是否等于这个数对的差的绝对值即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int n, a[200007], minx = 2147483647, cnt;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)	scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 1; i < n; ++i)	minx = min(minx, abs(a[i] - a[i + 1]));
	printf("%d ", minx);
	for(int i = 1; i < n; ++i)
		if(minx == abs(a[i] - a[i + 1]))	cnt++;
	printf("%d", cnt);	
}
```

---

## 作者：Phoenix_chaser (赞：0)

# 发个归并排序的代码

看了这道题的题解，发现竟然没有人用这种快速而又稳定的排序方法

既然这样，那就来一篇归并的题解

核心代码：

这就是**归并排序**

```cpp
void msort(int l,int r){
	if(l==r)
	return ;
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r) ;
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]>a[j])
		{
		c[k++]=a[j++];
		 }
		 else 
		 c[k++]=a[i++]; 
	}
	while(i<=mid) c[k++]=a[i++];
	while(j<=r) c[k++]=a[j++];
	for(int i=l;i<=r;i++)
	a[i]=c[i];
	
}
```
再加上输入输出可以了

就是归并排序之后，

 _**算出两个的差然后进行比较**_ 
 
 具体看代码

```cpp
cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	msort(1,n);
	for(int i=2;i<=n;i++)
	if(minx>abs(a[i]-a[i-1]))
	minx=abs(a[i]-a[i-1]);
	//进行比较 
	for(int i=2;i<=n;i++)
	if(minx==abs(a[i]-a[i-1]))
	ans++;
	//记录次数 
	cout<<minx<<" "<<ans;
	return 0;
```

最后一点：

**minx一定要**

## 开大一点！！！
# 谢谢观看
### THE END





---

## 作者：cryozwq (赞：0)

~~一道超级水题~~
### 题目分析

求 $\min(\left| \ a_i-a_j\right|)$ 及其出现次数。

先看 $n$ 的范围，显然复杂度不会是 $O(n^2)$，所以不会是枚举，考虑排序。

最小值一定在两个最接近的数中，也就是一个有序数列的相邻两项中产生，因为在一个有序数列中一定有 $\left| \ a_i-a_{i-1}\right| \le \left| \ a_i-a_{i-2}\right|$。

于是思路便是：令 $ans1$，$ans2$ 分别表示当前最小值和这个值出现的次数，先排序，再遍历一遍数组，如果 $\left| \ a_i-a_{i-1}\right| < ans1$，就把 $ans1$ 更新，**并把 $ans2$ 清零**（不要忘了！）

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000000],n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);
	int ans1=INT_MAX,ans2=0;//ans1初始化为很大的数，ans2清零
	for(int i=2;i<=n;i++)
	{
		if(a[i]-a[i-1]<ans1)
		{
			ans1=a[i]-a[i-1];//更新ans1
			ans2=0;//ans2清零（但本次也要算所以后面没有打else if）
		}
		if(a[i]-a[i-1]==ans1)
		ans2++;
	}
	cout<<ans1<<" "<<ans2<<endl;
}
```

---

