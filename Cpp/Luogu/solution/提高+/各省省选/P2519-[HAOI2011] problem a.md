# [HAOI2011] problem a

## 题目描述

一次考试共有 $n$ 个人参加，可能出现多个人成绩相同的情况。第 $i$ 个人说：“有 $a_i$ 个人成绩比我高，$b_i$ 个人成绩比我低。”

请求出最少有几个人没有说真话。

## 说明/提示

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$0 \leq a_i, b_i \leq n$。

## 样例 #1

### 输入

```
3
2 0
0 2
2 2```

### 输出

```
1```

# 题解

## 作者：xyz32768 (赞：79)

这里把第$i$个人的名次，定义为分数**严格高于**第$i$个人的人数加$1$。

把条件进行转化，可以得到「$a_i$个人分数比我高，$b_i$个人分数比我低」实际上就是「我是第$a_i+1$名， 算上我一共有$n-a_i-b_i$个人和我分数相同」。这里设$l_i=a_i+1$，$r_i=n-b_i$。意义是将分数从大到小排序之后，与第$i$个人分数相同（包括第$i$个人）的区间是$[l_i,r_i]$。

先去掉一些必假的话。

1、如果$l_i>r_i$，那么第$i$个人说的话必假。

2、如果$l_i$和$r_i$都相等的人出现了超过$r_i-l_i+1$个，那么最多只有其中的$r_i-l_i+1$个人说了真话，超出$r_i-l_i+1$部分的人说的话必假。

判断第$2$个条件，可以按照$l$为第一关键字，$r$为第二关键字从小到大排序来判断。去掉所有必假的话之后，把$l$和$r$都相等的人合并成一个区间（左右端点不变），并给区间定义一个价值，即为合并之前满足$l_i$等于该区间左端点且$r_i$等于该区间右端点的人数。

这样，求最多有多少人说真话，就变成了这一个问题：$m$个区间，每个区间为$[L_i,R_i]$，价值为$V_i$，从中选出若干个没有交集的区间，求选出区间的最大价值和。

这样就可以DP了。先把区间按$R_i$排序，设$f[i]$为到第$i$个区间的最优解。

转移就是先二分查找当$k\in[1,i-1]$时满足$R_k<L_i$的最大的$k$值，那么，转移方程就是：

$f[i]=\max(f[i-1],f[k]+V_i)$。

最后答案就是$n-f[m]$。

代码：

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
inline int read() {
    int res = 0; bool bo = 0; char c;
    while (((c = getchar()) < '0' || c > '9') && c != '-');
    if (c == '-') bo = 1; else res = c - 48;
    while ((c = getchar()) >= '0' && c <= '9')
        res = (res << 3) + (res << 1) + (c - 48);
    return bo ? ~res + 1 : res;
}
const int N = 1e5 + 5;
int n, tn, f[N];
struct cyx {
    int l, r, v;
} a[N], b[N];
bool comp1(cyx a, cyx b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}
bool comp2(cyx a, cyx b) {
    if (a.r != b.r) return a.r < b.r;
    return a.l < b.l;
}
int findx(int l, int r, int val) {
    while (l <= r) {
        int mid = l + r >> 1;
        if (a[mid].r < val) l = mid + 1;
        else r = mid - 1;
    }
    return r;
}
int main() {
    int i, x, y, tmpn; tmpn = read();
    for (i = 1; i <= tmpn; i++) a[i].l = read() + 1, a[i].r = tmpn - read();
    sort(a + 1, a + tmpn + 1, comp1);
    for (i = 1; i <= tmpn; i++) if (a[i].l <= a[i].r) b[++tn] = a[i];
    for (i = 1; i <= tn; i++) if (i == 1 || b[i].l != b[i - 1].l ||
        b[i].r != b[i - 1].r) a[++n] = b[i], a[n].v = 1;
        else if (a[n].v < a[n].r - a[n].l + 1) a[n].v++;
    sort(a + 1, a + n + 1, comp2); f[1] = a[1].v;
    for (i = 2; i <= n; i++) {
        int nxt = findx(1, i - 1, a[i].l);
        f[i] = max(f[i - 1], f[nxt] + a[i].v);
    }
    cout << tmpn - f[n] << endl;
    return 0;
}
```

---

## 作者：Mathison (赞：40)

【题面】
 
 一次考试共有n个人参加，第i个人说：“有ai个人分数比我高，bi个人分数比我低。”问最少有几个人没有说真话(可能有相同的分数)

~~题面短得以为这题是个水题~~

【分析】

通过他们所说的前面后面的人数，我们首先可以确定他的**排名区间**（区间内的人分数相等）

这样我们就很容易发现两个排除假话的关键：

1. 前后的人数之和如果大于等于总人数显然是不可能的。

1. 我们刚才分析得出，**区间内的分数相等**，假如一段区间是$[a,b]$，一段是$[b,c]$，如果两段区间同时存在，那么传达出的意思是：$a=b>$c且$a>b=c$，这显然是不成立的。所以我们发现，如果两段区间**不完全重合**显然是不符合题意的。

特别地，如果两段区间**完全重合**是可能的，因为他们可能分数相同。

但是**重合区间数**如果超过**区间长度**就一定有假话。

这个很好理解，假如区间长度为$k$，那么就是说有$k$个人分数相等，但却有多于$k$个人说自己在这段区间内，这显然有人说假话。

所以我们可以给区间附一个权值$w[i]=min($相同区间数$,$区间长度$)$

【问题等价】

 有若干个区间，每个区间都有一个权值，要求选出若干不相交区间使得权值和最大。
 
 这个问题用贪心显然是不能做了，因为可能选的很多区间的权值和还不如一个区间大。 
 
 我们考虑用DP，先模仿最长上升子序列的做法，我们令 $F[i]$ 表示选第 $i$ 个区间能得到的最大权值，那么我们有 $$F[i]=max(F[j])+Value[i]$$其中要求区间 $j$ 与区间 $i$ 不相交，可是这个复杂度是 $O(n^2)$的，我们可以用线段树优化求 $max(F[j])$的过程，复杂度变成 $O(nlogn)$。

但是我们还有更好的做法，我们这次以每个点为单位， $F[i]$ 表示到 $i$ 这个点为止能选择的最大权值，那么我们如果 $i$ 这个点是某个区间的右端点，$$F[i]=max(F[i],F[left]+value)$$，$left$ 是这个区间的左端点，$value$ 是这个区间的权值，这样除排序复杂度外可以 $O(n)$ 的解决。

【代码实现】
```
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
struct node{int l,r;} p[N];
int n,tot,num,a[N],w[N],L[N],R[N],f[N];
bool cmp(node x,node y)
{
    if(x.r!=y.r) return x.r<y.r;//关键字：右端点 
    return x.l<y.l;//次关键字：左端点 
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	int x,y;
        scanf("%d%d",&x,&y);
        if(x+y>=n) continue;//显然是假话（自己体会） 
        p[++tot].l=x+1,p[tot].r=n-y;//记录线段左右端点 
    }
    sort(p+1,p+tot+1,cmp);
    for(int i=1;i<=tot;i++)//计算区间权值
    {
        if(p[i].l!=p[i-1].l||p[i].r!=p[i-1].r) num++;
        //如果线段完全重合则num值不发生变化，权值增加
        w[num]=min(w[num]+1,p[i].r-p[i].l+1);//区间权值
        L[num]=p[i].l,R[num]=p[i].r;//记录重新选出来的线段
    }
    int j=1;
    for(int i=1;i<=n;i++)
    {
        f[i]=f[i-1];
        while(j<=num&&R[j]==i) 
		{
			f[i]=max(f[i],f[L[j]-1]+w[j]);//上文已解释
			j++;
		}
    }
    printf("%d",n-f[n]);
    return 0;
}
 ```


---

## 作者：封禁用户 (赞：22)

### ~~只要您的rp足，万物皆可线段树~~

居然没人拿线段树做……感觉就是裸的线段树优化dp……

首先题目让我们求最少的说假话的人，就是让说真话的人最多。这个“最多”就说明了我们需要构造出一种方案能让那些人可以被看作说的是真话，在这种方案中说真话的人不能互相矛盾。

那么什么可以是互相矛盾呢？我们已经知道了每个人的前面有多少分比他高的，后面有多少分比他低的，而分数可以有重复的，于是就知道了这个分在所有人的分数排好序的情况下占的是哪个区间，这个区间在这个人说真话的情况下一定是唯一确定的（考这个分的人只会占这么多这一段位置，不多不少），如果两个人的这个区间有交集但是不相同的话，显然这两个人矛盾（这个分不能同时对应两个不同的区间，交集的部分必须既考那个分，又得考这个分，这是不可能的），如果相同的话那就不矛盾——但是，可能会有对应这个区间的人的个数超出了这个区间的限制，那么我们干脆就把超限的人当成说的是假话，反正他们都是完全相同的。

可能有人就会问了，就算构造出了一种不会产生冲突的方案，您能保证前面一定有$a_i$个比i分高，后面$b_i$个比他分低的吗？其实这个比较好想，我们选出了说真话的人，那些说假话的人就想上那待着就上哪待着，因此不够的地方直接让他们填补就行了。

于是我们就能搞出每个区间里会有几个人跟他完全对应，那么我们就把题目转化成了——给定m个区间，每个区间有一个权值，要选出一些两两不相交的区间使得权值和最大。

那么我们就设$dp[i]$为在i区间对应的所有人说的是真话的条件下，最多说真话的人数。考虑他的转移，肯定要从一个和他不相交的区间转移过来，那么我们就把区间按照右端点从小到大排序，然后把区间的“重心”放到右端点上，这样右端点在i的左端点之前的区间就一定和i不相交，虽然这不一定是所有不和i相交的区间（只能说是在i之前的），但是别忘了这是有顺序的dp，$dp[i]$也会转移到后面和他不相交的状态上去。那么我们有状态转移方程（直接把i作为右端点，$L_i$为左端点，$v_i$为权值）：

$dp[i]=max_{j=0}^{L_i-1}(dp[j])+v_i$

这个东西拿线段树维护一下就能$O(nlogn)$ $A$掉此题啦~

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
inline int get(){
	int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
	n=c-'0';while((c=getchar())||1){
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
}
typedef struct _n{
	int left;int right;int data;
}node;node memchi[1000001];int gn=1;
inline void up(int tree){
	int ls=memchi[tree].left,rs=memchi[tree].right;memchi[tree].data=max(memchi[ls].data,memchi[rs].data);
}
int build(int l,int r){
	int tree=gn;gn++;memchi[tree].data=-1234567890;
	if(l!=r){
		int mid=(l+r)>>1;memchi[tree].left=build(l,mid);
		memchi[tree].right=build(mid+1,r);
	}return(tree);
}
int getmax(int rl,int rr,int l,int r,int tree){
	if(rl==l&&rr==r)return(memchi[tree].data);int mid=(l+r)>>1;
	if(rl>mid)return(getmax(rl,rr,mid+1,r,memchi[tree].right));
	if(rr<=mid)return(getmax(rl,rr,l,mid,memchi[tree].left));
	return(max(getmax(rl,mid,l,mid,memchi[tree].left),getmax(mid+1,rr,mid+1,r,memchi[tree].right)));
}
int pt,num;
void setpt(int l,int r,int tree){
	if(l==r){
		memchi[tree].data=max(memchi[tree].data,num);return;
	}int mid=(l+r)>>1;if(pt<=mid)setpt(l,mid,memchi[tree].left);
	else setpt(mid+1,r,memchi[tree].right);up(tree);
}
typedef struct _qj{
	int l;int r;
	friend bool operator <(const _qj &a,const _qj &b){
		if(a.r==b.r)return(a.l<b.l);return(a.r<b.r);
	}
}qujian;qujian qujians[1000001];map<qujian,int> mp;
int main(){
	int n=get();int ptr=1;for(register int i=1;i<=n;i++){
		int a=get(),b=get();if(a+b>=n)continue;
		int l=b+1,r=n-a;
		qujians[ptr].l=l;qujians[ptr].r=r;
		if(!mp.count(qujians[ptr])){
			mp[qujians[ptr]]=1;ptr++;
		}else{
			mp[qujians[ptr]]++;
		}
	}sort(qujians+1,qujians+ptr);
	int maxn=0;int root=build(0,n);pt=0;num=0;setpt(0,n,root);
	for(register int i=1;i<ptr;i++){
		int val=min(qujians[i].r-qujians[i].l+1,mp[qujians[i]]);
		int dp=getmax(0,qujians[i].l-1,0,n,root);
		maxn=max(maxn,dp+val);pt=qujians[i].r;num=dp+val;setpt(0,n,root);
	}cout<<n-maxn<<endl;
	return(0);
}
```

---

## 作者：Jμdge (赞：17)

优秀的解法，（亮点主要是代码短）



思路比较常规，就是处理出一段成绩相同的区间：
$$L=a[i]+1,R=n-b[i]$$

然后我们判断 L 是否 小于等于 R ，是的话我们就用 $map$ 更新当前 $L -- R$  区间的出现次数（就是  $mp[make\_pair(l,r)]++$  ），如果第一次出现就把 L 塞入以 R 结尾的 $vector$。

然后我们再直接搞 dp 转移就好了，转移的时候先令 $f[i]=f[i-1]$ ，然后遍历$vector$，找到以 当前区间 L 前面的位置结尾的 f 更新答案。

注意如果某段区间的出现次数大于区间长度我们要取 $min$

```cpp
//by Judge
#include<map>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define P make_pair
using namespace std;
const int M=1e5+11;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,f[M]; vector<int> vec[M]; map<pair<int,int>,int> mp;
inline void cmax(int& a,int b){ if(a<b) a=b; }
int main(){ n=read();
	for(int i=1,a,b;i<=n;++i){
		a=read()+1,b=n-read();
		if(a>b) continue;
		if(++mp[P(a,b)]==1)
			vec[b].push_back(a);
	} for(int i=1,L,R;i<=n;++i){ f[i]=f[i-1];
		for(int j=0;j<vec[i].size();++j) L=vec[i][j],
			cmax(f[i],f[L-1]+min(mp[P(L,i)],i-L+1));
	} return printf("%d\n",n-f[n]),0;
}
```

---

## 作者：安好 (赞：6)

/\*
对于每一个描述，我们可以根据他所描述的比他高的和比他矮的人数来构造一条线段，左端点l即为y+1，右端点r为n-x。

当我们转化成线段以后，这一段线段就表示着分数相同的人数，那么显然，只有与这个线段完全重合的线段是符合要求的，

对于有交集的线段一定是有一个说谎的，但是对于完全重合的线段，还是有可能出现说谎的情况

所以我们可以写个前向星add(b[i].r,b[i].l-1,b[i].w)

l为该区间的左端点，r为该区间的右端点，w为权值

建这个边的原因是f[b[i].r]=max(f[b[i].r],f[b[j].l-1]+e[i].w)

\*/





    
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100007
using namespace std;
int n,tot,num,cnt;
struct node{int l,r,w;}a[N],b[N];
struct node2{int u,v,net,w;}e[N];
int f[N],head[N];
int cmp(node a,node b)
{
    if(a.r==b.r)return a.l<b.l;
    return a.r<b.r;
}
int cmp2(node a,node b)
{
    if(a.r==b.r)return a.w<b.w;
    return a.r<b.r;
}
void add(int u,int v,int w)
{
    e[++cnt].v=v;e[cnt].w=w;e[cnt].net=head[u];head[u]=cnt;
}
int main()
{
    scanf("%d",&n);int x,y,ans=0;
    memset(head,-1,sizeof(head)),cnt=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        if(x+y>=n){ans++;continue;}
        a[++tot].l=x+1;
        a[tot].r=n-y;
    }
    sort(a+1,a+tot+1,cmp);
    for(int i=1;i<=tot;i++)
    {
        if(a[i].l==a[i-1].l&&a[i].r==a[i-1].r)
        {
            if(b[num].w<b[num].r-b[num].l+1)
            b[num].w++;
        }
        else b[++num].l=a[i].l,b[num].r=a[i].r,b[num].w=1;
    }
    sort(b+1,b+num+1,cmp2);
    for(int i=1;i<=num;i++) add(b[i].r,b[i].l-1,b[i].w);
    int r=0;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        f[i]=f[i-1];
        for(int j=head[i];j!=-1;j=e[j].net)
        {
            int v=e[j].v;
            f[i]=max(f[i],f[v]+e[j].w);
        }
    }
    printf("%d\n",n-f[n]);
}
```

---

## 作者：ljk123 (赞：5)

# problem a题解

### 分析：

根据成绩比他高的人数$a_{i}$和比他低的人数$b_{i}$可以推出他的排名区间$[l_{i},r_{i}],$

其中$l_{i}=b_{i}+1,r_{i}=n-a_{i}$

且$[l_{i},r_{i}]$的人成绩一定相等，并与除此区间外的人的成绩都不相同


显然，$l_{i}>r_{i}$的人一定在说谎，

并且与$[l_{i},r_{i}]$有交集或者被其包含的区间与其矛盾

为什么？

若另一区间为$[l_{j},r_{j}]$,设排序后的成绩数组为$c$

则意味着

$c[l_{j}]!=c[l_{j}-1],c[r_{j}]!=c[r_{j}+1]$,

1.显然与和$[l_{i},r_{i}]$有交集矛盾;

2.因为被包含,

$c[l_{i}]=c[l_{i}+1]=c[l_{i}+2]=……=c[l_{j}]=c[l_{j}+1]=c[l_{j}+2]=……=c[r_{j}]=……=c[r_{i}]$

也矛盾。

只有$l_{i}=l_{j},r_{i}=r_{j}$时才可合并(数量不能超过区间长度$r_{i}-l_{i}+1$)

### 题意：
转换一下题意：

求最少说谎的人数，

等于$n-$最多合法的区间数目

区间相交和区间包含不合法，

即是求不相交的最大区间数目(相同的也要算)

### 操作：

按$r_{i}$排序，每次取$<l_{i}$的区间最大值，

自己的值为最大值+相同的区间数目,

也存在$r_{i}$处，

我用的是树状数组维护最大值，

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100006;
int n,num=0,tot=0,t1,t2,f[N],w[N];
struct xd{int l,r;}a[N],b[N];
inline int read(){
   int T=0,F=1; char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') F=-1; ch=getchar();}
   while(ch>='0'&&ch<='9') T=(T<<3)+(T<<1)+(ch-48),ch=getchar();
   return F*T;
}
bool cmp(xd u,xd v){
    if(u.r<v.r) return 1;
    if(u.r>v.r) return 0;
    return u.l<v.l;
}//读入优化
inline int lowbit(int x){return x&(-x);}
void add(int u,int v){for(int i=u;i<=n;i+=lowbit(i)) f[i]=max(f[i],v);}
int getmax(int u){
    int maxans=0;
    for(int i=u;i;i-=lowbit(i)) maxans=max(maxans,f[i]);
    return maxans;
}//取最大值
int main(){
    n=read();
    for(int i=1;i<=n;++i){
        t1=read(),t2=read(),t1=n-t1,t2=t2+1;
        if(t1<t2) continue;
        //除去l>r的区间
        a[++num].l=t2,a[num].r=t1;
    }
    sort(a+1,a+num+1,cmp);
    for(int i=1;i<=num;++i){
        if(a[i].l==a[i-1].l&&a[i].r==a[i-1].r) w[tot]=min(b[tot].r-b[tot].l+1,w[tot]+1);
        else w[++tot]=1,b[tot]=a[i];
    }
    //除去完全相同的区间，权值累加
    for(int i=1;i<=tot;++i) t1=getmax(b[i].l-1)+w[i],add(b[i].r,t1);
    //树状数组动态维护
    printf("%d\n",n-getmax(n));
    return 0;
} 
```

---

## 作者：cdcq (赞：4)

随便点的一道DP题，本来这题以前无数次想不出来，题解好像也看不懂，想的时候都打算放弃了

但是想着一定要死磕思维能力，最后居然还真的自己做出来了

果真是以前放弃得太轻易hhh

首先要确定一下题意，“有ai个人”我感觉也可以理解为>=ai个人

但是其实后来想一下，如果这样说得话就没必要强调可能有相同分数了

因为如果是>=ai的话，两个同分的和两个相邻分数的对于合法性其实都一样

所以认为题意为恰好有ai个人（当然考场上还是大力问监考）

那么研究一下这个约束条件的限制，可以发现实际上是ai和bi中间摞了n-ai-bi个人

那么用xi=ai表示这一摞人前面有多少人，yi=n-ai-bi表示摞了多少人

可以发现对于xi相等而yi不等的两个人一定无法满足

而xi和yi都相等的人一定一起满足（除非xi和yi相等的人数超过了yi，那么多出者不满足）

所以可以把xi和yi相等的人合并，令zi表示满足这些人的要去需要再拿多少个假人充数

（假人就是条件不被满足的人）

然后灵稽一动，不妨就按xi递增排序，然后考虑枚举到的每个人是否满足要求

如果这样做的话状态可以设为f[i]表示把前i个人安排上需要的最少说谎人数

递推求解

这样好像不太对，有后效性

即假设现在要那一个假人充数，那这个假人是前面考虑过的，还是后面没考虑的，还是把已经满足的撤了

你不知道，会影响决策

我的思路转了一圈之后，找不到什么有可能的做法，再回来研究这样做，发现各种细节美好得不正常

于是决定随便写写试试

然后就ac了

我尻![](https://img2018.cnblogs.com/i-beta/1746505/201912/1746505-20191211180621056-567986158.png)这都行

现在再来考虑算法得正确性，可以发现刚才得顾虑是多余的

因为所有没满足要求的假人都是一样的，而易证假人是充足的，因为如果假人不够则与总人数冲突

所以我们完全不用考虑假人从哪来，只需要直到前边已经有i个人被安排了就行

最后整理一下思路

首先令xi=ai，yi=n-ai-bi，zi=需要补的假人

然后按xi递增排序，走递推

f[i]初值为i，包括f[0]=0

递推公式为f[a[i].x+a[i].y]=min(f[a[i].x+a[i].y],f[a[i].x]+a[i].z)

需要注意a[i].x和a[i-1].x中间可能隔了几个数，而这些状态实际受f[a[i-1].x]的影响

因为中间可以直接丢一个假人过去把之前的更优决策继承过来

也就是说f[a[i-1].x+j]应该等于f[a[i-1].x]+j，f[a[i].x]应该等于min(f[a[i].x],f[a[i-1].x]+a[i].x-a[i-1].x)

我的写法是用一个temp跟着a[i].x走，每次让temp++就令f[temp]=min(f[temp],f[temp-1]+1)

-----------------------------
代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct nds{int x,y,z;}a[110000],b[110000];  int m=0;
int n;
int f[110000];
bool cmp(nds x,nds y){  return x.x==y.x ? x.y<y.y : x.x<y.x;}
int main(){
	freopen("ddd.in","r",stdin);
	cin>>n;
	int l,r;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&l,&r);
		a[i].x=l,a[i].y=n-l-r;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)if(a[i].y>0){
		if(a[i].x!=b[m].x || a[i].y!=b[m].y){
			b[++m]=a[i];
			b[m].z=a[i].y-1;
		}
		else  b[m].z=(b[m].z ? b[m].z-1 : 0);
	}
	for(int i=1;i<=n;++i)  f[i]=i;
	f[0]=0;
	int tmp=0;
	for(int i=1;i<=m;++i){
		while(tmp<b[i].x){
			++tmp;
			f[tmp]=min(f[tmp],f[tmp-1]+1);
		}
		f[b[i].x+b[i].y]=min(f[b[i].x+b[i].y],f[b[i].x]+b[i].z);
	}
	while(tmp<n){
		++tmp;
		f[tmp]=min(f[tmp],f[tmp-1]+1);
	}
	printf("%d\n",f[n]);
	return 0;
}


```

---

## 作者：qwaszx (赞：4)

挺妙的一道题.

设$l_i=a_i+1,r_i=n-b_i$，那么一个限制等价于第$l_i$到$r_i$个人的分数都相等.

然后补集转化成说真话的人最多.对某个人的$l,r$，如果$l>r$那么他一定是假的；如果有多于$r-l+1$个人的$l,r$都一样那么这些人中最多只能有$r-l+1$个说真话.

于是问题转化成有$n$个区间，一个区间$[l,r]$的权值是$\min(r-l+1,\text{区间[l,r]出现的次数}$.要求选出尽量多的不相交区间使得权值和最大.

对这个问题我们已经有成熟的解决办法.按$r$排序，然后设$f[i]$表示前$i$个人选若干个的最大权值和，有$f[i]=\max\limits_{0\leq j<i,r_j<l_i}\{f[j]\}+w[i]\}$.可以二分一个位置然后转移也可以直接对坐标做一个前缀$\max$.写线段树的不知道是出于什么心理.....

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e5;
int n,f[N];
struct Node{int x,y,w;}a[N];
int cmp(const Node &a,const Node &b){return a.y!=b.y?a.y<b.y:a.x<b.x;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y),a[i].x++,a[i].y=n-a[i].y;
	sort(a+1,a+n+1,cmp);
	int nn=0;
	for(int i=1,x=0,y=0;i<=n;i++)
	{
		if(a[i].x==x&&a[i].y==y)a[nn].w++;
		else if(a[i].x<=a[i].y)a[++nn]=(Node){a[i].x,a[i].y,1},x=a[i].x,y=a[i].y;
	}
	for(int i=1;i<=nn;i++)a[i].w=min(a[i].w,a[i].y-a[i].x+1);
	int j=1;
	for(int i=1;i<=nn;i++)
	{
		while(j<=a[i].y)f[j]=max(f[j],f[j-1]),++j;//前缀max
		f[a[i].y]=max(f[a[i].y],f[a[i].x-1]+a[i].w);
	}
	cout<<n-f[a[nn].y]<<endl;
}
```


---

## 作者：大菜鸡fks (赞：1)

把自己的分数变成线段，去重+排序，于是就化为了求最大权的不交子段。二分查找转移点。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1; char c=getchar();
	while (c<'0'||c>'9') {
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
void write(int x){
	if (x<0){
		putchar('-');
		x=-x;
	}
	if (x>9) write(x/10);
	putchar(x%10+'0');
}
inline void writeln(int x){
	write(x); puts("");
} 
const int N=2e5+5;
struct node{
	int l,r,v;
}a[N];
int n,cnt,dp[N],res;
inline bool cmp(node A,node B){
	return A.l<B.l||(A.l==B.l&&A.r<B.r);
}
inline void init(){
	n=read(); res=n;
	for (int i=1;i<=n;i++){
		int L=read()+1,R=n-read();
		if (L<=R) a[++cnt]=(node){L,R,0};
	}
}
inline int find(int L,int R,int x){
	while (L<R){
		int mid=(L+R+1)>>1;
		if (a[mid].r<x) L=mid;
			else R=mid-1;
	}
	return L;
}
inline void solve(){
	n=cnt;
	sort(a+1,a+1+n,cmp); cnt=0;
	for (int i=1;i<=n;i++){
		if (a[i].l!=a[cnt].l||a[i].r!=a[cnt].r){
			a[++cnt]=a[i];
		}
		a[cnt].v++;
	}
	n=cnt;
	for (int i=1;i<=n;i++){
		a[i].v=min(a[i].v,a[i].r-a[i].l+1);
	}
	dp[1]=a[1].v;
	for (int i=2;i<=n;i++){
		int nxt=find(1,i-1,a[i].l);
		dp[i]=max(dp[i-1],dp[nxt]+a[i].v);
	}
	writeln(res-dp[n]);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：ww3113306 (赞：1)

，，本来想用贪心做，结果发现去重后权值不再都是1了，所以转而写DP
可能略长，无STL（sort不算），无二分
速度一般般吧三百ms左右
总体思路差不多，
将最少说谎人数转化为最多说真话的人数

	#include<bits/stdc++.h//谁能告诉我这里为什么把右边括起来就会消失？？？
	using namespace std;
	#define AC 101000
	#define R register int
	#define INF 999999999
	struct abc{
		int l,r;
	}p[AC];
	int w[AC],n,ans,tot,now,cnt,f[AC];
	int Next[AC],date[AC],Head[AC];
	inline int read()//读入优化
	{
		int x=0;char c;
		while(isspace(c=getchar()));
		while(c>='0' && c<='9')x=x*10+c-'0',c=getchar();
		return x;
	}


	bool cmp(abc a,abc b)//重载

	{
  
	  if(a.l!=b.l)return a.l<b.l;
  
  	if(a.r!=b.r)return a.r<b.r;

	}

	inline int Max(int a,int b)//求最大值
	{
		int c=(a-b)>>31;
		return (a &~ c) | (b & c);
	}

	inline int Min(int a,int b)//求最小值
	{
		int c=(b-a)>>31;
		return (a &~ c) | (b & c);
	}

	inline void add(int f,int w)//利用链式前向星（大概是不会vector）
	{
		date[++tot]=w;
		Next[tot]=Head[f];
		Head[f]=tot;
	}

	void pre()
	{
		R a,b,have=0;
		n=read();
		for(R i=1;i<=n;i++)
		{
			a=read(),b=read();
			if(a+b<n)	p[++cnt].l=a+1,p[cnt].r=n-b;//这里先取闭区间，然后端点不可重合
		}//只有合法才参与运算
		sort(p+1,p+cnt+1,cmp);
		for(R i=1;i<=cnt;i++)//上面取闭区间就是为了方便判重
		{
			if(p[i].l==INF)continue;
			if(p[i].l==p[i+1].l && p[i].r==p[i+1].r)//如果与前面的相同
		{
			//p[i].l=INF;
			have++;//记录有几个重复的了（不包括自己)
		}
		else//如果已经不重复了，那么更新w[i]
		{
			w[i]=Min(have+1,p[i].r-p[i].l+1);//在区间和重复里面取min，因为超出区间的肯定是假话
			add(p[i].r,i);//接到以右边界为终点的集合里面去
			have=0;//error!!! 要重置have
		}
	}
}

	void work()
	{
		R now;
		for(R i=1;i<=n;i++)//虽然去掉了一些，但是右边界还是有那么多
		{
			f[i]=f[i-1];//这里i的意义是右边界
			for(R j=Head[i]; j ;j=Next[j])
			{
				now=date[j];//error!!!date才是对应下标
				f[i]=Max(f[i],w[now]+f[p[now].l-1]);//和已经处理好的权值取max,取了这条边后就只能取它左边界之前的了
			}
		}
		printf("%d\n",n-f[n]);
	}

	int main()
	{
		freopen("in.in","r",stdin);
		pre();
		work();
		fclose(stdin);
		return 0;
	}

---

## 作者：替罪羊树 (赞：1)

### Comprehension:
有个不严格单调上升的n元序列，给定n个区间($l_i$,$r_i$),表示这区间的位置是。但是数字是有限并且非严格单调的，因此某些区间和前面的区间矛盾，求这些矛盾区间的最小个数。

### Analysis：
很容易发现这道题给定的相当于是两个开区间($0$,$l_i$)和($r_i$,$n$)。由于前后都是不等关系，这个东西很让人头疼。我们给他改一下，变成一个闭区间[$l_i$,$r_i$].相当于是一条线段，这条线段中所有的数都应该是相等的。

再来考虑，如果我们直接求互斥的个数，似乎比较难以维护，因为这个取舍不太好做。想想我们学过一个模型，就是线段覆盖问题，这个东西就可以用动态规划去搞一搞。

所以，我们把这个问题转化成为：n个等值区间，求最多的不矛盾的区间个数。

### Consideration:
定义变量如下：
```cpp
int dp[maxn];//dp[i]表示从第1名到第i名，排在这些名次的人最多有多少，也就是这范围内最多有多少个人说了真话 
int n;
map<pair<int,int>,int> qwq;//用来统计区间出现次数 
vector<int> clm[maxn];//用来记录每个区间。 
```
对于整个过程，我们大致做一个宏观的概述：

1. 将每个约束条件转换为闭区间，闭区间表示并列名次
2. 对于每个点$i$，有多少个点落在这个点上，用动态数组clm（即claim）来维护；对于每个区间[$l_i$,$r_i$],统计出现的次数，用一个映射qwq来维护
3. 升序扫描每个点（也就是排名），首先令$dp[i]$继承$dp[i-1]$的答案，因为我们用dp数组统计的是人数，从定义上来看就应该是不下降的，因此我们继承。
4. (1)对$dp[i]$转移。转移的对象是以当前节点i结尾的所有区间。但是如果某区间出现次数大于区间长度那肯定有问题，取min。
(2)令$s=clm[i][j]$表示区间左端，这区间是$[s,i]$.从$s-1$号点转移，$[s,i]$的出现次数(qwq统计)全部算作真话，累加.(3)是否需要考虑其他区间呢？不需要的。因为那些更小或者更大的区间，如果也以$s$为起点或者以$i$为终点，一定会被另行转移。只考虑当前的就好了。 

### Explanation:
所以我们可以写出状态转移方程如下：
```cpp
int limit=clm[i].size();
if(limit==0) continue;
for(register int j=0;j<limit;++j)
   	dp[i]=max(dp[clm[i][j]-1]+min(i-clm[i][j]+1,qwq[make_pair(clm[i][j],i)]),dp[i]);
```
对这个方程进行解释：
$min(i-clm[i][j]+1,qwq[make$_$pair(clm[i][j],i)])$前者是当前区间的长度，后者是这个区间被claim了多少次。为了防止上面提到的小问题，取最小值，多出来的一定没说真话。

$max(dp[clm[i][j]-1]+$上式$,dp[i])$，前者表示当前区间前段点再前面的一个节点，这是用来作转移的。

最后得出的$dp[n]$表示从rank1到rankn中最多的说真话的人数。那么我们所需要的答案就是$n-dp[n]$。

### Completed Code:
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define maxn 200200
using namespace std;
inline int read()
{
    int n=0,k=1;
    char c=getchar();
    while(c>'9'||c<'0') {if(c=='-') k=-1; c=getchar();}
    while(c<='9'&&c>='0') n=(n<<1)+(n<<3)+(c^48),c=getchar();
    return n*k;
}
int dp[maxn];//dp[i]表示从第1名到第i名，排在这些名次的人最多有多少，也就是这范围内最多有多少个人说了真话 
int n,m;
map<pair<int,int>,int> qwq;//用来统计区间出现次数 
vector<int> clm[maxn];//用来记录每个区间。 
int main()
{
    n=read();
    for(register int i=1;i<=n;++i)
    {
        int l=read()+1,r=n-read();//将(0,l)和(r,n)开区间 转化为维护并列名次的 [l,r]闭区间，即可用线段覆盖模型 
        if(l>r) continue;
        ++qwq[make_pair(l,r)];//统计次数 
        if(qwq[make_pair(l,r)]==1) clm[r].push_back(l);
    }
    memset(dp,0,sizeof(dp));
    for(register int i=1;i<=n;++i)
    {
        dp[i]=dp[i-1];//继承答案,显然这答案具有单调性 
        int limit=clm[i].size();
        if(limit==0) continue;
        for(register int j=0;j<limit;++j)
            dp[i]=max(dp[clm[i][j]-1]+min(i-clm[i][j]+1,qwq[make_pair(clm[i][j],i)]),dp[i]);
    }
    printf("%d\n",n-dp[n]);//要求最少说假话的人，那么总人数减去最多说真话的人即可 
    return 0;
}
```

### Moreover:
关于时间复杂度：dp中一重外循环$O(n)$,内部虽然有j但是每个区间只被访问一次，也是$O(n)$,而内部调用$qwq$的时间复杂度是$O(log_2n)$，因此总的时间复杂度是$O(nlog_2n)$。实测最大数据75ms（我常数巨大求轻d）

---

## 作者：木xx木大 (赞：0)

[P2519 [HAOI2011]problem a ](https://www.luogu.com.cn/problem/P2519)

* 设 $[l_i,r_i] $表示第 $i$ 个人的排名在 $l_i$ 到 $r_i$ 之间，即 $[l_i,r_i]$ 的人分数排名一样。显然 $l_i=b_i+1,r_i=n-a_i$。

* 先去掉一些必假的话。
  * 如果 $l_i>r_i$，那么第 $i$ 个人说的话必假。
  * 如果 $l_i$ 和 $r_i$ 都相等的人出现了超过 $r_i-l_i+1$ 个，那么最多只有其中的 $r_i-l_i+1$ 个人说了真话，超出 $r_i-l_i+1$ 部分的人说的话必假。
  * 如果有两个区间相交却不相同，这两个区间的人必有一个说假话。这与 $[l_i,r_i] $的人分数排名一样相违背。特别地，如果两段区间**完全重合**是可能的，因为他们可能分数相同。

* 去掉所有必假的话之后，把 $l$ 和 $r$ 都相等的人合并成一个区间（左右端点不变），并给区间定义一个价值，价值即为合并之前满足 $l_i$ 等于该区间左端点且 $r_i$ 等于该区间右端点的人数。

* 于是我们可以把问题转化为求最多有多少人说真话，就变成了这一个问题：$m$ 个区间，每个区间为 $[l_i,r_i]$，价值为 $v_i$，从中选出若干个没有交集的区间，求选出区间的最大价值和。

* 我们可以进行dp。先把区间按 $r_i$ 排序，设 $f_i$ 为到第 $i$ 个区间的最优解。边界 $f_1=v_1$。

* 转移：先二分查找当 $k\in [1,i−1]$ 时满足 $r_k<l_i$ 的最大的 $k$ 值，转移方程为：$f_i=\max(f_{i-1},f_k+v_i)$。最后答案就是 $n-f_m$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct ren{
	int l,r,v;
}a[100005],b[100005];
int f[100005];
int n,cnt;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')w=-w;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
 }
bool cmp1(ren x,ren y)
{
	return x.l==y.l? x.r<y.r:x.l<y.l;
 } 
bool cmp2(ren x,ren y)
{
	return x.r==y.r? x.l<y.l:x.r<y.r;
}
int find(int i)
{
	int l=1,r=i-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(b[mid].r<b[i].l)l=mid+1;
		else r=mid-1;
	}
	return r;
}
int main()
{

	n=read();
	for(int i=1;i<=n;i++)
	{
		int r=n-read(),l=read()+1;
		if(l<=r)
		{
			a[++cnt].r=r;
			a[cnt].l=l;
		}	
	}
	int num=0;
	sort(a+1,a+cnt+1,cmp1);
	for(int i=1;i<=cnt;i++)
	{
		if(i==1||a[i].l!=a[i-1].l||a[i].r!=a[i-1].r)
		{
			b[++num]=a[i];
			b[num].v=1;
		 } 
		else if(b[num].v<b[num].r-b[num].l+1)b[num].v++;
	}
	sort(b+1,b+num+1,cmp2);
	f[1]=b[1].v;
	for(int i=2;i<=num;i++)
	{
		int k=find(i);
		f[i]=max(f[i-1],f[k]+b[i].v);
	}
	int ans=n-f[num];
	printf("%d",ans);
	return 0;
}
```

---

## 作者：假装思考 (赞：0)

【题意】
```
	       一次考试共有n个人参加，第i个人说：“有ai个人分数比我高，bi个人分数比我低。”问最少有几个人没有说真话(可能有相同的分数)
```
【分析】
```
	       先进行补集转化，转化成求最多多少人说真话。每个人说的话的意思其实就是排完序后第bi+1个人到第n-ai个人分数相同，我们把它看做一条线段，那么问题就变成了求最多的不相交或者完全重合的线段的条数，直接DP，但是注意一条线段重合的次数不能大于它的长度。
	       对了。。数据毒瘤。。还要把ai+bi>=n的情况排除掉。。。
	       明明可以O(N)做，为什么网上清一色的O(NlogN)。。。
```
【代码】
```
	#include<bits/stdc++.h>
	#define For(i,a,b) for(register int i=(a);i<=(b);++i)
	#define Rof(i,a,b) for(register int i=(a);i>=(b);--i)
	#define LL long long
	#define MaxN 100111
	using namespace std;
	int N,a,b,Tot,Now,Opt[MaxN];
	struct Xjh{int X,Y,Cnt;}A[MaxN],B[MaxN];
	bool Cmp(Xjh a,Xjh b){return a.Y!=b.Y?a.Y<b.Y:a.X<b.X;}
	int main(){
		scanf("%d",&N);For(i,1,N)scanf("%d%d",&a,&b),A[i].X=b+1,A[i].Y=N-a;
		sort(A+1,A+1+N,Cmp);
		For(i,1,N){
			if(A[i].X>A[i].Y)continue;
			if(A[i].X!=A[i-1].X||A[i].Y!=A[i-1].Y)B[++Tot].X=A[i].X,B[Tot].Y=A[i].Y,B[Tot].Cnt=1;
			else B[Tot].Cnt=min(B[Tot].Cnt+1,B[Tot].Y-B[Tot].X+1);
		}
		For(i,1,N){
			Opt[i]=Opt[i-1];
			while(B[Now].Y<i&&Now<=Tot)++Now;
			while(B[Now].Y==i&&Now<=Tot)Opt[i]=max(Opt[i],Opt[B[Now].X-1]+B[Now].Cnt),++Now;
		}
		printf("%d\n",N-Opt[N]);
		return 0;
	}
```

---

## 作者：Hope2075 (赞：0)

既然有用线段树的，那我就用树状数组~~水一波~~

~~并捎带学习了一下树状数组~~

考虑求出最多有多少人说真话

首先转化问题：如果一个人说的是真话，那么这个人对应区间分数相同，且两端分数都与这个区间内部不同

把相同区间合并，根据人数给一个权值，如果过大就把它变小

问题变为：给定若干有权值的区间，取出一些两两不相交的区间，使权值和最大

可以列出dp方程（这里是用一个dp值更新后面的dp值）

$dp[p_{i}.r]=max(dp[p_{i}.r],max\{1..(p_{i}.l-1)\}+v{_i}])$

意思就是：如果选一个区间，从能保证与它不相交的dp值中取出最大的，加上权值，更新右端点

但是，树状数组似乎不能维护这个最大值

不过考虑一下：

1.单点修改，前缀询问

2.数值只会变大

这样，在树状数组上更新时，如果某个节点需要被更新

1.该节点对应最大值不是被修改的点
    
这样如果被修改的点数足够大，就可以更新，否则不会更新

这两种情况结果都是正确的

2.该节点对应最大值是被修改的点

由于数值只会变大，所以该节点数值也会变大

这样也是正确的

所以，可以用树状数组优化dp

时间复杂度$O(n\log n)$

而且常数应该比线段树小

不开O2用时387ms

如果排序换成基数排序，可能会更快

最后是代码：

```cpp
#include<iostream>
#include<algorithm>
#define lowbit(x) (x&(-x))
using namespace std;
const int N=100007;
int dp[N];
struct range{
	int l,r;
};
bool operator<(range a,range b){
	if(a.l>a.r)return false;
	if(b.l>b.r)return true;
	if(a.l==b.l)return a.r<b.r;
	return a.l<b.l;
}
bool operator==(range a,range b){
	return a.l==b.l&&a.r==b.r;
}
range list[N];
range nlist[N];
int val[N];
int arr[131076];
int query(int n){
	int ans=0;
	for(;n;n=n-lowbit(n)){
		ans=max(ans,arr[n]);
	}
	return ans;
}
int n;
void updata(int nn){
	if(nn==0)return;//如果去掉这里，会T掉一个点，原因不明
	for(int x=nn;x<=n;x=x+lowbit(x)){
		arr[x]=max(arr[x],dp[nn]);
	}
}

int a,b;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		list[i].l=b+1;
		list[i].r=n-a;
	}
	sort(list+1,list+n+1);
	int t=1;
	while(t<=n){
		if(list[t].l<=list[t].r)break;
		t++;
	}
	if(t==n+1){
		cout<<n<<endl;
		return 0;
	}
	int r=2;
	nlist[1]=list[t];
	val[1]=1;
	for(t++;t<=n;t++){
		if(list[t]==nlist[r-1]){
			val[r-1]++;
		}else{
			nlist[r]=list[t];
			val[r]=1;
			r++;
		}
	}
	for(int i=1;i<r;i++){
		if(val[i]>nlist[i].r-nlist[i].l+1)val[i]=nlist[i].r-nlist[i].l+1;
	}
	for(int i=1;i<r;i++){
		dp[nlist[i].r]=max(dp[nlist[i].r],query(nlist[i].l-1)+val[i]);
		updata(nlist[i].r);
	}
	cout<<n-query(n)<<endl;
}
```

---

## 作者：joe19025 (赞：0)

## Solution

### 转化

一眼看没有想法，后来yy出了很多奇怪解法，后来被我否掉。

问题的关键在于如何转化这个问题。

有a个人比他低和有b个人比他高等同于和他相同的排在第a+1到n-b位。

所以我们可以把每个输入重新理解一下，升序排序后，第a+1到n-b位相同，区间[l,r]相同。

### 注意

有两个需要是矛盾的需要特殊处理。对于每个区间

1. l>r,矛盾
2. 同样的区间出现次数超过区间长度，超出的肯定是矛盾的

### 实现

1. 读入，转化为区间
2. 排序，合并重复的。
3. 判断，把不合法的去掉
4. DP

### DP

DP方法很简单，我们计算最多能满足的人的个数，和n做差，就是答案。

设f[i]为前i位中，最多能满足多少人。

区间以右端点排序后，

f[i]=max(f[左端点-1]+同一区间出现次数，f[i-1])

O(n)即可求解

### 总复杂度为O(n)

## Code

```c++
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#define MAXN 100005
using namespace std;

struct line{
    int l,r;
    bool operator<(const line a)const
    {
        if(r==a.r) return l<a.l;
        return r<a.r;
    }
    bool operator==(const line a)const
    {
        return a.l==l && a.r==r;
    }
}a[MAXN],b[MAXN];
int c[MAXN],f[MAXN];
int n,cnt=0;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i].l=y+1;
        a[i].r=n-x;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        if(a[i].l>a[i].r)continue;
        if(!(a[i]==a[i-1]))
            b[++cnt]=a[i];
        c[cnt]++;
    }
    for(int i=1;i<=cnt;i++)
    {
        if(c[i]>b[i].r-b[i].l+1)
            c[i]=b[i].r-b[i].l+1;
    }
    int l=0;
    for(int i=1;i<=n;i++)
    {
        f[i]=f[i-1];
        while(l<cnt && b[l+1].r==i)
        {
            l++;
            f[i]=max(f[i],f[b[l].l-1]+c[l]);
        }
    }
    printf("%d",n-f[n]);
    return 0;
}
```



---

## 作者：yxchar (赞：0)

在有$n$个人参加考试时，若有人声称$a_i$个人考得比自己高，$b_i$个人考得比自己低，其实际上是在说自己考试的排名在区间$[b_{i}+1,n-a_{i}]$上，且这个区间中的人考试分数均相等，区间左边的人考试分数严格小于该区间中人的考试分数，右边则严格大于。若两个人的说法产生矛盾，当且仅当这两人声称的分数区间相交且不重叠。于是该问题转化成一个区间规划的问题，即找到最多的区间使得这些区间之间两两或重叠或不相交。

此题状态转移方程很容易想到，设在区间$[0,i]$上的最大非矛盾区间个数为$f[i]$，则$f[s[i].r]=max \left\{f[k]\right\}$ $(k<s[i].l)+w[i]$ 其中$w[i]$为与$i$区间重合的区间数。维护前缀最大值可以利用树状数组。

此外要注意，若区间长度小于重合区间数，则应选取区间长度作为$w[i]$。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100001;
struct seg{
	int l,r;
	seg(){
		l = 0; r = 0;
	}
	bool operator <(const seg &a) const{
		if (l == a.l) return r < a.r;
		return l < a.l; 
	}
	bool operator ==(const seg &a) const {return (a.l == l)&&(a.r == r);}
}s[maxn];
int x,y,n, ans = 0, tot = 0;
int c[maxn], f[maxn], w[maxn];
inline int lowbit(int x){return x&(-x);}
int qui(int x){
	int ret = 0;
	for(int i = x; i; i -= lowbit(i))
		ret = max(ret, c[i]);
	return ret;
}
void upd(int pos, int val){
	for (int i = pos; i <= n; i += lowbit(i))
		c[i] = max(c[i], val);
}
int main(){
	cin >> n;
	for (int i = 1; i <= n; i ++){
		cin >> x >> y;
		if (x + y < n){
		s[++ tot].l = y + 1;
		s[tot].r = n - x;
		}else ans ++;
	}
	sort(s + 1, s + 1 + tot);
	int j = 1,ini = 1;
	for (int i = 1; i <= tot; i ++){
		if (s[i] == s[j]) continue;
		w[j] = min(i - ini, s[j].r - s[j].l + 1);
		s[++j] = s[i]; ini = i;
	}
	w[j] = min(tot - ini + 1, s[j].r - s[j].l + 1);
	int ttot = tot;
	tot = j;
	for (int i = 1; i <= tot; i ++){
		f[s[i].r] = qui(s[i].l - 1) + w[i];
		upd(s[i].r, f[s[i].r]);
	}
	int ma = 0;
	for (int i = 1; i <= n; i ++)
		if (f[i] > ma) ma = f[i];
	ans += (ttot - ma);
	cout << ans << endl;
	return 0;
} 
```

---

## 作者：丶Cyanide (赞：0)

很简单的一道dp题。
一：
题意转化:最多说真话的人,为在说真话的前提下选尽量多的人。

****二：****

对于a[i]和b[i],指>i的分数和<i的分数的人的个数(没有等于,此题的关键点)。

相当于给所有人分数都排好序的数组中i这个人的可取值下标范围就是b[i]+1到n-a[i]。
选择他说真话,那么bi+1到n-ai分数应当相同。

****于是题目转化为给定n个区间,让我们使尽量多的区间被选。****
(当然只是泛指,还有限制条件,且区间有权值....)
三：(限制条件)
很容易发现2个性质：1.对于完全重合的区间,如果要选这个区间,那么对于所有相同区间一定是能选多少选多少(相同区间分数相同);2.对于不相同且没有公共部分的区间,是互相独立的。3.对于不完全重合且有公共部分的区间,最多只能选择一个。想一想为什么？
四:解法。
可以得到一个解法,把ai.bi转化为区间,相同的区间累加成一个,次数记为cnt[i]。min(cnt[i],r-l+1)为这个这个区间的贡献,记为w[i]。

按r升序排序,令dp[i]为前i个区间且第i个区间必选的最大真话数。dp[i]=dp[j]+w[i](j.r<i.l),因此二分查找最后一个j,使j.r<i.l,用树状数组维护前缀dp最大值。完了
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define lowb(x) x&(-x)
using namespace std;
const int N=100010;//转化一下求最多说真话,每一个人,相当于原数组排完序后有一个选择的区间,对于重复的区间可以同样的分数,不同的区间一定不能选重,简单dp。 
struct nod{
	int l,r;
	int cnt;
}a[N],b[N];
int n,m;
int dp[N];
int tot,t[N];
bool comp1(nod p1,nod p2){return p1.l!=p2.l?p1.l<p2.l:p1.r<p2.r;}
bool comp2(nod p1,nod p2){return p1.r!=p2.r?p1.r<p2.r:p1.l>p2.l;}
void add(int x,int val)
{
	for(int i=x;i<=tot;i+=lowb(i)) t[i]=max(t[i],val);
}
int q(int x)
{
	int tmp=0;
	for(int i=x;i;i-=lowb(i))tmp=max(tmp,t[i]);
	return tmp;
}
int main()
{
	scanf("%d",&n);
	tot=m=0;
	for(int i=1,x,y;i<=n;i++)
	{
		scanf("%d%d",&y,&x);
		y=n-y;x++;
		if(x>y||x<=0||y>n) continue;
		a[++m].l=x;a[m].r=y;a[m].cnt=1;
	}
	sort(a+1,a+m+1,comp1);
	for(int i=1;i<=m;i++)
	{
		b[++tot].cnt=1;b[tot].l=a[i].l;b[tot].r=a[i].r;
		while(i+1<=m&&a[i+1].l==a[i].l&&a[i+1].r==a[i].r) b[tot].cnt++,i++;
	}
	sort(b+1,b+tot+1,comp2);
	for(int i=1;i<=tot;i++) b[i].cnt=min(b[i].cnt,b[i].r-b[i].l+1);
	int ans;
	ans=dp[1]=b[1].cnt;
	add(1,dp[1]);
	for(int i=2,pos,l,r,mid;i<=tot;i++)
	{
		pos=0;
		l=1,r=i-1;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(b[mid].r<b[i].l) pos=mid,l=mid+1;
			else r=mid-1;
		}
		dp[i]=q(pos)+b[i].cnt;ans=max(ans,dp[i]);
		add(i,dp[i]);
	}printf("%d",n-ans);
	return 0;
}
```

---

