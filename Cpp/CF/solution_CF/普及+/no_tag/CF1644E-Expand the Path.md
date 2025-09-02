# Expand the Path

## 题目描述

Consider a grid of size $ n \times n $ . The rows are numbered top to bottom from $ 1 $ to $ n $ , the columns are numbered left to right from $ 1 $ to $ n $ .

The robot is positioned in a cell $ (1, 1) $ . It can perform two types of moves:

- D — move one cell down;
- R — move one cell right.

The robot is not allowed to move outside the grid.

You are given a sequence of moves $ s $ — the initial path of the robot. This path doesn't lead the robot outside the grid.

You are allowed to perform an arbitrary number of modifications to it (possibly, zero). With one modification, you can duplicate one move in the sequence. That is, replace a single occurrence of D with DD or a single occurrence of R with RR.

Count the number of cells such that there exists at least one sequence of modifications that the robot visits this cell on the modified path and doesn't move outside the grid.

## 说明/提示

In the first testcase, it's enough to consider the following modified paths:

- RD $ \rightarrow $ RRD $ \rightarrow $ RRRD $ \rightarrow $ RRRDD $ \rightarrow $ RRRDDD — this path visits cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (1, 4) $ , $ (2, 4) $ , $ (3, 4) $ and $ (4, 4) $ ;
- RD $ \rightarrow $ RRD $ \rightarrow $ RRDD $ \rightarrow $ RRDDD — this path visits cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (3, 3) $ and $ (4, 3) $ ;
- RD $ \rightarrow $ RDD $ \rightarrow $ RDDD — this path visits cells $ (1, 1) $ , $ (1, 2) $ , $ (2, 2) $ , $ (3, 2) $ and $ (4, 2) $ .

Thus, the cells that are visited on at least one modified path are: $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (1, 4) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 2) $ , $ (3, 3) $ , $ (3, 4) $ , $ (4, 2) $ , $ (4, 3) $ and $ (4, 4) $ .

In the second testcase, there is no way to modify the sequence without moving the robot outside the grid. So the only visited cells are the ones that are visited on the path DRDRDRDR.

In the third testcase, the cells that are visited on at least one modified path are: $ (1, 1) $ , $ (2, 1) $ and $ (3, 1) $ .

Here are the cells for all testcases:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1644E/8385744beba9b4eb7d29fe889ed5f7f306a3c22f.png)

## 样例 #1

### 输入

```
3
4
RD
5
DRDRDRDR
3
D```

### 输出

```
13
9
3```

# 题解

## 作者：Troubadour (赞：5)

感觉这题要比 D 简单一些，套路也是非常经典的对于每一个位置算贡献。好了，做完了（

### 题意

给你一个 $n\times m$ 的网格和一个操作序列，初始你在 $(1,1)$，你要按照操作序列操作：每次右移或下移一格。然后你可以把一次操作变为相同的两次，问你所有可能的操作序列一共可以到达多少格子。

### 分析

首先考虑一种特殊情况：假如操作序列只有一个方向，那么答案就是 $n$ 或 $m$。

首先我们按照给出的操作序列走一遍到那个格子，然后求出来这个位置最多可以在横或纵方向上走几格到达 $(n,m)$，记需要右移 $x$ 格，下移 $y$ 格。

在接下来的分析中，为方便起见，我们把格子与格子之间的操作改成格子内部的操作，比如说当前在 $(1,1)$ 然后要向右移，那么我们就把这个格子标记一个右移。当然这么做会漏一个格子，后面会加上的。

考虑计算答案。对于每一个格子，我们最多可以向**这个格子相对的方向**（比如格子是向右的，就考虑向下这个方向）移动 $x$ 或 $y$ 格。因为移动一定是向右向下的，你无论怎么扩展一定不会超出边界或者和别的重合，所以我们可以直接把这些贡献到答案里面。

注意一点，只有在第一次转向及以后才能进行这样的操作（想一想，为什么）。

然后考虑最后一个格子。不难发现，从右下角开始的 $x\times y$ 的所有格子都能走到，我们直接加上去。

### Code 

```cpp
#include<bits/stdc++.h>
#define int long long
namespace GGMZ
{
	const int N = 2e5 + 5;
	char s[N];
	int x, y, n, ans;
	void work()
	{
		bool flag = 1;
		std::cin >> n >> s + 1;
		x = 1, y = 1;
		for (int i = 1;s[i];i++)
		{
			if (s[i] == 'R')x++;
			else y++;
			if (s[i] != s[i - 1] && i != 1)flag = 0;
		}
		if (flag == 1)
		{
			std::cout << n << '\n';
			return;
		}
		x = n - x, y = n - y;
		int i = 2;
		ans = 1;
		while (s[i] == s[i - 1])ans++, i++;
		for (i;s[i];i++)
		{
			ans++;
			if (s[i] == 'R')ans += y;
			else ans += x;
			if (s[i + 1] == 0)ans += (x + 1)*(y + 1);
		}
		std::cout << ans << '\n';
	}
}
#undef int
int main()
{
	int t;
	std::cin >> t;
	while (t--)GGMZ::work();
	return 0;
}
```

---

## 作者：ArrogHie (赞：1)

## 题意

在一个 $n*n$ 的网格中，以最左上角的格子为起点，给定一个字符串 $s$ 表示移动序列，$R$ 表示向右走一格，$D$ 表示向下走一格。

你可以在一个 $R$ 字符后插入一个 $R$，也可以在一个 $D$ 字符后插入一个 $D$，形成一个新的移动序列。该操作次数不限，但形成的移动序列不能移动到网格外。

在所有能形成的合法序列中，问有多少个格子能被至少一个合法的移动序列遍历到。

## 题解
~~这题比D简单多了好嘛~~

如下图（图不严谨，意会即可）：

![](https://i.bmp.ovh/imgs/2022/02/5a6681ad719fcbe2.png)

绿色为原移动序列形成的路径，原路径走完后到达的格子为 $(x,y)$，那么最多复制 $n-x$ 个 $D$，$n-y$ 个 $R$。手玩一下样例能发现，移动序列的终点的位置会出现在红色方框的所有位置。此时我们把最后一步删掉同时把网格缩小一列，变成下图。

![](https://i.bmp.ovh/imgs/2022/02/0c45be13335f3eae.png)

此时重复上面思路会发现终点依然在红色方框区域，依次往下推我们会发现，所有格子都会覆盖以其为左上角的大小为 $(n-x) * (n-y)$ 的方格。

但是当路径为一条直线的时候，根据题意我们只能一直往下或者往右走。所以在原路径出现“拐弯”前的格子是不能覆盖范围为方框的格子的。

于是，答案便很容易求出了，原路径覆盖的格子和以原路径出现第一次拐弯后的所有格子为左上角的大小为 $(n-x) * (n-y)$ 的矩形所覆盖的格子的个数即为答案。简单遍历一遍原路径后容斥一下即可。

---

## 作者：清烛 (赞：0)

题意：给定 $n\times n$ 的网格，一个机器人初始在 $(1,1)$，给定其由若干个 `R` 和 `D` 构成的操作序列，两种字母分别代表右移一格和下移一格。你可以以任意次数将操作序列中的某个操作复制一遍，例如 `RDR` 可以变成 `RDDR` 也可以变成 `RRDR`，但要求机器人不能走出网格。问机器人有可能经过的格子数量。$1\le T\le 10^4$，$2\le n\le 10^8$，操作序列总长 $\le 2\times 10^5$。

首先对于全是 `R` 或全是 `D` 的操作序列，答案显然为 $n$，特判掉即可。

否则令 `R` 的个数为 $\mathrm{cnt}_R$，`D` 的个数为 $\mathrm{cnt}_D$，则我们发现，对于第一个 `RD` 或者 `DR` 之后的每个格子，其都可以覆盖以其为左上角的 $(n - \mathrm{cnt}_R + 1)\times (n - \mathrm{cnt}_D  + 1)$ 的矩形，因为可以通过任意倍增 `R` 或者 `D` 来实现。

现在的问题就是数出这些格子的数量。画图之后可以发现，我们可以行列分开考虑。对于每行的贡献加上对于每列的贡献再加上右下角的矩形即为答案，当然需要统计一下本身走过的路径，详见代码。

```cpp
using ll = long long;
const int maxn = 2e5 + 5;
char s[maxn];

int main() {
    int T; read(T);
    while (T--) {
        ll n, cntr = 0, cntd = 0;
        read(n);
        read(s + 1);
        int len = strlen(s + 1);
        ll nowx = 1, nowy = 1;
        FOR(i, 1, len) {
            if (s[i] == 'D') {
                ++cntd;
            } else {
                ++cntr;
            }
        }
        if (cntr == 0 || cntd == 0) {
            print(n);
        } else {
            ll cntr2 = 0, cntd2 = 0, ans = len + 1; // 首先会覆盖 len + (1,1) 个格子
            if (s[1] == 'R') { // 分类讨论
                ans += (cntd + 1) * (n - cntr - 1); // 这是关于每行的贡献
                FOR(i, 1, len) {
                    if (s[i] == 'D') break;
                    ++cntr2; // 统计开头的 R 操作的个数
                }
                ans += (cntr - cntr2 + 1) * (n - cntd - 1); // 统计关于每列的贡献，需要去除开头的连续的不会产生贡献的 R
            } else { // 下面的情况同理
                ans += (cntr + 1) * (n - cntd - 1);
                FOR(i, 1, len) {
                    if (s[i] == 'R') break;
                    ++cntd2;
                }
                ans += (cntd - cntd2 + 1) * (n - cntr - 1);
            }
            ans += (n - cntr - 1) * (n - cntd - 1); // 最后需要计算右下角的矩形
            print(ans);
        }
        FOR(i, 1, len) s[i] = 0;
    }
    return output(), 0;
}
```



---

