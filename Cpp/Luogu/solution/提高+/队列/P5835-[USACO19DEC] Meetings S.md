# [USACO19DEC] Meetings S

## 题目描述

有两个牛棚位于一维数轴上的点 $0$ 和 $L$ 处（$1 \leq L \leq 10^9$）。同时有 $N$ 头奶牛（$1 \leq N \leq 5 \times 10^4$）位于数轴上不同的位置（将牛棚和奶牛看作点）。每头奶牛 $i$ 初始时位于某个位置 $x_i$，并朝着正向或负向以一个单位每秒的速度移动，用一个等于 $1$ 或 $-1$ 的整数 $d_i$ 表示。每头奶牛还拥有一个在范围 $[1,10^3]$ 内的重量。所有奶牛始终以恒定的速度移动，直到以下事件之一发生：
- 如果奶牛 $i$ 移动到了一个牛棚，则奶牛 $i$ 停止移动。
- 当奶牛 $i$ 和 $j$ 占据了相同的点的时候，并且这一点不是一个牛棚，则发生了相遇。此时，奶牛 $i$ 被赋予奶牛 $j$ 先前的速度，反之亦然。注意奶牛可能在一个非整数点相遇。

令 $T$ 等于停止移动的奶牛（由于到达两个牛棚之一）的重量之和至少等于所有奶牛的重量之和的一半的最早时刻。请求出在时刻 $0 \ldots T$（包括时刻 $T$）之间发生的奶牛对相遇的总数。


## 说明/提示

### 样例解释

在这个例子中，奶牛们按如下方式移动：

1. 第一和第二头奶牛于时刻 0.5 在位置 1.5 相遇。此时第一头奶牛拥有速度 -1，第二头奶牛拥有速度 1。
2. 第二和第三头奶牛于时刻 1 在位置 2 相遇。此时第二头奶牛拥有速度 −1，第三头奶牛拥有速度 1。
3. 第一头奶牛于时刻 2 到达左边的牛棚。
4. 第二头奶牛于时刻 3 到达左边的牛棚。
5. 由于到达牛棚的奶牛的总重量已经至少是所有奶牛的总重量的一半，这个过程此时终止。如果继续进行下去，第三头奶牛将会在时刻 4 到达右边的牛棚。

发生了恰好两次相遇。 

### 子任务

测试点 $2\sim 4$ 满足 $N\le 10^2$，并且对所有 $i$，$w_i=1$。

测试点 $5\sim 7$ 满足 $N\le 10^2$。

供题：Benjamin Qi

## 样例 #1

### 输入

```
3 5
1 1 1
2 2 -1
3 3 -1```

### 输出

```
2```

# 题解

## 作者：kradcigam (赞：31)



# 前言

这道题目是道好题，想通了之后就可以把轻松这道题做出来。

# 正文

## 结论

先把一个结论写出来。

无论所有奶牛怎么走，它们的体重从左往右组成的序列是不会发生改变的。

这个结论简单地说明一下。

1. 首先我们可以把 $2$ 头牛相遇看成 $2$ 头牛走的方向不变，只是交换了体重。

2. 如果这些奶牛的体重从左往右组成的序列发生改变，一定是 $2$ 头牛相向而行，然后发生序列变化。但是现在我们可以把交换体重看做**如果序列发生变化，就将 $2$ 数交换，不让序列发生改变。**

## 分析

### 二分·时间

有了这个性质，就好办了。

我们发现时间是有单调性的，然后我们就可以二分时间。

```cpp
int ll=0,rr=INT_MIN>>1;
while(ll+1<rr){
	int mid=(ll+rr)>>1;
	if(check(mid))rr=mid;
	else ll=mid;
}
```

至于 $check$ 怎么写呢？

我们先要把 $a$ 数组是 **按位置从小到大排序。**

```cpp
sort(a+1,a+n+1,cmp);
```

$cmp$：

```cpp
bool cmp(node x,node y){
	return x.x<y.x;
}
```



先放一下代码。

```cpp
bool check(int x){
    int llll=1,rrrr=n,s=0;
    for(int i=1;i<=n;i++)
    	if(a[i].d==1)s+=a[i].x+x>=l?a[rrrr--].w:0;//如果能到，重量就是a[rr--].w
    	else s+=a[i].x-x<=0?a[llll++].w:0;//如果能到，重量就是a[ll++].w
    return s*2>=sm;
}
```

其实就是

```cpp
bool check(int x){
    int ll=1,rr=n,s=0;
    for(int i=1;i<=n;i++)
    	if(a[i].d==1){
    		if(a[i].x+x>=l)s+=a[rr--].w;//如果能到，重量就是a[rr--].w
    	}else{
    		if(a[i].x-x<=0)s+=a[ll++].w;//如果能到，重量就是a[ll++].w
    	}
    return s*2>=sm;
}
```

解释一下，有人可能会

问：

> 程序里的体重不一定对啊？

答：

> 最后的体重显然是
>
> $\sum\limits_{i=1}^{k1} w_{i}+\sum\limits_{i=k2}^{n} w_{i}$
>
> 因为最后到达牛棚的，一定是达到  $0$  的若干个，到达 $L$ 的若干个，再联系一下上面的性质，就显然是这个式子了。当然我们的 $a$ 数组是 **按位置从小到大排序的。**

### 二分·查找

我们知道了时间，距离 $AC$ 还需要找到奶牛相遇的对数的总数。

现在，我们的 $a$ 数组已经按位置从小到大排序了。

我们从左往右扫过去，我们知道，相遇的对数 $=$ 往左走的奶牛所碰到往右走的奶牛的数量之和。

那么碰到的往右走的奶牛的数量之和，我们可以用**二分**来统计。

```cpp
for(int i=1;i<=n;i++){
	if(a[i].d==-1){//向左走
		int xx=a[i].x-rr*2;//这里注意速度是1+1=2
		int lll=0,rrr=k+1;//二分，注意边界
		while(lll+1<rrr){
			int mid=(lll+rrr)>>1;
			if(f[mid]>=xx)rrr=mid;
			else lll=mid;
		}
		ans+=k-rrr+1;
	}else{
		f[++k]=a[i].x;
	}
}
```

这里的二分是在找**能与这头向左走的牛相遇的最左边的牛。** 

这里的 $f$ 数组是记录向右走的牛。

## 总代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
template<typename T>void write(T x){
	if(x<0)putchar('-'),x*=-1;
	if(x>9)write(x/10);
	putchar(x%10+48);
}
const int MAXN=5e4+10;
struct node{
	int w,x,d;
}a[MAXN];
int n,l,sm,f[MAXN],k,ans;
bool cmp(node x,node y){
	return x.x<y.x;
}
bool check(int x){
    int ll=1,rr=n,s=0;
    for(int i=1;i<=n;i++)
    	if(a[i].d==1)s+=a[i].x+x>=l?a[rr--].w:0;
    	else s+=a[i].x-x<=0?a[ll++].w:0;
    return s*2>=sm;
}
int main(){
	read(n);read(l);
	for(int i=1;i<=n;i++)read(a[i].w),read(a[i].x),read(a[i].d),sm+=a[i].w;
	sort(a+1,a+n+1,cmp);
	int ll=0,rr=INT_MAX>>1;
	while(ll+1<rr){
		int mid=(ll+rr)>>1;
		if(check(mid))rr=mid;
		else ll=mid;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i].d==-1){
			int xx=a[i].x-rr*2;
			int lll=0,rrr=k+1;
			while(lll+1<rrr){
				int mid=(lll+rrr)>>1;
				if(f[mid]>=xx)rrr=mid;
				else lll=mid;
			}
			ans+=k-rrr+1;
		}else{
			f[++k]=a[i].x;
		}
	}cout<<ans;
	return 0;
}
```

# 后记

总体来讲，这道题目细节比较多，思维难度也比较高。

所以，如作者有错误请在评论区指出，谢谢。

---

## 作者：VinstaG173 (赞：13)

### 前言

机房里各位说这是银组最难的一题，但是想通了好像也不是特别难的样子……（好像我们全机房的做法都比我复杂QwQ）

首先有一道题叫做[Piotr's Ants](https://www.luogu.com.cn/problem/UVA10881)。这题和Piotr's Ants好像差不多，但是更难一些。

### 正文

首先我们不考虑重量，于是我们容易发现可以把相遇变成直接穿过。

我们又发现牛相遇会掉头，所以牛的相对位置不变（即最开始是左边第$k$只牛，之后肯定一直是左边第$k$只牛）。

我们又可以将牛的相对位置对应到它的重量。

这时候，我们就可以用以下的方法来计算出整个过程结束的时间$T$：

1. 我们把每只牛看作一直沿着初始的方向走，计算它们走到牛棚的时间$t_i$与进入的牛棚$h_i$。由于我们可以看作直接穿过，所以当且仅当在每个$t_i$时刻有一只牛进入了牛棚$h_i$。

2. 然后我们可以将下标按$t_i$从小到大排序，然后按$t_i$升序扫描，扫到一个$t_i$时看$h_i$，因为牛的相对位置不变，所以最左边的牛没有进入$0$处的牛棚时左边第二只牛不可能进入$0$处的牛棚。于是我们对于$h_i$为$0$或$L$处的牛棚依次在进入牛棚的牛重量和中加上当前没有进过牛棚的最左边或最右边的牛的重量，然后把这只牛标记为已经进入牛棚（相当于一个双端队列的队头或队尾出队）。

3. 当某一只牛的重量被加上后进入牛棚的牛总重量超过全部牛重量和的一半时，$T$就是当前这只牛进入牛棚的时间$t_i$。

计算出$T$，我们就可以计算牛的相遇次数了。

我们首先知道对于每只牛，由于我们可以看作相遇直接穿过，所以我们对于每只牛直接让它走$T$时间，最后到达的位置上肯定有牛。

我们会发现如果这样的话每只牛初始和结束时的相对位置会改变。我们知道，如果一只牛的相对位置从$i$变成$j$，那么原来相对位置在$i$至$j$之间除这只牛以外的牛必须都与它相遇了，它才可能完成相对位置从$i$到$j$的过程。

我们视线追踪每只牛，看它们直接走的过程中相遇，那么在整个过程的进行中肯定有一次相遇发生在这个时间这个地点。

于是我们对于每只牛将它们的最终位置进行排序，然后将排序后的下标与初始下标取差的绝对值，求和，又因为一次相遇有两只牛，我们追踪每只牛时计算了两次，于是我们将得到的和除以2就得到了答案。

但是在牛棚的相遇不算相遇，而如果时刻$T$有牛在同一点则算相遇，我们需要处理这个。

其实我们只要在`std::sort`的`cmp`函数里对牛棚和非牛棚“区别对待”，对于位置相等且是牛棚就按初始的相对位置升序排序，不在就按降序排序，只要这样，我们就可以保证牛到了牛棚里不被算作是相遇，不在牛棚里被算作是相遇了。

Code:
```cpp
#include<cstdio>
#include<algorithm>
int L,N,T,W;
struct cow
{
	int tim,hos;
}c[50003];
inline bool cmp(cow a,cow b)
{
	return a.tim<=b.tim;
}
struct COW
{
	int id,tmp;
}C[50003];
inline bool CMP(COW A,COW B)
{
	if(A.tmp==B.tmp)return (A.tmp==L||A.tmp==0)?A.id<B.id:A.id>B.id;
	return A.tmp<B.tmp;
}
struct Cow
{
	int wh,st,dr;
}Cw[50003];
inline bool Cmp(Cow a,Cow b)
{
	return a.st<b.st;
}
int w,x,d;
int main()
{
	scanf(" %d %d",&N,&L);W=T=0;
	int wt=0;
	long long nm=0;
	for(int i=0;i<N;++i)
	{
		scanf(" %d %d %d",&w,&x,&d);W+=w;Cw[i].st=x;Cw[i].dr=d;Cw[i].wh=w;
	}
	std::sort(Cw,Cw+N,Cmp);
	for(int i=0;i<N;++i)
	{
		c[i].tim=(Cw[i].dr>0)?L-Cw[i].st:Cw[i].st;c[i].hos=(Cw[i].dr>0)?1:0;
	}
	std::sort(c,c+N,cmp);
	int min=0,max=N-1;
	for(int i=0;i<N;++i)
	{
		wt+=Cw[(c[i].hos)?max--:min++].wh;
		if((wt<<1)>=W){T=c[i].tim;break;}
	}
	for(int i=0;i<N;++i)
	{
		C[i].id=i;C[i].tmp=(Cw[i].dr==1)?((Cw[i].st+T>L)?L:Cw[i].st+T):((Cw[i].st<T)?0:Cw[i].st-T);
	}
	std::sort(C,C+N,CMP);
	for(int i=0;i<N;++i)
	{
		nm+=(C[i].id>i)?C[i].id-i:i-C[i].id;
	}
	printf("%lld\n",nm/2);
	return 0;
}
```

---

## 作者：UltiMadow (赞：12)

是时候祭出全谷（目前）最快解法了

### 前言
考场上看到这道题我是懵*的，然后打了$O(n^2logn)$的，过了7个点走人  
于是我考后去问了老师，结果老师告诉我这道题是一道队列的好题，于是，时隔半个月，我AC了这道题

### 解法
我采用了一个和所有题解都不一样的做法

首先，思路和其他题解是一样的，就是：  
1、算出T  
2、算出碰撞次数  
3、把每次碰撞是都看成是穿过，而不是反弹，并交换体重

P.S. 以下的计算全部都是把碰撞看成穿过并交换体重

#### 1 如何计算T
题解们都用的是二分$O(nlogn)$+两次排序$O(nlogn)$  
而我是用的四遍$O(n)$统计+两次排序$O(nlogn)$

接下来，我来讲讲我是如何计算T的

既然都已经穿过去了，那么，我们只要考虑每一头牛去到牛棚时的体重就好了

我们先来找一找规律：  
```
编号：  1  2  3  4
重量：  2  3  1  5
方向：  -> -> -> <-
```
我们单独考虑向右的奶牛们

当经过一系列的碰撞之后，向右的奶牛们的体重变成了：
```
编号：  1  2  3
重量：  3  1  5
```
这应该比较好理解吧

当这个向右的奶牛队列又遇到了一位向左的，体重为2的奶牛呢？
```
编号：  1  2  3
重量：  1  5  2
```
至此，规律基本上就推出来了  
当一个（同方向）奶牛遇到了一个反方向来的奶牛时  
第1头牛的重量变成第2头牛的重量，第2头牛的重量变成第3头牛的重量……最后一头牛的重量变成遇到的奶牛的重量

看到这里，我们的**队列**就出场了

我们可以先把所有奶牛按坐标从大到小排序  
然后用队列来维护向一个方向的奶牛（体重）队列  
按照顺序扫描每一个奶牛  
如果这是和队列维护的同方向奶牛，直接加入队列  
如果不是，弹出队头，并把这头牛的体重加入队列（根据上面的规律）

这里有个细节，就是在处理向原点走的奶牛时要从后往前扫描 ~~（自行理解，想一想，为什么）~~

求T的代码：
```cpp
	sort(cow+1,cow+n+1,cmp);//按照坐标排序
	for(int i=1;i<=n;i++)
	{
		if(Q1.empty()&&cow[i].d==-1)continue;//Q1存速度为1的奶牛的队列
		if(cow[i].d==1)Q1.push(cow[i].w);
		else Q1.pop(),Q1.push(cow[i].w);
	}
	for(int i=n;i>=1;i--)
	{
		if(Q2.empty()&&cow[i].d==1)continue;//Q2存速度为-1的奶牛的队列
		if(cow[i].d==-1)Q2.push(cow[i].w);
		else Q2.pop(),Q2.push(cow[i].w);
	}
	for(int i=1;i<=n;i++)
		if(cow[i].d==1)
		{//ncow存每头牛到达农场时的重量和体重
			ncow[i].t=L-cow[i].x;
			ncow[i].w=Q1.front();
			Q1.pop();
		}
	for(int i=n;i>=1;i--)
		if(cow[i].d==-1)
		{
			ncow[i].t=cow[i].x;
			ncow[i].w=Q2.front();
			Q2.pop();
		}
	int T=0,W=0,now=0;
	sort(ncow+1,ncow+n+1,cmp1);//按照到达时间排序
	while(2*W<sum)W+=ncow[++now].w;//尽量把除法写成乘法形式，否则可能会有精度问题
	T=ncow[now].t;//计算T
```
#### 2 求碰撞次数
这一部分就比较简单了  
~~不过阅读这部分之前请自学初二物理：运动学之参照物~~

我们以速度为1的奶牛为参照物（其实以速度为-1的为参照物也可以）  
我们可以得到速度为-1的奶牛的速度现在变成了-2  
那么，我们就可以得到（在以原先速度为1的奶牛为参照物的情况下）这些奶牛可以到达的位置  
现在，我们只要知道在这些奶牛和他们最终到达的位置之间有多少头站着不动的奶牛（也就是原先速度为1的奶牛）就好了

于是我们又要维护一个**队列**  
这个队列维护的就是在速度为-2（原先速度为-1）的奶牛能到达的范围内的所有（站着不动的）奶牛的编号   
我们扫描每一头奶牛  
如果这是一头原先速度为1的奶牛，则直接将其加入队列  
如果这是一头原先速度为-1的奶牛，则要检查队列的前部  
若这头奶牛到不了队头的奶牛，则将队头的奶牛弹出队列，一直执行到这头奶牛可以到达队头的奶牛为止  
这时，队列的长度就是这头奶牛碰撞的次数

代码：
```cpp
	//这里我手写了一个队列，并用sz表示它的大小
	int ans=0;//存碰撞总数
	for(int i=1;i<=n;i++)
	{
		if(cow[i].d==1)Q[Tail++]=i,sz++;
		else
		{
			while(Head<Tail)
			{
				if(cow[i].x-cow[Q[Head]].x>T*2)Head++,sz--;
				//如果当前奶牛到达不了队头的奶牛，就出队
				else break;
			}
			ans+=sz;
		}
	}
```
#### 3 时间复杂度
排序$O(nlogn)$  
计算T $O(n)$  
计算碰撞次数 $O(n)$  
所以总复杂度 $O(nlogn)$  
~~这烦人的排序~~

#### 4 代码
放上我的（没有注释）的完整代码
```cpp
#include<bits/stdc++.h>
#define MAXN 50010
using namespace std;
int n,L;
int read()
{
	int num=0,fl=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')fl=-1;c=getchar();}
	while(isdigit(c)){num=num*10+c-48;c=getchar();}
	return num*fl;
}
struct Node
{
	int w,x,d;
}cow[MAXN];
struct Node1
{
	int w,t;
}ncow[MAXN];
bool cmp(Node x,Node y)
{
	return x.x<y.x;
}
bool cmp1(Node1 x,Node1 y)
{
	return x.t<y.t;
}
queue<int>Q1,Q2;
int sum;
int Q[MAXN],Head,Tail,sz;
int main()
{
	n=read();L=read();
	for(int i=1;i<=n;i++)cow[i].w=read(),cow[i].x=read(),cow[i].d=read(),sum+=cow[i].w;
	sort(cow+1,cow+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(Q1.empty()&&cow[i].d==-1)continue;
		if(cow[i].d==1)Q1.push(cow[i].w);
		else Q1.pop(),Q1.push(cow[i].w);
	}
	for(int i=n;i>=1;i--)
	{
		if(Q2.empty()&&cow[i].d==1)continue;
		if(cow[i].d==-1)Q2.push(cow[i].w);
		else Q2.pop(),Q2.push(cow[i].w);
	}
	for(int i=1;i<=n;i++)
		if(cow[i].d==1)
		{
			ncow[i].t=L-cow[i].x;
			ncow[i].w=Q1.front();
			Q1.pop();
		}
	for(int i=n;i>=1;i--)
		if(cow[i].d==-1)
		{
			ncow[i].t=cow[i].x;
			ncow[i].w=Q2.front();
			Q2.pop();
		}
	int T=0,W=0,now=0;
	sort(ncow+1,ncow+n+1,cmp1);
	while(2*W<sum)W+=ncow[++now].w;
	T=ncow[now].t;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(cow[i].d==1)Q[Tail++]=i,sz++;
		else
		{
			while(Head<Tail)
			{
				if(cow[i].x-cow[Q[Head]].x>T*2)Head++,sz--;
				else break;
			}
			ans+=sz;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
#### 5 提交结果
开O2 118ms rk1  
不开O2 234ms 在不开O2的提交中rk4

最后，希望各位AC此题qwq

---

## 作者：tiger2005 (赞：9)

### 做题全过程

做完Silver T3之后就来挑战这道可能是模拟的题了。

乍一看，怎么和某蚁和某桥差不多呢……

但是这个重量是什么啊……

此时我想到了一件事：我在读每一本书的时候都会仔细研读前文。

这时，蓝本的例题显现在我的脑海里。

啊！这不就是那道题吗？

回家吃完饭就跑来机房了，问了一个同样CSP崩盘的同学，ta说ta想到这道题了，打了一半。

不好！我跑回机房马上调整状态。20分钟后，我敲出了69行的代码，提交了上去。

回到主页面刷新一下，我开心到直接在机房鼓起了掌。

> Congratulations! You get 1000 points ...

P.S. : 这道启发我的题就是阅读说明的例题——[Piotr's Ants](https://www.luogu.com.cn/problem/UVA10881)，最后的那段话实际上我忘了……

---

### 题意简述

N个带有重量信息的牛在数轴上以1单位/秒的速度走着，两头牛相撞时同时掉头，求出当到达数轴最左端(0)和最右端(L)的牛重量和不小于总重量的一半前牛的总碰撞次数。

---

### 做法

首先我们可以确定的是：

- 性质1：两头牛相撞可以被认为是交换重量后穿过对方身体继续行走，方向不变。

- 性质2：因为一次相撞的时候两头牛的相对位置不会改变，那么多次碰撞后牛的相对位置仍然不变。

我们先来考虑性质1在告诉我们什么。

假如我们按照性质1的方法替换，我们可以发现：

性质3:假设一头牛在a处，方向向右，那么T秒之后一定有一头牛在T+a处且方向向右。

Prove:由性质1的替换可以知道，这头牛在行走的时候，尽管重量在不断变换，但是这头牛还是这么走。所有，在T秒后，不管这头牛身上带着什么信息，它一定是在T+a处的且向右。那么在真正的碰撞下，一定有一头牛在T+a处且方向向右。

所以，我们可以知道这N头牛在T秒之后每头牛可能出现的位置和方向。这实际上就是Piotr's Ants要求的东西了。

回到这一题，这样的话我们可以具体知道，每一头牛还对应着一种入仓时间和地点。方式如下：

在a点的牛，方向向右->在(L-a)时刻有一头牛到达最右端

在a点的牛，方向向左->在a时刻有一头牛到达最左端

这个时候我们就拿到了一张表，这记录的是这N头牛的到达时间和地点。但是对应关系还是没有找到，因此下一步是确定关系。

怎么做呢？

别忘了我们还有性质2。从这个性质我们知道，最右边的牛，在碰撞时之后还是在最右边。那么最先到达右端点的就只可能是这头牛了。左边同理。

因此，将上述表按照到达时间排序，依次扫描，如果是到右端点就将最右边的牛和它联系起来，反之亦然。然后，删除这头牛并继续操作。

那么，我们拿到了每一头牛的到达时间，计算 __到达数轴最左端(0)和最右端(L)的牛重量和不小于总重量的一半__ 的时间也就很简单了。假设这个时间是$T_0$。

知道了时间，我们又能怎么做呢？

再次使用性质1。我们发现，如果是互相穿过的话，两头距离$a$的牛将在$\dfrac{a}{2}$的时间相撞。而且，由于这两头牛的对应牛是确实存在的(性质3)，那么这次碰撞时真实存在的。

所以，我们只用找每头牛面前距离小于$2T_0$并可能相撞(就是异向)的牛，这时在$T_0$的时间内这头牛将会和这群符合条件的牛相撞，对答案的贡献也一目了然了。二分就是解决问题的方法。

复杂度：$O(NlogN)$。

Code:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
struct Cow{
	int w,l,v,t;
	bool operator < (const Cow & a)const{
		return l<a.l;
	}
}t[50010];
struct Time{
	int zt,tm;
	bool operator < (const Time & a)const{
		return tm<a.tm;
	}
}T[50010];
int N,L,W,LT;
long long ans;
int sml[50010],smr[50010];
int main(){
	freopen("meetings.in","r",stdin);
	freopen("meetings.out","w",stdout);
	scanf("%d%d",&N,&L);
	for(int i=1;i<=N;i++){
		scanf("%d%d%d",&t[i].w,&t[i].l,&t[i].v);
		W+=t[i].w;
	}
	W=(W+1)/2;
	sort(t+1,t+N+1);
	for(int i=1;i<=N;i++){
		if(t[i].v==1)	sml[i]=sml[i-1],smr[i]=smr[i-1]+1;
		else	sml[i]=sml[i-1]+1,smr[i]=smr[i-1];
	}
	for(int i=1;i<=N;i++){
		if(t[i].v==1){
			T[i].tm=L-t[i].l;
			T[i].zt=1;
		}
		else{
			T[i].tm=t[i].l;
			T[i].zt=-1;
		}
	}
	sort(T+1,T+N+1);
	int U = 0 , L = 1 , R = N;
	for(int i=1;i<=N;i++){
		if(T[i].zt==1){U+=t[R].w;R--;}
		else{U+=t[L].w;L++;}
		if(U>=W){LT=T[i].tm;break;}
	}
	L = 1 , R = N;
	for(int i=1;i<=N;i++){
		if(T[i].zt==1){U+=t[R].w;t[R].t=T[i].tm;R--;}
		else{U+=t[L].w;t[L].t=T[i].tm;L++;}
	}
	for(int i=1;i<=N;i++){
		if(t[i].v==1){
			int L = i , R = N + 1, M;
			while(L < R - 1){
				M = (L + R) >> 1;
				if(t[M].l-t[i].l>2*LT)	R=M;
				else	L=M;
			}
			ans += sml[L] - sml[i-1];
		}
		else{
			int L = 0 , R = i , M;
			while(L < R - 1){
				M = (L + R + 1) >> 1;
				if(t[i].l-t[M].l>2*LT)	L=M;
				else	R=M;
			}
			ans += smr[i] - smr[R-1];
		}
	}
	printf("%lld",ans/2);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：Brainless (赞：6)

# 其实这道题还蛮水的。。。
   一看到这道题我就想到了[蚂蚁](https://www.luogu.com.cn/problem/P1367)。至于这种问题的标准套路，大家可以去看一看蚂蚁的题解解析，我这里也大概讲一下。
   
   这种题目的重点在于碰撞之后反向。要求每头牛在碰撞之后反向，其实在牛碰撞的时候，可以看成每头牛**依旧按照原来的方向行进**，只不过碰撞之后两头牛的体重等要素交换。
   
####    然后就可以发现——

——在线段上运动的牛中，所有牛的顺序固定不变。

假设 4头牛的排列与方向如下

	A--B--C--D
   
    1 -1 -1  -1

按照每头牛不会在碰撞时反向，则假设在 t 秒后，位置变为

	B--C--A--D
    
则发生的相遇次数就是 **2**

发现了没有，其实就是统计**向右运动的牛 以右为正方向发生的位置的变化** （向左也一样，两种中选一种就行了）
如 A牛，向右发生了2个位置的变化，所以就可以

这个问题解决了，这样我们就只需要求出停止运动时间就行了。

和别的题解不一样我这里采用**二分**的办法求出停止时间。

我们来**二分停止时间**，直到求出可以满足要求的最小时间。

二分我认为还是相对好理解的一些。看代码就可以明白了。。。

```cpp
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>
#define MAX 50005
#define rep(i,a,b)  for(int i=a;i<=b;++i)
#define per(i,a,b)  for(int i=a;i>=b;--i)
#define ck(i) (f[i].pos>=0&&f[i].pos<=len)
using namespace std;  
double len, tot;
int n;
struct Cow  
{  
    double pos, d;
    int id;  
}a[MAX], f[MAX];
double wt[MAX];
int ord[MAX], rev[MAX];
int cmp(Cow a, Cow b)
{
    if(a.pos == b.pos)
        return a.d < b.d;
    return a.pos < b.pos;
}
int check(int k) //求在k秒后是否能够停止
{
    double sum = 0;
    rep(i, 1, n)
        f[i] = a[i];
    rep(i, 1, n)
    {
        rev[i] = f[i].id; //统计原排名所对应的牛编号
        f[i].pos += f[i].d * k;
    }
    sort(f + 1, f + 1 + n, cmp);
    rep(i, 1, n)
    {
        if(f[i].pos <= 0 || f[i].pos >= len)
            sum += wt[rev[i]];
    }
    if(sum * 2 >= tot) return 1; //能停止，则继续缩小时间
    return 0;
}
int main()
{
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
    cin >> n >> len;
    rep(i, 1, n)
    {
        cin >> wt[i] >> a[i].pos >> a[i].d;
        tot += wt[i];
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    int lf = 0, rt = 1e9, ans = 0;
    while(lf <= rt) //二分停止时间
    {
        int mid = (lf + rt) >> 1;
        if(check(mid))
            rt = mid - 1, ans = mid;
        else lf = mid + 1;
    }
    int cnt = 0;
    rep(i, 1, n)
        f[i] = a[i], ord[f[i].id] = i, f[i].pos += f[i].d * ans;//这里和二分check中相反，统计每头牛的原排名
    sort(f + 1, f + 1 + n, cmp); //按t秒后的位置排序
    rep(i, 1, n)
    {
        if(f[i].d == 1)
        {
            cnt += i - ord[f[i].id]; //统计每头向右走的牛发生的排名变化
        }
    }
    cout << cnt << endl;
}

```





---

## 作者：7KByte (赞：5)

第一篇题解已经被某神仙抢了（这篇就不抢了（毕竟不是最优解


首先对所有的牛按照位置排序

我们用两个双端队列$P,Q$分别记录朝右和朝左的牛的有序集合

每次将$P$队尾离$L$的距离和$Q$队头到$0$的距离对比，选择更近的那头牛（它会更早到牛棚

然后将它路径上相遇的牛的重量全部往后移一个位置

一直循环下去，每次搞定一头牛，直到到牛棚的牛的质量大于总质量的一半停止


这样我们就得到了整个过程的持续时间

还没完，我们利用这个持续时间，计算如果两头相对的牛相遇，他们的距离差必定$\le2*Time$

避免最后计算过程爆$N^2$，我们用一个单调队列模拟一下即可

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x=0,op=1;char ch=getchar();
    while(!isdigit(ch))op=(ch=='-'?-1:1),ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*op;
}
int n,L,tot=0,Time=0;
struct node{
	int pos,wei,op;
	bool operator<(const node o)const{return pos<o.pos;}
}a[50005];
deque<int>p,q;
void init(){
	sort(a+1,a+n+1);
	rep(i,1,n)if(a[i].op==1)p.push_back(i);
	else q.push_back(i);
}
int sta[50005],top;
int work(){
	//��Ҫע��һ������Ϊ�� 
	if(p.empty()){
		int val=q.front();
		q.pop_front();
		Time=max(Time,a[val].pos);
		return a[val].wei;
	}
	if(q.empty()){
		int val=p.back();
		p.pop_back();
		Time=max(Time,L-a[val].pos);
		return a[val].wei;
	}
	int x=p.back();
	int y=q.front();
	//cout<<x<<" "<<y<<" ";
	if(a[y].pos<(L-a[x].pos)){
		int u,ed=a[p.front()].wei;
		if(y<p.front()){
			q.pop_front();
			Time=a[y].pos;return a[y].wei;
		}
		while(!p.empty()&&(u=p.front())<y){
			sta[++top]=u;p.pop_front();
		}
		rep(i,1,top-1)a[sta[i]].wei=a[sta[i+1]].wei;
		a[sta[top]].wei=a[y].wei;
		while(top)p.push_front(sta[top]),top--;
		q.pop_front();
		Time=a[y].pos;
		//cout<<u<<endl;
		return ed;
	}
	else{
		int u,ed=a[q.back()].wei;
		if(x>q.back()){
			p.pop_back();
			Time=L-a[x].pos;return a[x].wei;
		}
		while(!q.empty()&&(u=q.back())>x){
			sta[++top]=u;q.pop_back();
		}
		rep(i,1,top-1)a[sta[i]].wei=a[sta[i+1]].wei;
		a[sta[top]].wei=a[x].wei;
		while(top)q.push_back(sta[top]),top--;
		p.pop_back();
		Time=L-a[x].pos;
		//cout<<u<<endl;
		return ed;
	}
}
queue<int>Q;
void out(){
	int len=2*Time,ans=0,cnt=0;
	rep(i,1,n){
		if(a[i].op==1)Q.push(i);
		else{
			//cout<<i<<" "<<cnt<<"  ss"<<endl;
			while(!Q.empty()&&a[Q.front()].pos+len<a[i].pos)
			  Q.pop();
			//cout<<i<<" "<<cnt<<"  tt"<<endl;
			ans+=Q.size();
		}
	}
	printf("%d\n",ans);
}
int main(){
	//freopen("meetings.in","r",stdin);
	//freopen("meetings.out","w",stdout);
	n=read();L=read();
	rep(i,1,n)a[i].wei=read(),a[i].pos=read(),a[i].op=read(),tot+=a[i].wei;
	init();
	//cout<<endl<<endl;
	//rep(i,1,n)printf("%d %d %d\n",a[i].op,a[i].pos,a[i].wei);
	//cout<<endl<<endl;
	register int sum=0;
	while(sum*2<tot){
		sum+=work();
		//cout<<sum<<" "<<" ss "<<endl;
	}
	//cout<<Time<<endl;
	out();
	return 0;
}
```

各位围观的神仙肯定发现了一个问题就是这份代码时间复杂度可能爆$N^2$，但显然（口胡）这份代码是跑不满$N^2$（即使是最坏情况）（这也是我选择用双端队列列的原因），所以我们可以放心地切题了

~~荣登最劣榜榜首~~


为啥我感觉这题是金银铜中最毒瘤的题啊（肯定是因为我太菜了

---

## 作者：chenningxuan (赞：3)

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int w,x,d;
}a[50001];
//分别代表输入中的wi,xi,di，用一个struct存排序时方便一点
node l[50001],r[50001];
pair<int,int>b[50001];//二元组存坐标点
queue<int> q;//队列存状态

bool cmp(node a,node b) {
	return a.x<b.x;
}//比较函数

int main()
{
	int n,L,sumw=0;
	cin>>n>>L;//如题意
	for(int i=1;i<=n;i++) {
		cin>>a[i].w>>a[i].x>>a[i].d;
		sumw+=a[i].w;
	} // 不解释
	sort(a+1,a+n+1,cmp);//排序
	int suml=0,sumr=0;
	for(int i=1;i<=n;i++) {//将a[i]存进左和右
		if(a[i].d==-1) {
			suml++;
			l[suml]=a[i];
		}
		else {
			sumr++;
			r[sumr]=a[i];
		}
	}
	for(int i=1;i<=suml;i++) {
		b[i]=make_pair(l[i].x,a[i].w);//将l[i].x和a[i].w组成一个pair
	}
	for(int i=1;i<=sumr;i++) {
		b[suml+i]=make_pair(L-r[i].x,a[suml+i].w);//将L-r[i].x和a[suml+i].w组成一个pair
	}
	sort(b,b+n+1);//对b[i]排序，按第一关键字优先
	int sum=0,t;
	for(int i=1;i<=n;i++) {//寻找t和sum
		sum+=b[i].second;
		if(sum*2>=sumw) {
			t=b[i].first;
			break;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++) {//单调队列模拟
		if(a[i].d==-1) {
			while(!q.empty()&&a[i].x-q.front()>2*t) q.pop();
			ans+=q.size();
		}
		else q.push(a[i].x);
	}
	cout<<ans<<endl;//输出
	return 0;
}


```


---

## 作者：chenningxuan (赞：3)

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int w,x,d;
}a[50001];
//分别代表输入中的wi,xi,di，用一个struct存排序时方便一点
node l[50001],r[50001];
pair<int,int>b[50001];//二元组存坐标点
queue<int> q;//队列存状态

bool cmp(node a,node b) {
	return a.x<b.x;
}//比较函数

int main()
{
	int n,L,sumw=0;
	cin>>n>>L;//如题意
	for(int i=1;i<=n;i++) {
		cin>>a[i].w>>a[i].x>>a[i].d;
		sumw+=a[i].w;
	} // 不解释
	sort(a+1,a+n+1,cmp);//排序
	int suml=0,sumr=0;
	for(int i=1;i<=n;i++) {//将a[i]存进左和右
		if(a[i].d==-1) {
			suml++;
			l[suml]=a[i];
		}
		else {
			sumr++;
			r[sumr]=a[i];
		}
	}
	for(int i=1;i<=suml;i++) {
		b[i]=make_pair(l[i].x,a[i].w);//将l[i].x和a[i].w组成一个pair
	}
	for(int i=1;i<=sumr;i++) {
		b[suml+i]=make_pair(L-r[i].x,a[suml+i].w);//将L-r[i].x和a[suml+i].w组成一个pair
	}
	sort(b,b+n+1);//对b[i]排序，按第一关键字优先
	int sum=0,t;
	for(int i=1;i<=n;i++) {//寻找t和sum
		sum+=b[i].second;
		if(sum*2>=sumw) {
			t=b[i].first;
			break;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++) {//单调队列模拟
		if(a[i].d==-1) {
			while(!q.empty()&&a[i].x-q.front()>2*t) q.pop();
			ans+=q.size();
		}
		else q.push(a[i].x);
	}
	cout<<ans<<endl;//输出
	return 0;
}
```


---

## 作者：cbyybccbyybc (赞：1)

## 题意
有$n$只奶牛（~~一看就是USACO的题~~，每头牛都向着自己的方向前进，直到达到$L$或$0$。如果两头奶牛相遇，则方向互换，其他不变。

## 思路
我们从题意中可以发现，如果两头奶牛相遇，则除了方向改变而其他不变，那我们可以让方向不变而交换两牛的质量。

这道题问的是最小时间，那么我们就可以采用**二分答案**的方式。

**二分所需要的时间**，再用$mid$去判断所有奶牛前进的路线，如果两牛相遇，那么他们的排名一定会发生改变，即一定有一头牛超过了另一头牛，从而引起排名改变。反推，如果他们的排名发生变化，则两牛一定相遇过。由于方向不变而质量交换，只需判断每头牛是否到达$L$或$0$，如果到了，则判断它和哪头牛最后相遇，最后$ans$加上相遇的那头牛。如果超过了一半，则时间可以更短，即$r=mid-1$。反之$l=mid+1$

最后我们二分出了最短时间，只要$solve(mid)$一下，判断在$mid$时间内，有多少次相遇，即排名发生变化。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50000;
struct node
{
	int w,x,d;
	int id;
}a[N],f[N];
int n,l,W[N],cnt=1,Half=0,ans=0,anss=0,ord[N],rev[N];
bool cmp(node aa,node bb)
{
	if(aa.x==bb.x)
	return aa.d<bb.d;
	else
	return aa.x<bb.x;
}
int check(int T)//二分check
{
    int sum=0;
    for(int i=1;i<=n;i++)
        f[i]=a[i];
    for(int i=1;i<=n;i++)
    {
        rev[i]=f[i].id;
        f[i].x+=f[i].d*T;
    }
    sort(f+1,f+1+n,cmp);//排序进行排名
    for(int i=1;i<=n;i++)
    {
        if(f[i].x<=0||f[i].x>=l)//如果到达
            sum+=W[rev[i]];//加上最后相遇质量
    }
    return sum*2>=Half;
}

int answering(int T)//即solve
{
    for(int i=1;i<=n;i++)
        f[i]=a[i],ord[f[i].id]=i,f[i].x+=f[i].d*T;
    sort(f+1,f+1+n,cmp); 
    for(int i=1;i<=n;i++)
    {
        if(f[i].d==1)
            ans+=i-ord[f[i].id]; 
    //    else ans+=ord[f[i].id]-i;
    }
}
signed main()
{
//	freopen("meeting.in","r",stdin);
//	freopen("meeting.out","w",stdout);
	cin>>n>>l;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].w>>a[i].x>>a[i].d;
		Half+=a[i].w;
		W[i]=a[i].w;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	int l=0,r=1e9;
	int midd;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,midd=mid;
		else l=mid+1;
	}
	answering(midd);
	cout<<ans;
	return 0;
}
```

---

## 作者：gznpp (赞：1)

出题神仙 Benq 已经说了，这题放在银组还是比较难的。

> (Analysis by Benjamin Qi)  
> Note: This problem is quite tricky for silver!

考场上懵了，去学校之后问了 EternalAlexander 神仙，他做的，代码是我的。

思路：（时间复杂度 $O(N \log^2 N)$）
有两个重要的结论：

1. 最后各头牛的坐标值，在不考虑顺序的情况下，等于没有对冲的坐标值。因为两头牛做的是对撞。

2. 最后各头牛的相对顺序不变。还是因为反弹。

开始先按初始坐标从小到大排个序。

显然这题分为两步：求 $T$；求相遇次数。

1. 求 $T$ 可以二分答案。  
check 函数中，根据结论 1 算出末坐标，然后记录原编号按末坐标排序，这时初坐标和末坐标就对应了。简单计算是否满足条件即可。

2. 记录原编号就是用来做第二步的。  
记录末坐标的数组按初坐标和末坐标大小两种方式排序，会得到两种相对顺序。这两种相对顺序应该是两个 $1 \dots N$ 的排列。树状数组求逆序对即可。

这算法很明显是对的，但我的代码通不过第二个点，比标答小 1。评论有无大佬告诉我为什么？

```cpp
#include <bits/stdc++.h>

#define ll long long
#define rgi register int

#define sp putchar(32)
#define el putchar(10)

#define pb push_back
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second

#define filein(x) freopen(x, "r", stdin)
#define fileout(x) freopen(x, "w", stdout)

using namespace std;

const int maxn = 5e4 + 5;
int n, L, ans, sum;
struct cow {
	int w, x, d;
}a[maxn];
struct tmp {
	int id, y;
}b[maxn];
int c[maxn];

inline bool cmp1(cow p, cow q) { return p.x < q.x; }
inline bool cmp2(tmp p, tmp q) {
	if (p.y != q.y) return p.y < q.y;
	else return p.id < q.id;
}

bool check(int tim) {
	for (rgi i = 1; i <= n; ++i) {
		b[i].id = i;
		b[i].y = a[i].x + a[i].d * tim;
	}
	sort(b + 1, b + n + 1, cmp2);
	int tans = 0;
	for (rgi i = 1; i <= n; ++i)
		if (b[i].y < 0 || b[i].y > L)
			tans += a[i].w;
	if ((tans << 1) >= sum) return 1;
	else return 0;
}

inline int lowbit(int x) { return x & (-x); }
inline void add(int i, int x) {
	for (; i <= n; i += lowbit(i)) c[i] += x;
}
inline int query(int i) {
	int ret = 0;
	for (; i; i -= lowbit(i)) ret += c[i];
	return ret;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	filein("meetings.in"), fileout("meetings.out");
	cin >> n >> L;
	for (rgi i = 1; i <= n; ++i) {
		b[i].id = i;
		cin >> a[i].w >> a[i].x >> a[i].d;
		sum += a[i].w;
	}
	sort(a + 1, a + n + 1, cmp1);
	
	int l = 0, r = L;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	for (rgi i = 1; i <= n; ++i) {
		add(b[i].id, 1);
		ans += i - query(b[i].id);
	}
	cout << ans << endl;
	return 0;
}
```

---

