# [ABC086D] Checker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc086/tasks/arc089_b

シカのAtCoDeerくんは無限に広がる二次元グリッドを一辺が $ K $ の市松模様で塗ろうと考えています。 ただし、一辺が $ K $ の市松模様とは、各マスが白か黒で塗られたパターンであって、各色の各連結成分が $ K $ $ × $ $ K $ の正方形となっているようなものです。 例えば以下は一辺が $ 3 $ の市松模様の例です。

 ![cba927b2484fad94fb5ff7473e9aadef.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc089_b/f249ddb0b7d4831bdbfc799a6785c179fe0b5887.png)

AtCoDeerくんは $ N $ 個の希望を持っています。 $ i $ 個目の希望は、 $ x_i,y_i,c_i $ で表されます。 これは、$ c_i $ が `B` ならマス $ (x_i,y_i) $ を黒で塗る、 `W` なら白で塗ることを意味しています。 同時に最大でいくつの希望を叶えることが出来るか答えてください。

## 说明/提示

### 制約

- $ 1 $ $ <\ = $ $ N $ $ <\ = $ $ 10^5 $
- $ 1 $ $ <\ = $ $ K $ $ <\ = $ $ 1000 $
- $ 0 $ $ <\ = $ $ x_i $ $ <\ = $ $ 10^9 $
- $ 0 $ $ <\ = $ $ y_i $ $ <\ = $ $ 10^9 $
- $ i $ $ ≠ $ $ j $ なら $ (x_i,y_i) $ $ ≠ $ $ (x_j,y_j) $
- $ c_i $ は `B` または `W`
- $ N,K,x_i,y_i $ は整数

### Sample Explanation 1

上であげた例のように塗ればすべての希望を同時に叶えることができます。

## 样例 #1

### 输入

```
4 3
0 1 W
1 2 W
5 3 B
5 4 B```

### 输出

```
4```

## 样例 #2

### 输入

```
2 1000
0 0 B
0 1 W```

### 输出

```
2```

## 样例 #3

### 输入

```
6 2
1 2 B
2 1 W
2 2 B
1 0 B
0 6 W
4 5 W```

### 输出

```
4```

# 题解

## 作者：littlesnake (赞：3)

这个黑白交错的网格都是以 $2k$ 为周期，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/gjy642d5.png)

因此我们可以意识到，可以做一个转化，将 $(x,y)$ 是白色的愿望转化为 $(x+k,y)$ 是黑色的愿望。随后因为网格以 $2k$ 为周期，因此可以将 $(x,y)$ 是黑色的愿望再转化为 $x$ 与 $y$ 各自对 $2k$ 取模的坐标为黑色的愿望。

然后枚举 $2k \times 2k$ 的平面内，横竖的分割线都在那里。（横竖各 $2$ 条线，如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/v37rescs.png)

最后会把平面分成 $3^2=9$ 部分。

然后我们把输入的愿望当做点，在这 $9$ 块分别进行两种颜色分别的二维数点。由于暴力是 $O(nk^2)$ 的复杂度，明显会超时，因此我们使用二维前缀和优化，时间复杂度 $O(n+k^2)$。

代码如下：

```cpp
# include <bits/stdc++.h>
# define N 2010

using namespace std;

int n, k, ans;
int sum[N][N];

int calc (int xa, int ya, int xb, int yb) {
	return sum[xb][yb] - sum[xb][ya - 1] - sum[xa - 1][yb] + sum[xa - 1][ya - 1]; 
}

signed main () {

	cin >> n >> k;
	int x, y;
	char op;
	for (int i = 1; i <= n; i ++) {
		cin >> x >> y >> op;
		if (op == 'W') x += k;
		sum[x % (2 * k) + 1][y % (2 * k) + 1] ++;
	}
	for (int i = 1; i <= 2 * k; i ++) {
		for (int j = 1; j <= 2 * k; j ++) {
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}
	for (int i = 1; i <= k; i ++) {
		for (int j = 1; j <= k; j ++) {
			int tmp = calc (1, 1, i, j) + calc (i + 1, j + 1, i + k, j + k) + calc (i + k + 1, j + k + 1, 2 * k, 2 * k) + calc (i + k + 1, 1, 2 * k, j) + calc (1, j + k + 1, i, 2 * k);
			ans = max (ans, max (tmp, n - tmp));
		}
	}
	cout << ans;

	return 0;

}


```

---

## 作者：珅肐 (赞：3)

update:修改了一处错误和一处显示问题

题意：有一个无限大的矩阵，用$K*K$的黑白正方形填充。
给你$N$个坐标和它们被期望的颜色，问最多有多少可以同时满足。

就是说，你可以拖动这个矩阵，找一个合适的位置使满足数最大，输出这个最大满足值

首先这个矩阵是重复的，以$2K$为边长的正方形为一个单位。

我们可以将所有坐标对$2K$取模，这样答案是不变的，就将$x_iy_i$的范围缩到了$1000$

一开始考虑直接$a[x\%2k][y\%2k]$++，然后想办法$n^2$移动行列找到最优解

实现比较麻烦，想到一个更容易实现的做法

我们其实可以对矩阵进一步压缩到$K*K$

每一个点对答案都是单独贡献的，而且只要确定一块黑色区域，整个贡献就可以算出

我们可以只算黑色，用$N$减去黑色的就是白色答案。

我们需要把白色映射到黑色上面
```cpp
	int f=c=='B';
	if(x>k)x-=k,f^=1;
	if(y>k)y-=k,f^=1;
	//如果有一方>K说明是白色，两者都>K就还是黑色，异或1将影响消除了
```
$f$表示对黑色产生贡献。

现在，我们需要统计黑色的影响，而白色的应该消去

仿照着二维差分的做法，我们这样做：
```cpp
	if(f)a[1][1]++,a[x][1]--,a[1][y]--,a[x][y]+=2;
	else a[1][y]++,a[x][1]++,a[x][y]-=2;
```
如果对其进行前缀和，样子大概是这样的：

对于黑色$4$ $5$

$1$ $1$ $1$ $1$ $0$ $0$ $0$ $0$

$1$ $1$ $1$ $1$ $0$ $0$ $0$ $0$

$1$ $1$ $1$ $1$ $0$ $0$ $0$ $0$

$0$ $0$ $0$ $0$ $1$ $1$ $1$ $1$

$0$ $0$ $0$ $0$ $1$ $1$ $1$ $1$

$0$ $0$ $0$ $0$ $1$ $1$ $1$ $1$

对于白色$4$ $5$

$0$ $0$ $0$ $0$ $1$ $1$ $1$ $1$

$0$ $0$ $0$ $0$ $1$ $1$ $1$ $1$

$0$ $0$ $0$ $0$ $1$ $1$ $1$ $1$

$1$ $1$ $1$ $1$ $0$ $0$ $0$ $0$

$1$ $1$ $1$ $1$ $0$ $0$ $0$ $0$

$1$ $1$ $1$ $1$ $0$ $0$ $0$ $0$

我们可以发现，白色对$(x,y)$位置以内和以外是没有影响的，可是它的上下两个区域还是可以产生影响的，而黑色恰恰相反。

这正是我们所需要的。

于是我们把每个位置都差分一下，再统计一下前缀和

这时位置上的数就表示黑色产生贡献，$N$减去它就是白色产生的贡献，遍历一遍数组，最大值即为所求。

### 代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
using namespace std;
inline int read(){//快读，很快
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch))f|=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return f?-x:x;
}
int a[1007][1007];//开K*K的数组
char c;
int main(){
	int n=read(),k=read(),ans=0;
	for(int i=0;i<n;++i){
		int x=read()%(k+k)+1,y=read()%(k+k)+1;//读入的时候取模顺便加1，方便操作
        cin>>c;//读字符从来不敢用scanf
		int f=c=='B';//f如上述，表示黑白
		if(x>k)x-=k,f^=1;
		if(y>k)y-=k,f^=1;
		if(f)a[1][1]++,a[x][1]--,a[1][y]--,a[x][y]+=2;
		else a[1][y]++,a[x][1]++,a[x][y]-=2;//类似差分的操作
	}
	for(int i=1;i<=k;++i)for(int j=1;j<=k;++j){
		a[i][j]+=a[i][j-1]+a[i-1][j]-a[i-1][j-1];//前缀和
		ans=max(ans,max(n-a[i][j],a[i][j]));//取max
	}
	printf("%d\n",ans);//输出
    return 0;//好习惯
}
```


---

## 作者：xfrvq (赞：2)

[$\tt ARC089B$](/problem/AT3876)。

讲一个像我这样的菜鸡也能在赛时想到的，思维难度极低的做法。

首先发现这个黑白交错的网格横竖都是以 $2k$ 为周期。我们大可以让每个点的 $x,y$ 坐标都对 $2k$ 取模。

然后我们枚举在 $2k\times2k$ 的平面内，横竖的分割线分别应该在哪（注意到横竖都应该有两条，但是我们枚举前面的那条可以通过 $+k$ 算出后面那条），复杂度 $O(k^2)$。

然后平面会被分割成 $3^2=9$ 块。

然后我们把输入的愿望当做点，在这 $9$ 块分别进行两种颜色分别的二维数点。

然后因为平面大小是 $(2k)^2$ 的，所以二维数点可以直接二维前缀和。

```cpp
#include<stdio.h>
#include<algorithm>

using namespace std;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)

const int N = 1e5 + 5;
const int K2 = 2e3 + 5;

int n,k,v;
int s[2][K2][K2];

int sum(int xl,int xr,int yl,int yr,int c){
	if(xl > xr || yl > yr) return 0;
	int res = s[c][xr][yr];
	if(xl) res -= s[c][xl - 1][yr];
	if(yl) res -= s[c][xr][yl - 1];
	if(xl && yl) res += s[c][xl - 1][yl - 1];
	return res;
}

int main(){
	scanf("%d%d",&n,&k);
	v = 2 * k - 1;
	rep(i,1,n){
		int x,y; char c;
		scanf("%d%d",&x,&y);
		do{ c = getchar(); } while(c < 'A' || c > 'Z');
		++s[c == 'B'][x %= (v + 1)][y %= (v + 1)];
	}
	rep(i,0,v) rep(j,0,v) rep(c,0,1){
		if(i) s[c][i][j] += s[c][i - 1][j];
		if(j) s[c][i][j] += s[c][i][j - 1];
		if(i && j) s[c][i][j] -= s[c][i - 1][j - 1];
    }
	int res = 0;
	rep(i,0,k - 1) rep(j,0,k - 1){
		int x[] = {0,i + 1,i + k + 1,v + 1};
		int y[] = {0,j + 1,j + k + 1,v + 1};
		int a0 = 0,a1 = 0;
		rep(p,0,2) rep(q,0,2){
			a0 += sum(x[p],x[p + 1] - 1,y[q],y[q + 1] - 1,(p + q) & 1);
			a1 += sum(x[p],x[p + 1] - 1,y[q],y[q + 1] - 1,(p + q + 1) & 1);
		}
		res = max({res,a0,a1});
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：Conan15 (赞：1)

水到爆了。

显然在同一个网格中，$(x,y),(x-2k,y),(x,y-2k),(x-k,y-k)$ 这些点的颜色是一致的，因此可以先把 $x,y$ 对 $2k$ 取模。\
这样无限大的网格就被压缩到了 $2k \times 2k$。

由于 $k \leq 1000$，显然可以枚举这个矩阵的左下角再统计。\
显然为了方便，可以把网格扩大到 $4k \times 4k$，即复制四遍，然后前缀和维护一个 $k \times k$ 的方格内有多少个白点或黑点。\
于是这题就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4015;
int n, k, k2;
int s[N][N][2], ans = 0;

int query(int x, int y, int xx, int yy, int l) { return s[xx][yy][l] - s[x - 1][yy][l] - s[xx][y - 1][l] + s[x - 1][y - 1][l]; }

int main() {
    scanf("%d%d", &n, &k), k2 = k * 2;
    for (int i = 1, x, y, c; i <= n; i++) {
        char opt; scanf("\n %d%d %c", &x, &y, &opt);
        c = (opt == 'B');
        x = x % k2 + 1, y = y % k2 + 1;
        s[x][y][c]++, s[x + k2][y][c]++, s[x][y + k2][c]++, s[x + k2][y + k2][c]++;
    }
    
    for (int l = 0; l <= 1; l++)
        for (int i = 1; i <= 4 * k; i++)
            for (int j = 1; j <= 4 * k; j++) s[i][j][l] += s[i - 1][j][l] + s[i][j - 1][l] - s[i - 1][j - 1][l];
    for (int l = 0; l <= 1; l++)
        for (int i = 1; i <= k2; i++)
            for (int j = 1; j <= k2; j++) {
                int res = 0;
                res += query(i, j, i + k - 1, j + k - 1, l);    //左下角
                res += query(i + k, j + k, i + k2 - 1, j + k2 - 1, l);    //右上角
                res += query(i + k, j, i + k2 - 1, j + k - 1, l ^ 1);   //右下角
                res += query(i, j + k, i + k - 1, j + k2 - 1, l ^ 1);
                ans = max(ans, res);
            }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：liangbowen (赞：1)

[problem](https://www.luogu.com.cn/problem/AT_arc089_b) & [blog](https://www.cnblogs.com/liangbowen/p/17599062.html)。

给一个比较暴躁的做法。

---

若要求 $(x,y)$ 的颜色为 White，等价于要求 $(x+k,y)$ 的颜色为 Black；要求 $(x,y)$ 的颜色为 Black，等价于要求 $(x\bmod 2k, y\bmod 2k)$ 为 Black。

于是将全部点以黑点的形式塞到左上角 $2k\times2k$ 矩阵里。枚举黑白的「分界线」，挨个判断每个点所在格是否为 Black，$O(nk^2)$，寄。

优化很简单啊，$2k\times2k$ 很小捏，二维前缀和直接做即可。

[代码](https://atcoder.jp/contests/abc086/submissions/44151344)，时间复杂度 $O(n+k^2)$。


---

## 作者：Erotate (赞：0)

由于矩阵是重复出现的，所以我们不妨只考察大小为 $2K \times 2K$ 矩形，然后枚举横竖的分割线在哪。

我们让每一个愿望的横纵坐标都对 $2K$ 取模，然后做一个二维前缀和。然后对于每一种分割线都进行二维数点，看有多少个点在这条分割线下满足颜色相同，取最大值即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define mk(x,y) make_pair(x,y)
using namespace std;
const int inf=0x3f3f3f3f,INF=0x3f3f3f3f3f3f3f3f;
const int N=1e5+5,K=1e3+5;
int n,k,sum[2][K<<1][K<<1],kk,ans;
int gt(int x1,int x2,int y1,int y2,int col){
	if(x1>x2 || y1>y2) return 0;
	return sum[col][x2][y2]-(x1?sum[col][x1-1][y2]:0)-(y1?sum[col][x2][y1-1]:0)+((x1 && y1)?sum[col][x1-1][y1-1]:0);
}
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    kk=(k<<1)-1;
	for(int i=1,x,y;i<=n;++i){
		char ch;
		cin>>x>>y>>ch;
		sum[ch=='W'?0:1][x%(kk+1)][y%(kk+1)]++;
	}
	for(int i=0;i<=kk;++i)
		for(int j=0;j<=kk;++j)
			for(int l=0;l<2;++l) sum[l][i][j]+=(i?sum[l][i-1][j]:0)+(j?sum[l][i][j-1]:0)-((i && j)?sum[l][i-1][j-1]:0);
	for(int i=0;i<k;++i)
		for(int j=0;j<k;++j){
			int dx[]={0,i+1,i+k+1,kk+1},dy[]={0,j+1,j+k+1,kk+1};
			int resw=0,resb=0;
			for(int c1=0;c1<3;++c1)
				for(int c2=0;c2<3;++c2){
					resw+=gt(dx[c1],dx[c1+1]-1,dy[c2],dy[c2+1]-1,c1+c2&1);
					resb+=gt(dx[c1],dx[c1+1]-1,dy[c2],dy[c2+1]-1,c1+c2+1&1);
				}
			ans=max(ans,max(resw,resb));
		}
	cout<<ans<<endl;
	return 0;
}

```


---

