# 「HCOI-R1」孤独的 sxz

## 题目背景

sxz 不擅长与人交往，于是他平常都喜欢找偏僻的地方坐着。今天，sxz 来到了食堂，他依旧想找一个偏僻的地方坐着，让他与其他所有人的曼哈顿距离之和最大。

## 题目描述

食堂的座位可以看成一个被划分为 $n\times m$ 的格子的矩形，长为 $n$，宽为 $m$，矩形内的每一个格子 $(i, j)(i \in [1, n], j \in [1, m])$ $(i,j$ 为整数$)$ 都是一个座位。

现在，食堂里已经有了 $k$ 个人，其中第 $i(1 \leq i \leq k)$ 个人坐在 $(x_i, y_i)$ 处。sxz 想要找到一个座位，使得该座位与 $k$ 个人的曼哈顿距离之和最大。请你帮他找到这个最大值，剩下的就交给 sxz 吧！

假设 sxz 坐在点 $(a,b)$，那么他和 $k$ 个人的曼哈顿距离之和是 $\sum_{i=1}^{k}|a-x_i|+|b-y_i|$。

**很显然，sxz 不能和 $\bm k$ 个人中的任何一个人坐在同一个地方**。

## 说明/提示

### 样例解释 1

最佳位置为 $(2,5)$，对于 $3$ 个人的曼哈顿距离分别为 $5, 3, 2$。

### 数据规模与约定

**本题采用捆绑测试。**
+ Subtask 0（15 pts）：$n, m \leq 100$。
+ Subtask 1（25 pts）：$n, m \leq 10000$。
+ Subtask 2（20 pts）：$k = 3$。
+ Subtask 3（40 pts）：无特殊限制。

对于所有数据，$1 \leq n, m \leq 10^9$，$1\leq k \leq \min\{4 \times 10^5, n\times m-1\}$，$1 \leq x_i \leq n$，$1 \leq y_i \leq m$，保证所有 $(x_i, y_i)$ 互不相同。

## 样例 #1

### 输入

```
2 5 3
1 1
1 3
1 4```

### 输出

```
10```

## 样例 #2

### 输入

```
7 4 9
1 4
2 3
4 1
6 2
7 1
5 2
3 4
1 1
7 4```

### 输出

```
38```

# 题解

## 作者：小胖同学 (赞：12)

# 「HCOI-R1」孤独的 sxz - 题解
官方题解
## Easy Version

**【设】**

 $f[i][j]$ 表示 sxz 坐在 $[i , j]$ 时的曼哈顿距离之和。

------------

 **【分析】** 
 
 下图中黄色格子为同学，红色格子为 sxz 。黄色格子里的数为此格子对于 sxz 的曼哈顿距离。 

![](https://cdn.luogu.com.cn/upload/image_hosting/wd38kslh.png) 

![](https://cdn.luogu.com.cn/upload/image_hosting/493qfp0x.png) 

观察可以发现当 sxz 从 $f[i][j]$ 移动到 $f[i][j + 1]$ 时：

 矩阵内 $[p,q] (p \in [1 , n] , q \in [1 , i - 1])$ 的曼哈顿距离 $+1$；$[p,q] (p \in [1 , n] , q \in [i , m])$ 的曼哈顿距离 $-1$ 。

 ![](https://cdn.luogu.com.cn/upload/image_hosting/eul4k0h4.png)

 ![](https://cdn.luogu.com.cn/upload/image_hosting/4ayetcfy.png) 

同理当 sxz 从 $f[i][j]$ 移动到 $f[i + 1][j]$ 时：

 矩阵内 $[p,q] (p \in [1 , j - 1] , q \in [1 , m])$ 的曼哈顿距离 $+1$ ；

$[p,q] (p \in [j , n] , q \in [1 , m])$ 的曼哈顿距离 $-1$ 。

------------

**【递推式】** 

注：$ a[i][j] $ 代表第 $i$ 行第 $j$ 列是否有同学。

$f[i][j] = f[i - 1][j] + cnt_h - cnt_t$

$cnt_h = \sum _ {p = 1} ^ {n} \sum _ {q = 1} ^ {j - 1} a[i][j]$ 

$cnt_t = \sum _ {p = 1} ^ {n} \sum _ {q = j} ^ {m} a[i][j]$

$f[i][j] = f[i][j - 1] + cnt_l - cnt_r$

$cnt_l = \sum _ {p = 1} ^ {i - 1} \sum _ {q = 1} ^ {m} a[i][j]$   

$cnt_r = \sum _ {p = i} ^ {n} \sum _ {q = 1} ^ {m} a[i][j]$  

------------

**【实现】**

$O(nm)$ 预处理每一行和每一列的同学数。

$O(nm)$ 统计 $f[1][1]$ 的值。

$O(nm)$ 拓广。

---



## Hard Version

观察式子可以发现，对于列而言，相邻的两人间的的曼哈顿距离一定是单调的，行同理。

考虑 $O(k)$ 预处理 $f[1][1]$ 的值。

$O(8k)$ 计算 $(1,1)(n,1)(1,m)(n,m)$, $(x_i - 1 , y_i)(x_i + 1 , y_i)(x_i , y_i - 1)(x_i , y_i + 1)$ 和 $(1 , y_i),(n , y_i),(x_i , 1),(x_i , m)$

 转移乘上距离 $f[x_i][y_i] = f[x _ {i - 1}][y _ {i - 1}] + cnt_h \times (x_i - x_{x - 1}) - cnt_t \times (y_i - y_{i - 1})$ 就可以了。

---

## 作者：Demeanor_Roy (赞：6)

- [原题链接。](https://www.luogu.com.cn/problem/P10025)

------------

比较无趣。

先**不考虑**座位不能与别人重复的问题。

由于横纵坐标显然可以分开考虑，问题转化为：有界数轴上有若干点，你需要选择一个点，使其到其他所有点距离之和最长。根据**调整法**，可知所选点一定在数轴边界，否则向左或向右必有一方使答案不劣。

故对于二维版本，答案一定是 $(1,1),(1,m),(n,1),(n,m)$ 四个点之一。

现在考虑原问题，即不能与他人重复。此时思考不同点是什么，显然为了满足这个限制，我们最终所选点会**恰好避开**某个已知位置，于是我们可以得出：**最优选点必定为上述四个点之一，或者某个已知点的邻点。**

关于这个结论的严格证明，你同样可以考虑**调整法**，即：对于一个上下都是空格的点，往上下某一方调整一定不劣，左右同理。具体细节读者可自行思考。

这里插一句，从上述分析可以看出，某个点是最优选点一个**更严格**的必要条件是：往左上、左下、右上、右下四个方向之一的矩形被已知点完全填满。当然用前面的性质已经足够。

于是将点离散化，维护一下横纵坐标前缀和，多次回答某定点到所有点距离之和，对所有答案取个 $\max$ 即可。注意判断一下询问点与已知点是否重合。时间复杂度 $O(k \log k)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=4e5+10;
int n,m,k,x[N],y[N],px[N],py[N],mx[4]={0,0,1,-1},my[4]={1,-1,0,0};
long long sx[N],sy[N];
map<int,bool> mp[N];vector<int> a,b;
inline bool check(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;}
inline int fa(int x){return lower_bound(a.begin(),a.end(),x)-a.begin();}
inline int fb(int x){return lower_bound(b.begin(),b.end(),x)-b.begin();}
inline long long Get(int x,int y)
{
	if(!check(x,y)) return 0;
	int dx=fa(x),dy=fb(y);if(x==a[dx]&&y==b[dy]&&mp[dx][dy]) return 0;
	return 1ll*px[dx-1]*x-sx[dx-1]+sx[N-1]-sx[dx-1]-1ll*x*(px[N-1]-px[dx-1])+1ll*py[dy-1]*y-sy[dy-1]+sy[N-1]-sy[dy-1]-1ll*y*(py[N-1]-py[dy-1]);
}
inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;i++)
	{
		x[i]=read(),y[i]=read();
		a.emplace_back(x[i]);b.emplace_back(y[i]);
	}
	a.emplace_back(0);
	a.emplace_back(n+1); 
	sort(a.begin(),a.end());
	a.erase(unique(a.begin(),a.end()),a.end());
	b.emplace_back(0);
	b.emplace_back(m+1);
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	long long ans=0;
	for(int i=1;i<=k;i++)
	{
		int X=fa(x[i]),Y=fb(y[i]);
		mp[X][Y]=true;++px[X];++py[Y];sx[X]+=x[i];sy[Y]+=y[i];
	}
	for(int i=1;i<N;i++) px[i]+=px[i-1],py[i]+=py[i-1],sx[i]+=sx[i-1],sy[i]+=sy[i-1];
	for(int i=1;i<=k;i++) for(int j=0;j<4;j++) ans=max(ans,Get(x[i]+mx[j],y[i]+my[j]));
	ans=max(ans,Get(1,1));ans=max(ans,Get(n,1));ans=max(ans,Get(1,m));ans=max(ans,Get(n,m));
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：zzx0102 (赞：5)

不得不说，这的确是个抽象的好题。

首先考虑如何快速球 $\sum\limits_{i=1}^k|a-x_i|+|b-y_i|$

将其分成两部分去求，以 $\sum\limits_{i=1}^k |a-x_i|$ 为例：

将这个柿子分成 $a\ge x_i$ 和 $a<x_i$ 去求。

令 $a\ge x_i$ 部分的右端点下表为 $p$，则考虑计算当 $a=x_p$ 时，$\sum\limits_{i=1}^p a-x_i$。

即 $ap-\sum\limits_{i=1}^p x_i$。

然后再加上 $a-x_p$，答案为 $p(a-x_p)+ap-\sum\limits_{i=1}^p x_i$。

同理可得 $a<x_i$ 部分答案为 $(n-p)(x_{p+1}-a)+\sum\limits_{p+1}^{n}x_i-(n-p)a$。

所以 $\sum\limits_{i=1}^k |b-y_i|$ 同理。

复杂度 $\mathcal{O}(\log k)$。

考虑怎么找出最佳位置。

先判断一个位置是否有人，维护个 unordered_map 的 hash 即可。

由于 unordered_map 会离奇 CE，所以我用了 map。

然后发现在一个墙角时是最优的，因为食堂中离点最远的点一定在墙角上。

考虑在墙角上深搜，搜到没有人的点就求算一遍。

因为总共 $k$ 个人，每个人最多分出去 $2$ 个点，所以最多求 $2k$ 次，总复杂度 $\mathcal{O}(k\log k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mk_p make_pair
const int N = 400010;
int r[N], c[N], x[N], y[N], n, m, k; map<pair<int, int>, int> mp, vis; int sx[N], sy[N], px[N], py[N];
int cal(int a, int b) {
	int sum = 0;
	int x = lower_bound(r + 1, r + 1 + k, a) - r - 1;
	sum += px[x] + x * (a - r[x]);
	if(x < k) sum += sx[x + 1] + (k - x) * (r[x + 1] - a);
	int y = lower_bound(c + 1, c + 1 + k, b) - c - 1;
//	cout << x << ' ' << y << '\n';
	sum += py[y] + y * (b - c[y]);
	if(y < k) sum += sy[y + 1] + (k - y) * (c[y + 1] - b);
//	cout << a << ' ' << b << ' ' << sum << '\n';
	return sum;
}
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}; int mx;
void dfs(int x, int y) {
	if(!mp[mk_p(x, y)]) {
		mx = max(mx, cal(x, y));
		return ;
	}
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
		if(!vis[mk_p(nx, ny)]) {
			vis[mk_p(nx, ny)] = 1;
			dfs(nx, ny);
		}
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= k; i++) {
		cin >> x[i] >> y[i];
		mp[mk_p(x[i], y[i])] = 1;
		r[i] = x[i], c[i] = y[i];
	}
	sort(r + 1, r + 1 + k); sort(c + 1, c + 1 + k);
	for(int i = 1; i <= k; i++) {
		px[i] = px[i - 1] + (r[i] - r[i - 1]) * (i - 1);
		py[i] = py[i - 1] + (c[i] - c[i - 1]) * (i - 1);
	}
	for(int i = k; i; i--) {
		sx[i] = sx[i + 1] + (r[i + 1] - r[i]) * (k - i);
		sy[i] = sy[i + 1] + (c[i + 1] - c[i]) * (k - i);
	}
	dfs(1, 1); dfs(n, 1); dfs(1, m); dfs(n, m);
	cout << mx;
	return 0;
}
```

---

## 作者：Xiphi (赞：4)

### P10025

考虑贪心，直观感觉就是四个角 $(n,m),(1,m),(n,1),(1,1)$ 是最优的。在没有点占住四个角的时候答案必然在 $4$ 个点之中，自证不难。然后，若有点占上了四个角之一，则答案必然在占住的那个连通块的外围，同样自证不难。为了实现方便，直接枚举每个点的上下左右即可。注意边界问题。

特别的，可以用二分+算贡献的方法求出每个点与其他点的距离之和。把 $x,y$ 轴拆开，把 $x_i,y_i$ 排序，然后二分算贡献即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,x[400005],y[400005];
pair<int,int> pos[400005];
int sa[400005],sb[400005];
set<pair<int,int > > s;vector<pair<int,int>> v;
int calc(int a,int b){
	if(a>n||a<1||b<1||b>m) return 0;
	if(s.count({a,b})) return 0;
	int it1=lower_bound(x+1,x+k+1,a)-x,
		it2=lower_bound(y+1,y+k+1,b)-y;
//	if(it1==k+1) it1--;
//	if(it2==k+1) it2--;
	int px=((it1-1)*a-sa[it1-1])+sa[k]-sa[it1-1]-(k-it1+1)*a;
	int	py=((it2-1)*b-sb[it2-1])+sb[k]-sb[it2-1]-(k-it2+1)*b;
	return px+py;
}
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=k;++i) cin>>x[i]>>y[i],v.push_back({x[i],y[i]}),s.insert({x[i],y[i]});
	sort(x+1,x+k+1);
	sort(y+1,y+k+1);
	for(int i=1;i<=k;++i){
		sa[i]=sa[i-1]+x[i];
		sb[i]=sb[i-1]+y[i];
	}
	int maxn=max({calc(1,m),calc(n,m),calc(n,1),calc(1,1)});
	for(int i=1;i<=k;++i){
		int X=v[i-1].first,Y=v[i-1].second;
		maxn=max({calc(X,1),
				  calc(X,m),
				  calc(1,Y),
				  calc(n,Y),
				  calc(X-1,Y),
				  calc(X,Y+1),
				  calc(X+1,Y),
				  calc(X,Y-1),
				  maxn});
	} 
	cout<<maxn;
	return 0;
}
```

---

## 作者：robinyqc (赞：3)

几个挺有意思的解法。

### 题意简述

给定一个 $n\times m$ 的表格，上面有 $k$ 个格子被涂黑了。求一个白色格子，到所有黑色格子的曼哈顿距离之和**最大**。$n, m\leq 10^9, k\leq 4\times 10^5$。

### 主要思路

若没有 $n, m$ 的限制，答案是无限大的，选一个特别远的点即可。所以自然地想到，加上 $n, m$ 的限制，应当尽量选边角上的点。

为啥呢？不妨先钦定选择的点在第 $x$ 行。那么纵坐标的贡献对这一行都是相等的。那么问题变成一维的，数轴上若干个点，离他们距离和最远的点，要么是最右的点，要么是最左的点，这个很显然。所以对于每一行，答案要么是最左边那个白点，要么是最右边那个白点。对列可以类似地分析。我们称这种最左/右的点为关键点。

### 解法一

直接暴力做即可，复杂度 $O(k\sqrt k)$。

枚举行，若这一行最左边的白点比前面所有行最左边的白点都更左，那么它有可能成为答案。求出一行最左边的点可以 $O(l\log k)$，其中 $l$ 是最左边的点的横坐标。所以求出所有行有贡献最左边点的复杂度为 $O(\log k\sum l) = O(k\log k)$。也可以这么理解：每个黑点最多只被遍历一次，所以总复杂度 $O(k\log k)$。

注意到，一个横坐标为 $x$ 的关键点，前面一定有 $x - 1$ 个黑点作为支撑。并且按行看，没有横坐标相同的靠左的关键点。由于 $1 + 2 + 3 + \dots + n = O(n^2)$，且 $\sum_{p\in \{\text{关键点}\}} p_x \leq k$，极端情况下，$p_x$ 就是 $1..n$ 的形式。所以关键点的个数是 $O(\sqrt k)$ 级别的。

这是个很经典的结论。例题：喵星球上的点名。

所以直接暴力 $O(k)$ 计算每个关键点的答案即可。总复杂度 $O(k\log k + k\sqrt k) = O(k\sqrt k)$，思路极简单，~~代码也好写~~。

下面是两段比较关键的代码。

+ 找出一行靠左的关键点：
   ```cpp
   pair<int, int> find_p(int x)
   {
       for (int i = 0; i < m; i++) {
           pair<int, int> s(x + d1 * i, y + d2 * i);
           // 如果发现 s 不在黑点集合中，返回 s。
           if (!binary_search(o + 1, o + 1 + k, s)) {
               return s;
           }
       }
       return {x, m + 1};
   }
   ```

+ 统计可能成为答案的点：

   ```cpp
   int bf = m + 1; // 之前行最左边的点的横坐标。
   for (int i = 1, bf = m + 1; i <= n; i++) {
       auto x = find_p(i);
       if (x.second < bf) {
           // 将 x 加入可能成为关键点集中。
           qr.push_back(x);
           bf = x.second;
       }
       // 若 bf <= 1 那么显然不会有更左的点了，
       // 直接退出循环，否则复杂度显然是错误的。
       if (bf <= 1) break;
   }
   ```
   对于其它方向（总共八个方向）都可以类似地求。
   
这个做法复杂度比较高，不过出题人没有卡。我造了组[极限数据](https://www.luogu.com.cn/problem/U393061)，这种做法要跑 900 ms，也确实能过。


### 解法二

$O(k\log k)$。

不同于解法一，我们考虑如何优化计算，给定一个白点 $(a, b)$，其到所有曼哈顿距离之和。

这有个板子题，是 Gym100739E Life as a monster。

首先横纵坐标的贡献可以拆开算。就拿横坐标来说，将所有黑点分类成 $L = \{x\mid x \leq a\}$ 和 $R = \{x\mid x > a\}$ 两种。那么答案是：

$$
\left(|L|\cdot a - \sum_{i\in L} i\right) + \left(-|R|\cdot a + \sum_{i\in R}i \right)
$$

可以离散化后，前缀和计算这个答案。带修可以树状数组，强制在线就平衡树。本题前缀和即可。

枚举所有白点计算答案肯定是不行的。还是可以用一下**主要思路**中提到的结论，不过我们不需要那么麻烦。注意到所有关键点（除了四个角）一定和某个黑点相邻。所以枚举黑点相邻的点即可。最后如果四个角有白色的，加上这些的贡献即可。复杂度 $O(k\log k)$，瓶颈为离散化。

代码也很好写，我就不放了。

其实在此基础上，我们发现并不需要离散化这个步骤，只需要排序（扫描线）。比如就拿横坐标贡献来说。将所有点按照横坐标升序排序，从左到右遍历每个黑点，计算当前前缀和即可。总复杂度 $O(k\log k)$。

### 解法三

$O(k)$。

在解法一的基础上，进一步地，可以发现每个关键点离边界较大的距离不超过 $k$。这个可以从求解关键点的过程的复杂度得到。

所以，在解法二的基础上，我们只需要对横坐标小于等于 $k$ 的点计数排序（或开个桶前缀和）即可。只用遍历离边界不超过 $k$ 的黑点，剩下的点一定在关键点的另一侧，可以 $O(1)$ 计算贡献。总复杂度 $O(k)$。

---

## 作者：Wf_yjqd (赞：2)

更：23.12.28

膜拜验题人，希望数据不出锅（暂时没出）。

很典的水题，他真的没有蓝。

------------

显然这个题的数据很难造，因为要卡住一些随机撒点和在四个角落撒点的做法。

所以我写了个骗分方便验题人照着卡。

假如我们已经确定了答案在一些点中，只需要把每个点距离其他所有点的曼哈顿距离之和求出来，取最大值就好了。

我们先把 $x$ 轴和 $y$ 轴分开求距离。

考虑对于 $x$ 轴（$y$ 轴同理）如何求一个点距离其他所有点的距离之和。

为了去掉绝对值分讨左右两种情况，若当前点坐标为 $x$，左边共 $le$ 个点，$qz_i$ 表示前 $i$ 个点坐标和，则距离和为 $x\times(le\times2-k)+qz_k-qz_{le}\times2$。

显然只需要二分和前缀和就可以求出 $le$ 和 $qz_i$ 了。

考虑正解，贪心发现只需要跑一下与给定点相邻的以及四个角即可。

------------

补一个贪心的原理。

首先单独考虑一维，对于相邻两点之间，考虑在区间两边的个数。

显然选择的点一定要靠近个数较少的那边。

所以只要把相邻的都跑了，就一定能涵盖答案。

感性理解好了。

------------

复杂度 $\operatorname{O}(k\log k)$。

------------

进行一个代码的放。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=5e5+84,base=1e9;
ll n,m,k,ans,x[maxn],y[maxn],xx[maxn],yy[maxn],qzx[maxn],qzy[maxn],lepx,lepy;
unordered_map<ll,bool> vis;
inline void Update(ll x,ll y){
    if(x<1||x>n||y<1||y>m||vis.find(x*base+y)!=vis.end())
        return ;
    vis[x*base+y]=1;
    lepx=lower_bound(xx+1,xx+k+1,x)-xx-1;
    lepy=lower_bound(yy+1,yy+k+1,y)-yy-1;
    ans=max(ans,x*(lepx*2-k)+qzx[k]-qzx[lepx]*2+y*(lepy*2-k)+qzy[k]-qzy[lepy]*2);
    return ;
}
int main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    assert(1<=n&&n<=base&&1<=m&&m<=base);
    assert(k<n*m&&k<=4e5);
    for(ll i=1;i<=k;i++){
        scanf("%lld%lld",&x[i],&y[i]);
        assert(1<=x[i]<=n&&1<=y[i]<=m);
        assert(!vis[x[i]*base+y[i]]);
        vis[x[i]*base+y[i]]=1;
        xx[i]=x[i];
        yy[i]=y[i];
    }
    sort(xx+1,xx+k+1);
    sort(yy+1,yy+k+1);
    for(ll i=1;i<=k;i++){
        qzx[i]=qzx[i-1]+xx[i];
        qzy[i]=qzy[i-1]+yy[i];
    }
    Update(1,1);
    Update(n,m);
    Update(1,m);
    Update(n,1);
    for(ll i=1;i<=k;i++){
        Update(x[i]-1,y[i]);
        Update(x[i]+1,y[i]);
        Update(x[i],y[i]+1);
        Update(x[i],y[i]-1);
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：matrixPower (赞：2)

[传送门](https://www.luogu.com.cn/problem/P10025)

我们可以浅浅的考虑一个贪心~~为什么赛时没想出来~~。

易得：若四个角落**没有人**，那么答案一定在这**四个角落**中。

若有人**占**了四个角落之一，则答案必在**占住的那个连通块的外围**。

可以枚举每个点的上下左右即可。

注意**边界问题**。

---

## 作者：CaiZi (赞：1)

首先拆开求和，得到 $\sum_{i=1}^k|a-x_i|+\sum_{i=1}^k|b-y_i|$。这说明我们可以将 $x_i,y_i$ 分别考虑。

先考虑一维的情况，设 $m=1$。不难发现对于一个 $a\ne1,a\ne n$，如果其左边的人数大于右边的人数，则 $a+1$ 的答案更大，否则 $a-1$ 的答案更大。因此这个点一定在最左或者最右的没有人的位置。

二维同理，答案一定是在最靠近四个角的没有人的位置。可以用 BFS 找，但是太麻烦了。可以发现答案一定在四角，如果四角都被占则是某个人的四周，一个个检查即可。使用二分找到在某个点上方、下方、左方、右方的点，并使用前缀和得出这些点的 $x_i,y_i$ 和即可。

时间复杂度 $O(k\log k)$。

代码展示（代码中 $a,b$ 分别指排序后的 $x,y$）：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,x[400001],y[400001],a[400001],b[400001],sa[400001],sb[400001],t;
set<pair<int,int>>g;
inline int get(int i,int j){
	if(i<1||i>n||j<1||j>m||g.count(make_pair(i,j))){
		return -1;
	}
	int u=lower_bound(a+1,a+k+1,i)-a-1,v=lower_bound(b+1,b+k+1,j)-b-1;
	return (u*i-sa[u])+(sa[k]-sa[u]-(k-u)*i)+(v*j-sb[v])+(sb[k]-sb[v]-(k-v)*j);
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>x[i]>>y[i];
		a[i]=x[i];
		b[i]=y[i];
		g.insert(make_pair(x[i],y[i]));
	}
	sort(a+1,a+k+1);
	sort(b+1,b+k+1);
	for(int i=1;i<=k;i++){
		sa[i]=sa[i-1]+a[i];
		sb[i]=sb[i-1]+b[i];
	}
	t=max({get(1,1),get(1,m),get(n,1),get(n,m)});
	for(int i=1;i<=k;i++){
		t=max({t,get(x[i]-1,y[i]),get(x[i]+1,y[i]),get(x[i],y[i]-1),get(x[i],y[i]+1)});
	}
	cout<<t;
	return 0;
}
```

---

## 作者：LCat90 (赞：1)

孤独的人是我。

-----------

首先，考虑一个子问题。对于确定的一个选点 $(x,y)$，如何快速计算答案？

可以将坐标离散化，然后 BIT 将绝对值拆掉即可，实现的话维护两个 BIT，同时行和列也要分别维护。时间在对数级别。

然后，可能的选点有哪些？

这个问题考虑【**调整法**】和【**反向排除**】。

首先，如果不考虑重复，那么我们肯定是尽量地让这个点远离其余所有的位置，越远越好。但是因为边界的限制，所以只可以指定边缘那 4 个点。

一种可能的情况：4 个点全部被占用。怎么办？

这时候思考：如果我现在选择的这个位置，它的上下都是空的，我是不是一定可以通过上/下操作使得答案更不劣？（左右一样）

正确的，从贡献的角度考虑：上面的个数和下面的个数只要不等，那么移动肯定更优；若相等则不影响。根据这样的调整思路，我们就将上面这一类点全部排除，最终就剩下：相邻的位置一定有被占用的位置的点。

然后发现这时候合法的点数已经在 $4k$ 左右，于是我们找出这些点，解决 $4k$ 个子问题即可，时间复杂度为 $O(k\log k)$。

```cpp
#include <bits/stdc++.h>
#define pii pair <int, int> 
#define int long long
using namespace std; int lowbit(int x) { return x & -x; }
const int N = 2e6 + 5; int read();
const int zx[] = {-1, 0, 0, 1}, zy[] = {0, 1, -1, 0};
int n, m, k, ans, a[N], b[N]; 
map < pii , bool > f;
struct node { int x, y; } p[N]; int num; 

struct Tree {
	int T[N];
	void update(int k, int x) { for(int i = k;i <= N - 5;i += lowbit(i)) T[i] += x; }
	int query(int k) {
		int res = 0;
		for(int i = k;i;i -= lowbit(i)) res += T[i];
		return res;
	}
} T1, T2, t1, t2; // T 表示行；1 表示 num，2 表示 sum 

int cnt1, cnt2, h1[N], h2[N]; // 专门离散化 

signed main() {
	cin >> n >> m >> k; 
	for(int i = 1;i <= k; ++i)  {
		a[i] = read(), b[i] = read();
		f[{a[i], b[i]}] = 1; h1[i] = a[i], h2[i] = b[i];
	} cnt1 = k, cnt2 = k;
	if(!f[{1, 1}]) p[++num] = (node){1, 1}, f[{1, 1}] = 1, h1[++cnt1] = 1, h2[++cnt2] = 1;
	if(!f[{1, m}]) p[++num] = (node){1, m}, f[{1, m}] = 1, h1[++cnt1] = 1, h2[++cnt2] = m;
	if(!f[{n, 1}]) p[++num] = (node){n, 1}, f[{n, 1}] = 1, h1[++cnt1] = n, h2[++cnt2] = 1;
	if(!f[{n, m}]) p[++num] = (node){n, m}, f[{n, m}] = 1, h1[++cnt1] = n, h2[++cnt2] = m;
	for(int i = 1;i <= k; ++i) 
		for(int l = 0;l < 4; ++l) {
			int dx = a[i] + zx[l], dy = b[i] + zy[l];
			if(dx < 1 or dy < 1 or dx > n or dy > m or f[{dx, dy}]) continue ;
			p[++num] = (node){dx, dy}; f[{dx, dy}] = 1; h1[++cnt1] = dx, h2[++cnt2] = dy;
		}
	sort(h1 + 1, h1 + cnt1 + 1); cnt1 = unique(h1 + 1, h1 + cnt1 + 1) - h1 - 1;
	sort(h2 + 1, h2 + cnt2 + 1); cnt2 = unique(h2 + 1, h2 + cnt2 + 1) - h2 - 1;
	for(int i = 1, x, y;i <= k; ++i) {
		x = a[i], y = b[i];
		a[i] = lower_bound(h1 + 1, h1 + cnt1 + 1, a[i]) - h1;
		b[i] = lower_bound(h2 + 1, h2 + cnt2 + 1, b[i]) - h2; 
		T1.update(a[i], 1), t1.update(a[i], x);  
		T2.update(b[i], 1), t2.update(b[i], y); 
	}
	for(int i = 1;i <= num; ++i) {
		int x = p[i].x, y = p[i].y, sum = 0; // count
		x = lower_bound(h1 + 1, h1 + cnt1 + 1, x) - h1;
		y = lower_bound(h2 + 1, h2 + cnt2 + 1, y) - h2; 
		sum = p[i].x * T1.query(x - 1) - t1.query(x - 1) + t1.query(N - 5) - t1.query(x) - (k - T1.query(x)) * p[i].x;
		sum += p[i].y * T2.query(y - 1) - t2.query(y - 1) + t2.query(N - 5) - t2.query(y) - (k - T2.query(y)) * p[i].y;
		ans = max(ans, sum);
	}
	cout << ans;
	return 0;
}
// ======= 对于一个上下都是空格的点，往上下某一方调整一定不劣，左右同理。
int read() {
	char c; int sum = 0; while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') sum = (sum << 3) + (sum << 1) + (c ^ 48), c = getchar();
	return sum;	
}
```

---

## 作者：NATO (赞：0)

大数据结构。

考虑先将问题拆为 $\sum_{i=1}^{k}|a-x_i|+\sum_{i=1}^{k}|b-y_i|$，然后我们分开来考虑 $a,b$。

在此我们仅对 $\sum_{i=1}^{k}|a-x_i|$ 进行分析，因为 $\sum_{i=1}^{k}|b-y_i|$ 同理。

考虑我们当前选择的 $a$，设有 $p$ 个点 $x_p\le a$，则有 $n-p$ 个点 $x_p>a$。

若 $p\le n-p$，那么我们一直往左边走必然是最优的，因为显然一直往左边走 $p\le n-p$ 始终成立且我们每走一步答案会增加 $n-p-p$，而当前的 $a$ 随着减小它右边的点会增多，左边变少，那么增加的答案会越来越多，因此最左边即取 $1$ 时最优。

$p>n-p$ 同理可知取最右边即 $n$ 时最优。

那么同理可知 $\sum_{i=1}^{k}|b-y_i|$ 当 $b$ 取 $1$ 或者 $n$ 时存在最大值。

那么，理论上我们只需要取 $(1,1),(1,n),(n,1),(n,n)$ 这四个点时的结果的最大值我们就可以得到答案了，但是题目中告诉我们如果一个位置已经有人被选择了，我们就不能选择了，那么如果四个角被选了，该怎么办呢？

考虑根据上述贪心策略选点，我们的目标即是使 $a,b$ 尽可能地靠近 $1$ 或者 $n$ 那么基于这一点，我们就可以搜寻占据了四个角的那些点与之相邻的点，查询选择这些点时的答案，取最大值即可，由于一个点最多与 $4$ 个点相邻，那么我们查询的点的个数就和 $k$ 是同阶的。

考虑如何快速查询选择一个点时的结果。

由于我们可以将 $a,b$ 分开查询，我们就可以开两颗动态开点权值线段树，将输入点的 $x,y$ 分别扔到两颗线段树中，查询的时候对于 $a$ 就查询有多少个数小于等于 $a$ 及它们的和（记为 $size_1,sum_1$），还有有多少个数大于等于 $a$ 及它们的和（记为 $size_2,sum_2$），$a$ 的贡献即为 $a\times size_1-sum_1+sum_2-a\times size_2$，对于 $b$ 同理处理即可。

时间复杂度 $O(k\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 1000000000ll
using namespace std;
ll n,m,k;
map<ll,map<ll,bool>>vis;//记录点是否被选择
struct xp
{
	ll son[2],sum,s;
};
struct tree
{
	xp tr[20000005];
	ll cnt;
	#define ls(id) tr[id].son[0]
	#define rs(id) tr[id].son[1]
	void pushup(ll id)
	{
		tr[id].sum=tr[ls(id)].sum+tr[rs(id)].sum;
		tr[id].s=tr[ls(id)].s+tr[rs(id)].s;
	}
	void update(ll &id,ll l,ll r,ll ml,ll val)
	{
		if(!id)id=++cnt;
		if(l==r)
		{
			tr[id].sum+=val;
			++tr[id].s;
			return;
		}
		ll mid=l+r>>1;
		if(ml<=mid)update(ls(id),l,mid,ml,val);
		else update(rs(id),1+mid,r,ml,val);
		pushup(id);
	}
	ll query_sum(ll id,ll l,ll r,ll ml,ll mr)
	{
		if(ml>mr)return 0;
		if(!id)return 0;
		if(ml<=l&&r<=mr)return tr[id].sum;
		ll mid=l+r>>1,res=0;
		if(ml<=mid)res+=query_sum(ls(id),l,mid,ml,mr);
		if(mr>mid)res+=query_sum(rs(id),1+mid,r,ml,mr);
		return res;
	}
	ll query_s(ll id,ll l,ll r,ll ml,ll mr)
	{
		if(ml>mr)return 0;
		if(!id)return 0;
		if(ml<=l&&r<=mr)return tr[id].s;
		ll mid=l+r>>1,res=0;
		if(ml<=mid)res+=query_s(ls(id),l,mid,ml,mr);
		if(mr>mid)res+=query_s(rs(id),1+mid,r,ml,mr);
		return res;
	}
}xtr,ytr;//动态开点权值线段树
ll rtx,rty;
ll get_res(ll x,ll y)
{
	ll res=0;
	res+=x*xtr.query_s(rtx,1,MAXN,1,x)-xtr.query_sum(rtx,1,MAXN,1,x);
	res+=y*ytr.query_s(rty,1,MAXN,1,y)-ytr.query_sum(rty,1,MAXN,1,y);
	res+=xtr.query_sum(rtx,1,MAXN,x,MAXN)-x*xtr.query_s(rtx,1,MAXN,x,MAXN);
	res+=ytr.query_sum(rty,1,MAXN,y,MAXN)-y*ytr.query_s(rty,1,MAXN,y,MAXN);
	return res;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	ll x,y;
	for(ll i=1;i<=k;++i)
	{
		cin>>x>>y,vis[x][y]=1;
		xtr.update(rtx,1,MAXN,x,x);
		ytr.update(rty,1,MAXN,y,y);
	}
	ll res=0;
	for(ll j=1;j<=n;++j)
	{
		bool flag=0;
		ll ls=1;
		for(ll i=1;i<=m;++i)
		if(!vis[j][i])
		{
		res=max(res,get_res(j,i));
		if(i==1||i<=ls)
		flag=1;
		ls=i;
		break;
		}
		if(flag)break;
	}
	for(ll j=n;j;--j)
	{
		bool flag=0;ll ls=1;
		for(ll i=1;i<=m;++i)
		if(!vis[j][i])
		{
		res=max(res,get_res(j,i));
		if(i==1||i<=ls)
		flag=1;ls=i;
		break;
		}
		if(flag)break;
	}
	for(ll j=1;j<=m;++j)
	{
	bool flag=0;ll ls=1;
	for(ll i=1;i<=n;++i)
	if(!vis[i][j])
	{
		res=max(res,get_res(i,j));
		if(i==1||i<=ls)
		flag=1;ls=i;
		break;
	}	
	if(flag)break;
	}
	for(ll j=m;j;--j)
	{
	bool flag=0;ll ls=1;
	for(ll i=1;i<=n;++i)
	if(!vis[i][j])
	{
		res=max(res,get_res(i,j));
		if(i==1||i<=ls)
		flag=1;ls=i;
		break;
	}	
	if(flag)break;
	}
	
	for(ll j=1;j<=n;++j)
	{
		bool flag=0;ll ls=m;
		for(ll i=m;i;--i)
		if(!vis[j][i])
		{
		res=max(res,get_res(j,i));
		if(i==m||i>=ls)
		flag=1;ls=i;
		break;
		}
		if(flag)break;
	}
	for(ll j=n;j;--j)
	{
		bool flag=0;ll ls=m;
		for(ll i=m;i;--i)
		if(!vis[j][i])
		{
		res=max(res,get_res(j,i));
		if(i==m||i>=ls)
		flag=1;ls=i;
		break;
		}
		if(flag)break;
	}
	for(ll j=1;j<=m;++j)
	{
	bool flag=0;ll ls=n;
	for(ll i=n;i;--i)
	if(!vis[i][j])
	{
		res=max(res,get_res(i,j));
		if(i==n||i>=ls)
		flag=1;ls=i;
		break;
	}	
	if(flag)break;
	}
	for(ll j=m;j;--j)
	{
	bool flag=0;ll ls=n;
	for(ll i=n;i;--i)
	if(!vis[i][j])
	{
		res=max(res,get_res(i,j));
		if(i==n||i>=ls)
		flag=1;
		ls=i;
		break;
	}	
	if(flag)break;
	}//依次枚举四个角上的情况并查询
	cout<<res;
}
```


---

## 作者：icypenguin (赞：0)

### 题目分析

首先，$k = 3$ 这个部分分给了我们充分的启发，显然 $(1, 1)$、$(1, m)$、$(n, 1)$、$(n, m)$ 这四个角在没有人的时候一定有一个角是最优的，想到计算四次取最大值来完成这个部分分。

咋查看一个点是否有人呢，使用 map 加上一个简易的 hash 函数即可。

接下来有点难想，一个墙角是最优的，那么下一些最优的点一定在这些墙角的旁边！想到 bfs。

每次向上下左右进行 bfs，用一个 priority_queue 维护一个大顶堆。如何快速计算一个位置的距离之和？想到分别计算 $x$、$y$ 的距离之和，给 $x$、$y$ 数组从小到大排序，分别二分计算即可。因为最多会经过 $k$ 个有人的点，所以时间复杂度是 $O(k \log k)$ 的。

### 代码实现

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#define ll long long
using namespace std;
ll n, m, k, x[1000005], y[1000005], mx = 0, sumx[1000005], sumy[1000005];
map<ll, ll> book, book2;
ll dx[4] = {1, -1, 0, 0};
ll dy[4] = {0, 0, 1, -1};
struct node{
    ll x, y, k;
    friend bool operator<(node a, node b){
        return a.k < b.k;
    }
};
priority_queue<node> q;
ll ct(ll xa, ll ya){
    ll tot = 0;
    ll w = upper_bound(x + 1, x + k + 1, xa) - x;
    ll t = w;
    w--;
    if (w >= 1){
        tot += xa * w - sumx[w];
    }
    if (t <= k){
        tot += sumx[k] - sumx[t - 1] - xa * (k - t + 1);
    }
    w = upper_bound(y + 1, y + k + 1, ya) - y;
    t = w;
    w--;
    if (w >= 1){
        tot += ya * w - sumy[w];
    }
    if (t <= k){
        tot += sumy[k] - sumy[t - 1] - ya * (k - t + 1);
    }
    if (!book[xa * 3000000007 + ya]){
        mx = max(mx, tot);
    }
    return tot;
}
int main(){
    cin >> n >> m >> k;
    for (ll i = 1; i <= k; i++){
        cin >> x[i] >> y[i];
        book[x[i] * 3000000007 + y[i]] = 1;
    }
    sort(x + 1, x + k + 1);
    sort(y + 1, y + k + 1);
    for (ll i = 1; i <= k; i++){
        sumx[i] = sumx[i - 1] + x[i];
        sumy[i] = sumy[i - 1] + y[i];
    }
    q.push(node{1, 1, ct(1, 1)});
    book2[1 * 3000000007 + 1] = 1;
    if (!book2[1 * 3000000007 + m]){
        q.push(node{1, m, ct(1, m)});
        book2[1 * 3000000007 + m] = 1;
    }
    if (!book2[n * 3000000007 + 1]){
        q.push(node{n, 1, ct(n, 1)});
        book2[n * 3000000007 + 1] = 1;
    }
    if (!book2[n * 3000000007 + m]){
        q.push(node{n, m, ct(n, m)});
        book2[n * 3000000007 + m] = 1;
    }
    ll nic = -1e18;
    while (!q.empty()){
        node w = q.top();
        q.pop();
        if (w.k < nic){
            break;
        }
        if (!book[w.x * 3000000007 + w.y]){
            nic = w.k;
            ll tot = ct(w.x, w.y);
            if (tot > mx){
                mx = tot;
            }
        }
        if (w.k != nic){
            for (ll i = 0; i <= 3; i++){
                ll new_x = w.x + dx[i], new_y = w.y + dy[i];
                if (new_x <= 0 || new_x > n || new_y <= 0 || new_y > m || book2[new_x * 3000000007 + new_y]){
                    continue;
                }
                book2[new_x * 3000000007 + new_y] = 1;
                q.push(node{new_x, new_y, ct(new_x, new_y)});
            }
        }
    }
    cout << mx << endl;
    return 0;
}
```


---

