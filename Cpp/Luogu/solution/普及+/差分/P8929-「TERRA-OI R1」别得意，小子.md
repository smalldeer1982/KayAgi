# 「TERRA-OI R1」别得意，小子

## 题目背景

战至中途，蓝紫色天空瞬间变为黑压压一片，噬神者身上一些紫色外壳开始脱落，化为更小的蟒蛇，这些小家伙从出现开始便不要命的向你冲过来，刚清理掉这些小家伙，迷雾中忽然涌现出一张血盆大口，噬神者正向你冲击而来......

## 题目描述

现给定一个有 $n$ 段的分段函数，每一段可能是一个一次函数或者一个二次函数，并有 $q$ 次询问，每次询问 $x=k$ 时 $y$ 的取值或是 $y=k$ 与函数有多少个交点。



## 说明/提示

#### 【样例解释 #1】

三段函数分别为 $y=x+2$，$y=x^2-2x+1$，$y=x$。

对于当 $x=4$ 时套入第二段函数可以得到结果为 $9$。

而直线 $y=5$ 只与第一段与第二段函数相交，并且各只有一个交点，所以结果为 $2$。

显而易见，第三个询问对应的直线不与函数相交。

第四个询问虽然与第一段函数交于 $x=0$ 的位置，但 $0$ 不在该函数区间内，故舍去。

------------

#### 【数据范围】

**本题采用捆绑测试。**

| Subtask | Score | $n,q\le$ | limit |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10$ | $100$ | 无 |
| $2$ | $15$ | $10^3$ | $r_n\le 5\times 10^3$ |
| $3$ | $20$ | $2\times 10^5$ | 不存在询问 $2$ |
| $4$ | $25$ | $2\times 10^5$ | 不存在二次函数 |
| $5$ | $30$ | $2\times 10^5$ | 无 |

对于 $100\%$ 的数据，$1\le n,q\le 2\times 10^5$，$0\le l_i,r_i\le10^9$，$\forall i\in [1,n],r_i>l_i$ 。

所有的函数系数均在 **$64$ 位有符号整型变量**存储范围内，并且运算结果与每个函数式中任何一项的最大值与最小值不会超过 **$64$ 位有符号整型变量**存储范围。所有询问参数均在 **$32$ 位有符号整型变量**范围内。

（即 $-4\times 10^{18}\le k,a,b,c\le 4\times 10^{18}$，$-10^9\le x\le 10^9$）

------------
#### 【提示】

采用浮点数据时建议使用 long double，避免产生精度问题。

upd：添加一组 hack 数据，未通过会显示为“Unaccepted 100pts”。

## 样例 #1

### 输入

```
3 4
0 3 1 1 2
3 6 2 1 -2 1
6 10 1 1 0
1 4
2 5
2 114514
2 2```

### 输出

```
9
2
0
0```

## 样例 #2

### 输入

```
6 8
0 4 2 1 -4 0 
4 6 1 2 -10 
6 11 1 1 -19 
11 19 2 -1 -30 559 
19 29 1 1 -58 
29 38 1 1 -68 
1 11
2 4
2 -1
1 21
2 -5
2 2
1 34
2 1
```

### 输出

```
-8
1
4
-37
1
2
-34
2
```

# 题解

## 作者：MCRS_lizi (赞：6)

~~自己给自己出毒瘤题，自己挖的坑花了三四天才填上（悲）~~

前置知识：[二分查找](https://oi-wiki.org/basic/binary/)，[差分](https://oi-wiki.org/basic/prefix-sum/)，以及一些[STL的的小工具](https://oi-wiki.org/lang/csl/associative-container/)。

题目意思应该讲的还算明白，就直接来讲思路了。

第一个询问很简单，我们只需要二分查找对应区间，再把值代进去计算即可，这里不过多赘述，有问题可以去看代码。

难在第二个询问，由于询问的值最大可能在 $10^9$，并且与函数交点还不一定是个整点，导致处理非常棘手。

这个时候，我们发现，如果函数的值域是一段连续，单调的区间，我们便可以拿出大法宝------差分。只需要在这段的头尾打标记即可。但是 longlong 范围的值域使得正常的差分根本行不通，即使将区间限定在询问对应的区间也不是内存和时间所允许的。

但是这道题目一共就 $2\times 10^5$ 个函数，打的标记数量是十分有限的，意思上如果用朴素的差分，中间会有大量相同且无意义的元素。

这就是说，我们维护的差分数组仅需存储要打标记的点，而其他元素的询问只需要二分查找就可以实现，而这时我们就可以用到一个非常方便的小玩意------ ```map```。

之后就是打标记的问题了。

一次函数很简单，头尾打一下标记就可以了。恶心就在二次函数，我们需要将其按对称轴拆分成两段连续区间打标记，但是二次函数顶点不一定是整点，这就需要一些精密的思考，巧妙的运算，浮点数的熟练应用和恶心至极的分类讨论（这就是困扰我三四天的部分）。

总之大体思路就是这样，具体可以看一下代码和注释，时间复杂度 $O(n\log n)$。

**CODE:**

```cpp
#include<bits/stdc++.h>
#define int long long//不开 longlong 见祖宗
using namespace std;
const int N=200010;
const double e=1e-9;//浮点数必备的精度控制
int n,q,val[N<<2],num[N<<2],tot,cnt;
map<int,int> p,used;
struct fun
{
	int l,r,op,a,b,c;
}a[N];
inline int f(register int p,register int x)//求取函数值
{
	if(a[p].op==1)
	{
		return a[p].a*x+a[p].b;
	}
	else
	{
		return a[p].a*x*x+a[p].b*x+a[p].c;
	}
}
inline int query1(register int x)//直接二分查找对应区间
{
	register int l=1,r=n,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(a[mid].l>=x)
		{
			r=mid-1;
		}
		else if(a[mid].r<x)
		{
			l=mid+1;
		}
		else
		{
			break;
		}
	}
	return f(mid,x);
}
inline void upd(register int x,register int tp)//打标记函数
{
	if(!used[x])
	{
		used[x]=1;
		val[++tot]=x;
	}
	p[x]+=tp;
}
inline void line(register int ll,register int rr,register int x)//给一段连续函数区间打标记的
{
	register int l=f(x,ll),r=f(x,rr);
	if(l>r)
	{
		l--;
		swap(l,r);
	}
	else
	{
		l++;
	}
	upd(l,1),upd(r+1,-1);
}
inline void tag(register int x)//给第x个函数打标记
{
	register int aa=a[x].a,bb=a[x].b,cc=a[x].c;
	if(a[x].op==1)
	{
		line(a[x].l,a[x].r,x);//一次函数直接打
	}
	else
	{
		long double mid=-1.0*bb/(2*aa);//对称轴
		register int top=ceil(a[x].a*mid*mid+a[x].b*mid+a[x].c);//顶点向上取整
		if(mid<=a[x].l||mid-e>a[x].r||bb%(2*aa)==0&&-bb/(2*aa)==a[x].l)//如过对称轴不在区间内，视作一次函数处理。
		{
			line(a[x].l,a[x].r,x);
		}
		else if(top<=f(x,a[x].l)&&aa<0||top>=f(x,a[x].l)&&aa>0)//如果顶点与左端点为同一级别，特殊处理
		{
			if(aa<0)
			{
				upd(f(x,a[x].r),1),upd(top,-1);
			}
			else
			{
				upd(f(x,a[x].r)+1,-1),upd(top,1);
			}
		}
		else
		{
			
			if(aa<0)//开口向下
			{
				int tp=-2;
				if(fabs(a[x].a*mid*mid+a[x].b*mid+a[x].c-(long double)top)<=e)//这个很关键，如果顶点是整点那么交在这里只有一个交点而不是两个
				{
					upd(top+1,-1);
					tp++;
				}
				upd(top,tp),upd(f(x,a[x].l)+1,1),upd(f(x,a[x].r),1);
			}
			else//开口向上
			{
				int tp=2;
				if(fabs(a[x].a*mid*mid+a[x].b*mid+a[x].c-(long double)top)<=e)//和上面一样
				{
					upd(top+1,1);
					tp--;
				}
				upd(top,tp),upd(f(x,a[x].l),-1),upd(f(x,a[x].r)+1,-1);
			}
		}
	}
}
inline int query2(register int x)//求取交点数
{
	return num[upper_bound(val+1,val+tot+2,x)-val-1];//STL真好用
}
signed main()
{
	scanf("%lld%lld",&n,&q);
	for(register int i=1;i<=n;i++)
	{ 
    	scanf("%lld%lld%lld%lld%lld",&a[i].l,&a[i].r,&a[i].op,&a[i].a,&a[i].b);
		if(a[i].op==2)
		{
			scanf("%lld",&a[i].c);
		}
		tag(i);
	}
	sort(val+1,val+tot+1);//排序方便二分
	val[tot+1]=1e18;//这个很关键，不加的话upper_bound有时会找不到结果。
	for(register int i=1;i<=tot;i++)
	{
		num[i]=p[val[i]]+num[i-1];//还原差分数组
	}
	while(q--)
	{
		register int op,x;
		scanf("%lld%lld",&op,&x);
		if(op==1)
		{
			printf("%lld\n",query1(x));
		}
		else
		{
			printf("%lld\n",query2(x));
		}
	}
 	return 0;
}//抄袭题解是不好的习惯哦
```



---

## 作者：kbtyyds (赞：2)

# P8929 题解

建议在[博客](https://www.luogu.com.cn/blog/453059/solution-p8929)里食用：

[题目链接](https://www.luogu.com.cn/problem/P8929)

--- 

## 题目描述

现给定一个有 $n$ 段的分段函数，每一段可能是一个一次函数或者一个二次函数，并有 $q$ 次询问，每次询问 $x=k$ 时 $y$ 的取值或是 $y=k$ 与函数有多少个交点。

## 分析

首先我们要用结构体储存各个函数，信息包括 $l,r,a,b,c,k,ty$ 即区间端点，函数系数，函数种类。

对于操作 1,2 ，将在下面分别处理。

## 操作 $1$

题目给定的区间都是连续的，又保证 $k\in(0,r_n]$，则我们可以通过二分求出 $k$ 所在的函数区间，并代入计算即可。

代码如下：

```cpp
inline int find(int k)// 二分查找函数
{
    int l=1,r=n;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(k>f[mid].r) l=mid+1;//与当前右端点判断，当然左端点也可以（有点细节的差别）
        else r=mid;
    }
    return l;
}
```

然后在结构体内部实现一个计算函数：

```cpp
struct func
{
    int l,r,ty,a,b,c,k;
    // ... something ...
    inline int calc(int x)
    {
        if(ty==1) return k*x+b;
        return a*x*x+b*x+c;
    }
    // ... something ...
}f[S];
```

操作 1 就搞定啦！

## 操作 $2$

### 2.1 仅有一次函数

由于一次函数中 $k\ne 0$，所以在区间 $(l_i,r_i]$ 的值域也为一个区间，于是这个问题就转化为了：

> 给定 $n$ 个区间，每次查询一个 $y$，输出有多少个区间覆盖了 $y$ 这个点。

显然一个差分就可以解决。

但是？我们发现这个函数值域不是我们可以简单储存然后差分的，因此我们要离散化！

对 $k$ 的正负简单分类讨论一下端点即可。

注意一下左开右闭区间的取值问题。

部分代码如下：

```cpp
struct sec// 区间结构体
{
    int l,r;
}p[S<<1];
struct func
{
    int l,r,ty,a,b,c,k;
    // ... something ...
    inline void solve()
    {
        if(ty==1)
        {
            int tl,tr;
            if(k>0) tl=calc(l)+1,tr=calc(r);
            // calc(l) 由于左边的开区间取不到，要 +1
            else tl=calc(r),tr=calc(l)-1;
            // 同理，作为值域区间右端点要 -1
            len++,p[len].l=tl,p[len].r=tr;
        }
        // ... something ...
    }
}f[S];
int tmp[S<<3],tlen,cf[S<<3];
inline void solve()
{
    for(int i=1;i<=len;i++)
    {
        tmp[++tlen]=p[i].l-1,tmp[++tlen]=p[i].l;
        tmp[++tlen]=p[i].r,tmp[++tlen]=p[i].r+1;
    }// 储存区间为了确保连续要多存
    sort(tmp+1,tmp+tlen+1);
    tlen=unique(tmp+1,tmp+tlen+1)-tmp-1;
    for(int i=1;i<=len;i++)
    {
        int L=lower_bound(tmp+1,tmp+tlen+1,p[i].l)-tmp;
        int R=lower_bound(tmp+1,tmp+tlen+1,p[i].r)-tmp;
        cf[L]++,cf[R+1]--;// 差分
    }//sort+unique+lower_bound 离散化三连
    for(int i=1;i<=tlen;i++) cf[i]+=cf[i-1];// 对差分求前缀和以还原数组
}
```

那么我们就完成了一次函数部分！

### 2.2 二次函数

~~最恶心的地方来了。~~

大家可以回忆起九年级的二次函数分类讨论，首先我们要考虑对称轴。

先把二次函数的简单变形弄一下：

$$\boxed{ax^2+bx+c=a\left(x+\dfrac b {2a}\right)^2+\dfrac {4ac-b^2} {4a}}$$

那么对称轴 $\mathrm{line}=-\dfrac b {2a}$，顶点纵坐标 $\mathrm{top}=\dfrac {4ac-b^2} {4a}$

#### 2.2.1 $\mathrm{line}\in(l_i,r_i]$

此时的函数的值域就与一次函数有区别了，等价于两个区间，得要分两段：$x\in(l_i,\mathrm{line}]$ 以及 $x\in(\mathrm{line},r_i]$ 部分，故仍需要再次对 $a$ 的正负分类讨论。

##### 2.2.1.1 $a>0$

画出大致的函数图像：

![](https://cdn.luogu.com.cn/upload/image_hosting/zxorh8yw.png)

很明显地，这段二次函数可以被拆成 $AP,BP$ 两段，值域分别为 $[\mathrm{top},f(l))$ 及 $(\mathrm{top},f(r)]$

##### 2.2.1.2 $a<0$

和 2.2.1.1 差不多的思想，不再重复。

只给出分拆的区间：$(f(l),\mathrm{top}]$ 及 $[f(r),\mathrm{top})$

#### 2.2.2 $\mathrm{line}\notin(l_i,r_i]$

显然此时只能等价于一个区间。

为分类方便，直接分递增与递减讨论。

- 递增：$(a>0$ 且 $\mathrm{line}\le l_i)$ 或 $(a<0$ 且 $\mathrm{line}>r_i)$
- 递减：$(a>0$ 且 $\mathrm{line}>r_i)$ 或 $(a<0$ 且 $\mathrm{line}\le l_i)$

细节：
> - 2.2.1 部分由于可能存在待查询直线 $y=k$ 与二次函数相切的情况，于是 $\mathrm{top}$ 的分界要谨慎。
> - 处理 $\mathrm{top}$ 的小数部分以及其他区间的开闭取值照样要注意。

整个 2.2 部分代码如下：

```cpp
struct func
{
    // ... something ...
    inline void solve()
    {
        if(ty==1)
        {
            // ... something ...
        }
        else
        {
            long double tmp=-b/2.0l/a;// 对称轴
            // long double 的强制转化
            if(tmp>l&&tmp<=r)// 2.2.1 对称轴在区间内
            {
                int tl1,tr1,tl2,tr2;
                long double top=(4.0l*a*c-b*b)/4.0l/a;// 计算顶点
                if(a>0)// 2.2.1.1 a>0
                {
                    tl1=ceil(top),tr1=calc(l)-1;
                    tl2=ceil(top),tr2=calc(r);
                    if(ceil(top)==top) tl2++;// 特判相切
                }
                else// 2.2.1.2 a<0
                {
                    tl1=calc(l)+1,tr1=floor(top);
                    tl2=calc(r),tr2=floor(top);
                    if(floor(top)==top) tr2--;
                }
                len++,p[len].l=tl1,p[len].r=tr1;
                len++,p[len].l=tl2,p[len].r=tr2;
            }
            else// 2.2.2 对称轴不在区间内
            {
                int tl,tr;
                if((a>0&&tmp<=l)||(a<0&&tmp>r)) tl=calc(l)+1,tr=calc(r);// 递增
                else tl=calc(r),tr=calc(l)-1;// 递减
                len++,p[len].l=tl,p[len].r=tr;
            }
        }
    }
}f[S];
```

于是这道题就结束了。

## 代码

[云剪切板](https://www.luogu.com.cn/paste/eto36tje)

---

## 作者：聊机 (赞：2)

upd 2023.1.4： 修改了格式不当和两处笔误，感谢管理员审核（我不明白解法有哪里没解释清楚）。

~~这显然是一道水题~~

然而这是一道细节超多的题。

首先我没有一个好的思维，我只会暴力。比赛时看到这个题目，这不就是一个区间修改单点查询吗？我首先想的的是差分。

然后，数据范围 $ -4\times 10^{18}\le k\le 4\times 10^{18} $

...

那就动态开点线段树！

动态开点线段树维护函数的值域，然后每次进来一个函数区间修改，最后单点查询，具体细节加在代码里。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
inline ll qr() {
	ll k=0;bool f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch)){k=(k<<1)+(k<<3)+(ch^48);ch=getchar();}
	return f?k:-k;
}
const int N=2e5+2;
const ll INF=4e18;//值域范围 
int n,q,LL[N],RR[N],root=1;
ll k[N],a[N],b[N],c[N];//这里开longlong是为了方便计算 
//LL,RR是每个函数的左右端点，这个root其实没啥用，跟动态开点的实现方式有关 
int ls[N<<6],rs[N<<6];//这个数组大小我试了两次才开过 
int lz[N<<6];
//因为是单点查询，所以只要一个lazytag就可以了，ls，rs表示左右儿子 
int CNT=1;
inline void pushdown(int p) {
	if(!ls[p]) ls[p]=++CNT;
	if(!rs[p]) rs[p]=++CNT;//动态开点 
	lz[ls[p]]+=lz[p];//标记下传 
	lz[rs[p]]+=lz[p];
	lz[p]=0;
}
void update(int p,ll l,ll r,ll L,ll R,int x) {//正常区间修改 
	if(l>=L&&r<=R) {
		lz[p]+=x;
		return ;
	}
	pushdown(p);
	ll mid=(l+r)>>1;
	if(mid>=L) update(ls[p],l,mid,L,R,x);
	if(mid<R) update(rs[p],mid+1,r,L,R,x);
	return ;
}
int ask(int p,ll l,ll r,ll x) {//正常单点查询 
	if(l==r) return lz[p];
	pushdown(p);
	ll mid=(l+r)>>1;
	if(mid>=x) return ask(ls[p],l,mid,x);
	return ask(rs[p],mid+1,r,x);
}
long double xx,yy;//因为二次函数的顶点坐标可能不是整数，所以要开浮点 
int main() {
	n=qr(),q=qr();
	ll mx,mm,mn;//这三个分别是函数三个端点 
	for(int i=1,op;i<=n;i++) {//因为函数左开右闭，所以每次要把左端点删除一次 
		LL[i]=qr(),RR[i]=qr(),op=qr();
		if(op==1) {//一次函数非常好处理，不多赘述 
			k[i]=qr(),b[i]=qr();
			mn=k[i]*LL[i]+b[i];
			mx=k[i]*RR[i]+b[i];
			update(root,-INF,INF,mn,mn,-1);//删除左端点 
			if(k[i]<0) swap(mn,mx);
			update(root,-INF,INF,mn,mx,1);
		}
		else {
			a[i]=qr(),b[i]=qr(),c[i]=qr();
			xx=1.0*b[i]/(-2.0*a[i]);//求对称轴 
			if(xx>=1.0*RR[i]||xx<=1.0*LL[i]) {//如果在区间内是单调的，同一次函数 
				mn=a[i]*LL[i]*LL[i]+b[i]*LL[i]+c[i];
				mx=a[i]*RR[i]*RR[i]+b[i]*RR[i]+c[i];
				update(root,-INF,INF,mn,mn,-1);
				if(mn>mx) swap(mn,mx);//注意这里不能根据a判断单调性（我这里错过） 
				update(root,-INF,INF,mn,mx,1);
				continue;
			}
			yy=xx*xx*a[i]+xx*b[i]+c[i];//顶点函数值 
			if(a[i]>0) {
				mn=ceil(yy);
				mm=a[i]*LL[i]*LL[i]+b[i]*LL[i]+c[i];
				mx=a[i]*RR[i]*RR[i]+b[i]*RR[i]+c[i];
				update(root,-INF,INF,mm,mm,-1);
				if(yy==mn)update(root,-INF,INF,mn,mn,-1); //非常细节的一步（我也错过），如果顶点函数值是整数，那它只出现过一次，要删除一次，否则它出现了两次，就不能删除了 
				update(root,-INF,INF,mn,mm,1);
				update(root,-INF,INF,mn,mx,1);
			}
			else {
				mx=floor(yy);
				mm=a[i]*LL[i]*LL[i]+b[i]*LL[i]+c[i];
				mn=a[i]*RR[i]*RR[i]+b[i]*RR[i]+c[i];
				update(root,-INF,INF,mm,mm,-1);
				update(root,-INF,INF,mm,mx,1);
				update(root,-INF,INF,mn,mx,1);
				if(yy==mx)update(root,-INF,INF,mx,mx,-1); 
			}
		}
	}
	int op,K,l=1,r=n,mid;
	while(q--) {//常规输出 
		op=qr(),K=qr();
		if(op==1) {//这个op==1的部分可以骗分 
			l=1,r=n;
			while(l<=r) {//这里我没有考虑更高效的办法，直接二分找区间 
				mid=(l+r)>>1;
				if(RR[mid]>=K) r=mid-1;
				else l=mid+1;
			}
			if(k[l]) printf("%lld\n",k[l]*K+b[l]);//这里开longlong的高效就体现出来了，*1ll很慢 
			else printf("%lld\n",a[l]*K*K+b[l]*K+c[l]);
		}
		else {
			printf("%d\n",ask(root,-INF,INF,K));
		}
	}
	return 0; 
}
```
总之，感谢IOI赛制，如果是OI赛制，我绝对A不了这道题。还是不错的一道基础题（然而我只会基础题）。


---

## 作者：jifbt (赞：2)

## $op=1$

二分所在区间，直接计算即可。

## $op=2$

考虑每个函数造成的贡献。

### 一次函数

一次函数如果单调递增，则会让 $[ \lfloor f_i(l_i) \rfloor + 1, \lfloor f_i(r_i) \rfloor + 1 )$ 区间内的 $k$ 多出一个交点（注意 $k$ 为整数）。其中 $f_i(x)$ 表示这个函数。

如果单调递减，则为 $[ \lceil f_i(r_i) \rceil, \lceil f_i(l_i) \rceil )$。

### 二次函数

我最初想把二次函数当成一个整体来做，这样可能需要很多讨论，其实有更简单的做法。

上面一次函数的做法也适用于单调函数。如果二次函数的顶点在区间外，则也可以这么做。

如果顶点在区间内，则把它在顶点处分成两段，每一段分别做一遍。

进区间时加一，出去时减一，排序完做个前缀和，二分查找即可。

这样写起来只有 1.5 KB 不到，而且效率也还不错。

## 代码

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
template<typename T>void rd(T&x){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	x*=f;
}
template<typename T>T rd(){T x;rd(x);return x;}
template<typename T,typename...T2>void rd(T&x,T2&...y){rd(x),rd(y...);}
typedef long double db;
typedef long long ll;
ll rd(){return rd<ll>();}
const ll N=2e5+10;
ll n,q;
ll l[N],r[N],a[N],b[N],c[N];
ll cnt;
struct D{
	ll y,d;
	operator ll(){return y;}
}diff[N<<2];
template<typename T>T calc(ll i,T x){return a[i]*x*x+b[i]*x+c[i];}
void add(ll i,db l,db r){
	db x=calc(i,l),y=calc(i,r);
	if(x<y)diff[++cnt]={floor(x)+1,1},diff[++cnt]={floor(y)+1,-1};
	else diff[++cnt]={ceil(y),1},diff[++cnt]={ceil(x),-1};
}
int main(){
	rd(n,q);
	for(ll i=1;i<=n;++i){
		rd(l[i],r[i]);
		if(rd()==2)rd(a[i]);
		else a[i]=0;
		rd(b[i],c[i]);
		db z=-b[i]/(2.l*a[i]);
		if(l[i]<z&&z<=r[i])add(i,l[i],z),add(i,z,r[i]);
		else add(i,l[i],r[i]);
	}
	std::sort(diff+1,diff+cnt+1);
	ll j=0;diff[0].y=-0xffffffffffffffffll;
	for(ll i=1,sum=0;i<=cnt;++i){
		sum+=diff[i].d;
		if(diff[i].y!=diff[i-1].y)++j;
		diff[j]={diff[i].y,sum};
	}
	cnt=j;
	while(q--){
		ll o,k;rd(o,k);
		if(o==1)printf("%lld\n",calc(std::lower_bound(l+1,l+n+1,k)-l-1,k));
		else printf("%lld\n",(std::upper_bound(diff+1,diff+cnt+1,k)-1)->d);
	}
}
```

---

