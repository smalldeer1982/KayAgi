# Sabbat of the witch

## 题目背景

您正在在游玩《魔女的夜宴》,突然开始思考一个哲学问题:这作的restart线到底算不算ntr？

![](http://0d077ef9e74d8.cdn.sohucs.com/rcLQDT4_png)

![](http://0d077ef9e74d8.cdn.sohucs.com/rcLQJyV_png)

![](http://0d077ef9e74d8.cdn.sohucs.com/rcLQMrk_png)
~~您在思索了很长时间之后,突然注意到这是个涉及到时间线和人格同一性的哲学问题~~

此时您突然发现galgame和数(毒)据(瘤)结(分)构(块)有一些奥妙重重的关系，为了更好的思考这个问题，您决定去写一道数(毒)据(瘤)结(分)构(块)题

## 题目描述

维护一个序列,支持以下三种操作

1.区间赋值

2.区间求和

3.撤回之前的一个区间赋值操作

**强制在线**

注意：这里的撤回操作既不会影响之前的操作也不会影响之后的操作，换句话讲撤回一个操作之后序列将会变成历史上从来没有过被撤回操作的状态

煮个栗子，假设我们对序列按顺序执行了1,2,3,4,5号操作

当我们撤回操作4的时候，整个序列应该和按顺序执行了1,2,3,5操作之后的序列一样

当我们接着撤回操作2的时候，整个序列应该和按顺序执行了1,3,5操作之后的序列一样







## 说明/提示

对于第9,10个测试点,满足$n,m \leq 10^4$，这两个测试点的分数都为1

对于剩余的测试点$n,m \leq 10^5$并且操作1的个数不超过$65000$

保证输入的数字全部小于$10^9$

## 样例 #1

### 输入

```
20 20
8 6 4 9 9 8 5 5 7 9 8 8 5 8 2 2 2 1 9 4 
1 17 19 4
1 3 8 5
3 2
2 4 10
1 14 19 8
2 10 16
2 9 9
1 1 18 1
1 1 7 10
2 4 6
2 9 10
1 5 17 2
1 10 19 6
1 2 5 2
1 6 8 2
1 14 19 1
1 4 7 6
1 17 19 10
2 8 12
1 10 10 2
```

### 输出

```
52
54
7
30
2
22
```

## 样例 #2

### 输入

```
20 20
8 6 4 9 9 8 5 5 7 9 8 8 5 8 2 2 2 1 9 4 
1 17 19 4
1 3 8 5
3 2
2 4 10
1 58 39 8
2 62 36
2 63 63
1 6 21 1
1 6 0 10
2 3 1
2 23 20
1 7 19 2
1 8 17 6
1 0 7 2
1 4 10 2
1 12 17 1
1 6 5 6
1 19 17 10
2 10 14
1 28 28 2
```

### 输出

```
52
54
7
30
2
22
```

# 题解

## 作者：TheLostWeak (赞：15)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/Luogu5113.html)

**大致题意：** 给你一个序列，要你支持三种操作：区间赋值，区间求和，撤回之前任一区间赋值操作。

------

## 分块

这道题应该是一道十分**毒瘤**的**分块**题。

这道题要用到的算法并不是很难，但是思维难度是真的高。

大致思路就是对于每一个块维护一大堆信息，各用一个栈存储对**每个块**的赋值操作，并开一个邻接表来存储对**每个元素**的赋值操作，防止$MLE$。

具体的操作方法见下。

------

## 区间赋值

对于不完整的块，我们用邻接表来更新这些元素的赋值操作，然后**重构**块（关于重构详见后文）。

对于完整的块，我们用邻接表来更新这个块的赋值操作，然后更新这个块的$ans$为**块的大小**$*$**赋的值**。

------

## 区间求和

对于不完整的块，我们暴力求解其答案。对于每一个元素要进行如下分类讨论：

- 如果该块没有被整块赋值过。则对于每个元素，我们判断其是否被赋值过，如果赋值过，将$res$加上最后一次赋的值，否则将$res$加上该元素的初始值。
- 如果该块被整块赋值过。则对于每个元素，我们选择**该块最后一次被赋值**与**该元素最后一次被赋值**这两种情况中较后一次所赋的值，然后将$res$加上这个值。

对于完整的块，我们直接加上该块的$ans$（$ans$会在每次操作中更新，因此一定是当前的答案）。

------

## 撤销区间赋值

这应该是最恶心的一个操作了。

我们可以用一个$flag$数组来标记每一个操作是否被撤销。

考虑每次撤销操作时，如果该元素/块在这一次操作之后还有未被撤销的赋值操作，则此次撤销其实对答案暂时是没有任何影响的。

因此，对于不完整的块，我们只要将每个元素邻接表中最后面的一些已被撤销的操作全部清空，然后重构块即可（关于重构详见后文）。

而对于完整的块，我们首先依然是将该块的栈顶已被撤销的操作全部清空，然后要依据重构块时所保留下来的一些信息来对$ans$进行修改。

由于重构的部分还未介绍，因此这一部分也放后面讲。

------

## 重构

块的重构应该也是这道题比较恶心的地方之一。

首先，我们要对块内每一个元素**最后一次被赋值的时间**进行一次**基数排序**。

这样一来，这些元素就按照最后一次被赋值的时间从小到大被排好序了。

然后，我们倒着对被赋的值求一次**后缀和**，用一个数组$res$来存储。

千万要注意的是，$res_i$存储的是从**第$i+1$个元素开始的后缀和**。

还有，一定要记得将$res_0$加上**所有未被修改过的元素的初始值**。

接下来，我们要使用两个变量$lst$和$p$，它们在后面的块内撤销操作中也会发挥作用。

我们用$lst$来记录当前**堆顶的元素值**，它的实际意义即为**最后一次整块修改的时间**。

然后，我们用$p$从$0$开始枚举，找到最后一个单个元素赋值时间小于$lst$的元素。

则显然，第$1\sim p$个元素的值都应是整块修改所赋的值，而第$p+1\sim Size$个元素都是按自己最后一次赋值所赋的值。

不难发现，前面一部分即为$p*$**整块最后一次修改所赋的值**，后面一部分即为$res_p$。

这样就能更新$ans$了。

------

## 块内撤销操作

首先我们要注意到一个性质：在每次重构之前，所撤销的操作的编号肯定是**单调递减**的。

因此我们就可以使用之前重构时保留下来的$lst$和$p$两个变量，继续进行操作。

我们先判断当前栈顶的元素是否大于$lst$。

如果大于$lst$，则说明在重构之后又进行过整块修改，而这次整块修改肯定是覆盖块内所有元素的。

所以可以直接更新$ans$为**块的大小**$*$**赋的值**，然后退出函数。

否则，我们就要将$p$向前移，和之前的操作差不多刚好相反，找到最后一个单个元素赋值时间小于当前堆顶的元素。

然后按照上面的方法，更新$ans$为$p*$**整块最后一次修改所赋的值**$+res_p$。

------

## 代码

```cpp
#include<bits/stdc++.h>
#define N 100000
#define SqrtN 400
#define LL long long
using namespace std;
LL n,a[N+5],ql[N+5],qr[N+5],qv[N+5],flag[N+5];
class Class_FIO
{
    private:
        #define Fsize 100000
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,Fsize,stdin),A==B)?EOF:*A++)
        #define pc(ch) (FoutSize<Fsize?Fout[FoutSize++]=ch:(fwrite(Fout,1,Fsize,stdout),Fout[(FoutSize=0)++]=ch))
        #define Ftemp template<typename I>
        int Top,FoutSize;char ch,*A,*B,Fin[Fsize],Fout[Fsize],Stack[Fsize];
    public:
        Class_FIO() {A=B=Fin;}
        Ftemp inline void read(I &x) {x=0;while(!isdigit(ch=tc()));while(x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));}
        Ftemp inline void writeln(I x) {while(Stack[++Top]=x%10+48,x/=10);while(Top) pc(Stack[Top--]);pc('\n');}
        inline void clear() {fwrite(Fout,1,FoutSize,stdout),FoutSize=0;}
}F;
class Class_List//邻接表，存储对每个元素的赋值操作
{
    private:
        #define LIST_SIZE N*SqrtN
        LL cnt,lnk[N+5],val[LIST_SIZE+5],nxt[LIST_SIZE+5];
    public:
        inline void Add(LL x,LL v) {nxt[++cnt]=lnk[x],val[lnk[x]=cnt]=v;}
        inline void Del(LL x) {while(lnk[x]&&flag[val[lnk[x]]]) lnk[x]=nxt[lnk[x]];}
        inline LL GetVal(LL x) {return val[lnk[x]];}
}List;
class Class_BlockSolver//存储每个块的信息
{
    private:
        #define BLOCK_SIZE SqrtN
        LL Bsize,Btot,bl[N+5];
        class Class_Block
        {
            private:
                #define BLOCK SqrtN
                LL p,ans,lst,Top,res[BLOCK+5],InitVal[BLOCK+5],s[BLOCK+5],g[BLOCK+5],cnt[256],Stack[N+5];
                inline LL RadixSort()//基数排序
                {
                    register LL i,res=0;
                    for(i=1;i<=S;++i) !(s[i]=List.GetVal(L+i-1))&&(res+=InitVal[i]);
                    for(i=0;i<256;++i) cnt[i]=0;for(i=1;i<=S;++i) ++cnt[s[i]&255];for(i=1;i<256;++i) cnt[i]+=cnt[i-1];for(i=S;i;--i) g[cnt[s[i]&255]--]=s[i];
                    for(i=0;i<256;++i) cnt[i]=0;for(i=1;i<=S;++i) ++cnt[s[i]>>8];for(i=1;i<256;++i) cnt[i]+=cnt[i-1];for(i=S;i;--i) s[cnt[g[i]>>8]--]=g[i];
                    return res;
                }
            public:
                LL L,R,S;
                inline void Build(LL *data) {for(register LL i=1;i<=S;++i) res[0]+=(InitVal[i]=a[L+i-1]);ans=res[0];}//初始化
                inline void ReBuild()//重构
                {
                    register LL i,sum=RadixSort();
                    for(p=0,lst=Stack[Top],i=S-1;~i;--i) res[i]=res[i+1]+qv[s[i+1]];res[0]+=sum;
                    while(p<S&&s[p+1]<lst) ++p;ans=res[p]+1LL*p*qv[lst];
                }
                inline void Add(LL pos) {ans=1LL*S*qv[Stack[++Top]=pos];}//整块修改
                inline void Del()//整块撤销操作
                {
                    while(Top&&flag[Stack[Top]]) --Top;
                    if(Stack[Top]>lst) return (void)(ans=1LL*S*qv[Stack[Top]]);
                    while(p&&s[p]>=Stack[Top]) --p;ans=res[p]+1LL*p*qv[Stack[Top]];
                }
                inline LL BruteForce(LL l,LL r)//暴力求解答案
                {
                    register LL i,res=0;
                    if(Stack[Top]) for(i=l;i<=r;++i) res+=qv[max(List.GetVal(i),Stack[Top])];
                    else for(i=l;i<=r;++i) res+=List.GetVal(i)?qv[List.GetVal(i)]:InitVal[i-L+1];
                    return res;
                }
                inline LL GetAns() {return ans;}//返回答案
        }blk[BLOCK_SIZE+5];
    public:
        inline void Init()//初始化
        {
            register LL i;
            for(Bsize=sqrt(n),i=1;i<=n;++i) ++blk[bl[i]=(i-1)/Bsize+1].S;
            for(Btot=bl[n],i=1;i<=Btot;++i) blk[i].L=(i-1)*Bsize+1,blk[i].R=i*Bsize;blk[Btot].R=n;
            for(i=1;i<=Btot;++i) blk[i].Build(a);
        }
        inline void Modify(LL pos)//修改
        {
            register LL i,l=ql[pos],r=qr[pos],v=qv[pos];
            if(!(bl[l]^bl[r])) {for(i=l;i<=r;++i) List.Add(i,pos);return blk[bl[l]].ReBuild();}
            for(i=blk[bl[l]].R;i>=l;--i) List.Add(i,pos);blk[bl[l]].ReBuild();
            for(i=blk[bl[r]].L;i<=r;++i) List.Add(i,pos);blk[bl[r]].ReBuild();
            for(i=bl[l]+1;i<bl[r];++i) blk[i].Add(pos);
        }
        inline void CtrlZ(LL pos)//撤销修改
        {
            register LL i,l=ql[pos],r=qr[pos],v=qv[pos];
            if(!(bl[l]^bl[r])) {for(i=l;i<=r;++i) List.Del(i);return blk[bl[l]].ReBuild();}
            for(i=blk[bl[l]].R;i>=l;--i) List.Del(i);blk[bl[l]].ReBuild();
            for(i=blk[bl[r]].L;i<=r;++i) List.Del(i);blk[bl[r]].ReBuild();
            for(i=bl[l]+1;i<bl[r];++i) blk[i].Del();
        }
        inline LL Query(LL l,LL r)//询问
        {
            if(!(bl[l]^bl[r])) return blk[bl[l]].BruteForce(l,r);
            register LL i,res=blk[bl[l]].BruteForce(l,blk[bl[l]].R)+blk[bl[r]].BruteForce(blk[bl[r]].L,r);
            for(i=bl[l]+1;i<bl[r];++i) res+=blk[i].GetAns();
            return res;
        }
}B;
int main()
{
    register LL query_tot,i,cnt=0,op,x,y,ans=0;
    for(F.read(n),F.read(query_tot),i=1;i<=n;++i) F.read(a[i]);B.Init();
    while(query_tot--)
    {
        F.read(op);switch(op)
        {
            case 1:F.read(ql[++cnt]),F.read(qr[cnt]),F.read(qv[cnt]),ql[cnt]^=ans,qr[cnt]^=ans,B.Modify(cnt);break;
            case 2:F.read(x),F.read(y),F.writeln(ans=B.Query(x^ans,y^ans));break;
            case 3:F.read(x),flag[x^=ans]=1,B.CtrlZ(x);break;
        }
    }
    return F.clear(),0;
}
```

---

## 作者：critnos (赞：6)

看看题解发现 $O(n\sqrt n)$ 的老鸽还是比我多想一步啊。。

我的做法用基数排序实现可以 $O(n\sqrt{n\log n})$，不过用快排 $O(n\sqrt n \log n)$ 调调块长也过了。。

看到撤销操作就想到用栈了，我们对每个元素（以下称为点）和每块维护栈，按顺序保存这个东西经历过的 $1$ 操作，即栈中每个元素为 $(\text{时间戳},\text{推平值})$。

这样一，二操作就十分的简单了，维护每块的和。

对于三操作，首先要明确一点就是一个栈顶的值是代表这个东西的真实值。。

撤销当然不能（用平衡树）每次直接 erase，要用一个套路懒惰删除，即用一个数组标记每个操作是否被撤销。每次要把栈顶所有的被撤销的操作都 pop 掉，直到栈顶的操作未被撤销。由于每个操作最多被撤销一次，易得摊还时间复杂度是 $O(\sqrt n)$ 的。

散块撤销暴力即可。

整块撤销，对于点的真实值的时间戳小于该块的真实值的时间戳时，这个点最后是被推平的，值为该块的真实值的推平值。

对于点的真实值的时间戳大于该块的真实值的时间戳时，这个点最后被单点赋值的，值为这个点的真实值的推平值。

那么我们把点分为了两类，显然块内的和为（设每个点的时间戳为 $t_i$，推平值为 $v_i$，该块的时间戳为 $T$，该块的推平值为 $V$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/84qz5dql.png)

维护块内排序数组即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct op
{
	int ti,v;
	op(){}
	op(int ti_,int v_)
	{
		ti=ti_,v=v_;
	}
	friend bool operator <(const op &x,const op &y)
	{
		return x.ti<y.ti;
	}
};
const int bl=100;
stack<op> d[100005];
stack<op> k[100000/bl+5];
op st[100005];
int fl[100005],fr[100005];
int b[100005];
ll sum[100005];
bool del[100005];
int opl[100005],opr[100005];
int a[100005];
ll nxt[100005];
int lg;
void rebuild(int x)
{
	int i;
	for(i=fl[x];i<=fr[x];i++)
		st[i]=d[i].top();
	sort(st+fl[x],st+fr[x]+1);
	nxt[fr[x]]=st[fr[x]].v;
	for(i=fr[x]-1;i>=fl[x];i--)
		nxt[i]=nxt[i+1]+st[i].v;
}
void init(int n)
{
	int cnt=0,i,j;
	lg=log2(bl);
	for(i=1;i<=n;i+=bl)
		fl[++cnt]=i,fr[cnt]=min(i+bl-1,n);
	for(i=1;i<=cnt;i++)
	{
		k[i].push(op(0,0));
		for(j=fl[i];j<=fr[i];j++)
			b[j]=i,sum[i]+=a[j],d[j].push(op(0,a[j]));
		rebuild(i);
	}
}
int askw(int x)
{
	return k[b[x]].top().ti>d[x].top().ti?k[b[x]].top().v:d[x].top().v;
}
void add(int l,int r,int x,int ti)
{
	int i;
	if(b[l]==b[r])
	{
		for(i=l;i<=r;i++)
		{
			sum[b[l]]-=askw(i);
			d[i].push(op(ti,x));
		}	
		rebuild(b[l]);
		sum[b[l]]+=x*(r-l+1ll);
		return;
	}
	add(l,fr[b[l]],x,ti),add(fl[b[r]],r,x,ti);
	for(i=b[l]+1;i<b[r];i++)
		k[i].push(op(ti,x)),sum[i]=x*(fr[i]-fl[i]+1ll);
}
ll ask(int l,int r)
{
	ll s=0;
	int i;
	if(b[l]==b[r])
	{
		for(i=l;i<=r;i++)
			s+=askw(i);
		return s;
	}
	s=ask(l,fr[b[l]])+ask(fl[b[r]],r);
	for(i=b[l]+1;i<b[r];i++)
		s+=sum[i];
	return s;
}
int find(int x,int v)
{
	int w=fl[x]-1,i;
	for(i=1<<lg;i>=1;i>>=1)
		if(w+i<=fr[x]&&st[w+i].ti<v)
			w+=i;
	return w+1;
}
void rev(int l,int r,int ti)
{
	del[ti]=1;
	int i,w;
	if(b[l]==b[r])
	{
		for(i=l;i<=r;i++)
		{
			sum[b[l]]-=askw(i);
			while(del[d[i].top().ti])
				d[i].pop();
			sum[b[l]]+=askw(i);
		}
		rebuild(b[l]);
		return;
	}
	rev(l,fr[b[l]],ti),rev(fl[b[r]],r,ti);
	for(i=b[l]+1;i<b[r];i++)
	{
		while(del[k[i].top().ti])
			k[i].pop();
		w=find(i,k[i].top().ti);
		if(w<=fr[i])
			sum[i]=nxt[w];
		else sum[i]=0;
		sum[i]+=1ll*(w-fl[i])*k[i].top().v;
	}
}
int main()
{
	int n,m,i,l,r,x,opt,cnt=0;
	ll last=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	init(n);
	while(m--)
	{
		scanf("%d",&opt);
		if(opt==1)
			scanf("%d%d%d",&l,&r,&x),l^=last,r^=last,add(l,r,x,++cnt),opl[cnt]=l,opr[cnt]=r;
		if(opt==2)
			scanf("%d%d",&l,&r),l^=last,r^=last,printf("%lld\n",last=ask(l,r));
		if(opt==3)
			scanf("%d",&x),x^=last,rev(opl[x],opr[x],x);
	}
}
```


---

## 作者：EityDawn (赞：4)

### 题目大意

给定序列，需要支持三种区间操作：区间赋值，区间求和，撤销某一次赋值操作。

# 思路

一道小清新~~毒瘤~~的分块题。

每个块内主要维护以下信息：

1. 存储修改时间戳的栈。
2. 原来块内的初始值。
3. 按时间戳排序后的后缀和。

全局需要维护一个邻接表，来存储对散块修改的时间戳。

下面看三种操作：

## 区间赋值

设第 $i$ 次赋值操作修改的值为 $Val_i$，第 $i$ 个块的大小为 $Size_i$。

对于整块 $i$，直接将当前的时间戳，记为 $T$，存入栈内，整块答案更新为 $Size_i\times Val_T$。

对于散块而言，我们将 $T$ 存入该位置的邻接表，然后重构这个块。

### 重构

我们需要查询一遍每一个位置的时间戳。

按时间戳升序排序。

每个块内记录 $Last$，意为上一次整块赋值的最后一个时间戳，$Now$ 意为块内元素按照时间戳排序的最后一个时间戳小于 $Last$ 的位置。

那么对于大于 $Now$ 的位置，这一部分在领接表里查最后一次修改的时间戳，这一部分的和记为 $sum$，前半部分肯定都是整块赋值的值，整块的答案更新为 $sum+Now\times Val_{Last}$。

当然，如果这个块没有存储整块赋值的时间戳，如果单点没有经过赋值，记得加上初始时的权值。

## 区间询问

对于整块而言，我们的答案已经提前预处理了，直接累加。

对于散块，我们暴力查找，分两种情况。

如果这个块存储了整块赋值的时间戳，查询这个位置在领接表里最后的一次时间戳，取 $\max$，记为 $i$，那么就加上 $Val_i$。

反之，我们查询这个位置最后的一次时间戳，记为 $i$，找得到，答案加上 $Val_i$，否则加上这个位置的初始值。

## 撤销操作

此题的毒瘤之所在。

全局将撤销的这次操作的时间戳标记。

对于散块，直接在领接表里删除已经标记了时间戳，之后暴力重构这个块。

对于整块 $i$，先弹出栈顶被标记的时间戳。

我们在块内维护了 $Last$，这是上一次重构时我们记录的整块赋值操作的时间戳，将栈顶的时间戳记为 $St$，如果 $Last<St$，答案更新为 $Size_i\times Val_{St}$。

如果 $Last>St$，我们在块内维护了 $Now$，记录了上次重构时按照时间戳排序后最后一个时间戳小于 $Last$ 的位置，我们需要移动指针直至当前位置的时间戳小于 $St$，对于前面这一部分，上次重构处理的后缀和保持不变，后面一部分全部赋值为 $Val_{St}$，答案更新为 $Sum_{Now}+Now\times Val_{St}$。

## 复杂度分析

序列对 $B$ 分块，修改和撤销操作复杂度都为 $O(mB\log n+{mn\over B})$，查询复杂度为 $O(mB)$。

$n,m$ 同阶，可以认为总复杂度为 $O(nB\log n+{n^2\over B})$，但 $B$ 取 $\sqrt{n\over \log n}$ 时复杂度最优，为 $O(n\sqrt{n\log n})$。

实际上 $B$ 取 $\sqrt n$ 依旧轻松可过。

## code

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+10;
const int Len=200;
const int M=(N/Len)+1;
int bel[N],a[N];
bool del[N];//每次操作是否删除
ll Val[N],AL[N],AR[N],T=0;//赋值操作的信息
int Next[N*M],ID[N*M],Ink[N],Size=0;//邻接表存储单个元素的赋值时间戳
int n,m,t=0;
void Add(int now,int id)
{
    Next[++Size]=Ink[now];
    ID[Ink[now]=Size]=id;
    return;
}
void Del(int now)
{
    while(Ink[now]&&del[ID[Ink[now]]]) 
        Ink[now]=Next[Ink[now]];
    return;
}
struct Block{
    int Size,L=0,R=0;
    ll Ans=0;int Last,Now;//该块的答案;上一次该块的修改编号;单点最后一个小于 Last 的位置
    int top=0,St[N];//记录块的整块操作时间戳
    ll InitVal[M];//初始权值，撤销完之后如果没有赋值操作要用
    int dfn[M];//存储最后一次赋值的时间戳
    ll Sum[M];//存储按照时间排序后元素的后缀和
    void Init()
    {
        Size=R-L+1;
        for(int i=L;i<=R;i++) 
            InitVal[i-L+1]=a[i],Ans+=a[i];
        return void(Sum[0]=Ans);
    }
    void Add(int x){Ans=1ll*Size*Val[St[++top]=x];}//整块赋值操作
    void Del()//撤销块内的赋值操作
    {
        while(top&&del[St[top]]) --top;
        if(St[top]>Last) Ans=1ll*Size*Val[St[top]];
        else{
            while(Now>0&&dfn[Now]>=St[top]) --Now;
            Ans=Sum[Now]+Now*Val[St[top]];//找前面都为整块赋值的
        }
    }
    void Rebuild()//重构块
    {
        Ans=0;
        for(int i=1;i<=Size;i++) 
            dfn[i]=ID[Ink[i+L-1]],Ans+=((dfn[i]==0)*InitVal[i]);
        //重新计算时间戳
        sort(dfn+1,dfn+1+Size);
        Now=0,Last=St[top];
        for(int i=Size-1;~i;i--) Sum[i]=Sum[i+1]+Val[dfn[i+1]];Sum[0]+=Ans;
        while(Now<Size&&dfn[Now+1]<Last) ++Now;
        Ans=Sum[Now]+Now*Val[St[top]];
    }
    ll Calc(int l,int r)//散块查询
    {
        ll res=0;
        for(int i=l;i<=r;i++)
            res+=St[top]?Val[max(ID[Ink[i]],St[top])]:(ID[Ink[i]]?Val[ID[Ink[i]]]:InitVal[i-L+1]);
        return res;
    }
}B[M];
void Revoke(int l,int r)
{
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++) Del(i);
        B[bel[l]].Rebuild();
    }
    else{
        for(int i=l;i<=B[bel[l]].R;i++) Del(i);
        for(int i=B[bel[r]].L;i<=r;i++) Del(i);
        B[bel[l]].Rebuild(),B[bel[r]].Rebuild();
        for(int i=bel[l]+1;i<=bel[r]-1;i++) B[i].Del();
    }
}
void Modify(int l,int r)
{
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++) Add(i,T);
        B[bel[l]].Rebuild();
    }
    else{
        for(int i=l;i<=B[bel[l]].R;i++) Add(i,T);
        for(int i=B[bel[r]].L;i<=r;i++) Add(i,T);
        B[bel[l]].Rebuild(),B[bel[r]].Rebuild();
        for(int i=bel[l]+1;i<=bel[r]-1;i++) B[i].Add(T);
    }
}
ll query(int l,int r)
{
    ll res=0;
    if(bel[l]==bel[r]) res+=B[bel[l]].Calc(l,r);
    else{
        res+=B[bel[l]].Calc(l,B[bel[l]].R);
        res+=B[bel[r]].Calc(B[bel[r]].L,r);
        for(int i=bel[l]+1;i<=bel[r]-1;i++) res+=B[i].Ans;
    }
    return res;
}
void build(int n)
{
    int len=Len;t=n/len+bool(n%len);
    for(int i=1;i<=n;i++)
    {
        bel[i]=(i-1)/len+1;
        if(!B[bel[i]].L) B[bel[i]].L=i;
        B[bel[i]].R=i;
    }
    for(int i=1;i<=t;i++) B[i].Init();
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(n);
    int op;
    ll l,r,x;
    ll ans=0;
    while(m--)
    {
        cin>>op;
        if(op==1){
            ++T;
            cin>>AL[T]>>AR[T]>>Val[T];
            AL[T]^=ans,AR[T]^=ans;
            Modify(AL[T],AR[T]);
        }
        else if(op==2){
            cin>>l>>r;
            l^=ans,r^=ans;
            cout<<(ans=query(l,r))<<'\n';
        }
        else{
            cin>>x;del[x^=ans]=1;
            Revoke(AL[x],AR[x]);
        }
    }
    return 0;
}
```

---

