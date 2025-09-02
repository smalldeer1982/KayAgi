# [KTSC 2021] 路灯 / streetlight

## 题目背景

本题翻译自 [2021년도 국제정보올림피아드 대표학생 선발고사](https://www.ioikorea.or.kr/archives/ioitst/2021/) 2차 선발고사 [#4 가로등](https://assets.ioikorea.or.kr/ioitst/2021/2/streetlight/streetlight_statement.pdf)。

**请注意，你不需要也不应该实现 `main` 函数。具体实现方式见【实现细节】部分。**

**警告：滥用本题评测一次即可封号。**

## 题目描述

一条笔直的道路上竖立着 $N$ 盏路灯。第 $i$ 盏路灯的初始高度为 $A_i$（$1 \leq i \leq N$）。

现计划利用这些路灯架设电线。

若要在第 $i$ 盏路灯和第 $j$（$> i$）盏路灯之间架设电线，必须同时满足以下两个条件：

- $A_i = A_j$（两盏路灯的高度相同）。

- 对于所有 $i < k < j$，满足 $A_k < A_i$（两盏路灯之间的所有路灯高度均低于它们）。

部分路灯的高度会根据管理者的判断进行调整，调整后可能导致电线架设条件发生变化。

“将第 $x$ 盏路灯的高度修改为 $h$”的操作共会进行 $Q$ 次。每次修改后，需立即计算当前满足条件的电线架设路灯对数，并编写程序实现此功能。

### 实现细节

需实现以下函数：

```cpp
vector<long long int> count_cable(vector<int> A, vector< pair<int, int> > C)
```

- 该函数仅被调用一次。
- 参数 $A$ 的大小为 $N$，其元素表示路灯的初始高度。即 $A[i] = A_{i+1}$（$0 \leq i \leq N - 1$）。
- 参数 $C$ 是由 $Q$ 个有序对 $(x, h)$ 构成的数组，每个有序对表示一次“将第 $x$ 盏路灯的高度修改为 $h$”的操作。
- 该函数需返回一个长度为 $Q + 1$ 的整数数组，其中第一个元素为初始状态下可架设电线的路灯对数，后续元素为每次修改后的对数。

在提交的源代码中，任何位置均不得执行输入输出函数。


## 说明/提示

### 约束条件

- $2 \leq N \leq 100\,000$
- $1 \leq Q \leq 250\,000$
- 所有路灯高度均为 $1$ 至 $10^9$ 之间的整数。
- 在修改第 $x$ 盏路灯高度为 $h$ 的操作中，保证 $1 \leq x \leq N$ 且修改前该路灯高度不等于 $h$。

### 子任务

1. （$5$ 分）
   - $N \leq 50$
   - $Q \leq 100$
2. （$8$ 分）
   - $N \leq 10\,000$
   - $Q \leq 25\,000$
3. （$11$ 分）
   - 所有路灯高度不超过 $10$。
4. （$7$ 分）
   - 所有修改操作均降低路灯高度。
5. （$15$ 分）
   - 若某路灯高度曾被增加，则后续不会降低。
   - 若某路灯高度曾被降低，则后续不会增加。
6. （$12$ 分）
   - $Q \leq 8\,000$
7. （$16$ 分）
   - 高度被修改过的路灯总数不超过 $8\,000$ 盏。
8. （$21$ 分）
   - $N \leq 40\,000$
   - $Q \leq 100\,000$
9. （$55$ 分）
   - 无额外约束。

### 评分标准

各子任务的得分为该子任务所有测试数据得分的最小值。

### 示例

- 设 $A = [4, 2, 2, 2, 4, 6]$，$C = [(4, 6), (6, 4)]$。

  $C = [(4, 6), (6, 4)]$ 表示第一次操作将第 $4$ 盏路灯高度改为 $6$，第二次操作将第 $6$ 盏路灯高度改为 $4$。

  调用函数：

  ```cpp
  count_cable([4,2,2,2,4,6], [(4,6),(6,4)])
  ```

  下图展示了初始状态下 $6$ 盏路灯间可架设的 $3$ 条电线：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/nfkcf4e6.png)

  下图展示第一次修改后（第 $4$ 盏高度改为 $6$）可架设的 $2$ 条电线：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/hn3qemb5.png)

  下图展示第二次修改后（第 $6$ 盏高度改为 $4$）可架设的 $2$ 条电线：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/7sy1g16t.png)

  函数 `count_cable` 应返回 `[3, 2, 2]`。

  此示例满足除子任务 $4$ 外所有子任务的条件。


## 样例 #1

### 输入

```
6 2
4 2 2 2 4 6
4 6
6 4```

### 输出

```
[3, 2, 2]```

# 题解

## 作者：skkkh (赞：2)

KTSC怎么这么难？！！！

下文中将把一个可行的连接方案 $l,r$ 记作特殊区间 $[l,r]$。一个显然的结论是，任意两个特殊区间不可能相交（拥有共同端点不算相交），因为此时端点值较大的区间的两个端点之一必然被值较小的区间包含，从而阻断那个区间。因此，如果将特征区间的包含关系视作父子关系，那么所有特征区间将形成森林的结构。

当产生修改时，若修改值比当前值更大，则会删去从包含当前点最深的区间开始的一段树上祖先后代链，然后加入 $O(1)$ 个点并连上其对应的边。但若修改值比当前值小，则变化不好刻画。于是考虑对修改进行分治，令所有修改的位置初始为 $0$，每次向两侧递归时就将另一侧的修改加入并计算影响，就可以以 $O(\log Q)$ 的代价将修改全部转化为只增不减。

此时直接对序列再进行分治，用线段树维护就可以做到 $O(N \log N \log^2 Q)$，或者用 LCT 等数据结构直接维护树的形态做到 polylog，但~~実装がかなり大変です~~,并未完全发掘本题的性质。

我们发现修改的影响形式很特殊，一个修改只会在树上产生两处突变点，并新增 $O(1)$ 个点。如果对这些突变点建出虚树，那么删去虚树中的点后产生的每一个联通块都是一个等价类，可以将一个等价类缩成一个点。如果一颗树里没有突变点，就意味着后续加入的修改不会影响这颗树给答案的贡献，直接计算其贡献即可。这样分治到 $[l,r]$ 内的修改时，森林中便只有 $O(r-l+1)$ 个点，当往两侧递归时，直接加入另一侧的修改并维护森林，复杂度降到 $O(N \log N \log Q)$。

实现时可以不用显式地记录森林的结构，因为将特殊区间按 $l$ 排序后就是该森林的一个 dfs 序，可以通过从左往右扫描线做到遍历森林，且能更便捷地支持加点删点。

代码写的比较依托，不懂的可以看[这个](https://www.luogu.me/article/wmnywsvp)。

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace streetlights{
	const int N=3e5+5;
	int n,m,a[N],pl[N],h[N];
	struct pii{int l,r,w,c;
		bool operator<(const pii &a)const{return l<a.l||l==a.l&&w>a.w;}
	}p[20][N],tp[N];
	struct itv{int l,r,w;
		bool operator<(const itv &a)const{return l<a.l;} 
	}q[20][N],tq[N];
	int mx[N],de=131072;int td[N];
	int tx[20][N],pt[N],ans[N],id[N];
	int ch[20][N];bool ex[N],nok[N];
	void chg(int x,int v){
		x+=de;mx[x]=v;
		while(x>1)x>>=1,mx[x]=max(mx[x<<1],mx[x<<1|1]);
	}
	int askl(int x,int v){x+=de-1;
		while(__builtin_popcount(x)>1&&mx[x]<v)x=(x-1)>>1;
		if(mx[x]<v)return 0;
		while(x<=de)x=x<<1|(mx[x<<1|1]>=v);
		return (mx[x]==v?x-de:0);
	}
	int askr(int x,int v){x+=de+1;
		while(__builtin_popcount(x+1)>1&&mx[x]<v)x=(x+1)>>1;
		if(mx[x]<v)return 0;
		while(x<=de)x=x<<1|(mx[x<<1]<v);
		return (mx[x]==v?x-de:0);
	}
	void work(int d,int &cp,int cq){
		memcpy(q[d+1],q[d],(cq+1)*sizeof(itv));
		int c=0,px=0,cx=0;
		for(int i=1;i<=cq;i++)
			if(ch[d][i]){q[d+1][i].w=0;
				px=askl(q[d+1][i].l,ch[d][i]);
				if(px){
					px=upper_bound(q[d+1],q[d+1]+cq+1,(itv){px,0,0})-q[d+1]-1;
					tp[++c]={px,i,ch[d][i],1};
				}px=askr(q[d+1][i].l,ch[d][i]);
				if(px){
					px=upper_bound(q[d+1],q[d+1]+cq+1,(itv){px,0,0})-q[d+1]-1;
					if(!ch[d][px])tp[++c]={i,px,ch[d][i],1};
				}
			}
		sort(tp+1,tp+c+1);px=1;
		memset(nok,0,(cp+1)*sizeof(bool));
		for(int i=1;i<=cq;i++){
			while(cx&&p[d][td[cx]].r==i)cx--;
			while(px<=cp&&p[d][px].l==i)td[++cx]=px,px++;
			if(ch[d][i])while(cx&&p[d][td[cx]].w<=ch[d][i])nok[td[cx]]=1,cx--;
		}px=cx=1;int cl=0;
		while(px<=cp||cx<=c){
			while(px<=cp&&nok[px])px++;
			if(px>cp&&cx>c)break;
			if(cx>c||px<=cp&&cx<=c&&(p[d][px].l<tp[cx].l||p[d][px].l==tp[cx].l&&p[d][px].w>tp[cx].w))
				p[d+1][++cl]=p[d][px],px++;
			else p[d+1][++cl]=tp[cx],cx++;
		}cp=cl;
	}
	bool cmp(int x,int y){return pl[x]<pl[y];}
	int gp(int x,int y,int z){
		int l=1,r=y,md,an=0;
		while(l<=r){
			md=(l+r)>>1;
			if(p[z][td[md]].w<=x)an=md,r=md-1;
			else l=md+1;
		}return td[an];
	}
	void solve(int d,int lx,int rx,int cp,int cq,int an){
		if(lx==rx){
			for(int i=1;i<=cp;i++)
				an+=p[d][i].c*(p[d][i].r<pl[lx]||p[d][i].l>pl[lx]||p[d][i].w>h[lx]);
			ans[lx]=an+(askl(q[d][pl[lx]].l,h[lx])>0)+(askr(q[d][pl[lx]].l,h[lx])>0);return;
		}int mid=(lx+rx)>>1;int c=0;
		for(int i=1;i<=cq;i++){
			if(c&&!(q[d][i].w|tq[c].w))tq[c].r=q[d][i].r;
			else tq[++c]=q[d][i];id[i]=c;
		}cq=c;memcpy(q[d],tq,(c+1)*sizeof(itv));
		for(int i=lx;i<=rx;i++)
			tx[d][i]=pl[i],pl[i]=id[pl[i]],pt[i]=i;
		stable_sort(pt+lx,pt+rx+1,cmp);c=0;
		for(int i=1;i<=cp;i++){
			p[d][i].l=id[p[d][i].l],p[d][i].r=id[p[d][i].r];
			if(p[d][i].l==p[d][i].r)an+=p[d][i].c;else tp[++c]=p[d][i];
		}cp=c;memcpy(p[d],tp,(c+1)*sizeof(pii));c=0;int tl=1,tr=lx;
		for(int i=1;i<=cq;i++){
			while(c&&p[d][td[c]].r==i)c--;
			while(tl<=cp&&p[d][tl].l==i)td[++c]=tl,tl++;
			if(q[d][i].w){
				ex[gp(a[q[d][i].l],c,d)]=1;
				while(tr<=rx&&pl[pt[tr]]<=i){
					if(pl[pt[tr]]==i)ex[gp(h[pt[tr]],c,d)]=1;tr++;
				}
			}
		}c=0;
		for(int i=1;i<=cp;i++){
			if(!ex[i]&&c&&tp[c].l==p[d][i].l&&tp[c].r==p[d][i].r)
				tp[c].c+=p[d][i].c;else tp[++c]=p[d][i];ex[i]=0;
		}cp=c;memcpy(p[d],tp,(c+1)*sizeof(pii));
		for(int i=1;i<=cq;i++)ch[d][i]=q[d][i].w?a[q[d][i].l]:0;
		for(int i=lx;i<=mid;i++)ch[d][pl[i]]=0;
		for(int i=1;i<=cq;i++)if(ch[d][i])chg(q[d][i].l,ch[d][i]);
		work(d,(c=cp),cq);solve(d+1,lx,mid,c,cq,an);
		for(int i=lx;i<=mid;i++)a[q[d][pl[i]].l]=h[i];
		for(int i=1;i<=cq;i++)if(ch[d][i])ch[d][i]=0,chg(q[d][i].l,0);
		for(int i=lx;i<=rx;i++)ch[d][pl[i]]=h[i];
		for(int i=mid+1;i<=rx;i++)ch[d][pl[i]]=0;
		for(int i=1;i<=cq;i++)if(ch[d][i])chg(q[d][i].l,ch[d][i]);
		work(d,(c=cp),cq);solve(d+1,mid+1,rx,c,cq,an);
		for(int i=1;i<=cq;i++)if(ch[d][i])ch[d][i]=0,chg(q[d][i].l,0);
		for(int i=lx;i<=rx;i++)pl[i]=tx[d][i];
	}
	vector<long long int> streetlights_main(){
		chg(0,1e9),chg(n+1,1e9);
		for(int i=1;i<=n;i++)chg(i,a[i]);int px,c=0;
		for(int i=1;i<=n;i++)ans[0]+=(askl(i,a[i])>0);
		for(int i=1;i<=n;i++)q[1][i]={i,i,0};
		for(int i=1;i<=m;i++)q[1][pl[i]].w=1;
		for(int i=1;i<=n;i++)if(q[1][i].w)chg(i,0);
		for(int i=1;i<=n;i++)
			if(!q[1][i].w)if(px=askr(i,a[i]))p[1][++c]={i,px,a[i],1};
		solve(1,1,m,c,n,0);vector<long long int> res;
		for(int i=0;i<=m;i++)res.push_back(ans[i]);
		return res;
	}
}

vector<long long int> count_cable(vector<int> A, vector< pair<int, int> > C){
	streetlights::n=A.size();streetlights::m=C.size();
	for(int i=0;i<streetlights::n;i++)streetlights::a[i+1]=A[i];
	for(int i=0;i<streetlights::m;i++)
		streetlights::pl[i+1]=C[i].first,streetlights::h[i+1]=C[i].second;
	return streetlights::streetlights_main();
}
```

---

## 作者：yukimianyan (赞：1)

## 题目描述

有 $n$ 座灯塔排成一排，第 $i$ 座灯塔的高度是 $a_i$。你需要求出有多少对 $l < r$ 满足 $a_l = a_r$，且 $\forall l < i < r, a_i < a_l$。
灯塔的高度有 $Q$ 次修改，每次给定 $x, h$，表示将 $a_x$ 修改为 $h$。求出修改之前和每次修改之后的答案。

$n\leq 10^5, Q\leq 2.5\times 10^5,1\leq a_i, h\leq 10^9$。

## 解法 1

$n \leq 1000$。

单调栈随便做。。。

## 解法 2

保证只有至多 $C=1000$ 座灯塔的高度发生过变化。

将修改过的灯塔称为动点，没改过的灯塔称为静点。动点很少，考虑动点与动点之间、动点与静点之间的直接暴力。题解说可以 $O(CQ)$，可能的做法是对于动点-动点区间每次都跑单调栈，动点-静点区间可以忽略掉所有动点的影响预先跑单调栈（每个动点最多两个可能的动点-静点区间），然后维护有多少个动点正在刺破这个动点-静点区间，修改之后 $O(Q)$ 地维护刚才说的东西。

至于静点-静点区间，这个才是大头。首先无视所有动点，单调栈跑出所有 $O(n)$ 个区间。观察到这些区间要么不交要么包含（可能共端点，考虑连续三个相同的数），那么惯用手法就是建一棵树出来，互相包含的区间为祖孙关系，相当于整了一种很新的笛卡尔树出来，也用单调栈建。注意要使树上的每个点都代表一个区间。然后考虑动点影响，动点可能会刺穿树上的一条直链（深度递增的链），且这条链要么是空要么链底总是固定的，预处理这个链底（不一定是叶子哦），每次修改之后在树上倍增或者树剖等在树上跳，在刺穿的直链上打上标记（不覆盖是因为标记需要撤销），这部分依据实现写树剖线段树是 $O(Q\log^2 n)$。

## 解法 3

可以将部分分做法和根号重构结合一下，题解说过不了。所以考虑线段树分治，在向下递归的过程中，越来越多的动点被固定下来转化为静点，此时要考虑这些动点对祖先的静点的影响。在每个节点都建好静点-静点的区间的树，在子树中的动点上来刺树时，用一些单调栈、双指针技巧将这些动点在树上的位置找出来，然后树剖线段树。

但是你仔细算一下这么搞的复杂度。首先算动点定位，每个点上挂的节点都要进行子树大小加深度次扫描，只要根节点上挂足够多全局静点就会 TLE。还有树剖部分，一共 $O((n+Q)\log Q)$ 个点，每个点需要去找 $\log Q$ 个祖先的树，各自在 $\log Q$ 棵树上进行 $O(\log^2n)$ 的树剖，总计 $O((n+Q)\log^2Q\log^2n)$，直接升天。

解决方法是换个方向，考虑这个节点的树对子树内的点的贡献，因为我们知道长度为 $l$ 的区间内至多有 $O(l)$ 个本质不同点（即这段时间内被修改过的点，否则它不会进入这个子树），可以找出这些点，然后在树上定位它们（复杂度 $O((n+Q)\log Q)$，算上排序再乘一个 $O(\log n)$），然后可以暴力在子树内 dfs 做线段树分治的过程（共 $O(Q\log Q)$ 次调用树剖线段树）或者常数小一点的话先将涉及到的点在这段时间之前的状态处理出来，计算它们在树上的贡献，然后再扫描这段时间的所有修改。

至此本题可以在大约 $O((n+Q)\log^2Q+Q\log Q\log^2n)$ 的时间内解决（使用树剖线段树），写全局平衡二叉树可以优化到 $O(n\log^2n)$（视 $n, Q$ 同阶）。

## 实现细节

### 线段树二分

写 zkw 线段树，我们需要单点修改，找 $x$ 前面第一个不小于 $a_x$ 的数，$x$ 后面第一个不小于 $a_x$ 的数，可以看一下怎么写，这个是真的妙。

### 全局平衡二叉树

可参考下面的实现，感觉写的挺好。注意这里有一个线段树二分（平衡树二分？），只会在最后一次调用时发生递归，且因为二叉树深度不超过 $O(\log n)$ 所以单次操作还是 $O(\log n)$。

### 单调栈

对这些区间的某一个端点排序，稍微推导一下就能写，注意别写假了。


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
vector<pair<int, int>> Q[1000010];
void insqry(int L, int R, int i, int h, int p, int l, int r) {/*{{{*/
  if (L <= l && r <= R) return Q[p].emplace_back(i, h), void();
  int mid = (l + r) >> 1;
  if (L <= mid) insqry(L, R, i, h, p << 1, l, mid);
  if (mid < R) insqry(L, R, i, h, p << 1 | 1, mid + 1, r);
}/*}}}*/
template <int N>
struct zkwtree {/*{{{*/
  int mx[N << 1];
  static_assert((N & (N - 1)) == 0);
  void mdf(int x, int v) { for (mx[x += N] = v; x >>= 1; mx[x] = max(mx[x << 1], mx[x << 1 | 1])); }
  int fdpre(int x) {
    int v = mx[x += N];
    for (; x; x >>= 1) if (x & 1 && mx[x ^ 1] >= v) { x ^= 1; break; }
    while (x && x < N) x = x << 1 | (mx[x << 1 | 1] >= v);
    return x && mx[x] == v ? x - N : 0;
  }
  int fdnxt(int x) {
    int v = mx[x += N];
    for (; x; x >>= 1) if (~x & 1 && mx[x ^ 1] >= v) { x ^= 1; break; }
    while (x && x < N) x = x << 1 | !(mx[x << 1] >= v);
    return x && mx[x] == v ? x - N : 0;
  }
};/*}}}*/
zkwtree<1 << 17> zkw;
constexpr int N = 1e5 + 10;
pair<int, int> opt[250010], H[200010];
int n, q, cnt, ans[250010], a[100010], lst[100010], stk[N], b[100010];
namespace seg {
  int tag[N], len[N], ch[N][2], tf[N], vl[N], vr[N], his[N], val[N];
  int fa[N], dfn[N], rnk[N], siz[N], son[N], dep[N], top[N];
  void maintain(int p) {
    if (tag[p]) len[p] = 0;
    else len[p] = len[ch[p][0]] + !his[p] + len[ch[p][1]];
  }
  int build(int l, int r) {
    if (l > r) return 0;
    int L = l, R = r, ans = l, T = siz[rnk[l]] - siz[son[rnk[r]]];
    while (L <= R) {
      int mid = (L + R) >> 1;
      if ((siz[rnk[l]] - siz[son[rnk[mid]]]) * 2 <= T) ans = mid, L = mid + 1;
      else R = mid - 1;
    }
    int p = rnk[ans];
    if ((ch[p][0] = build(l, ans - 1))) tf[ch[p][0]] = p;
    if ((ch[p][1] = build(ans + 1, r))) tf[ch[p][1]] = p;
    tag[p] = his[p] = 0;
    maintain(p);
    vl[p] = val[rnk[l]], vr[p] = val[rnk[r]];
    return p;
  }
  void binary(int p, int v, int k) {
    if (vl[p] <= v) return tag[p] += k, maintain(p);
    if (vr[p] > v) return ;
    if (ch[p][0]) binary(ch[p][0], v, k);
    if (val[p] <= v) his[p] += k;
    if (ch[p][1]) binary(ch[p][1], v, k);
    maintain(p);
  }
  int update(int p, int v, int k) {
    int del = 0, lst = -1;
    while (p) {
      if (ch[tf[p]][0] != p && ch[tf[p]][1] != p) del -= len[p];
      if (ch[p][0] != lst) {
        if (val[p] <= v) his[p] += k;
        if (ch[p][0]) binary(ch[p][0], v, k);
      }
      maintain(p);
      if (ch[tf[p]][0] != p && ch[tf[p]][1] != p) del += len[p];
      lst = exchange(p, tf[p]);
    }
    return del;
  }
  vector<int> G[N];
  void dfs(int u, int f) {
    fa[u] = f, siz[u] = 1, dep[u] = dep[f] + 1, son[u] = 0;
    for (int v : G[u]) if (v != f) dfs(v, u), siz[u] += siz[v], siz[son[u]] < siz[v] && (son[u] = v);
  }
  void cut(int u, int topf) {
    dfn[u] = ++cnt, rnk[cnt] = u, top[u] = topf;
    if (son[u]) cut(son[u], topf);
    else seg::tf[seg::build(dfn[topf], dfn[u])] = fa[topf];
    for (int v : G[u]) if (v != fa[u] && v != son[u]) cut(v, v);
  }
}; // namespace seg
template <class T> void unique_proc(T arr[], int &len) {
  sort(arr + 1, arr + len + 1);
  len = (int)(unique(arr + 1, arr + len + 1) - arr - 1);
}
void build(const vector<pair<int, int>>& Qs) {
  int top = cnt = 0;
  for (auto e : Qs) {
    int i = e.first;
    if (int lpos = zkw.fdpre(i)) H[++cnt] = make_pair(lpos, i);
    if (int rpos = zkw.fdnxt(i)) H[++cnt] = make_pair(i, rpos);
  }
  unique_proc(H, cnt);
  for (int i = 1; i <= cnt; i++) {
    seg::G[i].clear(), seg::dfn[i] = 0, seg::val[i] = a[H[i].first];
    while (top && H[stk[top]].second <= H[i].first) --top;
    if (top && H[stk[top]].second >= H[i].second) seg::G[stk[top]].push_back(i);
    stk[++top] = i;
  }
  int cnt0 = exchange(cnt, 0);
  for (int i = 1; i <= cnt0; i++) if (!seg::dfn[i]) seg::dfs(i, 0), seg::cut(i, i);
}
int ont[100010], vec[350010];
void solve(int p, int l, int r) {
  for (auto e : Q[p]) zkw.mdf(e.first, a[e.first] = e.second);
  build(Q[p]);
  if (l == r) ans[l] += cnt;
  else if (cnt) {
    int tot = 0;
    for (int pd = p << 1, rd = (l + r) >> 1; l <= rd; pd <<= 1, rd = (l + rd) >> 1) {
      for (auto e : Q[pd]) vec[++tot] = e.first;
      if (l == rd) break;
    }
    ont[opt[l].first] = 0;
    for (int i = l + 1; i <= r; i++) assert(!a[opt[i].first]), vec[++tot] = opt[i].first;
    unique_proc(vec, tot);
    auto mapping = [&]() {/*{{{*/
      int top = 0, itl = cnt, itr = tot;
      for (int k = 1; k <= cnt + tot; k++) {
        if (itl && (!itr || H[itl].first > vec[itr])) {
          while (top && stk[top] <= H[itl].second) ont[stk[top--]] = itl;
          --itl;
        } else stk[++top] = vec[itr--];
      }
      while (top) ont[stk[top--]] = 0;
    };/*}}}*/
    mapping();
    int now = cnt;
    for (int i = 1; i <= tot; i++) {
      int x = vec[i];
      now += seg::update(ont[x], a[x] = b[x], +1);
    }
    if (!l) ans[l] += now;
    for (int i = l + !l; i <= r; i++) {
      int x = opt[i].first;
      now += seg::update(ont[x], a[x], -1);
      now += seg::update(ont[x], a[x] = opt[i].second, +1);
      ans[i] += now;
    }
    for (int i = 1; i <= tot; i++) a[vec[i]] = 0;
  }
  if (l != r) {
    int mid = (l + r) >> 1;
    solve(p << 1, l, mid);
    solve(p << 1 | 1, mid + 1, r);
  } else if (l) {
    b[opt[l].first] = opt[l].second;
  }
  for (auto e : Q[p]) zkw.mdf(e.first, a[e.first] = 0);
}
vector<LL> count_cable(vector<int> A, vector< pair<int, int> > C) {
  n = (int)A.size();
  q = (int)C.size();
  for (int i = 1; i <= n; i++) a[i] = A[i - 1];
  memcpy(b, a, sizeof b);
  for (int t = 1, i; t <= q; t++) {
    i = C[t - 1].first;
    opt[t].first = i;
    insqry(lst[i], t - 1, i, a[i], 1, 0, q);
    lst[i] = t;
    a[i] = C[t - 1].second;
    opt[t].second = a[i];
  }
  for (int i = 1; i <= n; i++) insqry(lst[i], q, i, a[i], 1, 0, q);
  memset(a, 0, sizeof a);
  solve(1, 0, q);
  return vector<LL>(ans + 0, ans + q + 1);
}
```

---

## 作者：CarroT1212 (赞：0)

模拟赛与此题大战三个小时勉强战胜。这是一个码量为线段树分治正解一半的做法。

显然的是架出来的电线最多 $n-1$ 条。连线形成嵌套关系，且每个左端点 $i$ 都对应一个**唯一**可能的右端点 $nxt_i$。这个右端点可以选择用两种方式刻画：

+ $nxt_i$ 是 $i$ 右侧第一个 $=A_i$ 的位置，合法要求 $[i+1,nxt_i-1]$ 中间所有 $A_j$ 都 $<A_i$；
+ $nxt_i$ 是 $i$ 右侧第一个 $\ge A_i$ 的位置，合法要求 $A_i=A_{nxt_i}$。

然后有档部分分是，变化过的位置最多 $B=1000$ 个。考虑一下。我们称这些位置为变位，否则为非变位。非变位形成了 $O(B)$ 个连续段。

电线可以分为以下几种：

+ 连接两个变位的。
+ 左边连变位，右边连非变位的。

以上两种可以根据上面的第二种刻画来统计：

把变位和非变位段排到一起，令它们的权值分别为变位的高度，和非变位段里的最大高度。从后往前跑单调栈，我们就能找到每个变位 $i$ 右边第一个不小于它的位置，是哪个变位，或者在哪个非变位段里。

如果是变位，直接看一下是否是相等的即可。

如果是非变位段，我们希望知道这个非变位段里面，存不存在一个前缀最大值，等于 $A_i$。这个可以对每个非变位段预处理一下丢进哈希表里，每次 $O(1)$ 查询。

这部分是每次询问 $O(B)$ 的。

+ 左边连非变位，右边连变位的。

反着做一遍。

+ 连接两个非变位的。

那么这样的每对 $A_i=A_{nxt_i}$ 的 $(i,nxt_i)$ 不会因为询问改变，可以预处理出来。如果 $(i,nxt_i)$ 中间没有跨过变位，那它可以在每次询问中都合法出现，加到全局答案里即可。

但是如果跨过了，那它合法出现还要求，中间的所有变位在**当前询问**时的高度全部都 $<A_i$。

这样的连线有 $O(n)$ 条，并不能每次询问都遍历判断一遍。

一种做法是，因为连线嵌套，可以根据连线的包含关系建一棵树出来。每次修改一个变位，会导致树中一条链上代表的所有连线的合法性统一变化，可以树剖维护。这样会给每次询问带上一个和 $B$ 无关的 $\log^2$。但据说是不好写的，而且建树常数很大，后续推广需要聪明的实现。

而我们有一种低能一点的思路。设非变位 $i$ 所在的非变位段编号为 $bel_i$。那么每对非变位的连线 $(i,nxt_i)$，连线连接的段 $(bel_i,bel_{nxt_i})$，这样的段对是只有 $O(B)$ 种的。画一下图就可以感受得到。

而 $(bel_i,bel_{nxt_i})$ 相同的所有 $(i,nxt_i)$ 连线，如果按照左端点 $i$ 递增排序，一定形如，高度 $A_i$ 递减，右端点 $nxt_i$ 递减，前面的连线会包住后面的连线。那么设某次询问时 $(bel_i,bel_{nxt_i})$ 中间最大的变位高度为 $mx$，此时所有 $A_i>mx$ 的连线都合法，而这些连线为一段前缀，可以二分找到。

每次询问，对每一对 $(bel_i,bel_{nxt_i})$ 求出这样的前缀长度就好了（可以特判省去无用的二分减少常数）。而求每一对的 $mx$ 不需要开额外的数据结构，可以根据嵌套关系做一些奇妙的乱搞。

于是这档部分分就获得了一个 $O(QB\log N)$ 左右的做法。那个 $\log N$ 显然完全卡不满。而且应该是有办法去掉的？

不过想到这里的人应该都不会去写这档分了，因为对于没有特殊性质的问题，只要我们做个定期重构，把操作每 $B$ 个分一段，每一段重做预处理，就完全变为了这档分的做法。每次预处理操作都可以做到 $O(N)$，所以最终的复杂度就是 $O(\frac{NQ}{B}+QB\log n)$ 的。

$B$ 的最优选取因实现而异，我测出来 $370$ 附近是最优的。不过即使这样，光是预处理部分每遍历一次 $1\sim N$ 都得多个五六百毫秒。所以虽然复杂度是卡不满，但是本身常数确实很大，写的时候还是注意一点。

3.3K，最大 2.7s。

```cpp
const int I=1e9,N=1e5+7,Q=2.5e5+7,B=350,P=2e5+7,K=114514;
const ll J=1e18;
int n,q,a[N],c[N],ans[Q];
int bw[N],wb,ww[N],is[N],bel[N],mx[N],nxt[N];
int st[N],tp;
pii cnq[Q];
struct hsh {
	int hd[P],frm[N*2],cnn;
	pii st[N*2];
	int get(pii x) { return (1ll*x.fi*K+x.se)%P; }
	void clr() {
		for (int i=1;i<=cnn;i++) hd[get(st[i])]=0,frm[i]=0;
		cnn=0;
	}
	void ins(pii x) {
		int k=get(x);
		frm[++cnn]=hd[k],st[cnn]=x,hd[k]=cnn;
	}
	bool fnd(pii x) {
		int k=get(x);
		for (int i=hd[k];i;i=frm[i]) if (st[i]==x) return 1;
		return 0;
	}
} H;
struct edg { int l,r,x; } b[N]; int m;
struct nod { int cl,cr,l,r; } bq[N]; int nm; int bmx[N];
void solve(int _l,int _r) {
	wb=0; for (int i=1;i<=n;i++) is[i]=0; int alas=0;
	for (int i=_l;i<=_r;i++) bw[++wb]=cnq[i].fi;
	sort(bw+1,bw+wb+1),wb=unique(bw+1,bw+wb+1)-1-bw,bw[wb+1]=n+1;
	for (int i=1;i<=wb;i++) is[bw[i]]=i,ww[i]=a[bw[i]];
	H.clr();
	for (int o=0;o<=wb;o++) {
		int l=bw[o]+1,r=bw[o+1]-1; mx[o]=0;
		for (int i=l,mx=0;i<=r;i++) {
			bel[i]=o;
			if (a[i]>mx) H.ins({o*2,mx=a[i]}),::mx[o]=mx;
		}
		for (int i=r,mx=0;i>=l;i--) if (a[i]>mx) H.ins({o*2+1,mx=a[i]});
	}
	m=0,tp=0; for (int i=n;i;i--) if (!is[i]) {
		while (tp&&a[st[tp]]<a[i]) tp--;
		nxt[i]=tp&&a[st[tp]]==a[i]?st[tp]:0,st[++tp]=i;
		if (nxt[i]) {
			if (bel[nxt[i]]==bel[i]) alas++;
			else b[++m]={i,nxt[i],a[i]};
		}
	}
	int j=1;
	auto get=[&](int x,int y) {
		bq[++nm]={x,y,j,j-1};
		while (j<=m&&bel[b[j].l]==x&&bel[b[j].r]==y) j++;
		bq[nm].r=j-1;
	};
	nm=0,tp=0; for (int i=wb;~i;i--) {
		while (tp&&mx[st[tp]]<=mx[i]) get(i,st[tp]),tp--;
		if (tp) get(i,st[tp]);
		st[++tp]=i;
	}
	for (int oo=_l;oo<=_r;oo++) {
		a[cnq[oo].fi]=cnq[oo].se,ww[is[cnq[oo].fi]]=cnq[oo].se;
		int ans1=0,ans2=0,ans3=0;
		auto getx=[&](int x){return x&1?mx[x>>1]:ww[x>>1];};
		tp=0; for (int i=wb;i;i--) {
			while (tp&&mx[i]>getx(st[tp])) tp--; st[++tp]=i*2+1;
			while (tp&&ww[i]>getx(st[tp])) tp--; 
			if (tp) {
				if (st[tp]&1&&H.fnd({st[tp]/2*2,ww[i]})) ans2++;
				else if (st[tp]&1^1&&ww[st[tp]/2]==ww[i]) ans1++;
			}
			st[++tp]=i*2;
		}
		tp=0; for (int i=1;i<=wb;i++) {
			while (tp&&mx[i-1]>getx(st[tp])) tp--; st[++tp]=i*2-1;
			while (tp&&ww[i]>getx(st[tp])) tp--; 
			if (tp) {
				if (st[tp]&1&&H.fnd({st[tp]/2*2+1,ww[i]})) ans2++;
			}
			st[++tp]=i*2;
		}
		bmx[nm]=0;
		for (int o=1;o<=nm;o++) {
			if (bq[o].cl+1==bq[o].cr) bmx[bq[o].cl]=ww[bq[o].cr];
			else bmx[bq[o].cl]=max(bmx[bq[o].cl],bmx[bq[o-1].cr]);
			int l=bq[o].l,r=bq[o].r,val=bmx[bq[o].cl];
			if (l<=r) {
				if (b[l].x>val) ans3+=r-l+1;
				else if (b[r].x<=val);
				else {
					int mid,res=r;
					while (l<=r) {
						mid=l+r>>1;
						if (b[mid].x>val) res=mid,r=mid-1;
						else l=mid+1;
					}
					ans3+=bq[o].r-res+1;
				}
			}
		}
		ans[oo]=ans1+ans2+ans3+alas;
	}
}
void mian() {
	cnq[0]={1,a[1]};
	for (int l=0,r=min(B-1,q);l<=q;l+=B,r=min(r+B,q)) solve(l,r);
}
vector<ll> count_cable(vector<int> _A,vector<pii> _C) {
    n=_A.size(),q=_C.size();
	for (int i=1;i<=n;i++) a[i]=_A[i-1];
	cnq[0]={1,a[1]};
	for (int i=1;i<=q;i++) cnq[i]={_C[i-1].fi,_C[i-1].se};
	mian();
    vector<ll> result(q+1);
    for (int i=0;i<=q;i++) result[i]=ans[i];
    return result;
}
```

---

