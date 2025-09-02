# [ICPC 2020 Nanjing R] Harmonious Rectangle

## 题目描述

一个顶点着色的矩形是指四个顶点都被涂上颜色的矩形。对于一个顶点着色的矩形来说，如果我们可以找到两个相邻顶点的颜色相同，而另外两个顶点也互相颜色相同，则称这个矩形是和谐的。

例如，矩阵 
$\begin{bmatrix} 1 & 0\\ 1 & 0 \end{bmatrix}$，$\begin{bmatrix} 0 & 0\\ 1 & 1 \end{bmatrix}$ 和 $\begin{bmatrix} 1 & 1\\ 1 & 1 \end{bmatrix}$ 都是和谐的，而 $\begin{bmatrix} 1 & 0\\ 0 & 1 \end{bmatrix}$ 不是（相同的颜色有相同的数字，不同的颜色有不同的数字）。

对于集合中的每个点 $\{(x,y) |	1 \le x \le n, 1 \le y \le m, x,y \in \mathbb{Z}\}$，其中 $\mathbb{Z}$ 是所有整数的集合，Kotori 想将其涂成三种颜色之一：红色、蓝色或黄色。她想知道有多少种不同的着色方案，使得至少存在一个由这些点形成的边都平行于 $x$ 或 $y$ 轴的和谐矩形。也就是说，存在 $1 \le x_1 < x_2 \le n$ 和 $1 \le y_1 < y_2 \le m $，满足以下条件之一：

$\begin{cases} \text{color}(x_1, y_1) = \text{color}(x_1, y_2)\\ \text{color}(x_2, y_1) = \text{color}(x_2, y_2)\\ \end{cases}$

或者

$\begin{cases} \text{color}(x_1, y_1) = \text{color}(x_2, y_1)\\ \text{color}(x_1, y_2) = \text{color}(x_2, y_2)\\ \end{cases}$

其中 $\text{color}(x, y)$ 表示点 $(x, y)$ 的颜色。

如果两个着色计划中存在一个点在两个着色计划中颜色不同，那么认为这两个着色计划是不同的。

## 样例 #1

### 输入

```
3
1 4
2 2
3 3```

### 输出

```
0
15
16485```

# 题解

## 作者：SDLTF_凌亭风 (赞：4)

题解来源于一位和我组队且不愿透露姓名的好兄弟。

这个题有点类似于 2018 年考过的填数游戏。

首先考虑正难则反，也即考虑有多少染色不存在这样的子矩形。注意到，这样的子矩形的特征是两个同色格子在一行或者一列，另两个同色格子在一行或者一列。

所以，这样的矩阵必然满足，对于同行的两个同色格子，这两行其他列的对应位置两个格子必然不一样，列同理。

于是我们直接考虑某一行一种颜色的鸽子就好了，显然一行的某种颜色的格子不可能超过四个，由抽屉原理可以知道，必然在其他行会存在一个同色对，于是一行同色格子最多三个。然而只给了红黄蓝三种颜色，再用一次抽屉原理，当矩形的长或宽超过 $10$ 的时候，必然存在一种颜色出现超过 $4$ 次。由此分析，矩形的长和宽最多为 $9$。

然后写个爆搜就好了。不要认为最多可能状态有 $3^{81}$ 种，首先你可以剪枝，其次你在搜完之后就会发现有值时对应的 $n$ 和 $m$ 非常少，打个表就能过了。

记得特判 $n=1$ 或者 $m=1$ 的情况。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace  std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e5+51,MOD=1e9+7;
ll test,n,m,res;
ll c[15][15];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline void solve()
{
	n=read(),m=read(),n>m?swap(n,m):(void)1;
	if(n==1||m==1)
	{
		return (void)puts("0");
	}
	if(n>=8||m>=8)
	{
		return (void)printf("%d\n",qpow(3,n*m));
	}
	printf("%d\n",(qpow(3,n*m)-c[n][m]+MOD)%MOD);
}
int main()
{
	test=read();
	c[2][2]=66,c[2][3]=390,c[2][4]=1800,c[2][5]=6120,c[2][6]=13680,c[2][7]=15120;
	c[3][3]=3198,c[3][4]=13176,c[3][5]=27000,c[3][6]=13680,c[3][7]=15120;
	c[4][4]=24336,c[4][5]=c[5][5]=4320;
	for(register int i=1;i<=test;i++)
	{
		solve();	
	}
}

```



---

## 作者：hellolin (赞：2)


# P9629 [ICPC2020 Nanjing R] Harmonious Rectangle 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/p9629/) 获得更好的阅读体验！

运用小学学过的鸽巢原理推断一下，当 $\max(n, m)>9$ 的时候，由于我们只有三种颜色，任何染色方案都是合法的。染色方案数是 $3^{nm}$。

再来考虑 $\max(n,m)\le 9$ 的情况，合法染色方案数就是所有方案数减去不合法的方案数。

当然就八十几个情况，你要打表也是可以哒！这里我直接写了个搜。

``` cpp
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
using ll = long long;
// 三种颜色分别是 1、2、3
constexpr static ll N = 1e4 + 114, Mod = 1e9 + 7;
ll me[N][N];
int T, n, m;
ll ans;
int col[N][N];
int sel[4][N]; // 由于我们搜的是列，同时还需要考虑行的情况，sel[i][x] 表示第 x 行有多少个 i 颜色
bool ok(int x, int y, int d) {
    col[x][y] = d;
    if(sel[1][x] <= 3 && sel[2][x] <= 3 && sel[3][x] <= 3) {
        rep(int, i, 1, x - 1)
            rep(int, j, 1, y - 1) { // 根据题目的约束条件检查
                int d_ = col[i][j];
                if((d == col[i][y] && d_ == col[x][j])
                ||(d == col[x][j] && d_ == col[i][y])) return 0;
            }
        return 1;
    }
    return 0;
}
void dfs(int x, int y) {
    if(x > n) { // 搜完了记到 ans 里面
        ++ans;
        return;
    }
    if(y > m) { // 这一列可以了，考虑下一列
        dfs(++x, 1);
        return;
    }
    rep(int, i, 1, 3) {
        ++sel[i][x];
        if(ok(x, y, i)) // 继续搜
            dfs(x, y+1);
        --sel[i][x]; // 回溯掉
    }
}
void solve() {
    for(std::cin >> T; T--; [&](){
        std::cin >> n >> m;
        if(n > m) std::swap(n, m); // 优化小技巧
        if(me[n][m]) return std::cout << me[n][m] << '\n', void(); // 优化小技巧
        if(n == 1 || m == 1) return std::cout << 0 << '\n', void(); // 判掉只有一行或一列的情况
        if(n > 9 || m > 9) return std::cout << fpow(3ll, n*m, Mod) << '\n', void();
        ans = 0;
        dfs(1, 1);
        std::cout << (me[n][m] = (fpow(3ll, n*m, Mod) - ans + Mod) % Mod) << '\n'; // 所有情况去掉不合法情况
    }());
}
```



---

## 作者：WhitD (赞：2)

## 题目大意
给定 $n\times m$ 的矩阵，用三种颜色给矩阵的每个点染色。当矩阵某一行中有至少两个点和某一列中有至少两个点被染上相同的颜色时，我们称这种染色方案是合法的，求所有合法的方案数，答案对 $10^9+7$ 取模。
## 思路
首先考虑当 $m=1$ 或 $n=1$ 时，一定不存在合法的方案，因为我们要求同行或同列中有至少两个点颜色相同（~~只有一行或一列哪来的两个点~~）。

考虑抽屉原理，因为我们只有三种颜色，所以当 $m>9$ 或 $n>9$ 时，不论怎么染色都一定是合法的，根据乘法原理可得总方案数是 $3^{m\times n}$。

我们可以用暴力求出 $m\le9,n\le9$ 对应情况的方案数（~~打表出奇迹~~）。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
typedef long long ll;
ll qpow(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1)
			res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res%mod;
}
int T;
int yuanshen[10][10]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,339,4761,52929,517761,4767849,43046721,387420489,0,0,339,16485,518265,14321907,387406809,460338013,429534507,597431612,0,0,4761,518265,43022385,486780060,429534507,792294829,175880701,246336683,0,0,52929,14321907,486780060,288599194,130653412,748778899,953271190,644897553,0,0,517761,387406809,429534507,130653412,246336683,579440654,412233812,518446848,0,0,4767849,460338013,792294829,748778899,579440654,236701429,666021604,589237756,0,0,43046721,429534507,175880701,953271190,412233812,666021604,767713261,966670169,0,0,387420489,597431612,246336683,644897553,518446848,589237756,966670169,968803245};
int main()
{
	//freopen("date.txt","w",stdout);
	cin>>T;
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		if(n==1||m==1)
		    cout<<0<<endl;
		else if(n>9||m>9)
			cout<<1ll*qpow(3,m*n)<<endl;
		else
			cout<<yuanshen[n][m]<<endl;
	}
	return 0;
}
```


---

## 作者：zheng_zx (赞：0)

## P9629  Harmonious Rectangle 

[题目传送门](https://www.luogu.com.cn/problem/P9629)

### 分析

---

不妨假设 $n<m$。考虑一个只有 $2$ 行的矩阵。由于我们只有 $3$ 种颜色，只能产生 $9$ 种不同的列组合。如果我们的列数超过 $9$，那根据抽屉原理，我们必定能找到相同的两列。

也就是说，当 $\max(n,m)>9$ 的时候，所有的染色方案都可以产生满足条件的矩阵。

对于更小的情况，我们可以暴力搜索来算出那些不满足题设的方案数。如果担心实现的效率，也可以打表。

---

