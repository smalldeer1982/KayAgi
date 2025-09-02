# Minimum Diameter Tree

## 题目描述

You are given a tree (an undirected connected graph without cycles) and an integer $ s $ .

Vanya wants to put weights on all edges of the tree so that all weights are non-negative real numbers and their sum is $ s $ . At the same time, he wants to make the diameter of the tree as small as possible.

Let's define the diameter of a weighed tree as the maximum sum of the weights of the edges lying on the path between two some vertices of the tree. In other words, the diameter of a weighed tree is the length of the longest simple path in the tree, where length of a path is equal to the sum of weights over all edges in the path.

Find the minimum possible diameter that Vanya can get.

## 说明/提示

In the first example it is necessary to put weights like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/c1a70d116ee899735bc4ecf7ff6c6bf75b292051.png)It is easy to see that the diameter of this tree is $ 2 $ . It can be proved that it is the minimum possible diameter.

In the second example it is necessary to put weights like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/7a6a70a648e37d9e55f1bb9aed6b2be7637ee566.png)

## 样例 #1

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
2.000000000000000000```

## 样例 #2

### 输入

```
6 1
2 1
2 3
2 5
5 4
5 6
```

### 输出

```
0.500000000000000000```

## 样例 #3

### 输入

```
5 5
1 2
2 3
3 4
3 5
```

### 输出

```
3.333333333333333333```

# 题解

## 作者：shiroi (赞：3)

### Description

给定一棵 $n$ 个点的树，和一个正整数 $s$ 。

现在让你在这棵树上给 $n-1$ 条边分配边权，使得这棵树的直径最小且权值之和为 $s$。



### Solution

观察题目发现连接叶子节点的边对结果的贡献最小，所以我们可以考虑只给连接叶子节点的边赋值。

题目中给定了权值之和为 $s$ ，考虑将权值之和平均分配每条连接叶子节点的边。

令 $cnt$ 为叶子节点数，则此时叶子节点的边的边权为 $\frac{s}{cnt}$ ，其他边边权都为 $0$ 。此时答案为 $\frac{2s}{cnt}$ 。

实现时只需求出叶子节点个数即可，代码相对简单。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,f=1,c=getchar();
    while(c<48) c=='-'&&(f=-1),c=getchar();
    while(c>47) x=x*10+c-'0',c=getchar();
    return x*f;
}

const int MAXN = 100005;
int deg[MAXN];
int n,s,tot;

int main(int argc, char const *argv[])
{
    n=read(); s=read()<<1;
    for(int i=1; i<n; ++i)
        ++deg[read()],++deg[read()];
    for(int i=1; i<=n; ++i)
        if(deg[i]==1) ++tot;
    printf("%.8lf", (double)s/tot);
    return 0;
}
```

---

## 作者：Y_QWQ_Y (赞：1)

### 题意解析
就是给定我们一颗 $n$ 个点的树，并给出树的 $n-1$ 条边，要求分配权值之和为 $s$ 且树的直径最小。

### 解题思路
通过分析，可以发现，连接叶子结点的边权对结果贡献较小，就可以考虑给叶子节点的的边赋值。

而且，题目给定了权值之和 $s$，所以只需要考虑把权值之和平分给叶子节点即可。

寻找叶子节点的方法就是计算度，度为 1 的节点就是叶子节点。统计叶子节点数量，其他边权值为 0，最终的答案为 $\frac{2s}{cnt}$。

### 伪代码部分
```
输入并统计度：++ d[x], ++ d[y];
（xy 是树的一条边）
统计树的叶子结点个数：if (d[i] == 1)++ c;
（d[i] 记录的是 i 号节点的度，c记录叶子节点的数量）
cout << fixed << steprecision (12) << double (2.0 * s / c);
```

### 资料部分
不懂的同学可以去看看。

[树](https://baike.baidu.com/item/%E6%A0%91%E5%BD%A2%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/21506701)。

[权值](https://baike.baidu.com/item/%E6%9D%83%E5%80%BC/170585?anchor=2#2)。

[叶子结点](https://baike.baidu.com/item/%E5%8F%B6%E5%AD%90%E7%BB%93%E7%82%B9)。

[树的度](https://answer.baidu.com/answer/land?params=4Zl%2FCHhQMXzgalRJiaszMbOLUTfMeKKCO4MGwJpCsoNEuqbzE%2Bn9YNnHgpVOBw%2FXUgX2T9g3KcKV3GybMKpd880yvE3dxCEt7S8XElbs6xjv%2FdNxe7offsYCIQQJNrUwUm5yFwYHI6plxnVAHNjWMuB1pz%2BFO1PF4lcenoHaEIxcm1m7ZI2OBmPCUFE%2B6l3IpZXjyJf8QjW5TUARYm3J4g%3D%3D&from=dqa&lid=bf8d540f006fcfbb&word=%E6%A0%91%E7%9A%84%E5%BA%A6%E6%80%8E%E4%B9%88%E7%AE%97)。

---

## 作者：GoodLuckCat (赞：1)

这是一篇适合新手阅读的题解，~~因为我就是新手~~。

前置知识：树的直径是什么？

>树上任意两节点之间最长的简单路径即为树的直径。

了解了这个概念后再来看题目。

分配边权时，要注意 **每一条连接叶子节点的边的边权要最大。**

为什么呢？

假如每一条连接叶子节点的边的边权不是最大的，那么在中间“过路”的边的边权就得变大。

但是，会有很多条直径经过这条“过路”的边，比如样例二中连接节点 $2$ 和节点 $5$ 的边就是“过路”的边。

如果“过路”的边的边权变大，那么会导致树的直径增加。这就导致答案不是最优解。

所以我们可以想到，将给出的 $s$ 平均分给每一条连接叶子节点的边。

假如题目给出的树有 $x$ 个叶子结点，那么我们的构造方法是：

- 每一条连接叶子节点的边的边权均为 $\frac{s}x$。

- 其余的边的边权均为 $0$。

那么此时，树的直径为 $\frac{2s}x$。是最小的。

所以代码就出来了。

一开始 WA 在第八个点，后来看了题解才发现精度问题。

```cpp
#include<iostream>
#include<iomanip>
using namespace std;
int a,b[100001];
int main()
{
    int n,s;
    cin>>n>>s;
    for(int i=1;i<=n-1;i++)
    {
        int x,y;
        cin>>x>>y;
        b[x]++;
        b[y]++;
    }
    for(int i=1;i<=n;i++)if(b[i]==1)a++;
    double aa=a,ss=s;
    cout<<fixed<<setprecision(8)<<ss*2/aa;
    return 0;
}
```

纪念一下我的第一百道绿题。（全是水的）

---

## 作者：_Lazy_whr_ (赞：0)

简单分析一下，由于要求的是数的直径，所以叶子结点对其的影响绝对是最大的，所以只需要将 $s$ 平摊给连接叶子结点的边即可。

注意其他节点都可以赋值为 $0$，此时答案就是 $\frac{2s}{cnt}$。

可以用统计度数的方法来判断一个点是不是叶子结点。~~一开始还用了 DFS~~。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define x0 x00
#define x1 x10
#define y0 y00
#define y1 y10
#define rep(i, l, r, x) for (int i = l; i <= r; i += x)
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20), stdin), p1 == p2) ? EOF : *p1++)
// #pragma GCC target("avx")
// #pragma GCC optimize(3,"Ofast","inline")
namespace FastIO {
	char buf[(1 << 20)], *p1, *p2;
	char pbuf[(1 << 20)], *pp;
	inline int read() {
		int x = 0, f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	
	template <typename T> inline void read (T &x) { x = read(); }
	
	template <typename T, typename... Args> inline void read (T &x, Args &...x_) {
		read (x);
		read (x_...);
	}
}

namespace Constants {
	const int INF = 1e18;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-7;
	const double PI = acos (-1);
}

using namespace std;
using namespace FastIO;
using namespace Constants;

int n, s;
int cnt[200010];

void Solve() {
	read(n, s);
	for (int i = 1; i < n; i++) {
		int x = read(), y = read();
		cnt[x]++;
		cnt[y]++;
	}

	int _ = 0;
	for (int i = 1; i <= n; i++) _ += (cnt[i] == 1);
	printf("%.15lf\n", s * 2.0 / _); // 多保留几位小数心里不慌
}

main() {
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr); cout.tie(nullptr);
	
	int T = 1;
	// T = read();
	while (T--) Solve();

	return 0;
}

```

---

## 作者：ChpyX2 (赞：0)

# CF1085D Minimum Diameter Tree 题解

比较水的一道绿题。

观察样例可以发现，边权都平分在叶子节点唯一的一条连边上，由此~~猜到~~联想到可以把贪心地将边权**全部平均分配到这些边上**，这样写出来就能过了。

### 如何证明：
先来一张图方便理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/l7ipnt16.png)

利用反证法：假设按上述做法分配边权后可以至少修改一次并得到更好选择。

那么一定会需要把至少一条在叶子节点上的边的边权减小，并且增加另一条边的边权。

分情况讨论增加边权的那一条边：

- 若这条边也连接叶子节点，显而易见的，从这出发，一定能找到另外一个连边未减小的叶子节点，那么此时这条边是直径，且长度相较于原答案会增加。

- 若这条边不连接叶子节点，更加显而易见的，一定有一条边穿过连边边权未减小的两个叶子节点，那么此时这条边是直径，且长度相较于原答案也会增加。

- 特殊考虑一下只有一条边的情况，显而易见满足之前所述规律。

所以~~显而易见的~~综上所述，把边权平均分配到叶子边上就行。

### 细节：
- 要求误差在 $10^{-6}$ 以内，所以输出要记得改一下。
 

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int d[maxn],u,v,n;
double s,c;
int main(){
    cin>>n>>s;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        d[u]++;
        d[v]++;//计算度数
    }
    for(int i=1;i<=n;i++)if(d[i]==1)c++;//度数为1的就是叶子节点,相应的有一条叶子边
    printf("%.10f",s/c*2);
    return 0;
}
```

--------

**Written by ChpyX2**

---

## 作者：clownor (赞：0)

题意就是说给定一棵树的形态和边权和，你要分配边权以最小化直径。

要求边权和全部分配完，但**不要求**边权不为零，可以分配**非整数**边权。

是一道结论题捏。

首先可以理解到，所有直径的长度均相等为最优解。

感性分析一下，发现对直径可能产生贡献最小的是有一端连向叶子的边。

所以猜一个结论，除了这类边，其他边权值均为零，对这类边权平均分配，任何一条直径都是由叶子连向叶子的，所以长度均相同。

很好，发现这个结论可以过样例，甚至你大胆来一发可以过，但是怎么证呢？

这里称连向叶子的为一类边，否则为二类边。

首先讨论可以发现当不存在任何两对叶子，使得他们有一条重合的二类边时，这个结论就成立。

详细讲一下就是对现在所有的叶子对，如果把其中一个一类边的一部分权调整到一条二类边上，如果这条二类边在另一对叶子间的路径上，那么直径会变大，否则也仅仅是不变而已。

这样就证明了你有链和菊花图成立。

接下来需要讨论的情况为存在两对叶子，其中一对经过某条二类边而另一对不经过。

设存在一种方案有一条二类边非零。

如果这条二类边只影响一对叶子，那么这就是链或菊花图了。

所以这张图有至少三个点，在这时所有二类边至少影响不到一对叶子。

把这条边断开，一定有一侧的树的叶子节点多于一。

令左边为较多点的一边，从左边选出2个点 $x,y$，右边选出一个 $z$。

发现有

$$dis_{x,y}=A_x+A_y,dis_{x,z}=A_x+A_z+B,dis_{y,z}=A_y+A_z+B$$

由最开始的直径均相等的结论，他们是相等的，解方程得 $B=0$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define int long long
using namespace std;
int read()
{
	int fl=1,v=0;
	char c=getchar();
	while (c!='-'&&(c<'0'||c>'9')) c=getchar();
	if (c=='-')
	{
		c=getchar();
		fl=-1; 
	}
	while (c>='0'&&c<='9')
	{
		v=v*10+c-'0';
		c=getchar();
	}
	return v*fl;
}
int n,s,du[100005];
signed main()
{
	n=read(),s=read();
	for (int i=1;i<n;i++)
	{
		int x=read(),y=read();
		du[x]++,du[y]++;
	}
	int cnt=0;
	for (int i=1;i<=n;i++) if (du[i]==1)
	{
		cnt++;
	}
	double ans=2.0*s/cnt;
	printf("%.10lf",ans);
	return 0;
}
```

---

