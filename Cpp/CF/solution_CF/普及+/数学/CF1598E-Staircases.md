# Staircases

## 题目描述

You are given a matrix, consisting of $ n $ rows and $ m $ columns. The rows are numbered top to bottom, the columns are numbered left to right.

Each cell of the matrix can be either free or locked.

Let's call a path in the matrix a staircase if it:

- starts and ends in the free cell;
- visits only free cells;
- has one of the two following structures: 
  1. the second cell is $ 1 $ to the right from the first one, the third cell is $ 1 $ to the bottom from the second one, the fourth cell is $ 1 $ to the right from the third one, and so on;
  2. the second cell is $ 1 $ to the bottom from the first one, the third cell is $ 1 $ to the right from the second one, the fourth cell is $ 1 $ to the bottom from the third one, and so on.

In particular, a path, consisting of a single cell, is considered to be a staircase.

Here are some examples of staircases:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1598E/30e6b70a090f9657a06b957e8113944b3c2b16f3.png)Initially all the cells of the matrix are free.

You have to process $ q $ queries, each of them flips the state of a single cell. So, if a cell is currently free, it makes it locked, and if a cell is currently locked, it makes it free.

Print the number of different staircases after each query. Two staircases are considered different if there exists such a cell that appears in one path and doesn't appear in the other path.

## 样例 #1

### 输入

```
2 2 8
1 1
1 1
1 1
2 2
1 1
1 2
2 1
1 1```

### 输出

```
5
10
5
2
5
3
1
0```

## 样例 #2

### 输入

```
3 4 10
1 4
1 2
2 3
1 2
2 3
3 2
1 3
3 4
1 3
3 1```

### 输出

```
49
35
24
29
49
39
31
23
29
27```

## 样例 #3

### 输入

```
1000 1000 2
239 634
239 634```

### 输出

```
1332632508
1333333000```

# 题解

## 作者：pythoner713 (赞：9)

令 $f(i,j)$ 表示以 $(i,j)$ 为左上角，第一步向**右**的台阶数量；$g(i,j)$ 表示以 $(i,j)$ 为左上角，第一步**下**的台阶数量。

例如（灰格为 free cells）：

![](https://cdn.luogu.com.cn/upload/image_hosting/w3l3a1om.png)

对于 free cells 有转移：

$$f(i,j)=g(i,j+1)+1$$
$$g(i,j)=f(i+1,j)+1$$

对于 locked cells 则 $f(i,j)=g(i,j)=0$。

然而对于大小为 $1$ 的台阶，会同时被 $f,g$ 统计，因此我们维护 $\rm cnt$ 为当前 free cells 的个数，则答案就是：

$$\sum_{i=1}^n\sum_{j=1}^m(f(i,j)+g(i,j))-\rm cnt$$

现在考虑一次修改，它只能影响到左上方 $\mathcal O(n)$ 级别个格子的 $f,g$ 值，因此可以暴力修改，时间复杂度 $\mathcal O(qn)$。记得更新答案和 $\rm cnt$。

赛时代码，比较乱：[Staircases.cpp](https://www.luogu.com.cn/paste/ms3uwrdc)

---

## 作者：Echo_Long (赞：2)

### [Staircases](https://www.luogu.com.cn/problem/CF1598E)

我们设 $f_{i,j,0/1}$ 表示到 $(i,j)$ 点，当前格子作为右上/左下拐点的方案数。

初始化 $f_{i,j,0}=f_{i,j,1}=1$。

那么我们首先将全部为 $0$ 的情况的答案先算出来，即：$f_{i,j,0}\leftarrow f_{i-1,j,1},f_{i,j,1}\leftarrow f_{i,j-1,0}$。

$ans=\sum_{i=1}^n\sum_{j=1}^m f_{i,j,0}+f_{i,j,1}-1$。

考虑一个修改 $(x,y)$ 的贡献，即为经过这个点的所有合法楼梯，那么我们向四个方向搜索并组合，累计修改即可。

注意当 $(x,y)$ 点本身不合法的时候，我们是不能直接跳出循环的，而应该继续向外搜索。

参考了[这篇代码](https://blog.csdn.net/weixin_44178736/article/details/120752978)的书写方式，使修改操作更加简洁。



```c++

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define getchar() cin.get()
#define pii pair<int,int>
#define fi first
#define se second
#define int long long
const int N = 1000 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , m , q , ans , f[N][N][2] , a[N][N] , cnt[4];//(i,j)，作为右上或左下拐点。

vector<pii> d[4] = { vector<pii> { {0,1},{1,0} } , vector<pii> { {1,0},{0,1} } , vector<pii> { {0,-1},{-1,0} } , vector<pii> { {-1,0},{0,-1} } };

int check ( int x , int y ) { return 1 <= x && x <= n && 1 <= y && y <= m ; }

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
    n = read() , m = read() , q = read();
    for ( int i = 1 ; i <= n ; i ++ )
        for ( int j = 1 ; j <= m ; j ++ )
            f[i][j][0] = f[i][j][1] = 1 , f[i][j][0] += f[i-1][j][1] , f[i][j][1] += f[i][j-1][0] , ans += f[i][j][0] + f[i][j][1] - 1;
    for ( int i = 1 ; i <= q ; i ++ )
    {
        int x = read() , y = read();
        fill ( cnt , cnt + 4 , 0 );
        for ( int i = 0 ; i < 4 ; i ++ )
        {
        	int op = 0 , tx = x , ty = y;
        	while ( check(tx,ty) && ( !a[tx][ty] || tx == x && ty == y ) ) ++ cnt[i] , tx += d[i][op].fi , ty += d[i][op].se , op ^= 1;
        }
        ans += ( a[x][y] == 1 ? 1 : -1 ) * ( cnt[0] * cnt[3] + cnt[1] * cnt[2] - 1 );
        a[x][y] ^= 1;
        cout << ans << endl;
    }
    return 0;
}   

```

---

## 作者：KSToki (赞：2)

# 题目大意
定义阶梯状为一个由初始格子不断交替向下向右形成的图形（一个格子也是阶梯），给定 $n\times m$ 的矩阵，初始都未锁定，$q$ 次询问每次将一个格子的锁定状态改变，求不含锁定格子的阶梯数。
# 题目分析
貌似有人用纯推式子的方法过了，但是比较麻烦，这里是 dp 的方法。

假如没有询问，即所有格子都没锁定，很容易想到一个暴力的 dp，用 $f[i][j][0/1]$ 表示以 $(i,j)$ 位置向下或右结束的阶梯数量，转移为 $f[i][j][0]=f[i-1][j][1]+1$ 和 $f[i][j][1]=f[i][j-1][0]+1$，最终答案需要减去未被锁定格子的数量，因为单个格子没有朝向要求，所以应特殊处理单个格子的情况。

现在考虑修改，注意到 $q$ 只有 $10^4$，阶梯修改只会影响到当前格斜向下、右边斜向下、下面斜向下总共 $O(n)$ 个，暴力修改即可做到 $O(qn)$。

通过观察最后一个样例可以发现爆不了 `long long`，~~但我没看到所以开了~~，注意边界就行了。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,m,q,x,y;
ll f[1005][1005][2],ans,cnt;
bool v[1005][1005];
int main()
{
	n=read();
	m=read();
	q=read();
	cnt=n*m;
	For(i,1,n)
		For(j,1,m)
		{
			f[i][j][0]=f[i-1][j][1]+1;
			f[i][j][1]=f[i][j-1][0]+1;
			ans+=f[i][j][0]+f[i][j][1];
		}
	while(q--)
	{
		x=read();
		y=read();
		if(!v[x][y])
		{
			--cnt;
			ans-=f[x][y][0]+f[x][y][1];
			f[x][y][0]=f[x][y][1]=0;
			if(y+1<=m&&!v[x][y+1])
			{
				ans-=f[x][y+1][0]+f[x][y+1][1]-(f[x-1][y+1][1]+2);
				f[x][y+1][0]=f[x-1][y+1][1]+1;
				f[x][y+1][1]=1;
			}
			For(i,x+1,n)
				For(j,y+i-x-1,min(m,y+i-x+1))
					if(!v[i][j])
					{
						ans-=f[i][j][0]+f[i][j][1]-(f[i-1][j][1]+1+f[i][j-1][0]+1);
						f[i][j][0]=f[i-1][j][1]+1;
						f[i][j][1]=f[i][j-1][0]+1;
					}
		}
		else
		{
			++cnt;
			f[x][y][0]=f[x-1][y][1]+1;
			f[x][y][1]=f[x][y-1][0]+1;
			ans+=f[x][y][0]+f[x][y][1];
			if(y+1<=m&&!v[x][y+1])
			{
				ans+=f[x-1][y+1][1]+1+f[x][y][0]+1-(f[x][y+1][0]+f[x][y+1][1]);
				f[x][y+1][0]=f[x-1][y+1][1]+1;
				f[x][y+1][1]=f[x][y][0]+1;
			}
			For(i,x+1,n)
				For(j,y+i-x-1,min(m,y+i-x+1))
					if(!v[i][j])
					{
						ans+=(f[i-1][j][1]+1+f[i][j-1][0]+1)-(f[i][j][0]+f[i][j][1]);
						f[i][j][0]=f[i-1][j][1]+1;
						f[i][j][1]=f[i][j-1][0]+1;
					}
		}
		v[x][y]^=1;
		putll(ans-cnt);
	}
	return 0;
}

```


---

## 作者：I_am_Accepted (赞：1)

~~本人 VP 中写挂了 QwQ。~~

### 题意

每次修改一个格子的状态（是否可用）并询问整个图中阶梯的个数。

### 分析

由于阶梯形状固定，可以将每一个极大的阶梯存下。

发现形状是类似这样的（橙色为红黄共有）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vmecnv52.png)

而每一个长度 $\geqslant2$ 的阶梯都为 有且仅有一个 极大的阶梯 的子阶梯。

对于一个极大的阶梯来说，有一些格子是被禁止的，这些禁止格子将这个阶梯拆成几段。

![](https://cdn.luogu.com.cn/upload/image_hosting/0w6j3rfn.png)

如图，红色被禁止的格子将这两条极大阶梯分别断成了三段。

于是……

### 算法

首先有一个性质：

如果一个阶梯中没有禁止的格子，则此阶梯的 长度 $\geqslant 2$ 的子阶梯的个数为：

$$\begin{pmatrix}len\\2\end{pmatrix}$$

其中 $len$ 为此阶梯的长度。

#### init

对每个极大阶梯计算上述式子并求和即可。

#### modify

**若将 $(x,y)$ 由可用转禁止：**

由于任意一个位置属于两个极大阶梯（这里规定左下角和右上角单独的位置也算极大），将这两个极大阶梯分别进行变化值的计算，即可。

变化值的计算：

极大阶梯中“左上”看作“前”，“右下”看作“后”，记录 $(x,y)$ 在此阶梯中前后第一个遇到的禁止格，记为 $pre$ 和 $suc$。

$e.g.$

![](https://cdn.luogu.com.cn/upload/image_hosting/jon6nfpy.png)

此时将 $(x,y)$ 转禁止，损失为**起点在 $(pre,(x,y)]$，终点在 $[(x,y),suc)$ 这些此极大阶梯的子阶梯**。

乘法原理计算即可。

**若将 $(x,y)$ 由禁止转可用：**

即为上面的逆过程，不再赘述。

### Code

细节较多，每次不要忘了考虑那些长度为 $1$ 的阶梯。

代码不到 $50$ 行。

时间复杂度 $O(n+m+q\log n)$。

[Code Link](https://codeforces.com/contest/1598/submission/132008407)

---

## 作者：Dtw_ (赞：0)

# 前言
/bx/bx [@__ryp__](https://www.luogu.com.cn/user/723993)。
# 题意
有 $n \times m$ 的网格，起初所有的格子都是白的。

定义阶梯为：起点到终点的路径上（包括起点和终点）都是白色的，且形状为“下右下右下右......”或者是“右下右下右下......”。

每次将一个点的颜色进行反转，求对于每次修改后的网格中阶梯的数量。
# Solution
先考虑暴力。

设 $f_{i, j, 0/1}$ 表示现在到了 $(i, j)$ 上一步是由上还是左转移过来的。

那转移有：

$$f_{i, j, 0} = f_{i-1, j, 1} + 1
\\
\
\\

f_{i, j, 1} = f_{i, j-1, 0} + 1$$

其中这个 $+1$ 是因为单独一个格子也算所以要加上他自己。

然后答案就是 $\left (\sum_{i=1}^{n}\sum_{j=1}^{n} \sum_{k=0}^{1}f_{i,j,k}\right ) - cnt$ 其中 $cnt$ 为当前白色点的数量，因为每个格子都被单独算了两遍所以要减掉。

每次修改跑一遍设遇到黑色的格子下标为 $(i,j)$ 则把 $f_{i,j,0}$ 和 $f_{i,j,1}$ 全设为 $0$ 就好。

现在考虑优化。值得注意的是，修改 $(i, j)$ 这个点只会对他的阶梯有影响，所以直接暴力修改这个阶梯就行，可以看一下代码注释。

时间复杂度 $O(nm + qn)$。

# Code

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e3 + 10;

int n, m, q; 

int cnt, res, f[N][N][2], a[N][N];

void dfs(int x, int y, int c, int k)
{
	if (x < 1 || x > n || y < 1 || y > m) return;
	if (!a[x][y]) return;
	res -= f[x][y][k];
	f[x][y][k] -= c;
	res += f[x][y][k];
	if (k) dfs(x + 1, y, c, 0); // 当前是 1 就要往下走 因为 1 表示往右走, 当前右已经走过了所以要向下走 
	else dfs(x, y + 1, c, 1);   // 当前是 0 就要往右走 同理 
}

signed main()
{
	fst
	cin >> n >> m >> q;
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			// [0] 表示上一步往下走 [1] 表示上一步往右走 
			a[i][j] = 1;
			f[i][j][0] = f[i - 1][j][1] + 1;
			f[i][j][1] = f[i][j - 1][0] + 1;
			res += f[i][j][0] + f[i][j][1];
			cnt++;
		}
	}
	while (q--)
	{
		int x, y;
		cin >> x >> y;
		if (a[x][y])
		{
			cnt--;
			res -= f[x][y][0] + f[x][y][1];
			dfs(x, y + 1, f[x][y][0], 1); // 0 就要往右走 可以看 dfs 里的注释 
			dfs(x + 1, y, f[x][y][1], 0); // 1 往下走 
			f[x][y][0] = f[x][y][1] = 0;
		}
		else
		{
			cnt++;
			f[x][y][0] = f[x - 1][y][1] + 1; 
			f[x][y][1] = f[x][y - 1][0] + 1;
			res += f[x][y][0] + f[x][y][1]; // 同理 
			dfs(x, y + 1, -f[x][y][0], 1);
			dfs(x + 1, y, -f[x][y][1], 0);
		}
		a[x][y] ^= 1;
		cout << res - cnt << endl;
	}
	return 0;
}

```

---

## 作者：ZLCT (赞：0)

# CF1598E Staircases
## 题意
给定一个初始全为白色的 $n\times m$ 的矩形，每次操作会使一个方格黑白反转。定义一个阶梯为向右向下交替的同色连通块（一个格点也算）。问每次操作后有多少白色阶梯。阶梯样式如下图。\
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1598E/30e6b70a090f9657a06b957e8113944b3c2b16f3.png)
## eazy version
我们可以从简单的问题入手，假设询问只有一次，也就是给定一个黑白染色的方格，求有多少白色阶梯。\
那么一个暴力的思路就是枚举阶梯起点（左上角），依次找可到达的阶梯。\
这样的复杂度大概是 $O(nm\max(n,m))$，显然是不行的。\
由于每次阶梯只要确定方向后的路径是固定的，我们其实只关系最远能到多远。\
那么问题解可以分解成先向下/右走一步，接着从到达的位置继续向另一个方向走。\
这就满足了 dp 的条件，我们设 $f_{i,j,0/1}$ 表示以 $i,j$ 为起点（左上角），第一步向下/右走的阶梯数。\
转移方程如上就是 $f_{i,j,0}=f_{i+1,j,1}+1;f_{i,j,1}=f_{i,j+1,0}+1$（加一是算上单独格点本身）。\
那么最终答案就是所有 $f_{i,j,0/1}$ 的和…吗？\
当然不是，我们在统计 $f_{i,j,0/1}$ 时都把 $i,j$ 单独成阶梯考虑了一遍，所以最终答案需要减去重复统计的 $n\times m$ 个单独格点。\
这样简化版的问题我们就有了 $O(nm)$ 的解法。
## hard version
接下来我们考虑修改操作对于 $f$ 的影响。\
如果是白点变黑点，那一个比较明显的影响就是对于 $f_{i,j,0/1}$ 都会变成 $0$。\
而对于无法到达 $(i,j)$ 的点，很明显它们的 $f$ 值不会发生任何改变。\
所以发生改变的只有可以到达 $(i,j)$ 的点。\
由于路径是一个阶梯，所以倒推上去只有 $(i,j),(i-1,j),(i,j-1)$ 左上方的三行斜线会发生改变。\
由于操作次数较少，对于这些点我们完全可以暴力修改。\
由于转移方程其实是一个恒等式，所以修改可以直接用我们的转移方程，只需要把 $f_i,j,0/1$ 单独赋值为 $0$ 即可。\
小细节：更新 $ans$ 时由于可能减少或增加一个点，于是需要注意单独格点的计算。而更新 $f$ 数组时，如果当前节点仍是黑点，那么当前节点出发（左上角）的方案数依然会是 $0$。
## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1010;
int n,m,Q;
ll f[N][N][2],ans;
bool vis[N][N];
void init(){
    for(int i=n;i>=1;--i){
        for(int j=m;j>=1;--j){
            for(int k=0;k<=1;++k){
                if(k)f[i][j][k]=f[i][j+1][k^1]+1;
                else f[i][j][k]=f[i+1][j][k^1]+1;
                ans+=f[i][j][k];
            }
        }
    }
    ans-=n*m;
}
void add(int x,int y){
    f[x][y][0]=f[x+1][y][1]+1;
    f[x][y][1]=f[x][y+1][0]+1;
    ans+=f[x][y][0]+f[x][y][1]-1;
    int delta=min(x,y);
    for(int k=0;k<=1;++k){
        if(vis[x-1][y])ans-=f[x-1][y][k];
        else break;
        if(k)f[x-1][y][k]=f[x-1][y+1][k^1]+1;
        else f[x-1][y][k]=f[x][y][k^1]+1;
        if(vis[x-1][y])ans+=f[x-1][y][k];
    }
    for(int k=0;k<=1;++k){
        if(vis[x][y-1])ans-=max(1ll,f[x][y-1][k]);
        else break;
        if(k)f[x][y-1][k]=f[x][y][k^1]+1;
        else f[x][y-1][k]=f[x+1][y-1][k^1]+1;
        if(vis[x][y-1])ans+=max(1ll,f[x][y-1][k]);
    }
    for(int i=1;i<delta;++i){
        int nx=x-i,ny=y-i;
        for(int k=0;k<=1;++k){
            if(vis[nx][ny])ans-=f[nx][ny][k];
            else break;
            if(k)f[nx][ny][k]=f[nx][ny+1][k^1]+1;
            else f[nx][ny][k]=f[nx+1][ny][k^1]+1;
            if(vis[nx][ny])ans+=f[nx][ny][k];
        }
        for(int k=0;k<=1;++k){
            if(vis[nx-1][ny])ans-=f[nx-1][ny][k];
            else break;
            if(k)f[nx-1][ny][k]=f[nx-1][ny+1][k^1]+1;
            else f[nx-1][ny][k]=f[nx][ny][k^1]+1;
            if(vis[nx-1][ny])ans+=f[nx-1][ny][k];
        }
        for(int k=0;k<=1;++k){
            if(vis[nx][ny-1])ans-=f[nx][ny-1][k];
            else break;
            if(k)f[nx][ny-1][k]=f[nx][ny][k^1]+1;
            else f[nx][ny-1][k]=f[nx+1][ny-1][k^1]+1;
            if(vis[nx][ny-1])ans+=f[nx][ny-1][k];
        }
    }
}
void del(int x,int y){
    ans-=f[x][y][0]+f[x][y][1]-1;
    f[x][y][0]=f[x][y][1]=0;
    int delta=min(x,y);
    for(int k=0;k<=1;++k){
        if(vis[x-1][y])ans-=f[x-1][y][k];
        else break;
        if(k)f[x-1][y][k]=f[x-1][y+1][k^1]+1;
        else f[x-1][y][k]=f[x][y][k^1]+1;
        if(vis[x-1][y])ans+=f[x-1][y][k];
    }
    for(int k=0;k<=1;++k){
        if(vis[x][y-1])ans-=max(1ll,f[x][y-1][k]);
        else break;
        if(k)f[x][y-1][k]=f[x][y][k^1]+1;
        else f[x][y-1][k]=f[x+1][y-1][k^1]+1;
        if(vis[x][y-1])ans+=max(1ll,f[x][y-1][k]);
    }
    for(int i=1;i<delta;++i){
        int nx=x-i,ny=y-i;
        for(int k=0;k<=1;++k){
            if(vis[nx][ny])ans-=f[nx][ny][k];
            else break;
            if(k)f[nx][ny][k]=f[nx][ny+1][k^1]+1;
            else f[nx][ny][k]=f[nx+1][ny][k^1]+1;
            if(vis[nx][ny])ans+=f[nx][ny][k];
        }
        for(int k=0;k<=1;++k){
            if(vis[nx-1][ny])ans-=f[nx-1][ny][k];
            else break;
            if(k)f[nx-1][ny][k]=f[nx-1][ny+1][k^1]+1;
            else f[nx-1][ny][k]=f[nx][ny][k^1]+1;
            if(vis[nx-1][ny])ans+=f[nx-1][ny][k];
        }
        for(int k=0;k<=1;++k){
            if(vis[nx][ny-1])ans-=f[nx][ny-1][k];
            else break;
            if(k)f[nx][ny-1][k]=f[nx][ny][k^1]+1;
            else f[nx][ny-1][k]=f[nx+1][ny-1][k^1]+1;
            if(vis[nx][ny-1])ans+=f[nx][ny-1][k];
        }
    }
}
signed main(){
    cin>>n>>m>>Q;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            vis[i][j]=1;
        }
    }
    init();
    while(Q--){
        int x,y;cin>>x>>y;
        if(vis[x][y]){
            del(x,y);
        }else{
            add(x,y);
        }
        vis[x][y]^=1;
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

