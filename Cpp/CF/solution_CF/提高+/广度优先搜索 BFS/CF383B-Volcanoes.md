# Volcanoes

## 题目描述

Iahub got lost in a very big desert. The desert can be represented as a $ n×n $ square matrix, where each cell is a zone of the desert. The cell $ (i,j) $ represents the cell at row $ i $ and column $ j $ $ (1<=i,j<=n) $ . Iahub can go from one cell $ (i,j) $ only down or right, that is to cells $ (i+1,j) $ or $ (i,j+1) $ .

Also, there are $ m $ cells that are occupied by volcanoes, which Iahub cannot enter.

Iahub is initially at cell $ (1,1) $ and he needs to travel to cell $ (n,n) $ . Knowing that Iahub needs $ 1 $ second to travel from one cell to another, find the minimum time in which he can arrive in cell $ (n,n) $ .

## 说明/提示

Consider the first sample. A possible road is: $ (1,1) $ $ → $ $ (1,2) $ $ → $ $ (2,2) $ $ → $ $ (2,3) $ $ → $ $ (3,3) $ $ → $ $ (3,4) $ $ → $ $ (4,4) $ .

## 样例 #1

### 输入

```
4 2
1 3
1 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7 8
1 6
2 6
3 5
3 6
4 3
5 1
5 2
5 3
```

### 输出

```
12
```

## 样例 #3

### 输入

```
2 2
1 2
2 1
```

### 输出

```
-1
```

# 题解

## 作者：duyi (赞：10)

# CF383B Volcanoes

[题目链接](https://codeforces.com/contest/383/problem/B)

## 本题题解

首先容易发现，如果存在一条从起点 $(1,1)$ 到终点 $(n,n)$ 的合法路径，其用时一定为 $2n-2$。

于是我们只需要判断是否存在这样的路径。

把点按行坐标从小到大排序，行坐标相同时按列坐标从小到大排序。

从小到大依次考虑每一行，行坐标相同的点放在一起处理。假设当前考虑到第 $i$ 行，设这行里一共有 $s_i$ 个障碍物（$s_i > 0$）。

在每一行里，有一些点是可以到达的，其他点则是不能到达的。我们把相邻的、可以到达的点，压缩成一条线段。一个重要的观察是：每行里可以到达的点组成的线段数量，不超过 $s_i + 2$ 条。因为线段不能覆盖障碍物（障碍物一定是不能到达的），并且相邻两个障碍物之间至多只有一条线段。

现在我们只要递推求出每一行的这些线段，然后判断最后一行的线段是否覆盖了 $(n,n)$。

考虑本行里相邻的两个障碍物 $(i,a), (i,b)$，则 $[a + 1, b - 1]$ 区间里可能存在线段。找出上一行被线段覆盖的点中、第一个在 $[a + 1, b -1]$ 区间内的点，记为 $c$，则 $[c, b - 1]$ 就成为了本行里的一条线段（也就是连续的一段可以到达的点）。如果不存在这样的 $c$，则显然 $[a + 1, b - 1]$ 区间里没有线段。

找 $c$ 可以在上一行的线段集合里二分查找，也可以用 two pointers 维护。二分查找更好写一些，并且也不会影响复杂度，因为我们前面本来就要排序的。

时间复杂度 $O(m\log m + \sum_{s_i > 0}(s_i\log s_i)) = O(m\log m)$。

## 参考代码

```cpp
// problem: CF383B
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXM = 1e5;

int n, m;
pii p[MAXM + 5];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> p[i].fi >> p[i].se;
	}
	sort(p + 1, p + m + 1);
	m = unique(p + 1, p + m + 1) - (p + 1);
	
	vector<pii> seg;
	seg.pb(mk(1, 1));
	int lst = 0;
	for (int i = 1; i <= m; ++i) {
		int j = i;
		while (j + 1 <= m && p[j + 1].fi == p[i].fi)
			++j;
		
		if (!SZ(seg)) {
			cout << -1 << endl;
			return 0;
		}
		if (p[i].fi > lst + 1) {
			pii tmp = mk(seg[0].fi, n);
			vector<pii>().swap(seg);
			seg.pb(tmp);
		}
		
		int pre = 0;
		vector<pii> newseg;
		for (int k = i; k <= j; ++k) {
			if (pre + 1 == p[k].se) {
				pre = p[k].se;
				continue;
			}
			// [pre + 1, p[k].se - 1]
			int t = lob(seg.begin(), seg.end(), mk(pre + 1, 0)) - seg.begin();
			
			if (t != 0 && seg[t - 1].se >= pre + 1) {
				newseg.pb(mk(pre + 1, p[k].se - 1));
			} else if (t != SZ(seg) && seg[t].fi <= p[k].se - 1) {
				newseg.pb(mk(seg[t].fi, p[k].se - 1));
			}
			pre = p[k].se;
		}
		if (pre != n) {
			// [pre + 1, n]
			int t = lob(seg.begin(), seg.end(), mk(pre + 1, 0)) - seg.begin();
			
			if (t != 0 && seg[t - 1].se >= pre + 1) {
				newseg.pb(mk(pre + 1, n));
			} else if (t != SZ(seg) && seg[t].fi <= n) {
				newseg.pb(mk(seg[t].fi, n));
			}
		}
		
		// for (int k = 0; k < SZ(newseg); ++k) {
		// 	cerr << "[" << newseg[k].fi << "," << newseg[k].se << "]" << " \n"[k == SZ(newseg) - 1];
		// }
		
		lst = p[i].fi;
		i = j;
		seg = newseg;
	}
	if (!SZ(seg)) {
		cout << -1 << endl;
		return 0;
	}
	if (lst != n) {
		pii tmp = mk(seg[0].fi, n);
		vector<pii>().swap(seg);
		seg.pb(tmp);
	}
	for (int i = 0; i < SZ(seg); ++i) {
		if (seg[i].fi <= n && seg[i].se >= n) {
			cout << n * 2 - 2 << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}
```



---

## 作者：Clover_BY (赞：3)

# [CF383B  Volcanoes](https://www.luogu.com.cn/problem/CF383B)
## 题目描述
给定一个大小为 $n\times n$ 的棋盘，其中有 $m$ 个点为禁区。  
求从棋盘左上角开始，只向下或右走，到达棋盘右下角的路径长度。无解输出 `-1`。

数据范围：$1 \leq x_i, y_i \leq n \leq 10^9, 1 \leq m \leq 10^5$。

## 题目分析
~~被诈骗了，以为是一道计数题。~~  
实际上稍加思考很快就能发现只要存在一条合法路径，其长度一定是 $2n-2$。路径等长的证明可以参考小学数学题计算不规则多边形周长时的平移线段操作。

于是我们只需要判断是否存在合法路径即可。注意到这一步不好操作，我们考虑按行数分开处理。  
接下来会用一些图例辅助说明。以下所有图例中 `#` 代表禁区，`.` 代表空地，`×` 代表不能到达，`√` 代表能够到达，`-` 代表不在可能的连续段内。  
```
......
.#....
#..#..
```  
考虑每行能走到的**连续段**有哪些。  
对于第一行，显然是整段 `[1,6]`。  
对于第二行，由于有禁区存在，连续段被分为 `[1,1]` 和 `[3,6]`。  
对于第三行，注意到由于只能向下或右走，第二个位置不能达到，故连续段为 `[3,3]` 和 `[5,6]`。

容易发现，能走到的位置都能用每行的连续段来量化。故我们只需要统计每一行能走到的连续段，并判断最后一行的连续段是否包含最后一个位置即可。

考虑这些连续段的转移。使用 `set` 维护各个连续段的左右端点，同时记录上一行连续段中最靠左的位置 `lb`。容易发现这个位置单调不减，因为段是逐渐向右移的。  
转移时有如下几种情况：  

1. 空行
```
#..#..#
.......
#...#..
```
第二行为空行，因而只要第一行可以向下走，其后方的位置都能到达。在 `set` 中直接插入 `[lb,n]` 即可。空行向下一行的转移同样需要注意。  
如果连续多行是空行，处理一行之后全部跳过即可。

2. 段中所有位置都能到达
```
#.......#
###...###
---√√√---
```
```
#...#####
###.....#
---√√√√√-
```
两个例子中，若第一行中的连续段能够被路径完全覆盖，第二行中的亦可。

3. 段中只有部分位置能够到达
```
####....#
#......##
-×××√√√--
```
```
##....###
#.......#
-×√√√√√√-
```
两个例子中，即使第一行的连续段能够被路径完全覆盖，第二行的段只有与第一行段左端点平齐位置往后的部分能够到达。

最后，注意起点行与终点行的特殊处理。  
转移的部分仿照上述，用 `set` 模拟即可。代码中用了一个类似滚动数组的技巧。  
整体难度不大，建议评绿或蓝。

## Code
```cpp
#include <cstdio>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;

inline int read()
{
    int x = 0; char c;
    while(!isdigit(c = getchar()));
    do{
        x = (x << 1) + (x << 3) + (c ^ 48);
    }while(isdigit(c = getchar()));
    return x;
}

int top = 0, stk[20];
inline void write(int x)
{
    do{
        stk[++top] = x % 10;
        x /= 10;
    }while(x);
    for(register int i = top; i; --i)
        putchar(stk[i] | 48);
    putchar('\n'); top = 0;
    return ;
}

int n, m, l, r, lb = 1, pre = 1, now = 1, last = 0;
struct node
{
    int x;
    int y;
}sz[100010];
inline bool operator < (node a, node b)
{
    if(a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
set<node> s[2];
set<node> :: iterator it;

inline void testinsert(int l, int r)
{
	it = s[last].upper_bound((node){l, 2147483647}); --it;
	if(it -> x <= l && it -> y >= l)
	{
		s[now].insert((node){l, r});
		return ;
	}
	it = s[last].lower_bound((node){l, 0});
	if(it -> x >= l && it -> x <= r)
		s[now].insert((node){it -> x, r});
	return ;
}

int main()
{
    n = read(); m = read();
	if(m == 0)
	{
		write((n << 1) - 2);
		return 0;
	}
    for(register int i = 1; i <= m; ++i)
    {
        sz[i].x = read();
        sz[i].y = read();
    }
    sort(sz + 1, sz + m + 1); pre = sz[1].x;
    if(sz[1].x > 1) s[0].insert((node){1, n});
    else s[0].insert((node){1, 1});
    for(register int i = 1; i <= m; ++i)
    {
        l = lb;
        while(i <= m && sz[i].x == pre)
        {
            r = sz[i].y - 1;
            if(l > r)
            {
                l = sz[i].y + 1;
                ++i; continue;
            }
            testinsert(l, r);
            l = sz[i].y + 1; ++i;
        }
        if(l <= n) testinsert(l, n);
        if(s[now].empty())
        {
            printf("-1\n");
            return 0;
        }
        it = s[now].begin(); lb = it -> x;
        if(i == m + 1)
        {
            if(sz[i - 1].x < n)
			{
				s[now].clear();
				s[now].insert((node){lb, n});
			}
            last ^= 1; now ^= 1; break;
        }
        if(sz[i].x > pre + 1)
        {
            s[now].clear();
            s[now].insert((node){lb, n});
        }
        pre = sz[i--].x; now ^= 1; last ^= 1; s[now].clear();
    }
    it = s[last].end(); --it;
    if(it -> y == n) write((n << 1) - 2);
    else printf("-1\n"); return 0;
}
```

---

## 作者：chenxia25 (赞：2)

首先注意到如果有解那么答案显然是 $2n-2$，于是判有解性即可。

我们考虑一个朴素的 DP，就是从上面和左边转移过来。我们考虑对其优化。注意到它是一个连空间都爆炸的 DP，对这类考虑惯用套路：设一个阶段，然后在阶段的递增过程中维护这个阶段内的 DP 序列 / 矩阵。于是我们把行作为阶段，这样更新次数显然是 $\mathrm O(m)$ 的。

如果经过空行，那么就找到第一个 `true` 然后赋后缀；如果有障碍物，那就在障碍物分割成的段们内进行如上操作。这显然可以用一个动态开点线段树轻松维护。不过看了 dyls 的题解发现有更简单的方法。我们考虑维护赋成 `true` 的区间们，用 `set` 存，每次查询就二分，修改就 `erase` 若干然后 `insert`。其实还可以每个阶段重新赋这个数据结构，更方便地用 `vector` 存。

---

## 作者：shao0320 (赞：2)

# CF383B Volcanoes

首先只有两种情况，如果能走到就是 $2n-2$ ，否则就是 $-1$ .

由于行数很少，因此考虑按行维护所有合法区间。

用 set 维护合法区间，由于障碍物不多，那么拆出来的区间必然也不会很多，
那么考虑的情况就是一段合法区间中间出了个障碍。

set 直接 lower_bound  查找后维护即可。

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2500}$
---
### 解题思路：

首先容易发现答案只有 $2n-2$ 和 $-1$ 两种，也就是只需要判断是否存在路径到达终点就行。

观察数据范围，可以发现火山的数量相对整个图的大小而言很少，也就是说有用的行或者列很少。两者对称，不妨取行来讨论。

将所有的火山按照行的大小排序，依次对于每一个有用的行维护出可以走到的区间，两行之间如果都是有用的则对于每一个区间依次处理，否则就只需要直接跳过大量的无用行就行了。最后判断在最后一行最后一列是否被包含在区间之内。

实现上可以把一堆的无用行压缩成一个有用行处理。

双指针写的话好像细节挺多的，需要注意一下。

---
### 代码：

```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int MAXN=200005;
int n,m,now,s[MAXN],tot,cnt1,cnt2;
struct str{
	int x,y;
	bool operator <(str a){
		if(y==a.y)return x<a.x;
		return y<a.y; 
	}
}p[MAXN],l[MAXN],l2[MAXN];
// 点     区间 
void copy(){
	cnt1=cnt2;
	for(int i=1;i<=cnt1;i++)
	l[i].x=l2[i].x,l[i].y=l2[i].y;
}
void work(){
	if(cnt1==0)return;
	cnt2=0;int p=1;tot++;s[tot]=n+1;
	for(int i=1;i<=tot;i++){
		if(s[i]-s[i-1]==1)continue;
		while(p<cnt1&&l[p].y<=s[i-1])p++;
		if(l[p].y<=s[i-1])continue;
		if(l[p].x<=s[i-1]){
			l2[++cnt2].x=s[i-1]+1;
			l2[cnt2].y=s[i]-1;
		}
		if(s[i-1]<l[p].x&&l[p].x<s[i]){
			l2[++cnt2].x=l[p].x;
			l2[cnt2].y=s[i]-1;
		}
	}
	copy();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+m+1);
	p[0].y=1;cnt1=1;l[1].x=1;l[1].y=1;
	for(int i=1;i<=m;i++){
		if(p[i].y==p[i-1].y)s[++tot]=p[i].x;
		else{
			work();
			if(p[i].y-p[i-1].y>1){tot=0;work();}
			tot=1;s[tot]=p[i].x;
		}
	}
	work();
	if(p[m].y<n){tot=0;work();}
	if(l[cnt1].y==n)printf("%d\n",2*n-2);
	else printf("-1\n");
	return 0;
}
```


---

