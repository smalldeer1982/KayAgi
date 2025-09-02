# [ABC379F] Buildings 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc379/tasks/abc379_f

有 $N$ 栋建筑从西向东依次排列，编号为建筑 $1$ 到建筑 $N$，其中建筑 $1$ 位于最西侧，建筑 $N$ 位于最东侧。建筑 $i$（$1 \leq i \leq N$）的高度为 $H_i$。

对于整数对 $(i,j)$（$1 \leq i < j \leq N$），当满足以下条件时，可以从建筑 $i$ 看到建筑 $j$：

- 在建筑 $i$ 和建筑 $j$ 之间不存在比建筑 $j$ 更高的建筑。即，不存在整数 $k$（$i < k < j$）满足 $H_k > H_j$。

现在需要回答 $Q$ 个询问。第 $i$ 个询问给出整数对 $(l_i, r_i)$（$l_i < r_i$），要求统计在建筑 $r_i$ 东侧的建筑（即建筑 $r_i+1$, 建筑 $r_i+2$, $\ldots$, 建筑 $N$）中，能够同时从建筑 $l_i$ 和建筑 $r_i$ 看到的建筑数量。

## 说明/提示

### 约束条件

- $2 \leq N \leq 2 \times 10^5$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq H_i \leq N$
- $H_i \neq H_j$（$i \neq j$）
- $1 \leq l_i < r_i \leq N$
- 输入中的所有值均为整数

### 样例解释 #1

- 对于第一个询问，在建筑 $2$ 东侧的建筑中，能够同时从建筑 $1$ 和建筑 $2$ 看到的建筑有建筑 $3$ 和建筑 $5$，共 $2$ 栋。
- 对于第二个询问，建筑 $5$ 东侧没有建筑。
- 对于第三个询问，在建筑 $4$ 东侧的建筑中，能够同时从建筑 $1$ 和建筑 $4$ 看到的建筑只有建筑 $5$，共 $1$ 栋。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5 3
2 1 4 3 5
1 2
3 5
1 4```

### 输出

```
2
0
1```

## 样例 #2

### 输入

```
10 10
2 1 5 3 4 6 9 8 7 10
3 9
2 5
4 8
5 6
3 8
2 10
7 8
6 7
8 10
4 10```

### 输出

```
1
3
1
2
1
0
1
1
0
0```

# 题解

## 作者：PineappleSummer (赞：14)

[F - Buildings 2](https://atcoder.jp/contests/abc379/tasks/abc379_f)

提供一个比较简单的做法。

考虑一个事情：对于一对 $(l,r)$，在 $l$ 处能看到的位置大于 $r$ 的楼房，在 $r$ 处一定也能看到；在 $r$ 处能看到的楼房，在 $l$ 处不一定能看到。

因此，$(l,r)$ 都能看到的楼房一定是 $l$ 能看到的位置大于 $r$ 处的所有楼房。

将询问离线，挂在 $l$ 处。从序列最后倒着做一个单调栈，存着在当前点能够看到的楼房编号。

那么在 $l$ 处，对于所有以 $l$ 为左端点的询问点对 $(l,r)$，能看到的楼房个数就是当前单调栈中位置大于 $r$ 的楼房个数，可以通过在单调栈上二分查找得到。

最后按询问顺序输出答案即可。

设 $n,q$ 同阶，时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> pii;
const int N = 1e6 + 10;
int n, Q, a[N];
int st[N], tot, ans[N];
vector <pii> query[N];
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> Q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, l, r; i <= Q; ++i)
        cin >> l >> r, query[l].emplace_back (r, i);
    for (int i = n; i; --i) {
        for (auto [j, id] : query[i]) {
            int l = 1, r = tot;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (st[mid] > j) l = mid;
                else r = mid - 1;
            }
            if (st[l] <= j) ans[id] = 0; // 单调栈中不存在位置大于 j 的点
            else ans[id] = l;
        }
        while (tot && a[st[tot]] < a[i]) --tot;
        st[++tot] = i;
    }
    for (int i = 1; i <= Q; ++i) cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：small_lemon_qwq (赞：8)

我可以说这道题水吗？

考虑一个理论：若 $i$ 能看到 $j$，且 $j<i$ 则 $i$ 能看到 $j+1$。

我们发现这似乎是一个单调性，可以用来二分查找 $i$ 能看到的编号最小的楼，记作 $b_i$。

那么问题就变成了问满足 $j\in(r_i,n]$ 且 $b_j\le i$ 的个数，可以离线将 $r_i$ 按降序排序然后用树状数组存储即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[200005],f[200005][32],lg[200005],b[200005],c[200005],ans[200005],cnt[200005];
int getm(int l,int r){
	int i=lg[r-l+1];
	return max(f[l][i],f[r-(1ll<<i)+1][i]);
}
struct ask{
	int i,l,r;
	bool operator<(const ask&x)const{
		return r>x.r;
	}
}did[200005];
namespace BIT{
	int t[200005];
	void add(int x,int y=1){for(;x<=n;x+=x&-x)t[x]+=y;}
	int ask(int x){int s=0;for(;x;x-=x&-x)s+=t[x];return s;}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	lg[0]=-1;
	for(int i=1;i<=2e5;i++)lg[i]=lg[i/2]+1;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i][0]=a[i];
	}
	for(int i=1;i<=30;i++){
		for(int j=1;j+(1ll<<i)-1<=n;j++){
			f[j][i]=max(f[j][i-1],f[j+(1<<i-1)][i-1]);
		}
	}
	for(int i=1;i<=n;i++){
		int L=1,R=i;
		while(L<=R){
			int mid=(L+R)>>1;
			if(getm(mid+1,i-1)<=a[i]){
				R=mid-1;
			}else{
				L=mid+1;
			}
		}
		b[i]=R+1;
	}
	for(int i=1;i<=m;i++){
		cin>>did[i].l>>did[i].r;
		did[i].r++;
		did[i].i=i;
	}
	stable_sort(did+1,did+m+1);
	int R=n+1;
	for(int i=1;i<=m;i++){
		while(R>did[i].r)BIT::add(b[--R]);
		ans[did[i].i]=BIT::ask(did[i].l);
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：Conan15 (赞：5)

提供一种支持在线回答询问的做法。

转化一下条件：$i$ 能看到 $j$ 仅当 $(\max\limits_{k=i+1}^{j-1} h_k) \lt h_j$。\
考虑对于每个 $j$，我们求出最大的 $i$ 满足 $i \lt j$ 且 $h_i \gt h_j$，此时 $i$ 能看到 $j$。\
这可以用**单调栈**求解左边第一个比它大的元素下标，记为 $pre_j$，于是有一个性质：$i \in [pre_j, j)$ 的元素都可以看到 $j$。

那么对于一个询问 $l,r$，我们需要统计 $j \in (r,n]$ 有多少个 $pre_j \leq l$。\
这是一个**二维数点**的形式，显然可以直接用**可持久化线段树**维护这个东西。

综上，预处理倒着枚举 $r$ 并单点加，查询就是某个历史版本的前缀和。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 15;
int n, m, tot = 0;
struct Tree {
    int lt, rt;
    int sum;
} tr[N << 5];

void change(int &u, int v, int l, int r, int d) {
    u = ++tot;
    tr[u].lt = tr[v].lt, tr[u].rt = tr[v].rt;
    tr[u].sum = tr[v].sum + 1;
    if (l == r) return;
    int mid = l + r >> 1;
    if (d <= mid) change(tr[u].lt, tr[v].lt, l, mid, d);
    else change(tr[u].rt, tr[v].rt, mid + 1, r, d);
}
int query(int u, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) return 0;
    if (l >= ql && r <= qr) return tr[u].sum;
    int mid = l + r >> 1, res = 0;
    if (ql <= mid) res += query(tr[u].lt, l, mid, ql, qr);
    if (qr > mid) res += query(tr[u].rt, mid + 1, r, ql, qr);
    return res;
}

int a[N], pre[N];
int stk[N], top = 0;
int root[N];
void init() {
    for (int i = 1; i <= n; i++) {
        while (top && a[stk[top]] < a[i]) top--;
        pre[i] = stk[top];
        stk[++top] = i;
    }
    root[n + 1] = 0;
    for (int i = n; i >= 1; i--)
        change(root[i], root[i + 1], 0, n, pre[i]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    init();
    // for (int i = 1; i <= n; i++) cout << pre[i] << ' '; puts("");
    while (m--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", query(root[r + 1], 0, n, 0, l));
    }
    return 0;
}
```

---

## 作者：Xuan_qwq (赞：4)

upd：修正了原文与注释的一点细节错误和示意图错误。

---
这里提供一种不需要高级数据结构的在线做法。

我们发现每个点向右看能看到的，且比自己高的建筑数量是可以用单调栈线性求的，可以先预处理出来，设为 $rs_i$。然后我们考虑询问：

对于每一个询问，考虑 $l+1$ 到 $r$ 这些建筑的高度最大值，设为 $h_{max}$，这可以很轻松地用 ST 表求出来。

如果 $h_{max}=h_r$，那么 $l$ 向右看到的建筑是 $r$ 向右看到的且不比 $r$ 低的建筑序列前面加上 $l+1$ 到 $r$ 中看到的建筑所得到的序列，此时容易知道答案为 $rs_r$。

但如果 $h_{max}>h_r$ 呢？

我们看一张示意图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ircnyvjq.png)

我们发现，答案所求长度的序列一定是 $r$ 看到的建筑序列的后缀，而该后缀的首个建筑的高度恰好大于等于 $h_{max}$。

所以我们的问题就变成了：在 $r$ 看到的建筑序列中，找到第一个高度大于等于 $h_{max}$ 的建筑。

这个问题可以使用倍增解决。记录每个建筑向右看到且不比自己低的建筑序列中，第 $2^0,2^1,2^2,\dots$ 个建筑是哪一个。查询时直接仿照最近公共祖先的跳法，找到序列中目标后缀的前一个建筑，输出该建筑向右能看到且不低于该建筑的建筑数量即可。

这里有一个坑点，就是一定要输出目标后缀的前一个建筑对应的答案，因为一个建筑向右看到的建筑是不包含它本身的。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,Q,lg[200005],f[200005][20],g[200005][20];
int h[200005],rs[200005];
int R,q[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>Q;lg[1]=0;
	for (int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)cin>>h[i],f[i][0]=h[i];
	h[0]=1e9+7;//这是哨兵
	for(int i=n;i>=1;i--){
		while(R>0&&h[q[R]]<h[i])R--;//队列里存的是编号！
		rs[i]=R;
		g[i][0]=q[R];//记录右侧第一个不小于自己的
		q[++R]=i;
	}//单调栈预处理rs[i]
	for (int j=1;j<=lg[n];j++)
		for (int i=1;i<=n-(1<<j)+1;i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]),
			g[i][j]=g[g[i][j-1]][j-1];//跳ST表和倍增
	while(Q--){
		int l,r;cin>>l>>r;
		l++;
		int len=lg[r-l+1];
		int mx=max(f[l][len],f[r-(1<<len)+1][len]);//区间最大值
		if(mx==h[r]){
			cout<<rs[r]<<endl;
			continue;
		}
		for(int i=18;i>=0;i--)
			if(h[g[r][i]]<mx)
				r=g[r][i];//直接跳
		cout<<rs[r]<<endl;
	}
	return 0;
}
```

---

## 作者：hellolin (赞：3)

考虑如果一栋 $r$ 右边的建筑 $x$ 可以被 $l$ 看到，那么 $x$ 必定也可以被 $r$ 看到。

证明是显然的，既然 $l$ 到 $x$ 之间没有高于 $x$ 的建筑，那么 $r$ 到 $x$ 之间也没有高于它的建筑。

离线询问，单调栈维护在 $l$ 右边能被它看到的递增建筑区间，然后栈上二分哪些建筑在 $r$ 右边即可。时间复杂度 $O(n\log n)$。

``` cpp
namespace hellolin {
void main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n), res(q);
  for (int &i : a)
    std::cin >> i;
  std::vector<std::vector<std::pair<int, int>>> b(n);
  for (int i = 0, l, r; i < q; ++i) {
    std::cin >> l >> r;
    --l, --r;
    b[l].emplace_back(r, i);
  }

  std::vector<int> stk;
  for (int l = n - 1; l >= 0; --l) {
    for (auto [r, p] : b[l]) {
      res[p] = std::distance(stk.begin(), ranges::lower_bound(stk, r, std::greater<int>{}));
    }
    // 这里栈上是一些递减的下标
    while (!stk.empty() and a[l] > a[stk.back()])
      stk.pop_back();
    stk.push_back(l);
  }
  for (int &i : res)
    std::cout << i << '\n';
}
} // namespace hellolin
```

---

## 作者：I_will_AKIOI (赞：3)

如果这道题只要求查询 $r$ 能看到的建筑数，很容易发现这是一个单调栈模板。但是题目加了一个 $l$，那么 $\max_{i=l+1}^r a_i$ 就会把 $l$ 的视野挡住一部分，这样 $l$ 能看到的建筑就需要满足 $r$ 能看到且不小于 $\max_{i=l+1}^r a_i$。容易发现如果知道了 $r$ 能看到的建筑，就可以用 ST 表求出 $\max_{i=l+1}^r a_i$，接着二分求出 $l$ 看到的建筑。但是本题 $r$ 并不是单调递减的，因此考虑离线做法，把 $r$ 从大到小排序，然后单调栈求解。

```cpp
#include<bits/stdc++.h>
#define N 200005
#pragma GCC optimize("O3")
using namespace std;
struct Data{int l,r,num;}w[N];
int n,q,len,last,res[N],s[N],a[N],f[N][20],Log[N];
bool cmp(Data x,Data y){return x.r>y.r;}
int query(int x,int y)
{
  int k=Log[y-x+1];
  return max(f[x][k],f[y-(1<<k)+1][k]);
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=2;i<N;i++) Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++) cin>>a[i],f[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++) for(int i=1;i+(1<<j)-1<=n;i++) f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
	for(int i=1;i<=q;i++) cin>>w[i].l>>w[i].r,w[i].num=i;
	sort(w+1,w+q+1,cmp);
	last=n;
	for(int i=1;i<=q;i++)
	{
		for(int j=last;j>w[i].r;j--)
		{
			while(len&&s[len]<a[j]) len--;
			s[++len]=a[j];
		}
		last=w[i].r;
		int l=0,r=len,mid,ans=0,maxx=query(w[i].l+1,w[i].r);
		while(l<r)
		{
			mid=l+r+1>>1;
			if(s[mid]>maxx) l=ans=mid;
			else r=mid-1;
		}
		res[w[i].num]=ans;
	}
	for(int i=1;i<=q;i++) cout<<res[i]<<"\n";
	return 0;
}
```

---

## 作者：MitchellZhong (赞：3)

# ABC 379 F
[题目传送门](https://www.luogu.com.cn/problem/AT_abc379_f)

对于区间 $[l,r]$ 来说，楼 $i(i>r)$，只有在以下情况能被看见：

- $x$ 大于 $[l,r]$ 的最大值，且 $x$ 到 $r$ 之间，没有大于他的元素。

发现可以用单调栈维护。从右向左维护一个递减的单调栈（里面的存的是下标），对于一组询问，找到第一个比 $r$ 大的就可以了。因为是单调栈们可以使用二分。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000005];
vector<pair<int,int> > q[1000005];
int ans[1000005];
int st[1000005],h;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        q[l].push_back({r,i});
    }
    for(int i=n;i>=1;i--){
        for(auto [rr,id] : q[i]){
            int l=1,r=h;
            int res=0;
            while(l<=r){
                int mid=(l+r)/2;
                if(st[mid]>rr){
                    res=mid;
                    l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            ans[id]=res;
        }
        while(h && a[st[h]]<=a[i]){
            h--;
        }
        st[++h]=i;
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
```

时间复杂度： $O(q\log n)$

---

## 作者：cjh20090318 (赞：2)

## 题意

有 $N$ 幢楼房，第 $i$ 幢楼房的高度为 $H_i$。

能从建筑 $i$ 看到建筑 $j$ 需要满足的条件是 $\nexists k \in (i,j) \cap \mathbb{Z}, H_k > H_j$。

有 $Q$ 次询问，每次询问给定 $(l,r)$，求 $(r+1,n]$ 中有多少个建筑物可以同时被 $l$ 和 $r$ 看到。

## 分析

将看到的定义转化成 $\forall k\in(i,j), H_k \le H_j$，也就是说 $\max\limits_{k=i+1}^{j-1} H_k \le H_j$。

因为 $l<r$，所以 $\max\limits_{k=l+1}^{j-1} H_k \ge \max\limits_{k=r+1}^{j-1} H_k$，也就是说能被 $l$ 看到的 $r$ 一定也能看到，所以就只需要考虑 $l$。

设 $a_i$ 表示最后一个在 $i$ 之前且这个位置的高度大于 $H_i$，只有当 $a_i \le l$ 时这个位置才能被 $l$ 看见。

于是问题就变成了 $(r,N]$ 中有多少个 $a_i \le l$，可以离线下来用树状数组求解。

$a_i$ 可以用单调栈求解，时间复杂度 $O(Q \log N)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<vector>
#define MAXN 200002
using namespace std;
typedef pair<int,int> PII;
int n,q;
int h[MAXN],a[MAXN],t[MAXN],p=0;
int ans[MAXN];
vector<PII> G[MAXN];
template<typename T>
struct fenwick_tree{
	public:
		fenwick_tree(int _SIZE=0):SIZE(_SIZE){dt=new T[SIZE+1]();memset(dt,0,sizeof(T)*(SIZE+1));}
		~fenwick_tree(){delete[] dt;}
		void add(int x,const T&v){for(;x<=SIZE;x+=x&-x)dt[x]+=v;}
		inline T sum(int x)const{T ret(0);for(;x;x^=x&-x)ret+=dt[x];return ret;}
	private:
		T*dt;
		int SIZE;
};
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&h[i]);
		while(p&&h[t[p]]<=h[i]) --p;//维护单调栈找到最后一个比他大的。
		a[i]=t[p],t[++p]=i;
	}
	for(int i=1,l,r;i<=q;i++) scanf("%d%d",&l,&r),G[r].emplace_back(l,i);//将询问加入。
	fenwick_tree<int> T(n);//树状数组。
	p=0;
	for(int i=n;i>0;--i){
		for(const PII&x:G[i]) ans[x.second]=T.sum(x.first)+p;//树状数组中查询小于等于 l 的个数，还要加上 a 等于 0 的数量。
		if(a[i]) T.add(a[i],1);else ++p;//树状数组单点加。
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：doumingze (赞：2)

简单玩一下样例可以发现：第 $i$ 组询问中，每一个在 $(r_i, n]$ 内的能被 $l_i$ 看到的建筑，$r_i$ 这个位置也都能够全部看到。相反 $r_i$ 能看到的所有建筑 $l_i$ 不一定能全看到（后面这个是显然的，例子也好举）。

先证明前面那一句：

首先 $l_i$ 能看到的建筑自西向东高度一定是单调递增的（显然如此，否则如果有一处不单调，这一处的建筑将无法被看到）。令 $g$ 数组为能被 $l_i$ 看到的，且下标大于 $r_i$ 的建筑（数组升序排序）。

接下来考虑反证法。我们假设 $g$ 数组中存在一些建筑无法被 $r_i$ 看到，此时按照我们的假设，在 $r_i$ 到某一个 $g_j$ 这个区间中存在一个高度 $> g_j$ 的建筑遮掉了 $g_j$（否则 $g$ 数组都能看到），令这个位置为 $k$，但是这个时候我们发现，按照题意 $l_i$ 也看不到 $g_j$ 了（$H_k > H_{g_j}$），而我们事先定义的 $g$ 数组中每一个 $g_j$ 都能被 $l_i$ 看到，于是与已知条件出现了矛盾，假设不成立，原命题成立，即 $l_i$ 位置能看到的建筑 $r_i$ 位置也一样能看的到。

上面的证明建议可以自己找个例子画个图理解一下。

那么做法就很显然了：先把询问离线下来。然后倒序维护每一个 $p$ 位置能看到的建筑，显然这是可以单调栈维护的（自栈底到栈顶，高度单调递减）。然后对于每一组 $l_i = p$ 的询问，我们直接在单调栈上二分找到最靠近栈顶的 $> r_i$ 的元素的位置 $t$，那么 $t$ 下面（包括 $t$）的所有元素就是 $l_i$ 和 $r_i$ 都能看到的。于是这组询问的答案就是 $t$。

不太理解就看代码。注意一下边界情况处理好。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
bool in_stk[N];
int stk[N], pos[N], top;
int h[N];
int n, qu;
struct Query{
	int l, r, id;
	bool operator < (const Query &w) const
	{
		return l > w.l; // 倒序维护，故按 l 降序排序
	}
}que[N];
int ans[N];

int main()
{
	cin >> n >> qu;
	for(int i = 1; i <= n; i ++) scanf("%d", &h[i]);
	for(int i = 1; i <= qu; i ++) scanf("%d%d", &que[i].l, &que[i].r), que[i].id = i;
	sort(que + 1, que + 1 + qu);
	stk[0] = n + 1;
	for(int i = n, ts = 0; i >= 1; i --) // 倒序维护
	{
		while(que[ts + 1].l == i && ts < qu)
		{
			ts ++;
			int l = 0, r = top;
			while(l < r)
			{
				int mid = l + r + 1 >> 1;
				if(stk[mid] > que[ts].r) l = mid; // 找比 r 大的且最靠近栈顶的元素的位置
				else r = mid - 1;
			}
			ans[que[ts].id] = l;
		}
		while(top && h[stk[top]] < h[i]) top --; // 此时小于 h[i] 的元素将不再被 [1, i) 中任何位置看到，失去贡献
		stk[++ top] = i; // 放入栈中，注意放的不是 h[i]
	}
	for(int i = 1; i <= qu; i ++) printf("%d\n", ans[i]);
	return 0;
}

```

---

## 作者：dayz_break404 (赞：2)

分析题目，发现对于每一个询问构成的答案集合，当集合内元素下标单调递增的时候，元素大小单调不降。且集合内相邻的两个数字 $a_i$ 和 $a_j$ 满足 $a_j$ 是 $a_i$ 之后第一个大于或等于 $a_i$ 的。

根据答案集合具有的单调性，考虑二分。

由于询问要求我们计算出答案集合的大小，暴力地一个一个地二分寻找，时间复杂度不可接受，考虑预处理出个数。注意到当答案集合的第一个数字确定之后，后面的数字个数也随之确定了。记以 $i$ 个元素开头后面可以构成答案的集合大小为 $cnt_i$，我们可以预先从后往前枚举每一个元素 $i$，二分找到第一个大于或等于他的数 $j$，于是有 $cnt_i=cnt_j+1$。

查询的时候二分找到 $[r+1,n]$ 区间内第一个符合条件的数字，那么答案就是 $cnt_i+1$。（因为 $cnt_i$ 不包括 $i$ 本身）

二分的判断可以用 st 表快速查询区间最值，时间复杂度为 $O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
const int maxn=2e5+20;
int st[maxn][30],n,a[maxn],q,cnt[maxn];
inline int get_max(int l,int r){
	int len=log2(r-l+1);
	return max(st[l][len],st[r-(1<<len)+1][len]);
}
int l,r,ans;
inline void init(){
	int t=(int)log2(n);
	for(int i=1;i<=t;i++){
		for(int j=1;j<=n-(1<<i)+1;j++){
			st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
		}
	}
	for(int i=n;i>=1;i--){
		l=i+1,r=n,ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(get_max(i+1,mid)>=a[i]) ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans!=-1) cnt[i]=cnt[ans]+1;
	}
}
inline void solve(int x,int y){
	l=y+1,r=n,ans=-1;
	int lim=get_max(x+1,y);
	while(l<=r){
		int mid=(l+r)>>1;
		if(get_max(y+1,mid)>=lim) ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(ans==-1) printf("0\n");
	else printf("%d\n",cnt[ans]+1);
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=st[i][0]=read();
	init();
	int x,y;
	while(q--){
		x=read(),y=read();
		solve(x,y);
	}
	return 0;
}
```

---

## 作者：刘梓轩2010 (赞：2)

纪念第一道在场上想出正解~~但没写出~~的 F 题。

## 题意

有 $n$ 栋大楼排成一排，给你 $q$ 次询问，每次给出 $l$ 和 $r$，问你在 $r$ 之后有多少栋大楼可以被 $l$ 到 $r$ 之间的大楼看到，定义两个楼能看到当且仅当它们之间没有比右边的楼更高的楼。

$n \le 2 \times 10^5$，$q \le 2 \times 10^5$。

## 思路

首先想到 $l$ 到 $r$ 之间的楼能向后看到的楼一定是一个单调不减的序列，而且一定是最靠近 $r$ 的单调不减的序列，否则就会互相遮挡看不见。

然后我们发现，能向后看到的楼的高度一定大于等于区间内的最大值，否则最大值左边的楼就看不见这栋楼了。如果最大值在最左边，那就要大于 $l+1$ 到 $r$ 之间的最大值。

所以我们先用单调栈倒序维护以每个点为开头的最近的单调不减序列的长度，记为 $ans_i$，用线段树找到区间内的最大值，然后可以用线段树二分找到 $r$ 之后的第一个大于最大值的楼的位置，记为 $pos$，$ans_{pos}$ 即为答案。

如果还没理解可以画图，或结合下面代码食用。

## Code

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
struct Node
{
    int l,r,val;
}tr[N<<2];
int n,q;
int a[N];
int ans[N];
inline void pushup(int rt)
{
    tr[rt].val=max(tr[rt<<1].val,tr[rt<<1|1].val);
}
void build(int rt,int l,int r)
{
    tr[rt].l=l,tr[rt].r=r;
    if(l==r)
    {
        tr[rt].val=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
int qry1(int rt,int l,int r)
{
    if(l<=tr[rt].l&&tr[rt].r<=r)
    {
        return tr[rt].val;
    }
    int mid=(tr[rt].l+tr[rt].r)>>1;
    int res=-inf;
    if(l<=mid) res=max(res,qry1(rt<<1,l,r));
    if(r>mid) res=max(res,qry1(rt<<1|1,l,r));
    return res;
}
pair<int,int> qry2(int rt,int l,int r,int val)
{
    if(tr[rt].l==tr[rt].r)
    {
        return {tr[rt].val,tr[rt].l};
    }
    int mid=(tr[rt].l+tr[rt].r)>>1;
    if(l<=tr[rt].l&&tr[rt].r<=r)
    {
        if(tr[rt<<1].val>=val) return qry2(rt<<1,l,r,val);
        else return qry2(rt<<1|1,l,r,val);
    }
    if(l<=mid)
    {
        pair<int,int> p=qry2(rt<<1,l,r,val);
        if(p.fi>=val) return p;
    }
    if(r>mid) return qry2(rt<<1|1,l,r,val);
}
stack<int> st;
signed main()
{
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	for(int i=n;i>=1;i--)
	{
	    while(!st.empty()&&st.top()<a[i]) st.pop();
	    st.push(a[i]);
	    ans[i]=st.size();
    }
	while(q--)
    {
        int l,r;
        cin>>l>>r;
        if(r==n)
        {
            cout<<0<<endl;
            continue;
        }
        int maxn=qry1(1,l,r);
        if(a[l]==maxn) maxn=qry1(1,l+1,r);
        if(qry1(1,r+1,n)<maxn)
        {
            cout<<0<<endl;
            continue;
        }
        cout<<ans[qry2(1,r+1,n,maxn).se]<<endl;
    }
    return 0;
}
```

---

## 作者：Down_syndrome (赞：2)

## 题意

有 $n$ 座高楼，第 $i$ 座楼的高度为 $h_i$。从第 $i$ 座楼能看到第 $j$ 座楼当且仅当不存在 $i<k<j$ 使得 $h_k>h_j$。给出 $q$ 个询问，每次给出 $l$ 和 $r$，询问第 $r+1$ 到第 $n$ 座楼中有多少座能被 $l$ 到 $r$ 中的所有楼都看到。

## 思路

来一个不需要动脑子的做法。

令 $lst_i$ 表示最大的 $j$ 满足 $j<i$ 且 $h_j>h_i$，不存在就为 $0$。显然，当且仅当 $[lst_i,i)$ 中的楼能看到 $i$。

求 $lst$ 就是单调栈模板，这里不细讲。

如果一座楼 $i(i>r)$ 能被 $l$ 到 $r$ 中所有的楼都看见，那么可知 $lst_i\le l$。也就是说，一次询问等价于求 $i\in(r,n]$ 中有多少 $lst_i\le l$。诶！直接暴力主席树即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,q,l,r,top,idx,a[N],s[N],lst[N],root[N];
struct node{
	int lc,rc,sum;
}t[N<<5];
void build(int &k,int l,int r){
	k=++idx;
	if(l==r) return;
	int mid=l+r>>1;
	build(t[k].lc,l,mid);
	build(t[k].rc,mid+1,r);
}
void modify(int &k,int last,int l,int r,int x){
	if(!k) k=++idx;
	t[k].sum=t[last].sum+1;
	if(l==r){
		t[k].sum=t[last].sum+1;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid){
		t[k].rc=t[last].rc;
		modify(t[k].lc,t[last].lc,l,mid,x);
	}
	else{
		t[k].lc=t[last].lc;
		modify(t[k].rc,t[last].rc,mid+1,r,x);
	}
}
int query(int k,int l,int r,int ql,int qr){
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return t[k].sum;
	int mid=l+r>>1;
	return query(t[k].lc,l,mid,ql,qr)+query(t[k].rc,mid+1,r,ql,qr);
}
signed main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		while(top&&a[s[top]]<=a[i]) top--;
		lst[i]=s[top];
		s[++top]=i;
	}
	build(root[n+1],0,n);
	for(int i=n;i>=1;i--) modify(root[i],root[i+1],0,n,lst[i]);
	while(q--){
		scanf("%d%d",&l,&r);
		printf("%d\n",query(root[r+1],0,n,0,l));
	}
	return 0;
}
```

---

## 作者：Ivan422 (赞：2)

发现这题是找右边能看到的个数，$i$ 能看到 $j$ 的标准是 $j$ 是 $i$ 到 $j$ 中最大值，是一个非常模版的单调栈，忘记的可以去模版题复习一下。

我们在处理单调栈的时候，先从后往前找，就可以处理出当前可以被看到的高楼。我们该如何处理答案呢？用一个树状数组来处理栈内元素，可以快速查询 $n$ 到 $i+1$ 区间内能看到的元素数量，把查询离线下来，用 $ans$ 数组统计答案。离线的时候注意一个左端点可能有多个右端点要求解，所以用 `vector` 存，比如 $i$ 号询问，就用 `qs[l].push_back({r,i})` 来按左端点存储，每到一个点就遍历下 `qs[i]`，可以求解，再在单调栈的基础上加栈元素的树状数组即可。

代码：[链接](https://atcoder.jp/contests/abc379/submissions/59634578)，还是很模版的题吧。

---

## 作者：gyyyyx (赞：1)

对于建筑 $i,j$，且 $i<j$，若 $j$ 能被 $i$ 看到，那么 $j$ 一定能被 $[i,j)$ 内的所有建筑看到。

那么询问 $l,r$ 的答案即为：能被 $l$ 看到且在 $r$ 右边的建筑数量。

我们发现答案建筑的高度一定是单调不降的。

那么我们可以预处理出 $nxt,len$ 数组，分别代表比当前建筑高且在当前建筑右边的第一个建筑的位置和以当前位置为开头的单调不降子序列长度最大值。

可以 $O(n)$ 解决：

```cpp
len[n]=1;
for(int i(n-1);i;--i){
  nxt[i]=i+1;
  while(nxt[i]&&h[nxt[i]]<h[i]) nxt[i]=nxt[nxt[i]];
  len[i]=len[nxt[i]]+1;
}
```

这相当于是一个单调栈，所以是 $O(n)$ 的。

对于询问 $l,r$，我们需要求出比 $(l,r]$ 中所有建筑都高，且在 $r$ 右侧的第一个建筑，这个建筑的 $len$ 值即为答案。

二分或者其它方法都可以 $O(q\log n)$ 解决，这里提供另一种方式。

其实我们可以将 $(l,r]$ 中最高的建筑也加进答案的单调不降子序列里。

这样我们的答案就是 $(l,r]$ 中最高的建筑的 $len$ 值减一。

我们只需要找到 $(l,r]$ 中 $len$ 值的最小值，其所代表的位置必定是 $(l,r]$ 中最高的建筑，可以用反证法证明。

那么我们只需要求静态区间最值就行了。

用 st 表解决，最终时间复杂度 $O(n\log n+q)$。

代码：

```
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,q,h[N],nxt[N];
int lg[N],st[N][18];
inline int Query(int l,int r){
	int k(lg[r-l+1]);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i(1);i<=n;++i) scanf("%d",&h[i]);
	st[n][0]=1;
	for(int i(n-1);i;--i){
		nxt[i]=i+1;
		while(nxt[i]&&h[nxt[i]]<h[i]) nxt[i]=nxt[nxt[i]];
		st[i][0]=st[nxt[i]][0]+1;
	}
	for(int i(2);i<=n;++i) lg[i]=lg[i>>1]+1;
	for(int j(1);j<=lg[n];++j)
		for(int i(1);i+(1<<j)-1<=n;++i)
			st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
	while(q--){
		int l,r;scanf("%d%d",&l,&r);
		printf("%d\n",Query(l+1,r)-1);
	}
	return 0;
}
```

---

## 作者：aCssen (赞：1)

### Solution

找到每个数左边第一个大于它的数，记为 $L_i$，这一步是单调栈的基础应用。

那么答案就是 $\sum_{i=r+1}^n[L_i \le l]$，原因很简单，首先建筑物要在 $[l,r]$ 右边，然后限制就只有 $l$，因为 $l$ 能看到的 $r$ 都能看到。为了让 $l$ 看到某个建筑物 $i$，那么 $(l,i)$ 中就不能有数比 $h_i$ 大，也就是 $i$ 左边第一个大于 $i$ 的数必须不超过 $l$。

那么离线，把询问挂在右端点上，倒着枚举 $r$，用树状数组维护 $L_i$ 这一维的限制，查询就是前缀和即可。

### Code
```cpp
#define lowbit(x) x&(-x)
const int maxn=2e5+5;
int t[maxn],a[maxn],ans[maxn],L[maxn],s[maxn],n;
vector<pair<int,int> >v[maxn];
void add(int x){
	for(;x<=n;x+=lowbit(x)) t[x]++;
}
int query(int x){
	int ans=0;
	for(;x;x-=lowbit(x)) ans+=t[x];
	return ans;
}
void Yorushika(){
	n=read();int Q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1,top=0;i<=n;i++){
		while(top&&a[s[top]]<=a[i]) top--;
		L[i]=top?s[top]:1;
		s[++top]=i;
	}
	for(int i=1;i<=Q;i++){
		int l=read(),r=read();
		v[r].push_back({l,i});
	}
	for(int i=n;i>=1;i--){
		for(auto now:v[i])
			ans[now.second]=query(now.first);
		add(L[i]);
	}
	for(int i=1;i<=Q;i++) Write(ans[i]);
}
```

---

## 作者：Union_Find (赞：1)

好简单的 F 题。

题目很好理解，我们转换一下题意，因为 $l_i \le r_i$，所以 $l_i$ 和 $r_i$ 都可以看到的 $j$ 其实只要要求 $l_i$ 可以看到并且在 $r_i$ 右边。

那就很简单了，我们把问题离线下来，将同一个 $l_i$ 的询问存入 vector 中，每次只要查询在 $r_i$ 右边的可以被 $l_i$ 看见的，就可以从后往前枚举，用单调栈维护可以看见 $j$，并且在单调栈上二分，求可以找出编号比 $r_i$ 大的数量了。可以二分是因为用的是单调栈。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, m, h[N], nr[N], p, ans[N], st[N], tp;
vector <ll> q[N];
il ll ask(ll t){
	ll l = 1, r = tp + 1, ans = -1;
	while (l <= r){
		ll mid = (l + r) >> 1;
		if (t >= st[mid]) r = mid - 1, ans = mid;
		else l = mid + 1;
	}return ans;
}
int main(){
	n = rd(), m = rd();
	for (int i = 1; i <= n; i++) h[i] = rd();
	for (int i = 1; i <= m; i++) p = rd(), nr[i] = rd(), q[p].push_back(i);
	for (int i = n; i >= 1; i--){
		for (int u : q[i]) ans[u] = ask(nr[u]) - 1;
		while (tp && h[st[tp]] < h[i]) tp--;st[++tp] = i;
	}for (int i = 1; i <= m; i++) printf ("%lld\n", ans[i]);
	return 0;
}

```

---

## 作者：xixisuper (赞：1)

# AT_abc379_f [ABC379F] Buildings 2 题解

好玩题。

赛后发现有 $O(n\log n+q)$ 的更优做法，但是我赛时没想到，只能写个不需要啥注意力的 $O((n+q)\log n)$ 的解法膜拜大佬。

## 思路

我们考虑对于第 $i$ 栋楼来说哪些楼是一定能被看见的：

- 第 $i+1$ 栋楼一定能被看见。
- 如果第 $j$ 栋楼能被看见，则下一个被看见的楼一定是第 $j$ 栋楼往后第一栋高度大于等于 $H_j$ 的楼。

我们记**第 $j$ 栋楼往后第一栋高度大于等于 $H_j$ 的楼是第 $nxt_j$ 栋楼**，显然所有的 $nxt_j$ 是可以跑一遍单调栈求出来的。

于是我们可以考虑建个模，在 $j$ 与 $nxt_j$ 之间连一条边，特别的，如果不存在 $nxt_j$ 则默认 $nxt_j=0$。我们会发现最终我们会建成一棵**以 $0$ 号节点为根节点的一棵树**，如果我们认为根节点的深度为 $0$ 的话，则**第 $i$ 栋楼能看见的楼的个数等价于 $i+1$ 号节点在这棵树上的深度**。

现在来考虑同时能被 $l,r$ 看到的楼有哪些，显然就是**在树上同时为 $l+1$ 号节点和 $r+1$ 号节点的祖先的那些节点**，所以我们直接求出树上节点 $l+1$ 和 $r+1$ 的最近公共祖先，然后输出其深度即可。

我们只需要跑一遍单调栈求出 $nxt$，再倍增优化求最近公共祖先即可，时间复杂度为 $O((n+q)
\log n)$。

## 代码

场上的代码。

```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#define ll long long
using namespace std;
const ll N=2e5+10;
ll fa[N][20],n,q,H[N],stk[N],top;
vector<ll> e[N];
ll dep[N];
void dfs(ll u,ll f){
	if(u!=0){
		dep[u]=dep[f]+1;
		for(ll i=1;i<20;i++){
			fa[u][i]=fa[fa[u][i-1]][i-1];
		}
	}
	ll lz=e[u].size();
	for(ll i=0;i<lz;i++){
		ll v=e[u][i];
		dfs(v,u);
	} 
}
ll lca(ll u,ll v){
	if(dep[u]<dep[v]) swap(u,v);
	for(ll i=19;i>=0;i--){
		if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	}
	if(u==v) return u;
	for(ll i=19;i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(ll i=1;i<=n;i++) cin>>H[i];
	for(ll i=1;i<=n;i++){
		while(top&&H[stk[top-1]]<=H[i]){
			fa[stk[top-1]][0]=i;
			e[i].push_back(stk[top-1]);
			top--;
		}
		stk[top]=i;
		top++;
	}
	for(ll i=1;i<=n;i++) if(fa[i][0]==0) e[0].push_back(i);
	dfs(0,0);
	while(q--){
		ll l,r;
		cin>>l>>r;
		ll u=l+1,v=r+1;
		if(r==n){
			cout<<"0\n";
			continue;
		}
		cout<<dep[lca(u,v)]<<"\n";
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

设楼 $i$ 左边最右的比它高的楼为 $p_i$，容易用单调栈求出。则楼 $i$ 能看见 $[p_i,i)$。

一个询问 $(l_i,r_i)$ 的答案为 $\sum\limits_{j=r_i+1}^N[p_j\le l_i]$。把询问按 $r_i$ 扫描线，把 $p_j$ 丢树状数组里统计即可。

```cpp
int n,m,tp,a[N],L[N],st[N],ans[N]; pii q[N]; vi v[N];
struct BIT {
	int c[N];
	il int lbt(int id) {return id&-id;}
	il void upd(int id) {for(;id<=n+1;id+=lbt(id)) c[id]++;}
	il int qry(int id) {int r=0; for(;id;id-=lbt(id)) r+=c[id]; return r;}
} bit;
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) {
		a[i]=rd();
		while(tp&&a[st[tp]]<a[i]) tp--;
		L[i]=st[tp],st[++tp]=i;
	}
	for(int i=1;i<=m;i++) q[i]={rd(),rd()},v[q[i].sec].pb(i);
	for(int i=n;i;i--) {
		for(int x:v[i]) ans[x]=bit.qry(q[x].fir+1);
		bit.upd(L[i]+1);
	}
	for(int i=1;i<=m;i++) wr(ans[i],"\n");
}
```

---

## 作者：lwwwb_555 (赞：0)

不难发现，对于每个询问的区间都有一个限制，而我们要求的就是这个区间右端点的右侧的一个第一个数大于这个限制的递增序列的长度。

我们先考虑如果我们有了这个限制之后该怎么做。我们可以现将询问离线，然后倒着扫，扫到一个区间 的右端点就检查第一个大于这个区间的限制的值在哪里，然后直接统计在这个点上的答案。那么我们又怎么维护点的答案了？我们也可以找到右边第一个大于它的值，那么这个值的答案就是右边那个比他大的点的答案加一。而维护一个点右边比它大的第一个点的位置明显可以用单调栈维护。

我们再来想如何得到每个区间的限制。很显然，这就是区间 $l+1\sim r$ 中的最大值。为什么是 $l+1$ 呢？因为 $l$ 并不可能挡到区间内的任意的点，所以不记录。

赛场上的代码有些地方写的比较麻烦，比如这题应该可以完全不用线段树的，可以在理解了思路以后自己尝试自己写一下而不要看我的代码。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[200050],st[200050][20];
int read(){
    int res=0,f=1;
    char c=getchar();
    while(!isdigit(c)){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(isdigit(c)){
        res=(res<<3)+(res<<1)+c-'0';
        c=getchar();
    }
    return res*f;
}
struct node{
    int ll,rr;
    long long w,ww;
};
struct tree{
    node tt[800050];
    void build(int p,int l,int r){
        tt[p]={l,r,0,0};
        if(l==r) return;
        int mid=(l+r)>>1;
        build(p*2,l,mid),build(p*2+1,mid+1,r);
    }
    void update(int p,int l,int k){
        if(tt[p].ll==tt[p].rr){
            tt[p].w+=k,tt[p].ww+=k;
            return;
        }
        int mid=(tt[p].ll+tt[p].rr)>>1;
        if(l<=mid) update(p*2,l,k);
        else update(p*2+1,l,k);
        tt[p].w=tt[p*2].w+tt[p*2+1].w;
        tt[p].ww=max(tt[p*2].ww,tt[p*2+1].ww);
    }
    int query(int p,int l,int r){
        if(tt[p].ll>=l && tt[p].rr<=r) return tt[p].w;
        int mid=(tt[p].ll+tt[p].rr)>>1;
        int o=0;
        if(l<=mid) o+=query(p*2,l,r);
        if(r>mid) o+=query(p*2+1,l,r);
        return o;
    }
    int query2(int p,int l,int r){
        if(tt[p].ll>=l && tt[p].rr<=r) return tt[p].ww;
        int mid=(tt[p].ll+tt[p].rr)>>1;
        int o=0;
        if(l<=mid) o=max(o,query2(p*2,l,r));
        if(r>mid) o=max(o,query2(p*2+1,l,r));
        return o;
    }
}tt1,tt2;
struct nnode{
    int l,r,ans,maxx;
}qu[200050];
vector<int> e[200050],ee[200050],eee[200050];
int stk[200050],tot,r[200050],pos[200050];
int main(){
    n=read(),q=read();
    for(int i=1;i<=n;i++) a[i]=read(),pos[a[i]]=i,st[i][0]=a[i];
    for(int i=1;i<=n;i++){
        while(tot && a[i]>a[stk[tot]]) eee[i].push_back(stk[tot]),r[stk[tot]]=i,tot--;
        stk[++tot]=i;
    }
    for(int i=1;i<=q;i++){
        qu[i]={read(),read(),0,0};
        e[qu[i].r+1].push_back(i);
        ee[qu[i].r].push_back(i);
    }
    for(int i=1;i<=19;i++){
        for(int j=1;j+(1<<i)-1<=n;j++) st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
    }
    tt1.build(1,1,n),tt2.build(1,1,n);
    for(int i=1;i<=n;i++) tt1.update(1,i,a[r[i]]);
    for(int i=n;i>=1;i--){
        for(auto k:ee[i]) qu[k].maxx=tt1.query2(1,qu[k].l,i);
        for(auto k:eee[i]) tt1.update(1,k,-a[i]);
    }
    for(int i=1;i<=q;i++){
        if(qu[i].l==qu[i].r) continue;
        int k=__lg(qu[i].r-qu[i].l);
        qu[i].maxx=max(qu[i].maxx,max(st[qu[i].l+1][k],st[qu[i].r-(1<<k)+1][k]));
    }
    for(int i=n;i>=1;i--){
        int u=0;
        if(r[i]) u=tt2.query(1,a[r[i]],a[r[i]]);
        tt2.update(1,a[i],u+1);
        for(auto k:e[i]){
            if(qu[k].maxx==0) qu[k].ans=tt2.query(1,a[i],a[i]);
            else qu[k].ans=tt2.query(1,a[r[pos[qu[k].maxx]]],a[r[pos[qu[k].maxx]]]);
        }
    }
    for(int i=1;i<=q;i++) printf("%d\n",qu[i].ans);
    return 0;
}
```

---

## 作者：zengziqvan (赞：0)

提供一个好想好写的做法。

注意到如果在 $j$ 之前出现了一个 $i$ 使得 $h_i>h_j$，则 $\forall 1\le k<i$，$j$ 不可能被 $k$ 看到。

所以先将询问离线。

再倒序扫描每个 $i$ 位置，枚举以 $i$ 为右端点的询问。

假设已经求完了 $i+1$，那么 $i+2\sim n$ 中所有比 $i+1$ 矮的楼，$1\sim i$ 中的任何一个都不会看到。

所以动态维护一棵权值线段树，节点 $[l,r]$ 表示扫到现在值域为 $[l,r]$ 的楼的个数的和。更新完 $i$ 的答案后将所有值域为 $1\sim h_i-1$ 的楼的个数和全部赋值为 $0$。然后将 $h_i$ 位置赋值成 $1$。

对于一个询问 $[l,r]$，扫到 $r$ 时权值线段树中所有值为 $1$ 的节点一定能够被 $r$ 看到。

现在考虑 $l$，注意到如果当前权值线段树中某个点值为 $1$ 且高度要比区间 $[l+1,r]$ 中最高的楼要矮，则 $l$ 必定看不到该点。

所以答案就是权值线段树中值域大于区间 $[l+1,r]$ 中最大值的所有值之和。

时间复杂度 $O(n\log n)$。

[code](https://atcoder.jp/contests/abc379/submissions/59618151)

---

## 作者：banned_gutongxing (赞：0)

### 思路

**注意：**$i$ 能看到 $j$ 并不代表 $h_i<h_j$。

我们先计算 $minn_i$ 代表 $i$ 后面能看见几栋楼（并且 $h_i<h_j$）。这里很明显使用单调栈。

所以能看见的建筑就是必须要比 $\displaystyle\max_{p=l_i-1}^{r_i}h_p$ 还要大。

就是求 $minn_{\displaystyle\text{maxpos}_{p=l_i-1}^{r_i}h_p}$。这里使用线段树来实现。

### 代码
```cpp
// Problem: F - Buildings 2
// Contest: AtCoder - Toyota Programming Contest 2024#11（AtCoder Beginner Contest 379）
// URL: https://atcoder.jp/contests/abc379/tasks/abc379_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');}
	}
	void write(int x,char y){write(x);write(y);}
	#ifndef int
	void read(long long &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void write(long long x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');}
	}
	void write(long long x,char y){write(x);write(y);}
	#endif
	deque<pair<int,int>> st;
	const int MAXN = 2e5+10;
	int n,m,a[MAXN],minn[MAXN];
	struct node{
		int l,r;
		pair<int,int> s;
	}tree[MAXN<<3];
	void pushup(int k){
		tree[k].s = min(tree[k*2].s,tree[k*2+1].s);
	}
	void build(int k,int l,int r){
		tree[k].l = l;
		tree[k].r = r;
		if(l==r) return tree[k].s={minn[l],l},void();
		int mid = (l+r)>>1;
		return build(k*2,l,mid),build(k*2+1,mid+1,r),pushup(k);
	}
	pair<int,int> ask(int k,int l,int r){
		if(tree[k].r<l||tree[k].l>r) return {0x3f3f3f3f,0};
		if(tree[k].r<=r&&tree[k].l>=l){
			return tree[k].s;
		}
		return min(ask(k*2,l,r),ask(k*2+1,l,r));
	}
	signed main(){
		read(n);read(m);
		for(int i = 1;i<=n;i++){
			read(a[i]);
		}
		for(int i = n;i>=1;i--){
			while(!st.empty()&&st.back().second<a[i]) st.pop_back();
			
			minn[i] = st.size();st.push_back({i,a[i]});
		}
		build(1,1,n);
		for(int i = 1;i<=m;i++){
			int l,r;
			read(l);read(r);
			write(minn[ask(1,l+1,r).second],endl);
		}
		return 0;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
//	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

## 作者：aimcf (赞：0)

### F

首先维护一个 st 表在 $O(n\log n)$ 预处理，$O(1)$ 查询的时间复杂度内求出任意区间的最大值。然后将询问离线，按照右端点从大到小处理。随后维护一个值从右往左单调递减的单调栈，对于每一次查询操作，计算出其最大值 $w$，然后直接在单调栈上二分即可。

总时间复杂度为 $O(n\log n)$，可以将 st 表替换为 $\pm1$ rmq，二分按照右端点单独替换为双指针，做到 $O(n)$。

```cpp
int f[N][20], lg[N], a[N], res[N];
int query(int l, int r) {
    int len = lg[r - l + 1];
    return max(f[l][len], f[r - (1ll << len) + 1][len]);
}
struct lng {
    int l, r, id;
    bool operator<(const lng &x) const {
        return r > x.r || r == x.r && l > x.l;
    }
} q[N];
vector<pair<int, int>> scc[N];
int arr[N], idx;
void run() {
    int n = read(), m = read();
    lg[0] = -1;
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        f[i][0] = a[i];
        lg[i] = lg[i / 2] + 1;
    }
    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j <= n - (1ll << i) + 1; ++j) {
            f[j][i] = max(f[j + (1ll << (i - 1))][i - 1], f[j][i - 1]);
        }
    }
    for (int i = 1; i <= m; ++i) {
        q[i].l = read(), q[i].r = read();
        q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    for (int i = 1; i <= m; ++i) {
        scc[q[i].r].eb(q[i].l, q[i].id);
    }
    for (int i = n; i; --i) {
        for (auto &[j, id] : scc[i]) {
            int key = query(j + 1, i);
            int l = 1, r = idx, best = 0;
            while (l <= r) {
                int mid = l + r >> 1;
                if (a[arr[mid]] > key) {
                    best = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            // cout << "query " << j << ' ' << i << ' ' << id << ' ' << best << ' ' << arr[1] << ' ' << arr[2] << ' ' << key << '\n';
            res[id] = best;
        }
        while (idx && a[arr[idx]] < a[i]) {
            --idx;
        }
        arr[++idx] = i;
    }
    for (int i = 1; i <= m; ++i) {
        cout << res[i] << '\n';
    }
}

---

## 作者：冷却心 (赞：0)

考虑对于每次询问，对于 $a_r$ 来说，他能看到的数在序列上一定是在 $r$ 之后的一个不降子序列，然后对于 $a_l$ 来说，记 $m=\max_{i=l+1}^r a_i$，则能被 $l,r$ 同时看到的数一定是那个不降子序列（满足能被 $r$ 看到）中所有大于 $m$ 的数（满足能被 $l$ 看到）。每次求 $m$ 可以写个 st 表 RMQ，而因为后面的序列已经是不降的，所以询问大于 $m$ 的数可以直接 `lower_bound` 查询，问题就是如何维护 $r$ 之后的单调不降序列。

如果每次询问都跑单调栈重构这个子序列是 $O(n)$ 的，所以可以离线下来，开一个 `vector` 把询问挂到右端点上，然后枚举右端点从 $n$ 往 $1$ 倒着处理，跑单调栈维护不降子序列，然后对 $l$ 查询，每个 $r$ 做完了把它塞到单调栈里。然后就做完了。

st 表的复杂度是 $O(n\log n+Q)$，单调栈 $O(n)$，二分查找 $O(Q\log n)$，所以总复杂度是 $O((n+Q)\log n)$。

代码就挂在这里。 [https://atcoder.jp/contests/abc379/submissions/59651515](https://atcoder.jp/contests/abc379/submissions/59651515)。

---

## 作者：Genius_Star (赞：0)

### 思路：


考虑令 $pre_i$ 表示在 $i$ 左侧第一个高度大于 $i$ 的楼房编号。

那么对于在区间 $[pre_i, i)$ 的楼房是都可以看到 $i$ 的。

那么对于一个询问 $[l,r]$，要保证 $[l,r]$ 都可以看到 $i$，则需要满足 $pre_i \le l, i > r$。

这是一个**类二维数点问题**，因为只是询问一段后缀 $pre_i \le l$ 的数量，则我们可以将询问离线，使用树状数组维护 $pre_i$ 即可。

时间复杂度为 $O((n + q) \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, q, l, r;
int a[N], pre[N], ans[N];
stack<int> T;
vector<pair<int, int>> Q[N];
namespace Tree{
	int s = 0;
	int a[N];
	inline void add(int x){
		if(!x){
			++s;
			return ;
		}
		for(int i = x; i <= n; i += lowbit(i))
		  ++a[i];
	}
	inline int query(int x){
		int sum = s;
		for(int i = x; i; i -= lowbit(i))
		  sum += a[i];
		return sum;
	}
};
bool End;
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	for(int i = n; i >= 1; --i){
		while(!T.empty() && a[i] > a[T.top()]){
			pre[T.top()] = i;
			T.pop();
		}
		T.push(i);
	}
	for(int i = 1; i <= q; ++i){
		l = read(), r = read();
		Q[r + 1].push_back({l, i});
	}
	for(int i = n; i >= 1; --i){
		Tree::add(pre[i]);
		for(auto t : Q[i])
		  ans[t.se] = Tree::query(t.fi);
	}
	for(int i = 1; i <= q; ++i){
		write(ans[i]);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：orson111 (赞：0)

## 前言
第一次这么早！

[原题地址](https://atcoder.jp/contests/abc379/tasks/abc379_f)

前置芝士：树状数组、长度可变数组、单调栈。

## 正片开始
分析一下题，不难看出只要 $l$ 能看见某个 $x>r$，则 $r$ 一定能看见。

所以我们首先单调栈预处理出对于每个可能的右端点 $i$，最左边的能看到他的点，令其为 $l_i$。

然后我们离线处理一下所有询问，定义 $\texttt{query}$ 类型存放询问，放在右端点。

最后我们从右到左扫一遍，扫到一个右端点看所有询问，用树状数组维护目前有多少个右端点的 $l$ 小于等于这个询问的 $l$。

## 上代码！
**请勿复制**
```cpp
#include<bits/stdc++.h>
#include<atcoder/al1>
using namespace std;
using namespace atcoder;
typedef long long ll;
const ll N=2e5+9;
ll n,h[N],l[N],q,stk[N],top,ans[N];
struct query{ll l,id;};
vector<query> qq[N];
ll bit[N];//树状数组
ll lowbit(ll x){return x&(-x);}
void upd(ll x){for(ll i=x;i<=n;i+=lowbit(i)) bit[i]++;}
ll sum(ll x){ll ss=0;for(ll i=x;i;i-=lowbit(i)) ss+=bit[i];return ss;}
void s0lve(){
    cin>>n>>q;
    for(ll i=1;i<=n;i++){
        cin>>h[i];
        while(top&&h[stk[top]]<=h[i]) top--;//单调栈预处理l
        l[i]=(top?stk[top]:1);
        stk[++top]=i;
    }
    for(ll i=1,lll,rr;i<=q;i++)
        cin>>lll>>rr,qq[rr].push_back((query){lll,i});//离线
    for(ll i=n;i>=1;i--){
        for(ll j=0;j<qq[i].size();j++)
            ans[qq[i][j].id]=sum(qq[i][j].l);
        upd(l[i]);
    }
    for(ll i=1;i<=q;i++) cout<<ans[i]<<endl;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    l1 T=1;
    //cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 前置知识
线段树（无修改，区间求最大值），二分答案，分块算法。
# 题解
## 一个很明显的性质
答案是对于所有大于点 $r$ 的点 $i$，满足最后一个大于 $h_i$ 的点在 $l$ 的左边，包括 $l$ 的点的个数。

## 求出最后一个大于 $h_i$ 的点
二分这个点的位置，判断 $mid$ 到 $i-1$ 之间是否有大于 $h_i$ 的点，用线段树求出 $mid$ 到 $i-1$ 的区间最大值，判断是否大于 $h_i$ 即可。
## 分块求答案
将上述值设为 $f_i$，按照 $f_i$ 从小到大排序。

分成 $\sqrt n$ 块，每块求出关于 $i$ 的前缀和。求解答案时，首先确定范围：最后一个小于等于 $l$ 的 $f_i$。

接下来，对成块的用前缀和 $s_n-s_{r}$，不成块的直接求。
## 时间复杂度
是 $O(n \log(n) \log(n) +n \sqrt n)$，常数有点大，但能卡过，卡到 $1.97$ 秒。
# 代码
```
//c++ 20/23：
#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int n,q,a[200010],l,r,tr[2000010],p[200010],S[500][200010],le;
struct g{
	int k,id;
	bool operator<(const g&t){return k<t.k;}
}s[200010];
void build(int i,int l,int r){
	if(l==r){tr[i]=a[l];return;}
	int m=(l+r)>>1;
	build(i<<1,l,m),build((i<<1)|1,m+1,r),tr[i]=max(tr[i<<1],tr[(i<<1)|1]);
}
int query(int i,int l,int r,int kl,int kr){
	if(kl>r||kr<l)return 0;
	if(kl<=l&&kr>=r)return tr[i];
	int m=(l+r)>>1;
	return max(query(i<<1,l,m,kl,kr),query((i<<1)|1,m+1,r,kl,kr));
}
int get(int i){return (i+le-1)/le;}
int main(){
	scanf("%d%d",&n,&q),le=sqrt(n);
	for(int w=1;w<=n;w++)scanf("%d",&a[w]);
	build(1,1,n);
	for(int w=1;w<=n;w++){
		int l=0,r=w-1;
		while(l<r){
			int m=(l+r+1)>>1;
			if(query(1,1,n,m,w-1)>a[w])l=m;
			else r=m-1;
		}
		s[w]={l,w};
	}
	sort(s+1,s+n+1);
	for(int w=1;w<=n;w++)p[w]=s[w].k,S[get(w)][s[w].id]++;
	for(int w=1;w<=n;w+=le)for(int x=1,y=get(w);x<=n;x++)S[y][x]+=S[y][x-1];
	while(q--){
		scanf("%d%d",&l,&r);
		int k=upper_bound(p+1,p+n+1,l)-p,ans=0,g=get(k);k--;
		for(int w=1;w<g;w++)ans+=S[w][n]-S[w][r];
		for(int w=(g-1)*le+1;w<=k;w++)if(s[w].id>r)ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

不难发现 $j$ 能否被 $i$ 看到与 $h_i$ 无关，因此如果 $l$ 能看到某个房子，那么 $r$ 一定也能看到，题目询问转化为有多少 $r$ 右侧的房子能被 $l$ 看到。

由于高的房子会挡住矮的，所以这些能被看到的房子的高度单调递增，而由于你不能忽视其中的某些房子不去看它们，所以这些房子便是一段最长上升子序列，可以使用单调栈加 dp 解决。

为了让 $l$ 看到这些房子，它们之中最矮的（也就是最前面的）必须比 $l\sim r$ 中最高的房子更高，可以二分出它的位置，使用前面求得的 dp 值就可以得出答案。时间复杂度与维护区间最大值的数据结构有关。这里使用了线段树，复杂度是 $O(n \log ^2 n)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int mx[N<<2],a[N],f[N],pos[N];
void build(int s,int t,int p)
{
	if(s==t)
	{
		mx[p]=a[s];
		return;
	}
	int m=s+t>>1;
	build(s,m,p<<1);
	build(m+1,t,p<<1|1);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
int qry(int l,int r,int s,int t,int p)
{
	if(l>r) return -1e9;
	if(l<=s&&t<=r) return mx[p];
	int m=s+t>>1;
	int ans=0;
	if(l<=m) ans=qry(l,r,s,m,p<<1);
	if(r>m) ans=max(ans,qry(l,r,m+1,t,p<<1|1));
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	stack<int> st;
	for(int i=1;i<=n;i++)
	{
		while(st.size()&&a[st.top()]<a[i]) pos[st.top()]=i,st.pop();
		st.push(i);
	}
	for(int i=n;i;i--)
	{
		if(!pos[i]) f[i]=1;
		else f[i]=f[pos[i]]+1;
	}
	build(1,n,1);
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		int nowmx=qry(l+1,r,1,n,1);
		if(qry(r+1,n,1,n,1)<nowmx)
		{
			cout<<0<<'\n';
			continue;
		}
		int ll=r+1,rr=n,mid,res;
		while(ll<=rr)
		{
			mid=ll+rr>>1;
			if(qry(r+1,mid,1,n,1)>=nowmx) res=mid,rr=mid-1;
			else ll=mid+1;
		}
		cout<<f[res]<<'\n';
	}
}

---

