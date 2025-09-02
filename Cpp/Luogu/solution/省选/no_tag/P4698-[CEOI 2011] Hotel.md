# [CEOI 2011] Hotel

## 题目描述

你经营着一家旅馆，这家旅馆有 $n$ 个房间，每个房间有维护费用和容量。其中第 $i$ 个房间的维护费用为 $c_i$，容量为 $p_i$ 人。

现在有 $m$ 个订单，每个订单有两个参数：$v_i,d_i$ ，其中 $v_i$ 表示这个订单支付的租金，$d_i$​​ 表示人数。

你现在得要合理选择一些订单，并放弃其他订单，使得每个选择的订单被安排在同一间房间内，且人数不超过这个房间的容量限制。当然，两个不同的订单也不能被安排在同一间房间内。

现在你想要知道，在最多选出 $o$ 个订单时的最大收益。一个方案的收益的定义为，选出的订单的租金和，减去选出的房间的维护费用和。

## 说明/提示

**样例 $1$ 解释**

可以将第一个订单安排至第三个房间，将第二个订单安排至第二个房间。

**数据范围**

对于 $100\%$ 的数据，有 $1\le n,m\le 500\ 000;1\le o\le \min(n,m);1\le c_i,p_i,v_i,d_i\le 10^9$，保证 $\forall 1\le i,j\le n$，若 $p_i\lt p_j$，则 $c_i\le c_j$。

## 样例 #1

### 输入

```
3 2 2
150 2
400 3
100 2
200 1
700 3```

### 输出

```
400```

# 题解

## 作者：liunian (赞：9)

- ~~这道题维度多得我都数不过来了。~~

- 其实这道题，找到单调性就容易突破了。

- 很明显是贪心思想，首先排序，房间按容量从大到小排，订单按租金从大到小排，对于每一个订单，二分查找到刚好满足能住进的房间。

- 但是万一这个房间已经住人了呢?  因此想到用并查集，维护刚好满足能住进且未住人的房间编号。

- 若一个房间被一个订单占用，那么它的父亲就变成了它的编号-1，这样一定是最优的（想想为什么），然后还要注意当它的父亲为0时，不能选用。

- 每一个订单花费为```b[i].x-a[res].x```即订单租金减去选中的房间维修费，用一个数组存起来。

- 将花费排序，从后往前选o（最大订单数）个花费，若o<tot(花费组数)就全加，得到答案。

**代码部分：**

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=5e5+5;
ll ans,icm[maxn];
int n,m,o,sum,pre[maxn],tot;
bool mark[maxn];

struct node {
	int x,y;
} a[maxn],b[maxn];

bool cmp1(node a,node b) {
	if(a.y==b.y)return a.x>b.x;
	return a.y>b.y;
}

bool cmp2(node a,node b) {
	if(a.x==b.x)return a.y>b.y;
	return a.x>b.x;
}

int find(int x) {
	return pre[x]==x?x:pre[x]=find(pre[x]);
}

int main() {
	scanf("%d%d%d",&n,&m,&o);
	for(int i=1; i<=n; i++)scanf("%d%d",&a[i].x,&a[i].y),pre[i]=i;
	for(int i=1; i<=m; i++)scanf("%d%d",&b[i].x,&b[i].y);
	sort(a+1,a+n+1,cmp1);
	sort(b+1,b+m+1,cmp2);
	for(int i=1; i<=m; i++) {
		int l=1,r=n,res=-1;
		while(l<=r) {
			int mid=l+r>>1;
			if(a[mid].y>=b[i].y)l=mid+1,res=mid;
			else r=mid-1;
		}
		if(res==-1)continue;
		if(!mark[res]) {
			if(b[i].x-a[res].x<=0)continue;
			mark[res]=1,pre[res]=res-1,icm[++tot]=b[i].x-a[res].x;
		} else {
			int fa=find(res);
			if(!fa)continue;
			if(b[i].x-a[fa].x<=0)continue;
			mark[fa]=1,pre[fa]=fa-1,icm[++tot]=b[i].x-a[fa].x;
		}
	}
	sort(icm+1,icm+tot+1);
	for(int i=tot; i>=1; i--) {
		if(sum==o)break;
		ans+=icm[i];
		sum++;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：DaydreamWarrior (赞：6)

[才不更好的阅读体验！](https://rainlycoris.github.io/#/post/27)

## 分析

注意到 $p_i<p_j$ 则 $c_i\leq c_j$，存在偏序关系。

一个贪心的想法是，按照订单的 $v$ 从大到小，每次找到大于 $d$ 的最小的 $p$ 住进去。

但是如果房间已经被占用，就住进大于 $d$ 的 $p$ 最小的没有被占用的房间，而不是把占用清除。

考虑这样为什么是对的，设占用房间的为 $i$，要住进去的为 $j$。
- 如果 $i,j$ 都要入住，答案无影响。
- 如果 $i,j$ 只有一个要入住，因为 $v_i>v_j$，所以 $i$ 肯定比 $j$ 更优，$j$ 必定不会被选到（就选选的不是最优的房间也不影响）。

现在问题变成了，找到大于 $d$ 的 $p$ 最小的没有被占用的房间，然后把这个房间删除，`multiset` 可以解决（注意房间可重，`set` 不可重）。

## 代码

```cpp
multiset<pair<int,int>> house;
vector<pair<int,int>> order;
int n,m,o;

int main(){
    n = in(),m = in(),o = in();
    for(int k=1;k<=n;k++){
        int c = in(),p = in();
        house.insert({p,c});
    }
    order.resize(m);
    for(auto &[v,d]:order)
        v = in(),d = in();
    sort(order.begin(),order.end(),[](auto a,auto b){return a.first!=b.first?a.first>b.first:a.second<b.second;});
    vector<int> res;
    for(auto [v,d]:order){
        auto it = house.lower_bound({d,0});
        if(it!=house.end()){
            if(v<=(*it).second)
                continue;
            res.push_back(v-(*it).second);
            house.erase(it);
        }
    }
    sort(res.begin(),res.end(),greater<>());
    long long ans = 0;
    for(int k=0;k<min(o,(int)res.size());k++)
        ans += res[k];
    out(ans);
    return 0;
}
```

## 闲话

$p_i<p_j$ 则 $c_i\leq c_j$ 放在题面更合理吧，放在数据范围有点抽象。

---

## 作者：VioletIsMyLove (赞：5)

此题有一个隐含的道理，当我们按照人数由大到小，人数相同打扫所需费用由大到小时，你会发现此时的房间打扫费用绝对是单调不升的。


那么二分按照所需人数定位到满足条件的最后一个的时候绝对是此时最优的选择，当然这个位置有可能被占用了，占用为 $1$，你会发现你标记一会儿
 $1$ 就联成一片，哎呦喂并查集立马登场，至此完美解决！

```cpp
#include<bits/stdc++.h>
#define LL long long
#define maxn 500005
using namespace std;
int N,M,O,pre[maxn],Mon[maxn];
LL Ans;
struct Room{
    int cos,p;
    bool operator <(const Room B)const{return B.p<p||B.p==p&&B.cos<cos;}
}a[maxn];
struct Custom{
    int val,num;
    bool operator <(const Custom B)const{return B.val<val||B.val==val&&num<B.num;}
}b[maxn];
int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if (ch=='-')f=-f;ch=getchar();} 
    while(isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
    return ret*f;
}
int search(int v){
    int L=1,R=N;
    while (L<=R){
        int mid=(R-L>>1)+L;
        if (a[mid].p>=v) L=mid+1;else R=mid-1;
    }
    return R;
}
int Get(int x){return pre[x]==x?x:pre[x]=Get(pre[x]);}
bool cmp(int x,int y){return y<x;}
int main(){
    N=read(),M=read(),O=read();
    for (int i=1;i<=N;i++) a[i].cos=read(),a[i].p=read(),pre[i]=i;
    for (int i=1;i<=M;i++) b[i].val=read(),b[i].num=read();
    sort(a+1,a+N+1);sort(b+1,b+M+1);
    int tot=0;
    for (int i=1;i<=M;i++){
        int x=Get(search(b[i].num));
        if (x){
            if (b[i].val-a[x].cos<=0) continue;
            Mon[++tot]=b[i].val-a[x].cos;
            pre[x]=Get(x-1);
        }
    }
    sort(Mon+1,Mon+tot+1,cmp);
    for (int i=1;i<=min(O,tot);i++) Ans+=Mon[i];
    printf("%lld\n",Ans);
    return 0;
}
```


---

## 作者：Hoks (赞：2)

## 前言
[题目链接](https://www.luogu.com.cn/problem/P4698)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-p4698)内食用也许不会更佳。

~~模拟赛题+1。~~
## 思路分析
首先这题看到我的第一反应是个背包，但是一看维度数果断放弃。

再仔细一看，求获得钱的最大值，那是不是可以贪心呢？

如果要贪心的话首先按照房间能容纳人数从大到小排序，旅客则按照给的租金从大到小排序。

那旅客应该去哪个房间呢？

这个时候想到了二分，二分出旅客前往的最优的房间。

但是如果有冲突呢？

想到了使用并查集如果有冲突就去选择次优选择尝试。

那一个房间的次优是什么呢？

肯定是上一个，因为下一个一定不满足人数限制（因为这个是最优的就应该是边界）这个房间又已经有人了所以一定是上一个。

然后记录每团旅客住下来的收益，取最优的前面几个就行了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{int x,y;}a[500010],b[500010];
int n,m,q,tot,Ans;
int f[500010],ans[500010],mp[500010];
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
bool cmp1(node x,node y){return x.y>y.y?true:x.y==y.y&&x.x>y.x?true:false;}
bool cmp2(node x,node y){return x.x>y.x?true:x.x==y.x&&x.y>y.y?true:false;}
bool cmp(int x,int y){return x>y;}
int find(int x)
{
	if(f[x]==x) return x;
	else return f[x]=find(f[x]);
}
signed main()
{
	freopen("hot.in","r",stdin);
	freopen("hot.out","w",stdout);
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read(),f[i]=i;
	for(int i=1;i<=m;i++) b[i].x=read(),b[i].y=read();
	sort(a+1,a+1+n,cmp1);sort(b+1,b+1+m,cmp2);
	for(int i=1;i<=m;i++)
	{
		int l=1,r=n,res=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(a[mid].y>=b[i].y) l=mid+1,res=mid;
			else r=mid-1;
		}
		if(res==-1) continue;
		if(!mp[res])
		{
			if(b[i].x-a[res].x<=0) continue;
			mp[res]=1,f[res]=res-1,ans[++tot]=b[i].x-a[res].x;
		}
		else
		{
			int fa=find(res);
			if(b[i].x-a[fa].x<=0||!fa) continue;
			mp[fa]=1,f[fa]=fa-1,ans[++tot]=b[i].x-a[fa].x;
		}
	}
	sort(ans+1,ans+1+tot,cmp);
	for(int i=1;i<=min(tot,q);i++) Ans+=ans[i];
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：china·xyc (赞：2)

### 题面
[题面](https://www.luogu.com.cn/problem/P4698)，懒得改LaTeX了

### 题解
这题是cy大佬讲的，用了一个叫做凸优化的东西。

具体想法是，先想假如没有o的限制，你可以选任意个，那么可以考虑贪心策略，先让容量最小的房间选订单，选它能够接受的报酬最高的订单，维护报酬最高的订单的这个操作可以用优先队列。

那么考虑如果有o的限制，应该怎么做呢？

对于同一组数据，$f(o)$表示不同的$o$时答案的大小，那么我们从样例中可以得知$f(1)-f(0)>f(2)-f(1)$，并且根据常理，选的越多肯定是越优的，那么我们不妨大胆猜测$f(x)-f(x-1)$永远大于$f(x+1)-f(x)$，那么$y=f(x)$的函数图像就一定是上凸的，我们可以用一条直线从上往下平移，使得这条直线与图像的第一个交点的横坐标恰好为o，这样纵坐标就是答案。

至于斜率的意义，可以把每个订单的报酬减去它，然后再进行没有o的限制时的策略，得出此时的o，即横坐标。

所以可以二分斜率，然后使横坐标确定在o，就可以成功得出答案了。

这题想法实在是妙啊。

代码

```cpp
# include <bits/stdc++.h>
using namespace std;
namespace fastio{
	template<typename tn> void read(tn &a){
	    tn x=0,f=1;char c=' ';
	    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	    for(;isdigit(c);c=getchar() ) x=x*10+c-'0';
	    a=x*f;
	}
	template<typename tn> void print(tn a){
	    if(a<0) putchar('-'),a=-a;
	    if(a>9) print(a/10);
	    putchar(a%10+'0');
	}
};
using namespace fastio;
#define int long long
int n,m,o;
const int N=5e5+5;
struct room{
	int c,p;
}r[N];
struct order{
	int v,d;
}h[N];
bool cmp1(room a,room b){
	if(a.p==b.p) return a.c<b.c;
	return a.p<b.p;
}
bool cmp2(order a,order b){
	return a.d<b.d;
}
priority_queue<int> q;
int ans;
int check(int x){
	int ret=0;
	while(!q.empty()) q.pop();
	ans=0;
	for(int i=1,j=1;i<=n;i++){
		while(r[i].p>=h[j].d&&j<=m){
			q.push(h[j].v-x);
			j++;
		}
		if(!q.empty()&&q.top()>r[i].c){			// > or >=
			int now=q.top();
			q.pop();
			ans+=now-r[i].c+x;
			ret++;
			//if(x==60) printf("%d %d %d!!\n",now,now-r[i].c,i);
		}
	}
	return ret;
}
signed main(){
	read(n);
	read(m);
	read(o);
	for(int i=1;i<=n;i++) read(r[i].c),read(r[i].p);
	for(int i=1;i<=m;i++) read(h[i].v),read(h[i].d);
	sort(r+1,r+n+1,cmp1);
	sort(h+1,h+m+1,cmp2);
	//for(int i=1;i<=100;i+=1) printf("%d!!\n",check(i));
	int l=0,r=1e18;
	int tot;
	while(l<=r){
		int mid=(l+r)/2;
		int camp=check(mid);
		if(camp>o) l=mid+1;
		else r=mid-1,tot=mid;
	}
	check(tot);
	printf("%lld\n",ans);
	return 0;
}
/*
3 2 2
150 2
400 3
100 2
200 1
700 3


3 2 1
150 2
400 3
100 2
200 1
700 3
*/
```


---

## 作者：devout (赞：2)

开始拿到题的时候非常的疑惑

注意题目里面说了保证“若$p_i<p_j$，则$c_i\leq c_j$”，也就是说，$c,p$是存在偏序关系的 ~~要不然就没法做了~~

考虑去除掉最多接$o$个订单的限制怎么做

我们可以对房间和人分别排序，扫描每一个房间，在每一个符合条件的订单中找价格最高的，然后配对，简单的贪心就可以了

关于贪心的正确性，因为有题目数据中保证的那个东西，所以对于一个订单来说，最优的应该是房间容量-订单人数最小的那个房间

考虑$F_i(x)$表示选了$i$个订单的答案，那么对于$\Delta x_i=F_i(x)-F_{i-1}(x)$一定是单调不增的，也就是说，$F(x)$是满足凸性质的

所以我们可以考虑$\text{wqs}$二分

让每一个订单的价格都减掉二分值$\Delta$，重新做一遍上面说的贪心，这个时候因为有些订单可能就不赚钱了，所以总接受的订单数量会变小，然后我们就可以确定最后我们要减去的值

最后重新计算一下答案就可以了，注意把$\Delta$加回来

二分$O(n\log n)$，配合堆可以$O(n\log n)$check，复杂度$O(n\log^2n)$

丑陋无比的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=5e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m,o;
ll ans,del;

struct room{
	int c,p;
	bool operator < (const room &cmp)const{
		if(p==cmp.p)return c<cmp.c;
        return p<cmp.p;
	}
}a[N];

struct sakura{
	int v,d;
	bool operator < (const sakura &cmp)const{
		return d<cmp.d;	
	}
}b[N];

bool check(int delta){
	priority_queue<int> q;
	int p=1,res=0;
	Rep(i,1,n){
		while(p<=m&&b[p].d<=a[i].p)q.push(b[p++].v);
		if(!q.empty()){
			int val=q.top();
			if(val-delta>a[i].c)res++,q.pop();	
		}
	}
	return res<=o;
}

signed main()
{
	read(n),read(m),read(o);
	Rep(i,1,n)read(a[i].c),read(a[i].p);
	Rep(i,1,m)read(b[i].v),read(b[i].d);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	int l=0,r=1e9;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))del=mid,r=mid-1;
		else l=mid+1;
	}
	priority_queue<int> q;
	int p=1,res=0;
	Rep(i,1,n){
		while(p<=m&&b[p].d<=a[i].p)q.push(b[p++].v);
		if(!q.empty()){
			int val=q.top();
			if(val-del>a[i].c)ans+=val-del-a[i].c,res++,q.pop();
		}
	}
	printf("%lld\n",ans+1ll*res*del);
	return 0;
}
```


---

## 作者：phil071128 (赞：1)

> $n$ 个房间，每个房间有维护费用 $c$ 和容纳人数 $p$。
>
> 有 $m$ 个订单，每个订单有价值 $v$ 和人数 $d$。你最多选择 $k$ 个订单，最大化收益：价值减去维护费用。
>
> 保证若 $p_i<p_j$，则有 $c_i\le c_j$。

考虑先对两个二元组序列分别按照 $p,d$ 排序。

但是订单有最多的限制，而且注意到房间是有不包含的性质的，因此我们考虑枚举房间。

如果我们能确定最终 $k$ 个订单的匹配具体是如何，那么问题就迎刃而解。

考虑一种贪心方案：每个房间去匹配能塞的下的，价值最大的订单。每匹配成功就将订单删去，防止后面再选。

可以证明，最终方案一定是这样选后，前 $k$ 大的边（对 $0$ 取 $\max$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vsb2gwc6.png)

黑色的边是我们按照贪心方案取得的边，紫色的边是贪心取的的前 $k=3$ 条权值最大的边。

如果存在一个最终方案，不是这三条边，形如左边两种红色边是等价于紫色边，形如右侧这种红色边，一定不优于一条黑色边，而黑色边不优于紫色边。

可以直接双指针 + 优先队列维护，代码非常短。


```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=5e5+5;
pii a[N],b[N];
signed main(){
	//fil();
	int n=read(),m=read(),o=read();
	for(int i=1,c,p;i<=n;i++) c=read(),p=read(),a[i]=pii(p,c);
	for(int i=1,v,d;i<=m;i++) v=read(),d=read(),b[i]=pii(d,v);
	sort(a+1,a+1+n);sort(b+1,b+1+m);
	priority_queue<int>q1,q2;
	int j=1;
	for(int i=1;i<=n;i++) {
		while(j<=m&&b[j].fi<=a[i].fi) {
			q2.push(b[j].se);j++;
		}
		if(!q2.empty()) {
			q1.push(-a[i].se+q2.top()),q2.pop();
		}
	}
	int ans=0;
	for(int i=1;i<=o;i++) ans+=max(0ll,q1.top()),q1.pop();
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：违规用户名1058825 (赞：1)

初看题面，毫无思绪。

观看数据范围：$\forall 1\le i,j\le n$，若 $p_i<p_j$，则 $c_i \le c_j$。

说明什么？

~~这个问题很现实。~~ **房间容量越大，维护费用越高。**

我们可以把每个房间以容量为第一关键字，排一趟序（房间容量高的放在前面）。容量相同比较维护价格，大的整前面。这样排序可以保证房价按照维护价格从大到小下来。  
**注意不能直接以维护费用排序！**  
（问题：万一费用相同但人数不同呢？）

每个订单找到第 $i$ 个房间，如果他可行，他前面的房间都可以。  
**换句话来说就是每个订单的最优解就是满足条件的房间中的最后一个。**     
可以用二分实现。  
但是不一定这个最优解的房间一定没被选过，可以用链表或并查集跳转。

每个订单也要以人数从大到小（相同时按金额从小到大）排一趟。
这样的话求出来是最优解。

讲完了！

AC code

```cpp
#include<bits/stdc++.h>
#define int long long //十年 OI 一场空，不开 long long 见祖宗
using namespace std;
const int maxn=500005;
int n,m,k,cnt,ans;
int pre[maxn],bns[maxn];
struct Room{
	int c,p;
	bool operator <(const Room &B)const{return p>B.p||p==B.p&&c>B.c;}
}room[maxn];
struct Custom{
	int v,d;
	bool operator <(const Custom &B)const{return v>B.v||v==B.v&&d<B.d;}
}custom[maxn];
int read(){
	int ret=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-f;c=getchar();}
	while(isdigit(c))ret=ret*10+(c&15),c=getchar();
	return ret*f;
}
int get_pre(int x){return pre[x]==x?x:pre[x]=get_pre(pre[x]);}
int find(int x){
	int L=1,R=n,ans;
	while(L<=R){
		int mid=L+(R-L>>1);
		if(room[mid].p>=x)ans=mid,L=mid+1;else R=mid-1;
	}
	return R;
}
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)room[i].c=read(),room[i].p=read(),pre[i]=i;
	for(int i=1;i<=m;i++)custom[i].v=read(),custom[i].d=read();
	sort(room+1,room+n+1),sort(custom+1,custom+m+1);
	for(int i=1;i<=m;i++){
		int x=get_pre(find(custom[i].d));
		if(x){
			if(custom[i].v-room[x].c<=0)continue;
			bns[++cnt]=custom[i].v-room[x].c;pre[x]=get_pre(x-1);
		}
	}
	sort(bns+1,bns+cnt+1);reverse(bns+1,bns+cnt+1);
	for(int i=1;i<=min(k,cnt);i++)ans+=bns[i];
	printf("%lld",ans);
	return 0;
}

```
**警告：抄题解会得到最宝贵的用户名颜色：${\color{brown} 棕}$**

---

## 作者：Felix72 (赞：1)

题目有挑选个数限制，先考虑 WQS 二分，若峰值横坐标大于限制则直接取峰值，否则正常 WQS 即可。

二分的内部判断函数可以用反悔贪心实现，用两个小根堆表示新开一间房处理当前订单，以及退掉一单用那间房处理当前订单两种方案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
typedef pair < long long, long long > PII;
int n, m, k;
struct node {int opt; long long val, num;} s[2 * N];
inline bool cmp(node u, node v)
{
	if(u.num == v.num) return u.opt < v.opt;
	return u.num > v.num;
}
priority_queue < long long, vector < long long >, greater < long long > > q1, q2;
inline PII pd(long long x)
{
	while(!q1.empty()) q1.pop();
	while(!q2.empty()) q2.pop();
	long long ans = 0, sig = 0;
	for(int i = 1; i <= n + m; ++i)
	{
		if(s[i].opt == 1) q1.push(s[i].val);
		else
		{
			long long n1, n2; n1 = -5e9, n2 = -5e9;
			if(!q1.empty()) n1 = s[i].val + x - q1.top();
			if(!q2.empty()) n2 = s[i].val + x - q2.top();
			if(n1 >= n2 && n1 >= 0)
			{
				ans += n1; ++sig;
				q1.pop();
				q2.push(s[i].val + x);
			}
			else if(n2 >= 0)
			{
				ans += n2;
				q2.pop();
				q2.push(s[i].val + x);
			}
		}
	}
	return {ans, sig};
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; ++i) cin >> s[i].val >> s[i].num, s[i].opt = 1;
	for(int i = 1; i <= m; ++i) cin >> s[n + i].val >> s[n + i].num, s[n + i].opt = 2;
	sort(s + 1, s + n + m + 1, cmp);
	PII cur = pd(0);
	if(cur.second <= k) {cout << cur.first << '\n'; return 0;}
	long long l = -2e9, r = 2e9, fin;
	while(l <= r)
	{
		long long mid = (l + r) >> 1;
		PII cur = pd(mid);
		if(cur.second >= k) fin = cur.first - k * mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << fin << '\n';
	return 0;
}
```

---

## 作者：内拉组里 (赞：0)

一道不算很难的贪心

# Thoughts：

首先题目对房间和订单的顺序没有要求，所以先排序。

由于房间和订单之间存在单射关系，

所以这里的 $ p_i $ 和 $ d_i $ 的值的绝对大小并不重要，只需要关注相对大小关系即可。

对于同一个房间，$ c_i $ 和 $ p_i $ 一定，肯定 $ v_i $ 越大越好。

所以考虑对订单按租金降序排序，

这样枚举到每一个订单时，无论匹配哪一个房间对于这个房间而言都是最优的。

故此时只需匹配一个满足条件的，维护费用尽量小的房间即可。

这里用 **multiset** 维护房间，以容量为第一关键字，维护费用为第二关键字升序排序。

用 **multiset** 是为了方便删除已经匹配的房间。

最后用一个优先队列存储每一条订单的收益，去除前 $ o $ 大相加即可。

注意每一单的收益一定非负，故需要特判。

# Analyses：

> - 总时间复杂度 $ \Theta (N \log{N M}) $。
> - 总空间复杂度 $ \Theta (N + M) $ 

# Code：

```cpp
/* reference : @ZLOJ.huhangqi */
/* construct : JUL 28'25 */
#include	<algorithm>
#include	<iostream>
#include	<vector>
#include	<queue>
#include	<set>
#define		int		long long
using namespace std;
using pii = pair<int,int>;
constexpr int maxn = 5e5+4;

int n, m, o;
pii a[maxn];
multiset<pii> st;
priority_queue<int> ans;

signed main (void)
{
	cin >> n >> m >> o;
	for (int c, p, i = 1; i <= n; i++)
	{
		cin >> c >> p;
		st.emplace(p, c);
	}
	for (int i = 1; i <= m; i++)
		cin >> a[i].first >> a[i].second;
	sort (a + 1, a + m + 1, greater<pii>());
	for (int i = 1; i <= m; i++)
	{
		auto it = st.lower_bound(pii (a[i].second, 0));
		if (it != st.end() && a[i].first > it->second)
		{
			ans.emplace(a[i].first - it->second);
			st.erase(it);
		}
	}
	int sum = 0;
	while (o-- && !ans.empty())
	{
		sum += ans.top();
		ans.pop();
	}
	cout << sum << endl;
	return 0;
}
```

---

## 作者：PokerKing (赞：0)

## 分析：

很容易想到的贪心，优先选择价值大且人数少的订单，对于每一个订单又优先选择容量小且花费小的房间。

所以先对房间和订单排序，房间按照容量与花费排序，订单按价值和人数排序。然后二分查找找到一个人数足够花费最小的房间，记录得到的收益，然后对所有收益排序取最大的 $o$ 个。

但问题在于一个房间可能已经被之前的订单占用了，所以用并查集维护一下，如果一个房间 $x$ 被使用了，就令 $fa_{x}$ 等于 $x−1$，因为显然这样是最优的。当然注意一下当搜到的房间的 $fa$ 为 $0$ 时不能记录。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+7;
int n,m,o,fa[N],mon[N];
long long ans;
struct Room {
    int cos,p;
    bool operator < ( const Room A ) const {
        return p==A.p ? cos>A.cos : p>A.p; 
    }
}a[N];
struct Custom {
    int val,num;
    bool operator < ( const Custom A ) const {
        return val==A.val ? num<A.num : val>A.val;
    }
}b[N];
inline int read()
{
    int x=0; char ch=getchar();
    while( ch<'0' || ch>'9' ) ch=getchar();
    while( ch>='0' && ch<='9' ) {
        x=x*10+ch-'0'; ch=getchar();
    }
    return x;
}
int search(int v)
{
    int l=1, r=n, mid, ret=0;
    while( l<=r ) {
        mid=l+r>>1;
        if( a[mid].p>=v ) ret=mid, l=mid+1;
        else r=mid-1;
    }
    return ret;
}
int find(int x)
{
    return fa[x]==x ? x : fa[x]=find(fa[x]);
}
int main()
{
    n=read(), m=read(), o=read();
    for(int i=1; i<=n; ++i) {
        a[i].cos=read(), a[i].p=read(); fa[i]=i;
    }
    for(int i=1; i<=m; ++i) {
        b[i].val=read(), b[i].num=read();
    }
    sort(a+1,a+n+1); sort(b+1,b+m+1);
    //for(int i=1; i<=n; ++i) cout<<a[i].cos<<' '<<a[i].p<<'\n';
    //for(int i=1; i<=m; ++i) cout<<b[i].val<<' '<<b[i].num<<'\n';
    int x,tot=0,sum=0;
    for(int i=1; i<=m; ++i) {
        x=search(b[i].num);
        x=find(x);
        if( x ) {
            if( b[i].val-a[x].cos<=0 ) continue;
            mon[++tot]=(b[i].val-a[x].cos);
            fa[x]=x-1;
        }
    }
    sort(mon+1,mon+tot+1);
    for(int i=tot; i>0; --i) {
        ans+=mon[i]; sum++;
        if( sum==o ) break;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：BYR_KKK (赞：0)

暂时还没见过类似的做法。

考虑 $o=n$ 的情况，按照 $p$ 将所有房间进行排序。将每个订单挂到第一个能住进去的房间上，那么该订单能覆盖的就是一段后缀。经典地，扫描房间序列，维护当前位置所有能住进去的订单按照 $v$ 从大到小排序的结果。贪心安排订单，这显然是对的。

$o\ne n$ 时，考虑对于每个被选中的房间的贡献排序，选前 $o$ 个（不要选到负数）。所有过程用堆维护即可。

---

## 作者：Jordan_Pan (赞：0)

## 0

把偏序关系藏在数据范围里，出题人是有什么心事吗……（

## 1

枚举房间，把订单的收益塞到堆里，贪心地取出符合条件的最大收益订单。由于房间具有单调性质，这是对于每个房间的最优匹配。双指针跑一遍，最后最大的 $o$ 个就是答案。

时间复杂度 $O(n \log n)$。

## 2

~~~cpp
#include<cstdio>
const int rSiz=1<<21;
char rBuf[rSiz],*p1=rBuf,*p2=rBuf;
#define gc() (p1==p2&&(p2=(p1=rBuf)+ \
	fread(rBuf,1,rSiz,stdin),p1==p2)?EOF:*p1++)
template<class T>void rd(T&x){
	char ch=gc();
	for(;ch<'0'||ch>'9';ch=gc());
	for(x=0;ch>='0'&&ch<='9';ch=gc())
		x=(x<<1)+(x<<3)+(ch^48);
}
#define fr(x) \
	freopen(#x".in","r",stdin); \
	freopen(#x".out","w",stdout);
#include<algorithm>
#include<queue>
const int _=5e5+5;
int n,m,k;
struct node{
	int num,val;
	bool operator < (const node y)const{
		if(num==y.num)return val<y.val;
		return num<y.num;
	}
}a[_],b[_];
std::priority_queue<int>q,ansq;
long long ans;
int main(){
//	fr(arrange);
	rd(n);rd(m);rd(k);
	for(int i=1;i<=n;i++)rd(a[i].val),rd(a[i].num);
	for(int i=1;i<=m;i++)rd(b[i].val),rd(b[i].num);
	std::sort(a+1,a+n+1);std::sort(b+1,b+m+1);
	for(int i=1,j=1;i<=n;i++){
		for(;j<=m&&b[j].num<=a[i].num;)q.push(b[j++].val);
		if(q.empty()||q.top()<=a[i].val)continue;
		ansq.push(q.top()-a[i].val);q.pop();
	}
	for(int i=1;!ansq.empty()&&i<=k;i++)
		ans+=ansq.top(),ansq.pop();
	printf("%lld",ans);
	return 0;
}
~~~

---

