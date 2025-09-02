# Maze 1D

## 题目描述

Valera has a strip infinite in both directions and consisting of cells. The cells are numbered by integers. The cell number $ 0 $ has a robot.

The robot has instructions — the sequence of moves that he must perform. In one move, the robot moves one cell to the left or one cell to the right, according to instructions. Before the robot starts moving, Valera puts obstacles in some cells of the strip, excluding cell number $ 0 $ . If the robot should go into the cell with an obstacle according the instructions, it will skip this move.

Also Valera indicates the finish cell in which the robot has to be after completing the entire instructions. The finishing cell should be different from the starting one. It is believed that the robot completed the instructions successfully, if during the process of moving he visited the finish cell exactly once — at its last move. Moreover, the latter move cannot be skipped.

Let's assume that $ k $ is the minimum number of obstacles that Valera must put to make the robot able to complete the entire sequence of instructions successfully and end up in some finishing cell. You need to calculate in how many ways Valera can choose $ k $ obstacles and the finishing cell so that the robot is able to complete the instructions successfully.

## 说明/提示

In the first sample Valera mustn't add any obstacles and his finishing cell must be cell $ 2 $ .

In the second sample, Valera must add an obstacle in cell number $ 1 $ , and his finishing cell must be cell number $ -1 $ . In this case robot skips the first two moves and on the third move he goes straight from the starting cell to the finishing one. But if Valera doesn't add any obstacles, or adds an obstacle to another cell, then the robot visits the finishing cell more than once.

## 样例 #1

### 输入

```
RR
```

### 输出

```
1
```

## 样例 #2

### 输入

```
RRL
```

### 输出

```
1
```

# 题解

## 作者：wlj_55 (赞：3)

## 题目分析

**首先我们可以看出，一堵墙只有被机器人撞到才是有用的墙。**

先考虑没有墙的情况，直接模拟即可。

我们再考虑两堵墙的情况，此时一共有两种可能：

- 墙在原点同侧

- 墙在原点异侧

在同侧的情况可以首先排除，因为前面的一堵墙可以挡住机器人的所有可能超过它的指令，所以后面的那堵墙永远不可能被机器人撞到。

那么异侧的情况呢？

根据最前面得出的理论，两堵墙都要被撞到才是有用的，那么此时我们会发现机器人的路径肯定覆盖了两堵墙间所有的点，那么就不可能使机器人最后一步停在一个没有走过的点上。

综上所述，墙的数量只可能为 $0$ 或 $1$ 。
 
那么考虑墙的数量为 $1$ 的情况，当最后一个操作是 "L" 的话，那么一种符合题意的情况最后一步必然在原点左边，反之同理。

那么我们可以推出如果一个点可以放置墙使得该情况符合题意，那么更靠近原点的摆放方式一定可以，因为它抵消了更多的反向移动。

所以直接二分出墙可能在的最大位置即可。

时间复杂度 $\mathcal{O}(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, npos, maxp, minp;
char ch[1000005];
int chk(int pos) {      //判断墙放在pos处是否可行，pos=0代表不放墙 
	npos = maxp = minp = 0;
	for(int i = 1; i <= n; i++) {
		maxp = max(maxp, npos);
		minp = min(minp, npos);
		npos += (ch[i] == 'R') ? 1 : -1;
		if(pos && npos == pos)  npos -= (ch[i] == 'R') ? 1 : -1;
	}
	return npos > maxp || npos < minp;
}
int main() {
	scanf("%s", ch + 1);
	n = strlen(ch + 1);
	if(chk(0)) {
		puts("1");
		return 0;
	}
	if(ch[n] == 'L') {
		int l = 1, r = 1E6, ans = 0;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(chk(mid))  ans = mid, l = mid + 1;
			else  r = mid - 1;
		}
		cout << ans << endl;
		return 0;
	}
	int l = -1E6, r = -1, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(chk(mid))  ans = mid, r = mid - 1;
		else  l = mid + 1;
	}
	cout << abs(ans) << endl;
}
```


---

## 作者：_Ponder_ (赞：1)

[Maze 1D](https://www.luogu.com.cn/problem/CF404E)

### 题目大意

在数轴上给定一串行动指令，类型有两种：向左移动一个单位 / 向右移动一个单位。要求最后一步到达一个没有到达过的位置。可以在数轴上放置若干个障碍物阻碍移动，问在放置的障碍物最少的情况下有多少放置方式。

### 思路分析

结论题。

结论一：**障碍物的数目不多于 $1$**。

- **证明**：

若可以在不放置任何障碍物的情况下满足要求，那么障碍物的数目为 $0$，放置方式为 $1$。

否则，一定可以通过放置**恰好**一个障碍物达成目标。

考虑放置两个障碍物的情况：

- 二者都在原点同侧：

此时离原点更远的障碍物没有任何作用，可以舍去。

- 一个在左一个在右：

如果两个障碍物都被触碰到，那么意味着所有可以被到达的地方均被到达过，不满足要求。

反之，如果存在一个障碍物没有被触碰到，那么它没有作用，可以舍去。

更多障碍物的情况可以归结为这两种情况的组合。

结论二：**若最后一步往左，那么障碍物在原点右侧，否则障碍物在原点左侧**。

- **证明**：

考虑**反证法**：

假设最后一步往左，且障碍物在原点左侧：

考虑到中途一定会触碰障碍物，所以总到达的区间是：左侧障碍物，右侧不确定，但最后一步移动起始的位置一定位于这个区间内，又因为区间左侧被封死，所以不可能到达新的位置。与要求矛盾，故结论成立，右侧同理。

结论三：**障碍物放置的合法区间一定是从原点到某一点的连续区间**。

- **证明**：

考虑到移动序列长度有限，故障碍物一定存在一个最远的可以放置的点，那么将障碍物从这个点向原点靠近，抵消的不利操作一定会越来越多，考虑到其单调性，结论显然成立。

在有了这三个结论之后这题就比较简单了：

二分找出最远的能放置的点，二分的判定直接暴力模拟即可。

### 代码

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N=1001000;

int n;
int vis[N<<1];

char inp[N];

bool walk(int B){//模拟
	int x=N,res;
	for(int i=1;i<=n;i++){
		vis[x]=1;
		if(inp[i]=='R'&&x+1!=B) x++;
		if(inp[i]=='L'&&x-1!=B) x--;
	}
	res=!vis[x];
	x=N;
	for(int i=1;i<=n;i++){//清空
		vis[x]=0;
		if(inp[i]=='R'&&x+1!=B) x++;
		if(inp[i]=='L'&&x-1!=B) x--;
	}
	return res;
}

int main(){
	scanf("%s",inp+1);
	n=strlen(inp+1);
	if(walk(-N)){cout<<"1\n";return 0;}//先判断不放合不合法
	if(inp[n]=='L'){//看最后一步往哪边
		int l=N,r=N*2;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(walk(mid)) l=mid;
			else r=mid-1;
		}
		cout<<l-N<<'\n';
	}
	if(inp[n]=='R'){
		int l=1,r=N;
		while(l<r){
			int mid=(l+r)>>1;
			if(walk(mid)) r=mid;
			else l=mid+1;
		}
		cout<<N-r<<'\n';
	}
	return 0;
}
```

---

