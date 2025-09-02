# Good Start

## 题目描述

The roof is a rectangle of size $ w \times h $ with the bottom left corner at the point $ (0, 0) $ on the plane. Your team needs to completely cover this roof with identical roofing sheets of size $ a \times b $ , with the following conditions:

- The sheets cannot be rotated (not even by $ 90^\circ $ ).
- The sheets must not overlap (but they can touch at the edges).
- The sheets can extend beyond the boundaries of the rectangular roof.

A novice from your team has already placed two such sheets on the roof in such a way that the sheets do not overlap and each of them partially covers the roof.

Your task is to determine whether it is possible to completely tile the roof without removing either of the two already placed sheets.

## 说明/提示

In the first test case, it is possible to add $ 8 $ roofing sheets as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113B/93f36282728350193810dfbfa6e6dfdf291648d2.png)In the second test case, it is impossible to completely tile the roof:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113B/cebcd94b71d8b7130f37fb6e9fd22f74c727960b.png)

## 样例 #1

### 输入

```
7
6 5 2 3
-1 -2 5 4
4 4 2 2
0 0 3 1
10 9 3 2
0 0 4 3
10 9 3 2
0 0 6 3
5 5 2 2
-1 -1 4 -1
5 5 2 2
-1 -1 2 3
7 8 2 4
0 0 0 5```

### 输出

```
Yes
No
No
Yes
No
Yes
No```

# 题解

## 作者：longStone (赞：0)

# CF2113B Good Start 题解

## 题目大意

屋顶是大小为 $w \times h$ 的矩形，左下角位于平面上的点 $(0,0)$。求是否可以在已经盖上 $2$ 块板的情况下让屋顶板盖住整个屋顶。屋顶板不能旋转，也不能重叠，但是可以超出屋顶。

## 思路

因为屋顶板完全不能旋转，所以我们需要考虑的就是顺着已经放置好的屋顶板**横着摆放**和**竖着摆放**。

- 当两块屋顶版位于同一列时，我们只需要考虑两块板上下之间的那一部分是否可以填充满。
- 当两块屋顶版位于同一行时，我们只需要考虑两块板左右之间的那一部分是否可以填充满。
- 否则，两种方式均可。

## Code

```c++
#include "bits/stdc++.h"
using namespace std;
int T, w, h, a, b, x1, yy1, x2, y2;
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--)
	{
		cin >> w >> h >> a >> b >> x1 >> yy1 >> x2 >> y2;
		if(x1 == x2)	cout << (abs(y2 - yy1) % b?"No\n":"Yes\n");
		else if(yy1 == y2)	cout << (abs(x2 - x1) % a?"No\n":"Yes\n");
		else	cout << ((abs(x2 - x1) % a && abs(y2 - yy1) % b)?"No\n":"Yes\n");
	}
	return 0;
}
```

---

