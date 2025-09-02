# [CERC2015] Greenhouse Growth

## 题目描述

你正在从计算机科学转向农业，你的新工作涉及在地下温室中种植向日葵。温室中有 n 株向日葵，按从左到右的顺序排列并编号为 1 到 n。两盏灯为向日葵提供生长所需的光和热：灯 A 位于左端，而灯 B 位于右端。

每天，只有一盏灯亮着，导致所有向日葵都朝向光源，并且其中一些会生长。向日葵只有在其正前方（朝向光源）的向日葵比它高时才会生长。生长是连续的，速率为每天正好 1 厘米。注意，当一株向日葵开始生长时，它可能会立即导致其正后方的向日葵开始生长。

你被给定了向日葵的初始高度和接下来 m 天的灯光计划，找出所有向日葵的最终高度。

## 说明/提示

Central Europe Regional Contest 2015 Problem G。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 5 
4 3 5 3 6 6 
BABAA
```

### 输出

```
5 5 6 6 6 6```

# 题解

## 作者：xie_lzh (赞：2)

题面十分简洁所以不复述题面。

我们发现，连续的一段高度相同的向日葵一定会一起增长，所以每次操作只会使相邻不同的向日葵变为相同的，而不会使连续相同的向日葵变为不同的。

基于上面这个性质，我们可以想到一种基于合并次数的做法。

我们考虑在现有情况下，相邻的两个连续段什么时候会合并。我们发现这个可以通过当前情况下两种方向照灯的长高情况直接二分出来。但是这个不一定是他们真正合并的时间，因为可能受到其他段长高后的影响。但是我们发现，这只会让合并时间提前，所以当前我们找到的合并时间最小的位置是不受影响的。

故我们可以每次找到合并时间最小的位置合并，记录下合并后的高度和时间。然后计算合并后与相邻段的合并时间。

容易想到将所有可能的合并丢进堆里，每次取出最小的。

但是这样又会有一个问题，如果相邻的两段的当前时间不一样，我该如何判断是否可以生长。

看起来不太好做，但是我们发现，一个位置的生长情况只会在合并时发生改变，而我们选择的是合并时间最小的位置，所以其他位置的生长情况不会发生改变。

所以我们可以直接求得其他位置在当前时间的高度，从而得知合并后的生长情况，然后我们可以直接重新计算相邻段之间的合并时间。

注意一下若取出的点的状态不是最新状态则不能更新。

如果无论怎样都不会出现合并就可以直接计算答案了。

复杂度 $\Theta(n\log n)$。

实现细节比较多。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
#define pii pair<int,int>
int sum[N][2];
int n,m,a[N],fa[N],L[N],R[N],tim[N],val[N],ans[N],op[N][2],siz[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
char c[N];
int getv(int x,int ntim)
{
	x=find(x);
	// int lx=(L[x]==1?0:find(L[x]-1));
	// int rx=(R[x]==n?0:find(R[x]+1));
	// op[0]={lx&&val[x]<val[lx]||(val[x]==val[lx]&&tim[x]>tim[lx])};
	// op[1]={rx&&val[x]<val[rx]||(val[x]==val[rx]&&tim[x]>tim[rx])};
	return val[x]+(op[x][0]?sum[ntim][0]-sum[tim[x]][0]:0)+(op[x][1]?sum[ntim][1]-sum[tim[x]][1]:0);
}
int sv(int x,int y)
{
	if(!x||!y) return m+5;
	x=find(x); y=find(y);
	int l=max(tim[x],tim[y]),r=m,mid;
	int xv=getv(x,l),yv=getv(y,l);
	if(xv==yv) return l;
	if(xv>yv) swap(x,y);
	// if(xv>yv||xv==yv&&tim[x]>tim[y]) swap(x,y);
	// if(val[x]>val[y]||(val[x]==val[y]&&tim[x]<tim[y])) swap(x,y);
	// if(a[x]>a[y]) swap(x,y);
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(getv(x,mid)>=getv(y,mid)) r=mid-1;
		else l=mid+1;
	}
	int pans=r+1;
	return r+1;
}
void merge(int x,int y)
{
	x=find(x); y=find(y);
	if(x==y) return ;
	fa[y]=x; siz[x]+=siz[y];
	// if(L[x]>L[y]) op[x][0]=op[y][0];
	// if(R[x]<R[y]) op[x][1]=op[y][1];
	R[x]=max(R[x],R[y]); L[x]=min(L[x],L[y]);
	op[x][0]=(L[x]!=1&&getv(find(L[x]-1),tim[x])>val[x]);
	op[x][1]=(R[x]!=n&&getv(find(R[x]+1),tim[x])>val[x]);
	// op[x][0]|=op[y][0]; op[x][1]|=op[y][1];
}
struct node
{
	int x,y,szx,szy,timx,timy,nxt;
};
bool operator <(node a,node b)
{
	return a.nxt>b.nxt;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],val[i]=a[i];
	cin>>c+1;
	for(int i=1;i<=m;i++)
	{
		int p=(c[i]=='B');
		sum[i][p]=sum[i-1][p]+1;
		sum[i][p^1]=sum[i-1][p^1];
	}
	fill(siz+1,siz+1+n,1);
	iota(fa+1,fa+1+n,1);
	for(int i=1;i<=n;i++) L[i]=R[i]=i;
	for(int i=1;i<n;i++)
		if(a[i]==a[i+1]) merge(i,i+1);
	priority_queue<node> q;
	int ntim=0;
	for(int i=1;i<=n;i++)
		if(find(i)==i)
		{
			if(R[i]!=n) op[i][1]=(a[R[i]+1]>a[i]);
			if(L[i]!=1) op[i][0]=(a[L[i]-1]>a[i]);
		}
	for(int i=1;i<=n;i++)
		if(find(i)==i)
		{
			if(R[i]!=n) q.push(node{i,find(R[i]+1),siz[i],siz[find(R[i]+1)],0,0,sv(i,find(R[i]+1))});
			if(L[i]!=1) q.push(node{find(L[i]-1),i,siz[find(L[i]-1)],siz[i],0,0,sv(find(L[i]-1),i)});
		}
	while(!q.empty())
	{
		node u=q.top(); q.pop();
		int x=u.x,y=u.y,timx=u.timx,timy=u.timy,nxt=u.nxt,szx=u.szx,szy=u.szy;
		if(nxt>m) break;
		if(find(x)!=x||find(y)!=y) continue;
		// if(timx!=tim[x]||timy!=tim[y]) continue;
		if(siz[x]!=szx||siz[y]!=szy) continue;
		// if(a[x]<a[y])  swap(x,y);
		val[x]=getv(x,nxt); tim[x]=nxt;
		merge(x,y);
		int lx=(L[x]==1?0:find(L[x]-1));
		int rx=(R[x]==n?0:find(R[x]+1));
		if(lx) q.push({lx,x,siz[lx],siz[x],tim[lx],tim[x],sv(lx,x)});
		if(rx) q.push({rx,x,siz[rx],siz[x],tim[rx],tim[x],sv(x,rx)});
	}
	for(int i=1;i<=n;i++)
		if(find(i)==i) ans[i]=getv(i,m);
	for(int i=1;i<=n;i++) cout<<ans[find(i)]<<' '; cout<<'\n';
}
```

---

## 作者：Daniel_yuan (赞：2)

提供一个 $O(n\log n)$ 的做法。

可以发现向日葵的长高一定是一段一段的，这启示我们使用差分。

考虑把原数组 $a$ 差分成数组 $c$，即 $c_x=c_x-c_{x-1}$ 且 $c$ 下标的范围是 $2\sim n$。显然差分数组为 $0$ 的地方可以合并，因为前后相等的时候，生长都是同时的。所以下面讨论的是 $c$ 数组中没有 $0$ 的情况。

对于操作 A，所有 $c$ 数组中**当前位置**小于 $0$ 的地方 $a$ 数组都会加一（即一个数小于前面的数，$a$ 数组就会加一），考虑这对差分数组 $c$ 的影响。如果 $c_x>0$，那么 $a_x$ 不会改变，而如果 $c_{x-1}<0$，那么 $a_{x-1}$ 会加一，所以 $c_x$ 要减一。如果 $c_x<0$，那么 $a_x$ 会加一，而如果 $c_{x-1}>0$，那么 $a_{x-1}$ 不会改变，所以 $c_x$ 要加一。

对于操作 B，所以 $c$ 数组中**后一个位置**大于 $0$ 的地方 $a$ 数组都会加一（即一个数小于后面的数，$a$ 数组就会加一），同样的，考虑其对差分数组 $c$ 的影响。如果 $c_{x+1}>0$，那么 $a_{x}$ 会加一，而如果 $c_{x+2}<0$，那么 $a_{x+1}$ 不会变，所以 $c_{x+1}$ 会减一。如果 $c_{x+1} <0$，那么 $a_{x+1}$ 不会变，而如果 $c_{x+2}>0$，那么 $a_{x+1}$ 会加一，所以 $c_{x+1}$ 会加一。

从上面的推导可以发现，所有 $c$ 会发生改变的地方都是前面或者后面的 $c$ 的正负性和当前不同，所以考虑把所有极长的符号相同的 $c$ 看成一段。 

那么对于操作 A，就是把所有正数段的最左边的数减一，所有负数段的最左边的数加一，特别的，如果第一段是正数段，那么它不需要减一。

同样的，对于操作 B，就是把所有正数段的最右边的数减一，所有负数段的最右边的数加一，特别的，如果最后一段是负数段，那么它不需要加一。

如果某个 $c_x$ 变成了 $0$，那么就把它从这个段里面删掉，如果这个段此时被删空了，那么它就会造成其前后的段合并，这时候直接合并即可。

直接用可删堆分别维护大小大于等于 $2$ 和大小等于 $1$ 的段，对于每次操作，直接打一个全局标记，然后如果有 $c_x=0$ 的 $x$ 就进行删除处理即可。

一个位置的 $c$ 只可能等于 $0$ 一次，所以它只会进堆一次，出堆一次，造成前后合并一次，故总复杂度 $O(n\log n)$。

得到最后的差分数组 $c$ 后，考虑还原数组 $a$。不难发现最大值是不会超过原序列的最大值的，找到原序列的最大值及其位置之后就可以直接还原了。

代码如下：

```cpp
#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define RI register int
typedef long long LL;

#define FILEIO(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

using namespace std;

int const MAXN = 3e5 + 5;
int a[MAXN], b[MAXN];
int cf[MAXN];
int nxt[MAXN], pre[MAXN];
struct Node {
  int val, id;
  bool operator < (const Node &A) const { return val ^ A.val ? val > A.val : id > A.id; }
  bool operator == (const Node &A) const { return val == A.val && id == A.id; }
};
struct DeleteHeap {
  priority_queue <Node> I, O;
  inline void Flush() {
    while (!O.empty() && I.top() == O.top())
      I.pop(), O.pop(); }
  inline void insert(Node x) { /*cout << this << " insert " << x.id << " " << x.val << endl;*/ I.push(x); }
  inline void erase (Node x) { /*cout << this << " erase  " << x.id << " " << x.val << endl;*/ O.push(x); }
  inline bool empty() { Flush(); return I.empty(); }
  inline Node top()   { Flush(); return I.top();   }
} Head, Tail, HT; // 前两个维护大小大于等于 2 的段，最后一个维护大小为 1 的段。
int tagh, tagt, taght; // 全局标记
int size[MAXN], L[MAXN], R[MAXN]; // 段大小，左右端点
int ans[MAXN];

// 找每个段的左右端点
int FindL(int x) { return x == L[x] ? x : L[x] = FindL(L[x]); }
int FindR(int x) { return x == R[x] ? x : R[x] = FindR(R[x]); }

void Init(int n) { // 求得差分数组，以及初始化。
  for (RI i = 2; i <= n; ++i)
    cf[i] = a[i] - a[i - 1], b[i] = (cf[i] > 0 ? 1 : -1);
  for (RI i = 1; i <= n; ++i)
    nxt[i] = i + 1, pre[i + 1] = i;
  for (RI i = 2; i <= n; ++i)
    if (cf[i] == 0) {
      nxt[pre[i]] = nxt[i];
      pre[nxt[i]] = pre[i];
    }
  int las = nxt[1], cnt = 0;
  for (RI i = nxt[1]; i != n + 1; i = nxt[i], ++cnt)
    if (b[i] != b[las]) {
      for (RI j = las; j != i; j = nxt[j])
        L[j] = las, R[j] = pre[i];
      size[las] = cnt;
      if (size[las] >= 2) {
        Head.insert((Node){b[las] * cf[las], las});
        Tail.insert((Node){b[pre[i]] * cf[pre[i]], pre[i]});
      }
      else
        HT.insert((Node){b[las] * cf[las], las});
      las = i, cnt = 0;
    }
  for (RI j = las; j; j = nxt[j])
    L[j] = las, R[j] = pre[n + 1];
  size[las] = cnt;
  if (size[las] >= 2) {
    Head.insert((Node){b[las] * cf[las], las});
    Tail.insert((Node){b[pre[n + 1]] * cf[pre[n + 1]], pre[n + 1]});
  }
  else
    HT.insert((Node){b[las] * cf[las], las});
}

inline void Del(int x) { // 删除一个段
  int sz = size[FindL(x)];
  if (sz >= 2) {
    int l = FindL(x), r = FindR(x);
    Head.erase((Node){b[l] * cf[l], l});
    Tail.erase((Node){b[r] * cf[r], r});
    cf[l] -= b[l] * tagh;
    cf[r] -= b[r] * tagt;
  }
  else {
    int l = FindL(x);
    HT.erase((Node){b[l] * cf[l], l});
    cf[l] -= b[l] * taght;
  }
}
inline void Ins(int x) { // 加入一个段
  int sz = size[FindL(x)];
  if (sz >= 2) {
    int l = FindL(x), r = FindR(x);
    cf[l] += b[l] * tagh;
    cf[r] += b[r] * tagt;
    Head.insert((Node){b[l] * cf[l], l});
    Tail.insert((Node){b[r] * cf[r], r});
  }
  else {
    int l = FindL(x);
    cf[l] += b[l] * taght;
    HT.insert((Node){b[l] * cf[l], l});
  }
}
void Merge(int lc, int rc) { // 合并两个段
  int szr = size[FindL(rc)];
  int r = FindR(lc);
  int l = FindL(rc);
  R[r] = FindR(rc);
  L[l] = FindL(lc);
  size[FindL(lc)] += szr;
  Ins(lc);
}

int main() {

#ifdef LOCAL
  FILEIO("a");
#endif

  int n, m; scanf("%d %d", &n, &m);
  for (RI i = 1; i <= n; ++i) scanf("%d", a + i);
  Init(n);
  while (m--) {
    char ch = getchar();
    while (ch != 'A' && ch != 'B') ch = getchar();
    if (ch == 'A') {
      ++tagh, ++taght;
      if (b[nxt[1]] == 1) { // 上文说的特判
        Del(nxt[1]);
        cf[FindL(nxt[1])] += b[FindL(nxt[1])];
        Ins(nxt[1]);
      }
    }
    else {
      ++tagt, ++taght;
      if (b[pre[n + 1]] == -1) { // 上文说的特判
        Del(pre[n + 1]);
        cf[FindR(pre[n + 1])] += b[FindR(pre[n + 1])];
        Ins(pre[n + 1]);
      }
    }
    while (666) { // 删除 c[x]=0 的位置
      int flag = 1;
      while (!HT.empty() && HT.top().val <= taght) {
        flag = 0;
        Node t = HT.top();
        Del(t.id);
        int P = pre[t.id], N = nxt[t.id];
        nxt[P] = N, pre[N] = P;
        if (P != 1 && N != n + 1) {
          Del(P), Del(N);
          Merge(P, N);
        }
      }
      while (!Head.empty() && Head.top().val <= tagh) {
        flag = 0;
        Node t = Head.top();// Head.erase(t);
        Del(t.id);
        int l = FindL(t.id);
        L[l] = L[nxt[l]] = nxt[l];
        size[nxt[l]] = size[l] - 1;
        nxt[pre[l]] = nxt[l];
        pre[nxt[l]] = pre[l];
        Ins(t.id);
      }
      while (!Tail.empty() && Tail.top().val <= tagt) {
        flag = 0;
        Node t = Tail.top();// Tail.erase(t);
        Del(t.id);
        int l = FindL(t.id), r = FindR(t.id);
        R[r] = R[pre[r]] = pre[r];
        size[l] = size[l] - 1;
        nxt[pre[r]] = nxt[r];
        pre[nxt[r]] = pre[r];
        Ins(t.id);
      }
      if (flag) break;
    }
  }
  while (!Head.empty()) Del(Head.top().id);
  while (!Tail.empty()) Del(Tail.top().id);
  while (!HT.empty()) Del(HT.top().id);
  int mx = -1, pos = -1;
  for (RI i = 1; i <= n; ++i) // 还原 a 数组
    if (a[i] > mx)
      mx = a[i], pos = i;
  ans[pos] = a[pos];
  for (RI i = pos + 1; i <= n; ++i)
    ans[i] = ans[i - 1] + cf[i];
  for (RI i = pos - 1; i >= 1; --i)
    ans[i] = ans[i + 1] - cf[i + 1];
  for (RI i = 1; i <= n; ++i)
    printf("%d ", ans[i]);

  cerr << (double)(clock()) / CLOCKS_PER_SEC << " s " << endl;

  return 0;
}

// created by Daniel yuan
/*
     ________
    /        \
   / /      \ \
  / /        \ \
  \            /
   \  ______  /
    \________/
*/
```





---

## 作者：yukimianyan (赞：1)

## 题目描述

你在潇杻国一座城市的街道上，这条街道是一个很长的直线。

在这条街道上，从左到右依次排布着 $n$ 棵树。开始时，第 $i$ 棵树的高度为 $h_i$。

因为人在挫折中成长，所以树在风暴中成长。有 $m$ 场风暴依次降临，每场风暴会**从左向右**或**从右向左依次**席卷这条街道上的每一颗树。当第 $i$ 棵树被风暴席卷时，如果前一棵被风暴席卷的树比第 $i$ 棵树高，那么第 $i$ 棵树会长高 $1$ 个单位的高度。最开始被席卷的树的高度不会有任何变化。

每场风暴会席卷每棵树**恰好**一次，每棵树是否长高取决于其前一棵树被**本场**风暴席卷后的高度。

由于潇杻国国王柬鋀只会做计数题，所以你需要帮他求出 $m$ 场风暴结束后每一棵树的高度。

从左向右的风暴叫作 A 风，从右向左的风暴叫作 B 风。

对于所有测试数据，$2 \leq n,m \leq  3\times 10^5,1\leq h_i\leq 10^9$。

特殊性质 A：$h_i\neq h_{i-1}$ 的 $i$ 只有 $100$ 个。

特殊性质 B：风暴全是 A 风。

## 题解

特殊性质 A：连续的高度相同的树会被同时拔高或者不拔高。所以将连续段并起来就做完了。

特殊性质 B：假设 $i-1$ 这个位置最终变成 $a_{i-1}$，现在输入 $a_i$，有几种情况：

1. $a_{i-1}\leq a_i$，风暴无法撼动这棵树。
2. $a_{i-1}\leq a_i+m$，这时候这棵树只能长高到 $a_{i-1}$，这一定做得到。
3. $a_{i-1}>a_i+m$，这棵树只能长高到 $a_i+m$。

以上三个讨论覆盖所有情况，因此可以 $O(1)$ 计算 $i$ 位置最终的高度，然后 $O(n)$ 计算整个序列的答案。

---

正解的第一步肯定是将连续段并起来，并观察到连续段只会被并 $O(n)$ 次所以很可能要暴力维护连续段。发现连续段之间的差在归零之前每次要么 $-1$ 要么不变且只取决于风向（以及旁边的连续段不被合并）。

仔细刻画连续段之间的差到底长啥样。记 $ca(i)$ 表示吹 A 风时 $i$ 是否会升高，$cb(i)$ 表示吹 B 风时 $i$ 是否会升高。现在 $i, j$ 两个连续段是相邻的，记 $a=[ca(i)\neq ca(j)], b=[cb(i)\neq cb(j)]$，则从当前时刻出发，经过 $ta$ 个 A 风和 $tb$ 个 B 风后 $i, j$ 之间的差降低 $a\cdot ta+b\cdot tb$，这个在 $a, b$ 改变之前都适用，而且这样可以轻易计算出这个连续段在没有意外的时候什么时候归零（记为 $tim$，可能需要处理出某时刻之前有多少个 A/B 风以及第 $i$ 个 A/B 风在什么时刻上）。每次合并连续段的时候，则将旁边 $O(1)$ 个连续段的差先结算再修改它们的 $a, b$。

由此导出一个恐怖的做法：维护每对相邻连续段的 $a, b, tim, lst, hei$ 其中 $hei$ 是考虑了 $[1, lst]$ 中的操作后的差，$a, b, tim$ 同上。计算出 $tim$ 之后，对每个操作开一个桶，将这对连续段放入第 $tim$ 个桶，当从前往后扫到这个操作时就可以将这两个连续段合并起来。事实上一直没有说的是外面需要维护一个双向链表和并查集，例如双向链表有 $L, R$ 表示前驱后继，然后相邻连续段的信息存在后一个连续段上，当前在 $t$ 操作尝试合并 $i, L[i]$，则你可能需要先结算 $R[i]$ 至 $t$ 时刻（这里是因为需要正确维护 $R[i]$ 的 $hei$），然后删去 $i$，将 $i$ 往 $L[i]$ 上合并，然后分别结算并更新 $L[L[i]], L[i], R[i], R[R[i]]$ 对应的一大坨东西。总复杂度是 $O(n+m)$，注意并查集先 merge 再 find 复杂度仍是线性，注意仔细实现小心同一个点被删两次导致桶大小超级加倍或者迭代器原地失效等逆天错误。

## code


```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
using LL = long long;
template <int N>
struct dsu {
  int fa[N + 10], siz[N + 10];
  void init(int n) { for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1; }
  int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    //  if (siz[x] < siz[y]) swap(x, y);
    siz[x] += siz[y], fa[y] = x;
    return true;
  }
};
int n, m, a[300010], L[300010], R[300010], op[300010], oid[2][300010], b[300010];
int ops[2][300010], cnt[2];
dsu<300010> dsy;
int ca(int i) { return L[i] >= 1 && a[i] < 0; }
int cb(int i) { return R[i] <= n && a[R[i]] > 0; }
vector<int> vec[300010];
int arga[300010], argb[300010], lst[300010], hei[300010], tim[300010];
int vis[300010];
void update(int i, int t) {
  if (L[i] < 1 || i > n) return ;
  assert(lst[i] <= t);
  // i & L[i]
  // (lst, t)
  if (lst[i] < t) {
    hei[i] -= arga[i] * (oid[0][t] - oid[0][max(lst[i], 0)]);
    hei[i] -= argb[i] * (oid[1][t] - oid[1][max(lst[i], 0)]);
  }
  // without t
  arga[i] = ca(i) != ca(L[i]);
  argb[i] = cb(i) != cb(L[i]);
  lst[i] = t;
  if (arga[i] && argb[i]) tim[i] = t + hei[i];
  else if (arga[i]) tim[i] = ops[0][min(m + 1, oid[0][t] + hei[i])];
  else if (argb[i]) tim[i] = ops[1][min(m + 1, oid[1][t] + hei[i])];
  else tim[i] = m + 1;
  tim[i] = min(tim[i], m + 1);
  if (tim[i] != t && tim[i] <= m) vec[tim[i]].push_back(i);
  debug("update %d -> tim = %d\n", i, tim[i]);
}
int main() {
#ifndef LOCAL
#ifndef NF
  freopen("growing.in", "r", stdin);
  freopen("growing.out", "w", stdout);
#endif
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  dsy.init(n);
  memset(ops, 0x3f, sizeof ops);
  for (int i = 1; i <= m; i++) {
    char _op;
    cin >> _op;
    op[i] = _op != 'A';
    oid[op[i]][i] = oid[op[i]][i - 1] + 1;
    oid[!op[i]][i] = oid[!op[i]][i - 1];
    ops[op[i]][++cnt[op[i]]] = i;
  }
  for (int i = n; i >= 1; i--) a[i] -= a[i - 1], hei[i] = abs(a[i]), debug("hei[%d] = %d\n", i, hei[i]);
  for (int i = 1; i <= n; i++) L[i] = i - 1, R[i] = i + 1;
  L[0] = 0, R[0] = 1, L[n + 1] = n, R[n + 1] = n + 1;
  for (int i = R[R[0]]; i <= n; i = R[i]) if (!hei[i]) dsy.merge(L[i], i), L[R[i]] = L[i], R[L[i]] = R[i], debug("rm %d\n", i);
  for (int i = R[R[0]]; i <= n; i = R[i]) update(i, 0);
#ifdef LOCAL
  debug("after t = %d\n", 0);
  for (int i = R[R[0]]; i <= n; i = R[i]) debug("st = %d, args = {%d, %d}, lst = %d, hei = %d, tim = %d\n", i, arga[i], argb[i], lst[i], hei[i], tim[i]);
#endif
  for (int t = 1; t <= m; t++) {
    if (R[1] <= n && a[R[1]] > 0 && op[t]) hei[1] += 1;
    vector<int> sb;
    for (int i : vec[t]) if (tim[i] == t)
    sb.push_back(i); for (int i : sb) 
     if (vis[i] < t) {
      update(R[i], t);
//    if (R[i] <= n && a[R[i]] > 0 && a[i] < 0) hei[R[i]] -= 1, debug("i = %d\n", i);
      dsy.merge(L[i], i), L[R[i]] = L[i], R[L[i]] = R[i];
      update(L[i], t), update(L[L[i]], t), update(R[i], t), update(R[R[i]], t);
      vis[i] = t;
      tim[i] = m + 1;
    }
#ifdef LOCAL
    debug("after t = %d\n", t);
    for (int i = R[R[0]]; i <= n; i = R[i]) debug("st = %d, args = {%d, %d}, lst = %d, hei = %d, tim = %d\n", i, arga[i], argb[i], lst[i], hei[i], tim[i]);
#endif
  }
  assert(R[0] == 1);
  b[1] = hei[1];
  debug("b[1] = %d\n", b[1]);
  for (int i = R[1]; i <= n; i = R[i]) update(i, m), b[i] = b[L[i]] + (a[i] < 0 ? -hei[i] : hei[i]);
#ifdef LOCAL
    debug("after t = %d\n", m + 1);
    for (int i = R[R[0]]; i <= n; i = R[i]) debug("st = %d, args = {%d, %d}, lst = %d, hei = %d, tim = %d\n", i, arga[i], argb[i], lst[i], hei[i], tim[i]);
#endif
  for (int i = 1; i <= n; i++) debug("dsy.find(%d) = %d\n", i, dsy.find(i));
  for (int i = 1; i <= n; i++) cout << b[dsy.find(i)] << " \n"[i == n];
  return 0;
}


```

---

## 作者：Lyz09 (赞：0)

模拟赛搬了这题，来水个题解（

模拟赛中的题面与原题面不同，具体可以见 [yukimianyan 的题解](https://www.luogu.com.cn/article/6f50qu2q)。因此下文中树为题面中的向日葵，风暴来袭为题面中的开灯操作。

------

首先容易发现，如果相邻的两棵树在某一时刻高度相同，那么它们之后的高度会一直相同。因此我们可以把这些树作为若干个连续段考虑。因为相邻两个连续段会在某个时刻合并，因此我们需要也只要关注相邻两个连续段会在什么时候合并。

考虑一场风暴来袭时一个连续段的树木会不会生长，也就是对于每一个连续段，分别求出其会不会在从左到右和从右到左的风暴中会不会生长。显然其等价于其左边的连续段和其右边的连续段的高度是否大于它的高度，其可以用一个式子快速表示。

根据这个我们得出了一个连续段树木的高度变化规律，同时也可以得出相邻两段高度差的缩小规律，同时对于所有可能的情况分析可以发现相邻两段高度差一定是单调非增的。因此我们可以知道这一段高度差会在什么时候变为零，相邻的两端合并成一段。

具体来说，令两段在**从左到右**的风暴中高度的变化情况**是否不相同**记为 $a$，两段在**从右到左**的风暴中高度的变化情况**是否不相同**记为 $b$，记录高度差的时刻为 $t$，记录时高度差为 $h$，第 $i$ 个时刻及以前从左到右的风暴有 $l_i$ 场，从右到左的风暴有 $r_i$ 场，则第 $x$ 个时刻其高度差为 $\max(0,h-a(l_x-l_i)-b(r_x-r_i))$。我们可以根据这条式子来快速计算出相邻两段高度变为相等的时刻，分别记录 $a=1,b=0$，$a=0,b=1$，$a=1,b=1$ 三类情况即可，显然单次记录与查询可以做到 $O(1)$。

当两段合并时，只会修改这两段的信息以及更新这两段与其相邻段的高度差信息，单次修改的信息量是 $O(1)$ 的。因此总时间复杂度是 $O(n+m)$ 的。

Stupid Code：

```cpp
#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define N 2000010 
#define int long long
int n,m,h[N];
int cnt,tot,now,ha[N],hb[N];
struct node
{
	int l,r,time;
	int pre,nxt,del;
	int t,h,da,db;
}a[N];
struct node2
{
	int p1,p2,t1,t2;
};
vector<node2> g[N],ga[N],gb[N];
string s;
int calc(int pos)
{
	return a[pos].h+(ha[now]-ha[a[pos].t])*a[pos].da+(hb[now]-hb[a[pos].t])*a[pos].db;
}
void calcmerge(int p1)
{
	int p2=a[p1].nxt;
	int ch=calc(p1)-calc(p2);
	if(ch<0)
	 ch=-ch;
	if(ch==0)
	{
		g[now].push_back((node2){p1,p2,a[p1].time,a[p2].time});
		return;
	}
	if(a[p1].da!=a[p2].da&&a[p1].db!=a[p2].db)
	{
		if(now+ch<=m)
		 g[now+ch].push_back((node2){p1,p2,a[p1].time,a[p2].time});
		return;
	}
	if(a[p1].da!=a[p2].da)
	{
		if(ha[now]+ch<=m)
		 ga[ha[now]+ch].push_back((node2){p1,p2,a[p1].time,a[p2].time});
	}
	if(a[p1].db!=a[p2].db)
	{
		if(hb[now]+ch<=m)
		 gb[hb[now]+ch].push_back((node2){p1,p2,a[p1].time,a[p2].time});
	}
}
void upd(int pos)
{
	a[pos].time=++tot;
	a[pos].da=a[pos].db=0;
	if(a[pos].pre&&calc(a[pos].pre)>=calc(pos))
	 a[pos].da=1;
	if(a[pos].nxt&&calc(a[pos].nxt)>=calc(pos))
	 a[pos].db=1;
	if(a[pos].nxt)
	 calcmerge(pos);
	if(a[pos].pre)
	 calcmerge(a[pos].pre);
}
void mergeblk(int p1,int p2)
{
	int p3=++cnt;
	a[p3].t=now;
	a[p3].h=calc(p1);
	if(a[p1].nxt)
	 a[a[p1].nxt].pre=0;
	if(a[p2].pre)
	 a[a[p2].pre].nxt=0;
	if(a[p1].pre)
	 a[a[p1].pre].nxt=p3;
	if(a[p2].nxt)
	 a[a[p2].nxt].pre=p3;
	a[p3].pre=a[p1].pre;
	a[p3].nxt=a[p2].nxt;
	a[p3].l=min(a[p1].l,a[p2].l);
	a[p3].r=max(a[p1].r,a[p2].r);
	a[p1].del=1;
	a[p2].del=1;
	upd(p3);
}
signed main()
{
//	freopen("growing.in","r",stdin);
//	freopen("growing.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	int las=1;
	for(int i=1;i<=n;i++)
	{
		cin>>h[i];
		if(h[i]!=h[i-1]&&i!=1)
		{
			cnt++;
			a[cnt]=(node){las,i-1,0,cnt-1,0,0,0,h[i-1],0,0};
			if(cnt>1)
			 a[cnt-1].nxt=cnt;
			las=i;
		}
	}
	cnt++;
	a[cnt]=(node){las,n,0,cnt-1,0,0,0,h[n],0,0};
	if(cnt>1)
	 a[cnt-1].nxt=cnt;
	for(int i=1;i<=cnt;i++)
	 upd(i);
	cin>>s;
	s=" "+s;
	for(int i=1;i<=m;i++)
	{
		now=i;
		ha[i]=ha[i-1];
		hb[i]=hb[i-1];
		if(s[i]=='A')
		 ha[i]++;
		else
		 hb[i]++;
		if(s[i]=='A')
		{
			for(node2 w:ga[ha[i]])
			if(a[w.p1].time==w.t1&&a[w.p2].time==w.t2&&!a[w.p1].del&&!a[w.p2].del)
			 mergeblk(w.p1,w.p2);
		}
		else
		{
			for(node2 w:gb[hb[i]])
			if(a[w.p1].time==w.t1&&a[w.p2].time==w.t2&&!a[w.p1].del&&!a[w.p2].del)
			 mergeblk(w.p1,w.p2);
		}
		for(int j=0;j<g[i].size();j++)
		{
			node2 w=g[i][j];
			if(a[w.p1].time==w.t1&&a[w.p2].time==w.t2&&!a[w.p1].del&&!a[w.p2].del)
			 mergeblk(w.p1,w.p2);
		}
	}
	for(int i=1;i<=cnt;i++)
	if(!a[i].del)
	{
		for(int j=a[i].l;j<=a[i].r;j++)
		 h[j]=calc(i);
	}
	for(int i=1;i<=n;i++)
	 cout<<h[i]<<" ";
	cout<<"\n";
}
```

---

