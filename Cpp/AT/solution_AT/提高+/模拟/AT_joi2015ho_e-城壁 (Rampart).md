# 城壁 (Rampart)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2015ho/tasks/joi2015ho_e

歴史学者である JOI 教授は，かつて存在した IOI 王国について研究している．

過去の調査によると，IOI 王国は縦 $ H $ 行，横 $ W $ 列のマスに区切られた長方形の形をしていた．IOI 王国の首都は，防衛のために城壁で囲われていた．

IOI 王国の首都を囲う城壁は次のような形をしている．城壁には大きさと呼ばれる値が定まっている．大きさ $ s $ ($ s\ \geqq\ 3 $) の城壁とは，$ s\ \times\ s $ の正方形の領域から外周以外の $ (s\ -\ 2)\ \times\ (s\ -\ 2) $ の正方形の領域を除いたものである．

調査によると，首都を囲う城壁の大きさは $ L $ 以上であった．また，IOI 王国のいくつかのマスには城壁が存在しなかったことがわかっている．

JOI 教授は，さらなる研究のために，城壁としてありうるものが何通りあるかを知りたい．

## 说明/提示

### 課題

IOI 王国の大きさと，城壁の大きさの最小値，城壁が存在しなかったことが分かっているマスの情報が与えられたとき，城壁としてありうるものは何通りあるかを求めるプログラムを作成せよ．

- - - - - -

### 制限

すべての入力データは以下の条件を満たす．

- $ 1\ \leqq\ H\ \leqq\ 4\,000 $．
- $ 1\ \leqq\ W\ \leqq\ 4\,000 $．
- $ 3\ \leqq\ L\ \leqq\ H $ かつ $ 3\ \leqq\ L\ \leqq\ W $．
- $ 0\ \leqq\ P\ \leqq\ 100\,000 $．
- $ 1\ \leqq\ A_i\ \leqq\ H $ ($ 1\ \leqq\ i\ \leqq\ P $)．
- $ 1\ \leqq\ B_i\ \leqq\ W $ ($ 1\ \leqq\ i\ \leqq\ P $)．
- ($ A_i,\ B_i)\ \neq\ (A_j,\ B_j $) ($ 1\ \leqq\ i\ <\ j\ \leqq\ P $)．

### 小課題

#### 小課題 1 \[4 点\]

以下の条件を満たす．

- $ H\ \leqq\ 500 $．
- $ W\ \leqq\ 500 $．

#### 小課題 2 \[16 点\]

- $ 0\ \leqq\ P\ \leqq\ 10 $ を満たす．

#### 小課題 3 \[80 点\]

追加の制限はない．

- - - - - -

### Sample Explanation 1

この入力例の場合，城壁としてありうるものは以下の $ 4 $ 通りが考えられる．ただし，`×` で示したマスは城壁が存在しなかったことがわかっているマスである． !\[e-1.png\](https://img.atcoder.jp/joi2015ho/e-1.png) - - - - - -

### Sample Explanation 2

\- - - - - -

## 样例 #1

### 输入

```
5 5 3 2
2 2
4 3```

### 输出

```
4```

## 样例 #2

### 输入

```
7 8 4 3
2 2
3 7
6 5```

### 输出

```
13```

## 样例 #3

### 输入

```
4000 4000 1234 4
1161 3028
596 1892
3731 2606
702 1530```

### 输出

```
7050792912```

# 题解

## 作者：Rusalka (赞：1)

## 题意简述

- 给定一张 $H \times W $ 的网格图，其中有 $P$ 个被标记的点，求边长为 $L$ 或以上的正方形的个数，要求正方形的边不得经过被标记的点。

- $1 \le H,W \le 4000$, $1 \le P \le 10^5$

## 分析与解答

考虑枚举合法正方形的左下端点 $(i,j)$ 和正方形边长 $len$ ，由此可以得到右上端点 $(i+len-1,j+len-1)$。

考虑什么条件下枚举到的正方形才能被计入答案。

记 $left,right,up,down$ 数组，分别表示点 $(i,j)$ 向左/右/上/下最多能延伸多少长度，并且不遇到被标记的点。

$left,right,up,down$ 数组可以通过 $\Theta(nm)$ 递推得到。

记 $lu_{i,j}=\min(light_{i,j},up_{i,j})$, $rd_{i,j}=\min(right_{i,j},down_{i,j})$  
$x = i+len-1$，$y=j+len-1$

那么必须当 $lu_{i,j} \ge len$ 且 $rd_{x,y} \ge len$ 且 $len \ge L$ 时，这个正方形才能被计入答案。

也就是说对于 $(i,j)$，我们需要求出有多少个点 $i+len-1$, $j+len-1$ 满足 $rd_{i+len-1,j+len-1} \ge len$。

这个问题就可以用主席树解决。

时间复杂度 $\Theta(nm \log_2 (\max(n,m)))$

## Code

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
const int MAXN = 4010;

int n, m, l, k, a[MAXN][MAXN];
int ld[MAXN][MAXN], rd[MAXN][MAXN], ud[MAXN][MAXN], dd[MAXN][MAXN];

struct node{
	int lc, rc, val;
}t[MAXN*40];
int rt[MAXN], cnt = 0;
void update(int l, int r, int &now, int ver, int pos)
{
	t[now = ++cnt] = t[ver];
	++t[now].val;
	if(l == r) return ;
	int mid = l+r>>1;
	if(pos <= mid) update(l, mid, t[now].lc, t[ver].lc, pos);
	else update(mid+1, r, t[now].rc, t[ver].rc, pos);
}
int query(int l, int r, int x, int y, int ql, int qr)
{
	if(l >= ql && r <= qr) return t[y].val - t[x].val;
	int mid = l+r>>1;
	int res = 0;
	if(ql <= mid) res += query(l, mid, t[x].lc, t[y].lc, ql, qr);
	if(qr >= mid+1) res += query(mid+1, r, t[x].rc, t[y].rc, ql, qr);
	return res;
}

int d1[MAXN], d2[MAXN], tot;

inline int calc()
{
	const int maxn = max(n, m);
	cnt = 0;
	for(int i=1;i<=tot;i++)
		update(-maxn, maxn, rt[i], rt[i-1], d2[i]-i-1);
	int res = 0;
	for(int i=1;i<=tot;i++)
	{
		int nl = i+l-1, nr = i+d1[i]-1;
		if(nl > nr) continue;
		res += query(-maxn, maxn, rt[nl-1], rt[nr], -i, maxn);
	}
	return res;
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&l,&k);
	for(int i=1;i<=k;i++)
	{
		int x, y;
		scanf("%d%d",&x,&y);
		a[x][y] = 1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			ld[i][j] = a[i][j]?0:ld[i][j-1]+1;
			ud[i][j] = a[i][j]?0:ud[i-1][j]+1;
		}
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
		{
			rd[i][j] = a[i][j]?0:rd[i][j+1]+1;
			dd[i][j] = a[i][j]?0:dd[i+1][j]+1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j] = 0;
	ll ans = 0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]) continue;
			int x = i, y = j;
			tot = 0;
			while(x <= n && y <= m)
			{
				a[x][y] = 1;
				d1[++tot] = min(rd[x][y], dd[x][y]);
				d2[tot] = min(ld[x][y], ud[x][y]);
				++x, ++y;
			}
			ans += calc();
		}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：极寒神冰 (赞：0)

将不存在城墙的格子看作 $0$ ，有城墙的格子看作 $1$。

令 $R_{i,j},L_{i,j},U_{i,j},D_{i,j}$​ 表示一个格子能向右/左/上/下延伸的长度，这几个量都可以在 $\mathcal O(n\times m)$ 的时间内预处理得到。

假设当前有一个左下角为 $(sx,sy)$，右上角为 $(tx,ty)$ 边长为 $d=tx-sx+1=ty-sy+1$ 的正方形满足为一个合法的城墙，当且仅当 $d\ge L$ 且 $\min(R_{sx,sy},U_{sx,sy})\ge d$ 且 $\min(L_{tx,ty},D_{tx,ty})\ge d$。

 由于此时一定有 $sx+sy=tx+ty$，因此可以按照 $x+y$ 即行号列号之和来枚举每条对角线。

考虑固定 $k=x+y$​，对于每组 $x_0+y_0=k$​，需要快速求出有多少 $x$​ 满足上述条件。

由于 $d=x_0-x+1$​，因此上面的条件可以转化为 $x_0-\min(R_{x_0,y_0},U_{x_0,y_0})+1\le x\le x_0-L+1\and \min(L_{x,y},D_{x,y})+x-1\ge x_0$

因此对于每一个格子创建点 $(x,\min(L_{x,k-x},D_{x,k-x})+x-1)$​，那么每次询问就变成了一个二维数点问题，树状数组解决即可。

时间复杂度 $\mathcal O(nm\log \min(n,m))$​

```int n,m,l,k;
int n,m,l,k;
int L[4444][4444],R[4444][4444],U[4444][4444],D[4444][4444];
int za[4444][4444];
vector<int>v[4444];

int val[4444];
inline void add(int x,int k)
{
    for(;x<=m;x+=(x&(-x))) val[x]+=k;
}
inline int query(int x)
{
    int ret=0;
    for(;x;x-=(x&(-x))) ret+=val[x];
    return ret;
}
signed main()
{
    n=read(),m=read(),l=read(),k=read();
    R(i,1,k)
    {
        int x=read(),y=read();
        za[x][y]=1;
    }
    R(i,1,n) R(j,1,m) if(!za[i][j]) L[i][j]=L[i][j-1]+1,U[i][j]=U[i-1][j]+1;
    L(i,1,n) L(j,1,m) if(!za[i][j]) R[i][j]=R[i][j+1]+1,D[i][j]=D[i+1][j]+1;
    R(i,1,n) R(j,1,m) ckmin(L[i][j],D[i][j]),ckmin(R[i][j],U[i][j]);
    ll ans=0;
    R(s,2,n+m)
    {
        int sx=1,sy=s-1;
        if(sy>m) sx+=sy-m,sy=m;
        for(int x=sx,y=sy;x<=n&&y>=1;++x,--y) v[y-L[x][y]].pb(y),add(y,1);
        for(int x=sx,y=sy;x<=n&&y>=1;++x,--y)
        {
            for(int tt:v[y]) add(tt,-1);
            if(R[x][y]>=l) ans+=query(y+R[x][y]-1)-query(y+l-2);
        }               
        R(i,1,m) v[i].clear(),val[i]=0;
    }
    printf("%lld\n",ans);
}
```



---

