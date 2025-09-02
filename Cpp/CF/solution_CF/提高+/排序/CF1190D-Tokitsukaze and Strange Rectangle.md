# Tokitsukaze and Strange Rectangle

## 题目描述

在平面上有 $n$ 个点，第 $i$ 个点的坐标为 $(x_i, y_i)$。Tokitsukaze 想要画出一个奇特的矩形区域，并选取该区域内的所有点。

这个奇特的区域由三条直线 $x = l$、$y = a$ 和 $x = r$ 所围成，分别作为左边界、下边界和右边界，其中 $l$、$r$ 和 $a$ 可以是任意实数，且满足 $l < r$。该区域的上边界是无界的，可以认为是一条在无穷远处与 $x$ 轴平行的直线。下图展示了一个奇特的矩形区域。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1190D/61dd515911e657abcecc735a28955cca0cecb620.png)

当且仅当 $l < x_i < r$ 且 $y_i > a$ 时，点 $(x_i, y_i)$ 在这个奇特的矩形区域内。例如，在上图中，$p_1$ 在区域内，而 $p_2$ 不在区域内。

Tokitsukaze 想知道，通过选取奇特矩形区域内的所有点，她最多能获得多少个不同的非空点集。我们认为如果存在至少一个点只属于其中一个集合而不属于另一个集合，则这两个集合不同。

## 说明/提示

对于第一个样例，每个 $k = 1, 2, 3$ 都恰好有一个包含 $k$ 个点的集合，所以总数为 $3$。

对于第二个样例，分别有 $3$ 个只包含一个点的集合，$2$ 个包含两个点的集合，$1$ 个包含三个点的集合，总和为 $6$。

对于第三个样例，如下图所示：

- 有 $2$ 个只包含一个点的集合；
- 有 $3$ 个包含两个点的集合；
- 有 $1$ 个包含四个点的集合。

因此，这个例子中不同非空点集的数量为 $2 + 3 + 0 + 1 = 6$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1190D/3320cb1751acf652e79c2b37c7cba6b4de29ce5f.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1
1 2
1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1
2 1
3 1
```

### 输出

```
6
```

## 样例 #3

### 输入

```
4
2 1
2 2
3 1
3 2
```

### 输出

```
6
```

# 题解

## 作者：Alex_Wei (赞：15)

> [LG 题面传送门](https://www.luogu.com.cn/problem/CF1190D) & [CF 题面传送门](http://codeforces.ml/problemset/problem/1190/D)。

> 题意简述：一个二维平面内有 $n$ 个点，你可以画一个向上开口的矩形，求该矩形能包含多少种不同的非空点集。

这恶意评分太明显。

这题是我打过的第一场 CF 里面的。当时我还是太 naive 了。

---

排序是必要的。将所有的点以 $y$ 为第一关键字，$x$ 为第二关键字从大到小排序。

考虑当前遍历到点 $i$，那么其对答案的贡献（包含点 $i$ 且不包含任何编号大于 $i$ 的点的开口长方形个数）为：$ansl\times ansr$。

- $ansl$ 表示前 $i$ 个点落在区间 $[-\infty,x_i]$ 的不同横坐标个数。

- $ansr$ 表示前 $i$ 个点落在区间 $[x_i,\infty]$ 的不同横坐标个数。

其实很容易理解：因为要包含点 $i$，所以 $l<x_i<r$。左部不同的点集共有 $ansl$ 种（每个落在区间 $[-\infty,x_i]$ 的横坐标左边），右部不同的点集共有 $ansr$ 种（每个落在区间 $[x_i,\infty]$ 的横坐标右边）。根据乘法原理，点 $i$ 对答案的贡献就是 $ansl\times ansr$。

**但是！如果纵坐标相同，不就 GG 了吗？这也是为什么要保证 $y$ 相同时，$x$ 要有序。**

**当 $y_i=y_{i+1}$ 时：**

- 如果 $x$ 从小到大排，那么 $ansr$ 要变成前 $i$ 个点落在区间 $[x_i,x_{i+1})$ 的不同横坐标个数，这样才能保证不包含任何编号大于 $i$ 的点（想一想，为什么）。

- 如果 $x$ 从大到小排，那么 $ansl$ 要变成前 $i$ 个点落在区间 $(x_{i+1},x_i]$ 的不同横坐标个数，原因同上。

计算当前落在区间 $[l,r]$ 的不同横坐标个数可以用线段树轻松实现。如果不动态开点，那么还需将所有横坐标离散化。

```cpp
const int N=2e5+5;

struct point{
	int x,y;
	bool operator < (const point &v) const {
		return y==v.y?x>v.x:y>v.y;
	}
}c[N];

int n,p[N],sz;
ll ans;

int val[N<<2];
void modify(int l,int r,int pos,int x){
	if(l==r){
		val[x]=1;
		return;
	}
	int m=l+r>>1;
	if(pos<=m)modify(l,m,pos,x<<1);
	else modify(m+1,r,pos,x<<1|1);
	val[x]=val[x<<1]+val[x<<1|1];
}
int query(int l,int r,int ql,int qr,int x){
	if(ql<=l&&r<=qr)return val[x];
	int m=l+r>>1,ans=0;
	if(ql<=m)ans+=query(l,m,ql,qr,x<<1);
	if(m<qr)ans+=query(m+1,r,ql,qr,x<<1|1);
	return ans;
}

int main(){
	n=read();
	for(int i=1;i<=n;i++)c[i].x=p[i]=read(),c[i].y=read();
	sort(p+1,p+n+1),sz=unique(p+1,p+n+1)-p-1;
	for(int i=1;i<=n;i++)c[i].x=lower_bound(p+1,p+sz+1,c[i].x)-p;
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++){
		modify(1,sz,c[i].x,1);
		ans+=1ll*query(1,sz,(c[i+1].y==c[i].y?c[i+1].x+1:1),c[i].x,1)*query(1,sz,c[i].x,sz,1);
	}
	cout<<ans<<endl;
	return 0; 
}
```

要是当时我想到这种解法多好啊，但是我太菜了。

---

## 作者：Eibon (赞：6)

先进行离散化，以纵坐标为第一顺位，从高到低排。以横坐标为第二顺位，从小到大排。

使用树状数组或者线段树进行统计，为了避免重复，对于每一个点，我们只需统计横坐标在 $x_{i}$ 与 $x_{i-1}$ 的点的数量即可。

### 双倍 CODE 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int n,id1,id2,pos,now,ans;
int t[maxn],x[maxn],y[maxn],vis[maxn];
int lowbit(int x)
{
	return x&(-x);
}
void update(int x,int w)
{
	while(x<=n){
		t[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x)
{
	int sum=0;
	while(x){
		sum+=t[x];
		x-=lowbit(x);
	}
	return sum;
}
struct node
{
	int x,y;
	bool operator < (const node &k) const
	{
		if(y==k.y){
			return x<k.x;
		}
		return y>k.y;
	}
};
node a[maxn];
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x[i],&y[i]);
		a[i].x=x[i];a[i].y=y[i];
	}
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	id1=unique(x+1,x+n+1)-x-1;
	id2=unique(y+1,y+n+1)-y-1;
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(x+1,x+id1+1,a[i].x)-x;
		a[i].y=lower_bound(y+1,y+id2+1,a[i].y)-y;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(i<n&&a[i].y==a[i+1].y){
			if(!vis[a[i].x]){
				update(a[i].x,1);
				vis[a[i].x]=1;
			}
			continue;
		}
		if(!vis[a[i].x]){
			update(a[i].x,1);
			vis[a[i].x]=1;
		}
		pos=i;
		while(a[pos-1].y==a[pos].y&&pos>1){
			pos--;
		}
		now=0;
		for(int j=pos;j<=i;j++){
			ans+=(query(n)-query(a[j].x-1))*(query(a[j].x)-query(now));
			now=a[j].x;
		}
	}
	printf("%lld\n",ans);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int n,id1,id2,pos,now,ans;
int t[maxn],x[maxn],y[maxn],vis[maxn];
struct Tree
{
	int sum,lz;
};
Tree tree[maxn*4];
void pushup(int root)
{
	tree[root].sum=tree[root<<1].sum+tree[root<<1|1].sum;
}
void pushdown(int root,int l,int r)
{
	int mid=(l+r)>>1;
	tree[root<<1].lz+=tree[root].lz;
	tree[root<<1].sum+=tree[root].lz*(mid-l+1);
	tree[root<<1|1].lz+=tree[root].lz;
	tree[root<<1|1].sum+=tree[root].lz*(r-mid);
	tree[root].lz=0;
}
void build(int root,int l,int r)
{
	if(l==r){
		tree[root].sum=0;
		return;
	}
	int mid=(l+r)>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	pushup(root);
}
void update(int root,int l,int r,int L,int R,int k)
{
	if(L<=l&&r<=R){
		tree[root].sum+=(r-l+1)*k;
		tree[root].lz+=k;
		return;
	}
	if(tree[root].lz)pushdown(root,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)update(root<<1,l,mid,L,R,k);
	if(R>mid)update(root<<1|1,mid+1,r,L,R,k);
	pushup(root);
}
int query(int root,int l,int r,int L,int R)
{
	if(R<L)return 0;
	if(L<=l&&r<=R)return tree[root].sum;
	if(tree[root].lz)pushdown(root,l,r);
	int mid=(l+r)>>1;
	int res=0;
	if(L<=mid)res+=query(root<<1,l,mid,L,R);
	if(R>mid)res+=query(root<<1|1,mid+1,r,L,R);
	return res;
}
struct node
{
	int x,y;
	bool operator < (const node &k) const
	{
		if(y==k.y){
			return x<k.x;
		}
		return y>k.y;
	}
};
node a[maxn];
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x[i],&y[i]);
		a[i].x=x[i];a[i].y=y[i];
	}
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	id1=unique(x+1,x+n+1)-x-1;
	id2=unique(y+1,y+n+1)-y-1;
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(x+1,x+id1+1,a[i].x)-x;
		a[i].y=lower_bound(y+1,y+id2+1,a[i].y)-y;
	}
	build(1,1,n);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(i<n&&a[i].y==a[i+1].y){
			if(!vis[a[i].x]){
				update(1,1,n,a[i].x,a[i].x,1);
				vis[a[i].x]=1;
			}
			continue;
		}
		if(!vis[a[i].x]){
			update(1,1,n,a[i].x,a[i].x,1);
			vis[a[i].x]=1;
		}
		pos=i;
		while(a[pos-1].y==a[pos].y&&pos>1){
			pos--;
		}
		now=0;
		for(int j=pos;j<=i;j++){
			ans+=(query(1,1,n,1,n)-query(1,1,n,1,a[j].x-1))*(query(1,1,n,1,a[j].x)-query(1,1,n,1,now));
			now=a[j].x;
		}
	}
	printf("%lld\n",ans);
    return 0;
}
//dyyyyds
//dyyyyds
```

---

## 作者：Frozencode (赞：5)

~~扫描线板子题？~~

首先离散化是理所当然的，因为这个矩形无上界，我们考虑按$y$排序，从上往下枚举$y$。~~（其实也算是出题人的暗示）~~

接下来的问题是如何统计下界为$y$的矩形数量，事实上我们只关心矩形的$l$和$r$,自然而然想到枚举,枚举什么？$l,r$？$No$枚举$l$和$r$会让复杂度爆炸。

考虑如何优化，~~（当然是换个东西枚举）~~
我们选择枚举$y$相同的点，对于一个点$(x_1,y_1)$，在$x=x_1$左侧的点会对$l$产生贡献，在$x=x_1$右侧的点会对$r$产生贡献。但是我们发现这样有**重复**的矩形！

~~仔细~~思考一波，事实上不同的$l$产生的矩形是不同的，对于一个点$(x_i,y_i)$，只有在$x=x_{i-1}$(这里$y_{i-1}=y_i$)到$x=x_i$之间的$l$还没有被统计过。这样我们只需要统计$x=x_i$右侧的点和$x=x_{i-1}$到$x=x_i$之间的点的数量，再根据乘法原理得到答案就行了。

萌新：统计要$O(n)$枚举啊。

神犇：出门左转树状数组。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=200010;
const ll INF=2147483647;
struct node
{
	ll x,y;
}a[maxn];
node r[maxn];
bool cmpy(node x,node y)
{
	if(x.y == y.y)return x.x < y.x;
	return x.y > y.y;
}
ll n,ix[maxn],iy[maxn],totx,toty,cnt[maxn],tot,res;
bool vis[maxn];
ll lowbit(ll x)
{
	return x & (-x);
}
void update(ll x)
{
	while(x <= n)
	{
		cnt[x]++;
		x += lowbit(x);
	}
	return;
}
ll qry(ll x)
{
	ll tem = 0;
	while(x)
	{
		tem += cnt[x];
		x -= lowbit(x);
	}
	return tem;
}
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i].x>>a[i].y;
		ix[i] = a[i].x;
		iy[i] = a[i].y;
	}
	sort(ix + 1,ix + n + 1);
	sort(iy + 1,iy + n + 1);
	totx = unique(ix + 1,ix + n + 1) - ix - 1;
	toty = unique(iy + 1,iy + n + 1) - iy - 1;
	for(int i = 1;i <= n;i++)
	{
		a[i].x = lower_bound(ix + 1,ix + totx + 1,a[i].x) - ix;
		a[i].y = lower_bound(iy + 1,iy + toty + 1,a[i].y) - iy;
	}
	//for(int i = 1;i <= n;i++)cout<<i<<" "<<a[i].x<<" "<<a[i].y<<endl;
	sort(a + 1,a + n + 1,cmpy);
	for(int i = 1;i <= n;i++)
	{
		if(i < n && a[i].y == a[i + 1].y)
		{
			if(!vis[a[i].x])
			{
				update(a[i].x);
				vis[a[i].x] = 1;
			}
			continue;
		}
		if(!vis[a[i].x])
		{
			update(a[i].x);
			vis[a[i].x] = 1;
		}
		ll pos = i;
		while(a[pos - 1].y == a[pos].y && pos > 1)pos--;
		ll item = 0;
		for(int j = pos;j <= i;j++)
		{
			res += 1ll * (qry(n) - qry(a[j].x - 1))*(qry(a[j].x) - qry(item));
			//cout<<j<<" "<<res<<"\n";
			item = a[j].x;
		}
	}
	cout<<res;
	return 0;
}
```


---

## 作者：XeniaF (赞：1)

小清新计数题。

考虑对于所有点按 $y$ 值大小排序，由上到下算贡献，有左到右算贡献，每个点算**自己必选**能造成的贡献。考虑有哪几种贡献。

对左边所有 $x$ 值比它小，$y$ 值不小于它的贡献：

&nbsp;&nbsp;&nbsp;此时相当于计算当前点的 $x$ 前面有多少种不同的 $x$ 值。

对右边所有 $x$ 值不小于它，$y$ 值不小于它的贡献：

&nbsp;&nbsp;&nbsp;发现如果算入了 $y$ 值与它相同且 $x$ 比它大的情况，那么在计算后面这个 $x$ 时这段区间也会重复算一次。因此此时的 $x$ 计算范围应该从当前 $x$ 开始，到下一个 $x_{next}-1$ 结束。

对所有跨它的区间：

&nbsp;&nbsp;&nbsp;发现就是上面两种情况左右拼凑一下即可，因此就是 $l_{ans}\times r_{ans}$ 。

## code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IN inline
#define RI register
#define I inline ll
#define V inline void
#define B inline bool
#define vd void()
#define db double
using namespace std;
const ll maxn=2e5+10;

ll n;
struct Node{
	ll x,y;
}q[maxn];
ll c[maxn];
ll d[maxn];
ll ln;
ll ld;

I read(){
	ll x=0,f=0;char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x; 
}

B cmp(Node dx,Node dy) {return (dx.y==dy.y)?dx.x<dy.x:dx.y>dy.y;}

bool ik[maxn];
ll ans;

struct Tree{
	ll tr[maxn];
	I lowbit(ll x) {return x&(-x);}
	V ins(ll x) {while(x<=ld) ++tr[x],x+=lowbit(x);}
	I qry(ll x) {ll re=0;while(x)re+=tr[x],x-=lowbit(x);return re;}
}tr,tr2;

signed main(){
	n=read();
	for(RI int i=1;i<=n;++i) q[i].x=read(),q[i].y=read();
	for(RI int i=1;i<=n;++i) d[i]=q[i].x,c[i]=q[i].y;
	sort(c+1,c+n+1),sort(d+1,d+n+1);
	ln=unique(c+1,c+n+1)-c-1,ld=unique(d+1,d+n+1)-d-1;
	for(RI int i=1;i<=n;++i) q[i].y=lower_bound(c+1,c+ln+1,q[i].y)-c;
	for(RI int i=1;i<=n;++i) q[i].x=lower_bound(d+1,d+ld+1,q[i].x)-d;
	sort(q+1,q+n+1,cmp);
	for(RI int i=1;i<=n;++i){
		++ans;
		ll re=tr.qry(q[i].x-1);
		ll tk=tr2.qry(ld-q[i].x);
		if(q[i+1].y==q[i].y) 
			tk-=tr2.qry(ld-q[i+1].x+1);
		ans+=re+tk;
		if(re&&tk) ans+=max(1ll,re)*max(1ll,tk);
		if(!ik[q[i].x]) tr.ins(q[i].x),tr2.ins(ld-q[i].x+1),ik[q[i].x]=1;
	}
	printf("%lld\n",ans);
	return 0;
} 
```



---

## 作者：GJX_Algorithm (赞：0)

# CF1190D 题解
## 题目描述
- 一个平面上有 $n$ 个点。

- 你能画一个由 $x = l$，$y = a$，$x = r$ 三条线围成的开口向上的矩形。

- 求一共可以框选多少种非空点集。

## 解题思路
- 其实就是个~~计数题~~，顺便有一点点树状数组（线段树）。
  
- 首先离散化，接着我们可以先按纵坐标从大到小排序，那么每个点对答案的贡献就是其左边的点（包括它）的个数与右边的点（包括它）的个数的积（这段文字可能有点难理解，看个图），统计树状数组就行。
![](https://cdn.luogu.com.cn/upload/image_hosting/0kho33jr.png)

- 但！！！这样写就会完蛋。为啥呢？我们发现同一纵坐标上可能有很多点，那么我们排序要有一个第二关键字，及为横坐标，所以此时枚举到的灰点的蓝线的区间就要到下一个点结束。

- 其实这题的重点是计数和处理特殊情况，~~树状数组倒显得没那么重要了~~。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x & -x
using namespace std;
const int N = 2e5 + 5;
int n, ans;
int c[N], b[N], tree[N];
bool vis[N];
struct node
{
    int x, y;
}a[N];
int query(int x)
{
    int sum = 0;
    while (x > 0)
    {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}
void update(int x, int val)
{
    while(x <= 1e6 + 1)
    {
        tree[x] += val;
        x += lowbit(x);
    }
    return ;
}
void discrete()
{
    sort(b + 1, b + n + 1);
    int len = unique(b + 1, b + n + 1) - (b + 1);
    for (int i = 1; i <= n; i++) a[i].x = lower_bound(b + 1, b + n + 1, a[i].x) - b;
    sort(c + 1, c + n + 1);
    len = unique(c + 1, c + n + 1) - (c + 1);
    for (int i = 1; i <= n; i++) a[i].y = lower_bound(c + 1, c + n + 1, a[i].y) - c;
    return ;
}
bool cmp(node l, node r)
{
    if (l.y == r.y) return l.x < r.x;
    return l.y > r.y;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y, b[i] = a[i].x, c[i] = a[i].y;
    discrete();
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
    {
        if (i != n && a[i].y == a[i + 1].y) //特殊情况
        {
            if (vis[a[i].x] == 0)
            {
                update(a[i].x, 1);
                vis[a[i].x] = 1;
            }
            continue;
        }
        if (vis[a[i].x] == 0) //只有一点
        {
            update(a[i].x, 1);
            vis[a[i].x] = 1;
        }
        int pos = i; //存位置，要找到这条线第一个点
        while(pos >= 2 && a[pos - 1].y == a[pos].y) pos--;
        int nxt = 0;
        for (int j = pos; j <= i; j++)
        {
            int l = query(n) - query(a[j].x - 1);
            int r = query(a[j].x) - query(nxt);
            ans += l * r;
            nxt = a[j].x;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

想的时间有点久，但做完觉得是唐题，还是太菜了。
### 题意
给定平面上 $n$ 个整点，定义一次框选出的点集是用 $x=l$，$x=r$，$y=a$（其中 $l<r$，$l$，$r$，$a$ 都是实数）三条直线围成的图形内的点集，问总共能框选出多少种非空点集。
### 分析
首先一个简单的观察，可以为实数的条件其实没什么用，只是能让你单独框选出一列中的一些点，所以我们让 $l\leq r$，这样只要取整数。又发现如果有任意一条边上没有点，那么肯定可以往里面缩到碰到某个点，点集不变，所以只要考虑三条边上都有点的情况。

接下来，静态二维问题，通常可以离散化以后用扫描线转化成动态一维。

所以我们考虑扫描线，先确定扫的横纵和方向。这里如果横着扫要考虑两条直线，不好维护，所以我们纵向扫描线。那么在钦定了框选的底线以后，我们只要考虑 $y$ 坐标在底线以上的点，所以从上往下扫描，这样就可以维护底线以上的信息。

现在枚举了底线，考虑两边的线的选法，显然可以在已经在该横坐标出现过点的横坐标里任意选择两个，但是这样选只保证了两条边线上有点，底线上的点无法保证。发现控制底线上有点不好做，那么我们正难则反，用随便选的方案数减去不合法的方案数，也就是枚举底线上相邻的两个点，算出两条边线被它们完全夹在中间的方案数减掉。那么我们动态维护当前的 $x$ 轴，如果该坐标出现过点则为 $1$，否则为 $0$，现在就是一个单点赋值区间求和问题，简单 BIT 即可。

总共是 $\mathcal O(n)$ 次修改和 $\mathcal O(n)$ 次查询，所以时间复杂度 $\mathcal O(n\log_2n)$，可以通过。

具体实现见代码。
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
const int maxn=2e5+5;
int n,ans;
struct node{
	int x,y;
}a[maxn];
int tx[maxn],ttx;
int ty[maxn],tty;
int vis[maxn];
vector<int> A[maxn];
struct Fenwick_Tree{
	int c[maxn];
	int lowbit(int x){
		return x&(-x);
	}
	void update(int x,int k){
		while(x<=ttx){
			c[x]+=k;
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}tr;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read();
		tx[++ttx]=a[i].x;ty[++tty]=a[i].y;
	}
	sort(tx+1,tx+ttx+1);sort(ty+1,ty+tty+1);
	ttx=unique(tx+1,tx+ttx+1)-tx-1;tty=unique(ty+1,ty+tty+1)-ty-1;
	for(int i=1;i<=tty;i++) A[i].eb(0);
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(tx+1,tx+ttx+1,a[i].x)-tx;
		a[i].y=lower_bound(ty+1,ty+tty+1,a[i].y)-ty;
		A[a[i].y].eb(a[i].x);
	}
	for(int i=tty;i>=1;i--){
		if(A[i].size()>2) sort(A[i].begin(),A[i].end());
		for(int x:A[i]) if(x&&!vis[x]) tr.update(x,1),vis[x]=1;
		int s=tr.query(ttx);
		ans+=s*(s+1)/2;
		A[i].eb(ttx+1);
		for(int j=1;j<A[i].size();j++){
			if(A[i][j]-A[i][j-1]>1){
				int k=tr.query(A[i][j]-1)-tr.query(A[i][j-1]);
				ans-=k*(k+1)/2;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：xukuan (赞：0)

### 离散化+树状数组

根据数据范围，$1 \leq n \leq 2*10^{5},1 \leq x_{i},y_{i} \leq 10^{9}$，离散化很好想到

至于如何实现离散化在此不再多讲

由于这个矩形没有上届，那么我们可以从上到下枚举纵坐标

接着肯定不能再枚举$x=l,r$，那么考虑优化

对于点$(x_{i},y_{i})$，在直线$x=x_{i}$左侧的点会对$l$产生贡献；同理，右侧的点会对$r$产生贡献。但是这样不能排除重复的矩形

不过，对于点$x_{i}$,我么只要统计横坐标从$x_{i-1}$到$x_{i}$中的点就行了。

这里就是每一个点加进去，统计一个区间=>

单点修改区间查询=>

树状数组

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

bool v[200010];
ll n,totx,toty,ans,X[200010],Y[200010],sum[200010];
struct node{
	ll x,y;
}a[200010];
//sum是树状数组的求和数组
//v[i]表示直线x=i有没有被统计

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline bool cmp(node a,node b){
	return a.y==b.y?a.x<b.x:a.y>b.y;
}

inline ll lowbit(ll x){
	return x&(-x);
}

inline void update(ll x){
	while(x<=n){
		sum[x]++;
		x+=lowbit(x);
	}
	return;
}

inline ll query(ll x){
	ll ans=0;
	while(x){
		ans+=sum[x];
		x-=lowbit(x);
	}
	return ans;
}

int main(){
	n=read();
	for(ll i=1; i<=n; i++){
		X[i]=a[i].x=read();
		Y[i]=a[i].y=read();
	}
	sort(X+1,X+1+n);
	sort(Y+1,Y+1+n);
	totx=unique(X+1,X+1+n)-X-1;
	toty=unique(Y+1,Y+1+n)-Y-1;
	for(ll i=1; i<=n; i++){
		a[i].x=lower_bound(X+1,X+1+totx,a[i].x)-X;
		a[i].y=lower_bound(Y+1,Y+1+toty,a[i].y)-Y;
	}//离散化
   
	sort(a+1,a+1+n,cmp);
	for(ll i=1; i<=n; i++){
		if(i<n&&a[i].y==a[i+1].y){//一个点和后面的点横坐标相同
			if(!v[a[i].x]){
				update(a[i].x);
				v[a[i].x]=1;//访问过
			}
			continue;
		}
		if(!v[a[i].x]){//这条直线没访问到
			update(a[i].x);//单点修改
			v[a[i].x]=1;//标记为访问
		}
		//区间查询
		ll now=i;
		while(a[now-1].y==a[now].y&&now>1) now--;
		ll Next=0;
		for(ll j=now; j<=i; j++){
			ans+=(query(n)-query(a[j].x-1))*(query(a[j].x)-query(Next));
			Next=a[j].x;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

