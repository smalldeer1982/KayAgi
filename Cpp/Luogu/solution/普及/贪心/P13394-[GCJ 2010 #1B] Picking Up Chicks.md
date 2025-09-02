# [GCJ 2010 #1B] Picking Up Chicks

## 题目描述

一群小鸡沿着一条笔直狭窄的道路向东奔跑。每只小鸡都以自己的恒定速度奔跑。当一只小鸡追上前面的小鸡时，它必须减速并以前面小鸡的速度跟随。你驾驶着一辆移动起重机在小鸡群后面，驱赶小鸡们朝着道路尽头的谷仓前进。起重机的机械臂可以瞬间将任意一只小鸡提起，让紧跟在它后面的小鸡从下面穿过，然后再把被提起的小鸡放回原位。这个操作是瞬时完成的，并且只能对相邻的两只小鸡进行，即使有三只或更多小鸡连续排成一排，也只能让其中一只通过。每次交换都计为一次操作。

给定每只小鸡在时间 $0$ 时的位置（$X_i$）和自然速度（$V_i$），以及谷仓的位置（$B$），请你计算，至少有 $K$ 只小鸡能在不晚于时间 $T$ 到达谷仓，所需的最少交换次数。如果无法实现，输出 "IMPOSSIBLE"。

你可以将小鸡视为在一条直线上移动的点。即使有三只或更多小鸡在同一位置且相邻，提起其中一只也只能让另外一只通过。每次交换是瞬时的，这意味着你可以同时进行多次交换，但每次都单独计数。

## 说明/提示

**限制条件**

- $1 \leqslant C \leqslant 100$；
- $1 \leqslant B \leqslant 1,000,000,000$；
- $1 \leqslant T \leqslant 1,000$；
- $0 \leqslant X_i < B$；
- $1 \leqslant V_i \leqslant 100$；
- 所有 $X_i$ 均不同且递增。

**小数据范围（13 分，测试集 1 - 可见）**

- $1 \leqslant N \leqslant 10$；
- $0 \leqslant K \leqslant \min(3, N)$；

**大数据范围（17 分，测试集 2 - 隐藏）**

- $1 \leqslant N \leqslant 50$；
- $0 \leqslant K \leqslant N$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5 3 10 5
0 2 5 6 7
1 1 1 1 4
5 3 10 5
0 2 3 5 7
2 1 1 1 4
5 3 10 5
0 2 3 4 7
2 1 1 1 4```

### 输出

```
Case #1: 0
Case #2: 2
Case #3: IMPOSSIBLE```

# 题解

## 作者：Rainbow_SYX (赞：1)

## 思路
我们把一只能够在非外力作用下跑到终点的鸡称为“好鸡”，否则称为“坏鸡”，容易理解，我们只需把跑在最前面的 $K$ 只“好鸡”全部赶到队头就行了，又因为交换操作是瞬时完成的，并且只能对相邻的两只小鸡进行，所以每一只“好鸡”到达目标位置（满足前面没有“坏鸡”时）所需要的交换次数必定是在初始位置时它前面所有的坏鸡之和，因此，我们可以得到代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int c,ans;
int x[55],v[55],tat[55];
int main() 
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>c;
    for(int T=1;T<=c;T++)
    {
    	int n,k,b,t;
    	ans=0;
    	cin>>n>>k>>b>>t;
    	memset(x,0,sizeof(x));
    	memset(x,0,sizeof(v));
    	for(int i=1;i<=n;i++) cin>>x[i];
    	for(int i=1;i<=n;i++) cin>>v[i];
    	int good=0,bad=0;
    	for(int i=n;i>=1;i--)
    	{
    		if(good==k) break;
    		if(x[i]+t*v[i]<b) 
			{
				bad++;
			}
    		else 
    		{
    			good++;
    			ans+=bad;
			}
		}
    	if(good<k){
    		cout<<"Case #"<<T<<": IMPOSSIBLE\n";
    		continue;
		}
    	else cout<<"Case #"<<T<<": "<<ans<<"\n";
	}
    return 0;
}
```

---

