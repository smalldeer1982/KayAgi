# [ABC308F] Vouchers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc308/tasks/abc308_f

あなたは店で $ N $ 個の商品を買おうとしています。 $ i $ 個目の商品の定価は $ P_i $ 円です。

また、あなたは $ M $ 枚のクーポンを持っています。$ i $ 枚目のクーポンを使うと、定価が $ L_i $ 円以上の商品を一つ選び、その商品を定価より $ D_i $ 円低い価格で買うことができます。

ここで、一つのクーポンは一回までしか使えません。また、複数のクーポンを同じ商品に重ねて使うことはできません。

クーポンを使わなかった商品は定価で買うことになります。 $ N $ 個すべての商品を買うのに必要な最小の金額を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N,M\leq\ 2\times\ 10^5 $
- $ 1\leq\ P_i\leq\ 10^9 $
- $ 1\leq\ D_i\ \leq\ L_i\ \leq\ 10^9 $
- 入力される数値は全て整数
 
### Sample Explanation 1

$ 2 $ 枚目のクーポンを $ 1 $ 個目の商品に、 $ 3 $ 枚目のクーポンを $ 2 $ 個目の商品に使うことを考えます。 このとき、$ 1 $ 個目の商品を $ 4-3=1 $ 円、$ 2 $ 個目の商品を $ 3-1=2 $ 円、$ 3 $ 個目の商品を $ 1 $ 円で買うことになるので、 $ 1+2+1=4 $ 円で全ての商品を買うことができます。

## 样例 #1

### 输入

```
3 3
4 3 1
4 4 2
2 3 1```

### 输出

```
4```

## 样例 #2

### 输入

```
10 5
9 7 1 5 2 2 5 5 7 6
7 2 7 8 2
3 2 4 1 2```

### 输出

```
37```

# 题解

## 作者：FreedomKing (赞：9)

懂了之后感觉好简单啊，这个难度放 D 差不多吧。

### 思路

因为此题要做到优惠劵的利用最大化，所以直接贪心。

考虑先给较便宜的物品其能使用的最优优惠劵，可以直接对物品进行升序排序，然后依靠使用每张优惠劵所需要的最少金额升序排序，遍历一遍物品，当某张优惠劵能作用于第 $i$ 件物品，就将他**能优惠的金额**加入到可用序列中，最后每次都使用掉这个物品能使用的最大优惠金额的优惠劵即可，这个可用优惠劵序列直接使用优先队列维护即可。

剩下不懂的可以看代码中的注释。

------------

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long//第一次交的时候没开寄了
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
priority_queue<int>pq;
struct node{
	int l,d;
}f[N];
bool cmp(node x,node y){
	return x.l<y.l;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>f[i].l;
	for(int i=1;i<=m;i++) cin>>f[i].d;
	sort(a+1,a+n+1);
	//升序排序后面的物品就一定能用上前面物品能用的优惠卷了
	sort(f+1,f+m+1,cmp);
	t=1;
	for(int i=1;i<=n;i++){
		while(t<=m&&f[t].l<=a[i]){//寻找所有当前能使用的优惠劵
			pq.push(f[t].d);
			t++;
		}
		k+=a[i];
		if(!pq.empty()){//如果还有优惠劵
			k-=pq.top();
			pq.pop();
		}
	}
	cout<<k;
	return 0;
}
```

---

## 作者：shinzanmono (赞：4)

# ABC308F 题解

题意：有 $n$ 个物品和 $m$ 张优惠券，第 $i$ 张优惠券可以在金额 $\geq l_i$ 的物品上使用，可以将该物品的加格减小 $d_i$，求最小花费。

盲猜贪心。

我们先将所有的原价存进 `std::multiset` 里，并将所有的优惠券以 $d_i$ 为第一关键字降序，$l_i$ 为第二关键字升序排序，然后枚举，使用 `lower_bound` 找到可以用这个优惠券的最小价格，然后将它移出 `std::multiset`，直到优惠券全部被遍历完成。

```cpp
#include<iostream>
#include<algorithm>
#include<numeric>
#include<set>
const int sz=2e5+10;
using ll=long long;
std::multiset<ll>p;
struct coupon{
    int l,d;
    bool operator<(const coupon&a)const{
        if(d!=a.d)return d>a.d;
        return l<a.l;
    }
}c[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m;
    std::cin>>n>>m;
    for(int i=1,x;i<=n;i++)std::cin>>x,p.insert(x);
    for(int i=1;i<=m;i++)std::cin>>c[i].l;
    for(int i=1;i<=m;i++)std::cin>>c[i].d;
    std::sort(c+1,c+m+1);
    ll tot=std::accumulate(p.begin(),p.end(),0ll);
    for(int i=1;i<=m;i++){
        int l=c[i].l,d=c[i].d;
        auto it=p.lower_bound(l);
        if(it!=p.end())p.erase(it),tot-=d;
    }
    std::cout<<tot<<"\n";
    return 0;
}
```

---

## 作者：zac2010 (赞：4)

反悔贪心模板题。

首先，先按照 $L_i$ 从大到小对所有的优惠券进行排序。

这时候我们对所有优惠券 $i=1\to m$ 一遍扫。扫的同时维护未使用过优惠券且 $\geq L_i$ 的 $P_j$ 个数，记为 $cnt$。维护的方法就是每次让 $cnt$ 加上 $L_{i-1}-1\to L_i$ 之间的 $P_j$ 的个数。

接下来对于是否能使用这张优惠卷进行了分类讨论：
1. $cnt>0$

	直接使用。
2. $cnt=0$

	看看前面有没有劣于当前优惠券的。若有，把前面的替换为当前的。具体来说，是比较 $D_i$ 的大小以确定优劣。
    
我们要做到上述 $cnt=0$ 的情况，只需要一个能支持插入、维护最值和最值删除的数据结构——堆。

```cpp
#include <bits/stdc++.h>
#define int long long
#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 10;
struct Node{int l, d;} d[N];
int n, m, ans, cnt, a[N];
priority_queue<int, vector<int>, greater<int> > q;
bool cmp(Node x, Node y){return x.l > y.l;}
signed main(){
	scanf("%lld%lld", &n, &m);
	L(i, 1, n) scanf("%lld", &a[i]), ans += a[i];
	L(i, 1, m) scanf("%lld", &d[i].l);
	L(i, 1, m) scanf("%lld", &d[i].d);
	sort(a + 1, a + n + 1, greater<int>());
	sort(d + 1, d + m + 1, cmp);
	int it = 1;
	L(i, 1, m){
		while(it <= n && a[it] >= d[i].l) cnt++, it++;
		if(cnt) cnt--, ans -= d[i].d, q.push(d[i].d); 
		else if(!q.empty() && q.top() < d[i].d)
			ans += q.top() - d[i].d, q.pop(), q.push(d[i].d);
	}
	printf("%lld\n", ans);
	return 0;
} 
```


---

## 作者：cjh20090318 (赞：3)

## 题意

有 $N$ 个要买的商品，第 $i$ 个商品的原价是 $P_i$。

有 $M$ 张优惠券，第 $i$ 张优惠券需要满 $L_i$ 减 $D_i$。

**一个物品最多只能使用一张优惠券，每一张优惠券最多使用一次。**

问最小花费。

## 分析

很简单的一道贪心题，~~但是赛时没有想出来~~。

首先将每一个物品的价格按升序排列，每一张优惠券按 $L$ 升序排列。

接着依次遍历 $1 \sim n$ 的物品，将可以使用的优惠券加入进来。（即第 $i$ 个物品，想要使用第 $j$ 张优惠券必须满足的条件是 $L_j \le P_i$）

要求最大的 $D$，直接加入一个优先队列 `priority_queue` 即可。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<queue>
int n,m;
int p[200002];
struct TIC{
	int l,d;
	TIC(int _l=0,int _d=0):l(_l),d(_d){}
	bool operator < (const TIC& y)const{return l<y.l;}//重载运算符。
}t[200002];
std::priority_queue<int> Q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	std::sort(p+1,p+n+1);//将物品价格升序排列。
	for(int i=1;i<=m;i++) scanf("%d",&t[i].l);
	for(int i=1;i<=m;i++) scanf("%d",&t[i].d);
	std::sort(t+1,t+m+1);//将优惠券升序排列。
	long long ans=0;
	for(int i=1,j=1;i<=n;i++){
		for(;j<=m && t[j].l<=p[i];j++)Q.push(t[j].d);
		int D=0;
		if(!Q.empty())
			D=Q.top(),Q.pop();//不为空（即有可用优惠券）就取出使用。
		ans+=p[i]-D;
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Miss_SGT (赞：2)

### **思路：**

首先观察题目，发现几个性质（要求）：一件衣服只能用一张优惠券，一张优惠券仅能用一次。

从衣服去配对优惠券并不好做，所以考虑用优惠券配对衣服。对于一件衣服 $i$ 它所能搭配的衣服 $j$ 必须满足 $P{j}\ge L_{i}$。

而如何选才能保证最优呢？我刚开始想的是把优惠券按 $D$ 排序，因为这样如果前面选了一个导致后面不能选的话，它减少的钱一定比后面更多，答案也更优。这么说，每张优惠卷都应按 $P$ 最大的来，才有更多可能不浪费这个优惠券所能优惠的钱。但是第二个样例告诉我们这是错的。假如一张优惠券 $L$ 较小，
$D$ 较大，选了 $P_{n}$ ，而后面一张 $L$ 较大，$D$ 较小，要求只能选 $P_{n}$，但那件已经被选过了，不行了，答案也就小了。其实前面一张优惠券选稍微价格小点的衣服，而又能发挥最大价值（所选衣服价格大于等于该优惠券所能优惠的价格），就可以了。

所以，对于优惠券每一张 $i$，先看有没有 $P_{j}$ 满足$P_{j}\ge \max(L_{i},D_{i})$，如果有，那就选满足条件中最小的。否则选 $P_{j}\ge L_{i}$ 中最大的。

### **实现:**
然后就可以把 $P$ 排序，转变成 $RMQ$ 问题。这里我认为最简单的是在线段树上二分，这里不多赘述。

### **代码：**
```cpp
#include<bits/stdc++.h>
#define mid (l+r)/2
using namespace std;
const int N=2e5+5;
int n,m,ps[N];
struct node{
	int l,d;
}a[N];
bool cmp(node x,node y){return x.d>y.d;}
long long ans;
int mx[N*3],mi[N*3],gt;
inline int maxn(int x,int y){return ps[x]>ps[y]?x:y;}
inline int minn(int x,int y){return ps[x]<ps[y]?x:y;}
void build(int p,int l,int r){
	if(l==r){
		mx[p]=mi[p]=l;
		return;
	}
	build(2*p,l,mid);
	build(2*p+1,mid+1,r);
	mx[p]=maxn(mx[2*p],mx[2*p+1]);
	mi[p]=minn(mi[2*p],mi[2*p+1]);
}
void change(int p,int l,int r,int x){
	if(l==r){
		mx[p]=0;
		mi[p]=n+1;
		return;
	}
	if(x<=mid) change(2*p,l,mid,x);
	else change(2*p+1,mid+1,r,x);
	mx[p]=maxn(mx[2*p],mx[2*p+1]);
	mi[p]=minn(mi[2*p],mi[2*p+1]);
}
int get2(int p,int l,int r,int x){
	if(ps[l]>=x) return mi[p];
	int ans=n+1;
	if(x<=ps[mx[2*p]]) ans=minn(ans,get2(2*p,l,mid,x));
	if(x<=ps[mx[2*p+1]]) ans=minn(ans,get2(2*p+1,mid+1,r,x));
	return ans;
}
int get(int p,int l,int r,int x){
	if(ps[l]>=x) return mx[p];
	int ans=0;
	if(x<=ps[mx[2*p]]) ans=maxn(ans,get(2*p,l,mid,x));
	if(x<=ps[mx[2*p+1]]) ans=maxn(ans,get(2*p+1,mid+1,r,x));
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&ps[i]),ans+=ps[i];
	sort(ps+1,ps+n+1);
	build(1,1,n);
	ps[0]=-114514;ps[n+1]=2e9;
	for(int i=1;i<=m;i++) scanf("%d",&a[i].l);
	for(int i=1;i<=m;i++) scanf("%d",&a[i].d);
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		gt=get2(1,1,n,max(a[i].l,a[i].d));
		if(gt==n+1) gt=get(1,1,n,a[i].l);
		if(gt&&gt!=n+1){
			ans-=min(ps[gt],a[i].d);
			change(1,1,n,gt);
		}
	}printf("%lld\n",ans);
	return 0;
 }

```


---

## 作者：Msents (赞：1)

### 题意

你正在商店购买 $N$ 件商品。第 $i$ 件商品的原价是 $P_i$ 日元。

你有 $M$ 张优惠券。你可以使用第 $i$ 张优惠券来购买原价至少为 $L_i$ 日元的商品，并享受 $D_i$ 日元的折扣。

每张优惠券只能使用一次，并且不能同时使用多张优惠券购买同一件商品。

如果没有使用优惠券购买商品，则以原价购买。找出购买所有 $N$ 件商品所需的最小金额。

### 思路

简单的贪心题，甚至~~可能~~比[上一题](/problem/AT_abc308_e)还水。（

不难发现，最终答案为所有商品价值之和减去所有使用的优惠券的折扣之和。

那么问题转换成使所有使用的优惠券的折扣之和最大。

先将商品按价格从小到大排序，优惠券按 $L$ 从小到大排序。

维护一个大根堆。

从前到后依次遍历商品，将 $L$ 比当前商品价格不大于的优惠券放进堆里，然后贪心地取 $D$ 最大的优惠券使用，此时贡献为 $P-D$ 。如果堆中没有优惠券，那么贡献为 $P$ 。

最终答案为贡献总和。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//记得开longlong
const int MaxN=200000;
int n,m,a[MaxN+1];
struct Coupon{
	int l,d;
	bool operator<(const Coupon&obj)const{return l<obj.l;}
}b[MaxN+1];
void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i].l;
	for(int i=1;i<=m;i++)cin>>b[i].d;
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	priority_queue<int>p;
//这里因为L在优惠券存入队列后没有用，所以直接只存D了
	int pt=1,ans=0;
	for(int i=1;i<=n;i++){
		while(pt<=m&&a[i]>=b[pt].l)p.push(b[pt++].d);
		ans+=a[i];
		if(!p.empty()){
			ans-=p.top();
			p.pop();
		}
	}
	cout<<ans;
}
#undef int
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
//	int T;
//	cin>>T;
//	while(T--)
		Solve();
	return 0;
}
```

---

## 作者：L_zaa_L (赞：0)

## 思路
首先想到的肯定是贪心：将货物的价格从大到小排序，将优惠券按照 $L$ 从大到小，将 $L$ 大的尽量给价格大的用，这样子可以让价格小的尽量使用多点优惠券。然后就发现了一个问题，有些优惠券虽然很大，但是前面的优惠券已经和这种优惠券匹配完了，是的这张优惠券浪费了，然后就想到了用优先队列储存已经匹配过的优惠券，因为前面优惠券可以匹配的这张肯定能匹配，所以如果这张优惠券不能匹配了，就加入队列，再删除队列中最小的。

## Code
```
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define N_4 10004
#define N_5 100005
#define N_6 1000006
#define Mod 1000000007
#define For(i,j,k) for(long long i=j;i<=k;++i)
#define FoR(i,j,k) for(long long i=j;i<k;++i)
#define FOR(i,j,k) for(long long i=j;i>=k;--i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
int n,m,ans;
int p[N_5*3];
struct XXX{
	int l,d;
}a[N_5*3];
int dp[N_5*3];
priority_queue<int,vector<int>,greater<int> >q;//优先队列
bool cmd(XXX a,XXX b){//按照L进行排序
	if(a.l==b.l) return a.d>b.d;
	return a.l>b.l;
}
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		p[i]=read();
		ans+=p[i];
	}
	for(int i=1;i<=m;i++){
		a[i].l=read();
	}
	For(i,1,m){
		a[i].d=read();
	}
	sort(a+1,a+m+1,cmd);
	sort(p+1,p+n+1,cmp);
	int tot=0;
	for(int i=1;i<=n;i++){
		tot++;
		while(a[tot].l>p[i]){
			q.push(a[tot].d);
			q.pop();
			tot++;
		}//将不能匹配的加入优先队列，并删除最小的
		q.push(a[tot].d);//在匹配一组
	}
	while(!q.empty()){//所有的货物之和减去在优先队列中的所有优惠券的值就是最后需要付的钱数。
		int ss=q.top();
		ans-=ss;
		q.pop();
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Light_az (赞：0)

## STL 好

首先本题肯定使用贪心算法，对于每一张优惠劵，优先选择价格高的，然后二分查找最小价格却可以满足优惠券条件的商品。

但是我们需要删除每次支付的物品，因此本片题解的主人公 `multiset` 就出场了，它和 `set` 的作用相似，就是不去重但是排序元素，并且支持删除指定数 $x$ 操作。

因此对于每一件商品，我们把它的价格加入 `multiset` 中，然后使用迭代器在 `multiset` 二分查找，最后删除并减去它的贡献即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
multiset<ll> num;
struct Node{
	ll x,y;
}a[N];
bool cmp(Node a,Node b){
	return a.y>b.y;
}
int main(){
	cin>>n>>m;
	F(i,1,n) cin>>x,num.insert(x),ans+=x;//添加
	F(i,1,m) cin>>a[i].x;
	F(i,1,m) cin>>a[i].y;
	sort(a+1,a+1+m,cmp);//贪心排序
	F(i,1,m){
	 	auto it=num.lower_bound(a[i].x);//二分判断
	 	if(it!=num.end()) ans-=a[i].y,num.erase(it);//找到该元素，减去贡献
  
	}
	cout<<ans;//输出
	return 0;
}
```


---

## 作者：tanghg (赞：0)

# 题目大意


有 $N$ 个要买的商品，第 $i$ 个商品的原价是 $P_i$。

有 $M$ 张优惠券，第 $i$ 张优惠券需要满 $L_i$ 减 $D_i$。

一个物品最多只能使用一张优惠券，每一张优惠券最多使用一次。

问最小花费。

# 思路
首先因为每一个物品都必须买，所以问题就转化成了如何让这个总价格降价最多。

考虑贪心。

因为每一个物品最多只能使用一张优惠券，所以肯定要先用 $D$ 最大的。在 $D$ 相同时先用 $L$ 小的。因为 $L$ 小的能用的券就少。所以能给后面更大范围的更多机会。

之后我们把 $P$ 按照价格从小到大排一个序。之后从第一个优惠券开始向后枚举。二分价格最小的能用的 $P$。然后只要能用就将所有 $P$ 的总和减去当前的 $L$。

还有一个要注意的点是**一个物品最多只能使用一张优惠券**，所以在用完一张券的时候就要把对应的物品删除掉。

# 代码
```cpp
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
const ll MAXN=2e5+5;
ll n,m;
struct node{
    ll l,d;
    bool operator<(const node&K)const{
        if(d!=K.d){
            return d>K.d;
        }
        return l<K.l;
    }
}c[MAXN];
ll ans;
map<ll,ll>ma;
int main() {
    scanf("%lld%lld",&n,&m);
    set<ll>p;
    for (int i = 1; i <=n ; ++i) {
        ll P;
        scanf("%lld",&P);
        ma[P]++;
        ans+=P;
        p.insert(P);
    }
    for (int i = 1; i <=m ; ++i) {
        scanf("%lld",&c[i].l);
    }
    for (int i = 1; i <=m ; ++i) {
        scanf("%lld",&c[i].d);
    }
    sort(c+1,c+m+1);
    for (int i = 1; i <=m ; ++i) {
        auto index=p.lower_bound(c[i].l);//lower_bound 代表第一个<=查找数的指针。
        if(index==p.end()){
            continue;//如果是空集就代表这张券不能用。
        }
        ans-=c[i].d;
        ma[*index]--;
        if(ma[*index]==0){
            p.erase(index);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Self_Killer (赞：0)

### 前言（可以不看）

~~这个蒟蒻在比赛后 $n$ 个小时后才做出来，赶快电摇嘲讽 $Ta$！~~

------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc308_f)

### 题目大意

有 $n$ 个商品和 $m$ 个优惠券，第 $i$ 个商品价格为 $P_i$。第 $i$ 个优惠券要在商品价格 $\ge L_i$ 的时候才能用，优惠价格为 $D_i$。每个商品只能用一张优惠券，每张优惠券只能用一次。问：最少需要多少钱才能买走所有商品？

------------

### 解法

商品和优惠券都是集合，直接排序吧。

**等等，这题不是贪心吗？**

我们把商品按照价格从小到大排序，优惠券按照使用价格从小到大排序。我们设第 $i$ 张优惠券可以让在 $X_i$ 及以后的商品都能优惠，可以用双游标求出。再把优惠券按照 $X_i$ 排序，给一个 multiset 存目前可以用的优惠券的价格，在优惠券的 $X_i$ 与之前不同时，把这一段区间全部分配价格最大的优惠券，再把价格减掉（最后记得从 $n$ 开始再算一遍）

------------

代码有点长，先放[这里](https://atcoder.jp/contests/abc308/submissions/43214075)了

---

## 作者：引领天下 (赞：0)

题意：要购买 $n$ 个物品，第 $i$ 个物品的正价为 $P_i$。现在有 $m$ 张优惠券，第 $i$ 张优惠券只能用于购买正价至少为 $L_i$ 的商品，可以优惠 $D_i$。问至少要花多少钱。

思路：很显然是贪心，只不过贪心的策略略微有些小坑。

一个很 naive 的思想是优先处理门槛高的优惠券，避免最后这些券花不出去。

但是这样就有了一个缺点就是优惠券很多（甚至比物品还多）的时候会导致一些门槛低，优惠幅度大的优惠券反而花不出去，这样是不划算的。

所以最后我们对优惠券的排序策略从 $L$ 降序变成了 $D$ 降序。具体使用优惠券时，为了保证不浪费，我们找比 $L$ 贵的最便宜的商品花掉优惠券。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int p,L[200005],D[200005],ans,n,m;
multiset<int>a;
struct Node{
    int L,D;
    inline bool operator <(const Node&q)const{
        return D==q.D?L>q.L:D>q.D;
    }
}x[200005];
signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>p,a.insert(p);
    for(int i=0;i<m;i++)cin>>x[i].L;
    for(int i=0;i<m;i++)cin>>x[i].D;
    sort(x,x+m);
    for(int i=0;i<m;i++){
        auto p=a.lower_bound(x[i].L);
        if (p!=a.end())ans+=*p-x[i].D,a.erase(p);
    }
    for (auto i:a)ans+=i;
    cout<<ans;
    return 0;
}
```

---

