# Triangular Paths

## 题目描述

考虑一个多层的“无穷三角形”，每层自上向下从一开始编号。第 $k$ 层有 $k$ 个节点，自左向右从一开始编号。三角形上每个点由坐标 $(r,c)$ 表示，其中前一个坐标表示层，后一个坐标表示序号。对于每个节点 $(r,c)$ 连两条**有向**边到点 $(r+1,c)$ 和 $(r+1,c+1)$，但是只有其中一条边被激活。如果 $r+c$ 是偶数，则到 $(r+1,c)$ 的边被激活。否则到 $(r+1,c+1)$ 的边被激活。如果您不能理解可以看题图理解。图中“被激活的边”为黑色，其他边为灰色。如果可以沿着被激活的边自 $(r_1,c_1)$ 到 $(r_2,c_2)$，称这两个点连通。例如，$(1,1)$ 和 $(3,2)$ 连通，但 $(2,1)$ 和 $(1,1)$ 不连通。

一开始，你在 $1,1$。每一步可以：

- 改变激活性。例如，您可以将本来到 $(r+1,c)$ 的激活边去激活并使得到 $(r+1,c+1)$ 的边被激活。这个操作花费 $1$ 的代价。

- 顺着激活的边到达下一层，无需消耗代价。

现在你被给出一个“无穷三角形”上的点的序列 $Q={r_i,c_i}$，现在请你找到花费最小的方式，使得你顺利经过这些点，不必考虑顺序。

## 说明/提示

$1\leqslant\sum n\leqslant2\times10^5,1\leqslant c_i\leqslant r_i \leqslant 10^9,1\leqslant t\leqslant10^4$

## 样例 #1

### 输入

```
4
3
1 4 2
1 3 1
2
2 4
2 3
2
1 1000000000
1 1000000000
4
3 10 5 8
2 5 2 4```

### 输出

```
0
1
999999999
2```

# 题解

## 作者：rong_nian (赞：5)

## 题意:

你有一个如下图构造的三角矩阵.

![1.jpeg](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1506F/2590a689fe7bd1eeca079bb14e0735bc33acbbf0.png)

它有无限层, 其中, 有些边是可以 **免费** 走的, 有些边要走需要有 $1$ 花费. (这些边都是有向的)

有 $T$ 组数据, 每组数据中有 $n$ 个点, 对于每组数据你需要输出, 不论顺序, 从 $(1, 1)$ 开始, 访问所有点的最小花费.

## solution

显然, 是有向图, 所以我们必须按照 $r_i$ 从小到大的顺序访问完所有的点.

我们考虑连续两点之间的路径的价值怎么算.

题目给的图点太少了, 看不出点啥东西, 这里手绘了一个. (很丑勿喷)

![1.png](https://i.loli.net/2021/03/28/TE9VKmAz5UvdeID.png)

这里的每个点所对应的 $(r_i, c_i)$ 都标在了点的右边. 那些被用黄笔涂过的边, 是题中 **免费** 走的边. 

我们可以注意到, 如果两点 $(r_1, c_1), (r_2, c_2)$ 的 $r - c$ 相同, 那么他们必然是处于同一条从左上到右下的链上. 而这些边中, 因为我们是无法从左下到右上的, 所以这样的两点之间路径是唯一的.

显然可得, 若 $(r - c) \% 2 == 0$ , 从 $(r_1, c_1)$ 到 $(r_2, c_2)$ 的花费为 $r_2 - r_1$ . 否则, 花费为 $0$

我们考虑如果两个点 $r-c$ 不相同该怎么做.

我们肯定是可以从 $(r_1, c_1)$ 走一段向右下的边再走一段向左下的边到达 $(r_2, c_2)$ 的. ~~(证明很简单, 留作习题)~~

那么我们必然可以找到一段从左上到右下的路径, 它是免费的, 而且我们可以途径它从 $(r_1, c_1)$ 走到 $(r_2, c_2)$

比如, 从 $(1, 1)$ 到 $(5,3)$ 可以 从 $(1, 1)$ 到 $(3,3)$ 到 $(5,3)$ 也可以从 $(1, 1)$ 到 $(2, 1)$ 到 $(4, 3)$ 到 $(5,3)$

所以我们结果就应该是走的从右上到左下, 不是免费的边的边数.

从 $(r, c)$ 向右走, 会到 $(r + 1, c + 1)$ 向左走会到 $(r + 1, c)$ 我们要求的是向左走的边数, 可以看出,  $\Delta c = c_2 - c_1$ 比 $\Delta r = r_2 - r_1$ 少的一部分就是向左走的边数.

因为 $r_1 + c_1$ 的奇偶性不同, 所以从 $(r_1, c_1)$ 出来的第一条向左走的边也会不同

- 若 $r_1 + c_1$ 为偶数, 第一条边是免费边, 而免费边和非免费边依次出现, 所以, 此时免费边个数 $\ge$ 非免费边个数
- 若 $r_1 + c_1$ 为奇数, 第一条边是非免费边, 所以此时 非免费边个数 $\ge$ 免费边个数

## Code : 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e5 + 5;
int n;
struct poi {
    int r, c;
} e[N];
bool cmp(poi a, poi b) {
    return a.r < b.r;
}
LL ans;

int main() {
    int t; scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        int pos = -1;
        for (int i = 1; i <= n; ++i) {
            scanf ("%d", &e[i].r);
            if (e[i].r == 1) pos = i;
        }
        for (int i = 1; i <= n; ++i) {
            scanf ("%d", &e[i].c);
            if (e[i].c == 1 && pos == i) pos = 0;
        }
        if (pos != 0) {
            n++;
            e[n].r = e[n].c = 1;
        }
        sort(e + 1, e + n + 1, cmp);
        ans = 0;
        for (int i = 2; i <= n; ++i) {
            if (e[i].r - e[i].c == e[i - 1].r - e[i - 1].c) {
                if ((e[i].c + e[i].r) % 2 == 0) {
                    ans += e[i].r - e[i - 1].r;
                }
            } else {
                int r = e[i].r - e[i - 1].r + 1, c = e[i].c - e[i - 1].c + 1;
                if ((e[i - 1].r + e[i - 1].c) % 2 == 0) {
                    ans += (r - c) / 2;
                } else ans += (r - c + 1) / 2;
            }
        }
        printf ("%lld\n", ans);
    }
    return 0;
}
```



---

## 作者：Warriors_Cat (赞：4)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1506F) & [CF 题面传送门](http://codeforces.com/problemset/problem/1506/F)。

题意：

* 有张无限三角形网格，每个点坐标可表示为 $(x, y)(1 \le y \le x)$。
* 当 $2\mid (x+y)$ 时，$(x, y)$ 会向 $(x+1, y)$ 连边，否则会向 $(x+1, y+1)$ 连边。
* 当 $(x, y)\rightarrow(x+1, y+d)(d=0, 1)$ 时，可以花费 $1$ 代价把连边变为 $(x, y)\rightarrow(x+1, y+1-d)$。
* 有 $n$ 个点 $(r_i, c_i)$，问从 $(1, 1)$ 出发至少要花费多少代价才能走遍所有点。保证必定存在一种能全部走完的方案。

一个相对来说比较水的 *2000 的 Div.3 题。

---

### Solution：

我们可以把这幅图稍微画一下，看它长什么样：

![](https://cdn.luogu.com.cn/upload/image_hosting/cqe9aip7.png)

然后我们就会发现是若干个互不联通且全等的子图拼成的一个大图。而这张子图的特点就是左边的相邻点全部有连边，右边的点会连到它的左下方。

我们先考虑如何从点 $(x, y)$ 走到点 $(z, w)$。

$(x, y)$ 在它所在的联通块中要么在左边，要么在右边，于是分两类讨论。

当 $2\mid (x+y)$ 时，从点 $(x, y)$ 走到点 $(z, w)$ 等价于从点 $(1, 1)$ 走到点 $(z-x+1, w-y+1)$，不妨记为 $(x', y')$。当 $x'=y'$ 时，发现每走一步都要换一次方向，答案为 $x'-1$；否则我们只需要考虑它跨过了多少个连通块即可，答案为 $\left\lfloor\dfrac{x'-y'}{2}\right\rfloor$。

当 $2\nmid (x+y)$ 时，从点 $(x, y)$ 走到点 $(z, w)$ 等价于从点 $(2, 1)$ 走到点 $(z-x+2, w-y+1)$，不妨记为 $(x', y')$。当 $x'=y'+1$ 时，发现可以直接走完，答案为 $0$；否则我们只需要考虑它跨过了多少个连通块即可，答案为 $\left\lfloor\dfrac{x'-y'}{2}\right\rfloor$。

最后再考虑如何算答案。首先在走的过程中 $x$ 一定是单调递增的，所以我们可以先将所有 $(r_i, c_i)$ 按照 $r$ 排序，然后相邻两个点按照刚才的走法走就行了。

over，时间复杂度为 $O(n\log n)$。

---

### Code：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 200010;
struct node{
	int x, y;
	bool operator < (const node&rhs)const{
		return x < rhs.x; 
	}
}a[N]; 
int n;
inline int calc1(int x, int y){
	if(x == y) return x - 1;
	return (x - y) / 2;
}
inline int calc2(int x, int y){
	if(x == y + 1) return 0;
	return (x - y) / 2;
}
inline void mian(){
	n = read(); a[0].x = a[0].y = 1;
	rep(i, 1, n) a[i].x = read();
	rep(i, 1, n) a[i].y = read();
	sort(a, a + n + 1); ll ans = 0;
	rep(i, 1, n){
		int x1 = a[i - 1].x, x2 = a[i].x, y1 = a[i - 1].y, y2 = a[i].y;
		if((x1 & 1) == (y1 & 1)) ans += calc1(x2 - x1 + 1, y2 - y1 + 1);
		else ans += calc2(x2 - x1 + 2, y2 - y1 + 1);
	}
	printf("%lld\n", ans);
}
int main(){ int qwq = read(); while(qwq--) mian(); return 0; }
```

---

## 作者：Prms_Prmt (赞：2)

提供一个不用排序的思路，读者可以尝试结合题意和以下描述自行画图。

把原图旋转四十五度，转化为网格图：其中同行 $ r - c $ 相等，同列 $ c $ 相等。

贪心地考虑，横向行走时尽量在 $r-c$ 为奇数的行（奇行）上走，没有代价；只有偶行上有代价——即偶行上极左点到极右点的距离。

因为激活性交替，所以分类讨论一下穿梭于行之间的代价，加上就行。

详见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,t,x[N],y[N];

map<int,int>mp,mq;//作者比较懒

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		x[n+1]=1,y[n+1]=1;//要求从 (1,1) 出发
		for(int i=1;i<=n;i++) scanf("%d",&x[i]);
		for(int i=1;i<=n;i++) scanf("%d",&y[i]);
		++n;
		mp.clear();
		mq.clear();
		int mid=INT_MAX,mad=INT_MIN;//最上面一行的 r-c 值和最下面一行的 r-c 值
		long long sum=0;
		
		for(int i=1;i<=n;i++)
		{
			if((x[i]-y[i])%2==0) {//只记录所有偶行的极左极右点
				if(!mp.count(x[i]-y[i])) mp[x[i]-y[i]]=y[i];
				else mp[x[i]-y[i]]=max(mp[x[i]-y[i]],y[i]);
				if(!mq.count(x[i]-y[i])) mq[x[i]-y[i]]=y[i];
				else mq[x[i]-y[i]]=min(mq[x[i]-y[i]],y[i]);
			}
			mid=min(mid,x[i]-y[i]);
			mad=max(mad,x[i]-y[i]);
		}
		for(auto i:mp) {
			sum+=mp[i.first]-mq[i.first];//统计偶行贡献
		}
		if(mid%2==0) printf("%lld\n",(mad-mid)/2+sum);//分类讨论
		else printf("%lld\n",(mad-mid+1)/2+sum);
	}
	return 0;
}
```

---

## 作者：__Deng_Rui_Song__ (赞：1)

# presafe

~~疾病题~~

# problem

[题目传送门](/problem/CF1506F)

# solution

对一般人来说，确实很难；但对脊椎病患者来说，这真是个福利，你只要把头顺时针旋转 45°，OK，这题秒了。

![](https://cdn.luogu.com.cn/upload/image_hosting/9072vrc5.png)

上面纯属玩笑，接下来怎么办？首先肯定要按行（题目）排序，因为这是个拓扑图，然后很容易发现现点在 $(r-c+1,c)$，所以分讨。

- $r_1-c_1=r_2-c_2$：如果 $r_1-c_1+1$ 为奇数，那么只能走虚线，否则直接走直线。

- $r_1-c_1\ne r_2-c_2$：

  - 如果 $r_1-c_1+1$ 为奇数，那么可以先左下，再右下直到 $c_1=c_2$，最后一直左下即可，可以发现，实线虚线交替出现，所以代价为 $\lfloor\frac{(r_2-r_1)}{2}\rfloor$。
  - 否则，可以先右下直到 $c_1=c_2$，最后一直左下即可，此时代价为 $\lceil\frac{(r_2-r_1)}{2}\rceil$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n;
pair<int, int> a[200005];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].first;
  for (int i = 1; i <= n; i++) cin >> a[i].second;
  sort(a + 1, a + n + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int tmp = ans, x1 = a[i - 1].first, y1 = a[i - 1].second, x2 = a[i].first, y2 = a[i].second;
    if (x1 - y1 == x2 - y2)
      ans += ((x1 - y1) % 2 ? 0 : x2 - x1);
    else {
      if ((x1 - y1) % 2)
        ans += (x2 - x1 - y2 + y1 + 1) / 2;
      else
        ans += (x2 - x1 - y2 + y1) / 2;
    }
  }
  cout << ans << '\n';
}
signed main() {
  a[0] = {1, 1};
  for (cin >> t; t--; solve());
  return 0;
}
```

# postscript

打字不易，点个赞吧（逃

---

