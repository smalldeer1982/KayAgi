# [ARC161D] Everywhere is Sparser than Whole (Construction)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc161/tasks/arc161_d

頂点集合が空でない単純無向グラフの**密度**を $ \displaystyle\frac{(辺数)}{(頂点数)} $ と定義します．

正整数 $ N,\ D $ が与えられます． $ N $ 頂点 $ DN $ 辺の単純無向グラフ $ G $ であって，以下の条件を満たすものが存在するかどうかを判定し，存在するならそのようなグラフを $ 1 $ つ求めてください．

**条件:** $ G $ の頂点集合を $ V $ とする． $ V $ の任意の空でない**真**部分集合 $ X $ に対して，$ X $ による $ G $ の誘導部分グラフの密度は $ D $ **未満**である．

 誘導部分グラフとは

 グラフ $ G $ の頂点部分集合 $ X $ に対して，$ X $ による $ G $ の**誘導部分グラフ**とは，「頂点集合が $ X $ であり，辺集合が『 $ G $ の辺であって $ X $ 内の $ 2 $ 頂点を結ぶもの全体』であるグラフ」を指します． 上記の条件では，頂点部分集合として空集合でも全体でもないもののみを考えていることに注意してください．

## 说明/提示

### 制約

- $ N\ \geq\ 1 $
- $ D\ \geq\ 1 $
- $ DN\ \leq\ 5\ \times\ 10^4 $
 
### Sample Explanation 1

出力されたグラフの頂点集合は $ \{1,\ 2,\ 3\} $，辺集合は $ \{(1,\ 2),\ (1,\ 3),\ (2,\ 3)\} $ であり，単純です． 頂点集合の空でない真部分集合 $ X $ としては $ \{1\},\ \{2\},\ \{3\},\ \{1,\ 2\},\ \{1,\ 3\},\ \{2,\ 3\} $ の $ 6 $ 通りが考えられ， - $ X\ =\ \{1\},\ \{2\},\ \{3\} $ のとき，$ X $ による誘導部分グラフの辺集合は空集合であり，その密度は $ \displaystyle\frac{0}{1}\ =\ 0 $， - $ X\ =\ \{1,\ 2\},\ \{1,\ 3\},\ \{2,\ 3\} $ のとき，$ X $ による誘導部分グラフの辺集合はそれぞれ $ \{(1,\ 2)\},\ \{(1,\ 3)\},\ \{(2,\ 3)\} $ であり，いずれも密度は $ \displaystyle\frac{1}{2} $ です． 全ての場合に対して誘導部分グラフの密度は $ D\ =\ 1 $ 未満であり，このグラフは条件を満たします．

### Sample Explanation 2

$ 4 $ 頂点 $ 8 $ 辺の単純無向グラフは存在しません．

## 样例 #1

### 输入

```
3 1```

### 输出

```
Yes
1 2
1 3
2 3```

## 样例 #2

### 输入

```
4 2```

### 输出

```
No```

# 题解

## 作者：incra (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc161_d)
### 前言
第一次做出 ARC 的 D 题欸。

updata 2023/6/6 17:40 修正一个明显的错误。

### 题解

首先，不难发现，若 $d\times n>\dfrac{n\times(n-1)}{2}$ 的话，一定无解。

接着，可以证明出，只要 $d\times n\le\dfrac{n\times(n-1)}{2}$，就一定有解。

**证明：**

设一个点 $x$ 的度为 $d_x$，令 $mind = \displaystyle\min_{1\le i\le n}\{d_x\}$。

则若要使有解，就必须满足 $\dfrac{n\times d - mind}{n - 1}<d$，即 $mind > d$，等价于删除任意一个点后的图密度必须小于原来的图，也就是说，构造出的方案中，必须满足每一个点的度大于 $d$。

不难想到一种可以构造一个每一个点的度相同的图，如何构造？其实，这里可以用迭代 $d$ 轮的想法，每一次迭代，把每一个点的度加上相同的一个数。这里，我想到了一种方法，假设在第 $k$ 次迭代，那么要连的 $n$ 对点分别为 $(i,(i + k - 1) \bmod n + 1)_{1\le i \le n}$，每次迭代，每一个点的度加上 $2$，最终每一个点的度为 $2\times d$，满足原始条件，故得证。
### 代码
```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair <int,int> PII;
int n,d;
int main () {
	cin >> n >> d;
	if (d * n > (LL)n * (n - 1) / 2) {
		puts ("No");
		return 0;
	}
	puts ("Yes");
	for (int len = 1;len <= d;len++) {
		for (int i = 1;i <= n;i++) {
			int ni = (i + len - 1) % n + 1;
			cout << i << ' ' << ni << endl;
		}
	}
	return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

构造题，但是结论比较好蒙，有一种感性的理解方式。

首先 $nd\le \frac{n(n-1)}{2}$ 才有解，不然根本连不出来 $nd$ 条边的无向图。

我们希望图是较为平衡的，具体表现在每个点度数相同，构造方式也是容易的，每个点向其编号后 $d$ 个点连边即可（超出 $n$ 则从 $1$ 开始），显然在 $nd\le \frac{n(n-1)}{2}$ 的情况下，是不会连出来重边的。

如果图不是那么平衡的话，即使某些子图的密度比上述构造的图优秀，但我们也一定可以找到一个子图使得密度比上述构造的图劣，此时是有可能不合法的。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back

#define N 202502
#define int long long

int n,d;

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>d;

    if(n*d>n*(n-1)/2){
        cout<<"No";
        return 0;
    }

    cout<<"Yes\n";
    rep(i,1,n){
        rep(j,1,d){
            int u=(i+j-1)%n+1;
            cout<<i<<' '<<u<<"\n";
        }
    }

    return 0;
}
```

---

## 作者：FreedomKing (赞：0)

### 题意

设一个图的点数为 $vertices$，边数为 $edge$，定义一个图的密度为 $\frac{edge}{vertices}$。

现给出 $N$ 和 $D$，请问是否可以构造一个有 $N$ 个点和 $N\times D$ 条边的简单无向图 $G$，满足对于任何一个非空且不等于 $G$ 的点集合连接的所有边的数量严格小于 $D$。如果可以，输出构造出的图。

------------

### 思路

简单构造题，稍微难在于不可构造条件和题目描述弯弯绕绕。

首先搞定不可构造的情况。必然的，对于一个 $N$ 个点的图最多只能有 $\frac{n(n-1)}{2}$ 条边，所以对于 $N\times D>\frac{n(n-1)}{2}$ 不可能存在任何一种构造方式是成立的，即 $D>\frac{n-1}{2}$ 是不可构造的。

构造就简单了，先考虑把点按照环摆放，尽可能使每个点主动连接的边的数量平衡（“主动连接”指对于一条边 `i j` 中的 `i`），也就是说对于 $N\times D$ 条边，每个点要主动连接 $D$ 条边，我们就直接将 $N_i$ 连接它后面的 $D$ 条边，注意一下边界就行了。

------------

### AC Code
```
#include<bits/stdc++.h>
using namespace std;
int n,d;
int main(){
	cin>>n>>d;
	if(d>(n-1)/2){
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++)
		for(int j=1;j<=d;j++)
			cout<<i<<' '<<((i+j>n)?(i+j-n):(i+j))<<'\n';
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 题意
给出 $n$ 和 $d$，表示有一个 $n$ 个点 $nd$ 条边的图，我们设 $E$ 为构造图的点非空真集，加入点权之间相连的边，我们设 $D$ 为这个子图的 $\frac{\text{边的个数}}{\text{点的个数}}$，若存在一个图满足所有的 $D$ 都小于 $d$，就输出 `Yes`，并输出图，否则输出 `No`。
# 思路

我们可以直接把边分布在每两个点之间，让 $D$ 降得最低，我们要加 $nd$ 条边，然后可以先枚举 $n$ 个点，然后将它和后面的 $d$ 个点全部连边，我举一个例子，当 $n$ 等于 $5$，$d$ 等于 $2$ 时，可以建下面这一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/3f9bi147.png)

发现这样建出来的图是对的。

我们在考虑什么时候输出 `No`，当 $\frac{(n-1)}{2}$ 大于 $d$ 的时候，无法连接 $nd$ 条边。

这里给出 $2$ 种理解方式，因为一个图最多有 $\frac{n(n-1)}{2}$ 条边，我们要选 $nd$ 条边，那么稍微移项可得 $d \le \frac{n-1}{2}$，另外一种是每一个点最多能连接 $n-1$ 条边，其中有 $d$ 条边是由前面 $d$ 个点指向它的，剩下还有 $d$ 个点是它要只想别的点的，那么就是 $2d\le n-1$ 两边相除可以得到同样的式子。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, d;
	cin >> n >> d;
	if (d > (n - 1) / 2) {
		cout << "No\n";
		return 0;
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= d; j++) {
			int x = i, y = (i + j) % n;
			if (y == 0) {
				y = n;
			}
			cout << x << " " << y << "\n";
		}
	}
	return 0;
}
```

---

## 作者：__stick (赞：0)

## 题意

构造一张 $n$ 个点的简单无向图，满足每个导出子图（不包含原图）的边数比点数值严格小于 $D$。

## 思路

首先一个感觉是越大的图越难满足，所以我们先考虑大小为 $n-1$ 的导出子图，假设删除的点度数为 $x$。

则我们可以列出不等式：
$$
\frac{nD-x}{n-1}< D
$$
                   
即：$x>D$。
 
也就是说每个点的度数必需要大于 $D$。
  
然后考虑删去两个点，同理（此处假设两个点之间有边，没有边同理）：

$$
\frac{nD-x-y+1}{n-2}<D$$
               
移项可得：
                         
$$
                         x+y-1>2 D
$$
此处发现只要 $x> D ,y> D$ 则 $x+y-1>2D$ 一定满足。

然后猜测每个点度数都是 $2D$ 的联通图满足条件，如果 $2D>n-1$ 显然无解，因为不论如何更改都会有点度数大于等于 $2D$，这样就不存在简单图了。

然后我们分析一波，一个大小为 $m$ 的完全图想要合法则：$\frac{m(m-1)/2}{m}<D,m<2D+1$。

而对于 $m>2D$ 比值最大是：$\frac{2dm/2}{m}=d$。是这个最大值是取不到的，因为我们构造出来的图是联通的，当前子图和剩下的图之间一定有至少一条边，则最大值取不到，所以合法。


所以我们证明了构造方式合法。

实现比较简单，每个点向后面 $D$ 个点连边，即满足两个条件。







---

