# [IOI 2009] Archery

## 题目背景

IOI2009 D1T1

## 题目描述

一场箭术比赛正在举行。一条直线上排着 $N$ 个靶子，靶子从左到右依次标号为从 $1$ 到 $N$。有 $2N$ 个选手，在比赛的任何时刻，同一个靶位上都有两个选手。比赛的每一轮按照如下规则进行：

- 在同一个靶位的两位选手比赛一场决出胜者，然后所有选手按照如下规则移动：

  - 在 $2$ 到 $N$ 号靶位上的胜者移动到他们的左侧的靶位（即分别移动到 $1\sim N - 1$ 号靶位）。
  - 在 $2$ 到 $N$ 号靶位上的负者，以及 $1$ 号靶位上的胜者，停留在同一个靶位。
  - $1$ 号靶位上的负者移动到 $N$ 号靶位。

比赛一共持续 $R$ 轮，轮数至少为参赛选手的数量，即 $R\geq 2N$。

你是唯一一个准时到达的选手。其它 $2N - 1$ 个选手已经提前到达并站成了一排，你现在要做的就是插入这个队伍。在你进入队伍后，队列中前两个选手（最左侧的两个选手）将对应一号靶位，接下来两个选手将对应二号靶位，以此类推，最右侧的两个选手对应 $N$ 号靶位。

所有 $2N$ 个选手（包括你）都用一个数值衡量技术水平，没有两个选手的技术水平相同。在同一个靶位上，数值较小的选手会成为胜者。

在了解了所有选手的技术水平之后，你需要找到一个位置插入使得你最终对应的靶位序号尽量小，在此前提下，你希望你初始时对应的靶位序号尽量大。

**任务**：编写一个程序，给定所有选手的技术水平（包括你自己）和你的对手们的排列顺序，计算出你的初始靶位编号，以满足你的上述目标。

## 说明/提示

### 样例解释

- 样例 1：你是排名倒数第二的选手。如果你从靶 $1$ 开始比赛，接下来你将移动到靶 $4$ 而且一直留在靶 $4$ 直到最后。如果你从靶 $2$ 或靶 $4$ 开始，你将会一直留到最后。如果你从靶 $3$ 开始，你将会击败最差的选手，然后移到靶 $2$ 并留在那里。

- 样例 2：你是排名第二的选手。排名第一的选手在靶 $1$ 并一直留在那里。因此，无论你从哪里出发，你永远会按 $4\to 3\to 2\to 1\to 4$ 的顺序循环移动。为了最终留在靶 $1$，你应该从靶 $2$ 开始。

### 数据范围与约定

- 对于 $20\%$ 的数据，$N\leq 200$。
- 对于 $60\%$ 的数据，$N\leq 5000$。
- 对于 $100\%$ 的数据，$1\leq N\leq 2\times 10 ^ 5$，$2N\leq R\leq 10 ^ 9$，$1\leq S_k\leq 2N$ 且 $S_k$ 互不相同。

另有三组 @[asmend](https://www.luogu.com.cn/user/21658) 提供的 hack 数据，不计分。

## 样例 #1

### 输入

```
4 8
7
4
2
6
5
8
1
3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 9
2
1
5
8
3
4
7
6
```

### 输出

```
2
```

# 题解

## 作者：Alex_Wei (赞：8)

> [P9112 [IOI2009] Archery](https://www.luogu.com.cn/problem/P9112)

通过样例提示或手玩几组小数据，我们发现有些选手一定的轮数后不再移动，而其它选手按从 $n$ 到 $1$ 的顺序环状移动。

- 考虑选手 $1$，他最终会在靶 $1$ 停下来。
- 考虑选手 $2n$，他最终会在某个非靶 $1$ 的位置停下来，因为他无法打败任何人，所以一旦进入某个非靶 $1$ 的位置，他就永远无法离开了。
- 考虑选手 $2n - 1$，他最终会在某个不是选手 $1$ 或选手 $2n$ 停下来的位置停下来，原因同理。

以此类推，可知不移动的选手为 $1$ 和 $n + 2\sim 2n$，而环状移动的选手为 $2\sim n + 1$。**我们将 $n$ 个靶位按编号排成圆圈**。 

我们探究什么时候所有选手会有规律地移动。一个直观猜测是，等选手 $1$ 进入靶位 $1$ 后，选手 $n + 2\sim 2n$ 会在不超过 $n$ 轮后停在靶位 $2\sim n$。因此，至多 $2n$ 轮后整个局面会以 $n$ 为循环节循环。

$2n$ 轮的上界已经够用了，而且很好证明。作为补充解释，我们尝试证明一个更强的结论：

> **$n + 2\sim 2n$ 会在不超过 $n$ 轮后停在靶位 $2\sim n$**。
>
> 证明：考虑某个靶位 $i$（$2\leq i\leq n$）且 $n$ 轮后没有 $n + 2\sim 2n$，那么 $i$ 从来没有被这样的选手经过，因为一旦经过就一直存在，无论留下的选手编号是什么。
>
> 在第一轮时，$i$ 左侧的靶位（靶位 $i - 1$）至多剩下一名 $n + 2\sim 2n$。
>
> 在第二轮时，$i$ 左侧的两个靶位总共至多剩下两名 $n + 2\sim 2n$。
>
> 特别地，在第 $i - 1$ 轮时，靶位 $1\sim i - 1$ 至多剩下 $i - 1$ 名 $n + 2\sim 2n$，且如果剩下 $i - 1$ 名，则靶位 $1$ 上至少有一名，此时我们再等一轮，第 $i$ 轮时，靶位 $1\sim i - 1$ 至多剩下 $i - 2$ 名 $n + 2\sim 2n$。
>
> 以此类推，可知第 $n$ 轮时，$i$ 左侧的 $n - 1$ 个靶位（也就是除了靶位 $i$ 本身的其它所有靶位）至多剩下 $n - 2$ 名 $n + 2\sim 2n$，但总共有 $n - 1$ 名 $n + 2\sim 2n$，这与靶位 $i$ 上没有 $n + 2\sim 2n$ 矛盾了。$\square$

这样，我们将 $R$ 替换为最小的 $R'\geq n$（或 $2n$）且 $R\equiv R'\pmod n$，答案不会改变。这给予我们 $\mathcal{O}(n ^ 3)$ 的模拟做法。

考虑优化单次 $\mathcal{O}(n ^ 2)$ 的模拟。我们观察到，若主角的技术水平为 $S_1$，则在模拟的过程中，所有 $> S_1$ 的选手是等价的，称为 $2$ 类选手；所有 $< S_1$ 的选手是等价的，称为 $0$ 类选手。并且，根据移动规则，类似上述证明，若有 $2$ 类选手进入靶位 $2\sim n$，则该靶位一直有 $2$ 类选手；若有 $1$ 类选手进入靶位 $1$，则该靶位一直有 $1$ 类选手。

因此，只要我们能够对于靶位 $2\sim n$ 求出第一次有 $2$ 类选手的时间 $t_2\sim t_n$，对于靶位 $1$ 求出第一次有 $1$ 类选手的时间 $t_1$，即可在任意时刻确定每个靶位上选手的类型，从而只维护主角的移动而不需要维护其它选手的移动。

$t_1$ 显然容易，考虑 $t_2\sim t_n$。设 $s_i$ 表示 $2$ 类选手数量关于靶位的前缀和。我们认为，如果两个 $2$ 类选手相遇，那么 **初始位置靠后的选手获胜**。这样，考虑最终移动到靶位 $i$ 上的选手初始靶位编号 $j$：

- 如果 $j$ 到 $i$ 不经过靶位 $1$，则 $j$ 移动到 $i$ 的充要条件是 $i\sim j$ 至少有 $j - i + 1$ 个 $2$ 类选手，即 $s_j - s_{i - 1} \geq j - (i - 1)$，且 **恰好在第 $j - i + 1$ 轮到达靶位 $i$，每一步都向前移动 $1$**。又因为每个靶位上至多有两个 $2$ 类选手，所以符合条件的最小的 $j$ 一定满足 $s_j - s_{i - 1} = j - (i - 1)$ 或 $j - (i - 1) + 1$。实际上，特判掉靶位 $i$ 本来就有 $2$ 类选手的情况之后，$s_j - s_{i - 1}$ 只能等于 $j - (i - 1)$。
- 如果 $j$ 到 $i$ 经过靶位 $1$，那么稍微复杂一些。首先，$j$ 移动到 $i$ 的充要条件是 $i\sim j$ 至少有 $j - i$ 个 $2$ 类选手，即 $s_j - s_{i - 1} \geq j - (i - 1) - 1$。类似地，除了靶位 $n$ 没有 $2$ 类选手，靶位 $1$ 有两个 $2$ 类选手的情况，$s_j - s_{i - 1}$ 只能等于 $j - (i - 1) - 1$。但是，$j$ 并不一定恰好在第 $j - i + 1$ 轮到达靶位 $i$：如果 $j$ 在到达靶位 $1$ 时，靶位 $1$ 有两个选手，那么 $j$ 会在这里停顿一下，使得 $j$ 在第 $j - i + 2$ 轮到达靶位 $i$。易知其充要条件为靶位 $1\sim j$ 初始全部有两个 $2$ 类选手。

求出 $t$ 之后，单次模拟的时间复杂度就可以做到 $\mathcal{O}(n)$。

因为超过一个 $2$ 类选手只能打败他，所以在靶位 $2\sim n$ 上，相较于靠前的起始位置，靠后的起始位置总要打败更多的 $2$ 类选手。而在靶位 $1$ 上，两个不同的起始位置可能等到相同的轮数才回到 $n$，但靠后的起始位置一定不会在靠前起始位置之前（更少的轮数）回到 $n$。因此，如果我们在线性的尺度下观察整个过程，设 $f_i$ 表示初始位置 $i$ 在线性尺度下的最终位置，即 $i$ 减去主角从 $i$ 出发经过 $R$ 轮的移动次数，那么对于 $i < j$，$f_i\leq f_j$。

因为 $R = \mathcal{O}(n)$，所以 $f_n - f_1 = \mathcal{O}(n)$。我们枚举 $[f_1, f_n)$ 的所有 $n$ 的倍数 $kn$，总共 $\mathcal{O}(1)$ 个，二分求出第一个 $i$ 使得 $f_i > kn$，则初始位置 $i$ 以及对应的最终位置才有可能更新答案。时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool Mbe;
constexpr int N = 4e5 + 5;
int n, R, a[N], b[N];
pair<int, int> ans = {N, 0};
auto simulate(int p) {
  for(int i = 1; i < 2 * p; i++) a[i] = b[i + 1];
  a[2 * p] = b[1];
  for(int i = 2 * p + 1; i <= 2 * n; i++) a[i] = b[i];
  static int t[N], s[N], buc[N << 1];
  memset(s, 0, N << 2), memset(buc, 0x3f, N << 3);
  for(int i = 1; i <= 2 * n; i++) if(a[i] == 2) s[i + 1 >> 1]++;
  for(int i = 1; i <= n; i++) s[i + n] = s[i], t[i] = 1e9;
  for(int i = 1; i <= 2 * n; i++) s[i] += s[i - 1];
  for(int i = 0; i <= 2 * n; i++) s[i] += N - i;
  for(int i = n + 1; i > 1; i--) { // i 从 n + 1 开始，特判特殊情况
    if(s[i] >= s[i - 1]) t[i] = 1;
    else t[i] = buc[s[i - 1]] - i + 1;
    buc[s[i]] = i;
  }
  memset(buc, 0x3f, N << 3);
  for(int i = 2 * n; i > 1; i--) {
    if(i > n) buc[s[i]] = i;
    else {
      int p = buc[s[i - 1] - 1];
      if(p < N) t[i] = min(t[i], p - i + (s[p] - s[n] == p - n ? 2 : 1));
    }
  }
  int fir = 0, cur = 0, fin;
  for(int i = 1; i <= 2 * n; i++) {
    if(a[i] == 0 && !fir) fir = i + 1 >> 1;
    else if(a[i] == 1) fin = cur = i + 1 >> 1;
  }
  for(int _ = 1; _ <= R; _++) {
    if(cur == 1) {if(fir <= _) cur = n, fin--;}
    else if(t[cur] <= _) cur--, fin--;
  }
  ans = min(ans, {cur, -p});
  return make_pair(cur, fin);
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> R, R = n + R % n;
  for(int i = 1; i <= 2 * n; i++) cin >> b[i];
  if(b[1] == 1) cout << n << "\n", exit(0);
  for(int i = 2; i <= 2 * n; i++) b[i] = b[i] < b[1] ? 0 : 2;
  b[1] = 1;
  auto fst = simulate(1), lst = simulate(n);
  for(int i = fst.second; i < lst.second; i++) {
    if(i != fst.second && (i % n + n) % n != 1) continue;
    int l = 1, r = n;
    while(l < r) {
      int m = l + r >> 1;
      auto dat = simulate(m);
      if(dat.second >= i) r = m;
      else l = m + 1;
    }
    int v = simulate(l).second;
    r = n;
    while(l < r) {
      int m = l + r + 2 >> 1;
      auto dat = simulate(m);
      if(dat.second <= v) l = m;
      else r = m - 1;
    }
    simulate(l);
  }
  cout << -ans.second << "\n";
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：Gmt丶FFF (赞：5)

首先有一个 $O(n^2r)$ 的做法，纯模拟，期望 $0$ pts，实际有 $11$ pts。

然后可以通过样例 $2$ 提示得到，由于 $1$ 最强，最后一定会留在 $1$ 靶位上，而且由于会一直赢，所以如果不在 $1$ 靶位上，每次会向右移一格，在 $n-1$ 回合以内就一定会到达 $1$ 靶位。

又由样例 $1$ 提示可得到，对于 $2$ 到 $n$ 靶位，最后最弱的 $n-1$ 个人一定会一人一直站在一个位子上，并且达到此状态回合数不超过 $n$，因为最弱的 $n-1$ 个人转了一圈以后一定会找到属于自己的靶场，如果没找到，那么一定有靶场为空，而这个人走 $n$ 次一定会走到这个靶场，两者矛盾，所以 $n$ 回合以内一定会达到最弱的 $n-1$ 个人占领这 $n-1$ 个靶场。

那么就能利用这两个性质进行优化，如果 $S_1$ 为 $1$，那么最后一定会留到 $1$，如果 $S_1$ 为最弱的 $n-1$ 个人，那么如果最弱的 $n-1$ 个对号入座，就可以直接确定位置了，如果两者都不是，那 $S_1$ 最后一定在一直转圈，等到所有人对号入座以后直接根据剩下了几回合计算出最后位置即可。

时间复杂度：$O(n^3)$，期望 $20$ pts，实际有 $33$ pts。

可以发现一个性质，其实对于一个人，我们并不关心他的具体数字，只关心大于 $S_1$ 还是小于 $S_1$，所以我们可以进一步把大于 $S_1$ 的数设为 $2$ 类数，小于 $S_1$ 的数设为 $0$ 类数，$S_1$ 设为 $1$。然后根据 $O(n^3)$ 的做法我们可以把 $S_1$ 分成三种情况讨论。

1、$S_1=1$

2、$2\le S_1\le n+1$

3、$n+2\le S_1\le n\times2$

第一种情况复杂度可优化至 $O(1)$。

剩下两种情况，我们先考虑第三种，因为看起来比较好处理，很明显对于这种情况，我们要先把所有 $2$ 类数入座，再把 $1$ 类数找第一个靶位入座，那么对于一个靶位有两个 $2$ 类数，或是 $1$ 号靶位有 $2$ 类数，我们直接找到接下来第一个空位入座即可，这个过程可以用栈模拟，处理环的情况即可当栈空时将所有数再入一次栈即可。复杂度降到了 $O(n^2)$

然而又有一个显然的结论，我们越往后坐，座位一定不会越靠前，所以我们只需要考虑座位在最前面的情况，我们先二分一次，找到第一次不会绕圈找到的座位，这个座位一定就是答案，那么对于这个答案，我们找到可能出发的最大值，同样可以用二分处理。

时间复杂度成功优化到 $O(n\log n)$，处理了两种情况后，分数成功提到 $52$ pts。

最后只剩下第三种情况，对于这种情况，最后 $S_1$ 一定实在绕圈，所以我们要找到绕圈的起点与绕圈的时间。

这一次我们只能考虑每个点什么时候能到达一号靶场，如果一个点两次到达一号靶场的间隔时间为 $n$，那么我们可以认定他在绕圈。

那么我们就要处理每个点多久能到达 $1$ 号靶场。

对于第 $1$ 时刻，留在 $1$ 靶场的为两者中的小值，而出去的是两者中的大值。

对于第 $2$ 时刻，留在 $1$ 靶场的为 $2$ 靶场的小值与 $1$ 靶场的小值，即前两个靶场的最小值，出去的是上一个留在 $1$ 靶场或这次前往 $1$ 靶场的值，即前两个靶场的次小值（已出去的不算）。

那么以此类推，第 $3$ 时刻留在 $1$ 靶场的为前三个靶场的最小值，出去的为前三个靶场的次小值（已出去的不算）。

这个操作我们就可以优先队列维护了，对于第 $i$ 次出队的，我们直接加到第 $i+n$ 个靶场即可。这个模拟我们持续 $2\times n$ 次后，每一次就是出一个进一个，并且进的一定是队列中的最大值，因为对于后 $n-1$ 个数，只有可能进一次队，然后到大于 $n$ 的靶场，所以模拟 $2\times n$ 次后一定不会再有后 $n-1$ 个数入队的情况。

那么这种情况模拟 $3\times n$ 次以后，我们就能找到循环起点时间了，即可找到循环次数，现在复杂度优化到了 $O(n^2\log n)$。

现在我们考虑对其优化，可以知道，如果我们将其位置排后，那么其出队会更晚，而其循环次数如果在一个值域 $\left(k\times n,k\times(n+1)\right]$ 内，因为初始点一定在 $1$ 号靶场，所以对于这种值域，最后的点一定也是单调的，所以我们可以二分找到所有在这个值域内的，最小的靶场即为这个值域的最右侧，再次二分找到最大答案为这个靶场的下标即可。

由于我们总共只枚举了 $3\times n$，所以值域最多只有 $3$ 个，这样我们就把复杂度优化至 $O(n\log^2_2n)$ 了。

但这么写会发现只有 $89$ pts，而且我们发现答案错误的正确值都在 $n$。

这是个什么情况呢，实际上，是因为由于一个数非常靠后，最后再进队，那么就可能会出现在大于 $2\times n$ 的首位，这是其第二次出现，即只有两次进队的循环节起点，而之前的情况都是有三次进队的循环节起点，那么只有两次的就有可能在有三次的前面。那么我们再对第 $n$ 个节点进行判断是否可成为最优解即可。

至此，已得分数 $100$ pts。

时间复杂度：$O(n\log^2_2 n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int wr[20],cnwr;
inline int read()
{
	int sum=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')sum=(sum<<1)+(sum<<3)+(ch^48),ch=getchar();
	return sum;
}
inline void write(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(!x)putchar('0');
	while(x)wr[++cnwr]=x%10,x/=10;
	while(cnwr)putchar(wr[cnwr]^48),cnwr--; 
}
const int N=4e5+5;
int n,k,a[3*N],s[N],num;
bool vis[N];
priority_queue<int>q;
namespace solve1
{
	int st[N],head;
	int getans(int x)
	{
		for(int i=1;i<=2*n-1;i++)s[i]=a[i];
		for(int i=2*n-1;i>=2*x-1;i--)a[i+1]=a[i];
		a[2*x-1]=1;
		head=0;
		for(int i=1;i<=n;i++)vis[i]=0;
		for(int i=2;i<=n;i++)if(a[i*2]==2||a[i*2-1]==2)vis[i]=1;
		for(int i=2;i<=n;i++)if(!vis[i])st[++head]=i;
		for(int i=n;i>=1;i--)
		{
			if(st[head]==i)head--;
			if(!head)for(int i=2;i<=n;i++)if(!vis[i])st[++head]=i;
			if(a[i*2]==2&&a[i*2-1]==2)vis[st[head--]]=1;
			if(i==1&&(a[i*2]==2||a[i*2-1]==2))vis[st[head--]]=1;
		}
		head=0;
		for(int i=2;i<=n;i++)if(!vis[i])st[++head]=i;
		st[0]=st[head];
		while(head&&st[head]>x)head--;
		for(int i=1;i<=2*n-1;i++)a[i]=s[i];
		return st[head];
	}
	void solve()
	{
		int num=getans(2);
		int l=2,r=num-1;
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			if(getans(mid)==num)l=mid;
			else r=mid-1;
//			cout<<l<<" "<<r<<" "<<mid1<<" "<<mid2<<" "<<getans(mid1)<<" "<<getans(mid2)<<endl;
		}
		while(l<=n&&getans(l+1)<num)
		{
			num=getans(l+1);
			l=l+1,r=n;
			while(l<r)
			{
				int mid=(l+r+1)>>1;
				if(getans(mid)==num)l=mid;
				else r=mid-1;
			}
		}
		write(l);
	}
}
namespace solve2
{
	int getans(int x)
	{
		for(int i=1;i<=2*n-1;i++)s[i]=a[i];
		for(int i=2*n-1;i>=2*x-1;i--)a[i+1]=a[i];
		a[2*x-1]=1;
		while(!q.empty())q.pop();
		int num=min(a[1],a[2]);
		a[2*n+2]=max(a[1],a[2]);
		for(int i=2;i<=2*n;i++)
		{
			q.push(-a[i*2]);
			if(i<=n)q.push(-a[i*2-1]);
			int x=-q.top();
			a[i*2+n*2]=max(num,x);
			num=min(num,x);
			q.pop();
//			cout<<i<<" "<<x<<endl;
		}
		int ans=0;
		for(int i=3*n;i>n;i--)if(a[i*2]==1){ans=-(k-i+1);break;}
		for(int i=1;i<=2*n-1;i++)a[i]=s[i];
		return ans;
	}
	void solve()
	{
		int res=0,ans=1e9;
		int l=1,r=n;
		while(l<=n)
		{
			r=n;
			int ll=l;
			int sum=getans(l),sum2=(sum+1)/n*n;
			if(sum>=0)sum2=sum/n*n+n;
			sum2--;
			while(l<r)
			{
				int mid=(l+r+1)>>1;
				if(getans(mid)<=sum2)l=mid;
				else r=mid-1;
			}
			if((sum%n+n)%n+1<=ans)
			{
				ans=(sum%n+n)%n+1;
				int rr=l;
//				cerr<<ll<<" "<<rr<<endl;
				while(ll<rr)
				{
					int mid=(ll+rr+1)>>1;
					if(getans(mid)==sum)ll=mid;
					else rr=mid-1;
				}
				res=ll;
			}
			l++;
		}
		if((getans(n)%n+n)%n+1<=ans)res=n;
		write(res);
	}
}
int main()
{
//	freopen("archery05.in","r",stdin);
//	freopen("archery.out","w",stdout);
	n=read(),k=read();
	num=read();
	for(int i=1;i<2*n;i++)a[i]=(read()>num)?2:0;
	if(num==1)write(n);
	else if(num>=n+2)solve1::solve();
	else solve2::solve();
	return 0;
}
/*
4 100
7
8
6
4
5
2
1
3
*/
```


---

## 作者：unputdownable (赞：5)

其实 IOI 自己的[英文题解](https://ioinformatics.org/files/ioi2009solutions.pdf)讲的还是很好的，当年国家队的[解题报告](https://noi.ccf.org.cn/jlfx/2009-10-08/716183.shtml)也是英文题解的翻译。

如果想要数据可以去 [IOI 官网](https://ioinformatics.org/page/ioi-2009/35)下载。

--------

首先这个结构非常的混沌，起始位置不同会小小的更改靶位上初始的人，使得你很难观察性质，只能直接模拟比赛。

所以这题应该分为两个部分：优化模拟的复杂度，以及尝试减少模拟的次数。

下面先讨论如何**降低模拟一次比赛的复杂度**。

--------

定义 $W$ 集合表示 $1$ 和 $(n+2) \cdots(2 \times n)$ 这 $n$ 个人的集合。 

可以发现再若干轮后局面会趋于循环。（看到 $r$ 这么大想必也能猜出来吧）

然后可以得到一个具体的结论，就是经过至多 $2n$ 轮后局面会变成 $W$ 集合里的人各占一个靶位，其他人以一定顺序轮转（其中 $1$ 一定会停在 $1$ 号靶位）。

$1$ 号选手一定会在 $n$ 轮内停在 $1$ 号靶位，转而关注 $(n+2) \cdots(2 \times n)$ 这 $n-1$ 个人。

将他们看成白球，其他看成黑球。这样就有 $n-1$ 个白球，而且可以认为白球完全相同，因为证明这个结论不需要关心某个人的具体位置。

那么一个白球能向前移动当且仅当他在 $1$ 号靶位，或者他所在的靶位两个人都是白球（我们认为这时候有一个白球开始就被卡住了）。

当他移动到一个没有白球的位置时，我们就认为他会一直卡在那里（即使能替换也只是白球换白球，对颜色没有影响）。

直接考虑每个白球和他最后会被卡住的位置，那么上面那个结论就易证了。

--------

确定结构后，这引向一个自然的分类讨论：

1. 我是 $1$ 号选手，因为我必然在 $1$ 号靶位停下，所以从 $n$ 开始即可；
2. 我不在 $W$ 集合中，我最后一定在绕圈圈，那么我只要求出 $2n+1$ 和 $3n$ 中我什么时候到达 $1$ 号靶位就能反推出让我最后的位置；
3. 我在 $W$ 中并且不是 $1$，那么我一定会卡死在一个位置，目标就是求出那个位置。

两种情况得分别优化。

--------

先讨论在 $W$ 中并且不是 $1$ 的情况。我要求出我被卡死的位置。

沿用上面证明的思想，将比我菜的看成白球，我是灰球，剩下的是黑球~~当他不存在就好~~。

还是考虑去匹配最终卡死的位置。

因为灰球即使卡在一个位置也能通过白球继续往前走，我们不妨先将灰球看成黑球。

白球直接没有区别，可以对每个白球贪心匹配前面第一个没有被匹配的靶场（然后他就会被定死在那里）。这里要注意 $1$ 号靶场是不能被匹配的，因为 $1$ 号选手会占据这个靶场并击败所有人。

然后再考虑灰球，你发现对灰球也可以贪心匹配前面第一个没有被匹配的靶场。首先他不可能走的更远，其次如果他占据了现在某个白球的靶场，那个白球到这个靶场的时候就会把灰球往前推。

实现的时候建议从 $1$ 号开始，捡起所有白球，然后从 $n$ 向 $2$ 遍历，不断重复有白球就拿然后放下一个的过程，直到所有白球都找到位置。

他的复杂度是 $\Theta(n)$ 的。

--------

接下来讨论我不在 $W$ 集合中的情况。

不难发现我们只关注 $1$ 号靶场。

$1$ 号靶场的比赛可以理解为一个人是擂主，后面的人一直挑战。

我们可以对每个时刻 $t$ 维护一个**可能去挑战的人的集合 $A$**，即假设他们一直赢，在时刻 $t$ 及以前能到达靶场 $1$ 的人的集合。

不难发现**最终挑战擂主的人一定在 $A$ 中，并且一定是最强的那一个**。

这是因为最强的人一定能赢下与集合内其他人的比赛从而一定能去挑战擂主。

而挑战擂主的人一定只有一个。

$A$ 的维护方法就是在 $t$ 轮**开始前**把初始站在靶场 $t$ 的人塞进去。

当然，上去挑战必然有一个人会输，那么那个人会在第 $t$ 轮重新回到 $n$ 号靶场，要在第 $t+n$ 轮才能回到 $A$ 中，我们认为他初始站在 $t+n$ 号靶场就行了。

记得特判初始 $1$ 号靶场的两个人并维护擂主。

复杂度也是 $\Theta(n)$ 的。

--------

接下来讨论怎么优化模拟次数。

没有思路的时候可以优先打一个表：（这是第 $56$ 个点的答案，第一行是从每个位置开始最终会到哪里的表）。

![](https://cdn.luogu.com.cn/upload/image_hosting/4eq89vow.png)

你发现他明显分成了几个单调不降的段。

你再思考可以发现，如果将 $1$ 掉到 $n$ 看成 $1$ 再往前走一步走到 $0$，以此类推（即统计从将 $1$ 掉到 $n$ 的次数 $T$，并将最终到达的位置看成 $res-n \times T$），那么这个东西在整个序列上是单调不降的。

证明是简单的，还是像上面分 $3$ 类讨论（与上面情况一一对应）：

1. 显然。
2. 思考找空位的过程，初始位置越后面，找到的空位不会越往前。
3. 加入 $A$ 的时间更晚，被弹出 $A$ 的时间不会更早。

都很显然。

由于我们之前证明了 $r$ 可以一直减 $n$ 直至小于等于 $3n$，所以上面两个模拟出的结果（$res-n \times T$）都在 $-2n$ 到 $n$ 之间，也就是说不同的 $T$ 不会很多（事实上，最多只有 $3$ 种）。

直接对每个 $T$ 二分就能做到只需要 $\Theta(\log n)$ 次模拟。

总时间复杂度 $\Theta(n \log n)$。

--------

**Code：**

```c++
#include <bits/stdc++.h>
#define pii pair <int, int> 
using namespace std;
inline int read(void) {
    int x=0,sgn=1; char ch=getchar();
    while(ch<48||57<ch) {if(ch==45)sgn=0;ch=getchar();}
    while(47<ch&&ch<58) {x=x*10+ch-48;   ch=getchar();}
    return sgn? x:-x;
}
void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,N,r,lim,Ans,pos;
int a[400005];
int cnt[3],cntT[600005][3];
pii result[400005];
inline int color(int x) { return (a[x] > a[1] ? 2 : 0); }
int bumps;  // 记录我从 1 号靶场掉下去多少次
inline void init(int x) {
    cnt[0]=cnt[1]=cnt[2]=bumps=0;
    for(int i=1; i<=lim; ++i) cntT[i][0]=cntT[i][1]=cntT[i][2]=0;
    for(int i=1; i<x; ++i) {
        ++cntT[i][color(i<<1)];
        ++cntT[i][color(i<<1|1)];
    }
    ++cntT[x][1]; ++cntT[x][color(x<<1)];
    for(int i=x+1; i<=n; ++i) {
        ++cntT[i][color((i<<1)-1)];
        ++cntT[i][color(i<<1)];
    }
}
inline void challenge(int t,int i,int&host) { if(i<host) swap(i,host); ++cntT[t][i]; bumps+=(i==1); }
inline int calc1(int x) {
    init(x);
    int host=0;  // who keep 1
    for(int k=0; k<=2; ++k) if(cntT[1][k]) { host=k; --cntT[1][k]; break; }
    for(int i=1; i<=N; ++i) {
        for(int k=0; k<=2; ++k) cnt[k]+=cntT[i][k];
        if(cnt[0]) --cnt[0],challenge(i+n,0,host);
        else if(cnt[1]) --cnt[1],challenge(i+n,1,host);
        else --cnt[2],challenge(i+n,2,host);
    }
    for(int i=1; i<=n; ++i) {
        for(int k=0; k<=2; ++k) cnt[k]+=cntT[i+N][k];
        if(cnt[0]) --cnt[0],challenge(1,0,host);
        else if(cnt[1]) return (bumps+=(i<=r)),(i-r+n-1)%n+1;
        else --cnt[2],challenge(1,2,host);
    }
}
inline int calc2(int x) {
    init(x);
    cnt[2]=cntT[1][2]; cntT[1][2]=0;
    for(int i=n; i>=2; --i) {
        cnt[2]+=cntT[i][2]; cntT[i][2]=0;
        if(cnt[2]) ++cntT[i][2],--cnt[2];
    }
    for(int i=n; i>=2; --i) {
        cnt[2]+=cntT[i][2]; cntT[i][2]=0;
        if(cnt[2]) ++cntT[i][2],--cnt[2];
    }
    for(int i=x; i>=2; --i) if(!cntT[i][2]) return i;
    ++bumps;
    for(int i=n; i>=x; --i) if(!cntT[i][2]) return i;
}
inline pii calc(int x) {
    if(result[x].first) return result[x];
    int res=( a[1]<=n+1 ? calc1(x) : calc2(x) );
    return result[x]=make_pair(res,bumps); 
}
inline void check(int l,int p) {  // 倍增找出最远的
    if(p>pos) return ;
    int d=1;
    for(; l+d<=n; d<<=1) if(calc(l+d).first==p) l+=d; else break;
    for(; d; d>>=1) if(l+d<=n&&calc(l+d).first==p) l+=d;
    Ans=l; pos=p;
}
signed main() {
    n=read(); N=n<<1; lim=n*3;
    r=read()%n; 
    for(int i=1; i<=N; ++i) a[i]=read();
    if(a[1]==1) return write(n),puts(""),0;
    pii L=calc(1),R=calc(n); 
    pos=L.first; 
    check(1,L.first);
    for(int i=L.second-1,l,r; i>=R.second; --i) {
        l=1; r=n;
        while(l<r) {
            int mid=(l+r)>>1;
            if(calc(mid).second<=i) r=mid;
            else l=mid+1;
        }
        check(l,calc(l).first);
    }
    write(Ans); puts("");
    return 0;
}
```





---

