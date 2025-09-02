# 「MCOI-08 / AC6-M12」Weapons of Mass Destruction

## 题目背景

Garuda Team, I've got some good news. 

The chemical agent used as a catalyst for their WMD is being transported to our shores from the Estovakian mainland. 

This catalyst has already been carried into the outskirts of Gracemeria. 

As a measure of caution against any attempts to destroy it, it has been concealed at Fort Norton in Gracemeria's north. 

If we start advancing again, the enemy will most likely bring the catalyst into Gracemeria at a faster pace. 

If in fact weapons of mass destruction are used on the population of Gracemeria, the resulting devastation can't be expressed in enough words. 

It will lead to unspeakable tragedies. 

We've used this intelligence to come up with a solid proposal on how to prevent this scorched earth policy from being executed in our capital.

Just a minute ago, we received a letter of approval for our prevention plan from the Joint Chiefs of Staff. 

The proposal we put on the table for our scorched earth prevention policy is really quite simple. 

While the enemy transport unit is stationed at Fort Norton, **we'll ambush them.** 

We like to call it our tactic for pre-emptive victory. 

The enemy has loaded this catalyst into their transport vehicles and is able to send them into Gracemeria at any time. 

This plan will be carried out by a handful of our top pilots under absolute secrecy. 

**Fly through Fort Norton's canyon at an extremely low altitude to avoid radar detection, and take out those transport vehicles.** 

We've determined that a high-risk mission of this magnitude could not be executed by anyone other than Garuda Team. 

We're counting on a flawless execution here.

$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 12} \\\Large\text{Weapons of Mass Destruction}\\\tiny -\textit{ Boiling Point }-$$

![](https://cdn.luogu.com.cn/upload/image_hosting/3e1iqxjw.png)

## 题目描述

为了摧毁敌方装载有 WMD 催化剂的车队，你需要在超低空穿过 Fort Norton 的峡谷以接近他们。

Fort Norton 抽象为**平面上两个关于 $y$（$y\in[0,10^7]$）的线性分段函数** $A(y):y\mapsto x$ 以及 $B(y):y\mapsto x$，其中对于任意实数 $y\in [0,10^7]$，**满足 $A(y) \le B(y)$**。

你和你的 F-15E 抽象为一质点，**初始位置是 $(X_1,0)$**，保证 $A(0)\leq X_1\leq B(0)$；**同时具有初速度 $(v_0,\theta_0)$，表示初速的大小和方向**。

为了避免敌方发现，你不能大功率开动发动机。你的动力刚好足够在保持平飞的时候保持匀速。

当然你可以转向。由于你是 Ace Combat 的主角，你的转向全部用 PSM 完成。具体来说，你的飞行轨迹应为一条由若干线段组成的折线。但是在转向中会受到阻力。**如果方向改变后的角与改变前的角的差的绝对值为 $\alpha$，则速度大小会减小 $\alpha$**。如果你不改变方向，那么你会一直做匀速直线运动。

由于 Ghost Eye 很着急完成任务，所以**你的 $y$ 坐标必须随时间递增**。

同时，你需要保证在任意时刻，你所在的位置 $(x,y)$ 满足 $A(y)\le x\le B(y)$。

PSM 转向的过载很大，因此你需要保证**转向次数不超过 $\bf 3\times 10^6$**。~~否则你就会像 Prez 一样 g-LOC 并一头栽在仪表盘上。~~

求任何一个转向方案，使得你运动到 $(X_2,10^7)$ 上（**即，速度不能在运动过程中变为 $\bf0$ 或负数**），同时转向次数不超过 $3\times 10^6$。类似的，保证 $A(10^7)\leq X_2\leq B(10^7)$。

## 说明/提示

样例解释（缩小 $10^6$ 倍）：

![](https://cdn.luogu.com.cn/upload/image_hosting/5g98x901.png)

**注意质点在运动过程中可以碰到边界，也可以沿着边界运动一段。**

---

对于 $100\%$ 的数据，保证 $2\leq n,m\leq 10^6$，$0\leq x,y,p,q\leq 10^7$，$x_1\leq X_1\leq p_1$，$x_n\leq X_2\leq p_m$，$0\leq \theta_0<\pi$，$0\leq v_0\leq 10^9$。

对于 $100\%$ 的数据，实数精度不超过 $12$ 位。

对于 $100\%$ 的数据，**保 证 有 解**。


- Subtask 1（3 pts）：$n,m\leq 6$；$v_0\ge 50$。
- Subtask 2（8 pts）：$n,m\leq 6$。
- Subtask 3（17 pts）：$n,m\leq 200$。
- Subtask 4（13 pts）：$n,m\leq 1500$。
- Subtask 5（17 pts）：$n,m\leq 5000$。
- Subtask 6（19 pts）：$n,m\leq 10^5$。
- Subtask 7（23 pts）：无特殊限制。

**请注意浮点数输出效率。**

---

idea：Sol1，solution：Sol1 & w33z8kqrqk8zzzx33，code：Sol1，data：w33z8kqrqk8zzzx33

## 样例 #1

### 输入

```
5 4 4000000 9000000 13 0
3000000 0
1000000 1000000
2000000 4000000
6000000 8000000
7000000 10000000
5000000 0
4000000 2000000
6000000 6000000
10000000 10000000```

### 输出

```
1
4
4000000.0000000000 0.0000000000
3000000.0000000000 2000000.0000000000
4000000.0000000000 6000000.0000000000
9000000.0000000000 10000000.0000000000```

# 题解

## 作者：鏡音リン (赞：4)

输出任意解是骗人的。我们直接把这题当最优化题，求出最优解，也就是转向角度最小的解。它是唯一的。

为了方便处理，出口位于终点左侧的部分一并算作左边界，右边界同理。

定义：对于合法范围内一点 $O$，如果存在点 $P,Q$ 使得：

- $O,P,Q$ 三点共线，且 $P$ 位于中间。
- $Q$ 的 $y$ 坐标大于 $O$。
- $P,Q$ 分别位于两侧的边界上。
- 线段 $OQ$ 完全位于合法范围内。

那么称 $P$ 为 $O$ 的尖点。

对于任意 $O$，我们可以用这样的方式找到 $O$ 的尖点。考虑从 $O$ 发射一道激光，从正左方向扫到正右方向。这个过程中，最开始激光照在左侧的墙上，一定有一个分割点，过了这个点激光就照在右侧的墙上。那么这个分割点激光相当于同时照在了两侧的墙上，两侧的墙各有一半的光点。这两个光点所在的位置就是 $P$ 和 $Q$，近的那个是 $P$，它就是尖点。如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/l4jg100p.png)

在一些极端情况下，在这个分割点的位置激光可能正好贴着一侧的墙壁，这时这一段墙壁上的所有点都可以是 $P$。我们可以人为地规定最远的那个 $P$ 是真正的 $P$。这样，**尖点有且只有一个**。而且过了 $P$ 之后，$P$ 所在的墙壁一定会向外拐，所以 $P$ 一定是”尖“的，所以它**一定是边界的顶点或者终点**。

下面放上最重要的结论：**从 $O$ 开始到终点的最优路径必然经过 $O$ 的尖点**。 

考虑从 $O$ 开始到终点的路径一定穿过了线段 $PQ$，记穿过的点叫做 $R$。反证法，如果一条路径不过 $P$，那么 $O$ 到 $R$ 这一段一定不是线段 $OR$。考虑直接把这一段改成过 $P$ 的线段 $OR$，经过一些简单证明发现答案一定变优了（根据某定理，一定有一个时刻方向和线段 $PQ$ 相同，所以直接走这条线段是转向角度最小的）。因此不过 $P$ 的一定不是最优的。具体如下图所示，我们要把蓝线改成线段 $OR$。

![](https://cdn.luogu.com.cn/upload/image_hosting/d9p5hume.png)

所以我们的算法就是，从起点开始，不断找到当前点的尖点，然后跳到那里，直到跳到终点（这时 $P,Q$ 和终点三点重合），找到的一定是最优路径。问题转化成了如何找到尖点。上述证明中，发射激光的那个方法其实就是找尖点的一种方式，不过不太好实现。

可以从前往后扫过去，并且模拟在 $O$ 点的视野，维护左墙在视野中最靠右的点和右墙视野中最靠左的点，一旦这两个点中间的缝隙消失就说明你找到了尖点。单次复杂度 $O(n)$，总复杂度最坏 $O(n^2)$。

但是数据是随的，这玩意 AC 了。期望复杂度多少我也不知道，反正能过。

正经做法：我们刚才维护的是两个点，把它们改成两个单调栈，维护两侧的凸包，也就是说，单调栈里每个元素都是它下面那个点视角最靠边的点，而栈底是当前点视角最靠边的点。其实就是凸包。

由于找到尖点之后，是把栈底那个点弹出来跳到那里（所以这实际上是个双端队列），栈里剩下的点还能接着用。这样每个点只会被扫一次，总复杂度 $O(n)$。


---

## 作者：Sol1 (赞：3)

似乎很多人找我反映这题看不懂题解，我来写一个我的理解方式，希望有一点帮助。

首先显然这题是让你求转向角度最小的解。（这里出成任意解是因为感觉这样更自然一点，毕竟背景是规划飞行路线，而要求这个路线的最终速度尽量大又好像不太合理。不过这样确实有点无意义干扰选手，我紫菜。）

然后有个结论。如果当前点是 $O$，那么从这个点开始，下一次变向的位置 $P$ 一定满足 $OP$ 不与分段函数相交，并且 $OP$ 延长线上离 $O$ 最近的与分段函数的交点与 $P$ 不在同一个分段函数上。

证明可以看另一篇题解。感性理解就是如果再往外的话肯定有调整的空间。

那么我们考虑怎么维护这个最远的线段端点。

考虑直接把视野维护出来。具体来说，沿 $y$ 轴进行扫描线，维护这样一个结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/vkjuwc1p.png)

（有个地方画的不太清楚，B5 在 A6-B6 连线下方）

当然实际上 A1、B1 上面不可能没有点，但是因为在扫描线范围内还没有看到那个点，我们姑且暂时算它不存在。

然后考虑加入一个点。我们需要执行两件事情：

1. 求出这个点在最优路径中的前驱；
1. 更新扫描线结构。

这里感觉比较难说清楚，可以结合下图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/7swxyrjk.png)


我们在 $B$ 里面增加了一个点 B0。此时我们把扫描线结构里面保存的若干个点从右边开始弹出，直到当前点满足上面对 $P$ 点的定义为止。图中用灰色线标明被弹出的点对应的线。然后，在 B0 右侧的所有点对应的 $P$ 都是 B0。当然如果是在 A 上面增加一个点就是左侧。

同时由图可以直观看出这个点的前驱就是它弹到哪里停下了。显然它无法把栈弹空（因为如果弹空了必定是由于两个分段函数交在一起）。

这个结构可以用双端队列维护，最后暴力跳前驱输出答案即可。复杂度线性。

可以结合下面的核心代码理解。

```cpp
inline void Read() {
	cin >> n >> m;
	cin >> p[0].x >> p[n + m + 1].x >> v0 >> a0;
	for (int i = 1;i <= n;i++) {
		int tx, ty; cin >> tx >> ty;
		p[i].x = tx; p[i].y = ty;
	}
	for (int i = 1;i <= m;i++) {
		int tx, ty; cin >> tx >> ty;
		p[i + n].x = tx; p[i + n].y = ty; p[i + n].type = 1;
	}
	p[n + m + 1].y = 1e7;
}

inline Vec Link(int u, int v) {
	return p[max(u, v)] - p[min(u, v)];
}

inline void Solve() {
	qhd = qtl = N + 3;
	que[qtl++] = 0;
	for (int i = 1;i <= n + m + 1;i++) {
		if (!p[i].type) {
			while (qhd < qtl - 1 && Link(i, que[qhd]).cosAng() > Link(que[qhd], que[qhd + 1]).cosAng()) qhd++; //cosAng 是辐角的余弦值，这里因为余弦函数在 [0,pi] 上递减所以不等号是反的。
			fa[i] = que[qhd];
			que[--qhd] = i;
		} else {
			while (qhd < qtl - 1
				 && Link(i, que[qtl - 1]).cosAng() < Link(que[qtl - 1], que[qtl - 2]).cosAng()) qtl--;
			fa[i] = que[qtl - 1];
			que[qtl++] = i;
		}
	}
	int u = n + m + 1; stk[++stktop] = p[u];
	while (fa[u]) {
		u = fa[u];
		stk[++stktop] = p[u];
	}
	stk[++stktop] = p[0];
	cout << fixed << setprecision(2) << "1\n" << stktop << "\n";
	for (int i = stktop;i >= 1;i--) cout << (int)stk[i].x << ".00 " << (int)stk[i].y << ".00\n";
}
```









---

