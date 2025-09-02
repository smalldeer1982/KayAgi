# 蛋糕 Cake

## 题目背景

>   道不同不相为谋。

$\text{.cilohocohc}$ 喜欢吃蛋糕，尤其是巧克力蛋糕。

$\text{LeverImmy}$ 送了一个超级大的巧克力蛋糕给她做生日礼物，蛋糕上面点缀着许多巧克力布丁。

$\text{.cilohocohc}$ 一个人肯定是吃不完那么大一个蛋糕的，于是她要 $\text{LeverImmy}$ 帮她蛋糕切成两块，使得两块蛋糕上的布丁数之比为 $a : b$。

蛋糕可以抽象为一个二维平面；而做蛋糕的作坊很缺心眼，因此每个布丁都很小，可以看成二维平面上的一个 **整点**。

$\text{LeverImmy}$ 的刀技非常高超，所以他准备秀一下，他只会以一个 **斜率不小于 $1$ ，不大于 $10^{12}$ 的一次函数图像** 为轮廓在蛋糕上划一刀。

他想考考聪明的你，如果是你，你会怎么划？


## 题目描述

已知 $n$ 以及 $a, b$，求一个一次函数 $f(x) = k(x - x_0) + y_0 (1 \le k \le 10^{12})$，使得 $f(x)$ 将平面内的 $n$ 个点恰好分为个数之比 $a : b$ 的两部分。

如果你不知道一次函数为什么要这样表示，这里有 [点斜式](https://baike.baidu.com/item/%E7%82%B9%E6%96%9C%E5%BC%8F/921468?fr=aladdin) 的定义。


## 说明/提示

本题采用 **捆绑测试**。

$\text{Subtask 1 (10 pts)}:$ 保证 $n \in \{2, 3\}$；

$\text{Subtask 2 (30 pts)}:$ 保证 $\left|x_i\right|, \left|y_i\right| \le 10$；

$\text{Subtask 3 (60 pts)}:$ 保证 $2 \le n \le 10^5$，$0 \le \left|x_i\right|, \left|y_i\right| \le 10^5$。

对于所有数据，保证 $(a + b) | n$ 且 $ab \neq 0$。

---

#### Special Judge

**本题采用 $\text{Special Judge}$。**

spj 返回信息一览：

`Your answer is correct!`：你的结果是正确的；

`Your answer is wrong, expected ratio as a : b, found A : B.`：你的函数有问题，它把所有的点分割成了 $A : B$ 的两部分而不是 $a : b$ 的两部分；

`Oops, data out of range!`：你所给出的点的横纵坐标，或是斜率，在题目要求的范围外。

注意，你在 **赛时** 并不能看到 Special Judge 的返回结果。


## 样例 #1

### 输入

```
2 1 1
0 1
1 0```

### 输出

```
1 0 0```

# 题解

## 作者：Y_zhao111 (赞：10)

> **You can go and read the [English version](https://www.luogu.com.cn/article/airy539m) of this solution.**

### Description

题目传送门：[P6614 蛋糕 Cake](/problem/P6614)。

自己构造出一个一次函数，要求将平面上的 $n$ 个点分成 $a:b$ 两部分。

### Analysis

考虑极端情况。

>以一个 **斜率不小于 $1$ ，不大于 $10^{12}$ 的一次函数图像** 为轮廓在蛋糕上划一刀。

极端数据 $k={10}^{12}$，那么函数就相当于一条平行于纵轴的直线，如下图。

![desmos-graph](https://cdn.zhaohonghao-qwq.com/desmos-graph.51e2wg88p8.svg)

所以我们只需要让左边满足 $n\times \dfrac{a}{a+b}$ 个，右边满足 $n\times \dfrac{b}{a+b}$ 即可。

化简一下就是左 $\dfrac{n\times a}{a+b}$，右 $\dfrac{n\times b}{a+b}$。

由于本题采用 $\text{Special Judge}$，输出**唯一合法解即可**。

设左边的点数为 $A$，右边的点数为 $B$。

$k={10}^{12}$，$x_0=x_A,y_A$ **一定是一组合法解。**

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;


const long long K = (long long)(pow(10 , 12));

struct Node
{
	int x , y;
	
	inline bool operator < (const Node &cmp) const //随个人喜好，也可以写成 cmp()
	{
		return x != cmp.x ? x < cmp.x : y > cmp.y;
	}
	
}Cake[1000005];

signed main()
{
	int n , a , b;
	cin >> n >> a >> b;
	
	for(register int i = 1 ; i <= n ; i ++)
	{
		cin >> Cake[i].x >> Cake[i].y;
	}
	
	sort(Cake + 1 , Cake + n + 1);
	cout << K << " " << Cake[n * a / (a + b)].x << " " << Cake[n * a / (a + b)].y << endl;
	return 0;
}
```

---

## 作者：Clever_Jimmy (赞：7)

~~出题人报到~~

我们可以按照 $x$ 为第一关键字从小到大，$y$ 为第二关键字从大到小对所有的点排序。

设 $A = \dfrac{n\cdot a}{a + b}, B = \dfrac{n\cdot b}{a + b}$。

因为恰好在线上的点算在上方，

所以我们只需要找到第 $A$ 个点，并构造一个很陡很陡的一次函数即可。

可以看出，$k = 10^{12}, x_0 = x_{A}, y_{A}$ 一定为一组合法解。


---

## 作者：hensier (赞：4)

本题可以采用极限法。为了做到分隔线的作用，我们可以让这条直线接近于平行于坐标轴，也就是说，让$k$的值尽可能大或者尽可能小。

> 一次函数图像斜率不小于$1$ ，不大于$10^{12}$

如果要让图像几乎是与$x$轴平行，那么$k$的值将非常接近$0$。可以说，当$k=0$的时候，函数为常数函数，此时关系式为$y=y_0$，函数与$x$轴平行。但是，$k<1$是要保证的，但是这不符合题目的要求。

如果要让图像几乎是与$y$轴平行，那么$k$的值将接近$∞$。可以说，当$k=∞$（当然这是不可能的）的时候，函数同样为常数函数，此时函数与$y$轴平行。

于是我们考虑作一个斜率为$10^{12}$的一次函数，可以发现，函数几乎是与$y$轴平行的。

此时，如果参数的值接近于$0$，那么函数几乎与$y$轴重合：

![](https://cdn.luogu.com.cn/upload/image_hosting/8fgwga94.png)

改变它的值，如果它大于$0$，那么直线在$y$轴左侧，否则在右侧。

![](https://cdn.luogu.com.cn/upload/image_hosting/2irt05j6.png)

通过这种方法，我们成功地找到了一种非常合理的划分方式。我们可以把这个斜率很大的函数看作是一个常数函数，我们用$x=a_0$表示。此时，该直线左侧满足$x<a_0$，右侧满足$x>a_0$。

题目中说要把这些直线分成$a:b$的比例，那么我们在排列之后（先按$x$值从小到大，再按$y$值从大到小），可以选取第$\dfrac{na}{a+b}$个点作为基准，让这个直线经过该点即可。

如下图，假如要把$6$个点分成$1:1$的比例，那么基准点就是$C$，即第三个点。我们让该直线过$C$点，然后接下来求关系式即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/3kta2yr5.png)

设该基准点坐标为$(x_1,y_1)$，而关系式为$y=k(x-x_0)+y_0$。现在已经让$k=10^{12}$，所以只需要求$x_0,y_0$的值。

我们要让直线经过$(x_1,y_1)$，那么$C$的横纵坐标要满足该关系式。因为要让$y=y_1$，所以$k(x-x_1)=0$。所以$x=x_1$。

因此最终输出的答案为$10^{12},x_1,y_1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,pos;
struct point
{
    int x,y;
}p[100001];//定义结构体，方便排序
bool cmp(point A,point B)
{
    if(A.x!=B.x)return A.x<B.x;//先按横坐标从小到大排序
    return A.y>B.y;//再按纵坐标排序
}
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);
    sort(p+1,p+n+1,cmp);
    pos=n/(a+b)*a;//确定基准点的下标
    printf("1000000000000 %d %d",p[pos].x,p[pos].y);//按照思路输出
    return 0;
}
```

---

## 作者：zlqwq (赞：3)

数据范围里 $k$ 好大呀！

不难发现，我们需要让左边共有 $n \times \frac{a}{a + b}$ 个，同时右边有 $n \times \frac{b}{a+b}$ 个。

开一个结构体。

然后我们将 $x$ 坐标从小到大，$y$ 坐标从大到小作为排序的依据将所有点进行排序。

设此时左右两数分别为 $u$ 和 $v$，只要将 $k$ 取最大值，且 $x_0=x_u,y_u$ 一定是一种正确答案。

---

## 作者：txrw (赞：3)

# P6614 题解
~~题意非常清晰明了了。~~

### 思路：
观察题目，可以发现 $1\le k \le 10^{12}$。

由此可以发现，$k$ 的取值可以非常大。

既然要求直线，根据初中数学知识，我们可以想到，这条直线可以看成平行于 $y$ 轴。

那么这题就很简单了。

### 实现：
可以将点按 $x$ 坐标从小到大排序，需要保证 $\dfrac {n\times a} {(a + b)}$ 个点在直线左边，那么 $\dfrac{n\times b}{(a + b)}$ 个点就在右边了，这样就分成了 $a,b$ 两部分。

且根据点斜式，此时的 $x_0,y_0$ 就是第 $\dfrac {n\times a} {(a + b)}$ 个点的横坐标，而 $k$ 直接取 $10^{12}$ 就可以了。

### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N=1e6+10;
int n,a,b;
struct nd{
	int x,y;
}t[N];

bool cmp(nd x,nd y){
	return (x.x==y.x)?x.y>y.y:x.x<y.x; 
	//这里的 y 从大到小是因为斜线上的点属于左边，那么它下面点就在右边了。 
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
		cin>>t[i].x>>t[i].y;
	sort(t+1,t+n+1,cmp);
	int ans=n/(a+b)*a;
	cout<<"1000000000000 "<<t[ans].x<<" "<<t[ans].y;
	return 0;
}
```

---

## 作者：_hxh (赞：2)

这道题可以考虑极端情况。试想一下，若 $k = 10^{12}$，函数不就近似于一条平行于 $y$ 轴的直线吗！这时我们只需要让函数的左边存在 $n \times \dfrac{a}{a + b}$ 个点，右边存在 $n \times \dfrac{b}{a + b}$ 个点就可以了。即我们只需要找到第 $n \times \dfrac{a}{a + b}$ 个点并构造一个 $k = 10^{12}$ 的函数。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,a,b,pos;
struct Node
{
	int x,y;
}dot[N];
bool cmp(Node a,Node b)
{
	if (a.x == b.x)
		return a.y > b.y;
	return a.x < b.x;
}
int main()
{
	cin >> n >> a >> b;
	pos = n * a / (a + b);
	for (int i = 1;i <= n;i++)
		cin >> dot[i].x >> dot[i].y;
	sort(dot + 1,dot + n + 1,cmp);
	cout << "1000000000000 " << dot[pos].x << " " << dot[pos].y << endl;
	return 0;
}
```

---

## 作者：Hedgehog_210508 (赞：2)


**题目传送门**：[here](https://www.luogu.com.cn/problem/P6614)。

**题目简述**：
构造一个一次函数使平面上的 $n$ 个点被分成 $a:b$ 两部分。

**思路**：
显然，这样的直线有很多，我们可以考虑极端的情况（其实 $k$ 取别的值也能做）；所以我们可以让斜率 $k$ 取到一个足够大的值，如 $114514$，这样的话直线几乎就是垂直的。

接下来我们要使前 $\dfrac{n \times a}{a+b}$ 个点在其左上侧。为此可以横坐标从小到大，纵坐标从大到小排列，确保第 $\dfrac {n \times a}{a+b}$ 号点之前的点全在左上侧，则经过此点的直线的左上侧也恰好这么多点。由于点斜式的特性，$x_0$ 和 $y_0$ 取此点坐标即可。

**代码如下**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a,b;
struct p{//点的结构体
    ll x;
    ll y;
    bool operator <(const p &a)const{//比较器，按照坐标排序
        if(x!=a.x) return x<a.x;
        else return y>a.y;
    }
}k[100009];
int main(){
    cin>>n>>a>>b;
    a=a*1.*n/(a+b),b*=b*1./a;//把比例变成点数
    for(ll i=1;i<=n;i++) cin>>k[i].x>>k[i].y;
    sort(k+1,k+n+1);
    cout<<"114514 "<<k[a].x<<' '<<k[a].y;//取第a个点的横纵坐标即可
	return 0;
}
```


---

## 作者：_ajthreac_ (赞：2)

## 0.Description
平面上有一些整点，请你找到一条直线使其将这些点分成 $a:b$ 两部分。
## 1.Solution
初看这道题可能有人觉得很难，但只要构造出结论就很简单了。      
我们考虑如何把点按比例分开：            
一条普通的直线不好讨论，于是自然而然地想去考虑一些极端情况，再加上数据范围中 $k$ 和 $x_0,y_0$ 的巨大差异，我们可以直接看 $k=10^{12}$ 时的情况。            
这种情况下的直线可以近似地看为与 $y$ 轴平行，那么我们只需要使它左边（由于斜率不是 $\infty$ 所以准确来说是左上方）有 $a$ 个点即可。
## 2.Implementation
由于取到前 $a$ 个点，我们首先对所有点的 $x$ 从小到大排序，再对 $y$ 从大到小排序，这样就保证了过第 $a$ 个点的直线**左上方**有 $a$ 个点。
## 3.Code
[开头代码](https://www.cnblogs.com/juruoajh/p/12632444.html)
```cpp
#define N 100010
int n,a,b;
struct Point {
	int x,y;
}p[N];
bool operator < (Point a,Point b){
	return (a.x==b.x)?(a.y>b.y):(a.x<b.x);
}
int main(){
	Read(n),Read(a),Read(b);
	for(rg int i=1;i<=n;i++)Read(p[i].x),Read(p[i].y);
	sort(p+1,p+1+n);
	int tmp=a*n/(a+b);
	cout<<1000000000000<<" "<<p[tmp].x<<" "<<p[tmp].y<<endl;
	return 0;
}
```

---

## 作者：_you_know_who_ (赞：0)

思路前面的大佬们已经讲的很清楚了，我来稍微详细地讲一遍吧。。。

## 思路

首先，我们看一下函数 $f(x)=10^{12}x$ 的图像。

![](https://cdn.luogu.com.cn/upload/image_hosting/6mn1rrw1.png)
我们发现，这个图像几乎和 $y$ 轴平行。
所以我们只需要让 $k$ 保正是 $10^{12}$，然后取点即可。

根据点斜式，我们只需要让直线左边有 $\frac{n \times a}{a + b}$ 个点，右边有 $\frac{n \times b}{a + b}$ 个点即可。

我们把每个点依次排序：
- 当两个点 $x$ 坐标不同时，坐标 $x$ 小的在前。
- 当两个点 $x$ 坐标相同时，坐标 $y$ 大的在前。

于是我们写出代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct tt
{
    int x,y;
}a[100001];
int mid;
bool gz(const tt u,const tt v);
signed main()
{
    int n,x,y;
    scanf("%lld%lld%lld",&n,&x,&y);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&a[i].x,&a[i].y);
    }
    sort(a+1,a+1+n,gz);
    mid=(n*x)/(x+y);
    cout<<"1000000000000"<<' '<<a[mid].x<<' '<<a[mid].y<<endl;
    return 0;
}
bool gz(const tt u,const tt v)
{
    if(u.x==v.x)
    {
        return u.y>v.y;
    }
    return u.x<v.x;
}
```

---

## 作者：ZY_king_YB (赞：0)

~~本蒟蒻的第2篇题解……（上一篇被打回两次呜呜呜）~~

很简单的一道数学题（八下函数秒了）。

# 第 $0$ 步 抽象题意

一个二维坐标系，上面分布着 $n$ 个整点，第 $i$ 个点的坐标为 $(x_i,y_i)$，现想要构建一个一次函数 $y=k(x−x_0)+y_0$，使得这些整点恰好分成 $a,b$ 两部分。其中 $k$ 为常数，且 $k\le10^{12}$.

# 第 $1$ 步 我的思路
观察题目，可以发现：

$$1\le k \le 10^{12}$$

即 $k$ 的取值可以非常大。

既然这是一条一次函数的图像（一条直线），根据一次函数的相关特性：

对于一个一次函数 $y=k(x−x_0)+y_0$，有：

当 $k\to\infty$ 时，函数 $y=k(x−x_0)+y_0$ 的图像也无限接近于 $x=0$ 的图像。

此题中，$k\le10^{12}$，很大，可近似看成 $k\to\infty$.

那么这题就很简单了。

# 第 $2$ 步 理论存在，实践开始
可以将点按 $x$ 坐标升序排列，需要保证 $\dfrac{an}{a+b}$ 个点在直线左边，那么剩下的 $\dfrac{bn}{a+b}$ 个点就在右边了，这样就分成了 $a,b$ 两部分。

并且根据点斜式的相关知识，此时的 $x_0,y_0$  就是第 $\dfrac{an}{a+b}$ 个点的 $x$ 坐标，而 $k$ 直接取最大值 $10^{12}$ 就可以了。

# 第 $3$ 步 Coding

AC代码如下：

```cpp
//P6614 亲测已AC 
#include <bits/stdc++.h>//不解释 
#define ll long long//用ll代替long long 
using namespace std;//不解释
struct point{ll x,y;}t[1000005];//结构体，储存每个点的x,y坐标
bool cmp(point x,point y){
	if(x.x==y.x)return x.y>y.y;
	else return x.x<y.x;
}//自定义sort排序使用函数 
int main(){
	ll n,a,b;
	scanf("%lld%lld%lld",&n,&a,&b);//输入n,a,b 
	for(ll i=1;i<=n;i++)
		scanf("%lld%lld",&t[i].x,&t[i].y);//输入每个点的坐标 
	sort(t+1,t+n+1,cmp);//排序 
	ll ans=n/(a+b)*a;//计算最后一个位于直线上方的点的下标ans 
	printf("1000000000000 %lld %lld",t[ans].x,t[ans].y);
	//输出k和第ans个点的坐标，即题目要求的解 
	return 0;//完结撒花！ 
}
```

---

## 作者：xiaokang_suancai (赞：0)

# P6614 题解
[朴实无华的题目传送门](https://www.luogu.com.cn/problem/P6614)
## 题目大意
构造一条直线，将平面分成两个部分，使得平面上的 $n$ 个点在两个部分内的数量比为 $a:b$。
## 题目分析
注意到斜率的数据范围是 $1 \le k \le 10^{12}$，因此这条直线可以非常的陡峭，那么这对我们解题有什么帮助呢？

不难发现，当 $k=10^{12}$ 时，直线可以看做是横轴的垂线。这样，这道题就很简单了。

我们将点按照横坐标从小到大排序，使得第 $\frac{a \times n}{a+b}$ 个点刚好在直线上，由于此时这个点视为在直线的上方，因此这个直线就完美地符合题意了。
## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;
}p[1000005]; // 用结构体存储点坐标
int n,a,b;
long long ans; // 谨慎起见开了 long long
bool cmp(node a,node b)
{
	if(a.x!=b.x)
		return a.x<b.x;
	else
		return a.y>b.y;
} // 排序函数
int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
		cin>>p[i].x>>p[i].y;
	sort(p+1,p+n+1,cmp); // 将点排序
	ans=n*a/(a+b);
	cout<<1000000000000<<" "<<p[ans].x<<" "<<p[ans].y; // 输出第 ans 个点的横纵坐标，原因上面已经讲了
	return 0;
}
```

---

## 作者：yanxu_cn (赞：0)

### 分析题意

用一条直线分割一个平面，使得直线两侧的点的数目之比等于给定的值。

### 思路

乍一看这题，感觉这题很难，找不到突破口。但我们可以发现一个特殊的地方——这题中其他的数据规模并不大，但是斜率 $k$ 的范围非常的大：$1\le k\le 10^{12}$。如果我们把 $k$ 取到足够的大，那么函数的图象就会长这样（这是函数 $f(x)={10}^{11}x$ 的图象）：

![函数图象](https://cdn.luogu.com.cn/upload/image_hosting/26rfgx8g.png)

根据图象，我们易知，如果 $k$ 的数量级比较大，此时**函数图象至多只经过题设的范围中的一个整点，且当函数经过某一个整点时，任意横坐标小于该整点的点和在该点正上方的点均会在该函数图象的左侧**。

### 做法

有了思路，做法就显而易见了。我们将所有的点按横坐标为第一关键字（升序）而纵坐标为第二关键字（降序）进行排序。我们将斜率开到最大，再将排序后第 $\displaystyle{\frac{a\times n}{a+b}}$ 个的坐标输出就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct point
{
	long long x,y;
	inline const bool operator < (const point &p)const
	{
		if(x<p.x)return true;
		else if(x==p.x&&y>p.y)return true;
		return false;
	}
}p[200007];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	register int n,a,b;
	cin>>n>>a>>b;
	a*=n/(a+b);
	for(int i=0;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		p[i].x=x;
		p[i].y=y;
	}
	sort(p,p+n);
	cout<<1000000000000ull<<' '<<p[a-1].x<<' '<<p[a-1].y;
	return 0;
}
```
### 做后总结
为什么我们要以上文所说的排序方法排序？
- 关键字的顺序：我们注意到这里对斜率的要求是 $1\le k\le 1^{12}$。也就是说斜率至少为 $1$，其倒数也不会大于 $1$。而如果我们交换关键字的顺序，这是我们就希望斜率的倒数能取到一个比较大的数，至少是 $2\times 10^5$，显然是不可以的。
- 纵坐标的顺序：我们注意到直线斜率 $k>0$，故如果直线经过一个点，则这个点正上方的点都在直线左侧。

---

## 作者：WindowsWKP (赞：0)

先以 $x$ 为第一关键字排序，从小到大，再以 $y$ 为第二关键字排序，从大到小。

然后，构造一条几乎平行于 $y$ 轴的函数，并让左边有 $\frac{n\times a}{a+b}$ 个，右边有 $\frac{n\times b}{a+b}$ 个。

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int>p[100010];
bool cmp(pair<int,int>a,pair<int,int>b){
    if (a.first!=b.first)
        return a.first<b.first;
    return a.second>b.second;
}
int main(){
    int n,a,b;
    cin>>n>>a>>b;
    for (int i=1;i<=n;i++)
        cin>>p[i].first>>p[i].second;
    sort(p+1,p+n+1,cmp);
    cout<<1000000000000<<" "<<p[n/(a+b)*a].first<<" "<<p[n/(a+b)*a].second;
    return 0;
}
```

---

## 作者：CaoSheng_zzz (赞：0)

### 题意

再一个平面上给出 $n$ 个点，你可以画一条直线将这个平面上的点分成两个部分，且在直线上面的点属于左边部分的，现在要求你画出一条直线需要满足这条直线将平面中的点分成两个部分且这两个部分点数量的比值为 $a : b$。

### 思路

不难发现我们首先需要将所有点按坐标排序，为了方便计算所以我们需要重左往右从上往下排序。

我们可以用一个结构体来储存这些点：
```cpp
struct Cake {
	int x , y ;
}
```

接着我们可以在结构体中写出一个按前文要求的重载运算符：
```cpp
bool operator < (const Cake &a) { return x == a.x ? y > a.y : x < a.x ;}
```

现在考虑怎么分点，我们不难想出可以画一条直线使这条直线刚好只包含排好序之后的 $n \times \frac{a}{a+b}$ 个点，因为这样就可以使令一半分到 $n - n \times \frac{a}{a+b}$ 及 $n \times \frac{b}{a+b}$ 个点，这样两个部分相比就刚好是 $a : b$ 了。

所以我们最后只需要解决如何画出一条刚好只包含第 $n \times \frac{a}{a+b}$ 个点。由于题目保证没有重点且 $|x_i,y_i| \leqslant 10^5$，所以我们对于最极端的情况只需要保证我们当前直线的斜率大于 $2 \times 10^5$ 就行了。

最后 Code：
```cpp
#include <algorithm>
#include <iostream>
#define ll long long
#define spc putchar(' ')
#define ent putchar('\n')
using namespace std;

inline int read(){
	int f = 1 , k = 0;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') f = -1;
		c = getchar() ;
	}
	while(c >= '0' && c <= '9'){
		k = (k << 3) + (k << 1) + (c ^ 48);
		c = getchar() ;
	}
	return (f == 1 ? k : -k);
}

void output(int now){
	if(now < 0){
		putchar('-');
		output(- now);
	}
	else{
		if(now > 9) output(now / 10);
		putchar((now % 10) ^ 48);
	}
}

struct Cake {
	int x , y ;
	inline bool operator < (const Cake &a) { return x == a.x ? y > a.y : x < a.x ;}
}f[500001];

signed main() {
	int n = read() , a = read() , b = read() ;
	for(int i=1 ; i<=n ; i++) f[i].x = read() , f[i].y = read() ;
	sort(f + 1 , f + n + 1) ;
	putchar('1') ; for(int i=1 ; i<=12 ; i++) putchar('0') ;
	return spc , output(f[n / (a + b) * a].x) , spc , output(f[n / (a + b) * a].y) , ent , 0 ;
}

---

