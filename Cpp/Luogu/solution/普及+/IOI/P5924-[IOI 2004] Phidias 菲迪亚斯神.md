# [IOI 2004] Phidias 菲迪亚斯神

## 题目背景

有名的希腊雕刻神菲迪亚斯正在为他下一座雄伟的雕像作准备。

## 题目描述

为了这座雕像他需要大小为 $W_1\times H_1,W_2\times H_2, ...,W_N \times H_N$ 的矩形大理石板。

最近菲迪亚斯获得一块矩形大理石块。菲迪亚斯想把这块石板切成所需要的大小。

石板或是石板所切割出的部分都可以由垂直(或水平)方向纵贯(或是横贯)加以切割到底成为两块矩形石板，同时切割出的这两块矩形石板都必须具有整数的宽度与高度。

石板只能以此种方法加以切割，同时石板不能粘合成较大石板。

因为石板具有花纹，所以石板也不能旋转。

如果菲迪亚斯切割出一块 $A\times B$ 的石板，则此石板不能被当成 $B\times A$ 的石板使用，除非 $A$ 等于 $B$。对每一种所需石板大小菲迪亚斯可切割出零或更多块石板。如果当所有的切割完成时，一块产生出的石板并不是任何所需要的大小，则此石板成为废料。

菲迪亚斯想知道如何切割最初的石板，才能让所产生的废料最少。

例如，下图中的原始石板宽度为 $21$ 且高度为 $11$，而所需石板大小为 $10\times4,6\times 2, 7\times5$ 及 $15\times 10$, 则最小废料总面积为 $10$。下图同时画出最小废料总面积为 $10$ 的切割方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/s48ydewh.png)

你的工作是写一个程序由给定的原始石板大小及所需要的各种石板大小计算出最小的废料总面积。

## 说明/提示

对于 $100\%$ 的数据，$1\le W,H\le600$，$0\le N\le 200$，$1 \le W_i \le W$，$1 \le H_i \le H$。



## 样例 #1

### 输入

```
21 11
4
10 4
6 2
7 5
15 10```

### 输出

```
10```

# 题解

## 作者：Begemot (赞：2)

$f_{i,j}$ 表示大小为 $i\times j$ 的矩形的最小废料总面积。将 $f_{i,j}$ 初始化为 $i\times j$，$f_{W_{i},H_{i}}$ 初始化为 $0$。

枚举每块矩形可以划分成的两块子矩形，用子矩形的和的最小值更新 $f_{i,j}$。

因为可以横着划分也可以竖着划分，所以时间复杂度为 $O(W\cdot H\cdot(W+H))$。

代码：

```cpp
#include <iostream>
const int MAXN = 605;
using namespace std;
int w, h, n;
int f[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false);
	cin >> w >> h;
	for (int i = 1; i <= w; ++i) {
		for (int j = 1; j <= h; ++j) {
			f[i][j] = i * j;
		}
	}
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int wi, hi;
		cin >> wi >> hi;
		f[wi][hi] = 0;
	}
	for (int i = 1; i <= w; ++i) {
		for (int j = 1; j <= h; ++j) {
			for (int k = 1; k <= i; ++k) {
				f[i][j] = min(f[i][j], f[k][j] + f[i - k][j]);
			}
			for (int k = 1; k <= j; ++k) {
				f[i][j] = min(f[i][j], f[i][k] + f[i][j - k]);
			}
		}
	}
	cout << f[w][h] << endl;
	return 0;
}
```

---

## 作者：GGapa (赞：2)

测试点 $5$ 似乎有问题？蒟蒻打完这道题之后只得了 $80$，调了一个下午没找到问题，一看讨论全都是关于测试点 $5$ 的，于是就翻了一下其它大佬的记录，发现她们好像都是特判才过了

推荐去 [SPOJ](https://www.luogu.com.cn/problem/SP365) 上提交。

这道题可以用记忆化搜索，定义 $D(w, h)$ 表示切割大小 $w\times h$ 的石板浪费的最小面积。每次选择一个大小为 $a\times b$ 的石板，且 $a \le w$，$b\le h$  。有两种决策：

- 竖着划分成三部分，浪费的面积为 $D(a, h - b) + D(w - a, h)$。
- 横着切成三部分，浪费的面积为 $D(w - a, b) + D(w, h - b)$。

时间复杂度 $O(WHN)$ 。

记忆化搜索代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
typedef long long ll;
const int N = 1000 + 5;

int W, H, n;
int F[N][N];
int a[N], b[N];

int dfs(int w, int h) {
    int & f = F[w][h];
    if(f != -1) return f;
    f = w * h;
    // cout << f << '\n';
    rep(i, 1, n) if(a[i] <= w && b[i] <= h)
        f = min({f, dfs(w - a[i], b[i]) + dfs(w, h - b[i]), dfs(a[i], h - b[i]) + dfs(w - a[i], h)});
    return f;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> W >> H;
    cin >> n;
    rep(i, 1 ,n) cin >> a[i] >> b[i];
    memset(F, -1, sizeof(F));
    cout << dfs(W, H) << '\n';
    return 0;
}
```

---

## 作者：AndyNotFound001 (赞：1)

[**P5924[IOI 2004] Phidias 菲迪亚斯神**](https://www.luogu.com.cn/problem/P5924)
## 题目大意
将初始尺寸为 $W \times H$ 的大理石板切割成若干所需尺寸，求废料面积的最小值。切割只能**水平**或**垂直**进行，且石板**不能旋转**。

## 思路（动态规划）
我们约定 $W$ 为原始石板的宽度，$H$ 为原始石板的高度。

考虑**动规**，定义 $f\big(w,h\big)$，表示处理 $w \times h$ 石板时的最小废料面积。

### 初始化
1. 初始情况下，如果需要尺寸 $(i,j)$，则废料 $f(i,j)=0$；
2. 否则，初始废料 $f(i,j)=i \times j$（这个石板的面积），就是假设不切割，就整个作为废料。

### 状态转移方程
对于每个 $f(w,h)$，我们尝试**所有可能的横向**和**纵向**切割方式（整一下）。  
横向切割，将高度 $h$ 分为 $h_1$ 和 $h_2$ 两部分，那么废料是 $f(w,h_1)+f(w,h_2)$。  
类似地，纵向切割，将宽度 $w$ 分为 $w_1$ 和 $w_2$ 两部分，废料是 $f(w_1,h)+f(w_2,h)$。  
然后在这些可能中取废料最小值作为当前状态的值。

那么，我们有状态转移方程：
1. **横向切割**（分割 $h$）：
$$f\big(w,h\big) = \min \Big( f\big(w,h\big), \ f\big(w,h_1\big) + f\big(w,h_2\big) \Big) \quad\text{其中} \ h_1 + h_2 = h $$  
2. **纵向切割**（分割 $w$）：
$$ f\big(w,h\big) = \min \Big( f\big(w,h\big), \ f\big(w_1,h\big) + f\big(w_2,h\big) \Big) \quad \text{其中} \ w_1 + w_2 = w $$  

这样，通过从小到大遍历，从较小的石板尺寸开整，整到初始石板尺寸，最终整到的 $f(W,H)$ 为所求的最小废料面积。
### Tips：
1. 在分割时，$h_1$ 和 $h_2$，$w_1$ 和 $w_2$ 都不能为 $0$（没有宽和高为 $0$ 的石板），所以在循环时条件为`h1 < h`和`w1 < w`。~你谷上 <= 似乎也可以（？）~

## 代码（含注释） 
 ```cpp
#include<iostream>
#include<cstdio> 
using namespace std ;
// 快读快写 
#define MAXSIZE (1<<25) 
#define isdigit(x) ( x >= '0' && x <= '9' ) 
#define blank(x) ( x == ' ' || x == '\n' || x == '\r' || x == '\t' )
#define Setprecision 6
namespace Fread  {char buf[MAXSIZE] ,*p1,*p2 ;inline char getchar () { if (p1 == p2) p2 = (p1 = buf) + fread(buf , 1 , MAXSIZE , stdin) ; return p1 == p2 ? '\n' : *p1++ ; }}
namespace Fwrite {char buf[MAXSIZE] ,*p1 = buf , *p2 = buf + MAXSIZE ;inline void flush () { fwrite(buf, 1, p1 - buf, stdout); p1 = buf; }inline void putchar (char c) { *p1++ = c; if (p1 == p2) flush(); } struct NTR { ~NTR() { flush(); } } ztr;}
using namespace Fread ;
using namespace Fwrite ;
#define getchar Fread ::getchar
#define putchar Fwrite::putchar
namespace Fast_IO {
	struct FRead {
		template <class T> FRead& operator >> (T &x)           {x = 0 ; short f = 1 ;         char c = getchar() ;while ( (!isdigit(c)) )            { if (c == '-') { f = -1 ; } c = getchar() ; }while ( (isdigit(c)) )  {x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar() ;}                                      x *= f ; return *this ; }
		FRead& operator >> (double &x)     {x = 0 ;      double t = 0 ; short f = 1 , s = 0 ; char c = getchar() ;while ( (!isdigit(c)) && c != '.') { if (c == '-') { f = -1 ; } c = getchar() ; }while ( (isdigit(c)) && c != '.' ) {x = (x * 10) + (c ^ 48) , c = getchar() ;}if (c == '.') {c = getchar() ;}else { x *= f ; return *this ; }while (isdigit(c)) {t = t * 10 + (c ^ 48) , s++ , c = getchar() ;}while (s--) {t /= 10.0 ;}x = (x + t) * f ;return *this ;}
		FRead& operator >> (long double &x){x = 0 ; long double t = 0 ; short f = 1 , s = 0 ; char c = getchar() ;while ( (!isdigit(c)) && c != '.') { if (c == '-') { f = -1 ; } c = getchar() ; }while ( (isdigit(c)) && c != '.' ) {x = (x * 10) + (c ^ 48) , c = getchar() ;}if (c == '.') {c = getchar() ;}else { x *= f ; return *this ; }while (isdigit(c)) {t = t * 10 + (c ^ 48) , s++ , c = getchar() ;}while (s--) {t /= 10.0 ;}x = (x + t) * f ;return *this ;}
		FRead& operator >> (float &x)      {x = 0 ;       float t = 0 ; short f = 1 , s = 0 ; char c = getchar() ;while ( (!isdigit(c)) && c != '.') { if (c == '-') { f = -1 ; } c = getchar() ; }while ( (isdigit(c)) && c != '.' ) {x = (x * 10) + (c ^ 48) , c = getchar() ;}if (c == '.') {c = getchar() ;}else { x *= f ; return *this ; }while (isdigit(c)) {t = t * 10 + (c ^ 48) , s++ , c = getchar() ;}while (s--) {t /= 10.0 ;}x = (x + t) * f ;return *this ;}
		FRead& operator >> (char &c)                        {c = getchar() ;while ( blank(c) ) {c = getchar() ;}                                                                         return *this ;}
		FRead& operator >> (char *__st)   {int len = 0 ;char c = getchar() ;while ( blank(c) ) {c = getchar() ;}while ( !blank(c) ) {__st[len++] = c , c = getchar() ;}__st[len] = '\0' ;return *this ;}
		FRead& operator >> (string &__st){__st.clear() ;char c = getchar() ;while ( blank(c) ) {c = getchar() ;}while ( !blank(c) ) {__st.push_back(c) , c = getchar() ;}                return *this ;}
		FRead() {}}cin;
	const char endl = '\n' ;
	struct FWrite {
		typedef int __exint ;
		template <class T> FWrite& operator << (T x){if (x == 0) { putchar('0') ; return *this; }if (x < 0) {putchar('-') , x = -x ;}static short sta[40] ;short top = 0 ;while (x > 0) {sta[++top] = x % 10 , x /= 10 ;}             while (top > 0) {putchar(sta[top] + '0') , top-- ;}return *this ;}
		FWrite& operator << (double x)     {if (x < 0) {putchar('-') , x = -x ;}__exint _ = x ;x -=       (double)_;static short sta[40] ;short top = 0 ;while (_ > 0) {sta[++top] = _ % 10 , _ /= 10 ;}if (top == 0) {putchar('0') ;}while (top > 0) {putchar(sta[top] + '0') , top-- ;}putchar('.') ;for (int i = 0 ; i < Setprecision ; i++) {x *= 10 ;}_ = x ;while (_ > 0) {sta[++top] = _ % 10 , _ /= 10 ;}for (int i = 0 ; i < Setprecision - top ; i++) {putchar('0') ;}while (top > 0) {putchar(sta[top] + '0') , top-- ;}return *this ;}
		FWrite& operator << (long double x){if (x < 0) {putchar('-') , x = -x ;}__exint _ = x ;x -= (long double)_ ;static short sta[40] ;short top = 0 ;while (_ > 0) {sta[++top] = _ % 10 , _ /= 10 ;}if (top == 0) {putchar('0') ;}while (top > 0) {putchar(sta[top] + '0') , top-- ;}putchar('.') ;for (int i = 0 ; i < Setprecision ; i++) {x *= 10 ;}_ = x ;while (_ > 0) {sta[++top] = _ % 10 , _ /= 10 ;}for (int i = 0 ; i < Setprecision - top ; i++) {putchar('0') ;}while (top > 0) {putchar(sta[top] + '0') , top-- ;}return *this ;}
		FWrite& operator << (float x)      {if (x < 0) {putchar('-') , x = -x ;}__exint _ = x ;x -=       (float)_ ;static short sta[40] ;short top = 0 ;while (_ > 0) {sta[++top] = _ % 10 , _ /= 10 ;}if (top == 0) {putchar('0') ;}while (top > 0) {putchar(sta[top] + '0') , top-- ;}putchar('.') ;for (int i = 0 ; i < Setprecision ; i++) {x *= 10 ;}_ = x ;while (_ > 0) {sta[++top] = _ % 10 , _ /= 10 ;}for (int i = 0 ; i < Setprecision - top ; i++) {putchar('0') ;}while (top > 0) {putchar(sta[top] + '0') , top-- ;}return *this ;}
		FWrite& operator << (char c) { putchar(c) ; return *this ; }
		FWrite& operator << (char *__st)               {int __Cnt = 0 ;while (__st[__Cnt]) {putchar(__st[__Cnt++]) ;}return *this ;}
		FWrite& operator << (const char *__st)         {int __Cnt = 0 ;while (__st[__Cnt]) {putchar(__st[__Cnt++]) ;}return *this ;}
		FWrite& operator << (string __st){int st = 0, ed = __st.size() ;while (st < ed) {putchar(__st[st++]) ;}      return *this ;}
		FWrite() {}
	}cout;
}
using namespace Fast_IO;
#define cin  Fast_IO::cin
#define cout Fast_IO::cout
#define endl Fast_IO::endl 
// 正文 
#define ll long long
#define re register
const int MAX_N = 602 ;
bool need[MAX_N][MAX_N]={0} ;// 标记所需尺寸
int f[MAX_N][MAX_N] ;
int W,H,N ;
int main() {
    cin >> W >> H ;
    cin >> N ;
    for (re int i=1 ; i<=N ; ++i) {//存下需要尺寸
        int w,h ;
        cin >> w >> h ;
        need[w][h] = 1 ;
    }
	//初始化
    for (re int w=1 ; w<=W ; ++w) {
        for (re int h=1 ; h<=H ; ++h) {
            if (need[w][h]) f[w][h] = 0 ;// 所需尺寸，废料为0
            else f[w][h] = w * h ;// 初始化为自身面积（假设不切割）
        }
    }
	//动规
    for (re int w=1 ; w<=W ; ++w) {
        for (re int h=1 ; h<=H ; ++h) {
	        //横向切割：分割高度为h1和h2（h1 < h）
            for (re int h1=1 ; h1<h ; ++h1) {
                int h2 = h - h1 ;
                f[w][h] = min(f[w][h] , f[w][h1] + f[w][h2]) ;
            }
            //纵向切割：分割宽度为w1和w2（w1 < w）
            for (re int w1=1 ; w1<w ; ++w1) {
                int w2 = w - w1 ;
                f[w][h] = min(f[w][h] , f[w1][h] + f[w2][h]) ;
            }
        }
    }
    cout << f[W][H] ;
    return 0 ;
}
  ```
## 复杂度分析 
- **时间复杂度**：$O(W \cdot H \cdot (W+H))$（飞起来）  
每个状态要遍历所有切割方式。

- **空间复杂度**：$O(W \cdot H)$

[**AC记录&2025/4/35最优解（509ms）**](https://www.luogu.com.cn/record/215025119)

---

## 作者：ny_jerry2 (赞：1)

***
## 做法
**记忆化搜索**
***
## 分析

1. 状态定义：$dfs(i,j)$：切割长为 $i$，宽为 $j$ 的长方形所浪费的最小值。
2. 状态转移：$dfs(i,j) = \min(dfs(i,j-b_{k})+dfs(i-a_{k},b_{k}),dfs(i-a_{k},j)+dfs(a_{k},j-b_{k}) )$  
    其中：$1 \le i \le W,1 \le j \le H,1 \le k \le n$。 
 
 	可知： $a_{k} \le i$，$b_{k} \le j$。   
      $dfs(i,j-b_{k})+dfs(i-a_{k},b_{k})$ 为竖着切。  
        $dfs(i-a_{k},j)+dfs(a_{k},j-b_{k}))$ 为横着切。
 
    因为是记忆化搜索，所以每搜完一个状态就记录它的最小值。
    
    $f_{i,j}$ 初始值（搜索内）为 $i \times j$，即最多将整个长方形都浪费，后面挨个取最小值。
 
    注意 $f$ 数组要全部初始化为 $-1$（搜索外），因为有可能可以不浪费。
***

## 时间复杂度
因为记忆化搜索每个状态只会被搜一遍 所以最多搜 $W \times H$ 种状态。

内部有 $O(n)$ 的遍历。

总时间复杂度约为 $O(W\times H\times n)$。

## 代码
``` cpp
#include<iostream>
#include<cstring>
using namespace std;
int w,h,n;
const int N=1010;
int a[N],b[N];
int f[N][N];
int dfs(int i,int j){
    if(f[i][j]!=-1){
        return f[i][j];
    }
    int res=i*j;
    for(int k=1;k<=n;k++){
        if(a[k]>i||b[k]>j){
            continue;
        }
        int x1=dfs(i,j-b[k])+dfs(i-a[k],b[k]);
        int x2=dfs(i-a[k],j)+dfs(a[k],j-b[k]);
        int cnt=min(x1,x2);
        res=min(res,cnt);
    }
    return f[i][j]=res;
}
int main(){
    memset(f,-1,sizeof f);
    cin>>w>>h>>n;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
    }
    cout<<dfs(w,h);
}
```

---

## 作者：__liujy (赞：0)

## 零. 前言
- 前置知识：动态规划。
- 错误想法：我本人第一次是想到了这个做法：$W \times H-\sum^{n}_{i=1} W_{i} \times H_{i}$，这个做法是错的为什么呢？因为可能忽略了切着切着切到边界了，可是这个做法就不能避免这个情况，因此是错误的。
## 壹. 思路
令 $F_{i,j}$ 为 $i \times j$ 的石板切完后最小的废料总面积。

1. 考虑初始化：

   - 初始化 $F_{W_{i},H_{i}}$ 时应该初始化为 $0$，因为这个本身就是要切的，自然没有剩下的。
   - 初始化非 $F_{i,j}$ 并且满足 $i$ 不等于任何一个 $W_{i}$，$j$ 不等于任何一个 $H_{i}$，这样应该初始化为 $i \times j$，因为自身没有石板所切，自然都是剩下的了。
2. 考虑求解：

    - 横着切：既然是横着切，那么 $j$ 肯定是不变的，变的只有 $i$，因此用 $k$ 枚举 $1$ 到 $i$，这样就能确定两个石板的 $i$ 了。$F_{i,j}=\min(F_{i,j},F_{i-k,j}+F_{k,j})$。
    - 竖着切：与横着切类似，这里就不放推导了，直接放方程：$F_{i,j}=\min(F_{i,j},F_{i,j-k}+F_{i,k})$。
## 贰. 代码
```cpp
// P5924 [IOI 2004] Phidias 菲迪亚斯神
#include<bits/stdc++.h>
const int MAXW=605,MAXN=205;
int W,H,n,w[MAXN],h[MAXN],F[MAXW][MAXW];
int main()
{
    scanf("%d%d%d",&W,&H,&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&w[i],&h[i]);
    for(int i=1;i<=W;i++)
        for(int j=1;j<=H;j++)
            F[i][j]=i*j;
    for(int i=1;i<=n;i++)
        F[w[i]][h[i]]=0;
    for(int i=1;i<=W;i++)
        for(int j=1;j<=H;j++)
        {
            for(int k=1;k<=i;k++) F[i][j]=std::min(F[i][j],F[i-k][j]+F[k][j]);
            for(int k=1;k<=j;k++) F[i][j]=std::min(F[i][j],F[i][j-k]+F[i][k]);
        }
    printf("%d\n",F[W][H]);
    return 0;
}
```

---

