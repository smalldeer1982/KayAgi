# Zero Array

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ .

In one operation you can choose two elements $ a_i $ and $ a_j $ ( $ i \ne j $ ) and decrease each of them by one.

You need to check whether it is possible to make all the elements equal to zero or not.

## 说明/提示

In the first example, you can make all elements equal to zero in $ 3 $ operations:

- Decrease $ a_1 $ and $ a_2 $ ,
- Decrease $ a_3 $ and $ a_4 $ ,
- Decrease $ a_3 $ and $ a_4 $

In the second example, one can show that it is impossible to make all elements equal to zero.

## 样例 #1

### 输入

```
4
1 1 2 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
NO```

# 题解

## 作者：Mysterious_Mini (赞：9)

这是本蒟蒻的第 $3$ 篇题解。
### 思路：
本题有两个关键要素：

$1.$ 数列中有奇数个奇数时，输出 $NO$。

$2.$ 数列中的最大数大于其它所有数的总和时，输出 $NO$。

接下来是两个要素的证明部分：

证明 $1$：

两个数一起减 $1$，总和减 $2$，相当于奇偶性不变。若数列中每个数之和为偶数，最后奇偶性也会与 $0$ 相同（$0$ 是偶数）。反之，最后也会变成奇数，永远也不能得到 $0$。

证明 $2$：

设这个数列中有 $n$ 个数：$a_1$，$a_2$，……，$a_n$。

∵ $a_n$ > $a_1$ + $a_2$ + …… + $a_{n-1}$

∴ $a_n$ - $a_1$ + $a_2$ + …… + $a_{n-1}$ > $0$

由上可知，$a_n$ 把 $a_1$，$a_2$，……，$a_{n-1}$ 都熬到了 $0$，而它自己却还是正整数，永远也不会变成 $0$。
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n, a, sum, maxa;
int main()
{
    //输入，预处理
    scanf("%lld", &n);
    for(long long i = 1; i <= n; i++)
    {
        scanf("%lld", &a);
        sum += a; //加和
        maxa = max(maxa, a); //循环比较求最大数
    }
    //核心思路
    if(sum % 2 == 1 || sum < 2 * maxa) printf("NO");
    else printf("YES");
    
    return 0;
}
```
### 坑：
开 $long$ $long$：十年 $OI$ 一场空，_______________。

这里我稍微解释一下，看似 $a_i$ 最大才到 $10^9$，但是数列的项数能达到 $10^5$。$sum$ 最大可以达到 $10^9$ · $10^5$ = $10^{14}$，超了 $int$，所以需要开 $long$ $long$。

[AC](https://www.luogu.com.cn/record/46788926)：最优解第四名。

求过+求赞QwQ

---

## 作者：Mubuky (赞：4)

# _**CF1201B Zero Array 题解**_ 

![](https://api.gushi.ci/all.svg)

**首先分享一下做完这道题（ _Pretest Passed_ ）的感受:**

>  _**蓝瘦香菇**_ 

发生了什么呢？困倦的我（借口），先做B题，首先想到了这是一道结论题，并且很快（并没有花费时间）的写出了完美（异想天开）的代码，CODEFORCES的比赛拼的就是速度，于是我过了样例就正确的（无脑的）点击了提交,果然（我先前并不知道而去看了A），Wrong ans on test 9.

>  _**懵逼的令人喷饭**_ 

我想到并提交的结论是:

 _**The sum of the elements must be even.**_ 

**所有数相加和为偶数（奇数的个数为偶数）**

**证明（虚假的证明）：**

 _At each turn, take the maximum element and the minimum element, and reduce each by 1. At this point the second point still holds true._ 

 _Consider the case when the maximum element got reduced by 1, and it became not the maximum. Then the sorted array looks like this:_ 

 _.....,x,x−1._ 

 _Since the total sum is still even, there is another positive element (≥1), apart from these two. Then x≤(x−1)+ "some elements, at least one of which is 1". So the second point still holds, and we continue with x as the maximum element._ 

代码：
```cpp
#include<cstdio>
#define max(a,b) a>b?a:b
int main()
{
	int n;
	scanf("%d",&n);
	int a,sum=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		if(a%2){
			sum++;
		}
	}
	printf("%s",sum%2==0?"YES":"NO");
	return 0;
}
```
WA后丧心病狂的我疯狂提交，甚至还写了一个模拟（恐怖）,结果TLE on test 5.

我渐渐变得理智（更加丧心病狂）,左思右想.....**终于，功夫不负有心人!**

我发现自己可以用下面这组数据HACK掉我自己的程序

```cpp
3
1 2 5
```
它满足和为偶数（奇数的个数为偶数），但是就1和5消变为2 4,2和4消变为2，且我们知道自己不能和自己消（不能自减2），所以最后不能变为0。

>那怎么办呢？

哦！我们终于可以发现：

 _**The biggest element have to be less or equal than the sum of all the other elements.**_ 

**最大的数必须小于等于所有数之和的一半（最大元素必须小于或等于所有其他元素的总和）**

**证明（虚假的证明）:**

 _The problem statement instructs us to pick 2 distinct indices and reduce each element by 1. Suppose the point in consideration "The biggest element has to be less or equal than the sum of all the other elements." were to be false. Let this biggest element be at index i. For all other indices j, if we pick (i, j) as our pair and reduce their values by 1, we should be able to see that it won't be possible to reduce the largest element to 0._ 

题意指示我们选择2个不同的元素，并将每个元素减少1。假设考虑中的条件“最大元素必须小于或等于所有其他元素的总和。”是错误的。把这个最大的元素记为元素i。对于所有其他的任一元素j，如果我们选择（i，j）作为我们的依照题意所配的对，并将它们的值减少1，我们能够发现将最大元素减少到0是不可能的。

总结：

 _**There are 2 things needed to be possible to make all elements zero:**_ 

 _**1: The sum of the elements must be even.**_ 

 _**2: The biggest element have to be less or equal than the sum of all the other elements.**_ 

 _**If both are true, the answer is "YES", otherwise "NO".**_ 

**达成题意有以下两个条件：**

**1：所有数相加和为偶数（奇数的个数为偶数）**

**2：最大的数必须小于等于所有数之和的一半（最大元素必须小于或等于所有其他元素的总和）**

**如果以上两个条件都满足，那么答案就是" _YES_ "，反之则是" _NO_ "。**

我在想出所有条件后，非常的开心...（只是一道Div.2的水题而已）,本着CODEFORCES时间优先的原则快速乱搞了一通代码，写出了代码结构和变量名混乱的代码，不过 _Pretest Passed_ 还是令人欣喜，如下：

```cpp
#include<cstdio>
#define max(a,b) a>b?a:b
int main()
{
	int n,sum1=0,sum2=0;
	long long sum=0,maxnum=0;
	scanf("%d",&n);
	if(n==2){
		int a,b;
		scanf("%d %d",&a,&b);
		if(a==b){
			printf("YES");
		}else{
			printf("NO");
		}
	}else{
		int a;
		for(int i=1;i<=n;i++){
			scanf("%d",&a);
			sum+=a;
			maxnum=max(maxnum,a);
			if(a%2){
				sum1++;
			}
		}
		if(maxnum*2>sum){
			printf("NO");
		}else{
			printf("%s",sum1%2==0?"YES":"NO");
		}
	}
	return 0;
}
```

但是为了利于大家正确的学习，我把看起来舒服的程序放在下面

**标程：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, a, s;
int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n;
    for (ll i=1; i<=n; i++)
    {
        cin>>a;
        s+=a;
        m=max(m, a);
    }
    if (s%2==1 || s<2*m)
    {
        cout<<"NO";
        return 0;
    }
    cout<<"YES";
    return 0;
}
```

另外吐槽一下，今天凌晨这场Div.2，欢乐ABC做起来还以为是Div.3，做到D题有点炸，看到E就想骂人...对于E和E2（Div.2中的Div.1？）...佩服!!

_**Name:** [Codeforces Round #577 (Div. 2)](https://codeforces.com/contest/1201)_ 

 _**Writers:** [SPatrik](https://codeforces.com/profile/SPatrik)_ 

 _**Start:** Aug/05/2019 00:35 UTC+8_ 

 _**Length** 02:00_ 

##  _**By Mubuky**_ 


---

## 作者：Zechariah (赞：1)

杰论：当整个数组和为偶数时一定可以全消成0  
特殊情况：有一个特别大的数，比其他所有数的和都大

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 2e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll a[N], sum;

int main() {
	rg int n = fast_IO::read();
	for (rg int i = 1; i <= n; ++i)sum += (a[i] = fast_IO::read());
	sort(a + 1, a + n + 1);
	if ((sum & 1) || (a[n] << 1) > sum)puts("NO");
	else puts("YES");
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15366905.html)

# 题目大意

给定一个数列，这个数列有 $n$ 个数，你可以对数列进行任意次操作。操作定义为：

* 在数列中选择两个数 $a_{i}$，$a_{j}(i\neq j,1\le a_i,a_j\le10^9)$，将它们的值分别减 $1$。

求若干次操作后该数列的 $n$ 个数是否可能都为 $0$。可能则输出 $\textsf{YES}$，否则输出 $\textsf{NO}$。

# 题目分析

## 结论及相关证明

**$\boxed{1}:$ 输出答案为 $\textsf{NO}$，当有奇数个奇数时。**

证明结论 $\boxed{1}:$

不妨设序列中有 $2k+1(1\le k\le\left\lfloor\dfrac{n-1}{2}\right\rfloor\texttt{~且~}k\texttt{~为正整数})$ 个奇数，并且这些奇数挤在一堆（不影响结果），分别为 $A_1,A_2,\cdots,A_{2k},A_{2k+1}$。

由于这些奇数的和（即 $\sum\limits_{i=1}^{2k+1}A_i$）一定为奇数，那么我们将这一堆奇数不停地减去 $2$，最后一定会剩余一个奇数；

而不论有多少偶数，最后都不可能得到一个奇数，所以就不可能与其抵消。

得证。

举个例子：

一个序列为 `3,5,7,9,11,2,10`，如果不停地执行操作，最后一定会变成这个样子 `0,0,0,0,0,0,1`。

**$\boxed{2}:$ 输出答案为 $\textsf{NO}$，当 $\max~a_i >\sum\limits_{i=1}^{n}a_i-\max~a_i$，即数列中的最大值严格大于其它所有数的总和时。**

证明结论 $\boxed{2}:$

先将序列中所有数升序排列。

$\because a_n>a_1+a_2+\cdots+a_{n-1}$

两边同时减去 $a_1+a_2+\cdots+a_{n-1}$ 不等式仍成立：

$\therefore a_n-a_1-a_2-\cdots-a_{n-1}>0$

很明显不可能，于是得证。

----
时间复杂度 $\Theta(N)$

# 代码

```cpp
//2021/10/4

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <algorithm> 

#define int long long 

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=100005;

const int INF=0x3f3f3f3f3f3f3f3f;

int a[ma];

#undef int

int main(void)
{
	#define int long long
	
	int n=read();
	
	int sum(0),maxx=-INF;
	
	int num(0);
	
	for(register int i=1;i<=n;i++)
	{
		a[i]=read();
		
		if(a[i]%2==1)
		{
			num++;
		}
		
		sum+=a[i];
		
		maxx=max(maxx,a[i]);
	}
	
	sum-=maxx;
	
	if(maxx>sum)
	{
		cek("NO");
	}
	
	else if(num%2==1)
	{
		cek("NO");
	}
	
	else
	{
		puts("YES");
	}
	
	return 0;
}
```

---

## 作者：Need_No_Name (赞：0)

# Solution for CF1021B

## 题意：

给定一个序列 $a$，现可以选择 $a_i$， $a_j$ $(i ≠j)$ 让这两个数同时减一。求经过若干次操作这个序列可不可以都为 $0$ 。

## 思路：

想了半天，才发现是一道~~大水题~~思维性很高的题（瞎扯）

分两种情况

1.容易想到，当序列中有奇数个奇数时，也就是序列的和为奇数时，将无法成功。因为在总和中，每次减少的是 $2$ ，所以如果数组的和是奇数话，无法实现。

2.在数组中，最大的数要大于其它数的和时，无法实现。这种情况下，就算你把其它数都给去掉了时，最大的那个数却依然没有减完，故无法实现。

## 代码

就记录数组的最大值，数组的和即可。

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 1e5 + 10;
int n, a[N], sum = 0, maxx = 0;
signed main()
{
	cin >> n;
	maxx = -99999;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum += a[i];
		maxx = max(maxx, a[i]);
	}
	if(sum & 1 || sum - maxx < maxx) cout << "NO" << endl;
	else cout << "YES" << endl;
	return 0;
}
```


---

## 作者：fjy666 (赞：0)

### 0x01 思路
定义：$\texttt{sum}$ 为数组总和，$\texttt{max}$ 为最大值。  
我们先来考虑不能减到 $0$ 的情况。
- $\boxed{2\nmid\texttt{sum}}$   
不证自明。
- $\boxed{\texttt{max}\times 2  > \texttt{sum}}$  
如果 $\texttt{max}\times2>\texttt{sum}$ ,那么即使其他所有数都和 $\texttt{max}$ 拼掉，$\texttt{max}$ 也会剩余，显然不行。

其他情况都可以将数组减到 $0$。  
时间复杂度：$\Theta(n)$

------------
### 0x02 代码
```cpp
/*
Time:2021/1/31
Author:fjy666
*/
#include <cstdio>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define rtn return

typedef long long ll;
ll sum,max,tmp;
int main()
{
	int n;
	scanf("%d",&n); 
	fo(i,1,n)
	{
		scanf("%lld",&tmp);
		sum += tmp;
		if(tmp > max)max = tmp;
	}
	if((sum&1) || (max * 2 > sum))puts("NO");
	else puts("YES");
	rtn 0;
}
```
代码很短，主要考思维。

---

## 作者：WinterRain208 (赞：0)

### CF1201B Zero Array 题解

题意：

给你一个数列，每次把这个数列中任意两个数减一，问最后能不能把所有数变成$0$。

注意，这两个数不能为同一个数。

题意分析：

这是一道判断题，我们看完题面来推推什么情况下会无解。

无解之一：

```cpp
4
1 1 2 3
```
减到最后一定有一个数等于一，所以无解。

造成无解的原因是什么呢？

所有数总和为$7$，是个奇数，每次减去$2$不可能减完。

抓紧写代码！

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

long long a,n,ans=0;
int main(){
	scanf("%d",&a);
	F(i,1,a){
		scanf("%d",&n);
		ans+=n;
	}
	puts(ans%2==0?"YES":"NO");
   return 0;
}

```

$WA$了。

如楼上苣佬所说的，还有别的无解情况。

无解之二：

```
2
2 4
```
总和是偶数啊！可是每次操作没得选只能是他们两个，二变成零后四变成二，没得减了，也无解。

造成这种情况的原因就是数列中有一个数太大了，其他数加起来都没有他大，这时候，其他数变成$0$时，他还不是$0$。

这时我们把这个最大的数独自分为一组，其他也分为一组。

但是可以等于，两边正好完全抵消了。

抓紧写代码！

### $UGLY$ $CODE$
```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

long long a,n,ans=0,M=-1;
int main(){
	scanf("%d",&a);
	F(i,1,a){
		scanf("%d",&n);
		ans+=n,M=max(M,n);
	}
	puts(ans%2==0&&M<=ans/2?"YES":"NO");
    return 0;
}

```

蒟蒻结束。

有任何错误欢迎各位苣佬批斗。

$wtrl$。

---

## 作者：kenlig (赞：0)

来个友好的题解。

考虑一种情况：如果总和是奇数呢？那么怎么减都减不了，这题显然是NO

再考虑一种情况：如果我存在一个很大的数，大于其他所有的数和呢？那所有的数加起来都消不了这个大数，也是NO

考虑这两种情况，和long long

Code:
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define LL long long
#define maxn 100001
using namespace std;
LL n,a[maxn],tot,maxx;
int main(){
    cin>>n;
    for(LL i=1;i<=n;i++){
        cin>>a[i];
        tot+=a[i];
        maxx=max(a[i],maxx);
    }
    if(tot%2==1||maxx*2>tot) cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    return 0;
}
```


---

## 作者：くろねこ (赞：0)

~~大胆猜想, 敢于实践, 罚时算个ball~~

题意很明确, 选$2$个不同的数各自减$1$, 最后能不能让数列全是$0$.

首先我们发现: 每次操作数列的和固定减$2$, 到最后数列的和减为$0$. 显然, 若数列的和最初为奇数则肯定不能通过每次减$2$达到$0(odd$ $mod$ $2$ $== 1)$, 这时我们输出$NO$.

然后是和为偶数的情况. 我们~~很容易就能~~想到若数列最大值大于数列和的一半, 则数列的和肯定不会为$0$. 若最大值大于数列和的一半, 我们每次用其它$n - 1$个数和最大值操作, 其它$n - 1$个数的和显然小于数列和的一半, 最后数列的最大值定有剩余$($相当于两个值作差$)$, 这时我们也输出$NO$.

然后我们输出$YES$就$AC$了~~整个room都是这个写法完全没hack的机会~~

```cpp
int main()
{
	read(n);
	for (rg int i = 1; i <= n; ++i) read(a[i]), sum += a[i], maxx = max(maxx, a[i]);
	if (sum & 1)
	{
		puts("NO");
		return 0;
	}
	if (maxx * 2 > sum)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	return 0;
}
```


---

