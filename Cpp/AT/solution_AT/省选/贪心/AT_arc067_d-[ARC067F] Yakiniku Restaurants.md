# [ARC067F] Yakiniku Restaurants

## 题目描述

有编号从 $ 1 $ 到 $ N $ 的 $ N $ 家烧烤店，烧烤店在一条线上按照编号顺序排序，第 $ i $ 家烧烤店与第 $ i + 1 $ 家烧烤店的距离是 $ A_i $ 。   
你有编号从 $ 1 $ 到 $ M $ 的 $ M $ 张烧烤券，不管是在哪一家烧烤店都可用烧烤券来吃烧烤，在第 $ i $ 家烧烤店用烧烤券 $ j $ 可以吃到一顿美味度为 $ B_{i,j} $ 的烧烤，每一张烧烤券只能使用一次，但是在一家烧烤店你可以使用任意多张烧烤券。  
你想从自己选择的一家烧烤店开始（随意选择一个开始），然后不断地用未使用的烧烤券去另一家烧烤店。你最终的幸福值是所吃所有烧烤的美味度减去所走的总路程。求最大可能的最终幸福值（ $ M $ 张券必须用完）。

## 说明/提示

输入的数字都是整数
$ 2 \leq N \leq 5 \times 10^3 $
$ 1 \leq M \leq 200 $
$ 1 \leq A_i \leq 10^9 $
$ 1 \leq B_{i,j} \leq 10^9 $
样例解释：
样例1：
在第一家烧烤店开始，使用第1张和第3张券，然后去第二家烧烤店，使用第2张和第4张券。

## 样例 #1

### 输入

```
3 4
1 4
2 2 5 1
1 3 3 2
2 2 5 1```

### 输出

```
11```

## 样例 #2

### 输入

```
5 3
1 2 3 4
10 1 1
1 1 1
1 10 1
1 1 1
1 1 10```

### 输出

```
20```

# 题解

## 作者：hs_black (赞：15)


容易发现选择的肯定是一条线段而且两端必选。

所以我们从右边开始枚举左端点，维护一个答案数组 $tans[j]$ 表示目前左端点固定，右端点在 j 的最优答案，接下来操作就是左端点向左移动一格，并更新答案扫一遍。

如何更新答案，单独考虑每张票，只可能是从某个位置买换到左端点买，这里要求原来的某个位置获利比这个位置小，所以我们可以用一个单调栈来维护前缀最大值，然后差分前缀和即可。

```cpp
const int N = 5005, M = 205;
ll d[N], b[M][N], ans, n, m;
int st[M][N], tp[M]; ll t[N], tans[N];
inline void add(int l, int r, ll k) { t[l] += k, t[r+1] -= k; }
int main() {
//	freopen ("hs.in","r",stdin);
	read(n), read(m);
	for (int i = 1;i < n; i++) read(d[i]);
	for (int i = 1;i <= n; i++) 
		for (int j = 1;j <= m; j++)
			read(b[j][i]);
	for (int i = 1;i <= m; i++) 
		st[i][tp[i] = 1] = n + 1, b[i][n + 1] = 1e15;
	for (int i = n;i >= 1; i--) {
		for (int j = 1;j <= m; j++) {
			ll *B = b[j]; int *St = st[j], &T = tp[j]; add(i, i, B[i]);
			while (B[St[T]] <= B[i]) add(St[T], St[T-1]-1, B[i] - B[St[T]]), T--;
			St[++T] = i;
		}
		add(i + 1, n, -d[i]);
		ll res = 0;
		for (int j = i;j <= n; j++)
			res += t[j], t[j] = 0, tans[j] += res, Mx(ans, tans[j]); 
	}
	write(ans);
	return 0;
}
```



---

## 作者：louhao088 (赞：10)

挺妙的一道题，感觉也不是很难但想了很久没想出来。


首先，我们选的必然是一个连续的线段，不然把中间的点选上一定不会变劣。

由于发现 $m$ 个物体其实是独立的，我们把考虑 $m$ 个物品分开来，对每个物品维护其在左边第一个比他大的位置 $L_i$ ，右边第一个大于等于他的位置 $R_i$ ，这个可以用单调栈来维护。那么起点为 $[L_i+1,i]$ ，终点为 $[i,R_i-1]$ 的线段对于这种物品的答案，一定是算这个位置的贡献。我们直接用二维差分统计即可。

注意一边取大于，另一边要取大于等于，不然会漏算。

复杂度 $O(n^2+nm)$ 



------------
代码如下

```cpp
// Problem: AT2289 [ARC067D] Yakiniku Restaurants
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2289
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 2022-06-02 14:36:35
// Author : louhao088

#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit(x) (x&-x)
#define int long long
const int maxn=5e3+5,M=34005;
inline int read(){
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x){
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,b[maxn],s[maxn][maxn],a[205][maxn],l[maxn],r[maxn],st[maxn],ans=0;
void add(int x,int y,int x2,int y2,int num){
	s[x][y]+=num;s[x2+1][y2+1]+=num;
	s[x2+1][y]-=num;s[x][y2+1]-=num;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();memset(s,0,sizeof s);
	for(int i=2;i<=n;i++)b[i]=b[i-1]+read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[j][i]=read();
	for(int i=1;i<=m;i++){
		memset(l,0,sizeof l);memset(r,0,sizeof r);int top=0;
		for(int j=1;j<=n;j++){
			while(top>0&&a[i][st[top]]<a[i][j])top--;
			l[j]=st[top];st[++top]=j;
		}
		top=1,st[top]=n+1;
		for(int j=n;j>=1;j--){
			while(top>1&&a[i][st[top]]<=a[i][j])top--;
			r[j]=st[top];st[++top]=j;
			add(l[j]+1,j,j,r[j]-1,a[i][j]);
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			s[i][j]+=s[i][j-1]+s[i-1][j]-s[i-1][j-1];
			if(i>j)continue;
			ans=max(s[i][j]-b[j]+b[i],ans);
		}
	cout<<ans<<endl;
 	return 0;
}

```


---

## 作者：小木虫 (赞：6)

### Preface  
神仙题，也是利用差分减少码量的一道题。  
### Problem  
有编号从 $ 1 $ 到 $ N $ 的 $ N $ 家烧烤店，烧烤店在一条线上按照编号顺序排序，第 $ i $ 家烧烤店与第 $ i + 1 $ 家烧烤店的距离是 $ A_i $ 。   
你有编号从 $ 1 $ 到 $ M $ 的 $ M $ 张烧烤券，不管是在哪一家烧烤店都可用烧烤券来吃烧烤，在第 $ i $ 家烧烤店用烧烤券 $ j $ 可以吃到一顿美味度为 $ B_{i,j} $ 的烧烤，每一张烧烤券只能使用一次，但是在一家烧烤店你可以使用任意多张烧烤券。  
你想从自己选择的一家烧烤店开始（随意选择一个开始），然后不断地用未使用的烧烤券去另一家烧烤店。你最终的幸福值是所吃所有烧烤的美味度减去所走的总路程。求最大可能的最终幸福值（ $ M $ 张券必须用完）。  
数据范围：
输入的数字都是整数。  
$ 2 \leq N \leq 5 \times 10^3 $  $ 1 \leq M \leq 200 $   $ 1 \leq A_i \leq 10^9 $  $ 1 \leq B_{i,j} \leq 10^9 $  
### Solution  
我们发现这个数据范围十分鬼畜，看起来不太像是传统的 $n\log n$ 复杂度。  
然后我们发现了一个性质：选一段内的烧烤店时只需要从一头走到另一头就是最短的走路路程。于是我们确定了一个子段内的走路长度，只需要最大化吃烧烤的快乐度就可以了。  
很显然可以搞出一个 $n^2m$ 的暴力，看起来很对。但是鬼畜的数据范围在这时又一次发挥了它的作用：这个复杂度是会超时的。  
看着 $n$ 的大小，我们肯定可以确定我们要搞出一个近似于 $n^2$ 复杂度的解法了，但是坏消息是：仅仅是枚举子段的复杂度就达到了 $n^2$。这让我们十分头疼，毕竟不太可能 $O(1)$ 统计吧！  
我们掏出一个惯用套路：固定子段的一头并把其看作常量，枚举另外一头，这个时候子段就最多只有 $n$ 了。  
在这里我们固定左端点并逐渐往左移动。  
然后我们发现了：往左移动一步之后会受到影响的是有一个烧烤卷的收益比这个端点小的子段。  
我们发现我们确实可以存下每个子段的每个烧烤卷在哪里用掉了。  
然后根据前面的分析，我们的操作应该是在固定左端点并枚举一种烧烤卷的情况下枚举使用贡献小于端点的烧烤店的子段并把它们的这种烧烤卷的使用地改为左端点。   
发现由于每个烧烤店能管到的子段只能是右端点在其之后的子段。这其实就是一个单调栈的流程，于是我们打出 $m$ 个单调栈。  

在上述流程中，扔掉烧烤店后还需要把所有在这个烧烤店买烧烤的子段全部换成左端点的贡献。思考一下什么情况子段会在一个烧烤店买烧烤？由于这是一个单调栈，所以从这个烧烤店开始到下一个在栈内的烧烤店，所有的点与目前左端点组成的子段都在这个烧烤店买烧烤，把这一段都给换成左端点贡献即可。  

每个点自己组成的子段直接就是当前所在烧烤店包场拿到的收益。  

直接在每个左端点处理完后枚举右端点取 $\max$ 更新答案即可。

上面的操作已经可以用线段树做了，但是我们并不甘心：“我推了这么久的东西你还要我再花时间打个线段树？这还是个不怎么优的带 $\log$ 解法？ ”   
欸，这个时候差分就要派上用场了！  
我们发现上述操作其实只有最后要拿到所有的元素，也就是说只询问一次，于是我们可以直接用一个差分数组来代替线段树来进行区间修改。  
code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5010;int now;
int n,m;int b[N][N];int a[N];
int ans;int Stack[N][N];int tot[N];int d[N];
void modify(int l,int r,int x){d[l]+=x;d[r+1]-=x;}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cin>>b[i][j];
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++){
			while(tot[j]>0&&b[Stack[j][tot[j]]][j]<=b[i][j]){
				if(tot[j]>1)
					modify(Stack[j][tot[j]],Stack[j][tot[j]-1]-1,b[i][j]-b[Stack[j][tot[j]]][j]);
				else modify(Stack[j][tot[j]],n,b[i][j]-b[Stack[j][tot[j]]][j]);
				tot[j]--;
			}
			modify(i,i,b[i][j]);Stack[j][++tot[j]]=i;
		}modify(i+1,n,-a[i]);now=0;
		for(int j=i;j<=n;j++)now+=d[j],ans=max(ans,now);
	}
	cout<<ans;
}
```


---

## 作者：鱼跃于渊 (赞：4)

一道很棒的决策单调性 dp。
## 1. 做法
我们首先可以注意到，最优解肯定会在一个区间 $[l,r]$ 之中，且不可能走回头路，那样一定不会更优。  
区间 $[l,r]$ 的答案如何求呢？首先 $l,r$ 两点之间的距离是一定要减去的。而对于烧烤券 $i$，我们可以找出一个 $k\in [l,r]$ 使得 $b_{k,i}$ 最大，这可以使用 ST 表优化，总查询复杂度是 $O(m)$。  
但是枚举所有的 $[l,r]$ 无疑复杂度是 $O(n^2m)$ 的，肯定要进行优化。  
于是我们很自然的就可以想到设 $f_i$ 为满足 $[j,i]$ 答案最大的 $j$，可以看出 $f$ 具有决策单调性，证明如下：  
设 $l$ 为 $f_r$，如果 $r$ 变成 $r+1$ 后 $l$ 往左移，则说明在距离变大的情况下，某个券的 $\max$ 发生了变化。而这种变化一定是 $l$ 移动带来的，也就是说它在 $r$ 不变时 $l$ 往左移也会发生，这样一来 $f_r$ 就不可能是 $l$，矛盾。  
既然有决策单调性，我们就可以考虑使用分治优化 dp，将时间复杂度降至 $O(nm\log n)$ 了。
## 2. 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+5,inf=-1e15;
int n,m,ans=inf,a[N],b[N][N];
int lg[N],st[205][30][N];
int f[N];
int query(int i,int l,int r){
	int k=lg[r-l+1];
	return max(st[i][k][l],st[i][k][r-(1<<k)+1]);
}
int query(int l,int r){
	int res=0;
	for(int i=1;i<=m;i++) res+=query(i,l,r);
	return res;
}
void solve(int l,int r,int L,int R){
	if(l>r) return;
	int mid=(l+r)>>1,mx=inf,p=0;
	for(int i=L,w;i<=min(mid,R);i++){
		w=query(i,mid)-(a[mid]-a[i]);
		if(w>mx){
			mx=w;p=i;
		}
	}
	ans=max(ans,mx);
	solve(l,mid-1,L,p);
	solve(mid+1,r,p,R);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=2;i<=n;i++){
		cin>>a[i];
		a[i]+=a[i-1];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>st[j][0][i];
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int k=1;k<=m;k++)
		for(int i=1;i<=lg[n];i++)
			for(int j=1;j+(1<<i)-1<=n;j++)
				st[k][i][j]=max(st[k][i-1][j],st[k][i-1][j+(1<<(i-1))]);
	solve(1,n,1,n);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Arghariza (赞：3)

萌萌题，给一个纯纯无脑做法。

不难发现题目即求：

$$\max\limits_{[l,r]\subseteq [1,n]}\left(\sum\limits_{p=1}^m\max\limits_{k=1}^n B_{k,p}-\sum\limits_{k=l}^{r-1}A_k\right)$$

$M=1$ 时的做法是熟知的。具体地，考虑扫描线，固定右端点 $r$，维护每个左端点 $l$ 到 $r$ 的答案值。考虑 $r\to r+1$，用**单调栈**维护 $\max\limits_{k=l}^rB_k$  的变化，将 $r+1$ 影响的 $[l_{\min},r]$ 后缀分成若干区间，然后变成区间加区间查最大值，线段树维护即可。

考虑 $M\neq 1$，直接大力开 $M$ 个单调栈，每次移动右端点 $r$ 时对于 $\forall p\in [1,M]$，维护$\max\limits_{k=l}^rB_{p,k}$ 的变化即可，修改次数均摊 $NM$。

复杂度 $O(NM\log N)$。

```cpp
const int N = 5e3 + 500;
const int M = 250;

int n, m, ans, a[N], b[N][M], st[N][M], tp[M];
struct seg { int mx, ad; } tr[N << 2];

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)

void pup(int x) { tr[x].mx = max(tr[ls].mx, tr[rs].mx); }
void pad(int x, int c) { tr[x].mx += c, tr[x].ad += c; }

void pdn(int x) {
    if (!tr[x].ad) return;
    pad(ls, tr[x].ad);
    pad(rs, tr[x].ad);
    tr[x].ad = 0;
}

void upd(int l, int r, int s, int t, int c, int x) {
    if (s <= l && r <= t) return pad(x, c);
    pdn(x);
    if (s <= mid) upd(l, mid, s, t, c, ls);
    if (t > mid) upd(mid + 1, r, s, t, c, rs);
    pup(x);
}

signed main() {
    n = rd(), m = rd();
    for (int i = 2; i <= n; i++) a[i] = rd();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            b[i][j] = rd();
    for (int i = 1; i <= n; i++) {
        if (i > 1) upd(1, n, 1, i - 1, -a[i], 1);
        for (int j = 1; j <= m; j++) {
            while (tp[j] && b[st[tp[j]][j]][j] < b[i][j])
                upd(1, n, st[tp[j] - 1][j] + 1, st[tp[j]][j], b[i][j] - b[st[tp[j]][j]][j], 1), tp[j]--;
            st[++tp[j]][j] = i, upd(1, n, i, i, b[i][j], 1);
        }
        ans = max(ans, tr[1].mx);
    }
    wr(ans);
    return 0;
}
```

---

## 作者：lzqy_ (赞：3)

~~啊？本来以为我的做法是标准做法来着（~~

一个不太一样的做法。

一个平凡的想法是枚举 $[l,r]$ 然后计算答案，预处理 RMQ 后这样做是 $O(n^2m)$ 的。

考虑优化。

设 $f_i$ 表示 $l=i$ 时最优的 $r$，容易发现这个 $f_i$ 是有单调性的。考虑右端点扩展到 $r+1$ 时，无论 $l$ 位于何处，花费的代价都是 $A_r$，而越大的 $l$ 越有可能更新到**相差更大**的幸福值。


于是就可以分治转移了。时间复杂度 $O(nm\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int maxn=5010;
const int maxm=210;
const ll inf=1ll<<60;
il int read(){
    int x=0;
    char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;   
}
ll pre[maxn];
int st[maxm][maxn][14];
int n,m,a[maxn];
int b[maxn][maxm];
int f[maxn];
int Que(int t,int l,int r){
    int Log=log2(r-l+1);
    return max(st[t][l][Log],st[t][r-(1<<Log)+1][Log]);
}
ll calc(int l,int r,ll sum=0){
    for(int i=1;i<=m;i++) sum+=Que(i,l,r);
    return sum-pre[r]+pre[l];
}
void init(){
    for(int t=1;t<=m;t++){
        for(int i=1;i<=n;i++) st[t][i][0]=b[i][t];
        for(int j=1;j<14;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                st[t][i][j]=max(st[t][i][j-1],st[t][i+(1<<j-1)][j-1]);
    }
}
void Solve(int l,int r,int L,int R){
    if(l>r) return ;
    int mid=l+r>>1;ll val=-inf;
    for(int i=max(L,mid);i<=R;i++)
        if(calc(mid,i)>val) f[mid]=i,val=calc(mid,i);
    Solve(l,mid-1,L,f[mid]);
    Solve(mid+1,r,max(mid+1,f[mid]),R);
}
int main(){
    n=read(),m=read();
    for(int i=2;i<=n;i++) 
        a[i]=read(),pre[i]=pre[i-1]+a[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            b[i][j]=read();
    init(),Solve(1,n,1,n);
    ll ans=-inf;
    for(int i=1;i<=n;i++)
        ans=max(ans,calc(i,f[i]));
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Jerryfish (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_arc067_d)

Upd.6.29.21:57 管理你能不能好好看看我到底是不是最优解。
## Simplify

不难想到其实题意就是让你求：

$$
\max_{1\le l\le r\le n}\left\{\sum_{i=1}^m\max_{l\le j\le r}\{b_{i,j}\}-\sum_{i=l}^ra_i\right\}
$$

## Solution
首先考虑暴力，我的话是枚举 $l,r(l\in[1,n],l\in[1,r])$，然后 $m$ 个单调队列先把 $l$ 到 $r$ 的 `b` 数组存进去，然后从 $1$ 到 $r$ 依次将超出范围的队头弹出维护最大值，$\sum_{i=l}^ra_i$ 就直接前缀和。

时间复杂度为 $O(n^2m)$，显然会炸，于是考虑优化。

枚举过程中保持单调不变的是 $r$，而 $l$ 会重复遍历……有重复的部分？

那么我们可以每次入完队后存一下这次的历史版本，以便在 $r+1$ 的时候可以免去“$m$ 个单调队列先把 $l$ 到 $r$ 的 `b` 数组存进去”这个操作。

但是任然解决不了问题。

想要将复杂度降下来，我们是不是可以考虑优化掉那个 $O(n)$ 的枚举 $l$，想想怎么才能把它优化掉……

简单，就是把每个 $1\le j\le m$ 的 $\max_{l\le i\le r}\{b_{i,j}\}$ 预处理出来，这样复杂度就降为 $O(n^2+nm)$，但是，怎么预处理呢？

再思考思考，我们会发现一些性质（~~废话~~），就是在枚举 $l$ 时单调队列的队头的 $b$ 值是成单调递减的，且第 $k$ 个队头 $l_k$ 是会从 $l_{k-1} + 1$ 保持到 $l_k$ 的，再通俗一点，在 $l$ 的遍历过程中，会有一段的最大值是不变的，再再再通俗一点，就是再一段区间里的最大值相等。

诶？差分！我们在 $l_k$ 和 $l_{k-1}$ 上进行差分，大概长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ko9di3d1.png)

这样就好做多了，但是一个新的 $r$ 入队时有可能会让这张图顶上的即队尾的几个 $l$ 弹出，那我们用丹钓战维护啊（况且这图也像个丹钓战），在弹出过程中更改一下当前队尾的差分数组（减去 $b_{l_k,j}-b_{l_{k+1},j}$（本来是设为 $0$，但是维护的是整个 $m$ 行的差分，所以不能设为 $0$）），出队出完了之后了的队尾要加上 $b_{l_{p+1},j}-b_{r,j}$（不是变为 $b_{l_p,j}-b_{r,j}$ 的原因与上面的同理）。~~单调队列什么的丢掉。~~

我们需要预处理的 $\max_{l\le i\le r}\{b_{i,j}\}$ 即为这个差分数组的前缀和。

这不就做完了吗。

顺便最优解。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int N = 5005, M = 205;
 
inline char nc(){ static char buf[1000000],*p=buf,*q=buf; return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++; } inline int read(){ int res = 0; char c = nc(); while(c<'0'||c>'9')c=nc(); while(c<='9'&&c>='0')res=res*10+c-'0',c=nc(); return res; }  
 
int n, m;
int b[N][M], q[N][M], top[M];
ll d[N], sum[N], ans, a[N];//不开 long long 见祖宗
 
int main(){
	n = read(); m = read();
	for (int i = 2; i <= n; ++ i ) a[i] = read(), a[i] += a[i - 1];
	for (int i = 1; i <= n; ++ i ) 
		for (int j = 1; j <= m; ++ j ) 	
			b[i][j] = read();
	
	for (int r = 1; r <= n; ++ r ) {
		for (int j = 1; j <= m; ++ j ) {
			int last = 0; //last 就是b[l[k+1]][j]
			while(top[j] && b[q[top[j]][j]][j] < b[r][j]) {
//			if(r == 2)cout << d[q[top[j]][j]] << endl;
				d[q[top[j]][j]]	-= 1ll * (b[q[top[j]][j]][j] - last);
				last = b[q[top[j] -- ][j]][j];
			}
			d[q[top[j]][j]] -= 1ll * (b[r][j] - last); 
			q[ ++ top[j]][j] = r; 
			d[q[top[j]][j]] += 1ll * b[r][j];
        //刚刚的差分
		}
		for (int l = r; l >= 1; -- l ) {
			sum[l] = sum[l + 1] + d[l];
//			cout << l << " " << r << "->" << d[l] << endl;
			ans = max(ans, sum[l] - a[r] + a[l]);
		}
	} 
    printf("%lld", ans);
// 	fwrite(obuf,p3-obuf,1,stdout);
	return 0;
}
```

---

## 作者：harmis_yz (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/9zpicw3e)。

没想到还能单调栈啊。

## 分析

枚举区间 $[l,r]$，得到每张烧烤券的最优位置，然后取最大价值。这个的时间复杂度是 $O(n^2m)$，难以接受。

考虑换个角度思考。我们还是去枚举 $l$，记 $q_i$ 为区间 $[l,n]$ 中最大的一个 $b_{j,i}$ 的位置。那么 $r=\max\limits_{i=1}^{m} q_i$。不难发现，随着 $l$ 的减小，$q_i$ 不增。同理可得 $r$ 不增。将 $r$ 视作 $l$ 的最优决策点，记为 $p_l$。那么有：$p_i \ge p_{i-1}(2 \le i \le n)$。

然后由于决策点有单调性，就能分治求解了。没学过的可以看[这里面对 CF321E 的讨论](https://www.luogu.com.cn/article/3yyu431w)。那么求所有点的最优决策点的复杂度就是 $O(nm\log^2 n) - O(nm\log n)$ 了。最后再对每对 $(l,p_l)$ 求一个最大价值即可。

## 代码

```cpp
il int query(int x,int l,int r){
	int k=_log[r-l+1];
	return max(f[x][l][k],f[x][r-(1ll<<k)+1][k]);
}
il int get(int l,int r){
	int sum=-(a[r]-a[l]);
	for(re int i=1;i<=m;++i) sum+=query(i,l,r);
	return sum;
}
il void work(int l,int r,int L,int R){
	L=max(L,l);
	int mid=l+r>>1;
	int Max=-1e18,id=mid;
	for(re int i=max(L,mid);i<=R;++i)
		if(get(mid,i)>Max) Max=get(mid,i),id=i;
	if(l==r) return p[l]=id,void(0);
	work(l,mid,L,id),work(mid+1,r,id,R);
}
```

---

## 作者：Zelotz (赞：1)

首先考虑暴力。$\mathcal O(n^2m)$ 枚举左右两个端点，再贪心地选其中 $M$ 张票的美味度最大那一家餐馆。复杂度不可接受，但是不难感觉到正解应该是 $\mathcal O(n^2)$ 的。

考虑枚举左端点 $i$，对于当前左端点，记每一个右端点 $j$ 的答案为 $now_j$，若暂时不考虑距离，大部分 $now_j$ 会从 $i + 1$ 继承过来，而少量的 $now_j$ 则会因为 $[i+1,j]$ 中选择的最大值比 $i$ 这个餐馆小而变大。

发现这是一个类似单调栈的过程，$M$ 张票互相独立。对于每一张票，若其选择的餐馆编号在 $i$ 之后，且美味度小于 $i$则其没有意义（选择编号更小的且美味度更大的显然更好）。那么弹出栈顶元素 `sk[top]`，发现编号为 `sk[top]` 至 `sk[top-1]-1` 的点都原本选择 `sk[top]` 作为餐馆，而现在全都选择 $i$ 号餐馆。于是差分维护变化量即可。

```
const int N = 5e3 + 5, M = 205;
ll b[M][N], a[N], d[N];
void add(int l, int r, int k) {d[l] += k, d[r + 1] -= k;}
int sk[M][N]; int top[M];
ll n, m, ans, now[N];
signed main() 
{
    cin >> n >> m;
    R(i, 1, n - 1) cin >> a[i];
    R(i, 1, n)
        R(j, 1, m) cin >> b[j][i];
    R(i, 1, m) sk[i][0] = n + 1;
    for (int i = n; i; --i)
    {
        R(j, 1, m)
        {
            now[i] += b[j][i];
            while (top[j] && b[j][sk[j][top[j]]] <= b[j][i]) add(sk[j][top[j]], sk[j][top[j] - 1] - 1, b[j][i] - b[j][sk[j][top[j]]]), --top[j];
            sk[j][++top[j]] = i;
        }
        add(i + 1, n, -a[i]);
        ll tmp = 0;
        R(j, i, n)
        {
            tmp += d[j]; d[j] = 0;
            now[j] += tmp; ans = max(ans, now[j]);
            // cout << i << ' ' << j << ' ' << d[j] << ' '<< tmp << ' ' << now[j] << '\n';
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：xuantianhao (赞：1)

# [Yakiniku Restaurants](https://www.luogu.com.cn/problem/AT_arc067_d)

明显在最优方案中，行走方式一定是从一条线段的一端走到另一端，不回头。

于是设 $f[i,j]$ 表示从 $i$ 走到 $j$ 的最优代价。明显，该代价对于不同的券相互独立。故我们依次考虑每一张券。

我们发现，假设有一张位置 $k$ 的券，则所有 $k\in[l,r]$ 的 $[l,r]$ 都是可以享受到它的。于是，我们建出笛卡尔树来，就可以把它用差分轻松解决了（假设笛卡尔树上有一个节点 $x$，它是区间 $[l,r]$ 中的最大值，则所有区间 $[l,r]$ 中穿过它的区间都会增加 $a_x$，但是它的两个子区间 $[l,x-1]$ 和 $[x+1,r]$ 却享受不到，故在该处再减少 $a_x$，即可实现差分地更新。

则时间复杂度 $O(nm+n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+100;
int n,m,tp,res;
int a[210][N],stk[N],l[N],r[N],s[N],f[N][N];
void solve(int id,int x,int L,int R,int las){
    f[L][R]+=a[id][x]-las;
    if(L==R) return;
    if(l[x]) solve(id,l[x],L,x-1,a[id][x]);
    if(r[x]) solve(id,r[x],x+1,R,a[id][x]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=2;i<=n;i++){
		cin>>s[i];
		s[i]+=s[i-1];
	}
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[j][i];
    for(int i=1;i<=m;i++){
        tp=0;
        for(int j=1;j<=n;j++){
            l[j]=r[j]=0;
            while(tp&&a[i][stk[tp]]<=a[i][j]) l[j]=stk[tp--];
            if(stk[tp]) r[stk[tp]]=j;
            stk[++tp]=j;
        }
        solve(i,stk[1],1,n,0);
    }
    for(int i=1;i<=n;i++)for(int j=n;j>=i;j--) f[i][j]+=f[i-1][j]+f[i][j+1]-f[i-1][j+1];
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++) res=max(res,f[i][j]-(s[j]-s[i]));
    cout<<res;
    return 0;
}
```


---

## 作者：chenxia25 (赞：1)

**[Portal](https://www.luogu.com.cn/problem/AT2289)**

固定了最左边到达的烧烤店和最右边之后，最右策略显然是从左往右走一遍，然后每个 ticket 用在 happiness 最大的那个商店。于是不难得到一个 $\mathrm O\!\left(n^2m\right)$ 的暴力：暴力枚举区间，每个区间算出每个 ticket 的最大 happiness。

如果直接想用甚么 DS 维护上述操作的话，那我想不到什么方法。我们注意到这是又一道的算贡献题，每个区间的答案是由走路代价和 $m$ 种 ticket 的代价共同贡献的。走路代价太好求了；我们考虑换贡献体：换成 ticket。

对于每个 ticket，我们考虑它在 $1\sim n$ 的每一种取值能影响到哪些区间。显然能影响到一个区间当且仅当它在里面最大（这里涉及到有多个最大值的问题，于是可以使用惯用套路：左边严格，右边不严格来去重）。而这些区间显然是左端点构成一个区间，右端构成一个区间，这些区间的左 / 右端点非常好求，二分 / BIT 均可，单调栈可以做到不带 log。然后就是个二维差分把它贡献到区间们上去的事情了（在这一点上我 dd 了 tzc，没有我的提醒他只知道二维线段树（））。

复杂度 $\mathrm O(n(n+m))$。

**_[code](https://www.luogu.com.cn/paste/aungshld)_**

然后听说还有包括但不限于四边形不等式的其他方法们？考虑以后补？

---

## 作者：Ebola (赞：1)

### 題目大意

你手中有若干張餐券，每張餐券在不同的飯館用會有不同的收益，飯館排成一排，你在飯館之間行走會付出一些代價，代價為你走的路徑長度，你要選擇若干個飯館使用這些餐券（不一定用完），使得净收益最大。

### 題解

大概轉化一下，其實就是要選擇一個包含若干個連續飯館的綫段，將餐券全部用出去（顯然每張餐券都要用在這個區間中收益最大的飯館裏面），代價就是綫段長度

如果直接枚舉綫段，然後枚舉每張餐券並判斷用在哪個飯館，複雜度O(n³m)

枚舉綫段這條路沒什麽可優化的空間，不如考慮B(i,j)會對哪些決策區間有貢獻

對於每一個B(i,j)，我們找到一個x，滿足x<i，并且B(x,j)>B(i,j)；找到一個y，滿足y>i，并且B(y,j)>B(i,j)，那麽B(i,j)對答案有貢獻，顯然是要求決策左端點位於x+1~i中，決策右端點位於i~y-1中，因爲在這樣的區間中，如果要用第j張餐券，顯然是要選擇第i家飯館才能收益最大

於是我們設二維數組f(l,r)表示決策區間為(l,r)時的收益，對於每個B(i,j)，我們就給f(x+1~i,i~y-1)中的所有點加上B(i,j)。容易證明，對於一張餐券j，B(1~n,j)對答案貢獻的矩陣，兩兩之間沒有任何交集。這個步驟可以利用二維差分來解決，全部加完之後一個二重循環將f數組還原出來

那麽現在就可以枚舉綫段了，收益已經算好了，而綫段長度可以通距離的前綴和O(1)求出。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef long long LL;
const int N=5010,M=210;
int L[M][N],R[M][N];
int B[M][N],n,m;
int stk[N],w[N],top;
LL a[N],mat[N][N];

int main()
{
    n=read();m=read();
    for(int i=2;i<=n;i++)
        a[i]=a[i-1]+read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            B[j][i]=read();
    for(int i=1;i<=m;i++)
    {
        top=0;
        for(int j=1;j<=n;j++)
        {
            while(top&&w[top]<B[i][j]) top--;
            L[i][j]=top?stk[top]+1:1;
            stk[++top]=j;w[top]=B[i][j];
        }
        top=0;
        for(int j=n;j>=1;j--)
        {
            while(top&&w[top]<B[i][j]) top--;
            R[i][j]=top?stk[top]-1:n;
            stk[++top]=j;w[top]=B[i][j];
        }
        for(int j=1;j<=n;j++)
        {
            mat[L[i][j]][j]+=B[i][j];
            mat[L[i][j]][R[i][j]+1]-=B[i][j];
            mat[j+1][j]-=B[i][j];
            mat[j+1][R[i][j]+1]+=B[i][j];
        }
    }
    LL ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) mat[i][j]+=mat[i][j-1];
        for(int j=1;j<=n;j++) mat[i][j]+=mat[i-1][j];
        for(int j=i;j<=n;j++) ans=max(ans,mat[i][j]-a[j]+a[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：OtterZ (赞：0)

# 0.前言

## 1.涉及知识点：

1. 二分（普及）
2. `ST` 表；（提高）
3. 单调队列；（提高）
4. 决策点单调性证明（不明）

## 2.优势

1. 代码较快，无需卡常；
2. 原理简单，易于想到；
3. 套路性强，核心算法类似于四边形不等式优化 `ID` 类方程方法。

# 1.题意

已知 $N$ 家烧烤店，$M$ 张消费券，第 $i$ 家烧烤店与第 $i + 1$ 家烧烤店距离为 $a_i$，在第 $i$ 家烧烤店花第 $j$ 张消费券可以得到美味度 $b_{i,j}$ 的美食，问在花完 $M$ 张消费券的情况，食品的美味度之和减去路程最小为多少？

# 2.三个贪心结论

## 1.从左往右走

这样路程最短，结论显然。

## 2.每张券买最美味的食物

当我们确定开始（最左边）的位置和结尾（最右边）的位置时，对于每张券，我们选其中能得到最美味的食物的烧烤店总是最好的，此结论也显然。

## 3.对于每个店，当这个店为结尾时，开始的点的编号单调不减

这个结论是得到核心解法的关键。

我们只需证明对于 $j > j'$ 而且区间贡献 $f(j,i) > f(j',i)$，则有 $\forall k \ge i,f(j,k) > f(j',k)$。

证明如下：

据结论 $1$、结论 $2$，我们得到 $f(j,i) = \sum_{x = 1} ^ M \max_{y = j}^{i} b_{y,x} - \sum_{x = j}^{i - 1} a_x$。

对于 $\forall 1 \le x \le M, \max_{y = j}^{i} b_{y,x} \le \max_{y = j'}^{i} b_{y,x}$，得 $\forall 1 \le x \le M,\max_{y = j}^{k} b_{y,x} - \max_{y = j}^{i} b_{y,x} \ge \max_{y = j'}^{k} b_{y,x} - \max_{y = j'}^{i} b_{y,x}$，知 $\sum_{1 \le x \le M}\max_{y = j}^{k} b_{y,x} - \max_{y = j}^{i} b_{y,x} \ge \sum_{1 \le x \le M}\max_{y = j'}^{k} b_{y,x} - \max_{y = j'}^{i} b_{y,x}$，故 $\forall k \ge i,f(j,k) - f(j,i) > f(j',k) - f(j',i)$，又有 $f(j,i) > f(j',i)$，故 $\forall k \ge i,f(j,k) > f(j',k)$。

由此得出结论 $3$ 成立。

# 基于三个结论得到的算法

首先处理以每家店，最有的开始节点。

我们用单调队列存每个可能从这家店开始的店的下标 $x_i$ 和对应最小的结束店 $l_i$ 使目前遍历到的点中从这家店到那家点最优，对于新加入的起点 $y$，我们进行两步：

1. 对于队尾元素 $i$，若 $f(y,l_i) >f(x_i,l_i)$ 的情况，将队尾删除。
2. 接下来二分得到 $l_y$，然后将 ($x_y,l_y$) 加入队尾。
3. 最后删除队首，直到队首的影响区间包含 $y$，记录得 $x_y$ 的最优开头。

最终枚举结尾，得到答案。

实现时用 `ST` 表预处理 $\forall 1 \le x \le M,\max_{y = j}^{i} b_{y,x}$，就能得到一个 $NM\log N$ 的解法。

# 代码


```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,a[5009],b[209][5009][16],top,st[5009],l[5009],p[5009],lock;
long long s[5009];
void ST_init(){
	for(int k = 1; k <= m; k ++)
		for(int j = 1; (1 << j) <= n; j ++)
			for(int i = 1; i + (1 << j) - 1 <= n; i ++)
				b[k][i][j] = max(b[k][i][j - 1],b[k][i + (1 << j - 1)][j - 1]);
}
int query(int j,int l,int r){
	int k = log2(r - l + 1) + 1e-6;
	return max(b[j][l][k],b[j][r - (1 << k) + 1][k]);
}
bool check(int x,int y,int z){
	long long ret1 = s[x] - s[z],ret2 = s[y] - s[z];
	for(int j = 1; j <= m; j ++){
		ret1 += query(j,x,z);
		ret2 += query(j,y,z);
	}
	return ret1 > ret2;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i < n; i ++)
		scanf("%d",&a[i]),s[i + 1] = s[i] + a[i];
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%d",&b[j][i][0]);
	ST_init();
	st[++top] = 1;
	l[top] = 1;
	p[1] = 1;
	lock = 0;
	for(int i = 2; i <= n; i ++){
		bool flg = false;
		while(top > 0 && l[top] >= i && check(i,st[top],l[top]))
			top --,flg = true;
		int lf = max(i - 1,l[top]),r = flg ? l[top + 1] : n + 1;
		while(lf + 1 < r){
			int mid = (lf + r + 1) >> 1;
			if(check(i,st[top],mid))
				r = mid;
			else
				lf = mid;
		}
		if(r <= n){
			top ++;
			st[top] = i;
			l[top] = r;
		}
		while(top - lock > 1 && l[lock + 2] <= i)
			lock ++;
		p[i] = st[lock + 1];
	}
	long long ans = 0;
	for(int i = 1; i <= n; i ++){
		long long ret = s[p[i]] - s[i];
		//printf("%d\n",p[i]);
		for(int j = 1; j <= m; j ++){
			ret += query(j,p[i],i);
		}
		ans = max(ans,ret);
	}
	printf("%lld\n",ans);
} 
```

+ 时间：$549 \text { ms}$。
+ 空间：$64776 \text { KB}$。
+ 码量：$68$ 行，$1691 \text{ Byte}$。

---

## 作者：Cry_For_theMoon (赞：0)

明明有两种做法怎么我看题解区 6 篇题解都是同一做法的（乐）

------

直接枚举 $l,r$ 然后求 $m$ 个餐券的最大值是难处理的。

考虑设 $f_i$ 是 $r=i$ 时令答案最大的 $l(\le i)$。

**结论：$f$** 是单调的。

证明：如果 $r\rightarrow r+1$ 的时候 $l$ 左移了，显然距离会变大，而答案还要比 $l$ 不变来的大，所以肯定有 $\max$ 发生了变化。而这个变化当 $r$ 没有拓展的时候，直接左移 $l$ 也会发生，而且距离还变小了。所以 $l$ 就不是 $r$ 的最优解，矛盾。

然后就是分治地进行决策单调性 dp。如果我们要求 $f_{l\sim r}$，已经知道了值域为 $x\sim y$，可以在值域上暴力求 $f_{mid}$，然后根据单调性来分治（值域也会被分治）。

注意到这个东西不能保证单次复杂度和 $r-l+1$ 有关，但是一共分成 $\log n$ 层，每层 $y-x+1$ 的和都是 $O(n)$ 的，所以总复杂度 $O(n\log n)$。又因为你每次更新都要花 $O(m)$ 的时间查一下 $m$ 个数列的 rmq，所以复杂度是 $O(nm\log n)$ 的。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const ll MAXN=5e3+10,MAXM=210,INF=1e18;
ll n,m,d[MAXN];
ll b[MAXM][MAXN],logn[MAXN];
ll ans=-INF;
struct ST{
    ll maxn[MAXN][20];
    void build(ll* a){
        rep(i,1,n)maxn[i][0]=a[i];
        rep(i,1,19)rep(j,1,n){
            if(j+(1<<i)-1>n)break;
            maxn[j][i]=max(maxn[j][i-1],maxn[j+(1<<(i-1))][i-1]);
        }
    }
    ll qry(int L,int R){
        int len=logn[R-L+1];
        return max(maxn[L][len],maxn[R-(1<<len)+1][len]);
    }
}st[MAXM];
ll qry(int L,int R){
    ll ret=0;
    rep(j,1,m)ret+=st[j].qry(L,R);
    return ret;
}
void solve(int l,int r,int x,int y){
    if(l>r)return;
    int mid=(l+r)>>1;
    ll pos=0,val=-INF;
    rep(i,x,min(y,mid)){
        ll ret=qry(i,mid)-(d[mid]-d[i]);
        if(ret>val){
            pos=i;val=ret;
        }
    }
    ans=max(ans,val);
    solve(l,mid-1,x,pos);
    solve(mid+1,r,pos,y);
}
int main(){
    logn[0]=-1;rep(i,1,5000)logn[i]=logn[i>>1]+1;
    ios::sync_with_stdio(false);
    cin>>n>>m;
    rep(i,2,n)cin>>d[i],d[i]+=d[i-1];
    rep(i,1,n)rep(j,1,m)cin>>b[j][i];
    rep(j,1,m)st[j].build(b[j]);
    solve(1,n,1,n);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：xcyle (赞：0)

提供一种新的方法

对于每一行，考虑每个位置的贡献，它的形式是：

- 设$L_i$为$i$左边第一个大于它的值的位置，$R_i$为$i$左边第一个大于它的值的位置。则所有左端点在$L_i - i$和右端点在$i-R_i$的区间都会以它为最大值

显然这样统计的所有区间是不重不漏的

再考虑统计原问题的答案

考虑枚举区间的左端点，对于不同的右端点，建线段树

那么上述贡献方式显然可以化为“区间的区间加”，外层差分，内层线段树即可

时间复杂度$O(nm\log n)$

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
#define maxn 5005
#define maxm 205
#define N 20005
using namespace std;
const long long INF = 1e17;
int n, m, L[maxn], R[maxn];
long long a[maxn], b[maxm][maxn];
struct node
{
	int l, r;
	long long data;
};
vector<node> p[maxn];
int stack[maxn], top;
long long sum[maxn];
long long t[N], tag[N];
void build(int x, int l, int r)
{
	if(l == r)
	{
		t[x] = -sum[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(lc(x), l, mid);
	build(rc(x), mid + 1, r);
	t[x] = max(t[lc(x)], t[rc(x)]);
}
inline void pushdown(int x)
{
	tag[lc(x)] += tag[x];
	tag[rc(x)] += tag[x];
	t[lc(x)] += tag[x];
	t[rc(x)] += tag[x];
	tag[x] = 0;
}
void change(int x, int l, int r, int a, int b, long long data)
{
	if(a <= l && r <= b)
	{
		tag[x] += data;
		t[x] += data;
		return;
	}
	pushdown(x);
	int mid = (l + r) >> 1;
	if(a <= mid) change(lc(x), l, mid, a, b, data);
	if(b > mid) change(rc(x), mid + 1, r, a, b, data);
	t[x] = max(t[lc(x)], t[rc(x)]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%lld", &b[j][i]);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		b[i][0] = b[i][n + 1] = INF;
		stack[top = 1] = 0;
		for (int j = 1; j <= n; j++)
		{
			while(b[i][stack[top]] <= b[i][j]) top--;
			L[j] = stack[top] + 1;
			stack[++top] = j;
		}
		stack[top = 1] = n + 1;
		for (int j = n; j >= 1; j--)
		{
			while(b[i][stack[top]] < b[i][j]) top--;
			R[j] = stack[top] - 1;
			stack[++top] = j;
		}
//		printf("\n");
		for (int j = 1; j <= n; j++)
		{
			p[L[j]].push_back({j, R[j], b[i][j]});
			p[j + 1].push_back({j, R[j], -b[i][j]});
//			printf("%d %d\n", L[j], R[j]);
		}
	}
	build(1, 1, n);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < p[i].size(); j++)
		{
			change(1, 1, n, p[i][j].l, p[i][j].r, p[i][j].data);
		}
		ans = max(ans, t[1]);
		change(1, 1, n, 1, n, a[i + 1]);
		change(1, 1, n, i, i, -INF);
	}
	printf("%lld", ans);
	return 0;
}
```

---

