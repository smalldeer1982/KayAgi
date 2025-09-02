# Dynamic Rankings

## 题目描述

给定一个含有 $n$ 个数的序列 $a_1,a_2 \dots a_n$，需要支持两种操作：  

- `Q l r k` 表示查询下标在区间 $[l,r]$ 中的第 $k$ 小的数  
- `C x y` 表示将 $a_x$ 改为 $y$ 


## 说明/提示

【数据范围】  

对于 $10\%$ 的数据，$1\le n,m \le 100$；  
对于 $20\%$ 的数据，$1\le n,m \le 1000$；  
对于 $50\%$ 的数据，$1\le n,m \le 10^4$；     
对于 $100\%$ 的数据，$1\le n,m \le 10^5$，$1 \le l \le r \le n$，$1 \le k \le r-l+1$，$1\le x \le n$，$0 \le a_i,y \le 10^9$。

请注意常数优化，但写法正常的整体二分和树套树都可以以大约 $1000\text{ms}$ 每个点的时间通过。

来源：bzoj1901

本题数据为洛谷自造数据，使用[CYaRon](https://github.com/luogu-dev/cyaron)耗时5分钟完成数据制作。


## 样例 #1

### 输入

```
5 3
3 2 1 4 7
Q 1 4 3
C 2 6
Q 2 5 3```

### 输出

```
3
6
```

# 题解

## 作者：租酥雨 (赞：170)

类似算法总结

**1、静态整体Kth**

滑稽吧...sort一遍就好了。

时间复杂度$O(nlogn)$    空间复杂度$O(n)$

**2、动态整体Kth**

离散化后开一棵权值线段树，每个位置的值表示这个位置对应的那个数（离散化后的）有多少个，向上维护和；

查询时先查询左子树和sum，比较k和sum的大小：若k<=sum则说明第k小数在左子树中，递归查询左子树；

否则，这个数对应的就是右子树中第k-sum小的数，k-=sum，递归查询右子树。

时间复杂度$O(nlogn)$    空间复杂度$O(n)$

**3、静态区间Kth**

对每个点以其前缀开一棵权值线段树，那么任意一段区间均可以表示成为两棵权值线段树作差，即R位置的线段树减去L-1位置上的线段树

每个点开一棵线段树空间复杂度$O(n^2)$，MLE，考虑到后一个位置相比于前一个位置的更改只有$logn$个节点，所以使用主席树

时间复杂度$O(nlogn)$    空间复杂度$O(nlogn)$

**4、动态区间Kth**(就是本题辣)

还是要想办法维护前缀和。如果只是同3、的前缀和的话，就要对前缀和进行$O(nlogn)$的单次修改，显然TLE。

这里考虑用树状数组维护前缀和。修改时，可以只修改$logn$个位置，复杂度$O(log^2n)$；

查询时，依旧是R位置减去L-1位置，这时候不再是两棵线段树作差，而是log棵线段树与log棵线段树作差；跳的时候，log个节点一起跳到左子树/右子树

时间复杂度$O(nlog^2n)$    空间复杂度$O(nlogn)$

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAX=10005;
struct segment_tree{int v;int ls,rs;}t[MAX*400];//线段树开nlogn大小
struct operation{bool b;int l,r,k;int pos,t;}q[MAX];//因为要离散花所以要把所有数据输进来离线搞
int n,m,a[MAX],o[MAX<<1],rt[MAX],len,tot,temp[2][20],cnt[2];
char opt;
void Modify(int &now,int l,int r,int pos,int val)
{
    if (!now) now=++tot;
    t[now].v+=val;
    if (l==r) return;
    int mid=l+r>>1;
    if (pos<=mid) Modify(t[now].ls,l,mid,pos,val);
    else Modify(t[now].rs,mid+1,r,pos,val);
}
void prepare_Modify(int x,int val)
{
    int k=lower_bound(o+1,o+len+1,a[x])-o;
    for (int i=x;i<=n;i+=i&-i) Modify(rt[i],1,len,k,val);//处理出需要修改哪log棵主席树
}
int Query(int l,int r,int k)
{
    if (l==r) return l;
    int mid=l+r>>1,sum=0;
    for (int i=1;i<=cnt[1];i++) sum+=t[t[temp[1][i]].ls].v;
    for (int i=1;i<=cnt[0];i++) sum-=t[t[temp[0][i]].ls].v;
    if (k<=sum)
    {
        for (int i=1;i<=cnt[1];i++) temp[1][i]=t[temp[1][i]].ls;
        for (int i=1;i<=cnt[0];i++) temp[0][i]=t[temp[0][i]].ls;
        return Query(l,mid,k);
    }
    else
    {
        for (int i=1;i<=cnt[1];i++) temp[1][i]=t[temp[1][i]].rs;
        for (int i=1;i<=cnt[0];i++) temp[0][i]=t[temp[0][i]].rs;
        return Query(mid+1,r,k-sum);
    }
}
int prepare_Query(int l,int r,int k)
{
    memset(temp,0,sizeof(temp));//同修改，处理出需要进行相减操作的是哪log棵主席树
    cnt[0]=cnt[1]=0;
    for (int i=r;i;i-=i&-i) temp[1][++cnt[1]]=rt[i];
    for (int i=l-1;i;i-=i&-i) temp[0][++cnt[0]]=rt[i];
    return Query(1,len,k);
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for (int i=1;i<=n;i++) cin>>a[i],o[++len]=a[i];
    for (int i=1;i<=m;i++)
    {
        cin>>opt;
        q[i].b=(opt=='Q');
        if (q[i].b)    cin>>q[i].l>>q[i].r>>q[i].k;
        else cin>>q[i].pos>>q[i].t,o[++len]=q[i].t;
    }
    sort(o+1,o+len+1);
    len=unique(o+1,o+len+1)-o-1;//离散 —— 排序 + 去重
    for (int i=1;i<=n;i++) prepare_Modify(i,1);
    for (int i=1;i<=m;i++)
    {
        if (q[i].b)    printf("%d\n",o[prepare_Query(q[i].l,q[i].r,q[i].k)]);
        else
        {
            prepare_Modify(q[i].pos,-1);
            a[q[i].pos]=q[i].t;
            prepare_Modify(q[i].pos,1);
        }
    }
    return 0;
}
```

---

## 作者：ThinkofBlank (赞：83)

# 		       【带修改的主席树】理解

## 一:前置芝士:

## 1.树状数组(不会树状数组来打这个?(大雾   )

##   	 	      2.主席树（不会主席树来打这个?(巨雾   )

## 		      3.前缀和  (不会前缀和来打这个?(神雾   ）

## 		      4.权值线段树 (不会权值线段树来打这个?(仙雾)    )

## 		      5.看这篇文章的你需要用主席树将求区间kth练得比较熟，并且要理解其原理。

## 二:分(che)析(dan):

首先,我们知道,主席树其实是一颗具有n个根的树(介于树与森林之间)。第i个根所形成的树(为了简写,我们用T(i)表示)其实就相当于将序列1->i依次添加进一个权值线段树所形成的树。

 我们又知道，权值线段树所储存的信息其实是它所管的区间中数字的数量，所以，对于区间l->r所形成的权值线段树,它相当于将T(r)的每一个节点与T(l-1)中对应的节点作差所行成的树。用一句话概括:"对于1->i所形成的树,它是可减的。"这便是主席树的核心内容。

#### 	然后，boss来了，如何使主席树资瓷修改操作呢？

 暴力的做法:如果我们修改了节点x的值(设为w[x])为y，那么包含节点x的主席树为T(x)->T(n)，我们只需要把T(x)->T(n)都去减一个w[x]的值,加一个y。单次复杂度O(nlogn)。于是光荣地超时了QwQ

 那么，我们该怎么办呢？

 #### 这里给出答案:我们知道，在查询时，我们需要将T(r)-T(l-1)，其中T(x)表示的是将1-x序列构成的权值线段树。即是说:T(x)=T(x-1)+w[x] (这里的‘+’代指将w[x]添加到树中)。现在有没有什么感觉？没错！T(x)其实就相当于记录的前缀和(注:此前缀和非彼前缀和)！于是，查询时，我们相当于求1->r,与1->l-1的一个前缀和！

#### 	现在，我们简化下题目:给出一个序列，资瓷单点修改和求区间和

 看到这里，是不是恍然大悟？这不是~~sb~~树状数组(线段树/分块)嘛!

 ~~由于树状数组快，又好打，所以我们选择树状数组(抠鼻~~

#### 	没错！其实我们只需要像做树状数组那样，维护这个序列就好了！只需要将每次的O(1)加法替换成O(log n)的修改主席树的add操作即可！复杂度O(nlognlogn)!

 撒花！！！

## 三:实现:

 由于某种神奇的玄学原因，我的代码的常数巨大，不适用于各位同学，所以，这里给只出[代码](https://www.luogu.org/paste/dlxstput)。同学们可以自行去网上搜搜模板，看看大佬们的巨快实现！

## 四:闲话:

 讲了这么多，感觉，还是自己讲得自己理解得比较好啊QwQ。我感觉我讲的其实还是挺好的吧？



---

## 作者：zcysky (赞：81)

怕是还没有题解，所以先写一篇。


这题就是维护带修改的主席树。首先树套树肯定是能做的，既然树套树能做那么整体二分肯定也是可以的。


由于我并没有使用这两种做法，所以此处不予介绍。


大概描述下主席树的思路：


首先说说怎么搞带修改主席树？


回忆一般的kth问题，我们的主席树求的是前缀和，这样我们在目标区间的左右端点的主席树差分下就能求出kth。


那么我们如何支持修改操作？


考虑到我们之前使用主席树朴素的维护区间前缀和，支持修改的话，只要把前缀和交给擅长它的树状数组维护，主席树只要维护下位置就好。


顺手广告：http://www.cnblogs.com/zcysky/p/6832876.html


代码：

```cpp
#include<bits/stdc++.h>
#define N 10005
using namespace std;
inline int lowbit(int x){return x&-x;}
int n,m,sz,totn,totx,toty,a[N],b[N<<1],ca[N],cb[N],cc[N];
int xx[N],yy[N],rt[N],size[600\*N],ls[600\*N],rs[600\*N];
void ins(int &o,int l,int r,int x,int q,int v){
    o=++sz;size[o]=size[x]+v;ls[o]=ls[x];rs[o]=rs[x];
    if(l==r)return;int mid=(l+r)>>1;
    if(q<=mid)ins(ls[o],l,mid,ls[x],q,v);
    else ins(rs[o],mid+1,r,rs[x],q,v);
}
int query(int l,int r,int q){
    if(l==r)return l;
    int sum=0,mid=(l+r)>>1;
    for(int i=1;i<=totx;i++)sum-=size[ls[xx[i]]];
    for(int i=1;i<=toty;i++)sum+=size[ls[yy[i]]];
    if(q<=sum){
        for(int i=1;i<=totx;i++)xx[i]=ls[xx[i]];
        for(int i=1;i<=toty;i++)yy[i]=ls[yy[i]];
        return query(l,mid,q);
    }
    else{
        for(int i=1;i<=totx;i++)xx[i]=rs[xx[i]];
        for(int i=1;i<=toty;i++)yy[i]=rs[yy[i]];
        return query(mid+1,r,q-sum);
    }
}
void add(int x,int v){
    int k=lower\_bound(b+1,b+totn+1,a[x])-b;
    for(int i=x;i<=n;i+=lowbit(i))ins(rt[i],1,totn,rt[i],k,v);
}
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x\*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f\*x;
}
int main(){char s[20];
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read(),b[++totn]=a[i];
    for(int i=1;i<=m;i++){
        scanf("%s",s);ca[i]=read();cb[i]=read();
        if(s[0]=='Q')cc[i]=read();else b[++totn]=cb[i];
    }
    sort(b+1,b+totn+1);
    totn=unique(b+1,b+totn+1)-b-1;
    for(int i=1;i<=n;i++)add(i,1);
    for(int i=1;i<=m;i++){
        if(cc[i]){
            totx=toty=0;
            for(int j=ca[i]-1;j;j-=lowbit(j))xx[++totx]=rt[j];
            for(int j=cb[i];j;j-=lowbit(j))yy[++toty]=rt[j];
            printf("%d\n",b[query(1,totn,cc[i])]);
        }
        else{add(ca[i],-1);a[ca[i]]=cb[i];add(ca[i],1);}
    }
}
···

---

## 作者：yurzhang (赞：47)

更好的阅读体验 -> [推销博客](https://nikaidou-shinku.github.io/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91-Luogu2617-DynamicRankings/)

---

# 前言

在题解区看见了一个用分块写这个题的，但是在数据加强到 $10^5$ 后貌似已经过不去了（或许卡卡常还有救），难道分块真的就比不过这些树套树整体二分？不不不，分块的潜力远远不止这些！

分块无快读无 $\text{O2}$ [评测记录](https://www.luogu.org/record/22245870)

---

# 正文

之前那篇分块题解的做法是二分答案，然后块内二分检验，这样做的时间复杂度是 $O(n\sqrt n\log n\log V)$ 的，其中 $V$ 是值域。然而二分跟分块就很不搭，我们考虑一个不需要二分也能求第 $k$ 小的方法。

先离散化，对序列分块，考虑维护块内每个数的出现次数，再将值域分块，维护每个块内每个值域块中数的出现次数。然后做前缀和，这样我们就能 $O(1)$ 查询一段块中每个数的出现次数以及每个值域块中数的出现次数。这部分的预处理是 $O(n\sqrt n)$ 的。

查询时考虑将散块中每个数及值域块中数的出现次数先记录下来，这部分是 $O(\sqrt n)$ 的，然后跳值域块，超过 $k$ 了就跳块内的数，直到找到正好超过 $k$ 的位置，这样可以 $O(\sqrt n)$ 查询第 $k$ 小。

修改时只要考虑对预处理的信息的影响即可，由于我们预处理的是前缀和，所以每次修改至多修改 $O(\sqrt n)$ 个块。

这样我们就得到了一个 $O(n\sqrt n)$ 的优秀算法，可以通过此题。

---

# 最后

这个做法是另一个题的 $trick$ ，有兴趣的可以去试一下：[望月悲叹的最初分块](https://www.luogu.org/problem/P4119)。

最后给出代码，仅供参考：

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using std::sort;
using std::unique;
using std::lower_bound;

#define N 100010

inline int min(int a,int b) {
	return a<b?a:b;
}

struct node{int opt,l,r,k;}q[N];
int n,m,a[N],b[N<<1],tot,l,r,k;
char opt;

int L[320],R[320];
int siz,szv,num,numsz;
int bl[N],blv[N<<1];
int sumc[320][N<<1];
int sums[320][450];

inline void modify(int x,int y) {
	for(int i=bl[x];i<=num;++i) {
		--sumc[i][a[x]];
		--sums[i][blv[a[x]]];
		++sumc[i][y];
		++sums[i][blv[y]];
	}
	a[x]=y;
}

int tmpa[N<<1],tmpc[450];
inline int query(int l,int r,int k) {
    int ans;
	if(bl[l]==bl[r]) {
		int vl,vr,tmp(0);
		for(int i=l;i<=r;++i)
			++tmpa[a[i]],++tmpc[blv[a[i]]];
		for(int i=1;i<=numsz;++i) {
			tmp+=tmpc[i];
			if(tmp>=k) {
				tmp-=tmpc[i];
				vl=(i-1)*szv+1;
				vr=i*szv;
				break;
			}
		}
		for(int i=vl;i<=vr;++i) {
			tmp+=tmpa[i];
			if(tmp>=k) {
			    ans=b[i];
			    break;
			}
		}
		for(int i=l;i<=r;++i)
			tmpa[a[i]]=0,tmpc[blv[a[i]]]=0;
	} else {
		int vl,vr,tmp(0);
		for(int i=l;i<=R[bl[l]];++i)
			++tmpa[a[i]],++tmpc[blv[a[i]]];
		for(int i=L[bl[r]];i<=r;++i)
			++tmpa[a[i]],++tmpc[blv[a[i]]];
		for(int i=1;i<=numsz;++i) {
			tmp+=tmpc[i]+sums[bl[r]-1][i]-sums[bl[l]][i];
			if(tmp>=k) {
				tmp-=tmpc[i]+sums[bl[r]-1][i]-sums[bl[l]][i];
				vl=(i-1)*szv+1;
				vr=i*szv;
				break;
			}
		}
		for(int i=vl;i<=vr;++i) {
			tmp+=tmpa[i]+sumc[bl[r]-1][i]-sumc[bl[l]][i];
			if(tmp>=k) {
			    ans=b[i];
			    break;
			}
		}
		for(int i=l;i<=R[bl[l]];++i)
			tmpa[a[i]]=0,tmpc[blv[a[i]]]=0;
		for(int i=L[bl[r]];i<=r;++i)
			tmpa[a[i]]=0,tmpc[blv[a[i]]]=0;
	}
	return ans;
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) {
		scanf("%d",a+i);
		b[++tot]=a[i];
	}
	for(int i=1;i<=m;++i) {
		scanf("\n%c%d%d",&opt,&l,&r);
		if(opt=='Q') {
			scanf("%d",&k);
			q[i]=(node){1,l,r,k};
		} else {
			q[i]=(node){2,l,r,0};
			b[++tot]=r;
		}
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;++i)
		a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	
	siz=ceil(sqrt(n));
	szv=ceil(sqrt(tot));
	for(int i=1;i<=n;++i)
		bl[i]=(i-1)/siz+1;
	for(int i=1;i<=tot;++i)
		blv[i]=(i-1)/szv+1;
	num=bl[n],numsz=blv[tot];
	for(int i=1;i<=num;++i) {
		L[i]=R[i-1]+1;
		R[i]=min(L[i]+siz-1,n);
		for(int j=1;j<=tot;++j)
			sumc[i][j]=sumc[i-1][j];
		for(int j=1;j<=numsz;++j)
			sums[i][j]=sums[i-1][j];
		for(int j=L[i];j<=R[i];++j) {
			++sumc[i][a[j]];
			++sums[i][blv[a[j]]];
		}
	}
	
	for(int i=1;i<=m;++i) {
		if(q[i].opt==1)
			printf("%d\n",query(q[i].l,q[i].r,q[i].k));
		else modify(q[i].l,lower_bound(b+1,b+tot+1,q[i].r)-b);
	}
	return 0;
}
```



---

## 作者：yingjz (赞：47)

**博客食用体验更佳~~感觉我很不要脸~~：[https://yjzoier.gitee.io/hexo/p/af72.html](https://yjzoier.gitee.io/hexo/p/af72.html)**

这是蒟蒻我第一次写树套树的题，打算写一篇**对初学者友好**的题解。

本文介绍**树套树**做法。

## 题目大意

题目链接：<https://www.luogu.org/problemnew/show/P2617>

本问题其实就是 **动态区间第 $k$ 小问题**

具体来讲，初始时给出一个序列 $a_i$，需要维护 $2$ 种操作：

1. 查询 $a_l \dots a_r$ 中第 $k$ 大的元素
2. 将 $a_i$ 的值修改为 $t$

## 题解

大家应该都会 **静态区间第K小** 问题，如果没有做过，请出门右转 → <https://www.luogu.org/problemnew/show/P3834>

**静态区间第K小** 最常用的做法是主席树，即维护权值线段树的前缀和。我们用 $T(i)$ 表示第 $i$ 棵线段树，那么主席树其实就是 $T(i) = T(i-1) + a_i$。也就是说，主席树就是暴力的前缀和，$T(i) = \sum_{j=1}^i a_j$。暴力的前缀和如果要单点修改时间复杂度就是 $O(n)$，又在权值线段树上单点修改是 $O(\log n)$ 的，所以暴力维护主席树单次操作的时间复杂度是 $O(n \log n)$。而查询操作，本质上就是要求出需要查询的区间 $[l,r]$ 对应的权值线段树的 $O(\log n)$ 个结点的权值。朴素的做法是用前缀和转化为 $T(r) - T(l)$。

这样虽然会超时，但是给进一步的优化带来了思路。问题就转化为了**单点修改，区间查询**的问题，就可以使用树状数组(或线段树)来解决。也就是说，每棵权值线段树 $T(i) = \sum_{j = i - lowbit(i) + 1}^i a_j$；这样每次修改 $a_i$ 的时候都要修改对应的 $O(\log n)$ 棵权值线段树，每次查询前缀和的时候都要求出 $O(\log n)$ 棵权值线段树对应节点的和。总时间复杂度和空间复杂度都是 $O(n \log^2 n)$。

我们可以发现树套树问题分析的时候需要把**每棵树看成一个点**，用*自顶向下*的方法进行分析，这样会更加容易分析。

### 实现

```c++
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 100007;

int n, m, num, n1, n2;
int a[N], b[N << 1], c[N], d[N], e[N], t1[N], t2[N];
int Top, Root[N], val[N * 400], ls[N * 400], rs[N * 400];

inline int lowbit(int x) {
    return x & (-x);
}

void Add(int &rt, int l, int r, int ind, int c) {
    if (!rt) rt = ++Top; 
    val[rt] += c;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (ind <= m) Add(ls[rt], l, m, ind, c);
    else Add(rs[rt], m+1, r, ind, c);
}

void Change(int ind, int val) {
    int x = lower_bound(b + 1, b + 1 + num, a[ind]) - b;
    for (int i = ind; i <= n; i += lowbit(i))
        Add(Root[i], 1, num, x, val);
}

int Kth(int l, int r, int k) { //求第 k 大
    // printf("%d %d %d\n", l, r, k);
    if (l == r) return l;
    int m = (l + r) >> 1, sum = 0;
    for (int i = 1; i <= n2; ++i)
        sum += val[ls[t2[i]]];
    for (int i = 1; i <= n1; ++i)
        sum -= val[ls[t1[i]]];
    if (sum >= k) {
        for (int i = 1; i <= n1; ++i) //所有树的节点保持对应
            t1[i] = ls[t1[i]];
        for (int i = 1; i <= n2; ++i)
            t2[i] = ls[t2[i]];
        return Kth(l, m, k);
    } else {
        for (int i = 1; i <= n1; ++i)
            t1[i] = rs[t1[i]];
        for (int i = 1; i <= n2; ++i)
            t2[i] = rs[t2[i]];
        return Kth(m+1, r, k - sum);
    }
}

int Kth_pre(int l, int r, int k) { 
    n1 = n2 = 0;
    for (int i = l - 1; i >= 1; i -= lowbit(i)) //处理出需要求和的 n1 棵树
        t1[++n1] = Root[i];
    for (int i = r; i >= 1; i -= lowbit(i)) 
        t2[++n2] = Root[i];
    return Kth(1, num, k);
}

int main(){
    //读入
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[++num] = a[i];
    }
    for (int i = 1; i <= m; ++i) {
        char ch = getchar();
        while (ch != 'Q' && ch != 'C') 
            ch = getchar();
        if (ch == 'Q') 
            scanf("%d%d%d", &c[i], &d[i], &e[i]);
        else {
            scanf("%d%d", &c[i], &d[i]);
            b[++num] = d[i]; //对于所有出现过的值（包括插入操作中的值）离散化
        }
    }
    //离散化
    sort(b + 1, b + 1 + num);
    num = unique(b + 1, b + 1 + num) - b - 1;
    //建树
    for (int i = 1; i <= n; ++i)
        Change(i, 1);
    //处理操作&询问
    for (int i = 1; i <= m; ++i) {
        if (e[i]) {
            printf("%d\n", b[Kth_pre(c[i], d[i], e[i])]);
        } else {
            Change(c[i], -1);
            a[c[i]] = d[i];
            Change(c[i], 1);
        }
    }
    return 0;
}
```

## 参考资料

1. ThinkofBlank - 题解 P2617 【Dynamic Rankings】 <https://www.luogu.org/blog/KingofNight/solution-p2617>

2. 租酥雨 - 题解 P2617 【Dynamic Ranking】<https://www.luogu.org/blog/zhoushuyu/solution-p2617>

---

## 作者：LPA20020220 (赞：37)

可能网上都是dalao吧，翻遍了CSDN和博客园竟然没有一篇详细的树状数组套主席树，全部是4、5行简简单单的说明就敷衍过去了，之后就是一堆一堆的代码，害的蒟蒻我看了几天QAQ...

终于在几位大牛的指导下和自己的探索中成功A掉了本题，并且有不开O2 140ms，开O2 72ms的优良常数。

接下来就来谈谈主席树吧。主席树的基本构成是一棵棵线段树，保存前缀中所有可能出现的数字出现的次数。为了节省空间，因为保存的为前缀，所以和每棵单独的线段树和上一棵线段树有相似的结构和仅仅一条链的差别，所以我们可以在构建静态主席树的时候将没有更改过的节点直接用上一棵线段树的节点代替，如此下来每一棵线段树只会多开logn条链，不会MLE。

既然说了保存的是可能出现的数字出现的次数，那么总不可能保存1e9个吧，所以我们需要对操作离线化处理一下，将所有涉及到的数字先进行去重与排序，再用序列号来代表它，起到映射的作用。注意，修改操作中出想过的修改值也要包含在内，因为主席树不可能临时在某一棵书上多开一个点。

如此建立以后，主席树就有了一个优良的性质：树与树间可以直接相减，那么区间第k大问题就可以通过右端点减去左端点的前一个根节点下的树来代表区间内所有出现过的数字，同时由于映射值已排序，所以直接二分查找即可。

那么现在来考虑如何实现动态区间第k大。在原来的主席树上直接修改未尝不可，但经实测常数、内存皆十分爆炸，而且我们又有下一个目标：可持久化，所以我们运用树状数组的思想，将原数据保存在静态主席树中，而修改在另一棵主席树中修改，并像树状数组一样每次将所有管制当前节点的点都修改一下。查询时因为静态主席树已保存了前缀和，所以我们只需要再求一下树状数组中更改的前缀和，再将两个值相加即为所求区间。

下面是代码实现，特地封了两个namespace方便阅读。

  
  

        
    
```cpp
    #include<cstdio>
    #include<cctype>
    #include<iomanip>
    #include<algorithm>
    #include<cmath>
    #include<cstdlib>
    #include<cstring>
    #define lowbit(a) a&(-a)//直接定义到这里貌似会更快 
    #define W while
    #define R register
    #define IN inline 
    #define gc getchar()
    #define MAX 20005
    IN void in(int &x)//快读 
    {
        x=0;R char c=gc;
        W(!isdigit(c))c=gc;
        W(isdigit(c)){x*=10;x+=c-48;c=gc;}
    }
    namespace President_Tree//主席树部分 
    {
        int cnt,siz,dot,idx;
        //分别代表内存分配的下标，不同数值点的个数，总共的点数，修改操作的下标 
        struct order//因为主席树必须离线，所以将指令存下来 
        {
            bool typ;//是查询还是修改 
            int from,to,k;
        }command[MAX];
        struct node
        {int son[2],sum;}tree[MAX*250];
        //内存一定要开的足够大，因为在这里静态主席树和树状数组共用这个数组内的点 
        int root[MAX],cpy[MAX],data[MAX];
        //分别保存静态主席树的根节点，离散化后的数据，原始数据 
        int build(int lef,int rig)//建立空树，和线段树差不多 
        {
            int now=cnt++;
            tree[cnt].sum=0;
            if(lef!=rig)
            {
                int mid=(lef+rig)>>1;
                tree[now].son[0]=build(lef,mid);
                tree[now].son[1]=build(mid+1,rig);
            }
            return now;
        }
        int updata(int last,int pos,int val)//更新虚拟节点或者插入静态主席树的函数
        //为了方便删除，传入val代表修改的量 
        {
            int now=cnt++,tmp=now,mid;
            int lef=0,rig=siz-1;//因为是值域线段树，所以保存的是离散化后的对应的数的编号 
            tree[now].sum=tree[last].sum+val;
            W(lef<rig)//非递归降低常数 
            {
                mid=(lef+rig)>>1;
                if(pos<=mid)//待插入节点在左子树 
                {
                    tree[now].son[1]=tree[last].son[1];//那么当前节点的右子树节点和之前的那棵权值线段树共用节点 
                    tree[now].son[0]=cnt++;//向左新开一个节点 
                    now=tree[now].son[0];
                    last=tree[last].son[0];
                    rig=mid;
                }
                else//同上 
                {
                    tree[now].son[0]=tree[last].son[0];
                    tree[now].son[1]=cnt++;
                    now=tree[now].son[1];
                    last=tree[last].son[1];
                    lef=mid+1;
                }
                tree[now].sum=tree[last].sum+val;
            }
            return tmp;
        }
        IN int ID(int now)//返回某个数在离散化后的数组中的位置 
        {
            return std::lower_bound(cpy,cpy+siz,now)-cpy;
        }
    }
    namespace Bit_Tree//树状数组相关 
    {
        using namespace President_Tree;
        int vir[MAX],use[MAX];
        //分别为树状数组的节点，计算前缀和时向前走的节点 
        IN void add(int now,int pos,int val)
        //因为树状数组的方便的查前缀和的功能，我们把改变量每次修改在对应的节点中 
        {
            W(now<=dot)
            {
                vir[now]=updata(vir[now],pos,val);
                now+=lowbit(now);
            }
        }
        IN int getsum(int now)//查询当前点更改值的左子树的大小 
        {
            int ret=0;
            W(now>0)
            {
                ret+=tree[tree[use[now]].son[0]].sum;
                now-=lowbit(now);
            }
            return ret;
        }
        IN int query(int left,int right,int kth)
        {
            int left_root=root[left-1];//静态主席树的两个相减的根节点 
            int right_root=root[right];
            int lef=0,rig=siz-1;//查询时左右范围 
            for(R int i=left-1;i;i-=lowbit(i))use[i]=vir[i];//初始化更改值的查询路径 
            for(R int i=right;i;i-=lowbit(i))use[i]=vir[i];
            W(lef<rig)
            {
                int mid=(lef+rig)>>1;
                int now_sum=getsum(right)-getsum(left-1)+tree[tree[right_root].son[0]].sum-tree[tree[left_root].son[0]].sum;//查询当前点的左儿子是否满足达到了k个
                //在静态主席树和树状数组上一起算 
                if(now_sum>=kth)//达到了 
                {
                    rig=mid;
                    for(R int i=left-1;i;i-=lowbit(i))use[i]=tree[use[i]].son[0];//那么我们就将查询范围缩小至左子树内 
                    for(R int i=right;i;i-=lowbit(i))use[i]=tree[use[i]].son[0];
                    left_root=tree[left_root].son[0];//同时静态主席树也要如此 
                    right_root=tree[right_root].son[0];
                }
                else//没达到就在右子树内范围继续查找 
                {
                    lef=mid+1;
                    kth-=now_sum;//因为有了左子树的一部分点，所以要减去 
                    for(R int i=left-1;i;i-=lowbit(i))use[i]=tree[use[i]].son[1];
                    for(R int i=right;i;i-=lowbit(i))use[i]=tree[use[i]].son[1];
                    left_root=tree[left_root].son[1];
                    right_root=tree[right_root].son[1];
                }
            }
            return lef;//返回是第几个离散出来的数据 
        }
    }
    using namespace President_Tree;
    using namespace Bit_Tree;
    using std::sort;
    using std::unique;
    using std::printf;
    using std::scanf;
    int main()
    {
        int num;
        in(dot),in(num);
        idx=dot;
        for(R int i=1;i<=dot;++i)
        {
            in(data[i]);cpy[i-1]=data[i];//cpy从0开始存方便unique和sort 
        }
        char c[10];
        for(R int i=1;i<=num;++i)//将指令离线下来 
        {
            scanf("%s",c);
            if(c[0]=='Q')
            {
                command[i].typ=false;
                in(command[i].from);in(command[i].to);in(command[i].k);
            }
            else
            {
                command[i].typ=true;
                in(command[i].from);in(command[i].k);
                cpy[idx++]=command[i].k;//如果是修改的话存入cpy中 
            }
        }
        sort(cpy,cpy+idx);
        siz=unique(cpy,cpy+idx)-cpy;
        root[0]=build(0,siz-1);//建立空静态主席树 
        for(R int i=1;i<=dot;++i)
        root[i]=updata(root[i-1],ID(data[i]),1);//建立满的静态主席树 
        for(R int i=1;i<=dot;++i)
        vir[i]=root[0];//初始化树状数组 
        for(R int i=1;i<=num;++i)//处理指令 
        {
            if(!command[i].typ)
            {
                printf("%d\n",cpy[query(command[i].from,command[i].to,command[i].k)]);
            }
            else
            {
                add(command[i].from,ID(data[command[i].from]),-1);
                add(command[i].from,ID(command[i].k),1);
                data[command[i].from]=command[i].k;//要将原数据修改至新数据，否则翻车 
            }
        }
        return 0;
}
```

---

## 作者：Owen_codeisking (赞：19)

居然没有 $O(n\sqrt{n})$ 分块的题解？我来写一篇好了。

~~结果我发现分块开个O2比我的主席树套BIT还快~~

强化版：[[Ynoi2018]未来日记](https://www.luogu.org/problemnew/show/P4119)

~~Ynoi做多了啥都是分块~~

首先我们离线，将值域离散化，易知最多只有 $n+m$ 个不同的权值。

我们考虑将序列和值域都分块。$sum1[i][j]$ 表示序列前 $i$ 块值域第 $j$ 块的元素个数，$sum2[i][j]$ 表示序列前 $i$ 块权值为 $j$ 的元素个数。

设有 $tot$ 个不同的权值。由于我比较懒，所以序列的块长设为 $\sqrt{n}$，值域的块长设为 $\sqrt{tot}$，那么预处理的时间 $O(tot\sqrt{n})$

由于修改操作是单点修改，所以直接暴力遍历前缀和，时间 $O(\sqrt{n})$

询问操作则是步步逼近答案，类似在权值线段树上找第 $k$ 小，先找整块再找零散的部分。由于我们还要将序列中零散的部分加过来，所以时间 $O(\sqrt{n}+\sqrt{tot})$

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
const int maxblo=317;
int n,m,blo,a[maxn],mp[maxn<<1],tot,pos[maxn],bl[maxn<<1],L[maxn],R[maxn];
int v1[maxn<<1],v2[maxn<<1],sum1[450][450],sum2[320][maxn<<1];

inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

struct Query{
	int op,l,r,k;
}q[maxn];

inline void modify(int x,int y){
    for(int i=pos[x];i<=pos[n];i++){
    	sum1[i][bl[a[x]]]--;
    	sum1[i][bl[y]]++;
    	sum2[i][a[x]]--;
    	sum2[i][y]++;
	}
	a[x]=y;
}

inline int query(int l,int r,int k){
    if(pos[l]==pos[r]){
        for(int i=l;i<=r;i++) v1[i]=a[i];
        nth_element(v1+l,v1+l+k-1,v1+r+1);
        int ans=v1[l+k-1];
        for(int i=l;i<=r;i++) v1[i]=0;
        return ans;
    }
    for(int i=l;i<=R[pos[l]];i++) v1[bl[a[i]]]++,v2[a[i]]++;
    for(int i=L[pos[r]];i<=r;i++) v1[bl[a[i]]]++,v2[a[i]]++;
    for(int i=1;i<=bl[tot];i++){
        if(k>v1[i]+sum1[pos[r]-1][i]-sum1[pos[l]][i]) k-=v1[i]+sum1[pos[r]-1][i]-sum1[pos[l]][i];
        else {
            for(int j=(i-1)*blo+1;j<=i*blo;j++){
                if(k>v2[j]+sum2[pos[r]-1][j]-sum2[pos[l]][j]) k-=v2[j]+sum2[pos[r]-1][j]-sum2[pos[l]][j];
                else {
                    for(int x=l;x<=R[pos[l]];x++) v1[bl[a[x]]]--,v2[a[x]]--;
                    for(int x=L[pos[r]];x<=r;x++) v1[bl[a[x]]]--,v2[a[x]]--;
                    return j;
                }
            }
        }
    }
}

int main()
{
    n=read(),m=read();blo=sqrt(n)+1;
    for(int i=1;i<=n;i++) a[i]=mp[++tot]=read();
    char op;
    for(int i=1;i<=m;i++){
    	op=getchar();
    	while(op!='Q'&&op!='C') op=getchar();
    	q[i].op=(op=='Q')?1:2;
    	if(q[i].op==1) q[i].l=read(),q[i].r=read(),q[i].k=read();
		else q[i].l=read(),q[i].k=mp[++tot]=read();
	}
	sort(mp+1,mp+tot+1);
	tot=unique(mp+1,mp+tot+1)-mp-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(mp+1,mp+tot+1,a[i])-mp;
    for(int i=1;i<=n;i++){
        pos[i]=(i-1)/blo+1;
        if(pos[i]!=pos[i-1]) L[pos[i]]=i,R[pos[i-1]]=i-1;
    }
    R[pos[n]]=n;blo=sqrt(tot)+1;
    for(int i=1;i<=tot;i++) bl[i]=(i-1)/blo+1;
    for(int x=1;x<=pos[n];x++){
        for(int i=1;i<=bl[tot];i++) sum1[x][i]=sum1[x-1][i];
        for(int i=1;i<=tot;i++) sum2[x][i]=sum2[x-1][i];
        for(int i=L[x];i<=R[x];i++) sum1[x][bl[a[i]]]++,sum2[x][a[i]]++;
    }
    for(int i=1;i<=m;i++){
    	if(q[i].op==1) printf("%d\n",mp[query(q[i].l,q[i].r,q[i].k)]);
		else q[i].k=lower_bound(mp+1,mp+tot+1,q[i].k)-mp,modify(q[i].l,q[i].k);
	}
    return 0;
}
```

---

## 作者：MCAdam (赞：19)

先说静态的：[P1533 可怜的狗狗](https://www.luogu.com.cn/problem/P1533)

为了避免混淆，对于处理的询问区间（一堆询问）记为$[l,r]$，一个询问$p$查询的是$[v[p].left,v[p].right]$，值域的区间记为$[low,high]$

首先原序列记为$A$。对于答案区间为$[low,high]$，有以下操作：

1、将$A$序列中值在$[l,mid]$的在序列中的位置单点修改（树状数组）

2、对于每一个询问$p$

在树状数组中查询$t[p].right$和$t[p].left-1$的前缀和，$query(t[p].right)-query(t[p].left-1)$就是这个区间内小于等于$mid$的个数$cnt$。

如果当前询问$k[p]\leq cnt$，那就把这个询问归到$[low,mid]$的小问题中；如果$k[p]>cnt$，就让$k[p]-cnt \to k[p]$，然后把它分到$[mid+1,high]$这个小问题中（类似于$CDQ$的过程）

3、清空树状数组，递归到$[low,mid],[mid+1,high]$中

当问题规模$[low,high]$，$low=high$的时候，答案就是$low$

时间复杂度是$O(n\,log_2^2n)$，只有60 QWQ

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=3e5+10,M=5e4+10;
int n,m;
int val[N],tmp[N],turn[N],ans[M];
struct tree
{
	int rt[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	inline int query(int x)
	{
		int res=0;
		if(x==0) return 0;
		for(register int i=x;i>=1;i-=lowbit(i))
			res+=rt[i];
		return res;
	}
	inline void change(int x,int c)
	{
		for(register int i=x;i<=n;i+=lowbit(i))
			rt[i]+=c;
	}
}t;
struct query
{
	int left,right;
	int k,id;
}v[M],w[M];
inline void divide(int l,int r,int low,int high)
{
	if(low==high)
	{
		for(register int i=l;i<=r;i++)
			ans[v[i].id]=low;
		return;
	}
	int mid=(low+high)/2,p=l-1,q=r+1;
	for(register int i=1;i<=n;i++)
		if(val[i]>=low&&val[i]<=mid) t.change(i,1);
	for(register int i=l;i<=r;i++)
	{
		int cnt=t.query(v[i].right)-t.query(v[i].left-1);
		if(cnt>=v[i].k) w[++p]=v[i];
		else w[--q]=v[i],w[q].k-=cnt;
	}
	for(register int i=1;i<=n;i++)
		if(val[i]>=low&&val[i]<=mid) t.change(i,-1);
	for(register int i=l;i<=r;i++)
		v[i]=w[i];
	if(l<=p) divide(l,p,low,mid);
	if(r>=q) divide(q,r,mid+1,high);
}
inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9'){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
	return x*f;
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;i++)
	{
		val[i]=read();
		tmp[i]=val[i];
	}
	sort(tmp+1,tmp+n+1);
	int tot=unique(tmp+1,tmp+n+1)-(tmp+1);
	for(register int i=1;i<=n;i++)
	{
		int sub=lower_bound(tmp+1,tmp+tot+1,val[i])-tmp;
		turn[sub]=val[i],val[i]=sub;
	}
	for(register int i=1;i<=m;i++)
		v[i].left=read(),v[i].right=read(),v[i].k=read(),v[i].id=i;
	divide(1,m,1,tot);
	for(register int i=1;i<=m;i++)
		printf("%d\n",turn[ans[i]]);
	return 0;
}
```
既然整体二分跑那么慢，那有什么用呢？当然有辣，当支持修改的时候，就比如[P2617 Dynamic Rankings](https://www.luogu.com.cn/problem/P2617)

当然你可以选择写树套树，但整体二分效率差不多，又好写，为什么要写毒瘤的树套树呢？

现在，支持更改一个数。我们把这个操作拆成两个：在$x$处删去$a_x$在$x$处插入$y$。对于一个非查询操作，如果它修改的值（不考虑正负）大于$mid$，即使它是排在左半部分的查询前面，也不会对查询造成影响，可以直接扔到右边。同理，如果它小于等于$mid$，那么可以提前把贡献算好，扔到左边就行了。

注意:

1、按照上一题的写法，两个指针一个从头，一个从尾部开始，但这里因为有顺序的影响，所以右半部分还有把它反过来（因为本来存进去时就是反的）。一开始的$n$个数可以直接当做插入就行了。

2、修改操作，要把原数组也改了

3、这题整体二分不用开$O_2$是可以过得，如果超时了，有可能是数组开小了

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=2e5+10;
int n,m;
int val[N],tmp[N],turn[N],ans[N];//tmp是离散化用的，turn是映射回原来的数字 
struct tree//树状数组 
{
	int rt[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	inline int query(int x)
	{
		int res=0;
		if(x==0) return 0;
		for(register int i=x;i>=1;i-=lowbit(i))
			res+=rt[i];
		return res;
	}
	inline void change(int x,int c)
	{
		for(register int i=x;i<=n;i+=lowbit(i))
			rt[i]+=c;
	}
}t;
struct opt
{
	int type,k;//0 查询 1 插入 -1 删除   查询时是第k大，修改时是权值 
	int left,right;//查询的区间
	int pos;//pos是查询时的编号或者修改的位置；
}v[2*N],w[2*N];
inline void rev(int l,int r)//反转 
{
	if(l>r) return;
	for(register int i=l;i<=(l+r)/2;i++)
		swap(w[i],w[r-i+l]);
}
inline void divide(int l,int r,int low,int high)
{
	if(low==high)//到底了，直接更新答案 
	{
		for(register int i=l;i<=r;i++)
			if(!v[i].type) ans[v[i].pos]=low;
		return;
	}
	int mid=(low+high)/2,p=l-1,q=r+1;
	for(register int i=l;i<=r;i++)
	{
		if(v[i].type)
		{
			if(v[i].k<=mid) t.change(v[i].pos,v[i].type),w[++p]=v[i];//如果权值小于等于mid，直接扔到左边 
			else w[--q]=v[i];
		}
		else
		{
			int cnt=t.query(v[i].right)-t.query(v[i].left-1);
			if(cnt>=v[i].k) w[++p]=v[i];
			else w[--q]=v[i],w[q].k-=cnt;//注意这里要减去cnt 
		}
	}
	for(register int i=l;i<=r;i++)
		if(v[i].type&&v[i].k<=mid) t.change(v[i].pos,-v[i].type);//树状数组清空 
	rev(q,r);//反转 
	for(register int i=l;i<=r;i++)//覆盖 
		v[i]=w[i];
	if(l<=p) divide(l,p,low,mid);//分治下去 
	if(r>=q) divide(q,r,mid+1,high);
}
inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9'){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
	return x*f;
}
int main()
{
	char ch[2];
	int tot=0,cnt=0,a,b,c;
	n=read(),m=read();
	for(register int i=1;i<=n;i++)
	{
		val[i]=read();
		tmp[++tot]=val[i];
		v[++cnt]=(opt){1,val[i],0,0,i};//一开始都是插入 
	}
	for(register int i=1;i<=m;i++)
	{
		scanf("%s",&ch);
		if(ch[0]=='Q')
		{
			a=read(),b=read(),c=read();
			v[++cnt]=(opt){0,c,a,b,i};//询问 
		}
		else
		{
			a=read(),b=read();
			v[++cnt]=(opt){-1,val[a],0,0,a};//删除原有的 
			v[++cnt]=(opt){1,b,0,0,a};//插入新的 
			tmp[++tot]=b;
			val[a]=b;//！！！！！记得修改 
		}
	}
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-(tmp+1);
	for(register int i=1;i<=cnt;i++)
	{
		if(!v[i].type) continue;
		int sub=lower_bound(tmp+1,tmp+tot+1,v[i].k)-tmp;//离散化 
		turn[sub]=v[i].k,v[i].k=sub;
	}
	divide(1,cnt,1,tot);//整体二分 
	for(register int i=1;i<=m;i++)
		if(ans[i]) printf("%d\n",turn[ans[i]]);
	return 0;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/c5knhgmo.png)

这是整体二分和树套树的对比（可能我写的比较丑，dalao勿喷），发现整体二分还是很快的。待修改的整体二分和没修改的其实就加了一点东西，但如果是主席树的话，就套多了一个树状数组（树状数组：没事套我干嘛？？？）。整体二分还是很棒的辣。

---

## 作者：Isonan (赞：17)

原题传送门[>Here<](https://www.luogu.org/problemnew/show/P2617)

~~虽然题面上说用树套树可以过，但是我不论怎样都没有卡进。。可能是因为我太菜吧~~

动态区间第K小模板题。

（打主席树是不可能的，这辈子都不可能的，树套树又要T飞，只能靠整体二分维持生计这样子）

要点：

1.把一个修改操作改成一个删除和一个添加；

2.用memset0的，可以获得50分的好成绩。

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

struct point{
	int opt,l,r,k,orig,add;
}queue[400001],tem1[400001],tem2[400001];
int c[200001],a[100001],n,m,all[200001],top,lim,ans[200001],l,r,k,proc,last[200001],change[400001][2],t;
bool isquery[200001],cnt[200001];
char opt;
void update(int ind,int num){for(;ind<=lim;ind+=ind&-ind)c[ind]+=num; }
int query(int ind){int tot=0;for(;ind;ind-=ind&-ind)tot+=c[ind];return tot;}
void binary(int l,int r,int el,int er){
	if(l>r)return;
	if(el==er){
		for(int i=l;i<=r;i++)ans[queue[i].orig]=all[el];
		return;
	}
	int mid=(el+er)>>1,i=0,j=0;
	for(int K=l;K<=r;K++){
		if(queue[K].opt==1){
			if(queue[K].k<=mid){
				update(queue[K].l,queue[K].add);
				change[++t][0]=queue[K].l,change[t][1]=queue[K].add;
				tem1[++i]=queue[K];
			}
			else{
				tem2[++j]=queue[K];
			}
		}
		else{
			int tem=query(queue[K].r)-query(queue[K].l-1);
			if(tem>=queue[K].k){
				tem1[++i]=queue[K];
			}
			else{
				queue[K].k-=tem;
				tem2[++j]=queue[K];
			}
		}
	}
	for(int K=1;K<=t;K++)update(change[K][0],-change[K][1]);
	t=0;
	for(int K=1;K<=i;K++)queue[K+l-1]=tem1[K];
	for(int K=1;K<=j;K++)queue[K+l+i-1]=tem2[K];
	binary(l,l+i-1,el,mid);
	binary(l+i,r,mid+1,er);
}
void get(){
	opt=getchar();
	while(opt!='C'&&opt!='Q')opt=getchar();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",all+i);
		queue[i]=(point){1,i,0,all[i],0,1};
		last[i]=all[i];
	}
	top=proc=n;
	for(int i=1;i<=m;i++){
		get();
		isquery[i]=opt=='Q';
		if(opt=='C'){
			scanf("%d%d",&l,&k);
			queue[++proc]=(point){1,l,0,last[l],i,-1};
			queue[++proc]=(point){1,l,0,k,i,1};
			all[++top]=k;
			last[l]=k;
		}
		else{
			scanf("%d%d%d",&l,&r,&k);
			queue[++proc]=(point){2,l,r,k,i};
		}
	}
	std::sort(all+1,all+top+1);
	lim=std::unique(all+1,all+top+1)-all-1;
	for(int i=1;i<=proc;i++)if(queue[i].opt==1)queue[i].k=std::lower_bound(all+1,all+lim+1,queue[i].k)-all;
	binary(1,proc,1,lim);
	for(int i=1;i<=m;i++)if(isquery[i])printf("%d\n",ans[i]);
}
```

---

## 作者：Ireliaღ (赞：15)

**看下面都是树状数组+主席树，我来一个树状数组+01Trie**

## 为什么用01Trie（可以不看）

显然，我们需要用一个区间树套一个值域树来做到$\Theta(\log ^ 2(n))$操作。而这个值域树只需要满足**可减性**即可，也就是说，用两个前缀值域树相同地位的节点的`size`相减，得到的就是这段区间的“值域树”的该节点`size` 

所以，由于平衡树每次操作形态改变较大，我们不能使用，只能用值域线段树和01Trie来代替。01Trie的编码难度更加简单，并且可以实现最大异或和等其他操作，所以本人更加推荐

## 实现方法

既然是动态操作，那么修改时我们将树状数组上对应的$\log$个树全部删除原数并加入新数，查询时用$R$在树状数组上对应的$\log$个树的节点的`size`和减去$L - 1$在树状数组上对应的$\log$个树的节点的`size`和，得到的就是这个区间的信息，和要求的$kth$比较，全部进入左/右子树即可

## 程序实现

需要吸氧

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
const int MAXN = 2e5 + 5;

struct Node{
	int siz;
	Node *ch[2];
	
	Node() {}
}npool[50000000];

int n, m;
int a[MAXN];
int ncnt;
Node *rt[MAXN];
Node *cur1[MAXN], *cur2[MAXN];
int tot1, tot2;

int LB(int x) {return x & -x;}

void Insert(Node *&now, int bit, int k) {
	if (!now) now = &npool[ncnt++];
	now->siz++;
	if (bit == 0) return;
	int f = (k & (1 << (bit - 1))) ? 1 : 0;
	Insert(now->ch[f], bit - 1, k);
}

void Remove(Node *now, int bit, int k) {
	if (!now) return;
	now->siz--;
	if (bit == 0) return;
	int f = (k & (1 << (bit - 1))) ? 1 : 0;
	Remove(now->ch[f], bit - 1, k);
}

int Query(int k, int bit, int res) {
	if (bit == 0) return res;
	int ls = 0;
	for (int i = 1; i <= tot1; i++) ls -= ((cur1[i] && cur1[i]->ch[0]) ? cur1[i]->ch[0]->siz : 0);
	for (int i = 1; i <= tot2; i++) ls += ((cur2[i] && cur2[i]->ch[0]) ? cur2[i]->ch[0]->siz : 0);
	if (k <= ls) {
		for (int i = 1; i <= tot1; i++) {
			if (cur1[i]) cur1[i] = cur1[i]->ch[0];
		}
		for (int i = 1; i <= tot2; i++) {
			if (cur2[i]) cur2[i] = cur2[i]->ch[0];
		}
		return Query(k, bit - 1, res);
	} else {
		for (int i = 1; i <= tot1; i++) {
			if (cur1[i]) cur1[i] = cur1[i]->ch[1];
		}
		for (int i = 1; i <= tot2; i++) {
			if (cur2[i]) cur2[i] = cur2[i]->ch[1];
		}
		res |= (1 << (bit - 1));
		k -= ls;
		return Query(k, bit - 1, res);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		for (int j = i; j <= n; j += LB(j)) Insert(rt[j], 30, a[i]);
	}
	char op[2];
	int x, y, z, res;
	for (int i = 1; i <= m; i++) {
		cin >> op;
		if (op[0] == 'Q') {
			cin >> x >> y >> z;
			tot1 = 0;
			for (int j = x - 1; j >= 1; j -= LB(j)) cur1[++tot1] = rt[j];
			tot2 = 0;
			for (int j = y; j >= 1; j -= LB(j)) cur2[++tot2] = rt[j];
			res = Query(z, 30, 0);
			cout << res << "\n";
		} else {
			cin >> x >> y;
			for (int j = x; j <= n; j += LB(j)) Remove(rt[j], 30, a[x]);
			a[x] = y;
			for (int j = x; j <= n; j += LB(j)) Insert(rt[j], 30, a[x]);
		}
	}
	return 0;
}
```

---

## 作者：skydogli (赞：15)

### 带修改主席树（主席树套树状数组）
这题还是有点烦人的，主要是离散化后思路会比较乱，其他都还好。

#### 看这篇题解之前，请先刷通：

##### [1、树状数组](https://www.luogu.org/problemnew/show/P3374)

##### [2、普通线段树](https://www.luogu.org/problemnew/show/P3372)

##### [3、离散化&静态主席树](https://www.luogu.org/problemnew/show/P3834)

注意，离散化虽然看起来不难，但是更加需要深刻理解，编程时要非常清晰地知道每一个变量代表的是数值还是排名，不然就~~会像我一样调一整个晚上~~可能出错。

#### 解题思路

首先我们已经知道静态的主席树之所以可以查询区间第K大，就是因为主席树记录了所有的历史版本（相当于前缀和），利用差分的思想取出l～r的区间，从而利用权值线段树的特性查询第K大。

而这个方法运用到带修改的题目中就十分尴尬了，因为我们知道前缀和的修改是需要O(n)的，于是我们的主席树就变成了常数码量都很大的暴力算法（逃）

但是我们有更加高效的维护单点修改、区间查询的前缀和的数据结构，例如~~分块大法吼啊~~线段树、树状数组等，线段树我没试过，但是码量、常数、直观程度（需要递归）都是不如树状数组的，于是我们大多数时候都会选择后者。

于是，我们用树状数组的思想，每次改变log个根，就可以达到（log^2)的修改复杂度了，而查询也需要查询log个根，复杂度也是O（log^n)。总时间复杂度O(Nlog^2(N)),空间复杂度O(Nlog^2(N))（于是题目愉快地给出了1024M:)

#### 代码&注释（常数略大，开O2跑了7200ms，仅作参考）

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
#define MN 200005
#define Ls Tree[x].lson
#define Rs Tree[x].rson
struct tree{
    int lson,rson,sum;
}Tree[MN*100];//主席树基本配置：左子树编号、右子树编号、区间中数的数量
inline int read(){
    int a=0;
    char c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while('0'<=c&&c<='9'){a=(a<<3)+(a<<1)+c-48;c=getchar();}
    return a;
}
inline int getc(){
    char c=getchar();
    while(c!='Q'&&c!='C') c=getchar();
    return c;
}
//int和char的快读(第二种应该没什么用)
inline int lowbit(int x){
    return (x&(-x));
}//lowbit操作
int root[MN],n,m,cnt,v[MN],a[MN],L,R,x[MN],y[MN],k[MN],now[MN],past[MN],N;
//root：根 cnt：点的总数 a：输入的数，后变为离散化后的排名
//x,y，k:询问的左右端点、排名，或x为替换的编号，y为替换的值
//past、now：用于从0到左右端点的求和（树状数组）
char c[MN];//Q还是C
void Discrete(){//离散化
    sort(v+1,v+1+N);
    N=unique(v+1,v+1+N)-v;//离散化后的数量
    for(int i=1;i<=n;i++){
        int l=1,r=N;
        while(l+1<r){
            if(v[mid]<=a[i]) l=mid;
                else r=mid;
        }
        a[i]=l;
    }
    for(int i=1;i<=m;i++)//注意y也要离散化
        if(c[i]=='C'){
            int l=1,r=N;
            while(l+1<r)
                if(v[mid]<=y[i]) l=mid;
                    else r=mid;
            y[i]=l;
        }
}
void change(int num,int &x,int l,int r,int ad){
    if(!x) x=++cnt;
    Tree[x].sum+=ad;
    if(l==r)return;
    if(num<=mid) change(num,Ls,l,mid,ad);
        else change(num,Rs,mid+1,r,ad);
}//正常主席树的插入
int kth(int l,int r,int k){
    if(l==r) return l;
    int sum=0;
    for(int i=1;i<=L;i++) sum-=Tree[Tree[past[i]].lson].sum;
    for(int i=1;i<=R;i++) sum+=Tree[Tree[now[i]].lson].sum;
    //算出左区间的数的数量
    if(sum>=k){
        for(int i=1;i<=R;i++)now[i]=Tree[now[i]].lson;
        for(int i=1;i<=L;i++)past[i]=Tree[past[i]].lson;
        return kth(l,mid,k);
        //如果第K名在左区间，就向左找
    }
    for(int i=1;i<=R;i++)now[i]=Tree[now[i]].rson;
    for(int i=1;i<=L;i++)past[i]=Tree[past[i]].rson;
    return kth(mid+1,r,k-sum);
    //否则在右区间找
}
int main(){
    n=read();m=read();
    cnt=1;
    for(int i=1;i<=n;i++) 
        a[i]=read(),v[i]=a[i];
    N=n;
    for(int i=1;i<=m;i++){
        c[i]=getc();
        if(c[i]=='Q'){x[i]=read();y[i]=read();k[i]=read();}
            else{x[i]=read();y[i]=read();v[++N]=y[i];}
    }
    //因为y可能与之前的a不同，所以要先输入所有问题，记录y的值
    Discrete();
    for(int i=1;i<=n;i++)
        for(int x=i;x<=n;x+=lowbit(x))
            change(a[i],root[x],1,N-1,1);
        //树状数组的原理，log个根都改变
    for(int i=1;i<=m;i++)
        if(c[i]=='Q'){
            L=R=0;
            for(int j=x[i]-1;j>0;j-=lowbit(j)) past[++L]=root[j];
            for(int j=y[i];j>0;j-=lowbit(j)) now[++R]=root[j];
            //记录各个需要参与树状数组运算的根节点
            printf("%d\n",v[kth(1,N-1,k[i])]);
            //注意！这里要输出原值，范围按离散化后的范围
        }
        else{
            for(int j=x[i];j<=n;j+=lowbit(j)) change(a[x[i]],root[j],1,N-1,-1);//注意！这里是排名！
            for(int j=x[i];j<=n;j+=lowbit(j)) change(y[i],root[j],1,N-1,1);
            //范围同样是按照离散化后的范围
            a[x[i]]=y[i];
        }
    return 0;
}


```


---

## 作者：zymooll (赞：11)

## 前言

大家好，我不会树状数组和离散化，所以我用线段树套权值线段树过了这道题。

## 做法

外层线段树的每个点维护一个区间，该区间用权值线段树维护。

对于每次修改，从外层树的根节点递归到叶子节点，顺带修改遍历到的点所维护的权值线段树。

对于每次查询，先预处理出查询区间所包含的外层树的节点，最后线段树二分时，将所有点权值贡献加和，根据情况将所有点向左或向右跳。

注意直接做会爆空间，需要在修改操作时候注意将大小为 0 的点进行回收利用。

参考时间复杂度：$O((n+m)\log n \log w)$。

## 参考代码

```cpp
// Author:zymooll

#include<bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
// #define int long long
using namespace std;
int read(){
  int s = 0, w = 1;
  char c = getchar();
  while(c < '0' || c > '9'){
    if(c == '-')w = -1;
    c = getchar();
  }
  while(c >= '0' && c <= '9'){
    s = s * 10 + c - '0';
    c = getchar();
  }
  return s * w;
}
void print(int x){
  if(x < 0){
    putchar('-');
    x = -x;
  }
  if(x >= 10)print(x / 10);
  putchar(x % 10 + '0');
  return;
}
char getcharS(){
  char ch = getchar();
  while(ch == '\n' || ch == '\r' || ch == ' ')ch = getchar();
  return ch;
}
const int NMax = 1e5;
const int KMax = 17;
int n, m;
int a[NMax + 10];
struct SegmentTree1{
  struct Node{
    int n, l, r;
  }t[2 * NMax + 10];
  struct SegmentTree2{
    struct Node{
      int n, l, r;
    }t[800 * NMax + 10];
    int ncnt;
    int root[KMax * NMax + 10];
    vector<int>pp;
    vector<int>gc;
    int newnode(){
      if(gc.empty())return ++ncnt;
      else{
        int p = (*(gc.end() - 1));
        gc.pop_back();
        t[p].n = t[p].l = t[p].r = 0;
        return p;
      }
    }
    void modify(int& p, int L, int R, int x, int k){
      if(!p)p = newnode();
      t[p].n += k;
      if(L == R)return;
      int mid = (L + R) / 2;
      if(x <= mid)modify(t[p].l, L, mid, x, k);
      else modify(t[p].r, mid + 1, R, x, k);
      if(t[p].l && !t[t[p].l].n){ gc.push_back(t[p].l), t[p].l = 0; }
      if(t[p].r && !t[t[p].r].n){ gc.push_back(t[p].r), t[p].r = 0; }
    }
    int ask(int L, int R, int k){
      if(L == R)return L;
      int pl = 0;
      for(int p : pp)pl += t[t[p].l].n;
      int mid = (L + R) / 2;
      if(k <= pl){
        for(int& p : pp)p = t[p].l;
        return ask(L, mid, k);
      }
      else{
        for(int& p : pp)p = t[p].r;
        return ask(mid + 1, R, k - pl);
      }
    }
  }T;
  int ncnt;
  int init(int L, int R){
    int p = ++ncnt;
    for(int i = L; i <= R; i++){
      T.modify(T.root[p], 0, 1e9, a[i], 1);
    }
    if(L == R)return p;
    int mid = (L + R) / 2;
    t[p].l = init(L, mid);
    t[p].r = init(mid + 1, R);
    return p;
  }
  void modify(int p, int L, int R, int x, int k){
    T.modify(T.root[p], 0, 1e9, a[x], -1);
    T.modify(T.root[p], 0, 1e9, k, 1);
    if(L == R)return;
    int mid = (L + R) / 2;
    if(x <= mid)modify(t[p].l, L, mid, x, k);
    else modify(t[p].r, mid + 1, R, x, k);
  }
  void getid(int p, int L, int R, int l, int r){
    if(l <= L && R <= r){
      T.pp.push_back(T.root[p]); return;
    }
    int mid = (L + R) / 2;
    if(l <= mid)getid(t[p].l, L, mid, l, r);
    if(r > mid)getid(t[p].r, mid + 1, R, l, r);
  }
  int ask(int l, int r, int k){
    T.pp.clear(); getid(1, 1, n, l, r);
    return T.ask(0, 1e9, k);
  }
}T;
signed main(){
  //freopen(".in","r",stdin);
  //freopen(".out","w",stdout);
  n = read(), m = read();
  for(int i = 1; i <= n; i++){
    a[i] = read();
  }
  T.init(1, n);
  while(m--){
    char opt = getcharS();
    if(opt == 'Q'){
      int l = read(), r = read(), k = read();
      print(T.ask(l, r, k)); putchar('\n');
    }
    else{
      int x = read(), y = read();
      T.modify(1, 1, n, x, y); a[x] = y;
    }
  }
  return 0;
}

```

感谢阅读！

---

## 作者：Aegir (赞：10)

### 真·在线做法：

几乎所有使用带修改主席树做法的代码都是读入所有询问之后进行离散化。

但如果这题是强制在线呢？那我们就无法读入所有数据进行离散化了。

我们使用动态开点的技巧，只有在用到这个点的时候才给这个点分配空间，

这样每次修改至多建立$log$(值域)个点。

当然时空复杂度都会高上不少，因为$log(n)$变成了$log(1e9)$（值域）

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int Read()
{
    int x = 0, f = 1; char s = getchar();
    for(; !isdigit(s); s = getchar()) if(s == '-') f = -1;
    for(; isdigit(s); s = getchar()) x = x * 10 + s - 48;
    return x * f;
}

inline void Print(int x)
{
    if(x > 9) Print(x / 10);
    putchar(x % 10 + 48);
}

#define lowbit(x) (x & (-x))
const int MAXN = 100010;

struct Node
{
    int ls, rs, cnt;
}node[MAXN * 800];
int cnt, root[MAXN];

int n, m, cntx, cnty;
int a[MAXN], cx[20], cy[20];

inline void modify(int &o, int l, int r, int pos, int val)
{
    if(!o) o = ++cnt;
    node[o].cnt += val;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) modify(node[o].ls, l, mid, pos, val);
    else modify(node[o].rs, mid + 1, r, pos, val);
}

inline void update(int pos, int val, int x)
{
    for(register int i = pos; i <= n; i += lowbit(i))
        modify(root[i], 0, 1e9, x, val);
}

inline int query(int l, int r, int k)
{
    if(l == r) return l;
    int mid = (l + r) >> 1, sum = 0;
    for(register int i = 1; i <= cntx; ++i) sum += node[node[cx[i]].ls].cnt;
    for(register int i = 1; i <= cnty; ++i) sum -= node[node[cy[i]].ls].cnt;
    if(k <= sum)
    {
        for(register int i = 1; i <= cntx; ++i) cx[i] = node[cx[i]].ls;
        for(register int i = 1; i <= cnty; ++i) cy[i] = node[cy[i]].ls;
        return query(l, mid, k);
    }
    else
    {
        for(register int i = 1; i <= cntx; ++i) cx[i] = node[cx[i]].rs;
        for(register int i = 1; i <= cnty; ++i) cy[i] = node[cy[i]].rs;
        return query(mid + 1, r, k - sum);
    }
}

int main()
{
    char op[5]; int l, r, k;
    n = Read(), m = Read();
    for(register int i = 1; i <= n; ++i)
    {
        a[i] = Read();
        update(i, 1, a[i]);
    }
    while(m--)
    {
        scanf("%s", op);
        if(op[0] == 'Q')
        {
            l = Read(), r = Read(), k = Read();
            cntx = cnty = 0;
            for(register int i = r; i; i -= lowbit(i)) cx[++cntx] = root[i];
            for(register int i = l - 1; i; i -= lowbit(i)) cy[++cnty] = root[i];
            Print(query(0, 1e9, k)), putchar('\n');	
        }
        else
        {
            l = Read(), k = Read();
            update(l, -1, a[l]);
            update(l, 1, k);
            a[l] = k;
        }
    }
    return 0;
}
```


---

## 作者：Leasier (赞：7)

前置芝士：[带修莫队](https://oi-wiki.org/misc/modifiable-mo-algo/)、[分块](https://oi-wiki.org/ds/decompose/)

~~不想打树套树的蒟蒻就只能靠带修莫队和值域分块维持生计了 /kk~~

看到区间查询，就想到了莫队；看到修改操作，就想到了带修莫队；发现这道题不强制在线，又看到数据范围 $1 \leq n, m \leq 10^5$，就肯定可以用带修莫队~~水过去~~。

每次指针移动时将当前数的出现次数和其所在块 $\pm 1$，查询时将题目中出现的 $a_i$ 和 $y$ 离散化后二分 + 分块查询。

当块长取 $\frac{n}{\sqrt[3]{m}}$，时间复杂度为 $O(nm^{\frac{2}{3}} + m \sqrt{n + m} \log (n + m))$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef struct {
	int pos;
	int val;
} Modification;

typedef struct {
	int id;
	int l;
	int r;
	int time;
	int k;
} Query;

int block1;
int a[100007], b[200007], belong[200007], lft[457], rt[457], cnt[200007], sum[457], ans[100007];
Modification modification[100007];
Query query[100007];

bool operator <(const Query a, const Query b){
	if (a.l / block1 != b.l / block1) return a.l < b.l;
	if (a.r / block1 != b.r / block1) return a.r < b.r;
	return a.time < b.time;
}

inline void add(int x){
	cnt[x]++;
	sum[belong[x]]++;
}

inline void del(int x){
	cnt[x]--;
	sum[belong[x]]--;
}

inline void modify(int x, int time){
	if (query[x].l <= modification[time].pos && modification[time].pos <= query[x].r){
		del(a[modification[time].pos]);
		add(modification[time].val);
	}
	swap(a[modification[time].pos], modification[time].val);
}

inline int brute_force_get_sum(int l, int r){
	int ans = 0;
	for (register int i = l; i <= r; i++){
		ans += cnt[i];
	}
	return ans;
}

inline int get_sum(int l, int r){
	int ans = brute_force_get_sum(l, min(r, rt[belong[l]]));
	if (belong[l] != belong[r]) ans += brute_force_get_sum(lft[belong[r]], r);
	for (register int i = belong[l] + 1; i < belong[r]; i++){
		ans += sum[i];
	}
	return ans;
}

inline int get_kth_number(int k, int n){
	int l = 1, r = n, ans;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (get_sum(1, mid) >= k){
			r = mid - 1;
			ans = mid;
		} else {
			l = mid + 1;
		}
	}
	return ans;
}

int main(){
	int n, m, block2, modification_cnt = 0, val_cnt, k, query_cnt = 0;
	cin >> n >> m;
	val_cnt = n;
	for (register int i = 1; i <= n; i++){
		cin >> a[i];
		b[i] = a[i];
	}
	for (register int i = 1; i <= m; i++){
		char ch;
		cin >> ch;
		if (ch == 'C'){
			modification_cnt++;
			cin >> modification[modification_cnt].pos >> modification[modification_cnt].val;
			b[++val_cnt] = modification[modification_cnt].val;
		} else {
			query_cnt++;
			cin >> query[query_cnt].l >> query[query_cnt].r >> query[query_cnt].k;
			query[query_cnt].id = query_cnt;
			query[query_cnt].time = modification_cnt;
		}
	}
	block1 = ceil(n / cbrt(query_cnt));
	sort(b + 1, b + val_cnt + 1);
	val_cnt = unique(b + 1, b + val_cnt + 1) - b - 1;
	block2 = sqrt(val_cnt);
	k = (val_cnt - 1) / block2 + 1;
	for (register int i = 1; i <= n; i++){
		a[i] = lower_bound(b + 1, b + val_cnt + 1, a[i]) - b;
	}
	for (register int i = 1; i <= modification_cnt; i++){
		modification[i].val = lower_bound(b + 1, b + val_cnt + 1, modification[i].val) - b;
	}
	for (register int i = 1; i <= val_cnt; i++){
		belong[i] = (i - 1) / block2 + 1;
	}
	for (register int i = 1; i <= k; i++){
		lft[i] = (i - 1) * block2 + 1;
		rt[i] = min(i * block2, val_cnt);
	}
	sort(query + 1, query + query_cnt + 1);
	for (register int i = 1, j = 1, x = 0, y = 0; i <= query_cnt; i++){
		while (j > query[i].l) add(a[--j]);
		while (x < query[i].r) add(a[++x]);
		while (j < query[i].l) del(a[j++]);
		while (x > query[i].r) del(a[x--]);
		while (y < query[i].time) modify(i, ++y);
		while (y > query[i].time) modify(i, y--);
		ans[query[i].id] = b[get_kth_number(query[i].k, val_cnt)];
	}
	for (register int i = 1; i <= query_cnt; i++){
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：Genius_Z (赞：7)

这是本蒟蒻写的第一篇题解，如有不足请见谅。

这题的思路可以由P3834的莫队的思路延伸出来，变成带修莫队就可以了。

但由于加强数据后传统的sqrt(n)的分块最后面10个点跑不过去，本蒟蒻就玄学调了一下块的大小，不成想吸口氧竟然A了。

注释详见代码

```cpp
// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
#include<set>
#include<bitset>
#define inl inline
#define re register int
using namespace std;
template <class Read>
inl Read read() {
    Read x = 0;
    bool w = 0;
    char c = getchar();
    while (c > '9' || c < '0') {
        if (c == '-')w = 1;
        c = getchar();
    }
    while (c >= '0'&&c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return w ? -x : x;//快读
}
int n, m, num;
int s[200001], cnt[200001], a[200001], b[200001], mp[200001], sum[200001], ans[200001];
//s:每个数所属的块，cnt:对值域分块后那个值的数的个数，sum:每个块的数的个数和，mp:原数据，离散化后起映射作用,a:离散化后数据,b:离散化所用数组;
struct modify {
    int pos, id;
}c[200001];
struct quiz {
    int l, r, rank, k, id;
    bool operator <(const quiz &poi)const {
        if (s[l] ^ s[poi.l])return s[l] < s[poi.l];
        if (s[r] ^ s[poi.r])return s[r] < s[poi.r];
        return k < poi.k;
        //带修莫队正常排序
    }
}q[200001];
inl void add(int x) {
    cnt[x]++, sum[s[x]]++;
}
inl void del(int x) {
    cnt[x]--, sum[s[x]]--;
}
inl void change(int x, int i) {
    if (c[x].pos >= q[i].l&&c[x].pos <= q[i].r) {
        cnt[a[c[x].pos]]--, cnt[a[c[x].id + n]]++, sum[s[a[c[x].pos]]]--, sum[s[a[c[x].id + n]]]++;
    }
    swap(a[c[x].id + n], a[c[x].pos]);
}
signed main() {
    n = read<int>(), m = read<int>(), num = pow(n,2.0/3);//玄学调块的大小;
    for (re i = 1; i <= n; i++)a[i] = b[i] = read<int>(), s[i] = (i - 1) / num + 1;
    char cc[2];
    re qnum = 0, cnum = 0;
    for (re i = 1; i <= m; i++) {
        scanf("%s", cc);
        if (cc[0] == 'Q') {
            q[++qnum].l = read<int>(), q[qnum].r = read<int>(), q[qnum].k = cnum, q[qnum].rank = read<int>(), q[qnum].id = qnum;
        }
        else {
            re cn = n + (++cnum);
            c[cnum].pos = read<int>(), a[cn] = b[cn] = read<int>(), s[cn] = (cn - 1) / num + 1, c[cnum].id = cnum;
        }
    }//读入
    sort(b + 1, b + 1 + n + cnum);
    re k, l = 1, r = 0, res, now;
    re siz = unique(b + 1, b + 1 + n + cnum) - b;
    int cn = n + cnum;
    for (re i = 1; i <= cn; i++) {
        k = a[i];
        mp[a[i] = lower_bound(b + 1, b + siz, a[i]) - b] = k;
    }//离散化
    sort(q + 1, q + 1 + qnum);
    k = 0;
    for (re i = 1; i <= qnum; i++) {
        while (l > q[i].l)add(a[--l]);
        while (r < q[i].r)add(a[++r]);
        while (l < q[i].l)del(a[l++]);
        while (r > q[i].r)del(a[r--]);
        while (k < q[i].k)change(++k, i);
        while (k > q[i].k)change(k--, i);
        //带修莫队板子
        res = 0, now = 0;
        while (res + sum[now] < q[i].rank)res += sum[now++];//统计答案，由于对值域分块，当res>=询问的k大值时就找到了答案所在的块；
        for (re j = (now - 1) * num + 1;; j++) {
            if ((res += cnt[j]) >= q[i].rank) {
                ans[q[i].id] = mp[j];
                break;
                //暴力统计小块的答案;
            }
        }
    }
    for (re i = 1; i <= qnum; i++)printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Parabola (赞：7)

都是$O(log^3N)$的线段树套平衡树？

看到泥萌都是二分+区间rank诶...

作为解决区间动态Kth最基本解法，线段树套平衡树肯定不能这么弱

其实可以$O(log^2N)$的...

离散化序列$A$以及接下来要修改的数

然后$build$一棵可爱的权值线段树，

在没有区间这个限制时，我们在权值线段树上查询第k小是这样的

定义$cnt[o]$代表$o$所对应的值域

当你站在$o$时，观望左儿子$lc$与右儿子$rc$

如果$cnt[lc] > k$，那么最终答案一定在$lc$所对应的值域里

否则在$rc$所对的值域里，并且$k-=cnt[lc]$

那么现在有区间限制呢？

其实就是$cnt[o]$并不是所有都满足了，而是$cnt[o]$中下标在$l$与$r$之间的所有数

所以很自然想到将$cnt[o]$替换成一棵平衡树$BST[o]$

$BST[o]$存放落在$o$所对应的值域的数在数组$A$的下标

然后无脑$rank$

至于修改操作就比较简单了...

直接找到该删除的删除，该添加的添加

---

## 作者：泰勒斯威夫特 (赞：5)

>  [点击此处](https://www.cnblogs.com/TaylorSwift13/p/11228276.html)获得更多相关内容和更好的阅读体验

这道题~~第一次做的话有点难理解~~,所以本蒟蒻写了一篇**针对初学者**的详细的**树状数组套动态开点权值线段树**的题解.

## 1.前置知识(都学到树套树了怎么可能不会)

- 前缀和/树状数组[LG3374**【模板】树状数组 1**](https://www.luogu.org/problemnew/show/P3374)

- 普通线段树[LG3372**【模板】线段树 1**](https://www.luogu.org/problemnew/show/P3372)/权值线段树/动态开点线段树
- 主席树求静态区间K小值[LG3834**【模板】可持久化线段树 1（主席树）**](https://www.luogu.org/problemnew/show/P3834)

## 2.原理

#### 2.1从位置到值域

在用数据结构维护一个数列时,我们通常会看到两种维护方式:

##### 2.1.1维护方式$1$

**以位置为下标,值为内容**,比如最基础的线段树,当我们执行查询操作,比如查询[3,8],得到的是**"原数列中第3个数到第8个数"**的某些信息(和/最值)等.

##### 2.1.2维护方式$2$

**以值域为下标,值出现的次数为内容**,比如用树状数组求逆序对,如果查询[3,8],得到的结果是**值在[3,8]内的数的出现次数**.

我们把采用**维护方式$2$**的线段树叫做**权值线段树**,根据**线段树自带的"二分"属性**(每一个节点二分为左子节点和右子节点),我们可以用**权值线段树**来求解**动态全局$K$小值**的问题.(~~不知道怎么求?复习下权值线段树~~)

#### 2.2从前缀和到树状数组

##### 2.2.1问题$1$

首先来思考一个很简单的问题:给你一个数列,**不修改**,多次询问区间和,怎么做?

~~太简单了!前缀和搞一搞就可以了.~~

具体来说,开一个长度为$n$的数组(记为$a$),$a_i$维护第$1$个数字到第$i$个数字的和,那么要查询$[L,R]$这个区间的和,只需要用$a_R$减去$a_{L-1}$就可以了.

##### 2.2.2问题$2$

再来一个问题:给你一个数列,**不修改**,多次询问区间第K小值,怎么做?

没错!就是静态区间$K$小,主席树的模板题!

~~太简单了!~~主席树搞一搞就可以了!

这里就需要理解**主席树求静态区间K小值**的原理.其实就是**前缀和**的思想:开$n$颗**权值线段树**,第$i$颗维护第$1$个数字到第$i$个数字的**值域**的信息,那么要查询$[L,R]$这个区间的权值的$K$小值,只需要用第$R$颗权值线段树减去第$L-1$颗权值线段树,再按上文$2.1.2$的思路求$[L,R]$区间$K$小值.

那开$n$颗权值线段树会爆空间怎么办?可持久化一下就好了.

~~看不懂?回去复习静态区间$K$小~~

##### 2.2.3问题$3$

给你一个数列,**边修改边询问**,多次询问区间和,怎么做?

~~太简单了!树状数组维护前缀和搞一搞就可以了.~~

具体来说,开一个长度为$n$的数组(记为$c$),也就是树状数组的那个数组.如果要查询$[1,i]$前缀和,只需要把不多于$log_2i$个$c$值加起来就可以了.修改时,也只需要修改不多于$log_2i$个$c$值.复杂度$O(log_2n)$.

~~看不懂?回去复习树状数组~~

##### 2.2.4问题$4$

给你一个数列,**边修改边询问**,多次询问区间第K小值,怎么做?

没错!就是本题!

结合$2.2.2$和$2.2.3$的思想,我们可以开$n$颗权值线段树,用**树状数组**维护(**权值线段树相当于树状数组的节点**).

如果要**查询**区间$[1,i]$的值域的信息(也就是各值出现的次数,~~不懂?回去复习下权值线段树~~),只需要把不多于$log_2i$颗线段树加起来就可以了.那么,如果要查询区间$[L,R]$ 的值域信息,我们先**把$log_2i$颗线段树加起来**求$[1,R]$的信息,再把**把$log_2i$级颗线段树加起来**求$[1,L-1]$的信息,然后用$[1,R]$的信息减掉$[1,L-1]$的信息,像$2.2.2$那么求就可以了.(~~不知道怎么加或者怎么求?回~~~~去读$2.2.2$~~).

**修改**时,也只需要修改不多于$log_2i$颗线段树.修改$1$颗线段树花费时间$O(log_2n)$,那么$1$次**修改**总时间就是$O(log_2^2n)$.

修改的复杂度好像对了,但是查询的**相加**那一步,累加$1$颗怎么着也得$O(n)$,还要累加$log_2i$颗,单次复杂度达到了$O(nlogn)$.怎么办?下一节我们再说.

到这里,我们也解决了刚学树状数组套线段树的人(~~比如当时的我~~)很纠结的问题——**内层的线段树存的是什么**?

我问你:**树状数组的那个数组**存的是什么?

是不是一时语塞,**只可意会不可言传**?

没错,这里的线段树存的东西就类似于那个数组存的东西.

## 3.代码实现

#### 3.1离散化

因为内层权值线段树的下标是值域需要进行离散化.**需要注意的是,要把修改的值也输入进来,同初始权值一起离散化**.

#### 3.2修改操作

和普通动态开点线段树的修改一样.如果进入空节点则新建节点.选择进入修改左右子树之一.

##### 3.2.1修改操作示例代码

```cpp
   //在内层线段树中
    void change(int &x,int L,int R,int Pos,int k)
    {
        if(x==0)x=++Tot;
        v[x]+=k;
        if(L==R)return;
        int Mid=(L+R)>>1;
        if(Pos<=Mid)change(LC[x],L,Mid,Pos,k);
        else change(RC[x],Mid+1,R,Pos,k);
    }
   //在外层树状数组中
	void change(int p,int val,int v)
    {
        for(int i=p;i<=n;i+=i&-i)
            SegmentTree.change(SegmentTree.Root[i],1,n,val,v);
    }
```

##### 3.2.2注意

值得注意的是,~~如果上面的分析看懂了的话~~,会发现外层的树状数组是以**位置**为下标的.这也是我们在外层树状数组修改时既需要传**位置的下标**(代码里的$p$),也要传**值**(即内层线段树的下标,代码里的$val$)的原因.

#### 3.3查询操作:记录节点,现算现用

假设我们已经得到了这$logn$颗线段树的和,现在我们要利用这个**和线段树**来计算答案.

容易发现,在访问一个节点时,我们是进入它的左子节点还是右子节点,只与**左子节点的大小与$K$的大小的关系**有关(~~不知道为什么?回去看主席树求静态区间K小值~~),**与树中其它任何节点都无关**,这启发我们**在要用到某个节点的数据的时候,再对这个节点求和**.举个例子,现在我们在**假想的和线段树中**到了节点$u$,需要通过$size[LC[u]]$的大小来判断是进入左子树还是右子树,那么我们**当场**从那$logn$颗子树中**揪出**对应的$LC[u]$这个节点,**现场求和**,并判断进入左子树还是右子树.

如果可以在$O(1)$时间内**揪出**,显然查询的复杂度也是$O(log_2^2n)$的(访问线段树$O(logn)$,每个节点求和$O(logn)$).

那么怎么个**揪**法呢?聪明的你一定可以想到,我们只需要在开始遍历这颗假想的**和线段树**之前,用一个数组存一下这$logn$颗线段树的根节点,即"**应该揪出的节点的编号**",然后每次进入左子树时,把"**应该揪出的节点的编号**"指向**其左儿子**,进入右子树则指向其右儿子.这样就可以保证$O(1)$**揪出**了.

没看懂?再来看图片解释:![3.3.2配图](https://cdn.luogu.com.cn/upload/pic/65155.png )

![3.3.2配图2](https://cdn.luogu.com.cn/upload/pic/65158.png )

需要注意的是,我们现在求的是$[L,R]$区间,所以要进行**现场加上$1...R$那$logn$颗子树**和**现场减去$1...L-1$那$logn$颗子树**两步操作.

**查询操作示例代码**

```cpp
    //内层线段树
	int Query(int L,int R,int K)
    {
        if(L==R)return L;
        int sum=0;
        for(int i=1;i<=C1;i++)sum-=v[LC[X[i]]];//现场减去1...L-1那logn颗子树
        for(int i=1;i<=C2;i++)sum+=v[LC[Y[i]]];//现场加上1...R那logn颗子树
 		if(K<=sum)//进入左子树
 		{
            for(int i=1;i<=C1;i++)X[i]=LC[X[i]];
            for(int i=1;i<=C2;i++)Y[i]=LC[Y[i]];
            return Query(L,Mid,K);	
        }
        else//进入右子树
 		{
            for(int i=1;i<=C1;i++)X[i]=RC[X[i]];
            for(int i=1;i<=C2;i++)Y[i]=RC[Y[i]];
            return Query(Mid+1,R,K-sum);				
        }
    } 
	//外层树状数组
    int Query(int L,int R,int K)
    {
        //预处理需要查询哪log(n)颗主席树 
        C1=C2=0;
        for(int i=(L-1);i;i-=(i&-i))X[++C1]=SegmentTree.Root[i];
        for(int i=R;i;i-=(i&-i))Y[++C2]=SegmentTree.Root[i];
        //"现算现用"查询区间K大 
        return SegTree.Query(1,n,K);
    }
```

## 4.完整代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define SIZE 200005 

int n,m;
int nx;
int A[SIZE];//原数组 
//int B[SIZE];//离散化之后的数组
int Tem[SIZE];//离散化临时数组 
int X[SIZE];//计算第[1...L-1]颗主席树的和 需要累加的主席树的编号
int Y[SIZE];//计算第[1...R]颗主席树的和 需要累加的主席树的编号
int C1;//计算第[1...L-1]颗主席树的和 需要累加的主席树的数量
int C2;//计算第[1...R]颗主席树的和 需要累加的主席树的数量

//离散化 
void D()
{
    //for(int i=1;i<=n;i++)Tem[i]=A[i]; 
    sort(Tem+1,Tem+1+nx);
    nx=unique(Tem+1,Tem+1+nx)-(Tem+1);
    //for(int i=1;i<=n;i++)B[i]=lower_bound(Tem+1,Tem+1+nx,A[i])-Tem;
} 

//内层: 动态开点权值线段树
struct SegTreeX
{
    int Tot,Root[SIZE*400],v[SIZE*400],LC[SIZE*400],RC[SIZE*400];
    #define Mid ((L+R)>>1)
    void Change(int &x,int L,int R,int Pos,int Val)
    {
        if(x==0)x=++Tot;
        v[x]+=Val;
        if(L==R)return;
        if(Pos<=Mid)Change(LC[x],L,Mid,Pos,Val);
        else Change(RC[x],Mid+1,R,Pos,Val);
    }
    int Query(int L,int R,int K)
    {
        if(L==R)return L;
        int sum=0;
        for(int i=1;i<=C1;i++)sum-=v[LC[X[i]]];
        for(int i=1;i<=C2;i++)sum+=v[LC[Y[i]]];
 		if(K<=sum)
 		{
            for(int i=1;i<=C1;i++)X[i]=LC[X[i]];
            for(int i=1;i<=C2;i++)Y[i]=LC[Y[i]];
            return Query(L,Mid,K);	
        }
        else
 		{
            for(int i=1;i<=C1;i++)X[i]=RC[X[i]];
            for(int i=1;i<=C2;i++)Y[i]=RC[Y[i]];
            return Query(Mid+1,R,K-sum);				
        }
    } 
}SegTree;

//外层树状数组 
struct BITX
{
    void Change(int Pos,int Val)
    {
        int k=lower_bound(Tem+1,Tem+1+nx,A[Pos])-Tem;//离散化之后的权值 也就是权值线段树里的下标
        for(int i=Pos;i<=n;i+=i&(-i))SegTree.Change(SegTree.Root[i],1,nx,k,Val);
    }
    int Query(int L,int R,int K)
    {
        //预处理需要查询哪log(n)颗主席树 
        C1=C2=0;
        for(int i=(L-1);i;i-=(i&-i))X[++C1]=SegTree.Root[i];
        for(int i=R;i;i-=(i&-i))Y[++C2]=SegTree.Root[i];
        //"现算现用"查询区间K大 
        return SegTree.Query(1,nx,K);
    }
}BIT;

struct Query
{
    int opp,Lx,Rx,k;
}q[SIZE];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){ scanf("%d",&A[i]); Tem[++nx]=A[i]; }
    char op[5];
    for(int i=1;i<=m;i++)
    {
        scanf("%s",op);
        if(op[0]=='Q'){ q[i].opp=1;	scanf("%d%d%d",&q[i].Lx,&q[i].Rx,&q[i].k); }
        else { scanf("%d%d",&q[i].Lx,&q[i].k); Tem[++nx]=q[i].k;}
    } 
    D();//初始权值和修改的值一起离散化
    for(int i=1;i<=n;i++)BIT.Change(i,1);
    for(int i=1;i<=m;i++)
    {
        if(q[i].opp==1)
        {
            printf("%d\n",Tem[BIT.Query(q[i].Lx,q[i].Rx,q[i].k)]);
        }
        else
        {
            BIT.Change(q[i].Lx,-1);
            A[q[i].Lx]=q[i].k;
            BIT.Change(q[i].Lx,1);
        }
    } 
    return 0;
}
```



---

## 作者：lilong (赞：4)

除了树套树做法外，整体二分也是可以的。

整体二分的主要思想是：通过对值域进行一次二分，来求多个区间排名，从而替代了树套树中的权值线段树。具体地，我们把所有操作按时间先后顺序确定后，假设当前的值域中点为 $mid$，那么按原顺序进行所有修改值不超过 $mid$ 的操作，用对应的下标更新树状数组。同时对于中间穿插的查询操作，利用树状数组求出 $[l,r]$ 内不超过 $mid$ 的数的个数，再与 $k$ 比较决定答案在 $mid$ 的哪侧，递归下去即可。当值域缩小为一个数时，此时包含的查询的答案即为这个数。

一些注意点：

- 修改操作要分解为删除和插入两步。

- 初始输入的 $a$ 应转为 $n$ 个插入操作。

- 将操作划分为左右两部分时要按原顺序存储，即**时间顺序不能改变**。

离散化后，由于最多有 $n+m$ 个不同的数，因此递归最多 $\log_2(n+m)$ 层，总操作数 $n+m$，每层执行所有操作时间复杂度 $O((n+m) \log (n+m) )$，总时间复杂度 $O((n+m)\log^2(n+m))$，实际最大点不到 300ms。（当然不离散化也可以）


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 200001

using namespace std;

int n,m,M,M2,a[N],ls[N * 2],siz,ans[N * 2],op2[N * 2];
int t[N * 2];

struct Q
{
    int op,l,r,k,x,y,id;
}q[N * 2],q1[N * 2],q2[N * 2];

int lowbit( int x )
{
    return x & ( -x );
}

void upd( int x , int y )
{
    for( int i = x ; i <= siz ; i += lowbit( i ) )
        t[i] += y;
    return;
}

int que( int x )
{
    int sum = 0;
    for( int i = x ; i >= 1 ; i-= lowbit( i ) )
        sum += t[i];
    return sum;
}

void solve( int l , int r , int ql , int qr )
{
    if( ql > qr ) return;
    if( l == r )
    {
        for( int i = ql ; i <= qr ; i ++ )
            if( q[i].op == 2 )
                ans[q[i].id] = l;
        return;        
    }
    int mid = ( l + r ) / 2,L = 0,R = 0;
    for( int i = ql ; i <= qr ; i ++ )
    {
        if( q[i].op == 0 )
        {
            if( q[i].y <= mid )
            {
                L ++;
                q1[L] = q[i];
                upd( q[i].x , 1 );
            }
            else
            {
                R ++;
                q2[R] = q[i];
            }
        }
        if( q[i].op == 1 )
        {
            if( q[i].y <= mid )
            {
                L ++;
                q1[L] = q[i];
                upd( q[i].x , -1 );
            }
            else
            {
                R ++;
                q2[R] = q[i];
            }
        }
        if( q[i].op == 2 )
        {
            int nw = que( q[i].r ) - que( q[i].l - 1 );
            if( nw >= q[i].k ) L ++,q1[L] = q[i];
            else R ++,q2[R] = q[i],q2[R].k -= nw;
        }
    }
    
    for( int i = ql ; i <= qr ; i ++ )
    {
        if( q[i].op == 0 && q[i].y <= mid ) upd( q[i].x , -1 );
        if( q[i].op == 1 && q[i].y <= mid ) upd( q[i].x , 1 );
    }
    int i = ql;
    for( int j = 1 ; j <= L ; i ++ , j ++ )
        q[i] = q1[j];
    for( int j = 1 ; j <= R ; i ++ , j ++ )
        q[i] = q2[j];
    solve( l , mid , ql , ql + L - 1 );
    solve( mid + 1 , r , ql + L , qr );
    return;
}

int main()
{
    ios::sync_with_stdio( false );
    cin.tie( 0 );
    cout.tie( 0 );
    cin >> n >> m;
    for( int i = 1 ; i <= n ; i ++ )
    {
        cin >> a[i];
        ls[++ siz] = a[i];
        M ++;
        q[M].id = M;
        q[M].op = 0;
        q[M].x = i;
        q[M].y = a[i];
    }
    int l,r,k,x,y;
    char op;
    for( int i = 1 ; i <= m ; i ++ )
    {
        cin >> op;
        if( op == 'C' )
        {
            cin >> x >> y;
            ls[++ siz] = y;
            M ++;
            q[M].op = 1;
            q[M].x = x;
            q[M].y = a[x];
            M ++;
            q[M].op = 0;
            q[M].x = x;
            q[M].y = y;
            a[x] = y;
        }
        else
        {
            M ++;
            M2 ++;
            cin >> l >> r >> k;
            q[M].op = 2;
            q[M].id = M2;
            q[M].l = l;
            q[M].r = r;
            q[M].k = k;
        }
    }
    sort( ls + 1 , ls + siz + 1 );
    siz = unique( ls + 1 , ls + siz + 1 ) - ls - 1;
    for( int i = 1 ; i <= M ; i ++ )
        if( q[i].op == 0 || q[i].op == 1 )
            q[i].y = lower_bound( ls + 1 , ls + siz + 1 , q[i].y ) - ls;
    solve( 1 , siz , 1 , M );
    for( int i = 1 ; i <= M2 ; i ++ )
        cout << ls[ans[i]] << '\n';
    return 0;
}
```

---

## 作者：zhangbubu (赞：3)

看了看楼下的题解，发现楼下的题解每次add都新开了一个树，但这是没有必要的，而且程序还变慢，所以我是直接在原树上修改就行了
，还有一个问题，这题的数据是不是加强了？？？题解很多RE，我开到了4e7才过的：
放码-。-

```cpp
#include"bits/stdc++.h"
using namespace std;
#define nn 40000000
#define lowbit(x) ((x)&(-x))

int rt[nn],b[nn],a[nn],ca[nn],cb[nn],cc[nn] ;
int size[nn],xx[nn],yy[nn],l[nn],r[nn];
int n,m;
int totn;
int tot,totx,toty;

inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}


void change(int &y,int L,int R,int pos,int v)
{
      if (!y)y=++tot; size[y]+=v;//,l[tot]=l[x],r[tot]=r[x];
    if (L==R)return ;
    int mid = R+L>>1;if (pos<=mid)change(l[y],L,mid,pos,v);
    else change(r[y],mid+1,R,pos,v);
}

inline void add(int x,int v)
{
    int k = lower_bound(b+1,b+1+totn,a[x])-b;
    for (int i=x;i<=n;i+=lowbit(i)) change(rt[i],1,totn,k,v);
}

int query(int L,int R,int p)
{
    if (L==R)return R; int sum=0; int mid = L+R>>1;
    for (int i=1;i<=totx;i++)sum-=size[l[xx[i]]];
    for (int i=1;i<=toty;i++)sum+=size[l[yy[i]]];

    if (p<=sum)
    {
       for ( int i=1;i<=totx;i++)xx[i]=l[xx[i]];
       for ( int i=1;i<=toty;i++)yy[i]=l[yy[i]];
       return query(L,mid,p);
    }
     for ( int i=1;i<=totx;i++)xx[i]=r[xx[i]];
       for ( int i=1;i<=toty;i++)yy[i]=r[yy[i]];
      return query(mid+1,R,p-sum);
}

int main()
{  char s;
    n=read(),m=read();
    for (int i=1;i<=n;i++)a[i]=read(),b[++totn]=a[i];

    for (int i=1;i<=m;i++)
    {
        cin>>s; if (s=='Q') ca[i]=read(),cb[i]=read(),cc[i]=read();
        else ca[i]=read(),cb[i]=read(),b[++totn]=cb[i];
    }
        sort(b+1,b+1+totn);
    totn=unique(b+1,b+1+totn)-b-1;

    for ( int i=1;i<=n;i++) add(i,1);
    for ( int i=1;i<=m;i++)
    {
        if (cc[i])
        {  totx=toty=0;
            for ( int j=ca[i]-1;j;j-=lowbit(j))xx[++totx]=rt[j];
            for ( int j=cb[i];j;j-=lowbit(j))yy[++toty]=rt[j];
            printf("%d\n",b[query(1,totn,cc[i])]);
        }
        else
        {
            add(ca[i],-1),a[ca[i]]=cb[i],add(ca[i],1);
        }
    }

}

```

---

## 作者：Minakami_Yuki (赞：2)

## 题目链接

[P2617 Dynamic Rankings](https://www.luogu.org/problem/P2617)

## 题意简述

动态区间第 $k$ 小。

## 解题思想

考虑静态解法，单点修改后对对应的主席树暴力，单次修改复杂度 $O(n\log n)$。显然会T。

考虑主席树维护的前缀和，我们发现问题相当于单点修改，区间查询。

这个不难用树状数组维护。

所以可以树状数组套主席树解决，单次修改 $O(\log^2n)$。

需要注意的是，必须把预处理所有的待修改元素，所以这是个离线算法。

修改可以将树状数组的 `modify()` 中的 `+=` 直接改成主席树 `modify()`，但是查询需要 $O(\log n)$ 个节点一起向下移动。所以要在主席树 `modify()` 的内部处理。

## 参考代码

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>

inline int read() {
    char ch = getchar(); int r = 0, w = 1;
    while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
    while(isdigit(ch)) {r = r * 10 + ch - '0', ch = getchar();}
    return r * w;
}

const int N = 4e7 + 6;

int n, m, sz, idx;
int a[N], b[N], t[N], ls[N], rs[N], rt[N], cur1[N], cur2[N], q1[N], q2[N], q3[N];
bool type[N];
#define mid ((l + r) >> 1)
inline void copy(int old, int o) {t[o] = t[old], ls[o] = ls[old], rs[o] = rs[old];}
inline void upd(int o) {t[o] = t[ls[o]] + t[rs[o]];}
void build(int &o, int l, int r) {o = ++idx; if(l == r) return; build(ls[o], l, mid); build(rs[o], mid + 1, r);}
void modify(int old, int &o, int l, int r, int x, int k) {o = ++idx; copy(old, o); if(l == r) {t[o] += k; return;} if(x <= mid) modify(ls[old], ls[o], l, mid, x, k); else modify(rs[old], rs[o], mid + 1, r, x, k); upd(o);}
inline int lowbit(int x) {return x & -x;}
inline void modify(int o, int x, int k) {for(; o <= n; o += lowbit(o)) modify(rt[o], rt[o], 1, sz, x, k);}
inline int query(int ll, int rr, int k) {
    int l = 1, r = sz, sum1, sum2;
    for(register int i = ll; i; i -= lowbit(i)) cur1[i] = rt[i];
    for(register int i = rr; i; i -= lowbit(i)) cur2[i] = rt[i];
    while(l < r) {
        sum1 = sum2 = 0;
        for(register int i = ll; i; i -= lowbit(i)) sum1 += t[ls[cur1[i]]];
        for(register int i = rr; i; i -= lowbit(i)) sum2 += t[ls[cur2[i]]];
        if(sum2 - sum1 >= k) {
            for(register int i = ll; i; i -= lowbit(i)) cur1[i] = ls[cur1[i]];
            for(register int i = rr; i; i -= lowbit(i)) cur2[i] = ls[cur2[i]];
            r = mid;
        }
        else {
            for(register int i = ll; i; i -= lowbit(i)) cur1[i] = rs[cur1[i]];
            for(register int i = rr; i; i -= lowbit(i)) cur2[i] = rs[cur2[i]];
            l = mid + 1, k -= sum2 - sum1;
        }
    }
    return l;
}

bool isQ() {
    char op = getchar();
    while(op != 'Q' && op != 'C') op = getchar();
    return op == 'Q';
}

int main() {
    n = read(), m = read(), sz = n;
    for(register int i = 1; i <= n; i++) a[i] = b[i] = read();
    for(register int i = 1; i <= m; i++) {
        type[i] = isQ();
        q1[i] = read(), q2[i] = read();
        if(type[i]) q3[i] = read();
        else b[++sz] = q2[i];
    }
    std::sort(b + 1, b + sz + 1);
    sz = std::unique(b + 1, b + sz + 1) - b - 1;
    build(rt[0], 1, sz);
    for(register int i = 1; i <= n; i++) modify(i, std::lower_bound(b + 1, b + sz + 1, a[i]) - b, 1);
    for(register int i = 1; i <= m; i++) {
        if(type[i]) printf("%d\n", b[query(q1[i] - 1, q2[i], q3[i])]);
        else {
            modify(q1[i], std::lower_bound(b + 1, b + sz + 1, a[q1[i]]) - b, -1);
            a[q1[i]] = q2[i];
            modify(q1[i], std::lower_bound(b + 1, b + sz + 1, a[q1[i]]) - b, 1);
        }
    }
    return 0;
}
```

---

## 作者：ljc20020730 (赞：2)

### **一些奇怪的东西**

这个大概是luogu某题目，然而我太菜了，所以现在才会做。

这个题目显然是由一些静态的东西衍生而来的（没错就是静态区间K大数）

一些静态和动态的问题，我列举一下：

- 静态区间K大数（排个序就好了）

- 静态区间K大数（主席树搞一搞）

- 待修改区间K大数（我就要讲的这个嘛）

- 动态区间和（zkw线段树/朴素线段树/2个树状数组）

- 静态区间和（...前缀和?）

然后是宣传blog ：[搓这里](https://www.cnblogs.com/ljc20020730/p/10357196.html)

### **步入正题**

话说带修改区间K大数（注意是修改而并不是插入）

显然我们如果按照静态区间K大数的方法搞，暴力更新整棵线段树那么复杂度将是O($ n log_2 n $ )修改每次

想到单点修改求前缀和想到树状数组。不妨用树状数组维护线段树每个节点的前缀和，

换句话说要想求得每个节点具体的值，那么必须将属于这个节点的$ log_2 n $个节点的和全部累加，才是这个节点值域范围内，前缀插入数的个数

既然我们能求出在线段树某一节点值域范围内，前缀插入数的个数，我们就按照和静态区间K大数的类二分查找（用线段树对值域的二分代替整体二分）来找到一个对于的树根，输出他的标号就行。

所以，树状数组是维护一个数组表示的是要想知道当前每一节点值域是[L,R]前缀插入数的个数，是哪log2 n个节点的累加和。

这样子复杂度是O($  log_2 ^ 2n $)每次插入。

查询的时候也是这样用R的前缀插入数的个数减去(l-1)前缀插入数的个数，就是该节点值域在[L,R]区间内插入数的个数。

这样的复杂度也是($  log_2 ^ 2n $)每次查询。

注意一些细节：

记录那几个点的数组（node_add和node_cut只需开log2n个即可），

然后离线离散化以后在线做（其实和在线效果一样），

然后离散化的时候尽量不用vector(不好习惯)

对tmp[]离散化，T记录离散化后下标
```
    sort(tmp+1,tmp+1+tmp[0]);
    T=unique(tmp+1,tmp+1+tmp[0])-tmp;
```
若要查询某个数val离散化以后是多少，那么就是
```
	w=lower_bound(tmp+1,tmp+1+T,val)-tmp;
```
若要查询某个离散化后的数kkk实际上是多少那么直接访问下标
```
	w=o[kkk];
```

还是得解释代码：
```
# include <cstdio>
# include <map>
# include <algorithm>
# include <vector>
# include <cstring>
using namespace std;
const int N=1e5+10;
# define lowbit(x) (x&(-x))
# define lson t[rt].ls,l,mid
# define rson t[rt].rs,mid+1,r
# define mid ((l+r)>>1)
int tmp[N<<1];
struct rec{
    int l,r,k,o;
}qes[N];
struct Seqment_Tree{
    int ls,rs,val;
}t[N*400];//树套树空间得开 n log n
int node_cut[25],node_add[25]; //这里只要log n个就行后面memset会慢
int cnt_cut,cnt_add,tot;
int root[N],a[N];
int T,n,m;
inline int read()
{
    int X=0,w=0; char c=0;
    while(c<'0'||c>'9') {w|=c=='-';c=getchar();}
    while(c>='0'&&c<='9') X=(X<<3)+(X<<1)+(c^48),c=getchar();
    return w?-X:X;
}
void write(int x)
{
    if (x<0) x=-x,putchar('-');
    if (x>9) write(x/10);
    putchar('0'+x%10);
}//I/O优化
void update(int &rt,int l,int r,int pos,int val)
{
    if (!rt) rt=++tot; //如果此时的访问空的节点那么建立节点，否则会覆盖掉原有节点信息（普通主席树最好也这么写,但是没必要，因为每个节点一定是空的!!!）
    t[rt].val+=val;
    if (l==r) return;
    if (pos<=mid) update(lson,pos,val);
    else update(rson,pos,val);
}//普通主席树的更改维护，值域+1/-1
void pre_update(int x,int val)
{
    int w=lower_bound(tmp+1,tmp+1+T,a[x])-tmp;
    for (int i=x;i<=n;i+=lowbit(i)) update(root[i],1,T,w,val);
}//首先处理出那几棵线段树管这个数组的位置的前缀和的，然后每个线段树分别维护
int query(int l,int r,int k)
{
    if (l==r) return l;
    int ret=0;
    for (int i=1;i<=cnt_add;i++)
        ret+=t[t[node_add[i]].ls].val;
    for (int i=1;i<=cnt_cut;i++)
        ret-=t[t[node_cut[i]].ls].val; 
//该加的加(r)，该减的减(l-1)
    if (k<=ret) {
        for (int i=1;i<=cnt_add;i++)
            node_add[i]=t[node_add[i]].ls;
        for (int i=1;i<=cnt_cut;i++)
            node_cut[i]=t[node_cut[i]].ls;
        return query(l,mid,k);
//不足右边不可能往左边搜
    } else {
        for (int i=1;i<=cnt_add;i++)
            node_add[i]=t[node_add[i]].rs;
        for (int i=1;i<=cnt_cut;i++)
            node_cut[i]=t[node_cut[i]].rs;
        return query(mid+1,r,k-ret);
//超过左边不可能往右边搜
    }
}
int pre_query(int l,int r,int k)
{
    memset(node_add,0,sizeof(node_add));
    memset(node_cut,0,sizeof(node_cut));
    cnt_add=cnt_cut=0;//清空
    for (int i=r;i;i-=lowbit(i)) node_add[++cnt_add]=root[i];
//处理该加的根节点
    for (int i=l-1;i;i-=lowbit(i)) node_cut[++cnt_cut]=root[i];
//处理该减的根节点
    return query(1,T,k);
}
int main()
{
    n=read();m=read();
    for (int i=1;i<=n;i++)
        tmp[++tmp[0]]=a[i]=read();
    for (int i=1;i<=m;i++) {
        char ch=0;
        while (ch!='Q'&&ch!='C') ch=getchar();
        if (ch=='Q') qes[i].l=read(),qes[i].r=read(),qes[i].k=read(),qes[i].o=1;
        else qes[i].l=read(),tmp[++tmp[0]]=qes[i].r=read(),qes[i].o=0;
    }
    sort(tmp+1,tmp+1+tmp[0]);
    T=unique(tmp+1,tmp+1+tmp[0])-tmp;
    for (int i=1;i<=n;i++) pre_update(i,1);
    for (int i=1;i<=m;i++) {
        if (qes[i].o==1) {
            write(tmp[pre_query(qes[i].l,qes[i].r,qes[i].k)]);
            putchar('\n');
        } else {
            pre_update(qes[i].l,-1);
            a[qes[i].l]=qes[i].r;
            pre_update(qes[i].l,1);
        }
    }
    return 0;
}
```
## 所以各位带修改区间中位数会做了吧！！！

---

## 作者：iyanhang (赞：1)

## 动态Kth问题
大致两个思路：
- BIT维护多颗权值线段树
- 原数据的主席树+BIT维护的修改路径主席树

通常第一种前四个点能过，后面的n,m<=10000时就栈溢出了，如果多颗权值线段树之间利用主席树的思想节约建树的消耗，AC大概600多ms。

第二种就可以跑到飞快。但两者核心都是一样的，看那个方便写吧。
（以下是第二种思路:）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MN=10005;

int n,m,cnt=0,len;
int root[MN],a[MN],rem[MN];
struct node{int l,r,sum;}T[MN*600];
vector<int> v;
struct queryList{int c,x,y,z;}qry[MN];//离线。

inline int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
inline int lowBit(int x){return x&(-x);}

void hjtTree(int l,int r,int &x,int y,int pos,int delt)
{
	++cnt,T[cnt]=T[y],T[cnt].sum+=delt,x=cnt;
	if (l==r) return ;
	int mid=(l+r)/2;
	if (mid>=pos) hjtTree(l,mid,T[x].l,T[y].l,pos,delt);
	else hjtTree(mid+1,r,T[x].r,T[y].r,pos,delt);
}
void build(int l,int r,int &cur)
{
	cur=++cnt;
	if (l==r) return ;
	int mid=(l+r)/2;
	build(l,mid,T[cur].l);
	build(mid+1,r,T[cur].r);
}
void change(int i,int now)
{
	int pre=getid(a[i]);
	while(i<=n)
	{
		//if (root[i]==0) build(1,len,root[i]);
		//不能碰到一个就建树，可以利用主席树思想。
		hjtTree(1,len,root[i],root[i],pre,-1);
		hjtTree(1,len,root[i],root[i],now,1);
		i+=lowBit(i);
	}
}
int qx[MN],qy[MN];
void queryTree(int x,int y)
{
	//记录BIT的查询树。
	memset(qx,0,sizeof(qx));
	memset(qy,0,sizeof(qy));
	for (;x;x-=lowBit(x)) qx[++qx[0]]=root[x];
	for (;y;y-=lowBit(y)) qy[++qy[0]]=root[y];
}
int query(int l,int r,int x,int y,int k)
{
	if (l==r) return l;

	int sumx=0,sumy=0;
	for (int i=1;i<=qx[0];++i) sumx+=T[T[qx[i]].l].sum;
	for (int i=1;i<=qy[0];++i) sumy+=T[T[qy[i]].l].sum;
	//保存logn个合并。
	int sum=sumy-sumx+T[T[y].l].sum-T[T[x].l].sum,mid=(l+r)/2;

	if (sum>=k)
	{
		//更新和同步。
		for (int i=1;i<=qx[0];++i) qx[i]=T[qx[i]].l;
		for (int i=1;i<=qy[0];++i) qy[i]=T[qy[i]].l;
		return query(l,mid,T[x].l,T[y].l,k);
	}
	else
	{
		for (int i=1;i<=qx[0];++i) qx[i]=T[qx[i]].r;
		for (int i=1;i<=qy[0];++i) qy[i]=T[qy[i]].r;
		return query(mid+1,r,T[x].r,T[y].r,k-sum);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]),v.push_back(a[i]);
	for (int i=1;i<=m;++i)
	{
		char c[1]; //一开始这里设大了调了好久。
		scanf("%s",c);
		if (c[0]=='Q')
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			qry[i]=(queryList){0,x,y,z};
		}
		else
		{
			int x,t;
			scanf("%d%d",&x,&t);
			qry[i]=(queryList){1,x,t,0};
			v.push_back(t);
		}
	}
	
	sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());
	len=v.size();
	//分两个，rem[1..n]记原始数据，root[1..n]记修改路径。
	for (int i=1;i<=n;++i) hjtTree(1,len,rem[i],rem[i-1],getid(a[i]),1);
	for (int i=1;i<=m;++i)
	{
		if (qry[i].c==0)
		{
			queryTree(qry[i].x-1,qry[i].y);
			//改用getid的时候用，不改用的时候千万不要用，不然样例可能过了，其他都WA。
			printf("%d\n",v[query(1,len,rem[qry[i].x-1],rem[qry[i].y],qry[i].z)-1]);
		}
		else change(qry[i].x,getid(qry[i].y)),a[qry[i].x]=qry[i].y;
	}
	return 0;
}
```

---

## 作者：风随逐影 (赞：1)

# 主席树
求动态区间第k大
（理论空间复杂度nlogn^2，所以要开4000万的数组）
第一次接触树套树，算是道模版题吧
```
//空间复杂度n*logn*logn 
#include<bits/stdc++.h>
using namespace std;
#define go(i,a,b) for(int i=(a);i<=(b);++(i))
#define com(i,a,b) for(int i=(a);i>=(b);--(i))
#define mem(a,b) memset((a),(b),sizeof(a))
#define inf 0x3f3f3f3f
#define fin freopen("input.txt","r",stdin)
#define fout freopen("output.txt","w",stdout)
#define lowbit(x) (x&-x)
const int maxn=100005;
int n,m,q,cntl,cntr,len;
int t[maxn],ls[maxn*400],rs[maxn*400],sum[maxn*400],prel[maxn],prer[maxn];
int a[maxn],oder[maxn*2],cnt=0;
struct node{
	int x,y,k;
}qs[maxn];

void read(int &x){
    int f=1;char s=getchar();x=0;
    while(!isdigit(s)){
    	if(s=='-') f=-1;s=getchar();
    }
    while(isdigit(s)){
   		x=(x<<3)+(x<<1)+s-'0';s=getchar();
    }
    x*=f;
}//读入优化

void update(int &rt,int l,int r,int pos,int val){
	if(!rt) rt=++cnt;
	sum[rt]+=val;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) update(ls[rt],l,mid,pos,val);
	else update(rs[rt],mid+1,r,pos,val);
}

void add(int pos,int val){
	int k=lower_bound(oder+1,oder+len+1,a[pos])-oder;
	for(int i=pos;i<=n;i+=lowbit(i)){
		update(t[i],1,len,k,val);
	}
}

int query(int l,int r,int k){
	if(l==r) return l;
	int tot=0,mid=(l+r)>>1;
	go(i,1,cntl) tot-=sum[ls[prel[i]]];
	go(i,1,cntr) tot+=sum[ls[prer[i]]];
	if(k<=tot){
		go(i,1,cntl) prel[i]=ls[prel[i]];
		go(i,1,cntr) prer[i]=ls[prer[i]];
		return query(l,mid,k);
	}
	else{
		go(i,1,cntl) prel[i]=rs[prel[i]];
		go(i,1,cntr) prer[i]=rs[prer[i]];
		return query(mid+1,r,k-tot);
	}
}

int get(int x,int y,int k){
	cntl=cntr=0;
	for(int i=x-1;i>0;i-=lowbit(i)) prel[++cntl]=t[i];
	for(int i=y;i>0;i-=lowbit(i)) prer[++cntr]=t[i];
	return query(1,len,k);
}

int main()
{
    //fin;//fout;
    read(n),read(m);
    len=n;
    go(i,1,n){
    	read(a[i]);oder[i]=a[i];
	}
	char c;
	int x,y,k;
	go(i,1,m){
		cin>>c;read(x),read(y);
		if(c=='Q'){
			read(k);
			qs[i]=(node){x,y,k};
		}
		else{
			qs[i]=(node){x,y,0};oder[++len]=y;
		}
	}
	sort(oder+1,oder+len+1);
	len=unique(oder+1,oder+len+1)-oder-1;
	go(i,1,n) add(i,1);
	go(i,1,m){
		//go(j,1,n) printf("%d ",t[j]);
		//putchar('\n');
		if(!qs[i].k){
			add(qs[i].x,-1);
			a[qs[i].x]=qs[i].y;
			add(qs[i].x,1);
		}
		else printf("%d\n",oder[get(qs[i].x,qs[i].y,qs[i].k)]);
	}
    return 0;
}
```


---

