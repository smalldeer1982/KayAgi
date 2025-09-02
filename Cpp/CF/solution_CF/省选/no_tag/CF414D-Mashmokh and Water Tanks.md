# Mashmokh and Water Tanks

## 题目描述

Mashmokh is playing a new game. In the beginning he has $ k $ liters of water and $ p $ coins. Additionally he has a rooted tree (an undirected connected acyclic graph) that consists of $ m $ vertices. Each vertex of the tree contains a water tank that is empty in the beginning.

The game begins with the fact that Mashmokh chooses some (no more than $ k $ ) of these tanks (except the root) and pours into each of them exactly $ 1 $ liter of water. Then the following process is performed until there is no water remained in tanks.

- The process consists of several steps.
- At the beginning of each step Mashmokh opens doors of all tanks. Then Mashmokh closes doors of some tanks (he is not allowed to close door of tank in the root) for the duration of this move. Let's denote the number of liters in some tank with closed door as $ w $ , Mashmokh pays $ w $ coins for the closing of that tank during this move.
- Let's denote by $ x_{1},x_{2},...,x_{m} $ as the list of vertices of the tree sorted (nondecreasing) by their depth. The vertices from this list should be considered one by one in the order. Firstly vertex $ x_{1} $ (which is the root itself) is emptied. Then for each vertex $ x_{i} $ $ (i&gt;1) $ , if its door is closed then skip the vertex else move all the water from the tank of vertex $ x_{i} $ to the tank of its father (even if the tank of the father is closed).

Suppose $ l $ moves were made until the tree became empty. Let's denote the amount of water inside the tank of the root after the $ i $ -th move by $ w_{i} $ then Mashmokh will win $ max(w_{1},w_{2},...,w_{l}) $ dollars. Mashmokh wanted to know what is the maximum amount of dollars he can win by playing the above game. He asked you to find this value for him.

## 说明/提示

The tree in the first sample is shown on the picture below. The black, red, blue colors correspond to vertices with 0, 1, 2 liters of water.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF414D/c32c25956aeb5f19835ae8010ab942b3e4600db9.png)One way to achieve the maximum amount of money is to put 1 liter of water in each of vertices 3 and 4. The beginning state is shown on the picture below.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF414D/0ece56653ffd25bc7155ae3d9fefd906a55801ad.png)Then in the first move Mashmokh will pay one token to close the door of the third vertex tank. The tree after the first move is shown on the picture below.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF414D/258bc0038f42a2b22caf648c306ac35f43192ac5.png)After the second move there are 2 liters of water in the root as shown on the picture below.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF414D/f9a31f68f8f511ebd76e9e0a46c30fc386393efb.png)

## 样例 #1

### 输入

```
10 2 1
1 2
1 3
3 4
3 5
2 6
6 8
6 7
9 8
8 10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 1000 1000
1 2
1 3
3 4
3 5
```

### 输出

```
4
```

# 题解

## 作者：Mas_Guo (赞：4)

参考[官方题解](https://codeforces.com/blog/entry/11470)，实现细节略有不同。

设点 $i$ 的深度为 $d[i]$。

可以发现能影响答案的是同时到达根的水的数量，因此我们应该尽量让水都在同一时刻到达根，即在它们到达根之前尽量让它们到达同一深度。两升水被放置的初始节点深度差越大，想要让它们到达同一深度的代价就越大，因此我们应该让初始放置水的节点彼此间深度差最小，也就是我们应该将它们放在按深度排序后都相邻的点上。

设深度为 $d$ 的点有 $c[d]$ 个放置了水，放置水的节点中深度最大的点的深度为 $D$。设我们选择的点按深度排序后编号从 $l$ 到 $r$，为了让放置水的点达到同一深度需要付出的代价是 $\sum_{i=l}^{r} (D - d[i])$（按点考虑），或 $\sum_{i=d[l]}^{D}(D-i) \cdot c[i]$（按深度考虑）。可以发现，当 $d[r]$ 变大的时候需要付出的代价也变大，而 $l$ 变大的时候付出的代价也变小，我们希望尽量把钱用完，但不能超过 $p$，所以可以用双指针处理，每次向右移动 $r$ 后移动 $l$。注意我们已选取放水的点不能超过 $k$ 个。

当 $d[r]$ 变大 $1$ 后多付出的代价是 $r - l$（从公式可以推出，也可以感性理解为之前的每升水都要被多停一次来等待多的这一升水），当 $l$ 变大 $1$ 后少付出的代价是 $d[r] - d[l]$（从公式可以推出，也可以感性理解为深度最小的那些水都需要被停止这么多次，我们少了一升需要被停止这么多次的水）。

代码：
```cpp
#include <algorithm>
#include <cstdio>

const int MAXM = 100000 + 5;

int head[MAXM], to[2 * MAXM], next[2 * MAXM], cnt;
int m, k, p, d[MAXM], count[MAXM], maxd = 2;

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int fa, int u) {
    d[u] = d[fa] + 1;
    count[d[u]]++;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa) continue;
        dfs(u, v);
    }
}

int main() {
    scanf("%d %d %d", &m, &k, &p);
    for (int i = 1, u, v; i < m; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(0, 1);
    std::sort(d + 1, d + m + 1);
    int l = 2, r = 2, ans = 1, cost = 0;
    // cost 为已经花费的代价
    while (l < m && r < m) { // 因为是先递增边界再更新答案，所以是小于
        r++;
        if (d[r] != d[r - 1]) {
            cost += r - l;
        }
        while (cost > p || r - l + 1 > k) {
            cost -= d[r] - d[l];
            ++l;
        }
        ans = std::max(ans, r - l + 1);
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：傅思维666 (赞：1)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11852367.html)

~~2019.11.13模拟赛T3 40分场~~

在此吹爆同届大佬**@iamrjj**，考场爆切黑题，简直是中国OI的先驱，IOI的未来！

（由于和我们考试的题面不一样，我简单概括一下题意：）

#### 题目大意

给一棵树，一开始$k$个人可以被放在树上除根节点之外的节点，但是每个节点只能放$1$个人。每一秒钟你可以往一些地方放路障拦住这里的所有人，花费的价值为当前点的人数。如果这个时刻这个点没有路障，这个点的所有人会向上爬一个点，这样的话，一些时刻会有人抵达根节点，现在需要你分配放路障的地方和时间，求所有时刻最多的抵达根节点的人数是多少。

#### 题解：

在考场上连暴力都不会写。所以我仔细观察了一下样例，我发现，如果通过技术手段把人都拦在根节点的儿子节点上，直到所有人都到达根节点的儿子节点们，这个时候同时放开拦截，这些人就会同时抵达终点。这种方法就是最优秀的（刨除其他的一切条件）

所以我就乱搞（骗分），如果$k<n$，输出$k$，否则输出$n-1$。成功40分。

#### 正经题解：

这回考虑其他的因素，我们发现最优的决策一定是越来越多的人都在到达根节点之前到达**同一深度**，同理，那么两个人一开始被放置的位置深度差越大，把一个人拦下使得另一个人追上他的难度（花费）就越大。所以我们要尽可能地让人们的初始深度差值最小。也就是说，我们要将其放在：**按深度排序后深度相邻的点上**。

那么我们把这些点按深度排序为$l-r$。假设深度为$depth$的点上有$cnt[depth]$个放上人。所有放人的节点中深度最大的为$D$。那么为了让他们达到统一深度，需要付出的钱是：
$$
\sum_{i=l}^{i=r}{(D-deep[i])}
$$
那么当$r$变大的时候代价也变大。$l$变大的时候代价会变小。为了控制这个$l-r$的范围，我们当然选用**双指针法**（尺取法）

关于尺取法和双指针，如有不太会的同学可以翻看蒟蒻的这篇博客：

[尺取法详解]( https://www.cnblogs.com/fusiwei/p/11313817.html )

AC代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;
int n,k,p;
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1];
int deep[maxn],cnt[maxn];
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int f)
{
	deep[x]=deep[f]+1;
	cnt[deep[x]]++;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)
			continue;
		dfs(y,x);
	}
}
int main()
{
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	sort(deep+1,deep+n+1);
	int l=2,r=2,ans=1,tmp=0;
	while(1)
	{
		if(l>=n || r>=n)
			break;
		r++;
		if(deep[r]!=deep[r-1])
			tmp+=(r-l);
		while(tmp>p || r-l+1>k)
		{
			tmp-=(deep[r]-deep[l]);
			l++;
		}
		ans=max(ans,(r-l+1));
	}
	printf("%d",ans);
	return 0;
}
```



---

