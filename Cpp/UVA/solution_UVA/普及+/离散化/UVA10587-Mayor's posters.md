# Mayor's posters

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1528

[PDF](https://uva.onlinejudge.org/external/105/p10587.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/cd78d581a1fc6c9ec2d9b3173f9b68a09424475e.png)

## 样例 #1

### 输入

```
1
5
1 4
2 6
8 10
3 4
7 10```

### 输出

```
4```

# 题解

## 作者：LevenKoko (赞：12)

先讲一下：dalao @lisuier 发布的前一篇题解严格来讲是有错误的

比如下一组数据：

```
1
3
1 10
1 4
7 10
显然答案是3，然而用lisuier dalao的程序做出来的答案是2（后面会讲错误原因）
```

## ~~简单~~看出这道题用线段树~~可解~~

# so

## 我们用[离散化+权值线段树（戳这里详解）](https://www.luogu.org/blog/cwr/solution-p1908)
~~实际上是安利自己博客~~


思路：建一棵空数，然后把某一区间的颜色更新为读入的颜色；

# WA,SO EASY
OK
那我们先建一棵(10^7*4)的空树
# 然后
就MLE了


# 正经的处理方法

对区间端点进行**离散化**

接下来
引用一下的 @lisuier 的话

>离散化，如下面的例子，因为单位1是一个单位长度，将下面的

>  1   2   3   4  6   7   8   10

> —  —  —  —  —  —  —  —

>  1   2   3   4  5   6   7   8
>离散化 X[1] = 1; X[2] = 2; X[3] = 3; X[4] = 4; X[5] = 6; X[7] =8; X[8] = 10 
这样我们就优化了空间



再看这一组数据

```
1
3
1 10
1 4
7 10
```

用该方法离散化后

第二张海报与第三张海报中间的间隔就**消...消失了**


处理方法：离散化时，加到临时数组b中的右端点+1也加到临时数组中

看起来是这样的
```cpp
int init(){//读入并进行离散处理
    n = read(); tot=0;
    for(int i = 1;i <= n;i++) 
        a[i].l = read(),a[i].r = read(),
        b[++tot] = a[i].l,b[++tot] = a[i].r,b[++tot] = a[i].r + 1;//加入右边的端点+1
    sort(b + 1,b + tot + 1);
    int len=unique(b + 1,b + tot + 1) - b - 1;
    for(int i = 1; i <= n;i++) 
        a[i].l = lower_bound(b + 1,b + len + 1,a[i].l) - b,
        a[i].r = lower_bound(b + 1,b + len + 1,a[i].r) - b; //下面是正常的离散化
    return len; //离散化后总共处理多长的墙; 
}
```
更新之类的与普通线段树差不多

但是要注意push_down操作和query操作

***比如说询问时已经访问过得颜色要标记一下***


# 接下来是
## 简单易懂
### 的代码.
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define M 20005
using namespace std;
inline int read(){
    char chr=getchar(); int f=1,ans=0;
    while(!isdigit(chr)) {if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr))  {ans=ans*10;ans+=chr-'0';chr=getchar();}
    return ans*f;
}
int ans = 0;
struct segment
{
int l,r;
}a[10005 << 4]; 
bool vis[20005 << 4];
struct node
{
    int l,r,val,lazy,sum;
    int mid()
    {
        return l + r >> 1;
    }
}t[M << 4];
int b[20005 << 4],n,tot=0,x,y;
int init()
{//读入并进行离散处理
    n = read(); 
    tot = 0;
    for(int i = 1;i <= n;i++) 
        a[i].l = read(),
        a[i].r = read(),
        b[++tot] = a[i].l,
        b[++tot] = a[i].r,
        b[++tot] = a[i].r + 1;
    sort(b + 1,b + tot + 1);
    int len=unique(b + 1,b + tot + 1) - b - 1;
    for(int i = 1; i <= n;i++) 
        a[i].l = lower_bound(b + 1,b + len + 1,a[i].l) - b,
        a[i].r = lower_bound(b + 1,b + len + 1,a[i].r) - b; 
    return len; //离散化后总共处理多长的墙; 
}
void push_down(int i){
    if(t[i].val == -1)  return;
    t[i << 1].val = t[i << 1 | 1].val = t[i].val;  
    t[i].val = -1;
}
void build(int i,int l,int r)
{
    t[i].l = l;
    t[i].r = r;
    t[i].val = 0;
    if(l == r)
    {
        return;
    }
    int m=t[i].mid();
    build(i << 1,l,m);
    build(i << 1 | 1,m + 1,r);
}
void updata(int i,int l,int r,int x)
{
    if(l <= t[i].l && t[i].r <= r)
    {
        t[i].val = x;
        return;
    }
    push_down(i);
    int m = t[i].mid();
    if(l <= m)  
        updata(i << 1,l,r,x);
    if(r > m)
        updata(i << 1 | 1,l,r,x);
}
void query(int i,int l,int r)
{
    if(t[i].val != -1)
    {
    	 if(!vis[t[i].val])
         {
            vis[t[i].val] = 1;//做标记
            ++ans;
         }
        return;
    }
    query(i << 1,l,r);
    query(i << 1 | 1,l,r);
}

int ask(int l,int r)
{
    memset(vis,0,sizeof(vis));
    ans = 0;
    vis[0] = 1;
    query(1,l,r);
    return ans;
}

int main()
{	
    int T = read();
    while(T--)
    {
        int m=init();   tot=0;//海报染成的颜色
        build(1,1,m);
        for(int i = 1;i <= n;i++)
            updata(1,a[i].l,a[i].r,++tot);
        printf("%d\n",ask(1,m));
    }
    return 0;
}
```














---

## 作者：blackjack (赞：9)

我来写篇动态开点的。
### 首先思考暴力线段树怎么写。

这很简单，我们将贴poster视为染色，这样这个问题就抽象成另一个问题，求颜色总数，这样描述更形象，也提醒我们，可以把poster视为不同的颜色，这样，贴poster就可以看成把区间内的所有数字改成另一个数。这样我们只需要知道这个区间是什么，修改成什么数即可，显然这都是给定的。

### 那么怎么统计颜色个数呢？
我没想到怎么在线统计，但是由于这题只需要我们统计一次，所以我们可以在最后遍历所有叶子节点，用hash标记某个数字代表的颜色出没出现过，没出现过就标记为出现过，然后++ans.

那么我们就有了一个大概的实现方式：线段树节点维护col,lazy-tag，表示这个节点的颜色，这个节点所管理的区间被懒标记标记的颜色。

注意，如果这个节点是叶子节点，则col和lazy-tag都表示这个位置的颜色，如果不是叶子节点，则col表示这个区间的颜色。由于一个区间可能有很多颜色，所以当这个区间只有一个颜色的时候col表示这个区间的颜色，否则col不重要。

那么，对于这个线段树，我们就要开4*坐标范围个节点，这显然是不能接受的。

### 怎么优化呢？
有两个常用方法，一个是离散化，另一个是动态开点。我更喜欢动态开点，这里对动态开点仔细阐述一下。

动态开点的思想、使用原因等，这里不再叙述。

那么对于这题，我们只需要在贴poster的时候直接访问对应区间，然后像区间求和一样把这个对应区间细分（递归完成，这也和区间求和一样），如果细分出的区间不存在，那么就新建这个区间。

那么还有一个问题，怎么在最后统计数字呢？如果使用了动态开点，叶子节点就有可能不存在，如果像正常线段树一样，在每个需要递归处理的地方都下传标记，那么就要在最后访问的时候把叶子节点全部开出来，就又不符合我们动态开点的目的，又要超空间了。

怎么办呢？我们思考一下，标记下传那个地方的意思是什么?

是这个区间被标记为同一个颜色。

为什么要标记下传？因为标记的是之前的操作，可能对后面的操作有影响，时间有先后，对于相同区间，先标记为a颜色后标记为b颜色与先标记为b颜色后标记为a颜色并不相同。

但是，由于我们只统计一次，所以根本不会对后来造成影响，所以在统计的那个函数中递归完成并不需要同时标记下传。

而对于还有标记的区间，意味着这个区间的所有地方是同一个颜色，我们不必再递归下去了，直接return。

注意我写的count函数，可以写

if (!p) return;

表示这个节点不存在，return;先访问再判断存在不存在。

也可以像我这样，先判断儿子节点存在不存在再访问（不存在的话下标是0，相信学过动态开点的都知道）

具体看代码吧。时间复杂度O(nlog10000000)，空间复杂度O(nlog10000000)，显然可过，这里我空间故意开大了很多。
```cpp
#include<bits/stdc++.h>

using namespace std;

int A[110001][3],root=0,ans=0;
int vh[110001],js=0;

struct node{
   int col;
   int left,right;
   int left_son,right_son;
   int lazy;
#define l(x)    (tree[x].left)
#define r(x)    (tree[x].right)
#define lazy(x) (tree[x].lazy)
#define col(x)  (tree[x].col)
#define ls(x)   (tree[x].left_son)
#define rs(x)   (tree[x].right_son)
};

node tree[600001];
void down(int &p){
   if (!lazy(p))
      return ;
   if (!ls(p)){
      ++js;
      ls(p)=js;
      l(ls(p))=l(p);
      r(ls(p))=(l(p)+r(p))/2;
   }
   lazy(ls(p))=lazy(p);
   col(ls(p))=lazy(p);
   if (!rs(p)){
      ++js;
      rs(p)=js;
      l(rs(p))=(l(p)+r(p))/2+1;
      r(rs(p))=r(p);
   }
   col(rs(p))=lazy(p);
   lazy(rs(p))=lazy(p);
   lazy(p)=0;
}
 
void set_sec(int &p,int l,int r,int ll,int rr,int d){
   if (!p){
      ++js;
      p=js;
      l(p)=l;
      r(p)=r;
   }
   if (l(p)>=ll and r(p)<=rr){
      lazy(p)=d;
      col(p)=d;
      return ;
   }
   down(p);
   int mid=(l(p)+r(p))/2;
   if (ll<=mid)
      set_sec(ls(p),l,mid,ll,rr,d);
   if (rr>mid)
      set_sec(rs(p),mid+1,r,ll,rr,d);
}
 
void count(int &p){
   if (lazy(p)){
      if (col(p) and !vh[col(p)]){
         ++ans;
         vh[col(p)]=1;
      }
      return ;
   }
   if (ls(p))
      count(ls(p));
   if (rs(p))
      count(rs(p));
}
 
int main(){
   freopen("test.in","r",stdin);
//   freopen("test.out","w",stdout);
   int t;
   cin>>t;
   int n;
   int minn,maxx;
   while (t){
      --t;
      cin>>n;
      minn=0x3f3f3f,maxx=0;
      for (int i=1;i<=n;++i){
         cin>>A[i][1]>>A[i][2];
         minn=min(minn,A[i][1]);
         maxx=max(maxx,A[i][2]);
      }
      memset(vh,0,sizeof(vh));
      memset(tree,0,sizeof(tree));
      root=1;
      js=1;
      l(root)=minn;
      r(root)=maxx;
      col(root)=0;
      lazy(root)=0;
      for (int i=1;i<=n;++i)
         set_sec(root,minn,maxx,A[i][1],A[i][2],i);
      ans=0;
      count(root);
      cout<<ans<<endl;
   }
   return 0;
}
```


---

## 作者：huayucaiji (赞：6)

# 这个题居然没人用扫描线！！！！  
## 经典的扫描线神题，为什么用线段树  
这道题跟[都市地平线](https://www.luogu.org/problem/P2061)很像，大家可以看看那个题，看看对这个题进行一番思考。

首先，我们可以按平常扫描线的思路走，把每一根线撸出来，放置在数组里，排个序，再把每个海报按起始点排个序，再依次把结构体扔到堆里（堆中按海报编号排序）,最后搞一个堆的懒标记，把已经不影响现在海报的海报移除堆，就结束了QAQ，根本不用线段树。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e4+10;

struct poster {
	int l,r,id;
	
	bool operator < (const poster &b)const {
		return id<b.id;
	}
}a[maxn];

int p[maxn<<1],n;
bool vis[maxn];
priority_queue<poster> q;

bool cmp(poster x,poster y) {
	return x.l<y.l;
}

int main()
{
	ios::sync_with_stdio(0);
	
	int T;
	cin>>T;
	
	int ans;
	while(T--) {
		ans=0;
		memset(vis,0,sizeof(vis));
		cin>>n;
		for(int i=1;i<=n;i++) {
			cin>>a[i].l>>a[i].r;
			a[i].id=i;
			p[i<<1]=a[i].l;
			p[(i<<1)-1]=a[i].r;
		}
		
		sort(a+1,a+n+1,cmp);
		sort(p+1,p+(n<<1)+1);
		
		int cnt=0;
		
		for(int i=1;i<=(n<<1);i++) {
			while(!q.empty()&&q.top().r<=p[i]) {
				q.pop();
			}
			
			while(p[i]<=a[cnt+1].l&&a[cnt+1].l<p[i+1]) {
				q.push(a[++cnt]);
			}
			if(!q.empty()) {
				vis[q.top().id]=1;
			}
		}
		
		for(int i=1;i<=n;i++) {
			ans+=(vis[i]);
		}
		cout<<ans<<endl;
		while(!q.empty()) {
			q.pop();
		}
	}
	
	return 0;
}
  
```

---

## 作者：傅思维666 (赞：3)

题解：
离散化+线段树。

因为你开10000000*4的线段树一定会MLE，所以我们这里需要引入离散化。

离散化模板抄的是大佬的。

应该是非常好用的一个模板，在此推荐给大家。

然后就是线段树了/

我在这里要着重讲一下让本蒟蒻痛苦不已的pushdown操作。

pushdown操作是线段树的精髓！！

我们假设节点now所表示的区间[L,R]，且tag[now]=id,说明now节点的整个区间都被id覆盖，就不需要再继续往它的儿子节点传递这一信息。只有当我们需要修改这个大区间的某一个子区间的时候，我们才把当前的标记下传到左右子节点，然后把当前的tag[now]清零。

这个过程请大家一定好好理解，非常重要。

最后我们需要统计答案，使用标记数组。

v[i]表示第i号海报是否被遍历过，注意，它有可能只被挡住一部分。

所以我们得出了完整思路：

输入数据，直接离散化，然后按照排好序之后的海报一张一张地开始修改，pushdown，最后依次寻找答案。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#define lson pos<<1
#define rson pos<<1|1
using namespace std; 
const int maxn=200004;    
int tag[maxn<<2],v[maxn<<2],ans;      
void mark(int l,int r,int now,int v) 
{
    if(r<l) return;  
    tag[now]=v;      
}
void pushdown(int l,int r,int now) 
{
    if(tag[now]) 
    {
        int mid=(l+r)>>1;  
        mark(l,mid,now<<1,tag[now]); 
        mark(mid+1,r,now<<1|1,tag[now]); 
        tag[now]=0; 
    }
}
void update(int l,int r,int now,int L,int R,int id) 
{
    if(l>=L&&r<=R)
    {
        tag[now]=id;  
        return;   
    }      
    pushdown(l,r,now);   
    int mid=(l+r)>>1;  
    if(L<=mid) update(l,mid,now<<1,L,R,id); 
    if(R>mid) update(mid+1,r,now<<1|1,L,R,id);  
} 
void getans(int l,int r,int now) 
{
    if(tag[now]) 
    {
        if(v[tag[now]]==0) 
        {
            v[tag[now]]=1, ans++;
        }
        return; 
    }    
    if(l==r) return; 
    int mid=(l+r)>>1; 
    if(mid>=l) getans(l,mid,now<<1); 
    if(r>mid) getans(mid+1,r,now<<1|1);   
}  
void re(int l,int r,int now) 
{
    v[tag[now]]=0,tag[now]=0; 
    if(l==r) 
    {
        return; 
    }
    int mid=(l+r)>>1;  
    if(l<=mid) re(l,mid,now<<1); 
    if(r>mid) re(mid+1,r,now<<1|1);  
}
int c;    
int A[10002<<1];   
struct tree
{
    int l,r,L,R; 
}t[10001<<2];  
int main()
{
    scanf("%d",&c);
    while(c--)
    {
        int n,cnt=0; 
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&t[i].l,&t[i].r);  
            A[++cnt]=t[i].l, A[++cnt]=t[i].r; 
        }
        sort(A+1,A+1+cnt);  
        for(int i=1;i<=n;++i) 
        { 
            t[i].L=lower_bound(A+1,A+1+cnt,t[i].l)-A; 
            t[i].R=lower_bound(A+1,A+1+cnt,t[i].r)-A; 
        }    
        for(int i=1;i<=n;i++) { 
            update(1,cnt,1,t[i].L,t[i].R,i);   
        }
        getans(1,cnt,1);   
        printf("%d\n",ans);
        ans=0;  
        re(1,cnt,1);  
    }
    return 0;
}
```


---

## 作者：Schwarzkopf_Henkal (赞：1)

题解里头一水的是离散化+线段树，这篇介绍一下珂朵莉树写法。

珂朵莉树的原名是老司机树（Old Driver Tree），起源[CF896C](https://www.luogu.com.cn/problem/CF896C)，是一种暴力数据结构，特点是会用set就能打，而且自带离散化。稍微推销一下我自己写的[博客](http://175.24.116.241/index.php/2020/07/29/chtholly-tree/)，对珂朵莉树没有啥了解的可以去看看。

我们知道珂朵莉树复杂度正确（某种意义上）的核心就在于那个区间推平 assign 操作。现在这题全是 assign 操作不用珂朵莉树用啥？

那么针对这题的具体实现的话……会给你几个区间，然后我们对于每个区间，把它 assign 到当前区间的编号，最后扫一遍树里面的每一个块，标记一下，然后计数就可以了。具体的话，看代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,mk[10005];
struct node{
    int l,r;
    mutable int val;
    friend bool operator<(node a,node b){
        return a.l<b.l;
    }
};
set<node>odt;
typedef set<node>::iterator iter;
iter split(int p){
    iter it=odt.lower_bound({p,p,0});
    if(it!=odt.end()&&it->l==p)
        return it;//左闭右开
    it--;
    int l=it->l,r=it->r,val=it->val;
    odt.erase(it);
    odt.insert({l,p-1,val});
    return odt.insert({p,r,val}).first;
}
void assign(int l,int r,int x){
    iter itr=split(r+1),itl=split(l);
    odt.erase(itl,itr);//左闭右开。
    odt.insert({l,r,x});
}
int main(){
    cin>>T;
    while(T--){
        odt.clear();
        memset(mk,0,sizeof(mk));
        cin>>n;
        odt.insert({1,(int)1e8,0});
        for(int i=1,a,b;i<=n;i++){
            cin>>a>>b;
            assign(a,b,i);
        }
        for(iter i=odt.begin();i!=odt.end();i++)
            mk[i->val]=1;
        int ans=0;
        for(int i=1;i<=n;i++)
            if(mk[i])
                ans++;
        cout<<ans<<'\n';
    }
}
```
I'm Schwarzkopf Henkal.

---

## 作者：jockbutt (赞：1)

这是一道很经典的线段树+离散化。
线段树其实没什么变化，按照模板套就行了，这不是重点。
以下是这道题线段树的代码。
```cpp
void pushdown(int rt)
{
	if(color[rt]!=-1)
	{
		color[rt<<1]=color[rt<<1|1]=color[rt];
		color[rt]=-1;
	}
} 
void update(int L,int R,int c,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		color[rt]=c;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	if(mid>=L)	update(L,R,c,l,mid,rt<<1);
	if(mid<R)	update(L,R,c,mid+1,r,rt<<1|1);
}
void query(int l,int r,int rt)
{
    if(color[rt]!=-1)
    {
        if(!hassh[color[rt]]) ans++;
        hassh[color[rt]]=1;
        return;
    }
    if(l==r) return;
    int mid=(l+r)>>1;
    query(l,mid,rt<<1);
    query(mid+1,r,rt<<1|1);
}
```
接下来（敲黑板，划重点）是离散化。

浅谈离散化：离散化主要是对空间的优化。这道题有1e7的数组，再开个4倍就快爆了。离散化可以大大地减少所需的空间。

离散化思想：用最简短的数组来表示一个很大的数组。就以这道题来说，假设有一个这样的区间：11111111111111111111，需要用20个变量来存，但是，你可以这样表示a[1].weizhi=1,a[1].color=1,a[2].weizhi=20,a[2].color=1这4个变量就存下了。

具体实现有很多方法，以下是其中一种：
```
for(int i=0;i<n;i++)
		{
			x[res++]=ll[i];
			x[res++]=rr[i];
		}
		sort(x,x+res);
		int ress=1;
		for(int i=1;i<res;i++)
		{
			if(x[i]!=x[i-1])
			{
				x[ress++]=x[i];
			}
		}
		for(int i=ress-1;i>0;i--)
		{
			if(x[i]!=x[i-1]+1)
			{
				x[ress++]=x[i-1]+1;
			}
		}
		sort(x,x+ress);
```
有点饶人。

最后是AC代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm> 
using namespace std;
int color[100100<<2];
int	hassh[100100];
int n,x[100100],ll[100100],rr[100100];
int ans=0;
void pushdown(int rt)
{
	if(color[rt]!=-1)
	{
		color[rt<<1]=color[rt<<1|1]=color[rt];
		color[rt]=-1;
	}
} 
void update(int L,int R,int c,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		color[rt]=c;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	if(mid>=L)	update(L,R,c,l,mid,rt<<1);
	if(mid<R)	update(L,R,c,mid+1,r,rt<<1|1);
}
void query(int l,int r,int rt)
{
    if(color[rt]!=-1)
    {
        if(!hassh[color[rt]]) ans++;
        hassh[color[rt]]=1;
        return;
    }
    if(l==r) return;
    int mid=(l+r)>>1;
    query(l,mid,rt<<1);
    query(mid+1,r,rt<<1|1);
}
int erfen(int k,int w)
{
    int l=0,r=w-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(k==x[mid]) return mid;
        if(k>x[mid]) l=mid+1;
        else r=mid-1;
    }
    return -1;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		scanf("%d",&n);
		memset(hassh,0,sizeof(hassh));
		memset(color,-1,sizeof(color));
		for(int i=0;i<n;i++)
		{
			scanf("%d%d",&ll[i],&rr[i]);
		}
		int res=0;
		for(int i=0;i<n;i++)
		{
			x[res++]=ll[i];
			x[res++]=rr[i];
		}
		sort(x,x+res);
		int ress=1;
		for(int i=1;i<res;i++)
		{
			if(x[i]!=x[i-1])
			{
				x[ress++]=x[i];
			}
		}
		for(int i=ress-1;i>0;i--)
		{
			if(x[i]!=x[i-1]+1)
			{
				x[ress++]=x[i-1]+1;
			}
		}
		sort(x,x+ress);
		for(int i=0;i<n;i++)
		{
			int l=erfen(ll[i],ress);
			int r=erfen(rr[i],ress);
			update(l,r,i,0,ress,1);
		}
		query(0,ress,1);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：lisuier (赞：1)

一看线段树没跑了对吧？
就像染色一样，贴一张海报就把那一段染上新颜色，
这就是个很裸的区间修改嘛，
最后统计线段上有多少种不同颜色输出答案，
完了。
好吧其实没完
注意海报长度明显爆内存
所以要用离散化
因为海报的张数显然爆不了内存
关于离散化这是我找的例子

离散化，如下面的例子，因为单位1是一个单位长度，将下面的

      1   2   3   4  6   7   8   10

     —  —  —  —  —  —  —  —

      1   2   3   4  5   6   7   8

离散化  X[1] = 1; X[2] = 2; X[3] = 3; X[4] = 4; X[5] = 6; X[7] = 8; X[8] = 10
这样我们就优化了空间
~~~
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
ll sum[1000101]={0},add[1000101]={0},a[1001001],ans[1000101]={0};
int n,m;
struct node{
	int s,id,id2;
}e[1000101];
void pushup(ll rt){
    if(!sum[rt<<1]||!sum[rt<<1|1]||sum[rt<<1]!=sum[rt<<1|1])
        sum[rt]=0;
    else
        sum[rt]=sum[rt<<1|1] ;
}
void pushdown(ll rt,ll ln,ll rn){
	if(add[rt]!=-1){
		add[rt<<1]=add[rt];
		add[rt<<1|1]=add[rt];
		sum[rt<<1]=add[rt];
		sum[rt<<1|1]=add[rt];
		add[rt]=-1;
	}
}
void update(ll l,ll r,ll c,ll L,ll R,ll rt){
	if(l>=L&&r<=R){
		sum[rt]=c;
		add[rt]=c;
		return ;
	}
	ll mid=(l+r)>>1;
	pushdown(rt,mid-l+1,r-mid);
	if(L<=mid)update(l,mid,c,L,R,rt<<1);
	if(R>mid) update(mid+1,r,c,L,R,rt<<1|1);
	pushup(rt);
}
void query(ll l,ll r,ll L,ll R,ll rt){
	if(sum[rt]==-1)
        return ;
    else if(sum[rt]>0){
        ans[sum[rt]]=1;
        return ;
    }
	ll mid=(l+r)>>1;
	pushdown(rt,mid-l+1,r-mid);
	query(l,mid,L,R,rt<<1);
	query(mid+1,r,L,R,rt<<1|1);
	pushup(rt);
}
bool cmp(node a,node b){
	return a.s<b.s;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
	scanf("%d%d",&e[i].s,&e[i+m].s);
	e[i].id=i;e[i+m].id=i+m;	
	}
	sort(e+1,e+2*m+1,cmp);
	//build(1,n,1);
	int temp=-1;
    n=0;
    for(int i=1;i<=2*m;i++){
        if(e[i].s==temp)
            e[i].id2=n;
        else{
            e[i].id2=++n;
            temp=e[i].s;
        }
        a[e[i].id]=e[i].id2;
    }
    memset(sum,-1,sizeof(sum));
    memset(add,-1,sizeof(add));
    memset(ans,0,sizeof(ans));
    for(int i=1;i<=m;i++){
    	update(1,n,i,a[i],a[i+m],1);
	}
	query(1,n,1,n,1);
	int cnt=0;
	for(int i=1;i<=m;i++){
		if(ans[i]>0)cnt++;
	}
	printf("%d\n",cnt);	
	}
    return 0;
}
~~~
完了emm


---

## 作者：quest_2 (赞：0)

**写在最前**：本题解的思路是 $RUI \_ R$ 大佬给小蒟蒻点拨的，在此先表示感谢， [点此膜大佬](https://www.luogu.com.cn/user/101984)

**UPD**：稍微纠正了一些错误，加上了一些讲解（2020-7-29）

### 题意稍加简述：

其实是 [P3740](https://www.luogu.com.cn/problem/P3740) 的数（shuang）据（bei）加（jing）强（yan）题？这里搬运一波翻译。

$\mathtt{Bytetown}$ 城市要进行市长竞选，所有的选民可以畅所欲言地对竞选市长的候选人发表言论。为了**统 一 管 理**，城市委员会为选民准备了一个张贴海报的 $\mathtt{electoral}$ 墙。

**张贴规则如下**：

1. $\mathtt{electoral}$ 墙是一个长度为N个单位的长方形，每个单位记为一个格子；

1. 所有张贴的海报的高度必须与 $\mathtt{electoral}$ 墙的高度一致的；

1. 每张海报以“$A\quad B$”表示，即从第 $A$ 个格子到第 $B$ 个格子张贴海报；

1. 后贴的海报可以覆盖前面已贴的海报或部分海报。

现在请你判断，张贴完所有海报后，在 $\mathtt{electoral}$ 墙上还可以看见多少张海报。

但是那道绿题能 ${\color{green}AC}$ 的代码（笔者那时候用的不离散化线段树）在这道紫题未必能过，为什么？~~笔者太蒻~~，一来海报数量增多，二来加入多组数据，增大了 $\color{black}TLE$ 的可能性。我们需要找到一种更有（bao）效（li）的方法做题。

### 向带伙隆重推荐：珂 朵 莉 树（ $\mathtt{ODT}$ ）
珂朵莉树是一种比线段树**更好打**，比树状数组**更易理解**，比分块**更暴力**的和树一点关系没有的数据结构，作为一个名字里带**树**的数据结构，他是用 $set$ 维护的（笑）。

珂朵莉树支持的操作其实不少：区间修改、查找 $k$ 大值、区间赋值、区间询问$\dots\dots$其复杂度趋向 $m\log{n}$ 。为什么？我们随后会讲。我们现在只需要知道，珂朵莉树可以切许许多多标程是线段树的题目，并且时不时**爆踩标程**（雾）。

先来讲解珂朵莉树的有关思想：珂朵莉树的一个重要思想就是找集合里**需要修改的部分推平**（暴力的气息），再**添加**这个被推平区间的新点进入集合。（即把**用不着的清除，留下一个新的代表**）。而从整个集合里找到需要修改的部分，并对其单独修改，靠的是分裂 $\operatorname{split}$ ：

非常玄学的算法，我们画个图尝试理解流程。

**一、从整个区间里分裂出要修改区间**

首先我们需要找到目标位置所在区间

![](https://cdn.luogu.com.cn/upload/image_hosting/ce3qwvey.png)
这里我们二分找到下一张海报。那么下一张海报的迭代器 $-1$ 就是 $pos$ 所在的这张海报的位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/6q6m0pcl.png)

将这张海报分割成 $l->pos-1$ 和 $pos->r$ 两个区间。这样我们就可以单独处理一部分的区间了。具体操作就是直接删掉这整个大块区间，然后再插入两个小块的区间（暴力气息逐渐浓厚）。

**二、暴力赋值要修改的区间**

这才是整个赋值实现里最精彩的部分，不如看一下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/swhfdktm.png)

我们要把 $x->y$ 赋值成 $val$ ，倘若我们已经把 $x$ 到他的区间末尾， $y$ 到他的区间头这两段区间单独分离出来了，他们加在一起就是我们要赋值的区间。

![](https://cdn.luogu.com.cn/upload/image_hosting/26bnlj5i.png)

对于这两小块，我们暴力推平他们，暴力插入一个新区间，暴力赋值为 $val$ （~~毁灭即重建~~）

这一思想体现在代码里就像下面这样:

```cpp
#define IT set<node>::iterator//纯粹懒得打
struct node
{
     int l, r;
     mutable int val;
//我们知道set里的普通元素是不能修改的，这里的mutable可以解决这一问题。
     node(int a=0,int b=0,int c=0)
     {
          l = a;
          r = b;
          val = c;
     }
     bool operator <(const node a)const
     {
          return l < a.l;
     }//重载运算符<，便于处理海报时从左到右处理
};
set<node> s;
IT split(int pos)//将pos所在区间分裂成以pos为界线的两个小区间
{
     IT it= s.lower_bound(node(pos, 0, 0));
     //取下一个海报头的位置，也就是这次要分裂的区间右限
     if(it!=s.end()&&it->l==pos)
     {//他不是最后一个海报（指位置），且他自己就是下一个海报的开头
          return it;
          //pos已经在我们是要更改的区间*it里了，到时候处理*it自己所在区间
     }
     it--;//处理上一个区间，这才是pos所在区间
     int L = it->l, R = it->r, VAL = it->val;
     s.erase(it);//这里到下个海报之前的这些位置就先删了
     s.insert(node(L, pos-1, VAL));
     //将我们删除的这个区间的前半部分（l~pos-1)加入集合
     return s.insert(node(pos, R, VAL)).first;
     //将我们删除的这个区间的后半部分(pos~r)加入集合
     //不会有人不知道insert是有pair返回值的，而且返回值的first是插入的位置的吧！(yygq)
}
void assign(int l,int r,int val)
{
     IT it2 = split(r + 1), it1 = split(l);
     //因为我们处理时是默认是左闭右开的区间，所以要找到r+1
     //先找r+1防的是分离l的时候不小心把r+1所在区间删了
     s.erase(it1, it2);
     //这段都扬喽
     s.insert(node(l, r, val));
     //插回一个新代表，代表的val是我们要赋的新值
}
```
有了上面这些操作，我们解决这道题已经游刃有余了，贴海报的动作无非就是**区间推平**，再赋上代表这张海报的编号值。我们可以用 $map$ 存最终情况下每种海报**是否已计入总数**，若出现则 $ans+\!+$ ，$map$ 里对应的值改为 $true$ ，放一个主函数里的代码：

```cpp
map<int, int> color;
int main()
{
     ios::sync_with_stdio(0);//cin,cout信仰优化
     int T;
     cin >> T;
     while (T--)
     {
          int N;
          cin >> N;
          s.clear();
          color.clear();//清空set和map
          s.insert(node(0, 1e7 + 7, 0));
          //开始的时候有一个很大很大的白墙等着贴海报
          for (int i = 1; i <= N; i++)
          {
               int l, r;
               cin >> l >> r;
               assign(l, r, i);
               //区间赋值，覆盖前面的
          }
          int res = 0;
          for (IT i = s.begin(); i != s.end(); i++)
          {
               if (i->val >= 1 && i->val <= N && !color[i->val])
               //倘若这个地方贴过一张海报（val不为0）
               //并且这张海报还没被统计过
               {
                    res++;
                    color[i->val] = 1;//统计进这张海报
               }
          }
          cout << res << endl;
     }
}
```
我们再来考虑之前的复杂度问题，为什么珂朵莉树可以逼近甚至超越线段树？其实很好解释，我们的 $set$ 里的元素可不是始终有 $N$ 个，我们经过 $\operatorname{assign}$ 的**清除元素留代表**的工作，已经在不断地**消减我们的工作量**，最终这里的工作量是趋于 $\log{n}$ 的（玄学）。

### 代码如下：
```cpp
#include <iostream>
#include <set>
#include <map>
using namespace std;
#define IT set<node>::iterator
struct node
{
     int l, r;
     mutable int val;
     bool operator<(const node &b) const
     {
          return l < b.l;
     }
     node(int a = 0, int b = -1, int c = 0)
     {
          l = a;
          r = b;
          val = c;
     }
};

set<node> s;

inline IT split(int pos)
{
     IT it = s.lower_bound(node(pos, 0, 0));
     if (it != s.end() && it->l == pos)
     {
          return it;
     }
     it--;
     int L = it->l, R = it->r, V = it->val;
     s.erase(it);
     s.insert(node(L, pos - 1, V));
     return s.insert(node(pos, R, V)).first;
}
inline void assign(int l, int r, int val)
{
     IT it2 = split(r + 1), it1 = split(l);
     s.erase(it1, it2);
     s.insert(node(l, r, val));
}
map<int, int> color;
int main()
{
     ios::sync_with_stdio(0);
     int T;
     cin >> T;
     while (T--)
     {
          int N;
          cin >> N;
          s.clear();
          color.clear();
          s.insert(node(0, 1e7 + 7, 0));
          for (int i = 1; i <= N; i++)
          {
               int l, r;
               cin >> l >> r;
               assign(l, r, i);
          }
          int res = 0;
          for (IT i = s.begin(); i != s.end(); i++)
          {
               if (i->val >= 1 && i->val <= N && !color[i->val])
               {
                    res++;
                    color[i->val] = 1;
               }
          }
          cout << res << endl;
     }
}
```

其实珂朵莉树的妙处不止止体现在这里，有兴趣的读者可以移步 [CF896C](https://www.luogu.com.cn/problem/CF896C) ，一道黑题，也是珂朵莉树和这个名字发源的地方，可以尝试体验一把。（~~逃~~）

---

## 作者：_NoOne (赞：0)

本题可离散化，也可动态开点 + 值域线段树，不过要开大概1e4 * 40的空间。

一些设定：
```cpp
struct segTree{
	int Lson, Rson; //左右儿子编号
	int l, r;	//对应值域
	int color;	//颜色标记
};
vector<segTree>Tree;
#define Lnode Tree[node].Lson
#define Rnode Tree[node].Rson
```
动态建树：
```cpp
inline void build(int &node, int L, int R){
	if(node) return;
	node = ++tot;
	Tree[node].l = L, Tree[node].r = R;
}

build(root, 1, 1e7);
```
每贴一张海报（读入l, r），就进行一次区间更新, 开辟左右儿子，对节点打上颜色标记：

```cpp
inline void change(int L, int R, int color, int node){
	if(!node) return;
	if(Tree[node].l == L && Tree[node].r == R){ 
		Tree[node].color = color;
		return;
	}
	int mid = (Tree[node].l + Tree[node].r) >> 1;
	build(Lnode, Tree[node].l, mid), build(Rnode, mid + 1, Tree[node].r); 
		//动态开辟左右儿子 左儿子的左右端点分别为父亲结点的l, mid
	pushTag(node); //下传标记
	if(R <= mid) change(L, R, color, Lnode);
	else if(L > mid) change(L, R, color, Rnode);
	else change(L, mid, color, Lnode), change(mid + 1, R, color, Rnode);
}
```
最后查询用set即可：

```cpp
if(!node) return; //不存在结点 直接return
if(Tree[node].color){ //叶子节点被染色 存入set 根据set的大小判断显示的海报数
	s.insert(Tree[node].color);
	return;
}
```
Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 4;
const int LOG = 40;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
struct segTree{
	int Lson, Rson; //左右儿子编号
	int l, r;	//对应值域
	int color;	//颜色标记
};
vector<segTree>Tree;
#define Lnode Tree[node].Lson
#define Rnode Tree[node].Rson
int testCase, root, tot;
inline void build(int &node, int L, int R){
	if(node) return;
	node = ++tot;
	Tree[node].l = L, Tree[node].r = R;
}
inline void pushTag(int node){
	if(!Tree[node].color) return;
	Tree[Lnode].color = Tree[Rnode].color = Tree[node].color;
	Tree[node].color = 0;
}
inline void change(int L, int R, int color, int node){
	if(!node) return;
	if(Tree[node].l == L && Tree[node].r == R){ 
		Tree[node].color = color;
		return;
	}
	int mid = (Tree[node].l + Tree[node].r) >> 1;
	build(Lnode, Tree[node].l, mid), build(Rnode, mid + 1, Tree[node].r); //动态开辟左右儿子
	pushTag(node); //下传标记
	if(R <= mid) change(L, R, color, Lnode);
	else if(L > mid) change(L, R, color, Rnode);
	else change(L, mid, color, Lnode), change(mid + 1, R, color, Rnode);
}
set<int>s;
inline void query(int L, int R, int node){
	if(!node) return; //不存在结点 直接return
	if(Tree[node].color){ //叶子节点被染色 存入set 根据set的大小判断显示的海报数
		s.insert(Tree[node].color);
		return;
	}
	int mid = (Tree[node].l + Tree[node].r) >> 1;
	if(R <= mid) query(L, R, Lnode);
	else if(L > mid) query(L, R, Rnode);
	else query(L, mid, Lnode), query(mid + 1, R, Rnode); 
}
int main(){
	testCase = read();
	while(testCase--){
		s.clear();
		root = tot = 0;
		int n = read();
		Tree.clear(), Tree.resize(MAXN * LOG);
		build(root, 1, 1e7);
		for(int i = 1; i <= n; i++){
			int l = read(), r = read();
			change(l, r, i, root);
		}
		query(1, 1e7, root);
		cout << s.size() << endl;
	}
	return 0;
}
```




---

