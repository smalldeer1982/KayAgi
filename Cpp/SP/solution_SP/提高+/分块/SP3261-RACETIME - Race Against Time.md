# RACETIME - Race Against Time

## 题目描述

现在有$n(1<=n<=1e5)$只奶牛站成一排，每只奶牛手中都拿着一个数字$A_i(0<=A_i<=1e9)$

现在$FJ$要执行$Q(1<=Q<=50000)$个操作，每个操作可能是下面两种操作之一：

$1.$ $M$ $i$ $X$ ：将第$i$只奶牛手上的数字$A_i$替换为$X$

$2.$ $C$ $l$ $r$ $K$：询问区间$[l,r]$内有多少只奶牛手上拿的数字$A_i\le K$

作为$FJ$的好朋友，请你对每一个$2$操作输出答案

由于$FJ$非常蕉♂躁，所以他只允许你在$1s$内回答这些问题

## 样例 #1

### 输入

```
4 6
3
4
1
7
C 2 4 4
M 4 1
C 2 4 4
C 1 4 5
M 2 10
C 1 3 9```

### 输出

```
2
3
4
2```

# 题解

## 作者：asasas (赞：8)

这是一道很好的分块练手题。

这题的主要操作就是查询操作，~~修改操作肯定都会对吧~~。

那么如何求出所有 $a_i\le k$ 的个数呢？

我们再看一下数据范围：$n\le 10^{5},m\le 5 \times 10^{4}$。

线段树？ 分块？~~显然分块比较好想，毕竟暴力数据结构。~~

不会分块的同学看看[这个](https://www.cnblogs.com/arcturus/p/9302143.html)。

总而言之，分块的思想就是：**对所有元素分成许多个块，每次操作时分开处理，对在同一个块内或者是块的一部分的元素直接暴力修改，对每个整的块再进行处理。**

块的大小和个数一半由题目的数据范围决定，一般来说取 $ \sqrt n $（这题也是）即可。但有的题目并不是分成 $ \sqrt n $ 块最好 这要视具体的题目而定。

好了，既然确定了分块，那么怎么做呢？

于是我们想到，**对每个块内的所有元素进行排序，查找的时候直接二分查找即可**。

~~修改操作太水了就不说了。~~ 

接下来就是预处理。先预处理每个块的所有信息：左端点，右端点，并把块内所有元素排序。

改的时候每次改完要重新排序。

求答案的时候如果区间在一个块内暴力扫一遍直接查 否则分成三段进行处理：**两端的散块暴力查询，中间的整块，对每个块进行二分**。

时间复杂度？大概是 $n\times \sqrt{n} \times \log_{2}{\sqrt n}$ 极限数据约为 $1.2s$ 还是有点卡的 所以时限很奇怪？


上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int L[500005],R[500005],pos[500005],b[500005],a[500005],kuai;//L,R是每个块的左端点和右端点 pos是每个点所在的块，a是初始数组，b是每个块排好序后的数组 
int getsum(int l,int r,int k){
	int x=pos[l],y=pos[r];
	if (x==y){
	    int ans=0;
	    for (register int i=l;i<=r;i++){
	    	if (a[i]<=k) ans++;
		}
		return ans;//在一个块暴力找 
	}
	int ans=0;
	for (register int i=l;i<=R[x];i++){
		if (a[i]<=k) ans++;
	}//和下面一样散块暴力找 
	for (register int i=x+1;i<=y-1;i++){
		int xs=L[i],mcqh=R[i],sum=0;
		while(xs<=mcqh){
			int mid=(xs+mcqh)/2;
			if (b[mid]>k) mcqh=mid-1;
			else xs=mid+1;
		}
		ans+=xs-L[i]; 
	}//二分找出第一个小于k的位置 
	for (register int i=L[y];i<=r;i++){
		if (a[i]<=k) ans++;
	}
	return ans;
}
int main(){
	int n,q;
	cin >> n >> q;
	for (register int i=1;i<=n;i++) cin >> a[i],b[i]=a[i];
	kuai=sqrt(n*1.0);
	for (register int i=1;i<=kuai;i++){
		L[i]=(i-1)*kuai+1,R[i]=i*kuai;
	}//预处理每个块的端点 
	if (R[kuai]!=n){
		L[kuai+1]=R[kuai]+1,R[kuai+1]=n,kuai++;
	}//分块必备，如果不能分成整块，就再加一个块 
	for (register int i=1;i<=kuai;i++){
		for (register int j=L[i];j<=R[i];j++){
		    pos[j]=i;
		    sort(b+L[i],b+R[i]+1); //预处理出每个点所在的块，并对b=每个块里的元素排序 
		} 
	}
	while(q--){
		char op[5];
		cin >> op;
		if (op[0]=='M'){
			int p,x;
			cin >> p >> x;
			a[p]=x;
			int bel=pos[p];
			for (register int i=L[bel];i<=R[bel];i++){
				b[i]=a[i];
			}
			sort(b+L[bel],b+R[bel]+1);//每次改了以后要重新排序 
		}
		else {
			int l,r,k;
			cin >> l >> r >> k;
			cout << getsum(l,r,k) << endl;
		}
	}
}
```

强化版是洛谷的[教主的魔法](https://www.luogu.com.cn/problem/P2801)，这题还需要打标记，处理相对来说麻烦一下大家可以去尝试一下 qwq

---

## 作者：KiDDOwithTopTree (赞：5)

题目在这：[传送门](https://www.luogu.com.cn/problem/SP3261)。

发现没有树套树的题解，于是我来水一篇。

### 做法：树状数组套主席树（树状数组套动态开点值域线段树）。

我看到这题的第一反应便是[这题](https://www.luogu.com.cn/problem/P3380)。

但是，我打代码的手却不想去写线段树套平衡树。

因为[这题](https://www.luogu.com.cn/problem/P3380)的操作很多，但是这一题却只有两种操作，打棵平衡树显得大材小用。作为一个主席树党，我考虑如何用主席树实现这两个操作。

首先，它要我们支持修改操作，那么我们应该使用树状数组套主席树让主席树可以支持修改。[模板在这](https://www.luogu.com.cn/problem/P2617)。

然后，它让我们求出区间 $[l,r]$ 内有个数 $A_i \le K$。

显然，[主席树模板题](https://www.luogu.com.cn/problem/P3834)中并没有这个操作，但是，我不会因此而不打树状数组套主席树。

我们考虑如何对查询操作进行修改。

我们可以在管辖区间 $[l,r]$ 的主席树上找到值为 K 的那个节点，然后分情况讨论一下：如果是要去左子树，那么直接返回左子树的结果就可以了。如果要去右子树，那么不仅要计算右子树的结果，**还要计算左子树的全部值**。如果是叶子节点，因为要计算的是 $A_i \le K$ 的个数，那么**还要计算叶节点有多少个值**。如果不懂的可以配合代码理解理解。

因为本题值域过大，所以应该先离散化。

这里给出我的代码：
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e5+10;
struct segment_tree{
	int lson,rson;
	int val;
};
struct node{
	char ch;
	int x,y,k;
};
segment_tree hjt[400*N];
node q[N];
int root[N],a[N],b[2*N];
int tmp[2][20];
int cnt1,cnt0;
int n,m;
int tot;
int t;
inline int get(int val){
	return lower_bound(b+1,b+t+1,val)-b;
}
inline int lowbit(int x){
	return x&-x;
}
void smt_ins(int &now,int l,int r,int pos){
	if(!now)
		now=++tot;
	hjt[now].val++;
	if(l==r)
		return ;
	int mid=l+r>>1;
	if(pos<=mid)
		smt_ins(hjt[now].lson,l,mid,pos);
	else
		smt_ins(hjt[now].rson,mid+1,r,pos);
}
void smt_del(int now,int l,int r,int pos){
	hjt[now].val--;
	if(l==r)
		return ;
	int mid=l+r>>1;
	if(pos<=mid)
		smt_del(hjt[now].lson,l,mid,pos);
	else
		smt_del(hjt[now].rson,mid+1,r,pos);
}
int smt_query(int l,int r,int pos){
	int val=0;
	if(l==r){
		for(int i=1;i<=cnt1;i++)
			val+=hjt[tmp[1][i]].val;
		for(int i=1;i<=cnt0;i++)
			val-=hjt[tmp[0][i]].val;
		return val;
	}
	for(int i=1;i<=cnt1;i++)
		val+=hjt[hjt[tmp[1][i]].lson].val;
	for(int i=1;i<=cnt0;i++)
		val-=hjt[hjt[tmp[0][i]].lson].val;
	int mid=l+r>>1;
	if(pos<=mid){
		for(int i=1;i<=cnt1;i++)
			tmp[1][i]=hjt[tmp[1][i]].lson;
		for(int i=1;i<=cnt0;i++)
			tmp[0][i]=hjt[tmp[0][i]].lson;
		return smt_query(l,mid,pos);
	}
	else{
		for(int i=1;i<=cnt1;i++)
			tmp[1][i]=hjt[tmp[1][i]].rson;
		for(int i=1;i<=cnt0;i++)
			tmp[0][i]=hjt[tmp[0][i]].rson;	
		return val+smt_query(mid+1,r,pos);
	}
}
void bit_ins(int pos,int val){
	for(int i=pos;i<=n;i+=lowbit(i))
		smt_ins(root[i],1,t,val);
}
void bit_del(int pos,int val){
	for(int i=pos;i<=n;i+=lowbit(i))
		smt_del(root[i],1,t,val);
}
int bit_query(int l,int r,int val){
	memset(tmp,0,sizeof tmp);
	cnt1=cnt0=0;
	for(int i=r;i;i-=lowbit(i))
		tmp[1][++cnt1]=root[i];
	for(int i=l-1;i;i-=lowbit(i))
		tmp[0][++cnt0]=root[i];
	return smt_query(1,t,val);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[++t]=a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].ch;
		if(q[i].ch=='C'){
			cin>>q[i].x>>q[i].y>>q[i].k;
			b[++t]=q[i].k;
		}
		else{
			cin>>q[i].x>>q[i].k;
			b[++t]=q[i].k;
		}
	}
	sort(b+1,b+t+1);
	t=unique(b+1,b+t+1)-b-1;
	for(int i=1;i<=n;i++)
		bit_ins(i,get(a[i]));
	for(int i=1;i<=m;i++)
		if(q[i].ch=='C')
			cout<<bit_query(q[i].x,q[i].y,get(q[i].k))<<'\n';
		else{
			bit_del(q[i].x,get(a[q[i].x]));
			a[q[i].x]=q[i].k;
			bit_ins(q[i].x,get(a[q[i].x]));
		}
}
```

---

## 作者：Hisaishi_Kanade (赞：2)

~~蒟蒻的第一道分块题，好激动~~

### 一、题意

对于一个序列 $\{a_n\}$，有两种操作。

1. $a_i\to x$；
2. 问 $[l,r]$ 区间中有多少个 $a_i\le k$。

### 二、思路

某位学长和我说：

> 做题目先看数据范围，这很可能提示了做法。

比如这道题。$n\le10^5$ 同时 $Q\le 5\times 10^4$。

考虑到区间操作，然后数据范围正好符合 $n\sqrt n$，那我们就可以快乐的使用分块了！
- - -
分块是什么？简而言之，优雅的暴力。

考虑原始暴力是如何处理区间操作的？

例如区间加操作，原始的暴力会从 $l$ 循环到 $r$，给修改每个数。而分块，将 $n$ 个数分割成 $\sqrt n$ 个块，如果整个块都在要加的区间里，打上标记；剩下的一部分不成整块的，使用原始暴力的方法处理。

显然看出，原始暴力为 $O(n)$，而分块达到了 $O(\sqrt n)$！

至于单点修改，直接 $O(1)$ 处理不就行了。

- - -

看本题要求的操作，很容易得到处理方法：

1. 先把原序列分块。
2. 对每个块**排序**。
3. 单点修改时，将原序列的值改掉，再把这个值所在块覆盖上去，并排序。
4. 区间查询时，由于区间**有序**，可以使用二分优化。

### 三、代码

```cpp
#include <math.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
char opt;
int n,q,cnt,x,y,len,i,j,k,ans,dep,siz;
int l[10000],r[10000];
vector<int> g[10000];
int own[1000005],s[1000005];
int main(){
    scanf("%d",&n);
    cnt=n/(len=int(sqrt(n)));//小小的压了行，len是块长，cnt是块数。
    for(i=1;i<=n;++i)
        scanf("%d",s+i);//读入原序列
    for(i=1;i<=cnt;++i){//得到每个区间的左端和右端。
    	l[i]=r[i-1]+1;
    	r[i]=n/cnt*i;
	}
    if(r[cnt]!=n){//如果还差一点没有划分，就多加一个块（n/int(sqrt(n))未必整除）。
        r[cnt+1]=n;
        l[cnt+1]=r[cnt]+1;
        ++cnt;
    }
    for(i=1;i<=cnt;++i){
        for(j=l[i];j<=r[i];++j){
            own[j]=i;
            g[i].push_back(s[j]);//收纳入块
        }
        sort(g[i].begin(),g[i].end());//将每个块排序
    }
    scanf("%d",&q);
    while(q--){
        scanf(" %c %d %d",&opt,&x,&y);
        if(opt==0){
            scanf("%d",&k);
            if(own[x]==own[y]){//如果两个在同一个块，直接for循环
                ans=0;
                for(i=x;i<=y;++i)
                    s[i]>=k&&++ans;//由于块长为根号n，此处复杂度不超过根号。
                printf("%d\n",ans);
            }else{
                ans=0;
                for(i=x;i<=r[own[x]];++i)
                    s[i]>=k&&++ans;
                for(i=l[own[y]];i<=y;++i)//两只小尾巴，同样暴力。
                    s[i]>=k&&++ans;
                for(i=own[x]+1;i<own[y];++i)
                    ans+=upper_bound(g[i].begin(),g[i].end(),k)-g[i].begin();//lower_bound找第一个大于等于的元素，并返回迭代器
                printf("%d\n",ans);
                //这一块的复杂度也是根号n
            }
        }else{//单点修改操作
            dep=own[x];
            siz=g[dep].size();
            s[x]=y;
            for(i=0,j=l[dep];i<siz;++i)//推平这个区间
                g[dep][i]=s[j++];//此处复杂度根号n
            sort(g[dep].begin(),g[dep].end());//此处复杂度log 根号n
        }
    }
    return 0;
}
```
总复杂度最坏时，就是每次都是区间修改，那么为 $q\sqrt n+\log \sqrt n$，最好就是每次都查询，为 $q\sqrt n$，显然能过。

再讲一两个小细节。
1. 读入单独一个字符时，使用 `getchar()` 可能会被 `\r` 搞错，所以是有风险的。可以使用读入字符串取第一个字符或是 `scanf(" %c",&c)`，这个空格就是让 `scanf` 过滤掉空白字符。效率和 `getchar()` 差不多。
2. 迭代器减迭代器返回的是整型，表示这个区间的元素个数。
3. 代码中使用 `vector` 是因为方便，不代表不能用二维数组写。

---

## 作者：OldVagrant (赞：2)

## 题意   
原题面其实已经挺简洁的了。   
[题意传送门](https://www.luogu.com.cn/problem/SP3261)   
~~蕉♂躁好评~~
## Solution   
考虑分块，块长为 $\sqrt{n}$，分块的同时建一个辅助数组，在辅助数组的每一块内排序，修改时把修改的位置所在的那一整块重新复制到辅助数组里并重新排序，查询时对于不足整块的小段暴力统计，整块的就二分去找第一个大于 $K$ 的位置，记为 $pos$，然后从这个块的左端点到 $pos-1$ 的所有数都满足条件。  
做完这个题建议做一下 [P2801 教主的魔法](https://www.luogu.com.cn/problem/P2801)，做法类似，二分的时候改一下即可。
## Code
```c
#include <bits/stdc++.h>
using namespace std;
#define ll int
#define rint register int
#define pc(x) putchar(x)
#define gc getchar
ll a[100001],t[100001],l[319],r[319],pos[100001],x,y,px,py,rx,ans,z;
inline ll read(){
	ll x=0;
	char ch=gc();
	while(!isdigit(ch)) ch=gc();
	while(isdigit(ch)) x=x*10+ch-48,ch=gc();
	return x;
}
inline void write(ll x){
	if(x>9) write(x/10);
	pc('0'+x%10);
}
int main(){
	ll n=read(),q=read(),len=sqrt(n),num=n/len;
	for(rint i=1;i<=num;i++) l[i]=r[i-1]+1,r[i]=r[i-1]+len;//l，r储存每个块的左右端点
	if(r[num]^n) ++num,l[num]=r[num-1]+1,r[num]=n;//如果最右边没有到n那么就要再开一块
	for(rint i=1;i<=num;i++){
		ll li=l[i],ri=r[i];
		for(rint j=li;j<=ri;j++) pos[j]=i,a[j]=read(),t[j]=a[j];//预处理每个位置所在的块的编号（pos数组），读入，复制到辅助数组
		sort(t+li,t+ri+1);//块内排序
	}while(q--){
		char tp=gc();
		while(tp!='C'&&tp!='M') tp=gc();
		if(tp=='M'){//修改
			x=read(),y=read(),px=pos[x],rx=r[px],a[x]=y;
			for(rint i=l[px];i<=rx;i++) t[i]=a[i];//修改完重新复制
			sort(t+l[px],t+rx+1);//排序
		}else{
			x=read(),y=read(),z=read(),px=pos[x],py=pos[y],rx=r[px],ans=0;
			if(px<py){
				for(rint i=x;i<=rx;i++) if(a[i]<=z) ++ans;//左边不足整块暴力统计
				for(rint i=px+1;i<py;i++) ans+=upper_bound(t+l[i],t+r[i]+1,z)-t-l[i];//中间对每个块二分统计
				for(rint i=l[py];i<=y;i++) if(a[i]<=z) ++ans;//右边不足整块暴力统计
			}else for(rint i=x;i<=y;i++) if(a[i]<=z) ++ans; //不足整块暴力统计
			write(ans),pc('\n');
		}
	}return 0;
}
```


---

## 作者：一铭君一 (赞：1)

# SP 3261 RACETIME

快 NOIp 了，发篇题解祝自己 rp++，退役快乐！

看到题解区众大佬都是写的树套树或者是在线的分块算法。

蒟蒻不会，于是写了一种离线的做法，权当抛砖引玉了。

## 解题思路

一看就是典型的数据结构题，区间带修改查询值 $k$ 的排名。

线段树套平衡树可以或者树状数组套主席树都可以解决这个问题，不过我在这里用了一种 $O(n^{1.5}+n\sqrt n)$ 的带修莫队做法。

使用带修莫队可以解决区间查询和修改，我们只需要存下每个询问然后排序，移动 `l,r,t` 指针依次回答问题就可以了，这很简单。

难的是如何高效的维护莫队的转移以及查询 $k$ 的排名。

假设带修莫队 `l,r,t` 三个指针每移动一次花费 $O(T)$ 的时间，查询一次 $k$ 的排名花费 $O(Q)$ 的时间，那么总复杂度就是 $O(Tn^{1.5}+Qn)$ 。

如果使用 `std::set` 来维护莫队的话，$T,Q$ 都是 $\log$ 级别，这样仅仅 $O(n^{1.5}\log n+n\log n)$ 实在太慢了，不可以接受。

发现其实这个算法的复杂度瓶颈在于转移，也就是 $T$ 的级别。只要我们的转移操作快一点，整个算法效率就会提高。

这时，我们需要用到另一种数据结构——值域分块。

简单来说，你可以把「值域分块」看成一种可以 $O(1)$ 插入删除，$O(\sqrt n)$ 实现 `std::set` 的所有功能的一种数据结构。它的内部实现是利用分块的「大段维护，小段暴力」的思想去维护一个桶。

如果不知道什么是值域分块，可以看[我写的博客](https://www.cnblogs.com/zaza-zt/p/15041167.html)。

实际上，带修莫队+值域分块的效率是可以吊打大多数树套树的（截止到 NOIp 2021 前，我的带修莫队还是洛谷树套树板子的次优解）。

那么总复杂度 $O(n^{1.5}+n\sqrt n)$，上代码！

```cpp
const int maxn=200003;
const int maxm=5003;

int n,Q,it;
int A[maxn],B[maxn];

int len,tot;
int bel[maxn],L[maxm],R[maxm];
int num[maxm],cnt[maxn];

int Qnum;
struct Query{
	int l,r,t,k,org;
}q[maxn];
inline bool operator <(const Query a,const Query b){
	return bel[a.l]^bel[b.l] ? bel[a.l]<bel[b.l] : (bel[a.r]^bel[b.r] ? a.r<b.r : a.t<b.t);
}

int Mnum;
struct Modify{
	int pos,val;
}m[maxn];

void Init(){
	read(n),read(Q);
	len=pow(n,0.66);
	for(int i=1;i<=n;++i){
		bel[i]=(i-1)/len+1;
		B[++it]=read(A[i]);
	}
	for(int i=1;i<=Q;++i){
		char opt[2];
		scanf("%s",opt);
		if(opt[0]=='C'){
			Qnum++;
			q[Qnum].t=Mnum,q[Qnum].org=Qnum;
			read(q[Qnum].l),read(q[Qnum].r);
			B[++it]=read(q[Qnum].k);
		}else{
			Mnum++;
			read(m[Mnum].pos);
			B[++it]=read(m[Mnum].val);
		}
	}
	//读入所有询问和修改

	std::sort(B+1,B+1+it);
	it=std::unique(B+1,B+it+1)-B-1;
	for(int i=1;i<=n;++i)
		A[i]=std::lower_bound(B+1,B+it+1,A[i])-B;
	for(int i=1;i<=Qnum;++i)
		q[i].k=std::lower_bound(B+1,B+it+1,q[i].k)-B;
	for(int i=1;i<=Mnum;++i)
		m[i].val=std::lower_bound(B+1,B+it+1,m[i].val)-B;
	//离散化

	std::sort(q+1,q+Qnum+1);
	//排好序，重复利用 bel[],len 等变量

	len=sqrt(it);
	tot=it/len;
	for(int i=1;i<=it;++i)
		bel[i]=(i-1)/len+1;
	for(int i=1;i<=tot;++i){
		if(i*len>it) break;
		L[i]=(i-1)*len+1;
		R[i]=i*len;
	}
	if(R[tot]<it)
		++tot,L[tot]=R[tot-1]+1,R[tot]=it;
	//初始化值域分块
}

inline void add(const int x){
	++cnt[x];
	++num[bel[x]];
}
inline void del(const int x){
	--cnt[x];
	--num[bel[x]];
}
inline void change(const int now,const int x){
	if(q[x].l<=m[now].pos && m[now].pos<=q[x].r)
		add(m[now].val),del(A[m[now].pos]);
	_swap(m[now].val,A[m[now].pos]);
}

int GetNum(const int k){
	int sum=0,i=1;
	while(R[i]<k){
		sum+=num[i];
		++i;
	}
	for(int j=L[i];j<=k;++j)
		sum+=cnt[j];
	return sum;
}

int ans[maxn];

signed main(){
	// freopen("data.in","r",stdin);
	// freopen("work.out","w",stdout);
	Init();
	int l=1,r=0,now=0;
	for(int i=1;i<=Qnum;++i){
		while(l<q[i].l) del(A[l++]);
		while(l>q[i].l) add(A[--l]);
		while(r<q[i].r) add(A[++r]);
		while(r>q[i].r) del(A[r--]);
		while(now<q[i].t) change(++now,i);
		while(now>q[i].t) change(now--,i);
		ans[q[i].org]=GetNum(q[i].k);
	}
	for(int i=1;i<=Qnum;++i)
		write(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：HYdroKomide (赞：1)

数据过水，建议降蓝。

### 题意：
一个序列，两种操作：
1. 单点修改。
2. 区间 $\le k$ 个数。

### 思路：
这题时限较大，我们用分块可以比较暴力地解出来。

开一个 vector $b_i$ 来存第 $i$ 个块排序后的结果。对于每次操作：

1. 单点修改：先更改原数列上的值，然后将此区间的 $b_i$ 清空，再依次推入 $a_i$。（常数极大）

2. 区间 $\le k$：如果左右端点在同一块中，直接暴力。不在同一块中时，对于左右侧零散块暴力，中间大段使用 STL自带的 upper_bound 对每块有序的 $b$ 进行二分即可。

时间复杂度：$O(q\sqrt n\log n)$。

### 程序如下：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#define rll register long long
using namespace std;
const int N=1e5+1,sq=320;
long long n,q,rt,a[N],st[sq],ed[sq],belong[N],x,y,k,ans;
char op;
vector<long long>b[sq];
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>q;
    rt=sqrt(n);
    for(rll i=1;i<=n;i++)cin>>a[i];
    for(rll i=1;i<=rt;i++){
    	st[i]=ed[i-1]+1;
    	ed[i]=n/rt*i;
	}
	ed[rt]=n;//初始化区间左右端点
	for(rll i=1;i<=rt;i++){
		for(rll j=st[i];j<=ed[i];j++){
			belong[j]=i;
			b[i].push_back(a[j]);
		}
		sort(b[i].begin(),b[i].end());//初始化排好序的b
	}
	while(q--){
		cin>>op>>x>>y;
		ans=0;
		if(op=='C'){//查询操作
			cin>>k;
			if(belong[x]!=belong[y]){
				for(rll i=x;i<=ed[belong[x]];i++)
					if(a[i]<=k)//零散块暴力
						ans++;
				for(rll i=st[belong[y]];i<=y;i++)
					if(a[i]<=k)
						ans++;
				for(rll i=belong[x]+1;i<belong[y];i++)ans+=upper_bound(b[i].begin(),b[i].end(),k)-b[i].begin();//大块二分
			}
			else//在同一块中直接暴力
				for(rll i=x;i<=y;i++)
					if(a[i]<=k)
						ans++;
			cout<<ans<<"\n";
		}
		else{//单点修改
			a[x]=y;//先修改原数组
			b[belong[x]].clear();//清空这块的b
			for(rll i=st[belong[x]];i<=ed[belong[x]];i++)b[belong[x]].push_back(a[i]);//再将这块里的a一个一个推入
			sort(b[belong[x]].begin(),b[belong[x]].end());//再次排序
		}
	}
    return 0;
} 
```

### THE END

附赠：

[UVA12003（双倍经验）](https://www.luogu.com.cn/problem/UVA12003)

[SP3266（不带修改）](https://www.luogu.com.cn/problem/SP3266)

[SP23776（不带修改，在线）](https://www.luogu.com.cn/problem/SP23776)

---

## 作者：zyh888 (赞：0)

[P2801](https://www.luogu.com.cn/problem/P2801) [SP18185](https://www.luogu.com.cn/problem/SP18185) [UVA12003](https://www.luogu.com.cn/problem/UVA12003) [SP3261](https://www.luogu.com.cn/problem/SP3261) ~~四倍经验~~

# 题意
给定一个序列，两个操作：单点修改和区间查询。

# 思路
对于这种不满足区间加的区间查询，我们首先考虑分块。

将每 $\sqrt{n}$ 个数分成一个块，如果剩下几个数，就把它们分到最后一个块中。

对于操作二，我们开一个辅助数组，先将这个辅助数组的每个块内排好序。将不在整块的数处理了，在整块里的，二分出块内第一个小于等于 $k$ 的数，减去这个块的左端点，就是这个块对答案的贡献。

对于操作一，不仅要将原数组的 $A_{i}$ 修改，也要在辅助数组中找到 $A_{i}$，将其修改，再将辅助数组排好序，为了下次查询整块区间更方便。（看代码更好理解些）
# code
```cpp
#include<bits/stdc++.h>
#define int long long 
const int N=5*1e5+10;
using namespace std;
int w[N],b[N],kuai[N]; //w是原数组，b是辅助数组，kuai[i]代表第i个元素在第几块
int l[N],r[N]; //每个区间的左右端点
int n,m,u,len,k;
int query(int x,int y,int v){ 
	int res=0;
	if(kuai[x]==kuai[y]){		
		for(int i=x;i<=y;i++) if(w[i]<=v) res++;
		return res; //块内直接暴力
	}
	for(int i=x;i<=r[kuai[x]];i++) if(w[i]<=v) res++; 
	for(int i=l[kuai[y]];i<=y;i++) if(w[i]<=v) res++; //不在一整块的直接暴力
	for(int i=kuai[x]+1;i<=kuai[y]-1;i++) 
		res+=(upper_bound(b+l[i],b+r[i]+1,v)-b)-l[i]; //每个完整的块利用辅助数组的单调性求出答案
	return res; 
}
void change(int hh,int v){
	int temp=w[hh];
	w[hh]=v; //原数组修改
	for(int i=l[kuai[hh]];i<=r[kuai[hh]];i++){ 
		if(b[i]==temp){ //在辅助数组中寻找 w[i],并将它修改
			b[i]=v;
			break;
		}
	}
	sort(b+l[kuai[hh]],b+r[kuai[hh]]+1);
}
signed main(){ 
	scanf("%lld%lld",&n,&m); 
	len=(int)sqrt(n);
	k=n/len;
	for(int i=1;i<=k;i++) l[i]=(i-1)*len+1,r[i]=l[i]+len-1;
	r[k]=n;
	for(int i=1;i<=k;i++) 
		for(int j=l[i];j<=r[i];j++) kuai[j]=i; //分块
	for(int i=1;i<=n;i++){
		scanf("%lld",&w[i]);
		b[i]=w[i];
	}
	for(int i=1;i<=k;i++) sort(b+l[i],b+r[i]+1); //辅助数组按块排序
	while(m--){
		char op[2];
		int x,y,v;
		scanf("%s%lld%lld",op,&x,&y);
		if(op[0]=='C'){
			scanf("%lld",&v);
			printf("%lld\n",query(x,y,v));
		}else change(x,y);
	}	
	return 0;
}
```

---

## 作者：红尘仙 (赞：0)

### 前序 

这道题一点都不卡常，好评耶！

### Description : 

给定一个序列，进行 $m$ 次操作，操作包含单点修改，查询区间 $\leq k$ 数的个数。

### Solution : 

鄙人写的是分块，对于树套树大佬，我只能 %%% 。

这道题是一点的都不卡分块，所以说写分块是很妙的选择。

#### Subtask 1：

首先先来到操作 2 ,我们可以用一个 `vector` 去存储一个块，并对其中的元素排个序，然后我们不必 $O(\sqrt n)$ 的去扫，直接二分找答案即可。


#### Subtask 2：

再来到操作 1 ，我们直接单点修改。

这时候我们可以直接进行单点修改，就是 $A_i = k$，直接赋值即可。但是同时这样会破坏我们维护的单调性。那么我们需要重新将这个块清空，重新维护吗？ 

显然不需要，我完全可以打一个 $tag_k$ 表示 $i$ 所在的块 $k$ 被更改过了，直到询问的时候在进行更改。

#### Subtask 3：

这个是有点多余了，这个就是因为我对某一个块进行了标记，所以这时候我需要将修改过的序列 $a$ 重新压入 `vector` 中，并排序维护单调性。

单独拿出来用于理解。

### Code ：

块长直接取 $\sqrt n$ 即可。

```
//
/*
Author : Zmonarch
Knowledge :
*/
#include <bits/stdc++.h>
#define inf 2147483647
#define qwq register
#define qaq inline
#define int long long
using namespace std ;
const int kmaxn = 1e6 + 10 ;
qaq int read() {
	int x = 0 , f = 1 ; char ch = getchar() ;
	while(!isdigit(ch)) {if(ch == '-') f = - 1 ; ch = getchar() ;}
	while( isdigit(ch)) {x = x * 10 + ch - '0' ; ch = getchar() ;}
	return x * f ;
}
int n , m , len ; 
int pos[kmaxn] , a[kmaxn] , tag[kmaxn] ;
vector<int> block[kmaxn] ; 
qaq void update(int u) {
	block[u].clear() ; tag[u] = 0 ; 
	for(qwq int i = (u - 1) * len + 1 ; i <= u * len ; i++) 
	block[u].push_back(a[i]) ; sort(block[u].begin() , block[u].end()) ; 
}
qaq void Modify(int u , int val) {
	a[u] = val ; tag[pos[u]] = 1 ; 
}
qaq int Query(int L , int R , int val) {
	int p = pos[L] , q = pos[R] , ret = 0 ;  
	if(tag[p]) update(p) ; 
	for(qwq int i = L ; i <= min(p * len , R) ; i++) 
	 if(a[i] <= val) ret++ ; 
	if(p != q) 
	{
		if(tag[q]) update(q) ; 
		for(qwq int i = (q - 1) * len + 1 ; i <= R ; i++) 
	  	 if(a[i] <= val) ret++ ; 
	}
	for(qwq int i = p + 1 ; i <= q - 1 ; i++) 
	{
		if(tag[i]) update(i) ; 
		ret += upper_bound(block[i].begin() , block[i].end() , val) - block[i].begin() ;
	}
	return ret ; 
}
signed main() {
	n = read() , m = read() ; len = sqrt(n) ; 
	for(qwq int i = 1 ; i <= n ; i++) a[i] = read() ; 
	for(qwq int i = 1 ; i <= n ; i++) 
	{
		pos[i] = (i - 1) / len + 1 ; 
		block[pos[i]].push_back(a[i]) ; 
	}
	for(qwq int i = 1 ; i <= pos[n] ; i++) sort(block[i].begin() , block[i].end()) ; 
	for(qwq int i = 1 ; i <= m ; i++) 
	{
		char opt ; cin >> opt ; int x = read() , y = read() ; 
		if(opt == 'M') Modify(x , y) ;
		else printf("%lld\n" , Query(x , y , read())) ; 
	}
	return 0 ;
}

```

---

## 作者：银河AI (赞：0)

这里提一句，这道题与[P2801 教主的魔法](https://www.luogu.com.cn/problem/P2801)有异曲同工之妙

建议做完那道题再回来做这道题，相当于双倍经验

### 解题思路

 $M$ 操作，相信分块的单点修改大家都已经很熟悉了。
 
 $C$ 操作，我们另开一个 $b$ 数组，存储每个块排序后的结果，所以我们单点修改后需要重新对 $b$ 赋值。
 
 那么如何查询 $\le k$ 的值呢？
 我们考虑二分
 
 我们知道有个函数叫 $upper$_$bound$ 是用来查询一个序列里面大于查找值的指针位置
 
 那我们该如何用代码解决$\le k$ 的值呢？
 
 ```cpp
	int l=st[i],r=ed[i],sum=0;
	sum=upper_bound(b+l,b+r+1,z)-b-l;
	ans+=sum;
```
其中 $st[i]$ 和 $ed[i]$ 表示这个块的头和尾

接下来就放 $AC$ 代码了啦~

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1; 
int n,q;
int a[N],b[N],lazy[N];
int bel[N],st[N],ed[N];
inline int read(){
	int s=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return s*f;
}
inline char getch(){
	char ch=getchar();
	while(ch<'A'||ch>'M') ch=getchar();
	return ch;
}
inline void init(){
	int block=sqrt(n);
	int len=ceil((double)n/block);
	for(register int i=1;i<=len;i++){
		for(register int j=(i-1)*block+1;j<=i*block;j++)
			bel[j]=i;
		st[i]=(i-1)*block+1,ed[i]=i*block;
		if(i==len) ed[len]=n;
		sort(b+st[i],b+ed[i]+1);
	}
}
inline void add(int x,int y,int z){
	if(bel[x]==bel[y]){
		for(register int i=x;i<=y;i++) a[i]=z;
		for(register int i=st[bel[x]];i<=ed[bel[x]];i++) b[i]=a[i];
		sort(b+st[bel[x]],b+ed[bel[x]]+1);
		return ;
	}
}
inline void ask(int x,int y,int z){
	int ans=0;
	if(bel[x]==bel[y]){
		for(register int i=x;i<=y;i++)
			if(a[i]<=z) ans++;
	}	
	else{
		for(register int i=x;i<=ed[bel[x]];i++) if(a[i]<=z) ans++;
		for(register int i=st[bel[y]];i<=y;i++) if(a[i]<=z) ans++;
		for(register int i=bel[x]+1;i<bel[y];i++){
			int l=st[i],r=ed[i],sum=0;
			sum=upper_bound(b+l,b+r+1,z)-b-l;
			ans+=sum;
		}	
	}
	printf("%d\n",ans);
}
char k;
int x,y,z;
int main(){
	n=read(),q=read();
	for(register int i=1;i<=n;i++) a[i]=read(),b[i]=a[i];
	init();
	while(q--){
		k=getch();x=read(),y=read();
		if(k=='M') add(x,x,y);
		else z=read(),ask(x,y,z);	
	}
}
```

好啦~

管理员大大求通过 $awa$

---

## 作者：syzf2222 (赞：0)

第一眼看到这道题，第一反应是线段树。

考虑维护区间极值，然而无情的TLE了……

然后拿出终极武器：分块。

考虑分为$\sqrt n$个块，思考再整块中如何处理答案。

考虑将每个块单独拿出排序，

然后一个二分即可。

边缘块课单独处理，注意每次处理完要重新排序。

复杂度为$O(q\sqrt n\log n)$

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
int n,m,len,a[maxn],b[maxn];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
inline char getc(){
	char c=getchar();
	while(c<'A'||c>'Z')c=getchar();
	return c;
}
int lft[maxn],rht[maxn];
inline void add(int l,int r){
	a[l]=r;for(int i=lft[l/len];i<=rht[l/len];i++)b[i]=a[i];
	sort(b+lft[l/len],b+rht[l/len]+1);
}
inline int divide(int l,int r,int c){
	int ans=l-1,tmp=l;
	while(l<=r){
		int mid=(l+r)>>1;
		if(b[mid]<c)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans-tmp+1;
}
inline int query(int l,int r,int c){
	int ans=0;
	for(int i=l;i<=r&&i<=rht[l/len];i++)
		if(a[i]<c)ans++;
	if(r<=rht[l/len])return ans;
	for(int i=l/len+1;i<=n/len&&rht[i]<r;i++)
		ans+=divide(lft[i],rht[i],c);
	for(int i=lft[r/len];i<=r;i++)
		if(a[i]<c)ans++;
	return ans;
}
signed main(){
	n=read(),m=read();len=sqrt(n)+1;
	for(int i=1;i<=n;i++)
		b[i]=a[i]=read();
	int opt,l,r,c;
	for(int i=0;i<=n/len;i++){
		lft[i]=i*len;if(!lft[i])lft[i]=1;
		rht[i]=(i+1)*len-1;if(rht[i]>n)rht[i]=n;
		sort(b+lft[i],b+rht[i]+1);
	}
	for(int i=1;i<=m;i++){
		opt=getc(),l=read(),r=read();
		if(opt=='M')add(l,r);
		else c=read(),printf("%lld\n",query(l,r,c+1));
	}
	return 0;
}
```

---

## 作者：RiverFun (赞：0)

先推广一波 [$\texttt{BOLG}$](https://stevebraveman.github.io/)

其实这道题就是[这道题](https://loj.ac/problem/6278)变一下，把区间修改变成了单点修改，然后把小于变成小于等于。

所以就是分块，对于每个块开个vector存一下，再排序，修改后暴力重构整个块，然后二分就行了。

所以时间复杂度应该是 $O(n \sqrt{n \times \log{n}} )$

Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define MAXN 100010
int a[MAXN], b[MAXN], t[MAXN];
std::vector<int> ve[350];
int n, sq, l, r, c, m;
char op[5];
int min(int a, int b) {
	if (a < b) return a;
	else return b;
}
void reset(int l) {
	ve[l].clear();
	for (int i = (l - 1) * sq + 1; i <= min(l * sq, n); i++) {
		ve[l].push_back(a[i]);
	}
	sort(ve[l].begin(), ve[l].end());
}
void upd(int x, int y) {
	a[x] = y;
	reset(b[x]);
}
int sum(int l, int r, int k) {
	int ans = 0;
	for (int i = l; i <= min(b[l] * sq, r); i++) {
		if (a[i] <= k) ans++;
	}
	if (b[l] != b[r]) {
		for (int i = (b[r] - 1) * sq + 1; i <= r; i++) {
			if (a[i] <= k) ans++;
		}
	}
	for (int i = b[l] + 1; i <= b[r] - 1; i++) {
		ans += std::upper_bound(ve[i].begin(), ve[i].end(), k) - ve[i].begin();
	}
	return ans;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	sq = sqrt(n);
	for (int i = 1; i <= n; i++) {
		b[i] = (i - 1) / sq + 1;
		ve[b[i]].push_back(a[i]);
	}
	for (int i = 1; i <= b[n]; i++) {
		std::sort(ve[i].begin(), ve[i].end());
	}
	for (int i = 1; i <= m; i++) {
		scanf("%s", op);
		if (op[0] == 'C') {
			scanf("%d%d%d", &l, &r, &c);
			printf("%d\n", sum(l, r, c));
		}
		else {
			scanf("%d%d", &l, &r);
			upd(l, r);
		}
	}
}
```

---

