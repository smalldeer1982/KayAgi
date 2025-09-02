# Permutation recovery

## 题目描述

Vasya 写下了一个由 $1$ 到 $n$ 的整数的排列 $p_1, p_2, \ldots, p_n$，即对于所有 $1 \leq i \leq n$，都有 $1 \leq p_i \leq n$，且 $p_1, p_2, \ldots, p_n$ 两两不同。之后，他又写下了 $n$ 个数 $next_1, next_2, \ldots, next_n$。其中 $next_i$ 表示满足 $i < j \leq n$ 且 $p_j > p_i$ 的最小下标 $j$。如果不存在这样的 $j$，则定义 $next_i = n + 1$。

傍晚放学回家时，Vasya 的笔记本被雨淋湿了，现在有些数字已经无法辨认。排列和一些 $next_i$ 的值完全丢失！如果某个 $i$ 的 $next_i$ 丢失了，则记 $next_i = -1$。

现在给定 $next_1, next_2, \ldots, next_n$（其中有些可能等于 $-1$）。请你帮助 Vasya 找出一个 $1$ 到 $n$ 的排列 $p_1, p_2, \ldots, p_n$，使得他可以把它写在笔记本上，并且所有 $next_i \neq -1$ 的位置都满足题目中的定义。

## 说明/提示

在第一个测试用例中，对于排列 $p = [1, 2, 3]$，Vasya 应该写下 $next = [2, 3, 4]$，因为排列中的每个数都小于其后面的数。显然这是唯一满足条件的排列。

在第三个测试用例中，所有 $next_i$ 都丢失了，因此任意一个排列都可以作为答案。

在第四个测试用例中，不存在满足条件的排列，因此答案为 $-1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
3
2 3 4
2
3 3
3
-1 -1 -1
3
3 4 -1
1
2
4
4 -1 4 5
```

### 输出

```
1 2 3
2 1
2 1 3
-1
1
3 2 1 4
```

# 题解

## 作者：AzusaCat (赞：12)

给你一个数组 $nxt$，你需要构造一个长为 $n$ 的排列 $p$，使得对任意 $i$，$p$ 中其后面第一个比 $p_i$ 大的数的位置是 $nxt_i$，如果 $nxt_i=n+1$ 则没有，如果 $nxt_i=-1$ 则这个位置没有限制。$n\leqslant 500000$。

这是一个构造做法。 

先不考虑 $-1$，可以发现如果不存在两个位置 $i,j$ 使得 $i<j<nxt_i<nxt_j$ 则一定有解，下面我们给出构造方法：

设 `dfs(l,r,x)` 表示当前确定 $p_l\dots p_r$ 的值，考虑这中间所有 $nxt_i=r+1$ 的位置，可以发现它们形成了若干“挡板”，我们继续递归 `dfs(l,i-1,x-1)` 这样做下去即可。用一个邻接表维护所有 $nxt_j=i$ 的 $j$，总复杂度 $O(n)$。

至于 $nxt_i=-1$ 的情况，根据我们刚才说的性质，将其置为 $i+1$ 即可。

[提交记录](https://codeforces.com/problemset/submission/1158/119721157)


---

## 作者：TheShadow (赞：7)

# 题面

[CF1158C Permutation recovery](https://www.luogu.org/problem/CF1158C)

# Solution

我们考虑给出的限制条件有什么用。

显然，如果是 $-1$ ，那么我们可以直接忽略掉。

如果 $nxt_i\not=-1$ ，那么，我们可以得到如下两个条件：

1.  $val_i<val_{nxt_i}$ 。
2.  $val_i>val_j,j\in[i+1,nxt_i-1]$ 。

我们要求的就是这样一个满足条件的序列。

我们可以将限制条件看作是边，那么我们将大的连向小的，

那么我们相当于是求图中的一个拓扑序，其中拓扑序越小的，对应的值就越大。

但是直接连边复杂度是 $O(n^2)$ 的，无法接受。

可以发现每个点都是连向一个区间，所以我们可以使用一个黑科技：**线段树优化连边**。

我们将要连向的区间在线段树上划分成一个个小区间，由线段树可知，这样的区间最多 $\log$ 个，所以时间复杂度和空间复杂度都变成了 $O(n\log n)$ ，就可以愉快的做这道题了。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 5e5+5;
int T,n,nxt[MAXN],head[MAXN<<2],num_edge,ru[MAXN<<2],val[MAXN],pos[MAXN],id[MAXN<<2];
struct Edge{
	int next,to;
	Edge(){}
	Edge(int next,int to):next(next),to(to){}
}edge[MAXN*40];
#define lc (cur<<1)
#define rc (cur<<1|1)
il build_tree(int cur,int l,int r){
	head[cur]=0,id[cur]=0,ru[cur]=1;
	if(l==r) return pos[l]=cur,id[cur]=l,void();
	edge[++num_edge]=Edge(head[cur],lc),head[cur]=num_edge,++ru[lc];
	edge[++num_edge]=Edge(head[cur],rc),head[cur]=num_edge,++ru[rc];
	build_tree(lc,l,mid),build_tree(rc,mid+1,r);
}
il updata(int cur,int l,int r,int L,int R,int pos){
	if(l>=L&&r<=R) return edge[++num_edge]=Edge(head[pos],cur),head[pos]=num_edge,++ru[cur],void();
	if(mid>=L) updata(lc,l,mid,L,R,pos);
	if(R>mid) updata(rc,mid+1,r,L,R,pos);
}
il solve(){
	read(n),num_edge=0;
	build_tree(1,1,n);
	for(ri i=1;i<=n;++i){
		read(nxt[i]);
		if(nxt[i]==-1) continue;
		if(nxt[i]!=n+1) edge[++num_edge]=Edge(head[pos[nxt[i]]],pos[i]),head[pos[nxt[i]]]=num_edge,++ru[pos[i]];
		if(i+1<=nxt[i]-1) updata(1,1,n,i+1,nxt[i]-1,pos[i]);
	}
	queue<int> q;q.push(1);ri cnt=n;
	while(!q.empty()){
		ri p=q.front();q.pop();
		if(id[p]) val[id[p]]=cnt--;
		for(ri i=head[p];i;i=edge[i].next){
			--ru[edge[i].to];
			if(!ru[edge[i].to]) q.push(edge[i].to);
		}
	}
	if(cnt) return puts("-1"),void();
	for(ri i=1;i<=n;++i) printf("%d ",val[i]);puts("");
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	for(ri i=1;i<=T;++i) solve();
	return 0;
}
```

# 总结

一道比较套路的题，感觉难度其实没有这么大。

---

## 作者：CYJian (赞：6)

~~这题怎么就黑了...~~

这里给一个不用线段树优化建图/拓扑排序的做法...

只需要一个sort...

---

我们令$p_i$表示第$i$个位置后面第一个比它大的位置.

首先我们需要判断一个方案是否合法.

如果我们将$i$和$p_i$用一条弧线连接起来, 容易发现不合法的情况只可能是两条弧线互相包含了一个端点(去掉共用一个端点的情况). 这样我们就可以用一个栈来判断方案是否合法.

然后再考虑找到一个合法解.

首先, 我们可以有一个非常naive的想法: 把所有位置按照$p_i$为第一关键字(从大到小), $i$为第二关键字(从小到大)排序, 然后按照排序的结果, 第一个赋值为$n$, 第二个赋值为$n-1$...然后就行了? 

对于没有-1的情况, 这样子是可以构造出一组合法解的. 但是如果存在了-1, 我们应该怎么办呢?

也很简单, 如果没有一个位置的$p_i$是它, 那么这个数只需要成为最小的数就没有影响了. 但是如果有至少一个位置的$p_i$是它, 那么它就至少要大于$p_i$等于它的那一些$i$. 只需要让这种位置的$p_i$等于$i+1$就解决问题了. (这种做法并不会导致不合法的情况, 稍加思索就能明白)

这样就可以不用写线段树优化建图了...下面抛出丑陋的代码.QwQ

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ge getchar()
#define Re read()

inline int read() {
	int t = 0, x = 0, ch;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = ge;
	return t ? -x : x;
}

const int MAXN = 500000;

struct Node {
	int id, v;

	friend bool operator < (Node a, Node b) {
		return a.v == b.v ? a.id < b.id : a.v > b.v;
	}
}St[MAXN + 1];

int p[MAXN + 1];
int S[MAXN + 1];
int res[MAXN + 1];
int top;
int n;
int P;

int main() {
	int T = Re, Err = 0;
	while(T--) { Err = 0;
		n = Re; S[top = 1] = n + 1;
		for(int i = 1; i <= n; i++) {
			p[i] = Re;
			while(S[top] <= i) top--;
			if(!Err && p[i] > S[top]) Err = 1;
			S[++top] = p[i];
			while(S[top] <= i) top--;
			St[i] = (Node){i, p[i]};
		}
		if(Err) { puts("-1"); continue; }
		for(int i = 1; i <= n; i++) if(p[i] != -1 && p[p[i]] == -1) St[p[i]].v = p[i] + 1;
		sort(St + 1, St + 1 + n);
		for(int i = 1; i <= n; i++) res[St[i].id] = n - i + 1;
		for(int i = 1; i <= n; i++) printf("%d%c", res[i], " \n"[i == n]);
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：5)

$O(n)$ 解法：

首先对于每个为 $-1$ 的 $nxt_i$，将其置为 $i+1$，然后从最小的 $nxt_i$ 开始还原这个排列，对所有等于 $nxt_i$ 的位置从右往左填写排列元素。

最后用单调栈判断生成的排列是否符合 $nxt$。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, n int
o:
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n)
		pos := make([][]int, n+2)
		nxt := make([]int, n)
		for i := range nxt {
			Fscan(in, &nxt[i])
			if nxt[i] == -1 {
				nxt[i] = i + 2
			}
			pos[nxt[i]] = append(pos[nxt[i]], i)
		}

		ans := make([]int, n)
		v := 1
		for _, p := range pos {
			for i := len(p) - 1; i >= 0; i-- {
				ans[p[i]] = v
				v++
			}
		}

		type pair struct{ v, i int }
		s := []pair{{1e9, n}}
		for i := n - 1; i >= 0; i-- {
			v := ans[i]
			for {
				if top := s[len(s)-1]; top.v > v {
					if top.i+1 != nxt[i] {
						Fprintln(out, -1)
						continue o
					}
					break
				}
				s = s[:len(s)-1]
			}
			s = append(s, pair{v, i})
		}
		for _, v := range ans {
			Fprint(out, v, " ")
		}
		Fprintln(out)
	}
}
```


---

## 作者：szh_AK_all (赞：2)

## 分析
首先考虑判断构造是否有解。

对于一个 $i$ 若 $nxt_i\ne -1$，则代表不存在一个 $j$ 满足 $a_j>a_i$ 且 $i<j<nxt_i$，而此时这样的 $j$ 恰好满足 $i<j<nxt_i<nxt_j$。

从而发现，无解当前仅当存在一对 $(i,j)$ 满足 $i<j<nxt_i<nxt_j$。

依次考虑每个位置 $i$，我们需要找到满足 $x<i$ 且 $nxt_x>i$ 的最小的 $nxt_x$，若 $nxt_x<nxt_i$，则代表无解。容易发现，我们可以用单调栈维护 $nxt$。

若有解，则考虑构造。我们可以贪心的让 $nxt$ 更大的位置 $i$ 放上更大的值，若存在一对 $(i,j)$ 满足 $nxt_i=nxt_j$ 且 $i<j$，那么我们应当让 $p_i>p_j$，不然 $nxt_i$ 便不合法了。

对于 $nxt_i=-1$ 的情况，钦定 $nxt_i=i+1$ 即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {
	int x, z;
	friend bool operator < (node l, node r) {
		if (l.z != r.z)
			return l.z > r.z;
		return l.x < r.x;
	}
	node(int aa = 0, int bb = 0) {
		x = aa;
		z = bb;
	}
} s[500005];

int nxt[500005], q[500005], ans[500005];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int l = 1;
		q[1] = n + 1;
		int p = 0;
		for (int i = 1; i <= n; i++) {
			cin >> nxt[i];
			while (q[l] <= i)
				l--;
			if (q[l] < nxt[i])
				p = 1;
			q[++l] = nxt[i];
			while (q[l] <= i)
				l--;
			if (nxt[i] == -1)
				nxt[i] = i + 1;
			s[i] = node(i, nxt[i]);
		}
		if (p) {
			cout << -1 << "\n";
			continue;
		}
		sort(s + 1, s + n + 1);
		for (int i = 1, j = n; i <= n; i++, j--)
			ans[s[i].x] = j;
		for (int i = 1; i <= n; i++)
			cout << ans[i] << " ";
		cout << "\n";
	}
}
```

---

## 作者：Exber (赞：1)

$O(n)$ 单调栈+递归构造即可，完全不需要线段树优化建图跑拓扑。

首先发现由于 $nxt_i=\min\{j|j>i,p_j>p_j\}$，所以 $a_{[i,nxt_i-1]}$ 都要比 $a_{nxt_i}$ 小，$nxt_{[i,nxt_i-1]}$ 也都要小于等于 $nxt_i$。设 $fir_i=\min\{j|nxt_j=i\}$，那么不难发现 $fir_i,i$ 构成了类似括号匹配的关系：

![](https://cdn.luogu.com.cn/upload/image_hosting/7rj4kf3m.png)

那么扫一遍序列，用单调栈找到最内层的“右括号”的位置 $pos$，刚开始单调栈中只有一个元素 $n+1$。扫到位置 $i$ 时：

- 先将单调栈顶小于等于 $i$ 的元素弹出；
- 若 $nxt_i=-1$，那么让 $nxt_i\to pos$；
- 否则：
  - 若 $nxt_i>pos$，那么无解；
  - 否则若 $nxt_i\not= pos$ 那么把 $nxt_i$ 加入单调栈；

可以通过下面的构造 $p$ 序列的方法证明这样构造 $nxt$ 是正确的：

不难发现，由于括号的嵌套关系，所以内层小段的构造方法和外层大段的基本相同，只需要加上一个偏移量即可，所以考虑递归构造。

设 $dfs(l,r,mov)$ 表示构造在括号 $lft_{nxt_r},nxt_r$ 中的 $p_{[l,r]}$ 这一段，并且整一段的偏移量为 $mov$。

显然边界条件是 $nxt_{[l,r]}=nxt_r$，这时只要构造 $\{r-l+1+mov,r-l+mov,r-l-1+mov,\dots,2+mov,1+mov\}$ 这样倒着的序列即可。

由于某个 “右括号” 也有可能是左括号，这时这两段要看作一段处理。所以先预处理出 $lb_i$ 表示以 $i$ 为右端点的“连通块”的左端点：

![](https://cdn.luogu.com.cn/upload/image_hosting/naguo7r4.png)

注意若 $i$ 不为“左括号”或者“右括号”，那么 $lb_i=i$。

在 $dfs(l,r,mov)$ 中：

1. 初始化一个空队列 $vec$，令 $pmov=mov$；
2. 从右往左扫过区间，扫到 $i$ 时：
   - 若 $nxt_i=nxt_r$，说明 $p_i$ 属于最外层的括号，那么把 $i$ 放入队列 $vec$ 的末尾，最后再处理；
   - 若 $nxt_i\not=nxt_r$，说明 $p_i$ 属于内层的某个括号中，那么递归处理 $dfs(lb_i,i,pmov)$，令 $i\to lb_i-1$，$pmov\to pmov+i-lb_i+1$；
3. 队列 $vec$ 中的元素 $i$ 都满足 $nxt_i=nxt_r$，并且队列中元素是从大到小排列的。那么参照 $nxt_{[l,r]}=nxt_r$ 情况的构造方法，不断从队头取出元素 $i$，令 $p_i\to pmov$，$pmov\to pmov+1$ 即可。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int S=500005;

int n,nxt[S];
int sta[S];
int lb[S],a[S];

void dfs(int l,int r,int mov)
{
	int len=r-l+1,nxmov=mov;
	vector<int> vec;
	for(int i=r;i>=l;i--)
	{
		if(nxt[i]!=nxt[r]) dfs(lb[i],i,nxmov),nxmov+=i-lb[i]+1,i=lb[i];
		else vec.push_back(i);
	}
	for(int u:vec) a[u]=++nxmov;
}

inline void slove()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&nxt[i]);
	int top=1;
	sta[1]=n+1;
	for(int i=1;i<=n;i++)
	{
		while(sta[top]<=i) top--;
		if(nxt[i]==-1) nxt[i]=sta[top];
		else
		{
			if(nxt[i]>sta[top])
			{
				puts("-1");
				return;
			}
			else if(nxt[i]<sta[top]) sta[++top]=nxt[i];
		}
	}
	for(int i=1;i<=n;i++) lb[i]=i;
	for(int i=1;i<=n;i++) lb[nxt[i]]=min(lb[nxt[i]],lb[i]);
	dfs(1,n,0);
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	printf("\n");
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T-->0) slove();
	return 0;
}
```



---

## 作者：Minuit (赞：1)

### 题意

对于一个排列 $a_1...a_n$ ,  $next_i$ 表示排列中$i$后面第一个比 $a_i$ 大的位置.现给定一个排列的一部分 $next_i$ 数组,试据此构造一个排列。
若 $next_i=n+1$ 表示 $i$ 后面没有比它更大的数, $next_i=-1$ 表示不确定,$n \leq 5*10^5$ .

### 法1:   $O(nlogn)$

考虑定义,对于任意一个 $nexti$ 不等于 $-1$ 的位置 $i$ ,有$a_i>a_j(i+1\leq j \leq nexti-1) , a_{next_i} > a_i$ 成立,显然连边+拓扑排序,用线段树优化连边做到 $O(nlogn)$ 即可。

### 法2:   $O(n)$

- **Step1** 考虑没有 $-1$  ,且 $next$ 互不相同怎么做.由于交叉必然无解,所以形成的区间是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/7g8l6oph.png)

容易发现,**如果 $next$ 互不相同**,我们按照 $next$ 从大到小排序依次填数,方案必定是合法的,原因在于,一个位置有比另一个位置小的限制,当且仅当被一个 $(i,next_i)$ 的区间覆盖,排序后就保证了右边的比左边小,所以必然合法。

- **Step2** 考虑有 $next$ 相同怎么做.显然,对于 $next$ 相等的位置,越靠前,数越大,对于这些位置按照从小到大排序即可。

- **Step3** 考虑有 $-1$ 怎么做.相当于在不考虑 $-1$ 形成的区间中加入许多新区间,使其合法,如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/85f8io39.png)

容易发现,只要让 $i$ 直接指向 $i+1$ 就不会产生任何交叉区间.如图:

![](https://cdn.luogu.com.cn/upload/image_hosting/bn0q0vpt.png)

用一个 vector 存储某个位置作为 $next$ 被哪些点指向,扫一遍,依次填数,就是一种合法方案.

---

## 作者：vectorwyx (赞：1)

没有 $-1$ 时的限制比有 $-1$ 的限制严格，所以先考虑没有 $-1$ 的情况。$nxt_i=j$ 意味着 $p_i>p_{[i+1,j)}\&p_i<p_j$。图论视角，如果 $p_i>p_j$ 就连一条 $i\rightarrow j$ 的有向边，然后拓扑排序。有环则无解，否则按拓扑序构造答案必然合法。直接上线段树优化建图，搞定了！！1

然而这是练习，不是比赛，我们不能满足于此。注意到产生环的关键在于 $nxt_i\rightarrow i$ 这条”返祖边“。考虑先走一条返祖边，再顺流而下看看能不能走回起点。假如我们从 $s$ 出发走了一条返祖边到 $t$，然后不断往右走。我们能走回 $s$，当且仅当我们可以走到一个点 $i$ 使得 $nxt_i>s$。换言之，存在 $i<t,nxt_i>s$。这是啥？区间相交（包含不算相交）！如果存在两个区间 $[i,nxt_i),[j,nxt_j)$ 满足 $i<j<nxt_i<nxt_j$ 则无解，否则一定有解。这也表明了我们该如何处理 $-1$ 的位置——区间越短越不容易和其他区间相交，因此把所有 $nxt_i=-1$ 的 $nxt$ 赋为 $i+1$ 是最优的。

判断是否存在两个区间相交可以从右向左扫，用单调栈存储互不相交的若干个区间，每次把当前区间包含到的区间弹出，然后判断它和栈顶区间是否相交。问题转为已知 $nxt$ 数组如何构造解。以区间 $[1,n]$ 为例，找出所有 $nxt$ 等于 $n+1$ 的位置（这个可以预处理出来），把它们的 $p$ 依次赋为 $n,n-1,…$ 后递归求解即可。总时间复杂度线性。

代码如下：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

const int N=1e6;
int a[N],stk[N],top,ans[N],id;
vector<int> g[N];

void solve(int l,int r){
	//printf("solve(%d,%d),%d\n",l,r,id);
	if(l>r) return;
	int lst=l;
	//这两种写法都可以，只需要让子问题里的值小于右端点的值即可 
	for(auto i:g[r+1]){
		ans[i]=id--;
		solve(lst,i-1);
		lst=i+1;
	}
	/*for(auto i:g[r+1]) ans[i]=id--;
	for(auto i:g[r+1]){
		solve(lst,i-1);
		lst=i+1;
	}*/
	solve(lst,r);
}

signed main(){int T=read();while(T--){
	int n=read();g[n+1].clear();top=0;id=n;
	fo(i,1,n) a[i]=read(),g[i].clear();
	fo(i,1,n){
		if(a[i]==-1) a[i]=i+1;
		g[a[i]].pb(i);
	}
	go(i,n,1){
		while(top&&a[i]>=a[stk[top]]) top--;
		if(top&&a[i]>stk[top]) goto H;
		stk[++top]=i;
	}
	solve(1,n);
	out(ans,1,n);
	continue;
	H:puts("-1");
}
	return 0;
}
```


---

## 作者：duyi (赞：1)

# CF1158C Permutation recovery

考虑最大值所在的位置，它左边和右边的两个部分一定互不影响（如果左边有点的 $\text{next}_i$ 指向右边，则无解）。如此每次找最大值，得到一个可以递归的结构，也就是所谓的“笛卡尔树”。

不过现在我们还不知道最大值是谁。考虑哪些点**不能**成为最大值。对于每个 $\text{next}_i\neq -1$ 的 $i$，$[i,\text{next}_i)$ 里的数显然都不可能成为最大值（除非 $\text{next}_i$ 等于当前右端点加 $1$，我们特判）。那么可能成为最大值的位置，就是未被任何 $[i,\text{next}_i)$ 覆盖的位置。假设这样的位置有多个，我们取下标最小的那个。可以证明这样最可能构造出解。

用线段树维护这些覆盖。支持区间加（或减），求区间最小值。

时间复杂度 $O(n\log n)$。

参考代码：

```cpp
// problem: CF1158C
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 5e5, INF = 1e9;
int n, f[MAXN + 5], ans[MAXN + 5];
vector<int> vec[MAXN + 5];

struct SegmentTree {
	int mn[MAXN * 4 + 5], mn_pos[MAXN * 4 + 5], tag[MAXN * 4 + 5];
	void push_up(int p) {
		if(mn[p << 1] <= mn[p << 1 | 1]) {
			mn[p] = mn[p << 1];
			mn_pos[p] = mn_pos[p << 1];
		} else {
			mn[p] = mn[p << 1 | 1];
			mn_pos[p] = mn_pos[p << 1 | 1];
		}
	}
	void build(int p, int l, int r) {
		tag[p] = 0;
		if(l == r) {
			mn[p] = 0;
			mn_pos[p] = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		push_up(p);
	}
	void push_down(int p) {
		if(tag[p] != 0) {
			mn[p << 1] += tag[p];
			tag[p << 1] += tag[p];
			mn[p << 1 | 1] += tag[p];
			tag[p << 1 | 1] += tag[p];
			tag[p] = 0;
		}
	}
	void range_add(int p, int l, int r, int ql, int qr, int v) {
		if(ql <= l && qr >= r) {
			mn[p] += v;
			tag[p] += v;
			return;
		}
		int mid = (l + r) >> 1;
		push_down(p);
		if(ql <= mid) {
			range_add(p << 1, l, mid, ql, qr, v);
		}
		if(qr > mid) {
			range_add(p << 1 | 1, mid + 1, r, ql, qr, v);
		}
		push_up(p);
	}
	pii query_min(int p, int l, int r, int ql, int qr) {
		if(ql <= l && qr >= r) {
			return mk(mn[p], mn_pos[p]);
		}
		int mid = (l + r) >> 1;
		push_down(p);
		pii res = mk(INF, INF);
		if(ql <= mid) {
			res = query_min(p << 1, l, mid, ql, qr);
		}
		if(qr > mid) {
			ckmin(res, query_min(p << 1 | 1, mid + 1, r, ql, qr));
		}
		push_up(p);
		return res;
	}
	SegmentTree() {}
}T;

bool fail;
void solve(int l, int r, int vl, int vr) {
	assert(r - l + 1 == vr - vl + 1);
	if(SZ(vec[r + 1])) {
		T.range_add(1, 1, n, vec[r + 1].back(), r, -1);
	}
	pii tmp = T.query_min(1, 1, n, l, r);
	if(tmp.fi != 0) { fail = 1; return; }
	ans[tmp.se] = vr;
	if(SZ(vec[r + 1])) {
		if(tmp.se == vec[r + 1].back()) {
			vec[r + 1].pop_back();
		} else {
			T.range_add(1, 1, n, vec[r + 1].back(), r, 1);
		}
	}
	
	if(tmp.se > l) {
		solve(l, tmp.se - 1, vl, vl + tmp.se - l - 1);
		if(fail) return;
	}
	if(tmp.se < r) {
		solve(tmp.se + 1, r, vl + tmp.se - l, vr - 1);
		if(fail) return;
	}
}
void solve_case() {
	cin >> n;
	T.build(1, 1, n);
	for(int i = 2; i <= n + 1; ++i) {
		vector<int>().swap(vec[i]);
	}
	for(int i = 1; i <= n; ++i) {
		cin >> f[i];
		if(f[i] == -1) continue;
		T.range_add(1, 1, n, i, f[i] - 1, 1);
		vec[f[i]].pb(i);
	}
	for(int i = 2; i <= n + 1; ++i) {
		reverse(vec[i].begin(), vec[i].end());
	}
	fail = 0;
	solve(1, n, 1, n);
	if(fail) {
		cout << -1 << endl;
		return;
	}
	for(int i = 1; i <= n; ++i) {
		cout << ans[i] << " \n"[i == n];
	}
}
int main() {
	int T; cin >> T; while(T--) {
		solve_case();
	}
	return 0;
}
```



---

## 作者：FL_sleake (赞：0)

### 前置

第一次独立做出来 `*2100` 的题，肯定是 cf 评分评高了。

### 题意简述

有一个排列 $p$，定义 $nxt_i$ 为 $p_i$ 右侧第一个大于 $p_i$ 的位置。若不存在这样的位置则 $nxt_i=n+1$。

现在排列 $p$ 和部分 $nxt_i$ 丢失了。你需要构造出一个排列 $p$，满足给出的 $nxt_i$ 关系。$nxt_i=-1$ 表示 $nxt_i$ 丢失（即你可以忽略这个 $nxt_i$ 关系）。

若无解，输出 `-1`。若有多组解，输出任意一组即可。

### 解题思路

先来考虑什么时候无解。对于一个 $i$，如果存在一个位置 $j$，满足 $i<j<nxt_i$ 且 $nxt_j>nxt_i$，则无解。理解一下，就是说给出的 $nxt_i$ 会推出大小关系冲突。

再来考虑构造一个合法的解。我们可以将 $nxt_i=-1$ 的 $nxt_i$ 全部替换成 $i+1$。这样的替换一定不会导致有解的序列变成无解。然后我们开一个堆存储当前还未选择的数有哪些，并确立 $i$ 和 $nxt_i$ 的大小关系，从堆中每次选最大的数填就可以了。可以看代码理解一下。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,nxt[500010],st[50][500010],ans[500010];
multiset<int> s;
vector<int> G[500010];
void init(){
	s.clear();
	for(int i=1;i<=n;i++) G[i].clear();
	for(int i=1;i<=n;i++) s.insert(i);
	for(int i=1;i<=n;i++) st[0][i]=nxt[i];
	for(int i=1;i<=__lg(n);i++){
		for(int j=1;j+(1<<i)-1<=n;j++) st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
	}
}
int query(int l,int r){
	int len=__lg(r-l+1);
	return max(st[len][l],st[len][r-(1<<len)+1]);
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>nxt[i];
	for(int i=1;i<=n;i++) if(nxt[i]==-1) nxt[i]=i+1;
	init();
	for(int i=1;i<=n;i++){
		if(nxt[i]==i+1) continue;
		if(query(i+1,nxt[i]-1)>nxt[i]){
			cout<<-1<<endl;
			return;
		}
	}
    //st表判断无解情况
	for(int i=1;i<=n;i++) G[nxt[i]].push_back(i);
    //确立大小关系
	for(int i=1;i<=n;i++){
		if(nxt[i]==n+1){
			ans[i]=*s.rbegin();
			s.erase(s.find(*s.rbegin()));
		}
	}
    //初始化 nxt_i=n+1 的位置
	for(int i=n;i>=1;i--){
		for(int v:G[i]){
			ans[v]=*s.rbegin();
			s.erase(s.find(*s.rbegin()));	
		}
        //每次找最大的未使用的数填入即可
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<endl;
	return;
}
signed main(){
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

