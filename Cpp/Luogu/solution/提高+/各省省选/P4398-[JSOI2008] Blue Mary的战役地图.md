# [JSOI2008] Blue Mary的战役地图

## 题目描述

Blue Mary 最近迷上了玩 Starcraft（星际争霸）的 RPG 游戏。她正在设法寻找更多的战役地图以进一步提高自己的水平。
 
由于 Blue Mary 的技术已经达到了一定的高度,因此，对于用同一种打法能够通过的战役地图，她只需要玩一张，她就能了解这一类战役的打法，然后她就没有兴趣再玩儿这一类地图了。而网上流传的地图有很多都是属于同一种打法，因此 Blue Mary 需要你写一个程序，来帮助她判断哪些地图是属于同一类的。 

具体来说，Blue Mary 已经将战役地图编码为 $n \times n$ 的矩阵，矩阵的每个格子里面是一个 $32$ 位（有符号）正整数。对于两个矩阵，他们的相似程度定义为他们的最大公共正方形矩阵的边长。两个矩阵的相似程度越大，这两张战役地图就越有可能是属于同一类的。

## 说明/提示

#### 样例解释： 

子矩阵：$
\begin{bmatrix}
  5 & 6 \\
  8 & 9 \\
\end{bmatrix}
$ 为两个地图的最大公共矩阵。

约定：$n \le 50$。

## 样例 #1

### 输入

```
3
1 2 3
4 5 6
7 8 9
5 6 7
8 9 1
2 3 4```

### 输出

```
2```

# 题解

## 作者：枫林晚 (赞：22)

# 全网唯一一篇dp题解

推广自家[blog](https://www.cnblogs.com/Miracevin/p/9735181.html)

网上貌似全部都是哈希+二分（反正我是大概baidu了翻了翻）（还有人暴力AC了的。。）

哈希还是相对于dp还是比较麻烦的。

而且正确性还有可能被卡（当然这个题不会）

而且还容易写错。

我就懒得写哈希了。

这个题，貌似和一个题目很像啊~~~

[P1387 最大正方形](https://www.luogu.org/problemnew/show/P1387)

P1387这个题相信大家都会吧。。

~~不会的话看那就随便找篇题解。。~~

这个题就是最大正方形的加强版。

设$f[x1][y1][x2][y2]$表示，在第一个正方形中，以$(x1,y1)$为右下角，第二个正方形中以$(x2,y2)$为右下角，公共正方形最大的边长。

然后一个四重循环。

因为都是正序的，所以没有后效性。

然后转移很自然了。

和P1387一样。

$f[x1][y1][x2][y2]=min(f[x1-1][y1-1][x2-1][y2-1],min(f[x1][y1-1][x2][y2-1],f[x1-1][y1][x2-1][y2]))+1;$

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=52;
int f[N][N][N][N];
int a[N][N],b[N][N];
int n;
int ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&b[i][j]);
	for(int x1=1;x1<=n;x1++){
		for(int y1=1;y1<=n;y1++){
			for(int x2=1;x2<=n;x2++){
				for(int y2=1;y2<=n;y2++){
					if(a[x1][y1]==b[x2][y2]){
						f[x1][y1][x2][y2]=min(f[x1-1][y1-1][x2-1][y2-1],min(f[x1][y1-1][x2][y2-1],f[x1-1][y1][x2-1][y2]))+1;
					}
					ans=max(ans,f[x1][y1][x2][y2]);
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}

```

虽然复杂度是$O(n^4)$不如哈希优秀。

但是好写啊！！

~~真是简单又自然~~

---

## 作者：RedreamMer (赞：18)

### [P4398](https://www.luogu.com.cn/problem/P4398)

这道题做法很多，且数据范围极小`(n<=50)`，所以大多数题解的时间复杂度都非常的高。

提供一种 $O(N^3)$ （可能有上下的浮动）的做法。

### Solution

1. 首先，我们使用二维数组维护`hash`数组`s[i][j]`表示从`(1,1)`长为`i`宽为`j`的矩形。

2. 然后枚举第一个矩阵的`(i,j)`坐标，在枚举以`(i,j)`正方形**右下角**的边长k，将这个正方形的边长存入一个以`hash`值（需要模）为`head`的领接表（方便查找且方便保存）。

3. 接着，跟第二步一样枚举`(i,j,k)`，得到这个正方形的`hash`值并查找是否有`hash`值与它相等切边长为k的正方形，更新`ans`。

4. 输出

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long//以下hash操作自然溢出，用无符号类型就是因为方便（懒） 
const int pow1=6767667;//行的乘数，防止撞上相同的 
const int pow2=8989889;//列的乘数，防止撞上相同的 
const int mod=9990813;//模数自定 
int a,x,y,top,ans;
ull s1[51][51],s2[51][51],head[9990813],power1[51],power2[51];
struct P {
	int last,sum;
	ull dis;
} s[9990813];
inline void push(ull n,int m) {//存储以hash值n为head，边长为m的正方形
	int nk=n%mod;
	s[++top].last=head[nk];
	s[top].dis=n;
	s[top].sum=m;
	head[nk]=top;
}
inline bool query(ull n,int m) {//查找以hash值n为head，边长为m的正方形 
	int nk=n%mod;
	for(int i=head[nk]; i; i=s[i].last)
		if(s[i].dis==n&&s[i].sum==m)
			return 1;
	return 0;
}
inline ull get(int x,int y,int xx,int yy,int k,bool p) {//求hash值得部分，有点长，不懂得可以私信我 
	return !p?s1[x][y]-s1[x][yy-1]*power1[k]-s1[xx-1][y]*power2[k]+s1[xx-1][yy-1]*power1[k]*power2[k]:s2[x][y]-s2[x][yy-1]*power1[k]-s2[xx-1][y]*power2[k]+s2[xx-1][yy-1]*power1[k]*power2[k];
}
int main() {
	power1[0]=power2[0]=1;
	for(int i=1; i<=50; i++)
		power1[i]=power1[i-1]*pow1;
	for(int i=1; i<=50; i++)
		power2[i]=power2[i-1]*pow2;
	cin>>a;
	for(int i=1; i<=a; i++)
		for(int j=1; j<=a; j++)
			cin>>s1[i][j];
	for(int i=1; i<=a; i++)
		for(int j=1; j<=a; j++)
			cin>>s2[i][j];
	for(int i=1; i<=a; i++)
		for(int j=1; j<=a; j++)
			s1[i][j]=s1[i][j-1]*pow1+s1[i][j];
	for(int i=1; i<=a; i++)
		for(int j=1; j<=a; j++)
			s2[i][j]=s2[i][j-1]*pow1+s2[i][j];
	for(int j=1; j<=a; j++)
		for(int i=1; i<=a; i++)
			s1[i][j]=s1[i-1][j]*pow2+s1[i][j];
	for(int j=1; j<=a; j++)
		for(int i=1; i<=a; i++)
			s2[i][j]=s2[i-1][j]*pow2+s2[i][j];
//	for(int i=1; i<=a; i++) {
//		for(int j=1; j<=a; j++)
//			cout<<s1[i][j]<<' ';
//		cout<<endl;
//	}
//	for(int i=1; i<=a; i++) {
//		for(int j=1; j<=a; j++)
//			cout<<s2[i][j]<<' ';
//		cout<<endl;
//	}
//	for(int i=1; i<=3; i++)
//		cout<<power1[i]<<' ';
//	cout<<get(2,2,1,1,2,0);
	for(int i=1; i<=a; i++)//枚举i 
		for(int j=1; j<=a; j++)//枚举j 
			for(int k=1; k<=i&&k<=j; k++){//枚举k 
//				cout<<i<<' '<<j<<' '<<k<<endl;
				push(get(i,j,i-k+1,j-k+1,k,0),k);
			}
	for(int i=1; i<=a; i++)//枚举i 
		for(int j=1; j<=a; j++)//枚举j 
			for(int k=1; k<=i&&k<=j; k++)//枚举k 
				if(query(get(i,j,i-k+1,j-k+1,k,1),k))
					ans=max(ans,k);
	cout<<ans;
	return 0;
}
```

#### [$\color{blue}\text{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：LightningUZ (赞：13)

## 前言
这是我老师E.Space神仙（某清华姚班神仙）上课讲到的例题，由于他非常的神，反手给数据加了个0

然后我就想出了 $O(n^2\log^2n)$ 的做法。如果把 `std::map` 换成 `unordered_map`，那还能少掉一个 $\log$。

一翻题解，似乎 **理论复杂度** 最低的是 $O(n^3)$ 做法，于是我决定讲一下平方俩 $\log$ 做法。 

## 主思路

目 力 可以看出这题的单调性，于是可以考虑二分答案。假设现在要检测一个 $k$。对于每个 $1\le i\le n-k+1,1\le j\le n-k+1$，求出 $h[i][j]$ 表示 $(i,j)$ 位置为左上角，边长为 $k$ 的正方形的哈希值。对于正方形 $A$，我们把它所有的 $h$ 值放在 $map$ 里。对于正方形 $B$ 也来求一遍，如果在 $map$ 中找到对应的，就检测成功，否则失败。

## 复杂度

对于每个 $k$，$O(n^2)$ 预处理，$O(n^2\log n)$ 查表，要二分 $\log n$ 次，于是复杂度是 $O(n^2\log^2 n)$。

## 细节

如何求某位置为左上角的边长为 $k$ 的正方形的哈希值？

对于每个位置，我们先求出它往后 $k$ 个位置的哈希值，存在 $h'$ 数组里。然后对于每个位置，把它下面 $k$ 个位置的 $h'$ 数组的值再做一次哈希。

然而，这两次哈希如果取相同的底数 $base$，那会 WA 掉两个点。去看了一下黑♂暗爆炸OJ的数据，发现了这毒瘤数据：
```plain
5
1 1 0 0 0
1 1 0 0 3
0 2 2 2 0
0 2 2 2 8
4 1 7 2 6
1 1 1 0 0
1 0 2 2 3
0 0 2 2 0
0 0 2 2 8
4 1 7 2 6
```
这组数据应该输出 $3$，然而我的算法却误判成了 $5$。换了几次 $base$ 和 $mod$ 都不行。

于是我就想了一个办法，反正我们哈希要做两次，第二次哈希的 $base$ 和第一次取不一样的就彳亍了。

事实证明这的确可以，我$mod=10^9+7$，$base_1=114514$，$base_2=1919810$，用人类智慧和先辈的力量苟过去了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Flandre_Scarlet
{
    #define int long long
    #define N    501ll
    #define base  114514ll
    #define base2 1919810ll
    #define mod   1000000007ll
    #define F(i,l,r) for(int i=l;i<=r;++i)
    #define D(i,r,l) for(int i=r;i>=l;--i)
    #define Fs(i,l,r,c) for(int i=l;i<=r;c)
    #define Ds(i,r,l,c) for(int i=r;i>=l;c)
    #define MEM(x,a) memset(x,a,sizeof(x))
    #define FK(x) MEM(x,0)
    #define Tra(i,u) for(int i=G.Start(u),v=G.To(i);~i;i=G.Next(i),v=G.To(i))
    #define p_b push_back
    #define sz(a) ((int)a.size())
    #define all(a) a.begin(),a.end()
    #define iter(a,p) (a.begin()+p)
    int I() {char c=getchar(); int x=0; int f=1; while(c<'0' or c>'9') f=(c=='-')?-1:1,c=getchar(); while(c>='0' and c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar(); return (x=(f==1)?x:-x);}
    void Rd(int cnt,...) {va_list args;va_start(args,cnt); F(i,1,cnt) {int* x=va_arg(args,int*);(*x)=I();} va_end(args);}
    void RA(int *a,int n) {int *p=(a+1); F(i,1,n) {(*p)=I();++p;}}
    int n,a[N][N],b[N][N];
    void Input()
    {
        n=I();
        F(i,1,n) F(j,1,n) a[i][j]=I();
        F(i,1,n) F(j,1,n) b[i][j]=I();
    }
    int pw[N*N],pw2[N*N],s[N][N];
    int ha[N][N],hb[N][N];
    map<int,bool> vis; // 开成 unordered_map 更快
    bool cxk(int k)
    {
        if (k==0) return true;
        F(i,1,n) F(j,1,n) s[i][j]=(s[i][j-1]*base+a[i][j])%mod;
        F(i,1,n) F(j,1,n-k+1) ha[i][j]=(s[i][j+k-1]+mod-s[i][j-1]*pw[k]%mod)%mod;
        // 这就相当于 h'
        // 实现的时候一个数组原地修改就可以了...h'只是一个理论的讲法
        F(j,1,n-k+1) F(i,1,n) s[i][j]=(s[i-1][j]*base2+ha[i][j])%mod;
        F(j,1,n-k+1) F(i,1,n-k+1) ha[i][j]=(s[i+k-1][j]+mod-s[i-1][j]*pw2[k]%mod)%mod;
        
        F(i,1,n) F(j,1,n) s[i][j]=(s[i][j-1]*base+b[i][j])%mod;
        F(i,1,n) F(j,1,n-k+1) hb[i][j]=(s[i][j+k-1]+mod-s[i][j-1]*pw[k]%mod)%mod;
        F(j,1,n-k+1) F(i,1,n) s[i][j]=(s[i-1][j]*base2+hb[i][j])%mod;
        F(j,1,n-k+1) F(i,1,n-k+1) hb[i][j]=(s[i+k-1][j]+mod-s[i-1][j]*pw2[k]%mod)%mod;
        // 我真该写个函数把这两个一模一样的玩意封装起来..可是我忘了

        vis.clear();
        F(i,1,n-k+1) F(j,1,n-k+1) vis[ha[i][j]]=1;
        F(i,1,n-k+1) F(j,1,n-k+1) if (vis[hb[i][j]]) return true;
        return false;
    }
    void Soviet()
    {
        pw[0]=1; F(i,1,n*n) pw[i]=pw[i-1]*base%mod;
        pw2[0]=1; F(i,1,n*n) pw2[i]=pw2[i-1]*base2%mod;
        // 两个base都处理一下幂
        int l=0,r=n;
        while(l<r)
        {
            int mid=(l+r+1)>>1;
            if (cxk(mid)) l=mid;
            else r=mid-1;
        }
        printf("%lld\n",l);
    }
    void IsMyWife()
    {
        Input();
        Soviet();
    }
}
#undef int //long long
int main()
{
    Flandre_Scarlet::IsMyWife();
    getchar();
    return 0;
}
```

---

## 作者：封禁用户 (赞：11)

## 题意：

输入两个大小相同的正方形矩阵，求这两个矩阵最大的相等正方形子矩阵。

## Solution 1

先考虑暴力的做法。

从大到小地枚举矩阵大小，然后分别枚举两个正方形的右上角，再进行判断。

时间复杂度：$O(n^7)$。

### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 55
int n,a[N][N],b[N][N];
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			scanf("%d",&a[i][j]);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			scanf("%d",&b[i][j]);
	for(int len = n;len >= 1;--len)
		for(int i = 1;i <= n-len+1;++i)
			for(int j = 1;j <= n-len+1;++j)
				for(int x = 1;x <= n-len+1;++x)
					for(int y = 1;y <= n-len+1;++y)
					{
						bool flag = 1;
						for(int p = 0;p < len&&flag;++p)
							for(int q = 0;q < len&&flag;++q)
								if(a[i+p][j+q] != b[x+p][y+q])
									flag = 0;
						if(flag)
						{
							printf("%d",len);
							return 0;
						}
					}
	return 0;
}
```
但时间卡得有点紧……qaq [提交记录](https://www.luogu.com.cn/record/89296433)。

最后一个点要 $982ms$ 才能跑完，还要吸氧,所以我们想要更优的做法。


## Solution 2

可以参照题目[最大正方形](https://www.luogu.com.cn/problem/P1387)的做法。

令 $f_{i,j,l,r}$ 表示 以 $a_{i,j}$ 为右下角的正方形与 $b_{l,r}$ 为右下角的正方形最大重合正方形边长为 $f_{i,j,l,r}$。

则可以得到 $f_{i,j,l,r}=\min(f_{i-1,j,l-1,r},f_{i,j-1,l,r-1},f_{i-1,j-1,l-1,r-1})+1$

时间复杂度 $O(n^4)$，因为 $n≤50$ 足以通过本题。

### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 55
int n,a[N][N],b[N][N],f[N][N][N][N],ans = 0;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)	
			scanf("%d",&a[i][j]);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)	
			scanf("%d",&b[i][j]);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			for(int l = 1;l <= n;++l)
				for(int r = 1;r <= n;++r)
					if(a[i][j] == b[l][r])
					{
						f[i][j][l][r] = min(min(f[i-1][j][l-1][r],f[i][j-1][l][r-1]),f[i-1][j-1][l-1][r-1]) + 1;
						ans = max(ans,f[i][j][l][r]);
					}
	printf("%d",ans);
	return 0;
}
```

## Solution 3

为了追求效率，可以使用[哈希](https://oi-wiki.org/string/hash/)。

先对于一个矩阵的每一行进行哈希，即通过一个算法把字符串（也可以是一些数字）压缩成一个数字，进行 $O(1)$ 的比较是否相同。

虽然有被卡的可能，但只要取合适的模数和系数，这个概率微乎其微。

通过计算，在取 $998244353$ 为模数时，$2500$ 个元素通过的概率约为 $99.69\%$，所以除非特别构造数据，否则几乎不可能被卡。

### 算法流程

先对一个矩阵每一行进行哈希，任意枚举两列，截取每一行中两列之间的哈希值，在对这些哈希值进行哈希，枚举与两列距离的相等的两行，构成一个矩形，然后就能对这个矩形取哈希。

需要指出的是，矩形在哈希过程中结构体还要再存一位 $x$（矩形边长），不然被卡的概率会大大增加。结构体中还要加一个对小于号的重定义，不然会编译错误。

**还有 $pw[]$ 一定要开到并预处理到 $n^2$，因为在矩形的哈希过程中会用到。**

本人选取模数为 $998244353$，系数为 $114514$。

时间复杂度为 $O(n^3 \log n)$。

### AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define P 114514
#define mod 998244353
#define ll long long
#define N 55
struct node
{
	int x;
	ll hh;
	bool friend operator<(node X,node Y) {return X.x > Y.x||(X.x == Y.x&&X.hh > Y.hh);}
};
map<node,int> mp;
int n,ans = 0;
ll pw[N*N],s[N],hs[N][N],a[N][N],b[N][N]; 
int main()
{
	scanf("%d",&n);
	pw[0] = 1;
	for(int i = 1;i <= n*n;++i) pw[i] = pw[i-1] * P % mod;
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			scanf("%lld",&a[i][j]);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			scanf("%lld",&b[i][j]);	
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			hs[i][j] = (hs[i][j-1] * P + a[i][j]) % mod;
	for(int p1 = 1;p1 <= n;++p1)
		for(int p2 = p1;p2 <= n;++p2)
		{
			int len = p2-p1+1;
			for(int i = 1;i <= n;++i) s[i] = (hs[i][p2] - hs[i][p1-1] * pw[len] % mod + s[i-1] * pw[len] % mod + mod) % mod;
			for(int l = 1,r = len;r <= n;++l,++r)
			{
				node p;
				p.hh = (s[r] - s[l-1] * pw[len*len] % mod + mod) % mod;
				p.x = len;
				mp[p] = 1;
			}
		}
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			hs[i][j] = (hs[i][j-1] * P + b[i][j]) % mod;
	for(int p1 = 1;p1 <= n;++p1)
		for(int p2 = p1;p2 <= n;++p2)
		{
			int len = p2-p1+1;
			for(int i = 1;i <= n;++i) s[i] = (hs[i][p2] - hs[i][p1-1] * pw[len] % mod + s[i-1] * pw[len] % mod + mod) % mod;
			for(int l = 1,r = len;r <= n;++l,++r)
			{
				node p;
				p.hh = (s[r] - s[l-1] * pw[len*len] % mod + mod) % mod;
				p.x = len;
				if(mp[p]) ans = max(ans,len);
			}
		}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：vectorwyx (赞：7)

疑似是第一篇时间复杂度为**严格** $O(n^{3})$ 的哈希题解？

前置知识：二维前缀和，哈希


------------
首先看到 $n\le50$，因此我们可以大胆地将所有正方形矩阵的边长和顶点都枚举出来，这个过程的复杂度为 $O(n^{3})$。

之后问题就转化成了给定 $2m$ 个边长相同的正方形矩阵，判定后 $m$ 个方阵与前 $m$ 个方阵是否有相同方阵。考虑使用哈希来解决。

使用哈希的难点有两个：选定一种合适的由矩阵转向哈希值的方式，以及快速地求出任意方阵的哈希值。

先看第一个：选定一种转化方式。我们可以参考[P3370【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)里的做法，将**所给的整个矩阵**压缩成一串 base 进制的数，再以这个 base 进制的数转化为十进制后的值对 mod 取模的结果作为矩阵的哈希值，其中 base 和 mod 均是我们选定的正整数。那怎么压缩呢？我们先把一个矩阵的每一行顺次取下来，再依次接到上一行的末尾处，这样得到的一串数就是我们想要的结果，换句话说，如果一个元素原来位于 $(i,j)$ 处，那么它在新数中的位置就是第 $(i\times(n-1)+j-1)$ 位。

再看第二个：快速地求出任意方阵的哈希值。刚才提到了把整个矩阵压缩成数的做法，那么我们需不需要对于每个方阵都压缩一遍呢？答案是不需要。因为我们将整个矩阵压缩后，每个位置都相应地带上了一个权重 $v_{i,j}=base^{i\times(n-1)+j-1}$，那对于任意一个方阵，我们只需要把它所包含的每个元素乘上对应的权重的结果加起来就行，这个可以轻松地用二维前缀和来维护。但这样做每个方阵的哈希值是和它在原矩阵中的位置有关的，如何消去位置对它的哈希值的影响呢？我们只需要把所有方阵都平移到原矩阵的右下角，也就是  $(n,n)$ 的位置。

这样，我们开一个大小为 $mod$ 的桶记录已经出现过的哈希值，然后判重就相当容易了。注意，由于最多有 $2n$ 个哈希值需要判重，因此单模数哈希的 $mod$ 最小应为 $(2n)^{2}=2.5\times 10^{7}$，这题又只给128M的空间，所以单模数哈希会炸掉，应当采用双模数哈希。

------------

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#define mod 19260817
#define mod2 1000003
#define base 100003
#define ll long long
#define get(x,y) (x*n-n+y-1)
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){ int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') fh=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+ch-'0'; ch=getchar(); } return x*fh; }

int t[mod],t2[mod];
int a[51][51],b[51][51],n,sum1[51][51],_sum1[51][51],_sum2[51][51],sum2[51][51],jc[2501],jc2[2501];

int main(){
	n=read();
	int k=n*n;
	fo(i,1,n) fo(j,1,n) a[i][j]=read()%base;
	fo(i,1,n) fo(j,1,n) b[i][j]=read()%base;
	//预处理base^i对两个模数取模的结果 
	jc[0]=1;
	fo(i,1,k) jc[i]=1ll*jc[i-1]*base%mod;
	jc2[0]=1;
	fo(i,1,k) jc2[i]=1ll*jc2[i-1]*base%mod2;
	//预处理出每个以(1,1)为左上角的矩阵的哈希值 
	fo(i,1,n) 
		fo(j,1,n){
			sum1[i][j]=(sum1[i-1][j]+sum1[i][j-1]-sum1[i-1][j-1]+1ll*a[i][j]*jc[get(i,j)]+mod)%mod;
			_sum1[i][j]=(_sum1[i-1][j]+_sum1[i][j-1]-_sum1[i-1][j-1]+1ll*a[i][j]*jc2[get(i,j)]+mod2)%mod2;
		} 
	fo(i,1,n)
		fo(j,1,n){
			sum2[i][j]=(sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1]+1ll*b[i][j]*jc[get(i,j)]+mod)%mod;
			_sum2[i][j]=(_sum2[i-1][j]+_sum2[i][j-1]-_sum2[i-1][j-1]+1ll*b[i][j]*jc2[get(i,j)]+mod2)%mod2;
		} 
	int ti=0;//用时间戳代替memset，降低复杂度 
	go(i,n,1){//枚举正方形的边长 
		++ti;
		fo(j,1,n-i+1)//枚举左上角的下标 
			fo(w,1,n-i+1){
				int qwq=(sum1[j+i-1][w+i-1]-sum1[j-1][w+i-1]-sum1[j+i-1][w-1]+sum1[j-1][w-1]+2*mod)%mod;
				qwq=1ll*qwq*jc[k-1-get((j+i-1),(w+i-1))]%mod;
				t[qwq]=ti;
				qwq=(_sum1[j+i-1][w+i-1]-_sum1[j-1][w+i-1]-_sum1[j+i-1][w-1]+_sum1[j-1][w-1]+2*mod2)%mod2;
				qwq=1ll*qwq*jc2[k-1-get((j+i-1),(w+i-1))]%mod2;
				t2[qwq]=ti;
			}
		fo(j,1,n-i+1)
			fo(w,1,n-i+1){
				int qwq=(sum2[j+i-1][w+i-1]-sum2[j-1][w+i-1]-sum2[j+i-1][w-1]+sum2[j-1][w-1]+2*mod)%mod;
				qwq=1ll*qwq*jc[k-1-get((j+i-1),(w+i-1))]%mod;
				int qwq2=(_sum2[j+i-1][w+i-1]-_sum2[j-1][w+i-1]-_sum2[j+i-1][w-1]+_sum2[j-1][w-1]+2*mod2)%mod2;
				qwq2=1ll*qwq2*jc2[k-1-get((j+i-1),(w+i-1))]%mod2;			
				if(t[qwq]==ti&&t2[qwq2]==ti){
					cout<<i;
					return 0;
				}
			}
	}
	cout<<0;
	return 0;
}
/*
-------------------------------------------------
*/
```



---

## 作者：communist (赞：7)

### 暴力水过系列

数据范围这么小，就打暴力吧

枚举最大公共子矩阵的边长$O(n)$

枚举两个最大公共子矩阵的左上角$O(n^4)$

判断是否相同$O(n^2)$

总复杂度$O(n^7)$，显然过不了

过不了怎么办，删冗余枚举啊

### 一堆优化：

1，倒序枚举边长，一旦满足，即为答案

2，判断是否相同，一旦不同，跳出去

然后就过了

```
#include<iostream>
#include<cstdio>
using namespace std;
int a[2][60][60],n,ans;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<2;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				scanf("%d",&a[i][j][k]);
	for(int l=n;l>=1;l--)
		for(int x1=1;x1<=n-l+1;x1++)
			for(int y1=1;y1<=n-l+1;y1++)
				for(int x2=1;x2<=n-l+1;x2++)
					for(int y2=1;y2<=n-l+1;y2++)
					{
						bool p=0;
						for(int x=0;x<l;x++)
						{
							for(int y=0;y<l;y++)
							{
								if(a[0][x1+x][y1+y]!=a[1][x2+x][y2+y])
									p=1;
								if(p)
									break;
							}
							if(p)
								break;
						}
						if(!p)
						{
							printf("%d\n",l);
							return 0;
						}
					}
	return 0;
}
```

---

## 作者：hanyuchen2019 (赞：5)

二分答案万岁！

### part 1 思路

可以看到，本题 $n\le 50$，范围非常小，可以考虑一些高复杂度的做法。

于是我们可以暴力：

1. 枚举公共矩阵的边长（即答案），$O(n)$；
2. 枚举两个矩阵中该公共矩阵出现位置**左上角**的坐标，$O(n^4)$；
3. 枚举矩阵是否相同 $O(n^2)$

乘在一起达到了 $O(n^7)$，显然需要优化：

1. 找到不同直接退出；
2. 左上角坐标只需要枚举到 $n-ans+1$；
3. `ans` 倒着枚举，和上一个优化一起使用效果显著，同时方便写，找到一个解直接 `return 0`。
4. 二分答案，可优化成 $O(n^6 \log n)$。

于是就 AC 了，剩下的放代码里说吧（

### part 2 Code

暴力做法哪里都有，这里就放个二分的吧，此做法比暴力快了几倍。

```cpp
// O(n^6 log n)
#include<bits/stdc++.h>
using namespace std;
int a[55][55],b[55][55],n;
bool check(int ans)
{
	int N=n-ans+1;//超过N会框不到数
	for(int ax=1;ax<=N;++ax)
	for(int ay=1;ay<=N;++ay)
	for(int bx=1;bx<=N;++bx)
	for(int by=1;by<=N;++by)
	{
		bool diff=0;//有没有区别
		for(int x=0;x<ans&&(!diff);++x)
		{
			for(int y=0;y<ans;++y)
			{
				if(a[ax+x][ay+y]^b[bx+x][by+y])//异或，换成 != 也可以
				{
					diff=1;
					break;
				}	
			}
		}
		if(!diff)
			return 1;//找到直接退出，不用塞一堆判断一层一层 break
	}
	return 0
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin>>a[i][j];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin>>b[i][j];
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r+1)>>1;//+1防止死循环
		if(check(mid))l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
```

求赞qwq

---

## 作者：ethan0328 (赞：4)

## 思路

因为 $n\leq 50$，所以考虑枚举每一个子矩阵的大小和左上角坐标。

用 map 记下每一个子矩阵，然后判是否有相同的。

考虑如何记录。可以像字符串哈希一样把他表示为一个 $p$ 进制数。第 $(i,j)$ 坐标就是第 $n\times (i-1)+j$ 位。

但计算每个子矩阵的哈希值太慢，考虑用一个数组记录每一个 $(i,j)$ 的哈希值，值就是 $p^{i-j}$。然后用二维前缀和记录。

但这样会受位置影响，所以我们每个矩阵移到右下，也就是把值乘上一个 $p$ 的 $n^2-$ 矩阵右下角坐标 次方。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=55,N2=55*55,base=114514,mod=1e9+7;
int n,ans,a[N][N],b[N][N],pre1[N][N],pre2[N][N],pw[N2];
map<int,bool> mp;
signed main()
{
	int x;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>b[i][j];
		}
	}
	pw[0]=1;
	for(int i=1;i<=n*n;i++)
	{
		pw[i]=pw[i-1]*base%mod;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			pre1[i][j]=((((pw[n*(i-1)+j-1]*a[i][j]%mod+pre1[i-1][j])%mod+pre1[i][j-1])%mod-pre1[i-1][j-1])%mod+mod)%mod;
			pre2[i][j]=((((pw[n*(i-1)+j-1]*b[i][j]%mod+pre2[i-1][j])%mod+pre2[i][j-1])%mod-pre2[i-1][j-1])%mod+mod)%mod;
		}
	}
	for(int l=1;l<=n;l++)
	{
		for(int i=1;i+l-1<=n;i++)
		{
			for(int j=1;j+l-1<=n;j++)
			{
				x=((((pre1[i+l-1][j+l-1]-pre1[i+l-1][j-1])%mod+mod)%mod-pre1[i-1][j+l-1]+mod)%mod+pre1[i-1][j-1])%mod;
				x=x*pw[n*n-n*(i+l-2)-(j+l-1)]%mod;
				mp[x]=1;
			}
		}
	}
	for(int l=1;l<=n;l++)
	{
		for(int i=1;i+l-1<=n;i++)
		{
			for(int j=1;j+l-1<=n;j++)
			{
				x=((((pre2[i+l-1][j+l-1]-pre2[i+l-1][j-1])%mod+mod)%mod-pre2[i-1][j+l-1]+mod)%mod+pre2[i-1][j-1])%mod;
				x=x*pw[n*n-n*(i+l-2)-(j+l-1)]%mod;
				if(mp[x]==1)
				{
					ans=max(ans,l);
				}
			}
		}
	}
	cout<<ans;
}
```


---

## 作者：R·Dali (赞：3)

# 哈希表的题解

在求解过程中二分查找答案，

## 时间复杂度Θ（n^5logn）!

在判断的过程中哈希匹配。
```cpp
#include<iostream>
using namespace std;
int n;
int f[2][51][51];
//第一维表示哪一张地图，
//第二维表示行，
//第三维表示列，
//第四维表示长度。
//例如，在样例中，Hash[0][1][1][3]表示“1 2 3”的哈希值。
//ull型的数溢出时，可自动取模。
unsigned long long Hash[2][51][51][51];
int main(){
	cin>>n;
	for(int i=0;i<2;++i)
		for(int j=1;j<=n;++j)
			for(int h=1;h<=n;++h)
				cin>>f[i][j][h];
	for(int k=0;k<2;k++)
		for(int i=1;i<n;i++)
			for(int j=1;j<=n;j++)
				for(int h=1;h+i<=n;h++)
					Hash[k][j][h][i]=Hash[k][j][h][i-1]*131+f[k][j][i+h-1];//递推Hash。
	int l=1,r=n,mid;
        //二分查找
	while(l<r){
		bool fleg=0;
		mid=(l+r)>>1;
		for(int i=1;i+mid<=n;++i){
			for(int j=1;j+mid<=n;++j){
				for(int k=1;k+mid<=n;++k){
					for(int o=1;o+mid<=n;++o){
                    				//若第一行匹配，则向下面的行匹配。
						if(Hash[0][i][j][mid]==Hash[1][k][o][mid]){
							bool flag=1;
							for(int m=1;m<=mid;++m){
								if(Hash[0][i+m][j][mid]!=Hash[1][k+m][o][mid])
									flag=0;
							}
                            				//若匹配，向右二分。
							if(flag)l=mid+1,fleg=1;
						}
					}
				}
			}
		}
        	//否则，向左二分。
		if(!fleg)r=mid;
	}	
	cout<<l;
	return 0;
}
```

---

## 作者：MuelsyseU (赞：2)

题目：[P4398](https://www.luogu.com.cn/problem/P3914)

## 1. 前言

最近由于在考试中遇到 KMP 板子题由于失误而爆零的惨案，发奋学习一波哈希算法。这题 $n\le50$ 的数据应该说是非常容易卡过的，但是当看到题解区已经有用二分及 `unordered_map` 能够做到 $O(n^2\log{n})$ 的做法时，不禁考虑起如果按照 $n\le10^3$ 来做这道题，是否有进一步优化的空间。

于是不禁回忆起了 KMP 算法利用**已经匹配部分**的数据优化时间复杂度的特点。考虑到这题是二分答案，因此想要进一步优化时间复杂度非常困难，但是如果利用类似的手段将常数减小则是完全可行的。

目前该题解的优化算法无论是否吸氧都能够达到最优解，吸氧可以达到平均每个测试点 2ms 的水平。

## 2. 二分答案

首先，该算法的主要思路和 LightningUZ 相同，也就是二分答案一个边长 $k$，并且检查是否存在边长为 $k$ 的公共矩阵，并根据检查结果调整二分上下界来求解，因为显然有如下性质：

1. 如果不存在一个边长为 $k$ 的公共矩阵，则不可能存在一个边长为 $x > k$ 的公共矩阵。

2. 如果存在且仅存在若干个边长为 $k$ 的公共矩阵，则可能存在一个或多个边长为 $x > k$ 的公共矩阵，且**这些边长为 $k$ 的矩阵一定是这些更大矩阵的子矩阵**。

因此，当发现某个 $k$ 值可行，更小的 $k$ 值我们就可以不再关心；当发现某个 $k$ 值不可行，更大的 $k$ 值我们也不再关心。因此只需要查找 $O(\log{n})$ 次就能够找到一个确定的 $k$ 值。

```cpp
int find(int low,int high) {
	int mid;
	while(low+1<high){
		//mid=(low+high)/2的防溢出形式
		mid=low+(high-low)/2;
		if(check(mid)) low=mid;
		else high=mid;
	}
	//如果答案为high需要特判
	if(check(high)) return high;
	else return low;
}
```

## 3. Hash

也就是说，二分答案能将求解问题转为判定问题。然而，如何在 $O(n^2)$ 的时间内进行判定呢？此处采用了一种不同于 LightningUZ 大佬的在二分答案之前 $O(n^2)$ 预处理、二分时 $O(1)$ 查询子矩阵 Hash 值的 Hash 算法。

首先，我们都知道矩阵上的坐标 $(i,j)$ 可以用一个数 $i\times n+j$ 唯一表示。这种方法实际上是将 $(i,j)$ 看作一个 $2$ 位 $n$ 进制数。同理，将一个数列看作一个 $n$ 位 $base$ 进制数（其中 $base$ 为一个大质数常数），并且将其计算成一个经过取模后的数值，就是我们所说的一维 Hash。一般来说，直接使用 `unsigned long long` 存储这个 Hash 值，这样就相当于在运算溢出的过程中自动取模 $2^{64}-1$。

Hash 值最直接的用处就是快速判断两个序列是否全等，因为尽管 Hash 不保证对于两个不同的序列映射出相同的值，但可以保证对于相同的序列映射出相同的值，并且对于不同的值其冲突的概率是很小的，对本题的数据范围来说小到可以忽略不计。

另外，`unordered_map` 本身也是基于 Hash 实现，也就是把给定的 `key` 值转化为一个较小范围内的 Hash 值，并且把所有 Hash 值相同的 `key` 及数据值用链表或平衡树存储起来，达到均摊 $O(1)$ 查询的目的。

那么二维 Hash 又如何实现呢？首先显然要分别对两个矩阵处理出 $H$ 数组，其中 $H_{i,j}$ 表示以 $(1,1)$ 为左上角，以 $(i,j)$ 为右下角的矩阵的 Hash 值。可以先利用一维 Hash 求出一个临时数组 $T_{i,j}$ 表示 每个以 $(i,1)$ 开头，$(i,j)$ 结尾的序列的 Hash 值；此时这些序列都被转化为了数，因此如果竖着看又变成了一个一维序列，再竖着做一遍即可求出 $H$ 数组。

注意两次 Hash 不能采用相同的进制数 $base$，否则将很容易人为造成冲突。此处分别采用 $133331$ 和 $19260817$ 作为 $base$。

```cpp
for(int i=1;i<=n;++i) p1[i]=p1[i-1]*133331,p2[i]=p2[i-1]*19260817;
for(int i=1;i<=n;++i){
	for(arg j=1;j<=n;++j) ha[i][j]=ha[i][j-1]*133331+a[i][j];
}
for(int i=1;i<=n;++i){
	for(arg j=1;j<=n;++j) ha[i][j]+=ha[i-1][j]*19260817;
}
for(int i=1;i<=n;++i){
	for(arg j=1;j<=n;++j) hb[i][j]=hb[i][j-1]*133331+b[i][j];
}
for(int i=1;i<=n;++i){
	for(arg j=1;j<=n;++j) hb[i][j]+=hb[i-1][j]*19260817;
}
```
那么，$O(1)$ 查询子矩阵 Hash 值要如何实现呢？容易想到在一维 Hash 的情况下，只需要把 $[1,i]$ 这一段的 $Hash$ 值乘上 $base^{j-i+1}$，再用 $[1,j]$ 这一段的 Hash 值减去它即可得到 $[i,j]$ 这一段的 Hash 值。可以发现，这一部分和前缀和有异曲同工之妙；那么同样类比二维前缀和，可以得到如下代码：

```cpp
for(int i=1;i<=n;++i) p1[i]=p1[i-1]*133331,p2[i]=p2[i-1]*19260817;
int get(int i,int j,int k){
	return h[i][j]-h[i][j-k]*p1[k]-h[i-k][j]*p2[k]+h[i-k][j-k]*p1[k]*p2[k];
}
```

`get(i,j,k)` 获取以 $(i,j)$为右下角，边长为 $k$ 的矩形 Hash 值。

回归本题，在检查是否存在公共矩阵的 `check` 函数中，枚举 $i,j\in[k,n]$，并且将以第一个矩阵每个 $(i,j)$ 为右下角的边长为 $k$ 的矩阵 Hash 值存入 `unordered_map`；之后同样在第二个矩阵中枚举所有边长为 $k$ 的矩阵的 Hash 值，如果发现重复则认为匹配并返回 `true`，否则返回 `false`。

## 4. 优化

上述代码的时间复杂度为 $O(n^2\log{n})$，考虑进一步优化常数。在本题解第 2 部分中，有一个非常重要的性质被加粗标识。可以发现，在题目给出的数据范围中，即使在很大的第二个矩阵中，如果采用随机数据，实际上很可能只有一个或很少的几个位置与产生了边长较大的匹配。

换言之，如果已知在某个矩阵中，存在边长为 $k$ 的公共矩阵，则如果在某个矩阵 $A$ 中，某个位置为右下角边长为 $k$ 的子矩阵在另一个矩阵 $B$ 中不存在，则之后 `check` 函数也就无需再遍历这个位置，因为对于之后更大的 $k$ 值，这一位置对答案不会有贡献。

实际上，我们可以维护两个二元组的数组，存储以当前二分的 $low$ 值作为边长的所有公共矩阵在两个矩阵 $A,B$ 中分别的右上角坐标。初始时 $low=0$，此时该数组包含矩阵的所有坐标；而随着二分的过程，除了 $low=0$ 的情况外，一定存在以 $low$ 为边长的公共矩阵。

每次检查一个 $mid$ 是否可行时，只考虑将 $A$ 的以在数组中的坐标为右下角的子矩阵的 Hash 值放入 `unordered_map`，并且只尝试将 $B$ 的在另一个数组的坐标为右下角的子矩阵的 Hash 值在 `unordered_map` 中查找，而由于 $mid$ 始终大于 $low$，其它右下角坐标都不可能产生更多匹配。直到在这个过程中找到下一个 $mid$ 值，使得以 $A$ 的某个位置为右下角的边长为 $mid$ 的矩阵与以 $B$ 的某个位置为右下角的子矩阵，按照定义应使 $low=mid$，此时把所有这样的右下角坐标分别存入二元组数组。

容易发现，在经过二分后，大部分右下角坐标都会被迅速排除，只留下很少的几个坐标需要遍历。因此该算法对于随机数据的期望复杂度为 $\Theta(n^2)$，对于人为数据的最坏复杂度为 $O(n^2\log{n})$。

## 5. 实现

尝试卡常而尽量保证可读性的代码。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<unordered_map>
#define ull unsigned long long
#define arg register int
using namespace std;

//输入 
int n,a[55][55],b[55][55];
//numa,numb分别表示两个矩阵的可能匹配坐标个数 
//xa,ya存储矩阵a的可能匹配坐标，xb,yb同理 
int numa,numb,xa[2505],ya[2505],xb[2505],yb[2505];
//Hash相关，p1[i]=133331^i，p2=19260817^i  
ull ha[55][55],hb[55][55],p1[55]={1},p2[55]={1};
unordered_map<ull,bool> mp;
//快读优化 
inline void read(int &a){
    char c=getchar();
    int x=0, f=1;
    while(!isdigit(c)) f=(c=='-'?-1:f),c=getchar();
    while(isdigit(c)) x=(x<<3)+(x<<1)+c-'0',c=getchar();
    a=x*f;
}
//获取对于哈希数组h而言，以(i,j)为右下角的边长为k的矩阵Hash值   
inline ull get(ull h[55][55],int i,int j,int k){
	return h[i][j]-h[i][j-k]*p1[k]-h[i-k][j]*p2[k]+h[i-k][j-k]*p1[k]*p2[k];
}
inline bool check(arg s) { 
	bool res=0;
	register ull hsh;
	//此处tmp表示有多少个匹配（即新的numb值） 
	arg tmp=0;
	mp.clear();
	//填哈希表 
	for(arg i=1;i<=numa;++i){ 
		if(xa[i]<s||ya[i]<s) continue;
		mp[get(ha,xa[i],ya[i],s)]=0;
	}
	for(arg i=1;i<=numb;++i){
		if(xb[i]<s||yb[i]<s) continue;
		hsh=get(hb,xb[i],yb[i],s);
		//若找到匹配则记录下所有匹配的右下点 
		//注意更新数组时使用memset会使算法退化为n^2logn 
		if(mp.count(hsh)) res=mp[hsh]=1,xb[++tmp]=xb[i],yb[tmp]=yb[i];
	}
	if(res){
		//如果找到匹配则排除没有匹配的起始点继续二分 
		numb=tmp;
		//由于一个可能匹配多个，所以此处重新统计numa的值  
		tmp=0;
		for(arg i=1;i<=numa;++i){
			if(xa[i]<s||ya[i]<s) continue;
			//更新被匹配到的矩形的坐标  
			if(mp[get(ha,xa[i],ya[i],s)]) xa[++tmp]=xa[i],ya[tmp]=ya[i];
		}
		numa=tmp;
	}
	return res;
}
void init(){
	//预处理base的整数次幂 
	for(arg i=1;i<=n;++i) p1[i]=p1[i-1]*133331,p2[i]=p2[i-1]*19260817;
	//横向进行a的单行hash 
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j) ha[i][j]=ha[i][j-1]*133331+a[i][j];
	}
	//纵向进行a的矩阵hash 
	for(arg i=1;i<=n;++i){
		for(arg j=1;j<=n;++j) ha[i][j]+=ha[i-1][j]*19260817;
	}
	//横向进行b的单行hash 
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j) hb[i][j]=hb[i][j-1]*133331+b[i][j];
	}
	//纵向进行b的矩阵hash 
	for(arg i=1;i<=n;++i){
		for(arg j=1;j<=n;++j) hb[i][j]+=hb[i-1][j]*19260817;
	}
	
}
int find(int low,int high) {
	int mid;
	while(low+1<high){
		//mid=(low+high)/2的防溢出形式
		mid=low+(high-low)/2;
		if(check(mid)) low=mid;
		else high=mid;
	} 
	//如果答案为high需要特判
	if(check(high)) return high;
	else return low;
}
int main(){
	cin>>n;
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j) read(a[i][j]);
	}
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j){
    		read(b[i][j]);
    		//初始化，将所有点加入数组 
    		xa[++numa]=xb[++numb]=i,ya[numa]=yb[numb]=j;
		}
	}
	//初始化hash 
	init();
	//二分答案 
	cout<<find(0,n);
	return 0;
}
```

另外，针对开头所说的 $n\le10^3$ 的情况进行了测试，发现如果不使用双Hash有几率发生误判，在这里放一下未经大量测试的加强版代码。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<unordered_map>
#define ull unsigned long long
#define arg register int
using namespace std;

int n;
int a[1005][1005],b[1005][1005];
int numa,numb,xa[1000005],ya[1000005],xb[1000005],yb[1000005];
ull ha[1005][1005],hb[1005][1005],ha2[1005][1005],hb2[1005][1005],p1[1005]={1},p2[1005]={1};
unordered_map<ull,int> mp,mp2;
inline void read(int &a){
    char c=getchar();
    int x=0, f=1;
    while(!isdigit(c)) f=(c=='-'?-1:f),c=getchar();
    while(isdigit(c)) x=(x<<3)+(x<<1)+c-'0',c=getchar();
    a=x*f;
}
inline ull get(ull h[1005][1005],int i,int j,int k){
	return h[i][j]-h[i][j-k]*p1[k]-h[i-k][j]*p2[k]+h[i-k][j-k]*p1[k]*p2[k];
}
inline ull get2(ull h[1005][1005],int i,int j,int k){
	return h[i][j]-h[i][j-k]*p2[k]-h[i-k][j]*p1[k]+h[i-k][j-k]*p2[k]*p1[k];
}
inline bool check(arg s) { 
	bool res=0;
	register ull hsh,hsh2;
	arg tmp=0;
	mp.clear();
	for(arg i=1;i<=numa;++i){
		if(xa[i]<s||ya[i]<s) continue;
		mp[get(ha,xa[i],ya[i],s)]=0;
		mp2[get2(ha2,xa[i],ya[i],s)]=0;
	}
	for(arg i=1;i<=numb;++i){
		if(xb[i]<s||yb[i]<s) continue;
		hsh=get(hb,xb[i],yb[i],s);
		hsh2=get2(hb2,xb[i],yb[i],s);
		if(mp.count(hsh)&&mp2.count(hsh2)) res=mp[hsh]=1,xb[++tmp]=xb[i],yb[tmp]=yb[i];
	}
	if(res){
		numb=tmp;
		tmp=0;
		for(arg i=1;i<=numa;++i){
			if(xa[i]<s||ya[i]<s) continue;
			if(mp[get(ha,xa[i],ya[i],s)]) xa[++tmp]=xa[i],ya[tmp]=ya[i];
		}
		numa=tmp;
	}
	return res;
}
void init(){
	for(arg i=1;i<=n;++i) p1[i]=p1[i-1]*133331,p2[i]=p2[i-1]*19260817;
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j) ha[i][j]=ha[i][j-1]*133331+a[i][j];
    	for(arg j=1;j<=n;++j) ha2[i][j]=ha2[i][j-1]*19260817+a[i][j];
	}
	for(arg i=1;i<=n;++i){
		for(arg j=1;j<=n;++j) ha[i][j]+=ha[i-1][j]*19260817;
		for(arg j=1;j<=n;++j) ha2[i][j]+=ha2[i-1][j]*133331;
	}
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j) hb[i][j]=hb[i][j-1]*133331+b[i][j];
    	for(arg j=1;j<=n;++j) hb2[i][j]=hb2[i][j-1]*19260817+a[i][j];
	}
	for(arg i=1;i<=n;++i){
		for(arg j=1;j<=n;++j) hb[i][j]+=hb[i-1][j]*19260817;
		for(arg j=1;j<=n;++j) hb2[i][j]+=hb2[i-1][j]*133331;
	}
	
}
int find(int low,int high) {
	int mid;
	while(low+1<high){
		mid=low+(high-low)/2;
		if(check(mid)) low=mid;
		else high=mid;
	}
	if(check(high)) return high;
	else return low;
}
int main(){
	cin>>n;
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j) read(a[i][j]);
	}
	for(arg i=1;i<=n;++i){
    	for(arg j=1;j<=n;++j){
    		read(b[i][j]);
    		xa[++numa]=xb[++numb]=i,ya[numa]=yb[numb]=j;
		}
	}
	init();
	cout<<find(0,n);
	return 0;
}
```

---

## 作者：blue_tsg (赞：2)

因为要匹配两个子矩阵，考虑二维哈希。

~~之前有次模拟赛我现场口胡二维哈希挂了还被别人嘲讽了，没想到真的有这个算法。~~

与一维哈希类似，二维哈希也是利用了前缀和的思想，在这里我用一种类似扫描线的方法求解二维哈希。

记 $hash(i,l,r)$ 为第 $i$ 行 $l\to r$ 个字符的哈希值，$p[i]$ 为 $base^i$，我们首先枚举子正方形的边长 $x$，枚举正方形右端点 $j$，当从第 $i$ 行转移到第 $i+1$ 行时，我们要把第 $i+1$ 行的哈希值加上，并把第 $i-x$ 行的哈希值减去。

![](https://cdn.luogu.com.cn/upload/image_hosting/zj2dbfev.png)

如图，红色正方形代表已经加上哈希值的矩阵，现在要转移到第 $i+1$ 行。

![](https://cdn.luogu.com.cn/upload/image_hosting/wcmxkks3.png)

设 $s$ 为此时算到的哈希值，此时要 $s$ 乘上 $p[x]$ 并加上 $hash(i+1,1,j)$，$s$ 再减去 $hash(i-x,1,j)\times p[x^2]$。

为什么要乘 $p[x^2]$？因为第一行下面一共有 $x^2$ 个元素，也就是说第一行的元素被乘了 $x^2$ 遍 $base$，类比一维哈希即可。

把第一个矩形的所有哈希值都塞到哈希表里，求第二个矩形的哈希值时查询即可。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
#include <iostream>
#define endl putchar('\n')
using namespace std;
const int M = 100;
const int Mod = 20060107;
const unsigned long long base = 13331;
typedef unsigned long long ull;
typedef long long ll;
struct HashTable{
    ull key;int next;
};
HashTable e[Mod];int head[Mod],tot;
inline int read(){
    int x=0,f=0;char c=getchar();
    while(!isdigit(c)){
        if(c=='-') f=1;c=getchar();
    }
    do{
        x=(x<<1)+(x<<3)+(c^48);
    }while(isdigit(c=getchar()));
    return f?-x:x;
}
inline void insert(ull v){
    int u=v%Mod;
    for(int i=head[u];~i;i=e[i].next){
        if(e[i].key==v) return;
    }
    e[tot].key=v;
    e[tot].next=head[u];
    head[u]=tot++;
}
inline bool Find(ull v){
    int u=v%Mod;
    for(int i=head[u];i;i=e[i].next){
        if(e[i].key==v) return 1;
    }
    return 0;
}
ull has[2][M][M],p[M*M];
inline ull gethash(int t,int i,int l,int r){
    return has[t][i][r]-has[t][i][l-1]*p[r-l+1];
}
int Map1[M][M],Map2[M][M];
int n;
void insertMap(int x){
    for(int i=x;i<=n;i++){
        ull s=0;
        int l=i-x+1,r=i;
        for(int j=1;j<=n;j++){
            s=s*p[x]+gethash(0,j,l,r);
            if(j-x>0) s-=gethash(0,j-x,l,r)*p[x*x];
            if(j-x>=0) insert(s);
        }
    }
}
bool FindMap(int x){
    for(int i=x;i<=n;i++){
        ull s=0;
        int l=i-x+1,r=i;
        for(int j=1;j<=n;j++){
            s=s*p[x]+gethash(1,j,l,r);
            if(j-x>0) s-=gethash(1,j-x,l,r)*p[x*x];
            if(j-x>=0&&Find(s)) return 1;
        }
    }
    return 0;
}
signed main(){
    memset(head,-1,sizeof(head));
    n=read();
    for(int i=1;i<=n;i++){
        has[0][i][0]=1;
        for(int j=1;j<=n;j++){
            Map1[i][j]=read();
            has[0][i][j]=has[0][i][j-1]*base+Map1[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        has[1][i][0]=1;
        for(int j=1;j<=n;j++){
            Map2[i][j]=read();
            has[1][i][j]=has[1][i][j-1]*base+Map2[i][j];
        }
    }
    p[0]=1;
    for(int i=1;i<=n*n;i++) p[i]=p[i-1]*base;
    for(int i=1;i<=n;i++) insertMap(i);
    for(int i=n;i>=1;i--){
        if(FindMap(i)){
            printf("%d\n",i);
            return 0;
        }
    }
    printf("0");
    return 0;
}
```




---

## 作者：koobee (赞：1)

二分答案即可。

检验函数：先把 $A$ 矩阵中所有边长为 $mid$ 的子矩阵的 hash 值求出来，存进哈希表，再枚举 $B$ 矩阵中每一个边长为 $mid$ 的子矩阵，判断它的 hash 值在哈希表中是否出现即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 55, P = 1e9+7, Q = 1e9+9, mod = 1e6+7, M = 2e6;
int n, a[N][N], b[N][N], l, r, head[M], cnt;
ll h1[N][N], h2[N][N], p[N], q[N];
struct node{
	ll to, nxt;
}  e[M];
ll Hash(int X1, int Y1, int X2, int Y2, int op){
	if(op == 1) return h1[X2][Y2] - h1[X2][Y1 - 1] * p[Y2 - Y1 + 1] - h1[X1 - 1][Y2] * q[X2 - X1 + 1] + h1[X1 - 1][Y1 - 1] * p[Y2 - Y1 + 1] * q[X2 - X1 + 1];
	return h2[X2][Y2] - h2[X2][Y1 - 1] * p[Y2 - Y1 + 1] - h2[X1 - 1][Y2] * q[X2 - X1 + 1] + h2[X1 - 1][Y1 - 1] * p[Y2 - Y1 + 1] * q[X2 - X1 + 1];
}
void add(int x, ll y){
	e[++cnt] = {y, head[x]}, head[x] = cnt;
}
bool check(int mid){
	memset(head, 0, sizeof(head));
	cnt = 0;
	for(int i = mid; i <= n; i++)
		for(int j = mid; j <= n; j++){
			ll num = Hash(i-mid+1, j-mid+1, i, j, 1);
			add((num%mod+mod)%mod, num);
		}
	for(int i = mid; i <= n; i++)
		for(int j = mid; j <= n; j++){
			ll num = Hash(i-mid+1, j-mid+1, i, j, 2);
			int yu = (num % mod + mod) % mod;
			for(int y = head[yu]; y; y = e[y].nxt)
				if(e[y].to == num) return true;
		}
	return false;
}
int main(){
	cin>>n;
	r = n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++){
			cin>>a[i][j];
			h1[i][j] = h1[i][j-1] * P + h1[i-1][j] * Q - h1[i-1][j-1] * P * Q + a[i][j];
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++){
			cin>>b[i][j];
			h2[i][j] = h2[i][j-1] * P + h2[i-1][j] * Q - h2[i-1][j-1] * P * Q + b[i][j];
		}
	p[0] = q[0] = 1;
	for(int i = 1; i <= n; i++) p[i] = p[i-1] * P, q[i] = q[i-1] * Q;
	while(l < r){
		int mid = (l + r + 1) / 2;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：Shawk (赞：1)

希丰展，看[博客](https://www.cnblogs.com/Z8875/p/13405596.html)

~~来一波对随机数据友好的操作~~
* 题目大意

找到最大公共子矩阵（必须为正方形）。
* 解题思路

写法类似于Hash表。

Hash表是将同一类的放进一个链表中，减少查找的次数。

这道题可以直接将矩阵内的和当做分类的标准，这个可以通过矩阵前缀和进行 $O(n^2)$ 的预处理，可以$O(1)$ 的计算出来，将矩阵和相同的放在一条链中，

* 注意事项
  1. Hash表的数量由子矩阵的数量确定，一个 n×n 的矩阵有 n×n×n 个子矩阵，head数组和链表结构体开 $n^3$ 的就够的，模数就取数组能开下的范围内最大的质数就可以了。
  2. 本写法比较用于随机数据，因为这样分布到每条链上的个数都会很少，而对于特殊构造的数据，时间复杂度可能会退化到 $O(n^7)$，但过本题是没问题的。
  
详细看代码注释。
```cpp
#include <cstdio>
#define ll long long
using namespace std;
const int N = 105, M = 1157621;//M是105*105*105中最大质数
const int N3 = N*N*N;
int n, a[N][N], b[N][N];
ll s[2][N][N];//存前缀和
struct Node {
	int k, x, y, next;
}h[N3];//链表
int head[N3], tot;
int Ha(int k, int x, int y, int p) {//求Hash值
	x--, y--;
	return (int)(s[p][x+k][y+k] - s[p][x][y+k] - s[p][x+k][y] + s[p][x][y]) % M;//通过前缀和求期间和
}
void Add(int k, int i, int j) {//在Hash表中添加，挺像加边操作
	int ha = Ha(k, i, j, 0);
	h[++tot] = (Node) {k, i, j, head[ha]};
	head[ha] = tot;
}
bool Judge(int n, int k, int x, int y) {//判断是否相同
	if (h[n].k != k) return 0;
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			if (a[h[n].x+i][h[n].y+j] != b[x+i][y+j])
				return 0;
	return 1;
}
bool Find(int k, int x, int y) {
	int ha = Ha(k, x, y, 1);
	if (!head[ha]) return 0;
	for (int i = head[ha]; i; i = h[i].next)//遍历这条链
		if (Judge(i, k, x, y)) return 1;
	return 0;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]), 
			s[0][i][j] = s[0][i-1][j] + s[0][i][j-1] - s[0][i-1][j-1] + a[i][j];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &b[i][j]),
			s[1][i][j] = s[1][i-1][j] + s[1][i][j-1] - s[1][i-1][j-1] + b[i][j];
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i + k - 1 <= n; ++i)
			for (int j = 1; j + k - 1 <= n; ++j)
				Add(k, i, j);//将第一个图的所有子矩阵加入
	for (int k = n; k >= 1; --k)//从大到小枚举，找到了直接输出，这个for也可以二分
		for (int i = 1; i + k - 1 <= n; ++i)
			for (int j = 1; j + k - 1 <= n; ++j)
				if (Find(k, i, j)) return printf("%d\n", k), 0;
	puts("0");
	return 0;
}

```

---

## 作者：Yanzy2333 (赞：1)

# $O(N^7)$ 暴力碾过！

$\qquad \qquad$————思路来自 @wangyitong的[一篇讨论](https://www.luogu.org/discuss/show?postid=68304)

7重循环的意思代码里解释：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a1[60][60];
int a2[60][60];//两个地图
int main(){
	int n;
	int mx=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a1[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a2[i][j]);
		}
	}//输入
	for(int o=1;o<=n;o++){//枚举正方形边长
		for(int i=1;i<=n-o+1;i++){//第一个地图的边长为o的正方形的第一个点的横坐标
			for(int j=1;j<=n-o+1;j++){//纵坐标
				for(int k=1;k<=n-o+1;k++){//
					for(int l=1;l<=n-o+1;l++){//第二个地图的
						if(a1[i][j]!=a2[k][l]) continue;//如果第一个点都不相等那就干脆不要比较了，省时间
						bool b=1;//b代表是否找到解
						for(int u=1;u<=o;u++){//
							for(int v=1;v<=o;v++){//两个地图比较
								if(a1[i+u-1][j+v-1]!=a2[k+u-1][l+v-1]){
									b=0;
									break;//找到不相等就立即退出，省时间
								}
							}
							if(b==0){
								break;
							}
						}
						if(b==1){
							mx=max(mx,o);//如果找到解就存储
						}
					}
				}
			}
		}
	}
	printf("%d",mx);//输出
	return 0;//结束
}

```

宣传[blog](https://jiying.blog.luogu.org/)

---

## 作者：Nemonade (赞：0)

## 题意：

给出两个 $n\times n$ 的正矩阵 $a$、$b$，求这两个矩阵的最大相同子正矩阵。

## 思路

由这个“最大正矩阵”很容易联想到[最大正方形](https://www.luogu.com.cn/problem/P1681)，所以考虑DP。

设状态 $dp_{x,y,xx,yy}$ 表示矩阵 $a$ 中右下角是 $a_{x,y}$，矩阵 $b$ 中右下角是 $b_{xx,yy}$ 的最大相同子正矩阵。

那么考虑转移，对于状态 $(x,y,xx,yy)$，当 $a_{x,y}\not=b_{xx,yy}$ 时，显然没有任何相同的矩阵，$dp_{x,y,xx,yy}=0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3jz0fhd8.png)

对于 $a_{x,y}=b_{xx,yy}$ 的情况，如上图。更新 $N$ 节点的值时，要取决于节点 $X$、$Y$、$Z$ 的大小，也就是图中蓝色矩阵的区域。因为节点 $N$ 的值，也就是红色区域，必须完全与蓝色部分重合。所以当 $X$ 或 $Z$ 节点的值较小时，$N$ 的值等于 $X$、$Z$ 中较小值加一。

![](https://cdn.luogu.com.cn/upload/image_hosting/21zhqvyn.png)

当 $Y$ 更小时，红色部分只是 $Y$ 部分的延续，所以直接是 $Y$ 节点的值加一。

综上所述，$a_{x,y}=b_{xx,yy}$ 时的转移方程是：

$$dp_{x,y,xx,yy}=\min(dp_{x-1,y,xx-1,yy},dp_{x,y-1,xx,yy-1},dp_{x-1,y-1,xx-1,yy-1})+1$$

转移是 $O(1)$ 的，状态数是 $n^4$，所以时间和空间复杂度是 $O(n^4)$。

虽然复杂度不是最优的，但是常数小并且非常好想又好写啊。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rd() (read<int>())
#define pfor(i,x,y) for(register int i=x;i<=y;++i)
#define mfor(i,x,y) for(register int i=x;i>=y;--i)
template<typename T>
inline T read(){
	T x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
template<typename T>
inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x/10) write(x/10);
	putchar((x%10)^48);return;
}
using std::max;using std::min;using std::abs;
using std::cin;using std::cout;using std::endl;
using std::sort;using std::__gcd;
const int N=5e1+5;
int n,a[N][N],b[N][N],dp[N][N][N][N],res;
signed main(){
	n=rd();
	pfor(i,1,n) pfor(j,1,n) a[i][j]=rd();
	pfor(i,1,n) pfor(j,1,n) b[i][j]=rd();
	dp[0][0][0][0]=0;
	pfor(x,1,n) pfor(y,1,n){
		pfor(xx,1,n) pfor(yy,1,n){
			if(a[x][y]==b[xx][yy])
				dp[x][y][xx][yy]=min(dp[x-1][y-1][xx-1][yy-1],
				min(dp[x-1][y][xx-1][yy],dp[x][y-1][xx][yy-1]))+1;
			else dp[x][y][xx][yy]=0;
		}
	}
	pfor(x,1,n) pfor(y,1,n) pfor(xx,1,n) pfor(yy,1,n)
		res=max(dp[x][y][xx][yy],res);//最后记录答案时一定要遍历整个数组 
	cout<<res; 
	return 0;
}
```

---

## 作者：Jayun (赞：0)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/P4398)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14731121.html)

# 题目大意：

求两个矩阵的最大公共子正方形矩阵的边长。

$n\leq 50$。

# 正文：

暴力是 $\mathcal{O}(n^7)$，考虑优化暴力。

既然是找“公共”，那么一定会判相同，可以用二维 Hash 和 Hash 表解决。

然后就有了一个 $\mathcal{O}(n^3)$ 的暴力：枚举正方形右下角点和其边长。继续优化它，可以发现，其实可以通过二分边长把时间复杂度降到 $\mathcal{O}(n^2\log n)$。

有一点需要注意：Hash 表的空间不是 $n^2$ 的，而是 $\sum_{i=1}^n i^2=\frac{n(n+1)(2n+1)}{6}$ 的，因为所有边长的正方形都要考虑到。

# 代码：

```cpp

const int N = 60;

inline ll READ()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

unsigned ll base1 = 87, base2 = 37;
unsigned ll fac1[N], fac2[N];
struct HASH
{
	unsigned ll h[N][N];
	HASH() {memset(h, 0, sizeof h);}
	inline unsigned ll* operator [] (int a) {return h[a];} 
}H[2];

const ll mod = 19260817ll;
struct Hash
{
	unsigned ll val;
	int nxt, len;
}h[1ll * N * (N + 1) * (2 * N + 1) / 6];
int head[mod + 10], tot;
void add(unsigned ll x, int len)
{
	ll y = x % mod;
	h[++tot] = (Hash){x, head[y], len}, head[y] = tot;
}
bool query(unsigned ll x, int len)
{
	ll y = x % mod;
	for (int i = head[y]; i; i = h[i].nxt)
		if (h[i].val == x && h[i].len == len) return 1;
	return 0;
}

int n;
ll a[N][N], b[N][N];

unsigned ll calc(int x1, int y1, int x2, int y2, int len, int f)
{
	return H[f][x2][y2] - H[f][x1 - 1][y2] * fac2[len] - 
	    H[f][x2][y1 - 1] * fac1[len] + H[f][x1 - 1][y1 - 1] * fac1[len] * fac2[len];
}

bool check(int x)
{
	for (int i = x; i <= n; i++)
		for (int j = x; j <= n; j++)
			add(calc(i - x + 1, j - x + 1, i, j, x, 0), x);
	for (int i = x; i <= n; i++)
		for (int j = x; j <= n; j++)
			if(query(calc(i - x + 1, j - x + 1, i, j, x, 1), x))
				return 1;
			
	return 0;
}

int main()
{
	n = READ();
	fac1[0] = fac2[0] = 1ull;
	for (int i = 1; i <= n; i++)
		fac1[i] = fac1[i - 1] * base1, 
		fac2[i] = fac2[i - 1] * base2;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = READ();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			b[i][j] = READ();
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			H[0][i][j] += H[0][i][j - 1] * base1 + a[i][j],
			H[1][i][j] += H[1][i][j - 1] * base1 + b[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			H[0][i][j] += H[0][i - 1][j] * base2,
			H[1][i][j] += H[1][i - 1][j] * base2;
			
	int l = 1, r = n, mid, ans = 0;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) l = mid + 1, ans = max(ans, mid);
		else r = mid - 1;
	} 
	printf("%d\n", ans);
	return 0;
}

```

---

