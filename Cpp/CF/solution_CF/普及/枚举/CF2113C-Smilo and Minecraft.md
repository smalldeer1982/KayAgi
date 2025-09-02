# Smilo and Minecraft

## 题目描述

Smilo 在玩 Minecraft！为了准备去打龙，他需要大量的金苹果，所以他需要大量的金子。因此，Smilo 准备下矿。

矿洞是一个 $n\times m$ 的矩形网格，每个格子可能是金矿、石头或空地。Smilo 可以在一个空地点燃炸药，这会将以此空地为中心的边长为 $2k+1$ 的正方形区域夷为平地。如果一个金矿在正方形的内部并且没有和边框相接触，那么它会直接消失；如果金矿在正方形的边框上（在内部并且和正方形的边相接触），Smilo 将会获得这个金子。

求出 Smilo 最多可以获得多少金子。

## 说明/提示

**样例解释**

对于第一组数据，Smilo 可以在任意空地中引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/31cdfd6d4d5bc2d30d1aa78bd3d2c6d2b0fc3eda.png)

对于第二组数据，Smilo 怎么做都不能获得任何金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/a0691441b6e186314d109f809a1563824ebb170d.png)

对于第三组数据，Smilo 可以先在左下角的空地中引爆炸药获得 $2$ 个金子，再在左边一个格子引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/83af7f606c31f060510f0f11993f3494ca718e49.png)

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3
2 3 1
#.#
g.g
2 3 2
#.#
g.g
3 4 2
.gg.
g..#
g##.```

### 输出

```
2
0
4```

# 题解

## 作者：chenly8128 (赞：3)

读题读题再读题！这题最难的就是一个不玩 mc 的人要能看懂题目。

### 题解

首先，只要能先炸出一个洞，那么接下来的爆炸中心只需要上下左右任意移动一格，再爆炸第二次，第二次就可以做到没有金子损失。

按照这个方式移动爆炸中心，就能收集到所有剩下的金子。

所以，有金子损失的有两种情况：

- 第一次爆炸无论如何都会有金子损失。
- 压根无法爆炸，因为全被填满了。

第一种就是求第一次的金子损失的最小值。

换而言之，求原先就有矿井的位置 $(2k+1) \times (2k+1)$ 范围内金子的最小数量。

第二种把最小金块损失设成总金数就行了。

于是，二维差分解决问题。注意最后用总金块减去最小损失。

复杂度 $O(n^2)$。

### 代码

```cpp

// Author: chenly8128
// Created: 2025-06-15 18:10:55

#include <bits/stdc++.h>
using namespace std;
int kase,n,m,k;
char s[505][505];
int sum[505][505];
int main (void) {
	scanf ("%d",&kase);
	while (kase--) {
		scanf ("%d%d%d",&n,&m,&k);
		memset (sum,0,sizeof (sum));
		for (int i = 1;i <= n;i++)
			scanf("%s",s[i]+1);
		for (int i = 1;i <= n;i++) for (int j = 1;j <= m;j++)
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1]
				+ (s[i][j] == 'g');
		int ans = sum[n][m];
		for (int i = k;i <= n+k-1;i++) for (int j = k;j <= m+k-1;j++)
		if (s[i-k+1][j-k+1] == '.') {
			int t = sum[min(i,n)][min(j,m)] - sum[max(i-2*k+1,0)][min(j,m)]
				- sum[min(i,n)][max(j-2*k+1,0)] + sum[max(0,i-2*k+1)][max(j-2*k+1,0)];
			ans = min(ans,t);
		}
		printf ("%d\n",sum[n][m]-ans);
	}
	return 0;
}
```

---

## 作者：DHeasy (赞：3)

~~感觉 C 比 A 简单~~。

手玩一下不难发现，除第一次外，如果每次选择放炸弹的位置和上一次的相邻，那么一定不会将金子炸没，简单证明如下：

> 如果选择和上一次相邻的位置，那么以这个位置为中心，边长为 $2k-1$ 的正方形，一定在以上一次的位置为中心，边长为 $2k+1$ 的正方形内。所以消除的部分（即样例图片中的红色正方形）一定全是空格。

然后就是上一次选择的位置四周相邻的位置一定可以选，证明同上。

于是有一个思路，选择第一次放炸弹的位置，然后之后选择的位置与上一次的相邻即可。

求答案是简单的，找到第一次放炸弹影响最小的（即消去部分金子最少）位置，用总金子个数减去消去的金子个数就是答案。

[提交记录](https://codeforces.com/contest/2113/submission/324652078)

---

## 作者：joe_zxq (赞：1)

诈骗题。被诈了，解法太唐。

其实发现炸一次之后，留出一块边长为 $2k+1$ 的空地之后，只需要将爆炸区域上下左右平移即可收集到剩下的所有金矿。

于是考虑正难则反，枚举出第一次爆炸范围，使得此次最少浪费多少个金矿。

关于如何枚举，二维前缀和维护即可。

---

## 作者：dongzirui0817 (赞：1)

首先，最优情况下，第 $2$ 个及之后的 TNT 是不需要炸烂黄金的。

因为对于在 $(x, \, y)$ 的 TNT 爆炸后，在满足 $|X - x| = 1 \land |Y - y| = 1$ 的 $(X, \, Y)$ TNT 是不会炸毁黄金的。因为就算能炸毁，也先被之前的 TNT 先炸毁（可参考数据 $3$）。

那么现在只需使第一个 TNT 炸毁的黄金最少即可。

然后掏出[二维前缀和](https://oi-wiki.org/basic/prefix-sum/#二维多维前缀和)，秒杀。

[Submission](https://codeforces.com/contest/2113/submission/324487483)

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

讲个笑话，赛时脑子发抽没做出来。

首先我们发现，无法收集到的金矿只有第一次直接被炸没的金矿，因为剩下的都可以通过每次将爆破点平移 $1$ 格保证全部收集到。

所以，我们可以做一次二维前缀和。然后对于每个空位，求出爆炸会炸没多少个金矿，取最小值，用金矿数总和减去这个最小值即为答案。

### Code

```cpp
#include <bits/extc++.h>
using namespace std;

int T,sum[514][514],A,B,C,D,n,m,k,tot;
char ch[514][514];
inline void Solve()
{
    cin >> n >> m >> k;
    --k;
    tot = 0;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            cin >> ch[i][j];
            tot += (ch[i][j] == 'g');
            sum[i][j] = (ch[i][j] == 'g') + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            if(ch[i][j] == '.')
            {
                A = max(i - k,1),B = max(j - k,1),C = min(i + k,n),D = min(j + k,m);
                ans = min(ans,sum[C][D] - sum[A - 1][D] - sum[C][B - 1] + sum[A - 1][B - 1]);
            }
        }
    }
    cout << (tot - ans) << '\n';
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
       Solve();
}
```

---

## 作者：longStone (赞：0)

# CF2113C Smilo and Minecraft 题解

~~MC好评~~

## 题目大意

有个大小为 $n \times m$ 地图里面有金子，石头，和空气，你可以在地图内的空地放置爆炸范围为 $k$ 的炸弹进行轰炸，范围内的元素会被炸毁，之后收集爆炸边界上的金矿。

爆炸范围可能位于地图外，但这不重要。

## 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/iaoetdgx.png)

看图，观察到第一次如果有损失是不可避免的。但是在第一次爆炸后，周围的金矿都被拾取了，所以炸弹可以任意的向上下左右移动 $1$ 格而保证不炸掉任何金矿。以此类推我们就可以采集除了初始爆炸范围外的所有的金矿。

所以问题就变成：选择损失最小的初始爆炸范围。考虑到多测和数据范围，可以使用**二维前缀和**。

## 代码

```c++
#include "bits/stdc++.h"
#define ll long long
using namespace std;
int T, n, m, k, q[505][505], ans;
char c[505][505];
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--)
	{
		cin >> n >> m >> k;
		ans = 0x3f3f3f3f;
		for(int i = 0;i <= max(n, m);i++)	q[i][0] = q[0][i] = 0;
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= m;j++)
			{
				cin >> c[i][j];
				q[i][j] = q[i - 1][j] + q[i][j - 1] - q[i - 1][j - 1] + (c[i][j] == 'g');
			}
		}
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= m;j++)
			{
				if(c[i][j] == '.')	ans = min(ans, q[min(i + k - 1, n)][min(j + k - 1, m)] - q[min(i + k - 1, n)][max(j - k, 0)] - q[max(i - k, 0)][min(j + k - 1, m)] + q[max(i - k, 0)][max(j - k, 0)]);
			}
		}
		cout << q[n][m] - ans << '\n';
	}
	return 0;
}
```

---

