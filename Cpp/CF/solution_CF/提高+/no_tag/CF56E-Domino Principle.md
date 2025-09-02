# Domino Principle

## 题目描述

Vasya is interested in arranging dominoes. He is fed up with common dominoes and he uses the dominoes of different heights. He put $ n $ dominoes on the table along one axis, going from left to right. Every domino stands perpendicular to that axis so that the axis passes through the center of its base. The $ i $ -th domino has the coordinate $ x_{i} $ and the height $ h_{i} $ . Now Vasya wants to learn for every domino, how many dominoes will fall if he pushes it to the right. Help him do that.

Consider that a domino falls if it is touched strictly above the base. In other words, the fall of the domino with the initial coordinate $ x $ and height $ h $ leads to the fall of all dominoes on the segment $ [x+1,x+h-1] $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF56E/f65e42e981956283652c923668ef12c3abd4f3cc.png)

## 样例 #1

### 输入

```
4
16 5
20 5
10 10
18 2
```

### 输出

```
3 1 4 1 ```

## 样例 #2

### 输入

```
4
0 10
1 5
9 10
15 10
```

### 输出

```
4 1 2 1 ```

# 题解

## 作者：H6_6Q (赞：7)

[**CF56E 【Domino Principle】**](https://www.luogu.com.cn/problem/CF56E)        
$ $     
#### 题目翻译：
>有 $n$ ( $n \le 10^5$ ) 个多米诺骨牌在一条直线上，给定他们的坐标 $x$和高度 $h$  ( $x$ 越大则越靠右) ，求出当第 $i$ 个骨牌向右倒下时会有几个骨牌倒下。第 $i$ 块骨牌能压倒的范围在 $[x_i+1,x_i+h_i-1]$ 之间。     

  
#### 需要注意的地方：
- 输入中骨牌的 $x$ 值不一定有序
- 被压倒骨牌可能也会压倒其他骨牌


#### 思路：
直接暴力算肯定会T，二分的话因为会有重复部分所以也不好做，因此考虑动态规划。     
1. 先按照 $x$ 坐标排正序，但枚举时要从后向前枚举 (因为后面骨牌的不会影响前面，因此先从后面算
1. 每次计算 $ans_i$ 时先考虑 $i$ 能否压倒 $i+1$，如果可以就加上 $ans_{i+1}$  ，然后再看 $i$ 能否压倒 $i+1$ 不能压倒的第一块骨牌，可以答案就再加上那块骨牌的答案，以此类推。

#### 代码：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<cmath>
#include<queue>
#include<map>
#include<set>

using namespace std;

int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

const int N=1e5+5;
int n,ans[N],last[N];
// last 存储排序后的第 i 块骨牌压不倒的第一块骨牌的位置

struct Node
{
	int x,h,p;  // p 用来标记问题编号
	bool operator < (const Node &t)const
	{  // 重载运算符，排序时按照 x 正序排列
		return t.x>x;
	}
}a[N];

int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i].x=read();
		a[i].h=read();
		a[i].p=i;
	}  // 读入
	sort(a+1,a+1+n); / / 排序
	for(int i=1;i<=n;++i)
		ans[i]=1; // 因为压倒一块骨牌时它自己一定会倒(这不是废话吗...)，所以答案至少是 1
	for(int i=n-1;i>=1;--i)
    // 因为最后面的骨牌谁都压不到，所以直接从 n-1 开始算
	{
		int now=i+1;  // now 存储下一次需要比较的骨牌下标，最开始为 i+1
		while(now&&a[i].x+a[i].h>a[now].x)
        // 如果后面还有骨牌 并且 这块骨牌能压倒下一个需要压倒骨牌
		{
			ans[a[i].p]+=ans[a[now].p];
            // 就把答案加上下一块需要压倒的骨牌的答案
			now=last[now];
            // 并更新 now 为 刚压倒的这块骨牌 的首个无法压倒的骨牌的下标
		}
		last[i]=now;  // 维护 last ，因为下标为 now 的骨牌已经无法被压倒，且它前面的骨牌都可以被压倒，所以 now 就是这块骨牌的首个无法被压倒的骨牌
	}
	for(int i=1;i<=n;++i)
    //输出时注意按照原输入顺序来输出
		printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Max_QAQ (赞：4)

看完题干有种莫名的熟悉感。

**思路**：

我们可以考虑这样一个 $O(n \log n)$ 的方法。瓶颈在排序上，核心代码是线性的。

首先将整个序列按照位置排好序。

又因为每个骨牌只能压倒他右侧的骨牌，所以我们不需要去考虑他左侧的。

因此我们就可以从右往左一次枚举，看看他是否能压倒他右侧的骨牌。

如果一个骨牌能够压倒他右面的骨牌，那也一定能压倒他右面的骨牌能压倒的所有骨牌，而且还可能压倒更多。

所以对于每一个已经判断过的骨牌，我们分别记录下他能够压倒的最靠右的骨牌。

这样一来，当前的骨牌如果可以压倒他右面的骨牌，我们可以直接将右侧能够压倒最多的骨牌转移。然后再接着判断能否压倒，能的话就继续，直到压不倒为止。

然后再简单的证明一下核心代码的线性复杂度。

核心代码长下面这样

```cpp

for(int i=n-1;i;i--)
	while(Dom[i].r<n&&Dom[Dom[i].r+1].pos-Dom[i].pos<Dom[i].range)
    		Dom[i].r=Dom[Dom[i].r+1].r;

```

外层的循环显然是线性的，内层循环看似要循环很多次但实际上并不会。

若有一个骨牌一次性的压倒了很多并没有被之前的骨牌压倒过的，若压倒了之前就被压倒了的那么他自然也就跳过这些判断了，那么其他没被之前压倒的骨牌就都被算在当前的骨牌身上了，之后再算过来就只需要判断能不能压倒当前的骨牌，如果能的话后面的一串也自然可以，如果不行那么显然再往后的骨牌也都不能被压倒，这样就能大大减少每次判断的操作了。

所以对于每个骨牌至多被判断一次，因此这两层循环的复杂度就是线性的了。

然后又因为事先排了一遍序，所以总的复杂度就是 $O(n \log n)$ 了。

**注意：**

题目里规定能压倒的范围是 $[x+1,x+h-1]$ ，要注意不能压倒 $x+h$ 的位置

再上个代码。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(int x){
	static int sta[35];int top=0;
	if(x<0) putchar('-'),x=-x;
	do{sta[++top]=x%10,x/=10;}while(x);
	while(top) putchar(sta[top--]+'0');
	putchar(' ');return;
}
inline void chkmax(int &x,int y){return x=(x>y)?x:y,void();}
inline void chkmin(int &x,int y){return x=(x<y)?x:y,void();}
int n,ans[100010];
struct domino{
	int pos,range,r,id;
	bool operator< (const domino &a)const{//根据位置进行排序。
		return pos<a.pos;
	}
}Dom[100010];
signed main(){
	n=read();
	for(int i=1;i<=n;i++) Dom[i].pos=read(),Dom[i].range=read(),Dom[i].id=i;//记录下来位置和范围，因为要排序所以要记录下 id。
	sort(Dom+1,Dom+1+n);
	for(int i=1;i<=n;i++) Dom[i].r=i;//初始化一下，每个骨牌一开始只能压倒自己。
	for(int i=n-1;i;i--) while(Dom[i].r<n&&Dom[Dom[i].r+1].pos-Dom[i].pos<Dom[i].range) Dom[i].r=Dom[Dom[i].r+1].r;//满足条件，直接转移。因为不能压倒x+h的位置所以用<。
	for(int i=1;i<=n;i++) ans[Dom[i].id]=Dom[i].r-i+1;//自己的位置是 i 两个一减就是个数。
	for(int i=1;i<=n;i++) write(ans[i]);
	return 0;
}

```

---

## 作者：mzyc_jx (赞：3)

[Domino Principle](https://www.luogu.com.cn/problem/CF56E)

这道题是真的~~水~~难，连本蒟蒻都能做出来。

## 思路：

1. 先将整个序列排好序。

2. 然后我们可以从右往左依次枚举，看它是否能压倒它右侧的骨牌。

3. 如果一个骨牌能够压倒它右边的骨牌，那也一定能压倒它右边的骨牌能压倒的所有骨牌。

4. 分别记录下每一个已经判断过的骨牌能够压倒的最靠右的骨牌。

5. 当前骨牌如果能压倒它右边的骨牌，我们可以直接加上它右边能够压倒的最多骨牌数。再接着判断能否压倒，能的话就继续。

### CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct domino
{
	int x,h,bh;//分别存储骨牌的位置、高度和编号
}a[100001];
inline bool cmp(domino x,domino y)
{
	return x.x<y.x;//从小到大排序
}
int ans[100001],b[100001];//b存储第i块骨牌压不倒的第一块骨牌的位置
int main()
{
	int n;
	cin>>n;
	for(register int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].h;
		a[i].bh=i;
	}
	sort(a+1,a+n+1,cmp);
	for(register int i=1;i<=n;i++)
	ans[i]=1;//因为无论压没压倒骨牌它自己一定会倒，所以答案至少为1
	for(register int i=n-1;i>0;i--)
	{
		int c=i+1;//存储下一次需要比较的骨牌编号
		while(c!=0&&a[i].x+a[i].h>a[c].x)//如果后面还有骨牌且能压倒下一个（因为不能压倒x+h的位置所以这里用<）
		{
			ans[a[i].bh]+=ans[a[c].bh];//把答案加上下一块压倒的骨牌能压倒的数量
			c=b[c];//c为刚压倒的骨牌的首个无法压倒的骨牌的编号
		}
		b[i]=c;//更新b
	}
	for(register int i=1;i<=n;i++)
	cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### 解题思路：

由于每一个骨牌并不是按照位置排序的，考虑先将其按照位置从小到大排序，然后从后往前考虑每一个骨牌。

发现，如果一个骨牌能够压到后面的某一个骨牌，那么也就一定能压到右边那个骨牌能压倒的所有的骨牌，首先想到一种二分向右直接压到的骨牌位置，然后根据直接能压到的其中的最大值来判定当前骨牌能压倒的骨牌数量。

这样的复杂度是 $O(nlogn)$ 的，已经可以通过本题了，但这样还不够优秀，其实这个后面的判定算法是可以做到 $O(n)$ 的。

-----
对于一个位置，将原先的二分法改为向右直接搜索位置，每一次直接跳到当期所在骨牌所能压倒的位置，能压倒的最右边的位置直接就是跳到的最后一个位置。

正确性行上。由于每一个位置能压倒的位置一定在其右边，所以单个位置最劣情况就是直接枚举过去。另一方面，即使原位置不能压到，通过一开始的分析也应当是可行的解，所以也不存在直接跳过了应当存在的位置。

复杂度上由于一个位置如果被另一个位置压到，也就意味着这个位置被那个位置覆盖了，

----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int nxt,id,h,x,ans;
}p[100005];
bool cmp1(node a,node b){
	return a.x<b.x;
}
bool cmp2(node a,node b){
	return a.id<b.id;
}
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d",&p[i].x,&p[i].h),p[i].id=i,p[i].ans=1;;
	sort(p+1,p+n+1,cmp1);
	for(int i=1;i<=n;i++)
	p[i].nxt=i;
	p[n+1].x=2147483647;
	for(int i=n;i>=1;i--){
		while(p[i].nxt<n&&p[p[i].nxt+1].x-p[i].x<p[i].h)
		p[i].ans+=p[p[i].nxt+1].ans,p[i].nxt=p[p[i].nxt+1].nxt;
	}
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<=n;i++)
	printf("%d ",p[i].ans);
	return 0;
}
```




---

## 作者：PanH (赞：1)

## 树状数组大法好！

比较明显的 dp 方程：

$$f[i]=\max\{f[j]+j-i\},(pos[j]-pos[i]<len[i],j>i)$$

从右往左扫，$pos$ 是骨牌的位置， $len$ 是骨牌的长度。

暴力显然是 $O(n^2)$ 的，考虑用数据结构维护 $f[j]+j$ 。

别的题解都讲的比较清楚了，但基本上都用了线段树来维护区间最大值，而我们其实可以用树状数组代替线段树 ~~（时间复杂度没变，但多好打啊）~~。

一般的树状数组只能用来维护前缀和，但考虑到那时询问的是区间，为了求 $sum[i]-sum[j]$ ,维护的信息必须满足可减性。

区间 $\max$ 不满足可减性，但没关系，对于这题我们不需要减。因为从右往左 dp 时 $i$ 之前的值肯定没更新到，都是 $0$ 。也就是说，我们只要求前缀 $\max$ 就可以了（还有二分求最右边能压倒的骨牌）。

时间复杂度： $O(n\log n)$ 。

code ~~（轻微压行）~~：
```
#include<bits/stdc++.h>
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
using namespace std;
const int N=1e5+5;
int n,f[N],pos[N],ans[N],pos2[N],tree[N];
struct node{
	int len,id;
	bool operator < (const node x) const {return pos[id]<pos[x.id];}
}a[N];
inline void add(int x,int v)	{for(int i=x;i<=n;i+=i&-i)	tree[i]=max(v,tree[i]);}
inline int query(int x)
{
	int res=0;
	for(int i=x;i>=1;i-=i&-i)	res=max(res,tree[i]);
	return res;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)	read(pos[i]),read(a[i].len),a[i].id=i,a[i].len--,pos2[i]=pos[i];
	sort(a+1,a+n+1),sort(pos2+1,pos2+n+1);
	for(int i=n,p;i;i--)
	{
		p=upper_bound(pos2+1,pos2+n+1,pos[a[i].id]+a[i].len)-pos2-1;
		f[i]=max(query(p)-i,1),add(i,f[i]+i);
		ans[a[i].id]=f[i];
	}
	for(int i=1;i<=n;i++)	printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：LTb_ (赞：1)

> [link](https://codeforces.com/problemset/problem/56/E)
>
> 题意简述：给你一些多米诺骨牌，在 $x$ 轴上从左到右排列在一起，问每一个倒向右边的时候会压倒多少个骨牌？

首先按坐标升序排序

从后往前维护 $to_i$，表示第 $i$ 个骨牌能推到的最远的骨牌的编号。

二分这个骨牌**自己**能推到的最远的骨牌，设这个骨牌为 $j$ ，则 $to_i=\max(\forall i\le k\le j:to_k)$ ，显然可以用线段树维护。

看起来比其他题解菜很多但是 **又 不 是 不 能 A**

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN=100005;
int n;
struct point{
	int pos,h,id;
	bool operator<(point b){
		return pos<b.pos;
	}
}tmp[MAXN];
int a[MAXN],h[MAXN];
int to[MAXN];
int ans[MAXN];

struct Segment_Tree{
	// const int INF=0x3f3f3f3f;
	struct node{
		int l,r,len;
		int add,v,mx;
	}st[MAXN*4];
	
	void build(int p,int l,int r){
		st[p].l=l;st[p].r=r;
		st[p].len=r-l+1;
		if (l==r){
			// st[p].v=a[l];
			st[p].mx=0;
			return;
		}
		int mid=l+r>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		st[p].v=st[p<<1].v+st[p<<1|1].v;
		st[p].mx=max(st[p<<1].mx,st[p<<1|1].mx);
	}

	void spread(int p){
		// st[p<<1].v+=st[p].add*st[p<<1].len;
		// st[p<<1|1].v+=st[p].add*st[p<<1|1].len;
		st[p<<1].add+=st[p].add;
		st[p<<1|1].add+=st[p].add;
		st[p<<1].mx+=st[p].add;
		st[p<<1|1].mx+=st[p].add;
		st[p].add=0;
	}

	void change(int p,int l,int r,int c){
		if (l<=st[p].l&&st[p].r<=r){
			// st[p].v+=c*st[p].len;
			st[p].add+=c;
			st[p].mx+=c;
			return;
		}
		spread(p);
		int mid=st[p].l+st[p].r>>1;
		if (l<=mid) change(p<<1,l,r,c);
		if (r>mid) change(p<<1|1,l,r,c);
		// st[p].v=st[p<<1].v+st[p<<1|1].v;
		st[p].mx=max(st[p<<1].mx,st[p<<1|1].mx);
	}

	int query_max(int p,int l,int r){
		if (l<=st[p].l && st[p].r<=r)
			return st[p].mx;
		spread(p);
		int mid=st[p].l+st[p].r>>1,ans=0;
		if (l<=mid) ans=query_max(p<<1,l,r);
		if (r>mid) ans=max(ans,query_max(p<<1|1,l,r));
		return ans;
	}
}seg;

int main()

{
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>tmp[i].pos>>tmp[i].h;
		tmp[i].id=i;
	}

	sort(tmp+1,tmp+1+n);

	for (int i=1;i<=n;i++){
		a[i]=tmp[i].pos;
		h[i]=tmp[i].h;
	}

	seg.build(1,1,n);
	to[n]=n;
	ans[tmp[n].id]=1;
	seg.change(1,n,n,n);
	for (int i=n-1;i>=1;i--){
		int l=i,r=n,goal=a[i]+h[i]-1;
		while (l<=r){
			int mid=l+r>>1;
			if (a[mid]<=goal) l=mid+1;
			else r=mid-1;
		}
		to[i]=max(i,seg.query_max(1,i,r));
		seg.change(1,i,i,to[i]);
		ans[tmp[i].id]=to[i]-i+1;
	}

	for (int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

这个题目的思想是把这些多米诺骨牌变成一颗数，使得节点 i 是节点 j 的一个前辈当且仅当骨牌 i 倒了会导致 j 倒。这样这些骨牌就退化成一个森林，一个骨牌的答案就是它对应子树的大小。

如何退化成一个森林就不多讲了，应为更 AT5369 一模一样，可以参考这里：[博客链接](https://b3s23life.blog.luogu.org/solution-at5369)

代码，去掉特长的template

```cpp
// writer: w33z8kqrqk8zzzx33
vector<pair<int, pii>> domino;
priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> pq;
vector<int> elist[100005];
int sz[100005];

int dfs(int u) {
	sz[u] = 1;
	for(int& v:elist[u]) sz[u] += dfs(v);
	return sz[u];
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; gi(n);
	rep(i, n) {
		int x, h; gi(x); gi(h);
		domino.pb({x, {h, i}});
	}
	sort(all(domino));
	for(int i=n-1; i>=0; i--) {
		while(pq.size() && pq.top().fi < domino[i].fi+domino[i].se.fi) {
			elist[domino[i].se.se].pb(pq.top().se.se);
			pq.pop();
		}
		pq.push(domino[i]);
	}
	while(pq.size()) {
		dfs(pq.top().se.se);
		pq.pop();
	}
	rep(i, n) {
		if(i) pc(' ');
		print(sz[i]);
	}
}

```


---

## 作者：万弘 (赞：0)

~~好奇怪啊,跟其它题解不一样~~

考虑$i$倒下后,满足$x_i<x_j\le x_i+h_i-1$的$j$都会倒下,而$j$倒下又会导致之后的骨牌倒下,即$i$的计算依赖于$j$的计算.

因此,将骨牌按$x$递增排序,并从大到小处理(可以顺便离散化一下).  
记$f(i)$表示(排序后)骨牌$i$倒下后能压到的最远横坐标.注意到对于$j>i$的$f(j)$已经算好,那么有
$$f(i)=\max\{x_i+h_i-1,\max_{x_i<x_j\le x_i+h_i-1} f(j)\}$$

这玩意就是个单点修改,,区间max.线段树即可维护.  
有趣的是,对于$k< i,f(k)$还没有被计算,如果将其初始化为-INF,则有
$$\max_{x_j\le x_i+h_i-1} f(j)=\max_{x_i<x_j\le x_i+h_i-1} f(j)$$

变成了单点修改,前缀max.树状数组即可维护.  
时间复杂度$\mathcal O(n \log n)$

通过$f$推出原答案,不用我多说了吧.
```cpp
#define MAXN 200011
ll n;
struct BIT
{
    ll t[MAXN];
    void build(ll n)//初始化为-INF
    {
    	for(ll i=1;i<=n;++i)t[i]=-INF;
	}
    #define lowb (i&-i)
    void modify(ll i,ll k)
    {
        while(i<=n)umax(t[i],k),i+=lowb;
    }
    ll Qmax(ll i)
    {
        ll res=-INF;
        while(i)umax(res,t[i]),i-=lowb;
        return res;
    }
}t;
struct one
{
    ll x,h,dex;
    bool operator <(const one& t)
    const
    {
        return x<t.x;
    }
}a[MAXN];
ll fx[MAXN],ans[MAXN];
ll place(ll val)
{
    return std::upper_bound(fx+1,fx+n+1,val)-fx;
}

int main()
{
    n=read();
    t.build(n);
    for(ll i=1;i<=n;++i)a[i].x=fx[i]=read(),a[i].h=read(),a[i].dex=i;
    std::sort(fx+1,fx+n+1),std::sort(a+1,a+n+1);
    for(ll i=n;i;--i)
    {
    	ll x=max(t.Qmax(place(a[i].x+a[i].h-1)-1),a[i].x+a[i].h-1);//求f(i)
    	ans[a[i].dex]=place(x)-i;
    	t.modify(i,x);
    }
    for(ll i=1;i<=n;++i)printf("%lld ",ans[i]);
    return 0;
}
```

---

