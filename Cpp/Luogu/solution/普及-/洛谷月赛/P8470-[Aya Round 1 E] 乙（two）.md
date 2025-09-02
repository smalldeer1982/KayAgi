# [Aya Round 1 E] 乙（two）

## 题目描述

定义由若干个边长为 $1$ 的正方体方块搭成的立体图形的「侧面积」为：对于所有方块，若它的前、后、左或右面没有紧贴着另一个方块，则该面计入侧面积。

维护长宽均无限的矩形地面，地面被划分为若干个边长为 $1$ 的格子。$n$ 次操作，每次选择一个格子 $(x_i,y_i)$ 在该位置向上堆叠 $z_i$ 个边长为 $1$ 的正方体方块。每次操作后，输出整个立体图形的「侧面积」。

## 说明/提示

### 样例 1 解释

如图所示，建立空间直角坐标系。注意这里的空间直角坐标系和数学上常用的略有区别，其 $x$-轴向南、$y$-轴向东、$z$-轴向上。限于技术原因，此处仅给出斜二测画法的立体图形，请读者自行脑补立体图形其他角度的模样。图中绿色部分即为立体图形的侧面。

第一次操作后，在 $(1,1)$ 位置放入了一个高度为 $2$ 的立体图形，侧面积为 $8$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ncd21a4f.png)

第二次操作后，在 $(1,3)$ 位置放入了一个高度为 $3$ 的立体图形，侧面积为 $12$。由于两个立体图形没有接触，因此可以直接加上第一次放上的立体图形的侧面积，总侧面积为 $20$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hl9f45rq.png)

第三次操作后，在 $(1,2)$ 位置放入了一个高度为 $4$ 的立体图形。由于某些面发生了接触，这些面对应的面积不计入侧面积的计算范围内。容易发现，总侧面积为 $26$。

![](https://cdn.luogu.com.cn/upload/image_hosting/j8x2mtc8.png)

---

再强调下，每次堆叠操作是在对应位置上再加上 $z_i$ 个方块。例如下图，是先执行了 $\verb!2 2 1!$，再执行了 $\verb!2 2 3!$ 的结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/3lgipl4z.png)

### 附加样例

- 样例 $3$ 见下发文件中的 $\textbf{\textit{two3.in/two3.ans}}$。该样例满足测试点 $4$ 的限制。
- 样例 $4$ 见下发文件中的 $\textbf{\textit{two4.in/two4.ans}}$。该样例满足测试点 $7$ 的限制。
- 样例 $5$ 见下发文件中的 $\textbf{\textit{two5.in/two5.ans}}$。该样例满足测试点 $10$ 的限制。
- 样例 $6$ 见下发文件中的 $\textbf{\textit{two6.in/two6.ans}}$。该样例满足测试点 $13$ 的限制。
- 样例 $7$ 见下发文件中的 $\textbf{\textit{two7.in/two7.ans}}$。该样例满足测试点 $20$ 的限制。

### 数据范围

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c||c|c|c|c|c|} \hline
\textbf{\textsf{\#}} & \bm{{n \le }} & \bm{{x,y \le}} & \bm{{z \le}} & \textbf{\textsf{特殊性质}} &
\textbf{\textsf{\#}} & \bm{{n \le }} & \bm{{x,y \le}} & \bm{{z \le}} & \textbf{\textsf{特殊性质}} \cr\hline
1 & 1 & 1 & 10 & - &
14 & 10^3 & 10^3 & 10^3 & - \cr\hline
2 & 2 & 5 & 10 & - &
15 & 10^3 & 10^3 & 10^9 & - \cr\hline
3 & 10 & 5 & 10 & - &
16 & 10^3 & 10^9 & 10^9 & - \cr\hline
4 & 100 & 100 & 100 & - &
17 & 10^5 & 10^9 & 10^9 & \textbf{AB} \cr\hline
5 & 10^3 & 10^3 & 10^3 & \textbf{AB} &
18 & 10^5 & 10^9 & 10^9 & \textbf{A} \cr\hline
6 & 10^3 & 10^3 & 10^9 & \textbf{AB} &
19 & 10^5 & 10^9 & 10^9 & \textbf{B} \cr\hline
7 & 10^3 & 10^9 & 10^9 & \textbf{AB} &
20 & 10^5 & 10^9 & 10^9 & - \cr\hline
8 & 10^3 & 10^3 & 10^3 & \textbf{A} &
21 & 2\times 10^5 & 10^9 & 10^9 & - \cr\hline
9 & 10^3 & 10^3 & 10^9 & \textbf{A} &
22 & 2\times 10^5 & 10^9 & 10^{12} & - \cr\hline
10 & 10^3 & 10^9 & 10^9 & \textbf{A} &
23 & 2\times 10^5 & 10^9 & 10^{13} & \textbf{A} \cr\hline
11 & 10^3 & 10^3 & 10^3 & \textbf{B} &
24 & 2\times 10^5 & 10^9 & 10^{13} & - \cr\hline
12 & 10^3 & 10^3 & 10^9 & \textbf{B} &
25 & 3\times 10^5 & 10^9 & 10^{13} & - \cr\hline
13 & 10^3 & 10^9 & 10^9 & \textbf{B} &&&&&\cr\hline
\end{array}
$$

- 特殊限制 $\bf A$：$\forall 1 \le i\le j \le n$，有 $x_i=x_j$。
- 特殊限制 $\bf B$：$\forall 1 \le i\le j \le n$，有 $(x_i,y_i) \ne (x_j,y_j)$。

对于 $100\%$ 的数据，保证 $1 \le n \le 3 \times 10^5$，$1 \le x,y \le 10^9$，$1\le z \le 10^{13}$。

## 样例 #1

### 输入

```
3
1 1 2
1 3 3
1 2 4```

### 输出

```
8
20
26```

## 样例 #2

### 输入

```
6
1 2 1
2 1 4
2 3 8
3 2 6
2 2 2
2 2 11```

### 输出

```
4
20
52
76
70
90```

# 题解

## 作者：chen_zhe (赞：20)

# 赛之河原的垒石人

如果立方体柱子互不相邻那么答案就是 $4\sum \limits_{i=1}^nz_i$。如何处理柱子有相邻的情况？

在堆叠立方体的时候即可去处理柱子相邻的情况。不妨设在这个无穷大平面上，每个点 $(x,y)$ 上立方体的高度是 $G[x][y]$。则对于当前的点 $(x,y)$ 以及所有四相邻的点 $(x',y')$ 以及高度 $G[x'][y']$，若 $G[x][y]<G[x'][y']$，则 $G[x][y]$ 的存在会让从平面到 $G[x][y]$ 这一高度上的侧面面积“无效”化，因而减掉这一部分面积，即 $2 \times \min(z,G[x'][y']-G[x][y])$。需要对 $z$ 取 $\min$ 是避免减去重叠部分过多。例如就堆叠一个方块，那显然就不必减掉相邻柱子高度差那么多的重叠面积。

而如何去维护 $G$ 数组呢？可以使用 map 套 map 解决，也可以将二维平面降维到一维（例如对于一个坐标 $(x,y)$，将其变成 $x \times 10^6+y$）后使用一个 `map<long long,long long>` 去解决。本题没有卡 `unordered_map`，但是你要是 `unordered_map` 套 `unordered_map` 会被卡死。

答案最大是多少？显然是所有柱子都不相邻且最高的时候产生，即 $4n\max(z_i)=1.2 \times 10^{19}$，需要开 unsigned long long 才能通过本题。

```cpp
#include <iostream>
#include <map>
using namespace std;
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
map <int,map<int,long long>> G;
unsigned long long ans;
int main()
{
    int n;
    cin >> n;
    for (int i=1;i<=n;i++)
    {
        int x,y;
        long long z;
        cin >> x >> y >> z;
        for (int j=0;j<4;j++)
        {
            int nx=x+dx[j],ny=y+dy[j];
            if (G[nx][ny]>G[x][y])
                ans-=2ull*min(z,G[nx][ny]-G[x][y]);
        }
        G[x][y]+=z;
        ans+=4ull*z;
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：FXT1110011010OI (赞：8)

$2022.9.25$ 更新了数组变量写错的地方

题目名为啥要改啊，原来不挺好的吗？

## 题目描述

定义由若干个边长为 $1$ 的正方体方块搭成的立体图形的「侧面积」为：对于所有方块，若它的前、后、左或右面没有紧贴着另一个方块，则该面计入侧面积。

维护长宽均无限的矩形地面，地面被划分为若干个边长为 $1$ 的格子。$n$ 次操作，每次选择一个格子 $(x_i,y_i)$ 在该位置向上堆叠 $z_i$ 个边长为 $1$ 的正方体方块。每次操作后，输出整个立体图形的「侧面积」。

## 具体思路

每次往格子 $(x_i, y_i)$ 上堆叠 $z_i$ 个边长为 $1$ 的正方体块，其实就是往格子 $(x_i, y_i)$ 上放一个高度为 $z_i$ 、顶面为 $1 \times 1$ 正方形的小长方体。为了方便描述，以下部分统称“小长方体”。

### 考虑增加部分

增加部分即为此次放入的小长方体的侧面积，也就是 $z_i \times 4$。

### 考虑重叠部分

我们用 $now$ 数组表示每个格子上堆叠起的长方体的高度。

对于小长方体的前、后、左、右面：

* 若没有相邻则跳过。
* 若有相邻，则让答案减去 $2 \times \min(z, \max(0, now_{tx, ty} - now_{x, y}))$ ，其中 $(tx, ty)$ 表示 $(x, y)$ 的四个相邻格子。根据定义，这里 $now_{tx, ty} - now_{x, y}$ 有可能为负，所以要与 $0$ 取 $\max$ 。还要 $\times 2$ 是因为 $(x, y)$ 和 $(tx, ty)$ 都包含重叠部分，要减两次。

### 注意事项

1. 本题的答案会爆 $\text {long~long}$，要开 $\text {unsigned~long~long}$。
2. 数组存不下坐标，代码中用的是 $\text {map}$，有其他方法欢迎评论区补充。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
map<PII, ll> now;

int main()
{
    int n;
    ull res = 0;
    scanf("%d", &n);
    while (n -- )
    {
        int x, y;
        ll z;
		scanf("%d%d%lld", &x, &y, &z);
		res += z * 4;
		for (int i = 0; i < 4; i ++ )
		{
		    int tx = x + dx[i], ty = y + dy[i];
		    res -= 2 * min(z, max(0ll, now[{tx, ty}] - now[{x, y}]));
		}
		now[{x, y}] += z;
		printf("%llu\n", res);
    }
    return 0;
}
```

这么水的题打比赛的时候竟然没打出来，还是太菜了，写篇题解纪念一下。

---

## 作者：wangzl (赞：3)

原题目好像是 `赛之河原的垒石人` ？
## 题目描述
定义由若干个边长为 $1$ 的正方体方块搭成的立体图形的「侧面积」为：对于所有方块，若它的前、后、左或右面没有紧贴着另一个方块，则该面计入侧面积。  
维护长宽均无限的矩形地面，地面被划分为若干个边长为 $1$ 的格子。$n$ 次操作，每次选择一个格子 $(x_i,y_i)$ 在该位置向上堆叠 $z_i$ 个边长为 $1$ 的正方体方块。每次操作后，输出整个立体图形的「侧面积」。
## 核心思路
每一次放入时先加上此次的总侧面积，再减去放入后与先前的立方体所重叠的区域，即是正确答案。其中，以下几点要注意：
- $1 \le x,y \le 10^9$, 二维数组要爆空间，这里用 `map` 和 `pair` 结合使用来代替二维数组；
- 本题最大 $\text{ans}$ 可以算到为 $4 \times n \times z$，其中 $1≤n≤3×10^5, 1\le z \le 10^{13}$， 所以 $\text{maxans} = 1.2e19$，爆 $\text{maxlonglong}$，要使用 `unsigned long long`，不然只能拿到 $96\text{pts}$，同时，`scanf` 和 `printf` 都要使用 `%llu`；
- 重叠时减去的面积要乘 $2$，因为是两个面互相遮挡。
## $\text{std}$:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;//一定要用ull
const int mod = 1e9 + 7;
int n;
ull ans;
map<pair<int, int>, long long>q;
 // y可能小于零，这里要与0取max值
long long Min(long long x,long long y) {return min(x, max(y, (long long)0)); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int x, y; long long z;
		scanf("%d%d%llu", &x, &y, &z);
		ans += z * 4,
		ans -= 2 * Min(z, q[{x - 1, y}] - q[{x, y}]),
		ans -= 2 * Min(z, q[{x, y - 1}] - q[{x, y}]),
		ans -= 2 * Min(z, q[{x + 1, y}] - q[{x, y}]),
		ans -= 2 * Min(z, q[{x, y + 1}] - q[{x, y}]);
		q[{x, y}] += z;
		printf("%llu\n", ans);
	}
    return 0; 
}
```
有任何疑问欢迎在评论中留言哦！

---

## 作者：南阳刘子骥 (赞：2)

对于这种题目我们一般没有什么特殊的算法，直接模拟即可。

每一次我们在加入新的方块时，我们先把这些方块的侧面积计入答案，然后枚举周围的四个格子内有没有重叠的部分，有的话就从答案里面减去两边重叠的面积。

再看一眼数据范围，$1 \leq x,y \leq 10^9$，我们不能直接在数组内存储，需要一发离散化。  
离散化好说，就用一个 `std::map<pair<int,int>,int>` 来存储即可。

参考代码：

注意答案可能会爆 `long long`。

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
ll h[N];
int idx = 0;
map<pair<ll, ll>, int>dic;
void write(__int128 res)
{
	if(res > 9)write(res / 10);
	putchar(res % 10 + '0');
}
int main()
{
	int n;
	scanf("%d", &n);
	__int128 res = 0;
	for(int i = 1; i <= n; i++)
	{
		ll x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		int now;
		if(dic.count(make_pair(x, y)))now = dic.find(make_pair(x, y))->second;
		else
		{
			dic.insert(make_pair(make_pair(x, y), ++idx));
			now = idx;
		}
		if(dic.count(make_pair(x, y - 1)))
		{
			int pos = dic.find(make_pair(x, y - 1))->second;
			res -= max(min(h[pos] - h[now], z) * 2, 0ll);
		}
		res += z;
		if(dic.count(make_pair(x, y + 1)))
		{
			int pos = dic.find(make_pair(x, y + 1))->second;
			res -= max(min(h[pos] - h[now], z) * 2, 0ll);
		}
		res += z;
		if(dic.count(make_pair(x - 1, y)))
		{
			int pos = dic.find(make_pair(x - 1, y))->second;
			res -= max(min(h[pos] - h[now], z) * 2, 0ll);
		}
		res += z;
		if(dic.count(make_pair(x + 1, y)))
		{
			int pos = dic.find(make_pair(x + 1, y))->second;
			res -= max(min(h[pos] - h[now], z) * 2, 0ll);
		}
		res += z;
		h[now] += z;
		write(res);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：BlanketRice (赞：1)

### 题意
定义由若干个边长为 $ 1 $ 的正方体方块搭成的立体图形的「侧面积」为：对于所有方块，若它的前、后、左或右面没有紧贴着另一个方块，则该面计入侧面积。

维护长宽均无限的矩形地面，地面被划分为若干个边长为 $ 1 $ 的格子。$ n $ 次操作，每次选择一个格子 $ (x_{i},y_{i}) $ 在该位置向上堆叠 $ z_{i} $
  个边长为 $ 1 $ 的正方体方块。每次操作后，输出整个立体图形的「侧面积」。
### 吐槽
太水了，太水了，简直太水了！！！！！
### 思路
直接用一个 `map` 记录每个格子的高度，即 $ G[x_{i}][y_{i}]=z_{i} $，然后就模拟。。。。。。

这里说一下这个侧面积的计算，对于不被遮挡的正方体，侧面积为所有侧面之和。当遇到遮挡，就在侧面积的和里减去遮挡高度的 $ 2 $ 倍，即 `ans -= 2 * min (G[x][y], G[x + dx[i]][y + dy[i]]);`。（设 `dx` 和 `dy` 表示 $ x $ 轴和 $ y $ 轴的偏移量。

这个题的坑点在于同一个点可以堆积，当相邻者高度大于自己本身的高度时，堆积后就会对表面积产生改变。所以我们需要判断的条件变成了 `ans -= 2 * min (z, G[x + dx[i]][y + dy[i]] - G[x][y]);`。解释：即只有相邻两者相差的高度会被改变。若堆积后还没超过的话，只改变当前堆积的高度 $ z_{i} $ 。

好了，思路讲完了。
### 代码
```cpp
#include <bits/stdc++.h>
#define space ' '
#define endl '\n'
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
int dx[5] = {114514, -1, 1, 0, 0}, dy[5] = {114514, 0, 0, -1, 1};
map < int, map < int, LL > > G;
ULL ans;
signed main () {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; ++ i) {
        int x, y;
        LL z;
        cin >> x >> y >> z;
        for (register int j = 1;j <= 4; ++ j) {
            int nx = x + dx[j], ny = y + dy[j];
            if (G[nx][ny] > G[x][y]) ans -= 2ull * min (z, G[nx][ny] - G[x][y]);
        }
        G[x][y] += z;
        ans += 4ull * z;
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Epoch_L (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P8470)
## Solution
本题是动态询问我们图形的侧面积，由于数据较大，肯定不能每一次暴力查找。所以我们考虑每一次的贡献。

假设说我们每一次都没有跟别的方块有冲突，那么每一次的贡献就是 $z\times 4$，然后我们要考虑重合的部分。

设放的当前方块原来有 $now$ 个，现在放上去 $z$ 个，开一个 map，看它前后左右是否有方块，如果有，设它的高度为 $h$，若 $h\le now$，则不会有冲突；若 $h>now$，则出现冲突的高度为 $\min(z,h-now)$，并且它会影响两个面，所以冲突的面积为 $2\times \min(z,h-now)$。

所以我们每次查询先加上 $z\times 4$，再减去冲突的面积就是答案。

注意由于最大的答案可能到 $1.2\times 10^{19}$，要开 unsigned long long。

## Code
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
map<pair<int,int>,int>mp;
void write(int x)
{
	char ch[20];
	int len=0;
	if(x<0)putchar('-'),x=-x;
	while(x)
	{
		ch[len++]=(x%10)^48;
		x/=10;
	}
	if(len==0)printf("0");
	while(len--)putchar(ch[len]);
	puts("");
}
main()
{
	int T,sum=0;
	read(T);
	while(T--)
	{
		int x,y,z;
		read(x);read(y);read(z);
		int now=mp[make_pair(x,y)];
		if(mp[make_pair(x+1,y)])
		{
			int k=mp[make_pair(x+1,y)];
			if(k>now)sum-=min(k-now,z)*2;
		}
		if(mp[make_pair(x-1,y)]&&x>0)
		{
			int k=mp[make_pair(x-1,y)];
			if(k>now)sum-=min(k-now,z)*2;
		}
		if(mp[make_pair(x,y+1)])
		{
			int k=mp[make_pair(x,y+1)];
			if(k>now)sum-=min(k-now,z)*2;
		}
		if(mp[make_pair(x,y-1)]&&y>0)
		{
			int k=mp[make_pair(x,y-1)];
			if(k>now)sum-=min(k-now,z)*2;
		}
		sum+=z*4;
		mp[make_pair(x,y)]+=z;
		write(sum);
	}
	return 0;
}
```

---

## 作者：lilong (赞：1)

### 题意
$n$ 次操作，每次在矩形地面上选择一个格子 $(x_i,y_i)$，在上面加上 $z_i$ 个方块。一个立体图形的「侧面积」定义为所有方块的前后左右面不紧贴着另一个方块，则该面计入「侧面积」。求每次操作后立体图形的侧面积。

### 分析
最直接的想法就是每加入 $z_i$ 个方块后，总的侧面积直接加上 $z_i \times 4$ 即可（前后左右共四个面）。但是，如果它的四周也有方块，那么这样就是不完整的，因此我们要分类讨论。我们不妨先设 $(x_i,y_i)$ 上原有 $a$ 个方块，周围的其中一个位置有 $b$ 个方块（其它位置同理），现要在 $(x_i,y_i)$ 的位置加入 $c$ 个方块。

- $a \le b$，$a+c \le b$

这种情况是原来比周围的低，增加了方块之后仍然比周围的低。增加了 $c$ 个方块后，那么两者紧贴的面积就增加了 $c$，即侧面积减少了 $c$。

- $a \le b$，$a+c >b$

这种情况是原来比周围的低，但加了 $c$ 个方块后，超过了周围的高度。因此很容易得知原来的高度差 $b-a$ 没了，然后产生了新的高度差 $(a+c)-b$，因此此时的侧面积要加上 $(a+c)-b-(b-a)$。

- $a > b$

这种情况不用多说了，原来已经比周围的高，那么加上 $c$ 个方块后也不会有方块紧贴着，所以侧面积直接加上 $c$ 即可。

### 实现

由于 $1 \le x,y \le 10^9$，普通的二维数组无法开到这么大的值域，因此我们可以用 map，map 里再开一个 map，就可以达到二维数组的效果（或者用 hash 也可以）。注意，求侧面积的变量要开 unsigned long long（极限数据 $3 \times 10^5 \times 10^{13} \times4 = 1.2 \times 10^{19}$，会爆 long long）。

具体实现细节见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned long long ans;
long long z;
int x,y;
map<int,map<int,long long> > a;
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		cin>>x>>y>>z;
		a[x][y]+=z;
		if(a[x-1][y]>=a[x][y]) ans=ans-z;
		else if(a[x][y]-z<a[x-1][y]) ans=ans-(a[x-1][y]-(a[x][y]-z))+(a[x][y]-a[x-1][y]);
		else ans=ans+z;
		if(a[x+1][y]>=a[x][y]) ans=ans-z;
		else if(a[x][y]-z<a[x+1][y]) ans=ans-(a[x+1][y]-(a[x][y]-z))+(a[x][y]-a[x+1][y]);
		else ans=ans+z;
		if(a[x][y-1]>=a[x][y]) ans=ans-z;
		else if(a[x][y]-z<a[x][y-1]) ans=ans-(a[x][y-1]-(a[x][y]-z))+(a[x][y]-a[x][y-1]);
		else ans=ans+z;
		if(a[x][y+1]>=a[x][y]) ans=ans-z;
		else if(a[x][y]-z<a[x][y+1]) ans=ans-(a[x][y+1]-(a[x][y]-z))+(a[x][y]-a[x][y+1]);
		else ans=ans+z;
		cout<<ans<<endl;
	}
}
```



---

## 作者：血色黄昏 (赞：1)

原来感觉不会做就没做，先写完 F 再写的这道，但其实很简单啊。

考虑在一个点放上 h 个方块的贡献，我们要求的是侧面积而这个柱体有四个独立的侧面，那我们只需要讨论一个侧面就好了。

根据小学知识，对于每个侧面我们要在答案上加上这个侧面的面积再减去两倍与相邻格子重叠的面积。具体的，如果这个格子原来有 a 个方块，在这个格子上加 h 个方块。相邻的格子有 b 个方块，那么答案要加上一个 $h - 2 * \min(h, \max(b - a, 0))$ 。对 $b - a$ 和 $0$ 取 $\max$ 是因为要考虑没有重合的情况。

接下来我们就应该考虑如何快速的查找和修改一个位置放置的方块数，容易发现用 map 恰好可以满足这个要求，每次查找修改均为 log 级别复杂度，我们可以建一个结构体映射到数字的 map ，注意我们要给这个结构体一个比较两个结构体大小的函数，不然会报错。

最后就是细节问题，本题答案会爆 long long ，你可以用 unsigned long long 或者 int128 结果这个问题，~~或者手写高精~~。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
__int128 ans = 0;
struct node{
	int x, y;
    bool operator<(const node b) const
	{
        if(x == b.x)return y < b.y;
		return x < b.x;
    }
};
map<node, int>m;//每次查找一个位置方块个数
inline void print(__int128 x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}
int read()
{
    int x = 0,f = 1;
	 char c = getchar();
    while (c != EOF && !isdigit(c)) {if (c == '-') f = -1;c = getchar();}
    while (isdigit(c)) {x = x * 10 + c - '0';c = getchar();}
    return x * f;
}
int d[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};//方向数
int cal(int x, int y, int h)
{
    node w = node{x, y}; 
	int cnt = 0;
	if(m.find(w) == m.end())m.insert(make_pair(w, h));
	else m[w] += h;
	for(int i = 0;i < 4;i ++)//考虑四个方向
	{
		int x1 = x + d[i][0], y1 = y + d[i][1];
        node w1 = node{x1, y1}; 
		if(m.find(w1) == m.end())cnt += h;
		else
		{
			int k = m[w1];
			cnt += h - 2 * min(h, max(k - m[w] + h, (int)0));//由于前面加上了h这里要减掉
		}
	}
	return cnt;
}
signed main()
{
	n = read();
	for(int i = 1;i <= n;i ++)
	{
		int x = read(), y = read(), h = read();
		ans += cal(x, y, h);//计算每次叠加的贡献
		print(ans);
   	  putchar('\n');
	}
	return 0;
}
```






---

## 作者：Supor__Shoep (赞：0)

本蒟蒻的方法没有正解的效率高，但是还是想写一篇题解。

首先看到坐标，再看到 $1≤x,y≤10^9$，我就唰地一下想到了用 map 储存一个二元组对应的值。

而对于存放 $z$ 个方块得到新的侧面积，我们可以分情况进行讨论。

- 如果加上 $z$ 个方块之后，$mp_{(x,y)}$ 的方块数小于 $mp_{(x+dx,y+dy)}$ 的方块数（其中有 $0≤dx,dy≤1$），那么我们就减去两倍的相互掩盖的面积。

- 如果加上 $z$ 个方块，原本的 $mp_{(x,y)}≤mp_{(x+dx,y+dy)}$ 变成了 $mp_{(x,y)}≥mp_{(x+dx,y+dy)}$，那么我们就减去凸出的方块以下的重复面积。

对于四个方向，我们都计算一遍，总共 $8$ 次条件判断。

所以就可以打出一段密密麻麻的代码：
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
map<pair<int,int>,int> mp;
int ans=0;
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int x,y,z;
		cin>>x>>y>>z;
		int w=mp[make_pair(x,y)];
		mp[make_pair(x,y)]+=z;
		ans+=(mp[make_pair(x,y)]-w)*4;
		if(mp[make_pair(x,y)]<=mp[make_pair(x-1,y)])	ans-=2*(mp[make_pair(x,y)]-w);
		if(mp[make_pair(x,y)]<=mp[make_pair(x+1,y)])	ans-=2*(mp[make_pair(x,y)]-w);
		if(mp[make_pair(x,y)]<=mp[make_pair(x,y+1)])	ans-=2*(mp[make_pair(x,y)]-w);
		if(mp[make_pair(x,y)]<=mp[make_pair(x,y-1)])	ans-=2*(mp[make_pair(x,y)]-w);
		if(mp[make_pair(x,y)]>mp[make_pair(x-1,y)]&&mp[make_pair(x-1,y)]>w)
			ans-=2*(mp[make_pair(x-1,y)]-w);
		if(mp[make_pair(x,y)]>mp[make_pair(x+1,y)]&&mp[make_pair(x+1,y)]>w)
			ans-=2*(mp[make_pair(x+1,y)]-w);
		if(mp[make_pair(x,y)]>mp[make_pair(x,y+1)]&&mp[make_pair(x,y+1)]>w)
			ans-=2*(mp[make_pair(x,y+1)]-w);
		if(mp[make_pair(x,y)]>mp[make_pair(x,y-1)]&&mp[make_pair(x,y-1)]>w)
			ans-=2*(mp[make_pair(x,y-1)]-w);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Jeremiahy (赞：0)

## 分析

首先明确一点：本题的侧面积就是侧面的面积······不算顶面和底面。

然后模拟就可以，可以用 ```map``` 存储坐标和高度，然后每次操作检查前后左右是否有方块，如果有就减去被覆盖的高度乘 $2$（因为两个方块都被盖住了），然后加上 $4\times h_i$（因为有四面），并存下高度。

另外，由于某个位置 $(x,y)$ 可能本来就有方块，处理覆盖的时候要注意，可以将身旁的方块高度减去原来就有的方块高度（可以理解为，把下面都砍去），然后再计算。

最后答案会爆 long long，开成 unsigned long long。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
map<pair<int, int>, int> m;//坐标与高度
int n, x, y, z, cnt;
unsigned long long ans;
signed main () {
	cin >> n;
	while (n--) {
		cin >> x >> y >> z;
		cnt = 0;
		if (m[make_pair(x, y)] > 0)
			cnt = m[make_pair(x, y)];
		else
			m[make_pair(x, y)] = 0;
		if (m[make_pair(x - 1, y)] > 0)
			ans -= max(0ll, min(m[make_pair(x - 1, y)] - cnt, z)) * 2;//可能减到负数，所以与 0 取max
		if (m[make_pair(x + 1, y)] > 0)
			ans -= max(0ll, min(m[make_pair(x + 1, y)] - cnt, z)) * 2;
		if (m[make_pair(x, y - 1)] > 0)
			ans -= max(0ll, min(m[make_pair(x, y - 1)] - cnt, z)) * 2;
		if (m[make_pair(x, y + 1)] > 0)
			ans -= max(0ll, min(m[make_pair(x, y + 1)] - cnt, z)) * 2;
		ans += z * 4;
		m[make_pair(x, y)] += z;
		cout << ans << '\n';
	}
	return 0;
}
```


---

## 作者：MujicaSaki (赞：0)

### 思路：

如果四面没有正方体理所当然就不用管了，如果四边的正方体其中有一个大于等于现在要放置的高度就会少 $z \times 2$ 面。如果小于现在的高度则当然会少这个正方体高度乘以 $2$。但是还有以前堆起来的正方体所以要把以前的正方体去掉才能算。记得特判一下负数情况。然后把正方体的四个面算一下就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,x,y,z;
map<long long,map<long long,long long>> m,m1;//map
unsigned long long s;//记得开unsigned long long！
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>x>>y>>z;
        //大于0的地方是特判负数
        if(m[x-1][y]>=z&&z-(z+m1[x][y]-m[x-1][y])>0) if(z+m1[x][y]-m[x-1][y]>0) s-=(z-(z+m1[x][y]-m[x-1][y]))*2;else s-=z*2;
        if(m[x+1][y]>=z&&z-(z+m1[x][y]-m[x+1][y])>0) if(z+m1[x][y]-m[x+1][y]>0) s-=(z-(z+m1[x][y]-m[x+1][y]))*2;else s-=z*2;
        if(m[x][y+1]>=z&&z-(z+m1[x][y]-m[x][y+1])>0) if(z+m1[x][y]-m[x][y+1]>0) s-=(z-(z+m1[x][y]-m[x][y+1]))*2;else s-=z*2;
        if(m[x][y-1]>=z&&z-(z+m1[x][y]-m[x][y-1])>0) if(z+m1[x][y]-m[x][y-1]>0) s-=(z-(z+m1[x][y]-m[x][y-1]))*2;else s-=z*2;
        if(m[x-1][y]>0&&m[x-1][y]<z&&m[x-1][y]-m1[x][y]>0) s-=(m[x-1][y]-m1[x][y])*2;
        if(m[x+1][y]>0&&m[x+1][y]<z&&m[x+1][y]-m1[x][y]>0) s-=(m[x+1][y]-m1[x][y])*2;
        if(m[x][y-1]>0&&m[x][y-1]<z&&m[x][y-1]-m1[x][y]>0) s-=(m[x][y-1]-m1[x][y])*2;
        if(m[x][y+1]>0&&m[x][y+1]<z&&m[x][y+1]-m1[x][y]>0) s-=(m[x][y+1]-m1[x][y])*2;
        s+=z*4;
        m[x][y]+=z;
        m1[x][y]=m[x][y];//以前的方块
        cout<<s<<endl;
    }
}
```


---

## 作者：Joker_1212 (赞：0)

# P8470 题解

[原题传送门](/probelm/P8470)

## 题意理解

求一个几何体的侧面积。

数据范围：

- $1 \le n \le 3 \times 10^5$
- $1 \le x, y \le 10^9$
- $1 \le z \le 10^{13}$

## 题目分析

每次加入都重新计算一遍不仅难以实现，还有 $\tt TLE$ 的风险，要选择更容易实现的算法。

容易发现，对于两个相邻的单位方块，它们对侧面积的贡献值为两者高度的较大值减去两者高度的最小值。这样可以用 `map` 存每个单位方块的高度信息，每次加入新方块时只用重新计算与它相邻的四个单位方块即可。

注意：由于答案最大可以达到 $1.2 \times 10 ^{19}$，需要用 `unsigned long long` 存储信息。

## 代码实现

```cpp
typedef pair<int, int> Point;

const int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

map<Point, ull> a;

#define dx (x + d[p][0])
#define dy (y + d[p][1])

int main()
{
    int n;
    read(n);
    ull ans = 0;
    while (n--)
    {
        ull x, y, z, lz; // lz 存储这个方块以前的信息
        read(x);
        read(y);
        read(z);
        auto pos = a.find(Point(x, y));
        if (pos != a.end())
            lz = pos->second, pos->second += z, z = pos->second;
        else
            a[Point(x, y)] = z, lz = 0;
        for (int p = 0; p < 4; ++p)
        {
            auto pos = a.find(Point(dx, dy));
            ull h = pos != a.end() ? pos->second : 0;
            ans -= max(h, lz) - min(h, lz); // 减去以前的贡献
            ans += max(h, z) - min(h, z);   // 加上现在的贡献
        }
        write(ans, 10);
    }
    return 0;
}
```


---

## 作者：alphayangyang (赞：0)

> 给定 $n$ 次操作，每次在 $(x_i, y_i)$ 处放置 $z_i$ 个正方体后求整个图形露在外面（接触空气）的侧面积。

### 分析

注意到 $x, y$ 的范围很大而 $n$ 的范围很小，因此整个图形是稀疏的。我们不能使用普通的数组来存储（这样存储效率太低且 MLE），于是考虑使用 $\textrm{STL}$ 中的 `std::map` 来存储。 其第一关键字可以用一个 `std::pair` 来记录点的横纵坐标，而第二关键字用于记录该坐标的方格数。后面使用时当数组使用即可。

接下来来到本题的核心部分：如何实时更新答案？

为了实现方便，我们考虑容斥原理：先假设四周没有方块，答案直接加上 $4z$ ，再减去被遮挡的面的面积的 **$2$ 倍**（重合的面永远是成双的）。

而我们注意到，在每一次操作后，每一个面都无非是以下几种情况：

1. 「万丈高楼拔地起」形。该面上没有其他的方格。此时重复面面积为 $0$。
2. 「与我无关」形。每一个点上的方块可能会被放置多次，此时如果原本立柱就比相邻面上的高，也没有重复面。
3. 「望之不及」形。虽然放置了，也不如相邻面高，此时重复面积即为该次放置的立柱高度 $z$。
4. 「后来者居上」形。这是重复的面积仅为旁边立柱的高度与当前方格上原有立柱的高度之差，即 $h_{x',y'}-h_{x, y}$（ $(x', y')$ 与 $(x, y)$ 相邻）。

统计答案即可。

**注意：数据范围十分毒瘤，不开 ull 见祖宗 qwq**

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int N = 3e5 + 5;
const int xx[] { -1, 0, 1, 0 }, yy[] { 0, 1, 0, -1 };
map < pair < int, int > , ULL > mp;
int n;
ULL ans;

int main() {
  scanf("%llu", &n);
  for (int i = 1; i <= n; ++i) {
    int x, y; ULL z;
    scanf("%d%d%llu", &x, &y, &z);
    ULL &p = mp[make_pair(x, y)]; // 原有高度
    ans += z << 2; // 先假设四周没有重复
    for (int k = 0; k < 4; ++k) {
      int nx = x + xx[k], ny = y + yy[k]; // 枚举四个方向
      ULL t = mp[make_pair(nx, ny)]; // 旁边的高度
      if (t > p) { // 如果旁边的比自己原来的高才有新增重复面
        if (t >= p + z) ans -= z << 1; // 分析中的第三种情况
        else ans -= t - p << 1; // 分析中的第四种情况
      }
    }
    p += z; // 更新该点的高度
    printf("%llu\n", ans);
  }
  return 0;
}
```



---

