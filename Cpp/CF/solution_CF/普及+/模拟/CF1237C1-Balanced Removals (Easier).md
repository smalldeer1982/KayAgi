# Balanced Removals (Easier)

## 题目描述

This is an easier version of the problem. In this version, $ n \le 2000 $ .

There are $ n $ distinct points in three-dimensional space numbered from $ 1 $ to $ n $ . The $ i $ -th point has coordinates $ (x_i, y_i, z_i) $ . The number of points $ n $ is even.

You'd like to remove all $ n $ points using a sequence of $ \frac{n}{2} $ snaps. In one snap, you can remove any two points $ a $ and $ b $ that have not been removed yet and form a perfectly balanced pair. A pair of points $ a $ and $ b $ is perfectly balanced if no other point $ c $ (that has not been removed yet) lies within the axis-aligned minimum bounding box of points $ a $ and $ b $ .

Formally, point $ c $ lies within the axis-aligned minimum bounding box of points $ a $ and $ b $ if and only if $ \min(x_a, x_b) \le x_c \le \max(x_a, x_b) $ , $ \min(y_a, y_b) \le y_c \le \max(y_a, y_b) $ , and $ \min(z_a, z_b) \le z_c \le \max(z_a, z_b) $ . Note that the bounding box might be degenerate.

Find a way to remove all points in $ \frac{n}{2} $ snaps.

## 说明/提示

In the first example, here is what points and their corresponding bounding boxes look like (drawn in two dimensions for simplicity, as all points lie on $ z = 0 $ plane). Note that order of removing matters: for example, points $ 5 $ and $ 1 $ don't form a perfectly balanced pair initially, but they do after point $ 3 $ is removed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237C1/7ad611aa18ed85b1538cfecdeefb390344c16862.png)

## 样例 #1

### 输入

```
6
3 1 0
0 3 0
2 2 0
1 0 0
1 3 0
0 1 0
```

### 输出

```
3 6
5 1
2 4
```

## 样例 #2

### 输入

```
8
0 1 1
1 0 1
1 1 0
1 1 1
2 2 2
3 2 2
2 3 2
2 2 3
```

### 输出

```
4 5
1 6
2 7
3 8
```

# 题解

## 作者：梧桐灯 (赞：0)

解决三维偏序问题。

由于此题范围较小，所以各种玄学做法都能水过QwQ

首先先按x为第一，y第二，z第三为关键字从小到大排序

然后枚举i，j判断是否可行即可。

看起来很暴力，但实际上用并查集维护一下其实是可以通过的。

~~至于更难的数据加强版不会，看CF别人代码似乎是贪心？~~

贴超级暴力的代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
 
inline void read (int& s) {
	s = 0; int f = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') {if (c == '-') f = 1; c = getchar ();}
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
	s = f ? -s : s; return ;
}
 
const int N = 2003;
int n, vis[N];
struct stu {
	int x, y, z, id;
	inline int operator < (const stu& p) const {
		return x == p.x ? y == p.y ? z < p.z : y < p.y : x < p.x;
	}
}s[N];
 
int fa[N];
 
int Find (const int p) {return fa[p] == p ? p : fa[p] = Find (fa[p]);}
 
inline void Union (const int x, const int y) {
	fa[Find (x)] = Find (y);
	return ;
}
 
inline int pd (const int L, const int R) {
	int i, mny = min (s[L].y, s[R].y), mxy = s[L].y + s[R].y - mny;
	int mnz = min (s[L].z, s[R].z), mxz = s[L].z + s[R].z - mnz;
	for (i = Find (1); i <= n && s[i].x <= s[R].x; i = Find (i + 1)) {
		if (i == L || i == R) continue;
		if (s[i].x >= s[L].x && s[i].x <= s[R].x && s[i].y >= mny && s[i].y <= mxy && s[i].z >= mnz && s[i].z <= mxz) return 0;
	}
	return 1;
}
 
int main () {
	read (n);
	int i, j; for (i = 1; i <= n; ++i) {
		read (s[i].x), read (s[i].y), read (s[i].z);
		s[i].id = i;
		fa[i] = i;
	} //并查集维护，保证访问过的不会再被访问
	fa[n + 1] = n + 1;
	sort (s + 1, s + 1 + n);
	int num = 0;
	while (num < n) {
		for (i = Find (1); i <= n; i = Find (i + 1)) {
			for (j = Find (i + 1); j <= n; j = Find (j + 1)) {
				if (pd (i, j)) {
					vis[i] = vis[j] = 1;
					num += 2;
					Union (i, i + 1);
					Union (j, j + 1);
					printf ("%d %d\n", s[i].id, s[j].id);
					break;
				}
			}
		} //剩下的只要会暴力就能写QwQ
	}
	return 0;
}
```

---

## 作者：Create_Random (赞：0)

题意为删除两个三维坐标上的点，

使这两个点之间无任何给出了的点。

显然当两个点距离最近时中间无任何给出的点，

那么我们可以 $n^2$ 暴力求出所有点之间的距离，

再从小到大找最短距离，

删除时打标记不再出现即可。

时间复杂度 $O(n^2\log_2 (n^2))$.~~能过就行~~

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long x[2010],y[2010],z[2010];
long long ans;
bool flag[2010];
struct node
{
	long long l,r,v;
}a[4000010];
long long cnt;
bool cmp(node a,node b)
{
	return a.v<b.v;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&x[i],&y[i],&z[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			a[++cnt].l=i;
			a[cnt].r=j;
			a[cnt].v=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]);
		}
	}
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		if(flag[a[i].l]==0&&flag[a[i].r]==0)
		{
			printf("%lld %lld\n",a[i].l,a[i].r);
			flag[a[i].l]=1;
			flag[a[i].r]=1;
		}
	}
	return 0;
}
```


---

