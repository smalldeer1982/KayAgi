# 序列 sequence

## 题目背景

原题 CF13C 数据加强版

## 题目描述

给定一个序列，每次操作可以把某个数 $+1$ 或 $-1$。要求把序列变成非降数列。

## 说明/提示

对于 $100 \%$ 的数据，$1 \le n \le 5 \times {10}^5$。

## 样例 #1

### 输入

```
5
3 2 -1 2 11
```

### 输出

```
4```

## 样例 #2

### 输入

```
5
2 1 1 1 1
```

### 输出

```
1```

# 题解

## 作者：bztMinamoto (赞：85)

表示完全看不懂楼下的大佬们说啥……特别是某绿……某c姓大佬

来说说个人的理解吧

大佬们说：考虑当前的数$x$和之前的最大数$y$，（默认$x<y$，因为如果$x>=y$已经满足非降了）为了让它非降，我们要在区间$[x,y]$里找到一个数$z$，使$y$减小到$z$,$x$增大到$z$，那么可以发现，不管取的数是什么，代价都是$y-x$

不难看出，$y$减小的越多，后面的序列越容易变成非降，那么只要让$y$减小到$x$就好了

看到这里，我一直有一个疑问，如果令$y$减小到$x$之后，序列不满足非降了怎么办？

仔细想了想，实际上应该是这样的：为了让序列非降，$y$不能小于$y$之前的最大值。而由于$y$是整个序列的最大值，如果它之前的最大值$z$小于等于$x$，那么将$y$减小到$x$仍能保证序列是非降的。否则的话，$z$大于$x$小于$y$，仍是在区间$[x,y]$内，那么移动的代价是$y-x$，所以用于更新答案是没有问题的

那么这里为什么要让$y$减到最小呢？这是因为$x$和$y$不论如何调整，他们的代价之和都已经不变了，但问题是他们目前选的最优方案并不是之后的最优。为了满足他们在之后最优，只有把$y$减小到$x$，才能保证之后更有可能非降。

概括一下，对于当前的数，无论最优解如何，对答案的贡献是一定的。而为了保证之后的解也最优，令$y$减小到$x$，可以保证之后的解最优，且不会影响当前的最优解

代码好短……
```
//minamoto
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
priority_queue<int> q;
int n;long long ans;
int main(){
	n=read();
	while(n--){
		int x=read();q.push(x);
		if(x<q.top()){
			ans+=q.top()-x;
			q.pop();q.push(x);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Mr_Wu (赞：62)

### 前言

smarthehe 神看我最近总不刷题就给我推了 CF713C，然后我猜了 dp 是下凸壳，然后给猜对了。。然后找到了三倍经验：CF713C、CF13C、还有这题。。

然后我也采用了大部分题解使用的写法，我认为出处应该来自于 [ko_osaga](https://codeforces.ml/blog/entry/47094?#comment-315161)，我将会做详细解释。

### 题解

首先我们弄出一个 dp，设 $f_{i,j}$ 表示到第 $i$ 个数，把这个数变成 $j$，考虑 $[1,i]$ 的最小代价，转移方程是

$$ f_{i,j}=\min_{k\le j} f_{i-1,k} +|a_i-j| $$

所以现在我们有了一个 $\Theta(n\max a_i)$ 的复杂度，实在是太好了，能通过 0 个加强前题目的数据！

接下来我们来证明对每个 $i$，$f_{i,x}$ 是关于 $x$ 的一个下凸壳。

首先 $i=1$ 的时候是的对吧。。

然后我们考虑每次发生了什么变化，

![](https://cdn.luogu.com.cn/upload/image_hosting/t77qt3rh.png)

（线段上标的是斜率，图中画的线段斜率可能不太准）

分 4 种情况，讨论下凸壳中的每一个线段：

1. 线段单降，在 $a_i$ 左侧

此时 $\min\limits_{k\le j} f_{i-1,k}=f_{i-1,j}$，所以 $f_{i,j}=f_{i-1,j}+a_i-j$，稍微看看就能发现是斜率减 1 。（数值 -1，不是绝对值 -1 ！）

2. 线段单降，在 $a_i$ 右侧

仿效上面的方法，$f_{i,j}=f_{i-1,j}+j-a_i$，是斜率增 1 。

3. 线段不单降，在 $a_i$ 左侧

此时找到之前最后一个单降的点 $\text{op}$，则 $f_{i,j}=\text{op}+a_i-j$，此时线段斜率变成 -1 。

4. 线段不单降，在 $a_i$ 右侧

$f_{i,j}=\text{op}+j-a_i$，此时线段斜率变成 1

因此这是个凸包，直接按照上面的方法，可以有 $\Theta(n^2)$ 了。

然后我们考虑用数据结构维护凸包，其实我们有一个很简单的方法，就是直接使用大根堆，堆中每个元素应当是二元组 $(x,k)$ 表示一条线段的右端点和这条线段的斜率，并且我们舍弃掉所有不单降的线段，**但是考虑到 priority_queue 可重，我们舍弃掉第二个元素，然后我们认为一个元素的 $k$ 是与它相同的最左边的元素到最大元素之间的距离的相反数**。例如用 $\{1,2,3,3\}$ 表示 $\{(1,-4),(2,-3),(3,-2),(3,-2)\}$。

我们加入了 $a_i$，两种情况：

1. $a_i\ge \text{op}$，此时 $a_i$ 成为新的决策点，我们不需要更新答案，只需要压如 $a_i$。

2. $a_i<\text{op}$，此时所有堆中的斜率都 -1，斜率为 -1 的应当弹出，由于这个写法很聪明，因此只需要把最大的元素弹出，在弹出之前更新答案。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, t; long long ans;
priority_queue<int> Q;

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &t), Q.push(t);
        if (Q.top() != t) ans += Q.top() - t, Q.pop(), Q.push(t);
    } printf("%lld\n", ans);
    return 0;
}
```




---

## 作者：DEVILK (赞：60)

看chen_zhe大佬的题解看的有点迷~~（我太弱了）~~

来一发自认为还算好理解的解释，欢迎指出bug

更好的阅读体验点击这里：[博客传送门](http://www.cnblogs.com/devilk-sjj/p/9038078.html)

## **【算法分析：】**
对于一个序列，可以看成高度不同的几根线

如：序列{3、 4、 1、 5}可以看做这样


```cpp
                  ----                
     ----
---- 
          
            ----
```

对于一个大数$a$和一个小数$b$，要做的就是在他们之间的任意位置找到一个基准，将大数向下挪到那个基准，小数向上挪到那个基准

移动的距离等价于$a - b$

由于是非降序列，将$a$向下移动的距离越多越可以使之后的数字更容易变成非降序列

所以这个基准应该是选择之前的最大数$c$，

当之前的最大数在$[a,\ b]$这个区间内，将$a$向下移到$c$并将$b$向上移到$c$的距离等价于将$a$向下移动到$b$的距离

　　所以就把$a$移到$b$就好了

　　而由于之前已经有一个$c$值，不把$a$,$b$移动到$c$也能保证之后答案的正确性

　　　　而当之后如果有许多个小数的时候，这么做也能保证之后答案的正确性，因为当前的$c$和当前$b$在这种情况里应该是同属于[之后的$a,~~$之后的$b$]的区间内

当之前的最大数比$b$还要小的时候，$b$就变成了之前非降序列的一部分，$a - b$相当于将$a$向下移动到$b$

由于$c$是之前的最大数（也就是说现在的$a > c$），所以不存在$c$比$a$大的情况

**然后开个大根堆瞎搞：**

对于读进的一个数num，把它push到优先队列里去

如果这个num比之前的最大值maxn（就是堆顶元素）要小的话

　　ans += maxn - num

　　并把maxn弹出，再push进一个num(把maxn移动到了num的位置，这个操作正确性的证明见上面)
  
Ac代码：
```cpp
//序列sequence加强版
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

int n;
long long ans;
priority_queue<int> q;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}

int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        int num = read();
        q.push(num);
        if(num < q.top()) {
            ans += q.top() - num;
            q.pop();
            q.push(num);
        }
    }
    printf("%lld\n", ans);
}
```

---

## 作者：do_while_true (赞：47)

感觉十分厉害的题，记录一下（

有个很显然的 $\mathcal{O}(n\max a)$  的 dp，设 $f_{i,j}$ 为 $a_i$ 变为 $j$，考虑原序列 $[1,i]$ 的最小代价。

显然有：

$$
f_{i,j}=\min_{k\leq j}f_{i-1,k}+|a_i-j|
$$

结论1：$f_{i,j}$ 关于 $j$ 的点相邻两个连起来是一个下凸壳。

证明：

$f_{1,j}=|a_1-j|$，是一个绝对值函数，顶点在 $a_1$。

考虑 $f_{i-1}\to f_{i}$ 会发生怎样的变化。

分类讨论一下，具体可以看[这里的证明](https://www.luogu.com.cn/blog/Mr-Wu/solution-p4597)，我认为写得非常地好，无需多补充，不过请务必看懂有关下凸壳的证明，后面的做法会涉及到加入 $a_i$ 对下凸壳线段的影响。

下凸壳的斜率肯定是递增的。先钦定线段的斜率是不断 $+1$ 的，如果中间出现了断层的现象就当作这个断的地方有长度为 $0$ 的线段，这些线段的斜率补充了中间断层的地方。

再设 $op_i$ 为 $f_i$ 的斜率为 $0$ 的那一条线段的左端点，也是斜率为 $-1$ 的那一条线段的右端点。

我们需要明确一点，最终答案是 $f_{n,op_n}$，换句话说，我们只关心 $f_{n,op_n}$ 的**纵坐标**，不关心 $op_n$ 具体是几，因为问题只要求输出最小的代价。

现在可以完全不管斜率 $>1$ 的线段了，它们怎么变和求答案没有关系。

--- 

考虑维护这些斜率 $\leq 0$ 的线段，设计一个可重元素的由大到小的优先队列（或者说大根堆），其元素为线段的右端点，一个右端点可以重复多次，其线段的斜率为其需要完全 pop 出的次数的相反数。

举个栗子，大根堆为 $\{3,2,2,1,1\}$，那么右端点为 $2$ 的线段的斜率为 $-3$，因为弹出全部的 $2$ 需要把一个 $3$，两个 $2$ 全部弹出。

现在惊奇地发现，这个优先队列恰好对上了我们前面钦定的斜率不断 $+1$ 递增"的"暴论"。

关于要用到的结论上面给出的链接已经证明，我现在重新叙述一遍。

1. 线段单降且在 $a_i$ 左侧，斜率 $-1$（其斜率的数值减去 $1$）；

1. 线段单降且在 $a_i$ 右侧，斜率 $+1$；

1. 线段不单降且在 $a_i$ 左侧，斜率变为 $-1$；

1. 线段不单降且在 $a_i$ 右侧，斜率变为 $1$；


考虑从 $f_{i-1}$ 到 $f_i$，一个 $a_i$ 会对答案造成怎样的影响。

设答案为 $ans$，也就是考虑 $i$ 增加时 $ans$ 如何改变。

Case1: $a_i\geq op_{i-1}$

这个时候 $a_i$ 前面的线段斜率都 $<0$ 了，而 $op_{i-1}$ 又是 $f_{i-1,j}$ 取到最小值时的 $j$，又在 $a_i$ 前面，所以可以从 $op_{i-1}$ 转移而来。答案变为 $f_{i,a_i}$ 处的取值即为 $f_{i-1,op_{i-1}}+|a_i-a_i|$，$ans$ 不变。

由于前面的线段斜率都会 $-1$，要维护堆的意义，就把 $a_i$ push 进堆中，这样堆中所有元素其 pop 完的次数都 $+1$，则斜率就 $-1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/70fzs2um.png)

Case2: $a_i<op_{i-1}$

首先考虑答案改变成什么样子，注意到新的决策点 $op_i$ 即为图中红点和 $op_{i-1}$ 之间的斜率变为了 $0$，所以 $f_{i,op_i}=f_{i,op_{i-1}}=f_{i-1,op_{i-1}}+op_{i-1}-a_i$。例如图中，这个时候每部分的线段的斜率由图中黑色的变成红色的，中间有一段 $-3,-1$ 中间断开了，少了 $-2$，换句话说，由于我们 push 进去了 $a_i$，还想要维护堆的意义，就要把 $op_{i-1}$ 弹出，再把 $a_i$ 压进去，使其拥有斜率为 $-2$ 的段。

我们要维护堆能够以 $1$ 递增实际上是让每次 $a_i<top$ 的时候保证加进去 $a_i$ 后 $top$ 作为右端点代表的线段斜率变为了 $-1$，保证它一定是需要弹出的点。所以多 push 进去是对的。

![](https://cdn.luogu.com.cn/upload/image_hosting/5zvvzbnh.png)

> 图中为一个栗子，值得注意的是两条线段之间的长度可能为 $0$，但这不影响答案。

综上所述，我们得到了一个很简洁的代码来完成这个过程。

时间复杂度 $\mathcal{O}(n\log n)$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 500010;
int n, a;
std::priority_queue<int>q;
long long ans;
signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(a); q.push(a);
		if(a < q.top()) {
			ans += q.top() - a;
			q.pop();
			q.push(a);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

感谢slyz的两位学长的指点以及 [Mr_Wu 的题解](https://www.luogu.com.cn/blog/Mr-Wu/solution-p4597)。

笔者才疏学浅，如有错误欢迎指出，如有疑惑也欢迎提出。

---

## 作者：water_tomato (赞：29)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p4597-%e5%ba%8f%e5%88%97sequence-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/P4597)。

给定一个序列，每次操作可以把某个数 $+1$ 或 $-1$。要求把序列变成非降数列。而且要求修改后的数列只能出现修改前的数。

## 解析

给出一种该题题解区中都没有提到的做法：整体二分。

对于整个区间按照值域进行二分，初始值域为负极大值到正极大值，每次二分都找出 $mid$ 值的分界线，然后对于左右两个区间依次二分。由于分界线左侧的那个数取 $mid$ 一定比取 $mid+1$ 优秀，由题目要求的非降数列可以推知整体也符合该要求，因此整体二分一定是正确的。时间复杂度为 $O(n\log v)$，$v$ 为值域，足够通过本题。

详见代码。



## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int inf=2e9+7;
int n,a[N],b[N];
inline void solve(int L,int R,int l,int r){
	if(L>R||l>=r) return;//边界
	int mid=(l+r)>>1,sum=0;
	for(int i=L;i<=R;i++) sum+=abs(a[i]-mid-1);
	int minn=sum,p=L-1;//初值全部定为 mid+1
	for(int i=L;i<=R;i++){
		sum-=abs(a[i]-mid-1);sum+=abs(a[i]-mid);
		if(sum<minn){
			minn=sum;
			p=i;
		}//找出分界线
	}
	for(int i=L;i<=p;i++) b[i]=mid;
	for(int i=p+1;i<=R;i++) b[i]=mid+1;//尝试赋值
	solve(L,p,l,mid);solve(p+1,R,mid+1,r);//对于两个区间依次继续二分
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	solve(1,n,-inf,inf);//整体二分
	int ans=0;
	for(int i=1;i<=n;i++) ans+=abs(a[i]-b[i]);
	printf("%lld\n",ans);//统计答案
	return 0;
}
```

---

## 作者：L_key (赞：21)

本关卡需要的装备：堆+强大的思考

看了许多堆做法的题解，都只看的个半懂（就是因为我太弱了），最后自己模拟了一下就懂了？！

这里写一份自认为还算能一次看懂的题解。

虽然方法相同，但这是一种新方式来理解这个做法，这是道思维题。

----------


先上操作：
```
//q为大根堆，装b数列
for(int i=1;i<=n;i++)
{
	q.push(a[i]);
	if(a[i]<a.top())
	{	
    		ans+=q.top()-a[i];
		q.pop();q.push(a[i]); 
	}
}
```
没错，核心代码就这些，要先看懂代码流程。

分析：

我们假设“最小花费”是**s**，**x**对应的b数组的值设为**bx**。

一开始，假如遇到前几个是递增的（只有一个也当作递增），那么就令```bi=ai```就好了。

然后新来了一个数**x**比前面b数列中的最大值数**y**小，不满足递增，只需让他们“互相靠近到一起”，使```bx=by```,就能满足**s**还是最小的。

详细点：

为什么y要取最大值，因为要满足递增，我们至少要让**bx**为最大值，而且**by**不变，这样**s**至少要加```y-x```，

如果不想让**bx**跑到**y**那么大，就应该让**by**小一点，假设减小了**c**，

这样**bx**能减**c**，但是因为**by**减**c**后又比**y**小了，所以**bx**变小让**s**减了**c**，但**by**的减少也让**s**加了**c**，所以**s**加的最小值就是```y-x```。

我们让**x**和**y**调整就够了，因为别的数一动就会使**s**增加。

那为了让未来更容易满组递增，应使**bx**和**by**越小越好，我们可以让```by=x```。

**小结**：
就是可以使
```
by=x;
ans+=y-x;//ans+=q.top()-a[i]
```


----------

**Boss is coming！**

问题来了，假设**y**之前的最大值为**z**，如果```x<z<y```,因为```bz=z>x=by```,那```by=x```会使**b**数列不满足递增，像这种情况：
```
	     y
       z
     -     x
   -
 -
```
调整后：
```
	     
       z
     -   y x
   -
 -
```
我们先让它不满足，继续上面的处理方法，

现在突出来了一个**z**，我们等待着未来有一个新来的数把现在的最大值**z**拉下去，使序列合法。

如果到最后不合法，因为在调整**x**和**y**时，**bx**，**by**移到区间[x,y]中任意一个位置都能满足**s**加的最小，

而```y>z>x```,**z**在这个区间内，意味着我们可以最后将不合法的再调整到合法，而**s**不变。

补充：
为什么到这里仍取最大值**y**？

其实我们只是假设by=x这样最好的情况，实际上仍需取最大值满足递增，也就是让最后不合法的序列一定能调整到合法，并且使**s**最小。

上面代码至此说明完毕。


----------


完整代码：
```
#include<cstdio>
#include<queue>
using namespace std;
int n;
priority_queue<int>q;
long long ans;
int main()
{
	scanf("%d",&n);
	ans=0;
	while(n--)
	{
		int a;scanf("%d",&a);
		q.push(a);
		if(a<q.top())
		{
			ans+=(long long)(q.top()-a);
			q.pop();q.push(a); 
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Ashankamiko (赞：12)

# 题目简述
### 题意
给定一个长度为 $n$ 的数列，每次操作可以将数列中的任意一个数 $+1$ 或 $-1$，求最少需要操作几次才能使这个数列变成不下降数列。
### 思路
每次操作，我们都找出当前的最大值，如果 $a_i$ 小于当前的最大值，我们就将 $a_i$ 不断变换，等价于直接用当前最大值减 $a_i$，以此达到不下降数列的目的，因为无论如何变，最终的代价都是不变的，所以可以直接相减，无需考虑其他因素。

模拟一下这个过程，我们不断的输入并进行处理。
```
5 
4 5 1 8 3
```
|$i$ 值|$a_i$|当前最大值|操作数|
|:-:|:-:|:-:|:-:|
|$1$|$4$|$4$|$0$|
|$2$|$5$|$5$|$0$|
|$3$|$1$|$5$|$4$|
|$4$|$8$|$8$|$0$|
|$5$|$3$|$8$|$5$|

所以答案就是 $4+5=9$。

不过如果我们操作结束，那么当前最大值也就不再存在，需要取当前的第二大值，那么这个过程很容易联想到优先队列，优先队列默认从大到小排序，所以我们每次操作都取出当前队首就行了。

## [AC 代码](https://www.luogu.com.cn/record/221704233)
```cpp
#include <bits/stdc++.h>
using namespace std;
#define in cin
#define out cout
#define int long long
priority_queue<int> q; //优先队列

signed main() {
	int n;
	in >> n;
	int x, cnt = 0;
	while (n--) {
		in >> x;
		q.push(x); //先加入队列
		if (x < q.top()) //如果不是最大值
			cnt += q.top() - x, q.pop(), q.push(x); //使之满足不下降数列的要求
	}
	out << cnt;
	return 0;
}
```
注意：当我们操作完成后，要取出队首，并且要再将 $x$ 加入队列，因为这个队列的队首出队后，不会再排序，因此要再加入一次 $x$ 才能使队列中的元素按从大到小排序。

---

## 作者：xiezheyuan (赞：8)

## 思路

整体二分。

我们可以每层枚举当前取多少个中间节点 $\operatorname{mid}$ 使得答案最优，这样就具备了可二分性。

整体二分时间复杂度 $O(n\log n)$，跑的挺快。

## 具体做法

首先统计一个 $\operatorname{sum}=\sum\limits_{i=l}^{r}{a[i]-\operatorname{mid}-1}$ 

然后暴力找 $\operatorname{mid}$（其实可以用数据结构优化，不过没必要）

然后更新我们找到的方案。

接着向下二分。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
int a[1000005];
int b[1000005];

void bs(int l,int r,int vl,int vr){
	if(l>r||vl>=vr)return;
	int mid=(vl+vr)>>1;
	int sum=0;
	for(int i=l;i<=r;i++){
		sum+=abs(a[i]-mid-1);
	}
	int minn=sum,minid=l-1;
	for(int i=l;i<=r;i++){
		sum-=abs(a[i]-mid-1);
		sum+=abs(a[i]-mid);
		if(sum<minn){
			minn=sum;
			minid=i;
		}
	}
	for(int i=l;i<=minid;i++){
		b[i]=mid;
	}
	for(int i=minid+1;i<=r;i++){
		b[i]=mid+1;
	}
	bs(l,minid,vl,mid);
	bs(minid+1,r,mid+1,vr);
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	bs(1,n,LLONG_MIN,LLONG_MAX);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=abs(a[i]-b[i]);
	}
	cout<<ans<<'\n';
	return 0;
}
```

## 扩展

整体二分习题：[P4331 [BalticOI 2004]Sequence 数字序列](https://www.luogu.com.cn/problem/P4331)


---

## 作者：wurzang (赞：7)

本文章参考了神犇 wzporz 的这篇[题解](https://www.luogu.com.cn/blog/Emoairx/boi2004-sequence-ti-xie)



------------


考虑 dp

设 $f_{i,j}$ 为第 $i$ 个数字小于等于 $j$ 且前 $i$ 个数字满足非降序列的最小代价。

显然，有经由最小代价修改后的合法序列由修改前的数字组成。

考虑 dp 转移。第一步有 $f_{i,j}=f_{i-1,j}+|a_i-j|$

第二步有 $f_{i,j}=\min(f_{i,j-1},f_{i,j})$

复杂度为 $\mathcal{O(n \max a_i)}$，考虑如何优化。

第一步可以得出 $f_i$ 是个上凸壳，第二步可以得出 $f_i$ 是个一次函数斜率均 $\le 0$ 的上凸壳。

然后考虑从 $f_{i-1}$ 到 $f_{i}$ 的变化。设 $f_i$ 中斜率为 $0$ 的一次函数的起始点横坐标为 $pos$

1. $a_i<pos$

**也就是令 $-∞ \sim a_i$ 中所有一次函数斜率加一，令 $a_i \sim ∞$ 中所有斜率大于 $0$ 的一次函数斜率减一。**

显然答案增加了 $pos-a_i$

效果如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/41rxli78.png)


![](https://cdn.luogu.com.cn/upload/image_hosting/zub5ofqu.png)


2. $a_i \ge pos$

**也就是令 $-∞ \sim a_i$ 中所有一次函数的斜率加一。**

显然答案没有增加。

效果如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/opnvl21y.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/x9gk8fqe.png)


考虑只维护一次函数"拐点"的横坐标，对于这两种分类讨论（显然 $pos$ 就是"拐点"横坐标中的最大值）

如果 $a_i<pos$，$pos$ 不作为一次函数的"拐点"，直接去掉

如果 $a_i \ge pos$，加入 $a_i$ 作为一次函数的"拐点"。

上述操作直接用堆维护即可。

然而上面的分类讨论是错的，原因是去掉 $pos$ 需要满足条件：以 $pos$ 为终点的一次函数的斜率是 $1$。

如果不存在斜率为 $1$ 的一次函数怎么办？

发现斜率为 $1$ 不存在肯定是因为 $a_i<pos$ 时 "令部分斜率加一,部分斜率减一" 的操作。

我们设 $a_i<pos$ 时 $a_i$ 于 $f_{i-1}$ 所在的一次函数的斜率为 $k$。那么 $f_i$ 中这段一次函数肯定分为了两段，一段斜率为 $k-1$，一段斜率为 $k+1$。所以斜率 $k$ 是不存在的。**所以我们可以往堆中再扔一个 $a_i$，来表示这个不存在的斜率。**

这样，如果斜率 $1$ 不存在的话，去掉 $pos$ 后堆里还有一个 $pos$，并不影响正确性。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<int> q;
int a[500005];
signed main(){
	int n;
	long long ans=0;
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	q.push(a[1]);
	for(int i=2;i<=n;++i){
		int u=q.top();
		if(a[i]<u) q.pop(),ans+=(long long)u-a[i],q.push(a[i]),q.push(a[i]);
		else q.push(a[i]);
	}
	cout<<ans;
	return 0;
}
```




------------


顺便一提，上述部分思路还可以用在 [APIO2016 烟火表演](https://www.luogu.com.cn/problem/P3642) 和 [A New Beginning](https://codeforces.com/contest/1534/problem/G) 中。这种技巧好像叫 Slope Trick

由于读者本人水平有限，所以可能有许多错误，欢迎读者在评论区下查漏补缺（

---

## 作者：coool (赞：6)

##### P4597 序列 sequence 个人题解

> 本题类似 [CF865D Buy Low Sell High](https://www.luogu.com.cn/problem/CF865D)。

CF865D：给定股票价格序列，每天买一股、卖一股或者什么的都不做，要求最后一天结束时不持有股票，问最大利润。

### 具体思路
对于给出的一个数列 $S$ $=$ $${a_1,a_2,a_3,...,a_n}$$，不妨一位一位地进行考虑。

具体地，给定 ${1,4,3,5,2}$：

- 我们首先从 $1$ 开始，一位数我们也将其视为**非降的**。
- 接着到第二位 $4$，发现 ${1,4}$ 仍然**递增**。
- 接着到第三位 $4$，这时发现 ${1,4,3}$ **不满足非降**，显然，我们需要使 $4$，$3$ 满足**非降**，这时我们有两个选择：$I.$ 让 $4$ 减去 $1$，$II.$ 让 $3$ 加上 $1$，均可满足。于是这里操作数 $+1$。
- 接着到第四位 $5$，发现仍然**非降**。
- 最后到第五位 $2$，发现 ${5,2}$ **不满足非降**，但这里不同于第三步，我们只能修改 $2$ 的值，若我们修改 $5$ 的值，前面的序列就**不满足非降**了，因此这里让 $2$ 加三次 $1$。于是这里操作数 $+3$。

综上，对于这组数据我们显然可以得出答案 $Ans=1+3=4$。



通过以上模拟，我们可以得出结论：对于给出的一个数列 $S$ $=$ $${a_1,a_2,a_3,...,a_n}$$，当我们从第 $i$ 位枚举到第 $j$ 位时，我们需要求出区间 $[a_i,a_j]$ 的最大值 $maxd$，区间 $[a_i,a_j]$ 对答案$Ans$的贡献值 $w_i$ 即为 $| maxd-a_j |$。

故答案 $Ans = $  $\sum_{i=1}^{n}| maxd-a_j |$。

这里用堆来维护区间最大值，故时间复杂度为：$O(n \log n)$。

### 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
priority_queue<int,vector<int>,less<int>> q;

int n,ans; 
signed main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		int x;
		cin >> x;
		if (!q.empty() && q.top() > x){
			ans += abs(q.top()-x);
			q.pop();
			q.push(x);	
		}
		q.push(x);
	} 
	cout << ans << endl;
	return 0;
}
```

---

## 作者：raincity (赞：5)

## 题面

[P4597 序列sequence](https://www.luogu.com.cn/problem/P4597)

## 解答

### 方法1（不是重点，因为超时，可以不看）
方法：$\color{red}\text{动态规划}$

定义状态$dp_{i,j}$表示将前$i$个数非降序排列，最后一项是$j$需操作的最小次数。

状态转移方程：$dp_{i,j}=\max{dp_{i-1,k} + |i - k|}$

> 而且要求修改后的数列只能出现修改前的数。

所以我们可以离散化，$j$的范围变为$[1, n]$。

这样的时间复杂度是$O(n^2)$。~~又长又臭还TLE的~~代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX = 505;
int dp[MAX][MAX], a[MAX], b[MAX], tot, n, m;

int main() {
	cin >> n;
	memset(dp, 0xcf, sizeof(dp));
	for (int i = 1; i <= n; i++)
		cin >> a[i], dp[i][0] = 0;
	cin >> m;
	for (int j = 1; j <= m; j++)
		cin >> b[j], dp[0][j] = 0;
	for (int i = 1; i <= n; i++) {
		int val = 0, pos = 0;
		for (int j = 1; j <= m; j++) {
			if (a[i] == b[j])
				dp[i][j] = val + 1, pre[i][j] = pos;
			else
				dp[i][j] = dp[i - 1][j], pre[i][j] = j;
			if (b[j] < a[i] && dp[i - 1][j] >= val)
				val = dp[i - 1][j], pos = j;
//			cout << i << " " << j << " " << dp[i][j] << " " /*<< pre[i][j] */<< endl;
		}
	}
	int p = 1, ans = dp[n][1];
	for (int i = 1; i <= m; i++)
		if (dp[n][i] > ans)
			ans = dp[n][i], p = i;
	cout << dp[n][p] << endl;
	return 0;
}
```
很明显无法通过。

### 方法2（重点）
方法：$\color{red}\text{贪心}$

假如$a_i$至$a_j$已经非降序排列，但是$a_{j+1}$<$a_k(i \le k \le j$且$a_k$是$a_i$至$a_j$的最大值)的话,我们必须调整。最容易想到将$a_k$减小，$a_{j+1}$增大，直到相等。这样花费了$a_k-a_j+1$次操作。最好的话，我们应该把$a_k$减少到$a_{j+1}$，这样能够最大限度减少后面的数大于$a_k$的数量。

但是出现了一个问题。$a_k$变小了，$a_i$到$a_j$就有可能不是非降序排列了。不过这个问题实际上不需要考虑，因为我们这样遍历数组后得到的答案，策略是有活动空间的。假如我们已经通过另外一些调整使$a_m$至$a_n$满足条件，而且$a_{m-1}>a_m$，则$a_{m}$一定是与之后的一个数相等的。原因在前文：

> 我们应该把$a_k$减少到$a_{j+1}$

我们就可以把$a_{m}$不下调过多，少下调一些即可。因为原来$a_{m-1} <= a_m$($a_m$是最大值呀)，只需要下调到$a_{m-1}$的大小就行了。怎么保证不下调到后面的那个数不会产生新的调整呢？这是因为如果有$a_{m}' > a_p(p > m)$的话，按照原来的策略，$a_{m-1}$作为新的最大值，会减小成$a_p$，重新变回非降序列。

实现：因为需要求最大值，所以要一个堆。时间复杂度$O(n \log n)$。

#### Code
```cpp
#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

int main() {
	int n, x;
	long long ans = 0;
	priority_queue <int> Q;
	scanf("%d%d", &n, &x);
	Q.push(x); 
	while (--n) {
		int tp = Q.top();
		scanf("%d", &x);
		if (x < tp) {
			ans = ans + tp - x;
			Q.pop();
			Q.push(x);
		}
		Q.push(x);
	}
	cout << ans << endl;
	return 0;
}
```

### THE END

---

## 作者：JHPOTATO (赞：4)

尝试给出一个比较严谨的贪心证明。

序列的最终状态一定是若干连续段，并且每个连续段的值是单调增的。

对于每个段，我们都有方法可以调整到最终状态的花费并使得最优。比如先对段内元素进行排序，然后从两端不断抽出元素，把它们差的绝对值累加，当剩余元素不足 $2$ 个时停止。

这种方案的正确性容易证明：由绝对值的几何意义可知，线段上两点到它们之间任意一点的距离相同，所以只需要从外到内累加，它们的中位数一定能被取到，总数为偶数时取较小值作为中位数。

于是可以定义一个“中和” 操作：取一个二元组 $\left ( a,b \right )$，满足 $b<a$，把他们同时调整为 $\left [ b,a \right ]$ 之间的任意整数 $c$，花费为 $a-b$。

由于最终每段互相独立且中位数单调递增，所以一定能通过“中和” 操作取到最优解。

但是仍有部分限制：“中和” 操作所选的数不能有重复，因为这相当于把三个数都限定为它们的中位数。比如取了 $\left ( a,b \right )$ 和 $\left ( b,c \right )$，由于 $b$ 同时属于 $\left [ b,a \right ]$ 和 $\left [ c,b \right ]$，所以 $a,b,c$ 都只能取值为 $b$。

但稍作观察即可发现，只对 $\left ( a,c \right )$ 进行“中和” 操作即可达到更优的效果，不妨将其命名为“改接”。

尝试动态维护最优序列，若加入新数仍满足单调不降，那么把它作为一个自由元加入大根堆，若加入后不满足，就用“中和” 操作处理，花费为堆顶元素与其的差，弹出堆顶，并将这个数加入大根堆**两次**。

为什么是两次？原因很简单：如果想把这个数作为大数再与更小的数进行“中和” 操作，首先要通过“改接”，使其变成自由元，同时补上少的那部分花费，下一次才能用它进行“中和”。

这时大根堆中元素有两种类型：自由元和待“改接” 的元素。自由元的值就是它本身，而待“改接” 元素的存在说明这个元素（不妨设为 $x$）与一个更大的数 $y$ 进行了“中和”，那么这两个数的值域为 $\left [ x,y \right ]$，又因为要使最大值尽可能小，所以当前序列的最大值就是堆顶元素的值。

容易发现每次操作的代价一定是最少的，现在只需证明能通过这样操作得到合法序列。

加入后满足单调不降显然合法，只需证明加入后不满足仍成立，设堆顶元素值为 $d$。

如果堆顶是自由元，直接“中和” 即可，因为两数仍然能取到 $d$，所以一定合法。

如果堆顶元素要进行“改接”，由于“改接” 前较大值的取值已经限定为 $d$ 了，那么从它开始到末尾的所有值只能为 $d$，“改接” 后值域扩大，一定还能取到 $d$，并且新增自由元的值也是 $d$，所以合法。

纵上，处理完新元素后序列仍合法，同时因为每不操作一定最优且可以只用“中和” 操作得到最优解，所以该算法正确。

代码已经有很多了，这里就不粘了。

---

## 作者：STL_qwq (赞：3)

这是一道思维性很强的题，写一发题解帮助我自己和大家理解。

**原题链接：**[传送门](https://www.luogu.com.cn/problem/P4597)


------------
### 题目大意：

增减数列中的数使其变为数列中的其他数进而使得数列变为非降序数列。

------------
### 分析：

这道题的实质是一个反悔贪心。

#### 规则：

我们从头开始扫这个数列，对于 $a_1\sim a_i$ 的数列：

1.若 $a_{x+1} \le a_1  \sim a_x$ 中的最大值,直接加入即可。

2.否则我们要将 $a_{x+1}$ 与 $a_1 \sim a_x$ 中的最大值的差值计入答案。

为什么呢？

我们看到这样一个数列：$[4,7,5,8]$。

我们很容易看出答案：序列 $[4,7,7,8],ans=2$。

但如果数列是这样的：$[4,7,2,6]$。

那么我们将发现：我们在加入第三个元素时，序列变为 $4,4,2$,这样的序列就不严格下降了，但我们接着模拟，加完第四个元素后就变成了 $[4,4,2,4],ans=5$。

那正确的序列是怎么样的呢？

我们手推一下可以发现，是 $[4,5,5,6],ans=5$。

**$ans$ 是一样的！**

再多几组数据？

我们佷容易发现，$ans$ 的最小值是可以被数列中数之间的关系算出来的，而与序列处理后是什么样的，是升序还是降序无关。

所以我们可以理解：“概括一下，对于当前的数，无论最优解如何，对答案的贡献是一定的。而为了保证之后的解也最优，令 $y$ 减小到 $x$ ，可以保证之后的解最优，且不会影响当前的最优解。”这段话。——载自 [bztMinamoto](https://www.luogu.com.cn/user/41781) 大佬的题解。

然后加个优先队列维护区间最大值，我们就可以愉快地写出这题代码啦！

------------
### AC 代码

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#define ll long long//记得开 long long

using namespace std;

const int N=5e5+10;
ll n,a[N],ans=0;
priority_queue<ll> q;

int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		q.push(a[i]);
		if(a[i]<q.top()){
			ans+=q.top()-a[i];
			q.pop();
			q.push(a[i]);//把maxn移动到a[i]的位置 
		}
	}
	printf("%lld",ans);
	return 0;
}
```
### 参考资料：[大佬博客](https://blog.csdn.net/Dove_xyh/article/details/104744900)

**_Thanks for reading!_**

---

## 作者：_Clown_ (赞：3)

# P4597.序列sequence
这道题目我们可以考虑直接上 STL。

我们一个数一个数地放进一个大根堆(优先队列)，

其实就是算到当前数时，

取前面最大的数出来。

假如现在这个数比前面最大数大或相等就没事，

反之我们则需要考虑如何改为不降。

我们肯定是将大的往小移，将小的往大移，

那么花费一定是 $|a-b|$。

为了不影响先前的答案，

当然都是移到同一基准，

即是先前的最大数。

代码不难写出。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
long long Total;
priority_queue< long long >Queue;
int main(void)
{
	BetterIO;
	register long long i;cin>>Total;
	register long long Ans(0);
	for(i=1;i<=Total;i++)
	{
		register long long Now;cin>>Now;
		Queue.push(Now);
		if(Queue.top()>Now)
		{
			Ans+=Queue.top()-Now;
			Queue.pop();
			Queue.push(Now);
		}
	}
	cout<<Ans<<endl;
	return 0;
}
```

---

## 作者：arrow_king (赞：2)

# 【算法分析】
假设我们要把 $a$ 转为 $b$ ，那么我们需要 $\left\vert a-b \right\vert$ 的代价。所以，既然怎么移都是 $\left\vert a-b \right\vert$ ，那就直接将 $a$ 移到 $b$ 就好了。    
**然后开个大根堆瞎搞：**    
假如我们读入了一个数 $a$ ，由于前面已经排好了序，这时候我们只需要考虑 $a$ 和当前已排序序列的最大值就可以了。
- 如果当前输入值 $a$ 不比队列最大值小，那就二话不说，直接塞！
- 如果 $a$ 比最大值小，那么就将答案加上它们的差，再将 $a$ 入队。    

至于如何找最大值，如果枚举一遍，时间复杂度 $\mathcal{O}(n^2)$ ，面对 $n\leqslant5\times10^5$ 的数据量肯定TLE。   
所以我们用堆，也就是STL的priority_queue，时间复杂度 $\mathcal{O}(n\log n)$ 。    
**代码如下：**
```
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
#define ll long long
priority_queue<ll> q;               //！！不开long long会十个WA
ll ans=0;
int main() {
  int n;
  cin>>n;
  while(n--) {
  	ll a;
  	cin>>a;
  	q.push(a);                      //用大根堆来排序
  	if(q.top()>=a) {
  		ans+=q.top()-a;
		q.pop();
  		q.push(a);
  	}
  }
  cout<<ans<<endl;
  return 0;
}
```
希望管理员审核通过！     
看在手敲的份上，给个赞再走好不好~

---

## 作者：xiayuanxia (赞：1)

### **P4597 序列 sequence** 题解思路

这题让我联想到 **P2893**（[USACO08FEB] Making the Grade G），它们都涉及调整序列使其满足某种单调性的最小代价问题。


#### **关键观察**
对于当前数字 $a$ 和下一个数字 $b$，有两种情况：
1. **$b \geq a$**：直接保留 $b$，无需调整。
2. **$b < a$**：需要调整，要么：
   - 把 $a$ **减小**到 $b$（相当于修改前面的数），
   - 把 $b$ **增大**到 $a$（相当于修改后面的数）。

为了最小化总操作次数，我们希望在调整时尽量**减少对后续数字的影响**，因此选择**调整前面的数**更优。

#### **贪心策略**
我们可以维护一个**大根堆**（`priority_queue<int>`），模拟调整过程：
1. **遍历序列**，逐个处理数字 $a$。
2. **如果 $a \geq$ 堆顶元素**，直接加入堆（无需调整）。
3. **否则**：
   - 堆顶元素 $q_{\text{top}}$ 比 $a$ 大，说明需要调整。
   - 最优策略是**把 $q_{\text{top}}$ 降到 $a$**（因为调整前面的数可以减少后续调整次数）。
   - 记录操作代价 $ans \gets ans + (q_{\text{top}} - a)$。
   - 弹出 $q_{\text{top}}$，并**重新插入 $a$ 两次**（因为调整后，$a$ 可能影响后续数字）。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n;
    cin >> n;
    priority_queue<int> q;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        q.push(a);
        if (a < q.top()) {
            ans += q.top() - a;
            q.pop();
            q.push(a);  
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：tony0530 (赞：0)

## 前置芝士

首先，请注意 Slope Trick 可不是斜率优化，是一种通过维护斜率序列的优化，它是有一定范围限制的：

- 连续。
- 是分段一次函数。
- 是凸函数。
- 每一段的斜率较小（通常为 $O(n)$），且均为整数。

我们发现如果此上类型的函数相加之后还是上面的一种函数。

它通常用来维护 DP，维护满足以上条件的函数的斜率加减来将函数平移，翻转，相加，取前缀/后缀 $\min$，求 $\min,\argmin$，维护方法如下：

可以先维护在某个 $x_0$ 处的 $f(x_0)$，$k_0$ 以及函数每个斜率变化点的集合。具体地，如果函数在 $x$ 位置斜率增加了 $\Delta_k$，就在集合中插入 $\Delta_k$ 个 $x$。

对于相加：将 $f(x_0)$，$k_0$ 直接相加，斜率变化点的集合直接合并。常用于加一次函数、绝对值函数。

对于取前缀/后缀 $\min$：去掉 $k >0\ or\ k < 0$ 的部分。

对于求 $\min，\argmin$：提取 $k = 0$ 的部分。

对于平移：维护 $f(x_0)$，$k_0$ 的变化，斜率变化点在全局打平移标记。

对于翻转：维护 $f(x_0)$，$k_0$ 的变化，斜率变化点在全局打翻转标记。

好了，可以开始做题了^v^。

## 思路

我们先考虑朴素的方法，定义 $f_{i，j}$ 为考虑 $1 ~i$ 能满足是非降数列且最后一个数是 $j$ 的最小花费。
则有 $f_{i,j} = \min_{k \le j}\{f_{i-1,k} + |j - a_i|\}$，但是这是过不去的，~~但是[# P2893 [USACO08FEB] Making the Grade G](https://www.luogu.com.cn/problem/P2893)  是能过滴~~。注意到只要设 $g_i(j) = f_{i,j}$ 发现这 $g_i$ 是满足 Slope Trick 的函数的条件！用因为 $g_i$ 就是 $g_{i - 1}$ 先取前缀再取 $\min$ 得到的，显然用 Slope Trick 呀！就做完了，按上面做就行了！

**代码如下：**

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 10;

int n;
int a[N];
priority_queue<int> heap;
int ans;

signed main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++ ) cin >> a[i];
    for(int i = 1 ; i <= n ; i ++ )
    {
        if(heap.size() == 0)
        {
            heap.push(a[i]);
            continue;
        }
        if(heap.top() > a[i])
        {
            ans += (heap.top() - a[i]);
            heap.pop();
            heap.push(a[i]);
        }
        heap.push(a[i]);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

给定一个有 $n$ 个正整数的数组，一次操作中，可以把任意一个元素加一或减一。求使得原序列严格递增的求最小操作次数。

# 题目分析

$\rm CF713C$：

虽然可以用 $\mathcal{O(n^2)}$ 的显然 $\verb!Dp!$ 水过，但是为了完成 $\rm P4597$ 和 $\rm P4331$，所以还是学了学 $\mathcal{O(n\log n)}$ 的优秀做法。

先把“严格递增”改成“非严格递增”。

具体地，$a_1\lt a_2\lt a_3\to a_1\le a_2-1\le a_3-2\to a_1-1\le a_2-2\le a_3-3$，即 $a_i\to a_i-i$。

然后用大根堆来维护。算到 $a[i]$ 时，取前面的最大数 $maxx$ 出来。因为要保持非严格递增，所以 $a[i]$ 小于 $maxx$ 时就必须做出一些决策了，这也就是 $|maxx-a[i]|$。

$\rm P4597$：

板子。

# 代码

$\rm CF713C$:

```cpp
//2022/5/3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <queue>
#define int long long
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 3005;
int a[N];
std::priority_queue<int>q;
int n;
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	n = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read() - i;
	int ans = 0;
	for (register int i = 1;i <= n; ++ i) {
		q.push(a[i]);
		if (q.top() > a[i]) {
			ans = ans + Abs(q.top() - a[i]);
			q.pop();
			q.push(a[i]);
		}
	}
	printf("%lld\n",ans);

	return 0;
}
```

$\rm P4597$：

```cpp
//2022/5/3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <queue>
#define int long long
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 5e5 + 5;
int a[N];
std::priority_queue<int>q;
int n;
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	n = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	int ans = 0;
	for (register int i = 1;i <= n; ++ i) {
		q.push(a[i]);
		if (q.top() > a[i]) {
			ans += Abs(q.top() - a[i]);
			q.pop();
			q.push(a[i]);
		}
	}
	printf("%lld\n",ans);

	return 0;
}
```

---

