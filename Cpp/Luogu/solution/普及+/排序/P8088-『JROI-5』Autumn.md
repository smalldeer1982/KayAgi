# 『JROI-5』Autumn

## 题目背景

感谢 @[王熙文](/user/353688) 提供了一种优于标算的做法。

## 题目描述

**本题读入量较大，建议使用较快的读入方式，可以参考 [赛时公告板](https://www.luogu.com.cn/paste/lueudpd5)**


给定 $n$ 个数列，每个数列有 $m$ 个元素，第 $i$ 个数列第 $j$ 个元素为正整数 $a_{i,j}$。

你每次可以选择 $i_1,j_1$ 和 $i_2,j_2$，交换 $a_{i_1,j_1}$ 和 $a_{i_2,j_2}$。你至多可以进行 $x$ 次交换。

定义 $d_i$ 为第 $i$ 个数列中第 $k$ 大的元素。

请最小化 $\max\limits_{i=1}^n \{d_i\}$。（表示 $d_1,d_2,\cdots,d_n$ 中的最大值）

## 说明/提示

对于样例 1，将 $a_{2,5}$ 和 $a_{1,5}$ 交换，可以证明，没有更优策略。
***
对于 $30\%$ 的数据，$x = 10^6,1\leq k\leq m$。

对于另外 $10\%$ 的数据，**所有的数都相等**。

对于另外 $30\%$ 的数据，$1\leq n,m\leq 2\times 10^3,1\leq k\leq m,a_{i,j}\leq 10^6,0\leq x\leq n\times m$。

对于 $100\%$ 的数据，$1\leq n,m\leq 2\times 10^3,1\leq k\leq m,1\leq a_{i,j}\leq 10^{18},0\leq x\leq n\times m$。



## 样例 #1

### 输入

```
5 5
1 2 3 4 5
6 7 8 9 10
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
2 1```

### 输出

```
8```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5
6 7 8 9 10
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
2 2```

### 输出

```
7```

## 样例 #3

### 输入

```
见附件```

### 输出

```
见附件```

# 题解

## 作者：囧仙 (赞：12)

## 题解

一种容易想到的思路是，二分答案，然后判断是否存在一种合法方案。

由于我们需要计算矩阵的每一行的第 $k$ 大，因此考虑先将每一行进行排序。对于样例，排序后是这个模样：

$$
\newcommand{\line}[5]{
\mathclap{#1} & \mathclap{#2} & \mathclap{#3} & \mathclap{#4} & \mathclap{#5}
}
\def\b{\rule{1.8em}{1.8em}}
\def\r#1{\raisebox{.5em}{#1}}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}}\cr[-18pt]
\line{1}{2}{3}{4}{5} \cr\hline
\line{1}{2}{3}{4}{5} \cr\hline
\line{6}{7}{8}{9}{10} \cr\hline
\line{1}{2}{3}{4}{5} \cr\hline
\line{1}{2}{3}{4}{5} \cr\hline
\end{array}
$$

那么每一行的第 $n-k+1$ 列，就是该行的第 $k$ 大。

假定现在二分的答案为 $d$。那么存在一种方案使得「每一行的第 $k$ 大」的最大值不超过 $d$，等价于我们要在每一行都有至少 $n-k+1$ 个不大于 $d$ 的数字。那么可以把数字分为两类：不大于 $d$ 的数字，和大于 $d$ 的数字。将其黑白染色，前者染成白色，后者染为黑色。以样例举例，假设现在 $d=7$。

$$
\newcommand{\line}[5]{
\mathclap{#1} & \mathclap{#2} & \mathclap{#3} & \mathclap{#4} & \mathclap{#5}
}
\def\bb{\color{black}\rule{1.8em}{1.8em}}
\def\wb{\color{white}\rule{1.7em}{1.8em}}
\def\r#1{\raisebox{.5em}{#1}}
\phantom{\kern{-19.5pt}\left|\phantom{\rule{1em}{5.5em}}\right.}
\phantom{\kern{-20.5pt}\left|\phantom{\rule{1em}{5.5em}}\right.}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}} & 
\phantom{\rule{.75em}{1em}}\cr[-18pt]
\line{\wb}{\wb}{\wb}{\wb}{\wb} \cr[-5pt]\hline
\line{\wb}{\wb}{\wb}{\wb}{\wb} \cr[-5pt]\hline
\line{\wb}{\wb}{\bb}{\bb}{\bb} \cr[-5pt]\hline
\line{\wb}{\wb}{\wb}{\wb}{\wb} \cr[-5pt]\hline
\line{\wb}{\wb}{\wb}{\wb}{\wb} \cr[-5pt]\hline
\end{array}
\kern{-19.5pt}\left|\phantom{\rule{1em}{5.5em}}\right.
\kern{-20.5pt}\left|\phantom{\rule{1em}{5.5em}}\right.
$$

那么我们需要把 $n-k+1$ 这条线（图中的双线）右侧的两个白色方块与 $n-k+1$ 左侧的两个黑块互换位置。

假设 $n-k+1$ 左侧黑块的个数为 $p$，右侧白块的个数为 $q$。那么当且仅当 $p\le q$ 且 $p\le x$ 时可以使得「每一行的第 $k$ 大」的最大值不超过 $d$。

直接这么做，复杂度是 $\mathcal O(\log v\cdot nm)$ 的，卡卡常勉强能过。不过可以发现，如果我们让枚举的 $d$ 从大到小变化，那么 $p$ 应该是单调不减，$q$ 应该是单调不增的。那么只需要对于 $a_{i,j}$ 从大到小作为可能的 $d$，就可以单调地维护 $p$ 和 $q$ 的值。均摊一下这部分的时间复杂度就降为了 $\mathcal O(nm)$。不过由于需要对于所有数字排序，所以复杂度是 $\mathcal O(\log (nm)\cdot nm)$，但是常数可能小一点（因为 $\text{STL}$ 当中的 `sort` 速度比较快）。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=2e3+3,MAXM=4e6+3;
i64 n,m,k,u,A[MAXN],t;
i64 qread(){
    i64 w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
i64 W[MAXM][2],I[MAXM],ans=1e18,p,q,x,y;
bool cmp(int a,int b){return W[a][0]<W[b][0];}
int main(){
    n=qread(),m=qread();
    up(1,n,i){
        up(1,m,j) A[j]=qread(); sort(A+1,A+1+m);
        up(1,m,j){
            W[++t][0]=A[j],W[t][1]=j,I[t]=t;
        }
    }
    k=m-qread()+1,u=qread(),sort(I+1,I+1+t,cmp);
    x=t,p=n*(m-k),y=t,q=0;
    dn(t,1,i){
        i64 d=W[I[i]][0];
        while(x>0&&W[I[x]][0]>d) p-=(W[I[x]][1]> k),--x;
        while(y>0&&W[I[y]][0]>d) q+=(W[I[y]][1]<=k),--y;
        if(q>u||q>p) break; ans=d;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：MichaelWong (赞：7)

奇怪了，大家怎么都用二分做的，那我换一种思路！

# 题意

简单来说，就是给定一个 $n \times m$ 的矩阵，$d_i$ 表示第 $i$ 行第 $k$ 大的元素，有 $x$ 次机会对这个矩阵中的任意两个元素进行交换，使 $\max\limits_{i=1}^n \{d_i\}$ 最小，输出这个最小值。

# 思路

- 不难得出，想要让每行的 $d_i$ 最小，一定是把当前最大的 $d_i$ 与其他行的前 $k-1$ 个数中比他小的数 $a$ 交换。这样，更小的 $a$ 就成为了新的 $d_i$；而原来的 $d_i$ 在新的一行必然是前 $k-1$ 个数，不会影响那一行的 $d_i$，最大的 $d_i$ 就变小了。

- 为了实现这个交换，我们可以把所有元素分成两个集合：每行的前 $k-1$ 个元素 $S$ 和后面的元素 $T$。

- 易证，$T$ 中最大的元素 $t$ 就是当前的 $\max\limits_{i=1}^n \{d_i\}$。反证法：如果 $t$ 是他那一行的第 $j$ 个数（$j>k$），那么必然有那一行的第 $k$ 个数 $a \in T$，且 $a>t$，则 $t$ 不是 $T$ 中最大元素。

- 所以，我们要做的就是将 $S$ 中最小的元素与 $T$ 中最大的元素进行交换，这个操作执行 $x$ 次，直至 $S$ 中的最小元素 $>T$ 中的最小元素。此时，$T$ 中最大的元素就是最小化的 $\max\limits_{i=1}^n \{d_i\}$。

# 实现

考虑到复杂度比较宽容，可以在每行读入完成后对该行进行排序，然后使用 `std::priority_queue` 来维护 $S$ 和 $T$。当然，$S$ 使用升序，$T$ 使用降序。最后输出 $T$ 的队首即可。

## AC CODE
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=2e3+3;
bool cmp(int a,int b)	{return a>b;}
int n,m,k,x,a[N][N];
std::priority_queue<int,std::vector<int>,std::greater<int> >S;
std::priority_queue<int,std::vector<int>,std::less<int> >T;
signed main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);std::cout.tie(0);
	std::cin>>n>>m;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			std::cin>>a[i][j];
		}
		std::sort(a[i]+1,a[i]+m+1,cmp);
	}
	std::cin>>k>>x;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(j<k)	S.push(a[i][j]);
			else T.push(a[i][j]);
		}
	}
	while(x) {
		if(S.top()<T.top()) {
			int a1=S.top(),a2=T.top();
			S.pop();T.pop();
			S.push(a2);T.push(a1);
			x--;
		}
		else break;
	}
	std::cout<<T.top();
	return 0;
}

```

本题解毕。

---

## 作者：Cocoly1990 (赞：7)

官方题解。

**C**

算法一

~~根据传统套路~~，考虑二分答案，注意到如果 $x$ 在某种交换策略下可以达到，那么最终的答案必然小于等于 $x$.

那么我们二分最终的答案，例如当前二分到的是 $k_0$，那么我们把集合中大于 $k_0$ 的赋值为 $1$，其余为 $0$，$\mathcal{O}\left(n\right)$

判断即可，综合实践复杂度 $\mathcal{O}\left(nm\log R\right)$ 其中 $R$ 为 值域，结合前两个 Subtask，可以通过 $70\%$ 的部分分。

算法二

不排除有松怪可以用上述做法松过这个 Subtask.

考虑把序列分成两个部分来维护，分别维护每个集合的前 $k-1$ 大值和剩余的部分分。

尝试着理解一次最优化交换的本质。可以发现，最后的答案是二部分的最大值，那么，容易发现，最优化交换其实就是那部分二的最大值交换部分一的最小值，当然了部分一的最小值大于部分二的最小值，就没必要继续交换了。

肯定有人要问，如果这次交换的两个数在同一个集合，那么交换不就不成立了吗，很显然，这种情况是不可能的，至于如何，~~留作课后作业~~ 如果两个数在同一个集合，那么说明此时部分一的最小值大于部分二的最小值，更没必要交换了。

综合时间复杂度 $\mathcal{O}\left(nm\log nm\right)$.

---

## 作者：Moya_Rao (赞：2)

# 题目大意
给定一个 $n \times m$ 的矩阵 $a$，你至多可以进行 $x$ 次操作，选择 $a_{i1,j2}$ 和 $a_{i2,j2}$，并将它们交换。

现在要你通过这 $x$ 次交换，来**最小化**每行第 $k$ 大的值的**最大值**。

# 思路
## 首先进行思考
看到**最小化最大值**，很容易联想到二分答案。  
不过二分答案的话，必须满足**单调性**。

那么这道题目满足了么？  
当然是满足了的。  
比方说，对于某组输入，如果答案 $w$ 是可行的，那么答案 $w+1,w+2,\dots$，只要是存在在 $a$ 里的数值，都是可行的。  
反之，如果对于某组输入，答案 $v$ 是不可行的，那么答案 $v-1,v-2,\dots$，只要是存在在 $a$ 里的数值，都是不可行的。  

## 二分的基本条件

首先来想：二分什么？  
答案肯定很快就能想到：二分这个需要被我们最小化的最大值呀！

好，那接下来就是二分的 `while` 循环了。假如现在我们已经写好了 `check` 函数，那个二分的大 `while` 该怎么写呢？

根据上边的分析，由于答案必须存在在 $a$ 里边，所以可以拿一个 $s$ 数组将这一共 $n \times m$ 个数值全部放进来，排个序后直接用这个数组来二分。

那么就可以写出如下的代码：
```cpp
l=1,r=cnt;//cnt 为 s 数组中数字的个数，其实就是 n*m，且 s 早已排好序
while(l<=r){
    int mid=(l+r)/2;
    if(check(mid))ans=mid,r=mid-1;
    else l=mid+1;
}
```

最后输出的，就是 `s[ans]` 了。

### `check` 函数该怎么写
二分答案中**最重要**的环节来啦：`check` 函数该怎么写呢？

我们来想一想：  
每行第 $k$ 大的值其实并不好算，因为 $a$ 是无序的。但是很容易发现，一行中各个数的顺序其实无关紧要，没有什么用，所以我们完全可以给 $a$ 数组的**每一行**进行一次升序排序。那就很好求了，第 $i$ 行 $k$ 大的数即为 $a_{i,m-k+1}$。当然了是可以进行降序排序的，但我嫌麻烦没搞了，直接加了句这个：
```cpp
k=m-k+1;
```
这样就爽快地解决啦！在之后的解析中，$k$ 就会代表 $m-k+1$ 了。

不过，`check` 到底怎么写，我们还不知道呢！

继续想：

我们可以知道，如果要让 `check(p)` 成功，就是要**以 $k$ 为分界，左边的所有值都小于等于 $p$**。这个很重要啊！  
但是我们可以进行交换，可以交换 $num$ 次（这里及以后的 $num$ 指的都是题目描述中的 $x$），所以就算 $k$ 左边的某些值是比 $p$ 大的，也有成功的可能性。

那么要满足什么条件才能让它成功呢？

我们可以把 $k$ 左边的超过了 $p$ 的数值的个数统计出来，这里我记为变量 $left\_big$，意为左边大的。  
而 $k$ 的右边又可能有一些不超过 $p$ 的值，它们则是我们当前成功的“救星”。有了它们，我们就可以将它们与那些左边大的数进行交换，从而达到目的。 
于是我们统计一下它们的个数，我记为变量 $right\_small$，意为右边小的。  
为了使交换成功，我们必须得要满足 $right\_small \ge left\_big$ 才行，必须够交换，是吧？但是也不能超过总次数 $num$，因此还得满足 $left\_big \le num$，对不对？  
没有别的条件了，就是这两个！

综上所述，我们可以编写出 `check` 函数的代码：
```cpp
bool check(int id){
    long long x=s[id];
    int right_small=0;
    int left_big=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j<=k&&a[i][j]>x)left_big++;
            if(j>k&&a[i][j]<=x)right_small++;
        }
    }
    if( right_small>=left_big && left_big<=num )return 1;
    else return 0;
}
```
为了让你们更好地看这份代码，我就没有压行了哟。

## 最后的优化

写完代码后，提交！  
咦？怎么 TLE 了啊？

因为你得写快读啊！题目里都提到了，就是这句话：
>**本题读入量较大，建议使用较快的读入方式，可以参考 [赛时公告板](https://www.luogu.com.cn/paste/lueudpd5)**

但是我估计还是会有一些粗心大意的人~~比如我~~，平常写快读写得少的啊，会忘记这件事。

加上快读就没事啦！不过也要记得开 `long long` 哦！

# [AC](https://www.luogu.com.cn/record/180206693) 代码

现在，你们最爱看的代码来咯！这份代码还是完整的呢。

完整的代码里还带了注释呢，就算你看不懂上面的思路解析，应该也能通过代码里的注释来理解我的做法吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NM = 2e3+5;
long long n,m,a[NM][NM],s[NM*NM],cnt,k,num,l,r,ans;
long long read(){
    char c=getchar();
    long long sum=0,f=1;
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        sum=sum*10+c-'0';
        c=getchar();
    }
    return sum*f;
}
//“本题读入量较大，建议使用较快的读入方式，可以参考赛时公告板”
//所以你们得写一下快读，否则是会 TLE 的
bool check(int id){
    long long x=s[id];//真正的值
    int right_small=0;//右边不超过 x 的个数
    int left_big=0;//左边比 x 大的个数
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j<=k&&a[i][j]>x)left_big++;//是在左边，且比 x 大
            if(j>k&&a[i][j]<=x)right_small++;//是在右边，且不超过 x
        }
    }
    if( right_small>=left_big && left_big<=num )return 1;//满足条件，返回 1
    else return 0;//否则不满足，返回 0
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a[i][j]=read();
            s[++cnt]=a[i][j];//存下 a 中的每个值
        }
        sort(a[i]+1,a[i]+m+1);//给每一行排序
    }
    k=read(),num=read();
    sort(s+1,s+cnt+1);//整个儿排序，就用这个来二分
    k=m-k+1;//调转，因为 s 是从小到大排序的，而题目求的是第 k 大
    l=1,r=cnt;//l 和 r 的边界值
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid))ans=mid,r=mid-1;//ans 存储的是可能答案在 s 数组中的下标
        else l=mid+1;
    }//常规二分答案
    cout<<s[ans];//由于 ans 是下标，最后输出时需要拿到真正的数值才行
    return 0;
}
```

如果觉得写得好，就给我个赞吧，谢谢!

---

## 作者：karanoli (赞：2)

# P8088『JROI-5』Autumn 题解

题目要求**最小化最大值**，很容易就能想到二分答案。

由于我们需要每一行的第 $k$ 大，最简单的做法就是先给每一行升序排序。

那么显然第 $k$ 大就在第 $m-k+1$ 列。

然后我们考虑二分答案 $D$ 。那么对于一种合法的方案必然满足：
+ 在第 $m-k+1$ 右侧小于等于 $D$ 的数字的个数 $\ge$ 左侧大于 D 的数字的个数。
+ 在第 $m-k+1$ 左侧大于 $D$ 的数字的个数 $\le x$。

接下来就是二分答案经典操作：
+ 如果方案可行，$r=mid-1,ans=mid$。
+ 否则，$l=mid+1$。

显然直接二分答案，时间复杂度为 $\Theta(nm\log_{2}{2^{64}})$，极其容易超时，所以我们考虑缩小二分范围，用一个数组 $b$ 存全部数据，然后排序，用这个数组进行二分，可以证明复杂度为 $\Theta(nm\log_{2}{nm})$。

### code time
```cpp
const ll N=2e3+5;
ll n,m,k,x,tot;
ll ans;
ll a[N][N],b[N*N];
ll l1,r1;
signed main(){
	read(n);read(m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			read(a[i][j]),b[++tot]=a[i][j];
		sort(a[i]+1,a[i]+m+1);
	}
	sort(b+1,b+n*m+1);
	read(k);read(x);k=m-k+1;
	int l=1,r=n*m,mid;
	while(l<=r){
		mid=l+r>>1;
		l1=r1=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]<=b[mid]&&j>k)++r1;
				if(a[i][j]>b[mid]&&j<=k)++l1;
			}
		}
		if(l1<=r1&&l1<=x)
			ans=mid,r=mid-1;
		else 
			l=mid+1;
	}
	printf("%lld\n",b[ans]);
    return 0;
}

```

---

## 作者：_Emperorpenguin_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8088)

-------------------------------------------------

## 分析

由于要求“最小的最大”，故想到二分答案。记最终答案为 $d_{max}$。


接下来就是二分的过程了。

二分要求有序，因此可以对每一组数进行降序排列。$a_{i,k}$ 即为 $d_i$。


可以先把二分的模板写好。容易发现，若当前二分出来的答案
    $mid$ 满足要求，则可以将 $d_{max}$ 减小，既 ```r=mid-1```。否则，```l=mid+1```。

  由于求最小值，答案在右区间。故输出 $l$。

这一部分的代码如下：

```cpp
while(l<=r){
		mid=l+r>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	cout<<l;
```

下面，便是最重要的 ```check()``` 函数了。

对于每个二分出来的答案 $u$，我们可以进行如下处理：

- 记录下 $j < k$ 且 $a_{i,j} \leq u$ 的 $a_{i,j}$ 的个数 $l$。

- 记录下 $j \geq k$ 且 $a_{i,j} > u$ 的 $a_{i,j}$ 的个数 $r$。

- 若 $r\geq l$，则说明有足够的在 $k$ 左侧的小于等于 $u$ 的数来与在 $k$ 右侧的大于 $u$ 的数进行交换。

- 若 $r\leq x$，则说明交换次数够用。

- 若满足上述两个条件，则 $u$ 可行。否则不可行。

这是 ```check()``` 函数的代码：

```cpp
bool check(int u){
	int l=0,r=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(j>=k&&a[i][j]>u) r++;
			else if(j<k&&a[i][j]<=u) l++;
		}
	return (r<=l)&&(r<=x);
}


```
    
  记得开快读和 ```long long```。
    
  ## Code

  ```cpp
#include <bits/stdc++.h>
#pragma GCC optmize(2)
using namespace std;

#define int long long
int n,m,k,x;
int a[2005][2005];

inline int read(){//快读 
    register int x=0,t=1;
    register char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            t=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*t;
}

bool cmp(int a,int b){//降序排序 
	return a>b;
}

bool check(int u){
	int l=0,r=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(j>=k&&a[i][j]>u) r++;
			else if(j<k&&a[i][j]<=u) l++;
		}
	return (r<=l)&&(r<=x);
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			a[i][j]=read();
		sort(a[i]+1,a[i]+m+1,cmp);
	}
	k=read();
	x=read();
	int l=1,r=1e18,mid; 
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}

```

---

