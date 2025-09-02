# [USACO3.3] 家的范围 Home on the Range

## 题目背景

农民约翰在一片边长是N (2 <= N <= 250)英里的正方形牧场上放牧他的奶牛。(因为一些原因，他的奶牛只在正方形的牧场上吃草。)遗憾的是,他的奶牛已经毁坏一些土地。( 一些1平方英里的正方形)


## 题目描述

农民约翰需要统计那些可以放牧奶牛的正方形牧场(至少是2x2的,在这些较大的正方形中没有一个点是被破坏的，也就是说，所有的点都是“1”)。

你的工作要在被供应的数据组里面统计所有不同的正方形放牧区域(>=2x2)的个数。当然，放牧区域可能是重叠。


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.3


## 样例 #1

### 输入

```
6
101111
001111
111111
001111
101101
111001```

### 输出

```
2 10
3 4
4 1```

# 题解

## 作者：Khan_ (赞：26)

矩阵DP,PJ蒟蒻首次题解（~~老师讲了一遍还是没有听懂，后来想了好久的说~~）。
	
   	用的是老师讲的方法，f[i][j]表示以i,j为右下角所能扩展的最大矩阵大小由于f[i][j]是由f[i-1][j],f[i-1][j-1]和f[i][j-1]决定的，所以方程为f[i][j]=min(f[i-1][j],f[i-1][j-1]),f[i][j-1])
    代码见下：
   ```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAX=300;
const int INF=0X3F3F3F3F;
int n;
char map[MAX][MAX];
int num[MAX*MAX];//用桶排进行存储，num[i]表示第i大的矩阵有num[i]个 
int f[MAX][MAX];//表示以map[i][j]为右下角的矩阵的最大值 
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	cin>>map[i];
	/*---考虑边界情况---*/ 
	for(int i=0;i<n;i++)
	f[i][0]=(map[i][0]=='1');
	for(int j=0;j<n;j++)
	f[0][j]=(map[0][j]=='1');
	/*---全矩阵扫进行DP---*/
	for(int i=1;i<n;i++)
		for(int j=1;j<n;j++)
		if(map[i][j]=='1')//当前这个点不是障碍
		{
			f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1;
			num[f[i][j]]++;
		}
	/*---统计全部个数（实现方式有点像斐波那契数列）---*/
	for(int i=n;i>0;i--)
	num[i-1]+=num[i];
	/*---输出结束---*/
	for(int i=2;i<=n;i++)
	if(num[i])
	cout<<i<<' '<<num[i]<<endl;		 
}
```

---

## 作者：Ricardo_Y_Li (赞：22)

~~并不认为这道题需要使用前缀和操作......~~

这道题的dp思想其实很简单

对于一个边长为$a$且其右下角坐标为$i,j$的正方形来说，满足以下条件即可认为其存在：
- 边长为$a-1$且右下角坐标为$i,j-1;i-1,j;i-1,j-1$的正方形都存在
- 此时的$i,j$点为$1$

这样就很好办了

定义$dp[a][i][j]$表示边长为$a$且右下角坐标为$i,j$的正方形是否存在(存在为$1$反之则$0$)，输入的时候把$map[i][j]$为$1$的点做预处理，使$dp[1][i][j]=1$，然后开三重循环扫一遍就好了，最后每种边长加到一个数组里输出就好
AC代码
```
/*
	Name:Home on the Range 
	Copyright:@Ricardo_Y_Li
	Author: Ricardo_Y_Li
	Date: 13/08/18 11:37
	Description:NULL
*/
#include<cstdio>
#define rr register
#define rep(i,a,b) for(rr int i=a;i<=b;++i)
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
using namespace std;

const int N=260;
int n;
int cnt[N],map[N][N],dp[N][N][N];

inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0' || c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9' && c>='0'){x=x*10+(int)(c-'0');c=getchar();}
	return x*f;
}

int main(){
	n=read();
	rep(i,1,n){
	    char s[251];
	    scanf("%s",s);
	    rep(j,0,n-1){
	        map[i][j+1]=(int)(s[j]-'0');
	        if(map[i][j+1])dp[1][i][j+1]=1;
	    }
	}
	rep(i,2,n)
		rep(j,i,n)
			rep(k,i,n)
				if(dp[i-1][j-1][k] && dp[i-1][j][k-1] && dp[i-1][j-1][k-1] && map[j][k])
					dp[i][j][k]=1,cnt[i]++;
	rep(i,2,n)
		if(cnt[i])printf("%d %d\n",i,cnt[i]);
	return 0;
}
```

---

## 作者：VenusM1nT (赞：19)

作为一名合格的PJ选手（蒟蒻） 在看到这道题时的第一想法只有3个字：

##前缀和！

（好吧我承认我脑回路很奇特）

不过这题前缀和递推肯定是正解之一啦 就是比较难写（貌似DP更难写？？？）

这道题目的输入也要注意，数之间没有空格，所以我使用了读入字符再转换

程序中的操作如下：

- 1.创建前缀和（sum[i][j]代表从1,1到i,j的“1”的数量）

这个只要想一下就知道了，$ sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] $

前提：i>2,j>2

例见图：

     ![](https://cdn.luogu.com.cn/upload/pic/8257.png) 

- 2.枚举边长、正方形左上角的点并计算是否符合条件

这一点的确很烦我知道 但其实多画几个图就能发现规律了

规律：$ area(x1,y1)(x2,y2) = sum[x1-1][y1-1] + sum[x1+k-1][y1+k-1] - sum[x1+k-1][y1-1] - sum[x1-1][y1+k-1] $

其中x1,y1为左上角坐标，x2,y2为右下角坐标，k为边长

注：x2=x1+k-1,y2=y1+k-1

例见图：

     ![](https://cdn.luogu.com.cn/upload/pic/8258.png) 

P.S.手写板用不太惯字写的丑见谅

具体见代码

     
 


```cpp
#include<iostream>
using namespace std;
int n;
int sum[255][255];
int ans[255];
char ch;
int main()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin >> ch;//由于题目输入的特殊性不得不出此计策 
            sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+ch-48;//前缀和部分 
        }
    }
    for(int k=2;k<=n;k++)
    {
        int area=k*k;//计算区间大小 
        for(int i=1;i<=n-k+1;i++)
        {
            for(int j=1;j<=n-k+1;j++)
            {
                if(sum[i-1][j-1]+sum[i+k-1][j+k-1]-sum[i+k-1][j-1]-sum[i-1][j+k-1]==area) ans[k]++;
                //按上述公式计算，并判断是否成立，若成立则在对应边长中+1 
            }
        }
    }
    for(int i=2;i<=250;i++) if(ans[i]>0) cout << i << " " << ans[i] << endl;//如果有符合边长的则输出即可 
    return 0;
}
```

---

## 作者：_ajthreac_ (赞：9)

[P2733 家的范围 Home on the Range](https://www.luogu.com.cn/problem/P2733)
### 题目概述
给出一个$N\times N$的矩阵，其中有一些点不可选，求全部由可选点组成的所有大小的正方形的个数（边长$\ge2 $）
### 解题思路
[~~先宣传下博客~~](https://www.cnblogs.com/juruoajh/)     
爆搜显然是不太好的，我们可以考虑$DP$。         
$DP$必须要有转移方程，于是考虑这样一张图
![](https://cdn.luogu.com.cn/upload/image_hosting/yrldnat3.png)
发现若设$f[i][j]$为点$(i,j)$向左上扩展的最大正方形的边长，则$f[i][j]$只能由$f[i-1][j]$（黄色）、$f[i][j-1]$（蓝色）和$f[i-1][j-1]$（绿色）推来。   
于是可写出状态转移方程：
$$f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1$$ 
$Tips:$     
1.由于每个点处理时只需要左侧和上方的点，我们可以边读边做。    
2.每个大正方形包含了比它小的所有正方形，所以桶排记录时要把所有情况记录上。 
3.读入没有空格，可以用```char```读入。        
$Code:(Don't \ copy!)$
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define rg register 
using namespace std;
inline void Read(int &x){
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>=0&&c<=9){
		x=(x<<3)+(x<<1)+c-48;
	}
	x*=f;
}
int n;
char mp[256][256];//每个格子的情况0/1 
int f[256][256];//dp数组 
int buc[256];//桶排记录每种边长有多少 
int maxa=0;//所有正方形中的最大边长，输出用 
int mian()
{
	Read(n);
	for(rg int i=1;i<=n;i++){
		for(rg int j=1;j<=n;j++){
			scanf("%c",&mp[i][j]);//Tips:3
			if(mp[i][j]=='0')continue;//有障碍就不计算（因为根本取不到） 
			f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+1;
			for(int k=2;k<=f[i][j];k++)buc[k]++;//Tips:2
			maxa=max(maxa,f[i][j]);
		}
	}
	for(int i=2;i<=maxa;i++){//只循环到maxa，减少循环次数 
		if(buc[i]){
			printf("%d %d\n",i,buc[i]);
		}
	}
	retunr 0;
}
```
### 最后的话               
写题解不易，如果我的题解对你有帮助，请点个赞吧！

---

## 作者：Hongse_Fox (赞：5)

[题目链接](https://www.luogu.org/problem/P2733)

# 在进入正题之前先介绍一种高级操作：

看到题目的输入是不是又开始打起了字符串呢？

是不是光在输入的地方就调了几分钟呢？

以后遇到类似的输入就不用担心了！

**scanf("%1d",&orz)** 可以强制只读入一位！！！

这样就可以免去很多麻烦了！

————————————————正文分割线——————————

# 解法一：二位前缀和$(O(n^3))$
我们不难想到，一个合法的正方形，其内部全部都是1，那么这个正方形的面积就恰好等于正方形内的数的和。

换句话说，如果找到一个正方形，里面的和恰好等于它的面积，那么它就是合法的

一个正方形的面积可以之间边长的平方，那么数的和呢？那就要用到二位前缀和了

一开始先用$n^2$搞出前缀和

再用$n^3$方分别枚举变长，左下角的点的横纵坐标,就可以 轻松 解决这道题了

具体实现代码如下：
```cpp
#include<cstdio>
int n,mapp[255][255],qzh[255][255];
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			scanf("%1d",&mapp[i][j]);	//炒鸡方便的读入！！！！！ 
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			qzh[i][j]=qzh[i-1][j]+qzh[i][j-1]-qzh[i-1][j-1]+mapp[i][j];
		}
	}
	for(register int i=2;i<=n;i++){		//枚举边长 
		int ans=0;
		for(register int j=i;j<=n;j++){	//枚举第一个坐标 
			for(register int k=2;k<=n;k++){
				if(qzh[j][k]-qzh[j-i][k]-qzh[j][k-i]+qzh[j-i][k-i]==i*i) ans++;	//找到一个合法的正方形就加加啊 
			}
		}
		if(ans==0) return 0;			//如果当前大小没有正方形了，那么更大也不会有，就直接结束 
		printf("%d %d\n",i,ans);		//输出 
	}
}
```
轻松解决

欸不对怎么跑的比其他人都要慢！！！

身为对于rank特别在意的OIer而言这是极大的侮辱（好吧可能只对于我一个蒟蒻

我们再来想想 $O(n^3)$的指数似乎有点太大了吧

看来得想办法降次

# 解法二：伪·动态规划$(O(n^2))$
既然$n^3$不能跑过去了，对于二维的图，$O(n^2)$基本上是复杂度的下界了

那么如果可以从之前的状态推到当前状态的话，那就可以轻松秒切这道题了 

我们再重新翻看一下题目

我们不难发现如果对于一个点，决定它所能形成的合法正方形大小只有三个因素

![](https://s2.ax1x.com/2019/07/27/eMhHjx.png)

正如这张图的左数第一个所示，假设红色的区域为某个点，蓝色区域是其左上角的点所形成的最大的正方形，绿色的区域为它所能向上拓展的1的数量，黄色为向左拓展数量

那我们就发现，当绿色区域和黄色区域都比蓝色区域要突出的时候，它所形成的最大正方形其实也只是蓝色的加一

而黄色和蓝色比绿色大的时候就就取决于绿色

那我们就可以明白，其实对于一个点，它形成的正方形的最大边长为左上蓝色区域，正上绿色区域，正左黄色区域的最小值加一

那我们就可以事先处理一下绿色和黄色区域，在通过类似dp的东西转移一下，最后就可以切掉了

那么再上一次代码：
```cpp
#include<cstdio>
#include<cctype>
inline int R(){							//快读 
    int r=0;char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
    return r;
}
inline int max(int a,int b){return a>b? a:b;}
inline int min(int a,int b){return a<b? a:b;}
inline int minn(int a,int b,int c){return min(a,b)<c? min(a,b):c;} 
int n,col[255][255];
int f[255][255];						//f[i][j]:第i,j个点可以向右上角拓展的最多个数 
int l[255][255],up[255][255];                                    //l[i][j]:第i,j个点可以向左拓展的最多个数
int size[255];							//size[i]:边长为i的正方形的个数 

inline void init(){
    scanf("%d\n",&n);
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=n;j++){
        	scanf("%1d",&col[i][j]);	//再次安利一波超nb的读入 
        }
    }
}
inline void prepare(){
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=n;j++){
            if(!col[i][j]) continue;
            l[i][j]=l[i][j-1]+1; 		//预处理向上的个数 
            up[i][j]=up[i-1][j]+1;		//预处理向左的个数 
        }
    }
}
inline void workk(){
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=n;j++){
            if(!col[i][j]) continue;	//如果这个点本来就是0那要它还有何用 
            f[i][j]=minn(l[i][j],up[i][j],f[i-1][j-1]+1);//通过式子求出当前所可以形成的最大正方形 
            for(register int k=2;k<=f[i][j];k++) size[k]++;//在最大正方形变长内的所有正方形都可以形成 
        }
    }
}
int main(){
    init();
    prepare();
    workk();
    for(register int i=2;i<=n;i++){
        if(!size[i]) break;			//直到某个大小的正方形不存在，那么更大的也就不可能存在了，那就直接结束吧 
        printf("%d %d\n",i,size[i]);
    }
    return 0;
}
```
当然，也有大佬发现，dp转移方程可以写成$f[i][j]=max(f[i][j-1],f[i-1][j],f[i-1][j-1])$

其实是一样的

因为你取了最小之后和之前的式子是等价的

如果嫌内存太大的读者可以去尝试一下

Finally，感谢阅读
## 真·完结

---

## 作者：Palace (赞：4)

[走你](https://www.luogu.org/problemnew/show/P2733)
## 思路：
本校第二次模拟赛T1，因为自己DP和搜索菜的要命，曾一度绝望，后来急中生智，想用**前缀和**暴力一下，写完之后不再理会，没想到A了……

我们可以先整出前缀和，先枚举正方形可能的边长size，枚举点(i,j)，这样就可以得到(i,j)左上方尺寸为size的正方形，如果这个正方形内的和为size*size ，就说明该正方形内没有坏的地方，是合法的，统计数量。

## 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define N 2018
using namespace std;
int n,ans;
int a[N][N],sum[N][N];
inline int read(){
	char ch;
	bool f=false;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-') f=true;
	int res=ch-48;
	while((ch=getchar())>='0'&&ch<='9')
	res=res*10+ch-48;
	return f?res+1:res; 
}
int main(){
	freopen("home.in","r",stdin);
	freopen("home.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int tmp;
			scanf("%1d",&tmp);//输入算是一个坑吧 
			a[i][j]=tmp;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]+=(sum[i][j-1]+a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]+=sum[i-1][j];//到此就整出了二维前缀和sum 
	for(int size=2;size<=n;size++){
		ans=0;//每个size正方形的数量 
		for(int i=size;i<=n;i++)
			for(int j=size;j<=n;j++)
				if(sum[i][j]-sum[i-size][j]-sum[i][j-size]+sum[i-size][j-size]==size*size)//这般就说明没有损坏，是合法的 
					ans++;
		if(ans!=0)
			printf("%d %d\n",size,ans);
	}
	return 0;
}
```

---

## 作者：账号Plus (赞：3)

# 打到DP！
~~我不喜欢do~~

~~也不喜欢前缀和~~

## 所以我要用





# DFS
废话不多说，贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[255];
char cmp[253][253];
bool check(int x,int y,int k){
    for(int i=x;i<=x+k-1;i++)
        for(int j=y;j<=y+k-1;j++)
            if(cmp[i][j]=='0')return 0;
    return 1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>cmp[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=2;i+k-1<=n&&j+k-1<=n;k++)//暴力
                if(check(i,j,k))
                    a[k]++;
    for(int i=2;i<=250;i++)
        if(a[i])cout<<i<<" "<<a[i]<<endl;
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：2)


这题是dp。

状态定义：f[i][j]为以(i,j)为右下角顶点的正方形的最大边长。

边界：f[i][j]为初始读入的矩阵。

状态转移方程： f[i][j]=min{ f[i-1][j] , f[i][j-1] , f[i-1][j-1] } + 1;所以写出来其实是：如果 f[i-1][j] , f[i][j-1] , f[i-1][j-1]，f[i][j]等于当前求的边长-1，才能组成一个正方形

解析： G[i-1][j] , G[i][j-1] , G[i+1][j+1]分别为(i,j)向上、向左、向左上一格的状况。

```cpp
/*
ID: ylx14274
PROG: range
LANG: C++     
*/
#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int n,i,j,k;
char c;
int f[251][251];
int sum[251];
int main() 
{
    freopen("range.in","r",stdin);
    freopen("range.out","w",stdout); 
    scanf("%d\n",&n);
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
        {
            scanf("%c",&c);//读入 
            if (c=='1') f[i][j]=1;//标记 
        }
        scanf("\n");
    }//f[i][j]表示右下角角顶点为（i,j）的正方形最大边长
    for (k=2;k<=n;k++)//枚举正方形的大小
        for (i=n;i>=1;i--)
            for (j=n;j>=1;j--)
            if (f[i-1][j]+f[i][j-1]+f[i-1][j-1]+f[i][j]==(k-1)*4)
            //其实相当于这四个点都能组成变成为k-1的正方形（都等于k-1） 
            {
                f[i][j]++;//更大的方形 
                sum[k]++;//统计
            } 
    for (i=2;i<=n;i++)
    {
        if (sum[i]!=0)
        {
            printf("%d %d\n",i,sum[i]); 
        }//else break;//否则更大的方形也不会有了 
    }
    return 0;
}
```

---

## 作者：liaohaoping (赞：2)

听[**Lynking大佬**](https://lynking.blog.luogu.org/)说这题是DP，然而蒟蒻只会前缀和（可参考题目：[**P1719** 最大加权矩形](https://www.luogu.org/problemnew/show/P1719)）。

sum[i][j]表示前i行j列1的个数，若a[i][j]表示当前格子是否为1，不难得出 sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j]，可结合下图理解。

![a](https://cdn.luogu.com.cn/upload/pic/17979.png)

然后每次枚举左上角的点(i,j)以及边长k，与上面类似，该形中1的个数为sum[i+k-1][j+k-1]-sum[i-1][j+k-1]-sum[i+k-1][j-1]+sum[i-1][j-1]（注意是i-1与j-1，而不是i,j），若1的个数为k²（即全是1），则答案个数+1。

时间复杂度O(n³)，刚好能过（250³=15625000）。

**代码**

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,w=0;char ch=getchar();
    while(ch<'0'||ch>'9')w|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
int ans[260],sum[260][260];//sum[i][j]表示前i行j列1的个数 
int main()
{
	int n=read();
	for(register int i=1;i<=n;++i)
	{
		for(register int j=1;j<=n;++j)
		{
			char ch;cin>>ch;
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(ch^48);
		}
	}
	for(register int i=1;i<=n;++i)
	{
		for(register int j=1;j<=n;++j)
		{
			int o=n-max(i,j)+1;
			for(register int k=1;k<=o;++k)
			{
				if(sum[i+k-1][j+k-1]-sum[i-1][j+k-1]-sum[i+k-1][j-1]+sum[i-1][j-1]==k*k)++ans[k];//注意是i-1与j-1，而不是i,j
			}
		}
	}
	for(register int i=2;ans[i];++i)printf("%d %d\n",i,ans[i]);
	return 0;
}
```

---

## 作者：MaverickT (赞：1)

1. 题解有说dp的
，但是有一说一
    
 蒟蒻不想dp。。。~~不会~~
     
   所以暴力一波：我们都知道大的正方形里面绝对包含小的正方形，我们一左上角的一个方块举例，2X2的正方形需要四个，记录一下（用vis[x坐标][y坐标][多大的正方形]），然后3X3的正方形就能用四个2X2的正方形找出来

------------
111

111

111

------------


3X3的正方形里面能用四个2X2的正方形将所有3X3的方块包含。
于是可以得到

------------

vis[x][y][m]=true的条件是

vis[x+1][y][m-1]=true

vis[x][y+1][m-1]=true

vis[x+1][y+1][m-1]=true

然后就可以上代码了

目测不需要备注

这题输入用字符串注意一下（~~真特娘坑~~）

```
#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int map[300][300],n,vis[300][300][300],cnt[250],ct=0;
int di[2][4]={{1,0,-1,0},{0,1,0,-1}};
struct a{
	int r,c;
}v[70000];//平方
int dfs(int m){
	int h=0;
	for(int i=1;i<=ct;i++){
		int x=v[i].r,y=v[i].c;
		if(vis[x][y][m-1]==1&&vis[x][y][m-1]==vis[x+1][y][m-1]&&vis[x][y+1][m-1]==vis[x][y][m-1]&&vis[x][y][m-1]==vis[x+1][y+1][m-1]){
		h++;
		vis[x][y][m]=1;
		}
	}
	return h;
}
int main() {
	std::ios::sync_with_stdio(false);
	cin>>n;
	memset(map, -1, sizeof(map));
	memset(cnt, 0, sizeof(cnt));
	memset(vis, 0, sizeof(vis));
	char ch;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			cin>>ch;
			if(ch=='0'){
				map[i][j]=0;
			}
			else map[i][j]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
		if(map[i][j]==1&&map[i+1][j]==1&&map[i][j+1]==1&&map[i+1][j+1]==1){
				cnt[2]++;
				vis[i][j][2]=1;
				ct++;
				v[ct].r=i,v[ct].c=j;
			}	
		}
		//if(cnt[2]!=0)
			cout<<2<<" "<<cnt[2]<<endl;
		for(int i=3;i<=n;i++){
			int h=dfs(i);
			if(h==0){
				return 0;
			}
			else{
				cout<<i<<" "<<h<<endl;
			}
		}
	return 0;
}
```

------------


---

## 作者：Starlight_Glimmer (赞：1)

做完之后看到题解里面很多bfs,dfs,甚至还有dp?

写了一个不知道怎么称呼它的方法，暂且叫他乱搞吧。
用数组a[][]预处理出以当前行作为最底层，这一列从上往下的最长的1的长度。
如果这个格子为0的话，a[i][j]就是0，当然也可以特殊标记一下（比如我就用的-1）
统计答案的时候，就枚举每个非0的格子作为最底层第一个格子依次往右边拓展，记录途中最短的从上往下1的长度。由于是正方形，能构成的正方形的边长为$min(pos-j+1,m)$（见代码）。当纵向延伸的长度大于途中最短的从上往下1的长度时，后面就已经不能再构成正方形了，就可以break掉

当然还可以用单调队列，悬线法什么的做，不过这道题的数据范围是真的小。
```cpp
/*
ID: Starry21
LANG: C++
TASK: range            
*/  
#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
#define N 255
#define ll long long 
#define INF 0x3f3f3f3f
int n;
char s[N][N];
int a[N][N];
int ans[N];
int main()
{
	freopen("range.in","r",stdin);
	freopen("range.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		for(int j=1;j<=n;j++)
			if(s[i][j]=='0') a[i][j]=-1;
	}
	for(int i=1;i<=n;i++)
		if(a[1][i]!=-1) a[1][i]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==-1) continue;
			if(a[i-1][j]==-1) a[i][j]=1;
			else a[i][j]=a[i-1][j]+1;
		}
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%2d ",a[i][j]);
		puts("");
	}*/
	for(int i=2;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]>0)
			{
				int pos=j,m=INF;
				while(a[i][pos]>0)
				{
					m=min(m,a[i][pos]);
					if(pos-j+1>m) break;
					ans[min(m,pos-j+1)]++;
					//if(min(m,pos-j+1)==2) printf("%d %d %d\n",i,j,pos);
					pos++;
				}
			}
	for(int i=2;i<=n;i++)
		if(ans[i]>0)
			printf("%d %d\n",i,ans[i]);
    return 0;
}
```


---

## 作者：周子衡 (赞：1)

思路：动态规划

状态：设$ans[i][j]$表示以单元格$(i,j)$为右下角的最大正方形边长

先分析转移方程：显然，如果以$(i,j)$为右下角存在边长为$x$的正方形，那么必然存在以$(i-1,j-1)$为右下角的边长为$x-1$的正方形且$(i,j)$上面及左边的连续$x-1$个格子都必须是正方形，故可得方程：

$ans[i][j]=min(ans[i-1][j-1]+1,up[i][j],lf[i][j])$

（其中$up[i][j]$、$lf[i][j]$分别代表$(i,j)$上面和左边各有几个可用格）

再分析输出：若$ans[i][j]=x$，则必有以$(i,j)$为右下角、边长分别为$1,2,3,...,x$的正方形各一个，且不存在其他的正方形，统计即可

附上代码：

```cpp
#include<cstdio>

using namespace std;

char c[251][251]={};
int up[251][251]={},lf[251][251]={};
int ans[251][251]={};
int out[251]={};

#define min(a,b)((a)<(b)?(a):(b))

int main()
{
	int n=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf(" %c",&c[i][j]);
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			up[i][j]=c[i][j]=='1'?up[i-1][j]+1:0;
			lf[i][j]=c[i][j]=='1'?lf[i][j-1]+1:0; 
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			ans[i][j]=min(
			ans[i-1][j-1]+1,
			min(up[i][j],lf[i][j]));
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=2;k<=ans[i][j];k++)
			{
				out[k]++;
			}
		}
	}
	
	for(int i=2;out[i];i++)
	{
		printf("%d %d\n",i,out[i]);
	}
	
	return 0;
}
```

---

## 作者：WJCwjc142857 (赞：1)

DP?
不存在的

状态转移方程?

本蒟蒻推不出

其实搜索可以过

读入a[i][j]后先经过一步预处理

使得b[i][j]表示以(1,1),(1,j),(i,1)和(i,j)为顶点的矩形中有几个点为1

所以b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j]

然后接着开始搜索,当搜索到右下角坐标(j,k),边长为i的正方形时,其中包含的点的个数即为:

b[j][k]-b[j-i][k]-b[j][k-i]+b[j-i][k-i]

当其等于i^2时,说明该正方形可以被覆盖

下面贴代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,i,j,k,a[300][300]={0},b[300][300]={0},ans=0,x;
    char c;
    cin >> n;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
        {
            cin >> c;
            a[i][j]=c-'0';
            b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
        }
    }
    for (i=2;i<=n;i++)
    {
        ans=0;
        for (j=i;j<=n;j++)
            for (k=i;k<=n;k++)
            {
                x=b[j][k]-b[j-i][k]-b[j][k-i]+b[j-i][k-i];
                if (x==i*i) ans++;
            }
        if (ans!=0) cout << i << ' ' << ans << endl;
    }
}
```

---

## 作者：约修亚_RK (赞：1)

这题我是用前缀和来写的，微妙地和动规的程序有点像...?

用farm[k][i]来表示前k行i列的数字和，这个在输入的时候就可以处理掉。

具体的处理方式是，输入farm[k][i]之后，farm[k][i] = farm[k][i] + farm[k-1][i] + farm[k][i-1] - farm[k-1][i-1]。

接下来遍历正方形的边长，从2到n；然后遍历正方形左上角的位置，从1到n-k+1（x和y）。显然，每一个小正方形中，如果它的数字和等于边长的平方，就说明这个正方形中的每一格都是1。设这个正方形为(x1, y1)到(x2, y2)，如果farm[x2][y2] + farm[x1-1][y1-1] - farm[x1-1][y2] - farm[x2][y1-1]，则答案累加1。这个画个图很容易就可以明白了。


```cpp
/* P2733
 * Au: SJoshua
 */
#include <cstdio>

int n, farm[251][251];
    
int main(void) {
    scanf("%d", &n);
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            scanf("%1d", &farm[k][i]);
            farm[k][i] += farm[k][i-1];
            farm[k][i] += farm[k-1][i];
            farm[k][i] -= farm[k-1][i-1]; 
        }
    }
    for (int k = 2; k <= n; k++) {
        int size = k*k, ans = 0; 
        for (int i = 1; i+k-1 <= n; i++) {
            for (int j = 1; j+k-1 <= n; j++) {
                if (farm[i+k-1][j+k-1] + farm[i-1][j-1] - farm[i+k-1][j-1] - farm[i-1][j+k-1] == size) {
                    ans++;
                }
            }
        }
        if (ans) {
            printf("%d %d\n", k, ans);
        }
    }
    return 0;
}
```

---

## 作者：Conrad (赞：1)

这是本蒟蒻的第一篇题解！！！

思路：

dp（没什么说的）

矩形dp公式也很容易想到，就是前三个中最小的加上本身一个

详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[300][300];
int n,f[300][300],ans[100000];
int main()
{
	ios::sync_with_stdio(false);
	char c;
	cin>>n;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
		{
			cin>>a[i][j];
			if(i==1) f[1][j]=(a[i][j]=='1');
			if(j==1) f[i][1]=(a[i][j]=='1');
		}
	for(int i=2; i<=n; i++)
		for(int j=2; j<=n; j++)
			if(a[i][j]=='1') f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1,ans[f[i][j]]++;
	for(int i=n; i>=2; i--) ans[i-1]+=ans[i];		//要累加是因为包含了i+1个的正方形，必定包含i个
	for(int i=2; i<=n; i++)
		if(ans[i]) cout<<i<<" "<<ans[i]<<endl;
	return (^o^);
}
```

感谢管理大大的审核！！！

---

## 作者：zjp_shadow (赞：1)

看到别的题解全部都用的dp， 我想想能不能强行枚举搜索呢 。

后来想了想 250^4 就炸了，但是250^3 就行了呢。

- 在强行枚举起点和边长后，怎么快速判断，原来就是两个点之间1的数量为它边长的平方就好了嘛~

- 这里，我们只需要预处理一个累加数组就能很快的计算出来 两点之间1的数量了。

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#define pb push_back
#define F(i,l,r) for(int i=(l);i<=(int)(r);++i)
#define D(i,r,l) for(int i=(r);i>=(int)(l);--i)
#define inf 0x7f7f7f7f
#define N 250
using namespace std;

inline void read(int &x)
{
    char ch;
    ch=getchar();
    while ((ch<'0' || ch>'9') && ch!='-') ch=getchar();
    x=0;
    bool b=0;
    if(ch=='-') b=1;
    else x=ch^'0';
    while ((ch=getchar())>='0' && ch<='9')
      x=(x<<1)+(x<<3)+(ch^'0');
    if(b) x*=-1;
}
int n,m;
int G[N+1][N+1];
int sum[N+1][N+1];
int zs[N+1];

void dfs (int x,int y,int cs)
{
    int x1 = x+cs-1, y1 = y+cs-1;                    //找到正方形另一个顶点的位置
    if (sum[x1][y1] - sum[x1][y-1] - sum[x-1][y1] + sum[x-1][y-1] == cs*cs)   //如果两点之间1的数量等于它边长的平方 就累加并继续向下推进
    {++zs[cs];
    dfs(x,y,cs+1);}
}

int main ()
{
    read (n);
    char str[N+1];
    F (i, 1, n) 
    {cin >> str;
    F (j, 0, n-1)
     G[i][j+1] = str[j] - '0';}
   
   F (i, 1, n)
    F (j, 1, n)
    sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + G[i][j];  //sum[i][j]意思为到i行j列总共有多少个1  至于递推公式可以由容斥原理推出
    
   F (i, 1, n-1)
    F (j, 1, n-1)              //到最后一行和最后一列就没有必要了
     if (G[i][j] == 1) dfs(i,j,2);  //判断一下这个点是不是可用
     
   F (i, 2, n)  if (zs[i]) printf ("%d %d\n",i,zs[i]);   //如果存在就输出边长为i的正方形总数
    return 0;
}
```
PS：看到评测里有些人提交AC的思路和我差不多（和nocow上也差不多。。orz各路大神）  只是看题解没写就动动手来写了下  赚点贡献。。


---

## 作者：YanYou (赞：0)

# P党福利！

~~本PJ蒟蒻的DP实在太差，只好用前缀和暴力水过去。~~


------------


## 下面说正经的
我们发现，矩阵的面积只有250 * 250而已，所以可以枚举每一个点，再枚举边长，看一下整个正方形是否均为 1 。

但是，这样的复杂度高达O(n^4)，显然是过不了的，于是我们想到了：
### 矩阵前缀和
这样，时间复杂度就降低到了O(n^3)，数据可以过。
具体看代码。


代码分割线
___________________

```pascal
var n,i,j,k,t:longint;
    ch:char;
    s,a:array[0..260,0..260] of longint;
    ans:array[0..260] of longint;
begin
  readln(n);
  for i:=1 to n do begin
    for j:=1 to n do begin
      read(ch);
      if ch='1' then a[i,j]:=1;
    end;
    readln;
  end; //读入
  for i:=1 to n do
    for j:=1 to n do s[i,j]:=s[i-1,j]+s[i,j-1]-s[i-1,j-1]+a[i,j];//前缀和
  for i:=1 to n do
    for j:=1 to n do begin  //枚举点
      for k:=2 to n do begin //枚举边长
        if j+k-1>n then break;
        if i+k-1>n then break; //边界判断
        t:=s[i+k-1,j+k-1]-s[i+k-1,j-1]-s[i-1,j+k-1]+s[i-1,j-1];  //是否全是 1
        if t=k*k then inc(ans[k]); //更新答案
      end;
    end;
  for i:=1 to n do if ans[i]>0 then writeln(i,' ',ans[i]); //输出
end.
```
______________

---

## 作者：龟龟我的龟龟 (赞：0)

这道题大佬都说很简单，但是看完大佬们的题解我还木明白dp方程怎么搞，数据预处理我还没看过。。。

经过我一番思索，终于得出了正解。

这道题求正方形数目，于是我们用排除法： 

对于一个矩阵中的（1x1）零点它所影响范围内的（2x2）正方形肯定不选，即，也即为零

比如：

		1 0 1 1 1 1

		0 0 1 1 1 1

		1 1 1 1 1 1

		0 0 1 1 1 1 

		1 0 1 1 0 1 

		1 1 1 0 0 1

对于测试样例的（6x6）矩阵，经过第一次关于（2x2）正方形的变化后会变成（5x5）的矩阵，也可以推出，（i，j）点控制的点为（i-1，j）（i，j-1）（i-1,j-1）

经过变化：

		0 0 1 1 1 

		0 0 1 1 1 

		0 0 1 1 1 

		0 0 1 0 0

		0 0 0 0 0 
        
矩阵中1的点的个数即为所构成（2x2）正方形的个数

然后，（3x3）变换也可以直接由该“经过（2x2）变换的这个矩阵”得到。

附上代码

```cpp
#include<iostream>
#define Max 300
using namespace std;
int main() {
	int n, a[Max][Max]{ 0 },sum = 0;
	cin >> n;
	char c[Max][Max];
	for (int i = 0; i < n; ++i)
		cin >> c[i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			a[i + 1][j + 1] = c[i][j] - '0';
	for (int k = 2; k <= n; ++k) {
		sum = 0;
		for (int i = 1; i <= n - k; ++i) {
			for (int j = 1; j <= n - k; ++j){
				if (!a[i][j]) { a[i - 1][j] = 0; a[i][j - 1] = 0; a[i - 1][j - 1] = 0; }//如果a[i][j]为零，则它控制的三个矩形也为零
		        sum += a[i - 1][j - 1];
			}
		}
		if (！sum) break;
		cout << k << ' ' << sum << endl;
	}
	return 0;
}
```

有修改，不要抄

---

## 作者：_skyline (赞：0)

此题并不很难，但是为了练习（~~水~~）dp，便拿来练手，居然不小心疏忽~~蒟蒻~~了一些所以就来写篇题解了。
首先还是来讲一下思路吧，

状态转移是f[x][y]来表示以（x，y）为右下角的正方形的最大边长，
那么可以~~很明显地~~看出其只与f[x][y-1],f[x-1][y-1],f[x-1][y]有关

  
 

 
 |  |  |  |  |
| :----------- | :----------- | :----------- | :----------- |
|  |  |  |  |
|  |  |  |  |
|  |  |  |  | 

 现在要确定表格最右下角的f[x][y],那么f[x-1][y]=2，f[x][y-1]=2,这时还要确定f[x-1][y-1]等于2才可以判定f[x][y]=3
 
 
------------


```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#include<string>//随便打的，毕竟复赛不能用万能头
using namespace std;
int val[250];
char a[50][50];
int f[50][50];//算是防抄袭？因为一开始开错了，所以没改
int n;
int main(){
	scanf("%d",&n);
	for(int x=1;x<=n;x++){
		scanf("%s",a[x]);
	}
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++){
			if(a[x][y]=='1'){
	     //这里有问题，自己想一想，我警告过l
			f[x][y]=min(min(f[x-1][y],f[x][y-1]),f[x-1][y-1])+1;
			val[f[x][y]]++;
			}
		}
	}
	for(int x=n;x>=2;x--){
		val[x]+=val[x+1];
	}
	for(int x=2;x<=n;x++){
		if(val[x]){
			printf("%d %d\n",x,val[x]);
		}
	}
	return 0;
}
```

---

## 作者：JustinRochester (赞：0)

蛤？这题是前缀和？为什么我是用差分  ~~逃~~

好吧，只算是用差分来优化统计

---

**【分析】**
--

按照题目意思，我们需要对所给定的 $N\times N$ 矩阵求其中边长为 $k\times k,(k \geq 2)$ 的元素全为 $1$ 的子矩阵个数

那么我们这么考虑

对于某个正方形，我们只考虑它的右下角和左上角两个点(因为这两个点已经足以描述这个正方形)

那么，如果以 $(x,y)$ 为右下角的点，可以构成边长为 $k$ 的正方形。那么显然，它也可以构成边长为 $t(1 \leq t \leq k)$ 的正方形 ~~(LRJ:想一想，为什么)~~

那么，根据这个性质，我们如果已知当前访问到的点可构成边长最大为 $k$ 的正方形，那么，我们就相当于在答案上把 $1$~$k$ 全部 $+1$

那么接下来我们讨论如何得知一个点可构成的最大正方形

已知当且仅当当前的点上元素为 $1$ 才可构成正方形

而构成的正方形显然受到三个条件制约：向左能延伸的最大长度，向上能延伸的最大长度，左上方那个点能构成的最大正方形

有人可能不理解第三个制约条件，这边给出一个数据：
```
0 0 1
0 1 1
1 1 1
```

如果只考虑左和上，最右下方的那个点显然是 $3$ ，但实际是 $2$

那么我们可以得到，设 $Dp_{i,j}$ 表示以 $(i,j)$ 为右下角的点，能构成的最大正方形， $L_{i,j}$ 表示以该点向左的最大延伸长度，$U_{i,j}$ 表示该点向上的最大延伸长度

那么可以得出方程 $Dp_{i,j}=min(L_{i,j-1},U_{i-1,j},Dp_{i-1,j-1})+1$

同时还有：

$L_{i,j}=((i,j)==0)?0:(L_{i,j-1}+1)$

$U_{i,j}=((i,j)==0)?0:(U_{i-1,j}+1)$

当然，这里可以用滚动优化空间的，本人就不做讲述了 ~~(虽然本蒟蒻用的是这个方法)~~

---

接下来，关于统计，我们可以用差分

对于计算出的 $Dp_{i,j}$ ，表示最大正方形的边长

那么 $1$~$Dp_{i,j}$ 的答案都应该 $+1$

也就是说，如果我们用 $Ans_i$ 表示边长为 $i$ 的正方形个数

则对 $\forall i\in[2,Dp_{i,j}] $ 都满足 $( Ans_{i}-Ans_{i-1} )$ 不变

而唯一有变的是 $Ans_1$ 和 $Ans_{Dp_{i,j}+1}$ 与前一项的差值，前者 $+1$ ，后者 $-1$

如果我们保存变量 $Cf_i$ 表示 $(Ans_i-Ans_{i-1})$，那么，一旦算出 $Dp_{i,j}$ 不为 $0$

那么，我们直接这么修改： $Cf_1++$ , $Cf_{Dp_{i,j}+1}--$

那统计的时候我们需要的 $Ans_i=\sum_{j=1}^iCf_j$

这个我们可以一边 $O(n)$ 的扫过去，一边算即可

而一旦统计到 $Ans_i==0$  就可以跳出了，因为根据刚刚提出的那个性质，后面一定不会有正方形了

其他的一些细节就看本蒟蒻的代码吧

---

**【代码】**
---

那本蒟蒻就放我 ~~码风极丑的~~ 代码了

```cpp
#include<cstdio>
using namespace std;
#define f(a,b,c) for(register int a=b;a<=c;a++)
#define g(a,b,c) for(register int a=b;a>=c;a--)
#define Max(a,b) ((a>b)?a:b)
#define Min(a,b) ((a<b)?a:b)
typedef long long int ll;
typedef unsigned long long int ull;
const int MAXN=300;
typedef int ar[MAXN];
typedef int mt[MAXN][MAXN];
inline ll read(){
    register ll ans=0;register char c=getchar();register bool neg=0;
    while((c<'0')|(c>'9')) neg^=!(c^'-'),c=getchar();
    while((c>='0')&(c<='9')) ans=(ans<<3)+(ans<<1)+(c^'0'),c=getchar();
    return neg?-ans:ans;
}//前面都是条件反射的结果
int N,Left;
ar Up,Cf;
mt Dp;
void pre(){
	N=read();
	f(i,1,N){
		f(j,1,N){
			char c=getchar();
			while(c!='0'&&c!='1') c=getchar();
			if(c=='1'){
				Dp[i][j]=Min(Dp[i-1][j-1],Min(Left,Up[j]))+1;
				Cf[1]++; Cf[Dp[i][j]+1]--;
				Left++; Up[j]++;
			}
			else Left=0,Up[j]=0;
		}
		Left=0;
	}
}
int main(){
	pre();
	f(i,2,N){
		Cf[i]+=Cf[i-1];
		if(Cf[i]) printf("%d %d\n",i,Cf[i]);
		else return 0;
	}
	return 0;
}
```

---

## 作者：Adove (赞：0)

这题二维ST表可做啊

$ST[i][j][k]$ 维护从$(i,j)$向右下拓展边长为$2^k$的正方形是否全为1

预处理复杂度$O(n^2 \log n)$，遍历查询复杂度$O(n^2)$

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1<<8;

int n;
int log[MAXN];
bool ST[MAXN][MAXN][8];

bool query(int x,int y,int c){return ST[x][y][log[c]]&ST[x+c-(1<<log[c])][y][log[c]]&ST[x][y+c-(1<<log[c])][log[c]]&ST[x+c-(1<<log[c])][y+c-(1<<log[c])][log[c]];}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		log[i]=log[i-1];
		if(i>>log[i]+1) ++log[i];
	}for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			scanf("%1d",&ST[i][j][0]);
		}
	}for(int k=1;k<=log[n];++k){
		for(int i=1;i<=n;++i){
			if(i+(1<<k)-1>n) break;
			for(int j=1;j<=n;++j){
				if(j+(1<<k)-1>n) break;
				ST[i][j][k]=ST[i][j][k-1]&ST[i+(1<<k-1)][j][k-1]&ST[i][j+(1<<k-1)][k-1]&ST[i+(1<<k-1)][j+(1<<k-1)][k-1];
			}
		}
	}for(int k=2;k<=n;++k){
		int sum=0;
		for(int i=1;i<=n-k+1;++i){
			for(int j=1;j<=n-k+1;++j){
				sum+=query(i,j,k);
			}
		}if(!sum) break;
		printf("%d %d\n",k,sum);
	}return 0;
}
```

---

## 作者：Celebrate (赞：0)

这一道题主要靠的是DP，f记录这个点到1,1矩形中有多少个1

想想就可以推出来：f[i][j]=f[i][j-1]+f[i-1][j]-f[i-1][j-1]+t

然后枚举边长和起点：如果1的个数有这么多，就把这种边长的矩形数量+1

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int f[310][310];
int bk[310];
int main()
{
	int i,j,k;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            scanf("%1d",&t);
            f[i][j]=f[i][j-1]+f[i-1][j]-f[i-1][j-1]+t;//记录 
        }
    }
    for(k=2;k<=n;k++)//这样可能有一些浪费 
    {
        int area=k*k;
        for(i=1;i<=n-k+1;i++)
        {
            for(j=1;j<=n-k+1;j++)
            {
                if(f[i-1][j-1]+f[i+k-1][j+k-1]-f[i+k-1][j-1]-f[i-1][j+k-1]==area) bk[k]++;//如果可以的话 
            }
        }
    }
    for(i=2;i<=250;i++) if(bk[i]>0) printf("%d %d\n",i,bk[i]);//只要有就输出 
    return 0;
}
```

---

## 作者：珅肐 (赞：0)

这题其实就是[P1387 最大正方形](https://www.luogu.org/problemnew/show/P1387#sub)最大正方形, 稍微改一改

/还有这题可以在线做的(我看那么多大佬都开了两个二维数组，没必要)
#### 直接上代码：
```cpp
#include<iostream>
using namespace std;
int f[257][257],sum[257];
int N,M,ans;
char c;//个人习惯把所有变量定义在外面
int main()
{
	ios::sync_with_stdio(false);//取消同步
	cin>>N;//输入
	for(int i=1;i<=N;++i)
		for(int j=1;j<=N;++j)
		{
			cin>>c;//输入，因为只用一次，就没必要存起来
			if(c=='1')//因为只有两种字符，这样判断也可以
            {
            f[i][j]=min(min(f[i][j-1],f[i-1][j]),f[i-1][j-1])+1;
            sum[f[i][j]]++;//顺便统计正方形出现的个数
            }
		}	
	for(int i=N;i>=2;--i) sum[i-1]+=sum[i];
    //累加每个正方形，举个例子：如果一个点为3，那么肯定也包括一个2；注意：要从后往前加！（卡了我很久）
	for(int i=2;i<=N;++i)
    	if(sum[i])cout<<i<<" "<<sum[i]<<endl;//如果这个点不为零，就输出
	return 0；//让抄题解的过不了编译
}
```

---

## 作者：asdfghjkl123 (赞：0)

前几天做了创意吃鱼法……感觉和那道题有点像（其实还有一道叫最大正方形，这题更像最大正方形，不过最大正方形我是暴力水过的……）

[p1736创意吃鱼法](https://www.luogu.org/problemnew/show/P1736)
[p1387最大正方形](https://www.luogu.org/problemnew/show/P1387)

对于一个点，可以记录其上有多少个1，其左有多少个1，并根据其左上点的dp值，取min得到当前点为右下节点的最大正方形大小。

具体状转看代码……（代码有点丑，求大佬不要diss……）

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
int n;
char maps[252][252];
int col[252][252];
int lin[252][252];
int  dp[252][252];
int ans[252];
int minn(int a,int b,int c)
{
	return min(a,min(b,c));
}
int add(int i,int j)
{
	for(int a=dp[i][j];a>=2;a--)ans[a]++;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){scanf("\n");for(int j=1;j<=n;j++)scanf("%c",&maps[i][j]),dp[i][j]=maps[i][j]-='0';}
//其实当时没想到这个dp的赋值有没有问题……可能没有吧，因为AC了……
	
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(maps[i][j])
	{
		lin[i][j]=lin[i][j-1]+1;
		col[i][j]=col[i-1][j]+1;
		 dp[i][j]=minn(lin[i][j],col[i][j],dp[i-1][j-1]+1);
	}
	for(int i=2;i<=n;i++)for(int j=2;j<=n;j++)add(i,j);
	for(int i=2;ans[i];i++)printf("%d %d\n",i,ans[i]);
	return 0;
}
```

---

## 作者：z3475 (赞：0)

贡献一发蒟蒻的做法
#### 首先我们来推边长为2的正方形的做法

我们让a[i][j]+=a[i+1][j]+a[i][j+1]+a[i+1][j+1]

那么显然a[i][j]==4时就是一个边长为2的正方形

那么我们再来一下a[i][j]+=a[i+1][j]+a[i][j+1]+a[i+1][j+1]

显然a[i][j]==16时就是一个边长为3的正方形

合理推断

**进行w次a[i][j]+=a[i+1][j]+a[i][j+1]+a[i+1][j+1]的运算之后a[i][j]==4^w的话(i,j)就是边长为w+1的正方形的左上角的点的坐标**

严谨性请自行证明

时间复杂度为O(n^3)

#### 但是我们又想到a[i][j]最大值肯定是4^n

而n最大为250

肯定会炸int/long long

分析一下

我们在推边长为w的正方形的时候必须要a[i][j],a[i+1][j],a[i][j+1],a[i+1][j+1]都必须是4^(w-1)才成立

我们大可在a[i][j]计算完毕时进行判断,是4就赋值为1,不是4就是零

严谨性请自行证明

这样子的话a[i][j]就只有0,1俩种可能

对，对，对a数组可以上bitset优化

还有这题读入有点坑...

```cpp
#include <bits/stdc++.h>

using namespace std;

int gc(){
    while (1){
        char o=getchar();
        if (o=='1') return 1;
        if (o=='0') return 0;
    }
}

int main(){
	register int n;
	scanf("%d\n",&n);
	bitset<256> a[n+2];
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			a[i][j]=gc();
	register int q=2;
	do{
		register int w=0;
		for(register int i=1;i<=n;i++)
			for(register int j=1;j<=n;j++){
				a[i][j]=a[i][j]&a[i][j+1]&a[i+1][j]&a[i+1][j+1];
				w+=a[i][j];
			}
		if (w==0) return 0;
		printf("%d %d\n",q++,w);
	}while(1);
}
```



---

## 作者：chestX_ray (赞：0)

此题正解 dp

f[i][j]的意思是以i，j为正方形右下角的那个点 所得到的最大的正方形的个数

状态转移方程看代码

答案将小的正方形的个数加上大的正方形的个数就ok了

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[255][255];
int n;
char c;
int f[255][255];
int t[255];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            cin>>c;
            if(c=='\n')cin>>c;
            a[i][j]=c-'0';    
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j]){
                f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1;
                t[f[i][j]]++;
        }
    for(int i=n;i>=2;i--)
        t[i-1]+=t[i];
    for(int i=2;i<=n;i++)
        if(t[i])printf("%d %d\n",i,t[i]);
    return 0;
}
```

---

## 作者：玫葵之蝶 (赞：0)

##前面的人为什么要说这是前缀和呢？

在我看来这题就是一个二维DP，加上累积答案后才成了三维的时间复杂度。

f[i][j]代表以i,j结尾的最大正方形的边长，a[i][j]代表矩阵上的值。

状态转移方程：if(a[i][j]==1)f[i][j]=min(f[i-1][j-1],f[i-1][j],f[i][j-1])+1;else f[i][j]=0;

然后，每算出来一个值，就从把从2到f[i][j]的答案都加1.

最后输出。

不过这题有一个坑的地方，就是输入。

希望julao可以来看看我的博客：[blog](http://blog.csdn.net/stone41123)

下面贴代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1000000000
using namespace std;
int n;
int a[251][251];
int f[251][251];
int cnt[251];
int mx=0;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c;
            cin>>c;
            a[i][j]=c-'0';
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]){
                f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+1;
                mx=max(mx,f[i][j]);
                for(int k=2;k<=f[i][j];k++){
                    cnt[k]++;
                }
            }
        }
    }
    for(int i=2;i<=mx;i++){
        printf("%d %d\n",i,cnt[i]);
    }
    return 0;
}
```

---

## 作者：lqzhhh (赞：0)

水题233

时间复杂度n^3

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for (int i=a;i<=b;i++)
#define Rep(i,a,b) for (int i=b;i>=a;i--)
using namespace std;
int n;
int a[300][300],ans[300];
inline ll read()//读入优化
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int main()
{
    n=read();
    For(i,1,n)//读入
    {
        For(j,1,n)
        {
            char ch=getchar();
            while(ch!='0'&&ch!='1')ch=getchar();
            if(ch=='1')a[i][j]=1;
        }
    }
    For(i,2,n)a[1][i]+=a[1][i-1];
    For(i,2,n)a[i][1]+=a[i-1][1];
    For(i,2,n)For(j,2,n)a[i][j]=a[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];//前缀和
    For(i,2,n)//判断可行解
        For(j,2,n)
            For(k,2,min(i,j))
                if(k*k==a[i][j]-a[i-k][j]-a[i][j-k]+a[i-k][j-k])ans[k]++;
    For(i,2,n)
        if(ans[i]>0)cout<<i<<" "<<ans[i]<<endl;
    return 0;
}

```

---

## 作者：Drinkwater (赞：0)

感觉这道题不是很难？？？开始写了一个O（n^4）的暴力，只有85分，后来开始想dp，dp[i][j][k]表示以i，j这个格子长度为k的正方形是否存在

显然，存在的条件是(i,j-1),(i-1,j),(i-1,j-1),的格子长度为k-1的正方形必须存在（纸上模拟即可）

转移方程为dp[i][j][k] = (dp[i][j-1][k-1] && dp[i-1][j][k-1] && dp[i-1][j-1][k-1]);

最后我们把和求一遍就好了

/*************************************************************************

    > Author: Drinkwater-cnyali
    > Created Time: 2017/4/7 19:13:47
************************************************************************/










```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
int map[300][300],n;
char s[300];
int dp[251][251][251],ans[300];
int main()
{
    n = read();
    REP(i,1,n)
    {
        scanf("%s",s+1);
        REP(j,1,strlen(s+1))
            map[i][j] = (s[j] == '1'),dp[i][j][1] = map[i][j];
    }
    REP(i,1,n)
    {
        REP(j,1,n)
        {
            if(i-1 < 1 || j -1 < 1|| !map[i][j])continue;
            REP(k,2,n)
            {
                if(dp[i-1][j][k-1] &&dp[i][j-1][k-1]&&dp[i-1][j-1][k-1])dp[i][j][k]++;
            }
        }
    }
    REP(i,1,n)
    {
        REP(j,1,n)
        {
            REP(k,2,n)
                ans[k] += dp[i][j][k];
        }
    }
    REP(i,2,n){if(ans[i] > 0)cout<<i<<" "<<ans[i]<<endl;}
    return 0;
}

```

---

