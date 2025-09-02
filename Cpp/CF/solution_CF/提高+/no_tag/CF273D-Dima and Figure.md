# Dima and Figure

## 题目描述

Dima loves making pictures on a piece of squared paper. And yet more than that Dima loves the pictures that depict one of his favorite figures.

A piece of squared paper of size $ n×m $ is represented by a table, consisting of $ n $ rows and $ m $ columns. All squares are white on blank squared paper. Dima defines a picture as an image on a blank piece of paper, obtained by painting some squares black.

The picture portrays one of Dima's favorite figures, if the following conditions hold:

- The picture contains at least one painted cell;
- All painted cells form a connected set, that is, you can get from any painted cell to any other one (you can move from one cell to a side-adjacent one);
- The minimum number of moves needed to go from the painted cell at coordinates $ (x_{1},y_{1}) $ to the painted cell at coordinates $ (x_{2},y_{2}) $ , moving only through the colored cells, equals $ |x_{1}-x_{2}|+|y_{1}-y_{2}| $ .

Now Dima is wondering: how many paintings are on an $ n×m $ piece of paper, that depict one of his favorite figures? Count this number modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
2 2
```

### 输出

```
13
```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
571
```

# 题解

## 作者：DarkMoon_Dragon (赞：9)

## 题意
+ 从$N*M$的方格中选出一个连通的格子集，满足任意两个同行/列的集合内的格子之间的仍然是集合内的。求这样的集合个数。
   
## $Solution:$
+ 条件等价于格子集合是凸的，即左右边界是凸的。等价于：左边界先减后增，右边界先增后减。如图所示。
![hhh](https://cdn.luogu.com.cn/upload/image_hosting/6r85yuow.png)
+ 显然$dp$统计答案
+ $f[i][l][r][0/1][0/1]$表示第$i$行左边界是$l$，右边界是$r$的答案，左右边界是否为凸的方案数。
+ 第一维可以滚掉，考虑每一行的$f$的贡献，可以把这一行一直拉到底，设
$$sum =\sum_l^{l<=m}\sum_r^{l<=r<=m}f[l][r][0/1][0/1]$$
+ 那么统计答案时贡献$sum*(n-i+1)$（如上，可以一直拉到底）
+ 统计答案比较显然，更新$dp$需要讨论四种情况
	1. 左边界$l$为凹
	+ 对于当前状态$f[l][r][0][0/1]$，就有两种转移，可以是从凸转换成凹，也可以一直凹。（自己画图看看）。
   + $$f[l][r][0][0/1] = \sum_{l'}^{l'<=l}f[l'][r][0][0/1]+\sum_{l'}^{l'<=l}f[l'][r][1][0/1]$$
   + 需要前缀和？其实没必要，发现转移$l'$的时候，把$dp$值累加过来就可以了，所以枚举顺序很重要。
   + 当前状态的转移是没有转移完的，只是先统计左边来的贡献（因为是凹的，所以是从左边加过来）。
	2. 右边界$r$为凹
	+ 和①同理，右边界凹，转移过来的状态可以凹也可以凸。
   + 同样把右边的$dp$值累加过来，因为是累加，枚举$r'$的顺序得从右到左。
	3. 左边界$l$为凸
	+ 因为是凸的，所以累加就得从右边累加起走，并且只能从之前的凸的状态转移（前面说过了先凸再凹）。
	+ $$f[l][r][1][0/1] = \sum_{l'}^{l<=l'<=m}f[l'][r][1][0/1]$$
   + 注意一下边界问题。
	4. 右边界$r$为凸
	+ 和①同理，右边界凹，转移过来的状态可以凹也可以凸。
   + 因为右边界是凸的，转移$r'$就得从左边加起走

+ 这样就愉快地更新完了$dp$，其实手写前缀和也可以，码量大，思维量小。


------------

~~这道题细节还是有点恶心的。~~
   
```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return res * f;
}
const int mod = 1000000007;
const int N = 155;
ll f[N][N][2][2];  // 左边界是否凸，右边界是否凸
int n, m;
inline void upd(ll &a, ll b) { a = (a + b) % mod; }
int main() {
    n = read(), m = read();
    for (rr i = 1; i <= m; ++i) {
        for (rr j = i; j <= m; ++j) {
            f[i][j][1][1] = 1;
        }
    }
    ll ans = 0;
    for (rr i = 1; i <= n; ++i) {
        ll res = 0;
        for (rr l = 1; l <= m; ++l)
            for (rr r = l; r <= m; ++r)
                for (rr kl = 0; kl <= 1; ++kl)
                    for (rr kb = 0; kb <= 1; ++kb)
                        res = (res + f[l][r][kl][kb]) % mod;
        ans = (ans + res * (n - i + 1)) % mod;
        for (rr l = 1; l <= m; ++l)
            for (rr r = l + 1; r <= m; ++r)
                for (rr kr = 0; kr <= 1;
                     ++kr) {  //前缀叠加 注意顺序 凹的时候另外一边凸凹都可以
                    upd(f[l + 1][r][0][kr], f[l][r][0][kr]);
                    upd(f[l + 1][r][0][kr], f[l][r][1][kr]);
                }
        for (rr l = 1; l <= m; ++l)
            for (rr r = m; r >= l + 1; --r)
                for (rr kl = 0; kl <= 1; ++kl) {
                    upd(f[l][r - 1][kl][0], f[l][r][kl][0]);
                    upd(f[l][r - 1][kl][0], f[l][r][kl][1]);
                }
        for (rr l = m; l >= 2; --l)
            for (rr r = l; r <= m; ++r)
                for (rr kr = 0; kr <= 1; ++kr) {
                    upd(f[l - 1][r][1][kr], f[l][r][1][kr]);
                }
        for (rr l = m; l >= 1; --l)
            for (rr r = l; r < m; ++r)
                for (rr kl = 0; kl <= 1; ++kl) {
                    upd(f[l][r + 1][kl][1], f[l][r][kl][1]);
                }
    }
    printf("%lld\n", ans);
}
```



---

## 作者：duanyll (赞：2)

[更好的阅读体验](https://duanyll.com/2019/10/03/Codeforces-273D.html)

## 题意

在$n\times m, (n, m \leq 150)$的方格纸上选择一个四连块, 要求对于四连块中的任意两点之间的最小移动距离等于他们之间的曼哈顿距离. 问有多少种选法.

## 分析

条件的意思是选出的格子集是凸的, 即: **左边界先减后增, 右边界先增后减**

可以定义$dp[i][l][r][ls][rs]$, 表示考虑前$i$行, 左边界为$l$, 右边界为$r$, $ls$表示左边界是否可以减少, $rs$表示右边界是否可以增加. 不难发现第一维可以滚动数组.

得到大量转移方程, 具体分类讨论见代码.

## 代码

```cpp
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;
const int MAXN = 155;
const int MOD = 1e9 + 7;

int64 dp[MAXN][MAXN][2][2];

int main() {
    int n, m;
    cin >> n >> m;
    for (int l = 1; l <= m; l++) {
        for (int r = l; r <= m; r++) {
            dp[l][r][1][1] = 1;
        }
    }
    int64 ans = 0;
    for (int i = 1; i <= n; i++) {
        int64 sum = 0;
        for (int l = 1; l <= m; l++) {
            for (int r = l; r <= m; r++) {
                for (int sl = 0; sl <= 1; sl++) {
                    for (int sr = 0; sr <= 1; sr++) {
                        sum += dp[l][r][sl][sr];
                        sum %= MOD;
                    }
                }
            }
        }
        ans += sum * (n - i + 1);  // 统计的是上一行的答案
        ans %= MOD;

        // 左侧收缩
        for (int l = 1; l < m; l++) {
            for (int r = l + 1; r <= m; r++) {
                for (int sl = 0; sl <= 1; sl++) {
                    for (int sr = 0; sr <= 1; sr++) {
                        dp[l + 1][r][0][sr] += dp[l][r][sl][sr];
                        dp[l + 1][r][0][sr] %= MOD;
                    }
                }
            }
        }

        // 右侧收缩
        for (int l = m - 1; l >= 1; l--) {
            for (int r = m; r >= l + 1; r--) {
                for (int sl = 0; sl <= 1; sl++) {
                    for (int sr = 0; sr <= 1; sr++) {
                        dp[l][r - 1][sl][0] += dp[l][r][sl][sr];
                        dp[l][r - 1][sl][0] %= MOD;
                    }
                }
            }
        }

        // 左侧扩张
        for (int l = m; l >= 2; l--) {
            for (int r = m; r >= l; r--) {
                for (int sr = 0; sr <= 1; sr++) {
                    dp[l - 1][r][1][sr] += dp[l][r][1][sr];
                    dp[l - 1][r][1][sr] %= MOD;
                }
            }
        }

        // 右侧扩展
        for (int l = 1; l < m; l++) {
            for (int r = l; r < m; r++) {
                for (int sl = 0; sl <= 1; sl++) {
                    dp[l][r + 1][sl][1] += dp[l][r][sl][1];
                    dp[l][r + 1][sl][1] %= MOD;
                }
            }
        }
    }
    cout << ans << endl;
}
```

---

## 作者：yspm (赞：0)

重塑题目中所提到的模型：如果联通块的上下左右都是一个向外凸出的形状

那么得到一个简单的 $\rm{DP}$ 定义：$f_{i,l,r,0/1,0/1}$ 表示到了第 $i$ 行表示，选择的方格覆盖了本行 $[l,r]$ 这一连续段，向左，右侧是否还可以扩展

由于用行数表示上下，所以并不在状态中进行体现

本题解的转移和其它题解所提到的按照一定顺序进行扩展有所不同，而是直接使用前缀和对 $dp$ 数组进行维护

具体而言，$sum_{i,j,k,l}$ 表示区间左端点不大于 $i$ 右端点不大于 $i$ 时后两维为 $k,l$ 时的 $dp$ 值之和，该数组每行求出 $\rm{DP}$ 值之后进行更新

转移更多根据实际含义而来，左端点能扩展的部分继承的是原来左端点大于之的，否则继承左端点小于之的，右端点同理

那么这两个取值都是连续区间，甚至都是前后缀，直接使用 $sum$ 这个二维前缀和进行更新即可

关于是否扩展过这个限制之间的转移仍然是根据实际含义，这里需要注意的就是去除重复：右端点扩展过 $l,r,x,1$ 向不再能扩展的 $l',r',y,0$ 转移的时候需要满足 $r>r'$ 不能取等，否则和后两维全 $1$ 的转移就重复了

**注意，这个在后两维相同的时候不用管**

纸上得来终觉浅，绝知此事要躬行，方程还是要自己慢慢摸索的，这里不再给出具体式子

- 可能的一个疑惑：在两行之间 $(l,r,s_1,s_2)$ 从上一行直接加到下一行上的同一状态上，该转移的含义是将上面得到的联通块整体向下平移一个

	这里不再用 $+1$ 来计算上面全是空的，$(l,r)$ 从这行才开始

下附代码供有需要的同学取用

```cpp
#include<bits/stdc++.h>
using namespace std;
#define sec second
#define fir first
#define int long long
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i) 
#define Down(i,a,b) for(int i=a;i>=b;--i)
template<typename T>inline void ckmax(T &x,T y){x=x<y?y:x; return ;}
template<typename T>inline void ckmin(T &x,T y){x=x<y?x:y; return ;}
namespace FastIO{
    template<typename T>inline T read(){
        T res=0,f=1; char k;
        while(!isdigit(k=getchar())) if(k=='-') f=-1;
        while(isdigit(k)) res=res*10+k-'0',k=getchar();
        return res*f;
    }
    char OPUT[100];
    template<typename T>inline void print(T x){
        if(x<0) putchar('-'),x=-x; 
        int cnt=0; do OPUT[++cnt]=x%10,x/=10; while(x); 
        Down(i,cnt,1) putchar(OPUT[i]+'0'); putchar('\n'); return ;
    }
}using namespace FastIO;
const int mod=1e9+7;
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int del(int x,int y){return x-y<0?x-y+mod:x-y;}
inline int mul(int x,int y){return x*y-x*y/mod*mod;}
inline void ckadd(int &x,int y){x=x+y>=mod?x+y-mod:x+y;}
inline void ckdel(int &x,int y){x=x-y<0?x-y+mod:x-y;}
inline void ckmul(int &x,int y){x=x*y-x*y/mod*mod;}
int ans,n,m,dp[2][151][151][2][2],cur,sum[151][151][2][2];
inline int get(int sx,int sy,int ex,int ey,int e1,int e2){
    if(sx>ex||ey<sy||sx==0||sy==0||ex>m||ey>m) return 0;
    return del(add(sum[ex][ey][e1][e2],sum[sx-1][sy-1][e1][e2]),add(sum[sx-1][ey][e1][e2],sum[ex][sy-1][e1][e2]));
}
signed main(){
    n=read<int>(); m=read<int>(); 
    for(int i=1;i<=m;++i) for(int j=i;j<=m;++j) dp[cur][i][j][1][1]=1;
    rep(i,1,m) rep(j,1,m) sum[i][j][1][1]=sum[i-1][j][1][1]+sum[i][j-1][1][1]-sum[i-1][j-1][1][1]+dp[cur][i][j][1][1];
    for(int lin=1;lin<=n;++lin){
        int res=0;
        rep(i,1,m) rep(j,i,m) rep(k,0,1) rep(l,0,1) ckadd(res,dp[cur][i][j][k][l]);
        ckadd(ans,mul(res,n-lin+1)); if(lin==n) break;
        rep(i,1,m) rep(j,i,m){
            if(i>1) dp[cur^1][i][j][0][1]=add(get(1,i,i,j,0,1),get(1,i,i-1,j,1,1));

            if(j<m) dp[cur^1][i][j][1][0]=add(get(i,j,j,m,1,0),get(i,j+1,j,m,1,1));
            
            if(i>1&&j<m){
                rep(k,0,1) rep(l,0,1) dp[cur^1][i][j][0][0]+=get(1,j,i,m,k,l);
                
                dp[cur^1][i][j][0][0]-=get(1,j,i,j,0,1);
                
                dp[cur^1][i][j][0][0]-=get(i,j,i,m,1,0);
                
                
                dp[cur^1][i][j][0][0]-=get(1,j,i,j,1,1)+get(i,j,i,m,1,1)-dp[cur][i][j][1][1];
                
                dp[cur^1][i][j][0][0]=(dp[cur^1][i][j][0][0]%mod+mod)%mod;
            }
            dp[cur^1][i][j][1][1]=get(i,i,j,j,1,1);
        }
        rep(i,1,m) rep(j,1,m) rep(k,0,1) rep(l,0,1){
            sum[i][j][k][l]=del(add(sum[i-1][j][k][l],sum[i][j-1][k][l]),sum[i-1][j-1][k][l]);
            ckadd(sum[i][j][k][l],dp[cur^1][i][j][k][l]);
            dp[cur][i][j][k][l]=0;
        }cur^=1;
    } print(ans); return 0;
}
```

---

