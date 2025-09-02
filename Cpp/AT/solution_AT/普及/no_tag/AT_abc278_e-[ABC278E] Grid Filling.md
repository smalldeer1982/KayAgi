# [ABC278E] Grid Filling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc278/tasks/abc278_e

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ で表します。 $ (i,j)\ (1\leq\ i\leq\ H,1\leq\ j\leq\ W) $ には $ 1 $ 以上 $ N $ 以下の整数 $ A\ _\ {i,j} $ が書かれています。

整数 $ h,w $ が与えられます。$ 0\leq\ k\leq\ H-h,0\leq\ l\leq\ W-w $ を満たすすべての $ (k,l) $ の組について、次の問題を解いてください。

- $ k\lt\ i\leq\ k+h,l\lt\ j\leq\ l+w $ を満たす $ (i,j) $ を塗りつぶしたとき、塗りつぶされていないマスに書かれている数が何種類あるか求めよ。
 
ただし、問題を解く際に実際にマスを塗りつぶすことはない（各問題が独立である）ことに注意してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W,N\ \leq\ 300 $
- $ 1\ \leq\ h\ \leq\ H $
- $ 1\ \leq\ w\ \leq\ W $
- $ (h,w)\neq(H,W) $
- $ 1\ \leq\ A\ _\ {i,j}\ \leq\ N\ (1\leq\ i\leq\ H,1\leq\ j\leq\ W) $
- 入力される値はすべて整数
 
### Sample Explanation 1

与えられた盤面は下の図のようになります。 !\[\](https://img.atcoder.jp/abc278/d3542563ea2e11fda78c3307c0a2b0fe.png) 例えば、$ (k,l)=(0,0) $ のときは塗りつぶされていないマスに書かれている数は $ 1,3,4,5 $ の $ 4 $ 種類なので、$ 4 $ が答えになります。

## 样例 #1

### 输入

```
3 4 5 2 2
2 2 1 1
3 2 5 3
3 4 4 3```

### 输出

```
4 4 3
5 3 4```

## 样例 #2

### 输入

```
5 6 9 3 4
7 1 5 3 9 5
4 5 4 5 1 2
6 1 6 2 9 7
4 7 1 5 8 8
3 4 3 3 5 3```

### 输出

```
8 8 7
8 9 7
8 9 8```

## 样例 #3

### 输入

```
9 12 30 4 7
2 2 2 2 2 2 2 2 2 2 2 2
2 2 20 20 2 2 5 9 10 9 9 23
2 29 29 29 29 29 28 28 26 26 26 15
2 29 29 29 29 29 25 25 26 26 26 15
2 29 29 29 29 29 25 25 8 25 15 15
2 18 18 18 18 1 27 27 25 25 16 16
2 19 22 1 1 1 7 3 7 7 7 7
2 19 22 22 6 6 21 21 21 7 7 7
2 19 22 22 22 22 21 21 21 24 24 24```

### 输出

```
21 20 19 20 18 17
20 19 18 19 17 15
21 19 20 19 18 16
21 19 19 18 19 18
20 18 18 18 19 18
18 16 17 18 19 17```

# 题解

## 作者：liangbowen (赞：25)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc278_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16910389.html)

非常套路的题目，为啥要放在 E。

[整合题解](https://www.luogu.com.cn/blog/liangbowen/abc278-ti-jie)。

## 思路

容易发现，相邻查询的覆盖区间不会差太远。所以考虑用较短的时间处理两个查询。

思路也很容易想到：维护两个操作 add 与 del，支持 $O(1)$ 增加、删除一个数。

```cpp
void add(int x)
{
    if (!vis[x]) ans++;
    vis[x]++;
}
void del(int x)
{
    vis[x]--;
    if (!vis[x]) ans--;
}
```

然后，对于相邻两个操作，只需要删除掉前一列，并增加新的一列即可。

只需要特殊处理一下第一个区间即可。

这样，时间复杂度就是 $O(n^3)$ 了。

## 代码

省去了大段的缺省源。

```cpp
const int N = 305;
int vis[N], zlt[N]; //zlt 是备份的原 vis
int a[N][N];

int ans, tans; //tans 是备份的原 ans
void add(int x)
{
    if (!vis[x]) ans++;
    vis[x]++;
}
void del(int x)
{
    vis[x]--;
    if (!vis[x]) ans--;
}
int ANS[N][N];
void solve()
{
    int n, m, k, h, w; 
    scanf("%d%d%d%d%d", &n, &m, &k, &h, &w);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            if (!vis[a[i][j]]) ans++, tans++;
            vis[a[i][j]]++, zlt[a[i][j]]++;
        }
    for (int i = 1; h + i - 1 <= n; i++)
    {
        ans = tans;
        for (int j = 1; j <= k; j++) vis[j] = zlt[j];

        for (int j = i; j <= h + i - 1; j++)
            for (int k = 1; k <= w; k++)
                del(a[j][k]);
        ANS[i][1] = ans;
        for (int j = 1; j + w - 1 <= m; j++) //纵坐标
        {
            for (int k = i; k <= h + i - 1; k++) add(a[k][j]), del(a[k][j + w]); //横坐标
            ANS[i][j + 1] = ans; //统计答案
        }
    }
    for (int i = 1; i <= n - h + 1; i++, putchar('\n'))
        for (int j = 1; j <= m - w + 1; j++, putchar(' '))
            printf("%d", ANS[i][j]);
}
```

希望能帮助到大家！

---

## 作者：FFTotoro (赞：3)

本题需要使用类似高维前缀和的做法。

首先预处理，用 $F_{i,j,x}$ 表示 $(1,1)$ 为左上角、$(i,j)$ 为右上角的矩阵中 $x$ 的个数。易得 $F$ 的转移式：

$$F_{i,j,x}=F_{i-1,j,x}+F_{i,j-1,x}-F_{i-1,j-1,x}+[A_{i,j}=x]$$

转移方程的依据是容斥原理，考虑到学过二维前缀和的人较多，这里不多赘叙。

然后对于每一对 $(k,l)$ 我们只需统计题目所示的小矩阵中每个数的个数（可以由 $F$ 推导出来）。具体地，以 $(k+1,l+1)$ 为左上角，$(k+h,l+w)$ 为右下角的子矩阵中 $x$ 的个数即为：

$$F_{k+h,l+w,x}-F_{k,l+w,x}-F_{k+h,l,x}+F_{k,l,x}$$

可以发现，$\forall 1\le x\le N$，如果上述式子的值等于 $F_{H,W,x}$ 的值，就说明这个子矩阵外已经不包含任何的 $x$。

如果我们称满足上述条件的的 $x$ 为“独特的”，那么每次询问的答案就是整个矩阵中包含的不同种类的数的数量减去子矩阵内“独特的”数的数量。

具体地，每次询问中对于每个在矩阵中有出现过的 $x$ 判断一下即可。

总时间复杂度 $O(HWN)$，可以通过本题。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int c[301][301][301];
bool v[301];
set<int> s;
main(){
  ios::sync_with_stdio(false);
  int h,w,n,a,b; cin>>h>>w>>n>>a>>b;
  for(int i=1;i<=h;i++)
    for(int j=1;j<=w;j++){
      int x; cin>>x;
      for(int k=1;k<=n;k++)
        c[i][j][k]=c[i-1][j][k]+c[i][j-1][k]-c[i-1][j-1][k]+(x==k);
      s.emplace(x); v[x]=true;
    } // 前缀和预处理
  for(int i=0;i<=h-a;i++,cout<<endl)
    for(int j=0;j<=w-b;j++){
      int r=0;
      for(int k=1;k<=n;k++)
        if(v[k])r+=(c[i+a][j+b][k]-c[i][j+b][k]-c[i+a][j][k]+c[i][j][k]==c[h][w][k]); // 统计“独特的”x
      cout<<s.size()-r<<' ';
    } // 枚举 (k,l)
  return 0;
}
```

---

## 作者：SoyTony (赞：1)

考虑对于每种颜色进行计算。

可以维护出每种颜色出现的最左、最右、最上、最下的位置。这形成了一个矩形，如果 $h\times w$ 的矩形可以将其覆盖，那么这个颜色是可能产生贡献的，反之不存在一个矩形可以掩盖这个颜色出现的全部位置。

于是可以暴力对这个颜色产生贡献的矩形进行覆盖。

```cpp
int H,W,n,h,w;
int a[305][305];
int min_x[305],max_x[305],min_y[305],max_y[305];
int ans[305][305];
int main(){
    H=read(),W=read(),n=read(),h=read(),w=read();
    memset(min_x,0x3f,sizeof(min_x));
    memset(min_y,0x3f,sizeof(min_y));
    for(int i=1;i<=H;++i){
        for(int j=1;j<=W;++j){
            int x=read();
            a[i][j]=x;
            min_x[x]=min(min_x[x],i),max_x[x]=max(max_x[x],i);
            min_y[x]=min(min_y[x],j),max_y[x]=max(max_y[x],j);
        }
    }
    for(int i=1;i<=n;++i){
        // printf("id:%d\n",i);
        int x=max_x[i]-min_x[i]+1,y=max_y[i]-min_y[i]+1;
        if(x>h||y>w) continue;
        // printf("%d %d\n",x,y);
        for(int r=max(1,max_x[i]-h+1);r<=min(H-h+1,min_x[i]);++r){
            for(int c=max(1,max_y[i]-w+1);c<=min(W-w+1,min_y[i]);++c){
                // printf("(%d,%d)\n",r,c);
                --ans[r][c];
            }
        }
        // for(int i=1;i<=H-h+1;++i){
        //     for(int j=1;j<=W-w+1;++j){
        //         printf("%d ",ans[i][j]);
        //     }
        //     printf("\n");
        // }
    }
    for(int i=1;i<=H-h+1;++i){
        for(int j=1;j<=W-w+1;++j){
            ans[i][j]+=n;
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：FReQuenter (赞：1)

## 思路

一般判断一个数是否出现有两种方式：哈希或前缀和。

但这里是二维矩形，哈希显然不太好写啊。

我们考虑所有数一起二维前缀和：设 $sum_{k,i,j}$ 为数 $k$ 在 $(1,1)$ 到 $(i,j)$ 出现的次数。这样判断一个数是否出现在非阴影范围内就是判断在阴影外这个数是否出现过。这样用每一次 $O(n^2)$ 枚举阴影的范围，而 $O(n)$ 枚举所有数，检查 $(1,1)$ 到 $(i,j)$ 出现的次数减去阴影中出现的次数，如果非零，就是在阴影外出现过。

关于二维前缀和：可以前往模板：[HNOI2003激光炸弹](luogu.com.cn/problem/P2280)，了解具体如何使用。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int H,W,n,h,w,sum[305][305][305],a[305][305],ans[305][305];
signed main(){
	cin>>H>>W>>n>>h>>w;
	for(int i=1;i<=H;i++) for(int j=1;j<=W;j++) cin>>a[i][j];
	for(int k=1;k<=n;k++){
		for(int i=1;i<=H;i++){
			for(int j=1;j<=W;j++){
				sum[k][i][j]=sum[k][i-1][j]+sum[k][i][j-1]-sum[k][i-1][j-1]+(a[i][j]==k); 
			} 
		}
	}
	for(int i=h;i<=H;i++){
		for(int j=w;j<=W;j++){
			int s=0;
			for(int k=1;k<=n;k++){
				if(sum[k][H][W]-(sum[k][i][j]-sum[k][i-h][j]-sum[k][i][j-w]+sum[k][i-h][j-w])) s++;
			}
			ans[i][j]=s;
		}
	}
	for(int i=h;i<=H;i++) {
		for(int j=w;j<=W;j++) cout<<ans[i][j]<<' ';
		cout<<endl;
	}
}
```

---

## 作者：Suyun (赞：1)

按照题意暴力模拟。枚举左上角的点 $(i, j)$，覆盖所有满足 $i \le i' < i + w, j \le j' < j + h$ 的点 $(i', j')$，并使用 Hash 表维护每个数字的出现次数并统计答案。最终复杂度 $O(WHwh)$。

需要注意的是，STL 内的 `std::unordered_map` 常数较大，最好自己实现 Hash 表或使用 `__gnu_pbds::gp_hash_table`。（咱在使用 `__gnu_pbds::gp_hash_table` 的情况下，最慢的一个点跑了 1725 ms。）

```cpp
#define _EXT_CODECVT_SPECIALIZATIONS_H 1
#define _EXT_ENC_FILEBUF_H 1
#include <bits/extc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	const char endl = '\n';
	
	int H, W, N, h, w;
	cin >> H >> W >> N >> h >> w;
	
	vector< vector<int> > A(H + 1, vector<int>(W + 1));
	
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			cin >> A[i][j];
		}
	}
	
	__gnu_pbds::gp_hash_table<int, int> cnt;
	
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			cnt[ A[i][j] ]++;
		}
	}
	
	for (int i = 1; i <= H - h + 1; ++i) {
		for (int j = 1; j <= W - w + 1; ++j) {
			for (int di = 0; di < h; ++di) {
				for (int dj = 0; dj < w; ++dj) {
					if (--cnt[ A[i + di][j + dj] ] == 0) {
						cnt.erase(A[i + di][j + dj]);
					}
				}
			}
			
			cout << cnt.size() << ' ';
			
			for (int di = 0; di < h; ++di) {
				for (int dj = 0; dj < w; ++dj) {
					cnt[ A[i + di][j + dj] ]++;
				}
			}
		}
		
		cout << endl;
	}
}
```

---

## 作者：sunzz3183 (赞：1)

# [ABC278E] Grid Filling 题解

## 题意

给定一个 $H \times W$ 的矩阵，每个位置都有一个 $[1,N]$ 的数字。

再给定一个 $h$ 和 $w$，每次把一个 $h \times w$ 的矩阵涂黑，求没涂黑的区域里，有多少种数字。

## 分析

直接暴力的话，复杂度是 $O(N^4)$ 的，看眼范围

- $ 1\ \leq\ H,W,N\ \leq\ 300 $

~~再见~~。

考虑优化：

我们可以开个数组 $sum$ 求出总矩阵的每个数字出现的次数，然后开个数组 $f$ 求出每个小矩阵的每个数字出现的次数，那么每个矩阵的答案即：

$\sum_{i=1}^N [sum_i-f_i >0] $ 

总复杂度：$O(N^4)$ （$T(HWhw)$） 

继续优化

假设我们求出了第一个矩阵（左上为 $(1,1)$，右下为 $(h,w)$）。

那么左上为 $(1,2)$，右下为 $(h,w+1)$ 的矩阵或左上为 $(2,1)$，右下为 $(h+1,w)$ 的矩阵，都可以 $O(h)$ 或 $O(w)$，的求出来（删掉一行，加上一行）。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vqiu7qrv.png)

所以，先 $O(hw)$ 求出第一个矩阵。

代码：

```cpp
for(int i=1;i<=h;i++)
	for(int j=1;j<=w;j++)
		f[1][1][a[i][j]]++;
```

再 $O(HN)$ 求出所有左上角为 $(i,1)$ 的矩阵。


代码：

```cpp
for(int i=2;i<=H-h+1;i++){
	memset(sum1,0,sizeof(sum1));
	memset(sum2,0,sizeof(sum2));
	for(int j=1;j<=w;j++)sum1[a[i-1][j]]++,sum2[a[i+h-1][j]]++;
	for(int j=1;j<=n;j++)f[i][1][j]=f[i-1][1][j]-sum1[j]+sum2[j];
}
```


最后从所有左上角为 $(i,1)$ 的矩阵，推出后面的矩阵，复杂度：$O(HWN)$ 。

代码：

```cpp
for(int i=1;i<=H-h+1;i++)
	for(int j=2;j<=W-w+1;j++){
		memset(sum1,0,sizeof(sum1));
		memset(sum2,0,sizeof(sum2));
		for(int l=i;l<=i+h-1;l++)sum1[a[l][j-1]]++,sum2[a[l][j+w-1]]++;
		for(int l=1;l<=n;l++)f[i][j][l]=f[i][j-1][l]-sum1[l]+sum2[l];
	}
```

总复杂度：$O(N^3)$ （$T(hw+HN+HWN)$） 

## 代码

```cpp
#include<bits/stdc++.h>
// #define int long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=305;
int W,H,n,h,w,a[N][N],sum[N],f[N][N][N];
int sum1[N],sum2[N];
signed main(){
	H=read();W=read();n=read();h=read();w=read();
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
			a[i][j]=read(),sum[a[i][j]]++;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			f[1][1][a[i][j]]++;
	for(int i=2;i<=H-h+1;i++){
		memset(sum1,0,sizeof(sum1));
		memset(sum2,0,sizeof(sum2));
		for(int j=1;j<=w;j++)sum1[a[i-1][j]]++,sum2[a[i+h-1][j]]++;
		for(int j=1;j<=n;j++)f[i][1][j]=f[i-1][1][j]-sum1[j]+sum2[j];
	}
	for(int i=1;i<=H-h+1;i++)
		for(int j=2;j<=W-w+1;j++){
			memset(sum1,0,sizeof(sum1));
			memset(sum2,0,sizeof(sum2));
			for(int l=i;l<=i+h-1;l++)sum1[a[l][j-1]]++,sum2[a[l][j+w-1]]++;
			for(int l=1;l<=n;l++)f[i][j][l]=f[i][j-1][l]-sum1[l]+sum2[l];
		}
	for(int i=1;i<=H-h+1;puts(""),i++)
		for(int j=1;j<=W-w+1;j++){
			int ans=0;
			for(int l=1;l<=n;l++)if(sum[l]-f[i][j][l]>0)ans++;
			printf("%lld ",ans);
		}
	return 0;
}
```


---

## 作者：Jerrywang09 (赞：0)

实际上，目前有的题解都没法精确体现“前缀和”的思想。

给定一个矩形，每次覆盖一个 $w\times h$ 的矩形。求没有被覆盖的数中有多少个不同的数。

考虑到 $n\le 300$，可以三重循环。不难想到使用二维前缀和维护，每一个元素存每种值的出现次数。

可以自定义运算符处理运算。最后二维前缀和求值时，只统计不同数的个数，因此只需要判断相应位是否 $>0$。

问题是，执行 `-` 操作时为什么 $x_k$ 可以取到负数？实际上，对于每个 $f_{i,j,k}$ 都不可能取到负数，因为右下的是包含左上的，那么 `f[i][j]-f[i-h][j]-f[i][j-w]+f[i-h][j-w]` 一定不会是负数。如果过早地判断负数的情况会导致无法通过第 $3$ 个样例。详见 [这个提交记录](https://atcoder.jp/contests/abc278/submissions/36864677)。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, s, t) for(int i=s; i<=t; i++)
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
const int SIZE=301;
using namespace std;

int m, n, K, h, w;
int a[SIZE][SIZE];
vector<int> f[SIZE][SIZE];

vector<int> operator +(vector<int> x, vector<int> y)
{
	rep(k, 0, 300) x[k]+=y[k];
	return x;
}

vector<int> operator -(vector<int> x, vector<int> y)
{
	rep(k, 0, 300) x[k]-=y[k];
	return x;
}

int cnt(vector<int> x)
{
	int res=0;
	rep(k, 0, 300) if(x[k]>0) res++;
	return res;
}

signed main()
{
	scanf("%d %d %d %d %d", &m, &n, &K, &h, &w);
	rep(i, 0, m) rep(j, 0, n) f[i][j].resize(SIZE);
	rep(i, 1, m) rep(j, 1, n) scanf("%d", &a[i][j]);
	rep(i, 1, m) rep(j, 1, n)
	{
		f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
		f[i][j][a[i][j]]++;
		//cout<<cnt(f[i][j])<<" ";
	}
	rep(i, h, m)
	{
		rep(j, w, n)
			printf("%d ",
			//          注意优先级！
			cnt(f[m][n]-(f[i][j]-f[i-h][j]-f[i][j-w]+f[i-h][j-w])));
		puts("");
	}

    return 0;
}
```



---

## 作者：Shimotsuki (赞：0)

[传送门 to 洛谷](https://www.luogu.com.cn/problem/AT_abc278_e)

[传送门 to AT](https://atcoder.jp/contests/abc278/tasks/abc278_e)

题意：给定一个 $H \times W$ 的网格图，每次覆盖一个面积为 $h \times w$ 的区域，求未被覆盖的区域中不重复的数字的个数。

思路：首先，暴力计算每一个被覆盖区域并统计答案的复杂度是 $O(n^4)$，明显不可取。因为题目的数据范围都 $\leq 300$，所以考虑一个 $O(n^3)$。考虑优化暴力做法：可以先暴力计算覆盖最左上角的的答案，然后向右向下转移。向右转移时，只需要加上最左列的贡献和减去最右列的贡献，因为最左列是空出来的区域，最右列则是新覆盖的区域，中间部分是对上一个覆盖区域的继承部分；向下转移时，要加上最上面一行的贡献和减去最下面一行的贡献，道理同向右转移。这样这道题就做完了，时间复杂度 $O(n^3)$。

长得比较丑的考场代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

int n,m;
int h,w;
int mx;
int a[310][310],dp[310][310];
int cnt[310];

int main(){
	cin>>n>>m>>mx>>h>>w;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j) cin>>a[i][j],cnt[a[i][j]]++;
	}
	for(int i=1;i<=h;++i){
		for(int j=1;j<=w;++j){
			cnt[a[i][j]]--;
		}
	}
	for(int i=1;i<=mx;++i) if(cnt[i]) dp[1][1]++;
//	for(int i=1;i<=h;++i){
//		for(int j=1;j<=w;++j){
//			cnt[a[i][j]]++;
//		}
//	}
	for(int i=1;i+h-1<=n;++i){
		if(dp[i][1]) continue;
		int res=0;
		for(int j=1;j<=w;++j){
			cnt[a[i-1][j]]++;
		}
		for(int j=1;j<=w;++j){
			cnt[a[i+h-1][j]]--;
		}
		for(int j=1;j<=mx;++j) if(cnt[j]) res++;
		dp[i][1]=res;
	}
	for(int i=1;i<=mx;++i) cnt[i]=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j) cnt[a[i][j]]++;
	}
	for(int i=1;i+h-1<=n;++i){
		for(int j=i;j<=i+h-1;++j){
			for(int k=1;k<=w;++k) cnt[a[j][k]]--;
		}
//		int zcy=0;
//		for(int j=1;j<=mx;++j) if(cnt[j]) zcy++;
//		cout<<"zcy="<<zcy;
		for(int j=1;j+w-1<=m;++j){
			if(dp[i][j]) continue;
			int res=0;
			for(int k=i;k<=i+h-1;++k) cnt[a[k][j-1]]++;
			for(int k=i;k<=i+h-1;++k) cnt[a[k][j+w-1]]--;
			for(int k=1;k<=mx;++k) if(cnt[k]) res++;
			dp[i][j]=res;
		}
		for(int j=1;j<=mx;++j) cnt[j]=0;
		for(int j=1;j<=n;++j){
			for(int k=1;k<=m;++k) cnt[a[j][k]]++;
		}
	}
	for(int i=1;i+h-1<=n;++i){
		for(int j=1;j+w-1<=m;++j) cout<<dp[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：MoyunAllgorithm (赞：0)

**题意**

你有一个 $H \times W$ 的方格纸，每个格子上都有一种颜色。每种颜色用一个数表示，且这个数不超过 $N$。$N$ 与 $H,W$ 同阶。

现在，你有一个 $h \times w$ 的黑色小纸板。你要依次将该纸板盖住大方格纸的每一个 $h \times w$ 的子正方形。对于每一次覆盖，回答大方格纸还有多少个颜色没被盖住。

$H,W,N \le 300$。

**分析**

如果我们枚举小黑纸板的位置，之后统计，可以轻松的做到  $O(N^4)$。好像是可以优化的，但我在考场上没有继续想了。

我们换一个思考角度：枚举颜色。**如果小黑纸板能够完全盖住一个颜色，那么小黑纸板一定可以同时盖住该颜色的上界、下界、左界、右界**。我们可以枚举所有位置符合该要求的小黑纸板。枚举颜色是 $O(N)$ 的，枚举纸板是 $O(N^2)$ 的，总复杂度 $O(N^3)$。

具体实现时，设 $cnt_{i,j}$ 表示当小黑纸板的左上角在 $(i,j)$ 时，剩下的颜色数。一开始，将所有 $cnt$ 全都赋值为图的总颜色数。我们用 `struct` 记录每个颜色的上界、下界、左界、右界。

该部分代码：

```cpp
int colcnt=0;
	for(int i=1;i<=H;i++)
	{
		for(int j=1;j<=W;j++)
		{
			scanf("%d",&a[i][j]);
			if(col[a[i][j]].n==305) colcnt++;//如果第一次读入该颜色
			col[a[i][j]].n=min(col[a[i][j]].n,i);//上界
			col[a[i][j]].s=max(col[a[i][j]].s,i);
//下界
			col[a[i][j]].w=min(col[a[i][j]].w,j);
//左界
			col[a[i][j]].e=max(col[a[i][j]].e,j);
//右界
		}
	}
	for(int i=1;i<=H;i++)
	{
		for(int j=1;j<=W;j++)
		{
			cnt[i][j]=colcnt;//cnt初始值
		}
	}
```
接下来，我们枚举所有的颜色。我们根据该颜色的边界坐标，可以得到如果小黑纸板能够覆盖该颜色，它的左上角应在的坐标。

具体为：设该颜色的上下左右界分别是 $a,b,c,d$，符合条件的小黑纸板的左上角可能在的位置的上下左右界分别是 $n,s,w,e$，小黑纸板是 $x \times y$ 的，则

$n=\text{min}(1,b-x+1)$

$s=a$

$w=\text{min}(1,d-y+1)$

$e=c$

之后，我们对 $i \in [n,s],j \in [w,e]$ 进行双重循环统计。

```cpp
for(int i=1;i<=N;i++)
	{
		int nn=col[i].n,ss=col[i].s,ww=col[i].w,ee=col[i].e;
	//当然，如果小黑纸板不够大，那就跳过
		if(!(nn-ss+1<=h&&ee-ww+1<=w)) continue;
		int a=max(1,ss-h+1);
		int b=nn;
		int c=max(1,ee-w+1);
		int d=ww;
		for(int i=a;i<=b;i++)
		{
			for(int j=c;j<=d;j++)
			{
				cnt[i][j]--;//如果存在左上角为 (i,j) 的小黑纸板能够覆盖，则统计
			}
		}
	}
```

这样这道题就做完力（喜）我们来看一下全代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=305;
struct Node
{
	int n=305,s=1,w=305,e=1;
}col[MAXN];
bool vis[MAXN];
int H,W,N,h,w;
int cnt[MAXN][MAXN];
int a[MAXN][MAXN];
int main()
{
	scanf("%d %d %d %d %d",&H,&W,&N,&h,&w);
	int colcnt=0;
	for(int i=1;i<=H;i++)
	{
		for(int j=1;j<=W;j++)
		{
			cin>>a[i][j];
		//	printf("SCAN:%d %d %d\n",a[i][j],i,j);
			if(col[a[i][j]].n==305) colcnt++;
			col[a[i][j]].n=min(col[a[i][j]].n,i);
			col[a[i][j]].s=max(col[a[i][j]].s,i);
			col[a[i][j]].w=min(col[a[i][j]].w,j);
			col[a[i][j]].e=max(col[a[i][j]].e,j);
		//	colcnt++;
		}
	}
	for(int i=1;i<=H;i++)
	{
		for(int j=1;j<=W;j++)
		{
			cnt[i][j]=colcnt;
		}
	}
	for(int i=1;i<=N;i++)
	{
		int nn=col[i].n,ss=col[i].s,ww=col[i].w,ee=col[i].e;
	//	printf("%d %d %d %d %d\n",i,nn,ss,ee,ww);
		if(!(nn-ss+1<=h&&ee-ww+1<=w)) continue;
		int a=max(1,ss-h+1);
		int b=nn;
		int c=max(1,ee-w+1);
		int d=ww;
	//	printf("%d %d %d %d %d %d %d %d %d\n",i,nn,ss,ww,ee,a,b,c,d);
		for(int i=a;i<=b;i++)
		{
			for(int j=c;j<=d;j++)
			{
				cnt[i][j]--;
			}
		}
	}
	for(int i=1;i<=H-h+1;i++)
	{
		for(int j=1;j<=W-w+1;j++)
		printf("%d ",cnt[i][j]);
		puts("");
	}
	return 0;
}
                                 
                                 
```



---

## 作者：happybob (赞：0)

## 题意

给定 $H \times W$ 的一个矩形，矩形中每个点有一个不超过 $n$ 的正整数。

你需要对于 $0 \leq i \leq H-h, 0\leq j \leq W-w$ 的所有 $(i,j)$，将 $k < i \leq k +h, p<j\leq j+w$ 的 $(k,p)$ 都在矩形中涂成黑色，求出没有被涂黑的数有多少种，即有多少种不一样的数。

询问的 $(i,j)$ 是独立的，即涂黑操作在每次询问后将会还原。

## 解法

考虑按照题意模拟，复杂度是 $O(n^4)$，显然通不过，我们可以看数据范围，像是一个 $O(n^3)$ 的。

我们可以考虑枚举 $i$，然后可以发现，随着 $j$ 的增加，每次都是将一列的贡献涂成白色，一列涂成黑色，其余的列都被两次同时覆盖。然后就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 305, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

int cnt[N], res;

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int H, W, n, h, w, a[N][N], ans[N][N], rcnt[N];

void add(int x)
{
	if(++cnt[x]==1) res++;
}

void del(int x)
{
	if(--cnt[x]==0) res--;
}
int rres;

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	H=read(),W=read(),n=read(),h=read(),w=read();
	for(int i=1;i<=H;i++)
	{
		for(int j=1;j<=W;j++) a[i][j]=read(), add(a[i][j]);
	}
	for(int i=0;i<=H-h;i++)
	{
		for (int j=1;j<=n;j++) rcnt[j]=cnt[j];
		rres=res;
		int nl=i+1,nr=i+h;
		int kl=1,kr=w;
		for(int j=nl;j<=nr;j++)
		{
			for(int k=kl;k<=kr;k++) del(a[j][k]);
		}
		ans[i][0]=res;
		for(int j=1;j<=W-w;j++)
		{
			for(int k=nl;k<=nr;k++)
			{
				add(a[k][j]);
			}
			int rr=j+w;
			for(int k=nl;k<=nr;k++) del(a[k][rr]);
			ans[i][j]=res;
		}
		for(int i=1;i<=n;i++) cnt[i]=rcnt[i];
		res=rres;
	}
	for(int i=0;i<=H-h;i++)
	{
		for(int j=0;j<=W-w;j++)
		{
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```


---

