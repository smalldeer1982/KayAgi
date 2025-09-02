# GSS5 - Can you answer these queries V

## 题目描述

 You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| <= 10000 , 1 <= N <= 10000 ). A query is defined as follows: Query(x1,y1,x2,y2) = Max { A\[i\]+A\[i+1\]+...+A\[j\] ; x1 <= i <= y1 , x2 <= j <= y2 and x1 <= x2 , y1 <= y2 }. Given M queries (1 <= M <= 10000), your program must output the results of these queries.

## 样例 #1

### 输入

```
2
6 3 -2 1 -4 5 2
2
1 1 2 3
1 3 2 5
1 1
1
1 1 1 1```

### 输出

```
2
3
1```

# 题解

## 作者：energy2002 (赞：41)

大概可以算是线段树维护区间最大子段和的模板题了吧...

## 题意

对于长度为$n$的序列，回答$m$个询问，每个询问查询左端点在$[l_1,r_1]$之中,右端点在$[l_2,r_2]$之中的所有区间和的最大值，即：
$$\max_{l_1\leq l\leq l_2,r_1\leq r\leq r_2} \sum_{i=l}^{j} a[i]$$

( 其中保证$l_1\leq l_2;r_1\leq r_2;n,m,|a[i]|\leq 1E4$ ).

## solution:

## 0 如何建立线段树

### 0.0 节点信息
建立线段树时，对于每个节点，额外存储4个信息$pre,mid,suf,sum$；

详细信息如图：

![](https://cdn.luogu.com.cn/upload/pic/34790.png)

可以看出，父节点的$pre$可由其左儿子的$pre$或其左儿子的$sum$加右儿子的$pre$更新，在此情况中，父节点的$pre$由前者更新；

### 0.1 更新

类比父节点$pre$的更新方式，可以写出其$mid$与$suf$的更新方式：

（为了方便，我把这4个数据封装到一个struct中了...）

```cpp
struct trans{
    int pre,mid,suf,sum;
};
trans merge(trans s1,trans s2){
    trans ans;
    ans.pre=max(s1.pre,s2.pre+s1.sum);
    ans.mid=max(max(s1.mid,s2.mid),s1.suf+s2.pre);
    //父节点的mid要由3个数据更新
    ans.suf=max(s1.suf+s2.sum,s2.suf);
    ans.sum=s1.sum+s2.sum;
    //别忘了更新sum
    return ans;
}
```

而对于叶节点，在建树时顺便更改其数据即可，这样就可以很容易地写出建树的代码了:
```cpp
void build(int rt,int l,int r){
    p[rt].l=l;p[rt].r=r;
    if(l==r){
        p[rt].dat.pre=p[rt].dat.mid=p[rt].dat.suf=p[rt].dat.sum=dat[l];
        //我这里规定每个子序列不可以为空，如果这里规定序列可以为空，那相应的，查询时也应更改。
        return;
    }
    int mid=(l+r)/2;
    build(rt*2,l,mid);
    build(rt*2+1,mid+1,r);
    update(rt);
    return;
}
```
Tips：如果还没有写过这类问题，建议先做[GSS1](https://www.luogu.org/problemnew/show/SP1043)
## 1 区间最大字段和查询
与普通线段树差不多，此线段树的查询结果也由多个节点的值合并而成：
![](https://cdn.luogu.com.cn/upload/pic/34807.png)

如图，比如查询的区间是$[3,8]$，那么，查询的答案将由存储范围为$[3,4]$和$[5,8]$的两个区间合并而成；

我们不难发现，在建立线段树和查询时信息的合并方式是相同的，那么，我们也就可以很容易地写出查询的代码了:
```cpp
trans query_sub_max(int rt,int l,int r){
    if(l>r){
    //这个是为了防止之后的查询中出现的BUG用的
        return (trans){0,0,0,0};
    }
    if(p[rt].l==l&&p[rt].r==r){
        return p[rt].dat;
    }
    int mid=p[rt*2].r;
    if(r<=mid)return query_sub_max(rt*2,l,r);
    else if(l>mid)return query_sub_max(rt*2+1,l,r);
    //如果要查寻的区间没有跨越其中一个儿子的范围，直接返回即可
    return merge(query_sub_max(rt*2,l,mid),query_sub_max(rt*2+1,mid+1,r));
}
```
可以看出，查询一次的复杂度为$O(log(n))$
## 2 对左右端点有限制的区间的查询

本题对左右端点的范围有限制，不能一次查询出结果，于是可以考虑分情况多次查询：
### 2.1 两个区间没有交集的情况
![](https://cdn.luogu.com.cn/upload/pic/34817.png)

如图，可以看出，蓝框中的数是无论如何要选上的，为了最大化结果，只能最大化区间$[l_1,r_1]$与$[l_2,r_2]$的选中部分的和，所以，不难写出这种情况的代码：
```cpp
if(r1<l2){
    int tmp=query_sub_max(1,l1,r1).suf;
    //区间[l1,r1]的最大后缀和
    tmp+=query_sub_max(1,r1+1,l2-1).sum;
    //蓝框部分的和
    tmp+=query_sub_max(1,l2,r2).pre;
    //区间[l2,r2]的最大前缀和
    return tmp;
}
```
### 2.2 两个区间有交集的情况
而这种情况就比较复杂了，可分为3种情况，如图：
![](https://cdn.luogu.com.cn/upload/pic/34820.png)

我们可以发现，其实情况1与情况2是可以用同一种方式求出的，即区间$[l_1,l_2]$的$suf$+区间$[l_2,r_2]$的$pre$(或区间$[l_1,r_1]$的$suf$+区间$[r_1,r_2]$的$pre$);

而情况3就很好写了，只需求出区间$[l_2,r_1]$的$mid$即可；

**Tips: 注意特判区间$[l_1,r_1],[r_1,r_2]$是否存在,即$l_1$与$l_2$,$r_1$与$r_2$是否相等。**

代码如下：
```
int ans=query_sub_max(1,l2,r1).mid;
    if(l1<l2)ans=max(ans,query_sub_max(1,l1,l2).suf+query_sub_max(1,l2,r2).pre-dat[l2]);
	if(r2>r1)ans=max(ans,query_sub_max(1,l1,r1).suf+query_sub_max(1,r1,r2).pre-dat[r1]);
    return ans;
}
```

## 最后，附上AC代码：
```cpp
#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define db(x) debug(x)
using namespace std;
int dat[10005],n;
struct trans{
    int pre,mid,suf,sum;
    int fin(){
        return max(max(pre,suf),mid);
    }
    trans DB(){
        db(pre);db(mid);db(suf);db(sum);
        return *this;
    }
};
trans merge(trans s1,trans s2){
    trans ans;
    ans.pre=max(s1.pre,s2.pre+s1.sum);
    ans.mid=max(max(s1.mid,s2.mid),s1.suf+s2.pre);
    ans.suf=max(s1.suf+s2.sum,s2.suf);
    ans.sum=s1.sum+s2.sum;
    return ans;
}
struct node{
    int l,r;
    trans dat;
}p[40005];
void update(int rt){
    p[rt].dat=merge(p[rt*2].dat,p[rt*2+1].dat);
    return;
}
void build(int rt,int l,int r){
    p[rt].l=l;p[rt].r=r;
    if(l==r){
        p[rt].dat.pre=p[rt].dat.mid=p[rt].dat.suf=p[rt].dat.sum=dat[l];
        return;
    }
    int mid=(l+r)/2;
    build(rt*2,l,mid);
    build(rt*2+1,mid+1,r);
    update(rt);
    return;
}
trans query_sub_max(int rt,int l,int r){
    if(l>r){
        return (trans){0,0,0,0};
    }
    if(p[rt].l==l&&p[rt].r==r){
        return p[rt].dat;
    }
    int mid=p[rt*2].r;
    if(r<=mid)return query_sub_max(rt*2,l,r);
    else if(l>mid)return query_sub_max(rt*2+1,l,r);
    return merge(query_sub_max(rt*2,l,mid),query_sub_max(rt*2+1,mid+1,r));
}
int query(int l1,int r1,int l2,int r2){
    if(r1<l2){
        int tmp=query_sub_max(1,l1,r1).suf;
        tmp+=query_sub_max(1,r1+1,l2-1).sum;
        tmp+=query_sub_max(1,l2,r2).pre;
        return tmp;
    }
    int ans=query_sub_max(1,l2,r1).mid;
    if(l1<l2)ans=max(ans,query_sub_max(1,l1,l2).suf+query_sub_max(1,l2,r2).pre-dat[l2]);
    if(r2>r1)ans=max(ans,query_sub_max(1,l1,r1).suf+query_sub_max(1,r1,r2).pre-dat[r1]);
    return ans;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&dat[i]);
        build(1,1,n);
        int m;
        scanf("%d",&m);
        while(m--){
            int x1,x2,y1,y2;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            printf("%d\n",query(x1,y1,x2,y2));
        }
    }
    return 0;
}
```

---

## 作者：一叶知秋。 (赞：30)

我的题解应该只比猫树慢了吧(其实是我没想到，歪打正着)(~~好歹也是最优解里的rank6~~)

看题目，最大子段和，一下子就想到另外两道题：

[SP1043 GSS1 - Can you answer these queries I](https://www.luogu.org/problemnew/show/SP1043)

[SP1043 GSS1 - Can you answer these queries III](https://www.luogu.org/problemnew/show/SP1716)

所以就定下来了，用线段树完成这道题！(废话)

------------

但是，题解中都是直接想到求最大子段和，但是我想的是，既然定下了两个区间(一开始压根没考虑两个区间会有相交)，那么在两个区间里找后缀和的最值(脑残写了一个后缀和)左边找最大，右边找最小，这样相差不就是最大子段和了吗？然后就高高兴兴的写完交上去，然后，0pts。。。

0分代码如下：

```cpp
#include<cstdio>

inline int read(){
	int r=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')r=(r<<1)+(r<<3)+c-'0',c=getchar();
	return r*f;
}

struct TR{
	int l,r,max,min;
}tr[400004];

int a[100001],n,m,r_s[100001];//r_s[i]是指从a[i+1]~a[n]的和，这样写方便作差

inline int max(int a,int b){
	return a>b?a:b;
}

inline int min(int a,int b){
	return a<b?a:b;
}

void build(int p,int l,int r){
	tr[p].l=l,tr[p].r=r;
	if(l==r){
		tr[p].max=r_s[l]+a[l];//最大后缀和，被减数要加上自己
		tr[p].min=r_s[l];//最小后缀和
		return;
	}
	int mid=l+r>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	tr[p].max=max(tr[p*2].max,tr[p*2+1].max);
	tr[p].min=min(tr[p*2].min,tr[p*2+1].min);
}

int query_max(int p,int l,int r){//左区间找最大
	if(l<=tr[p].l&&tr[p].r<=r)return tr[p].max;
	int mid=tr[p].l+tr[p].r>>1;
	if(l>mid)return query_max(p*2+1,l,r);
	if(r<=mid)return query_max(p*2,l,r);
	return max(query_max(p*2,l,r),query_max(p*2+1,l,r));
}

int query_min(int p,int l,int r){//右区间找最小
	if(l<=tr[p].l&&tr[p].r<=r)return tr[p].min;
	int mid=tr[p].l+tr[p].r>>1;
	if(l>mid)return query_min(p*2+1,l,r);
	if(r<=mid)return query_min(p*2,l,r);
	return min(query_min(p*2,l,r),query_min(p*2+1,l,r));
}

int main(){
	int t=read();
	for(int i=1;i<=t;i++){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=n-1;i>=1;i--)r_s[i]=r_s[i+1]+a[i+1];
		build(1,1,n);
		m=read();
		for(int i=1;i<=m;i++){
			int l=read(),r=read(),ll=read(),rr=read();
			printf("%d\n",query_max(1,l,r)-query_min(1,ll,rr));//大减小
		}
	}
	return 0;
}
```

经过一番~~深思熟虑~~思考以后，我~~突然~~想起可能会有重叠部分，这时的值还是会最大,但是可能选的子段左端点在右端点右边，值是错的。

那能不能一边取到最值，另外一边从这个点开始向左(或右)找最优的节点呢？这样是不行的，说不定正确答案的两端点是一个后缀和较大，一个后缀和较小的点。所以这样也是不行的。

这时我们想到相交的部分不就是[这道题]问的东西吗？(https://www.luogu.org/problemnew/show/SP1043)

然后剩下的左右两段又可以用刚才的方法算，最后取大就出来了！

所以中西结合，啊不，IV结合(可还行)，就成功的A了这道题目了！

不过代码是更新前交的，现在更新后交速度变慢了(不过还是题解中的rank2)

100分代码如下：(0ms,16MB(更新前))

```cpp
#include<cstdio>

inline int read(){
	int r=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')r=(r<<1)+(r<<3)+c-'0',c=getchar();
	return r*f;
}

struct TR{//ll指的是区间最大前缀和，rr指的是区间最大后缀和
	int l,r,max,min,ll,rr,sum,max_sum;//sum是区间和，max_sum是最大子段和
}tr[400004];

int a[100001],n,m,r_s[100001];

inline int max(int a,int b){
	return a>b?a:b;
}

inline int min(int a,int b){
	return a<b?a:b;
}

void build(int p,int l,int r){
	tr[p].l=l,tr[p].r=r;
	if(l==r){
		tr[p].max=r_s[l]+a[l];
		tr[p].min=r_s[l];
		tr[p].max_sum=tr[p].sum=tr[p].ll=tr[p].rr=a[l];
		return;
	}
	int mid=l+r>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	if(tr[p*2].max>tr[p*2+1].max)tr[p].ll=tr[p*2].ll;
	else tr[p].ll=tr[p*2+1].ll;
	tr[p].max=max(tr[p*2].max,tr[p*2+1].max);
	tr[p].min=min(tr[p*2].min,tr[p*2+1].min);
	tr[p].max_sum=max(tr[p*2].rr+tr[p*2+1].ll,max(tr[p*2].max_sum,tr[p*2+1].max_sum));//更新方式多样
	tr[p].sum=tr[p*2].sum+tr[p*2+1].sum;
	tr[p].ll=max(tr[p*2].ll,tr[p*2].sum+tr[p*2+1].ll);
	tr[p].rr=max(tr[p*2+1].rr,tr[p*2+1].sum+tr[p*2].rr);
}

int query_max(int p,int l,int r){
	if(l<=tr[p].l&&tr[p].r<=r)return tr[p].max;
	int mid=tr[p].l+tr[p].r>>1;
	if(l>mid)return query_max(p*2+1,l,r);
	if(r<=mid)return query_max(p*2,l,r);
	return max(query_max(p*2,l,r),query_max(p*2+1,l,r));
}

int query_min(int p,int l,int r){
	if(l<=tr[p].l&&tr[p].r<=r)return tr[p].min;
	int mid=tr[p].l+tr[p].r>>1;
	if(l>mid)return query_min(p*2+1,l,r);
	if(r<=mid)return query_min(p*2,l,r);
	return min(query_min(p*2,l,r),query_min(p*2+1,l,r));
}

inline TR mer_TR(TR a,TR b){
	TR maxx;
	maxx.max_sum=max(a.rr+b.ll,max(a.max_sum,b.max_sum));
	maxx.sum=a.sum+b.sum;
	maxx.ll=max(a.ll,a.sum+b.ll);
	maxx.rr=max(b.rr,b.sum+a.rr);
	return maxx;
}

TR query(int p,int l,int r){
	if(l<=tr[p].l&&tr[p].r<=r)return tr[p];
	int mid=tr[p].l+tr[p].r>>1;
	TR max_sum;
	if(l>mid)return query(p*2+1,l,r);
	if(r<=mid)return query(p*2,l,r);
	return mer_TR(query(p*2,l,r),query(p*2+1,l,r));//合并两个区间
}

inline int max_ans(int l1,int r1,int l2,int r2){
	int x=query(1,l2,r1).max_sum;//相交部分最大子段和
	int y=query_max(1,l1,l2)-query_min(1,l2,r2);//左段与右边整个区间
	int z=query_max(1,l1,r1)-query_min(1,r1,r2);//右段与左边整个区间
	return max(x,max(y,z));//取大
}

int main(){
	int t=read();
	for(int i=1;i<=t;i++){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=n-1;i>=1;i--)r_s[i]=r_s[i+1]+a[i+1];
		build(1,1,n);
		m=read();
		for(int i=1;i<=m;i++){
			int l=read(),r=read(),ll=read(),rr=read();
			if(r<=ll)printf("%d\n",query_max(1,l,r)-query_min(1,ll,rr));//不相交
			else printf("%d\n",max_ans(l,r,ll,rr));//相交
		}
	}
	return 0;
}
```

~~偷偷完结撒花~~✿✿ヽ(°▽°)ノ✿

---

## 作者：kradcigam (赞：19)

# 前言

最近沉迷于数据结构，感觉数据结构很有意思。

# 正文

## 分析

先来分类讨论一下

### 1. $x2<y1$

![afd.png](https://i.loli.net/2020/03/04/y1Z4Y7XQADTWwM3.png)

如果 $y1<x2$ 的话，答案 $=\max \limits_{ y1 \leq x \leq y2} \{ s_i \} - \min \limits_{x1 \leq x \leq x2} \{ s_i \}$

其中 $s_i$ 表示 $\sum\limits_{j=1}^{i} a_j$ ，就是俗称的前缀和

![afd.png](https://i.loli.net/2020/03/04/E7g8BYwDZUQNypd.png)

这个东西可以用线段树维护。

### 2. $x2>=y1$

![afd.png](https://i.loli.net/2020/03/04/5O18AXc39CQnliT.png)

这个怎么处理呢

答案 $=$ $\max \begin{cases}\max \limits_{ y1 \leq x \leq y2} \{ s_i \} - \min \limits_{x1 \leq x \leq y1} \{ s_i \}\\ \max \limits_{ x2 \leq x \leq y2} \{ s_i \} - \min \limits_{x1 \leq x \leq x2} \{ s_i \}\\ f(x,y)\end{cases}$

这里的 $f$ 函数就是最大子段和。

不会用线段树求最大子段和的可以看[这里](https://zhaohaikun.blog.luogu.org/solution-sp1716)

最上面的 $2$ 个也是可以用线段树来维护的。

## 代码

**最后要注意的一点是前缀和**，我们知道区间 $[i,j]$ 的和 $ = s_j-s_{i-1}$，而不是 $ = s_j-s_{i}$

这个怎么处理呢，我们发现我们的题目全部都是用 $Max$ 函数的答案减去 $Min$ 函数的答案，所以，我们可以把线段树维护的 $\min$ 全部减去 $a_{i}$

现在这份代码就能 $A$ 了

```cpp
#include <bits/stdc++.h>
#define ls num<<1
#define rs num<<1|1
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
template<typename T>void write(T x){
	if(x<0)putchar('-'),x*=-1;
	if(x>9)write(x/10);
	putchar(x%10+48);
}
template<typename T>void writen(T x){
	write(x);
	puts("");
}
const int MAXN=5e4+10;
struct Tree{
	int l,r;
	ll lans,rans,sum,ans,max,min;
}t[MAXN*4];
int a[MAXN],x,y,n,T,T_,l1,r1,l2,r2;
ll s[MAXN];
Tree pushup(Tree L,Tree R){
	Tree z;
	z.sum=L.sum+R.sum;
	z.lans=max(L.lans,L.sum+R.lans);
	z.rans=max(R.rans,R.sum+L.rans);
	z.ans=max(max(L.ans,R.ans),L.rans+R.lans);
	z.max=max(L.max,R.max);
	z.min=min(L.min,R.min);
	z.l=L.l;z.r=R.r;
	return z;
}
void build(int l,int r,int num){
	if(l==r){
		t[num].l=l;
		t[num].r=r;
		t[num].sum=a[l];
		t[num].lans=a[l];
		t[num].rans=a[l];
		t[num].ans=a[l];
		t[num].max=s[l];
		t[num].min=s[l]-a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls);
	build(mid+1,r,rs);
	t[num]=pushup(t[ls],t[rs]);
}
Tree query(int num){
	if(x<=t[num].l&&t[num].r<=y)return t[num];
	if(t[rs].l>y)return query(ls);
	if(t[ls].r<x)return query(rs);
	return pushup(query(ls),query(rs));
}
ll Max(int num){
	if(t[num].l>=x&&t[num].r<=y)return t[num].max;
	if(t[ls].r<x)return Max(rs);
	if(t[rs].l>y)return Max(ls);
	return max(Max(ls),Max(rs));
}
ll Min(int num){
	if(t[num].l>=x&&t[num].r<=y)return t[num].min;
	if(t[ls].r<x)return Min(rs);
	if(t[rs].l>y)return Min(ls);
	return min(Min(ls),Min(rs));
}
ll Mx(int a,int b){
	x=a;y=b;
	return Max(1);
}
ll Mn(int a,int b){
	x=a;y=b;
	return Min(1);
}
ll qy(int a,int b){
	x=a;y=b;
	return query(1).ans;
}
int main(){
	read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++)read(a[i]);
		for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
		build(1,n,1);
		read(T_);
		while(T_--){
			read(l1);read(r1);read(l2);read(r2);
			if(r1>l2)writen(max(qy(l2,r1),max(Mx(l2,r2)-Mn(l1,l2),Mx(r1,r2)-Mn(l1,r1))));
			else writen(Mx(l2,r2)-Mn(l1,r1));
		}
	}
	return 0;
}
```
# 后记

这篇题解如果有问题可以私信或评论，告诉我，一起完善

---

## 作者：warzone (赞：18)

这道题和

[SP1043 GSS1 - Can you answer these queries I](https://www.luogu.org/problemnew/show/SP1043)

[SP1716 GSS3 - Can you answer these queries III](https://www.luogu.org/problemnew/show/SP1716)

同为线段树求最大子段和的例题,大家都先去做一下

~~虽然自己懒得写它们的题解~~

它们整个代码的重点都在于**区间合并**,我们可以将相邻区间的和,最大子段和,最大前缀和/后缀和**合并**

我们把它们配成一个结构体,一起处理
```cpp
struct pair{
    int h,lmax,rmax,max;
    inline void update(pair *l,pair *r){
        h=l->h+r->h;//和直接相加
		lmax=l->lmax>r->lmax+l->h? l->lmax:r->lmax+l->h;
/*
最大前缀和只需比较两个:
----左区间----|--右区间---
比较这两个:
----	<=左区间的最大前缀和
--------------|--- <=左区间和+右区间的最大前缀和
*/
		rmax=r->rmax>l->rmax+r->h? r->rmax:l->rmax+r->h;
//最大后缀和同上
		max=l->max>r->max? l->max:r->max;
		max=max>l->rmax+r->lmax? max:l->rmax+r->lmax;
/*
最大子段和比较三个:
左右区间分别的最大子段和
两区间相连得到的新子段最大和
(即 左区间的最大后缀和+右区间的最大前缀和)
*/
	}
}
```

通过这些,我们就可以用线段树**分解区间,需要时再合并**得到这些数据

```cpp
inline pair sum(const int&f,const int&t){
	if(from==f&&to==t) return *p;
	if(t<=l->to) return l->sum(f,t);//向左边搜区间
	if(r->from<=f) return r->sum(f,t);//向右边搜区间
	pair left=l->sum(f,l->to),right=r->sum(r->from,t),out;
	out.update(&left,&right);
   //横跨两个子树的区间,分别搜索再合并
	return out;
}
```

由此,GSS1已经易如反掌

而这一题要我们求的,可以通过**分类讨论**解决

1. 两区间无交叉/包含关系时如图所示
![](https://cdn.luogu.com.cn/upload/pic/63848.png)

于是所求值为

#### (左区间的最大后缀和+右区间的最大前缀和+两区间之间的区间总和)

2. 两区间有交叉/包含关系时如图所示
![](https://cdn.luogu.com.cn/upload/pic/63849.png)

于是就需比较两种情况:

- 两端点都在交叉部分 ->直接求

- 一端点不在交叉部分 ->用最大前缀/后缀和求

于是查询为如下代码

```cpp
#define c const
#define i int
inline int sum(c i&ff,c i&ft,c i&tf,c i&tt){
	register i ans,cmp;
	if(tf-ft>=1){
		ans=root->sum(ff,ft).rmax+root->sum(tf,tt).lmax;
		if(tf-ft>1) ans+=root->sum(ft+1,tf-1).h;
		return ans;
	}
  	//无交叉/包含关系的情况
	ans=root->sum(tf,ft).max;
	if(ff<tf){
		cmp=root->sum(ff,tf-1).rmax+root->sum(tf,tt).lmax;
		ans=ans>cmp? ans:cmp;
	}
	if(ft<tt){
		cmp=root->sum(ff,ft).rmax+root->sum(ft+1,tt).lmax;
		ans=ans>cmp? ans:cmp;
	}
	return ans;
  	//有交叉/包含关系的情况
}
#undef c
#undef i
```

由此主要部分(核心代码)就完成了,剩下的便是初始化和输入输出

AC完全代码(20ms,3.7MB)
```cpp
#include<cstdio>
using namespace std;
namespace io{
	inline int r32(){
		register char c=getchar();
		register short w=1;
		while('0'>c||c>'9'){
			if(c=='-') w=-1;
			c=getchar();
		}
		register int a=0;
		while('0'<=c&&c<='9'){
			a=a*10+(c-'0');
			c=getchar();
		}
		return a*w;
	}
	inline void w32(const unsigned int&num){
		if(num==0) return;
		w32(num/10);
		putchar(num%10+'0');
	}
}//快读快写 
struct pair{//区间的和,最大子段和,最大前缀和,最大后缀和
	int h,lmax,rmax,max;
	inline void update(pair *l,pair *r){
		h=l->h+r->h;
		lmax=l->lmax>r->lmax+l->h? l->lmax:r->lmax+l->h;
		rmax=r->rmax>l->rmax+r->h? r->rmax:l->rmax+r->h;
		max=l->max>r->max? l->max:r->max;
		max=max>l->rmax+r->lmax? max:l->rmax+r->lmax;
	}
}ans;
class segment_tree{
	private:
		#define c const
		#define i int
		struct point{
			point *l,*r;
			int from,to;
			pair *p;
			point(c i&f,c i&t){
				from=f,to=t;
				p=new pair;
				if(f==t){
					p->h=io::r32();
					p->max=p->lmax=p->rmax=p->h;
				}
				else{
					l=new point(f,(f+t)/2);
					r=new point(l->to+1,t);
					p->update(l->p,r->p);
				}
			}//线段树初始化 
			~point(){
				if(from!=to){
					delete l;
					delete r;
				}
			}
			inline pair sum(c i&f,c i&t){
				if(from==f&&to==t) return *p;
				if(t<=l->to) return l->sum(f,t);
           		//向左边搜区间
				if(r->from<=f) return r->sum(f,t);
           		//向右边搜区间
				pair left=l->sum(f,l->to);
				pair right=r->sum(r->from,t),out;
				out.update(&left,&right);
   				//横跨两个子树的区间,分别搜索再合并
				return out;
			}
		}*root;
	public:
		segment_tree(c i&length){root=new point(1,length);}
		~segment_tree(){delete root;}
		inline int sum(c i&ff,c i&ft,c i&tf,c i&tt){
			register int ans,cmp;
			if(tf-ft>=1){
				ans=root->sum(ff,ft).rmax+root->sum(tf,tt).lmax;
				if(tf-ft>1) ans+=root->sum(ft+1,tf-1).h;
				return ans;
			}
  			//无交叉/包含关系的情况
			ans=root->sum(tf,ft).max;
			if(ff<tf){
				cmp=root->sum(ff,tf-1).rmax;
				cmp+=root->sum(tf,tt).lmax;
				ans=ans>cmp? ans:cmp;
			}
			if(ft<tt){
				cmp=root->sum(ff,ft).rmax;
				cmp+=root->sum(ft+1,tt).lmax;
				ans=ans>cmp? ans:cmp;
			}
			return ans;
  			 //有交叉/包含关系的情况
		}
		#undef c
		#undef i
};
int main(){
	const int CASE=io::r32();
	for(register int Case=0,n,m;Case<CASE;Case++){
		n=io::r32();
		segment_tree tree(n);
		m=io::r32();
		for(register int i=0,x1,y1,x2,y2;i<m;i++){
			x1=io::r32();
			x2=io::r32();
			y1=io::r32();
			y2=io::r32();
			x1=tree.sum(x1,x2,y1,y2);
			if(x1==0) putchar('0');
			else if(x1<0){
				putchar('-');
				io::w32(-x1);
			}
			else io::w32(x1);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：Plozia (赞：11)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/111566557)

GSS5 是 GSS1 的进一步的升级。

这一道题控制了左右端点的范围，因此我们需要分类讨论。

第一种情况：$r1 \leq l2$，如图：

![在这里插入图片描述](https://cdn.luogu.com.cn/upload/image_hosting/6v6hdz0e.png)

那么从图上我们可以很清晰的看到：我们实质是要求 $[r1,l2]$ 的和加上 $[l1,r1]$ 的最大后缀加上 $[l2,r2]$ 的最大前缀然后减去 $a_{r1},a_{l2}$。这样做是为了防止 $l1==r1$ 这种坑爹的情况干扰我们的判断（如果直接求 $[l1,r1-1]$ 的前缀就直接炸了）。

第二种情况：$l2 < r1$，如图：

![在这里插入图片描述](https://cdn.luogu.com.cn/upload/image_hosting/4qgb648t.png)

那么此时我们需要进行分类讨论。设我们选取的最大子段和区间为 $[x,y]$。

1. 当 $x$ 在 $[l1,l2)$ 中，$y$ 在 $[l2,r1]$ 中时，我们要求的是 $[l1,l2]$ 的最大后缀加上 $[l2,r1]$ 的最大后缀减去 $a_{l2}$。
2. 当 $x$ 在 $[l1,l2)$ 中，$y$ 在 $(r1,l2]$ 中时，此时的询问就变成了前面 $r1 \leq l2$ 的询问，此处不再讲解。
3. 当 $x$ 在 $[l2,r1]$ 中，$y$ 在 $[l2,r1]$ 中时，我们要求的是 $[l2,r1]$ 的最大子段和，模仿 GSS1 即可。
4. 当 $x$ 在 $[l2,r1]$ 中，$y$ 在 $(r1,l2]$ 中时，我们要求的是 $[l2,r1]$ 的最大后缀加上 $[r1,l2]$ 的最大前缀减去 $a_{r1}$。

所以我们只需要按照上面的讨论解题即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int Max(LL fir, LL sec) {return (fir > sec) ? fir : sec;}
int Min(LL fir, LL sec) {return (fir < sec) ? fir : sec;}

const int MAXN = 1e4 + 10;
int t, n, m, a[MAXN];
struct node
{
	int l, r;
	LL sum, pre, aft, maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define p(p) tree[p].pre
	#define a(p) tree[p].aft
	#define m(p) tree[p].maxn
	node operator + (const node &b)
	{
		node c;
		c.l = l, c.r = b.r;
		c.sum = sum + b.sum;
		c.pre = Max(pre, sum + b.pre);
		c.aft = Max(b.aft, b.sum + aft);
		c.maxn = Max(maxn, Max(b.maxn, aft + b.pre));
		return c;
	}
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^48); ch = getchar();}
	return sum * fh;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) {s(p) = a(p) = p(p) = m(p) = a[l]; return ;}
	int mid = (l(p) + r(p)) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

node Ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return tree[p];
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid && r > mid) return Ask(p << 1, l, r) + Ask(p << 1 | 1, l, r);
	if (l <= mid) return Ask(p << 1, l, r);
	if (r > mid) return Ask(p << 1 | 1, l, r);
}

int main()
{
	t = read();
	while (t--)
	{
		memset(a, 0, sizeof(a)); memset(tree, 0, sizeof(tree));
		n = read();
		for (int i = 1; i <= n; ++i) a[i] = read();
		build(1, 1, n); m = read();
		for (int i = 1; i <= m; ++i)
		{
			int l1 = read(), r1 = read(), l2 = read(), r2 = read(); LL ans;
			if (r1 <= l2) ans = Ask(1, r1, l2).sum + Ask(1, l1, r1).aft + Ask(1, l2, r2).pre - a[r1] - a[l2];
			else
			{
				ans = Ask(1, l1, l2).aft + Ask(1, l2, r1).pre - a[l2];
				ans = Max(ans, Ask(1, l1, l2).aft + Ask(1, l2, r1).sum + Ask(1, r1, r2).pre - a[l2] - a[r1]);
				ans = Max(ans, Ask(1, l2, r1).maxn);
				ans = Max(ans, Ask(1, l2, r1).aft + Ask(1, r1, r2).pre - a[r1]);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
```


---

## 作者：陈浩然 (赞：9)

前置知识：线段树维护区间最大子段和（若有不会请转GSS1），st表（只有第二种做法会用到）（应该没有不会的吧）。

define 左 x1到min(y1,x2);

define 右 max(y1,x2)到y2;

define 中 min(y1,x2)到max(y1,x2);

define l 答案区间的左端点

define r 答案区间的右端点

由于鄙人很是蒟蒻，用纯粹的线段树维护区间最大子段和总是因为边界以及+1-1之类的神奇操作莫名其妙的锅，可能是我太菜了……菜是原罪……

于是，请教了YOUSIKI大佬，他向我提供了一种做法，然后我觉得时间复杂度应该还算比较优秀，于是就来发题解来了。

先说说我的思路，应该是比较像是一个从GSS3过来的人。

用线段树，维护区间最大子段和，其实和GSS3一样（~~可以复制代码~~）。

然后分类讨论，若有y1<x2，即区间无重合部分，答案是(左的最大后缀和+右的最大前缀和+中的总和)，else，即为有区间重合，分类讨论l和r的范围可知，答案要么是无重合的，要么可以由区间的后缀和和前缀和算出。

下面是另外一种做法。

思路是这样的。

如果这题我不会，给自己找个台阶下，我会去想要是没有区间重叠怎么办，显然，可以搞出一个前缀和数组，答案就是右的前缀和最大值减去左的前缀和最小值，这应该不难。

那要是有重叠咋办？？？？？？

于是还是得分类讨论：

1.l在左，r在中。 就相当于分离

2.l在左，r在右。 同上，且有1,2可合并

3.l在中，r在右。 同上

4.l在中，r在中。 同GSS1

于是就很爽，静态区间最值问题可以写st表，O(nlogn)预处理，O(1)查询，GSS1可以写线段树，常数应该很小，毕竟st表是O(1)查询。

放一波代码吧

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
using namespace std;
const int MAXN=1e5+5;
int dat,n,q,root,tree_cnt,lg[MAXN],a[MAXN],ls[MAXN],rs[MAXN];
int st1[MAXN][26],st2[MAXN][26];  //st1维护最大值，st2维护最小值
struct Node
{
	int sum,qm,hm,jm;  //sum区间和,qm最大前缀和,hm最大后缀和,jm最大区间和
}t[MAXN];
inline int read()  //快读，不解释
{
	int x=0;int f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline void pushup(int cur)
{
	t[cur].sum=t[ls[cur]].sum+t[rs[cur]].sum;
	t[cur].qm=max(t[ls[cur]].qm,t[ls[cur]].sum+t[rs[cur]].qm);
	t[cur].hm=max(t[rs[cur]].hm,t[rs[cur]].sum+t[ls[cur]].hm);
	t[cur].jm=max(t[ls[cur]].jm,max(t[rs[cur]].jm,t[ls[cur]].hm+t[rs[cur]].qm));
}
void build(int l,int r,int &cur)
{
	cur=++tree_cnt;
	if(l==r)
	{
		t[cur].sum=t[cur].qm=t[cur].hm=t[cur].jm=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls[cur]);
	build(mid+1,r,rs[cur]);
	pushup(cur);
}
Node query(int l,int r,int ql,int qr,int cur)
{
	if(ql<=l&&qr>=r) return t[cur];
	Node ans,ll,rr;
	int mid=(l+r)>>1,flag1=0,flag2=0;
	if(ql<=mid) ll=query(l,mid,ql,qr,ls[cur]),flag1=1;
	if(qr>mid) rr=query(mid+1,r,ql,qr,rs[cur]),flag2=1;
	if(flag1&&flag2)
	{
		ans.sum=ll.sum+rr.sum;
		ans.qm=max(ll.qm,ll.sum+rr.qm);
		ans.hm=max(rr.hm,rr.sum+ll.hm);
		ans.jm=max(ll.jm,max(rr.jm,ll.hm+rr.qm));
	}
	else if(flag1) return ll;
	else return rr;
	return ans;
}  //以上同GSS1
inline void getlog()  //据说log函数不是线性的(不知道对不对),只好预处理一下
{
	for(int i=2;i<=20005;i++)
		lg[i]=lg[i/2]+1;
}
inline int getmax(int l,int r)
{
	int k=lg[r-l+1];
	return max(st1[l][k],st1[r-(1<<k)+1][k]);
}
inline int getmin(int l,int r)
{
	int k=lg[r-l+1];
	return min(st2[l][k],st2[r-(1<<k)+1][k]);
}
inline int query2(int x1,int y1,int x2,int y2)
{
	return getmax(x2,y2)-getmin(x1,y1);
}
int main()
{
	dat=read(),getlog();
	while(dat--)
	{
		n=read(),tree_cnt=0,root=1;  //注意tree_cnt要归为0,root似乎无影响
		for(int i=1;i<=n;i++)  //st表初值直接赋为前缀和
			a[i]=read(),st1[i][0]=st2[i][0]=st1[i-1][0]+a[i];
		build(1,n,root);  //建树
		for(int j=1;j<=25;j++)  //st表预处理
			for(int i=0;i+(1<<j)-1<=n;i++)  //注意要从0开始,因为下面查询有的减一,有点小坑 
				st1[i][j]=max(st1[i][j-1],st1[i+(1<<(j-1))][j-1]),
				st2[i][j]=min(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
		q=read();
		for(int i=1;i<=q;i++)
		{
			int x1=read(),y1=read(),x2=read(),y2=read();
			if(y1<=x2)  //无重叠
				printf("%d\n",query2(x1-1,y1-1,x2,y2));
			else   //有重叠
				printf("%d\n",max(query2(x1-1,x2-1,x2,y2),max(
				query2(x1-1,y1-1,y1,y2),query(1,n,x2,y1,1).jm)));
               			//查询时,查询左区间的时候全部减一是个坑,由于是闭区间,st表里的是前缀和,
				//区间和[x1,y1]=sum[y1]-sum[x1-1],所以我们要的是减一的区间,可以画下图举个例子,我不会上传图片… 
		}
	}
	return 0;
}
```
这份代码是可以直接满分的，但是最好别抄吧，有些小细节只有写了才知道，哪怕对着打一遍也好。

yousiki大佬还是很强的，%%%。

最后，祝大家早日也成为大佬，可以吊打许多像我这样的蒟蒻（~~似乎现在就可以~~）（逃）。

---

## 作者：潜翎 (赞：8)

[SP2916 GSS5](https://www.luogu.org/problemnew/show/SP2916)

明明是咕咕日报上的例题，却没有人写**猫树**的题解呀qwq

我们除了像[GSS1中的猫树做法一样](https://www.luogu.org/blog/qianling/solution-sp1043)维护普通从中心到两端的最大子段和与包含中心节点的子段中的最大子段和之外，还需要维护**从中点到该点的前缀和与从某点到该点的前缀和的最大值。**（虽然根据猫树的特点，在区间右侧它才是**前缀和**，在区间左侧时它就是**后缀和**，叫它**中缀和**似乎更合适，因为它是从中间向两边求和）

嗯，我这里不严谨的在下文把这个东西称为中缀和。

举个例子吧，比如说mid是3，位置1的**中缀和**就是a[1]+a[2]+a[3]，而**从某点到该点的中缀和的最大值**是指从a[3]+a[2]+a[1],a[2]+a[1],a[1]中取**最大值**

我们观察询问的区间，可能性无非**两种**：

- 这两个区间没有交集。

很显然，这种情况下两区间之间的部分的数**必须全部取**。

然后我们想要求出**靠左的区间**从**右端点**到**左侧区间内某点**的最大值（后面把这个操作定义为suc）和**靠右的区间**从**左端点**到**右侧区间内某点**的最大值（后面把这个操作定义为pre）

怎么求呢？

以第一种为例：我们最后取得的答案有两种情况，1是**不知道过不过猫树该节点中点**，我们直接选用**从某点到右端点的中缀和**就好了。2是**过猫树该节点中点**，我们选用**区间左端点包含中点的最大子段和**与**从区间右端点到节点中心的整段前缀和。**

第二种同理。

然后我们把这两种与两区间之间的数全部加起来就OK啦。

- 这两个区间有交集。

首先，这两个区间交的部分**既可以放左端点，又可以放右端点。**所以我们把这一段当GSS1先求出一个答案。

如果左区间左端点小于右区间左端点的话，对左区间左端点和右区间左端点求suc再对右区间左端点和右区间右端点求pre，把这两个值加起来再减去重复的右区间左端点的值，我们又得到了一个可能答案。

然后右区间右端点大于左区间右端点时，同理得到另一个可能答案。

然后在可能答案中选一个最大的作为此次询问答案

好啦，看代码理解一下吧qwq

```cpp
#include <stdio.h>
const int N=20010;
int T,n,m,len;
int a[N],pos[N],p[16][N],f[16][N],sum[16][N],e_sum[16][N],lg[N<<2];
int read()
{
    int x=0,w=1;char ch;ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*w;
}
int max(int x,int y){return x>y?x:y;}
void init()
{
	for(len=2;len<n;len<<=1);
	int l=len<<1;
	for(int i=2;i<=l;i++)
	 lg[i]=lg[i>>1]+1;
}
void build(int l,int r,int k,int d)
{
	if(l==r) {pos[l]=k;return;}
	int f1,f2,mid=(l+r)>>1;
	p[d][mid]=f[d][mid]=sum[d][mid]=e_sum[d][mid]=f1=f2=a[mid];
	f2=max(f2,0);
	for(int i=mid-1;i>=l;i--)
	{
		f1+=a[i];f2+=a[i];
		p[d][i]=max(p[d][i+1],f1);
		f[d][i]=max(f[d][i+1],f2);
		sum[d][i]=f1;e_sum[d][i]=f2;
		f2=max(f2,0);
	}
	p[d][mid+1]=f[d][mid+1]=sum[d][mid+1]=e_sum[d][mid+1]=f1=f2=a[mid+1];
	f2=max(f2,0);
	for(int i=mid+2;i<=r;i++)
	{
		f1+=a[i];f2+=a[i];
		p[d][i]=max(p[d][i-1],f1);
		f[d][i]=max(f[d][i-1],f2);
		sum[d][i]=f1;e_sum[d][i]=f2;
		f2=max(f2,0);
	}
	build(l,mid,k<<1,d+1);
	build(mid+1,r,k<<1|1,d+1);
}
int s_query(int l,int r)
{
	if(l>r) return 0;
	if(l==r) return a[l];
	int d=lg[pos[l]]-lg[pos[l]^pos[r]];
	return sum[d][l]+sum[d][r];
}
int pre_query(int l,int r)
{
	if(l>r) return 0;
	if(l==r) return a[l];
	int d=lg[pos[l]]-lg[pos[l]^pos[r]];
	return max(e_sum[d][l],sum[d][l]+p[d][r]);
}
int suc_query(int l,int r)
{
	if(l>r) return 0;
	if(l==r) return a[l];
	int d=lg[pos[l]]-lg[pos[l]^pos[r]];
	return max(e_sum[d][r],p[d][l]+sum[d][r]);
}
int m_query(int l,int r)
{
	if(l>r) return 0;
	if(l==r) return a[l];
	int d=lg[pos[l]]-lg[pos[l]^pos[r]];
	return max(max(f[d][l],f[d][r]),p[d][l]+p[d][r]);
}
int query(int l1,int r1,int l2,int r2)
{
	int ans;
	if(r1<l2) return s_query(r1+1,l2-1)+suc_query(l1,r1)+pre_query(l2,r2);
	ans=m_query(l2,r1);
	if(l1<l2) ans=max(ans,suc_query(l1,l2)+pre_query(l2,r2)-a[l2]);
	if(r2>r1) ans=max(ans,suc_query(l1,r1)+pre_query(r1,r2)-a[r1]);
	return ans;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		init();
		build(1,len,1,1);
		int l1,r1,l2,r2;
		m=read();
		while(m--)
		{
			l1=read();r1=read();l2=read();r2=read();
			printf("%d\n",query(l1,r1,l2,r2));
		}
	}
}
```


------------
后记：

写这个的时候深深感受到了自己语文能力的不足……希望大家多多包涵QWQ

以及这是我的第一篇黑题题解！撒fafa！

---

## 作者：Lolierl (赞：7)

线段树模板题。 

显然，y1<x2时，用GSS1的做法就可以很好解决（[x1, y1)的后缀最大值 + sum[y1, x2] + (x2, y2]的前缀最大值）。

当y1>=x2时，此时情况较多，需分类考虑

![](https://cdn.luogu.com.cn/upload/pic/25278.png)

当x2<=x<=y1, x2<=y<=y1(黄色线段)时，ans = [x2, y1]的最大子段和;

当x1<=x<x2, x2<=y<=y1(红色线段)时，ans = [x1, x2)的最大后缀 + [x2, y1]的最大前缀;

当x2<=x<=y1, y1<y<=y2(蓝色线段)时，ans = [x2, y1]的最大后缀 + (y1, y2]的最大前缀;

最后，当x1<=x<=x2, y1<=y<=y2(绿色线段)时，ans = [x1, x2)的最大后缀 + [x2, y1]的区间和 + (y1, y2]的最大前缀。

此外，还要注意边界条件，当y1 = x2时可能会重复计算或出现查询负区间的情况，需要手动避免。

线段树维护和查询每个指标都是log级别的复杂度，所以整体时间是O(mlogn)。尽管常数较大，可通过这题10^4的数据应该没有压力。

以下是我的代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std; 

int n, m, x1, x2, y_1, y2, cnt, a[10001]; 
struct tree
{
	int l, r, lson, rson; 
	int sum, fsum, bsum, d; //fsum:最大前缀 bsum:最大后缀 sum:区间和 d:最大子段和
}b[20001], new_tree; 

int buildtree(int l, int r)
{
	cnt++; 
	b[cnt].l = l; b[cnt].r = r;
	if(l == r)
	{
		b[cnt].lson = 0; b[cnt].rson = 0; //注意此题多组数据，一定要将叶节点指针清0
		b[cnt].fsum = a[l]; 
		b[cnt].bsum = a[l]; 
		b[cnt].sum = a[l]; 
		b[cnt].d = a[l]; //我的版本不允许出现取空区间的情况，在查询时需要单独判断空区间
		return cnt; 
	}
	
	int tmp = cnt, mid = (l + r) >> 1; 
	b[tmp].lson = buildtree(l, mid); 
	b[tmp].rson = buildtree(mid + 1, r); 
	b[tmp].sum = b[b[tmp].lson].sum + b[b[tmp].rson].sum; 
	b[tmp].fsum = max(b[b[tmp].lson].fsum, b[b[tmp].lson].sum + b[b[tmp].rson].fsum); 
	b[tmp].bsum = max(b[b[tmp].rson].bsum, b[b[tmp].rson].sum + b[b[tmp].lson].bsum); 
	b[tmp].d = max(max(b[b[tmp].lson].d, b[b[tmp].rson].d), b[b[tmp].lson].bsum + b[b[tmp].rson].fsum); 
	return tmp; 
}//建树，维护多个指标
tree query(int t, int l, int r)
{
	if(l > r)return new_tree; //无效查询就返回空节点
	if(l <= b[t].l && r >= b[t].r)
		return b[t]; 
	
	int mid = (b[t].l + b[t].r) >> 1; 
	if(l > mid)
		return query(b[t].rson, l, r); 
	else if(r <= mid)
		return query(b[t].lson, l, r); 
	else
	{
		tree ans, p, q; 
		p = query(b[t].lson, l, r); 
		q = query(b[t].rson, l, r); 
		ans.sum = p.sum + q.sum; 
		ans.fsum = max(p.fsum, p.sum + q.fsum); 
		ans.bsum = max(q.bsum, q.sum + p.bsum); 
		ans.d = max(max(p.d, q.d), p.bsum + q.fsum); 
		return ans; 
	}
}//GSS1的经典做法，将左右子树的前缀后缀拼合成最大子段和
int main()
{
	int t; 
	scanf("%d", &t); 
	while(t--)
	{
		scanf("%d", &n); 
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]); 
		cnt = 0; //根节点清0
		buildtree(1, n); 
		
		scanf("%d", &m); 
		for(int i = 1; i <= m; i++)
		{
			scanf("%d%d%d%d", &x1, &y_1, &x2, &y2); 
			if(y_1 < x2)
				printf("%d\n", max(query(1, x1, y_1 - 1).bsum, 0) + query(1, y_1, x2).sum + max(query(1, x2 + 1, y2).fsum, 0)); //当区间不重叠时直接求出答案
			else
			{
				int tmp = query(1, x2, y_1).d; 
				tmp = max(tmp, query(1, x2, y_1).fsum + query(1, x1, x2 - 1).bsum); 
				tmp = max(tmp, query(1, y_1 + 1, y2).fsum + query(1, x2, y_1).bsum); 
				tmp = max(tmp, query(1, x2, y_1).sum + max(0, query(1, x1, x2 - 1).bsum) + max(0, query(1, y_1 + 1,y2).fsum));//四种情况，注意±1的边界值，避免重复计算
				printf("%d\n", tmp); 
			}
		}
	}
	return 0; 
}
```

---

## 作者：RedreamMer (赞：2)

### [$\texttt{SP2916 GSS5}$](https://www.luogu.com.cn/problem/SP2916)

-----

$GSS$ 的线段树模板题目都非常得经典，可以都做一做。~~除了树剖题~~

前置知识：[$\texttt{SP1043 GSS1}$](https://www.luogu.com.cn/problem/SP1043)的操作

----

### $\texttt{Meaning}$

题目描述已经讲的十分清晰了，这里不做赘述，但是要强调一句话：

> 但是不保证端点所在的区间不重合

所以我们就要对此作出分类讨论（两种）。

---

### $\texttt{Solution}$

首先，对于区间最大子段和，我们要熟练运用 $GSS1$ 中的转移操作，即维护三个区间信息：左起最大子段和，右起最大子段和，区间最大子段和。

学会了这个，我们就要开始分类讨论这道题的情况。

#### 1. 出现 $y_1<x_2$

即两个区间没有重合部分。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6xs9czw9.png)

此时，我们只有一种选择方案：

区间 [$x_1,y_1$] 找到**右起最大子段和**，区间 [$y_1+1,x_2-1$] 的**区间和**，区间 [$x_2,y_2$] 找到**左起最大子段和**，三者相加就是这个询问的答案。

------------

#### 2. 出现 $y_1\ge x_2$

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/t6uk9ava.png)

这个情况的特殊点在于，两个区间有重叠，那我们就不能考虑一种方案了。

分三种情况：

+ 区间 $[x_2,y_1]$ 的**区间最大子段和**
+ 区间 $[x_1,x_2]$ 的**右起最大子段和** $+$ 区间 $[x_2,y_2]$ 的**左起最大子段和**
+ 区间 $[y_1,y_2]$ 的**左起最大子段和** $+$ 区间 $[x_1,y_1]$ 的**右起最大子段和**

这样这个询问的最优解就一定被计算到了，保证了答案的最优。

最后，就能保证所有的询问都是最优的答案。

---

### $\texttt{Code}$

码量确实有点大，细节要注意下


```cpp
#include <bits/stdc++.h>
using namespace std;

#define ls now<<1
#define rs now<<1|1
//#define int long long
const int N=10010;

int t,a,b,s1[N],l1,l2,r1,r2;
struct tree {
	int l,r,lmx,rmx,sum,mx;//l为区间做端点，r为区间右端点，lmx为左起最大子段和，rmx为右起最大子段和，sum为区间和，mx为区间最大子段和 
	tree operator+(const tree x)const {//用这种转移方式或许会更方便，转移方法详见GSS1 
		tree ans;
		ans.l=l;
		ans.r=x.r;
		ans.sum=sum+x.sum;
		ans.lmx=max(lmx,sum+x.lmx);
		ans.rmx=max(x.rmx,x.sum+rmx);
		ans.mx=max(rmx+x.lmx,max(mx,x.mx));
		return ans;
	}
} s[N<<2],ans;

inline void build(int now,int l,int r) {
	s[now].l=l;
	s[now].r=r;
	if(l==r) {
		s[now].sum=s[now].lmx=s[now].rmx=s[now].mx=s1[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	s[now]=s[ls]+s[rs];
}
inline tree query(int now,int l,int r){//query的返回值最好是一颗线段树，方便处理 
	if(s[now].l>=l&&s[now].r<=r) return s[now];
	int mid=(s[now].l+s[now].r)>>1;
	if(l<=mid&&mid<r) return query(ls,l,r)+query(rs,l,r);
	if(l<=mid) return query(ls,l,r);
	else return query(rs,l,r);
}
inline int sum(int now,int l,int r){
	if(l>r) return 0;
	if(s[now].l>=l&&s[now].r<=r) return s[now].sum;
	int mid=(s[now].l+s[now].r)>>1,p=0;
	if(l<=mid) p+=sum(ls,l,r);
	if(mid<r) p+=sum(rs,l,r);
	return p;
}
signed main() {
//	freopen("in1.in","r",stdin);
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&a);
		for(int i=1; i<=a; i++) scanf("%d",&s1[i]);
		build(1,1,a);
		scanf("%d",&b);
//		for(int i=1;i<=(a<<2);i++){
//			cout<<s[i].l<<' '<<s[i].r<<' '<<s[i].lmx<<' '<<s[i].rmx<<' '<<s[i].mx<<' '<<s[i].sum<<endl;
//		}
		for(int i=1; i<=b; i++) {
			scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
			if(r1<l2){//第一种情况 
				printf("%d\n",query(1,l1,r1).rmx+sum(1,r1+1,l2-1)+query(1,l2,r2).lmx);
			}
			else{//第二种情况 
				int f1=query(1,l2,r1).mx,f2=-0x7fffffff,f3=-0x7fffffff;//三种考虑方案，注意一开始变量的初始值设为-inf
				if(l2-1>=l1) f2=query(1,l1,l2-1).rmx+query(1,l2,r2).lmx;//注意两个区间的左端点是否重合，重合就不必考虑 
				if(r1+1<=r2) f3=query(1,r1+1,r2).lmx+query(1,l1,r1).rmx;//注意两个区间的右端点是否重合，重合就不必考虑
				printf("%d\n",max(f1,max(f2,f3)));
			}
		}
	}
	return 0;
}
```

### [$\texttt{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：Azazеl (赞：2)

> 题目传送门:[$SP2916$](https://www.luogu.com.cn/problem/SP2916)

温馨提醒:请确保您已看懂[$GSS1$](https://www.luogu.com.cn/problemnew/solution/SP1043)的题解，这篇题解将围绕它展开.  

对于这道题，做完过后觉得它其实只有紫题水平吧 ~~,但为什么做之前觉得它是纯种黑题呢?~~  

我们来复习一下对于最大子段和,($GSS1$)我们维护了哪些信息?  

区间最大前缀和$(lmaxn)\ \ \ \ \ $ 区间最大后缀和$(rmaxn)\ \ \ \ \ $区间和$(sum)\ \ \ \ \ $  区间最大子段和$(dat)$

现在,我们看这道题,它的两个区间有下面三种情况(借用了圆的思想):  
1.相离($l_2<r_1$)   
2.相切($l_2=r_1$)   
3.相交($l_2>r_1$) 

$1.$两个区间相离  
![无标题.png](https://i.loli.net/2020/01/01/HX7ownv6y1JhcsE.png)  
如图，答案即为  
$$\texttt{rmaxn[l1,l2)+sum[l2,r1]+lmaxn(r1,r2]}$$

$2.$两个区间相切
![无标题.png](https://i.loli.net/2020/01/01/V8BRYADUfbGdXi2.png)  
如图，答案即为  
$$\texttt{rmaxn[l1,l2)+lmaxn[r1,r2]}$$

$3.$两个区间相交
![无标题.png](https://i.loli.net/2020/01/01/FpwVjokZcQbudmB.png)  
这其中又有四种情况.这里不一一画图，大家可以自己理解一下.~~(说白了就是懒得画)~~  
$(1).$答案的区间两个端点在$[l2,r1]$  
$$\texttt{dat[l2,r1]}$$  

$(2).$答案的区间起点在$[l1,l2]$,终点在$(l2,r1]$  
$$\texttt{rmaxn[l1,l2]+lmaxn(l2,r1]}$$

$(3).$答案的区间起点在$[l2,r1]$,终点在$(r1,r2]$
$$\texttt{rmaxn[l2,r1]+lmaxn(r1,r2]}$$

$(4).$答案的区间起点在$[l1,l2]$,终点在$[r1,r2]$  
$$\texttt{rmaxn[l1,l2)+sum[l2,r1]+lmaxn(r1,r2]}$$

在上面四种情况中去最大值即可

但实现的时候可能会有一点问题，为什么呢?我们的线段树存储的是闭区间的信息，但这里会有半开半闭的情况.  
不过查询的时候很简单，只需要把多算的区间减掉即可.

[$\mathcal{CODE}$](https://www.luogu.com.cn/paste/c5vl2v7g)

---

## 作者：Social_Zhao (赞：2)



如果我没有理解错的话，GSS的意思应该就是最大子段和，所以这一堆GSS全是有关最大子段和的题

所以这就有一个现实的问题：最大子段和怎么求？

# 关于最大子段和

裸的最大子段和，也就是GSS1，增加一个单点修改就成了GSS3

其实是有套路的。

我们开一颗线段树，每个节点维护几个值：

区间和、最大前缀和、最大后缀和、最大子段和

这几个值的传递：（证明略）

- 最大前缀和取 max(左儿子的最大前缀和, 左儿子的区间和 + 右儿子的最大前缀和)
- 最大后缀和取 max(右儿子的最大后缀和, 右儿子的区间和 + 左儿子的最大后缀和)

- 最大区间和取 左儿子的区间和 + 右儿子的区间和

- 最大子段和取 max(左儿子的最大子段和, 右儿子的最大子段和, 左儿子的最大后缀和 + 右儿子的最大前缀和)

把这些东西应用于query和pushup，于是得到了GSS1的重要代码：

```cpp
struct Segment {
	int sum, pre, suf, ans;
    //sum：区间和
    //pre：最大前缀和
    //suf：最大后缀和
    //ans：最大子段和
} t[N << 2];

#define lson u << 1, l, mid //习惯极差写法
#define rson u << 1 | 1, mid + 1, r //习惯极差写法
#define lid u << 1 //习惯极差写法
#define rid u << 1 | 1 //习惯极差写法
#define max(a,b) (a > b? a : b)
#define min(a,b) (a < b? a : b)

inline void pushup(int u) {
	t[u].sum = t[lid].sum + t[rid].sum;
	t[u].pre = max(t[lid].pre, t[lid].sum + t[rid].pre);
	t[u].suf = max(t[rid].suf, t[rid].sum + t[lid].suf);
	t[u].ans = max(max(t[lid].ans, t[rid].ans), t[lid].suf + t[rid].pre);
}

inline void build(int u, int l, int r) {
	if(l == r) {
		t[u].ans = t[u].pre = t[u].suf = t[u].sum = num[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(lson), build(rson);
	pushup(u);
}

inline Segment query(int u, int l, int r, int a, int b) {
	if(l == a && r == b) return t[u];
	int mid = (l + r) >> 1;
	if(b <= mid) return query(lson, a, b);
	else if(a > mid) return query(rson, a, b);
	else {
		Segment x = query(lson, a, mid), y = query(rson, mid + 1, b), ans;
		ans.sum = x.sum + y.sum;
		ans.pre = max(x.pre, x.sum + y.pre);
		ans.suf = max(y.suf, y.sum + x.suf);
		ans.ans = max(max(x.ans, y.ans), x.suf + y.pre);
		return ans;
	}
}
```

那么

# 关于本题

本题要求求出左端点 $\in [l_1, r_1]$ ，右端点 $\in [l_2, r_2]$ 的最大子段和，并且保证了$l_1\leq l_2,r_1\leq r_2$

而上面的代码中，我们的最大子段和显然是没有规定范围的，所以直接查询是不可能的了。

但是也不代表着上面的代码就没有用了。

由于数据保证了$l_1\leq l_2,r_1\leq r_2$，所以这两个区间无非就是一下几种情况（这里仿造圆的位置关系）：

1. 外离：$l_2 > r_1 $
2. 相切：$l_2 = r_1$
3. 相交：$l_2 < r_1$

下面我们针对每一种情况来讨论。

1. 对于这种情况，最后的答案必然是$[l_1,r_1)$的最大后缀和加上$[r_1,l_2)$的区间和再加上$[l_2,r_2]$的最大前缀和

   但是我们的query函数是针对闭区间的。解决方法有以下几种：

   - 特判区间$[l_1,r_1-1]$和$[r_1,l_2-1]$是否存在
   - 开区间的端点重复算了一次，因此将其减掉

   于是我选择了后者

2. 答案一定是$[l_1,r_1)$的最大后缀和加上$[r_1,r_2]$的最大前缀和

   和上面同理，我们将开区间的端点减掉

3. 这里又有三种情况。

   - 在重合部分取到了最大值，答案是 $[l_2,r_1]$的最大子段和
   - 在$[l_1, r_1]$取到了最大值，答案是$[l_1,l_2)$的最大后缀和加上$[l_2,r_1]$的最大前缀和
   - 在$[l_2, r_2]$取到了最大值，答案是$[l_2,r_1)$的最大后缀和加上$[r_1,r_2]$的最大前缀和

   然后再这三种情况中找一个最大的答案就是解了

所以代码：

```cpp
#include<bits/stdc++.h>
#define lson u << 1, l, mid
#define rson u << 1 | 1, mid + 1, r
#define lid u << 1
#define rid u << 1 | 1
#define max(a,b) (a > b? a : b)
#define min(a,b) (a < b? a : b)
using namespace std;

inline int get() {
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

const int N = 1e4 + 5;
struct Segment {
	int sum, pre, suf, ans;
} t[N << 2];
int n, m, num[N];

inline void pushup(int u) {
	t[u].sum = t[lid].sum + t[rid].sum;
	t[u].pre = max(t[lid].pre, t[lid].sum + t[rid].pre);
	t[u].suf = max(t[rid].suf, t[rid].sum + t[lid].suf);
	t[u].ans = max(max(t[lid].ans, t[rid].ans), t[lid].suf + t[rid].pre);
}

inline void build(int u, int l, int r) {
	if(l == r) {
		t[u].ans = t[u].pre = t[u].suf = t[u].sum = num[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(lson), build(rson);
	pushup(u);
}

inline Segment query(int u, int l, int r, int a, int b) {
	if(l == a && r == b) return t[u];
	int mid = (l + r) >> 1;
	if(b <= mid) return query(lson, a, b);
	else if(a > mid) return query(rson, a, b);
	else {
		Segment x = query(lson, a, mid), y = query(rson, mid + 1, b), ans;
		ans.sum = x.sum + y.sum;
		ans.pre = max(x.pre, x.sum + y.pre);
		ans.suf = max(y.suf, y.sum + x.suf);
		ans.ans = max(max(x.ans, y.ans), x.suf + y.pre);
		return ans;
	}
}

inline void init() {
    memset(t, 0, sizeof(t));
    memset(num, 0, sizeof(num));
}

inline void solve() {
    init();
    n = get();
    for(register int i = 1; i <= n; i++) num[i] = get();
    build(1, 1, n);
    m = get();
    for(register int i = 1; i <= m; i++) {
        int l1 = get(), r1 = get(), l2 = get(), r2 = get(), ans = 0;
        if(r1 == l2) { //相切的情况
        	ans = query(1, 1, n, l1, r1).suf + query(1, 1, n, l2, r2).pre - num[l2];
		}
        if(r1 < l2) { //外离的情况
            ans = query(1, 1, n, l1, r1).suf + query(1, 1, n, r1, l2).sum + query(1, 1, n, l2, r2).pre;
            ans -= num[r1] + num[l2];
        }
        else { //相交的情况
            ans = query(1, 1, n, l2, r1).ans;
            ans = max(ans, query(1, 1, n, l1, l2).suf + query(1, 1, n, l2, r2).pre - num[l2]);
            ans = max(ans, query(1, 1, n, l1, r1).suf + query(1, 1, n, r1, r2).pre - num[r1]);
        }
        printf("%d\n", ans);
    }
}

int main() {
    int T = get();
    while(T--) solve();
	return 0;
}
```

[$\color{red}{\text{更坏的阅读体验}}$](https://socialzxy.github.io/articles/tj-SP2916.html)

---

## 作者：Bring (赞：1)

## 前置知识：

先是关于序列**GSS**的**四大性质**：

$gssl$ ：最大前缀和（代码用gl表示）

$gssr$ ：最大后缀和（代码用gr表示）

$gss$：最大连续子段和（代码用gs表示）

$sum$：数值和（代码用s表示）

如果知道序列$a$和$b$的四大性质，如何求将$b$序列接在$a$序列之后的新序列的四大性质呢？

$gssl$：

1：右端点在a中，则为$a.gssl$

2：右端点在b中，则为$a.sum+b.gssl$

所以最终为$max(a.gssl,a.sum+b.gssl)$

$gssr$：同理为$max(a.gssr+b.sum,b.gssr)$

$gss$：

1：两个端点都在$a$中，则为$a.gss$

2：两个端点都在$b$中，则为$b.gss$

3：左端点在$a$中，右端点在$b$中，则为$a.gssr+b.gssl$

所以最终为$max(a.gss,b.gss,a.gssr+b.gssl)$

$sum$：$a.sum+b.sum$

所以可以定义结构体$G=${ $gssl,gssr,gss,sum$ }

并定义加法：

关于$G$ $a,b$

$a+b=${

$max(a.gssl,a.sum+b.gssl),$

$max(a.gssr+b.sum,b.gssr),$
    
$max(max(a.gss,b.gss),a.gssr+b.gssl),$

$a.sum+b.sum$

}

加法单位（就是只任何一个G与它相加后都得到本身）：

$zero=${ $-INF,-INF,-INF,0$ }

## 回到题目：

题目要求左端点在$[xa,ya]$，右端点在$[xb,yb]$ $(xa<=xb,ya<=yb)$的$gss$

假设我们已经有一种方法可以快速求出任意连续子段的四大性质，记为$qry(a,b)$表示$[a,b]$的四大性质

1：$ya<xb$，即两个区间相离

那么$[ya+1,xb-1]$一定会全部用上，所以要加上$qry(ya+1,xb-1).sum$

然后$ya$左边要的是$qry(xa,ya).gssr$，$xb$右边要的是$qry(xb,yb).gssl$

所以答案为$qry(xa,ya).gssr+qry(ya+1,xb-1).sum+qry(xb,yb).gssl$

2：$ya>=xb$，即两个区间相交

（1）：两个端点在交集中，则为$qry(xb,ya).gss$

（2）：左端点在交集外，则为$qry(xa,xb-1).gssr+qry(xb,yb).gssl$

（3）：右端点在交集外，则为$qry(xa,ya).gssr+qry(ya+1,yb).gssl$

所以答案为$max($

$qry(xb,ya).gss,$

$qry(xa,xb-1).gssr+qry(xb,yb).gssl,$

$qry(xa,ya).gssr+qry(ya+1,yb).gssl$

$)$

答案的合并是$O(1)$的，关键在于如何求$qry(a,b)$

关注到$G$的加法满足结合律

所以可以使用——**分块系列算法**

~~简单分块我就不讲了~~ $O(n^{\frac{3}{2}})$

**线段树**：一种**二分递归**的分块，每个块的答案都由其分成的两个小块的答案$O(1)$合并而来，高度为$\log_2n$，做到$O(n)$预处理（建树），$O(\log_2n)$查询的非常优秀的算法

然鹅我并不决定用它

~~因为线段树功能太强大了，它还支持修改，对于这样的无需修改的题目来说线段树有点大材小用（但是GSS3就非常适合了）~~

因为我太懒了（感觉码量有点大）

### 其实还有一种大家用过很多次的分块，就是

# 倍增迭代版分块——st表！！！

定义$st[i][k]$表示从第$i$号开始，经过$2^k$个数字后的$G$和

于是有$st[i][0]=${ $a[i],a[i],a[i],a[i]$ }

$st[i][k]=st[i][k-1]+st[i+2^k][k-1]$（怎么样，熟悉吧）

$qry(a,b)$时，从$[a,b]$中取$st[a][\log_2(b-a+1)]$加入，然后$a$加上$2^{\log_2(b-a+1)}$，不断迭代直到$a>b$为止

于是就有了快速版$qry(a,b)${

$G$ $re=${ $-INF,-INF,-INF,0$ }$;$

$while(a<=b)re=re+st[a][\log_2(b-a+1)],a+=2^{\log_2(b-a+1)};$

$return$ $re;$

}

在预先$O(n)$处理所有$\log_2$值后预处理$O(n\log_2n)$，查询$O(\log_2n)$

总时间复杂度$O(n\log_2n)$，且常数极小

上代码(0ms/4.3MB，rank 2)

```cpp
//This program is written by Bring.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define Rd(a) (a=read())
inline int read(){
	register int x;register char c(getchar());register bool k;
	while((c<'0'||c>'9')&&c^'-')if((c=getchar())==EOF)exit(0);
	if(c^'-')x=c&15,k=1;else x=0,k=0;
	while(c=getchar(),c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(register int a){
	if(a<0)putchar('-'),a=-a;
	if(a<=9)putchar(a|'0');
	else wr(a/10),putchar((a%10)|'0');
}
#define Pe putchar('\n')
#define Frn0(i,a,b) for(register int i(a);i<(b);++i)
#define Frn1(i,a,b) for(register int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(register int i(a);i>=(b);--i)
#define NINF signed(0xc3c3c3c3)
#define N (10001)
struct G{
	int gl,gr,gs,s;
	inline G operator+(G b)const{
		return{
            max(gl,s+b.gl),max(b.gr,gr+b.s),
			max(max(gs,b.gs),gr+b.gl),s+b.s
        };
	}
}st[N][14];
int lg[N]{-1},n,m,xa,ya,xb,yb,a,t;
inline G qry(int a,int b);
signed main(){
    Frn0(i,2,N)lg[i]=lg[i>>1]+1;
    Rd(t);
    while(t--){
        Rd(n);
        Frn1(i,1,n)Rd(a),*st[i]={a,a,a,a};
        Frn_(i,n,1)Frn1(k,1,lg[n-i+1])st[i][k]=st[i][k-1]+st[i+(1<<(k-1))][k-1];
        Rd(m);
        while(m--){
            Rd(xa),Rd(ya),Rd(xb),Rd(yb);
            if(ya<xb)wr(qry(xa,ya).gr+qry(ya+1,xb-1).s+qry(xb,yb).gl),Pe;
            else wr(max(qry(xb,ya).gs,max(qry(xa,xb-1).gr+qry(xb,yb).gl,qry(xa,ya).gr+qry(ya+1,yb).gl))),Pe;
        }
    }
	exit(0);
}
inline G qry(int a,int b){
    G re({NINF,NINF,NINF,0});
    while(a<=b)re=re+st[a][lg[b-a+1]],a+=1<<lg[b-a+1];
    return re;
}
```


---

## 作者：斗神_君莫笑 (赞：1)

推荐前置知识：gss1   

本题在gss1的基础上增加了一个区间访问的操作  
本质上还是要把这个所谓的区间询问分开来处理  
楼下大神们讲解的非常好，这里提示几个小细节：   
代码中每个区间的端点必须处理好！  
尤其是当两个区间重叠时候，考虑好哪些点能取，哪些点不能取  
因为lsum和rsum可能为负数，这个考虑不周就会炸  
附上本人的代码
```cpp
#include<bits/stdc++.h>
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
struct Node{
	int l,r,sum,lsum,rsum,ans;
}T[400010];
int a[100010];
inline void pushup(int p){
	T[p].sum=T[lc].sum+T[rc].sum;
	T[p].lsum=max(T[lc].lsum,T[lc].sum+T[rc].lsum);
	T[p].rsum=max(T[rc].rsum,T[rc].sum+T[lc].rsum);
	T[p].ans=max(max(T[lc].ans,T[rc].ans),T[lc].rsum+T[rc].lsum);
}
void build(int p,int l,int r){
	T[p].l=l;T[p].r=r;
	if(l==r){
		T[p].sum=T[p].lsum=T[p].rsum=T[p].ans=a[l];
	 	return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(p);
}
Node query(int p,int ql,int qr){
	if(ql>qr)return (Node){0,0,0,0,0,0};
	//printf("%d %d %d %d\n",ql,qr,T[p].l,T[p].r);
	if(ql<=T[p].l&&T[p].r<=qr) return T[p];
	int mid=(T[p].l+T[p].r)>>1;
    if(ql<=mid&&mid<qr){
    	Node ans,l=query(lc,ql,qr),r=query(rc,ql,qr);
        ans.lsum=max(l.lsum,l.sum+r.lsum);
        ans.rsum=max(r.rsum,r.sum+l.rsum);
        ans.sum=l.sum+r.sum;
        ans.ans=max(max(l.ans,r.ans),l.rsum+r.lsum);
        return ans;
	}
	if(ql<=mid)return query(lc,ql,qr);
	if(qr>mid)return query(rc,ql,qr);
	return (Node){0,0,0,0,0,0};
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		memset(T,0,sizeof(T));
		memset(a,0,sizeof(a));
		int n;scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		build(1,1,n);
		int m;scanf("%d",&m);
		for(int i=1;i<=m;++i){
			int l1,r1,l2,r2;
			scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
			int ans=0;
			if(r1<l2)
				ans=max(query(1,l1,r1-1).rsum,0)+query(1,r1,l2).sum+max(0,query(1,l2+1,r2).lsum);
			else{
				ans=query(1,l2,r1).ans;
				ans=max(ans,query(1,l1,l2).rsum+query(1,l2+1,r1).lsum);
				ans=max(ans,query(1,l2,r1-1).rsum+query(1,r1,r2).lsum);
				ans=max(ans,max(0,query(1,l1,l2-1).rsum)+query(1,l2,r1).sum+max(0,query(1,r1+1,r2).lsum));
				//printf("2   ");
			}
			printf("%d\n",ans);	
		}
	}
	return 0;
}
```

---

## 作者：唔啊唔 (赞：1)

人生第一道黑题（虽然有大佬的一点点指导）

所以也顺便宣传一下[同机房大佬的题解](https://www.luogu.org/blog/wangrxgod/solution-12342)

所以分类讨论的思想什么的，可以在他的题解中理解，但由于这位大佬的码风诡异（真看不懂），所以教练鼓励（怂恿）我写一篇题解。

其实这道题，你若做出了第一问和第三问，便可顺理成章地写出来（要加一点点分类讨论），那么此时这道题便只有紫题难度了。

[第一问题解](https://www.luogu.org/blog/99247/solution-sp1043)

OK，最后附上我的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5000000];
struct HZY{
    int l,r;
    int pre,suf,data,sum;
}t[5000000],s;
inline void build(int l,int r,int k){
    t[k].l=l;
    t[k].r=r;
    if(l==r){
        t[k].sum=a[l];
        t[k].pre=a[l];
        t[k].suf=a[l];
        t[k].data=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,2*k);
    build(mid+1,r,2*k+1);
    t[k].data=max(t[2*k].data,t[2*k+1].data);
    t[k].data=max(t[k].data,t[2*k].suf+t[2*k+1].pre);
    t[k].pre=max(t[2*k].pre,t[2*k].sum+t[2*k+1].pre);
    t[k].suf=max(t[2*k].suf+t[2*k+1].sum,t[2*k+1].suf);
    t[k].sum=t[2*k].sum+t[2*k+1].sum; 
}
int cnt;
inline void ask(int l,int r,int k){
    if(l<=t[k].l&&r>=t[k].r){
        if(cnt==0){
            cnt=1;
            s=t[k];
        }
        else{
			s.pre=max(s.pre,s.sum+t[k].pre);
            s.sum=s.sum+t[k].sum;
            s.data=max(s.data,t[k].data);
            s.data=max(s.data,s.suf+t[k].pre);
            s.suf=max(t[k].suf,s.suf+t[k].sum);
        }
        return;
    }
    int mid=(t[k].l+t[k].r)/2;
    if(l<=mid) ask(l,r,2*k);
    if(r>mid) ask(l,r,2*k+1);
}
int f;
int main(){
	cin>>f;
	for(register int i=1;i<=f;i++){
		scanf("%d",&n);
	    for(register int i=1;i<=n;i++){
	        scanf("%d",&a[i]);
	    }
	    build(1,n,1);
	    scanf("%d",&m);
	    int x,y,z,hzy;
	    for(register int i=1;i<=m;i++){
	    	scanf("%d%d%d%d",&x,&y,&z,&hzy);
	    	if(y+1<z){
	    		int lzf=0;
				cnt=0;
	    		ask(x,y,1);
	    		lzf+=s.suf;
	    		cnt=0;
	    		ask(y+1,z-1,1);
	    		lzf+=s.sum;
	    		cnt=0;
	    		ask(z,hzy,1);
	    		lzf+=s.pre;
	    		printf("%d\n",lzf);
			}
			else if(y+1==z){
				int lzf=0;
				cnt=0;
				ask(x,y,1);
				lzf+=s.suf;
				cnt=0;
				ask(z,hzy,1);
				lzf+=s.pre;
				printf("%d\n",lzf);
			}
			else if(y==z){
				int lzf=0;
				cnt=0;
				ask(x,y,1);
				lzf+=s.suf;
				cnt=0;
				ask(z,hzy,1);
				lzf+=s.pre;
				printf("%d\n",lzf-a[y]);
			}
			else if(y>z){
				int wan=0,zwnpyhm=0;
				cnt=0;
				ask(x,z,1);
				wan+=s.suf;
				cnt=0;
				ask(z,hzy,1);
				wan+=s.pre;
				wan-=a[z];
				cnt=0;
				ask(x,y,1);
				zwnpyhm+=s.suf;
				cnt=0;
				ask(y,hzy,1);
				zwnpyhm+=s.pre;
				zwnpyhm-=a[y];
				cnt=0;
				ask(z,y,1);
				wan=max(wan,s.data);
				printf("%d\n",max(wan,zwnpyhm));
			}
		}
	}
    return 0;
}
```


---

## 作者：木木！ (赞：0)

蒟蒻的分类方法比较粗暴，但是比较麻烦（想不出`dalao`那么短的分类方法QwQ）

首先，可以对所有询问分成两类：

1. 两个区间有重叠部分
2. 两个区间无重叠部分

第二种情况比较简单。无重叠部分的话，可以分出三个段：`[l1 r1] [r1+1 l2-1] [l2 r2]`，答案就是中间一段的和+左端最大后缀+右段最大前缀。需要特判一下中间一段为不为空。

第一种情况，也可以分成三段：`l1 l2-1` `l2 r1` `r1+1 r2`，答案一定存在在这四种情况之中：

+ 中间段的最大子段和
+ 中间段最大前缀+前段最大后缀
+ 中间段最大后缀+后段最大前缀
+ 中间段的和+前段最大后缀+后段最大前缀

分别算出来，取个`max`就好了。需要特判左右端为不为空。

一次询问最多只需要查询三个区间，时间复杂度$\Theta(m\log n)$。

附AC代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

struct node
{
    int lmax;
    int rmax;
    int mmax;
    int sum;
};

node operator + (node l,node r)
{
    return (node){
        max(l.lmax, l.sum+r.lmax),
        max(r.rmax, r.sum+l.rmax),
        max({l.mmax, r.mmax, r.lmax+l.rmax}),
        l.sum+r.sum
    };
}

#define lt(x) (((x)<<1)|1)
#define rt(x) ((x)<<1)

node ti[40005];

node build(int t,int l,int r,int* arr)
{
    if(l==r)
        return ti[t] = (node){ arr[l], arr[l], arr[l], arr[l] };

    int mid = (l+r)>>1;
    return ti[t] = build(lt(t),l,mid,arr)+build(rt(t),mid+1,r,arr);
}

node query(int t,int l,int r,int ql,int qr)
{
    if(l>=ql && r<=qr)
        return ti[t];

    int mid = (l+r)>>1;
    if(mid>=qr)
        return query(lt(t),l,mid,ql,qr);
    if(mid<ql)
        return query(rt(t),mid+1,r,ql,qr);
    return query(lt(t),l,mid,ql,qr)+query(rt(t),mid+1,r,ql,qr);
}

int ai[10005];

int main()
{
    int t;
    scanf("%d",&t);
    for(int lll=1; lll<=t; ++lll)
    {
        int n;
        scanf("%d",&n);
        for(int i=1; i<=n; ++i)
            scanf("%d",ai+i);
        
        build(1,1,n,ai);

        int m;
        scanf("%d",&m);
        for(int i=1; i<=m; ++i)
        {
            int l1,r1,l2,r2;
            scanf("%d%d%d%d",&l1,&r1,&l2,&r2);

            if(r1+1 <= l2-1)
            {
                node mid = query(1,1,n,r1+1,l2-1);
                node left = query(1,1,n,l1,r1);
                node right = query(1,1,n,l2,r2);
                printf("%d\n", left.rmax + mid.sum + right.lmax);
            }
            else if(r1 == l2-1)
                printf("%d\n", query(1,1,n,l1,r1).rmax + query(1,1,n,l2,r2).lmax);

            else if(l2>l1 && r1<r2)
            {
                node mid = query(1,1,n,l2,r1);
                node leftn = query(1,1,n,l1,l2-1);
                node rightn = query(1,1,n,r1+1,r2);

                printf("%d\n",max({
                    mid.sum + leftn.rmax + rightn.lmax,
                    mid.lmax + leftn.rmax,
                    mid.rmax + rightn.lmax,
                    mid.mmax
                }));
            }
            else if(l2==l1 && r1<r2)
            {
                node mid = query(1,1,n,l2,r1);
                node rightn = query(1,1,n,r1+1,r2);
                printf("%d\n",max(mid.rmax+rightn.lmax, mid.mmax));
            }
            else if(l2>l1 && r1==r2)
            {
                node mid = query(1,1,n,l2,r1);
                node leftn = query(1,1,n,l1,l2-1);
                printf("%d\n",max(mid.lmax+leftn.rmax, mid.mmax));
            }
            else
                printf("%d\n",query(1,1,n,l2,r1).mmax);
        }
    }
}
```

---

## 作者：wxwoo (赞：0)

[$$\color{#0e90d2}\huge{\texttt{my blog}}$$](https://wxwoo.github.io/2019/06/14/solution-sp2916)

******

[原题目链接](https://www.luogu.org/problemnew/show/SP2916)

前置知识：不带修区间最大子段和

没做过请先右转[GSS1](https://www.luogu.org/problemnew/show/SP1043)

这题比GSS1多了一个对左右端点的区间限制，GSS1的做法不再适用

这时我们就要分两种情况讨论

情况1：左右端点的区间不相交，即$[x_1,y_1]\cap[x_2,y_2]=\varnothing$

此时$[y_1+1,x_2-1]$为必选区间，我们只能最大化$[x_1,y_1]$的后缀和和$[x_2,y_2]$的前缀和，加上$[y_1+1,x_2-1]$的和即为答案

情况2：左右端点的区间相交
，即$[x_1,y_1]\cap[x_2,y_2]\ne\varnothing$

设最终答案区间左右端点分别为$x_{ans},y_{ans}$

此时答案分4种情况：

1. $\{y_1,x_2\}\subsetneqq[x_{ans},y_{ans}]$

1. $\{y_1\}\subsetneqq[x_{ans},y_{ans}]$

1. $\{x_2\}\subsetneqq[x_{ans},y_{ans}]$

1. $\{y_1,x_2\}\nsubseteqq[x_{ans},y_{ans}]$

情况1即为刚才讨论的左右端点区间不相交的情况

情况2可以最大化$[x_1,y_1]$的后缀和和$[y_1,y_2]$的前缀和求出

情况3可以最大化$[x_1,x_2]$的后缀和和$[x_2,y_2]$的前缀和求出

情况4即为求$[x_2,y_1]$的最大子段和

答案即为这4种情况中的最大值

不难发现，若情况1为最优，则情况1，2，3相等

所以情况1可以通过情况2或3来求出

代码如下

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
template<typename T> inline void read(T &x)
{
    char ch=getchar();
    T f=1;
    x=0;
    while(!('0'<=ch&&ch<='9'))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9')
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    x*=f;
}
const int N=50010;
struct sgttree
{
    int left,right,sum,ans;
}t[N<<2];
int n,m;
int a[N];
#define ls(p) p<<1
#define rs(p) p<<1|1
inline sgttree pushup(sgttree ls,sgttree rs)
{
    sgttree tmp;
    tmp.sum=ls.sum+rs.sum;
    tmp.left=max(ls.left,ls.sum+rs.left);
    tmp.right=max(rs.right,rs.sum+ls.right);
    tmp.ans=max(max(ls.ans,rs.ans),ls.right+rs.left);
    return tmp;
}
void build(int p,int l,int r)
{
    if(l==r)
    {
        t[p].ans=t[p].sum=t[p].left=t[p].right=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    t[p]=pushup(t[ls(p)],t[rs(p)]);
}
sgttree query(int ql,int qr,int l,int r,int p)
{
    if(ql>qr)
        return (sgttree){0,0,0,0};
    if(ql<=l&&r<=qr)
    {
        return t[p];
    }
    int mid=l+r>>1;
    if(qr<=mid)
        return query(ql,qr,l,mid,ls(p));
    if(mid<ql)
        return query(ql,qr,mid+1,r,rs(p));
    sgttree ls,rs;
    if(ql<=mid)
        ls=query(ql,qr,l,mid,ls(p));
    if(mid<qr)
        rs=query(ql,qr,mid+1,r,rs(p));
    return pushup(ls,rs);
}
int main()
{
    int _;
    read(_);
    ++_;
    while(--_)
    {
        memset(t,0,sizeof(t));
    	read(n);
    	for(int i=1;i<=n;++i)
    	    read(a[i]);
    	build(1,1,n);
    	read(m);
    	++m;
    	int ll,lr,rl,rr;
    	while(--m)
    	{
    	    read(ll);
    	    read(lr);
    	    read(rl);
    	    read(rr);
    	    if(lr<rl)
    	        printf("%d\n",query(lr+1,rl-1,1,n,1).sum+query(ll,lr,1,n,1).right+query(rl,rr,1,n,1).left);
    	    else
    	    {
    	        int res=query(rl,lr,1,n,1).ans;
    	        if(ll<rl)
    	            res=max(res,query(ll,rl,1,n,1).right+query(rl,rr,1,n,1).left-a[rl]);
    	        if(rr>lr)
    	            res=max(res,query(ll,lr,1,n,1).right+query(lr,rr,1,n,1).left-a[lr]);
    	        printf("%d\n",res);
            }
    	}
    }
    return 0;
}

```

---

## 作者：Itst (赞：0)

#### 又捡了一道黑题的便宜（雾
### SPOJ的GSS系列都是线段树的好题，其中一部分是围绕最大子段和进行询问，不熟悉最大子段和做法的可以右转[GSS1](https://www.luogu.org/problemnew/show/SP1043)与[GSS3](https://www.luogu.org/problemnew/show/SP1716)一定要注意到最大子段和题目的精髓：pushup的方式。
### 这一题的询问相对来说也比较好实现，只是需要一定分类讨论，如果不能很好理解的话可以画图qwq：
#### $PS:lMax(a,b)$表示区间$[a,b]$的最大前缀，$rMax[a,b]$表示区间$[a,b]$的最大后缀，$ansMax[a,b]$表示区间$[a,b]$的最大子段和
### ①$b<c$时
### $query(a,b,c,d)=sum[b-1,c+1]+rMax[a,b]+lMax[c,d]$
#### (当$b-1>c+1$时，令$sum[b-1,c+1]=0$）
### ②$b \geq c$时，$query(a,b,c,d)$的答案可由3部分得来：
### $a.$左、右端点同时属于$[b,c]$，答案为$ansMax[b,c]$
### $b.$左端点属于$[a,b-1]$，右端点属于$[b,d]$，此时答案为$lMax[a,b-1]+rMax[b,d]$
### $c.$左端点属于$[b,c]$，右端点属于$[c+1,d]$，此时答案为$lMax[b,c]+rMax[c+1,d]$
### 将上面三个答案取$max$就能得到答案了。
------------
### 接下来是代码环节，代码不好看请见谅qwq
```
#include<bits/stdc++.h>
#define MAXN 10001
using namespace std;

inline int max(int a , int b){
    return a > b ? a : b;
}
inline int min(int a , int b){
	return a < b ? a : b;
}

struct node{
    int l , r , lMax , rMax , midMax , sum;
}Tree[MAXN << 2];
int a[MAXN] , N , lMax , rMax , allMax;

void init(int dir , int l , int r){
    Tree[dir].l = l;
    Tree[dir].r = r;
    if(l == r)
        Tree[dir].lMax = Tree[dir].rMax = Tree[dir].midMax = Tree[dir].sum = a[l];
    else{
        init(dir << 1 , l , (l + r) >> 1);
        init(dir << 1 | 1 , ((l + r) >> 1) + 1 , r);
        Tree[dir].sum = Tree[dir << 1].sum + Tree[dir << 1 | 1].sum;
        Tree[dir].lMax = max(Tree[dir << 1].lMax , Tree[dir << 1].sum + Tree[dir << 1 | 1].lMax);
        Tree[dir].rMax = max(Tree[dir << 1 | 1].rMax , Tree[dir << 1].rMax + Tree[dir << 1 | 1].sum);
        Tree[dir].midMax = max(Tree[dir << 1].rMax + Tree[dir << 1 | 1].lMax , max(Tree[dir << 1].midMax , Tree[dir << 1 | 1].midMax));
        //最大子段和线段树问题中pushup操作是精髓！
    }
}

int findSum(int dir , int l , int r){
    if(Tree[dir].l >= l && Tree[dir].r <= r)
        return Tree[dir].sum;
    int sum = 0;
    if(l <= (Tree[dir].l + Tree[dir].r) >> 1)
        sum += findSum(dir << 1 , l , r);
    if(r > (Tree[dir].l + Tree[dir].r) >> 1)
        sum += findSum(dir << 1 | 1 , l , r);
    return sum;
}

//找最大后缀
void findRightMax(int dir , int l , int r){
    if(Tree[dir].l >= l && Tree[dir].r <= r){
        allMax = max(allMax , Tree[dir].rMax + rMax);
        rMax += Tree[dir].sum;
        return;
    }
    if(r > (Tree[dir].l + Tree[dir].r) >> 1)
        findRightMax(dir << 1 | 1 , l , r);
    if(l <= (Tree[dir].l + Tree[dir].r) >> 1)
        findRightMax(dir << 1 , l , r);
}

//找最大前缀
void findLeftMax(int dir , int l , int r){
    if(Tree[dir].l >= l && Tree[dir].r <= r){
        allMax = max(allMax , Tree[dir].lMax + lMax);
        lMax += Tree[dir].sum;
        return;
    }
    if(l <= (Tree[dir].l + Tree[dir].r) >> 1)
        findLeftMax(dir << 1 , l , r);
    if(r > (Tree[dir].l + Tree[dir].r) >> 1)
        findLeftMax(dir << 1 | 1 , l , r);
}

//找最大子段和
void findMax(int dir , int l , int r){
    if(Tree[dir].l >= l && Tree[dir].r <= r){
        allMax = max(allMax , max(Tree[dir].lMax + rMax , Tree[dir].midMax));
        rMax = max(0 , max(Tree[dir].sum + rMax , Tree[dir].rMax));
        return;
    }
	if(l <= (Tree[dir].l + Tree[dir].r) >> 1)
        findMax(dir << 1 , l , r);
    if(r > (Tree[dir].l + Tree[dir].r) >> 1)
        findMax(dir << 1 | 1 , l , r);
}

//找满足a<=b<c<=d时query(a,b,c,d)的答案
inline int getAns(int a , int b , int c , int d){
    int t = 0;
    if(b + 1 < c)
        t += findSum(1 , b + 1 , c - 1);
    if(a <= b){
    	allMax = -0x7fffffff;
    	rMax = 0;
    	findRightMax(1 , a , b);
    	t += allMax;
	}
    if(c <= d){
    	allMax = -0x7fffffff;
    	lMax = 0;
    	findLeftMax(1 , c , d);
    	t += allMax;
    }
    return t;
}

inline int work(int a , int b , int c , int d){
	c = max(a , c);
    b = min(b , d);
    if(b < c)
        return getAns(a , b , c , d);
    else{
    	allMax = -0x7fffffff;
    	rMax = 0;
    	findMax(1 , c , b);
    	int t = allMax;
		return max(max(getAns(a , c - 1 , c , d) , getAns(c , b , b + 1 , d)) , t);
        //这里可以偷点懒hhh
    }
}

int main(){
	//freopen("testdata.in" , "r" , stdin);
	//freopen("testdata.out" , "w" , stdout);
	int T;
    for(cin >> T ; T ; T--){
		cin >> N;
        for(int i = 1 ; i <= N ; i++)
            cin >> a[i];
        init(1 , 1 , N);
        int M;
        for(cin >> M ; M ; M--){
            int a , b , c , d;
            cin >> a >> b >> c >> d;
            printf("%d\n" , work(a , b , c , d));
        }
    }
    return 0;
}
```
## 虽然码数据结构题手都要酸了，Debug又十分烦人，但是看到最后转了很久终于显示的AC不是一件十分诱人的事么qwq

---

