# [ARC157C] YY Square

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc157/tasks/arc157_c

$ H $ 行 $ W $ 列のマス目の各マスに `X`, `Y` のいずれかの文字が書かれています． 上から $ i $ 行目，左から $ j $ 列目のマスを $ (i,\ j) $ で表します． マス目に書かれている文字は $ H $ 個の文字列 $ S_1,\ S_2,\ \dots,\ S_H $ によって与えられ，$ S_i $ の $ j $ 文字目がマス $ (i,\ j) $ に書かれた文字を表します．

下または右に隣接するマスへの移動を繰り返してマス $ (1,\ 1) $ からマス $ (H,\ W) $ に至る経路 $ P $ に対して，

- 「 $ P $ で通るマスに書かれた文字を順に並べて得られる長さ $ (H\ +\ W\ -\ 1) $ の文字列」を $ \mathrm{str}(P) $ とし，
- 「 $ \mathrm{str}(P) $ 中で `Y` 同士が隣り合う箇所の**個数の $ 2 $ 乗**」を $ P $ の**スコア**と定義します．
 
そのような経路 $ P $ としてあり得るものは $ \displaystyle\binom{H\ +\ W\ -\ 2}{H\ -\ 1} $ 通りありますが，その全てに対するスコアの総和を $ 998244353 $ で割った余りを求めてください．

  $ \binom{N}{K} $ の意味 $ \displaystyle\binom{N}{K} $ は，$ N $ 個の相異なる要素から $ K $ 個を選ぶ場合の数を表す二項係数です．

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 2000 $
- $ 1\ \leq\ W\ \leq\ 2000 $
- $ S_i\ (1\ \leq\ i\ \leq\ H) $ は `X`, `Y` からなる長さ $ W $ の文字列である．
 
### Sample Explanation 1

経路 $ P $ としてあり得るものは $ (1,\ 1)\ \to\ (1,\ 2)\ \to\ (2,\ 2) $ と $ (1,\ 1)\ \to\ (2,\ 1)\ \to\ (2,\ 2) $ の $ 2 $ 通りです． - $ (1,\ 1)\ \to\ (1,\ 2)\ \to\ (2,\ 2) $ の場合，$ \mathrm{str}(P)\ =\ {} $`YYY` であり，$ 1,\ 2 $ 文字目と $ 2,\ 3 $ 文字目の $ 2 $ 箇所で `Y` 同士が隣り合っているので，スコアは $ 2^2\ =\ 4 $ です． - $ (1,\ 1)\ \to\ (2,\ 1)\ \to\ (2,\ 2) $ の場合，$ \mathrm{str}(P)\ =\ {} $`YXY` であり，`Y` 同士が隣り合う箇所は無いので，スコアは $ 0^2\ =\ 0 $ です． したがって，求める総和は $ 4\ +\ 0\ =\ 4 $ となります．

### Sample Explanation 2

$ 2 $ 通りのいずれの経路の場合も $ \mathrm{str}(P)\ =\ {} $`XYY` であり，スコアは $ 1^2\ =\ 1 $ です．

### Sample Explanation 3

スコアの総和を $ 998244353 $ で割った余りを出力してください．

## 样例 #1

### 输入

```
2 2
YY
XY```

### 输出

```
4```

## 样例 #2

### 输入

```
2 2
XY
YY```

### 输出

```
2```

## 样例 #3

### 输入

```
10 20
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY
YYYYYYYYYYYYYYYYYYYY```

### 输出

```
423787835```

# 题解

## 作者：naoliaok_lovely (赞：4)

套路题，这种涉及到了 **次方** 的题目知道套路就很好做。

先考虑没有 **权值平方的和** 的情况，只是普通的权值和。设 $f_{k,i,j}$ 表示以 $c_{i,j}$ 为终点的权值的 $k$ 次方的和。这种情况下，很容易写出状态转移方程：  

- 若 $c_{i,j}=\text{X}$，则 $f_{1,i,j}=f_{1,i-1,j}+f_{1,i,j-1}$。
- 若 $c_{i,j}=\text{Y}$，则 $f_{1,i,j}=f_{1,i-1,j}+[c_{i-1,j}=\text{Y}]\times C_{i+j-3}^{i-2}+f_{1,i,j-1}+[c_{i,j-1}=\text{Y}]\times C_{i+j-3}^{i-1}$。

但是问题来了，对于题干中的平方，我们应该怎么处理呢？  
——没错，拆开！

举个例子，对于 $(a+1)^2$，我们可以将其转化为 $a^2+2a+1$。这样做，就可以达到递推的效果。

至于转移方程，基本与 $1$ 次的那种类似，见代码。

```
#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int N = 2010, M = 2 * N, mod = 998244353;
int n, m;
char c[N][N];
LL f[3][N][N];

LL ksm(LL x, LL y)
{
	LL res = 1;
	x %= mod;
	while(y)
	{
		if(y & 1) res = res * x % mod;
		y >>= 1;
		x = x * x % mod;
	}
	return res;
}

LL fac[M], inv[M];
void init(int n)
{
	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = ksm(fac[n], mod - 2);
	for(int i = n - 1; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
}

LL C(int n, int m)
{
	return fac[n] * inv[n - m] % mod * inv[m] % mod;
}

int main()
{
	init(4000);
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		scanf("%s", c[i] + 1);
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(c[i][j] == 'X')
			{
				f[1][i][j] = (f[1][i - 1][j] + f[1][i][j - 1]) % mod;
				f[2][i][j] = (f[2][i - 1][j] + f[2][i][j - 1]) % mod;
			}
			else
			{
				f[1][i][j] = (f[1][i - 1][j] + f[1][i][j - 1] + (c[i - 1][j] == 'Y' ? C(i + j - 3, i - 2) : 0) + (c[i][j - 1] == 'Y' ? C(i + j - 3, i - 1) : 0)) % mod;
				f[2][i][j] = (f[2][i - 1][j] + f[2][i][j - 1] + (c[i - 1][j] == 'Y' ? C(i + j - 3, i - 2) + 2 * f[1][i - 1][j] : 0) + (c[i][j - 1] == 'Y' ? C(i + j - 3, i - 1) + 2 * f[1][i][j - 1] : 0)) % mod;
			}
	
	cout << f[2][n][m] << endl;
	return 0;
}
```

---

## 作者：Cure_Wing (赞：3)

[AT_arc157_c [ARC157C] YY Square](https://www.luogu.com.cn/problem/AT_arc157_c)

### 思路

看到向右和向下的路径，又要求和，于是想到了动态规划。

设计状态时，看到是个矩阵，沿路又有关于 $Y$ 的三种状态：$0$ 个，$1$ 个和 $2$ 个及以上，于是设 $f_{i,j,0/1/2}$ 表示当前从 $(1,1)$ 走到 $(i,j)$，此时后缀的 $Y$ 有 $0$ 个/$1$ 个/$2$ 个及以上时所得答案。

考虑此时的点，如果 $s_{i,j}=X$，显然 $f_{i,j,0}=\sum\limits_{k=1}^3f_{i-1,j,k}+f_{i,j-1,k},f_{i,j,1}=f_{i,j,2}=0$，因为此时没有 $Y$，后缀长度一定为 $0$，且不产生任何贡献，而且还会清空之前的后缀长度。

考虑 $s_{i,j}=Y$，当后缀为 $1$ 时，显然 $f_{i,j,1}=f_{i-1,j,0}+f_{i,j-1,0}$，因为后缀长度只有 $1$，也无法产生贡献。

考虑 $s_{i,j}=Y$，当后缀大于或等于 $2$ 时，可以从后缀 $1$ 和 $2$ 转移，并且开始产生贡献。此时设到 $(i,j)$ 的若干条路径得到 `YY` 的次数为 $a_1,a_2,a_3,\dots,a_k$，那么它们对答案的总和为 $\sum\limits_{i=1}^ka_i^2$，那么加一个 $Y$ 会使得它们变为 $a_1+1,a_2+1,a_3+1,\dots,a_k+1$，对答案的总和变为 $\sum\limits_{i=1}^k(a_i+1)^2=\color{red}\sum\limits_{i=1}^ka_i^2\color{black}+2\color{blue}\sum\limits_{i=1}^ka_i\color{black}+k$，通过代换发现，红色部分与加 $Y$ 之前的贡献相同，于是我们转移时只需要计算新产生的贡献即可。显然的，我们需要维护蓝色部分的和和末尾的 $k$，于是我们新设两个数组，$t_{i,j,0/1/2}$ 表示当前从 $(1,1)$ 走到 $(i,j)$，此时后缀的 $Y$ 有 $0$ 个/$1$ 个/$2$ 个及以上时所得所有路径的 `YY` 个数之和，$c_{i,j,0/1/2}$  表示当前从 $(1,1)$ 走到 $(i,j)$，此时后缀的 $Y$ 有 $0$ 个/$1$ 个/$2$ 个及以上时所有路径的条数。此时写出 $f_{i,j,2}$ 的转移方程：$\color{green}f_{i,j,2}=f_{i-1,j,1}+f_{i,j-1,1}+f_{i,j-1,2}+f_{i-1,j,2}\color{black}+2\times t_{i,j,2}+c_{i,j,2}$。

考虑 $t$ 和 $c$ 的转移。当 $s_{i,j}=X$ 或 $s_{i,j}=Y$ 且后缀长度为 $1$ 时，它们的转移和 $f$ 是一样的，因为没有贡献产生。当 $s_{i,j}=Y$ 且后缀长度为 $2$ 时，$c$ 的转移方程和 $f$ 的绿色部分相同，显然需要合并长度的个数。而 $t$ 的转移，不仅需要合并长度，按照 $f$ 的绿色部分转移，而且需要加上这个 $Y$ 产生的新长度，于是最终要加上新的 $c_{i,j,2}$。稍微想一下，可以发现转移的顺序是，先转移 $c$，再合并 $t$ 的长度，然后转移 $f$，最后给 $t$ 加上 $c_{i,j,2}$ 的新长度。因为 $c_{i,j,2}$ 开头的 $Y$ 不会对 $f_{i,j,2}$ 有影响，而是会对之后的答案贡献。

答案的话就是 $\begin{cases}f_{h,w,0}&(s_{h,w}=X)\\f_{h,w,1}+f_{h,w,2}&(s_{h,w}=Y)\end{cases}$，原因不用多说。

最后的话注意一下边界条件 $c_{0,1,0}=1$，即空路径（$Y$ 的个数为 $0$） 有 $1$ 条，否则根本无法转移。

时间复杂度 $O(hw)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=2003,p=998244353;
int h,w,f[N][N][3],t[N][N][3],c[N][N][3];
std::string s[N];
signed main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>h>>w;c[0][1][0]=1;
    for(int i=1;i<=h;++i){cin>>s[i];s[i]=" "+s[i];}
    for(int i=1;i<=h;++i)
        for(int j=1;j<=w;++j)
            if(s[i][j]=='X'){//上面讲的分类
                for(int k=0;k<=2;++k){
                    f[i][j][0]=(f[i][j][0]+(f[i-1][j][k]+f[i][j-1][k])%p)%p;
                    t[i][j][0]=(t[i][j][0]+(t[i-1][j][k]+t[i][j-1][k])%p)%p;
                    c[i][j][0]=(c[i][j][0]+(c[i-1][j][k]+c[i][j-1][k])%p)%p;//上面讲的转移方程
                }
            }else{
                f[i][j][1]=(f[i-1][j][0]+f[i][j-1][0])%p;
                t[i][j][1]=(t[i-1][j][0]+t[i][j-1][0])%p;
                c[i][j][1]=(c[i-1][j][0]+c[i][j-1][0])%p;
                c[i][j][2]=((c[i][j-1][2]+c[i-1][j][2])%p+(c[i][j-1][1]+c[i-1][j][1])%p)%p;
                t[i][j][2]=((t[i][j-1][2]+t[i-1][j][2])%p+(t[i][j-1][1]+t[i-1][j][1])%p)%p;
                f[i][j][2]=(((f[i][j-1][1]+f[i-1][j][1])%p+(f[i][j-1][2]+f[i-1][j][2])%p)%p+(2*t[i][j][2]%p+c[i][j][2])%p)%p;
                t[i][j][2]=(t[i][j][2]+c[i][j][2])%p;//上面讲的顺序
            }
    cout<<(f[h][w][0]+(f[h][w][1]+f[h][w][2])%p)%p;//上面讲的答案
    return 0;
}
```

---

## 作者：daduoli (赞：2)

另解，不过也是 dp。

一个小套路，关于平方我们可以考虑他的组合意义。

假如一条路径上有三个 YY。

那么他的贡献是 $(1+1+1)^2=(1+1+1)(1+1+1)$。

相当于是从左右两边括号里各选一个 $1$。

所以实际上我们的贡献可以看成从 $(1,1)\to (n,n)$ 路径上中所有 YY 中任选两个 YY 的方案数（可以选同一个，而且算的是有序对的个数）。

所以我们记状态 $f_{i,j,0/1/2,0/1/2}$ 表示到了 $i,j$ 这个位置，路径上的 YY 选了 $0/1/2$ 个，然后目前连续的 Y 的个数是 $0/1/2$ 个。

时间复杂度 $O(9n^2)$。


```
#include<bits/stdc++.h>
typedef long long LL;

using namespace std;
const int MAXN=2010,P=998244353;
int n,m;
int f[MAXN][MAXN][3][3];
char ch[MAXN][MAXN];
LL add(LL x,LL y) {
	return (x+y>=P?x+y-P:x+y);
}
int main () {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) {
		scanf("%s",ch[i]+1);
	}
	f[1][1][0][(ch[1][1]=='Y')]=1;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(i==1&&j==1) continue;
			for(int q=0;q<=2;++q) {
				for(int w=0;w<=2;++w) {
					f[i][j][q][w]=add(f[i][j][q][w],f[i-1][j][q][w]);
					f[i][j][q][w]=add(f[i][j][q][w],f[i][j-1][q][w]);
				}
			}
			if(ch[i][j]=='X') {
				for(int q=0;q<=2;++q) {
					f[i][j][q][0]=add(f[i][j][q][0],f[i][j][q][1]);
					f[i][j][q][0]=add(f[i][j][q][0],f[i][j][q][2]);
					f[i][j][q][1]=f[i][j][q][2]=0;
				}
			}
			else {
				for(int q=0;q<=2;++q) {
					f[i][j][q][2]=add(f[i][j][q][2],f[i][j][q][1]);
					f[i][j][q][1]=f[i][j][q][0];
					f[i][j][q][0]=0;
				}
				f[i][j][2][2]=add(f[i][j][2][2],add(f[i][j][1][2]*2%P,f[i][j][0][2]));
				f[i][j][1][2]=add(f[i][j][1][2],f[i][j][0][2]);
			}
		}
	}
	printf("%lld\n",add(f[n][m][2][0],add(f[n][m][2][1],f[n][m][2][2])));
	return 0;
}
```


---

## 作者：Composite_Function (赞：2)

$$\text{思路}$$

题目要求我们算所有路径的值之和，每条路径可以看作路径上值之和的平方（题面中地图 $S$ 要求连续的 $\texttt{Y}$，我们可以把它看作一个新的地图 $T$）。此题第一眼看上去很难，但不妨我们可以想一想弱化的题意。

可以考虑，弱化题意为线性的的而不是平方的。对于地图 $T$ 中的每个点 $(x,y)$，走到该点有 $X$ 种方法（$X$ 可以用杨辉三角预处理），那么对于到该点做出的值之和为： $T_{x,y} \times X$。对于点 $(x,y)$，他的答案可以推到 $(x + 1, y)$ 和 $(x, y + 1)$。这样我们就能用类 DP 的方法处理这个问题。注意，我们并不需要知道每一条路径的值，取而代之的是值之和。

回到原问题。不同于弱化问题的的地方在于，每有一个 $T_{x,y}=1$，所做出的贡献是不一样的。若目前一条路径上有 $N$ 个 $T_{i, j}=1$，那么新增的一个会是答案从 $N^2$ 变为 $(N + 1)^2$，贡献为 $2N + 1$。然后我们就会惊奇的发现，因为同样的只要处理和，而这个 $N$ 的和正是我们考虑到的弱化问题！

由此，只要维护零次答案（即组合数）、一次答案和二次答案，这个问题就被解决了。回顾这道题，它并没有用到很难的 OI 或 MO 知识，但却能巧妙地将这道题升级。此题质量很高，值得一做。

------------

$$\text{代码}$$

- 杨辉三角要开两倍，因为是会访问到两倍的

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2010, mod = 998244353;
int n, m, sum[N][N], sqa[N][N], c[4010][4010];
char mp[N][N];
signed main()
{
	c[0][0] = 1;
	for (int i = 1; i <= 4000; ++i)
		for (int j = 0; j <= i; ++j)
			c[i][j] = ((j == 0? 0 : c[i - 1][j - 1]) + c[i - 1][j]) % mod;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> mp[i][j];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			if (i == 1 && j == 1) continue;
			int b1 = (mp[i - 1][j] == 'Y');
			int b2 = (mp[i][j - 1] == 'Y');
			int b3 = (mp[i][j] == 'Y');
			sum[i][j] = (sum[i - 1][j] + (b1 * b3) * (i == 1? 0 : c[i + j - 3][i - 2]) + sum[i][j - 1] + (b2 * b3) * (j == 1? 0 : c[i + j - 3][j - 2]) + mod) % mod;
			sqa[i][j] = (sqa[i - 1][j] + (2 * sum[i - 1][j] + (i == 1? 0 : c[i + j - 3][i - 2]) + mod) % mod * (b1 * b3) + sqa[i][j - 1] + (2 * sum[i][j - 1] + (j == 1? 0 : c[i + j - 3][j - 2]) + mod) % mod * (b2 * b3) + mod) % mod;
		}
	cout << sqa[n][m] << endl;
	return 0;
} 
```

------------

完结！

~~说句题外话，这是这只蒟蒻第一次打 ARC，只做了 A 和 C。。。~~

---

## 作者：CrTsIr400 (赞：1)

[11. [ARC157C] YY Square](https://www.luogu.com.cn/problem/AT_arc157_c)

如果说没有这个平方和的话，那么就比较容易做了，拆一对 `YY` 的贡献，然后 $O(n^2)$ 组合数预处理一下，累计进答案就行了。

（埋下伏笔）

---

遇事不决就 DP，考虑每行每行转移，利用行间的关系来快速解决。

观察权值很小，是不是可以通过权值来计算答案呢？

容易想到一个很暴力的 DP，设 $f[x][y][z]$ 为从起点走到 $(x,y)$ 权值为 $z$ 的答案，若当前为 $y$ 且下一个为 $y$ 就 $z+1$，最后直接把平方的贡献直接枚举，最终算进来。可以压缩一下空间进而达到更高的效率。

考虑 $O(n^3)$ 过两千实在是太不礼貌了，而且常数还要乘上个 2 会很难卡过去，于是考虑 $O(n^2)$ 的。

观察平方这个性质也不是用不上，把平方拆一下还是有用武之地的。

观察到权值为 $x$ 的一条路径，会带来 $2x+1$ 的贡献。于是设 $f[x][y]$ 为从起点走到 $(x,y)$ 的答案。那么其实就是两倍权值和加上从起点走到它的路径条数。

但是我发现我并不知道所有路径的权值和，于是我再设 $g[x][y]$ 为从起点走到 $(x,y)$ 的所有路径 YY 的贡献之和。

回收前面埋下的伏笔，发现我们的 $g[x][y]$ 就直接可以组合数算。也可以不用组合数算，再次递推统计即可。

于是这个题就完美结束了。码量不到 700 bytes。

实现方面的一些优化细节，设 $f[0/1/2][x][y]$ 为贡献的 $0/1/2$ 次方之和，直接转移写的代码会有很多重复、很容易出错，于是运用传引用+指针+换维+滚动数组优化+atcoder modint，可以很容易写得很短很简洁。

```cpp
#include<bits/stdc++.h>
#include<atcoder/modint>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using V=void;
const I N=2002,dx[2]={0,-1},dy[2]={-1,0};using MI=atcoder::modint998244353;
I n,m;string s;bitset<N>b[N];MI f[2][N][3];
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	fo(i,1,n){I j=0;cin>>s;
		for(auto k:s)b[i][++j]=(k=='Y');}
	f[1][1][0]=1;
	fo(i,1,n)fo(j,1,m){MI*nw=f[i&1][j];if(i!=1||j!=1)fill(nw,nw+3,0);
	fo(k,0,1){I x=dx[k]+i,y=dy[k]+j;if(x<1||y<1)continue;
		MI*nx=f[x&1][y];fo(q,0,2)nw[q]+=nx[q];
		if(b[i][j]&&b[x][y])nw[1]+=nx[0],nw[2]+=nx[1]*2+nx[0];
	}}printf("%d\n",f[n&1][m][2].val());
	return 0;}
```

扩展：[P1654 OSU!](https://www.luogu.com.cn/problem/P1654) 和 [Let's Play Osu!](https://www.luogu.com.cn/problem/CF235B)。使用了类似的算法，代码超级简洁。

---

## 作者：Mikefeng (赞：1)

## 题意

给定一个全是 $X$ 和 $Y$ 的 $n\times m$ 的矩阵，从左上角走到右下角有 $\binom {n+m-2} {m-1}$ 种走法。每种走法的权值是这条路径上 $YY$ 的数量的平方，求所有走法的权值和，对 $998244353$ 取模。

$1\le n,m\le 2000$

## 做法

显然是 dp 题。

我们套路地将转移时的式子拆开：
$\begin{alignedat}{3}(x_1+1)^2+(x_2+1)^2+\cdots+(x_k+1)^2
&={x_1}^2+2\times x_1+1+{x_2}^2+2\times x_2+1+\cdots+{x_k}^2+2\times x_k+1
\\&=({x_1}^2+{x_2}^2+\cdots+{x_k}^2)+2\times(x_1+x_2+\cdots+x_k)+k
\end{alignedat}$

$k$ 显然是路径条数，即 $\binom {i+j-2} {j-1}$，那么维护分别维护路径和和路径平方和即可。

## 代码

```cpp
const int N=4005;
const int p=998244353;
int n,m;
char c[N][N];
ll C[N][N],f[N][N],g[N][N];
inline void init(){
	C[0][0]=1;
	F(i,1,n+m){
		C[i][0]=1;
		F(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
	}
}
int main(){
	n=read();m=read();
	init();
	F(i,1,n) F(j,1,m) cin>>c[i][j];
	F(i,1,n) F(j,1,m){
		if(c[i-1][j]=='Y'&&c[i][j]=='Y'&&i>1){
			f[i][j]=(f[i][j]+f[i-1][j]+2*g[i-1][j]+C[i+j-3][j-1])%p;
			g[i][j]=(g[i][j]+g[i-1][j]+C[i+j-3][j-1])%p;
		}else{
			f[i][j]=(f[i][j]+f[i-1][j])%p;
			g[i][j]=(g[i][j]+g[i-1][j])%p;
		}
		if(c[i][j-1]=='Y'&&c[i][j]=='Y'&&j>1){
			f[i][j]=(f[i][j]+f[i][j-1]+2*g[i][j-1]+C[i+j-3][j-2])%p;
			g[i][j]=(g[i][j]+g[i][j-1]+C[i+j-3][j-2])%p;
		}else{
			f[i][j]=(f[i][j]+f[i][j-1])%p;
			g[i][j]=(g[i][j]+g[i][j-1])%p;
		}
	}
	printf("%lld\n",f[n][m]);
	return 0;
}

```


---

## 作者：HappyJaPhy (赞：0)

# 题意
- 给出只含 `X` 和 `Y` 的矩阵，求出所有左上到右下的路径的权值 $v$ 的平方和，定义 $v$ 为路径上连续的两个 `Y` 的数量。

# 分析
- 平方比较难搞定，考虑拆贡献。令 $f_{x,y}$ 表示到达坐标 $(x,y)$ 时的平方和，假设有 $l$ 条到达坐标 $(x,y)$ 的路径，其权值分别为 $v_1,v_2,\cdots,v_l$，那么就有
$$f_{x,y}=\sum_{i=1}^lv_i^2$$
- 若 $mp_{x,y+1}=mp_{x,y}=\texttt{Y}$（对于坐标 $(x+1,y)$ 同理），则有转移
$$f_{x,y+1}=\sum_{i=1}^l(v_i+1)^2$$
展开得到
$$f_{x,y+1}=f_{x,y}+2\sum_{i=1}^lv_i+l$$
- 若 $mp_{x,y+1}$ 和 $mp_{x,y}$ 之间存在 `X`，也就是说其构不成 `YY` 的结构，也就没有多余的贡献，那么直接转移即可。这里的 $\sum_{i=1}^lv_i$ 很好维护，就是一般的 $2$ 维 DP，另外开一个 DP 数据来求即可。
- 上面推式子为了方便写的是主动转移，下面的代码用的是被动转移。

# AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 2005
using namespace std;
int n, m, cnt[N][N], f[N][N], f2[N][N], dv[2][2] = {{0, -1}, {-1, 0}};
bool mp[N][N];
char s[N];

signed main() {
	scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
    	scanf("%s", s + 1);
        for (int j = 1; j <= m; j++) {
        	if (s[j] == 'Y') mp[i][j] = 1;
		}
    }
    cnt[1][1] = 1;
    int x, y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) continue;
            for (int k = 0; k <= 1; k++) {
                x = i + dv[k][0], y = j + dv[k][1];
                if (x < 1 || y < 1) continue;
                cnt[i][j] = (cnt[i][j] + cnt[x][y]) % mod; //转移路径数
                if (mp[x][y] && mp[i][j]) { //都是 Y
                    f[i][j] = (f[i][j] + f[x][y] + cnt[x][y]) % mod; //权值和
                    f2[i][j] = (f2[i][j] + f2[x][y] + (f[x][y] << 1ll) + cnt[x][y]) % mod; //权值平方和
                } else { //存在 X
                    f[i][j] = (f[i][j] + f[x][y]) % mod;
                    f2[i][j] = (f2[i][j] + f2[x][y]) % mod;
                }
            }
        }
    }
    printf("%lld", f2[n][m]);
    return 0;
}
```


---

## 作者：Z1qqurat (赞：0)

学到了一种很新的拆贡献 trick！

发现这种贡献为平方的式子不是很好做，考虑拆贡献。假设目前我们是从位置 $(x_1, y_1)$  转移到位置 $(x_2, y_2)$，且当前所有到 $(x_1, y_1)$ 的路径的权值分别为 $p_1, p_2, \dots, p_k$，如果 $(x_1, y_1)$ 和 $(x_2, y_2)$ 都是 `Y`，那么 $(x_2, y_2)$ 将加上的权值为：

$$
(p_1 + 1) ^ 2 + (p_2 + 1) ^ 2 + \dots + (p_k + 1)^2 = (p_1^2 + p_2^2 + \dots + p_k^2) + 2(p_1 + p_2 + \dots + p_k) + k
$$

不难发现这个东西直接拆开维护就可以了！

设 $f_{0/1/2, i, j}$ 分别为到点 $(i, j)$ 的路径条数，路径权值和（这里指不带平方的），路径权值平方和。那么现在我们仍然是从 $(x_1, y_1)$ 转移到 $(x_2, y_2)$：

* 无论如何，$f_{0, x_2, y_2} \leftarrow f_{0, x_1, y_1}$；

* 如果 $(x_1, y_1)$ 和 $(x_2, y_2)$ 都是 `Y`，那么：

$$
  f_{1, x_2, y_2} \leftarrow f_{1, x_1, y_1} + f_{0, x_1, y_1}
$$
$$
  f_{2, x_2, y_2} \leftarrow f_{2, x_1, y_1} + 2f_{1, x_1, y_1} + f_{0, x_1, y_1}
$$

* 否则如果 $(x_1, y_1)$ 和 $(x_2, y_2)$ 有一个不是 `Y`，那么：
$$
  f_{1, x_2, y_2} \leftarrow f_{1, x_1, y_1}
$$
$$
  f_{2, x_2, y_2} \leftarrow f_{2, x_1, y_1}
$$
  

答案输出 $f_{2, n, m}$ 即可。

同样 trick 的题：ABC277G。

```cpp
#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v); 
using ll = long long;
const int N = 2005, inf = 2e9;
const ll infl = 2e18, P = 998244353;

int n, m;
bool b[N][N];
std::string s;
std::array <int, 3> dx{0, -1}, dy{-1, 0};
std::array <std::array<ll, N>, N> f[3];

int main() {
    #ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    #endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s, s = '0' + s;
        for (int j = 1; j <= m; ++j) b[i][j] = (s[j] == 'Y');
    }
    f[0][1][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if(i == 1 && j == 1) continue;
            for (int k = 0; k < 2; ++k) {
                int x = i + dx[k], y = j + dy[k];
                if(x < 1 || y < 1) continue;
                f[0][i][j] = (f[0][i][j] + f[0][x][y]) % P;
                if(b[x][y] && b[i][j]) {
                    f[1][i][j] = (f[1][i][j] + f[1][x][y] + f[0][x][y]) % P;
                    f[2][i][j] = (f[2][i][j] + f[2][x][y] + 2ll * f[1][x][y] + f[0][x][y]) % P;
                }
                else {
                    f[1][i][j] = (f[1][i][j] + f[1][x][y]) % P;
                    f[2][i][j] = (f[2][i][j] + f[2][x][y]) % P;
                }
            }
        }
    }
    std::cout << f[2][n][m] << "\n";
    return 0;
}
```



---

## 作者：Xy_top (赞：0)

独立想出的一道我感觉挺好的 dp 题。

$n$ 和 $m$ 均 $\leq 2000$ 这显然是 DP，但如果仅仅设 $f_{i,j}$ 为从点 $(i,j)$ 出发走到右下角所有路径上 YY 数量的平方和，就会发现很难转移。

思考其原因，无非就是假设原先是 $3^2+2^2+9^2$，现在多了一个 YY 就成 $4^2+3^2+10^2$ 了，发现多出的就是 $2\times (3+2+9) + 3$其实解决方案很简单，再加一个 $g$ 存储的就是多出的东西，也就是 $(i,j)$ 走到 $(n,m)$ 所有路径上 YY 个数的二倍的和，至于那个 $+1$，其实就是从 $(i, j + 1)$ 或者 $(i + 1,j)$ 走到 $(n,m)$ 的方案数，这样就能很容易地进行 DP 了。

刚开始把 $m$ 写成 $n$ 吓得我以为这个东西假了。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m;
int fac[4005], inv[4005];
char a[2005][2005];
int f[2005][2005], g[2005][2005];
const int mod = 998244353;
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
int C (int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int fun (int n, int m) {return C (n + m - 2, n - 1);}
void solve () {
	scanf ("%d%d", &n, &m);
	For (i, 1, n) For (j, 1, m) cin >> a[i][j];
	fac[0] = 1;
	For (i, 1, 4000) fac[i] = fac[i - 1] * i % mod;
	inv[4000] = q_pow (fac[4000], mod - 2);
	foR (i, 3999, 0) inv[i] = inv[i + 1] * (i + 1) % mod;
	foR (i, n, 1) {
		foR (j, m, 1) {
			if (i != n) {
				f[i][j] = f[i + 1][j];
				g[i][j] = g[i + 1][j];
				if (a[i][j] == 'Y' && a[i + 1][j] == 'Y') {
					f[i][j] = (f[i][j] + g[i + 1][j] + fun (n - i, m - j + 1) ) % mod;
					g[i][j] = (g[i][j] + 2 * fun (n - i, m - j + 1) ) % mod;
				}
			}
			if (j != m) {
				f[i][j] = (f[i][j] + f[i][j + 1]) % mod;
				g[i][j] = (g[i][j] + g[i][j + 1]) % mod;
				if (a[i][j] == 'Y' && a[i][j + 1] == 'Y') {
					f[i][j] = (f[i][j] + g[i][j + 1] + fun (n - i + 1, m - j) ) % mod;
					g[i][j] = (g[i][j] + 2 * fun (n - i + 1, m - j) ) % mod;
				}
			}
		}
	}
	cout << f[1][1];
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：KingPowers (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_arc157_c)

没啥思维含量的 dp 题，直接暴力拆式子维护就做完了，想不明白为啥 AT 和洛谷上都能评到蓝。

最直接的思路就是设 $f_{i,j}$ 表示终点为 $(i,j)$ 时所有路径权值的平方和，那么 $f_{i,j}$ 就可以从 $f_{i-1,j}$ 和 $f_{i,j-1}$ 转移过来，当有一个点和 $(i,j)$ 的字符都是 `Y` 时会产生新的贡献，考虑如何计算这个贡献。

不妨拆下式子，$(a+1)^2=a^2+2a+1$，假设我们能从 $(i',j')$ 转移到 $(i,j)$ 且这两个点字符都为 `Y`，那么每一条能够到 $(i',j')$ 的路径都会给 $f_{i,j}$ 多贡献其权值的二倍加 $1$，因此我们再多记个 $g_{i,j}$ 表示终点为 $(i,j)$ 时的权值和，那么 $(i',j')$ 对 $(i,j)$ 的转移就可以写成

$$
f_{i,j}\leftarrow f_{i',j'}+2g_{i',j'}+cnt_{i',j'}
$$

其中 $cnt_{i,j}$ 是走到 $(i,j)$ 的路径条数，递推出来或者直接组合数算都可以。

然后这题就做完了，时间复杂度 $O(nm)$。

我代码里写的 $f$ 是维护的权值和，$g$ 是维护的权值平方和，跟上文反了过来。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rof(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef pair<int,int> pii;
const int mod=998244353;
const int dx[2]={-1,0},dy[2]={0,-1};
int n,m,f[5005][5005],g[5005][5005],fac[5005],ifac[5005];
string mp[5005];
int qpow(int x,int y){
	int res=1;
	for(;y;x=x*x%mod,y>>=1)
		if(y&1) res=res*x%mod;
	return res;
}
void init(int n){
	fac[0]=1;
	For(i,1,n) fac[i]=fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	Rof(i,n,1) ifac[i-1]=ifac[i]*i%mod;
}
int C(int n,int m){
	if(n<m) return 0;
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int calc(int n,int m){ 
	return C(n+m-2,n-1);
}
void Main(){
	cin>>n>>m;
	For(i,1,n) cin>>mp[i],mp[i]=' '+mp[i];
	For(i,1,n) For(j,1,m) For(k,0,1){
		int xx=i+dx[k],yy=j+dy[k];
		if(xx<1||xx>n||yy<1||yy>m) continue;
		f[i][j]=(f[i][j]+f[xx][yy])%mod;
		g[i][j]=(g[i][j]+g[xx][yy])%mod;
		if(mp[xx][yy]=='Y'&&mp[i][j]=='Y'){
			f[i][j]=(f[i][j]+calc(xx,yy))%mod;
			g[i][j]=(g[i][j]+2*f[xx][yy]%mod+calc(xx,yy))%mod;
		}
	}
	cout<<g[n][m]<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;init(5000);
	while(T--) Main();
	return 0;
}

```


---

