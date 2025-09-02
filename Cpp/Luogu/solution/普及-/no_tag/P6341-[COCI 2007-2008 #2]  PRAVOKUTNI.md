# [COCI 2007/2008 #2]  PRAVOKUTNI

## 题目描述

给出平面内的 $n$ 个点，计算有多少不同的直角三角形，满足其顶点均为给出的点。

两个直角三角形不同当且仅当它们存在至少一个顶点不同。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $3\le n\le 1500$，坐标的数值在 $-10^9$ 和 $10^9$ 之间，且不存在任何两个点的坐标相同。
#### 说明

**题目译自 [COCI2007-2008](https://hsin.hr/coci/archive/2007_2008/) [CONTEST #2](https://hsin.hr/coci/archive/2007_2008/contest2_tasks.pdf) *T6  PRAVOKUTNI***。

## 样例 #1

### 输入

```
3
4 2
2 1
1 3```

### 输出

```
1```

## 样例 #2

### 输入

```
4
5 0
2 6
8 6
5 7```

### 输出

```
0```

## 样例 #3

### 输入

```
5
-1 1
-1 0
0 0
1 0
1 1```

### 输出

```
7```

# 题解

## 作者：NDFS (赞：4)

看了一下别人都写的是 $O(n^3)$ 的解法，这里提供一个 $O(n^2\log n)$ 的正解。

$O(n^3)$ 的解法基本上都是直接枚举三个点再根据勾股定理逆定理判断直角三角形，但下面的这种解法是根据斜率判断的。

首先枚举一个点，平移整个坐标系，使这个点落在原点上。具体地说，就是其他点的横纵坐标都分别减去这个点的横纵坐标。然后再判定直角。

现在我们需要找另外两个点与其构成直角三角形，设其为点 $A$ 和 点 $B$，则要使 $AO \perp BO$，所以这两个点一定在相邻的两个象限（正好落在坐标轴上的情况是类似的）。设 $A$、$B$ 分别在第一象限和第二象限（都是一样的证明方法），如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/w9kye8mi.png)

可以发现，当 $AO\perp BO$ 时：

$\because\angle AOB=90^{\circ}=\angle 2+\angle 3$

又 $\because\angle 1+\angle 3=90^{\circ}$

$\therefore\angle 1=\angle 2$

反过来，当 $\angle 1=\angle 2$ 时：

$\because\angle AOB=\angle 2+\angle 3$

又 $\because\angle 1=\angle 2$

$\therefore\angle AOB=\angle 1+\angle 3=90^{\circ}$

$\therefore AO\perp BO$

那要如何判断 $\angle 1=\angle 2$ 呢？将线段 $BO$ 绕点 $O$ 逆时针旋转 $90^{\circ}$ 得到 $OB'$，如果 $\angle 1=\angle 2$ 那么 $OB'$ 会与 $OA$ 重合，所以 $OB'$ 与 $OA$ 斜率相同。

所以解法流程：
1. 枚举作为原点的点，平移其他点，并旋转到第一象限。
2. 按照斜率排序，斜率相同的点都会连成一段。
3. 统计四个象限斜率相同的点，相邻象限点数相乘累加答案

总的时间复杂度 $O(n\times(n\log n+n))$，也就是 $O(n^2\log n)$，可能可以用基数/计数排序优化到 $O(n^2)$。

补充： 排序时要判断 $\frac{y_A}{x_A}$ 与 $\frac{y_B}{x_B}$ 的大小关系，可以交叉相乘，比较 $y_A\times x_B$ 与 $y_B\times x_A$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
struct point
{
	ll x,y;int k;//横纵坐标和象限
}p[1505];
int n,ans=0;
ll x[1505],y[1505];
void swap(int &a,int &b){a=a^b,b=a^b,a=a^b;}
void xz(int t)
{//我写了顺时针旋转，这样方便计算在第几象限，坐标关系可以手推出来
	p[t].k++,swap(p[t].x,p[t].y),p[t].y=-p[t].y;
}
bool cmp(point a,point b)
{//比较斜率，为了避免误差把除法通分换乘法
	return a.y*b.x<b.y*a.x;	
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(j!=i)
			{
				p[j].x=x[j]-x[i],p[j].y=y[j]-y[i],p[j].k=1;
				while(p[j].x<=0||p[j].y<0)xz(j);//一直转到第一象限，可能在坐标轴上所以横坐标等于零也要转
			}
			else p[i]=p[1];//原点不能排序，因为不能除以零，会出问题
		}
		sort(p+2,p+1+n,cmp);
		for(int j=2,k;j<=n;j=k)//从上次结束的地方开始
		{
			int s[4]={0};//统计四个象限
			for(k=j;k<=n;s[p[k].k-1]++,k++)if(p[j].y*p[k].x!=p[k].y*p[j].x)break;//排序后相同的肯定时连续一段，不相同直接break
			for(int i=0;i<=3;i++)ans+=s[i]*s[(i+1)%4];
		}
	}
	printf("%d",ans);
	return 0;
}

```

---

## 作者：zct_sky (赞：2)

### Description:
-----
给你 $n$ 个点，任选 3 点，请问能组成几个直角三角形。	 
### Solution:
-----
暴力枚举，判断每三个点能否组成直角三角形。

可以用勾股定理的逆定理来判断三个点能否组成直角三角形：

若 $a^2+b^2=c^2$，则以 $a,b,c$ 为边的三角形是直角三角形。 
### Code(O2):
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){//快读 
	ll x=0,y=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(ll x){//快输 
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
ll di(ll x,ll y,ll xx,ll yy){//计算距离平方的函数 
	return (x-xx)*(x-xx)+(y-yy)*(y-yy);
}
bool check(ll x,ll y,ll x2,ll y2,ll x3,ll y3){//判断 
	ll xy1=di(x,y,x2,y2),xy2=di(x,y,x3,y3),xy3=di(x2,y2,x3,y3);
	return (xy1+xy2==xy3)||(xy1+xy3==xy2)||(xy2+xy3==xy1);
}
ll x[1510],y[1510],n,ans;
int main(){
    n=read();
    for(ll i=0;i<n;i++)
        x[i]=read(),y[i]=read();
    for(ll i1=0;i1<n-2;i1++)//暴力枚举
        for(ll i2=i1+1;i2<n-1;i2++)
            for(ll i3=i2+1;i3<n;i3++)
                if(check(x[i1],y[i1],x[i2],y[i2],x[i3],y[i3])) ans++;
    write(ans);
    return 0;
}

```

---

## 作者：wyhm (赞：2)

## 思路：
暴力，枚举三个点，计算三条边的长度，再使用勾股定理来判断是否是一个三角形。~~不是正解，但是没有用任何优化过了~~
## 优化：
$1.$预处理每一条边的长度，在需要的时候直接调用。

$2.$在循环的时候，每一重都要从这个数的后面开始。
## 证据:
[证据](https://www.luogu.com.cn/record/36419108)
## 代码：
在我写题解的时候这份代码能过但是以后就不知道了（求大佬们轻喷)
```c
#include <stdio.h>
int read()//读入优化
{
    int a=0,f=1;
    char b=getchar();
    while(b<'0'||b>'9') 
    {
		if(b=='-')
			f=-1;
		b=getchar();
	}
    while(b>='0'&&b<='9')
    {
        a=a*10+b-'0';
        b=getchar();
    }
    return a*f;
}
int main()
{
	long long x[1501],y[1501],s[1501][1501];//横坐标纵坐标和每一条边的长度
	int n=read(),ans=0;//输的入点的个数，答案
	for(int i=1;i<=n;i++)//枚举每一个点
	{
		x[i]=read();//输入横坐标
		y[i]=read();//输入纵坐标
		for(int j=1;j<i;j++)//枚举这之前的点
		{
			s[j][i]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);//计算距离
		}
	}
	for(int i=1;i<=n;i++)//枚举
		for(int j=i+1;j<=n;j++)//枚举
			for(int k=j+1;k<=n;k++)//枚举
				if(s[i][j]+s[i][k]==s[j][k]||s[i][j]+s[j][k]==s[i][k]||s[i][k]+s[j][k]==s[i][j])//如果方案可行
					ans++;//答案加一
	printf("%d",ans);//输出答案
	return 0;//别忘了
} 
```
如果代码过不了可以试试下面的卡常代码~~当然别抄~~
```c
#pragma GCC optimize("O2")
#include <stdio.h>
int read()
{
    int a=0,f=1;
    char b=getchar();
    while(b<'0'||b>'9') 
    {
		if(b=='-')
			f=-1;
		b=getchar();
	}
    while(b>='0'&&b<='9')
    {
        a=a*10+b-'0';
        b=getchar();
    }
    return a*f;
}
int main()
{
	long long x[1501],y[1501],s[1501][1501];
	int n=read(),ans=0;
	for(int i=1;i<=n;i++)
	{
		x[i]=read();
		y[i]=read();
		for(int j=1;j<i;j++)
		{
			s[j][i]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(s[i][j]+s[i][k]==s[j][k]||s[i][j]+s[j][k]==s[i][k]||s[i][k]+s[j][k]==s[i][j])
					ans++;
	printf("%d",ans);
	return 0;
} 
```
谢谢管理审核和大家观赏！

---

## 作者：Gorenstein (赞：1)

这一题的意思就是，给出几个点，求出至少有几组三个点能组成以这三个点为顶点的直角三角形。

首先一开始想的时候并没有想到什么方法来做这道题。于是只好暴力了。

看到数据范围 $3≤n≤1500$ ，发现暴力是珂以通过的。

因此我们输入完之后，暴力枚举每一组三个点，然后判断即可。珂以开一个结构体数组来存储x坐标和y坐标。

时间复杂度大概是 $O(n^3)$ 。

------------

首先是判断。判断一个三角形是不是直角三角形，我用的是勾股定理的逆定理。

如果有两条边的长度的平方之和等于第三条边的平方，那么就是直角三角形。

假设两个点 $(x1,y1),(x2,y2)$ ，算边长的方法就是 $\sqrt{(x1-x2)^2+(y1-y2)^2}$ 。


但是，如果需要算边长，则需要开根号，这样大部分情况就会出现小数点。这个时候判断的时候多半会因为精度损失了，所以把原先是直角三角形的判断成不是。

举个栗子，$\sqrt{3}$、$2$和$\sqrt{7}$。这个时候$\sqrt{3}$和$\sqrt{7}$都是无理数，因此开根号的时候会把这两个数四舍五入掉（毕竟电脑不可能存下无限位小数。。），然后用勾股定理逆定理算的时候根号3的平方加4并不完全等于7。因为有一大串小数四舍五入掉了。。

于是为了避免烦人的小数，计算距离的时候直接算 $(x1-x2)^2+(y1-y2)^2$ 了。此时算出来的是每条边的平方，所以判断的时候看看相加是否等于第三个就行了。

计算边长的平方代码如下：

```cpp
long long jl(long long x1,long long y1,long long x2,long long y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
```

判断是否为直角三角形：

```cpp
bool check(long long x1,long long y1,long long x2,long long y2,long long x3,long long y3)
{
	long long jl1=jl(x1,y1,x2,y2);
	long long jl2=jl(x2,y2,x3,y3);
	long long jl3=jl(x3,y3,x1,y1);
	if(jl1+jl2==jl3||jl1+jl3==jl2||jl2+jl3==jl1)
		return true;
	else return false;
}
```

其次，看这个数据范围，要开 $\texttt {long\ long}$ 。

我第一次就是因为没开 $\texttt {long\ long}$所以WA掉了最后一个点。

------------
最后放上代码（O2）：

```cpp
#include<bits/stdc++.h>
using namespace std;

//用结构体数组来存储x坐标和y坐标 
struct node
{
	long long x,y;
}a[1505];
long long ans,n;

//计算边长的平方 
long long jl(long long x1,long long y1,long long x2,long long y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

//判断是否为直角三角形 
bool check(long long x1,long long y1,long long x2,long long y2,long long x3,long long y3)
{
	long long jl1=jl(x1,y1,x2,y2); 
	long long jl2=jl(x2,y2,x3,y3);
	long long jl3=jl(x3,y3,x1,y1);//三边的平方 
	if(jl1+jl2==jl3||jl1+jl3==jl2||jl2+jl3==jl1)//勾股定理逆定理 
		return true;
	else return false;
}

int main()
{
	cin>>n;
	for(long long i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	for(long long i=1;i<=n;i++)
		for(long long j=i+1;j<=n;j++)
			for(long long k=j+1;k<=n;k++)//暴力枚举 
			{
				bool is=check(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y);//检查是否为直角三角形 
				if(is)ans++;
			}
	cout<<ans;
	return 0;
} 
```

---

## 作者：jxbe6666 (赞：1)

在做这一道题时，我们需要了解一些关于直角三角形的知识。

 $a^2+b^2=c^2$ 
 
这个就是 ↑ 著名的勾股定理。相信各位 dalao 对此肯定是再熟悉不过了。它所代表的就是，直角三角形的高的平方加上底的平方，就会等于斜边的平方。我们也可以从这个定理中反推，是不是直角三角形。

注意在计算距离时，不要开根，不要开根，不要开根。在 OI 中有许多精度损失，只要不开根就不会精度损失，毒瘤的出题人就不会让你 WA 了。

#### 题目思路：
暴力穷举，判断取三个点是否能组成直角三角形。请注意十年 OI 一场空，不开 long long 见祖宗。$O(n^3)$ 的时间复杂度应该要吸氧才能过吧


------------
AC Code:↓
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
const int N = 1505;
int n;
ll ans;//
struct XY
{
    ll x, y;//
} a[N];
inline int read()
{ // 快读
    int number = 0, check = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57)
    {
        check = ch == 45 ? -1 : 1;
        ch = getchar();
    }
    while (ch >= 48 && ch <= 57)
    {
        number = (number << 1) + (number << 3) + (ch ^ 48);
        ch = getchar();
    }
    return number * check;
}
inline void write(ll X)
{ // 快输
    if (X < 0)
    {
        X = ~(X - 1);
        putchar('-');
    }
    if (X > 9)
        write(X / 10);
    putchar(X % 10 + '0');
}
ll dight(ll x1, ll y1, ll x2, ll y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);// 开根号会损失精度
}
bool check(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3)
{
    ll dight1 = dight(x1, y1, x2, y2);
    ll dight2 = dight(x2, y2, x3, y3);
    ll dight3 = dight(x3, y3, x1, y1);
    if (dight1 + dight2 == dight3 || dight1 + dight3 == dight2 || dight2 + dight3 == dight1)
        return 1;
    else
        return 0;//判断三点是否组成直角三角形
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i].x = read();
        a[i].y = read();
    }
    for(int i = 1; i <= n; i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1; k <= n; k++){
                if(check(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y)){//暴力枚举
                    ans++;
                }
            }
        }
    }
    write(ans);
    I AK IOI
}

```


---

## 作者：zxd0801 (赞：0)

本蒟蒻的第一篇题解
# 思路分析

首先，我们要从3个点中确定这个三角形是不是直角三角形，先用勾股定理求出3个边的边长，最后再用一次勾股定理的逆定理，判断它是不是直角三角形。    
本题复杂度是O³，需要开O2优化。
### 温馨提示：不开long long 见祖宗！
不开O2 70分，不开long long 90分（~~作者的惨痛教训~~）
## check函数如下：
```cpp
bool check(long long a,long long b,long long c){
	long long ab,bc,ca;
	ab=(x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]);
	bc=(x[c]-x[b])*(x[c]-x[b])+(y[c]-y[b])*(y[c]-y[b]);
	ca=(x[a]-x[c])*(x[a]-x[c])+(y[a]-y[c])*(y[a]-y[c]);
	if(ab+bc==ca||ab+ca==bc||ca+bc==ab){
		return true;
	}
	return false;
}
```
## 接下来就是暴力枚举，上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x[1505];
long long y[1505]; 
long long n,ans=0;
bool check(long long a,long long b,long long c){
	long long ab,bc,ca;
	ab=(x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]);
	bc=(x[c]-x[b])*(x[c]-x[b])+(y[c]-y[b])*(y[c]-y[b]);
	ca=(x[a]-x[c])*(x[a]-x[c])+(y[a]-y[c])*(y[a]-y[c]);
	if(ab+bc==ca||ab+ca==bc||ca+bc==ab){
		return true;
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=j+1;k<=n;k++){
				if(check(i,j,k)){
					ans++;
				}
			} 
		}
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：a_l_g_d (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6341)

[博客食用更香](https://editor.csdn.net/md/?articleId=119961865)

### Description

> 给出平面内的 n 个点，计算有多少不同的直角三角形，满足其顶点均为给出的点。两个直角三角形不同当且仅当它们存在至少一个顶点不同。

题目意思就是在给出的 n 个点中，任意选 3 个点，且这三个点组成的三角形恰为直角三角形。

输入的第一行为给出的点的数目 n，第 2 到 n+1 行分别为这 n 个点的坐标 x和y，分别是点的 x 坐标和 y 坐标。

### 思路

我们可以通过勾股定理来求出两个点的直线距离，也可以用勾股定理来判断是否是直角三角形。

直角三角形满足：

1. 三角形中有一角的角度为90°

2. 若 $a^2+b^2=c^2$ 的平方，则以a、b、c为边的三角形是以c为斜边的直角三角形（勾股定理的逆定理）。

3. 若一个三角形30°内角所对的边是某一边的一半，那么这个三角形是以这条长边为斜边的直角三角形。

4. 直角三角形中，斜边上的中线等于斜边的一半（即直角三角形的外心位于斜边的中点，外接圆半径 $R=C/2$ ）。该性质称为直角三角形斜边中线定理。

而我们这题用到的是判断 2，即勾股定理逆定理。由于这题的数据好像没有题目所说那么大，所以这种 $ O(n^3) $ 的复杂度应该是能够 AC 的。鄙人太蒻，暂时没有想出别的更好的方法。



### Answer

[Record](https://www.luogu.com.cn/record/57103168)

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
#define for(i,j,n) for(int i=j+1;i<=n;++i)
const int maxn=1510;

ull x[maxn],y[maxn],mp[maxn][maxn];

inline int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}

/*

inline double dist(int i,int j) {
	return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
} 求两点距离的平方 

*/

signed main() {
	
	std::ios::sync_with_stdio(false);
	int n=read(),ans=0;
	
	for(i,0,n) {
		x[i]=read();
		y[i]=read();
		for(j,0,i-1) {
			mp[j][i]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]); //因为计算勾股的时候要平方，所以这里不用求根，下同 ↓ 
			// 或是：mp[j][i]=dist(j,i);
		}
	}
	
	for(i,0,n)
		for(j,i,n)
			for(k,j,n)
				if(mp[i][j]+mp[i][k]==mp[j][k]||mp[i][j]+mp[j][k]==mp[i][k]||mp[i][k]+mp[j][k]==mp[i][j])
					ans++;
					
	printf("%d",ans);
	return 0;
}
```


---

