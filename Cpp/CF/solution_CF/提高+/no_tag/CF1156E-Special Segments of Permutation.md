# Special Segments of Permutation

## 题目描述

给定一个长度为 $n$ 的排列 $p$，排列由 $1, 2, \ldots, n$ 这 $n$ 个整数组成（排列是一个数组，其中每个 $1$ 到 $n$ 的元素恰好出现一次）。

我们称排列的某个子区间 $p[l, r]$ 是“特殊”的，如果满足 $p_l + p_r = \max\limits_{i = l}^{r} p_i$。请计算该排列中有多少个特殊子区间。

## 说明/提示

第一个样例中的特殊子区间为 $[1, 5]$ 和 $[1, 3]$。

第二个样例中唯一的特殊子区间是 $[1, 3]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3 4 1 5 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 3 2
```

### 输出

```
1
```

# 题解

## 作者：nofind (赞：16)

题意：

给定一个长度为n的排列p，求有多少区间[l,r]满足，p[l]+p[r]=max{p[i]}，其中l<=i<=r

解析：

首先显然要预处理最大值。

先将每个数所控制的区间(向左右第一个大于a[i]的数的位置)预处理（正反两遍单调栈O(N)）：L[i],R[i]

之后对于每个数,满足条件的区间[L,R] : L[i]<L<i , i<R<R[i].

之后枚举L,R,由于用pos[]记录了每个数值的位置,对于a[i]：假设枚举的位置是x,只需判断a[i]-a[x]是否在相反的区间即可判断是否满足要求。

以上听起来似乎是O(N^2),但是我们可以做一些优化：我们发现对于a[i]，我们似乎只需要扫描左右区间中较小的一个即可,因为从哪边扫描是一样的（应该很好理解吧~）

好吧还是解释一下吧：两边满足条件的点是一一对应的，所以从任意一边扫描,找到的点对是相同的。

栗子： 3 4 5 2 1

对于5这个数，左右的 4-1 是对应的,你会发现可以从左边的 4发现 右边的 1, 从右边的 1 也同样能找到 4,找到的点对是相同的
 
 
 好的我们成功将每个数的区间切半（最小那一边的长度必定不超过该区间长度的一半）

考虑每个点最多被log个处理区间覆盖,总复杂度：O(NlogN）

code：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
int n,top;
int a[maxn],pos[maxn],L[maxn],R[maxn],s[maxn];
long long ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),pos[a[i]]=i;
	//printf("1111\n");
	for(int i=1;i<=n;i++)//正向. 
	{
		while(top&&a[s[top]]<a[i]) top--;
		L[i]=s[top],s[++top]=i;
	}
	top=0,s[top]=n+1;
	//printf("1111\n");
	for(int i=n;i>=1;i--)//反向. 
	{
		while(top&&a[s[top]]<a[i]) top--;
		R[i]=s[top],s[++top]=i;
	}
	//printf("1111\n");
	for(int i=1;i<=n;i++)
	{
		if(i-L[i]<R[i]-i)
		{
			for(int j=L[i]+1;j<i;j++)
				if(pos[a[i]-a[j]]>i&&pos[a[i]-a[j]]<R[i]) ans++;		
		}
		else
		{
			for(int j=i+1;j<R[i];j++)
				if(pos[a[i]-a[j]]>L[i]&&pos[a[i]-a[j]]<i) ans++;
		}
	}
	//printf("1111\n");
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：jucason_xu (赞：10)

启发式合并算是一种被人们熟知的算法，启发式合并的复杂度正确性证明等价于重链剖分的正确性证明。

不过在很多题目中，我们或许需要逆用启发式合并，从而在可能非常不平衡的树上达到正确的复杂度。

（本题和两 edu 场后的 [CF1175F](https://www.luogu.com.cn/problem/CF1175F)，都是在笛卡尔树上进行启发式合并或模拟这一过程，笛卡尔树就是典型的期望深度 $O(\log n)$ 但是容易被卡且无法通过随机化保证深度的例子）


对于一个排列，求有多少个区间 $[l,r]$ 满足：$p(l)+p(r)=max_{i=l}^{r}{p(i)}$

### 暴力的火种

如果枚举 $l$ 或 $r$，很明显 $i$ 会随着另一个端点的变化而变化，单调栈很难维护。这里，我们就需要尝试别的方法——枚举 $i$。

我们发现，$i$ 一定只会对自己是区间最大值的区间产生贡献。

想到使用单调栈维护每一个点左边和右边第一个比自己大的位置，也就是对于每个i，用单调栈处理出 $lm(i)$ 和 $rm(i)$。

然后？朴素的做法是枚举 $[lm(i),i)$ 和 $(i,rm(i)]$ 中的所有数进行配对。

这样做是 $O(n^3)$ 的。

### 优化的希望

考虑优化这个做法，只枚举 $[lm(i),i-1]$ 中的所有数 $j$，提前处理排列的逆（也就是处理每一个数出现的位置），判断 $p(i)-p(j)$ 的位置是否在 $[i+1,rm(i)]$ 中。

这样我们就得到了一个 $O(n^2)$ 的做法，卡掉它也很容易，构造一个完全有序的排列就可以了。

### 通过的奇迹

每次都枚举 $[lm(i),i-1]$ 中的数会挂，那么如果我每次挑 $[lm(i),i-1]$ 和 $[i+1,rm(i)]$ 中短的一个枚举而匹配另一个，怎么样呢？

这样看上去是错的，实际上可以 AC，为什么呢？其实，这就是在模拟笛卡尔树上逆向启发式合并的过程。

### 通过后的反思 

$i$ 的左边第一个大于 $i$ 的位置是 $lm(i)$，$i$ 的右边第一个大于 $i$ 的位置是 $rm(i)$。

如果给这个序列建立笛卡尔树的话， __$i$ 一定是 $lm(i)$ 或 $rm(i)$ 的儿子。并且是 $i$ 父亲的那一个一定是另一个的后代。__

1. 如果 $i$ 既不是 $lm(i)$ 的儿子也不是 $rm(i)$ 的儿子，那么意味着 $i$ 和父亲之间有一个大于 $i$ 的点，父亲的左/右儿子已经被占去，而 $i$ 不能成为这个点的祖先，这个点就没有父亲了。

2. 如果 $i$ 的父亲不是另一个的后代：那么考虑它们的 LCA，一定在$(lm(i),rm(i))$区间内。否则一定会有一个点同时有两个左/右儿子。但是这段区间没有比他们大的数。

__因此， $(lm(i),rm(i))$ 中的每个点都在以i为根的子树上__ 。这是为什么呢？现在先假设 $rm(i)$ 是 $i$ 的父亲而 $lm(i)$ 是 $i$ 的祖先，那么 $lm(i)$ 的右儿子位置被占去，$(lm(i),i)$ 中的所有位置都应当处于 $i$ 的左子树。$rm(i)$ 的右儿子位置被占去，$(i,rm(i))$ 都应处于 $i$ 的右子树。

所以， __我们前文的“对于每一个 $i$，找到最大的以它为最大值的区间”其实就是“对于每一个 $i$，找到它在笛卡尔树上的子树”。__

那么，我们扫一遍所有点，对于每一个点，扫其较小的一棵子树（相当于把较小子树的信息合并到较大子树上）从而统计答案。

我们发现，这一过程就是启发式合并的逆过程，两者在正确性上也是等价的。

本做法有三种实现。

第一种是真的建出笛卡尔树，然后真的在笛卡尔树上跑启发式合并。

对每一个点维护一个 `set` 存储子树信息，每次合并的时候，先遍历小 `set` 计算答案，再把小 `set` 加到大 `set` 中。这就是完全标准的启发式合并。启发式一个  $\log$，带上 `set` 一个 $\log$，复杂度 $O(n\log^2 n)$。

```cpp

int n,a[200005],ls[200005],rs[200005],st[200005],top,rt;
set<int>s[200005];
inline void build(){
	st[top=1]=1,rt=1;
	rep(i,2,n){
		int lst=0;
		while(top&&a[st[top]]<a[i])lst=st[top--];
		if(lst)ls[i]=lst;
		if(!top)rt=i;
		else rs[st[top]]=i;
		st[++top]=i;
	}
}
int ans=0;
inline void merge(int i,int j){
	if(s[j].size()>s[i].size())swap(s[i],s[j]);
	for(auto v:s[j]){
		if(s[i].find(a[i]-v)!=s[i].end())ans++;
	}
	for(auto v:s[j]){
		s[i].insert(v);
	}
}
inline void dfs(int i){
	if(ls[i]){
		dfs(ls[i]);
		merge(i,ls[i]);
	}
	if(rs[i]){
		dfs(rs[i]);
		merge(i,rs[i]);
	}
	s[i].insert(a[i]);
	
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	rp(i,n)cin>>a[i];
	build();
	dfs(rt);
	cout<<ans<<endl;
	return 0;
}
//Crayan_r
```

第二种是两次单调栈处理出 $lm(i)$ 和 $rm(i)$，然后去模拟这个过程。

因为这个算法和点在笛卡尔树上的祖先顺序无关，所以可以直接从左往右枚举 $i$。

因为这道题是排列，可以 $O(1)$ 判断区间内是否有某一个值，所以只有启发式的一个 $\log$，复杂度 $O(n\log n)$。

实际上，这种做法虽然简单，但是只有完全理解上一个做法之后，才能明白、敢写这一种做法。

```cpp
int n,a[200005],b[200005];
int lm[200005],rm[200005],st[200005],top;
inline void init(){
	a[0]=1e9,st[top=1]=0;
	rep(i,1,n){
		while(top&&a[st[top]]<a[i])top--;
		lm[i]=st[top];
		st[++top]=i;
	}
	a[n+1]=1e9,st[top=1]=n+1;
	per(i,1,n){
		while(top&&a[st[top]]<a[i])top--;
		rm[i]=st[top];
		st[++top]=i;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	rp(i,n)cin>>a[i];
	rp(i,n)b[a[i]]=i;
	init();
	int ans=0;
	rp(i,n){
		int l=lm[i]+1,r=rm[i]-1;
		if(l<i&&i<r){
			if(r-i>i-l)rep(j,l,i-1){
				int to=b[a[i]-a[j]];
				ans+=(i<to&&to<=r);
			}else rep(j,i+1,r){
				int to=b[a[i]-a[j]];
				ans+=(l<=to&&to<i);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
//Crayan_r
```

第三种是分治模拟笛卡尔树，每次解决区间 $[l,r]$。

我们可以预处理 st 表然后每次 $O(1)$ 查询当前区间最大位置 $mid$，也就是找到当前子树的根。

然后暴力扫描较小的区间计算答案，递归处理 $[l,mid-1]$ 和 $[r,mid+1]$ 。相当于不建树完成第一个做法，复杂度 $O(n\log n)$。

```cpp
int n,a[200005],b[200005];
int st[200005][20],ans=0;
inline int cmp(int x,int y){
	if(a[x]>a[y])return x;
	return y;
}
inline void init(){
	rep(i,1,n)st[i][0]=i;
	rep(j,1,20)rep(i,1,n)if(i+(1<<j)-1<=n){
		st[i][j]=cmp(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
}
inline int rmq(int l,int r){
	int x=__lg(r-l+1);
	return cmp(st[l][x],st[r-(1<<x)+1][x]);
}
inline void solve(int l,int r){
	if(l==r||l>r)return;
	int mid=rmq(l,r);
	if(r-mid>=mid-l){
		rep(i,l,mid-1){
			int to=b[a[mid]-a[i]];
			if(mid<to&&to<=r)ans++;
		}
	}else{
		rep(i,mid+1,r){
			int to=b[a[mid]-a[i]];
			if(l<=to&&to<mid)ans++;
		}
	}
	solve(l,mid-1);
	solve(mid+1,r);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	rp(i,n)cin>>a[i];
	rp(i,n)b[a[i]]=i;
	init();
	solve(1,n);
	cout<<ans<<endl;
	return 0;
}
//Crayan_r
```
分析这三种做法的优劣：

第一种时间最劣（时间双 $\log$ `483ms` ）

第二种属于对做法本质理解之后才能写出的做法，最简单。

第三种可以扩展到更多的相似题目，比如说 [CF1175F](https://www.luogu.com.cn/problem/CF1175F)。



---

## 作者：hfctf0210 (赞：7)

看到Unrated就不打了，口胡了一个分治做法，一写发现，它居然过了。

做法大致如下：直接算很难处理，考虑分治，对于长度大于等于3的区间[l,r]，考虑覆盖mid和mid+1的所有区间，可以把[l,r]分为[l,mid]和[mid+1,r]两半，然后mx[i]对于左半部分表示后缀最大值，对于右半部分表示前缀最大值，然后枚举位置计算另一端的位置是否符合题意，因为区间的max值出现在两端的mx之一，所以左右都搜一下即可统计所有答案。复杂度O(nlogn)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+7;
int n,ans,a[N],b[N],mx[N];
void solve(int l,int r)
{
	if(l+1>=r)return;
	int mid=l+r>>1;
	solve(l,mid),solve(mid+1,r);
	mx[mid]=a[mid];for(int i=mid-1;i>=l;i--)mx[i]=max(mx[i+1],a[i]);
	mx[mid+1]=a[mid+1];for(int i=mid+2;i<=r;i++)mx[i]=max(mx[i-1],a[i]);
	for(int i=l;i<=mid;i++)
	{
		int pos=b[mx[i]-a[i]];
		if(pos>mid&&pos<=r&&mx[pos]<mx[i])ans++;
	}
	for(int i=mid+1;i<=r;i++)
	{
		int pos=b[mx[i]-a[i]];
		if(pos>=l&&pos<=mid&&mx[pos]<mx[i])ans++;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[a[i]]=i;
	solve(1,n);
	printf("%d",ans);
}
```


---

## 作者：yijan (赞：4)

### 1156E Special Segments of Permutation

分治套路题。

开始没想到按照题解说的直接枚举较小的一边。。

其实可以直接按照套路从中间分开，然后考虑枚举从中间点开始向右枚举右端点，假设当前枚举到的右端点是 $R$ ，我们钦定最大值在 $[mid+1,R]$ 区间内，那么左端点可以存在的一定是 $[L,mid]$ 的一段后缀，直接双指针扫这个后缀就完事了，用一个 set 或者 hash 表维护一下 $[L,mid]$ 的数。再对钦定在左边同样操作一下，复杂度 是 $O(n\log^2n)$ 或者 $O(n\log n)$ 。很好写，而且跑得挺快的。。

而且这么做即使给的不是排列一样能做吧。。只是换成 `multiset` 而已了。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
#define min( a , b ) ( (a) < (b) ? (a) : (b) )
#define max( a , b ) ( (a) > (b) ? (a) : (b) )
#define P 998244353
typedef long long ll;
int n , m;
int A[MAXN];
long long ans = 0;
set<int> S;
void solve( int l , int r ) {
    if( l == r ) return;
    int mid = l + r >> 1;
    int L = mid + 1 , R = mid + 1 , mxr = 0 , mxl;
    S.clear();
    for( ; R <= r ; ++ R ) {
        mxr = max( mxr , A[R] );
        while( L > l && A[L - 1] < mxr ) -- L , S.insert( A[L] );
        if( S.find( mxr - A[R] ) != S.end() ) ++ ans;
    }
    L = mid , R = mid , mxl = 0;
    S.clear();
    for( ; L >= l ; -- L ) {
        mxl = max( mxl , A[L] );
        while( R < r && A[R + 1] < mxl ) ++ R , S.insert( A[R] );
        if( S.find( mxl - A[L] ) != S.end() ) ++ ans;
    }
    solve( l , mid ) , solve( mid + 1 , r );
}
void solve() {
    cin >> n;
    rep( i , 1 , n ) scanf("%d",A + i);
    solve( 1 , n );
    cout << ans << endl;
}

signed main() {
//    freopen("input","r",stdin);
//    freopen("fuckout","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
    solve();
}

```



---

## 作者：nekko (赞：3)

考虑对序列建立笛卡尔树，那么在笛卡尔树上进行启发式合并即可

对应到序列上的实际操作就是，首先对于每一个位置搞出它作为最大值所能扩展的区间，然后枚举小区间的每一个数字，判断另一个数字是否可以在大区间取到

``` cpp
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, pos[N], a[N], L[N], R[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
        L[i] = R[i] = i;
    }
    stack<int> sta;
    for(int i = 1 ; i <= n ; ++ i) {
        while(sta.size() && a[sta.top()] < a[i]) {
            sta.pop();
        }
        if(sta.size()) {
            L[i] = sta.top() + 1;
        } else {
            L[i] = 1;
        }
        sta.push(i);
    }
    sta = stack<int> ();
    for(int i = n ; i >= 1 ; -- i) {
        while(sta.size() && a[sta.top()] < a[i]) {
            sta.pop();
        }
        if(sta.size()) {
            R[i] = sta.top() - 1;
        } else {
            R[i] = n;
        }
        sta.push(i);
    }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("[%d, %d]\n", L[i], R[i]);
    // }

    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        int la = i - L[i];
        int ra = R[i] - i;
        if(la < ra) {
            for(int j = L[i] ; j <= i ; ++ j) {
                int y = a[i] - a[j];
                if(1 <= y && y <= n) {
                    if(i <= pos[y] && pos[y] <= R[i]) {
                        ++ ans;
                    }
                }
            }
        } else {
            for(int j = i ; j <= R[i] ; ++ j) {
                int y = a[i] - a[j];
                if(1 <= y && y <= n) {
                    if(L[i] <= pos[y] && pos[y] <= i) {
                        ++ ans;
                    }
                }
            }
        }
    }
    printf("%lld\n", ans);
}
```

---

## 作者：UperFicial (赞：2)

提供一个三只老哥的做法，喜提最烈解/cy

考虑 CDQ 分治后，需要求出左右端点分别在 $[l,mid]$ 和 $(mid,r]$ 的数对数量。

设 $b_i$ 为 $[i,mid]$ 或 $[mid+1,r]$ 中 $a_i$ 的最大值。

则原式转化为 $a_i+a_j=\max(b_i,b_j)$。

有一个 $\max$，分情况讨论就好了：

- 若 $b_i>b_j$，需要求出 $(mid,r]$ 中 $a_j=b_i-a_i$ 的 $j$ 的数量。

- 若 $b_i\le b_j$，需要求出 $(mid,r]$ 中 $b_j-a_j=a_i$ 的 $j$ 的数量。

把 $b$ 看做下标，用树状数组套 vector 维护就好了，查询等于某个数的数量只需要两次二分。

注意每次插入数后 vector 都排序会 T，则先将下标和键值看做二元组排序，然后顺序插入就好了。

注意每次清空时记录树状数组用了哪些节点，每次只清空那些节点对应的 vector 就好了。



---

## 作者：CG__HeavenHealer (赞：1)


这一类问题还是挺套路的。

---

### 题意

给定一个长度为 $n$ 的排列 $p$，求有多少区间 $[l,r]$ 满足，$p[l]+p[r]=max{p[i]}$，其中 $l<=i<=r$

---

### 解法

首先这个东西的暴力应该很好想。

不考虑任何优化，枚举左右端点，再找最大值的做法应该是 $\Theta(n^3)$ 的，用 ST 表去找最大值可以做到 $\Theta(n^2)$。

但是这还远远不够。

如果一直考虑枚举端点的话复杂度是降不下来的，换种角度考虑枚举区间内的最大值。

但是每个值的作用范围，也就是那些区间的最大值是这个数是不确定的。

那么可以先用单调栈处理出每个数前面和后面第一个比它大的数，记为  $pre_i,suf_i$，那么这个数起作用的子区间的端点 $l,r\in[pre_i+1,suf_i-1]$。

接下来就是比较套路的处理方式了：枚举每一个最大值，然后枚举短的一边计算贡献，这样的复杂度可以做到均摊 $\log$。

~~这个题实在是太弱化了~~统计这个贡献甚至什么数据结构都不需要，直接记一个 $pos$ 就可以了。

如果要求可重集的答案的话，需要用一个主席树，复杂度是 $\Theta(n\log^2n)$ 的。

~~虽然主席树没用但我还是用了~~

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 1e9 + 7;
namespace IO {
    template<typename T>
    inline void read(T &x) {
        x = 0;
        bool f = false;
        char c = getchar();
        for (; !isdigit(c); c = getchar()) f |= (c == '-');
        for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
        if (f) x = ~x + 1;
    }
    template<typename T, typename ...Args>
    inline void read(T &t, Args &...args) {
        read(t), read(args...);
    }
    template<typename T>
    inline void write(T x, char ed = ' ') {
        static char sk[50];
        int tp = 0;
        if (!x) putchar('0');
        if (x < 0) x = ~x + 1, putchar('-');
        while (x) sk[++tp] = x % 10 + '0', x /= 10;
        while (tp) putchar(sk[tp--]);
        putchar(ed);
    }
    template<typename T, typename ...Args>
    inline void write(T t, Args ...args) {
        write(t), write(args...);
    }
}
using namespace IO;
int n, a[N];
namespace Chairman_Tree {
    struct Tree {
        int l, r, v;
    } t[N * 100];
#define ls(x) t[x].l
#define rs(x) t[x].r
#define mid ((l + r) >> 1)
    int rt[N], tot;
    void update(int &x, int pre, int l, int r, int pos) {
        x = ++tot, t[x] = t[pre], t[x].v++;
        if (l == r) return;
        if (pos <= mid)
            update(ls(x), ls(pre), l, mid, pos);
        else
            update(rs(x), rs(pre), mid + 1, r, pos);
    }
    int query(int x, int y, int l, int r, int pos) {
        if (l == r) return t[y].v - t[x].v;
        if (pos <= mid)
            return query(ls(x), ls(y), l, mid, pos);
        else
            return query(rs(x), rs(y), mid + 1, r, pos);
    }
}
using namespace Chairman_Tree;
int stk[N], top, pre[N], suf[N], ans;
int main() {
#ifdef LOCAL
    freopen("aa.in", "r", stdin);
    freopen("aa.out", "w", stdout);
#endif  
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        pre[i] = 1, suf[i] = n;
        update(rt[i], rt[i - 1], 1, n, a[i]);
    }   
    stk[top = 0] = 0;
    for (int i = 1; i <= n; i++) {
        while (top && a[stk[top]] < a[i]) top--;
        pre[i] = stk[top], stk[++top] = i;
    }
    stk[top = 0] = n + 1;
    for (int i = n; i; i--) {
        while (top && a[stk[top]] < a[i]) top--;
        suf[i] = stk[top], stk[++top] = i;
    }

    // for (int i = 1; i <= n; i++) {
    //     printf("pre = %d, suf = %d\n", pre[i], suf[i]);
    // }

    for (int i = 1; i <= n; i++) {
        int l = pre[i] + 1, r = suf[i] - 1;
        if (i - l < r - i) {
            for (int j = l; j < i; j++) {
                int x = a[i] - a[j];
                ans += query(rt[i - 1], rt[r], 1, n, x);
            }
        } else {
            for (int j = i + 1; j <= r; j++) {
                int x = a[i] - a[j];
                ans += query(rt[l - 1], rt[i], 1, n, x);
            }
        }
    }
    write(ans, '\n');
#ifdef LOCAL
    fclose(stdin), fclose(stdout);
#endif
    return 0;
}
```



---

## 作者：DPair (赞：1)

提供一种另类的解法

## 思路

首先看到这种题的第一反应应该是枚举中间那个 $\max$

我们考虑维护一个 $[1, n]$ 的集合，表示这些 **位置** 上的数没有被访问过，那么我们考虑在值域上从小到大枚举，发现 **前驱+1 到 后继-1** 这些位置都以当前值为最大值，而更远一些则不行

发现可以链表维护前驱后继，这部分是 $O(n)$ 的

那么处理时也很简单，发现当前位置把区间分成了两边，我们扫描较小的一边，然后发现由于我们已经确定了 $\max$ 和 $l, r$ 中的一个，那么另一个的值也可以唯一确定，由于原序列是一个排列，因此直接判断另一个数的出现位置是否在另一半区间内即可，若是则加上贡献

我们考虑分析其复杂度，发现如果要卡满，那么有：

$$T(n)=\max_{i=1}^{{\lfloor{n\over 2}\rfloor}}\{T(i)+T(n-i)+i\}$$

这个自行理解不难，可以考虑从大往小枚举会发生什么，本质上是相同的

然后本地跑一遍 dp 会发现这东西是 $O(n\log n)$ 级别的，因此可以通过本题

## 代码
只保留关键部分
```cpp
const int MAXN = 2e5 + 5;
int n, a[MAXN], p[MAXN], suc[MAXN], pre[MAXN], ans = 0;
inline void solve(int l, int r, int mid, const int x) {
    if(r - mid > mid - l) rep(i, l, mid - 1) ans += (p[x - a[i]] > mid && p[x - a[i]] <= r);
    else rep(i, mid + 1,r) ans += (p[x - a[i]] < mid && p[x - a[i]] >= l);
}

signed main(){
    read(n); read(a + 1, a + n + 1); rep(i, 1, n) p[a[i]] = i, pre[i] = i - 1, suc[i] = i + 1;
    rep(i, 1, n) {
        const int x = p[i];
        solve(pre[x] + 1, suc[x] - 1, x, i);
        pre[suc[x]] = pre[x]; suc[pre[x]] = suc[x];
    } print(ans);
}
```

---

## 作者：Tari (赞：1)

### 思路：笛卡尔树？（好像并不一定要建出来，但是可以更好理解）
### 提交：2次
#### 错因：没有判左右儿子是否为空来回溯导致它T了
### 题解：
建出笛卡尔树，考虑如何计算答案：  

先预处理每一个值出现的位置 $pos[]$；

对于每一个有左右儿子的点，设他在原序列中的值为 $mx$，根据笛卡尔树的性质，他比自己的子树中的任何一个元素都大 。这样， 我们遍历他的轻儿子中的元素 $vl$ ，查询 $pos[mx-vl]$ 是否在重子树中。

其实可以不建树，直接求出每个点作为最大值能够向左右扩展的区间，枚举小的区间就够了。

复杂度 $O(nlogn)$ ，原因是类似树剖，每个点最多只会向上跳 $logn$ 条轻边；而一个点被计算，只有在枚举轻子树的时候；其实类似 dsu on tree。

当然，不建树的做法的复杂度虽然解释不同，但本质都是一样的.


### 代码：
```cpp
#include<bits/stdc++.h>
#define R register int
using namespace std;
namespace Luitaryi {
inline int g() { R x=0,f=1;
  register char ch; while(!isdigit(ch=getchar())) f=ch=='-'?-1:f;
  do x=x*10+(ch^48); while(isdigit(ch=getchar())); return x*f;
} const int N=250010;
int n,rt,a[N],pos[N],ans;
struct node {int ls,rs,sz,l,r;} t[N];
#define ls(tr) t[tr].ls
#define rs(tr) t[tr].rs
#define sz(tr) t[tr].sz
#define l(tr) t[tr].l
#define r(tr) t[tr].r
int stk[N],top;
inline void calc(int tr,int rn,int mx) {
  for(R i=l(tr);i<=r(tr);++i) 
    ans+=(pos[mx-a[i]]>=l(rn)&&pos[mx-a[i]]<=r(rn));
}
inline void dfs(int tr) {
  sz(tr)=1,l(tr)=r(tr)=tr;
  if(ls(tr)) dfs(ls(tr)),l(tr)=l(ls(tr)); 
  if(rs(tr)) dfs(rs(tr)),r(tr)=r(rs(tr));
  if(!ls(tr)||!rs(tr)) return ;
  sz(tr)=sz(ls(tr))+sz(rs(tr));
  if(sz(ls(tr))<sz(rs(tr))) calc(ls(tr),rs(tr),a[tr]);
  else calc(rs(tr),ls(tr),a[tr]);
}
inline void main() {
  n=g(); for(R i=1;i<=n;++i) a[i]=g(),pos[a[i]]=i; 
  stk[++top]=0,a[0]=1e9;
  for(R i=1;i<=n;++i) { R lst=0;
    while(a[stk[top]]<a[i]) lst=stk[top],--top;
    ls(i)=lst,rs(stk[top])=i; stk[++top]=i;
  } rt=stk[2];
  dfs(rt); printf("%d\n",ans);
}
} signed main() {Luitaryi::main(); return 0;}
```
***
2019.09.15  
61

---

## 作者：世末OIer (赞：1)

题解：二分+搜索


大体思路见程序注释

```cpp
#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#define ll long long
using namespace std;
const int N=2e5+5;
int n;
int a[N],b[N],mx[N];
ll ans=0;
inline void solve(int l,int r){//类似于二分+搜索 
	if(l==r) return;
	int md=l+r>>1,i;
	solve(l,md);
	solve(md+1,r);
	mx[md]=a[md];
	mx[md+1]=a[md+1];
	for(i=md-1;i>=l;--i) mx[i]=max(mx[i+1],a[i]);        //从中间往外取max 
	for(i=md+2;i<=r;++i) mx[i]=max(mx[i-1],a[i]);        //同上 
	for(i=md;i>=l;--i){
		int t=b[mx[i]-a[i]];
		if(t>md and t<=r and mx[t]<=mx[i]) ++ans;        //找一找:如果在它之前有mx[i]-a[i]则将答案累加 
	}
	for(int i=md+1;i<=r;i++){                            //同上 
		int t=b[mx[i]-a[i]];
		if(t<=md and t>=l and mx[t]<=mx[i]) ++ans;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]=i;              //因为是全排列，所以每一个数字只出现一次，b[]存储出现的位置 
	solve(1,n);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：青烟绕指柔 (赞：0)

凭感觉思考了一下，因为是一个排列，那么如果我们枚举每个数作为最大值时，然后往两边扫，统计答案。因为是排列嘛，所以不可能一直都是扫很长的区间，所以说就是一个暴力。
具体证明不会，也不知道是不是数据水，但是感觉上完全不可能达到O(n^2)

AC代码：
```c
#pragma GCC optimize("-Ofast","-funroll-all-loops")
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=2e5+10;
int n,p[N],vis[N]; long long res;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)	scanf("%d",&p[i]);
	for(int i=2,j,k;i<n;i++){
		if(p[i-1]>p[i]||p[i+1]>p[i])	continue;	j=i-1;
		while(p[j]<p[i]&&j>0)	vis[p[j]]=1,j--;	k=i+1;
		while(p[k]<p[i]&&k<=n){if(vis[p[i]-p[k]])	res++;	k++;}	j=i-1;
		while(p[j]<p[i]&&j>0)	vis[p[j]]=0,j--;
	}
	cout<<res;
	return 0;
}
```

---

