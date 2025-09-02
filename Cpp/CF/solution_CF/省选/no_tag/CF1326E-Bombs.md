# Bombs

## 题目描述

You are given a permutation, $ p_1, p_2, \ldots, p_n $ .

Imagine that some positions of the permutation contain bombs, such that there exists at least one position without a bomb.

For some fixed configuration of bombs, consider the following process. Initially, there is an empty set, $ A $ .

For each $ i $ from $ 1 $ to $ n $ :

- Add $ p_i $ to $ A $ .
- If the $ i $ -th position contains a bomb, remove the largest element in $ A $ .

After the process is completed, $ A $ will be non-empty. The cost of the configuration of bombs equals the largest element in $ A $ .

You are given another permutation, $ q_1, q_2, \ldots, q_n $ .

For each $ 1 \leq i \leq n $ , find the cost of a configuration of bombs such that there exists a bomb in positions $ q_1, q_2, \ldots, q_{i-1} $ .

For example, for $ i=1 $ , you need to find the cost of a configuration without bombs, and for $ i=n $ , you need to find the cost of a configuration with bombs in positions $ q_1, q_2, \ldots, q_{n-1} $ .

## 说明/提示

In the first test:

- If there are no bombs, $ A $ is equal to $ \{1, 2, 3\} $ at the end of the process, so the cost of the configuration is $ 3 $ .
- If there is one bomb in position $ 1 $ , $ A $ is equal to $ \{1, 2\} $ at the end of the process, so the cost of the configuration is $ 2 $ ;
- If there are two bombs in positions $ 1 $ and $ 2 $ , $ A $ is equal to $ \{1\} $ at the end of the process, so the cost of the configuration is $ 1 $ .

In the second test:

Let's consider the process for $ i = 4 $ . There are three bombs on positions $ q_1 = 5 $ , $ q_2 = 2 $ , and $ q_3 = 1 $ .

At the beginning, $ A = \{\} $ .

- Operation $ 1 $ : Add $ p_1 = 2 $ to $ A $ , so $ A $ is equal to $ \{2\} $ . There exists a bomb in position $ 1 $ , so we should delete the largest element from $ A $ . $ A $ is equal to $ \{\} $ .
- Operation $ 2 $ : Add $ p_2 = 3 $ to $ A $ , so $ A $ is equal to $ \{3\} $ . There exists a bomb in position $ 2 $ , so we should delete the largest element from $ A $ . $ A $ is equal to $ \{\} $ .
- Operation $ 3 $ : Add $ p_3 = 6 $ to $ A $ , so $ A $ is equal to $ \{6\} $ . There is no bomb in position $ 3 $ , so we do nothing.
- Operation $ 4 $ : Add $ p_4 = 1 $ to $ A $ , so $ A $ is equal to $ \{1, 6\} $ . There is no bomb in position $ 4 $ , so we do nothing.
- Operation $ 5 $ : Add $ p_5 = 5 $ to $ A $ , so $ A $ is equal to $ \{1, 5, 6\} $ . There exists a bomb in position $ 5 $ , so we delete the largest element from $ A $ . Now, $ A $ is equal to $ \{1, 5\} $ .
- Operation $ 6 $ : Add $ p_6 = 4 $ to $ A $ , so $ A $ is equal to $ \{1, 4, 5\} $ . There is no bomb in position $ 6 $ , so we do nothing.

In the end, we have $ A = \{1, 4, 5\} $ , so the cost of the configuration is equal to $ 5 $ .

## 样例 #1

### 输入

```
3
3 2 1
1 2 3```

### 输出

```
3 2 1```

## 样例 #2

### 输入

```
6
2 3 6 1 5 4
5 2 1 4 6 3```

### 输出

```
6 5 5 5 4 1```

# 题解

## 作者：Flandre_495 (赞：20)

前天晚上的爆肝赛，回来补锅。很多大佬到了这题都不屑于做下去了，所以又是一场掉分赛。

刚开始不太能看明白英文题解，感谢 z7z_Eta 提供的思路和解释。

~~题解反正也没人看，补个锅自己留着，怕忘了。。。~~

### 题意：

>给你一个长度为$n$的排列$a$，再来一个长度为$n$的排列$b$，$b$表示安放炸弹的顺序，$b_i$表示每次放炸弹的位置。每安放一个炸弹，它会询问你整个序列$a$的值。即把$a$排列的数依次放入集合中，若当前位置有炸弹，则去掉集合中的最大值，最终集合中最大值即为答案。

首先从样例也能看出来：**答案是单调不递增的**，这个很重要。也很好证：若当前答案被炸掉后，它就永远成为不了答案 ，它要么被新放的炸弹炸，要么被曾经炸它的炸弹炸，不可能起死回生。

那么答案什么时候会减。我们考虑当前答案$x$，如果我们希望$x$留着，就得保证 **存在一个 $i$**，使得$i$后面 “ $\geq x$ 的数 ” 比$i$后面的 “ 炸弹数 ” 要多。这样说明$i$后面的炸弹炸不完 “ $\geq x$ 的数 ”，$x$ 当然就可以留下了。（这里要注意，如果你想如果后面的炸弹先把 $x$ 炸了留下更大的数怎么办？这个就不需要考虑了，因为答案是单调的，既然你现在正在考虑答案是否为 $x$，那么说明比 $x$ 大的那些数，之前肯定是被炸过的，翻不了身。）

显然如果不存在这么一个 $i$ 满足条件，说明**从任何位置开始**，$x$ 都避免不了被炸的悲剧，那么答案就要减了，这里得循环判断，因为答案可能减少不止一次。

所以我们要求是否**所有的位置**： “ $\geq x$ 的数 ” 小于等于 “ 炸弹数 ” ，若是，答案 $x$ 减 $1$。用线段树每一个位置表示当前位置后面 “ $\geq x$ 的数 ”减“ 炸弹数 ” ，维护全局最大值，若最大值小于等于$0$，满足条件，答案减。每改变一个 $x$，$x$ 位置前面值加一，每安放一个炸弹，炸弹位置前面值减一。

具体实现代码也很简单，这是道降智题。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define QWQ cout<<"QwQ"<<endl;
#define ll long long
#include <vector>
#include <queue>
#include <stack>
#include <map>
#define ls now<<1
#define rs now<<1|1
using namespace std;
const int N=301010;
const int qwq=1203030;
const int inf=0x3f3f3f3f;

int n;
int ans;
int a[N],wei[N];
int tree[qwq],tag[qwq];

inline int read() {
	int sum = 0, f = 1; char c = getchar();
	while(c<'0' || c>'9') { if(c=='-') f = -1; c = getchar(); }
	while(c>='0'&&c<='9') { sum = sum * 10 + c - '0'; c = getchar(); }
	return sum * f;
}

inline void pushdown(int now) {
	if(tag[now]==0) return ;
	tag[ls] += tag[now]; tag[rs] += tag[now];
	tree[ls] += tag[now]; tree[rs] += tag[now];
	tag[now] = 0;
}

void insert(int now,int l,int r,int x,int y,int g) {
	if(x<=l && r<=y) { tree[now] += g; tag[now] += g; return ; }
	pushdown(now);
	int mid = l+r >> 1;
	if(x<=mid) insert(ls, l, mid, x, y, g);
	if(y>mid)  insert(rs, mid+1, r, x, y, g);
	tree[now] = max(tree[ls],tree[rs]);
}

int main() {
	int x;
	n = read();
	for(int i=1;i<=n;i++) a[i] = read(), wei[ a[i] ] = i;
	ans = n; cout<<ans<<" ";
	insert(1, 1, n, 1, wei[n], 1);
	for(int i=1;i<n;i++) {
		x = read();
		insert(1, 1, n, 1, x, -1);
		while(tree[1]<=0) {
			ans--;
			insert(1, 1, n, 1, wei[ans], 1);
		}
		cout<<ans<<" ";
	}
	return 0;
}
```

但愿这不是我退役前的最后一篇题解。

---

## 作者：胖头鱼学员 (赞：8)

# [CF1326E](https://www.luogu.com.cn/problem/CF1326E)
## 题意
给定$n$的排列，每个数所在的位置最多有一个标记。

每次处理排列都从空集开始，依次将数加入集合，如果遇到位置上有标记则删掉集合中最大的数。

依次添加$n$个标记，求每次添加标记后，处理排列后剩下的最大数。

## 思路
### 校验答案
如果当前最大的$i$个数被删除了，那么在添加一个标记后，这$i$个数肯定还是会被删除，所以答案是不增的。

### 校验策略
令最大$i$个数的位置按顺序依次为$p_1$……$p_i$。

那么这个$i$数会被删除，等价于有$i$个标记的位置 $\geq p_1$、有$i -1$个标记的位置 $\geq p_i$ 、…… 、有1个标记的位置$\geq p_i$。

## 加速
站在每个位置$p$的角度来考虑，就是从$p$起靠右的标记数要不少于数的数量。
#### 每次增加标记或者数时，都有一段连续位置上的值会发生变化。所以可以使用线段树来进行加速。
### 代码如下 
```cpp
#include <iostream>

using namespace std;

const int kMaxN = 300001;

struct T {  // 线段树节点
  int v;    // 区间累加值
  int d;    // 区间最小值
} t[kMaxN * 4];
int p[kMaxN];
int n, x, a;

void Add(int i, int ml, int mr, int nl, int nr, int v) {  // 范围增加
  if (ml == nl && mr == nr) {                             // 区间匹配
    t[i].v += v;                                          // 增加累计值
    t[i].d += v;                                          // 增加最小值
    return;
  }
  int m = (ml + mr) >> 1;
  if (nl <= m) {  // 左半区间累加
    Add(i * 2, ml, m, nl, min(nr, m), v);
  }
  if (nr > m) {  // 右半区间累加
    Add(i * 2 + 1, m + 1, mr, max(nl, m + 1), nr, v);
  }
  t[i].d = min(t[i * 2].d, t[i * 2 + 1].d) + t[i].v;  // 更新区间最小值
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x;
    p[x] = i;  // 记录位置
  }
  a = n + 1;  // 初始化答案
  for (int i = 1; i <= n; i++) {
    while (t[1].d >= 0) {  // 检查答案范围最小值
      a--;
      Add(1, 1, n, 1, p[a], -1);  // 增加数的数量
    }
    cout << a << " ";
    cin >> x;
    Add(1, 1, n, 1, x, 1);  // 增加标记的数量
  }
  return 0;
}
```
## 复杂度分析
### 时间
数和标记分别增加$O(n)$次，每次添加$O(log_2 n)$，总共$O(n log2 n)$。

### 空间
记录数的位置$O(n)$。

线段树统计$O(n)$。

总空间复杂度为$O(n)$。 

---

## 作者：xht (赞：8)

首先有答案是递减的。

对于当前答案 $x$，我们如何判断它时候能被保留下来呢？

可以发现，$x$ 能留下当且仅当存在一个位置满足它右边 $\ge x$ 的数大于它右边的炸弹数。

于是线段树维护全局 $\max$ 和区间修改即可，时间复杂度 $\mathcal O(n \log n)$。

```cpp
const int N = 3e5 + 7;
int n, a[N], b[N], p[N], ans;
struct T {
	int l, r, x, z;
} t[N<<2];

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) return;
	build(ls, l, md), build(rs, md + 1, r);
	t[p].x = max(t[ls].x, t[rs].x);
}

void spd(int p) {
	if (t[p].z) {
		t[ls].x += t[p].z;
		t[ls].z += t[p].z;
		t[rs].x += t[p].z;
		t[rs].z += t[p].z;
		t[p].z = 0;
	}
}

void add(int p, int l, int r, int k) {
	if (t[p].l >= l && t[p].r <= r) return t[p].x += k, t[p].z += k, void();
	spd(p);
	if (l <= md) add(ls, l, r, k);
	if (r > md) add(rs, l, r, k);
	t[p].x = max(t[ls].x, t[rs].x);
}

int main() {
	rd(n);
	for (int i = 1; i <= n; i++) rd(a[i]), p[a[i]] = i; 
	for (int i = 1; i <= n; i++) rd(b[i]);
	build(1, 1, n), ans = n, print(n, ' ');
	add(1, 1, p[n], 1);
	for (int i = 1; i < n; i++) {
		add(1, 1, b[i], -1);
		while (t[1].x <= 0) add(1, 1, p[--ans], 1);
		print(ans, ' ');
	}
	return 0;
}
```

---

## 作者：zac2010 (赞：6)

~~为什么有那么多人喜欢把套路题叫成思维题，真是神奇。~~

在不知道套路的情况下，套路题便是思维题；如果能熟练运用套路，思维题便成了套路题罢。

这道题的套路是两种经典套路相乘。
1. 对于一类二分题，我们可以在二分后把满足条件的设为 $1$ ，不满足的设为 $0$ 或 $-1$ （视情况而定），这时我们能很方便与统计/做前后缀和。
2. 对于一类动态的前后缀和问题（或者上述问题），很多时候可以用线段树维护动态的。

我太菜了，第一种套路都没想到。

所以到底该怎么做呢？我们先从简单入手罢。假设我们已经确定了哪些位置有炸弹，那么可以套用第一种套路。就是去二分答案 $x$ ，这时候我们发现我们把大于 $x$ 的全部标为 $1$ ，表示可以删掉，不难发现，由于 $x$ 只要剩 $1$ 个，而且相同的权值把越前面置 $1$ 必定更优（那么后面就越可能有东西能删），那么我们把除最后一个外权值等于 $x$ 的也置 $1$ ，然后判断是否有前缀和小于等于 $0$ 即可。

由于这种做法非常的逊，所以我们考虑优化他（对每个数做一遍的时间复杂度为 $O(n^2 \log n)$ ）。所以我们考虑优化掉一个 $n$ 的级别。这时也许还是被二分限制着，但是只要阅读了套路二，你将会豁然开朗。

由于有单调性所以能二分，而我们发现答案是单调递减的，所以呢我们发现在这样的性质下一个答案是合法的仅当有一个点右边的大于等于 $ans$ 的数大于炸弹数，这样必定会剩下至少一个没有被删，而因为答案是单调递减的所以答案一定是当前的。我们记录每种数值的位置（注意数值是 $1$ 到 $n$ 的全排列），每次，把 $1$ 到 $q[i-1]$ 的位置置位减 $1$ ，然后把答案减小时对 $1$ 到答案在 $p$ 中的位置加 $1$ ，这样可以算出后缀和。

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 300010;
struct Tree{
	int l, r, mid, mx, lazy;
	void Tag(int v){mx += v, lazy += v;}
}t[N << 2];
int n, id[N], p[N], q[N];
void Pushup(int p){
	t[p].mx = max(t[p << 1].mx, t[p << 1 | 1].mx);
}
void Pushdown(int p){
	t[p << 1].Tag(t[p].lazy);
	t[p << 1 | 1].Tag(t[p].lazy);
	t[p].lazy = 0;
}
void Build(int p, int l, int r){
	t[p] = {l, r, l + r >> 1, 0, 0};
	if(l == r) return;
	Build(p << 1, t[p].l, t[p].mid);
	Build(p << 1 | 1, t[p].mid + 1, t[p].r);
	Pushup(p);
}
void Update(int p, int l, int r, int v){
	if(l <= t[p].l && t[p].r <= r){
		t[p].Tag(v);
		return;
	}
	Pushdown(p);
	if(l <= t[p].mid) Update(p << 1, l, r, v);
	if(t[p].mid < r) Update(p << 1 | 1, l, r, v);
	Pushup(p);
}
int main(){
	scanf("%d", &n);
	L(i, 1, n) scanf("%d", &p[i]), id[p[i]] = i;
	L(i, 1, n) scanf("%d", &q[i]);
	Build(1, 1, n);
	int x = n;
	L(i, 1, n){
		if(i > 1) Update(1, 1, q[i - 1], -1);
		while(t[1].mx <= 0) Update(1, 1, id[x--], 1);
		printf("%d ", x + 1);
	}
	return 0;
}
```


---

## 作者：chenxia25 (赞：4)

思维题杀我！现场$^*2600$的状压DP都会做，$^*2400$的思维题就不会了，看来是wtcl/ll

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF1326E) & [CodeForces题目页面传送门](https://codeforces.com/contest/1326/problem/E)

>给定$2$个$1\sim n$的排列$a,b$。$a$上某些位置会存在炸弹。对于某些位置有炸弹的$a$，维护一个集合，初始为空，从左往右扫描整个排列$a$，每到一个位置上就将此位置上的数压进集合，若此位置有炸弹就把集合中最大的数弹出，我们称最终集合中最大的元素为$a$的结果。$\forall i\in[0,n)$，求若在$\forall j\in[1,i],b_i$这些位置放下炸弹，结果是多少。

>$n\in\left[1,3\times10^5\right]$。

显然，依次算每个结果的话，第$i$次被弹出的集合是第$i+1$次被弹出的集合的子集，即今朝被弹出，永远就不会复活了。可以推出这$n$个结果非严格单调递减。于是我们可以two-pointers，维护目前最大的没有被弹出的数$now$，初始时$now=n$，每次算答案时不停地令$now=now-1$直到$now$没有被弹出。难点在于如何快速判断$now$是否被弹出。

如果真就一直在想$now$被弹出的充要条件，恭喜你，你被魔法杀死了。不难发现一个性质：无论何时，只要你正在考虑判断$now$是否被弹出，那么一定所有$>now$的数已经确认被弹出了（因为如果不是那样，$now$自减的过程就会在某个$>now$的数处停下）。于是**我们所考虑的**$now$被弹出，其实等价于所有$\geq now$的数都被弹出。这个东西的充要条件看上去容易探索一点（然鹅的确是这样）。

下面我们来探索所有$\geq now$的数都被弹出的充要条件。考虑每个$\geq now$的数$a_x$，显然对于每个在$a_x$右边且$\geq now$的数$a_y$（包括$a_x$自己），弹出它们的炸弹在$a_y$右边（包括$a_y$位置上），结合$a_y$在$a_x$右边可以得到弹出它们的炸弹一定在$a_x$右边（包括$a_x$位置上）。于是我们得到了所有在$a_x$右边且$\geq now$的数（包括$a_x$自己）都被弹出的一个很弱的必要条件：$a_x$右边的炸弹（包括$a_x$位置上）数量不低于在$a_x$右边且$\geq now$的数（包括$a_x$自己）的数量。充分性显然不满足。

不过，如果将$\forall x(a_x\geq now)$，所有在$a_x$右边且$\geq now$的数（包括$a_x$自己）都被弹出的这么多必要条件合并起来，得到所有$\geq now$的数都被弹出的一个必要条件：$\forall x(a_x\geq now)$，$a_x$右边的炸弹（包括$a_x$位置上的）数量不低于在$a_x$右边且$\geq now$的数（包括$a_x$自己）的数量。你会发现这个条件似乎很强，于是我们试图证明它的充分性。然后真就证出来了！

充分性证明（感性）：找到$a_x=n$，显然，$a_x$右边（包括$a_x$位置上）的最左边的炸弹与$a_x$匹配，于是我们可以想象将这个炸弹扔掉，并将$a_x$扔出排列，两边挨紧形成一个新的$1\sim n-1$的排列。$a_x$左边所有$\geq now$的数右边$\geq now$的数（包括自己）数量$-1$，右边的炸弹（包括自己位置上）数量$-1$；$a_x$右边、炸掉$a_x$的炸弹左边（包括炸弹位置上）所有$\geq now$的数，右边$\geq now$的数（包括自己）的数量不变，由于$a_x$与炸弹之间没有炸弹，所以它们右边的炸弹（包括自己位置上）数量至少剩$a_x$原来右边炸弹（包括自己位置上）的数量$-1$；炸弹右边所有$\geq now$的数右边$\geq now$的数（包括自己）的数量、炸弹（包括自己位置上）数量都没变。由此看来条件依然满足。于是原证明题可以转化为一个规模$-1$的证明题，可以用数学归纳法加以证明。

有了这个结论，接下来就好办了。设$a_i$右边$\geq now$的数（包括$a_i$自己）有$grt_i$个，右边的炸弹（包括$a_i$位置上）有$bmb_i$个。那么$\forall x(a_x\geq now)$，$a_x$右边的炸弹（包括$a_x$位置上的）数量不低于在$a_x$右边且$\geq now$的数（包括$a_x$自己）的数量，可以写成$\forall x(a_x\geq now),bmb_x\geq grt_x$，即$\forall x(a_x\geq now),bmb_x-grt_x\geq0$。于是我们需要维护$\forall i\in[1,n],bmb_i-grt_i$。判断$now$是否被弹出时只需判断全局最小值是否$\geq0$，每当$now=now-1$时（初始$now=n$时也要）就将位置$a^{-1}_{now}$上的$bmb_{a^{-1}_{now}}-grt_{a^{-1}_{now}}$激活（即今后算进全局最小值，激活之前懒标记可以帮忙保存$bmb_{a^{-1}_{now}}-grt_{a^{-1}_{now}}$）并令$\forall i\in\left[1,a^{-1}_{now}\right],grt_i=grt_i+1$，每当新增一个炸弹$b_x$就令$\forall i\in[1,b_x],bmb_i=bmb_i+1$。这只需要单点修改、区间增加、全局查询最小值的线段树即可实现。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=300000;
int n;//排列长度 
int a[N+1]/*排列*/,b[N+1]/*炸弹添加顺序*/;
int pos[N+1];//pos[i]为数i在a中的位置 
struct segtree{//线段树 
	struct node{int l,r,mn_dif/*此节点表示的区间内bmb[i]-grt[i]的最小值*/,lz/*蓝标记*/;}nd[N<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define mn_dif(p) nd[p].mn_dif
	#define lz(p) nd[p].lz
	void bld(int l=1,int r=n,int p=1){//建树 
		l(p)=l;r(p)=r;mn_dif(p)=inf;/*一开始都是未激活状态*/lz(p)=0;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
	}
	void init(){bld();}//初始化 
	void sprup(int p){mn_dif(p)=min(mn_dif(p<<1),mn_dif(p<<1|1));}//上传节点信息 
	void sprdwn(int p){//下传懒标记 
		if(lz(p)){
			mn_dif(p<<1)+=lz(p);mn_dif(p<<1|1)+=lz(p);
			lz(p<<1)+=lz(p);lz(p<<1|1)+=lz(p);
			lz(p)=0;
		}
	}
	void on(int x,int p=1){//激活位置x 
		if(l(p)==r(p)){mn_dif(p)=lz(p)/*之前的bmb[l(p)]-grt[l(p)]保存在lz(p)里*/;return;}
		sprdwn(p);
		int mid=l(p)+r(p)>>1;
		on(x,p<<1|(x>mid));
		sprup(p);
	}
	void add(int l,int r,int v,int p=1){//区间增加 
		if(l<=l(p)&&r>=r(p)){mn_dif(p)+=v;lz(p)+=v;return;}
		sprdwn(p);
		int mid=l(p)+r(p)>>1;
		if(l<=mid)add(l,r,v,p<<1);
		if(r>mid)add(l,r,v,p<<1|1);
		sprup(p);
	}
	int _mn_dif(){return mn_dif(1);}//全局最小值 
}segt;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],pos[a[i]]=i;
	for(int i=1;i<=n;i++)cin>>b[i];
	int now=n;//初始now=n 
	cout<<now<<" ";//不放炸弹时 
	segt.init();
	segt.on(pos[n]);
	segt.add(1,pos[n],-1);//增加一个>=now的数 
	for(int i=1;i<n;i++){
		segt.add(1,b[i],1);//增加一个炸弹 
		while(segt._mn_dif()>=0/*now被弹出*/){
			now--;
			segt.on(pos[now]);
			segt.add(1,pos[now],-1);//增加一个>=now的数 
		}
		cout<<now<<" ";
	}
	return 0;
}
```

---

## 作者：灵梦 (赞：3)

观察到答案是随炸弹数增加而减小的。我们可以考虑依次加入炸弹，对于一组固定的炸弹设置再从大到小加入每个数。如果当前的这些数可以被炸弹全部弹掉，那么说明我们需要继续加数。于是我们现在的问题就是快速判断当前的数是否能被全部弹掉。

假设当前已经加入的数是 $[x,n]$，那么我们可以认为炸弹弹了小于 $x$ 的数就相当于没有匹配，这不会产生影响。考虑建立二分图，把这些数视为左部点，当前的炸弹视为右部点，每个数可以向它后面（下标不小于它）的所有炸弹匹配。可以发现 $[x,n]$ 被全部弹掉的充要条件就是这张图有完美匹配。应用 Hall 定理，因为匹配边是单向的，我们只用检测每个后缀的左部点数 $\leq$ 匹配到的右部点数即可。也就是说，我们要对每个位置 $i$ 检测 $[i,n]$ 的数的个数 减去炸弹个数小于等于 $0$。用线段树维护，加入一个数或炸弹相当于区间加 $1$ 或 $-1$，判断时需要询问全局最小值。复杂度 $O(n\log n)$。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=330000;
const int INF=1E9;
struct SegmentTree
{
	struct Node
	{
		int val, add;
	} tr[4*MAXN];
	#define lc (o<<1)
	#define rc (o<<1|1)
	void pushup(int o)
	{
		tr[o].val=max(tr[lc].val, tr[rc].val);
	}
	int plus(int o, int k)
	{
		tr[o].val+=k, tr[o].add+=k;
	}
	void pushdown(int o)
	{
		if (tr[o].add)
		{
			plus(lc, tr[o].add);
			plus(rc, tr[o].add);
			tr[o].add=0;
		}
	}
	void update(int o, int l, int r, int ul, int ur, int k)
	{
		if (l>ur||r<ul) return;
		if (ul<=l&&r<=ur) { plus(o, k); return; }
		pushdown(o); int mid=l+r>>1;
		update(lc, l, mid, ul, ur, k);
		update(rc, mid+1, r, ul, ur, k);
		pushup(o);
	}
	#undef lc
	#undef rc
} sgt;
int p[MAXN];
int main()
{
//	freopen("E.in", "r", stdin);
//	freopen("E.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i=1; i<=n; i++)
	{
		int x; scanf("%d", &x);
		p[x]=i;
	}
	sgt.update(1, 1, n, 1, p[n], 1);
	for (int i=1, j=n; i<=n; i++)
	{
		printf("%d ", j);
		int x; scanf("%d", &x);
		sgt.update(1, 1, n, 1, x, -1);
		while (j>=1&&sgt.tr[1].val<=0)
			sgt.update(1, 1, n, 1, p[--j], 1);
	}
	putchar('\n');
	return 0;
}
```



---

## 作者：George1123 (赞：3)

# 题解-Bombs

[$\color{#344622}{\texttt{Read it in my cnblogs}}$](https://www.cnblogs.com/Wendigo/p/12558365.html)

**前置知识：**

> 线段树

---
> [$\color{orange}{\texttt{Bombs on luogu}}$](https://www.luogu.com.cn/problem/CF1326E) / [$\color{orange}{\texttt{Bombs on CF}}$](http://codeforces.com/problemset/problem/1326/E)

> 有一个 $n$ 的排列 $p_i$。其中有一些 $i$ 被打了**标记**。对于 $i=1\to n$，将 $p_i$ 放入集合，如果 $i$ 被**标记**，就删除集合中的**最大数**。最后**剩下的集合的最大数**就是这种标记状态下**该序列的值**。给定另一个 $n$ 的排列 $q_j$，求对于 $j=1\to n$，将 $q_1\sim q_j$ 标记后对应的**序列值**。

> 数据范围：$1\le n\le 3\times 10^5$。

---
考虑当前序列值为 $p_i$，如果打上标记 $q_j$ 后的序列值变化。

1. 如果 $q_j<i$：序列值不改变。
2. 如果 $q_j\ge i$：序列值**变小**。

所以打上标记 $q_j$ 相当于**破坏 $1\sim q_j$ 的最大值**。

可以把打标记 $q_j$ 变化为令 $[1,q_j]$ 的 $w$ 区间值 $-1$。

而将当前序列值 $p_i$ 退让成 $p_k=p_i-1$ 则相当于**树立 $1\sim k$ 的最大值**。

可以把退让序列值变化为令 $[1,k]$ 的 $w$ 区间值 $+1$。

这样的话**如果有 $w_i>0$ 就说明当前序列值未被删除，否则就该退让最大值**。

---

因为要看是否满足有 $w_i>0$，所以可以**线段树维护 $w$ 区间最大值**。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define re register
#define il inline
#define inf 0x3f3f3f3f
typedef long long lng;

//&Data
#define N 300000
int n,p[N+10],q[N+10],I[N+10];

//&Segmenttree
struct smt{ //线段树
	int mx[N<<2|7],mk[N<<2|7];
	il void pushdown(re int k){
		if(mk[k]!=0) mx[k<<1]+=mk[k],mx[k<<1|1]+=mk[k],mk[k<<1]+=mk[k],mk[k<<1|1]+=mk[k],mk[k]=0;
	}
	il void add(re int x,re int y,re int z,re int k=1,re int l=1,re int r=n){
		if(x<=l&&r<=y){mx[k]+=z,mk[k]+=z;return;}
		int mid=(l+r)>>1; pushdown(k);
		if(mid>=x) add(x,y,z,k<<1,l,mid);if(mid<y) add(x,y,z,k<<1|1,mid+1,r);
		mx[k]=max(mx[k<<1],mx[k<<1|1]);
	}
}tree;

//&Main
int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;i++) scanf("%d",p+i),I[p[i]]=i; //记录pk对应的k，方便退让
	for(re int i=1;i<=n;i++) scanf("%d",q+i);
	re int res=n;
	tree.add(1,I[res],1),printf("%d%c",res,"\n "[1<n]);
	for(re int i=1;i<n;i++){
		tree.add(1,q[i],-1); //打标记-删除
		while(tree.mx[1]<=0) tree.add(1,I[--res],1);//退让知道未被删除
		printf("%d%c",res,"\n "[i<n-1]); //未被删除的序列值
	}
	return 0;
}
```
---

**祝大家学习愉快！**


---

## 作者：fade_away (赞：1)

# CF1326E Bombs

## Solution
提供一种比较麻烦的做法。

由于猪头不太好使，只想出了一个无脑的判断 $x$ 是否存留的方法：
1. 对于一个全 $0$ 的数组 $a$ ，我们先把标记的位置的 $a$ 加上 $-1$ ，然后对于 $p_i$ 大于等于 $x$ 的 $i$ 的 $a_i$ 加 $1$ 。
2. 对于 $\{a\}$ 求一个“类前缀和”（如果当前小于 $0$ 就设为 $0$ 的那种），记作 $\{s\}$。
3. 令 $x$ 在 $p$ 中的出现位置为 $pos$ ，这样如果 $x$ 不会被删掉当且仅当 $s_i<1$ 的 $i$ 都比 $pos$ 小。

这是一个 $O(n)$ 的暴力判断方法。

考虑如何优化，我们发现上面的过程相当于是求出 $1...pos-1$ 的“类前缀和”，再求出 $pos...n$ 的前缀和的最小值，两者相加大于等于 $1$ 就说明 $x$ 可行。

因此我们可以用线段树维护区间和、“类前缀和”、“前缀和最小值”，这三个都是常见的线段树可以维护的东西。

最后考虑一下怎么求哪个 $x$ 最优，显然答案是递减的，我们可以双指针来维护，修改相当于某一个 $a_i$ 加一或减一，~~因此这个做法甚至不需要 lazy_tag ！~~

总时间复杂度为 $O(n\log n)$。

## Code
```cpp
struct Node{
	int sum, mn, Sum;
	Node(){}
	Node(int x, int y, int z):sum(x), mn(y), Sum(z){};
	friend Node operator + (const Node &a, const Node &b) {
		int t = (a.Sum >= -b.mn ? a.Sum + b.sum : b.Sum); 
		return Node(a.sum + b.sum, min(a.mn, a.sum + b.mn), t);
	}
} s[MAXN << 2];
void update(int x, int l, int r, int y, int z) {
	if (l == r) { s[x].sum += z, s[x].mn += z, s[x].Sum = max(s[x].sum, 0); return; }
	int mid = (l + r) >> 1;
	if (y <= mid) update(x << 1, l, mid, y, z);
	else update(x << 1 | 1, mid + 1, r, y, z);
	s[x] = s[x << 1] + s[x << 1 | 1];
}
Node query(int x, int l, int r, int L, int R) {
	if (l >= L && r <= R) return s[x];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(x << 1, l, mid, L, R);
	else if (L > mid) return query(x << 1 | 1, mid + 1, r, L, R);
	else return query(x << 1, l, mid, L, mid) + query(x << 1 | 1, mid + 1, r, mid + 1, R);
}


int Q[MAXN], pos[MAXN];
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n;
	read(n);
	for (int i = 1, x; i <= n ; ++ i) read(x), pos[x] = i;
	for (int i = 1; i <= n ; ++ i) read(Q[i]);

	update(1, 1, n, pos[n], 1);
	for (int i = 1, nw = n; i <= n ; ++ i) {
		print(nw), putc(' ');
		update(1, 1, n, Q[i], -1);
		while (nw > 1 && (pos[nw] == 1 ? 0 : query(1, 1, n, 1, pos[nw] - 1).Sum) + query(1, 1, n, pos[nw], n).mn < 1) update(1, 1, n, pos[-- nw], 1);
	}
	return 0;
}
```


---

## 作者：momo5440 (赞：1)

由于本人太菜了所以没太理解其他题解推出来的结论是怎么来的，所以就决定讲一讲我能理解的$dengyaotriangle$大佬的做法

首先我们需要了解一件事那就是答案肯定是递减的，由于递减性我们就可以维护一个指针代表当前答案，每加进一个答案就不断往下减，直到它合法为止，那么问题就变为**如何迅速的判断一个答案他是不是合法的**

先做一些定义，我们令$x$ 表示当前的答案，$pos$表示他在$p$中是第几个

只要一个答案合法，那么就一定是比它大的元素帮他把炸弹全挡掉了，由于答案是不断往下减的，所以可以理解为我们是在不断的加元素

现在我们把序列分为两部分分别考虑与维护

$Case 1:i\in[1,pos-1]$

这时候这里面的炸弹不管怎么样都不会把$x$给弹掉，所以我们只要考虑这个区间里有多少数能剩下来帮$x$挡刀，这个东西类似一个前缀和$a[i]=max(0,a[i-1]+(p[i]>x)-(i$有炸弹$)),i\in[1,pos-1]$，(可以理解为在这个里面若$a[i]<0$时则必定会有$<x$的数被弹掉了所以就不用管了)，我们可以根据这个式子递推， 那么前面留给后面的福祉就是$a[pos-1]$

这东西咋维护后面再说

$Case 2:i\in[pos,n]$

现在炸弹可能会把$x$弹掉了，我们现在直接维护当前比$x$大的元素的个数
$b[i]=b[i-1]+(p[i]>x)-(i$有炸弹$),i\in[pos,n]$ 其中$b[pos-1]=a[pos-1]$现在只要有一个$b[i]<0$我们就直接$gg$，因为$x$肯定被弹掉了

考虑咋维护$b-a[pos-1]$（先不管$a[pos-1]$后面直接加就行了），我们可以拿一个线段树记录$b$从$1$开始递推的结果，每次改对应后缀加减，但是我们在这里只是从$pos$递推，可是由于我们算的这个值是满足直接加减的，所以后面实际的$b$值就是线段树里的$b[i]-b[pos-1]$，这样就可以算出来$b[i]-a[pos-1]$的值了，由于只用考虑最小，所以需要记录最小值

现在考虑维护$a$，这也是一个前缀的东西，同时修改也是对应一个后缀，我们考虑开**另一颗**线段树维护，但是发现取$max$咋办呢，由于发生取$max$的情况只会在减操作，也就是在插入一个炸弹的时候出现，先假定我们直接把后缀$-1$，那现在就有可能出现负数了，同时他最小是$-1$，我们可以让线段树多维护一个值，这样我们就可以知道$-1$最早出现在何处，我们设这个位置为$tp$，那我们现在可以把$[tp,n]$里面所有数$+1$，这样他们就全非负了，但是同时我们也**欠下一笔债**，这是因为假如后面有一个加的操作先于$tp$，我们就相当于白取了$max$，也就是多加了，对于这种情况，我们可以开一个$set$记录所有$tp$的值，在以后做加的操作时把$[tp,n]$减一

所以形式化的把步骤写出来就是

1，插入炸弹，在两颗线段树上都做修改，假如有$-1$就欠下债，以后还

2，不断的把答案减小并插入，直到满足，插入是在两个线段树上后缀加，加入发现前面欠债了，就还债，还的债是$set$里$pos$的$lower$_$bound$

3，输出答案

下面便是代码了

在我的代码里，$id=0$是$a$，$id=1$是$b$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <set>
using namespace std;
const int maxn=3e5+5;
typedef long long ll;
pair<int,int> t1[maxn*4][2];
int tag[maxn*4][2];
pair<int,int> merged(pair<int,int> a1,pair<int,int> b1){
	if (a1.first<b1.first) return a1;
	if (a1.first>b1.first) return b1;
	return make_pair(a1.first,min(a1.second,b1.second));
}
inline int lc(int u){
	return u<<1;
}
inline int rc(int u){
	return u<<1|1;
}
inline void co(int u,int id){
	t1[u][id]=merged(t1[lc(u)][id],t1[rc(u)][id]);
}
inline void pushdown(int u,int id){
	if (tag[u][id]==0) return;
	tag[lc(u)][id]+=tag[u][id];
	tag[rc(u)][id]+=tag[u][id];
	t1[lc(u)][id].first+=tag[u][id];
	t1[rc(u)][id].first+=tag[u][id];
	tag[u][id]=0;
}
inline void add(int u,int l,int r,int ql,int qr,int d,int id){
	if (d==0) return;
	if (ql<=l&&r<=qr){
		t1[u][id].first+=d;
		tag[u][id]+=d;
		return;
	}
	pushdown(u,id);
	int mid=(l+r)/2;
	if (ql<=mid) add(lc(u),l,mid,ql,qr,d,id);
	if (mid+1<=qr) add(rc(u),mid+1,r,ql,qr,d,id);
	co(u,id);
	return;
}
inline pair<int,int> qmin(int u,int l,int r,int ql,int qr,int id){
	if (ql<=l&&r<=qr) return t1[u][id];
	int mid=(l+r)/2;
	pushdown(u,id);
	if (ql<=mid&&mid+1<=qr){
		return merged(qmin(lc(u),l,mid,ql,qr,id),qmin(rc(u),mid+1,r,ql,qr,id));
	}
	if (ql<=mid) return qmin(lc(u),l,mid,ql,qr,id);
	if (mid+1<=qr) return qmin(rc(u),mid+1,r,ql,qr,id);
}
inline void build(int u,int l,int r,int id){
	if (l==r){
		t1[u][id]=make_pair(0,l);
		return;
	}
	int mid=(l+r)/2;
	build(lc(u),l,mid,id);
	build(rc(u),mid+1,r,id);
	co(u,id);
}
int pos[maxn];
int a[maxn],p[maxn];
int n;
inline bool chk(int x){
	int tp=pos[x];
	int mem=0;
	if (tp!=1){
		mem=qmin(1,1,n,tp-1,tp-1,0).first;
	}
	int fw=0;
	if (tp!=1){
		fw=qmin(1,1,n,tp-1,tp-1,1).first;
	}
	if (qmin(1,1,n,tp,n,1).first+mem-fw>=0) return true;
	else return false;
}
multiset<int> mem;
multiset<int>::iterator it;
// 0 mdf 1 real 
int main(){
	cin>>n;
	build(1,1,n,0);
	build(1,1,n,1);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pos[a[i]]=i;
	}
	for (int i=1;i<=n;i++){
		scanf("%d",&p[i]);
	}
	int res=n;
	for (int i=1;i<=n;i++){
		if (i==1){
			printf("%d ",res);
			continue;
		}
		else{
			add(1,1,n,p[i-1],n,-1,1);
			add(1,1,n,p[i-1],n,-1,0);
			pair<int,int> tp=qmin(1,1,n,p[i-1],n,0);
			if (tp.first<0){
				add(1,1,n,tp.second,n,1,0);
				mem.insert(tp.second);
			}
		}
		while(chk(res)==false){
			add(1,1,n,pos[res],n,1,1);
			add(1,1,n,pos[res],n,1,0);
			it=mem.lower_bound(pos[res]);
			if (it!=mem.end()){
				int x=(*it);
				add(1,1,n,x,n,-1,0);
				mem.erase(it);
			}
			res--;
		}
		printf("%d ",res);
	}
}
```

%%%dengyaotriangle

---

## 作者：Fracture_Dream (赞：0)

# 题意简述
给定两个长度为 $n$ 的排列 $a ,b$，对于一个初始为空的集合进行以下操作：对于每个 $i$，将 $a_i$ 加入集合，若 $vis_i=1$，将此时集合中的最大值删除。
现对于每一个 $i$，求出 $\forall j \in [1 , i - 1]，vis_j=1$ 的情况下，进行一次操作后集合中的最大值。

- $1 \le n \le 3 \times 10^5$
# 思路
不妨令 $ans_i$ 为 $i$ 的答案，由于只有删除操作，显然有 $ans_{i+1} \le ans_i$。
可以很自然的想到，我们可以 $O(n)$ 从 $n$ 往 $1$ 扫一遍，对于每一个 $i$ 判断当前枚举到的 $x$ 合不合法，如果不合法就 $x \leftarrow x-1$，继续判断即可。

所以现在的瓶颈便在于：该如何快速判断当前枚举到的 $x$ 合不合法呢？
- Hint1：$x$ 合法意味着什么？
- Hint2：一个数 $y$ 已被删除的条件是什么？
- Hint3：需要删除的数和标记点有什么联系？

不妨从以上 $\text{tips}$ 入手。如果 $x$ 合法，那么 $x$ 一定未被删除，且 $\forall y \in [x + 1 , n]$ 都已被删除。$y$ 被删除的充要条件是 $y$ 所处的位置后面有一个标记点可以用来删除 $y$。想到这，便不难发现其实判断的本质就是在寻找标记点与待删除点的 **配对关系**，类似于一个 **括号序列**。

不妨将一个待删除点 $y \in [x + 1 , n]$ 视作左括号，将一个标记点视作右括号，那么原问题便转化为括号序列中，每一个 **左括号是否都有与之对应的右括号** 的匹配问题。

注意在此题中，一个位置上既可以有左括号，也可以有右括号（一个点既可以待删除，也可以被标记。）且此题中括号匹配存在优先级的概念，即 $y \in [x+1,n]$ 会比 $x$ 优先匹配右括号。通俗地讲，如果想给当前 $x$ 分配右括号，那么必须先匹配完比他大的数才可以。

想想普通的括号匹配问题，如果对于任意位置 $i$，$[1 , i]$ 中左括号的数量大于等于 $[1,i]$ 中右括号的数量，且 $[1,n]$ 中左括号与右括号序列数量相等才能匹配。对于这道题，我们不要求匹配，只需要左括号配对完即可，右括号过剩也是被允许的。因此，如果对于任意 $i$，$[i,n]$ 中左括号的数量都小于等于 $[i,n]$ 中右括号的数量，那么便说明 $[i,n]$ 中的右括号不仅可以把 $[i+1,n]$ 中的左括号匹配完，且可以匹配到当前 $i$ 位置上的左括号。

所以，$x$ **不合法**（即被删除） 的充要条件为：对于任意 $i$，$[i,n]$ 中左括号的数量小于 $[i,n]$ 中右括号的数量。也就等价于 $[i,n]$ 中左括号的数量减去 $[i,n]$ 中右括号的数量小于等于 $0$。所以，我们将左括号视为 $1$，右括号视为 $-1$，用线段树维护这个差值即可，添加括号就修改后缀，最后判断全局最大值 $Max$ 是否 $\le0$ 即可。

# 代码
代码也很简洁易懂。

```cpp
#include<bits/stdc++.h>
#define int long long
const int MAXN = 3e5 + 5;
using namespace std;
int n , a[MAXN] , b[MAXN] , id[MAXN];
namespace Segment{
    struct tree{
        int l , r , Max , val , add;
    }tree[MAXN << 3];
    void pushup(int p) {tree[p].Max = max(tree[p << 1].Max , tree[p << 1 | 1].Max);}
    void pushdown(int p) {
        if (tree[p].add) {
            tree[p << 1].Max += tree[p].add , tree[p << 1 | 1].Max += tree[p].add;
            tree[p << 1].add += tree[p].add , tree[p << 1 | 1].add += tree[p].add;
            tree[p].add = 0;
        }
    }
    void build(int p , int l , int r) {
        tree[p].l = l , tree[p].r = r;
        if (l == r) return;
        int mid = l + r >> 1;
        build(p << 1 , l , mid) , build(p << 1 | 1 , mid + 1 , r);
    }
    void update(int p , int l , int r , int v) {
        if (tree[p].l >= l && tree[p].r <= r) {
            tree[p].Max += v , tree[p].add += v;
            return;
        }
        pushdown(p);
        int mid = tree[p].l + tree[p].r >> 1;
        if (l <= mid) update(p << 1 , l , r , v);
        if (r > mid) update(p << 1 | 1 , l , r , v);
        pushup(p);
    }
}
using namespace Segment;
bool check(int x) {return (tree[1].Max <= 0);}
void remove(int x) {update(1 , 1 , id[x] , 1);}
void add(int x) {update(1 , 1 , x , -1);}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr) , cout.tie(nullptr);
    cin >> n;
    build(1 , 1 , n);
    for (int i = 1 ; i <= n ; i ++) cin >> a[i] , id[a[i]] = i;
    for (int i = 1 ; i <= n ; i ++) cin >> b[i];
    remove(n);
    for (int i = 1 , now = n ; i <= n ; i ++) {
        while(now >= 1) {
            if (check(now)) remove(-- now);
            else break;
        }
        cout << now << ' ';
        add(b[i]);
    }
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

一天一道水题题解，$\color{red} \rm IGM$ 远离我。

考虑如何判定数 $p$ 会不会被删掉？

不妨把 $\le p$ 的数看做 $0$，$> p$ 的数看做 $1$。

考虑在 $p$ 出现后的所有位置，每次删除优先删掉 $1$，如果 $1$ 不在了那么肯定就是把 $p$ 删掉了。

这个又如何判定？

考虑把删数变成 $-1$。在 $p$ 之前，我们认为前缀中库存的 $1$ 的个数 $pre_i$ 为 $pre_i = \max\{0,pre_i + v_i\}$（$v$ 是问题转化后的数组。）而记 $opre_i = \sum_{j=1}^i v_j$。则 $pre_u = opre_u - \min_{0 \le i \le u} opre_i$。设 $p$ 出现的位置为 $k$，则只要 $\exists i \ge k$ 使得 $pre_i < \min_{0 \le j \le k-1} pre_j$，$p$ 就一定会被删掉。只需要一个维护区间 $\min$ 的线段树即可。

注意到本题答案对于 $q$ 的下标有单调性，所以可以使用 $\rm two-pointer$ 状物解决。

代码很短：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10;
int n,p[MAXN],q[MAXN],rev[MAXN],tag[MAXN<<2],mn[MAXN<<2];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void push_down(int k,int l,int r) {
	return mn[lson]+=tag[k],mn[rson]+=tag[k],tag[lson]+=tag[k],tag[rson]+=tag[k],tag[k]=0,void();
	}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return tag[k]+=v,mn[k]+=v,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	return mn[k]=min(mn[lson],mn[rson]),void();	
}
int query(int k,int l,int r,int x,int y) {
	if(x>y) return 0x3f3f3f3f;
	if(x<=l&&r<=y) return mn[k];
	push_down(k,l,r);
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return min(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>p[i],rev[p[i]]=i;
	ffor(i,1,n) cin>>q[i];
	int tans=n;
	ffor(i,1,n) {
		while(query(1,1,n,rev[tans],n)-min(0,query(1,1,n,1,rev[tans]-1))<0) update(1,1,n,rev[tans],n,1),tans--;
		cout<<tans<<' ';
		update(1,1,n,q[i],n,-1);
	}
	return 0;
}
```

---

