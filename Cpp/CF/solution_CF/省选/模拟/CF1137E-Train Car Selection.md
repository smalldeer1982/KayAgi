# Train Car Selection

## 题目描述

给出一个序列$a_i$，初始有$n$个$0$。$m$次操作，操作有$3$种：

$1\ k(1 \leq k \leq 10^9)$：在序列开头加入$k$个$0$

$2\ k(1 \leq k \leq 10^9)$：在序列末尾加入$k$个$0$

$3\ b\ s(1 \leq b , s \leq 10^9)$：对序列的所有元素做加法，给序列的第$i$个元素加上$b + s(i-1)$

你需要在每一次操作过后输出当前序列中最小值位置和它的值。如果存在多个最小值则只考虑位置最靠前的。

## 样例 #1

### 输入

```
1 8
1 1
3 1 1
3 1 1
2 1
2 1
3 1 1
2 1
3 1 5
```

### 输出

```
1 0
1 1
1 2
3 0
3 0
1 3
5 0
1 4
```

# 题解

## 作者：凄魉 (赞：5)

重要的条件是每次加入的直线，斜率和截距全都是正数。

哦，那不就是永远第一个点最小值吗？不不不可能前后插入0进来，emmmm。

如果前面插入0，那么后面之前的点不就都没用了吧，可是当后面插入0的时候事情好像就稍微复杂一点……

直线……线性……最优性问题……这一类的条件很容易扯到凸包上面去，我们来推导一番。

结论：不在当前局面由所有点$(x-1,A_x)$（$x$代表序列中第$x$个点）（$x-1$是因为题目中的直线就是$s(i-1)+b$）构成的下凸壳的那些点，永远不是最小值。

首先不在凸壳上意味着在当前局面就不是最小值，我们要证明的就是在之后加入一些直线后他也不会是最小值。

![](https://cdn.luogu.com.cn/upload/pic/53989.png)

如图，其中1号点和3号点在凸壳上，2号点不在凸壳上，并且有$A_3<A_2<A_1$。

我们现在想要加入一条直线，使得3号点的值增加，并且还要使2号点成为最小值。$A_3+kx_3+b>A_2+kx_2+b$，那么
$$k>\frac {A_2-A_3}{x_3-x_2}$$

由于凸壳的性质，我们知道1号点和2号点直线的斜率是大于2号点和3号点直线的斜率的，也就是
$$\frac {A_3-A_2}{x_3-x_2}<\frac {A_2-A_1}{x_2-x_1}$$

换一下符号发现
$$k>\frac {A_2-A_3}{x_3-x_2}>\frac {A_1-A_2}{x_2-x_1}$$

即$A_2+kx_2>A_1+kx_1$，所以我们发现这时候2号点的值已经大于1号点了，不可能是最小值。
(以后碰到线性问题就瞎猜凸包)。

那么我们就只需要维护一个下凸壳就行了：

操作1：前面加入一个点下凸壳清空。

操作2：后面加入一个点，不停地从凸壳尾部弹点。

操作3：全体加上一条直线………好像有点麻烦？对于这个操作我们单独维护一个全局标记$(k,b)$表示每个点的值应该是存储的值加上这个标记的值。如在数组里面存的点是$(x,y)$，实际上它的值是$(x,y+kx+b)$。那么进行第3个操作的时候就是增加标记。同时注意第一个操作清空凸包也清空标记，第2个操作为了让加入的点的纵坐标是0，初始的权值是$(x,-(kx+b))$。

代码（膜拜yybyyb，借鉴了dalao的代码思路）：

```cpp
#include<cstdio>
#define N 1023000
#define ll long long
#define double long double
const double eps=1e-6;
struct Point{
	ll x,y;
	Point (ll _x=0,ll _y=0) : x(_x),y(_y) {}
	Point operator - (const Point &B) const {return Point(x-B.x,y-B.y);}
	double operator * (const Point &B) const {return (double)x*B.y-(double)y*B.x;}
}stk[N];
int top;ll k,b;
ll calc(Point A) {return A.y+k*A.x+b;}
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<3)+(n<<1)+(a^48);
	}
	return n;
}
int main()
{
	ll n=read();int Q=read(),opt;Point now;
	stk[top=1]=Point();
	while(Q--)
	{
		opt=read();
		switch(opt)
		{
			case 1:stk[top=1]=Point();n+=read();k=b=0;break;
			case 2:now=Point(n,-(n*k+b));n+=read();
				while(top>1&&(now-stk[top-1])*(stk[top]-stk[top-1])>-eps) --top;
				stk[++top]=now;break;
			case 3:b+=read();k+=read();break;
		}
		while(top>1&&calc(stk[top])>=calc(stk[top-1])) --top;
		printf("%lld %lld\n",stk[top].x+1,calc(stk[top]));
	}
	return 0;
}

//by qlwpc
```


---

## 作者：夜猫子驱蚊器 (赞：2)

[题目传送门](https://codeforces.com/problemset/problem/1137/E)   
感觉[官方题解](https://codeforces.com/blog/entry/65825)已经讲得很好了……  
有很多log的做法，但其实是可以线性的。（额，谁教教我log怎么做啊QAQ)  
例行宣传一下自己的[博客](https://blog.csdn.net/ymzqwq/article/details/88591819)

首先，我们注意到，每次加进去的一组0都是一起增加的，所以我们只需要关心这组0中的第一个（因为后面的肯定会永远大于等于第一个）。

然后我们又注意到，如果在最前面加入一些0，那么除了第一个以外的都永远不会是最大的，那么就相当于让所有$A_i=0$。

所以我们只需要关心2和3两个操作。

我们把所有$(x,A_x)$转化到二维平面上，然后维护一条向左下凸的折线，显然不在这个折线上的就永远不会是答案了。实际上答案就是折线上最后的点，就是右下角那个。

于是2操作就是加个点，然后和求凸包差不多，会删掉末尾的一些点。

3操作的话，我们发现经过操作之后所有线段的斜率都会变大，所以经过操作后凸折线的最后若干个点可能会“翘起来”，所以我们只需要从后往前，把那些“翘起来”的点删掉就行了。
![Untitled1.png](https://i.loli.net/2019/03/18/5c8f567140255.png)
有个小技巧。我们可以记录一下$b[i],s[i]$的前缀和，再结合点$(x,A_x)$是在第几个操作加进来的，就可以O(1)算出$A_x$，而不用在每次进行3操作后给每个凸折线上的点都加一波。

我计算几何弱渣，所以写得很丑QAQ

```cpp
#include<bits/stdc++.h>
#define ll long long
#define x1 _x1
#define y1 _y1
#define x2 _x2
#define y2 _y2
#define fr(i,x,y) for(int i=(x);i<=(y);i++)
#define rf(i,x,y) for(int i=(x);i>=(y);i--)
#define frl(i,x,y) for(int i=(x);i<(y);i++)
using namespace std;
const int N=300003;
int n,m;
ll b[N],s[N];
struct data{
	int num,x;
}st[N];  //这是一个栈，维护凸折线上的点
int L;

inline int sign(ll &x){
	if (x>0) return 1;
	if (x<0) return -1;
	return 0;
}

inline int mul(ll x1,ll y1,ll x2,ll y2){  //这个是判断叉积是否>0的
	int w1=sign(x1)*sign(y2),w2=sign(y1)*sign(x2);
	if (w1!=w2) return w1>w2;
	if (w1==0) return 0;
	return (long double)x1*y2>(long double)y1*x2;
}

void read(int &x){ scanf("%d",&x); }
void read(ll &x){ scanf("%lld",&x); }

void chkmin(ll &x,ll y){ if (y<x) x=y; }

inline ll cal(data q,int w){ //计算A[q.x]
	return b[w]-b[q.num]+1ll*(q.x-1)*(s[w]-s[q.num]);
}

void AddPoint(int w,int x){
	if (cal(st[L],w)==0) return;
	ll y=cal((data){w,x},w);
	while(L>=2){
		if (mul(st[L].x-st[L-1].x,cal(st[L],w)-cal(st[L-1],w),x-st[L].x,y-cal(st[L],w))) break;
		L--;
	}
	st[++L]=(data){w,x};
}

void PopBack(int w){
	while(L>=2&&cal(st[L],w)>=cal(st[L-1],w)) L--;
}

int main(){
	read(n);read(m);
	int tp;ll x,y;
	st[L=1]=(data){0,1};
	fr(i,1,m){
		b[i]=b[i-1];s[i]=s[i-1];
		read(tp);read(x);
		if (tp==1){
			b[i]=s[i]=0;
			st[L=1]=(data){i,1};
			n+=x;
		}else if (tp==2){
			AddPoint(i,n+1);
			n+=x;
		}else{
			read(y);
			b[i]+=x;s[i]+=y;
			PopBack(i);
		}
		printf("%d %lld\n",st[L].x,cal(st[L],i));
	}
	return 0;
}
```


---

## 作者：zesqwq (赞：1)

想写一篇比较简短而清楚的题解。

时间复杂度是线性的，是 $\text{CF}$ 上的最优解。

---

性质 $1$：

我们发现对于两个数 $x, y$，如果 $A_x > A_y$ 且 $x > y$，那么 $x$ 这个位置肯定是没用了，原因比较显然。

---

所以说我们初步的想法是维护一个从大到小的单调栈，但是我们发现从大到小并不能很好的利用题目中的性质。

性质 $2$：

我们发现对于 $x, y$，如果 $A_x > A_y$ 且 $x < y$ 的话 $y$ 超过 $x$ 的操作的 $s$ 和 $\geq\dfrac{A_x-A_y}{y-x}$，然后我们发现这个东西很像斜率，于是对于 $x, y, z$，若 $x>y>z$，那么根据性质 $1$ 有 $A_x<A_y<A_z$，而若 $\dfrac{A_y-A_x}{x-y}\geq\dfrac{A_z-A_y}{y-z}$ 表明 $y$ 已经没有用了，因为这意味着在 $x$ 超过 $y$ 前 $y$ 就超过 $z$ 了，$y$ 不可能在某个时刻成为最小值。

---

这样我们发现维护的东西就是一个坐标为 $(x,A_x)$ 的凸壳状物，有了这个凸壳之后，我们只需要用一个栈来维护，操作 $1$ 直接清空栈（性质 $1$），操作 $2$ 直接用性质 $1$ 和 $2$ 来维护凸壳，操作 $3$ 直接从栈顶开始弹就行了。

直接维护这个凸壳上的每个点也是不太好直接做的，但是我们维护最后一个值和差分是好做的，于是这题就做完了。

代码写的很乱，[需要对拍的可以康康](https://codeforces.com/contest/1137/submission/202470393)。

---

## 作者：bztMinamoto (赞：1)

## 题面

三个操作

1.在当前数列最左端加入$k$个初始为$0$的数

2.在当前数列最右端加入$k$个初始为$0$的数

3.将当前数列从左到右第$i$个数加上$b+(i-1)k(b>0,k>0)$

请在每一次操作之后输出当前数列的最小值以及最小值所在的位置，如果有多个相同的最小值取最左端的

## 题解

首先有两个结论

1.如果在左端加入一个数，那么它后面的所有数都没有用了

证明：因为每一次$3$操作后面加的永远比前面的多，而且值相同时要取最左边的，所以左边加入一个之后后面的都没用了

2.不管是左端还是右端，加入的$k$个数里只有最左端的是有用的

证明同$1$

那么简单来说过程就是这样，我们需要一个能够不断往后添加元素的东西，每一次如果前面加了值我们就把它暴力重构

易发现我们需要维护的是一个递减的序列（因为如果有一个元素大于前面的那么前面那个并没有什么卵用），而且有可能加着加着某一个数突然大于前面了，得把它删去

那么很明显就是一个链表了，只有这玩意儿资瓷快速在数列中间删数

于是我们接下来的过程都假定左端点固定（因为左端点一变我们就需要直接重构）

设当前左端点为$1$，那么后面加入的每个数的位置都是已经定的，对于加的值我们可以维护$\sum b$和$\sum s$，那么到时候需要用的时候可以一起加上去。对于一个新加入的值，设当前$tmpb=\sum b,tmps=\sum s$，我们需要把它的值减去$tmpb+(id-1)tmps$（其中$id$为它的位置），这样才能保证后面加上懒标记的时候它的值是真的

会改变序列中数的大小关系的只与$s$有关，对于数列中相邻的两个数，如果它们的位置之差为$k$，那么一次$3$操作的$s$会使它们之间的值的差减少$ks$，设它们原来的差为$val$，那么只要之后的$s$操作的总和达到了$val/k$（这里是上取整），那么后面那个数就废了，我们就可以删了它

我们每次插入一个数的时候算出它和前面那个数此时相差的值，并记录一下需要达到的$s$，并把它放进一个优先队列里。每一次$3$操作的时候都不断取出最顶端的元素看看是否需要删

注意，我们算出的$s$是之后还需要多少，但是$tmps$记录的是从开始到现在有多少，所以放进队列的时候还需要加上当前的$tmps$

还有，每一次删数的时候，设当前删的数为$p$，那么队列里记录的$p$右边那个数和$p$的差就没有意义了，要删掉，所以我们需要的是一个可删堆

然后没有然后了

ps：为了好看一点第一次用了指针……结果$bug$死活调不出来……以后再也不乱搞了……$RE\ on\ test\ \#70$不知道有多酸爽……

```cpp
//minamoto
#include<bits/stdc++.h>
#define R register
#define ll long long
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
int read(){
    R int res,f=1;R char ch;
    while((ch=getc())>'9'||ch<'0')(ch=='-')&&(f=-1);
    for(res=ch-'0';(ch=getc())>='0'&&ch<='9';res=res*10+ch-'0');
    return res*f;
}
char sr[1<<21],z[20];int C=-1,Z=0;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
void print(R ll x){
    if(C>1<<20)Ot();if(x<0)sr[++C]='-',x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=5e5+5;
struct node{
	node *lc,*rc;int s,id;ll v,c;
	inline void init(R int ss,R int Id,R ll vv){s=ss,id=Id,v=vv,lc=rc=NULL;}
}pool[N],*p[N],*T,*g;
struct point{
	node *c;ll v;
	point(){c=NULL,v=0;}
	point(node *cc,ll vv):c(cc),v(vv){}
	inline bool operator <(const point &b)const{return v>b.v;}
	inline bool operator ==(const point &b)const{return c==b.c&&v==b.v;}
};
struct Queue{
	priority_queue<point>A,B;
	inline void push(R point x){A.push(x);}
	inline void pop(R point x){B.push(x);}
	inline void pop(){A.pop();}
	inline bool empty(){
		while(!B.empty()&&A.top()==B.top())A.pop(),B.pop();
		return A.empty();
	}
	inline point top(){
		while(!B.empty()&&A.top()==B.top())A.pop(),B.pop();
		return A.top();
	}
}q;
int n,m,tot,op,b,s,k,sum;ll sumb,sums,tmpb,tmps;
inline void insh(){p[++tot]->init(sum+k,1,0),T=p[tot],tmpb=tmps=0;while(!q.empty())q.pop();}
inline ll val(node *it){return tmpb+tmps*(it->id-1)+it->v;}
void inst(){
	if(val(T)==0)return T->s+=k,void();
	p[++tot]->init(k,sum+1,-tmpb-tmps*sum);
	p[tot]->c=(val(T)-val(p[tot])+T->s-1)/T->s+tmps;
	p[tot]->lc=T,T->rc=p[tot],q.push(point(p[tot],p[tot]->c));
	T=p[tot];
}
void update(){
	tmpb+=b,tmps+=s;
	while(!q.empty()&&q.top().v<=tmps){
		g=q.top().c,q.pop();
		if(g==T)T=g->lc,T->s+=g->s,T->rc=NULL;
		else{
			g->lc->rc=g->rc,g->rc->lc=g->lc,g->lc->s+=g->s;
			q.pop(point(g->rc,g->rc->c));
			g->rc->c=(val(g->lc)-val(g->rc)+g->lc->s-1)/g->lc->s+tmps;
			q.push(point(g->rc,g->rc->c));
		}
	}
}
int main(){
//	freopen("testdata.in","r",stdin);
	n=read(),m=read();
	fp(i,1,N-5)p[i]=&pool[i];
	k=n,insh(),sum=k;
	while(m--){
		op=read();
		switch(op){
			case 1:k=read(),insh(),sum+=k;break;
			case 2:k=read(),inst(),sum+=k;break;
			case 3:b=read(),s=read(),update();break;
		}
		print(T->id),sr[C]=' ',print(val(T));
	}
	return Ot(),0;
}
```

---

## 作者：Mashu77 (赞：0)

操作 1 和操作 3 后，答案一定是最左端的点，答案的都容易维护。

对于操作 2，我们维护一个左下凸的凸壳，显然这个答案点一定在凸壳上，并且维护凸壳之上的修改操作，对于新加的点答案一定是这一段的左端点，它的实际值为 $0$。

于是我们就可以假设它上面打着修改标记，计算它应有的值，然后加入这个点。加等差数列不会改变凸壳上应有的点，我们可以在凸壳上三分，或者直接从栈弹栈顶，直到找出实际上的底部的点。

---

## 作者：IdnadRev (赞：0)

由于 $b,s$ 均为正，考虑维护一个下凸壳，凸壳的元素值从前往后递减，随着 $3$ 操作后面的值会慢慢变劣并被弹出凸壳。

我们维护一个全局的斜率加 $k$ 与截距加标记 $b$，那么我们的答案就是凸壳上所有点 $(x,y)$ 对应 $kx+y+b$ 的最大值。

$1$ 操作带来的 $0$ 一定是全局最优值，因此可以把凸壳直接清空只保留新加入的 $0$。

$2$ 操作插入一段 $0$ 并从后往前检查凸壳的合并。

$3$ 操作更新标记，并从后往前检查凸壳的合并。

输出凸壳最后一个元素对应的值就好啦，复杂度 $O(n)$。

代码：

```cpp
#include<stdio.h>
const int maxn=300005;
int T,top;
long long len,Btag,Ktag;
struct vec {
	long long k,b;
	inline vec operator -(vec p) {
		return vec {k-p.k,b-p.b};
	}
	inline long long operator ^(vec p) {
		return k*p.b-p.k*b;
	}
	inline long long operator ()() {
		return k*Ktag+b+Btag;
	}
} v[maxn];
int main() {
	scanf("%lld%d",&len,&T),top=1,v[top]=vec {0,0};
	while(T--) {
		int o,x,y;
		scanf("%d%d",&o,&x);
		if(o==1)
			len+=x,Ktag=Btag=0,top=1,v[top]=vec {0,0};
		if(o==2) {
			len+=x;
			if(v[top]()!=0) {
				vec now= {len-x,-Ktag*(len-x)-Btag};
				while(top>1&&((v[top]-v[top-1])^(now-v[top-1]))<0)
					top--;
				v[++top]=now;
			}
		}
		if(o==3) {
			scanf("%d",&y),Btag+=x,Ktag+=y;
			while(top>1&&v[top]()>=v[top-1]())
				top--;
		}
		printf("%lld %lld\n",v[top].k+1,v[top]());
	}
	return 0;
}
```

---

