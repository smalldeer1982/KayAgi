# Vasya and Magic Matrix

## 题目描述

Vasya has got a magic matrix $ a $ of size $ n \times m $ . The rows of the matrix are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ m $ from left to right. Let $ a_{ij} $ be the element in the intersection of the $ i $ -th row and the $ j $ -th column.

Vasya has also got a chip. Initially, the chip is in the intersection of the $ r $ -th row and the $ c $ -th column (that is, in the element $ a_{rc} $ ). Vasya performs the following process as long as possible: among all elements of the matrix having their value less than the value of the element with the chip in it, Vasya randomly and equiprobably chooses one element and moves his chip to this element.

After moving the chip, he adds to his score the square of the Euclidean distance between these elements (that is, between the element in which the chip is now and the element the chip was moved from). The process ends when there are no elements having their values less than the value of the element with the chip in it.

Euclidean distance between matrix elements with coordinates $ (i_1, j_1) $ and $ (i_2, j_2) $ is equal to $ \sqrt{(i_1-i_2)^2 + (j_1-j_2)^2} $ .

Calculate the expected value of the Vasya's final score.

It can be shown that the answer can be represented as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime integer numbers, and $ Q \not\equiv 0~(mod ~ 998244353) $ . Print the value $ P \cdot Q^{-1} $ modulo $ 998244353 $ .

## 说明/提示

In the first example, Vasya will move his chip exactly once. The expected value of the final score is equal to $ \frac{1^2 + 2^2+ 1^2}{3} = 2 $ .

## 样例 #1

### 输入

```
1 4
1 1 2 1
1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3
1 5 7
2 3 1
1 2
```

### 输出

```
665496238
```

# 题解

## 作者：Durancer (赞：8)

### 前置知识

- DP入门

- 期望

- 前缀和

### 思路

~~纪念自己第一道独立做出来的期望~~。

首先我们观察数据范围，可以发现用 $O(nm)$ 的时间复杂度即可解决问题。

首先题目是说了等概率，那么就可以想象成一个类似于加权平均值的问题了，我们发现转移与位置并无关系，所以我们考虑根据权值关系，化二维为一维来进行求解。

按照权值进行升序排列，设 $f_i$ 表示从第 $i$ 个点出发的期望得分，可以列出一下柿子($\text{tot}$ 表示值小于当前初始点的点的个数)：

$$f_i=\frac{1}{\text{tot}}\sum_{a_i>a_j}(x_i-x_j)^2+(y_i-y_j)^2+f_j$$

把式子拆开可以得到：


$$f_i=\frac{1}{\text{tot}}\sum_{a_i>a_j}x_i^2+x_j^2-2x_ix_j+y_i^2+y_j^2-2y_iy_j+f_j$$

$$f_i=\frac{1}{\text{tot}}\sum_{a_i>a_j}x_i^2+x_j^2+y_i^2+y_j^2-2(y_iy_j+x_ix_j)+f_j$$

然后我们发现这可以非常优秀的用前缀和进行优化！

```cpp
int A[N],Aon[N];//A记录 x^2 的前缀和, Aon 记录 x 的前缀和 
int B[N],Bon[N];//B记录 y^2 的前缀和, Bon 记录 y 的前缀和 
int F[N];//F记录 f^2 的前缀和 
```

然后我们就可以得到：

$$f_i=\frac{1}{\text{tot}}\left( A[\text{tot}]+B[\text{tot}]-2x_iAon[tot]-2y_iBon[\text{tot}]+F[\text{tot}]+x_i^2\times \text{tot}+y_i^2\times \text{tot}\right)$$

然后判断一下到了起点输出即可。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<stack>
#include<cstring>
#include<queue>
#include<algorithm>
#include<map>
#define int long long 
using namespace std; 
const int N=1e6+9;
const int mod=998244353;
struct node{
	int x,y;
	int val;
}a[N];
int f[N];
int n,m;
int A[N],Aon[N];//A记录 x^2 的前缀和, Aon 记录 x 的前缀和 
int B[N],Bon[N];//B记录 y^2 的前缀和, Bon 记录 y 的前缀和 
int F[N];//F记录 f^2 的前缀和 
int s,t;
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
bool cmp(node a,node b)
{
	return a.val<b.val;
}
int quick(int x,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*x%mod;
		x=x*x%mod;
		p>>=1;	
	} 
	return ret;
}
int top;
int Sum[N];
void Prepare()
{
	for(int i=1;i<=top;i++)
		A[i]=(A[i-1]+(a[i].x)*(a[i].x))%mod;
	for(int i=1;i<=top;i++)
		B[i]=(B[i-1]+(a[i].y)*(a[i].y))%mod;
	for(int i=1;i<=top;i++)
		Aon[i]=(Aon[i-1]+a[i].x)%mod;
	for(int i=1;i<=top;i++)
		Bon[i]=(Bon[i-1]+a[i].y)%mod; 
}
void DP(int i,int Num)
{
	int Inv=quick(Num,mod-2);
	f[i]=(f[i]+A[Num])%mod;//小的数的x的平方
	f[i]=(f[i]+B[Num])%mod;//小的数的y的平方
	f[i]=(f[i]-2*Aon[Num]*a[i].x%mod+mod)%mod;//减去x*以前的x的两倍
	f[i]=(f[i]-2*Bon[Num]*a[i].y%mod+mod)%mod;
	f[i]=(f[i]+Num*(a[i].x)*(a[i].x)%mod)%mod;
	f[i]=(f[i]+Num*(a[i].y)*(a[i].y)%mod)%mod; 
	f[i]=(f[i]+Sum[Num])%mod;
	f[i]=f[i]*Inv%mod; 
	Sum[i]=(Sum[i-1]+f[i])%mod;
}
signed main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			a[++top].x=i;
			a[top].y=j;
			a[top].val=read();
		}
	s=read(); t=read();
	sort(a+1,a+1+top,cmp);
	Prepare(); 
	int last=0;
	for(int i=1;i<=top;i++)
	{
		if(a[i].val!=a[i-1].val)
			last=i-1;//更新小的个数
		DP(i,last); 
		if(a[i].x==s and a[i].y==t)
			return printf("%lld\n",f[i]),0;
	}
	return 0;
}
```




---

## 作者：夜猫子驱蚊器 (赞：5)

[题面传送门](http://codeforces.com/contest/1042/problem/E)

~~没事干来划个水~~（喂喂喂，想想你还有多少题没补w(ﾟДﾟ)w

感觉这题顶多蓝啊。。

这题是个非常水的期望DP
我们先按格子从小到大排个序
然后用$f[i]$表示$i$从$i$这个格子出发的期望得分

最小的那些格子的f值显然是0啦
大的格子的f值显然是从比它小的转移来的啦

转移方程大概长这个样子，假设比第$i$个格子小的共有$s$个，$j$是权值比$i$小的那些格子
$$f[i]=\frac{\sum{(f[j]+(x[i]-x[j])^2+(y[i]-y[j])^2))}}{s}$$
但是这样好像并！无！卵！用！因为我们还是要枚举$j$
于是我们可以把上面的式子的分子展开
$$\sum{(f[j]+(x[i]-x[j])^2+(y[i]-y[j])^2))}=\sum{(f[j]+x[i]^2-2x[i]x[j]+x[j]^2+y[i]^2-2y[i]y[j]+y[j]^2)}$$
再化简就是（由于式子较长就只写了关于$x$的部分，$y$同理）
$$s\cdot x[i]^2-2 \cdot x[i] \cdot \sum{x[j]}+\sum{x[j]^2}$$
于是，我们就可以让$sf=\sum{f[j]},sx=\sum{x[j]},sx2=\sum{x[j]^2}$，当然还有$sy$和$sy2$

于是
$$f[i]=\frac{sf+s \cdot x[i]^2-2 \cdot x[i] \cdot sx+sx2+s \cdot y[i]^2-2 \cdot y[i] \cdot sy+sy2}{s}$$
欸，怎么还有个除$s$ ？？？
没事没事，这个一开始线性求逆元预处理一波就好啦O(∩_∩)O

还有一个需要注意的细节是，由于每个格子是由严格小于它的格子转移来的，所以要把权值相同的格子的f值全求完了之后再一起更新$sf,sx$这些变量。
```cpp
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;i++)
#define rf(i,x,y) for(int i=y;i>=x;i--)
#define ll long long
using namespace std;
const int N=1001;
const int p=998244353;
int n,m;
struct data{
	int x,y,c;
}a[N*N];
int x,y;
ll inv[N*N];
ll f[N*N];
ll s,sf,sx,sx2,sy,sy2;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
}

int cmp(const data &q,const data &w){
	return q.c<w.c;
}

void Add(ll &x,ll y){  //手动取模
	x+=y;
	while(x<0) x+=p;
	while(x>=p) x-=p;
}

inline ll sqr(ll x){
	return x*x;
}

int main(){
	read(n);read(m);
	fr(i,1,n) fr(j,1,m){
		read(x);
		a[(i-1)*m+j]=(data){i,j,x};
	}
	read(x);read(y);
	n*=m;
	sort(a+1,a+1+n,cmp);
	inv[1]=1;
	fr(i,2,n) inv[i]=(-p/i*inv[p%i])%p;  //线性求逆元
	a[n+1].c=-1;
	fr(i,1,n){
		if (s){  //可以转移
			Add(f[i],(s*sqr(a[i].x)%p-2*sx*a[i].x%p+sx2)%p);
			Add(f[i],(s*sqr(a[i].y)%p-2*sy*a[i].y%p+sy2)%p);
			Add(f[i],sf);
			f[i]=f[i]*inv[s]%p;
		} else f[i]=0;   //已经是最小的格子了
		if (a[i].x==x&&a[i].y==y){   //算出答案就输出
			cout<<(f[i]+p)%p<<endl;
			exit(0);
		}
		if (a[i].c!=a[i+1].c)   //相同权值的格子全部处理完了就更新
		 for(int j=i;j;j--){
		 	if (a[j].c!=a[i].c) break;
		 	Add(sf,f[j]);
		 	Add(sx,a[j].x);
		 	Add(sx2,sqr(a[j].x));
		 	Add(sy,a[j].y);
		 	Add(sy2,sqr(a[j].y));
		 	s++;
		 }
	}
	return 0;
}
```

最后再厚颜无耻地安利一下自己的[博客](https://blog.csdn.net/ymzqwq)

---

## 作者：Genius_Star (赞：4)

### 思路：

将所有的数字从大到小排序。

很明显期望 DP。

定义 $dp_i$ 表示从第 $i$ 个数出发的期望得分。

状态转移方程为（$T$ 为小于 $a_i$ 的个数）：

$$dp_i = \frac{1}{T}\sum\limits_{j=i+1}^n dp_j + dist_{i,j}$$

$$dp_i = \frac{1}{T}\sum\limits_{j=i+1}^n dp_j + (x_i - x_j)^2 + (y_i - y_j)^2$$

这样直接转移是 $O((NM)^2)$ 的，考虑化简式子。

$$(x_i - x_j)^2 + (y_i - y_j)^2=x_i^2 - 2 \times x_i \times x_j +x_j^2+y_i^2- 2 \times y_i \times y_j + y_j^2$$

$$=x_i^2+x_j^2+y_i^2+y_j^2-2 \times(x_i\times x_j+y_i \times y_j)$$

这里可以根据后缀和求出答案：

定义 $A_i$ 表示 $\sum\limits_{j=i}^n x_j$，$B_i$ 表示 $\sum\limits_{j=i}^n y_j$，$C_i$ 表示 $\sum\limits_{j=i}^n x_j^2$，$D_i$ 表示 $\sum\limits_{j=i}^n y_j^2$，$F_i$ 表示 $\sum\limits_{j=i}^n dp_j$。

之后原式可以转化为：

$$dp_i=\frac{(F_{i+1}+C_{i+1}+D_{i+1}+ T \times (x_i^2+y_i^2))-2 \times (x_i \times A_{i+1} + y_i \times B_{i+1})}{T}$$

时间复杂度为：$O(NM)$。

**注意：因为数字有重复，所以这里的 $i+1$ 这里指的下一个小于 $a_i$ 的数。**

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=1000100,mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,x,y,cnt=0,sum=0;
ll h[N];
ll A[N],B[N],C[N],D[N],F[N];
map<ll,ll> P;
struct Node{
	ll x,y;
	ll data;
	bool operator<(const Node&rhs)const{
		return data>rhs.data;
	}
	ll dist(const Node&rhs)const{
		return ((x-rhs.x)*(x-rhs.x)+(y-rhs.y)*(y-rhs.y))%mod;
	}
}a[N];
ll dp[N];
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
		a[++cnt]={i,j,read()};
	x=read(),y=read();
	for(int i=1;i<=cnt;i++)
	  h[++sum]=a[i].data;
	sort(h+1,h+sum+1);
	sort(a+1,a+cnt+1);
	for(int i=1;i<=cnt;i++)
	  P[a[i].data]=i+1;
	A[cnt]=a[cnt].x;
	B[cnt]=a[cnt].y;
	C[cnt]=(a[cnt].x*a[cnt].x)%mod;
	D[cnt]=(a[cnt].y*a[cnt].y)%mod;
	for(int i=cnt-1;i>=0;i--){
		A[i]=(A[i+1]+a[i].x)%mod;
		B[i]=(B[i+1]+a[i].y)%mod;
		C[i]=(C[i+1]+(a[i].x*a[i].x)%mod)%mod;
		D[i]=(D[i+1]+(a[i].y*a[i].y)%mod)%mod;
	}
	for(int i=(cnt-1);i>=1;i--){
		ll k=lower_bound(h+1,h+sum+1,a[i].data)-(h+1),p=P[a[i].data];
		ll t=qpow(k,mod-2); 
		/*for(int j=p;j<=cnt;j++)
		  dp[i]=((dp[i]+dp[j])%mod+a[i].dist(a[j]))%mod;
		dp[i]=(dp[i]*t)%mod;*/
//		printf("%lld\n",k);
		dp[i]=(F[p]+C[p]+D[p])%mod;
		dp[i]=(dp[i]+(k*(((a[i].x*a[i].x)%mod+(a[i].y*a[i].y)%mod)%mod))%mod)%mod;
		dp[i]=(dp[i]-((2ll*(((a[i].x*A[p])%mod+(a[i].y*B[p])%mod)%mod))%mod)+mod)%mod;
		dp[i]=(dp[i]*t)%mod;
		F[i]=(F[i+1]+dp[i])%mod;
	}
	for(int i=1;i<=cnt;i++){
		if(a[i].x==x&&a[i].y==y){
			printf("%lld\n",dp[i]);
			exit(0);
		}
	}
	return 0;
}
```


---

## 作者：Nicrobot (赞：2)

先对所有点按照权值排序。

倒推，从结束即 $1$ 开始从小到大做，设 $f(i)$ 表示 $i\to 1$ 的得分期望。
   
不妨令 $m$ 为排序后小于 $a_p$ 的第一个位置。容易得到：

$$f(p)=\sum_{i=1}^m \dfrac{1}{m} \left [(x_i-x_p)^2+(y_i-y_p)^2\right ] $$

直接做是 $O(n^2m^2)$ 的。考虑优化。

暴力拆开式子。

$$f(p)=\sum_{i=1}^m \dfrac{1}{m} \left (x_i^2-2x_ix_p+x_p^2+y_i^2-2y_iy_p+y_p^2\right ) $$

$$f(p)= \dfrac{1}{m}\left[m\left(x_p^2+y_p^2\right)-2\left(\sum_{i=1}^mx_i\right)\cdot x_p -2\left(\sum_{i=1}^my_i\right)\cdot y_p+\sum_{i=1}^m\left(x_i^2+y_i^2\right)+\sum_{i=1}^mf(i)\right]$$


前缀和维护 $\sum x_i$，$\sum y_i$，$\sum x_i^2$，$\sum{y_i^2}$ 以及 $\sum f(i)$，即可 $O(1)$ 转移。

时间 $O(nm\log nm )$。

[很丑的 code](https://codeforces.com/contest/1042/submission/233646900)

---

## 作者：ifffer_2137 (赞：1)

啊……算是比较简单的期望题了吧，调都没调直接过了。
### 题意
一个 $n$ 行 $m$ 列的矩阵,每个位置有权值 $a_{i,j}$。

给定一个出发点，每次可以等概率的移动到一个权值小于当前点权值的点（不能移动就停止），同时得分加上两个点之间欧几里得距离的平方，即 $(x_1-x_2)^2+(y_1-y_2)^2$。问得分的期望，对 $998244353$ 取模。
### 分析
期望 DP，一般考虑逆推，这里即从权值小的转移到权值大的。

设计状态，平凡地，令 $f_{i,j}$ 表示以 $(i,j)$ 为起点的期望得分，考虑转移，设有 $cnt$ 个点的权值小于 $a_{i,j}$，则有转移：
$$f_{i,j}=\sum_{a_{x,y}<a_{i,j}}\frac{f_{x,y}+(i-x)^2+(j-y)^2}{cnt}$$
完全平方公式展开，把和 $x$，$y$ 无关的拿到外面，$cnt$ 扔到下面去：
$$f_{i,j}=i^2+j^2+\frac{\sum_{a_{x,y}<a_{i,j}}f_{x,y}-2ix-2jy+x^2+y^2}{cnt}$$
然后我们把所有点排个序，按照权值从小到大转移，只需要维护前缀 $\sum x$，$\sum y$，$\sum x^2+y^2$，$\sum f$ 和 $cnt$ 就可以 $\mathcal O(1)$ 转移了。

最终时间复杂度 $\mathcal O(n^2\log_2n)$，瓶颈在排序。

代码给出一些主要部分，边界可能需要注意一下。
### 代码
```cpp
n=read(),m=read();
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		a[i][j]=read();
		p[++tot]={i,j,a[i][j]};
	}
}
qx=read(),qy=read();
sort(p+1,p+tot+1,cmp);
for(int i=1;i<=tot;i++){
	int j=i;
	while(p[j+1].v==p[i].v) j++;
	if(cnt){
		int inv=pw(cnt,mod-2);
		for(int k=i;k<=j;k++){
			int x=p[k].x,y=p[k].y;
			f[x][y]=x*x+y*y;
			f[x][y]=(f[x][y]-x*sx%mod*inv%mod*2%mod+mod)%mod;
			f[x][y]=(f[x][y]-y*sy%mod*inv%mod*2%mod+mod)%mod;
			f[x][y]=((f[x][y]+sqxy*inv%mod)%mod+pre*inv%mod)%mod;
		}
	}
	for(int k=i;k<=j;k++){
		int x=p[k].x,y=p[k].y;
		sx=(sx+x)%mod,sy=(sy+y)%mod;
		sqxy=(sqxy+x*x+y*y)%mod;
		pre=(pre+f[x][y])%mod;
		cnt++;
	}
	i=j;
}
cout<<(f[qx][qy]+mod)%mod<<endl;
```

---

## 作者：CrTsIr400 (赞：1)

# [Vasya and Magic Matrix](https://www.luogu.com.cn/problem/CF1042E) 题解

## 了解题意

一个 $n$ 行 $m$ 列的矩阵，每个位置有权值 $a_{i,j}(1\le n,m\le 1000)$。

给定一个出发点 $(r,c)$，每次可以**等概率的移动到**一个权值小于当前点权值的点，同时得分加上两个点之间欧几里得距离的平方，问得分的期望。

## 研究探索

乍一看暴力建边似乎没有突破口，因为 $nm$ 是 $10^6$ 级别的。

所以要观察一下**特殊性质**：

1. 在矩阵上面操作。而且得分是欧氏距离的**平方**；

2. 对于同一个值的所有点来说，连向的出点是一样的（只是边权不同）。

观察一下欧氏距离平方和就是 $x$ 的差的平方，和 $y$ 的差的平方 之和。

我们要求的是什么？**总期望得分**。

于是，把矩阵中每个数**拎出来从小到大排序**。

设排完序的点对序列中，$a_i$ 表示这对点对的权值，$x_i,y_i$ 表示这对点对的坐标。

则设 $f[i]$ 为 $i$ 为起点的总期望得分。

观察转移：对于每个 $i$，设 $S={k|a[k]<a[i]}$ 有 $f[i]=(\sum_{j\in S} f[j]+(x_j-x_i)^2+(y_j-y_i)^2)\times |S|^{-1}$（$|S|$ 表示 $S$ 集合的大小）。

分析式子，很可做！$f[j]$ 没有和 $i$ 有关的系数，就可以分离 $i$ 转移了。

于是把 $|S|^{-1}$ 先丢到后面，看下面那部分。

 $\sum_{j\in S}(x_j-x_i)^2+(y_j-y_i)^2$。

也就是 $\sum_{j\in S}x_j^2+x_i^2-2x_ix_j+y_j^2+y_i^2-2y_jy_i$。

就是 $|S|(x_i^2+y_i^2)+\sum_{j\in S}x_j^2+\sum_{j\in S}y_j^2-2x_i\sum_{j\in S}x_j-2y_i\sum_{j\in S}y_j$。

实际程序编写的时候，用四个前缀和数组维护即可。

## 确定算法

在编写程序之前先要想想如下操作：

1. 输入矩阵，并且把矩阵拍扁成为数列。

2. 对数列进行排序。

3. 求 前缀 $x$ 和，$y$ 和，$x$ 平方和，$y$ 平方和。

4. 代入式子，直接求解。

## 程序验证

话不多说，上代码。

```cpp
//此处省略文件头。
//I 为 int 类型，in(x) 为快速读入 x。 
const I mod=998244353,N=1e6+10;
I n,m,ex,ey;
struct nd{I x,y,h;}a[N];
I xs1[N],xs2[N],ys1[N],ys2[N],sf[N],f[N];
I add(I x,I y){x+=y;if(x>=mod)x-=mod;return x;}
template<typename T,typename...Args>I add(T a,T b,Args...args){
	return add(a,add(b,args...));}
template<typename T>I mul(T x,T y){return 1ll*x*y%mod;}
template<typename T,typename...Args>I mul(T a,T b,Args...args){
	return mul(a,mul(b,args...));}
I ksm(I x,I y){I ans=1;
	for(;y;y>>=1,x=mul(x,x))if(y&1)ans=mul(ans,x);
	return ans;}
int main(){
	in(n,m);
	for(I i=1;i<=n;++i)for(I j=1;j<=m;++j)in(a[i*m-m+j].h),a[i*m-m+j].x=i,a[i*m-m+j].y=j;
	sort(a+1,a+n*m+1,[=](nd a,nd b){return a.h<b.h;});
	for(I i=1,x,y;i<=n*m;++i){
		x=a[i].x,y=a[i].y;
		xs1[i]=add(xs1[i-1],x);
		xs2[i]=add(xs2[i-1],mul(x,x));
		ys1[i]=add(ys1[i-1],y);
		ys2[i]=add(ys2[i-1],mul(y,y));}
	for(I i=1,j,iv;i<=n*m;++i){
		iv=ksm(i-1,mod-2);
		for(j=i;j<=n*m&&a[j].h==a[i].h;++j)
			f[j]=mul(iv,
					add(sf[i-1],
						mul(i-1,add(mul(a[j].x,a[j].x),mul(a[j].y,a[j].y))),
						xs2[i-1],
						ys2[i-1],
						mul(mod-2,a[j].x,xs1[i-1]),
						mul(mod-2,a[j].y,ys1[i-1]))
					),
			sf[j]=add(sf[j-1],f[j]);
		i=j-1;}
	in(ex,ey);
	for(I i=1;i<=n*m;++i)if(a[i].x==ex&&a[i].y==ey)printf("%d\n",f[i]);
	return 0;
}

```

---

## 总结

~~意研定证，鉴定为：没有瓶颈。~~

这类题目思维难度并不高，有两个套路：

1.寻找本质相同的转移边.

2.欧式距离平方和的时候，对于多对点对可以拆式子并且分别求和。


---

## 作者：天梦 (赞：1)

# CF1042E 期望 dp

[链接](https://www.luogu.com.cn/problem/CF1042E)

考虑到一个点只能由权值小于它的点转移过来，我们考虑把所有点按照权值排序组成一个序列。

我们设 $f_i$ 表示序列上从第 $i$ 点出发的期望得分是多少。那么我们显然有：
$$
f_{i}=\sum\limits_{a_j<a_i}\frac{(x_j-x_i)^2+(y_j-y_i)^2+f_j}{num}
$$
其中，$num$ 计数的是所有权值小于 $a_i$ 的数。

我们按照权值分组，把权值相同的分成一组，这样，在每一组中的数只能由前面的数转移过来。

我们把分子拆开，可以得到：
$$
x_j^2-2x_ix_j+x_i^2+y_j^2-2y_jy_i+y_i^2+f_j
$$
 显然可以用前缀和维护，可以 $O(1)$ 进行转移。

对于分母的逆元，我们预处理线性求逆元即可。

不过这个题实现宽泛，及时现求也可以过。

代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 1000100
#define M number
using namespace std;

const int INF=0x3f3f3f3f;
const ll mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

struct node{
    int x,y,val;
    inline bool operator < (const node &b) const{
        return val<b.val;
    }
};
node a[N];

int n,m,r,c;
ll num,numx,numy,numx2,numy2;
ll nownum,nownumx,nownumy,nownumx2,nownumy2;
ll sumf,nowsumf;
ll f[N],g[N],ansid,inv[N];

inline ll ksm(ll a,ll b,ll mod){
    ll res=1;
    while(b){
        if(b&1) (res*=a)%=mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int main(){
    read(n);read(m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int now=(i-1)*m+j;
            read(a[now].val);a[now].x=i;a[now].y=j;
        }
    read(r);read(c);
    sort(a+1,a+n*m+1);
    inv[1]=1;for(int i=2;i<=n*m;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<=n*m;i++){
        if(a[i].val!=a[i-1].val){
            num+=nownum;numx+=nownumx;numy+=nownumy;
            numx2+=nownumx2;numy2+=nownumy2;
            nownum=nownumx=nownumy=nownumx2=nownumy2=0;
            sumf+=nowsumf;nowsumf=0;
        }
        f[i]=(num*(a[i].x*a[i].x+a[i].y*a[i].y)%mod+numx2+numy2-2*a[i].x*numx%mod-2*a[i].y*numy%mod+sumf)%mod*inv[num]%mod;
        nownum++;nownumx+=a[i].x;nownumy+=a[i].y;nownumx2+=a[i].x*a[i].x;nownumy2+=a[i].y*a[i].y;nowsumf+=f[i];
        nownumx%=mod;nownumy%=mod;nownumx2%=mod;nownumy2%=mod;nowsumf%=mod;
        if(a[i].x==r&&a[i].y==c){ansid=i;break;}
    }
    printf("%lld\n",f[ansid]);
    return 0;
}
```



---

## 作者：Weng_Weijie (赞：1)

题解：

不难得到转移方程

$$f[i]=\frac{1}{m}\sum_{a_j<a_i}f[j]+(x_i-x_j)^2+(y_i-y_j)^2$$

m 表示权值比 i 小的格子数量

然后将每个格子按权值排序，前缀和优化dp即可

注意要将平方项拆开，便于计算

代码：
```cpp
#include <cstdio>
#include <algorithm>
#define N 1000005
int n, m, sumx, sumy, sump, dp[N], sumdp, x, y, tot;
struct point { int x, y, val; } p[N];
const int mod = 998244353;
void up(int &x, int y) { if ((x += y) >= mod) x -= mod; }
using LL = long long;
int pow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = static_cast<LL> (x) * x % mod)
        if (y & 1) ans = static_cast<LL> (ans) * x % mod;
    return ans;
}
int main() {
    std::scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::scanf("%d", &p[++tot].val), p[tot].x = i, p[tot].y = j;
    std::scanf("%d%d", &x, &y);
    std::sort(p + 1, p + tot + 1, [] (point A, point B) { return A.val < B.val; });
    for (int i = 1, l = 1; i <= tot; i++) {
        dp[i] = 0;
        if (p[i].val != p[l].val)
            for (; l < i; l++) up(sumx, p[l].x), up(sumy, p[l].y), up(sump, p[l].x * p[l].x + p[l].y * p[l].y), up(sumdp, dp[l]);
        int n = l - 1;
        up(dp[i], static_cast<LL> (n) * (p[i].x * p[i].x + p[i].y * p[i].y) % mod);
        up(dp[i], mod - 2 * (static_cast<LL> (p[i].x) * sumx % mod + static_cast<LL> (p[i].y) * sumy % mod) % mod);
        up(dp[i], (sump + sumdp) % mod);
        dp[i] = static_cast<LL> (dp[i]) * pow(n, mod - 2) % mod;
        if (p[i].x == x && p[i].y == y) {
            std::printf("%d\n", dp[i]);
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

考虑一条路径是单调递减的，用离散化后的权值做下标利于转移。

所以定义 $f_i$ 表示从 $i$ 点出发的最大价值，不难得到方程 $f_i=\frac{1}{i-1}\sum_{j=1}^{i-1} f_j+(x_j-x_i)^2+(y_j-y_i)^2$，时间复杂度为 $O(n^4)$。

考虑到形如 $(A-B)^2$ 不能优化，不妨展开为 $A^2+B^2-2\times A\times B$，那么原式即为 $f_i=\frac{1}{i-1}\sum_{j=1}^{i-1} (f_j+{x_j}^2+{x_i}^2+{y_j}^2+{y_i}^2-2\times x_i\times x_j-2\times y_i\times y_j)$，将 $x_i,y_i$ 提出来即为 $f_i=\frac{1}{i-1} \times \{({x_i}^2+{y_i}^2) \times (i-1)-2\times x_i \times \sum_{j=1}^{i-1} x_j-2\times y_i-\sum_{j=1}^{i-1} y_j+\sum_{j=1}^{i-1}(f_j+{x_j}^2+{y_j}^2) \}$。

接下来令 $X_i=\sum_{j=1}^{i}x_j$，$Y_i=\sum_{j=i}^{i}y_j$，$g_i=\sum_{j=1}^{i} (f_j+{x_j}^2+{y_j}^2)$。

最后式子即为 $f_i=\frac{1}{i-1} \times \{{(x_i}^2+{y_i}^2) \times (i-1)-2\times(x_i \times X_{i-1}+y_i \times Y_{i-1})+g_{i-1}\}$，时间复杂度为 $O(n^2)$。虽然看着麻烦，但是写起来很简单，把公式套上去即可。

---

## 作者：codecode (赞：0)

今年学校模拟赛考了这题，然而当时我写的代码~~又臭又长~~几乎无法调错，导致三分钟的思路三小时都没有调出来。。。

参考楼下大佬的写法，代码简短了许多。


------------

#### 题解：

看到题面，一个自然的思路是用 $f(x,y)$ 表示从 $(x,y)$ 出发期望的得分，那么有明显的递推式 

$$f(x,y)=\frac{\sum\limits_{a_{z,w}<a_{x,y}}\left(f(z,w)+(x-z)^2+(y-w)^2\right)}{\sum\limits_{a_{z,w}<a_{x,y}}^{}1}$$

上式的含义即从 $(x,y)$ 到 $(z,w)$ 的得分加上从 $(z,w)$ 出发的期望得分。

但是，上式中对所有 $a_{z,w}<a_{x,y}$ 的 $(z,w)$ 统计的复杂度是 $O(nm)$ 的，这将导致总时间复杂度为 $O(n^2m^2)$，无法通过此题。

事实上，我们没有必要逐项累加，可以将各项分开，并预处理前缀和。

如果记 $\mathcal{A}=\mathcal{A}(x,y)=\{(z,w)|a_{z,w}<a_{x,y}\}$，则完全可以在按 $a_{x,y}$ 排序后 $O(1)$ 递推下列各式

- $|\mathcal{A}|$，$\sum\limits_{P\in\mathcal{A}}f(P)$；

- $\sum\limits_{P\in\mathcal{A}}P_x$，$\sum\limits_{P\in\mathcal{A}}P_x^2$；

- $\sum\limits_{P\in\mathcal{A}}P_y$，$\sum\limits_{P\in\mathcal{A}}P_y^2$。

而原递推式可以将平方拆开，得到

$$f(x,y)=\frac{\sum\limits_{P\in\mathcal{A}}f(P)+\sum\limits_{P\in\mathcal{A}}P_x^2-2x\sum\limits_{P\in\mathcal{A}}P_x+x^2|\mathcal{A}|+\sum\limits_{P\in\mathcal{A}}P_y^2-2y\sum\limits_{P\in\mathcal{A}}P_y+y^2|\mathcal{A}|}{|\mathcal{A}|}$$

维护以上六个变量即可 $O(1)$ 求出分子，而分母总有 $|\mathcal{A}|<mn$，可以预处理逆元，总时间复杂度降到 $O(mn)$。


------------

#### 代码：

具体地写代码时，可以有一些优化：

- 用**一维**的结构体存储点的坐标与权值；

- 预处理逆元；

- 排序后递推时，遇到所求点即可输出并结束程序；

特别注意的是，对于权值相同的点，我们应当将其看作**一整批**，处理完一批点后，再一次性累加维护。

```
#include<bits/stdc++.h>
#define int long long //不建议这样写，因为会比较耗时
using namespace std;
const int mod=998244353;
const int maxn=1000+233;
int n,m,cnt,X,Y,sum,sumx,sumx2,sumy,sumy2,sumf;
struct node{int x,y,data;}a[maxn*maxn];
int et[maxn*maxn],f[maxn*maxn];
bool cmp(node u,node v){
	return u.data<v.data;
}
signed main(){
	cin>>n>>m;
	cnt=m*n,et[1]=1;
	for(int i=2;i<=cnt;i++)
		et[i]=(mod-mod/i)*et[mod%i]%mod; //预处理逆元
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			int x;cin>>x;
			a[(i-1)*m+j]=(node){i,j,x}; //一维的结构体存储，方便排序，更方便调错
	}
	cin>>X>>Y;
	sort(a+1,a+cnt+1,cmp);
	a[cnt+1].data=-1; //增加一个边界，减少不必要的判断
	for(int i=1;i<=cnt;i++){
		if(sum){
			f[i]=(f[i]+sumf)%mod;
			f[i]=((f[i]+sum*a[i].x%mod*a[i].x%mod-2*sumx*a[i].x%mod+sumx2)%mod+mod)%mod;
			f[i]=((f[i]+sum*a[i].y%mod*a[i].y%mod-2*sumy*a[i].y%mod+sumy2)%mod+mod)%mod;
			f[i]=f[i]*et[sum]%mod;
		}else f[i]=0;
		if(a[i].x==X&&a[i].y==Y){cout<<f[i];return 0;} //得出答案即可结束程序
		if(a[i].data!=a[i+1].data){
			for(int j=i;j>=1;j--){ //将权值相同的一起递推，时间仍是均摊 O(nm) 的
				if(a[j].data!=a[i].data)break;
				sum++;
				sumf=(sumf+f[j])%mod;
				sumx=(sumx+a[j].x)%mod;
				sumy=(sumy+a[j].y)%mod;
				sumx2=(sumx2+a[j].x*a[j].x%mod)%mod;
				sumy2=(sumy2+a[j].y*a[j].y%mod)%mod;
			}
		}
	}
	return 0;
}
```

---

