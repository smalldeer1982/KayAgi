# MinimizOR

## 题目描述

给出一个长度为 $n$ 的非负整数数列 $a$，下标编号从 $1$ 到 $n$。

定义一个数列 $a$ 的代价为 $\min\limits_{i\neq j} a_i|a_j$，其中 $|$ 表示 [按位或](https://en.wikipedia.org/wiki/Bitwise_operation#OR) 运算。

$q$ 个询问，每个询问给出两个整数 $l,r\ (l<r)$，求数列 $a_l,a_{l+1},\dots,a_r$ 的最小代价。

## 样例 #1

### 输入

```
2
5
6 1 3 2 1
4
1 2
2 3
2 4
2 5
4
0 2 1 1073741823
4
1 2
2 3
1 3
3 4```

### 输出

```
7
3
3
1
2
3
1
1073741823```

# 题解

## 作者：enucai (赞：17)

## Analysis

线段树解法。

----

**结论**：$\min\limits_{l\le i<j\le r} a_i|a_j$ 的 $a_i$ 与 $a_j$ 一定是 $[l,r]$ 区间内的前 $31$ 小数中的 $2$ 个。

**证明**：采用数学归纳法。原命题 $\Leftrightarrow$ 小于 $2^k$ 的数中的 $\operatorname{OR}$ 最小值出现在前 $k+1$ 小数中的两个数之间。

对于 $k=1$，结论显然成立。

对于 $k>1$：

1. 若当前最高位有 $\ge 2$ 个 $0$，根据高位贪心策略，当前位选 $0$，最小值一定是 $k-1$ 位的最小值，一定在前 $k$ 小值中。

2. 若当前为高位没有 $0$，则只能选一，结果是 $k-1$ 位中的最小值 $+2^{k-1}$，也一定在前 $k$ 小值中。

3. 若当前位有 $1$ 个 $0$，当前位一定是 $1$，找当前位为 $1$ 的最小值一定在前 $k$ 个当前位为 $1$ 的数中，加上一个当前位为 $0$ 的。因此一定在前 $k+1$ 小值中。

----

用线段树维护区间最小值，每次询问找到区间前 $31$ 小值，暴力枚举统计即可。时间复杂度 $O(31^2\cdot q\cdot \log n)$。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1665/submission/153100026)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid (l+r)/2
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
pair<int,int> tr[400010];
void upd(int c,int l,int r,int x,int val){
	if(l==r){
		tr[c]=make_pair(val,x);
		return;
	}
	if(x<=mid) upd(c*2,l,mid,x,val);
	else upd(c*2+1,mid+1,r,x,val);
	tr[c]=min(tr[c*2],tr[c*2+1]);
}
pair<int,int> qry(int c,int l,int r,int x,int y){
	if(l==x&&r==y) return tr[c];
	else if(y<=mid) return qry(c*2,l,mid,x,y);
	else if(x>mid) return qry(c*2+1,mid+1,r,x,y);
	else return min(qry(c*2,l,mid,x,mid),qry(c*2+1,mid+1,r,mid+1,y));
}
int n,q,a[100010];
vector<pair<int,int> > now;
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n) upd(1,1,n,i,a[i]);
	cin>>q;
	while(q--){
		int l,r;cin>>l>>r;
		now.clear();int lim=min(r-l+1,31ll);
		For(i,1,lim) now.push_back(qry(1,1,n,l,r)),upd(1,1,n,now.back().second,(1ll<<31));
		int mn=(1ll<<31);
		For(i,0,now.size()-1) For(j,i+1,now.size()-1) mn=min(mn,now[i].first|now[j].first);
		cout<<mn<<endl;
		for(auto p:now) upd(1,1,n,p.second,a[p.second]);
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;cin>>T;
	while(T--) work();
}
```

---

## 作者：Wuyanru (赞：9)

题意：

定义一个数组的成本为 $ \min\limits_{i\ne j}a_i|a_j $，现在给出一个数组，每次询问一个连续的子区间的成本，多组数据。每组数据中数组大小与询问个数的和不超过 $ 10^5 $。

题目中求的是任何一个子区间的成本，我们不妨先从简单的想起，考虑如何求出整个区间的成本。

首先我们能看到，成本是整个数组中不同元素按位或之后得到的最小值，既然是一个位运算，我们不如先把 trie 树建出来。（其实这种思路本人感觉比较套路，因为有很多题都是这样）

我们现在考虑从高位到低位进行按位贪心。

我们想一下，在什么时候某一位上可以是 $ 0 $ 呢？

没错，至少有 $ 2 $ 个数字，满足这一位上是 $ 0 $。

那么我们在进行按位贪心的时候，如果有大于等于两个数字这一位上是 $ 0 $，那么我们无脑只选这些数字。

假如说这一位上是 $ 0 $ 的数字小于两个，那么这一位上就只能是 $ 1 $。现在有两种情况，要么选的两个数字这一位上都是 $ 1 $，要么是一个 $ 0 $ 和一个 $ 1 $。

这个时候方法不太好想，但实际上特别简单，我们只需要将左右两棵子树一起继续进行按位贪心就可以了。

你或许想说：这样时间复杂度不就变成 $ O(n) $ 了吗？

但其实不是的，每经过一层，我们只会多添加一棵子树进来，所以时间复杂度是 $ O(\log^2n) $ 的。（不包括建树）

现在我们知道询问整个区间如何解决，询问子区间其实也差不多了。

我们只需要一个可持久化 trie，就可以将整个问题解决。

最后，多组询问记得清空。

代码：

```
#include<cstdio>
#include<vector>
using namespace std;
using pi=pair<int,int>;
using vpi=vector<pi>;
inline int read()
{
    int s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
int root[100001];
int num[4000001];
int ls[4000001];
int rs[4000001];
int tot;
int n,q;
void build(int &p,int v,int dep,int w)
{
	p=++tot;
	num[p]=num[v]+1;
	if(dep==-1) return ;
	if(w&(1<<dep)) ls[p]=ls[v],build(rs[p],rs[v],dep-1,w);
	else rs[p]=rs[v],build(ls[p],ls[v],dep-1,w);
}
int get(vpi ve,int dep)
{
	if(dep==-1) return 0;
	int sum=0,flag=-1;
	for(unsigned i=0;i<ve.size();i++)
	{
		int p=ve[i].first,v=ve[i].second;
		sum+=num[ls[p]]-num[ls[v]];
		if(num[ls[p]]!=num[ls[v]]) flag=i;
	}
	if(sum>=2)
	{
		for(unsigned i=0;i<ve.size();i++) ve[i].first=ls[ve[i].first],ve[i].second=ls[ve[i].second];
		return get(ve,dep-1);
	}
	int siz=ve.size();
	if(sum==1) ve.push_back(pi(ls[ve[flag].first],ls[ve[flag].second]));
	for(int i=0;i<siz;i++) ve[i].first=rs[ve[i].first],ve[i].second=rs[ve[i].second];
	return get(ve,dep-1)+(1<<dep);
}
signed main()
{
	int t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++) root[i]=0,build(root[i],root[i-1],29,read());
		q=read();
		for(int i=1;i<=q;i++)
		{
			int l=read(),r=read();
			vpi num;
			num.push_back(pi(root[r],root[l-1]));
			printf("%d\n",get(num,29));
		}
		for(int i=1;i<=tot;i++) ls[i]=rs[i]=num[i]=0;
		tot=0;
	}
	return 0;
}
```

---

## 作者：StayAlone (赞：6)

### 题意  

给定长度为 $n(2\leqslant n\leqslant 10^5)$ 的数组 $a$，$q$ 次询问 $\min\limits_{l\leqslant i,j\leqslant r \land i\ne j}{a_i|a_j}$。  

### 思路  

重要的结论很多题解已经给出：答案一定是数列从小到大排序后前 $31$ 个里面两两相或的最小值。考虑归并树记录每一个区间里从小到大排序后的前 $31$ 个数，用类似线段树的思想，对于询问 $[l, r]$，可以分出 $\log$ 个区间。将这些区间合并后，取前 $31$ 个暴力求解即可。  


[record](https://codeforces.com/problemset/submission/1665/155564378)  

码量较短，思想简单。  

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define ptc putchar
#define il inline
#define pb push_back
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define rout return 0
#define .......
using namespace std;
const int MAXN = 1e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int LOGN = log2(MAXN) + 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc {
	template <typename T> il bool read(T &x)
    
	il int read()

	template <typename T> il bool read(pair <T, T> &x)

	template <typename T, typename ...L>
	il bool read(T &x, L &...y) 

	template <typename T> il void write(T x)

	template <typename T> il void write(T x, char ch) 
}
// 奇妙缺省源
using namespace stupid_lrc;
int n, a[MAXN];
vector <int> num[MAXN << 4], ans;

il void operator += (vector <int> &a, const vector <int> &b) {
	vector <int> np;
	int i = 0, j = 0, len = 0, l = a.size(), r = b.size();
	while (i < l && j < r) {
		if (++len > 31) return a = np, void();
		if (a[i] < b[j]) np.pb(a[i++]);
		else np.pb(b[j++]);
	}
	while (i < l && ++len <= 31) np.pb(a[i++]);
	while (j < r && ++len <= 31) np.pb(b[j++]);
	a = np;
	return;
}

il void merge(int x, int l, int mid, int r) {
	int *b = new int[r - l + 1];
	memcpy(b, a + l, sizeof(int) * (r - l + 1));
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (b[i - l] < b[j - l]) a[k++] = b[i - l], ++i;
		else a[k++] = b[j - l], ++j;
	}
	while (i <= mid) a[k++] = b[i - l], ++i;
	while (j <= r) a[k++] = b[j - l], ++j;
	int len = num[x].size();
	rep1(i, l, r) {
		if (++len > 31) break;
		num[x].pb(a[i]);
	}
	delete b;
}

il void msort(int x, int l, int r) {
	num[x].clear();
	if (l == r) return num[x].pb(a[l]);
	int mid = l + r >> 1;
	msort(ls(x), l, mid); msort(rs(x), mid + 1, r);
	merge(x, l, mid, r);
}

il void query(int x, int l, int r, int ql, int qr) {
	if (l > qr || r < ql) return;
	if (l >= ql && r <= qr) return ans += num[x];
	int mid = l + r >> 1;
	query(ls(x), l, mid, ql, qr); query(rs(x), mid + 1, r, ql, qr);
}

int main() {
	int T = read(); while (T--) {
		read(n); rer(i, 1, n, a);
		msort(1, 1, n); int q = read();
		while (q--) {
			ans.clear(); int l, r; read(l, r);
			query(1, 1, n, l, r); vector <int> ep;
			int len = ans.size(), ot = INF;
			rep1(i, 0, len - 1) rep1(j, i + 1, len - 1) ot = my_min(ot, ans[i] | ans[j]);
			write(ot, '\n');
		}
	}
	rout;
}
```

---

## 作者：灵茶山艾府 (赞：5)

从特殊到一般。

### 一

如果 $a$ 中只有 $0$ 和 $1$，我们只需要知道区间内是否有两个 $0$。

如果有两个 $0$，那么最小 OR 是 $0$，否则是 $1$。

相当于只需要知道最小的两个数是多少，就能确定 OR 最小是多少。

### 二

如果 $a$ 中只有 $0,1,2,3$，在最坏情况下，最少需要知道几个数呢？

考虑下面这三个二进制数，其中 $?$ 表示 $0$ 或者 $1$。

$$
\begin{aligned}
0?\\
1?\\
1?
\end{aligned}
$$

如果只选择 $0?$ 和 $1?$，这在 $00$ 和 $10$ 的情况下是没问题的，但当它们分别是

$$
\begin{aligned}
01\\
10\\
10
\end{aligned}
$$

只选择 $01$ 和 $10$ 会算出 OR 为 $11$，但是选择 $10$ 和 $10$ 会算出 OR 为 $10$。

**猜想**：在 $a$ 中只有 $0,1,2,3$ 的情况下，至少要知道最小的 $3$ 个数，才能保证**一定**可以得到 OR 的最小值。

**证明**：分类讨论。

1. 如果有两个 $0?$，那么 OR 的最高位肯定是 $0$，问题变成一个比特，也就是 $a$ 中只有 $0$ 和 $1$ 的情况。我们已经知道，这只需要知道最小的 $2$ 个数。
2. 如果没有 $0?$ 只有 $1?$，那么 OR 的最高位肯定是 $1$，所以同上，变成一个比特的问题，也只需要知道最小的 $2$ 个数。
3. 如果恰好有一个 $0?$，其余的是 $1?$，继续分类讨论：
    - 如果 $0?$ 和 $1?$ 的 OR 最小，那么 $1?$ 这边只需要选最小的数。
    - 如果 $1?$ 和 $1?$ 的 OR 最小，问题变成上面讨论的第 2 点，需要知道 $1?$ 中最小的 $2$ 个数。
    - 所以知道最小的 $3$ 个数就行，OR 的最小值一定是这 $3$ 个数中的 $2$ 个数的 OR。

### 三

如果 $a[i]$ 的范围是 $[0,7]$，至少要知道最小的几个数，才能保证**一定**可以得到 OR 的最小值？

至少要知道最小的 $4$ 个数，证明方式同上。

按照如下方式构造，可以使 OR 的最小值一定来自第三小和第四小的数的 OR。

$$
\begin{aligned}
011\\
101\\
110\\
110
\end{aligned}
$$

如果 $a[i]$ 的范围是 $[0,15]$，构造方法如下：

$$
\begin{aligned}
0111\\
1011\\
1101\\
1110\\
1110
\end{aligned}
$$

### 四

总的来说，通过**数学归纳法**可以证明，OR 的最小值一定是最小的 $31$ 个数中选 $2$ 个数的 OR。

所以用**线段树**维护区间内最小的 $31$ 个数，问题就变成 $C(31,2)$ 的暴力枚举了。

```go
package main
import ("bufio";."fmt";"os")
func min(a, b int) int { if b < a { return b }; return a }

type seg [][]int

// 合并两个有序数组，保留前 k 个数
func merge(a, b []int) []int {
	const k = 31
	i, n := 0, len(a)
	j, m := 0, len(b)
	res := make([]int, 0, min(n+m, k))
	for len(res) < k {
		if i == n {
			res = append(res, b[j:min(j+k-len(res), m)]...)
			break
		}
		if j == m {
			res = append(res, a[i:min(i+k-len(res), n)]...)
			break
		}
		if a[i] < b[j] {
			res = append(res, a[i])
			i++
		} else {
			res = append(res, b[j])
			j++
		}
	}
	return res
}

func (t seg) build(a []int, o, l, r int) {
	if l == r {
		t[o] = a[l-1 : l]
		return
	}
	m := (l + r) >> 1
	t.build(a, o<<1, l, m)
	t.build(a, o<<1|1, m+1, r)
	t[o] = merge(t[o<<1], t[o<<1|1])
}

func (t seg) query(o, l, r, L, R int) []int {
	if L <= l && r <= R {
		return t[o]
	}
	m := (l + r) >> 1
	if R <= m {
		return t.query(o<<1, l, m, L, R)
	}
	if m < L {
		return t.query(o<<1|1, m+1, r, L, R)
	}
	return merge(t.query(o<<1, l, m, L, R), t.query(o<<1|1, m+1, r, L, R))
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, n, q, l, r int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n)
		a := make([]int, n)
		for i := range a {
			Fscan(in, &a[i])
		}
		t := make(seg, n*4)
		t.build(a, 1, 1, n)
		for Fscan(in, &q); q > 0; q-- {
			Fscan(in, &l, &r)
			b := t.query(1, 1, n, l, r)
			ans := 1 << 30
			for i, v := range b {
				for _, w := range b[:i] {
					ans = min(ans, v|w)
				}
			}
			Fprintln(out, ans)
		}
	}
}
```

**时间复杂度**：$\mathcal{O}(nk + q(k\log n+k^2))$，其中 $k=31$。

**空间复杂度**：$\mathcal{O}(nk)$。


---

## 作者：只鹅烧烤二度 (赞：4)

题意：给出有 $n$ 个数的数组 $a$ ，对于 $q$ 个询问，分别求出在 $l$ 到 $r$ 的区间内任取两个不同的数 $a_i$ , $a_j$ 最小的 $a_i|a_j$ 。

提供一种暴力数据结构 $O(nlog^2n)$ 做法。

首先考虑如何快速忽略 $l,r$ 全局求取两数或的最小值，对于这种位运算的最值问题可以考虑0/1trie解决，一种朴素的想法是对于区间内每一个数分别求最大的或值，然而每次查询的时间复杂度并不优，因此尝试直接于trie上求全局解。

假设当前位置在trie上的某个节点 $p$ 且当前是二进制从小到大的第 $i$ 位，有以下三种情况。

假设 $p$ 左儿子所在的子树有至少两个值：那么当前位肯定能使得或的结果等于0，前往左节点。

假设 $p$ 左儿子子树没有值：则不用处理，并前往右节点。

假设 $p$ 左儿子子树恰好有一个值：寻找出左儿子子树中的这个值$x$，然后发现他与其余数或的值与 $x+2^i$ 与这些数或的值相同，于是将 $x+2^i$ 添加进trie然后继续求值。

于是我们在建立了这棵trie的前提下，最多重新添加了 $logn$ 个值并递归了 $logn$ 层解决了这个全局求或最小值得问题，复杂度除去建树是 $log^2n$ 的。

那么对于子区间内求的问题也较为好办了，只需要建一棵可持久化trie，重复上面的流程解决此问题，需要注意的是直接往trie上多添加值再删除的流程较为麻烦，我们可以在一个辅助数组存这样的值，然后查询值的时候看辅助数组内的数有多少个于此节点上即可。

```cpp
#include <bits/stdc++.h>
#define ls(p) tr[p].ls
#define rs(p) tr[p].rs
using namespace std;
const int N=1e5+10;
int t,n,a[N],node,tmp[N],cnt1,T[N];
struct TREE
{
	int ls,rs,cnt;
}tr[N*70];

int update(int pre,int x)
{
	int p=++node,tmp=node;
	for(int i=30;i>=0;i--)
	{
		tr[p]=tr[pre];tr[p].cnt++;
		if((1<<i)&x) pre=rs(pre),tr[p].rs=node+1;
		else pre=ls(pre),tr[p].ls=node+1;
		p=++node;
	}tr[p]=tr[pre];tr[p].cnt++;
	return tmp;
}

int query(int u,int v)
{
	int sum=0,fv=v,tmp1=node;cnt1=0;
	for(int i=30;i>=0;i--)
	{
		int num=tr[ls(v)].cnt-tr[ls(u)].cnt,pos=-1;
		for(int j=1;j<=cnt1;j++)
		{
			int tmp1=tmp[j]^(tmp[j]&((1<<i)-1));
			if(tmp1==sum) num++,pos=tmp[j];
		}
		if(num>=2) {u=ls(u),v=ls(v);continue;}
		if(num==1)
		{
			int nu=u,nv=v,num=sum;
			if(pos!=-1) tmp[++cnt1]=pos+(1<<i);
			else
			{
				for(int j=i;j>=0;j--)
				{
					if(tr[ls(nv)].cnt-tr[ls(nu)].cnt) nu=ls(nu),nv=ls(nv);
					else nu=rs(nu),nv=rs(nv),num+=1<<j;
				}
				tmp[++cnt1]=num+(1<<i);
			}
		}
		u=rs(u),v=rs(v),sum+=1<<i;
	}
	return sum;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		node=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			T[i]=update(T[i-1],a[i]);
		}
		int q,l,r;
		scanf("%d",&q);
		while(q--)
		{
			scanf("%d %d",&l,&r);
			printf("%d\n",query(T[l-1],T[r]));
		}
	}
}

---

## 作者：迟暮天复明 (赞：2)

题解区好像没见到我的做法。可能是我不知道什么是可持久化字典树的缘故。

考虑建出字典树。那么对于一次询问，如果某一位上往 $0$ 走的分支有至少两个数在区间内，那么就走下去。如果一个也没有，就朝另一边走下去。这个是很好解决的，只要在字典树上每个节点记录其子树下所有数字的下标即可。

那么恰好有一个的情况呢？

我发现，如果恰好有一个数，那么最坏情况下整个过程中这样的数也不会超过 $\log V$ 个。所以我可以在往 $1$ 的方向走的时候，拿一个 `vector` 把这样子孤立出来的数给记录下来。那么 `vector` 里的数和当前字典树节点里面的数，本质上是一致的，可以一起处理。直到字典树走到底的时候，把 `vector` 里的数字两两配对算答案即可。

由于我每次询问只会两两配对不超过一次，所以时间复杂度应该是 $O(q\log n\log V+q\log^2V)$ 的。前者是递归求解的复杂度，后者是两两配对算答案的复杂度。

我这种做法需要一些分类讨论，但是不需要思考，也不需要有什么前置知识或者性质的观察。

以下是代码。


```cpp
int nxt[4000000][2],cnt,a[100010];
std::vector<int>A[4000000];
void insert(int x,int id){
  int p=1;
  nrep(i,30,0){
    A[p].pb(id);
    int c=(x>>i)&1;
    if(!nxt[p][c])nxt[p][c]=++cnt;
    p=nxt[p][c];
  }
  A[p].pb(id);
}
int solve(int,int,int,int);
int solve(int l,int r,std::vector<int>_,int p,int n){
  if(n<0)return 0;
  int P=nxt[p][0],Q=nxt[p][1];
  auto X=std::lower_bound(A[P].begin(),A[P].end(),l),Y=std::upper_bound(A[P].begin(),A[P].end(),r);
  auto _X=std::lower_bound(A[Q].begin(),A[Q].end(),l),_Y=std::upper_bound(A[Q].begin(),A[Q].end(),r);
  --Y,--_Y;
  int S=std::distance(X,Y)+1,T=std::distance(_X,_Y);
  if(S+T<2){
    if(std::distance(X,Y)>=0){
      for(auto i=X;i!=Y;++i)_.pb(*i);
      _.pb(*Y);
    }
    if(std::distance(_X,_Y)>=0){
      for(auto i=_X;i!=_Y;++i)_.pb(*i);
      _.pb(*_Y);
    }
    int minn=1e18;
    for(int i:_)for(int j:_)if(i!=j)ckmin(minn,a[i]|a[j]);
    return minn&((1ll<<(n+1))-1);
  }int ss=0;
  for(int i:_)if(!((a[i]>>n)&1))++ss;
  if(S==0){
    if(ss>=2){
      int minn=1e18;
      for(int i:_)for(int j:_)if(i!=j)ckmin(minn,a[i]|a[j]);
      return minn&((1ll<<(n+1))-1);
    }
    return solve(l,r,_,nxt[p][1],n-1)|(1ll<<n);
  }
  else if(S==1){
    if(ss>=1){
      _.pb(*X);
      int minn=1e18;
      for(int i:_)for(int j:_)if(i!=j)ckmin(minn,a[i]|a[j]);
      return minn&((1ll<<(n+1))-1);
    }
    _.pb(*X);
    return solve(l,r,_,nxt[p][1],n-1)|(1ll<<n);
  }
  else{
    std::vector<int>__;
    for(int i:_)if(!((a[i]>>n)&1))__.pb(i);
    if(_.empty())return solve(l,r,nxt[p][0],n-1);
    else return solve(l,r,__,nxt[p][0],n-1);
  }
}
int solve(int l,int r,int p,int n){
  if(n<0)return 0;
  if(A[nxt[p][0]].empty()||A[nxt[p][0]].end()[-1]<l||A[nxt[p][0]][0]>r)return solve(l,r,nxt[p][1],n-1)|(1ll<<n);
  int P=nxt[p][0];
  auto X=std::lower_bound(A[P].begin(),A[P].end(),l),Y=std::upper_bound(A[P].begin(),A[P].end(),r);
  --Y;
  if(std::distance(X,Y)<0)return solve(l,r,nxt[p][1],n-1)|(1ll<<n);
  else if(std::distance(X,Y)==0)return solve(l,r,{*X},nxt[p][1],n-1)|(1ll<<n);
  else return solve(l,r,nxt[p][0],n-1);
}
void solve(){
  int n;read(n);
  rep(i,1,cnt)nxt[i][0]=nxt[i][1]=0,A[i].clear();
  cnt=1;
  rep(i,1,n){
    read(a[i]);insert(a[i],i);
  }
  int q;read(q);
  while(q--){
    int l,r;read(l),read(r);
    print(solve(l,r,1,30),'\n');
  }
}
```

---

## 作者：WaterSun (赞：2)

# 思路

发现 $2^k$ 大的数，最终的答案一定由前 $k + 1$ 小的元素组成。

考虑数学归纳法，显然当 $k = 1$ 成立。假令 $k'$ 时成立，证明 $k = k' + 1$ 时成立即可：

1. 若第 $k$ 位有两个及以上的 $0$，显然最终答案的第 $k$ 位一定为 $0$，因此考虑前面的 $k - 1$ 位，显然取前 $k + 1$ 小的数是对的。

2. 若第 $k$ 位只有一个 $0$，显然最终答案的第 $k$ 位一定为 $1$，因此考虑前面的 $k - 1$ 位，显然取前 $k + 1$ 小的数成立。

3. 若第 $k$ 位没有 $0$，显然最终答案的第 $k$ 位一定为 $1$，考虑前 $k - 1$ 位，显然取前 $k + 1$ 小的数可以。

因此我们不妨使用线段树维护区间前 $31$ 小。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e5 + 10,inf = (int)(1e18) + 10;
int n,q;
int arr[N];
vector<int> emp;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)
    
    struct value{
        vector<int> v;

        value friend operator +(const value &a,const value &b){
            value v;
            for (auto x:a.v) v.v.push_back(x);
            for (auto x:b.v) v.v.push_back(x);
            sort(v.v.begin(),v.v.end());
            while (v.v.size() > 31) v.v.pop_back();
            return v;
        }
    };

    struct node{
        int l,r;
        value val;
    }tr[N << 2];

    inline void pushup(int u){
        tr[u].val = tr[ls(u)].val + tr[rs(u)].val;
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r,{emp}};
        if (l == r) return tr[u].val.v.push_back(arr[l]),void();
        int mid = l + r >> 1;
        build(ls(u),l,mid),build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline auto query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].val;
        int mid = tr[u].l + tr[u].r >> 1;
        value res = {emp};
        if (l <= mid) res = res + query(ls(u),l,r);
        if (r > mid) res = res + query(rs(u),l,r);
        return res;
    }

    #undef ls
    #undef rs
}T;

inline void solve(){
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    T.build(1,1,n);
    q = read();
    while (q--){
        int l,r,ans = inf;
        l = read(),r = read();
        vector<int> res = T.query(1,l,r).v;
        int len = res.size();
        for (re int i = 0;i < len;i++){
            for (re int j = i + 1;j < len;j++) ans = min(ans,res[i] | res[j]);
        }
        printf("%lld\n",ans);
    }
}

signed main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：hsaht2426 (赞：1)

按位贪心。

但是直接考虑 $\text{trie}$ 会出现合并子树答案的情况，不好做。

单个考虑不好做，能不能用**整体法**呢？

是可以的。

分讨一下某一位的情况。

- 有超过两个数该位为 $0$ 以上，答案该位为 $0$，直接递归处理该位为 $0$ 的数的情况。

否则答案该位为 $1$。

- 有一个 $0$，与该位为 $1$ 的数合并递归处理。

- 没有，直接处理。

然后**从简单情形入手**。

我们只需要知道最开始 $0$ 的个数是 $\ge 2$，$=1$ 还是 $=0$。

只用记录开始的前 $2$ 小数即可。

然后考虑**递推**回去，如果我们是情况 $2$，要添一位：

考虑我们每次去掉一位其实最多只会多一个需合并的数，且加入的数必然比原有数集的数小，所以等价于多记录一个最小值，与原来集合的前 $k$ 小合并就等价于当前集合的前 $k+1$ 小。

否则如果我们是情况 $1,3$：

那么答案一定不会被影响：

充分性：前 $k$ 小答案一定包含在前 $k+1$ 小中。

显然成立。

必要性：前 $k+1$ 小答案合法。

这个其实是不对的，但是不合法只会因为 $k+1>r-l+1$，很好处理，取数的数量与区间长取个 $\min$ 即可。

所以综上所述，我们只需要取区间中前 $\min(\log \omega+1,r-l+1)$ 小数暴力计算即可保证正确性。($\log \omega=\log 10^9=30$)

取区间中前 $\min(\log \omega+1,r-l+1)$ 小数可以在 $\text{ST}$ 表上二分加优先队列。

时间复杂度 $O(n \log n+q \log^2 \omega)$，空间复杂度 $O(n \log n)$。

代码：(年代较久远)
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int t,n,st[N+100][20],a[N+100],b[N+100],lg[N+100];
int Min(int l,int r){
	int len=lg[r-l+1];
	return min(st[l][len],st[r-(1<<len)+1][len]);
}
struct node{
	int l,r;
};
bool operator <(const node &chrono,const node &stasis){
	return Min(chrono.l,chrono.r)>Min(stasis.l,stasis.r);
}
priority_queue<node> q;
void choose(int l,int r){
	int cnt=min(31,r-l+1);
	q.push((node){l,r});
	while(cnt){
		node now=q.top();
		q.pop();
		int num=Min(now.l,now.r);
		int pos=now.l;
		b[cnt]=num;
		cnt--;
		int L=now.l,R=now.r,mid=L;
		while(L<=R){
			mid=(L+R)/2;
			if(Min(L,mid)==num) pos=mid,R=mid-1;
			else L=mid+1;
		}
		if(now.l!=pos) q.push((node){now.l,pos-1});
		if(now.r!=pos) q.push((node){pos+1,now.r});
	}
	while(!q.empty()) q.pop();
}
int sol(int l,int r){
	int res=2e9+7;
	int cnt=min(31,r-l+1);
	choose(l,r);
	for(int i=1;i<=cnt;i++)
		for(int j=i+1;j<=cnt;j++)
			res=min(b[i]|b[j],res);
	return res;
}

int main(){
	for(int i=2;i<=N;i++) lg[i]=lg[i/2]+1;
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],st[i][0]=a[i];
		for(int i=1;(1<<i)<=n;i++) 
			for(int j=1;j+(1<<i)-1<=n;j++)
				st[j][i]=min(st[j][i-1],st[j+(1<<i-1)][i-1]);
		int Q;
		cin>>Q;
		for(int i=1;i<=Q;i++){
			int l,r;
			cin>>l>>r;
			cout<<sol(l,r)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2500}$
---
### 解题思路：

要求的是任意两个位置的或的最小值，感性的思路就是要取一些尽可能小的，最高位尽可能低的数。

此时可以想到一个简单的规约性质，当出现了两个最高位比另一个低的数，最高位高的那一个就一定用不到了。类似地，对于一些最高位相同的数，次高位同样可以用类似的性质进行规约。这其实就预示着其实真正能用的数并不多。

直接通过这种方法实现代码会比较麻烦，而且复杂度也无法简单分析。

尝试构造出一种不能被这种规约方法优化的最大集合。首先对于最高位，只能有一个的最高位是低于其它的。同理对于次高位，在所有的最高位相同的中只能有一个次高位较小。并以此类推，最后的画风是这样的：

$01\dots$

$101\dots$

$1101\dots$

$11101\dots$

$\dots$

也就是最大的集合大小只有 $\log a$，其中 $a$ 表示值域。

---
但即使是确定了集合大小，通过枚举每一位进行规约依然效率不高。此时可以发现这样被优化掉的部分一定是将所有数从小到大排序之后一个后缀，证明可以考虑如果一个较小的数被优化掉了，则比这个数大的一定也可以被优化较小数的两个数优化掉了。

这样就只需要维护区间最小的 $\log a$ 个数了，本题中维护 $31$ 个数就行了。具体实现的时候可以用线段树或者 $\text{ST}$ 表进行区间操作，合并区间的时候用类似于归并排序的方法就行。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int T,n,q,a[MAXN],l,r;
struct str{
	int num[35],cnt;
}t[MAXN*4],zero;
void init(){
	for(int i=1;i<=4*n;i++)
	t[i]=zero,a[i]=0;
}
str work(str a,str b){
	str c;
	c.cnt=min(31,a.cnt+b.cnt);
	int p1=1,p2=1;
	for(int i=1;i<=c.cnt;i++){
		if((p1<=a.cnt&&a.num[p1]<=b.num[p2])||(p2>b.cnt)){
			c.num[i]=a.num[p1];
			p1++;continue;
		}
		if((p2<=b.cnt&&a.num[p1]>b.num[p2])||(p1>a.cnt)){
			c.num[i]=b.num[p2];
			p2++;continue;
		}
	}
	return c;
}
void build(int p,int l,int r){
	if(l==r){
		t[p].cnt=1;
		t[p].num[1]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p]=work(t[p*2],t[p*2+1]);
}
str query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[p];
	int mid=(l+r)/2;
	str ans=zero;
	if(L<=mid)ans=work(ans,query(p*2,l,mid,L,R));
	if(R>mid)
	ans=work(ans,query(p*2+1,mid+1,r,L,R));
	return ans;
}
int main(){
	scanf("%d",&T);
	while(T--){
		init();
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		build(1,1,n);
		scanf("%d",&q);
		while(q--){
			scanf("%d%d",&l,&r);
			str now=query(1,1,n,l,r);
			int ans=2147483647;
			for(int i=1;i<=now.cnt;i++)
			for(int j=i+1;j<=now.cnt;j++)
			ans=min(ans,now.num[i]|now.num[j]);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```




---

## 作者：Duramente (赞：1)

## 题意
有一个长度为 $n$ 的序列 $a$，$q$ 组询问，每次查询一个区间 $[l,r](l<r)$，问 $[l,r]$ 中的数的两两之间按位 or 最小是多少。  
$n,q\leq 10^5$

## Solution  
先来想想一次询问怎么做。  
考虑从高到低确定每个二进制位，发现如果这一位能贪心地选 0 一定要选。  
如何看这一位能不能选 0 呢，我们查询 $[l,r]$ 中这一位是 0 的个数。  
设现在能选的值域是 $[L,R]$，  
如果有至少两个，那答案的这一位就可以是 0，接下来只能在值域 $[L,mid]$ 中选数了。  
如果说一个都没有，那我们直接在值域 $[mid+1,R]$ 中选数。  
如果恰好有一个，我们两边都进去递归肯定是不划算的，我们可以把左边一段的唯一那个数找出来，这一位变成 1，然后放进右半段，询问完再删除。

问题需要在一段区间内查找一段值域的数字出现的次数，容易想到用主席树来维护。

注意要记得回收内存，每次单独插入数字后，把内存回收掉，否则空间会是 $O(nlog^2n)$ 的。  

## 额外的想法  
因为根据上述操作，每一层最多有一个数字被扔到旁边去会被选择，因此最多用来选择的数是 $O(\log A)$ 级的，$A$ 是数字值域，而被扔到右边去的都是最小的数，所以说维护每个区间最小的 31 个数暴力找 or 最小值也是可以的。  
31 是因为还要多算本身就在递归到的右边区间的最小一个。

## Code  

[153103647](https://codeforces.com/contest/1665/submission/153103647)



---

## 作者：Yakurii (赞：1)

这是近期最简单的一道 div2 最后一题。

我们首先感性分析一下，由于我们可以按位贪心，第一步必然是要或和的最高位尽量小：设当前 $a[l ... r]$ 的最高位最大值为 $k$ ，若 $a[l ... r]$ 中有至少两个数最高位不为 $k$，那么我们第 $k$ 位的贡献就可以忽略了，若所有数最高位均为 $k$ ，那么我们累加 $2^k$ 后第 $k$ 位的贡献也可以忽略了，最难办的是恰有一个数的情况，我们想要猜一个看起来很显然的结论：这个数必然会计入答案，但遗憾的是，这是错的，比如像 $128,128,1$ 这种就会卡掉。

但是我们考虑有没有什么我们漏掉的东西：如果将限制变得简单，当我们只剩 $0,1$ 两种数时，我们只要计算 $a$ 中最小的两个数或和即可，它一定是答案，那么对于更高的位呢，我们能不能也取最小的若干个数，假设为 $x$ ？

直觉告诉我们 $x$ 不会太大，事实上我们可以归纳地证明，$x$ 是 $\log$ 级别的，具体地就是我们上面的那三种情况，前两种满足二进制最高位增加 $1$ ，但 $x$ 不变；第三种满足二进制最高位和 $x$ 同时增加 $1$ 。

实现时我们不需要那些炫技的数据结构，像题解里说的那个 non-practical 的 van Emde Boas tree，我们直接用倍增 ST 表归并出我们需要的前 $\log$ 个值，然后平方暴力找，不难发现这样复杂度是可以承受的。

总时间复杂度 $O(n \log n + q \log^2 v)$，空间复杂度 $O(n \log n \log v)$。

代码

```cpp
vector<int>f[N][18];
vector<int> upd(vector<int> x,vector<int> y){
	vector<int>tp,k; k.resize(x.size()+y.size());
	merge(x.begin(),x.end(),y.begin(),y.end(),k.begin());
	int bi=min((int)k.size(),31);
	for(int i=0;i<bi;i++) tp.pb(k[i]); return tp;
}vector<int> ask(int l,int r){
	vector<int>ret; ret.clear();
	for(int i=17;~i;--i) if(l+(1<<i)-1<=r) ret=upd(ret,f[l][i]),l+=(1<<i);
	return ret; 
}signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n); for(int i=1;i<=n;i++) f[i][0].clear();
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),f[i][0].pb(a[i]);
		for(int j=1;j<18;j++)
			for(int i=1;i+(1ll<<(j-1))<=n;i++)
				f[i][j]=upd(f[i][j-1],f[i+(1ll<<(j-1))][j-1]);
		scanf("%d",&Q);
		while(Q--){
			int l,r; scanf("%d%d",&l,&r);
			vector<int> p=ask(l,r); int ans=2e9;
			for(int i=0;i<p.size();i++)
				for(int j=i+1;j<p.size();j++)
					ans=min(ans,p[i]|p[j]);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

[Code by jiangly](https://codeforces.com/contest/1665/submission/153062010)。


---

## 作者：Pekac (赞：1)

[CF1665E](https://www.luogu.com.cn/problem/CF1665E)

直接做不是很好下手，考虑找些性质。

有一个比较显然的贪心，就是按位从高到低的考虑，如果当前位至少有 $2$ 个 $0$，就可以去掉该位为 $1$ 的数。但是时间上显然是不行的。

假如没有重复的数，可以发现扫到最后一位时，剩下的数的数量是 $\log V$ 的，证明省去。

于是我们就可以大胆的猜一个结论：对答案可能会产生贡献的数不超过 $1+\log V$ 个，且一定是最小的 $1+\log V$ 个。

最小是显然的。$\log V$ 可以通过刚刚的贪心感性理解一下，严谨的证明可以使用数学归纳法。不妨令 $V=\max\{a_i\}=2^k$。

显然，$k=1$ 时是成立的。

考虑 $k>1$ 的情况。

若第 $k$ 位有 $\ge 2$ 个 $0$，那么这一位最后肯定为 $0$，即在前 $k$ 位中找 $\min$，也就是 $k-1$ 个数。

若第 $k$ 位没有 $0$，那这一位一定是一，第 $k$ 位已经没有影响，还是 $k$ 个数。

否则，考虑前 $k-1$ 位时可能不需要第 $k$ 位为 $0$ 的数，故 $k+1$ 个数。

所以我们只需求出区间的前 $\min(31,r-l+1)$ 小的所有数，然后暴力求解即可，求出这些数可以用线段树。

时间复杂度：$\mathcal{O}(q\log n\log V+q\log^2V)$

---

## 作者：Unnamed114514 (赞：0)

有个结论是，决定答案的 $i,j$ 只会选取前 $\lceil\log V\rceil+1$ 个值。

证明如下：

令 $\lceil\log V\rceil=p$。

- $p=1$ 时显然成立。

- 在第 $p$ 位，若这个位为 $0$ 的数的数量 $\ge 2$，那么显然会从这些 $0$ 里面选，然后就递归到 $p-1$ 的情况，此时只需要 $p$ 个数，如果没有 $0$ 同理。

- 在第 $p$ 位，如果有 $1$ 个 $0$，那么此时如果要选 $0$，那么它一定比其它数都小，作为最小值加进去，然后在 $p-1$ 的情况下和其它数进行匹配，这样就只需要 $p+1$ 个数。

找区间前 $k$ 小，用超级钢琴的 trick 即可，每次找到区间最小值然后分裂区间，时间复杂度 $O(q\log V\log n)$。

---

## 作者：Forg1weN (赞：0)

# [CF1609F MinimizOR](https://www.luogu.com.cn/problem/CF1665E)

命题：知道值域 $V\in[0,2^{k}-1]$ 中区间 $[l,r]$ 前 $k+1$ 小的数即可知道 $\min\limits_{i\neq j} a_i|a_j$ 最小值。

证明：根据二进制，肯定是最高位为 $0$ 的数字与起来最小，假设现在考虑的位置为最高位 $k$ ，若当前有 $\ge 2$ 个 $0$ 或者全部都是 $1$ ，则显然其选出则的方案一定是选最小的两个最好，这样可以让下一位尽可能的优，这时候我们需要知道的数字集合在第 $k$ 位是不变的，为 $2$。

但是如果只有一个 $0$ 和若干个 $1$ 呢，则第 $k$ 位必然为 $1$ ，但是考虑下一位，其最小值可能由第 $k$ 位为 $1$ 的数的最小的两个和第 $k$ 位为 $0$ 的仅有的一个数，所以可见需要知道的数字集合在第 $k$ 位是变大了 $1$ 的，为 $3$。

以此类推，这样每一位都是最坏情况下，总共有从第 $k$ 位到第 $2$ 位需要为了下一位多知道一个数，所以总共需要知道的数字集合大小最大为 $2+(k-2+1)=k+1$。   

思路大体是这样。

如果将求前 $k$ 小的数字采用线段树不断删除最小值的方法，便可以省去一个 $\log V$ 的复杂度，最后时间复杂度 $O(\log^2V\times q\log n)$。

---

## 作者：xixisuper (赞：0)

# CF1665E MinimizOR 题解

数据结构题。

集训的时候场切了这一题，发现题解里好像没有用 01 trie 加暴力两两配对的做法，来发个题解。

本题解采用可持久化 01 trie 解决。

## 思路


简述题意：在区间中取两个数（位置不同），使得其**按位取或**后的值最小，输出最小值即可。

首先思考全局（不附加区间这一条件）如何求解。遇到位运算的数据结构题，考虑往 01 trie 上靠，我们先建一棵 01 trie，然后考虑如何寻找答案。

假设我们现在在 01 trie 第 $d$ 层，如果往第 $d+1$ 层通为 $0$ 的数的个数多于 $2$ 的话，我们选取的两个数一定在 $0$ 的那部分当中，因为或完后二进制下表示显然 $0$ 更小。如果没有 $0$，那我们只能走 $1$ 这个方向。

现在考虑有 $0$，但只有一个的情况，由于我们无法确定这个数是否对答案有贡献，我们不妨把它取出来，存到一个数组里。不难发现我们最多取出来 $\log A$ 个数（$A$ 为 $a$ 数列值域），最后我们把所有取出来的数进行一个暴力两两配对，取最小值即可。

最后考虑限定区间怎么做，不难发现我们 01 trie 只需要统计数的个数，相当于一个值域线段树，于是我们可持久化一下就过了。

程序包括建树和查询两部分，于是最后总时间复杂度为 $O(n\log A+q\log^2A)$。

## 代码

~~场上调了我半天，但最后过了，赢！~~

```cpp
#include <iostream>
#include <algorithm> 
#define ll unsigned int
using namespace std;
const ll N=1e5+3;
ll mi[32];
void init(){
	mi[0]=1;
	for(ll i=1;i<=31;i++) mi[i]=mi[i-1]<<1;
}
inline ll read(){
	register ll x=0;
	register char c=getchar();
	while(c<'0'||c>'9'){c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x;
}
ll tr[N*32][2],sum[N*32],tot,head[N];
ll n,A[N],q;
void add_(ll lst,ll &x,ll now,ll dep){
	x=++tot;
	sum[x]=sum[lst]+1;
	if(dep==32) return;
	tr[x][((now>>(31-dep))&1)^1]=tr[lst][((now>>(31-dep))&1)^1];
	add_(tr[lst][(now>>(31-dep))&1],tr[x][(now>>(31-dep))&1],now,dep+1);
}
ll get(ll lst,ll now,ll dep){
	if(dep==32) return 0;
	if(sum[tr[now][0]]-sum[tr[lst][0]]!=0) return get(tr[lst][0],tr[now][0],dep+1);
	return get(tr[lst][1],tr[now][1],dep+1)+mi[31-dep];
}
ll chk[100],top;
void ask(ll lst,ll now,ll dep,ll tonow){
	if(dep==32){
		chk[++top]=tonow;
		if(sum[now]-sum[lst]>1) chk[++top]=tonow;
		return;
	}
	if(sum[tr[now][0]]-sum[tr[lst][0]]>=2){
		ask(tr[lst][0],tr[now][0],dep+1,tonow);
		return;
	}
	if(sum[tr[now][0]]-sum[tr[lst][0]]==0){
		ask(tr[lst][1],tr[now][1],dep+1,tonow+mi[31-dep]);
		return ;
	}
	if(sum[tr[now][1]]-sum[tr[lst][1]]==1&&sum[tr[now][0]]-sum[tr[lst][0]]==1){
		ll a=get(tr[lst][1],tr[now][1],dep+1)+mi[31-dep];
		ll b=get(tr[lst][0],tr[now][0],dep+1);
		chk[++top]=a+tonow;chk[++top]=b+tonow;
		return; 
	}
	ll Ze=get(tr[lst][0],tr[now][0],dep+1);
	chk[++top]=Ze+tonow;
	ask(tr[lst][1],tr[now][1],dep+1,tonow+mi[31-dep]);
	return ;
}
ll T; 
int main(){
	init();
	T=read();
	while(T--){
		for(ll i=1;i<=tot;i++) head[i]=sum[i]=0;
		for(ll i=1;i<=tot;i++) tr[i][0]=tr[i][1]=0;
		tot=0;
		n=read();
		for(ll i=1;i<=n;i++){
			A[i]=read();
			add_(head[i-1],head[i],A[i],1);
		}
		q=read();
		while(q--){
			ll L,R,ans=2147483647;
			L=read(),R=read();
			top=0;
			ask(head[L-1],head[R],1,0);
			for(ll i=1;i<=top;i++){
				for(ll j=i+1;j<=top;j++){
					ans=min(ans,(chk[i]|chk[j]));
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：chzhc (赞：0)

### 题意

给出 $n$ 个数 $a_1 \sim a_n$，有 $q$ 次询问，每次给出 $l, r$，求 $\min\limits_{l \leq i <  j \leq r} a_i | a_j$。

数据范围：$2 \leq n \leq 10^5$，$0 \leq a_i < 2^{30}$，$1 \leq q \leq 10^5$。

### 做法 1

考虑莫队 + Trie 树。

首先将询问离线，考虑建 01 Trie，在 Trie 树上记录结点被到达的次数 $siz$。考虑怎么求出答案，从根结点往下走，若走 $0$ 边到达的结点的 $siz\geq 2$，那么走 $1$ 边一定不优，走 $0$ 边往下递归即可；否则只能往走 $1$ 边的结点递归，若此时有走 $0$ 边的结点，我们就记录下走 $0$ 边所能得到的值（顶多只有 $1$ 个），然后走 $1$ 边往下递归即可。递归到末端时记录该节点的值（若 $\geq2$ 个则只需要记录两个，因为只有两个有用），容易发现，答案一定在记录下的值中的某两个，暴力求即可。时间复杂度 $\mathcal O(n \sqrt{n} \log a + q \log^2 a)$。

容易发现不需要莫队，可持久化 trie 即可。时间复杂度 $\mathcal O(n \log a + q\log^2 a)$。

[评测链接](https://codeforces.com/contest/1665/submission/153626211)。

### 做法 2

有一个结论：如果所有数都小于 $2^k$，那么只需要考虑 $k + 1$ 个最小数字即可。

考虑归纳证明。

$k=1$ 时，只有两个数字 $0, 1$，显然只需要考虑这两个数字即可。

若结论对 $k$ 成立，那么我们现在只需要证明结论对 $k + 1$ 也成立即可。

1. 所有数字中第 $k$ 位都是 $1$，那么无论如何答案的第 $k$ 位一定是 $1$，问题转化为选出两个数使得前 $k - 1$ 位最小，由于结论对 $k$ 成立，故此时只需要 $k + 1$ 个数字即可；
2. 所有数字中第 $k$ 位是 $0$ 的数不少于 $2$ 个，则答案的第 $k$ 位一定是 $0$，此时我们只需要考虑第 $k$ 位为 $0$ 的数字，由于结论对 $k$ 成立，故此时只需要 $k + 1$ 个数字即可；
3. 所有数字中第 $k$ 位是 $0$ 的数恰好只有一个，那么无论如何答案的第 $k$ 位一定是 $1$，我们需要找到 $k$ 位上对应的那 $k + 1$ 个最小的数，这些数在 $k + 1$ 位上是前 $k + 2$ 个最小数，故此时只需要 $k + 2$ 个数字即可。

证毕。

线段树维护前 $30$ 小值即可。时间复杂度 $\mathcal O(n \log n + q \log^2 a)$。

---

## 作者：I_am_Accepted (赞：0)

### Preface

考场口胡可持久化 01Trie。考完发现这神奇线段树做法。

### Analysis

先来个结论。

------------

**结论：** 若区间中每个数均 $<2^k$，则每次询问只取区间前 $k+1$ 小值（若有多个数值相同，重复计入），两两作 $\text{OR}$ 后一定是正确答案。

**证明：** 归纳法。

基础步骤：若序列中所有数 $<2^1=2$，则取前 $2$ 小的数两两作即为答案。

归纳步骤：若序列中所有数 $<2^{k-1}$ 时成立。我们证明序列中所有数 $<2^k$ 时也成立。

1. 若序列中所有数 $\ge 2^{k-1}$，则全部将最高位 $2^{k-1}$ 减掉，这样就是所有数 $<2^{k-1}$ 的问题了。

2. 若序列中有两个及以上的数 $<2^{k-1}$，则答案必然在这些数之间，转化为所有数 $<2^{k-1}$ 的问题。

3. 若序列中只有一个数 $<2^{k-1}$，设为 $x$。则答案必然包含 $2^{k-1}$ 这一二进制位，所以将 $x$ 加上 $2^{k-1}$ 对答案无影响。但是这时最小的 $k-1$ 个值会变，我们把 $x$ 加进去（变为前 $k$ 小）则必然包含答案。转化到情况 $(1.)$。

至此，归纳成立，原命题得证。

------------

所以我们维护区间前 $31$ 小值即可。

注意 ST 表和 simple 的线段树会炸空间，我们维护区间最小值，然后每次改最小值为 $\inf$，这样 $31$ 次即可，最后记得改回来。

时间 $O(n+31q(31+\log n))$

### Code

[Link](https://codeforces.com/contest/1665/submission/153105645)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define N 100010
#define mid ((l+r)>>1)
#define ls (rt<<1)
#define rs (rt<<1|1)
#define endl '\n'
#define pi pair<int,int>
const int inf=2e9;
int n,a[N],q,s[32];
pi t[4*N];
void build(int rt,int l,int r){
	if(l==r){
		t[rt]=mkp(a[l],l);
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	t[rt]=min(t[ls],t[rs]);
}
pi que(int rt,int l,int r,int x,int y){
	if(l==x && r==y) return t[rt];
	if(y<=mid) return que(ls,l,mid,x,y);
	if(x>mid) return que(rs,mid+1,r,x,y);
	return min(que(ls,l,mid,x,mid),que(rs,mid+1,r,mid+1,y));
}
void add(int rt,int l,int r,int x,int val){
	if(l==r){
		t[rt]=mkp(val,l);
		return ;
	}
	if(x<=mid) add(ls,l,mid,x,val);
	else add(rs,mid+1,r,x,val);
	t[rt]=min(t[ls],t[rs]);
} 
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	build(1,1,n);
	cin>>q;
	int l,r,cnt,ans;
	while(q--){
		cin>>l>>r;
		cnt=min(r-l+1,31);
		For(i,1,cnt){
			s[i]=que(1,1,n,l,r).sec;
			add(1,1,n,s[i],inf);
		}
		For(i,1,cnt) add(1,1,n,s[i],a[s[i]]);
		ans=inf;
		For(i,1,cnt-1) For(j,i+1,cnt) ckmn(ans,a[s[i]]|a[s[j]]);
		cout<<ans<<endl;
	}
}
signed main(){IOS;
	int T;cin>>T;
	while(T--)work();
return 0;}
```

---

