# April Fools' Problem (hard)

## 题目描述

The plans for HC $ ^{2} $ are rather far-fetched: we are just over 500 000 days away from HC $ ^{2} $ 3387, for example, and accordingly we are planning to have a couple hundred thousand problems in that edition (we hope that programming contests will become wildly more popular). The marmots need to get to work, and they could use a good plan...

## 样例 #1

### 输入

```
8 4
3 8 7 9 9 4 6 8
2 5 9 4 3 8 9 1
```

### 输出

```
32```

# 题解

## 作者：gxy001 (赞：25)

首先，这题有一个显然的费用流做法，连边如下：

- $S$ 向 $i$ 连边，费用为 $a_i$，流量为 $1$。（$1\le i\le n$）
- $i$ 向 $T'$ 连边，费用为 $b_i$，流量为 $1$。（$1\le i\le n$）
- $i$ 向 $i+1$ 连边，费用为 $0$，流量为 $\inf$。（$1\le i<n$）
- $T'$ 向 $T$ 连边，费用为 $0$，流量为 $k$。


$S$ 向 $T$ 跑最小费用最大流，费用即为答案，时间复杂度 $O(knm)$。

我们发现复杂度瓶颈在于求 $k$ 次最短路，考虑优化最短路，我们注意到，可以使用线段树优化这个过程，这样找最短路的复杂度就被优化为 $O(\log n)$，增广的过程也可以修改线段树复杂度也是 $O(\log n)$。总复杂度 $O(k\log n)$。

接下来讲解如何用线段树维护，我们维护从左向右的最短路，从右向左的最短路，从右向左的最短**可流**路，$a_i$ 的最小值，$b_i$ 的最小值，**可以接受来自右边流量**的最小 $b_i$，**可以向左流**的最小 $a_i$，**从右向左**的流量。

找最短路可以直接访问根节点的信息，得到最短路 $S\rarr u\rarr v\rarr T'\rarr T$，增广可以把 $a_u$ 和 $b_v$ 设为 $\inf$，区间修改从右向左的流量。

这样我们就获得了 $O(k\log n)$ 的做法。

~~所以为什么另一篇题解多个 log？~~

```cpp
#include<cstdio>
int n,k,a[500010],b[500010];
struct node{
	struct path{
		int x,y;
		path():x(),y(){}
		path(int const &a,int const &b):x(a),y(b){}
		path operator +(path const &k)const{
			return a[x]+b[y]<a[k.x]+b[k.y]?*this:k;
		}
	}va,vb,vc;
	int aa,ab,ba,bb,vm,tag;
	node():va(),vb(),vc(),aa(),ab(),ba(),bb(),vm(),tag(){}
	friend node operator + (node const &l,node const &r){
		node x;
		x.va=l.va+r.va+path(l.aa,r.ab);
		x.vc=l.vc+r.vc+path(r.aa,l.ab);
		x.aa=a[l.aa]<a[r.aa]?l.aa:r.aa;
		x.ab=b[l.ab]<b[r.ab]?l.ab:r.ab;
		x.vm=l.vm>r.vm?r.vm:l.vm;
		if(l.vm<r.vm){
			x.vb=l.vb+r.vb+r.vc+path(r.aa,l.bb);
			x.ba=l.ba;
			x.bb=b[r.ab]<b[l.bb]?r.ab:l.bb;
		}else if(l.vm>r.vm){
			x.vb=l.vb+r.vb+l.vc+path(r.ba,l.ab);
			x.ba=a[r.ba]<a[l.aa]?r.ba:l.aa;
			x.bb=r.bb;
		}else{
			x.vb=l.vb+r.vb+path(r.ba,l.bb);
			x.ba=l.ba;
			x.bb=r.bb;
		}
		return x;
	}
}tr[2000010];
inline void add(int const &x,int const &p){tr[x].tag+=p,tr[x].vm+=p;}
inline void pushdown(int const &x){if(tr[x].tag)add(x<<1,tr[x].tag),add(x<<1|1,tr[x].tag),tr[x].tag=0;}
void build(int const &x=1,int const &l=0,int const &r=n){
	if(l==r) return tr[x].va=tr[x].vc=node::path(l,l),tr[x].aa=tr[x].ab=tr[x].ba=l,void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	tr[x]=tr[x<<1]+tr[x<<1|1];
}
void update(int const &pl,int const &pr,int const &v,int const &x=1,int const &l=0,int const &r=n){
	if(l==pl&&r==pr) return add(x,v);
	pushdown(x);
	int mid=(l+r)>>1;
	if(pr<=mid) update(pl,pr,v,x<<1,l,mid);
	else if(pl>mid) update(pl,pr,v,x<<1|1,mid+1,r);
	else update(pl,mid,v,x<<1,l,mid),update(mid+1,pr,v,x<<1|1,mid+1,r);
	tr[x]=tr[x<<1]+tr[x<<1|1];
}
void upd(int const &p,int const &x=1,int const &l=0,int const &r=n){
	if(l==r) return;
	pushdown(x);
	int mid=(l+r)>>1;
	if(p<=mid) upd(p,x<<1,l,mid);
	else upd(p,x<<1|1,mid+1,r);
	tr[x]=tr[x<<1]+tr[x<<1|1];
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=n;i++)scanf("%d",b+i);
	a[0]=b[0]=0x3f3f3f3f;
	build();
	long long ans=0;
	while(k--){
		node::path t=tr[1].va+tr[1].vb;
		int i=t.x,j=t.y;
		ans+=a[i]+b[j];
		if(i<j)update(i,j-1,1);
		if(i>j)update(j,i-1,-1);
		a[i]=0x3f3f3f3f,upd(i);
		b[j]=0x3f3f3f3f,upd(j);
	}
	printf("%lld\n",ans);
	return 0;
} 
```





---

## 作者：KaisuoShutong (赞：19)

UPD：谢谢 Futa 先森，指正了一些错误。

详细讲一下线段树模拟费用流做法。

大概会比较啰嗦，但是您会的可以自行跳过。

首先我们可以得出一个简单的费用流建图：

$S\rightarrow i$，流量 $1$，费用 $A_i$；  
$i\rightarrow T_1$，流量 $1$，费用 $B_i$；  
$T_1\rightarrow T_2$，流量 $K$，费用 $0$；  
$i\rightarrow i+1$，流量 $inf$，费用 $0$。

好。那么直接跑肯定超时。考虑优化。

发现如果我们将选择的 $A$ 看成 $($，同时把选择的 $B$ 看成 $)$，那么最终形成的一定是一个合法的括号序列，因为每个 $B$ 的前面必须对应一个 $A$。

令左括号为 $+1$，右括号为 $-1$，做前缀和。  
考虑带悔贪心，每次往里面插入一对匹配的左右括号。  
此时有两种情况：
1. 选择 $()$，那么前缀和数组中 $[i,j)$ 的位置需要加 $1$；
2. 选择 $)($，那么前缀和数组中 $[i,j)$ 的位置需要减 $1$（**显然此时 $[i,j)$ 中的最小值必须大于 $0$**）；

为了维护 $2$ 条件中括号内容，我们有一个 naive 的想法即直接找出 $0$ 的位置然后线段树 pushup 一通乱搞；但这样是不行的，因为有区间减操作。

故我们转而维护：  
$mn$：前缀和数组的区间最小值；  
$va$：$()$ 的最小花费的位置数对；  
$vb$：$)($ 的最小花费的位置数对（**满足两个位置之间的 $mn$ 大于当前线段树区间的 $mn$**）  
$vc$：$)($ 的最小花费的位置数对；

其中 $vc$ 辅助更新 $vb$，$va$、$vb$ 用来更新答案。  
为了辅助更新，我们可以将 $0$ 位置一同处理在线段树中，同时要求 $A_0=B_0=inf$；这样可以保证根区间的 $mn$ 一定为 $0$，从而使得 $vb$ 变成给定的定义。

协助更新，我们还需维护 $ma$、$mb$ 表示区间中 $A$ 和 $B$ 数组的最小值。  
以上内容的维护都是 naive 的。但是非常不幸，仅这些内容并不能很好地维护处 $vb$。

在此之外，额外维护：  
$al$，表示区间中满足前缀（$[L,al)$）点的前缀和区间最小值大于区间的 $mn$ 的位置，多个满足取 $A$ 最小的；  
$bl$，表示区间中满足后缀（$[bl,R]$）点的前缀和区间最小值大于区间的 $mn$ 的位置，多个满足取 $B$ 最小的。

注意看我的开闭。

不妨做一些讨论（设 $l$ 和 $r$ 分别是当前线段树结点的两个儿子）：

1. $mn_l>mn_r$：

此时 $l$ 中任意点均可作 $B$，那么可用 $(mb_l,al_r)$、$vc_l$ 更新 $vb$。  
此时 $al$、$bl$ 相应更新，具体见代码。

2. $mn_l<mn_r$：

同上理，略过。

3. $mn_l=mn_r$：

啥都不行，只能拿 $(al_l,bl_r)$ 更新 $vb$。  
$al$、$bl$ 继承左右。

有啥不懂的，可以看代码。

码长文不易，点个赞吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 500010;
int A[maxn],B[maxn],tg[maxn<<2],n,K;ll ans;
struct node {
	int x,y;
};
bool operator <(node x,node y) {return A[x.x]+B[x.y]<A[y.x]+B[y.y];}
struct info {
	int ma,mb,al,bl,mn;
	node va,vb,vc;
}c[maxn<<2];
info operator +(info x,info y) {
	info z;
	z.ma=A[x.ma]<A[y.ma]?x.ma:y.ma;
	z.mb=B[x.mb]<B[y.mb]?x.mb:y.mb;
	z.mn=min(x.mn,y.mn);
	z.va=min(min(x.va,y.va),(node){x.ma,y.mb});
	z.vc=min(min(x.vc,y.vc),(node){y.ma,x.mb});
	z.vb=min(x.vb,y.vb);
	if(x.mn>y.mn) {
		z.vb=min(min(z.vb,(node){y.al,x.mb}),x.vc);
		z.al=(A[x.ma]<A[y.al]?x.ma:y.al),z.bl=y.bl;
	} else if(x.mn<y.mn) {
		z.vb=min(min(z.vb,(node){y.ma,x.bl}),y.vc);
		z.bl=(B[y.mb]<B[x.bl]?y.mb:x.bl),z.al=x.al;
	} else {
		z.vb=min(z.vb,(node){y.al,x.bl});
		z.al=x.al,z.bl=y.bl;
	}return z;
}
void tag(int k,int vl) {tg[k]+=vl,c[k].mn+=vl;}
void psp(int k) {c[k]=c[k<<1]+c[k<<1|1];}
void psd(int k) {if(tg[k]) tag(k<<1,tg[k]),tag(k<<1|1,tg[k]),tg[k]=0;}
void ins(int k,int l,int r,int p) {
	if(l==r) return;int mid=l+r>>1;psd(k);
	p>mid?ins(k<<1|1,mid+1,r,p):ins(k<<1,l,mid,p),psp(k);
}
void byd(int k,int l,int r) {
	if(l==r) return c[k]=(info){l,l,l,0,0,(node){l,l},(node){0,0},(node){l,l}},void();
	int mid=l+r>>1;byd(k<<1,l,mid),byd(k<<1|1,mid+1,r),psp(k);
}
void upd(int k,int l,int r,int L,int R,int vl) {
	if(l>R||L>r) return;
	if(L<=l&&r<=R) return tag(k,vl);int mid=l+r>>1;psd(k);
	upd(k<<1,l,mid,L,R,vl),upd(k<<1|1,mid+1,r,L,R,vl),psp(k);
}
const int inf = 0x3f3f3f3f;
signed main() {
	n=read(),K=read();
	for(int i=1;i<=n;i++) A[i]=read();
	for(int i=1;i<=n;i++) B[i]=read();
	A[0]=B[0]=inf,byd(1,0,n);
	while(K--) {
		int x,y,vl;
		if(c[1].va<c[1].vb) x=c[1].va.x,y=c[1].va.y,vl=+1;
		else x=c[1].vb.x,y=c[1].vb.y,vl=-1;
		ans+=A[x]+B[y],A[x]=B[y]=inf,ins(1,0,n,x),ins(1,0,n,y),upd(1,0,n,min(x,y),max(x,y)-1,vl);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：E_huan (赞：17)

### WQS二分+反悔贪心（两种反悔贪心方法）


------------
首先看到恰好 $k$ 题，联想到 WQS 二分，二分 $b$ 的增加量（也可以二分 $a$ 的，也可以二分减小量），不难发现增加量越少则打印的题目数量越多，也就是说打印的题目数量关于 $b$ 的增加量的函数是单调递减的，它显然属于凸函数，符合 WQS 二分的前提条件。

对于内层求解，不需要考虑打印的题目数量（但是要记录），可以通过反悔贪心求解。

最开始写了一种很暴力的反悔贪心的实现，没什么思维难度、代码比较长，就是暴力考虑“改变原来的打印时间”、“改变原来的准备时间和打印时间”、“打印一份新的”三种情况，反悔贪心的时间复杂度 $O(n \log n)$。
```cpp
struct node
{
    ll v;
    int id,va;
    bool operator<(const node &t)const{return v<t.v;}
};
inline void calc(int d)
{
    res=cnt=0;
    priority_queue<int,vector<int>,greater<int> > A;
    priority_queue<node>  B,chs;
    for(int i=1;i<=n;i++) erase[i]=0;
    for(int i=1;i<=n;i++)
    {
        while(chs.size()&&erase[chs.top().id]) chs.pop();
        while(B.size()&&erase[B.top().id]) B.pop();

        A.push(a[i]);

        ll delta1=0,delta2=0,delta3=0;
        if(B.size()&&b[i]<B.top().v) delta1=b[i]-B.top().v;
        if(chs.size()&&A.top()+b[i]<chs.top().v)
            delta2=(A.top()+b[i]-chs.top().v);
        if((b[i]+d)+A.top()<0) delta3=(b[i]+d)+A.top();
        if(delta1>=0&&delta2>=0&&delta3>=0) continue;

        if(delta1==min({delta1,delta2,delta3}))
        {
            res+=delta1;
            node last=B.top(); B.pop();
            B.push({b[i],i,last.va});
            chs.push({last.va+b[i],i,last.va});
            erase[last.id]=1;
        }
        else if(delta2==min({delta1,delta2,delta3}))
        {
            res+=delta2;
            node last=chs.top(); chs.pop();
            chs.push({A.top()+b[i],i,A.top()});
            B.push({b[i],i,A.top()});
            A.pop();
            A.push(last.va);
            erase[last.id]=1;
        }
        else{//注意只用管总价值最优，数量只用即时记录就可以了，所以不是“delta3<0就delta3”
            res+=delta3;
            cnt++;
            B.push({b[i],i,A.top()});
            chs.push({A.top()+b[i],i,A.top()});
            A.pop();
        }
    }
}
```

其实还有一种很简洁的方法，发现由于 $a$ 是一边枚举一边加入的，当前在堆中的 $a$ 对于当前的 $b$ 都是合法的（即不会出现先打印再准备的情况），而 $b$ 只有两件事可以做：

$1$. 和 $a$ 组成一对，代表新增加一题（准备+打印）。其实就是找到最小的 $a$，把 $a$ 从堆中删除，累加答案 `res+=(a'+b[i])`。

$2$. 替换原来的 $b$。其实就是找到最大的已选择的 $b$，把它从堆中删除，修改答案 `res+=(-b'+b[i])`。

这二者可以合并，因为每次只能做两件事中的一件，且对答案的贡献分别是 $a'$ 和 $-b'$，所以可以放在一个堆中维护。循环到 $i$ 时把 $a[i]$ 加入堆中，若 $b[i]$ 被选择则将 $-b[i]$ 加入堆中。反悔贪心的时间复杂度 $O(n \log n)$。代码如下：

```cpp
struct node
{
    ll v;
    int add;
    bool operator<(const node &t)const{return v>t.v;}
};
inline void calc(int d)
{
	res=cnt=0;
	priority_queue<node> heap;
	for(int i=1;i<=n;i++)
	{
		heap.push({a[i],1});
		if((b[i]+d)+heap.top().v<0)
		{
			res+=(b[i]+d)+heap.top().v;
			cnt+=heap.top().add;
			heap.pop();
			heap.push({-(b[i]+d),0});
		}
	}
}
```

总时间复杂度 $O(n \log^2 n)$

两种写法的完整 AC 代码：
[第1种](https://codeforces.com/contest/802/submission/184523882)
[第2种](https://codeforces.com/contest/802/submission/184524843)

---

## 作者：翼德天尊 (赞：12)

经典 $k$ 道题，一眼 wqs 二分。

于是可以抛开这个条件，再来看这道题。

发现我们每次决策的时候可以在打印的时候考虑，打印时考虑打印哪天准备的题目。贪心地来讲，我们一定会选择当前准备+打印总花费最少的题目。

进一步而言，对于每一次打印，我们一定会挑选之前准备花费最少且准备+打印总花费为非正数的题目进行打印。但是这显然还不够。

很显然的反例是，之前准备花费最小的题目在最优情况下，本来应该被后面的打印挑走，却被前面的打印先挑走了。这显然是不行的。

于是考虑反悔，用一个小根堆维护之前的所有决策，每次取出价格最低的决策，将当前打印的花费加上决策花费后，如果总花费为非正数，则先选择该决策。又由于：
$$
a_i+b_j-b_j+b_k=a_i+b_j+(-b_j+b_k)
$$
于是把当前打印的花费的相反数加入堆中，供以后反悔使用即可。

还需要特别注意的一点是，由于 wqs 二分时应尽量多选择物品，所以当正常选的决策和反悔的决策花费相同时，我们应该优先选择正常选的决策，使得物品数更多，防止斜率相同的情况发生而无法处理。

剩下的基本就是板子了。代码很短。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+5;
ll n,m,a[N],b[N],ans,sum,now;
struct node{
	ll w;
	bool pd;
	node (ll w=0,bool pd=0)
		:w(w),pd(pd){}
	bool operator <(const node&x) const{
		return (w^x.w)?w>x.w:pd<x.pd;
	}
};
int read(){
	int w=0,fh=1;
	char ch=getchar();
	while (ch>'9'||ch<'0'){
		if (ch=='-') fh=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*fh;
}
bool check(ll x){
	sum=now=0;
	priority_queue<node> q;
	while (!q.empty()) q.pop();
	for (int i=1;i<=n;i++){
		q.push(node(a[i]-x,1));
		node s=q.top();
//		printf("%lld %lld\n",1ll*i,s.w);
		if (s.w+b[i]<=0){
			sum+=s.w+b[i];
			now+=s.pd;
			q.pop();
			q.push(node(-b[i],0));			
		}
	}
	return now>=m;
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++) b[i]=read();
	ll l=0,r=2e9;
	while (l<=r){
		ll mid=l+r>>1;
		if (check(mid)) r=mid-1,ans=sum+m*mid;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lzp101001 (赞：12)

#### 属于无脑的套路题，然而有些题解写的比较含糊

------------

首先猜想答案关于 $k$ 是一个**凸函数**，这种东西最好用**数学方法**严谨证明，感性理解是很容易翻车的。但是在正式比赛中，**打表**显然是最佳方式。

**WQS二分** 的核心思想就是给受到 “恰好” 这种个数限制的物品附加一个**额外代价**，从而达到**控制个数**的目的

本题直接套用，给每次配对附加一个额外代价，然后二分这个附加权值

如果配对个数 $\ge k$ 就增加额外代价，否则就减小额外代价

WQS二分内部就是原题去掉个数限制，我联想到了**模拟费用流**

顺序扫描，每次先往堆中加入 $a_i$，再考虑 $b_i$ 如何配对

有两种决策：

① 与某个单身的 $a_x$ 配对

② 拆散原有的一对 $(a_x,b_y)$，与其中的 $a_x$ 配对，让 $b_y$ 恢复自由

再想想两种决策分别的代价：

① $a_x+b_i$ 

② $(a_x+b_i)-(a_x+b_y)=-b_y+b_i$

我发现两种代价中都有 $+b_i$ 这一项，所以每次**贪心**选择当前所有 $a_x$ 与 $-b_y$ 中的**最小值**即可

为了让所有的决策都在堆中被考虑到，每个单身的 $a_i$ 和每对 $(a_x,b_y)$ 都要加入堆中

**代码：**

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=500010;
int n,k;
int a[N],b[N];
int sum,cnt;
struct nd{
	int x;
	bool op;
	bool operator < (const nd &rhs) const{
		return x>rhs.x;
	}
};
bool check(int mid){
	priority_queue<nd> q;
	cnt=sum=0;
	for(int i=1;i<=n;i++){
		q.push({a[i],0});
		if(q.top().x+b[i]+mid<=0){
			sum+=q.top().x+b[i]+mid;
			if(!q.top().op) cnt++;
			q.pop();
			q.push({-b[i]-mid,1});
		}
	}
	return cnt>=k;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int l=-1e10,r=1e10;
	while(l<r){
		int mid=l+r+1>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	check(l);
	cout<<sum-k*l;
	return 0;
}
```

说实话，这种套路题的**思维含量**确实不高，不太需要思考就能做，但是基本的套路题还是要刷够的，否则一旦遇到自己没做过但别人做过的套路题就会**懊悔万分**了

---

## 作者：NusGhy (赞：11)

提供一下不需要考虑网络流的思路。  
  
主要思路：看到题中一个元素两种操作求最优联想到 [CF865D Buy Low Sell High](https://www.luogu.com.cn/problem/CF865D) ，考虑这两道题之间的区别和联系。 
  
第一个区别是 CF865D 中对股票的第二次操作为收益，本题中两次均为支出。  
  
 我们假设打印题目每道题花费上限为 $M$ 元，则每次在第 $i$ 天打印题目可视为节省（即收益） $M - b_i$ 元。  
   
将准备题目视为买入题目，打印视为卖出，运用 CF865D 中的方法，最后求出的答案 $ans'$ 是：   
  $$ans' = \max \ \{\ \sum (M - b_{use}) - \sum a_{use}\ \} $$
  运用这个我们可以 $O(1)$ 求出要求的答案 $ans$（$m$ 为选择题目个数）：     
   $$ans = \min \ \{\ \sum b_{use} + \sum a_{use}\ \} = M \times m \ -\ ans'$$   
  
第二个区别是本题只能出刚好 $m$ 道题。  
  
考虑 CF865D 中两种极端情况，第一种是收益均为正无穷，显然买越多越好，第二种是收益均为负数，显然最好一个都不买。  
  
感性理解一下，我们发现假如令所有股票的收益都加上 $x$，那么买的股票数是随 $x$ 单调不减的。  
  
而这种关系换到上面提出的做法就是求出最优解当中出题数随 $M$ 单调不减。  
  
那么我们二分 $M$ ，找到刚好使最优解出题数为题中 $m$ 的某个 $M$，再用它计算答案即可。  
  
不过还需要考虑计算最优解出题数的方法。  
  
在 CF865D 中，我们对于每一天会把两个价格丢进堆里，一次是买股票的支出，一次供反悔的卖股票的收入。  
  
我们在把价格扔进堆里时多记录一个状态，若是真正买的则为 $1$，若是供反悔的则为 $0$。  
  
每次取出堆顶时，若这个状态为 $1$，则给购买数（出题数）加一，反之不加，最后就得到了最优解购买数（出题数）。  
  
代码：  
  
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 500005;

int n, m;
ll ans;
int a[maxn], b[maxn];
ll lb[maxn];
priority_queue <pair<ll, int> > que;

int read() {
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') {  
    	if (ch == '-') w = -1;    
    	ch = getchar();             
    }
    while (ch >= '0' && ch <= '9') { 
    	x = x * 10 + (ch - '0'); 
    	ch = getchar();  
    }
    return x * w; 
}

int check(ll tp)
{
	for(int i = 1; i <= n; i ++)
		lb[i] = tp - b[i];
	while(!que.empty()) que.pop();
	ans = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i ++)
	{
		que.push({-a[i], 1});
		if(lb[i] > -que.top().first)
		{
			ans += lb[i] + que.top().first;
			cnt += que.top().second;
			que.pop();
			que.push({-lb[i], 0});
		}
	}
	ans -= 1ll * m * tp;
	return cnt;
}

int main()
{
	n = read(); m = read();
	for(int i = 1; i <= n; i ++)
		a[i] = read();
	for(int i = 1; i <= n; i ++)
		b[i] = read();
	ll l = 0, r = 20000000009;
	while(l < r)
	{
		ll mid = (l + r) >> 1;
		int res = check(mid);
		if(res == m)
		{
			r = mid;
			break;
		}
		else if(res > m)
			r = mid - 1;
		else l = mid + 1;
	} 
	check(r);
	cout<<-ans<<endl;
}
```


---

## 作者：Leap_Frog (赞：8)

### Before Read.
前置：CF802N 的费用流做法（  
upd on 5.6 修正了一个字符的错别字
### Description.
见题目翻译
### Solution.
感谢 @[$\color{black}\text{F}\color{red}\text{lying2018}$](https://www.luogu.com.cn/user/52902) 对笔者的指导。  
首先，它是一个费用流模型（见 CF802N 的题解。  
> 如果是一个费用流模型，它肯定具有下凸性  
> 因为费用流的过程中，肯定是先增广最短路，增广完了之后不可能增广更短的路  
> ——$\color{black}\text{F}\color{red}\text{lying2018}$

所以我们可以直接用类似 wqs二分 一样的套路二分一个差值。  
每次可以 $O(n\log n)$ 判断可以选多少。  
具体就是当前这个点有两种决策：
1. 把它当作 a
2. 把它当作 b 并和之前最小的 a 匹配

可以用一个堆来维护。
### Coding.
代码很短
```cpp
//愿你和你重要的人能够重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}
int n,K,a[500005],b[500005];priority_queue<pair<int,int> >q;
int main()
{
	read(n),read(K);for(int i=1;i<=n;i++) read(a[i]);
	long long l=0,r=2e9,md;for(int i=1;i<=n;i++) read(b[i]);
	while(l<=r)
	{
		md=(l+r)>>1;long long s=0;int cnt=0;
		for(int i=1;i<=n;i++)
		{
			q.push(make_pair(-a[i],0));
			int tmp=b[i]-md-q.top().first;
			if(tmp<0) s+=tmp,q.pop(),q.push(make_pair(b[i]-md,1));
		}
		while(!q.empty()) cnt+=q.top().second,q.pop();
		if(cnt==K) return printf("%lld\n",s+1ll*K*md),0;
		if(cnt<K) l=md+1;else r=md-1;
	}
}
```

---

## 作者：Prean (赞：4)

太厉害啦，出题人究竟是怎么想到的。

首先这题很显然可以使用费用流：对于 $ i \leq j $，连接一条边 $ (i,j+n $，流量为 $ 1 $，费用为 $ a_i+b_j $。最后连接 $ (0,i)(1 \leq i \leq n) $ 和 $ (i+n,n+n+1)(1 \leq i \leq n) $，流量全部为 $ 1 $，费用为 $ 0 $，然后连接 $ (n+n+1,n+n+2) $，流量为 $ k $，费用为 $ 0 $。

众所周知，费用流模型都是凸函数，所以我们理所当然地能够使用 wqs 二分。

二分之后，原问题变成了打印题目最多的时候的最小化费。

我们仍然能够建立一个费用流模型，但是删除了 $ (n+n+1,n+n+2) $ 的边。

也就是说，这个东西变成了一个二分图的最小费用最大流。（似乎是特殊二分图的带权最大匹配？）

我们考虑像匈牙利算法那样去匹配，但是由于边数太多，在这里能使用反悔贪心来代替匈牙利。

具体来讲，对于一个决策 $ (i,j) $，使用 $ (i,k) $ 将其替换掉的条件明显是 $ b_k>b_i $。所以我们将 $ a_i - mid $ 丢进堆中，取最小的，然后使用自身与其匹配。若代价为正就不匹配，否则匹配，若其是反悔后的元素则不计数。

于是就能够做到 $ O(n\log n\log V) $，可以通过。~~实际上最大点只有 1.4s~~

当然你也可以使用线段树模拟费用流，复杂度是能够吊打这个做法的 $ O(k\log n) $。
```cpp
#include<cstdio>
#include<cctype>
#include<queue>
typedef long long ll;
const int M=5e5+5;
int n,k,a[M],b[M];ll ans;
struct data{
	int V;bool typ;
	inline bool operator<(const data&it)const{
		return V>it.V;
	}
};std::priority_queue<data>q;
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
signed main(){
	int i,V,L(0),R(2000000000),mid,cnt;n=read();k=read();
	for(i=1;i<=n;++i)a[i]=read();for(i=1;i<=n;++i)b[i]=read();
	while(L<=R){
		mid=1ll*L+R>>1;cnt=ans=0;std::priority_queue<data>().swap(q);
		for(i=1;i<=n;++i){
			q.push((data){a[i]-mid,true});V=b[i]+q.top().V;
			if(V<0)ans+=V,q.top().typ&&++cnt,q.pop(),q.push((data){-b[i],false});
		}
		if(cnt==k)return printf("%lld",ans+1ll*k*mid),0;
		if(cnt<k)L=mid+1;else R=mid-1;
	}
}
```

---

## 作者：pldzy (赞：2)

线段树模拟费用流。

[LG传送门](https://www.luogu.com.cn/problem/CF802O)。

## Solution

### Part 1 

根据题面，显然想到此题是费用流。建图方式亦是显然：
- $S\rightarrow i$，流量为 $1$，费用为 $a_i$；
- $i\rightarrow T_0$，流量为 $1$，费用为 $b_i$；
- $i\rightarrow i+1$，流量为 $\inf$，费用为 $0$；
- $T_0\rightarrow T_1$，流量为 $k$，费用为 $0$。

观察数据，知道直接跑费用流肯定会起飞。所以我们选择模拟费用流。

### Part 2

不难抓住题目条件的特性：第 $i$ 天经过第一次处理后的东西，第二次处理的时间必定在时刻 $i$ 之后，不能在它之前。这种特性与**括号序列**所具有的是相同的。

具体地，记“第一次处理”为 $+1$（等价于左括号），“第二次处理”为 $-1$（等价于右括号）。并现有一前缀数组 $S$，其长度为 $n$。若第 $i$ 天选择第一次处理，则 $S_i + 1$；若选择第二次处理，则 $S_i-1$。与括号序列同理，这个前缀数组 $S$ 的特点是：**每一项权值都是非负数**，且 $S_n=0$。

进而，我们现在的目标转化为：**在括号序列合法的前提下，每次放入一左一右两个括号，重复 $k$ 次，并使最终总代价最少**。每次一并放两个括号，一正一负，不会改变 $S_n$ 的值，$S_n$ 一直为 $0$。

### Part 3

假设将左括号放在第 $i$ 位，右括号放在第 $j$ 位。不难得出，每次放置只有两种情况：$i\leq j$ 或 $i > j$。形象些，即是 `..(..)..` 与 `..)..(..`。

最直接的方式就是线段树动态维护两个序列的最小值，每次取最小值即可。这种方式对第一种情况是适用的。

但是因为括号序列前缀数组的特殊限制，对于第二种情况，需要满足前提条件：对于 $x \in [j, i)$，$S_x > 0$。

而我们使用线段树动态维护的，是对于区间 $[l,r]$，代价最小且合法的两个数对，分别对应第一种情况以及第二种情况里的 $i$ 和 $j$。此次代价即是两种情况中代价较小的一个。

如何维护第二种情况？如果直接维护权值是否为 $0$，未免太过麻烦，可能超时。所以我们不妨转化一下，使 $a_0=b_0=\inf$，那么对于 $S_0$ 而言，必定恒为 $0$。故我们线段树维护的范围是 $[0,n]$，且 $t_1.min$（即整个 $S$ 序列的最小值）恒为 $0$。此时，满足第二种情况限制的数对，它所构成的区间，只需要保证，该区间内每个权值都**严格大于整个区间的最小值**。相比前者而言，它显然好维护些。

故，对于某一区间 $[l,r]$，我们需要维护：
- $ma$ 与 $mb$：满足下标在 $[l,r]$ 范围内，$a[ma]$ 与 $b[mb]$ 分别是各自序列中的最小值；
- $la$ 与 $lb$：仅针对情况二，维护当前区间满足情况二限制的前缀 $[l,la)$ 与 $[lb,r]$，辅助情况二求解；
- $mn$：下标在 $[l,r]$ 内，$S$ 序列中的项的最小值；
- $va$：当前区间对于情况一的答案（一数对）；
- $vb$：当前区间对于情况二的答案（一数对，且考虑情况二的特殊限制）；
- $vc$：当前区间对于情况二的临时答案（一数对，且不考虑情况二的特殊限制）。

然后区间合并时，以上变量之间的合并差不多是基本的常见操作，$vb$ 的合并稍复杂，详析见代码注释。

### Part 4

时复 $\mathcal{\text{O}}(n+k\log n)$。

另：此做法可求出 $k\in [1,n]$ 时的任一答案。

## Code

内附有注释。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define ls (x<<1)
#define rs (x<<1|1)
const int maxn = 5e5 + 5, inf = 0x3f3f3f3f;
int n, k, a[maxn], b[maxn];
ll ans;
struct node{int x, y;};
struct tree{
	int ma, mb, la, lb, mn, tg;  
	node va, vb, vc;
}t[maxn << 2];
inline bool operator <(node x, node y){
	return a[x.x] + b[x.y] < a[y.x] + b[y.y];
} 
inline tree operator +(tree x, tree y){
	tree z; z.tg = 0;
	if(a[x.ma] < a[y.ma]) z.ma = x.ma; else z.ma = y.ma;
	if(b[x.mb] < b[y.mb]) z.mb = x.mb; else z.mb = y.mb;
	z.mn = min(x.mn, y.mn);//以上三者直接取最小 
	z.va = min((node){x.ma, y.mb}, min(x.va, y.va));
	z.vc = min((node){y.ma, x.mb}, min(x.vc, y.vc));//在没有特殊限制时，两区间合并可产生新的、符合条件的数对 
	z.vb = min(x.vb, y.vb);
	if(x.mn > y.mn){
	//此时，x所代表的区间内的所有数 都严格大于合并后区间最小值，所以x区间内的数可直接取最小 
		z.vb = min(z.vb, min((node){y.la, x.mb}, x.vc));
		z.la = (a[x.ma] < a[y.la] ? x.ma : y.la), z.lb = y.lb;
		/*z.la=y.la等价于这个前缀直接涵盖了x区间，并与y区间的la前缀接上了*/
	} else if(y.mn > x.mn){
		z.vb = min(z.vb, min((node){y.ma, x.lb}, y.vc));
		z.la = x.la, z.lb = (b[y.mb] < b[x.lb] ? y.mb : x.lb);
	} else{ z.la = x.la, z.lb = y.lb;
		z.vb = min(z.vb, (node){y.la, x.lb});//直接合并前后缀 
	} return z;
}

inline void psd(int x){
	if(!t[x].tg) return;
	t[ls].tg += t[x].tg, t[ls].mn += t[x].tg;
	t[rs].tg += t[x].tg, t[rs].mn += t[x].tg;
	t[x].tg = 0;
}
inline void psp(int x){ t[x] = t[ls] + t[rs];}
inline void build(int x, int l, int r){
	if(l == r) return 
		t[x] = (tree){l, l, l, 0, 0, 0, (node){l, l}, (node){0, 0}, (node){l, l}}, void();
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r), psp(x);
}
inline void updt1(int x, int l, int r, int p){
	if(l == r) return;
	int mid = l + r >> 1; psd(x);
	if(p <= mid) updt1(ls, l, mid, p); else updt1(rs, mid + 1, r, p);
	psp(x);
}
inline void updt2(int x, int l, int r, int L, int R, int p){
	if(l > R or L > r) return;
	if(L <= l and r <= R) {t[x].tg += p, t[x].mn += p; return;}
	int mid = (l + r) >> 1; psd(x);
	updt2(ls, l, mid, L, R, p), updt2(rs, mid + 1, r, L, R, p);
	psp(x);
}

int main(){
	scanf("%d%d", &n, &k); 
	rep(i, 1, n) scanf("%d", &a[i]); rep(i, 1, n) scanf("%d", &b[i]);
	a[0] = b[0] = inf; build(1, 0, n);
	while(k--){ int x, y, p;
		if(t[1].va < t[1].vb) x = t[1].va.x, y = t[1].va.y, p = 1;
		else x = t[1].vb.x, y = t[1].vb.y, p = -1;
		ans += a[x] + b[y]; a[x] = b[y] = inf;
		updt1(1, 0, n, x), updt1(1, 0, n, y);
		updt2(1, 0, n, min(x, y), max(x, y) - 1, p);
	} printf("%lld\n", ans);
	return 0;
} 
```
## Reference

- [CF802O April Fools' Problem (hard) 题解](https://www.luogu.com.cn/blog/Criticism/solution-cf802o)，by [KaisuoShutong](https://www.luogu.com.cn/user/106182).
- [题解 CF802O April Fools' Problem](https://www.luogu.com.cn/blog/gxy001/solution-cf802o), by [gxy001](https://www.luogu.com.cn/user/55707).

---

## 作者：ty_mxzhn (赞：1)

## 题意

$n$ 道题，第 $i$ 天可以花费 $a_i$ 准备一道题，花费 $b_i$ 打印一道题，每天最多准备一道，最多打印一道，准备的题可以留到以后打印，求最少花费使得准备并打印 $k$ 道题。$1\le k\le n\le 5\times 10^5$。

## 题解

贪心太厉害！

$k$ 道题的限制不用管，因为这个答案函数显然是下凸的，直接 wqs 二分即可。

我们每天打印的时候，显然是可以选一道自己喜欢的题打印下来，一个贪心的想法是每次打一道准备花费最小的还没有打的，并且这次打完不会对代价产生正贡献的打下来。

显然是错误的，考虑反悔。之前打印完了的匹配，我们可以让之前那个不打印，然后让这个新的换上去。当然的，我们也需要这次代价不存在正贡献。

可以用堆来维护反悔贪心。

---

## 作者：xfrvq (赞：0)

[【费用流】弱化版做法](https://www.luogu.com.cn/blog/_post/487050)。

备注：双倍经验 P4694。

结合这个要做 $x_0$ 道题的限制，考虑 $\tt wqs$ 二分。

---

我们设 $g(x)$ 为处理 $x$ 道题而非 $x_0$ 道的代价。

首先有 $g(0)=0$，然后它单调上升，它的导函数也是单调上升（下凸函数），这是 $\tt wqs$ 能使用的条件。

然后我们二分一个斜率 $k_0$，然后尝试计算 $f(x)=g(x)-k_0x$ 的最小值位置 $x_1$，然后看 $x_1$ 和 $x_0$ 的大小关系来判断答案会取在 $mid$ 的左还是右。

---

考虑 $f(x)=g(x)-k_0x$ 的意义是什么。做 $x$ 道题的代价减去 $x\times k_0$ 的代价，相当于做每道题的代价都减去 $k_0$。因为要 $f(x)$ 最大，相当于求“所有 $b_i\gets b_i-k_0$，最小代价是多少，此时做多少道题”。

因为要代价最小且减去 $k_0$ 后代价可能为负，我们自然而然认为把所有代价是负的题全都做了。

这个过程实现可以考虑贪心。我们制定这样一个策略：

1. 对于每一个 $b_i$ 找到 $\forall j\le i,\min\{a_j\}$。
2. 如果 $b_i+a_j\lt 0$，将其配对，并不允许“$a_j$ 再在后面的第 1 步中出现”。

当然实现可以考虑优先队列（小根堆），第一步就是 `top()`，第二步如果配对成功就是 `pop()`。

但是这种贪心存在不够优秀的情况。比如完成一组匹配时，为了达到最优抢走了另一组匹配唯一可选的点。

这种情况需要加一个反悔选项在优先队列里。考虑一组匹配带来 $a_j+b_i$ 的贡献，$a_j$ 此刻应该是有用的。我们考虑让 $a_j$ 和 $b_k$ 配，就等价于加上一个 $-b_i$ 和 $b_k$ 配的贡献。所以反悔的方法是在堆里加入 $-b_i$。

[评测链接](https://codeforces.com/problemset/submission/802/188556789)。

---

## 作者：creation_hy (赞：0)

wqs 二分好题。

二分一个临界值 $mid$，然后按照常规套路来就行了。

对于每次打印，用一个优先队列维护最优的对应的准备题的那天即可。

具体实现就是每天把当天的 $a_i-mid$ 插进优先队列就行了，然后如果 $b_i$ 加最优的 $a_i$ 大于 $mid$，就考虑转移。

注意一个点，打完之后如果不是最优方案，可能需要撤销。

怎么撤销呢？其实就是相当于撤销的那天花的 $b_i$ 可以不花了，所以把 $-b_i$ 推进去不就行了（

所以要维护两个东西，一个是最优的没有用过的 $a_i$，还有就是最优的反悔的代价，即 $-b_i$。

然后如果是没有用过的 $a_i$，把计数变量加一，否则如果是反悔的，不变。

**注意一个坑点：优先用还没用过的 $a_i$！打一道新的题优先度肯定比反悔高，因为最后如果没有打完 $k$ 道题是不能计入答案的嘛。**

思路很简单，上代码吧。

还有就是，二分的 $l,r,mid$ 都要开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MP make_pair
typedef long long ll;
typedef pair<ll, bool> plb;
const int N = 5e5 + 5;
int n, m;
ll a[N], b[N], cost;
priority_queue<plb, vector<plb>, greater<plb>> q;
inline int check(ll k)
{
    q = priority_queue<plb, vector<plb>, greater<plb>>();
    int cnt = 0;
    cost = 0;
    for (int i = 1; i <= n; i++)
    {
        q.emplace(MP(a[i] - k, 0));
        if (q.top().first + b[i] <= 0)
        {
            cost += q.top().first + b[i];
            cnt += q.top().second ^ 1;
            q.pop();
            q.emplace(MP(-b[i], 1));
        }
    }
    cost += k * m;
    return cnt;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    ll l = 0, r = 0, ans = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i], r += a[i] + b[i];
    while (l <= r)
    {
        ll mid = l + r >> 1;
        if (check(mid) < m)
            l = mid + 1;
        else
            r = mid - 1, ans = cost;
    }
    cout << ans;
    return 0;
}
```

---

