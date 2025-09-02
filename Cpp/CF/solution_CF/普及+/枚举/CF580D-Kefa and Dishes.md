# Kefa and Dishes

## 题目描述

$\texttt{songshe}$ 进入了一家餐厅，这家餐厅中有 $n\ (1\leqslant n\leqslant18)$ 个菜。$\texttt{songshe}$ 对第 $i$ 个菜的满意度为 $a_i\ (0\leqslant a_i\leqslant10^9)$。

对于这 $n$ 个菜，有 $k\ (0\leqslant k\leqslant n^2-n)$ 条规则：如果 $\texttt{songshe}$ 在吃完第 $x_i$ 个菜之后立刻吃了第 $y_i\ (x_i\neq y_i)$ 个菜，那么会额外获得 $c_i\ (0\leqslant c_i\leqslant10^9)$ 的满意度。

$\texttt{songshe}$ 要吃 $m\ (1\leqslant m\leqslant n)$ 道任意的菜，但是他希望自己吃菜的顺序得到的满意度最大，请你帮 $\texttt{songshe}$ 解决这个问题。

## 样例 #1

### 输入

```
2 2 1
1 1
2 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 3 2
1 2 3 4
2 1 5
3 4 2
```

### 输出

```
12
```

# 题解

## 作者：Moon_Goddy (赞：13)

蒟蒻第一次独立写出状压 dp，分享一下我的思路。

首先看到 $n \leq 18$ 自然就想到了爆搜和状压 dp。

又因为吃菜的**顺序影响答案**，所以使用 dp 来转移。


------------


设 $f(i,j)$ 的第一维表示当前状态，也就是**已经吃了**的菜；第二维表示此时**最后**吃的菜。

为什么这么做呢？因为吃菜的**顺序**会有额外的满意度增加，这样设计方便转移。时间复杂度是 $O(2^nn^2) \approx 10^8$,CF 少爷鸡完全可过。

最后还有一些小细节比如开 long long 之类的。

具体内容见代码（附注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl putchar('\n')
#define ll long long
#define qwq printf("Moon")
#define en putchar(' ')
#define yes printf("Yes")
#define no printf("No")
#define mp make_pair

template<typename T>inline void read(T&x){
	x=0;char q;bool f=1;
	while(!isdigit(q=getchar()))if(q=='-')f=0;
	while(isdigit(q)){
		x=(x<<1)+(x<<3)+(q^48);
		q=getchar();
	}
	x=f?x:-x;
}
template<typename T>inline void print(T x){
	if(x<0){
		x=-x;
		putchar('-');
	}
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
const int N=20,M=(1<<18)+5;//262144
int n,a[N],m,k;
int ex[N][N];//额外满意度
ll f[M][N];
ll ans;
int calc(int a){//统计吃了多少菜
	int res=0;
	for(int i=0;i<n;i++)res+=((a>>i)&1);
	return res;
}
int main(){
	read(n);read(m);read(k);
	
	for(int i=1;i<=n;i++){
		read(a[i]);
		f[1<<(i-1)][i]=a[i];//吃且仅吃了第i份，当前最后吃的是第i份
	}
	for(int i=1;i<=k;i++){
		int x,y,c;
		read(x);read(y);read(c);
		ex[x][y]=c;
	}
	for(int i=1;i<(1<<n);i++){//枚举所有状态
		int tmp=calc(i);
		if(tmp>m)continue;//吃多了
		if(tmp==m){
			for(int j=1;j<=n;j++)
				if((i>>(j-1))&1)//在吃过的菜中选最后吃的
					ans=max(ans,f[i][j]);
			continue;
		}
		for(int j=1;j<=n;j++){//枚举要吃的菜
			if((i>>(j-1))&1)continue;//已经吃过
			
			for(int u=1;u<=n;u++){//枚举已经吃过的菜
				if((i>>(u-1))&1)
					f[i|(1<<(j-1))][j]=max(f[i|(1<<(j-1))][j],f[i][u]+a[j]+ex[u][j]);//吃了之后当前最后吃的就是j
			}
			
		}
	}
	print(ans);
	return 0;
}

```




---

## 作者：Jμdge (赞：8)

不是很想解释，就是状压dp嘛！QAQ，程序里稍微讲讲各位大佬就懂了吧。

我作为一个蒟蒻就来发发the first题解历练一下吧。_ __(:з」∠)_ _


------------


```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read()
{
	ll x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}
ll n,m,k,ans;
ll a[20],ad[20][20],f[(1<<18)+5][20];
//     以下为有效内容   //
int main()
{
	n=read(); m=read(); k=read();
	for(int i=0;i<n;++i)
		a[i]=read();
	for(int i=0;i<k;++i)  //做的时候编号从0开始
		ad[read()-1][read()-1]=read();
	for(int i=0;i<n;++i)  //先吃任意一个，满意度就是a[i]
		f[1<<i][i]=a[i];
	
	for(int now=0;now < (1<<n);++now) //枚举状态
	{
		int cnt=0;  //计算已经吃了几道菜
		for(int i=0;i<n;++i) if(now & (1<<i)) //枚举吃的最后一道菜
		{
			++cnt;
			for(int j=0;j<n;++j) if(!(now & (1<<j))) //枚举接下来吃的那道菜
				f[now|(1<<j)][j]=max(f[now|(1<<j)][j] , f[now] [i]+a[j]+ad[i][j]);  //ad表示附加的满意度
		}
		if(cnt==m)  //如果当前状态就是吃了m道菜则ans取最大值
		for(int i=0;i<n;++i) if(now & (1<<i)) //枚举吃的最后一道菜（没办法这里还是要枚举的）
			ans=max(ans , f[now][i]);
	}
	printf("%I64d\n",ans);  //直接输出一个longlong的ans
	
	return 0;
}
```

---

## 作者：红色OI再临 (赞：5)

看到$n<=18$这种字眼，我们就应该想到状态压缩dp

发现题目当前选的菜的贡献只跟**当前状态**和**上一次吃的菜**有关

所以考虑把它们设计成状态，设$f[i][j]$表示当前状态为`i`，上一次吃的菜为`j`时的最大满意值，然后考虑转移：

$f[x|(1<<j)][j]=max(f[x][i]+dis[i][j]+a[j])$

dis即题目中的$c$

具体实现中，我们只要枚举`x`,`i`,`j`即可，还要注意`f`数组的初始值

吐槽一下：我受了宝藏的坑害想防止重边，结果手残写成了双向边。。。然后我一晚上的大好光阴没了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define re register long long
#define ll long long
#define maxn 20
using namespace std;
ll f[1<<maxn][20];
int n,m,k;ll ans;
int dis[maxn][maxn];
int a[maxn];int s[1<<maxn];
int  main(){
	scanf("%d%d%d",&n,&m,&k);
	for(re i=0;i<n;i++){
		scanf("%d",&a[i]);
		f[1<<i][i]=a[i];
	}
	for(re i=1;i<=k;i++){
		int a1,a2,a3;
		scanf("%d%d%d",&a1,&a2,&a3);
		a1--;a2--;
		dis[a1][a2]=max(dis[a1][a2],a3);//时刻注意卡重边
	}
	for(re x=0;x<(1<<n);x++)
		for(re i=0;i<n;i++){
			if(x&(1<<i)){	
			s[x]++;
			}
		}
	for(re x=0;x<1<<n;x++){ 
		for(re i=0;i<n;i++){
			if((x&(1<<i)))
			{for(re j=0;j<n;j++){
					if((i==j)||(x&(1<<j)))continue;
					int xx=x|(1<<j);
					f[xx][j]=max(f[xx][j],f[x][i]+dis[i][j]+a[j]);
				}
			}
		}
	}
	
for(re i=0;i<(1<<n);i++){
	if(s[i]!=m)continue;
	for(re j=0;j<n;j++){
		ans=max(ans,f[i][j]);
	}
}
printf("%lld\n",ans);

return 0;	
}
```


---

## 作者：xixike (赞：3)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15733256.html)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/CF580D)

## Solution

好水的状压 $dp$……

非常套路的状态，设 $dp_{i, s}$ 表示吃了状态为 $s$ 的菜，且最后一个吃的是 $i$ 的最大满意度。

那么如何转移呢？

枚举状态 $s$，枚举最后一个吃的 $i$，再枚举倒数第二个吃的菜 $j\ (i, j \in s)$。

转移方程：
$$
dp_{i, s} = \max\{dp_{j, s \oplus (1 << (i - 1))} + a_i + g_{j, i} \}
$$

> $\oplus$：表示异或。
>
> $a_i$：表示单独吃 $i$ 的满意度。
>
> $g_{i, j}$：表示先吃 $i$ 然后紧跟着吃 $j$ 的额外满意度。

这个转移方程的意思是：从吃了状态为 $s \oplus (1 << (i - 1))$ 的菜（就是不吃 $i$），且最后一个吃的是 $j$ 转移到 $dp_{i, s}$，要加上 $i$ 的满意度，再加上吃了 $j$ 之后紧跟着吃 $i$ 的额外满意度。

~~还是非常显然的吧。~~

**注意：额外满意度没有双向性。**

统计答案的时候枚举一下状态 $s$，再枚举最后吃的 $i$，如果 $s$ 中有  $m$ 个 1，就取 $\max$。

## Code

（据说开两维数组时，小的一维放前，大的放后更快一些。）

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

int n, m, k;
int a[20], g[20][20];
ll dp[20][(1 << 18) + 5];

signed main(){
    n = read(), m = read(), k = read();
    for(int i = 1; i <= n; ++i) a[i] = read(), dp[i][1 << (i - 1)] = a[i];
    for(int i = 1; i <= k; ++i){
        int u = read(), v = read(), w = read();
        g[u][v] = w;
    }
    for(int s = 0; s < (1 << n); ++s)
        for(int i = 1; i <= n; ++i)
            if(s & (1 << (i - 1)))
                for(int j = 1; j <= n; ++j)
                    if(i != j && (s & (1 << (j - 1))))
                        dp[i][s] = max(dp[i][s], dp[j][s ^ (1 << (i - 1))] + a[i] + g[j][i]);
    ll ans = 0;
    for(int s = 0; s < (1 << n); ++s)
        if(__builtin_popcount(s) == m)
            for(int i = 1; i <= n; ++i)
                if(s & (1 << (i - 1)))
                    ans = max(ans, dp[i][s]);
    write(ans), puts("");
    return 0;
}
```

$$
\_EOF\_
$$


---

## 作者：attack (赞：3)

官方题解是$O(2^n n^2)$的，不过我没发现状态之间的联系，就写了一个$O(2^n n^3)$的，不过还是水过去了。

$f[i][j][sta]$表示现在已经放了$i$个，本轮要放第$j$个，状态为$sta$

转移的时候枚举一下上一个放了什么

考虑到状态之间有许多可行性剪纸，因此实际上效果是非常nice的。

多枚举一层$M$，也仅仅慢一倍左右

```cpp
/*

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<set>
#include<queue>
#include<cmath>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
#define int long long 
#define LL long long 
#define rg register 
#define sc(x) scanf("%d", &x);
#define pt(x) printf("%d ", x);
#define db(x) double x 
#define rep(x) for(int i = 1; i <= x; i++)
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<22, stdin), p1 == p2) ? EOF : *p1++)
//char buf[(1 << 22)], *p1 = buf, *p2 = buf;
char obuf[1<<24], *O = obuf;
#define OS  *O++ = ' ';
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 1e6 + 10, INF = 1e9 + 10, mod = 1e9 + 7;
const double eps = 1e-9;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
void print(int x) {
    if(x > 9) print(x / 10);
    *O++ = x % 10 + '0';
}
int N, M, K;
int f[2][19][262145];
int lk[19][19], a[MAXN];
main() {
	N = read(); M = read(); K = read();
	for(int i = 1; i <= N; i++) a[i] = read();
	for(int i = 1; i <= K; i++) {
		int x = read(), y = read(), z = read();
		lk[x][y] = z;
	}
	int lim = (1 << N) - 1, o = 0;
	for(int i = 1; i <= M; i++) {
		o ^= 1;
		for(int sta = 0; sta <= lim; sta++) {
			if((__builtin_popcount(sta)) != i) continue;
			for(int j = 1; j <= N; j++) {
				if(!(sta & (1 << j - 1))) continue;
				for(int k = 1; k <= N; k++) {
					if(sta & (1 << k - 1)) {
						f[o][j][sta] = max(f[o][j][sta], f[o ^ 1][k][sta ^ (1 << j - 1)] + lk[k][j]);
					}
				}				
			}
		}			
	}
	int ans = 0;
	for(int i = 1; i <= N; i++) {
		for(int sta = 0; sta <= lim; sta++) {
			if((__builtin_popcount(sta)) != M) continue;
			if(!(sta & (1 << i - 1))) continue;
			int now = f[o][i][sta];
			for(int j = 1; j <= N; j++) 
				if(sta & (1 << j - 1)) now += a[j];
			ans = max(ans, now);
		}
	}
	cout << ans;
	return 0;
}
/*
2 2 1
1 1
2 1 1
*/
```

---

## 作者：Mobius127 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF580D)

为什么这么降智的题会有紫。。。

看到 $n$ 这么小，果断状压 DP。

又想到当前状态只与上一个吃的什么有关，多开一维即可。

记 $dp_{S, i}$ 为已经吃过的食物的集合 $S$，最后一次吃的是 $i$，那么有：

$$dp_{S, i}=\max_{T \in S} \max_{(T>>j)\ is\ 1} dp_{T, j} + val_i +edge_{j,i}$$

拿着这个大力跑循环即可，时间复杂度 $O(2^n n^2) \approx  10^9$。~~少爷机跑得还挺快。~~

还有就是注意预处理以及爆 int 的问题。 

### Code:

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int n, m, k, R, ans;
int a[20], edge[20][20], dp[1<<18][20];
signed main(){
	n=read(), m=read(), k=read();R=1<<n;
	for(int i=1; i<=n; i++)
		a[i]=read(), dp[1<<(n-i)][n-i]=a[i];
	for(int i=1; i<=k; i++){
		int x=read(), y=read(), c=read();
		edge[x][y]=max(edge[x][y], c);
	}
	for(int S=1; S<R; S++)
		for(int i=0; i<n; i++)
			if((S>>i)&1)
				for(int T=S^(1<<i), j=0; j<n; j++)
					if((T>>j)&1)
						dp[S][i]=max(dp[S][i], dp[T][j]+a[n-i]+edge[n-j][n-i]);
	for(int S=1; S<R; S++){
		int cnt=0;
		for(int T=S; T; T-=lowbit(T))
			cnt++;
		if(cnt!=m) continue;
		for(int i=0; i<n; i++)
			if((S>>i)&1)
				ans=max(ans, dp[S][i]);
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：When (赞：2)

#### 算法

状压DP

#### 思路

$n \leq 18$，一看就很状压。

设$f_{st,i}$为当前状态为$st$（二进制下第$x$位为$1$时表示选了第$x$个），最后一个选了$i$时的最大满意度（记录$i$是为了计算吃菜顺序的额外贡献），则有：

$$ f_{st,i} = max(f_{pre,j} + a_i + c_{j,i})$$

其中，$j$必须在状态$st$时被选中，$pre$为$st$不选$i$时的状态。

至于统计答案，把$st$中$1$的个数为$m$时的$f$取$min$就可以了。

#### 代码
```cpp
#include <cstdio>
#include <algorithm>
#define LL long long

using namespace std;

const int maxn = 3e5 + 10;
int n,k,m;
LL a[20],c[20][20],f[maxn][20];

int cnt(int x){
    int num = 0;
    while(x) num += (x & 1), x >>= 1; 
    return num;
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < n; ++ i) scanf("%lld", &a[i]);
    for(int i = 1; i <= k; ++ i){
        int x,y; scanf("%d%d", &x, &y);
        scanf("%lld", &c[x - 1][y - 1]);
    } LL Ans = 0;
    for(int st = 0; st < (1 << n); ++ st){
        for(int i = 0; i < n; ++ i){
            bool flag = 0;
            if(st & (1 << i)){
                for(int j = 0; j < n; ++ j){
                    if(j == i || !(st & (1 << j))) continue;
                    flag = 1;
                    f[st][i] = max(f[st][i], f[st ^ (1 << i)][j] + a[i] + c[j][i]);
                }
                if(!flag) f[st][i] = a[i];
            }
            if(cnt(st) == m) Ans = max(Ans, f[st][i]);
        }
    }
    printf("%lld\n", Ans);
    return 0;
}
```

---

## 作者：设计涉及社稷 (赞：2)

**前言：我们在做题的时候就是把一道新的问题归约成已知的模型（其实OI考察的就是泛化模型的能力），“学”的时候你就好好学，只管见模型，就算是看了代码也不可耻，重点是，“学”完之后“习”的方式，或许“习”指的并不是温习，而是应用模型的能力。**

我写这么一大段话的原因是什么呢？

此题不就是[最短哈密顿路径](https://www.acwing.com/problem/content/93/)的变式嘛？怎么就紫了？？？

[【此题是最长哈密顿问题】AT2673 Tree and Hamilton Path](https://www.luogu.org/problem/AT2673)

---
接下来讲一下如何把此题归约成最短哈密顿路径的模型

---
先瞄一眼数据范围
$1\le m\le n\le 18$

为什么这么小呢？考虑暴力做法，极端情况m==18，全排列枚举路径,再遍历这条路径计算长度，时间复杂度：

$O(18! \times 18)$

有什么方法能把指数型的时间复杂度优化到多项式呢？

您的模型告诉你：状压DP

---
每道菜只有吃和不吃两种状态,我们找到了一个**对立态**，可以用01表示，哟，状压妥儿了。

在吃完一道菜x之后紧接着吃另一道菜y会有加成$w_{x,y}$，我们可以把这个条件看做x到y的一条边权为 $w_{x,y}$的有向边。因为n很小，我们可以直接使用邻接矩阵存储

**状态定义**：

我们把菜吃了记为1 ，没吃记为0，那么我们可以用一个01串i来描述这些菜的情况，也就是一个**局面**

`f[i][j]`表示吃了第j道菜后形成i局面下的最大满意度，和最短哈密顿路径一模一样，这题只是加了一个初始权值而已

**转移方程**：

$f[i][j]=max(f[i][j],f[i\ xor\ (1<<j-1)][k]+a[j]+w[k][j])$

其中j表示当前的菜，k枚举的是上一道菜

**初始化**：

`f[1<<(i-1)][i]=a[i];`

**终态**：
很显然，如果没有只选m个菜的限制的话，这就是个最短哈密顿路径的裸模板，那我们遍历一下所有状态，只选1的个数是m的状态来记录答案，由于所有点都可以作为结束节点，遍历一下就好了。

```
#define int long long//可耻的定义全局long long，并省掉了头文件和宏定义

const int N=18,M=1<<N;
int a[N+5],w[N+5][N+5];
int n,m,k;
int f[M+5][N+5];

inline int get_num(int x){
	int res=0;
	while(x){
		x&=(x-1);
		res++;
	}
	return res;
}

#undef int
int main(){
#define int long long
	rd(n),rd(m),rd(k);
	rep(i,1,n){
		rd(a[i]);
		f[1<<(i-1)][i]=a[i];
	} 
	rep(i,1,k){
		int u,v,z;rd(u),rd(v),rd(z);
		w[u][v]=z;
	}
	for(int i=0;i<1<<n;++i)	
		rep(j,1,n)
			if(i>>(j-1)&1)
				rep(k,1,n)
					if((i^(1<<(j-1)))>>(k-1)&1)
						f[i][j]=max(f[i][j],f[i^(1<<(j-1))][k]+a[j]+w[k][j]);
	int ans=0;
	for(int i=0;i<1<<n;++i){
		if(get_num(i)==m)//判断是否选了m个
			rep(j,1,n)
				ans=max(ans,f[i][j]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

**后记：我为什么写这篇题解呢，不是因为我闲的痛，而是……马上要考状压了……我还没学会k进制状压，打算巩固一下二进制状压模型……而不是去“学”一下k进制状压模型，hh点题了。**

---

## 作者：aRenBigFather (赞：2)

### 用dp[sta][j]表示sta状态下,最后吃的是第j个菜，能获得的最大满意度

### 然后可以得到以下转移式

$$dp[i | 2^k][k+1] = max(dp[i | 2^k][k+1],dp[i][j+1]+ww[k+1]+G[k+1][j+1]);$$

#### 其中,j为当前枚举状态i下能吃的菜,k为1~n中任意一道菜,ww[]数组为每道菜单独吃的收益,G[i][j]表示吃完j再吃i的额外收益
-------------------------
## AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 20;
ll n,m,k;
ll ww[maxn];
ll G[maxn][maxn];
ll ans = 0;
ll dp[1 << maxn][maxn]; //dp[sta][j],sta状态下,最后吃的是第j个菜，能获得的最大满意度
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for(ll i=1;i<=n;i++) cin >> ww[i];
    memset(G,0,sizeof G);
    for(ll i=1;i<=k;i++){
        ll x,y,val;
        cin >> x >> y >> val;
        G[y][x] = val;
    }
    memset(dp,0,sizeof dp);
    for(int i=1;i<=n;i++){
        dp[1<<(i-1)][i] = ww[i];
    }
    for(int i=1;i<(1<<n);i++){
        //枚举状态
        ll cnt = 0;
        for(int j=0;j<30;j++){
            if(i & (1ll << j)) cnt++;
        }
        for(int j=0;j<n;j++){
            if(i & (1ll << j)){
                for(int k=0;k<n;k++){
                    if((i & (1ll << k)) == 0){
                        dp[i | (1ll << k)][k+1] = max(dp[i | (1ll << k)][k+1],dp[i][j+1]+ww[k+1]+G[k+1][j+1]);
                    }
                }
            }
        }
        for(int j=0;j<n;j++){
            if(i & (1ll << j)){
                if(cnt == m) ans = max(ans,dp[i][j+1]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：loverintime (赞：0)

本题数据 $N\leqslant 18$, 容易想到状压 $dp$
令 $f(S,i)$ 表示现在已经吃了集合 $S$ 中的所有菜， 并且上一次吃的菜是 $i$

转移： 枚举倒数第二次吃的菜 $j$， 就可以列出转移方程：

$f(S,i)=\max_{j\in S\wedge j\neq i} \{f(S-\{i\},j)+a_i+c_{j,i} \}$

其中， $a_i$ 表示第 $i$ 道菜的满意程度， $c_{i,j}$ 表示吃完 $i$ 后立即吃 $j$ 可以额外获得的满意值。

时间复杂度： $\Theta(2^nn^2)$, 可以通过此题

最后一点就是要注意开 $long\ long$

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[(1<<18)+1][19];
int n,m,k;
long long Map[19][19],a[19];
int sum[(1<<18)+1];
long long ans;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int s=1; s<(1<<n); s++){
		sum[s]=sum[s&(~((-s)&s))]+1;
	}
	for(int i=0; i<n; i++) scanf("%lld",&a[i]),ans=max(ans,a[i]);
	for(int i=1; i<=k; i++){
		int u,v;long long c;scanf("%d%d%lld",&u,&v,&c);u--,v--;
		Map[u][v]=c;
	}
	for(int i=0; i<n; i++) f[1<<i][i]=a[i];
	for(int s=1; s<(1<<n); s++){
		if(sum[s]>m||sum[s]==1) continue;
		for(int i=0; i<n; i++){
			if(s&(1<<i)){
				for(int j=0; j<n; j++){
					if(i!=j&&(s&(1<<j))){
						f[s][i]=max(f[s][i],f[s&(~(1<<i))][j]+a[i]+Map[j][i]);
					}
				}
			}
		}
		if(sum[s]==m){
			for(int i=0; i<n; i++)
			ans=max(ans,f[s][i]);
		} 
	}
	printf("%lld\n",ans);
	return 0;
}


---

