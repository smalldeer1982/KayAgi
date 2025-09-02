# [BalkanOI 2007] Mokia 摩基亚

## 题目描述

摩尔瓦多的移动电话公司摩基亚（Mokia）设计出了一种新的用户定位系统。和其他的定位系统一样，它能够迅速回答任何形如 “用户 C 的位置在哪？” 的问题，精确到毫米。但其真正高科技之处在于，它能够回答形如 “给定区域内有多少名用户？” 的问题。

在定位系统中，世界被认为是一个 $w\times w$ 的正方形区域，由 $1\times 1$ 的方格组成。每个方格都有一个坐标 $(x, y)$，$1\leq x,y\leq w$。坐标的编号从 $1$ 开始。对于一个 $4\times 4$ 的正方形，就有 $1\leq x\leq 4$，$1\leq y\leq 4$（如图）：

![](https://cdn.luogu.com.cn/upload/pic/17271.png)

请帮助 Mokia 公司编写一个程序来计算在某个矩形区域内有多少名用户。

## 说明/提示

#### 数据规模与约定


对于 $100\%$ 的数据，保证：
- $1\leq w\leq 2\times 10 ^ 6$。
- $1\leq x_1\leq x_2\leq w$，$1\leq y_1\leq y_2\leq w$，$1\leq x,y\leq w$，$0<a\leq 10000$。
- 命令 $1$ 不超过 $160000$ 个。
- 命令 $2$ 不超过 $10000$ 个。

## 样例 #1

### 输入

```
0 4
1 2 3 3
2 1 1 3 3
1 2 2 2
2 2 2 3 4
3```

### 输出

```
3
5
```

# 题解

## 作者：潜翎 (赞：57)

[P4390 Mokia 摩基亚](https://www.luogu.org/problemnew/show/P4390)

主体思路：cdq分治

前置芝士：[三维偏序](https://www.luogu.org/problemnew/show/P3810)，以及大家都会的[一点点容斥技巧](https://www.luogu.org/problemnew/show/P2280)

代码效率：[1527ms](https://www.luogu.org/recordnew/show/20396227)
个人认为是还不错的效率，毕竟没有刻意去卡常数qwq


------------
因为并不是强制在线，所以不考虑常数较大的树套树和~~我并不会的K-D Tree~~做法。

对于每一个询问的矩阵**（x1,y1）（x2,y2）**，考虑利用容斥小技巧把它拆成四个询问**（0,0）（x2,y2）、（0,0）（x1-1,y1-1）**以及**（0,0）（x1-1,y2）、（0,0）（x2,y1-1）**，前者对答案做出**正贡献**而后者做出**负贡献**。

然后我们发现：诶，只有**横坐标**，**纵坐标**，以及**出现时间**三者都小于当前询问的才能对当前询问做出贡献！

这是……三维偏序的味道！

接下来，除了套模板，还有一点点需要注意的地方：

- x1-1和y1-1可能为零，这会导致树状数组死循环。

我们可以把这种情况特判掉，但特判好麻烦啊qwq

所以我们需要把所有坐标都+1，**还有w也别忘了+1哦qwq**，这样我们就完美避免了0的出现。

- 要不要去重？

三维偏序的板子不去重应该会WA的很惨，但我们这里**不用去重**。

考虑我们的元素特点。对于修改操作，我们不需要记录答案，对于询问操作，它没有做出贡献。所以我们只需**在第一次排序时保证所有询问操作在三维都相等的修改操作之后**就可以保证所有**修改的**贡献都被统计。这可以通过修改cmp函数实现。

如果执意要去重，你会无从下手的qwq

更多的小细节，请看代码实现。

如果有帮助到你，记得点赞哦qwq
```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
const int N=200010;
int w,cnt,qcnt,fcnt,ans[N],c[N];
struct Node{
	int x,y,ti,pos,opt,val; 
}node[N],temp[N];
/*
 pos是询问的位置
 opt是操作种类，等于0是修改，1和-1分别代表询问应该统计正贡献或负贡献。
 val是贡献 
*/ 
int read(){
    int x=0,w=1;char ch;ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*w;
}
bool cmp(const Node &a,const Node &b){
	if(a.x!=b.x) return a.x<b.x;
	if(a.y!=b.y) return a.y<b.y;
	if(a.ti!=b.ti) return a.ti<b.ti;//
	return a.val>b.val;//请注意这两行与三维偏序模板的不同之处qwq 
}
int lowbit(int x){
	return x&(-x);
}
void add(int x,int v){
	for(;x<=cnt;x+=lowbit(x))
	 c[x]+=v;
}
int query(int x){
	int v=0;
	for(;x;x-=lowbit(x))//如果不+1这里就死了哦qwq 
	 v+=c[x];
	return v;
}
void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(node[i].y<=node[j].y){
			if(!node[i].opt)
			 add(node[i].ti,node[i].val);
			temp[k++]=node[i++];
		}
		else{
			if(node[j].opt){
				int s=query(node[j].ti);
				ans[node[j].pos]+=s*node[j].opt;
			}
			temp[k++]=node[j++];
		}
	}
	while(j<=r){
		if(node[j].opt){
			int s=query(node[j].ti);
			ans[node[j].pos]+=s*node[j].opt;
		}
		temp[k++]=node[j++];
	}
	for(int o=l;o<i;o++)
	 if(!node[o].opt)
	  add(node[o].ti,-node[o].val);
	while(i<=mid)
	 temp[k++]=node[i++];
	for(int i=l;i<=r;i++)
	 node[i]=temp[i];
}
int main()
{
	int opt,x,y,xx,yy,num,t=0;
	read();w=read()+1;
	while(1){
		opt=read();
		if(opt==1){
			x=read()+1;y=read()+1;num=read();t++;
			node[++cnt]=Node{x,y,t,0,0,num};
		}
		else if(opt==2){
			x=read(),y=read();xx=read()+1,yy=read()+1;
			node[++cnt]=Node{xx,yy,t,++qcnt,1,0};
			node[++cnt]=Node{x,yy,t,qcnt,-1,0};
			node[++cnt]=Node{xx,y,t,qcnt,-1,0};
			node[++cnt]=Node{x,y,t,qcnt,1,0};
		}
		else break;
	}
	sort(node+1,node+cnt+1,cmp);
	cdq(1,cnt);
	for(int i=1;i<=qcnt;i++)
	 printf("%d\n",ans[i]);
	return 0;
}
```


------------
后记：我是时候该去认真学Markdown了QAQ

---

## 作者：Nemlit (赞：31)

upd：$(x1,y1)(x2,y2)$表示以$(x1,y1)$为左上端点 $(x2,y2)$为右下端点的矩形

本来以为是一道二位树状数组的模板，但是看数据范围之后就放弃了，边界既然到了2000000，那么我们只能使用其他办法来代替树状数组

~~于是，CDQ分治就诞生了！~~

此题我们可以把问题转化成[cdq分治模板](https://www.luogu.org/problemnew/show/P3810)

回忆一下二位树状数组是怎么求二维区间查询的：对于区间[x1,y1][x2,y2]，我们把它转化成$ (1,1)(x1-1,y1-1)+(1,1)(x2,y2)-(1,1)(x1-1,y2)-(1,1)(x2,y1-1) $求即可，所以对于每一个询问操作，把他看成四个坐标，求出前缀和就能找到答案

把操作的时间看作一维（时间在前的才可能对后面的操作有影响），把x，y看作后两维，对于$(1,1)(x,y)$，那么问题就转化成了$timea<timeb xa<xb ya<yb$的数量，也就是三位偏序模板了

注意几点：

1、树状数组的下标不能为0（0的lowbit的值也是0），所以我们需要把每一个点横纵坐标加一，最后w也要记得+1

2、注意区分询问和加法，在操作树状数组时要区分

给出代码：
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define debug printf("Now is Line : %d\n",__LINE__)
il int read()
{
    re int x=0,f=1;re char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return x*f;
}
#define lb(x) (x)&-(x)
#define maxn 200005
#define maxm 2000005
struct node
{
	int tim,x,y,val,id;
}e[maxn];
int cnt,a[maxm],w;
il void add(int x,int v)
{
	while(x<=w)
	{
		a[x]+=v;
		x+=lb(x);
	}
}
il int query(int x)
{
	int ans=0;
	while(x)
	{
		ans+=a[x];
		x-=lb(x);
	}
	return ans;
}
il bool cmp1(node a,node b)
{
	return (a.x==b.x)?(a.y<b.y):(a.x<b.x);
}
il bool cmp(node a,node b)
{
	return a.tim<b.tim;
}
il void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(e+l,e+mid+1,cmp1);
	sort(e+mid+1,e+r+1,cmp1);
	re int i=l,j=mid+1;
	for(;j<=r;++j)
	{
		while(e[i].x<=e[j].x&&i<=mid)
		{
			if(e[i].id==0) add(e[i].y,e[i].val);
			++i;
		}
		if(e[j].id==1) e[j].val+=query(e[j].y);
	}
	for(j=l;j<i;++j) if(e[j].id==0) add(e[j].y,-e[j].val);
}
int main()
{
	read(),w=read()+1;
	int opt=read();
	while(opt!=3)
	{
		if(opt==1)
		{
			int x=read()+1,y=read()+1,val=read();
			e[++cnt]=(node){cnt,x,y,val,0};
		}
		else
		{
			int x1=read(),y1=read(),x2=read()+1,y2=read()+1;
			e[++cnt]=(node){cnt,x1,y1,0,1};
			e[++cnt]=(node){cnt,x2,y2,0,1};
			e[++cnt]=(node){cnt,x2,y1,0,1};
			e[++cnt]=(node){cnt,x1,y2,0,1};
		}
		opt=read();
	}
	CDQ(1,cnt);
	sort(e+1,e+cnt+1,cmp);
	for(re int i=1;i<=cnt;++i)
	{
		if(e[i].id==1)
		{
			printf("%d\n",e[i].val+e[i+1].val-e[i+2].val-e[i+3].val);
			i+=3;
		}
	}
	return 0;
}
```

---

## 作者：arfa (赞：16)

### $CDQ$ 分治再续

这一次是给出两个常见的问题,由于某种原因,我们可以使用 $CDQ$ 有效的解决这一系列的问题。

### $I.$ 一维 \ 树状数组 $1$ 问题

题目大意 : 给出一个序列 ($N$个数字) ,操作包括单点修改,区间查询。

再次提一下 $CDQ$ 分治的主要思想:

- 求左边区间的贡献
- 求右边区间的贡献
- 求左半边对右半边的贡献

在求偏序的时候,以上三点的顺序是可以打乱的。不过在这道题目中,必须遵循一定的顺序,需要注意。

在我们使用树状数组或者线段树解决这道问题的时候,基于的是前缀和和分治的思想,这里稍微有点不同。我们想,**一个修改必定会影响它后面的查询**,当我们把原数组也视作修改的时候,
整个就变成了**哪个修改会影响哪个查询**的问题。

再想一下 $CDQ$ 分治的思想,我们可不可以求左半边对右半边的贡献呢? 先假设一个区间 $l,r$,假如 $l$ 到 $mid$ 的操作都是在 $mid+1$ 到 $r$ 前面做的(也就是左半边所有的时间都小于右半边的时间),那么 $l$ 到 $mid$ 的修改必定会影响到 $mid+1$ 到 $r$ 的查询。

![](https://s1.ax1x.com/2018/09/08/iPaVAI.png)

而我们把所有的查询 $L,R$ 的值变为 $1,R$ 的值减去 $1,L-1$ 的值,那么所有的查询的起点都是 $1$。这个时候我们判断是否有贡献的时候,我们就拿右端点 (修改的只有一个点,也视其为右端点) 来判断,修改的右端点小于查询的右端点,那么肯定是对查询有贡献的。(黑色的是加的,红色的是减去的,剩下的黄色就是目标区间)

![](https://i.loli.net/2018/09/15/5b9c82c0adb8d.png)

那是左半边所有的修改都会影响到右半边所有的贡献吗? 并不是。

![](https://s1.ax1x.com/2018/09/08/iPaGEn.png)

(注意,$time$ 为操作的时间,$point$ 为右端点的位置,$mode$ 为查询 ($Q$) 或者修改 ($C$)。以下的 $n$ 为操作的总数,包括把查询拆分和原序列)

我们对左半边和右半边的区间的右端点进行排序以后,左半边的时间还是要小于右半边最低的时间。我们可以很容易想到, $1$ 号 的 右端点是 $1$,它对右半边的所有查询都会产生贡献。而 $2$ 号的右端点是 $3$右半边,它只能对
右半边的 $2,3,4$ 号有贡献。也就是说,我们只需要每一次比较 $left$ 是否小于 $right$ (其中 $left$ 为 $1$ 到 $mid$,$right$ 为 $mid+1$ 到 $r$),如果小于,那么当前的 $left$ 号会对 $right$ 到 $r$ 都有贡献,
所以 $inc(sum,val[left])$。如果不是,我们就直接计算 $1$ 到 $left-1$ 对 $right$ 的贡献,就是 $inc(ans[id[right]],sum)$。

上述的方法是要求左半边和右半边的右端点有序,且左半边的最大时间小于等于右半边的最小时间的。我们可以采用先 $CDQ(l,mid)\ CDQ(mid+1,right)$ 的方法,**每一次算完当前的贡献,就排好序**,这样子就可以保证啦。既然是 $CDQ$,那么可以直接归并排序,常数小。

然后解释一下为什么 $CDQ$ 要分治。对于一个点 $i$,它经过 $\log\ n$ 层的分治以后,必然会与每一个右区间算贡献。一开始右区间有 $\frac{n}{2}$ 个数字,然后变为 $\frac{n}{4}\ \frac{n}{8}.etc$。时间复杂度涉及到递归,这里作出大致的推测 : $\log\ n$ 层,每一层的总和是 $n$,那就是 $n \log\ n$。实际上应该是 $O(f(n) \log\ n)$,我表示并不会主定理。

最后注意一下时间相同,先修改,再查询(虽然不知道为什么时间会相同)。

```pascal
function judge(i,j:longint):boolean;
begin
	if place[i]<>place[j] then // place 是右端点
	begin
		if place[i]<place[j] then exit(True);
		exit(False);
	end;
	if mode[i]<mode[j] then exit(True); // 查询的 mode 是 2,修改的 mode 是 1
	exit(False);
end;

procedure CDQ(l,r:longint);
var
	left,right,i,mid:longint; // left 是左半边开始第一个节点,right 是右半边第一个节点,两者都用于归并排序
	sum:int64; // '现在'左半边的贡献
begin
	if l=r then exit;
	mid:=(l+r) >> 1;
	CDQ(l,mid); // 先往下
	CDQ(mid+1,r);
	sum:=0; left:=l; right:=mid+1;
	for i:=l to r do
		if (left<right)and(judge(left,right)) or (right>r) then // 在左边
		begin
			if mode[left]=1 then inc(sum[id[left]]); // 修改的 id 是修改的值,而查询的 id 是此查询是第几个查询
			copy[1,i]:=mode[left]; copy[2,i]:=place[left]; copy[3,i]:=id[left]; inc(left); // 归并排序
		end
		else
		begin
			if mode[right]=2 then dec(ans[id[right]],sum);
			if mode[right]=3 then inc(ans[id[right]],sum);
			copy[1,i]:=mode[right]; copy[2,i]:=place[right]; copy[3,i]:=id[right]; inc(right);
		end;
	for i:=l to r do
	begin mode[i]:=copy[1,i]; place[i]:=copy[2,i]; id[i]:=copy[3,i]; end;
end;
```

### $II.$ 二维 \ $Mokia$

题目大意 : 给出一个空的二维矩阵 ($N$ 行 $N$ 列),操作包括单点修改,矩阵查询。

这是一个比较简单的二维树状数组的题目,至少在看到 $N$ 的数据范围之前是怎么认为的。

数据范围 : $N \leq 2 \times 10^6$。而树套树 (我指的是树状数组或者线段树) 怎么也只能 $N \leq 10^4$。

这就展现了 $CDQ$ 比较好的以一面 **哪个修改会影响哪个查询**,就不用考虑 $N$ 的大小,不用考虑模拟矩阵。

第一步,我们把查询看做是一个二维前缀和的查询。也就是说,我们对于 $x,y,x1,y1$ 的查询,看做全部以 $1$ 开始的矩阵,如下图 : (黑色的是加的,红色的是减去的,剩下的黄色就是目标矩阵)

![](https://i.loli.net/2018/09/15/5b9c83b75cb73.png)

现在问题从原来的一个右端点变成了两个右端点,但是贡献还是相同的,且有一个。假如两个点 $x_i,y_i$,$x_i$ 已经满足 $\leq x_j$,那么我们就只需要看 $y_i$ 对 $y_j$ 怎么样。这时候我们用一个树状数组(权域)来维护一下,
每一次左半边有修改的时候更新一下树状数组,每当右半边有点可以满足当前的左半边的点的时候 ($left,right$),就统计右边的点的第二个右端点 ($right_y$) 的前面有多少个左半边的点 ($1_y~left_y$) 的第二个右端点。

我们可以思考一下,如果我们先对所有的第一个右端点 ($x$) 进行了排序,那么每一次**往下**,我们只需要对时间进行归并排序即可,这样子跟上文的 **从下往上,对右端点进行排序** 是一样的。

```pascal
procedure CDQ(l,r:longint);
var
	left,right,i,mid:longint; // left 是左半边开始第一个节点,right 是右半边第一个节点,两者都用于归并排序
begin
	if l=r then exit;
	mid:=(l+r) >> 1;
	left:=l; right:=mid+1;
	for i:=l to r do 
	begin
		if (time[i]<=mid)and(mode[i]=1) then // 计算左半边的产生的贡献
			Insert(point[2,i],value[i]);  // value[i] 是修改的值,Insert 是树状数组的 Add
		if (time[i]>mid)and(mode[i]=2) then // 计算右半边拥有的贡献
			inc(ans[id[i]],Query(point[2,i])*value[i]); // 查询的 value[i] 只有 1 和 -1,用来表示加还是减
		if (time[i]<=mid) then // 以下都是归并排序
		begin
			copy[1,left]:=time[i]; copy[2,left]:=point[1,i]; copy[3,left]:=point[2,i]; 
			copy[4,left]:=value[i]; copy[5,left]:=id[i]; copy[6,left]:=mode[i]; inc(left);
		end
		else
		begin
			copy[1,right]:=time[i]; copy[2,right]:=point[1,i]; copy[3,right]:=point[2,i]; 
			copy[4,right]:=value[i]; copy[5,right]:=id[i]; copy[6,right]:=mode[i]; inc(right);
		end;
	end;
	for i:=l to r do // 算完贡献以后按照 time 排序
	begin
		time[i]:=copy[1,i]; point[1,i]:=copy[2,i]; point[2,i]:=copy[3,i];
		value[i]:=copy[4,i]; id[i]:=copy[5,i]; mode[i]:=copy[6,i]; 
	end;
	CDQ(l,mid);
	CDQ(mid+1,r);
end;
```

最后总结 $CDQ$ 分治需要注意的地方:

$I.\ CDQ$分治会按照各个参数的顺序而改变递归的顺序。

$II.\ CDQ$分治的时间复杂度并不是非常的好,常数巨大,但是可以做那些二维以上的题目,不用考虑 $N$ 的大小。 (但是询问太多还是会炸)

$III.\ $有些人是直接 $Sort$ 的,而不是归并排序,所以 $CDQ$ 分治的三个步骤可以打乱。








---

## 作者：Reanap (赞：10)

要求查询矩阵(x1 , y1 , x2 , y2)内的用户个数，为了使问题更加具有一般性，我们考虑将问题简化，记$f(x,y)$为矩阵(1 , 1 , x , y)的用户个数，则答案显然为
$$f(x2,y2)+f(x1-1,y1-1)-f(x1-1,y2)-f(x2,y1 -1)$$

因此，问题转化为了如何求解$f(x,y)$

我们考虑使用cdq分治离线解决，我们的目标即求解时间戳在当前询问之前，同时横纵坐标均小于等于当前横纵坐标的加入操作的加入用户和。

我们尝试使用时间作为第一维，x作为第二维归并排序。

当$q_i.x > q_j.x$时，如果$q_j$是查询操作，由于$q_j$的结果一定会被左区间的插入操作所影响，由于已加入的$i$的$x$一定小于等于$q_j$的$x$，所以我们希望能够在已加入的$i$中找到$y$值比当前小的，所以我们可以用树状数组维护左区间已插入$i$的$y$值，之后就可以快速统计答案。

则当$q_i.x <= q_j.x$时，如果$q_i$是查询操作，则我们在正在合并的数据中已经在左端查询过结果了忽略掉，否则我们把$y$值插入树状数组中（理由见上）。

完成后直接输出答案就好了~

~~不知道为什么那么题解都要用$x$排序作为第一维~~

不懂的可以看一下代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
void read(int &x){ 
	int f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=f;
}
const int MAXQ = 2e5 + 5;
const int MAXN = 2e6 + 5;
struct node {
	int x , y , ty , t , val;
	node () {}
	node (int X , int Y , int T , int Ti , int V) {
		x = X;y = Y;ty = T;t = Ti;val = V;
	}
}q[MAXQ] , b[MAXQ];
LL tr[MAXN] , ans[MAXN];
int n , cnt , T;
void update(int x , int y) {
	for (; x <= n; x += (x & (-x))) tr[x] += y;
}
LL find(int x) {
	LL res = 0;
	for (; x; x -= (x & (-x))) res += tr[x];
	return res;
}
void cdq(int l , int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l , mid);cdq(mid + 1 , r);
	int x = l , y = mid + 1 , t = 0;
	while(x <= mid && y <= r) {
		if(q[x].x <= q[y].x) {
			b[++t] = q[x];
			if(!q[x].ty) update(q[x].y , q[x].val);
			x ++;
		}
		else {
			b[++t] = q[y];
			if(q[y].ty) ans[q[y].t] += find(q[y].y) * q[y].ty;
			y ++;
		}
	}
	for (int i = x; i <= mid; ++i) {
		b[++t] = q[i];
		if(!q[i].ty) update(q[i].y , q[i].val);
	}
	for (int i = y; i <= r; ++i) {
		b[++t] = q[i];
		if(q[i].ty) ans[q[i].t] += find(q[i].y) * q[i].ty;
	}
	for (int i = l; i <= mid; ++i) if(!q[i].ty) update(q[i].y , -q[i].val);
	for (int i = 1; i <= t; ++i) q[i + l - 1] = b[i];
}
int main() {
	int ty;
	read(ty);read(n);
	while(1) {
		read(ty);
		if(ty == 3) break;
		else if(ty == 1) {
			int x , y , a;
			read(x);read(y);read(a);
			q[++cnt] = node(x , y , 0 , 0 , a);
		}
		else {
			int x1 , y1 , x2 , y2;
			read(x1);read(y1);read(x2);read(y2);
			T ++;
			q[++cnt] = node(x1 - 1 , y1 - 1 , 1 , T , 0);q[++cnt] = node(x2 , y2 , 1 , T , 0);
			q[++cnt] = node(x1 - 1 , y2 , -1 , T , 0);q[++cnt] = node(x2 , y1 - 1 , -1 , T , 0);
		}
	}
	cdq(1 , cnt);
	for (int i = 1; i <= T; ++i) printf("%lld\n" , ans[i]);
	return 0;
}
```

---

## 作者：Froggy (赞：7)

算法书的网站可同步提交:[Contest-Hunter](http://noi-test.zzstep.com/contest/0x49%E3%80%8C%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E8%BF%9B%E9%98%B6%E3%80%8D%E7%BB%83%E4%B9%A0/4911%20Mokia)

---

看一眼题,二维树状数组裸题??

再看一眼数据范围,woc,这不是$ K- D\ \ Tree \ $么,不会写啊QAQ

翻一翻算法书,提示写着:基于时间的分治算法(不就是$CDQ$分治么)

来之前先把[陌上花开](https://www.luogu.org/problem/P3810)做了

考虑把横坐标$CDQ$分治,把纵坐标用树状数组存

询问不太好,可以用**差分的思想**把矩形$S_{(X1,Y1,X2,Y2)}$拆成$S_{(1,1,X2,Y2)}-S_{(1,1,X1-1,Y2)}-S_{(1,1,X2,Y1-1)}+S_{(1,1,X1-1,Y1-1)}$,分成4个询问即可,然后就可以套$CDQ$的板子了 ^v^

~~有篇题解说时间是$O(nlogn)$,我觉得那位大爷需要回去重新学$CDQ$分治了~~

分治+树状数组,显然是$O(nlog^2n)$(准确地说应该是$O(nlognlogw)$

如果你做过[天使玩偶](https://www.luogu.org/problem/P4169)这道毒瘤卡常的话你就知道分治过程中的快排可以用归并排序写,这样能将常数优化到原来的$\frac{1}{2}$,不过这道题时间很松,不需要,最慢点也不超过$1s$

**细节:** long long,回溯 都不要忘了

下面看代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define N 2000100
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int s,w,n,opt,id,bit[N],mx;
ll ans[N];
struct Query{//id表示是第几个询问,type指操作类型
	int x,y,type,val,id;//val在修改中表示加上的权值,在询问中表示加上还是减去(1/-1)
}q[N],a[N];
struct Note{//ans还要加上矩形大小*s,所以要记录矩形坐标
	int X1,Y1,X2,Y2;
}qwq[N];
bool cmp2(Query a,Query b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}
//下面是树状数组基本操作,不说了
inline int lowbit(int x){
	return x&(-x);
}
inline void Add(int x,int d){
	while(x<=mx){
		bit[x]+=d;
		x+=lowbit(x);
	}
} 
inline int Ask(int x){
	int ans=0;
	while(x){
		ans+=bit[x];
		x-=lowbit(x);
	}
	return ans;
}
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(a+l,a+mid+1,cmp2);
	sort(a+mid+1,a+r+1,cmp2);//sort即可,还可以用归排
	int i=mid+1,j=l;
	while(i<=r){
		while(j<=mid&&a[j].x<=a[i].x){//扫描l-mid的修改对mid+1-r的询问的影响
			if(a[j].type==1){
				Add(a[j].y,a[j].val);
			}
			++j;
		}
		if(a[i].type==2){
			ans[a[i].id]+=1LL*a[i].val*Ask(a[i].y);
		}
		++i;
	} 
	for(int i=l;i<j;i++){
		if(a[i].type==1)Add(a[i].y,-a[i].val);//别忘了回溯
	}
}
int main(){
	s=read(),w=read();mx=2000000;
	while(opt=read(),opt^3){
		++n;
		if(opt==1){
			q[n].x=read(),q[n].y=read(),q[n].val=read();
			q[n].type=opt;
		}
		else{
			int X1=read(),Y1=read(),X2=read(),Y2=read();
			++id;
            //拆成四个询问
			q[n].x=X2,q[n].y=Y2;
			q[n].val=1,q[n].id=id,q[n].type=opt;
			++n;
			q[n].x=X1-1,q[n].y=Y2;
			q[n].val=-1,q[n].id=id,q[n].type=opt;
			++n;
			q[n].x=X2,q[n].y=Y1-1;
			q[n].val=-1,q[n].id=id,q[n].type=opt;
			++n;
			q[n].x=X1-1,q[n].y=Y1-1;
			q[n].val=1,q[n].id=id,q[n].type=opt;
			qwq[id].X1=X1,qwq[id].X2=X2,qwq[id].Y1=Y1,qwq[id].Y2=Y2;
		}
	}
	for(int i=1;i<=n;i++){
		a[i]=q[i];//闲的复制一下
	}
	CDQ(1,n);
	for(int i=1;i<=id;i++){
		printf("%lld\n",ans[i]+1LL*(qwq[i].X2-qwq[i].X1+1)*(qwq[i].Y2-qwq[i].Y1+1)*s);
	}
	return 0;//bye bye
}

```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!



---

## 作者：GNAQ (赞：7)

这种题当然要大力 `K-D Tree` 啦！

首先是对矩阵建 2-D Tree ，然后维护加入的点和管辖范围的权值和就行了。

查询的时候直接判断管辖范围和查询范围的关机即可。

加一个替罪羊式重构，因子是 $0.65$ 就挺好的

(当然好像深度为 $25$ 的朝鲜树效果也挺好……?)

这种大数据结构没啥可讲的，直接看代码吧

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<stack>
#define ll long long
using namespace std;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

namespace KDT
{
    #define LCH tree[inx].ch[0]
    #define RCH tree[inx].ch[1]
    
    int tsiz,troo,cstD,plen;
    struct __Point
    {
        int x,y,v;
        bool operator < (const __Point& b) const
        {
            if (!cstD) return ( (x<b.x) || (x==b.x && y<b.y) );
            else return ( (y<b.y) || (y==b.y && x<b.x) );
        }
    }tmp[200010],tmp_point;
    struct KDT_Node
    {
        int ch[2],Lx,Ly,Rx,Ry,siz,sum;
        __Point p;
    }tree[200010];
    stack<int> memalc;
    
    void MemInit(const int& rg)
    {
        for (int i=rg;i;i--) memalc.push(i);
        memset(tmp,0,sizeof tmp); tmp_point.x=tmp_point.y=tmp_point.v=0;
    }
    
    void NewNode(int& inx)
    {
        inx=memalc.top(); memalc.pop();
        tree[inx].Lx=tree[inx].Ly=tree[inx].Rx=tree[inx].Ry;
        tree[inx].siz=tree[inx].sum=0; tree[inx].p=tmp_point;
        LCH=RCH=0;
    }
    
    void Update(const int& inx)
    {
        tree[inx].siz=tree[LCH].siz+tree[RCH].siz+1;
        tree[inx].sum=tree[LCH].sum+tree[RCH].sum+tree[inx].p.v;
        tree[inx].Lx=tree[inx].Rx=tree[inx].p.x;
        tree[inx].Ly=tree[inx].Ry=tree[inx].p.y;
        
        if (LCH)
        {
            tree[inx].Lx=min(tree[inx].Lx,tree[LCH].Lx);
            tree[inx].Rx=max(tree[inx].Rx,tree[LCH].Rx);
            tree[inx].Ly=min(tree[inx].Ly,tree[LCH].Ly);
            tree[inx].Ry=max(tree[inx].Ry,tree[LCH].Ry);
        }
        if (RCH)
        {
            tree[inx].Lx=min(tree[inx].Lx,tree[RCH].Lx);
            tree[inx].Rx=max(tree[inx].Rx,tree[RCH].Rx);
            tree[inx].Ly=min(tree[inx].Ly,tree[RCH].Ly);
            tree[inx].Ry=max(tree[inx].Ry,tree[RCH].Ry);
        }
    }
    
    int BuildTree(int lxx,int rxx,int dd)
    {
        cstD=dd; int mid=(lxx+rxx)>>1,inx=0;
        nth_element(tmp+lxx,tmp+mid,tmp+rxx+1);
        
        NewNode(inx); tree[inx].p=tmp[mid];
        if (mid>lxx) LCH=BuildTree(lxx,mid-1,!dd);
        if (mid<rxx) RCH=BuildTree(mid+1,rxx,!dd);
        Update(inx); return inx;
    }
    
    void Pia(int inx)
    {
        if (LCH) Pia(LCH);
        tmp[++plen]=tree[inx].p;
        memalc.push(inx);
        if (RCH) Pia(RCH);
    }
    
    void RebuildCheck(int& inx,int dd)
    {
        if (tree[inx].siz*0.65+1<max(tree[LCH].siz,tree[RCH].siz))
        {
            plen=0; Pia(inx);
            inx=BuildTree(1,plen,dd);
        }
    }
    
    void Ins(int& inx,__Point pn,int dd)
    {
        cstD=dd;
        if (!inx)
        {
            NewNode(inx);
            tree[inx].p=pn; Update(inx);
            return;
        }
        if (tree[inx].p.x==pn.x && tree[inx].p.y==pn.y)
        {
            tree[inx].p.v+=pn.v;
            tree[inx].sum+=pn.v;
            Update(inx);
            return;
        }
        if (pn<tree[inx].p) Ins(LCH,pn,!dd);
        else Ins(RCH,pn,!dd);
        Update(inx); 
        if (inx!=troo) RebuildCheck(inx,dd);
    }
    
    bool InSqu(const int& _x1,const int& _y1,const int& _x2,const int& _y2,const int& _X1,const int& _Y1,const int& _X2,const int& _Y2)
    {
        return ( (_X1>=_x1) && (_Y1>=_y1) && 
                 (_X2<=_x2) && (_Y2<=_y2) );
    }
    
    bool OutSqu(const int& _x1,const int& _y1,const int& _x2,const int& _y2,const int& _X1,const int& _Y1,const int& _X2,const int& _Y2)
    {
        return ( (_x1>_X2) || (_y1>_Y2) || 
                 (_x2<_X1) || (_y2<_Y1) );
    }
    
    int Qry(const int& inx,const int& _x1,const int& _y1,const int& _x2,const int& _y2)
    {
        if (!inx) return 0; register int ret=0;
        if (InSqu(_x1,_y1,_x2,_y2,tree[inx].Lx,tree[inx].Ly,tree[inx].Rx,tree[inx].Ry))
            return tree[inx].sum;
        if (OutSqu(_x1,_y1,_x2,_y2,tree[inx].Lx,tree[inx].Ly,tree[inx].Rx,tree[inx].Ry))
            return 0;
        if (InSqu(_x1,_y1,_x2,_y2,tree[inx].p.x,tree[inx].p.y,tree[inx].p.x,tree[inx].p.y))
            ret+=tree[inx].p.v;
        ret+=Qry(LCH,_x1,_y1,_x2,_y2); ret+=Qry(RCH,_x1,_y1,_x2,_y2);
        return ret;
    }
    
    #undef LCH
    #undef RCH
};

int main()
{
    register int _x1,_x2,_y1,_y2,n,opt,ans; KDT::__Point pnt;
    readx(n); readx(n); KDT::MemInit(200005); 
    while (1)
    {
        readx(opt);
        if (opt==3) return 0; 
        if (opt==1)
        {
            readx(pnt.x); readx(pnt.y); readx(pnt.v);
            KDT::Ins(KDT::troo,pnt,0);
        }
        else
        {
            readx(_x1); readx(_y1); readx(_x2); readx(_y2);
            ans=KDT::Qry(KDT::troo,_x1,_y1,_x2,_y2);
            printf("%d\n",ans);
        }
    }
}
```

---

## 作者：Weng_Weijie (赞：5)

CDQ分治

把询问离线  
对于第二个询问$(x1,y1)(x2,y2)$，把它拆$(1,1)(x2,y2)-(1,1)(x1-1,y2)-(1,1)(x2,y1-1)+(1,1)(x1-1,y1-1)$

~~之后17w询问变成20w询问~~

首先按时间轴将所有询问分成两半，对两边分别递归处理内部的答案更新，之后再处理左边对右边的贡献

两边分别按x坐标排序，y坐标用树状数组(线段树)维护，双指针扫描一下就好了，至于排序，既然已经用了双指针，干脆用归并排序就好了

时间复杂度$\rm O(nlogn)$，空间复杂度$\rm O(n)$

代码：
```cpp
#include <stdio.h>
#include <algorithm>
#include <assert.h>

#define int long long

struct Query {int x, y, id, typ, num; } q[200005], t[200005];
inline bool operator < (const Query &a, const Query &b) {return a.id < b.id; }

int x1, y1, x2, y2, tot, w, S, x, y, z, op;
int b[2000005];
void add(int x, int y) {for (; x <= w; x += x & -x) b[x] += y; }
void clear(int x) {for (; x <= w; x += x & -x) b[x] = 0; }
int query(int x) {int ans = 0; for(; x; x -= x & -x) ans += b[x]; return ans; }
void CDQ(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	CDQ(l, mid); CDQ(mid + 1, r);
	int p1 = l, p2 = mid + 1, p3 = l;
	while (p1 <= mid && p2 <= r) {
		if (q[p1].x <= q[p2].x) {
			if (!q[p1].typ) add(q[p1].y, q[p1].num);
			t[p3++] = q[p1++];
		} else {
			if (q[p2].typ) q[p2].num += query(q[p2].y);
			t[p3++] = q[p2++];
		}
	}
	while (p1 <= mid) {
		if (!q[p1].typ) add(q[p1].y, q[p1].num);
		t[p3++] = q[p1++];
	}
	while (p2 <= r) {
		if (q[p2].typ) q[p2].num += query(q[p2].y);
		t[p3++] = q[p2++];
	}
	for (int i = l; i <= mid; i++) if (!q[i].typ)  clear(q[i].y);
	for (int i = l; i <= r; i++) q[i] = t[i];
}
signed main() {
	scanf("%lld%lld", &S, &w);
	while (scanf("%lld", &op), op ^ 3) {
		if (op == 1) {
			scanf("%lld%lld%lld", &x, &y, &z); ++tot;
			q[tot] = (Query) {x, y, tot, 0, z};
		} else {
			scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
			++tot, q[tot] = (Query) {x2, y2, tot, 1, 0};
			++tot, q[tot] = (Query) {x1 - 1, y2, tot, 1, 0};
			++tot, q[tot] = (Query) {x2, y1 - 1, tot, 1, 0};
			++tot, q[tot] = (Query) {x1 - 1, y1 - 1, tot, 1, 0};
		}
	}
	CDQ(1, tot);
	std::sort(q + 1, q + tot + 1);
	for (int i = 1; i <= tot; i++) 
		if (q[i].typ) {
			printf("%lld\n", 
				q[i].num - q[i + 1].num - q[i + 2].num + q[i + 3].num 
				+ S * (q[i].y - q[i + 3].y) * (q[i].x - q[i + 3].x));
			i += 3;
		}
	return 0;
}
```

---

## 作者：bzy369258147 (赞：4)

不同的解法,支持在线.
# 分块 + 权值线段树
这大概是除了CDQ以外最好写的方法了吧,对于2000000的区间，我们直接分成大小为3500(不一定最优秀)的块，每一列和每一块维护一个动态开点权值线段树，对于修改操作，直接将其插入该列和该块的权值线段树，对于查询操作，直接对于跨过的块和边角的权值线段树上二分即可.

时间复杂度 $ O( nlog_2W + m \sqrt{W}log_2W ) $

理论上是难以过去，但是考虑到修改操作十分稀疏，我们可以给权值线段树加一个路径lazy优化，对于一个size只有1的子树，我们可以不建出来，而是把要建的节点保存在该点.

事实证明以上优化十分有效。+O2可以AC此题.

不过好像有一个完全路径压缩的虚树版权值线段树,但是似乎十分难写.

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace WST{
	#define LR l,mid
	#define RR mid + 1,r
	#define mid ( (l + r) >> 1 )
	const int mxSize = 1e7;
	
	int ls[ mxSize ];
	int rs[ mxSize ];
	int v [ mxSize ];
	int lz[ mxSize ];
	int cnt = 0;
	
	int require() { return ++ cnt; }
	
	void push_down(int now,int l,int r){
	    if( !lz[now] or l == r )return ;
	    if( lz[now] <= mid )
	      { ls[now] = require(); v[ ls[now] ] = v[now],lz[ ls[now] ] = lz[now]; }
	    if( lz[now] >  mid )
	      { rs[now] = require(); v[ rs[now] ] = v[now],lz[ rs[now] ] = lz[now]; }
	    lz[now] = 0;
	}
	
	int insert(int now,int l,int r,int p,int val){
	    if( !now )
	      { now = require(); v[now] = val;lz[now] = p;return now; }
	    push_down(now,l,r); v[now] += val;
	    if( l == r )return now;
	    if( p <= mid )ls[now] = insert( ls[now],LR,p,val );
	    if( p >  mid )rs[now] = insert( rs[now],RR,p,val );
	    return now;
	}
	
	int query(int now,int l,int r,int p){
        if( !p or !now )return 0;
	    if( l == r )return v[now];
	    if( lz[now] )return ( p >= lz[now] ) ? v[now] : 0;
	    int ans = v[ ls[now] ] * ( p >= mid );
	    if( p < mid )ans += query( ls[now],LR,p );
	    if( p > mid )ans += query( rs[now],RR,p );
	    return ans;
	}
}

int size = 3500;

int main(){
    int w,op;cin >> w >> w; WST::cnt = w + w / size + 2;
    while( cin >> op ){
        if( op == 3 )break;
        if( op == 1 ){
            int x,y,A;cin >> x >> y >> A;
            WST::insert( x,1,w,y,A );
            WST::insert( w + x / size + 1,1,w,y,A );
        }
        if( op == 2 ){
            int X1,Y1,X2,Y2;cin >> X1 >> Y1 >> X2 >> Y2;
            int blockL = ( X1 - 1 ) / size + 1 + 1;
            int blockR = ( X2 + 1 ) / size - 1 + 1;
            int ans = 0;
            for( int b = blockL;b <= blockR;b ++ )
              { ans += WST::query( w + b,1,w,Y2 );
                ans -= WST::query( w + b,1,w,Y1 - 1 ); }
            for( ;X1 / size + 1 != blockL and X1 <= X2;X1 ++ )
              { ans += WST::query( X1,1,w,Y2 );
                ans -= WST::query( X1,1,w,Y1 - 1 ); }
            for( ;X2 / size + 1 != blockR and X2 >= X1;X2 -- )
              { ans += WST::query( X2,1,w,Y2 );
                ans -= WST::query( X2,1,w,Y1 - 1 ); }
            cout << ans << "\n";
        }
    }
    return 0;
}


```



---

## 作者：DukeLv (赞：4)

这个题其实和陌上花开有异曲同工之妙,只需要一个转化.陌上花开是x,y,z三维坐标轴,而此题直接把时间顺序想象成第一维就行了.

计算答案的时候有一步容斥原理,和矩形覆盖很像,就是(x2,y2) - (x1 - 1,y2) - (x2,y1 - 1) + (x1,y1),然后再加上s*(x2-x1)*(y2 -y2)便是答案.

剩下的就是cdq分治了,用树状数组维护一下3维偏序就行了,板子就不说了

上代码:

```

#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define duke(i,a,n) for(int i = a;i <= n;i++)
#define lv(i,a,n) for(int i = a;i >= n;i--)
#define clean(a) memset(a,0,sizeof(a))
#define pr pair<int,int>
#define mp make_pair
const int INF = 1 << 30;
const double eps = 1e-8;
typedef long long ll;
typedef double db;
#define B cout << "BBB" << endl;
template <class T>
void read(T &x)
{
	char c;
	bool op = 0;
	while(c = getchar(), c < '0' || c > '9')
		if(c == '-') op = 1;
	x = c - '0';
	while(c = getchar(), c >= '0' && c <= '9')
		x = x * 10 + c - '0';
	if(op) x = -x;
}
template <class T>
void write(T x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x >= 10) write(x / 10);
	putchar('0' + x % 10);
}
struct node
{
	int x,y,id,typ,num;
	inline bool operator < (const node &a) const
	{
		return id < a.id;
	}
}q[2000005],t[2000005];
struct tr
{
	int tree[2000005],kk;
	int lowbit(int x)
	{
		return x & (-x);
	}
	void add(int x,int k)
	{
		if(x == 0) B
		while(x <= kk)
		{
			tree[x] += k;
			x += lowbit(x);
		}
	}
	int query(int x)
	{
		int ans = 0;
		while(x)
		{
			ans += tree[x];
			x -= lowbit(x);
		}
		return ans;
	}
	void clear(int x)
	{
		while(x <= kk)
		{
			tree[x] = 0;
			x += lowbit(x);
		}
	}
}T;
int s,w,tot;
void cdq(int l,int r)
{
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l,mid);cdq(mid + 1,r);
	int p1 = l,p2 = mid + 1,p3 = l;
	while(p1 <= mid && p2 <= r)
	{
		if(q[p1].x <= q[p2].x)
		{
			if(!q[p1].typ) T.add(q[p1].y,q[p1].num);
			t[p3++] = q[p1++];
		}
		else
		{
			if(q[p2].typ) q[p2].num += T.query(q[p2].y);
			t[p3++] = q[p2++];
		}
	}
	while(p1 <= mid)
	{
		// cout<<q[p1].y<<endl;
		if(!q[p1].typ)
		T.add(q[p1].y,q[p1].num);
		t[p3++] = q[p1++];
	}
	while(p2 <= r)
	{
		if(q[p2].typ)
		q[p2].num += T.query(q[p2].y);
		t[p3++] = q[p2++];
	}
	duke(i,l,mid)
	{
		if(!q[i].typ) T.clear(q[i].y);
	}
	duke(i,l,r)
	{
		q[i] = t[i];
	}
}
int op;
int main()
{
	read(s);read(w);
	T.kk = w;
	while(scanf("%d",&op),op != 3)
	{
		if(op == 1)
		{
			int x,y,z;
			read(x);read(y);read(z);
			// x += 1;y += 1;
			q[++tot] = (node){x,y,tot,0,z};
		}
		else if(op == 2)
		{
			int x1,x2,y1,y2;
			read(x1);read(y1);read(x2);read(y2);
			// x1 += 1;y1 += 1;x2 += 1;y2 += 1;
			q[++tot] = (node){x2,y2,tot,1,0};
			q[++tot] = (node){x1 - 1,y2,tot,1,0};
			q[++tot] = (node){x2,y1 - 1,tot,1,0};
			q[++tot] = (node){x1 - 1,y1 - 1,tot,1,0};
		}
		// cout<<tot<<endl;
	}
	// cout<<"QAQ"<<endl;
	cdq(1,tot);
	sort(q + 1,q + tot + 1);
	duke(i,1,tot)
	{
		if(q[i].typ)
		{
			printf("%d\n",q[i].num - q[i + 1].num -	q[i + 2].num + q[i + 3].num + s * (q[i].y - q[i + 3].y) * (q[i].x - q[i + 3].x));
			i += 3;
		}
	}
	return 0;
}


```


---

## 作者：GKxx (赞：2)

由于本蒟蒻不会cdq分治，我申请把时限调大了然后树套树终于卡过去了...

~~可能需要一个O2~~

~~fread是个好东西~~

树状数组套splay（套treap也行）

非常裸的二维数点，注意横坐标离散化，树状数组维护横坐标，上面套splay维护纵坐标，查询就调用4次前缀和查询然后用容斥原理那样搞一下就行了

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

// 此处略去一个用fread实现的读入优化

#define npt NULL
#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define rrep(I, A, B) for (int I = (A); I >= (B); --I)

inline int lowbit(int x) { return x & -x; }

struct Command {
    int q, x, y, x1, y1, x2, y2;
    int a;
};

const int maxq = 2e5 + 100;
Command cmd[maxq];
int exes[maxq << 2];
int n, m, tot;

struct Node {
    int loc;
    int value, sum;
    Node *ch[2], *fa;
    explicit Node(int l = 0, int v = 0)
        : loc(l), value(v), sum(v), fa(npt) { ch[0] = ch[1] = npt; }
    int isc(int c) const { return fa && fa->ch[c] == this; }
    int isc() const { return fa ? isc(1) : -1; }
};

inline void update(Node*& x) {
    x->sum = x->value;
    rep(i, 0, 1) if (x->ch[i])
        x->sum += x->ch[i]->sum;
}
inline void rotate(Node*& x) {
    if (!x->fa) return;
    int d = x->isc();
    Node* f = x->fa;
    if (f->isc() != -1)
        f->fa->ch[f->isc()] = x;
    x->fa = f->fa;
    f->ch[d] = x->ch[d ^ 1];
    if (x->ch[d ^ 1]) x->ch[d ^ 1]->fa = f;
    x->ch[d ^ 1] = f;
    f->fa = x;
    update(f);
    update(x);
}
inline void splay(Node*& x, Node*& root) {
    if (x == root) return;
    Node* p = root->fa;
    while (x->fa != p) {
        Node* f = x->fa;
        if (f->fa == p) rotate(x);
        else {
            if (f->isc() == x->isc())
                rotate(f);
            else rotate(x);
            rotate(x);
        }
    }
    root = x;
}
inline void insertSplay(Node*& root, int pos, int val) {
    if (!root) {
        root = new Node(pos, val);
        return;
    }
    Node* curr = root;
    while (0207) {
    	curr->sum += val;
        if (pos == curr->loc) {
            curr->value += val;
            return;
        }
        int d = (pos > curr->loc);
        if (curr->ch[d]) curr = curr->ch[d];
        else {
            curr->ch[d] = new Node(pos, val);
            curr->ch[d]->fa = curr;
            curr = curr->ch[d];
            splay(curr, root);
            return;
        }
    }
}
inline int querySplay(Node* curr, int x) {
    if (!curr) return 0;
    int ret = 0;
    while (curr) {
        if (x < curr->loc) curr = curr->ch[0];
        else {
            if (curr->ch[0])
                ret += curr->ch[0]->sum + curr->value;
            else
                ret += curr->value;
            curr = curr->ch[1];
        }
    }
    return ret;
}

Node *root[maxq << 2];

inline void addBit(int x, int y, int v) {
    for (; x <= tot; x += lowbit(x)) insertSplay(root[x], y, v);
}
inline int queryBit(int x, int y) {
    int ans = 0;
    for (; x; x -= lowbit(x)) ans += querySplay(root[x], y);
    return ans;
}

int main() {
    // freopen("mokia.in", "r", stdin);
    // freopen("mokia.out", "w", stdout);
    { int zero; read(zero); }
    read(n);
    int q; read(q);
    while (q != 3) {
    	cmd[++m].q = q;
        if (q == 1) {
            read(cmd[m].x); read(cmd[m].y); read(cmd[m].a);
            exes[++tot] = cmd[m].x;
        } else {
            read(cmd[m].x1); read(cmd[m].y1); read(cmd[m].x2); read(cmd[m].y2);
            exes[++tot] = cmd[m].x1;
            exes[++tot] = cmd[m].x2;
        }
        read(q);
    }
    std::sort(exes + 1, exes + tot + 1);
    tot = std::unique(exes + 1, exes + tot + 1) - (exes + 1);
    rep(i, 1, m)
    	if (cmd[i].q == 1) {
    		cmd[i].x = std::lower_bound(exes + 1, exes + tot + 1, cmd[i].x) - exes;
    		addBit(cmd[i].x, cmd[i].y, cmd[i].a);
        } else {
            cmd[i].x1 = std::lower_bound(exes + 1, exes + tot + 1, cmd[i].x1) - exes;
            cmd[i].x2 = std::lower_bound(exes + 1, exes + tot + 1, cmd[i].x2) - exes;
            int w1 = queryBit(cmd[i].x2, cmd[i].y2);
            int w2 = queryBit(cmd[i].x2, cmd[i].y1 - 1);
            int w3 = queryBit(cmd[i].x1 - 1, cmd[i].y2);
            int w4 = queryBit(cmd[i].x1 - 1, cmd[i].y1 - 1);
            printf("%d\n", w1 - w2 - w3 + w4);
        }
    return 0;
}
```

---

## 作者：MuYC (赞：1)

这道题我爱了！

## 思路

看到这题目我直接想到了三值偏序，然后我就开始了不归之路

1.把操作按时间排序，就能离线操作了

2.首先读入的时候各个操作已经默认是按时间排序的了，所以不用考虑时间这一维

接着，操作分两种：
（1）.添加住户（相当于是把这个点的权值加上一个a）

（2）.查询住户（查询的这个范围是个矩形）

所以自然就可以用归并排序+树状数组来解决了

其中最妙的一步在于将操作2中的给出的两个点进行扩展，扩展成4个点来进行操作，然后在归并排序的时候按照坐标x来排序，根据树状数组的性质来进行操作：

结合代码来讲一下

    for (;tql!=3;){
        cin>>tql;
        if(tql == 1)R++,T[R].tt=R,cin>>T[R].x>>T[R].y>>T[R].z;
        if(tql == 2){
            R++;
            int m=R;
            book[m]=1;
            R=R,T[R].t=1,cin>>T[R].x>>T[R].y,T[R].tt=m;
            T[R].x--,T[R].y--;
            R++,T[R].t=4,cin>>T[R].x>>T[R].y,T[R].tt=m;
            R++,T[R].t=2,T[R].x=T[R-2].x,T[R].y=T[R-1].y,T[R].tt=m;
            R++,T[R].t=3,T[R].x=T[R-2].x,T[R].y=T[R-3].y,T[R].tt=m;
        }
   }


   （见tql==2的情况）
   
   （给拓展的四个点进行标记然后在后面计算答案）
   
if(T[t2].t == 1)tong[T[t2].tt]+=get(T[t2].y); 
   
if(T[t2].t == 2)tong[T[t2].tt]-=get(T[t2].y);
   
if(T[t2].t == 3)tong[T[t2].tt]-=get(T[t2].y);if(T[

t2].t == 4)tong[T[t2].tt]+=get(T[t2].y);

此处请自行脑补一个树状数组 

借用前面题解的图片来理解

![](https://i.loli.net/2018/09/15/5b9c83b75cb73.png)
            
            
            
  ## CODE
  ```cpp
#include  <bits/stdc++.h>
using namespace std;
int c[2005001];
int tong[200001];
int w,tql,R=0;
struct node{int x,y,z,t,tt;}T[200001],p[200001];
int book[200005];
int lowbit(int x){return x&(-x);}

int add(int x,int k){
    while(x <= w)c[x]+=k,x+=lowbit(x);
    return 0;
}

int get(int x){
    int total=0;
    while(x > 0)
    total+=c[x],x-=lowbit(x);
    return total;
}

int CDQ(int l , int r ){
    if(l == r)return 0;
    int mid=(l+r)>>1;
    CDQ(l,mid);CDQ(mid+1,r);
    int t1=l,t2=mid+1;
    for (int i = l ; i <= r ; i ++){
        if(T[t1].x <= T[t2].x && t1 <=mid || t2 > r){
            if(T[t1].t == 0)add(T[t1].y,T[t1].z);
            p[i]=T[t1],t1++;
        }
        else {
            if(T[t2].t == 1)tong[T[t2].tt]+=get(T[t2].y);
            if(T[t2].t == 2)tong[T[t2].tt]-=get(T[t2].y);
            if(T[t2].t == 3)tong[T[t2].tt]-=get(T[t2].y);
            if(T[t2].t == 4)tong[T[t2].tt]+=get(T[t2].y);
            p[i]=T[t2],t2++;
        }
    }
    for (int i = l ; i <= mid ; i ++)
    if(T[i].t == 0)add(T[i].y,-T[i].z);
    for (int i = l ; i <= r ; i ++)
    T[i]=p[i];
    return 0;
}
int main(){
    cin>>tql>>w;
    R=0;
    for (;tql!=3;){
        cin>>tql;
        if(tql == 1)R++,T[R].tt=R,cin>>T[R].x>>T[R].y>>T[R].z;
        if(tql == 2){
            R++;
            int m=R;
            book[m]=1;
            R=R,T[R].t=1,cin>>T[R].x>>T[R].y,T[R].tt=m;
            T[R].x--,T[R].y--;
            R++,T[R].t=4,cin>>T[R].x>>T[R].y,T[R].tt=m;
            R++,T[R].t=2,T[R].x=T[R-2].x,T[R].y=T[R-1].y,T[R].tt=m;
            R++,T[R].t=3,T[R].x=T[R-2].x,T[R].y=T[R-3].y,T[R].tt=m;
        }
        if(tql == 3)break;
    }
    
    CDQ(1,R);
    for (int i = 1 ; i <= R ; i ++)
    if(book[i] != 0)cout<<tong[i]<<endl;
    return 0;
}
```


---

## 作者：qianfujia (赞：1)

# 似乎本题题解里还没有用二维线段树过的
## 这是一道二维线段树板子题
### 动态开点，运用四分的思想，将区间分为左上，左下，右上，右下四块，分别进行递归求解

时间复杂度 $O(q \log W)$ 但是常数较大，被树状数组吊着打，动态开点后空间复杂度$O(s\log W)$ s为修改操作个数

贴代码
```
#include<bits/stdc++.h>
#define N 160010
using namespace std;
int tree[N*22], lu[N*22], ld[N*22], ru[N*22], rd[N*22], cnt = 1;//一分为四
inline void pushup(int rt){
	tree[rt] = tree[lu[rt]] + tree[ld[rt]] + tree[ru[rt]] + tree[rd[rt]];
}
inline void update(int x, int y, int rt, int LU, int LD, int RU, int RD, int p){
	if(LU == LD && RU == RD){tree[rt] += p; return ;}
	int midx = (LU + LD) >> 1, midy = (RU + RD) >> 1;
	if(midx >= x){
		if(midy >= y){
			if(!lu[rt])lu[rt] = ++ cnt;
			update(x, y, lu[rt], LU, midx, RU, midy, p);
		}
		else if(midy != RD){
			if(!ld[rt])ld[rt] = ++ cnt;
			update(x, y, ld[rt], LU, midx, midy + 1, RD, p);
		}
	}
	else if(midx != LD){
		if(midy >= y){
			if(!ru[rt])ru[rt] = ++ cnt;
			update(x, y, ru[rt], midx + 1, LD, RU, midy, p);
		}
		else if(midy != RD){
			if(!rd[rt])rd[rt] = ++ cnt;
			update(x, y, rd[rt], midx + 1, LD, midy + 1, RD, p);
		}
	}
	pushup(rt);
}
inline int query(int lx, int rx, int ly, int ry, int LU, int LD, int RU, int RD, int rt){
	if(lx <= LU && LD <= rx && ly <= RU && RD <= ry)return tree[rt];
	int midx = (LU + LD) >> 1, midy = (RU + RD) >> 1, ans = 0;
	if(midx >= lx && midy >= ly && lu[rt])ans += query(lx, rx, ly, ry, LU, midx, RU, midy, lu[rt]);
	if(midx >= lx && midy < ry && ld[rt] && midy != RD)ans += query(lx, rx, ly, ry, LU, midx, midy + 1, RD, ld[rt]);
	if(midx < rx && midy >= ly && ru[rt] && midx != LD)ans += query(lx, rx, ly, ry, midx + 1, LD, RU, midy, ru[rt]);
	if(midx < rx && midy < ry && rd[rt] && midx != LD && midy != RD)ans += query(lx, rx, ly, ry, midx + 1, LD, midy + 1, RD, rd[rt]);
	return ans;
}
int main(){
	int opt, w;
	while(scanf("%d", &opt) != EOF && opt != 3){
		if(opt == 0){
			scanf("%d", &w); continue;
		}
		if(opt == 1){
			int x, y, A; scanf("%d%d%d", &x, &y, &A);
			update(x, y, 1, 1, w, 1, w, A);
		} else{
			int xl, xr, yl, yr; scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
			printf("%d\n", query(xl, xr, yl, yr, 1, w, 1, w, 1));
		}
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

想必 [我的另外一篇题解](https://www.luogu.com.cn/article/6nhuppfs) 已经把这道题的思路说的很清楚了，但是那道题是把所有的修改全部告诉你，然后再一个一个问你矩阵和，但是这道题他是修改中夹着询问，但是没有关系，我们照样可做。

考虑将所有询问或修改存起来，因为我的另外一篇题解的那个思路还支持修改，那我们只需要将所有修改当成那个题里的 $n$ 个基站（有重复点不影响），将 $p$ 全部设置为 $0$，然后每次修改就正常修改就行，同样是整块改那个数和前缀和，散块直接改那个数，就做完了。

但这题的思维难度和代码难度远不止如此，下面说一下要改动的点：

- 这次前缀和数组就只能每个块的处理了，因为如果全部处理，修改时就会产生后面也要修改的情况，这样处理起来就比较麻烦，如果是块前缀和，就只需要对块进行暴力处理就行了。
- 对于每次修改我们要找到当前修改的这个坐标在 $a_i$ 中的位置，这个位置是作为散块的修改位置，因为整块它预处理时使用了排序，所以还得开一个数组记录排序后原本在 $i$ 位置的数，现在跑到哪里了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7+5;
struct node
{
	int x;
	int y;
	int p;
	int id;
}a[N];
int cmp(node x,node y)
{
	return x.x == y.x?x.y<y.y:x.x<y.x;
}
struct node1
{
	int y;
	int p;
	int id;
}s[N],s1[N];
int sum[N];
int id[N];
int cmp1(node1 x,node1 y)
{
	return x.y<y.y;
}
struct node2
{
	int x1;
	int y1;
	int x2;
	int y2;
}e[N];
struct node3
{
	int opt;
	int x1;
	int y1;
	int x2;
	int y2;
}w[N];
int mpp[N];
int mppp[N];
signed main()
{
	int qq = 0;
    int _,__,n = 0,m = 0;
    scanf("%d %d",&_,&__);
    while(1)
    {
    	int opt;
    	scanf("%d",&opt);
    	if(opt == 1)
    	{
    		int x,y,p;
    		scanf("%d %d %d",&x,&y,&p);
    		a[++n] = {x,y,0,n};
			w[++qq] = {opt,x,y,p,0};
		}
		else if(opt == 2)
		{
			int x1,y1,x2,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			e[++m] = {x1,y1,x2,y2};
			w[++qq] = {opt,x1,y1,x2,y2};
		}
		else
		{
			break;
		}
	}
	int len = sqrt(n);
    for(int i = 1;i<=n;i++)
    {
        id[i] = (i+len-1)/len;
    }
	sort(a+1,a+n+1,cmp);
	for(int i = 1;i<=n;i++)
	{
		s[i].y = a[i].y;
        s[i].p = a[i].p;
        s[i].id = i;
        s1[i] = s[i];
        mpp[a[i].id] = i;
	}
	for(int i = 1;i<=id[n];i++)
	{
		int l = (i-1)*len+1,r = min(i*len,n);
		sort(s1+l,s1+r+1,cmp1);
		sum[l] = s1[l].p;
		for(int j = l+1;j<=r;j++)
		{
			sum[j] = sum[j-1]+s1[i].p;
		}
	}
	for(int i = 1;i<=n;i++)
	{
		mppp[s1[i].id] = i;
	}
	int cnt = 0;
    for(int i = 1;i<=qq;i++)
    {
    	if(w[i].opt == 1)
    	{
    		cnt++;
    		int tt = mpp[cnt];
    		int ttt = mppp[tt];
    		s[tt].p+=w[i].x2;
    		s1[ttt].p+=w[i].x2;
    		int l = (id[ttt]-1)*len+1,r = min(id[ttt]*len,n);
    		sort(s1+l,s1+r+1,cmp1);
    		sum[l] = s1[l].p;
    		for(int i = l+1;i<=r;i++)
    		{
    			sum[i] = sum[i-1]+s1[i].p;
			}
		}
		else
		{
			int x1 = w[i].x1,y1 = w[i].y1,x2 = w[i].x2,y2 = w[i].y2;
	    	int l = 1,r = n,num = 0;
	    	while(l<=r)
	    	{
	    		int mid = l+r>>1;
	    		if(a[mid].x>=x1)
	    		{
	    			num = mid;
	    			r = mid-1;
				}
				else
				{
					l = mid+1;
				}
			}
			if(!num||a[num].x>x2)
			{
				printf("0\n");
				continue;
			}
			l = 1,r = n;
			int num1 = 0;
			while(l<=r)
	    	{
	    		int mid = l+r>>1;
	    		if(a[mid].x<=x2)
	    		{
	    			num1 = mid;
	    			l = mid+1;
				}
				else
				{
					r = mid-1;
				}
			}
			if(!num1||a[num1].x<x1)
			{
				printf("0\n");
				continue;
			}
			int ss = 0;
			for(int i = id[num]+1;i<=id[num1]-1;i++)
			{
				int l = (i-1)*len+1,r = i*len,num2 = 0;
		    	while(l<=r)
		    	{
		    		int mid = l+r>>1;
		    		if(s1[mid].y>=y1)
		    		{
		    			num2 = mid;
		    			r = mid-1;
					}
					else
					{
						l = mid+1;
					}
				}
				if(!num2||s1[num2].y>y2)
				{
					continue;
				}
				l = (i-1)*len+1,r = i*len;
				int num3 = 0;
				while(l<=r)
		    	{
		    		int mid = l+r>>1;
		    		if(s1[mid].y<=y2)
		    		{
		    			num3 = mid;
		    			l = mid+1;
					}
					else
					{
						r = mid-1;
					}
				}
				if(!num3||s1[num3].y<y1)
				{
					continue;
				}
				if(num2 == (i-1)*len+1)
				{
					ss+=sum[num3];
				}
				else
				{
					ss+=sum[num3]-sum[num2-1];
				}
			}
			if(id[num] == id[num1])
			{
				for(int i = num;i<=num1;i++)
				{
					if(s[i].y>=y1&&s[i].y<=y2)
					{
						ss+=s[i].p;
					}
				}
			}
			else
			{
				for(int i = num;i<=id[num]*len;i++)
				{
					if(s[i].y>=y1&&s[i].y<=y2)
					{
						ss+=s[i].p;
					}
				}
				for(int i = (id[num1]-1)*len+1;i<=num1;i++)
				{
					if(s[i].y>=y1&&s[i].y<=y2)
					{
						ss+=s[i].p;
					}
				}
			}
			printf("%d\n",ss);
		}
	}
    return 0;
}
```
[提交记录。](https://www.luogu.com.cn/record/193833253)

这个题还是很有难度的，如果有不会的欢迎私信提问！

---

## 作者：hzoi_liuchang (赞：0)


## 分析
我们会发现格子很大，但是修改数和查询数比较小

因此，我们肯定不能维护整个格子，而要从修改和查询上找突破口

我们设第$i$次修改的点的横纵坐标分别为 $nx,ny$ ，如果它要对之后的某个矩形产生贡献的话

必须满足 $x_1 \leq nx \leq x_2,y_1\leq ny \leq y_2$

如果加上时间的限制，那么就是一个五维的偏序，不好处理

我们可以用容斥的方法把一个大矩形分成四个小矩形，类似于求前缀和的方法

即 $sum[x_2][y_2]-sum[x_2][y_1-1]-sum[x_1-1][y2]+sum[x_1-1][y_1-1]$

$sum[i][j]$ 表示原点和 $(i,j)$ 围成的矩形所增加的值

这样问题就变成了一个三维偏序 $i<j,x[i] \leq x[j],y[i] \leq y[j]$

然后就可以离线用 $CDQ$ 分治解决

## 代码
``` cpp
#include<cstdio>
#include<algorithm>
inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=2e6+5;
struct asd{
	int id,x,y,wz,val;
	bool jud;
	asd(){}
	asd(int aa,int bb,int cc,int dd,int ee,bool ff){
		id=aa,x=bb,y=cc,wz=dd,val=ee,jud=ff;
	}
}b[maxn];
int s,w,cnt,js;
bool cmp1(asd aa,asd bb){
	if(aa.id==bb.id && aa.x==bb.x) return aa.y<bb.y;
	if(aa.id==bb.id) return aa.x<bb.x;
	return aa.id<bb.id;
}
bool cmp2(asd aa,asd bb){
	if(aa.x==bb.x) return aa.y<bb.y;
	return aa.x<bb.x;
}
int lb(int xx){
	return xx&-xx;
}
int tr[maxn];
void ad(int wz,int val){
	for(int i=wz;i<maxn;i+=lb(i)){
		tr[i]+=val;
	}
}
int cx(int wz){
	int nans=0;
	for(int i=wz;i>0;i-=lb(i)){
		nans+=tr[i];
	}
	return nans;
}
int ans[maxn][6];
void solve(int l,int r){
	if(l==r) return;
	int mids=(l+r)>>1;
	solve(l,mids);
	solve(mids+1,r);
	std::sort(b+l,b+mids+1,cmp2);
	std::sort(b+mids+1,b+r+1,cmp2);
	int now=l;
	for(int i=mids+1;i<=r;i++){
		while(now<=mids && b[now].x<=b[i].x){
			if(!b[now].jud){
				ad(b[now].y,b[now].val);
			}
			now++;
		}
		if(b[i].jud){
			ans[b[i].id][b[i].wz]+=cx(b[i].y);
		}
	}
	for(int i=now-1;i>=l;i--){
		if(!b[i].jud){
			ad(b[i].y,-b[i].val);
		}
	}
}
int jl[maxn],anss[maxn];
int main(){
	s=read(),w=read();
	while(1){
		int aa,bb,cc,dd,ee;
		aa=read();
		js++;
		jl[js]=aa;
		if(aa==1){
			bb=read(),cc=read(),dd=read();
			bb++,cc++;
			b[++cnt]=asd(js,bb,cc,0,dd,0);
		} else if(aa==2){
			bb=read(),cc=read(),dd=read(),ee=read();
			bb++,cc++,dd++,ee++;
			b[++cnt]=asd(js,dd,ee,1,0,1);
			b[++cnt]=asd(js,dd,cc-1,2,0,1);
			b[++cnt]=asd(js,bb-1,ee,3,0,1);
			b[++cnt]=asd(js,bb-1,cc-1,4,0,1);
			anss[js]=(dd-bb+1)*(ee-cc+1)*s;
		} else {
			break;
		}
	}
	std::sort(b+1,b+1+cnt,cmp1);
	solve(1,cnt);
	for(int i=1;i<js;i++){
		if(jl[i]==2){
			printf("%d\n",ans[i][1]-ans[i][2]-ans[i][3]+ans[i][4]+anss[i]);
		}
	}
	return 0;
}
```

---

## 作者：OYBDOOO (赞：0)

### 我CDQ一直学不明白，看了看别人的思路，想想后写篇题解。将询问与修改排序，通过前缀和来搞掉询问。由于此题性质，在CDQ（ll，rr）内，先用时间来分治，这样保证题目询问与修改的性质，分治完处理[ll,rr]区间，分左右两半，按坐标（x）排序，这样就是一个二维数点，可以通过树状数组维护得出，在函数尾部要清空，其实，CDQ内的顺序大概就是按照题目的性质吧。
```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
using namespace std;
int lowbit(int x)
{
	return x&(-x);
}
struct AAA
{
	int x,y,num,xws,ans,ti;
}xw[210000];
int bj,cnt=0;
int ccc[2000100];
bool cmp(const AAA&ax,const AAA&bx)
{
	if(ax.x==bx.x)return ax.y<bx.y;
	return ax.x<bx.x;
}
bool cmpp(const AAA&ax,const AAA&bx)
{
	return ax.ti<bx.ti;
}
void add(int pos,int x)
{
	for(int i=pos;i<=bj;i+=lowbit(i))
		ccc[i]+=x;
}
int gtsm(int pos)
{
	int ret=0,i;
	for(i=pos;i>0;i-=lowbit(i))
		ret+=ccc[i];
	return ret;
}
void CDQ(int ll,int rr)
{
	if(ll==rr)return;
	int mid=(ll+rr)/2;
	CDQ(ll,mid);
	CDQ(mid+1,rr);
	sort(xw+ll,xw+mid+1,cmp);
	//int k;
	//for(k=ll;k<=mid;k++)printf("::%d %d:: ",xw[k].x,xw[k].y);
	//cout<<endl;
	sort(xw+mid+1,xw+rr+1,cmp);
	//for(k=mid+1;k<=rr;k++)printf("::%d %d:: ",xw[k].x,xw[k].y);
	//cout<<endl;
	int i=ll,j;
	for(j=mid+1;j<=rr;j++)
	{
		while(xw[i].x<=xw[j].x&&i<=mid)
		{
			if(xw[i].xws==0)
				add(xw[i].y,xw[i].num);
			i++;
		}
		if(xw[j].xws==1)
			xw[j].ans+=gtsm(xw[j].y);
	}
	for(j=ll;j<i;j++)
		if(xw[j].xws==0)
			add(xw[j].y,-xw[j].num);
}
int main()
{
	int aa,bb,cc,dd;
	scanf("%d",&aa);
	scanf("%d",&aa);
	bj=aa+1;
	int opt,i;
	while(1)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			cnt++;
			scanf("%d%d",&xw[cnt].x,&xw[cnt].y);
			xw[cnt].x++;
			xw[cnt].y++;
			xw[cnt].ti=cnt;
			scanf("%d",&xw[cnt].num);
		}
		else if(opt==2)
		{
			scanf("%d%d%d%d",&aa,&bb,&cc,&dd);
			aa++;bb++;cc++;dd++;
			cnt++;
			xw[cnt].x=aa-1;xw[cnt].y=bb-1;
			xw[cnt].xws=1;xw[cnt].ti=cnt;
			cnt++;
			xw[cnt].x=aa-1;xw[cnt].y=dd;
			xw[cnt].xws=1;xw[cnt].ti=cnt;
			cnt++;
			xw[cnt].x=cc;xw[cnt].y=bb-1;
			xw[cnt].xws=1;xw[cnt].ti=cnt;
			cnt++;
			xw[cnt].x=cc;xw[cnt].y=dd;
			xw[cnt].xws=1;xw[cnt].ti=cnt;
		}
		else break;
	}
	CDQ(1,cnt);
	sort(xw+1,xw+cnt+1,cmpp);
	for(i=1;i<=cnt;i++)
	{
		if(xw[i].xws==1)
		{
			printf("%d\n",xw[i].ans+xw[i+3].ans-xw[i+1].ans-xw[i+2].ans);
			i+=3;
		}
	}
	return 0;
}
```


---

## 作者：Lance1ot (赞：0)

乍一看，这是一个二维树状数组题

发现被数据范围淦翻了

作为一个从来不愿意动脑子的人。当然是能用数据结构绝不像算法啦。

考虑将树状数组套平衡树。

发现空间可以开的下。只不过时间有点卡紧。不过前面有位仁兄申请将时间调至两秒。应该就够了

插入不在话下。对于询问，我们可以利用树状数组前缀和，以及平衡树中的前缀和搞下来。

其实思想不难，难的就是code

```cpp

//没有卡常，所以会T一个点
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#define Ls T[R].ch[0]
#define Rs T[R].ch[1]

const int maxn=4000000;

struct node
{
	int Size;//节点个数
	int Self;//可重集
	int Val;
	int Key;//treap的key
	int ch[2];
	node (int a=0,int b=0,int c=0)
	{
		Val=a;
		Size=Self=b;
		Key=c;
		ch[0]=ch[1]=0;
	}
};

node T[maxn];
int tail;
int len,base[maxn];

void sum(int R)
{
	T[R].Size=T[R].Self+T[Ls].Size+T[Rs].Size;
	return ;
}

void rotate(int &R,int base)
{
	int k=T[R].ch[base^1];
	T[R].ch[base^1]=T[k].ch[base];
	T[k].ch[base]=R;
	sum(R);sum(k);
	R=k;
	return ;
}//旋转和更新

int cmpnum(int R,int val)
{
	if(T[R].Val==val)	return -1;
	return T[R].Val<val;
}//比较该往子树的那个方向走

void insert(int &R,int val,int k)
{
	if(!R)	//节点不存在，直接新建
	{
		R=++tail;
		T[R]=node(val,k,rand());
		return ;
	}
	int dir=cmpnum(R,val);
	if(dir==-1)//鉴于数据范围比较小，可以不考虑空间回收
	{
		T[R].Size+=k;
		T[R].Self+=k;
		return;
	}
	insert(T[R].ch[dir],val,k);
	sum(R);
	if(T[R].Key<T[T[R].ch[dir]].Key)	rotate(R,dir^1);
	return ;
}

int check(int R,int val)//在平衡树中，找到多少个比他小的点，然后前缀和
{
	if(!R)	return 0;
	int dir=cmpnum(R,val);
	if(dir==-1)	return T[Ls].Size+T[R].Self;
	if(dir==0)	return check(Ls,val);
	if(dir==1)	return check(Rs,val)+T[Ls].Size+T[R].Self;
	return 0;
}

void Insert(int pos,int val,int k)//树套树插入
{
	while(pos<=len)
	{
		insert(base[pos],val,k);
		pos+=(pos&(-pos));
	}
	return ;
}

int Sum(int pos,int l,int r)//处理询问
{
	int res=0;
	while(pos)
	{
		res=res+check(base[pos],r)-check(base[pos],l-1);//前缀和
		pos-=(pos&(-pos));
	}
	return res;
}

int Ask(int L,int R,int l,int r)
{
	return Sum(R,l,r)-Sum(L-1,l,r);
}

void init(int n)
{
	len=n;
	return ;
}

int main()
{
	int opt,a,b,c,d;
	scanf("%d%d",&opt,&a);
	init(a);
	scanf("%d",&opt);
	while(opt!=3)
	{
		if(opt==1)
		{
			scanf("%d%d%d",&a,&b,&c);
			Insert(a,b,c);
		}
		if(opt==2)
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			printf("%d\n",Ask(a,c,b,d));
		}
		scanf("%d",&opt);
	}
	return 0;
}
```

---

## 作者：partychicken (赞：0)

### CDQ分治

看数据范围：160000个修改，10000个查询。怎么看都别扭，加起来都不是整数的！！！所以为了凑成整数，我们把一个查询拆成四个查询，这样就是整数了233

这题卡空间卡的特别死（我才不会告诉你我二维线段树卡空间卡了一晚上才60分的）

所以只好CDQ分治了（明明二维线段树那么好写）

我们把操作的时间当成一维$t_i$，然后就变成了对于每个查询操作，回答所有满足$t\le t_i,x\le x_i,y\le y_i$的修改操作的权值和，然后就是三维偏序的板子了

记录一下我愚蠢的错误：调试的时候怀疑清空出了问题，就memset了一下。调了20min发现**没有递归右区间**(f\*\*k,我TM是SB吧)。然后交上去，TLE！嗯？怎么回事儿？又调了20min发现我把清空加回来以后没有删memset，mmp

谨以此题解悼念因我SB而逝去的1个小时

```
#include<bits/stdc++.h>

using namespace std;

struct Operate
{
    int posx,posy,id,val,type;

    Operate(){}
    Operate(int posx,int posy,int id,int val,int type):posx(posx),posy(posy),id(id),val(val),type(type){}
}op[200010];
int cnt;

int ans[200010],qucnt;

int s,n;

bool cmpx(const Operate &x,const Operate &y)
{
    return x.posx<y.posx;
}

bool cmpid(const Operate &x,const Operate &y)
{
    return x.id<y.id;
}

struct BIT
{
    int tr[2000010];

    int lowbit(int x)
    {
        return x&-x;
    }

    void modify(int pos,int val)
    {
        for(;pos<=n;pos+=lowbit(pos))
        {
            tr[pos]+=val;
        }
    }

    int query(int pos)
    {
        int res=0;
        for(;pos;pos-=lowbit(pos))
        {
            res+=tr[pos];
        }
        return res;
    }
}A;

void CDQ(int l,int r)
{
    if(l==r) return;
    int mid=l+r>>1;
    CDQ(l,mid);
    sort(op+l,op+mid+1,cmpx);
    sort(op+mid+1,op+r+1,cmpx);
    int ptr=l;
    for(int i=mid+1;i<=r;i++)
    {
        while(op[ptr].posx<=op[i].posx&&ptr<=mid)
        {
            if(op[ptr].type==1) A.modify(op[ptr].posy,op[ptr].val);           
            ptr++;
        }
        if(op[i].type==2)
        {
            ans[op[i].id]+=(A.query(op[i].posy)+op[i].posx*op[i].posy*s)*op[i].val;
        }
    }
    for(int i=l;i<ptr;i++)
    {
        if(op[i].type==1) A.modify(op[i].posy,-op[i].val);           
    }
    sort(op+l,op+r+1,cmpid);
    CDQ(mid+1,r);
}

bool vis[200010];

int main()
{
    cin>>s>>n;
    int opt;
    for(int i=1;cin>>opt;i++)
    {
        if(opt==3) break;
        if(opt==1)
        {
            int x,y,val;
            cin>>x>>y>>val;
            op[++cnt]=Operate(x,y,i,val,1);
        }
        else
        {
            int lx,ly,rx,ry;
            cin>>lx>>ly>>rx>>ry;
            op[++cnt]=Operate(rx,ry,i,1,2);
            op[++cnt]=Operate(rx,ly-1,i,-1,2);
            op[++cnt]=Operate(lx-1,ry,i,-1,2);
            op[++cnt]=Operate(lx-1,ly-1,i,1,2);
            vis[i]=1;
        }
    }
    CDQ(1,cnt);
    for(int i=1;i<=200000;i++)
    {
        if(vis[i])
        {
            cout<<ans[i]<<'\n';
        }
    }
}
```

---

