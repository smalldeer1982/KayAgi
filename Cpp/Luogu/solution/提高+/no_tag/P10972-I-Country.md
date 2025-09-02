# I-Country

## 题目描述

根据绝密的 A 国计划，I 国被划分为 $N\times M$ 个相等的正方形，每个正方形包含一些石油资源。他们希望占领整个 I 国的领土，但联合国只允许他们占领 $K$ 个正方形。

当然，A 国希望控制尽可能多的石油，但是他们必须守卫他们的全部领土。因此，他们需要他们的领土易于控制，即从任何一个正方形到另一个正方形只能沿着两个方向移动（从下列列表中选择：左、右、上、下；对于不同的正方形对，方向可能不同）。

你需要编写一个程序，确定 A 国将占领哪些正方形。如果有多个解决方案，你可以输出任意一个。

## 样例 #1

### 输入

```
2 3 4
10 20 30
40 2 3```

### 输出

```
Oil : 100
1 1
1 2
1 3
2 1```

# 题解

## 作者：Drifty (赞：10)

### Solution

介绍一下蓝书上的 dp 做法。

注意到本题的阶段满足线性增长的特性，考虑线性 dp。

我们设状态 $f_{i,j,l,r,x,y}$ 表示前 $i$ 行选了 $j$ 个格子，当前的第 $i$ 行选了 $l\sim r$ 个格子（包括第 $l,r$ 个格子，若不选 $l, r$ 均为零），左边界是否在扩张（即列号的单调性）记为 $x$，右边界是否在扩张记为 $y$。其中：

- $x = 1$ 左边界扩张，$x = 0$ 左边界收缩。
- $y = 0$ 右边界扩张，$y = 1$ 右边界收缩。

以下记：
$$
S_{l, r} = \sum_{p = l} ^ {r} a_{i,p}
$$

对 $x,y$ 进行分讨，有以下转移。

$$
f_{i, j, l, r, 1, 1} = S_{l, r} + \max_{l\le p \le r\le q} \left \{ \max_{0\le y\le 1} \left \{ f_{i - 1,j - (r - l + 1),p, q, 1, y} \right  \} \right \}
$$

$$
f_{i, j, l, r, 0, 0} = S_{l, r} + \max_{p\le l \le q\le r} \left \{ \max_{0\le x\le 1} \left \{ f_{i - 1,j - (r - l + 1),p, q, x, 0} \right  \} \right \}
$$

$$
f_{i, j, l, r, 1, 0} = S_{l, r} + \begin{cases}
f_{i - 1, 0, 0, 0, 1, 0} &{\mathrm{if\ }} j = r - l + 1 > 0\\
\max_{l\le p \le q\le r} \left \{ f_{i - 1,j - (r - l + 1), p, q, 1, 0} \right \} &{\mathrm{if\ }} j > r - l + 1 > 0
\end{cases}
$$

$$
f_{i, j, l, r, 0, 1} = S_{l, r} + \max_{p \le l \le r \le q} \left \{ \max_{0\le x \le 1} \left \{ \max_{0\le y \le 1} \left \{ f_{i - 1, j - (r - l + 1), p, q, x, y} \right \} \right \} \right \}
$$

我们发现 $n, m, k$ 很小，因此暴力转移即可。

本题还要求输出方案，我们记录每个阶段从上一个阶段的转移来源最后回溯输出即可。

本题转移不算难想，但是代码实现细节较多，具体见代码。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define P(C) [C][C * C][C][C][2][2]
#define ft(tp, i, l, r) for (tp i = l; i <= r; i ++)
constexpr int N = 17;
int n, m, k, f P(N), a[N][N];
struct lst {
	int i, j, l, r, x, y;
	lst () : i(0), j(0), l(0), r(0), x(0), y(0) {};
	lst (int a, int b, int c, int d, int e, int f) : 
		i(a), j(b), l(c), r(d), x(e), y(f) {};
} pr P(N), ed;
void dp (int i, int j, int l, int r) {
	i64 sum = 0, len = r - l + 1, dt = 0;
	ft (int, p, l, r) sum += a[i][p];
	if (j == len) dt = f[i - 1][0][0][0][1][0];
	else ft (int, p, l, r) ft(int, q, p, r) if (f[i - 1][j - len][p][q][1][0] > dt) 
		dt = f[i - 1][j - len][p][q][1][0], pr[i][j][l][r][1][0] = lst(i - 1, j - len, p, q, 1,0);
	f[i][j][l][r][1][0] = sum + dt, dt = 0;
	ft(int, p, l, r) ft(int, q, r, m) ft(int, x, 0, 1) if (f[i - 1][j - len][p][q][1][x] > dt) 
		dt = f[i - 1][j - len][p][q][1][x], pr[i][j][l][r][1][1] = lst(i - 1, j - len, p, q, 1,x);
	f[i][j][l][r][1][1] = sum + dt, dt = 0;
	ft(int, p, 1, l) ft(int, q, l, r) ft(int, x, 0, 1) if (f[i - 1][j - len][p][q][x][0] > dt) 
		dt = f[i - 1][j - len][p][q][x][0], pr[i][j][l][r][0][0] = lst(i - 1, j - len, p, q, x,0);
	f[i][j][l][r][0][0] = sum + dt, dt = 0;
	ft(int, p, 1, l) ft(int, q, r, m) ft(int, x, 0, 1) ft(int, y, 0, 1) 
		if (f[i - 1][j - len][p][q][x][y] > dt) dt = f[i - 1][j - len][p][q][x][y], 
			pr[i][j][l][r][0][1] = lst(i - 1, j - len, p, q, x, y);
	f[i][j][l][r][0][1] = sum + dt, dt = 0;
}
void print (lst p) {
	if (p.j == 0) return ;
	print (pr[p.i][p.j][p.l][p.r][p.x][p.y]);
	ft(int, i, p.l, p.r) cout << p.i << ' ' << i << '\n';
}
i64 findans() {
	i64 ans = 0;
	ft(int, i, 1, n) ft(int, l, 1, m) ft(int, r, l, m) 
		ft(int, x, 0, 1) ft(int, y, 0, 1) if (ans < f[i][k][l][r][x][y]) 
			ans = f[i][k][l][r][x][y], ed = lst(i, k, l, r, x, y);
	return ans;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> n >> m >> k;
	ft (int, i, 1, n) ft (int, j, 1, m) cin >> a[i][j];
	ft (int, i, 1, n) ft (int, j, 1, k) 
		ft (int, l, 1, m) ft (int, r, l, m) 
			if (j >= (r - l + 1)) dp(i, j, l, r);
	cout << "Oil : " << findans() << '\n';
	return print(ed), 0;
}
```

---

## 作者：high_sky (赞：5)

# P10972 I-Country 题目分析
[题目链接](https://www.luogu.com.cn/problem/P10972)
## 分析题目性质

观察题目，可以发现的是一个凸多边形一定满足：

- 每一行的左端点列号先递减后递增。
- 每一行的右端点列号先递增后递减。

我们可以以此想到**线性 $dp$**。

## 思路

根据上述，我们需要关注以下的信息：

- 当前的左端点。
- 当前的右端点。

- 这一行以左端点开始连续选多少个。
- 当前左端点列号需要满足的单调性。
- 当前右端点列号需要满足的单调性。

显然的，右端点、左端点和选的格子数知道两个就可确定第三个的值。

因此我们设：$f_{i,j,l,r,0/1,0/1}$ 表示前 $i$ 行已经处理完毕加上第 $i$ 行有 $j$ 个格子，第 $i$ 行选择第 $l$ 到 $r$ 的格子，且左端点、右端点列号满足现在该有的单调性的最大价值（其中 $0$ 表示递减，$1$ 表示递增）。

考虑分类讨论，以下令 $t=\sum_{w=l}^r a_{i,w},lst=j-(r-l+1)$。

- 两边扩张状态：
  - $f_{i,j,l,r,1,0}=t+\max_{l\leq l_2\leq r_2\leq r}\{f_{i-1,lst,l_2,r_2,1,0}\}.$
- 左边扩张，右边收缩：
  - $f_{i,j,l,r,1,1}=t+\max_{l\leq l_2\leq r\leq r_2}\left\{\max_{p_2\in[0,1]}\left\{f_{i-1,lst,l_2,r_2,1,p_2}\right\}\right\}.$
- 左边收缩，右边扩张：
  - $f_{i,j,l,r,0,0}=t+\max_{l_2\leq l\leq r_2\leq r}\left\{\max_{p_1\in[0,1]}\left\{f_{i-1,lst,l_2,r_2,p_1,0}\right\}\right\}.$
- 两边收缩状态：
  - $f_{i,j,l,r,0,1}=t+\max_{l_2\leq l\leq r\leq r_2}\left\{\max_{p_1\in[0,1]}\left\{\max_{p_2\in[0,1]}\left\{f_{i-1,lst,l_2,r_2,p_1,p_2}\right\}\right\}\right\}.$

对于路径只需要记录当前状态的决策点即可，记得初始化一些必要的变量。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
#define N 20
using namespace std;
int n,m,K,a[N][N],sum[N][N];
struct node{
	int val;
	int prej,prel,prer;
	bool type1,type2;//to find the last.
	void init() {
		val = prej = prel = prer = 0;
		type1 = type2 = 0;
	}
	bool operator<(const node&adv) const {
		return val < adv.val;
	}
}f[N][N * N][N][N][2][2];
void debug(int i,int j,int l,int r,int typ1,int typ2) {
	printf("---------------- For %d %d %d %d %d %d --------------------\n",i,j,l,r,typ1,typ2);
	node t = f[i][j][l][r][typ1][typ2];
	cout << t.val << ' ' << t.prej << ' ' <<
			t.prel << ' ' << t.prer << ' ' << t.type1 <<' ' << t.type2 << endl;
	printf("----------------- END ---------------------\n");
}
signed main(){
	cin >> n >> m >> K;
	for (int i = 1;i <= n;i ++)
		for (int j = 1;j <= m;j ++)
			cin >> a[i][j];
	for (int i = 1;i <= n;i ++)
		for (int j = 1;j <= K;j ++)
			for (int l = 1;l <= m;l ++) 
				for (int r = l;r <= m && r - l + 1 <= j;r ++){
					int t = 0,lst = j - (r - l + 1);
					for (int times = l;times <= r;times ++) t += a[i][times];
//					cout << lst <<' ' << t <<endl;
					node mx;
					mx.init();//以下的转移都是按照题解上面的转移顺序写的
					for (int l2 = l;l2 <= r;l2 ++)
						for (int len = 1;l2 + len - 1 <= r && len <= lst;len ++) {
							int r2 = l2 + len - 1;
	//						mx = max(mx,f[i - 1][lst][l2][r2][1][0]);
							if (mx < f[i - 1][lst][l2][r2][1][0])
								mx = {f[i - 1][lst][l2][r2][1][0].val,lst,l2,r2,1,0};
						}
					f[i][j][l][r][1][0] = mx,f[i][j][l][r][1][0].val += t;
					
					mx.init();
					for (int l2 = l;l2 <= r;l2 ++)
						for(int r2 = r;r2 - l2 + 1 <= lst && r2 <= m;r2 ++) {
	//						mx = max(mx,f[i - 1][lst][l2][r2][1][0]),
	//						mx = max(mx,f[i - 1][lst][l2][r2][1][1]);
							if (mx < f[i - 1][lst][l2][r2][1][0])
								mx = {f[i - 1][lst][l2][r2][1][0].val,lst,l2,r2,1,0};
							if (mx < f[i - 1][lst][l2][r2][1][1])
								mx = {f[i - 1][lst][l2][r2][1][1].val,lst,l2,r2,1,1};
						}
					f[i][j][l][r][1][1] = mx,f[i][j][l][r][1][1].val += t;
					
					mx.init();
					for (int l2 = 1;l2 <= l;l2 ++)
						for (int r2 = l;r2 <= r && r2 - l2 + 1 <= lst;r2 ++){
	//						mx = max(mx,f[i - 1][lst][l2][r2][0][0]),
	//						mx = max(mx,f[i - 1][lst][l2][r2][1][0]);
							if (mx < f[i - 1][lst][l2][r2][0][0])
								mx = {f[i - 1][lst][l2][r2][0][0].val,lst,l2,r2,0,0};
							if (mx < f[i - 1][lst][l2][r2][1][0])
								mx = {f[i - 1][lst][l2][r2][1][0].val,lst,l2,r2,1,0};
						}
					f[i][j][l][r][0][0] = mx,f[i][j][l][r][0][0].val += t;
					
					mx.init();
					for (int l2 = 1;l2 <= l;l2 ++)
						for (int r2 = r;r2 <= m && r2 - l2 + 1 <= lst;r2 ++)
							for (int p1 = 0;p1 < 2;p1 ++)
								for (int p2 = 0;p2 < 2;p2 ++)
									if (mx < f[i - 1][lst][l2][r2][p1][p2])
										mx = {f[i - 1][lst][l2][r2][p1][p2].val,lst,l2,r2,p1,p2};
					f[i][j][l][r][0][1] = mx,f[i][j][l][r][0][1].val += t;
					
//					debug(i,j,l,r,0,0),debug(i,j,l,r,0,1),debug(i,j,l,r,1,0),debug(i,j,l,r,1,1);
				}
	node ans;
	ans.init();
	int sl = 0,sr = 0,si = 0;
	for (int i = 1;i <= n;i ++)
		for (int l = 1;l <= m;l ++)
			for (int r = l;r - l + 1 <= K && r <= m;r ++)
				for (int p1 = 0;p1 < 2;p1 ++)
					for (int p2 = 0;p2 < 2;p2 ++)
						if (ans < f[i][K][l][r][p1][p2])
							ans = f[i][K][l][r][p1][p2],sl = l,sr = r,si = i;
	cout << "Oil : " << ans.val << endl;
	int fc = K;
	for (;fc;) {
		for (int i = sl;i <= sr;i ++) cout << si << ' ' << i << endl,fc --;
		sl = ans.prel,sr = ans.prer,si --;
		ans = f[si][fc][sl][sr][ans.type1][ans.type2];
	}
	return 0;
}
```

---

## 作者：zdycoding (赞：4)

## 思路

分析题目后，我们可以发现当小正方形构成一个凸连通块时满足题意。本题难点在于状态设计，应关注如下信息：

  当前的行数，已选出的格子数，每行左右端点位置，左右轮廓的单调性类型（由凸多边形形状特性所决定）。于是状态表示为 $f[i][j][l][r][x][y]$，含义见上。

  由于 $x$ 与 $y$ 各有两种情况（$0$ 表示递增，$1$ 表示递减），故有如下四种转移方程：

  第一种：左列号递减，右列号递增：

  $f[i,j,l,r,1,0]=\sum_{p=l}^{r}{a[i,p]}+\min\limits_{l\le p\le q\le r} \left\{\ f[i-1,j-(r-l+1),p,q,1,0]\right\} $

  第二种：左列号递减，右列号递减：

  $f[i,j,l,r,1,1]=\sum_{p=l}^{r}{a[i,p]}+\min\limits_{l\le p\le r\le q} \left\{\ \max\limits_{0\le y\le 1} \left\{\ f[i-1,j-(r-l+1),p,q,1,y]\right\}\right\} $


  第三种：左列号递增，右列号递增：
  
$f[i,j,l,r,0,0]=\sum_{p=l}^{r}{a[i,p]}+\min\limits_{p\le l\le q\le r} \left\{\ \max\limits_{0\le x\le 1} \left\{\ f[i-1,j-(r-l+1),p,q,x,0]\right\}\right\} $

  第四种：左列号递增，右列号递减：

$f[i,j,l,r,0,1]=\sum_{p=l}^{r}{a[i,p]}+\min\limits_{p\le l\le r\le q} \left\{\ \max\limits_{0\le x\le 1} \left\{\ \max\limits_{0\le y\le 1} \left\{\ f[i-1,j-(r-l+1),p,q,x,y]\right\} \right\}\right\} $


  对于第一问，遍历 $i$，$l$，$r$，$x$，$y$，输出$f[i][k][l][r][x][y]$ 的最大值即可。关于输出方案，另用一数组记录每个状态的最优值的来源，最终递归输出即可。

  注：本题参考蓝书做法。

  ## 代码

  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 16
int n,m,k,a[N][N],f[N][N*N][N][N][2][2];
struct node{
	int i,j,l,r,x,y;
}pre[N][N*N][N][N][2][2],st;
void print(node st){
	if(st.j==0)return ;
	print(pre[st.i][st.j][st.l][st.r][st.x][st.y]);
	for(int j=st.l;j<=st.r;j++)
		cout<<st.i<<" "<<j<<"\n";
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			for(int l=1;l<=m;l++)
				for(int r=l;r<=m;r++){
					int val=0,add=0;
					for(int p=l;p<=r;p++)val+=a[i][p];
					//左列号递减，右列号递增
					if(j<r-l+1)continue;
					for(int p=l;p<=r;p++){
						for(int q=p;q<=r;q++){
							int t=f[i-1][j-(r-l+1)][p][q][1][0];
							if(t>add)add=t,pre[i][j][l][r][1][0]={i-1,j-(r-l+1),p,q,1,0};
						}
					}
					f[i][j][l][r][1][0]=val+add;
					//左列号递减，右列号递减 
					add=0;
					for(int p=l;p<=r;p++){
						for(int q=r;q<=m;q++){
							for(int y=0;y<=1;y++){
								int t=f[i-1][j-(r-l+1)][p][q][1][y];
								if(t>add)add=t,pre[i][j][l][r][1][1]={i-1,j-(r-l+1),p,q,1,y};
							} 
						}
					}
					f[i][j][l][r][1][1]=val+add;
					//左列号递增，右列号递增
					add=0;
					for(int p=1;p<=l;p++){
						for(int q=l;q<=r;q++){
							for(int x=0;x<=1;x++){
								int t=f[i-1][j-(r-l+1)][p][q][x][0];
								if(t>add)add=t,pre[i][j][l][r][0][0]={i-1,j-(r-l+1),p,q,x,0};
							} 
						}
					}
					f[i][j][l][r][0][0]=val+add;
					//左列号递增，右列号递减 
					add=0;
					for(int p=1;p<=l;p++){
						for(int q=r;q<=m;q++){
							for(int x=0;x<=1;x++){
								for(int y=0;y<=1;y++){
									int t=f[i-1][j-(r-l+1)][p][q][x][y];
									if(t>add)add=t,pre[i][j][l][r][0][1]={i-1,j-(r-l+1),p,q,x,y};
								}
							} 
						}
					}
					f[i][j][l][r][0][1]=val+add;
				} 
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int l=1;l<=m;l++)
			for(int r=l;r<=m;r++)
				for(int x=0;x<=1;x++)
					for(int y=0;y<=1;y++){
						int t=f[i][k][l][r][x][y];
						if(t>ans)ans=t,st={i,k,l,r,x,y};
					}	
	cout<<"Oil : "<<ans<<'\n';
	print(st);
	return 0;
}


```

---

## 作者：liuChF (赞：2)

比较有趣的题，首先要分析出这个图形是一个**凸连通块**：最后的图形一定是一个从上到下，宽度先增大，再减小的图形，然后就是状态的定义，要考虑几个东西：
- 转移到第几行
- 已经选了几块
- 上一行的左端点、右端点
- 上一行左右端点的单调性状态

我们可以设 $f_{i,j,l,r,0/1,0/1}$ 表示前 $i$ 行，已经选了 $j$ 个正方形，这一行选 $l\sim r$ 这一段，扩展/收缩。然后分 $4$ 类单调性进行转移，仔细推一下是比较好转移的，初始状态全部为 $0$ 即可。

至于输出方案，常规套路，用一个 `pre` 数组存每个状态是从哪个状态转移过来的，递归输出就行了。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define fq(i,d,u) for(int i(d); i <= u; ++i)
#define fr(i,u,d) for(int i(u); i >= d; --i)
using namespace std;
const int N = 16;
struct from {
	int i, j, l, r, x, y;
} pre[N][N * N][N][N][2][2], st;
int n, m, k, a[N][N], f[N][N * N][N][N][2][2], ans;
// f[i][j][l][r][0/1][0/1] 前 i 行,已经选了 j 个,最后一行为 [i, j],  1: 向左, 0: 向右(指从上一个状态到这个状态的端点单调性)
void find(from p) {
	if (p.j == 0) return ;
	find(pre[p.i][p.j][p.l][p.r][p.x][p.y]);
	fq(i, p.l, p.r) cout << p.i << ' ' << i << '\n';
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m >> k;
	fq(i, 1, n) fq(j, 1, m) cin >> a[i][j];
	fq(i, 1, n) fq(j, 1, k) fq(l, 1, m) fq(r, l, m) { // 此时状态已经枚举好了
		int val = 0; // 这一行的价值
		fq(p, l, r) val += a[i][p];
		// (1,0) 在向两边扩展
		if (j < (r - l + 1)) continue;
		int ret = 0;
		fq(p, l, r) fq(q, p, r) {
			int t = f[i - 1][j - (r - l + 1)][p][q][1][0];
			if (t > ret) ret = t, pre[i][j][l][r][1][0] = {i - 1, j - (r - l + 1), p, q, 1, 0};
		}
		f[i][j][l][r][1][0] = ret + val;
		// (1,1) 在向左
		ret = 0; // l <= p <= r <= q
		fq(p, l, r) fq(q, r, m) fq(x, 0, 1) {
			int t = f[i - 1][j - (r - l + 1)][p][q][1][x];
			if (t > ret) ret = t, pre[i][j][l][r][1][1] = {i - 1, j - (r - l + 1), p, q, 1, x};
		}
		f[i][j][l][r][1][1] = ret + val;
		// (0,0) 在向右
		ret = 0; // 1 <= p <= l <= q <= r
		fq(p, 1, l) fq(q, l, r) fq(x, 0, 1) {
			int t = f[i - 1][j - (r - l + 1)][p][q][x][0];
			if (t > ret) ret = t, pre[i][j][l][r][0][0] = {i - 1, j - (r - l + 1), p, q, x, 0};
		}
		f[i][j][l][r][0][0] = ret + val;
		// (0,1) 在向内收缩
		ret = 0; // q <= l <= r <= p
		fq(p, 1, l) fq(q, r, m) fq(x, 0, 1) fq(y, 0, 1) {
			int t = f[i - 1][j - (r - l + 1)][p][q][x][y];
			if (t > ret) ret = t, pre[i][j][l][r][0][1] = {i - 1, j - (r - l + 1), p, q, x, y};
		}
		f[i][j][l][r][0][1] = ret + val;
	}
	int ans = 0;
	fq(i, 1, n) fq(l, 1, m) fq(r, l, m) fq(x, 0, 1) fq(y, 0, 1) {
		int t = f[i][k][l][r][x][y];
		if (ans < t) ans = t, st = {i, k, l, r, x, y};
	}
	cout << "Oil : " << ans << '\n';
	find(st);
	return 0;
}
```

---

## 作者：W_C_B_H (赞：1)

不难发现，“从任何一个正方形到另一个正方形只能沿着两个方向移动”相当于“该连通块是凸的”。任何一个凸连通块可以划分成连续的若干行，每行的左端点列号先递减、后递增（均为非严格，下同），右端点列号先递增、后递减。

我们可以一次考虑从 $N\times M$ 矩阵的每一行中选择哪些格子来构成所求的连通块，则需要关注的信息有：

1. 当前已经处理完的行数；
2. 已经选出的格子数；
3. 当前行已选格子的左、右端点位置——为了确定下一行左、右端点的位置，以满足单调性；
4. 当前左、右侧轮廓的单调性类型——列号递增还是递减。

行数和格子数可以作为 dp 的“阶段”，每次转移到下一行，同时选出的格子数增加，在这两个维度上都符合“线性增长”的特点。因此，可以设计如下的状态表示：$dp_{i,j,l,r,x,y}$ 表示处理完前 $i$ 行，选择了 $j$ 个格子，其中第 $i$ 行选择了第 $[l,r]$ 个格子（若不选则 $l=r=0$，否则显然应该保证 $j\ge r-l+1$），左、右边界的单调性类型分别为 $x,y$（$0$ 表示递增，$1$ 表示递减）时，能构成的凸连通块的最大权值和。

状态转移方程如下（记 $len=r-l+1,S=\sum_{k=l}^rA_{i,k}$，$S$ 在前缀和预处理后可以 $O(1)$ 求出）：

1. 左边界列号递减，右边界列号递增（两边都扩）：

   $dp_{i,j,l,r,1,0}=S+\begin{cases}dp_{i-1,0,0,0,1,0}&\text{if }j=len\\\begin{aligned}\max_{l\le p\le q\le r}\{dp_{i-1,j-len,p,q,1,0}\}\end{aligned}&\text{if }j>len\end{cases}$；

1. 左右边界行号都递减（左扩右缩）：

   $\begin{aligned}dp_{i,j,l,r,1,1}=S+\max_{l\le p\le r\le q\le M}\{\max_{0\le y\le1}\{dp_{i-1,j-len,p,q,1,y}\}\}\end{aligned}$；

1. 左右边界行号都递增（左缩右扩）：

   $\begin{aligned}dp_{i,j,l,r,0,0}=S+\max_{1\le p\le l\le q\le r}\{\max_{0\le x\le1}\{dp_{i-1,j-len,p,q,x,0}\}\}\end{aligned}$；

1. 左边界列号递增，右边界列号递减（两边都缩）：

   $\begin{aligned}dp_{i,j,l,r,0,1}=S+\max_{1\le p\le l\le r\le q\le M}\{\max_{0\le x\le1}\{\max_{0\le y\le1}\{dp_{i-1,j-len,p,q,x,y}\}\}\}\end{aligned}$。

初始状态为 $dp_{i,0,0,0,1,0}=0$，最终答案即为 $\max\{dp_{i,K,l,r,x,y}\}$。时间复杂度 $O(NM^4K)=O(N^2M^5)$。

本题还需要输出方案，在 dp 过程中维护一个大小与 dp 状态大小相同的数组 $f$，记录每个状态的“最优解”是从哪里转移过来的。最终在求出答案后，通过递归即可输出方案。

Code（细节非常多，很容易写错）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read()
{
	int r=0; char c=getchar(); bool f=0;
	while(c<48 || c>57){ if(c=='-'){ f=1; } c=getchar(); }
	while(c>=48 && c<=57){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return f?-r:r;
}
void write(int x)
{
	if(x<0){ putchar('-'); x=-x; }
	if(x>9){ write(x/10); }
	putchar(x%10+48);
}
void write(string s)
{
	for(char c:s){ putchar(c); }
}
void writeln(int x)
{
	write(x); putchar('\n');
}
#define N 20
#define K 230
struct pos	// 记录一个状态 
{
	int pi,pj,pl,pr,px,py;
	pos(int _i=0,int _j=0,int _l=0,int _r=0,int _x=0,int _y=0)
	{
		pi=_i, pj=_j, pl=_l, pr=_r, px=_x, py=_y;
	}
}f[N][K][N][N][2][2],ans=pos(0,0,0,0,1,0);	// f 表示每个状态的最优解从哪里转移而来, ans 表示最终答案在哪个状态 
int n,m,k,a[N][N],sum[N][N],dp[N][K][N][N][2][2];
pos getf(pos p)
{
	return f[p.pi][p.pj][p.pl][p.pr][p.px][p.py];
}
int getdp(pos p)
{
	return dp[p.pi][p.pj][p.pl][p.pr][p.px][p.py];
}
void print(pos p)	// 递归输出方案 
{
	if(!p.pl || !p.pr)
	{
		return;
	}
	print(getf(p));
	for(int i=p.pl;i<=p.pr;i++)
	{
		write(p.pi);
		putchar(' ');
		writeln(i);
	}
}
signed main()
{
	n=read(), m=read(), k=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			sum[i][j]=sum[i][j-1]+a[i][j];	// 前缀和 
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int l=1;l<=m;l++)
		{
			for(int r=l;r<=m;r++)
			{
				int len=r-l+1, s=sum[i][r]-sum[i][l-1];
				for(int j=len;j<=min(m*i,k);j++)
				{
					f[i][j][l][r][1][0]=pos(i-1,0,0,0,1,0);	// 两边都扩 
					f[i][j][l][r][1][1]=pos(i-1,0,0,0,1,0);	// 左扩右缩 
					f[i][j][l][r][0][0]=pos(i-1,0,0,0,1,0);	// 左缩右扩 
					f[i][j][l][r][0][1]=pos(i-1,0,0,0,1,0);	// 两边都缩 
					if(j==len)
					{
						dp[i][j][l][r][1][0]=s+dp[i-1][0][0][0][1][0];
					}
					else
					{
						for(int p=l;p<=r;p++)	// 两边都扩 
						{
							for(int q=p;q<=r;q++)
							{
								if(getdp(f[i][j][l][r][1][0]) < dp[i-1][j-len][p][q][1][0])
								{
									dp[i][j][l][r][1][0]=s+dp[i-1][j-len][p][q][1][0];
									f[i][j][l][r][1][0]=pos(i-1,j-len,p,q,1,0);
								}
							}
						}
					}
					for(int p=l;p<=r;p++)	// 左扩右缩 
					{
						for(int q=r;q<=m;q++)
						{
							for(int y=0;y<2;y++)
							{
								if(getdp(f[i][j][l][r][1][1]) < dp[i-1][j-len][p][q][1][y])
								{
									dp[i][j][l][r][1][1]=s+dp[i-1][j-len][p][q][1][y];
									f[i][j][l][r][1][1]=pos(i-1,j-len,p,q,1,y);
								}
							}
						}
					}
					for(int p=1;p<=l;p++)	// 左缩右扩 
					{
						for(int q=l;q<=r;q++)
						{
							for(int x=0;x<2;x++)
							{
								if(getdp(f[i][j][l][r][0][0]) < dp[i-1][j-len][p][q][x][0])
								{
									dp[i][j][l][r][0][0]=s+dp[i-1][j-len][p][q][x][0];
									f[i][j][l][r][0][0]=pos(i-1,j-len,p,q,x,0);
								}
							}
						}
					}
					for(int p=1;p<=l;p++)	// 两边都缩 
					{
						for(int q=r;q<=m;q++)
						{
							for(int x=0;x<2;x++)
							{
								for(int y=0;y<2;y++)
								{
									if(getdp(f[i][j][l][r][0][1]) < dp[i-1][j-len][p][q][x][y])
									{
										dp[i][j][l][r][0][1]=s+dp[i-1][j-len][p][q][x][y];
										f[i][j][l][r][0][1]=pos(i-1,j-len,p,q,x,y);
									}
								}
							}
						}
					}
					if(j==k)	// 统计答案 
					{
						for(int x=0;x<2;x++)
						{
							for(int y=0;y<2;y++)
							{
								if(getdp(ans)<getdp(pos(i,j,l,r,x,y)))
								{
									ans=pos(i,j,l,r,x,y);
								}
							}
						}
					}
				}
			}
		}
	}
	write("Oil : ");
	writeln(getdp(ans));
	print(ans);
	return 0;
}
```

再次提醒：本题代码细节很多，特别是转移时 $x,y,p,q$ 的取值范围，出错时务必认真检查！

---

## 作者：hinin (赞：0)

代码长度感人。

### 题目描述

在 $N \times M$ 的矩阵中，要求寻找一个包含 $K$ 个格子的格子的权值和最大的凸连通块。

### 思路

设状态 $f_{i,j,l,r,op1,op2}$ 表示当前处理到第 $i$ 行，已经选了 $j$ 个格子，第 $i$ 行选择 $[l,r]$ 区间且两侧分别为 $op1$/$op2$（单调延长 / 单调缩短）的所有方案，值是最多石油。

状态计算可以分 $4$ 种情况（见代码）。

$pre$ 是预处理出的前驱数组。

$cost(i,l,r)$ 表示前缀和维护的第 $i$ 行的 $[l,r]$ 区间的权值和。

### 代码

``` cpp
#define repeat(x, a, b) for(int x = a; x <= b; x ++)
#define f(y, x) f[i][j][l][r][(y)][(x)]
#define pre(y, x) pre[i][j][l][r][(y)][(x)]

if (j < r - l + 1) { continue; }
			
repeat(ll, l, r) repeat(rr, ll, r) {
    int t = f[i - 1][j - (r - l + 1)][ll][rr][0][0] + cost(i, l, r);
				
    if (f(0, 0) < t) {
	    f(0, 0) = t;
	    pre(0, 0) = {i - 1, j - (r - l + 1), ll, rr, 0, 0};
    }
}
			
repeat(ll, l, r) repeat(rr, r, m) {
	repeat(op2, 0, 1) {
		int t = f[i - 1][j - (r - l + 1)][ll][rr][0][op2] + cost(i, l, r);
					
		if (f(0, 1) < t) {
			f(0, 1) = t;
			pre(0, 1) = {i - 1, j - (r - l + 1), ll, rr, 0, op2};
		}
	}
}
			
repeat(ll, 1, l) repeat(rr, l, r) {
	repeat(op1, 0, 1) {
		int t = f[i - 1][j - (r - l + 1)][ll][rr][op1][0] + cost(i, l, r);
		
		if (f(1, 0) < t) {
			f(1, 0) = t;
			pre(1, 0) = {i - 1, j - (r - l + 1), ll, rr, op1, 0};
		}
	}
}

repeat(ll, 1, l) repeat(rr, r, m) {
	repeat(op1, 0, 1) repeat(op2, 0, 1) {
		int t = f[i - 1][j - (r - l + 1)][ll][rr][op1][op2] + cost(i, l, r);
		
		if (f(1, 1) < t) {
			f(1, 1) = t;
			pre(1, 1) = {i - 1, j - (r - l + 1), ll, rr, op1, op2};
		}
	}
}
			
if (j == k) repeat(op1, 0, 1) repeat(op2, 0, 1)  {
    if (res < f(op1, op2)) {
		res = f(op1, op2);
		st = {i, j, l, r, op1, op2};
	}
}
```

---

## 作者：andycode (赞：0)

## 思路
因为占据的连通块的左端点先递减、后递增，右端点先递增、后递减，所以设 $f_{i,j,l,r,x(0/1),y(0/1)}$ 为前 $i$ 行中，选择 $j$ 个方格，其中第 $i$ 行选择的区间的左端点为 $l$，右端点为 $r$，$x$ 表示左端点是否出现递增，$y$ 表示右端点是否递增的所有方案的最大石油数量。

容易列出状态转移方程，
$$
f_{i,j,l,r,0,0}=\max\{f_{i-1,j-(r-l+1),a,b,0,0},f_{i-1,j-(r-l+1),a,b,0,1}\}+s_{i,r}-s_{i,l-1}\\
f_{i,j,l,r,0,1}=\max\{f_{i-1,j-(r-l+1),a,b,0,1}\}+s_{i,r}-s_{i,l-1}\\
f_{i,j,l,r,1,0}=\max\{f_{i-1,j-(r-l+1),a,b,0,0},f_{i-1,j-(r-l+1),a,b,0,1},f_{i-1,j-(r-l+1),a,b,1,0},f_{i-1,j-(r-l+1),a,b,1,1}\}+s_{i,r}-s_{i,l-1}\\
f_{i,j,l,r,1,1}=\max\{f_{i-1,j-(r-l+1),a,b,0,1},f_{i-1,j-(r-l+1),a,b,1,1}\}+s_{i,r}-s_{i,l-1}\\
$$
。

注意，由于联通，所以 $r\ge a$ 且 $l\le b$。因为递增递减，所以当 $x=0$ 时，$l\le a$，当 $x=1$ 时，$l\ge a$，当 $y=0$ 时，$r\le b$，当 $y=1$ 时，$r\ge b$。$s_{i,j}$ 为第 $i$ 行的前缀和，不是二维前缀和。

最终答案为 $\max\{f_{i,k,l,r,x,y}\}$，输出路径可以存一个结构体 $la_{i,j,l,r,x,y}$ 统计 $f_{i,j,l,r,x,y}$ 从哪里转移来。

思路容易想，代码细节却很多，~~本人被硬控了几个小时~~。
## 代码
```cpp
//要C++14(GCC 9)，不然会RE
#include <bits/stdc++.h>
using namespace std;
const int N=25;
struct Last{
    int i,j,l,r,x,y;
}la[N][N*N][N][N][2][2];
int n,m,k,a[N][N],s[N][N],f[N][N*N][N][N][2][2];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            s[i][j]=s[i][j-1]+a[i][j];
        }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=i*m;j++)
            for(int l=1;l<=m;l++)
                for(int r=l;r<=m;r++){
                    if(r-l+1+(i-1)*m<j || j<r-l+1)
                        continue;
                    int sum=s[i][r]-s[i][l-1];
                    if(i==1){
                        f[i][j][l][r][0][0]=f[i][j][l][r][0][1]=f[i][j][l][r][1][0]=f[i][j][l][r][1][1]=sum;
                        continue;
                    }
                    //x=0,y=0
                    for(int x=1;x<=m;x++)
                        for(int y=x;y<=m;y++)
                            if(!(y<l || x>r) && x>=l && y>=r){//注意要联通,l要递减,r要递减
                                if(f[i-1][j-(r-l+1)][x][y][0][0]+sum>f[i][j][l][r][0][0])
                                    f[i][j][l][r][0][0]=f[i-1][j-(r-l+1)][x][y][0][0]+sum,la[i][j][l][r][0][0]={i-1,j-(r-l+1),x,y,0,0};

                                if(f[i-1][j-(r-l+1)][x][y][0][1]+sum>f[i][j][l][r][0][0])
                                    f[i][j][l][r][0][0]=f[i-1][j-(r-l+1)][x][y][0][1]+sum,la[i][j][l][r][0][0]={i-1,j-(r-l+1),x,y,0,1};
                            }
                    //x=0,y=1
                    for(int x=1;x<=m;x++)
                        for(int y=x;y<=m;y++)
                            if(!(y<l || x>r) && x>=l && y<=r){//l要递减,r要递增
                                if(f[i-1][j-(r-l+1)][x][y][0][1]+sum>f[i][j][l][r][0][1])
                                    f[i][j][l][r][0][1]=f[i-1][j-(r-l+1)][x][y][0][1]+sum,la[i][j][l][r][0][1]={i-1,j-(r-l+1),x,y,0,1};
                            }
                    //x=1,y=0
                    for(int x=1;x<=m;x++)
                        for(int y=x;y<=m;y++)
                            if(!(y<l || x>r) && x<=l && y>=r){//l要递增,r要递减
                                if(f[i-1][j-(r-l+1)][x][y][0][0]+sum>f[i][j][l][r][1][0])
                                    f[i][j][l][r][1][0]=f[i-1][j-(r-l+1)][x][y][0][0]+sum,la[i][j][l][r][1][0]={i-1,j-(r-l+1),x,y,0,0};

                                if(f[i-1][j-(r-l+1)][x][y][0][1]+sum>f[i][j][l][r][1][0])
                                    f[i][j][l][r][1][0]=f[i-1][j-(r-l+1)][x][y][0][1]+sum,la[i][j][l][r][1][0]={i-1,j-(r-l+1),x,y,0,1};

                                if(f[i-1][j-(r-l+1)][x][y][1][0]+sum>f[i][j][l][r][1][0])
                                    f[i][j][l][r][1][0]=f[i-1][j-(r-l+1)][x][y][1][0]+sum,la[i][j][l][r][1][0]={i-1,j-(r-l+1),x,y,1,0};

                                if(f[i-1][j-(r-l+1)][x][y][1][1]+sum>f[i][j][l][r][1][0])
                                    f[i][j][l][r][1][0]=f[i-1][j-(r-l+1)][x][y][1][1]+sum,la[i][j][l][r][1][0]={i-1,j-(r-l+1),x,y,1,1};
                            }
                    //x=1,y=1
                    for(int x=1;x<=m;x++)
                        for(int y=x;y<=m;y++)
                            if(!(y<l || x>r) && x<=l && y<=r){//l要递增,r要递增
                                if(f[i-1][j-(r-l+1)][x][y][0][1]+sum>f[i][j][l][r][1][1])
                                    f[i][j][l][r][1][1]=f[i-1][j-(r-l+1)][x][y][0][1]+sum,la[i][j][l][r][1][1]={i-1,j-(r-l+1),x,y,0,1};

                                if(f[i-1][j-(r-l+1)][x][y][1][1]+sum>f[i][j][l][r][1][1])
                                    f[i][j][l][r][1][1]=f[i-1][j-(r-l+1)][x][y][1][1]+sum,la[i][j][l][r][1][1]={i-1,j-(r-l+1),x,y,1,1};
                            }
                }

    int ans=0;
    Last tmp;
    for(int i=1;i<=n;i++)
        for(int l=1;l<=m;l++)
            for(int r=l;r<=m;r++){
                if(f[i][k][l][r][0][0]>ans)
                    ans=f[i][k][l][r][0][0],tmp={i,k,l,r,0,0};//tmp存储当前的状态

                if(f[i][k][l][r][0][1]>ans)
                    ans=f[i][k][l][r][0][1],tmp={i,k,l,r,0,1};

                if(f[i][k][l][r][1][0]>ans)
                    ans=f[i][k][l][r][1][0],tmp={i,k,l,r,1,0};

                if(f[i][k][l][r][1][1]>ans)
                    ans=f[i][k][l][r][1][1],tmp={i,k,l,r,1,1};
            }
    printf("Oil : %d",ans);
    while(tmp.j && tmp.i){//输出路径
        for(int i=tmp.l;i<=tmp.r;i++)
            printf("\n%d %d",tmp.i,i);
        tmp=la[tmp.i][tmp.j][tmp.l][tmp.r][tmp.x][tmp.y];
    }
    return 0;
}
```

---

## 作者：LDY_ (赞：0)

麻烦的 dp 题，写篇题解加深理解。
发现满足要求的情况当且仅当最后的范围是一个凹四边形。结合数据范围我们可以设计状态如下。

设 $f_{i,j,l,r,0/1,0/1}$ 表示前 $i$ 行选了 $j$ 块，这一行选择 $l$ 至 $r$ ，当前图形处于向两边扩展/向内收缩/向左扩展/向右扩展阶段。 

剩下的就是比较套路的东西，依据不同状态转移，并记录转移前驱以获得方案。**注意题目要求正序输出**。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int f[16][230][16][16][2][2];
struct Pre{
	int i,j,l,r,p,q;
}pre[16][230][16][16][2][2];
Pre en;
int w[20][20];
void getans(Pre p){
	if(p.j==0) return;
	getans(pre[p.i][p.j][p.l][p.r][p.p][p.q]);
	for(int i=p.l;i<=p.r;i++) cout<<p.i<<" "<<i<<endl;
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		cin>>w[i][j];
	}
	}
	for(int i=1;i<=n;i++){
	for(int j=1;j<=k;j++){
	for(int l=1;l<=m;l++){
	for(int r=l;r<=m;r++){
		int tot=0;
		for(int p=l;p<=r;p++) tot+=w[i][p];
		if(j<(r-l+1)) continue;
		// 向外 
		int maxx=0;
		for(int p=l;p<=r;p++){
		for(int q=p;q<=r;q++){
			int res=f[i-1][j-(r-l+1)][p][q][1][0];
			if(res>maxx){
				maxx=res;
				pre[i][j][l][r][1][0]=(Pre){i-1,j-(r-l+1),p,q,1,0};
			}
		}
		}
		f[i][j][l][r][1][0]=maxx+tot;
		//
		//  向右 
		maxx=0;
		for(int p=1;p<=l;p++){
		for(int q=l;q<=r;q++){
		for(int x=0;x<=1;x++){
			int res=f[i-1][j-(r-l+1)][p][q][x][0];
		     if(res>maxx){
				maxx=res;
				pre[i][j][l][r][0][0]=(Pre){i-1,j-(r-l+1),p,q,x,0};
			}
		}
		}
		}
		f[i][j][l][r][0][0]=maxx+tot;
		//
		//  向左 
		maxx=0;
		for(int p=l;p<=r;p++){
		for(int q=r;q<=m;q++){
		for(int x=0;x<=1;x++){
			int res=f[i-1][j-(r-l+1)][p][q][1][x];
		     if(res>maxx){
				maxx=res;
				pre[i][j][l][r][1][1]=(Pre){i-1,j-(r-l+1),p,q,1,x};
			}
		}
		}
		}
		f[i][j][l][r][1][1]=maxx+tot;
		//
		//向内
		 maxx=0;
		for(int p=1;p<=l;p++){
		for(int q=r;q<=m;q++){
		for(int x=0;x<=1;x++){
		for(int y=0;y<=1;y++){	
			int res=f[i-1][j-(r-l+1)][p][q][x][y];
		     if(res>maxx){
				maxx=res;
				pre[i][j][l][r][0][1]=(Pre){i-1,j-(r-l+1),p,q,x,y};
			}
		}
		}
		}
	}
		f[i][j][l][r][0][1]=maxx+tot;
		//
		 
	}		
	}
	}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
	for(int l=1;l<=m;l++){
	for(int r=l;r<=m;r++){
	for(int x=0;x<=1;x++){
	for(int y=0;y<=1;y++){
		if(f[i][k][l][r][x][y]>ans){
			ans=f[i][k][l][r][x][y];
			en=(Pre){i,k,l,r,x,y};
		}
	}
	}
	}
	}
	}
	cout<<"Oil : "<<ans<<endl;
	getans(en);
}
```

---

## 作者：dci66666 (赞：0)

这题成噩梦了，写完了来写篇题解。
怎么好题无人啊。

## 题目理解
两条消息，选 $k$ 个正方形，从任意一个正方形到其他任意一个正方形都只需要两个方向（题目说的很晕）。
这个条件其实就是要满足类似凸边形的条件（注意不是凸边形，因为当方向不变时斜率可以变）。这时我们考虑 $dp$。 


所以我们的思路也随之而来：
## 思路
我们惊奇的发现里面具有单调性，比如开始收缩时不能再放大。
1. 左移。
2. 右移。
3. 收缩。
4. 放大。

其中的转化也很明显。即放大前只能放大（其他情况都不满足单调性），左移不能在右移后面，收缩后什么也不能干。
~~是不是像极了血型。~~

我们可以开 $6$ 维 $dp$。分别代表枚举到多少行，左右端点，左右节点单调性，以及还剩多少选择数量。

转移是不是很简单？~~这写了我几个小时。~~

可以上代码了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int dp[25][405][25][25][2][2],sum[25][25],ans;
struct node{
	int h,l,r,an1,an2,q,ans;
}pre[25][405][25][25][2][2]; 
void print(node x){
	if(x.ans==0)return ;
	print(pre[x.h][x.q][x.l][x.r][x.an1][x.an2]);
	for(int i=x.l;i<=x.r;i++)cout<<x.h<<" "<<i<<endl;
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
		    int a;
			cin>>a;
			sum[i][j]=sum[i][j-1]+a; 
		}
	}
	for(int i=1;i<=n;i++)for(int l=1;l<=m;l++)for(int r=l;r<=m;r++)for(int j=k;j>=r-l+1;j--){
		int t=r-l+1,tt=sum[i][r]-sum[i][l-1];
	    //左移
		for(int ll=l;ll<=r;ll++)for(int rr=ll;rr<=m;rr++)for(int x=0;x<=1;x++){ 
		int ret=dp[i][j-t][l][r][0][0];
		//cout<<ret<<" ";
		dp[i][j-t][l][r][0][0]=max(dp[i-1][j][ll][rr][0][x]+tt,dp[i][j-t][l][r][0][0]);	
		if(dp[i][j-t][l][r][0][0]>ret)pre[i][j-t][l][r][0][0]={i-1,ll,rr,0,x,j,dp[i-1][j][ll][rr][0][x]};
		//cout<<l<<" "<<r<<" "<<ll<<" "<<rr<<" "<<i<<" "<<dp[i][j-t][l][r][0][0]<<endl;
		} 
		//左面左移,右面右移 
		for(int ll=l;ll<=r;ll++)for(int rr=ll;rr<=r;rr++){
		int ret=dp[i][j-t][l][r][0][1];
		dp[i][j-t][l][r][0][1]=max(dp[i-1][j][ll][rr][0][1]+tt,dp[i][j-t][l][r][0][1]);
		if(dp[i][j-t][l][r][0][1]>ret)pre[i][j-t][l][r][0][1]={i-1,ll,rr,0,1,j,dp[i-1][j][ll][rr][0][1]};
		}
		//左面右移，右面左移 x1
		for(int ll=1;ll<=l;ll++)for(int rr=r;rr<=m;rr++)for(int x=0;x<=1;x++)for(int y=0;y<=1;y++){
		int ret=dp[i][j-t][l][r][1][0];
		dp[i][j-t][l][r][1][0]=max(dp[i-1][j][ll][rr][x][y]+tt,dp[i][j-t][l][r][1][0]);
		if(dp[i][j-t][l][r][1][0]>ret)pre[i][j-t][l][r][1][0]={i-1,ll,rr,x,y,j,dp[i-1][j][ll][rr][x][y]};
		}
		//右移
		for(int ll=1;ll<=l;ll++)for(int rr=l;rr<=r;rr++)for(int x=0;x<=1;x++){
		int ret=dp[i][j-t][l][r][1][1];
		dp[i][j-t][l][r][1][1]=max(dp[i-1][j][ll][rr][x][1]+tt,dp[i][j-t][l][r][1][1]);
		if(dp[i][j-t][l][r][1][1]>ret)pre[i][j-t][l][r][1][1]={i-1,ll,rr,x,1,j,dp[i-1][j][ll][rr][x][1]};
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			for(int l=1;l<=m;l++){
				for(int r=l;r<=m;r++){
					for(int x=0;x<=1;x++)for(int y=0;y<=1;y++){
						//cout<<i<<" "<<l<<" "<<r<<" "<<dp[i][j][l][r][x][y]<<endl;
					    if(ans<dp[i][j][l][r][x][y]){
						    ans=dp[i][j][l][r][x][y];
						    pre[0][0][0][0][0][0]={i,l,r,x,y,j,ans};
					    }
				    }
				}
			}
		}
	}
	//cout<<dp[2][0][1][1][0][0]<<endl;
	cout<<"Oil : "<<ans<<endl;
	print(pre[0][0][0][0][0][0]);
}
```

---

