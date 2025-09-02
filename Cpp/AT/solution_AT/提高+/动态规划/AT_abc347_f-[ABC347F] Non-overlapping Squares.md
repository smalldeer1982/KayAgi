# [ABC347F] Non-overlapping Squares

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_f

$ N\times\ N $ のマス目があり、上から $ i $ 行目、左から $ j $ 列目 $ (1\leq\ i,j\leq\ N) $ のマスには整数 $ A\ _\ {i,j} $ が書かれています。

整数 $ M $ が与えられます。 $ M\times\ M $ のマス目を重ならないように $ 3 $ つ選ぶときの、選んだマス目に書かれている整数の総和としてありえる最大値を求めてください。

 問題の厳密な定義 整数の $ 6 $ つ組 $ (i\ _\ 1,j\ _\ 1,i\ _\ 2,j\ _\ 2,i\ _\ 3,j\ _\ 3) $ が次の $ 3 $ つの条件を満たしているとき、**良い $ 6 $ つ組**ということにします。 - $ 1\leq\ i\ _\ k\leq\ N-M+1\ (k=1,2,3) $
- $ 1\leq\ j\ _\ k\leq\ N-M+1\ (k=1,2,3) $
- $ k\neq\ l\ (k,l\in\lbrace1,2,3\rbrace) $ ならば、$ \lbrace(i,j)\mid\ i\ _\ k\leq\ i\lt\ i\ _\ k+M\wedge\ j\ _\ k\leq\ j\lt\ j\ _\ k+M\rbrace $ と $ \lbrace(i,j)\mid\ i\ _\ l\leq\ i\lt\ i\ _\ l+M\wedge\ j\ _\ l\leq\ j\lt\ j\ _\ l+M\rbrace $ に共通部分はない
 
 良い $ 6 $ つ組 $ (i\ _\ 1,j\ _\ 1,i\ _\ 2,j\ _\ 2,i\ _\ 3,j\ _\ 3) $ に対する値 $ \displaystyle\ \sum\ _\ {k=1}\ ^\ 3\sum\ _\ {i=i\ _\ k}\ ^\ {i\ _\ k+M-1}\sum\ _\ {j=j\ _\ k}\ ^\ {j\ _\ k+M-1}A\ _\ {i,j} $ の最大値を求めてください。 この問題の制約のもとで良い $ 6 $ つ組が存在することが示せます。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 1000 $
- $ 1\leq\ M\leq\ N/2 $
- $ 0\leq\ A\ _\ {i,j}\leq10\ ^\ 9 $
- 入力はすべて整数
 
### Sample Explanation 1

与えられたグリッドから、以下の図のように $ 3\times3 $ のマス目を $ 3 $ つ選ぶと（これは $ (i\ _\ 1,j\ _\ 1,i\ _\ 2,j\ _\ 2,i\ _\ 3,j\ _\ 3)=(1,5,2,1,5,2) $ とすることに対応します）、選んだマス目に書かれている数の合計は $ 154 $ となります。 ![](https://img.atcoder.jp/abc347/f24ee82455befb7c9af500437f79cde8.png) 問題文の条件を満たす選び方であって選んだマス目に書かれている数の合計が $ 155 $ 以上であるものは存在しないため、$ 154 $ を出力してください。

### Sample Explanation 2

以下のように選ぶのが最適です。 ![](https://img.atcoder.jp/abc347/d380b6de908ba5259451d798e7851be3.png)

### Sample Explanation 3

以下のように選ぶのが最適です。 ![](https://img.atcoder.jp/abc347/592c9536ace6712dd7532131b8da15be.png)

## 样例 #1

### 输入

```
7 3
3 1 4 1 5 9 2
6 5 3 5 8 9 7
9 3 2 3 8 4 6
2 6 4 3 3 8 3
2 7 9 5 0 2 8
8 4 1 9 7 1 6
9 3 9 9 3 7 5```

### 输出

```
154```

## 样例 #2

### 输入

```
7 1
3 1 4 1 5 9 2
6 5 3 5 8 9 7
9 3 2 3 8 4 6
2 6 4 3 3 8 3
2 7 9 5 0 2 8
8 4 1 9 7 1 6
9 3 9 9 3 7 5```

### 输出

```
27```

## 样例 #3

### 输入

```
16 4
74 16 58 32 97 52 43 51 40 58 13 24 65 11 63 29
98 75 40 77 15 50 83 85 35 46 38 37 56 38 63 55
95 42 10 70 53 40 25 10 70 32 33 19 52 79 74 58
33 91 53 11 65 63 78 77 81 46 81 63 11 82 55 62
39 95 92 69 77 89 14 84 53 78 71 81 66 39 96 29
74 26 60 55 89 35 32 64 17 26 74 92 84 33 59 82
23 69 10 95 94 14 58 58 97 95 62 58 72 55 71 43
93 77 27 87 74 72 91 37 53 80 51 71 37 35 97 46
81 88 26 79 78 30 53 68 83 28 59 28 74 55 20 86
93 13 25 19 53 53 17 24 69 14 67 81 10 19 69 90
88 83 62 92 22 31 27 34 67 48 42 32 68 14 96 87
44 69 25 48 68 42 53 82 44 42 96 31 13 56 68 83
63 87 24 75 16 70 63 99 95 10 63 26 56 12 77 49
94 83 69 95 48 41 40 97 45 61 26 38 83 91 44 31
43 69 54 64 20 60 17 15 62 25 58 50 59 63 88 70
72 95 21 28 41 14 77 22 64 78 33 55 67 51 78 40```

### 输出

```
3295```

# 题解

## 作者：MrPython (赞：7)

三个矩形之间的相对位置可以用这两种情况概括，其他的所有情况都可以由原矩阵旋转而得：![image.png](https://www.imghost.net/ib/ZO7kF08yWwAOIHC_1726406977.png)

在此之前，我们先将 $b_{x,y}=\sum_{i=x}^{x+k-1}\sum_{j=y}^{y+k-1}a_{i,j}\space(x\leq n-k+1,y\leq n-k+1)$ 用二维前缀和预处理出来。时间复杂度 $O(n^2)。$

先来看求第一种情况。先预处理求任意两行之间的最大值（$d_{x,s}=\max_{i=x}^{x+s}\max_{j=1}^{n-k+1}b_{i,j}$，可以求出每行的最大值后对着这个数组 DP）。然后，枚举中间的两条分割线，求三个区间内的最大值之和，注意区间间距离不应小于 $k$。总时间复杂度 $O(n^2)$。

对于第二种，DP 预处理出左上角矩形的最大值 $ul_{x,y}=\max_{i=1}^{x}\max_{j=1}^{y}b_{i,j}$、右上角矩形最大值 $ur_{x,y}=\max_{i=1}^{x}\max_{j=y}^{n-k+1}b_{i,j}$ 与下方若干行的最大值 $d_x=\max_{i=x}^{n-k+1}\max_{j=1}^{n-k+1}b_{i,j}$。枚举两条线求即可。时间复杂度 $O(n^2)$。

以上操作都需要旋转 4 次分别进行。总程序时间复杂度 $O(n^2)$。
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
template<typename T> class PrefixSum2D{
    vector<vector<T>> sum;
public:
    template<typename S>
    PrefixSum2D(vector<vector<S>> const& a):sum(a.size()+1,vector<T>(a.front().size()+1)){
        size_t const n=a.size(),m=a.front().size();
        for (size_t i=0;i<n;i++) for (size_t j=0;j<m;j++)
            sum[i+1][j+1]=sum[i+1][j]+sum[i][j+1]-sum[i][j]+a[i][j];
    }
    T get_sum(size_t ax,size_t ay,size_t bx,size_t by) const{
        return sum[bx][by]+sum[ax][ay]-sum[ax][by]-sum[bx][ay];
    }
};
uli f(size_t n,size_t k,vector<vector<uli>> const& a){
    vector<vector<uli>> ul(n,vector<uli>(n)),
                        ur(n,vector<uli>(n));
    ul[0][0]=a[0][0];
    for (size_t i=1;i<n;++i) ul[i][0]=max(ul[i-1][0],a[i][0]);
    for (size_t j=1;j<n;++j) ul[0][j]=max(ul[0][j-1],a[0][j]);
    for (size_t i=1;i<n;++i) for (size_t j=1;j<n;++j)
        ul[i][j]=max({ul[i-1][j],ul[i][j-1],a[i][j]});
    ur[0][n-1]=a[0][n-1];
    for (size_t i=1;i<n;++i) ur[i][n-1]=max(ur[i-1][n-1],a[i][n-1]);
    for (size_t j=n-2;j<n;--j) ur[0][j]=max(ur[0][j+1],a[0][j]);
    for (size_t i=1;i<n;++i) for (size_t j=n-2;j<n;--j)
        ur[i][j]=max({ur[i-1][j],ur[i][j+1],a[i][j]});
    vector<uli> d(n);
    d[n-1]=*max_element(a[n-1].cbegin(),a[n-1].cend());
    for (size_t i=n-2;i<n;--i) d[i]=max(d[i+1],*max_element(a[i].cbegin(),a[i].cend()));
    uli ans=numeric_limits<uli>::min();
    for (size_t i=0;i+k<n;++i) for (size_t j=0;j+k<n;++j)
        ans=max(ans,ul[i][j]+ur[i][j+k]+d[i+k]);
    return ans;
}
uli g(size_t n,size_t k,vector<vector<uli>> const& a){
    vector<uli> mx(n);
    for (size_t i=0;i<n;++i) mx[i]=*max_element(a[i].begin(),a[i].end());
    vector<vector<uli>> d(n);
    for (size_t i=0;i<n;++i){
        d[i].push_back(mx[i]);
        for (size_t j=i+1;j<n;++j)
            d[i].push_back(max(mx[j],d[i].back()));
    }
    uli ans=numeric_limits<uli>::min();
    for (size_t i=0;i+k<n;++i) for (size_t j=i+k;j+k<n;++j)
        ans=max(ans,d[0][i-0]+d[i+k][j-(i+k)]+d[j+k][n-1-(j+k)]);
    return ans;
}
vector<vector<uli>> rotate(size_t n,vector<vector<uli>> const& x){
    vector<vector<uli>> y(n,vector<uli>(n));
    for (size_t i=0;i<n;++i) for (size_t j=0;j<n;++j)
        y[i][j]=x[j][n-i-1];
    return y;
}
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m;cin>>n>>m;
    vector<vector<ui>> a(n,vector<ui>(n));
    for (vector<ui>& i:a) for (ui& j:i) cin>>j;
    size_t k=n-m+1;
    vector<vector<uli>> b(k,vector<uli>(k));
    {
        PrefixSum2D<uli> s(a);
        for (size_t i=0;i<k;++i) for (size_t j=0;j<k;++j)
            b[i][j]=s.get_sum(i,j,i+m,j+m);
    }
    cout<<max({f(k,m,b),g(k,m,b),
               f(k,m,rotate(k,b)),g(k,m,rotate(k,b)),
               f(k,m,rotate(k,rotate(k,b))),g(k,m,rotate(k,rotate(k,b))),
               f(k,m,rotate(k,rotate(k,rotate(k,b)))),g(k,m,rotate(k,rotate(k,rotate(k,b))))});
    return 0;
}
```

---

## 作者：wangbinfeng (赞：7)

[![](https://img.shields.io/badge/题目-P3625_[APIO2009]_采油区域-green)
![](https://img.shields.io/badge/难度-提高+/省选−-blue)
![](https://img.shields.io/badge/考点-分类讨论、前缀和-yellow)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/P3625)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)    
[![](https://img.shields.io/badge/题目-AT__abc347__e_[ABC347F]_Non—overlapping_Squares-green)
![](https://img.shields.io/badge/难度-暂无评定（提高+/省选−）-blue)
![](https://img.shields.io/badge/考点-分类讨论、前缀和-yellow)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/AT_abc347_f)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009) 

-----------
说明：ABC347F 是 P3625 的弱化版，故本题解同时讲解两道题目。特别地，$N_{本题解}=N_{P3625}=N_{ABC347F},M_{本题解}=M_{P3625}=N_{ABC347F},K_{本题解}=K_{P3625}=M_{ABC347F}$。

枚举每个点 $S\left(i,j\right),1\le i\le N,1\le j\le M$，可以发现对于每个点有且只有 $6$ 种情况，分别是：
```
┏━┳━┳━┓　　　┏━━━━━┓
┃　┃　┃　┃　　　┃　　Ａ　　┃
┃　┃　┃　┃　　　┣━━━━━┫
┃Ａ┃Ｓ┃Ｂ┃　　　┃　　Ｓ　　┃
┃　┃　┃　┃　　　┣━━━━━┫
┃　┃　┃　┃　　　┃　　Ｂ　　┃
┗━┻━┻━┛　　　┗━━━━━┛
　【情况一】　　　　　【情况二】
┏━━┳━━┓　　　┏━━━━━┓
┃　　┃　　┃　　　┃　　　　　┃
┃　Ｓ┃Ａ　┃　　　┃　　Ｓ　　┃
┣━━┻━━┫　　　┣━━┳━━┫
┃　　Ｂ　　┃　　　┃　Ａ┃Ｂ　┃
┃　　　　　┃　　　┃　　┃　　┃
┗━━━━━┛　　　┗━━┻━━┛
　【情况三】　　　　　【情况四】
┏━━┳━━┓　　　┏━━┳━━┓
┃　　┃　　┃　　　┃　　┃　　┃
┃　Ｓ┃　　┃　　　┃　　┃Ａ　┃
┣━━┫Ｂ　┃　　　┃　Ｓ┣━━┫
┃　Ａ┃　　┃　　　┃　　┃Ｂ　┃
┃　　┃　　┃　　　┃　　┃　　┃
┗━━┻━━┛　　　┗━━┻━━┛
　【情况五】　　　　　【情况六】
```
分别计算六种情况的最大值，时间复杂度为 $\Theta\left(NMK^2\right)$，无法承受。

考略前缀和，用 $s_{i,j}$ 表示右下角为 $S\left(i,j\right)$，大小为 $K\times K$ 的正方形数字之和。用类似动态规划的做法，记录下每个点左上、左下、右上、右下四个方向的大小为 $K\times K$ 的正方形数字之和最大值。时间复杂度优化为 $\Theta\left(NM\right)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#ifndef PROBLEM
#define PROBLEM 【这里选填数3625或347表示题号】
#endif
const int maxn=1509;
int n,m,k,ans,sum[maxn][maxn],dat[4][maxn][maxn];
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#if defined(PROBLEM) && (PROBLEM == 3625)
	cin>>n>>m>>k;
#elif defined(PROBLEM) && (PROBLEM == 347)
	cin>>n>>k,m=n;
#else
	throw("[ERROR] The code does not target either P3625 or ABC347F and cannot be run for the time being.");
#endif
	for(int i=1;i<=n;i++)for(int j=1,x;j<=m;j++)cin>>x,sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+x;
	for(int i=n;i>=k;i--)for(int j=m;j>=k;j--)sum[i][j]-=sum[i-k][j]+sum[i][j-k]-sum[i-k][j-k];
	for(int i=k;i<=n;i++)for(int j=k;j<=m;j++)dat[0][i][j]=max({sum[i][j],dat[0][i-1][j],dat[0][i][j-1]});
	for(int i=k;i<=n;i++)for(int j=m-k+1;j>=1;j--)dat[1][i][j]=max({sum[i][j+k-1],dat[1][i-1][j],dat[1][i][j+1]});
	for(int i=n-k+1;i>=1;i--)for(int j=k;j<=m;j++)dat[2][i][j]=max({sum[i+k-1][j],dat[2][i+1][j],dat[2][i][j-1]});
	for(int i=n-k+1;i>=1;i--)for(int j=m-k+1;j>=1;j--)dat[3][i][j]=max({sum[i+k-1][j+k-1],dat[3][i+1][j],dat[3][i][j+1]});
	for(int i=k;i<=n;i++)for(int j=k;j<=m;j++)ans=max(ans,dat[0][i-k][m]+dat[2][i+1][m]+sum[i][j]);//情况一
	for(int i=k;i<=n;i++)for(int j=k;j<=m;j++)ans=max(ans,dat[0][n][j-k]+dat[1][n][j+1]+sum[i][j]);//情况二 
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans=max(ans,dat[0][i][j]+dat[1][i][j+1]+dat[2][i+1][m]);//情况三 
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans=max(ans,dat[0][i][m]+dat[2][i+1][j]+dat[3][i+1][j+1]);//情况四 
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans=max(ans,dat[0][i][j]+dat[1][n][j+1]+dat[2][i+1][j]);//情况五 
	for(int i=1;i<=n;i++)for(int j=k;j<=m;j++)ans=max(ans,dat[0][n][j]+dat[1][i][j+1]+dat[3][i+1][j+1]);//情况六 
	cout<<ans;
}
```

---

## 作者：elbissoPtImaerD (赞：6)

不交不好处理，尝试用若干条线将 $3$ 个正方形划开成几个独立的问题做。

首选用直线划分，发现我们用两条线段即可。

证明就是考虑不交等价于在水平方向投影不交 或 竖直方向不交，在不交的部分划线即可。

然后就是 $6$ 种情况（抱走官方题解图）
![](https://img.atcoder.jp/abc347/c8c4557905764a04a59ff89c7b249746.png)

对于每种情况，枚举两条线的位置，我们只需求解同色矩形中的最大权 $m \times m$ 方阵即可。

前缀和后转化为静态矩形最值，但是由于查询矩形是特殊的，所以我们可以通过 $O(n^2)$ 预处理前缀最值做到 $O(1)$ 回答。


有一些细节。

```cpp
const LL infLL=(LL)4e18;
il void Solve()
{
  int n,m,K;rd(n),rd(m),K=n-m+1;
  auto a=[&]
  {
    ve<ve<LL>>a(n,ve<LL>(n)),b(K,ve<LL>(K));
    for(auto&f:a) for(LL&x:f) rd(x);
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
      if(i) a[i][j]+=a[i-1][j];
      if(j) a[i][j]+=a[i][j-1];
      if(i&&j) a[i][j]-=a[i-1][j-1];
    }
    for(int i=0;i<K;++i) for(int j=0;j<K;++j) {
      // [i,i+m) & [j,j+m)
      int I=i+m-1,J=j+m-1;
      b[i][j]=a[I][J];
      if(i) b[i][j]-=a[i-1][J];
      if(j) b[i][j]-=a[I][j-1];
      if(i&&j) b[i][j]+=a[i-1][j-1];
    }
    return b;
  }();
  ve<LL>mxi(K),mxj(K);
  ve<ve<LL>>mif(K,ve<LL>(K+1,-infLL)),mjf=mif;
  for(int i=0;i<K;++i) for(int j=0;j<K;++j) cx(mxi[i],a[i][j]),cx(mxj[j],a[i][j]);
  for(int l=0;l<K;++l) for(int r=l+1;r<=K;++r) mif[l][r]=max(mif[l][r-1],mxi[r-1]);
  for(int l=0;l<K;++l) for(int r=l+1;r<=K;++r) mjf[l][r]=max(mjf[l][r-1],mxj[r-1]);
  ve<ve<ve<LL>>>mx(4,ve<ve<LL>>(K,ve<LL>(K,-infLL)));
  // 0 1
  // 3 2
  const int fx[]={-1,-1,1,1},fy[]={-1,1,1,-1};
  for(int k=0;k<4;++k) {
    mx[k]=a;
    for(int i=fx[k]>0?K-1:0;0<=i&&i<K;i-=fx[k])
      for(int j=fy[k]>0?K-1:0;0<=j&&j<K;j-=fy[k]) {
        int I=i+fx[k],J=j+fy[k];
        if(0<=I&&I<K) cx(mx[k][i][j],mx[k][I][j]);
        if(0<=J&&J<K) cx(mx[k][i][j],mx[k][i][J]);
      }
  }
  LL ans=0;
  auto _Q=[&](int k,int l,int r){return assert(l<r),k?mjf[l][r]:mif[l][r];};
  for(int i=m;i<=n-m;++i) for(int j=i+m;j<=n-m;++j) {
    // [0,i) [i,j) [j,n) -> [0,i-m] [i,j-m] [j,n-m]
    for(int k:{0,1}) cx(ans,_Q(k,0,i-m+1)+_Q(k,i,j-m+1)+_Q(k,j,n-m+1));
  }
  // cross
  for(int i=m;i<=n-m;++i) for(int j=m;j<=n-m;++j) {
    // [0,x) [x,n) -> [0,x-m] [x,n-m]
    cx(ans,_Q(0,0,i-m+1)+mx[3][i][j-m]+mx[2][i][j]);
    cx(ans,_Q(0,i,n-m+1)+mx[0][i-m][j-m]+mx[1][i-m][j]);
    cx(ans,_Q(1,0,j-m+1)+mx[1][i-m][j]+mx[2][i][j]);
    cx(ans,_Q(1,j,n-m+1)+mx[0][i-m][j-m]+mx[3][i][j-m]);
  }
  wrt(ans);
  return;
}
```
[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc347/submissions/51934454)

---

## 作者：HHH6666666666 (赞：2)

正方形的数量很少，不妨考虑一下三个正方形的可能摆放方式。

对于其中任意两个正方形有个很显然的性质：至少存在一条竖线或横线，使两个正方形分别在其两侧。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/23nqk0qq.png)

如果只考虑这两个正方形，可以通过枚举这条线 + 前后缀最大值轻松维护。

推广到三个正方形有：至少存在一条竖线或横线，使其中一个正方形在一侧，另外两个在另一侧。通过枚举这条线将这个正方形分割出来，再枚举剩下两个正方形的分界线即可得到 $O(n^2)$ 做法。

官方题解中的六张图对应了两条分割线的六种状态：

![](https://img.atcoder.jp/abc347/c8c4557905764a04a59ff89c7b249746.png)

赛时忘记考虑 1、4 两种情况也能通过，不好评价。

---

## 作者：xpz0525 (赞：1)

### \[ABC347F] Non-overlapping Squares 题解

在博客 [here](https://www.luogu.com.cn/article/fubkr1cz) 食用更佳哦 ~~*这题有点小难。。。*~~

以下是正文部分：

---

**先**注意到本题的**数据范围**要求我们必须满足 $O(n^2)$ 或多一些 $\log$ 的时间复杂度，**如果**单是枚举一个坐标就要 $O(n^2)$ 的时间复杂度，因此我们一定需要**加上**一些**预处理**才能解决本题。

首先我们不妨考虑枚举其中一个 $M \times M$ 的网格，然后考虑用接近常数时间的方法去找到**其他两个不重叠的** $M \times M$ 网格。但是我们并没有什么好办法能一次性找到两个，因为这可能会牵扯到要找的这两个网格重叠的问题。

如何**避免**另外两个网格**重叠**呢？这便是本题的关键点。要解决这个问题需要先推出一个关键性质：对于任何一个选取三个网格的方案，我们总是可以用**两条平行于坐标轴的线**将三个网格划分到三个区域内。这可以使用**反证法**证出。

一共有哪些分割方法呢？我们可以先确定第一条线的方向，再去枚举第二条线的方向 / 相对第一条线的位置，得出一共有 $6$ 个方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/pq3f7qvd.png)

那么这样就非常好解决了，我们只要先使用**前缀和 + 差分**求出所有网格 $M \times M$ 的数字和，然后分别对 左上 / 右上 / 左下 / 右下 四个方向维护一个“前缀” 最大值。

例如右上方向，我们维护一个 $tr_{i,j}$ 代表第 $i$ 行及以上，第 $j$ 列及右侧的最大 $M \times M$ 网格值。然后枚举两根分界线，即可 $O(1)$ 求出当前分界线情况下选取三个矩阵的最大值。最终时间复杂度为预处理 $O(N^2)$，枚举分界线 $O(N^2)$。下方示例代码中对于每个情况枚举的坐标可以参考下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/aik5daac.png)

思路讲解完了，以下是 **AC** 代码（还可以**参考注释**）：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n,m,a[1002][1002]; 
ll pre[1002][1002],sum[1002][1002]; 
ll tl[1002][1002],tr[1002][1002],bl[1002][1002],br[1002][1002]; 
int main()
{ 
    cin>>n>>m; 
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j]; 
    // 前缀和，pre[i][j]代表前i行前j列的数字之和 
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) pre[i][j]=pre[i-1][j]+pre[i][j-1]+a[i][j]-pre[i-1][j-1];  
    // 差分求出 sum[i][j]，代表以(i,j)为右下角坐标的m*m网格内数字之和
    for(int i=m;i<=n;i++) for(int j=m;j<=n;j++) sum[i][j]=pre[i][j]-pre[i-m][j]-pre[i][j-m]+pre[i-m][j-m];
    // 左上角的最大值，tl[i][j]代表在<=i行，<=j列的区域内，最大的m*m网格数字之和 
    for(int i=m;i<=n;i++) for(int j=m;j<=n;j++) tl[i][j]=max({tl[i][j-1],tl[i-1][j],sum[i][j]}); 
    // 右上角     tr[i][j]代表在<=i行，>=j列的区域
    for(int i=m;i<=n;i++) for(int j=n-m+1;j>=1;j--)tr[i][j]=max({tr[i][j+1],tr[i-1][j],sum[i][j+m-1]});
    // 左下角       代表>=i行，<=j列 
    for(int i=n-m+1;i>=1;i--) for(int j=m;j<=n;j++)bl[i][j]=max({bl[i+1][j],bl[i][j-1],sum[i+m-1][j]}); 
    // 右下角      代表>=i行，>=j 列 
    for(int i=n-m+1;i>=1;i--) for(int j=n-m+1;j>=1;j--)br[i][j]=max({br[i+1][j],br[i][j+1],sum[i+m-1][j+m-1]}); 
    ll ans=0; 
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
	{ 
        // 横向切分，此时i,j代表中间m*m矩阵的右下角坐标 
        if(i-m>=m && i+m<=n && j>=m) 
            ans=max(ans,sum[i][j]+tr[i-m][1]+br[i+1][1]); 
        // 纵向切分，此时i,j代表中间m*m矩阵的右下角坐标
        if(i>=m && j-m>=m && j+m-1<=n) 
           ans=max(ans,sum[i][j]+bl[1][j-m]+br[1][j+1]); 
        // i,j 代表中间分割点右下角的坐标 
        if(i-1>=m  &&  i+m-1<=n  &&  j-1>=m && j+m-1<=n)
		{ 
            // 第2种情况 
            ans=max(ans,br[i][j]+bl[i][j-1]+tr[i-1][1]); 
            // 第3种情况 
            ans=max(ans,br[i][1]+tl[i-1][j-1]+tr[i-1][j]); 
            // 第5种情况 
            ans=max(ans,br[1][j]+tl[i-1][j-1]+bl[i][j-1]); 
            // 第6种情况
            ans=max(ans,br[i][j]+bl[1][j-1]+tr[i-1][j]);  
        } 
    } 
    cout<<ans;
}
````

---

## 作者：EmptyAlien (赞：0)

# 前置芝士

- 普通 ST 表，普通前缀和

# 题意

- 给定一个 $n\times n$ 的方阵 $a$。

- 在 $a$ 中不重叠地选 $3$ 个 $m\times m$ 的方阵。

- 求这 $3$ 个方阵内的数之和最大值。

- $1 \le n \le 1000$

# 思想

第一眼就是很恶心的分类讨论。

我们不可能 $3$ 个矩阵同时搞，非常麻烦，那我们就**把 $a$ 切成 $3$ 份**。

很明显，对于任意可能的解，我们都能切两刀把 $a$ 切成 $3$ 部分然后每个部分都包含一个矩阵。

切法有 $6$ 种，这里放张图。（不要问我这张图是从哪来的）

![](https://img.atcoder.jp/abc347/c8c4557905764a04a59ff89c7b249746.png)

这样我们就把问题转化为了**求一个子矩阵内的最大子矩阵和**。

如果直接跑类似最大子段和和的话就会 TLE，那怎么办呢？

子矩阵和我们就先做个前缀和。

注意这里是二维的，我们照着一维前缀和来弄，$sum_{i,j}$ 表示**以 $(i,j)$ 为右下角，$(1, 1)$ 为左上角的矩阵的元素和**。

```
|-------------|
|         |   |
|         |   |
|         |   |
|---------|---|
|         |i,j|
|---------|---|
```

根据上面的图我们可以得出以下结论：

$$
sum_{i, j}=sum_{i-1,j}+sum_{i,j-1}-sum_{i-1,j-1}+a_{i,j}
$$

也就是容斥原理，$sum_{i-1,j}+sum_{i,j-1}$ 后 $sum_{i-1,j-1}$ 会算两次就减去一次就行了。

如何查询呢？

```
|-------------|
|    |        |
|----|--------|
|    |p,q     |
|    |        |
|    |     i,j|
|----|--------|
```

观察上面的图，还是容斥原理。

$$
Ans=sum_{i,j} - sum_{p - 1, j} - sum_{i, q - 1} + sum_{p - 1, q - 1}
$$

我们这样就完成了前缀和，并且可以 $O(1)$ 查询了。

接下来怎么办呢？

仔细观察以下，我们发现：每个 $m\times m$ 的矩阵的位置在 $a$ 中也是一个矩阵的布局。

So?

我们把每个 $m\times m$ 的矩阵的和都算出来然后按照位置将矩阵的和当成元素扔到另一个矩阵里。

问题变成了：查询**子矩阵内的最大值**。

是不是很眼熟？

这不是 ST 表干的事吗?

但是这是二维的，所以我们要弄一弄二维 ST 表。

正常的 ST 表 $st_{i,j}$ 表示 $i$ 到 $i + 2^j - 1$ 的最大值。

那我们的二维 ST 表就简单粗暴复制一下。

$st_{i,j,p,q}$ 表示以 $(i,j)$ 为左上角，$(i+2^p-1, j+2^q-1)$ 为右下角的矩阵的最大值。

如何构建呢？

如果它的 $p$ 不等于 $0$ 也就是这个矩阵的宽不为 $1$ 那我们可以把这个矩阵拆成左右两个矩阵来更新。

但如果 $p$ 等于 $0$ 的话我们就把它拆成上下两个矩阵进行更新，也就是：

$$
st_{i,j,p,q}=\left\{
\begin{array}{rcl}
\max\left\{st_{i, j, p, q-1}, st_{i, j + 2^{q-1}, p, q-1}\right\} &     & p=0\\

\max\left\{st_{i, j, p-1, q}, st_{i + 2^{p-1}, j, p-1, q}\right\} &     & p\neq 0\\
\end{array}
\right.
$$

如何查询呢？

我们类似普通 ST 表，把查询的矩阵拆成4个完全覆盖了的子矩阵然后取最值。

也就是：

$$
Ans=\max\left\{st_{x1, y1, p, q}, st_{x2 - 2^p + 1, y1, p, q}, st_{x1, y2 - 2^q + 1, p, q}, st_{x2 - 2^p + 1, y2 - 2^q + 1, p, q} \right\}
$$

就这样，问题解决了！

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1005;
constexpr long long INF = 1e18;

int n, m;

long long st[MAXN][MAXN][11][11];

long long val[MAXN][MAXN];

void build_prefix_sum() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            val[i][j] += val[i - 1][j] + val[i][j - 1] - val[i - 1][j - 1];
}

long long ask_prefix_sum(int x, int y) {
    x--, y--;
    return val[x + m][y + m] - val[x][y + m] - val[x + m][y] + val[x][y];
}

void build_sparse_table() {
    for (int i = 1; i <= n - m + 1; i++)
        for (int j = 1; j <= n - m + 1; j++)
            st[i][j][0][0] = ask_prefix_sum(i, j);
    for (int p = 0; p < 11; p++) {
        for (int q = 0; q < 11; q++) {
            if (p || q) {
                for (int i = 1; i <= n - m - (1 << p) + 2; i++) {
                    for (int j = 1; j <= n - m - (1 << q) + 2; j++) {
                        if (p == 0)
                            st[i][j][p][q] = max(st[i][j][p][q - 1], st[i][j + (1 << (q - 1))][p][q - 1]);
                        else
                            st[i][j][p][q] = max(st[i][j][p - 1][q], st[i + (1 << (p - 1))][j][p - 1][q]);
                    }
                }
            }
        }
    }
}

long long ask_sparse_table(int x1, int y1, int x2, int y2) {
    if (x2 - x1 + 1 < m)
        return -INF;
    if (y2 - y1 + 1 < m)
        return -INF;
    x2 -= m - 1;
    y2 -= m - 1;
    int p = __lg(x2 - x1 + 1);
    int q = __lg(y2 - y1 + 1);
    long long m1 = st[x1][y1][p][q];
    long long m2 = st[x2 - (1 << p) + 1][y1][p][q];
    long long m3 = st[x1][y2 - (1 << q) + 1][p][q];
    long long m4 = st[x2 - (1 << p) + 1][y2 - (1 << q) + 1][p][q];
    return max({ m1, m2, m3, m4 });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> val[i][j];

    build_prefix_sum();
    build_sparse_table();

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            long long m1 = -INF, m2 = -INF, m3, m4, m5, m6;
            if (i < j) {
                m1 = ask_sparse_table(1, 1, i, n) + ask_sparse_table(i + 1, 1, j, n) + ask_sparse_table(j + 1, 1, n, n);
                m2 = ask_sparse_table(1, 1, n, i) + ask_sparse_table(1, i + 1, n, j) + ask_sparse_table(1, j + 1, n, n);
            }
            m3 = ask_sparse_table(1, 1, i, j) + ask_sparse_table(1, j + 1, i, n) + ask_sparse_table(i + 1, 1, n, n);
            m4 = ask_sparse_table(1, 1, i, j) + ask_sparse_table(i + 1, 1, n, j) + ask_sparse_table(1, j + 1, n, n);
            m5 = ask_sparse_table(1, 1, i, n) + ask_sparse_table(i + 1, 1, n, j) + ask_sparse_table(i + 1, j + 1, n, n);
            m6 = ask_sparse_table(1, 1, n, j) + ask_sparse_table(1, j + 1, i, n) + ask_sparse_table(i + 1, j + 1, n, n);
            ans = max({ ans, m1, m2, m3, m4, m5, m6 });
        }
    }
    cout << ans << endl;

    return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

考虑答案一共只有六种情况：

![](https://img.atcoder.jp/abc347/c8c4557905764a04a59ff89c7b249746.png)

所以考虑维护 $fu_i$ 表示矩形右下角横坐标在 $1 \sim i$ 行的最大矩形，$fd_i$ 表示矩形左上角横坐标在 $i \sim n$ 行的最大矩形，$fl_j$ 表示矩形右下角纵坐标在 $1 \sim j$ 列的最大矩形，$fr_j$ 表示矩形左下角纵坐标在 $j \sim n$ 列的最大矩形。

再维护 $lu_{i,j}$ 表示右下角坐标为 $(i,j)$ 的左上角区间的最大矩形，$ld_{i,j}$ 表示左下角坐标为 $(i,j)$ 的右上角区间的最大矩形，$ru_{i,j}$ 表示左下角坐标为 $(i,j)$ 的右上角区间的最大矩形，$rd_{i,j}$ 表示左上角坐标为 $(i,j)$ 的右下角区间的最大矩形。

~~维护的东西有一点点多。~~

转移时用二维前缀和优化即可，注意枚举顺序。

然后答案即为六种情况中的最大值：

1. 三个行的形状：`ans=max(ans,fu[i-1]+fd[i+k]+get(i,j,i+k-1,j+k-1)); `

2. 三个列的形状：`ans=max(ans,fl[j-1]+fr[j+k]+get(i,j,i+k-1,j+k-1));` 

3. 上面一行，下面两列：`ans=max(ans,fu[i-1]+ld[i][j]+rd[i][j+1]);`

4. 下面一行，上面两列：`ans=max(ans,fd[i+1]+lu[i][j]+ru[i][j+1]);`

5. 左边一列，右边两行：`ans=max(ans,fl[j-1]+ru[i][j]+rd[i+1][j]);`

6. 右边一列，左边两行：`ans=max(ans,fr[j+1]+lu[i][j]+ld[i+1][j]);`

转移的时候为了在判断边界的时候不错可以将二维前缀和写成如下形式：

```
il int get(int x1,int y1,int x2,int y2){ 
	if(x1<1||y1<1||x2>n||y2>m) return -INF; 
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1]; 
} 
```

然后就可以不用判断边界了。

时间复杂度 $O(n^2)$。因为要转移的东西很多，所以常数会很大。

[Code](https://atcoder.jp/contests/abc347/submissions/51938980)

---

## 作者：Starrykiller (赞：0)

赛时没有想到划分方式，降智了。

显然三个正方形格子有六种划分方式。（贺一下 Official Solution 的图）

![](https://cdn.luogu.com.cn/upload/image_hosting/ll4w0dwa.png)

请注意，以下的讨论中，$x$ 轴是向下指的，以左上角的点为 $(1,1)$。

对于右边的四种情况，我们可以预处理出 $\operatorname{maxul}(i,j)$ 表示以 $(i,j)$ 为右下角、以 $(1,1)$ 为右上角的区域内能够选出的最大的 $m\times m$ 区域的权值是多少。对于 $\operatorname{maxur}$，$\operatorname{maxdl}$，$\operatorname{maxdr}$ 同理（$\mathrm d$ 代表从下往上考虑，$\mathrm l$ 代表从做左往右考虑，反过来同理）。

那么对于右边的四种情况，就很好解决了。以右下角的情况为例，我们枚举中心格子的坐标 $(x,y)$（我们把中心格子归到左边的区域），答案显然为 $\operatorname{maxul}(x,y)+\operatorname{maxdl}(x+1,y)+\operatorname{maxdr}(1,y+1)$。分类讨论四种情况即可。

对于两条平行线的情况，以左上角的情况为例，我们先枚举第一条横线坐标是 $x_1$（将 $x_1$ 归到上面的区域）。然后，我们枚举第二个正方形区域的上边界的 $x$ 坐标 $x_2$（这一行的正方形都可以取，所以要对一行的所有可能取 $\max$），于是第三个正方形区域的上边界的 $x$ 坐标至少是 $x_2+m$。于是我们需要预处理出 $\operatorname{maxx}(x)$ 表示上边界为 $x$ 的正方形区域的权值最大值，然后用 $\operatorname{maxur(x_1,1)}+\operatorname{maxx}(x_2)+\operatorname{maxdr}(x_2+m,1)$ 更新答案。左下角的情况是对称的。

因此，我们在 $\Theta(n^2)$ 的时间内解决了本题。由于 Atcoder 评测机过于强大，所以[不预处理](https://atcoder.jp/contests/abc347/submissions/51897612) $\operatorname{maxx},\operatorname{maxy}$ 也能过？

[My submission](https://atcoder.jp/contests/abc347/submissions/51897744).

---

## 作者：int_R (赞：0)

把每个要选出来的矩形用左上角的点表示，通过二维前缀和预处理出选择以 $(i,j)$ 为左上角的点的矩形的贡献 $c_{i,j}$。

发现三个矩形很优，因为一定可以找到一条线将一个矩形和另外两个矩形分隔开。两个矩形肯定也是能分隔开的，所以枚举选择哪两条线，这一步复杂度是 $O(n^2)$ 的。

问题转化成一个子矩阵中选出一个最大值，直接做肯定不行，所以需要根据题目性质优化。由于只分割了两次，如果两次分割方向不同（一次竖着一次横着），那么每个矩形至少带着一个角。如果两次分割方向相同，那么每个矩形都有一条边长度为 $n$。

于是我们可预处理出 $f_{i,j}$ 表示从 $(1,1)$ 到 $(i,j)$ 的矩阵最大值，从另外三个角同理。再预处理出 $g_{i,j}$ 表示从第 $i$ 行到第 $j$ 行中最大的值，从列到列同理，这样 $O(n^2)$ 预处理之后就可以 $O(1)$ 得到最大值。总时间复杂度 $O(n^2)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int MAXN=1e3+10;
int n,m,a[MAXN][MAXN],s[MAXN][MAXN],c[MAXN][MAXN],f[6][MAXN][MAXN],g[2][MAXN];
inline int Q(int x1,int x2,int y1,int y2)
{
    if(x1==1&&y1==1) return f[0][x2][y2];
    if(x1==1&&y2==n-m+1) return f[1][x2][y1];
    if(x2==n-m+1&&y1==1) return f[2][x1][y2];
    if(x2==n-m+1&&y2==n-m+1) return f[3][x1][y1];
    if(y1==1&&y2==n-m+1) return f[4][x1][x2];
    return f[5][y1][y2];
}
inline int DO(int x1,int x2,int y1,int y2,int k)//递归做
{
    if(k==1) return Q(x1,x2-m+1,y1,y2-m+1);
    long long ans=0;
    for(int i=x1+m-1;i<=x2-m;++i) for(int K=1;K<k;++K)
        ans=max(ans,DO(x1,i,y1,y2,K)+DO(i+1,x2,y1,y2,k-K));
    for(int i=y1+m-1;i<=y2-m;++i) for(int K=1;K<k;++K)
        ans=max(ans,DO(x1,x2,y1,i,K)+DO(x1,x2,i+1,y2,k-K));
    return ans;
}
signed main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin>>a[i][j],s[i][j]=s[i][j-1]+a[i][j];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            s[i][j]+=s[i-1][j];
    for(int i=1;i<=n-m+1;++i)
        for(int j=1;j<=n-m+1;++j)
            c[i][j]=s[i+m-1][j+m-1]+s[i-1][j-1]-s[i+m-1][j-1]-s[i-1][j+m-1];
    for(int i=1;i<=n-m+1;++i)
        for(int j=1;j<=n-m+1;++j)
            f[0][i][j]=max(max(f[0][i-1][j],f[0][i][j-1]),c[i][j]);
    for(int i=1;i<=n-m+1;++i)
        for(int j=n-m+1;j;--j)
            f[1][i][j]=max(max(f[1][i-1][j],f[1][i][j+1]),c[i][j]);
    for(int i=n-m+1;i;--i)
        for(int j=1;j<=n-m+1;++j)
            f[2][i][j]=max(max(f[2][i+1][j],f[2][i][j-1]),c[i][j]);
    for(int i=n-m+1;i;--i)
        for(int j=n-m+1;j;--j)
            f[3][i][j]=max(max(f[3][i+1][j],f[3][i][j+1]),c[i][j]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            g[0][i]=max(g[0][i],c[i][j]);
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;++j)
            f[4][i][j]=max(f[4][i][j-1],g[0][j]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            g[1][j]=max(g[1][j],c[i][j]);
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;++j)
            f[5][i][j]=max(f[5][i][j-1],g[1][j]);
    cout<<DO(1,n,1,n,3)<<'\n';return 0;
}
```

---

