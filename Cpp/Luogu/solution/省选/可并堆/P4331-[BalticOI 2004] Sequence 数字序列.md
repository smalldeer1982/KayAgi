# [BalticOI 2004] Sequence 数字序列

## 题目描述

给定一个整数序列 $a_1, a_2, \cdots , a_n$，求出一个递增序列 $b_1 < b_2 < ··· < b_n$，使得序列 $a_i$ 和 $b_i$ 的各项之差的绝对值之和 $|a_1 - b_1| + |a_2 - b_2| + \cdots + |a_n - b_n|$ 最小。

## 说明/提示

【数据范围】

- $40\%$ 的数据 $n≤5000$；
- $60\%$ 的数据 $n≤300000$；
- $100\%$ 的数据 $n≤10^6 , 0≤a_i≤2^{31}-1$；

题目来源：BalticOI 2004 Day 1, Sequence。

感谢 @TimeTraveller 提供 SPJ。


## 样例 #1

### 输入

```
5
2 5 46 12 1
```

### 输出

```
47
2 5 11 12 13```

# 题解

## 作者：wzporz (赞：91)

正好一年前做的这道题，趁着自己快退役了翻了翻记录，找到了这题。

看了一圈题解都是可并堆……我捉摸着这也不需要这么复杂的数据结构呀。

于是有了这篇题解，使用STL的堆就可以完成此题。

首先是一个显然的DP。

$f[i][j]$表示前i个数字，其中最后一个数字小于等于j，最优答案是多少。

考虑转移，考虑转移

首先让$f[i][j] = f[i-1][j] + |a[i] - j|$

然后再让$f[i][j] = min(f[i][j],f[i][j-1])$

如果我们得到这个dp数组，用一般的方法就可以倒着推回去得到方案。

其实$f[i][j]$其实是一个斜率单调以1递减的折线。我们只需要知道拐点就可以了。

考虑加入一个绝对值函数，如果在之前斜率为0的直线上，相当于这个左边斜率减一，否则相当于右边的斜率都加一（这时候斜率为为-1的就没啦，和右边并起来了）。

我们用堆来维护折线的拐点的横坐标即可。

一年前的代码，有点丑见谅。
```C++
#include<bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
typedef long long ll;
#define Rep(i,a,b) for(register int i=(a);i<=int(b);++i)
#define Dep(i,a,b) for(register int i=(a);i>=int(b);--i)
#define rep(i,a,b) for(register int i=(a);i<int(b);++i)
#define mem(x,v) memset(x,v,sizeof(x))
#define fi first
#define se second
#define debug(x) cout << #x" = " << x << endl;
#define pp(x,y) cout << "pp: " << x << " " << y << endl;
namespace IO{
    const int L=1<<15;char ibuf[L|1],*iS=ibuf,*iT=ibuf,obuf[L|1],*oS=obuf,*oT=obuf+L,c,st[66];int tp=0,f;
    inline char gc(){if(iS==iT) iT=(iS=ibuf)+fread(ibuf,sizeof(char),L,stdin);return (*iS++);}
    inline void flush(){fwrite(obuf,sizeof(char),oS-obuf,stdout);oS = obuf;}
    inline void pc(char c){*oS++=c;if(oS==oT) flush();}
    inline ll read(){ll x=0;f=1,c=gc();for(;!isdigit(c);c=gc())if(c=='-')f=-1;for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c&15);return x*f;}
    inline void write(ll x){if(!x) pc('0');if(x<0) pc('-'),x=-x;while(x) st[++tp]=x%10+'0',x/=10;while(tp) pc(st[tp--]);}
    inline void writeln(ll x){write(x);pc('\n');}
    struct IOflusher{~IOflusher(){flush();}}_ioflusher_;
}using IO::read;using IO::write;using IO::writeln;using IO::gc;using IO::pc;
int n,m,ans,x;
priority_queue<int>q;
int a[1000005],b[1000005];
signed main(){
    n=read();q.push(b[1] = read()-1);
    a[1] = q.top();
    Rep(i,2,n){
        x=read()-i;
        q.push(b[i] = x);
        if (q.top()>x){
            ans+=q.top()-x;
            q.pop();q.push(x);
        }
        a[i] = q.top();
    }
    for(int i=n-1;i>=1;i--) a[i]=min(a[i],a[i+1]);
    ll res = 0;
    for(int i=1;i<=n;++i) res += abs(a[i]-b[i]);
    writeln(res);
    for(int i=1;i<=n;i++)
        write(a[i]+i),pc(' ');
    return 0;
}

```

---

## 作者：Soulist (赞：45)

标签：贪心+数据结构

$Step1:$ 我们先考虑原题的弱化版：

求不下降序列$b$使得$\sum_{i=1}^n|a_i-b_i|$最小

我们可以感性的得到两个结论：

-------------

若：

$$1.a_1\le a_2\le a_3...\le a_n $$

则 $b_i=a_i$

$$2.a_1\ge a_2\ge a_3...\ge a_n$$

则 $b_i=a$的中位数

-------------------

根据这两个结论，我们可以得到一个比较感性的做法：

将原序列分成单调不升的$m$段，则每一段我们都取中位数。

然而这个做法不完全正确，比如我们取完中位数后是这样的序列：

$$3~3~3~2~2$$

我们发现这仍然不单调不降，所以我们需要合并这两个区间并重新取个中位数。

也就是说我们需要合并区间以求中位数。

-------------------------

#### $Step2:$ 如何求中位数？

我们考虑维护一个堆，将整个区间的元素都存入堆内，每次从里面弹出最大元素，直到堆内只剩一半的元素为止

你可能会认为这个做法的正确性有问题，在我们合并区间的时候，新中位数是不是已经被删除了？

比如合并的区间是这样的：$4~5~6~| ~7~8$

本来的中位数是$5$，我们删除了$6$，但合并后中位数变成了$6$，在上述流程中是不能做到的，也就是错了？吗？

并不是，我们发现合并区间的前提条件是某个区间的中位数比它后面的区间中位数大，所以我们能保证，中位数一定大于前面这个区间的中位数而小于后面区间的中位数，换而言之，这样合并是正确的。

现在我们考虑实现，我们发现我们需要兹娃的操作只有弹出堆内最大值和合并堆，用左偏树可以做到$O(n\log n)$

-------------------------------

#### $End:$ 那么原题怎么做呢？

假设我们求出了答案，那么给每对$a_i,b_i$减去一个$i$答案并不会受到影响，而此时，我们只需要$b$数组单调不降即可，转换成了刚刚解决的问题。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define ls(x) ch[0][x]
#define rs(x) ch[1][x]
#define int long long
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 1e6 + 5 ; 
int n, top, Ans ;  
int a[N], b[N], ch[2][N], dis[N] ;
struct node {
	int rt, l, r, sz, val ; 
} s[N];
int merge( int x, int y ) {
	if( !x || !y ) return x + y ; 
	if( a[x] < a[y] ) swap( x, y ) ; 
	rs(x) = merge( rs(x), y ) ; 
	if( dis[rs(x)] > dis[ls(x)] ) swap( rs(x), ls(x) ) ;
	dis[x] = dis[rs(x)] + 1 ; return x ; 
}
int Del( int x ) { return merge( ls(x), rs(x) ) ; }
signed main()
{
	n = read() ; dis[0] = -1 ; 
	rep( i, 1, n ) a[i] = read() - i;
	rep( i, 1, n ) {
		s[++ top] = (node){ i, i, i, 1, a[i] } ; 
		while( top != 1 && s[top - 1].val > s[top].val ) {
			-- top ; s[top].rt = merge( s[top].rt, s[top + 1].rt ) ; 
			s[top].sz += s[top + 1].sz ; s[top].r = s[top + 1].r ; 
			while( s[top].sz > ( s[top].r - s[top].l + 2 ) / 2 ) { //此处可行性
			//合并的前提是左平均数小于右平均数，把左全部丢入右，平均数变大 
				-- s[top].sz, s[top].rt = Del( s[top].rt ) ; 
			}
			s[top].val = a[s[top].rt] ; 
		}
	}
	int cnt = 1 ;
	rep( i, 1, n ) {
		if( s[cnt].r < i ) ++ cnt ; 
		Ans += abs( s[cnt].val - a[i] ) ; 
	}
	printf("%lld\n", Ans ) ; cnt = 1 ; 
	rep( i, 1, n ) {
		if( s[cnt].r < i ) ++ cnt ;  
		printf("%lld ", s[cnt].val + i ) ; 
	}
	return 0;
}
```

---

## 作者：Nemlit (赞：23)

PS：参考了黄源河的论文《左偏树的特点及其应用》

[原文地址](https://www.cnblogs.com/bcoier/p/10355646.html)

题目描述：给定一个整数序列$a_1, a_2, … , a_n$，求一个递增序列$b_1 < b_2 < … < b_n$，使得序列$a_i$和$b_i$的各项之差的绝对值之和 $|a_1 - b_1| + |a_2 - b_2| + … + |a_n - b_n|$ 最小。

不难发现两条性质：

①：若原序列a满足$a_1 < a_2 < … < a_n$，显然最优情况为$b_i=a_i$

②：若原序列a满足$a_1 > a_2 > … > a_n$，显然最优情况为$b_{mid}=x$（x为a中位数）

有了上述的两种情况，不难发现，整个a序列是尤一些单调区间组成。

所以我们可以将原序列a拆成若干个单调区间，最后再将答案合并。

那两段区间的答案怎么合并呢？

我们可以重新找一个中位数来合并即可。

不断的找中位数，不难想到[这道题](https://www.luogu.org/problemnew/show/P1168)，可是那道题是一个一个加入进堆，而现在我们要解决的是将两个堆合并来找中位数，直接上二叉堆合并复杂度为$O(n)$，所以不难想到[可并堆](https://www.luogu.org/problemnew/show/P3377)（这里使用左偏树）。

假设我们已经找到前k个数的最优解，队列中有$cnt$段区间，每段区间最优解为$w_1,w_2,…,w_{cnt}$，现在要加入$a_{k+1}$，并更新队列。

首先把$a_{k+1}$加入队尾，令$w_{cnt+1}=a_{k+1}$，如果$w_{cnt}>w_{cnt+1}$，就将最后两个区间合并，并找出新区间的最优解。重复上述过程，直至满足$w$单调递增。

注意：题目要求的是一个递增序列b，可以用减下标来实现（即输入时把每个数都减去对应下标，输出时加上），这样就可以将递增序列转化成不下降序列，这样就可以保证每一段区间的序列b不一样了（原本有很多连续一段区间全是中位数，不能保证递增）。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define debug printf("Now is Line : %d\n",__LINE__)
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
#define mod 1000000007
il int read()
{
    re int x=0,f=1;re char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return x*f;
}
#define _ 1000006
int n,dis[_],ch[_][2],cnt;
ll a[_],b[_],ans;
struct node{int root,ls,rs,size,val;}e[_];
il int merge(int x,int y)
{
    if(!x||!y) return x+y;
    if(a[x]<a[y]||(a[x]==a[y]&&x>y)) swap(x,y);
    ch[x][1]=merge(ch[x][1],y);
    if(dis[ch[x][0]]<dis[ch[x][1]]) swap(ch[x][0],ch[x][1]);
    dis[x]=dis[ch[x][1]]+1;
    return x;  
}
int main()
{
    n=read(); dis[0]=-1;
    for(re int i=1;i<=n;++i) a[i]=read()-i;
    for(re int i=1;i<=n;++i)
    {
        e[++cnt]=(node){i,i,i,1,a[i]};
        while(cnt>1&&e[cnt].val<e[cnt-1].val)
        {
            --cnt;
            e[cnt].root=merge(e[cnt].root,e[cnt+1].root);
            e[cnt].size+=e[cnt+1].size;
            e[cnt].rs=e[cnt+1].rs;
            while(e[cnt].size*2>e[cnt].rs-e[cnt].ls+2)
            {
                --e[cnt].size;
                e[cnt].root=merge(ch[e[cnt].root][0],ch[e[cnt].root][1]);
            }
            e[cnt].val=a[e[cnt].root];
        }
    }
    for(re int i=1;i<=cnt;++i)
    {
        for(re int j=e[i].ls;j<=e[i].rs;++j)
        {
            b[j]=e[i].val;
            ans+=abs(a[j]-b[j]);
        }
    }
    printf("%lld\n",ans);
    for(re int i=1;i<=n;++i) printf("%lld ",b[i]+i);
    return 0;
}
```

---

## 作者：Rayment (赞：19)

# Solution
dalao安利的一道论文题。。

为了方便思考，我们可以把ai减去i，把严格递增的条件转化为非严格递增的条件。

不妨先考虑特殊情况，a如果是递增的，那么直接bi=ai即可。如果是递减的，就取它的中位数，为什么？

先考虑一个简化的问题，是一个初中数学题，求使得$|A-x|+|B-x|(A\leq B)$最小的x值。这个比较简单，画个数轴，然后把绝对值转化为距离，就是$x\in[A,B]$。那么再继续扩展呢，沿用之前的方法，容易发现最中间的值总是最优的，也就是中位数，当然了偶数个的情况下，答案是最中间的区间。

拓展回本题，就是先把这个序列分成多段，现在的问题就是如何合并两段数列的答案。不妨设$x_1,x_2$分别表示两段数列最优时x的值。如果$x_1\leq x_2$，这是合法的，那么显然最优是无需操作。而如果$x_1>x_2$，那么就合并这两个段中的元素，这又变成了上面谈论过的问题，取中位数为新的x。这个合并操作可以用左偏树来维护。
# Code
```cpp
#include <algorithm>
#include <cstdio>
#define rg register
using namespace std;
typedef long long ll;
const int maxn=1000010;
int n,top,b[maxn];
ll ans;
struct data{int l,r,sz,rt,val;}stk[maxn];
struct leftist{
	int dis[maxn],ch[maxn][2],val[maxn];
	int merge(int x,int y)
	{
		if(!x||!y) return x|y;
		if(val[x]<val[y]) swap(x,y);
		ch[x][1]=merge(y,ch[x][1]);
		if(dis[ch[x][1]]>dis[ch[x][0]]) swap(ch[x][0],ch[x][1]);
		dis[x]=dis[ch[x][1]]+1;
		return x;
	}
	int erase(int x){return merge(ch[x][0],ch[x][1]);}
}h;
template <typename Tp> inline void read(Tp &x)
{
	x=0;int f=0;char ch=getchar();
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') f=1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	if(f) x=-x;
}
inline int abs(int x){return x<0?-x:x;}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	read(n);
	for(rg int i=1;i<=n;i++) read(h.val[i]),h.val[i]-=i;
	stk[top=1]=(data){1,1,1,1,h.val[1]};
	for(rg int i=2;i<=n;i++)
	{
		stk[++top]=(data){i,i,1,i,h.val[i]};
		while(top^1&&stk[top].val<stk[top-1].val)
		{
			top--;
			stk[top].rt=h.merge(stk[top].rt,stk[top+1].rt);
			stk[top].sz+=stk[top+1].sz;stk[top].r=stk[top+1].r;
			while(stk[top].sz>(stk[top].r-stk[top].l+2)/2)
			{
				stk[top].sz--;
				stk[top].rt=h.erase(stk[top].rt);
			}
			stk[top].val=h.val[stk[top].rt];
		}
	}
	for(rg int i=1,p=1;i<=n;i++)
	{
		if(i>stk[p].r) p++;
		ans+=abs(stk[p].val-h.val[i]);
	}
	printf("%lld\n",ans);
	for(rg int i=1,p=1;i<=n;i++)
	{
		if(i>stk[p].r) p++;
		printf("%d ",stk[p].val+i);
	}
	putchar('\n');
	return 0;
}
```


---

## 作者：LengChu (赞：19)

## 一.一个约定

#### 把a[i]都减去i，易知b[i]也减去i后答案不变，本来b要求是递增序列，这样就转化成了不下降序列，方便操作。

（以下讨论的情况均为转化后，也就是要求的b序列为不下降序列）



------------


## 二.两个结论

#### 1.如果a是一个不下降序列，那么b[i]==a[i]时取得最优解。

    解释：显而易见。

#### 2.如果a是一个严格递减序列，则取a序列的中位数x，令b[1]=b[2]=b[3]=...=b[n]=x，即是最优解。

    解释：感觉是初中数学。想象一个数轴，a序列中的数为数轴上的点，那么问题就是要求一个点到所有点的距离和最小，显而易见法（？）可得这个点一定在这些数的中位数上。
    
    

------------

    
## 三.考虑一般情况

a序列一定不可能这么良心是上面的两种情况。

但它一定是由这两种情况组成的，也就是把a序列看成一段一段的，每一段要么不下降，要么严格递减。

那么要分别计算出每一段的答案是很容易的。

问题是要保证b序列不下降，所以该怎么合并答案呢？

这里又有一个结论：

### 把两段合在一起，取一个新的中位数就行了=。=

道理是同上的。



------------


## 四.具体操作

    1.初始令每一段的长度为1，令中位数为ci，则ci = ai，然后一段一段的合并起来。

    若ci <= ci+1，那么就保持不变；否则将ci和ci+1所在的区间合并，取一个新的中位数，作为新区间的答案。

.........................................................................................................................................

    2.这里会出现一个问题，就是第一次合并时，有可能ci+1>=ci，没有把两个区间并起来取中位数。

    但是可能后面的那个区间又和其他区间合并了，中位数变小了，以至于还要和前一个区间合并。

    其实很简单qwq，用栈维护一下就好了。
    
   .........................................................................................................................................

    3.那么问题来了，怎么求中位数呢？求了中位数还要把两段区间合并起来？

    （下面一段话引用于某dalao博客）

    因此我们需要一个数据结构，支持合并、查询最大值和删除。

    为什么要查询最大值和删除呢？因为维护中位数可以只维护⌈1/2区间长度⌉小的数，用一个大根堆，则堆顶就是中位数。

    合并完两个区间后，就一直删除堆顶，直到元素个数 = ⌈1/2区间长度⌉。

    显然是用左偏树啦qwq。
    
    

------------

    
Code：
```
#include<bits/stdc++.h>
#define ll long long
#define in inline
#define rint register int
#define N 1000010
using namespace std;
int n,m;
int d[N],ls[N],rs[N];
ll a[N],b[N],ans;
struct node{
	int rt,l,r,siz;
	ll w;
}s[N];
in ll read()
{
	ll x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
in int merge(int x,int y)
{
	if(x==0||y==0) return x+y;
	if(a[x]<a[y]) swap(x,y);
    rs[x]=merge(rs[x],y);
    if(d[ls[x]]<d[rs[x]]) swap(ls[x],rs[x]);
    d[x]=d[rs[x]]+1;
    return x;
}
in void work()
{
	for(rint i=1;i<=n;i++)
	{
		s[++m]=(node) { i,i,i,1,a[i] };
		while(m>1&&s[m].w<s[m-1].w)
		{
			m--;
			s[m].rt=merge(s[m].rt,s[m+1].rt);
			s[m].siz+=s[m+1].siz; 
			s[m].r=s[m+1].r;
			while(s[m].siz>(s[m].r-s[m].l+1+2)>>1)//向上取整 
			{
				s[m].siz--;
				s[m].rt=merge(ls[s[m].rt],rs[s[m].rt]);
			}
			s[m].w=a[s[m].rt];
		}
	}
	for(rint i=1;i<=m;i++)
		for(rint j=s[i].l;j<=s[i].r;j++) 
			b[j]=s[i].w,ans+=abs(a[j]-b[j]);
}
int main()
{
	d[0]=-1; n=read();
	for(rint i=1;i<=n;i++) a[i]=read()-i;
	work();
	printf("%lld\n",ans);
	for(rint i=1;i<=n;i++) printf("%lld ",b[i]+i);
	return 0;
}

```


---

## 作者：ZYF_B (赞：13)

最近看了2018年高睿泉的集训队论文《浅谈保序回归问题》。

将问题转化为$b$非严格递增后，这题就是一个$L_1$问题，且偏序关系构成一条链，可以使用论文3.1中的那种贪心做法，由于$L_1$均值为带权中位数，这个做法其实就是左偏树做法。

也可以使用整体二分，每层枚举前多少个取mid最优，比左偏树做法好写多了。

整体二分做法时间复杂度为$O(n\log v)$,左偏树做法时间复杂度为$O(n\log n)$,都可通过此题。

放一下整体二分做法：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
#define INF 2147483647
using namespace std;

inline int read()
{
	int f=1,x=0;char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-') f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=x*10+s-48;
		s=getchar();
	}
	return f*x;
}

const int N=1e6+5;
ll a[N],b[N];
int n;

void solve(int L,int R,ll l,ll r)
{
	if(L>R) return;
	if(l>=r) return;
	ll mid=(1ll*l+r)/2;
	ll sum=0;
	for(int i=L;i<=R;i++) sum+=abs(a[i]-mid-1);
	ll mn=sum,id=L-1;
	for(int i=L;i<=R;i++)
	{
		sum-=abs(a[i]-mid-1);
		sum+=abs(a[i]-mid);
		if(sum<mn)
		{
			mn=sum;
			id=i;
		}
	}
	for(int i=L;i<=id;i++) b[i]=mid;
	for(int i=id+1;i<=R;i++) b[i]=mid+1;
	solve(L,id,l,mid);
	solve(id+1,R,mid+1,r);
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read()-i;
	solve(1,n,-INF,INF);
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans+=abs(a[i]-b[i]);
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)
		printf("%lld ",b[i]+i);
	return 0;
}
```

---

## 作者：a154051 (赞：8)

[博客链接](https://a154051.gitee.io/2021/09/25/solution-P4331-sequence/)

好多题解都是用的中位数做法，其实贪心就可以直接做。

## 题意

给定一个长度为 $n$ 的整数序列 $a$，求出一个严格递增整数序列 $b$，使得 $\sum^n_{i=1}\left\vert a_i-b_i\right\vert$ 最小。

## 做法

首先给 $b$ 赋一个初值，使得 $b_i\le a_i(i\in n)$ 并且 $b_i=b_{i-1}+1(i\in [2,n])$。

在这种情况下，要想使答案更优只能增大 $b$ 序列或不变。

因为 $b$ 严格递增，并且 $b_i=b_{i-1}+1$，所以要想使 $b_i$ 增加 $x$，就要对 $[i,n]$ 整个区间加上 $x$。

定义 $val_i=\begin{cases}1&a_i>b_i\\-1&a_i\le b_i\end{cases}$，$sum_i=\sum\limits_{j=i}^n val_j$。

然后重复执行下列操作：

1. 在 $[1,n]$ 中找到最大的 $sum$ 的位置 $k$，可以发现 $b_i=b_{i-1}+1(i\in[k+1,n])$，证明在下面。

2. 设 $x=\min\{a_i-b_i \}(i\in[k,n],a_i-b_i>0)$，令 $b_i+x(i\in[k,n])$。

3. 更新 $val$ 和 $sum$。

直到所有的 $sum$ 都小于等于 $0$。

正确性证明：

对初始序列 $b$ 执行一遍该操作显然正确。

记 $last$ 为上一次操作中最大的 $sum$ 的位置，$k$ 为这次操作中最大的 $sum$ 的位置。

可以得到，对于任意的 $i\in [1,last-1]$，都有 $sum_i\le sum_{last}$。

在上一次操作中，$[last,n]$ 中至少会有一个位置的 $val$ 变为 $-1$，则 $sum_i(i\in[1,last-1])$ 只会变得更小，所以 $k$ 不可能在 $[1,last-1]$ 中，$k$ 只会越来越靠右，因此 $b_i=b_{i-1}+1(i\in[k+1,n])$，所以对 $b_i(i\in [k,n])$ 执行该操作显然也正确。

证毕。

用线段树维护 $sum$，$set$ 维护 $[k,n]$ 中 $a_i-b_i(i\in[k,n])$ 大于 $0$ 的元素。 

每次操作用线段树求出 $[1,n]$ 中最大的 $sum$ 的位置 $k$，将 $set$ 中位置在 $[1,k-1]$ 的元素删除，在 $set$ 中查询此时 $a_i-b_i$ 的最小值，将等于该值的元素删除，并在线段树上将区间 $[1,\text{该元素位置}]$ 中所有 $sum$ 减 $1$。

由于不会添加元素，所以 $set$ 至多有 $n$ 次删除操作，线段树至多有 $n$ 次修改操作。

时间复杂度为 $O(n\log n)$。

复杂度虽然正确，但常数有点大，时间卡得很紧，要开 $O2$ 才能过。

## 代码

```cpp
#include <bits/stdc++.h>
#define mk(x,y) make_pair(x,y)
#define ls now<<1
#define rs now<<1|1
using namespace std;
typedef long long ll;
const int mn=1e6+7;
struct tree {
    int ans,mx,tag;
}tr[mn<<2];
int a[mn],sum[mn],val[mn];
ll b[mn];
set<pair<ll,int> > st;
int in()
{
    int x=0;
    char c=getchar();
    while(!isdigit(c))  c=getchar();
    while(isdigit(c))
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}
void upd(int now)
{
    if(tr[rs].mx>=tr[ls].mx)
      tr[now].mx=tr[rs].mx,tr[now].ans=tr[rs].ans;
    else
      tr[now].mx=tr[ls].mx,tr[now].ans=tr[ls].ans;
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        tr[now].mx=sum[l];
        tr[now].ans=l;
        return ;
    }
    int mid=(l+r)>>1;
    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);
    upd(now);
}
void push(int now)
{
    if(!tr[now].tag)  return ;
    tr[now<<1].mx+=tr[now].tag;
    tr[now<<1].tag+=tr[now].tag;

    tr[now<<1|1].mx+=tr[now].tag;
    tr[now<<1|1].tag+=tr[now].tag;
    tr[now].tag=0;
}
void add(int now,int l,int r,int x,int v)
{
    if(r<=x)
    {
        tr[now].mx+=v;
        tr[now].tag+=v;
        return ;
    }
    push(now);
    int mid=(l+r)>>1;
    if(x>mid)  add(now<<1|1,mid+1,r,x,v);
    add(now<<1,l,mid,x,v);
    upd(now);
}

int main()
{
    int n,mi=1;
    n=in();
    ll ans=0;
    for(int i=1;i<=n;++i)
    {
        a[i]=in();
        mi=min(mi,a[i]-i+1);
    }
    for(int i=1;i<=n;++i)
    {
    	b[i]=mi+i-1;
    	ans+=abs(b[i]-a[i]);
    	if(b[i]<a[i])  val[i]=1,st.insert(mk(a[i]-b[i],i));
    	else  val[i]=-1;
	}
    sum[n]=val[n];
    for(int i=n-1;i>=1;--i)  sum[i]=sum[i+1]+val[i];
    build(1,1,n);
    int last=1,cnt=0;
    while(1)
    {
        if(tr[1].mx<=0){  //终止条件
            for(int i=last;i<=n;++i)  b[i]+=cnt;
            break;
        }
        int now=tr[1].ans;  //最大的 sum 的位置
        for(int i=last;i<now;++i){  //删除 set 中多余的元素
            b[i]+=cnt;
            if(a[i]-b[i]-cnt>0)  st.erase(mk(a[i]-b[i],i));
        }
        last=now;
        ans-=tr[1].mx*((*st.begin()).first-cnt);
        cnt=(*st.begin()).first;
        while(st.size())  //删除 a-b 等于 0 的元素
        {
            pair<ll,int> it=*st.begin();
            if(it.first!=cnt)  break;
            add(1,1,n,it.second,-2);  //维护 sum
            st.erase(st.begin());
        }
    }
    printf("%lld\n",ans);
    for(int i=1;i<=n;++i)  printf("%lld ",b[i]);
    return 0;
}
```


---

## 作者：Yyxxxxx (赞：6)

## 题意
给一个序列$a_1,a_2,a_3...a_n$，求一个序列$b$，其中$b_1<b_2<b_3<...<b_n$，使$|a_1-b_1|+|a_2-b_2|+...+|a_n-b_n|$最小  
首先$b$是递增的不好弄，那就减去下标，变为不减序列就行，记得到时候得加回来。

那显然$a$序列没有限制，那就考虑最简单的
- $a$是递增的，那么$b$与$a$完全一样就行了。
- $a$是递减的，那么只有形式为$b_1=b_2=b_3=...=b_n=x$使原式最小，而用初中的 **绝对值的几何意义** 就可以知道$x$为$a$序列的中位数

那真实的$a$是怎样呢？是一堆递增序列和递减序列拼成的！  
那我们就可以把每部分的递增序列和递减序列的取值求出来，再合并。  
令要合并的两个序列为$c_1,c_2$且$c_1$在$c_2$的前面
且它们的最优解为$x_1,x_2$

- 如果$x_1\le x_2$，不需要操作
- 如果$x_1>x_2$，重新求一次中位数就行了。

而这种把堆合起来的操作用[可并堆](https://www.luogu.com.cn/problem/P3377)就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
struct Node
{
	int l,r,fa,val,dis;
}ltt[maxn];
struct dat//求每一个区间的最优解 
{
	int l,r,siz,fa,val;//l左端，r右端，siz长度，val最优解 
}c[maxn];
inline int merge(int x,int y)//可并堆合并操作 
{
	if(!x||!y)return x+y;
	if(ltt[x].val<ltt[y].val)swap(x,y);
	ltt[x].r=merge(ltt[x].r,y);
	ltt[ltt[x].r].fa=x;
	ltt[x].dis=ltt[ltt[x].r].dis+1;
	if(ltt[ltt[x].l].dis<ltt[ltt[x].r].dis)swap(ltt[x].l,ltt[x].r);
	return x;
}
long long ans=0;//答案 
int b[maxn];
int main()
{
	int n,cnt=0;
	ltt[0].dis=-1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ltt[i].val);
		ltt[i].val-=i;	//先减去i，回头加上，可以使b变为不减序列 
	}	
	for(int i=1;i<=n;i++)
	{
		c[++cnt]=(dat){i,i,1,i,ltt[i].val};//新区间 
		while(cnt>1&&c[cnt-1].val>c[cnt].val)//有至少两个区间，且最后两个区间要合并 
		{
			cnt--;//合并，区间数-1 
			c[cnt].fa=merge(c[cnt].fa,c[cnt+1].fa);//合并 
			c[cnt].siz=c[cnt].siz+c[cnt+1].siz;//长度加上 
			c[cnt].r=c[cnt+1].r;//右端更新为右边区间的右端 
			while(c[cnt].siz>(c[cnt].r-c[cnt].l+3)/2)//求中位数 
			{
				c[cnt].siz--;//每次减一，直到长度为真正长度的一半 
				c[cnt].fa=merge(ltt[c[cnt].fa].l,ltt[c[cnt].fa].r);//合并两个，去掉最值 
			}
			c[cnt].val=ltt[c[cnt].fa].val;//更新最优解 
		}
	}
	int m=1;
	for(int i=1;i<=n;i++)
	{
		if(i>c[m].r)m++;
		ans+=abs(c[m].val-ltt[i].val);//每个区间求b的值，然后累加上答案 
	}
	printf("%lld\n",ans);
	m=1;
	for(int i=1;i<=n;i++)
	{
		if(i>c[m].r)m++;//不要忘了加上i 
		printf("%d ",c[m].val+i);
	}
	return 0;	
}
```


---

## 作者：too_later (赞：4)

[题面](https://www.luogu.com.cn/problem/P4331)

### 题意：

- 给定一个整数序列 $a_1,a_2,...,a_n$。

- 求一个递增序列 $b_n$，使得 $\sum|a_i -b_i|$ 最小。

- $1\le n\le 10^6,1\le a_i \le 2\times10^9$。

### 思路：

~~这题如果能有部分分提示一下部分思路就更好了。~~

#### 不递减处理

首先，原题的 $b_i$ 递增很难受，应该让他成为不递减的。这能做到！

令 $b_i=i+val_i$，那么原式就为 $\sum|a_i-(i+val_i)|=\sum\limits|(a_i-i)-val_i|$。

那么我们把 $a_i,b_i$ 都减去 $i$，就对应新的 $a_i,val_i$ 了，满足了不递减。

#### 部分->局部

根据我们初一数学经验，就是在数轴上有 $n$ 个点，求一个从左往右递增的点集，使得一一对应的距离最小。

显然，如果 $a_i$ 是递增的，那么一一对应。

如果 $a_i$ 是递减的，那么取中位数。（不懂得可以手动模拟一下，画个数轴。）

那么我们的目的就是让 $b_i$ 不递减，那么把原来的数列分为这样两种，可以分别完成代替。那么如果还有递减的怎么办呢？那还是取中位数（这里是取 $a_i$ 的中位数，不是 $b_i$ 的）。

#### 左偏树

我们去维护这样一个东西，可以满足：

- 查询中位数

- 合并两个堆

显然左偏树，维护一个大根堆，只要大于 $\frac{size+1}{2}$ 就 pop。

#### 一点小补充

还有，一定会有人有疑问：比如 $7,8,4,5,6$ 这样子的，只剩下了一个 $7$，右边剩下一个 $4.5$，那么合并不是变成了 $5$ 嘛？

注意，我们这里是一有递减就合并，那么在加入之前，后面的中位数一定大于前面的中位数。在加入之后，后面的中位数一定小于前面的中位数。好了，那么后面这个堆，只有前一半有用，可以保证。

### Code:

时间复杂度 $O(nlogn)$

```cpp
#include<bits/stdc++.h>
#define int long long
#define W while
#define I inline
#define RI register int
#define CI const int
#define DB double
#define ll long long
#define rep(i,a,b) for(RI i=a;i<=b;i++)
#define dow(i,a,b) for(RI i=a;i>=b;--i)
#define edg(i,u,v) for(RI v,i=head[u];v=e[i].to,i;i=e[i].next)
using namespace std;
CI N=1e6+5;
int n,m,ans,top,a[N],sz[N],l[N],r[N],dist[N],lc[N],rc[N],rt[N],val[N];
I int merge(int x,int y){
	if(!x||!y) return x|y;a[y]>a[x]&&(swap(x,y),0);rc[x]=merge(rc[x],y); // 注意这里是 a 不要写成 val~! 
	dist[lc[x]]<dist[rc[x]]&&(swap(lc[x],rc[x]),0);dist[x]=dist[rc[x]]+1;return x;
}
signed main(){
	scanf("%lld",&n);rep(i,1,n) scanf("%lld",&a[i]),a[i]-=i,dist[i]=-1; // 不递减
	rep(i,1,n){
		++top,sz[top]=1,l[top]=r[top]=rt[top]=i,val[top]=a[i];
		W((top^1)&&val[top]<val[top-1]){ // 递减就合并 
			rt[top-1]=rt[top]=merge(rt[top-1],rt[top]);
			sz[top-1]+=sz[top],r[top-1]=r[top];top--;
			W(sz[top]>(r[top]-l[top]+2)/2) rt[top]=merge(lc[rt[top]],rc[rt[top]]),sz[top]--; // 中位数处理 
			val[top]=a[rt[top]];
		}
	}
	rep(i,1,top) rep(j,l[i],r[i]) ans+=abs(a[j]-val[i]);printf("%lld\n",ans);
	rep(i,1,top) rep(j,l[i],r[i]) printf("%lld ",val[i]+j);return 0;
}
```

---

## 作者：Register (赞：2)

###  首先考虑要构造序列是单调不降的：

- 如果原序列是单调下降的:

结论：全部取中位数

证明：

首先证明全部都取一样的：随便假设一个点 $x$ ， $b_x=a_x$ （自己理解，一定会有这个 $x$ ），$x$ 之前的点都小于等于 $x$ ，最优就都和 $x$ 一样， $x$ 后的同理。

剩下的就扔掉数轴上，所以取中位数最优（初一数学）。

- 如果原序列单调不下降：显然 $b$ 数组等于 $a$ 数组最好。

- 来看随机的序列：

一段单调下降的序列：显然都取一样的值。

假设前面的数都暂时取好值，现在给一段单调下降赋值，显然取中位数最优，但是这个中位数不一定能大于等于前面的取值。

怎么办呢？貌似直接取到上一段序列的取值即可。但是你发现这样做两点序列相当于是一段，不如直接合并两段再取中位数。

然后就一直合并直到这一段中位数比前一段大（时间复杂度你想想是对的）。

现在问题已经变成了个数据结构题：序列中位数，序列合并。

你说：这不是直接平衡树/权值线段树合并吗吗（然而被卡了（虽说我没试验过））？

于是你想起了可并堆（左偏树）。

接着我想：对顶堆还行吧（然而要维护一个大根堆，一个小根堆，有点麻烦）？

正解是只维护一个大根堆，只保留一半的数（弹掉大的）。

你说这不是假的吗？没保留的数可能又成为中位数。

此时的情况是这个序列的数是大于前面的（不是全都大于，感性理解），但是这样的话应该就直接取值了，不应该在一个序列里，所以是不存在的。

然后用栈模拟一下过程。

### 接着回到原题：

首先给所有 $a_i$ 减去 $i$ ，最后再加上即可，比较好理解。

### 代码:

```cpp
#include <cstdio>
#define reg register
const int N=1e6+5;
inline int read(){
    char ch=getchar();int res=0,w=1;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
    return res*w;
}
int n,top,a[N],dis[N],ch[N][2];
long long ans;
struct node{
	int l,r,sz,rt,v;
}s[N];
inline void Swap(int&x,int&y) {int t=x;x=y;y=t;}
int merge(int x,int y){
	if(!x||!y) return x|y;
	if(a[x]<a[y]) Swap(x,y);
	ch[x][1]=merge(y,ch[x][1]);
	if(dis[ch[x][1]]>dis[ch[x][0]]) Swap(ch[x][0],ch[x][1]);
	dis[x]=dis[ch[x][1]]+1;return x;
}
signed main(){
	n=read();
	for(reg int i=1;i<=n;i++) a[i]=read()-i;
	s[top=1]=(node){1,1,1,1,a[1]};
	for(reg int i=2;i<=n;i++)
	{
		s[++top]=(node){i,i,1,i,a[i]};
		while(top-1&&s[top].v<s[top-1].v)
		{
			top--;s[top].rt=merge(s[top].rt,s[top+1].rt);s[top].sz+=s[top+1].sz;s[top].r=s[top+1].r;
			while(s[top].sz>(s[top].r-s[top].l+2)/2) {s[top].sz--;s[top].rt=merge(ch[s[top].rt][0],ch[s[top].rt][1]);}
			s[top].v=a[s[top].rt];
		}
	}
	for(reg int i=1,j=1;i<=n;i++) {j+=(i>s[j].r)?1:0;ans+=s[j].v>a[i]?s[j].v-a[i]:a[i]-s[j].v;}
	printf("%lld\n",ans);
	for(reg int i=1,j=1;i<=n;i++) {j+=(i>s[j].r)?1:0;printf("%d ",s[j].v+i);}
	puts("");
    return 0;
}
```


---

## 作者：Honor誉 (赞：1)


考虑两种情况：

1.$a_1$<$a_2$<$a_3$<$a_4$...<$a_n$

直接令$b_i$=$a_i$,最小。

2.$a_1$>$a_2$>$a_3$>$a_4$...>$a_n$

初一的一道绝对值题是这题的弱化版。

给定$a_1$,$a_2$...$a_n$,求一点x，使得$abs(a_1-x)$+$abs(a_2-x)$...+$abs(a_n-x)$值最小

直接求中位数即可（初一的知识——绝对值）

同理，关于2.我们令$b_i$取1到i中位数即可。

那么这道题我们就可以看做是许多个严格递减的序列，每一个序列的答案我们是可以知道的。所以我们所要做的就是合并答案即可。

怎么维护每一次合并呢？

我们想到了左偏树。

对于左偏树，我们每放入一个新节点，我们就$-=i$,使得原应严格下降的序列变成$a_{i-1}>=a_i$,再判断新加入的节点是否符合这个规则，不符合就与上一个merge。

因为我们是要求中位数，所以节点的size不应超过它的范围的二分之一再$+1$，所以我们要一直$size--$，同时删除这个节点。

最后我们求答案即可。

注：因为我们一开始就减去了i，所以在输出序列是要加上i。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct data
{
	int l,r,size,fa,val;
}s[1000001];
int val[1000001],n,k,cnt,ch[1000001][2],dis[1000001];
long long ans;
int merge(int x,int y)
{
	if(!x||!y)
	{
		return x+y;
	}
	if(val[x]<val[y])
	{
		swap(x,y);
	}
	ch[x][1]=merge(ch[x][1],y);
	if(dis[ch[x][0]]<dis[ch[x][1]])
	{
		swap(ch[x][0],ch[x][1]);
	}
	dis[x]=dis[ch[x][1]]+1;
	return x;
}
int read()
{
	char ch=getchar();
	int sum=0,f=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch<='9'&&ch>='0')
	{
		sum=sum*10+ch-'0';
		ch=getchar();
	}
	return sum*f;
}
int main()
{
	n=read();
	dis[0]=-1;
	for(int i=1;i<=n;i++)
	{
		val[i]=read();
		val[i]-=i;
	}
	for(int i=1;i<=n;i++)
	{
		s[++cnt]=(data){
			i,i,1,i,val[i] 
		};
		while(cnt!=1&&s[cnt-1].val>s[cnt].val)
		{
			cnt--;
			s[cnt].fa=merge(s[cnt].fa,s[cnt+1].fa);
			s[cnt].size+=s[cnt+1].size;
			s[cnt].r=s[cnt+1].r;
			while(s[cnt].size>(s[cnt].r-s[cnt].l+3)/2)
			{
				s[cnt].size--;
				s[cnt].fa=merge(ch[s[cnt].fa][0],ch[s[cnt].fa][1]);
			}
			s[cnt].val=val[s[cnt].fa];
		} 
	}
	int m=1;
	for(int i=1;i<=n;i++)
	{
		if(i>s[m].r)
		{
			m++;
		}
		ans+=abs(s[m].val-val[i]);
	}
	printf("%lld\n",ans);
	m=1;
	for(int i=1;i<=n;i++)
	{
		if(i>s[m].r)
		{
			m++;
		}
		printf("%d ",s[m].val+i);
	}
	return 0;
} 
```

---

