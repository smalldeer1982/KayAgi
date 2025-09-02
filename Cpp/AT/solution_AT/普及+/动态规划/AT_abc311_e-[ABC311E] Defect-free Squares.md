# [ABC311E] Defect-free Squares

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc311/tasks/abc311_e

縦 $ H $ 行, 横 $ W $ 列のグリッドがあります。グリッドの上から $ i $ 行目, 左から $ j $ 列目のマスを $ (i,\ j) $ と呼びます。  
 グリッドの各マスは穴の空いたマスとそうでないマスのどちらかです。穴が空いたマスは $ (a_1,\ b_1),\ (a_2,\ b_2),\ \dots,\ (a_N,\ b_N) $ のちょうど $ N $ マスです。

正整数の組 $ (i,\ j,\ n) $ が次の条件を満たすとき、$ (i,\ j) $ を左上隅, $ (i\ +\ n\ -\ 1,\ j\ +\ n\ -\ 1) $ を右下隅とする正方形領域を **穴のない正方形** と呼びます。

- $ i\ +\ n\ -\ 1\ \leq\ H $
- $ j\ +\ n\ -\ 1\ \leq\ W $
- $ 0\ \leq\ k\ \leq\ n\ -\ 1,\ 0\ \leq\ l\ \leq\ n\ -\ 1 $ を満たす全ての非負整数の組 $ (k,\ l) $ に対して、$ (i\ +\ k,\ j\ +\ l) $ は穴が空いていないマスである。
 
グリッド内に穴のない正方形は何個ありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W\ \leq\ 3000 $
- $ 0\ \leq\ N\ \leq\ \min(H\ \times\ W,\ 10^5) $
- $ 1\ \leq\ a_i\ \leq\ H $
- $ 1\ \leq\ b_i\ \leq\ W $
- $ (a_i,\ b_i) $ は互いに異なる
- 入力される値は全て整数
 
### Sample Explanation 1

穴のない正方形は全部で $ 6 $ 個あります。 それらを列挙すると次の通りです。このうちはじめの $ 5 $ 個は $ n\ =\ 1 $ の場合であり、領域の左上隅のマスと右下隅のマスが一致します。 - $ (1,\ 1) $ を左上隅かつ右下隅とする正方形領域 - $ (1,\ 2) $ を左上隅かつ右下隅とする正方形領域 - $ (1,\ 3) $ を左上隅かつ右下隅とする正方形領域 - $ (2,\ 1) $ を左上隅かつ右下隅とする正方形領域 - $ (2,\ 2) $ を左上隅かつ右下隅とする正方形領域 - $ (1,\ 1) $ を左上隅, $ (2,\ 2) $ を右下隅とする正方形領域

### Sample Explanation 2

穴のない正方形が存在しない場合もあります。

### Sample Explanation 3

穴のない正方形がグリッド全体と一致する場合もあります。

## 样例 #1

### 输入

```
2 3 1
2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
3 2 6
1 1
1 2
2 1
2 2
3 1
3 2```

### 输出

```
0```

## 样例 #3

### 输入

```
1 1 0```

### 输出

```
1```

## 样例 #4

### 输入

```
3000 3000 0```

### 输出

```
9004500500```

# 题解

## 作者：ran_qwq (赞：7)

枚举正方形的右下顶点，再枚举正方形的边长，正方形数量是 $n^3$ 数量级的。

对于每个正方形，暴力判断有没有黑点，时间复杂度 $O(n^5)$。可以使用**二维前缀和**优化至 $O(n^3)$。

接着不难看出，固定右下顶点后，正方形的边长越大，越有可能包含黑点。换句话说，固定右下顶点后，正方形边长和有无黑点具有单调性。

考虑**二分**边长，用二维前缀和快速判断一个正方形有无黑点。时间复杂度 $O(n^2\log n)$，可以通过此题。

[AT 提交记录](https://atcoder.jp/contests/abc311/submissions/43916213)

---

## 作者：EmptyAlien (赞：4)

# [E - Defect-free Squares](https://atcoder.jp/contests/abc311/tasks/abc311_e)

## Sol

考虑 DP，设 $f_{i,j}$ 为以 $(i, j)$ 为右下角的无洞正方形的数量。

此时状态转移方程该怎么写呢？

考虑到对于一个点 $(i,j)$，对它有贡献的只有 $3$ 个点：$(i-1,j)$，$(i,j-1)$，$(i-1,j-1)$。

此时我们发现，如果一个点 $(i, j)$ 为右下角的正方形的边长为 $l$，那就需要满足有以 $(i-1, j)$，$(i,j-1)$，$(i-1,j-1)$ 为右下角的边长至少为 $l-1$ 的正方形。

所以转移方程式就出来了：

$$
f_{i,j} = 
\begin{cases}
0, &\text{if $(i,j)$ is hole}\\
\min(f_{i-1,j},f_{i,j-1},f_{i-1,j-1})+1, &\text{otherwise}
\end{cases}
$$

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
int n, m, k, a[MAXN][MAXN];
long long f[MAXN][MAXN], ans;
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j]) {
                continue;
            }
            f[i][j] = min({f[i][j - 1], f[i - 1][j], f[i - 1][j - 1]}) + 1;
            ans += f[i][j];
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Pt_crN (赞：4)

首杀 E，写来纪念。

题意即求一个矩阵内全为 $1$ 的正方形数。典中典。想起来我们做过[最大正方形](https://www.luogu.com.cn/problem/P1387)。这题只是改最值为计数。还是一样的状态及状转：设 $dp_{i,j}$ 为以 $(i,j)$ 为右下角的最大正方形边长。则有转移：

$$dp_{i,j}=\begin{cases}0&a_{i,j}=0\\ \min(dp_{i-1,j},dp_{i,j-1},dp_{i-1,j-1})+1&a_{i,j}=1\end{cases}$$

答案即为 $\sum dp_{i,j}$。

code：

```cpp
int n,m,k,pd[N][N],dp[N][N];
void Yorushika(){
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,k){
		int x,y;
		scanf("%d%d",&x,&y);
		pd[x][y]=true;
	}
	ll ans=0;
	rep(i,1,n){
		rep(j,1,m){
			if(pd[i][j])
				dp[i][j]=0;
			else 
				dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
			ans+=dp[i][j];
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Wonder_Fish (赞：2)

看到官方题解是 $O(n^2)$ 的 dp。

提供一个 $O(n^2 \log_2 n)$ 的做法，考场思路，大概比较简单。

---

## Description

给一个 $H$ 行 $W$ 列的网格，其中一些点被涂成黑色，求整个正方形内都未被涂黑的正方形的个数。

---

## Solution

考场上首先想到的简单暴力做法，即枚举正方形左上角端点，然后枚举正方形边长，求目前枚举的正方形中有没有黑色格子。

这样做是 $O(n^3)$ 的，接受不了。

所以我们需要减少或者优化掉一维的枚举。

考虑固定正方形的左上角，先 $O(n^2)$ 枚举左上角 $(i,j)$，然后考虑如何快速计算答案。

显然对于满足条件的正方形，其内部黑色格子的数量是 $0$，而在暴力枚举的过程中，正方形的边长不断增大，黑色格子的数量是单调不减的。

因此，如果以 $(i,j)$ 为左上角端点，边长为 $len$ 的正方形中黑格个数 $> 0$，那么左上端点不变，边长 $\geq len$ 的正方形中黑格个数一定 $> 0$，不可行。

而如果以 $(i,j)$ 为左上角端点，边长为 $len$ 的正方形中黑格个数 $= 0$，那么左上角不变，边长 $\leq len$ 的正方形中黑格个数也一定 $= 0$，可行。

换句话说，设 $a_{len}$ 表示以 $(i,j)$ 为左上角的正方形中，边长为 $len$ 的，其内部黑色格子的数量，那 $a_{len}$ 随 $len$ 单调不减，而我们要求出 $a$ 数组前面连续的 $0$ 的个数。

这满足单调性，可以二分边长 $len$ ，对于每一个二分到的 $len$ ，可以用二维前缀和 $O(1)$ 算出正方形内黑色格子数。

不会二维前缀和的同学可以看一下 [P2004](https://www.luogu.com.cn/problem/P2004)。

总复杂度 $O(n^2 \log_2 n)$ ，此处的 $n$ 即题目里的 $H$,$W$, $3000$ 级别的，勉强可以过，最慢的点 $528 ms$。

---

## Code

里面有一些注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
	template<typename T> inline void write(T x){
		if(x<0) putchar('-'),x=-x;
		if(x==0){
			putchar('0'); return ;
		}
		if(x>9) write(x/10);
		putchar(x%10+'0');
		return ;
	}
	template<typename T> inline void read(T &x){
		x=0; int w=1; char ch=getchar();
		while(!isdigit(ch)){
			if(ch=='-') w=-1; ch=getchar();
		}
		while(isdigit(ch))
			x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
		x*=w; return ;
	}
}
using namespace IO; //快读
#define writesp(x) write(x),putchar(' ')
#define writeln(x) write(x),putchar('\n')
#define inf 0x3f3f3f3f3f3f
#define mod 998244353
#define maxn 3010
#define int long long
#define pb emplace_back
int h,w,n,a[maxn][maxn],x,y,l,r,mid,ans=0;
int calc(int x1,int _y1,int x2,int y2){
	return a[x2][y2]-a[x1-1][y2]-a[x2][_y1-1]+a[x1-1][_y1-1]; //二维前缀和
}
bool check(int i,int j,int mid){
	return (calc(i,j,i+mid-1,j+mid-1)==0); //满足条件即为不含黑色方格
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
//	cin.tie(0); cout.tie(0);
	read(h); read(w); read(n);
	memset(a,0,sizeof(a));
	while(n--){
		read(x); read(y); a[x][y]=1;
	}
	for(int i=1;i<=h;++i)
		for(int j=2;j<=w;++j) a[i][j]+=a[i][j-1];
	for(int i=1;i<=w;++i)
		for(int j=2;j<=h;++j) a[j][i]+=a[j-1][i];
	//计算二维前缀和数组
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j){
			l=1; r=min(h-i+1,w-j+1); //二分，最小边长是 1，最大边长需要保证不越界
			while(l<=r){
				mid=(l+r)>>1;
				if(check(i,j,mid)) l=mid+1;
				else r=mid-1;
			}
			ans+=r; //二分出 r 为以 (i,j) 为端点的满足条件的正方形最大边长，也是正方形个数
		}
	writeln(ans);
	return 0;
}

```

---

## 作者：wizardMarshall (赞：2)

## 题意

一个方格矩阵，有一些格子被涂成了黑色（个数不超过 $10^5$），求有多少个白色正方形。

## 思路

可以考虑以每一个白色格子作为白色正方形左上角，求最大边长。

![](https://cdn.luogu.com.cn/upload/image_hosting/zl0uva13.png)

如上如所示，以左上角往下构造正方形，总会有一层遇到黑色格子（或边缘）。如果对于每个白色格子都这样一层层枚举，时间复杂度骤增，无法通过此题。

于是我们考虑对于每一个黑色格子，会影响多少个白色格子。最坏情况是需要枚举每个黑色格子及其左上角的矩阵，复杂度 $O(HW\times 10^5)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4098imne.png)

如上图，我们发现有很多重叠的部分，也就是说大多数黑色格子是无用的。

由于对于每个白色格子，只有右下方最近的黑色格子有用，自然而然想到多源最短路。

从每个黑色格子出发，往左上跑最短路。

![](https://cdn.luogu.com.cn/upload/image_hosting/iiu4zhkn.png)

由于最短路，每个格子最多只会经过一次，满足了时间复杂度。同时，最短路恰好是正方形的边长。

有些格子右下区域没有黑色格子，计算其与矩形边长的差的较小值。

另：跑最短路的时候，每一步不仅要往左、往上，还要走左上。这样才能实现每一层都构成正方形形状。

## 代码

代码说明：$vis$ 数组记录的是格子编号而非最短路。省去了判断是黑格子还是没有跑到的空格子等操作。最终通过编号对应的坐标计算边长。


```

#include <bits/stdc++.h>
using namespace std;
#define int long long
int vis[3005][3005];
pair <int, int> node[100005];
signed main() {
	int h, w, n;
	cin >> h >>w >> n;
	queue <pair <pair <int, int>, int> > q;//边长相同，不需要优先队列
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &node[i].first, &node[i].second);
		vis[node[i].first][node[i].second] = i;
		q.push({node[i], i});
	}
	
	while (!q.empty()) {
		pair <pair <int, int>, int> f = q.front();q.pop();
		//往上
		if (f.first.first != 1) {
			if (!vis[f.first.first - 1][f.first.second]) {
				vis[f.first.first - 1][f.first.second] = f.second;
				q.push({{f.first.first - 1, f.first.second}, f.second});
			}
		}
		//往左
		if (f.first.second != 1) {
			if (!vis[f.first.first][f.first.second - 1]) {
				vis[f.first.first][f.first.second - 1] = f.second;
				q.push({{f.first.first, f.first.second - 1}, f.second});
			}
		}
		//左上
		if (f.first.first != 1 && f.first.second != 1) {
			if (!vis[f.first.first - 1][f.first.second - 1]) {
				vis[f.first.first - 1][f.first.second - 1] = f.second;
				q.push({{f.first.first - 1, f.first.second - 1}, f.second});
			}
		}
	}
	int sum = 0;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (vis[i][j]) {//注意：边长大于矩形边缘时，取矩形边缘（否则此时正方形会超出矩形）
				int temp = min(min(h - i + 1, w - j + 1), max(node[vis[i][j]].first - i, node[vis[i][j]].second - j));
				sum += temp;
			}else {//右下没有黑格，与边缘作差
				int temp = min(h - i + 1, w - j + 1);
				sum += temp;
			}
		}
	}cout << sum;
	return 0;
}


```

考场思路，不保证最简，仅供参考。严禁抄袭。

---

## 作者：康立扬 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc311_e)

题意即求不包含特殊点的格点正方形数。
## $\mathtt{Solution}$
考虑固定正方形的右下角，记为 $(x,y)$。

注意到包含特殊点的个数随着边长的增加单调不降，因此可以使用二分来求出符合要求的最大边长 $l_{x,y}$。在二分时，可以用二维前缀和来快速判断包含的特殊点个数。

所求答案即为 $\sum\limits_{i=1}^H \sum\limits_{j=1}^Wl_{i,j}$。

[提交记录](https://atcoder.jp/contests/abc311/submissions/43859619)

---

## 作者：Neil_Qian (赞：2)

# AT_abc311_e Defect-free Squares 题解

## 题目描述

给出一个 $H\times W$ 的矩阵，每个位置**要么有洞，要么没洞**，$a_{i,j}$ 表示位置 $(i,j)$ 是否有洞。问有多少个每个元素均为正整数的三元组 $(x,y,n)$，满足：

$x+n-1\le H$，$y+n-1\le W$，以 $(x,y)$ 为左上角、$(x+n-1,y+n-1)$ 为右下角的矩阵**每个位置都没有洞**。

$H,W\le 3000$，洞的个数不超过 $10^5$。

## 解决方案

很容易发现，对于每一个 $(x,y,n)$，如果它不满足条件，则 $(x,y,n+1)$ 一定也不满足。发现满足单调性，于是考虑二分。现在问题在于如何快速统计一个子矩阵内是否有洞。

不难想到二维前缀和，令 $s_{i,j}=\sum_{k=1}^i\sum_{l=1}^ja_{i,j}$，统计一个左上角为 $(x1,y1)$，右下角为 $(x2,y2)$ 的子矩阵内是否有洞，即 $s_{x2,y2}-s_{x1-1,y2}-s_{x2,y1-1}+s_{x1-1,y1-1}>0$。

$H$ 和 $W$ 同阶，时间复杂度为 $O(H^2logH)$。发现上述方法可以延伸到洞的个数不超过一个值，时间复杂度相同。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=3002;
int n,m,k,s[N][N],x,y,i,j,l,r,mid,d;long long ans;
inline int calc(int a1,int b1,int a2,int b2){
	return s[a2][b2]-s[a2][b1-1]-s[a1-1][b2]+s[a1-1][b1-1];
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//IO优化
	cin>>n>>m>>k;
	while(k--)cin>>x>>y,s[x][y]=1;
	for(i=1;i<=n;++i)for(j=1;j<=m;++j)s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];//前缀和计算
	for(i=1;i<=n;++i)for(j=1;j<=m;++j){//计算每一个位置
		l=1,r=min(n-i+1,m-j+1),d=0;
		while(l<=r)mid=(l+r)>>1,(!calc(i,j,i+mid-1,j+mid-1)?(d=mid,l=mid+1):r=mid-1);//二分答案
		ans+=d;
	}
	return cout<<ans<<"\n",0;//输出
}
```

---

## 作者：luogu_gza (赞：1)

我们枚举 $(i,j)$，可以发现对于 $n$ 来说，问题的可行性是单调的，所以考虑二分，二分最大的 $l$ 使得 $\sum_{x=i}^{i+l-1}\sum_{y=j}^{j+l-1}a_{x,y}=0$。

我们可以使用当前矩阵总和是否为 $0$ 来判断是否为空。

记得判断当前点是否本身有洞，这样的话当前点对于答案的贡献就明显是 $0$ 了。

如果你是在原数组上直接做了前缀和的话，判断是否本身有洞就不是普通的判定方式了，也要像计算矩阵和一样做。

[code](https://atcoder.jp/contests/abc311/submissions/43874285)

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目大意】**

$n \times m$ 的矩形内有 $q$ 个点，问矩形内有几个正方形不包含任意一个点。$1 \le n,m \le 3 \times 10^3,1 \le q \le 10^5$。

**【题目分析】**

听说这题正解 $\Theta(nm+q)$，但赛时 $\Theta(nm \log n+q)$ 过了 qwq。

我们发现如果一个点向下扩展边长为 $i$ 的正方形内包含点，则边长为 $j(j \ge i)$ 的正方形内也一定有点，因此考虑二分答案。先二维前缀和预处理出区间内点的数量是否为 $0$，然后枚举起点，二分最大能扩展的正方形的边长统计答案，时间复杂度 $\Theta(nm \log n+q)$。

记得开 `long long`！

**【代码】**


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,q,x[100005],y[100005],mp[3005][3005],a[3005][3005],ans;
bool check(int i,int j,int x){
    if(x == 1) return !mp[i][j];
    int p = i + x - 1,q = j + x - 1;
    if(p > n || q > m) return 0;
    int sm = a[p][q] + a[i-1][j-1] - a[p][j-1] - a[i-1][q];
    if(sm > 0) return 0;return 1;
}
signed main(){
    cin >> n >> m >> q;
    for(int i = 1;i <= q;i ++) cin >> x[i] >> y[i],mp[x[i]][y[i]] = 1;
    for(int i = 1;i <= n;i ++){
        for(int j = 1;j <= m;j ++)
            a[i][j] = mp[i][j] + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
    }
    for(int i = 1;i <= n;i ++){
        for(int j = 1;j <= m;j ++){
            int l = 1,r = min(n-i+1,m-j+1),res = 0;
            while(l <= r){
                int mid = (l + r) / 2;
                if(check(i,j,mid)) l = mid + 1,res = mid;
                else r = mid - 1;
            }
            ans += res;
        }
    }
    cout << ans;
    return 0;
}
```

---

