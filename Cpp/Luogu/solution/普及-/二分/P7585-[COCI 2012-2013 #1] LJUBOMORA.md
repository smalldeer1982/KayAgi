# [COCI 2012/2013 #1] LJUBOMORA

## 题目描述

一家弹珠厂向一所幼儿园捐赠了一些弹珠，弹珠一共有 $M$ 种颜色，每颗弹珠都有一种颜色。老师需要把所有的弹珠分给 $N$ 个孩子。每个孩子得到的所有弹珠都必须是**相同的颜色**，而且可以有一些孩子一颗弹珠也没得到。

我们把**嫉妒值**定义为分给一个孩子最多的弹珠数量。请你帮助老师分弹珠，使得嫉妒值**最小**。

例如，如果有 $4$ 个红色的弹珠（$\texttt{RRRR}$）和 $7$ 个蓝色的弹珠（$\texttt{BBBBBBB}$），要分给 $5$ 个孩子，那么我们可以这样划分：$\texttt{RR}$，$\texttt{RR}$，$\texttt{BB}$，$\texttt{BB}$，$\texttt{BBB}$。这样分的嫉妒值为 $3$，是最小的。

## 说明/提示

#### 【数据范围】

对于 $100\%$ 的数据，保证 $1 \le M \le 3 \times 10^5$，$1 \le N \le 10^9$，$M \le N$。

#### 【说明】

本题分值按 COCI 原题设置，满分 $120$。

题目译自 **[COCI2012-2013](https://hsin.hr/coci/archive/2012_2013/) [CONTEST #1](https://hsin.hr/coci/archive/2012_2013/contest1_tasks.pdf)** ___T4 LJUBOMORA___。

## 样例 #1

### 输入

```
5 2
7
4```

### 输出

```
3```

## 样例 #2

### 输入

```
7 5
7
1
7
4
4```

### 输出

```
4```

# 题解

## 作者：chlchl (赞：89)

## 题目及意思
[题目传送门](https://www.luogu.com.cn/problem/P7585)。

这道题若难以理解“嫉妒值”的意思，~~先别急着看题解~~，可以结合样例来帮助理解题目的意思。这里就先拿题目的样例来做例子分析。

有 4 个红色的弹珠和 7 个蓝色的弹珠，要分给 5 个孩子，那么我们可以这样划分（红为 R，蓝为 B）：$\texttt{RR}$,$\texttt{RR}$,$\texttt{BB}$,$\texttt{BB}$,$\texttt{BBB}$。这样分的嫉妒值为 3，是最小的。

看出来了吧？这题其实是让我们找到一种合适的方案，分给每个人之后让他们之中的最大值最小。

## 思路
这道题正解是二分，关键词为**最大值（即嫉妒值）最小**。看到这种问题的可优先考虑二分。确定核心算法后，进一步分析发现：如果每个分到弹珠的孩子都分到最多的弹珠，那么嫉妒值越大，分到弹珠的孩子越少；嫉妒值越小，分到弹珠的孩子越少。这个嫉妒值是具有单调性的，满足二分的要求。所以确定本题为**二分答案**。

以下为二分模板。
```cpp
while(l <= r){
		mid = (l + r) / 2;
		if(check(mid)){//check 函数需要手写
			r = mid - 1;//不同题目可能这里不太一样
		}else	l = mid + 1;//同上
	}
}
```
若连上面的模板都不能打出来的话建议先去做一下[P2249](https://www.luogu.com.cn/problem/P2249)。

check函数的思路：我们需要将相同颜色的弹珠**尽量按当前枚举的数量平均分给小盆友们**，具体的模拟过程就是除法。我们通过二分枚举嫉妒值 mid，发现第 i 种颜色的弹珠数 $a_i$ 至少需要分给 $\left\lceil\dfrac{a_i}{mid}\right\rceil$ 个孩子。最后把每种颜色的弹珠所分得的孩子数加起来就得到最小的孩子数了。

## 一些小坑
1. 二分答案时，不能**将 mid 直接当做答案输出**，要将它的值**赋给 ans**，输出 ans，否则你会只有 90 分。

1. 注意二分条件和范围。
1. check 函数求每种颜色的弹珠可分得的人数时，应注意判断是否整除，如出现余数则人数应该+1，因为是向上取整.

1. 谨记：**~~五年 OI 一场空，不开 long long 见祖宗！~~** 不开 long long 会 WA 两个点，只有 90 分。

## 代码
**~~要什么代码，自己写嘛。~~**

以下是参考代码，我真诚地劝大家不要抄袭。

$Code$:
```cpp
#include<bits/stdc++.h>
#define ll long long
//这里意思是将long long缩写为ll，省点力气
using namespace std;

const int N = 300000 + 10;
ll n, m, l, r, ans, mid, a[N];

bool check(ll x){
	ll sum = 0;
	for(int i=1;i<=m;i++){
		sum += a[i] / x;
		if(a[i] % x != 0)	sum++;
                //也有题解写成 sum+=(a[i]+x-1)/x，是等价的
	}
	return sum <= n;//人数是否达标？
}

int main(){
	cin >> n >> m;
	for(int i=1;i<=m;i++){
		cin >> a[i];
		r += a[i];//确定右边界，嫉妒值极限为所有球之和
	}
	while(l <= r){//开始二分
		mid = (l + r) >> 1;//等价于 /2
		if(check(mid)){//返回true意味着可以考虑更大些
			r = mid - 1;
			ans = mid;
		}else	l = mid + 1;//返回false意味着要小些
	}
	cout << ans << endl;//输出答案
	return 0;
}
```
**最后提醒大家：自强不息才是好的学习态度，不要嫉妒别人。向优秀的人学习，改正自己的缺点，才能成就更好的自己。**

---

## 作者：信息向阳花木 (赞：16)

~~话说为什么要嫉妒别人，太小心眼了吧。。。~~

### 简化题意！

有 $n$ 个小朋友，弹珠有 $m$ 个颜色，每个小朋友分到的弹珠都得是同一种颜色的，求分到弹珠最多的小朋友手里的弹珠数最少是多少？

### 进入正题！
这道题用$\color{red}{\text{二分}}$去解决会比较好。~~我默认为你已经看过题了。~~

为什么用$\color{red}{\text{二分}}$比较好？

* 此题具有单调性。什么意思？就是说小朋友分到的弹珠越多，嫉妒值越高；小朋友分到的弹珠越少，嫉妒值越低。

所以，我们可以先用二分模板去$\color{red}{\text{二分}}$小朋友的嫉妒值，然后每次对于 $mid$ 去调用 `check` 函数（`check(mid)`）。那么，`check` 函数该怎么写呢？

* 很简单，我们用求每个颜色按每个小朋友 $mid$ 个弹珠，能分给多少个小朋友，用 $sum$ 记按每个每个小朋友 $mid$ 个弹珠最多能分给多少小朋友。若 `sum>=n` ，代表我们的嫉妒值得再大一些（小朋友的弹珠数量再大一些）；否则，需要把嫉妒值调小。

### 展示代码！

```
#include <iostream>  
using namespace std;
long long n,m,l=1,r,ans;
long long a[300010];
bool check(long long x){ //x 是当前的嫉妒值
	long long sum=0;
	for(int i=1;i<=m;i++) sum+=(a[i]+x-1)/x;
	return sum<=n;
} 
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){cin>>a[i];r+=a[i];} //mid 的极限是总共的球数 
	while(l<r){	//二分模板 
		long long mid=(l+r)/2+1;
		if(check(mid)){r=mid-1;ans=mid;}
		else l=mid;
	}
	cout<<ans;
	return 0; 
}
```	

---

## 作者：C_S_L (赞：7)

采用二分：

```cpp
bool OK(ll x){
	ll sum=0;
	for(int i=1;i<=m;++i){
		sum+=(a[i]+x-1)/x;
	}
	return sum<=n;
}
```
若嫉妒值为$x$，那么当每个人的球数取到最大时，得到的人数$sum$应小于等于$n$。

接下来就是二分的基本操作：

```cpp
while(l<=r){
	ll mid=(l+r)/2;
	if(OK(mid)){
		r=mid-1;
		ans=mid;
	}
	else{
		l=mid+1;
	}
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a[300009],ans;
int m;
bool OK(ll x){
	ll sum=0;
	for(int i=1;i<=m;++i){
		sum+=(a[i]+x-1)/x;
	}
	return sum<=n;
}
int main(){
	scanf("%lld%d",&n,&m);
	ll l=1,r=0;
	for(int i=1;i<=m;++i){
		scanf("%lld",&a[i]);
		r+=a[i];
	}
	while(l<=r){
		ll mid=(l+r)/2;
		if(OK(mid)){
			r=mid-1;
			ans=mid;
		}
		else{
			l=mid+1;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：SunsetSamsara (赞：3)

这题从条件**相同的颜色**与分给一个孩子**最多的**弹珠数量可以看出可以用二分完成该题.

既然是二分,就有 $2$ 个中点:判定函数与边界条件.判定函数可以说是十分经典的了,下面直接贴代码:
```cpp
bool judge(int x){
	int sum=0;
	for(int i=1;i<=M;++i)
		sum+=(A[i]+x-1)/x;
    //只要有余数就得+1,相当于(A[i]+x-1)/x
	return sum<=N;
}
```

边界条件中,我采用了典型(也不容易错)的判定方式:左闭右开区间.
```cpp
int left=0,right=0x3f3f3f3f;
while(left+1<right){
	int mid=(left+right)>>1;
	if(judge(mid))right=mid;
	else left=mid;
}
printf("%d\n",right);
```

所以,最后贴完整代码:
```cpp
#include<stdio.h>
int N,M,A[300001];
bool judge(int x){
	int sum=0;
	for(int i=1;i<=M;++i){
		if(A[i]%x)++sum;
		sum+=A[i]/x;
	}
	return sum<=N;
}
int main(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;++i)scanf("%d",A+i);
	int left=0,right=0x3f3f3f3f;
	while(left+1<right){
		int mid=(left+right)>>1;
		if(judge(mid))right=mid;
		else left=mid;
	}
	printf("%d\n",right);
	return 0;
}
```

---

## 作者：fanypcd (赞：2)

### 题目简述：

有 $M$ 种不同颜色的弹珠，第 $i$ 种颜色的弹珠有 $x_i$ 个。现在要求将弹珠分成 $N$ 份（**全部用完**），且每份颜色相同，并使得弹珠数量最多的那一份尽可能少（即嫉妒值最小）。

### 题目思路：

- 二分（这种**最大中取最小，最小中取最大**的且不方便直接求解的问题一般都用二分答案，然后验证答案的合法性）
- 考虑枚举可能的嫉妒值,初始范围 $l,r$ 是 $[0,x_{max}]$。
- 每次取 $mid = (l+r) / 2$，若满足条件（全部用完），则令 $r=mid$ （保留结果），否则令 $l=mid+1$（ $mid$ 不合法则舍弃）。
- 验证过程则是贪心，即对于第 $i$ 种颜色的弹珠，至少要分给 $(x_i+mid - 1)/mid$ 人，这样可以规避不整除人数加一的情况（实际代码中使用特判）。
- 如果总人数 $tot\leq N$，则 $mid$ 作为嫉妒值是可以满足的（允许有人分不到，所以可以小于），反之不能满足。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a[300005];
int check(int x)
{
	int tot = 0;
	for(int i = 1; i <= m; i++)
	{
		tot += a[i] / x;
		if(a[i] % x)//此时该种颜色的弹珠无法分完，剩下的还需要分给一个人
		{
			tot++;
		}
	}
	return tot <= n;
}
int main()
{
	ios::sync_with_stdio(false);//读入优化
	cin >> n >> m;
	int l = 0, r = -1, mid;
	for(int i = 1; i <= m; i++)
	{
		cin >> a[i];
		r = max(r, a[i]);
	}
	while(l < r)
	{
		mid = (l + r) / 2;
		if(check(mid))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	cout << l;
	return 0;
}
```


---

## 作者：luckydrawbox (赞：1)

## 题意

$\sum^M_{i=1}x_i$ 个弹珠有 $M$ 种颜色，第 $i$ 种颜色 $x_i$ 个，分给 $N$ 个孩子，每个孩子获得的弹珠必须颜色相同（可以没有弹珠），求分到弹珠最多的孩子的弹珠数量（嫉妒值）的最小值。

## 分析

可以发现答案是单调的，嫉妒值越大越容易分配完弹珠，我们二分嫉妒值 $mid$，并让分到弹珠的孩子尽量少，显然，第 $i$ 种颜色的弹珠最少能分给 $\left\lceil\dfrac{x_i}{mid}\right\rceil$ 个孩子，判断 $\sum^M_{i=1}\left\lceil\dfrac{x_i}{mid}\right\rceil$ 是否大于 $N$ 即可。时间复杂度为 $\Theta(M\ log\max^M_{i=1}x_i)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int m,n,l=1,r,x[N];
bool check(int ans)//判定答案 
{
	int sum=0;
	for(int i=1;i<=m;i++)
		sum+=ceil(1.0*x[i]/ans);
	return sum<=n;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
    	cin>>x[i];
    	r=max(r,x[i]);//r最大为max(x[i]) 
	}
	while(l<r)//二分 
	{
		int mid=l+r>>1;
		if(check(mid))
			r=mid;
		else l=mid+1;
	}
	cout<<l<<endl;
	return 0;
}
```

---

## 作者：Cambridge (赞：1)


蒟蒻又来发题解了！

#### 题目算法：二分答案

从**每个孩子得到的所有弹珠都必须是相同的颜色**、**把嫉妒值定义为分给一个孩子最多的弹珠数量**、**使得嫉妒值最小**可以看出来。

#### 大致思路：

首先二分最小的嫉妒值，部分代码如下：

```cpp
long long er_find(long long x)
{
	long long ll=0,rr=x+1;
	while(ll+1<rr)//二分
	{
		long long mid=ll+(rr-ll)/2;
		if(Cambridge(mid))rr=mid;
		else ll=mid;
	}
	return rr;
}
```
然后再将二分值进行判断是否可行，部分代码如下：

```cpp
long long Cambridge(long long y)
{
	long long ans=0;
	for(long long i=1; i<=m; i++)
		ans+=a[i]/y+(a[i]%y!=0);//如果有余数，ans还要再加1
	return ans<=n;
}
```
思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<fstream>
#include<algorithm>//文件头不解释
using namespace std;
long long n,m,sum;
long long a[300010];//定义变量
long long Cambridge(long long y)//判断操作
{
	long long ans=0;
	for(long long i=1; i<=m; i++)
		ans+=a[i]/y+(a[i]%y!=0);//见上方解释
	return ans<=n;
}
long long er_find(long long x)//普通二分操作
{
	long long ll=0,rr=x+1;
	while(ll+1<rr)
	{
		long long mid=ll+(rr-ll)/2;
		if(Cambridge(mid))rr=mid;
		else ll=mid;
	}
	return rr;
}
int main()
{
    cin>>n>>m;
    for(long long i=1; i<=m; i++){scanf("%d",&a[i]);sum+=a[i];}
	cout<<er_find(sum);//输出
        //P.S:关于代码为什么满屏的long long——由于作者太菜了，第一次提交的时候WA了两个点，懒得手动把部分int换成long long，所以用“替换文件内容”全部换了。
	return 0;
}
```
好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：Nemonade (赞：0)

这道题暴力枚举每一种嫉妒值的情况肯定是可以做的。

但是由于 $1 \le N \le 10^9$ ，暴力绝对过不了。

又因为人数对于嫉妒值是有序的，所以可以使用二分答案。

```cpp
bool check(long long x){
	long long ans=0;
	for(int i=1;i<=m;++i) ans+=(a[i]+x-1)/x;
	return ans<=n;
}
```
原理：每一个嫉妒值都必须保证可行人数小于等于规定人数。由此可以得出最佳答案。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
long long n,a[N],ans,m;

bool check(long long x){
	long long ans=0;
	//累加人数 
	for(int i=1;i<=m;++i) ans+=(a[i]+x-1)/x;
	return ans<=n;
}
int main(){
	cin>>n>>m;
	long long l=1,r=0,mid;
	for(int i=1;i<=m;++i){
		cin>>a[i];
		//右端点开始点为所有颜色之和 
		r+=a[i];
	}
	while(l<=r){
		//计算中点 
		mid=(l+r)/2;
		if(check(mid))
			//左侧查找 
			r=mid-1,
			ans=mid;
		else
			//右侧查找 
			l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：fls233666 (赞：0)

一开始，我们有些无从下手。但是我们再次观察题目，我们发现嫉妒值是一个孩子分到的弹珠的**最大值**，而我们要做的是让嫉妒值**最小**。让最大值最小，这是标准的**二分答案**题目！进一步考虑会发现，当嫉妒值越大，能分到弹珠的孩子越少；嫉妒值越小，能分到弹珠的孩子则越多。因此我们得出结论: **嫉妒值有单调性，可以二分。** 

我们设我们当前二分的答案区间为 $[l,r]$，二分值为 $mid$，第 $i$ 种弹珠有 $g_i$ 个，在嫉妒值为 $mid$ 的情况下能分给 $cnt$ 个孩子。下面来设计二分算法。

首先我们来考虑 $cnt$ 如何计算。因为我们要满足嫉妒值为 $mid$，所以每个孩子最多只能分到 $mid$ 个弹珠。那么，对于第 $i$ 种弹珠，能分给的孩子数是$\lceil \frac{g_i}{mid} \rceil$，最终有 $cnt=\sum_{i=1}^M \lceil \frac{g_i}{mid} \rceil$。

计算得到 $cnt$ 后，我们考虑如何缩小二分区间。根据题意，当 $cnt \le n$ 时，当前 $mid$ 太大，因此区间应该改为 $[l,mid]$；而当 $cnt > n$ 时，当前 $mid$ 太小，因此区间应该改为 $[mid+1,r]$。

至此，二分答案的整体算法已经设计完成。每次计算 $cnt$ 用时是 $O(M)$， 再算上二分的时间复杂度，总时间复杂度为 $O(M \log (N))$，可以通过此题。

代码如下:

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 3e5+5;

int n,m,g[mxn];
int l,r,mid;

inline bool check(int hen){
	int cnt=0;
	for(rgt i=1;i<=m;i++){
		cnt+=g[i]/hen;
		if(g[i]%hen)
			cnt++;
	}  //计算cnt
	return cnt<=n;
}

int main(){
	scanf("%d%d",&n,&m);
	for(rgt i=1;i<=m;i++)
		scanf("%d",&g[i]);
	l=1;
	r=1e9+7;
	while(l<r){
		mid=(l+r)>>1;  //二分mid
		if(check(mid))  //计算cnt，并与mid比较
			r=mid;
		else
			l=mid+1;  //缩边界
	}
	printf("%d",l);  //得到答案
	return 0;
}
```


---

