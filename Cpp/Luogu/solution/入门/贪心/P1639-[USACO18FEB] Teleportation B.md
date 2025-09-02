# [USACO18FEB] Teleportation B

## 题目描述

Farmer John 最讨厌的农活是运输牛粪。为了精简这个过程，他制造了一个伟大的发明：便便传送门！与使用拖拉机拖着装满牛粪的大车从一个地点到另一个地点相比，他可以使用便便传送门将牛粪从一个地点瞬间传送到另一个地点。

Farmer John 的农场沿着一条长直道路而建，所以他农场上的每个地点都可以简单地用该地点在道路上的位置来表示（相当于数轴上的一个点）。一个传送门可以用两个数 $x$ 和 $y$ 表示，被拖到地点 $x$ 的牛粪可以瞬间传送到地点 $y$，反之亦然。

Farmer John 想要将牛粪从地点 $a$ 运输到地点 $b$，他建造了一个可能对这一过程有所帮助的传送门（当然，如果没有帮助，他也可以不用）。请帮助他求出他需要使用拖拉机运输牛粪的总距离的最小值。 

## 说明/提示

在这个样例中，最佳策略是将牛粪从位置 $3$ 运到位置 $2$，传送到位置 $8$，再运到位置 $10$。 所以需要用拖拉机的总距离为 $1 + 2 = 3$。

## 样例 #1

### 输入

```
3 10 8 2```

### 输出

```
3```

# 题解

## 作者：Iggle_Piggle (赞：13)

[题传](https://www.luogu.com.cn/problem/P1639)

这是一道贪心题。

从起点到终点和从终点到起点是等效的，所以视两者为端点。

设端点 $s,t$ 且 $s<t$，传送门 $p_1,p_2$ 且 $p_1<p_2$。

不妨求从 $s$ 至 $t$ 的最短距离。

设想，若要使用传送门，则一定是从 $p_1$ 到 $p_2$ 的。

采用反证法，假设 $p_2$ 至 $p_1$ 使用传送门。

因为 $s$ 到 $t$ 是向左走，而 $p_2$ 至 $p_1$ 是向右走，所以这样使用传送门一定产生多余的步数。

所以，若要使用传送门，则一定是从 $s$ 至 $p_1$ 再到 $p_2$ 最后到 $t$。

最后我们算答案就从用传送门和不用传送门中，花费距离取最小即可，也即

$$ans=\min(|t-s|,|p_1-s|+|p_2-s|)$$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a, b, c, d;
signed main()
{
	scanf("%d%d%d%d", &a, &b, &c, &d);
	if(a > b) a ^= b ^= a ^= b;
	if(c > d) c ^= d ^= c ^= d;
	printf("%d", min(b - a, abs(c - a) + abs(d - b)));
	return 0;
}
```

---

## 作者：__Floze3__ (赞：12)

## 题意简述

给定起点 $a$，终点 $b$，以及可以互相直达的两点 $x$、$y$。求从 $a$ 到 $b$ 的最短路程。

## 思路简述

不难想到，从 $a$ 点到 $b$ 点一共有三种方式：  
1. 直接从 $a$ 走到 $b$。路程为：$\left| a - b \right|$
2. 从 $a$ 走到 $x$，传送到 $y$，再从 $y$ 走到 $b$。路程为：$\left| a - x \right| + \left| y - b \right|$
3. 从 $a$ 走到 $y$，传送到 $x$，再从 $x$ 走到 $b$。路程为：$\left| a - y \right| + \left| x - b \right|$

直接按照三种方式模拟即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a, b, x, y;

int main(){
    cin >> a >> b >> x >> y;
    cout << min(abs(x - a) + abs(y - b), min(abs(b - a), abs(x - b) + abs(y - a)));
    return 0;
}
```

---

## 作者：xuchuhan (赞：8)

## Solution

总共分 $3$ 种情况。

- 从 $a$ 直接走到 $b$，不使用传送门。走路距离 $\lvert a-b \rvert$。

- 从 $a$ 走到传送门一端 $x$，传送到传送门另一端 $y$，再从 $y$ 走到 $b$。走路距离 $\lvert a-x \rvert+\lvert b-y \rvert$。

- 从 $a$ 走到传送门一端 $y$，传送到传送门另一端 $x$，再从 $x$ 走到 $b$。走路距离 $\lvert a-y \rvert+\lvert b-x \rvert$。

将 $3$ 种情况取 $\min$ 即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,x,y;
signed main(){
	cin>>a>>b>>x>>y;
	int ans1=abs(b-a);
	int ans2=abs(a-x)+abs(b-y);
	int ans3=abs(a-y)+abs(b-x);
	cout<<min({ans1,ans2,ans3});
	return 0;
}
```

---

## 作者：xxboyxx (赞：7)

### 思路

传送门就只有一个，那么也就只有两种情况，用传送门和不用传送门。

不用传送门很好解决，行走距离就是两点之间的距离，为了避免负数，这里使用绝对值，就为 $\left | a-b \right | $。

再来讨论一下用传送门的情况，先走到最近的传送门，然后再统计走到传送门的距离和从传送门另一端走到终点。

再让两种方案求最小值即可。

### 证明

如果使用传送门并走到较远的传送门，肯定会浪费，因为可以直接走到较近的传送门，省下走到较远传送门的距离，就算传送远了，也可以不使用传送门。

### 代码

代码不长，思路简单，建议评红。

```
#include<bits/stdc++.h>
using namespace std;
int a,b,x,y,s;
int main()
{
	cin>>a>>b>>x>>y;
	if (abs(a-x)<=abs(a-y))//到较近的传送门 
		s=abs(a-x)/*走到传送门*/+abs(b-y);/*走到终点*/ 
	else
		s=abs(a-y)+abs(b-x);//同上 
	cout<<min(abs(a-b)/*不用传送门*/,s/*用传送门*/);
	return 0;
}
```


---

## 作者：WoodReal12 (赞：3)

## 思路分析

可以将路径分为三种情况，并取最小值：

- 不用传送门，直接去。

- 用传送门，从 $x$ 传送到 $y$ 点。

- 用传送门，从 $y$ 传送到 $x$ 点（注意：这种情况也是可以的）。

于是，代码就很好实现了。

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int a,b,x,y;
int ans=0; 
int main(){
	cin>>a>>b>>x>>y;
	ans=abs(a-b);//不用传送门
	ans=min(ans,abs(x-a)+abs(y-b));//从x到y 
	ans=min(ans,abs(x-b)+abs(y-a));//从y到x 
	cout<<ans<<endl;
	return 0;
}
```

---

