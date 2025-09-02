# [NEERC 2015] Landscape Improved

## 题目描述

路易斯 $L$ Le Roi-Univers 下令改善从皇宫看到的景观。陛下希望看到一座高山。  

首席景观经理打算为路易斯建造一座山。他将景观表示为单位方格网格上的平面图。一些方格已经被岩石填满，而其他方格是空的。这大大简化了设计。单位方格足够小，从皇宫看去，景观似乎是平滑的。  

首席景观经理有一个景观计划——每个单位宽度的所有岩石填充列的高度。他打算在现有景观上最多添加 $n$ 个单位方格的石头，以建造一座尽可能高的山峰。不幸的是，石头堆非常不稳定。一个单位方格的石头只能精确地放在其他填充的石头或岩石方格的正上方，而且其左下方和右下方的方格应该已经被填满。  

现有景观  

改进后的景观  

你的任务是帮助首席景观经理确定他能建造的最高山峰的最大高度。

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
8 4
3
4
2
1
3
3
2
4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 100
3
3
3
```

### 输出

```
4
```

# 题解

## 作者：_wkjzyc (赞：5)

先考虑“平坦”且不限次数时的最高高度。此时，除左右端点外皆可+1，相当于通过 $w-2$ 次操作使其变为长 $w-2$ ，高度 $1$ 的新区间。这是一个子问题。最后，得到的序列形如

$$1,2\dots h_{max}-1,h_{max},h_{max}-1\dots 2,1$$

可以证明这是+1次数最少的方案。而在“不平坦”的序列中，可选一段区间“填平”之后处理。于是得出性质：

- 对于最优解下的操作方案，其最高点向左右皆以 $1$ 每下标的速度下降。

- 若下降时被“阻挡”，之后无需+1操作。

- 若始终不被阻挡，则高度无法达到。

![](https://cdn.luogu.com.cn/upload/image_hosting/xn22ymrs.png)

易知最高点单调。对于每个位置二分高度，判断能否达到，以及可达到时所需最少的+1次数。所有位置上二分结果的最大值就是答案。

### 判断

“被阻挡”相当于此时的蓝色高度低于黄色（原序列）高度。

记最高点 $p$ 高度 $m$ ，若在 $[l,q]$ 区间内（最高点左侧）被阻挡，则可以表达为

$$\exists i\in[l,p]\,,s.t.\quad h_i\geq m-(p-i)$$

等价于
$$\max_{i=l}^p\{h_i-i\}\geq m-p$$

左边RMQ问题可以用st表维护，判断时二分左端点即可。最高点右侧同理。

### 代码

```cpp

#include<iostream>
#include<cstdio>
#define int long long
using namespace std;

const int MAXN=1e5+5;
int n,ans,s[MAXN];
int w,h[MAXN];

namespace ST { //预处理
	int lg2[MAXN],l[MAXN][20],r[MAXN][20];
	int QueryL(int i,int j,int num) {
		int tmp=lg2[j-i+1];
		return max(l[i][tmp],l[j-(1<<tmp)+1][tmp])+j-num;
	}
	int QueryR(int i,int j,int num) {
		int tmp=lg2[j-i+1];
		return max(r[i][tmp],r[j-(1<<tmp)+1][tmp])-i-num;
	}
	void Init() {
		for(int i=2;i<=w;i++) lg2[i]=lg2[i-1]+(2<<lg2[i-1]==i);
		for(int i=1;i<=w;i++) l[i][0]=h[i]-i,r[i][0]=h[i]+i;
		for(int i=1;(1<<i)<=w;i++) for(int j=1;j+(1<<i)-1<=w;j++) {
			l[j][i]=max(l[j][i-1],l[j+(1<<(i-1))][i-1]);
			r[j][i]=max(r[j][i-1],r[j+(1<<(i-1))][i-1]);
		}
	}
}

bool Check(int p,int m) { //第二次 二分下标
	int _l,_r,l,r;
	for(l=1,r=p;l<r;) {
		int mid=l+r+1>>1;
		if(ST::QueryL(mid,p,m)>=0) l=mid;
		else r=mid-1;
	}
	if(ST::QueryL(l,p,m)<0) return 0; //必须“被阻挡”
	_l=l;
	for(l=p,r=w;l<r;) {
		int mid=l+r>>1;
		if(ST::QueryR(p,mid,m)>=0) r=mid;
		else l=mid+1;
	}
	if(ST::QueryR(p,l,m)<0) return 0; //必须“被阻挡”
	_r=l;
	if((_r-p)*(2*m-_r+p+1)/2+(p-1-_l)*(2*m-p+_l)/2-s[_r-1]+s[_l]>n) return 0; //操作不多于n次
	return 1;
}

signed main() {
	scanf("%lld%lld",&w,&n);
	for(int i=1;i<=w;i++) scanf("%lld",&h[i]),s[i]=s[i-1]+h[i];
	ST::Init();
	for(int i=1;i<=w;i++) {
		int l=h[i],r=h[i]+n;
		while(l<r) { //第一次 二分高度
			int mid=l+r+1>>1;
			if(Check(i,mid)) l=mid;
			else r=mid-1;
		}
		ans=max(ans,l);
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：YangHHao (赞：2)

题意见原题面 [P6984](https://www.luogu.com.cn/problem/P6984)

思路以及原题条件的转化其它题解已经讲得很详细很清楚了，这里我就重点分享下码量较小且复杂度更优的做法。

题目可以转化为对于每个点 $i$，目标高度为 $x$，找出最接近的 $l$ 与 $r$，使得 $h_l-l \ge x-i$，$h_r+r \ge x+i$。

其它题解的做法是 ST表 或 线段树，复杂度 $\mathcal O(w \log w \log h)$，这里我提供两个 $\mathcal O(w \log h)$ 的方法。

### Method One

这里我们不在每个位置二分答案，而是整体二分答案后判断是否可行。

我们先从求最近的 $l$ 入手，之后 $r$ 同理求得即可。

对于位置 $i$，我们发现 $x-i$ 递减，要求最接近的 $l < r$ 使 $h_l-l \ge x-i$，可以考虑使用单调队列。

在第 $i$ 位置判断结束后，从队列末尾弹出若干元素后插入 $h_i-i$，使队列单调递减，这时只需从队列头部弹出元素并判断，再根据 $x-i$ 的单调性传递即可。

[Code of Method One](https://www.luogu.com.cn/paste/x90njkm2)

### Method Two

在写代码的过程中，我们发现单调队列优美的下标单调的性质并没有用上，于是开始思考是否存在更简单的写法。

变形方程，得 $i \ge x+l-h_l$，发现对于一段持续至末尾的区间内都能用上 $l$。

于是，方法呼之即出：
直接赋值，线性求前缀最大值 / 最小值。

[Code of Method Two](https://www.luogu.com.cn/paste/5lggl700)

### 总结

本题复杂度优化的核心在于常识整体进行值域二分，发现所求值的单调性。

在做题时，好好思考不同部分的进行顺序对复杂度的影响，对 ~~卡常丢分的避免~~ 能力的提高大有裨益。



---

## 作者：bluewindde (赞：1)

~~其实英文版的题意更好理解，所以翻译了什么~~

题意：给定序列 $\{a_w\}$，表示位置 $i$ 有 $a_i$ 块石头。进行至多 $n$ 次操作，每次操作选择一个位置，满足其下方、左下方、右下方都有石头，并把这个位置放上石头，问石头最高可以堆多高？

这是 $a=\{3,4,2,1,3,2,4,4,5,8,6,4\}$ 时的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/x8r02z1y.png)

石头不是没有上限的，最高堆到下图所示位置，即切每一个位置的斜率为 $1$ 的直线和斜率为 $-1$ 的直线的最高的交点。

容易发现，对于每一个位置作为最高点，它的高度不会大于与 $l_1$ 或 $m_1$ 的交点的高度。

考虑枚举每一个位置作为最高点。因为存在最高操作次数的限制，不一定每个点都能取到最大答案，那么再考虑对于每一个最高点二分其高度。

![](https://cdn.luogu.com.cn/upload/image_hosting/e9ajlsmv.png)

如图是不限制操作次数时可以达到的最高点，发现对于低于 $l_1,m_1$ 两条直线的点 $Q$，过 $Q$ 的斜率为 $\pm1$ 的直线一定会与一些石头产生交点。（这是显然的，因为这些直线的截距一定小于 $l_1,m_1$ 的）

所以，先进行坐标系的转换，令 $g_i=a_i-i,h_i=a_i+i$，代表着过点 $(i,a_i)$ 的斜率分别为 $\pm1$ 的直线的截距。

设当前二分到位置 $x$，高度为 $height$，$x$ 左边第一个 $g_i\ge g_x$ 的位置为 $qg$，$x$ 右边第一个 $h_i\ge h_x$ 的位置为 $qh$。（这可以用二分和 ST 表处理，千万不要用线段树！）

接下来考虑检验高度是否合法。

若不存在 $qg$ 或 $qh$，那么这个 $height$ 不合法。（这等价于它们没有与石头产生交点）

可以用前缀和 $f$ 算出区间 $(qg,qh)$ 已经填入的石头数量 $tot=f_{qh-1}-f{qg}$。用梯形面积公式算出区间全部填满应该有的石头数量 $need=\dfrac{1}{2}(qh-x)\cdot(2\cdot height-qh+x+1)+\dfrac{1}{2}(x-1-qg)\cdot(2\cdot height-x+qg)$。如果 $need-tot>n$，即需要填入的石头数量大于最大操作数量，则这个 $height$ 不合法。

排除掉两种不合法情况，剩下情况一定合法。

[Code.](https://www.luogu.com.cn/paste/rflgnhjo)

---

## 作者：zhylj (赞：0)

考虑枚举贡献最高点的位置 $i\in(0,w)$。

二分答案 $x$，问题变成如何 Check 这个点的高度是否能够为 $x$。

注意到我们的修改方案必然是从位置 $i$ 开始，两边每次减 $1$，直到接触原先就存在的 $h_j$，我们需要找到左边右边第一个 $x-|i-j|\le h_j$ 的位置，讨论一下左右、移个项不难发现我们只需要维护出 $h_j-j$ 和 $h_j+j$ 的区间最大值即可二分找到对应点。

可以使用线段树上二分 / ST 表维护，时间复杂度 $\mathcal O(w\log w\log n)$。

```cpp
const int N = 1e5 + 5, INF = 0x7f7f7f7f;

int n, h[N];
ll m, s[N];

#define mx_a(o) tr[o].mx_a
#define mx_b(o) tr[o].mx_b

struct Node {
	int mx_a, mx_b;
	Node() { mx_a = mx_b = -INF; }
} tr[N << 3];
void Update(int o) {
	mx_a(o) = std::max(mx_a(o << 1), mx_a(o << 1 | 1));
	mx_b(o) = std::max(mx_b(o << 1), mx_b(o << 1 | 1));
}
void Modify(int o, int l, int r, int p, int v_a, int v_b) {
	if(l == r) {
		mx_a(o) = v_a;
		mx_b(o) = v_b;
	} else {
		int mid = (l + r) >> 1;
		if(p <= mid) Modify(o << 1, l, mid, p, v_a, v_b);
		else Modify(o << 1 | 1, mid + 1, r, p, v_a, v_b);
		Update(o);
	}
}
int QueryA(int o, int l, int r, ll v) {
	if(v > mx_a(o)) return 0;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(v <= mx_a(o << 1 | 1))
		return QueryA(o << 1 | 1, mid + 1, r, v);
	else return QueryA(o << 1, l, mid, v);
}
int QueryB(int o, int l, int r, ll v) {
	if(v > mx_b(o)) return r + 1;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(v <= mx_b(o << 1))
		return QueryB(o << 1, l, mid, v);
	else return QueryB(o << 1 | 1, mid + 1, r, v);
}
ll Check(int i, ll mid) {
	ll tot = 0;
	int L = QueryA(1, 1, n, mid - i),
		R = QueryB(1, 1, n, mid + i);
	if(L == 0 || R == n + 1) return INF;
	++L; --R;
	tot = (mid + mid - (i - L)) * (i - L + 1) / 2 +
		(mid + mid - (R - i)) * (R - i + 1) / 2 - mid;
	tot -= s[R] - s[L - 1];
	return tot;
}
ll GetPosAns(int i) {
	ll l = h[i], r = 2e9;
	while(l < r) {
		ll mid = (l + r + 1) >> 1;
		if(Check(i, mid) <= m) l = mid;
		else r = mid - 1;
	}
	return l;
}

int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", h + i);
		s[i] = s[i - 1] + h[i];
	}
	for(int i = 1; i <= n; ++i)
		Modify(1, 1, n, i, -INF, h[i] + i);
	ll ans = 0;
	for(int i = 1; i <= n; ++i) {
		ans = std::max(ans, GetPosAns(i));
		Modify(1, 1, n, i, h[i] - i, -INF);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

