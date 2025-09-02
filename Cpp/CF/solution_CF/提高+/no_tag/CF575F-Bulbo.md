# Bulbo

## 题目描述

Bananistan is a beautiful banana republic. Beautiful women in beautiful dresses. Beautiful statues of beautiful warlords. Beautiful stars in beautiful nights.

In Bananistan people play this crazy game – Bulbo. There’s an array of bulbs and player at the position, which represents one of the bulbs. The distance between two neighboring bulbs is 1. Before each turn player can change his position with cost $ |pos_{new}-pos_{old}| $ . After that, a contiguous set of bulbs lights-up and player pays the cost that’s equal to the distance to the closest shining bulb. Then, all bulbs go dark again. The goal is to minimize your summed cost. I tell you, Bananistanians are spending their nights playing with bulbs.

Banana day is approaching, and you are hired to play the most beautiful Bulbo game ever. A huge array of bulbs is installed, and you know your initial position and all the light-ups in advance. You need to play the ideal game and impress Bananistanians, and their families.

## 说明/提示

Before 1. turn move to position 5

Before 2. turn move to position 9

Before 5. turn move to position 8

## 样例 #1

### 输入

```
5 4
2 7
9 16
8 10
9 17
1 6
```

### 输出

```
8
```

# 题解

## 作者：hank0402 (赞：5)

## 题解

首先考虑你在 $C$ 这个点，当前轮的游戏区间在 $[A,B]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/fu9emfr3.png)

那么在这个这轮开始前如果移动到 $[B,C]$ 中的一点，这轮游戏结束后的代价都是 $C-B$，并且其为最优解。

所以我们想到保持答案最优的点在一个区间内。

也就是说在这轮游戏前以最优方式移到这个区间内的点都是最优的。

我们考虑维护这个区间，并计算每一轮的最小代价。

我们再来几张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/67e8dy5c.png)

$[A,B]$ 表示这轮的区间，$[C,D]$ 表示最优解区间。

那么在这个点从 $C$ 这个点移到 $[B,C]$ 中任意一点的代价都是最小的 $C-B$。这里答案加上这里 $C-B$ 的代价。
 
$[C,D]$ 在 $[A,B]$ 左边并且没有交的情况也是同理。

![](https://cdn.luogu.com.cn/upload/image_hosting/lchejxvq.png)

这里，$[C,D]$ 与 $[A,B]$ 有交。

那么当前轮一定是在 $[C,D]$ 与 $[A,B]$ 的交内最优，并且代价为 $0$。

一轮轮做过去即可，复杂度 $O(n)$。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, x, ansl, ansr, ans;
signed main() {
    // freopen("ex_travel2.in", "r", stdin);
    scanf("%lld%lld", &n, &x);
    ansl = x, ansr = x;
    for(int i = 1, l, r; i <= n; ++i) {
        scanf("%lld%lld", &l, &r);
        if(ansl > r) {
            ans += ansl - r;
            ansr = ansl;
            ansl = r;
        }
        else if(ansr < l) {
            ans += l - ansr;
            ansl = ansr;
            ansr = l;
        }
        else {
            int tl = ansl, tr = ansr;
            ansl = max(tl, l);
            ansr = min(tr, r);
        }
    }
    printf("%lld", ans);
    return 0;
}
```

## 对算法的一些说明

为什么不多花点代价多移一点，因为这里多出来的移动可以在下一轮处理，所以这个贪心是对的。


---

## 作者：Flowery (赞：3)

这道题感觉很考思维（因为很难想）

### 其实在数轴上主要就三种情况：

1. 自己与当前区间有交集，因此不需要花费，转移到小区间

2. 对方区间右端点在自己区间左端点左边（即没有交集的第一种情况），显然到对方右端点是最优的，自己区间变为对方区间右端点到自己区间左端点这一段

3. 对方区间左端点在自己区间右端点右边（即没有交集的第二种情况），显然到对方左端点是最优的，自己区间变为对方区间右端点到自己左端点这一段

ps:自己区间其实就是自己到对方之间的这段总价值（自己移动的花费与看到灯亮的花费）相等的这段区间

知道这三种情况后就好办了，直接O(n)扫一遍啦。


# Code

```cpp
#define Flowery
#define ll long long
#define rg register int
#include<bits/stdc++.h>
using namespace std;
int n,l,r,u,v;
ll ans;
int main()
{
	scanf("%d%d",&n,&l);r=l;
	for(rg i=1;i<=n;i++)
	{
		scanf("%d%d",&u,&v);
		if(max(l,u)<=min(r,v))l=max(l,u),r=min(r,v);//情况一
		else if(v<l)ans+=(l-v),r=l,l=v;//情况二
		else if(u>r)ans+=(u-r),l=r,r=u;//情况三
	}
	printf("%lld",ans);
	return 0;
}
```
[my blog](https://www.luogu.com.cn/blog/flowery/)

---

## 作者：EuphoricStar (赞：1)

提供一个傻逼 $O(n^2)$ 做法。

首先考虑暴力 dp，设第 $i$ 轮后在 $j$ 坐标上的最小花费为 $f_{i, j}$，有：

$$f_{i, j} = \min f_{i, k} + |j - k| + \begin{cases} l_i - j & j < l_i \\ 0 & l_i \le j \le r_i \\ j - r_i & j > r_i \end{cases}$$

然后你直观感受一下，除了初始位置，到一个区间的端点肯定不劣。离散化一下，拆绝对值后前后缀 $\min$ 优化，就是 $O(n^2)$ 了。

[code](https://codeforces.com/problemset/submission/575/236665514)

---

