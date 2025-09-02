# Connected Cubes

## 题目描述

There are $ n \cdot m $ unit cubes currently in positions $ (1, 1, 1) $ through $ (n, m, 1) $ . Each of these cubes is one of $ k $ colors. You want to add additional cubes at any integer coordinates such that the subset of cubes of each color is connected, where two cubes are considered connected if they share a face.

In other words, for every pair of cubes of the same color $ c $ , it should be possible to travel from one to the other, moving only through cubes of color $ c $ that share a face.

The existing cubes are currently in the corner of a room. There are colorless cubes completely filling the planes $ x = 0 $ , $ y = 0 $ , and $ z = 0 $ , preventing you from placing additional cubes there or at any negative coordinates.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1965E/e7bc678b62ef5fe5e71522904706ca384bbd46d9.png)Find a solution that uses at most $ 4 \cdot 10^5 $ additional cubes (not including the cubes that are currently present), or determine that there is no solution. It can be shown that under the given constraints, if there is a solution, there is one using at most $ 4 \cdot 10^5 $ additional cubes.

## 说明/提示

The image in the statement corresponds to the first example case, with $ \text{red} = 1 $ , $ \text{blue} = 2 $ , $ \text{green} = 3 $ .

## 样例 #1

### 输入

```
3 4 3
3 2 3 1
1 1 1 1
1 3 3 2```

### 输出

```
13
1 1 2 3
1 3 2 3
2 1 2 3
2 2 2 3
2 3 2 3
3 3 2 3
1 2 2 2
1 2 3 2
1 3 3 2
1 4 3 2
2 4 3 2
3 4 3 2
3 4 2 2```

## 样例 #2

### 输入

```
2 2 2
2 1
1 2```

### 输出

```
9
1 3 1 1
2 3 1 1
3 1 1 1
3 2 1 1
3 3 1 1
1 1 2 2
1 2 2 2
2 1 2 2
2 2 2 2```

# 题解

## 作者：rui_er (赞：60)

场切了 1E，第一次上 IGM，纪念一下。

多图警告。

我们称题目中的一个方块为“某色混凝土”。感受一下，发现本题主要的难点在于这些混凝土方块排布得太紧密了，导致容易出现互相遮挡的现象，进而难以构造。于是，我们先思考能否通过一些操作使得这些混凝土互相分离。

如下图的方式可以将每两列混凝土中间插入一列空气：

![](https://cdn.luogu.com.cn/upload/image_hosting/bcsm039g.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/fijzod14.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/7epoyd7j.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/nnr5lqt6.png)

至此，我们在每两列之间都塞了一列空气，且最上层的每块混凝土都显然与最下层对应的混凝土连通。

显然，最上层所有混凝土均至少紧挨着一格空气，我们只需要把所有空气替换成一种颜色的混凝土，那么这种颜色的所有混凝土就连通了：

![](https://cdn.luogu.com.cn/upload/image_hosting/7j33u02b.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/udoakyy1.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/hbj6udo8.png)

于是就做完了。出于美观考虑，上面示意图中的构造与代码中的构造略有出入，但主要思路完全一致。代码中最坏情况 $p=373700$，足以通过本题。这个构造显然还有很大的优化空间，但是我懒了。

![](https://cdn.luogu.com.cn/upload/image_hosting/2xx0ei63.png)

谢谢大家！

```cpp
// Problem: E. Connected Cubes
// Contest: Codeforces - Codeforces Round 941 (Div. 1)
// URL: https://codeforces.com/contest/1965/problem/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 55;

int n, m, k, a[N][N], px[N][N], py[N][N];
vector<tuple<int, int>> pos[N];
vector<tuple<int, int, int, int>> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    // rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
    rep(i, 1, n) rep(j, 1, m) a[i][j] = k;
    rep(i, 1, n) rep(j, 1, m) px[i][j] = i, py[i][j] = j;
    rep(z, 1, m) {
        if(z >= 2) {
            rep(i, 1, n) rep(j, 1, m) ans.emplace_back(px[i][j], py[i][j], z, a[i][j]);
        }
        rep(i, 1, n) {
            rep(j, 1, m) {
                if(j == m - z + 1) {
                    int gy = 2 * j - 1;
                    rep(y, j + 1, gy) ans.emplace_back(i, y, z, a[i][j]);
                    px[i][j] = i;
                    py[i][j] = gy;
                }
            }
        }
    }
    int z = m;
    rep(c, 1, k) {
        rep(i, 1, n + 1) {
            rep(j, 1, 2 * m - 1) {
                if(i == n + 1) ans.emplace_back(i, j, z, c);
                else if(j % 4 == 2 || j >= 2 * m - 3 && j % 2 == 0) ans.emplace_back(i, j, z, c);
                else if(int u = a[i][(j + 1) / 2]; (j & 1) && z != m && u >= c) ans.emplace_back(i, j, z, u);
            }
        }
        ++z;
    }
    cout << ans.size() << endl;
    for(auto [x, y, z, c] : ans) cout << x << " " << y << " " << z << " " << c << endl;
    return 0;
}
```

---

## 作者：Jorisy (赞：3)

upd：玻璃太不清楚了，将其更换为陶瓦。

---

样例颜色有点少了，以下图为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/p9bsnkek.png)

首先一个很自然的想法是将每个块互相分离，这样可以每层使用一种颜色填充空隙。

列之间可以如下图一样分离，行同理。

![](https://cdn.luogu.com.cn/upload/image_hosting/xwr8z7y8.png)

于是每层可以这样做：

![](https://cdn.luogu.com.cn/upload/image_hosting/occ66k3q.png)

但是用到的方块数量远远超过了限制，考虑优化。

考虑到，假设已经分离了列，那其实行是没必要分离的，可以将该层填满后再在下面添一行来连接。如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/ikbetuh8.png)

但这样其实还是超出范围的，考虑进一步优化。

注意到我们填充的是所有第 $2k(k\in\mathbb N_+)$ 列，其实如果 $2\nmid k$ 的列填充完了，$2\mid k$ 且 $2k+1\neq 2m-1$ 的列就不必再填了，因为每个方块只需要一个额外的列来通往第 $n+1$ 行，前往其他列上。如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/bk9azktp.png)

这样其实就可以过了，最终构造长成下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/b5n61xyi.png)

当然还可以更进一步优化，比如空着的列可以删去，已经填充的颜色不用再增高，等等。

```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int x,y,z,c;
};
set<node>ans;
int n,m,c,a[205][205][205];

bool operator<(node x,node y){return x.x==y.x?x.y==y.y?x.z<y.z:x.y<y.y:x.x<y.x;}

int main()
{
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j][1]);
		}
	}
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
		{
			int k=2;
			while(k<=m-j+1)
			{
				a[i][j][k]=a[i][j][k-1];
				k++;
			}
			k--;
			int l=j+1;
			while(l<=j*2-1)
			{
				a[i][l][k]=a[i][l-1][k];
				l++;
			}
			l--;
			k++;
			while(k<=m+c-1)
			{
				a[i][l][k]=a[i][l][k-1];
				k++;
			}
		}
	}
	for(int k=m;k<=m+c-1;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=2;j<=m*2-1;j+=2)
			{
				if((~(j/2)&1)&&j+1!=m*2-1) continue;
				a[i][j][k]=k-m+1;
			}
		}
		for(int j=2;j<m*2-1;j++) a[n+1][j][k]=k-m+1;
	}
	for(int i=1;i<=100;i++)
	{
		for(int j=1;j<=100;j++)
		{
			for(int k=1;k<=200;k++)
			{
				if(!a[i][j][k]||i&&i<=n&&j&&j<=m&&k==1) continue;
				ans.insert({i,j,k,a[i][j][k]});
			}
		}
	}
	printf("%d\n",ans.size());
	for(auto i:ans) printf("%d %d %d %d\n",i.x,i.y,i.z,i.c);
	return 0;
}
```

---

## 作者：WeWantToRun (赞：3)

（这是我的第一篇题解，如有瑕疵还请多多包涵，欢迎在评论区或私信中指出【玫瑰】【玫瑰】【玫瑰】）

[特别感谢 Nocriz](https://bytew.net/?p=1074)

感觉思想和 [AGC004C](https://www.luogu.com.cn/problem/AT_agc004_c) 有共同之妙。

首先假设我们有一个初始图如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9814avtp.png)

我们首先从前到后，依次把每一排全部拔高 $2,3,5,6,\ldots,3n-1,3n,3n+2,\ldots$ 格，并把后面的拉到前面来，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rsxnmbaf.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/pjoc9q93.png)

完了之后，对于再前面的每一竖版，我们处理一种颜色。只需要把刚才没有用到的 $3n+1$ 的位置全部用这种颜色填满，并且开辟第 $m+1$ 列全部放这个颜色，就可以保证连接，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p9y6p7wk.png)

然后我们只需要对每一种颜色都用一个竖版处理即可，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6dlszgn3.png)

（由于我晕 3D，后面实在是干不下去了）

此构造方法使用块数不会超过 $(n+k)\times(m+1)\times \dfrac{3}{2}n$，Nocriz 给出了 $348800$ 的上界，感觉可能比尺子优（？）

---

## 作者：strcmp (赞：1)

呜惹~

提供一个跟题解区不一样的，自己基本独立想出来的笨蛋做法。这是使用中文四字英文九字母的好题。

个人认为这种做法比较自然，是可以被想出来的构造。

![](https://cdn.luogu.com.cn/upload/image_hosting/fr9ex9kk.png)

比如假设这是我们要联通的平面。

我们肯定是要利用它给定点的范围可以非常大（对比 $n,\,m$ 来说）这点的。

先随便取一边拉出去 $k - 1$ 个。

下一边怎么办，肯定不能直接拉挡住前面拉出来的。

然后我们发现给它增高一格再拉就不会挡了。

然后对于上面的隔两列再增高并拉平。

![](https://cdn.luogu.com.cn/upload/image_hosting/fwluy7kj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/7nm98lc1.png)

按顺序填充颜色：

![](https://cdn.luogu.com.cn/upload/image_hosting/vjktxaks.png)

连接：

![](https://cdn.luogu.com.cn/upload/image_hosting/cdc91rgd.png)

构造完成呐！

先计算我们需要的方块量，这里直接取极限 $n = m = k = 50$。程序计算得到 $342500$，似乎优于目前题解区的其它题解，而且还有不少的优化空间，代码也很好写。

![](https://cdn.luogu.com.cn/upload/image_hosting/0r3fyunc.png)

月亮好闪，拜谢月亮。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define mp make_pair
#define mid (l + r >> 1)
#define pb push_back
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ld = double;
typedef long long int ll;
using pdi = pair<ld, int>;
using vec = vector<int>;
constexpr int maxn = 5e5 + 10;
int d[maxn][4], p = 0, n, m, k, a[55][55];
inline void ins(int x, int y, int z, int c) { d[++p][0] = x, d[p][1] = y, d[p][2] = z, d[p][3] = c; }
int main() {
	scanf("%d%d%d", &n, &m, &k);
	rep(x, 1, n) rep(y, 1, m) scanf("%d", &a[x][y]);
	rep(x, n + 1, n + k - 1) rep(y, 1, m) ins(x, y, 1, a[n][y]);
	rep(x, n, n + k - 1) rep(y, 1, m) ins(x, y, 2, x - n + 1);
	int h = 3, wx = 0, mx = 0;
	per(x, n - 1, 1) {
		rep(y, 1, m) rep(z, 2, h) ins(x, y, z, a[x][y]);
		rep(y, 1, m) rep(z, x + 1, n + k - 1) ins(z, y, h, a[x][y]);
		if (wx) {
			rep(y, 1, m) rep(z, n, n + k - 1) ins(z, y, h + 1, z - n + 1);
			h += 2, wx = 0; mx = h + 1;
		}
		else wx = 1, ++h;
	}
	rep(x, n, n + k - 1) rep(z, 2, mx) ins(x, m + 1, z, x - n + 1);
	printf("%d\n", p);
	rep(i, 1, p) printf("%d %d %d %d\n", d[i][0], d[i][1], d[i][2], d[i][3]);
	return 0;
}
```

---

