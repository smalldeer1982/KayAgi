# Mirror

## 题目背景

![Mirror](https://mivik.gitee.io/image/nurture/mirror.png)

> And it’s not the voice of all the others
>
> You’ve only said it to yourself
>
> I know what you want from me, from me
>
> I know what you’re thinking

## 题目描述

> Porter Robinson: We all have these avatars that we give to our critical inner voices - we might imagine a scornful parent telling us we’ll fail, or a critic telling us our work comes up short, or a society telling us that we aren’t good enough - it’s about recognizing that most of this criticism is self-inflicted.

Mivik 在镜中看见了自己的 Inner Voice ——不过是在一个镜子般对称的迷宫中。这个迷宫很特殊：它有无穷多行和无穷多列，行和列都从 $0$ 开始标号。一个格子 $(i,j)$ 能通过（没有障碍）当且仅当 $(i\&j)=0$，其中 $\&$ 指按位与运算（Bitwise And，[百度百科](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E4%B8%8E/9601818)）。下图给出了这个迷宫的 $0\sim63$ 行和 $0\sim 63$ 列的图像：

![迷宫](https://cdn.luogu.com.cn/upload/image_hosting/das5c73w.png)

Mivik 想抓到并消灭那个给予自己负面声音的 Inner Voice，但他找不到路了。Mivik 和 Inner Voice 最初处在迷宫中的两点。Mivik 想知道，在 Mivik 的 Inner Voice 一直不移动的情况下，他至少需要走过多少个方格才能抓到他的 Inner Voice（Mivik 的起始格不算）。

但是... 游戏并不会像 Mivik 想象的一样简单。邪恶的 ggy 在这个迷宫中的某些格子布下了许多炸弹，Mivik 需要拆除它们才能踏上这些格子。Mivik 需要你告诉他，在他走过的方格数最少的情况下，他至少需要拆除哪些炸弹。

**请注意炸弹可能会重合，而你只有拆除一个格子上的所有炸弹才能通过这个格子。保障炸弹不与起点重合。**

## 说明/提示

### 样例解释

样例一：显然由于没有任何炸弹，Mivik 向右走两格就能抓到他的 Inner Voice。

样例二：Mivik 的最短路径如图所示：

![路径](https://cdn.luogu.com.cn/upload/image_hosting/mg0hmhgs.png)

其中，图片左上角为 $(0,0)$，蓝色代表 Mivik 的起始位置，绿色代表 Inner Voice 的位置，红色代表 Mivik 的最短路径，黄色代表炸弹，橙色（其实是黄色 + 红色）代表 Mivik 必须拆除的炸弹。

### 数据范围

对于全部数据，有 $1\le n\le 2\cdot 10^5$，$(sx,sy)\ne(ex,ey)$，并保证对于给出的任何坐标 $(x,y)$ 都有 $x\&y=0$ 且 $0\le x,y\le 10^{18}$。

Subtask 1 (10 pts)：保证 Mivik 可以直线（只向 上/下/左/右 走）抓到他的 Inner Voice。

Subtask 2 (15 pts)：保证 $sx=sy=0$。

Subtask 3 (20 pts)：保证 $0\le(\text{任意 x,y 坐标})\le 100$。

Subtask 4 (25 pts)：保证 $n=0$。

Subtask 5 (30 pts)：无特殊限制。

## 样例 #1

### 输入

```
0
0 0
0 2```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
0 0
0 2
1 2
4 2
3 4```

### 输出

```
13
110```

## 样例 #3

### 输入

```
0
12 34
3 100```

### 输出

```
85
```

# 题解

## 作者：Mivik (赞：5)


[欢迎到我的博客查看](https://mivik.gitee.io/2021/solution/mivik-round-nurture-mirror/)

## Subtask 1

由于可以直走，两个点之间要走多少格就是它们的曼哈顿距离了，然后中间需要拆除的障碍物直接判一下就好了。

## Subtask 2

如果你善于观察，那么你会发现当起点位于 $(0,0)$ 时，两个点之间要走多少格依旧等于他们的曼哈顿距离。为什么呢？

我们注意到时刻都必须有 $x\&y=0$，初始时是满足条件的，那么我们考虑每次取出 $(x|y)$ 的 lowbit，然后把这一位走掉，一直这样直到走到 $(0,0)$，我们的总路径是 $(x+y)$。举个例子，假设 $(x,y)=(4,3)$，那么我们先写出二进制：

> x: 100
>
> y: 011

然后 lowbit 是 $y$ 的 1，所以我们从 $(4,3)$ 走到 $(4,2)$，变成了：

> x: 100
>
> y: 010

lowbit 是 $y$ 的 2，所以我们从 $(4,2)$ 走到 $(4,0)$，变成了：

> x: 100
>
> y: 000

然后直接走到 $(0,0)$ 就可以了。容易发现最短的路径是唯一的，因为如果你减少的那一维不是 lowbit 所在的那一维的话，那么必定会产生一堆 1，然后这堆 1 就会和 lowbit 所在的那一维位与不为 0 了，不合法。

综上，我们模拟一下上面那个过程就好了。

[mivik.h](https://mivik.gitee.io/mivik.h)

```cpp
// Mivik 2021.1.6
#include <mivik.h>

#include <algorithm>
#include <list>

using std::list;

MI cin;

typedef long long qe;

const int N = 200005;

struct point { qe x, y; };
template<> struct Q<point> { inline void operator()(MI &r, point &t) {
	r > t.x > t.y;
} };
int N;
point st, en, bar[N];
bool vis[N];
list<int> rem; // 还没被处理的障碍物
int main() {
	cin > n;
	for (int i = 1; i <= n; ++i) {
		cin > bar[i];
		rem.push_back(i);
	}
	cin > st > en;
	if (st.x || st.y) {
		cout < "Orz\n";
		return 0;
	}
	auto &[x, y] = en;
	cout < (x + y) < endl;
	for (int i = 0; i < 60; ++i) { // 扫描 lowbit
		if ((x >> i) & 1) {
			const qe to = x & (x - 1);
			for (auto it = rem.begin(); it != rem.end(); ) {
				auto &p = bar[*it];
				if (p.y == y && to <= p.x && p.x <= x) {
					vis[*it] = 1;
					it = rem.erase(it);
				} else ++it;
			}
			x = to;
		} else if ((y >> i) & 1) {
			const qe to = y & (y - 1);
			for (auto it = rem.begin(); it != rem.end(); ) {
				auto &p = bar[*it];
				if (p.x == x && to <= p.y && p.y <= y) {
					vis[*it] = 1;
					it = rem.erase(it);
				} else ++it;
			}
			y = to;
		}
	}
	for (int i = 1; i <= n; ++i) cout < vis[i];
	cout < endl;
}
```

## 满分做法

实际上我们可以递归。每次把一个宽和高都为 $2^n$ 的迷宫（以 $(0,0)$ 为左上角）平均分成四个部分，即左上左下右上和右下，但右下是不能走的所以我们忽略。如果当前位置和终点在一个块就继续向下递归，否则我们使两个点都统一“走”到左上角那一块然后再递归到左上角。容易发现这样对答案是没有影响的。

根据我们在 Subtask 2 中得到的结论，在一个块内的点是可以用 $abs(x-\text{左上角x})+abs(y-\text{左上角y})$ 的步数走到左上角的，因此计算距离就容易了。但是障碍物的判断呢？

实际上我们只需要判断一下 $dist(st,p)+dist(p,en)$ 是否等于 $dist(st,en)$ 就好了，因为根据上面的说明我们知道两点间的最短路径只有一条。

时间复杂度 $O\left(\log^2(10^{18})n\right)$。但我的实现 稍 微 研究了一下二进制本质然后写了一个 $O(1)$ 判上面那个东西的函数，所以就少了个平方了。

[mivik.h](https://mivik.gitee.io/mivik.h)

[代码](https://paste.ubuntu.com/p/m3mpBFhC67/)


---

## 作者：AuCloud (赞：2)

想来想去还是来写一发题解吧（

# 题意

给你一个[如图所示](https://www.luogu.com.cn/problem/P7264)的分形迷宫，让你求两点间最短距离以及路径上的炸弹数量

# 题解

赛时先瞅了一眼T3发现十分恶心，就回去好好整T1T2了，现在想想我干嘛来看T3呢（

![](https://s3.ax1x.com/2021/01/11/s3INGD.png)

奇奇怪怪的分形，可以比较容易的看见将每个大正方形分成四份，左上右上左下的部分是**完全相同**的，而右下部分是全黑所以不需要考虑。所以很容易想到递归。

继续观察，选几个点手画一下，发现**两点之间最短路唯一**（这个不知道咋证明，大家感性理解（？）

注意是最短路，不是所有可能路径。

而对于每个正方形中每个点，显然存在一条通向正方形左上角的路，这样递归再回溯上来，一定会在最大的正方形的左上角相遇。这个就是一条**可行路径**

但是请看下图：

![](https://s3.ax1x.com/2021/01/11/s3qSP0.png)

从黄色块出发到橙色块，最短路径显然是绿色部分，然而在上面的方法里我们多算了红色的部分两次，所以上面的并不是最优。

如何解决？考虑这个最短路的性质：必定是

某两个正方形左上角的连线长度+两个点分别到自己对应的正方形的左上角点的距离

感性理解：下图中紫色线段+两条蓝色线段

![](https://s3.ax1x.com/2021/01/11/s3L49P.png)

我们可以每次递归时把当前正方形左上角作为“拐点”记录下来，同时记录当前到点的距离是多少，在两边都递归完之后用类似Floyd一样的方法枚举点对求最短路。

看起来十分暴力，但是分析一下复杂度：

$10^{18}$大概是$2^{60}$，我们每次递归一层相当于把它除以二。所以60层就会递归完毕，也就是说对于起点和终点，每个点的“拐点”最多$60$个，平方级枚举完全没问题。

这样，第一问的距离就解决了！

剩下的就十分好做了：

继续暴力枚举每个炸弹位置，枚举路径上的点对，看是否在两者之间就没问题。

总时间复杂度~~O(可过)~~$O(Nlog^210^{18})$

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int zx[1000001], zy[1000001], id[1000001];
int ans = 0, cnt;
struct hehe{
    int x, y;
}p[3][1000001], guai[1000001], l[1000001];
bool ddd[1000001];
map<pair<int,int>, int>mp[3];
int tot[3];
bool in(int a,int b,int c,int d,int x,int y)
{
	if(a<=x&&x<=c&&b<=y&&y<=d)
		return 1;
	return 0;
}
int f(int a,int b,int c,int d,int x,int y,int opt)
{
	int l=c-a+1,mid;
	mid=l>>1;
	p[opt][++tot[opt]]=hehe{a,b};

	if(in(a,b,a+mid-1,b+mid-1,x,y))
	{

		if(mid==1)
		{
			p[opt][++tot[opt]]=hehe{x,y};
			return mp[opt][make_pair(a,b)]=0;
		}
		return mp[opt][make_pair(a,b)]=f(a,b,a+mid-1,b+mid-1,x,y,opt);
	}
	else if(in(a+mid,b,c,b+mid-1,x,y))
	{
		if(mid==1)
		{
			p[opt][++tot[opt]]=hehe{x,y};
			return mp[opt][make_pair(a,b)]=1;
		}
		return mp[opt][make_pair(a,b)]=f(a+mid,b,c,b+mid-1,x,y,opt)+mid;
	}
	else if(in(a,b+mid,a+mid-1,d,x,y))
	{
		if(mid==1)
		{
			p[opt][++tot[opt]]=hehe{x,y};
			return mp[opt][make_pair(a,b)]=1;
		}
		return mp[opt][make_pair(a,b)]=f(a,b+mid,a+mid-1,d,x,y,opt)+mid;
	}
    return 0;
}
/*int fz(int x1, int y1, int x2, int y2, int x, int y, int op)//写失败的递归
{
    p[op][++tot[op]] = hehe{x1, y1};
    int xx = (x1 + x2) >> 1;
    int yy = (y1 + y2) >> 1;
    if(x <= xx && y <= yy)
    {
        if(x2 - x1 == 0)
        {
            p[op][++tot[op]] = hehe{x, y};
            return mp[op][make_pair(x1, y1)] = 0;
        }
        return mp[op][make_pair(x1, y1)] = fz(x1, y1, xx, yy, x, y, op);
    }
    else if(x <= xx && y > yy)
    {
        if(x2 - x1 == 0)
        {
            p[op][++tot[op]] = hehe{x, y};
            return mp[op][make_pair(x1, y1)] = 1;
        }
        return mp[op][make_pair(x1, y1)] = fz(x1, yy, xx, y2, x, y, op) + (x2 - x1 + 1) / 2;
    }
    else
    {
        if(x2 - x1 == 0)
        {
            p[op][++tot[op]] = hehe{x, y};
            return mp[op][make_pair(x1, y1)] = 1;
        }
        return mp[op][make_pair(x1, y1)] = fz(xx, y1, x2, yy, x, y, op) + (x2 - x1 + 1) / 2;
    }
}*/
signed main()
{
    int x1, x2, y1, y2;
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> l[i].x >> l[i].y;
    }
    cin >> x1 >> y1 >> x2 >> y2;
    int ysx = 0, ysy = 0, zxx = 1ll << 60, zxy = 1ll << 60;
    f(ysx, ysy, zxx, zxy, x1, y1, 1);
    f(ysx, ysy, zxx, zxy, x2, y2, 2);
    int ans = 0x7f7f7f7f7f7f7f7f;
    int num1 = 0, num2 = 1;
    for(int i = 1; i <= tot[1]; i++)
    {
        for(int j = 1; j <= tot[2]; j++)
        {
            if(p[1][i].x == p[2][j].x || p[1][i].y == p[2][j].y)
            {
                int ll = abs(p[1][i].x - p[2][j].x + p[1][i].y - p[2][j].y);
                auto qwq = make_pair(p[1][i].x, p[1][i].y), qaq = make_pair(p[2][j].x, p[2][j].y);
                if(ans > mp[1][qwq] + mp[2][qaq] + ll)
                {
                    num1 = i, num2 = j;
                    ans = mp[1][qwq] + mp[2][qaq] + ll;
                }
            }
        }
    }
    for(int i = tot[1]; i >= num1; i--)
    {
        guai[++cnt] = p[1][i];
    }
    for(int i = num2; i <= tot[2]; i++)
    {
        guai[++cnt] = p[2][i];
    }
    cout << ans << endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j < cnt; j++)
        {
            if(guai[j].x == guai[j + 1].x)
            {
                if(l[i].x == guai[j].x && ((guai[j].y <= l[i].y && l[i].y <= guai[j + 1].y) || (guai[j + 1].y <= l[i].y && l[i].y <= guai[j].y)))
                {
                    ddd[i] = 1;
                }
            }
            if(guai[j].y == guai[j + 1].y)
            {
                if(l[i].y == guai[j].y && ((guai[j].x<=l[i].x&&l[i].x<=guai[j+1].x) || (guai[j+1].x<=l[i].x&&l[i].x<=guai[j].x)))
                {
                    ddd[i] = 1;
                }
            }
        }
        cout << ddd[i];
    }
    return 0;
}
```

---

## 作者：囧仙 (赞：1)

由于出题人提供的题解的证明不甚清晰，于是打算自己写一篇题解谈一谈想法。

> $\verb!upd 2021.1.10 23:14!$ 修正了一些笔误。管理审核太快了还没来得及勘误 $\verb!qwq!$

## 题目大意

- 一个无穷大的矩阵，坐标为 $(x,y)$ 的格子可以通过当且仅当 $x\operatorname{and} y=0$ ，其中 $\operatorname{and}$ 是二进制下的与操作。

- 现在矩阵上有 $n$ 个位置 $(x_i,y_i)$ 为炸弹。询问从 $(s_x,s_y)$ 到 $(t_x,t_y)$ 的**最短路径**上有哪些炸弹。

## 题解

通过大眼观察法，我们能够从题目中所给的 $64\times 64$ 的矩阵图上观察到这样两个很重要的结论：

- 这张图形成了一个树形结构。也就是说，两点之间的路径**唯一确定**。

- 假使满足 $x>0,y>0$ 的点 $(x,y)$ 可以通过，那么 $(x-1,y)$ 和 $(x,y-1)$ 中**有且仅有**一个点可以通过。

我们先考虑第二个结论，因为根据这个结论可以反过来证明第一个结论。

事实上，假使 $x>0,y>0$ 的 $(x,y)$ 可以通过，那么 $x\operatorname{and} y=0$ 。于是对于不存在某个二进制位，使得 $x,y$ 的这一位同时相同。怎么样考虑 $x-1$ 后它的二进制值的变化呢？考虑 $x,y$ 的最右侧的为 $1$ 的位，因为减 $1$ 操作只会影响到这一位以及更低位的二进制值。不妨设 $x$ 最右侧的位是 $p$ ， $y$ 最右侧的位是 $q$ ，其所对应的二进制位是 $2^p$ 和 $2^q$ 。显然， $p\neq q$ （不然 $x,y$ 的与值就不为 $0$ 了） 那么要么 $p<q$ ，要么 $p>q$ 。

当 $p<q$ 时， $2^p-1$ 的末尾 $p-1$ 位全部都是 $1$ ，并且不会影响到 $x$ 的 $p+1$ 位以后的数位。但是由于 $p<q$ ，于是这部分 $1$ 和 $y$ 的与值仍然为 $0$ ，于是 $(x-1) \operatorname{and} y=0$ ，于是 $(x-1,y)$ **可以通过**。同时， $2^q-1$ 的末尾 $q-1$ 位全部都是 $1$ ，由于 $p<q$ ，于是此时 $x \operatorname{and} (y-1)\neq 1$ ，也就是 $(x,y-1)$ **不可通过**。

当 $p>q$ 时如法炮制，可以发现 $(x-1,y)$ 与 $(x,y-1)$ 中有且仅有一个可以通过。我们不妨将其与其左侧/上侧那个可达的点连边。

考虑第 $0$ 行和第 $0$ 列的数字。显然，除了 $(0,0)$ ，都可以向左侧或者上侧的点连边。于是所有点联通，并且边数是总点数 $-1$ 。这时已经满足**整张图是树形结构**这样的结论了。

下面考虑如何构造解法。事实上，在刚刚的论证过程中，我们提到了最低的为 $1$ 的位。我们可以用 $\operatorname{lowbit}$ 函数进行求值，其中 $\operatorname{lowbit}(x)$ 表示 $x$ 的最低位的 $1$ 对应的二进制数的值，并且 $\operatorname{lowbit}(x)=x\operatorname{and}(-x)$ （树状数组中也经常用到这个结论）。由于路径唯一，并且每个点只能向上或者向左走，我们可以考虑每个点每次走的时候**最远走多少**。

我们先找出 $(s_x,s_y),(t_x,t_y)$ 如果分别向左上角走，最终会走到哪里（不妨设为 $(p_x,p_y)$ ） 。观察可得该图为一个分形，并且每一个子正方形的第 $0$ 行第 $0$ 列都是可通过的位置。于是从小到大枚举这个子正方形的边长 $2^k$ 。我们能够通过 $\left\lfloor\dfrac{s_x}{2^k}\right\rfloor,\left\lfloor\dfrac{s_y}{2^k}\right\rfloor$ 计算出 $(s_x,s_y)$ 所在的这个正方形是第几排第几个的正方形。只要判断起点和终点是否在同一个正方形中就行了，可以计算出 $(p_x,p_y)$ 。由于是一个子图，我们可以将刚刚出现过的**所有坐标**（包括起点终点和炸弹坐标）向左平移 $p_x$ 、向上平移 $p_y$ ，于是起点和终点最终应当在第 $0$ 行或者第 $0$ 列会合了。
 
假设当前点在 $(x,y)$ ，满足 $x\neq 0$ 且 $y \neq 0$ 。考虑每次向左或者向上走尽可能远的距离。同样，我们求出 $x,y$ 的最低位 $p,q$ 。不妨设 $p<q$ ，那么该点可以不停向左走。什么时候这个点要改变方向了呢？

不妨举个例子：

$$\begin{aligned}
x&=554_{(10)}&=1000101010_{(2)} \cr
y&=336_{(10)}&=0101010000_{(2)} \cr
\end{aligned}$$

显然，由于 $p<q$ ，我们要不断减去 $x$ 的值，也就是向上走。可以发现，对于 $x$ 的后 $q$ 位，无论它的值如何，与上 $y$ 都是 $0$ 。那么也就是说，我们要不断减去这后 $q$ 位，直到他们全部为 $0$ 。

$$\begin{aligned}
x&=544_{(10)}&=1000100000_{(2)} \cr
y&=336_{(10)}&=0101010000_{(2)} \cr
\end{aligned}$$

此时 $p,q$ 的大小关系就对调了。于是我们应当向左走了。这一部分一共花费了 $554-544=10$ 步。

可以证明，全过程中走的步数不会超过 $\log_2(x+y)$ 。因为每走一段路，$x$ 或 $y$ 的 $\operatorname{lowbit}$ 值至少加上 $1$ 。

然后这条路就被我们拆分成了 $\log_2(x+y)$ 个线段。分别对 $(s_x,s_y),(t_x,t_y)$ 执行这些操作，直到他们的横坐标或者列坐标到达了 $0$ 。

考虑最后一步。事实上我们要考虑他们会不会在 $(0,0)$ 相遇，而这取决于他们是否在同一行或者同一列上了。这部分只需要判断一下，~~留给读者自几处理~~。

那么最后线段总数应该是 $\log_2v$ 级别的（ $v$ 是值域）。对于每个炸弹，枚举所有线段，判断这个炸弹是否在这条线段上。总复杂度 $\mathcal O(n\log v)$ 。由于不像题解中用到比较麻烦的递归，所以速度飞起，拿到了赛时最块。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN =2e5+3,MAXM=500+3;
i64 n,X[MAXN],Y[MAXN],s1,s2,t1,t2,ans;
i64 A[MAXM],B[MAXM],C[MAXM],p;
i64 P[MAXM],Q[MAXM],R[MAXM],q;
void del(i64 &x,i64 &y){
    while(x!=0&&y!=0){
        if(!((x-1)&y)){i64 t=y&-y,l=x&(t-1); A[++p]=y,B[p]=x-l,C[p]=x,x-=l,ans+=l;}
        else          {i64 t=x&-x,l=y&(t-1); P[++q]=x,Q[q]=y-l,R[q]=y,y-=l,ans+=l;}
    }
}
i64 qread(){
    i64 w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    n=qread(); up(1,n,i) X[i]=qread(),Y[i]=qread();
    s1=qread(),s2=qread(),t1=qread(),t2=qread();
    up(1,60,i){
        i64 l=1ll<<i,a1=s1/l,a2=s2/l,b1=t1/l,b2=t2/l,p1,p2;
        if(a1==b1&&a2==b2){
            p1=a1*l,p2=a2*l,s1-=p1,s2-=p2,t1-=p1,t2-=p2;
            up(1,n,j) X[j]-=p1,Y[j]-=p2; break;
        }
    }
    del(s1,s2),del(t1,t2);
    printf("%lld\n",ans+llabs(s1-t1)+llabs(s2-t2));
    P[++q]=min(s1,t1),Q[q]=min(s2,t2),R[q]=max(s2,t2);
    A[++p]=min(s2,t2),B[p]=min(s1,t1),C[p]=max(s1,t1);
    up(1,n,i){
        bool f=0;
        up(1,p,j) if(Y[i]==A[j]&&X[i]>=B[j]&&X[i]<=C[j]) f=true;
        up(1,q,j) if(X[i]==P[j]&&Y[i]>=Q[j]&&Y[i]<=R[j]) f=true;
        putchar(f?'1':'0');
    }
    return 0;
}
```

---

