# Chess

## 题目描述

Brian the Rabbit adores chess. Not long ago he argued with Stewie the Rabbit that a knight is better than a king. To prove his point he tries to show that the knight is very fast but Stewie doesn't accept statements without evidence. He constructed an infinite chessboard for Brian, where he deleted several squares to add some more interest to the game. Brian only needs to count how many different board squares a knight standing on a square with coordinates of $ (0,0) $ can reach in no more than $ k $ moves. Naturally, it is forbidden to move to the deleted squares.

Brian doesn't very much like exact sciences himself and is not acquainted with programming, that's why he will hardly be able to get ahead of Stewie who has already started solving the problem. Help Brian to solve the problem faster than Stewie.

## 样例 #1

### 输入

```
1 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2 7
-1 2
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
```

### 输出

```
9
```

# 题解

## 作者：ttq012 (赞：25)

非常简单的 `*3000`，不需要使用任何的高级算法知识。

首先可以考虑暴力 `bfs`，每一次扩展周围的 $8$ 个位置。

但是明显不行。

容易发现，由于 $|x_i|$，$|y_i|$ 的范围非常的小，所以大胆猜测走到一个很大的步数 $step$ 的时候，可以通过一定的公式计算。

于是暴力打表。发现在 $k$ 很大的时候每一步可以走到的位置呈一个公差是 $28$ 的等差数列。

于是在 $k\le step$ 的时候暴力，$k>step$ 的时候暴力计算前 $step$ 个位置，剩下的位置套一个等差数列的公式即可。

然后就过了。

[Code](https://github.com/yuyu1184/Luogu_PT/blob/main/CF57E-Code.cpp)（$step=456$）

---

## 作者：封禁用户 (赞：17)

提供一个感性的对打表结论的证明。

由题意，下图是骑士可以走的地方。

![](https://cdn.luogu.com.cn/upload/image_hosting/ow9l5kuq.png)

定理 $1$：当 $k \in [0,4]$ 时，骑士从无限棋盘上的初始位置出发，需要移动 $k$ 次才能到达的方格数分别为 $1$，$8$，$32$，$68$，这个可以通过计数实现证明。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4dq5fn31.png)

定理 $2$：当 $k \ge 5$ 时，需要移动 $28k-20$ 步。

观察图二，发现答案具有对称性。那么对于 $k \ge 5$ 的情况，可以使用斜率大约为 $\pm 2$ 和 $\pm {\frac{1}{2}}$ 的一次函数将棋盘分解为两种类型的八个区域（即图中标黑白的地方）。

这样我们就可以进行分讨了：

 - 以右边的为例。参考下图，在第 $7$ 列和第 $8$ 列只有 $k=4$ 和 $k=5$，并且 $k=5$ 的格子有 $11$ 个。第 $9$ 列和第 $10$ 列只有 $k=5$ 和 $k=6$,并且 $k＝6$ 的格子有 $13$ 个。
当 $k = 6$ 时，$11 + 13 = 24$ 个格子具有 $13+15=28$ 个后继格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/ajvhud9z.png)

因为矩形的大小增加了四个格子，并且一半的附加格子是白色的，一半是黑色的，所以标记为 $6$ 的 $28$ 个格子在四列中具有$15+17=32$ 个后继格子，就是推到了 $k=7$ 的情况。

以此类推，由于将 $k + 1 \to k$ 会使可达格子的数量增加 $4$，且 $k=5$ 时，答案为 $24$。利用数学归纳法，当 $k \ge 5$ 时，需要移动 $24+4(k-5)=4k+4$ 步。

- 以斜上方的为例，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/gqx61807.png)

在随后的每个黑色区域中，每一列的大小都增加了 $1$，因此有 $3(k-3)$ 个格子将被标记为 $k$。

由此，把二者贡献相加，即：$28k-20$。

参考论文：《Counting the Number of Squares Reachable in k Knight’s MovesAmanda M. Miller, David L. Farnsworth》 阿曼达·米勒，大卫·法恩斯沃斯。

---

## 作者：pufanyi (赞：14)

一道神奇的乱搞题。

首先，对于一个oier，最基本的技能是暴力，于是我们先用bfs打一个暴力（代码下面会有）。

但是除了大暴力，我们似乎并没有什么路可走——因为情况非常复杂。

那么这题为什么这么复杂？

因为有这句话：**可是这个坐标图有点残缺，有几个点是不能跳到的。**

于是我们想到简化：那这句话不在会怎么样？

我们发现一时找不出规律，但我们可以打张表。

```cpp
#include <cstdio>
#include <queue>

using namespace std;

int mp[2003][2003];
int ans[6000];//ans[i]:第i步所到新到达的地方

int dirx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int diry[] = {2, -2, 2, -2, 1, -1, 1, -1};

struct sxd
{
	int x, y;
};

queue<sxd> Q;

int n;
long long k;
long long cnt;

inline void bfs(int x, int y)
{
	mp[x][y] = 1;
	Q.push((sxd){x, y});
	while(!Q.empty())
	{
		sxd tmp = Q.front();
		Q.pop();
		ans[mp[tmp.x][tmp.y]]++;
		if(mp[tmp.x][tmp.y] > 70)
			break;
		for(int i = 0; i < 8; ++i)
		{
			int tx = tmp.x + dirx[i];
			int ty = tmp.y + diry[i];
			if(mp[tx][ty]) continue;
			mp[tx][ty] = mp[tmp.x][tmp.y] + 1;
			Q.push((sxd){tx, ty});
		}
	}
}

int main()
{
	bfs(1001, 1001);
	for(int i = 1; i <= 60; ++i)
		printf("%d,", ans[i]);
	return 0;
}
```

运行结果：

```
1,8,32,68,96,120,148,176,204,232,260,288,316,344,372,400,428,456,484,512,540,568,596,624,652,680,708,736,764,792,820,848,876,904,932,960,988,1016,1044,1072,1100,1128,1156,1184,1212,1240,1268,1296,1324,1352,1380,1408,1436,1464,1492,1520,1548,1576,1604,1632,
```

发现了什么？~~（并没有发现什么）~~到了后面项，该数列竟趋向于一个等差数列！

把`printf("%d,", ans[i]);`改成`printf("%d,", ans[i+1]-ans[i]);`会更清晰：

```
7,24,36,28,24,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
```

然后我们就可以大胆猜想了……

我们发现数据规模中$|xi|, |yi|$的值很小，是不是这样就不怎么会影响等差数列的波动幅度？

于是我们需要验证一下

```cpp
//前面只是把if(mp[tmp.x][tmp.y] > 70)改成了if(mp[tmp.x][tmp.y] > 200)

int main()
{
	bfs(1001, 1001);
	cin >> n;
	for(int i = 1, x, y; i <= n; ++i)
	{
		cin >> x >> y;
		x += 1001;
		y += 1001;
		mp[x][y] = 1;
	}
	for(int i = 1; i <= 150; ++i)//输出多一些，让结论更可信
		printf("%d,", ans[i+1] - ans[i]);
	return 0;
}
```

随便造组数据验证一下：

```cpp
8
2 3
1 2
2 1
5 6
-1 -2
-2 -1
-3 -4
-3 -2
```

输出

```cpp
7,24,36,28,24,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
```

经过多次验证，我们就可以很方便地想到正解：先暴力搜索几步（似乎都是选择500步的），然后用等差数列直接求出答案。

### 于是代码如下

```cpp
//前面的bfs都差不多，就在写一遍了。

signed main()
{
	fin >> k >> n;//由于当时是模拟赛所以用了文件流
	for(int i = 1, x, y; i <= n; ++i)
	{
		fin >> x >> y;
		x += 1001;
		y += 1001;
		mp[x][y] = 1;
	}
	bfs(1001, 1001);
	if(k < 500)
	{
		for(int i = 1; i <= k+1; ++i)
			cnt = (cnt+ans[i])%mod;
		fout << cnt << endl;
	}
	else
	{
		long long inc = ans[500] - ans[499];//等差数列的公差
		k -= 498;
		k %= mod;
		for(int i = 0; i <= 499; ++i)
			cnt = (cnt+ans[i])%mod;
		fout << (((k*ans[500]%mod+cnt)%mod+(k*(k-1)>>1)%mod*inc%mod)%mod+mod)%mod << endl;
	}
	return 0;
}
```

最后，恭喜你打出了一道tourist当场也没打出来的题。

---

