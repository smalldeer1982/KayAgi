# 「Daily OI Round 3」Tower

## 题目背景

定义 $(x_1,y_1),(x_2,y_2)$ 的 `A 距离` 为 $\max\{|x_1-x_2|,|y_1-y_2|\}+1$，下文中的距离都指的是 `A 距离`。

比如说，$(1,1)$ 和 $(3,8)$ 的 `A 距离` 为 $\max\{|1-3|,|1-8|\}+1=8$。

比如说，$(46,1)$ 和 $(35,9)$ 的 `A 距离` 为 $\max\{|46-35|,|1-9|\}+1=12$。

## 题目描述

A 国的国土可以看成是 $n\times m$ 的矩阵，第 $x$ 行第 $y$ 列坐标为 $(x,y)$。

国土可以是山地，用 `#` 表示，可以是平地，用 `.` 表示。

A 国在每一个平地建了一个能量塔，能量塔搜集能量的范围是正方形的。如果 $e$ 满足到该能量塔 `A 距离` **不超过** $e$ 的地方是 A 国的国土，并且该地方是平地，则称 $e$ 是该能量塔的基准能量。

一个能量塔的综合能量 $E$ 为该能量塔基准能量 $e$ 的最大值。

特殊地，如果这个地方没有能量塔，该处综合能量 $E=0$，否则，该处的综合能量就是能量塔的综合能量。

记第 $i$ 行第 $j$ 列的综合能量为 $E_{i,j}$。

记一个国家的能量总和 $\xi=\sum\limits^n_{i=1}\sum\limits_{j=1}^mE_{i,j}^2$。

你需要求一个国家的能量总和 $\xi$。

当然，由于特殊的原因（比如宇宙射线的影响），某一个地方的平地可能会突然变成山地，当地的能量塔也会被摧毁，而且影响到附近能量塔的综合能量 $E$。

作为 A 国的参谋，国王想让你预备方案，看看每一个非山地的点变成山地之后，该国家的能量总和是多少。

## 说明/提示

#### 【样例解释 #1】

下面举 $3$ 个例子：

开始，这个国家的 $E_{i,j}$ 如下：

```
1 1 1 1 
1 2 1 0
1 1 1 1
```

$(1,1)$ 变成山地后，$E_{i,j}$ 如下：

```
0 1 1 1
1 1 1 0
1 1 1 1
```



$(3,4)$ 变成山地后，$E_{i,j}$ 如下：

```
1 1 1 1
1 2 1 0
1 1 1 0
```

#### 【数据范围】

对于全部数据保证：$1\le n,m\le600$。

## 样例 #1

### 输入

```
3 4
....
...#
....```

### 输出

```
14
10 10 10 13
10 10 10 -1
10 10 10 13```

## 样例 #2

### 输入

```
5 6
...#..
#.....
......
......
...#..```

### 输出

```
39
38 38 38 -1 38 38
-1 35 32 29 32 35
35 32 29 29 32 35
35 32 29 29 32 35
35 35 35 -1 38 38```

## 样例 #3

### 输入

```
7 7
....#..
.#.....
.......
.......
.#...##
..#####
.......```

### 输出

```
51
50 50 50 50 -1 50 50
50 -1 47 44 41 44 47
50 50 44 41 38 44 47
50 50 44 41 38 44 47
50 -1 47 47 47 -1 -1
50 50 -1 -1 -1 -1 -1
50 50 50 50 50 50 50```

# 题解

## 作者：huangrenheluogu (赞：8)

本来有个部分分的，但是因为 ACM 赛制被删掉了。

想想看，$E_{i,j}$ 比较小的时候怎么做？

一种暴力的做法是在每次询问的时候，直接枚举附近的点，看看变成山地是不是会减少那一个点的答案。

但是上面的做法显然是不可以进行拓展到 $E_{i,j}$ 很大的情况，原因在于这个点答案的改变关于其他的点，这样很难搞（或者有什么大佬有方法可以私信我）。

那么，怎么把答案汇聚到一个点上？

对于一个点 $(X,Y)$，考虑它的贡献，就是它变成山地之后的答案变化量。

它的贡献在于满足 $(i,j)$ 和 $(X,Y)$ 的 `A距离`（记为 $x$），小于等于 $E_{i,j}$ （记为 $y$）的改变的贡献总和。

看看改变了多少，对于 $(i,j)$，它的 $E$ 由 $y$ 变成了 $x$，那么就是 $y^2-x^2$。难搞。

难搞就先放一边，看看数据范围 $n,m\le600$，时限 $1$ 秒，猜猜是 $O(n^3)$ 的复杂度。~~但是好像会 TLE，不管了，直接冲冲看~~。仔细分析可以发现，同一个点对其他点产生的贡献，和 `A距离` 有关，`A距离` 一样的得到的贡献一样，`A距离` 不同的得到的贡献不同。如果我们枚举 $\sum\limits_{i=1}^n\sum\limits_{j=1}^mE_{i,j}$，因为 $E_{i,j}\le \min\{i, j,n-i+1,n-j+1\}$，所以如果对于一个点，枚举 $E_{i,j}$ 层，分层算贡献的复杂度是刚刚好的。

~~可能大家不像我这么大胆，毕竟我是知道做法的。~~

累计其他点的贡献好像不是很好做？但是，我们可以换一个方法，枚举点，给其他点统计贡献。

这样的情况下，`A距离` 为 $1$ 的点统计了 $E_{i,j}$ 次，`A距离` 为 $2$ 的点统计了 $E_{i,j}-1$ 次，发现距离越近，统计的次数越多。

那么，考虑换一个思路，如果 $(X,Y)$ 变成了山地，那么 $(i,j)$ 点的 $E$ 会减小 $x$。

$$(E'_{i,j})^2=(E_{i,j}-x)^2=E_{i,j}^2-2E_{i,j}x+x^2=E_{i,j}^2-(2E_{i,j}x-x^2)$$

答案减小了 $2E_{i,j}x-x^2$。

这个是不是很好维护。

$2E_{i,j}x$ 可以每一层都在这一层加上 $E_{i,j}$。

$-x^2$ 就是利用 $\sum\limits_{i=1}^n(2i-1)=n^2$ 一层一层解决。

这样枚举一个点是 $O(n^2)$ 的，枚举层是 $O(n)$ 的，每一层加上给定的数是 $O(n^2)$ 的，时间复杂度达到了 $O(n^5)$，预计得到 TLE。

一层一层的一个一个加有点慢，就二维差分好了。这样复杂度就是 $O(n^3)$ 了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 605;
int n, m, a[N][N], k, f, ans, x, y, b[N][N], c[N][N];
char ch;
inline void add(int x, int y, int X, int Y, int val){
	b[x][y] += val;
	b[X + 1][Y + 1] += val;
	b[x][Y + 1] -= val;
	b[X + 1][y] -= val;
}
inline int get(int x, int y, int X, int Y){
	return c[X][Y] + c[x - 1][y - 1] - c[X][y - 1] - c[x - 1][Y];
}
signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ch = getchar();
			while(ch != '.' && ch != '#') ch = getchar();
			if(ch == '#') a[i][j] = 1;
			c[i][j] = c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1] + a[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 1) continue ;
			for(k = 1; ; k++){
				if(i - k < 1 || i + k > n || j - k < 1 || j + k > m) break;
				if(get(i - k, j - k, i + k, j + k)) break ;
			}
			ans += k * k;
			x = k;
			for(k = 0; k < x; k++){
				//x ^ 2 - (x - y) ^ 2 = 2xy - y ^ 2;
				add(i - k, j - k, i + k, j + k, 2 * x);
				add(i - k, j - k, i + k, j + k, -(2 * (x - k) - 1));
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
		}
	}
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 1) printf("-1 ");
			else printf("%lld ", ans - b[i][j]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：5)

没看懂官方题解。

下文 $n,m$ 同阶。

第一问枚举 $(x,y)$ 二分 $E_{x,y}$ 然后前缀和优化 check 即可做到 $O(n^2\log n)$。

考虑暴力怎么做：枚举 $(i,j)$，再枚举 $(x,y)$，统计删 $(i,j)$ 对 $E_{x,y}$ 的影响。

这样暴力做好像不大能优化，把贡献拆掉：枚举 $(x,y)$，对于每个 $(i,j)$ 统计删去 $(i,j)$ 对 $E_{x,y}$ 的影响，将影响挂在 $(i,j)$ 上。

这个好做。考虑对 $E_{x,y}$ 有贡献的最大全 $1$ 方形，将其中元素按和 $(x,y)$ 的曼哈顿距离分组，每组贡献相同。

每组可以拆成 $O(1)$ 个矩形，用二维差分维护矩形加，单点求值，即可做到 $O(n^3)$。

```cpp
il void Solve()
{
  int n,m;rd(n),rd(m);
  ve<ve<int>>mp(n,ve<int>(m)),a=mp,E=a;
  for(int i=0;i<n;++i) {
    string s;rd(s);
    for(int j=0;j<m;++j) {
      mp[i][j]=a[i][j]=s[j]=='.';
      if(i) a[i][j]+=a[i-1][j];
      if(j) a[i][j]+=a[i][j-1];
      if(i&&j) a[i][j]-=a[i-1][j-1];
    }
  }
  auto F=[&](int x){return x*x;};
  LL s=0;
  ve<ve<LL>>b(n,ve<LL>(m));
  auto _M=[&](int x,int y,int xx,int yy,int w)
  {
    b[x][y]+=w;
    if(xx+1<n) b[xx+1][y]-=w;
    if(yy+1<m) b[x][yy+1]-=w;
    if(xx+1<n&&yy+1<m) b[xx+1][yy+1]+=w;
  };
  for(int i=0;i<n;++i) for(int j=0;j<m;++j) if(mp[i][j]) {
    int e=[&]
    {
      int l=0,r=min(n,m);
      auto S=[&](int x,int y,int xx,int yy)
      {
        int s=a[xx][yy];
        if(x) s-=a[x-1][yy];
        if(y) s-=a[xx][y-1];
        if(x&&y) s+=a[x-1][y-1];
        return s;
      };
      auto chk=[&](int k)
      {
        if(i-k<0||i+k>=n||j-k<0||j+k>=m) return false;
        return S(i-k,j-k,i+k,j+k)==F(k*2+1);
      };
      for(int mid;l<r;) chk(mid=l+r+1>>1)?l=mid:r=mid-1;
      return l;
    }()+1;
    s+=E[i][j]=F(e);
    for(;--e;) {
      int w=-E[i][j]+F(e);
      _M(i-e,j-e,i-e,j+e-1,w);
      _M(i-e,j+e,i+e-1,j+e,w);
      _M(i+e,j-e+1,i+e,j+e,w);
      _M(i-e+1,j-e,i+e,j-e,w);
    }
  }
  for(int i=0;i<n;++i) for(int j=0;j<m;++j) {
    if(i) b[i][j]+=b[i-1][j];
    if(j) b[i][j]+=b[i][j-1];
    if(i&&j) b[i][j]-=b[i-1][j-1];
  }
  wrt(s,'\n');
  for(int i=0;i<n;++i) for(int j=0;j<m;++j) wrt(mp[i][j]?s+b[i][j]-E[i][j]:-1," \n"[j==m-1]);
  return;
}
```

[$\color{green}{\checkmark}$](https://www.luogu.com.cn/record/149648135)

---

## 作者：wxzzzz (赞：4)

### 题意

一个正方形的边长为 $x$，定义它的半径为 $\lceil\dfrac{x}{2}\rceil$。

给定一张平面图，$\tt \#$ 表示空点。

点 $(i,j)$ 的能量为以这个点为中心的最大完整正方形的半径 $e_{i,j}$。

能量总和为 $\displaystyle\sum_{i=1}^n\sum_{j=1}^m {e_{i,j}}^2$。

求将 $(i,j)$ 删掉后的能量总和。

### 思路

最初的能量总和很好求，以每个点为中心二分半径即可求出 $e_{i,j}$。

难点在于求每个点删掉后的能量总和。

考虑求出每个点对能量总和产生的贡献。

可以在求 $e_{i,j}$ 是顺带求出。

对于某个点 $(i,j)$，以它为中心的最大完整正方形半径为 $e_{i,j}$，定义这个正方形有 $e_{i,j}$ 层，每一层都是一个比上一层刚好小一个点的正方环。

第 $k$ 层上的任一点被删掉后，以 $(i,j)$ 为中心的正方形半径减少了 $e_{i,j}-(k-1)$，能量总和减少了 ${e_{i,j}}^2-(k-1)^2$，于是将第 $k$ 层上的每个点的贡献累加 ${e_{i,j}}^2-(k-1)^2$，可用二维差分维护。

对每个正方形的每一层累加贡献，就得到了每个点的贡献，每个点的答案就是能量总和减去它的贡献。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
long long sum, c[605][605], e[605][605], s[605][605];
char g[605][605];
long long getsum(int x, int xx, int y, int yy) {
    return s[xx][yy] - s[x - 1][yy] - s[xx][y - 1] + s[x - 1][y - 1];
}
void change(int x, int xx, int y, int yy, int k) {
    c[x][y] += k;
    c[x][yy + 1] -= k;
    c[xx + 1][y] -= k;
    c[xx + 1][yy + 1] += k;
}
int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        scanf("%s", g[i] + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];

            if (g[i][j] == '#')
                s[i][j]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == '#')
                continue;

            int l = 1, r = min(min(i, n - i + 1), min(j, m - j + 1)), mid;

            while (l <= r) {
                mid = l + r >> 1;

                if (!getsum(i - mid + 1, i + mid - 1, j - mid + 1, j + mid - 1))
                    e[i][j] = mid, l = mid + 1;
                else
                    r = mid - 1;
            }

            sum += e[i][j] * e[i][j];

            for (int k = e[i][j]; k >= 2; k--) {
                change(i - k + 1, i + k - 1, j - k + 1, j + k - 1, e[i][j]*e[i][j] - (k - 1) * (k - 1));
                change(i - (k - 1) + 1, i + (k - 1) - 1, j - (k - 1) + 1, j + (k - 1) - 1, (k - 1) * (k - 1) - e[i][j]*e[i][j]);
            }

            change(i, i, j, j, e[i][j]*e[i][j]);
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            c[i][j] += c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];

    cout << sum << '\n';

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == '#')
                cout << "-1 ";
            else
                cout << sum - c[i][j] << ' ';
        }

        cout << '\n';
    }

    return 0;
}
```

---

## 作者：Coffins (赞：2)

首先考虑若地图确定，如何求出 $E_{i,j}$。

可以从小到大枚举答案 （假设当前为 $k$），先判越界，然后判断 $[i-k+1,i+k-1]\times[j-k+1,j+k-1]$ 这个范围内是否有障碍。

前者可以直接判，后者做一个前缀和可以 $O(n^2)$ 预处理 $O(1)$ 查询，再算上枚举答案的复杂度，于是每个点可以 $O(n)$ 求得答案。

然后我们就先把原图的 $E_{i,j}$ 都算出来，这样第一问就解决了。

然后对于第二问，考虑对于每一个点 $A$ 计算它在其他点（这里设为 $B$）变成障碍时对这个点的贡献。

当 $dis(A,B)\gt E_A$ 时，显然 $B$ 变成什么牛鬼蛇神都对 $A$ 毫无影响，那么 $A$ 对于这些点的贡献就是 $E_A^2$；

当 $dis(A,B)\le E_A$ 时，设 $dis(A,B)=k$，那么 $B$ 点变为障碍后  $E_A$ 就减小为 $k-1$ 了，于是 $A$ 对于这些点贡献为 $(k-1)^2$。

考虑到满足 $dis(A,B)\le k$ 的点 $B$ 组成的集合为 $[A_i-k+1,A_i+k-1]\times[A_j-k+1,A_j+k-1]$，于是我们可以得到如下算法流程：

首先枚举点 $A$，然后首先把每个点的答案都加上 $E_A^2$，然后从 $E_A$ 到 $1$ 枚举一个 $k$，每次把 $[i-k+1,i+k-1]\times[j-k+1,j+k-1]$ 这些点都减去 $k^2-(k-1)^2=2k-1$ （也就是把当前点对其的贡献从 $k^2$ 变成 $(k-1)^2$），这样的话最后点 $A$ 对于每个点的贡献就都正好处理好了。

最后考虑复杂度。

第一部分就是 $O(n^3)$，第二部分需要一个二维区间加，不过由于只有最终需要查询每一个点的值，所以可以差分一下，最后再前缀和推回来，总复杂度也是 $O(n^3)$，所以最终复杂度为 $O(n^3)$。

[丑陋的代码](https://www.luogu.com.cn/paste/9h3dau11)

---

## 作者：Cure_Wing (赞：1)

[P10127 「Daily OI Round 3」Tower](https://www.luogu.com.cn/problem/P10127)

力的作用是相互的。

### 思路

我们先求最初的能量之和。

因为能量塔搜集的范围是正方形的，又要求最大值，我们会想到二分。很显然，$e$ 越小，越能够搜集能量。因此我们枚举每个点，暴力二分综合能量大小，然后我们检查一下此时能量塔搜集的范围是否有山地即可。检查是否有山地，我们可以把平地和山地标为 $0$ 和 $1$，然后做一个前缀和，如果检查出对应的正方形内和为 $0$ 那就是合法的。

接下来我们想一块平地变为山地会对能量总和如何影响。如果直接做，我们需要计算出这一次变化会对那些平地造成影响，显然需要枚举每一块平地，直接爆炸。但是反过来思考，让这一块平地的能量值减小一定的值，需要在那些地方放山地。容易看出，如果想让一座能量塔的总和能量减少 $E^2-(E-k)^2$，那么需要在离该能量塔 `A距离` 为 $E-k+1$ 的一圈放任意一块山地。而我们暴力更新和的话又会起飞，考虑差分，我们可以让距离该能量塔 `A距离` 小于或等于 $E-k+1$ 的区域全部加上 $(E-k+1)^2-(E-k)^2=2(E-k)+1$，那么加和的时候所得到的值就是我们一开始期望的值了。

时间复杂度有一点紧，大约是 $O(nm(\log\min\{n,m\}+\min\{n,m\}))$，但是常数极小，而且很多点取不到上限，所以跑起来特别优秀。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=606;
int n,m,b[N][N];
long long ans,c[N][N];
bool a[N][N];
std::string s;
signed main(){
	// freopen("a.in","r",stdin);
	// freopen("a.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>s;
        for(int j=1;j<=m;++j){
            b[i][j]=a[i][j]=(s[j-1]=='#');//前缀和判定
            b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
        }
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            if(a[i][j]) continue;
            int l=1,r=std::min(n,m);
            while(l<=r){
                int mid=(l+r)>>1;
                if(i+mid-1<=n&&j+mid-1<=m&&i-mid>=0&&j-mid>=0&&b[i+mid-1][j+mid-1]-b[i-mid][j+mid-1]-b[i+mid-1][j-mid]+b[i-mid][j-mid]==0) l=mid+1;
                else r=mid-1;
            }//二分最大能量值
            ans+=r*r;
            for(int k=r;k>=1;--k){
                int x=2*k-1;
                c[i-k+1][j-k+1]-=x;c[i-k+1][j+k]+=x;
                c[i+k][j-k+1]+=x;c[i+k][j+k]-=x;
            }//差分（这里维护负值）
        }
    cout<<ans<<'\n';
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
            cout<<(a[i][j]?-1:ans+c[i][j])<<(j==m?'\n':' ');
        }
    return 0;
}
```

---

## 作者：39xiemy (赞：0)

## 题目大意

给定一个 $n \times m$ 大小的由 `.` 和 `#` 所组成的矩形 $C$。对于每个位于第 $i$ 行第 $j$ 列的 `.`，找出一个 $k$ 最大的，边长为 $2 \times k -1$ 的正方形，满足其所有字符都为 `.` 且不超出矩阵，定义 $E_{i,j}$ 为上文的 $k$。

求 $\sum^n_{i=1} \sum_{j=1}^m E_{i,j}^2$ 的值。

此外，对于这个矩形的第 $i$ 行第 $j$ 列，若 $C_{i,j}$ 为 `.`，将 $C_{i,j}$ 改为 `#`，重新计算 $\sum^n_{i=1} \sum_{j=1}^m E_{i,j}^2$ 的值，否则输出 $-1$。每次修改互不影响。

## 分析

令 `.` 为 $1$，`#` 为 $0$。

则矩形 $C$ 变成了一个 $01$ 矩阵，要对每个点求出一个最大的 $k$，使得其中的所有数字都为 $1$。对于这种问题，显然可以对每个点枚举 $k$，然后用二维前缀和来判断包含的数字是否全为 $1$。这样就可以得到没有修改时的答案。

当有修改时，肯定不能将上述方法重复 $n \times m$ 遍，这样做的时间复杂度为 $O(n^2m^2)$。

可以考虑将每个为 $1$ 的点对答案的贡献通过二维差分存储下来。具体来说，在第一步对每个点枚举 $k$ 时，每枚举到一个 $k$ 值，就将当前的正方形中的所有点，通过二维差分的方式把贡献加上 $k^2-(k-1)^2$。

例如，当 $k$ 枚举到 $3$ 时，正方形中首次包含点 $C_{i,j}$，那么点 $C_{i,j}$ 对答案的贡献即为 $k^2-(3-1)^2$。这是因为当点 $C_{i,j}$ 变为 $0$ 时，$k$ 的值将变为 $2$，答案就会减少 $k^2-(3-1)^2$。

最后将二维差分数组还原，对于每次对点 $C_{i,j}$ 的修改，答案即为没有修改时的答案减去点 $C_{i,j}$ 的贡献。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,s[605][605],b[605][605],ans,t,a[605][605],k;
char c;
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			cin>>c,a[i][j]=(c=='.');
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];//二维前缀和计算
		}
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			for(k=0,t=1;s[i+k][j+k]-s[i-k-1][j+k]-s[i+k][j-k-1]+s[i-k-1][j-k-1]==4*k*k+4*k+1;k++,t+=2)
			{
				b[i-k][j-k]+=t,b[i-k][j+k+1]-=t,b[i+k+1][j-k]-=t,b[i+k+1][j+k+1]+=t;
				//在计算正方形的大小时，将k^2-(k-1)^2加入二维差分数组中
			}
			ans+=k*k; 
		}
	}
	cout<<ans<<'\n';
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];//将差分数组还原
			if(!a[i][j])
			{
				printf("-1 ");
				continue;
			}
			printf("%lld ",ans-b[i][j]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：modfish_ (赞：0)

## 思路
这题显然分为两个步骤，求出 $\xi$ 和求出所有 $\xi_{i,j}$。

对于第一步，我们可以求出每一个格子的 $E_{i,j}$。怎么求呢？一个很自然的想法是标记每一个障碍，然后对于每一个非障碍格子，一层层遍历围着它的一个正方形环，直到环上存在标记。在一开始写的时候，我想当然地用了树状数组：维护每一行和每一列上的标记即可。但是这样就是 $O(n^3\log n)$ 的了，过不去。

但是，我们很容易发现：这并不是一个实时询问的问题，而是先操作后查询，我们可以用前缀和数组达到相同的目的：维护每行每列的标记的前缀和，每次打标记时，直接 $O(n)$ 修改，查询就可以 $O(1)$ 了。这样可以 $O(n^3)$ 完成 $\xi$ 的求解。

对于第二步，正着直接模拟每一个平地变为山地的影响是不现实的。我们可以反着来：对于每一个平地，将所有会影响其 $E$ 值的格子加上一个权值，这个权值即为影响大小。例如：原本 $E_{i,j}=5$，在对某个格子进行修改后 $E_{i,j}$ 变成了 $3$，则影响大小为 $5^2-3^2=16$。

这样，每一个格子上的权值即为将它修改后产生的影响。

这一步求解，先进行区间修改，再进行单点查询，可以用差分数组维护：维护每行每列的权值的差分数组，修改直接 $O(1)$ 改，查询 $O(n)$ 查，复杂度为 $O(n^3)$。

这样，我们就以 $O(n^3)$ 的时间复杂度通过了这题。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 605;

char ch[maxn][maxn];
int e[maxn][maxn], d1[maxn][maxn], d2[maxn][maxn], s1[maxn][maxn], s2[maxn][maxn];

signed main(){
	int n, m;
	scanf("%lld %lld", &n, &m);
	for(int i = 1; i <= n; i ++){
		scanf("%s", ch[i] + 1);
		for(int j = 1; j <= m; j ++){
			if(ch[i][j] == '#'){
				for(int k = j; k <= m; k ++) s1[i][k] ++;
				for(int k = i; k <= n; k ++) s2[j][k] ++;
			}
		}
	}
	int E = 0;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			if(ch[i][j] == '#') continue;
			for(int mid = 1; i - mid + 1 >= 1 && j - mid + 1 >= 1 && i + mid - 1 <= n && j + mid - 1 <= m; mid ++){
				int up = s1[i - mid + 1][j + mid - 1] - s1[i - mid + 1][j - mid];
				int dn = s1[i + mid - 1][j + mid - 1] - s1[i + mid - 1][j - mid];
				int le = s2[j - mid + 1][i + mid - 1] - s2[j - mid + 1][i - mid];
				int ri = s2[j + mid - 1][i + mid - 1] - s2[j + mid - 1][i - mid];
				if(up + dn + le + ri > 0) break;
				e[i][j] = mid;
			}
			E += e[i][j] * e[i][j];
		}
	}
	printf("%lld\n", E);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			for(int k = 1; k <= e[i][j]; k ++){
				int cost = e[i][j] * e[i][j] - (k - 1) * (k - 1);
				if(k == 1){
					d1[i][j] += cost;
					d1[i][j + 1] += -cost;
					continue;
				}
				d1[i - k + 1][j - k + 1] += cost;
				d1[i - k + 1][j + k] += -cost;
				d1[i + k - 1][j - k + 1] += cost;
				d1[i + k - 1][j + k] += -cost;
				d2[j - k + 1][i - k + 2] += cost;
				d2[j - k + 1][i + k - 1] += -cost;
				d2[j + k - 1][i - k + 2] += cost;
				d2[j + k - 1][i + k - 1] += -cost;
			}
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			if(ch[i][j] == '#') printf("-1");
			else{
				int met = 0;
				for(int k = 1; k <= j; k ++) met += d1[i][k];
				for(int k = 1; k <= i; k ++) met += d2[j][k];
				printf("%lld", E - met);
			}
			if(j < m) printf(" ");
		}
		if(i < n) printf("\n");
	}
	return 0;
}
```


---

## 作者：_zuoqingyuan (赞：0)

[传送门。](https://www.luogu.com.cn/problem/P10127)

# 题意简述：
有一个大小为 $n\times m$ 的二维 $01$ 矩阵 $a$。对于矩阵的任意一个位置 $a_{i,j}$。其贡献 $E_{i,j}$ 的定义为最小的 $k$。使得以 $(i,j)$ 为中心点，$2\times k-1$ 为边长的正方形不超过边界，且其范围内不存在 $a_{x,y}=1$。

定义矩阵 $a$ 的总贡献 $e=\sum\limits_{i=1}^n\sum\limits_{j=1}^m E_{i,j}$。你需要求出当 $a_{i,j}$ 从 $0$ 变到 $1$ 后 $e$ 的值以及 $e$ 原本的值。特殊的，如果 $a_{i,j}=1$。则输出 $-1$。
# 思路分析
有一个很朴素的思想。就是枚举每一个位置 $(x,y)$。表示将 $a_{x,y}$ 变为 $1$。然后枚举每一个位置 $(i,j)$，计算 $E_{i,j}$ 的值然后累加。对于计算 $E(i,j)$。我们再次枚举点 $(a,b)$。计算其是否是可能是 $E_{i,j}$。每一种枚举的时间复杂度都是 $O(n^2)$ 这样的算法总时间复杂度达到了惊人的 $O(n^6)$。考虑优化。

我们要思考一个问题。对于一个位置 $(i,j)$ 我们要让那些 $a_{x,y}=1$。使其会影响 $E_{i,j}$ 的值。显然，只有在它所覆盖的正方形的范围内，才会影响 $E_{i,j}$。举个例子：
```
原矩阵 
0 0 0
0 0 1
0 0 0
E矩阵
1 1 1
1 1 0
1 1 1
```
对于上面例子中的 $(2,2)$，除非在 $(2,2)$ 处发生改变，才会影响 $E_{i,j}$ 的取值。所以我们考虑计算矩阵 $c$。$c_{i,j}$ 表示让 $a_{i,j}=1$ 后对原本 $e$ 的影响，我们计算出每一个点的 $E_{i,j}$ 后，就可以对中间部分一层层累加。最后答案减去 $c_{i,j}$ 就是所求。

但修改仍然是 $O(n^2)$ 的。我们可以用二维差分优化。能想到二维差分。自然就可以想到二维前缀和计算 $E_{i,j}$。具体的在我代码里。

# Code
```cpp
#include <iostream>
#define int long long
using namespace std;
const int N=605;
int n,m,a[N][N],b[N][N],c[N][N],ans;
char ch;
inline int ask(int x1,int y1,int x2,int y2){
    return b[x2][y2]-b[x1-1][y2]-b[x2][y1-1]+b[x1-1][y1-1];
}
inline void add(int x1,int y1,int x2,int y2,int t){
    c[x1][y1]+=t,c[x2+1][y1]-=t,c[x1][y2+1]-=t,c[x2+1][y2+1]+=t;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>ch;
            if(ch=='#')a[i][j]=1;
            b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1,k;j<=m;j++){
            if(a[i][j])continue;
            for(k=0;;k++){
                if(i-k<1||i+k>n||j-k<1||j+k>m)break;
                if(ask(i-k,j-k,i+k,j+k))break;
            }
            ans+=k*k;k--;
            for(k;k>=0;k--)add(i-k,j-k,i+k,j+k,2*k+1);
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            c[i][j]=c[i-1][j]+c[i][j-1]-c[i-1][j-1]+c[i][j];
            if(a[i][j]==1)cout<<"-1"<<" ";
            else cout<<ans-c[i][j]<<" ";
        }
        cout<<'\n';
    }
    return 0;
}

```
如有错误请指出。

---

## 作者：LOvO (赞：0)

# 「Daily OI Round 3」Tower 题解

## 题意简述：

给你一个 $n\times m$ 的仅包含 `#` 与 `.` 的矩阵 $a$，定义点 $a_{i,j}$ 的能量 $E_{i,j}$ 为最大的 $e^2$，使得以 $(i,j)$ 为中心，边长为 $2e-1$ 的正方形仅包含字符 `.`。

你要求出一开始的 $\sum_{i=1}^n\sum_{j=1}^m E_{i,j}$ 与在每一个点 $(i,j)$ 变为 `#` 后的 $\sum_{i=1}^n\sum_{j=1}^m E_{i,j}$。

## 解题思路：

### 任务一：求最开始的能量总和。

考虑二分 $e$。

$e$ 明显具有单调性，可以二分。

对于点 $(i,j)$，若以点 $(i,j)$ 为中心，$2e+1$ 为边长的正方形中仅包含 `.`，那么这个 $e$ 可以取到，反之不行。

这可以用二维前缀和维护。

这样就可以求出最初的能量总和，时间复杂度 $O(n^2\log n)$。

### 任务二：求把某一平地变为山地后的能量总和。

直接枚举每一个点，把该点变为山地后再用任务一的方法去求是不行的，会喜提 TLE。

所以可以考虑当一个点 $(i,j)$ 变为山地后，该点对总答案的影响。

而这个影响，可以在任务一二分最大的 $e$ 值时处理：

对于一个点 $(i,j)$，它的能量值会被中心为 $(i,j)$，边长为 $2e+1$ 的正方形内的所有点影响。

这个影响有大有小，在这个正方形中，最外圈的数字影响最小，中心的影响最大，具体的，对于每一个到中心的 `A 距离` 小于等于 $e$ 的点 $(x,y)$，设它到中心的 `A 距离` 为 $z$，它的影响为 $e^2-z^2$，也就是说，对于每个这样的点，都会让最后的总答案减少 $z^2-e^2$。

而对于一些到中心的 `A 距离` 相等且小于等于 $e$ 的点，它对答案的影响是相同的，所以我们可以用二维差分记录影响。

记录影响时，我们要枚举每个小于 $e$ 的整数，所以，时间复杂度为 $O(en\log n)$，最大的一个点跑了 70 ms。

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char a[605][605];
int q[605][605], num[605][605], diff[605][605];
int n, m;
bool check(int r, int i, int j) {
	int x = i - r + 1, y = j - r + 1, xx = i + r - 1, yy = r + j - 1, len = 2 * r - 1;
	if (x > n || xx > n || y > m || yy > m) return false;	//如果越界，就返回。
	if (len * len == q[xx][yy] - q[x - 1][yy] - q[xx][y - 1] + q[x - 1][y - 1]) return true;
	return false;
}					//二分答案的判断
void add(int x, int y, int xx, int yy, int p) {
	diff[xx + 1][yy + 1] += p, diff[x][y] += p;
	diff[xx + 1][y] -= p, diff[x][yy + 1] -= p;
}					//差分
signed main() {
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1;i <= n; i++)
		for(int j = 1; j <= m; j++) {
			while (a[i][j] != '.' && a[i][j] != '#') a[i][j] = getchar();
			q[i][j] = q[i - 1][j] + q[i][j - 1] - q[i - 1][j - 1] + (a[i][j] == '.'?1:0);
		}
	int sum = 0;//sum 为原本的能量总和。
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if(a[i][j] == '#') continue;
			int l = 1, r = max(i - 1, max(j - 1, max(n - i + 1, m - j + 1)));
			while (r > l) {
				int mid = (l + r + 1) >> 1;
				if(check(mid, i, j)) l = mid;
				else r = mid - 1;
			}
			sum += r * r;
			for (int k = r, g = 1; k >= 1; k--, g++) {
				int p = r * r - (r - g) * (r - g);
           			//p 为对答案的影响，是原本的能量值减现在的能量值，表示若这些点变成山地，该点能量值会减少多少。
				int x = i - k + 1, y = j - k + 1, xx = i + k - 1, yy = j + k - 1;
				if (x != xx || y != yy) {
                  			//如果不是中心，则要将这一圈单独计算。
					add(x, y, xx - 1, y, p);
					add(xx, y, xx, yy - 1, p);
					add(x, y + 1, x, yy, p);
					add(x + 1, yy, xx, yy, p);
				}
				else add(x, y, xx, yy, p);//是中心，直接加。
			}
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			num[i][j] = num[i][j - 1] + num[i - 1][j] - num[i - 1][j - 1] + diff[i][j];//统计答案
	cout << sum << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if(a[i][j] == '#') cout << -1 << " ";
			else cout << sum-num[i][j] << " ";
		}
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：I_will_AKIOI (赞：0)

二维前缀和差分好题。场切一道上位绿，必须写篇题解纪念一下。

题目有定义了一个 A 距离，我们看看是啥意思。翻译一下就是求两点坐标差的最大值 $+1$。给定一个点，哪些点到该点的 $A$ 距离不超过 $e$ 呢？给定的点为中心，方格内的数字表示到给定点的 A 距离，方格外的数字表示坐标，设此时 $e=3$，枚举画图一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/oroxg4u0.png)

我们发现其实就是一个边长为 $2e-1$ 的正方形而已。

接下来枚举每个点，如果是空地则继续枚举。设置一个变量 $k$，枚举能量塔的基准能量。得到正方形的左上角、右下角坐标：$x1=x-k+1,y1=y-k+1,x2=x+k-1,y2=y+k-1$。如果这四个点没有超过边界，枚举判断正方形内是否全部是空地，是的话就继续枚举。直到不符合要求，就得到了这个点的综合能量。想想也知道，这复杂度根本承受不起啊！

我们将空地用 $1$ 表示，山地用 $0$ 表示。如果全是空地，则这个正方形的和一定是他的面积 $s$。就可以用二维前缀和维护啦。

但是，题目还没有结束，还有第二部分等着你解决。将每个空地变为山地，求这个国家的能量总和。

同样的，暴力就是枚举每个点，变为山地，再继续枚举，复杂度 $O(n^2m^2)$，根据数据范围，推断复杂度应为 $O(n^3)$，得优化。

首先考虑修改一个点对总答案的贡献，但是你得枚举全部点看看答案的变化，是行不通的。所以我们反过来，考虑这个点会被哪些点的修改所影响。设 $(i,j)$ 的综合能量为 $val_{i,j}$。根据上图，可知 $(i,j)$ 仅会被到 $(i,j)$ 的 A 距离不超过 $vai_{i,j}$ 的点影响。同样设置变量 $k$ 开始枚举。被影响后，该点的综合能量会变为 $k-1$。根据能量综合计算公式，得出答案会减少 $val^2_{i,j}-(k-1)^2$。

这样去掉一个点，这个点的综合能量就会变为上图所对应的值。有没有发现，综合能量的排列很像一个空心正方形，所以用差分修改四条边就行了。注意当 $k=1$ 时要特判，因为他的边是一个点。

最后给差分数组做一次前缀和，就得到修改一个点对总答案的影响。最后只要用第一小问的答案减去他即可。

注意这里得开 ```long long```。

```
#include<iostream>
#define int long long
#define N 605
using namespace std;
int n,m,sum,a[N][N],b[N][N],cnt[N][N],val[N][N];
char c;
int query(int x1,int y1,int x2,int y2){return b[x2][y2]+b[x1-1][y1-1]-b[x1-1][y2]-b[x2][y1-1];}//查询区间和
void update(int x1,int y1,int x2,int y2,int s)
{
  cnt[x1][y1]+=s;
  cnt[x2+1][y1]-=s;
  cnt[x1][y2+1]-=s;
  cnt[x2+1][y2+1]+=s;
  return;
}//差分
signed main()
{
  ios::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=1;i<=n;i++)
  {
  	for(int j=1;j<=m;j++)
  	{
  	  cin>>c;
  	  a[i][j]=(c=='.');
	  b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
	}
  }
  for(int i=1;i<=n;i++)
  {
  	for(int j=1;j<=m;j++)
  	{
  	  int k=1;
  	  while(1)
  	  {
  	  	int x1=i-k+1,y1=j-k+1,x2=i+k-1,y2=j+k-1;//正方形的端点 
  	  	if(x1<1||y1<1||x2>n||y2>m||query(x1,y1,x2,y2)<(k*2-1)*(k*2-1))
		{
		  val[i][j]=k-1;
		  sum+=val[i][j]*val[i][j];
		  break;
		}//越界了，得到综合能量
  	  	k++;
	  }
	}
  }
  for(int i=1;i<=n;i++)
  {
  	for(int j=1;j<=m;j++)
  	{
  	  int k=1;
  	  for(int k=1;k<=val[i][j];k++)
  	  {
  	    int times=val[i][j]*val[i][j]-(k-1)*(k-1);//先计算贡献，减少时间
  	  	if(k==1) update(i,j,i,j,times);//特判
  	  	else
  	  	{
  	  	  int x1=i-k+1,y1=j-k+1,x2=i+k-1,y2=j+k-1;
  	  	  update(x1,y1+1,x1,y2,times);
  	  	  update(x1+1,y2,x2,y2,times);
  	  	  update(x2,y1,x2,y2-1,times);
  	  	  update(x1,y1,x2-1,y1,times);
          //修改四条边
		}
	  }
	}
  }
  for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cnt[i][j]+=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];//给差分数组做前缀和
  cout<<sum<<"\n";
  for(int i=1;i<=n;i++)
  {
  	for(int j=1;j<=m;j++) cout<<((a[i][j]==0)?-1:(sum-cnt[i][j]))<<" ";
  	cout<<"\n";
    //输出第一小问答案减去对答案的影响
  }
  return 0;
}
```

---

## 作者：寄风 (赞：0)

神秘题。

第一问是好算的，我们对于每一个可能建立能量塔的位置，去二分它的综合能量，用二维前缀和来 `check `。

但是第二问如果直接去模拟的话是 $O(n^2m^2)$ 的，不能通过。

我们发现他每次修改都只会修改一个点，所以我们考虑算出这个点的贡献，然后用总贡献减去这个贡献。

不难发现，对于一个综合能量为 $E$ 的能量塔，所有在它探测范围内的点如果变成了山地，那么这个能量塔的范围就要变成 $E-1$。

然后根据平方差，我们知道所有在它探测范围内的点的贡献都要加上 $E^2-(E-1)^2=2E-1$。

但是这个范围操作就很不好搞，但是我们是在所有修改后都查询。

于是上二维差分即可。

实现时注意细节。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , m;
char c[1005][1005];
int cost[1005][1005] , sum[1005][1005] , cnt[1005][1005];
inline int getcost(int x1 , int y1 , int x2 , int y2){
    return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}
int diff[1005][1005];
signed main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> c[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (c[i][j] == '.');
        }
    }
    for(int x = 1;x <= n;x++){
        for(int y = 1;y <= m;y++){
            if(c[x][y] == '#'){
                continue;
            }
            int l = 1 , r = min({x , y , n - x + 1 , m - y + 1}) , dw = 0;
            while(l <= r){
                int mid = l + r >> 1;
                bool fg = 0;
                int now = mid - 1;
                if(getcost(x - now , y - now , x + now , y + now) == 4 * now * now + 4 * now + 1) fg = 1;
                if(fg){
                    dw = mid;
                    l = mid + 1;
                }
                else{
                    r = mid - 1;
                }
            }
            cost[x][y] = dw;
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(c[i][j] == '#') continue;
            int noww = cost[i][j] - 1 , now = cost[i][j];
            for(;noww >= 0;noww-- , now--){
                int x1 = i - noww , y1 = j - noww , x2 = i + noww , y2 = j + noww;
                int nw = 2 * now - 1;
                diff[x1][y1] += nw;
                diff[x2 + 1][y2 + 1] += nw;
                diff[x1][y2 + 1] -= nw;
                diff[x2 + 1][y1] -= nw;
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(c[i][j] != '#')
            ans += cost[i][j] * cost[i][j];
        }
    }
    cout << ans << endl;
    memset(sum , 0 , sizeof(sum));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + diff[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(c[i][j] == '#'){
                cout << -1;
                if(j < m) cout << ' ';
                continue;
            }
            cout << ans - sum[i][j];
            if(j < m) cout << ' ';
        }
        if(i < n) puts("");
    }
}
```

---

