# Maximum Submatrix 2

## 题目描述

You are given a matrix consisting of digits zero and one, its size is $ n×m $ . You are allowed to rearrange its rows. What is the maximum area of the submatrix that only consists of ones and can be obtained in the given problem by the described operations?

Let's assume that the rows of matrix $ a $ are numbered from 1 to $ n $ from top to bottom and the columns are numbered from 1 to $ m $ from left to right. A matrix cell on the intersection of the $ i $ -th row and the $ j $ -th column can be represented as $ (i,j) $ . Formally, a submatrix of matrix $ a $ is a group of four integers $ d,u,l,r $ $ (1<=d<=u<=n; 1<=l<=r<=m) $ . We will assume that the submatrix contains cells $ (i,j) $ $ (d<=i<=u; l<=j<=r) $ . The area of the submatrix is the number of cells it contains.

## 样例 #1

### 输入

```
1 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2
10
11
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 3
100
011
000
101
```

### 输出

```
2
```

# 题解

## 作者：localhost (赞：4)

预处理出$f[i][j]$表示$(i,j)$向右连续多少个1

然后枚举矩阵的一边，然后对这一列的$f[i][j]$排序后枚举就可以了

具体看代码

```cpp
#include<bits/stdc++.h>
namespace ZDY{
	#pragma GCC optimize(3)
	#define il __inline__ __attribute__ ((always_inline))
	#define rg register
	#define ll long long
	#define ull unsigned long long
	#define db double
	#define sht short
	#define MB template <class T>il
	#define Fur(i,x,y) for(int i=x;i<=y;i++)
	#define Fdr(i,x,y) for(int i=x;i>=y;i--)
	#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
	#define clr(x,y) memset(x,y,sizeof(x))
	#define cpy(x,y) memcpy(x,y,sizeof(x))
	#define fin(s) freopen(s".in","r",stdin)
	#define fout(s) freopen(s".out","w",stdout)
	#define fcin ios::sync_with_stdio(false)
	#define l2(n) (int(log2(n)))
	#define inf 0x3f3f3f3f
	MB T ABS(T x){return x>0?x:-x;}
	MB T MAX(T x,T y){return x>y?x:y;}
	MB T MIN(T x,T y){return x<y?x:y;}
	MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
	MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 5011
int n,m,f[N][N],t[N];
char a[N][N];
int main(){
	in>>n>>m;
	Fur(i,1,n)in>>(a[i]+1);
	Fur(i,1,n)
		Fdr(j,m,1)
		if(a[i][j]==49)f[i][j]=f[i][j+1]+1;
	
	int ans=0;
	Fur(j,1,m){
		Fur(i,1,n)t[i]=f[i][j];
		sort(t+1,t+n+1);
		Fur(i,1,n)ans=MAX(ans,t[i]*(n-i+1));
	}
	out<<ans<<ln;
}
```

---

## 作者：hsy8116 (赞：3)

### 前言

管理员大大，图是我一笔一画画上去的，很认真了，我刚开始写题解，文中可能仍有疏忽，求谅解，求通过。

### 题意简述

给定一个只包含 $01$ 的矩阵，如果可以**无数次**交换任意两行，求一个只包含 $1$ 的子矩阵且满足面积最大，最大面积是多少？

### 思路分析

考虑到矩形的边一定是横平竖直的，所以先尝试确定下矩形的一边。图 1 中，如使 $j=2$ 为矩形的一边，标定为 $\textcolor{red}{红色}$，来分析怎样计算交换后的最大矩形面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/ic98u3w2.png)

首先，在 $j=2$ 左侧的数字中只有最右侧的连续一段的 $1$ 才有可能记成以 $j=2$ 为边的矩形的组成部分。这部分是我们计算要使用的，标定为 $\textcolor{blue}{蓝色}$，可以考虑预处理出 $c_{i,j}$ 表示坐标 $(i,j)$ 左侧连续 $1$ 的个数。

接下来，我们考虑 _无数次交换任意两行_ 这个操作，如果每两行都可以无限交换，那么这个矩阵可以随意改变行的先后顺序，也就是**按照一定顺序对行排序**。

想到这点后，我们思考如何排序有利于矩形面积的计算。显然，当对同一列的 $c_{i,j}$ **从小到大排序**时，对于每个第 $j$ 列第 $i$ 行的 $c_{i,j}$ 值 ，它对后面更大的 $c_{i',j}$ 值的位置有贡献，这里 $i'$ 一定在 $i$ 后面，因而 $c_{i,j} \leqslant c_{i',j}$，所以 $i$ 一定能和 $i'$ 形成矩形，这个矩形中 $c_{i,j}$ 就是矩形的宽，$i’-i+1$ 就是矩形的长。很明显，$i'$ 越大矩形的长越大，矩形的宽又不变，矩形的面积就最大，于是 $i'$ 最优值取 $n$ 。

**总结上一段，我们对列 $j$ 的 $c$ 值从小到大排序，依次遍历行 $i$，矩形最大面积不断和 $c_{i,j} \times (n-i+1)$ 取最大值，即可得到答案。**

上图图 1 处理后形成一下图：

注意：下图中的 $i$ 本应不改变，但为了识别不同的行在什么位置，我手动将它改变，上文中的 $i$ 和 $i'$ 与下图中的 $i$ 无关。

![](https://cdn.luogu.com.cn/upload/image_hosting/e1hkv6nm.png)

图 2 中考虑第 $1$ 行时，最大矩形面积为 $3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/przzhutd.png)

图 3 中考虑第 $2$ 行时，最大矩形面积为 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ish082hn.png)

图 4 中考虑第 $3$ 行时，最大矩形面积为 $2$。

### $Code$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int NR = 5010;
char a[NR][NR];
int c[NR][NR];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
	{
		scanf("%s", a[i] + 1);
	}
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 1; j <= m; j ++)
		{
			if (a[i][j] == '1') c[j][i] = c[j - 1][i] + 1;
			else c[j][i] = 0;
		}
	}
	int ans = 0;
	for (int j = 1; j <= m; j ++)
	{
		sort(c[j] + 1, c[j] + n + 1);
		for (int i = 1; i <= n; i ++)
		{
			ans = max(ans, c[j][i] * (n - i + 1));
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：SkyRainWind (赞：3)

这道题，当时 18 年在浙江培训的时候做过几乎一样的原题，叫《说好的一起富起来呢贺爸你怎么不等我》，青春易逝啊，挺感慨的。

题目本身非常简单，甚至不需要动态规划。

注意到行是可以随便换的，因此从第 $m$ 列到第 $1$ 列递推，每次只与当前列右边第一串 $1$ 的个数有关，这样每次就可以从第 $i+1$ 列递推到第 $i$ 列，就记一下极长的 $1$ 个数，然后逆序排序统计答案即可。

直接实现是 $O(n^2\log n)$ 的，由于 $n=5000$ 还是通不过的。考虑优化：

注意到每次如果当前列当前行是 $1$ 的话，其实相对大小是不会变的，如果是 $0$ 的话就挪到最后，这样每次用类似归并排序的想法就可以做到线性的合并了，时间复杂度 $O(n^2)$。

```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define pii pair<int,int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 5005;

int n,m,a[maxn][maxn];
pii sum[maxn];	// <sum, id>
pii s[5002];

signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		char s[5005];scanf("%s",s + 1);
		for(int j=1;j<=m;j++)a[i][j] = s[j] - '0';
	}
	int ans = 0;
	for(int j=1;j<=n;j++)
		if(a[j][m] == 1)sum[j] = mpr(1, j), ans = 1;
		else sum[j] = mpr(0, j);
	sort(sum+1,sum+n+1,[&](pii a,pii b){return a.first > b.first;});
	
	for(int i=m-1;i>=1;i--){
		int lst = n, fi = 0;
		for(int j=1;j<=n;j++){
			pii v = sum[j];
			if(a[v.second][i] == 0)s[lst --] = mpr(0, v.second);
			else s[++ fi] = mpr(v.first+1, v.second);
		}
		for(int i=1;i<=n;i++)
			ans = max(ans, s[i].first * i), 
			sum[i] = s[i];
	}
	printf("%d\n",ans);
	
	return 0;
}
```

青春不朽，青春万岁。

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF375B)

### 题目大意
给定一个 $n \times m$ 的 01 矩阵，可以任意交换行，求交换后只包含 $1$ 的子矩阵的最大面积。

### 解题思路
由于可以交换行，但是不能交换列，一个贪心的想法是枚举两列，然后找到在这两列之间全为 $1$ 的行，通过交换放到一起，就是以这两列为边界的子矩阵中最大的情况。

其实这样已经可以写了，强行二维前缀和一下可以知道用 $1$ 覆盖一个区间的行数。

不过还有更简单的方法。预处理出每一格往右的连续的 $1$ 的右端点。枚举左边的列边界，然后对于每一行在对于连续的 $1$ 位置差分一下，这样就可以枚举右端点，并知道从左端点一直到右端点有多少行用连续的 $1$ 完全覆盖了这个区间。

时间复杂度 $O(nm)$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3010;
char s[N];
int Nxt[N][N],sum[N];
int main(){
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++){
		scanf("%s",s+1);
		for (j=m;j>=1;j--){
			if (s[j]=='0'){
				Nxt[i][j]=0;
			}else{
				Nxt[i][j]=max(j,Nxt[i][j+1]);
			}
		}
	}
	int Ans=0;
	for (i=1;i<=m;i++){
		for (j=1;j<=n;j++){
			if (Nxt[j][i]!=0){
				sum[i]++;
				sum[Nxt[j][i]+1]--;
			}
		}
		int Sum=0;
		for (j=i;j<=m;j++){
			Sum+=sum[j];
			sum[j]=0;
			Ans=max(Ans,Sum*(j-i+1));
			if (Sum==0){
				break;
			}
		}
	}
	printf("%d",Ans);
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

我们首先预处理一个数组 $f_{i,j}$，表示从 $a_{i,j}$ 开始往后一共有几个连续的 $1$（包括 $a_{i,j}$）。

然后我们枚举子矩阵的左边界 $j$（子矩阵为 $[(i,j)(x,y)]$，分别是左上角和右下角的坐标）。这时我们把所有 $f_{i,j},i\in[1,n]$ 都加入到一个数组 $t$ 中，然后对其进行从大到小排序（从小到大也行，只不过要一些下标上的变化）。

这样做有什么用呢？我们在排序后从前往后枚举 $t_i$，那么我们知道 $t_1\sim t_i$ 都是 $≥t_i$ 的，说明这 $i$ 行的第 $j$ 个数字及后面都有 $≥t_i$ 个连续的 $1$，由于我们可以进行无数次交换，所以我们总可以把这 $i$ 行交换到一起。

所以这时候我们就可以用 $t_i\times i$ 来尝试更新答案了。

时间复杂度为 $O(n^2)$。

## 代码
注意卡常。

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////
#pragma GCC optimize(3)
//
#include<bits/stdc++.h>

//
//#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back


using namespace std;
//
const int N=5e3+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
//const int IINF=1e18;
const db eps=1e-9;
//
int n,m,b,q,s[N],op,idx,len[N],ans,res,tmp,cnt[N],id[N];

int f[N][N],t[N];
char a[N][N];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=m;j>=1;j--)
		if(a[i][j]=='1')f[i][j]=f[i][j+1]+1;
	
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=m;j++)
//		cout<<f[i][j]<<' ';
//		cout<<endl;
//	}
	int ans=0;
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++)t[i]=f[i][j];
		sort(t+1,t+n+1);
		for(int i=1;i<=n;i++)ans=max(ans,t[i]*(n-i+1));
	}
	printf("%d",ans);
}
//

```






---

## 作者：Allanljx (赞：0)

## 思路
用 $dp$ 数组预处理出从第 $i$ 行，第 $j$ 列开始向右有多少个连续的 $1$。如果当前这位是 $0$，那么 $dp_{i,j}=0$，否则 $dp_{i,j}=dp_{i,j+1}+1$。然后对于每一列的 $dp$ 数组从大到小排序，然后枚举前 $i$ 行计算，$ans=\max(ans,i\cdot a_i)$。另外，建议使用 C++20 这样不容易 T。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[5005][5005];
char c[5005][5005];
int a[5005];
int n,m,ans;
int b[5005];
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		getchar();
		for(int j=1;j<=m;j++) c[i][j]=getchar();
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=1;j--)
		{
			if(c[i][j]=='1') dp[i][j]=dp[i][j+1]+1;//dp
			else dp[i][j]=0;
		}
	}
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++) a[i]=dp[i][j];
		sort(a+1,a+n+1,greater<int>());
		for(int i=1;i<=n;i++)
		{
			ans=max(ans,i*a[i]);//求矩形面积 
		}
	}
	printf("%lld",ans);
}
```

---

