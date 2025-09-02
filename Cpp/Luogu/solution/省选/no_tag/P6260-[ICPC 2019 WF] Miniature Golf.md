# [ICPC 2019 WF] Miniature Golf

## 题目描述

几个朋友玩了一场小型的高尔夫。这种小型的高尔夫是由若干个洞组成的。每个玩家轮流玩这个游戏，不停地击球直到球落到每个洞里。玩家在一个洞上的得分是他击球的次数。为了防止捣乱的玩家把游戏速度放慢太多，游戏规则中也会给一个上限$l$（一个正整数）来控制分数：如果一个玩家在一个洞上已经击球$l$次，但是球还没有落到洞里，那么这个玩家在这个洞上的得分就是$l$，并且这个玩家的回合就结束了。一个玩家的总得分就是他在各个洞上的得分之和。自然地，在这个游戏中，分越低越好。

但是有一个问题：没有玩家记得$l$的值。玩家们决定在玩的时候不设置$l$的值，允许每个玩家不断击球，直到球掉到洞里。玩完游戏，他们准备设置$l$的值，并更改那些在洞上的分数大于$l$的值。

游戏结束了，但他们还没有设置$l$。他们想知道自己的最佳排名是什么。一个人的排名是在所有人中，得分比这个人低或和这个人相等的人数（包含自己）。比如，当五个人的得分分别是 $3,5,5,4,3$，那么他们的排名就是 $2,5,5,3,2$。

给你每个玩家在每个洞上的得分，为每一个玩家求出最小的可能的排名。

## 说明/提示

来源：ICPC World Finals 2019 Problem J 

题目名称：Miniature Golf

## 样例 #1

### 输入

```
3 3
2 2 2
4 2 1
4 4 1```

### 输出

```
1
2
2```

## 样例 #2

### 输入

```
6 4
3 1 2 2
4 3 2 2
6 6 3 2
7 3 4 3
3 4 2 4
2 3 3 5```

### 输出

```
1
2
5
5
4
3
```

# 题解

## 作者：zhylj (赞：4)

记 $a_{i,j}$ 是第 $i$ 个人的得分。

考虑 $l$ 由 $0$ 到 $10^9$ 每增加 $1$ 都会导致其得分增加 $\sum_{j=1}^h[a_{i,j} > l]$。故而如果用所有 $a_{i,j}$ 把数轴划分为若干个区间，在一个区间内某个人的得分是一条直线，而由于 $\sum_{j=1}^h[a_{i,j} > l]$ 随 $l$ 不减，故某个人得分关于 $l$ 的函数是一个凸壳。

由于这些凸壳的一个交点对应着一次排名的变化，我们考虑关注这些凸壳的交点。一条直线至多交一个凸壳于 $2$ 点，而一共有 $p\cdot h$ 条直线，$p$ 个凸壳，故至多有 $p^2h$ 个交点。

考虑每次在拐点处处理新增直线对旧的直线（也就是拐点在这条直线之前的直线）的影响，然后对模拟直线之间排名上下变化的过程就好了。

由于拐点处比较烦，所以我在拐点处暴力算排名，然后再模拟直线的排名变化。

由于要排序，所以时间复杂度是 $\mathcal O(p^2h\log ph)$ 的。

```cpp
typedef std::pair <int, int> pii;
typedef std::pair <int, pii> pipii;
const int kP = 5e2 + 5, kH = 50 + 5, kN = kP * kP * kH, kInf = 0x3f3f3f3f;
const ll kMod = 998244353, kInfLL = 0x3f3f3f3f3f3f3f3fLL;

int p, h, ans[kP]; ll A[kP][kH], cur_k[kP], cur_b[kP];

int chg_pos[kN], cnt_cp = 0, cnt_ip = 0; bool vis[kP]; pipii intrs_pos[kN];
ll Intsec(int i, int j) {
	ll dtk = cur_k[i] - cur_k[j], dtb = cur_b[j] - cur_b[i];
	if(!dtk) return -1;
	return (ll)ceil(dtb / dtk);
}
void GetIntrsPos() {
	for(int i = 1; i <= cnt_cp; ++i) {
		memset(vis, false, sizeof(vis));
		int l = chg_pos[i];
		for(int j = 1; j <= p; ++j) {
			while(cur_k[j] && A[j][h - cur_k[j] + 1] <= l) {
				vis[j] = true; --cur_k[j];
				cur_b[j] += l;
			}
		}
		for(int j = 1; j <= p; ++j) if(vis[j]) {
			for(int k = 1; k <= p; ++k) if(j != k) {
				ll x = Intsec(j, k);
				if(x >= A[j][h - cur_k[j] + 1] || x < A[j][h - cur_k[j]] ||
					x >= A[k][h - cur_k[k] + 1] || x < A[k][h - cur_k[k]])
					continue;
				intrs_pos[++cnt_ip] = mkp(
					x, cur_k[j] < cur_k[k] ? mkp(j, k) : mkp(k, j)
				);
			}
		}
	}
	std::sort(intrs_pos + 1, intrs_pos + cnt_ip + 1);
	cnt_ip = std::unique(intrs_pos + 1, intrs_pos + cnt_ip + 1) - intrs_pos - 1;
}

int rk[kP]; ll pts[kP];
void Calc() {
	memset(cur_b, 0, sizeof(cur_b));
	for(int i = 1; i <= p; ++i) cur_k[i] = h;
	for(int i = 1, ptr = 0; i <= cnt_cp; ++i) {
		int o_l = chg_pos[i];
		for(int j = 1; j <= p; ++j) {
			while(cur_k[j] && A[j][h - cur_k[j] + 1] <= o_l) {
				--cur_k[j];
				cur_b[j] += o_l;
			}
		}
		for(int j = 1; j <= p; ++j)
			pts[j] = cur_k[j] * o_l + cur_b[j];
		std::sort(pts + 1, pts + p + 1);
		for(int j = 1; j <= p; ++j) {
			ll tmp_pts = cur_k[j] * o_l + cur_b[j];
			rk[j] = std::upper_bound(pts + 1, pts + p + 1, tmp_pts) - pts - 1;
			ans[j] = std::min(ans[j], rk[j]);
		}
		++o_l;
		if(o_l > chg_pos[i + 1]) continue;
		for(int j = 1; j <= p; ++j)
			pts[j] = cur_k[j] * o_l + cur_b[j];
		std::sort(pts + 1, pts + p + 1);
		for(int j = 1; j <= p; ++j) {
			ll tmp_pts = cur_k[j] * o_l + cur_b[j];
			rk[j] = std::upper_bound(pts + 1, pts + p + 1, tmp_pts) - pts - 1;
			ans[j] = std::min(ans[j], rk[j]);
		}
		for(; ptr <= cnt_ip && intrs_pos[ptr].fi <= chg_pos[i + 1]; ++ptr) {
			pipii cur = intrs_pos[ptr]; int u = cur.se.fi, v = cur.se.se;
			if(cur.fi <= o_l) continue;
			--rk[u]; ++rk[v];
			ans[u] = std::min(ans[u], rk[u]);
		}
	}
}

int main() { 
	memset(ans, 0x3f, sizeof(ans));
	rd(p, h);
	for(int i = 1; i <= p; ++i) {
		A[i][h + 1] = kInf;
		for(int j = 1; j <= h; ++j) {
			rd(A[i][j]);
			chg_pos[++cnt_cp] = A[i][j];
		}
		std::sort(A[i] + 1, A[i] + h + 1);
		cur_k[i] = h;
	}
	chg_pos[++cnt_cp] = 1e9; chg_pos[++cnt_cp] = 0;
	std::sort(chg_pos + 1, chg_pos + cnt_cp + 1);
	cnt_cp = std::unique(chg_pos + 1, chg_pos + cnt_cp + 1) - chg_pos - 1;
	GetIntrsPos(); Calc();
	for(int i = 1; i <= p; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：CashCollectFactory (赞：3)

### 题目大意

有 $p$ 个人一起去打高尔夫，一共有 $h$ 局，每局每人各有一个杆数。打完之后，他们想把杆数设一个最大值来调整得分，如果某一局杆数超过最大值就把杆数改成这个最大值。问在不同的杆数最大值下，每个人的**最高排名分别是多少**。

### 数学解法
对于每个人的**总杆数关于杆数限制**的函数，是一个分段线性函数，如下图所示。

当限制超过他的最大杆数，直线是平的，前面的线段的斜率就是这个人有多少杆的得分超过了这一个限制。

![函数图像](https://cdn.luogu.com.cn/upload/image_hosting/gi6tcu9e.png)

由此性质，我们不难想出如下做法：

首先，将每个人自己的分数从大到小排序，用两重循环求出每个人的最佳排名，外层循环每次处理一个人，内层循环遍历其他所有人。

对于内层循环，我们首先将两个人的分数从大到小排列，在头部加一个 $+∞$(得分的曲线只会在这些点改变)，作为待选的杆数限制。然后，对每一个限制，调整两人的得分，当且仅当调整前后两人的得分大小关系发生改变，说明两个人的排名发生了变化。

遍历完其他人后，首先可以知道在无限制的情况下的排名，再通过之前整理的排名变化情况，就可以得知在不同限制下的排名，从而得知最佳排名，于是本题就完成啦！

最后，算法的时间复杂度约为 $O(p \times h \times \log ph)$，就此达成本题目目前的最优解！

具体的实现细节见下方代码：

### 代码时间（~~码丑勿喷，我颜良文丑~~）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int P,H;
	while(cin >> P >> H) {
		vector<vector<int>> S(P, vector<int>(H));
		vector<int64_t> tot(P);
		for(int i = 0; i < P; i++) {
			for(int j = 0; j < H; j++) {
				cin >> S[i][j];
				tot[i] += S[i][j];
			}
			S[i].push_back(0); //设置一个最小的地板，在26行的循环递增条件用
			sort(S[i].begin(), S[i].end(), greater<int>());
		}
		for(int i = 0; i < P; i++) {
			vector<pair<int, int>> events; //pair中第一个int为取的lim,第二个表示取此lim时,排名需要如何变化
			int cur = 0;
			for (int j = 0; j < P; j++) {
				int64_t itot = tot[i], jtot = tot[j], lim = 1000000000;
				if (jtot <= itot) cur++;
				for (int ih = 0, jh = 0; ih < H || jh < H; S[i][ih] > S[j][jh] ? ih++ : jh++) {
					bool old = (jtot <= itot); //这里的条件比较巧妙，具体看下面
					int v = max(S[i][ih], S[j][jh]); //不断取ij的scores中较大者为lim,如果有重复,当两个都到达小值时才会进入下一lim
					itot -= (lim-v) * ih; jtot -= (lim-v) * jh; //对两者总score进行裁减
					lim = v;
					if (!old && jtot <= itot) {
						/*排名要+1，在前一lim需要jtot>itot（=不行，因为排名算的是小于等于自己分数的个数），当前lim jtot <= itot
						 *直线过（lim，tot）点，斜率是h，分别列出ij两直线的方程式，求出交点横坐标就是lim+(itot-jtot)/(jh-ih), 同时计算出的是double,需要向下取整(转int已经执行了)
						 *判断条件相当于if(orig_jtot>orig_itot && (jtot<itot || jtot==itot))*/
						events.emplace_back(lim+(itot-jtot)/(jh-ih), 1);
					} else if (old && jtot > itot) {
						/*排名要-1，在前一lim需要jtot<=itot，在当前lim jtot>itot，并且如果交点是整数,-1的效果要计入前一个点，所以会有jtot-itot-1
						 *判断条件相当于if((orig_jtot>orig_itot || orig_jtot==orig_itot) && jtot>itot)*/
						events.emplace_back(lim+(jtot-itot-1)/(ih-jh), -1);
					}
				}
			}
			sort(events.begin(), events.end(), greater<pair<int, int>>());
			int ret = cur;
			for (auto const& e : events) {cur += e.second; ret = min(ret, cur);}
			cout<<ret<<endl;
		}
	}
	return 0;
}

```

补充一句，本代码需要使用 C++11 以上版本才可以正常编译，只因里面用了“auto”这个新东西~

---

