# Decomposition

## 题目描述

For a sequence of integers $ [x_1, x_2, \dots, x_k] $ , let's define its decomposition as follows:

Process the sequence from the first element to the last one, maintaining the list of its subsequences. When you process the element $ x_i $ , append it to the end of the first subsequence in the list such that the bitwise AND of its last element and $ x_i $ is greater than $ 0 $ . If there is no such subsequence in the list, create a new subsequence with only one element $ x_i $ and append it to the end of the list of subsequences.

For example, let's analyze the decomposition of the sequence $ [1, 3, 2, 0, 1, 3, 2, 1] $ :

- processing element $ 1 $ , the list of subsequences is empty. There is no subsequence to append $ 1 $ to, so we create a new subsequence $ [1] $ ;
- processing element $ 3 $ , the list of subsequences is $ [[1]] $ . Since the bitwise AND of $ 3 $ and $ 1 $ is $ 1 $ , the element is appended to the first subsequence;
- processing element $ 2 $ , the list of subsequences is $ [[1, 3]] $ . Since the bitwise AND of $ 2 $ and $ 3 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 0 $ , the list of subsequences is $ [[1, 3, 2]] $ . There is no subsequence to append $ 0 $ to, so we create a new subsequence $ [0] $ ;
- processing element $ 1 $ , the list of subsequences is $ [[1, 3, 2], [0]] $ . There is no subsequence to append $ 1 $ to, so we create a new subsequence $ [1] $ ;
- processing element $ 3 $ , the list of subsequences is $ [[1, 3, 2], [0], [1]] $ . Since the bitwise AND of $ 3 $ and $ 2 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 2 $ , the list of subsequences is $ [[1, 3, 2, 3], [0], [1]] $ . Since the bitwise AND of $ 2 $ and $ 3 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 1 $ , the list of subsequences is $ [[1, 3, 2, 3, 2], [0], [1]] $ . The element $ 1 $ cannot be appended to any of the first two subsequences, but can be appended to the third one.

The resulting list of subsequences is $ [[1, 3, 2, 3, 2], [0], [1, 1]] $ .

Let $ f([x_1, x_2, \dots, x_k]) $ be the number of subsequences the sequence $ [x_1, x_2, \dots, x_k] $ is decomposed into.

Now, for the problem itself.

You are given a sequence $ [a_1, a_2, \dots, a_n] $ , where each element is an integer from $ 0 $ to $ 3 $ . Let $ a[i..j] $ be the sequence $ [a_i, a_{i+1}, \dots, a_j] $ . You have to calculate $ \sum \limits_{i=1}^n \sum \limits_{j=i}^n f(a[i..j]) $ .

## 样例 #1

### 输入

```
8
1 3 2 0 1 3 2 1```

### 输出

```
71```

## 样例 #2

### 输入

```
5
0 0 0 0 0```

### 输出

```
35```

# 题解

## 作者：Leasier (赞：9)

首先，$0$ 肯定只能被分到一个单独的序列里，则接下来我们可以不讨论它，一个 $a_i = 0$ 会产生 $i(n - i + 1)$ 的总贡献。

现在，我们可以发现：**扔掉 $0$ 之后，至多只会有三个序列**。

- 如果有 $3$，一定在第一个序列里。
- 可能存在暂时扔不进第一个序列的 $1, 2$，至多会再构成两个序列。

考虑 dp。设 $dp_{i, j, k, l}$ 表示所有以 $i$ 结尾的子段中，所得的第一个序列末项为 $j$，第二个为 $k$，第三个为 $l$ 的方案数（若没有该序列则对应项为 $0$）。

每次遇到一个 $a_i = 0$ 直接继承；$a_i > 0$ 则枚举一个 $j, k, l$ 作为加入 $a_i$ 之前各个序列的结尾，讨论一下插入第几个序列即可。

答案：$\displaystyle\sum_{i = 1}^n ([a_i = 0] i(n - i + 1) + \sum_{j = 0}^3 \sum_{k = 0}^3 \sum_{l = 0}^3 dp_{i, j, k, l}([j > 0] + [k > 0] + [l > 0]))$

时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int dp[7][7][7][7];

int main(){
	int n, cur = 0;
	ll ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		int a;
		scanf("%d", &a);
		dp[cur][0][0][0]++;
		if (a == 0){
			ans += (ll)i * (n - i + 1);
		} else {
			int nxt = cur ^ 1;
			for (int j = 0; j <= 3; j++){
				for (int k = 0; k <= 3; k++){
					for (int l = 0; l <= 3; l++){
						dp[nxt][j][k][l] = 0;
					}
				}
			}
			for (int j = 0; j <= 3; j++){
				for (int k = 0; k <= 3; k++){
					for (int l = 0; l <= 3; l++){
						if (j == 0 || (j & a)){
							dp[nxt][a][k][l] += dp[cur][j][k][l];
						} else if (k == 0 || (k & a)){
							dp[nxt][j][a][l] += dp[cur][j][k][l];
						} else {
							dp[nxt][j][k][a] += dp[cur][j][k][l];
						}
					}
				}
			}
			cur = nxt;
		}
		for (int j = 0; j <= 3; j++){
			for (int k = 0; k <= 3; k++){
				for (int l = 0; l <= 3; l++){
					ans += dp[cur][j][k][l] * ((j > 0 ? 1 : 0) + (k > 0 ? 1 : 0) + (l > 0 ? 1 : 0));
				}
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：cats142857 (赞：1)

给定一个长为 $n$ 的数组 $a$ 。定义一个区间的权值为：有一个数组的链表，初始为空，对于区间从左到右的每个元素 $a_i$ ，对链表左到右枚举每个数组，如果 $a_i$ 与某个数组末尾元素的二进制AND不为 $0$ ，则将这个元素放到这个数组的末尾，并停止枚举。如果找不到这样的数组，则新建一个只有一个元素 $a_i$ 的数组，并将这个数组放在链表的尾部，最后链表中数组的个数即是区间的权值。求数组 $a$ 每个区间的权值之和。数据范围 $1\le n\le 3\times 10^5,0\le a_i\le 3$。

由于 $a_i$ 很小，考虑对 $a_i$ 分类讨论。若 $a_i=0$ ，链表中一定不存在满足条件的数组，每次加入 $0$ 都一定会导致链表长度增加 $1$ 。所以每个 $0$ 对答案的贡献都是包含这个 $0$ 的区间个数，可以单独计算。

不考虑 $0$ 后，由于 $3$ 与 $1,2,3$ 的二进制AND都不为 $0$ ，所以每次加入 $3$ 都一定加入链表从左到右第一个数组中。又因为 $1$ 与 $2$ 二进制AND为 $0$ ，也就是，在链表第一个数组后面，只能存在全部为 $1$ 的数组和全部为 $2$ 的数组，且每种最多一个(后文称为纯 $1$ 数组和纯 $2$ 数组)。

考虑枚举区间的左端点，对其右侧的所有右端点计算贡献和。对于每个左端点，在其向右添加元素时，只要遇到非 $0$ 的数，第一个数组就会出现，并对其右侧所有的右端点产生 $1$ 的贡献。

当第一个数组的尾部为 $2$ 时，如果添加 $1$ ，纯 $1$ 数组就会出现。如果要让第一个数组尾部为 $2$ ，只有两种可能：区间从左到右第一个非 $0$ 元素为 $2$ ，或者在遇到某个 $3$ 后遇到的下一个非 $0$ 元素即为 $2$ 。这之后，如果在未遇到 $3$ 时遇到 $1$ ，就会对其右侧所有的右端点产生 $1$ 的贡献。纯 $2$ 数组同理。为在 $O(1)$ 时间解决此问题，需要预处理以下 $5$ 个数组。

1. $nval[i]$ ：每个位置向右的下一个非 $0$ 元素的位置(如果不存在记为 $-1$ )。

2. $n1[i]$ ：每个位置向右在未遇到 $3$ 时遇到的下一个 $1$(如果不存在记为 $-1$ )。

3. $n2[i]$ ：每个位置向右在未遇到 $3$ 时遇到的下一个 $2$(如果不存在记为 $ -1$ )。

4. $n31[i]$ ：每个位置向右遇到 $3$ ，满足这个 $3$ 向右遇到的第一个非 $0$ 元素为 $2$，且这个 $2$ 向右在未遇到 $3$ 时存在 $1$，记录这样的的 $1$ 中最靠左的 $1$ (如果不存在记为 $-1$ )。

5. $n32[i]$ ：每个位置向右遇到 $3$ ，满足这个 $3$ 向右遇到的第一个非 $0$ 元素为 $1$，且这个 $1$ 向右在未遇到 $3$ 时存在 $2$，记录这样的的 $2$ 中最靠左的 $2$ (如果不存在记为 $-1$ )。

每个左端点 $i$ 在计算贡献时

- 如果 $nval[i]$ 不为 $-1$ ，设 $t=nval[i]$ ，则从 $t$ 位置开始，第一个数组就会出现，对答案加上相应的贡献。否则这个左端点对答案的贡献为 $0$ ，并跳过下面的步骤。

- 如果 $a[t]=2$ ，且 $n1[t]$ 不为 $-1$ ，则从 $n1[t]$ 位置开始，纯 $1$ 数组就会出现，对答案加上相应的贡献。否则，如果 $n31[t]$ 不为 $-1$ ，则从 $n31[t]$ 位置开始，纯 $1$ 数组就会出现，对答案加上相应的贡献。如果两个条件都不满足，则纯 $1$ 数组不会出现。

- 纯 $2$ 数组同理。

总时间复杂度为 $O(n)$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300000],nval[300000],n1[300000],n2[300000],n31[300000],n32[300000];
int main(int argc, char** argv) {
	ios::sync_with_stdio(false),cin.tie(0);
	long long ans=0,n,i,t;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>a[i];
		if(a[i]==0)ans+=(long long)(i+1)*(n-i);
	}
	for(i=n-1;i>-1;i--)
	{
		if(a[i]>0)nval[i]=i;
		else
		{
			if(i==n-1)nval[i]=-1;
			else nval[i]=nval[i+1];
		}
	}
	for(i=n-1;i>-1;i--)
	{
		if(a[i]==1)n1[i]=i;
		else if(a[i]==0||a[i]==2)
		{
			if(i==n-1)n1[i]=-1;
			else n1[i]=n1[i+1];
		}
		else n1[i]=-1;
	}
	for(i=n-1;i>-1;i--)
	{
		if(a[i]==2)n2[i]=i;
		else if(a[i]==0||a[i]==1)
		{
			if(i==n-1)n2[i]=-1;
			else n2[i]=n2[i+1];
		}
		else n2[i]=-1;
	}
	for(i=n-1;i>-1;i--)
	{
		if(i<n-1&&a[i]==3&&nval[i+1]!=-1&&a[nval[i+1]]==2&&n1[nval[i+1]]!=-1)n31[i]=n1[nval[i+1]];
		else if(i==n-1)n31[i]=-1;
		else n31[i]=n31[i+1];
	}
	for(i=n-1;i>-1;i--)
	{
		if(i<n-1&&a[i]==3&&nval[i+1]!=-1&&a[nval[i+1]]==1&&n2[nval[i+1]]!=-1)n32[i]=n2[nval[i+1]];
		else if(i==n-1)n32[i]=-1;
		else n32[i]=n32[i+1];
	}
	for(i=0;i<n;i++)
	{
		t=nval[i];
		if(t==-1)continue;
		ans+=n-t;
		if(a[t]==1&&n2[t]!=-1)ans+=n-n2[t];
		else if(n32[t]!=-1)ans+=n-n32[t];
		if(a[t]==2&&n1[t]!=-1)ans+=n-n1[t];
		else if(n31[t]!=-1)ans+=n-n31[t];
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：honglan0301 (赞：1)

## 题目分析
说一个不太一样的想法qwq。

我们手玩一下发现可以分类计算。首先是数列中的 $0$, 显然每个 $0$ 都会单独占一个子序列。于是对序列中的每个 $0$ 分别计算贡献, $a_i$ 的贡献为 $i\times(n-i+1)$。

而对于剩下的非零数，发现它们最多会构成 $3$ 个子序列，因为 $3$ 必然在第一个里，而剩下的 $1$ 和 $2$ 最多各自再占一个子序列。接下来分类讨论。

1. 构成至少一个子序列。这种情况只需要选的段中有非零数，把原数列中连续的 $0$ 预处理出来，用 ${n\times (n+1)}\over2 $ 减去全是 $0$ 的段数即可。

2. 构成至少两个子序列。这种情况只需要选段中存在一处形如 $\{1,2\}$ 或 $\{2,1\}$, 当然中间有 $0$ 也可以，以下均不考虑 $0$。那么我们把这两种形式的位置预处理出来，记录下每个位置后面最近的 $\{1,2\}$ 和 $\{2,1\}$ 的结束点，记作 $next_{12}[i],next_{21}[i]$, 再分别计算贡献：从第 $i$ 个位置开始选的贡献是 $(n+1-\min(next_{12}[i],next_{21}[i]))$。

3. 构成至少三个子序列。先考虑子序列个数怎么能从两个变成三个。不妨设当前第二个子序列都是 $2$, 即子序列为 $[[......1],[2]]$, 那么第三个子序列必然全是 $1$, 这就要求第一个子序列中的 $1$ 被 $2$ 覆盖住，即接下来要出现形如 $\{3,2,...,2,1\}$ 的一段，反之需要出现 $\{3,1,...,1,2\}$ 的一段。那么我们用类似的思路，记录下每个位置后最近的结束点，记作 $next_{321}[i],next_{312}[i]$。

	但这时的计算贡献还要考虑到第二个子序列是什么，即对于从 $i$ 位置开始选的贡献，需要知道 $next_{12}[i]$ 和 $next_{23}[i]$ 哪个更小（赛时没考虑这点，test 16 多输出了一千多，一直 wa）。对于较小的一种，再看对应的 $next_{321}[next_{12}[i]]$ 或 $next_{312}[next_{21}[i]]$。具体的计算可以看代码。
    
## 代码

代码看起来比较长，但其实每个预处理过程都是重复的。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#define int long long
using namespace std;

int n,a[300005],cntab,cntba,cntcab,cntcba,nxtab[300005],nxtba[300005],nxtcab[300005],nxtcba[300005];

pair <int,int> tab[300005],tba[300005],scab[300005],scba[300005];

long long ans;

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	a[0]=10000; a[n+1]=3;

	int nowl=1,nowr=1;
	while(nowr<=n+1)//预处理0
	{
		if(!a[nowr]) 
		{
			ans+=nowr*(n-nowr+1); 
			nowr++;
		}
		else 
		{
			if(nowr>nowl)
			{
				ans-=(nowr-nowl+1)*(nowr-nowl)/2;
			}
			nowr++; 
			nowl=nowr;
		}
	}
	ans+=n*(n+1)/2; 

	nowl=1;
	while(nowl<=n)//{1,2}
	{
		while(a[nowl]!=1) nowl++;
		for(int kkk=nowl+1;kkk<=n+1;kkk++)
		{
			if(a[kkk]==0) continue;
			if(a[kkk]==3) {nowl=kkk+1;break;}
			else if(a[kkk]==a[nowl]) {nowl=kkk;break;}
			else if(a[kkk]) {cntab++; tab[cntab]=make_pair(nowl,kkk); nowl=kkk+1; break;}
		}
	}

	nowl=1;
	while(nowl<=n)//{2,1}
	{
		while(a[nowl]!=2) nowl++;
		for(int kkk=nowl+1;kkk<=n+1;kkk++)
		{
			if(a[kkk]==0) continue;
			if(a[kkk]==3) {nowl=kkk+1;break;}
			else if(a[kkk]==a[nowl]) {nowl=kkk;break;}
			else if(a[kkk]) {cntba++; tba[cntba]=make_pair(nowl,kkk); nowl=kkk+1; break;}
		}
	}

	nowl=1;
	while(nowl<=n)//{3,2,1}
	{
		while(a[nowl]!=3) nowl++;
		bool flag=0;
		for(int kkk=nowl+1;kkk<=n+1;kkk++)
		{
			if(a[kkk]==0) continue;
			if(a[kkk]==3) {nowl=kkk;break;}
			else if(a[kkk]==2) {flag=1;}
			else if(a[kkk]==1) {if(flag) {cntcba++; scba[cntcba]=make_pair(nowl,kkk);} nowl=kkk+1; break;}
		}
	}
	
	nowl=1;
	while(nowl<=n)//{3,1,2}
	{
		while(a[nowl]!=3) nowl++;
		bool flag=0;
		for(int kkk=nowl+1;kkk<=n+1;kkk++)
		{
			if(a[kkk]==0) continue;
			if(a[kkk]==3) {nowl=kkk;break;}
			else if(a[kkk]==1) {flag=1;}
			else if(a[kkk]==2) {if(flag) {cntcab++; scab[cntcab]=make_pair(nowl,kkk);} nowl=kkk+1; break;}
		}
	}

	for(int i=1;i<=cntab;i++)
	{
		for(int j=tab[i-1].first+1;j<=tab[i].first;j++)
		{
			nxtab[j]=tab[i].second;//nextab，以下同理
		}
	}
	for(int j=tab[cntab].first+1;j<=n;j++)
	{
		nxtab[j]=n+1;
	}

	for(int i=1;i<=cntba;i++)
	{
		for(int j=tba[i-1].first+1;j<=tba[i].first;j++)
		{
			nxtba[j]=tba[i].second;
		}
	}
	for(int j=tba[cntba].first+1;j<=n;j++)
	{
		nxtba[j]=n+1;
	}

	for(int i=1;i<=cntcab;i++)
	{
		for(int j=scab[i-1].first+1;j<=scab[i].first;j++)
		{
			nxtcab[j]=scab[i].second;
		}
	}
	for(int j=scab[cntcab].first+1;j<=n+1;j++)
	{
		nxtcab[j]=n+1;
	}

	for(int i=1;i<=cntcba;i++)
	{
		for(int j=scba[i-1].first+1;j<=scba[i].first;j++) 
		{
			nxtcba[j]=scba[i].second;
		}
	}
	for(int j=scba[cntcba].first+1;j<=n+1;j++) 
	{
		nxtcba[j]=n+1;
	}

	for(int i=1;i<=n;i++)//分别计算贡献
	{
		ans+=n-min(nxtab[i],nxtba[i])+1;
		int kkk=nxtab[i],ppp=nxtba[i];
		if(kkk<ppp)
		{
			ans+=n-nxtcba[nxtab[i]]+1;
		}
		else
		{
			ans+=n-nxtcab[nxtba[i]]+1;
		}
		//ans+=n-min(nxtcba[nxtab[i]],nxtcab[nxtba[i]])+1;
	}
	cout<<ans<<endl;
}
```

---

## 作者：Alex_Wei (赞：1)

这题还蛮不错的。

先考虑 $f(1, n)$。

首先，$0$ 是相对特殊的。每个 $a_i = 0$ 恰好产生一个空序列，且不产生其他任何影响，对 $f(1, n)$ 的贡献为 $1$。

**不妨设序列里面没有 $0$**。

我们注意到，因为 $3$ 可以和所有数（$1\sim 3$ 相邻），所以 $3$ 一定放在第一个序列里，不会影响到其它序列。

因此，除了第一个序列以外，其它序列要么全是 $1$，要么全是 $2$，$f(1, n)\leq 3$。

因为只有三个序列，且我们只关心序列的最后一个数，可能的状态很少，这启发我们设 $f_{i, j, k, l}$ 表示在所有 $f(a[p, i]) (p \leq i)$ 当中，三个序列末尾分别为 $j, k, l$ 的 $p$ 的数量，其中若 $j / k / l = 0$ 则表示对应序列不存在。

直接枚举 $j, k, l$，结合对应的 $a_i$ 通过模拟题目要求转移即可。答案即 $\sum f_{i, j, k, l} ([j > 0] + [k > 0] + [l > 0])$。

当序列里面有 $0$ 时，它对所有包含它的区间产生 $1$ 的贡献，这是容易计算的。

可以记录是否存在全 $1$ 序列和全 $2$ 序列取代 $k, l$，将总状态数除以 $4$，但不必要。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1766/submission/185020456)。

---

## 作者：MSqwq (赞：1)

非常傻逼，最后一分钟写出来了，然后没开 LL，光荣 WA on 18 离场。  

------------
题意：  
给你一个序列，对于一个序列我们定义一个分解的操作，就是从左往右讨论每个数，这个数去和每个已经分出来的子序列的最后一个数比较，如果按位与不为 $0$ ，就放在它后面，讨论下一个数。然后问你这个序列所有区间能分解的子序列个数和。  

------------
题解：  
首先有个非常妙而且非常有用的性质，就是除去 0 之后，剩下的数组成的子序列个数不会超过三个。  
证明就是因为你要放到符合条件的第一个子序列上面，还要考虑顺序，所以两个是不够的。更深刻的说就是当且仅当第一个子序列和第二个子序列相同且为 1 或 2，那么这个时候再进来一个不同于上者的 1 或 2，那么就会产生第三个，且一定不会产生第四个。  
举个例子 现在是 3 2，进来一个 2 ，会优先加到第一个里面，变成 2 2，然后再加个 1，就会变成 2 2 1，就产生了第三个。且这个时候再加任何数都不会增加数量了，同理也可以构造 1 1 2。  
之所以不讨论 0，是因为只要有 0 加进来，那么一定会产生一个新的子集，因为 0 按位与任何数都是 0 嘛。  
因为每个子序列和前面的数无关，之和末尾的那个数有关，所以只需要记录最后一个数即可。  
然后考虑算贡献，如果我在 $i$ 位置怎加了一个子序列，那么我们不难发现，增加一个子序列的情况，只会是 $a_i=0$ 或者前面的子序列都加不进去，就是上面的两种情况 1 1 2 或者 2 2 1。那么当我们再讨论他后面的数的时候，是不是子序列都多了一个，那么 $i$ 位置的贡献就是 $n-i+1$。如果可以直接加到已有的子序列里面，那么就不会产生贡献，只需要更新一下数组就好了。  
然后你会发现这个东西和 **状压DP** 的思想很像，我们只需要知道上一个数的子序列末尾状态，那么就能继续往下面算贡献，顺便的记忆化一下，跑的飞快的。 

代码：  
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=3e5+10;
int n,a[N];
string b;
map<string,ll>mp[N];
ll dfs(int now)
{
	if(now==n+1)return 0;
	if(mp[now].find(b)!=mp[now].end())return mp[now][b];
	if(a[now]==0)return mp[now][b]=dfs(now+1)+n-now+1;
	ll res=0;
	for(int i=1;i<=3;i++)
	{
		if(b[i]=='0')
		{
			b[i]=a[now]+'0';
			res=dfs(now+1)+n-now+1;
			b[i]='0';
			return mp[now][b]=res;
		}
		else if((b[i]-'0')&a[now])
		{
			char tmp=b[i];
			b[i]=a[now]+'0';
			res=dfs(now+1);
			b[i]=tmp;
			return mp[now][b]=res;
		}
	}
	return 0;
}
int main()
{
	string tmp="?000";
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	ll ans=0;
	for(int i=n;i>=1;i--)b=tmp,ans+=dfs(i);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：include_BM (赞：1)

先考虑如何对一个序列求解。

序列中的每个 $0$ 一定会单独成一段，故可以单独计算 $0$ 的贡献，对于不为 $0$ 的部分，考虑以下序列：

$$\color{red}1 \ \color{black}2 \ \color{red}1 \ \color{red}3 \ 3\ 2 \ 2 \ \color{black}1 \ \color{red}2\  3\  1 \ 1 \ \color{black}2 \ 2\ \color{red}3\  1\  1\ \color{black}2$$

其中标红的数表示这些数最终会出现在划分得到的第一个子序列中，可以发现所有 $3$ 一定出现，每两个 $3$ 中间出现的数一定是所有与这两个 $3$ 中第一个 $3$ 后面的那个数相同的数，第一个 $3$ 之前出现的数一定是所有与第一个数相同的数。

对于没有标红的部分，最终所有的 $1$ 会被划分到一个子序列，所有的 $2$ 会被划分到一个子序列。

对于本题，可以从大到小枚举 $l$，同时用集合 $S_1,S_2$ 分别表示所有还未被标红的 $1,2$ 的位置，具体细节看代码注释。

```cpp
signed main(){
    n=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=n;++i) if(!a[i]) ans+=i*(n-i+1);
    s[1].emplace(n+1),s[2].emplace(n+1),s[3].emplace(n+1);
    for(int las=0,i=n;i>=1;s[a[i]].emplace(i),--i)
        if(a[i]==3){
            int nxt=*s[3].begin();
            if(i!=n&&a[i+1]!=3){
                // 将 [i,nxt] 内所有 =a[i+1] 的数标红，若为 0 则找下一个不为 0 的数。
                if(!a[i+1]) a[i+1]=(*s[1].begin()<*s[2].begin()?1:2);
                while(*s[a[i+1]].begin()<nxt) s[a[i+1]].erase(s[a[i+1]].begin());
            }
            int x=*s[1].begin(),y=*s[2].begin();
            ans+=(las=(n-i+1)+(n-x+1)+(n-y+1)); // 右端点在 [x,n] 至少包含一个没被标红的 1，需要一个子序列放 1，同理在 [y,n] 的需要一个放 2，下同。
        }
        else if(a[i]){
            int nxt=*s[3].begin();
            int x=*s[a[i]].lower_bound(nxt),y=*s[3-a[i]].begin(); // [i,nxt] 内所有 =a[i] 的数也需要标红。
            ans+=(las=(n-i+1)+(n-x+1)+(n-y+1));
        }
        else ans+=las; // 由于不考虑 0 的贡献，对于为 0 的位置，答案与上一个不为 0 的位置相同。
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

$\textbf{CF1766E}$

首先注意到插入一个 $0$ 一定会新开一段，且任意数字与 $0$ 均为 $0$，即 $0$ 段不会对插入的数字做贡献。我们可以统一统计 $0$ 的贡献。

忽略 $0$ 后，容易发现段数最多为 $3$。

- $3$ 只可能出现在第一段末尾。
- $1,2$ 均不可能在除第一段外的段末尾出现大于 $1$ 次。

因此本质不同的数组只有 $\mathcal O(1)$ 种。

考虑扫描线扫描右端点，维护以右端点结尾的所有后缀。我们只需要了解每个本质不同的数组出现了几次，用 map 存下来即可。每个状态新增一个数字转移到的新状态直接暴力计算即可。

注意到状态数是常数级别的，因此 map 的复杂度也可以看做 $\mathcal O(1)$。总复杂度也是 $\mathcal O(n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 01.08.2024 17:04:57
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,x; map<vector<int>,int> mp; ll ans,sm;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n; int now = 1;
    for(int i = 1;i <= n;i ++){
        if(cin >> x,!x) {
            sm += i,ans += sm,now ++; 
            for(auto [x,y] : mp) ans += x.size() * y;
            continue;
        }auto pm = mp; mp.clear(),mp[{x}] += now,now = 1;
        for(auto [xx,y] : pm){
            int fd = 0; vector<int> vc = xx;
            for(int &i : vc) if(i & x) {i = x,fd = 1; break;}
            if(!fd) vc.push_back(x);
            mp[vc] += y;
        }for(auto [x,y] : mp) ans += x.size() * y;
        ans += sm;
    }cout << ans << "\n";
}
```

---

## 作者：sanaka87 (赞：0)

感谢手速场让我拿到了有生之年的第一个 div2 rk 4...

自认为这大概是最直观的一种解法了吧？

首先可以发现 $0$ 加入一定造成一个贡献。我们把 $0$ 的贡献单独拿出来计算，也就是 $\sum_{a_i=0}i(n-i+1)$。

接下来发现子序列的末尾构成的序列是很少的，具体来说是 $16$ 种。

这个我们通过 $\texttt{map<vector<int>, int>}$ + bfs 打表编号，建造出一个“插入自动机”，然后预处理一个转移二维数组表示编号 $i$ 加入一个 $j$ 转移到哪个编号。
  
然后就可以在这个自动机上 dp 了。每一次加入一个数，对所有状态转移，再加入一个新的。时间复杂度 $O(\omega n)$，其中 $\omega=16$。这么写不是很严谨。
  
  ```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define vec vector<int> 
using namespace std;
map<vec,int> ID;
vec init(int a=0){vec d;if (a) d.pb(a);return d;}
vec add(vec y,int x){
	if (y.size()==0) return init(x);
	for (int i=0;i<(int)y.size();i++){
		if (y[i]&x){
			y[i]=x;return y;
		}
	}
	y.pb(x);return y;
}
int e[17][4],a[302020],tot,n,i,j;
ll dp[300032][17],len[17],_;
signed main(){
	queue<vec> dl;
	dl.push(init());
	ID[init()]=0;
	while (!dl.empty()){
		vec u=dl.front();dl.pop();
		len[ID[u]]=u.size();
		for (i=1;i<=3;i++){
			vec v=add(u,i);
			if (!ID.count(v)){
				ID[v]=++tot;
				dl.push(v);
			}
			e[ID[u]][i]=ID[v];
		}
	}
	scanf("%d",&n);
	for (i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if (a[i]) for (j=0;j<=15;j++) dp[i][e[j][a[i]]]+=dp[i-1][j];
		else{
			_+=1ll*i*(n-i+1);
			for (j=0;j<=15;j++) dp[i][j]=dp[i-1][j];
		}
		dp[i][ID[init(a[i])]]++;
		for (j=0;j<=15;j++) _+=dp[i][j]*len[j];
	}
	cout<<_;
	return 0;
}


```


---

