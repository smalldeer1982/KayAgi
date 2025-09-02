# Block Towers

## 题目描述

Students in a class are making towers of blocks. Each student makes a (non-zero) tower by stacking pieces lengthwise on top of each other. $ n $ of the students use pieces made of two blocks and $ m $ of the students use pieces made of three blocks.

The students don’t want to use too many blocks, but they also want to be unique, so no two students’ towers may contain the same number of blocks. Find the minimum height necessary for the tallest of the students' towers.

## 说明/提示

In the first case, the student using two-block pieces can make a tower of height $ 4 $ , and the students using three-block pieces can make towers of height $ 3 $ , $ 6 $ , and $ 9 $ blocks. The tallest tower has a height of $ 9 $ blocks.

In the second case, the students can make towers of heights $ 2 $ , $ 4 $ , and $ 8 $ with two-block pieces and towers of heights $ 3 $ and $ 6 $ with three-block pieces, for a maximum height of $ 8 $ blocks.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5 0
```

### 输出

```
10
```

# 题解

## 作者：Melon_Musk (赞：10)

[CF626C Block Towers 题面](https://www.luogu.com.cn/problem/CF626C)

写完发现这题题解里没有我的做法，感觉这个做法更简单实用，故分享给大家。

## 分析

因为每个人的塔的高度要不相同，假设只有 2 层 2 层往上搭的话，那么很显然每个人只要都比前面的人多搭 2 层即可，所以n个人搭的高度为 2 * n 。

![](https://cdn.luogu.com.cn/upload/image_hosting/61tuogm6.png)

只有 3 层往上搭的同理，高度为 3 * m。

我们记 n 个 2 层 2 层往上搭的人的总高度为 sum1 ， m 个 3 层 3 层往上搭的人的总高度为 sum2 。

所以一开始我们先令 sum1 = 2 * n , sum2 = 3 * m。

而本题同时有 2 层搭的和 3 层搭的，此时我们注意到，当第三个搭 2 层的人和第二个搭3层的人的高度均为 6 。

![](https://cdn.luogu.com.cn/upload/image_hosting/5nysk573.png)

所以此时，我们应该把其中一个人让他再叠 2 层或 3 层使两人高度不再重合。

而当一个人又叠了一次之后，他之后的所有人都得往上再叠一次，所以可以理解为 sum1 的值增加了 2 或者 sum2 的值增加了 3。为了使结果最小，我们当然会增加当前值较小的一个使总结果更小。

而当层数是 6 的倍数时，就会有这样的一次重合，本题数据告诉我们可以暴力枚举。

本题的答案为 min ( sum1 , sum2 ) 。

## 参考代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,sum1,sum2;
int main()
{
	scanf("%d%d",&n,&m);
	sum1=n*2;sum2=m*3;
	while(n>=3 && m>=2)
	{
		if(sum1+2<=sum2+3) sum1+=2,n++;   //注意这里我们把sum1的层数加了1次，所以要n++!
		else sum2+=3,m++;
		n-=3,m-=2;
	}
	printf("%d\n",max(sum1,sum2));
	return 0;
}
```


---

## 作者：SummerFlyFly (赞：7)

竟然没有人写题解！！！\
写一篇题解来填补这个空缺\
这道题的思想非常简单，个人觉得评级偏高\
至于如何考虑这个问题，可以自行尝试人工试验。\
二分答案，然后进行实际判断即可\
上代码（二分写得很丑，勿见怪）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int lf=1,rg=5000000,n,m,md=(lf+rg)/2,ans;
int main()
{
	scanf("%d%d",&n,&m);
	while(rg-lf>1)
	{
		int k=0,s=1;
		int p=2*n,q=3*m;
		if(p>md)
		{
			s=0;
		}
		int pp=0,qq=0;
		if(p<md&&s)
		{
			pp=(md-p)/2;
		}
		if(q>md&&s)
		{
			s=0;
		}
		if(q<md&&s)
		{
			qq=(md-q)/3;
		}
		k=pp+qq;
		if(s)
		{
			if(k>=md/6)
			{
				s=1;
			}
			else
			{
				s=0;
			}
		}
		if(s==1)
		{
			rg=md;
			md=(lf+rg)/2;
		}
		else
		{
			lf=md;
			md=(lf+rg)/2;
		}
	}
	int k=0,s=1;
	int p=2*n,q=3*m;
	if(p>lf)
	{
		s=0;
	}
	int pp=0,qq=0;
	if(p<lf&&s)
	{
		pp=(lf-p)/2;
	}
	if(q>lf&&s)
	{
		s=0;
	}
	if(q<lf&&s)
	{
		qq=(lf-q)/3;
	}
	k=pp+qq;
	if(s)
	{
		if(k>=lf/6)
		{
			s=1;
		}
		else
		{
			s=0;
		}
	}
	if(s==1)
	{
		ans=lf;
	}
	else
	{
		ans=rg;
	}
	printf("%d",ans);
}
```


---

## 作者：Bpds1110 (赞：1)

水蓝了属于是。

考虑已经得到答案 $s$。

要求高度各不相同，则至少有 $n$ 个 $2$ 的倍数在 $[1,s]$ 中，为 $n$ 个塔的高度，即要满足 $\left \lfloor \frac{s}{2}  \right \rfloor \ge n$。同理，至少有 $m$ 个 $3$ 的倍数在 $[1,s]$ 中，满足 $\left \lfloor \frac{s}{3}  \right \rfloor \ge m$。如果当前数为 $6$ 的倍数，实际上被算了 $2$ 次，于是考虑计算总塔数是否满足。把 $\left \lfloor \frac{s}{2}  \right \rfloor$ 和 $\left \lfloor \frac{s}{3}  \right \rfloor$ 容斥一下，得 $\left \lfloor \frac{s}{2}  \right \rfloor + \left \lfloor \frac{s}{3}  \right \rfloor - \left \lfloor \frac{s}{6}  \right \rfloor \ge n + m$。

$0 \le n,m \le 10^6$，完全可以暴力，枚举每个答案 $s$。输出满足条件中最小的即可。

```cpp
#include <bits/stdc++.h>

int main()
{
	int n, m;
 	std::cin >> n >> m;
 	for (int i = 1; ; ++ i)
 		if (i / 2 >= n && i / 3 >= m && i / 2 + i / 3 - i / 6 >= n + m)
 			return std::cout << i, 0;
	return 0;
}

```


---

## 作者：Fat_Fish (赞：1)

我们在读题时，发现了 **最高的塔高度的最小值** 这几个字，很明显的**二分**特征。并且要**各不相同**。

**思路：**我们可以二分**最高塔的高度**。我们设$x$为最高塔的高度，可以缩小范围的条件如下：

- $x/2 \geq n$ 

- $x/3 \geq m$ 

- $x/2 + x/3 -x/6 \geq n+m$ 

对于第三条，因为要各不相同，所以 $lcm(2,3) = 6$ 的倍数只能有一个，所以最后算的时候要减掉。最后不断二分即可。代码还是很好写的。

Code: 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+100;
int n,m,t,a[maxn];
bool check(int x){//最高塔的高度
	if(x/2>=n&&x/3>=m&&x/2+x/3-x/6>=m+n){//符合条件
		return true;
	}
	return false;
}
signed main(){
	cin>>n>>m;
	int l=0,r=6000000;//r开到2*3*1000000
	while(l+1<r){
		int mid=l+r>>1;//取中间值
		if(check(mid)){
			r=mid;//看看能不能更小
		}else {
			l=mid;//否则一定更大
		}
	}
	if(check(l)){
		cout<<l<<'\n';//先看看小的能不能
	}else if(check(r)){
		cout<<r<<'\n';//再看大的
	}
	return 0;
}
```


---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF626C)

我的思路是枚举每一个数字，$sum1$ 表示所有由 $2$ 块搭起来的人当中已经确定高度的人数，$sum2$ 表示由 $3$ 块搭起来的人当中已经确定高度的人数。

如果该数字是 $2$ 的倍数且不是 $6$ 的倍数时让 $sum1$ 加一，如果该数字是 $3$ 的倍数且不是 $6$ 的倍数时让 $sum2$ 加一。

如果该数字是 $6$ 的倍数时判断是 $sum1$ 离 $n$ 的差距多还是 $sum2$ 离 $m$ 的差距多，如果 $sum1$ 离 $n$ 的差距多就优先把这个数字让给由 $2$ 块搭起来的人，$sum1$ 加一，否则给由 $3$ 块搭起来的人，$sum2$ 加一。注意，这里如果 $n-sum1=m-sum2$ 时要把该数让给由 $3$ 块搭起来的人，因为如果 $2$ 的多出来那么最大数只需再加 $2$，但如果是 $3$ 多出就得再加 $3$，明显更亏。

当然，$sum1$ 要小于等于 $n$ 且 $sum2$ 要小于等于 $m$。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bitset<100000010> b;
int sum1=0,sum2=0;
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=1e8;i++)
		if(!(i%2)&&!(i%3))
		{
			if(sum1==n&&sum2==m) break;
			if(sum1==n) sum2++,b[i]=1;
			else if(sum2==m) sum1++,b[i]=1;
			else if((n-sum1)>(m-sum2)) sum1++,b[i]=1;
			else sum2++,b[i]=1;
		}
		else if(!(i%2)&&sum1<n) sum1++,b[i]=1;
		else if(!(i%3)&&sum2<m) sum2++,b[i]=1;
	for(register int i=1e8;i>=1;i--) if(b[i]){printf("%d",i);break;}
	return 0;
}
```

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF626C)

# 题意

一群人在搭建积木塔。有 $N$ 个人 $2$ 块 $2$ 块往上搭，有 $M$ 个人 $3$ 块 $3$ 块往上搭，每个人塔的高度都要大于 $0$，且高度各不相同，问最高的塔高度的最小值。

# 思路

依次枚举答案 $i$。

-  $i$ 要塞下 $n$ 个 $2$ 的倍数，因此 $n\le i/2$。
- 同理 $m\le i/3$
-  $2$ 的倍数和 $3$ 的倍数都选，容斥一下，$n+m\le i/2+i/3-i/6$

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(i=1;;i++)
        if(i/2>=n&&i/3>=m&&i/2+i/3-i/6>=n+m)
            return cout<<i,0;
    return 0;
}
```


---

## 作者：SilverLi (赞：0)

[Block Towers の 传送门](https://www.luogu.com.cn/problem/CF626C)

我们发现两种积木搭起来重叠**当且仅当为 $6$ 倍数**。

为什么？因为 $6$ 是 $2,3$ 的最小公倍数。

再发现 $n,m\leq10^6$，就只用枚举高度。

```cpp
#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("avx2")
int n,m;
signed main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;true;++i)
		if(i/2>=n&&i/3>=m&&
		i/2+i/3-i/6>=n+m) {cout<<i;	return 0;}
	return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：0)

发现自己在 114514 年前交了一个输出样例的代码试图骗分（

于是看了看这道题。

### 题面

> 一群人在搭建积木塔。有 $n$ 个人搭的塔必须是 $2$ 的倍数，有 $m$ 个人搭的塔必须是 $3$ 的倍数。每个人塔的高度都要大于 $0$，且高度各不相同，问最高的塔高度的最小值。 $0\le n,m\le 10^6$ 。

### 做法

考虑最终答案 $x$ 应该满足什么条件。首先，$x$ 以下要能塞下 $n$ 个 $2$ 的倍数，故 $n\le\left\lfloor\dfrac{x}{2}\right\rfloor$。同理可知 $m\le\left\lfloor\dfrac{x}{3}\right\rfloor$。

然后考虑最多有多少塔。$2$ 的倍数和 $3$ 的倍数都可以选，因此容斥一下是 $\left\lfloor\dfrac{x}{2}\right\rfloor+\left\lfloor\dfrac{x}{3}\right\rfloor-\left\lfloor\dfrac{x}{6}\right\rfloor$，那么总共的塔数应满足 $n+m\le\left\lfloor\dfrac{x}{2}\right\rfloor+\left\lfloor\dfrac{x}{3}\right\rfloor-\left\lfloor\dfrac{x}{6}\right\rfloor$。

注意到 $n,m\le 10^6$ ，答案显然不会超过 $10^7$，因此枚举答案 $x$ 即可。

代码很短，感觉评分偏高了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=10000000;i++)
		if(n<=i/2&&m<=i/3&&n+m<=i/2+i/3-i/6){
			printf("%d\n",i);
			return 0;
		}
	return 0;
}
```

---

## 作者：hank0402 (赞：0)

提供一个简单的做法。

upd：将 $k$ 改成了 $p$，~~本人眼瞎~~

[题目传送门](https://www.luogu.com.cn/problem/CF626C)

首先，我们设答案为 $p$，则 $p$ 至少要等于 $\max(2\times n,3\times m)$ ，这个应该很好想，因为有 $n$ 个人两块两块搭，至少有 $2\times n$ 种可能，而有 $m$ 个人三块三块搭，至少有 $3 \times m$ 种可能，如果这些答案都有重合的话，$p$ 的最小值就是 $\max(2\times n,3\times m)$.

按照前面的思路，假设有 $p$ 种答案，两个两个搭，应有 $\frac{p}{2}$  种，显然 $\frac{p}{2}$ 要大于等于 $n$，而三个三个搭，应有 $\frac{p}{3}$ 种，显然 $\frac{p}{3}$ 也要大于等于 $m$，这两种重合的种数，即 $\frac{p}{6}$ 种，加起来一共是 $\frac{p}{2}+\frac{p}{3}-\frac{p}{6}$ 种，这样，我们结合前面的最小值，就可以枚举 $p$ 的大小，如果不满足将 $p$ 加 $1$ 即可。

**Code**:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	int p = max(3 * m, 2 * n);
	while(! ((p / 2 >= n) && (p / 3 >= m) && (p / 2 + p / 3 - p / 6 >= n + m))) p ++;
	cout << p;
	return 0;
}
```

---

