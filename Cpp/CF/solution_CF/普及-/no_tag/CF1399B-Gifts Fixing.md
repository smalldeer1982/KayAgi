# Gifts Fixing

## 题目描述

You have $ n $ gifts and you want to give all of them to children. Of course, you don't want to offend anyone, so all gifts should be equal between each other. The $ i $ -th gift consists of $ a_i $ candies and $ b_i $ oranges.

During one move, you can choose some gift $ 1 \le i \le n $ and do one of the following operations:

- eat exactly one candy from this gift (decrease $ a_i $ by one);
- eat exactly one orange from this gift (decrease $ b_i $ by one);
- eat exactly one candy and exactly one orange from this gift (decrease both $ a_i $ and $ b_i $ by one).

Of course, you can not eat a candy or orange if it's not present in the gift (so neither $ a_i $ nor $ b_i $ can become less than zero).

As said above, all gifts should be equal. This means that after some sequence of moves the following two conditions should be satisfied: $ a_1 = a_2 = \dots = a_n $ and $ b_1 = b_2 = \dots       = b_n $ (and $ a_i $ equals $ b_i $ is not necessary).

Your task is to find the minimum number of moves required to equalize all the given gifts.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, we can perform the following sequence of moves:

- choose the first gift and eat one orange from it, so $ a         = [3, 5, 6] $ and $ b = [2, 2, 3] $ ;
- choose the second gift and eat one candy from it, so $ a =         [3, 4, 6] $ and $ b = [2, 2, 3] $ ;
- choose the second gift and eat one candy from it, so $ a =         [3, 3, 6] $ and $ b = [2, 2, 3] $ ;
- choose the third gift and eat one candy and one orange from it, so $ a = [3, 3, 5] $ and $ b = [2, 2, 2] $ ;
- choose the third gift and eat one candy from it, so $ a =         [3, 3, 4] $ and $ b = [2, 2, 2] $ ;
- choose the third gift and eat one candy from it, so $ a =         [3, 3, 3] $ and $ b = [2, 2, 2] $ .

## 样例 #1

### 输入

```
5
3
3 5 6
3 2 3
5
1 2 3 4 5
5 4 3 2 1
3
1 1 1
2 2 2
6
1 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1
3
10 12 8
7 5 4```

### 输出

```
6
16
0
4999999995
7```

# 题解

## 作者：Edmundino (赞：5)

# 题意

给你两个数组 $a$ 和 $b$，你可以有三种操作:

1. $a_i--$
2. $b_i--$
3. $a_i--,b_i--$

使得 $a$ 的每一个数相等，$b$ 的每一个数相等，问你最少的操作次数。

# 分析

其实就是把 $a$ $b$ 数组变成那个数组中最小的数。

首先我们先找到这个最小的数，

$a$ 数组是 $mina$, $b$ 数组是 $minb$,


然后算出每一项与这个最小的数的差，

最后在遍历整个两个数组，

总操作数 $s$ 就加上 $\max(a_i-mina,b_i-minb)$。

最后输出即可

# 代码

**核心部分**

```cpp
//x[i]即a[i],y[i]即b[i],zs即s
void solve()
{
	while(m--)
	{
		cin>>n;
		zs=0;
		minx=1e9+50;
		miny=1e9+50;
		for(int i=0;i<n;i++)
		{
			cin>>x[i];
			if(minx>x[i])
			{
				minx=x[i];
			}
		}
		for(int i=0;i<n;i++)
		{
			cin>>y[i];
			if(miny>y[i])
			{
				miny=y[i];
			}
		}
		for(int i=0;i<n;i++)
		{
			c[i]=x[i]-minx;
			d[i]=y[i]-miny;
			zs+=max(c[i],d[i]);
		}
		cout<<zs<<endl;
	}
    
}
```


---

## 作者：引领天下 (赞：3)

显然最后的所有的 $a_i$ 一定是原先 $a_i$ 中最小的一个。（因为只能吃掉不能加上）。

同理 $b_i$ 也一定是原先 $b_i$ 中最小的一个。

那么直接暴力统计就好了。

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int t,n,a[55],b[55];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);int mn1=1<<30,mn2=1<<30;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),mn1=min(mn1,a[i]);
        for(int i=1;i<=n;i++)scanf("%d",&b[i]),mn2=min(mn2,b[i]);
        long long cnt=0;
        for(int i=1;i<=n;i++)cnt+=max(a[i]-mn1,b[i]-mn2);//如果a[i]和b[i]，那么所耗费的操作次数一定是两边的操作的最大值：可以先使用若干次一起减小，最后再单独减小。
        printf("%lld\n",cnt);
    }
    return 0;
}
```

---

## 作者：Lylighte (赞：2)

#### CF1399B Gifts Fixing 题意~~简~~述

给定长度同为 $n$ 的数组 $a$ 和数组 $b$，每次你可以进行以下操作之一（$1\le i\le n$）：

1. $a_i \gets a_i-1$
2. $b_i \gets b_i -1$
3. 同时进行 $a_i \gets a_i-1$ 和 $b_i \gets b_i -1$

当然 $a$ 和 $b$ 始终满足 $a_i,b_i\ge 0$。现在要求经过若干次操作后使得 $a_1 = a_2 = \cdots a_n$ 并且 $b_1 = b_2 = \cdots b_n$，不一定需要使得 $a_i=b_i$，求出最少的操作次数。

输入：$t$ 组数据（$1\le t\le 1000$），每组数据包括：第一行一个整数 $n$（$1\le n\le 50$），第二行 $n$ 个数，第 $i$ 个数表示 $a_i$（$1\le a_i\le 10^9$），第三行 $n$ 个数，第 $i$ 个数表示 $b_i$（$1\le b_i\le 10^9$）。

输出：对于每组数据，输出最少的操作次数。

#### 思路~~简~~述

操作次数最少，应使得 $a_i$ 尽可能大，所以这个最大值是数组 $a$ 中的最小值，记作 $x$，数组 $b$ 同理，最小值记作 $y$。

然后对于每一个 $i$，分别计算 $a_i-x$ 和 $b_i-y$ 的值。显然，如果两数同大于 $0$，可以进行 $\min\{a_i-x,b_i-y\}$ 次操作 3 以减少操作次数，再进行 $\max\{a_i-x,b_i-y\}-\min\{a_i-x,b_i-y\}$ 次操作 1 或者 2（取决于 $a_i-x$ 和 $b_i-y$  的大小关系），总计操作次数为 $\max\{a_i-x,b_i-y\}$，并累加。

最后输出这个累加值即可。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[110], b[110], dpa[110], dpb[110];
int t, n;
long long ans;

inline void real_main(){
	ans = 0;
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<n; ++i)
		cin >> b[i];
	dpa[0] = a[0];
	dpb[0] = b[0];
	for(int i=1; i<n; ++i){
		dpa[i] = min(dpa[i-1], a[i]);
		dpb[i] = min(dpb[i-1], b[i]);
	}//注1
	for(int i=0; i<n; ++i){
		ans += max(a[i]-dpa[n-1], b[i]-dpb[n-1]);
	}
	cout << ans << endl;
}

int main(){
	cin >> t;
	while(t>0){
		--t;
		real_main();
	}
	return 0;
}

```

注 1：

记 $\texttt{dpa}_i$ 为 $a_1,a_2,\cdots,a_i$ 中的最小值，则 $\texttt{dpa}_1=a_1$，$\texttt{dpa}_i=\min\{\texttt{dpa}_{i-1},a_i\}$，~~这是世界上最简单的 DP 题~~。

因为 $\texttt{dpa}_i$ 的值只与 $\texttt{dpa}_{i-1}$ 和 $a_i$ 有关，而且只需要保存 $\texttt{dpa}_n$ 的值，所以可以把 DP 的一维数组压成~~零维数组~~，即一个变量。

然而代码中数组元素是从下标 0 开始存的……

---

## 作者：GBLoi (赞：1)

a修改后剩下的值 $a'=min(a[1],a[2],...,a[n])$ ;

b修改后剩下的值 $b'=min(b[1],b[2],...,b[n])$ ;

对于每一个 $a[i],b[i]$ ：

- 尽量用操作3，因为 操作3=操作1+操作2，使用操作3的次数为 $min(a[i]-a',b[i]-'b)$

- 使用完后需要再使用操作1 $a[i]-min(a[i]-a',b[i]-b')-a'$ 

- 再使用操作2 $b[i]-min(a[i]-a',b[i]-b')-b'$ ,当然这二者有一个为0

- 总共 $tot[i]=min(a[i]-a',b[i]-'b)+a[i]-min(a[i]-a',b[i]-b')-a'+b[i]-min(a[i]-a',b[i]-b')-b'$ $= a[i]-a'+b[i]-b'-min(a[i]-a',b[i]-b')$ 

  $= max(a[i]-a',b[i]-b')$

- $ans=\sum_{i=1}^{n} tot[i]=\sum_{i=1}^{n} max(a[i]-a',b[i]-b')$ 

Code:

```cpp
#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
const int INF=2e9+5,N=56;
int T,n;
int a[N],b[N];
int mina,minb;
LL ans;
int main()
{
	int i;
	scanf("%d",&T);
	while(T--) {
		mina=minb=INF; ans=0;
		scanf("%d",&n);
		for(i=1;i<=n;i++) 
			scanf("%d",&a[i]),mina=min(a[i],mina);
		for(i=1;i<=n;i++)
			scanf("%d",&b[i]),minb=min(b[i],minb);
		for(i=1;i<=n;i++) 
			ans+=(LL)max(b[i]-minb,a[i]-mina);
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：Histone (赞：1)

### 题意概要：

给你两个数组 **a** 和 **b** 

每一步你可以执行以下的操作之一

- ${a_i}$ 减一

- ${b_i}$ 减一

- ${a_i}$ 和 ${b_i}$ 都减一

使得数组 **a** 中各元素相等，数组 **b** 中各元素也相等，且不能出现负数值

求所需的最小步数

### 思考ing：

这题看上去有点像个模拟啊

要想数组里面相等，还只能执行自减的操作，那么找到每个数组中的最小值

把其余的数都减到那个最小值不就好了？

### 一些细节：

注意第三个操作，我们在减的时候

如果两个数组中某一对可以一起减，那我们就尽量一起减

求所需的最小步数嘛

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;

inline int read(){
	re int ans = 0;re bool f = 1;re char ch = getchar();
	while(ch<'0'||ch>'9'){if (ch=='-')f = 0;ch = getchar();}
	while(ch>='0'&&ch<='9'){
		ans = (ans<<3)+(ans<<1)+(ch^48);
		ch = getchar();
	}
	return f?ans:~(ans-1);
}

signed main(void){
	int t = read();
	while(t--){
		int a[128],b[128],ans = 0,n=read();
		int ma = 1e16,mb = 1e16;
		for(re int i=1;i<=n;++i){a[i]=read();ma = min(a[i],ma);}
		for(re int i=1;i<=n;++i){b[i]=read();mb = min(b[i],mb);}//这两行，读入数据并找最小值
	
		for(re int i=1;i<=n;++i)
			if(a[i]-ma>0&&b[i]-mb>0)//如果可以一起减，那么步数加上两者消耗步数的最大值
				ans+=max(a[i]-ma,b[i]-mb);
			else if(a[i]-ma>0&&b[i]-mb<=0)//单独的情况
				ans+=a[i]-ma;
			else if(b[i]-mb>0&&a[i]-ma<=0)//单独的情况
				ans+=b[i]-mb;

		printf("%lld\n",ans);
	}
	return 0;
}
```

非常简单的一道题，无脑模拟QAQ

水题解的Histone

测试 [用时30ms](https://www.luogu.com.cn/record/36461013)

---

## 作者：Error_Eric (赞：1)

### 前言

竟然没人发题解？

### 正解

有以下三种决策:

- 把 $a_i$ **减** $1$。

- 把 $b_i$ **减** $1$。

- 把 $a_i,b_i$ 都**减** $1$。

显然想要使$a_1=a_2=...=a_n,b_1=b_2=...=b_n$ ，需要使 $a$中的每个元素变为 $\min a_i$,$b_i$中每个元素变为$\min b_i$。

那么显然在每一个 $i$，操作数最小为 $\max{(a_i-mina,b_i-minb)}$

代码就很容易出来了。

### 注意

不开 ``long long`` 见祖宗。

### code

```
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define maxll 9223372036854775807
long long t,n,a[100],b[100],ans=0,mina,minb;
int main(){
    scanf("%lld",&t);//输入数据组数
    while(t--){//每一组
        mina=maxll,minb=maxll,ans=0;//先要初始化
        scanf("%lld",&n);//还要输入
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]),mina=min(mina,a[i]);//输入+枚举最小值。
        for(int i=1;i<=n;i++)scanf("%lld",&b[i]),minb=min(minb,b[i]);//输入+枚举最小值
        for(int i=1;i<=n;i++)ans+=max(a[i]-mina,b[i]-minb);//显然
        printf("%lld\n",ans);//显然
    }
    return 0;//显然
}
```

---

## 作者：lndjy (赞：0)

因为可以两个都减，所以对于一个二元组，只需要考虑和目标相差最大的，另一个顺便就减了。

又因为不存在加，所以只能减到最小值。答案就是每个二元组和最小值的差的较大值的和。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
int a[100],b[100];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		for(int i=1;i<=n;i++)
		cin>>b[i];
		long long ans=0,mina=1e15,minb=1e15;
		for(int i=1;i<=n;i++)
		{
			mina=min(mina,a[i]);
			minb=min(minb,b[i]);
		}
		for(int i=1;i<=n;i++)
		ans+=max(a[i]-mina,b[i]-minb);
		cout<<ans<<endl;
	}
	return 0;
}
//此题解祭第一次自己号打CF。
```

---

## 作者：KSToki (赞：0)

题目大意是给你两个长为$n$的数组$a$,$b$，对于正整数$i(1\le i\le n)$，有以下三种操作：1、将$a_i$减一；2、将$b_i$减一；3、将$a_i$和$b_i$都减一。问最少经过多少次操作使$a$中所有数相等且$b$中所有数也相等。

显然，我们的目标是将$a$中的所有数变成原来$a$中最小的数，$b$同样。那么针对每个$i(1\le i\le n)$，先计算出$a_i$与目标数$mina$的差，记为$xa$和$b_i$与目标数$minb$的差，记为$xb$。我们可以先进行$min(xa,xb)$次操作$3$使得某一个数先达到目标数，然后差距较大的数再进行$max(xa,xb)-min(xa,xb)$次操作达到目标数，总共需要$max(xa,xb)$次。模拟即可。

注意答案可能超int。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,a[51],b[51];
bool f;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		    flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		ll ans=0;
		int mina=0x7fffffff,minb=0x7fffffff;
		for(register int i=1;i<=n;++i)
			a[i]=read(),mina=min(mina,a[i]);
		for(register int i=1;i<=n;++i)
			b[i]=read(),minb=min(minb,b[i]);
		for(register int i=1;i<=n;++i)
		{
			int xa=a[i]-mina;
			int xb=b[i]-minb;
			ans+=max(xa,xb);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：dead_X (赞：0)

## 题意
给定 $n$ 个礼物，每个礼物有 $a_i$ 个苹果和 $b_i$ 个橘子。你可以执行一次操作，即吃掉任意一个礼物中的一个苹果，一个橘子或两者各一个。你需要用最小操作数使得所有礼物的 $a_i,b_i$ 都相等。
## 思路
显然最后相等的 $a_i$ 和 $b_i$ 都是原来的最小值，那么记 $a_i$ 最小值为 $x$，$b_i$ 最小值为 $y$ 每一个礼物需要的操作数就是 $min(a_i-x,b_i-y)$，$O(n)$ 预处理，$O(n)$ 统计答案即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define qwq int T=read(); while(T--)
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003],b[1000003];
int main()
{
	qwq
	{
		long long ans=0;
		int n=read(),Min1=1000000003,Min2=1000000003;
		for(int i=1; i<=n; i++) a[i]=read(),Min1=min(Min1,a[i]);
		for(int i=1; i<=n; i++) b[i]=read(),Min2=min(Min2,b[i]);
		for(int i=1; i<=n; i++) ans+=max(a[i]-Min1,b[i]-Min2);
		printf("%lld\n",ans);
	}
    return 0;
}
//By dead_X
```

---

## 作者：Doubeecat (赞：0)

## [CF1399B. Gifts Fixing](https://codeforc.es/contest/1399/problem/B)

> 给你两个数列 $a,b$,有三种操作：让$a_i - 1$,让$b_i - 1$,让 $a_i - 1,b_i - 1$
> 
> 求让 $a_1 = a_2 = \dots = a_n$,$b_1 = b_2 = \dots = b_n$ 的最少操作次数。
>
> $T \leq 1000,n \leq 50$

### 思路

贪心题。

首先分析题目，发现是要将数列变得两两相等，而且操作只有减，所以我们可以将数列中的最小值 $a_{min},b_{min}$ 作为"基准",剩下的工作就是让每个元素都等于 $a_{min}$ 或 $b_{min}$

我们可以贪心思考一下

- 如果 $a_i > a_{min},b_i > b_{min}$,则设 $p = \min(a_i,b_i)$
 
  将 $a_i - p,b_i - p$, $p$ 累积到答案里。

- 如果 $a_i > a_{min},b_i = b_{min}$,则 $a_i - (a_i - a_{min})$ , 将 $(a_i - a_{min})$ 累积到答案里

- 如果 $a_i = a_{min},b_i > b_{min}$,则 $b_i - (b_i - b_{min})$ , 将 $(b_i - b_{min})$ 累积到答案里

这样就做完了。

```cpp

const int N = 100010;
int a[N],n,b[N],aa[N],bb[N];

signed main() {
	int T;read(T);
	while (T--) {
		read(n);
		for (int i = 1;i <= n;++i) read(a[i]),aa[i] = a[i];
		for (int i = 1;i <= n;++i) read(b[i]),bb[i] = b[i];
		sort(aa+1,aa+1+n);
		sort(bb+1,bb+1+n);
		int p1 = aa[1],p2 = bb[1];
		int ans = 0;
		for (int i = 1;i <= n;++i) {
			if (a[i] > p1 && b[i] > p2) {
				int delta = min(a[i]-p1,b[i]-p2);
				ans += delta;
				a[i] -= delta,b[i] -= delta;
			}
			if (a[i] > p1) {
				ans += a[i] - p1;
				a[i] = p1;
			}
			if (b[i] > p2) {
				ans += b[i] - p2;
				b[i] = p2;
			}
		} 
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：0)

首先，我们考虑两个数组分别减到什么位置。

因为只能减，不能加，所以小的元素不能变成大的，只能把所有元素减到这里的最小值。我们需要把两个数组分别求个 min 值，然后求出答案。

答案怎么求呢？对于一个 $(a,b)$，我们如果想把它减到 $(mina,minb)$，两个元素分别要减 $a-mina,b-minb$ 下。如果两个元素都可以减，那么就都减一下，这个部分的价值是 $min(a-mina,b-minb)$。然后还剩下一个没有减完的元素，是 $max(a-mina,b-minb)-min(a-mina,b-minb)$。两部分的加和就是 $max(a-mina,b-minb)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55],b[55];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int ma=2147483647,mb=2147483647;
		long long ans=0;
		for(int i=1;i<=n;i++)cin>>a[i],ma=min(ma,a[i]);
		for(int i=1;i<=n;i++)cin>>b[i],mb=min(mb,b[i]);
		for(int i=1;i<=n;i++)if(a[i]>ma||b[i]>mb)ans+=max(a[i]-ma,b[i]-mb);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

