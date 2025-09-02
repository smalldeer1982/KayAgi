# [USACO14FEB] Airplane Boarding G

## 题目描述

FJ's cows have decided to take a vacation, and have miraculously managed to find an airline willing to sell them tickets.  When they arrive at the airport and start boarding their plane, they face an interesting problem, however.

The airplane has N seats, which we model as the points x=1 through x=N on the number line.  All N cows (1 <= N <= 200,000) are standing in line waiting to get to their seats.  Cow N is at position x=0, Cow N-1 is at position x=-1, and so on.  Cow i has been assigned to Seat S\_i, where S\_1,...,S\_N is a permutation of 1,...,N.

At each time step, each cow takes a step to the right if she can. When cow i reaches her seat S\_i, she will stop to put her baggage in the overhead bin, which takes T\_i seconds, and then sit down. For those T\_i steps, the cow behind her (if there is one) is blocked from moving forward.  If there is a line of cows behind her, the line is effectively blocked as well.

How long will it take for all the cows to sit down? 

The sum of T\_i for all cows will be less than 1,000,000,000. 

想象一下飞机有N个座位，N个座位相当于数轴上的1至N共N个整点，第1个座位在整点1处，第2个座位在整点2处，……第N个座位在整点N处。


有N个奶牛排好队，要登陆坐飞机，第N头奶牛在数轴的整点0处，第N−1头奶牛在数轴的整点−1处，……第1头奶牛在数轴的整点−N+1处。第i头奶牛的座位号是Si。注意：每头奶牛都有唯一的一个座位，不会出现多头奶牛有相同的座位号。


在每一秒钟，奶牛会向右移动一步到达下一个整点，前提是没有奶牛挡住它。 当第i头奶牛到达它的座位Si时，它需要花费Ti秒去把行李放到头顶的行李架上，然后坐到自己的位置上，在此过程中，由于飞机通道很窄，所以在第i头奶牛坐到自己座位之前，在它左边的所有奶牛都不能动，要等奶牛i放好行李坐好后才能动。


现在的问题是，至少要多少秒之后，所有的奶牛都能做到自己的座位上？


## 说明/提示

Initially, the cows are situated like this:

cows -> 123

123 <- seats 

with cow 1 trying to get to seat 2, cow 2 trying to get to seat 3, and cow 3 trying to get to seat 1.


After one step, they will all move 1 to the right and cow 3 will reach her seat:

123
123
Cow 3 takes 5 seconds to sit down, at which point she effectively disappears.

12
123
It takes 3 more seconds for cows 1 and 2 to reach their desired seats:

12
123
It takes 5 seconds for cow 1 to sit down and 10 seconds for cow 2 to sit down, so that's 10 seconds total.

In total this took 1 + 5 + 3 + 10 = 19 seconds. 



## 样例 #1

### 输入

```
3 
2 5 
3 10 
1 5 
```

### 输出

```
19 
```

# 题解

## 作者：xixike (赞：22)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15807885.html)

## $Description$

[Luogu传送门](https://www.luogu.com.cn/problem/P3103)

## $Solution$

偶然发现这道题所以来做做。

刚开始看完题的时候感觉这只能暴力模拟……

~~于是不要脸的看了一眼题解之后~~，我们可以用一些表达式来表示每头奶牛到达它应该到的位置的时间，从而计算出总共时间。

具体来说，第 $n$ 头牛到达其位置所用时间是 $s_n + t_n$，第 $n - 1$ 头牛到达 $s_n$ 的时间就是 $s_n + t_n + 1$（因为 $cow_{n - 1}$ 初始坐标比 $cow_n$ 的坐标靠左 1）

所以我们可以用二元组 $(pos_i, time_i)$ 来表示一头牛到达 $pos_i$ 所花的时间为 $time_i$，对于一头牛有许多这样的二元组来限制它。

那么这只牛走到目的地的时间就是 $\max\{time_i + (S - pos_i)\} + T$，二元组满足条件 $pos_i \leq S$。

我们再把 $S$ 提出来，所以要找的就是 $time_i - pos_i$ 的最大值。

但是目前复杂度还是 $n^2$ 的，我们还要考虑如何优化。

~~不难发现~~，对于两个二元组限制条件 $(a, b)$ 和 $(c, d)$，如果 $a < c$ 且 $d - c < b - a$，那么 $(c, d)$ 对于以后所有的奶牛都是没有用的。

$d - c < b - a$  使得 $(c, d)$ 对于当前的奶牛没有贡献，再加上 $a < c$ 使得 $(c, d)$ 这个条件对于后面所有的奶牛都没有了贡献。

所以我们直接把这个条件删掉即可。

用平衡树维护一下 $pos$ 和 $time - pos$ 的值，以及 $time - pos$ 的最大值，倒序枚举每一头奶牛：

- 查询：把 $pos \leq S_i$ 的数切下来查询。
- 修改：当前插入的二元组是 $(a, b)$，然后把树中 $d - c > b - a$ 的点全都删掉。

然后就没别的了，具体见代码吧。

我写的 fhq-treap

## $Code$

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 2e5 + 10;
int n;
int S[N], T[N];

namespace FHQ_treap{
    #define ls(x) t[x].l
    #define rs(x) t[x].r

    struct tree{
        int sum, wei, l, r, x, y, val, tag;
    }t[N];
    int root, tot;

    inline void pushup(int x){
        if(!x) return;
        t[x].val = t[x].y;
        if(ls(x)) t[x].val = max(t[x].val, t[ls(x)].val);
        if(rs(x)) t[x].val = max(t[x].val, t[rs(x)].val);
    }

    inline void pushdown(int x){
        if(!x || !t[x].tag) return;
        int tag = t[x].tag;
        if(ls(x)){
            t[ls(x)].x -= tag, t[ls(x)].y += tag;
            t[ls(x)].tag += tag, t[ls(x)].val += tag;
        }
        if(rs(x)){
            t[rs(x)].x -= tag, t[rs(x)].y += tag;
            t[rs(x)].tag += tag, t[rs(x)].val += tag;
        }
        t[x].tag = 0;
    }

    inline void split_pos(int x, int k, int &a, int &b){
        if(!x) return a = b = 0, void();
        pushdown(x);
        if(k >= t[x].x) a = x, split_pos(rs(x), k, rs(x), b);
        else b = x, split_pos(ls(x), k, a, ls(x));
        pushup(x);
    }

    inline void split_val(int x, int k, int &a, int &b){
        if(!x) return a = b = 0, void();
        pushdown(x);
        if(k >= t[x].y) a = x, split_val(rs(x), k, rs(x), b);
        else b = x, split_val(ls(x), k, a, ls(x));
        pushup(x);
    }

    inline int merge(int x, int y){
        if(!x || !y) return x | y;
        if(t[x].wei <= t[y].wei){
            pushdown(x);
            rs(x) = merge(rs(x), y);
            return pushup(x), x;
        }else{
            pushdown(y);
            ls(y) = merge(x, ls(y));
            return pushup(y), y;
        }
    }

    inline int newnode(int a, int b){
        t[++tot].x = a, t[tot].y = t[tot].val = b, t[tot].wei = rand();
        return tot;
    }
}
using namespace FHQ_treap;

int main(){
    n = read();
    for(int i = 1; i <= n; ++i)
        S[i] = read(), T[i] = read();
    int ans = 0, a, b, c;
    root = newnode(0, 0);
    for(int i = n; i >= 1; --i){
        split_pos(root, S[i], a, b);
        int res = t[a].val + S[i] + T[i];
        ans = max(ans, res);
        t[a].tag++, t[a].x--, t[a].y++, t[a].val++;//奶牛初始坐标向左依次减 1，对于 (a, b) 来说相当于变成了 (a - 1, b)
        split_val(b, res + 1 - S[i], b, c);
        root = merge(a, merge(newnode(S[i], res + 1 - S[i]), c));
    }
    write(ans), puts("");
    return 0;
}
```

$$
\_EOF\_
$$


---

## 作者：Usada_Pekora (赞：15)

$cow_n$ 在 $t=0$ 的时候位于 $0$ 的位置，并且在时间 $S_n$ 时走到自己位置， $S_n + T_n$时坐下。对于 $cow_{n-1}$ 的限制是：在时间 $S_n + T_n+1$ 时才能走到 $S_n$ 。

设对 $(a,b)$ 表示在时间 $b$ 时才能到 $a$ 位置。

$O(n^2)$ 做法：我们将把对储存下来。对于 $cow_i$，搜索 $b-a$ 最大且满足 $a<S_i$ 的对 $(a,b)$。计算 $cow_i$ 坐下的时间 $(V_i=b-a+S_i+T_i)$ 。然后，将 $(S_i,V[i])$ 插入列表（在时间 $V_i$ 时，$cow_i$ 必须在座位 $S_i$  ）。为了转移到 $cow_{i-1}$ ，我们通过将所有 $(a,b)$ 替换为 $(a-1,b)$ 来执行更新，使得$a \leq S_i$。

$O(n \log n)$ 做法：我们观察到，对于两个对 $(a,b)$  ， $(c,d)$ ,如果 $a<c$ 且 $b-a>d-c$ ， $(c,d)$ 就没用了。在插入 $(a,b)$ 之后，删除所有 $c>=a$ 且 $d-c<=b-a$ 的对$(c,d)$。

我们需要一个能够支持搜索步骤、插入步骤和范围更新步骤的数据结构。你以为我们要用平衡树吗？不，我们用跳表！

跳表是一种随机化的数据结构，可以被看做二叉树的一个变种，插入、查询、删除都是 $O(\log n)$ 的。而且非常好打。

```cpp
#include <cstdio>
#include <cstdlib>
const int N = 200100,H = 22;
int s[N], t[N], nxt[H + 1][N], lazy[H + 1][N], a[N], b[N], n, cur, head = 1;
inline int read(){
	int x = 0, ch = getchar();
	while(ch < '0' || ch > '9')ch = getchar();
	while(ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x;
}
inline void down(int r, int n) {
  if (r == 0) return;
  bool first = true;
  for(int x = n; x != nxt[r][n]; x = nxt[r - 1][x]) {
    if (!first) a[x] -= lazy[r][n];
    first = false;
    lazy[r - 1][x] += lazy[r][n];
  }
  lazy[r][n] = 0;
}
inline int getheight() {
  for(int i = 0; i < H; ++i) if (rand() % 2) return i;
  return H; 
}
inline bool cmp(int x, int y) {
  return b[x] - a[x] >= b[y] - a[y];
}
int main() {
  srand(NULL);
  n = read();
  for(int i = 1; i <= n; ++i) s[i] = read(), t[i] = read();
  ++cur; 
  int ans = 0;
  for(int i = n; i >= 1; --i) {
    ++cur;
    a[cur] = s[i];
    int height = getheight();
    int x = head;
    for(int r = H; r >= 0; --r) {
      while (nxt[r][x] && a[nxt[r][x]] < a[cur]) x = nxt[r][x];
      down(r, x);
    }
    int val = b[x] - a[x] + s[i] + t[i];
    b[cur] = val; 
    if (val > ans) ans = val;
    x = head;
    --a[x];
    for(int r = H; r >= 0; --r) {
      while (nxt[r][x] && a[nxt[r][x]] < a[cur]) {
        ++lazy[r][x];
        x = nxt[r][x];
        --a[x];
      }
      down(r, x);
      while (nxt[r][x] && cmp(cur, nxt[r][x])) {
        down(r, nxt[r][x]);
        nxt[r][x] = nxt[r][nxt[r][x]];
      }
      if (height >= r) {
        nxt[r][cur] = nxt[r][x];
        nxt[r][x] = cur;
      }
    }
    --a[cur];
  }
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：AquaRio (赞：12)

**Description**

有 $n$ 头牛，排在 $−n+1,...,0$ 的位置上。从左往右就座，有走路的时间，有原地放东西的时间。牛不能越过另一头牛。求时间。

**Solution**

先看第 $n$ 只牛，他在 $t=0$ 的时候位于 $x=0$ 的位置，并且在时间 $t=S_n$ 时走到自己位置， $t=S_n + T_n$ 时坐下。而这就带给了第 $n-1$ 只牛一个限制：必须要等到时间为$t=S_n + T_n+1$时他才有办法走到 $S_n$。

所以当我们处理每只牛的时候，假设对这只牛的限制为 $(a_1，b_1),...,(a_r，b_r)$ ，其中 $(a,b)$ 代表至少要等到 $b$ 秒时才可以走到 $a$ 位置。

那么这只牛走到目的地的时间就会是：$\max\{b_i+(S - a_i)\}$ ，其中 $a_i$ 满足 $a_i <= S$ 。

也就是我们会需要查询在所有第一个坐标 $<= S$ 的限制中，$b - a$ 最大的数是多少。

$O(n^2)$ 的做法很好想，直接大力枚举。

我们仔细思考，发现，如果有两个限制 $(a,b)$ 和 $(c,d)$ ，满足 $c > a$ 且 $d-c < b-a$ ，那么 $(c,d)$ 这个限制就废掉了。

所以每次加入一个新的限制 $(a,b)$ 时要再把所有废掉的 $(c,d)$ 都去掉。

虽然看起来还是 $O(n^2)$ 的，但是我们可以发现可以用treap维护所有的限制。

打一个FHQ Treap，对每个限制都记录他的 $a$ 值和 $b-a$ 值，还有这棵子树中 $b-a$ 的最大值。询问的时候只要把 $a <= S_i$ 的那一部分切下来就好了，然后把右子树 $b-a$ 值小的子树切掉。最后再把更新完的子树合并起来即可。

代码请看[blog](http://39.105.95.125/index.php/archives/433/)


---

## 作者：Leasier (赞：4)

~~感觉现有题解都好抽象啊 /ng~~

------------

考虑按照初始位置即编号从大到小处理，显然只有编号大于当前的奶牛会对其产生限制。

考虑逐条画出 $n$ 条由斜率为 $1$ 和水平的线段组成的折线，其中第 $i$ 条表示奶牛 $i$ 在放好行李前的每个 $t$ 时刻所在位置。

考虑现在加入折线 $i$，则此前每条折线 $j$ 的限制即为：

- 设其终于 $(x, y)$，则奶牛 $i$ 在 $x + 1$ 时刻才能到达 $y$。

或者说，折线 $i$ 的纵坐标到达 $s_i$ 的时间被限制为：

- $s_i + (n - i)$。
- $\forall x \leq s_i$，$(s_i - y) + (x + 1)$。

于是 $i$ 的答案为上述两者的最大值加上 $t_i$。

当我们加入折线 $i$ 之后，考虑其被此前折线“卡住”的每个拐点 $(x, y)$，则一个新的限制为 $(x, y - 1)$。它显然强于原限制。

又注意到对于当前折线左上方的拐点，其此后始终不优于被上述拐点，于是我们每次把 $y \leq s_i$ 的限制的 $y$ 加 $1$，再加入折线 $i$ 的限制即可。

平衡树维护即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int ls;
	int rs;
	int add;
	int pos;
	int val;
	int max;
	int heap;
} Node;

int root = 0;
int s[200007], t[200007], tm[200007];
Node tree[200007];

inline void push_add(int x, int k){
	if (x == 0) return;
	tree[x].add += k;
	tree[x].pos -= k;
	tree[x].val += k;
	tree[x].max += k;
}

inline void pushdown(int x){
	if (tree[x].add != 0){
		push_add(tree[x].ls, tree[x].add);
		push_add(tree[x].rs, tree[x].add);
		tree[x].add = 0;
	}
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline void update(int x){
	tree[x].max = max(tree[tree[x].ls].max, max(tree[tree[x].rs].max, tree[x].val));
}

void split(int x, int &y, int &z, int k){
	if (x == 0){
		y = z = 0;
		return;
	}
	pushdown(x);
	if (tree[x].pos <= k){
		y = x;
		split(tree[x].rs, tree[x].rs, z, k);
	} else {
		z = x;
		split(tree[x].ls, y, tree[x].ls, k);
	}
	update(x);
}

int merge(int x, int y){
	if (x == 0) return y;
	if (y == 0) return x;
	pushdown(x);
	pushdown(y);
	if (tree[x].heap < tree[y].heap){
		tree[x].rs = merge(tree[x].rs, y);
		update(x);
		return x;
	}
	tree[y].ls = merge(x, tree[y].ls);
	update(y);
	return y;
}

int main(){
	int n, ans = 0;
	scanf("%d", &n);
	srand(time(NULL));
	for (register int i = 1; i <= n; i++){
		scanf("%d %d", &s[i], &t[i]);
	}
	for (register int i = n; i >= 1; i--){
		int x, y;
		split(root, x, y, s[i]);
		tm[i] = s[i] + t[i] + max(tree[x].max, n - i);
		push_add(x, 1);
		tree[i].pos = s[i];
		tree[i].val = tree[i].max = tm[i] - s[i] + 1;
		tree[i].heap = rand();
		root = merge(x, merge(i, y));
	}
	for (register int i = 1; i <= n; i++){
		ans = max(ans, tm[i]);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：MuelsyseU (赞：2)

一种更加朴素的方法。

首先我们此题实际上要做的，就是对每个数维护其到达目标 $s_i$ 的实际时间，设为 $s_i+tim$。

于是用小根堆维护 **已经到达的 $s_i$ 的奶牛 $i$** 的所有 $s_i+tim+t_i$，考虑堆顶这个点在 $t_i$ 时间内，实际上是堵住了序列上一个连续区间的所有其它点，使得它们对应的 $tim$ 加上了 $t_i$。

可以把每个数维护一个 $v_j=s_j - j$，然后考虑现在一个 $s_i=k$ 位置正在坐下，那么直到上一个 $j$ 满足 $v_j \le n - k$，其之后的部分就是这个区间。

然后再考虑那个 $j$，其已经到达目标，再求出其对应区间，并将其插入小根堆。

接下来，考虑从堆顶 `pop` 出 $i$，则这个区间可以继续往后走。我们可以把这区间里面的 $v_j$ 减去 $t_i$，然后把这个区间包含进入下一个在堆内的节点。

同时在这个区间内，继续计算是否有已经到达目标的点，并插入堆。

为了方便，多加上一个 $s_{n + 1} = n + 1, t_{n + 1} = \infty$。这样下一个点一定存在。

用线段树处理区间操作。

关于复杂度，可以用势能分析。故复杂度 $O(n\log n)$。

---

## 作者：bluewindde (赞：1)

zyf 学长去年讲了，三月份补了，今天 @[modfisher](https://www.luogu.com.cn/user/605226) 追忆过去翻出这道题，于是记录这种做法。

---

把奶牛的位置和时间画成 x-t 图，横轴为位置，纵轴为时间。样例的 x-t 图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5lzjdysp.png?x-oss-process=image/resize,m_lfit,h_400)

奶牛看作二维平面上的点，原题中向右移动变为平面上向右上方移动，等待变为向上方移动。奶牛在平面上的移动轨迹组成一条折线。

如下左图，如果一头奶牛移动后折线将与另一头奶牛的折线相交，称其将要“撞上”另一条折线。根据题意，一头奶牛坐到座位上前，它左边与它挨着的奶牛都不能动，所以折线永远不交。如果一头奶牛将要撞上另一头，那么这头奶牛必须等待至其坐下，对应折线需要向上移动，如下右图。

![](https://cdn.luogu.com.cn/upload/image_hosting/gqrdqieo.png?x-oss-process=image/resize,m_lfit,h_300)

明显折线在斜向移动时不会相撞，所以只需要维护竖直的部分。明显一头奶牛只会受到其后面的奶牛影响，倒序处理。

考虑添加一头奶牛，如果它撞到很多条竖线，只需要考虑最后一条的高度，因为其它竖线对 $y = x$ 作差的结果一定小于最后一条竖线，通过平移能够消除其它竖线的影响，如下图。（这张图存在一点缺陷，落座时产生的竖线不需要被平移，平移了也没错，请注意区分）

![](https://cdn.luogu.com.cn/upload/image_hosting/clj8alyp.png?x-oss-process=image/resize,m_lfit,h_400)

相撞后由于等待产生的新竖线恰在原竖线左边一个单位，且高度与被撞上的竖线相等，可以看作被撞上的竖线向左平移了一个单位，因为被撞上的竖线不会再被撞。

平面上本来没有竖线，落座的奶牛多了，也便有了竖线。只有落座时会添加竖线，其总数为 $n$。

设竖线的最高点为 $(x, y)$（最低点的位置没有影响），维护点 $(x, y - x)$ 以消除斜向移动的影响。如果当前奶牛的座位为 $x_0$，则 $x \leqslant x_0$ 的所有竖线中，$y - x$ 最大的竖线就是撞上的最后一条竖线。处理答案后把撞上的竖线向左平移一个单位。最后插入落座的竖线。

平衡树维护 $y - x$ 的前缀最大值容易处理上述操作。注意插入落座的竖线后要将其后面 $y - x$ 小于它的竖线删除，以维护前缀最大值性质。时间复杂度 $O(n \log n)$。

```cpp
#include <chrono>
#include <iostream>
#include <random>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int n;
struct {
    int a, b;
} a[200005];

int cnt;
struct fhq {
    int ls, rs, pri, x, y, val, tag;
} d[200005];
static inline void pushup(int p) {
    d[p].val = max(d[p].y, max(d[d[p].ls].val, d[d[p].rs].val));
}
static inline void pushtag(int p, int c) {
    if (!p)
        return;
    d[p].x -= c;
    d[p].y += c;
    d[p].val += c;
    d[p].tag += c;
}
static inline void pushdown(int p) {
    pushtag(d[p].ls, d[p].tag);
    pushtag(d[p].rs, d[p].tag);
    d[p].tag = 0;
}
static inline void split(int x, int p, int &u, int &v) {
    if (!p) {
        u = v = 0;
        return;
    }
    pushdown(p);
    if (d[p].x <= x)
        u = p, split(x, d[p].rs, d[p].rs, v);
    else
        v = p, split(x, d[p].ls, u, d[p].ls);
    pushup(p);
}
static inline void splity(int x, int p, int &u, int &v) {
    if (!p) {
        u = v = 0;
        return;
    }
    pushdown(p);
    if (d[p].y <= x)
        u = p, splity(x, d[p].rs, d[p].rs, v);
    else
        v = p, splity(x, d[p].ls, u, d[p].ls);
    pushup(p);
}
static inline int merge(int u, int v) {
    if (!u || !v)
        return u | v;
    if (d[u].pri > d[v].pri) {
        pushdown(u);
        d[u].rs = merge(d[u].rs, v);
        pushup(u);
        return u;
    } else {
        pushdown(v);
        d[v].ls = merge(u, d[v].ls);
        pushup(v);
        return v;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].a >> a[i].b;
    int rt = ++cnt, ans = 0;
    for (int i = n; i; --i) {
        int u, v;
        split(a[i].a, rt, u, v);
        int x = d[u].val + a[i].a + a[i].b;
        ans = max(ans, x);
        pushtag(u, 1);
        int w = x - a[i].a + 1, z;
        splity(w, v, z, v);
        d[++cnt].pri = rnd();
        d[cnt].x = a[i].a;
        d[cnt].y = w;
        rt = merge(u, merge(cnt, v));
    }
    cout << ans << endl;
    return 0;
}
```

---

