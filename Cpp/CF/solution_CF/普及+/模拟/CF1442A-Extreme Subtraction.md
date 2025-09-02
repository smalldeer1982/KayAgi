# Extreme Subtraction

## 题目描述

You are given an array $ a $ of $ n $ positive integers.

You can use the following operation as many times as you like: select any integer $ 1 \le k \le n $ and do one of two things:

- decrement by one $ k $ of the first elements of the array.
- decrement by one $ k $ of the last elements of the array.

For example, if $ n=5 $ and $ a=[3,2,2,1,4] $ , then you can apply one of the following operations to it (not all possible options are listed below):

- decrement from the first two elements of the array. After this operation $ a=[2, 1, 2, 1, 4] $ ;
- decrement from the last three elements of the array. After this operation $ a=[3, 2, 1, 0, 3] $ ;
- decrement from the first five elements of the array. After this operation $ a=[2, 1, 1, 0, 3] $ ;

Determine if it is possible to make all the elements of the array equal to zero by applying a certain number of operations.

## 样例 #1

### 输入

```
4
3
1 2 1
5
11 7 9 6 8
5
1 3 1 3 1
4
5 2 1 10```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：_Ezreal (赞：15)

## $\mathsf {Solution\space to \space CF1442A}$
因为操作是对连续序列进行 $-1$，考虑到求出原序列的差分数组 $a$，每次操作就是对差分数组中两个数一个 $+1$，一个 $-1$ 。又由于题目对操作序列有限制，对于从最左边开始的操作序列，每次 `a[1]--`，然后对任意一个 `a[i]++` （$2\le i \le n+1$）；同理，从右边开始的操作序列，只需要将 `a[i]--,a[n+1]++`（$1\le i \le n$）。

因为对 `a[n+1]` 的操作并没有什么卵用，而 `a[i]--` 的操作也只针对大于零的 `a[i]`，所以只需要将差分数组中所有小于 $0$ 的数的绝对值加起来 ，检查是否小于等于 $a[1]$ 即可。
```
# include <cstdio>

const int N=1e5+5;
int a[N];
int n;

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		for(int i=n;i>=1;i--)
		a[i]-=a[i-1];
		
		int sum=0;
		for(int i=2;i<=n;i++)
		if(a[i]<0) sum-=a[i];
		
		if(a[1]>=sum)
		printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```

---

## 作者：LeavingZzz (赞：9)

# $\mathsf{Solution\space For\space CF1442A}$  
Upd：修复了~~因为喝假酒造成的~~两处小笔误，感谢@wwldx 提出
## $\mathsf{Description}$  
给出一个长度为 $n$ 的序列，每次操作你可以选择一个 $k$，然后将这个序列的前 $k$ 个元素**或者**后 $k$ 个元素一起减一，求问可不可以将其变成一个全部为 $0$ 的序列。  
## $\mathsf{Analysis}$  
把题目略略转化一下  
我们称选取前 $k$ 个元素一起减一为从前面减掉，选取后 $k$ 个元素一起减一为从后面减掉。  
现在给你两个初始全部是 $0$ 的序列，那么从前面减掉的时候就把第一个序列的前 $k$ 个元素一起加一，从后面减掉的时候就把第二个序列的后 $k$ 个元素一起加一，不妨称这两个序列分别为 **前序列** 和 **后序列**。  

然后你会发现 **前序列** 一定是单调不增的，而 **后序列** 一定是单调不减的。  
这个也很好发现，对于前序列中的一个元素 $a_i$ 来说，如果 $a_i$ 要加一，那么位置在 $i$ 之前的元素一定也都要加一次，所以前序列是单调不增的，后序列同理。  

所以题目现在转化为这样的一个问题：  
给出一个序列 $\{a\}$ ，问是否能构造一个单调不减的序列 $\{inc\}$ 和一个单调不增的序列 $\{dec\}$ 使得对于 $\forall i\in [1,n]$ 都有 $a_i=inc_i+dec_i$ 而且 $dec_i\ge0$。  

接下来贪心地构造即可  
对于两个序列的第一个元素，因为其和为 $a_1$，为了让这两个序列尽量的长，我们要让单调不减的序列的值尽量小，单调不增的序列的值尽量大，所以 $inc_1=0,dec_1=a_1$  

接下来考虑 $dec_2$  
首先要有 $dec_2\le dec_1$  
其次因为 $dec_2+inc_2=a_2$ 所以 $dec_2\le a_2$  
最后要让 $inc_2\ge inc_1$，所以 $dec_2\le a_2-inc_1$  

在满足这三个限制的情况下让 $dec_2$ 最大，直接取 $dec_2=min(dec_1,a_2-inc_1)$ 即可  
如果 $dec_2<0$ 那么没办法构造出合法的 $\{inc\}$ 和 $\{dec\}$，无解。（我都用了最优策略了你还是便乘负的了那还能怎么办啊QAQ）  
然后直接令 $inc_2=a_2-dec_2$  
依次构造 $dec_3$ 即可  

如果能构造出两个序列的话，那么有解，否则无解。  
## $\mathsf{Code}$ 
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;
const int maxn=30007;
int T,N;
int A[maxn],inc[maxn],dec[maxn];
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=1;i<=N;i++)
            scanf("%d",&A[i]);
        dec[1]=A[1];
        inc[1]=0;
        bool f=true;
        for(int i=2;i<=N;i++)
        {
            dec[i]=min(dec[i-1],A[i]-inc[i-1]);
            if(dec[i]<0) {f=false;break;}
            inc[i]=A[i]-dec[i];
        }
        if(f) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：LEle0309 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1442A)

一看题面，~~很快看出~~经教练提醒是**差分**。

### 神马是差分？（大佬自行跳过）

差分是创建一个数组 $ d $，其中 $ d_i $ 是给出数组 $ a $ 中 $ a_i-a_{i-1} $ 的值。

代码：
```cpp
d[i]=a[i]-a[i-1];
//从1开始（从0开始会访问a[-1])
```
#### 差分的重要作用：区间修改

把区间 $ [l,r] $ 中的每个数加 $ x $。

因为两个数同时加 $ x $，差不变，所以差分数组的值也不变，**因此只要改差分数组的首尾**，即 $ d_l $ 加上 $ x $，$ d_{r+1} $ 减去 $ x $，时间复杂度 $ O(1) $。

### 分析：

设原数组为 $ a $，差分数组为 $ d $。

为了让每一项都是 $ 0 $，那么差分数组也是 $ 0 $，且 $ d_1 $ 是 $ 0 $。

- 对于操作 $ 1 $：改变前 $ k $ 个数，让它们减 $ 1 $，则 $ d_{i+1} $ 加上 $ 1 $，$ d_1 $ 减去 $ 1 $，则可以把差分数组中的负数变成 $ 0 $，同时把 $ d_1 $ 减 $ 1 $。

- 对于操作 $ 2 $：改变后 $ k $ 个数，让它们减 $ 1 $，则 $ d_{i+1} $ 减去 $ 1 $，$ d_{n+1} $ 加上 $ 1 $，则可以把差分数组中的正数变成 $ 0 $，而 $ d_{n+1} $ 完全不关我们事。

最初，$ d_1 $ 与 $ a_1 $ 相等。所有正数我们都不用管，因为正数变 $ 0 $ 不影响 $ d_1 $，而负数变 $ 0 $ 则会影响 $ a_1 $。而我们要让 $ a_1 $ 变成 $ 0 $，则有以下两种情况。

设 $ d $ 数组中负数之和的绝对值为 $ s $。

- $ s \le a_1 $，则 $ d $ 数组中所有数变为 $ 0 $ 后，$ d_1 $ 还是大于等于 $ 0 $，此时在通过操作 $ 2 $ 把 $ d_1 $ 变成 $ 0 $，所以直接输出 `YES`。

- $ s>a_1 $，则 $ d $ 数组中的数要变为 $ 0 $ 时，$ d_1 $ 就会小于 $ 0 $，而没有把 $ d_1 $ 从负数变成 $ 0 $ 的操作。操作 $ 2 $ 只能把 $ d_1 $ 从正数变成 $ 0 $，所以直接输出 `NO`。

```cpp
#include<iostream>
using namespace std;
const int maxn=3e4+7;
int t,a[maxn],d[maxn],n,s,i,ans;
int main()
{
	cin>>t;
	while(t--)//t组数据
	{
		cin>>n;ans=0;s=0;//多测不清空，提交两行泪（WA了一次QAQ）
		for(i=1;i<=n;i++)//输入
		{
		    cin>>a[i];
			d[i]=a[i]-a[i-1];//求差分数组
		}
		for(i=2;i<=n;i++)if(d[i]<0)s+=(-1*d[i]);//差分数组中负数绝对值之和
		if(s<=a[1])cout<<"YES\n";//情况1
		else cout<<"NO\n";//情况2
	}
	return 0;//完结撒花！
}
```

---

## 作者：tommymio (赞：2)

### 题意

你有一个序列 $a$，你可以进行 $2$ 种操作：

- 选择前 $k$ 个数，将它们全部减 $1$。
- 选择后 $k$ 个数，将它们全部减 $1$。
- 每次操作的 $k$ 可以不同。

问是否可以把通过若干次操作整个序列变为全是 $0$ 的序列。

$\texttt{Data Range:}t\leq 30000,\sum n \leq 30000,a_i \leq {10}^6$

### 分析

我们分析半天，似乎可以得到一堆错误结论看上去很对（雾

不妨尝试规约一下这个问题。我们设 $x_i$ 为选择左边 $i$ 个数 $-1$ 的次数，$y_i$ 为选择右边 $i$ 个数 $-1$ 的次数。由于对于 $a_i$ 而言，能够影响到 $a_i$ 的左边的操作 $k$ 都满足 $k\geq i$，能够影响到 $a_i$ 的右边的操作都满足 $k\leq i$，并且 $a_i$ 会被影响 $a_i$ 次。因此我们可以得到一组约束：
$$
\begin{cases}
\sum\limits_{j=1}^nx_j+\sum\limits_{j=1}^1y_j=a_1,
\\
\sum\limits_{j=2}^nx_j+\sum\limits_{j=1}^2y_j=a_2,
\\
...
\\
\sum\limits_{j=n}^nx_n+\sum\limits_{j=1}^ny_j=a_n,
\\
\forall i\in[1,n],x_i,y_i\in N
\end{cases}
$$
这组约束似乎不大好做，没关系，我们从差分的角度来考虑它。

对于 $i\in [2,n]$，我们将 $\sum\limits_{j=i}^nx_j+\sum\limits_{j=1}^iy_j=a_i$ 与 $\sum\limits_{j=i-1}^nx_j+\sum\limits_{j=1}^{i-1}y_j=a_{i-1}$ 相减，得到 $y_i-x_{i-1}=a_i-a_{i-1}$，这个约束是对于 $\forall i\in [2,n]$ 都成立的。

如果只有差分的这部分约束，我们会将约束变松。加入原约束中未被考虑进差分的柿子即可。于是有：
$$
\begin{cases}
\forall i\in[2,n],y_i-x_{i-1}=a_i-a_{i-1},
\\
\sum\limits_{j=1}^nx_j+y_1=a_1,
\\
\sum\limits_{j=1}^ny_j+x_n=a_n,
\end{cases}
$$
事实上无论在上述的约束中，无论哪一个约束都不关心 $y_1,x_n$ 具体的值，只关心其和 $y_1+x_n\in N$。并且，由于 $y_i$ 的值仅与 $x_{i-1}$ 与 $a_{i}-a_{i-1}$ 有关，使得我们可以任意构造一组 $x,y$。

根据上述分析，$\sum\limits_{j=1}^nx_j+y_1=a_1$ 可换为 $\sum\limits_{j=1}^{n-1} x_j\leq a_1$，$\sum\limits_{j=1}^ny_j+x_n=a_n$ 可换为 $\sum_{j=2}^n\limits y_j\leq a_n$。将两个等式转化为不等式后，我们发现可以贪心构造出一组 $x,y$，正确性相当显然。

最后鸣谢 @盧鋅，是他帮我完善了这个非常理性的解法（

时间复杂度 $O(\sum n)$。

```cpp
#include<cstdio>
typedef long long ll;
int a[30005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
int main() {
    int T=read();
    while(T--) {
        int n=read();
        ll sumx=0,sumy=0;
        for(register int i=1;i<=n;++i) a[i]=read();
        for(register int i=2;i<=n;++i) {
            int del=a[i]-a[i-1];
            if(del>=0) sumy+=del;
            else sumx+=del;
        }
        if(sumy<=a[n]&&sumx<=a[1]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```



---

## 作者：ql12345 (赞：2)

## 全局观想思路

#### 题意：

给一个序列，每次可将从头开始的若干连续元素-1，或以尾结束的若干连续元素-1，是否可以将整个序列变为全0

#### Solution：

我自己在考场上想到：两边大于靠中间一个的数是没有贡献的，削成一样，然后看中间高出的部分是否都一样，发现不对，于是发现中间高出的部分可以是凹凸形的，只要满足凸出的两边“尖”可以消去即可，于是就复杂了。。。

假如我不那么心急，咱们从后面的思路开始想：

两边“尖”是否可消去可记录一个需要消去的总数，与最两边的大小比较，这本身就可以转化为**差分**，对于开始想的两边，也可用这个思路**统一**起来：“如果第二个比第一个小，可以看做第一个加上第二个的差分”，这就是将全局的问题统一起来了，接着解决这个问题

可以发现，如果加差分加到小于0，肯定是不行的，只需判断是否小于0即可

疑问：我在考场上想的是两边一块解决“削尖”问题，怎么变成开头解决，结尾的贡献不算在内了呢？其实不是的，可以发现，结尾不管把后面的怎么削，前面的“尖”是不会受到影响的，也就是说它们是**相互孤立的**，所以这个疑问就解决了！

实现：直接按找前面说的思路，差分，从前到后扫一遍即可

#### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 233333;

int b[N];

signed main()
{
	int t;
	cin >> t;
	while(t --)
	{
		int n, lst = 0;
		cin >> n;
		for(int i = 1, a; i <= n; ++i) cin >> a, b[i] = a - lst, lst = a;
		
		int flag = 1, sum = b[1];
		for(int i = 2; i <= n; ++i)
			if(b[i] < 0)
				if((sum += b[i]) < 0) flag = 0;
		
		puts(flag ? "YES" : "NO");
		
		for(int i = 1; i <= n; ++i) b[i] = 0;
	}
	
	return 0;
}
```

---

## 作者：b6e0_ (赞：1)

题目链接：<https://www.luogu.com.cn/problem/CF1442A>

不太需要差分数组吧，不太需要那么多的分析吧。

首先是一个很显然的结论：可以将这个数组变为全 $0$ 当且仅当可以将这个数组变得全部相等。充分性：如果全部相等，那么选择前缀（或后缀） $n$ 个数一直做就行；必要性：如果全 $0$，全 $0$ 也是全部相等的一种。

考虑将相邻的两个数 $a_x$ 和 $a_{x+1}$ 变相等。如果 $a_x<a_{x+1}$，那么只靠前缀操作是一定无法变相等的，不管怎样都需要在 $x+1$ 处做 $a_{x+1}-a_x$ 次后缀操作。类似地，如果 $a_x>a_{x+1}$，那么需要在 $x$ 处做 $a_x-a_{x+1}$ 次前缀操作。于是我们只需要对于每一对相邻的数，判断能否做这么多操作即可。维护前缀 $\min$ 和后缀 $\min$，判断要做的操作次数是否小于等于这个 $\min$ 值，如果小于就把这个 $\min$ 减去要做的次数，否则输出 `NO`。代码：
```cpp
#include<bits/stdc++.h>
using namepace std;
int a[30005];
int main()
{
	int T,n,i,minv;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(i=1;i<=n;i++)
			cin>>a[i];
		minv=1000005;
		for(i=1;i<n;i++)//前缀
		{
			if(a[i]>a[i+1]&&minv<a[i]-a[i+1])
				break;
			minv=min(minv,a[i])-max(0,a[i]-a[i+1]);//记得减去做的次数
		}
		if(i<n)//如果循环条件还满足时就退出了说明是break出来的
		{
			puts("NO");
			continue;
		}
		minv=1000005;
		for(i=n;i>1;i--)//后缀
		{
			if(a[i]>a[i-1]&&minv<a[i]-a[i-1])
				break;
			minv=min(minv,a[i])-max(0,a[i]-a[i-1]);
		}
		if(i>1)
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}
```

---

## 作者：_Winham_ (赞：1)

其实这一题只要多点思考，代码实现就不难了。

-----------
思路：

首先先运用差分的方法，求出序列 $a$ 的升与降。

接下来就开始遍历这个序列：

1. 先初始变量 $ans$ 为第一个 $a_1$ 的高度。

1. 开始一个循环，从 $2$ 遍历到 $n$（作者代码中确实把初始定义放在了 $i$ 等于 $1$ 的情况下）。

1. 当 $sum_i$ 为负数时，在判断一下如果 $ans$ 加上 $sum_i$ 为负数时，就输出 `NO`。

1. 每次$sum_i$ 为负数时 $ans$ 加上 $sum_i$。（$sum$ 存差分的值， $sum_i$ 为第 $i$ 个的高度）。

1. 当循环结束是没有输出过 `NO`，就输出 `YES`。

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define LL long long
const int N = 2e5+10;
const int INF = 0x3f3f3f3f;
int sum[N],a[N],n;
signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i = 1;i<=n;i++){
			cin>>a[i];
			sum[i]=a[i]-a[i-1];
		}
		bool f=1;
		int ans=0;
		for(int i=1;i<=n;i++){
			if(i==1){
				ans=sum[i];
				continue;
			}
			if(sum[i]<0){
				if((ans+sum[i])<0){
					f=0;
					cout<<"NO"<<endl;
					break;
				}
				ans+=sum[i];
			}
		}
		if(f)cout<<"YES"<<endl;
		
	}
	
	return 0;
}

```

---

## 作者：Refined_heart (赞：0)

题目大意：要求对给定序列进行前缀$-1$或后缀$-1$问能不能让原序列变成全$0$序列。

$Solution:$

考虑前缀减所能消成$0$的一定是一个不增序列，后缀减反之。

那么我们考虑将两种操作拆开并转化为加法，这样我们把目标转化为构造一个不升一个不降序列使得对应位置的和$=a[i].$

那么考虑贪心地构造：让递增序列的每一项尽量小，递减序列的每一项尽量大。设其分别为$A[i],B[i].$

则$A[1]=0,B[1]=a[1].$

考虑限制：

$B[i+1]\leq B[i]$

$B[i+1]\leq a[i+1]-A[i]$

第二个限制是因为 $B[i+1]+A[i+1]=a[i+1],A[i+1]\ge A[i].$

所以两者取$\min$即可。最后扫一下看一看$B$里面有没有负数（负数不合法，因为序列$A,B$定义是不能出现负数的）。有负数就无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200010];
int inc[200010],ddec[200010];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		ddec[1]=a[1],inc[1]=0;
		for(int i=2;i<=n;++i){
			ddec[i]=min(ddec[i-1],a[i]-inc[i-1]);
			inc[i]=a[i]-ddec[i];
		}
		int f=0;
		for(int i=1;i<=n;++i)if(ddec[i]<0)f=1;
		if(f==1)puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1442A)

------------
# 思路：
将此题目转化成一个差分问题。要使数组中的全部数都为 $0$，那么差分数组也必须为 $0$ 且 $d_1 = 0$。

那么我们来看两种操作对于差分数组有何影响：

操作 $1$：```d[1]−1``` 且 ```d[i+1]+1```。那么我们就可以凭借操作 $1$，将差分数组中的负数变成 $0$，同时减小 $d_1$。

操作 $2$：```d[i+1]−1``` 且 ```d[n+1]+1```。那么我们就可以凭借操作 $2$，将差分数组中的正数变成 $0$，而 $d_{n+1}$ 为多少和我们并没有关系。

在最开始时 $d_1=a_1$，所以只要差分数组的负数和的绝对值小于等于 $a_1$,即输出 ```YES```，否则输出 ```NO```。

------------
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,a[N],b[N],s;
signed main(){
	cin>>T;
	while(T--){
		s=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			a[i]=b[i]=0;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=a[i]-a[i-1];
		}
		for(int i=2;i<=n;i++){
			if(b[i]<0){
				s-=b[i];
			}
		}
		if(s<=a[1]){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```
完结撒花~

---

