# Urbanization

## 题目描述

## 题目大意

$n$个人要住进两个城市里，两个城市分别能住$n1$,$n2$个人。

$n$个人中，每个人都有一个财富值——第$i$个人的是$ai$。

现在请你安排这些人的入住，使得两个城市的每位居民的财富值**平均值的和**最大。（分别计算两个城市的财富值平均值，再相加）

当然，每一个人只能至多住进一个城市。

注意，并不是每一位居民都必须被安排住进两个城市中，没有被安排的居民直接回家。

## 说明/提示

$ 1≤n,n1,n2≤100000 $

$ n1+n2≤n $

$ 1≤ai≤100000 $


第一个样例中，可以让第一个居民住进第一个城市、让第二个居民住进第二个城市。

第二个样例中，让三号、四号居民住进第一个城市，让二号居民住进第二个城市。这样平均值的和最大，等于
$ (2+3)÷2+4÷1=6.5 $。

## 样例 #1

### 输入

```
2 1 1
1 5
```

### 输出

```
6.00000000
```

## 样例 #2

### 输入

```
4 2 1
1 4 2 3
```

### 输出

```
6.50000000
```

# 题解

## 作者：pandaSTT (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF735B)

[更好的阅读体验?](https://www.luogu.com.cn/blog/cathyqwq/solution-cf735b)

## 思路

题目简洁，题意清晰。

首先观察数据，显然不能暴力，因此开始考虑贪心。

可以很快发现贪心策略：**富裕的人居住在人少的城市**。

## 证明如下：

~~生活常识好吧，有钱人肯定住在人少的地方啊。~~

简化题意，让两个人来选择城市，第一个人的富裕程度为 $ a $ 小，第二人的富裕程度为 $ b $ ,且 $ a \leq b ,n1 \leq n2 $ 。

那么两个人的居住情况可以分成两种情况讨论：第一个人住第一座城市，第二个人住第二座城市和第一个人住第二座城市，第二个人住第一座城市。~~（废话好多啊）~~

那么两种情况的两个城市的每位居民的富裕值平均值的和分别为:

$ \frac{a}{n1}+\frac{b}{n2} $ and $ \frac{a}{n2}+\frac{b}{n1} $

接下来通过做差法比较大小：

$ \frac{a}{n1} + \frac{b}{n2} - \frac{a}{n2} + \frac{b}{n1} $

$ = \frac{a \times ( n2 - n1 ) +  b \times ( n1 - n2 )}{n1 \times n2}$

$ = ( n2- n1 ) \times ( a + b ) \times  \frac{1}{ n1 \times n2 } $

由于我们默认 $ n1 \leq n2 $，所以 $ \frac{a}{n1}+\frac{b}{n2} \leq \frac{a}{n2}+\frac{b}{n1} $，得证。

# 代码

```cpp
  #include<bits/stdc++.h>
  namespace lovely_cathy{
      #include<bits/stdc++.h>
      using namespace std;
      #define int long long
      inline char gc(){
          static char buf[1000010],*p1=buf,*p2=buf;
          return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
      }
      inline int read(){
          register int x=0,f=0;
          static char s=gc();
          while(s<'0'||s>'9')f|=s=='-',s=gc();
          while(s>='0'&&s<='9'){
              x=(x<<3)+(x<<1)+(s^48);s=gc();
          }return f?-x:x;
      }
  }
  using namespace lovely_cathy;
  const int N=1e5+5;
  int n,n1,n2;
  struct node{
      int val;
      friend bool operator<(node x,node y){
          return x.val>y.val;
      }
  }a[N];
  double ans1,ans2;
  signed main(){
      n=read(),n1=read(),n2=read();
      for(int i=1;i<=n;a[i++].val=read());
      sort(a+1,a+n+1);
      if(n1>n2){
          n1^=n2^=n1^=n2;
      }
      for(int i=1;i<=n1;i++){
          ans1+=a[i].val*1.0;
      }
      for(int i=n1+1;i<=n1+n2;i++){
          ans2+=a[i].val*1.0;
      }
      printf("%.8lf",(ans1/(n1*1.0))+(ans2/(n2*1.0)));
      return 0;
  }
```


---

## 作者：cqbztz2 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF735B)

# 前言：

~~这道贪心也配做绿题？~~

# 思路：

由于题目要求两个城市的每位居民的财富值平均值的和最大，那就只让财富值排名前 $ n1+n2 $ 的居民入住，并且让财富值排名靠前的居民入住人数较少的城市，解释如下：

设 $ a<b $ 且 $ n1<n2 $，则情况分为 $\frac{a}{n1}+\frac{b}{n2} $ 和 $ \frac{a}{n2}+\frac{b}{n1} $ 两种情况

$ \frac{a}{n1}+\frac{b}{n2} - \frac{a}{n2}+\frac{b}{n1} $

$ =\frac{a*n2+b*n1}{n1*n2} - \frac{a*n1+b*n2}{n1*n2} $ 

$ =a*n2+b*n1 - a*n1+b*n2 $

$ =a*n2-a*n1 - b*n2+b*n1 $

$ =(n2-n1)*a - (n2-n1)*b $ 

$ =a - b > = 0$



综上所述，应该让财富值排名靠前的居民入住人数较少的城市，所以代码实现就十分简单了。

# 代码：

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,n1,n2,a[100005];
  double ans1,ans2;
  bool cmp(int x,int y){
      return x>y;
  }
  int main(){
      cin>>n>>n1>>n2;
      for(int i=1;i<=n;i++){
          cin>>a[i];
      }
      sort(a+1,a+n+1,cmp);
      for(int i=1;i<=min(n1,n2);i++){
          ans1+=a[i];
      }
      for(int i=min(n1,n2)+1;i<=n1+n2;i++){
          ans2+=a[i];
      }
      printf("%.6lf",(ans1/min(n1,n2))+(ans2/max(n1,n2)));
      return 0;
  }
```


---

## 作者：BigJoker (赞：1)

# 0x00 思路

看到此题大致读完题后，会发现是一道贪心。

# 0x01 贪心

首先，我们为了使平均值最大，因此所选的数也是其中最大的才可以，因此我们对财富值从大到小进行排序，取前 $n1 + n2$ 个就可以了，其余的不管。思考第二个事情，如何将这些人分配进去。我们假设现在 $n1<n2$，并且现在最富的人拥有 $x$ 的财富值，最穷的拥有 $y$ 的财富值。那么需要分两种情况讨论。

* 那么如果将最富的人分配到 $n1$，将最穷的人分配到 $n2$，那么所获取到的价值就是：

	
   $\frac{\frac{x}{n1}+\frac{y}{n2}}{2}$
    

* 那么如果将最富的人分配到 $n2$，将最穷的人分配到 $n1$，那么所获取到的价值就是:

	$\frac{\frac{y}{n1}+\frac{x}{n2}}{2}$
    
我们可以将 $2$ 都给约掉

那么第一个式子为：
	
  
  $\frac{x}{n1}+\frac{y}{n2}$

$=\frac{x \cdot n2}{n1 \cdot n2}+\frac{y \cdot n1}{n1 \cdot n2}$

$=\frac{x \cdot n2+y \cdot n1}{n1 \cdot n2}$


第二个式子同理：

  $\frac{y}{n1}+\frac{x}{n2}$

$=\frac{y \cdot n2}{n1 \cdot n2}+\frac{x \cdot n1}{n1 \cdot n2}$

$=\frac{y \cdot n2+x \cdot n1}{n1 \cdot n2}$

现在两个式子可以同时约掉 $n1 \cdot n2$，我们用第一个式子减去第二个式子，如果是正数，说明第一个式子大，如果是负数，说明第二个式子大：

$x \cdot n2+y \cdot n1-y \cdot n2-x \cdot n1$

$=x \cdot (n2-n1)-y \cdot (n2-n1)$

$=(n2-n1) \cdot (x-y)$

由于 $n1<n2$ 并且 $x>y$，所以这个式子一定是个正数，所以第一个式子的值大于第二个式子，那么我们就可以说明需要将更富的人放在人更少的房子里，以上便是证明。

# 0x02 代码

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dep(i,r,l) for(int i=r;i>=l;i--)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;
const int N=1e5+5;
int n,n1,n2,a[N],p;
double ans1,ans2;
bool cmp(int x,int y){return x>y;}
int main(){
	scanf("%d %d %d",&n,&n1,&n2);p=n1+n2;
	rep(i,1,n) scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	rep(i,1,min(n1,n2)) ans1+=a[i]*1.0;
	rep(i,min(n1,n2)+1,p) ans2+=a[i]*1.0;
	printf("%.8lf",ans1/min(n1,n2)*1.0+ans2/max(n1,n2)*1.0);
	return 0;
}
```


---

## 作者：WinterRain208 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF735B)

### 做法

题目比较长，请自行跳转查看。给大家提供一种好理解的算法。同时经过一些优化时间空间都很小，目前我还是时间空间双第一。

首先这个结论非常重要：两个城市一定要填满。

证明:一个人财富最小是一，设城市一有$p_1$个人，城市二有$p_2$个人，只要他加入一个城市，那么这个$p_i$一定大于0，他对最后答案的贡献也一定大于0，所以不加入白不加入。

其次，财富之多的人应该在人少的城市里。

证明:这个人的财富为$a_p$且为最大的$a_i(1<=i<=n)$，设$p_1>p_2$，那么因为$a_i/p_1<a_i/p_2$，所以$a_i$必定在$p_2$里。

### 贪心策略

当这个人加入一个城市之后，它可以从名单中删除，接下来对下一个财富最大的人考虑，知道有一个城市没有名额或者人全部分完位置。

然后我们的贪心策略就可以完成了：从大到小排序，大的全部加入人少的城市，其他的人中大的那一部分加入另一个城市，这样产生的贡献总值一定最大。

再提出几个小优化，可以节省你的空间和时间，竞赛中常常用到。

首先节省时间，可以是用快读和$printf$。

然后节省空间，可以把空间大的数组替换成$vector$使用。然后这题就结束了。

### 代码 


主函数代码如下：

```cpp
n=read(),n1=read(),n2=read();
if(n2>n1)pos=n2,n2=n1,n1=pos;
F(i,1,n)
	num=read(),v1.push_back(num);
sort(v1.begin(),v1.end(),cmp);
F(i,0,n2-1)tot1+=v1[i];
F(i,n2,n2+n1-1)tot2+=v1[i];
printf("%.8lf",(double)tot1/n2+(double)tot2/n1);
```

点个赞再走吧

---

## 作者：Southern_Dynasty (赞：0)

**本题解法：贪心。**

贪心策略：将有钱的人放入人口少的城市，没钱的放入人口多的城市。

**考虑证明：**


设两个城市的总财富值分别为 $a1$ 和 $a2$，那么有两种情况：城市 $n1$ 的总财富值为 $a1$，城市 $n2$ 的总财富值为 $a2$（即平均值的和为 $\frac{a1}{n1}+\frac{a2}{n2}$）以及城市 $n1$ 的总财富值为 $a2$，城市 $n2$ 的总财富值为 $a1$（即平均值的和为 $\frac{a1}{n2}+\frac{a2}{n1}$）。

我们规定 $n1$ 小于等于 $n2$，$a1$ 小于等于 $a2$。

考虑用做差法比较大小：

$\frac{a1}{n1}+\frac{a2}{n2}-\frac{a1}{n2}-\frac{a2}{n1}$

=$\frac{a1*n2+a2*n1}{n1*n2}-\frac{a1*n1+a2*n2}{n1*n2}$

考虑舍去分母，得：

$a1*n2+a2*n1-a1*n1-a2*n2$

=$a1(n2-n1)-a2(n2-n1)$

=$(a1-a2)(n2-n1)$

综上，应该让财富值高的人住在人口少的城市。

## $\text{Code:}$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<iomanip>
#define gt getchar
#define pt putchar
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
inline int read(){
    int x=0,f=1;char ch=gt();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=gt();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gt();}return x*f;
}
inline void print(int x){
    if(x<0)pt('-'),x=-x;
    if(x>9)print(x/10);
    pt(x%10+48);
}
inline void println(int x){
	print(x);
	puts("");
}
int n,n1,n2,a[100005];
double a1,a2;
inline void myswap(int &a,int &b){
	a^=b;
	b^=a;
	a^=b;
}
signed main(){
	n=read(),n1=read(),n2=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	if(n1>n2)myswap(n1,n2);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n1;++i)
		a1+=a[i]*1.0;
	for(int i=n1+1;i<=n1+n2;++i)
		a2+=a[i]*1.0;
	double ans=(a1/n1*1.0)+(a2/n2*1.0);
	printf("%.8f",ans);
	return 0;
}
```


---

