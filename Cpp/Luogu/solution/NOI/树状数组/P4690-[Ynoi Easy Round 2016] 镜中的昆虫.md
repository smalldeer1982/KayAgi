# [Ynoi Easy Round 2016] 镜中的昆虫

## 题目背景

镜子的世界里会有美丽的东西吗？

镜子的世界里会有快乐的事情吗？

镜子世界的我，像我一样摆着一副无聊的表情

——出自《镜之国的爱丽丝》

![](https://cdn.luogu.com.cn/upload/pic/21104.png)

两个少女的战斗故事

文学代表强烈的意志，化学是对抗物理世界的力量

她们只有这两样对抗现实的武器

![](https://cdn.luogu.com.cn/upload/pic/21105.png)

啊，勒布雷！

我今天要登上乳白色的月球了！

不需要发明是机器，真是如此，我要一跃而出！

没错朋友！那个月亮的世界！

才是为我们创造的世界！

不止一个我所爱的人，大概都被放逐到那里...然后在等着我...

苏格拉底！伽利略！

物质的基本要素的灵魂就是...

这是...不，这有问题...哥白尼说过！

没错朋友们，究竟为何，会中了魔障？

究竟为何，会中了魔障，他到底去双桅战船上干什么呢？

作为哲学家！

物理学家！

诗人！

剑客！

音乐家！

空中旅行家！

针尖对麦芒的辩士！

他无所不能

作为至高...但是...

却又一事无成...

...没错，你们这些家伙，想夺走我的一切！

...来，夺走吧，夺走就是了...

但是...无论你们再怎么叫嚷，在去往新世界的路上，我还是会带走一个！

让我看看你坚强的心吧！

没错，你帽子上的羽饰！

象征你内心的勇气的纹章...毛子上的羽饰！

对不起，我该走了，我不能让人久等！

你们看...月亮来迎接我了！

Mon panache！

![](https://cdn.luogu.com.cn/upload/pic/21106.png)

我往空中踏出一步

两人拼命地想要拉住我

但是我往空中踏出一步

没错

我要为了崭新的世界，从天而降

为了获得新的力量

为了新的真实

我踏出了这一步

从手上，感到了两人的颤抖

没关系...

我在你们身边！

Sora！

![](https://cdn.luogu.com.cn/upload/pic/21109.png)

我完全投身于空中

我的身体瞬间从空中向地面落去

我紧紧地握住两人手腕，拉着两人

看见两人的表情...

她们边哭边笑...

似乎很害怕...

却又似很高兴的表情...

啊...

什么嘛，飞翔好舒服啊

宛如变成了天使一般...

好快的速度...

好快的风...

但是却听不见声音...

世界在静静地回转

已经，马上就要到地面了...

空气力学的先驱者...

我知道一切都在回转的天空，

还有包容着我的大地

还差一点，就抵达世界了...

还差一点，就抵达地面了...

接近着的影子

地面映出我的身影


## 题目描述

您正在欣赏 galgame 的 HS，然后游戏崩溃了，于是您只能做数据结构题了：

维护一个长为 $n$ 的序列 $a_i$，有 $m$ 次操作。

1. 将区间 $[l,r]$ 的值修改为 $x$。

2. 询问区间 $[l,r]$ 出现了多少种不同的数，也就是说同一个数出现多次只算一个。


## 说明/提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

$1\leq n , m \leq 10^5$，$1\leq a_i\leq 10^9$。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
2 1 5
1 2 3 4
2 1 5
2 3 3
2 2 4```

### 输出

```
5
3
1
1```

# 题解

## 作者：shadowice1984 (赞：83)

普通数据结构题……

注意通过封装以及分好函数来规避分情况讨论的尴尬情况……，不然你会死的很惨

_____________________

# 本题题解

题目简单明了区间赋值区间数颜色

但是这个东西乍一看是十分不可做的，所以让我们先来想一个这个问题的弱化版本作为启发…
____________________

### 单点修改区间数颜色

那么对于区间数颜色问题我们是有一个非常明确的套路的，就是只数这个区间里某种颜色最左边的点，这样的话每种颜色只会被数到过一次

具体实现上来讲我们可以处理一个$pre$数组，其中$pre_{i}$表示i左侧第一个和他同色点的位置，如果没有的$pre_{i}=0$

这样的话询问$[l,r]$区间里的颜色个数等价于询问$[l,r]$区间里有多少个点的$pre$值小于$l$，因为这些$pre$值小于l的点都是自己这个颜色的左边第一个点，所以这样数颜色就可以不重不漏的数完每一个颜色

然后接下来要支持静态的询问就不是非常困难了，无论是用主席树维护一下还是把询问离线一下用线段树维护都可以，你可以认为我们是将$(i,pre_{i})$看作二维平面上的一个点，每次数颜色相当于是询问$[l,r][0,l)$这个矩形里有多少个点，从而将问题转化为了一个经典的二维数点问题

问题来了，我们现在要支持单点修改，该怎么做呢？

发现一件事情是我们更改一个点的颜色的时候这个点的pre值会改变，并且pre值是这个点的点的pre值也会发生改变(也就是这个点右侧第一个和他同色的点的pre值会改变),但是除此之外没有别的点的pre值会发生改变了，这样的话我们一次操作只需要修改$O(1)$个点的pre值就可以了

我们每种颜色开一个set,然后这样的话我们就可以查出修改的的右侧第一个和他同色的点的是谁，然后我们修改pre值的话相当于在二维平面上插入一个点并删去一个点具体来讲我们把i的pre值修改为val的时候在$(i,pre_{i})$单点-1一下然后在$(i,val)$这个位置单点+1一下就行了

然后这就是经典的带修改二维数点问题了

写二维线段树？常数大的不行而且由于一次修改需要拆成4次单点加减法操作稍微多些稍不留神就mle了

为什么不试试神奇的cdq分治呢？常数小省空间还跑到快

我们发现每一个点修改会对时间在他之后的一个矩形询问产生+1/-1/0的贡献(取决于这个点到底在不在矩形里面)

而这样的关系有$O(n^2)$种，因此我们对这些修改-询问关系进行分治

假设我们现在处理时间在$(l,r)$这段区间的修改-询问关系

那么我们可以按照修改-询问关系是否跨越$(l,r)$的中点mid进行分类，所以我们先递归的考虑$(l,mid)$的修改-询问关系。递归然后考虑$(mid,r)$的修改-询问关系

现在考虑所有跨越了mid的修改询问关系，我们发现这相当于是先做了$(l,mid)$之前的所有修改然后做了$(mid,r)$的所有询问工作，换句话说我们此时的问题是个彻头彻尾的静态问题……

那么将所有修改按照$pre$进行排序，将所有询问按照$l$进行排序，然后开始处理每一个询问，将所有$pre$值小于这个询问的$l$的修改，都插到树状数组里面
(插入方法是如果这个修改是将$(i,pre)$这个点添加/删去，那么就在树状数组i这个位置单点+1/-1)

此时我们在树状数组上区间求一下和就可以算出$(l,mid)$所有的修改对这个询问的贡献了

由于所有修改已经按照pre值排好序，所有询问已经按照l排好序，所以我们可以使用双指针的形式来不停的向树状数组插入点，总插入量$O(n)$

此时我们的时间复杂度是$T(n)=T(\lfloor \frac{n}{2} \rfloor)+T(\lceil \frac{n}{2} \rceil)+O(nlogn)=O(nlog^2n)$的

具体写的时候你会发现可能为了排序只能写一个5元组结构体出来(因为询问是$(time,l,r,ans)$而修改是$(time,pos,pre,val)$这个4个参数，为了区分类型可能还得加一个type属性)这会导致修改和询问只能凑合着用同一组变量名，十分的不清真。

那么这里我们可以有一个代码上的trick可以让你不用写一个5元组结构体，而是询问写一个4元组，修改写一个4元组，变量名会变得比较清真的写法

就是我们写cdq的solve函数的时候不传$(l,r)$这个参表示我们分治$(l,r)$这段操作序列而是传6个参$(l1,r1),(l2,r2),(L,R)$表示分治时间范围在$(L,R]$的操作序列，其中修改部分的序列是$(l1,r1]$而询问部分的序列是$(l2,r2]$,然后每次分治的时候先求出$(L,R]$中点的$MID$，然后分别求出修改序列和询问序列时间比$MID$小的部分$(l1,mid1]$和$(l2,mid2]$那么比$MID$大的部分就是$(mid1,r1]$和$(mid2,r2]$了，此时我们就可以递归的向两侧分治了

这样写的话并不需要将修改和询问塞到同一个数组里面而是可以将修改存一个数组，询问存一个数组，同时对两个序列进行分治因此自然可以开两个结构体，不仅变量名清真而且处理贡献的时候不用判节点的类型了。
__________________________

### 区间赋值区间数颜色

## 结论:

## 对一个长度为n的数组进行m次区间赋值操作，pre数组的改变次数为$O(n+m)$级别

~~好了有了这个结论我们可以直接cdq了，每次区间赋值拆成暴力单点的pre值改变即可~~

乍一看这个结论相当的不可接受，明明我单次修改了$O(n)$个点的颜色到头来你告诉我总改变次数是$O(n+m)$级别的？

~~当你觉得一个东西复杂度相当诡异的时候他一定是用了摊还分析，比如splay，比如lct~~

所以我们也用摊还分析来证明这个东西的复杂度是对的

先来考虑一下pre数组的定义，左侧第一个和i同色点的位置

所以如果有一个内部的点的颜色相同的区间，此时我们将这个区间的颜色整体赋值成一个别的颜色，那么只有这个区间左端点的pre值以及右端点右侧第一个同色点的pre值会变，对于其他的点，因为左边的点换完颜色之后还是同色的，pre值保持$i-1$不变

根据这个性质，我们将颜色相同的一段看成一个点

那么我们的区间赋值相当于执行删去$(l,r)$中的所有点,然后插入$(l,r)$这个点这个操作(可能我们的l,r落在了一个区间里面而不是包含这个区间，那么我们可以将这个节点从l处或者从r断开，拆成两个节点)

根据刚才的结论，$pre_{i}$的改变次数应该是O(删去节点个数)的，问题来了，一开始节点有n个，每次区间赋值最多插入3个节点，每个节点最多被删除一次，那么我们删除的总节点个数就是$O(n+m)$级别的，从而pre的改变此时就是$O(n+m)$级别的了……

具体来讲我们每个区间缩成一个点存到set里面，当区间赋值的时候首先split两下左端点和右端点所在的块，将他们从l和r这两个位置断成两个块,之后删除l，r之间的所有块,最后将$(l,r)$这个块插到set里面，总复杂度$O((n+m)logn)$，至于插入和删除时pre到底变成了谁可以每种颜色开一个set单独维护一下，注意保持每种颜色开的set和存储整个序列的set是同步的，否则你的pre的改变量就炸掉了

然后就是实现时候的细节了，我们需要注意的是，请不要妄想你可以一遍插入删除一遍维护好pre的变化，这样会导致你的代码又臭又长充斥分情况讨论

正确的写法的是修改的时候把所有可能pre值变动的点，也就是被删掉块的左端点和被删掉(插入)块在自己颜色的set里的后继的左端点，丢到一个set里面，在修改结束之后挨个去查这些点的pre值都变成了什么，具体来讲先在维护序列的set里面查一下这个点的颜色，如果这个点不是左端点的话pre就是i-1，否则到自己的颜色里面取查前驱，pre值就是前驱的右端点

处理好pre值的变化之后直接去套单点修改时的cdq代码就可以解决问题了


上代码~


```C
#include<cstdio>
#include<algorithm>
#include<set>
#include<map> 
#define SNI set <nod> :: iterator 
#define SDI set <data> :: iterator 
using namespace std;const int N=1e5+10;int n;int m;int pre[N];int npre[N];int a[N];int tp[N];int lf[N];int rt[N];int co[N];
struct modi{int t;int pos;int pre;int va;friend bool operator <(modi a,modi b){return a.pre<b.pre;}}md[10*N];int tp1;
struct qry{int t;int l;int r;int ans;friend bool operator <(qry a,qry b){return a.l<b.l;}}qr[N];int tp2;int cnt;
inline bool cmp(const qry& a,const qry& b){return a.t<b.t;}
inline void modify(int pos,int co)//修改函数
{
	if(npre[pos]==co)return;md[++tp1]=(modi){++cnt,pos,npre[pos],-1};
	md[++tp1]=(modi){++cnt,pos,npre[pos]=co,1};
}
namespace prew
{
	int lst[2*N];map <int,int> mp;//提前离散化
	inline void prew()
	{
		scanf("%d%d",&n,&m);for(int i=1;i<=n;i++)scanf("%d",&a[i]),mp[a[i]]=1;
		for(int i=1;i<=m;i++){scanf("%d%d%d",&tp[i],&lf[i],&rt[i]);if(tp[i]==1)scanf("%d",&co[i]),mp[co[i]]=1;}
		map <int,int> :: iterator it,it1;
		for(it=mp.begin(),it1=it,++it1;it1!=mp.end();++it,++it1)it1->second+=it->second;
		for(int i=1;i<=n;i++)a[i]=mp[a[i]];for(int i=1;i<=m;i++)if(tp[i]==1)co[i]=mp[co[i]];
		for(int i=1;i<=n;i++)pre[i]=lst[a[i]],lst[a[i]]=i;for(int i=1;i<=n;i++)npre[i]=pre[i];
	}
}
namespace colist
{
    struct data {int l;int r;int x;friend bool operator <(data a,data b){return a.r<b.r;}};set <data> s;
    struct nod {int l;int r;friend bool operator <(nod a,nod b){return a.r<b.r;}};set <nod> c[2*N];set <int> bd;
    inline void split(int mid)//将一个节点拆成两个节点
    {
    	SDI it=s.lower_bound((data){0,mid,0});data p=*it;if(mid==p.r)return;
		s.erase(p);s.insert((data){p.l,mid,p.x});s.insert((data){mid+1,p.r,p.x});
    	c[p.x].erase((nod){p.l,p.r});c[p.x].insert((nod){p.l,mid});c[p.x].insert((nod){mid+1,p.r});
	}
	inline void del(set <data> :: iterator it)//删除一个迭代器
	{
		bd.insert(it->l);SNI it1,it2;it1=it2=c[it->x].find((nod){it->l,it->r});
		++it2;if(it2!=c[it->x].end())bd.insert(it2->l);c[it->x].erase(it1);s.erase(it);
	}
	inline void ins(data p)//插入一个节点
	{
		s.insert(p);SNI it=c[p.x].insert((nod){p.l,p.r}).first;++it;
		if(it!=c[p.x].end()){bd.insert(it->l);}
	}
	inline void stv(int l,int r,int x)//区间赋值
	{
		if(l!=1)split(l-1);split(r);int p=l;//split两下之后删掉所有区间
		while(p!=r+1){SDI it=s.lower_bound((data){0,p,0});p=it->r+1;del(it);}
		ins((data){l,r,x});//扫一遍set处理所有变化的pre值
		for(set <int> :: iterator it=bd.begin();it!=bd.end();++it)
		{
			SDI it1=s.lower_bound((data){0,*it,0});
			if(*it!=it1->l)modify(*it,*it-1);
			else
			{
				SNI it2=c[it1->x].lower_bound((nod){0,*it});
				if(it2!=c[it1->x].begin())--it2,modify(*it,it2->r);else modify(*it,0);
			}
		}bd.clear();
	}
	inline void ih()
	{
		int nc=a[1];int ccnt=1;//将连续的一段插入到set中
		for(int i=2;i<=n;i++)
			if(nc!=a[i]){s.insert((data){i-ccnt,i-1,nc}),c[nc].insert((nod){i-ccnt,i-1});nc=a[i];ccnt=1;}
			else {ccnt++;} s.insert((data){n-ccnt+1,n,a[n]}),c[a[n]].insert((nod){n-ccnt+1,n});
	}
}
namespace cdq
{   
    struct treearray//树状数组
    {
        int ta[N];
        inline void c(int x,int t){for(;x<=n;x+=x&(-x))ta[x]+=t;}
        inline void d(int x){for(;x<=n;x+=x&(-x))ta[x]=0;}
        inline int  q(int x){int r=0;for(;x;x-=x&(-x))r+=ta[x];return r;}
        inline void clear(){for(int i=1;i<=n;i++)ta[i]=0;}
    }ta;int srt[N];
    inline bool cmp1(const int& a,const int& b){return pre[a]<pre[b];}
    inline void solve(int l1,int r1,int l2,int r2,int L,int R)//cdq
    {
        if(l1==r1||l2==r2)return;int mid=(L+R)/2;
        int mid1=l1;while(mid1!=r1&&md[mid1+1].t<=mid)mid1++;
        int mid2=l2;while(mid2!=r2&&qr[mid2+1].t<=mid)mid2++;
        solve(l1,mid1,l2,mid2,L,mid);solve(mid1,r1,mid2,r2,mid,R);
        if(l1!=mid1&&mid2!=r2)
        {
            sort(md+l1+1,md+mid1+1);sort(qr+mid2+1,qr+r2+1);
            for(int i=mid2+1,j=l1+1;i<=r2;i++)//考虑左侧对右侧贡献
            {
                while(j<=mid1&&md[j].pre<qr[i].l)ta.c(md[j].pos,md[j].va),j++;
                qr[i].ans+=ta.q(qr[i].r)-ta.q(qr[i].l-1);
            }for(int i=l1+1;i<=mid1;i++)ta.d(md[i].pos);
        }
    }
	inline void mainsolve()
	{
		colist::ih();for(int i=1;i<=m;i++)
			if(tp[i]==1)colist::stv(lf[i],rt[i],co[i]);else qr[++tp2]=(qry){++cnt,lf[i],rt[i],0};
		sort(qr+1,qr+tp2+1);for(int i=1;i<=n;i++)srt[i]=i;sort(srt+1,srt+n+1,cmp1);
		for(int i=1,j=1;i<=tp2;i++)//初始化一下每个询问的值
		{
			while(j<=n&&pre[srt[j]]<qr[i].l)ta.c(srt[j],1),j++;
			qr[i].ans+=ta.q(qr[i].r)-ta.q(qr[i].l-1);
		}ta.clear();sort(qr+1,qr+tp2+1,cmp);solve(0,tp1,0,tp2,0,cnt);sort(qr+1,qr+tp2+1,cmp);
		for(int i=1;i<=tp2;i++)printf("%d\n",qr[i].ans);
	}
}
int main(){prew::prew();cdq::mainsolve();return 0;}//拜拜程序~
```




















---

## 作者：251Sec (赞：36)

神仙题，orz lxl。

## 不带修

先考虑不带修怎么做，即 [P1972](/problem/P1972)，我们对每个点维护 $pre_i$ 代表与它颜色相同且下标在它之前的，下标最大的点的下标。（好绕口）

那么我们对于一个区间询问，考虑对于每种颜色，只统计它在区间中出现的最左边一次，也就是查询有多少 $l \leq i \leq r$，满足 $pre_i<l$。那么我们可以作二维偏序来得到答案。

## 单点修

有了不带修的做法，单点修改的做法就很显然了。注意到进行一次单点修改对 $pre$ 数组的影响是 $O(1)$ 的。因此我们把一次单点修改变成一次删除和一次插入，这样就是在二维偏序的基础上加了时间维。因此我们可以作三维偏序。CDQ 分治即可。

## 区间修

先扔一个结论：进行所有区间修改后，$pre$ 数组的单点修改次数是 $O(n+m)$ 的。

凭啥？我们设 $\{a_n\}$ 一个值域相同的极长连续段为一个「节点」。注意到如果一个节点整体赋上一个值，那么只有节点中第一个数的 $pre$ 会被修改。

考虑 ODT 的过程，每次修改，我们先将两端的节点分裂，然后我们将中间的节点删掉，再换成同一个节点。

分裂和更换的过程，就是删除若干节点，再添加至多三个节点。对 $pre$ 数组的修改次数和删除的节点个数同阶。而每个节点至多删除一次，我们添加的节点个数是 $O(m)$ 的，初始的节点个数是 $O(n)$ 的。因此，$pre$ 数组的单点修改次数是 $O(n+m)$ 的。

既然这样，我们就只需要找到 $pre$ 数组被修改的位置和时间，然后按照单点修改的方式做就好了！

怎么找呢？其实就是上面复杂度分析那个过程。我们直接拿个 ODT 维护，然后每次修改就可以找出若干可能被修改的节点，然后对这些节点求修改后的 $pre$ 即可。怎么求 $pre$？我们对每种颜色开个 ODT 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
map<int, int> mp;
int mcnt;
struct Node {
    int x, y, t, v, id;
} q[1500005];
bool cmpByT(const Node &a, const Node &b) {
    return a.t != b.t ? a.t < b.t : a.id < b.id;
}
bool cmpByX(const Node &a, const Node &b) {
    return a.x != b.x ? a.x < b.x : a.id < b.id;
}
int qcnt;
int pre[200005];
struct ODTNode {
    int l, r, v;
    bool operator<(const ODTNode &o) const {
        return l < o.l;
    }
};
struct ODT {
    typedef set<ODTNode>::iterator iter;
    set<ODTNode> tr, col[200005];
    iter Insert(int l, int r, int v) {
        col[v].insert({ l, r, v });
        return tr.insert({ l, r, v }).first;
    }
    void Delete(int l, int r, int v) {
        col[v].erase({ l, r, v });
        tr.erase({ l, r, v });
    }
    iter Split(int p) {
        iter it = tr.lower_bound({ p, 0, 0 });
        if (it != tr.end() && it->l == p) return it;
        it--;
        int l = it->l, r = it->r, v = it->v;
        Delete(l, r, v);
        Insert(l, p - 1, v);
        return Insert(p, r, v);
    }
    int Pre(int p) {
        iter it = --tr.upper_bound({ p, 0, 0 });
        if (it->l < p) return p - 1;
        else {
            iter co = col[it->v].lower_bound({ p, 0, 0 });
            if (co != col[it->v].begin()) return (--co)->r;
            return 0;
        }
    }
    void Assign(int l, int r, int v, int t) {
        iter itr = Split(r + 1), itl = Split(l);
        vector<int> ps;
        for (iter it = itl; it != itr; it++) {
            if (it != itl) ps.emplace_back(it->l);
            iter nxt = col[it->v].upper_bound(*it);
            if (nxt != col[it->v].end()) ps.emplace_back(nxt->l);
            col[it->v].erase(*it);
        }
        tr.erase(itl, itr);
        Insert(l, r, v);
        ps.emplace_back(l);
        iter nxt = col[v].upper_bound({ l, r, v });
        if (nxt != col[v].end()) ps.emplace_back(nxt->l);
        for (int i = 0; i < ps.size(); i++) {
            q[++qcnt] = { ps[i], pre[ps[i]], t, -1, 0 };
            pre[ps[i]] = Pre(ps[i]);
            q[++qcnt] = { ps[i], pre[ps[i]], t, 1, 0 };
        }
    }
} odt;
struct BIT {
    int f[100005];
    BIT() {
        memset(f, 0, sizeof(f));
    }
    int lowbit(int x) { return x & -x; }
    void Modify(int i, int x) {
        for (; i <= 100001; i += lowbit(i)) f[i] += x;
    }
    int Query(int i) {
        int res = 0;
        for (; i; i -= lowbit(i)) res += f[i];
        return res;
    }
} bit;
int a[100005], las[200005];
int ans[100005], acnt;
void CDQ(int l, int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid); CDQ(mid + 1, r);
    int i = l, j = mid + 1;
    while (j <= r) {
        while (i <= mid && q[i].x <= q[j].x) {
            if (!q[i].id) bit.Modify(q[i].y + 1, q[i].v);
            i++;
        }
        if (q[j].id) ans[q[j].id] += bit.Query(q[j].y + 1) * q[j].v;
        j++;
    }
    for (int k = l; k < i; k++) if (!q[k].id) bit.Modify(q[k].y + 1, -q[k].v);
    inplace_merge(q + l, q + mid + 1, q + r + 1, cmpByX);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (!mp[a[i]]) mp[a[i]] = ++mcnt;
        a[i] = mp[a[i]];
        pre[i] = las[a[i]];
        las[a[i]] = i;
        q[++qcnt] = { i, pre[i], 0, 1, 0 };
        odt.Insert(i, i, a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r, v;
            scanf("%d%d%d", &l, &r, &v);
            if (!mp[v]) mp[v] = ++mcnt;
            v = mp[v];
            odt.Assign(l, r, v, i);
        }
        else {
            int l, r;
            scanf("%d%d", &l, &r);
            q[++qcnt] = { r, l - 1, i, 1, ++acnt };
            q[++qcnt] = { l - 1, l - 1, i, -1, acnt };
        }
    }
    sort(q + 1, q + qcnt + 1, cmpByT);
    CDQ(1, qcnt);
    for (int i = 1; i <= acnt; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
```

ODT 的实现参考了 Sol1 的题解。

---

## 作者：Ynoi (赞：28)

## update on 2020.3.8
## 时空开小后使用了$O(n)$空间的分块

juruo第一次给Ynoi写题解啊

这里提供一个$nsqrt(n)$的做法

我们定义$f[i]$表示$i$后面第一个与$i$颜色相同的位置的下标

（如果没有，我们认为$f[i] = n+1$）

这个我们可以开一个$set$维护每一段里同一种颜色的，另外再对于每种颜色分别开个$set$维护,然后$f$的修改次数是$O(n+m)$的。

这个我就不详细说了，别的题解也有。

这里主要讲下分块怎么维护

（我看其他dalao有写树套树的，我这个蒟蒻树套树还不太熟练，于是写了个分块）

每次询问我们的答案，就是$[l,r]$里$f$值$>=r$的数的个数

我们对于整个序列分块，块里维护$f$值。对于块里，我们现在要求这么一个东西：

> 单点修改

> 查询整体 >= r 的个数

因为$f$ 的值域是$[1,n]$，所以说我们可以维护块内前缀和，就是
块内f值在$[1,i]$内的数的个数

这个如果我们用树状数组维护，再调整块大小，可以

$n\sqrt{nlogn}$解决

（没写过不知道能不能过

当然，也有更好的方法

我们在块里再来一个分块

要求达到一个基本操作

> O(1)前缀和

> O(sqrt(n)) 修改

这个很简单，我们维护每个数在块中的前缀和，和每个块结尾的前缀和即可

这个还是放下代码吧

```
    inline void add(int x,int y)
    {
    	for(int i = c[x]; i <= mm; i ++)
			s[i] += y;
		for(int i = x; c[i] == c[x]; i ++)
			ss[i] += y; 
	  }

    inline int sum(int x) {
    	return ss[x] + s[c[x]-1];
    }
```


这样我们就达到了$n\sqrt{n}$

这个做法应该还是比树套树写着方便很多的

好了，下面是完整代码
```

#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define se set<aa>
#define it iterator
#define lb lowber_bound

int n,m,nn,mm,sb;
map<int,int>p;
int a[MAXN],f[MAXN],u[MAXN],tt[MAXN];
int c[MAXN],d[MAXN]; 
struct aa
{
    int l,r,v;
};
set<aa>s[MAXN];

bool operator <(aa a,aa b) {
    return a.r < b.r;
}

set<aa>odt;

void fenkuai() 
{
	sb = sqrt(n);
	for(int i = 1; i <= n+1; i ++) {
		if(i%sb == 1) {
			c[i] = c[i-1]+1;
			d[i] = 1;
		} else {
			c[i] = c[i-1];
			d[i] = d[i-1]+1;
		}
	}
	mm = c[n];
}

struct kuai
{
    int s[MAXN],ss[MAXN];

    inline void jia(int x,int y)
    {
    	for(int i = c[x]; i <= mm; i ++)
			s[i] += y;
		for(int i = x; c[i] == c[x]; i ++)
			ss[i] += y; 
	}

    inline int sum(int x) {
    	return ss[x] + s[c[x]-1];
    }
}b[355];

void rd()
{
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i ++)
        scanf("%d",&a[i]);
    for(int i = 1; i <= n; i ++)
    {
    	if(!p.count(a[i])) {
    		nn ++;
    		p[a[i]] = nn;
    		tt[nn] = a[i];
		}
		s[ p[a[i]] ].insert((aa){i,i,p[a[i]]});
	}
    fenkuai();
    for(int i = n; i >= 1; i --) {
    	int t = u[ p[a[i]] ];
    	if(t) f[i] = t;
    	else f[i] = n+1;
    	b[c[i]].jia(f[i],1);
		u[p[a[i]]] = i;
	}
	for(int i = 1; i <= n; i ++) {
		odt.insert((aa){i,i,p[a[i]]});
	} 
	
	for(int i = 1; i <= n*2; i ++) {
		s[i].insert((aa){n+1,n+1,i}); 
		s[i].insert((aa){0,0,i}); 
		
	}
} 

void split(se::it x,int i)
{
	int v = x->v,l = x->l,r = x->r;
	if(i < l || i >= r) return; 
	
	s[v].erase((aa){l,r,v});
	s[v].insert((aa){l,i,v});
	s[v].insert((aa){i+1,r,v});
	
	odt.erase(x);
	odt.insert((aa){l,i,v});
	odt.insert((aa){i+1,r,v});
}

aa qls(int v,int x) {
	se::it i = s[v].upper_bound((aa){0,x,0});
	i --;
	return (*i);
} 

void qf(int x,int y) {
	b[c[x]].jia(f[x],-1);
	f[x] = y; 
	b[c[x]].jia(f[x],1);
} 

void dlt(int l,int r,int v)
{
	s[v].erase((aa){l,r,v});
	aa ls = qls(v,l);
	aa rs = *s[v].lower_bound((aa){0,r,0});
	qf(r,r+1); 
	qf(ls.r,rs.l);
}

void jlt(int l,int r,int v)
{
	aa ls = qls(v,l);
	aa rs = *s[v].lower_bound((aa){0,r,0}); 
	s[v].insert((aa){l,r,v});
	qf(ls.r,l);
	qf(r,rs.l);
} 

void assign(int l,int r,int v)
{
	se::it x = odt.lower_bound((aa){0,l-1,0});
	split(x,l-1);
	
	se::it y = odt.lower_bound((aa){0,r,0});
	split(y,r);
	
	x = odt.lower_bound((aa){0,l,0});
	y = odt.lower_bound((aa){0,r+1,0});
	
	for(se::it i = x; i != y; ) {
		se::it j = i;
		i ++; 
		dlt(j->l,j->r,j->v);
		odt.erase(j);
	} 
	
	odt.insert((aa){l,r,v});
	jlt(l,r,v);
}

signed main()
{
    rd();
    for(int i = 1; i <= m; i ++)
    {
        int l,r,v,opt;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt == 1) {
	    	scanf("%d",&v);
		    if(!p.count(v)) {
	        	nn ++;
	        	p[v] = nn;
	        	tt[nn] = v;
			}
			assign(l,r,p[v]);
		} else {
			int ans = r-l+1;
			if(c[l] != c[r])
			{
				for(int j = c[l]+1; j <= c[r]-1; j ++) 
					ans -= b[j].sum(r);
				for(int j = l; c[l] == c[j]; j ++)
					ans -= (f[j] <= r);
				for(int j = r; c[r] == c[j]; j --)
					ans -= (f[j] <= r);
					
			} else {
				for(int j = l; j <= r; j ++)
					ans -= (f[j] <= r);
			}
			printf("%d\n",ans);
		}
	}
    return 0;
 } 

```

## Update 关于O(n)空间分块做法

还是当初[Juan_Feng](https://www.luogu.com.cn/user/66965)鸽鸽教我的qaq

考虑对询问分块，考虑每一个块的询问，我们会发现$r$只有$\sqrt n$种，那么我们就可以把按照$r$,把$f[i]$的值分成$\sqrt n$段，然后询问每个块完成后重构一下即可。

时间和与原来的做法差不多，但是空间小了很多

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define se set<aa>
#define it iterator
#define lb lowber_bound

int n,m,nn,mm,sb;
map<int,int>p;
int a[MAXN],f[MAXN],u[MAXN],tt[MAXN];
int c[MAXN],d[MAXN]; 
struct aa
{
    int l,r,v;
};
set<aa>s[MAXN];
struct op {
	int op,l,r,v;
}opt[MAXN]; 
int mr[MAXN],srz[MAXN],ak;

bool operator <(aa a,aa b) {
    return a.r < b.r;
}

set<aa>odt;

void fenkuai() 
{
	sb = sqrt(n);
	for(int i = 1; i <= n+1; i ++) {
		if(i%sb == 1) {
			c[i] = c[i-1]+1;
			d[i] = 1;
		} else {
			c[i] = c[i-1];
			d[i] = d[i-1]+1;
		}
	}
	mm = c[n];
}

struct kuai
{
    int s[355];

    inline void jia(int x,int y)//sqrt(n)
	  {
		if(srz[x] == 0) return; 
    	for(int i = srz[x]; i <= mm; i ++)
			s[i] += y;
	  }

    inline int sum(int x) {//O(1)
    	return s[x];
    }
}b[355];

inline int read()
{
    register int x = 0 , ch = getchar();
    while( !isdigit( ch ) ) ch = getchar();
    while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();
    return x;
}

void chonggou(int x)
{
	for(int i = 1; i <= c[n]; i ++)
		memset(b[i].s,0,sizeof(b[i].s));
	memset(srz,0,sizeof(srz));
	ak = 0;
	for(int i = x; i <= m && i <= x+sb-1; i ++)  
	if(opt[i].op == 2){
		ak ++;
		mr[ak] = opt[i].r+1;
		srz[mr[ak]] ++;
	}
	sort(mr+1,mr+ak+1);
	srz[1] ++;
	for(int i = 1; i <= n; i ++)
		srz[i] += srz[i-1];
	srz[n+1] = 0;
	for(int i = 1; i <= n; i ++) 
		b[c[i]].s[srz[f[i]]] ++;

	for(int i = 1; i <= mm; i ++)
		for(int j = 2; j <= mm; j ++)
			b[i].s[j] += b[i].s[j-1];
} 

void rd()
{
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i ++)
        scanf("%d",&a[i]);
    for(int i = 1; i <= m; i ++) {
    	opt[i].op = read();
    	opt[i].l = read();
    	opt[i].r = read();
    	
		if(opt[i].op == 1) {
    		opt[i].v = read();
		}
	}
    for(int i = 1; i <= n; i ++)
    {
    	if(!p.count(a[i])) {
    		nn ++;
    		p[a[i]] = nn;
    		tt[nn] = a[i];
		}
		s[ p[a[i]] ].insert((aa){i,i,p[a[i]]});
	}
    fenkuai();
    for(int i = n; i >= 1; i --) {
    	int t = u[ p[a[i]] ];
    	if(t) f[i] = t;
    	else f[i] = n+1;
    	b[c[i]].jia(f[i],1);
		u[p[a[i]]] = i;
	}
	chonggou(1);
	for(int i = 1; i <= n; i ++) {
		odt.insert((aa){i,i,p[a[i]]});
	} 
	for(int i = 1; i <= n*2; i ++) {
		s[i].insert((aa){n+1,n+1,i}); 
		s[i].insert((aa){0,0,i}); 
	}
} 

void split(se::it x,int i)
{
	int v = x->v,l = x->l,r = x->r;
	if(i < l || i >= r) return; 
	
	s[v].erase((aa){l,r,v});
	s[v].insert((aa){l,i,v});
	s[v].insert((aa){i+1,r,v});
	
	odt.erase(x);
	odt.insert((aa){l,i,v});
	odt.insert((aa){i+1,r,v});
}

aa qls(int v,int x) {
	se::it i = s[v].upper_bound((aa){0,x,0});
	i --;
	return (*i);
} 

inline void qf(int x,int y)
{
	if(x == 0) return;
	b[c[x]].jia(f[x],-1);
	f[x] = y; 
	b[c[x]].jia(f[x],1);
} 

void dlt(int l,int r,int v)
{
	s[v].erase((aa){l,r,v});
	aa ls = qls(v,l);
	aa rs = *s[v].lower_bound((aa){0,r,0});
	qf(r,r+1); 
	qf(ls.r,rs.l);
}

void jlt(int l,int r,int v)
{
	aa ls = qls(v,l);
	aa rs = *s[v].lower_bound((aa){0,r,0}); 
	s[v].insert((aa){l,r,v});
	qf(ls.r,l);
	qf(r,rs.l);
} 

void assign(int l,int r,int v)
{
	se::it x = odt.lower_bound((aa){0,l-1,0});
	split(x,l-1);
	se::it y = odt.lower_bound((aa){0,r,0});
	split(y,r);
	
	x = odt.lower_bound((aa){0,l,0});
	y = odt.lower_bound((aa){0,r+1,0});
	
	for(se::it i = x; i != y; ) {
		se::it j = i;
		i ++;
		dlt(j->l,j->r,j->v);
		odt.erase(j);
	} 
	
	odt.insert((aa){l,r,v});
	jlt(l,r,v);
}

signed main()
{
    rd();
    for(int i = 1; i <= m; i ++)
    {
        int l = opt[i].l,r = opt[i].r,v = opt[i].v,op = opt[i].op;
        if(op == 1) {
		    if(!p.count(v)) {
	        	nn ++;
	        	p[v] = nn;
	        	tt[nn] = v;
			}
			assign(l,r,p[v]);
		} else {
			int ans = r-l+1;
			if(c[l] != c[r])
			{
				int t = srz[r];
				for(int j = c[l]+1; j <= c[r]-1; j ++) 
					ans -= b[j].sum(t);
				for(int j = l; c[l] == c[j]; j ++)
					ans -= (f[j] <= r);
				for(int j = r; c[r] == c[j]; j --)
					ans -= (f[j] <= r);
			} else {
				for(int j = l; j <= r; j ++)
					ans -= (f[j] <= r);
			}
			printf("%d\n",ans);
		}

		if((i%sb) == 0) {
			chonggou(i+1);
		}
	}
    return 0;
 } 

```


---

## 作者：EnofTaiPeople (赞：21)

颜色段均摊有两层含义，都是建立在存在区间赋值（推平）操作的基础上。

1. 随机数据：任意时刻的颜色段个数期望 $O(\log_2n)$；
2. 非随机数据（本题）：每次推平时访问的颜色段个数为均摊 $O(n)$。

考虑本题有区间推平操作，所以使用珂朵莉树，然而我们发现数据不随机，所以暴力上珂朵莉树是 $O(n^2)$ 的，不要想着用这种方法过去。

因为要求的是不同颜色个数，我们可以用只算第一次出现的方法来计算，设 $pre_x=\max\limits_{(y<x\land a_y=a_x)\lor y=0}y$，即上一次出现或者它在数组里第一次出现，则为 $0$。

这个数组有什么用？发现 $x$ 在区间 $[l,r]$ 第一次出现当且仅当 $x\in[l,r],pre_x\in[0,l)$，于是就变成了典型的二维数点问题，可以用 CDQ 分治解决。

如何维护这个数组？因为每次推平操作时，每一个被删除的颜色段都会有 $O(1)$ 次修改，所以总修改数是 $O(n)$ 的，总复杂度为 $O(n\log_2^2n)$，具体实现时要用 `set` 维护每种颜色的当前存在段，以便删除段时更改后继左端点的 $pre$ 值：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
using ll=long long;
int n,QT,a[N],qt,rq,pr[N],mp[N],mt;
struct Q{int l,r,d,p;}q[N*6],q2[N*6];
struct odt{
    int l,r;mutable int d;
    bool operator<(const odt &z)
    const{return l<z.l;}
};
struct rag{
    int l,r;
    bool operator<(const rag &z)
    const{return r<z.r;}
};
void addp(int x,int d){q[++rq]={pr[x],x,d};}
void cgpr(int x,int y){
    if(pr[x]!=y)addp(x,-1),pr[x]=y,addp(x,1);
}
struct RGdt:set<rag>{
    void add(int l,int r){
        auto it=lower_bound({0,r});
        if(it!=end())cgpr(it->l,r);
        if(it!=begin())--it,cgpr(l,it->r);
        else cgpr(l,0);
        insert({l,r});
    }void del(int l,int r){
        erase({l,r});
        auto it=lower_bound({0,r});
        if(it!=end()){
            if(it!=begin()){
                auto at=it;--at;
                cgpr(it->l,at->r);
            }else cgpr(it->l,0);
        }
    }
}lt[N];
struct Odt:set<odt>{
    set<odt>::iterator split(int r){
        if(r>n)return end();
        auto it=lower_bound({r});
        if(it!=end()&&it->l==r)return it;
        --it;int L=it->l,R=it->r,D=it->d;
        lt[D].erase({L,R}),lt[D].insert({L,r-1});
        lt[D].insert({r,R});
        erase(it),insert({L,r-1,D});
        auto res=insert({r,R,D}).first;
        return res;
    }
}ADT;
ll ct[N],ans[N];
void solve(int l,int r){
    if(l>=r)return;
    int i,x,y,md=l+r>>1;
    solve(l,md),solve(md+1,r);
    for(x=md+1,y=l;x<=r;++x){
        while(y<=md&&q[y].l<=q[x].l){
            if(!q[y].p)for(i=q[y].r;i<=n;i+=i&-i)ct[i]+=q[y].d;++y;
        }if(q[x].p)for(i=q[x].r;i;i-=i&-i)ans[q[x].p]+=q[x].d*ct[i];
    }
    for(x=l;x<y;++x)
        if(!q[x].p)for(i=q[x].r;i<=n;i+=i&-i)ct[i]-=q[x].d;
    merge(q+l,q+md+1,q+md+1,q+r+1,q2+l,[&](Q x,Q y){
        return x.l<y.l;
    });for(i=l;i<=r;++i)q[i]=q2[i];
}
int main(){
    ios::sync_with_stdio(false);
    int i,j,A,l,r,d,qi;cin>>n>>QT;
    for(i=1;i<=n;++i)cin>>a[i],mp[++mt]=a[i];
    for(qi=1;qi<=QT;++qi){
        cin>>q2[qi].p>>q2[qi].l>>q2[qi].r;
        if(q2[qi].p==1){
            cin>>q2[qi].d;
            mp[++mt]=q2[qi].d;
        }
    }
    sort(mp+1,mp+mt+1),unique(mp+1,mp+mt+1)-mp-1;
    for(i=1;i<=n;++i)a[i]=lower_bound(mp+1,mp+mt+1,a[i])-mp;
    for(qi=1;qi<=QT;++qi)
        if(q2[qi].p==1)
            q2[qi].d=lower_bound(mp+1,mp+mt+1,q2[qi].d)-mp;
    for(i=1;i<=n;++i){
        ADT.insert({i,i,a[i]});
        if(lt[a[i]].size()){
            auto it=lt[a[i]].end();--it;
            pr[i]=it->r;
        }lt[a[i]].insert({i,i});
        addp(i,1);
    }
    for(qi=1;qi<=QT;++qi){
        A=q2[qi].p,l=q2[qi].l,r=q2[qi].r,d=q2[qi].d;
        if(A==1){
            auto R=ADT.split(r+1),L=ADT.split(l);
            auto it=L;lt[it->d].del(it->l,it->r);
            for(++it;it!=R;++it)cgpr(it->l,it->l-1),lt[it->d].del(it->l,it->r);
            ADT.erase(L,R);
            ADT.insert({l,r,d});
            lt[d].add(l,r);
        }else{
            ++qt,q[++rq]={l-1,r,1,qt};
            q[++rq]={l-1,l-1,-1,qt};
        }
    }solve(1,rq);
    for(i=1;i<=qt;++i)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：xfrvq (赞：18)

[$\tt Link$](/problem/P4690)

题意：区间推平，区间数颜色

这是一个非常清新的分块做法。

我们从弱化版开始谈起。

## 1. 区间数颜色

$a_i\le10^9$，你首先得想离散化吧。考虑一种方便的写法，即直接使用 `map` 维护每个值的离散化后的结果。如果这个值第一次出现就给它放上一个新的离散值。

考虑维护每一个位置的 **上一个与其颜色相同的位置**，记为 $pre_i$。单次询问 $l,r$，就等价于求区间 $[l,r]$ 中有多少 $i$ 使得 $pre_i\lt l$。问题转化为 **求区间小于 $x$ 的数的个数**。

接下来就可以大显神通了。你可以直接主席树，也可以离线后上值域树状数组。

## 2. 单点修改区间数颜色

~~带修莫队？$\sout{O(n^{\frac 53})}$ 的复杂度，您想想还是算了吧~~。

考虑在第一问的解法上修改。我们维护 $nxt_i$ 代表 **下一个与其相同颜色的位置**。想想 $i$ 位置的改变会影响哪些位置。$pre_i$ 显然会被改变，$pre_{nxt_i}$ 变成 $pre_i$。

但是…怎么计算更改后的 $pre_i$ 呢？考虑维护 $n+m$ 个 `set`，记录每种颜色所有出现过的位置，这样修改暴力 在 `set` 里面 `insert()/erase()`，然后使用 `lower_bound` 来计算更改后的 $pre_i$。

因为要修改，那么主席树不行了，可以考虑 CDQ/树套树。

## 3. 区间修改区间数颜色

乍一看，直接弃掉，这个东西没法做了。

但是你注意到一个性质：如果本来有一个区间 $[l,r]$ 颜色相同，我们要把它整体改成另一个颜色，那么只有 $prv_l$ 会发生改变（同样要变的还有这个区间右端第一个同色点），$prv_{l+1},\cdots,prv_r$ 保持不变，它们应该是 $l,l+1,\cdots,r-1$ 的一个等差数列。

既然问题和区间推平有关，这个性质和 **颜色相同的区间** 有关，那么我们来考虑一个老朋友—— $\tt ODT$，然后我们 **把所有颜色相同的区间看成一个点**。

如果我们使用上述方法对一个点进行修改，那么复杂度是不是就正确了呢？考虑证明复杂度正确。

+ 首先可知一开始 $\tt ODT$ 内有 $n$ 个点。
+ 每次修改
	1. 把 $l$ 以及 $r+1$ 所在节点断开，一分为二。这一步最坏增加两个节点。
	1. 然后删去属于这个区间的所有节点
	1. 然后增加一个节点 $[l,r]$。

注意到两点

+ 每次操作最坏增加三个节点（第一步两个，第三步一个），总量是 $O(m)$ 个。
+ 第二步删去的节点总数是 $O(n)$ 个。

于是所有修改的总数是 $O(n+m)$。

## 4. 区间修改怎么写

在上文有提到过维护 $n+m$ 个 `set`，记为 $t$ 数组。但是要记得维护成 $\tt ODT$ 节点的形式。

1. 我们首先提取出 $l\sim r$ 的所有 $\tt ODT$ 结点
1. 然后我们扫描 $l\sim r$ 的所有节点，把所有要修改的位置装进一个桶里
1. 注意你要修改的位置不仅仅是每个节点的左端点，还有这个节点的下一个相同值的位置（这个位置可以使用我们的 $t$ 数组进行 `lower_bound/upper_bound` 算出）
1. 删除 $t$ 里面的和 $\tt ODT$ 里面的所有这个区间内的节点
1. 最后逐一处理我们提取出来的要修改的位置，修改它。

## 5. 单点修改区间数颜色的线性空间写法

你当然可以考虑树套树，但是 ~~我不会~~ 这题卡空间。  
你当然也可以考虑 CDQ，但是个人感觉分块写法简单的多。

我们把空间限制去掉，原问题是这样的：

+ 单点修改
+ 询问区间值 $\lt x$ 的数的个数。

这个题有一个比较显然的 序列分块+值域分块 的做法

> 注：这里的值域指的是 $prv$ 的值的范围（即 $0\sim n-1$）。在值域和 $n$ 有区别的时候，需要对于值域和序列处理两套分块辅助数组，这会比较麻烦。这题值域有特殊性质，所以考虑将其整体 $+1$，然后和序列共用一个分块辅助数组。

考虑序列分块部分在散块暴力，只想整块，那么原问题变为如此：

+ 单点修改
+ 询问全局值 $\lt x$ 的数的个数（注意留给这一步的时间是 $O(1)$）

那么这就很简单了，它变成一个 $O(\sqrt n)$ 单点修改 $O(\sqrt n)$ 前缀（区间）和查询，直接莽上值域分块分块，这里空间是值域的 $O(n)$。

然后每个块都来一个这样的值域分块，时空都是 $O(n\sqrt n)$。

~~然后我就在这里卡住了~~。

作为大口胡选手，我首先考虑了 Ynoi 常见套路 **离线后滚块**：对所有操作的位置进行分块，枚举块然后处理包含这个块的操作。

然后就口胡挂了，因为可能不属于这个区间的修改，也会影响到这个区间的 $prv$ 值。

然后去看 sol，发现了 [$\texttt{\color{black}Y\color{red}noi}$](https://www.luogu.com.cn/user/124721) 大佬的做法：对询问而非询问的位置进行分块，但是！！哈哈我看不懂啊哈哈哈哈！！

于是想到此题解里区间修改的第 5 步：提取出所有要修改的位置进行修改。那么我们是不是可以把这些单点修改给存下来？（毕竟它的总数是 $O(n+m)$ 的）。

好，那就把所有的单点修改以及区间查询存下来，离线后滚块即可。

感觉这题卡不掉分块。

## 6. [代码](https://www.luogu.com.cn/paste/bubz6le0)

总时间复杂度 $O((n+m)(\sqrt n+\log n))$，空间复杂度 $O(n)$。

---

## 作者：BFqwq (赞：13)

# Ynoi2016 镜中的昆虫

**由于本题空间范围修改，该题解目前无法通过，但做法为正解的二维数点，仅供参考。**

（其实这道在Ynoi中还算简单）

首先，区间染色，想到珂朵莉树。但显然这题数据不可能随机。

接着我们来思考：在无修改的情况下（也就是[HH的项链](https://www.luogu.com.cn/problem/P1972)）我们是使用一个线段树或树状数组维护前驱的。

那么这道题的解法就是综合这两种思想：



我们考虑一个颜色，显然，我们只需要将这种颜色记录一次。

在静态中，我们是通过维护前驱完成的，那么在动态中，我们同样维护前驱。

记一个点左侧最靠右且与之颜色相同的点为 $pre$，若无则为 $0$，

那么我们只需要统计 $i\in[l,r]$ 且 $pre_i\in[0,l)$ 的点，因为这些点是这个区间中这个颜色的点中最靠左的那一个。

(这是个很显然的事实，因为如果这个点的 $pre_i\le l$ 那么 $pre_i$ 这一个点也属于 $[l,r]$ 且与之同色，并且更靠左)

将点在序列中的位置作为一维，前驱作为另一维，用树状数组套权值树维护。

在修改的时候，我们用珂朵莉树的思想，用 set 将同色的点结合成一个段，显然，一个段内的点出了最左侧的之外前驱均为 $i-1$。

每次修改的时候，我们将左右个端点所在的段拆分，然后暴力取出中间的段修改并将之合并为一个段。

采用摊还法，set 内初始有 $n$ 个段，修改时产生的段个数可以看成 $\operatorname{O}(m)$ （左右端点断开后新增的段），

那么修改次数的复杂度可以看成均摊的 $\operatorname{O}(n+m)=\operatorname{O}(n)$ （$n,m$ 同阶），单次修改复杂度 $\operatorname{O}(\log^2 n)$，总复杂度 $\operatorname{O}(n\log^2 n)$。

在具体实现的时候有几个小细节。第一个是权值线段树的下标要从 $0$ 开始，

第二个是我们在维护全局 set 的同时也对每个颜色各开一个 set 一起操作，这样会更方便。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
const int maxn=400005;
int len=0;
const int inf=2147483647;
struct node{
	int l,r,x;
	//node():l(0),r(0),x(0){}
	friend bool operator <(node a,node b){
		return a.l<b.l;
	}
}tp;
struct seg{
	int v,ls,rs;
}t[maxn*50];
int rt[maxn],n,m,tot,tem[maxn],tmp[maxn],cnt,num;
int lsh[maxn<<1],a[maxn],pre[maxn];
struct cz{
	int a,b,c,d;
}q[maxn];
set<node> s[maxn],al;
set<int> now;
set<node>:: iterator it;
set<int>:: iterator _it;
int lb(int x){
	return x&(-x);
}
void pushup(int o){
	t[o].v=t[t[o].ls].v+t[t[o].rs].v;
}
void change(int &o,int l,int r,int k,int v){
	if(!o) o=++tot;
	if(l==r){
		t[o].v+=v;
		return ;
	}
	int mid=l+r>>1;
	if(k<=mid) change(t[o].ls,l,mid,k,v);
	else change(t[o].rs,mid+1,r,k,v);
	pushup(o);
}
void add(int o,int v){
	for(int i=o;i<=n;i+=lb(i)) change(rt[i],0,n,pre[o],v);
}
int query(int l,int r,int k){
	if(l==r) {
		return 0;
	}
	int mid=l+r>>1,sum=0;
	if(k<=mid){
		for(int i=1;i<=cnt;i++) tem[i]=t[tem[i]].ls;
		for(int i=1;i<=num;i++) tmp[i]=t[tmp[i]].ls;
		return query(l,mid,k);
	}
	else{
		for(int i=1;i<=cnt;i++) sum+=t[t[tem[i]].ls].v,tem[i]=t[tem[i]].rs;
		for(int i=1;i<=num;i++) sum-=t[t[tmp[i]].ls].v,tmp[i]=t[tmp[i]].rs;
		return sum+query(mid+1,r,k);
	}
}
int find(int l,int r,int k){
	cnt=num=0;
	for(int i=r;i;i-=lb(i)){
		tem[++cnt]=rt[i];
	}
	for(int i=l-1;i;i-=lb(i)){
		tmp[++num]=rt[i];
	}
	return query(0,n,k);
}
void split(int x){
	tp=(node){x,0,0};
	it=al.upper_bound(tp);--it;
	if(it->l==x) return;
	tp=*it;
	al.erase(tp);s[tp.x].erase(tp);
	node tp1=(node){tp.l,x-1,tp.x};
	node tp2=(node){x,tp.r,tp.x};
	al.insert(tp1);al.insert(tp2);
	s[tp.x].insert(tp1);
	s[tp.x].insert(tp2);
}
void update(int l,int r,int x){
	if(l!=1) split(l);
	if(r+1<=n) split(r+1);
	now.insert(x);
	tp=(node){l,0,0};
	it=al.lower_bound(tp);
	while(it->l!=r+1){
		tp=*it;now.insert(tp.x);
		if(tp.l>l&&pre[tp.l]!=tp.l-1){
            add(tp.l,-1);
            pre[tp.l]=tp.l-1;
            add(tp.l,1);
        }
        al.erase(tp);s[tp.x].erase(tp);
		tp=(node){l,0,0};
		it=al.lower_bound(tp);
		if(it==al.end()) break;
	}
	tp=(node){l,0,0};
	it=s[x].lower_bound(tp);--it;
	add(l,-1);pre[l]=it->r;add(l,1);
	tp=(node){l,r,x};
	al.insert(tp);s[x].insert(tp);
	for(_it=now.begin();_it!=now.end();++_it){
		tp=(node){r,0,0};
		it=s[*_it].upper_bound(tp);
		if(it!=s[*_it].end()){
			l=it->l;
			tp=(node){l,0,0};
			it=s[*_it].lower_bound(tp);--it;
			add(l,-1);pre[l]=it->r;add(l,1);
		}
	}
	now.clear();
}
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();lsh[++len]=a[i];
	}
	for(int i=1;i<=m;i++){
		q[i].a=read();q[i].b=read();q[i].c=read();
		if(q[i].a==1){
			q[i].d=read();
			lsh[++len]=q[i].d;
		}
	}
	sort(lsh+1,lsh+len+1);
	len=unique(lsh+1,lsh+len+1)-lsh-1;
	tp=(node){0,0,0};
	for(int i=1;i<=len;i++)s[i].insert(tp);
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(lsh+1,lsh+1+len,a[i])-lsh;
		it=s[a[i]].end();it--;pre[i]=it->l;
		add(i,1);
		tp=(node){i,i,a[i]};
		al.insert(tp);s[a[i]].insert(tp);
	}
	for(int i=1;i<=m;i++){
		if(q[i].a==1){
			q[i].d=lower_bound(lsh+1,lsh+len+1,q[i].d)-lsh;
			update(q[i].b,q[i].c,q[i].d);
		}
		else{
			write(find(q[i].b,q[i].c,q[i].b));
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：FZzzz (赞：11)

好题。不过丢 Yn 里有点水了。

写了三（四？）天终于过了，写篇题解纪念一下。

------------
首先考虑单点修改区间数颜色咋做。

~~啥？你说带修莫队？$O(n^\frac53)$ 的复杂度，过了这题我请你吃糖。~~

正确姿势大概是带修莫队模板题里 xzz 神仙那个题解，每次修改的时候把修改需要修改的前驱。然后查询 $[l,r]$ 就是 $[l,r]$ 里有多少个点的前驱是小于 $l$ 的。树套树维护。

然后区间赋值就可以猜一个很显然并且很常见（？）的性质：所有点的前驱的改变次数之和为 $O(n)$。

用珂朵莉树的思想，~~读者自证不难~~。

这样我们就建珂朵莉树，和每种颜色的珂朵莉树，然后就可以做了。

要是你疯狂分类讨论你多半是调不出来的~~调出来我也请你吃糖~~，正确姿势是把所有需要修改的点存下来，最后一个个看要改成什么。

所有需要修改的点有：珂朵莉树所有被删掉的点的左端点，这些点在它们的颜色里的后继的左端点，插入的段在自己颜色里的后继的左端点。

然后就可以直接上树套树了。
```cpp
#include<set>
#include<map>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=1e5+5;
int n,m;
struct odt_node{
	int l,r,v;
	odt_node(int l,int r,int v):l(l),r(r),v(v){}
	bool operator <(odt_node b)const{
		return r<b.r;
	}
};
set<odt_node> s,s2[maxn*2];
typedef set<odt_node>::iterator iter;
iter split(set<odt_node>& s,int x){
	iter it=s.lower_bound(odt_node(x,x,0));
	if(it==s.end()||it->l>x) return it;
	odt_node res=*it;
	s.erase(res);
	if(x>res.l) s.insert(odt_node(res.l,x-1,res.v));
	return (s.insert(odt_node(x,res.r,res.v))).first;
}
int lst[maxn],pre[maxn];
struct treap_node{
	int v,s,r;
	treap_node* ch[2];
	treap_node(int x):v(x),s(1),r(rand()){
		ch[0]=ch[1]=0;
	}
	inline void pushup(){
		s=1;
		if(ch[0]) s+=ch[0]->s;
		if(ch[1]) s+=ch[1]->s;
	}
	int rank(int x){
		if(x<=v){
			if(ch[0]) return ch[0]->rank(x);
			else return 0;
		}
		else{
			if(ch[0]){
				if(ch[1]) return ch[0]->s+1+ch[1]->rank(x);
				else return ch[0]->s+1;
			}
			else{
				if(ch[1]) return 1+ch[1]->rank(x);
				else return 1;
			}
		}
	}
};
treap_node* merge(treap_node* l,treap_node* r){
	if(!l) return r;
	if(!r) return l;
	if(l->r>r->r){
		r->ch[0]=merge(l,r->ch[0]);
		r->pushup();
		return r;
	}
	else{
		l->ch[1]=merge(l->ch[1],r);
		l->pushup();
		return l;
	}
}
void split(treap_node* o,int x,treap_node*& l,treap_node*& r){
	if(!o){
		l=r=0;
		return;
	}
	if(x>=o->v){
		split(o->ch[1],x,o->ch[1],r);
		o->pushup();
		l=o;
	}
	else{
		split(o->ch[0],x,l,o->ch[0]);
		o->pushup();
		r=o;
	}
}
struct treap{
	treap_node* rt;
	treap():rt(0){}
	void insert(int x){
		treap_node *l,*r;
		split(rt,x,l,r);
		rt=merge(merge(l,new treap_node(x)),r);
	}
	void remove(int x){
		treap_node *l,*mid,*r;
		split(rt,x,mid,r);
		split(mid,x-1,l,mid);
		rt=merge(merge(l,merge(mid->ch[0],mid->ch[1])),r);
		delete mid;
	}
	int rank(int x){
		if(!rt) return 0;
		return rt->rank(x);
	}
};
treap c[maxn];
inline int lowbit(int x){
	return x&-x;
}
void insert(int x,int k){
	while(x<=n){
		c[x].insert(k);
		x+=lowbit(x);
	}
}
void remove(int x,int k){
	while(x<=n){
		c[x].remove(k);
		x+=lowbit(x);
	}
}
int query(int x,int k){
	int ans=0;
	while(x>0){
		ans+=c[x].rank(k);
		x-=lowbit(x);
	}
	return ans;
}
int get_pre(int x){
	iter it=s.lower_bound(odt_node(x,x,0));
	it=s2[it->v].lower_bound(odt_node(x,x,0));
	if(it->l!=x) return x-1;
	else{
		if(it==s2[it->v].begin()) return 0;
		else return (--it)->r;
	}
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    srand(time(0)*20060122);
    n=readint();
    m=readint();
    map<int,int> mp;
    for(int i=1;i<=n;i++){
    	int a=readint();
    	if(!mp.count(a)) mp[a]=mp.size();
    	a=mp[a];
    	s.insert(odt_node(i,i,a));
    	s2[a].insert(odt_node(i,i,a));
    	pre[i]=lst[a];
    	lst[a]=i;
    	insert(i,pre[i]);
	}
	while(m--){
		int opt=readint();
		if(opt==1){
			int l,r,x;
			l=readint();
			r=readint();
			x=readint();
			if(!mp.count(x)) mp[x]=mp.size();
			x=mp[x];
			iter itl,itr;
			itr=split(s,r+1);
			itl=split(s,l);
			itr--;
			split(s2[itr->v],r+1);
			split(s2[itl->v],l);
			itr++;
			vector<int> res;
			for(iter i=itl;i!=itr;i++){
				res.push_back(i->l);
				iter it=s2[i->v].upper_bound(*i);
				if(it!=s2[i->v].end()) res.push_back(it->l);
			}
			for(iter i=itl;i!=itr;i++) s2[i->v].erase(*i);
			s.erase(itl,itr);
			s.insert(odt_node(l,r,x));
			s2[x].insert(odt_node(l,r,x));
			iter it=s2[x].upper_bound(odt_node(l,r,x));
			if(it!=s2[x].end()) res.push_back(it->l);
			for(int i=0;i<(int)res.size();i++){
				int x=res[i];
				remove(x,pre[x]);
				insert(x,pre[x]=get_pre(x));
			}
		}
		else{
			int l,r;
			l=readint();
			r=readint();
			printf("%d\n",query(r,l)-query(l-1,l));
		}
	}
    return 0;
}
```
就可以了……吗？

由于要卡分块，所以大毒瘤一不小心就把树套树一个 log 的空间也给卡掉了……

~~并且对我不耐烦之后大毒瘤还叫我去造 5e5 的数据，我就算真能造出来也至少得一个月了。~~

所以我们要找一种线性空间的东西来做这题。

我们把 $(i,pre_i)$（$pre_i$ 代表 $i$ 的前缀）看成是一个点，则查询就是二维偏序问题，修改就是插入一个点再删除一个点……

偏序问题？那可不可以离线下来上 cdq 分治呢？

这里讲一下 cdq 分治怎么去做带修二维偏序。

其实很简单，我们把时间也看作一个维度，修改和插入删除都看成点，这样就可以转化成三维偏序问题，直接上 cdq 即可。

然后你就被卡常了……

很简单，cdq 改成归并排序，加个火车头，就能过了。
```cpp
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=1e5+5;
int n,m;
struct node{
	int l,r,v;
	node(int l,int r,int v):l(l),r(r),v(v){}
	bool operator <(node b)const{
		return r<b.r;
	}
};
set<node> s,s2[maxn*2];
typedef set<node>::iterator iter;
iter split(set<node>& s,int x){
	iter it=s.lower_bound(node(x,x,0));
	if(it==s.end()||it->l>x) return it;
	node res=*it;
	s.erase(res);
	if(x>res.l) s.insert(node(res.l,x-1,res.v));
	return (s.insert(node(x,res.r,res.v))).first;
}
int lst[maxn],pre[maxn];
int get_pre(int x){
	iter it=s.lower_bound(node(x,x,0));
	it=s2[it->v].lower_bound(node(x,x,0));
	if(it->l!=x) return x-1;
	else{
		if(it==s2[it->v].begin()) return 0;
		else return (--it)->r;
	}
}
struct point{
	int x,y,w,id;
	bool flag;
	point(int x,int y,int w,int id,bool flag)
	:x(x),y(y),w(w),id(id),flag(flag){}
};
vector<point> p;
int ans[maxn];
int ord[maxn*11];
int c[maxn];
inline int lowbit(int x){
	return x&-x;
}
void modify(int x,int k){
	while(x<=n+1){
		c[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x){
	int s=0;
	while(x>0){
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
void solve(int l,int r){
	if(l==r){
		ord[r]=r;
		return;
	}
	int mid=l+(r-l)/2;
	solve(l,mid);
	solve(mid+1,r);
	int cur=l;
	vector<int> res;
	for(int i=mid+1;i<=r;i++){
		while(cur<=mid&&p[ord[cur]].x<=p[ord[i]].x){
			modify(p[ord[cur]].y+1,p[ord[cur]].w);
			res.push_back(ord[cur]);
			cur++;
		}
		if(p[ord[i]].id>=0){
			int res=query(p[ord[i]].y+1);
			if(p[ord[i]].flag) ans[p[ord[i]].id]+=res;
			else ans[p[ord[i]].id]-=res;
		}
		res.push_back(ord[i]);
	}
	for(int i=l;i<cur;i++) modify(p[ord[i]].y+1,-p[ord[i]].w);
	for(int i=cur;i<=mid;i++) res.push_back(ord[i]);
	for(int i=l;i<=r;i++) ord[i]=res[i-l];
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    m=readint();
    map<int,int> mp;
    for(int i=1;i<=n;i++){
    	int a=readint();
    	if(!mp.count(a)) mp[a]=mp.size();
    	a=mp[a];
    	s.insert(node(i,i,a));
    	s2[a].insert(node(i,i,a));
    	pre[i]=lst[a];
    	lst[a]=i;
    	p.push_back(point(i,pre[i],1,-1,0));
	}
	int cnt=0;
	while(m--){
		int opt=readint();
		if(opt==1){
			int l,r,x;
			l=readint();
			r=readint();
			x=readint();
			if(!mp.count(x)) mp[x]=mp.size();
			x=mp[x];
			iter itl,itr;
			itr=split(s,r+1);
			itl=split(s,l);
			itr--;
			split(s2[itr->v],r+1);
			split(s2[itl->v],l);
			itr++;
			vector<int> res;
			for(iter i=itl;i!=itr;i++){
				res.push_back(i->l);
				iter it=s2[i->v].upper_bound(*i);
				if(it!=s2[i->v].end()) res.push_back(it->l);
			}
			for(iter i=itl;i!=itr;i++) s2[i->v].erase(*i);
			s.erase(itl,itr);
			s.insert(node(l,r,x));
			s2[x].insert(node(l,r,x));
			iter it=s2[x].upper_bound(node(l,r,x));
			if(it!=s2[x].end()) res.push_back(it->l);
			for(int i=0;i<(int)res.size();i++){
				int x=res[i];
				p.push_back(point(x,pre[x],-1,-1,0));
				p.push_back(point(x,pre[x]=get_pre(x),1,-1,0));
			}
		}
		else{
			int l,r;
			l=readint();
			r=readint();
			p.push_back(point(r,l-1,0,cnt,1));
			p.push_back(point(l-1,l-1,0,cnt,0));
			cnt++;
		}
	}
	solve(0,p.size()-1);
	for(int i=0;i<cnt;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Sol1 (赞：10)

相对 Ynoi 来说更偏结论和模板的 cdq 题。

前置知识：CDQ 分治、时间复杂度分析、卡常。

---

首先这玩意看起来不太好做，考虑弱化为单点修改。

单点修改区间颜色数有一个非常套路的转换，就是维护每一个点的颜色的前驱（即对每一个 $i$ 维护最大的 $p_i$ 使得 $p_i<i$ 且 $a_{p_i}=a_i$，如果不存在则为 $0$），然后每次统计满足 $l\leq i\leq r, 1\leq p_i<l$ 的 $i$ 的数量。

显然这玩意就是一个二维数点。

但是带上单点修改之后就没法简单地维护了怎么办呢？

显然，每次单点修改 $i$ 为 $x$，只会改变 $i$ 的前驱、$i$ 的原后继的前驱、$i$ 的新后继的前驱。

修改一个点可以拆分为先删除再加入，然后在 $t$ 时间删除一个点 $(x,y)$ 可以通过加一个权值为 $-1$ 的三维空间内的点 $(t,x,y)$，然后再加入一个权值为 $1$ 的点 $(t,x',y')$ 来实现。

然后，因为询问只考虑到询问时间之前的修改的影响，所以这就转换为了一个三维偏序，就可以树套树/CDQ 维护了。

---

那么区间修改怎么做呢？

【区间修改的时候，$p$ 数组最多发生多少次改变？】  
那还用说吗，每次改变 $O(n)$ 个位置，显然是 $O(nm)$。  
【好，你说是 $O(nm)$，怎么卡满这个复杂度？】  
嗯……  
【试了 15 分钟】  
为啥就死活卡不满呢……  
【也许不是 $O(nm)$？】  
也许吧……试着证一下吧。

每次推平一段区间的时候，所有 $p$ 改变的位置一定是 **一段极长连续同色子段的左端点**，剩下的都将 **维持为下标减 $1$ 不变**。

推平之后，这些连续同色子段都会被 **删除**。

如果我们删掉了 $O(x)$ 个节点，花费的代价一定是 $O(x)$ 的。

删除的过程中，先要执行 ODT 的 split，这一步增加的点的数量是 $O(1)$ 的。

然后花费 $O(x)$ 的代价删去 $O(x)$ 个节点。

然后再把这一段加回来，增加的点的数量是 $O(1)$ 的。

所以增加的点的数量是 $O(m)$ 的。

一开始有 $O(n)$ 个点，所以总点数是 $O(n+m)$ 的。

显然只有 $O(n+m)$ 个点，删除的总次数也只有 $O(n+m)$。

每次删除对总修改次数的贡献为 $O(1)$。

得到结论：

**所有修改操作完成后，$p$ 数组上单点修改的次数为 $O(n+m)$。**

---

好！那么这就变成了单点修改！

现在的问题就变成了如何维护出需要修改的点。

显然还是要拿一棵 ODT，但是区间修改的时候要是直接讨论需要修改的位置……看着……看着……就不想写了……

换一个思路，如果把所有需要修改的位置存下来，然后排除掉 $p$ 数组直接修改 ODT，然后再对这些位置看要改成啥……诶！好像非常好写！

为了方便处理前驱，ODT 上面还要再额外对每一种颜色维护一个 set。

那么现在就只需要把所有修改的位置处理出来，然后使用单点修改的方法拆点转换为三维偏序，这题就做完啦~

最终时间复杂度 $O((n+m)\log ^2 n)$，空间复杂度 $O(n+m)$。

---

然后直接写好了交上去，就 TLE+MLE 了 QAQ

我们发现一个点的空间开销较大，需要 $5$ 个 int，然后这个点数的 $O(n)$ 带大常数，所以在 CDQ 分治的归并排序过程中不去维护点的临时数组 $p'$，而是维护 **点的下标** 的临时数组 $v'$，其中 $v'_i$ 实际对应的点是 $p_{v'_i}$。

这样临时数组的空间就优掉了很多，于是就不 MLE 了。

然后有两个主要的剪枝：

1. 对于所有**查询**点维护出最大的 $X$、最大的 $Y$ 和最大的 $Z$，然后将所有满足 $x_0>X$ 或 $y_0>Y$ 或 $z_0>Z$ 的**修改**点剔除（因为这些点不可能产生贡献）；
2. 树状数组清零的时候可以另写一个函数，清到一个位置为 $0$ 的时候就没有必要往下走了。

加上这两个剪枝和一些常用的卡常技巧（如快读）~~再打开 O2~~ 就可以爆过去啦~

代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <set>
#include <vector>
#include <tr1/unordered_map>
using namespace std;
using namespace std::tr1;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

struct Node {
	int l, r, v;
	bool operator < (const Node& b) const {return l < b.l;}
	Node() {}
	Node(int l, int r, int v) : l(l), r(r), v(v) {}
};
struct Point {
	int _time, x, y, val;
	bool type;
	Point() {}
	Point(int _time, int x, int y, int val, bool type) : _time(_time), x(x), y(y), val(val), type(type) {}
};
int n, prv[100005], a[100005], m, mptop, lst[100005], ans[100005], c[100005], idx[1200005];
vector <Point> vc;
unordered_map <int, int> mp;
struct ChthollyTree {
	typedef set<Node>::iterator SNI;
	set <Node> tr, col[200005];
	inline SNI Insert(int l, int r, int v) {
		col[v].insert(Node(l, r, v));
		return tr.insert(Node(l, r, v)).first;
	}
	inline void Delete(int l, int r, int v) {
		col[v].erase(Node(l, r, v));
		tr.erase(Node(l, r, v));
	}
	inline int Prev(int pos) {
		SNI it = tr.upper_bound(Node(pos, 0, 0));
		it--;
		if (it->l < pos) return pos - 1;
		else {
			SNI rm = col[it->v].lower_bound(Node(pos, 0, 0));
			if (rm != col[it->v].begin()) {
				rm--;
				return rm->r;
			}
			return 0;
		}
	}
	inline SNI Split(int pos) {
		SNI it = tr.lower_bound(Node(pos, 0, 0));
		if (it != tr.end() && it->l == pos) return it;
		--it;
		int l = it->l, r = it->r;
		long long v = it->v;
		Delete(l, r, v);
		Insert(l, pos - 1, v);
		return Insert(pos, r, v);
	}
	inline void Assign(int l, int r, int v, int _time) {
		//printf("%d:\n", _time);
		SNI itr = Split(r + 1), itl = Split(l);
		vector <int> mpnt;
		for (SNI it = itl;it != itr;it++) {
			if (it != itl) mpnt.push_back(it->l);
			SNI nxt = col[it->v].upper_bound(*it);
			if (nxt != col[it->v].end()) mpnt.push_back(nxt->l);
			col[it->v].erase(*it);
		}
		tr.erase(itl, itr);
		tr.insert(Node(l, r, v));
		col[v].insert(Node(l, r, v));
		mpnt.push_back(l);
		SNI nxt = col[v].upper_bound(Node(l, r, v));
		if (nxt != col[v].end()) mpnt.push_back(nxt->l);
		register int siz = mpnt.size();
		for (register int i = 0;i < siz;i++) {
			if (mpnt[i] > n || mpnt[i] < 1) continue;
			vc.push_back(Point(_time, mpnt[i], prv[mpnt[i]], -1, 0));
			prv[mpnt[i]] = Prev(mpnt[i]);
			//printf("%d %d\n", mpnt[i], prv[mpnt[i]]);
			vc.push_back(Point(_time, mpnt[i], prv[mpnt[i]], 1, 0));
		}
		//puts("End");
	}
};
ChthollyTree tr;

inline int Lowbit(int x) {
	return x & -x;
}

inline void Update(int i, int x) {
	for (register int j = i;j <= n;j += Lowbit(j)) c[j] += x;
}

inline void Remove(int i) {
	for (register int j = i;j <= n;j += Lowbit(j)) {
		if (!c[j]) break;
		else c[j] = 0;
	}
}

inline int Query(int i) {
	register int ans = 0;
	for (register int j = i;j >= 1;j -= Lowbit(j)) ans += c[j];
	return ans;
}

inline void Read() {
	n = qread(); m = qread();
	for (register int i = 1;i <= n;i++) {
		a[i] = qread();
		if (!mp[a[i]]) {
			mptop++;
			mp[a[i]] = mptop;
		}
		a[i] = mp[a[i]];
	}
}

inline void Prefix() {
	vc.push_back(Point(-1, 0, 0, 0, 0));
	for (register int i = 1;i <= n;i++) {
		prv[i] = lst[a[i]];
		vc.push_back(Point(0, i, prv[i], 1, 0));
		lst[a[i]] = i;
		tr.tr.insert(Node(i, i, a[i]));
		tr.col[a[i]].insert(Node(i, i, a[i]));
	}
}

inline void Cdq(int l, int r) {
	//printf("cdq(%d,%d){\n", l, r);
	if (l == r) return;
	register int mid = l + r >> 1;
	Cdq(l, mid);
	//puts("}");
	Cdq(mid + 1, r);
	//puts("}");
	vector <int> tmp;
	int i = l, j = mid + 1;
	while (i <= mid && j <= r) {
		if (vc[idx[i]].x <= vc[idx[j]].x) {
			if (vc[idx[i]].type == 0) Update(vc[idx[i]].y, vc[idx[i]].val);
			tmp.push_back(idx[i]);
			i++;
		} else {
			if (vc[idx[j]].type == 1) {
				ans[vc[idx[j]]._time] += vc[idx[j]].val * Query(vc[idx[j]].y);
				//printf("%d %d %d %d\n", vc[j]._time, vc[j].x, vc[j].y, ans[vc[j]._time]);
			}
			tmp.push_back(idx[j]);
			j++;
		}
	}
	while (j <= r) {
		if (vc[idx[j]].type == 1) {
			ans[vc[idx[j]]._time] += vc[idx[j]].val * Query(vc[idx[j]].y);
			//printf("%d %d %d %d\n", vc[j]._time, vc[j].x, vc[j].y, ans[vc[j]._time]);
		}
		tmp.push_back(idx[j]);
		j++;
	}
	for (register int k = l;k < i;k++) {
		if (vc[idx[k]].type == 0) Remove(vc[idx[k]].y);
	}
	while (i <= mid) {
		tmp.push_back(idx[i]);
		i++;
	}
	for (i = l;i <= r;i++) idx[i] = tmp[i - l];
}

inline void Solve() {
	for (register int i = 1;i <= m;i++) {
		register int opt = qread();
		if (opt == 1) {
			register int l = qread(), r = qread(), v = qread();
			if (!mp[v]) {
				mptop++;
				mp[v] = mptop;
			}
			v = mp[v];
			tr.Assign(l, r, v, i);
		} else {
			register int l = qread(), r = qread();
			vc.push_back(Point(i, r, l - 1, 1, 1));
			vc.push_back(Point(i, l - 1, l - 1, -1, 1));
		}
	}
	register int pcnt = vc.size() - 1;
	for (register int i = 1;i <= pcnt;i++) vc[i].y++;
	// for (register int i = 1;i <= pcnt;i++) {
	// 	printf("%d %d %d %d %d\n", vc[i].type, vc[i]._time, vc[i].x, vc[i].y, vc[i].val);
	// }
	register int maxx = 0, maxy = 0, maxz = 0;
	vector <int> ridx;
	for (register int i = 1;i <= pcnt;i++) {
		if (vc[i].type) {
			maxx = Max(maxx, vc[i]._time);
			maxy = Max(maxy, vc[i].x);
			maxz = Max(maxz, vc[i].y);
		}
	}
	for (register int i = 1;i <= pcnt;i++) {
		if (vc[i].type || (vc[i]._time <= maxx && vc[i].x <= maxy && vc[i].y <= maxz)) ridx.push_back(i);
	}
	pcnt = ridx.size();
	for (register int i = 1;i <= pcnt;i++) idx[i] = ridx[i - 1];
	Cdq(1, pcnt);
	for (register int i = 1;i <= m;i++) {
		if (ans[i]) printf("%d\n", ans[i]);
	}
}

int main() {
	Read();
	Prefix();
	Solve();
	return 0;
}
```

---

## 作者：_Arahc_ (赞：9)

调了三天的题，今天可算干出来了。

**树套树**，没错，就是树套树，在线做法，时间空间都过了。

~~虽然拿了一个你谷最劣解~~，但是这至少说明带毒瘤还没有太狠，不然给这题加强制在线了www。

附带本蒟蒻调题时拍到的曾经让我的代码卡 WA 的数据：[Link](https://www.luogu.com.cn/paste/oc4i9cyt)，希望对大家有帮助。

## 题意

[题目传送门](https://www.luogu.com.cn/problem/P4690)，大致题意如下：

> 维护一个序列：
>
> 1. 将区间 $[l,r]$ 染色。
> 2. 查寻区间 $[l,r]$ 有几种颜色。
>
> $n,m\leqslant 10^5$，空间限制 $\text{64MiB}$。

颜色编号不管多大，离散化即可，因此颜色数为 $n+m$ 级别。

## 分析

考虑这个问题的弱化版 [CF848C](https://www.luogu.com.cn/problem/CF848C)（可以转化为**类似**单点修改颜色，区间查询的问题）怎么做，设位置为 $i$ 的颜色上一次出现的位置为 $pre_i$，查寻时转化为查寻 $i\in[l,r],pre_i\in[0,l-1]$ 的 $i$ 的数量。将 $i,pre_i$ 看作横纵坐标，就可以转化为数点问题。于是可以：用 $n+m$ 个 `set` 分别维护每个颜色出现的位置，方便查寻前驱后继。单次修改时：

1. 这个位置原本的贡献，和它后继的贡献删除。

2. 更新它的后继的贡献。

3. 修改这个位置的颜色，更新新颜色带来的贡献和变化。

现在 **单点修改** 问题转化为了 **区间修改**。显然把 $i,pre_i$ 当成横纵坐标数点的思路仍然正确，考虑如何解决区间修改。发现本题的修改操作就是区间覆盖，可以用类似 ODT 的推平操作进行。

还是对于每个颜色维护一个 `set`，但是 `set` 内应该存区间，表示这一段区间内都是这个颜色，按左右端点排序无所谓，因为显然各个 `set` 的区间无交。单次修改时：

1. **细节**：左端点可能被一个区间完全包含，这时可以把这个区间裂成两个区间，右端点同理。使得要修改的范围内所有区间都严格被修改的范围 $[l,r]$ 包含。
2. 遍历 $[l,r]$ 内的每一个区间，对于任意一个区间，修改它的后继对这个区间造成的的贡献，删除本区间对 $pre$ 造成的贡献，然后把这个区间删除。
3. 把这个区间覆盖成新的颜色，更新新颜色带来的贡献和变化。

为什么这么做不会 T？考虑初始状态下有 $n$ 个区间，单次修改最坏产生三个区间（在一个区间内部覆盖），修改次数可以均摊地视为 $\operatorname{O}(n)$ 级别。

考虑查寻，发现一段区间内出了左端点其它所有点的 $pre_i=i-1$，因此只需要记录每个左端点产生的贡献。查询时，如果 $l$ 被一个区间包含，可以将 $l$ 直接拉到这个区间的左端点的位置再查寻，避免这个区间被查漏。

## 实现

根据上述分析本题的做法已经完形，剩下的就是如何实现，我见过的（不一定写过）的有以下几种：

1. 离线 cdq 查询。时间复杂度 $n\log n$，空间线性。可过。
2. 在线 KDTree 数点，时间复杂度 $n\sqrt{n}$，空间线性，不可过。参考我 [LOJ 上代码](https://loj.ac/s/1340282)。
3. 分块，时空复杂度 $n\sqrt n$，不可过。
4. 二维线段树等，时空复杂度 $n\log^2 n$，不可过。
5. 树套树，时间复杂度 $n\log^2n$，空间复杂度 $n\log n$，可过。

很多人认为树套树的空间复杂度是 $n\log^2 n$，事实上，考虑用树状数组套平衡树即可。因为树状数组的空间复杂度是单 $\log$，写平衡树的时候删除操作记个内存池回收即可。

本人用的树状数组套替罪羊，替罪羊树常数较小，推荐使用。

## 代码

本人代码较冗长，可以参考我在 [LOJ 上的提交记录](https://loj.ac/s/1340227)，这份代码在 luogu 已经同步 AC，空间基本压线。



---

## 作者：2014吕泽龙 (赞：5)

### **分析**
区间修改数颜色。

单点修改的操作是把相同颜色往前链，等价于问区间内前驱相同颜色不在当前区间的数的个数，这个东西用$cdq$分治或者树套树可以解决。修改的话用$set$搞定。

区间修改的话有一个结论是修改次数不超过$O(n+m)$次。

证明的话采用摊还分析。

考虑把所有相同颜色缩成一个点。
显然要修改的只有相同颜色区间的头和尾。

每一次区间操作把这个区间给单独抓出来，然后把这个区间内的点全部删掉，再插入修改后的代表这个区间的节点。
每次区间头，区间尾，以及新的区间各产生一个节点，总共新产生不超过$3m$个节点。

一个点之多再删除和插入的时候修改一次，所以至多进行$2$次修改。所以总共修改次数不超过$O(n+m)$

上述证明就提供了方法。采用$set$维护区间即可。

$P.S:$一个技巧是分别维护全局的$set$和每种颜色的$set$，两边一起修改会比较方便。
### **代码**
采用树套树

常数巨大。
```cpp
#include<bits/stdc++.h>
#define ins insert
#define era erase
#define Ub(x) upper_bound(Data(x))
#define Lb(x) lower_bound(Data(x))
const int N = 4e5 + 10;
int ri() {
    char c = getchar(); int x = 0, f = 1; for(;c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
    for(;c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) - '0' + c; return x * f;
}
int n, Mx, cnt, pre[N], a[N];
struct Data {
    int l, r, col;
    Data(int _l = 0, int _r = 0, int _col = 0) : l(_l), r(_r), col(_col) {}
    bool operator < (const Data &a) const {return l < a.l;}
};
std::set<Data>st[N], all;
std::set<Data>::iterator it;
std::set<int>nw;
std::set<int>::iterator it2;
std::map<int, int>M;
struct Val_Segment{
    int s[N * 50], ls[N * 50], rs[N * 50], sz;
    void Modify(int &p, int L, int R, int x, int v) {
        s[p ? p : p = ++sz] += v;
        if(L == R) return ; int m = L + R >> 1;
        x <= m ? Modify(ls[p], L, m, x, v) : Modify(rs[p], m + 1, R, x, v);
    }
    int Query(int p, int L, int R, int ed) {
        if(!p || ed == R) return s[p]; int m = L + R >> 1;
        return ed <= m ? Query(ls[p], L, m, ed) : s[ls[p]] + Query(rs[p], m + 1, R, ed);
    }
}seg;
struct Pos_Segment {
    int rt[N];
    void Modify(int x, int l, int v) {
        for(;x <= n; x += x&-x)
            seg.Modify(rt[x], 0, Mx, l, v);
    }
    int Query(int x, int k) {
        int r = 0;
        for(;x; x -= x&-x)
            r += seg.Query(rt[x], 0, Mx, k);
        return r;
    }
    int Query(int l, int r, int k) {return Query(r, k) - Query(l - 1, k);}
}Rt;
void Up(int x, int v) {
    Rt.Modify(x, pre[x], -1);
    pre[x] = v;
    Rt.Modify(x, pre[x], 1);
}
void Ins(int l, int r, int col) {
    st[col].ins(Data(l, r)); all.ins(Data(l, r, col));
}
void Era(Data x) {
    st[x.col].era(x); all.era(x);
}
void Split(int x) {
    it = all.Ub(x); --it;
    if(it->l == x) return ;
    Data tmp = *it;
    Era(tmp);
    Ins(tmp.l, x - 1, tmp.col);
    Ins(x, tmp.r, tmp.col);
}
void Modify(int l, int r, int col) {
    Split(l);
    if(r < n) Split(r + 1);
    nw.clear(); nw.ins(col);
    for(;1;) { //把所有介于l，r的区间全部抓出来。 
        it = all.Lb(l);
        if(it == all.end() || it->l > r)
            break;
        Data tmp = *it; nw.ins(tmp.col);
        if(tmp.l > l && pre[tmp.l] != tmp.l - 1) 
            Up(tmp.l, tmp.l - 1);
        Era(tmp);
    }
    it = st[col].Lb(l); Up(l, (--it)->r);
    Ins(l, r, col); 
    for(it2 = nw.begin();it2 != nw.end(); ++it2) { //所有右端点开头的都要修改。 
        it = st[*it2].Ub(r);
        if(it == st[*it2].end())
            continue;
        int pos = it->l;
        it = st[*it2].Lb(pos); 
        Up(pos, (--it)->r);
    }
}
int main() {
    n = ri(); int q = ri(); Mx = n + q;
    for(int i = 1;i <= n; ++i) {
        a[i] = ri();
        if(!M[a[i]]) 
            st[M[a[i]] = ++cnt].insert(Data());
        a[i] = M[a[i]];
    }
    for(int i = 1;i <= n; ++i) {
        it = st[a[i]].end(); --it; pre[i] = it->l; 
        Rt.Modify(i, pre[i], 1);
        Ins(i, i, a[i]);
    }
    for(;q--;) {
        int op = ri(), l = ri(), r = ri();
        if(op == 1) {
            int x = ri();
            if(!M[x])
                st[M[x] = ++cnt].insert(Data());
            x = M[x]; Modify(l, r, x);
        }
        else if(op == 2)
            printf("%d\n", Rt.Query(l, r, l - 1));
    }
    return 0;
}
```


---

## 作者：x7103 (赞：3)

[**不知道更好还是更差的阅读体验**](https://www.cnblogs.com/VCLS01/p/14823564.html)
## 题目描述
给定一个长度为 $n$ 的序列 $a$，有 $m$ 次操作。共有两种操作：

 - `1 l r x`，将 $[l,r]$ 区间赋值为 $x$。
 - `2 l r`，求 $[l,r]$ 中出现了多少种不同的数。

**数据范围：**$1\le n,m\le 10^5$，$a_i\le 10^9$。

**时间范围：**$1500\operatorname{ms}$。

## Solution

直接暴力是 $O(n^2)$ 的，~~显然可以通过本题，不需要~~考虑优化。

对于每个数，求出上一个与这个数相同的位置，定为 $pre$，没有则为 $0$。

对于区间赋值，我们发现当我们会令 $\forall i\in(l,r],pre_i\leftarrow i-1$，对于 $i=l$ 特判即可。

同时我们可以发现，当修改位于 $[l,r]$ 中的元素时，与它相同的下一个元素的 $pre$ 也会变；同时颜色与 $x$ 相同的位置 $>r$ 的第一个元素的 $pre$ 也会变。特判即可。

这一步时间复杂度为 $O(n)$。~~大佬们都写了我就不证了。~~

那么问题转化为求 $\sum_{i=l}^{r}[pre_i<l]$，三维数点即可，时间复杂度为 $O(n\log^2 n)$。
## Code
```cpp
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int maxn=200010,maxq=1000010;
typedef pair<int,int> PII;
struct Data{
	int x,y,z,k,d,ans;
	inline Data(){}
	inline Data(int _x,int _y,int _z,int _k,int _d){x=_x;y=_y;z=_z;k=_k;d=_d;ans=0;}
	inline bool operator<(const Data &da)const{return x!=da.x?x<da.x:(y!=da.y?y<da.y:z<da.z);}
}q[maxq],w[maxq/2];
struct Operation{
	int opt,l,r,x;
}p[maxn];
int pre[maxn],n,m,tot,a[maxn],b[maxn],cnt,ans[maxn];
inline bool cmpy(const Data &d1,const Data &d2){return d1.y!=d2.y?d1.y<d2.y:d1.z<d2.z;}
struct Color{
	set<PII>col,v[maxn];
	inline void Split(int k){
		set<PII>::iterator it=col.lower_bound(make_pair(k+1,0));
		int r=it->first-1;--it;
		int l=it->first;
		if(k==r)return;
		int c=it->second;
		col.erase(it);
		col.insert(make_pair(l,c));col.insert(make_pair(k+1,c));
		v[c].erase(make_pair(l,r));
		v[c].insert(make_pair(l,k));v[c].insert(make_pair(k+1,r));
	}
	inline void Insert(int l,int r,int c,int t){
		Split(l-1);Split(r);
		for(set<PII>::iterator it=col.lower_bound(make_pair(l,0));it->first<=r;){
			int x=it->first,y=it->second;
			++it;int z=it->first-1;
			col.erase(make_pair(x,y));
			v[y].erase(make_pair(x,z));
			if(x==l){
				int e=(--(v[c].upper_bound(make_pair(x,0))))->second;
				if(pre[x]!=e){
					q[++tot]=Data(t,x,pre[x],0,-1);
					pre[x]=e;
					q[++tot]=Data(t,x,pre[x],0,1);
				}
			}
			else{
				if(pre[x]!=x-1){
					q[++tot]=Data(t,x,pre[x],0,-1);
					pre[x]=x-1;
					q[++tot]=Data(t,x,pre[x],0,1);
				}
			}
			x=z+1;
			z=(v[y].lower_bound(make_pair(x,0)))->first;
			int e=(--v[y].lower_bound(make_pair(l,0)))->second;
			if(z>r&&z<=n&&pre[z]!=e){
				q[++tot]=Data(t,z,pre[z],0,-1);
				pre[z]=e;
				q[++tot]=Data(t,z,pre[z],0,1);
			}
		}
		set<PII>::iterator it=v[c].lower_bound(make_pair(r+1,0));
		int x=it->first;
		if(x<=n&&pre[x]!=r){
			q[++tot]=Data(t,x,pre[x],0,-1);
			pre[x]=r;
			q[++tot]=Data(t,x,pre[x],0,1);
		}
		v[c].insert(make_pair(l,r));
		col.insert(make_pair(l,c));
		x=r+1;
		if(x<=n){
			it=col.lower_bound(make_pair(x,0));
			int y=it->second;
			int e=(--v[y].lower_bound(make_pair(x,0)))->second;
			if(pre[x]!=e){
				q[++tot]=Data(t,x,pre[x],0,-1);
				pre[x]=e;
				q[++tot]=Data(t,x,pre[x],0,1);
			}
		}
	}
}color;
struct TreeArray{
	#define lowbit(x) (x&-x)
	int tr[maxn];
	inline void add(int x,int d){++x;while(x<maxn)tr[x]+=d,x+=lowbit(x);}
	inline int ask(int x){++x;int ans=0;while(x)ans+=tr[x],x-=lowbit(x);return ans;}
	#undef lowbit
}BIT;
inline void CDQ(int l,int r){
	if(l>=r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	int i=l,j=mid+1,k=0;
	bool flag=(l!=1||r!=tot);
	while(i<=mid&&j<=r){
		if(q[i].y<=q[j].y){if(q[i].k==0)BIT.add(q[i].z,q[i].d);if(flag)w[k++]=q[i];++i;}
		else{if(q[j].k==1)q[j].ans+=BIT.ask(q[j].z);if(flag)w[k++]=q[j];++j;}
	}
	while(i<=mid){if(q[i].k==0)BIT.add(q[i].z,q[i].d);if(flag)w[k++]=q[i];++i;}
	while(j<=r){if(q[j].k==1)q[j].ans+=BIT.ask(q[j].z);if(flag)w[k++]=q[j];++j;}
	for(i=l;i<=mid;++i)if(q[i].k==0)BIT.add(q[i].z,-q[i].d);
	if(flag)for(int i=0;i<k;++i)q[i+l]=w[i];
}
FILE *read=stdin,*write=stdout;
int main(){
	fscanf(read,"%d%d",&n,&m);
	for(int i=1;i<=n;++i)fscanf(read,"%d",&a[i]),b[++cnt]=a[i];
	for(int i=1;i<=m;++i){
		fscanf(read,"%d%d%d",&p[i].opt,&p[i].l,&p[i].r);
		if(p[i].opt==1)fscanf(read,"%d",&p[i].x),b[++cnt]=p[i].x;
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	for(int i=1;i<=m;++i)if(p[i].opt==1)p[i].x=lower_bound(b+1,b+cnt+1,p[i].x)-b;
	for(int i=1;i<=cnt;++i)
		color.v[i].insert(make_pair(0,0));
	for(int i=1;i<=n;++i){
		pre[i]=(--color.v[a[i]].end())->second;
		q[++tot]=Data(0,i,pre[i],0,1);
		color.v[a[i]].insert(make_pair(i,i));
		color.col.insert(make_pair(i,a[i]));
	}
	for(int i=1;i<=cnt;++i)
		color.v[i].insert(make_pair(n+1,0));
	color.col.insert(make_pair(0,0));
	color.col.insert(make_pair(n+1,n+1));
	for(int i=1;i<=m;++i){
		if(p[i].opt==1)
			color.Insert(p[i].l,p[i].r,p[i].x,i);
		else{
			q[++tot]=Data(i,p[i].r,p[i].l-1,1,1);
			q[++tot]=Data(i,p[i].l-1,p[i].l-1,1,-1);
		}
	}
	sort(q+1,q+tot+1);
	CDQ(1,tot);
	for(int i=1;i<=tot;++i)
		if(q[i].k)ans[q[i].x]+=q[i].ans*q[i].d;
	for(int i=1;i<=m;++i)
		if(p[i].opt==2)fprintf(write,"%d\n",ans[i]);
	return 0;
}
```

---

## 作者：NATURAL6 (赞：2)

# 题意
维护一个长为 $n$ 的序列 $a_i$，有 $m$ 次操作。

1.将区间 $[l,r]$ 的值修改为 $x$ 。

2.询问区间 $[l,r]$ 出现了多少种不同的数，也就是说同一个数出现多次只算一个。

# sol

这是一篇线性空间分块做法，但效率很高，是目前的[最优解](https://www.luogu.com.cn/record/list?pid=P4690&orderBy=1&status=&page=1)。

首先，对于每个数维护一个值，表示上一个该数出现的位置。

因为值域很大，所以要离散化。

那么，问题就转化成了，询问一段区间中值小于左端点的数的个数。

考虑分块，块内存每个值出现的次数，前缀和一下就能得到答案了。

但因为有修改，这样时间是 $O(n^2)$ 的。

考虑到一个块内实际只有 $O(\sqrt{n})$ 个不同的取值，所以只用维护这些值的答案，于是暴力修改的复杂度就只有 $O(\sqrt{n})$ 了。

但这样的话要么对每个块维护一个大小为 $n$ 的数组实现 $O(1)$ 查，要么每次花费 $O(\log{n})$ 的时间二分查。

要么时间爆炸，要么空间爆炸。

那怎么解决呢？

考虑刚才的操作实际上只是找了一些值出来对值域做离散，因为每个块取值的不同，所以不方便查询。

那么我们可以让每个块的取值相同，这样就能线性空间 $O(1)$ 查询了。

但有意义的取值有 $O(n)$ 个，这样子又回去了。

考虑有意义的实际上是询问的取值，而非块内的值，所以可以对询问分块。

每 $O(\sqrt{n})$ 个询问为一块，每 $O(\sqrt{n})$ 个询问就换取值暴力重构。

这样的时间复杂度就是 $O(n\sqrt{n})$ 的了。

好像缺点什么。。。

以上都是默认了修改为单点修，共 $O(n)$ 次，实际上，这是一个结论：

对一个长度为 $n$ 的数组进行 $m$ 次区间赋值操作，每个数的值总共的改变次数为 $O(n+m)$ 级别。

于是区间赋值就变成了单点修改了，这个操作可以用珂朵莉树来维护。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define iter set<ODT>::iterator
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int qread()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
inline void qw(register int x)
{
	if(x>9)qw(x/10);
	putchar(x%10+'0');
	return ;
}
int n,m,a[100010],s,cnt,ans[100010],cl,c[100010],st[500],ed[500],CL,ST[350],ED[350],C[100010],pos[500],tot,sum[500][1000],b[200010],pre[100010];
struct xw
{
	int op,l,r,id;
}q[100010];
struct ODT
{
	int l,r,id;
};
bool operator <(const ODT x,const ODT y){return x.l<y.l;}
bool operator >(const ODT x,const ODT y){return x.l>y.l;}
set<ODT>odt,vis[200010];
inline iter spilt(register int x)
{
	if(x>n)return odt.end();
	iter it=--odt.upper_bound((ODT){x,0,0});
	if(it->l==x)return it;
	int l=it->l,r=it->r,id=it->id;
	odt.erase(it);
	odt.insert((ODT){l,x-1,id});
	return odt.insert((ODT){x,r,id}).first;
}
inline iter vspilt(register int col,register int x)
{
	if(x>n)return vis[col].end();
	iter it=--vis[col].upper_bound((ODT){x,0,0});
	if(it->l>x||it->r<x)return vis[col].end();
	if(it->l==x)return it;
	int l=it->l,r=it->r,id=it->id;
	vis[col].erase(it);
	vis[col].insert((ODT){l,x-1,id});
	return vis[col].insert((ODT){x,r,id}).first;
}
inline void U(register int sc,register int x,register int y)
{
	if(b[x]==b[y])return ;
	if(x<y)for(register int i=b[x];i<b[y];++i)--sum[sc][i];
	else for(register int i=b[y];i<b[x];++i)++sum[sc][i];
	return ;
}
inline void f(register int x,register int an)
{
	U(c[x],pre[x],an);
	pre[x]=an;
	return ;
}
inline void ff(register int x,register int col)
{
	iter cx=vis[col].lower_bound((ODT){x,0,0});
	if(cx->l!=x&&cx!=vis[col].begin())--cx;
	if(cx->l<x&&cx->r>=x)
	{
		f(x,x-1);
		return ;
	}
	int an=0;
	(cx==vis[col].begin())?((x<=cx->l)?an=0:an=cx->r):((x<=cx->l)?an=(--cx)->r:an=cx->r);
	U(c[x],pre[x],an);
	pre[x]=an;
	return ;
}
inline void assign(register int l,register int r,register int op)
{
	iter itr=spilt(r+1),itl=spilt(l);
	iter it,cx;
	int sl,sr,col;
	for(;itl!=itr;)
	{
		it=itl;
		++itl;
		sl=it->l,sr=it->r,col=it->id;
		(sl!=l)?f(sl,sl-1):ff(sl,op);
		if(sl!=sr&&sr!=r)f(sr,sr-1);
		cx=vspilt(col,sr+1);
		cx=vspilt(col,sl);
		vis[col].erase(cx);
		cx=vis[col].lower_bound((ODT){sr,0,0});
		if(cx!=vis[col].end())ff(cx->l,col);
		odt.erase(it);
	}
	odt.insert((ODT){l,r,op});
	vis[op].insert((ODT){l,r,op});
	cx=vis[op].upper_bound((ODT){l+1,0,0});
	if(cx!=vis[op].end())f(cx->l,r);
	ff(r+1,itr->id);
	return ;
}
inline int solve(register int l,register int r)
{
	int an=0;
	if(c[l]==c[r])for(register int i=l;i<=r;++i)an+=(pre[i]<l);
	else
	{
		for(register int i=l;i<=ed[c[l]];++i)an+=(pre[i]<l);
		for(register int i=c[l]+1;i<c[r];++i)an+=sum[i][b[l]-1];
		for(register int i=st[c[r]];i<=r;++i)an+=(pre[i]<l);
	}
	return an;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=qread();
	m=qread();
	cl=sqrt(n<<2)+1;
	CL=sqrt(m)*3+1;
	s=1;
	for(register int i=1;i<=n;++i)b[++tot]=a[i]=qread(),c[i]=(i-1)/cl+1,ed[c[i]]=i;
	for(register int i=n;i;--i)st[c[i]]=i;
	for(register int i=1;i<=m;++i)
	{
		C[i]=(i-1)/CL+1,ED[C[i]]=i;
		q[i].op=qread();
		q[i].l=qread();
		q[i].r=qread();
		if(q[i].op==1)b[++tot]=q[i].id=qread();
		else q[i].id=++cnt;
	}
	sort(b+1,b+1+tot);
	tot=unique(b+1,b+1+tot)-b-1;
	for(register int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
	for(register int i=1;i<=n;++i)
	{
		if(a[i]!=a[s])
		{
			odt.insert((ODT){s,i-1,a[s]});
			vis[a[s]].insert((ODT){s,i-1,a[s]});
			s=i;
		}
	}
	odt.insert((ODT){s,n,a[s]});
	vis[a[s]].insert((ODT){s,n,a[s]});
	for(register int i=m;i;--i)ST[C[i]]=i,(q[i].op==1)&&(q[i].id=lower_bound(b+1,b+1+tot,q[i].id)-b);
	memset(b,0,sizeof(b));
	for(register int i=1;i<=n;++i)
	{
		pre[i]=b[a[i]];
		b[a[i]]=i;
	}
	for(register int i=1;i<=C[m];++i)
	{
		tot=0;
		for(register int j=ST[i];j<=ED[i];++j)(q[j].op==2)&&(pos[++tot]=q[j].l);
		sort(pos+1,pos+1+tot);
		tot=unique(pos+1,pos+1+tot)-pos-1;
		pos[tot+1]=1e9;
		s=0;
		for(register int j=0;j<=(n+m);++j)
		{
			while(j>=pos[s])++s;
			b[j]=s;
		}
		for(register int j=1;j<=c[n];++j)
		{
			for(register int i=b[n+m];i;--i)sum[j][i]=0;
			for(register int k=st[j];k<=ed[j];++k)++sum[j][b[pre[k]]];
			for(register int k=1;k<=tot;++k)sum[j][k]+=sum[j][k-1];
		}
		for(register int j=ST[i];j<=ED[i];++j)
		{
			if(q[j].op==1)assign(q[j].l,q[j].r,q[j].id);
			else ans[q[j].id]=solve(q[j].l,q[j].r);
		}
	}
	for(register int i=1;i<=cnt;++i)qw(ans[i]),puts("");
	return 0;
}


```


---

## 作者：Macesuted (赞：1)

[在我的个人博客中阅读](https://macesuted.cn/article/lg4690/)

---

[题目链接](https://www.luogu.com.cn/problem/P4690)

## 题目大意

维护一个长为 $n$ 的序列 $a_i$，有 $m$ 次操作。

1. 将区间 $[l,~r]$ 的值修改为 $x$。
2. 询问区间 $[l,~r]$ 出现了多少种不同的数，也就是说同一个数出现多次只算一个。

$1 \le n,~m \le 10^5,~1 \le a_i \le 10^9$

## 分析

区间数不同颜色数量问题我们常用的解决方案是记 $pre_i$ 等于最大的 $j$ 满足 $j < i$ 且 $a_j = a_i$，数区间内满足 $pre_i < l$ 的数量即为区间内的颜色数量。

此题的难点在于区间修改操作，经分析不难发现当一个区间 $[l,~r]$ 被修改为 $x$ 时 $\forall i \in (l,~r],~pre[i]=i-1$，所以在每次操作后我们只需要：

1. 将 $pre_l$ 修改为上一个 $x$ 区间的右端点。
2. 将下一个 $x$ 区间的左端点的 $pre$ 改为 $r$。
3. 将 $(l,~r]$ 区间内的所有 $pre_i$ 改为 $i-1$。

考虑 3 操作，如果我们在每次修改时将所有 $pre_i \neq i-1$ 的位置找出并修改为 $i-1$，全局花在 3 操作上的修改次数为 $O(n+m)$：初始时每个 $pre_i$ 可能都不等于 $i-1$，而后面的 $m$ 个操作中每个操作最多只会让两个 $pre_i$ 修改得不等于 $i-1$，所以全局出现过 $pre_i$ 不等于 $i-1$ 情况的次数为 $O(n+m)$，所以花在 3 操作上的修改次数也就为 $O(n+m)$。

考虑如何快速找出 $pre_i \neq i-1$ 的位置。容易发现这样的位置一定是一个连续颜色段的开头。因此我们对原序列建一颗 ODT，每次修改 $[l,~r]$ 时，1 操作和 2 操作直接单点修改，3 操作找到 ODT 上被 $[l,~r]$ 包含的所有连续颜色段，将它们全部删除并把它们的左端点的 $pre$ 设为 $i-1$ 即可。

我们可以使用树套树在线维护修改操作并 $O(\log^2 n)$ 解决查询操作。

然后我翻开题解区发现 [BFqwq](https://www.luogu.com.cn/user/120074) 的题解也使用了树套树，便非常自信地写完了树套树并且提交，不出所料怎么卡空间都是全 MLE。[帖子](https://www.luogu.com.cn/discuss/show/341872)（然后 BF 就在博客的前面加上了“题解不可通过此题，仅供参考”的提示）

考虑使用复杂度不变但空间更小的做法。

我们现在是在使用树套树在线解决带修改二维数点问题，考虑再开一维表示数据修改的时间，问题就转变为静态三维数点问题，离线 CDQ 分治即可。

时间复杂度仍旧为 $O(m \log^2 n)$，空间复杂度优化到 $O(n+m)$。

## 代码

[View on GitHub](https://github.com/Macesuted/Code/blob/main/Luogu/4690.cpp)


---

## 作者：chenxia25 (赞：1)

先考虑单点修改怎么做。一个套路是，数区间里面所有第一次出现的数，形式化的表示是 $i\in[l,r],prv_i<l$。那这是个二维数点了，要是单点修改就动态二维数点上 cdq，至于如何维护 $prv$ 那就很 trivial 了，`set` 乱搞。

区间修改怎么做？观察 $prv$ 的变化，发现 $(l,r]$ 内的元素 $i$ 都有 $prv_i=i-1$，依据这个特殊性开始搞事情。那对某个区间，满足 $i\in[l,r],i-1<l$ 的元素仅可能是 $i=l$，那就判一判就可以了，这很 trivial。于是就是要对 $l$ 们展开维护。

那么每次区间修改，把这个区间里原本的 $l$ 的信息都要删除。怎么快速删除？其实不难想到暴力删除复杂度是对的，因为每次修改只会增加一个 $l$，那删除的次数也必定不超过修改的次数，这是个简单的势能分析。同时在删除、添加的时候，还要实时维护（原本）以它为前驱的后面的元素，不难发现对每个位置最多有一个，复杂度也是不用担心的。那对任意位置找前驱 / 后继就对每个值维护位置的 `set`，但是值是批量批量修改的怎么办呢。再开个 `set` 记录相等段们，然后把区间的代表元（$l$）扔进之前的那个 `set` 即可。

搞着搞着搞出一个动态二位数点的操作序列，最后对着这个序列 cdq 一遍即可。复杂度二次对数。虽然这个操作序列异常的长（可能 $10n$ 左右吧），但还是跑得很快，大概是 cdq 和 BIT 常数实在太小了。

但是这题莫名卡空间，理论上我的空间复杂度是线性~~（又称线性空间）~~但还是过不去。我采取了一些卡空间手段（但是只有最后一步起到决定性作用）：把 `int` 能压成 `short` 就压，甚至可以压到 `bool` / `signed char`；把装 3 个 1e6 级别的 `int` 的 `pair<pair<int,int>,int>` 用一个 `long long` 压缩起来然后解压；cdq 的时候不在里面开部分操作序列的 `vector`，开到外面，并且换成数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define X x()
#define Y y()
#define Z z()
#define pb push_back
const int inf=999999;
int lowbit(int x){return x&-x;}
const int N=100010,QU=100010;
int n,qu;
int a[N];
struct query{
	int tp,l,r,x;
}qry[QU];
vector<int> nums;
void discrete(){
	sort(nums.begin(),nums.end());
	nums.resize(unique(nums.begin(),nums.end())-nums.begin());
	for(int i=1;i<=n;i++)a[i]=lower_bound(nums.begin(),nums.end(),a[i])-nums.begin()+1;
	for(int i=1;i<=qu;i++)qry[i].x=lower_bound(nums.begin(),nums.end(),qry[i].x)-nums.begin()+1;
}
set<int> st[N+QU];
struct query0{
	bool add;int x,y;signed char v;int id;
	friend bool operator<(query0 z,query0 w){return z.x==w.x?(z.y<w.y):(z.x<w.x);}
};
vector<query0> qry0;
struct tup{
	unsigned long long zip;
	tup(int x,int y,int z){zip=(1ll*x<<40)+(1ll*y<<20)+z;}
	int x()const{return zip>>40;}
	int y()const{return zip>>20&((1<<20)-1);}
	int z()const{return zip&((1<<20)-1);}
	friend bool operator<(tup x,tup y){return x.zip<y.zip;}
};
set<tup> rg;
set<tup>::iterator in(int x){
	set<tup>::iterator fd=rg.upper_bound(tup(x,inf,0));
	return --fd;
}
int ans[QU];
int prv[N];
int tor(int l){return l==0?l:in(l)->Y;}
void delblk(int l,int r,int x){//updlist: st(pos), query0, rg, prv
	st[x].erase(l);
	qry0.pb(query0({1,l,prv[l],-1,0}));
	set<int>::iterator fd=st[x].upper_bound(l);
	if(fd!=st[x].end()){
		qry0.pb(query0({1,*fd,prv[*fd],-1,0}));
		set<int>::iterator fd0=fd--;
		qry0.pb(query0({1,*fd0,prv[*fd0]=tor(*fd),1,0}));
	}
}
void addblk(int l,int r,int x){//updlist: st(pos), query0, rg, prv
	st[x].insert(l);rg.insert(tup(l,r,x));
	set<int>::iterator fd=st[x].lower_bound(l);
	qry0.pb(query0({1,l,prv[l]=tor(*--fd),1,0}));
	fd++;fd++;
	if(fd!=st[x].end()){
		qry0.pb(query0({1,*fd,prv[*fd],-1,0}));
		qry0.pb(query0({1,*fd,prv[*fd]=r,1,0}));
	}
}
struct bitree{
	int cnt[N];
	bitree(){memset(cnt,0,sizeof(cnt));}
	void add(int x,int v){
		while(x<=n+1)cnt[x]+=v,x+=lowbit(x);
	}
	int Cnt(int x){
		int res=0;
		while(x)res+=cnt[x],x-=lowbit(x);
		return res;
	}
}bit;
query0 v[10*N];int tail;
void cdq(int l=0,int r=qry0.size()-1){
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	tail=0;
	for(int i=l;i<=mid;i++)if(qry0[i].add==1)v[tail++]=qry0[i];
	for(int i=mid+1;i<=r;i++)if(qry0[i].add==0)v[tail++]=qry0[i];
	stable_sort(v,v+tail);
	for(int i=0;i<tail;i++){
		int add=v[i].add,x=v[i].y,v0=v[i].v,id=v[i].id;
		if(add)bit.add(x+1,v0);
		else ans[id]+=v0*bit.Cnt(x+1);
	}
	for(int i=0;i<tail;i++){
		int add=v[i].add,x=v[i].y,v0=v[i].v;
		if(add)bit.add(x+1,-v0);
	}
}
int main(){
	cin>>n>>qu;
	for(int i=1;i<=n;i++)scanf("%d",a+i),nums.pb(a[i]);
	for(int i=1;i<=qu;i++){
		scanf("%d%d%d",&qry[i].tp,&qry[i].l,&qry[i].r);
		if(qry[i].tp==1)scanf("%d",&qry[i].x),nums.pb(qry[i].x);
	}
	discrete();
	for(int i=1;i<=nums.size();i++)st[i].insert(0);//很好的 trick！ 
	for(int i=1;i<=n;i++){
		qry0.pb(query0({1,i,prv[i]=*--st[a[i]].end(),1,0}));
		rg.insert(tup(i,i,a[i]));
		st[a[i]].insert(i);
	}
	int ask=0;
	for(int i=1;i<=qu;i++){
		int tp=qry[i].tp,l=qry[i].l,r=qry[i].r,x=qry[i].x;
		if(tp==1){//updlist: st(pos), query0, rg, prv
			set<tup>::iterator pl=in(l),pr=in(r);
			tup PL=*pl,PR=*pr;
			vector<tup> del;
			for(set<tup>::iterator j=pl;;j++){
				delblk(j->X,j->Y,j->Z),del.pb(*j);
				if(j==pr)break;
			}
			for(int j=0;j<del.size();j++)rg.erase(del[j]);
			if(l!=PL.X)addblk(PL.X,l-1,PL.Z);
			addblk(l,r,x);
			if(r!=PR.Y)addblk(r+1,PR.Y,PR.Z);
		}
		else{
			ask++;
			tup pl=*in(l);
			ans[ask]=l!=pl.X;
			qry0.pb(query0({0,r,l-1,1,ask})),qry0.pb(query0({0,l-1,l-1,-1,ask}));
		}
	}
	cdq();
	for(int i=1;i<=ask;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：_quasar_ (赞：1)

区间数不同的数的个数是个常见的套路，不说了。

考虑这个区间修改怎么办——意味着需要修改一堆数的 $pre$。

假设对于修改前，有一段区间 $[l',r'],l\leq l'\leq r'\leq r$ ，满足这一段区间中的数都是相同的。那么进行了修改过后，容易发现改变 $pre$ 只有 $pre_{l'},pre_{r''}$ ，这里 $pre_{r''}$ 满足修改前，$pre_{r''}=r'$ 。

接着考虑，如果最开始整个序列有 $n$ 个区间，显而易见的，如果一次修改覆盖到了 $a$ 个完整的区间并且碰到了 $b\leq 2$ 个不完整的区间，那么暴力进行修改的话是 $a+b$ 次修改的，然后区间数就会减去 $a-1$ 。

由于区间数最多减到 $1$，又因为 $b\leq 2$ ，所以其实暴力修改的次数是 $O(n+m)$ 级别的。事实上，最坏情况大概是 $n+2m$ 次修改。

所以拿一个 set 维护一下区间，然后维护 $pre$ 的话用二维线段树即可。

时间复杂度是 $O((n+m)\log n$ ？只有 $10^5$ 所以应该不会被卡常吧？

----------

关于实现：

- 二维线段树：最坏点得跑 $2.7s$ 。（空间 $\log^2$）
- 树状数组 + 动态开点线段树：最坏点 $1.7s$，足以通过 loj 数据。（空间 $\log ^2$）。

- CDQ + 平衡树：卡住了懒得调。（空间 $\log$）。
- CDQ + 树状数组：最坏点 $0.9s$，足以通过 luogu 数据。（空间 $\log$）。

容易发现 luogu 的空间有毒，甚至不足以开下两个 `Node` 数组搞 CDQ，所以可以开两个 `int` 数组维护编号（具体见代码实现）

而且为了加速，这里采用归并排序。

----------

关于代码。

树状数组 + 动态开点线段树：[详见提交记录](https://loj.ac/s/1016373)

CDQ + 树状数组：

```cpp
const int N=1e5+5;
const int M=1e6+5;

int n,m,_,cnt,a[N],id[M],ti[M],ans[N],h[N<<1];
struct Query {int tim,l,r,val,typ,op;} q[M];

namespace ChthollyTree { // {{{ ChthollyTree
    #define ins insert

    int pre[N],las[N<<1];
    struct Node {
        int l,r,val;
        bool operator < (const Node &kls) const {return r<kls.l;}
    };
    std::set <Node> seq;
    std::set <pii> sta[N<<1];

    inline void update(int x,int now) {
        q[++cnt]=(Query){cnt,x,-1,pre[x],0,-1},
        q[++cnt]=(Query){cnt,x,-1,pre[x]=now,0,1};
    }
    inline void init() {
        lep(i,1,n) {
            a[i]=std::lower_bound(h+1,h+1+_,a[i])-h;
            q[++cnt]=(Query){cnt,i,-1,pre[i]=las[a[i]],0,1},las[a[i]]=i;
            seq.ins((Node){i,i,a[i]}),sta[a[i]].ins(mkp(i,i));
        }
        lep(i,1,_) sta[i].ins(mkp(0,0));
    }
    inline void insert(int l,int r,int val) {
        std::set <pii>::iterator it2=sta[val].upper_bound(mkp(l,r)),it1=it2; --it2;
        if(it1!=sta[val].end()) update(it1->fi,r); update(l,it2->se);
        sta[val].ins(mkp(l,r)),seq.ins((Node){l,r,val});
    }
    inline void erase(int l,int r,int val,int _flag) {
        std::set <pii>::iterator it2=sta[val].upper_bound(mkp(l,r)),it1=it2; --it2,--it2;
        if(it1!=sta[val].end()) update(it1->fi,it2->se);
        if(l!=_flag) update(l,l-1);
        sta[val].erase(mkp(l,r)),seq.erase((Node){l,r,val});
    }
    inline void cut(int l,int r,int val,int pos) {
        seq.erase((Node){l,r,val}),sta[val].erase(mkp(l,r));
        seq.ins((Node){l,pos,val}),sta[val].ins(mkp(l,pos));
        seq.ins((Node){pos+1,r,val}),sta[val].ins(mkp(pos+1,r)); 
    }
    inline void split(int L,int R,int val) {
        std::set <Node>::iterator it=seq.lower_bound((Node){L,L-1,0});

        if(it->l<=L&&R<=it->r) {
            int l=it->l,r=it->r,_val=it->val;
            if(l<L) cut(l,r,_val,L-1);
            if(R<r) cut(L,r,_val,R);
            erase(L,R,_val,L);
        } else while(it!=seq.end()&&it->l<=R) {
            int l=it->l,r=it->r,_val=it->val; ++it;
            if(L<=l&&r<=R) erase(l,r,_val,L);
            else {
                if(l<L&&L<=r&&r<=R) cut(l,r,_val,L-1),erase(L,r,_val,L);
                if(L<=l&&l<=R&&R<r) cut(l,r,_val,R),erase(l,R,_val,L);
            }
        }
        insert(L,R,val);
    }
} using namespace ChthollyTree; // }}}

// {{{ cdq divide

// {{{ BIT

int res,c[N];
inline int lowbit(int x) {return x&(-x);}
inline void modify(int x,int y) {for(;x<=n;x+=lowbit(x)) c[x]+=y;}
inline int query(int l,int r) {
    --l,res=0;
    while(r>l) res+=c[r],r-=lowbit(r);
    while(l>r) res-=c[l],l-=lowbit(l);
    return res;
}

// }}}

void cdq(int l,int r) {
    if(l==r) return ;
    int mid=(l+r)>>1;
    cdq(l,mid),cdq(mid+1,r);

    int L=mid+1; lep(i,l,mid) {
        while(L<=r&&q[id[L]].val<q[id[i]].val) {
            if(q[id[L]].typ) ans[q[id[L]].typ]+=q[id[L]].op*query(q[id[L]].l,q[id[L]].r);
            ++L;
        }
        if(!q[id[i]].typ) modify(q[id[i]].l,q[id[i]].op);
    }
    while(L<=r) {
        if(q[id[L]].typ) ans[q[id[L]].typ]+=q[id[L]].op*query(q[id[L]].l,q[id[L]].r);
        ++L;
    }
    lep(i,l,mid) if(!q[id[i]].typ) modify(q[id[i]].l,-q[id[i]].op);

    int i=l,j=mid+1,t=l;
    while(i<=mid&&j<=r) ti[t++]=(q[id[i]].val<q[id[j]].val)?id[i++]:id[j++];
    while(i<=mid) ti[t++]=id[i++];
    while(j<=r) ti[t++]=id[j++];
    lep(i,l,r) id[i]=ti[i];
}
// }}}

int query_cnt,_op[N],_l[N],_r[N],_x[N];
int main() {
    IN(n,m);
    lep(i,1,n) IN(a[i]),h[++_]=a[i];
    lep(i,1,m) {
        IN(_op[i],_l[i],_r[i]);
        if(_op[i]==1) h[++_]=_x[i]=int(IN);
    }
    
    std::sort(h+1,h+1+_); int tmp=_; _=1;
    lep(i,2,tmp) if(h[i]!=h[_]) h[++_]=h[i];

    init();
    lep(i,1,m) {
        if(_op[i]==1) split(_l[i],_r[i],std::lower_bound(h+1,h+1+_,_x[i])-h);
        if(_op[i]==2) q[++cnt]=(Query){cnt,_l[i],_r[i],_l[i]-1,++query_cnt,1};
    }
    
    lep(i,1,cnt) id[i]=i;
    cdq(1,cnt);
    lep(i,1,query_cnt) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Leasier (赞：1)

看到区间推平，考虑 ODT。

但是这道题要求区间不同数的数量，除非数据随机（可以时间戳 + 暴力遍历做到 1log），感觉不太好做了……

注意到区间出现不同数的次数有一个等价形式：

- $\displaystyle\sum_{i = l}^r [nxt_i > r]$，其中 $nxt_i$ 表示下一个与 $i$ 相同的数，不存在则为 $n + 1$。

假如 $nxt_i$ 的修改次数较少，我们就可以先对序列分块、在块内再维护一个 $O(\sqrt{n})$ 修改、$O(1)$ 查询后缀和的值域分块，然后就可以做到 $O((n + m + k) \sqrt{n})$ 了，其中 $k$ 表示修改次数。

注意到每次在 ODT 上的修改只会影响下面这样的位置：

- 被删掉的区间 $[l', r', x']$ 的 $r'$。
- 另一个区间 $[l'', r'', x']$ 的 $r''$ 满足 $r'' < l'$ 且最大。
- 另一个区间 $[l'', r'', x]$ 的 $r''$ 满足 $r'' < l$ 且最大。

于是修改次数是 $O(n + m)$ 的，则时间复杂度为 $O((n + m) \sqrt{n})$。

为了卡空间，我将序列分块块长设为 $\frac{\sqrt{n}}{8}$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <set>
#include <cstdio>
#include <cmath>

using namespace std;

typedef struct {
	int belong[100007];
	int lft[327];
	int rt[327];
	int suf1[327];
	int suf2[100007];
	
	inline void init(int n){
		int block = sqrt(n), m = (n - 1) / block + 1;
		for (register int i = 1; i <= n; i++){
			belong[i] = (i - 1) / block + 1;
		}
		for (register int i = 1; i <= m; i++){
			lft[i] = block * (i - 1) + 1;
			rt[i] = min(i * block, n);
		}
	}
	
	inline void del(int x){
		for (register int i = 1; i <= belong[x]; i++){
			suf1[i]--;
		}
		for (register int i = lft[belong[x]]; i <= x; i++){
			suf2[i]--;
		}
	}
	
	inline void add(int x){
		for (register int i = 1; i <= belong[x]; i++){
			suf1[i]++;
		}
		for (register int i = lft[belong[x]]; i <= x; i++){
			suf2[i]++;
		}
	}
	
	inline int get_sum(int x){
		return suf1[belong[x] + 1] + suf2[x];
	}
} Block;

typedef struct Node_tag {
	int l;
	int r;
	int val;
	Node_tag(int l_, int r_, int val_){
		l = l_;
		r = r_;
		val = val_;
	}
} Node;

int block;
bool type = false;
int belong[100007], lft[47], rt[47], a[100007], b[200007], nxt[100007], op[100007], l[100007], r[100007], x[100007], bucket[200007], val[200007];
Block blk[47];
set<Node> s1, s2[200007];

bool operator <(const Node a, const Node b){
	return !type ? a.r < b.r : a.l < b.l;
}

bool operator ==(const Node a, const Node b){
	return a.l == b.l && a.r == b.r && a.val == b.val;
}

inline set<Node>::iterator insert(Node x){
	s2[x.val].insert(x);
	return s1.insert(x).first;
}

inline void modify(int x, int y){
	if (nxt[x] != 0) blk[belong[x]].del(nxt[x]);
	nxt[x] = y;
	blk[belong[x]].add(y);
}

inline void erase(Node x){
	s1.erase(x);
	s2[x.val].erase(x);
}

inline set<Node>::iterator split(int x){
	set<Node>::iterator it;
	type = true;
	it = s1.lower_bound(Node(x, 0, 0));
	type = false;
	if (it != s1.end() && it->l == x) return it;
	Node cur = *(--it);
	if (cur.r < x) return s1.end();
	erase(cur);
	if (cur.l < x) insert(Node(cur.l, x - 1, cur.val));
	return insert(Node(x, cur.r, cur.val));
}

int main(){
	int n, m, k, ni, y = 0;
	scanf("%d %d", &n, &m);
	block = sqrt(n) * 7.0;
	k = (n - 1) / block + 1;
	ni = n + 1;
	for (register int i = 1; i <= n; i++){
		belong[i] = (i - 1) / block + 1;
	}
	for (register int i = 1; i <= k; i++){
		lft[i] = block * (i - 1) + 1;
		rt[i] = min(i * block, n);
		blk[i].init(ni);
	}
	for (register int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		b[++y] = a[i];
	}
	for (register int i = 1; i <= m; i++){
		scanf("%d %d %d", &op[i], &l[i], &r[i]);
		if (op[i] == 1){
			scanf("%d", &x[i]);
			b[++y] = x[i];
		}
	}
	sort(b + 1, b + y + 1);
	y = unique(b + 1, b + y + 1) - b - 1;
	for (register int i = 1; i <= n; i++){
		a[i] = lower_bound(b + 1, b + y + 1, a[i]) - b;
	}
	for (register int i = 1; i <= m; i++){
		if (op[i] == 1) x[i] = lower_bound(b + 1, b + y + 1, x[i]) - b;
	}
	for (register int i = n; i >= 1; i--){
		set<Node>::iterator it;
		insert(Node(i, i, a[i]));
		it = s2[a[i]].lower_bound(Node(0, i + 1, 0));
		modify(i, it == s2[a[i]].end() ? ni : it->l);
	}
	for (register int i = 1; i <= m; i++){
		if (op[i] == 1){
			int cnt = 0;
			set<Node>::iterator it1, it2, it3;
			it1 = split(r[i] + 1);
			it2 = split(l[i]);
			for (register set<Node>::iterator j = it2; j != it1; j++){
				cnt++;
				bucket[cnt] = j->r;
				val[cnt] = x[i];
				it3 = s2[j->val].lower_bound(*j);
				if (it3 != s2[j->val].begin()){
					cnt++;
					bucket[cnt] = (--it3)->r;
					val[cnt] = j->val;
				}
				s2[j->val].erase(*j);
			}
			s1.erase(it2, it1);
			insert(Node(l[i], r[i], x[i]));
			it3 = s2[x[i]].lower_bound(Node(0, r[i], 0));
			if (it3 != s2[x[i]].begin()){
				cnt++;
				it3--;
				bucket[cnt] = it3->r;
				val[cnt] = x[i];
			}
			for (register int j = 1; j <= cnt; j++){
				it3 = s2[val[j]].lower_bound(Node(0, bucket[j] + 1, 0));
				modify(bucket[j], it3 == s2[val[j]].end() ? ni : max(it3->l, bucket[j] + 1));
			}
		} else {
			int ans = 0;
			if (belong[l[i]] == belong[r[i]]){
				for (register int j = l[i]; j <= r[i]; j++){
					if (nxt[j] > r[i]) ans++;
				}
			} else {
				int ri = r[i] + 1;
				for (register int j = l[i]; j <= rt[belong[l[i]]]; j++){
					if (nxt[j] > r[i]) ans++;
				}
				for (register int j = belong[l[i]] + 1; j < belong[r[i]]; j++){
					ans += blk[j].get_sum(ri);
				}
				for (register int j = lft[belong[r[i]]]; j <= r[i]; j++){
					if (nxt[j] > r[i]) ans++;
				}
			}
			cout << ans << endl;
		}
	}
	return 0;
}
```

---

## 作者：Others (赞：1)

神题一枚，学习卡空间的蚌题。

**Solution**：

区间赋值区间数颜色，随机的话一个板珂朵莉树，空间大点线段树套平衡树之类的树套树均可，但~~毒瘤的是~~这题都不符合。后者的空间没法优化，所以这题只能考虑整珂朵莉树。

珂朵莉树在只有区间赋值的题里总修改次数是 $O(n+m)$ 的（即使数据不随机）。这也是其他题解里主要证明的一点，有很多种证法（~~包括但不限于“感性理解”~~），这里用摊还分析来证明：

我们先将颜色分段，某一段颜色的未来有两种情况：被覆盖或分裂后一部分被覆盖。这里修改时被覆盖的颜色段数之和是我们要找的修改次数，可以发现直接被覆盖的段数最大为原来的颜色段数与修改带来的新颜色段数之和，为 $O(n+m)$，但分裂后一部分被覆盖不会减少颜色段数（甚至会加），由于每次操作最多分裂出两个颜色段，所以这里分裂出来的颜色段的总数是 $O(m)$ 的，再加入上述分析，得出修改次数为 $O(n+m)$ 的。

由于上述结论只有在只有一个区间赋值操作的题里正确，所以考虑用另外的方式数颜色。介绍一个实用的 `trick`（各种地方都用得到）：维护一个 $lst_i$ 表示上一个颜色相同的位置，我们就只需要找 $[l,r]$ 里 $lst_i<l$ 的个数。因为珂朵莉树可以维护一些信息，所以加上一个 $lst$ 元素还是可以用的。

为了方便找到某个颜色段的前驱和后继来更新删掉这个颜色段后的 $lst$，我们要再对每个颜色维护一个 `set`。注意每个颜色的 `set` 要和珂朵莉树里的颜色段一一对应。于是我们就得到了一些操作：

- 在 $t$ 时刻第 $x$ 的位置多了 $delta(delta\in \{1,-1\})$ 个前驱为 $y$ 的值。
- 在 $t$ 时刻查询 $[l,r]$ 里前驱小于 $y$ 的值的和。

第二个操作可以用两个前缀和的差来减少一维，然后就只有 $t,x,y$ 三维了，直接上一个 cdq 分治这题就结束了。

**需要注意的细节（我挂过的）**：

- 别觉得这题很难写，这题真的很难写（客观，而不是主观）。
- 区间赋值时删掉的颜色段的左端点的前驱要改，它的后继的前驱也要改，分裂时最好先把边界处理干净，不然后面会很难打。
- 可以用链表维护珂朵莉树，个人感觉会方便一点（虽然我也写的 `set` 维护），因为删掉的颜色段的后继也在珂朵莉树里，这时候不方便删，得保存下来之后再搞，链表就不需要处理这些了。

**然后就是卡 cache 的奇妙 `trick` 了**：

- 其他神仙题解里有写神仙做法，但我觉得有点复杂，于是自创了一条道路（如有雷同，纯属巧合）。
- 加操作的时候是按时间顺序，所以 $tim$ 元素并不必要。
- 第一个点里的 $tim$ 要用于映射查询的原下标，是必要的，但是我们可以发现查询的 $delta$ 也属于 $\{1,-1\}$，所以我们可以搞成 $\{tim,-tim\}$，查询时取个绝对值就行了，实测有效。
- 发现还是挂了几个点，千万不要去优化啥其他的东西，我们对最多的下手：操作。在 cdq 分治时我们要维护一个临时数组去记录归并后的信息，但是这玩意儿在全区间里没用，所以特判一下最大的那一层归并，不用临时数组，这样可以节省 $\frac{1}{4}$ 的空间，**可以通过**。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO{
}
using IO::read;
const int N=100005;
struct opera {
    int x,y,delta;bool op;
};vector<opera> vec,vec2;
struct assign_count {
    int op,l,r,x;
}p[N];
int n,m,a[N],flag[N<<1],top,ans[N],bit[N];
void add(int x,int y) {
    x++;
    while(x<=n) bit[x]+=y,x+=(x&-x);
}
int ask(int x) {
    int tot=0;
    x++;
    while(x) tot+=bit[x],x-=(x&-x);
    return tot;
}
struct Chtholly_Tree {
    struct node {
        int l,r,pre,col;
        bool operator<(const node &p) const {
            return l<p.l;
        }
    }LL,RR,tmp;set<node> odt,pos[N<<1];
    int Pre;
    vector<node> Tmp;
    auto split(int x) {
        auto it=--odt.upper_bound({x,x,0,0}),iit=pos[it->col].find(*it);
        int l=it->l,r=it->r,pre=it->pre,col=it->col;
        odt.erase(it);
        pos[col].erase(iit);
        if(l<x) odt.insert({l,x-1,pre,col}),pos[col].insert({l,x-1,pre,col});
        odt.insert({x,r,l<x?x-1:pre,col}),pos[col].insert({x,r,l<x?x-1:pre,col});
        return --odt.upper_bound({x,x,0,0});
    }
    void assign(int l,int r,int col) {
        auto R=split(r+1),L=split(l);
        for(auto it=L;it!=R;it++) {
            auto iit=pos[it->col].find(*it),lst=iit,nxt=iit;
            vec.push_back({it->l,iit->pre,-1,0});
            ++nxt;
            if(nxt!=pos[it->col].end()) {
                tmp=*nxt;
                if(iit==pos[it->col].begin()) tmp.pre=0;
                else --lst,tmp.pre=lst->r;
                vec.push_back({nxt->l,nxt->pre,-1,0});
                Tmp.push_back(tmp);
                pos[it->col].erase(nxt);
                vec.push_back({tmp.l,tmp.pre,1,0});
                pos[it->col].insert(tmp);
            }
            pos[it->col].erase(*it);
            if(it!=L) 
                vec.push_back({it->l,it->l-1,1,0});
        }
        LL=*L,RR=*R;
        for(const auto &lxl:Tmp) odt.erase(lxl),odt.insert(lxl);
        odt.erase(odt.find(LL),odt.find(RR));
        Tmp.clear();
        auto nxt=pos[col].upper_bound({l,l,0,0});
        Pre=0;
        if(nxt!=pos[col].begin()) {
            auto it=nxt;
            it--;
            Pre=it->r;
        }
        if(nxt!=pos[col].end()) {
            vec.push_back({nxt->l,nxt->pre,-1,0});
            tmp=*nxt;
            tmp.pre=r;
            vec.push_back({tmp.l,tmp.pre,1,0});
            odt.erase(*nxt);
            odt.insert(tmp);
            pos[col].erase(nxt);
            pos[col].insert(tmp);
        }
        odt.insert({l,r,Pre,col});
        pos[col].insert({l,r,Pre,col});
        vec.push_back({l,Pre,1,0});
    }
}ODT;
void cdq(int l,int r) {
    if(l==r) return ;
    int mid=l+r>>1;
    cdq(l,mid),cdq(mid+1,r);
    int p1=l,p2=mid+1;
    bool flag=(l==0&&r==vec.size()-1);
    while(p1<=mid||p2<=r) {
        if(p2>r||(p1<=mid&&vec[p1].x<=vec[p2].x)) {
            if(!vec[p1].op) add(vec[p1].y,vec[p1].delta);
            if(!flag) vec2.push_back(vec[p1]);p1++;
        }else {
            if(vec[p2].op) {
                ans[abs(vec[p2].delta)]+=(abs(vec[p2].delta)/vec[p2].delta)*ask(vec[p2].y);
            }
            if(!flag) vec2.push_back(vec[p2]);p2++;
        }
    }
    for(int i=l;i<=mid;i++) if(!vec[i].op) add(vec[i].y,-vec[i].delta);
    if(!flag) for(int i=l;i<=r;i++) vec[i]=vec2[i-l];
    vec2.clear(),vec2.shrink_to_fit();
    return ; 
}
int main() {
    // freopen("P4690.in","r",stdin);
    // freopen("P4690.out","w",stdout);
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read(),flag[++top]=a[i];
    for(int i=1;i<=m;i++) {
        p[i].op=read();
        if(p[i].op^2) p[i].l=read(),p[i].r=read(),flag[++top]=p[i].x=read();
        else p[i].l=read(),p[i].r=read();
    }
    sort(flag+1,flag+top+1),top=unique(flag+1,flag+top+1)-flag-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(flag+1,flag+top+1,a[i])-flag;
    for(int i=1;i<=m;i++) if(p[i].op^2) p[i].x=lower_bound(flag+1,flag+top+1,p[i].x)-flag;
    for(int i=1;i<=n;i++) {
        if(ODT.pos[a[i]].empty()) ODT.odt.insert({i,i,0,a[i]}),ODT.pos[a[i]].insert({i,i,0,a[i]}),vec.push_back({i,0,1,0});
        else {
            vec.push_back({i,ODT.pos[a[i]].rbegin()->r,1,0});
            ODT.odt.insert({i,i,ODT.pos[a[i]].rbegin()->r,a[i]});
            ODT.pos[a[i]].insert({i,i,ODT.pos[a[i]].rbegin()->r,a[i]});
        }
    }
    for(int i=1;i<=m;i++) {
        if(p[i].op^2) ODT.assign(p[i].l,p[i].r,p[i].x);
        else vec.push_back({p[i].r,p[i].l-1,i,1}),vec.push_back({p[i].l-1,p[i].l-1,-i,1});
    }
    cdq(0,vec.size()-1);
    for(int i=1;i<=m;i++) if(p[i].op^1) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：orz_z (赞：1)

### P4690 [Ynoi2016] 镜中的昆虫

区间赋值区间数颜色，$n \leq 10^5$，值域 $[1,10^9]$，要求线性空间。

##### sol

首先考虑经典数颜色套路，设 $pre_i$ 表示上一个与 $a_i$ 相同的数的位置。

对于区间赋值操作，我们发现性质：$\forall i\in(l,r],pre_i ←i-1$，对于 $i=l$ 或区间外的情况特判即可。

考虑使用 `ODT` 维护 $pre$ 的修改，一个 `ODT` 维护序列，一个 `ODT` 数组维护颜色位置，均摊修改次数为 $\mathcal O(n)$（增加节点总数 $\mathcal O(n)$，删除节点总数 $\mathcal O(n)$），时间复杂度 $\mathcal O(n\log n)$。

那么问题转化为带修求 $\sum\limits_{i=l}^{r}[pre_i<l]$，考虑到要求线性空间，故使用三维 `cdq`，时间复杂度 $\mathcal O(n \log^2 n)$。

时间复杂度 $\mathcal O(n \log ^2 n)$，空间复杂度 $\mathcal O(n)$。

详见代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace Fread
{
	const int SIZE = 1 << 21;
	char buf[SIZE], *S, *T;
	inline char getchar()
	{
		if (S == T)
		{
			T = (S = buf) + fread(buf, 1, SIZE, stdin);
			if (S == T)
				return '\n';
		}
		return *S++;
	}
}

namespace Fwrite
{
	const int SIZE = 1 << 21;
	char buf[SIZE], *S = buf, *T = buf + SIZE;
	inline void flush()
	{
		fwrite(buf, 1, S - buf, stdout);
		S = buf;
	}
	inline void putchar(char c)
	{
		*S++ = c;
		if (S == T)
			flush();
	}
	struct NTR
	{
		~NTR()
		{
			flush();
		}
	} ztr;
}

#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline void write(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 2e5 + 10, M = 1e6 + 10;

int n, m, tot, a[_], cnt, b[_], ans[_], d[_], pre[_];

struct Query
{
	int opt, l, r, x;
} q[_];

struct Node
{
	int x, y, z, k, d, ans;
	inline bool operator < (const Node &t) const
	{
		return x != t.x ? x < t.x : (y != t.y ? y < t.y : z < t.z);
	}
} p[M], c[M >> 1];

#define pii pair<int, int>
#define pa set<pii>::iterator

struct Col
{
	set<pii> cl, v[_];
	inline void split(int k)
	{
		pa it = cl.lower_bound({k + 1, 0});
		int r = it->first - 1;
		--it;
		int l = it->first;
		if(k == r) return;
		int c = it->second;
		cl.erase(it);
		cl.insert({l, c});
		cl.insert({k + 1, c});
		v[c].erase({l, r});
		v[c].insert({l, k});
		v[c].insert({k + 1, r});
	}
	inline void Insert(int l, int r, int c, int t)
	{
		split(l - 1), split(r);
		for(pa it = cl.lower_bound({l, 0}); it-> first <= r;)
		{
			int x = it->first, y = it->second;
			++it;
			int z = it->first - 1;
			cl.erase({x, y});
			v[y].erase({x, z});
			if(x == l)
			{
				int e = (--(v[c].upper_bound({x, 0})))->second;
				if(pre[x] != e)
				{
					p[++tot] = {t, x, pre[x], 0, -1, 0};
					pre[x] = e;
					p[++tot] = {t, x, pre[x], 0, 1, 0};
				}
			}
			else
			{
				if(pre[x] != x - 1)
				{
					p[++tot] = {t, x, pre[x], 0, -1, 0};
					pre[x] = x - 1;
					p[++tot] = {t, x, pre[x], 0, 1, 0};
				}
			}
			x = z + 1;
			z = (v[y].lower_bound({x, 0}))->first;
			int e = (--v[y].lower_bound({l, 0}))->second;
			if(z > r && z <= n && pre[z] != e)
			{
				p[++tot] = {t, z, pre[z], 0, -1, 0};
				pre[z] = e;
				p[++tot] = {t, z, pre[z], 0, 1, 0};
			}
		}
		pa it = v[c].lower_bound({r + 1, 0});
		int x = it->first;
		if(x <= n && pre[x] != r)
		{
			p[++tot] = {t, x, pre[x], 0, -1, 0};
			pre[x] = r;
			p[++tot] = {t, x, pre[x], 0, 1, 0};
		}
		v[c].insert({l, r});
		cl.insert({l, c});
		x = r + 1;
		if(x <= n)
		{
			it = cl.lower_bound({x, 0});
			int y = it->second;
			int e = (--v[y].lower_bound({x, 0}))->second;
			if(pre[x] != e)
			{
				p[++tot] = {t, x, pre[x], 0, -1, 0};
				pre[x] = e;
				p[++tot] = {t, x, pre[x], 0, 1, 0};
			}
		}
	}
} col;

inline void update(int x, int v)
{
	++x;
	while(x < _) d[x] += v, x += x & -x;
}

inline int query(int x)
{
	++x;
	int res = 0;
	while(x) res += d[x], x -= x & -x;
	return res;
}

void solve(int l, int r)
{
	if(l >= r) return;
	int mid = (l + r) >> 1;
	solve(l, mid), solve(mid + 1, r);
	int i = l, j = mid + 1, k = 0;
	bool flg = (l != 1 || r != tot);
	while(i <= mid && j <= r)
		if(p[i].y <= p[j].y)
	{
		if(p[i].k == 0) update(p[i].z, p[i].d);
		if(flg) c[k++] = p[i];
		++i;
	}
	else
	{
		if(p[j].k == 1) p[j].ans += query(p[j].z);
		if(flg) c[k++] = p[j];
		++j;
	}
	while(i <= mid)
	{
		if(p[i].k == 0) update(p[i].z, p[i].d);
		if(flg) c[k++] = p[i];
		++i;
	}
	while(j <= r)
	{
		if(p[j].k == 1) p[j].ans += query(p[j].z);
		if(flg) c[k++] = p[j];
		++j;
	}
	for(int i = l; i <= mid; ++i) if(p[i].k == 0) update(p[i].z, -p[i].d);
	if(flg) for(int i = 0; i < k; ++i) p[i + l] = c[i];
}

signed main()
{
	n = cnt = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = b[i] = read();
	for(int i = 1; i <= m; ++i)
	{
		q[i].opt = read(), q[i].l = read(), q[i].r = read();
		if(q[i].opt == 1) b[++cnt] = q[i].x = read();
	}
	sort(b + 1, b + cnt + 1);
	cnt = unique(b + 1, b + cnt + 1) - b - 1;
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
	for(int i = 1; i <= m; ++i) if(q[i].opt == 1) q[i].x = lower_bound(b + 1, b + cnt + 1, q[i].x) - b;
	for(int i = 1; i <= cnt; ++i) col.v[i].insert({0, 0});
	for(int i = 1; i <= n; ++i)
	{
		pre[i] = (--col.v[a[i]].end())->second;
		p[++tot] = {0, i, pre[i], 0, 1, 0};
		col.v[a[i]].insert({i, i});
		col.cl.insert({i, a[i]});
	}
	for(int i = 1; i <= cnt; ++i) col.v[i].insert({n + 1, 0});
	col.cl.insert({0, 0}), col.cl.insert({n + 1, n + 1});
	for(int i = 1; i <= m; ++i)
		if(q[i].opt == 1) col.Insert(q[i].l, q[i].r, q[i].x, i);
	else p[++tot] = {i, q[i].r, q[i].l - 1, 1, 1, 0}, p[++tot] = {i, q[i].l - 1, q[i].l - 1, 1, -1, 0};
	sort(p + 1, p + tot + 1);
	solve(1, tot);
	for(int i = 1; i <= tot; ++i) if(p[i].k) ans[p[i].x] += p[i].ans * p[i].d;
	for(int i = 1; i <= m; ++i) if(q[i].opt == 2) write(ans[i]), putchar('\n');
	return 0;
}
```



---

## 作者：Nopain (赞：1)

算是思维题？把树套树卡了差评。

刚接到这道题有个显然的思路：直接分块，整修打 tag，散修重构。但是查询需要块间做按位或操作，需要维护 bitset 一类的结构做按位或运算，这样时间复杂度上天，不可以直接维护。

所以想想区间颜色数有没有其他方法。

显然另一种维护方法是求 pre 值，即求这个位置的颜色上一次出现在哪里，如果没有则认为是 0 位置。那查询就显然可以变为查询区间中 $pre_i<l$ 的数量，是一个二维偏序问题。

再看看如何修改：直接的想法是区间内每个位置的 pre 值都会发生改变。

灵魂拷问：真的需要改这么多位置吗？

答案显然是不需要。如果我们把每一个连续的颜色相同的位置维护成一个段，类似珂朵莉树的结构，我们会发现总的颜色段数量将是 $O(n+m)$ 量级的。而将一个颜色段推平成另一个颜色，除了段头位置 ，修改前段头的后继位置 ，修改后段头的后继位置三个点的 pre 会发生改变外，其余位置的 pre 仍旧是 $i-1$ 。所以总修改数也在 $O(n+m)$ 量级。然后我们分类讨论这几个修改怎么做。

具体的，对于每一种颜色也维护一个珂朵莉树，你就可以快速求出每一个段头的前驱，后继位置。对于段头的 pre ，我们发现如果他不在修改的 $l$ 位置，那么他的 pre 会变为 $i-1$，否则一次 lower_bound 直接去改后颜色里找 $l$ 的前驱位置即可；对于修改前段头的后继位置，也只需要在改前颜色里找段头的后继位置，将后继的 pre 改成段头的前驱位置；对于改后段头的后继，显然这个后继位置的 pre 值应该是 $r$ 所以在做完所有修改后在改后颜色里查 $r$ 的后继位置，将其的 pre 改成 $r$ 即可。那么这道题就变成了带修二维数点，也就是三位偏序问题。由于空间卡的较死，这里采用了 cdq 分治实现。

关于实现，建议在颜色段里插入 0 位置和 $n+1$位置，会少很多特判。然后想清楚在写，每写一部分都做好调试。否则巨量的细节你很难调过来，记得离散化，开不下 1e9 的值域。

防抄袭只给核心部分（？

```
int n,m,a[N],p[N],lst[N],ans[S];
int qt;struct oper{int opt,a,b,c;} q[S],b[S];
struct node{int l,r;mutable int v;};
bool operator<(const node &a,const node &b){return a.l<b.l;}
set<node> s[N];
namespace uni{
	map<int,int> mp;int tot;
	inline void add(int x){if(mp.count(x)==0) mp[x]=++tot,s[tot].insert(node{0,0,tot}),s[tot].insert(node{n+1,n+1,tot});}
	inline int ask(int x){return mp[x];}
}
#define It set<node>::iterator
inline set<node>::iterator split(int op,int p){
	set<node>::iterator it=s[op].lower_bound(node{p,0,0});
	if(it!=s[op].end()&&it->l==p) return it;
	--it;
	if(it->r<p) return ++it;
	int l=it->l,r=it->r,v=it->v;
	s[op].erase(it);
	s[op].insert(node{l,p-1,v});
	return s[op].insert(node{p,r,v}).first;
}
inline void change(int x,int y){
	if(x<1||x>n) return;
	++qt;q[qt]=oper{-1,qt,p[x],x};p[x]=y;
	++qt;q[qt]=oper{1,qt,p[x],x};
}
inline void assign(int l,int r,int v){
	It itr=split(0,r+1),itl=split(0,l),IT;
	split(itl->v,l),split(itr->v,r+1);
	int ll,rr,vv,pre,pos;
	for(It it=itl;it!=itr;++it){
		ll=it->l,rr=it->r,vv=it->v;
		IT=s[vv].lower_bound(node{ll,0,0});
		IT--;pre=IT->r;
		IT++,IT++,pos=IT->l;
		change(pos,pre);
		IT--;s[vv].erase(IT);
		if(ll==l){
			IT=s[v].lower_bound(node{ll,0,0});IT--;
			change(ll,IT->r);
		}else change(ll,ll-1);
	}
	s[0].erase(itl,itr);
	s[0].insert(node{l,r,v});
	itr=split(v,r+1),itl=split(v,l);
	s[v].erase(itl,itr);
	s[v].insert(node{l,r,v});
	IT=s[v].lower_bound(node{r+1,0,0});
	change(IT->l,r);
}
int t[N],ta;
inline void add(int x,int v){while(x<=n) t[x]+=v,x+=(x&-x);}
inline int ask(int x){ta=0;while(x) ta+=t[x],x^=(x&-x);return ta;}
inline bool cmpb(const oper &x,const oper &y){return x.b^y.b?x.b<y.b:x.opt>y.opt;}
void cdq(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;cdq(l,mid);
	for(int i=l;i<=r;++i) b[i]=q[i];sort(q+l,q+r+1,cmpb);
	for(int i=l;i<=r;++i){
		if(q[i].a<=mid&&q[i].opt^2){
			add(q[i].c,q[i].opt);
		}else if(q[i].a>mid&&q[i].opt==2){
			ans[q[i].a]+=ask(q[i].c)-ask(q[i].b-1);
		}
	}
	for(int i=l;i<=r;++i) if(q[i].a<=mid&&q[i].opt^2) add(q[i].c,-q[i].opt);
	for(int i=l;i<=r;++i) q[i]=b[i];cdq(mid+1,r);
}
```


---

## 作者：_171829 (赞：0)

## 题意:

实现**区间赋值**，区间**数颜色**

## 分析：
首先我们维护一下每个位置左侧第一个同色点的位置，记为 `prei`，此时区间数颜色就被转化为了一个经典的  **二维数点问题**

通过将连续的一段颜色看成一个点的方式我们可以证明 `pre` 的变化量是 $O(n + m)$ 的，换句话说单次操作仅仅引起 $O(1)$ 的 `pre`  值变化，那么我们可以用 **cdq分治** 来解决动态的单点加矩形求和问题

`pre` 数组的具体变化可以使用 `set` 来进行处理（这个用 `set` 维护连续的区间的技巧也被称之为 `old driver tree` )

## 代码：
```cpp
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#define SNI set<nod>::iterator
#define SDI set<data>::iterator
using namespace std;
const int N = 1e5 + 10;
int n;
int m;
int pre[N];
int npre[N];
int a[N];
int tp[N];
int lf[N];
int rt[N];
int co[N];
struct modi {
  int t;
  int pos;
  int pre;
  int va;
  friend bool operator<(modi a, modi b) { return a.pre < b.pre; }
} md[10 * N];
int tp1;
struct qry {
  int t;
  int l;
  int r;
  int ans;
  friend bool operator<(qry a, qry b) { return a.l < b.l; }
} qr[N];
int tp2;
int cnt;
inline bool cmp(const qry& a, const qry& b) { return a.t < b.t; }
inline void modify(int pos, int co)  // 修改函数
{
  if (npre[pos] == co) return;
  md[++tp1] = (modi){++cnt, pos, npre[pos], -1};
  md[++tp1] = (modi){++cnt, pos, npre[pos] = co, 1};
}
namespace prew {
int lst[2 * N];
map<int, int> mp;  // 提前离散化
inline void prew() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]), mp[a[i]] = 1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &tp[i], &lf[i], &rt[i]);
    if (tp[i] == 1) scanf("%d", &co[i]), mp[co[i]] = 1;
  }
  map<int, int>::iterator it, it1;
  for (it = mp.begin(), it1 = it, ++it1; it1 != mp.end(); ++it, ++it1)
    it1->second += it->second;
  for (int i = 1; i <= n; i++) a[i] = mp[a[i]];
  for (int i = 1; i <= n; i++)
    if (tp[i] == 1) co[i] = mp[co[i]];
  for (int i = 1; i <= n; i++) pre[i] = lst[a[i]], lst[a[i]] = i;
  for (int i = 1; i <= n; i++) npre[i] = pre[i];
}
}  // namespace prew
namespace colist {
struct data {
  int l;
  int r;
  int x;
  friend bool operator<(data a, data b) { return a.r < b.r; }
};
set<data> s;
struct nod {
  int l;
  int r;
  friend bool operator<(nod a, nod b) { return a.r < b.r; }
};
set<nod> c[2 * N];
set<int> bd;
inline void split(int mid) {  // 将一个节点拆成两个节点
  SDI it = s.lower_bound((data){0, mid, 0});
  data p = *it;
  if (mid == p.r) return;
  s.erase(p);
  s.insert((data){p.l, mid, p.x});
  s.insert((data){mid + 1, p.r, p.x});
  c[p.x].erase((nod){p.l, p.r});
  c[p.x].insert((nod){p.l, mid});
  c[p.x].insert((nod){mid + 1, p.r});
}
inline void del(set<data>::iterator it) {  // 删除一个迭代器
  bd.insert(it->l);
  SNI it1, it2;
  it1 = it2 = c[it->x].find((nod){it->l, it->r});
  ++it2;
  if (it2 != c[it->x].end()) bd.insert(it2->l);
  c[it->x].erase(it1);
  s.erase(it);
}
inline void ins(data p) {  // 插入一个节点
  s.insert(p);
  SNI it = c[p.x].insert((nod){p.l, p.r}).first;
  ++it;
  if (it != c[p.x].end()) {
    bd.insert(it->l);
  }
}
inline void stv(int l, int r, int x) {  // 区间赋值
  if (l != 1) split(l - 1);
  split(r);
  int p = l;  // split两下之后删掉所有区间
  while (p != r + 1) {
    SDI it = s.lower_bound((data){0, p, 0});
    p = it->r + 1;
    del(it);
  }
  ins((data){l, r, x});  // 扫一遍set处理所有变化的pre值
  for (set<int>::iterator it = bd.begin(); it != bd.end(); ++it) {
    SDI it1 = s.lower_bound((data){0, *it, 0});
    if (*it != it1->l)
      modify(*it, *it - 1);
    else {
      SNI it2 = c[it1->x].lower_bound((nod){0, *it});
      if (it2 != c[it1->x].begin())
        --it2, modify(*it, it2->r);
      else
        modify(*it, 0);
    }
  }
  bd.clear();
}
inline void ih() {
  int nc = a[1];
  int ccnt = 1;  // 将连续的一段插入到set中
  for (int i = 2; i <= n; i++)
    if (nc != a[i]) {
      s.insert((data){i - ccnt, i - 1, nc}),
          c[nc].insert((nod){i - ccnt, i - 1});
      nc = a[i];
      ccnt = 1;
    } else {
      ccnt++;
    }
  s.insert((data){n - ccnt + 1, n, a[n]}),
      c[a[n]].insert((nod){n - ccnt + 1, n});
}
}  // namespace colist
namespace cdq {
struct treearray  // 树状数组
{
  int ta[N];
  inline void c(int x, int t) {
    for (; x <= n; x += x & (-x)) ta[x] += t;
  }
  inline void d(int x) {
    for (; x <= n; x += x & (-x)) ta[x] = 0;
  }
  inline int q(int x) {
    int r = 0;
    for (; x; x -= x & (-x)) r += ta[x];
    return r;
  }
  inline void clear() {
    for (int i = 1; i <= n; i++) ta[i] = 0;
  }
} ta;
int srt[N];
inline bool cmp1(const int& a, const int& b) { return pre[a] < pre[b]; }
inline void solve(int l1, int r1, int l2, int r2, int L, int R) {  // cdq
  if (l1 == r1 || l2 == r2) return;
  int mid = (L + R) / 2;
  int mid1 = l1;
  while (mid1 != r1 && md[mid1 + 1].t <= mid) mid1++;
  int mid2 = l2;
  while (mid2 != r2 && qr[mid2 + 1].t <= mid) mid2++;
  solve(l1, mid1, l2, mid2, L, mid);
  solve(mid1, r1, mid2, r2, mid, R);
  if (l1 != mid1 && mid2 != r2) {
    sort(md + l1 + 1, md + mid1 + 1);
    sort(qr + mid2 + 1, qr + r2 + 1);
    for (int i = mid2 + 1, j = l1 + 1; i <= r2; i++) {  // 考虑左侧对右侧贡献
      while (j <= mid1 && md[j].pre < qr[i].l) ta.c(md[j].pos, md[j].va), j++;
      qr[i].ans += ta.q(qr[i].r) - ta.q(qr[i].l - 1);
    }
    for (int i = l1 + 1; i <= mid1; i++) ta.d(md[i].pos);
  }
}
inline void mainsolve() {
  colist::ih();
  for (int i = 1; i <= m; i++)
    if (tp[i] == 1)
      colist::stv(lf[i], rt[i], co[i]);
    else
      qr[++tp2] = (qry){++cnt, lf[i], rt[i], 0};
  sort(qr + 1, qr + tp2 + 1);
  for (int i = 1; i <= n; i++) srt[i] = i;
  sort(srt + 1, srt + n + 1, cmp1);
  for (int i = 1, j = 1; i <= tp2; i++) {  // 初始化一下每个询问的值
    while (j <= n && pre[srt[j]] < qr[i].l) ta.c(srt[j], 1), j++;
    qr[i].ans += ta.q(qr[i].r) - ta.q(qr[i].l - 1);
  }
  ta.clear();
  sort(qr + 1, qr + tp2 + 1, cmp);
  solve(0, tp1, 0, tp2, 0, cnt);
  sort(qr + 1, qr + tp2 + 1, cmp);
  for (int i = 1; i <= tp2; i++) printf("%d\n", qr[i].ans);
}
}  // namespace cdq
int main() {
  prew::prew();
  cdq::mainsolve();
  return 0;
}  // 拜拜程序~
```


---

