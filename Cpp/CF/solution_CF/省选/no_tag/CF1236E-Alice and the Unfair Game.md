# Alice and the Unfair Game

## 题目描述

Alice is playing a game with her good friend, Marisa.

There are $ n $ boxes arranged in a line, numbered with integers from $ 1 $ to $ n $ from left to right. Marisa will hide a doll in one of the boxes. Then Alice will have $ m $ chances to guess where the doll is. If Alice will correctly guess the number of box, where doll is now, she will win the game, otherwise, her friend will win the game.

In order to win, Marisa will use some unfair tricks. After each time Alice guesses a box, she can move the doll to the neighboring box or just keep it at its place. Boxes $ i $ and $ i + 1 $ are neighboring for all $ 1 \leq i \leq n - 1 $ . She can also use this trick once before the game starts.

So, the game happens in this order: the game starts, Marisa makes the trick, Alice makes the first guess, Marisa makes the trick, Alice makes the second guess, Marisa makes the trick, $ \ldots $ , Alice makes $ m $ -th guess, Marisa makes the trick, the game ends.

Alice has come up with a sequence $ a_1, a_2, \ldots, a_m $ . In the $ i $ -th guess, she will ask if the doll is in the box $ a_i $ . She wants to know the number of scenarios $ (x, y) $ (for all $ 1 \leq x, y \leq n $ ), such that Marisa can win the game if she will put the doll at the $ x $ -th box at the beginning and at the end of the game, the doll will be at the $ y $ -th box. Help her and calculate this number.

## 说明/提示

In the first example, the possible scenarios are $ (1, 1) $ , $ (1, 2) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (3, 2) $ , $ (3, 3) $ .

Let's take $ (2, 2) $ as an example. The boxes, in which the doll will be during the game can be $ 2 \to 3 \to 3 \to 3 \to 2 $

## 样例 #1

### 输入

```
3 3
2 2 2
```

### 输出

```
7```

## 样例 #2

### 输入

```
5 2
3 1
```

### 输出

```
21```

# 题解

## 作者：MyukiyoMekya (赞：11)

翻了下官方题解发现一个超 nb 的做法。

分别对每个起始点 $x$ 求其能到达的左右边界这个贪心我就不多说了，主要怎么求边界。

思路大概就是搞张 $(m+1)\times n$ 的图 ，表示第 $i$ 个操作的时刻，$(i,a_i)$ 是不能走的。

然后每个操作的时刻，只能选择向下、向左下、向右下走。

$m=3,a=\{2,2,2\}$ 的图大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/xkr59dg3.png)

这里以左边界为例，肯定是能往左走就往左走，主要看右边那 3、4、5。

设 $f(i,j)$ 表示第 $i$ 次操作，起始点为 $(0,j)$ ，一直贪心往左边界走，需要“碰”多少次壁（也就是只能往下走），我们考虑这个 $(3,2)$ 产生了什么影响，一是让起始点为 $(0,5)$ 的“碰”了一次壁，二是让起始点为 $(0,5)$ 的和起始点为 $(0,6)$ 的在 $i$ 之后的路线重合，也就是说后面 $(0,6)$ 怎么走 $(0,5)$ 就怎么走，所以可以推导出一个递推柿子：$f(i,a_i+i)=f(i+1,a_i+i+1)+1$ ，其余直接从 $i+1$ 继承过来。可以发现，第一维没用，直接倒着转移即可。

时空复杂度 $\mathcal O(n+m)$。

```cpp
// This code wrote by chtholly_micromaker(Myukiyomekya)
#include <bits/stdc++.h>
const int MaxN=1e5+50;
int f[MaxN<<1],a[MaxN],n,m;
signed main(void)
{
	std::scanf("%d%d",&n,&m);
	if(n==1)return std::puts("0"),0;
	for(int i=1;i<=m;++i)std::scanf("%d",&a[i]);
	int N=std::max(n,m);
	for(int i=m;i;--i)f[a[i]+i]=f[a[i]+i+1]+1;
	long long ans=0;
	for(int i=1;i<=n;++i)ans+=std::min(i,m+2-f[i]);
	std::memset(f,0,sizeof(f));
	for(int i=m;i;--i)f[a[i]-i+N]=f[a[i]-i-1+N]+1;
	for(int i=1;i<=n;++i)ans+=std::min(n-i+1,m+2-f[i+N]);
	std::printf("%lld\n",ans-n);
	return 0;
}
```



---

## 作者：daniEl_lElE (赞：2)

先找性质，对于任意 $x$，合法的 $y$ 一定是一段连续的。

对于每个前缀，合法的 $y$ 一定是一个连续段缺掉一个位置。于是，归纳即可证明。

考虑分开维护左右端点。

考虑左端点（右端点类似），于是我们需要维护的变成全局 $-1$，全局将等于 $a_i$ 的数 $+1$。

容易发现每一个时刻左端点一定是单调不降的。于是可以二分找到第一个 $a_i$ 与最后一个 $a_i$，问题变成了区间 $+1$。线段树维护即可。复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define double long double
using namespace std;
struct sgt{
	int maxv[400005],minv[400005],lzt[400005];
	void pushdown(int i){
		maxv[i*2]+=lzt[i];
		minv[i*2]+=lzt[i];
		lzt[i*2]+=lzt[i];
		maxv[i*2+1]+=lzt[i];
		minv[i*2+1]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void pushup(int i){
		maxv[i]=max(maxv[i*2],maxv[i*2+1]);
		minv[i]=min(minv[i*2],minv[i*2+1]);
	}
	void build(int i,int l,int r){
		lzt[i]=0;
		if(l==r){
			maxv[i]=minv[i]=l;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		pushup(i);
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			maxv[i]+=cg;
			minv[i]+=cg;
			lzt[i]+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		pushup(i);
	}
	int qfirst(int i,int l,int r,int k){
		if(l==r){
			if(maxv[i]!=k) return 1e8; 
			return l;
		}
		pushdown(i);
		if(maxv[i*2]<k) return qfirst(i*2+1,mid+1,r,k);
		return qfirst(i*2,l,mid,k);
	}
	int qlast(int i,int l,int r,int k){
		if(l==r){
			if(maxv[i]!=k) return -1;
			return l;
		}
		pushdown(i);
		if(minv[i*2+1]>k) return qlast(i*2,l,mid,k);
		return qlast(i*2+1,mid+1,r,k);
	}
	int cal(int i,int l,int r){
		if(l==r){
			return maxv[i];
		} 
		pushdown(i);
		return cal(i*2,l,mid)+cal(i*2+1,mid+1,r);
	}
}tree;
signed main(){
	int n,m; cin>>n>>m;
	if(n==1){
	    cout<<0;
	    return 0;
	}
	int a[m+1];
	for(int i=1;i<=m;i++) cin>>a[i];
	int ans=0,l,r;
	tree.build(1,1,n);
	for(int i=1;i<=m;i++){
		tree.change(1,1,n,1,n,-1);
		int l,r;
		l=tree.qfirst(1,1,n,0),r=tree.qlast(1,1,n,0);
		if(l<=r) tree.change(1,1,n,l,r,1);
		l=tree.qfirst(1,1,n,a[i]),r=tree.qlast(1,1,n,a[i]);
		if(l<=r) tree.change(1,1,n,l,r,1); 
	}
		tree.change(1,1,n,1,n,-1);
		l=tree.qfirst(1,1,n,0),r=tree.qlast(1,1,n,0);
		if(l<=r) tree.change(1,1,n,l,r,1);
	ans-=tree.cal(1,1,n);
	tree.build(1,1,n);
	for(int i=1;i<=m;i++){
		tree.change(1,1,n,1,n,1);
		int l,r;
		l=tree.qfirst(1,1,n,n+1),r=tree.qlast(1,1,n,n+1);
		if(l<=r) tree.change(1,1,n,l,r,-1);
		l=tree.qfirst(1,1,n,a[i]),r=tree.qlast(1,1,n,a[i]);
		if(l<=r) tree.change(1,1,n,l,r,-1); 
	}
		tree.change(1,1,n,1,n,1);
		l=tree.qfirst(1,1,n,n+1),r=tree.qlast(1,1,n,n+1);
		if(l<=r) tree.change(1,1,n,l,r,-1);
	ans+=tree.cal(1,1,n);
	cout<<ans+n;
	return 0;
} 

```

---

## 作者：devout (赞：2)

考虑枚举起点 $x$，那么最后合法的 $y$ 显然应该是连续的一段 $l\cdots r$

如果没有询问的话，显然应该是 $[x-m-1,x+m+1]$

考虑有询问的时候，我们有可能会在一个地方卡住

用 $(t,i)$ 表示时间 $t$ 在 $i$ 这个点

那么如果往右走， $(t,i)$ 会在最小的 $(t^\prime,j),t^\prime-j=t-i$ 卡住

往左走也是同理的

发现对于一个询问 $a_i$，我们要么卡在左边，要么卡在右边

所以我们把他拆成两个点 $i$ 和 $i+m$

相应的我们可以二分找到连边的点，这样我们可以建出来一张有向图

发现这张图上连边都是从时间小的往时间大的连，所以是一张 DAG

我们在 DAG 上维护一下每个位置最小能走到哪里，最大能走到哪里

查询 $x$ 为起点的答案的时候我们首先找到他第一次被卡住的位置，然后直接查询答案即可，如果没被卡住就是 $[x-m-1,x+m+1]$

注意 $n=1$ 的情况需要特判一下。。。

$\mathcal O(n\log n)$

当然这道题只需要开个指针正反扫一遍就可以得到一个 $\mathcal O(n)$ 的做法，然而写完才发现（

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m;
int a[N]; 
int head[N<<1],cnt;
int L[N<<1],R[N<<1];
int inde[N<<1],tpx[N<<1],tpxu;
// i 被卡在第 i 个询问的左边
// i+m 被卡在第 i 个询问的右边 
vector<int> T1[N<<1],T2[N<<1];
ll ans;

struct Edge{
	int to,next;	
}e[N<<2];

void add(int x,int y){
	inde[y]++;
	e[++cnt]=(Edge){y,head[x]},head[x]=cnt;	
}

int main()
{
	memset(L,0x3f,sizeof(L));
	memset(head,-1,sizeof(head));
	read(n),read(m);
	Rep(i,1,m){
		read(a[i]);	
		T1[a[i]-i+n].push_back(i);
		T2[a[i]+i].push_back(i);
	}
	if(n==1)return puts("0"),0;
	Rep(i,1,m){
		int realpos=a[i]-1;
		if(!realpos)continue;
		int x=realpos-i+n;
		int pos=upper_bound(T1[x].begin(),T1[x].end(),i)-T1[x].begin();
		if(pos<T1[x].size())add(i,T1[x][pos]);
		x=realpos+i;
		pos=upper_bound(T2[x].begin(),T2[x].end(),i)-T2[x].begin();
		if(pos<T2[x].size())add(i,T2[x][pos]+m);
	}
	Rep(i,1,m){
		int realpos=a[i]+1;
		if(realpos>n)continue;
		int x=realpos-i+n;
		int pos=upper_bound(T1[x].begin(),T1[x].end(),i)-T1[x].begin();
		if(pos<T1[x].size())add(i+m,T1[x][pos]);
		x=realpos+i;
		pos=upper_bound(T2[x].begin(),T2[x].end(),i)-T2[x].begin();
		if(pos<T2[x].size())add(i+m,T2[x][pos]+m);	
	}
	queue<int> q;
	Rep(i,1,2*m)if(!inde[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		tpx[++tpxu]=u;
		RepG(i,u){
			int v=e[i].to;
			inde[v]--;
			if(!inde[v])q.push(v);
		}
	}
	_Rep(i,tpxu,1){
		int u=tpx[i];
		RepG(i,u){
			int v=e[i].to;
			if(v<=m)R[u]=max(R[u],R[v]);
			else L[u]=min(L[u],L[v]);
		}
		if(L[u]>n)
			if(u<=m)L[u]=max(a[u]-1-(m-u),1);
			else L[u]=max(a[u-m]+1-(m-(u-m)),1);
		if(!R[u])
			if(u<=m)R[u]=min(a[u]-1+(m-u),n);
			else R[u]=min(a[u-m]+1+(m-(u-m)),n);	
	}
	Rep(i,1,n){
		int x=i+n;
		int ansl=i,ansr=i;
		if(T1[x].size()){
			int pos=T1[x][0];
			ansr=min(R[pos]+1,n);
		}
		else ansr=min(i+m+1,n);
		x=i;
		if(T2[x].size()){
			int pos=T2[x][0];
			ansl=max(L[pos+m]-1,1);	
		}
		else ansl=max(i-m-1,1);
		ans+=ansr-ansl+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：zyh_helen (赞：0)

[这道题背后的故事](https://www.luogu.com.cn/article/2vrchchx)

下面来分享一个不同的做法。

---

分别对每个起始点 $x$ 求其能到达的左右边界这个贪心别的题解已经说了，考虑求边界。

我们首先考虑不管这些操作的情况，那么左端点和右端点是可以在开始的时候就算出来的，但是每次遇到一个操作，在那个位置向右（左）走的操作就会被挡住，然后那个位置对应的右（左）端点就会往左（右）走一步。

这样的话，一个右（左）端点就可能对应多个起始点，但一个起始点只能对应一个右（左）端点，考虑那起始点存进其对应的右（左）端点的集合里，每次遇到向左（右）合并两个端点的集合，共需合并 $m$ 次，我们此时发现可以使用启发式合并（每次把小的合进大的），容易证明复杂度是 $O(n\log n)$。

---
代码中用了 set 来实现集合，复杂度是 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
//#include<Windows.h>
#define int long long
//#define ll long long
//#define double long double
#define fi first
#define se second
//#define ls t[p].l
//#define rs t[p].r
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 4e5 + 10, inf = 1e9, M = 2e5;
//const double eps = 1e-16;
const int mod = 1e9 + 7;
//const int mod;
//const int AQX = 9;
mt19937 rnd(time(0) ^ clock());
int random(int l, int r){
	return rnd() % (r - l + 1) + l;
}
const int offset = 101, offset2 = 103;
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/
//struct Graph{
//	int head[N], tot;
//	struct edge{
//		int t, f;
//		int d, fa;
//		int next;
//	}e[N << 1];
//	void edge_add(int u, int v, int w = 0){
//		e[++tot].next = head[u];
//		e[tot].t = v;
//		e[tot].d = w;
//		e[tot].f = u;
//		head[u] = tot;
//	}
//	void clear(int n){
//		for(int i = 1;i <= tot;i++)e[i].t = e[i].f = e[i].d = e[i].next = 0;
//		for(int i = 1;i <= n;i++)head[i] = 0;
//		tot = 0;
//	}
//}g1, g2;
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

int n, m, a[N], b[N], c[N], d[N];
set<int>mx[N], mn[N];
signed main(){
	cin >> n >> m;
	if(n == 1){
		cout << 0 << endl;
		return 0;
	}
	for(int i = -m;i <= n + m + 1;i++)a[i + M] = i + M, b[i + M] = i + M;
	for(int i = 1;i <= n;i++)mx[i + m + M + 1].insert(i), mn[i - m + M - 1].insert(i);
	for(int i = 1;i <= m;i++){
		int x;
		scanf("%lld", &x);
		int p = x + m - i + M + 1;
//		cout << p << " " << a[p] << endl;
		if(mx[a[p]].size() < mx[a[p - 1]].size()){
			for(int x : mx[a[p]])mx[a[p - 1]].insert(x);
			mx[a[p]].clear();
		}
		else {
			for(int x : mx[a[p - 1]])mx[a[p]].insert(x);
			mx[a[p - 1]].clear();
			swap(a[p], a[p - 1]);
		}
		
		p = x - m + i + M - 1;
		if(mn[b[p]].size() < mn[b[p + 1]].size()){
			for(int x : mn[b[p]])mn[b[p + 1]].insert(x);
			mn[b[p]].clear();
		}
		else {
			for(int x : mn[b[p + 1]])mn[b[p]].insert(x);
			mn[b[p + 1]].clear();
			swap(b[p], b[p + 1]);
		}
//		for(int i = -m;i <= n + m;i++){
//			if(mx[a[i + M]].size()){
//				cout << i << endl;
//				for(int x : mx[a[i + M]])printf("%lld ", x);
//				putchar('\n');
//			}
//		}
	}
	for(int i = -m;i <= n + m + 1;i++){
		for(int x : mx[a[i + M]]){
			c[x] = min(i, n);
		}
		for(int x : mn[b[i + M]]){
//			cout << x << endl;
			d[x] = max(i, 1ll);
		}
	}
	int ans = 0;
	for(int i = 1;i <= n;i++)ans += c[i] - d[i] + 1;
	cout << ans << endl;
	return 0;
}

---

