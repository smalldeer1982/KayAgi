# Air Safety

## 题目描述

[problemUrl]: https://atcoder.jp/contests/m-solutions2020/tasks/m_solutions2020_f

M 君は立派な航空管制官です。

今、彼が管理するレーダーのディスプレイの中では、番号 $ 1,\ 2,\ ...,\ N $ の $ N $ 機の飛行機が、全て同じ高度を飛行しています。  
 各飛行機は秒速 $ 0.1 $ という一定の速度で一定の方向に飛行しており、番号 $ i $ の飛行機の現在の座標は $ (X_i,\ Y_i) $、進行方向は以下の通りです。

- $ U_i $ が `U` の場合：y 座標の正の方向に進む。
- $ U_i $ が `R` の場合：x 座標の正の方向に進む。
- $ U_i $ が `D` の場合：y 座標の負の方向に進む。
- $ U_i $ が `L` の場合：x 座標の負の方向に進む。

M 君の仕事を助けるために、このままでは衝突してしまう飛行機の組が存在するかどうか判定してください。  
 もし存在する場合は、最も早いもので今から何秒後に衝突してしまうかを求めてください。  
 ただし、すべての飛行機は無視できるほど小さく、衝突は $ 2 $ つの飛行機が同じ座標に同時に到達した場合にのみ起こるものとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 0\ \leq\ X_i,\ Y_i\ \leq\ 200000 $
- $ U_i $ は `U`、`R`、`D`、`L` のいずれかである
- $ N $ 機の飛行機の現在位置 $ (X_i,\ Y_i) $ はすべて異なる
- $ N,\ X_i,\ Y_i $ は整数

### Sample Explanation 1

このままでは、$ 230 $ 秒後に、番号 $ 1 $ の飛行機と番号 $ 2 $ の飛行機が同時に座標 $ (11,\ 24) $ に到達し、衝突してしまいます。

### Sample Explanation 2

衝突してしまう飛行機の組はひとつもありません。

## 样例 #1

### 输入

```
2
11 1 U
11 47 D```

### 输出

```
230```

## 样例 #2

### 输入

```
4
20 30 U
30 20 R
20 10 D
10 20 L```

### 输出

```
SAFE```

## 样例 #3

### 输入

```
8
168 224 U
130 175 R
111 198 D
121 188 L
201 116 U
112 121 R
145 239 D
185 107 L```

### 输出

```
100```

# 题解

## 作者：沉石鱼惊旋 (赞：2)

# 题目翻译

你现在拥有 $n$ 架飞机，每架飞机有一个出发点 $(x_i,y_i)$，每架飞机每秒向指定方向飞 $0.1$ 个单位，问什么时候会发生第一次撞击（撞击指两架飞机坐标完全相同），不会发生输出 `SAFE`。

方向：

- $\tt U$ 向上，即向 $y$ 轴正方向运动。
- $\tt R$ 向右，即向 $x$ 轴正方向运动。
- $\tt D$ 向下，即向 $y$ 轴负方向运动。
- $\tt L$ 向左，即向 $x$ 轴负方向运动。

$1\leq n\leq 2\times 10^5,0\leq x_i,y_i\leq 2\times 10^5$。

# 前言

空心黄，五分钟胡完正解实现了一个多小时，终究还是太菜了。

# 题目思路

什么初二一次函数入门题。

首先，飞机相遇有两种大情况，共线面对面或者垂直。

面对面还贡献很好处理，我们把每个方向的飞机按 $x$ 储存在 $4\times 2\cdot10^5$ 个 vector 里，枚举 $x$ 找一下即可。

垂直就要分 $4$ 个小情况了，这里介绍 $2$ 个情况，剩下两个是一模一样只是换个方向。

**但是不要吝啬草稿纸，笔者就是因为发现了 $2$ 种情况非常高兴，剩下 $2$ 种分类错了调试了一个小时。**

我们现在的问题是，如何知道了一个点，找到别的和它垂直的点？

一个小类情况是 UL 和 RD 两种相遇，以 UL 为例，应该长这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/kx0b1dh9.png)

不难发现，我们知道了一个 $(x,y)$，能很容易发现所有的 $(x+z,y+z)$ 能和它垂直。再分析一下，$y-x=(y+z)-(x+z)$，也就是他们的横纵坐标差 $z$ 是相同的。那么我们按 $z$ 开若干 vector 记录即可。实现要注意方向和负数下标。

另一小类是 RU 和 DL。这里以 DL 为例，应该长这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/raxp9zwx.png)

同样不难发现，我们知道了一个 $(x,y)$，能很容易发现所有的 $(x+z,y-z)$ 能和它垂直。再分析一下，$x+y=(x+z)+(y-z)$，也就是他们的横纵坐标之和是相同的。那么我们按横纵坐标之和开若干 vector 记录即可。实现要注意方向。

我们找点可以双指针跑来优化。因为需要排序，所以时间复杂度 $\mathcal O(n\log n)$，空间复杂度 $\mathcal O(n)$。

虽然看上去思维难度不高，但写得拉一点还是很恶心的。

# 丑陋代码

[AT submission 46484503](https://atcoder.jp/contests/m-solutions2020/submissions/46484503)

---

## 作者：Conan15 (赞：1)

容易想到给飞机相撞的情况分类：

1. 横向直接相撞。
2. 纵向直接相撞。
3. 两架飞机在从左下到右上的对角线上。
4. 两架飞机在从左上到右下的对角线上。

观察这四类情况的性质：

1. $x$ 相等。
2. $y$ 相等。
3. $x-y$ 相等。
4. $x+y$ 相等。

所以可以用四个 vector 记录在这些线上的点。\
排序后遍历每一条横、竖线和对角线，并检查是否会有相撞情况产生即可。

代码还挺好写。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 15, M = 4e5 + 15, INF = 0x3f3f3f3f;

struct node { int x, y; char d; };

int n, Minx, Maxx, Miny, Maxy, ans;
vector< node > heng[M], shu[M];
vector< node > st1[M], st2[M];
//st1: 左下 -> 右上
//st2：左上 -> 右下

bool cmpheng(node a, node b) { return a.x < b.x; }
bool cmpshu(node a, node b) { return a.y < b.y; }

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y; char c; scanf("\n %d%d %c", &x, &y, &c);
        node now = (node){x, y, c};
        if (c == 'U' || c == 'D') shu[x].push_back(now);
        if (c == 'L' || c == 'R') heng[y].push_back(now);
        st1[x - y + N].push_back(now);
        st2[x + y].push_back(now);
    }
    for (int i = 0; i <= 400000; i++) {
        if (heng[i].size()) sort(heng[i].begin(), heng[i].end(), cmpheng);
        if (shu[i].size()) sort(shu[i].begin(), shu[i].end(), cmpshu);
        if (st1[i].size()) sort(st1[i].begin(), st1[i].end(), cmpheng);
        if (st2[i].size()) sort(st2[i].begin(), st2[i].end(), cmpheng);
    }
    
    ans = INF;
    for (int i = 0; i <= 200000; i++) { //横向
        if (heng[i].size() <= 1) continue;
        Maxx = -INF;
        for (node it : heng[i]) {
            if (it.d == 'R') Maxx = it.x;
            else if (Maxx != -INF) ans = min(ans, it.x - Maxx);
        }
    }
    for (int i = 0; i <= 200000; i++) { //竖向
        if (shu[i].size() <= 1) continue;
        Maxy = -INF;
        for (node it : shu[i]) {
            if (it.d == 'U') Maxy = it.y;
            else if (Maxy != -INF) ans = min(ans, it.y - Maxy);
        }
    }
    for (int i = 0; i <= 400000; i++) { //左下 -> 右上
        if (st1[i].size() <= 1) continue;
        Maxx = -INF, Maxy = -INF;
        for (node it : st1[i]) {
            if (it.d == 'U') Maxy = it.y;
            if (it.d == 'L' && Maxy != -INF) ans = min(ans, (it.y - Maxy) * 2);
            if (it.d == 'R') Maxx = it.x;
            if (it.d == 'D' && Maxx != -INF) ans = min(ans, (it.x - Maxx) * 2);
        }
    }
    for (int i = 0; i <= 400000; i++) { //左上 -> 右下
        if (st2[i].size() <= 1) continue;
        Maxx = -INF, Miny = INF;
        for (node it : st2[i]) {
            if (it.d == 'D') Maxx = it.x;
            if (it.d == 'L' && Maxx != -INF) ans = min(ans, (it.x - Maxx) * 2);
            if (it.d == 'R') Miny = it.y;
            if (it.d == 'U' && Maxy != INF) ans = min(ans, (Miny - it.y) * 2);
        }
    }
    if (ans == INF) puts("SAFE");
    else printf("%d\n", ans * 5);
    return 0;
}
```

---

## 作者：ran_qwq (赞：0)

约定向上是 $0$，向右是 $1$，向下是 $2$，向左是 $3$。

如果两架飞机 $i,j$ 发生撞击有这么六种情况。除了第六种情况之外钦定 $x_i<x_j$，第六种钦定 $y_i<y_j$：

- $x_i+x_j=y_i+y_j$ 且 $d_i=2$ 且 $d_j=3$。
- $x_i+x_j=y_i+y_j$ 且 $d_i=1$ 且 $d_j=0$。
- $x_i-x_j=y_i-y_j$ 且 $d_i=1$ 且 $d_j=2$。
- $x_i-x_j=y_i-y_j$ 且 $d_i=0$ 且 $d_j=3$。
- $y_i=y_j$ 且 $d_i=1$ 且 $d_j=3$。
- $x_i=x_j$ 且 $d_i=0$ 且 $d_j=2$。

画成图来是这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/om7phqng.png)

开每个 $x_i+x_j$，$x_i-x_j$，$x_i$，$y_i$ 的 vector，对六种情况分别计算即可。以情况一为例，按 $x$ 排序后维护前一个 $d_i=2$ 位置，若碰到 $d_i=3$ 则拿当前位置和前一个 $d_i=2$ 位置 $x$ 坐标相减即可。

```cpp
int n,as=INF/10+1,mn=INF/5+1; vi t[N*2],u[N*2],v[N],w[N];
struct NODE {int x,y,d;} p[N];
il int gt() {char c; scanf(" %c",&c); return c=='U'?0:c=='R'?1:c=='D'?2:3;}
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) p[i]={rd(),rd(),gt()},t[p[i].x-p[i].y+N].pb(i),u[p[i].x+p[i].y].pb(i),v[p[i].x].pb(i),w[p[i].y].pb(i);
	for(int i=0;i<=N*2-20;i++) {
		sort(t[i].begin(),t[i].end(),[&](int x,int y) {return p[x].x<p[y].x;});
		for(int j=0,k=-1;j<t[i].size();j++)
			if(p[t[i][j]].d==1) k=j;
			else if(p[t[i][j]].d==2&&~k) cmin(as,p[t[i][j]].x-p[t[i][k]].x);
		for(int j=t[i].size()-1,k=-1;~j;j--)
			if(p[t[i][j]].d==3) k=j;
			else if(!p[t[i][j]].d&&~k) cmin(as,p[t[i][k]].x-p[t[i][j]].x);
	}
	for(int i=0;i<=N*2-20;i++) {
		sort(u[i].begin(),u[i].end(),[&](int x,int y) {return p[x].x<p[y].x;});
		for(int j=0,k=-1;j<u[i].size();j++)
			if(p[u[i][j]].d==2) k=j;
			else if(p[u[i][j]].d==3&&~k) cmin(as,p[u[i][j]].x-p[u[i][k]].x);
		for(int j=u[i].size()-1,k=-1;~j;j--)
			if(!p[u[i][j]].d) k=j;
			else if(p[u[i][j]].d==1&&~k) cmin(as,p[u[i][k]].x-p[u[i][j]].x);
	}
	for(int i=0;i<=N-10;i++) {
		sort(v[i].begin(),v[i].end(),[&](int x,int y) {return p[x].y<p[y].y;});
		for(int j=0,k=-1;j<v[i].size();j++)
			if(!p[v[i][j]].d) k=j;
			else if(p[v[i][j]].d==2&&~k) cmin(mn,p[v[i][j]].y-p[v[i][k]].y);
	}
	for(int i=0;i<=N-10;i++) {
		sort(w[i].begin(),w[i].end(),[&](int x,int y) {return p[x].x<p[y].x;});
		for(int j=0,k=-1;j<w[i].size();j++)
			if(p[w[i][j]].d==1) k=j;
			else if(p[w[i][j]].d==3&&~k) cmin(mn,p[w[i][j]].x-p[w[i][k]].x);
	}
	as=min(as*10,mn*5);
	if(as>=INF) puts("SAFE");
	else wr(as,"\n");
}
```

---

