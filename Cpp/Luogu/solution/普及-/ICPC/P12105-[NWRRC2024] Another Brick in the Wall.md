# [NWRRC2024] Another Brick in the Wall

## 题目描述

Alice 喜欢搭建玩具墙。她拥有许多 $1 \times 2$ 的砖块和数量有限的 $1 \times 3$ 砖块。两种砖块的高度均为 1 且不可旋转。

Alice 打算用这些砖块建造一堵长度为 $l$、高度为 $h$ 的单层厚度墙。一堵墙被称为$\textit{坚固的}$，当且仅当不存在上下直接对齐的砖缝。

![](https://cdn.luogu.com.cn/upload/image_hosting/zgs4gn57.png)

请帮助 Alice 计算出建造一堵长度为 $l$、高度为 $h$ 的坚固墙所需的最少数量的 $1 \times 3$ 砖块。

## 样例 #1

### 输入

```
7 4```

### 输出

```
4```

# 题解

## 作者：穼柗° (赞：3)

注意到题目里面的这幅图。

![](https://cdn.luogu.com.cn/upload/image_hosting/0l5bfzms.png?x-oss-process=image/resize,h_170,w_225)

可以发现，每行都在最左或最右放了一个 $1\times 3$ 砖头，并且不能放得更少。不难想到当 $l$ 为奇数时答案就是 $h$，因为如果这样放，一行长度就是 $3+2k(k\in\Z)$，一定为奇数。

当 $l$ 为偶数时，可以想几个例子。
- $6\times4$ 墙的最佳方案：$2$ 个 $1\times3$ 砖头和 $3$ 个 $1\times2$ 砖头交替。
- $8\times4$ 墙的最佳方案：$2$ 个 $1\times3$ 砖头加上 $1$ 个 $1\times2$ 砖头和 $4$ 个 $1\times2$ 砖头交替。

不难发现，$l$ 为偶数时最佳方案是 $2$ 个 $1\times3$ 砖头加上 $\frac{l-6}2$ 个 $1\times2$ 砖头和 $\frac{l}2$ 个 $1\times2$ 砖头交替。要让 $1\times3$ 砖头使用得尽量少就要使“$2$ 个 $1\times3$ 砖头加上 $\frac{l-6}2$ 个 $1\times2$ 砖头”的一行尽量少，这样的一行有 $\lfloor\frac{h}2\rfloor$ 个。答案就是 $\lfloor\frac{h}2\rfloor\times2$。

---

## 作者：yangfengzhao (赞：1)

## 题意
将一面 $h \times l$ 的墙面，全部用 $1 \times 3$ 填充。求最最少的砖块数量。
## 推导
1. 考虑按着行放，如果 $l=3n$（$n$ 为一行的砖块数）成立（即：单行是 $3$ 的倍数）就按这样贴，答案就是：$h \times n$。
2. 如果不满足，那么就是照其余数而定。余数是 $t$ 就按列放 $t$ 块。但是每一块列放的砖会影响到后面两行，所以有必要将 $h$ 判断一下。
---
可以推导出一个通用公式：$ans=\lfloor \frac{l}{3}\rfloor \times h+\lceil \frac{h}{3}\rceil \times (l \bmod 3)$
## 代码
```cpp
#include <cstdio>
using namespace std;

int main() {
    int l, h;
    scanf("%d%d", &l, &h);
    int base = l / 3;         // 每行横向砖块数
    int remain = l % 3;       // 剩余宽度
    int vertical = (h + 2) / 3; // 纵向铺设次数（向上取整）
    printf("%d\n", base * h + vertical * remain);
    return 0;
}
```

---

## 作者：Wendy_Hello_qwq (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/P12105)

## 题意

给定一堵宽 $l$ 高 $h$ 的墙面，用 $1 \times 3$ 尺寸的砖块铺墙面，求出铺的最小数量的砖块。

## 分析

首先对于墙面宽 $l$ 进行分类讨论：

- $l$ 为奇数的情况：由于砖块尺寸是 $1 \times 3$，那么不难想到，在墙面的左边或右边铺上 $1 \times 3$ 的砖块，中间总会剩下若干个 $1 \times 2$ 的砖块，那么不难想到最小数量就是 $h$。

- $l$ 为偶数的情况：只要在墙面的左右两边铺上 $1 \times 3$ 的砖块，那么这样一共有 $\lfloor \frac{h} 2 \rfloor$ 行，所以答案就是 $\lfloor \frac{h} 2 \rfloor \times 2$。

分类讨论结束后，根据条件判断并输出即可，代码十分简短。

## Code 

```cpp
// P12105 [NWRRC2024] Another Brick in the Wall
#include <cstdio>
using namespace std;
int l, h;
signed main() {
	scanf ("%d%d", &l, &h);
	// 分类讨论，l 为偶数 
	if (l % 2 == 1) printf ("%d", h);
	// l 为奇数 
	else printf ("%d", 2 * (h / 2));
	return 0;
}
```

[AC 记录。](https://www.luogu.com.cn/record/215464000)

完结撒花。

---

## 作者：xiezheyuan (赞：1)

注意到题目保证 $5\leq l$，这很好，省去了一些细节分讨。注意到若 $2\mid l$，一种平凡的方法是全放 $1\times 2$ 的砖，但是这样子砖缝会对齐，可以在偶数层最左侧放两个 $1\times 3$ 的砖，故答案为 $2\cdot(\frac{h-1}{2})$。若 $2\nmid l$，则每一层都必须放 $1\times 3$，可以交替将 $1\times 3$ 放到每层第一个 / 第二个砖来保证砖缝不对齐，故答案为 $h$。[QOJ Submission](https://qoj.ac/submission/986589)。

---

## 作者：DevilsFlame (赞：1)

题目不再赘述。

由题意，我们尽可能的多用 $1 \times 2$ 的砖块。若 $l \equiv 1 \pmod{2}$，不难想到 $ans = h$，因为为了没有缝是直接对齐的，具体如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/i7t4kvde.png)

其中，蓝线连接起来的是一块砖。

继续讨论 $l \equiv 0 \pmod{2}$ 的情况。

其实对于 $1 \times 2$ 的砖，如果是互相交错是刚好的，而 $1 \times 3$ 刚好是为了补足剩余的空。各位可以先画只用 $1 \times 2$ 的砖搭墙。不难发现，有一些空的地方（都是在边上）相邻的砖换成 $1 \times 3$，那就是我们的最优解。以此不难推出式子 $ans = \lfloor \frac{h}{2} \rfloor \times 2$。注意 $1 \times 2$ 的砖要放在底下，对于 $l \equiv 0 \pmod{2}$ 的情况，自己需要注意。

---

## 作者：yihang2011 (赞：0)

### [题解：P12105 [NWRRC2024] Another Brick in the Wall](https://www.luogu.com.cn/problem/P12105)

小小思维题。

根据 $7 \times 4$ 的样例，注意到当 $2 \mid l$ 时，在每一行的最左边或最右边交替放置 $1 \times 3$ 的砖块，剩下的放置 $1 \times 2$ 的砖块，这样每一行行宽都是 $3 + 2k (k \in \mathbb{Z})$，必定为奇数。答案为 $h$。

否则可以在偶数行的最左侧和最右侧各放一个 $1 \times 3$ 的砖块，其余用 $1 \times 2$ 的砖块填充，可以保证偶数行和奇数行的砖块不对齐，偶数行行宽 $2 \times 3 + 2k (k \in \mathbb{Z})$，奇数行行宽 $2k (k \in \mathbb{Z})$，均为偶数。这种放置方法使用两倍的偶数行行数的 $1 \times 3$ 的砖块。答案为 $2 \times \lfloor \frac{h}{2} \rfloor$。

代码过于简单不放了。

---

## 作者：_Star_Universe_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P12105)
### 思路
较基础的一个分类讨论题。数据范围中提到 $l>5$ 其实已经帮我们除去了搭不出墙的情况，那么分两类讨论即可。

- 当 $l$ 为奇数时，很显然我们可以在墙的最多端和最右端交错着铺 $1 \times 3$ 的砖块，剩下的部分一定能用 $1 \times 2$ 的砖块填满，这样做必定不会出现上下重合的砖缝，因此易得
$$ans = h$$
- 当 $l$ 为偶数时，因为题目要求节省 $1 \times 3$ 的砖块，我们可以在最底层铺上 $l \mid 2$ 个 $1 \times 2$ 的砖块，第二层两头先铺上 $1 \times 3$ 的砖块，若中间还有空隙，再拿一些 $1 \times 2$ 的砖块补上。因此易得
$$ans = 2 \times \lfloor \frac{h}{2} \rfloor$$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int l,h;
    cin>>l>>h;
    if(l%2==1) cout<<h;
    else cout<<2*(h/2);
    return 0;
}
```

---

## 作者：Merlin_Meow (赞：0)

## Analysis

我们先来看一下只用 $1\times 2$ 砖，墙的两端不需要对齐时建出来的东西，它一定是长成这样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/jz8y2193.png)

我们很容易想到 $1\times 3$ 砖只需要用来填补缝隙即可。

对于上图的这种情况，我们把每行有空缺的一端换成 $1\times 3$ 的砖，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dz34nw82.png)

容易发现此时答案为 $h$。

再来讨论 $l$ 为偶数的情况，我们显然只需要每隔一行将左右两端全部换成 $1\times 3$ 砖，这样的行一共有 $\lfloor \dfrac{h}{2}\rfloor$ 个，那么答案就是 $2\times \lfloor \dfrac{h}{2}\rfloor$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

int l, h;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> l >> h;
    if (l % 2)
        cout << h << endl;
    else
        cout << 2 * (h / 2) << endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这道题让我们建一个墙，要求只能用横着的 $1\times2$ 和 $1\times3$ 砖块，并且不能有两条竖着的缝相连。

刚开始一看，这不水题吗。然后打了一份 [B2003](https://www.luogu.com.cn/problem/B2003)，交上去 WA 了。

### 思路

如果 $l$ 是奇数，答案就是 $h$。只需要从上到下每一行依次在最左边、最右边放置 $1\times3$ 砖块就可以了。

如果 $l$ 是偶数，答案是 $2 \lfloor \frac{h}{2} \rfloor$。只需要在奇数行全放置 $1\times2$ 砖块，偶数行在最左边和最右边放置 $1\times3$ 砖块，其他时候放置 $1\times2$ 砖块。这样答案就是偶数行的数量乘上 $2$。如果再少，就一定有 $2$ 个相邻行全放置 $1\times2$ 的砖块，这是不合法的。

时间复杂度 $O(1)$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    if(a%2==1)cout<<b;
    else cout<<2*(b/2);
}
```

---

