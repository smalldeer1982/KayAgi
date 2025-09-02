# Vasya and Robot

## 题目描述

Vasya has $ n $ items lying in a line. The items are consecutively numbered by numbers from $ 1 $ to $ n $ in such a way that the leftmost item has number $ 1 $ , the rightmost item has number $ n $ . Each item has a weight, the $ i $ -th item weights $ w_{i} $ kilograms.

Vasya needs to collect all these items, however he won't do it by himself. He uses his brand new robot. The robot has two different arms — the left one and the right one. The robot can consecutively perform the following actions:

1. Take the leftmost item with the left hand and spend $ w_{i}·l $ energy units ( $ w_{i} $ is a weight of the leftmost item, $ l $ is some parameter). If the previous action was the same (left-hand), then the robot spends extra $ Q_{l} $ energy units;
2. Take the rightmost item with the right hand and spend $ w_{j}·r $ energy units ( $ w_{j} $ is a weight of the rightmost item, $ r $ is some parameter). If the previous action was the same (right-hand), then the robot spends extra $ Q_{r} $ energy units;

Naturally, Vasya wants to program the robot in a way that the robot spends as little energy as possible. He asked you to solve this problem. Your task is to find the minimum number of energy units robot spends to collect all items.

## 说明/提示

Consider the first sample. As $ l=r $ , we can take an item in turns: first from the left side, then from the right one and last item from the left. In total the robot spends $ 4·42+4·99+4·3=576 $ energy units.

The second sample. The optimal solution is to take one item from the right, then one item from the left and two items from the right. In total the robot spends $ (2·4)+(7·1)+(2·3)+(2·2+9)=34 $ energy units.

## 样例 #1

### 输入

```
3 4 4 19 1
42 3 99
```

### 输出

```
576
```

## 样例 #2

### 输入

```
4 7 2 3 9
1 2 3 4
```

### 输出

```
34
```

# 题解

## 作者：Gypsophila (赞：3)

### Description

一个序列 $a$ ，每次可以从左边或右边取走一个，从左边取消耗 $l \times a_i$，从右边取消耗 $r \times a_i$。连续取走左边的额外消耗 $ql$，连续取走右边的额外消耗 $qr$ 能量。最小化取走所有物品的价值。

### Solution

对于每个 $i$ ，考虑他是从左边拿走的还是从右边拿走的。

则必然满足这个条件：$1,2 \cdots x-1,x$ 的物品是由左手取走的，$x+1,x+2 \cdots n-1,n$ 的物品是由右手取走的。即一个前缀是由左手拿走的，其余的一个后缀是由右手拿走的。

枚举中间断点 $x$ ，使用前缀后缀和维护代价。

还有一个连续取的细节，想要达到最优必然是左拿一个右拿一个间隔拿，如果左/右边不够拿了，剩下的必然要连续取。根据给定的 $ql,qr$ 来计算多余代价即可。复杂度 $O(n)$。

### Code 

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 100100;
const int INF = (int)1e9;
int n, l, r, ql, qr, ans = INF;
int a[N], pre[N], suf[N];
int main() {
    scanf("%d %d %d %d %d", &n, &l, &r, &ql, &qr);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pre[i] = pre[i - 1] + a[i];
    for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] + a[i];
    for(int i = 0; i <= n; i++) {
        int L = i, R = n - i;
        int sum = pre[i] * l + suf[i + 1] * r;
        if(R - L >= 2 || L - R >= 2) sum += (R > L ? qr : ql) * (abs(R - L) - 1);
        ans = min(ans, sum);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：DiDi123 (赞：2)

# 一、题意
这道题大概就是说从左边取或者右边取物品每个物品都有一定的费用，而且连续取会有额外的费用，求最小的花费

# 二、分析
第一眼看到这题，感觉很像区间 dp，但是一看数据范围 $n\leq10^5$ 就肯定没戏了。在仔细看一下，发现物品的价值和取的先后顺序没有直接关系，但是连续取还会有额外费用，所以，用一下贪心，尽量间隔着左右取就好了。

注意到一个物品不是左手取的就是右手取的，而且如果要是左手取的话还需要左边的物品已经被取了，右手也同理，所以维护一个断点，这个点左边左手取，右边右手取就好了。

还有一个细节就是分配左右手取的顺序的问题，用贪心的想法，先左右间隔取，如果一边取完了再取另一边的，设左边有 $x$ 个，右边有 $y$ 个，$x<y$，那么应该花费 $(y-x-1)\times Q_r$ 的费用，具体见下图（蓝和绿代表右手，红代表左手）：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/up0r7ijc.png)

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001
int n,r,l,ql,qr;
int w[MAXN],lsum,rsum;
int ans=0x7f7f7f7f;
int extra(int x,int y)
{
	if(x==y) return 0;
	if(x<y) return (y-x-1)*qr;
	return (x-y-1)*ql;
}
int main()
{
	cin>>n>>l>>r>>ql>>qr;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		rsum+=w[i]; //初始默认全取右边
	}
	for(int i=0;i<=n;i++) //左边i个，右边n-i个
	{
		lsum+=w[i],rsum-=w[i]; //断点右移，左边区间+w,右边区间-w
		ans=min(ans,lsum*l+rsum*r+extra(i,n-i));
	}
	cout<<ans;
}
```


---

## 作者：PCCP (赞：1)

## 思路

太简单了，不难发现我们左右交替是最优的。然后发现从左边拿的一定不会和从右边拿的混合，整个序列一定是左边一部分从左边拿走的，剩下的从右边拿走的。最后，同时，我们可以改变第一次拿的某一边，使得即使某一边多出一个也不需要额外花费。

提前做一遍前缀和后缀和即可，再枚举有多少从左边拿的即可。

这不比今年 CSP-S T1 诈骗题简单？

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
const int N=1e5+10;
int n,L,R,ql,qr,w[N];
long long suml[N],sumr[N],ans=1e18;
signed main(){
	scanf("%d%d%d%d%d",&n,&L,&R,&ql,&qr);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
		suml[i]=w[i]*L+suml[i-1];
		sumr[i]=w[i]*R;
	}
	for(int i=n;i>=1;i--){
		sumr[i]+=sumr[i+1];
	}
	for(int i=0;i<=n;i++){
		long long tem=suml[i]+sumr[i+1];
		if(i<n-i){
			tem+=(n-(i<<1)-1)*qr;
		}
		else if(i>n-i){
			tem+=((i<<1)-n-1)*ql;
		}
		ans=min(tem,ans);
	}
	printf("%lld\n",ans);
}
```


---

