# Three displays

## 题目描述

### 形式化题面

给定一个有两个性质 $s_i$ 和 $c_i$ 的数组，要求在其中选出三个数，满足：

 - $i<j<k$.
 - $s_i<s_j<s_k$.
 - $c_i+c_j+c_k$ 最小.

## 样例 #1

### 输入

```
5
2 4 5 4 10
40 30 20 10 40
```

### 输出

```
90
```

## 样例 #2

### 输入

```
3
100 101 100
2 4 5
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
10 13 11 14 15 12 13 13 18 13
```

### 输出

```
33
```

# 题解

## 作者：小菜鸟 (赞：17)

虽说CF上这题的正解是DP，但是~~我DP学得非常差，所以只好暴力解决~~  
枚举中间数j将路分为左右两段，再分别枚举左右两段中的数，将符合条件的答案存下来，最后找出最优解输出( 这种枚举方式使时间复杂度从O(n^3)->O(n^2) )  
上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s[3010],c[3010],i,j,l,r,ans=0x7fffffff;
void read(int &x)//读入优化
{
    int s=1,n=0;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<='9'){n=n*10+c-48;c=getchar();}
    x=s*n;
}
int main()
{
    read(n);
    for(i=1;i<=n;i++)
        read(s[i]);
    for(i=1;i<=n;i++)
        read(c[i]);
    c[0]=c[n+1]=0x7fffffff;
    for(i=2;i<=n-1;i++)
    {
        l=0;r=n+1;
        for(j=1;j<i;j++)
            if (s[j]<s[i])
                if (c[j]<c[l]) l=j;
        for(j=i+1;j<=n;j++)
            if (s[j]>s[i])
                if (c[j]<c[r]) r=j;
        if (l!=0&&r!=n+1) ans=min(ans,c[l]+c[r]+c[i]);
    }
    if (ans==0x7fffffff) printf("-1");
    else printf("%d",ans);
}
```

---

## 作者：love_luke (赞：11)

思路来源于网络。

我们可以设数组f，f[i][k]表示第i个位置被选中，作为选出的三个物品中的第k个的c之和。

这时候我们只需扫一遍i之前，作为第k-1个的位置，再加上c[i]。

易得状态转移方程：
```cpp
f[i][k]=min(f[i][k],f[j][k-1]+c[i]);
```
其中0<j<i，且s[j]<s[i]。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[3001],c[3001],f[3001][4];
int main()
{
	int n,i,j,k,maxx=0x3f3f3f3f;
	cin>>n;
	for (i=1;i<=n;++i)
	{
		cin>>s[i];
	}
	for (i=1;i<=n;++i)
	{
		cin>>c[i];
	}
	memset(f,0x3f,sizeof(f));
	for (i=1;i<=n;++i)
	{
		f[i][1]=c[i];//当前位置被选中为第一个，值就是c[i]
		for (k=2;k<=3;++k)
		for (j=1;j<i;++j)
		if (s[j]<s[i])//满足此条件才能被选中
		{
			f[i][k]=min(f[i][k],f[j][k-1]+c[i]);
		}
	}
	for (i=1;i<=n;++i)
	{
		maxx=min(f[i][3],maxx);
	}
	if (maxx==0x3f3f3f3f)//如没有满足条件的三个数，maxx不会更新，还是最大值
	{
		cout<<-1;
	}
	else
	{
		cout<<maxx;
	}
	return 0;
}
```


---

## 作者：Priori_Incantatem (赞：6)

这题虽然说要上升子序列，但只需要长度为 $3$ 的，所以我们不需要求 LIS 的长度，只用求费用

设 $f[i][j]$ 表示以第 $i$ 个元素结尾的，长度为 $j$ 的上升子序列的最小费用（$j \le 3$）  
则 $f[i][j]=min\{ f[k][j-1]+c[i] \}(a[k]<a[i]),(k<i)$

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int Maxn=3010,inf=0x3f3f3f3f;
int a[Maxn],c[Maxn];
int f[Maxn][5];
int n,ans=inf;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	a[i]=read();
	memset(f,inf,sizeof(f));
	for(int i=1;i<=n;++i)
	{
		c[i]=read();
		f[i][1]=c[i];
	}
	
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<i;++j)
		{
			if(a[j]>=a[i])continue;
			f[i][2]=min(f[i][2],f[j][1]+c[i]);
			f[i][3]=min(f[i][3],f[j][2]+c[i]);
		}
		ans=min(ans,f[i][3]);
	}
	if(ans==inf)puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Tweetuzki (赞：5)

动态规划 + 权值线段树优化。

$dp[i][k]$ 表示选择 $i$ 作为三元组中的第 $k$ 个数的最小花费。

转移方程：

$dp[i][1]=c[i]$  
$dp[i][k] = \min (dp[j][k-1])(1\le j<i$ && $s[j] < s[i])+c[i]$	$(1 < k \le 3)$

注意到第二个只要从 $1 \le j < i$ 的区间内取出满足 $s[j] < s[i]$ 的 $dp[j][k-1]$ 的最小值。可以先将 $s$ 数组离散，然后使用权值线段树，可以快速查询到满足 $s[j] < s[i]$ 的 $dp[j][k-1]$ 最小值。

时间复杂度：$O(n \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long llt;
const int MAXN = 3000;
const llt INF = 0x0F0F0F0F0F0F0F0F;

int N;
int s[MAXN+1], c[MAXN+1], lisan[MAXN+1];
int L[MAXN*4+1], R[MAXN*4+1]; llt Min[MAXN*4+1];
llt dp[MAXN+1][4];

void init()
{
    memset( dp, 0x0F, sizeof dp );
    scanf( "%d", &N );
    for ( int i = 1; i <= N; ++i )
        scanf( "%d", &s[i] ), lisan[i] = s[i];
    for ( int i = 1; i <= N; ++i )
        scanf( "%d", &c[i] );
    sort( lisan+1, lisan+1+N );
    for ( int i = 1; i <= N; ++i )
        s[i] = lower_bound( lisan+1, lisan+1+N, s[i] ) - lisan;
}

inline void Push_up( int i ) { Min[i] = min( Min[i << 1], Min[i << 1 | 1] ); }

inline void Build_Tree( int left, int right, int i )
{
    L[i] = left, R[i] = right;
    if ( L[i] == R[i] ) { Min[i] = INF; return; }
    int mid = L[i] + R[i] >> 1;
    Build_Tree( left, mid, i << 1 );
    Build_Tree( mid + 1, right, i << 1 | 1 );
    Push_up( i );
}

inline void Update_Tree( int x, llt v, int i )
{
    if ( L[i] == R[i] ) { Min[i] = min( Min[i], v ); return; }
    int mid = L[i] + R[i] >> 1;
    if ( x <= mid ) Update_Tree( x, v, i << 1 );
    else Update_Tree( x, v, i << 1 | 1 );
    Push_up( i );
}

inline llt Query_Tree( int left, int right, int i )
{
    if ( L[i] == left && R[i] == right ) return Min[i];
    int mid = L[i] + R[i] >> 1;
    if ( right <= mid ) return Query_Tree( left, right, i << 1 );
    else if ( left > mid ) return Query_Tree( left, right, i << 1 | 1 );
    else return min( Query_Tree( left, mid, i << 1 ), Query_Tree( mid + 1, right, i << 1 | 1 ) );
}

void solve()
{
    for ( int i = 1; i <= N; ++i ) dp[i][1] = c[i];
    Build_Tree( 1, N, 1 );
    for ( int i = 1; i <= N; ++i )
    {
        if ( s[i] != 1 ) dp[i][2] = min( dp[i][2], Query_Tree( 1, s[i] - 1, 1 ) + c[i] );
        Update_Tree( s[i], dp[i][1], 1 );
    }
    Build_Tree( 1, N, 1 );
    for ( int i = 1; i <= N; ++i )
    {
        if ( s[i] != 1 ) dp[i][3] = min( dp[i][3], Query_Tree( 1, s[i] - 1, 1 ) + c[i] );
        Update_Tree( s[i], dp[i][2], 1 );
    }
}

void print()
{
    llt ans = INF;
    for ( int i = 1; i <= N; ++i ) ans = min( ans, dp[i][3] );
    if ( ans == INF ) puts( "-1" );
    else cout << ans << endl;
}

int main()
{
    init();
    solve();
    print();
    return 0;
}

```

---

## 作者：Yizhixiaoyun (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF987C)

## 题目分析

本题思路考虑**动态规划**。

我们假设 $dp_{i,j}$ 为选中了第 $i$ 个位置，选出的第 $j$ 个物品的 $c$ 之和，接着往前扫一遍即可。

## 状态转移方程

$dp_{i,j} = \min(dp_{i,j},dp_{k,j-1} + c_i)$

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3005;
int n,a[maxn],b[maxn];
int ans=1145141919,dp[maxn][4];
int main(){
	memset(dp,114514,sizeof(dp));
	cin>>n;
	for(register int i=1;i<=n;++i) cin>>a[i];
	for(register int i=1;i<=n;++i) cin>>b[i];
	for(register int i=1;i<=n;++i){
		dp[i][1]=b[i];
		for(register int j=2;j<=3;++j){
			for(register int k=1;k<i;++k){
				if(a[k]<a[i]) dp[i][j]=min(dp[i][j],dp[k][j-1]+b[i]);
			}
		}
	}
	for(register int i=1;i<=n;++i) ans=min(dp[i][3],ans);
	if(ans==1145141919) cout<<-1;
	else cout<<ans;
}
```

---

## 作者：MurataHimeko (赞：4)

## [CF987C](https://www.luogu.com.cn/problem/CF987C)



------------


### 思路

考虑设 $dp[i][1/2/3]$ 分别表示以第 $i$ 位为末尾，长度为 $1/2/3$ 的 $s$ 的上升子序列的 $c$ 之和的最小值。很容易想出下面的转移方程：

$$ dp[i][1] = c[i] $$

$$ dp[i][2] = \min \limits_{s_j < s_i,1 \le j < i } {dp[j][1] + c[i]} $$

$$ dp[i][3] = \min \limits_{s_j < s_i, 1 \leq j < i} {dp[j][2] + c[i]} $$

转移时枚举 $j$ 即可。



------------


### 优化

可以利用权值线段树来维护 $ s_j < s_i $ 的 $dp[j][1]$ 和 $dp[j][2]$ 的最小值，$ O(\log n) $ 查询即可。不过要先离散化处理。



------------

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b
#define swap_(i, j) i = i^j, j = i^j, i = i^j
#define abs_(x) (((x)>>31)^(x)) - ((x)>>31)
#define INF 0x3f3f3f3f
#define rep(i, f, t) for(register int i(f); i <= t; ++i)
#define per(i, f, t) for(register int i(t); i >= f; --i)
#define ste(i, f, t, s) for(register int i(f); i <= t; i += s)
#define nx(i, u) for(register int i(head[u]); i; i = e[i].next) 
#define index(l, r) (l + r | l != r)
// #define dis(a, b) (abs(nd[a].x - nd[b].x))
// #define int long long
typedef long long ll;



/***************??***************/

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

/***************??***************/

int n, ans = INF;
int s[3003], c[3003], a[3003];
int cnt, tnt;

struct Tree {
    int minn[3];
}tr[6006];

void build (int l, int r) {
    tr[index(l, r)].minn[2] = tr[index(l, r)].minn[1] = INF;
    if(l == r) return ;
    int m = l + r >> 1;
    build(l, m);
    build(m+1, r);
}

void update (int l, int r, int p, int a, int b) {
    int node = index(l, r);
    if(l == r) {    
        tr[node].minn[1] = min_(tr[node].minn[1], a);
        tr[node].minn[2] = min_(tr[node].minn[2], b);
        return ;
    }
    int m = l + r >> 1;
    if(p <= m) update(l, m, p, a, b);
    else update(m+1, r, p, a, b);
    tr[node].minn[1] = min_(tr[index(l, m)].minn[1], tr[index(m+1, r)].minn[1]);
    tr[node].minn[2] = min_(tr[index(l, m)].minn[2], tr[index(m+1, r)].minn[2]);
    return ;
}

int query (int ls, int rs, int L, int R, int lim) {
    if(R < ls) return INF;
    if(L <= ls && rs <= R) {
        return tr[index(ls, rs)].minn[lim];
    }
    int m = ls + rs >> 1;
    int a = INF, b = INF;
    if(L <= m) a = query(ls, m, L, R, lim);
    if(R > m) b = query(m+1, rs, L, R, lim);
    return min_(a, b);
}

int siz;

int main () {
    read(n);
    rep(i, 1, n) read(s[i]), a[i] = s[i];
    rep(i, 1, n) read(c[i]);
    std::sort(a+1, a+n+1);
    siz = std::unique(a+1, a+n+1) - (a+1);
    rep(i, 1, n) s[i] = std::lower_bound(a+1, a+siz+1, s[i]) - a;
    build(1, siz);
    rep(i, 1, n) {
        cnt = tnt = INF;
        int a = query(1, siz, 1, s[i]-1, 1);
        int b = query(1, siz, 1, s[i]-1, 2);
        cnt = a + c[i];
        tnt = b + c[i];
        update(1, siz, s[i], c[i], cnt);
        ans = min_(ans, tnt);
    }
    ans = ans >= INF ? -1 : ans;
    out(ans);
}
```


------------

感谢您能阅读本蒟蒻这篇博客！


---

## 作者：伟大的王夫子 (赞：3)

练DP的好题

适合新手入门，我这个初学DP的蒟蒻都写出来了

其实题目翻译有误，还要满足$i<j<k$才行

设$f[i][3], f[i][2]$为第$i$个必选，前$i$个数中能取到的最小值

暴力枚举，则有状态方程

$f[i][3]=\max\limits_{1 \le j<i, s[j] <s[i]} {f[j][2] +c[i]}$

其中$s[j]<s[i]$为题设条件，设前一个要选得数是第$j$个，枚举要选那个$j$,再从这几个里面选$2$个，所以加上$f[j][2]+c[i]$,$c[i]$表示选了第$i$个

同理$f[i][2]=\max\limits_{1 \le j<i, s[j] <s[i]} {c[j] +c[i]}$

$ans= \max\limits_{1\le i \le n}{f[i][3]}$

注意细节（边界，初始化最大值即可）

code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s[3001], c[3001], f[3001][5], ans = 0x3f3f3f3f;
int main() {
	cin >> n;
	memset(f, 0x3f, sizeof(f));
	ans = 1e9;
	for (register int i = 1; i <= n; ++i) cin >> s[i];
	for (register int i = 1; i <= n; ++i) cin >> c[i];
	for (register int i = 1; i <= n; ++i) 
		for (register int j = 1; j < i; ++j)
			if (s[j] < s[i]) {
				f[i][3] = min(f[j][2] + c[i], f[i][3]);
				f[i][2] = min(f[i][2], c[j] + c[i]);
				ans = min(ans, f[i][3]);
			}
	if (ans == 1e9) puts("-1");
	else cout << ans;
}
```

为[我的blog](https://www.luogu.com.cn/blog/I-AK-IOI/)打一下广告

---

## 作者：0xFF (赞：2)

#### 题目简述


------------
给定长度为 $n$ 的序列，数列中的每一个数有 $s_i$ 和 $c_i$ 这两个性质，要求找出一个三元组 $(i,j,k)$ 满足 $s_i < s_j < s_k$ 的同时使得 $c_i + c_j + c_k$ 的值最小。

#### 题目分析


------------
根据题设可以很快分析出类似于上升子序列问题，只不过此时的上升子序列长度固定为 $3$，需要求的是上升子序列的和。

- 状态表示：$f(i,j)$ 表示选择第 $i$ 个数作为三元组的第 $k$ 个元素的最小花费。

- 状态转移：首先考虑 $f(i,1)$ 易知其等于 $c_i$，由此可以推得 $f(i,k) = \min \left \{ f(i,k) , f(j,k-1) + c[i]  \right \} $。

- 记录所有的 $f(i,3)$ 中最小的答案，若无答案满足题设则输出 ```-1```。

- 不要忘了开 ```long long``` 

#### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define INF 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 3050; 
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

int s[N],c[N],f[N][4];

signed main(){
	int ans = INF;
	int n = read();
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++){
		s[i] = read();
	}
	for(int i=1;i<=n;i++){
		c[i] = read();
	}
	for(int i=1;i<=n;i++){
		f[i][1] = c[i];
		for(int k = 2;k <= 3;k ++){
			for(int j=1;j<i;j++){
				if(s[j] < s[i]){
					f[i][k] = min(f[i][k],f[j][k-1] + c[i]);
				}
			}
		}		
		ans = min(ans,f[i][3]);
	}
	if(ans == INF){
		printf("-1\n");
		return 0;
	}
	else 
		printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Suuon_Kanderu (赞：0)

新手DP入门题，建议大家先自己思考，再看题解，否则容易像笔者一样成为DP低能儿……

DP，先看数据规模$n \leq 3000$，$n^2$可过。

- 状态：$f_{i,j}$表示将第 i 个数据作为三元组$i,j,k$中的第 j 个数的最大值，不难看出答案就是$\max_{i=1}^{n}f_{i,3}$。
- 初始化
$$ f_{i,1} = c_i,f_{i,2}=f_{i,3}= ∞$$
- 状态转移方程：
$$ f_{i,2} = c_i+\min^{n}_{j=i+1}f_{j,1} ~~~~~~~~s_j<s_i$$
$$ f_{i,3} = c_i+\min^{n}_{j=i+1}f_{j,2}~~~~~~~~s_j<s_i $$
只要设计出状态后方程很好推的

虽然$n^2$可过，但我们看到了一个熟悉的套路，$s_j$权值比$s_i$小的最小值？欸，权值线段树啊！然而我们这里只需要维护$[1,1],[1,2],[1,3]…[1,n]$的最小值，我们可以使用常数更小码量更小的树状数组。

具体而言，我们两颗权值树状数组，维护最小值，每次在$s_i$上插入$f_{i,1}$，$f_{i,2} = c_i+\operatorname{query}s_{i}-1$,再插$f_{i,2}$，维护$f_{i,3}$

然而$s_i \leq 10^9$，我们需要[离散化](https://baike.baidu.com/item/%E7%A6%BB%E6%95%A3%E5%8C%96/10501557?fr=aladdin)。

具体细节见代码：

```
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 3000+20;
int t[N],s[N],c[N];
ll f[N][4];//由于初值设为inf可能会溢出，所以使用ll,懒得特判了
const int INF = 0x7fffffff;//无穷
ll ans = INF;
ll tree1[N],tree2[N];//树状数组
int n;
int lowbit(int k) {return k&(-k);}
void update1(int x,ll y) {for(;x <= n; x += lowbit(x))tree1[x] = min(tree1[x],y);}
void update2(int x,ll y) {for(;x <= n; x += lowbit(x))tree2[x] = min(tree2[x],y);}
ll query1(int x) {ll ans = INF;for(;x; x -= lowbit(x))ans = min(ans,tree1[x]);return ans;}
ll query2(int x) {ll ans = INF;for(;x; x -= lowbit(x))ans = min(ans,tree2[x]);return ans;} 
//轻微压行，这不是重点
int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)scanf("%d",&t[i]),s[i] = t[i];
	for(int i = 1; i <= n; i++)scanf("%d",&c[i]),tree1[i] = tree2[i] = INF;
	sort(t+1,t+n+1);//离散化三件套
	int len = unique(t+1,t+n+1)-t-1;
	for(int i = 1; i <= n; i++)
	s[i] = lower_bound(t+1,t+len+1,s[i])-t;
	for(int i = 1; i <= n; i++) {
		f[i][1] = c[i];//初始化
		f[i][2] = f[i][3] = INF;
		update1(s[i],f[i][1]);
		f[i][2] = min(f[i][2],query1(s[i]-1)+c[i]) ;//因为是要求Sj < Si 所以我们查询所有小于等于Si-1的最小值
		update2(s[i],f[i][2]); 
		f[i][3] = min(f[i][3],query2(s[i]-1)+c[i]);
		ans = min(ans,f[i][3]);
//		cout << f[i][1] << " " << f[i][2] << " " << f[i][3] << endl; 
	}
	
	if(ans == INF)puts("-1");//INF代表没有一个满足条件
	else cout << ans << endl;
} 
```

顺带一提，带着 long long 的大常数 + 本人的大常数在没开O2的情况下玩到了最优解，树状数组tql !

---

## 作者：Apro1066 (赞：0)

#### 注意，非原创，非原创！

网上神仙很多，我在百度上找到一个比较好理解的dp，觉得不错，但是不够详细，我把我的大致思路写了下来。

题目大意是给定$n$个数，每个数有两个权值$(a,b)$，问取三个数，要求这三个数的$a$值递增，满足要求的最小三个数的和。

这题可以转换成线性dp，类似于最大子序列和。

先求出$s[i]$后面比$s[i]$大的$c[i]$的最小值，然后枚举前两个数$c[i],c[j]$以及$j$后面递增并且有最小值的$dp[j]$。
```cpp
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#define inf 0x3f3f3f3f+1
using namespace std;
int n,cnt,c[3001],s[3001],dp[3001];
//定义dp[i]代表s[i]后面比s[i]大的对应c[i]的最小值 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	cin>>n;
	cnt=inf;
	for(i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(i=1;i<=n;i++)
	{
		cin>>c[i];
	}
	memset(dp,inf,sizeof dp);
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)//只在后面找 
		{
			if(s[j]>s[i])//如果后面的比前面的大 
			{
				dp[i]=min(dp[i],c[j]);//对应每个c[i]的最小值 
			}
		}
	}
	for(i=1;i<=n;i++)//枚举每个c[i]和c[j] 
	{
		for(j=i+1;j<=n;j++)
		{
			if(s[j]>s[i] && dp[i]!=inf)
			{
				cnt=min(cnt,c[i]+c[j]+dp[j]);//c[i]+c[j]+对应的每个c的最小值 
			}
		}
	}
	if(cnt==inf) cout<<-1<<endl;
	else
	{
		cout<<cnt<<endl;
	}
	return 0;
}
```

---

