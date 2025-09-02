# [ABC143D] Triangles

## 题目描述

【问题描述】

小$Z$有$N$条木棍，每条木棍的长度为$D_i$。他想在这$N$条木棍中选择三条，让这三条木棍能构成一个三角形。小$Z$想知道有多少种方案能构成三角形（不同的方案定义为一条木棍在其中一个三角形中出现不在另一个中出现）。

## 说明/提示

样例$1$：只能形成一个三角形：由第一，第二和第三根木棍形成的三角形。

样例$2$：无法形成三角形。

【数据规模与约定】

对于$100\%$的数据，$3 \leq N \le 2×10^3$，$1\le D_i 
\le10^3$。

## 样例 #1

### 输入

```
4
3 4 2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 1000 1```

### 输出

```
0```

## 样例 #3

### 输入

```
7
218 786 704 233 645 728 389```

### 输出

```
23```

# 题解

## 作者：CaiXY06 (赞：2)

这里提供一种较慢的 $O(n^{2}\log n)$ 的做法。

我们先将数组 $a$ 排序，保证单调性。再双重循环暴力枚举三角形中最小的两条边，分别设下标为 $i,j$ 且 $a_{i}\leq a_{j}$ 然后在下标为 $(j,n]$ 的区间内 **二分查找** 第一个 $a_{k}$ ,使得 $a_{i}+a_{j}\leq a_{k}$ ，这样就保证了区间 $(j,k)$ 三角形的存在，最后更新答案
 $$ans=\Sigma k-j-1$$
  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2010],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<n-1;i++)
	for(int j=i+1;j<n;j++){
		int pos=lower_bound(a+j+1,a+n+1,a[i]+a[j])-a;
		ans+=pos-j-1;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：RainFestival (赞：2)

我们先将木棍长度排序

设 $cnt_i$ 为长度为 $i$ 的木棍的数量

也就是满足 $l_x=i,x\in [1,n] $ 的 $x$ 的数量

$b$ 为 $cnt$ 的前缀和

即 $b_i=\sum\limits_{k=0}^{i}cnt_k$

### 我们先枚举一种木棍长度为 $i$

**case 1**

三根木棍长度为 $i,i,i$ 

此时对答案的贡献为 $C_{cnt_i}^{3}$

### 然后我们再枚举一种木棍为 $j$ ,满足 $i<j$

**case 2**

三根木棍长度为 $i,i,j$ ,要满足 $i+i>j$

此时对答案的贡献为 $C_{cnt_i}^{2}\times C_{cnt_j}^{1}$

**case 3**

三根木棍长度为 $i,j,j$

此时对答案的贡献为 $C_{cnt_i}^{1}\times C_{cnt_j}^{2}$

**case 4**

三根木棍长度为 $i,j,k$ ,其中 $j<k<i+j$

记满足条件的 $k$ 的数量 $x=\sum\limits_{k=j+1}^{i+j-1}cnt_k$

$x$ 可以用 $b$ 数组 $O(1)$ 求

此时对答案的贡献为 $C_{cnt_i}^{1}\times C_{cnt_j}^{1}\times C_{x}^{1}$

时间复杂度 $O((\max\limits_{i=1}^{n}l_i)^2) $

然后是代码：

```cpp
#include<cstdio>
#include<algorithm>
int n,a[2005],b[2005],cnt[2005];
long long ans=0;
int solve(int l,int r){return b[r]-b[l-1];}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),cnt[a[i]]++;
	for (int i=1;i<=2000;i++) b[i]=cnt[i]+b[i-1];
	std::sort(a+1,a+n+1);
	for (int i=1;i<=1000;i++)
	{
		ans=ans+1ll*cnt[i]*(cnt[i]-1)*(cnt[i]-2)/3/2/1;
		for (int j=i+1;j<=1000;j++)
	        ans=ans+1ll*cnt[i]*cnt[j]*solve(j+1,i+j-1)+(i+i>j?1ll*cnt[i]*(cnt[i]-1)/2/1*cnt[j]:0)+1ll*cnt[j]*(cnt[j]-1)/2/1*cnt[i];
	}
	printf("%lld\n",ans);
	return 0;
}
```

注意long long

然后就AC了

QAQ

---

## 作者：xtr169 (赞：0)

-  题目大意：有$n$个棍子，把它摆成三角形，看能摆成多少个。
 
- 思路：看时间限制和数据规模：(三重枚举会超时)排序后，可以用二分，时间快。先枚举两位，再用
```cpp
lower_bound()//二分
```
具体是这样的
```cpp
lower_bound(s.begin(),s.end(),c)-s.begin();//从s.begin()二分查找到s.end(),找比c小的
```
 
- 实现：AC代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;
int main()
{
	int n,ans=0,l,c,tmp;
	cin>>n;
	vector<int>s;
	for(int i=0;i<n;i++)
	{
		cin>>tmp;
		s.push_back(tmp);	
	} 
	sort(s.begin(),s.end());
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
		    c=s[i]+s[j];
			l=lower_bound(s.begin(),s.end(),c)-s.begin();
			ans=ans+(l-j-1);//计算答案加数
		}
	}
	cout<<ans;
}
```
第一次发题解，希望能通过。

---

## 作者：封禁用户 (赞：0)

**题目解释**

从 $a$ 数组中找到 $a_i$、$a_j$、$a_k$，满足 

$\begin{cases}a_i+a_j=a_k\\a_i+a_k=a_j\\a_j+a_k=a_i \end{cases}$

中的任意一条。

**前置芝士：`lower_bound`**

`lower_bound` 是 `C++` 自带的二分函数，时间复杂度 $\mathcal O (\log n)$，食用方法是：

```
lower_bound(一个指针，另一个指针，a)
```

其中这两个指针都在同一个数组里，

它的用处是在第一个指针所指向的数（包括）到第二个指针之间所指向的数中（不包括）第一个大于 $n$ 的数，这两个指针之间的子序列**必须是单调不下降的**，并返回**这个数的地址**。

使用示例：

```
int a[]={1,2,3,4,5,6,9,10,1000};
cout<<lower_bound(a，a+n，3)-a;//会输出2
```

**拓展：关于指针**

对于一个数组 `a[]`，`a[0]` 的地址可以表达为 $a$，即
```
int a[100];
cout<<&a;
```
会输出 `a[0]` 的地址。

而且数组的地址是连续的，所以 `a[i]` 的地址可以表达为 $a+i$。

**思路 1**

直接暴力枚举 $i$、$j$、$k$，但由于 $n \le 2\times10^3$，时间复杂度 $\mathcal O (n^3)$，必定超时。

**思路 2**

先对数组 $a$ 排序，然后枚举 $i$、$j$，然后在 $[
j+1,n)$ 找到最后一个 $<i+j$ 的，再将 $ans+\text{那个数的位置} - j + 1$，具体看下面：

```
1 2 3 4 5 6 7 10 12 15 17
0 0 0 0 i j Y Y  N  N  N
```
我们观察 $>j$ 的这一段，具有单调性。

所以二分就行。

**code**
```
sort(a,a+n);
for(int i=0;i<n-2;i++){
   for(int j=i+1;j<n-1;j++){
       int k=lower_bound(a+j+1,a+n,a[i]+a[j])-a;
       ans+=(k-j-1);
   }
}
cout<<ans;
```
**注意&提示**

- 数组开大一点；
- `lower_bound` 第一个参数是 $a+j+1$；
- 循环范围：$i<n-2$，$j<n-1$。

---

