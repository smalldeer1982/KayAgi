# Great Graphs

## 题目描述

Farmer John has a farm that consists of $ n $ pastures connected by one-directional roads. Each road has a weight, representing the time it takes to go from the start to the end of the road. The roads could have negative weight, where the cows go so fast that they go back in time! However, Farmer John guarantees that it is impossible for the cows to get stuck in a time loop, where they can infinitely go back in time by traveling across a sequence of roads. Also, each pair of pastures is connected by at most one road in each direction.

Unfortunately, Farmer John lost the map of the farm. All he remembers is an array $ d $ , where $ d_i $ is the smallest amount of time it took the cows to reach the $ i $ -th pasture from pasture $ 1 $ using a sequence of roads. The cost of his farm is the sum of the weights of each of the roads, and Farmer John needs to know the minimal cost of a farm that is consistent with his memory.

## 说明/提示

In the first test case, you can add roads

- from pasture $ 1 $ to pasture $ 2 $ with a time of $ 2 $ ,
- from pasture $ 2 $ to pasture $ 3 $ with a time of $ 1 $ ,
- from pasture $ 3 $ to pasture $ 1 $ with a time of $ -3 $ ,
- from pasture $ 3 $ to pasture $ 2 $ with a time of $ -1 $ ,
- from pasture $ 2 $ to pasture $ 1 $ with a time of $ -2 $ .

 The total cost is $ 2 + 1 + -3 + -1 + -2 = -3 $ .In the second test case, you can add a road from pasture $ 1 $ to pasture $ 2 $ with cost $ 1000000000 $ and a road from pasture $ 2 $ to pasture $ 1 $ with cost $ -1000000000 $ . The total cost is $ 1000000000 + -1000000000 = 0 $ .

In the third test case, you can't add any roads. The total cost is $ 0 $ .

## 样例 #1

### 输入

```
3
3
0 2 3
2
0 1000000000
1
0```

### 输出

```
-3
0
0```

# 题解

## 作者：Reobrok_Kk (赞：12)

### 一道思维题

其实这是一道很水的题，就是思维难度比较大一点。

-----------------------

题目大意：给你已经求出的最短路数组，求在不改变最短路情况下，使得建出来的**有向图**的边权之和最小。

可以有**负权边**，但不可以有**负环**与**重边**

一拿到这题我还是比较蒙的，竟然想到用前缀和（也不知道我怎么想的），然后测了一下样例，全错。

心情复杂.jpg

后来经 $CZX$ 大佬指点，竟想出了正解！

--------

### 思路

因为我们要使边权之和最小，所以尽量少点正权边，因此我们选择让建完正权边后的图形成一条链，可以直接将最短路从小到大排序，然后每相邻的两点建一条边权为 $dis[i] - dis[i - 1]$ 的正权边。

加负权边时，可以发现每两点之间都可以加一条负权边，然后这里可以运用贪心，使加的边权值最小。

例：

给出的 $dis$ 数组为 $0, 2, 4, 6$ 。

先建正权边。

![](https://cdn.luogu.com.cn/upload/image_hosting/upyj7pb1.png)

建好正权边后再建负权边。

![](https://cdn.luogu.com.cn/upload/image_hosting/aesqfwdm.png)

然后暴力查询。

但是：



可是这样做特别麻烦，并且时间复杂度爆炸，我们只能想其他优化的方法。

-------

### 优化

仔细观察可以发现，答案只能是负数或 $0$ ，而且每一条边都对答案有一定的贡献。那我们就可以不用建负权边，直接拿正权边一条边一条边来处理，可以很好地降低代码的复杂以及时间复杂度。

很显然，每条边对于答案的贡献为：经过这条边的**所有负权边的数量** $\times$ **权值**。但是我们没建负权边，怎么算数量呢？

其实很简单，这条边之后每一个点都会往这条边前面每一个点做一条负权边，也就是说：数量 $=$ 这条边之前的点 $\times$ 这条边之后的点。

因为要求和，所以还需要减去正权边，最后取相反数就可以了。

那么，每条边对答案的贡献为 $edge[i] \times (n - i + 1) \times (i - 1) - edge[i]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/x7sqtjaj.png)

为了使得答案更好统计，我们设 $edge[i]$ 为从点 $i - 1$ 到点 $i$ 的长度。 

上图中，$i = 3, n = 4$，那么经过 $edge[3]$ 边的数量则为 $(4 - 3 + 1) \times (3 - 1) = 4$ 条，分别是 $3 \to 1, 3 \to 2, 4 \to 1, 4 \to 2$。

最后我们得出答案为：

$$\sum\limits_{i=2}^n edge[i] \times (n - i + 1) \times (i - 1) - edge[i]$$

------

### 代码

#### 核心代码

```cpp
int ans = 0;
for (int i = 2; i <= n; ++i)
    ans += edge[i] * (n - i + 1) * (i - 1) - edge[i];
```

#### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long //long long 好习惯，以防爆int（就是有点耗内存） 
using namespace std;
inline int read() {
	int x = 0;
	bool flag = 1;
	char c = getchar();
	while (!isalnum(c)) {
		if (c == '-')
			flag = 0;
		c = getchar();
	}
	x = c - '0';
	c = getchar();
	while (isalnum(c)) {
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (flag) return x;
	return ~(x - 1);
} 
inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = ~(x - 1);
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
//上面快读快输模板（其实可以不用打，但是已经成了习惯）
//加了位运算（虽然没什么用） 
const int N = 1e5 + 5;
int dis[N], edge[N]; //dis[]为读入的最短路径，edge[]为建完图后每条边的长度（有点像差分数组） 
signed main(){
	int T = read();
	while (T--) { //T组测试数据（dis[]要用的会完全覆盖，所以不用清空） 
		int n = read();
		for (int i = 1; i <= n; ++i)
			dis[i] = read();
		sort(dis + 1, dis + n + 1); //从小到大排序 
		for (int i = 2; i <= n; ++i)
			edge[i] = dis[i] - dis[i - 1]; //预处理出每条边 
		int ans = 0;
		for (int i = 2; i <= n; ++i)
			ans += edge[i] * (n - i + 1) * (i - 1) - edge[i]; //计算每条边对答案的贡献 
		write(~(ans - 1)); //答案为负数或0，直接取相反数（位运算取相反数，虽然也没什么用） 
		puts(""); //换行 
	}
	return 0;
}
```

---

## 作者：Kevin_Zhen (赞：3)

题目链接 [$\mathfrak{CF1540A}$](https://www.luogu.com.cn/problem/CF1540A)。  
[可能更好的阅读体验](https://www.luogu.com.cn/blog/150cm/solution-cf1540a)。

### 解题思路
对于任意一条路径 $1\rightarrow i$ 上的一个结点 $j$，我们设 $j$ 到 $i$ 的距离为 $w$，那么我们可以连一条反向边 $i\rightarrow j$，权值为 $-w$。这样，$j$ 到 $i$ 的路径以及新加的反向边构成了一个总权值为 $0$ 的环，使得我们在不出现负环的前提下尽可能减小了权值总和。

接下来的问题是图的构造。因为 $d$ 数组存储的顺序不会影响图的构造，为了方便下面的讨论，不妨先将 $d$ 升序排序。  
对于一个点 $i$，我们有以下两种选择：  
1. 直接连在结点 $1$ 后面，连边权值为 $d_i$。
2. 连在已有的一条链之后。设链的末尾结点为 $j$，则连边的权值为 $d_i-d_j$。

我们需要考虑的是哪种构造方式能够尽可能多地连出反向边。可以发现，选择一只能增加一条权值为 $-d_i$ 的边，而选择二使得 $i$ 不仅能与 $1$ 连边，还能与链中结点连边。所以我们应将图构造成一条链。

最后的问题是权值的累加。设我们当前走到的结点为 $i$，上一个结点为 $i-1$，边 $(i-1)\rightarrow i$ 的权值为 $w$。对于正向边权值的累加，直接加上 $w$ 即可，难点在于反向边。

考虑当前边的反向边 $i\rightarrow (i-1)$ 对答案的贡献次数。结点 $i$ 会与结点 $1,2,\cdots,(i-1)$ 分别连边，所以 $i$ 会将 $-w$ 累加 $i-1$ 次。而结点 $i$ 之后的点也会分别与之前的 $i-1$ 个点连边，所以每个点都会贡献 $i-1$ 次。即，$i,(i+1),\cdots,n$ 这 $n-i+1$ 个点，每个点都会将当前反向边覆盖 $i-1$ 次。所以当前反向边被覆盖的次数为 $(n-i+1)\times (i-1)$ 次。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int maxn = 1e5 + 10;

int T, n, d[maxn];
ll ans;

int main() {
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &d[i]);
		sort(d + 1, d + 1 + n);
		for (int i = 2; i <= n; ++i) {
			int w = d[i] - d[i - 1];
			ans += w + (-1ll) * w * (n - i + 1) * (i - 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Zheng_iii (赞：2)

## 思路
CF 思维题。

因为我们要让边权值最小，所以可以利用贪心思想先将数组 $d$ 进行升序排序。

然后再预处理出每一条边的权重。

其次我们来想一下如何处理答案，因为这道题说图中不能出现负环和重边，所以我们可以通过加反方向负边的方法来解决这道题。

因为对于一条边，这条边之后的所有点都会与这条边之前的点连负边，它们都会经过这条边，我们就可以把这条边之前的点数与这条边之后的点数相乘，得到所有经过这条边的负边数量。

得出核心代码。


```cpp
for(int i = 2; i <= n; i++){
    e[i] = d[i] - d[i - 1];
    ans += e[i] * (n - i + 1) * (i - 1) - e[i];//记得加上原边的权值
}
```
## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+10;
int d[N],e[N],n,ans,T;

int main(){
	// freopen("text.in","r",stdin);
	// freopen("text.out","w",stdout);
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
	cin>>T;
	while (T--){
        cin>>n;
        ans = 0;
        for (int i = 1; i <= n; i++){
            cin>>d[i];
        }
        sort(d + 1, d + n + 1);
        
        for(int i = 2; i <= n; i++){
            e[i] = d[i] - d[i - 1];
            ans += e[i] * (n - i + 1) * (i - 1) - e[i];//记得加上原边的权值
        }
        
        cout <<-ans<< '\n';
    }
	return 0;
}

```

---

## 作者：_xbn (赞：2)

提供一种比较好想的思路，首先可以把每个点到点 $1$ 的距离排序，保证路径升序。

然后我们要使总和最短，我们发现，每个点都可以向之前的点连一条负权边，权值为之前的点到这个点的距离，于是我们可以预处理出前缀和，之后按照上述方法计算。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200002;
int a[N], m, n, k, p, q, ans, sum, tot, cnt, b[N];
inline int read()
{
    register int x = 0, f = 1;
	char ch = getchar();
    while(!isdigit(ch))
	{
		if(ch == '-') f=-1;
		ch = getchar();
	}
    while(isdigit(ch))
	{
		x=(x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
    return x * f;
}
signed main() 
{
	int T = read();
	while (T--)
    {
        n = read();
        sum = 0;
        for (int i = 1; i <= n; i ++ )
        {
            a[i] = read();
            sum = max(sum, a[i]);
        }
        sort(a + 1, a + n + 1);
        ans = sum;
        
        for(int i = 2; i <= n; i++)
        {
            b[i] = a[i] - a[i - 1];
            
        }
        for(int i = 2; i <= n; i++)
        {
            ans = ans - b[i] * (n - i + 1) * (i - 1);
        }
        cout << ans << endl;
    }
	return 0;
}
```


---

## 作者：Gokix (赞：2)

[CF1540A](https://www.luogu.com.cn/problem/CF1540A)

**upd on 21/8/3：修正评论区中提出的一些错误。**

------------

题目大意：给定从节点 1 出发到所有节点的最短路，求构造一个图，使得满足最短路的前提下所有边权和最小。

---------

首先，有一个显然的结论：**最终答案不大于 0**。

我们可以用一种简单的构造造出答案是 0 的情况。构造方法就是从源点向每个节点按边权为最短路连一条边，并按边权为最短路的相反数连一条反边。如此构造答案为 0，且显然合法。（感谢 [wxy_](https://www.luogu.com.cn/user/317459) 同学指出之前的证明有误）

------------

然后，有一个不太好想的结论：构造的负权边只需满足下式，即可保证所有负权边和最小且满足题意。

在 $d$ 序列**从小到大排序后**，连负权边满足 边权 $w=d_i-d_j,1 \le i<j \le n$，即可使所有负权边和最小且满足题意。

为什么这是合法的？

考虑连接负权边时需要注意什么：**不能出现负环**。

而上面那个解法的负权边集是个 DAG，自然不可能出现负环。重边就更不可能了。

如何证明其边权和最小呢？

考虑对于每一条边权和为 $w$ 正向路径（注意不是正向边） $i \to j$，你需要把所有的 边权和为 $-w$ 的反向路径 $j \to i$ 都构造出来。而上式恰好满足这个最优情况。

------------

既然最优负权边和最小值是定值，那么我们只需要使正向边之和最小即为答案最优情况。

那么就显然了，在 $d_i$ 从小到大排序后，顺序连边形成一条链，边权即相邻两点 $d$ 值之差。

于是这题构造方法就结束了。

------------

但是你这时候发现一个问题：正向边权和可以 $O(n)$ 求，反向边权和这个是什么鬼鬼。

通过手玩，你发现每条反向边经过次数并不相同，而且看上去没有一点规律。

那就打表来看看！

打出来的表长这个样子：

```
n
2: 1
3: 2  2
4: 3  4  3
5: 4  6  6  4
6: 5  8  9  8  5
7: 6  10 12 12 10 6
8: 7  12 15 16 15 12 7
9: 8  14 18 20 20 18 14 8
10:9  16 21 24 25 24 21 16 9
11:10 18 24 28 30 30 28 24 18 10
12:11 20 27 32 35 36 35 32 27 20 11
13:12 22 30 36 40 42 42 40 36 30 22 12
14:13 24 33 40 45 48 49 48 45 40 33 24 13
15:14 26 36 44 50 54 56 56 54 50 44 36 26 14
```

这是什么？

横着看是一个回文单边二阶等差数列（感谢 [⚡LYR_⚡](https://www.luogu.com.cn/user/110319) 同学的提醒），但求起来有点麻烦。可是你一竖着看……

等差数列！

$i$ 表明了公差，$n-i+1$ 表明了项数。

然后这题就做完了。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

long long t,n,a[100010],b[100010],ans;

long long calc(long long x,long long y){
	long long gc=y,xs=x-y+1;
	return gc*xs-1;
}

int main(){
	long long i,j,u,v;
	cin>>t;
	while(t--){
		ans=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		cin>>n;
		for(i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		for(i=1;i<=n;i++){
			b[i]=a[i]-a[i-1];
		}
		for(i=1;i<=n;i++){
			ans+=(b[i]*calc(n-1,i-1));
		}
		cout<<-ans<<endl;
	}
	return 0;
}
```

---

## 作者：HEIMOFA (赞：0)

用边来计算贡献其他题解已经讲的很清楚了，我在这里讲一下用点来计算贡献的方法。

首先还是要排序，使得后面的比前面的要大，形成一条链，由于无论交换任意两项都会导致结果变差，所以现在是最优解。

因为任意一条图上的路径都可以从尾结点向头节点连一条边，由于不能出现负环，所以只能让这条边与路径权值和相加为 $0$。

直接计算肯定是会超时，对于以节点 $i$ 为尾节点的路径，其对答案的贡献应为以下这个式子：

$$ans_i=-(d_i-d_{last})\times last+ans_{last}$$

其中 $last$ 表示排序后上一个节点。

这个也很好理解，就是把以节点 $last$ 为尾节点的路径对答案的贡献全部加上 $last$ 到 $i$ 这条边的权值。

最后还要记得加上原本的权值和。
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+5;
ll d[N];

int main()
{
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        ll ans=0,last=0;
        for(int i=1;i<=n;i++) scanf("%d",&d[i]);
        sort(d+1,d+n+1);
        for(int i=1;i<=n;i++){
            ll tmp=-(d[i]-d[i-1])*(i-1)+last;
            ans+=tmp;
            last=tmp;
        }
        printf("%lld\n",ans+d[n]);
    }
    return 0;
}
```

---

