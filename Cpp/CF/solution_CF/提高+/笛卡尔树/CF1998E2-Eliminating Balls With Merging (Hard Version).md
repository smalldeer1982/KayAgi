# Eliminating Balls With Merging (Hard Version)

## 题目描述

喝水。     
—— 孙武，《成为一名健康程序员的艺术》

这是这个问题的更难的版本。唯一的区别是在这个版本中 $x = 1$。你必须破解这两个版本才能破解。

你被给定了两个整数 $n$ 和 $x$ ( $x = 1$ )，有 $n$ 个球排成一排，从左到右从 $1$ 到 $n$ 编号。最初，在第 $i$ 个球上写了一个值 $a_i$。

对于从 $1$ 到 $n$ 的每一个整数 $i$，我们定义函数 $f(i)$ 如下：

+ 假设你有一个集合 $S = \{1, 2, \ldots, i\}$。
+ 对于每一次操作，你需要从 $S$ 中选择出一个整数 $l$ $(1 \le l < i)$，使得 $l$ 不是 $S$ 中的最大元素。假设 $r$ 是 $S$ 中比 $l$ 大的最小元素。    
	+ 如果 $a_l > a_r$，你把 $a_l$ 赋值为 $a_l + a_r$，然后将 $r$ 从 $S$ 中移除
    + 如果 $a_l < a_r$，你把 $a_r$ 赋值为 $a_l + a_r$，然后将 $l$ 从 $S$ 中移除
    + 如果 $a_l = a_r$，你可以在 $l$ 和 $r$ 任意选一个移出 $S$：
    	+ 如果 你选择把 $l$ 从 $S$ 中移除，你需要 $a_r$ 赋值为 $a_l + a_r$，然后将 $l$ 从 $S$ 中移除。
        + 如果 你选择把 $r$ 从 $S$ 中移除，你需要 $a_l$ 赋值为 $a_l + a_r$，然后将 $r$ 从 $S$ 中移除。
+ $f(i)$ 表示整数 $j$ $(1 \le j \le i)$ 的个数，使得在执行上述运算 $i − 1$ 次后可以得到 $S = \{ j \}$。

对于每一个整数 $i$ 从 $x$ 到 $n$，你需要找到 $f(i)$。

## 说明/提示

对于第一组数据，下面是对于每个 $1$ 到 $n$ 的 $i$，$j$ 可以取到的所有数值：

+ 对于 $f(1)$，$j$ 只能取 $1$。
+ 对于 $f(2)$，$j$ 只能取 $2$。
+ 对于 $f(3)$，$j$ 能取 $2$ 和 $3$。
+ 对于 $f(4)$，$j$ 能取 $2$ 和 $3$。
+ 对于 $f(5)$，$j$ 能取 $2$，$3$ 和 $4$。

## 样例 #1

### 输入

```
3
5 1
1 2 3 2 1
7 1
4 5 1 2 1 4 5
11 1
1 2 3 1 1 9 3 2 4 1 3```

### 输出

```
1 1 2 2 3
1 1 1 1 1 3 4
1 1 2 2 2 1 1 1 3 3 4```

# 题解

## 作者：灵乌路空 (赞：7)

枚举，分治，笛卡尔树。

我有一个极其优美的笛卡尔树做法！而且跑得飞快！前置知识：[该题 Easy Version 的笛卡尔树解法](https://www.luogu.com.cn/article/6w2tilfv)。

同样考虑笛卡尔树。一个显然的想法是在线性建笛卡尔树过程中，对于每个前缀对应的笛卡尔树套用 Easy Version 的做法，但是总时间复杂度变 $O(n^2)$ 了过不去。

于是考虑细致地观察 E1 中做法得到的合法位置，在笛卡尔树中呈现什么形态：
- 一定是以笛卡尔树根为根的，连通的树形的**连通块**；
- 每对连通的父子节点间满足：子节点对应区间之和，**不小于**父节点对应的最值。
- 答案即为该连通块的大小。

考虑在线性建立笛卡尔树过程中，维护上述以笛卡尔树根为根的，连通的树形的连通块。线性建立笛卡尔树过程中实际上是在**维护笛卡尔树的右链**，则容易发现，每次新增一个节点时，仅会影响右链上连通块的形态，已遍历过的左侧部分完全不会受影响，于是**仅需考虑每次加点对右链上的连通性的影响**。

**连通**性实际上即区间之和与父节点对应最值的**大小**关系，又区间之和仅会单调递增，加点过程中不会出现失去连通性的情况，于是考虑使用并查集维护连通性，当某个子节点区间之和大于父节点对应最值时，则将它们 merge 起来，并记 merge 后祖先为子节点，也即对应**右链上深度较深的节点**。

然后基于上述分析，考虑在建树过程中加入 $a_i$ 时如何维护右链：
- 为保证右链的性质，先将右链上小于 $a_i$ 的点全部弹出。
- 检查是否有 $a_i$ 的**左儿子** $\operatorname{lson}$ 对应区间和不小于 $a_i$，若是则将 $\operatorname{lson}$ 与 $i$ merge 起来。
- 此时右链上所有节点对应区间之和均会增大 $a_i$，考虑直接**从根暴力下跳右链上的连通块**，在此过程中检查相邻连通块之间，是否有子节点对应区间之和不小于父节点对应的最值，若是则可以建立它们之间的连通性，将他们 merge 起来即可。

可以证明：并查集合并后，右链上相邻的连通块 $(u, v)$ 之间一定有：$v$ 的顶部节点对应区间和**小于** $u$ 的底部节点最值 $a_u$。则可知右链上连通块的个数一定不会超过 $O(\log_2 v)$ 级别，当且仅当右链上最值形如：$2^0 \rightarrow 2^1 \rightarrow 2^2\rightarrow \cdots \rightarrow 2^{\log_2 v}$ 时达到上界。则每次暴跳更新右链信息的复杂度上界仅为 $O(\log v)$ 级别，

此时直接查询根节点所在连通块大小即为答案。

总复杂度 $O(n\log v)$ 级别，但是常数超级小跑得飞快：[https://codeforces.com/contest/1998/submission/275684758](https://codeforces.com/contest/1998/submission/275684758)。

```cpp
//
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 2e5 + 10;
const LL kInf = 1e18 + 2077;
//=============================================================
int n, x, ans[kN];
LL a[kN], sum[kN];
int fa[kN], sz[kN], son[kN][2];
int top, st[kN];
//=============================================================
int find(int x_) {
  return (fa[x_] == x_) ? (x_) : (fa[x_] = find(fa[x_]));
}
void merge(int u_, int v_) {
  int fu = find(u_), fv = find(v_);
  if (fu == fv) return ;
  fa[fu] = fv;
  sz[fv] += sz[fu];
}
//=============================================================
int main() {
  // freopen("1.txt", "r", stdin);
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int T; std::cin >> T;
  while (T --) {
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++ i) {
      std::cin >> a[i];
      sum[i] = sum[i - 1] + a[i];
    }
    a[0] = a[n + 1] = kInf;
    for (int i = 0; i <= n; ++ i) {
      son[i][0] = son[i][1] = ans[i] = 0;
      fa[i] = i, sz[i] = 1;
    }
    st[top = 0] = 0;
    for (int i = 1; i <= n; ++ i) {
      while (top && a[st[top]] < a[i]) -- top;
      son[i][0] = son[st[top]][1], son[st[top]][1] = i;

      if (son[i][0] && sum[i - 1] - sum[st[top]] >= a[i]) merge(son[i][0], i);
      st[++ top] = i;
      
      int f = find(st[1]), u = son[f][1];
      while (u) {
        if (sum[i] - sum[f] >= a[f]) merge(f, u);
        f = find(u), u = son[f][1];
      }
      ans[i] = sz[find(st[1])];
    }

    for (int i = 1; i <= n; ++ i) std::cout << ans[i] << " ";
    std::cout << "\n";
  }
  return 0;
}
```

---

## 作者：ifffer_2137 (赞：6)

校内 NOIP 模拟赛搬的题，~~是放在 T2 的 \*2500~~。

@IceKylin 有高贵 $O(n)$ 做法，~~但事实上他自己都分析不动复杂度~~。
### 题意
~~有点长就不贴了~~。
### 分析
我们先考虑 E1 的情形。

我们现在想要快速判定一个数能否最后留下，先看一下最大值，你发现它必胜；然后再看一下次大值，你发现只要它把自己身边小于等于自己的全吃掉后能吃掉最大值那么它也能留下；然后数值再往下也同理……你发现一个数能留下有两种情况：

1.它是最大值。

2.它把自己身边所有小于等于自己的全吃掉后能吃掉一个**已经确定能留下的数**。

显然在第二种情况中它只可能吃掉自己左/右边第一个大于自己的数，记为 $L_i,R_i$。这个东西我们可以先用单调栈求一下，然后按数值从大到小枚举每个数，按上述方法判断即可。

然后考虑 E2 的情形，要对于每个前缀求一遍，复杂度爆炸。显然每个数的贡献作用于一段区间，于是你可以考虑维护每个数的贡献区间然后差分统计答案。

我们还是按数值从大到小转移，只不过这次转移的是区间。首先第 $i$ 个数的区间为 $[i,n]$，然后你再交上一些东西：

如果 $i$ 先往左吃到 $L_i+1$，再往右至少吃到 $x$ 后大于 $a_{L_i}$，其中要求 $x\leq R_i-1$，那么区间就可以与 $[\max(x,l_{L_i}),r_{L_i}]$ 取交，$x$ 可以通过二分简单求出。

同理可以从 $R_i$ 的区间类似转移，当然还要考虑 $i$ 恰为前缀最大值的情况。注意区间的交与并。

时间复杂度 $O(n\log n)$，具体实现见代码。
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
const int maxn=1e6+5;
int T;
int n,X;
int a[maxn],s[maxn],p[maxn];
int stk[maxn],tp;
int L[maxn],R[maxn];
int x[maxn],y[maxn];
bool cmp(int x,int y){return a[x]>a[y];}
int getpos(int x){
	int l=x+1,r=R[x]-1,pos=n+1;
	while(l<=r){
		int m=(l+r)>>1;
		if(s[m]-s[L[x]]>=a[L[x]]){
			pos=m;
			r=m-1;
		}else{
			l=m+1;
		}
	}
	return pos;
}
int ans[maxn];
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read(),X=read();
		for(int i=1;i<=n;i++){
			ans[i]=0;x[i]=0,y[i]=n+1;
			a[i]=read();p[i]=i;
			s[i]=s[i-1]+a[i];
			L[i]=0,R[i]=n+1;
		}
		tp=0;
		for(int i=1;i<=n;i++){
			while(tp&&a[stk[tp]]<a[i]) R[stk[tp]]=i,tp--;
			stk[++tp]=i;
		}
		tp=0;
		for(int i=n;i>=1;i--){
			while(tp&&a[stk[tp]]<a[i]) L[stk[tp]]=i,tp--;
			stk[++tp]=i;
		}
		sort(p+1,p+n+1,cmp);
		for(int i=1;i<=n;i++){
			x[p[i]]=p[i],y[p[i]]=n;
			int xx=n+1,yy=0;
			if(L[p[i]]){
				int xxx=n+1,yyy=0;
				if(s[p[i]]-s[L[p[i]]]>=a[L[p[i]]]) xxx=x[L[p[i]]],yyy=y[L[p[i]]];
				else xxx=max(getpos(p[i]),x[L[p[i]]]),yyy=y[L[p[i]]];
				xx=min(xx,xxx),yy=max(yy,yyy);
			}else{
				xx=min(xx,p[i]),yy=max(yy,R[p[i]]-1);
			}
			if(R[p[i]]){
				int xxx=n+1,yyy=0;
				if(s[R[p[i]]-1]-s[L[p[i]]]>=a[R[p[i]]]) xxx=max(R[p[i]],x[R[p[i]]]),yyy=y[R[p[i]]];
				xx=min(xx,xxx),yy=max(yy,yyy);
			}
			x[p[i]]=max(x[p[i]],xx),y[p[i]]=min(y[p[i]],yy);
			if(x[p[i]]>y[p[i]]) continue;
			ans[x[p[i]]]++,ans[y[p[i]]+1]--;
		}
		for(int i=1;i<=n;i++){
			ans[i]+=ans[i-1];
			cout<<ans[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Eternatis (赞：3)

$O(n)$ 解。

考虑 E1 的分治解法，其过程相当于一棵笛卡尔树，而笛卡尔树可以通过维护右链 $O(n)$ 建，于是考虑动态维护需要的信息。

注意到在构造笛卡尔树时，一个点一旦被作为某个点的左子树，其信息就**不再改变**，即维护的右链上，每个点的左子树答案确定，考虑对当前栈内每个点，维护**根与左子树**的权值和与贡献和，记作 $sum$ 与 $w$ ，这样从栈中删除点并挂到左儿子上的过程是简单的。

现在考虑加点时，对栈中元素 $sum$ 值的影响。

考虑这相当于对插入的元素到根的链进行链加，但注意到每次插入元素时，其最终会作为右链的结尾，于是可以直接维护一个全局加标记 $tag$ ，再记录一个 $r$ 表示当前元素还需要加多少变为合法，即子树权值和不小于父节点权值。

用一个队列维护上述过程，每次判断队头是否合法，若已经合法就出队，这样每个元素只会入队出队一次。注意初始化每个元素的 $r$ 时消去当前标记的影响即可。


最后只剩求答案的部分，考虑当前队头，即第一个不合法位置，因为每个点都维护了左子树的信息，所以当前的答案相当于栈内元素 $w$ 值的前缀和，在将元素插入栈内时维护即可。

注意因为会从栈顶删数，队列里可能会存在不在栈中的元素，开个数组记录一下就好了。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000010
#define int long long
#define db long double
#define pii pair<int,int>
#define st first
#define ed second
#define mkp make_pair
#define pb push_back
#define eps 1e-9
#define mod 998244353
#define mod2 1000000007
#define bs 13131
#define bs2 131
#define INF 0x3f3f3f3f3f3f3f3f
#define il inline
#define vi vector<int>
#define ins insert
#define umap unordered_map
#define uset unordered_set
#define R(x) x.begin(),x.end()
#define B(x) x.begin()
#define E(x) x.end()
#define lb lower_bound
#define ub upper_bound
#define vi vector<int>
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int T=1,n,m,q,k;
int s[N],sum[N],w[N]; // sum 和 w 记录栈内左子树信息 
int stk[N],top;
int sm[N],val[N]; // sm 与 tag 对应，用来维护栈内元素是否合法，val 记录栈内贡献前缀和 
bool instk[N]; // instk 记录是否在栈内，防止队列未及时清空 
il void solve(){
	n=read();m=read();
	for(int i=1;i<=n;i++)
		s[i]=read(),sum[i]=w[i]=sm[i]=val[i]=instk[i]=0;
	top=0;
	int tag=0;
	queue<int> q;
	for(int i=1;i<=n;i++){
		int k=top;
		while(k&&s[stk[k]]<s[i])k--;
		sum[i]=s[i],w[i]=1;
		while(top>k+1){ // 合并栈顶到当前节点 
			if(sum[stk[top]]>=s[stk[top-1]])
				w[stk[top-1]]+=w[stk[top]];
			sum[stk[top-1]]+=sum[stk[top]];
			instk[stk[top]]=0;
			top--;
		}
		if(top>k){ // 特判最后一个元素是否合并（可能出现当前元素加入即为栈顶的情况） 
			if(sum[stk[k+1]]>=s[i])
				w[i]+=w[stk[k+1]];
			sum[i]+=sum[stk[k+1]];
			instk[stk[k+1]]=0;
		}
		stk[k+1]=i;top=k+1;
		instk[i]=1;
		
		tag+=s[i];
		sm[i]=s[stk[top-1]]+tag-sum[i]; // 消除已有 tag 的影响 
		val[i]=val[stk[top-1]]+w[i];
		q.push(i);
		while(!q.empty()){
			int x=q.front();
			if(tag>=sm[x]||!instk[x])q.pop();
			else break;
		}
		if(q.empty())printf("%lld ",val[i]);
		else {
			int p=q.front();
			printf("%lld ",val[p]-w[p]);
		}
	}
	puts("");
}
signed main(){
	T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：Xy_top (赞：1)

可以先看一下 [E1](https://www.luogu.com.cn/article/lysjjjw6) 的题解，思维更加连贯一些。

与 E1 不同的是这道题要我们对于每个前缀求出答案。

考虑每次优先向左扩展，对于 $[i,i]$ 先判断能不能扩展到 $1$，如果能的话找到最小的 $mir$ 使得能扩展到 $[1,r]$ 再向右扩展找到最大的 $mxr$，那么 $i$ 在询问 $[mir,mxr]$ 间可以成为答案。如果不能扩展到 $1$ 那么无法对答案做出贡献。

找的过程依旧是倍增 + ST 表。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x;
int ans[200005];
int d[200005];
int a[200005], s[200005], lg[200005];
int pre[200005], suf[200005];
int fx[18][200005], fy[18][200005];
void initst () {
	For (i, 1, 17) for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
		fx[i][j] = max (fx[i - 1][j], fx[i - 1][j + (1 << i - 1)]);
		fy[i][j] = max (fy[i - 1][j], fy[i - 1][j + (1 << i - 1)]);
	}
}
int qry1 (int x, int y) {
	if (x > y) return 0;
	int l = lg[y - x + 1];
	return max (fx[l][x], fx[l][y - (1 << l) + 1]);
}
int qry2 (int x, int y) {
	if (x > y) return 0;
	int l = lg[y - x + 1];
	return max (fy[l][x], fy[l][y - (1 << l) + 1]);
}
void solve () {
	cin >> n >> x;
	For (i, 1, n) d[i] = 0;
	For (i, 1, n) ans[i] = 0;
	For (i, 1, n) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
		fx[0][i] = a[i] + s[i];
		fy[0][i] = a[i] - s[i - 1];
	}
	initst ();
	For (i, 1, n) {
		int l = i, r = i;
		if (qry1 (1, i - 1) <= s[r]) {
			l = 1;
			foR (j, 17, 0) if (r + (1 << j) <= n && qry2 (r + 1, r + (1 << j) ) <= -s[l - 1]) r += 1 << j;
			++ d[i];
			-- d[r + 1];
			continue;
		}
		while (1) {
			int tl = l, tr = r;
			foR (j, 17, 0) if (l > (1 << j) && qry1 (l - (1 << j), l - 1) <= s[r]) l -= 1 << j;
			foR (j, 17, 0) if (r + (1 << j) <= n && qry2 (r + 1, r + (1 << j) ) <= -s[l - 1] && qry1 (1, l - 1) > s[r + (1 << j)]) r += 1 << j;
			if (tl == l && tr == r) {
				if (r == n) break;
				if (a[r + 1] <= s[r] - s[l - 1]) {
					l = 1;
					++ r;
					if (r > n) break;
					++ d[r];
					foR (j, 17, 0) if (r + (1 << j) <= n && qry2 (r + 1, r + (1 << j) ) <= -s[l - 1]) r += 1 << j;
					-- d[r + 1];
				}
				break;
			}
		}
	}
	For (i, 2, n) d[i] += d[i - 1];
	For (i, 1, n) cout << d[i] << ' ';
}
/*
a[l] + s[l] <= s[i];
a[r] - s[r - 1] <= - s[i - 1];
*/
signed main () {
	lg[1] = 0;
	For (i, 2, 200000) lg[i] = lg[i / 2] + 1;
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：LHLeisus (赞：1)

[原题链接](https://codeforces.com/contest/1998/problem/E2)

[我的博客](https://www.cnblogs.com/LHLeisus/p/18393071)

考虑对于每个 $i$，算出向左扩展到 $1$ 时向右至少和至多扩展到哪里，记为 $minr$ 和 $maxr$。

那么也就是说每个 $i$ 会对 $minr\sim maxr$ 做出贡献，差分一下就可以了。重点是怎么计算这两个东西。

先说 $maxr$。如果暴力跳，过程是：先向左扩展直到不能扩展，然后再向右扩展到不能扩展。不断重复直到左边界到 $1$ 或者两边都无法继续扩展宣告失败。

然后你想起了刚刚做完的 E1，每次扩展一定是找到一个最近的最大值，把最大值之前的都加上，再看看能不能也把这个最大值也加上。这个可以用 ST 表和二分 $\mathcal{O}(\log V\log n)$ 解决。

具体地说，记 $l,r$ 为当前左右边界，$s$ 为前缀和，在向左扩展时，要找到一个最大的 $x$ 使得 $s_r-s_{l-1}<a_{l-1}$，移项变为 $s_r<a_{l-1}+s_{l-1}$，用 ST 表维护 $a_i+s_i$ 的最大值。二分时每次检查右区间是否符合条件，如果是则增大左边界，否则减小右边界。向右扩展基本同理，式子稍有变化，换成了维护最小值。

~~其实 $maxr$ 也可以双指针来着~~然后再看 $minr$。有区别的是向右扩展时不是无脑扩展，而是扩展到刚好够左边能跨过下一个最大值。那么只需每次向右扩展之后再二分一下，尝试把 $r$ 往回减一些。这个不需要 ST 表。

来看一下时间复杂度。每次当前区间总和因为跨过了一个最大值，所以至少增加了一倍，那么也就最多增加 $\log V$ 次。再加上二分和枚举 $i$ 的复杂度，总复杂度 $\mathcal{O}(n\log n\log V)$。

细节说多不多说少不少。

```cpp
#include<bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
const int N=2e5+5;
const int inf=0x3f3f3f3f;
inline int read();
int n,m,k;int a[N];
int f[30][N],g[30][N];
int ans[N],minr[N],maxr[N],s[N];
int getmax(int x,int y){
	int s=__lg(y-x+1);
	return max(f[s][x],f[s][y-(1<<s)+1]);
}
int getmin(int x,int y){
	int s=__lg(y-x+1);
	return min(g[s][x],g[s][y-(1<<s)+1]);
}
void work(){
	n=read();read();
	FOR(i,1,n)a[i]=read(),s[i]=s[i-1]+a[i],ans[i]=0;
	a[n+1]=0;
	FOR(i,1,n)f[0][i]=a[i]+s[i],g[0][i]=s[i]-a[i+1];
	for(int j=1;1<<j<=n;++j)
		for(int i=1;i+(1<<j)-1<=n;++i){
			f[j][i]=max(f[j-1][i],f[j-1][i+(1<<j-1)]);
			g[j][i]=min(g[j-1][i],g[j-1][i+(1<<j-1)]);
		}
	int L,R,l,r,mid;
	FOR(i,1,n){
		l=i,r=i;
		while(1){
			bool flag=0;
			L=1,R=l;
			while(L<R){
				mid=L+R>>1;
				if(s[r]<getmax(mid,R-1))L=mid+1;
				else R=mid;
			}
			if(l!=L)l=L,flag=1;
			if(l==1||r==n)break;
			L=r,R=n;
			while(L<R){
				mid=L+R>>1;
				if(getmin(L,mid)<s[l-1])R=mid;
				else L=mid+1;
			}
			if(r!=L){
				flag=1;
				int x=L;
				L=r+1,R=x;
				while(L<R){
					mid=L+R>>1;
					if(s[mid]-s[l-1]>=a[l-1])R=mid;
					else L=mid+1;
				}
				r=R;
			}
			if(!flag)break;
		}
		if(l==1)minr[i]=r;
		else minr[i]=inf;
		l=i,r=i;
		while(1){
			bool flag=0;
			L=r,R=n;
			while(L<R){
				mid=L+R>>1;
				if(getmin(L,mid)<s[l-1])R=mid;
				else L=mid+1;
			}
			if(r!=L)flag=1,r=R;
			L=1,R=l;
			while(L<R){
				mid=L+R>>1;
				if(s[r]<getmax(mid,R-1))L=mid+1;
				else R=mid;
			}
			if(l!=L)l=L,flag=1;
			if(!flag)break;
		}
		if(l==1)maxr[i]=r;
		else maxr[i]=inf;
	}
	FOR(i,1,n)
		if(maxr[i]!=inf&&minr[i]<=maxr[i])
			ans[minr[i]]++,ans[maxr[i]+1]--;
	FOR(i,1,n)ans[i]+=ans[i-1];
	FOR(i,1,n)printf("%lld ",ans[i]);puts("");
}
signed main()
{
	int T=read();
	while(T--)work();
	return 0;
}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
```

---

## 作者：_Ch1F4N_ (赞：1)

[接着 E1 的做法继续。](https://www.luogu.com.cn/article/hrkkmwyx)

对于每个前缀都要查询的话，我们考虑对于一个点优先扩展左端点，没法扩展再去扩展右端点，扩展右端点时也是扩展到左端点可以再次被扩展就结束，那么假若最后可以左端点可以扩展到节点 $1$，则第一次扩展到节点 $1$ 时的右端点以及最终状态的右端点组成的区间内的前缀均可以被贡献到，考虑差分维护一下即可，时间复杂度依然是 $O(n \log n \log V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
const int inf = 1e18+114;
int a[maxn],pre[maxn],n;
int st[maxn][20];
int lg[maxn];
void init(){
    for(int i=1;i<=n;i++) st[i][0]=a[i];
    for(int j=1;j<20;j++)
        for(int i=1;i<=n;i++){
            if(i+(1<<(j-1))<=n) st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            else st[i][j]=st[i][j-1];
        }
    lg[1]=0;
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
}
int query(int l,int r){
    int len=lg[r-l+1];
    return max(st[l][len],st[r-(1<<len)+1][len]);
}
int ChiFAN;
int answer[maxn];
void work(){
    cin>>n>>ChiFAN;
    a[0]=a[n+1]=inf;
    for(int i=1;i<=n;i++) cin>>a[i],pre[i]=pre[i-1]+a[i],answer[i]=0;
    //for(int i=1;i<=n;i++) cout<<answer[i]<<' ';
    //cout<<'\n';
    init();
    for(int i=1;i<=n;i++){
        int l=i,r=i;
        int now=a[i];
        int start=inf;
        while(a[l-1]<=now||a[r+1]<=now){
            while(a[l-1]<=now){
                int lt=0,rt=l-1;
                while(lt+1<rt){
                    int mid=(lt+rt)>>1;
                    if(query(mid,l-1)<=now) rt=mid;
                    else lt=mid;
                }
                if(l!=1&&query(rt,l-1)<=now) now=now+pre[l-1]-pre[rt-1],l=rt;
                if(l==1) start=min(start,r);
            }
            if(l==1) start=min(start,r);
            int lt=r+1,rt=n+1;
            while(lt+1<rt){
                int mid=(lt+rt)>>1;
                if(query(r+1,mid)<=now) lt=mid;
                else rt=mid;
            }
            if(r!=n&&query(r+1,lt)<=now) now=now+pre[lt]-pre[r],r=lt;
            //cout<<i<<' '<<l<<' '<<r<<' '<<a[l-1]<<' '<<a[r+1]<<' '<<now<<'\n';
        }
        if(l==1){
            l=r=i;
            now=a[i];
            start=inf;
            while(a[l-1]<=now||a[r+1]<=now){
                while(a[l-1]<=now){
                    int lt=0,rt=l-1;
                    while(lt+1<rt){
                        int mid=(lt+rt)>>1;
                        if(query(mid,l-1)<=now) rt=mid;
                        else lt=mid;
                    }
                    if(l!=1&&query(rt,l-1)<=now) now=now+pre[l-1]-pre[rt-1],l=rt;
                    if(l==1) start=min(start,r);
                }
                if(l==1) start=min(start,r);
                int lt=r+1,rt=n+1;
                while(lt+1<rt){
                    int mid=(lt+rt)>>1;
                    if(query(r+1,mid)<=now) lt=mid;
                    else rt=mid;
                }
                if(r==n||query(r+1,lt)>now) continue;
                rt=lt;
                lt=r;
                while(lt+1<rt){
                    int mid=(lt+rt)>>1;
                    if(now+pre[mid]-pre[r]>=a[l-1]) rt=mid;
                    else lt=mid;
                }
                now=now+pre[rt]-pre[r],r=rt;
                //cout<<i<<' '<<l<<' '<<r<<' '<<a[l-1]<<' '<<a[r+1]<<' '<<now<<'\n';
            }
        }
        if(l==1) start=min(start,r);
        //if(l==1) cout<<i<<' '<<start<<' '<<r<<'\n';
        if(l==1) answer[start]++,answer[r+1]--;
    }
    for(int i=1;i<=n;i++) answer[i]+=answer[i-1],cout<<answer[i]<<' ';
    cout<<'\n';
}
signed main(){
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
11 1
1 2 3 1 1 9 3 2 4 1 3
*/
/*
1 0 2
2 2 8
3 0 4
4 6 8
5 0 6
6 7 8
7 7 8
*/

```

---

## 作者：jiangxinyang2012 (赞：0)

[E1 题解](https://www.luogu.com.cn/article/17hfrj7x)

这次题目是问你有多少个 $i$ 可以消掉一个 $[1,k]$ 的前缀。

首先，我们和刚才一样，计算每个 $a_i$ 可以删除的最大区间。如果最大区间的左端点不是 $1$，显然它对答案没有任何贡献。

我们假设算出来的右端点是 $R$，那么 $a_i$ 能删除的前缀的右端点就形成了一个 $[x,R]$ 的区间。

我们发现，这个 $x$ 也是可以二分的。

关于这个二分，我们的 check 就是和前面那样计算一下 $a_i$ 在 $[1,x]$ 范围内能消除的最大区间。如果最大区间也是 $[1,x]$ 的话，就可行。

二分完之后，我们只要用差分给 $[x,R]$ 区间加一就好了。

时间复杂度又多了一个 $\log$，能 3.9s 卡过去。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 200005;
const int INF = 0x3f3f3f3f;
int a[N], n;
ll s[N];
ll sum(int l, int r) {
    return s[r] - s[l - 1];
}
int st[N][30];
void st_init() {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    int p = __lg(n);
    for (int k = 1; k <= p; k++) {
        for (int s = 1; s + (1 << k) <= n + 1; s++) {
            st[s][k] = max(st[s][k - 1], st[s + (1 << (k - 1))][k - 1]);
        }
    }
}
int mx(int l, int r) {
    int k = __lg(r - l + 1);
    int x = max(st[l][k], st[r - (1 << k) + 1][k]);
    return x;
}
int D[N];
bool check(int i, int x) {
    int l = i, r = i;
    ll res = a[i], lr = a[i];
    while (1) {
        int L = 1, R = l - 1, p = l;
        while (L <= R) {
            int mid = L + R >> 1;
            if (mx(mid, l - 1) <= res) {
                p = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        if (p <= l - 1) {
            res += sum(p, l - 1);
            l = p;
        }
        L = r + 1, R = x, p = r;
        while (L <= R) {
            int mid = L + R >> 1;
            if (mx(r + 1, mid) <= res) {
                p = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        if (r + 1 <= p) {
            res += sum(r + 1, p);
            r = p;
        }
        if (res == lr) break;
        lr = res;
        if (l == 1 && r == x) break;
    }
    if (l == 1 && r == x) return true;
    return false;
}
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        scanf("%d%*d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
        for (int i = 1; i <= n; i++) D[i] = 0;
        st_init();
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int l = i, r = i;
            ll res = a[i], lr = a[i];
            while (1) {
                int L = 1, R = l - 1, p = l;
                while (L <= R) {
                    int mid = L + R >> 1;
                    if (mx(mid, l - 1) <= res) {
                        p = mid;
                        R = mid - 1;
                    } else {
                        L = mid + 1;
                    }
                }
                if (p <= l - 1) {
                    res += sum(p, l - 1);
                    l = p;
                }
                L = r + 1, R = n, p = r;
                while (L <= R) {
                    int mid = L + R >> 1;
                    if (mx(r + 1, mid) <= res) {
                        p = mid;
                        L = mid + 1;
                    } else {
                        R = mid - 1;
                    }
                }
                if (r + 1 <= p) {
                    res += sum(r + 1, p);
                    r = p;
                }
                if (res == lr) break;
                lr = res;
                if (l == 1 && r == n) break;
            }
            if (l == 1) {
                int left = i, right = r, rr = r;
                while (left <= right) {
                    int mid = left + right >> 1;
                    if (check(i, mid)) {
                        right = mid - 1;
                        rr = mid;
                    } else {
                        left = mid + 1;
                    }
                }
                D[rr]++;
                D[r + 1]--;
            }
        }
        for (int i = 1; i <= n; i++) D[i] += D[i - 1];
        for (int i = 1; i <= n; i++) printf("%d ", D[i]);
        printf("\n");
    }
    return 0;
}

```

---

## 作者：快斗游鹿 (赞：0)

线性做法。

考虑 E1 的做法。其实就是建出笛卡尔树，然后查询根节点所在合法连通块大小，合法连通块定义为其中每个点的子树和都不小于父亲权值。

现在要求对每个前缀求答案，回顾线性建笛卡尔树的过程，是在维护右链。由于子树和只会加不会减，并且每个点的父亲权值只会越来越小，因此已经合法的点不会变的不合法。考虑用并查集之类的东西维护合法连通块。

每次新加一个点 $i$ 进来，会先把原本右链上权值小于它的点弹掉，弹的过程中只要一对父子合法，就把它们并起来。弹完后有一个把原本点右子树扔到新点左子树的过程，这时新的父子边也判一下即可。这部分显然线性。接下来由于右链上的所有点子树大小有变化，因此需要从根所在合法连通块开始暴力往下判下一个合法连通块能不能跟它并上，直到不能就停止。因为每次枚举都会导致某两个连通块合并或直接停止，所以这部分也是线性的。

核心代码：


```cpp
top=0;
	for(int i=1;i<=n;i++){
		int cur=top;
		while(cur&&a[st[cur]]<a[i]){
            cur--;
            if(sum[i-1]-sum[st[cur]]>=a[st[cur]])merge(st[cur],st[cur+1]);
        }
        if(cur)rs[st[cur]]=i;
		if(cur<top)ls[i]=st[cur+1];
		if(sum[i-1]-sum[st[cur]]>=a[i])merge(ls[i],i);
		int now=find(st[1]);
		while(rs[now]&&sum[i]-sum[now]>=a[now]){
			merge(now,rs[now]);
			now=find(rs[now]);
		}
		st[++cur]=i;top=cur;
		cout<<sz[find(st[1])]<<' ';
	}
```

---

## 作者：内拉组里 (赞：0)

这道题的部分分还是非常有意思的。

先考虑 $ x = n $。

# Raw

暴力枚举每个数作为最后留下的 $ j $，然后从这个数开始向两侧合并，

能并则并，不能并就换个方向继续并。

若最后被两个更大的数夹在中间两个方向都无法继续并了，那么该数一定不是 $ j $，直接跳过。

否则将 $ ans + 1 $。

不过这样只能过个样例，一个 **pts** 也拿不到。

## Analyses：

> 总时间复杂度 $ \Theta (N^2) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# ST

从 **Raw** 中不难看出，其实有些时候没必要一个一个地并，而是一块一块地并。

而一块的大小，显然前缀和存在一个单调性，故考虑二分。

- 假设右端点固定，左端点从 $ l $ 移到 $ l^\prime $，则需满足 $ \forall i \in [l^\prime,l],p[r] - p[i - 1] \ge a[i - 1] $，

  化简后得到 $ \forall i \in [l^\prime - 1,l - 1],p[r] \ge p[i] + a[i] $。

  显然令 $ f[i] = p[i] + a[i] $，则有 $ \max\limits^{l - 1}_{i = l^\prime - 1} f[i] \le p[r] $，

  这里 $ f[i] $ 只与 $ a $ 数组有关，直接预处理出来用 **ST** 表即可。

- 同样地，左端点固定，右端点从 $ r $ 移到 $ r^\prime $，

  则需满足 $ \forall i \in [r,r^\prime],p[i - 1] - p[l - 1] \ge a[i] $，

  移项得到 $ \forall i \in [r,r^\prime],p[l - 1] \le p[i - 1] - a[i] $，

  令 $ g[i] = p[i - 1] - a[i] $，则有 $ \min\limits^{r^\prime}_{i = r} g[i] \ge p[l - 1] $，

  同样可以用 **ST** 表预处理，$ \Theta (1) $ 查询。

如此，将暴力优化一下就过了。

> 有人可能会认为这样做时间复杂度是假的，
>
> 因为当每次只能一个一个地合并时，时间复杂度就退化为了 $ \Theta (N^2) $。
>
> 以一组数据为例：
>
> | 数据         | 1024 | 256  | 64   | 16   | 4    | 1    | 1    | 2    | 8    | 32   | 128  | 512  |
> | ------------ | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
> | **二分次数** | 2    | 4    | 6    | 8    | 10   | 12   | 13   | 11   | 9    | 7    | 5    | 3    |
>
> 这种情况下，每次无法合并的数字 $ a_{l - 1} $ 一定有 $ a_{l - 1} \gt 2 \sum\limits^r_{i = l} a_i $，
>
> 故在两次二分以后 $ \sum\limits^r_{i = l} a_i $ 至少会翻一倍。
>
> 而 $ a_i \le 10^9 $，所以每次二分的次数不会超过 $ \lceil \log{a_{\max}} \rceil $。
>
> 故最坏时间复杂度为 $ \Theta (N \log{a_{\max}}) $。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{a_{\max}}) $。
>
> 总空间复杂度 $ \Theta (N \log{N}) $。

***

# CDQ

准确的来讲，这并不是传统意义上的 **CDQ**，只能算是分治。

从最简单的情况入手，显然一个区间里的最大值一定可以合并这整一个区间。

所以考虑最大值分治，即每次从最大值处分成两个子区间，但最大值不属于任何一个子区间。

寻找最大值位置的过程交给 **ST** 表，这里考虑跨区间信息合并。

显然地，对于一个能够并掉整个子区间的数而言，

想要合并这整个区间，那就一定要把区间内最大值并掉。

判断一下子区间数字之和能否并掉最大值即可。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{N}) $，瓶颈在于 **ST** 表的预处理。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Cartesian Tree

观察 **CDQ** 时递归区间的特征。

发现每个节点都大于子树中任意节点，这一点符合大根堆的性质；

同时，每个节点将当前区间分成了两段连续的区间，这一点符合二叉搜索树的性质。

故考虑**笛卡尔树**。

这题建树方法这里不再赘述，自己去翻 [**OI-Wiki**](https://oi-wiki.org/ds/cartesian-tree/)。

建完树以后从根节点 **dfs** 下去跑刚才的分治，就不需要再借助 **ST** 表找最值了。

## Analyses：

> 总时间复杂度 $ \Theta (N) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Hard Version

如上方法都是针对 $ x = n $ 的情况的，只能通过 **Easy Version**。

**Hard Version** 的做法需要综合以上三种做法。

对于 $ x = 1 $ 的情况，直接暴力肯定不行，不妨考虑每个数对不同的 $ i $ 的贡献。

- 对于左区间的节点，假如左区间全部并起来能够并掉根节点，

  那么所有能并掉整个左区间的数字也同样能并掉整个区间。

  所以左区间的这些数字就会对根节点的 $ i $ 做出贡献，

  贡献的大小就是分治到左区间时计算出的答案，直接从左区间继承答案即可。

- 对于右区间的每个节点，需要找到最小的一个右端点，

  使得该节点至少要并掉这个右端点才能并掉根节点。

  那么该节点对对应的右端点及以后的所有 $ i $ 都有贡献。

  - 这里的二分与 **ST** 中的二分有些许不同，

    需要二分出来的是指定节点能够并掉根节点时的最小右端点，

    故对左端点的二分与 **ST** 中无异，对右端点的二分中，

    左端点固定，只有在当前区间能够并到 $ mid $，

    且（并完以后的区间依然无法向左继续并）的点才算合法。

这里只计算了根节点和右子树的贡献，左子树递归计算即可。

由于只递归左子树，故所有的递归区间的左端点都是 $ 1 $。

统计答案是跑一遍前缀和即可。

需要注意的是，所有的前缀最大值的位置的答案是固定的，不能从前缀和里求解。

因为当 $ \max_{[1,i]} $ 落在 $ i $ 上时，只有能并掉 $ [1,i - 1] $ 的数字才有可能成为答案 $ j $，

而这些数字在分治时就已经确定了。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{N} \log{a_{\max}}) $。
>
> 总空间复杂度 $ \Theta (N \log{N}) $。

# Code：

不是一般的长，放在[云剪贴板](https://www.luogu.com.cn/paste/g8ysne62)里。

---

## 作者：wangyibo201026 (赞：0)

## solution

注意到这个题并不是很正经，所以我们做这题也不需要很正经（[如果你想看我口胡](https://www.cnblogs.com/alexande/articles/18389561)）。

cnblogs 上的内容于本篇博客不相同哦。

### E1

让我们先充分思考 E1。

由于 $x = n$，所以我们可以思考每个数是否可以存活到最后的暴力做法。

我们其实可以将题面中的一系列复杂操作只针对于数 $a_i$ 来说最优的策略去进行，这样我们只需要看在针对数 $a_i$ 的最优策略下，最后能否只剩下一个数 $a_i$。具体来说，我们可以将这个策略抽象为这个过程：

- 对于原始的数 $a_i$，我们先向左依次将数吃掉，我吃掉一个数就能将这个数加到 $a_i$ 上，如果左边不能再吃了，那我就掉头向右吃，吃完继续向左，以此类推。

注意到这其实是一个经典问题，假设值域是 $V$，那么我对于一个数 $a_i$ 每次能**不消化吃掉的连续段数**其实是远小于 $\log V$ 的。举个例子，假设目前 $a_i$ 向左吃，那么只要向左的一段数每个数都要 $\le a_i$，那么我们就可以把它当作一段吃掉，**但是不意味着 $a_i$ 只能吃掉这些数**（究其本质是因为没有将这些数的和加上）。

于是我们就有了一个朴素的做法了，每次二分一次不消化能够吃掉的连续段，然后吃掉继续二分，如果不能继续吃了，那我们就掉头继续吃，注意到由于在二分过程中区间最大值我们可以用 ST 表进行求解，于是对于一个 $a_i$ 进行这种的操作的单次时间复杂度为 $O(\log n \log V)$，总复杂度为 $O(n \log n \log V)$。

### E2

对 E1 进行充分思考后，我们来思考 E2。

我们发现唯一的加强点在于你需要对于每个 $i$ 都求出 $1 \sim i$ 中有多少满足条件的数，于是你还是考虑每个数对每个答案的贡献。

以下默认先向右拓展，并且将点 $i$ 拓展的过程抽象为管辖范围左端点和右端点的扩展。

考虑优化，不难发现按照 E1 的二分过程，我们其实一个数 $a_i$ 只会向右拓展 $\log V$ 个连续段，但是我们发现无法实时的维护左端点扩展的信息，咋办呢？

我们发现左端点的扩展信息其实是不那么重要的，就是我们可以先把右端点扩展完再扩展左端点，我们发现其实是对每个数的 $\log$ 个向右的连续段每段（不是上述的连续段，是向右到底再向左后的连续段）进行二分（为啥要分段二分，因为我们下一个右端点的扩展需要靠当前的这一段所供给的左端点扩展长度，比较难理解），二分到了啥时候我的当前区间值就不能覆盖整个区间了。但是我们二分左端点扩展到那时又要二分，这样就是三只 $\log$ 的了，非常的不优美。

然后我们就可以差分修改答案了。

我们发现此时我们可以对于每个前缀二分出至少当前区间总值为多少才能覆盖整个前缀，这样的预处理复杂度是两只 $\log$ 的（我好像用了线段树啥的，反正能过就行），然后我们具体计算的时候直接比大小就好了。

## code

代码写得比较狗屎，谨慎观看。

E1：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int t;
int n, x, ans;
int a[N], bin[N], logg[N], f[N][21], pre[N];

int query ( int x, int y ) {
  if ( x > y ) {
    return 1e18;
  }
  int len = y - x + 1, tmp = logg[len];
  return max ( f[x][tmp], f[y - bin[tmp] + 1][tmp] );
}

void Solve () {
  cin >> t;
  while ( t -- ) {
    ans = 0;
    cin >> n >> x;
    for ( int i = 1; i <= n; i ++ ) {
      cin >> a[i];
      f[i][0] = a[i];
      pre[i] = pre[i - 1] + a[i];
    }
    bin[0] = 1;
    logg[0] = -1;
    for ( int i = 1; i <= 20; i ++ ) {
      bin[i] = bin[i - 1] << 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      logg[i] = logg[i >> 1] + 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      for ( int j = 1;  j <= 20; j ++ ) {
        f[i][j] = 0;
      }
    }
    for ( int i = 1; i <= logg[n]; i ++ ) {
      for ( int j = 1; j <= n && j + bin[i] - 1 <= n; j ++ ) {
        f[j][i] = max ( f[j][i - 1], f[j + bin[i - 1]][i - 1] );
      }
    }
    for ( int i = 1; i <= n; i ++ ) {
      int posl = i, posr = i, sum = a[i];
      for ( int j = 1; j <= 63; j ++ ) {
        if ( j & 1 ) {
          int l = posr, r = n + 1;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( posr + 1, mid ) <= sum ) {
              l = mid;
            }
            else {
              r = mid;
            }
          }
          sum += pre[l] - pre[posr];
          posr = l;
        }
        else {
          int l = 0, r = posl;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( mid, posl - 1 ) <= sum ) {
              r = mid;
            }
            else {
              l = mid;
            }
          }
          sum += pre[posl - 1] - pre[r - 1];
          posl = r;
        }
      }
      if ( posl == 1 && posr == n ) {
        ans ++;
      }
    }
    cout << ans << '\n';
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

E2：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int t;
int n, x;
int a[N], bin[25], logg[N], f[N][21], pre[N], chifan[N];

struct Node {
  int l, r, ll, sum;
};

vector < Node > ans[N];

int query ( int x, int y ) {
  if ( x > y ) {
    return 4e18;
  }
  int len = y - x + 1, tmp = logg[len];
  return max ( f[x][tmp], f[y - bin[tmp] + 1][tmp] );
}

int diff[N];

void change ( int l, int r, int k ) {
  if ( l > r ) {
    return ;
  }
  diff[l] += k, diff[r + 1] -= k;
}

int tree[N << 2], tag[N << 2];

void pushup ( int node ) {
  tree[node] = max ( tree[node << 1], tree[node << 1 | 1] );
}

void addtag ( int node, int k ) {
  tree[node] += k;
  tag[node] += k;
}

void pushdown ( int node ) {
  if ( !tag[node] ) {
    return ;
  }
  addtag ( node << 1, tag[node] ), addtag ( node << 1 | 1, tag[node] );
  tag[node] = 0;
}

void update ( int node, int lt, int rt, int x, int y, int k ) {
  if ( y < lt || x > rt ) {
    return ;
  }
  if ( x <= lt && rt <= y ) {
    addtag ( node, k );
    return ;
  }
  pushdown ( node );
  int mid = lt + rt >> 1;
  update ( node << 1, lt, mid, x, y, k ), update ( node << 1 | 1, mid + 1, rt, x, y, k );
  pushup ( node );
}

int query ( int node, int lt, int rt, int x, int y ) {
  if ( y < lt || x > rt ) {
    return -4e18;
  }
  if ( x <= lt && rt <= y ) {
    return tree[node];
  }
  pushdown ( node );
  int mid = lt + rt >> 1;
  return max ( query ( node << 1, lt, mid, x, y ), query ( node << 1 | 1, mid + 1, rt, x, y ) );
}

bool Check ( int sum, int x ) {
  for ( int i = x; i >= 1; i -- ) {
    if ( sum < a[i] - ( pre[x] - pre[i] ) ) {
      return false;
    }
  }
  return true;
}

void Solve () {
  ios :: sync_with_stdio ( false );
  cin.tie ( 0 ), cout.tie ( 0 );
  cin >> t;
  while ( t -- ) {
    cin >> n >> x;
    for ( int i = 1; i <= n; i ++ ) {
      cin >> a[i];
      diff[i] = 0;
      ans[i].clear ();
      f[i][0] = a[i];
      pre[i] = pre[i - 1] + a[i];
    }
    for ( int i = 1; i <= 4 * ( n + 1 ); i ++ ) {
      tree[i] = tag[i] = 0;
    }
    for ( int i = 1; i <= n; i ++ ) {
      if ( i != 1 ) {
        update ( 1, 1, n, 1, i - 1, -a[i] );
      }
      update ( 1, 1, n, i, i, a[i] );
      chifan[i] = query ( 1, 1, n, 1, i );
    }
    bin[0] = 1;
    logg[0] = -1;
    for ( int i = 1; i <= 20; i ++ ) {
      bin[i] = bin[i - 1] << 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      logg[i] = logg[i >> 1] + 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      for ( int j = 1; j <= 20; j ++ ) {
        f[i][j] = 0;
      }
    }
    for ( int i = 1; i <= logg[n]; i ++ ) {
      for ( int j = 1; j <= n && j + bin[i] - 1 <= n; j ++ ) {
        f[j][i] = max ( f[j][i - 1], f[j + bin[i - 1]][i - 1] );
      }
    }
    for ( int i = 1; i <= n; i ++ ) {
      int posl = i, posr = i, sum = a[i];
      ans[i].push_back ( { i, i, i, 0 } );
      for ( int j = 1; j <= 85; j ++ ) {
        if ( j & 1 ) {
          int l = posr, r = n + 1;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( posr + 1, mid ) <= sum ) {
              l = mid;
            }
            else {
              r = mid;
            }
          }
          ans[i].push_back ( { posr + 1, l, posl, sum } );
          sum += pre[l] - pre[posr];
          posr = l;
        }
        else {
          int l = 0, r = posl;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( mid, posl - 1 ) <= sum ) {
              r = mid;
            }
            else {
              l = mid;
            }
          }
          sum += pre[posl - 1] - pre[r - 1];
          posl = r;
        }
      }
    }
    pre[n + 1] = 4e18;
    for ( int i = 1; i <= n; i ++ ) {
      for ( Node x : ans[i] ) {
        int l = x.l - 1, r = x.r + 1;
        while ( l + 1 < r ) {
          int mid = l + r >> 1;
          if ( x.sum + pre[mid] - pre[x.l - 1] < chifan[x.ll - 1] ) {
            l = mid;
          }
          else {
            r = mid;
          }
        }
        change ( l + 1, x.r, 1 );
      }
    }
    for ( int i = 1; i <= n; i ++ ) {
      diff[i] += diff[i - 1];
    }
    for ( int i = 1; i <= n; i ++ ) {
      cout << diff[i] << " ";
    }
    cout << '\n';
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

