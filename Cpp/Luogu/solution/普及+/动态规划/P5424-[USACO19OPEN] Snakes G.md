# [USACO19OPEN] Snakes G

## 题目描述

传说，数千年前圣帕特里克消灭了哞尔兰所有的蛇。然而，蛇们现在卷土重来了！圣帕特里克节是在每年的 3 月 17 日，所以 Bessie 要用彻底清除哞尔兰所有的蛇来纪念圣帕特里克。

Bessie装备了一个捕网，用来捕捉 $ N $ 组排成一行的蛇（ $ 1 \leq N \leq 400 $ ）。Bessie 必须按照这些组在这一行中出现的顺序捕捉每一组的所有蛇。每当 Bessie 抓完一组蛇之后，她就会将蛇放在笼子里，然后带着空的捕网开始捕捉下一组。

一个大小为 $ s $ 的捕网意味着 Bessie 可以抓住任意包含 $ g $ 条的一组蛇，其中 $ g \leq s $ 。然而，每当 Bessie 用大小为 $ s $ 的捕网抓住了一组 $ g $ 条蛇，就意味着浪费了 $ s-g $ 的空间。Bessie 可以任意设定捕网的初始大小，并且她可以改变 $ K $ 次捕网大小（ $ 1 \leq K<N $ ）。

请告诉 Bessie 她捕捉完所有组的蛇之后可以达到的总浪费空间的最小值。

## 说明/提示

Bessie 可以设置她的捕网开始时大小为 $7$。当她抓完第一组蛇之后，她将她的捕网的大小调整为 $9$，保持这个大小直到抓完第 $3$ 组蛇，再将捕网大小调整为 $3$。总浪费空间为 $ (7-7)+(9-9)+(9-8)+(3-2)+(3-3)+(3-2)=3 $ 。

## 样例 #1

### 输入

```
6 2
7 9 8 2 3 2```

### 输出

```
3```

# 题解

## 作者：fighter (赞：17)

首先有一个非常显然的分段式DP:

设$f[i][j]$表示前$i$条蛇，改变$j$次大小所得到的最小剩余空间

$g[i][j]$表示区间$[i,j]$的空余空间

那么可以得到如下转移方程：

$f[i][j] = min(f[i][j], f[k][j-1]+g[k+1][i])$

$k$为我们枚举的一个断点，表示$[k+1,i]$这段区间用同一大小的网。

那么考虑怎么求$g[i][j]$。

根据定义，一段区间的空余空间一定是用区间中的最大值作为网的大小，减去其他数字得到的和。即$g[i][j]=maxn*(j-i+1)-sum(i,j)$，其中区间和可以用前缀和$O(1)$处理。

由于我们的$dp$已经是$O(n^3)$了，所以我们考虑快速（最好是$O(1)$）求出区间最大值。

首先想到的是线段树，但有一只$log$，太慢了。然后发现没有修改操作，可以用$st$表$O(1)$查询搞一搞（没写过不知道效果怎么样）。

但实际上有一种更简洁的方式，由于我们枚举断点的时候会从$i-1$向下逐一枚举，那么我们可以在枚举断点的时候同时更新最大值。

```cpp
#include <bits/stdc++.h>
#define MAX 405
using namespace std;

int n, m;
int a[MAX], f[MAX][MAX], s[MAX];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        s[i] = s[i-1]+a[i];
    }
    m++;
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(m, i); ++j) {
            int mx = a[i];
            for (int k = i-1; k >= 0; --k) {
                f[i][j] = min(f[i][j], f[k][j-1]+mx*(i-k)-(s[i]-s[k]));
                mx = max(mx, a[k]);
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= m; ++i) {
        ans = min(ans, f[n][i]);
    }
    cout << ans << endl;

    return 0;
}
```

---

## 作者：CheerJustice (赞：10)

一眼 DP，准确说是资源分配类 DP。这类题目大意是有 $ N $ 个资源（本题是蛇，类似还有工程项目，作业等等），要把这 $ N $ 组资源分配给 $ K $ 个人（本题是要分给 $ K $ 个网去抓蛇），并求最值。[P1854](https://www.luogu.com.cn/problem/P1854) 就是一个典型的资源分配类 DP。

那么这类 DP 怎么做呢？一般分三重循环。

第一重： 循环 $ i $ 表示前 $ i $ 个物品

第二重： 循环 $ j $ 表示现在要分配第 $ j $ 组物品

第三重： 循环 $ k $ 表示将编号 $ k+1 $ 到 $ i $ 的物品分配给第 $ j $ 组

状态转移方程可以归纳为

> $ f[i][j]=\max/\min(f[i][j], f[k][j-1]+\operatorname{value}(k+1,i,j)) $

$ \operatorname{value(k+1,i,j)} $ 表示编号 $ k+1 $ 到 $ i $ 的物品分配给第 $ j $ 组的价值。

本题只需要将上面的模板中 $ \operatorname{value}(k+1,i,j) $ 修改一下就好了。

不难发现，本题若是将区间 $ [l,r] $ 分为一组，其价值（最小浪费空间）为

> $ maxnum[l][r]*(r-l+1)-sum[l][r] $

$ sum $ 直接前缀和处理，$ maxnum $ 用 $ n^2 $ 扫一遍求也无伤大雅，于是可以开心的打代码了。

# Code
```c++
#include <bits/stdc++.h>
#define lc(a) (a)<<1
#define rc(a) (a)<<1|1
#define ll long long
#define Mod 1000000007
#define Max 1145141919
#define LLMax 9223372036854775807
using namespace std;
inline int in(){
	char c=getchar();int f=1;int x;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
template <typename T>
inline void in(T &x){
	char c=getchar();int f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
const int N=405,M=1e3+5;
int s[N],mx[N][N],f[N][N];
int main(){
	int n=in(),m=in()+1;
	for(int i=1;i<=n;i++)
		in(mx[i][i]),s[i]=s[i-1]+mx[i][i];
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			mx[i][j]=max(mx[i][j-1],mx[j][j]);
	memset(f,0x3f,sizeof f);f[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m&&j<=i;j++)
			for(int k=0;k<i;k++)
				f[i][j]=min(f[i][j],f[k][j-1]+mx[k+1][i]*(i-k)-s[i]+s[k]);
	for(int i=0;i<=m;i++)
		f[n][m+1]=min(f[n][m+1],f[n][i]);
	printf("%d\n",f[n][m+1]);
	return 0;
}


```

---

## 作者：狸狸养的敏敏 (赞：7)

在@清风ღ 的指导下，本蒟蒻终于A掉了这道题QAQ

点这张图去他的博客->[![](https://cdn.luogu.com.cn/upload/usericon/96580.png)](https://www.luogu.org/blog/qfblog/solution-p5424)

清风一直试图卡Rk1，然后他成功了

然后我就把他的Rk1挤下去了[滑稽保命]

## 步入正题

这题显然是一个Dp的题目，考场上放了这道题，写了一个伪$N^3$，实则是$N^4$的区间Dp~~果然我还是太弱了~~

这道题可以转化为这样一个模型：

把一个长度为N的区间分成k+1段（就是寻找k个断点）

其中，选取[l,r]区间的代价为

$$\max^r_{i=l}a_i \times (r-l+1)\ -\ \sum^r_{i=l} a[i]$$

求符合条件的方案的最小代价


我们可以证明以下贪心结论：

```
对于区间[l,r]，分成x段显然不会比分成y段更优
其中x<y<=r-l+1
```

### 证明：
设$val_{l,r}$为选取区间$[l,r]$的代价

令上文中的$x=0,y=1$，则设我们选取的断点为$k$

分成$x$段的代价：

$$\max^r_{i=l}a_i \times (r-l+1)\ -\ \sum^r_{i=l} a[i]$$

分成$y$段的代价：

$$(\max^k_{i=l}a_i \times (k-l+1)\ -\ \sum^k_{i=l} a[i])\ + \ (\max^r_{i=k+1}a_i \times (r-k)\ -\ \sum^r_{i=k+1} a[i])$$

于是上面这个式子，我们把括号去掉，就变成了

$$\max^k_{i=l}a_i \times (k-l+1)+\max^r_{i=k+1}a_i \times (r-k)\ -\ \sum^r_{i=l} a[i]$$

显然，对于任意的p,q，有

$$\max^r_{i=l}a[i] \ge \max^q_{i=p}a[i]|\ \ l \le p \le q \le r$$

所以

$$\max^k_{i=l}a_i \times (k-l+1)+\max^r_{i=k+1}a_i \times (r-k)\le \max^r_{i=l}a_i \times (r-l+1)$$

推广到任意的$x\lt y$的情况，即得出结论。

### 证毕

然后这就是一个很重要的性质，我们不需要再去考虑是否要把k次改变的机会全部都使用掉，因为全部都用掉比一定不会比不用掉差。

下面我们再考虑Dp的主体

状态设计：设$f[i][j]$表示我们已经处理了前$i$组蛇，并且已经使用了$j$次变化的机会

思考一下，显然有$f[i][j]=\min (f[i][j],f[k][j-1]+val(k+1,i))$

其中$k \lt i$，这个转移方程的意思就是把$[k+1,i]$这个区间放到一起，用同一个大小的网进行捕捉

联系到我们上面转化的模型，也就是在$k$这个位置后面插入一个断点

由此，我们就可以写出Dp

但是我们要求速度！如何快速求出$val(l,r)$呢？

我们注意到$val(l,r)$里面需要求一个区间和，以及一个区间最大值

区间和：前缀和维护

区间最大值：ST表维护

这样就把求$val(l,r)$的时间从$N^2$优化到了$Nlog_2N$

目前是这道题的Rk1，开了一坨蛇皮优化之后，52ms（评测机可能有波动）

Code：

```
//Copyright (c) 2019 by xiao_mmQF. All Rights Reserved.
#include<bits/stdc++.h>
// #include<bits/extc++.h>
// #define int long long
#define GCC optimize(3)
#define inl inline
#define reg register
// #define db long double
using namespace std;
// using namespace __gnu_pbds;
inl int read(){ int x=0,f=0; char ch=0; while(!isdigit(ch))f|=(ch=='-'),ch=getchar(); while(isdigit(ch))(x*=10)+=(ch^48),ch=getchar(); return f?-x:x; }
inl void Print(reg int x) { if(x<0)putchar('-'),x=-x; if(x>=10)Print(x/10); putchar(x%10+'0'); }
inl void Println(reg int x){Print(x);putchar('\n');}
inl int Max(reg int x,reg int y){return x>y?x:y;}
inl int Min(reg int x,reg int y){return x<y?x:y;}
inl int Abs(reg int x){return x<0?-x:x;}

//上面都是模板

int n,m ;
const int MAXN=440;
int lg2[MAXN];//维护log2[1-N]
int pre[MAXN];//维护前缀和
int mx[MAXN][11];
int f[MAXN][MAXN];
inl int sum(int lx, int rx) {
    int l=lg2[rx-lx+1];
    int Mx=Max(mx[lx][l-1],mx[rx-(1<<(l-1))+1][l-1]);
    // printf("[%d,%d]=%d\n",lx,rx,Mx);
    return Mx*(rx-lx+1)-(pre[rx]-pre[lx-1]);
}
signed main() {
	n=read(),m=read()+1;
    for(reg int i=1;i<=n;++i)lg2[i]=lg2[i>>1]+1;//我求的是第一个满足1>>k > i的k
	for(reg int i=1;i<=n;++i)mx[i][0]=read(),pre[i]=pre[i-1]+mx[i][0];
    for(reg int i=1;i<=lg2[n];++i)
    for(reg int j=1;j<=n;++j){
        reg int k=j+(1<<(i-1));mx[j][i]=mx[j][i-1];
        if (k<=n)mx[j][i]=Max(mx[j][i],mx[k][i-1]);
    }//标准的ST表操作
	// memset(f,0x3f,sizeof(f));
    for(reg int i=0;i<=n;++i)
    for(reg int j=0;j<=m;++j)
    f[i][j]=0x3f3f3f3f;
	f[0][0]=0;
	for(reg int i=1;i<=n;++i)
		for(reg int k=0;k<i;++k)
			for(reg int j=1;j<=Min(m,i);++j)
				f[i][j]=Min(f[i][j],f[k][j-1]+sum(k+1,i)) ;//Dp的转移
	Println(f[n][m]);
	return 0 ;
}

```

---

## 作者：ModestCoder_ (赞：6)

非常简单的一个dp题目

先预处理$sum_{i,j}$表示用一个网把区间$[i,j]$的蛇全抓走的代价

然后暴力dp

$dp_{i,j}$表示到第$i$条蛇，用了$j$个网的最小代价


$dp_{i,j}=min(dp_{k,j-1}+sum_{k+1,i})$

Code：


```cpp
#include <bits/stdc++.h>
#define maxn 410
#define LL long long
using namespace std;
LL a[maxn], b[maxn][maxn], dp[maxn][maxn];
int n, m;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read(), m = read() + 1;
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i){
		LL sum = 0, Max = 0;
		for (int j = i; j <= n; ++j) Max = max(Max, a[j]), sum += a[j], b[i][j] = Max * (j - i + 1) - sum;
	}
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= m; ++j) dp[i][j] = 1e9;
	dp[0][0] = 0;
	for (int k = 1; k <= m; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < i; ++j)
				dp[i][k] = min(dp[i][k], dp[j][k - 1] + b[j + 1][i]);
	printf("%lld\n", dp[n][m]);
	return 0;
}
```


---

## 作者：vеctorwyx (赞：3)

### 本人比较弱，做法比较朴素

$N$远小于$a_i$，~~随手~~离散化。

设状态$dp_{i,j,k}$表示抓到第$i$组蛇，改了$j$次网，当前网的大小为$k$的最小代价。（$j<i-1,k>a_i$）

同时开一个数组$g_{i,j}$记录前$i$组蛇，改了$j$次网的最小代价。

则转移方程为：

$$\large dp_{i,j,k} = min(dp_{i -1,j,k} + a_i - k, g_{i - 1,j - 1})$$

当然这是$j>0$的情况，$j=0$直接


$$\large dp_{i,j,k} = dp_{i -1,j,k} + a_i - k$$

这种做法复杂度$O(n^3)$，可过。

**但是空间炸了。。。**

~~压空间多简单啊，滚动一下不就好了~~

回到转移方程，可以发现$dp_{i,j,k}$只会从$dp_{i-1,j,k}$以及$g$数组转移。

所以$dp$数组的第一维就可以直接删掉了。

然后内存就小了很多，就能过了。

当然要注意的是$k<a_i$的部分不用时要被赋最大值，否则会锅。

__离散化！！！__

代码写的不是很好，仅供参考

code：

```
#include<bits/stdc++.h>
using namespace std;
int n, o;
int a[410], lsh[410];
struct node{
	int dat, id;
	bool operator < (const node &x)const {
		return dat < x.dat;
	}
}b[410];
int dp[410][410];
int cnt, pl[410];
int ans = 0x7f7f7f7f;
int dp1[410][410];
signed main(){
	memset(dp, 0x3f, sizeof(dp));
	memset(dp1, 0x3f, sizeof(dp1));
	scanf("%d%d", &n, &o);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), b[i].dat = a[i], b[i].id = i;
	sort(b + 1, b + 1 + n);
	b[0].dat = -1; 
	for(int i = 1; i <= n; i++){//手动离散化
		if(b[i].dat != b[i - 1].dat)
			cnt++;
		lsh[b[i].id] = cnt;
		pl[cnt] = b[i].dat;
	}
	for(int i = 1; i <= cnt; i++)
		dp[0][i] = 0;
	dp1[1][0] = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= o; j++)
			for(int k = 1; k <= cnt; k++){
				if(k < lsh[i]){//空闲的部分赋极大值
					dp[j][k] = 0x3f3f3f3f;
					continue;
				}
				if(j >= 1)//j-1可能小于0
					dp[j][k] = min(dp[j][k] + pl[k] - pl[lsh[i]], dp1[i - 1][j - 1] + pl[k] - pl[lsh[i]]);
				else
					dp[j][k] = dp[j][k] + pl[k] - pl[lsh[i]];
				dp1[i][j] = min(dp1[i][j], dp[j][k]);
				if(i == n)
					ans = min(dp[j][k], ans);
			}
	}
	printf("%d\n", ans);
}
```

---

## 作者：1saunoya (赞：3)

$\text{一道比较经典的区间}$ $DP$

$\text{定义数组}$ $sum_{i,j}$ 
$\text{表示抓 i
 -> j 蛇的代价}$
 
 $\text{我觉得前缀和可做 但是我的方法更容易理解叭}$
 
 ~~~
 for(register int i = 1 ; i <= n ; i ++) {
		int last = a[i] ;
		for(register int j = i + 1 ; j <= n ; j ++)
			if(last < a[j]) {
				sum[i][j] = sum[i][j - 1] + (a[j] - last) * (j - i) ;
				last = a[j] ;
			}
			else sum[i][j] = sum[i][j - 1] + (last - a[j]) ;
	}
 ~~~
 $\text {另一种sum}$ $\text{求法是}$ $max(a[i] - > a[j]) * (j - i + 1)- \sum_{k = i}^{j} a[k]$ 
 应该是可以 在 
 $\Theta(n^2)$ $\text{可以优化成 st表 + 前缀和 ， 可以变成 n log n + n + n 整体还是O(n log n) 的}$ $\text{可是DP是}$$n^3$$\text{的，所以优化这个地方是没有意义的。}$
 
 $\text{另一个是dp数组 i表示当前抓了几组 ， j 表示用了j次变袋子大小的能力}$
 $\text{dp 方程 是 dp[i][j] = min(dp[i][j] , dp[k][j - 1] + sum[k + 1][i])}$
 
 
 ```cpp
 
 //Isaunoya
#include <bits/stdc++.h>
using namespace std ;
inline int read() {
	register int x = 0 , f = 1 ;
	register char c = getchar() ;
	for( ; ! isdigit(c) ; c = getchar()) if(c == '-') f = -1 ;
	for( ; isdigit(c) ; c = getchar()) x = (x << 1) + (x << 3) + (c & 15) ;
	return x * f ;
}
inline int PW(int x , int y , int Mod) {
	register int ans = 1 ;
	for( ; y ; y >>= 1 , x = (x * x) % Mod)
		if(y & 1) ans = (ans * x) % Mod ;
	return ans ;
}

int n , m ;
const static int N = 400 + 5 ;
int a[N] ;
int sum[N][N] ;
int f[N][N] ;

signed main() {
	freopen("snakes.in" , "r" , stdin) ;
	freopen("snakes.out" , "w" , stdout) ;
	n = read() , m = read() ; m ++ ;
	for(register int i = 1 ; i <= n ; i ++) a[i] = read() ;
	for(register int i = 1 ; i <= n ; i ++) {
		int last = a[i] ;
		for(register int j = i + 1 ; j <= n ; j ++)
			if(last < a[j]) {
				sum[i][j] = sum[i][j - 1] + (a[j] - last) * (j - i) ;
				last = a[j] ;
			}
			else sum[i][j] = sum[i][j - 1] + (last - a[j]) ;
	}
//	for(register int i = 1 ; i <= n ; i ++) printf("%d\n" , sum[i][n]) ;
	memset(f , 0x3f , sizeof(f)) ;
	f[0][0] = 0 ;
	for(register int j = 1 ; j <= m ; j ++)
		for(register int i = 1 ; i <= n ; i ++)
			for(register int k = 0 ; k <= i - 1 ; k ++)
				f[i][j] = min(f[k][j - 1] + sum[k + 1][i] , f[i][j]) ;
//	for(register int i = 1 ; i <= m ; i ++) printf("%d" , f[n][i]) ;
//	for(register int i = 1 ; i <= n ; i ++){
//		for(register int j = 1 ; j <= m ; j ++) printf("%d " , f[i][j]) ;
//		puts("") ;
//	}
	int ans = INT_MAX ;
	for(register int i = 1 ; i <= m ; i ++) ans = min(ans , f[n][i]) ; 
	printf("%d\n" , ans) ;
	return 0 ;
}
/*
5 1
1 2 3 4 5
*/

```

---

## 作者：破忆 (赞：2)

### 【题目大意】
有n个数，a[1...n]

可以分成至多k+1段，其中一段的代价为Σh-a[i]，h为自己选择的数，必须大于此段中的任意a[i]，求最小代价

### 【分析】

首先想到DP

可以设f[i][j]表示前i个，换了j次的最小代价

状态转移也很容易写

```
f[i][j]=min(f[i][j],f[t][j-1]+g[t+1][i]);
```
复杂度 n^2*k,可以通过

g[l][r]表示[l,r]这一区间的最小代价

![](https://cdn.luogu.com.cn/upload/image_hosting/a6v20fdb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

阴影的面积表示代价

显然，要使阴影部分最小，h应选择区间内最大值

#### 那么如何快速统计区间代价最小值？

假设[l,r-1]的代价以及区间最大值已经知道，记为h

考虑[l,r]的代价

#### 如果a[r]>h

![](https://cdn.luogu.com.cn/upload/image_hosting/5fmgur9i.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么新增的代价为 (r-l)*(a[r]-h）  （红色部分）

同时需要更新h

#### 如果a[r]<=h

![](https://cdn.luogu.com.cn/upload/image_hosting/anns92h1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么新增的代价为 h-a[i]  （蓝色部分）

那么,g[l][r]就可以以n^2的复杂度求了

### 坑点

记得开long long

~~NOIP2018龙虎斗惨案~~

~~3年OI一场空，不开longlong见祖宗~~

### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn=405;
int n,k;
int a[maxn];
LL g[maxn][maxn];
LL f[maxn][maxn],ans=1ll<<60;
//f[i][j] 前i条蛇，网换了j次的最小代价 
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
// 	freopen("pa.in","r",stdin);
// 	freopen("pa.out","w",stdout);
	n=read(),k=read()+1;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){
		LL now=0,maxh=0;
		for(int j=i;j<=n;j++){
			if(a[j]>maxh){
				g[i][j]=g[i][j-1]+(LL)(j-i)*(a[j]-maxh);
				maxh=a[j];
			}
			else g[i][j]=g[i][j-1]+maxh-a[j];
		}
	}
	memset(f,63,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=k;j++)
	for(int t=0;t<i;t++)
	f[i][j]=min(f[i][j],f[t][j-1]+g[t+1][i]);
	for(int i=1;i<=k;i++) ans=min(ans,f[n][i]);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：盖矣斌峥 (赞：2)

[本人博客](https://prime.design.blog/)


------------
题目大意：给你一个长度为n的序列，你可以将它分成不大于k+1段连续子序列，求每段序列的最大值乘序列长度减去序列的和的和的最小值是多少

相信大家看了我翻译出来的题目大意之后应该有一点感觉了吧

再看看数据范围k<=n<=**400**...嗯......

于是瞬间想到一个O(n^3)的DP算法

我们先预处理一个序列的前缀和a[]，以及序列的最大值Max[][]

设f[i]表示捕捉完1~i的蛇最少浪费多少，预处理dp数组f[i]=Max[1][i]*i-a[i]

给出转移方程
```
	while(k--)
	{
		for(int i=n;i>=1;--i)
			for(int j=1;j<i;++j)
			f[i]=min(f[i],f[j]+Max[j+1][i]*(i-j)-a[i]+a[j]);
	}
```
来解释一下我的转移，我一共转移了k次，在执行完x(1<=x<=k)次操作后，f[i]代表的是把捕捉完1~i的蛇，期间一共换了x次捕网的最小浪费空间

中间类似一个01背包倒序降维的操作，因为换x次捕网，只能由换x-1次来转移，所以把i倒序，压掉一维

然后那个f[i]=f[j]+Max[j+1][i]*(i-j)-a[i]+a[j]就是在捕捉完1~j的蛇后将捕网大小换成Max[j+1][i]


**代码**
```
#include<cstdio>
#include<iostream>
using namespace std;
inline int read()
{
	int ans=0,flag=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){flag|=ch=='-';ch=getchar();}
	while('0'<=ch&&ch<='9'){ans=(ans<<1)+(ans<<3)+(ch^48);ch=getchar();}
	return flag?-ans:ans;
}
inline int max(int x,int y){return x>y?x:y;}
int n,k,a[405];
int f[405];
int Max[405][405];
int main()
{
	n=read();k=read();
	for(int i=1;i<=n;++i)
	{
		Max[i][i]=read();
		a[i]=a[i-1]+Max[i][i];
	}
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			Max[i][j]=max(Max[i][j-1],a[j]-a[j-1]);
	for(int i=1;i<=n;++i)f[i]=Max[1][i]*i-a[i];
	while(k--)
	{
		for(int i=n;i>=1;--i)
			for(int j=1;j<i;++j)
			f[i]=min(f[i],f[j]+Max[j+1][i]*(i-j)-a[i]+a[j]);
	}
	printf("%d",f[n]);
	return 0;
}
```

~~自认为我的代码是很好理解的~~  /滑稽

---

## 作者：LevenKoko (赞：2)

$$\Large\href{https://www.cnblogs.com/zhenglw}{\textcolor{red}{My Blog}}$$

显然是DP......

然而考场写了个假算法，$O(n^3m)$的DP，而且毒瘤出题人并没有具体的数据范围，只给了一个n<=400...

 

考场上$O(n^3m)$的算法拿了48pts；

由于常数的问题是所有打部分分的人里面得分最高的；

然而出考场用了毒瘤方法卡常后拿了70+pts(在Luogu上甚至拿了80pts)

**先贴个假算法：**

令$f[i][j][k]$表示当前在抓第$i$堆蛇，从$i$开始到$i+j-1$堆蛇都用一种背包大小抓，已经用了k个蛇袋子；

显然这里要用$[i,i+j-1]$中的最大值来抓这个区间内所有的蛇；

不难得到转移方程：
$$f[i][j][k]=min\{f[p][i-p][k-1]\}+Max(i,i+j-1)*j-(sum[i+j-1]-sum[i-1])$$

其中$Max(l,r)$表示区间$[l,r]$中$a[]$的最大值，$sum[i]$为$a[]$的前缀和

 

**但是——考试的时候毒瘤出题人还卡了空间...**

于是乎我们观察到$f[i][j][k]$中的状态$k$只与$k-1$有关，所以把第三维压掉即可

（代码写的有点难以描述，但是反正是假算法，将就一下呗）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int ans=0,f=1;char chr=getchar();
    while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
    return ans*f;
}const int M = 405;
int f[M][M][2],a[M],n,K,s[M],g[M][M];
signed main(){
    n=read(),K=read();
    for(int i=1;i<=n;i++)a[i]=read(),s[i]=a[i]+s[i-1];
    for(int len=1;len+1-1<=n;len++){
        int maxn=0;
        for(int i=1;i<=len;i++) maxn=max(maxn,a[i]);
        g[1][len]=maxn*len-s[len];
    }memset(f,0x3f,sizeof(f));
    for(int k=1;k<=K;k++)
        for(int i=k+1;i<=n;i++)
            for(int j=1;j<=n-i+1;j++){
                int maxn=0;
                for(int p=i;p<=i+j-1;p++)maxn=max(maxn,a[p]);
                f[i][j][k&1]=g[1][i-1];
                for(int p=2;p<i;p++){
                    if(k-1==0&&p!=1) continue;
                    f[i][j][k&1]=min(f[p][i-p][k&1^1],f[i][j][k&1]);
                }f[i][j][k&1]+=maxn*j-s[i+j-1]+s[i-1];
            }int ans=0x7f7f7f7f7f;
    for(int i=K+1;i<=n;i++)ans=min(ans,f[i][n-i+1][K&1]);
    cout<<ans<<endl;
    return 0;
}
```

### 考虑优化这个算法：

#### 方法一：

**智商不够，数据结构来凑**

因为转移的时候枚举的是$f[p][i-p][k-1]$，也就是说我们的第一维状态和第二维状态之间其实是线性关系（因为在一次转移过程中$i$的值是确定的），所以我们可以考虑用线段树来优化这个枚举$p$的过程，然后求$a[]$数组一段的最大值我们可以用线段树，也可以用st表，也可以直接O(n^3)预处理

时间复杂度$O(n^2mlogn)$

因为跑不满所以理论上可以过，然而由于线段树自带大常数，所以并不推荐（其实我也没试过）

 

#### 方法二：

其实我们的状态设计的并不是很好，因为$f[i][j][k]$的状态设计已经潜在的要求了我们枚举$i,j$两个状态，我们能不能通过改变状态来减少枚举的维度呢？

显然是可以的，因为$f[i][j][k]$中只有$j$这个状态看着十分鸡肋，因为状态$i$显然是必须的，而状态$k$是只与$k-1$有关的，所以不用管它们；

根据这个思路，我们重新设计状态，设$f[i][j]$表示前面$i$个已经处理好了，并且已经用了j张网

不难拿到方程：
$$f[i][j]=Min\{f[k][j-1]+Max(k+1,i)*(i-k)-(sum[i]-sum[k])\}$$

其中Max我们用st表预处理然后O(1)求就好了

~~老年选手并不打算卡常......所以就贴一个正常的代码惹qwq~~

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int ans=0,f=1;char chr=getchar();
    while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
    return ans*f;
}const int M = 405;
int st[M][15],n,a[M],m,p[20],f[M][M],s[M],lg2[M]={-1};
#define min(x,y) ((x)>(y)?(y):(x))
#define max(x,y) ((x)<(y)?(y):(x))
inline int Max(int l,int r){
    int px=lg2[r-l+1];
    return max(st[l][px],st[r-p[px]+1][px]);
}
int main(){
    freopen("snakes.in","r",stdin);
    freopen("snakes.out","w",stdout);
    n=read(),m=read(),p[0]=1;
    for(register int i(1);i<=n;++i)a[i]=read(),st[i][0]=a[i],s[i]=s[i-1]+a[i],lg2[i]=lg2[i>>1]+1;
    for(register int j(1);j<=14;p[j]=p[j-1]<<1,++j)
        for(register int i(1);i<=n;++i)
            st[i][j]=max(st[i][j-1],st[i+p[j-1]][j-1]);
    for(register int i(1);i<=n;++i)f[i][0]=Max(1,i)*i-s[i];
    for(register int i(2);i<=n;++i)
        for(register int j(1);j<=min(i-1,m);++j){
            f[i][j]=0x3f3f3f3f;
            for(register int k(1);k<i;++k)
                f[i][j]=min(f[k][j-1]+Max(k+1,i)*(i-k)-s[i]+s[k],f[i][j]);
        }printf("%d\n",f[n][m]);
    return 0;
}
```
 

---

## 作者：Daniel_7216 (赞：1)

题目大意：将一个区间分为最多 $K+1$ 个子区间，每个子区间的代价为区间最大值，求最小代价。可以得到方程：

$dp_{i,j} = \min\limits_{k=1}^{i}(dp_{i,j}, dp_{k -1,j} + g_{k,i})$

$g_{l,r} = \max\limits_{i=l}^{r}(a_i) \times(r - l + 1)-\sum\limits_{i=l}^{r}a_i$

其中 $dp_{i,j}$ 表示捕了前 $i$ 组蛇，且调整了 $j$ 次大小的最小浪费，$g_{l,r}$ 表示用一张网捕 $[l,r]$ 的所有蛇最小浪费。显然一个区间用一张网捕的话，这张网的大小就是区间最大值。

如何确定初始的大小呢？~~看过题解后~~可以知道一个技巧，那就是强制规定初始设置也算一次调整，这样就可以同样适用转移方程。

还有就是如何计算 $g_{l,r}$ 呢？根据前面推出的性质可得：

$\sum\limits_{i =l}^{r}\max\limits_{j=l}^{r}(a_j)-a_i$

$=\sum\limits_{i =l}^{r}\max\limits_{j=l}^{r}(a_j)-\sum\limits_{i =l}^{r}a_i$

$=\max\limits_{i=l}^{r}(a_i) \times(r - l + 1)-\sum\limits_{i=l}^{r}a_i$

这样我们就无须在转移时 $O(N)$ 计算，可以在枚举时直接维护第一个式子，再用前缀和算第二个式子。

代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int n, K, a[401], dp[401][401], maxx, sum[401];
int g(int i, int j){
	return maxx * (j - i + 1) - (sum[j] - sum[i - 1]);
}
int main(){
	scanf("%d%d", &n, &K);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	K++;
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= min(K, i); j++){
			maxx = a[i];
			for (int k = i; k >= 1; k--){
				dp[i][j] = min(dp[i][j], dp[k - 1][j - 1] + maxx * (i - k + 1) - (sum[i] - sum[k - 1]));
                maxx = max(maxx, a[k - 1]);
			}
		}
	}
	int ans = 2147483647;
	for (int i = 0; i <= K; i++){
		ans = min(ans, dp[n][i]);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Cat_shao (赞：1)

这里给出一种十分暴力的 $O(n^3)$ dp 。

题目中的 $N \le 400$ 提示我们能通过这道题的时间复杂度约为多项式，可以考虑下 dp 。

对于第 $i$ 组蛇，它需不需要调整网的大小、浪费等数值只跟 $i - 1$ 相关的数值有关系，也就是无后效性。这样确认了用 dp 求解似乎可行，尝试着设计状态。

根据题目中的信息，记 $f[i][j][k]$ 表示抓 $1 \sim i$ 这些组蛇，改变了 $j$ 次网的大小，网最终的大小为 $k$ 这种情况下总浪费空间的最小值。目标即为 $\begin{aligned} \max_{0 \le i \le K, 0 \le j \le \text{值域}}f[n][i][j] \end{aligned}$ 。其中值域表示一组蛇最多有多少条，本题中是 $10^6$ 。

对于 $f[i][j][k]$ ，如果 $a_i > k$ ，那么无法装下第 $i$ 组蛇，将其赋值为 $\infty$ （在实现中就是一个很大的数，表示正无穷）。如果能装得下，那么有两种选择：
1. 这个网我不用动就能装下第 $i$ 组蛇：以前浪费的空间 + 这次装蛇浪费的空间，也就是 $f[i - 1][j][k] + k - a_i$ 。
2. 这个网太小不合适（装不下或是有浪费空间）需要更改大小才能装下：以前浪费的空间的最小值 + 这次浪费的空间 $\min_{x  \in [0, \text{值域}]}f[i - 1][j - 1][x] + k - a_i$ 。

合起来就得到了下面这个式子：

$$f[i][j][k] = \left \{ \begin{aligned} 
& {\infty} & (k < a_i)\\
& f[i - 1][j][k] + k - a_i & (j = 0 \text{ 且 } k \ge a_i)\\
& \min \left ( f[i - 1][j][k], \min_{x  \in [0, \text{值域}]}f[i - 1][j - 1][x]\right) + k - a_i& (j > 0 \text{ 且 }k \ge a_i)
\end{aligned} \right.$$

其中第二行是特判，防止 $j -1 < 0$ 造成的越界访问。

到现在这个式子直接转移是 $O(n^3 \times \text{值域})$ ，空间是 $O(n^2 \times \text{值域})$ 的，过不去。先把题目中给我们的原序列离散化了，值域变为 $O(n)$ ，时间复杂度变为 $O(n^4)$ ，空间复杂度变为 $O(n^3)$ 。

观察式子中的 $\min_{x  \in [0, \text{值域}]}f[i - 1][j - 1][x]$ 与 $k$ 无关，在 $i, j$ 不变 $k$ 变的时候不需要算多次。时间复杂度变为 $O(n^3)$ 。

算 $f[i][j][k]$ 只需要 $f[i - 1][][]$ ，可以使用滚动数组，空间复杂度变为 $O(n^2)$ 。


至此题目得解，时间复杂度 $O(n^3)$ ，空间复杂度 $O(n^2)$ ，可以通过此题。

```cpp
//
// Created by Cat-shao on 2022/4/29.
//

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 405;
const long long INF = 0x3f3f3f3f3f3f3f3f;

int a[MAX_N], h[MAX_N];
long long f[2][MAX_N][MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, K, u;
    cin >> n >> K;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    memcpy(h + 1, a + 1, n * sizeof(int));
    sort(h + 1, h + n + 1);
    u = unique(h + 1, h + n + 1) - (h + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(h + 1, h + u + 1, a[i]) - h;
    }
    memset(f, 0x3f, sizeof(f));
    memset(f[0][0], 0, sizeof(f[0][0]));
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            memset(f[i & 1], 0x3f, sizeof(f[i & 1]));
        }
        for (int k = 1; k < a[i]; ++k) {
            f[i & 1][0][k] = INF;
        }
        for (int k = a[i]; k <= u; ++k) {
            f[i & 1][0][k] = f[(i - 1) & 1][0][k] + h[k] - h[a[i]];
        }
        for (int j = 1; j <= K; ++j) {
            long long tmp1 = *min_element(f[(i - 1) & 1][j - 1], f[(i - 1) & 1][j - 1] + u + 1);
            for (int k = 1; k < a[i]; ++k) {
                f[i & 1][j][k] = INF;
            }
            for (int k = a[i]; k <= u; ++k) {
                f[i & 1][j][k] = min(f[(i - 1) & 1][j][k], tmp1) + h[k] - h[a[i]];
            }
        }
    }
    long long ans = INF;
    for (int i = 0; i <= K; ++i) {
        for (int j = 0; j <= u; ++j) {
            ans = min(ans, f[n & 1][i][j]);
        }
    }
    cout << ans;
    return 0;
}
```

所以这题为什么是蓝题？

---

## 作者：Diaоsi (赞：1)

**分段 dp**

方程挺显然的，设 $f_{i,k}$ 表示当前捕捉了前 $i$ 组蛇，改变了 $k$ 次捕网大小时总浪费空间的最小值。

有一个 $\mathcal{O(n^3)}$ 的转移：

$$f_{i,k}=\min_{0\leq j <i}\{f_{j,k-1}+\text{calc}(j+1,i)\}$$

其中 $\text{calc}(l,r)$ 表示捕捉区间 $[l,r]$ 的蛇浪费空间的最小值。

显然：

$$\text{calc}(l,r)=\max_{l \leq i \leq r}\{a_i\} \ast (r-l+1) -\sum_{i=l}^r a_i$$

$\sum_{i=l}^r a_i$ 可以用前缀和 $\mathcal{O(1)}$ 地求，至于 $\max_{l \leq i \leq r}\{a_i\} $ ，我看到很多题解都用了类似于 ST 表之类的能求区间最值的数据结构，或者在转移时记录最大值，其实不用那么麻烦，可以预处理出每个子区间的最大值，然后用数组记录下来，转移的时候直接 $\mathcal{O(1)}$ 查询就可以了。

预处理的时间复杂度是 $\mathcal{O(n^3)}$ 的，跟转移同阶。

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const int N=410,M=1000010,INF=0x3f3f3f3f;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int &x,int &y){x^=y^=x^=y;}
int n,m,ans=INF,a[N],sum[N],f[N][N],pre[N][N];
int calc(int l,int r){
	return pre[l][r]*(r-l+1)-(sum[r]-sum[l-1]);
}
int main(){
	scanf("%d%d",&n,&m);++m;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int k=i;k<=j;k++)
				pre[i][j]=Max(pre[i][j],a[k]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			for(int k=1;k<=m;k++)
				f[i][k]=Min(f[i][k],f[j][k-1]+calc(j+1,i));
	for(int i=0;i<=m;i++)
		ans=Min(ans,f[n][i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_Clown_ (赞：1)

这是一道动态规划题目。

我们先预处理出Sum数组，Sum[i][j]表示[i,j]这个区间用一个网捕捉的最小浪费。我们不妨这样计算：
$$Sum[i][j]=(j-i+1)*Max-Prefix$$

其中Max表示[i,j]区间蛇的最大值，Prefix表示[i,j]的和。

然后我们可以动态规划了。

设状态：Dp[i][j]表示前i组蛇，用j个网的最小浪费。

易证：
$$Dp[i][j]=min(Dp[i][j],Dp[k][j-1]+Sum[k+1][i])$$

意思是，这个点会从前一个点k推过来，前k个点用了j-1个网，k+1到i用了1个网（我们预处理过了）。

这样就可以A掉了，代码不放了。

---

## 作者：HHYQ_07 (赞：1)

# 题解

## [题目链接](https://www.luogu.com.cn/problem/P5424)

## 简洁题意

把一段长度 $N$ 的序列分成小于等于 $K+1$ 段，每一段区间中的最大值与这个区间中所有数差的和为这个区间的浪费空间。求所有区间中浪费空间的最小值。

## 大致思路

要求最终的最小值，而每一步的最小值都是从前面的最小值递推出来的，一步步推出答案，显然是[动态规划](https://oi.wiki/dp)的算法。

### 定义状态

$f_{i,j}$ 表示前 $i$ 个数共用了 $j$ 个区间最小的浪费空间。

### 转移方程

$$f_{i,j}=\min(f_{i,j},f_{k,j-1}+g_{k+1,i})$$

$g_{k+1,i}$ 表示区间 $[k+1,i]$ 的浪费空间。

### 时间复杂度

三重循环，$O(n^3)$ 的时间复杂度，$n\leq 400$，此题给了两秒是绝对够的。

## 处理细节

1. 浪费空间的计算方法为：区间长度乘区间最大值再减去区间和。区间和可以使用[前缀和](https://oi.wiki/basic/prefix-sum/)优化。最终的转移方程为：


$$f_{i,j}= \min(f_{i,j},f_{k,j-1}+(i-k)\times maxn-(sum_{i}-sum_{k}))$$

2. 要维护区间最大值，可以提前预处理出，或者倒叙枚举 $k$，初始最大值为 $a[i]$，每次更新最大值。

3. 答案要求最小值，就把 $f$ 数组 `memset` 成 `0x3f`，也就是无穷大，再令 $f_{0,0}=0$。

4. 题目中是最多能分 $K$ 次，所以最多应是 $K+1$ 段。

5. 最终不一定分成 $K+1$ 段是最小的，答案应是 $\min_{i=0}^{k+1} f_{n,i}$。

## AC code

C++：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,maxn,ans=1e9;
int a[405],sum[405],f[405][405];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=a[i]+sum[i-1];
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=min(i,m+1);j++)
		{
			maxn=a[i];
			for(int k=i-1;k>=0;k--)
			{
				f[i][j]=min(f[i][j],f[k][j-1]+(i-k)*maxn-(sum[i]-sum[k]));
				maxn=max(maxn,a[k]);
			}
		}
	for(int i=0;i<=m+1;i++)
		ans=min(ans,f[n][i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Supor__Shoep (赞：0)

首先分析数据范围，$1\leq K\leq N\leq 400$。再看一下题意，大概就是在 $N$ 个数字中进行不同位置的 $K$ 次操作，这个就是一个非常经典的 DP 模型——设 $dp_{i,j}$ 表示在前 $i$ 个数字当中，修改 $j$ 次 $s$ 的大小的最优答案。

这个时候我们先抛开数据范围不谈，进行一次朴素转移。这个经典模型的做法几乎是人尽皆知，我们在前 $i-1$ 个数当中选择一个 $k$，然后将 $[k+1,i]$ 的区间进行第 $j$ 次修改，形成了一个转移。则有：

$$dp_{i,j}=\min\{dp_{k,j-1}+\sum_{l=k+1}^{i}(\max\{a_{k+1},\dots,a_i\}-a_l) \}$$

然后代入数据范围，由于这种垃圾转移时间复杂度为 $O(n^4)$，所以肯定是不行的。

不难发现中间那个取 $\max$ 值是一个区间询问，我们先离线处理所有的 $\sum_{k=i}^j (\max\{a_i,\dots,a_j\}-a_k)$ 的值，这个很明显就是个 $O(n^3)$ 的处理，因此离线处理的时间复杂度和转移时间复杂度并列，总时间复杂度为 $O(n^3)$。

设 $f_{i,j}=\sum_{k=i}^j (\max\{a_i,\dots,a_j\}-a_k)$，则原转移方程变为：

$$dp_{i,j}=\min\{dp_{k,j-1}+f_{k+1,i}\}$$

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=405;
int dp[MAXN][MAXN];
int f[MAXN][MAXN];
int n,m;
int a[MAXN];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int len=1;len<=n;len++)
	{
		for(int i=1;i<=n-len+1;i++)
		{
			int j=i+len-1;
			int maxx=0;
			for(int k=i;k<=j;k++)	maxx=max(maxx,a[k]);
			for(int k=i;k<=j;k++)	f[i][j]+=maxx-a[k];
		}
	}
	for(int i=1;i<=n;i++)	dp[i][0]=f[1][i];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)	dp[i][j]=1e9;
		for(int j=1;j<=m;j++)
		{
			for(int k=0;k<i;k++)	dp[i][j]=min(dp[i][j],dp[k][j-1]+f[k+1][i]);
		}
	}
	int minn=f[1][n];
	for(int i=1;i<=m;i++)	minn=min(minn,dp[n][i]);
	cout<<minn;
	return 0;
}
```

---

## 作者：dxy2020 (赞：0)

一道经典的区间分段类动态规划。

设 $f_{i,j}$ 为捕前 $i$ 组蛇改变 $j$ 次网的浪费空间的最小值。

设 $ans_{i,j}$ 表示区间 $[i,j]$ 内只用一个网的浪费空间的最小值，$p_{i,j}$ 表示 $[i,j]$ 区间最大值,$sum_{i,j}$ 表示区间 $[i,j]$ 内元素之和。这三个数组我们可以直接预处理求出。

$ans_{i,j}=p_{i,j}×(j-i+1)-sum_{i,j}$

设捕从 $a_{k+1}$ 到 $a_i$ 的蛇只用一个网（即改变0次大小），则 $a_1$ 到 $a_k$ 用 $j-1$ 个网。

状态转移方程就很好写了：

$$f_{i,j}=\min\{{f_{k,j-1}+ans_{k+1,i}}\}$$

预处理：$f_{i,0}=ans_{1,i}$，其他全部为无穷大。

附上无注释的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;int s[405],ans[405][405];
int a[405],f[405][405],p[405][405];
signed main (){
	scanf ("%d%d",&n,&m);
	for (int i=1;i<=n;++i){
		scanf ("%d",a+i);
		s[i]=s[i-1]+a[i];
	}
	for (int i=1;i<=n;++i)
		p[i][i]=a[i];
	for (int i=1;i<=n;++i){
		int maxx=p[i][i];
		for (int j=i+1;j<=n;++j){
			if (a[j]>maxx) maxx=a[j];
			p[i][j]=maxx;
		}
	}
	for (int i=1;i<=n;++i)
		for (int j=i;j<=n;++j)
			ans[i][j]=p[i][j]*(j-i+1)-s[j]+s[i-1];
	for (int i=0;i<=400;++i)
		for (int j=0;j<=400;++j)
			f[i][j]=1<<30;
	for (int i=1;i<=n;++i)
		f[i][0]=ans[1][i];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int k=j;k<i;++k)
				f[i][j]=min (f[i][j],f[k][j-1]+ans[k+1][i]);
    int Ans=1<<30;
    for (int i=1;i<=m;++i)
    	Ans=min (Ans,f[n][i]);
	printf ("%d\n",Ans);
	return 0;
} 
```


---

## 作者：Coros_Trusds (赞：0)

# 题目大意

将一个长为 $n$ 的区间分为最多 $m+1$ 个子区间，每个子区间的代价为区间最大值，求最小代价。

$1\le n\le 400$。

# 题目分析

令 $dp[i][j]$ 为前 $i$ 条蛇用（改变）了 $j$ 张网的最小代价。

我们可以枚举断点 $k$，可以得到状态转移方程：

$$dp[i][j]\gets \min\{dp[k][j-1]+cost[k+1][i]\}$$

其中，$cost[l][r]$ 表示选区间 $[l,r]$ 的蛇（在一张网里）所需的最小代价。

枚举 $n,m$ 一层循环，枚举断点 $k$ 一层循环，找 $cost[k+1][i]$ 又一层循环，时间复杂度为 $\mathcal{O(n^4)}$。

我们不妨预处理出 $cost$ 数组，因为 $cost[l][r]=\max-a[l]+\cdots+\max-a[r]$，这其实是等价于 $cost[l][r]=\max\times(r-l+1)-\sum\limits_{i=l}^ra[i]$ 的。这样，我们就省掉了找最小值这一步，时间复杂度优化到 $\mathcal{O(n^3})$。时限为 $2s$，够了。

# 代码

```cpp
// Problem: P5424 [USACO19OPEN]Snakes G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5424
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Date:2022-06-07 22:30
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getchar();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getchar();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int INF = 0x3f3f3f3f;
const int N = 405;
int a[N],cost[N][N],dp[N][N];
//dp[i][j]:考虑了前 i 条蛇,用了 j 张网的最小代价
//dp[i][j] = min{dp[k][j - 1] + cost[k + 1][i]}
int n,m;
int main(void) {
	n = read(),m = read() + 1;
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	for (register int i = 1;i <= n; ++ i) {
		int maxx = 0,sum = 0;
		for (register int j = i;j <= n; ++ j) {
			maxx = std::max(maxx,a[j]),sum += a[j];
			cost[i][j] = maxx * (j - i + 1) - sum;
		}
	}
	mst(dp,0x3f);
	dp[0][0] = 0;
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = 1;j <= m; ++ j) {
			for (register int k = 0;k < i; ++ k) {
				dp[i][j] = std::min(dp[i][j],dp[k][j - 1] + cost[k + 1][i]);
			}
		}
	}
	int ans = INF;
	for (register int i = 1;i <= m; ++ i) ans = std::min(ans,dp[n][i]);
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：郑朝曦zzx (赞：0)

# 一 解题思路
**主要思路:** 动态规划（和其他题解差不多）

**状态设计：** 令 $dp_{i,j}$ 表示捕到第 $i$ 组蛇，使用不多于 $j$ 次设置网大小的机会时，最小的浪费空间。

**初始化：** 除了 $dp_{0,i}$ （没捕蛇的状态）为 $0$，其他状态都为无穷大。

**答案：** $dp_{n,k}$ 即为所求

**状态转移（重点）：** 

$dp_{i,use} = \min(dp_{i,use}, dp_{mid,use-1} + val_{mid+1,i})$

解释：$val_{l,r}$ 的含义是捕 $[l,r]$ 组的蛇在**不调整**网大小的情况下浪费的空间。

方程讨论的是：是否在此处调整网的大小。

# 二 具体实现
## 1 求解 $val_{l,r}$ 数组

先给代码：
```cpp
for (int i = 1; i <= n; ++i)
	{
		int maxnow = 0, sum = 0;
		for (int j = i; j <= n; ++j)
		{
			maxnow = max(maxnow, num[j]);
			sum += num[j];
			val[i][j] = maxnow * (j - i + 1) - sum;
		}
	}
```
$maxnow$ 记录的是这个区间的最大值，$sum$ 记录的是这个区间的总和，此处使用两层循环求解 $val$ 数组，复杂度 $O(n^{2})$。

## 2 状态转移
```cpp
for (int use = 1; use <= k; ++use)
    for (int i = 1; i <= n; ++i)
        for (int mid = 0; mid < i; ++mid)
            dp[i][use] = min(dp[i][use], dp[mid][use - 1] + val[mid + 1][i]);
```
代码和其他题解类似，此处说一下循环顺序，状态转移 $dp_{i,use}$ 的时候要用到 $dp_{mid,use-1}$，所以我们要先求出较小设置次数时的 $dp$ 值，这也是先枚举 $use$ 的原因。

# 完整代码
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 410;
int n, k;
int num[maxn], dp[maxn][maxn], val[maxn][maxn];
int main()
{
	scanf("%d %d", &n, &k);
	++k;
	for (int i = 1; i <= n; ++i)
		scanf("%d", &num[i]);
	for (int i = 1; i <= n; ++i)
	{
		int maxnow = 0, sum = 0;
		for (int j = i; j <= n; ++j)
		{
			maxnow = max(maxnow, num[j]);
			sum += num[j];
			val[i][j] = maxnow * (j - i + 1) - sum;
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0; i <= k; ++i)
		dp[0][i] = 0;
	for (int use = 1; use <= k; ++use)
		for (int i = 1; i <= n; ++i)
			for (int mid = 0; mid < i; ++mid)
				dp[i][use] = min(dp[i][use], dp[mid][use - 1] + val[mid + 1][i]);
	printf("%d\n", dp[n][k]);
	return 0;
}
```


---

## 作者：ricky0916 (赞：0)

首先可以知道一件事：若在捕 $ [i,j] $ 之间的蛇的过程中没有改变网的大小，那么浪费的空间为 $ \max\limits_{l=i}^j a_l\times (j-i+1)-\sum\limits_{l=i}^j a_l $

令 $ dp[i][j] $ 表示前 $ i $ 次捕蛇，修改 $ j $ 次网的大小所浪费空间的最小值。

转移方程：
$$ 
dp[i][j]=\min_{l=1}^{i-1}(dp[l][j-1]+\max_{m=l+1}^i a_m\times(i-l)-\sum_{m=l+1}^i a_m)
$$

注意 $dp[i][0]$ 的特判。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
static char buf[10000],*pa=buf,*pd=buf;
static char buf2[10],*pp=buf2;
#define getchar() pa==pd&&(pd=(pa=buf)+fread(buf,1,10000,stdin),pa==pd)?EOF:*pa++
inline void pc(char ch){
	*pp++=ch;
}
inline void pcc(){
	fwrite(buf2,1,pp-buf2,stdout);
	pp=buf2;
}
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
void write(int x){
	static int sta[20];
	int top=0;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) pc(sta[--top]+48);
}
int n,k,a[410],mxx[410][410],dp[410][410],sum[410];
inline int mx(int x,int y){
	return x>y?x:y;
}
inline int mn(int x,int y){
	return x<y?x:y;
}
int main(){
	n=read();
	k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			mxx[i][j]=mx(mxx[i][j-1],a[j]);
		}
		sum[i]=sum[i-1]+a[i];
	}
	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		dp[i][0]=mxx[1][i]*i-sum[i];
		for(int j=1;j<=k;j++){
			for(int kk=1;kk<i;kk++){
				dp[i][j]=mn(dp[i][j],dp[kk][j-1]+mxx[kk+1][i]*(i-kk)-(sum[i]-sum[kk]));
			}
		}
	}
	write(dp[n][k]);
	pcc();
	return 0;
}
```


---

## 作者：Ezis (赞：0)

我们可以设 $f[i][j]$ 表示前 $i$ 条蛇，改变 $j$ 次大小所得到的最小剩余空间。

初始化 $f[0][0]$ 为 $0$。

其余为$\inf$。

转移方程为：

$f[i][j]=min(f[i][j],f[k][j-1]+max*(i-k)-(s[i]-s[k]));$

每次把 $max$ 与 $a[k]$ 比较。
（ $k$ 从 $i-1$ 到 $0$ ）

最后的答案为最小的 $f[n][i]$。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[405];
int s[405];
int f[405][405];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i];
	m++;
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=min(m,i);j++){
            int mx=a[i];
            for(int k=i-1;k>=0;k--) {
                f[i][j]=min(f[i][j],f[k][j-1]+mx*(i-k)-(s[i]-s[k]));
                mx=max(mx,a[k]);
            }
        }
    int ans=1e9;
    for(int i=0;i<=m;i++)
    	ans=min(ans,f[n][i]);
    printf("%d",ans);
	return 0;
}
```


---

## 作者：lx_zjk (赞：0)

这道题我只想出了暴力的做法

$f[i][j][k]$表示到了第$i$个数 用了$j$个网 最后一个网的大小为$k$

因为$k$的大小在$[1, 1e6]$但是只有$[1, 400]$可以离散化一下 $b$表示离散化后的数组

$f[i][j][a[i]] = f[i - 1][j - 1][k]$

$f[i][j][k] = min(f[i][j][k], f[i - 1][j][k] + b[k] - b[a[i]])$

时间复杂度$O(n * n * m)$据说能过$70%$的数据

然后翻看了题解 我又知道了新的算法

$f[i][j]$表示到了第$i$个数 用了$j$个网的最小剩余空间

预处理一个$g[i][j]$函数表示区间$[i, j]$的最小剩余空间
用线段树来预处理

状态转移方程式也就比较易得

$f[i][j] = min(f[i][j], f[k][j - 1] + g[k + 1][i])$

所以有时$dp$会$TLE$可以考虑预处理$memset$

# Code

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

inline ll read() {
    ll f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a > b ? b : a)

const int MAX_N = 400 + 5;

#define int ll

int n, k, a[MAX_N], sum[MAX_N], g[MAX_N][MAX_N], f[MAX_N][MAX_N];

struct segment_tree {
	int l, r;
	int dat;
	#define ls(p) (p << 1)
	#define rs(p) (p << 1 | 1)
}t[MAX_N << 2];

inline void build (int p, int l, int r) {
	t[p].l = l; t[p].r = r;
	if (l == r) {
		t[p].dat = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	t[p].dat = max(t[ls(p)].dat, t[rs(p)].dat);
}

inline int query (int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r) 
		return t[p].dat;
	int mid = (t[p].l + t[p].r) >> 1, ans = -1E9;
	if (l <= mid)
		ans = max(ans, query(ls(p), l, r));
	if (r > mid)
		ans = max(ans, query(rs(p), l, r));
	return ans;
}

signed main() {
	n = read(); k = read();
	k ++ ;
	for (int i = 1; i <= n; i ++ ) 
		a[i] = read(), sum[i] = sum[i - 1] + a[i];
	build(1, 1, n);	
	for (int i = 1; i <= n; i ++ ) 
		for (int j = i; j <= n; j ++ ) 
			g[i][j] = query(1, i, j) * (j - i + 1) - (sum[j] - sum[i - 1]);
	memset(f, 127, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 0; j < i; j ++ ) {
			for (int l = 1; l <= k; l ++ ) {
				f[i][l] = min(f[i][l], f[j][l - 1] + g[j + 1][i]);
			}
		}
	}
	printf("%lld\n", f[n][k]);
	return 0;
}

```

---

