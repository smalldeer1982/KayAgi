# Weight of the System of Nested Segments

## 题目描述

On the number line there are $ m $ points, $ i $ -th of which has integer coordinate $ x_i $ and integer weight $ w_i $ . The coordinates of all points are different, and the points are numbered from $ 1 $ to $ m $ .

A sequence of $ n $ segments $ [l_1, r_1], [l_2, r_2], \dots, [l_n, r_n] $ is called system of nested segments if for each pair $ i, j $ ( $ 1 \le i < j \le n $ ) the condition $ l_i < l_j < r_j < r_i $ is satisfied. In other words, the second segment is strictly inside the first one, the third segment is strictly inside the second one, and so on.

For a given number $ n $ , find a system of nested segments such that:

- both ends of each segment are one of $ m $ given points;
- the sum of the weights $ 2\cdot n $ of the points used as ends of the segments is minimal.

For example, let $ m = 8 $ . The given points are marked in the picture, their weights are marked in red, their coordinates are marked in blue. Make a system of three nested segments:

- weight of the first segment: $ 1 + 1 = 2 $
- weight of the second segment: $ 10 + (-1) = 9 $
- weight of the third segment: $ 3 + (-2) = 1 $
- sum of the weights of all the segments in the system: $ 2 + 9 + 1 = 12 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650C/5aeab71f3d5a716d6e18fda5439622dc4cd35cbc.png)System of three nested segments

## 说明/提示

The first test case coincides with the example from the condition. It can be shown that the weight of the composed system is minimal.

The second test case has only $ 6 $ points, so you need to use each of them to compose $ 3 $ segments.

## 样例 #1

### 输入

```
3

3 8
0 10
-2 1
4 10
11 20
7 -1
9 1
2 3
5 -2

3 6
-1 2
1 3
3 -1
2 4
4 0
8 2

2 5
5 -1
3 -2
1 0
-2 0
-5 -3```

### 输出

```
12
2 6
5 1
7 8

10
1 6
5 2
3 4

-6
5 1
4 2```

# 题解

## 作者：xhhhh36 (赞：4)

### [传送门](https://www.luogu.com.cn/problem/CF1650C)
# 思路
首先，我们发现只要选定 $2\times n$ 个点之后，就可以确定**唯一**的一种连线方法。即每次寻找**最左边**和**最右边**的两个点，将它们连起来。所以原问题就变为在 $m$ 个点中求**最小**的 $2\times n$ 个点。
# 具体做法
使用一个**结构体**来记录每个点的位置，权值和**编号**（最后输出时要输出点的编号）。在输入后按每个点的**权值大小**进行排序，权值小的在前。然后算出前 $2\times n$ 个点的权值和并输出。接着将前 $2\times n$ 个点按**位置**排序，每次输出最左边和最右边的两个点。注意每组数据输出后要**多输出一个空行**。
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
int t,n,m;
long long ans;
struct node
{
	int x,w,no;
}a[200001];
bool cmp(node x,node y)
{
	if (x.w==y.w) return x.no<y.no;
	return x.w<y.w;
}
bool cmp1(node x,node y)
{
	return x.x<y.x;
}
int main()
{
	cin>>t;
	while (t--)
	{
		cin>>n>>m;
		ans=0;
		for (int i=1;i<=m;i++)
		{
			cin>>a[i].x>>a[i].w;
			a[i].no=i;
		}
		sort(a+1,a+1+m,cmp);
		for (int i=1;i<=2*n;i++)
		{
			ans+=a[i].w;
		}
		cout<<ans<<endl;
		sort(a+1,a+1+2*n,cmp1);
		for (int i=1;i<=n;i++)
		{
			cout<<a[i].no<<" "<<a[2*n-i+1].no<<endl;
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：3)

# $\text{CF1650C}$ 题解

## 题目大意

数轴上有 $m$ 个点，每个点的位置是 $p_i$，权值是 $w_i$。

现在你要在这 $m$ 个点中选取 $2\times n$ 个点，并且连接成 $n$ 条没有公共端点的线段 $[l_1,r_1]\sim [l_n,r_n]$ 满足若 $i<j$ 则 $l_i<l_j<r_j<r_i$。

同时最小化这 $2\times n$ 个点的权值和，输出一种可行的方案。

数据范围保证：$n\le10^5,m\le2\times 10^5,-10^4\le w_i\le 10^4,-10^9\le p_i\le 10^9$ 且 $2\times n\le m$。

## 思路分析

一道简单的贪心题。

首先考虑线段之间互相包含的条件：不难发现，如果我们选择好了这 $2\times n$ 个点之后，一定能唯一确定一种连线方式满足要求：每一次位置取最左的点连位置最右的点即可。

所以就变成了一个水贪心题，选择权值最小的 $2\times n$ 个点然后再互相连即可。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1;
struct node {
	int id,pos,val;
	//因为要输出配对的点的编号所以要记录排序前是第几个 
}	a[MAXN];
inline bool Compare_Val(const node &x,const node &y) {
	//按值排序,贪心取点 
	return x.val<y.val;
}
inline bool Compare_Pos(const node &x,const node &y) {
	//按位置排序,连线的时候要用 
	return x.pos<y.pos;
}
inline void solve() {
	int n,m,ans=0;
	scanf("%lld%lld",&n,&m);
	for(register int i=1;i<=m;++i) {
		scanf("%lld%lld",&a[i].pos,&a[i].val);
		a[i].id=i;
	}
	sort(a+1,a+m+1,Compare_Val);
	//把所有的点按值降序排序,选择最小的2n个 
	for(register int i=1;i<=2*n;++i) ans+=a[i].val;
	printf("%lld\n",ans); //输出这些点的权值和 
	sort(a+1,a+2*n+1,Compare_Pos);
	//把所有的点按值降序排序,方便配对 
	for(register int i=1;i<=n;++i) {
		printf("%lld %lld\n",a[i].id,a[2*n+1-i].id);
		//把第i个和第2n-i+1个连起来 
	}
	return ;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：cyrxdzj (赞：1)

### 一、思路

这道题可以用结构体去做。

首先，按照权值排序。

然后，对于权值最低的 $2\times n$ 个点，按照位置排序。

最后分组输出一个点的 ID 即可。

### 二、完整代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct point_object
{
	int x,w;
	int id;
}point[200005];
int t;
int n,m;
bool cmp1(point_object a,point_object b)
{
	return a.w<b.w;
}
bool cmp2(point_object a,point_object b)
{
	return a.x<b.x;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&point[i].x,&point[i].w);
			point[i].id=i;
		}
		sort(point+1,point+1+m,cmp1);
		sort(point+1,point+1+2*n,cmp2);
		for(int i=1;i<=2*n;i++)
		{
			ans+=point[i].w;
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
		{
			printf("%d %d\n",point[i].id,point[2*n-i+1].id);
		}
		printf("\n");
	}
	return 0;
}

```

---

## 作者：Hooch (赞：0)

### 题目大意

给定 $m$ 个点，让你选定 $2n$ 个点，并让其中每个点两两配对。并且对于每两个配对的点，都不会和另一对交错，并且呈包围态。（如下图）

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650C/5aeab71f3d5a716d6e18fda5439622dc4cd35cbc.png)

每个点有一个代价 $w_i$，每次配对两个点的代价（另两个点是 $x$ 和 $y$）是 $w_x+w_y$，现在你要让总代价最小，并输出使得总代价最小的任意方案。

### 基本思路

首先非常容易看出无论选那些点，都能将其两两配对成题目要求的那样。设并且方案为：另下标为 $a_1,a_2,\cdots,a_{2n}$，只要将 $(a_1,a_{2n})$ 配对，$(a_2,a_{2n-1})$ 配对即可。

然后考虑贪心，显然选择 $2n$ 个权值最小的节点即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m;
struct node {int id, x, w; inline bool operator < (const node &V) const {return w == V.w ? id < V.id : w < V.w;}} a[N]; //按权值排序
signed main(void) {
	ios::sync_with_stdio(false);
	int t; cin >> t; while (t--) {
        cin >> n >> m;
        rep1(i, 1, m) cin >> a[i].x >> a[i].w, a[i].id = i;
        sort(a + 1, a + 1 + m);
        n <<= 1; vector <pair <int, int> > p; int ans = 0;
        rep1(i, 1, n) p.push_back(make_pair(a[i].x, a[i].id)), ans += a[i].w;
        sort(p.begin(), p.end()); //再按下标排一遍序
        int l = 0, r = p.size() - 1; cout << ans << endl;
		while (l < r) cout << p[l++].second << ' ' << p[r--].second << endl;//输出方案
        cout << endl;
	}
}
```

---

## 作者：落花月朦胧 (赞：0)

# Weight of the System of Nested Segments

## 题意

找 $n \times 2$ 个点，时这些点构成的区间互相包含，比如有区间 $a, b, c$，$a$ 就要包含 $b$, 而 $b$ 则要包含 $c$， 问选择点的权值最小值和这些嵌套的区间的左端点和右端点。

## Solution
可以发现无论选择那些点，都一定可以构成包含的关系，连接 $p,2\times n - p$ 总是满足条件的（$1 \le p\le n \times 2$）。

显然是一个贪心了，贪心的选择权值更大的点，然后在像上面一样连接就可以了。

一共排两次序。

## Code

```cpp
/*
Writer: ZhengXiangYu
*/
#include <bits/stdc++.h>

using i64 = long long;

int main() {
	auto solve = [&]() -> void {
		int n, m;
		scanf("%d%d", &n, &m);		
		
		struct node {
			int x, w, id;
			bool operator < (const node &a) const {
				return w < a.w;
			}
		};
		
		std::vector<node> a(m + 1);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &a[i].x, &a[i].w);
			a[i].id = i;
		}
		
		std::sort(a.begin() + 1, a.begin() + m + 1);
		
		int ans = 0;
		for (int i = 1; i <= n * 2; i++) {
			ans += a[i].w;
		}
		
		auto cmp = [&](node a, node b) -> bool {
			return a.x < b.x;
		};
		
		std::sort(a.begin() + 1, a.begin() + n * 2 + 1, cmp);
		
		std::cout << ans << std::endl; 
		for (int i = 1; i <= n; i++) {
			std::cout << a[i].id << " " << a[n * 2 - i + 1].id << std::endl;
		}
		
		std::cout << std::endl;
	};
	
	int T;
	std::cin >> T;
	while (T--) {
		solve();
	} 


	return 0;
}

```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

数轴上有 $m$ 个点，选出 $2\times n$ 个点，每个点位置为 $p_i$，价值为 $v_i$。

你需要根据题目给定的规则将这 $2\times n$ 个点两两连线成 $n$ 条线段，并且这 $n$ 条线段不相交。

如图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650C/5aeab71f3d5a716d6e18fda5439622dc4cd35cbc.png)
$$\tiny{\texttt{只能按照这种方式：左端点依次递增，每个左端点对应的右端点依次递减}}$$

请输出任意一种连线方案。

# 题目分析

这是一道贪心题。

因为要最小化权值和，所以先排序，然后取出前 $2\times n$ 个点。

随后对于这 $2\times n$ 个点，我们需要再将它们按位置排序，根据题目描述，我们按位置排序后维护两个指针，一个从头开始一个从尾开始，左指针和右指针所在的点连成一条线段。

# 代码

```cpp
//2022/3/8
//2022/3/16
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 2e5 + 5;
struct Node {
	int pos,val,id;
} node[ma];
int T,n,m;
inline bool cmp1(Node x,Node y) {
	return x.val < y.val;
}
inline bool cmp2(Node x,Node y) {
	return x.pos < y.pos;
}
inline void solve() {
	puts("");
	n = read(),m = read();
	
	for (register int i = 1;i <= m; ++ i) node[i].pos = read(),node[i].val = read(),node[i].id = i;
	sort(node + 1,node + m + 1,cmp1);
	int sum = 0;
	for (register int i = 1;i <= 2 * n; ++ i) sum += node[i].val;
	printf("%d\n",sum);
	sort(node + 1,node + 2 * n + 1,cmp2);
	int l = 1,r = 2 * n;
	while (l < r) {
		printf("%d %d\n",node[l].id,node[r].id);
		l ++,r --;
	}
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	T = read();
	while (T --) {
		solve();
	}

	return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 题目意思
有 $m$ 个下标在 $x$、权值为 $w$ 的数，现在要将这些数连成两两配对的 $n$ 条线，并且这 $n$ 条线是嵌套的，两两配对会产生一个权值和，然后最后要让总和最小，求最小值和按照输入顺序的编号输出是哪些数配对了。

### 解题思路
先按照权值大小将数排序，然后因为要配对就有 $2 \times n$ 个数要取出来，然后再将前 $2 \times n$ 个数按照位置排序，最后从外到内配对就行了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node {
  int id, x, w;
} a[200005];
int t, n, m, ans = 0;
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0', ch = getchar();
  }
  return x * f;
}
bool cmp1(Node a, Node b) {
  return a.w < b.w;
}
bool cmp2(Node a, Node b) {
  return a.x < b.x;
}
int main() {
  t = read();
  while (t--) {
    n = read();
    m = read();
    for (int i = 1; i <= m; i++) {
      a[i].x = read();
      a[i].w = read();
      a[i].id = i;
    }
    stable_sort(a + 1, a + 1 + m, cmp1);
    ans = 0;
    for (int i = 1, j = n * 2; i < j; i++, j--) {
      ans = ans + a[i].w + a[j].w;
    }
    printf("%d\n", ans);
    stable_sort(a + 1, a + 1 + n * 2, cmp2);
    for (int i = 1, j = n * 2; i < j; i++, j--) {
      printf("%d %d\n", a[i].id, a[j].id);
    }
  }

  return 0;
}

```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很明显，在 $m$ 个点中，选 $2n$ 个最小的点即可。

首先我们把那 $m$ 个点按权值升序排序，然后把最小的 $2n$ 个点按坐标降序排一遍。

然后，将第 $i(1\le i\le n)$ 号点与 $n\times2-i+1$ 号点配对即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
int t;
int n;
int m;
struct P{
	int id;
	int x;
	int d;
}p[max_n+2];
int ans=0;
bool cmp(P a,P b){
	return a.d<b.d;
}
bool cmpx(P a,P b){
	return a.x<b.x;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1650C_1.in","r",stdin);
	freopen("CF1650C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&m,&n);
		for(int i=1,x;i<=n;++i){
			scanf("%d%d",&p[i].x,&p[i].d);
			p[i].id=i;
		}
		sort(p+1,p+n+1,cmp);
		ans=0;
		for(int i=1;i<=(m<<1);++i)ans+=p[i].d;
		printf("%d\n",ans);
		sort(p+1,p+(m<<1)+1,cmpx);
		for(int i=1;i<=m;++i)printf("%d %d\n",p[i].id,p[(m<<1)-i+1].id);
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/71017433)

By **dengziyue**

---

## 作者：include_BM (赞：0)

任意选取 $2n$ 个点 $\{a_1,\dots a_{2n}\}$，一定可以构成一组互相嵌套的线段，其中第 $i$ 条线段两端点为 $a_i,a_{2n-i+1}$，如图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650C/5aeab71f3d5a716d6e18fda5439622dc4cd35cbc.png)

那么为了使权值和最小，只需要枚举权值最小的 $2n$ 个点即可。

代码：

```cpp
const int N=5e5+10;
ll n,m,ans;
struct node{
    int id,x,w;//编号，坐标，权值。
}a[N];
signed main(){
    for(int T=read();T;--T){
        n=read(),m=read(),ans=0;
        for(int i=1;i<=m;++i) a[i].id=i,a[i].x=read(),a[i].w=read();
        sort(a+1,a+m+1,[](node a,node b){return a.w<b.w;});//先按权值排序。
        sort(a+1,a+2*n+1,[](node a,node b){return a.x<b.x;});//将权值较小的 2n 个点按坐标排序。
        for(int i=1;i<=2*n;++i) ans+=a[i].w; printf("%lld\n",ans);
        for(int i=1;i<=n;++i) printf("%d %d\n",a[i].id,a[2*n-i+1].id); puts("");
    }
    return 0;
}
```

---

## 作者：ryanright (赞：0)

## Description

数轴上有 $m$ 个点，每个点都有一个坐标 $x_i$ 和权值 $w_i$。
定义一个线段序列 $[l_1,r_1],[l_2,r_2],\dots,[l_n,r_n]$ 为嵌套线段系统当 $[l_{i+1},r_{i+1}]$ 被严格嵌套在 $[l_i,r_i]$ 中。现在需要从中选出 $2n$ 个点，组成 $n$ 条线段，使其为嵌套线段系统，且所有端点权值和最小。求这个系统。

## Solution

事实上，不需要理睬什么嵌套线段系统，只需要从 $m$ 个点中选出权值最小的 $2n$ 个，这样它们的和必定最小，然后一首一尾输出原编号即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct point{int x,w,id;}p[200005];
inline bool cmp(const point& a,const point& b)
{
	return a.w<b.w;
}
inline bool cmp2(const point& a,const point& b)
{
	return a.x<b.x;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++) scanf("%d%d",&p[i].x,&p[i].w),p[i].id=i;
		sort(p+1,p+m+1,cmp);//取权值最小的 2n 个点
		sort(p+1,p+n*2+1,cmp2);//将取出的 2n 个点按照坐标排序
		int ans=0;
		for(int i=1;i<=n*2;i++) ans+=p[i].w;
		printf("%d\n",ans);
		for(int i=1;i<=n;i++) printf("%d %d\n",p[i].id,p[n*2-i+1].id);
		puts("");
	}
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：0)

### Solution

只要取出 $2n$ 个点，都可以说明这些点可以配对（从左到右，从右到左依次配对）。

所以，我们只需要以代价排一遍序，左边取 $2n$ 个数，再以坐标为关键字排序配对即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
    int x,w,id;
}nd[200001];
vector<Node> ans;

bool cmp(Node a,Node b) { return a.w<b.w; }
bool cmp2(Node a,Node b) { return a.x<b.x; }

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,sum=0;
        cin>>n>>m;
        for(int i=1;i<=m;i++) nd[i].id=i;
        for(int i=1;i<=m;i++) cin>>nd[i].x>>nd[i].w;
        sort(nd+1,nd+m+1,cmp);
        ans.clear();
        for(int i=1;i<=n*2;i++) sum+=nd[i].w,ans.push_back(nd[i]);
        cout<<sum<<endl;
        sort(ans.begin(),ans.end(),cmp2);
        for(int i=0;i<ans.size()/2;i++) cout<<ans[i].id<<" "<<ans[ans.size()-i-1].id<<endl;
    }
    return 0;
}
```

---

