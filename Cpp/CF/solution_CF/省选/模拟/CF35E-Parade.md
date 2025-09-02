# Parade

## 题目描述

No Great Victory anniversary in Berland has ever passed without the war parade. This year is not an exception. That’s why the preparations are on in full strength. Tanks are building a line, artillery mounts are ready to fire, soldiers are marching on the main square... And the air forces general Mr. Generalov is in trouble again. This year a lot of sky-scrapers have been built which makes it difficult for the airplanes to fly above the city. It was decided that the planes should fly strictly from south to north. Moreover, there must be no sky scraper on a plane’s route, otherwise the anniversary will become a tragedy. The Ministry of Building gave the data on $ n $ sky scrapers (the rest of the buildings are rather small and will not be a problem to the planes). When looking at the city from south to north as a geometrical plane, the $ i $ -th building is a rectangle of height $ h_{i} $ . Its westernmost point has the x-coordinate of $ l_{i} $ and the easternmost — of $ r_{i} $ . The terrain of the area is plain so that all the buildings stand on one level. Your task as the Ministry of Defence’s head programmer is to find an enveloping polyline using the data on the sky-scrapers. The polyline’s properties are as follows:

- If you look at the city from south to north as a plane, then any part of any building will be inside or on the boarder of the area that the polyline encloses together with the land surface.
- The polyline starts and ends on the land level, i.e. at the height equal to 0.
- The segments of the polyline are parallel to the coordinate axes, i.e. they can only be vertical or horizontal.
- The polyline’s vertices should have integer coordinates.
- If you look at the city from south to north the polyline (together with the land surface) must enclose the minimum possible area.
- The polyline must have the smallest length among all the polylines, enclosing the minimum possible area with the land.
- The consecutive segments of the polyline must be perpendicular.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF35E/23dca3b6890c3864c0838cb5956c4323cb001fd2.png) Picture to the second sample test (the enveloping polyline is marked on the right).

## 样例 #1

### 输入

```
2
3 0 2
4 1 3
```

### 输出

```
6
0 0
0 3
1 3
1 4
3 4
3 0
```

## 样例 #2

### 输入

```
5
3 -3 0
2 -1 1
4 2 4
2 3 7
3 6 8
```

### 输出

```
14
-3 0
-3 3
0 3
0 2
1 2
1 0
2 0
2 4
4 4
4 2
6 2
6 3
8 3
8 0
```

# 题解

## 作者：EnofTaiPeople (赞：5)

题目如标题所说。

恕我直言，这道题摆明了是用来水的，观察性质可以发现，我们只需要维护每一个位置的高度，高度变化时会多出两个点，直接用线段树区间取最值即可，注意离散化。

这里使用非递归线段树，似乎一发就得到了最优解？

由于是紫题，做之前应该都有必要会线段树操作，直接放 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
namespace fast_io{
    char buf[N+5],*p1,*p2;
    int ot,t,c;
    #define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2)?EOF:*p1++)
    inline int read(){
        int an=0,f=1;while(!isdigit(c=gc))if(c=='-')f=-f;
        do an=an*10+(48^c);while(isdigit(c=gc));return an*f;
    }
    char ob[N+20],stk[20];
    inline void fls(){
        fwrite(ob,1,ot,stdout),ot=0;
    }
    inline void write(ll x,char c='\n'){
        if(x<0)ob[ot++]='-',x=-x;
        while(x>9)stk[++t]=48^(x%10),x/=10;
        for(ob[ot++]=48^x;t;ob[ot++]=stk[t--]);
        ob[ot++]=c;if(ot>N)fls();
    }
}
using fast_io::read;
using fast_io::write;
int mp[N],mt,m,n,tg[N<<1];
struct seg{
    int h,l,r;
    inline bool operator<(const seg &z)
    const{return h<z.h;}
}g[N];
vector<tuple<int,int> >gt;
int main(){
#ifdef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read();int i,l,r;
    for(i=1;i<=n;++i){
        g[i]={read(),read(),read()};
        mp[++mt]=g[i].l,mp[++mt]=g[i].r;
    }
    sort(mp+1,mp+mt+1),sort(g+1,g+n+1);
    mt=unique(mp+1,mp+mt+1)-mp;
    for(m=1;m<=mt;m<<=1);
    for(i=1;i<=n;++i){
        l=lower_bound(mp+1,mp+mt,g[i].l)-mp+m-1;
        r=lower_bound(mp+1,mp+mt,g[i].r)-mp+m;
        while(l^r^1){
            if((l&1)^1)tg[l^1]=g[i].h;
            if(r&1)tg[r^1]=g[i].h;
            l>>=1,r>>=1;
        }
    }for(i=1;i<m;++i){
        l=i<<1,r=l|1;
        if(tg[l]<tg[i])tg[l]=tg[i];
        if(tg[r]<tg[i])tg[r]=tg[i];
    }for(i=1;i<mt;++i){
        l=m+i;
        if(tg[l]!=tg[l-1]){
            gt.emplace_back(mp[i],tg[l-1]);
            gt.emplace_back(mp[i],tg[l]);
        }
    }write(gt.size());
    for(auto at:gt){
        tie(l,r)=at;
        write(l,' '),write(r);
    }fast_io::fls();
    return 0;
}
```
记得开文件！

---

## 作者：Unordered_OIer (赞：2)

# CF35E

若干个矩形，矩形之间可能有交，求轮廓线。

# Solution

古早题目，现在估计有一车人能秒。

破防点解析：因为空间开小导致 WA，调试破防。

首先这些矩形都有一条边在 X 轴上，那么完全可以将其看做一个一维序列，矩形可以看做在这个序列上的区间 $[l_i,r_i]$ 上进行 chkmax。

由于坐标是 $[-10^9,10^9]$，而坐标本身没有太大作用，所以可以直接离散化。考虑线段树，每条线段直接维护这个线段上的**高度 $h$（即这条线段上所有位置的高度都为 $h$）**，因为不难发现一条线段上如果高度不同那么记录这条线段没有什么价值，而且是单点查。所以与一般线段树不同，不需要维护 lazytag，并且由于维护信息特殊性不能 pushup，只能 pushdown。注意输出细节，可以参考代码。

注意题目要求文件 IO。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const ll N=1e5+5;
inline ll read(){
  ll x=0,f=0;char ch=getchar();
  while(ch<'0'||ch>'9')f|=(ch=='-'),ch=getchar();
  while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
  return f?-x:x;
}
ll lsh[N<<1],tot;
ll n,h[N],l[N],r[N];
struct node{
  ll l,r,mx;
}t[N<<4];
void pushup(ll x){
  t[x].mx=max(t[x].mx,max(t[x<<1].mx,t[x<<1|1].mx));
}
void pushdown(ll x){
  t[x<<1].mx=max(t[x<<1].mx,t[x].mx);
  t[x<<1|1].mx=max(t[x<<1|1].mx,t[x].mx);
}
void build(ll x,ll l,ll r){
  t[x]=(node){l,r,0};
  if(l==r)return;
  ll mid=l+r>>1;
  build(x<<1,l,mid);
  build(x<<1|1,mid+1,r);
}
void modify(ll x,ll l,ll r,ll h){
  if(t[x].r<l||t[x].l>r)return;
  if(t[x].l>=l&&t[x].r<=r){
    t[x].mx=max(t[x].mx,h);
    pushdown(x);
    return;
  }
  modify(x<<1,l,r,h);
  modify(x<<1|1,l,r,h);
}
ll query(ll x,ll i){
  pushdown(x);
  if(t[x].l==t[x].r)return t[x].mx;
  if(i<=t[x<<1].r)return query(x<<1,i);
  else return query(x<<1|1,i);
}
vector<pair<ll,ll>> p;
void addp(ll x,ll y){
  if(x==p[p.size()-1].fi&&y==p[p.size()-1].se)return;
  p.emplace_back(mp(x,y));
}
int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout); 
  n=read();
  for(ll i=1;i<=n;i++){
    h[i]=read(),l[i]=read(),r[i]=read();
    lsh[++tot]=l[i];
    lsh[++tot]=r[i];
  }
  sort(lsh+1,lsh+tot+1);
  tot=unique(lsh+1,lsh+tot+1)-lsh-1;
  for(ll i=1;i<=n;i++){
    l[i]=lower_bound(lsh+1,lsh+tot+1,l[i])-lsh;
    r[i]=lower_bound(lsh+1,lsh+tot+1,r[i])-lsh;
  }
//  for(ll i=1;i<=tot;i++)cout<<lsh[i]<<' ';puts("");
  build(1,1,tot);
  for(ll i=1;i<=n;i++)modify(1,l[i],r[i]-1,h[i]);
  ll lst=0,l=1;
  p.emplace_back(mp(1,0));
  for(ll i=1;i<=tot;i++){
    ll cur=query(1,i);
    if(cur!=lst){
      addp(l,lst);
      addp(i,lst);
      addp(i,cur);
      l=i;
      lst=cur;
    }
  }
  cout<<p.size()<<'\n';
  for(ll i=0;i<p.size();i++)cout<<lsh[p[i].fi]<<' '<<p[i].se<<'\n';
  return 0;
}
```

---

## 作者：BqtMtsZDnlpsT (赞：2)

远古场 2100。

$\large\text{Solution}$

考虑一个交接点产生的条件：

1. 首先这个点一定在一条竖向的矩形边上。
2. 两个矩形相交产生两个点。
3. 这两个点一定是同一列交点中纵坐标最大的（否则会被比他大的覆盖掉）。

所以对于每个横坐标维护最大值和次大值，然后扫描线扫过去，就好了？不！。

考虑这样的情况：

![](https://s4.ax1x.com/2022/01/28/7xWLnK.png)

应该选 $A,B$ 吗？不，选 $A,C$。

那怎么办？其实很简单：

考虑对于横坐标的第一个（按输出顺序）点，在一个矩形的右边界或中间；第二个在一个矩形的左边界或中间。

如上图，就是一个在右边界一个在中间。

于是，我们可以开两个线段树维护：

对于当前横坐标：在右边界或中间的点，纵坐标最大值；

对于当前横坐标：在左边界或中间的点，纵坐标最大值；


对于每个横坐标，分别在两个线段树里查询最大值即可（具体维护细节参考代码）。

注意事项：
- 输出顺序（见下图）

![](https://s4.ax1x.com/2022/01/28/7xTMv9.png)

- 空地可以看做高度为 $0$ 的矩形。

- 若一个横坐标上，点在右边界或中间时，纵坐标的最大值 $=$ 点在左边界或中间时，纵坐标的最大值，即

![](https://s4.ax1x.com/2022/01/28/7xT4rn.png)

跳过即可
    
代码：
```cpp
int n,l[100005],r[100005],h[100005],b[200005],L;
struct SGT{//线段树，ans[i] 表示节点 i 对应区间最大值
	int ans[800005];
	#define u (s<<1)
	#define v (s<<1|1)
	void build(int l,int r,int s){
		ans[s]=0;//看成无限宽高度 0 的矩形
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,u);
		build(mid+1,r,v);
	}
	inline void pass(int s,int k){ans[s]=max(ans[s],k);}
	inline void push_down(int s){pass(u,ans[s]),pass(v,ans[s]);}//把一个节点答案下传
	void update(int x,int y,int l,int r,int s,int k){
		if(x<=l&&r<=y){pass(s,k);return;}
		push_down(s);
		int mid=(l+r)>>1;
		if(x<=mid)update(x,y,l,mid,u,k);
		if(y>mid)update(x,y,mid+1,r,v,k);
	}
	int query(int x,int l,int r,int s){//单点查询即可。
		if(l==r)return ans[s];
		push_down(s);
		int mid=(l+r)>>1;
		if(x<=mid)return query(x,l,mid,u);
		return query(x,mid+1,r,v);
	}
	#undef u
	#undef v
}t[2];
vector<pair<int,int>>ans;
signed main(){
	freopen("input.txt","r",stdin);//别忘了！！！CF某些地方的feature
	freopen("output.txt","w",stdout);//别忘了！！！
	n=read();
	for(int i=1;i<=n;i++)h[i]=read(),l[i]=read(),r[i]=read(),b[++L]=l[i],b[++L]=r[i];//b是离散化之后的横坐标数组
	sort(b+1,b+1+L);L=unique(b+1,b+1+L)-b-1;//离散化
	t[0].build(1,L,1);t[1].build(1,L,1);//建树
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(b+1,b+1+L,l[i])-b;
		r[i]=lower_bound(b+1,b+1+L,r[i])-b;
		t[0].update(l[i],r[i]-1,1,L,1,h[i]);//在左边界或中间时
		t[1].update(l[i]+1,r[i],1,L,1,h[i]);//在右边界或中间时
	}
	for(int i=1;i<=L;i++){
		int u=t[0].query(i,1,L,1),v=t[1].query(i,1,L,1);
		if(u==v)continue;//相同就跳过
		ans.push_back({b[i],v});//根据输出格式先输出在右边界或中间的点
		ans.push_back({b[i],u});
	}
	write(ans.size(),'\n');
	for(auto I:ans)write(I.first,' '),write(I.second,'\n');
}

```

---

## 作者：Karry5307 (赞：2)

### 题意

给你 $n$ 个 $x$ 轴上的矩形，求轮廓线的顶点。

$\texttt{Data Range:}1\leq n\leq 10^5$

### 题解

~~憨批 CF 为什么这题要文件输入输出啊，你家中文翻译又没写害的我浪费一次提交~~

第一次写维护轮廓线就勇敢地踩坑了/kk

先讲一下这个题的一个典型错误解法：对所有矩形的左右端点离散化之后按照 $h_i$ 从小到大排序然后做区间覆盖。这个很明显会在样例 $2$ 上 WA 掉，原因是如果某一个矩形的上边界作为轮廓线的一部分的那一段的两边都是比这段要高的，那么这段根本不会被统计到。

好，然后现在讲正解。注意到这样一个结论：轮廓线的高度只有可能在某个矩形的两个端点处更新。于是可以拿个什么东西将这些端点存下来然后从小到大排序扫一遍。对于每一个端点来说，按照扫描线的思想将矩形插入删除，然后查询覆盖到这个点高度最大的矩形就是答案了。

于是现在只需要弄一个支持插入删除查最大值的数据结构，可以写离散化后的线段树二分，我这里是用的 multiset，好写而且跑的也很快。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
typedef pair<ll,ll> pii;
const ll MAXN=2e5+51;
struct Event{
	ll tp,id,h;
	inline bool operator <(const Event &rhs)const
	{
		return id==rhs.id?tp<rhs.tp:id<rhs.id;
	}
};
Event ev[MAXN<<1];
multiset<ll>st;
vector<pii>v;
ll n,totd,lst,cur,id;
ll l[MAXN],r[MAXN],h[MAXN],dsc[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	n=read();
	for(register int i=1;i<=n;i++)
	{
		dsc[++totd]=h[i]=read(),l[i]=read(),r[i]=read();
	}
	sort(dsc+1,dsc+totd+1),totd=unique(dsc+1,dsc+totd+1)-dsc-1;
	for(register int i=1;i<=n;i++)
	{
		h[i]=lower_bound(dsc+1,dsc+totd+1,h[i])-dsc;
		ev[i*2-1]=(Event){0,l[i],h[i]},ev[i*2]=(Event){1,r[i],h[i]};
	}
	sort(ev+1,ev+2*n+1);
	for(register int i=1;i<=2*n;i++)
	{
		lst=st.empty()?0:dsc[*(st.rbegin())];
		ev[i].tp?st.erase(st.find(ev[i].h)):st.insert(ev[i].h);
		while(ev[i+1].id==ev[i].id)
		{
			i++;
			ev[i].tp?st.erase(st.find(ev[i].h)):st.insert(ev[i].h);
		}
		cur=st.empty()?0:dsc[*(st.rbegin())];
		if(lst!=cur)
		{
			v.push_back((pii){ev[i].id,lst}),v.push_back((pii){ev[i].id,cur});
		}
	}
	printf("%d\n",v.size());
	for(auto i:v)
	{
		printf("%d %d\n",i.first,i.second);
	}
}
```

---

## 作者：xh39 (赞：2)

前置算法:离散化**或**动态开点。 //建议先学习其中之一,但这只是代码实现问题,不会也不影响看懂题解的思路部分。

这题直接用类似于扫描线的方法就可以了。没学过扫描线的也可以看此篇题解。如果学了扫描线,基本上就是模板题了。

首先把所有平行于y轴放到一个数组里面**从小到大**排序(放平行于x轴的也可以),如果是矩形的左线段标记为1,右线段标记为-1。为什么这样标记后面再说。

现在想要维护一个矩形构成的轮廓线,那么根据之前排好序的线段逐一进行操作,如果**当前线段有顶点**,此点的x轴还是原来的x轴,y轴肯定是由当前的y值最大的线段的上端顶点的y值和其他的一个点。这个其他的点其实就是上一次的最大值。

如果没有顶点,那么就是该线段不是当前的最大值,或者不是唯一的最大值。比如对于以下2种情况。
```
(v表示枚举到了这条边)
________         __v_____
|   v___|__     |  |  |  |
|   |   |  |    |  |  |  | (图2矩形1是第1,3条边)
|___|___|__|    |__|__|__|
     图1            图2
```
所以在枚举时要特判,如果max值不更新,那么一定是以上2中情况之一。

还有一个问题:怎么求最大值?

这时候我们标记的1和-1就有用了,求最大值很容易想到线段树。然后对于标记为1的,就把线段的上下端点y值之间的值都+1,然后在修改的时候可以记录最大值,这就是结果,不用写查询函数。

细节部分: //讲一下部分我错过的地方。

#1:要开freopen,具体可以看cf原题面的提交部分有提示。

>**inputinput.txt**\
>**outputoutput.txt**

#3:考虑清楚加和查询的顺序,~~顺序不做提示,自己去调吧。~~

#29:考虑线段重复问题,~~也不做提示~~。

代码: //注释比较少,将就着吧。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct xyq{
	int x1,x2,y,sign;
}a[1000005];
struct rule{
	bool operator()(const xyq &s1,const xyq &s2){
		return s1.y<s2.y||s1.y==s2.y&&s1.x2<s2.x2;
	}
};
int x[1000005];
int addsum[1000005],size[1000005];
void change(long long id,long long nowl,long long nowr,long long ql,long long qr,long long add){
	if(nowr<ql||nowl>qr){
		return;
	}
	if(nowl>=ql&&nowr<=qr){
		addsum[id]+=add;
		if(addsum[id]>0){
			size[id]=x[nowr+1]-x[nowl]; //size可以表示最大值。
		}else{
			size[id]=0; //没有线段,即为0。
		}
		if(addsum[id]<=0){
			if(nowl==nowr){
				size[id]=0;
			}else{
				size[id]=size[id<<1]+size[(id<<1)|1];
			}
		}
		return;
	}
	long long mid=nowl+nowr>>1;
	change(id<<1,nowl,mid,ql,qr,add);
	change((id<<1)|1,mid+1,nowr,ql,qr,add);
	if(addsum[id]<=0){
		if(nowl==nowr){
			size[id]=0;
		}else{
			size[id]=size[id<<1]+size[(id<<1)|1];
		}
	}
}
int ansx[1000005],ansy[1000005],tot=0;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout); 
	long long l,r,h,n,i,x1,y1,x2,y2,ykb,sum=0,t1,t2,last=0;
	cin>>n;
	for(i=0;i<n;++i){
		cin>>h>>l>>r;
		x1=0;
		x2=h;
		y1=l;
		y2=r;
		a[i<<1].x1=x1;
		a[(i<<1)|1].x1=x1;
		a[i<<1].x2=x2;
		a[(i<<1)|1].x2=x2;
		a[i<<1].y=y1;
		a[(i<<1)|1].y=y2;
		a[i<<1].sign=1;
		a[(i<<1)|1].sign=-1;
		x[i<<1]=x1;
		x[(i<<1)|1]=x2;
	}
	sort(a,a+(n<<1),rule()); //离散化。
	sort(x,x+(n<<1));
	ykb=(n<<1);
	for(i=0;i<ykb;++i){
		sum+=size[1]*(a[i].y-a[i-1].y);
		t1=lower_bound(x,x+ykb,a[i].x1)-x; //与下面一行都是离散化。
		t2=lower_bound(x,x+ykb,a[i].x2)-x;
		change(1,0,ykb,t1,t2-1,a[i].sign);
		if(size[1]!=last&&a[i].y!=a[i+1].y&&(a[i].y!=a[i-1].y||a[i].sign==a[i-1].sign||a[i].x2!=a[i-1].x2)){
			ansx[tot]=a[i].y;
			ansx[tot+1]=a[i].y;
			ansy[tot]=last;
			ansy[tot+1]=size[1];
			last=size[1];
			tot+=2;
		}
	}
	cout<<tot<<endl;
	for(i=0;i<tot;i++){
		cout<<ansx[i]<<" "<<ansy[i]<<endl;
	}
	return 0;
}
/*
给大家提供这些数据。
(#3简化版)
2
2 -1 1
1 0 1 

(#4)
8
7 4 9
2 9 11
2 11 13
1 -3 -2
4 4 8
4 0 3
6 2 7
3 5 6

(#29)
10
64 23 96
24 85 98
24 -93 -70
58 -30 30
1 39 88
55 54 87
75 41 53
75 97 99
50 -80 -13
48 95 97 
*/
```

---

## 作者：Stone_Xz (赞：1)

## [传送门：CF35E Parade](https://www.luogu.com.cn/problem/CF35E)

## 分析：

首先你需要基本掌握 [【模板】扫描线](https://www.luogu.com.cn/problem/P5490)。

这一题算是比较板了。一个简单的办法是，将题目给的图顺时针旋转 $90$ 度，然后用扫面线从上往下扫，维护当前区间长度，放到原图中就是当前楼的高度。当长度相较于上一条线段有所变化，说明出现了一个这样的东西：

![](https://cdn.luogu.com.cn/upload/image_hosting/ihixxum3.png)

此时我们取出当前线段在原图中的 $x$ 坐标，上面顶点的坐标就为 $(x, \text{之前高度（之前线段的长度）})$，下面顶点的坐标就为 $(x, \text{当前高度（当前线段的长度）})$。

最后一条线段的两个顶点单独输出即可。

### 一个坑点
（~~我被坑了 QWQ~~），有一种情况会使得我们的做法出错：

![](https://cdn.luogu.com.cn/upload/image_hosting/y3fccfs6.png)

这时红色建筑右侧的线段和黑色建筑右侧的线段会被程序视为两条不同的线段。如果我们先更新了黑色建筑右侧的线段，程序会认为轮廓线的高度从黑色建筑的高度变为了红色建筑的高度，就会输出黑色建筑右上角的顶点和红色建筑右上角的顶点，导致错误。

如何解决呢？我是这样做的：若当前的线段的 $x$ 坐标与下一条线段的 $x$ 坐标相同时，不要输出，而是继续更新下一条线段，把当前 $x$ 坐标上的所有线段都处理完再输出就行了。

```cpp
#include<bits/stdc++.h>
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define int long long
using namespace std;

const int N = 1e5 + 5;

int n, tot, X[N << 1];

struct D {
	int x1, x2, y, val;
} a[N << 1];

struct node {
	int len, cnt;
} tree[N << 4];

struct Ans {
	int p1, p2, p3, p4;
};
vector<Ans> ans;

void update(int cur, int lt, int rt) {
	if (tree[cur].cnt)
		tree[cur].len = X[rt + 1] - X[lt];
	else
		tree[cur].len = tree[ls(cur)].len + tree[rs(cur)].len;
}

void change(int cur, int lt, int rt, int x, int y, int val) {
	if (x <= X[lt] && X[rt + 1] <= y) {
		tree[cur].cnt += val;
		update(cur, lt, rt);
		return ;
	}
	int mid = lt + rt >> 1; // mid 是一个区间！！！ 
	if (x < X[mid + 1]) 
		change(ls(cur), lt, mid, x, y, val);
	if (y > X[mid + 1])
		change(rs(cur), mid + 1, rt, x, y, val);
	update(cur, lt, rt);
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout); 
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int h, l, r;
		cin >> h >> l >> r;
		a[i] = {0, h, l, 1};       // 将原图顺时针转 90° 
		a[i + n] = {0, h, r, -1};
		X[i] = h;
		X[i + n] = 0;
	}
	sort(a + 1, a + 1 + n * 2, [&](const D &x, const D &y) {
		return x.y < y.y;
	});
	sort(X + 1, X + 1 + n * 2);
	tot = unique(X + 1, X + 1 + n * 2) - X - 1;
	int las = 0;
	for (int i = 1; i < n * 2; i++) {
		change(1, 1, tot - 1, a[i].x1, a[i].x2, a[i].val);
		if (a[i + 1].y - a[i].y == 0) // 当前线段还没计算完 
			continue;
		if (tree[1].len != las)
			ans.push_back({a[i].y, las, a[i].y, tree[1].len});
		las = tree[1].len;
	}
	cout << ans.size() * 2 + 2 << "\n";
	for (auto ha : ans)
		cout << ha.p1 << " " << ha.p2 << "\n" << ha.p3 << " " << ha.p4 << "\n";
	cout << a[n * 2].y << " " << las << "\n" << a[n * 2].y << " 0";
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

怎么离散化调了八万年啊，汗流浃背了。
### 题意
给定 $n$ 个底边在 $x$ 轴上的矩形，输出按顺序输出矩形并的轮廓线的顶点。
### 分析
扫描线板子。

横向扫描，轮廓线相当于要找出所有最高点变化的位置。离散化以后把矩形拆成 $l_i$ 处 $[1,h_i]$ 加，$r_i+1$ 处 $[1,h_i]$ 减，扫一遍维护一下前一个最高点，当前 $x$ 修改完以后 sgt 上二分查一下新的最高点，如果变了就把产生的顶点加进 `vector` 里最后输出即可。

注意如果直接离散化后差分，连续两个位置变化可能会有查不到的情况，可以把所有横坐标放大两倍并把每个横坐标 $+1$ 也加入离散化数组规避掉这种情况。

时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=4e5+5;
int n;
int h[maxn],l[maxn],r[maxn];
int x[maxn],tx,y[maxn],ty;
vector<int> A[maxn];
vector<pii> ans;
class Segment_Tree{
public:
	int mn[maxn<<2],tag[maxn<<2];
	void pushdown(int o){
		if(!tag[o]) return;
		mn[o*2]+=tag[o],tag[o*2]+=tag[o];
		mn[o*2+1]+=tag[o],tag[o*2+1]+=tag[o];
		tag[o]=0;
	}
	void update(int o,int l,int r,int x,int y,int k){
		if(x<=l&&r<=y){tag[o]+=k,mn[o]+=k;return;}
		int m=(l+r)>>1;pushdown(o);
		if(x<=m) update(o*2,l,m,x,y,k);
		if(y>m) update(o*2+1,m+1,r,x,y,k);
		mn[o]=min(mn[o*2],mn[o*2+1]);
	}
	int binary(int o,int l,int r){
		if(mn[o]) return -1;
		if(l==r) return l;
		int m=(l+r)>>1;pushdown(o);
		if(!mn[o*2]) return binary(o*2,l,m);
		return binary(o*2+1,m+1,r);
	}
}sgt;
signed main(){
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		h[i]=read(),l[i]=read()*2,r[i]=read()*2;
		x[++tx]=l[i],x[++tx]=r[i],y[++ty]=h[i];
		x[++tx]=l[i]+1,x[++tx]=r[i]+1;
	}
	sort(x+1,x+tx+1),tx=unique(x+1,x+tx+1)-x-1;
	sort(y+1,y+ty+1),ty=unique(y+1,y+ty+1)-y-1;
	for(int i=1;i<=n;i++){
		h[i]=lower_bound(y+1,y+ty+1,h[i])-y;
		l[i]=lower_bound(x+1,x+tx+1,l[i])-x;
		r[i]=lower_bound(x+1,x+tx+1,r[i])-x;
		A[l[i]].eb(h[i]),A[r[i]+1].eb(-h[i]);
	}
	ty++;
	for(int i=1,p=0,pt=0;i<=tx+1;i++){
		for(int k:A[i]){
			if(k>0) sgt.update(1,1,ty,1,k,1);
			else sgt.update(1,1,ty,1,-k,-1);
		}
		int t=sgt.binary(1,1,ty)-1;
		if(t==pt) continue;
		if(t<pt) ans.eb(mkpr(i-1,pt)),ans.eb(mkpr(i-1,t));
		else ans.eb(mkpr(i,pt)),ans.eb(mkpr(i,t));
		p=i,pt=t;
	}
	cout<<ans.size()<<'\n';
	for(pii v:ans) cout<<x[v.fir]/2<<' '<<y[v.sec]<<'\n';
	return 0;
}
```

---

## 作者：mango2011 (赞：0)

线段树离散化题。

首先读入了这么一堆矩形，就按照横坐标离散化掉，纵坐标保持不变。

设离散化之后的值域为 $[1,N]$，则显然 $N$ 的上限为 $2n$。我们考虑维护每一个竖条（注意不是竖线），开一棵 $[1,N-1]$ 的线段树（因为只有 $N-1$ 个竖着的条），题中的矩形相当于区间求最大值（因为对于每一个竖着的条，仅需要知道最高的位置）。具体来说，一个 $[l_i,r_i,h_i]$ 的矩形相当于对 $[l_i,r_i-1]$ 中的竖条与 $h_i$ 取 $\max$。求每一个看最高的高度的时候直接单点查询。

于是我们用 $O(n\log n)$ 的时间复杂度维护出了每一个竖条对应的值。接下来考虑如何给出轮廓线：

对于一个竖条（如果是空的直接跳过），如果它的前一个是空位，则显然输出左下角；若后一个是空位，则输出右下角；若与前一个高度不同（或者前面是空的），输出左上角；若与后一个高度不同（或者后面是空的），输出右上角。具体判断的时候请注意顺序。

于是，我们就用 $O(n\log n)$ 的时间复杂度解决了本题。温馨提示：请注意输入输出方式。

---

## 作者：black_trees (赞：0)


建议在我的 [Github blog](https://hylwxqwq.github.io/sol/pro/cf35e/) 上观看，体感更好而且有我踩过的一些坑，如果有问题还可以直接 Gitalk 回复，我能及时看到。

### Statement

给出 $n$ 个底边在 $x$ 轴上的矩形，求外面的轮廓线顶点。

$1\le n \le 10^5$，输入以 $h_i, l_i, r_i$ 的方式给出，表示有一个覆盖 $x \in [l_i, r_i]$ 的高为 $h_i$ 的矩形。

### Analysis 

首先考虑离散化然后直接一个扫描线扫过去（从左到右）。

然后注意到拐点只会在整体最大高度变化的时候出现。

所以我们考虑直接维护一下扫描线上的 $y$ 的最大值，记 $maxy$ 表示线段树上一个节点内被覆盖到的最高 $y$ 值，记 $cnt$ 表示线段树上的节点自身被覆盖的次数，记 $len$ 表示这个节点维护的段内总共被覆盖的长度（记录这个是为了判断是否能更新 $maxy$）

令第 $i$ 段为 $[raw(i), raw(i + 1)]$，令线段树上的 $[l, r]$ 维护第 $l \sim r$ 段。 

修改的时候注意，如果对于扫描线上的 $[l, r]$，操作时应当修改线段树上的 $[val(l), val(r) - 1]$。

因为我们维护的是一个段，维护点是没有意义的。

这里的 Pushup 方式和主流不太一样，在 Change 到一个节点的时候仍然需要做类似 Pushup 的处理，这样可以省去 Pushdown。

具体来说，对于 Pushup，如果当前节点的 $cnt > 0$，那么令 $len = raw(r + 1) - raw(l)$ 并令 $maxy = raw(r + 1)$，否则考虑从儿子节点更新 $len$，如果更新完之后 $len > 0$，再从子树更新 $maxy$。（$raw$ 表示离散化之前的值）

然后在修改的时候也要直接处理更改，方式类似，只不过在处理 $cnt = 0$ 的情况的时候，需要先判是否为叶子节点（不然要额外再开空间），然后再从子树上传信息，这里就算修改了 $cnt$，还是需要考虑用儿子节点信息更新 $maxy$，不然没法处理有多个矩形的更改堆在一起的情况。

那么每次更新完我们只需要询线段树树根的 $maxy$ 即可，并和修改前的 $maxy^{\prime}$ 比较，如果发生改变，就直接把 $(x, maxy), (x, maxy^{\prime})$ 扔进 Vector 就行。

还有一个要注意的地方是，因为这个做法是在每次 Query 之后直接比对并更新答案，所以如果在一个 $x$ 上有多个更改要处理，需要一口气全部处理完再更新，否则会多出来一些实际上不存在的顶点。

最后空间记得开够，不然会 RE on #22.

```cpp
// author : black_trees

#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using i64 = long long;

const int si = 1e5 + 10;

int n, m; 
std::vector<int> v;
int raw[si * 3];
int val(int x) { return lower_bound(v.begin(), v.end(), x) - v.begin(); }

struct Tuple {
	int l, r, k;
	void trans() {
		int vl = val(l), vr = val(r), vk = val(k);
		raw[vl] = l, raw[vr] = r, raw[vk] = k, l = vl, r = vr, k = vk;
	} 
	bool operator < (const Tuple &b) const {
		if(l == b.l) return r > b.r;  // 这里是一开始写的，如果同时做处理的话其实已经没意义了，但是懒得删（
		return l < b.l;
	}
} a[si], b[si << 1]; // 这里是同时存输入的信息和三元组信息的

class SegTree {
	private:
		struct Node {
			int l, r;
			int cnt, len, mxy;
			int Len() { return raw[r + 1] - raw[l]; } 
		} t[si * 11]; // 要开大一点
		inline void pushup(int p) {
			if(t[p].cnt > 0) t[p].len = t[p].Len(), t[p].mxy = raw[t[p].r + 1];
			else {	
				t[p].len = t[p << 1].len + t[p << 1 | 1].len;
				if(t[p].len > 0) t[p].mxy = max(t[p << 1].mxy, t[p << 1 | 1].mxy);
				else t[p].mxy = 0;
			}
		}
	public:
		void build(int p, int l, int r) {
			t[p].l = l, t[p].r = r, t[p].mxy = t[p].len = t[p].cnt = 0;
			if(l == r) return;
			int mid = (l + r) >> 1;
			build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
		}
		void change(int p, int l, int r, int v) {
			int nl = t[p].l, nr = t[p].r;
			if(l <= nl && nr <= r) {
				t[p].cnt += v;
				if(t[p].cnt > 0) t[p].len = t[p].Len(), t[p].mxy = raw[t[p].r + 1];
				else {
					if(nl == nr) t[p].len = 0, t[p].mxy = 0;
					else {
						t[p].len = t[p << 1].len + t[p << 1 | 1].len;
						if(t[p].len > 0) t[p].mxy = max(t[p << 1].mxy, t[p << 1 | 1].mxy);
						else t[p].mxy = 0;
					} // 注意这里也是需要上传的。
				}
				return;
			}
			int mid = (nl + nr) >> 1;
			if(l <= mid) change(p << 1, l, r, v);
			if(r > mid) change(p << 1 | 1, l, r, v);
			pushup(p);
		}
		int Query_global() { return t[1].mxy; } 
} tr; 

std::vector<std::pair<int, int> > ans;

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin.tie(0) -> sync_with_stdio(false);
	cin.exceptions(cin.failbit | cin.badbit);

	cin >> n, v.push_back(0);
	for(int i = 1; i <= n; ++i) {
		cin >> a[i].k >> a[i].l >> a[i].r;
		v.push_back(a[i].k), v.push_back(a[i].l), v.push_back(a[i].r);
	}
	sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
	for(int i = 1; i <= n; ++i) a[i].trans();
	tr.build(1, 1, (int)v.size() + 1);
	
	for(int i = 1; i <= n; ++i) {
		b[i] = (Tuple){a[i].l, a[i].k, 1};
		b[i + n] = (Tuple){a[i].r, a[i].k, -1};
	}
	sort(b + 1, b + 1 + n + n);

	int nowy = 0;	
	for(int i = 1; i <= n + n; ) {
		int x = raw[b[i].l];
		int l, r, v;
		while(true) {
			l = val(0), r = b[i].r, v = b[i].k;
			tr.change(1, l, r - 1, v);
			if(raw[b[i + 1].l] != x) break;
			i++;
		} // 同时处理同一个 x 上的所有更改。
		int nmxy = tr.Query_global();	
		if(nmxy != nowy) {
			ans.push_back(make_pair(x, nowy));
			ans.push_back(make_pair(x, nmxy));
			nowy = nmxy;
		}
		i++;
	}

	cout << ans.size() << endl;
	for(auto [x, y] : ans) cout << x << " " << y << endl;

	return 0;
}
```


---

