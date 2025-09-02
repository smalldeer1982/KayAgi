# Koa and the Beach (Easy Version)

## 题目描述

The only difference between easy and hard versions is on constraints. In this version constraints are lower. You can make hacks only if all versions of the problem are solved.

Koa the Koala is at the beach!

The beach consists (from left to right) of a shore, $ n+1 $ meters of sea and an island at $ n+1 $ meters from the shore.

She measured the depth of the sea at $ 1, 2, \dots, n $ meters from the shore and saved them in array $ d $ . $ d_i $ denotes the depth of the sea at $ i $ meters from the shore for $ 1 \le       i \le n $ .

Like any beach this one has tide, the intensity of the tide is measured by parameter $ k $ and affects all depths from the beginning at time $ t=0 $  in the following way:

- For a total of $ k $ seconds, each second, tide increases all depths by $ 1 $ .
- Then, for a total of $ k $ seconds, each second, tide decreases all depths by $ 1 $ .
- This process repeats again and again (ie. depths increase for $ k $ seconds then decrease for $ k $ seconds and so on ...). Formally, let's define $ 0 $ -indexed array $ p = [0, 1, 2,           \ldots, k - 2, k - 1, k, k - 1, k - 2, \ldots, 2, 1] $ of length $ 2k $ . At time $ t $ ( $ 0 \le t $ ) depth at $ i $ meters from the shore equals $ d_i + p[t \bmod 2k] $ ( $ t \bmod 2k $ denotes the remainder of the division of $ t $ by $ 2k $ ). Note that the changes occur instantaneously after each second, see the notes for better understanding.

At time $ t=0 $ Koa is standing at the shore and wants to get to the island. Suppose that at some time $ t $ ( $ 0 \le t $ ) she is at $ x $ ( $ 0 \le x \le n $ ) meters from the shore:

- In one second Koa can swim $ 1 $ meter further from the shore ( $ x $ changes to $ x+1 $ ) or not swim at all ( $ x $ stays the same), in both cases $ t $ changes to $ t+1 $ .
- As Koa is a bad swimmer, the depth of the sea at the point where she is can't exceed $ l $ at integer points of time (or she will drown). More formally, if Koa is at $ x $ ( $ 1 \le x         \le n $ ) meters from the shore at the moment $ t $ (for some integer $ t\ge 0 $ ), the depth of the sea at this point — $ d_x + p[t \bmod 2k] $ — can't exceed $ l $ . In other words, $ d_x + p[t \bmod 2k] \le l $ must hold always.
- Once Koa reaches the island at $ n+1 $ meters from the shore, she stops and can rest. Note that while Koa swims tide doesn't have effect on her (ie. she can't drown while swimming). Note that Koa can choose to stay on the shore for as long as she needs and neither the shore or the island are affected by the tide (they are solid ground and she won't drown there).

Koa wants to know whether she can go from the shore to the island. Help her!

## 说明/提示

In the following $ s $ denotes the shore, $ i $ denotes the island, $ x $ denotes distance from Koa to the shore, the underline denotes the position of Koa, and values in the array below denote current depths, affected by tide, at $ 1, 2,       \dots, n $ meters from the shore.

In test case $ 1 $ we have $ n = 2, k = 1, l = 1, p = [ 0, 1 ] $ .

Koa wants to go from shore (at $ x = 0 $ ) to the island (at $ x = 3 $ ). Let's describe a possible solution:

- Initially at $ t = 0 $ the beach looks like this: $ [\underline{s}, 1, 0, i] $ .
- At $ t = 0 $ if Koa would decide to swim to $ x = 1 $ , beach would look like: $ [s, \underline{2}, 1, i] $ at $ t =         1 $ , since $ 2 > 1 $ she would drown. So Koa waits $ 1 $ second instead and beach looks like $ [\underline{s}, 2, 1,         i] $ at $ t = 1 $ .
- At $ t = 1 $ Koa swims to $ x = 1 $ , beach looks like $ [s, \underline{1}, 0, i] $ at $ t = 2 $ . Koa doesn't drown because $ 1 \le 1 $ .
- At $ t = 2 $ Koa swims to $ x = 2 $ , beach looks like $ [s, 2, \underline{1}, i] $ at $ t = 3 $ . Koa doesn't drown because $ 1 \le 1 $ .
- At $ t = 3 $ Koa swims to $ x = 3 $ , beach looks like $ [s, 1, 0, \underline{i}] $ at $ t = 4 $ .
- At $ t = 4 $ Koa is at $ x = 3 $ and she made it!

We can show that in test case $ 2 $ Koa can't get to the island.

## 样例 #1

### 输入

```
7
2 1 1
1 0
5 2 3
1 2 3 2 2
4 3 4
0 2 4 3
2 3 5
3 0
7 2 3
3 0 2 1 3 0 1
7 1 4
4 4 3 0 2 4 2
5 2 3
1 2 3 2 2```

### 输出

```
Yes
No
Yes
Yes
Yes
No
No```

# 题解

## 作者：strange757 (赞：2)

看见一道如此明显的 $dp $ 题， 居然还没有 $ dp $ 的题解，于是自己动手写了一下。
    

------------


## 题面描述


Koa 要从海岸游到岛上。海岸的位置是 $0$，岛的位置是 $n+1$。

除了海岸和岛上，在  $[1,n]$  之间的位置 $i$  都有一个深度 $d_i$。海里有潮汐，具体来讲，给定值 $k$ ，则有下标**从**  $0$  **开始**的数组 $p=[0,1,2,...,k-1,k,k-1,...,1]$ 。在时间 $t$ ，海里的潮汐高度为 $p_{t \mod 2k}$ 。

在任意时间，如果 Koa 在位置 $x$ ，可以选择下一个时间停留位置 $x$ ，或游到位置 $x+1$ 。

Koa 能在时间 $t$ 到达位置 $i$ 当且仅当时间 $t$ 的潮汐高度与位置 $i$ 的深度之和不超过一个给定的值 $l$ ，即：$p_{t \mod 2k}+d_i \leq l$ ，否则她会溺水。海岸和岛上是安全的，不会受潮汐影响，所以在任何时间停留在那里都不会溺水。Koa 在游泳的时候不会受潮汐的影响（不会溺水）。

求出 Koa 是否能安全地到达岛上。



------------
首先看到这题可以比较容易的想到 $ dp $ 状态为 $dp[i][j]$ ,表示时间 $i$ 时是否能游到 $j$ 。转移也是非常的好想。

 在
  $ d[j] +p[i] \le l     $ 时有 $ f[i][j] = f[i - 1][j]|f[i-1][j-1] $
 
 到这里这道题其实差不多已经做完了，只有一点还没有解决，那就是边界条件，即从出发到到达需要的时间的上限。如果认为每个点都停留$k$个时间的话，那么上限就是$k \times n + n $ ,这样的话总的时间复杂度就是 $O(nk)$ .
 
 
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 205;
int t, n, k, l, d[N], p[N], mod;
int f[N * N][105];
int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d%d%d", &n, &k, &l);
        mod = 2 * k;
        bool f1 = 0;
        for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
        for(int i = 0; i <= k; i++) p[i] = i;
        for(int i = 2 * k - 1; i >= k + 1; i--) p[i] = 2*k - i;
        for(int i = 0; i <= k * n + n; i++) f[i][0] = 1;
        for(int i = 1; i <= k * n + n; i++){
            for(int j = 1; j <= n; j++){
                f[i][j] = 0;
                if(d[j] + p[i%mod] <= l) f[i][j] = f[i - 1][j]|f[i - 1][j - 1];
            }
            if(f[i][n]) {
                printf("Yes\n"), f1 = 1;
                break;
            }
        }
        if(!f1)printf("No\n");
    }
    return 0;
}
```


---

## 作者：liuyongle (赞：2)

#### 思路分析

考虑模拟Koa的每个可能动作。

设 $\{pos,tide,down\}$ 为一个状态，其中 $pos$ 是Koa的当前位置（即0是海岸，从 $1$ 到 $n$ 是海，$n+1$ 是小岛），$tide$ 是当前潮汐的增量，$down$ 是一个布尔值，如果潮汐正在减小，则为 `true`，否则为 `false`。

对于每个状态（如节点）和每个动作（即等待或游泳），只需执行一次dfs即可判断从海岸是否可以到达该岛。

时间复杂度为 $O(n \cdot k)$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int test;
	cin>>test;
	while(test--) {
		int n,k,l;
		cin>>n>>k>>l;
		vector<int> d(n+2,-k);
		for(int i=1;i<=n;++i)
			cin>>d[i];
		set<tuple<int,int,bool>> mark;
		function<bool(int,int,bool)> go=[&](int pos,int tide,bool down) {
			if(pos>n)
            		return true;
			if(mark.find({pos,tide,down})!=mark.end())
				return false;
			mark.insert({pos,tide,down});
			tide+=down?-1:+1;
            if(!tide)
            		down=false;
			if(tide==k)
            		down=true;
			if(d[pos]+tide<=l && go(pos,tide,down))
				return true;
			if(d[pos+1]+tide<=l && go(pos+1,tide,down))
				return true;
			return false;
		};
		if(go(0,0,false))
            cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：Michael1234 (赞：1)

本题可以使用动态规划的思路：

很明显，可以通过题意设计一种 dp 状态：$dp_{i,j}$ 表示在第 $i$ 个位置上，在 $j$ 时刻时的状态是否可实现。

显然根据题意，可以计算序列 $p$，并推出转移方程：

$$dp_{i,j}=[d_i+p_{j \bmod {2k}} \le l] \times dp_{i-1,j-1} \operatorname{or} dp_{i,j-1}$$

同时，假设每个位置上最多停留 $2k$ 个时刻，则最多需要 $2kn$ 个时刻，这是因为在这 $2k$ 个时刻中可以到达任意潮汐高度，所以只枚举 $2kn$ 个时刻。

并且，当我们安全到达第 $n$ 个位置，我们马上就可以登岛，所以只需枚举 $n$ 个位置。

最后有答案：

$$ans=[(\sum_{i=1}^{2kn}{dp_{n,i}})>0]$$

---

## 作者：ys_kylin__ (赞：1)

这道题是比赛赛题，当时做出来了，还是挺简单的。

一看这个数据范围就是很明显的 DP。可以发现，每个点在不同的时间不一定能过，所以设计一个状态：$dp_{i,j}$ 表示在 $i$ 这个点 $j$ 时刻能否在这里，那么转移是十分简单的：首先要判断在 $j$ 时刻在这里会不会被淹，如果会那就肯定不行。不然的话，他可以由两个状态转移而来：上一个时刻的这个点，上一个时刻的上个点，假如这两个点有一个是一，那 $dp_{i,j}$ 就是一。

```cpp
#include<bits/stdc++.h>
using namespace std;
int d[105];
int f[105][1005];
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		memset(f,0,sizeof f);//多测
		int n,k,l;
		scanf("%d%d%d",&n,&k,&l);
		for(int i=1;i<=n;i++) scanf("%d",&d[i]);
		for(int i=0;i<=1000;i++) f[0][i]=1;//在岸上的所有点都可以。时刻上限设高一点。
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=1000;j++) {
				int tmp=j,cx=0;
				tmp%=(2*k);
				if(tmp>k) cx=2*k-tmp;//判断潮汐
				else cx=tmp;
				cx+=d[i];
				if(cx>l) f[i][j]=0; //会不会被淹
				else {
					if(f[i-1][j-1]==1 || f[i][j-1]==1) f[i][j]=1;//能不能转移
				}
			}
		}
		for(int i=1;i<=1000;i++) {//最后一个点能不能到
			if(f[n][i]==1) {
				printf("Yes\n");
				goto brk;
			}
		}
		printf("No\n");
		brk:
			;
	}
	return 0;
}

```

---

