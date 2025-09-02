# [IOI 1998] Polygon

## 题目描述

# 题目可能有些许修改，但大意一致

多边形是一个玩家在一个有n个顶点的多边形上的游戏，如图所示，其中n＝4。每个顶点用整数标记，每个边用符号+（加）或符号*（乘积）标记。

![](https://cdn.luogu.org/upload/pic/16086.png)

第一步，删除其中一条边。随后每一步： 

选择一条边连接的两个顶点V1和V2，用边上的运算符计算V1和V2得到的结果来替换这两个顶点。 

游戏结束时，只有一个顶点，没有多余的边。

如图所示，玩家先移除编号为3的边。之后，玩家选择计算编号为1的边，然后计算编号为4的边，最后，计算编号为2的边。结果是0。

![](https://cdn.luogu.org/upload/pic/16088.png)

（翻译者友情提示：这里每条边的运算符旁边的数字为边的编号，不拿来计算）

编写一个程序，给定一个多边形，计算最高可能的分数。

## 样例 #1

### 输入

```
4
t -7 t 4 x 2 x 5
```

### 输出

```
33
1 2```

# 题解

## 作者：Kalista (赞：158)

事实上，这道题，绝大多数题解都有疏漏，原因是这道题的数据是真的水。。毕竟连最小值不要都可以得到$80$。。至于错误的原因在下文有说明。

让我们重新开始吧，看到这道题，我们首要的两个问题：

1.如何处理这样一个环。

2.如何得到最开始删除的边。

对于第一个问题，很轻易地就可以想到断环成链，同时我们还可以发现，通过断环成链，我们把第二个问题就解决了，我们可以通过对最后的结果再来一次对最大值的遍历，输出即可。

开始考虑$DP$，首先我们可以很显然的得到一个区间$DP$的板子：

设$f[i][j]$表示$[i,j]$这一个区间内可以得到的最大得分，转移方程如下：

加法：$f[i][j]=max(f[i][k]+f[k+1][j])$

乘法：$f[i][j]=max(f[i][k]\times f[k+1][j])$

但是我们更往深入思考，因为有乘法的存在，且有负数，那就肯定会有一个负负得正的情况，所以我们还需要维护一个最小值。设这个最小值为$g[i][j]$

然后就是分情况讨论的时间：

首先对于加法的情况，因为不存在负负得正一类的情况存在，所以两者的转移方程是基本一样的，大区间的最大值等于合并的两个区间的最大值之和，最小值等于合并的两个区间的最小值之和：

$f[i][j]=max(f[i][k]+f[k+1][j])$

$g[i][j]=min(g[i][k]+g[k+1][j])$

其次对于乘法，这里就很容易有很多遗漏点，让我们一种种分情况讨论：

（啊这里原意想画图，但考虑到手画太丑，用软件又麻烦，实在不理解可以拿着笔画一下各种情况）

$1.f[i][k],g[i][k],f[k+1][j],g[k+1][j] > 0$时：

$f[i][j]=max(f[i][k]\times f[k+1][j])$

$g[i][j]=min(g[i][k]\times g[k+1][j])$

$2.f[i][k],g[i][k],f[k+1][j] > 0,g[k+1][j] < 0$时：

$f[i][j]=max(f[i][k]\times f[k+1][j])$

$g[i][j]=min(f[i][k]\times g[k+1][j])$

$3.f[i][k],g[i][k] > 0,f[k+1][j],g[k+1][j] < 0$时：

$f[i][j]=max(g[i][k]\times f[k+1][j])$

$g[i][j]=min(f[i][k]\times g[k+1][j])$

$4.f[i][k],f[k+1][j],g[k+1][j] > 0,g[i][k] < 0$时：

$f[i][j]=max(f[i][k]\times f[k+1][j])$

$g[i][j]=min(g[i][k]\times f[k+1][j])$


$5.f[i][k],f[k+1][j] > 0,g[i][k],g[k+1][j] < 0$时：

$f[i][j]=max(f[i][k]\times f[k+1][j],g[i][k]\times g[k+1][j])$

$g[i][j]=min(f[i][k]\times g[k+1][j],g[i][k]\times f[k+1][j])$

（此处就没分绝对值大小的情况了，可以感性理解一下。）

$6.f[i][k] > 0,g[i][k],f[k+1][j],g[k+1][j] < 0$时：

$f[i][j]=max(g[i][k]\times g[k+1][j])$

$g[i][j]=min(f[i][k]\times g[k+1][j])$

$7.f[k+1][j],g[k+1][j] > 0,f[i][k],g[i][k] < 0$时：

$f[i][j]=max(f[i][k]\times g[k+1][j])$

$g[i][j]=min(g[i][k]\times f[k+1][j])$

$8.f[k+1][j] > 0,f[i][k],g[i][k],g[k+1][j] < 0$时：

$f[i][j]=max(g[i][k]\times g[k+1][j])$

$g[i][j]=min(g[i][k]\times f[k+1][j])$

$9.f[i][k],g[i][k],f[k+1][j],g[k+1][j] < 0$时：

$f[i][j]=max(g[i][k]\times g[k+1][j])$

$g[i][j]=min(f[i][k]\times f[k+1][j])$

（~~做了一个下午脑袋都要炸了，~~如果有$BUG$欢迎指出）

虽然说情况很多，但事实上你可以压成两行，不用特判。。（懒）

$f[i][j]=max(f[i][j],max(f[i][k]\times f[k+1][j],max(g[i][k]\times g[k+1][j],max(f[i][k]\times g[k+1][j],g[i][k]\times f[k+1][j]))))$

$g[i][j]=min(g[i][j],min(f[i][k]\times f[k+1][j],min(g[i][k]\times g[k+1][j],min(f[i][k]\times g[k+1][j],g[i][k]\times f[k+1][j]))))$

记得初始化长度为$1$的情况，至于区间端点为$0$的情况，由于上面的这个式子里面四种组合都全部考虑到了就可以不管了。

然后就可以愉快的$A$掉啦!

$Code$：

```cpp
#include<bits/stdc++.h>
#define lcy AKIOI
#define ll long long
const int inf=0x3f3f3f3f;
int n,ans=-inf;
int a[105];
int f[150][150],g[150][150];
char c[105];
int max(int x,int y){return (x>y)?(x):(y);}
int min(int x,int y){return (x<y)?(x):(y);}
int main(){
    scanf("%d\n",&n);//读入很诡异
    for(int i=1;i<=n;i++){
        scanf("%c %d",&c[i],&a[i]);getchar();
        a[n+i]=a[i];c[n+i]=c[i];//断环为链
    }
    for(int i=1;i<=(n<<1);i++){
        for(int j=1;j<=(n<<1);j++){
            f[i][j]=-inf,g[i][j]=inf;
        }
    }
    for(int i=1;i<=(n<<1);i++)f[i][i]=g[i][i]=a[i];
    for(int len=2;len<=n;len++){
        for(int i=1,j=len;j<=(n<<1);i++,j++){
            for(int k=i;k<j;k++){
                if(c[k+1]=='x'){
                    f[i][j]=max(f[i][j],max(f[i][k]*f[k+1][j],max(g[i][k]*g[k+1][j],max(f[i][k]*g[k+1][j],g[i][k]*f[k+1][j]))));
                    g[i][j]=min(g[i][j],min(f[i][k]*f[k+1][j],min(g[i][k]*g[k+1][j],min(f[i][k]*g[k+1][j],g[i][k]*f[k+1][j]))));
                }
                else if(c[k+1]=='t'){
                    f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]);
                    g[i][j]=min(g[i][j],g[i][k]+g[k+1][j]);
                }
            }
        }
    }
    for(int i=1;i<=n;i++)ans=max(ans,f[i][i+n-1]);printf("%d\n",ans);
    for(int i=1;i<=n;i++)if(f[i][i+n-1]==ans)printf("%d ",i);
    return 0;
}

```

---

## 作者：ZigZagKmp (赞：49)

## update on 2020.4.27
感谢评论区的同学 @[Fairicle](https://www.luogu.com.cn/user/135839) ，求最大值的确需要考虑最大乘最小的情况。

## update on 2019.11.01
在做dp题的时候又看到了这个题目，然后发现之前写的题解有一些小问题（~~逃~~，故作此更新。

---

## 题意分析
先随便删一条边，但不运算，这时就形成1条链，然后对这一条链，每删一条边，就相连节点运算一次，直到最后一个节点。求最大得分，以及得到最大得分的第一步的删边有哪些？

## 算法分析

### Part 1 有关先随便删掉的一条边
1. 暴力

我们按照题意来处理，要求我们随便删掉一条边，那我们就先枚举删掉的那一条边，然后转化为链上问题处理。

2. 破环为链

这题我们可以把原序列复制二倍接在原序列后面，这样$\forall i\in [1,n],a_i -a_{i+n-1}$就可以表示题意中的$n$种链。

### Part 2 设计核心算法
这题的子问题是区间，因此我们使用区间dp求解。

设计状态：$f(l,r)$表示区间$[l,r]$通过合并最终能够达到的最大的价值。

### 边界状态
显然$\forall i\in [1,2\times n),f(i,i)=a_i$

（因为只有一个数字，没有边，所以$f(i,i)=a_i$）。

### 状态转移

合并操作分为加法和乘法两种，因此状态转移也分为两种。

1. 合并法则为加法

这个相对简单，对于区间$[l,r]$，那么有
$$f(l,r)=\max_{k\in[l,r)}\{f(l,k)+f(k+1,r)\}$$

2. 合并法则为乘法

类比一下，对于区间$[l,r]$，那么有
$$f(l,r)=\max_{k\in[l,r)}\{f(l,k)\times f(k+1,r)\}$$

但这个是不严谨的，因为这一题存在负数，所以**负数乘负数**也有可能可以更新最大值。

因此之前的状态设计也是不严谨的，状态设计如下：

- $f_{max}(l,r)$表示区间$[l,r]$通过合并最终能够达到的最大的价值。
- $f_{min}(l,r)$表示区间$[l,r]$通过合并最终能够达到的最小的价值。

状态转移也应该重新设计：

1. 合并法则为加法

对于区间$[l,r]$，有
$$f_{max}(l,r)=\max_{k\in[l,r)}\{f_{max}(l,k)+f_{max}(k+1,r)\}$$

$$f_{min}(l,r)=\min_{k\in[l,r)}\{f_{min}(l,k)+f_{min}(k+1,r)\}$$

因为是加法运算，所以这里不需要考虑$f_{max}+f_{min}$的情况。

2. 合并法则为乘法

最大值情况1 ：最大乘最大

$$f_{max}(l,r)=\max_{k\in[l,r)}\{f_{max}(l,k)\times f_{max}(k+1,r)\}$$

最大值情况2 ：最小乘最小（同为负数）

$$f_{max}(l,r)=\max_{k\in[l,r)}\{f_{min}(l,k)\times f_{min}(k+1,r)\}$$

最大值情况3：最大乘最小，主要考虑如下的情况：

- $f1_{max}\le0,f2_{min}>0$，答案为负数，这是可能取得更大结果的（虽然说它是负数）。
$$f_{max}(l,r)=\max_{k\in[l,r)}\{f_{max}(l,k)\times f_{min}(k+1,r)\}$$

$$f_{max}(l,r)=\max_{k\in[l,r)}\{f_{min}(l,k)\times f_{max}(k+1,r)\}$$


---

最小值情况1 ：最小乘最小（同为正数）

$$f_{min}(l,r)=\min_{k\in[l,r)}\{f_{min}(l,k)\times f_{min}(k+1,r)\}$$

最小值情况2 ：最大乘最大（同为负数）

$$f_{min}(l,r)=\min_{k\in[l,r)}\{f_{max}(l,k)\times f_{max}(k+1,r)\}$$

最小值情况3 ：最小乘最大（一正一负）

$$f_{min}(l,r)=\min_{k\in[l,r)}\{f_{max}(l,k)\times f_{min}(k+1,r)\}$$

$$f_{min}(l,r)=\min_{k\in[l,r)}\{f_{min}(l,k)\times f_{max}(k+1,r)\}$$

### 目标状态
$\forall i\in [1,n],f(i,i+n-1)$

### Part 3 第二问
设答案为$ans$，那么所有$f(i,i+n-1)=ans$都是符合要求的答案


## 代码实现
下面用`f[1][][]`表示上文的$f_{max}$，`f[0][][]`表示上文的$f_{min}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 105
#define maxm 200005
template <typename Tp>
void read(Tp &x){
	x=0;int f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=f;
}
int n,m;
int op[maxn],a[maxn];
int f[2][maxn][maxn];
vector<int>pos;
int main(){
	read(n);scanf("\n");
	for(int i=1;i<=n;i++){
		scanf("%c %d ",&op[i],&a[i]);
		a[i+n]=a[i];op[i+n]=op[i];
	}
	m=2*n-1;//复制2倍，破环为链 
	memset(f[0],0x3f,sizeof(f[0]));//0x3f3f3f3f
	memset(f[1],0xc0,sizeof(f[1]));//0xc0c0c0c0近似等于-0x3f3f3f3f 
	for(int i=1;i<=m;i++)f[0][i][i]=f[1][i][i]=a[i];
	for(int i=2;i<=m;i++){
		for(int l=1,r;l+i-1<=m;l++){
			r=l+i-1;
			for(int k=l;k<r;k++){//区间dp 
				if(op[k+1]=='t'){//加法情况 
					f[0][l][r]=min(f[0][l][r],f[0][l][k]+f[0][k+1][r]);
					f[1][l][r]=max(f[1][l][r],f[1][l][k]+f[1][k+1][r]);
				}
				else{//乘法情况 
					f[0][l][r]=min(f[0][l][r],min(f[0][l][k]*f[0][k+1][r],
											  min(f[0][l][k]*f[1][k+1][r],
											  min(f[1][l][k]*f[0][k+1][r],
											  	  f[1][l][k]*f[1][k+1][r]))));
					f[1][l][r]=max(f[1][l][r],max(f[0][l][k]*f[0][k+1][r],
											  max(f[0][l][k]*f[1][k+1][r],
											  max(f[1][l][k]*f[0][k+1][r],
											 	  f[1][l][k]*f[1][k+1][r]))));
				}
			}
		}
	}
	int ans=-inf;
	for(int i=1;i<=n;i++){
		if(f[1][i][i+n-1]>ans){
			ans=f[1][i][i+n-1];
			pos.clear();pos.push_back(i);//pos是第二问答案集合 
		}
		else if(f[1][i][i+n-1]==ans)pos.push_back(i);
	}
	printf("%d\n",ans);
	for(int i=0;i<pos.size();i++)printf("%d ",pos[i]);
	return 0;
}
```

## 写在最后

对于这种分类讨论的`DP`问题，如果在考场上遇到，最好是把所有的情况都讨论一遍；但如果是在日常训练中遇到，我认为应当再回头思考每一种情况是否真正必要，因为可能有些题目存在部分情况求解比较麻烦，但实际上不可能成为最优解。

同时，再次感谢 @[Fairicle](https://www.luogu.com.cn/user/135839) 及时指出我的错误并给出一种反例。

---

## 作者：brealid (赞：43)

C++ 的指针是 C++ 的精髓。很多人因为指针的不好理解，而放弃学习。在短期内的 OI 生涯来看，这确实不会造成太大影响。但是，大部分的 STL 都是用指针实现的（包括常用的 sort，sort 是 STL 指针使用的一个显著例子）。下面，就本题中我实现的函数指针向大家作个介绍

### 初 · 读题

> 蒟蒻 : 这个题有两种操作（加法(t)和乘法(x)），怎么做？  
> 大佬 : 分类讨论转移方程  
> 蒟蒻 : 但我懒得分类讨论  
> 大佬 : ~~你个蒟蒻哪来这么多问题~~ 请使用万能的函数指针

### 二 · 指针中的王者——函数指针

> 蒟蒻 : 何为函数指针？  
> 大佬 : 函数指针，就是指向一个函数的指针 ~~等于没说~~  
> 大佬 : 这个问题还是给个例子吧，好解释一点  
```cpp
 1 typedef void Func();
 2 void f1() { puts("chen_zhe&LJC00118 aked ioi\n"); }
 3 void f2() { puts("I won't ak ioi\n"); }
 4 void f3() { puts("everyone in luogu can ak ioi\n"); }
 5 Func *s;
 6 int main()
 7 {
 8     int a;
 9     scanf("%d", &a);
10     switch (a) {
11         case 1: s = f1; // 合法写法
12         case 2: s = &f2; // 不合法写法
13         default: &s = f3; // 不合法写法
14     }
15     s(); // 合法写法
16     *s(); // 合法写法
17 }
```
(为了叙述方便，我加入了行编号)  
> 蒟蒻 : 啊啊啊什么东西啊，看不懂   
> 大佬 : 。。。  

逐行解释：  
1 定义函数指针**类型**，即把形如 ``void function_name()`` 的函数取别名为 ``Func``    
2~4 定义三个函数  
5 定义 Func 类型的函数指针 s   
11 函数名的本质是一个 const 的函数指针, 所以这里把函数指针赋值给函数指针，合法   
13 不符合。对于 ``int`` 与 ``int*`` ，这种写法可以；但是这里，函数不可以作为一个值来赋。  
15 可以的写法(在 C++ 之中，C 里不行)    
16 这是 C 里的写法，C++ 也适用  

> 蒟蒻 : 我懂了，谢谢

### 三 · 关于这道题

首先，负负得正的考虑我就不说了，别的题解都有。

其次，我本题关于函数指针的实现大概长这个样子

```cpp
// 定义
typedef int Func(int, int);
int op_plus(int a, int b) { return a + b; }
int op_multi(int a, int b) { return a * b; }
Func *oper[107];
// 使用
oper[k](a, b); 
```

### 终 · 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline Int read(char &c)       
{
    Int flag = 1;
    c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}

typedef int Func(int, int);

int op_plus(int a, int b) { return a + b; }
int op_multi(int a, int b) { return a * b; }

int n;
Func *oper[107];
int f[107][107], g[107][107];
int maxans = -32768;
vector<int> ans;

#define max4(a, b, c, d) max(max(a, b), max(c, d))
#define min4(a, b, c, d) min(min(a, b), min(c, d))

int main()
{
    memset(f, 0xcf, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    n = read<int>();
    char buf[3];
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        if (buf[0] == 't') oper[i] = oper[i + n] = op_plus;
        else oper[i] = oper[i + n] = op_multi;
        f[i][i] = f[i + n][i + n] = g[i][i] = g[i + n][i + n] = read<int>();
    }
    for (int l = 2; l <= n; l++) {
        for (int i = 1, j = l; j < n * 2; i++, j++) {
            for (int k = i; k < j; k++) {
                f[i][j] = max(f[i][j], max4(oper[k + 1](f[i][k], f[k + 1][j]),
                                            oper[k + 1](f[i][k], g[k + 1][j]),
                                            oper[k + 1](g[i][k], f[k + 1][j]),
                                            oper[k + 1](g[i][k], g[k + 1][j])));
                g[i][j] = min(g[i][j], min4(oper[k + 1](f[i][k], f[k + 1][j]),
                                            oper[k + 1](f[i][k], g[k + 1][j]),
                                            oper[k + 1](g[i][k], f[k + 1][j]),
                                            oper[k + 1](g[i][k], g[k + 1][j])));
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (f[i][i + n - 1] > maxans) {
            maxans = f[i][i + n - 1];
            ans.clear();
            ans.push_back(i);
        } else if (f[i][i + n - 1] == maxans) ans.push_back(i);
    }
    write(maxans, 10);
    for (unsigned i = 0; i < ans.size(); i++) write(ans[i], 32);
    return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/byy0ikm8.png)

---

## 作者：览遍千秋 (赞：19)

## 前言

题目提供者前来填坑。这是$IOI1998$的题目，一道经典的区间动规题

---

## 对断边的理解

一个$Polygon$相当于一个$n$个结点的环。在给定的$Polygon$中，取一个长度为$n-1$长度的链等价于删除了一条边。因此，不需要枚举断的边，正常对其进行区间动规即可。

---

## 阶段、状态的划分

和普通的区间动规一样，本题的阶段即是链的长度$i$，在每个阶段内，枚举起点$j$，边界条件$j≤2×n-i+1$

---

## 状态转移的特殊处理

本题中，涉及到乘法的处理，由于负数乘正数得到答案的特殊性，不能只用一个数组来记录最大值，还需要有一个数组来记录最小值，同时维护，最终算乘法的时候有用。

---

## 状态的表示

$opt[i][j]$代表长度为$i$，起点为$j$时的最大值。

$f[i][j]$代表长度为$i$，起点为$j$时的最小值。

---

## 状态转移方程

本题的状态转移方程较为特殊，需要进行分类讨论。

### 第一类·切割点边为加运算

$$opt[j][i+j-1]=max(opt[j][i+j-1],opt[j][k]+opt[k+1][i+j-1])$$

$$f[j][i+j-1]=min(f[j][i+j-1],f[j][k]+f[k+1][i+j-1]$$


### 第二类·切割点边为乘运算

$$opt[j][i+j-1]=max(opt[j][i+j-1],max(opt[j][k]*opt[k+1][i+j-1],max(f[j][k]*f[k+1][i+j-1],max(opt[j][k]*f[k+1][i+j-1],f[j][k]*opt[k+1][i+j-1]))))$$

$$f[j][i+j-1]=min(f[j][i+j-1],min(opt[j][k]*opt[k+1][i+j-1],min(f[j][k]*f[k+1][i+j-1],min(opt[j][k]*f[k+1][i+j-1],f[j][k]*opt[k+1][i+j-1]))))$$

---

## 注意点

本题中第$i$条边连接的是第$i-1$号和第$i$号点，第$1$条边连接的是第$n$号和第$1$号点。

---

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 102 
#define INF 0x7fffffff
bool c[maxn];
int r,num[maxn],n,opt[maxn][maxn],b[maxn],top,ans[maxn],f[maxn][maxn];
char sss;
inline void Init()
{
	cin>>n;
	for(register int i=1;i<=n;i++)
	{
		cin>>sss>>num[i];
		num[i+n]=num[i];
		if(sss=='t')
		{
			c[i]=c[i+n]=1;
		}
	}
}
inline void fill()
{
	for(register int i=1;i<=2*n;i++)
		for(register int j=1;j<=2*n;j++)
			opt[i][j]=0;
}
inline void Work()
{
	for(register int i=1;i<=2*n;i++)
		for(register int j=i+1;j<=2*n;j++)
		{
			opt[i][j]=-INF;
			f[i][j]=INF;
		}
	for(register int i=1;i<=2*n;i++)
	{
		if(c[i+1])
			opt[i][i+1]=f[i][i+1]=num[i]+num[i+1];
		else
			opt[i][i+1]=f[i][i+1]=num[i]*num[i+1];
		opt[i][i]=f[i][i]=num[i];
	}
	for(register int i=3;i<=n;i++)
	{	
		for(register int j=1;j<=2*n-i+1;j++)
		{
			r=j+i-1;
			for(register int k=j;k<r;k++)
			{
				if(c[k+1])
				{
					opt[j][r]=max(opt[j][r],opt[j][k]+opt[k+1][r]);
					f[j][r]=min(f[j][r],f[j][k]+f[k+1][r]);
				}
				else
				{
					opt[j][r]=max(opt[j][r],max(opt[j][k]*opt[k+1][r],max(f[j][k]*f[k+1][r],max(opt[j][k]*f[k+1][r],f[j][k]*opt[k+1][r]))));
					f[j][r]=min(f[j][r],min(opt[j][k]*opt[k+1][r],min(f[j][k]*f[k+1][r],min(opt[j][k]*f[k+1][r],f[j][k]*opt[k+1][r]))));
				}
			}
		}
	}
	int maxx=-0x7fffffff;
	for(register int i=1;i<=n;i++)
	{
		maxx=max(maxx,opt[i][i+n-1]);
	}
	cout<<maxx<<endl;
	for(register int i=1;i<=n;i++)
		if(opt[i][i+n-1]==maxx) cout<<i<<" ";
	cout<<endl;
}
int mian()
{
	Init();
	Work();
	return 0;
}
```

---

## 作者：Obito (赞：11)

###  ~~个人认为此题没有紫题难度~~

 _**总体来说是一个区间DP**_ 
 
#### 此题首先是一个环，要你进行删边操作，剩下的在经过运算得到一个最大值
## 我们先一步步来，由粗入细：
1.删去一条边，剩下的构成一条线，相当于求此的最大值，经典区间DP该有的样子；

2.现在大概想法有了，还有一个细节，就是当中会出现负数，负数*负数是可能超过当前的最大值的，所以我们不仅需要维护区间最大值，还有最小值，因为两个极小值相乘是可以超过最大值的。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100+10;
char c[maxn];
int a[maxn];
short int n;
int dp1[maxn][maxn],dp2[maxn][maxn];// dp1维护max,dp2维护min;
int x[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//把区间翻倍，这里如果看不懂，建议先去看合并石子会好一些
		cin>>c[i]>>a[i];
		c[i+n]=c[i];
		a[i+n]=a[i];
	}	
	int N=n*2-1;
	memset(dp1,0x80,sizeof(dp1));//极小值
	memset(dp2,0x3f,sizeof(dp2));//极大值
	for(int i=1;i<=N;i++){
		dp1[i][i]=a[i];
		dp2[i][i]=a[i];
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=N;i++){//区间DP开始
			int j=i+len-1;
			for(int k=i+1;k<=j;k++){
				if(c[k]=='x'){//乘法，维护max与min
				dp1[i][j]=max(dp1[i][j],max(dp1[i][k-1]*dp1[k][j],max(dp2[i][k-1]*dp1[k][j],max(dp1[i][k-1]*dp2[k][j],dp2[i][k-1]*dp2[k][j]))));
				dp2[i][j]=min(dp2[i][j],min(dp1[i][k-1]*dp1[k][j],min(dp2[i][k-1]*dp1[k][j],min(dp1[i][k-1]*dp2[k][j],dp2[i][k-1]*dp2[k][j]))));
				}
				else {//加法直接解决
				dp1[i][j]=max(dp1[i][j],dp1[i][k-1]+dp1[k][j]);		
				dp2[i][j]=min(dp2[i][j],dp2[i][k-1]+dp2[k][j]);
				}
			}
		}
	}
	int ans=-2147418364,cnt=0;//最后输出
	for(int i = 1;i <= n;i ++)ans = max(ans,dp1[i][i + n - 1]);
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
	if(dp1[i][i+n-1]==ans)
	cout<<i<<" ";
	}
	for(int i=1;i<=cnt;i++)cout<<x[i]<<" ";
	return 0;
}  
```

# 完结散花


---

## 作者：谦谦君子 (赞：8)

这是一道IOI的题（虽然是远古题），并且是紫题，还是比较吓人的。可是看完题目考虑是一道区间dp的题，其实似乎并没有到紫题的难度，（~~经老师点拨~~）他和石子合并[P1880](https://www.luogu.org/problem/P1880)比较的类似，可以通过一些操作变成石子合并，所以可以先做完P1880再来做这道题。

### 思路：
我们考虑维护一个最大值，一个最小值，做法与石子合并类似，还需维护一个最大子段积，具体见代码。

我们来看一下做题的过程：

### 首先，确定架构
一道动规题中，必有三个**关键点**：

- **阶段**--子问题

- **状态**--一组通解

- **决策**--转移更合算（由题目决定）

由此即可确定**循环顺序**:
```cpp
阶段
{
	状态
	{
		决策点
	}
}
```
### 其次，动态转移方程：
写动态转移方程前先得判断题目是否满足[最优化原理](https://baike.baidu.com/item/%E6%9C%80%E4%BC%98%E5%8C%96%E5%8E%9F%E7%90%86/797797?fr=aladdin)和[无后效性](https://baike.baidu.com/item/无后效性/1135283?fr=aladdin)（当然这题显然满足）然后确定决策对象并给决策对象划分阶段，接着对每个阶段决定状态，最后推出动态转移方程

于是根据思路推出：


- c[k]=='t'时，即两边之间加号相连时有：
```cpp
f1[i][j]=max(f1[i][j],f1[i][k]+f1[k+1][j]);
f2[i][j]=min(f2[i][j],f2[i][k]+f2[k+1][j]);
```
- c[k]=='x'时，即两边之间乘号相连时有：
```cpp
f1[i][j]=max(f1[i][j],max(f1[i][k]*f1[k+1][j],f2[i][k]*f2[k+1][j]));
f2[i][j]=min(f2[i][j],min(f1[i][k]*f1[k+1][j],min(f2[i][k]*f2[k+1][j],min(f1[i][k]*f2[k+1][j],f2[i][k]*f1[k+1][j]))));
```
**注意！！！：**

1. 在循环中一定是判断c[k+1] !
2. 在c[k]=='x'是，最小值可以将f1[i][k]*f1[k+1][j]排除


于是：动规部分代码（核心代码）：

```cpp
for (int l=2;l<=n;l++)										//阶段
{
	for (int i=1;i+l-1<=nn;i++)								//状态
	{
		int j=i+l-1;
		for (int k=i;k<j;k++)								//决策点
		{
			if (c[k+1]=='t')								//若为"+"号
			{
				f1[i][j]=max(f1[i][j],f1[i][k]+f1[k+1][j]);
				f2[i][j]=min(f2[i][j],f2[i][k]+f2[k+1][j]);
			}
			if (c[k+1]=='x')								//"×"号
			{
				f1[i][j]=max(f1[i][j],max(f1[i][k]*f1[k+1][j],f2[i][k]*f2[k+1][j]));
				f2[i][j]=min(f2[i][j],min(f1[i][k]*f1[k+1][j],min(f2[i][k]*f2[k+1][j],min(f1[i][k]*f2[k+1][j],f2[i][k]*f1[k+1][j]))));
				//其实可以写得简单一些，为了增强代码可读性QAQ
			}
		}
	}
}
```

##  全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
int a[maxn];
char c[maxn];
int f1[maxn][maxn],f2[maxn][maxn],x[maxn];	//f1维护的是最大值，f2维护的是最小值
int main()
{
	int n;
	cin>>n;
	memset(f2,0x7f,sizeof(f2));	//0x7f是int范围内的极大值
	memset(f1,0x80,sizeof(f1)); //0x80是int范围内的极小值
	for (int i=1;i<=n;i++)
	{
		cin>>c[i]>>a[i];
		c[i+n]=c[i];
		a[n+i]=a[i];
		f1[i][i]=a[i];
		f2[i][i]=a[i];
		f1[i+n][i+n]=a[i];
		f2[i+n][i+n]=a[i]; //初始化，注意要赋到2*n-1
	}
	int nn=2*n-1; //倍增思想，翻倍
	for (int l=2;l<=n;l++) //阶段
	{
		for (int i=1;i+l-1<=nn;i++) //状态
		{
			int j=i+l-1;
			for (int k=i;k<j;k++) //决策点
			{
				if (c[k+1]=='t') //若为"+"号
				{
					f1[i][j]=max(f1[i][j],f1[i][k]+f1[k+1][j]);
					f2[i][j]=min(f2[i][j],f2[i][k]+f2[k+1][j]);
				}
				if (c[k+1]=='x') //"×"号
				{
					f1[i][j]=max(f1[i][j],max(f1[i][k]*f1[k+1][j],f2[i][k]*f2[k+1][j]));
					f2[i][j]=min(f2[i][j],min(f1[i][k]*f1[k+1][j],min(f2[i][k]*f2[k+1][j],min(f1[i][k]*f2[k+1][j],f2[i][k]*f1[k+1][j]))));
					//增强代码可读性QAQ
				}
			}
		}
	}
	int ans=-2147418364,cnt=0;
	for (int i=1;i<=n;i++)
	{
		ans=max(ans,f1[i][i+n-1]); //得出ans
	}
	cout<<ans<<endl;
	for (int i=1;i<=n;i++)
	{
		if (f1[i][i+n-1]==ans)
		{
			cout<<i<<" "; //输出所有可能的被清除后的边仍能得到最高得分的列表
		}
	}
	return 0;
}
```




---

## 作者：IceLocke (赞：5)

### 【解题思路】
如果设 dp[l, r] 为区间 [l, r] 的最大值（其中，0 <= l, r <= n），这样不满足最优子结构，因为节点之间的操作为 op ∈ {+, *}，很容易发现如果当某两个很小的负数相乘，积为正，其结果有可能会大于两个正数相乘的结果，因此我们也需要考虑到负数的情况。

所以，我们需要分类讨论一下最大值可能存在的几种情况（k 为决策， k ∈ [l, r]）。：

① 当操作为 + 的时候，区间 [l, r] 最大值肯定是区间 [l, k] 与区间 [k+1, r] 最大值之和的最大值。

② 当操作为 * 的时候，区间 [l, r] 的最大值可能是区间 [l, k] 与区间 [k+1, r] 的最大值之积的最大值；也可能是区间 [l, k] 与区间 [k+1, r] 的小值之积（考虑到两个负数之积比两个正数之积的情况）的最大值。

从上面说明的来看，我们还需要一个数组存区间 [l, r] 的最小值，对于最小值的几种情况，我们这样讨论：

① 当操作为 + 的时候，区间 [l, r] 最小值肯定是区间 [l, k] 与区间 [k+1, r] 最小值之和的最小值。

② 当操作为 * 的时候，区间 [l, r] 的最小值可能是区间 [l, k] 的最小值与区间 [k+1, r] 的最大值之积的最小值；也可能是区间 [l, k] 的最大值与区间 [k+1, r] 的最小值之积的最小值；还可能是区间 [l, k] 的最小值与区间 [k+1, r] 的最小值之积的最小值。

这时，我们设 dp[l, r, 0]表示区间最大值，设 dp[l, r, 1] 表示区间最小值，从上面几种情况可以总结出状态转移方程：  

![](https://s0.wp.com/latex.php?latex=+++dp%5Bl%2C+r%2C+0%5D+%3D+max%5Cbegin%7BBmatrix%7D++max%28dp%5Bl%2C+k%2C+0%5D+%2B+dp%5Bk%2B1%2C+r%2C+0%5D%29%2C+%28operator+%3D+%2B%29%5C%5C%5C%5C++max%5Cleft%5C%7B%5Cbegin%7Bmatrix%7D++dp%5Bl%2C+k%2C+0%5D+%2A+dp%5Bk%2B1%2C+r%2C+0%5D%5C%5C++dp%5Bl%2C+k%2C+1%5D+%2A+dp%5Bk%2B1%2C+r%2C+1%5D++%5Cend%7Bmatrix%7D%5Cright.++%2C%28operator%3D+%2A%29++%5Cend%7BBmatrix%7D+++&bg=ffffff&fg=000000&s=0)  
  
![](https://s0.wp.com/latex.php?latex=+++dp%5Bl%2C+r%2C+1%5D+%3D+min%5Cbegin%7BBmatrix%7D++min%28dp%5Bl%2C+k%2C+1%5D+%2B+dp%5Bk%2B1%2C+r%2C+1%5D%29%2C+%28operator+%3D+%2B%29%5C%5C%5C%5C++min%5Cleft%5C%7B%5Cbegin%7Bmatrix%7D++dp%5Bl%2C+k%2C+1%5D+%2A+dp%5Bk%2B1%2C+r%2C+1%5D%5C%5C++dp%5Bl%2C+k%2C+1%5D+%2A+dp%5Bk%2B1%2C+r%2C+0%5D%5C%5C++dp%5Bl%2C+k%2C+0%5D+%2A+dp%5Bk%2B1%2C+r%2C+1%5D++%5Cend%7Bmatrix%7D%5Cright.%2C+%28operator+%3D+%2A%29++%5Cend%7BBmatrix%7D+++&bg=ffffff&fg=000000&s=0)

有了转移方程之后，就比较好解决了，我们现在需要把环变成链来考虑。如果是朴素的枚举每个去除的边，时间复杂度为 O(n^4)，并不理想，我们有一个更好的降低时间复杂度的方法：

对于一个环，我们切掉其中一条边变成一个链，然后把这个链的长度延长两倍，然后对这一条链进行 DP。

### 【代码】
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 0x7fffff
using namespace std;

int n, tot = 0, ans = -32768,
	num[51], dp[101][101][2];

char op[101];

//初始化
void init() {
	for(int i = 1; i <= n * 2; i++) {
		for(int j = i; j <= n * 2; j++) {
			dp[i][j][0] = -INF;
			dp[i][j][1] = INF;
		}
	}
	for(int i = 1; i <= n; i++) {
		dp[i][i][0] = num[i];
		dp[i][i][1] = num[i];
		dp[i+n][i+n][0] = num[i];
		dp[i+n][i+n][1] = num[i];
		op[i+n] = op[i];
	}
}

int main() {
	
	ios::sync_with_stdio(false);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++)
		cin >> op[i] >> num[i];
	
	init();
	
    //枚举区间长度
	for(int len = 2; len <= n; len++) {
    	//枚举区间左端点
		for(int l = 1; l <= 2 * n - len + 1; l++) {
        	//根据阶段 len 和状态 l 推出状态 r
			int r = l + len - 1;
            //枚举决策
			for(int k = l; k < r; k++) {
				if(op[k+1] == 't') {
                	//这里对应着操作为 + 的情况，详细解释看上面
					dp[l][r][0] = max(dp[l][r][0], dp[l][k][0] + dp[k+1][r][0]);
					dp[l][r][1] = min(dp[l][r][1], dp[l][k][1] + dp[k+1][r][1]);
				}
				else {
                	//这里对应着操作为 * 的情况，详细解释看上面
					dp[l][r][0] = max(dp[l][r][0], max(dp[l][k][0] * dp[k+1][r][0], dp[l][k][1] * dp[k+1][r][1]));
                    dp[l][r][1] = min(dp[l][r][1], min(dp[l][k][1] * dp[k+1][r][1], min(dp[l][k][1] * dp[k+1][r][0], dp[l][k][0] * dp[k+1][r][1])));
				}
			}
		}
	}
	
    //循环取答案
	for(int i = 1; i <= n+1; i++) {
		ans = max(dp[i][i+n-1][0], ans);
	}
	
	cout << ans << endl;
	
    //第二问
	for(int i = 1; i <= n; i++) {
		if(dp[i][i+n-1][0] == ans)
			cout << i << " ";
	}
	
	return 0;
}
```

---

## 作者：zyj_Orz (赞：3)

## 区间DP题。

~~感觉紫题难度还是有点过了吧？~~

此题难就难在要考虑乘法，而且负数乘负数还等于正数，否则与[石子合并](https://www.luogu.org/problemnew/show/P1880)相似

大致思路就是建两个二维数组dpmax【i】【j】表示i到j运算得到的最大值，dpmin【i】【j】表示其运算得到的最小值


这时候就大致可以得出**动态转移方程**了，如下

------------
1.首先肯定要破环为链。

------------
2.此时设置一个长度l自2至n枚举

------------
3.此时i从1枚举至n-l+1，j此时则为i+l-1。

------------
4.如果为乘法，考虑最大值负负得正的情况；最小值分类讨论即可；如果为加法，则与合并石子思路相似。即```dp[i][j] = max(dp[i][k] + dp[k+1][j] + dp(i,j));其中，1<=i<=<=k<j<=N。```

------------



故状态转移方程代码如下：

```
 for(int l=2;l<=n;l++)
    for(int i=1;i<=2*n+1-l;i++)
    {
        int j=i+l-1;
        for(int k=i;k<j;k++)
        {
            if(fh[k+1]=='x')
            {
                dpmax[i][j]=max(dpmax[i][j],max(dpmax[i][k]*dpmax[k+1][j],dpmin[i][k]*dpmin[k+1][j])),
                dpmin[i][j]=min(dpmin[i][j],min(min(dpmax[i][k]*dpmin[k+1][j],dpmin[i][k]*dpmax[k+1][j]),dpmin[i][k]*dpmin[k+1][j])); 
            }
            else
            {
                dpmax[i][j]=max(dpmax[i][j],dpmax[i][k]+dpmax[k+1][j]);
                dpmin[i][j]=min(dpmin[i][j],dpmin[i][k]+dpmin[k+1][j]);
            }           
        }
    }
```

得出答案后，再输出所有f【i】【i+n-1】=ans的i即可。

------------


发现了吗？实际上代码很精简的，IOI的题行数就20来行。只要你有心，IOI难度在你眼里都将是水题！


```
#include<bits/stdc++.h>
using namespace std;
int n,a[110],dpmax[110][110],dpmin[110][110],ans=-999999999;
char fh[110];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin>>fh[i]>>a[i];
        fh[i+n]=fh[i],a[i+n]=a[i];
    }//破坏成链 
    for(int i=1;i<=2*n;i++)
    	for(int j=1;j<=2*n;j++){
    	if(i==j) dpmax[i][j]=a[i],dpmin[i][j]=a[i];
    	else dpmax[i][j]=-0x7f7f,dpmin[i][j]=0x7f7f;
    	}//初始化 
    for(int l=2;l<=n;l++)
    	for(int i=1;i<=2*n+1-l;i++){
	        int j=i+l-1;
	        for(int k=i;k<j;k++)
	            if(fh[k+1]=='x') dpmax[i][j]=max(dpmax[i][j],max(dpmax[i][k]*dpmax[k+1][j],dpmin[i][k]*dpmin[k+1][j])),dpmin[i][j]=min(dpmin[i][j],min(min(dpmax[i][k]*dpmin[k+1][j],dpmin[i][k]*dpmax[k+1][j]),dpmin[i][k]*dpmin[k+1][j])); 
	            else dpmax[i][j]=max(dpmax[i][j],dpmax[i][k]+dpmax[k+1][j]),dpmin[i][j]=min(dpmin[i][j],dpmin[i][k]+dpmin[k+1][j]);       
	    }//核心代码 
    for(int i=1;i<=n;i++) ans=max(ans,dpmax[i][i+n-1]);
    cout<<ans<<endl;//最大值 
    for(int i=1;i<=n;i++) if(dpmax[i][i+n-1]==ans) cout<<i<<" ";
}
```

------------


>PPS：这是[@M_sea](https://www.luogu.org/space/show?uid=38370) dalao給我们讲解的，深入浅出Orz

>PPPS：应该没有题解与这个相似吧？因为我们全机房都是听的M_sea dalao讲解的，所以可能机房会有与我相似的题解投上来QAQ

---

## 作者：米奇奇米 (赞：2)

## 题解 - $P4342 \ [IOI1998]\ Polygon$
### 题目意思
[$lg\ 4342$](https://www.luogu.com.cn/problem/P4342)

### $Sol$
* 一道比较经典的区间$DP$题。视乎远古$IOI$特别喜欢区间$DP$

* 首先对序列断环为链，即$a_{i+n}=a_i$

* 状态设立很简单
	* $f_{i,j}$表示$[i,j]$能合成的最大值
	* $g_{i,j}$表示$[i,j]$能合成的最小值
	* 为什么维护最小值呢，因为对于乘法，最大值$=$最大值$\times$最大值 $=$最小值$\times$最小值 

* 转移也很基础啊：

	* 如果是$t$，那么$f_{i,j}=\max (f_{i,k}+f_{k+1,j})$，$g_{i,j}=\min (g_{i,k}+g_{k+1,j})$
	* 如果是$x$，那么
				- $f_{i,j}=\max(f_{i,k}\times f_{k+1,j},g_{i,k}\times g_{k+1,j})$
				- $g_{i,j}=\min(f_{i,k}\times g_{k+1,j},g_{i,k}\times f_{k+1,j},g_{i,k}\times g_{k+1,j})$

* 答案就是$\max_{i\leq n} (f_{i,i+n})$
* 对于第二问就$\ O(n)$扫一遍就可以了。
* 复杂度：$\ O(2\times n^3)$

### $Code$

```c
#include <bits/stdc++.h>
#define int long long 
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=105;

int n,m,ans,f[N][N],g[N][N];
int a[N],b[N];
char ch[N];

inline int min(int x,int y)
{
	if(x<y) return x;
	return y;
}

inline int max(int x,int y)
{
	if(x>y) return x;
	return y;
}

signed main()
{
	scanf("%lld",&n);
	memset(f,-63,sizeof(f));
	memset(g,63,sizeof(g));
	for ( int i=1;i<=n;i++ )
	{
		cin>>ch[i];
		scanf("%lld",&a[i]);
		ch[i+n]=ch[i];
		a[i+n]=a[i];
		f[i][i]=f[i+n][i+n]=a[i];
		g[i][i]=g[i+n][i+n]=a[i];
	}
	m=n*2-1;
	for ( int l=2;l<=m;l++ ) 
		for ( int i=1;i+l-1<=m;i++ ) 
		{
			int j=i+l-1;
			for ( int k=i;k<j;k++ ) 
			{
				if(ch[k+1]=='t') 	
				{
					f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]);
					g[i][j]=min(g[i][j],g[i][k]+g[k+1][j]);
				}
				if(ch[k+1]=='x')
				{
					f[i][j]=max(f[i][j],f[i][k]*f[k+1][j]);
					f[i][j]=max(f[i][j],g[i][k]*g[k+1][j]);
					g[i][j]=min(g[i][j],g[i][k]*f[k+1][j]);
					g[i][j]=min(g[i][j],f[i][k]*g[k+1][j]);
					g[i][j]=min(g[i][j],g[i][k]*g[k+1][j]);
				}
			}
		}
	ans=-1e12;
	for ( int i=1;i<=n;i++ ) ans=max(ans,f[i][i+n-1]);
	printf("%lld\n",ans); 
	int sum=0;
	for ( int i=1;i<=n;i++ ) 
		if(f[i][i+n-1]==ans) printf("%lld ",i); 
	return 0;
}
```


---

## 作者：LevenKoko (赞：2)

### 很早就看到这题了...但因为有个IOI标志，拖到现在才做
### [同步发表于这儿](https://www.cnblogs.com/zhenglw/p/10754623.html)

 UPD于刚发布1min后：刚刚瞄了一眼其他人题解，貌似这种做法有和我类似的，不过码风没法和我比啊！！！

 由于是以前在书上看到的，就没有想过其他算法，直接区间DP了...
 
 方程式也挺好想的
 
 跟我们平时做数学题求几个数乘积最大差不多
 
 
> 最大的*最大的

> 最小的*最小的（可能是负数）

这样两种情况

由于求最大中要用到最小值，我们在维护最大同时维护最小

> 最小的*最小的

> 最小的*最大的

也是两种情况

再考虑加法

>最大：最大+最大

>最小：最小+最小

各有一种情况

Tip 面所述的类似于最大*最大都是左区间最大/小 和右区间最大/小

表达起来大概是这样的
```cpp
	for(int len=2;len<=n;++len){
		for(int i=1;i+len-1<=2*n;++i){
			int j=i+len-1;
			for(int k=i;k<j;++k){
				if(opt[k+1]=='x')
					cmax(dpd[i][j],dpd[i][k]*dpd[k+1][j],dpx[i][k]*dpx[k+1][j]),
					cmin(dpx[i][j],dpd[i][k]*dpx[k+1][j],dpx[i][k]*dpd[k+1][j],dpx[i][k]*dpx[k+1][j]);
				else
					cmin(dpx[i][j],dpx[i][k]+dpx[k+1][j]),
					cmax(dpd[i][j],dpd[i][k]+dpd[k+1][j]);
			}
		}
	}
```

最后的代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define inf (0x7fffffff)
#define writeln(x)  write(x),puts("")
#define writep(x)   write(x),putchar(' ')
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}int n,a[155],dpx[155][155],dpd[155][155],ans=-inf;char opt[55];
inline void cmin(int &a,int b){if(b<a) a=b;}
inline void cmin(int &a,int b,int c){cmin(a,b),cmin(a,c);}
inline void cmin(int &a,int b,int c,int d){cmin(a,b,c),cmin(a,d);}
inline void cmax(int &a,int b){if(a<b)a=b;}
inline void cmax(int &a,int b,int c){cmax(a,b),cmax(a,c);}
int main(){
	n=read();
	for(register int i=1;i<=n;++i) cin>>opt[i]>>a[i];
	for(register int i=1;i<=n;++i) opt[i+n]=opt[i],a[i+n]=a[i];
	for(int i=1;i<=n*2;++i)
		for(int j=1;j<=n*2;++j)
			(i==j)?(dpx[i][i]=dpd[i][i]=a[i]):(dpd[i][j]=-inf,dpx[i][j]=inf);
	for(int len=2;len<=n;++len){
		for(int i=1;i+len-1<=2*n;++i){
			int j=i+len-1;
			for(int k=i;k<j;++k){
				if(opt[k+1]=='x')
					cmax(dpd[i][j],dpd[i][k]*dpd[k+1][j],dpx[i][k]*dpx[k+1][j]),
					cmin(dpx[i][j],dpd[i][k]*dpx[k+1][j],dpx[i][k]*dpd[k+1][j],dpx[i][k]*dpx[k+1][j]);
				else
					cmin(dpx[i][j],dpx[i][k]+dpx[k+1][j]),
					cmax(dpd[i][j],dpd[i][k]+dpd[k+1][j]);
			}
		}
	}
	for(int i=1;i<=n;++i) cmax(ans,dpd[i][i+n-1]);writeln(ans);
	for(int i=1;i<=n;i++) if(dpd[i][i+n-1]==ans) writep(i);
	return 0;
}

```



---

## 作者：Reanap (赞：1)

这道题
~~显然~~
是一个区间dp，我们可以非常轻易地联想到这道题
[石子合并](https://www.luogu.com.cn/problem/P1880) 。

他们都是环并且都只能选相邻的两个东西进行合并，所以这应该是一道区间dp板子题。

想当然地列出dp方程：

在$i \leq k \leq j - 1$且$opt_{k+1} = *$时

$dp_{i,j} = max(dp_{i,k} * dp_{k+1,j})$

在$i \leq k \leq j - 1$且$opt_{k+1} = +$时

$dp_{i,j} = max(dp_{i,k} + dp_{k+1,j})$

但是它其实是错误的，因为在数据中允许存在负数，所以最大值不一定由最大值得来，反而有可能由最小值得来(负负得正)，最小值同理。

~~由于dp式过长，详见代码~~

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long // 虽然方便，但慎用，滥用会爆空间
using namespace std;
int n , MIN[105][105] , MAX[105][105];
struct node {
	int data;
	char opt;
}cir[105];
signed main() {
	scanf("%lld" , &n);
	for (int i = 1; i <= n; ++i) {
		char s = getchar();
		while (s != 't' && s != 'x') s = getchar();
		cir[i].opt = s;
		scanf("%lld" , &cir[i].data);
		cir[i + n] = cir[i];//把环展开
	}
	memset(MAX , 128 , sizeof MAX);
	memset(MIN , 127 , sizeof MIN);//最大值赋为极小值，最小为极大
	for (int i = 1; i <= n * 2; ++i) MAX[i][i] = MIN[i][i] = cir[i].data;//初始化
	for (int len = 2; len <= n; ++len) {
		for (int i = 1; i + len - 1 <= n * 2; ++i) {
			int j = i + len - 1;
			for (int k = i; k < j; ++k) {
				if(cir[k + 1].opt == 't') {
					MAX[i][j] = max(MAX[i][j] , MAX[i][k] + MAX[k + 1][j]);
					MIN[i][j] = min(MIN[i][j] , MIN[i][k] + MIN[k + 1][j]);//加法不影响
				}
				else {
					MAX[i][j] = max(MAX[i][j] , max(MAX[i][k] * MAX[k + 1][j] , max(MIN[i][k] * MIN[k + 1][j] , max(MIN[i][k] * MAX[k + 1][j] , MAX[i][k] * MIN[k + 1][j]))));
					MIN[i][j] = min(MIN[i][j] , min(MAX[i][k] * MAX[k + 1][j] , min(MIN[i][k] * MIN[k + 1][j] , min(MIN[i][k] * MAX[k + 1][j] , MAX[i][k] * MIN[k + 1][j]))));//有四种情况，最大和最大，最大和最小，最小和最大，最小和最小，都有可能是最优的
				}
			}
		}
	}
	int l = 0;
	for (int i = 1; i <= n; ++i) {
		if(l == 0 || MAX[i][i + n - 1] > MAX[l][l + n - 1]) l = i;//寻找最优处
	}
	printf("%lld\n" , MAX[l][l + n - 1]);
	for (int i = 1; i <= n; ++i) {
		if(MAX[i][i + n - 1] == MAX[l][l + n - 1]) printf("%lld " , i);
	}//断开的地方就是没有计算的地方，即序列的开头
	return 0;
}

```

---

## 作者：Azuree (赞：1)

[查看原题请戳这里](https://www.luogu.org/problem/P4342)

emmmm......

感觉和合并石子那个题目还是非常相似的。

我们用f[i][j]表示将区间[i,j]合并后能获得的最大分数。对于环的处理，我们可以在[n+1,n+n]区间将原始分数重新复制一份，以达到短环成链的效果，这里就不多赘述了。

但是，我们发现，如果两个极小的负数相乘，那么就可能会获得一个比较大的正数，所以我们在储存最大值的同时要用g[i][j]储存每一种状态的最小值。

如果两个区间用加法连接，那么转移的方法是这样的：

```cpp
f[i][j] = max(f[i][j],f[i][k] + f[k + 1][j]);
g[i][j] = min(g[i][j],g[i][k] + g[k + 1][j]);
```
如果两个区间用乘法连接，我们就要考虑负负得正的情况了，转移的方法是这样的：

```cpp
f[i][j] = Max(f[i][j],f[i][k] * f[k + 1][j],g[i][k] * g[k + 1][j],f[i][k] * g[k + 1][j],g[i][k] * f[k + 1][j]);
g[i][j] = Min(g[i][j],f[i][k] * f[k + 1][j],g[i][k] * g[k + 1][j],f[i][k] * g[k + 1][j],g[i][k] * f[k + 1][j]);
```

这就是DP转移的方程了。

注意，由于初始分数可能为负数，所以我们一定要初始化f与g为-INF和INF。

code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define qwq printf("qwq\n");

using namespace std;

int read()
{
	register int x = 0,f = 1;register char ch;
	ch = getchar();
	while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
	while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}

int n,f[105][105],ans,tj[105],fh[105],num[105],p,g[105][105];

char c,s[105];

int Max(int a,int b,int c,int d,int e)
{
	return max(a,max(max(b,c),max(d,e)));
}

int Min(int a,int b,int c,int d,int e)
{
	return min(a,min(min(b,c),min(d,e)));
}

int main()
{
	n = read();
	for(int i = 1; i <= n + n; i++) 
		for(int j = 1; j <= n + n; j++)
			f[i][j] = -INF,g[i][j] = INF;
//	rep(i,1,n) f[0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		cin >> s[i] >> f[i][i];
		s[i + n] = s[i];
		f[i + n][i + n] = f[i][i];
		g[i][i] = g[i + n][i + n] = f[i][i];
	}
	for(int l = 1; l < n; l++)
		for(int i = 1; i + l <= n + n; i++)
		{
			int j = i + l;
			for(int k = i; k < j; k++)
			{
				if(s[k + 1] == 't')
				{
					f[i][j] = max(f[i][j],f[i][k] + f[k + 1][j]);
					g[i][j] = min(g[i][j],g[i][k] + g[k + 1][j]);
				}
				else
				{
					f[i][j] = Max(f[i][j],f[i][k] * f[k + 1][j],g[i][k] * g[k + 1][j],f[i][k] * g[k + 1][j],g[i][k] * f[k + 1][j]);
					g[i][j] = Min(g[i][j],f[i][k] * f[k + 1][j],g[i][k] * g[k + 1][j],f[i][k] * g[k + 1][j],g[i][k] * f[k + 1][j]);
				}
			}
		}
	int ans = -INF;
	for(int i = 1; i <= n; i++) ans = max(ans,max(f[i][i + n - 1],g[i][i + n - 1]));
	printf("%d\n",ans);
	for(int i = 1; i <= n; i++)
	{
		if(f[i][i + n - 1] == ans) printf("%d ",i);
		else if(g[i][i + n - 1] == ans) printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：noall (赞：1)


[题目](https://img.langlangago.xyz/2019/09/22/5d864d203cd6e.pdf)

### 思路

这题算是一个能一眼看出做法的题吧……也许

首先因为环形+区间问题，一般就是要考虑区间DP吧。所以我们肯定要将环拆开。

而且这个题和**石子合并**很像，只不过有了负数，而且我们都知道负负得正。

我们设$f_{i,j}$表示区间最大，$g_{i,j}$表示区间最小。

那么转移方程就可以参照石子合并，很容易就得出。

所以答案就是$\max_{i=1}^{n}f[i][i+n-1]$，然后输出所有$f[i][i+n-1]==ans$中的$i$即可。

_~~冯神：这不是一道傻逼题吗?~~_……咳咳。

### code

```cpp
#include<cstdio>
#include<iostream>

const int maxn=1e2+10;
const int uus=0x7fffffff;

int n,a[maxn],f[maxn][maxn]/* i -> j max */,g[maxn][maxn]/* i -> j min */;
char opt[maxn];

inline int read(){
	char ch=getchar();int x=0,f=1;
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

inline void pmax(int& a,int b){
	if(a<b) a=b;
	return ;
}

inline void pmin(int& a,int b){
	if(a>b) a=b;
	return ;
}

int main(){
	n=read();
	for(register int i=1;i<=n;i++){
		std::cin>>opt[i];a[i]=read();
		opt[i+n]=opt[i],a[i+n]=a[i];
	}
	n<<=1;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			if(i==j) f[i][j]=g[i][j]=a[i];
			else f[i][j]=-uus,g[i][j]=uus;
	for(register int t=2;t<=(n>>1);t++){
		for(register int i=1;i<=n-t+1;i++){
			int j=i+t-1;
			for(register int k=i;k<j;k++){//头晕眼花，所以换了换行
				if(opt[k+1]=='x'){// *
                    pmin( g[i][j] , f[i][k] * g[k+1][j] );
					
                    pmin( g[i][j] , g[i][k] * f[k+1][j] );
					
                    pmax( f[i][j] , g[i][k] * g[k+1][j] );
					
					pmax( f[i][j] , g[i][k] * g[k+1][j] );
					
					pmax( f[i][j] , f[i][k] * f[k+1][j] );
				}
				else{// +
					pmax( f[i][j] , f[i][k] + f[k+1][j] );
					pmin( g[i][j] , g[i][k] + g[k+1][j] );
				}
			}
		}
	}
	n>>=1;
	int ans=-uus;
	for(register int i=1;i<=n;i++)
		if( f[i][i+n-1]>ans ) ans=f[i][i+n-1];
	printf("%d\n",ans);
	for(register int i=1;i<=n;i++)
		if( f[i][i+n-1]==ans ) printf("%d ",i);
	return 0;
}
```



---

## 作者：Object_ (赞：1)

**易错点：**
- 由于需要在一开始减少一条边且相邻输入数据在图上相邻，需要将输入的运算符复制一倍后向左平移一个单位.
- 乘法的状态转移需要注意负负得正，也就是说，最大值可以由两个最小值推导出来。因此，需要保存最小值，也就是使用f[l][r][0/1]分别保存最大/最小值。而最小值也有可能由多种情况推导出来，因此如果拿不准可以四种情况都尝试进行转移.
- 输出答案时不能直接输出f[1][n][0]，因为题目需要断环并加一倍在后面.

------------

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=120,INF=1<<30;
int f[MAXN][MAXN][2];
char opt[MAXN];
int a[MAXN];
int main(){
	for(int i=0;i<MAXN;i++)
	for(int j=0;j<MAXN;j++){
		f[i][j][0]=-INF;
		f[i][j][1]=INF;
	}
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		char nowOpt;int nowValue;
		cin>>nowOpt>>nowValue;
		opt[i]=opt[i+n]=nowOpt;
		a[i]=a[i+n]=nowValue;
		f[i][i][0]=f[i][i][1]=a[i];
		f[i+n][i+n][0]=f[i+n][i+n][1]=a[i];
	}
	for(int i=1;i<2*n;i++)
		opt[i]=opt[i+1];
	for(int len=2;len<=n;len++){
		for(int l=1;l<=2*n-len+1;l++){
			int r=l+len-1;
			for(int k=l;k<r;k++){
				char nowOpt=opt[k];
				if(nowOpt=='t'){
					f[l][r][0]=max(f[l][r][0],f[l][k][0]+f[k+1][r][0]);
					f[l][r][1]=min(f[l][r][1],f[l][k][1]+f[k+1][r][1]);
				}else{
					f[l][r][0]=max(f[l][r][0],f[l][k][0]*f[k+1][r][0]);
					f[l][r][0]=max(f[l][r][0],f[l][k][1]*f[k+1][r][1]);
					f[l][r][1]=min(f[l][r][1],f[l][k][1]*f[k+1][r][0]);
					f[l][r][1]=min(f[l][r][1],f[l][k][0]*f[k+1][r][1]);
				}
			}
		}
	}
	int nowAns=-INF;
	vector<int> scc;
	for(int i=1;i<=n;i++){
		if(f[i][i+n-1][0]>nowAns){
			scc.clear();
			scc.push_back(i);
			nowAns=f[i][i+n-1][0];
		}else if(f[i][i+n-1][0]==nowAns){
			scc.push_back(i);
		}
	}
	cout<<nowAns<<endl;
	for(int i=0;i<scc.size();i++){
		int nowValue=scc.at(i);
		cout<<nowValue<<" ";
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：一只野生蒟蒻 (赞：1)

这道题看上去吓人，其实就是一个简单的区间DP

先来看两道PJ题：

最大子段和: dp[i]表示：以第i个数结尾的子段所能获得的最大和。于是就有：dp[i]=max(dp[i-1]+a[i],a[i]); 

最大子段乘积： dp1[i]表示：以第i个数结尾的子段所能获得的最大乘积。但我们注意到乘积不一定是要由最大的两个数相乘得来，也可以由最小的两个数相乘得来。于是我们又维护一个dp2[i]:以第i个数结尾的子段所能获得的最小乘积。 

这两道PJ的题结合后，再加上一点区间DP（类似石子合并）就能愉快AC了！~~（PJ+PJ=IOI?）~~

下面上代码：
```c
#include <bits/stdc++.h>
using namespace std;
int n,a[104],dp1[104][104],dp2[104][104];
//dp1[i][j]表示从i到j的运算最大值
//dp2[i][j]表示从i到j的运算最小值
char b[104];
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>b[i]>>a[i];
		a[i+n]=a[i];
		b[i+n]=b[i];
		//环变链，加长一倍 
	}
	memset(dp1,0x80,sizeof(dp1));//极小值
	memset(dp2,0x3f,sizeof(dp2));//极大值
	for (int i=1;i<2*n;i++)
		dp1[i][i]=dp2[i][i]=a[i];//每个跨度为1的区间，最大最小值都是它自己 
		
	for (int l=2;l<=n;l++)//枚举区间长度 
		for (int i=1;i+l-1<2*n;i++)//起点 
		{
			int j=i+l-1;//终点 
			for (int k=i+1;k<=j;k++)//由于循环的是符号，所以从i+1到j 
			{
				if (b[k]=='t')//加号 
				{
					dp1[i][j]=max(dp1[i][j],dp1[i][k-1]+dp1[k][j]);//维护最大值 
                    dp2[i][j]=min(dp2[i][j],dp2[i][k-1]+dp2[k][j]);//维护最小值 
				}
				else//乘号 
				{
					dp1[i][j]=max(dp1[i][j],max(dp1[i][k-1]*dp1[k][j],dp2[i][k-1]*dp2[k][j]));//维护最大值 
					dp2[i][j]=min(dp2[i][j],min(dp1[i][k-1]*dp1[k][j],min(dp2[i][k-1]*dp2[k][j],min(dp1[i][k-1]*dp2[k][j],dp2[i][k-1]*dp1[k][j]))));
					//维护最小值 
				}
			}
		}
	int ans=-1e8;
	for (int i=1;i<=n;i++)
		ans=max(ans,dp1[i][i+n-1]);//第一问 
	cout<<ans<<endl;
	for (int i=1;i<=n;i++)
		if (ans==dp1[i][i+n-1])//第二问 
			cout<<i<<' ';
	return 0;
}
```



---

## 作者：fletmer (赞：1)

## 每做一道题都要积累一道题的经验，记忆思考的过程

### 一道经典的区间DP，同NOI1995石子合并大同小异，覆盖面广，难度适中，码量适中，解法自然

#### 扯句废话，区间DP以区间长度为状态，从小区间转移向大区间

#### 1. 首先是对于环的处理，空间开2倍，把环复制成两倍的链，op[]存运算符，num[]存节点数字。如果暴力枚举断点复杂度就会升级
----
```cpp
for(int i=1;i<=n;i++){
		cin>>op[i]>>num[i];
		op[i+n]=op[i],num[i+n]=num[i];
	}
```
----

#### 2.然后是对 |阶段，状态，决策| 的确定。和石子合并的不同之处在于，此题出现了负数运算，可能的特殊情况是两负数相乘结果较大，所以DP[i][j][0]表示从i到j的最大运算结，DP[i][j][1]存最小运算结果，DP[i][j]当然存初始节点值,所以，对DP数组初始化：
----
需要注意的是，题上给出了运算结果的上下界：“对于任何一系列的操作，顶点数字都在[-32768,32767]的范围内。”，最开始我初始化为-INF，INF，INF=0x7fffffff，结果炸了三个点

```cpp
for(int i=1;i<=2*n;i++){
		for(int j=1;j<=2*n;j++){
			if(i==j) dp[i][i][0]=dp[i][i][1]=num[i];
			else dp[i][j][1]=32768,dp[i][j][0]=-32769;
		}
	}
```

----

第一维枚举阶段，即区间长度

第二维枚举区间左端点

第三维自然是进行决策，可以想象，**一条链上的运算，必然存在一个点，使这个节点左边所有点合并完成，右边所有点合并完成后才合并改节点**，所以枚举此节点决策

#### 3.关于状态转移方程，很好懂啊（注意思维的严密）：
---


```cpp

乘法
dp[l][r][0]=max(dp[l][r][0],max(dp[l][k][0]*dp[k+1][r][0],dp[l][k][1]*dp[k+1][r][1]));
dp[l][r][1]=min(dp[l][r][1],min(dp[l][k][1]*dp[k+1][r][0],dp[l][k][0]*dp[k+1][r][1]));

-----------

加法
dp[l][r][0]=max(dp[l][r][0],dp[l][k][0]+dp[k+1][r][0]);
dp[l][r][1]=min(dp[l][r][1],dp[l][k][1]+dp[k+1][r][0]);

```
---

#### 4.关于最大结果的判断：
枚举所有区间长度为n的区间最大值DP[i][j][0]即可

---

```cpp

int maxn=-32769;
	for(int i=1;i<=n+1;i++){
		int l=i,r=l+n-1;
		maxn=max(maxn,dp[l][r][0]);
	}
```
---
然后再枚举断链处就吼了。



```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#define SIZE 55
using namespace std;
int n;
char x; int y;
int num[SIZE<<1];
char op[SIZE<<1];
int dp[SIZE<<1][SIZE<<1][2];

//x 120
//t 116
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>op[i]>>num[i];
		op[i+n]=op[i],num[i+n]=num[i];
	}
	for(int i=1;i<=2*n;i++){
		for(int j=1;j<=2*n;j++){
			if(i==j) dp[i][i][0]=dp[i][i][1]=num[i];
			else dp[i][j][1]=32768,dp[i][j][0]=-32769;
		}
	}
	for(int i=1;i<=2*n;i++) dp[i][i][0]=dp[i][i][1]=num[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=2*n-i+1;j++){
			int l=j,r=j+i-1;
			for(int k=l;k<r;k++){
				switch(op[k+1]){
					case 'x'://乘法运算
						dp[l][r][0]=max(dp[l][r][0],max(dp[l][k][0]*dp[k+1][r][0],dp[l][k][1]*dp[k+1][r][1]));
						dp[l][r][1]=min(dp[l][r][1],min(dp[l][k][1]*dp[k+1][r][0],dp[l][k][0]*dp[k+1][r][1]));
						break;
					case 't':
						dp[l][r][0]=max(dp[l][r][0],dp[l][k][0]+dp[k+1][r][0]);
						dp[l][r][1]=min(dp[l][r][1],dp[l][k][1]+dp[k+1][r][0]);
						break;
				}
			}
		}
	}
	int maxn=-32769;
	for(int i=1;i<=n+1;i++){
		int l=i,r=l+n-1;
		maxn=max(maxn,dp[l][r][0]);
	}
	cout<<maxn<<endl;
	for(int i=1;i<=n;i++){
		int l=i,r=l+n-1;
		if(dp[l][r][0]==maxn) cout<<i<<" ";
	}
	
	return 0;
}
```

---

## 作者：AubRain (赞：1)

题意：给出一个环形算式，断掉其中一条边，剩下的算式以任意书顺序合并，求得分最大值，并输出方案

做法：把给出的序列复制一遍接在后面，每次美枚举断掉哪条边

注意：

1、每次不仅要记录区间得分最大值，还要记录区间得分最小值，因为可能有负数，而负负得正

2、当大区间左端点为x时，右端点不是x+n，而是x+n-1

3、g[i][j]（得分最小值）如果是乘法，转移的时候要考虑最大值和最小值的乘积（负数乘上大正数是一个很小的负数）

4、因为要复制一遍原数组，所以N不能开成50


```cpp
#include<bits/stdc++.h>
#define N 150
#define int long long
using namespace std;

int n,ans=-2e9,cnt;
int cal[N],a[N],pr[N];
int f[N][N],g[N][N];

int work(int x)
{
	memset(f,0xcf,sizeof f);
	memset(g,0x3f,sizeof g);
	for(int i=x;i<=x+n-1;i++)
		g[i][i]=f[i][i]=a[i];
	for(int l=1;l<=n;l++)
		for(int i=x;i+l-1<=x+n-1;i++)
		{
			int j=i+l-1;
			for(int k=i+1;k<=j;k++)
			{
				if(!cal[k])
					f[i][j]=max(f[i][j],f[i][k-1]+f[k][j]),
					g[i][j]=min(g[i][j],g[i][k-1]+g[k][j]);
				else
					f[i][j]=max(f[i][j],f[i][k-1]*f[k][j]),
					f[i][j]=max(f[i][j],g[i][k-1]*g[k][j]),
					g[i][j]=min(g[i][j],g[i][k-1]*g[k][j]),
					g[i][j]=min(g[i][j],g[i][k-1]*f[k][j]),
					g[i][j]=min(g[i][j],f[i][k-1]*g[k][j]);
					
			}
		}

	return f[x][x+n-1];
}

signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		char b;
		cin>>b;
		scanf("%lld",&a[i]);
		cal[i+n]=cal[i]=b=='x';
		a[i+n]=a[i];
	}
	
	for(int i=1;i<=n;i++)
	{
		int now=work(i);
		if(ans==now) pr[++cnt]=i;
		else if(ans<now) ans=now,cnt=0,pr[++cnt]=i;
	}
	
	printf("%lld\n",ans);
	for(int i=1;i<=cnt;i++)
		printf("%lld ",pr[i]);
	
	return 0;
}
```

---

## 作者：yu__xuan (赞：0)

### 题目
[P4342 [IOI1998]Polygon](https://www.luogu.com.cn/problem/P4342)

### 思路
区间 $dp$。结点按输入顺序编好号，操作也编好号。

$f[i][j]$ 表示 $[i,j]$ 这个区间能合出的最大值。

$g[i][j]$ 表示 $[i,j]$ 这个区间能合出的最小值（为什么需要算最小值？因为有可能出现负数，并且有乘法操作）。

枚举断哪一条边（断环成链正好完成了这个工作），断环成链后$f[1][n], f[2][n + 1], \dots, f[n][n + n -1]$ 正好代表断了第 $1,2,\dots,n$ 条边。

状态转移方程：

对于加法，
```cpp
f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j]);
```
对于乘法,因为要考虑正负所以要麻烦一些,

* $f[i][k]>0,f[k+1][j]>0,g[i][k]>0,g[k+1][j]>0$
```cpp
f[i][j] = max(f[i][j], f[i][k] * f[k + 1][j]);
g[i][j] = min(g[i][j], g[i][k] * g[k + 1][j]);
```

* $f[i][k]>0,f[k+1][j]>0,g[i][k]>0,g[k+1][j]<0$，因为一个大的正数乘负的显然会更小所以，
```cpp
f[i][j] = max(f[i][j], f[i][k] * f[k + 1][j]);
g[i][j] = min(g[i][j], f[i][k] * g[k + 1][j]);
```

* $f[i][k]>0,f[k+1][j]<0,g[i][k]>0,g[k+1][j]<0$，这个区间一定是一个负数乘一个正数，那么大的负数乘小的正数得到最大值，小的负数乘大的正数得到最小值。
```cpp
f[i][j] = max(f[i][j], g[i][k] * f[k + 1][j]);
g[i][j] = min(g[i][j], f[i][k] * g[k + 1][j]);
```

* $f[i][k]>0,f[k+1][j]>0,g[i][k]<0,g[k+1][j]>0$，因为一个大的正数乘负的显然会更小所以，
```cpp
f[i][j] = max(f[i][j], f[i][k] * f[k + 1][j]);
g[i][j] = min(g[i][j], g[i][k] * f[k + 1][j]);
```

* $f[i][k]>0,f[k+1][j]>0,g[i][k]<0,g[k+1][j]<0$，因为负负得正所以，
```cpp
f[i][j] = max(f[i][j], f[i][k] * f[k + 1][j], g[i][k] * g[k + 1][j]);
g[i][j] = min(g[i][j], f[i][k] * g[k + 1][j], g[i][k] * f[k + 1][j]);
```

* $f[i][k]>0,f[k+1][j]<0,g[i][k]<0,g[k+1][j]<0$
```cpp
f[i][j] = max(f[i][j], g[i][k] * g[k + 1][j]);
g[i][j] = min(g[i][j], f[i][k] * g[k + 1][j]);
```

* $f[i][k]<0,f[k+1][j]>0,g[i][k]<0,g[k+1][j]>0$
```cpp
f[i][j] = max(f[i][j], f[i][j] * g[k + 1][j]);
g[i][j] = min(g[i][j], g[i][k] * f[k + 1][j]);
```

* $f[i][k]<0,f[k+1][j]>0,g[i][k]<0,g[k+1][j]<0$
```cpp
f[i][j] = max(f[i][j], g[i][k] * g[k + 1][j]);
g[i][j] = min(g[i][j], g[i][k] * f[k + 1][j]);
```

* $f[i][k]<0,f[k+1][j]<0,g[i][k]<0,g[k+1][j]<0$
```cpp
f[i][j] = max(f[i][j], g[i][k] * g[k + 1][j]);
g[i][j] = min(g[i][j], f[i][k] * f[k + 1][j]);
```

要考虑的情况比较多，但不难。。

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define inf 0x3f3f3f

int n, ans = -inf, a[110];
int f[110][110], g[110][110];
char opt[110];

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= 2 * n; ++i) {
		if (i & 1) std::cin >> opt[i / 2 + 1];
		else std::cin >> a[i / 2];
	}
	for (int i = 1; i <= 2 * n; ++i) {
		for (int j = 1; j <= 2 * n; ++j) {
			f[i][j] = -inf;
			g[i][j] = inf;
		}
	}
	for (int i = 1; i <= n; ++i) {
		a[i + n] = a[i];
		opt[i + n] = opt[i];
		f[i][i] = f[i + n][i + n] = a[i];
		g[i][i] = g[i + n][i + n] = a[i];
	}
	for (int l = 2; l <= n; ++l) {
		for (int i = 1; i <= 2 * n - l + 1; ++i) {
			int j = i + l - 1;
			for (int k = i; k < j; ++k) {
				if (opt[k + 1] == 't') {
					f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
					g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j]);
				}
				else {
					f[i][j] = max(f[i][j], max(f[i][k] * f[k + 1][j], max(g[i][k] * g[k + 1][j], max(f[i][k] * g[k + 1][j], g[i][k] * f[k + 1][j]))));
					g[i][j] = min(g[i][j], min(f[i][k] * f[k + 1][j], min(g[i][k] * g[k + 1][j], min(f[i][k] * g[k + 1][j], g[i][k] * f[k + 1][j]))));
				}
			}
		}
	 }
	for (int i = 1; i < n; ++i) {
		ans = max(ans, f[i][i + n - 1]);
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; ++i) {
		if (f[i][n + i - 1] == ans) printf("%d ", i);
	}
	return 0;
}
```

---

## 作者：jins3599 (赞：0)

区间$dp$模板。

仔细想想就会发现这道题和石子合并是一模一样的。

我们发现断边的这个过程，其实用石子合并化环为链的方法就可以解决。

然后我们用一个$opt$数组存每个数前面的运算符是什么。

之后进行一次区间$dp$，但是我们发现乘法的话不一定是两个最大值乘在一起是最大的。因此我们需要$dp$最大值和最小值。

也就是说，我们在记录乘法的答案时，要依次判断:

最大 $\ *$ 最大 ， 最大 $\ *$ 最小 ， 最小 $\ *$  最大 ， 最小$\ *$ 最小。

最后输出断哪一条边，只需要记录答案之后看有几组最优解即可。

$Code:$

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 500;
int a[N];
bool opt[N]; // 1 * , 0 + 
int n;
int f[N][N];
int g[N][N];

int main () {
	ios :: sync_with_stdio(false);
	cin >> n;
	for(int i = 1 ; i <= n ; i ++) {
		char p; 
		cin >> p >> a[i];
		if(p == 't') opt[i] = 0;
		else opt[i] = 1;
	}
	for(int i = 1 ; i <= n ; i ++){
		a[i + n] = a[i];
		opt[i + n] = opt[i];
	}
	memset(g , 0x3f , sizeof(g));
	for(int i = 1 ; i <= (n << 1) ; ++ i) 
		for(int j = 1 ; j <= (n << 1 ) ; j ++) f[i][j] = -0x3f3f3f3f;
		
	for(int i = 1 ; i <= (n << 1) ; i ++) f[i][i] = g[i][i] = a[i];
		
	for(int len = 2 ; len <= n ; ++ len) {
		for(int i = 1 ; i <= (n << 1) - len + 1 ; ++ i) {
			int j = i + len - 1;
			for(int k = i + 1 ; k <= j ; k ++) {
				if(opt[k] == 0) {
					f[i][j] = max(f[i][j] , f[i][k - 1] + f[k][j]);
					g[i][j] = min(g[i][j] , g[i][k - 1] + g[k][j]); 	
				} else {
					f[i][j] = max(f[i][j] , max(f[i][k - 1] * f[k][j] ,max(f[i][k - 1] * g[k][j] , max(g[i][k - 1] * g[k][j] , g[i][k - 1] * f[k][j]))));
					g[i][j] = min(g[i][j] , min(f[i][k - 1] * f[k][j] ,min(f[i][k - 1] * g[k][j] , min(g[i][k - 1] * g[k][j] , g[i][k - 1] * f[k][j]))));
				}
			} 
		}
	}
	int ans = -0x3f3f3f3f;
	for(int i = 1 ; i <= n ; i ++) ans = max(ans , f[i][i + n - 1]);
	cout << ans << endl;
	for(int i = 1 ; i <= n ; i++) {
		if(f[i][i + n - 1] == ans) cout << i << " ";
	}
	return 0;
}
```

---

## 作者：xiejinhao (赞：0)

# P4342[IOI1998]Polygon 题解  

### 这个输入有毒……


------------


#### 总的来看这一题还是比较经典的区间DP

附赠区间DP模板题：

- [P1880 [NOI1995]石子合并](https://www.luogu.org/problemnew/show/P1880)

- [P1063 [NOIP2006]能量项链](https://www.luogu.org/problemnew/show/P1063)

建议可以先弄懂上面两题。

接着讲一下思路：

1. 首先把数据复制一倍，把环断开转换成链（这个不用解释吧？）。

1. 其实转移方程还是很好写的：

- 题目要求的是最高的分数，并且每一条边有加或乘的操作。

对于加法，我们只要求加和不加哪个值最大就好了，这里不再赘述，模板题做了就会了。

这里重点讲乘法：我们考虑下乘法如何得到最大值？无非两种情况，一种是两个最小的负数相乘，另一种是两个最大的正数相乘，因此我们需要辅助数组来保存最小值，以便我们判断乘法。

但是这个输入真的有毒：

```cpp
//如果你这么写
  scanf("%d",&n);
//0分
//然而应该这么写：
  scanf("%d\n",&n);
```

```cpp
//如果你这么写：
  for(int i = 1; i <= n; i++)
      getchar(),scanf("%c %d",&b[i],&a[i]),b[i+n] = b[i],a[i+n] = a[i];
//80分，第三个点过不了
```
但是上面那种写法在本地是对的orz

如果你不写 getchar() ，那你貌似是0分（样例过不了）；

于是只能把 getchar() ，放在后面，这样就AC了（我也不知道为什么）


正确读入
------------

```cpp
  scanf("%d\n",&n);
  for(int i = 1; i <= n; i++)
      scanf("%c %d",&b[i],&a[i]),getchar(),b[i+n] = b[i],a[i+n] = a[i];
                     
//当然你可以用 cin
```
这输入里面还包括了转环成链。

然后就没有什么毒瘤的地方了，只需要一个辅助数组保存最小值，然后乘法的时候判断一下就行了（加法还是照常）。



$AC$  $Code$
------------
```cpp
  #include <iostream>
  #include <cstdio>
  #include <cstring>
  #include <cstdlib>
  using namespace std;
  const int M = 60;
  int n,a[2*M],f[2*M][2*M],f1[2*M][2*M];
  char b[2*M];
  int main()
  {
      memset(f,-0x3f,sizeof f);
      memset(f1,0x3f,sizeof f1);
      scanf("%d\n",&n);
      for(int i = 1; i <= n; i++)
          scanf("%c %d",&b[i],&a[i]),getchar(),b[i+n] = b[i],a[i+n] = a[i];
      //输入 
      for(int i = 1; i <= 2*n;i ++) f1[i][i] = f[i][i] = a[i]; 
      for(int j = 2; j <= n;j++)
          for(int k = 1; j + k - 1 <= 2 * n; k++)
              for(int l = k+1;l <= j + k - 1; l++)
              {

                  if(b[l] == 't')
                  {
                      f[k][j+k-1] = max(f[k][j+k-1],f[k][l-1] + f[l][j+k-1]);
                      f1[k][j+k-1] = min(f1[k][j+k-1],f1[k][l-1] + f1[l][j+k-1]);
                      //寻找最小值，以便乘法使用;
                  }
                  else
                  {
                      f[k][j+k-1] = max(f[k][j+k-1],f[k][l-1] * f[l][j+k-1]);
                      f[k][j+k-1] = max(f[k][j+k-1],f1[k][l-1] * f1[l][j+k-1]);
                      //这里遇到了乘法，最大值分两种情况，最小x最小、最大x最大; 
                      //接下来寻找最小值，因为是乘法，故符号改成*;
                      //最小值可以是 f与f1数组 混合相乘 中的某一个; 
                      //总共有4种情况： 
                      f1[k][j+k-1] = min(f1[k][j+k-1],f1[k][l-1] * f1[l][j+k-1]);
                      f1[k][j+k-1] = min(f1[k][j+k-1],f1[k][l-1] * f[l][j+k-1]);
                      f1[k][j+k-1] = min(f1[k][j+k-1],f[k][l-1] * f1[l][j+k-1]);
                      f1[k][j+k-1] = min(f1[k][j+k-1],f[k][l-1] * f[l][j+k-1]);
                  }
              }
      int maxx = -0x7fffffff;	
      for(int i = 1; i <= n; i++)
      maxx = max(maxx,f[i][i+n-1]);	
      //寻找最高分 
      printf("%d\n", maxx);
      for(int i = 1; i <= n; i++)
          if(f[i][i+n-1] == maxx)
          printf("%d ",i);
      //寻找被剪掉的边 
      return 0;
  }
```




---

## 作者：G_A_TS (赞：0)

此题是道区间dp，理论上可做  
~~不会区间dp板子的就算了~~  
此题基本思路参照[石子合并](https://www.luogu.org/problemnew/solution/P1880)  
但是，此题有加有乘~~(没有人不知道吧)~~，若只有加则基本是合并石子  
而乘就稍微恶心，有个神奇的初一知识点：  
## 负负得正  
所以，本题不再是一个DP数组，而是两个！ 

------------
```cpp
dpmax[i][j]=max(dpmax[i][j],max(dpmax[i][k]*dpmax[k+1][j],dpmin[i][k]*dpmin[k+1][j]));//最大值考虑负负得正
dpmin[i][j]=min(dpmin[i][j],min(min(dpmax[i][k]*dpmin[k+1][j],dpmin[i][k]*dpmax[k+1][j]),dpmin[i][k]*dpmin[k+1][j]));//最小值分类讨论 
```

------------
至于破哪条边。。。区间dp时不就默认破成链了吗？  
上代码(有注释)

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,num[110],dpmax[110][110],dpmin[110][110],ans=-999999999;
/*dpmax[i][j]表示i到j的最大值,dpmin[i][j]表示其最小值*/
char fh[110];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>fh[i]>>num[i];
		fh[i+n]=fh[i];
		num[i+n]=num[i];//破环为链
	}
	for(int i=1;i<=2*n;i++)
	{
		for(int j=1;j<=2*n;j++)
		{
            if(i==j)
			{
				dpmax[i][j]=num[i];
				dpmin[i][j]=num[i];//没有不理解初始化的吧
			} 
            else 
			{
				dpmax[i][j]=-20000;
				dpmin[i][j]=20000;
			}
        }
	}
	for(int l=2;l<=n;l++)
	{
		for(int i=1;i+l-1<=2*n;i++)
		{
			int j=i+l-1;
			for(int k=i;k<j;k++)//区间dp板子
			{
				if(fh[k+1]=='x')
				{
					dpmax[i][j]=max(dpmax[i][j],max(dpmax[i][k]*dpmax[k+1][j],dpmin[i][k]*dpmin[k+1][j]));//最大值考虑负负得正
					dpmin[i][j]=min(dpmin[i][j],min(min(dpmax[i][k]*dpmin[k+1][j],dpmin[i][k]*dpmax[k+1][j]),dpmin[i][k]*dpmin[k+1][j]));//最小值分类讨论 
				}
				else
				{
					dpmax[i][j]=max(dpmax[i][j],dpmax[i][k]+dpmax[k+1][j]);
					dpmin[i][j]=min(dpmin[i][j],dpmin[i][k]+dpmin[k+1][j]);
				}			
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,dpmax[i][i+n-1]);
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
	{
		if(dpmax[i][i+n-1]==ans)//前文说过，区间dp已默认破了边
		{
			cout<<i<<" ";
		}
	}
}
```

---

## 作者：command_block (赞：0)

### 总感觉这道题和[P1063 能量项链](https://www.luogu.org/problemnew/show/P1063)区别不大?

~~我就是仗着代码短来发题解的~~

这题怎么会是紫题呢?

思路楼下讲得很清楚,我就不赘述了……

```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long n,tmp,f[105][105],ff[105][105],s[105],ans;
//ff表示区间最小值,f表示区间最大值
char op[105];
//没用区间DP的板子,所以有点慢(western reporter?)
void dfs(int i,int j)
{
  if (f[i][j]>=0)return ;
  for (int k=i+1;k<=j;k++){
	dfs(i,k-1);dfs(k,j);
	long long rf=f[k][j],rff=ff[k][j],lf=f[i][k-1],lff=ff[i][k-1];
    f[i][j]=max(f[i][j],op[k]=='t' ? lf+rf:max(lf*rf,lff*rff));
	ff[i][j]=min(ff[i][j],op[k]=='t' ? lff+rff:min(min(lff*rf,lf*rff),lff*rff));
    //方程一点也不长,而且很好理解
  }
}
int main()
{
  cin>>n;
  for (int i=1;i<=n;i++){
	cin>>op[i]>>s[i];
    s[i+n]=s[i];
	op[i+n]=op[i];
    //拆环为链
  }memset(f,-0x3f,sizeof(f));
  memset(ff,0x3f,sizeof(ff));
  ans=-1ll<<60;
  for (int i=1;i<=n;i++)
   ff[i][i]=ff[i+n][i+n]=f[i][i]=f[i+n][i+n]=s[i];
  //边界条件
  for (int i=1;i<=n;i++){
    dfs(i,i+n-1);
    ans=max(ans,f[i][i+n-1]);
  }cout<<ans<<endl;
  for (int i=1;i<=n;i++)
   if (ans==f[i][i+n-1])cout<<i<<' ';
  return 0;
}
```

~~皮这一下很开心~~

我是在[夏令营梗收集帖](https://www.luogu.org/discuss/show/51862?&page=11)见到这题的……

---

