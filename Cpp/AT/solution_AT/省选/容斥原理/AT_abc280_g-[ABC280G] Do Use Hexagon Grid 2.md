# [ABC280G] Do Use Hexagon Grid 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc280/tasks/abc280_g

以下のような、無限に広い六角形のグリッドがあります。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc280_g/992f7292cb6316e33ee0c40605e4a519c5d857df.png)

六角形のマスは $ 2 $ つの整数 $ i,j $ を用いて $ (i,j) $ と表されます。  
 マス $ (i,j) $ は以下の $ 6 $ つのマスと辺で隣接しています。

- $ (i-1,j-1) $
- $ (i-1,j) $
- $ (i,j-1) $
- $ (i,j+1) $
- $ (i+1,j) $
- $ (i+1,j+1) $
 
$ 2 $ つのマス $ X,Y $ の距離を、辺で隣接しているマスをたどってマス $ X $ からマス $ Y $ まで移動するときの、移動回数の最小値と定めます。  
 例えばマス $ (0,0) $ とマス $ (1,1) $ の距離は $ 1 $、マス $ (2,1) $ とマス $ (-1,-1) $ の距離は $ 3 $ です。

$ N $ 個のマス $ (X_1,Y_1),\ldots,(X_N,Y_N) $ が与えられます。  
 この $ N $ マスの中から $ 1 $ つ以上のマスを選ぶ方法のうち、選んだマスのうちどの $ 2 $ マスの距離も $ D $ 以下になるようなものは何通りありますか？  
 $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ -10^9\leq\ X_i,Y_i\ \leq\ 10^9 $
- $ 1\leq\ D\ \leq\ 10^{10} $
- $ (X_i,Y_i) $ は相異なる
- 入力は全て整数である
 
### Sample Explanation 1

選ぶマスの集合として考えられるのは $ \{(0,0)\},\{(0,1)\},\{(1,0)\},\{(0,0),(0,1)\},\{(0,0),(1,0)\} $ の $ 5 $ 通りです。

## 样例 #1

### 输入

```
3 1
0 0
0 1
1 0```

### 输出

```
5```

## 样例 #2

### 输入

```
9 1
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2```

### 输出

```
33```

## 样例 #3

### 输入

```
5 10000000000
314159265 358979323
846264338 -327950288
-419716939 937510582
-97494459 -230781640
628620899 862803482```

### 输出

```
31```

# 题解

## 作者：YxYe (赞：6)

# [ATabc280G](https://www.luogu.com.cn/problem/AT_abc280_g)

> 感觉大家的思路都和我不同耶？赶紧写篇题解分享一下吧！

### 题意
在一个六边形网格上有 $n$ 个点，求有多少个点集满足集合内的每对点的距离都不超过 $d$ 。
### 分析
由于是六边形网格，考虑建立一个坐标系，方便描述。

![](https://cdn.luogu.com.cn/upload/image_hosting/mi23hxta.png)

记录 $f[i][x][y]$ 表示点 $i$ 与右限为**点** $x$（点的横坐标）和下限为**点** $y$（点的纵坐标）的区域能够组成的符合要求的点集数量。

如果看不懂可以参照下图的一种情况，点 $i$ 由红框中的绿色区域转移，点 $j$ 由黄框中的绿+蓝色区域转移。其中红/黄边界由点的坐标产生（也就是说只用记录点的编号就可以知道边界的位置）。

初始状态就是 $f[i][x][y]=1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ykxgi22.png)

考虑 **点 $i$ 限制为绿色区域** 如何向 **点 $j$ 限制为绿+蓝色区域** 转移。（如图）

- 当 $i$ 与 $j$ 两点本身超出限制时，无法转移。（即判断橙线与深黄线间的距离是否可以）

- 当 $i$ 与 $j$ 取的两个右限横坐标差或两个下限纵坐标差超出限制，无法转移。（即判断横着的红线与黄线间的距离和斜着的红线的黄线间的距离是否可以）

- 当 $i$ 与 $j$ 取的两个右限纵坐标差/两个下限横坐标差超出限制，则该处的限制只能转移到 $i$ 的对应纵坐标/横坐标。(对应 $j$ 点的转移，若右限的黄线到 $i$ 的距离超过 $d$ 就只能取绿+浅蓝,若下限黄线到 $i$ 的距离超过 $d$ 就只能取绿+深蓝，若都满足就全取)

最后答案记得 $+n$ （自己可以转移给自己）。

### 代码
```cpp
#include<iostream>
#include<algorithm>
#define ll long long
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fp(i,a,b) for(int i=a;i<b;i++)
#define pii pair<ll, ll>
#define fir first
#define sec second
using namespace std;
const int maxn=305,mod=998244353;
ll n,d,f[maxn][maxn][maxn],ans;
pii a[maxn];
int main(){
	cin>>n>>d;
	fo(i,1,n)cin>>a[i].fir>>a[i].sec;
	sort(a+1,a+n+1);
	fo(i,1,n){
		f[i][i][i]=1;
		fp(x,1,i){
			if(a[i].fir-a[x].fir>d)continue;
			fp(y,x,i){
				if(a[i].sec-a[y].sec>d)continue;
				fp(z,x,i){
					if((!f[x][y][z])||((a[i].fir-a[z].fir)-(a[i].sec-a[z].sec)>d))continue;
					(ans+=f[x][y][z])%=mod;
					(f[x][(a[i].sec<a[y].sec)?i:y][(a[i].fir-a[i].sec<a[z].fir-a[z].sec)?i:z]+=f[x][y][z])%=mod;
				}
			}
		}
	}
	cout<<ans+n;
	return 0;
}
```

以上就是本蒟蒻的思路，觉得不错的就点个赞吧！^v^

---

## 作者：enucai (赞：4)

## G - Do Use Hexagon Grid 2

在一个六边形网格上，有 $n$ 个点，同时给定一个 $d$，求有多少个点集，使得集合内的每对点的距离都不超过 $d$。$n\le 300$。

首先考虑从 $(0,0)$ 到点 $(x,y)$ 的距离怎么算。由于 $(x,y)$ 可以向四方向走，可以向 $(1,1)$ 和 $(-1,-1)$ 方向走，所以距离是 $\max(|x|,|y|,|x-y|)$。考虑将一个点 $(x,y)$ 直接映射成一个三元组 $(x,y,x-y)$。那么问题就转化为：在一个三维空间内，有多少个点集是在同一个 $(d+1)\times (d+1)\times (d+1)$ 的立方体内。

考虑钦定前两维的最小值位置，然后双指针去扫第三维在范围内的数。即钦定所有点的前两维为 $[x,x+d],[y,y+d]$。

但是这样会算重，所以考虑做一个小容斥，即 $(x,y)-(x+1,y)-(x,y+1)+(x+1,y+1)$。

最终复杂度 $O(n^3\log n)$，$\log n$ 由于要排序。

提交记录：[link](https://atcoder.jp/contests/abc280/submissions/37001427)。

---

## 作者：Raisetsu41 (赞：3)

两个点之间距离的计算比较复杂，但是发现距离具有平移不变的性质，于是考虑通过每个点与 $(0,0)$ 之间的距离来刻画两点间的距离。   

具体过程可以手玩得到，记 $d_1 = x_1 - y_1, d_2 = y_1 - y_2$ 两点间的距离为 $\max\{\mid d_1 \mid, \mid d_2 \mid, \mid d_1 - d_2 \mid\}$。   
发现这个东西是三维的，于是可以用一个 $d^3$ 的正方体刻画，那么每次框起来的就是一个可行的点集，考虑去重。
于是开始枚举每一个维度上的最小值，记为 $x_0, y_0, z_0$，钦定这些点必须选，如果这些点围起来的点数为 $tot$，则总的答案增加 $2^{tot}$，直接做是 $\Theta(n^4)$ 的，在统计围起来的点数时可以用双指针优化，最后的复杂度是 $\Theta(n^3)$。   

代码稍微有点复杂。   

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("avx2,fma")
#include <cstdio>
#include <iostream>
#include <algorithm>
#define LL long long
#define ULL unsigned long long
using namespace std;
const int Mod = 998244353;
const int MAXN = 2e5 + 5;

template <typename T>
void read(T& x) {
  x = 0; int f = 1; char c = getchar(); while (c < '0' || c > '9') { if (c == '-') f = -f; c = getchar(); }
  while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); } x *= f;
}
template <typename T, typename... Args>
void read (T &x, Args&... Arg) { read (x), read (Arg...); }
int Abs(int x) { return x < 0 ? -x : x; }
template <typename T>
inline T Max(T x, T y) { return x > y ? x : y; }
template <typename T>
inline T Min(T x, T y) { return x < y ? x : y; }

LL n, d, cntx, cnty, totx[MAXN], toty[MAXN];
LL ans, pow2[MAXN], xtmp[MAXN], ytmp[MAXN];
struct Point { LL x, y; } a[MAXN];

bool check(LL u, LL p, LL q) { return a[u].x >= a[p].x && xtmp[a[u].x] <= xtmp[a[p].x] + d && a[u].y >= a[q].y && ytmp[a[u].y] <= ytmp[a[q].y] + d; }

int main() {

  read(n, d);
  pow2[0] = 1;
  for (int i = 1; i <= n; i++) pow2[i] = pow2[i - 1] * 2 % Mod;

  for (int i = 1; i <= n; i++) {
    read(a[i].x, a[i].y);
    xtmp[i] = a[i].x, ytmp[i] = a[i].y;
  }
  sort(xtmp + 1, xtmp + 1 + n), sort(ytmp + 1, ytmp + 1 + n);
  for (int i = 1; i <= n; i++) {
    a[i].x = lower_bound(xtmp + 1, xtmp + 1 + n, a[i].x) - xtmp;
    totx[a[i].x]++, a[i].x += totx[a[i].x] - 1;
    a[i].y = lower_bound(ytmp + 1, ytmp + 1 + n, a[i].y) - ytmp;
    toty[a[i].y]++, a[i].y += toty[a[i].y] - 1;
  }
  sort(a + 1, a + 1 + n, [](const Point& p, const Point& q) { return xtmp[p.x] - ytmp[p.y] < xtmp[q.x] - ytmp[q.y]; });

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) if (check(i, i, j) && check(j, i, j)) {
      int r = 0, s = 0;
      for (int k = 1; k <= n; k++) if (check(k, i, j)) {
        LL tmp = xtmp[a[k].x] - ytmp[a[k].y];
        while (r < n) {
          if (!check(r + 1, i, j)) r++;
          else if (xtmp[a[r + 1].x] - ytmp[a[r + 1].y] <= tmp + d) r++, s++;
          else break;
        }
        if (k <= i && k <= j && tmp + d >= xtmp[a[i].x] - ytmp[a[i].y] && tmp + d >= xtmp[a[j].x] - ytmp[a[j].y]) {
          int now = s;
          if (i == j && j == k) now--;
          else if (i == j || j == k || i == k) now -= 2;
          else now -= 3;
          ans = (ans + pow2[now]) % Mod;
        }
        s--;
      }
    }
  }
  printf("%lld\n", ans);

  return 0;
}
```

---

## 作者：DengDuck (赞：1)

一年前的期末考试赛题，终于补出来了。

对于 @YxYe 的题解进行一点补充（或者说另一种解释）。

首先点可以转换成三维点的形式 $(x,y,x-y)$，然后距离相当于切比雪夫距离。

然后我们设 $F_{i,j,k}$ 表示 $i$，$j$ 和 $k$ 是立方体以 $i,j,k$ 为三个维度的最靠左边的边界的方案数。

接下来暴力维护转移即可。

其实很多题解都在思考怎么优化到 $\mathcal O(n^3)$ 的时间复杂度，其实 $\mathcal O(n^4)$ 常数优秀也是可以快速通过的。

校内 OJ 时限 $1$ 秒不放 $\mathcal O(n^4)$ 过，难受。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
//#define Ls(x) (x<<1)
//#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
//const LL Inf;
const LL N=305;
//const LL M;
const LL Mod=998244353;
//const LF eps;
//const LL P;
LL n,D,F[N][N][N],Ans;
struct Pt
{
	LL X,Y,Z;
}A[N];
int main()
{
	cin>>n>>D;
	for(int i=1;i<=n;i++)
	{
		cin>>A[i].X>>A[i].Y;
		A[i].Z=A[i].X-A[i].Y;
	}
	sort(A+1,A+n+1,[](Pt x,Pt y){
		if(x.X!=y.X)return x.X<y.X;
		if(x.Y!=y.Y)return x.Y<y.Y;
		return x.Z<y.Z;
	});
	for(int i=1;i<=n;i++)
	{
		F[i][i][i]=1;
		for(int x=i-1;x>=1;x--)
		{
			if(A[i].X-A[x].X>D)break;
			for(int y=x;y<i;y++)
			{
				if(A[i].Y-A[y].Y>D)continue;
				for(int z=x;z<i;z++)
				{
					if(!F[x][y][z])continue;
					if(A[i].Z-A[z].Z>D)continue;
					Ans=(Ans+F[x][y][z])%Mod;
					LL a=i,b=i;
					if(A[i].Y>=A[y].Y)a=y;
					if(A[i].Z>=A[z].Z)b=z;
					F[x][a][b]=(F[x][a][b]+F[x][y][z])%Mod;
				}
			}
		}
	}
	Ans=(Ans+n)%Mod;
	cout<<Ans<<endl;
	return 0;
}
//RP++
```

---

## 作者：beauty_son_whm (赞：1)

考虑这么几个性质：

在六角网络中，从 $(0,0)$ 到 $(x,y)$ 的距离是: 
$\max(|x|,|y|,|x-y|)$ 。

证明：对于右上方向和左下方向，我们的 $x,y$ 是同时同向改变的，所以可以先让某一维到位然后再改变另一维。答案是 $\max(|x|,|y|)$ 可以证明的是此时 $|x-y|$ 是小于这个值的，对于右下和左上方向，我们的 $x,y$ 是反向改变的，所以此时的距离可以认为是先改变一维，再改变另一维，答案是 $|x-y|$ 。

从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的距离可以认为是从 $(0,0)$ 到 $(x_2-x_1,y_2-y_1)$ 的距离。这个结论具体证明可以分类讨论，这里不展开了。

所以说，这两个点的距离就是 $\max(|x_2-x_1|,|y_2-y_1|,|(x_2-y_2)-(x_1-y_1)|)$ 。这里设 $c_i=x_i-y_i$ ，那么这个式子本质就在告诉我们，在以 $(x,y,c)$ 构成的立体坐标系中边长 $<=D$ 的正方形所包含的点构成的任意一个点集，自然地，我们会想到枚举这个正方形的三维都最小的点，设其为 $(x,y,z)$ ,计算以这个点出发的正方形的答案，但是这样直接算是会算重的。所以我们钦定这个点集每一维的最小值是 $(x,y,z)$，考虑某个点是否在某一维上等于我们枚举的这个点的那一维。相当于是，根据三个坐标是否是 $(x,y,z)$ 划分出三个集合，从这三个集合里选出某些点使得这些点构成的点集满足上述条件即可。

启发：想到转换距离，转化为正方形的计数，枚举点集每一维的最小值计数，比较巧妙。

---

## 作者：SoyTony (赞：0)

先考虑最短路径是什么？不难发现，题目中走的直线有三条，分别对应在第一维移动、在第二位移动、在一、二维同时移动。

考虑 $(x_1,y_1)$ 与 $(x_1,y_2)$，当 $x_2-x_1$ 与 $y_2-y_1$ 同号时，最短路径显然先同时移动再只移动一维，也就是 $\max(|x_2-x_1|,|y_2-y_1|)$，而异号时，分开移动一定更优，于是此时答案是 $|(x_2-x_1)-(y_2-y_1)|$。

这里为什么把绝对值放在外面？因为这样的写法可以使得无论二者同号与否，距离都可以表示为 $\max(|x_2-x_1|,|y_2-y_1|,|(x_2-x_1)-(y_2-y_1)|)$。

这样似乎把问题转移到空间坐标系上，如果能找到最小的 $x,y,x-y$，那么就是在 $[x,x+D],[y,y+D],[x-y,x-y+D]$ 中计数。

可以先枚举出最小的 $x$，$y$，以此确定有可能合法的点，再依次枚举 $x-y$，可以固定一个区间 $[x-y,x-y+D]$。

注意到这里有严格的下界，于是可以简单容斥（其实不很容斥）的算一下，做到不重不漏即可。

下面代码的计数方法是先考虑前两维下界的来源，再考虑第三维。

```cpp
int n;
ll D;
struct node{
    int a,b,c;
    node()=default;
    node(int a_,int b_,int c_):a(a_),b(b_),c(c_){}
}P[305];
vector<int> Va,Vb,Vc;
int cntab[305],cnta[305],cntb[305],cnt0[305];
int pw[305];
inline int POW(int l,int r,int tmp[]){
    if(l>r) return 1;
    return pw[tmp[r]-tmp[l-1]];
}
int ans;
int main(){
    n=read(),D=read();
    pw[0]=1;
    for(int i=1;i<=n;++i){
        int x=read(),y=read();
        P[i]=node(x,y,x-y);
        Va.push_back(x),Vb.push_back(y),Vc.push_back(x-y);
        pw[i]=pw[i-1]*2%mod;
    }
    sort(Va.begin(),Va.end());
    Va.erase(unique(Va.begin(),Va.end()),Va.end());
    sort(Vb.begin(),Vb.end());
    Vb.erase(unique(Vb.begin(),Vb.end()),Vb.end());
    sort(Vc.begin(),Vc.end());
    Vc.erase(unique(Vc.begin(),Vc.end()),Vc.end());
    for(int i=1;i<=n;++i) P[i].c=lower_bound(Vc.begin(),Vc.end(),P[i].c)-Vc.begin()+1;
    for(int i=0;i<Va.size();++i){
        for(int j=0;j<Vb.size();++j){
            int mina=Va[i],minb=Vb[j];
            for(int k=1;k<=Vc.size();++k) cntab[k]=0,cnta[k]=0,cntb[k]=0,cnt0[k]=0;
            for(int k=1;k<=n;++k){
                if(P[k].a<mina||P[k].a>mina+D||P[k].b<minb||P[k].b>minb+D) continue;
                if(P[k].a==mina&&P[k].b==minb) ++cntab[P[k].c];
                else if(P[k].a==mina) ++cnta[P[k].c];
                else if(P[k].b==minb) ++cntb[P[k].c];
                else ++cnt0[P[k].c];
            }
            for(int k=1;k<=Vc.size();++k){
                cntab[k]+=cntab[k-1];
                cnta[k]+=cnta[k-1];
                cntb[k]+=cntb[k-1];
                cnt0[k]+=cnt0[k-1];
            }
            for(int k=0;k<Vc.size();++k){
                int l=k+1;
                int r=upper_bound(Vc.begin(),Vc.end(),Vc[k]+D)-Vc.begin();
                int now;
                if(l!=r){
                    now=1ll*(POW(l,l,cntab)-1)*POW(l+1,r,cntab)%mod*POW(l,r,cnta)%mod*POW(l,r,cntb)%mod*POW(l,r,cnt0)%mod;
                    ans=(ans+now)%mod;
                    now=1ll*(POW(l+1,r,cntab)-1)*(POW(l,l,cnta)-1)%mod*POW(l+1,r,cnta)%mod*POW(l,r,cntb)%mod*POW(l,r,cnt0)%mod;
                    ans=(ans+now)%mod;
                    now=1ll*(POW(l+1,r,cntab)-1)*POW(l+1,r,cnta)%mod*(POW(l,l,cntb)-1)%mod*POW(l+1,r,cntb)%mod*POW(l,r,cnt0)%mod;
                    ans=(ans+now)%mod;
                    now=1ll*(POW(l+1,r,cntab)-1)*POW(l+1,r,cnta)%mod*POW(l+1,r,cntb)%mod*(POW(l,l,cnt0)-1)%mod*POW(l+1,r,cnt0)%mod;
                    ans=(ans+now)%mod;
                    now=1ll*(POW(l,l,cnta)-1)*POW(l+1,r,cnta)%mod*(POW(l,r,cntb)-1)%mod*POW(l,r,cnt0)%mod;
                    ans=(ans+now)%mod;
                    now=1ll*(POW(l+1,r,cnta)-1)*(POW(l,l,cntb)-1)%mod*POW(l+1,r,cntb)%mod*POW(l,r,cnt0)%mod;
                    ans=(ans+now)%mod;
                    now=1ll*(POW(l+1,r,cnta)-1)*(POW(l+1,r,cntb)-1)%mod*(POW(l,l,cnt0)-1)%mod*POW(l+1,r,cnt0)%mod;
                    ans=(ans+now)%mod;
                }
                else{
                    now=1ll*(POW(l,l,cntab)-1)*POW(l,l,cnta)%mod*POW(l,l,cntb)%mod*POW(l,l,cnt0)%mod;
                    ans=(ans+now)%mod;
                    now=1ll*(POW(l,l,cnta)-1)*(POW(l,l,cntb)-1)%mod*POW(l,l,cnt0)%mod;
                    ans=(ans+now)%mod;
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

