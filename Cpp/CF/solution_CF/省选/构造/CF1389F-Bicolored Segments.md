# Bicolored Segments

## 题目描述

给你 $n$ 条线段 $[l_1, r_1], [l_2, r_2], \ldots, [l_n, r_n]$。线段有两种颜色，第 $i$ 条线段的颜色为 $t_i$。

我们称一对线段 $i, j$ 是不好的，当且仅当以下两个条件同时满足：

- $t_i \neq t_j$；
- 线段 $[l_i, r_i]$ 和 $[l_j, r_j]$ 相交、相嵌或相切。换句话说，存在这样一个整数 $x$，使得 $x \in [l_i, r_i]$ 且 $x \in [l_j, r_j]$。

请问最多可以选择给定的这些线段中的多少条，使得选择的线段中没有任何一对线段是不好的。

## 样例 #1

### 输入

```
3
1 3 1
4 6 2
2 5 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
5 8 1
1 3 2
3 4 2
6 6 1
2 10 2```

### 输出

```
4```

## 样例 #3

### 输入

```
7
19 20 1
13 15 2
6 11 2
4 10 1
14 17 1
13 13 2
5 9 1```

### 输出

```
5```

# 题解

## 作者：George1123 (赞：13)

**到蒟蒻的博客园里来赞赞文章 $\to $ [$\tt George1123$](https://www.cnblogs.com/Wendigo/p/13406024.html)**

---
## 题面

> [CF1389F Bicolored Segments](https://www.luogu.com.cn/problem/CF1389F)

> 给 $n$ 条线段 $[l_i,r_i]$，每条有个颜色 $t_i\in\{0,1\}$，求最多选出多少条线段，使没有不同颜色的线段相交。

> 数据范围：$1\le n\le 2\cdot 10^5$，$1\le l_i\le r_i\le 10^9$。

---
## 蒟蒻语

昨天蒟蒻打 CF，发挥得不错，迷惑回橙。但是蒟蒻没做出这题，赛后想了好久感觉这题很奇妙，于是蒻蒻地来写篇题解。

---
## 蒟蒻解一

线段树维护 dp。

先将每条线段 $l_i,r_i$ 离散化，坐标范围为 $[0,cnt]$。

设 $f(i,j,k)$ 表示看了 $[0,i]$，$[j+1,i]$ 的线段颜色都为 $k$ 的最多线段数。

$$j<i:f(i,j,k)=f(i-1,j,k)+\sum_{x=1}^{n}[l_x>j][r_x=i]$$

$$f(i,i,k)=\max[\max_{j=0}^{i-1}f(i,j,!k),\max_{j=0}^{i-1}f(i,j,k)]$$

那么答案是 $\max_{j=0}^{cnt}f(cnt,j,0/1)$。

设 $ca_i$ 这个 vector 存放 $r_x=i$ 的 $x$。

所以可以用一个线段树代替 $j$ 维，把 $i$ 维滚掉，实现上述dp。

**时间复杂度 $\Theta(n\log n)$。**

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
#define be(a) a.begin()
#define en(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;
 
//Data
const int N=2e5,M=(N<<1)+1;
int n,l[N],r[N],t[N],cnt,b[M],ans;
vector<int> ca[M];
 
//Segmenttree
const int T=M<<2;
#define lk k<<1
#define rk k<<1|1
struct Segmenttree{ //线段树，下标为坐标，维护区间加、全局最大值
    int mx[T],mk[T];
    void pushup(int k){mx[k]=max(mx[lk],mx[rk]);}
    void pm(int k,int v){mk[k]+=v,mx[k]+=v;}
    void pushdown(int k){if(mk[k]) pm(lk,mk[k]),pm(rk,mk[k]),mk[k]=0;}
    void fix(int x,int y,int v,int k,int l,int r){
        if(x<=l&&r<=y) return pm(k,v);
        pushdown(k);
        int mid=(l+r)>>1;
        if(mid>=x) fix(x,y,v,lk,l,mid);
        if(mid<y) fix(x,y,v,rk,mid+1,r);
        pushup(k);
    }
    int Mx(){return mx[1];}
    void Print(int k,int l,int r){
        if(l==r){cout<<mx[k]<<' ';return;}
        pushdown(k);
        int mid=(l+r)>>1;
        Print(lk,l,mid),Print(rk,mid+1,r);
    }
}g[2];
 
//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>l[i]>>r[i]>>t[i],--t[i];
        b[cnt++]=l[i],b[cnt++]=r[i];
    }
    b[cnt++]=0,sort(b,b+cnt),cnt=unique(b,b+cnt)-b;
    for(int i=0;i<n;i++){
        l[i]=lower_bound(b,b+cnt,l[i])-b;
        r[i]=lower_bound(b,b+cnt,r[i])-b;
        ca[r[i]].pb(i);
    }
    for(int i=1;i<cnt;i++){
        for(int x:ca[i]) g[t[x]].fix(0,l[x]-1,1,1,0,cnt);
        g[0].fix(i,i,g[1].Mx(),1,0,cnt),g[1].fix(i,i,g[0].Mx(),1,0,cnt);//这么写也是可以的
    }
    cout<<max(g[0].Mx(),g[1].Mx())<<'\n';
    return 0;
}
```
---
## 蒟蒻解二

萌新初学 OI 的时候，有一个贪心问题：求最多线段互不相交。做法是右端点再左端点双关键字排序，然后贪心取舍一下。

这题可以同样地骚操作：

初始化答案为 $n$。用两个 multiset 记录两种颜色分别选了哪些线段。

顺序枚举排序了的线段，如果没有**选了的线段**与当前线段异色并重合，那么蒟蒻们可以很开心地选上这条线段。

否则把**右端点在当前线段左端点右边并且最近的异色线段**从 multiset 中删除，不往 multiset 中加入当前线段，把答案 $-1$，表示一个对抗抵消的过程。

比如加了一条 $0$ 线段，然后再加一条 $1$ 线段与它抵消。这时如果来 $2$ 条 $1$ 线段，相当于选了 $3$ 条 $1$ 线段；如果来 $2$ 条 $0$ 线段，相当于选了 $3$ 条 $0$ 线段。

这种思想类似求序列众数时的对抗抵消选举和模拟网络流反悔推流。

**时间复杂度 $\Theta(n\log n)$。**

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
#define be(a) a.begin()
#define en(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=2e5;
int n,ans;
struct S{int l,r,t;}a[N];
multiset<int> g[2];

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n,ans=n;
    for(int i=0;i<n;i++)
        cin>>a[i].l>>a[i].r>>a[i].t,--a[i].t;
    sort(a,a+n,[&](const S p,const S q){return p.r==q.r?p.l<q.l:p.r<q.r;});
    for(int i=0;i<n;i++)
        if(g[!a[i].t].lower_bound(a[i].l)==en(g[!a[i].t])) g[a[i].t].insert(a[i].r);
        else ans--,g[!a[i].t].erase(g[!a[i].t].lower_bound(a[i].l));
    cout<<ans<<'\n';
    return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：huayucaiji (赞：6)

拿出单词小本本，我们来记一个单词：  
[embed](https://fanyi.baidu.com/?aldtype=85#en/zh/embed)：嵌入，本题中意思就是一个区间被另一个区间所包含。

回归正题，我在写这篇题解时看了洛谷上[一篇和我思路差不多的大佬写的题解](https://www.luogu.com.cn/blog/Wendigo/solution-cf1389f)，他的线段树优化DP写的不错的，大家可以看看，但是我觉得他的解法二不太清晰，特别是那个“对抗抵消”。可能蒟蒻不太能理解qwq，这里换一个角度在重新讲一下。

我们这样想，既然有两种不同颜色的区间，就代表我们可以理解把它们为一个二分图的节点。如果你愿意，我们再把所有互为“不好的”区间连边。我们就得到了一个~~看着不错~~二分图。举个例子，我们题目中的样例二构图：

**样例二**：

```plain
5
5 8 1
1 3 2
3 4 2
6 6 1
2 10 2
```

**我们构成的二分图**：

![F](https://cdn.luogu.com.cn/upload/image_hosting/4qlyx6pm.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

我们再看这个图，是不是有一点感觉了，我们要求的正是这个图的最大点独立集。求最大点独立集，我们就要求最大匹配。这两个概念不知道的同学可以上网搜。我们令最大点独立集的答案为 $x$，最大匹配的答案为 $y$。我们有 $x+y=n$。$n$ 就是点的个数。~~证明略~~我们的问题成功转化为这个二分图求最大匹配。

~~我相信不会有人想着真的把图建出来用网络流求解吧，不会吧，不会吧。~~  
~~咳咳，我一开始就这么想的~~

不扯远了，但确实我们的第一反应应该是网络瘤，毕竟是它的好伙伴二分图嘛。但是我们建图的时间复杂度就是 $O(n^2)$，Dinic 做二分图的时间复杂度 $O(m\sqrt{n})$，显然爆炸。我们要像一种高效的方法才行。

我们先和上面的那篇 blog 一样，按每个区间的右端点为第一关键字排序，搞两个 multiset 记录我们选择了哪些区间。接下来的操作还是一样，但是我们的解释不太一样。我们要求的是最大匹配，**如果我们在异色的 multiset 中，存在与我们现在考虑的这个区间形成“不好区间”的区间的话，我们就选择这两个点之间的这条边作为最大匹配中的一条边，把那个 muliset 中的点给抹掉，并且现在的这个区间也不加入到 multiset 中，因为我们这两个点不能再出现在最大匹配的边里了，这是最大匹配的定义要求的**。否则这个区间我们可以加入到 multiset 中。这样解释应该更清楚一些吧（自认为）。也就不用去理解“对抗抵消”了。

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=2e5+10; 

int n=0,ans=0;
struct segment {
	int l,r,col;
	
	const operator < (const segment& y) {
		return r<y.r;
	}
}s[maxn];

multiset<int> sel[2];

signed main() {
	n=read();
	for(int i=1;i<=n;i++) {
		s[i].l=read();
		s[i].r=read();
		s[i].col=read()-1;
	}
	
	sort(s+1,s+n+1);
	
	ans=n;
	for(int i=1;i<=n;i++) {
		if(sel[1-s[i].col].lower_bound(s[i].l)!=sel[1-s[i].col].end()) {
			ans--;
			sel[1-s[i].col].erase(sel[1-s[i].col].lower_bound(s[i].l));
		}
		else {
			sel[s[i].col].insert(s[i].r);
		}
	}
	
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：MuYC (赞：4)

#### 前言：

前置知识：线段树(维护区间修改，区间查询最大值，单点覆盖) + $dp$

这道题目挺有意思的，在经过许多删改后，写了一份比较容易看懂的代码。

这篇题解我将提供两个版本，一种是详细版（给完全没有思路的同学看的，位于文末,有思路讲解，一步一步分析题目）

另外一种是精简版，大概的简述做法，您可以根据自己的情况选择看哪一种。

#### 题意转述：

```plain
每条线段为黑色或白色。我们称一对线段不好当且仅当颜色不同且有公共点。

求一个最大的子集(包含的线段最多)使得不存在不好的线段对。
```

### 精简版:

通过将线段按照右端点从小到大排序依次加入去除后效性。同时要离散化。

+ 状态设立：$dp[i][j][0/1]$ 

+ 状态转移方程:(假设当前处理到的线段是线段 $i$)

假设当前这条线段的左端点是 $l_i$ 右端点是 $r_i$。

（因为考虑到黑白是同样的做法，就假定当前这条线段是黑的吧，对应 $dp[i][r_i][1]$）

+ 不选当前线段:

$dp[i][r_i][1] = dp[i - 1][r_{i-1}][1]$

+ 选当前线段:

假设上一条被选择的白色线段的右端点是 $r_j$

根据题目的意思，左右端点都在 $[r_j + 1$,$r_i]$ 这里面的所有黑色线段显然是都可以选择的。

状态转移方程:$dp[i][r_i][1] = max(dp[k][r_k][0] + Clac(r_k + 1,r_i))$

ps.这里的 $k < i$ 并且 $r_k < l_i$(其右端点不能在这条线段的左端点及后面),$Clac(r_k + 1,r_i)$表示左右端点都在 $[r_k + 1,r_i]$ 这段区间内的黑色线段。

考虑到如何提前计算$Clac(r_k + 1,r_i)$,进行状态转移前就先将 $r_k < l_i$ 的所有 $dp[k][r_k][0]$ 都加上一个 $1$。

然后方程就变成了$dp[i][r_i][1] = max(dp[k][r_k][0])$($k < i$ 并且 $r_k < l_i$)

发现要实现区间加法，区间找最大值，单点修改，使用线段树维护即可。

#### Code

```cpp
// Memory Limit: 250 MB
// Time Limit: 2000 ms

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 50;
int n;
map <int,int> mp;
int N[MAXN * 2];

inline int read() {
	int x = 0 , flag = 1;
	char ch = getchar() ;
	for( ; ch > '9' || ch < '0' ; ch = getchar()) ;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

struct Segment {
	int l,r,ty;
	void init(){l = read() , r = read() , ty = read() ;return ;}
	bool operator < (const Segment &P) { return r < P.r; }//重载了运算符
} S[MAXN];

struct SegmentTree { //两个线段树，一个是维护黑色的，为线段树B，另外一个维护白色的，为线段树W
	int Max[MAXN * 8],laz[MAXN * 8],L[MAXN * 8],R[MAXN * 8];
	void build(int x,int l,int r) {//建树
		L[x] = l , R[x] = r;
		Max[x] = laz[x] = 0;
		if(l == r) return ;
		int mid = (l + r) >> 1;
		build(x << 1 , l , mid);
		build(x << 1 | 1 , mid + 1 , r);
		return ;
	}
	void update(int x,int k) {
		laz[x] += k , Max[x] += k;
		return ;
	}
	void pushdown(int x) {
		if(laz[x] == 0) return ;
		update(x << 1 , laz[x]);
		update(x << 1 | 1 , laz[x]);
		laz[x] = 0;
		return ;
	}
	int GetMax(int x,int l,int r) {//区间最大值
		int M = 0;
		if(L[x] >= l && R[x] <= r) return Max[x];
		pushdown(x);
		int mid = (L[x] + R[x]) >> 1;
		if(l <= mid) M = max(M , GetMax(x << 1 , l , r) );
		if(r  > mid) M = max(M , GetMax(x << 1 | 1 , l , r) );
		return M;
	}
	void add(int x,int l,int r,int k) {//区间加法
		if(L[x] >= l && R[x] <= r) {
			update(x , k);
			return ;
		}
		pushdown(x);
		int mid = (L[x] + R[x]) >> 1;
		if(l <= mid) add(x << 1 , l , r , k);
		if(r  > mid) add(x << 1 | 1 , l , r , k);
		Max[x] = max(Max[x << 1] , Max[x << 1 | 1]);
		return ;
	}
	void change(int x,int pos,int k) { //单点修改
		if(L[x] == pos && R[x] == pos) {
			Max[x] = k;
			return ;
		}
		pushdown(x);
		int mid = (L[x] + R[x]) >> 1;
		if(pos <= mid) change(x << 1 , pos , k);
		else change(x << 1 | 1 , pos , k);
		Max[x] = max(Max[x << 1] , Max[x << 1 | 1]);
		return;
	}
} B,W;

void Discretization() {//离散化
	int len = 0;
	for(int i = 1 ; i <= n ; i ++) 
	N[++len] = S[i].l , N[++len] = S[i].r;
	sort(N + 1 , N + 1 + len);
	for(int i = 1 ; i <= len ; i ++) mp[N[i]] = i + 1;
   //因为S[i].l离散化后-1可能是0，所以我在离散化的时候就将每一个
   //S[i].l 以及S[i].r + 1 了，就是上面的mp[N[i]] = i + 1;
	for(int i = 1 ; i <= n ; i ++)
	S[i].l = mp[S[i].l] , S[i].r = mp[S[i].r];
	return ;
}

int main() {
	n = read();
	for(int i = 1 ; i <= n ; i ++) S[i].init();//读入而已，为了看起来简便就这么写了
	Discretization();//离散化
	sort(S + 1 , S + 1 + n);//按照右端点从小到大排序，重载了运算符
	B.build(1 , 1 , 2 * n + 1);
	W.build(1 , 1 , 2 * n + 1);
	for(int i = 1 ; i <= n ; i ++) {
		if(S[i].ty == 1) {//代表是白色
			B.add(1 , 1 , S[i].l - 1 , 1);//提前加上
			int Max = W.GetMax(1, 1 , S[i].r);//假设不选，求一个最大值
			int op = B.GetMax(1 , 1 , S[i].l - 1);//假设选择，求一个最大值
			W.change(1 , S[i].r , max(op,Max));//最后当前点就修改为选择以及不选择的max就行了
		}
		else {//否则是黑色，操作同上，只不过 "B"改成了"W"，"W"改成了"B"
			W.add(1 , 1 , S[i].l - 1 , 1);
			int Max = B.GetMax(1, 1 , S[i].r);
			int op = W.GetMax(1 , 1 , S[i].l - 1);
			B.change(1 , S[i].r , max(op,Max));
		}
	}
	cout << max(B.GetMax(1 , 1 , n * 2 + 1),W.GetMax(1 , 1 , n * 2 + 1));
	return 0;
}
```

### 详细版

#### 引入:

想必大家在初学贪心的阶段都做过这么一道题目：
```plain
从若干线段中选出若干条不相交的线段，求最多选出的线段数
```
本题其实就是由这个题目“进化”来的。

$Ask$：这道题还能按照原来的题目进行贪心吗？

$Answer$: 不能说完全一样吧，但是用到了一部分贪心思想。

#### 题目分析

要保证动态规划没有后效性。

一个非常显而易见的做法就是我们按照右端点从小到大加入就可以去除掉后效性，所以这个题目可以使用动态规划。

+ 状态的设置:

**我的思考过程**(也就是如何得出状态设置的)：

一维可以吗？

$dp[i]$ 表示前 $i$ 个后能获得的最多线段数?

这个显然不行，因为不能进行转移，我并不知道最后一个是放入的是黑色还是白色，以及它的右端点坐标是哪里。

二维可以吗？

$dp[i][j][0/1]$ 表示考虑前 $i$ 个， $j$ 表示最后一个放入的线段的右端点，$0/1$ 就表示最后放入的线段的颜色。

好像时间上过不去啊（空间上是没有问题的，因为第一维可以滚动掉，第二维可以进行离散化）。

**时间上的优化**

+ 从状态转移方程着手:

假设当前这条线段的左端点是 $l_i$ 右端点是 $r_i$。

+ 如果不选择当前线段:

$dp[i][r_i][0] = dp[i - 1][r_i][0] , dp[i][r_i][1] = dp[i - 1][r_i][1]$

+ 如果选择当前线段:


（因为考虑到黑白是同样的做法，就假定当前这条线段是黑的吧，对应 $dp[i][r_i][1]$）

那么我们就需要知道上一条被选择的白色线段的右端点是在哪一个位置，假设是 $r_j$

左右端点都在 $[r_j + 1$,$r_i]$ 这里面的所有黑色线段显然是都可以选择的。就很容易写出状态转移方程:

$dp[i][r_i][1] = max(dp[k][r_k][0] + Clac(r_k + 1,r_i))$

ps.这里的 $k < i$ 并且 $r_k < l_i$(其右端点不能在这条线段的左端点及后面)，$Clac(r_k + 1,r_i)$ 表示 左右端点都在 $[r_k + 1,r_i]$ 这段区间内的黑色线段。

时间复杂度瓶颈是在枚举所有的 $k < i$ 求 $max(dp[k][r_k][0] + Clac(r_k + 1,r_i))$ 的过程。

这里的 $Clac(r_k + 1 , r_i)$ 是跟 $r_k$ 有关的，这给我们带来了很大的麻烦，考虑如何使得其与 $r_k + 1$ 无关。

可以事先在转移之前将 $dp[k][r_k][0]$ 提前加上 $Clac(r_k + 1,r_i))$ 。

因为枚举的是 $k < i$ 并且 $r_k < l_i$ ，所以我们加入一条线段的时候就先将 $r_k < l_i$ 的所有 $dp[k][r_k][0]$ 都加上一个 $1$ 。

这样子 $dp$ 状态转移的时候只需要找 $max(dp[k][r_k][0])$($r_k < l_i$) ，这个方程是一个经典的状态转移，可以用单调队列/ 线段树优化。

但是考虑到我们要将 $r_k < l_i$ 的所有 $dp[k][r_k][0]$ 都加上一个 $1$ ，所以只能使用线段树。

然后将所有**做法转移到两棵线段树上**：

一棵线段树维护的是最后选择白色线段的 $dp$，另外一棵就维护最后选择黑色线段的 $dp$ 。

线段树中的节点 $[j,j]$ 就表示 $dp[i][j][0/1]$($i$ 的那一维在枚举的时候就滚动掉了 )

还是假设当前是处理黑色线段。

首先将白色的那棵对应的对应区间 $[1,l_i - 1]$ 全部加一(对应上面的做法就是将 $dp[k][r_k][0](r_k < l_i)$ 加一)。

如果是不选择的话，那么我们就无需修改黑线段树的状态，也就是当前黑线段树的全局最大值 $Max$ ，如果选择的话，实际上就是目前白线段树中 $[1,l_i - 1]$ 中的最大值。

取选择/不选择的最大值对于当前黑线段树上的点$[r_i,r_i]$ 进行单点修改。

将整个 $dp$ 完全用线段树来实现，最后的答案就是线段树中的最大值。

实现的操作为：区间加法，区间找最大值，单点修改。


---

## 作者：V1mnkE (赞：3)

[Link](https://codeforces.com/problemset/problem/1389/F)，太妙了太妙了。

题意就是选出一组区间，使其中的异色区间不能有交。

因为只有两种颜色，那么把有交的异色区间之间连一条边，就有了一张二分图，我们要求的就是其中的最大独立点集。

看一眼数据范围，$n\le 2\times 10^5$，而我们连边的复杂度为 $O(n^2)$，接受不了，所以不可以连边之后跑匈牙利直接求。

发现，把所有区间按右端点位置排序后，所有与同一个区间连有边的区间是连续的同色区间。可以分别记录**目前选出的两种颜色的区间**，当枚举到区间 $i$ 时，有两种可能：

若当前区间与任何已选区间没有交，那么答案加一，将当前区间的右端点插入集合。

若当前区间与已选异色区间有交，就将**与其有交的异色区间中最靠前的一个**删除，当前区间不加入集合。因为实际上这还是一个求最大独立点集的过程，当前区间与已选区间有连边，那这条边肯定是**最大匹配中的边**，此时那个已选的区间不能再与其他的区间有最大匹配中的边，这是由定义决定的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
struct data{
	int l,r,t;
	bool operator <(const data &x)const{
		return x.r>r;
	}
}a[maxn];
multiset<int>s[2];
int n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r>>a[i].t;
		a[i].t--;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(s[!a[i].t].lower_bound(a[i].l)==s[!a[i].t].end()){
			ans++;
			s[a[i].t].insert(a[i].r);
		}		
		else {
			s[!a[i].t].erase(s[!a[i].t].lower_bound(a[i].l));
//			ans--;
		}
	}
	cout<<ans;
}
```


---

## 作者：__3E24AC7002AD9292__ (赞：2)

萌新 VP 赛没场切的题。

因为 $t$ 只有两种，很显然可以把每个线段在图上建立节点，并将有重合的不同颜色线段对连边，跑二分图最大匹配。以上是我在场上想到的全部了。

事实上，可以把每个线段按右端点排序，并扫一遍每个线段：

- 若异色 `multiset` 中存储的线段与该线段均无交点，说明这个点暂无连边，可以直接判断存储的右端点与该线段左端点的关系，然后把这条线段加入对应同色的 `multiset`。
- 若有交点，需要去当前这个线段匹配掉有交点的线段，直接用当前线段匹配掉一定不劣。

```cpp
int n,ans;
struct node{
	int l,r,t;
	const operator<(node _){
		return r<_.r;
	}
}a[N];
multiset<int>s[2];
signed main(){
	n=read(),ans=n;
	for (int i=1;i<=n;i++) a[i]={read(),read(),read()-1};
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++){
		multiset<int>::iterator it=s[a[i].t^1].lower_bound(a[i].l);
		if (it!=s[a[i].t^1].end()) ans--,s[a[i].t^1].erase(it);
		else s[a[i].t].insert(a[i].r);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Tweetuzki (赞：2)

> 有 $n$ 条线段，第 $i$ 条线段为 $[l_i, r_i]$。每条线段为黑色或白色。我们称一对线段不好当且仅当颜色不同且有公共点。求一个最大的子集使得不存在不好的线段对。
> 
> $n \le 2 \cdot 10 ^ 5$。

老套路了，按照 $r_i$ 从小到大的顺序加入。

考虑记 $black[i][j]$ 表示第 $i$ 条线段加入后，最后一条黑色线段右端点在 $j$ 的最大答案；同理，记 $white[i][j]$ 为白色线段右端点在 $j$ 的最大答案。

加入第 $i$ 条线段时，不妨设其为黑色，白色同理。那么有转移式：

- 如果不选择这条线段，$black[i][j] \gets black[i - 1][j]$，$white[i][j] \gets white[i - 1][j]$。
- 如果选择这条线段，则不能选择右端点在 $[l_i, r_i]$ 间的白色线段，而左端点在 $[l_i, r_i]$ 间的黑色线段随便选。那么有，$\displaystyle black[i][r_i] \xleftarrow{\max} \max\limits_{0 \le j \lt l_i}(white[i - 1][j] + count\_black(j + 1, r_i))$，其中 $count\_black(l, r)$ 表示左右端点都在 $[l, r]$ 之间的黑色线段数量。

我们可以把 $count\_black()$ 的贡献先贡献到 $white[i][j]$ 里面，然后变成一个前缀最大值转移。准确来说，每次要加入一条黑色线段 $[l, r]$ 之前，给所有的 $j \lt l$ 的 $white[i][j]$ 加上 $1$，这是个前缀加。

于是我们发现这个可以直接线段树维护，只要实现单点修改、前缀加、查前缀最大值。时间复杂度 $\mathcal{O}(n \log n)$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>

const int MaxN = 200000, MaxV = 400000;
const int MaxNodes = (1 << 20);

int N, V;
struct seg_t { int l, r, t; } A[MaxN + 5];

struct SegTree {
  int L[MaxNodes + 5], R[MaxNodes + 5];
  int Max[MaxNodes + 5], Tag[MaxNodes + 5];

  inline void upt(int x, int v) {
    Max[x] += v;
    Tag[x] += v;
  }

  inline void pushdown(int i) {
    if (Tag[i] != 0) {
      upt(i << 1, Tag[i]);
      upt(i << 1 | 1, Tag[i]);
      Tag[i] = 0;
    }
  }

  void buildTree(int left, int right, int i = 1) {
    L[i] = left, R[i] = right;
    Max[i] = Tag[i] = 0;
    if (L[i] == R[i]) return;
    int mid = (L[i] + R[i]) >> 1;
    buildTree(left, mid, i << 1);
    buildTree(mid + 1, right, i << 1 | 1);
  }

  void updateTree(int left, int right, int val, int i = 1) {
    if (left > right) return;
    if (left == L[i] && right == R[i]) {
      upt(i, val);
      return;
    }
    pushdown(i);
    int mid = (L[i] + R[i]) >> 1;
    if (right <= mid) updateTree(left, right, val, i << 1);
    else if (left > mid) updateTree(left, right, val, i << 1 | 1);
    else updateTree(left, mid, val, i << 1), updateTree(mid + 1, right, val, i << 1 | 1);
    Max[i] = std::max(Max[i << 1], Max[i << 1 | 1]);
  }

  void updatePos(int pos, int val, int i = 1) {
    if (L[i] == R[i]) {
      Max[i] = val;
      return;
    }
    pushdown(i);
    int mid = (L[i] + R[i]) >> 1;
    if (pos <= mid) updatePos(pos, val, i << 1);
    else updatePos(pos, val, i << 1 | 1);
    Max[i] = std::max(Max[i << 1], Max[i << 1 | 1]);
  }

  int queryTree(int left, int right, int i = 1) {
    if (left > right) return 0;
    if (L[i] == left && R[i] == right) return Max[i];
    pushdown(i);
    int mid = (L[i] + R[i]) >> 1;
    if (right <= mid) return queryTree(left, right, i << 1);
    else if (left > mid) return queryTree(left, right, i << 1 | 1);
    else return std::max(queryTree(left, mid, i << 1), queryTree(mid + 1, right, i << 1 | 1));
  }
};
SegTree Wh, Bl;

template <typename Int>
inline void tense(Int &x, Int y) { if (y > x) x = y; }
template <typename Int>
inline void relax(Int &x, Int y) { if (y < x) x = y; }

void init() {
  static int d[MaxV + 5];
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d %d %d", &A[i].l, &A[i].r, &A[i].t);
    d[++V] = A[i].l, d[++V] = A[i].r;
  }
  std::sort(d + 1, d + 1 + V);
  for (int i = 1; i <= N; ++i) {
    A[i].l = std::lower_bound(d + 1, d + 1 + V, A[i].l) - d;
    A[i].r = std::lower_bound(d + 1, d + 1 + V, A[i].r) - d;
  }
}

inline bool seg_cmp(const seg_t &x, const seg_t &y) { return x.r < y.r; }

void solve() {
  std::sort(A + 1, A + 1 + N, seg_cmp);
  Wh.buildTree(0, V), Bl.buildTree(0, V);
  for (int l = 1, r = 0; l <= N; l = r + 1) {
    while (r < N && A[r + 1].r == A[l].r) r++;
    int wh_max = 0, bl_max = 0;
    for (int i = l; i <= r; ++i) {
      if (A[i].t == 2) Wh.updateTree(0, A[i].l - 1, 1);
      else Bl.updateTree(0, A[i].l - 1, 1);
    }
    for (int i = l; i <= r; ++i) {
      // printf("(%d, %d, %d)\n", A[i].l, A[i].r, A[i].t);
      if (A[i].t == 1) tense(wh_max, Bl.queryTree(0, A[i].l - 1));
      else tense(bl_max, Wh.queryTree(0, A[i].l - 1));
    }
    // printf("wh_max = %d, bl_max = %d\n", wh_max, bl_max);
    Wh.updatePos(A[l].r, wh_max);
    Bl.updatePos(A[l].r, bl_max);
  }
  printf("%d\n", std::max(Wh.queryTree(0, V), Bl.queryTree(0, V)));
}

int main() {
  init();
  solve();
  return 0;
}
```

---

## 作者：violin_wyl (赞：1)

## [Bicolored Segments](https://codeforces.com/contest/1389/problem/F)

### 解析：

#### 题目大意：
两个颜色不同切相交的线段不能同时选（颜色 $c_i\in\{0,1\}$），问最大选择方案。

#### 思路：

（以下 $c_i$ 代表 $t_i$ ）。

考虑先对线段按照 $r$ 从小到大排序，设计一个 $dp_i$ 表示前 $i$ 个线段最多能选多少个线段。

那么有 $n^2$ 转移：$dp_{i}=\max_{j<i,c_j=c_i\| r_j<l_i}dp_j+1$。

考虑优化，我们发现排序后满足 $c_j\not=c_i\land r_j<l_i$ 的线段应该是 $n$ 的一个前缀，因此考虑线段树。我们开两棵线段树，第 $i$ 个位置的值是 $dp_i$，那么转移等价于前缀最大值。

考虑如果我们选择了 $dp_j$，那么 $\forall k,r_j<l_k\land c_k=c_i$ 的 $k$ 也是可以选的，所以我们在更新完 $dp_i$ 后，先找到满足 $c_j\not=c_i\land r_j<l_i$ 的最大的 $j$ ，对 $c_i \operatorname{xor} 1$ 对应线段树的区间 $[1,j]$ 上做一次区间加。

~~2600恶评，2200差不多~~

----------------------------------------------------

### code：

```c++
#include <bits/stdc++.h>
#define mk make_pair
#define pb push_back
#define eb emplace_back
#define lob lower_bound
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 10;
const int INF = INT_MAX;
typedef pair <int, int> pii;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') { if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n;
int dp[N];
struct node {
	int l, r, c;
	bool operator < (const node &a) const {
		return r == a.r ? l < a.l : r < a.r;
	}
} a[N];
struct node2 {
	int l, r, id;
	node2 () {}
	node2 (int _l, int _r, int _id) { l = _l; r = _r; id = _id; }
	bool operator < (const node2 &a) const {
		return r == a.r ? (id == a.id ? l < a.l : id < a.id) : r < a.r;
	}
};
vector <node2> v[2];
struct Seg_tree {
    #define lson rt << 1
    #define rson rt << 1 | 1
    struct node {
        int mx, tag;
        #define mx(rt) tree[rt].mx
        #define tag(rt) tree[rt].tag
    } tree[N << 2];
    inline void pushup (int rt) { mx(rt) = max (mx(lson), mx(rson)); }
    void spread (int rt)
	{
		if (tag(rt))
		{
			mx(lson) += tag(rt); mx(rson) += tag(rt);
			tag(lson) += tag(rt); tag(rson) += tag(rt);
			tag(rt) = 0;
		}
	}
    void modify (int rt, int l, int r, int L, int R, int val)
    {
        if (L <= l && r <= R) { mx(rt) += val; tag(rt) += val; return ; }
        spread (rt);
        int mid = (l + r) >> 1;
        if (L <= mid) modify (lson, l, mid, L, R, val);
        if (R > mid) modify (rson, mid + 1, r, L, R, val);
        pushup (rt);
    }
    int query (int rt, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return mx(rt);
		spread (rt);
		int mid = (l + r) >> 1, res = 0;
		if (L <= mid) res = max (res, query (lson, l, mid, L, R));
		if (R > mid) res = max (res, query (rson, mid + 1, r, L, R));
		return res;
	}
} T[2];
signed main()
{
    n = read ();
    for (int i = 1; i <= n; i++) a[i].l = read (), a[i].r = read (), a[i].c = read () - 1;
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) v[a[i].c].eb (a[i].l, a[i].r, i);
	for (int i = 0; i <= 1; i++) sort (v[i].begin (), v[i].end ());
	int sum[2] = {0, 0};
	for (int i = 1; i <= n; i++) dp[i] = ++sum[a[i].c];
	for (int i = 1; i <= n; i++)
	{
		int c = a[i].c ^ 1;
		int t = lob (v[c].begin(), v[c].end(), node2(0, a[i].l, 0)) - v[c].begin() - 1;
		if (~t)
		{
			dp[i] = max (dp[i], T[c].query (1, 1, n, 1, v[c][t].id) + 1);
			T[c].modify (1, 1, n, 1, v[c][t].id, 1);
		}
		T[a[i].c].modify (1, 1, n, i, i, dp[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max (ans, dp[i]);
	printf ("%d\n", max (ans, max (sum[0], sum[1])));
    return 0;
}
```

---

## 作者：wangyishan (赞：0)

神秘题。

首先我们知道二分图的 $\texttt{最大独立集}=n-\texttt{最大匹配}=n-\texttt{最小点覆盖}$。

证明可以看 [OI-Wiki](https://oi-wiki.org/graph/graph-matching/bigraph-match/#%E4%BA%8C%E5%88%86%E5%9B%BE%E6%9C%80%E5%B0%8F%E7%82%B9%E8%A6%86%E7%9B%96k%C3%B6nig-%E5%AE%9A%E7%90%86)。

然后注意到这里面只有两种颜色，所以我们可以把它转化成一个二分图的模型。

具体的，我们在任意两条不同颜色且有交点的两条线段之间连边，这样就形成了一个二分图。原来题目的问题就变成了求这个二分图的最大独立集。

根据上面的定理，我们只需要求这个图的最大匹配即可。

但是你不能直接增广路、Dinic，因为这里 $n\leq 1\times10^5$，$m$ 甚至可以是 $1\times 10^{10}$ 级别的。

但是你可以直接贪心。

按照右端点排序后对于两种线段各维护一个可重集，里面保存着还没有被匹配的线段。

从前往后遍历，每次去对方的可重集里二分寻找是否有能够和这条线段匹配的线段，如果有就匹配上，有多个就优先匹配右端点最靠左的那条（贪心，证明显然）。如果没有就把这条线段放到还没被匹配的可重集中，最后 $n-\texttt{匹配数}$ 就是答案。

时间复杂度是排序以及维护 `multiset` 的 $\mathcal{O}(n\log n)$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
struct node{
    int l,r,t;
}a[500050];
multiset<int>b[2];
int n;
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i].l>>a[i].r>>a[i].t;a[i].t--;}
    sort(a+1,a+n+1,[](node x,node y){
        if(x.r==y.r)return x.l<y.l;
        return x.r<y.r;
    });
    int num=0;
    for(int i=1;i<=n;i++){
        auto it=b[a[i].t^1].lower_bound(a[i].l);// 二分
        if(it!=b[a[i].t^1].end()){
            num++;
            b[a[i].t^1].erase(it);
        }else b[a[i].t].insert(a[i].r);
    }
    cout<<n-num<<endl;
    return 0;
}
```

---

