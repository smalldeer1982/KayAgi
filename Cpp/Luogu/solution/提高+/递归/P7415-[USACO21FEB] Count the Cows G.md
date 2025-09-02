# [USACO21FEB] Count the Cows G

## 题目描述

如同平常一样，Farmer John 的奶牛们分散在他的最大的草地上。草地可以看作是一个由正方形方格组成的巨大的二维方阵（想象一个巨大的棋盘）。 

奶牛分布在草地上的方式相当迷人。对于每一个满足 $x\ge 0$ 以及 $y\ge 0$ 的方格 $(x,y)$，当对于所有整数 $k\ge 0$，$\left\lfloor \frac{x}{3^k}\right\rfloor$ 和 $\left\lfloor \frac{y}{3^k}\right\rfloor$ 除以三的余数的奇偶性均相同时，有一头奶牛位于 $(x,y)$。换言之，两个余数均为奇数（均等于 $1$），或均为偶数（均等于 $0$ 或 $2$）。例如，满足 $0\le x,y<9$ 的方格中，包含奶牛的方格在下图中用 1 表示。

```
        x
    012345678

  0 101000101
  1 010000010
  2 101000101
  3 000101000
y 4 000010000
  5 000101000
  6 101000101
  7 010000010
  8 101000101
```

FJ 对他的草地上的某个特定区域内的奶牛数量感兴趣。他进行了 $Q$ 个询问，每个询问由三个整数 $x_i,y_i,d_i$ 组成。对每个询问，FJ 想要知道有多少奶牛位于 $(x_i,y_i)$ 至 $(x_i+d_i,y_i+d_i)$ 的对角线上的方格内（包括两端）。


## 说明/提示

#### 测试点性质：

 - 对于另外 $8\%$ 的数据，满足对于每一个询问有 $d_i\le 100$。
 - 对于另外 $32\%$ 的数据，满足对于每一个询问有 $x+d=3^{30}-1$ 以及 $y=0$。
 - 对于另外 $52\%$ 的数据，没有额外限制。

供题：Benjamin Qi

## 样例 #1

### 输入

```
8
10 0 0
10 0 1
9 0 2
8 0 2
0 1 7
1 1 7
2 1 7
1000000000000000000 1000000000000000000 1000000000000000000```

### 输出

```
11
0
4
3
1
2
2
1000000000000000001```

# 题解

## 作者：green_orange (赞：18)

# USACO 2021 Feb T3 Count the Cows G

## 分析

首先转化题意，分析题中所给出的 $\lfloor\frac{x}{3^k}\rfloor$ 和 $\lfloor\frac{y}{3^k}\rfloor$：

对于向下取整，我们所拥有的技巧相对较少，我们不妨将其写成如下形式：
$$
x = 3^ka + r_0
$$
$$
y = 3^kb + r_1
$$
其中 $r_0, r_1 \le 3^k - 1$，那么我们所分析的条件可转化为 $a, b$ 之间的关系。

接下来分析 $a, b$ 的性质

我们观察到对于不同的 $k$ 值, $a, b$ 的系数始终是 $3$ 的次幂，而题目中所给的关系中出现了对于 $3$ 的余数，这启发我们将 $a,b$ 中再提出一个 $3$ 来。那么有
$$
x = 3^k(3p_x + q_x) + r_0
$$
$$
y = 3^k(3p_y + q_y) + r_1
$$
题目中的关系可转化为 $q_x \equiv q_y \pmod{2}$。

我们发掘出了对于单一的 $k$ 其具有的性质，考虑对于所有的 $k$

展开上式
$$
x = 3^{k + 1}p_x + 3_{k}q_x + r_0
$$
$$
y = 3^{k + 1}p_y + 3_{k}q_y + r_1
$$
我们发现有大量 $3$ 的次幂，这启发我们尝试将 $r$ 也写成 $3$ 的次幂相加的形式

$$
x = \sum_{k = 0} 3^k a_{k}
$$
$$
y = \sum_{k = 0} 3^k b_{k}
$$

题目所给关系转化为 $\forall k, a_k \equiv b_k \pmod{2}$。

根据我们的经验，我们发现上式中的形式就是 $x, y$ 的三进制，要求转化为 $x, y$ 三进制下每一位关于 $2$ 同余。

这个结论对我们来说大有脾益，那么，我们就是求有多少的 $d \in [d, d_0]$ 满足 $x_0 + d$ 与 $y_0 + d$ 三进制每一位下关于 $2$ 同余。我们可以很容易联想到数位DP, 设状态为当前DP到多少位，$x_0 + d$，$y_0 + d$ 的更低位在做加法时有没有进位 ，由高位向低位DP即可，时间复杂度 $O(q\log x)$。

## 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const static int mlg = 40;
#define int long long
int f[mlg][2][2][2];
bool vis[mlg][2][2][2];
int Ab[mlg], Bb[mlg], lb[mlg];
bool check(int a, int b) {
	if (a < 0 || b < 0 || a > 2 || b > 2)
	  return false;
  else if ((a & 1) == (b & 1))
    return true;
  else
    return false;
}
typedef long long inte;
inline int dfs(int p/*第几位*/, bool a/*x 是否进位*/, bool b/*y 是否进位*/, bool lim/*d 是否被顶满*/) {
	if (p < 0)
	  return (a == 0) && (b == 0);
	if (vis[p][a][b][lim])
	  return f[p][a][b][lim];
  vis[p][a][b][lim] = true;
	inte ans = 0;
	for (int v = 0; v <= (lim ? lb[p] : 2); ++v) {
		for (int ak = 0; ak <= 1; ++ak) {
			for (int bk = 0; bk <= 1; ++bk) {
				if (check(Ab[p] - 3 * a + v + ak, Bb[p] - 3 * b + v + bk)) {
					ans += dfs(p - 1, ak, bk, lim & (v == lb[p]));
				}
			}
		}
	}
	return f[p][a][b][lim] = ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
	int Q;
	cin >> Q;
	while (Q--) {
		inte x, y, d;
		cin >> d >> x >> y;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < mlg; ++i) {
			Ab[i] = x % 3;
			x /= 3;
			Bb[i] = y % 3;
			y /= 3;
			lb[i] = d % 3;
			d /= 3;
		}
		cout << dfs(mlg - 1, 0, 0, true) << endl;
	}
  return 0;
}
```





---

## 作者：henryhu2006 (赞：8)

## USACO 21 Feb G T3 题解

## 题意
$$\colorbox{BLUE}{\color{BLUE}x}\colorbox{red}{\color{red}x}\colorbox{BLUE}{\color{BLUE}x}
\\
\colorbox{red}{\color{red}x}\colorbox{blue}{\color{blue}x}\colorbox{red}{\color{red}x}
\\
\colorbox{BLUE}{\color{BLUE}x}\colorbox{red}{\color{red}x}\colorbox{BLUE}{\color{BLUE}x}
$$
定义以上 $3\times3$ 矩阵为一阶标准矩阵。

对于 $i$ 阶标准矩阵，$i\ge2$，是一个 $3^i\times3^i$ 的矩阵，将其横纵坐标分别三等分，并在对角线和反对角线上的 $5$ 个矩形区域填上一个 $i-1$ 阶矩阵。

题目给定 $Q$ 个询问，每个询问查询，在无限阶的标准矩阵中，以 $(x,y)$ 和 $(x+d,y+d)$ 为端点的对角线上有几个蓝色方块。 

$Q \le 10^4,x,y,d\le10^{18}$。

## 分析
1. 首先整个无限大的矩阵关于 $y=x$ 对称，所以不妨令 $x \le y$，把所有 $x,y$ 都搬到右上角。

2. 将对角线变成“前缀减前缀”的形式，每次只要查询“前缀”，比如 $(x,y)$ 前缀为 $(0,y-x)$ 到 $(x,y)$，其中 $x \le y$。

3. 将 $(x,y)$ 套入一个 $i$ 阶矩阵，使得 $\max(x,y)\le3^i$。

## 分治
$calc_{v,n}$  函数意义：直线 $y=x+v$ 函数所经过的蓝色格子在一个 $i$ 阶标准矩阵有几个，其中 $n=3^i$，$v<n$。（$x$ 横 $y$ 纵）

$query_{x,y,n}$ 函数意义：求 $(x,y)$ “前缀”有几个蓝色。

### $query$ 步骤

- 若 $n=3$，访问数组返回答案。

- 若 $x>y$，交换 $x,y$。

- 令 $v=y-x$，$m=\dfrac{n}{3}$。

- 若 $v<m$（穿过了正对角的三个区域）

	1. $y<m$（完全在最左上角的区域内），返回 $query_{x,y,m}$
   2. $x<m$ ( 穿过最左上角的区域，没有经过第二个 )，返回 $calc_{v,m}$（其他地方都是空的）。
   3. $y<2m$ ( 穿过第一个，经过第二个，没有穿），返回 $calc_{v,m}+query_{x-m,y-m,m}$。
   4. $x<2m$（穿过前两个，没有经过第三个），返回 $2\times calc_{v,m}$。
   5. $else$（穿过前两个，经过第三个），返回 $2\times calc_{v,m}+query_{x-2m,y-2m,m}$。
   
| 0 | 1 | 2| 3 |4  | 5 | 6 | 7 | 8 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | **0** | 1 | 0 | 0 |  0|1  | 0 |1  |
| 0 | 1 | **0** | 0 | 0 | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | **0** | 0 | 0 | 1 |0  | 1|
| 0|  0|0 | 1 |  **0**| 1| 0|0 | 0|
| 0|0 |  0 |  0| 1 | **0** | 0|0 | 0|
| 0| 0|  0 | 1 | 0 | 1 | **0**| 0| 0 |
|1| 0|1| 0| 0|  0|1| **0**| 1|
| 0|  1|0| 0|0 | 0| 0|1 |**0** |
|1|0|1|0|0|0|1|0|1|

   
- 若 $v=m$（刚好没碰到），返回 $0$。

| 0 | 1 | 2| 3 |4  | 5 | 6 | 7 | 8 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 0 | 1 | **0** | 0 | 0 | 1 | 0 | 1 |
| 0 | 1 | 0 | 0 | **0** | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | 0 | 0 | **0** | 1 | 0 | 1 |
| 0 | 0 | 0 | 1 | 0 | 1 | **0** | 0 | 0 |
| 0 | 0 | 0 | 0 | 1 | 0 | 0 | **0** | 0 |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | **0** |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |

- 若 $v<2m$（碰到右上角区域，没有过对角线）
	1. $y<2m$ （没有碰到右上角区域），返回 $0$。
   2. $x\ge m$ （穿过），返回 $calc_{2m-v,m}。（看图推导一下）$
   3. $else$，（经过没穿），返回 $query_{x,y-2m,m}$。


| 0 | 1 | 2| 3 |4  | 5 | 6 | 7 | 8 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 0 | 1 | 0 | 0 | **0** | 1 | 0 | 1 |
| 0 | 1 | 0 | 0 | 0 | 0 | **0** | 1 | 0 |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | **0** | 1 |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | **0** |
| 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
   

   

   
- 若 $v \ge 2m$（过了对角线），返回 $query_{x,y-2m,m}$。

| 0 | 1 | 2| 3 |4  | 5 | 6 | 7 | 8 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | **0** | 1 |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | **0** |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
   

### $calc$ 步骤
和前者步骤相似，但是比前者简单。

- 若 $n=1$ 或 $n=3$，特判。
- 令 $m=\dfrac{n}{3}$。
- 若 $v< m$，返回 $3\times calc_{v,m}$。（因为三个方块中的情况一样）
- 若 $v=m$，返回 $0$。
- 若 $v<2m$，返回 $calc_{2m-v,m}$。（和上面一样，其实就是平移 + 翻转）
- 若 $v\ge 2m$，返回 $calc_{v-2m,m}$。

### 复杂度分析
$calc$ 复杂度很明显为 $\log_3\operatorname{V}$，（$\operatorname{V}$ 就是最大值域）。
 
$query$ 会递归 $\log_3\operatorname{V}$ 层，每层最多调用一次 $calc$ 函数，所以单次复杂度为 $O(\log_3^2\operatorname{V})$。

总复杂度为 $O(Q\times\log_3^2\operatorname{V})$，可以通过。

## 代码
```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
typedef long long ll;
const int a[3][3]={{1,0,1},{0,2,0},{1,0,3}};
int q; ll d,x,y,ans;
ll calc(ll x,ll n){
	if(n==1) return 1;
	if(n==3){
		if(x==0) return 3;
		else if(x==1) return 0;
		else return 1;
	}
	n/=3;
	if(x<n) return 3ll*calc(x,n);
	else if(x==n) return 0;
	else if(x<2ll*n) return calc(2ll*n-x,n);
	else return calc(x-2ll*n,n);
}
ll query(ll x,ll y,ll n){
	if(n==3) return a[x][y];
	if(x>y) swap(x,y);
	ll val=y-x; n/=3ll;
	if(val<n){
		ll tmp=calc(val,n);
		if(y<n) return query(x,y,n);
		if(x<n) return tmp;
		if(y<2ll*n) return tmp+query(x-n,y-n,n);
		if(x<2ll*n) return tmp*2ll;
		else return tmp*2ll+query(x-2ll*n,y-2ll*n,n);
	}
	else if(val==n) return 0;
	else if(val<2ll*n){
		if(y<2ll*n) return 0;
		if(x>=n) return calc(2ll*n-val,n);
		return query(x,y-2ll*n,n);
	}
	else return query(x,y-2ll*n,n);
}
ll Query(ll x,ll y){
	if(x<0||y<0) return 0;
	if(x>y) swap(x,y);
	ll dif=y-x,val=3ll;
	while(val<=y) val*=3ll;
	return query(x,y,val);
}
int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%lld%lld%lld",&d,&x,&y);
		cout<<Query(x+d,y+d)-Query(x-1,y-1)<<endl;
	}
	return 0;
}
```

## 题外话
如果要求矩形内的蓝格子数量怎么办？（假设取模不会爆 `long long`）

1. 变成二维前缀。
2. 设计 $calc$ 函数：一个标准矩阵在 $v$ 处横切 / 纵切后上一半 / 左一半的蓝格子数量。（很明显，横向和纵向是一样的）。
3. 如何计算 $calc$：将 $v$ 按 $v<m,m\le v<2m,v\ge2m$ 分类，最后递归加上下面的零头（$3\times calc_{v/v-m/v-2m,m}$）。
4. 设计 $query$ 函数：一个标准矩阵在 $x$ 处横切， $y$ 处纵切，左上角的蓝格子数量。
5. 发现 $i$ 阶矩阵的蓝格子数量为 $5^i$ 个。
6. 如何实现 $query$ 函数：
```cpp
ll ret=0;
int xnum=x/m,ynum=y/m;
ret+=1ll*xnum*ynum*pw[m]%mod; // pw[m]=5^m%mod
ret+=1ll*ynum*calc(x%m,m),ret+=xnum*calc(y%m,m),ret%=mod;
return (ret+calc(x%m,y%m,m))%mod;
```
7. 写好套路的主程序和简单的特判。

同理，其实递归型的图形都可以这么做。

---

## 作者：OptimisticForever (赞：5)

# 	[USACO21FEB] Count the Cows G 题解

考虑 $x,y$ 满足情况，当且仅当 $x$ 和 $y$ 的三进制表示位下每一位奇偶性相同。

所以题目转化为有多少个 $z$ 满足 $(x+z,y+z)$ 满足条件，注意 $0\leq z\leq d$。

考虑数位 dp，设 $f_{i,0/1,0/1,0/1}$ 分别表示构造到第 $i$ 位的 $z$， 当前 $x+z,y+z$ 分别是否进位，当前是否确定 $z<d$ 的方案数。

考虑转移，在 dfs 上枚举当前位选择的数转移。设上一次存的进位分别为 $ck1,ck2$，当前枚举进位 $j,k$，那么我们要判断 $x+z-3ck1+j$ 和 $y+z-3ck2+k$ 是否合法。

 ```cpp
#include<bits/stdc++.h>
using namespace std;
int q;
typedef long long ll;
ll a[50],b[50],c[50],f[50][2][2][2],g[50][2][2][2];
ll dfs(ll len,ll ck1,ll ck2,ll ck3){
	if (len==0){
		if (ck1==0&&ck2==0)return 1;
		else return 0;
	}
	if (f[len][ck1][ck2][ck3]!=-1)return f[len][ck1][ck2][ck3];
	ll lim=2,ans=0;
	if (ck3==1){
		lim=c[len];
	}
	for (ll i=0;i<=lim;i++){
		for (ll j=0;j<=1;j++){
			for (ll k=0;k<=1;k++){
				ll x=a[len]+i-ck1*3+j;
				ll y=b[len]+i-ck2*3+k;
				if (x>=0&&y>=0&&x<=2&&y<=2&&x%2==y%2){
					if (ck3==1&&i==c[len])ans+=dfs(len-1,j,k,1);
					else ans+=dfs(len-1,j,k,0);
				}
			}
		}
	}
	f[len][ck1][ck2][ck3]=ans;
	return ans;
}
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d",&q);
	while (q--){
		memset(f,-1,sizeof(f));
		memset(g,0,sizeof(g));
		ll x,y,d;
		scanf("%lld%lld%lld",&d,&x,&y);
		ll len1=0,len2=0,len3=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		while (d){
			c[++len3]=d%3;
			d/=3;
		}
		while (x){
			a[++len1]=x%3;
			x/=3;
		}
		while (y){
			b[++len2]=y%3;
			y/=3;
		}
		len1=40;
		len2=40;
		len3=40;
		printf("%lld\n",dfs(len3,0,0,1));
	}
}
 ```



---

## 作者：lzqy_ (赞：4)

## 题意转化

题目的要求看起来很复杂，但是，如果我们尝试打一个表，输出前面矩阵放置奶牛的情况，我们不难发现，题目的矩阵就是如下矩阵：

1 0 1

0 1 0

1 0 1

对于这个基本矩阵，按照如上的摆放方式生成更大的矩阵，依次类推。

于是题目就转化为，对于这个递归式的矩阵，求出 $(x,y)$ 到 $(x+d,y+d)$ 对角线上 $1$ 的个数。

注：容易发现，上方图形沿对角线对称，所以我们假设 $x\leq y$。

## 问题转化

看到有 $y=0$ 的部分分，于是考虑将所有数据转化成 $y=0$ 的情况。

设 $f_{i,j,n}$ 表示从 $(0,0)$ 到 $(i,j)$ 对角线上 $1$ 的个数，其中， $n$ 是左上角为原点、包含整条对角线的正方形的边长。

那么，$(x,y)$ 到 $(x+d,y+d)$ 对角线上 $1$ 的个数就可以转化为 $f_{x+d,y+d,n}-f_{x-1,y-1,n'}$（前缀和思想）。

于是，现在问题就转化为求 $f_{i,j,n}$ 的值了。

## 问题求解

以下图为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/4t887qt1.png)


设现在要求的是 $f_{x,y,n}$，如图是边长为 $n$、左上角为 $(0,0)$ 的正方形，编号为子矩阵编号。

另外地，为了表示简便，再设 $g_{i,n}$ 表示从 $(0,i)$ 出发的对角线在左上角为 $(0,0)$、边长为 $n$ 的正方形中 $1$ 的个数。

设 $z=x-y$（即线段延长至 $y=0$ 时的 $x$ 坐标），$m=n/3$（即子矩阵边长）。

**在以下情况下，$f_{x,y,n}$ 分别等于：**


- 线段从矩阵 $1$ 出发（$z<m$）
	
    - 到矩阵 $1$ 结束（$x<m,y<m$）：$f_{x,y,m}$
    
    - 到矩阵 $4$ 结束（$m\leq x<2m,y<m$）：$g_{z,m}$
   
    - 到矩阵 $5$ 结束（$m\leq x< 2m,m\leq y<2m$）：$f_{x-m,y-m,m}+g_{z,m}$
    
    - 到矩阵 $8$ 结束（$x≥2m,m\leq y< 2m$）：$2\times g_{z,m}$
    
    - 到矩阵 $9$ 结束（$x≥2m,y≥2m$）：$2\times g_{z,m}+f_{x-2m,y-2m,m}$
    
- 线段从矩阵 $4$ 出发 （$m\leq z<2m$）
	
    - 到矩阵 $4$ 结束（$m\leq x<2m,y<m$）：$0$
    
    - 到矩阵 $8$ 结束（$x≥2m,m\leq y<2m$）
    	- 未经过矩阵 $7$（$z=m$）：$0$
        - 经过矩阵 $7$（$m<z<2m$）：$g_{2m-z,m}$
    
    - 到矩阵 $7$ 结束 （$x≥2m,y<m$）：$f_{x-2m,y,m}$
		

- 线段从矩阵 $7$ 出发（$z≥2m$）

	- 所有情况都与从矩阵 $1$ 出发对称，返回 $f_{x-2m,y,m}$
    
(由于 $y\leq x$，所以 $2,3,6$ 号矩阵不可能经过)

**边界条件**：当 $n=3$ 时特判答案。

-----

到这里，这道题基本就做完了，唯一的问题就是 $g$ 的转移。其实，由于对角线一定穿过对应正方形，所以，分别从 $1,4,7$ 号矩阵出发的对角线，一定会分别在 $9,8,7$ 号矩阵结束。于是就可以按照 $f$ 数组转移中的三种情况来转移 $g$ 数组了。

## 代码

具体看注释趴

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=41;
inline ll read()
{
    register ll x=0;
    register char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;
}
const int biao[3][3]={{1,0,1},
					  {0,2,0},
					  {1,0,3}};
//n=3 时的特判
int q;
ll G(ll z,ll n)//g 的转移
{
	register ll m=n/3;
	if(n==3) 
		return biao[2][2-z];
  //边界条件（注意，本题都是从 0 计数）
	if(z<m)
		return 3*G(z,m);
	else if(z==m)
		return 0;
	else if(z<(m<<1))
		return G(m*2-z,m);
	else
		return G(z-m*2,m);
  //按照方程分情况转移
}
ll F(ll x,ll y,ll n)
{
	if(n==3)
		return biao[x][y];
	if(y>x) 
		swap(x,y);
	register ll m=n/3,z=x-y;
	if(z<m)
	{
		if(x<m&&y<m)
			return F(x,y,m);
		if(y<m&&x>=m&&x<2*m)
			return G(z,m);
		if(x>=m&&x<2*m&&y>=m&&y<2*m)
			return G(z,m)+F(x-m,y-m,m);
		if(x>=2*m&&y>=m&&y<2*m)
			return G(z,m)*2;
		if(x>=2*m&&y>=2*m)
			return G(z,m)*2+F(x-m*2,y-m*2,m);
	}
	if(z>=m&&z<2*m)
	{
		if(x<2*m&&x>=m&&y<m)
			return 0;
		if(y>=m&&y<2*m&&x>=2*m)
		{
			if(z==m)
				return 0;
			if(z>m&&z<2*m)
			    return G(2*m-z,m);
		}
		if(x>=2*m&&y<m)
			return F(x-2*m,y,m);
	}
	if(z>=2*m)
		return F(x-2*m,y,m);
 	//按照方程分情况转移
}
ll Work(ll x,ll y)
{
	if(x<0||y<0) return 0;
	if(y>x) swap(x,y);
	register ll sum=1;
	while(sum<=x)
		sum*=3;//取 n 的值(第一个大于 max{x,y} 的3的整数次幂)
	return F(x,y,sum); 
}
int main()
{
	register ll d,x,y;
	q=read();
	while(q--)
	{
		d=read(),x=read(),y=read();
		printf("%lld\n",Work(x+d,y+d)-Work(x-1,y-1));
	}
    return 0;
}
```
Tipes：为了易懂，本代码会稍有些冗长。大家可以自行优化~

---

## 作者：Eibon (赞：3)

### 方法一

通过观察不难发现该图形类似于 X 的分形。于是进行模拟即可。没有写，所以没代码。

### 方法二

通过转化题意，我们不难发现，满足题意的数在三进制拆解下每一位都奇偶性相同。

因为 $x$，$y$ 和 $d$ 都很大，考虑数位 dp。

设 $dp_{len,i,j,lim}$ 表示当前构造到 $len$ 位，$x+i$ 与 $y+j$ 是否进位，是否顶到上界的方案数。

设上一次的 $i$ 为 $p$,枚举到 $c$。

那我们需要判断 $x-3\times p+c+i$ 是否合法，保证其为三进制。

另一个数同理。

同时还要判断两个数的奇偶性。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T=1;
int dp[45][2][2][2],a[45][4];
bool check(int x,int y)
{
	if(x<0||y<0||x>2||y>2){
		return 0;
	}
	return (x&1)==(y&1);
}
int VIP(int len,bool x,bool y,bool lim)
{
	if(!len){
		return !x&&!y;
	}
	int &ans=dp[len][x][y][lim];
	if(~ans){
		return ans;
	}
	ans=0;
	int mx=2;
	if(lim){
		mx=a[len][3];
	}
	for(int i=0;i<=mx;i++){
		for(int j=0;j<=1;j++){
			for(int k=0;k<=1;k++){
				if(check(a[len][1]-3*x+i+j,a[len][2]-3*y+i+k)){
					ans+=VIP(len-1,j,k,lim&&(i==mx));
				}
			}
		}
	}
	return ans;
}
void solve()
{
	int d,l,r;
	scanf("%lld%lld%lld",&d,&l,&r);
	memset(dp,-1,sizeof dp);
	for(int i=1;i<=40;i++){
		a[i][1]=l%3;l/=3;
		a[i][2]=r%3;r/=3;
		a[i][3]=d%3;d/=3;
	}
	printf("%lld\n",VIP(40,0,0,1));
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：lcyxds (赞：2)

这次终于 AK 了金组，水篇题解纪念一下

设 $f(x,y)=[\text{有一头奶牛位于} (x,y)]$，则此值可以通过不断比较模 $3$ 的余数并不断同除 $3$ 来判断。

此时得到了一个 $\Theta(d)$ 的做法，但是只能拿到 2 个点。

~~战术嘲讽~~

根据定义可得 $f(x,y)=f(y,x)$。

不妨设每次询问 $x\leq y$，设最终所求为 $g(d, x, y)$，经过观察可得所求序列的规律与 $y-x$ 有很大关系。于是设 $g(d, x, y)=h(x, x+d, y-x)$。

考虑求 $h(l, r, d)$：

先摆出一些 $f(x, y)$ 的性质：

定义$count(x)$ 为 $x$ 三进制的 $1$ 的个数。

1. $f(x, x)=1$，证明略。
2. $f(x, y)=1$，当且仅当两个数的三进制拆分的 $1$ 的位置完全相同。求 $f(x, y)$ 本质就是对两数进行三进制拆分。
3. $f(x, x+d)=1$，当且仅当 $x+d$ 不改变 $x$ 三进制的 $1$ 的位置。同 2。
3. $count(x+y)\equiv count(x)+count(y)(\mod 2)$。直观理解如果某位加一，有三种情况：原位为 $0$，原位为 $1$，原位为 $2$。前两种情况都会改变 $1$ 的奇偶性，而第三种情况等价于在下一位加一。加 $y$ 可以理解为在 $x$ 的各位不断加一，而加的次数奇偶性与 $count(y)$ 一致。
5. $f(x,x+3d)=f(\lfloor x/3\rfloor,\lfloor x/3\rfloor+d)$，可以忽略 $d$ 的最低位对答案的影响

6. 当$x\equiv2(\mod3)$ 时 $f(x,x+3d+1)=f(\lfloor x/3\rfloor,\lfloor x/3\rfloor+d+1)$，否则为 $0$。

6. 当$x\equiv0(\mod3) $ 时 $f(x,x+3d+2)=f(\lfloor x/3\rfloor,\lfloor x/3\rfloor+d)$，否则为 $0$。这两条可以通过找规律得出，不符合先决条件时值为 $0$ 看个位显然，符合时可以类似第五条进行递归求解

~~我自己都有亿点懵~~

而 $h(l,r,d) = \sum\limits_{i=l}^r{f(i,i+d)}$

于是可以递归求解

具体的，不妨设 $l\equiv0,r\equiv2(\mod3)$

则
$h(l,r,d) = \left\{\begin{matrix}3h(l/3,(r-2)/3,d/3)(d\equiv 0(\mod 3))
\\ h(l/3,(r-2)/3,(d+2)/3)(d\equiv 1(\mod 3))
\\ h(l/3,(r-2)/3,(d-2)/3)(d\equiv 2(\mod 3))

\end{matrix}\right.$（根据 5, 6, 
7 性质推出，对每一个除个位外相同的三个数进行讨论，然后递归求解）

最终代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define ull unsigned long long

using namespace std;

int Q;

bool In(ull x, ull y) {
	while (x || y) {
		if ((x%3==1)^(y%3==1)) {
			return false;
		}
		x/=3;
		y/=3;
	}
	return true;
}

int Count1(ull a) {
	int res = 0;
	while (a) {
		if (a%3==1) res++;
		a/=3;
	}
	return res;
}

ull Res(ull l, ull r, ull diff) {
	if (diff==0) {
		return r-l+1;
	}
	if (l>r) return 0;
	if (l==r) return In(l, l+diff);
	if (r==l+1) return In(l, l+diff)+In(r, r+diff);
	ull res = 0;
		while (l%3) {
			res+=In(l, l+diff);
			l++;
		}
		while (r%3!=2) {
			res+=In(r, r+diff);
			r--;
		}
	switch(diff%3) {
		case 0:
			
		return res+Res(l/3, r/3, diff/3)*3;
		case 1:
			return res+Res(l/3, r/3, (diff+2)/3);
		case 2:
			return res+Res(l/3, r/3, (diff-2)/3);
	}
}

void Solve(ull d, ull x, ull y) {
	if (x==y) {
		printf("%llu\n", d+1);
		return;
	}
	if (Count1(x-y)&1) {
		printf("0\n");
		return;
	}
	printf("%llu\n", Res(y, y+d, x-y));
}

int main() {
	scanf("%d", &Q);
	while (Q--) {
		ull d, x, y;
		scanf("%llu%llu%llu", &d, &x, &y);
		if (x < y) swap(x, y);
		Solve(d, x, y);
	}
	return 0;
}

```

考场代码：（挂了很多次）
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define ull unsigned long long

using namespace std;

int Q;

bool In(ull x, ull y) {
	while (x || y) {
		if ((x%3==1)^(y%3==1)) {
			return false;
		}
		x/=3;
		y/=3;
	}
	return true;
}

int Count1(ull a) {
	int res = 0;
	while (a) {
		if (a%3==1) res++;
		a/=3;
	}
	return res;
}

ull Hubu(ull x) {
	ull base = 1;
	ull res = 0;
	vector<int> list;
	while (x) {
		list.push_back(x%3);
		x/=3;
	}
	for (int i = 0; i < list.size(); i++) {
		if (list[i] > 2) {
			list[i+1]+=list[i]/3;
			list[i]%=3;
		}
		if (list[i]==1) {
			res+=base<<1;
			list[i] = 0;
			list[i+1]++;
		}
		base*=3ull;
	}
	return res;
}

ull Da(ull a) {
	ull res = 1ull;
	while (res <= a) res*=3ull;
	return res;
}

ull Count(ull l, ull r, ull dn, ull mod) {
//	cout << "Count " << l << ',' << r << ',' << dn << ',' << mod << endl;
	l-=dn;
	r-=dn;
	return (r+mod)/mod-(l-1+mod)/mod;
}

ull Res(ull l, ull r, ull diff) {
//	cout << "Res(" << l << ',' << r << ',' << diff << endl;
	if (diff==0) {
		return r-l+1;
	}
	if (l>r) return 0;
	if (l==r) return In(l, l+diff);
	if (r==l+1) return In(l, l+diff)+In(r, r+diff);
	ull res = 0;
		while (l%3) {
			res+=In(l, l+diff);
			l++;
		}
		while (r%3!=2) {
			res+=In(r, r+diff);
			r--;
		}
	switch(diff%3) {
		case 0:
			
		return res+Res(l/3, r/3, diff/3)*3;
		case 1:
			return res+Res(l/3, r/3, (diff+2)/3);
		case 2:
			return res+Res(l/3, r/3, (diff-2)/3);
	}
}

//ull Res(ull d, ull x, ull y) {
//	if (d==-1) return 0;
//	if (d<2) {
//	ull res = 0;
//	for (ull i = 0; i <= d; i++) {
//		res+=In(x+i, y+i);
//	}
//	return res;
//	}
//	ull res = 0;
//	ull diff = x-y;
//	if (diff%3==0) {
//		while (x%3) {
//			res+=In(x, y);
//			x++;
//			y++;
//			d--;
//		}
//		while ((d+1)%3) {
//			res+=In(x+d, y+d);
//			d--;
//		}
//		return res+Res((d+1)/3-1, x/3, y/3)*3;
//	}
//	if (diff%3==2) {
//		int newdiff = diff/3;
//		int l = (y/3+diff)
//		return res+Res(, y/3+diff, y/3);
//	}
////	return Count(y, y+d, Hubu(diff), Da(diff));
//}

void SolveOld(ull d, ull x, ull y) {
	ull res = 0;
	for (ull i = 0; i <= d; i++) {
		res+=In(x+i, y+i);
	}
	printf("%llu\n", res);
	return;
}

void Solve(ull d, ull x, ull y) {
//	if (d == 1000000000000000000ull && x == 1000000000000000000ull && y == 1000000000000000000ull) {
//		printf("1000000000000000001\n");
//		return;
//	}
//	if (d <= 100) {
//	ull res = 0;
//	for (ull i = 0; i <= d; i++) {
//		res+=In(x+i, y+i);
//	}
//	printf("%llu\n", res);
//	return;
//	}
	if (x==y) {
		printf("%llu\n", d+1);
		return;
	}
	if (Count1(x-y)&1) {
		printf("0\n");
		return;
	}
	printf("%llu\n", Res(y, y+d, x-y));
}

void DisplayThree(ull a) {
	if (a) {
		DisplayThree(a/3);
		cout << a%3;
	}
}

int main() {
	scanf("%d", &Q);
//	for (int i = 0; i < 1000; i++) {
//		int d = 1000;
//		int x = i;
//		int y = 0;
//		Solve(d, x, y);
//		SolveOld(d, x, y);
//	}
//	printf("%llu\n", res);
////	return;
////	}
//		DisplayThree(x);
//		cout << ',' << x << ',';
//		Solve(d, x, y);
//	}
	while (Q--) {
		ull d, x, y;
		scanf("%llu%llu%llu", &d, &x, &y);
		if (x < y) swap(x, y);
		Solve(d, x, y);
	}
	return 0;
}

```


---

