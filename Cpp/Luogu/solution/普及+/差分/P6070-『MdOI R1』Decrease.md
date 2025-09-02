# 『MdOI R1』Decrease

## 题目描述

给定一个 $n \times n$ 的矩阵，你可以进行若干次操作。

每次操作，你可以将一个 $k \times k$ 的 **连续** 子矩阵里的所有数全都加上 $1$ 或者全都减去 $1$。

初始时，矩阵中有 $m$ 个位置上的数不为 $0$，其它位置上的数均为 $0$。

请你求出至少需要多少次操作，可以将矩形中所有数都变为 $0$。

## 说明/提示

【样例 1 解释】:  

给出的矩阵为：  

```plain
1 1 1 0
1 3 3 2
1 3 3 2
0 2 2 2
```

具体步骤：  

先将以第一行第一列为左上角的连续子矩阵执行 **减 1 操作** 一次；

再将以第二行第二列为左上角的连续子矩阵执行 **减 1 操作** 两次。

总共三次。

```plain
1 1 1 0  0 0 0 0  0 0 0 0  0 0 0 0
1 3 3 2  0 2 2 2  0 1 1 1  0 0 0 0
1 3 3 2  0 2 2 2  0 1 1 1  0 0 0 0
0 2 2 2  0 2 2 2  0 1 1 1  0 0 0 0
```

【样例 2 解释】：  

给出的矩阵为：  

```plain
1 0 0
0 0 0
0 0 0
```

只通过 $2\times 2$ 的连续子矩阵操作不可能使得所有格子上的数都变为 $0$。

【数据范围】   

**本题采用捆绑测试。**

| 子任务编号 |    $n\leq$     | $k\leq$ | 分值 |
| :--------: | :------------: | :-----: | :--: |
|     1      |     $10^3$     |   $1$   |  11  |
|     2      |      $20$      |  $20$   |  14  |
|     3      |     $100$      |  $100$  |  17  |
|     4      |     $10^3$     | $10^3$  |  34  |
|     5      | $5\times 10^3$ | $10^3$  |  24  |

对于所有数据，$1\leq n\leq 5\times 10^3$，$1\leq m\leq \min(n^2,5\times 10^5)$，$1\leq k\leq \min(n,10^3)$，$1\leq x,y\leq n$，每对 $(x,y)$ 至多出现一次，$1 \le |z| \leq 10^9$。

数据保证如果有解，答案不超过 $2^{63}-1$。

---

【提示】

本题读入量较大，建议使用较快的读入方式。  

## 样例 #1

### 输入

```
4 14 3
1 1 1
1 2 1
1 3 1
2 1 1
2 2 3
2 3 3
2 4 2
3 1 1
3 2 3
3 3 3
3 4 2
4 2 2
4 3 2
4 4 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 1 2
1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 5 1
1 1 5
2 2 -3
2 3 -4
3 3 1
4 4 2
```

### 输出

```
15
```

# 题解

## 作者：George1123 (赞：23)

**blog上的题解地址：[题解-\[MdOI2020\] Decrease](https://blog.csdn.net/KonnyWen/article/details/104240310)**

### [\[MdOI2020\] Decrease](https://www.luogu.com.cn/problem/P6070)
今天巨佬团队 $\texttt{luogu}$ 公开赛中的第三题，当时我写了好久才想到暴力做法 $\color{orange}\texttt{42分}$，后来我还很离谱的写了个二维线段树，最终也没做出来。看来我还是太蒻了。

**其实此题的做法是：简单差分**

审题很重要，按照题目描述输入矩阵，题目中也说了，要快读：

```cpp
for(int i=1,x,y,z;i<=m;i++){
	x=d(),y=d(),z=d();
	a[x][y]=z;
}
```
**暴力做法：枚举覆盖正方形的左上角，暴力覆盖。** 代码：

```cpp
int main(){
	n=d(),m=d(),k=d();
	for(int i=1,x,y,z;i<=m;i++){
		x=d(),y=d(),z=d();
		a[x][y]=z;
	}
	for(int i=1;i<=n-k+1;i++)
		for(int j=1;j<=n-k+1;j++)
			if(a[i][j]!=0){
				ans+=abs(a[i][j]);
				int tmp=a[i][j];
				for(int x=i;x<=i+k-1;x++)
					for(int y=j;y<=j+k-1;y++)
						a[x][y]-=tmp;
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]!=0) return puts("-1"),0;
	printf("%lld\n",ans);
	return 0;
}
```
这么蒟蒻的做法，我拿到了 $\color{orange}\texttt{42分}$，可见暴力的重要性。

然后我们发现，修改的区间一定是一个**矩形**，而且是**增减修改**，并且是**统一修改**，就应该想到用**差分**。把每行单独拎出来差分一下，形成差分数组 $cf[][]$：

```cpp
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		cf[i][j]=a[i][j]-a[i][j-1];
```
然后暴力枚举覆盖正方形左上角端点，如果不为零就把整个右下角的 $k\times k$ 矩阵减去左上角端点的数，然后让 $\texttt{ans}$ 加上左上角端点数的绝对值。因为当枚举到一个端点的时候，它同一行左端的端点肯定被清零了，所以到这个端点时这个端点的值就是 $cf[][]$ 了。代码：

```cpp
for(int i=1;i<=n-k+1;i++)
	for(int j=1,num=0;j<=n-k+1;j++){
		num=cf[i][j];
		if(num!=0){
			ans+=abs(num);
			for(int t=i;t<=i+k-1;t++)
				cf[t][j]-=num,cf[t][j+k]+=num; //k*k矩阵修改通过差分优化，时间复杂度为O(n)
		}
	}
```
因为要覆盖的左端点少，所以这样的代码时间复杂度是合理的。

题目中说还有“无法使矩阵中所有数都变为 $0$”的情况，所以最后再 $n\times n$ 暴力扫一遍差分矩阵，如果还有没清零的数，就 $\texttt{puts("-1")}$。代码：

```cpp
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		if(cf[i][j]) return puts("-1"),0;
```
就这么简单，普及难度，可是我比赛时缺没想到。如果你懂了，那么蒟蒻就放代码了：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define lng long long
namespace rd{
    const int L=1<<16;
    char buf[L],*S,*T;
    inline char Gc_(){
        if(S==T){T=(S=buf)+fread(buf,1,L,stdin);
            if(S==T) return EOF;}
        return *S++;
    }
    inline char Gc(){return getchar();}
    inline int d(){
        char c;int f=1,x;
        for(c=Gc();c>'9'||c<'0';c=Gc())
            if(c=='-') f=-1;
        for(x=0;c>='0'&&c<='9';c=Gc())
            x=(x<<1)+(x<<3)+c-'0';
        return x*f;
    }
}using namespace rd;
const int N=5e3+10;
int n,m,k,a[N][N];
lng ans;
int cf[N][N];
int main(){
	n=d(),m=d(),k=d();
	for(int i=1,x,y,z;i<=m;i++){
		x=d(),y=d(),z=d();
		a[x][y]=z;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cf[i][j]=a[i][j]-a[i][j-1];
	for(int i=1;i<=n-k+1;i++)
		for(int j=1,num=0;j<=n-k+1;j++){
			num=cf[i][j];
			if(num!=0){
				ans+=abs(num);
				for(int t=i;t<=i+k-1;t++)
					cf[t][j]-=num,cf[t][j+k]+=num;
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(cf[i][j]) return puts("-1"),0;
	printf("%lld\n",ans);
	return 0;
}
```

**祝大家学习愉快！**

---

## 作者：风急风也清 (赞：10)

众所周知，不开 long long 见祖宗。
***
对于所有的题目，如果不会，都可以用暴力做出，拿到部分分，像这道题，就可以拿到 $17$ ~ $34$ 分。

当然啦，我们要的是满分！

根据题目，你可以将一个 $k\times k$ 的连续子矩阵里的所有数全都加上 $11$ 或者全都减去 $11$。

因此，我们很容易得知这道题可以用二维差分。

那什么是二维差分呢？

如下图所示：
![二维差分](https://img-blog.csdnimg.cn/20200225221053457.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2p1c3RpZGxl,size_16,color_FFFFFF,t_70)

根据二维前缀和表示的是右上角矩形的和，由于差分只涉及前面相邻的数（由一维可以推出），并且由前面范围的数相加得到这个位置的数。

那么类比二维前缀和和一维差分，就可以简单推测出二维差分的公式（可以自行推理一下）。

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,ans;//记得一定要开 long long。
long long a[5005][5005],d[5005][5005];
void f(int x,int y,int c)
{
    if(x+k>n+1 || y+k>n+1)
	{ cout<<"-1"; exit(0); }//特判，这个相当于是题目中说的无法修改完。
    d[x][y]-=c;   //差分大纲。
    d[x+k][y]+=c;
    d[x][y+k]+=c;
    d[x+k][y+k]-=c;
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int x,y,z; scanf("%d%d%d",&x,&y,&z); //读入用 scanf，如果会快排的可以用快排（本人不会）。
		a[x][y]=z;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			d[i][j]=d[i-1][j]+d[i][j-1]-d[i-1][j-1]+d[i][j];//前缀和
			long long t=d[i][j]+a[i][j];
			if(t) { ans+=abs(t); f(i,j,t); }//差分数组中有可能有负数，所以要取它的绝对值。
		}
	}
	cout<<ans;//完美结束~
	return 0;
}
```


---

## 作者：ILLENIUM_DOOR (赞：5)

### 前言

差分大法好！（~~蒟蒻刚刚学完~~）

-----------------------

首先，这道题**毒瘤**的数据范围，就保证了 $\operatorname{O(n^2k^2)}$ 的暴力写法只能拿部分分。

然后，我们看到这一行字：**可以将一个 $k\times k$ 的子矩阵全部加上 $1$ 或者全部减去 $1$**。

这一句话很符合二维差分的思想：**对区间做整体修改**。

首先，对于 $f_{1,1}$，我们如果想对它做修改，就只能对 $f_{n,n}$ 这一个大矩阵进行修改。

然后，对于 $f_{1,2}$，由于我们不能改变 $f_{1,1}$ 的值，所以就只能改动 $f_{1,2}$ 到 $f_{n,n}$ 这个矩阵的值。

以此类推，只要把当前数消为 $0$ 就可以了。

现在就到了关键的问题：怎么修改？

这时候就要应用**二维差分**的思想了。

![](https://cdn.luogu.com.cn/upload/image_hosting/w9g120y7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)




我们如果想对图中红色部分整体减 $1$，则图中蓝色部分也会随之修改，所以蓝色部分整体加 $1$。

然而，蓝色部分又会带来绿色部分多减了 $1$，所以绿色部分加 $1$。

然后，因为对当前点只有左上角的点有影响，所以复原数组就是对当前点做**前缀和**。

最后，**记得开 long long**，读入用 **scanf** (~~蒟蒻不会快读~~)。

还有，当差为负数时，要变成正数，所以要取绝对值。

**AC 代码**
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll d[5010][5010],f[5010][5010];
int n,m,k;
void cf(int x,int y,int c){
	int xx=x+k,yy=y+k;
	if(xx>n+1||yy>n+1){
		cout<<"-1";//特判数组越界
		exit(0);
	}
	d[x][y]-=c;//差分数组 
	d[xx][y]+=c;
	d[x][yy]+=c;
	d[xx][yy]-=c;
}
int main(){
	ll ans=0;
	scanf("%d%d%d",&n,&m,&k);
	while(m--){
		int x,y;
		ll z;
		scanf("%d%d%lld",&x,&y,&z);
		f[x][y]=z;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			d[i][j]+=d[i-1][j]+d[i][j-1]-d[i-1][j-1];//前缀和 
			ll k=d[i][j]+f[i][j];
			if(k){
				ans+=abs(k);//绝对值
				cf(i,j,k);
			}
		}
	printf("%lld",ans);	
	return 0;
}

```

---

## 作者：YellowBean_Elsa (赞：5)

### 出题人的题解我没看懂……

## 于是来发一波我赛时自创的算法

# 二维差分

首先注意到对于$a_{1,1}$，**只有一个矩阵$a_{1,1}-a_{k,k}$可以影响他**，所以必须不停地用这个矩阵直至$a_{1,1}=0$。

那么在这之后，**为了不改变$a_{1,1}$** ，能用于改变$a_{1,2}$的矩阵也只有一个。以此类推，我们一行一行扫过去，发现对每个位置$(i,j)$，为了不影响已经处理好的位置，都只有一个矩阵$a_{i,j}-a_{i+k-1,j+k-1}$能用于改变他。那么就按$a_{1,1}$的处理方法处理他们就行了。

当$i+k-1$或$j+k-1$超出$n$时，要果断puts("-1")然后return 0

时间复杂度$O(n^2k^2)$ 

（虽然跑不满，也只T了两个点，但由于subtask,只有42 MDZZ）

### 如何优化呢？

瓶颈在于每次使用$k*k$矩阵加减时，复杂度都是$O(k^2)$

对于这种类似“区间修改”的东东，很容易想到线段树什么的

然而我很菜，不知道什么能维护二维的数据结构，于是……

### knock the blackboard!!!

对于这种修改比查询耗时的东东，**差分**是个好东西

**差分常常把单点的值转化为前缀值**

而这题我们是一行行扫过去的，前缀值 **（从左上角到当前位置的矩形内的差分值之和）** 也可以$O(1)$求得

具体如何差分：

![如图](https://cdn.luogu.com.cn/upload/image_hosting/7wwlp8o4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样，对于红色覆盖部分，前缀和$+1$，其它部分不变，符合差分原则。

更多细节请见代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e3+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)&&ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x*f;
}int n,m,k,xx,yy;
ll a[N][N],ans;
ll sum[N][N];//为了防止MLE，差分和前缀和要用同一个数组qwq
inline void alter(int x,int y,ll c){
	xx=x+k,yy=y+k;
	if(xx>n+1 || yy>n+1)puts("-1"),exit(0);//矩阵越界特判
	//***差分***
	sum[x][y]-=c;
	sum[x][yy]+=c;sum[xx][y]+=c;
	sum[xx][yy]-=c;
}int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		a[x][y]=(ll)read();
	}for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
			//经典的容斥原理计算二维前缀和 
			ll x=sum[i][j]+a[i][j];//对当前位置需要的修改量 
			if(x)ans+=abs(x),alter(i,j,x);//注意修改次数要取绝对值 
		}
	}printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：BaCO3 (赞：4)

### 前置芝士：

二维前缀和 $sum[i][j]$ 定义为以 $1,1$ 为左上角，$i,j$ 为右下角的矩形的数字和。

二维前缀和的式子：$sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]$ （简单的容斥原理）

还有，前缀和就是差分的逆运算，差分数组的前缀和就是原数组哦。

### 来看这道题

这是一道类似于二维差分的模板题吧。

如果我们想将 $a[i][j]$ 的值变为 $0$，这个操作就会影响以 $i,j$ 为左上角，边长为 $k$ 的正方形。如何记录这次修改呢？这时候我们就可以用二维差分了。

跟二维前缀和类似，如果我们对 $cf[i][j]$ 加上 $1$，从 $a[i][j]$ 到 $a[n][n]$ 都会被加上 $1$，因此我们考虑分别对 $cf[i+k][j]$ 和 $cf[i][j+k]$ 都减去 $1$。但很不幸，从 $a[i+k][j+k]$ 到 $a[n][n]$ 都会被多减去一个 $1$，所以我们需要再把 $cf[i+k][j+k]$ 加 $1$。

综上，我们可以得到二维差分的式子了。
```cpp
（x是我们要给某个区间加上的数）
cf[i][j]+=x;
cf[i+k][j]-=x;
cf[i][j+k]-=x;
cf[i+k][j+k]+=x;
```
那在这道题中，如果一个数不为 $0$，且它所在的位置不能再在右下角画出一个边长为 $k$ 的正方形，那就说明我们无法使矩阵中所有数都变为 $0$ 了，别忘了输出 $-1$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,z,a[5005][5005],cf[5005][5005];
long long ans;

int main(){
	scanf("%d%d%d",&n,&m,&k);
	while(m--){
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=z;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cf[i][j]+=cf[i-1][j]+cf[i][j-1]-cf[i-1][j-1];
			a[i][j]+=cf[i][j];
			if(a[i][j]!=0){
				if(i+k>n+1||j+k>n+1){
					printf("-1");
					return 0;
				}
				cf[i][j]-=a[i][j];
				cf[i+k][j]+=a[i][j];
				cf[i][j+k]+=a[i][j];
				cf[i+k][j+k]-=a[i][j];
				ans+=abs(a[i][j]);//记得加绝对值
			}
		}
	}
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：Hexarhy (赞：3)

### Preface

NOIP 考前复习二维前缀和与差分。

算是基础题。**同时也说明了动手画图很重要。**

### Solution

首先要分析如何做到最优解。观察题目的操作我们知道：

- 在同一个位置进行一加一减的操作是不合算的。

- **$(1,1)$ 位置只有唯一的矩阵可以被覆盖。**

根据第二条，我们只能进行 $|a_{1,1}|$ 次矩阵覆盖来使得这个点为 $0$。

再考虑其它的点，例如 $(1,2)$，发现如果覆盖的矩阵包括了 $(1,1)$ 的话，显然是合算的。而此时能覆盖 $(1,2)$ 的矩阵也就唯一了。

以此类推，每次操作都不能影响到前面的操作，每次的操作也就是唯一的了。我们就这样得到了最优解策略。

如果直接模拟上述过程，时间复杂度是 $O(n^2k^2)$ 的。但是区间加减操作是可以用差分进行简化的。

只会一维差分？那就先对原矩阵的行差分，再**对这个行差分矩阵**进行列差分（相当于一维中的二阶差分？）

其实仔细看图就会发现，只对行差分可以把时间优化到 $O(n^2k)$，再对列差分就可以 $O(n^2)$。

具体地如下图。为了方便，在 $n+1$ 行和 $n+1$ 列设置了 $0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/2kt044q6.png)

那么我们只要根据刚才的策略，进行二维差分即可。若将上图的列差分矩阵记为 $d$，那么具体操作为：

从 $(1,1)$ 枚举到 $(n-k+1,n-k+1)$（矩阵不能出界），答案累加 $|a_{i,j}|$，然后进行二维区间覆盖：

- $a_{i,j}=a_{i,j}-a_{i,j}$
- $a_{i+k,j}=a_{i+k,j}+a_{i,j}$
- $a_{i,j+k}=a_{i,j+k}+a_{i,j}$
- $a_{i+k,j+k}=a_{i+k,j+k}-a_{i,j}$

最后判断一下 $d$ 还不存不存在不为 $0$ 的格子，存在即无解。

### Code

```cpp
void solve(void)
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            d[i][j]=a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1];
    for(int i=1;i<=n-k+1;i++)
        for(int j=1;j<=n-k+1;j++)
        {
            ans+=abs(d[i][j]);
            d[i+k][j]+=d[i][j];
            d[i][j+k]+=d[i][j];
            d[i+k][j+k]-=d[i][j];
            d[i][j]=0;
        }
}
int main()
{
    read(n,m,k);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;read(x,y,z);
        a[x][y]=z;
    }
    solve();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(d[i][j])
            {
                puts("-1");
                return 0;
            }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：未见堇开 (赞：2)

对于本题，显然有这样一个暴力做法：

从上至下，从左至右依次枚举左上角，通过题目所述的操作将左上角变为$0$，并统计操作次数。

暴力做法的时间复杂度为$O(n^{2}k^{2})$。

考虑用二维差分维护上述过程。

设原矩阵为$M$，差分矩阵为$D$，根据二维前缀和的递推公式有$M_{i,j}=M_{i-1,j}+M_{i,j-1}-M_{i-1,j-1}+D_{i,j}$，

移项得$D_{i,j}=M_{i,j}-M_{i-1,j}-M_{i,j-1}+M_{i-1,j-1}$。

若要维护区间修改，只需在$M_{i,j}$改变$\Delta x$时，让$M_{i+k,j+k}$改变$\Delta x$，同时让$M_{i+k,j}$和$M_{i,j+k}$改变$-\Delta x$即可。

时间复杂度$O(n^{2})$。

代码：
```cpp
#include<cstdio>
#define reg register
#define MAXN 5003
using namespace std;

typedef long long ll;

int map[MAXN][MAXN],subm[MAXN][MAXN];
ll ans=0;
int n,k;

inline int iabs(int x)
{return(x>=0?x:-x);}

int main()
{
	int m;
	scanf("%d %d %d",&n,&m,&k);
	while(m--)
	{
		int x,y,val;
		scanf("%d %d %d",&x,&y,&val);
		map[x][y]=val;
	}
	for(reg int i=1;i<=n;i++)
		for(reg int j=1;j<=n;j++)
			subm[i][j]=map[i][j]-map[i-1][j]+map[i-1][j-1]-map[i][j-1];
	for(reg int i=1;i<=n-k+1;i++)
		for(reg int j=1;j<=n-k+1;j++)
		{
			ans+=iabs(subm[i][j]),subm[i+k][j]+=subm[i][j],subm[i+k][j+k]-=subm[i][j],subm[i][j+k]+=subm[i][j];
			subm[i][j]=0;
		}
	for(reg int i=1;i<=n;i++)
		for(reg int j=1;j<=n;j++)
			if(subm[i][j]!=0)
			{
				printf("-1");
				return(0);
			}
	printf("%lld",ans);
	return(0);
}
```

---

## 作者：Durancer (赞：1)

#### 前言

二维的差分看题解里有，但是自己手模了数据自己依旧是不懂，这里介绍一种化$n\times n$ 的二维为 $n$ 个 长度为 $n$ 的一维差分

~~比赛题思维度确实高~~

#### 思路

化二维为一维做，因为操作时一个连续的，所以只要一行的 $k$ 列进行操作了，那么更新一下其他的 $k-1$ 行就可以了

还是按照差分的套路

$$poi[i][j]=a[i][j]-a[i][j-1]$$

预处理一下差分数组

其实可以用一种很形象的定义标志是表示

$poi[i][j]$ 就表示如果 $a[i][j-1]$ 处理完了，那么 $a[i][j]$ 还需要进行多少次操作（注意处理时要有绝对值）

那么就考虑一下修改时的操作

假设当前的位置为$(i,j)$

那么假设当前 $flag=poi[i][j]$

修改后的操作为

$$poi[i][j]-=flag$$


$$poi[i][j+k]+=flag$$

因为这个$k\times k$ 的矩阵已经修改过了

所以在这个矩阵每一行末尾的后一个点，因为修改过了，所以必须要把还需要的操作数加上。

注意上方 $poi[i][j]$ 表示的意义，因为末尾的后一个点并没有经过修改，所以必须要再多上当前修改的操作数

#### 核心代码

```
    for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			poi[i][j]=a[i][j]-a[i][j-1];//预处理差分数组 
	for(int i=1;i<=n-k+1;i++)
		for(int j=1;j<=n-k+1;j++)
        {
			int flag=poi[i][j];
			if(!flag) continue;
			ans+=abs(num);
			for(int head=i;head<=i+k-1;head++)
			{
			    poi[head][j]-=num;
                poi[head][j+k]+=num;
            }
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		    if(poi[i][j])
		    {
		        printf("-1\n");
		        return 0;
            }		
	printf("%lld\n",ans);
```




---

## 作者：Little09 (赞：1)

每次选择一个 $k*k$ 的矩形，显然对于 $(1,1)$ 这个点，只有唯一的矩形选择。那么要是 $(1,1)$ 变成 $0$，也只有唯一的操作。操作后再观察 $(1,2)$，发现只有两个矩形，其中一个刚才已经操作过了，那么这种操作还是唯一的。这样递推下去就可以了。而对于有些放个的矩形都被操作过了，直接判断。

那么怎么维护每个点的值呢？二维线段树也许没有必要，这仅仅一个二维差分就可以解决。因为每次的询问是从 $(1,1)$ 依次到 $(n,n)$ 的，所以对每个要修改的操作差分一次就可以做完这道题了。

记得开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m,k;
ll ans;
const int N=5003;
int a[N][N],b[N][N],s[N][N];
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
    n=read(),m=read(),k=read();
    for (int i=1;i<=m;i++)
    {
    	int x=read(),y=read(),z=read();
    	a[x][y]=z;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			s[i][j]=b[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
			a[i][j]+=s[i][j];
			if (a[i][j]!=0)
			{
				if (i+k-1<=n&&j+k-1<=n) 
				{
					ans+=abs((ll)a[i][j]);
					b[i][j]-=a[i][j],b[i+k][j]+=a[i][j],b[i][j+k]+=a[i][j],b[i+k][j+k]-=a[i][j];
					s[i][j]-=a[i][j],a[i][j]=0;
				}
				else 
				{
					printf("-1");
					return 0;
				}
			}
		}
	}
	cout << ans;
	return 0;
}
```


---

