# [JSOI2008] Blue Mary 开公司

## 题目背景

Blue Mary 最近在筹备开一家自己的网络公司。由于他缺乏经济头脑，所以先后聘请了若干个金融顾问为他设计经营方案。

## 题目描述

万事开头难，经营公司更是如此。开始的收益往往是很低的，不过随着时间的增长会慢慢变好。也就是说，**对于一个金融顾问 $i$，他设计的经营方案中，每天的收益都比前一天高，并且均增长一个相同的量 $P_i$。**

由于金融顾问的工作效率不高，**所以在特定的时间，Blue Mary 只能根据他已经得到的经营方案来估算某一时间的最大收益**。由于 Blue Mary 是很没有经济头脑的，所以他在估算每天的最佳获益时完全不会考虑之前的情况，而是直接从所有金融顾问的方案中选择一个在当天获益最大的方案的当天的获益值，例如：

有如下两个金融顾问分别对前四天的收益方案做了设计：

|   | 第一天 | 第二天 | 第三天 | 第四天 | $P_i$ |
| :-: | :-: | :-: | :-: | :-: | :-: |
| 顾问 1 | $1$ | $5 $| $9$ | $13$ | $4$ |
| 顾问 2 | $2$ | $5$ | $8$ | $11$ | $3$ |

在第一天，Blue Mary 认为最大收益是 $2$（使用顾问 2 的方案），而在第三天和第四天，他认为最大收益分别是 $9$ 和 $13$（使用顾问 1 的方案）。而他认为前四天的最大收益是：$2 + 5 + 9 + 13 = 29$。

现在你作为 Blue Mary 公司的副总经理，会不时收到金融顾问的设计方案，也需要随时回答 Blue Mary 对某天的“最大收益”的询问（这里的“最大收益”是按照 Blue Mary 的计算方法）。**一开始没有收到任何方案时，你可以认为每天的最大收益值是 0**。下面是一组收到方案和回答询问的例子：


- 询问 $2$，回答 $0$。
- 收到方案：$0\ 1\ 2\ 3\ 4\ 5\ \cdots$
- 询问 $2$，回答 $1$。
- 收到方案：$2\ 2.1\ 2.2\ 2.3\ 2.4\ \cdots$
- 询问 $2$，回答 $2.1$。

## 说明/提示

**数据范围**

$1 \leq N \leq 10 ^ 5$，$1 \leq T \leq 5\times 10 ^ 4$，$0 < P < 100$，$|S| \leq 10 ^ 5$。

**提示**

本题读写数据量可能相当巨大，请选手注意选择高效的文件读写方式。

## 样例 #1

### 输入

```
10
Project 5.10200 0.65000
Project 2.76200 1.43000
Query 4
Query 2
Project 3.80200 1.17000
Query 2
Query 3
Query 1
Project 4.58200 0.91000
Project 5.36200 0.39000```

### 输出

```
0
0
0
0
0```

# 题解

## 作者：LengChu (赞：23)

## 题解&&李超线段树学习笔记

### 一.李超线段树解决的问题

考虑下面一个问题： 

定义一个坐标系，有m次操作 

操作1：添加一条直线 

操作2：求x=x0这条直线和其他直线的交点的最高纵坐标

要求时间复杂度log级别，**可以用线段树维护**。

### 二.原理

对于一个区间，我们维护该区间的所有直线中，没有被其他直线覆盖的从上往下去看在x轴上的投影最大的直线（称为标记直线）。

其实这条直线的意义就是对这个区间内**大多数点**而言最优的直线，但也**不一定是最优的直线**，更优解可能在更小的区间内。

现在插入一条直线（称为新直线）到了一个区间，尝试更改该区间的标记直线。

分为几种情况：

1.新直线完全覆盖标记直线，直接更新并return，不用继续向下更新。

2.新直线完全被覆盖，那么新直线无用，直接return。

3.不是上面两种情况，判断两条直线哪一个投影大一些，作为新的标记直线，再递归下去处理。

询问时直接整个线段树包含x0的区间所存的线段取max即可。

其实相当于一个标记永久化的思想。

### 三.细节

如何判断两条直线哪一个应该作为标记直线呢？

分类讨论，设原标记直线为y，新直线为x。

1.k[x]>k[y]

如图，蓝色的代表线段中垂线。

![](http://a2.qpic.cn/psb?/V1190t7T1Jiov3/L0EYCRX232UeawP*7LPTk19pqy16r*Rwqh**LgboHJI!/b/dLkAAAAAAAAA&ek=1&kp=1&pt=0&bo=wAMcAgAAAAADF.8!&tl=1&vuin=630449676&tm=1545645600&sce=60-2-2&rf=viewer_4)

可以直观感受到如果斜率更大且在中点所对应的x上y更大，则投影更大。

还可以清楚认识到y直线对右边的区间已经没有贡献了，在右区间内x肯定优于y，但是y对左边可能还有贡献，所以把y放到左区间去更新一波答案就好。

2.k[x]<k[y]

道理同上，结论是如果斜率更小且在中点所对应的x上y更大，则投影更大。

较弱的那条直线对左区间没有贡献。

### 四.练习题

P4254 裸题，唯一的区别是纵截距给的是x==1的。

bzoj4515 听说是树剖+李超线段树



------------



## Code：

```
#include<bits/stdc++.h>
#define ll long long
#define db double
#define in inline
#define rint register int
#define ls (id<<1)
#define rs (id<<1|1)
using namespace std;
int n,t[200010],cnt;
db k[100010],b[100010];
char s[10];
in ll read()
{
    ll x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}
in db w (int id,int x) { return k[id]*(x-1)+b[id]; }
in void updata(int id,int l,int r,int x)
{
    if(w(x,l)>w(t[id],l)&&w(x,r)>w(t[id],r)) { t[id]=x; return; }//如果完全覆盖 直接return
    if(w(x,l)<=w(t[id],l)&&w(x,r)<=w(t[id],r)) return; //如果完全被覆盖 直接return
    //上面两种情况已经可以解决l==r时候的问题了 所以不用判断 
    int mid=(l+r)>>1;
    if(k[t[id]] < k[x])
    {
    	//如果新加入直线的斜率更大，且中点纵坐标更大，更改标记直线
        if(w(x,mid) > w(t[id],mid)) updata(ls,l,mid,t[id]),t[id]=x; 
        //因为标记直线有可能在左区间还有贡献 所以把以前的标记直线丢到左区间 
        else updata(rs,mid+1,r,x);
        //如果纵坐标更小 那么新加入直线可能在右区间有贡献 
    }
    else //同理 
    {
        if(w(x,mid) > w(t[id],mid)) updata(rs,mid+1,r,t[id]),t[id]=x;
        else updata(ls,l,mid,x);
    }
}
in db query(int id,int l,int r,int x)
{
    if(l==r) return w(t[id],x);
    int mid=(l+r)>>1;
    if(x<=mid) return max(w(t[id],x),query(ls,l,mid,x));
    else return max(w(t[id],x),query(rs,mid+1,r,x));
}
int main()
{
    n=read();
    while(n--)
    {
        scanf("%s",s);
        if(s[0]=='P')
        {
            cnt++;
            scanf("%lf%lf",&b[cnt],&k[cnt]);
            updata(1,1,50005,cnt);
        }
        else
        {
            int x=read();
            printf("%d\n",(int)(query(1,1,50005,x)/100)) ;
        }
    }
    return 0;
}

```


---

## 作者：Scarlet_Hypoc (赞：11)

看来大家都是用李超线段树做的qwq，蒟蒻来一个cdq的做法。

脑补一下不难发现，最后对答案可能有贡献的那些直线，即处于最上方的那些直线，一定是一个下凸包的形状，像这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/cfdj6xf9.png)


假如按时间顺序加入的直线的斜率递增，那么就可以很方便地维护出这个凸包，但题目并不保证这一点。

具体来说，一条直线能对一个询问产生贡献，需要满足：$t_i<t_j$。

而我们希望直线按斜率递增的顺序出现，即 $k_i<k_j$。

诶，那不是正好可以用cdq分治来做吗？

做法也很简单，将操作以时间顺序排好然后分治。每次递归完左右区间后，将左区间内的直线按斜率递增排序，然后一条一条加入单调队列。接着就可以很容易地更新右区间内的询问了。

当然，可以将右区间内的询问也进行排序，那么求解会变得更加简单，排序可以在分治时直接归并排序排好，时间复杂度 $O(n\log n)$。

~~但是由于浮点数运算次数较多所以跑的并不算快~~，在吸了氧后跑到了 $938ms$。

代码如下：
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define maxn 100010
#define eps 1e-8

int n;
struct par{int type;double k,b;int pos;}a[maxn],tmp[maxn];
struct line{double k,b;}q[maxn];
int st,ed;
double meet(line x,line y){return (y.b-x.b)/(x.k-y.k);}
int dcmp(double x){return x>eps?1:x<-eps?-1:0;}
void cdq(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;cdq(l,mid);cdq(mid+1,r);
	//求解
	q[st=ed=1]=(line){0,0};
	for(int i=l;i<=mid;i++)if(!a[i].type){
		line now=(line){a[i].k,a[i].b};
		while(ed>0&&dcmp(q[ed].k-now.k)==0&&dcmp(q[ed].b-now.b)<0)ed--;//特判斜率相同的直线
		while(ed>1&&dcmp(meet(q[ed],q[ed-1])-meet(q[ed],now))>0)ed--;
		q[++ed]=now;
	}
	for(int i=mid+1;i<=r;i++)if(a[i].type){
		while(st<ed&&a[i].k-meet(q[st],q[st+1])>eps)st++;
		a[i].b=max(a[i].b,q[st].b+q[st].k*a[i].k);
	}
	//归并
	int x=l,y=mid+1,now=0;
	while(x<=mid&&y<=r){
		if(dcmp(a[x].k-a[y].k)<0)tmp[++now]=a[x++];
		else tmp[++now]=a[y++];
	}
	while(x<=mid)tmp[++now]=a[x++];
	while(y<=r)tmp[++now]=a[y++];
	for(int i=l;i<=r;i++)a[i]=tmp[i-l+1];
}
bool cmp(par x,par y){return x.pos<y.pos;}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		char s[10];scanf("%s",s);
		if(s[0]=='P')a[i].type=0,scanf("%lf %lf",&a[i].b,&a[i].k),a[i].b-=a[i].k;
		else a[i].type=1,scanf("%lf",&a[i].k);
		a[i].pos=i;
	}
	cdq(1,n);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	if(a[i].type)printf("%d\n",(int)a[i].b/100);
}
```

---

## 作者：DQYdqy (赞：11)

**先安利一发自己的博客：**[ヾ(≧∇≦*)ゝ](http://www.cnblogs.com/NLDQY/p/10147594.html)
	
#### **大致题意：** 
有两种操作：1.给你一条一次函数 2.给你一个x，让你求所有函数中最大的y

现在有n个操作，要求你对每一个操作2输出最大的y值/100的结果

#### **Solution:**
这道题可以让我们很好的了解李超线段树

什么是李超线段树呢？

李超线段树是用来解决二维直角坐标系上给定一条线求最值的一类题目的线段树

这一类题目往往很难像传统线段树一样下传lazy_tag，所以就需要用到标记永久化

标记永久化作为预备知识，就不在此多做赘述了

好了，进入正题

----------
我们用tag来维护当前区间内mid上的最大y值所属的函数的编号，每次插入新的函数，我们需要分情况讨论来对tag进行更新

**若新插入的函数斜率比tag所记录的函数斜率更大**

1.若新函数在mid上的y值也大于tag，那我们就可以直接把tag覆盖为新的函数，再用**原tag**去更新左区间。

因为原tag对于**右区间**肯定是不会有贡献了的，但对于**左区间**却不一定，所以我们需要再次去进行更新，而原区间tag直接被覆盖，**右区间**则继续用新函数去尝试更新

图解：![此处输入图片的描述][2]

2.若新函数在mid上的y值小于tag，则再尝试用新函数去更新**右区间**，**左区间**就不用管了。

因为新函数在mid上已经比tag要小，则新函数对于**左区间**肯定不会再有贡献，而对于**右区间**却可能有贡献，所以还要再往右更新，基本原理跟之前差不多，就不再给出图解

**若新插入的函数斜率比tag所记录的函数斜率更小**

1.若新函数在mid上的值大于tag，我们就覆盖原tag，同时用原tag去更新**右区间**。由于斜率比原tag要小，则这种情况下，原tag对于**左区间**肯定是不会有贡献的，但对**右区间**却不一定,所以还需要去尝试更新**右区间**。

2.若原区间在mid的值小于tag，则在用新函数去尝试更新左区间，原理和以上大同小异

#### **Code：**
```
#include<bits/stdc++.h>
#define N 1000020
using namespace std;
typedef double dl;
int n,t=1;
struct sgt_tag{
    #define ls q<<1
    #define rs q<<1|1
    int tot,tag[N*4];
    struct function{dl k,b;}fun[N*4];
    inline dl val(int x,int id){return fun[id].k*(x-1)+fun[id].b;}//因为起始点是1所以x要-1
    inline void ins(dl k,dl b){fun[++tot].k=k;fun[tot].b=b;change(1,1,N,tot);}
    inline void change(int q,int l,int r,int id){
        if(l==r){
            if(val(l,id)>val(l,tag[q]))tag[q]=id;
            return ;
        }
        int mid=(l+r)>>1;
        if(fun[id].k>fun[tag[q]].k){
            if(val(mid,id)>val(mid,tag[q]))change(ls,l,mid,tag[q]),tag[q]=id;
            else change(rs,mid+1,r,id);
        }else{
            if(val(mid,id)>val(mid,tag[q]))change(rs,mid+1,r,tag[q]),tag[q]=id;
            else change(ls,l,mid,id);
        }
    }
    inline dl query(int q,int l,int r,int x){
        if(l==r)return val(l,tag[q]);
        int mid=(l+r)>>1;dl ans=val(x,tag[q]);
        if(x<=mid)ans=max(ans,query(ls,l,mid,x));
        else ans=max(ans,query(rs,mid+1,r,x));
        return ans;
    }
}T;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int main(){
    n=read();
    begin:if(t>n)goto end;t++;
    char ch[10];scanf("%s",ch);
    if(ch[0]=='P'){dl k,b;scanf("%lf%lf",&b,&k);T.ins(k,b);}
    if(ch[0]=='Q'){int x=read();dl ans=T.query(1,1,N,x);printf("%d\n",(int)ans/100);}
    goto begin;
    end:return 0;
}
```

  [2]: https://files-cdn.cnblogs.com/files/NLDQY/tu1.bmp

---

## 作者：风羽跃 (赞：8)


关键句：“每天的收益都比前一天高，并且均增长一个相同的量 $Pi$”。

言外之意，如果把收益的变化看做一段函数，那么它就是以 $Pi$ 为斜率且单调递增的一次函数！准确来说，它的图像是一条线段。

由此我们引入一种数据结构：

李超线段树。

#### 什么是李超线段树？

李超线段树是支持区间加入一条平面上的线段，单点询问函数最值的一种线段树。

#### 什么是线段树？

线段树可以在 $O(logn)$ 的时间复杂度内完成单点修改、区间修改、单点查询、区间查询，是一种常用数据结构，主要用于维护区间信息。

李超线段树的每个节点，存储当前区间内最大优势线段，即在这个区间内所有线段中处于最高位置时所占横坐标跨度最大的线段。

存储方式：一次函数（存储 $k$，$b$）。

#### 修改：

分类讨论。

若当前区间内新线段完全高于老线段，直接替换；

若当前区间内新线段完全低于老线段，跳过；

若一部分高一部分低（就是中间有交点），再分类讨论：

新线段在左子树区间内完全高于老的，替换左边，把老的递归到右边；
 
新线段在左子树区间内完全低于老的，把新的递归到右边；
 
新线段在右子树区间内完全高于老的，替换右边，把老的递归到左边；
 
新线段在右子树区间内完全低于老的，把新的递归到左边。
#### 查询：

因为是单点查询，依次缩小点所在的区间，用 $y=kx+b$ 计算出所有经过的区间中纵坐标最大值即可。

#### 本题注意事项：

手写快读；

输入的 $s$ 是第一天收益 $b$ 需要自己算；

没有方案输 $0$；

精确到整百元，即除以 $100$ 化成整数；

线段树开四倍空间。

#### AC代码（加注释）：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>

#define maxn 500005

using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int n;

struct Tree{
	int l,r;
	double k,b; //k,b开double
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define k(p) tree[p].k
	#define b(p) tree[p].b
	#define ls p<<1
	#define rs p<<1|1
}tree[maxn<<2];

inline void build(int p,int l,int r)
{
	l(p)=l,r(p)=r;
	if(l==r){
		k(p)=b(p)=0;
		return ;
	}
	int mid=l(p)+r(p)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}

inline void up(int p,double k,double b)
{
	k(p)=k,b(p)=b;
}

inline void change(int p,int l,int r,double k,double b)
{
	int mid=l(p)+r(p)>>1;
	if(l<=l(p)&&r>=r(p)){
		double x0=l(p),x1=r(p);
		double y0p=k(p)*x0+b(p),y1p=k(p)*x1+b(p);
		double y0=k*x0+b,y1=k*x1+b;
		if(y0>=y0p&&y1>=y1p) up(p,k,b);//新线段完全高于老线段
		else if(y0<=y0p&&y1<=y1p) return ;//新线段完全低于老线段
		else{
			double mid=(x0+x1)/2.0,jiao=(b-b(p))/(k(p)-k);
			if(y0>y0p){
				if(jiao<=mid) change(ls,l,r,k,b);//在右子树区间内完全低于老的
				else change(rs,l,r,k(p),b(p)),up(p,k,b);//在左子树区间内完全高于老的
			}
			else{
				if(jiao<=mid) change(ls,l,r,k(p),b(p)),up(p,k,b);//在右子树区间内完全高于老的
				else change(rs,l,r,k,b);//在左子树区间内完全低于老的
			}
		}
		return ;
	}
	if(l<=mid) change(ls,l,r,k,b);
	if(r>mid) change(rs,l,r,k,b);
}

inline double ask(int p,int x,double ans)
{
	ans=max(ans,k(p)*(1.0*x)+b(p));//纵坐标最大值
	if(l(p)==r(p)) return ans;
	int mid=l(p)+r(p)>>1;
	if(x<=mid) return ask(ls,x,ans);
	else return ask(rs,x,ans);
}

int main()
{
	n=read();
	build(1,1,50000);
	while(n--){
		string opt;
		cin>>opt;
		if(opt=="Query"){
			int t;
			t=read();
			printf("%d\n",(int)(ask(1,t,0)/100.0));//化成百元
		}
		else{
			double s,k,b;
			scanf("%lf %lf",&s,&k);
			b=s-k;//手算b
			change(1,1,50000,k,b);
		}
	}
	return 0;
}
```

---

## 作者：Always (赞：5)

才一篇题解  感觉看了不是很懂 ！ 我来一发！
### 题目大意:
动态给多条直线方程y = kx + b; 求当x的值被给出时哪根直线上的函数值大
### 其实是个裸题 (超哥线段树[传送门^_^](https://www.cnblogs.com/zwfymqz/p/7305682.html))
那谈谈我的理解:

首先是用线段树来维护 对吧! 

那我们用一个 _tree[]_ 数组来维护题目中给出的直线(b[],k[]对应一次函数的纵截距 和 斜率) 我们考虑一下 对于每个一次方程 它要接近最优解 那 **斜率**应该大

但对于一条直线来说 他的斜率大 对应的函数值有可能不及比他斜率小的 直线对应的函数值大 (可以自己画画图看看)

那我们除了考虑斜率之外 还应考虑他们交点在何处 

经过...(自行领会= =) 我们通过比较两者的**当前区间中点值和斜率** 来确定他应该替代原来位置的(tree[id])还是该继续递归下去 ! 

## 我们再来看看这些操作具体应该如何实现?

### 如何加一条线段

• 把输入线段砍成长为2的幂次的小区间，放到线
段树对应位置上

• 对于每个小区间：

• 如果一条线段碾压另一条，则将高的那条记录在
当前区间上，结束递归

• 如果新线段的中点比原线段的中点高，则用新线
段替代原线段，并将原线段较高的半边继续下放

• 如果新线段的中点比原线段的中点低，则将新线
段较高的半边继续下放

### 如何查询x=k上最高的线段

• 对于线段树上覆盖了点x=k的区间（共logn）个，
询问每个区间上记录的线段在x=k处的高度，取
最大值输出

### 复杂度 : 
• 插入O(log2n)

• 询问O(logn)


------------

代码:
```cpp
#include<bits/stdc++.h>
#define M 500005
//这里说一下 我也不知道 为什么M 500000 + 5 的时候 全是RE 只有 M 500005 的时候才能A
//(可以自己试试 - -)  有知道的可以跟我说 
using namespace std;
int n , m , tree[M * 4];//m 是当前线段总数 (也是最后一条线段的编号)
//声明 ！！！！ tree[] 里存的是当前节点 的某条线段的编号 
double k[M * 2] , b[M * 2];
//y = kx + b  对应斜率 和 纵截据 
char op[20];
double f(int w , int x){//计算对应函数 x对应y的值 <=> f(x) = kx + b
	return k[w] * (x - 1) + b[w];
}
void up(int id ,int l , int r ,int x){
	if(l == r){//如果到了叶子节点 
		if(f(x , l) > f(tree[id] , l)) tree[id] = x ;//考虑两者的函数值 
		//如果x比tree[id]还大 更换掉就行了 
		return ;
	}
	int mid = l + r >> 1 ;
	if(k[tree[id]] < k[x]){//比较斜率 
		if(f(x , mid) > f(tree[id] , mid)){//比较此时的中点 
			up(id * 2 , l , mid , tree[id]) ; tree[id] = x;
			//如果 x 这条线段的中点函数值 比当前tree[mid] 这条线段的...大
			//那就替换掉(在那之前先把tree[id] 递归下去 不然会导致线段丢失) 
		}
		else up(id * 2 + 1 , mid + 1 , r , x);//否则直接把x 递归下去就可以了 
	}
	if(k[tree[id]] > k[x]){//道理都和上面差不多 就不说了 
		if(f(x , mid) > f(tree[id] , mid)){
			up(id * 2 + 1 , mid + 1 , r , tree[id]); tree[id] = x ;
		}
		else up(id * 2 , l , mid , x) ;
	}
}
double query(int id , int l ,int r ,int x){
	if(l == r) return f(tree[id] , x);//已经到了叶子节点 
	int mid = l + r >> 1;
	if(x <= mid){//左子树 
		return max(f(tree[id] , x) , query(id * 2 , l , mid , x));
	}
	else return max(f(tree[id] , x) , query(id * 2 + 1 , mid + 1 , r , x));
	//右子树 
}
int main(){
	scanf("%d",&n);
	while(n --){
		scanf("%s",op);
		if(op[0] == 'P'){ 
		    m ++;//新的线段加入 
			scanf("%lf%lf",&b[m],&k[m]) ;
			up(1 , 1 , M , m);
		}
		else{ int x ;
			scanf("%d",&x);
		//	printf("%.6lf\n", query(1 , 1 , M , x));不要求输出这个 好扯淡= =
		    printf("%d\n",(int) (query(1 , 1 , M , x) / 100)) ;
		}
	}
	return 0;
}
```

---

## 作者：Prean (赞：4)

李超树板子。。。

题意简明，不说了。

我们可以把每个顾问看成一个一次函数，其中第一天的收益为 $ b $，每天增加的收益为 $ k $。

于是就愉快的过掉了。。。
```cpp
#include<cstdio>
typedef double db;
const int M=5e4+5;
int n;char s[15];
struct line{
	db k,b;
	line(const db&k=0,const db&b=0):b(b),k(k){}
	inline db calc(const int&x)const{
		return b+k*x;
	}
	inline bool empty()const{
		return !k&&!b;
	}
}t[M<<2];
inline void swap(line&a,line&b){
	line c=a;a=b;b=c;
}
inline db max(const db&a,const db&b){
	return a>b?a:b;
}
void pushdown(int u,int L,int R,line lie){
	int mid=L+R>>1;
	if(t[u].empty())t[u]=lie;
	else{
		if(lie.calc(mid)>t[u].calc(mid))swap(lie,t[u]);
		if(lie.calc(L)>t[u].calc(L))pushdown(u<<1,L,mid,lie);
		else if(lie.calc(R)>t[u].calc(R))pushdown(u<<1|1,mid+1,R,lie);
	}
}
db Query(int u,int x,int L,int R){
	if(L==R)return t[u].calc(x);
	int mid=L+R>>1;
	if(x<=mid)return max(Query(u<<1,x,L,mid),t[u].calc(x));
	else return max(Query(u<<1|1,x,mid+1,R),t[u].calc(x)); 
}
signed main(){
	register int i,x;register db k,b;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		scanf("%s",s);
		if(s[0]=='P'){
			scanf(" %lf%lf",&b,&k);
			pushdown(1,1,5e4,line(k,b-k));
		}
		else{
			scanf("%d",&x);
			printf("%d\n",int(Query(1,x,1,5e4)/100));
		}
	}
}
```

---

## 作者：BeyondStars (赞：3)

其实不需要什么李超线段树~~太菜了不会~~，暴力就可以过。对于线段树每个节点，维护一个最大值和最小值。查询的时候直接查，修改的时候就判断新函数在此区间内的最大值是否小于区间内当前的最小值，如果小于，那么直接返回，否则暴力修改。复杂度 $ O(测评机快可以过) $。bzoj和luogu都过了。。。。可能是数据比较水吧！
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int MAXT = 50010;
const int T = 50000;
struct node{double mn,mx;}tree[MAXT<<2];
void pushup(int k){tree[k].mn = min(tree[k<<1].mn,tree[k<<1|1].mn);tree[k].mx = max(tree[k<<1].mx,tree[k<<1|1].mx);}
void modify(int k,int l,int r,double first,double p){
    if(l==r){	
        tree[k].mn = tree[k].mx = max(tree[k].mx,first+p*double(r-1));
        return;
    }
    if(tree[k].mn>first+p*double(r-1))return;
    int mid = l+r>>1;
    modify(k<<1,l,mid,first,p);modify(k<<1|1,mid+1,r,first,p);
    pushup(k);
}
double query(int k,int l,int r,int pos){
    if(l==r){return tree[k].mx;}
    int mid = l+r>>1;
    if(pos<=mid)return query(k<<1,l,mid,pos);
    else return query(k<<1|1,mid+1,r,pos);
}
int main(){
    int n;scanf("%d",&n);
    char c[20];
    double S,P;
    int D;
    while(n--){
        scanf("%s",c);
        if(c[0]=='P'){
            scanf("%lf%lf",&S,&P);
            modify(1,1,T,S,P);
        }else{
            scanf("%d",&D);
            printf("%d\n",((int)(query(1,1,T,D)))/100);
        }
    }
}
```

---

## 作者：TheShadow (赞：2)

---
title: P4254 [JSOI2008]Blue Mary开公司
---



# 闲扯

出了一个玄学问题，结果 $JKLover$ 帮我找了半天的错。。

# 题面

[P4254 [JSOI2008]Blue Mary开公司](https://www.luogu.org/problem/P4254)

# Solution

考虑李超线段树。

对于线段树的每一个区间，我们记录该区间的优势线段。

**$ps:$ 优势线段是指在该区间内满足所有线段都不超过它的线段**

对于插入线段，我们进行如下讨论：

1. 若该区间还没有优势线段，将其修改为当前线段，然后直接返回。
2. 若该区间的优势线段被当前线段完全盖过，将其修改为当前线段，然后直接返回。
3. 若该区间的优势线段将当前线段完全盖过，直接返回。
4. 否则递归进入左右区间。

但是需要注意的是，我们使用了**标记永久化**的方式，即我们不用上传懒标记。在每一次查询的时候，我们一次遍历所有包含 $pos$ 的区间，然后求出其中的最大值（或者最小值）最为最后的答案。

这道题里面需要注意的是：我们已知的是**第一天**的收益，和随后的增长，所以计算的时候要将 $S$ 减去一个 $P$ 才是我们真正要求的 $k,b$ 。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x) {
	int f=1;
	char k=getchar();
	x=0;
	for(; k>'9'||k<'0'; k=getchar()) if(k=='-') f=-1;
	for(; k>='0'&&k<='9'; k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il print(T x) {
	if(x/10) print(x/10);
	putchar(x%10+'0');
}
ll mul(ll a,ll b,ll mod) {
	long double c=1.;
	return (a*b-(ll)(c*a*b/mod)*mod)%mod;
}
it qpow(int x,int m,int mod) {
	int res=1,bas=x%mod;
	while(m) {
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 1e5+5,MAXM = 5e4+5;
int n,k,cnt,T[MAXM<<2];
double vl,vr,cl,cr;
char opt[10];
struct Node {
	double k,b;
} node[MAXN];
#define lc (cur<<1)
#define rc (cur<<1|1)
double calc(int x,int id){return node[id].k*x+node[id].b;}
il insert(int cur,int l,int r,int k){
	vl=calc(l,k),vr=calc(r,k),cl=calc(l,T[cur]),cr=calc(r,T[cur]);
	if(!T[cur]||(vl>=cl&&vr>=cr)){T[cur]=k;return ;}
	if(vl<=cl&&vr<=cr) return ;
	insert(lc,l,mid,k),insert(rc,mid+1,r,k);
}
inl double query(int cur,int l,int r,int pos){
	if(l==r) return calc(pos,T[cur]);
	double res=calc(pos,T[cur]);
	if(mid>=pos) return max(res,query(lc,l,mid,pos));
	else return max(res,query(rc,mid+1,r,pos));
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(ri i=1; i<=n; ++i){
		scanf("%s",opt);
		if(opt[0]=='Q')	read(k),printf("%d\n",(int)(query(1,1,MAXM,k)/100));
		if(opt[0]=='P') scanf("%lf%lf",&node[cnt].b,&node[++cnt].k),node[cnt].b-=node[cnt].k,insert(1,1,MAXM,cnt);
	}
	return 0;
}
```

# 总结

$scanf$ 传入参数的时候是从后往前传的，如果用 $++cnt$ 的写法，要加在最后面。

---

## 作者：半仙胡小桃 (赞：2)

## 题目描述：
有两个操作
Project b k 表示 第一天有 b 的收益 以后每天增加 k 的收益
Query x 表示 查询 第 x 天的最大收益是多少
## 题目分析：
对于每个计划 第X天的收益可以表示为 P(i)=k*(i-1)+b
形式为一个一次函数
题目可表示为维护每个点上覆盖本点1次函数的最大值是多少
如何维护一条线段上的一次函数？
用超哥线段树啊(雾
[![CQJZy.md.png](https://s1.ax2x.com/2018/03/08/CQJZy.md.png)](https://simimg.com/i/CQJZy)
##题目链接:
[Luogu 4254](https://www.luogu.org/problemnew/show/P4254)
[BZOJ 1568](http://www.lydsy.com/JudgeOnline/problem.php?id=1568)
## Ac 代码:
```
#include <cstdio>
#include <iostream>
const int maxm=500003;
double b[maxm*2],k[maxm*2];
int st[maxm*4],cnt;
inline bool pd(int x,int y,int pos) {return b[x]+(pos-1)*k[x]>b[y]+(pos-1)*k[y];}
inline double getans(int x,int pos) {return b[x]+(pos-1)*k[x];}
double d[]={0,1e-1,1e-2,1e-3,1e-4,1e-5,1e-6,1e-7,1e-8,1e-9,1e-10};
double read()
{
	int x=0,w=1,now=0,f=0;
	double xs=0;
	char ch=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') w=-1; 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'||(ch=='.'))
	{
		if(ch=='.')
		{
			f=1;
			ch=getchar();
			continue; 
		} 
		if(f) xs+=(((ch-'0')*d[++now]));
		else x=((x<<3)+(x<<1)+ch-'0');
		ch=getchar();
	}
	xs+=(double)x;
	return xs*w;
}
void insert(int o,int l,int r,int now)
{
    //printf("%d %d %d\n",o,l,r);
    if(l>=r)
    {
        if(pd(now,st[o],l)) st[o]=now;
        return;
    }
    int mid=(l+r)>>1;
    if(k[now]>k[st[o]])
    {
        if(pd(now,st[o],mid))
        insert((o<<1),l,mid,st[o]),st[o]=now;
         else insert((o<<1)|1,mid+1,r,now);
    }
    if(k[now]<k[st[o]])
    {
      if(pd(now,st[o],mid))
       insert((o<<1)|1,mid+1,r,st[o]),st[o]=now;
      else insert((o<<1),l,mid,now);
    }
}
double ask(int o,int l,int r,int ind)
{
    if(l>=r) return getans(st[o],ind);
    int mid=(l+r)>>1;
    double ans=getans(st[o],ind);
    if(ind<=mid) return std::max(ans,ask((o<<1),l,mid,ind));
    else return std::max(ans,ask((o<<1)|1,mid+1,r,ind));
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        char s[20];
        scanf("%s",s);
        if(s[0]=='P')
        {
            cnt++;
            b[cnt]=read(),k[cnt]=read();
            insert(1,1,maxm,cnt);
        }
        else
        {
            int d;
            scanf("%d",&d);
            printf("%d\n",(int)ask(1,1,maxm,d)/100);
        }
    }
    return 0;
}
```

---

## 作者：JK_LOVER (赞：1)

## 写在前面
如果格式炸了，请前往这里 [$QwQ$](https://www.luogu.com.cn/blog/xzc/solution-p4254)
。
## 李超线段树
## 引入
查询在平面直角坐标系中与直线 $x=x_0$ 的相交的最大 (最小) 值。换而言之就是查询 $\max (k_ix_0+b_i)$ 的值。
## 实现
我们发现当我们插入一条线段时，我们只会在直线交点中修改 。所以我们将问题转化为 $\text{找到每条直线的交点，并修改}$ 。可以发现这其实就是一个凸壳，这也是李超线段树可以维护并优化一些   $dp$ 方程的原因。我们考虑用线段树来维护每个区间的最大值。
### 插入
我们发现每次找到一个交点我们就修改它，那么我们还要递归它的儿子，所以每次都是 $O(n)$ ，那么复杂度是不可以接受的。我可以借鉴最短路的 $heap$ 的延迟删除，我们只是将这条线段放在下一层。并不删除它。这里放两种插入方法。

$I:$
```cpp
 
int change(int u,int pre,int l,int r,int now)
{
	if(!u) u = ++tot;
	int mid = l+r>>1;	
	if(!pre)
	{
		t[u] = now;
		return u;
	}
	if(l == r) 
	{
		if(f(l,seg[pre].k,seg[pre].b) <= f(l,seg[now].k,seg[now].b))
		t[u] = now;
		return u;
	}
	double val_mid = f(mid,seg[now].k,seg[now].b);
	double val_Mid = f(mid,seg[pre].k,seg[pre].b);
	if(val_mid >= val_Mid)
	{
		if(seg[now].k >= seg[pre].k) 
		{
			t[u] = now;
			lc[u] = change(lc[u],t[lc[u]],l,mid,pre);
			return u;
		}
		else 
		{
			t[u] = now;
			rc[u] = change(rc[u],t[rc[u]],mid+1,r,pre);
			return u;
		}
	}
	else 
	{
		if(seg[now].k >= seg[pre].k) 
		{
			rc[u] = change(rc[u],t[rc[u]],mid+1,r,now);
			return u;
		}
		else 
		{
			lc[u] = change(lc[u],t[lc[u]],l,mid,now);
			return u;
		}
	}
	return u;
}

```
以上代码的时间复杂度十分清晰，我们只递归了一边那么复杂度是由树高决定的，为 $O(\log n)$ 。其思想，总结如下：

- 如果插入的线段的中值大：如果插入的线段斜率大，则交点出现在左侧，向左递归；反之向交点在右侧，因为我们 **覆盖** 了这个节点的线段，所以传的参数应该是原线段。

- 如果插入的线段的中值小：如果插入的线段斜率大，则交点出现在右侧，向右递归；反之向交点在左侧，因为我们 **没有覆盖** 了这个节点的线段，所以传的参数应该是插入线段。

- 用图例说明：红色为插入线段，黑色为原先线段。

![](https://cdn.luogu.com.cn/upload/image_hosting/h8eii4et.png)
$II:$


```cpp
int insert(int u,int pre,int l,int r,int now)
{
	if(!u) u = ++tot; 
	double val_l = f(l,seg[now].k,seg[now].b);double val_r = f(r,seg[now].k,seg[now].b);
	double val_L = f(l,seg[pre].k,seg[pre].b);double val_R = f(r,seg[pre].k,seg[pre].b);
	if(!pre||(val_r>=val_R&&val_l>=val_L)) 
	{t[u] = now;return u;}
	if(val_R>=val_r&&val_L>=val_l)
	{return u;}
	int mid = l+r>>1;
	lc[u] = insert(lc[u],t[lc[u]],l,mid,now);
	rc[u] = insert(rc[u],t[rc[u]],mid+1,r,now);
	return u;
}
```

这种方法是来自大佬 @TheShadow 的方法。时间复杂度是等同于单点查询的。虽然我们两边都递归了，但两条直线最多只有 **一个** 交点。所以复杂度还是 $O(\log n)$ 。其思想是利用函数的单调性，如果左右端点的值都大(小) ，那么这条直线肯定就没有贡献了，则可以 $return$ 。

### 查询
因为我们是没有完全删去一条线段的，所以每一条覆盖了这个点的线段都要计算 $f(x_0)$ 。
```cpp
double query(int u,int l,int r,int p)
{
	if(l==r) return f(l,seg[t[u]].k,seg[t[u]].b);
	double ans = f(p,seg[t[u]].k,seg[t[u]].b);
	int mid = l+r>>1;
	if(p <= mid) return max(ans,query(lc[u],l,mid,p));
	else return max(ans,query(rc[u],mid+1,r,p));
}

```
### 总结
李超线段树是一种码量不大的的数据结构，在很多时候用来维护凸壳是十分优秀的工具。
## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f?-x:x;
}

const int maxn = 1e6+10;
const int Maxn = 4e6+10;
int tot=0,root,t[Maxn],lc[Maxn],rc[Maxn];
struct node{double k,b;}seg[Maxn];

double f(int x,double k,double b){return k*x+b;}

int insert(int u,int pre,int l,int r,int now)
{
	if(!u) u = ++tot; 
	double val_l = f(l,seg[now].k,seg[now].b);double val_r = f(r,seg[now].k,seg[now].b);
	double val_L = f(l,seg[pre].k,seg[pre].b);double val_R = f(r,seg[pre].k,seg[pre].b);
	if(!pre||(val_r>=val_R&&val_l>=val_L)) 
	{t[u] = now;return u;}
	if(val_R>=val_r&&val_L>=val_l)
	{return u;}
	int mid = l+r>>1;
	lc[u] = insert(lc[u],t[lc[u]],l,mid,now);
	rc[u] = insert(rc[u],t[rc[u]],mid+1,r,now);
	return u;
}
 
int change(int u,int pre,int l,int r,int now)
{
	if(!u) u = ++tot;
	int mid = l+r>>1;	
	if(!pre)
	{
		t[u] = now;
		return u;
	}
	if(l == r) 
	{
		if(f(l,seg[pre].k,seg[pre].b) <= f(l,seg[now].k,seg[now].b))
		t[u] = now;
		return u;
	}
	double val_mid = f(mid,seg[now].k,seg[now].b);
	double val_Mid = f(mid,seg[pre].k,seg[pre].b);
	if(val_mid >= val_Mid)
	{
		if(seg[now].k >= seg[pre].k) 
		{
			t[u] = now;
			lc[u] = change(lc[u],t[lc[u]],l,mid,pre);
			return u;
		}
		else 
		{
			t[u] = now;
			rc[u] = change(rc[u],t[rc[u]],mid+1,r,pre);
			return u;
		}
	}
	else 
	{
		if(seg[now].k >= seg[pre].k) 
		{
			rc[u] = change(rc[u],t[rc[u]],mid+1,r,now);
			return u;
		}
		else 
		{
			lc[u] = change(lc[u],t[lc[u]],l,mid,now);
			return u;
		}
	}
	return u;
}

double query(int u,int l,int r,int p)
{
	if(l==r) return f(l,seg[t[u]].k,seg[t[u]].b);
	double ans = f(p,seg[t[u]].k,seg[t[u]].b);
	int mid = l+r>>1;
	if(p <= mid) return max(ans,query(lc[u],l,mid,p));
	else return max(ans,query(rc[u],mid+1,r,p));
}

int cnt = 0;

int main()
{
	int n = read();
	for(int i = 1;i <= n;i++)
	{
		char s[100];
		cin>>s;
		if(s[0] == 'Q') {
			int p=read();
			printf("%d\n",(int)(query(root,1,maxn,p)/100));
		}
		if(s[0] == 'P')
		{
			++cnt;
			cin>>seg[cnt].b>>seg[cnt].k;
			seg[cnt].b -= seg[cnt].k;
			//root = insert(root,t[root],1,maxn,cnt);
			root = change(root,t[root],1,maxn,cnt);
		}
	}
}
```

 

---

