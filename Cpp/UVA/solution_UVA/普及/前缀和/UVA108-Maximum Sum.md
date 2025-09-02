# Maximum Sum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=44

[PDF](https://uva.onlinejudge.org/external/1/p108.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/9bad502ba34d25d0111329e7b191a1e73f37eafb.png)

## 样例 #1

### 输入

```
4
0 -2 -7 0 
9 2 -6 2
-4 1 -4 1 
-1 8 0 -2```

### 输出

```
15```

# 题解

## 作者：gcwixsxr (赞：8)

本蒟蒻看这道题还没有动态规划这个做法,于是就发一发动态规划的题解.

这道题有一道很类似的题目 [P3009 [USACO11JAN]Profits S](https://www.luogu.com.cn/problem/P3009) ,那道题是一维的,而这道题则变成了二维的,但做法大同小异.

首先解释一下几个变量:

```cpp
int n;
int a[101][101];
int sum[101][101];
int f[101][101][101];
```
 $n$为题目中的矩阵边长;

 $a$数组,$a[i][j]$代表第 $i$ 行第 $j$ 列的元素的值;

 $sum$数组,$sum[i][j]$代表第 $i$ 行前 $j$ 个数的和;

 $f$数组,$f[i][j][k]$代表第 $i$ 行选定从第 $j$ 个到第 $k$ 个元素为前提下前 $i$ 行的最大值,简单的就理解为当矩阵的左下角为$(i,j)$,右下角为$(i,k)$时,最优矩阵的值;

然后看看状态转移方程:

```cpp
f[i][j][k]=max(0,f[i-1][j][k])+sum[i][k]-sum[i][j-1];
```
解释一下这个方程:

如果前 $i-1$ 行从第 $j$ 列到第 $k$ 列产生最优矩阵的值小于零,则第 $i$ 行不加入前面的矩阵,自成新矩阵, 那么前 $i$ 行从第 $j$ 列到第 $k$ 列产生最优矩阵的值就是本行从 $j$ 个元素到第 $k$ 个元素的和.

反之,如果前 $i-1$ 行从第 $j$ 列到第 $k$ 列产生最优矩阵的值大于零,则第 $i$ 行要加入前面的矩阵,那么前 $i$ 行从第 $j$ 列到第 $k$ 列产生最优矩阵的值就是前面的最优矩阵的值加上本行从 $j$ 个元素到第 $k$ 个元素的和.

![](https://cdn.luogu.com.cn/upload/image_hosting/gq568n5l.png)


就例如上面这个矩阵,当枚举到$f[2][1][3]$这个状态时,容易想到它是通过$f[1][1][3]$转移过来的,但$f[1][1][3]=(-1)+2+(-2)=-1<0$,所以$f[2][1][3]$不取$f[1][1][3]$的结果,因此$f[2][1][3]=max(0,f[1][1][3])+1+2+2=5$.

下面是 $AC$ 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int f[101][101][101];
int a[101][101];
int sum[101][101];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			sum[i][j]=sum[i][j-1]+a[i][j];
		} 
	}
	int ans=-0x7fffffff;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int l=1;l<=n-j+1;l++){
				int k=j+l-1;
				f[i][j][k]=max(0,f[i-1][j][k])+sum[i][k]-sum[i][j-1];
				ans=max(ans,f[i][j][k]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Dreamweaver (赞：5)

# 前言

这题其实是P1719的双倍经验，一道二维前缀和入门题。

萌新第一次写题解，~~求过~~如有纰漏，请各位大佬斧正。

# 题意

给你一个 $N*N$ 的矩阵，矩阵的每一个元素都有一权值，求矩阵中最大加权矩形，即从中找一矩形，矩形大小无限制，使其中包含的所有元素的和最大 。

# 知识点

## 前缀和

### 一维前缀和：

![](https://cdn.luogu.com.cn/upload/image_hosting/cxfhihq7.png)

#### 定义：

设有一数组 $a[]$，其前缀和数组为 $sum[]$,则 $sum[i]=a[1]+a[2]+……+a[i]$。

#### 求法：

```cpp
for(int i=1;i<=n;++i)
	cin>>a[i],sum[i]=sum[i-1]+a[i];                     
                     
```
#### 性质：

通过前缀和数组可以快速求出原数组的区间和。

例如：求区间 $[l,r]$ 的和，（即 $a[l]+a[l+1]+…+a[r]$)，则 $a[l]+a[l+1]+…+a[r]=(a[1]+a[2]+…+a[r])-(a[1]+a[2]+…+a[l-1])=sum[r]-sum[l-1]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/yu2zez0a.png)

### 二维前缀和

![](https://cdn.luogu.com.cn/upload/image_hosting/uup1gbf3.png)

#### 定义：

设有一二维数组 $a[][]$，其前缀和数组为 $sum[][]$,则 $sum[i][j]=a[1][1]+a[1][2]+…+a[2][1]+a[2][2]+…+a[i][j]$(即：从 $a[1][1]$ 到 $a[i][j]$ 这个矩形内的权值和）。

#### 求法：

##### 法一：

```cpp
for(re int i=1;i<=n;i++)
	for(re int j=1;j<=n;j++)
		cin>>a[i][j],sum[i][j]+=sum[i][j-1]+sum[i-1][j]+a[i][j]-sum[i-1][j-1];
```
	
##### 法二：

直接在原数组上进行两次一维前缀和。

 ```cpp
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
			cin>>a[i][j],a[i][j]+=a[i][j-1];
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
			a[i][j]+=a[i-1][j];
```

#### 性质：

通过前缀和数组可以快速求出原数组的一个矩形区域权值和。

例如：
求 $a$ 数组 $(x1,y1)$ 到 $(x2,y2)(x1<x2,y1<y2)$ 的和 $Ans$，则 $Ans=sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wexaa4g9.png)

图中是求 $(2,2)$ 到 $(5,3)$ 这个矩形的和，$(1,1)$ 这一部分被减掉了两次，所以最后要再加上一个。

# 作法

1. 读入矩阵，求出前缀和数组；

1. 枚举 $(x1,y1)$,$(x2,y2)$,即枚举选择的矩形；

1. 利用前缀和数组，求出这个矩形内的权值和，并每次与 $Ans$ 取 $max$；

1. 输出 $Ans$。

# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define inf 0x3f3f3f3f
#define re register
#define maxn 100010
#define int long long
#define Orz cout<<"stO %王队% Orz"<<'\n';
int n;
int a[220][220]; 
int ans=0;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0'; ch=getchar();}
    return x*f;
}
signed main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
//	printf("%dM\n",(sizeof(dp) >> 20));
	cin>>n;
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
			a[i][j]=read(),a[i][j]+=a[i][j-1];
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
			a[i][j]+=a[i-1][j];  //直接在原数组上求前缀和
	for(re int x1=1;x1<=n;x1++)  //枚举两个点的坐标，注意：这两个点可以重合，此时选择的矩形就是一个点
		for(re int y1=1;y1<=n;y1++)
			for(re int x2=x1;x2<=n;x2++)
				for(re int y2=y1;y2<=n;y2++)
					ans=max(ans,a[x2][y2]-a[x2][y1-1]-a[x1-1][y2]+a[x1-1][y1-1]);
	cout<<ans<<'\n';//结尾一定要输出换行符，否则会WA
	return 0;
}

```





---

## 作者：qianfujia (赞：4)

安利一发我的blog[我的博客](https://www.luogu.org/blog/user29519/)

还没有O(n^3)做法？我来水一发

是一种贪心+前缀和，很巧妙吧？

其实前一篇题解没有优化，n稍微大一点就不行了

~~根据他的前缀和，最大子段和也要n^2~~

# **又及：输出千万要endl，我被坑了很久**

详见代码注释

```
#include<bits/stdc++.h>
using namespace std;
int n,ans=-2147483647;
int a[300][300],f[300][300],s[300];
int main()
{
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
          for (int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
         //读入
        for (int j=1;j<=n;j++)
          for (int i=1;i<=n;i++)
            f[i][j]=f[i-1][j]+a[i][j];
        //前缀和预备
        for (int i=1;i<=n;i++)
          for (int j=i;j<=n;j++)
                {
                        for (int k=1;k<=n;k++)
                          s[k]=f[j][k]-f[i-1][k];
                        //转化成一维最大子段和
                        int p=0;
                        for (int k=1;k<=n;k++)
                        {
                                if (p>0) p+=s[k];
                                  else p=s[k];
                                if (p>ans) ans=p;
                        }
                        //最大子段和标准贪心
                }
        cout<<ans<<endl;//输出endl，endl，endl（重要的事情说三遍）
        return 0;
}
```

---

## 作者：封禁用户 (赞：2)

### 前言

这道题就这么优秀嘛，为啥和Luogu 题库撞了啊QAQ

[前置芝士](https://www.luogu.com.cn/blog/CM0/chafen-qianzhuihe)


### 题目大意

求矩阵中最大加权矩形。即矩阵的每一个元素都有一权值，从中找一矩形，使其中包含的所有元素之和最大。

### $\sf Solution$

二维前缀和。

$N\leq100$ 暴力枚举是能过的。

前缀和预处理公式：

$w_{i,j}=w_{i-1,j}+w_{i,j-1}-w_{i-1,j-1}+a_{i,j}$

我们知道有查询$a_{x1,y1}\sim a_{x2,y2}$ 的值的公式：

$res=w_{x2,y2}-w_{x1-1,y2}-w_{x2,y1-1}+w_{x1-1,y1-1}$

所以只要四重循环枚举$x1,x2,y1,y2$ ，计算总和并取最大值就可以啦~

复杂度：$\mathcal{O}(n^4)$

### $\sf Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[301][301],w[301][301],n,sum;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&a[i][j]),w[i][j]+=w[i][j-1]+w[i-1][j]-w[i-1][j-1]+a[i][j];//预处理
	for(int i=1;i<n;++i)
		for(int j=1;j<n;++j)
			for(int k=i+1;k<=n;++k)
				for(int q=j+1;q<=n;++q)
				{
					int res=w[k][q]-w[i-1][q]-w[k][j-1]+w[i-1][j-1];//套用公式
					sum=max(sum,res);//取最大值
				}
	printf("%d\n",sum);
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 思路

看到了 $n\le 100$ 这种这么小的数据范围，就知道，暴力枚举端点是可以通过 $3s$ 的时间的，只要使用前缀和就行了。

**一定要记住二维前缀和的公式！**

### 2 代码与记录

看注释吧。

```cpp
#include<cstdio>//用于输入输出的头文件
using namespace std;//名字空间
const int max_n=100;//数组最大的尺寸
const int min_a=-127;//在数组中最小的数字
int n;//数组尺寸
int a[max_n+2][max_n+2];//数组
int s[max_n+2][max_n+2];//二维前缀和
int ans=min_a;//答案，记得初始化为很小的值
int main(){//main函数
	scanf("%d",&n);//输入尺寸
	for(int i=1;i<=n;++i){//绘制数组
		for(int j=1;j<=n;++j){
			scanf("%d",&a[i][j]);//输入
			s[i][j]=a[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];//计算前缀和，记得公式
		}
	}
	for(int x1=1;x1<=n;++x1){//枚举左上端点，因为n最大只有100，所以不会超过3s
		for(int y1=1;y1<=n;++y1){
			for(int x2=x1;x2<=n;++x2){//枚举右下端点
				for(int y2=y1,sum;y2<=n;++y2){
					sum=s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];//计算矩阵数字之和
					if(ans<sum){//更新答案
						ans=sum;
					}
				}
			}
		}
	}
	printf("%d\n",ans);//输出答案
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51355781)

By **dengziyue**

---

## 作者：ahwhQZY (赞：1)

## UVA108

### 题目大意：

求一个矩阵中子矩阵和的最大值。

~~哇，这不是裸的二位前缀和吗？/kk~~

### 题目分析：
	
   看看数据，数据规模不大，$1 \le n \le 100$ 
   暴力可以过的。
   
   又因为矩阵元素$-127\le num \le 127$
   
   所以要考虑负数情况。
   
   ~~不然就直接累加不就行了吗。~~
   
核心算法：
	
二维前缀和。
   
先解释一下二位前缀和是干嘛的：

在一个矩阵中，通过$O(n^2)$的预处理，在$O(1)$的时间复杂度中求一个子矩阵的和。

递推式（预处理）：

其中 $num[i][j]$ 表示矩阵的第 $i$ 行第 $j$ 列的元素。
   
   $ sum[i][j]=num[i][j]+sum[i][j-1]-sum[i-1][j]+sum[i-1][j-1]$
   
   例如：
   		$\sum\limits_{i=1}^n\sum\limits_{j=1}^mnum[i][j],=sum[n][m]-sum[i-1][m]+sum[i-1][j-1]-sum[n][j-1];$
        
当当当，上 code 
```cpp
#include<bits/stdc++.h>
using namespace std;
int num[101][101];//矩阵元素数组 
int sum[101][101]={0};//前缀和数组 
int n;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			scanf("%d",&num[i][j]);
			sum[i][j]=num[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//前缀和预处理 
		}
	int ans=-2147483647;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int a=i+1;a<=n;a++)
				for (int b=j+1;b<=n;b++)
					ans=max(ans,sum[a][b]-sum[i-1][b]+sum[i-1][j-1]-sum[a][j-1]);//暴力枚举求最大值 
	printf("%d\n",ans); 
}
```


---

## 作者：Mars_Dingdang (赞：1)

由于本题的数据规模极小，用简单的二维前缀和维护，暴力枚举即可。

## 题目大意
有一个 $n\times n$ 的矩阵，元素 $a_{i_j}\in [-127,127]\cap \mathbb Z$，求该元素的最大子矩阵。

 一个子矩阵是任意在总矩阵中大小为 $1
 \times 1$ 或更大的邻近子数组。
 
## 大体思路
正如我在第一行所说，由于本题的数据规模极小，用简单的二维前缀和维护，暴力枚举即可。

好了，思路没了。

那么，本题的关键就是二维前缀和的思想。普通的前缀和是记录某一“线段”上所有数的和，即 $S_k=\sum\limits_{i=1}^k a_i$。因此，区间 $[l,r]$ 的元素和可以由容斥得到：$sum[l,r]=S_{r}-S_{l-1}$。

而推广到二维平面也是一样。如下图所示，用 $S_{i,j}$ 表示矩阵起点（或坐标原点）到点 $(i,j)$（包含）的矩阵内部的元素之和，及下图染色区域的元素之和。由容斥可得：

$$S_{m,n}=\sum_{i=1}^m\sum_{j=1}^na_{i,j}=a_{m,n}+S_{m-1,n}+S_{m,n-1}-S_{m-1,n-1}$$

![](https://cdn.luogu.com.cn/upload/image_hosting/itdrwwxp.png)

在计算 $S_{i,j}$ 的过程中，由几部分组成：本身所代表的元素（绿色），横坐标减一的矩阵和（红色），纵坐标减一的矩阵和（黄色），以及重叠部分（红+黄=橙色）。其中，重叠部分被计算两次，因此减去，即 

$$[m,n]=[m-1,n]\cup [m,n-1]+ a_{m,n}=[m-1,n]+ [m,n-1]+ a_{m,n}-[m-1,n]\cap[m,n-1]$$

然后模拟即可，复杂度近似 $O(n^4)$。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii=aa;ii<=bb;ii++)
#define Rep(ii,aa,bb) for(re int ii=aa;ii>=bb;ii--)
typedef long long ll;
typedef unsigned long long ull;
const int maxn=105;
const int inf=-2e9+7;
namespace IO_ReadWrite{
	#define re register
	#define gg getchar()
	template <typename T>
	inline void read(T &x){
		x=0;re T f=1;re char c=gg;
		while(c>57||c<48){if(c=='-') f=-1;c=gg;}
		while(c>=48&&c<=57){x=(x<<1)+(x<<3)+(c^48);c=gg;}
		x*=f;return;
	}
	inline void ReadChar(char &c){
		c=gg;
		while(!isalpha(c)) c=gg;
	}
	template <typename T>
	inline void write(T x){
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar('0'+x%10);
	}
	template <typename T>
	inline void writeln(T x){write(x);putchar('\n');}
}
using namespace IO_ReadWrite;//快读
int n,a[maxn][maxn],sum[maxn][maxn],ans=-1;
//a是原矩阵，sum是二维前缀和
int main(){
	read(n);
	rep(i,1,n){
		rep(j,1,n){
			read(a[i][j]);//输入
			sum[i][j]=(a[i][j]+sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]);
            //利用容斥计算前缀和
			ans=max(ans,a[i][j]);
		}
	}
	rep(i,1,n-1) {
		rep(j,i,n-1){
			for(re int line=i+1;line<=n;line++) {
				for(re int row=j+1;row<=n;row++){//暴力枚举
					int s=sum[line][row]-sum[i-1][row]-sum[line][j-1]+sum[i-1][j-1];//当前矩阵（思路同上）
					ans=max(ans,s);//取最大子矩阵
				}
			}
		}
	}	
	writeln(ans);//输出+换行
	return 0;
}
```

---

## 作者：WCG2025 (赞：1)

这道题一看就是贪心对吧？（~~我看了二十分钟才理解~~）
那么，再看数据规模
N<=100?
那么n三方算法也能够过。
果断采用矩阵去存他，用前缀和来计算
具体看代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int maps[101][101];
int sum[101][101];
int ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    scanf("%d",&maps[i][j]);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    sum[i][j]=sum[i][j-1]+maps[i][j];//前缀和计算
    for(int fir=1;fir<=n;fir++)
    for(int las=fir;las<=n;las++)//这两步就是在枚举矩阵的列数
    {
        int x=0;
        for(int i=1;i<=n;i++)
        {
        x+=sum[i][las]-sum[i][fir-1];//	这一步是在枚举矩阵的行数
        ans=max(ans,x);//取最大值
        x=max(x,0);//如果x<0 果断变为最小值（这一步加不加无所谓，但是怕遇到有心的出题人把数据全部造成负数，那这一步就不能加)
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
还有，输出千万要换行，UVA的PE（格式错误）会在洛谷上报WA。


---

## 作者：Unnamed114514 (赞：0)

### 前置知识
[二位前缀和](https://blog.csdn.net/qq_34990731/article/details/82807870)，是在矩阵中求的前缀和，常用于最大子矩阵。
### 思路分析
题意显然，求一个矩阵的最大子矩阵。
### 算法思路
首先，一般我们采用的都是前缀和法，即为二维前缀和，$a_{i,j}$ 表示 $(1,1)$ 到 $(i,j)$ 的所有数的和，所以说我们可以用 $O(n^4)$ 的时间求出这道题。
### 具体分析
首先四层循环枚举左上角、左下角、右上角、右下角的位置。，设 l 表示左上，r 表示右上，l1 表示坐下，r1 表示右下，根据容斥原理得，答案为 $a_{l1,r1}-a_{l-1,r1}-a_{l1,r-1}+a_{l-1,r-1}$，最后求出最大值即可。
### AC Code:
```
#include<bits/stdc++.h>
using namespace std;
int n,a[105][105],ans=INT_MIN;//取最大值是赋最小值
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]),a[i][j]+=a[i][j-1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]+=a[i-1][j];
	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++)
			for(int l1=l;l1<=n;l1++)
				for(int r1=r;r1<=n;r1++)
					ans=max(ans,a[l1][r1]-a[l-1][r1]-a[l1][r-1]+a[l-1][r-1]);//套公式
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、粗略思路&前置芝士

本题的数据范围是 $N\le100$，可以使用[二维前缀和](https://blog.csdn.net/qq_34990731/article/details/82807870)去做。

二维前缀和有一个关键数组，命名为 $pre$。其中 $pre[i][j]$ 表示第 $i$ 行第 $j$ 列的二维前缀和。

设 $input[i][j]$ 是题目中的输入矩阵第 $i$ 行第 $j$ 列。

二维前缀和有两个关键公式。

1. 求二维前缀和：计算公式为$pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+input[i][j]$。此步骤可以在输入时去做。
2. 求二维区间和：设左上角端点位于第 $x1$ 行第 $y1$ 列，右上角端点位于第 $x2$ 行第 $y2$ 列，则求出此区间之和的计算公式为 $sum=pre[x2][y2]+pre[x1-1][y1-1]-pre[x2][y1-1]-pre[x1-1][y2]$。

使用二维前缀和之后，每一次查询二维区间和的操作的时间复杂度就降到了 $O(1)$，大大加快了不少。

### 二、具体思路

本题要求一个子矩阵，这个子矩阵中的数之和最大。

那么，我们可以使用 $O(N^2)$ 的时间复杂度进行输入&预处理二维前缀和，然后再使用小于 $O(N^4)$ 的时间复杂度进行枚举，总时间复杂度在最坏情况下（$N=100$）小于 $O(100010000)$，$3s$ 的时间绝对足够。

### 三、完整代码

还是那句话：道路千万条，诚信第一条。直接抄题解，棕名两行泪。

```cpp
#include<cstdio>
using namespace std;
int input[101][101],pre[101][101];//input为输入数组，pre为二维前缀和数组。
int n;
int ans=-999999;//ans一定要设置成很小的值，因为答案有可能为负数，ans的初始值不能为0。
inline int max(int a,int b)//定义max函数求两个数的最大值。
{
	return a>b?a:b;
}
int main()
{
	scanf("%d",&n);//输入n。
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&input[i][j]);//输入矩阵。
			pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+input[i][j];//计算二维前缀和。
		}
	}
	for(int x1=1;x1<=n;x1++)//枚举左上角端点。
	{
		for(int y1=1;y1<=n;y1++)
		{
			for(int x2=x1;x2<=n;x2++)枚举右下角端点。
			{
				for(int y2=y1;y2<=n;y2++)
				{
					ans=max(ans,pre[x2][y2]+pre[x1-1][y1-1]-pre[x2][y1-1]-pre[x1-1][y2]);//计算二维区间和，并与ans取最大值。
				}
			}
		}
	}
	printf("%d\n",ans);//输出。
	return 0;//完结撒花！
}

```

### 四、后记

记录：<https://www.luogu.com.cn/record/51405789>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：Jiyuu_no_Tsubasa (赞：0)

这是一道非常经典矩阵题，

这篇题解将为大家列出 $3$ 种解法。

## 解法 $1$
暴力枚举矩阵的左上角与右下角，

再用 $2$ 维前缀和求和。

时间复杂度 $O(n^4)$，

在 $n\le100$ 的情况下可以通过。

当然，不要觉得我是来水篇幅的，

接下来我将为大家详细介绍 $2$ 维前缀和。

首先，诸位需要了解前缀和是什么东西。

$1$ 维前缀和表示此元素与所有在其之前元素的和，

我们常用前缀和数组储存，实现静态区间求和功能。

![](https://cdn.luogu.com.cn/upload/image_hosting/846ess35.png)

若前缀和数组为 $b$，

则可得递推式：$b(i)<=b(i-1)+a(i)$。

接下来进入 $2$ 维前缀和：

如 $1$ 维定义，

$b(i,j)$ 表示 $(1,1)$ 为左上角，$(i,j)$ 为右下角的矩阵之和。

$b(5,5)$ 表示范围如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/djn80cdj.png)

那么怎么得到它呢？

我们发现：

红色部分就是蓝色部分 $+$ 黄色部分 $-$ 重复的绿色部分 $+$ $(5,5)$ 这个点的和 

![蓝色部分](https://cdn.luogu.com.cn/upload/image_hosting/hsq2fiuy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
![黄色部分](https://cdn.luogu.com.cn/upload/image_hosting/26o0ikws.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
![绿色部分](https://cdn.luogu.com.cn/upload/image_hosting/cgay3bur.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

最终效果是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/g8obusnn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

也就是：

$b(i,j)=b(i-1,j)+b(i,j-1)-b(i-1,j-1)+a(i,j)$。

调用求和时只需要进行如下操作即可：

设矩形左上角为 $(x1,y1)$，右下角为 $(x2,y2)$，

$b(x2,y2)-b(x1-1,y2)-b(x2,y1-1)$ 就可以表示其和。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/cwdot3l9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样，我们就可以写代码了。

```
#include<bits/stdc++.h>
using namespace std;
int b[301][301];
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1,x;j<=n;j++){
            cin>>x;
            b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+x;//预处理
        }
    int ans=INT_MIN;
    for(int x1=1;x1<n;x1++)
        for(int y1=1;y1<n;y1++)
            for(int x2=x1+1;x2<=n;x2++)
                for(int y2=y1+1;y2<=n;y2++)
                    ans=max(ans,b[x2][y2]-b[x1-1][y2]-b[x2][y1-1]+b[x1-1][y1-1]);//调用
    cout<<ans<<endl;
    return 0;
}
```

## 解法 $2$
贪心 $+$ $1$ 维前缀和。

通过枚举将 $2$ 维最大矩阵转化为最大子段和问题。 

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int b[300][300];
int ans=INT_MIN;
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1,x;j<=n;j++){
            cin>>x;
            b[i][j]=b[i][j-1]+x;//预处理
        } 
    for(int i=1;i<=n;i++)
        for(int j=i,x=0;j<=n;j++,x=0) 
            for(int k=1;k<=n;k++)
                x=max(x,0)+(b[k][j]-b[k][i-1]),ans=max(ans,x);//最大子段和 
    cout<<ans<<endl;
	return 0;
}
```

## 解法 $3$
动规 $+$ $1$ 维前缀和。

与贪心做法本质上相同，都是转化为最大子段和问题。

首先声明，这里使用的前缀和为 $1$ 维前缀和。

首先设计状态：$f(i,j,k)$ 表示前 $i$ 行选定 $j$~$k$ 列的最大值。

接下来仿照最大子段和列出状态转移方程：

```
f[i][j][k]=max(f[i-1][j][k],0)+b[i][k]-b[i][j-1]
```
然后问题迎刃而解：

```
#include<bits/stdc++.h>
using namespace std;
int b[300][300];
int f[300][300][300];
int ans=INT_MIN;
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1,x;j<=n;j++){
            cin>>x;
            b[i][j]=b[i][j-1]+x;//预处理
        } 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) 
            for(int k=j;k<=n;k++)
                 f[i][j][k]=max(f[i-1][j][k],0)+b[i][k]-b[i][j-1],ans=max(ans,f[i][j][k]);
                 //转移并记录答案
    cout<<ans<<endl;
    return 0;
}
```

## 完结撒花

---

## 作者：Scrutiny (赞：0)

题意就是求给定一个矩阵，求子矩阵最大和。

题解好像大部分都是 $O(n^4)$ 的。其实 $n=100$ 的数据是可以把 $O(n^4)$ 卡掉的。

我来写篇 $O(n^3)$ 的题解。

记 $num_{i,j}$ 表示第 $i$ 行第 $j$ 列的元素。

考虑前缀和：$cnt_{i,j}$ 表示前 $i$ 行第 $j$ 列的元素之和，即 

$$cnt_{i,j}=\sum\limits_{k=1}^inum_{k,j}$$

于是，$cnt_{i,j}=cnt_{i-1,j}+num_{i,j}$。

我们从 $1\sim n$ 枚举 $i,j$。

对于每组 $(i,j)$，从 $1\sim n$ 枚举 $k$。

记 $a_k$ 表示第 $i\sim j$ 行第 $k$ 列的元素之和，即 

$$a_k=cnt_{j,k}-cnt_{i-1,k}$$

以第 $i,j$ 行为上、下边界，以第 $k$ 列为右边界的子矩阵元素和最大值记为 $b_k$。那么，

$$b_k=\max(a_k,a_k+b_{k-1})$$

于是，对于每组 $(i,j)$，答案为 $\max\{b_k\}$。

最后统计每组 $(i,j)$ 的答案的最大值即可。

Sample Code(C++)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rei register int
const int maxn=107;
int n,m;
int a[maxn],num[maxn][maxn],cnt[maxn][maxn];
int ans;
int work(){
	int res=0;
	for(rei i=1;i<=n;++i){
		a[i]=max(a[i],a[i]+a[i-1]);
		res=max(res,a[i]);
	}
	return res;
}
int main(){
	cin>>n;
	for(rei i=1;i<=n;++i){
		for(rei j=1;j<=n;++j){
			scanf("%d",&num[i][j]);
			cnt[i][j]=cnt[i-1][j]+num[i][j];
		}
	}
	for(rei i=1;i<=n;++i){
		for(rei j=i;j<=n;++j){
			for(rei k=1;k<=n;++k){
				a[k]=cnt[j][k]-cnt[i-1][k];
			}
			ans=max(ans,work());
		}
	}
    printf("%d\n",ans);
	return 0;
}
```






---

## 作者：yoyiETO (赞：0)

为什么都用$O(n^3)$算法?还是我最蒟蒻...

楼下说的都很好,算法性能也比我高,但我觉的我的是最简单易懂的QAQ

还是先看数据范围：$n<=100$，暗示着$O(n^4)$算法。

首先想到的当然是~~简洁但得不了满分~~的**暴力枚举**

实现：开始行->开始列->结束行->结束列->累加->求最大值。

**时间复杂度**:$O(n^6)$ ×

可以用前缀和优化一重循环。

定义$x[i][j]$为第$i$行1到$j$个数的和,则$x[i][j]=x[i][j-1]+a[i][j]$,第$i$行$p$到$q$个数的和==$x[i][q]-x[i][p-1]$;

实现类似：开始行->开始列->结束行->结束列->累加每一行->求最大值。

**时间复杂度**:$O(n^5)$ ×

我的思路:再用一次前缀和¡

定义$y[i][j]$为前$i$行前$j$个数的和,则$y[i][j]=y[i-1][j]+a[i][j]$,$i$到$j$行$k$到$t$列的子矩阵和是~~好像错了~~

错误的原因:无法直接加减得出任意子矩阵。

所以可以把状态定义得强一些:$y[i][j][k]$为前i行j到k个数的和。

方程也很容易得出:$y[i][j][k]=y[i-1][j][k]+x[i][k]-x[i][j-1]$.

于是$i$到$j$行$k$到$t$列的子矩阵和是$y[i][j][t]-y[i][j][k-1]$

**Code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[101][101],x[101][101],y[101][101][101],ans=-9999999; //ans要定义为负数
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    	cin>>a[i][j];
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    	x[i][j]=x[i][j-1]+a[i][j];
    for(int i=1;i<=n;i++)
    for(int j=i;j<=n;j++)
    for(int k=1;k<=n;k++)
    	y[i][j][k]=y[i][j][k-1]+x[k][j]-x[k][i-1];
    for(int i=1;i<=n;i++)
    for(int j=i;j<=n;j++)
    for(int k=1;k<=n;k++)
    for(int t=k;t<=n;t++)//暴力
    	ans=max(ans,y[i][j][t]-y[i][j][k-1]);
    cout<<ans<<"\n";//别忘了换行！！
    return 0;
}
```


---

