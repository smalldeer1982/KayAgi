# [CERC2015] Cow Confinement

## 题目描述

附近的一个牧场可以表示为一个由 $10^6$ 行和 $10^6$ 列组成的矩形网格。行从上到下用整数 $1$ 到 $10^6$ 编号，列从左到右用整数 $1$ 到 $10^6$ 编号。

一群共 $n$ 头牛分散在网格中，每头牛占据一个单位方格。牧场中还包含 $m$ 朵蒲公英花（牛喜欢的花），同样每朵花占据一个单位方格。此外，牧场包含 $p$ 个栅栏，每个栅栏是一个沿单位方格边缘延伸的矩形。栅栏之间不会相交或接触。然而，一个栅栏内部可能包含其他栅栏。

由于不利的风向条件，牛只能朝两个方向移动——向下或向右。牛可以经过被其他牛或花占据的方格，但不能穿过栅栏。  
对于每头牛，求从它当前位置可以到达的花朵总数。

## 说明/提示

样例图示：

![](https://cdn.luogu.com.cn/upload/pic/16231.png)

Central Europe Regional Contest 2015  
Problem C

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4 
2 2 8 4 
1 9 4 10 
6 7 9 9 
3 3 7 3 
9 
3 4 
8 4 
11 5 
10 7 
10 8 
9 8 
2 8 
4 11 
9 11 
8 
1 1 
5 10 
6 9 
3 7 
7 1 
4 2 
7 5 
3 3```

### 输出

```
5 
1 
0 
1 
3 
1 
3 
0 ```

# 题解

## 作者：starusc (赞：11)

线段树加扫描线维护答案的差分。加花单点加 1，查询后缀和。

![](https://cdn.luogu.com.cn/upload/image_hosting/6p3nrz77.png)

加入右区间时把绿色点加上蓝色区域的值（实际上不是到底，而是到下一个栅栏）（因为我们新加入两条栅栏后就走不下来了），然后把橘色区域清零（会被栅栏挡住）。

删除左区间时把棕色区域清零（会被栅栏挡住），并在粉色点减去紫色区域的值（去掉两条栅栏后，粉色点可能先下后右，或先右后下，会算重，所以减掉去重）。

注意排序顺序：先右区间，然后左区间，然后加花，最后查询。

时间复杂度 $O(n\log n)$。

```cpp
//starusc
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1,c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f==1?x:-x;
}
const int N=2e5+4,M=1e6+4,mx=1e6+1;
namespace seg{
	#define lc (p<<1)
	#define rc (p<<1|1)
	int t[M<<2],lz[M<<2];
	inline void pushdown(int p,int l,int r){
		if(!lz[p])return;
		lz[lc]=lz[rc]=1;
		t[lc]=t[rc]=0;
		lz[p]=0;
	}
	inline void pushup(int p){
		t[p]=t[lc]+t[rc];
	}
	void modify(int p,int l,int r,int x,int v){
		if(l==r){
			t[p]+=v;
			return;
		}
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(x<=mid)modify(lc,l,mid,x,v);
		else modify(rc,mid+1,r,x,v);
		pushup(p); 
	}
	void cover(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr){
			lz[p]=1;
			t[p]=0;
			return;
		}
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(ql<=mid)cover(lc,l,mid,ql,qr);
		if(mid<qr)cover(rc,mid+1,r,ql,qr);
		pushup(p);
	}
	int query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return t[p];
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(qr<=mid)return query(lc,l,mid,ql,qr);
		if(mid<ql)return query(rc,mid+1,r,ql,qr);
		return query(lc,l,mid,ql,qr)+query(rc,mid+1,r,ql,qr);
	}
	#undef lc
	#undef rc
}
struct ques{
	int x,yl,yr,id,op;
}q[N<<2];
inline bool comp(const ques &a,const ques &b){//op!顺序问题 
	if(a.x!=b.x)return a.x>b.x;
	return a.op<b.op;
}
int n,tot,ans[N],tmp[N];
multiset<int>s;
int main(){
	freopen("cow.in","r",stdin);
	freopen("cow.out","w",stdout);
	n=read();
	for(int i=1,a1,b1,a2,b2;i<=n;i++){
		a1=read();b1=read();a2=read();b2=read();
		q[++tot]=(ques){a2,b1,b2,i,1};
		q[++tot]=(ques){a1-1,b1,b2,-i,2};
	} 
	n=read();
	for(int i=1,x,y;i<=n;i++){
		x=read();y=read();
		q[++tot]=(ques){x,y,0,0,3};
	}
	n=read();
	for(int i=1,x,y;i<=n;i++){
		x=read();y=read();
		q[++tot]=(ques){x,y,i,0,4};
	}
	sort(q+1,q+tot+1,comp);
	s.insert(mx);
	for(int i=1,nxt;i<=tot;i++){
		if(q[i].id){
			if(q[i].id>0){
				nxt=(*s.upper_bound(q[i].yr));
				tmp[q[i].id]=seg::query(1,0,mx,q[i].yr+1,nxt);
				seg::modify(1,0,mx,q[i].yl-1,seg::query(1,0,mx,q[i].yl,nxt));
				seg::cover(1,0,mx,q[i].yl,q[i].yr);
				s.insert(q[i].yl-1);
				s.insert(q[i].yr);
			}
			else{
				seg::modify(1,0,mx,q[i].yl-1,-tmp[-q[i].id]);
				seg::cover(1,0,mx,q[i].yl,q[i].yr);
				s.erase(s.find(q[i].yl-1));
				s.erase(s.find(q[i].yr));
			}
		}
		else if(!q[i].yr){
			seg::modify(1,0,mx,q[i].yl,1);
		}
		else{
			nxt=(*s.lower_bound(q[i].yl));
			ans[q[i].yr]=seg::query(1,0,mx,q[i].yl,nxt);
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
	return (0-0);
}
```

---

## 作者：樱雪喵 (赞：5)

题解看不懂，所以试图不差分直接大力维护，过了。

从右往左，对 $y$ 坐标扫描线。设现在处理到第 $j$ 列，那么 $tr_i$ 就表示点 $(i,j)$ 出发的答案（这里就是题里问的答案，不是差分数组）。

假设我们现在扫描线向左移动了一列，按如下顺序依次处理这一列上的东西对答案的影响：

- 矩形的右边界
- 矩形的左边界
- 花
- 统计这一列的答案

### Part 1. 矩形右边界
![](https://cdn.luogu.com.cn/upload/image_hosting/xeg98gyi.png)  
假设我们处理完了蓝色的列，现在要处理的是绿色的列。
![](https://cdn.luogu.com.cn/upload/image_hosting/l3m5909d.png)

那么可以发现，矩形的右边界 $[6,9]$ 影响了标记为黄色的这一段区间。因为新加的列上的花都还没有被考虑，其余位置的 $tr_i$ 不改变。而黄色的部分被竖线挡住，这部分答案必然是 $0$。
把它们区间清零即可。

### Part 2. 矩形左边界
![](https://cdn.luogu.com.cn/upload/image_hosting/4jkr05cm.png)

假设我们正在处理第 $6$ 列，考虑 $[6,9]$ 这段区间的线消失对答案的影响。那么标记为黄色的部分应该舍弃原来的答案，它们现在唯一的走法是先走到橙色点再找答案，因此把黄色这段区间推平为橙色位置的值。

再考虑上面的紫色部分（其实这里应当延伸到上面的第一个障碍，这里没有就延伸到顶了）。  
它们相比原来有一个新的选择，就是走到橙色那里获得橙色部分的答案。不过这样是有重复的，因为蓝色部分它们原来就能走到。整个蓝色部分的答案存在深蓝色点上，所以在紫色部分区间加上橙色点去掉深蓝色点的答案。

### Part 3. 花

![](https://cdn.luogu.com.cn/upload/image_hosting/dq6yonlj.png)

花是好处理的，一个花对它上面不越过障碍的位置都有 $1$ 的贡献，区间加即可。

### Part 4. 查询
存的本身就是答案，直接单点查就好了。

综上，我们需要一个支持区间推平、区间加、单点查询的数据结构，可以使用线段树维护。向上的第一个障碍使用 `std::set` 维护。

gen 放在讨论区，调了一晚上发现是因为没排序 /cf

```cpp
#define int long long
#define pii pair<int,int>
const int N=1e6+5;
int n,m,t,mx=1e6+1;
int ans[N];
struct segtree
{
    #define ls (now<<1)
    #define rs (now<<1|1)
    #define mid (l+r>>1)
    int tr[N<<2],add[N<<2],tag[N<<2];
    il void pushup(int now) {tr[now]=tr[ls]+tr[rs];}
    il void pushtag(int tg,int ad,int now,int l,int r)
    {
        if(tg!=-1) tr[now]=(r-l+1)*tg,add[now]=0;
        if(ad) tr[now]+=(r-l+1)*ad;
    }
    il void pushdown(int now,int l,int r)
    {
        pushtag(tag[now],add[now],ls,l,mid),pushtag(tag[now],add[now],rs,mid+1,r);
        if(tag[now]!=-1) tag[ls]=tag[rs]=tag[now];
        add[ls]+=add[now],add[rs]+=add[now];
        tag[now]=-1,add[now]=0;
    }
    void build(int now,int l,int r)
    {
        tag[now]=-1;
        if(l==r) {tr[now]=0;return;}
        build(ls,l,mid),build(rs,mid+1,r);
        pushup(now);
    }
    void tp(int now,int l,int r,int ml,int mr,int k)
    {
        if(ml>mr) return;
        if(l==ml&&r==mr) {add[now]=0,tag[now]=k,tr[now]=(r-l+1)*k;return;}
        pushdown(now,l,r);
        if(mr<=mid) tp(ls,l,mid,ml,mr,k);
        else if(ml>mid) tp(rs,mid+1,r,ml,mr,k);
        else tp(ls,l,mid,ml,mid,k),tp(rs,mid+1,r,mid+1,mr,k);
        pushup(now);
    }
    void Add(int now,int l,int r,int ml,int mr,int k)
    {
        if(ml>mr) return;
        if(l==ml&&r==mr) {add[now]+=k,tr[now]+=(r-l+1)*k;return;}
        pushdown(now,l,r);
        if(mr<=mid) Add(ls,l,mid,ml,mr,k);
        else if(ml>mid) Add(rs,mid+1,r,ml,mr,k);
        else Add(ls,l,mid,ml,mid,k),Add(rs,mid+1,r,mid+1,mr,k);
        pushup(now);
    }
    int query(int now,int l,int r,int x)
    {
        if(l==r) return tr[now];
        pushdown(now,l,r);
        if(x<=mid) return query(ls,l,mid,x);
        else return query(rs,mid+1,r,x);
    }
}seg;
struct node
{
    //type 1:rseg 2:lseg 3:flower 4:cow
    int tp,l,r,x,to;
};
vector<node> q[N];
map<pii,int> mp;
il bool cmp(node x,node y) {return x.tp<y.tp;}
set<int> s;
il int lst(int x) 
{
    auto nw=s.lower_bound(x);
    if(nw==s.begin()) return 0;
    else return *prev(nw);
}
signed main()
{
    t=read(); seg.build(1,1,mx);
    for(int i=1;i<=t;i++) 
    {
        int a=read(),b=read(),c=read(),d=read();
        q[b-1].push_back({2,a-1,c,0,d}),q[d].push_back({1,a-1,c,0,0});
    }
    m=read();
    for(int i=1,x,y;i<=m;i++) x=read(),y=read(),q[y].push_back({3,0,0,x,0});
    n=read();
    for(int i=1,x,y;i<=n;i++) x=read(),y=read(),q[y].push_back({4,0,0,x,i});
    for(int j=mx;j;j--)
    {
        sort(q[j].begin(),q[j].end(),cmp);
        for(auto nw:q[j])
        {
            if(nw.tp==1) 
            {
                mp[pii(nw.r+1,j+1)]=seg.query(1,1,mx,nw.r+1);
                seg.tp(1,1,mx,nw.l+1,nw.r,0),s.insert(nw.l),s.insert(nw.r);
            }
            if(nw.tp==2)
            {
                int k1=mp[pii(nw.r+1,nw.to+1)],k2=seg.query(1,1,mx,nw.r+1);
                seg.tp(1,1,mx,nw.l+1,nw.r,k2);
                seg.Add(1,1,mx,lst(nw.l)+1,nw.l,k2-k1);
                s.erase(nw.l),s.erase(nw.r);
            }
            if(nw.tp==3) seg.Add(1,1,mx,lst(nw.x)+1,nw.x,1);
            if(nw.tp==4) ans[nw.to]=seg.query(1,1,mx,nw.x);
        }
    }
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：ezoixx118 (赞：3)

[更好的阅读体验](https://blog.csdn.net/ezoixx118/article/details/95370146)  
# 题意

一个$10^6$行$10^6$列的网格图，上面有一些牛、花和一些矩形围栏，围栏在格子的边界上，牛和花在格子里，牛只能向下或向右走，不能穿过围栏和地图边界，求每头牛它能到达的花的数量。（栅栏不会相交）
# 题解
###### 暴力
首先，可以想出一个很显然的dp，设$dp_{i,j}$表示方格$(i,j)$能到达的花数。要分类讨论，前三种情况很简单，再次不赘述，特别地，有一种情况不能忽略，如下图：（红色范围为栏杆，蓝色为当前格）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190710194651399.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V6b2l4eDExOA==,size_16,color_FFFFFF,t_70)  
如果$dp_{i,j}=dp_{i+1,j}+dp_{i,j+1}$，会发现黑色部分重复计算，需要减去围栏左下角的$dp$值。  
  
时间复杂度$O(n^2)$，需要优化

###### 优化
我们发现除了有围栏遮挡的情况外，当前状态的更新都用到$dp_{i+1,j}$和$dp_{i,j+1}$，可以考虑**差分**：
我们可以按$y$从大往小**扫描线**，维护数组$f_i$，表示第y列中（注意题目中的y是横坐标）$dp_{i,y}-dp_{i+1,y}$的值。可以画个图帮助理解：  
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190710201842812.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V6b2l4eDExOA==,size_16,color_FFFFFF,t_70)  
如上图$f_1$统计范围是蓝色部分，$f_2$也是它对应的横条，$f_3$统计围栏内，而$f_4$则统计黄色部分，一个“7”形。  
  这样，要统计某一头牛$(x,y)$能到达的花，只需找出第一个挡住它的围栏横坐标（R），答案就是$\sum_{x\leq i\leq R}f_i$  
    
   现在问题是当扫描完一条线，$y$值减一时，如何维护$f_i$？同样要分类讨论。
   1.遇到花，直接在对应位置把$f_i$加一即可
   2.遇到牛，更新答案
   3.遇到栏杆的开始：设栏杆纵坐标为$y$，横坐标范围为$l$到$r$。首先需要把$f_{l-1}$加上旧的$\sum_{l\leq i\leq r}f_i$（即上图黄色图形的下边三格），然后把$f_l$至$f_r$设为0（因为出不去），再把$l$，$r$标记为围栏（更新答案要用）
   4.遇到围栏的结束：设栏杆纵坐标为$y$，横坐标范围为$l$到$r$。需要把$f_{l-1}$减去重复部分（像dp第4种情况一样，即上图黄色图形的下边两格与$f_1,f_2$重复，重复部分需要在情况3记录），把$f_l$至$f_r$设为0（因为进不去围栏），再把$l$，$r$删除围栏标记  
    
 综上所述，我们要对$f_i$进行单点修改，区间复制，区间求和，建立标记和查询后一个标记。可以用**线段树**维护。
 （水平有限，表达可能不清，请结合代码）
 # 代码
 为了过审核我把快读快写删了QaQ
 ```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1000005
#define INF 2005
using namespace std;
 
struct ST{
    int sum,set,fen;
}t[inf*4];
 
void ST_pushdown(int u){
    if (t[u].set!=-1){
        t[u*2+1].set=t[u*2].set=0;
        t[u*2+1].sum=t[u*2].sum=0;
        t[u].set=-1;
    }
    return;
}
 
void ST_pushup(int u){
    t[u].sum=t[u*2].sum+t[u*2+1].sum;
    t[u].fen=(t[u*2].fen|t[u*2+1].fen);
    return;
}
 
void ST_build(int u,int l,int r,int N){
    t[u].set=-1;
    if (l==r){
        if (l==N){
            t[u].fen=1;
        }
        return;
    }
    int mid=(l+r)/2;
    ST_build(u*2,l,mid,N);
    ST_build(u*2+1,mid+1,r,N);
    ST_pushup(u);
    return;
}
 
void ST_add(int u,int l,int r,int k,int v){
    if (l==r){
        t[u].sum+=v;
        return;
    }
    ST_pushdown(u);
    int mid=(l+r)/2;
    if (k<=mid){
        ST_add(u*2,l,mid,k,v);
    }
    else{
        ST_add(u*2+1,mid+1,r,k,v);
    }
    ST_pushup(u);
    return;
}
 
void ST_set0(int u,int l,int r,int L,int R){
    if (L<=l && r<=R){
        t[u].set=0;
        t[u].sum=0;
        return;
    }
    ST_pushdown(u);
    int mid=(l+r)/2;
    if (L<=mid){
        ST_set0(u*2,l,mid,L,R);
    }
    if (R>mid){
        ST_set0(u*2+1,mid+1,r,L,R);
    }
    ST_pushup(u);
    return;
}
 
void ST_setfen(int u,int l,int r,int k){
    if (l==r){
        t[u].fen^=1;
        return;
    }
    int mid=(l+r)/2;
    ST_pushdown(u);
    if (k<=mid){
        ST_setfen(u*2,l,mid,k);
    }
    else{
        ST_setfen(u*2+1,mid+1,r,k);
    }
    ST_pushup(u);
    return;
}
 
int ST_nxtfen(int u,int l,int r,int k){
    if (k<=l){
        if (!t[u].fen){
            return 0;
        }
        while (l!=r){
            int mid=(l+r)/2;
            if (t[u*2].fen){
                u=u*2,r=mid;
            }
            else{
                u=u*2+1,l=mid+1;
            }
        }
        return l;
    }
    ST_pushdown(u);
    int mid=(l+r)/2;
    if (k<=mid){
        int ans=ST_nxtfen(u*2,l,mid,k);
        return ans?ans:ST_nxtfen(u*2+1,mid+1,r,k);
    }
    return ST_nxtfen(u*2+1,mid+1,r,k);
}
 
int ST_query(int u,int l,int r,int L,int R){
    if (L<=l && r<=R){
        return t[u].sum;
    }
    ST_pushdown(u);
    int mid=(l+r)/2,ans=0;
    if (L<=mid){
        ans+=ST_query(u*2,l,mid,L,R);
    }
    if (R>mid){
        ans+=ST_query(u*2+1,mid+1,r,L,R);
    }
    return ans;
}
 
struct line{
    int l,r,y;
    int id,p;
    line(){}
    line(int x1,int x2,int yy,int ii,int pp){
        l=x1,r=x2,y=yy,id=ii,p=pp;
    }
}L[inf];
 
bool operator<(line _1,line _2){
    if (_1.y==_2.y){
        return _1.l<_2.l;
    }
    return _1.y>_2.y;
}
 
struct point{
    int x,y;
    int id;
}C[inf],F[inf];
 
bool operator<(point _1,point _2){
    return _1.y>_2.y;
}
 
int lcnt,ccnt,fcnt,N;
int ans[inf],s[inf];
 
void addline(int id){
    if (L[id].p==0){
        int nxt=ST_nxtfen(1,1,N,L[id].r);
        s[L[id].id]=ST_query(1,1,N,L[id].r+1,nxt);
        int sum=ST_query(1,1,N,L[id].l,L[id].r);
        ST_set0(1,1,N,L[id].l,L[id].r);
        if (L[id].l!=1){
            ST_add(1,1,N,L[id].l-1,sum+s[L[id].id]);
            ST_setfen(1,1,N,L[id].l-1);
        }
        ST_setfen(1,1,N,L[id].r);
    }
    else{
        ST_set0(1,1,N,L[id].l,L[id].r);
        if (L[id].l!=1){
            ST_add(1,1,N,L[id].l-1,-s[L[id].id]);
            ST_setfen(1,1,N,L[id].l-1);
        }
        ST_setfen(1,1,N,L[id].r);
    }
    return;
}
 
int main(){
    int cnt,x1,x2,y1,y2;
    rd(cnt)
    for (int i=1;i<=cnt;i++){
        rd(x1) rd(y1) rd(x2) rd(y2)
        L[i*2]=line(x1,x2,y2,i,0);
        L[i*2-1]=line(x1,x2,y1-1,i,1);
        N=max(N,x2);
    }
    lcnt=cnt*2;
    rd(fcnt)
    for (int i=1;i<=fcnt;i++){
        rd(F[i].x) rd(F[i].y)
        N=max(N,F[i].x);
    }
    rd(ccnt)
    for (int i=1;i<=ccnt;i++){
        rd(C[i].x) rd(C[i].y) 
        N=max(N,C[i].x);
        C[i].id=i;
    }
    sort(L+1,L+lcnt+1);
    sort(C+1,C+ccnt+1);
    sort(F+1,F+fcnt+1);
    N=inf-4;
    ST_build(1,1,N,N);
    int li=1,ci=1,fi=1;
    for (int i=N;i>=1;i--){
        for (;L[li].y==i;li++){
            addline(li);
        }
        for (;F[fi].y==i;fi++){
            ST_add(1,1,N,F[fi].x,1);
        }
        for (;C[ci].y==i;ci++){
            int nxt=ST_nxtfen(1,1,N,C[ci].x);
            ans[C[ci].id]=ST_query(1,1,N,C[ci].x,nxt);
        }
    }
    for (int i=1;i<=ccnt;i++){
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}
 ```



---

## 作者：happybob (赞：0)

二维问题，考虑套路扫描线。

比较好的方向是右到左，现在考虑加入一列，如何更改答案。

发现需要支持 $4$ 种类型的加入，但是询问的牛直接询问就好，所以只需要考虑加入右边界，删去左边界，和加入花三种操作。

细想一下发现删去左边界肯定是在加入右边界之后，否则右边界不容易更新。同时发现花的更新很容易进行。维护上下边界的 `set` 之后直接等价于区间加。

于是顺序是先加右边界，删除左边界，最后加入花。

考虑加入右边界，直接做区间覆盖成 $0$ 即可。因为新的花还没加入，目前全都是 $0$。

删除左边界比较困难。事实上可以发现这是左边界，所以在这一段中的位置出发都只能往下走，所以 $[l,r]$ 的答案都应覆盖成 $r+1$ 的答案。但是 $l$ 到上面那个矩形边的一段也可能新增贡献。由于矩形不交，贡献应该是 $r+1$ 答案减去在这个矩形右下角那个位置的答案。这个位置固定，可以直接在之前的扫描线时求出。

所以我们只需要维护区间加区间覆盖单点查询。使用线段树维护即可。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

#define x1 rewrwetg
#define y1 elwkgbdfg

using ll = long long;

const int N = 1e6 + 5;

int f, x1[N], y1[N], x2[N], y2[N];
int n, m;

struct Node
{
	int l, r, id;
	Node() = default;
	Node(int l, int r, int id) : l(l), r(r), id(id) {}
};

vector<int> flower[N];
vector<Node> rt[N], lt[N];
vector<pair<int, int>> cow[N];

int ans[N];

class SegmentTree
{
public:
	struct Node
	{
		int l, r, tag;
		int coltag;
		ll sum;
	}tr[N << 2];
	void pushtag(int u, int v)
	{
		tr[u].tag += v, tr[u].sum += 1ll * v * (tr[u].r - tr[u].l + 1);
	}
	void pushtag2(int u, int c)
	{
		tr[u].tag = 0, tr[u].coltag = c, tr[u].sum = 1ll * c * (tr[u].r - tr[u].l + 1);
	}
	void pushdown(int u)
	{
		if (tr[u].coltag != -1)
		{
			pushtag2(u << 1, tr[u].coltag);
			pushtag2(u << 1 | 1, tr[u].coltag);
			tr[u].coltag = -1;
		}
		if (tr[u].tag)
		{
			pushtag(u << 1, tr[u].tag);
			pushtag(u << 1 | 1, tr[u].tag);
			tr[u].tag = 0;
		}
	}
	void pushup(int u)
	{
		tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0, -1, 0ll };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update_col(int u, int l, int r, int x)
	{
		if (l > r) return;
		if (tr[u].l >= l and tr[u].r <= r)
		{
			pushtag2(u, x);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update_col(u << 1, l, r, x);
		if (r > mid) update_col(u << 1 | 1, l, r, x);
		pushup(u);
	}
	void update_add(int u, int l, int r, int x)
	{
		if (l > r) return;
		if (tr[u].l >= l and tr[u].r <= r)
		{
			pushtag(u, x);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update_add(u << 1, l, r, x);
		if (r > mid) update_add(u << 1 | 1, l, r, x);
		pushup(u);
	}
	ll query(int u, int l, int r)
	{
		if (l > r) return 0ll;
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].sum;
		pushdown(u);
		ll res = 0ll;
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res += query(u << 1 | 1, l, r);
		return res;
	}
}sgt;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> f;
	for (int i = 1; i <= f; i++)
	{
		cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
		rt[y2[i]].emplace_back(Node(x1[i], x2[i], i));
		lt[y1[i] - 1].emplace_back(Node(x1[i], x2[i], i));
	}
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		flower[y].emplace_back(x);
	}
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		cow[y].emplace_back(make_pair(x, i));
	}
	for (int i = 1; i <= f; i++)
	{
		cow[y2[i] + 1].emplace_back(make_pair(x2[i] + 1, i + n));
	}
	sgt.build(1, 1, (int)1e6 + 5);
	multiset<int> st, nls, nr;
	for (int i = (int)1e6; i >= 1; i--)
	{
		for (auto& [l, r, id] : rt[i])
		{
			sgt.update_col(1, l, r, 0);
			//cout << "subcol: " << l << " " << r << " " << 0 << "\n";
			st.insert(r);
			st.insert(l);
			nls.insert(l), nr.insert(r);
		}
		sort(lt[i].begin(), lt[i].end(), [&](const auto& x, const auto& y) {return x.l > y.l; });
		for (auto& [l, r, id] : lt[i])
		{
			int val = (sgt.query(1, r + 1, r + 1));
			sgt.update_col(1, l, r, val);
			st.erase(st.find(r));
			nr.erase(nr.find(r));
			st.erase(st.find(l));
			nls.erase(nls.find(l));
			auto it = st.upper_bound(l);
			int nl;
			if (st.size() && it != st.begin())
			{
				--it;
				if (nr.count(*it)) nl = *it + 1;
				else nl = *it;
			}
			else nl = 1;
			val = (sgt.query(1, r + 1, r + 1));
			if (l - 1 && sgt.query(1, l - 1, l - 1))
			{
				val = val - ans[id + n];
			}
			sgt.update_add(1, nl, l - 1, val);
		}
		for (auto& x : flower[i])
		{
			auto it = st.upper_bound(x);
			if (nr.count(x))
			{
				auto it = st.lower_bound(x);
				--it;
				if (nls.count(x))
				{
					sgt.update_add(1, x, x, 1);
					//cout << "add: " << i << " " << x << " " << x << " " << "1\n";
				}
				else
				{
					if (nr.count(*it))
					{
						sgt.update_add(1, *it + 1, x, 1);
						//cout << "add: " << i << " " << x << " " << x << " " << "1\n";
					}
					else
					{
						sgt.update_add(1, *it, x, 1);
						//cout << "add: " << i << " " << *it << " " << x << " " << "1\n";
					}
				}
			}
			else if (st.size() && it != st.begin())
			{
				--it;
				bool tag = nr.count(*it);
				sgt.update_add(1, *it + tag, x, 1);
				//cout << "add: " << i << " " << *it + tag << " " << x << " " << "1\n";
			}
			else
			{
				sgt.update_add(1, 1, x, 1);
				//cout << "add: " << i << " " << 1 << " " << x << " " << "1\n";
			}
		}
		for (auto& [x, id] : cow[i])
		{
			ans[id] = (sgt.query(1, x, x));
		}
		//if (sgt.query(1, 5, 5)) cout << "res: " << i << " " << sgt.query(1, 5, 5) << "\n";
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：shenxinge (赞：0)

> solution of P4348

wind_seeker : 这黑题随随便便秒切。一眼扫描线 , 从右往左扫 。


考虑二维动态规划 , 

$$dp_{i,j}=dp_{i+1,j}+dp_{i,j+1}$$

如果我们沿用 wind_seeker 的做法 ， 扫描线从右往左扫 , 容易发现在同一列中会被分割成若干条线段 , 我们可以用一个有序数据结构比如 set 维护当前处理的点的下边界 ，考虑到有些列是无法进行继承的 , 用线段树维护列上的差分 ， 然后进行一段区间求和就可以还原出 $dp_{i,j}$ 。

然后遇到篱笆的时候就需要区间清空，具体如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/giryq7hq.png)

现在扫到的是整体偏绿的一行 ， 左边是篱笆的范围 ， 由于篱笆内部和篱笆外部是彼此分离的 ， 我们需要在右上角的那个点加上整条绿色的和还原出原本的数组， 而在篱笆范围 $(y1,y2)$ 内清 0 进行计算 。

还有一点需要注意的是 ， 由于我们在差分的时候还原了数组 ， 所以遇到另一边的时候我们需要将还原的贡献减去 ， 因为到了粉色那一行蓝色同属一个范围之内 ， 但由于绿色部分是只有右侧深绿色的点才能到达的 , 所以我们还原的时候只需减去浅绿色的后缀和大小。 具体操作就是在遍历到绿色那一行的时候记录浅绿色的代价 , 到篱笆的另一侧减掉即可。

---

