# Dark Assembly

## 题目描述

Dark Assembly is a governing body in the Netherworld. Here sit the senators who take the most important decisions for the player. For example, to expand the range of the shop or to improve certain characteristics of the character the Dark Assembly's approval is needed.

The Dark Assembly consists of $ n $ senators. Each of them is characterized by his level and loyalty to the player. The level is a positive integer which reflects a senator's strength. Loyalty is the probability of a positive decision in the voting, which is measured as a percentage with precision of up to $ 10% $ .

Senators make decisions by voting. Each of them makes a positive or negative decision in accordance with their loyalty. If strictly more than half of the senators take a positive decision, the player's proposal is approved.

If the player's proposal is not approved after the voting, then the player may appeal against the decision of the Dark Assembly. To do that, player needs to kill all the senators that voted against (there's nothing wrong in killing senators, they will resurrect later and will treat the player even worse). The probability that a player will be able to kill a certain group of senators is equal to $ A/(A+B) $ , where $ A $ is the sum of levels of all player's characters and $ B $ is the sum of levels of all senators in this group. If the player kills all undesired senators, then his proposal is approved.

Senators are very fond of sweets. They can be bribed by giving them candies. For each received candy a senator increases his loyalty to the player by $ 10% $ . It's worth to mention that loyalty cannot exceed $ 100% $ . The player can take no more than $ k $ sweets to the courtroom. Candies should be given to the senators before the start of voting.

Determine the probability that the Dark Assembly approves the player's proposal if the candies are distributed among the senators in the optimal way.

## 说明/提示

In the first sample the best way of candies' distribution is giving them to first three of the senators. It ensures most of votes.

It the second sample player should give all three candies to the fifth senator.

## 样例 #1

### 输入

```
5 6 100
11 80
14 90
23 70
80 30
153 70
```

### 输出

```
1.0000000000
```

## 样例 #2

### 输入

```
5 3 100
11 80
14 90
23 70
80 30
153 70
```

### 输出

```
0.9628442962
```

## 样例 #3

### 输入

```
1 3 20
20 20
```

### 输出

```
0.7500000000
```

# 题解

## 作者：vеctorwyx (赞：1)

### ~~远古CF也不简单嘛~~

首先吐槽阴间题面。

dfs + 概率计算

~~呜呜呜我不会数学~~

分糖：暴力枚举，复杂度是$O(k^{n+1})$

重点在通过的概率上：

先想最暴力的计算方法：按概率把每种情况都枚举出来然后求总体。

总体时间复杂度：$O((10^n*k^{n+1})$，会TLE。

1. 剪枝：

	分析情况发现每位议员只有两种情况：同意和不同意。
    
    那么每次枚举只枚举同意或不同意，然后计算答案时再乘概率，时间复杂度就变成了$O((2^n*k^{n+1}))$。
    
    ~~但是怎么算着还是TLE的啊~~。
    
2. 继续剪枝：

	调试一下发现其实每一种分糖情况都会被算K次，那么让每次分糖都之分给上一次分的议员已经他后面的议员，保证不出现重复。
    
    这时候的时间复杂度就是$O(2^n * k^{?})$，~~其实是我不会算了~~，其中能保证“$?$”一定比$n$小不少，（如果有哪位大佬知道这里的实际复杂度请私信我$Orz$）。
    
3. 怎么算概率

	- 如果有至少$\lceil n/2 \rceil$位议员同意则概率为当前概率；
    
    - 如果不足$\lceil n/2 \rceil$位议员同意则需要把当前概率乘$\Large \frac{A}{A+B} $；
    
    最后把所有情况的$ans$取个$\max$就是答案了。
    
code：

```
#include<bits/stdc++.h>
#define int long long//十年OI一场空，不开longlong见祖宗
using namespace std;
int n,m,k,a[10],e[10];
long double ans, ans1;
void dfs(int x,int dat,int cnt,int b){
	if(x == n + 1){
		if(cnt > n / 2)
		ans += dat * 1.0;
		else
		ans += dat * k * 1.0 / (k + b);
		return;
	}
	dfs(x + 1, dat * e[x] / 10 , cnt + 1, b);
	dfs(x + 1, dat * (100 - e[x]) / 10, cnt, b + a[x]);
}
void dfs1(int x, int pre){
	if(x > m){
		ans = 0;
		dfs(1, 1, 0, 0);
		ans1 = max( ans1 , ans /(pow(10, n)) );
		return;
	}
	for(int i = pre; i <= n ; i++){
		if(e[i] == 100)
			continue;
		e[i] += 10;
		dfs1(x + 1, i);
		e[i] -= 10;
	}
}
signed main(){
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++)
		cin >> a[i] >> e[i];
	int dui = 0;
	dfs1(1, 0);
	printf("%.10Lf", ans1);
}
```

由于~~玄学原因~~，我的代码只能在CF上C++17才能通过，~~而洛谷没有C++17选型~~（别问我原因，~~我也不知道~~）。

---

## 作者：lemondinosaur (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF105B)

[CODEFORCES传送门](http://codeforces.com/problemset/problem/105/B)

---
题目强调贿赂要在投票开始前完成说明分糖和成功率可以分开计算

那么分糖考虑直接暴搜，由于题目并没有说糖必须全部分完，

所以每一次分完一颗糖后均要求当前状态下的成功率

那成功率怎么求呢，考虑暴搜每个议员是否赞同或反对，

当赞同人数超过一半时，成功率为当前概率，否则要乘上 $\frac{A}{A+B}$ ，

这样按照题目要求算出成功率，最后取最大值

---
```cpp
#include <cstdio>
#define rr register
using namespace std;
int n,mid,A,a[11],b[11],k; double ans;
inline void ev(int dep,int cnt,double pro,int deny,double &sum){
	if (!pro) return;
	if (dep==n){
		if (cnt>=mid) sum+=pro;
		else sum+=pro*A/(A+deny);
		return;
	}
	ev(dep+1,cnt+1,pro*a[dep+1]/10.0,deny,sum);
	ev(dep+1,cnt,pro-pro*a[dep+1]/10.0,deny+b[dep+1],sum);
}
inline void dfs(int dep,int swe){
	rr double sum=0;
	ev(0,0,1,0,sum);
	ans=ans>sum?ans:sum;
	if (dep==n||!swe) return;
	for (rr int i=0;i<=swe;++i)
	if (a[dep+1]+i<=10)
		a[dep+1]+=i,dfs(dep+1,swe-i),a[dep+1]-=i;
}
signed main(){
	scanf("%d%d%d",&n,&k,&A); mid=n/2+1;
	for (rr int i=1;i<=n;++i) scanf("%d%d",&b[i],&a[i]),a[i]/=10;
	dfs(0,k); return !printf("%lf",ans);
}
```

---

