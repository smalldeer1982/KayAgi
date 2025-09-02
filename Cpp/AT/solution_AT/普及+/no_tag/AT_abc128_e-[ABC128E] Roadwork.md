# [ABC128E] Roadwork

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc128/tasks/abc128_e

東西に無限に続く $ 1 $ 本の大通りがあり、数直線とみなすことができます。

この大通り上で $ N $ 回道路工事が行われます。 $ i $ 番目の道路工事は時刻 $ S_i\ -\ 0.5 $ から時刻 $ T_i\ -\ 0.5 $ まで座標 $ X_i $ を通行止めにします。

$ Q $ 人の人が座標 $ 0 $ に立っています。 $ i $ 番目の人は時刻 $ D_i $ に座標 $ 0 $ を出発し、速度 $ 1 $ で正の方向へ歩き続けます。 歩いている途中で通行止めとなっている地点に到達した場合には、そこで歩くのをやめます。

$ Q $ 人それぞれが進む距離を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ S_i\ <\ T_i\ \leq\ 10^9 $
- $ 1\ \leq\ X_i\ \leq\ 10^9 $
- $ 0\ \leq\ D_1\ <\ D_2\ <\ ...\ <\ D_Q\ \leq\ 10^9 $
- $ i\ \neq\ j $ かつ $ X_i\ =\ X_j $ の時、区間 $ [S_i,\ T_i) $ と 区間 $ [S_j,\ T_j) $ は重ならない

### Sample Explanation 1

$ 1 $ 番目の人は時刻 $ 0 $ に座標 $ 0 $ を出発し、時刻 $ 2 $ に座標 $ 2 $ に到着した時点で、$ 1 $ 番目の道路工事による通行止めによって歩くのをやめます。 $ 2 $ 番目の人は時刻 $ 1 $ に座標 $ 0 $ を出発し、時刻 $ 3 $ に座標 $ 2 $ に到着します。この時、$ 1 $ 番目の道路工事は既に終了していますが、$ 4 $ 番目の道路工事が始まっているため、同様に座標 $ 2 $ で歩くのをやめます。 $ 4 $ 番目および $ 6 $ 番目の人は、歩いている最中に通行止めに出くわさないため、無限に歩き続けます。

## 样例 #1

### 输入

```
4 6
1 3 2
7 13 10
18 20 13
3 4 2
0
1
2
3
5
8```

### 输出

```
2
2
10
-1
13
-1```

# 题解

## 作者：chen_hx (赞：7)

### 本大蒟蒻的第一篇题解,写得不好请多多见谅
这个题目是一道经典的区间覆盖类问题  。

但是每个事件并不是覆盖在同一个维度,那么这样子怎么办呢?

显然可以把不同的维度转换到同一个维度中,就是把每一个项目投射到开始的时间  。

假如一个项目从 $s$ 开始,在 $t$ 结束,位置是 $x$ ,那么从 $s-x$ 到 $t-x$ 这段时间的人走到这就必然停下来  。

但是怎么知道是哪些人从 $s-x$ 到 $t-x$ 开始呢?  
排个序然后每次二分一遍就行了。

建一棵线段树来记录每个人(排过序)的终止情况,每次二分找到在 $s-x$ 出发的是哪个人和在 $t-x$ 出发的是哪个人,然后区间修改即可  。

建议将每个事件按 $x$ 从大到小排序,这样修改时就可以直接修改而不用再取min(众所周知线段树区间取min是个很痛苦的事)  。

代码如下,嫌丑误喷,阿里嘎多

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return x*f;
}
struct num{
	int val,id;
}input[N];
struct block{
	int s,t,x;
}sch[N];
int a[N],n,q,A,b,c,rev[N];
int find(int k){
	int l=1,r=q+1,mid,ans;
	while(l<=r){
		mid=l+r>>1;
		if(k<a[mid])ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int cmp1(block A,block B){
	return A.x>B.x;
}
int cmp2(num A,num B){
	return A.val<B.val;
}

//线段树 & lazytag 
int val[N*4],ls[N*4],rs[N*4],root,siz;
void build(int &p,int l,int r){
	if(!p)p=++siz;
	val[p]=-1;
	if(l==r)return;
	int mid=l+r>>1;
	build(ls[p],l,mid);
	build(rs[p],mid+1,r);
}
void pushdown(int p){
	if(!val[p])return;
	val[ls[p]]=val[rs[p]]=val[p];
	val[p]=0;
}
void change(int p,int l,int r,int L,int R,int d){
	if(R<l||r<L)return;
	if(L<=l&&r<=R){
		val[p]=d;
		return;
	}
	pushdown(p);
	int mid=l+r>>1;
	change(ls[p],l,mid,L,R,d);
	change(rs[p],mid+1,r,L,R,d);
}
int query(int p,int l,int r,int d){
	if(d<l||r<d)return -100;
	if(val[p])return val[p];
	else{
		int mid=l+r>>1;
		return max(query(ls[p],l,mid,d),query(rs[p],mid+1,r,d));
	}
}

int ans[N];
void solve(){
	a[q+1]=1e9;
	build(root,1,q);
	for(int i=1;i<=n;i++){
		int l=find(sch[i].s-1-sch[i].x);
		int r=find(sch[i].t-1-sch[i].x);
		change(root,1,q,l,r-1,sch[i].x);
	}
	for(int i=1;i<=q;i++){
		ans[rev[i]]=query(root,1,q,i);
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}
void pre(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		A=read(),b=read(),c=read();
		sch[i]=block{A,b,c};
	}
	sort(sch+1,sch+n+1,cmp1);
	for(int i=1;i<=q;i++){
		A=read();
		input[i]=num{A,i};
	}
	sort(input+1,input+q+1,cmp2);
	for(int i=1;i<=q;i++){
		rev[i]=input[i].id;
		a[i]=input[i].val;
	}
}
signed main(){
//	freopen("e.in","r",stdin);
//	freopen("e.out","w",stdout);
	pre();
	solve();
}
```


---

## 作者：FFTotoro (赞：5)

这里提供一种比较奇怪的数据结构做法。

本题需要利用**优先队列**与**线段树**。

先考虑如果一个点的施工永远不会结束应该怎么做：假设出发时间为 $D$，显然可以二分出最近的点 $X_j$，这个点满足所有离它近的点 $X_i$ 都在人走过去之后才开始施工（条件为 $D+X_i<S_i$，为方便处理将它变为 $D<S_i-X_i$），并且人会卡在 $X_j$ 上（即人到达 $X_j$ 的时候它已经开始施工了）。这个可以用线段树维护 $S_i-X_i$ 的区间最小值。

考虑如果施工时间会结束应该怎么做。因为询问的出发时间是递增的，所以如果目前问到的 $D$ 存在一段施工结束时间 $T_i\le X$ 的，可以删除这一段施工并且以后都用不到，如果该点的下一段施工满足 $T_i>X$ 就更新线段树，否则继续删除施工时间继续往下找（即同一个点可能存在不止一段 $T_i\le X$ 的施工），最终如果这个点都没有施工了就将其值设为 $\inf$。删除哪些段可以用优先队列维护。

线段树可以借助 AtCoder Library，有自带二分函数 `max_right<>()`。

放代码（GNU C++ 17, with AtCoder Library）：

```cpp
// AtCoder Segtree + Priority Queue
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpi;
int op(int a,int b){return min(a,b);}
int e(){return INT_MAX;}
int d; bool f(int x){return x>d;}
int main(){
  ios::sync_with_stdio(false);
  int n,m,c=-1; cin>>n>>m;
  vector<tuple<int,int,int> > a(n);
  for(auto &[x,l,r]:a)cin>>l>>r>>x,l=max(l-x,0),r=max(r-x,0);
  sort(a.begin(),a.end());
  map<int,int> w;
  map<int,queue<pii> > v;
  vector<int> p;
  for(auto [x,l,r]:a){
    if(!w.count(x))w[x]=++c,p.emplace_back(x);
    v[c].emplace(l,r);
  }
  p.emplace_back(-1);
  priority_queue<pii,vector<pii>,greater<> > q;
  atcoder::segtree<int,op,e> t(c+1);
  for(auto [x,l,r]:a)
    if(int y=w[x];t.get(y)==INT_MAX)t.set(y,l),q.emplace(r,y);
  // 以上为预处理
  while(m--&&cin>>d){
    while(!q.empty()&&q.top().first<=d){
      int x=q.top().second; q.pop();
      while(!v[x].empty()&&v[x].front().second<=d)v[x].pop();
      if(v[x].empty())t.set(x,INT_MAX);
      else t.set(x,v[x].front().first),q.emplace(v[x].front().second,x);
    } // 删除工作段
    cout<<p[t.max_right<f>(0)]<<'\n'; // 二分找答案
  }
  return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：5)

什么年代了还在写线段树，学 ds 学的。

不管第一个遇到的条件，先考虑一个在 $[l,r)$ 时间位于 $x$ 的路障会被什么时刻开始的人创到。

当且仅当时刻 $t\in[l-x,r-x)$。

不难想到将询问的权设为 $d_i$，加入路障权设为 $s_i-x_i$，撤去路障权设为 $t_i-x_i$，然后按权递增排序，维护一个集合，能够插入/删除元素，求全体最小值，`multiset` 即可。

又快又好写。

复杂度 $\mathcal{O(n\log n)}$。

```cpp
const int N=2e5+3;
int n,m,b[N];
sd vector<pii>a;
sd multiset<int>S;
il void Solve()
{
  rd(n,m);
  for(int i=1,x,l,r;i<=n;++i) rd(l,r,x),a.push_back({l-x,~i}),a.push_back({r-x,i}),b[i]=x;
  for(int x;m--;) rd(x),a.push_back({x,n+1});
  sd stable_sort(begin(a),end(a));
  for(pii x:a) x.y>n?wrt(S.size()?*begin(S):-1,'\n'):x.y<0?S.insert(b[~x.y]),7:(S.erase(S.find(b[x.y])),7);
  return;
}
```

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc128/submissions/44367084)。

---

## 作者：hyxgg (赞：3)

[题目](https://www.luogu.com.cn/problem/AT_abc128_e)

### 思路
先考虑哪些时间开始的人会遇到第 $i$ 个工程：

设开始时间为 $k$，有：
$$k+X_i\in [S_i,T_i) $$
易推出
$$k\in [S_i-X_i,T_i-X_i)$$

于是先将所有的 $S_i$，$T_i$ 减去 $X_i$。

于是问题转化为线段覆盖问题。发现数据范围有点大，可以离散化后再求解。

当然如果你和我一样不想做离散化，这里也提供另一种思路：

先给人按出发时间排序，再对于每个工程二分求出出发时间最早和最晚的会碰到它的人，然后做线段覆盖（其实也是另一种离散化）。

### 代码
```
#include<iostream>
#include<cstdio>
#include<map>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
struct gongcheng
{
    ll s,t,k;
}g[200005];
ll n,m,d[200005],q[200005],z[200005],b[200005];
bool cmp(gongcheng x,gongcheng y){
    return x.k<y.k;
}
int main(){
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=n;i++){
        scanf("%lld%lld%lld",&g[i].s,&g[i].t,&g[i].k);
        g[i].s-=g[i].k,g[i].t-=g[i].k;
    }
    for(ll i=1;i<=m;i++){
        scanf("%lld",&d[i]);
    }
    sort(g+1,g+1+n,cmp);
    for(ll i=1;i<=n;i++){
        ll ms=g[i].s,mt=g[i].t;
        ll l=1,r=m,sw=0,tw=0;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(d[mid]<ms){
                l=mid+1;
            }
            else{
                sw=mid;
                r=mid-1;
            }
        }
        l=1,r=m;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(d[mid]>=mt){
                r=mid-1;
            }
            else{
                tw=mid;
                l=mid+1;
            }
        }
        for(ll j=sw;j<=tw;j++){
            if(b[j]){
                j=z[b[j]];
            }
            else{
                b[j]=i;
            }
        }
        z[i]=tw;
    }
    for(ll i=1;i<=m;i++){
        ll ans=g[b[i]].k;
        if(ans==0){
            ans=-1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：MSqwq (赞：3)

看了一下题解，貌似没有双堆的做法，来补一下。  


------------
首先这题单点询问区间转化成区间覆盖询问点是关键啊，相信大家不难可以想出，然后就是如何处理区间覆盖的问题。  
我们不难想到可以把这个题看成三个操作，添加路障，过了一段时间删除路障，和询问。可以发现这些操作都是在一个时间点发生的，有很显然的先后顺序，那么我们可以用两个堆完成，一个是 ins 添加堆，用来记录哪些点在维修，显然是小根堆，因为我们询问点的时候是就先原则，坐标越小就会被越先挡住，其次是 del 删除堆，用来看一定时间过后，就该删除 ins 里的了，为了保持一直，肯定也是小根堆。    
知道了这个之后其实就做完了，每次询问去删除 ins 和 del 堆顶相同的元素，那肯定就是被删除了的，再看 ins 堆还有没有元素就行，如果有，就是答案，如果没有，就是 $-1$。 
值得一提的还有，如果同一时间点有多个操作需要发生的话，优先级是添加大于询问大于删除，因为添加了才能询问，同样的询问了之后才可以删除。  
更细节的，本题可以将左闭右开转化成左闭右闭的形式，就是人到每个施工地的时间可以由 $[s-x,t-x)$ 变为 $[s-x,t-1-x]$ 更好处理，当然前面都想出来了，这一步也是显而易见了。  
代码：  
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=2e5+10;
struct qwq{
	int op,x,y;
}a[N*3];
bool cmp(qwq x,qwq y)
{
	if(x.x==y.x)return x.op<y.op;
	return x.x<y.x;
}
int d[N],ans[N];
int tot;
priority_queue<int,vector<int>,greater<int> >ins,del;
int main()
{
	int n=read(),q=read();
	for(int i=1;i<=n;i++)
	{
		int st=read(),en=read(),x=read();
		a[++tot]=(qwq){1,st-x,x},a[++tot]=(qwq){3,en-1-x,x};
	}
	for(int i=1;i<=q;i++)d[i]=read(),a[++tot]=(qwq){2,d[i],i};
	
	sort(a+1,a+1+tot,cmp);
	for(int i=1;i<=tot;i++)
	{
		if(a[i].op==1)ins.push(a[i].y);
		if(a[i].op==3)del.push(a[i].y);
		if(a[i].op==2)
		{
			while(!ins.empty()&&!del.empty()&&ins.top()==del.top())ins.pop(),del.pop();
			if(ins.empty())ans[a[i].y]=-1;
			else ans[a[i].y]=ins.top();
		}
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<endl;
	return 0;
}
```


---

## 作者：Mu_leaf (赞：2)

### [题意]

有一条无限长的街道,上面有 $N$ 个将要进行的工程，第 $i$ 个工程在第 $X_i$ 坐标处从 $S_i$ 到 $T_i$。

且有 $Q$ 个人，将在 $D_i$ 秒时从 $0$ 的地方开始向街道的右方向移动每秒移动 $1$ ，如果当前位置在施工，则立即停下。问一个人会走多少米，如果永远也不会停下则输出 $-1$。

### [思路]

可以将问题转化为**区间覆盖问题**和**单点查询问题**。

一共会有 3 种操作：

1.插入一个区间。

2.删除一个区间。

3.查询一个区间。

想到这我是想用双堆去做。

一个小根堆存已经插入的区间，一个小根堆存已经被删除的区间。

当两个堆的堆顶相同时，就代表这个区间已经删除了可以去掉了。

此时的开始时间就会转化为 $s-x$ 和 $t-x$，那么从 $s-x$ 到 $t-x$ 这段时间走到这的就必然停下。
### [细节处理]：

1.建议将施工结束的时间从小到大排序，如果结束时间相同就比较施工开始时间。



 AC 代码：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int mx=2e5+5;
#define ll long long
ll ans[mx],d,s,t,x;
struct cz{ll zl,wz,id;}E[mx*5];
priority_queue<int,vector<int>,greater<int>> add,del;
int n,q,cnt;
bool cmp(cz a,cz b){return (a.wz<b.wz)||(a.wz==b.wz&&a.zl<b.zl);}
void ad(ll a,ll b,ll c){
	cnt++;
	E[cnt].zl=a;
	E[cnt].wz=b;
	E[cnt].id=c;
	return;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&s,&t,&x);
		ad(1,s-x,x);
		ad(2,t-x,x);
	}	
	for(int i=1;i<=q;i++){
		scanf("%lld",&d);
		ad(3,d,i); 
	}
	sort(E+1,E+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		if(E[i].zl==1){
			add.push(E[i].id);
		}else if(E[i].zl==2){
			del.push(E[i].id);
		}else{
			while(!add.empty()&&!del.empty()&&add.top()==del.top()){
				add.pop();
				del.pop();
			}
			if(add.empty()) ans[E[i].id]=-1;
			else ans[E[i].id]=add.top();
		}
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

杜绝抄袭！！!

---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题其实很简单，我们知道求得是最近的停下来的位置，每次人每秒移动一个单位长度。

首先我们知道每支施工队施工的起始时间与终止时间，及施工的地点，那么我们就可以处理出在一个人从某个时间段中出现会被这支施工队拦住的时间段（初始时间以及终止时间分别减去出现地点）。

那么我们就可以给出现时间排序，扫描线把出现时间比当前人早或相等的扔进平衡树中，把终止位置大于等于的从平衡树中扔出去，而停下来的位置就是还在平衡树中的施工队出现位置的最小值（如果没有施工队还在平衡树中，记得判不合法）。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define ls tr[p].ch[0]
#define rs tr[p].ch[1]
#define int long long
using namespace std;
struct f{int rnd,ch[2],sum,mi,id;}tr[200005];
void wei(int p){
	tr[p].mi=min(tr[p].id,tr[ls].mi);
	tr[p].mi=min(tr[p].mi,tr[rs].mi);
}
void split(int p,int &x,int &y,int k){
	if(!p){x=y=0;return;}
	if(tr[p].sum<=k){x=p;split(rs,rs,y,k);wei(x);}
	else y=p,split(ls,x,ls,k),wei(y);
}
void merge(int &p,int x,int y){
	if(!x||!y){p=x+y;return;}
	if(tr[x].rnd<=tr[y].rnd) p=x,merge(rs,rs,y);
	else p=y,merge(ls,x,ls);
	wei(p);
}int cnt;
int add(int id,int sum){
	int p=++cnt;
	tr[p].mi=tr[p].id=id,tr[p].sum=sum;tr[p].rnd=rand();
	return p;
}
struct ff{int s,t,id;}a[200005];
bool cmp(ff x,ff y){return x.s<y.s;}
signed main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i].s>>a[i].t>>a[i].id;
		a[i].s=a[i].s-a[i].id;
		a[i].t=a[i].t-a[i].id;
	}
	sort(a+1,a+1+n,cmp);
	int l=1,root=0;tr[0].mi=1e18;
	for(int i=1;i<=q;i++){
		int x;cin>>x;
		while(l<=n&&a[l].s<=x){
			int x,y;split(root,x,y,a[l].t);
			merge(x,x,add(a[l].id,a[l].t));
			merge(root,x,y);
			l++;
		}
		int xx,y;
		split(root,xx,y,x);
		root=y;
		if(tr[root].mi==1e18) cout<<-1<<'\n';
		else cout<<tr[root].mi<<'\n'; 
	}
	return 0;
}
```

---

## 作者：Endt (赞：1)

# Roadwork-题解

### 题面

一共有 $n$ 个工程，第 $i$ 个工程在 $X_i$ 位置施工，施工时间是 $[S_i,T_i)$。

一共 $m$ 个人，均从位置 $0$ 出发。

第 $i$ 个人在 $D_i$ 时刻出发，每秒走 $1$ 个单位长度。如果当前位置正在施工，则停下。

你需要求出每个人停下的位置，如果可以一直走下去，输出 $-1$。

### 分析

> 第 $i$ 个工程在 $X_i$ 位置施工，施工时间是 $[S_i,T_i)$。

由于人的速度为 $1$ 个单位长度每秒，那么实际上这一个工程就对 $[S_i-X_i​, Ti-X_i​)$ 时刻出发的人有影响。按照工程起始时间排序，$ans_i$ 表示在时刻 $i$ 出发时的 $ans$。枚举 $i$ ，如果此时有新的会对人产生影响的工程，扔进按照坐标大小排序的 `set` 里面，工程结束时删掉。$ans_i$ 则为 `set` 中的最小值。

根据题目，需要对时间离散化，可以用 `set` 实现。

为方便找到工程何时结束，可以把结束时间放进 `set` 里面。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
class G{
    public:
        int S,T,x;
}a[200005];
int d[200005];
bool cmp(G a,G b){
    return a.S<b.S;
}
set<int> lisanhua;map<int,int> mp;//离散化
set<int> minx;//最近的施工位置
set<pair<int,int>> endt;//结束时间及对应x

int ans[600100];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d%d%d",&a[i].S,&a[i].T,&a[i].x);
        a[i].S-=a[i].x,a[i].T-=a[i].x;
        lisanhua.insert(a[i].S);lisanhua.insert(a[i].T);
    }
    for(int i=1;i<=m;++i){
        scanf("%d",&d[i]);
        lisanhua.insert(d[i]);
    }
    {int j=0;for(int i:lisanhua)mp[i]=j++;}
    for(int i=1;i<=n;++i){
        a[i].S=mp[a[i].S],a[i].T=mp[a[i].T];
    }
    for(int i=1;i<=m;++i){
        d[i]=mp[d[i]];
    }
    sort(a+1,a+1+n,cmp);//按起始时间排序
    
    int ii=1;
    for(int i=0;i<=600000;++i){
        while(!endt.empty()&&i==endt.begin()->first){//工程结束
            minx.erase(endt.begin()->second); 
            endt.erase({endt.begin()->first,endt.begin()->second});
        }
        while(i==a[ii].S){//工程开始
            minx.insert(a[ii].x);
            endt.insert({a[ii].T,a[ii].x});
            ++ii;
        }
        if(minx.empty())ans[i]=-1;//没有阻拦
        else ans[i]=*minx.begin();//有阻拦
    }
    for(int i=1;i<=m;++i){
        printf("%d\n",ans[d[i]]);
    }
    return 0;
}
```




---

## 作者：cosf (赞：0)

转化一下题意，其实就能发现，限制 $(x, s, t)$ 相当于让出发时间在 $[s - x, t - x - 1]$ 的人卡住。

因此，题目相当于区间覆盖加上单点查询。使用动态开点就非常好写。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 200005
#define MAXM 1000000009

struct Tree
{
    int l, r;
    int x;
} s[MAXN << 7];
int idx = 0, rt;

struct Item
{
    int s, t, x;
} val[MAXN];

void pushdown(int p)
{
    if (s[p].x)
    {
        if (!s[p].l)
        {
            s[p].l = ++idx;
        }
        if (!s[p].r)
        {
            s[p].r = ++idx;
        }
        s[s[p].l].x = s[s[p].r].x = s[p].x;
        s[p].x = 0;
    }
}

void add(int &p, int l, int r, int ql, int qr, int v)
{
    if (!p)
    {
        p = ++idx;
    }
    if (ql <= l && r <= qr)
    {
        s[p].x = v;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (mid >= ql)
    {
        add(s[p].l, l, mid, ql, qr, v);
    }
    if (mid < qr)
    {
        add(s[p].r, mid + 1, r, ql, qr, v);
    }
}

int query(int p, int l, int r, int q)
{
    if (!p)
    {
        return -1;
    }
    if (s[p].x)
    {
        return s[p].x;
    }
    int mid = (l + r) >> 1;
    if (mid >= q)
    {
        return query(s[p].l, l, mid, q);
    }
    else
    {
        return query(s[p].r, mid + 1, r, q);
    }
}

int n, m;

signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i].s >> val[i].t >> val[i].x;
        val[i].s -= val[i].x;
        val[i].t -= val[i].x + 1;
    }
    sort(val + 1, val + n + 1, [](Item a, Item b)
         { return a.x > b.x; });
    for (int i = 1; i <= n; i++)
    {
        if (val[i].t < 0)
        {
            continue;
        }
        add(rt, 0, MAXM, val[i].s, val[i].t, val[i].x);
    }
    while (m--)
    {
        int d;
        cin >> d;
        cout << query(rt, 0, MAXM, d) << endl;
    }
    return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

对于第 $i$ 个工程 $(S_i,T_i,X_i)$，它只对出发时间在 $[S_i -X_i,T_i-X_i)$ 区间内的人会起到阻塞作用，所以对于每一个人，我们只需要找到能对他起到阻塞作用且施工位置最前的工程位置就行了。

对于每一个 $D_i$，与他有关的工程是那些已经开始但还没结束的，为了挑选出所有这些工程的位置，可以构造一个三元组  $event(t_i, x_i, d_i)$，定义如下：

1. $ d_i \in \{0, 1\} $ 。
2. 当 $ d_i = 0 $ 时，$ t_i = S_i - X_i $ 
3. 当 $ d_i = 1 $ 时，$ t_i =T_i - X_i $。
4. $ x_i = X_i $。

然后专门用一个集合存放与当前 $ D_i $ 有关的 $ X_i $，把三元组按照 $ t_i $ 排个序，然后顺序遍历所有 $ t_i \leq D_i $ 的事件，如果 $ d_i = 0 $，就把 $ x_i $ 加入集合，否则就从集合中删去。

然后集合中最小的位置就是当前人所停留的位置。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define INIT() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define Rep(i,n) for (int i = 0; i < (n); ++i)
#define For(i,s,t) for (int i = (s); i <= (t); ++i)
#define rFor(i,t,s) for (int i = (t); i >= (s); --i)
#define ForLL(i, s, t) for (LL i = LL(s); i <= LL(t); ++i)
#define rForLL(i, t, s) for (LL i = LL(t); i >= LL(s); --i)
#define foreach(i,c) for (__typeof(c.begin()) i = c.begin(); i != c.end(); ++i)
#define rforeach(i,c) for (__typeof(c.rbegin()) i = c.rbegin(); i != c.rend(); ++i)

#define pr(x) cout << #x << " = " << x << "  "
#define prln(x) cout << #x << " = " << x << endl

#define LOWBIT(x) ((x)&(-x))

#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())

#define ms0(a) memset(a,0,sizeof(a))
#define msI(a) memset(a,inf,sizeof(a))
#define msM(a) memset(a,-1,sizeof(a))

#define MP make_pair
#define PB push_back
#define ft first
#define sd second

template<typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &p) {
    in >> p.first >> p.second;
    return in;
}

template<typename T>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v)
        in >> x;
    return in;
}

template<typename T1, typename T2>
ostream &operator<<(ostream &out, const std::pair<T1, T2> &p) {
    out << "[" << p.first << ", " << p.second << "]" << "\n";
    return out;
}

inline int gc(){
    static const int BUF = 1e7;
    static char buf[BUF], *bg = buf + BUF, *ed = bg;

    if(bg == ed) fread(bg = buf, 1, BUF, stdin);
    return *bg++;
}

inline int ri(){
    int x = 0, f = 1, c = gc();
    for(; c<48||c>57; f = c=='-'?-1:f, c=gc());
    for(; c>47&&c<58; x = x*10 + c - 48, c=gc());
    return x*f;
}

typedef long long LL;
typedef unsigned long long uLL;
typedef pair< double, double > PDD;
typedef pair< int, int > PII;
typedef pair< string, int > PSI;
typedef set< int > SI;
typedef vector< int > VI;
typedef vector< PII > VPII;
typedef map< int, int > MII;
typedef multimap< int, int > MMII;
typedef unordered_map< int, int > uMII;
typedef pair< LL, LL > PLL;
typedef vector< LL > VL;
typedef vector< VL > VVL;
typedef priority_queue< int > PQIMax;
typedef priority_queue< int, VI, greater< int > > PQIMin;
const double EPS = 1e-10;
const LL inf = 0x7fffffff;
const LL infLL = 0x7fffffffffffffffLL;
const LL mod = 1e9 + 7;
const int maxN = 2e5 + 7;
const LL ONE = 1;
const LL evenBits = 0xaaaaaaaaaaaaaaaa;
const LL oddBits = 0x5555555555555555;

struct Tuple{
    int T, X, D;

    inline bool operator< (const Tuple &x) const{
        return T < x.T;
    }
};

int N, Q;
Tuple event[maxN << 1];
int len;
multiset< int > msi;

int main(){
    //INIT();
    N = ri();
    Q = ri();
    For(i, 1, N) {
        int S, T, X;
        S = ri();
        T = ri();
        X = ri();

        event[++len].T = S - X;
        event[len].X = X;
        event[len].D = 1;

        event[++len].T = T - X;
        event[len].X = X;
        event[len].D = 0;
    }
    sort(event + 1, event + len + 1);

    int k = 1, D;
    For(i, 1, Q) {
        D = ri();
        //********************************************************************
        while(k <= len) {
            if(event[k].T <= D) {
                if(event[k].D) msi.insert(event[k].X);
                else msi.erase(msi.find(event[k].X));
                ++k;
            }
            else break;
        }

        /*
        血的教训，一开始我写的不是while循环，而是for循环，貌似是没问题
        但是提交一直超时，原因是某些案例使得else分支一直没有执行到，于是时间复杂度就激增了
        贴上错误代码，引以为戒
        For(j, k, len) {
            if(event[j].T <= D) {
                if(event[j].D) msi.insert(event[j].X);
                else msi.erase(msi.find(event[j].X));
                ++k;
            }
            else {
                k = j;
                break;
            }
        }
        */

        //********************************************************************

        int ans = -1;
        if(msi.size()) ans = *msi.begin();
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Down_syndrome (赞：0)

## 题意
省略
## 思路
分析一下题意，可以发现对于从 $t$ 开始出发的人到达第 $i$ 个施工地点的时间是 $t+X_i$，若此时在施工，则 $T_i\le t+X_i<S_i$，整理得 $T_i-X_i\le t<S_i-X_i$。也就是说，第 $i$ 个施工地只对从 $T_i-X_i$ 到 $S_i-X_i-1$ 出发的人有影响。这样对于每个人就查找 $X_i$ 最小的受影响的施工地就行了。我们可以维护一个序列 $ans$，第 $i$ 项表示从 $i$ 时出发的人会停在哪里，并按施工地 $X_i$ 从大到小排序（这样 $X_i$ 小的值会覆盖原来的值，就能保证 $X_i$ 最小），每次把 $t$ 的第 $T_i-X_i$ 到 $S_i-X_i-1$ 项改为 $X_i$，就能够得出答案。明显，暴力去做肯定会超时。看到区间修改单点查询，可以想到线段树（如果您不会线段树，可以[参考一下](https://zhuanlan.zhihu.com/p/106118909)）。看到数据范围 $10^9$ 级别，强开线段树会炸空间，可以想到离散化或动态开点。代码以离散化为例（主要是好写）。
## 一些细节
1. 询问也要离散化。
2. 注意线段树要开 $12$ 倍空间（本身 $4$ 倍空间，左端点和右端点和询问总共 $3$ 倍空间），不知道卡不卡，但是保险。

## Code
```cpp
#include<bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=2e5+5;
int n,m,cnt,ask[N],liser[N*3];//我的一个同学喜欢把离散化叫成liser化，故有此名 
struct node{
	int s,t,x;
}d[N];
struct tree{
	int l,r,tag,dat;
}t[N*12];//注意要开够 
bool cmp(node a,node b){
	return a.x>b.x;
}
void build(int k,int l,int r){
	t[k].l=l;
	t[k].r=r;
	t[k].dat=-1;//把没有值得赋为-1，也就是不会停下来，方便输出答案 
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void add(int k,int v){
	t[k].tag=t[k].dat=v;
}
void push_down(int k){
	if(t[k].tag){
		add(ls,t[k].tag);
		add(rs,t[k].tag);
		t[k].tag=0;
	} 
}//懒标记下传
void modify(int k,int l,int r,int v){
	if(r<liser[t[k].l]||liser[t[k].r]<l) return;//离散化其实可以这么写 
	if(l<=liser[t[k].l]&&liser[t[k].r]<=r){
		add(k,v);
		return;
	}
	push_down(k);
	modify(ls,l,r,v);
	modify(rs,l,r,v);
}//区间修改 
int query(int k,int x){
	if(liser[t[k].r]<x||x<liser[t[k].l]) return -1;
	if(t[k].l==t[k].r) return t[k].dat;
	push_down(k);
	return max(query(ls,x),query(rs,x));//这个max主要是为了方便 
}//单点查询 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&d[i].s,&d[i].t,&d[i].x);
		d[i].s=max(d[i].s-d[i].x,0);//注意加上max(x,0) 
		d[i].t=max(d[i].t-d[i].x-1,0);
		liser[++cnt]=d[i].s;
		liser[++cnt]=d[i].t;
		}
	sort(d+1,d+n+1,cmp);
	for(int i=1;i<=m;i++){
		scanf("%d",&ask[i]);
		liser[++cnt]=ask[i];
	}
	sort(liser+1,liser+cnt+1);
	cnt=unique(liser+1,liser+2*n+m+1)-liser-1;//离散化 
	build(1,1,cnt);
	for(int i=1;i<=n;i++) modify(1,d[i].s,d[i].t,d[i].x);//修改 
	for(int i=1;i<=m;i++) printf("%d\n",query(1,ask[i]));//输出 
	return 0;//优雅结束 
}
```


---

## 作者：ZnPdCo (赞：0)

~~提供一个现有题解里最大空间の题解。~~

发现二维很不好做，考虑转换为一维。

对于在 $[S_i,T_i)$ 施工的工程创到的人一定是从 $[S_i-X_i,T_i-X_i)$ 出发的，对于一个点只需要判断是不是在任何一个区间内即可。

可以用的算法很多，使用线段树。赋值以 $X$ 从大到小，这样最后覆盖的一定是最小的工程（最先创到的工程）。

由于数据很大，考虑区间离散化，这个可看[例题](https://www.luogu.com.cn/problem/UVA10587)。

然后就很水了：

```c++
#include <cstdio>
#include <algorithm>
#define ll long long
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define N 200010
using namespace std;
ll n, m;
ll t[24*N];							// 4倍的线段树，3倍的离散化节点，2倍的修改和查询操作
ll lazy[24*N];
struct node {
	ll l, r, x;
} a[2*N];
ll temp[6*N];						// 记录离散化后的节点
ll cnt;
bool cmp(node x, node y) {
	return x.x > y.x;
}


// 不需要push_up的线段树
void push_down(ll pos) {
	t[ls(pos)] = lazy[pos];
	lazy[ls(pos)] = lazy[pos];
	t[rs(pos)] = lazy[pos];
	lazy[rs(pos)] = lazy[pos];
	lazy[pos] = -1;
}
void build(ll l, ll r, ll pos) {
	lazy[pos] = -1;
	if(l == r) {
		t[pos] = -1;
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, ls(pos));
	build(mid+1, r, rs(pos));
}
void update(ll nl, ll nr, ll l, ll r, ll pos, ll k) {
	if(nl <= l && r <= nr) {
		t[pos] = k;
		lazy[pos] = k;
		return;
	}
	if(lazy[pos] != -1)
		push_down(pos);
	ll mid = (l + r) >> 1;
	if(nl <= mid)
		update(nl, nr, l, mid, ls(pos), k);
	if(mid < nr)
		update(nl, nr, mid+1, r, rs(pos), k);
}
ll query(ll x, ll l, ll r, ll pos) {
	if(l == r) {
		return t[pos];
	}
	if(lazy[pos] != -1)
		push_down(pos);
	ll mid = (l + r) >> 1;
	if(x <= mid)
		return query(x, l, mid, ls(pos));
	if(mid < x)
		return query(x, mid+1, r, rs(pos));
}




int main() {
	scanf("%lld %lld", &n, &m);
	for(ll i = 1; i <= n; i++) {
		ll s, t, x; 
		scanf("%lld %lld %lld", &s, &t, &x);
		a[i] = {l: s-x, r: t-x-1, x:x};
		temp[++cnt] = a[i].l;
		temp[++cnt] = a[i].r;
		temp[++cnt] = a[i].r+1;
	}
	for(ll i = 1; i <= m; i++) {
		ll d;
		scanf("%lld", &d);
		a[n+i] = {l: d, r: d, x:0};
		temp[++cnt] = a[n+i].l;
		temp[++cnt] = a[n+i].r;
		temp[++cnt] = a[n+i].r+1;
	}
	
    // 离散化
	sort(temp+1, temp+1+cnt);
	ll len = unique(temp+1, temp+1+cnt)-temp-1;
	for(ll i = 1; i <= n+m; i++) {
		a[i].l = lower_bound(temp+1, temp+1+len, a[i].l)-temp;
		a[i].r = lower_bound(temp+1, temp+1+len, a[i].r)-temp;
	}
	
	sort(a+1, a+1+n, cmp);
	
    // 然后就很板了
	build(1, len, 1);
	for(ll i = 1; i <= n; i++) {
		update(a[i].l, a[i].r, 1, len, 1, a[i].x);
	}
	
	for(ll i = 1; i <= m; i++) {
		printf("%lld\n", query(a[n+i].l, 1, len, 1));
	}
} 
```

---

