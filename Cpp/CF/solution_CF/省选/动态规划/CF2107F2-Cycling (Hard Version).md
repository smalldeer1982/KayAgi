# Cycling (Hard Version)

## 题目描述

> 这是此问题的困难版本，和其他版本的区别是此版本中 $n\le 10^6$，且不需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

额外地，Leo 想知道对于每个 $i(1\le i\le n)$，当只有骑手 $1,2,\cdots,i$ 存在时，他超过所有 $i$ 名骑手的最小代价。

## 说明/提示

**样例解释**

第一组数据中，当存在所有 $n$ 名骑手时，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中，当存在所有 $n$ 名骑手时，如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

By chenxi2009

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 1 1 1
2
1 2
4
4 1 3 2```

### 输出

```
1 3 7
1 2 3 4
1 3
4 3 6 8```

# 题解

## 作者：masonpop (赞：2)

思维难度 *800 的做法。

以下的 $a$ 序列均是 reverse 后的，即这里认为需要从 $1$ 走到 $n$。

不难想到最优方案一定是若干段代价相同的段组成的，考虑对这些段进行 DP。由于 F2 是后缀询问，因此设 $f_i$ 表示走完了 $1\sim i$，走到 $n$ 的最小代价。转移就枚举这一段的结尾 $j$，那么最优方案一定是把 $[i+1,j]$ 区间的最小值推过来，再一路推到 $j$。设 $[i+1,j]$ 的最小值位置为 $p_j$（如有多个取离 $i+1$ 最近的），那么有转移：

$$\begin{aligned}f_i=\min\limits_{j\ge i+1}\{f_j+(p_j-i-1)+(j-i-1)+a_{p_j}\times (j-i)\}\end{aligned}$$

直接实现可以通过 F1。

注意到这个做法转移和区间最小值有关，太不牛了，考虑简化一下转移形式。我们可以把刚刚的转移方式拆成两段，即 $(i+1)\to p_j$ 和 $(p_j+1)\to j$。那么，我们其实可以认为，如果要从 $i$ 走到 $j$，则中间的代价只有 $a_i$ 和 $a_j$ 两种可能。显然这样能覆盖刚刚的所有转移且均是合法的。

因此可以把转移式拆成以下两种取 $\min$：

$$\begin{aligned}f_i\leftarrow  f_j+(a_i+1)\times (j-i)\end{aligned}$$

$$\begin{aligned}f_i\leftarrow f_j+2(j-i-1)+a_j\times (j-i)\end{aligned}$$

这个东西显然可以使用斜率优化/李超树实现。

这份[代码](https://codeforces.com/contest/2107/submission/319011411)使用后者实现，复杂度 $O(n\log n)$。

---

## 作者：Eous (赞：2)

建议先阅读[简单版题解](https://www.luogu.com.cn/article/ditmhfhm)。~~不读也行~~

我们发现其实我们是可以确定区间的分界点的。比如我们拿一个样例：`4 1 3 2`。我们首先拿 $2$ 一直超。直到我们发现这里出现了一个 $1$。我们发现拿 $1$ 一直超比拿 $2$ 一直超更优。于是我们改拿 $1$ 一直超。我们把 $dp_i$ 的意义改一下，改成：先拿最后的一直超，直到现在超的比前一个数小，我们改拿前一个数继续超，如此循环往复。用此策略超到最前面的最小代价。显然，这玩意可以 $O(n)$ 预处理。

> 不懂策略的看过来\
> 比如 `4 1 3 2 5 3`，先拿 $3$ 一直超，直到我们看到了 $2$，就改拿 $2$ 继续超，然后我们又看到了 $1$，我们又改超 $1$。

那有人要问了：你没考虑把一段区间的最小值掏过来然后拿它一直超的情况啊？确实没考虑，所以我们现在考虑。依然是这个样例：`4 1 3 2 5 3`。假设我们现在在第 $6$ 个数后面。如果我们想把 $2$ 掏过来超，那么需要花费的代价是 $dp_4 + (6 - 4) \times 2 + 2 \times (6 - 4)$。每一项分别表示：已经走到 $2$ 所在的位置还需要的代价，$2$ 往返需要的代价，不停的超过 $2$ 需要的代价。

我们再推几组样例，会发现：如果我想把 $a_i$ 拿到 $j$ 的位置然后一直超，所需要的代价是 $dp_i + (j - i) \times 2 + (j - i) \times a_i$。这玩意可以看做是一个关于 $j$ 的一次函数。总共 $n$ 个一次函数。我们把所有的一次函数都塞到一颗李超线段树里，然后每个位置的答案就是在这个位置查最小值。

```cpp
#include<bits/extc++.h>
#define int long long
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn = 1e6 + 5;
int n;
int a[maxn],dp[maxn],ans[maxn];
struct line
{
    int k,b;
    int f(int x){return k * x + b;}
}tree[maxn << 2];
int read()
{
    int x = 0,f = 1;
    char ch = getchar();
    while (!isdigit(ch)){f = ch == '-' ? -1 : 1; ch = getchar();}
    while (isdigit(ch)){x = x * 10 + (ch ^ 48); ch = getchar();}
    return x * f;
}
void build(int l,int r,int rt)
{
    tree[rt] = {0,inf};
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l,mid,ls);
    build(mid + 1,r,rs);
}
void upd(line ln,int l = 1,int r = n,int rt = 1)
{
    int lp = tree[rt].f(l),rp = tree[rt].f(r);
    int lq = ln.f(l),rq = ln.f(r);
    if (lq <= lp && rq <= rp)
        tree[rt] = ln;
    else if (lq < lp || rq < rp)
    {
        int mid = (l + r) >> 1;
        if (ln.f(mid) < tree[rt].f(mid))
            swap(ln,tree[rt]);
        if (ln.f(l) < tree[rt].f(l))
            upd(ln,l,mid,ls);
        else
            upd(ln,mid + 1,r,rs);
    }
}
int que(int pos,int l = 1,int r = n,int rt = 1)
{
    int res = tree[rt].f(pos);
    if (l == r)
        return res;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        res = min(res,que(pos,l,mid,ls));
    else
        res = min(res,que(pos,mid + 1,r,rs));
    return res;
}
void solve()
{
    n = read();
    build(1,n,1);
    stack<int> stk;
    stk.push(0);
    for (int i = 1,j; i <= n; i++)
    {
        a[i] = read();
        while (a[j = stk.top()] > a[i])
            stk.pop();// 单调栈维护 dp
        // 我们发现，a[i] 会在 i 和第一个小于 a[i] 的数之间被一直超，于是效仿简单版的转移即可
        dp[i] = dp[j] + i - j - 1 + (i - j) * a[i];
        upd({a[i] + 2,dp[i] - (a[i] + 2) * i});// 塞进李超树
        ans[i] = que(i),stk.push(i);// 单点查询更新答案（一定是边插入边查询）
    }
    for (int i = 1; i <= n; i++)
        printf("%lld ",ans[i]);
    putchar('\n');
}
signed main()
{
    int t = read();
    while (t--)
        solve();
    return 0;
}
```

---

