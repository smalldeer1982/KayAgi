# Ball

## 题目描述

 $ N $ ladies attend the ball in the King's palace. Every lady can be described with three values: beauty, intellect and richness. King's Master of Ceremonies knows that ladies are very special creatures. If some lady understands that there is other lady at the ball which is more beautiful, smarter and more rich, she can jump out of the window. He knows values of all ladies and wants to find out how many probable self-murderers will be on the ball. Lets denote beauty of the $ i $ -th lady by $ B_{i} $ , her intellect by $ I_{i} $ and her richness by $ R_{i} $ . Then $ i $ -th lady is a probable self-murderer if there is some $ j $ -th lady that $ B_{i}<B_{j},I_{i}<I_{j},R_{i}<R_{j} $ . Find the number of probable self-murderers.

## 样例 #1

### 输入

```
3
1 4 2
4 3 2
2 5 3
```

### 输出

```
1
```

# 题解

## 作者：_Yonder_ (赞：12)

这题首先按 $a_i$ 的值从大到小排序，那后面的 $a_i$ 就一定小于前面的值了。然后这题就是权值线段树了，但是我用的是树状数组。

由于树状数组是求前缀值的，但是题目要求是求大于本身的，所以转化一下题意。求值比本身小的，然后离散化按从大到小的顺序赋值为 $1 \sim i$，那么这题就解决了。
# Code
```
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct node{int a,b,c;}p[N];
map<int,int> m;//离散化
int n,tr[N*3],id,sum;
bool f[N];
void change(int x,int d){while(x<=id) tr[x]=min(tr[x],d),x+=x&-x;}
int ask(int x){int ans=N*3;while(x) ans=min(ans,tr[x]),x-=x&-x;return ans;}
bool cmp(node x,node y){return x.a==y.a?(x.b==y.b?x.c>y.c:x.b>y.b):x.a>y.a;}
int main(){
    memset(tr,0x0f,sizeof(tr));
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i].a),m[p[i].a]=1;
    for(int i=1;i<=n;i++) scanf("%d",&p[i].b),m[p[i].b]=1;
    for(int i=1;i<=n;i++) scanf("%d",&p[i].c),m[p[i].c]=1;
    id=m.size();
    for(auto it=m.begin();it!=m.end();it++)
        it->second=id--;
    id=m.size();sort(p+1,p+1+n,cmp);
    int i=1,j=1;
    while(i<=n){
        while(j<=n&&p[i].a==p[j].a) j++;//这里要把a[i]的值相同的处理出来。
        for(int l=i;l<j;l++)
            if(ask(m[p[l].b]-1)<m[p[l].c]) sum++;//离散化是从大到小赋值的，所以是 < 。
            else f[l]=1;
        for(int l=i;l<j;l++)
            if(f[l]) change(m[p[l].b],m[p[l].c]);//赋值到树状数组。
        i=j;
    }
    printf("%d",sum);
    return 0;
}
```

---

## 作者：离散小波变换° (赞：9)

## 题目大意

有三个数列 $A_i,B_i,C_i$，询问有多少个 $i$，使得存在 $j$，使得 $A_i<A_j,B_i<B_j,C_i<C_j$。

## 题解

题面虽然看上去像是三维偏序，但可以通过一系列转换求解。

首先，我们可以按照 $A_i$ 进行排序。这样的好处是，可以保证符合题意的 $j>i$。然后考虑如何寻找满足 $B_j>B_i$ 的 $j$。

这里使用**值域线段树+动态开点**。

具体而言，我们在值域 $[1,10^9]$ 上维护一个线段树。每次计算完元素 $i$ 的结果，就将线段树上**下标**为 $B_i$ 的位的最大值用 $C_i$ 进行更新。也就是说，如果我们需要访问大于 $B_i$ 的所有元素，本质上就是访问线段树上 $(B_i,10^9]$ 的这一段。取其中 $C_i$ 的最大值，就能知道是否存在元素 $j$，使得$A_i<A_j,B_i<B_j,C_i<C_j$。

动态开点的好处是，只有需要访问线段树对应节点时，再申请该节点空间。

当然，要注意的是，元素 $j$ 可以被加入线段树当且仅当 $A_j>A_i$。

## 参考代码


```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;
const int MAXN =4e6+3,MAXM=1e9+3;
int tot,n,ans;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
#define lc(t) (L[t]?L[t]:(L[t]=++tot))
#define rc(t) (R[t]?R[t]:(R[t]=++tot))
class Seg{
    public:
        int L[MAXN*4],R[MAXN*4],M[MAXN*4];
        void cng(int t,int a,int b,int k,int w){ 
            M[t]=max(M[t],w);if(a==b) return; int mid=(a+b)>>1;
            if(k<=mid) cng(lc(t),a,mid,k,w);
            if(k> mid) cng(rc(t),mid+1,b,k,w);
        }
        int  qry(int t,int a,int b,int l,int r){
            if(l<=a&&b<=r) return M[t];
            int mid=(a+b)>>1,ret=0;
            if(l<=mid) ret=max(ret,qry(lc(t),a,mid,l,r));
            if(r> mid) ret=max(ret,qry(rc(t),mid+1,b,l,r));
            return ret;
        }
}T;
struct Node{
    int a,b,c;
    bool operator <(Node t){
        return a==t.a?(b==t.b?c<t.c:b<t.b):a<t.a;
    }
}P[MAXN];
int main(){
    n=qread(),++tot;
    up(1,n,i) P[i].a=qread();
    up(1,n,i) P[i].b=qread();
    up(1,n,i) P[i].c=qread();
    sort(P+1,P+1+n),P[n+1].a=MAXM;
    dn(n,1,i){
        if(P[i+1].a!=P[i].a){
            for(int p=i+1;P[p].a==P[i+1].a;++p)
            T.cng(1,0,MAXM,P[p].b,P[p].c);
        }
        if(T.qry(1,0,MAXM,P[i].b+1,MAXM)>P[i].c) ++ans;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：EastPorridge (赞：8)

### 题目概述

描述一个有三个元素 $a_i,b_i,c_i$ 的 $t$ ，问针对 $\sum_{i=1}^{n} t_i $ ，求出所有的 $t_j$ 满足 $a_i < a_j , b_i < b_j , c_i < c_j$ 的个数。

### 题目分析

提供一种不用任何数据结构的轻工业解法。

首先我们发现这是一个典型的三位偏序问题，启发我们使用 CDQ 分治，但题目让求的是所有满足条件 $i$ 的个数，而针对 $i$ 是否满足只是一个存在性的问题，如果出现一个 $i$ 满足条件，我们标记 $i$ 就可以了，使用分治套分治即可解决。

我们针对第一维 $a_i$ 从大到小排序，第二维 $b_i$ 分治，然后对 $c_i$ 判断前一半的最大数是否大于目前的 $c_i$ ，如果存在就标记当前的 $st[i]$ ，结束后遍历一遍统计 $st[i]=1$ 的数量就可以了。

### Code.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10; int res,st[N],n;
struct node {int a,b,c,id;} q[N];
bool cmp1(node a,node b) {return a.a > b.a;}
bool cmp2(node a,node b) {return a.b > b.b;}
void cdq(int l,int r)
{
    if(l == r) return; int mid = l + r >> 1;
    int t1=q[mid].a,d1=0,d2=0; cdq(l,mid); cdq(mid+1,r);
    stable_sort(q+l,q+mid+1,cmp2); stable_sort(q+mid+1,q+r+1,cmp2);
    for(int i=mid+1,j=l;i<=r;i++)
	{
        while(j <= mid && q[j].b > q[i].b)
		{
            d1=max(d1,q[j].c);
            if(q[j].a > t1) d2=max(d2,q[j].c);
            j++;
        }
        if(q[i].a == t1) {if(d2 > q[i].c) st[q[i].id]=1;} 
		else {if(d1 > q[i].c) st[q[i].id]=1;}
    }
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) q[i].id=i;
	for(int i=1;i<=n;i++) scanf("%d",&q[i].a);
	for(int i=1;i<=n;i++) scanf("%d",&q[i].b);
	for(int i=1;i<=n;i++) scanf("%d",&q[i].c);
	stable_sort(q+1,q+1+n,cmp1); cdq(1,n);
	for(int i=1;i<=n;i++) if(st[i]) res++;
	printf("%d",res); 
	return 0;
}
```

---

## 作者：LuckyCloud (赞：5)

 ### 本题解，某些话有些绕，已加粗注明重点，可能需要多读几遍，也可以自己画图理解。
 

------------

 第一次看到这道题完全无头绪，偶然间看到了一种东西叫**CDQ分治**——可以解决偏序问题的一种高端操作，不会CDQ分治的同学可以到B站或者Youtube上看视频，讲的超级详细！！我这里就稍微简单的讲一下基于CDQ分治如何解决这道题。
 
 归并排序都会的吧？~~（假装你们会了）~~那么就简单多了，我们首先按所有lady的第一个属性排序，然后按照第二个属性归并排序，重点来了——归并排序有什么用？
 首先我们已经按第一个属性排序过了，那么在归并排序中合并两个有序序列的时候，
 可以保证
 
 **左序列和右序列的所有元素的第一个属性值必定满足某种大小关系**
 
 For Example
 
 (5,3,2)(4,3,2)(3,5,1)(2,4,2)(1,4,3)[已经按第一个属性从大到小排序完成]
 
** 那么我们在归并排序中合并左右两个序列的时候，可以保证，左序列的任意一个元素的第一个属性必定大于右序列任意一个元素的第一个属性。**

OK，不知道你们有没有觉得有一丝神奇。那么接下来在合并左右序列的时候，**当遇到左序列的当前指向元素的第二个属性大于右序列的当前指向元素的第二个属性的时候**我们就把左序列的当前指向元素的第三个属性丢进**树状数组**。当右序列的当前指向元素的第二个属性小于等于右序列的当前指向元素的第二个属性的时候，我们就利用树状数组，通过一些计算，**得出大于右序列当前指向元素的第三个属性的属于左序列的元素的个数**为什么能这样做？第一个属性绝对满足大小关系，上文已经说过。至于第二个属性，**只有大于右序列当前元素的属于左序列的元素被查询的时候才会在树状数组里**

关于以上这些特性请仔细看代码和深入理解归并排序，代码丑陋，请谅解
                                                 
                                                      LuckyCloud 
                                                      
 ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct data
{
 int a,b,c,id;
}p[500003],res[500003];
int n,t,tot,c[500003],ds[500003],f[500003],ans;
inline int read()
{
  register int cnt=0,f=1,ch=getchar();
  while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
  while (ch>='0'&&ch<='9'){cnt=cnt*10+ch-48;ch=getchar();}
  return cnt*f;
}
inline int find(int x)
{
  int l=1,r=tot,mid;
  while (l<=r)
  {
  	mid=(l+r)>>1;
  	if (ds[mid]==x) return mid;
  	if (ds[mid]>x) r=mid-1;
  	if (ds[mid]<x) l=mid+1;
  }
}
inline void clear(int x)
{
  for (int i=x;i<=500000;i+=i&-i)
   c[i]=0;
}
inline void add(int x)
{ 
  for (int i=x;i<=500000;i+=i&-i)
   c[i]++;
}
inline int query(int x)
{
  int res=0;
  for (int i=x;i;i-=i&-i)
   res+=c[i];
  return res;
}
inline bool cmp(data x,data y)
{
  return x.a>y.a||(x.a==y.a&&x.c<y.c);//(x.a==y.a&&x.c<y.c)为了避免一种情况，希望读者自行理解
}
void solve(int l,int r)
{
  int mid=(l+r)>>1,x=l,y=mid+1,len=0;
  while (x<=mid&&y<=r)
  {
  	if (p[x].b>p[y].b){add(p[x].c);res[++len]=p[x++];}
  	else {f[p[y].id]+=x-l-query(p[y].c);res[++len]=p[y++];}//对于(a,b,c)，将x<a,y<b,z<c，(x,y,z)的个数存入f数组
  }
  while (x<=mid) res[++len]=p[x++];
  while (y<=r) {f[p[y].id]+=x-l-query(p[y].c);res[++len]=p[y++];}
  for (int i=l;i<=mid;i++)
   clear(p[i].c);
  for (int i=1;i<=len;i++) 
   p[l+i-1]=res[i];
}
inline void CDQ(int l,int r)
{
  int mid=(l+r)>>1;
  if (l==r) return;
  CDQ(l,mid);
  CDQ(mid+1,r);
  solve(l,r);
}
int main()
{
  n=read();
  for (int i=1;i<=n;i++)
   {p[i].id=i;p[i].a=read();}
  for (int i=1;i<=n;i++)
   p[i].b=read();
  for (int i=1;i<=n;i++)
   ds[i]=p[i].c=read();
  
  sort(ds+1,ds+1+n);//离散化部分
  tot=1;
  t=ds[1];
  for (int i=2;i<=n;i++)
   if (ds[i]!=t){ds[++tot]=ds[i];t=ds[i];}
  for (int i=1;i<=n;i++)
   p[i].c=find(p[i].c);//将第三个属性离散化，用于之后的树状数组。
   
  sort(p+1,p+1+n,cmp);//按第一个属性排序
  
  CDQ(1,n);//CDQ分治
  
  for (int i=1;i<=n;i++)
   if (f[i]>0) ans++;
  printf("%d\n",ans);
  return 0;
}
```
 
 
 
 

---

## 作者：叶枫 (赞：4)

用树状数组也能写
### $Idea$
对于女人$i$，想要知道她自不自杀，无非是有没有女人$j$，使得$B_i<B_j\&\&I_i<I_j\&\&R_i<R_j$。这里用树状数组表示前$i$个女人中$R$值的最大值写，由于那三个值小于等于$1e9$，所以必须离散化。相对其中某个量（这里我按$B$来排序）升序排序，然后编号，这样生成的树状数组，保证在查询时满足$getmax(id+1)$中所有的女人的$B$值比当前女人的要大。于是再按$I$值降序，这样保证在之后的遍历中，$lady[i].i\ge lady[i-1].i$，再以$R$值更新树状数组

### $Code$
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#define ll long long
#define maxn 500050
#define inf 2147483647
#define mod 10003
#define eps 1e-6
#define pi acos(-1.0)
#define de(x) ((x)*(x))
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int c[maxn],cnt,n,ans;
struct Node{
	int b,i,r,id;
}a[maxn];
inline void add(int x,int d){
	while(x>0){
		if(c[x]<d) c[x]=d;
		x-=x&(-x);
	}
}
inline int getmax(int x){
    int res=-1;
    for(int i=x;i<=cnt;i+=i&(-i))
        if(res<c[i]) res=c[i];
    return res;
}
inline bool cmp(Node a,Node b){return a.b<b.b;}
inline bool cmp1(Node a,Node b){return a.i>b.i;}
signed main(){
	n=read();
	int i,j;
	for(i=0;i<n;i++) a[i].b=read();
	for(i=0;i<n;i++) a[i].i=read();
	for(i=0;i<n;i++) a[i].r=read();
	sort(a,a+n,cmp); cnt=1; a[0].id=1;
	for(i=1;i<n;i++)
		if(a[i].b==a[i-1].b) a[i].id=cnt;
		else a[i].id=++cnt;//这个地方不能写成cnt++;原因您们懂得
	sort(a,a+n,cmp1);
	for(i=1;i<=cnt;i++) c[i]=-1;
	for(i=0;i<n;){
		for(j=i;j<n&&a[i].i==a[j].i;j++)
			if(getmax(a[j].id+1)>a[j].r) ans++;
		for(j=i;j<n&&a[i].i==a[j].i;j++)
			add(a[j].id,a[j].r);
		i=j; 
	}
	printf("%d",ans);
    return 0;
}
```

---

## 作者：KazamaRuri (赞：3)

## 题意
给定 $ n $ 个有三个属性 $ a,b,c $ 的元素，问对于多少个元素存在一个三个属性分别大于他自身的属性的元素

## 分析

这是一道三维偏序的题，但只用求存在性，求数量就要用~~cdq分治~~了。

不妨先思考一下只有一个属性 $ a $，即一维偏序的问题。显然，问题变成了有多少个不同于最大值的元素，$ O(n) $ 即可解决。

对于二维，我们可以先按第一个属性逆序排序，这样对于元素 $ i $ 来说，满足条件的元素下标一定在其前面。因为我们只关心**是否存在任意一个元素满足条件，而不用管具体是哪一个元素**，那么我们只需要维护 $ b $ 的前缀最大值，在看一下 $ i - 1 $ 的前缀最大值是否大于 $ b_{i} $，若大于就统计一次答案，总时间复杂度 $ O(n \log_{2}n) $。

到了原题，先按 $ a $ 为第一关键字，$ b $ 为第二关键字逆序排序，满足条件的元素也一定在当前遍历到的元素之前。问题变成了在 $ i $ 前面的元素中，$ b $ 比 $ b_{i} $ 大的元素中是否存在 $ c $ 比 $ c_{i} $ 大的元素，存在则当前元素会被答案统计一次。按照二维偏序的思路，这其实是在  $ [ b_{i} + 1,b_{\max} ] $ 中查询 $ c_{i} $ 的最大值，可以用支持单点修改和区间查询的数据结构随便维护一下，比如权值线段树和权值树状数组，时间复杂度可以做到 $ O(n \log_{2}n) $。

## 代码

注：我用的是维护后缀的树状数组，还有记得离散化。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N=5e5+5;
typedef long long ll;
int n,c[N],h[N],cnt,ans;
struct per{ int a,b,c; }t[N];
int cmp(per x,per y){ return x.a>y.a; }
inline int lb(int x){ return x&-x; }
void upd(int x,int k){ for(;x;x-=lb(x)) c[x]=max(c[x],k); }
int ask(int x){ int ret=-1; for(;x<=n;x+=lb(x)) ret=max(c[x],ret); return ret; }
int f(int x){ return lower_bound(h+1,h+1+cnt,x)-h; }
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&t[i].a);
	for(int i=1;i<=n;i++) scanf("%d",&t[i].b),h[++cnt]=t[i].b;
	for(int i=1;i<=n;i++) scanf("%d",&t[i].c);
	sort(h+1,h+1+n,less<int>());
	cnt=unique(h+1,h+1+n)-h-1;
	for(int i=1;i<=n;i++)
		t[i].b=f(t[i].b); //离散化
	sort(t+1,t+1+n,cmp);
	for(int i=1;i<=n;){
		int j=i-1;
		for(;j<n&&t[i].a==t[j+1].a;j++) ans+=ask(t[j+1].b+1)>t[j+1].c; //a相同的元素统一处理
		for(;i<=j;i++) upd(t[i].b,t[i].c);//更新最值
	}
	printf("%d",ans);
	
	return 0;
}
```

---

## 作者：wdgm4 (赞：3)

 ~~第一次提交蓝题的题解，心情十分鸡冻。QWQ~~ 

## 思路

一个三维偏序（cdq 分治）的板子题。唯一需要注意的是要求是大于而不是大于等于。

我说的要求取决于**具体如何写 cdq 分治**。

首先由于这道题只需要计数，所以我们可以把用树状数组来判断第三维的删去，只剩下分治和双指针，用一个变量取右指针走过的第三维中最大的值（说明右指针走过的前两维都符合要求），如果左指针的第三维满足它与那个变量的要求，就将左指针对应的位置打上标记，最后计数即可。

但是如果直接用三维偏序的板子会有一个问题，就是我们的双指针一个在 $[l,mid]$ 的区间中，一个在 $[mid+1,r]$ 的区间中（前提是已经对第一维从小到大排过序了），那么有可能会出现在 $[l,mid]$ 的区间中的 $i$ 和在 $[mid+1,r]$ 的区间中的 $j$，$a_i=a_j,b_i<b_j,c_i<c_j$ 。直接用板子的代码可能会多算 $i$ 这个位置的值。

所以我们用一个新的变量专门记录如果有上面第一维有问题的，即只取右指针走过的不会出现上述问题的第三维中最大的值。

具体如何实现就看代码吧。QWQ

## 代码

```cpp
#include<bits/stdc++.h>
#define XD 114514
#define MAXN 500010
using namespace std;
int n;
struct QWQ{
	int a,b,c,id;
} a[MAXN];
bool cmp1(QWQ x,QWQ y){
	if(x.a!=y.a) return x.a<y.a;
	if(x.b!=y.b) return x.b<y.b;
	return x.c<y.c;
}
bool cmp2(QWQ x,QWQ y){
	if(x.b!=y.b) return x.b<y.b;
	return x.c<y.c;
}
bool jump[MAXN];
int ans;
void cdq(int l,int r){
	if(l==r) return;
	int mid=l+r>>1,num=a[mid+1].a,cab1=0,cab2=0;
	cdq(l,mid);cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp2);sort(a+mid+1,a+r+1,cmp2);
	int j=r;
	for(int i=mid;i>=l;i--){
		while(a[i].b<a[j].b and j>=mid+1){
			cab1=max(cab1,a[j].c);
			if(a[j].a>num) cab2=max(cab2,a[j].c);
			j--;
		}
		if(a[i].a==num){
			if(cab2>a[i].c) jump[a[i].id]=true;
		}else{
			if(cab1>a[i].c) jump[a[i].id]=true;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].a;
	for(int i=1;i<=n;i++) cin>>a[i].b;
	for(int i=1;i<=n;i++) cin>>a[i].c;
	for(int i=1;i<=n;i++) a[i].id=i;//初始位置
	sort(a+1,a+1+n,cmp1);
	cdq(1,n);
	for(int i=1;i<=n;i++) if(jump[i]) ans++;
	cout<<ans;
	return 0;
}

```

## 后记

记得用较快的输入，不然会 **TLE**。QWQ

---

## 作者：山田リョウ (赞：2)

首先我们先按照以 $a_i$ 为第一关键字、以 $b_i$ 为第二关键字、以 $c_i$ 为第三关键字降序排序，按顺序遍历，遍历到第 $i$ 个人的时候，把 $(b_i,c_i)$ 插进一个数据结构里，并查询这个数据结构中所有的 $b$ 权值比 $b_i$ 大的节点中 $c$ 权值的最大值，如果比 $c_i$ 大的话，就意味着这个女人要跳楼，将 $cnt$ 加 $1$。

具体的，我们可以用一颗值域线段树维护，将 $(b_i,c_i)$ 插进去时，就是让 $b_i$ 这个位置的值和 $c_i$ 取个 $\max$，而查询就是查询后缀 $\max$。

code:
```cpp
// Problem: CF12D Ball
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF12D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <stdio.h>
const int maxnlogw = 15e6 + 2, maxn = 5e5 + 1;
inline int max( int a, int b ) {
    return a > b ? a : b;
}
int n, maxw;
struct tree {
    int a[ maxnlogw ], lc[ maxnlogw ], rc[ maxnlogw ], cnt = 1;
    int _query( int x, int ql, int qr, int l, int r ) {
        if ( ql <= l && r <= qr )
            return a[ x ];
        int mid = l + r >> 1, ans = 0;
        if ( ql <= mid )
            ans = lc[ x ] ? max( ans, _query( lc[ x ], ql, qr, l, mid ) ) : ans;
        if ( mid < qr )
            ans = rc[ x ] ? max( ans, _query( rc[ x ], ql, qr, mid + 1, r ) ) : ans;
        return ans;
    }
    int query( int l, int r ) {
        return _query( 1, l, r, 0, maxw );
    }
    void _set( int x, int y, int k, int l, int r ) {
        if ( l == r ) {
            a[ x ] = max(a[x],k);
            return;
        }
        int mid = l + r >> 1;
        if ( y <= mid )
            _set( lc[ x ] = ( lc[ x ] ? lc[ x ] : ++cnt ), y, k, l, mid );
        else
            _set( rc[ x ] = ( rc[ x ] ? rc[ x ] : ++cnt ), y, k, mid + 1, r );
        a[ x ] = max( a[ lc[ x ] ], a[ rc[ x ] ] );
    }
    void set( int x, int y ) {
        _set( 1, x, y, 0, maxw );
    }
} t;
struct node {
    int a, b, c;
    bool operator<( const node &o ) const {
        return a != o.a ? a > o.a : ( b != o.b ? b > o.b : c > o.c );
    }
} a[ maxn ];
int main( ) {
    scanf( "%d", &n );
    for ( int i = 1; i <= n; ++i )
        scanf( "%d", &a[ i ].a );
    for ( int i = 1; i <= n; ++i )
        scanf( "%d", &a[ i ].b ), maxw = max( maxw, a[ i ].b );
    for ( int i = 1; i <= n; ++i )
        scanf( "%d", &a[ i ].c );
    std::sort( a + 1, a + n + 1 );
    int ans = 0;
    for ( int i = 1; i <= n; ++i ) {
        if ( i > 1 && a[ i ].a < a[ i - 1 ].a )
            for ( int j = i - 1; j && a[ j ].a == a[ i - 1 ].a; --j )
                t.set( a[ j ].b, a[ j ].c );
        ans += t.query( a[ i ].b + 1, maxw ) > a[ i ].c;
    }
    printf( "%d", ans );
    return 0;
}
```

---

## 作者：Planetary_system (赞：1)

## 题面解释：
有 $n$ 组数，每组 $3$ 个，求满足存在其他一组 $3$ 个数都比本组数大的个数。

## 思路分析：
对于第一个数 $x$ 用排序确定顺序，然后再用一棵权值线段树（值域 $10^9$ 所以建议使用动态开点），求出 $y$ 所在范围内 $z$ 的最大值与当前 $z$ 值比较，计数即可。

这里要注意题目要求不包括等于情况，所以要把相同数算完之后再加到线段树内。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,tot,root,ans,tr[N<<5],ls[N<<5],rs[N<<5];
struct node{int x,y,z;}a[N];
bool cmp(node q,node p){
	if(q.x==p.x&&q.y==p.y)return q.z>p.z;
	if(q.x==p.x)return q.y>p.y;
	return q.x>p.x;
}
void push_up(int p){
	if(ls[p])tr[p]=max(tr[p],tr[ls[p]]);
	if(rs[p])tr[p]=max(tr[p],tr[rs[p]]);
	return;
}
void upd(int &p,int l,int r,int x,int y){
	if(!p)p=++tot;
	if(l==r){
		tr[p]=max(tr[p],y);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)upd(ls[p],l,mid,x,y);
	if(mid+1<=x)upd(rs[p],mid+1,r,x,y);
	push_up(p);
	return;
}
int qry(int p,int pl,int pr,int l,int r){
	if(l<=pl&&pr<=r)return tr[p];
	int res=0,mid=(pl+pr)>>1;
	if(ls[p]&&l<=mid)res=max(res,qry(ls[p],pl,mid,l,r));
	if(rs[p]&&mid+1<=r)res=max(res,qry(rs[p],mid+1,pr,l,r));
	return res;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].x);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].y);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].z);
	sort(a+1,a+n+1,cmp);
	for(int i=1,j=1;i<=n;i++){
		if(qry(root,0,1e9,a[i].y+1,1e9)>a[i].z)ans++;
		while(a[i].x!=a[i+1].x&&j<=i)upd(root,0,1e9,a[j].y,a[j].z),j++;
	}
	printf("%d",ans);	
	return 0;
}
```

谢谢！

---

## 作者：wizardMarshall (赞：0)

## 题意

求 $i$ 的个数使得对于这个 $i$ 存在 $j$，$a_i < a_j,b_i < b_j,c_i <c_j$。

## 思路

乍一眼看类似三维偏序（其实不然）。

套路地，将 $a$ 从大到小排序，问题就变成了 $b$ 与 $c$ 之间的关系。考虑枚举每个元素。

从左到右依次操作，用一个线段树维护当前状态。具体地，$[l,r]$ 区间表示 $\max(c_i)$，其中 $i$ 满足 $l \le b_i \le r$（即值域线段树）。由于 $b$ 过大，需要离散化（假设最大值为 $m$）。

每次只要将 $[b_i+1,m]$ 中的最大值 $C$ 与当前 $c_i$ 做比较，若 $C>c_i$，则说明三个条件都满足，$i$ 是答案之一（这里我们不用知道 $i$ 具体与谁发生关系，只需要知道存在这个值即可）。

还有一个注意点，由于题目需要 $a_i$ 严格小于 $a_j$，因此如果立刻存入线段树，可能会导致一些 $a$ 相等。需要暂时存下 $a$ 相等的这些元素，待 $a$ 变化后再放进线段树中。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
map <int, int> mp;
struct node{
	int a, b, c;
}a[N];
bool cmp(node a, node b) {
	return a.a > b.a;
}
vector <node> temp;int now_a;//如果a大于now_a就把积存的元素修改
int mx[N << 2];//c的最大值，如上文

void change(int id, int value, int l, int r, int x) {//单点更新
	if (l == r) {
		mx[x] = max(mx[x], value);
		return;
	}
	int m = (l + r) / 2;
	if (id <= m) {
		change(id, value, l, m, x * 2);
	}else {
		change(id, value, m + 1, r, x * 2 + 1);
	}
	mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
    return;
}

int ask(int L, int R, int l, int r, int x) {//查询区间
	if (L <= l && r <= R) {
		return mx[x];//返回最大值，下同
	}
	int m = (l + r) / 2;
	int ret = 0;
	if (L <= m) {
		ret = max(ret, ask(L, R, l, m, x * 2));
	}if (R > m) {
		ret = max(ret, ask(L, R, m + 1, r, x * 2 + 1));
	}return ret;
}
signed main() {
	int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].a);
	}
    for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].b);
		mp[a[i].b] = 1;
	}
    for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].c);
	}
  //离散化：
	int E = 0;
	for (auto i : mp) {
		mp[i.first] = ++E;
	}
	for (int i = 1; i <= n; i++) {
		a[i].b = mp[a[i].b];
	}
	sort(a + 1, a + n + 1, cmp);//按a的值排序
	now_a = a[1].a;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].a != now_a) {//a与上一个不相等，可以把之前所有a相等的元素压入
			for (auto j : temp) {
				change(j.b, j.c, 1, E, 1);//修改
			}temp.clear();
			now_a = a[i].a;//更新now_a的值
		}temp.push_back(a[i]);//同样的，暂时存储
		if (a[i].b != E && ask(a[i].b + 1, E, 1, E, 1) > a[i].c) {//存在b_j>b_i且c_j>c_i
			ans++;
		}
	}cout << ans;
	return 0; 
}
```

---

## 作者：Unnamed114514 (赞：0)

这题是一个三维偏序，但是由于只需要考虑每个位置的存在性而并不需要计数，所以有比 $O(n\log n)$ 的 CDQ 分治的更优秀的方法。

首先按照 $(a,b,c)$ 为第一、二、三关键字排序。

然后我们倒着枚举，这样就能满足 $a$ 的限制。

维护一棵线段树，下标是 $b$，每个位置要找 $c$ 的最大值。

记录 $pre$ 表示已经插入完的原序列的后缀的最左边的前一个位置。如果 $a_i\ne a_{pre}$，那么把 $(i,pre]$ 插入即可。

查询 $(b_i+1,+\infty)$ 中 $c$ 的最大值，满足 $b$ 的限制，如果这个最大值大于了 $c_i$ 就会对答案造成贡献。

时间复杂度 $O(n\log n)$。

---

## 作者：taojinchen (赞：0)

# 思路
我们可以先考虑从两个维度去比较：两个维度时，我们就可以考虑将第一个维度开一个桶，桶中的每一个元素的权值为第二个维度的值。这时候，我们发现桶中的每一个元素的右边第一个维度的值都是比他大的，这一个元素的右边有权值更大的数，这两个值都比它高。对于这一种寻找连续区间的最值，还要支持修改，我们就可以想到用线段树来写。

然后就是三个维度：我们思考一下，如何才可以去掉第三个维度的影响？要是之前插入的值都是第三个维度更大的就好了。等等！我们排一下顺序不就可以了吗？我们按照排序后的顺序插入不就好了。

注意！一定要考虑等于。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;//代码建议扔去格式化，不想看代码的话建议看看注释
const int kM=5e5+5;
ll ans,x,y,d=1,q,cnt,i,j,n,m,k,h[kM<<2],top;
struct T{
  ll ma;//作者**了（模板上直接改的，删了lazy_tag）
}tr[kM<<3];
struct M{
  ll b,i,r;
}a[kM];
//--------线段树-----
void update(int rt,int l,int r){
  if(x<=l&&r<=y){
    tr[rt].ma=max(tr[rt].ma,d);
    return;
  }
  int mid=(l+r)>>1;
  if(x<=mid)update(rt<<1,l,mid);
  if(mid<y)update(rt<<1|1,mid+1,r);
  tr[rt].ma=max(tr[rt<<1].ma,tr[rt<<1|1].ma);
  return;
}
ll push_down(int rt,int l,int r){//个人习惯，应该为q…（不记得了
  if(x<=l&&r<=y){
    return tr[rt].ma;
  }
  ll ret=0,mid=(l+r)>>1;
  if(x<=mid)ret=max(ret,push_down(rt<<1,l,mid));
  if(mid<y)ret=max(ret,push_down(rt<<1|1,mid+1,r));
  tr[rt].ma=max(tr[rt<<1].ma,tr[rt<<1|1].ma);
  return ret;
}
//---------排序时要-----------
bool cmp(M a,M b){
  return a.b>b.b;
}
//----------------------------
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  //------输入-------
  cin>>n;
  for(i=1;i<=n;i++){
    cin>>a[i].b;
    h[++cnt]=a[i].b;
  }
  for(i=1;i<=n;i++){
    cin>>a[i].i;
    h[++cnt]=a[i].i;
  }
  for(i=1;i<=n;i++){
    cin>>a[i].r;
    h[++cnt]=a[i].r;
  }
  //-----离散化-------
  sort(h+1,h+1+cnt);
  cnt=unique(h+1,h+1+cnt)-h-1;
  for(i=1;i<=n;i++){
    a[i].b=lower_bound(h+1,h+1+cnt,a[i].b)-h;
    a[i].i=lower_bound(h+1,h+1+cnt,a[i].i)-h;
    a[i].r=lower_bound(h+1,h+1+cnt,a[i].r)-h;
  }
  //---------核心代码--------
  sort(a+1,a+1+n,cmp);
  top=1;
  for(i=2;i<=n;i++){
    if(a[i].b!=a[i-1].b){//为了避免等于的干扰就可以先记下来，后面再搞
      for(j=top;j<i;j++){
        x=y=a[j].r,d=a[j].i;//线段树
        update(1,1,cnt);
      }
      top=i;
    }
    x=a[i].r+1,y=cnt;
    if(x>cnt)continue;//边界
    if(push_down(1,1,cnt)>a[i].i){
      ans++;//统计
    }
  }
  cout<<ans;//输出
  return 0;
}
```


---

