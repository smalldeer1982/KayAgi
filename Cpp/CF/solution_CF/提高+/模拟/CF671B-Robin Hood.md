# Robin Hood

## 题目描述

We all know the impressive story of Robin Hood. Robin Hood uses his archery skills and his wits to steal the money from rich, and return it to the poor.

There are $ n $ citizens in Kekoland, each person has $ c_{i} $ coins. Each day, Robin Hood will take exactly $ 1 $ coin from the richest person in the city and he will give it to the poorest person (poorest person right after taking richest's $ 1 $ coin). In case the choice is not unique, he will select one among them at random. Sadly, Robin Hood is old and want to retire in $ k $ days. He decided to spend these last days with helping poor people.

After taking his money are taken by Robin Hood richest person may become poorest person as well, and it might even happen that Robin Hood will give his money back. For example if all people have same number of coins, then next day they will have same number of coins too.

Your task is to find the difference between richest and poorest persons wealth after $ k $ days. Note that the choosing at random among richest and poorest doesn't affect the answer.

## 说明/提示

Lets look at how wealth changes through day in the first sample.

1. $ [1,1,4,2] $
2. $ [2,1,3,2] $ or $ [1,2,3,2] $

So the answer is $ 3-1=2 $

In second sample wealth will remain the same for each person.

## 样例 #1

### 输入

```
4 1
1 1 4 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 1
2 2 2
```

### 输出

```
0
```

# 题解

## 作者：kevin1616 (赞：6)

### 审题
每天最富的人财富 $-1$，最穷的人财富 $+1$（若有相同，随便选一个），求最后的穷人与富人财富的差值最小是多少。
***
### 方法
+ 【暴力】$k$ 次循环，每一次求出最大值与最小值，将最大值 $-1$，最小值 $+1$，最后输出最大值减最小值即可。时间复杂度为 $O(nk)$，故不可以。

+ 【二分答案】可以考虑先求出最大值和最小值，再两者相减即为答案，最大、最小值都可以用二分答案求出。此方法的时间复杂度为 $O(n \log n)$，此方法可行。

***
### 思路
1. 最大值的答案是在平均钱数 $\sim$ 钱数总和之间，使每个人从原来的钱数降到目标钱数所需要的天数是否可行。此部分代码如下：

```cpp
bool check1(int x){
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(c[i] > x) cnt += c[i] - x;
    }
    return cnt <= k;
}
```

2. 最小值的答案是在 $1 \sim$ 平均钱数之间，使每个人从原来的钱数升到目标钱数所需要的天数是否可行。此部分代码略同上，就不单独展示了。

***
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int c[500005];
int l1,r1;
int l2 = 1,r2;
int sum;
bool check1(int x){ // 最大值的答案
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(c[i] > x) cnt += c[i] - x;
    }
    return cnt <= k;
}
bool check2(int x){ // 最小值的答案
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(c[i] < x) cnt += x - c[i];
    }
    return cnt <= k;
}
signed main(){
    cin >> n >> k;
    for(int i = 1;i <= n;i++){
        cin >> c[i];
        r1 = max(r1,c[i]);
        sum += c[i];
    }
    l1 = sum / n + (sum % n != 0);
    /*
    也可以这样写：
    if(sum % n == 0) l1 = sum / n;
    else l1 = sum / n + 1;
    */
    r2 = sum / n;
    while(l1 < r1){ // 求最大值
        int mid = (l1 + r1) / 2;
        if(check1(mid)) r1 = mid;
        else l1 = mid + 1;
    }
    while(l2 < r2){ // 求最小值
        int mid = (l2 + r2 + 1) / 2;
        if(check2(mid)) l2 = mid;
        else r2 = mid - 1;
    }
    cout << l1 - l2 << endl;
    // 其实这里的 l 也可以替换成 r
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：liruixiong0101 (赞：6)

### 题目简述：
每天最富的人财富减一，最穷的人财富加一（若有相同，随便选一个），求最后的穷人与富人财富的差值最小是几？  
### 思路：
贪心地想一想，很容易发现我们需要让最大值最小，最小值最大，才可以让最大值减最小值的差最小。

------------


首先暴力做法 $k$ 次循环，每一次求出最大值与最小值，将最大值减一，最小值加一，最后输出最大值减最小值即可，时间复杂度： $O(nk)$。 很明显不可过。

------------

可以考虑先求出最大值，再求出最小值，两者相减即为答案，最大最小值都可以用二分答案求出。  
设 $f(x)$ 为若最后最大值为 $x$ 是否可以在 $k$ 天以内得到此最大值：
* 若 $c_i$ 大于 $x$ 就需要花 $c_i - x$ 的天数来变成 $x$。
* 否则不变。

用循环枚举每一个 $c_i$ 累计天数，若天数小于等于 $k$ 即为能够在 $k$ 天以内得到这个最大值返回 $1$ 否则返回 $0$。

此部分代码如下：
```cpp
bool check1(int x){//check1(x)就是f(x)
	int day = 0;//累计天数的计数器
	for(int i = 1; i <= n; i++){
		if(c[i] > x) day += c[i] - x;//若大于x则变成x
	}
	return day <= k;
	/*可以写成如下
	if(day <= k) return 1;
	else return 0;
	*/
}
```
由此我们可以设计出 $g(x)$ 为若最后最小值为 $x$ 是否可以在 $k$ 天以内得到此最小值，分析方式与 $f(x)$ 略同，就不给出来了。

此方法的时间复杂度： $O(n\log n)$。时间没问题，可以试试。

------------

然后就是疯狂写代码的时候，实现难度还是挺小的，代码如下：
```cpp
#include <bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
int n , k , sum , c[500005];
int l1 , r1 , l2 , r2;
bool check1(int x){//f(x)
	int day = 0;
	for(int i = 1; i <= n; i++){
		if(c[i] > x) day += c[i] - x;
	}
	return day <= k;
}
bool check2(int x){//g(x)
	int day = 0;
	for(int i = 1; i <= n; i++){
		if(c[i] < x) day += x - c[i];
	}
	return day <= k;
}
signed main(){
	scanf("%d%d" , &n , &k);
	for(int i = 1; i <= n; i++){
		scanf("%d" , &c[i]);
		//输入
		sum += c[i];
		r1 = max(r1 , c[i]);
	}
	if(sum % n == 0) l1 = sum / n;
	else l1 = sum / n + 1;
	//最大最小情况为总的财富除以人数向上取整，最大情况为最大的财富
	while(l1 < r1){
		int mid = (l1 + r1) / 2;
		if(check1(mid)) r1 = mid;
		else l1 = mid + 1;
	}//最大值最小
	l2 = 1 , r2 = sum / n;
	//最小值最小情况为1次，最大情况为总的财富除以人数向下取整
	while(l2 < r2){
		int mid = (l2 + r2 + 1) / 2;
		if(check2(mid)) l2 = mid;
		else r2 = mid - 1;
	}//最小值最大
	printf("%d" , l1 - l2);//输出
	return 0;
}
```

---

## 作者：用户已注销 (赞：3)


拿到题目不着急，抽象成一个数学问题后，看看到底问了什么，要求什么：

题意很清晰，一个序列操作 K 次，每次最大值 -1 后最小值 +1 ，求最终的 最大值-最小值 。

这种区间最大最小值还带修改的问题当然自然的想到线段树啦！

然后发现 k ≤ 1e9

 。。。。。。
 
我们学校的一名大佬说过：

**处理一个1e9的整数当然是二分啊！**

于是我们想想这道题怎么二分！

首先想想二分什么：

既然答案是 Max - Min ，你总不能直接二分这个答案吧。

所以考虑让这个东西最小，只要让 Max 最小而 Min 最大就好了。

所以我们分别二分这两个值，由于道理是相同的，就只讲 Max 的部分了：

经过 K 轮劫富济贫后，剩下的人最多的钱数为 Max ，那么很明显：

**1，初始钱数不大于 Max 的人都不会被劫**

**2，初始钱数大于 Max 的人都会被劫 A[i] - Max 次**

所以只要 O(N) 扫一遍看看达成当前的 Max 值的话，K 天够不够。

边界处理要略小心，因为最大值显然不会低于平均值，不会多于最富的人的钱，所以 L = Num / N + ( Num % N != 0 ) , R = Max A

这个 L 的意思就是，整除的话就是平均值，否则就是平均值 +1 。

对于 Min 做一次一样的二分， L = 1 , R = Num / N 整不整除都没关系。

最后输出 Max - Min 

**那么这样做为什么是对的呢？**

~~闭上眼睛，感性理解，~~回顾一下我们在做什么：

两遍二分，我们都是尽量让最小值最大，最大值最小。

那么这个**主人公**在干什么呢？

他每次抢最多的人的钱给最少的人，尽量减小最大值，增加最小值，所以和我们做的事情是一样的。

于是这个二分是对的。

```
#include <cstdio>
using namespace std ;

inline long long Max( long long A , long long B ) { return A > B ? A : B ; }
inline long long Readin() {
	
	register long long K = 0 ;
	register char C = getchar() ;
	
	for( ; C < '0' or C > '9' ; C = getchar() ) ;
	for( ; C <= '9' and C >= '0' ; C = getchar() )
		K = ( K << 1 ) + ( K << 3 ) + C - '0' ;
	
	return K ;
	
}

long long N , K ;
long long A[500005] ;
long long Sum ;
long long Arv ;

inline bool Check1( long long Num ) {
	
	long long Ans1 = 0 ;
	for(register long long i = 1 ; i <= N ; i++ )
		Ans1 += Max( 0 , Num - A[i] ) ;
	return Ans1 <= K ;
	
}

inline bool Check2( long long Num ) {
	
	long long Ans2 = 0 ;
	for(register long long i = 1 ; i <= N ; i++ )
		Ans2 += Max( 0 , A[i] - Num ) ;
	return Ans2 <= K ;
	
}

long long L , R , Mid ;
long long Maxx , Minn ;

int main() {
	
	N = Readin() ;
	K = Readin() ;
	
	for(register long long i = 1 ; i <= N ; i++ ) {
		Maxx = Max( Maxx , A[i] = Readin() ) ;
		Sum += A[i] ;
	}
	Arv = Sum / N ;
	
	Mid = ( L = 1 ) + ( R = Arv ) >> 1 ;
	for( ; L < R ; Mid = L + R + 1 >> 1 )
		Check1( Mid ) ? L = Mid : R = Mid - 1 ;
	Minn = L ;
	
	Mid = ( L = Arv + ( Sum % N != 0 ) ) + ( R = Maxx ) >> 1 ;
	for( ; L < R ; Mid = L + R >> 1 )
		Check2( Mid ) ? R = Mid : L = Mid + 1 ;
	Maxx = L ;
	
	return not printf( "%lld\n" , Maxx - Minn ) ;
	
} 
```

二分真是个好东西。

---

## 作者：XL4453 (赞：1)

似乎还没有发现和我做法一样的题解。

---
### 解题思路：

本题完全可以不用二分法做，模拟加个小优化就行了，不过细节会有点多，代码量也相对较大，而且常数比较大，唯一的有点是好理解。

发现最小的总是总一个最小的往上加然后带着次大的一起加，而且一旦相同就再也不会分离超过 $1$，否则一定不满足题目给出的条件。对于最大的也是同理。

考虑模拟这个过程，先将所有的人按照价格从小到大排序，然后维护两个指针，一个指向当前总钱数最多的被给予的人，另一个维护被抢劫的钱数最少的人，计算出使得所有的人往下一个位置移动的代价，然后分别推进这两个指针。

需要维护：当前相同钱数的人的个数，当前的，但是还未达到下一个人的最大值和最小值，当前到达下一个人需要的钱数，当前未到达下一个值剩下的钱数。

注意上述需要维护的最后一个值，也就是当前未到达下一个值剩下的钱数，这个值在当前的一群人未到达下一个人之前计算当前最大值和最小值有重要作用。

每一次移动指针需要考虑三种情况，分别是左指针向右移动，右指针向左移动，同时向中间移动。这里注意判断恰好到了中间的情况。

根据上述过程每一次模拟可以直接跳到下一个人，而且这两个指针都是单调的，所以模拟的复杂度是 $O(n)$ 的。总复杂度 $O(n\log n)$ 瓶颈在排序。

建议配合代码理解。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,a[500005],k,l,r,cntl,cntr,minl,maxr,totl,totr,tot,lastl,lastr;
signed main(){
	scanf("%I64d%I64d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%I64d",&a[i]),tot+=a[i];
	sort(a+1,a+n+1);
	l=1;r=n;
	cntl=cntr=1;
	minl=a[1];maxr=a[n];
	while(k){
		if(totl==0)totl=(a[l+1]-a[l])*cntl,minl=a[l],lastl=0;
		if(totr==0)totr=(-a[r-1]+a[r])*cntr,maxr=a[r],lastr=0;
		if(k<min(totl,totr)){
			minl+=(k+lastl)/cntl;
			maxr-=(k+lastr)/cntr;
			lastl=(lastl+k%cntl)%cntl;
			lastr=(lastr+k%cntr)%cntr;
			break;
		}
		if(totl<totr){
			minl+=(totl+lastl)/cntl;
			maxr-=(totl+lastr)/cntr;
			lastl=(lastl+totl%cntl)%cntl;
			lastr=(lastr+totl%cntr)%cntr;
			k-=totl;totr-=totl;totl=0;
			l++;cntl++;
		}
		if(totl>totr){
			minl+=(totr+lastl)/cntl;
			maxr-=(totr+lastr)/cntr;
			lastl=(lastl+totr%cntl)%cntl;
			lastr=(lastr+totr%cntr)%cntr;
			k-=totr;totl-=totr;totr=0;
			r--;cntr++;
		}
		if(totl==totr){
			minl+=(totl+lastl)/cntl;
			maxr-=(totl+lastr)/cntr;
			lastl=(lastl+totr%cntl)%cntl;
			lastr=(lastr+totr%cntr)%cntr;
			k-=totr;totl=totr=0;
			r--;cntr++;
			l++;cntl++;
		}
		if(l>=r){
			if(tot%n==0)printf("0\n");
			else printf("1\n");
			exit(0);
		}
	}
	if(maxr==minl)if(lastl!=0||lastr!=0)maxr=minl+1;
	printf("%I64d",max(0ll,maxr-minl));
	return 0;
}
```


---

## 作者：Xie_BR (赞：1)

这道题其实是一道很好的二分题目，下面请听本蒟蒻慢慢道来：

首先，对于每一道二分题目需要找到一个上限&下线

其次，我的思路是从左跑一边，从又跑一边，所以最后的答案就是ansr-ansl

来一段AC二分代码：（代码简单，再次不做更多解释）

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long
#define MK 500050
using namespace std;
int n,k;
int a[MK];

bool checkl(int x)
{
	int opt = 0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<x)
		{
			opt+=(x-a[i]);
		}
	}
	if(opt<=k)
	{
		return true;
	}else
	{
		return false;
	}
}

bool checkr(int x)
{
	int opt = 0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>x)
		{
			opt+=(a[i]-x);
		}
	}
	if(opt<=k)
	{
		return true;
	}else
	{
		return false;
	}
}

int workl(int l,int r)
{
	int opt = l;
	int mid;
	while(l<=r)
	{
		mid = (l+r)/2;
		if(checkl(mid))
		{
			opt = mid;
			l = mid+1;
		}else
		{
			r = mid-1;
		}
	}
	return opt;
}

int workr(int l,int r)
{
	int opt = l;
	int mid;
	while(l<=r)
	{
		mid = (l+r)/2;
		if(checkr(mid))
		{
			opt = mid;
			r = mid-1;
		}else
		{
			l = mid+1;
		}
	}
	return opt;
}

signed main()
{
	scanf("%lld%lld",&n,&k);
	int minx = 0x3f3f3f3f;
	int maxn = -0x3f3f3f3f;
	int sum = 0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum+=a[i];
		minx = min(minx,a[i]);
		maxn = max(maxn,a[i]);
	}
	int cntl = sum/n;
	int cntr = (sum+n-1)/n;
	int ansl = workl(minx,cntl);
	int ansr = workr(cntr,maxn);
	printf("%lld",ansr-ansl);
	return 0;
}
```


---

## 作者：ylch (赞：0)

# 洛谷 CF671B 题解

[【猛击这里 查看题目】](https://www.luogu.com.cn/problem/CF671B)

## 题目大意

有一个长度为 $n$ 的序列，每次把最大的数加一，把最小数减一，求 $k$ 次操作后最大值和最小值的差。

## 解题思路

> 数学先打表，规律找一找。

——《OIer 行动准则》


------------

通过打表，不难发现，数列在若干次操作之后一定会达到一个“平衡”的状态，打表如下：

当序列为 $\texttt{1142}$ 时：
$\texttt{1124} \rightarrow \texttt{1223} \rightarrow \texttt{2222} \rightarrow \texttt{2222} \cdots$

当序列为 $\texttt{15349}$ 时：
$\texttt{13459} \rightarrow$ $\texttt{23458} \rightarrow$ $\texttt{33457} \rightarrow$ $\texttt{34456} \rightarrow$ $\texttt{44455} \rightarrow$ $\texttt{44455} \cdots$

由此，我们可以对最大值和最小值进行二分。

接下来要写 `check` 函数，在二分最小值时，我们可以累加每一个比 $mid$ 小的元素要达到以 $mid$ 为最小值的平衡状态需要多少天（注意这个元素一定要比 $mid$ 小，这样才可能经过操作使 $mid$ 成为最小值），如果天数在 $k$ 以内就返回真值。二分最大值同理，不多做赘述。


------------

在讨论区里有一篇[《如何严格证明二分是对的》](https://www.luogu.com.cn/discuss/show/598465)，楼主的意思是二分时最大值和最小值是分开求的，如何保证两者可以同时取到？换句话说，存不存在二分出的最小值和最大值不相互对应的情况呢？

其实不会出现这种情况，如上文所说，序列最后会达到一个“平衡”的状态，所以求出的最大值和最小值一定是平衡后数列的最大和最小值，数列已经“平衡”了，自然不会存在不合法的情况（不合法的在 `check` 函数里已经筛掉了）。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,k;
int a[500005];

int check1(int x)
{
	int cnt = 0; //表示还有cnt天到达以x为最小值的状态
	for (int i=1; i<=n; i++) //如果比二分的最小值小，就加上差值
		if (a[i] < x)	cnt += x - a[i];
	return cnt <= k;
}

int check2(int x)
{
	int cnt = 0; //表示还有cnt天到达以x为最大值的状态
	for (int i=1; i<=n; i++) //如果比二分的最小值大，就加上差值
		if (a[i] > x)	cnt += a[i] - x;
	return cnt <= k;
}

int sum,l,r,s1,s2;

signed main()
{
	scanf("%lld %lld", &n, &k);
	for (int i=1; i<=n; i++)
	{
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	sort(a+1, a+n+1, less<int>());
	
	//	先二分最小值，单调递增，左边界为数列最小值，右边界为数列平均数
	l = a[1], r = sum / n;
	while (l <= r)
	{
		int mid = (l+r) >> 1;
		if (check1(mid))
		{
			s1 = mid;
			l = mid+1; //可以，继续往大了搜
		}
		else	r = mid-1; //说明选大了，动右指针往小搜
		
	}
	
	//	再二分最大值
	l = a[n], r = (sum%n? sum/n+1 : sum/n); //最后可能不会完全平衡，所以除不尽要向上取整
	while (l >= r) //坑点，递减二分，l>=r
	{
		int mid = (l+r) >> 1;
		if (check2(mid))
		{
			s2 = mid;
			l = mid-1; //符合要求，再往小找
		}
		else	r = mid+1; //调整次数大了，说明mid小了，要往大搜
		
	}
	
	printf("%lld\n", s2-s1);
	return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！祝大家 AC！

---

## 作者：Cutler (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF671B)

**简化题意**

每次把最大值减一，最小值加一，问 $\texttt k$ 次后的极差。

看到这个题面，首先想到线段树或者模拟，但看到这个数据范围 $1 \le n \le 500000,0 \le k \le 10^9$。

额，打扰了。

面对这种毒瘤范围，我们现在面临两种选择，一种是二分答案，一种是直接 $O(1)$ 求。我们考虑前者（~~后者我不会~~）。

既然是二分，那肯定要先确定二分的对象，最后我们需要得出 $Max - Min$，但又不太可能直接二分这个值，所以我们分别二分出 $Max$ 和 $Min$，最后相减出答案。

思路已经清晰，那具体怎么二分呢。我们来看这个罗宾汉每次在干什么，其实就是让最大值尽可能小，最小值尽可能大，我们就可以用二分来模拟这个过程，求出**最小的最大值**和**最大的最小值**。

嗯，嗯，那现在我们可以开始写代码了吗？显然不能，我们还缺最重要的一部分：$\texttt{check}$ 函数。

我们以最大值为例，想要让最后的最大值为我们想要的那个数，要满足什么呢？我们设这个数为 $\texttt x$，因为每次罗宾汉只能把最大值减少一，就有 **所有大于 $\texttt x$ 的数与 $\texttt x$ 的差之和要不大于 $\texttt k$**，即

$$
\sum_{i=1}^{n}\max(c_i-x,0) \le k
$$

最小值也同理，每次只能把最小值加一，即有

$$
\sum_{i=1}^{n}\max(x-c_i,0) \le k
$$

这样我们就解决了这个问题，但这样还不够优雅，我们还可以通过缩小值域的方法提高效率。根据罗宾汉的行为易得

1. 最后的最大值一定不小于平均值，不大于最开始的最大值。
  
2. 最小值同理，不大于平均值，不小于最开始的最小值。

然后我们就优雅的解决了这个问题。
  
代码如下：
  

```cpp
#include<bits/stdc++.h>

using namespace std;
const int Maxn = 5e5+10;

#define int long long
int n, k, c[Maxn], maxn, minn, sum, Max, Min(1e15);

bool check1(int x){
    int cnt = 0;
    for(int i = 1;i <= n;++ i)
        cnt += max(c[i] - x, 0ll);
    return cnt <= k;
}
bool check2(int x){
    int cnt = 0;
    for(int i = 1;i <= n;++ i)
        cnt += max(x - c[i], 0ll);
    return cnt <= k;
}

signed main(){
    scanf("%lld%lld",& n,& k);
    for(int i = 1;i <= n;++ i)
        scanf("%lld", c + i),sum += c[i],
        Max = max(Max, c[i]),Min = min(Min, c[i]);

    int l = (sum + n - 1) / n,r = Max;\\最大值的值域要考虑整除，不整除的要+1
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check1(mid)) maxn = mid,r = mid - 1;
        else l = mid + 1;
    }
    l = Min,r = sum / n;\\最小值直接除就行
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check2(mid)) minn = mid,l = mid + 1;
        else r = mid - 1;
    }
    printf("%lld\n", maxn - minn);
    return 0;
}
```

优雅撒花。

---

