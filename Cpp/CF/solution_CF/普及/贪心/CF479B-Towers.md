# Towers

## 题目描述

As you know, all the kids in Berland love playing with cubes. Little Petya has $ n $ towers consisting of cubes of the same size. Tower with number $ i $ consists of $ a_{i} $ cubes stacked one on top of the other. Petya defines the instability of a set of towers as a value equal to the difference between the heights of the highest and the lowest of the towers. For example, if Petya built five cube towers with heights (8, 3, 2, 6, 3), the instability of this set is equal to 6 (the highest tower has height 8, the lowest one has height 2).

The boy wants the instability of his set of towers to be as low as possible. All he can do is to perform the following operation several times: take the top cube from some tower and put it on top of some other tower of his set. Please note that Petya would never put the cube on the same tower from which it was removed because he thinks it's a waste of time.

Before going to school, the boy will have time to perform no more than $ k $ such operations. Petya does not want to be late for class, so you have to help him accomplish this task.

## 说明/提示

In the first sample you need to move the cubes two times, from the second tower to the third one and from the second one to the first one. Then the heights of the towers are all the same and equal to 6.

## 样例 #1

### 输入

```
3 2
5 8 5
```

### 输出

```
0 2
2 1
2 3
```

## 样例 #2

### 输入

```
3 4
2 2 4
```

### 输出

```
1 1
3 2
```

## 样例 #3

### 输入

```
5 3
8 3 2 6 3
```

### 输出

```
3 3
1 3
1 2
1 3
```

# 题解

## 作者：Alex_Wei (赞：5)

> [洛谷题面传送门](https://www.luogu.com.cn/problem/CF479B) & [CF题面传送门](http://codeforces.com/problemset/problem/479/B)

> 题意简述：有 $n$ 个塔，每个塔的高度为 $a_i$，现在你可以执行**最多 $k$ 次**将一个塔的高度 $-1$，另一个塔的高度 $+1$ 的操作，求 $(\max_{i=1}^{n}a_i)-\min_{i=1}^{n}$ 的最小值以及操作序列。

> P.S. 洛谷题面上好像没有数据范围，这里补充一下：$1\leq n\leq 10^2$，$1\leq k\leq 10^3$，$1\leq a_i\leq 10^4$。

显然的贪心，对于每次操作，我们可以找出 $a_i$ 的最大值以及最小值。

设当前最大值的下标为 $x$，最小值的下标为 $y$（不唯一任意一个即可）。

如果 $a_x-a_y>1$，那么就将 $a_x$ 减去 $1$，$a_y$ 加上 $1$。

为什么？如果 $a_x-a_y=1$，那么进行一次操作后 $a_y$ 就等于原来的 $a_x$，$a_x$ 就等于原来的 $a_y$，**没有任何贡献**。

可以发现，$a_i$ 的值域是在不断减小的，所以我们可以 Two - pointers 进一步减小时间复杂度。

代码里面开了一个桶存储 $a_i$ 落在该值上的下标。

时间复杂度：$\mathcal O(\max(n,k))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a,l=1e9,r;
vector <int> buc[12345],al,ar;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a,buc[a].push_back(i),l=min(l,a),r=max(r,a);
	while(k&&l+1<r){
		int val=min(k,(int)min(buc[l].size(),buc[r].size()));
		k-=val;
		while(val--){
			al.push_back(buc[r].back());
			ar.push_back(buc[l].back());
			buc[r-1].push_back(buc[r].back());
			buc[l+1].push_back(buc[l].back());
			buc[l].pop_back();
			buc[r].pop_back();
		}
		if(!buc[l].size())l++;
		if(!buc[r].size())r--;
	}
	cout<<r-l<<" "<<ar.size()<<endl;
	for(int i=0;i<ar.size();i++)cout<<al[i]<<" "<<ar[i]<<endl;
	return 0;
}
```
求赞 qwq

---

