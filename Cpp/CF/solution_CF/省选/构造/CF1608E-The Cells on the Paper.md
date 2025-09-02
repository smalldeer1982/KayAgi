# The Cells on the Paper

## 题目描述

On an endless checkered sheet of paper, $ n $ cells are chosen and colored in three colors, where $ n $ is divisible by $ 3 $ . It turns out that there are exactly $ \frac{n}{3} $ marked cells of each of three colors!

Find the largest such $ k $ that it's possible to choose $ \frac{k}{3} $ cells of each color, remove all other marked cells, and then select three rectangles with sides parallel to the grid lines so that the following conditions hold:

- No two rectangles can intersect (but they can share a part of the boundary). In other words, the area of intersection of any two of these rectangles must be $ 0 $ .
- The $ i $ -th rectangle contains all the chosen cells of the $ i $ -th color and no chosen cells of other colors, for $ i = 1, 2, 3 $ .

## 说明/提示

In the first sample, it's possible to leave $ 6 $ cells with indexes $ 1, 5, 6, 7, 8, 9 $ .

In the second sample, it's possible to leave $ 3 $ cells with indexes $ 1, 2, 3 $ .

## 样例 #1

### 输入

```
9
2 3 1
4 1 2
2 1 3
3 4 1
5 3 2
4 4 3
2 4 1
5 2 2
3 5 3```

### 输出

```
6```

## 样例 #2

### 输入

```
3
1 1 1
2 2 2
3 3 3```

### 输出

```
3```

# 题解

## 作者：ran_qwq (赞：3)

看到“最大的 $k$”，先二分这个 $\dfrac k3$。

题目选三个互不相交的矩形，考虑让每个点都在某个矩形内，这样是最优的。

现在矩形的分布就只有这六种：

![](https://cdn.luogu.com.cn/upload/image_hosting/scv6vqgg.png)

其中每种的每个矩形的颜色可以任意排列，共 $6\times3!=36$ 种情况。分讨即可。

接下来我们看对于一种情况如何处理。

我们注意到，三个矩形中必有一个矩形在 $x$ 坐标意义上包含了所有点，或者在 $y$ 坐标意义上包含了所有点。

我们提前将点列存两份，一份按 $x$ 坐标排序，一份按 $y$ 坐标排序。二分时先扫一遍，使这个矩形包含 $\dfrac k3$ 个对应的颜色的点，并给另外两个矩形留出空间，使它面积最小。

然后转化为了两个矩阵的问题。同理再扫一遍即可。

时间复杂度 $O(n\log n)$，但常数巨大。虽然是分讨但可以复制粘贴，所以实现起来并不算太难（？）

```cpp
int n,tc,td;
struct PT {int x,y,c;} a[N],b[N];
bool cmpA(PT s,PT t) {return s.x<t.x;}
bool cmpB(PT s,PT t) {return s.y<t.y;}
bool chk(int x) {
	for(int u=1,cnt,i;u<=3;u++) for(int v=1;v<=3;v++) for(int w=1;w<=3;w++) if(u!=v&&u!=w&&v!=w) {
		cnt=0,i=1; for(;i<=n&&cnt<x;i++) cnt+=a[i].c==u; for(;i<=n&&a[i].x==a[i-1].x;i++);
		cnt=0; for(;i<=n&&cnt<x;i++) cnt+=a[i].c==v; if(cnt<x) continue; for(;i<=n&&a[i].x==a[i-1].x;i++);
		cnt=0; for(;i<=n&&cnt<x;i++) cnt+=a[i].c==w; if(cnt==x) return 1;
	}
	for(int u=1,cnt,j;u<=3;u++) for(int v=1;v<=3;v++) for(int w=1;w<=3;w++) if(u!=v&&u!=w&&v!=w) {
		cnt=0,j=1; for(;j<=n&&cnt<x;j++) cnt+=b[j].c==u; for(;j<=n&&b[j].y==b[j-1].y;j++);
		cnt=0; for(;j<=n&&cnt<x;j++) cnt+=b[j].c==v; if(cnt<x) continue; for(;j<=n&&a[j].y==a[j-1].y;j++);
		cnt=0; for(;j<=n&&cnt<x;j++) cnt+=b[j].c==w; if(cnt==x) return 1;
	}
	for(int u=1,cnt,i,j,lim;u<=3;u++) for(int v=1;v<=3;v++) for(int w=1;w<=3;w++) if(u!=v&&u!=w&&v!=w) {
		cnt=0,i=j=1; for(;i<=n&&cnt<x;i++) cnt+=a[i].c==u; for(;i<=n&&a[i].x==a[i-1].x;i++); lim=a[i-1].x;
		cnt=0; for(;j<=n&&cnt<x;j++) cnt+=b[j].x>lim&&b[j].c==v; if(cnt<x) continue; for(;j<=n&&b[j].y==b[j-1].y;j++);
		cnt=0; for(;j<=n&&cnt<x;j++) cnt+=b[j].x>lim&&b[j].c==w; if(cnt==x) return 1;
	}
	for(int u=1,cnt,i,j,lim;u<=3;u++) for(int v=1;v<=3;v++) for(int w=1;w<=3;w++) if(u!=v&&u!=w&&v!=w) {
		cnt=0,i=n,j=1; for(;i&&cnt<x;i--) cnt+=a[i].c==u; for(;i&&a[i].x==a[i+1].x;i--); lim=a[i+1].x;
		cnt=0; for(;j<=n&&cnt<x;j++) cnt+=b[j].x<lim&&b[j].c==v; if(cnt<x) continue; for(;j<=n&&b[j].y==b[j-1].y;j++);
		cnt=0; for(;j<=n&&cnt<x;j++) cnt+=b[j].x<lim&&b[j].c==w; if(cnt==x) return 1;
	}
	for(int u=1,cnt,i,j,lim;u<=3;u++) for(int v=1;v<=3;v++) for(int w=1;w<=3;w++) if(u!=v&&u!=w&&v!=w) {
		cnt=0,i=j=1; for(;j<=n&&cnt<x;j++) cnt+=b[j].c==u; for(;j<=n&&b[j].y==b[j-1].y;j++); lim=b[j-1].y;
		cnt=0; for(;i<=n&&cnt<x;i++) cnt+=a[i].y>lim&&a[i].c==v; if(cnt<x) continue; for(;i<=n&&a[i].x==a[i-1].x;i++);
		cnt=0; for(;i<=n&&cnt<x;i++) cnt+=a[i].y>lim&&a[i].c==w; if(cnt==x) return 1;
	}
	for(int u=1,cnt,i,j,lim;u<=3;u++) for(int v=1;v<=3;v++) for(int w=1;w<=3;w++) if(u!=v&&u!=w&&v!=w) {
		cnt=0,i=1,j=n; for(;j&&cnt<x;j--) cnt+=b[j].c==u; for(;j&&b[j].y==b[j+1].y;j--); lim=b[j+1].y;
		cnt=0; for(;i<=n&&cnt<x;i++) cnt+=a[i].y<lim&&a[i].c==v; if(cnt<x) continue; for(;i<=n&&a[i].x==a[i-1].x;i++);
		cnt=0; for(;i<=n&&cnt<x;i++) cnt+=a[i].y<lim&&a[i].c==w; if(cnt==x) return 1;
	}
	return 0;
}
void QwQ() {
	n=rd();	for(int i=1;i<=n;i++) a[i]=b[i]={rd(),rd(),rd()}; sort(a+1,a+1+n,cmpA),sort(b+1,b+1+n,cmpB);
	int l,r,mid; for(l=1,r=n/3;l<=r;) mid=l+r>>1,chk(mid)?l=mid+1:r=mid-1; wr(r*3,"\n");
}
```

---

## 作者：liuhengxi (赞：3)

## 题意
平面上有 $n$ 个点 $(3\mid n)$，$1,2,3$ 这 3 种颜色的点每种 $\dfrac n3$ 个。

求最大的 $k\ (3\mid k)$，可以选择每种点 $\dfrac k3$ 个，存在 $3$ 个互不相交的矩形分别包含全部每种颜色的 $\dfrac k3$ 个点。

## 题解
**二分答案**。

只要把平面分成 $3$ 块，每一块至少有 $\dfrac k3$ 个该颜色的点即可。

因为是 $3$ 块，一定是下面两种之一。（旋转等价）

![](https://cdn.luogu.com.cn/upload/image_hosting/nkkq9urc.png)

先排序。

+ 对于第 1 种，将横线从下向上移，直到有 $\dfrac k3$ 个该颜色的点，然后在上面用前缀和。

+ 对于第 2 种，将横线从左向右移（和第 1 种类似），直到有 $\dfrac k3$ 个该颜色的点，然后换一种颜色继续移，最后检查剩下区域的对应颜色是否有 $\dfrac k3$ 个。

[code](https://codeforces.com/problemset/submission/1608/138819724)

---

## 作者：JWRuixi (赞：1)

惊慌，尽然有这种大分类讨论型题目。

- 题意

给定 $n$ 个点，每个点有对应的颜色 $c_i(1 \le c_i \le 3)$，和坐标 $(x_i,y_i)$，每种颜色恰 $\frac{n}{3}$ 个。

找一个最大值 $k$ 使得从三种颜色中各选 $\frac{k}{3}$ 个，可以用三个交集为 $0$ 的矩形完全覆盖每个颜色的 $\frac{k}{3}$ 个点。

- 分析

既然和图有关系，那在没有思路的时候就不妨画个图，于是，你发现其实只有六种不同的可能的图，如下：

第一种情况，三个并排，分横向和竖向：

![CF1608E_sub1.png](https://s2.loli.net/2022/07/24/FazNRnlgKYXLBHT.png)

![CF1608E_sub2.png](https://s2.loli.net/2022/07/24/jCvnrbf7YoxQh3a.png)

第二种情况一个竖向两个横向，可以翻转：

![CF1608E_sub3.png](https://s2.loli.net/2022/07/24/gRC4MFsNzru5SBX.png)

![CF1608E_sub4.png](https://s2.loli.net/2022/07/24/lMx4QOWuJtZFofS.png)

第三种情况，如果将第二种情况旋转九十度，可以得到下面两幅图：

![CF1608E_sub5.png](https://s2.loli.net/2022/07/24/sU2I69KHrWLcSDA.png)

![CF1608E_sub6.png](https://s2.loli.net/2022/07/24/o9CwQgGJbxjHpeX.png)

那想到这里，就基本做完了，我们可以二分答案，枚举 $k$ 然后考虑，分这六类讨论。

对于每一种情况，我们可以将所有点按 $x_i$ 和 $y_i$ 分别排序，然后对于第一种情况，顺序取；第二种情况先取 $x_i$ 前 $k$ 大的点，在顺序去剩余连个矩形，注意满足这两个矩形的 $x_i$ 要大于第一个矩形，其余同理。

- 小细节

可能会出现 $x_i$ 或 $y_i$ 大小相同的不同颜色的点，要跳过。

- 复杂度

三种颜色排列，六种不同情况，复杂度 $O(36n\log{n})$。

实际上跑得还挺快的（

![CF1608E_status.png](https://s2.loli.net/2022/07/24/VjNIMQ165TwmARG.png)

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

const int maxn = 1e5 + 500;

struct pnt { int x, y, id; } p[maxn], q[maxn];

int n;

bool sub1 (int mid) {
	for (int s = 1; s <= 3; s++) {
		for (int t = 1; t <= 3; t++) {
			if (s == t) continue;
			for (int r = 1; r <= 3; r++) {
				if (s == r || t == r) continue;
				int ptr = 1, cnt;
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (p[ptr].id == s) cnt++;
				if (cnt < mid) continue;
				for (; ptr <= n && p[ptr].x == p[ptr - 1].x; ptr++);
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (p[ptr].id == t) cnt++;
				if (cnt < mid) continue;
				for (; ptr <= n && p[ptr].x == p[ptr - 1].x; ptr++);
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (p[ptr].id == r) cnt++;
				if (cnt < mid) continue;
				return 1;
			}
		}
	}
	return 0;
}

bool sub2 (int mid) {
	for (int s = 1; s <= 3; s++) {
		for (int t = 1; t <= 3; t++) {
			if (s == t) continue;
			for (int r = 1; r <= 3; r++) {
				if (s == r || t == r) continue;
				int ptr = 1, cnt;
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (q[ptr].id == s) cnt++;
				if (cnt < mid) continue;
				for (; ptr <= n && q[ptr].y == q[ptr - 1].y; ptr++);
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (q[ptr].id == t) cnt++;
				if (cnt < mid) continue;
				for (; ptr <= n && q[ptr].y == q[ptr - 1].y; ptr++);
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (q[ptr].id == r) cnt++;
				if (cnt < mid) continue;
				return 1;
			}
		}
	}
	return 0;
}

bool sub3 (int mid) {
	for (int s = 1; s <= 3; s++) {
		for (int t = 1; t <= 3; t++) {
			if (s == t) continue;
			for (int r = 1; r <= 3; r++) {
				if (s == r || t == r) continue;
				int ptr = 1, cnt, pt;
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (p[ptr].id == s) cnt++;
				if (cnt < mid) continue;
				pt = 1, ptr--;
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (q[pt].id == t && q[pt].x > p[ptr].x) cnt++;
				if (cnt < mid) continue;
				for (; pt <= n && q[pt].y == q[pt - 1].y; pt++);
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (q[pt].id == r && q[pt].x > p[ptr].x) cnt++;
				if (cnt < mid) continue;
				return 1;
			}
		}
	}
	return 0;
}

bool sub4 (int mid) {
	for (int s = 1; s <= 3; s++) {
		for (int t = 1; t <= 3; t++) {
			if (s == t) continue;
			for (int r = 1; r <= 3; r++) {
				if (s == r || t == r) continue;
				int ptr = n, cnt, pt;
				for (cnt = 0; ptr && cnt < mid; ptr--) if (p[ptr].id == s) cnt++;
				if (cnt < mid) continue;
				ptr++, pt = 1;
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (q[pt].id == t && q[pt].x < p[ptr].x) cnt++;
				if (cnt < mid) continue;
				for (; pt <= n && q[pt].y == q[pt - 1].y; pt++);
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (q[pt].id == r && q[pt].x < p[ptr].x) cnt++;
				if (cnt < mid) continue;
				return 1;
			}
		}
	}
	return 0;
}

bool sub5 (int mid) {
	for (int s = 1; s <= 3; s++) {
		for (int t = 1; t <= 3; t++) {
			if (s == t) continue;
			for (int r = 1; r <= 3; r++) {
				if (r == s || r == t) continue;
				int ptr = 1, pt, cnt;
				for (cnt = 0; ptr <= n && cnt < mid; ptr++) if (q[ptr].id == s) cnt++;
				if (cnt < mid) continue;
				ptr--, pt = 1;
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (p[pt].id == t && p[pt].y > q[ptr].y) cnt++;
				if (cnt < mid) continue;
				for (; pt <= n && p[pt].x == p[pt - 1].x; pt++);
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (p[pt].id == r && p[pt].y > q[ptr].y) cnt++;
				if (cnt < mid) continue;
				return 1;
			}
		}
	}
	return 0;
}

bool sub6 (int mid) {
	for (int s = 1; s <= 3; s++) {
		for (int t = 1; t <= 3; t++) {
			if (s == t) continue;
			for (int r = 1; r <= 3; r++) {
				if (s == r || t == r) continue;
				int ptr = n, pt, cnt;
				for (cnt = 0; ptr && cnt < mid; ptr--) if (q[ptr].id == s) cnt++;
				if (cnt < mid) continue;
				ptr++, pt = 1;
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (p[pt].id == t && p[pt].y < q[ptr].y) cnt++;
				if (cnt < mid) continue;
				for (; pt <= n && p[pt].x == p[pt - 1].x; pt++);
				for (cnt = 0; pt <= n && cnt < mid; pt++) if (p[pt].id == r && p[pt].y < q[ptr].y) cnt++;
				if (cnt < mid) continue;
				return 1;
			}
		}
	}
	return 0;
}

bool check (int mid) {
	if (sub1(mid)) return 1;
	if (sub2(mid)) return 1;
	if (sub3(mid)) return 1;
	if (sub4(mid)) return 1;
	if (sub5(mid)) return 1;
	if (sub6(mid)) return 1;
	return 0;
}

int main () {
	n = read();
	for (int i = 1; i <= n; i++) p[i] = q[i] = {read(), read(), read()};
	sort(p + 1, p + n + 1, [] (pnt u, pnt v) { return u.x < v.x; });
	sort(q + 1, q + n + 1, [] (pnt u, pnt v) { return u.y < v.y; });
	int l = 1, r = n / 3, mid, ans;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	write(ans * 3);
}
```

---

## 作者：Tyyyyyy (赞：1)

# CF1608E

#### 题意简述
- 给定平面上的 $n$ 个点 $(x_i,y_i)$，每个点有一个颜色 $c_i\in\{1,2,3\}$。每种颜色的点恰好各有 $\frac{n}{3}$ 个。
- 找到最大的 $k$，使得恰好能在每个颜色中选出 $\frac{k}{3}$ 个点，可以用三个交集为 $0$ 的矩形完全覆盖每个颜色的 $\frac{k}{3}$ 个点。
- $1 \leq n \leq 10^5,|x_i|,|y_i| \leq 10^9,c_i \in\{1,2,3\},3 | n$。

#### 题目分析
显然可以二分答案：若 $k_1$ 成立，则 $k<k_1$ 必定也成立。

接下来考虑怎么检查 $k$ 的正确性。

不难发现这三个矩形只可能有 $6$ 种情况：
1. 从左往右依次摆放。
1. 从上往下依次摆放。
1. 最上方有一个，下方左右各一个。
1. 最下方有一个，上方左右各一个。
1. 最左方有一个，右方上下各一个。
1. 最右方有一个，左方上下各一个。

依次检查上述 $6$ 种情况即可。注意，应该枚举颜色的排列来将颜色互换，尝试每种可能的情况。

具体实现上，前两种情况先尝试将两种颜色放在最左、最右或最上、最下方，再尝试将剩下的一种颜色放到中间即可。

对于后四种情况，可以先找到那个单个的颜色所处的最偏上、下、左、右的位置，再尝试放另外两种颜色。

算上依次检查和枚举排列，总的时间复杂度为 $O(36n\operatorname{log}n)$，实现时应当注意细节和边界情况的处理。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e5+10;
int n,cnt[3];
struct node
{
	int x,y;
}p[3][N],px[3][N],py[3][N],cur[3][N];
inline bool cmpx(node a,node b){return a.x<b.x;}
inline bool cmpy(node a,node b){return a.y<b.y;}
inline bool check_left_to_right(int k,int per[])
{
	for(int i=0;i<3;i++)memcpy(cur[i],px[per[i]-1],sizeof(px[per[i]-1]));
	int lx=cur[0][k].x,rx=cur[2][n/3-k+1].x;
	if(lx>=rx)return 0;
	for(int i=1;i+k-1<=n/3;i++)
		if(cur[1][i].x>lx&&cur[1][i+k-1].x<rx)return 1;
	return 0;
}
inline bool check_up_to_down(int k,int per[])
{
	for(int i=0;i<3;i++)memcpy(cur[i],py[per[i]-1],sizeof(py[per[i]-1]));
	int dy=cur[0][k].y,uy=cur[2][n/3-k+1].y;
	if(dy>=uy)return 0;
	for(int i=1;i+k-1<=n/3;i++)
		if(cur[1][i].y>dy&&cur[1][i+k-1].y<uy)return 1;
	return 0;
}
inline bool check_up1down2(int k,int per[])
{
	memcpy(cur[0],py[per[0]-1],sizeof(py[per[0]-1]));
	for(int i=1;i<3;i++)memcpy(cur[i],px[per[i]-1],sizeof(px[per[i]-1]));
	int uy=cur[0][n/3-k+1].y;
	int mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[1][i].y<uy)cnt1++,mx=cur[1][i].x;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[2][i].y<uy)cnt2++,mn=cur[2][i].x;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[2][i].y<uy)cnt1++,mx=cur[2][i].x;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[1][i].y<uy)cnt2++,mn=cur[1][i].x;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	return 0;
}
inline bool check_left1right2(int k,int per[])
{
	memcpy(cur[0],px[per[0]-1],sizeof(px[per[0]-1]));
	for(int i=1;i<3;i++)memcpy(cur[i],py[per[i]-1],sizeof(py[per[i]-1]));
	int lx=cur[0][k].x;
	int mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[1][i].x>lx)cnt1++,mx=cur[1][i].y;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[2][i].x>lx)cnt2++,mn=cur[2][i].y;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[2][i].x>lx)cnt1++,mx=cur[2][i].y;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[1][i].x>lx)cnt2++,mn=cur[1][i].y;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	return 0;
}
inline bool check_down1up2(int k,int per[])
{
	memcpy(cur[0],py[per[0]-1],sizeof(py[per[0]-1]));
	for(int i=1;i<3;i++)memcpy(cur[i],px[per[i]-1],sizeof(px[per[i]-1]));
	int dy=cur[0][k].y;
	int mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[1][i].y>dy)cnt1++,mx=cur[1][i].x;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[2][i].y>dy)cnt2++,mn=cur[2][i].x;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[2][i].y>dy)cnt1++,mx=cur[2][i].x;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[1][i].y>dy)cnt2++,mn=cur[1][i].x;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	return 0;
}
inline bool check_right1left2(int k,int per[])
{
	memcpy(cur[0],px[per[0]-1],sizeof(px[per[0]-1]));
	for(int i=1;i<3;i++)memcpy(cur[i],py[per[i]-1],sizeof(py[per[i]-1]));
	int rx=cur[0][n/3-k+1].x;
	int mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[1][i].x<rx)cnt1++,mx=cur[1][i].y;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[2][i].x<rx)cnt2++,mn=cur[2][i].y;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	mx=-2e9,cnt1=0,mn=2e9,cnt2=0;
	for(int i=1;i<=n/3;i++){if(cur[2][i].x<rx)cnt1++,mx=cur[2][i].y;if(cnt1==k)break;}
	for(int i=n/3;i>=1;i--){if(cur[1][i].x<rx)cnt2++,mn=cur[1][i].y;if(cnt2==k)break;}
	if(mx<mn&&cnt1==k&&cnt2==k)return 1;
	return 0;
}
inline bool check(int k)
{
	if(k*3>n)return 0;
	int per[]={1,2,3};
	do
	{
		if(check_left_to_right(k,per))return 1;
		if(check_up_to_down(k,per))return 1;
		if(check_up1down2(k,per))return 1;
		if(check_left1right2(k,per))return 1;
		if(check_down1up2(k,per))return 1;
		if(check_right1left2(k,per))return 1;
	}while(next_permutation(per,per+3));
	return 0;
}
template<typename T>inline void read(T &x) 
{
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
int main()
{
	read(n);
	for(int i=1,x,y,c;i<=n;i++)
	{
		read(x);read(y);read(c);
		p[c-1][++cnt[c-1]]=(node){x,y};
	}
	for(int i=1;i<=n/3;i++)
		for(int j=0;j<3;j++)
			px[j][i].x=py[j][i].x=p[j][i].x,
			px[j][i].y=py[j][i].y=p[j][i].y;
	for(int i=0;i<3;i++)
		sort(px[i]+1,px[i]+n/3+1,cmpx),sort(py[i]+1,py[i]+n/3+1,cmpy);
	int l=0,r=(n/3)+1,mid,ans=0;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%d",ans*3);
	return 0;
}
```

---

## 作者：louhao088 (赞：1)

题意：用三个不相交的矩形，使其每一个举行中有 $k$ 个某种颜色的点。使 $k$ 最大。


------------


由于答案明显具有单调性，我们可以考虑使用二分答案。


------------


那么如何判断一个值可不可行呢，这个似乎有点复杂，我们逐步考虑。

首先，我们考虑如果只有两种颜色怎么办。

很明显两个矩形的分布必然如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/ivjshgdy.png)



------------
那么其实分成三个矩形也差不多，可以大致归为以下六类

![](https://cdn.luogu.com.cn/upload/image_hosting/qp54mgs7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/r84itnh2.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/elignqo2.png)


我们只要判断能不能用这六种方式做到就可以了，再加上颜色的排列一次，二分每次判断 36 次。

对于如何判断任意一种矩形排列是否可行呢，我们可以用两个数组存储坐标，一个按 x 排序，另一个按 y 排序。对满足限制的坐标数颜色即可。


注意：代码细节较多，一个矩形内只能含一种颜色的点，判断不能取等于。

------------
代码如下


```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define lowbit (x&-x)
const int maxn=1e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,l,r,vis[maxn];
struct node 
{
	int x,y,z,id;
}a[maxn],b[maxn];
bool cmp(node a,node b)
{
	return a.x<b.x;
}
bool cmp2(node a,node b)
{
	return a.y<b.y;
}

bool check(int d,int e,int f,int x)
{
	int l=0,r=0,t=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].z==d)t++;
		if(t==x){l=a[i].x;break;}
	}
	if(t==x)
	{
		t=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i].z==e&&a[i].x>l)t++;
			if(t==x){r=a[i].x;break;}
		}
		if(t==x)
		{
			t=0;
			for(int i=1;i<=n;i++)
			{
				if(a[i].z==f&&a[i].x>r)t++;
				if(t==x){break;}
			}

			if(t==x)return 1;
		}
	
		t=0;
		for(int i=1;i<=n;i++)
		{
			if(b[i].z==e&&b[i].x>l)t++;
			if(t==x){r=b[i].y;break;}
		}
		if(t==x)
		{
			t=0;
			for(int i=1;i<=n;i++)
			{
				if(b[i].z==f&&b[i].x>l&&b[i].y>r)t++;
				if(t==x){break;}
			}
			if(t==x)return 1;
		}
	}
	
	
	
	t=0;
	for(int i=n;i>=1;i--)
	{
		if(a[i].z==d)t++;
		if(t==x){r=a[i].x;break;}
	}
	if(t==x)
	{
		t=0;
		for(int i=1;i<=n;i++)
		{
			if(b[i].z==e&&b[i].x<r)t++;
			if(t==x){l=b[i].y;break;}
		}
		if(t==x)
		{
			t=0;
			for(int i=1;i<=n;i++)
			{
				if(b[i].z==f&&b[i].x<r&&b[i].y>l)t++;
				if(t==x){break;}
			}
			if(t==x)return 1;
		}
	}
	
	
	
	
	
	
	
	
	
	t=0;
	for(int i=1;i<=n;i++)
	{
		if(b[i].z==d)t++;
		if(t==x){l=b[i].y;break;}
	}
	if(t==x)
	{
		t=0;
		for(int i=1;i<=n;i++)
		{
			if(b[i].z==e&&b[i].y>l)t++;
			if(t==x){r=b[i].y;break;}
		}
		
		if(t==x)
		{
			t=0;
			for(int i=1;i<=n;i++)
			{
				if(b[i].z==f&&b[i].y>r)t++;
				if(t==x){break;}
			}
			if(t==x)return 1;
		}
		
		
		
		
		t=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i].z==e&&a[i].y>l)t++;
			if(t==x){r=a[i].x;break;}
		}
		if(t==x)
		{
			t=0;
			for(int i=1;i<=n;i++)
			{
				if(a[i].z==f&&a[i].y>l&&a[i].x>r)t++;
				if(t==x){break;}
			}
			if(t==x)return 1;
		}
	}
	
	
	t=0;
	for(int i=n;i>=1;i--)
	{
		if(b[i].z==d)t++;
		if(t==x){r=b[i].y;break;}
	}
	if(t==x)
	{
		t=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i].z==e&&a[i].y<r)t++;
			if(t==x){l=a[i].x;break;}
		}
		if(t==x)
		{
			t=0;
			for(int i=1;i<=n;i++)
			{
				if(a[i].z==f&&a[i].y<r&&a[i].x>l)t++;
				if(t==x){break;}
			}//cout<<t<<endl;
			if(t==x)return 1;
		}
	}return 0;
}
bool check2(int x)
{
	if(check(1,2,3,x))return 1;
	if(check(2,1,3,x))return 1;
	if(check(3,1,2,x))return 1;
	if(check(3,2,1,x))return 1;
	if(check(1,3,2,x))return 1;
	if(check(2,3,1,x))return 1;
	return 0;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read(),a[i].z=read(),a[i].id=i,b[i]=a[i];
	sort(a+1,a+n+1,cmp),sort(b+1,b+n+1,cmp2);
	int l=1,r=n/3,res=0;//return 0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check2(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	cout<<res*3<<endl;
 	return 0;
}

```


---

## 作者：intel_core (赞：0)

这么无聊的题都能 2800，我居然打了这场还没场切。

二分答案，考虑 check 答案 $x$。

首先，我们肯定是要让每个矩形尽可能扩大到角上，注意到一共只有三个矩形，所以一定有一个矩形占据了两个角。那么剩下的两个矩形就只有两种位置关系。

分讨所有可能的位置关系，然后先确定那个占了两个角的矩形的最小大小，然后双指针扫另外两个矩形的边界即可。

复杂度 $O(n\log n)$。

---

