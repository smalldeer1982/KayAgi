# 「SWTR-1」Sunny's Crystals

## 题目背景

小 $\mathrm{S}$ 喜欢收集水晶。

## 题目描述

小 $\mathrm{S}$ 有 $n$ 个水晶，每个水晶有一个属性 $d_i$ ，为这个水晶的**价值**。

有一天，小 $\mathrm{A}$ 来到了 小 $\mathrm{S}$ 家，让 小 $\mathrm{S}$ 把他的水晶排成一个序列，并且摧毁所有价值为 $w$ 的水晶。

但是，由于这个序列的特殊性，你的每次摧毁必须要满足：

- 该水晶在序列里的位置**必须要是 $2$ 的次幂**，即你只能摧毁在 $2^x$ 这个位置上的水晶，$0\leq x \leq \log_2 y$ 且为整数，其中 $y$ 为现在序列里水晶的个数。

摧毁后，**所有在该水晶后面的水晶都会向前移动一格**。

例如，水晶价值序列 $6\  10\  4\  7\  8$，你只能摧毁位置为 $1,2,4$ 上的水晶。

如果摧毁 $2$ 号水晶，序列就会变成 $6\  4\  7\  8$。

为了节省时间，小 $\mathrm{S}$ 想知道**最少**多少次可以摧毁所有价值为 $w$ 的水晶，且第 $i$ 次摧毁的水晶初始位置是什么。

**本题使用 Special Judge**，如果有多种答案，任意输出一种即可。

## 说明/提示

---

### 样例说明

样例 $1$：

先摧毁后面的 $4$，初始位置为 $4$，**价值**序列变成： $1\  4\  2\  5$。

再摧毁前面的 $4$，初始位置为 $2$。

总次数是 $2$ 次。

样例 $2$：

先摧毁第 $1$ 个 $2$，初始位置为 $2$，序列变成：$1\  2\  2\  2$。

再摧毁剩下的第 $1$ 个 $2$，初始位置为 $3$，序列变成：$1\  2\  2$。

再摧毁第一个 $2$，初始位置为 $4$，序列变成：$1\  2$。

再摧毁第一个 $2$，初始位置为 $5$。

总次数是 $4$ 次。

---

### 数据范围与约定

对于 $15\%$ 的数据，有 $n\leq5$。

对于 $25\%$ 的数据，有 $n\leq20$。

对于 $30\%$ 的数据，有 $n\leq1000$。

对于 $35\%$ 的数据，有 $n\leq10000$。

对于 $50\%$ 的数据，有 $n\leq3\times 10^5$。

对于 $80\%$ 的数据，有 $n\leq10^6$。

对于 $100\%$ 的数据，有 $1\leq n\leq3\times 10^6,1\leq d_i\leq 40000$，保证 $w$ 的个数不大于 $1.5\times 10^6$。

---

碎掉的水晶在阳光下闪闪发光……

## 样例 #1

### 输入

```
5 4
1 4 2 4 5```

### 输出

```
2
4 2```

## 样例 #2

### 输入

```
5 2
1 2 2 2 2```

### 输出

```
4
2 3 4 5```

## 样例 #3

### 输入

```
5 8
6 10 4 7 8```

### 输出

```
2
4 5```

# 题解

## 作者：Alex_Wei (赞：26)

$\color{#00cfff}T3.\ Sunny's\ Crystals$

[$\color{#00cfff}\text{题面}$](https://www.luogu.org/problem/T99101?contestId=21489)

官方题解

---

$Sol\ 1\ :\ 15\ pts$

$n!$ 枚举，可过 $15\%$ 的点

代码就不贴了

---

$Sol\ 2:\ 30-35\ pts$

$n^2$ 贪心，可过 $30-35\%$ 的点

模拟每次摧毁

- 如果有可以摧毁的水晶，摧毁位置靠后的

**（如果不是位置在最后，那么摧毁该水晶的时会影响到后面可摧毁的水晶）**

- 否则摧毁当前序列第一个

（贪心思想，没有可摧毁的 $w$，则摧毁位置越前越好）

代码就不贴了

---

$Sol\ 3:\ 80-100\ pts$

$nlog(n)$，线段树维护贪心


线段树的常数巨大，如果你脸黑可能拿不到满分（毕竟只开了不加优化的标程 $+500ms$）

我们先找出所有 $w$，可以 $O(n)$ 求出第 $i$ 个 $w$ 到 **在它之前第一个可以摧毁的位置** 的距离，记为 $d_i$，共有 $c$ 个，记录初始位置 $pos_i$

也就是说，求出 $pos_i-v_i$，其中 $v_i\leq pos_i,v_i=2^x,x$ 为非负整数且 $v_i$ 要最大

接着在 $d_1-d_c$ 之间建线段树，维护区间最小值

仍然是模拟每次摧毁

- $1.$ 如果有可以摧毁的水晶，摧毁位置靠后的

这其实就是找到一个 $i$ 最大且 $d_i$ 为 $0$ 的 $i$，摧毁

接着**把这个位置上的值赋为极大**， $2147483647$ 或一个大于 $10^7$ 的数

然后它后面所有的 $d_{i+1},d_{i+2},\dots,d_c$ 都要 $-1$（这个能理解吧 $qwq$）

- $2.$ 否则求出 $d_1,d_2,\dots,d_c$ 中最小的数，记为 $l$，摧毁 $l$ 个位置为 $1$ 的水晶，$d_1,d_2,\dots,d_c$ 全部减去 $l$，再执行操作 $1$

简而言之，就是让你维护一个 **区间修改，区间最小值** 的线段树

---

代码

```
//by ALEX_WEI
#include<bits/stdc++.h>
using namespace std;
//pragma GCC optimize(3) 开了 O(3) 跑得飞快 , 妈妈再也不用担心我 TLE 啦 !
const int N=3e6+2;
const int inf=2e9+7;
inline void read(int &x)//建议写快读
{
	x=0;char s=getchar();
	while(!isdigit(s))s=getchar();
	while(isdigit(s))x=(x<<1)+(x<<3)+s-'0',s=getchar();
}
inline int _min(int a,int b){return a<b?a:b;}//建议手写 min
int n,x,a,cnt,pow2=1,pos,ori[N],dis[N],els[N],t[N<<2],laz[N<<2],ans[N],now;
//ori 记录初始位置 , els 记录不是 w 的位置 , dis 为题解中的 pos[i]-v[i] , ans 为答案序列 , cnt 为题解中的 c
void build(int l,int r,int x)//建树
{
	if(l==r){t[x]=dis[l];return;}
	int m=l+r>>1;
	build(l,m,x<<1);
	build(m+1,r,x<<1|1);
	t[x]=_min(t[x<<1],t[x<<1|1]);
}
void push_down(int l,int r,int x)
{
	t[x<<1]-=laz[x];
	t[x<<1|1]-=laz[x];
	laz[x<<1]+=laz[x];
	laz[x<<1|1]+=laz[x];
	laz[x]=0;//清零
	t[x]=_min(t[x<<1],t[x<<1|1]);//更新
}
void update(int l,int r,int ql,int qr,int x)
{
	if(ql<=l&&r<=qr){laz[x]++,t[x]--;return;}
	int m=l+r>>1;
	if(m>=ql)update(l,m,ql,qr,x<<1);
	if(m<qr)update(m+1,r,ql,qr,x<<1|1);
	t[x]=_min(t[x<<1],t[x<<1|1]);//最小值
}
int get(int l,int r,int x)
{
	if(l==r){t[x]=inf;return l;}//返回的是编号 ! 
	push_down(l,r,x);//pushdown
	int m=l+r>>1,tmp;
	if(!t[x<<1|1])tmp=get(m+1,r,x<<1|1);//如果左边是 0, 往左边跑
	else tmp=get(l,m,x<<1);//否则往右边跑
	t[x]=_min(t[x<<1],t[x<<1|1]);//更新
	return tmp;
}
int main()
{
	read(n),read(x);
	for(int i=1;i<=n;i++){//O(n) 求 dis 数组
		read(a);
		if((pow2<<1)==i)pow2<<=1;
		if(a==x)ori[++cnt]=i,dis[cnt]=i-pow2;
		else els[++pos]=i;
	}
	build(1,cnt,1),pos=0;
	for(int i=1;i<=cnt;i++){
		if(t[1]){//t[1] 即为 min(dis[1],dis[2],...,dis[cnt]) 
			laz[1]+=t[1];//懒惰标记标上
			for(int j=1;j<=t[1];j++)
				ans[++now]=els[++pos];//从不是 w 的取 t[1] 个
			t[1]=0;//清零
		}
		int p=get(1,cnt,1);//求出可摧毁的水晶编号
		ans[++now]=ori[p];//摧毁掉 , 编号为初始位置
		if(p<cnt)update(1,cnt,p+1,cnt,1);//如果摧毁的不是最后一个 , 将 d[p+1],d[p+2],...,d[c] 减去 1
	}
	cout<<now<<endl;//输出
	for(int i=1;i<=now;i++)
		cout<<ans[i]<<" ";
	return 0;
}
```

求赞 $qwq$ 

---

## 作者：localhost (赞：4)

可以想到贪心: 

如果目前有可以摧毁的目标水晶,那么摧毁最靠后的

否则摧毁第一个水晶

证明: 

> 如果一个水晶目前无法摧毁,它必须等前面若干个水晶被摧毁它才能移动到目标位置
> 
> 所以当目标水晶没有可以摧毁的时候,摧毁序列第一个可以移动最多的目标水晶

> 当有超过一个目标水晶可以摧毁的时候,从后往前摧毁显然是最优的

那么要如何实现这个贪心呢?

很容易想到数据结构

1. 平衡树暴力操作: 数据范围$3\times 10^6$,显然是不行的
   
2. 线段树 目标水晶最多$1.5\times 10^6$,且线段树常数不大,可行

实现: 

1. 线段树维护

维护$d_1,d_2,\dots,d_{cnt}$表示目标水晶到可以摧毁的位置的距离

维护最小值

若最小值为$0$,这找到最靠后的$d_x=0$,摧毁,也就是距离赋值为无穷大,然后将$d_i,i\in[x+1,cnt]$都减去$1$

否则一直摧毁第一个水晶直到最小值为$0$,也就是所有$d_i$都减去$min(d_i)$

代码如下:

```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i=x;i<=y;++i)
il int MIN(int x,int y){return x<y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}}using namespace IO;
const int N=1500011;
int n,w,cnt=0,s[N<<2],laz[N<<2],a[N],old[N],ANS[N<<1],ans=0,oth[N<<1];
#define ls rt<<1
#define rs rt<<1|1
il void pu(int rt){s[rt]=MIN(s[ls],s[rs]);}
il void pd(int rt){
    if(laz[rt]){
        laz[ls]+=laz[rt];s[ls]-=laz[rt];
        laz[rs]+=laz[rt];s[rs]-=laz[rt];
        laz[rt]=0;
    }
}
void build(int l,int r,int rt){
    if(l==r){s[rt]=a[l];return;}
    int m=(l+r)>>1;
    build(l,m,ls);build(m+1,r,rs);
    pu(rt);
}
void upd(int L,int c,int l,int r,int rt){
    if(L<=l){s[rt]-=c;laz[rt]+=c;return;}
    int m=(l+r)>>1;
    pd(rt);
    if(L<=m)upd(L,c,l,m,ls);
    upd(L,c,m+1,r,rs);
    pu(rt);
}
int ask(int l,int r,int rt){
    if(l==r){
        s[rt]=(1<<30);
        ANS[++ans]=old[l];
        return l;
    }
    int m=(l+r)>>1,res;
    pd(rt);
    if(!s[rs])res=ask(m+1,r,rs);
    else res=ask(l,m,ls);
    pu(rt);
    return res;
}
int main(){
    in(n,w);
    int x,b=1,now=0;
    Fur(i,1,n){
        if((b<<1)<=i)b<<=1;
        in(x);
        if(x==w)a[++cnt]=i-b,old[cnt]=i;
        else oth[++now]=i;
    }
    now=0;
    build(1,cnt,1);
    Fur(t,1,cnt){
        if(s[1]){
            Fur(j,1,s[1])ANS[++ans]=oth[++now];
            upd(1,s[1],1,cnt,1);
        }
        x=ask(1,cnt,1)+1;
        if(x<=cnt)upd(x,1,1,cnt,1);
    }
    out(ans);pt('\n');
    Fur(i,1,ans)out(ANS[i]),pt(' ');
    flush();
}
```

2. 巧妙的模拟

可以只维护所有$2$次幂位置在原序列中的位置

每次修改只需要修改$\log_2 n$个位置,复杂度完全可以接受

根据这个特性,暴力跑的比正解线段树还快

代码如下: 

```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i=x;i<=y;++i)
#define Fdr(i,x,y) for(int i=x;i>=y;--i)
il int MIN(int x,int y){return x<y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}}using namespace IO;
const int N=3000011;
int n,tot=0,b=0,w,a[N],p[N],ans=0,ANS[N];
int main(){
    in(n,w);
    Fur(i,1,n){
        in(a[i]);
        if(a[i]==w)++tot;
    }
    a[n+1]=-1;
    while((1<<b)<=n)p[b+1]=(1<<b),++b;
    while(tot){
        bool f=0;
        Fdr(i,b,1)if(a[p[i]]==w){
            ANS[++ans]=p[i];
            a[p[i]]=0;
            Fur(j,i,b)if(p[j]<=n)
                while(!a[++p[j]]);
            --tot;f=1;break;
        }
        if(!f){
            ANS[++ans]=p[1],a[p[1]]=0;
            Fur(i,1,b)if(p[i]<=n)
                while(!a[++p[i]]);
        }
    }
    out(ans);pt('\n');
    Fur(i,1,ans)out(ANS[i]),pt(' ');
    flush();
}
```


---

## 作者：Acestar (赞：2)

~~闲来无事水一篇题解~~

一个小贪心：

>如果有可以摧毁的水晶，则摧毁最靠后的水晶，否则摧毁第一个。

因为摧毁最靠后的水晶不会影响前面的水晶的位置，如果没有可以摧毁的，就需要改变水晶的位置，摧毁第一个就会把后面的全都向前移动。

于是，记录下来第 $i$ 个价值为 $w$ 的水晶的位置 $pos_i$ 和第 $i$ 个水晶到前一个可以摧毁的位置的距离 $dis_i$。还要记录下来价值不为 $w$ 的第 $i$ 个水晶的位置 $del_i$，因为后面要输出。

接下来，就会发现可以用线段树**维护 $dis$ 数组最小值**和**区间修改**。

线段树数组为 $t$。也就是说，如果 $t_1=0$，说明有可以摧毁的水晶，于是查找最靠后的 $dis$ 为 $0$ 的水晶的下角标，否则，摧毁 $t_1-1$ 个水晶，让一个价值为 $w$ 的水晶，移动到可以摧毁的位置上，同时，其余水晶跟着向前移动。最后用 $ans_i$ 记录下来第 $i$ 次摧毁的位置。

本题就做完了。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define INF 0x3f3f3f3f

using namespace std;

const int N=3e6+10;
int n,w,cnt,tot;
int pos[N],del[N],dis[N],ans[N];
int t[N<<2],tag[N<<2];

int read()	//快读 
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}

void pushup(int rt)
{
	t[rt]=min(t[rt<<1],t[rt<<1|1]);
}

void build(int l,int r,int rt)
{
	if(l==r)
	{
		t[rt]=dis[l];
		return;
	}
	int m=(l+r)>>1;
	build(l,m,rt<<1);
	build(m+1,r,rt<<1|1);
	pushup(rt);
}

void pushdown(int rt)
{
	if(tag[rt])
	{
		t[rt<<1]-=tag[rt];
		t[rt<<1|1]-=tag[rt];
		tag[rt<<1]+=tag[rt];
		tag[rt<<1|1]+=tag[rt];
		tag[rt]=0;
		pushup(rt);
	}
}

int get(int l,int r,int rt)
{
	if(l==r)
	{
		t[rt]=INF;
		return l;
	}
	pushdown(rt);
	int m=(l+r)>>1,ret;
	if(!t[rt<<1|1]) ret=get(m+1,r,rt<<1|1);	//这里要先找靠后的水晶 
	else ret=get(l,m,rt<<1);
	pushup(rt);
	return ret;
}

void update(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		tag[rt]++;
		t[rt]--;
		return;
	}
	int m=(l+r)>>1;
	if(L<=m) update(L,R,l,m,rt<<1);
	if(m<R) update(L,R,m+1,r,rt<<1|1);
	pushup(rt);
}

int main()
{
	int p2=1,sum=0;
	n=read();
	w=read();
	for(int i=1; i<=n; i++)
	{
		int a=read();
		if((p2<<1)==i) p2<<=1;	//p2:每个可以摧毁的位置 
		if(a==w) pos[++cnt]=i,dis[cnt]=i-p2;//pos:价值为w的水晶的位置，dis:水晶到前一个可以摧毁的位置的距离 
		else del[++sum]=i;	//价值不为w的水晶 
	}
	build(1,cnt,1);
	sum=0;
	for(int i=1; i<=cnt; i++)
	{
		if(t[1])	//没有可以摧毁的水晶 
		{
			tag[1]+=t[1];	//lazytag 
			for(int j=1; j<=t[1]; j++)
				ans[++tot]=del[++sum];
			t[1]=0;
		}
		int x=get(1,cnt,1);	//获取dis最小的水晶的下角标 
		ans[++tot]=pos[x];
		if(x<cnt) update(x+1,cnt,1,cnt,1);
	}
	printf("%d\n",tot);
	for(int i=1; i<=tot; i++)
		printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：Fzrcy (赞：0)

考虑贪心，若当前序列可以摧毁价值为 $w$ 的水晶，则摧毁最靠右的价值为 $w$ 的水晶，这样做不会影响到其他的可以摧毁的水晶，显然答案不会变劣；若当前序列不存在可以摧毁价值为 $w$ 的水晶，则摧毁第一颗水晶即可。

显然位置在 $i$ 的价值为 $w$ 的水晶会在 $2^d$ 的位置被摧毁（$2^d\le i$、$2^{d+1}>i$），所以我们对价值为 $w$ 的水晶维护 $s_i=i-2^d$ 即可，每一次摧毁一个最靠右的 $s_i=0$ 的水晶 $i$ 或摧毁第一颗水晶，用线段树维护即可，时间和空间复杂度均为线性对数。

注意我们只对价值为 $w$ 的水晶建立线段树即可，不要对序列直接建立线段树。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N=3e6+7;
pair<int,int>s[N<<2]; int g[N<<2];
void build(int k,int l,int r,int *a){
    if(l==r){s[k]={a[l],-l};return;}int mid=l+r>>1;
    build(k<<1,l,mid,a),build(k<<1|1,mid+1,r,a);
    s[k]=min(s[k<<1],s[k<<1|1]);
}
void pg(int x,int v){s[x].first+=v,g[x]+=v;}
void dw(int x){if(g[x])pg(x<<1,g[x]),pg(x<<1|1,g[x]),g[x]=0;}
void upd(int k,int l,int r,int x,int v){
    if(l==r){s[k]={v,-l};return;}int mid=l+r>>1;dw(k);
    if(x<=mid)upd(k<<1,l,mid,x,v);
    else upd(k<<1|1,mid+1,r,x,v);
    s[k]=min(s[k<<1],s[k<<1|1]);
}
void add(int k,int l,int r,int x,int y,int v){
    if(l>=x&&r<=y)return pg(k,v);int mid=l+r>>1;dw(k);
    if(x<=mid)add(k<<1,l,mid,x,y,v);
    if(y>mid)add(k<<1|1,mid+1,r,x,y,v);
    s[k]=min(s[k<<1],s[k<<1|1]);
}
int n,a[N],w,ban[N],t;
vector<int>ans;
deque<int>oth;
int b[N],id[N],m;
int main(){
    cin>>n>>w;
    for(int i=1,f=1;i<=n;i++){
        if(i>1&&i==f*2)f*=2;
        cin>>a[i];
        if(a[i]==w){
            b[++m]=i-f;
            id[m]=i;
            ++t;
        }
        else{
            oth.push_back(i);
        }
    }
    build(1,1,m,b);
    for(;t;){
        if(s[1].first==0){
            int x=-s[1].second;
            ans.push_back(id[x]);
            add(1,1,m,x,m,-1);
            upd(1,1,m,x,1e9);
            t--;
        }
        else{
            int x=oth.front();
            oth.pop_front();
            ans.push_back(x);
            pg(1,-1);
        }
    }
    cout<<ans.size()<<'\n';
    for(auto i:ans)cout<<i<<' ';
    return 0;
}
```



---

## 作者：Mine_King (赞：0)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/LuoguP5584.html)

## Problem

[P5584 【SWTR-01】Sunny's Crystals](https://www.luogu.com.cn/problem/P5584)

**题目大意：**

给你一个长度为 $n$ 的序列，每次可以删掉下标为 $2$ 的非负整数次幂的数，删掉一个数后他后面的数会往前补，问删掉所有值为 $w$ 的数所需要的最小步数及对应的方案。

## Solution

考虑贪心做法。

如果当前能删的数中有 $w$，显然删 $w$ 最优。但当有多个值为 $w$ 的位置时应该如何选择？容易发现删最后一个更优，因为删前面的数会影响后面的数，所以要尽量不影响后面。  
如果当前能删的数中没有 $w$，那么与之前相反，要让尽可能多的位置改变，所以删第一个数。

但是直接做是 $n^2$ 的，所以考虑优化。  
这里给出一个不需要数据结构的做法。  
考虑到能删的位置只有 $\log n$ 个，所以可以维护 $\log n$ 个指针，分别指向能删的位置。每次删一个数就把当前及之后的指针右移一位。并且在删过的数上打上 tag。每次删数都只会影响 $\log n$ 个指针，且每个数最多被 $\log n$ 个指针扫到，复杂度为 $O(n \log n)$。

## Code

实现起来很简单，码就不贴了。

---

