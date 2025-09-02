# Weights and Measures

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1095

[PDF](https://uva.onlinejudge.org/external/101/p10154.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10154/c29ed6cce99dc9e3052d764393c705794c12e076.png)

## 样例 #1

### 输入

```
300 1000
1000 1200
200 600
100 101```

### 输出

```
3```

# 题解

## 作者：TemplateClass (赞：0)

$\gdef \dp{\mathrm{dp}}$
$\gdef \ans{\mathrm{ans}}$

记第 $i$ 只乌龟的力量为 $s _ i$，重量为 $w _ i$。显然要想让堆的层数高，就应该把力量越大的乌龟放下面，因此我们先按照 $s _ i$ 升序排序。

设 $\dp _ i$ 表示叠放 $i$ 层时最小的总重量，初始时 $\dp _ 0 = 0, \dp _ i = +\infty(i \ge 1)$。设当前求出的最大层数为 $\ans$，依次对于排序后的每个乌龟，从后往前遍历当前可能的层数，检查是否能将其放在当前层数的下面形成新的层数，并更新最小总重量以及 $\ans$。

~~没在答案结尾输出换行使我虚空调试 1h。~~

```cpp
#include<iostream>
#include<algorithm>
#include<utility>
#include<climits>

constexpr int N = 5607 + 1;
typedef std::pair<int, int> T;

#define s first
#define w second

int n = 0, dp[N], ans = 0; T a[N];

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	while(std::cin >> a[n + 1].w >> a[n + 1].s) ++n;
	
	std::sort(a + 1, a + n + 1);
	std::fill(dp + 1, dp + n + 1, INT_MAX);
	for(int i = 1; i <= n; ++i) {
		for(int j = ans; j >= 0; --j) {
			if(dp[j] + a[i].w <= a[i].s && dp[j] + a[i].w < dp[j + 1]) {
				dp[j + 1] = dp[j] + a[i].w;
				if(j + 1 > ans) ans = j + 1;
			}
		}
	}
	
	std::cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 题意

输入若干行，每行有 $2$ 个整数，分别是乌龟的重量和力量。

乌龟在重叠时，要求任何一只乌龟的力量都要不小于它和它上面乌龟的重量。

请问，最高能叠多少层？

### 2 思路

这很明显就是一道动规题。

首先，设数组 $dp_i$ 为叠到 $i$ 层时的最小重量，设第 $i$ 只乌龟的重量为 $w_i$。

设变量 $ans$，初始为 $0$。

然后就有了动规公式：

在选到第 $i$ 个乌龟，叠了 $j$ 层时：

$$dp_j=\operatorname{min}(dp_j,dp_{j-1}+w_i)$$

### 3 代码与记录

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define max_n 5607
#define INF 21474837
int n=1;//乌龟数
struct T{//乌龟结构体
	int w;//重量
	int s;//力气
	int val;//净值
}t[max_n+2];//乌龟
int dp[max_n+2];//动规数组
int ans=0;//答案
bool cmp(T a,T b){return a.val<b.val;}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("UVA10154_1.in","r",stdin);
	freopen("UVA10154_1.out","w",stdout);
	#endif
	while(scanf("%d%d",&t[n].w,&t[n].s)!=EOF){
		t[n].val=t[n].s-t[n].w;
		++n;
	}
	sort(t+1,t+n,cmp);
	for(int i=1;i<n;++i)dp[i]=INF;
	for(int i=1;i<n;++i){
		for(int j=ans+1;j>0;--j){
			if(dp[j-1]<=t[i].val){
				if(j>ans)ans=j;
				if(dp[j]>dp[j-1]+t[i].w){
					dp[j]=dp[j-1]+t[i].w;
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/53818360)

By **dengziyue**

---

