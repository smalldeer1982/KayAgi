# Unordered Subsequence

## 题目描述

【题面描述】

如果一个序列是递增或递降的（相等也算增或降），则称它为有序的。给定一个序列，找出最短的非有序的子序列。子序列可以不连续。

## 样例 #1

### 输入

```
5
67 499 600 42 23
```

### 输出

```
3
1 3 5
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
2 3 1
```

### 输出

```
3
1 2 3
```

# 题解

## 作者：ahawzlc (赞：7)

思路：~~推理~~

-----

首先我们知道，如果一个数列长度 $len\le 2$，那么这个数列肯定不是无序的，证明显然。

题目中要求求最短的序列，那么只要题目有解，我们肯定能找到一个 $len=3$ 的无序序列。

对于这个题，有一种简便方法，就是只枚举 i ，如果这个序列是有解的，那么肯定能找到 $a[1],a[i],a[i+1]$ 是无序的情况。

证明一下：

1. 如果$a[i]>a[i+1]$：
	1. 如果$a[1]$是三者最大，呈降序，不符合条件，舍去。
    2. 如果$a[1]$居中，满足“小大小”无序。
    3. 如果$a[1]$是三者最小，同上。
2. 如果$a[i]<a[i+1]$：
	1. 如果$a[1]$是三者最大，满足“大小大”无序。
    2. 如果$a[1]$居中，同上。
    3. 如果$a[1]$是三者最小，呈升序，不符合条件，舍去。
    
除了这些情况的，一定无解。

代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=100005;
int a[N],n;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=2;i<n;i++) {//注意越界问题
		if((a[i+1]>a[i]&&a[i]<a[1])||(a[i+1]<a[i]&&a[i]>a[1])) {
			printf("3\n1 %d %d\n",i,i+1);
			return 0;//找到答案直接输出结束。
		}
	}
	printf("0\n");//非要无解我莫得办法
	return 0;
}
```


---

## 作者：xiaozeyu (赞：3)

**这题翻译有问题**

是要找出一个3长度的无序的就好了

```c
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],m=0;
int main()
{
	
	cin>>n;
	for(int i=0;i<n;i++)
	    cin>>a[i];
	for(int i=0;i<n-1;i++)
	    if((a[i]-a[0])*(a[i+1]-a[i])<0)
		{
			cout<<3<<endl<<1<<" "<<i+1<<" "<<i+2<<endl;
			return 0;
		}
	cout<<0;
}
```


---

## 作者：AC_Automation (赞：2)

这道题的翻译有问题，要找到的是最短的非有序子序列。

很明显，长度 <3 的子序列不可能是非有序的，这样的话我们只需要找到长度为三，且非有序的子序列就行了。因为如果我们有一个长度为4的非有序子序列，我们一定可以删掉其中的一个元素，并保持它的非有序性。

于是，题目简化为找到一个长度为3的非有序子序列。我们可以枚举这个子序列的中间点，然后判断是否可以以它为中间点找到非有序子序列。这可以用前缀最大最小值，后缀最大最小值来完成。

code:
```
#include<iostream>
using namespace std;
int a[100005];
struct node{
	int premax,premin,sufmax,sufmin;
}q[100005];//前后缀最大最小值
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	a[n+2]=999999999;
	a[n+1]=-999999999;
	q[0].premin=q[n+1].sufmin=n+2;
	q[0].premax=q[n+1].sufmax=n+1;
	for(int i=1;i<=n;i++){
		q[i].premax=(a[i]>a[q[i-1].premax])?i:q[i-1].premax;
		q[i].premin=(a[i]<a[q[i-1].premin])?i:q[i-1].premin;
	}
	for(int i=n;i>0;i--){
		q[i].sufmax=(a[i]>a[q[i+1].sufmax])?i:q[i+1].sufmax;
		q[i].sufmin=(a[i]<a[q[i+1].sufmin])?i:q[i+1].sufmin;
	}//预处理
	for(int i=2;i<n;i++){
		if(a[q[i-1].premin]<a[i]&&a[q[i+1].sufmin]<a[i]){
			cout<<3<<endl<<q[i-1].premin<<' '<<i<<' '<<q[i+1].sufmin;
			return 0;
		}
		if(a[q[i-1].premax]>a[i]&&a[q[i+1].sufmax]>a[i]){
			cout<<3<<endl<<q[i-1].premax<<' '<<i<<' '<<q[i+1].sufmax;
			return 0;
		}
	}
    //如果对于一个中间点，它的左边最小和右边最小都比它小，或者它的左边最大和右边最大都比它大，那么它就可以构成非有序子序列
	cout<<0;
	return 0;
}

```

---

## 作者：Acerkaio (赞：1)

## 题意翻译：

如果一个序列是递增或递降的（相等也算增或降），则称它为有序的。给定一个序列，找出最短的非有序的子序列。子序列可以不连续。


## 解析：
|情况|结果|原因|
|----|----|---|
| $N \le 2$ |无解|元素只可能是单调的|
|在序列中有 $a_x \le a_y$ 且 $a_y \ge a_z$ 或 $a_x \ge a_y$ 且 $a_y \le a_z$ 的情况|一定有解|这些元素形成无序的情况|

我们明显要着重分析 $N \ge 3$ 情况：
 我们首先需要的是分析是否存在 $a_1 \le a_i$ 且 $a_i \ge a_j$ 或 $a_1 \ge a_i$ 且 $a_i \le a_j$ 的情况。
 Q：为啥是这样?
 
![](https://cdn.luogu.com.cn/upload/image_hosting/85iiv5rb.png)

 如果有解，第一个是 $a_1$。
 
再简化：是否存在 $a_1 \le a_i$ 且 $a_i \ge a_{i+1}$ 或 $a_1 \ge a_i$ 且 $a_i \le a_{i+1}$ 的情况。

 Q：为啥是这样?
 
因为：

1.     如果 $a[i]>a[i+1]$：
        如果 $a[1]$ 是三者最大，呈降序，不符合条件，舍去。
        如果 $a[1]$ 居中，满足“小大小”无序。
        如果 $a[1]$ 是三者最小，同上。

 	--by ahawzlc

所以仅需枚举 $1$ 至 $N$ 即可。
## CODE：
```cpp
#include <iostream>
using namespace std;
int a[100001];
int main(){
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=2;i<n;i++)
	{
		if((a[i+1]>a[i]&&a[i]<a[1])||(a[i+1]<a[i]&&a[i]>a[1])){	
		cout<<3<<endl<<1<<' '<<i<<' '<<i+1;
		return 0;
		}
	}
	cout<<"0\n";
    return 0;
}
```


---

## 作者：Leonid (赞：1)

[原题](https://www.luogu.com.cn/problem/CF27C)

显然当 $n\le 2$ 时无解，所以 $min\{k\}=3$，如果有子序列长度大于 $3$ 的无序子序列，那么他肯定能取掉若干个数使得这个子序列长度为 $3$ 且无序。证明显然。

当子序列长度为 $3$ 且无序时，只有“大小大”和“小大小”两种情况。考虑选定 $a_1$，从 $2$ 开始枚举 $a_i$ 。

当 $(a_1,a_i,a_{i+1})$ 满足“大小大”或“小大小”时，直接输出 $(1,i,i+1)$ 。当枚举 $i$ 已经到 $n-1$ 时则 $a$ 一定满足单调，无解。证明显然。

```cpp
#include<cstdio>

using namespace std;

#define M 100005
#define ok(x) return printf("3\n1 %d %d",x,x+1),0; //方便

int n;
int a[M];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=2;i<n;++i){
		if(a[1]>a[i]) if(a[i]<a[i+1]) ok(i);
		if(a[1]<a[i]) if(a[i]>a[i+1]) ok(i);
	} //枚举
	printf("0");
	return 0;
}
```


---

## 作者：Double_Light (赞：0)

这是一道求最短非有序子序列的题目。

对于一个序列，如果其长度 $\le2$，则其显然为有序。

而对于一个非有序序列，如果它的长度 $\ge3$，其中肯定有一段长度为 $3$ 的子序列亦为最短非有序序列。由于非有序子序列不满足不升或不降，所以总能在序列中找到 $3$ 个数的子序列 $x,y,z$ 使得 $x<y,y>z$ 或者 $x>y,y<z$。

综上，如果输入的序列有解，则肯定解是三个数。对于本题，三个中的 $x$ 可以为 $a_1$。由于 $x$ 是第一个数，所以放在 $a_1$ 也不会有问题。接下来 $y,z$ 就可以进行枚举：枚举 $y$，$z=y+1$。只要满足 $x<y,y>z$ 或者 $x>y,y<z$，则输出就可以了。

放上AC代码：

```cpp
#include<iostream>
using namespace std;
int n,a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=2;i<n;i++){//不要越界
		if(a[1]<a[i]&&a[i]>a[i+1]){//条件一
			cout<<3<<endl<<1<<' '<<i<<' '<<i+1;
			return 0;
		}
		if(a[1]>a[i]&&a[i]<a[i+1]){//条件二
			cout<<3<<endl<<1<<' '<<i<<' '<<i+1;
			return 0;
		}
	}
	cout<<0;
	return 0;
}
```


---

## 作者：Epoch_L (赞：0)

## Solution
首先如果有解，那么长度一定是 $3$，因为如果长度大于 $3$，那其中必然包含一个长度为 $3$ 的无序序列。

问题转化为找长度为 $3$ 的无序序列，要让其呈现单峰或单谷，考虑枚举中间那个数，那我们使左右两边同时最大（单谷）或同时最小（单峰）肯定是最能满足条件的，所以看有没有这样的中间数即可。

前缀后缀最小最大值很好维护，$O(n)$ 一遍搞定，记得记录位置。

## Code
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=1e5+7,inf=1e9+7;
int a[N];
struct node{
  int val,pos;
}lmn[N],lmx[N],rmn[N],rmx[N];
int main(){
  int n;read(n);
  for(int i=1;i<=n;i++)read(a[i]),lmn[i].val=rmn[i].val=inf,lmx[i].val=rmx[i].val=-inf;
  lmn[1].val=lmx[1].val=a[1];
  lmn[1].pos=lmx[1].pos=1;
  for(int i=2;i<=n;i++){
    if(a[i]<lmn[i-1].val)lmn[i].val=a[i],lmn[i].pos=i;
    else lmn[i]=lmn[i-1];
    if(a[i]>lmx[i-1].val)lmx[i].val=a[i],lmx[i].pos=i;
    else lmx[i]=lmx[i-1];
  }
  rmn[n].val=rmx[n].val=a[n];
  rmn[n].pos=rmx[n].pos=n;
  for(int i=n-1;i>=1;i--){
    if(a[i]<rmn[i+1].val)rmn[i].val=a[i],rmn[i].pos=i;
    else rmn[i]=rmn[i+1];
    if(a[i]>rmx[i+1].val)rmx[i].val=a[i],rmx[i].pos=i;
    else rmx[i]=rmx[i+1];
  }
  for(int i=2;i<n;i++){
    if(a[i]>lmn[i-1].val&&a[i]>rmn[i+1].val){
      puts("3");
      printf("%d %d %d\n",lmn[i-1].pos,i,rmn[i+1].pos);
      return 0;
    }
    if(a[i]<lmx[i-1].val&&a[i]<rmx[i+1].val){
      puts("3");
      printf("%d %d %d\n",lmx[i-1].pos,i,rmx[i+1].pos);
      return 0;
    }
  }
  puts("0");
  return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题意：
现在，给定一个 $n$ 个整数的序列 $a_1,a_2,...,a_n$。

请你找到该序列的最短非有序子序列。

## 题解思路：
若他是非有序，那么就是有两种请况：

1.	先上升，再下降
2.	先下降，再上升

为什么没有相同的呢？

因为我们要求的是最短的子序列，所以有相等的我们只留一个就可以了。

而且我们发现这两种情况只需要三个元素就够了。

那么我们其实就是要求在这个序列里是否有三个元素满足：

第一个和第三个都大于或都小于中间的元素。

那么对于第一种情况，我们可以枚举中间的元素，那么我们只要判断是否有两个元素，满足一个在他左边一个在他右边并且两个数都比他小。

对于第二种请况同理，只是要求两边的元素都比他大就可以了。

那么我们就预处理 $minn1_i,minn2_i,maxn1_i,maxn2_i$ 分别代表他前 $i$ 个的最小值的下标，后 $i$ 个的最小值的下标，前 $i$ 个的最大值的下标和后 $i$ 个的最大值的下标。

那么对于一个数，我们就判断他前面和后面的最大（最小）值是否满足条件即可。

## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100010];
int minn1[100010], maxn1[100010], minn2[100010], maxn2[100010];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    if (n < 3) {//长度小于三就一定不行
        puts("0");
        return 0;
    }
    maxn1[1] = minn1[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[maxn1[i - 1]] > a[i])//若他是比前一个小，那么下标还是前i-1的最大值
            maxn1[i] = maxn1[i - 1];
        else
            maxn1[i] = i;//否则赋值成他自己
        if (a[minn1[i - 1]] < a[i])//最小值同理
            minn1[i] = minn1[i - 1];
        else
            minn1[i] = i;
    }
    //从后面开始的同理
    maxn2[n] = minn2[n] = n;
    for (int i = n - 1; i >= 1; --i) {
        if (a[maxn2[i + 1]] > a[i])
            maxn2[i] = maxn2[i + 1];
        else
            maxn2[i] = i;
        if (a[minn2[i + 1]] < a[i])
            minn2[i] = minn2[i + 1];
        else
            minn2[i] = i;
    }
    int i;
    for (i = 2; i < n; ++i) {//枚举中间值
        if(a[minn1[i - 1]] < a[i] && a[minn2[i + 1]] < a[i]) {//第一种情况
            puts("3");
            printf("%d %d %d\n", minn1[i - 1], i, minn2[i + 1]);
            break;
        }
        if (a[maxn1[i - 1]] > a[i] && a[maxn2[i + 1]] > a[i]) {//第二种请况
            puts("3");
            printf("%d %d %d\n", maxn1[i - 1], i, maxn2[i + 1]);
            break;
        }
    }
    if (i == n) {
        puts("0");
    }
    return 0;
}
```

---

## 作者：lilong (赞：0)

题意为找出最短的无序子序列。这题看到 $k$ 的取值有多种可能，我们不妨对其取值作分类讨论。

- $k=1$ 或 $k=2$

很显然，当 $k=1$ 时，只有一个数，不满足题意；当 $k=2$ 时，两个数之间一定是递增或递降的，也不符合要求。

- $k=3$

当 $k=3$ 时，存在两种可能的情况是有解的。设三个数从前至后依次为 $a,b$ 和 $c$。

1. $a < b$ 并且 $c<b$

这种情况即是出现了一个“山峰”，左右的数都比中间小，不是有序的子序列。

2. $a>b$ 并且 $c>b$

这种情况即是出现了一个“低谷”，左右的数都比中间大，也不是有序的子序列。

- $k>3$

很容易得知，既然存在 $k>3$ 的非有序子序列，它肯定是由比它短的子序列构成的。因此若存在 $k>3$ 的非有序子序列，则一定也存在 $k=3$ 的子序列。


分析完毕之后，实现思路就很简单了：在整个序列中判断是否存在长度为 $3$ 的非有序子序列，若有则输出方案，否则无解。

代码见下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,a[1000001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(n==1||n==2)	
	{
		cout<<0;
		return 0;
	}
	for(int i=2;i<n;i++)
		if(a[i]<a[1]&&a[i]<a[i+1]||a[i]>a[1]&&a[i]>a[i+1])	
		{
			cout<<3<<endl;
			cout<<1<<' '<<i<<' '<<i+1;
			return 0;
		}
	cout<<0;
	return 0;
}
```


---

## 作者：Cuiyi_SAI (赞：0)

## 解题思路

显然，长度为 $1$ 或者 $2$ 的序列必定是有序的。若原序列存在解，那么最短长度必定为 $3$，因为任何长度大于 $3$ 的非有序序列必定可以通过一系列删数，使得可以保留非有序性的情况下让序列长度更小。

对于一个数 $a_i$，若其有 $a_{i-1}<a_i>a_{i+1}$，则称其为**峰值**，若其有 $a_{i-1}>a_i<a_{i+1}$，则称其为**低谷**。

**对于原序列中的峰值或低谷，其必定属于至少一个长度为 $3$ 的非有序序列中**，因为对于任意一个峰值或者低谷，其定义都使其对周围的数不满足单调关系。

因此问题转化为找峰值或者低谷。

具体实现过程是，我们将 $a_1$ 作为答案序列的首位，从头到尾扫一遍原序列，若找到一个 $i$ 使得 $(a_1,a_{i-1},a_i)$ 构成山峰或者低谷，那么就存在解。时间复杂度 $O(n)$。

## CODE：

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
int n,a[100010];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	if(n<=2)
	{
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=3;i<=n;i++)
	{
		if(a[i]>=a[i-1]&&a[i-1]>=a[1]) continue;
		if(a[i]<=a[i-1]&&a[i-1]<=a[1]) continue;
		cout<<3<<'\n';
		cout<<1<<' '<<i-1<<' '<<i<<'\n';
		return 0;
	}
	cout<<0;
    return 0;
}
```


---

## 作者：Siteyava_145 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF27C)

首先，单独一个数是有序的，两个数也是有序的。而 $3$ 个数就不一定了。

于是我们可以构造出这样的 $3$ 个数（题目要求最小）。

先选出 $2$ 个数，例如 $a_{i}$ 与 $a_{i+1}$，或者 $a_{i}$ 与 $a_{i-1}$。

再选第 $3$ 个数，例如 $a_1$。

接着进行判断（枚举 $i$（$1<i<n$））。代码中是比较的 $a_i$ 与 $a_{i+1}$。若 $a_i>a_{i+1}$，如果 $a_1<a_i$，那么输出即可（$a_i$ 最大，$a_1,a_{i+1}$ 较小）；否则```continue```掉。若 $a_i=a_{i+1}$，那么```continue```掉（退化成了两数的情况）。若 $a_i<a_{i+1}$，如果 $a_1>a_i$，那么输出即可（$a_i$ 最小，$a_1,a_{i+1}$ 较大）；否则```continue```掉。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int a[N];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=2;i<n;i++){
        if(a[i]>a[i+1]){
            if(a[1]>a[i])continue;
            else if(a[i]==a[1])continue;
            else{cout<<3<<endl<<1<<' '<<i<<' '<<i+1;return 0;}
        }
        else if(a[i]<a[i+1]){
            if(a[1]>a[i]){cout<<3<<endl<<1<<' '<<i<<' '<<i+1;return 0;}
            else continue;
        }
    }
    cout<<0;
    return 0;
}
```


---

## 作者：LYqwq (赞：0)

 [题目传送门](https://www.luogu.com.cn/problem/CF27C)

# 题目大意

给定一个长度为 $n$ 的序列，请找出最短的非有序的子序列。子序列可以不连续。

有序定义如下：如果一个序列是递增的或递减的（相等也算增和降），则是有序的。

输出最短非有序子序列的长度，并输出这些数的下标。

# 思路

首先，可以排除长度 $\le 2$ 的情况，因为长度 $\le 2$ 的序列一定是有序的。然后就要看长度 $\ge 3$ 的情况了。若为 $3$，则是最优情况。若为 $4$，我们可以通过删去一个元素，变成长度为 $3$ 的序列，可以发现，长度为 $4$ 的序列始终可以通过删去一个元素还是保持非有序。当长度 $\ge 5$ 时，同上，也可以化简为长度为 $3$ 的非有序序列。

于是，题意就化简为：找到长度为 $3$ 的非有序子序列。

如果暴力枚举 $3$ 个点，那一定会超时，时间复杂度 $\mathcal{O}(n^3)$。

先来分析一下长度为 $3$ 的序列非有序的条件。若有两个数相等，那么一定是最左边和最右边的数，不可能连在一起。递增或递减也不行，包括全部相等。那就只有两种可能：`小大小` 和 `大小大` 的情况。稍微想一想，就很能明白了。

我们可以假定下标为 $1$ 的数是第一个数，搜一遍数组，找连续两个数作为另外两个数。然后判断，按照上面的分析，判断条件也很容易得出：`a[1]<a[i] && a[i]>a[i+1] || a[1]>a[i] && a[i]<a[i+1]`。若条件成立，则已经找到正确答案，输出并退出程序。若始终没有找到正确答案，那么就无解。

# 代码

```cpp
#include <iostream>
using namespace std;
int n,a[100005];

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i];
	}
	for(int i=2; i<n; i++){
		// 中间的最大或最小，都算可以。
		if(a[1]<a[i] && a[i]>a[i+1] || a[1]>a[i] && a[i]<a[i+1]){
			cout << "3\n1 " << i << " " << i+1 << endl;
			return 0;
		}
	}
	puts("0"); // 没找到则无解
	return 0;
}
```



---

## 作者：codeLJH114514 (赞：0)

[CF27C Unordered Subsequence in Luogu](https://www.luogu.com.cn/problem/CF27C)

[CF27C Unordered Subsequence in CodeForces](https://codeforces.com/contest/27/problem/C)

# Problem

给定一个长度为 $N$ 的数组 $a_{1...N}$，求这个数组的**最短无序子序列**。

无序：非升序也非降序就是无序。

输出：先输出长度 $k$，再输出子序列每一个元素的在原数组的下标。（如果没有输出 `0`）

# Analysis

如果 $k = 1$，只有一个元素显然有序；$k = 2$，只有两个元素，仍然有序；$k > 3$，可以删到 $3$ 个元素。

所以我们输出的第一个 $k$ 一定是 $3$。（无解除外）

$k = 3$ 有哪些情况？显然是小大小和大小大。

对于每一个数，我们预处理出前缀最小、最大和后缀最小、最大，这样我们就可以对于每一个 $1 < i < N$ 判断如果 `{1 ... i - 1 最大值, i, i + 1 ... N 最大值}` 无序 或者 `{1 ... i - 1 最小值, i, i + 1 ... N 最小值}` 无序那么就输出即可。

如果全算一遍还没有输出就输出 $0$。

# Coding

```cpp
#include <iostream>
#define maxn 131072
int N;
struct Lister {
    int value;
    int premax, premin;
    int bckmax, bckmin;
    Lister(): value(0), premax(0), premin(maxn - 1), bckmax(0), bckmin(maxn - 1){};
} a[maxn];
bool Unordered(int, int, int);
int main() {
    std::cin >> N;
    a[0].value = 0xACACACAC;
    a[maxn - 1].value = 0x3f3f3f3f;
    for (int i = 1; i <= N; i++) 
        std::cin >> a[i].value;
    for (int i = 1; i <= N; i++) {
        if (a[i].value > a[a[i - 1].premax].value) a[i].premax = i;
        else a[i].premax = a[i - 1].premax;
        if (a[i].value < a[a[i - 1].premin].value) a[i].premin = i;
        else a[i].premin = a[i - 1].premin;        
    }
    for (int i = N; i >= 1; i--) {
        if (a[i].value > a[a[i + 1].bckmax].value) a[i].bckmax = i;
        else a[i].bckmax = a[i + 1].bckmax;
        if (a[i].value < a[a[i + 1].bckmin].value) a[i].bckmin = i;
        else a[i].bckmin = a[i + 1].bckmin;
    }
    for (int i = 2; i < N; i++) {
        if (Unordered(a[i - 1].premax, i, a[i + 1].bckmax)) {
            std::cout << "3\n" << a[i - 1].premax << " " << i << " " << a[i + 1].bckmax;
            return 0;
        }
        if (Unordered(a[i - 1].premin, i, a[i + 1].bckmin)) {
            std::cout << "3\n" << a[i - 1].premin << " " << i << " " << a[i + 1].bckmin;
            return 0;
        }
    }
    std::cout << "0";
    return 0;
}
bool Unordered(int x, int y, int z) {
    return not(a[x].value <= a[y].value and a[y].value <= a[z].value or a[x].value >= a[y].value and a[y].value >= a[z].value);
}
```

---

## 作者：TsH_GD (赞：0)

### 题意

给出 $ N $ 个数。

找出其中不递增或者不递减的序列位置，否则输出 $ 0 $ 。

## 思路：

序列无序的个数要么是 $ 0 $ 要么就是 $ 3 $ ，所以只要找到序列的峰值或者低值就可以了。

就是输入的时候就比较前面已经输入的数的最大值和最小值并保存他们的位置，如果最大或最小产生了变化，那么结果就出来了…


### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,i,k,max,min;
	while(~scanf("%d",&n)){
		int f1=0,f2=0,ff=0;
		int pos1,pos2;
		for (i=1; i<=n; i++){
			scanf("%d",&k);
			if(i==1){
				max=k;
				min=k;
			} 
			else if(ff==0){
				if(k>max){
					if(f2==0){
						max=k;
						pos1=i;
						f1++;
					} 
					else{
						pos2=i;
						ff=1;
					}
				}
				if(k<min){
					if(f1==0){
						min=k;
						pos1=i;
						f2++;
					} 
					else{
						pos2=i;
						ff=1;
					}
				}
				if((k>min&&f2)||(k<max&&f1)){
					pos2=i;
					ff=1;
				}
			}
		}
		if(ff) printf("3\n1 %d %d\n",pos1,pos2);
		else printf("0\n");
	}
	return 0;
}
```

---

