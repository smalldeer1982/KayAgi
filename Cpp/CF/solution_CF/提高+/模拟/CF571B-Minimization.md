# Minimization

## 题目描述

You've got array $ A $ , consisting of $ n $ integers and a positive integer $ k $ . Array $ A $ is indexed by integers from $ 1 $ to $ n $ .

You need to permute the array elements so that value

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF571B/74275c71e404f8e7fe1cae2f08e7a067764084b1.png) became minimal possible. In particular, it is allowed not to change order of elements at all.

## 说明/提示

In the first test one of the optimal permutations is $ 1 4 2 $ .

In the second test the initial order is optimal.

In the third test one of the optimal permutations is $ 2 3 4 4 3 5 $ .

## 样例 #1

### 输入

```
3 2
1 2 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 2
3 -5 3 -5 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 3
4 3 4 3 2 5
```

### 输出

```
3
```

# 题解

## 作者：DarkMoon_Dragon (赞：11)

# $CodeForces 571B$ 题解
# $tags$: $dp$,思维。
## 题意如题

### 首先,原题的每$k$个相减，就相当于转化为将原数列按照下标%$k$划分成$k-1$个数集
例如：原数列 $A_1+A_2+A_3+...+A_n$划分为          
**数集0:**$A_{i\%k==0}$ **数集1:**$A_{i\%k==i}$ $~...~...~$ **数集k-1:**$A_{i\%k==k-1}$ ,这里就有$k$个数集

把数集$n$当做例子 $A_{i1}+A_{i2}+A_{i3}+...+A_{in}$,显然数集排序后答案最优，并且**当前数列贡献就是最大减去最小**$A_{in}-A_{i1}$ 

### 考虑数集的数量以及每个数集的大小
先考虑以后面$len\%k$个数结尾的数集,每个数集的大小为$num_x=\frac{n}{k}+1$,并且数集的个数$cnt_x$即为$len\%k$,称之为**集合$X$**。然后之前不是余数结尾的数集个数为(总数集数-之前结尾的数集数)即$cnt_y=k-len\%k$,大小$num_y=\frac{n}{k}$,**称之为集合$Y$**。

### 现在对于每个数字，一定属于集合$X$或集合$Y$。因为集合大小确定,即首尾已经确定。那么便具有了无后效性。
设**$dp[i][j]$表示选完了i个$X$集合,j个$Y$集合的最小和。** $dp$初值赋为`0x3f`。  
显然的$dp$方程 
$dp[i][j]=min(dp[i][j],dp[i-1][j]+a[i*num_x+j*num_y]-a[(i-1)*num_x+j*num_y+1]);$  
$dp[i][j]=min(dp[i][j],dp[i][j-1]+a[i*num_x+j*num_y]-a[(j-1)*num_y+i*num_x+1]);$
后面$dp$方程加上的贡献值即为末位减去首位。   
### 代码
```
#include<cstring>
#include<iostream>
#include<cstdio>
#include<algorithm>
#define rr register int
typedef long long ll;
using namespace std;
inline ll read(){
    char i=getchar();
    ll f=1,res=0;
    while(i<'0'||i>'9'){if(i=='-')f=-1;i=getchar();}
    while(i>='0'&&i<='9'){res=res*10+i-'0';i=getchar();}
    return res*f; 
}
const int N=3e5+50;
const int M=5e3+50; 
ll a[N],dp[M][M];
int main(){
    int n=read(),k=read();
    for(rr i=1;i<=n;++i) a[i]=read();
    sort(a+1,a+n+1);
    int cntx=n%k,cnty=k-cntx,numx=n/k+1,numy=n/k;
    memset(dp,0x3f,sizeof dp);
    for(rr i=0;i<=cntx;++i)
     for(rr j=0;j<=cnty;++j){
     	if(!i&&!j) dp[i][j]=0;
     	else{
     		//一段的代价就是最后一个减第一个 
     		if(i!=0) dp[i][j]=min(dp[i][j],dp[i-1][j]+a[i*numx+j*numy]-a[i*numx-numx+j*numy+1]);
     		if(j!=0) dp[i][j]=min(dp[i][j],dp[i][j-1]+a[i*numx+j*numy]-a[j*numy-numy+i*numx+1]);
     	}
     }
    printf("%lld\n",dp[cntx][cnty]);
    return 0;
}
```

---

## 作者：TernaryTree (赞：7)

2023.6.5 upd：修复了 typo。

---

相对简单的一道 *2000。

看到下标 $+k$ 这个东西显然一个套路化的模 $k$ 意义**分组**。这样，记第 $i$ 组为下标模 $k=i$ 的位置。我们只需要考虑每组里面的这个东西的和的最小值：

$$\sum_{j=0}^{z-1} |A_{jk+i}-A_{(j+1)k+i}|$$

其中 $z$ 为下标满足这个组里面的元素个数。

形象地画个图，这是 $n=3$，$k=3$ 时的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/uinms7q3.png)

我们先证明这样一个东西：**若一个颜色里的值最小，则序列有单调性（非严格）**。想想绝对值的几何意义，即在数轴上两个数的距离。现在有几个数轴上的数，我们如果不按照从小到大或者从大到小走过去，那么肯定会有一段路多走，这肯定是不划算的。如图，红色的距离一定比绿色的短：

![](https://cdn.luogu.com.cn/upload/image_hosting/7blqseu0.png)

因此一个颜色要填数，我们就将这些数从小往大填。这一段的贡献为

$$
\begin{aligned}
&\sum_{j=0}^{z-1} A_{(j+1)k+i}-A_{jk+i} \\
=&\sum_{j=0}^{z-1} A_{(j+1)k+i}-\sum_{j=0}^{z-1}A_{jk+i} \\
=&\sum_{j=1}^{z} A_{jk+i}-\sum_{j=0}^{z-1}A_{jk+i} \\
=&A_{kz+i}-A_{i}
\end{aligned}
$$

也就是这个区间的**极差**。

***

接下来证明，在最优情况下，对于**任意**两种颜色组别的集合 $S_x,S_y$（$S_i=\{A_j\mid j\bmod k=i\}$），一定有 $\max(S_x)\le \min(S_y)$。同样从数轴的几何意义证明，若两个集合中的数的区间在数轴上有大小 $>0$ 的交集，那么距离加起来一定不优。

![](https://cdn.luogu.com.cn/upload/image_hosting/lw8mswgj.png)

图中间重叠的部分是可以省掉的。

***

这样我们完成了以上两项证明。现在还差求。

我们考虑先排序后分组。因为排序后对其进行分组的每组都是连续的。

问题转换为：在序列中分 $k$ 组连续段，有 $n\bmod k$ 段长度为 $\lfloor\dfrac nk\rfloor+1$，其余段为 $\lfloor\dfrac nk\rfloor$，每段的极差之和的最小值。

设计一个 dp。看到 $k\le 5000$，这是一个非常好的暗示。于是我们设 $dp_{i,j}$ 表示放了 $i$ 组，其中 $j$ 组长度为 $\lfloor\dfrac nk\rfloor+1$ 的每组极差之和最小值。

容易得到状态转移方程，即

$$dp_{i,j} = \min(dp_{i-1,j-1} + A_{pos(i, j)} - A_{pos(i - 1, j - 1) + 1}, dp_{i-1,j} + A_{pos(i, j)} - A_{pos(i - 1, j) + 1})$$

其中 $pos(i,j)=i \times  \lfloor\dfrac nk\rfloor + j$，表示这样放（$i,j$ 意义与 dp 设计相同）的右端点。

最后输出 $dp_{k,n\bmod k}$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 3e5 + 10;
const int maxk = 5e3 + 10;

int n, k, r;
int a[maxn];
int dp[maxk][maxk]; // dp[i][j] 表示放了 i 组，j 组大的，最小值。

int pos(int i, int j) {
    return i * (n / k) + j;
}

signed main() {
    cin >> n >> k; r = n % k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= min(i, r); j++) {
            if (j) dp[i][j] = min(dp[i - 1][j - 1] + (a[pos(i, j)] - a[pos(i - 1, j - 1) + 1]), dp[i - 1][j] + (a[pos(i, j)] - a[pos(i - 1, j) + 1]));
            else dp[i][j] = dp[i - 1][j] + (a[pos(i, j)] - a[pos(i - 1, j) + 1]);
        }
    }
    cout << dp[k][r] << endl;
    return 0;
}
```

---

## 作者：_edge_ (赞：3)

这道是比较好的思维题，综合了很多思考方式。

首先我们可以发现，这个东西它是长这样的：

$a_1,a_2,\cdots,a_{k-1},a_k,a_{k+1},\cdots,a_n$。

我们可以发现，其实 $a_1$ 只和 $a_{k+1}$ 还有 $a_{2\times k+1}$，$a_{3 \times k+1}$ 有关(当然后面还有很多)。

这个分割的东西处理起来非常难受，所以考虑把互相能影响的数都给提出。

提出了之后可以发现，实际上这些能互相影响的序列都是长度为 $n/k$ 或者 $n/k+1$ 的。

两段长度中每个序列可以看成是相同的。

所以问题即转化成，给定一个序列，让你把它分成若干个 $n/k$ 长度的序列，以及 $n/k+1$ 长度的序列。

对于每一个序列来说，每一个数可以看成数轴上的一个点，如果这个序列被分配好了，那么显然是让整一个序列排个序最优，因为 $|a-b|$ 可以看成数轴上 $a$ 点到 $b$ 点的距离。

处理完以上这些东西，发现这个问题还是比较难搞，因为这样似乎没有 dp 的子结构性质。

考虑如果只有两个长度分别为 $x$ 和 $x+1$ 的序列，要你从 $2\times x +1$ 中分出这两个序列，可以猜一下，大概是排个序然后再分开来。

考虑每一个序列本质上的贡献就是最后一个数减去第一个数。

如果把这个原序列(排序之后)变成两个小序列，如果交换两个小序列的任意两个数都会使得答案变劣。

所以就是要把这个序列排序，然后分成 $n/k$ 和 $n/k+1$ 两种长度的区间，注意这里是区间，也就是说这些长度都是连续的。

这里提供一种比较好的状态，即 $f_{i,j}$ 表示长度为 $n/k+1$ 已经选了 $i$ 个，$n/k$ 长度选了 $j$ 个。

这样子进行转移就比较方便一些。

~~当然，相信大家都会怎么求长度为 $n/k$ 或者  $n/k+1$ 的序列个数。~~

dp 的时候稍微注意一下边界就可以了。

```cpp
#include <iostream>
#include <cstdio> 
#include <cstring>
#include <algorithm>
#define int long long 
using namespace std;
const int INF=3e5+5;
const int INFN=5e3+5;
int n,k,a[INF],f[INFN][INFN];
signed main()
{
	memset(f,63,sizeof f);
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	// len len+1
	int len=n/k;
	//   len+1   len
	int cntx=n%k,cnty=(n-cntx)/len-cntx;
	for (int i=0;i<=cntx;i++)
		for (int j=0;j<=cnty;j++) {
			int kk=i*(len+1)+j*len;
			if (i==0 && j==0) f[i][j]=0;
			else {
				if (i) f[i][j]=min(f[i][j],f[i-1][j]+a[kk]-a[kk-len]);
				if (j) f[i][j]=min(f[i][j],f[i][j-1]+a[kk]-a[kk-len+1]);
			}
//			cout<<i<<" "<<j<<" "<<kk<<" "<<f[i][j]<<" kk\n"; 
		}
	cout<<f[cntx][cnty]<<"\n";
	return 0;
}
```


---

## 作者：lfxxx (赞：2)

原题意转换为划分为 $k$ 个序列，其中 $n \bmod k$ 个序列大小为 $\frac{n}{k} + 1$，其余大小为 $\frac{n}{k}$。

给序列重排最小化相邻差之和显然是直接排序，和就是序列极差，于是相当于划分为 $k$ 个集合。

注意到划分出的集合在值域上相交一定是不优秀的，因为交换相交集合的 $\min,\max$ 一定会使得答案减小。

所以考虑对原序列排序后变为划分序列的问题，考虑设计状态 $dp_{i,j}$ 表示划分为 $i$ 段有 $j$ 段长度为 $\frac{n}{k} + 1$ 即可做到 $O(n + k^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxk = 5114;
const int maxn = 3e5+114;
int dp[maxk][maxk];
int a[maxn],n,k;
signed main(){
	for(int i=0;i<maxk;i++)
		for(int j=0;j<maxk;j++)
			dp[i][j]=1e18;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	dp[0][0]=0;
	for(int i=1;i<=k;i++){
		for(int j=0;j<=n%k;j++){
			if(j>0){
				dp[i][j]=min(dp[i][j],dp[i-1][j-1]+a[i*(n/k)+j]-a[(i-1)*(n/k)+j-1+1]);
			}
			dp[i][j]=min(dp[i][j],dp[i-1][j]+a[i*(n/k)+j]-a[(i-1)*(n/k)+j+1]);
		}
	}
	cout<<dp[k][n%k]<<'\n';
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：2)

## solution

首先我们发现下标模 $k$ 同余的数肯定放一组，然后这一组的最小贡献肯定是排完序后最大减最小。

考虑这样一个贪心，我们的一组内的数肯定是原数组排完序后连续的一段，因为如果不是一段，我们的值域上将会有区间的贡献次数 $> 1$，这是不优的，然后由于是连续的，所以我们考虑 DP。

发现一组的大小只会是 $\frac{n}{k}$ 或者 $\frac{n}{k} + 1$，除法默认向下取整，然后我们设 $f_{i, j}$ 为有 $i$ 组大小为 $\frac{n}{k}$，$j$ 组大小为 $\frac{n}{k} + 1$，然后每次转移一段连续区间就做完了。

## code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;
const int M = 5005;

int n, m;
int a[N], f[M][M];

void Solve () {
  cin >> n >> m;
  for ( int i = 1; i <= n; i ++ ) {
    cin >> a[i];
  }
  sort ( a + 1, a + 1 + n );
  int t1 = n / m, t2 = n / m + 1;
  memset ( f, 0x3f, sizeof ( f ) );
  f[0][0] = 0;
  for ( int i = 0; i <= m; i ++ ) {
    for ( int j = 0; j <= m; j ++ ) {
      if ( i * t1 + j * t2 <= n ) {
        int st = i * t1 + j * t2 + 1;
        if ( st + t1 - 1 <= n ) {
          f[i + 1][j] = min ( f[i + 1][j], f[i][j] + a[st + t1 - 1] - a[st] );
        }
        if ( st + t2 - 1 <= n ) {
          f[i][j + 1] = min ( f[i][j + 1], f[i][j] + a[st + t2 - 1] - a[st] );
        }
      }
    }
  }
  cout << f[m - n % m][n % m];
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：davidhu1332 (赞：1)

题目链接：[CF571B-Minimization](https://codeforces.com/contest/571/problem/B)

### 思路

- 可以将 $a_1,a_2,\dots,a_n$ 看为 $k$ 个子序列：{$a_1,a_{k+1},\dots$} {$a_2,a_{k+2},\dots$} ……

#### 结论1：当每一个子序列单调时，$\sum\limits_{\texttt{这个子序列}}\texttt{两两之间的差值}$ 最小，为 $a_{\texttt{这个子序列最大数}}-a_{\texttt{这个子序列最小数}}$
- 将绝对值看做点:
  ![](https://cdn.luogu.com.cn/upload/image_hosting/a7qz7i4m.png)
- 此时显然交换 $a_2$ 和 $a_3$ 最优。
- $\therefore$ 结论成立。

#### 结论2: 当每个子序列之间值域相交时，$\sum\limits_{i=1}^{n-k} |A_i-A_{i+k}|$ 不可能为最小
- 根据结论1，将这两个子序列的最小值设为 $a_1,a_3$，最大值设为 $a_2,a_4$，则当值域相交时，如下图：
  ![](https://cdn.luogu.com.cn/upload/image_hosting/a7qz7i4m.png)
- 此时显然交换 $a_2$ 和 $a_3$ 更优。
- $\therefore$ 结论成立。


根据题目，我们可以得知有 $n\mod k$ 个长度为 $\lfloor\frac{n}{k}\rfloor+1$ 的子序列，$k-(n\mod k)$ 个长度为 $\lfloor\frac{n}{k}\rfloor$ 的子序列。

于是，我们设计出状态: `f[i][j]`表示 $i$ 个长度为 $\lfloor\frac{n}{k}\rfloor+1$ 的子序列，$j$ 个长度为 $\lfloor\frac{n}{k}\rfloor$ 的子序列，答案的最小值。

根据结论2，状态转移为 `fr[i][j] = std::min(fr[i - 1][j] + ar[now] - ar[now - x]，fr[i][j - 1] + ar[now] - ar[now - x + 1])，now = i * (x + 1) + j * x`

初始化为 `f[0][0] = 0`

其他请参见代码



### 代码
```cpp
#include <bits/stdc++.h>

using i64 = long long;

const i64 MAXN = 3e5 + 10，MAXK = 5010，INF = 0x3f3f3f3f3f3f3f3f;
i64 ar[MAXN]，fr[MAXK][MAXK]，n，k;

void solve(void) {
    std::cin >> n >> k;
    for (i64 i = 1; i <= n; ++i) {
        std::cin >> ar[i];
    }
    std::sort(ar + 1，ar + n + 1);
    i64 x = n / k;
    for (i64 i = 0; i <= n % k; ++i) {
        for (i64 j = 0; j <= k - n % k; ++j) {
            if (!i && !j) continue;
            i64 now = i * (x + 1) + j * x;
            fr[i][j] = INF;
            if (i) fr[i][j] = fr[i - 1][j] + ar[now] - ar[now - x];
            if (j) fr[i][j] = std::min(fr[i][j]，fr[i][j - 1] + ar[now] - ar[now - x + 1]);
        }
    }
    std::cout << fr[n % k][k - n % k] << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    solve();

    return 0;
}
```

---

## 作者：endswitch (赞：1)

模 $k$ 意义下分组，可以分为个数为 $\lfloor \frac{n}{k} \rfloor, \lfloor \frac{n}{k} \rfloor + 1$ 两组。

再贪心地想，要使 $\displaystyle\sum_{i=1}^{n-k} |A_i-A_{i+k}|$ 最小，直接排序是一定最优的。因为去交换邻项可以反证出答案一定更大。

设 $dp_{i, j}$ 为选上述第一种组别 $i$ 次，选第二种组别 $j$ 次的最小值，对于每个划分的组都是可以拆贡献为末项减首项的，于是就很好转移了。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 5;
const int M = 5e3 + 5;
int n, k, a[N], dp[M][M];

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	
	sort(a + 1, a + 1 + n);
	
	int len = n / k, m1 = n % k, m2 = (n - m1) / len - m1;
	
	memset(dp, 0x3f, sizeof dp);
	
	dp[0][0] = 0;
	
	for(int i = 0 ; i <= m1 ; ++ i)
		for(int j = 0 ; j <= m2 ; ++ j) {
			int now = i * (len + 1) + j * len;
			
			if(i) dp[i][j] = min(dp[i][j], dp[i - 1][j] + a[now] - a[now - len]);
			if(j) dp[i][j] = min(dp[i][j], dp[i][j - 1] + a[now] - a[now - len + 1]);
		}
	
	cout << dp[m1][m2];
	
	return 0;
}
```

---

## 作者：JWRuixi (赞：1)

这道是比较好的思维题，综合了很多思考方式。

- 题意

给定长度为 $n$ 的数组 $a$ 和 数 $k$，重排 $a$,输出 $\sum\limits_{i = 1}^{n - k}\mid a_{i + k} - a_i \mid$ 的最小值。

- 分析

学过小学奥数的同学们会想到，这些相减的数均相差 $k$，所以可以将这些数按模 $k$ 的余数分成 $k$ 组。

可以发现每一组相互独立，且最小贡献为最大值减最小值，即排序后的末减首。

相互独立启发我们用动规，末减首启发我们排序后处理，我们又发现一组的长度有两种情况，启发我们设二维动规。

设 $f_{i,j}$ 为选 $i$ 个长度为 $\frac{n}{k}$ 的组，$j$ 个长度为 $\frac{n}{k}+ 1$ 的组的最小代价。

显然状态转移方程为：

$$f_{i,j}=\min\{f_{i-1,j}+a_{now}-a_{now-len},f_{i,j-1}+a_{now}-a_{now-len+1}\}$$

- code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

const int maxn = 3e5 + 500;
int n, k, a[maxn], f[5005][5005], len, m1, m2;

signed main () {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	memset(f, 63, sizeof(f));
	f[0][0] = 0;
	len = n / k, m1 = n % k, m2 = (n - m1) / len - m1;
	for (int i = 0; i <= m1; i++) {
		for (int j = 0; j <= m2; j++) {
			int now = i * (len + 1) + j * len;
			if (i) f[i][j] = min(f[i][j], f[i - 1][j] + a[now] - a[now - len]);
			if (j) f[i][j] = min(f[i][j], f[i][j - 1] + a[now] - a[now - len + 1]);
		}
	}
	write(f[m1][m2]);
}
```

---

## 作者：Msents (赞：0)

某场 IOI 练习赛唯一会做的题。

首先注意到一个套路，可以先将位于 $1,1+k,1+2k,...$ 位置上的元素分为一组,位于 $2,2+k,2+2k,...$ 位置上的元素分为一组，如此下去，直到将 $k-1,k-1+k,k-1+2k,...$ 位置上的元素分为一组，这样共分 $k$ 组，然后可以发现每一组的元素对答案的贡献互不影响，互相独立，也就是说更改一组中的元素的值只会影响这一组的元素对答案的贡献，不会影响其它组对答案的贡献。

考虑每一组内的元素如何排序使得贡献最小，显然的，将元素升序或降序排序，这时贡献为组内最大的元素减去最小的元素。

于是将原数组排序，可以发现每一组所包含的元素一定是数组中连续的一个区间，且不相交。

考虑反证，如果将两组中每组的一个元素交换，因为两组不相交，所以会增大一组的最大值和另一组的最小值，答案一定会更劣。

回到最开始，可以发现有 $(n\bmod k)$ 个组的大小为 $\lfloor \frac n k \rfloor +1$ ，其余的大小为 $\lfloor \frac n k \rfloor$。

于是直接 DP，设 $f_{i,j}$ 为已经分了 $i$ 组，有$j$ 个组大小为 $\lfloor \frac n k \rfloor +1$，此时答案的最小值，随便转移。

复杂度 $O(n^2)$。

码，但 DP 的东西意思不一样，只有 500b：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=300000,MaxK=5000;
int n,k,a[MaxN+1],g[2][MaxK+1],*f[2];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	stable_sort(a+1,a+1+n);
	f[0]=g[0],f[1]=g[1];
	for(int i=1,w=n%k,q=n/k;i<=k;i++){
		for(int j=0;j<=min(i,w);j++){
			f[1][j]=max(((j<=min(i-1,w))?f[0][j]:0),(j>0)?f[0][j-1]:0);
			int p=q*i+j;
			if(p<n)f[1][j]+=a[p+1]-a[p];
		}
		swap(f[0],f[1]);
	}
	cout<<a[n]-a[1]-f[0][n%k];
	return 0;
}

```

---

