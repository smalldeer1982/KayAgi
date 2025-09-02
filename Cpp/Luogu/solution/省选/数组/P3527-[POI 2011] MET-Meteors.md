# [POI 2011] MET-Meteors

## 题目描述

Byteotian Interstellar Union 

有 $n$ 个成员国。现在它发现了一颗新的星球，这颗星球的轨道被分为 $m$ 份（第 $m$ 份和第 $1$ 份相邻），第 $i$ 份上有第 $o_i$ 个国家的太空站。

这个星球经常会下陨石雨。BIU 已经预测了接下来 $k$ 场陨石雨的情况。

BIU 的第 $i$ 个成员国希望能够收集 $p_i$ 单位的陨石样本。你的任务是判断对于每个国家，它需要在第几次陨石雨之后，才能收集足够的陨石。

## 说明/提示

$1\le n,m,k\le 3\cdot10^5$；

$1\le p_i,a_i\le 10^9$；

## 样例 #1

### 输入

```
3 5
1 3 2 1 3
10 5 7
3
4 2 4
1 3 1
3 5 2```

### 输出

```
3
NIE
1```

# 题解

## 作者：jiangly (赞：93)

#### 题意

给出一个环形序列，被分为 $m$ 段。有 $n$ 个国家，序列的第 $i$ 段属于国家 $o_i$。接下来有 $k$ 次事件，每次给环形序列上的一个区间加上一个正整数。每个国家有一个期望 $p_i$，求出每个国家在序列上所有位置的值的和到达 $p_i$ 的最早时间（或报告无法达到）。

#### 限制

$1\le n,m,k\le 3\cdot10^5$。

#### 题解

下面认为 $n,m,k$ 同阶，时间复杂度均以 $n$ 表示。

忽略环的条件，跨越首尾的事件可以拆成两个。

考虑二分每个国家的时间，每次二分后执行二分位置之前的所有事件，判断是否达到期望。然而这样的时间复杂度太高。但是我们可以将所有国家一起二分，这样每一轮只用完整地执行一次操作序列，时间复杂度 $O(n(\log n)^2)$。

用树状数组维护操作再结合一定的常数优化已经足以通过该题，但还有复杂度更优秀的做法。

我们考虑扫描序列，用线段树维护时间。对于第 $i$ 个操作 $([l_i,r_i),a_i)$，扫到 $l_i$ 时在位置 $i$ 加 $a_i$，扫到 $r_i$ 时减 $a_i$。这样直接用整体二分的方法并不能改善复杂度，但是在将线段树可持久化后把一个国家的所有位置一起在线段树上二分就能做到 $O(n\log n)$ 的时空复杂度。然而本题的空间限制很紧，这种做法并不能通过。

沿用之前整体二分和差分操作的方法，假设目前在区间 $[l_v,r_v)$ 内二分，在保持操作和序列位置有序的情况下，我们可以利用 two-pointers 在线性时间内求出所有国家在给定操作集合（即 $[l_v,\lfloor\frac{l_v+r_v}{2}\rfloor)$ 中的操作）中的权值 $\mathrm{val}_i$。如果 $\mathrm{val}_i\ge p_i$，向左递归；如果 $\mathrm{val}_i<p_i$，将 $p_i$ 减去 $\mathrm{val}_i$，向右递归。由于递归层数为 $O(\log n)$，该算法的时间复杂度为 $O(n\log n)$，空间复杂度为 $O(n)$。

#### 代码

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cctype>
constexpr int N = 300'000;
int n, m, q, qn;
int o[N], p[N], s[N], ans[N], tmp[N];
long long sum[N];
struct Query {
    int x, y, v;
    Query() {}
    Query(int x, int y, int v) : x(x), y(y), v(v) {}
    friend bool operator<(const Query &lhs, const Query &rhs) {
        return lhs.x < rhs.x;
    }
};
Query queries[3 * N], temp[3 * N];
char buf[1 << 22], *p1, *p2;
char get() {
    if (p1 == p2) {
        p1 = buf;
        p2 = buf + fread(buf, 1, sizeof(buf), stdin);
    }
    if (p1 == p2)
        return EOF;
    return *p1++;
}
int readInt() {
    int x = 0;
    char c = get();
    while (!std::isdigit(c))
        c = get();
    while (std::isdigit(c)) {
        x = 10 * x + c - '0';
        c = get();
    }
    return x;
}
void print(int x) {
    static char stk[20];
    int top = 0;
    while (x > 0) {
        stk[top++] = x % 10 + '0';
        x /= 10;
    }
    for (int i = top - 1; i >= 0; --i)
        *p2++ = stk[i];
    *p2++ = '\n';
}
void nie() {
    *p2++ = 'N';
    *p2++ = 'I';
    *p2++ = 'E';
    *p2++ = '\n';
}
void solve(int vl, int vr, int sl, int sr, int ql, int qr) {
    if (sl == sr)
        return;
    for (int i = sl; i < sr; ++i)
        sum[o[s[i]]] = 0;
    if (vr - vl == 1) {
        int qi = ql;
        long long curSum = 0;
        for (int i = sl; i < sr; ++i) {
            while (qi < qr && queries[qi].x <= s[i]) {
                curSum += queries[qi].v;
                ++qi;
            }
            if (sum[o[s[i]]] < p[o[s[i]]])
                sum[o[s[i]]] += curSum;
        }
        for (int i = sl; i < sr; ++i) {
            if (sum[o[s[i]]] >= p[o[s[i]]]) {
                ans[o[s[i]]] = vr;
            } else {
                ans[o[s[i]]] = -1;
            }
        }
        return;
    }
    int vm = (vl + vr) / 2;
    int qm = ql, nqr = qr;
    std::copy(queries + ql, queries + qr, temp + ql);
    for (int i = ql; i < qr; ++i) {
        if (temp[i].y < vm) {
            queries[qm++] = temp[i];
        } else {
            queries[--nqr] = temp[i];
        }
    }
    std::reverse(queries + qm, queries + qr);
    int qi = ql;
    long long curSum = 0;
    for (int i = sl; i < sr; ++i) {
        while (qi < qm && queries[qi].x <= s[i]) {
            curSum += queries[qi].v;
            ++qi;
        }
        if (sum[o[s[i]]] < p[o[s[i]]])
            sum[o[s[i]]] += curSum;
    }
    std::copy(s + sl, s + sr, tmp + sl);
    int sm = sl, nsr = sr;
    for (int i = sl; i < sr; ++i) {
        if (sum[o[tmp[i]]] >= p[o[tmp[i]]]) {
            s[sm++] = tmp[i];
        } else {
            s[--nsr] = tmp[i];
        }
    }
    std::reverse(s + sm, s + sr);
    for (int i = sm; i < sr; ++i) {
        if (sum[o[s[i]]] != -1) {
            p[o[s[i]]] -= sum[o[s[i]]];
            sum[o[s[i]]] = -1;
        }
    }
    solve(vl, vm, sl, sm, ql, qm);
    solve(vm, vr, sm, sr, qm, qr);
}
int main() {
    n = readInt();
    m = readInt();
    std::fill(ans, ans + n, -1);
    std::iota(s, s + m, 0);
    for (int i = 0; i < m; ++i)
        o[i] = readInt() - 1;
    for (int i = 0; i < n; ++i)
        p[i] = readInt();
    q = readInt();
    for (int i = 0; i < q; ++i) {
        int l, r, a;
        l = readInt() - 1;
        r = readInt();
        a = readInt();
        if (l < r) {
            queries[qn++] = Query(l, i, a);
            if (r != m)
                queries[qn++] = Query(r, i, -a);
        } else {
            queries[qn++] = Query(0, i, a);
            if (l != r) {
                queries[qn++] = Query(r, i, -a);
                queries[qn++] = Query(l, i, a);
            }
        }
    }
    std::sort(queries, queries + qn);
    solve(0, q, 0, m, 0, qn);
    p1 = p2 = buf;
    for (int i = 0; i < n; ++i) {
        if (ans[i] == -1) {
            nie();
        } else{
            print(ans[i]);
        }
    }
    fwrite(buf, 1, p2 - p1, stdout);
    return 0;
}
```



---

## 作者：ysy20021208 (赞：68)

​&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于这道题是整体二分的经典例题，我们先抛开整体二分，思考二分怎么做。对于一个询问，因为答案有单调性，如果$x$时刻为最小可以时刻，则比$x$小的时刻都不可以，比$x$大的时刻都可以，所以我们可以进行二分答案，并加以验证。先不说怎样验证，就单是时间复杂度就不能接受，$O(nmlog_2n)$。

​&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果一个一个进行二分时间复杂度不允许，且这些询问不是强制在线的，我们不妨整体进行二分，我们把所有询问放在一起进行二分。我们设计一个函数$solve(l,r,x,y)$，表示当前询问序列$[x,y]$的答案在当前答案$[l，r]$区间。有一个问题，就是为什么答案在答案区间$[l,r]$的所有询问会连接在一起，在询问序列的连续一段呢？这个问题放在后面，先置之不理。我们思考，怎样进行二分。

​&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;二分答案的思想是取出当前答案区间的中间值进行验证，如果比答案小，则让答案的区间的左端点为中间值加一，反之让答案的右端点为中间值。按照二分答案的思想，我们也进行中间值验证。看例题，我们思考怎么验证。

​&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于当前答案区间$[l,r]$，我们把第$[l,mid]$场流星雨全部落下，看在当前答案区间$[l,r]$所属的所有询问是否在第$[l,mid]$场流星雨下过之后已经收集足够的陨石，如果当前询问已经收集够，我们把它归为答案区间$[l,mid]$中，反之我们把它归为答案区间$[mid+1,r]$中，并且对于归为答案区间$[mid+1,r]$的询问我们需要进行修改，对于其希望要收集的陨石数要减去$[l,mid]$场流星雨的陨石总数，此处理解一下。

​&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;现在解决一下上面留下的问题，我们怎么能将答案都在$[x,y]$区间的所有询问都放在一起呢？我们对于每一次划分，都将这些询问进行拷贝，并且修改，然后重新按左右排布，这样我们就能让这些答案在同一区间的询问在一起了。 

​&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们分析一下时间复杂度：我们运用线段树的思想进行分析，我们一共有$log_2{r-l+1}$层，在这个式子中的$r$表示答案可能到达的最大值，反之$l$表示的就是答案可能到达的最小值，在本题中，我们的$r=n，l=1$，但是下方的代码最开始的传参为$r=n+1$，这表示前$n$场流星雨都不能满足这个询问，所以最后落在$n+1$的所有询问表示不能在所有$n$个流行雨中的到满足，故输出$-1$。每一层中我们运用线段树的思想，知道遍历每一层的所有流星雨，一共是线性的时间复杂度，并且每一层正正好好摊分所有$m$个询问，在每一层中我们每一个询问和流星雨都会运用树状数组，所以总的时间复杂度是$O((n+m)log_2{n}log_2{r-l+1})$。


```c++
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 300010
struct Per {int head,id;long long need;}per[N],per_[N<<1];
int n,m,k,L[N],R[N];long long A[N];int ans[N],nxt[N],to[N],idx;long long tmp[N<<1];
void add(int a,int b) {nxt[++idx]=per[a].head,to[idx]=b,per[a].head=idx;}
void change(int x,long long y) {while(x<=2*m) tmp[x]+=y,x+=x&-x;}
long long find(int x) {long long sum=0;while(x) sum+=tmp[x],x-=x&-x;return sum;}
void solve(int l,int r,int x,int y)
{
    if(l==r) {for(int i=x;i<=y;i++) ans[per[i].id]=l;return;}
    int mid=(l+r)>>1,tl=0,tr=n;
    for(int i=l;i<=mid;i++) change(L[i],A[i]),change(R[i]+1,-A[i]);
    for(int i=x;i<=y;i++)
    {
        long long tmp1=0;
        for(int j=per[i].head;j&&tmp1<=per[i].need;j=nxt[j])
            tmp1+=find(to[j]+m)+find(to[j]);
        if(tmp1>=per[i].need) per_[++tl]=per[i];
        else per_[++tr]=per[i],per_[tr].need-=tmp1;
    }
    for(int i=l;i<=mid;i++) change(L[i],-A[i]),change(R[i]+1,A[i]);
    for(int i=1;i<=tl;i++) per[x+i-1]=per_[i];
    for(int i=n+1;i<=tr;i++) per[x+tl+i-n-1]=per_[i];
    solve(l,mid,x,x+tl-1),solve(mid+1,r,y-tr+n+1,y);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a;i<=m;i++) scanf("%d",&a),add(a,i);
    for(int i=1;i<=n;i++) scanf("%lld",&per[i].need),per[i].id=i;
    scanf("%d",&k);for(int i=1;i<=k;i++) scanf("%d%d%lld",&L[i],&R[i],&A[i]);
    for(int i=1;i<=k;i++) if(R[i]<L[i]) R[i]+=m; solve(1,k+1,1,n);
    for(int i=1;i<=n;i++) (ans[i]==k+1)?printf("NIE\n"):printf("%d\n",ans[i]);
}
```

---

## 作者：Alex_Wei (赞：34)

[P3527 [POI2011] MET-Meteors](https://www.luogu.com.cn/problem/P3527)

给出一种不同于 jiangly 的更容易理解且更好写的单 $\log$ 做法。

设 $n, m, k$ 同阶，很显然我们有主席树 + 直接二分的做法，但空间复杂度和时间复杂度不优秀。

考虑整体二分，则 $\mathrm{solve}$ 相当于进行所有区间加之后单点查询，通过差分做到线性。问题在于向下递归时，我们不能直接下传原有坐标，否则每个区间处理的复杂度均为 $\mathcal{O}(n)$。

解决方法非常简单。在处理每个 $\mathrm {solve}$ 前，将所有相关下标离散化。这里离散化可以直接用桶维护而不需要排序，因为复杂度和它父区间离散化后的值域相关，加起来还是 $\mathcal{O}(n\log n)$ 的。

时间复杂度 $\mathcal{O}(n\log n)$，空间复杂度 $\mathcal{O}(n)$。代码非常好写，因为常数小所以跑得也很快。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define TIME 1e3 * clock() / CLOCKS_PER_SEC

constexpr int N = 3e5 + 5;
int n, m, k, cnt, p[N], ans[N];
int id[N], _id[N];
long long d[N], res[N];
vector<int> buc[N];
struct shower {
  int id, l, r, a;
} c[N << 1];
void solve(int l, int r, int cl, int cr, int range) {
  if(cl > cr) return;
  if(l == r) {
    for(int i = cl; i <= cr; i++) ans[id[i]] = l;
    return;
  }

  // relabel
  for(int i = 1; i <= range; i++) d[i] = 0;
  for(int i = cl; i <= cr; i++) for(int it : buc[id[i]]) d[it] = 1;
  for(int i = 1; i <= range; i++) d[i] += d[i - 1];
  for(int i = cl; i <= cr; i++) for(int &it : buc[id[i]]) it = d[it];
  for(int i = l; i <= r; i++) c[i].l = d[c[i].l - 1] + 1, c[i].r = d[c[i].r];
  range = d[range];
  
  // binary search
  int m = l + r >> 1, cm = cl - 1, cd;
  for(int i = 1; i <= range; i++) d[i] = 0;
  for(int i = l; i <= m; i++) d[c[i].l] += c[i].a, d[c[i].r + 1] -= c[i].a;
  for(int i = 2; i <= range; i++) d[i] += d[i - 1];
  for(int i = cl; i <= cr; i++) {
    res[i] = 0;
    for(int it : buc[id[i]]) res[i] = min(0x3f3f3f3fll, res[i] + d[it]);
    if(res[i] >= p[id[i]]) _id[++cm] = id[i];
  }
  cd = cm;
  for(int i = cl; i <= cr; i++)
    if(res[i] < p[id[i]])
      p[id[i]] -= res[i], _id[++cm] = id[i];
  for(int i = cl; i <= cr; i++) id[i] = _id[i];

  solve(l, m, cl, cd, range);
  solve(m + 1, r, cd + 1, cr, range);
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 1, o; i <= m; i++) cin >> o, buc[o].push_back(i);
  for(int i = 1; i <= n; i++) cin >> p[i];
  cin >> k;
  for(int i = 1; i <= k; i++) {
    int l, r, a;
    cin >> l >> r >> a;
    if(l <= r) c[++cnt] = {i, l, r, a};
    else c[++cnt] = {i, l, m, a}, c[++cnt] = {i, 1, r, a};
  }
  for(int i = 1; i <= n; i++) id[i] = i;
  solve(1, cnt + 1, 1, n, m);
  for(int i = 1; i <= n; i++)
    if(ans[i] > cnt) cout << "NIE\n";
    else cout << c[ans[i]].id << "\n";
  return cerr << "Time: " << TIME << " ms\n", 0;
}
```

---

## 作者：Nemlit (赞：34)

~~在发现此题前，我以为整体二分只能求第K大来着，我还是太菜了~~

我们先不考虑多组询问，假设只有一组询问

不难发现，答案具有明显的单调性，所以我们考虑二分来做

对于我们二分的值$mid$，我们先假设$l-mid$的雨全部下下来

如果当前的降雨量大于我们所需要的，那么答案大了，否则答案小了，就把所需要的降雨量变为：原本所需要的降雨量$-(l-mid$的降雨量$)$

那么有多组询问要怎么做呢？

我们考虑整体二分，我们定义函数solve(l, r, L, R)为我们二分的值为$[l, r]$（也就是单组询问的$l, r$），目前的操作区间为$[L,R]$（如果是单组询问的话就是$[L==R]$）

我们可以将$[L, R]$区间内所有的操作进行分类：分成答案大的和答案小的（见单组二分的分类），将答案小的放在前面（类似于归并排序），将答案大的放在后面，于是我们就可以继续二分递归了

我们假设在$[L, R]$内有$cnt1$个操作比答案小，那么我们递归应该是：

	solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);

最后，我们最开始的假设$[l, mid]$的雨全部下下来，可以用树状数组来实现，在每次递归进入下一次的时候，树状数组需要清空，但我们并不需要$memset$，只需要把这一层递归修改的值改回来就行了
### $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define int long long
#define inf 1000000000 
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define lb(x) (x)&(-(x))
#define maxn 300005
int n, m, ans[maxn], tr[maxn * 2], T;
struct ques {
	int l, r, a, id;
}e[maxn];
struct node {
	int ned, id;
}p[maxn], p1[maxn], p2[maxn];
vector<int> q[maxn];
il void add(int x, int v) {
	for(re int i = x; i <= 2 * m; i += lb(i)) tr[i] += v;
}
il int query(int x) {
	int ans = 0;
	for(re int i = x; i; i -= lb(i)) ans += tr[i];
	return ans;
}
il int Query(int x) {
	int ans = 0;
	for(re int i = 0; i < q[p[x].id].size(); ++ i) {
		ans += query(q[p[x].id][i]) + query(q[p[x].id][i] + m);
		if(ans >= p[x].ned) return ans;
	}
	return ans;
}
il void solve(int l, int r, int L, int R) {
	if(L > R) return;
	if(l == r) {
    	//如果二分到了终点，显然当前操作区间的答案都等于二分的答案
		rep(i, L, R) ans[p[i].id] = l;
		return;
	}
	int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    //差分，假设[l, mid]的雨全部下下来
	rep(i, l, mid) add(e[i].l, e[i].a), add(e[i].r + 1, -e[i].a);
    //判断哪些答案大了，那些小了
	rep(i, L, R) {
		int temp = Query(i);
		if(temp >= p[i].ned) p1[++ cnt1] = p[i];
		else p[i].ned -= temp, p2[++ cnt2] = p[i];
	}
    //清空树状数组
	rep(i, l, mid) add(e[i].l, -e[i].a), add(e[i].r + 1, e[i].a);
    //归并排序
	rep(i, L, L + cnt1 - 1) p[i] = p1[i - L + 1];
	rep(i, L + cnt1, R) p[i] = p2[i - L - cnt1 + 1];
    //继续二分
	solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
signed main() {
	n = read(), m = read();
	rep(i, 1, m) q[read()].push_back(i);
	rep(i, 1, n) p[i].ned = read(), p[i].id = i;
	T = read();
	rep(i, 1, T) {
		e[i].l = read(), e[i].r = read(), e[i].a = read(), e[i].id = i;
		if(e[i].r < e[i].l) e[i].r += m;
	}
	++ T, e[T].id = T, e[T].l = 1, e[T].r = 2 * m, e[T].a = inf;
	solve(1, T, 1, n);
	rep(i, 1, n) ans[i] == T ? puts("NIE") : printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：wxgwxg (赞：22)

这题思路是整体二分，就是把所有查询丢到队列里后二分，

$mid=(L+R)/2$,把mid前可以完成任务的国家 丢到左边的队列，不能的丢到右边，如果达到边界 $(L==R) $，就把队列里的询问答案赋值为$L$,每次用树状数组修改和求前缀和就行；

另外，我在另外一个oj交了下楼下几位的题解，发现wa了几个点，

因为数据是可能爆long long的，想一下，$m$个节点属于同一个国家，每次都把$1-m$的节点加$1e9$;所以判断的时候，如果收集数大于目标，就终止；具体看代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const int N=1000055;
int m,n,k,ans[N],cnt,mb[N];
ll sum[N];//树状数组
vector<int> G[N];// 存每个国家的节点
inline int read()
{
    int k=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-')f=-1;
    for(;isdigit(c);c=getchar()) k=k*10+c-'0';return f*k; 
}
struct que
{
    int l,r,opt,id;
    ll k;
}q[N],q1[N],q2[N];// opt=1 是每个国家的任务
// opt=2 是l<=r的陨石雨 opt=3 是l>r的陨石雨
void add(int x,ll v)
{
    for(;x<=m;x+=x&-x) sum[x]+=v;
}
ll query(int x)
{
    ll anss=0;for(;x;x-=x&-x) anss+=sum[x];return anss;
}
void ef(int s,int t,int l,int r)
{
    if(s>t) return;
    if(l==r) 
    {
        for(int i=s;i<=t;i++) if(q[i].opt==1) ans[q[i].id]=l;return;// 达到边界，跟新答案
    }
    int mid=l+r>>1,s1=0,s2=0;
    for(int i=s;i<=t;i++)
    {
        if(q[i].opt==1)
        {
            ll tmp=0;
            for(int j=0;j<G[q[i].id].size();j++)
            {
                tmp+=query(G[q[i].id][j]);
                if(tmp>q[i].k) break;// 统计，如果超过目标就终止，防止爆long long
            }
            if(tmp>=q[i].k) q1[++s1]=q[i];//丢左边
            else q[i].k-=tmp,q2[++s2]=q[i];//减去l-mid的数量，丢右边
        }
        else 
        {// 区间修改
            if(q[i].id<=mid)
            {
                if(q[i].opt==2)
                {
                    add(q[i].l,q[i].k);add(q[i].r+1,-q[i].k);
                }
                else 
                {
                    add(1,q[i].k);add(q[i].r+1,-q[i].k);add(q[i].l,q[i].k); 
                }
                q1[++s1]=q[i];
            }
            else q2[++s2]=q[i];
        }
    }
    for(int i=s;i<=t;i++)// 清空树状数组 if(q[i].id<=mid&&q[i].opt!=1)
    {
        if(q[i].opt==2)
        {
            add(q[i].l,-q[i].k);add(q[i].r+1,q[i].k);
        }
        else 
        {
            add(1,-q[i].k);add(q[i].r+1,q[i].k);add(q[i].l,-q[i].k); 
        }
    }
    int f=0,fl=0;
    for(int i=1;i<=s1;i++) 
    {
        q[s+i-1]=q1[i],f=1;
    }
    for(int i=1;i<=s2;i++) 
    {
        q[s+s1+i-1]=q2[i],fl=1;
    }
    if(f) ef(s,s+s1-1,l,mid);if(fl) ef(s+s1,t,mid+1,r);
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++) G[read()].push_back(i);
    for(int i=1;i<=n;i++) mb[i]=read();
    k=read();
    for(int i=1;i<=k;i++)
    {
        q[i].l=read();q[i].r=read();q[i].k=read();
        if(q[i].r>=q[i].l) q[i].opt=2;else q[i].opt=3;
        q[i].id=i;
    }
    for(int i=1;i<=n;i++)
    {
        q[i+k].k=mb[i];q[i+k].opt=1;
        q[i+k].id=i;
    }
    ef(1,k+n,1,k+1);
    for(int i=1;i<=n;i++)
    if(ans[i]!=k+1) printf("%d\n",ans[i]);
    else puts("NIE");
    return 0;
}
```

---

## 作者：AlanSP (赞：19)

### 0.引述

来看这样一道题：

> 多次询问，查询静态区间k小，**可离线**。

相信很多人都想到了主席树，但我们发现题中可以离线，所以我们有了一种常数小，debug方便，码量小的方法:

$\Huge\text{整体二分}$

---

### 1.引述

整体二分，是指将询问，修改等操作一起二分，基于值域。

传入的时候传四个参数：l,r,L,R。

表示值域在l到r内，操作在L到R内的操作答案。

处理的时候把操作分治，分到左右区间里。

同时，要使用树状数组，对左区间操作。

往下分治时，记住要撤销上次操作的影响，即清空树状数组。

整体二分还是很套路的，唯一不同的是树状数组中维护的内容。

```cpp
inline void solve(int l,int r,int L,int R)
{
	if(L>R) return;//防越界
	if(l==r)
	{
		for(int i=L;i<=R;i++) if(q[i].op==2) ans[q[i].id]=l;
		//当区间缩小为1时，表示[L,R]内的查询答案都是当前的数，直接赋值就好
		return;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	for(int i=L;i<=R;i++)
	{
		if(q[i].op==1)
		{
			//修改操作，若当前的数小于左边界的最大值，则统计左区间个数时可以算上
			if(q[i].l<=mid) q1[++cnt1]=q[i],add(q[i].id,q[i].r);
			else q2[++cnt2]=q[i];
		}
		else
		{
			//查询操作，如果查询的k大于左区间的个数，就分到右边
			int tmp=ask(q[i].r)-ask(q[i].l-1);//左区间个数
			if(q[i].k<=tmp) q1[++cnt1]=q[i];
			else q[i].k-=tmp,q2[++cnt2]=q[i];
		}
	}
	for(int i=1;i<=cnt1;i++) if(q1[i].op==1) add(q1[i].id,-q1[i].r);//撤销操作
	for(int i=1;i<=cnt1;i++) q[L+i-1]=q1[i];//分治下去操作
	for(int i=1;i<=cnt2;i++) q[L+cnt1+i-1]=q2[i];
	solve(l,mid,L,L+cnt1-1);
	solve(mid+1,r,L+cnt1,R);
}
```

---

### 2.例题

重要的还是例题~~。

- **[P1533 可怜的狗狗](https://www.luogu.com.cn/problem/P1533)**

模板题，树状数组为值域树状数组，查询可以直接仿照主席树的做法。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
const int N=2e5+9,INF=0x3f3f3f3f;
#define lowbit(x) (x&-x)
struct Query
{
	int l,r,k,id,op;
} q[N*3],q1[N*3],q2[N*3];
int n,m,a[N],cnt,cntq,ans[N],tr[N];
char op[2];
inline void add(int x,int c){while(x<=n){tr[x]+=c,x+=lowbit(x);}}
inline int ask(int x){int res=0;while(x){res+=tr[x],x-=lowbit(x);}return res;}

inline void solve(int l,int r,int L,int R)
{
	if(L>R) return;//防越界
	if(l==r)
	{
		for(int i=L;i<=R;i++) if(q[i].op==2) ans[q[i].id]=l;
		//当区间缩小为1时，表示[L,R]内的查询答案都是当前的数，直接赋值就好
		return;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	for(int i=L;i<=R;i++)
	{
		if(q[i].op==1)
		{
			//修改操作，若当前的数小于左边界的最大值，则统计左区间个数时可以算上
			if(q[i].l<=mid) q1[++cnt1]=q[i],add(q[i].id,q[i].r);
			else q2[++cnt2]=q[i];
		}
		else
		{
			//查询操作，如果查询的k大于左区间的个数，就分到右边
			int tmp=ask(q[i].r)-ask(q[i].l-1);//左区间个数
			if(q[i].k<=tmp) q1[++cnt1]=q[i];
			else q[i].k-=tmp,q2[++cnt2]=q[i];
		}
	}
	for(int i=1;i<=cnt1;i++) if(q1[i].op==1) add(q1[i].id,-q1[i].r);//撤销操作
	for(int i=1;i<=cnt1;i++) q[L+i-1]=q1[i];//分治下去操作
	for(int i=1;i<=cnt2;i++) q[L+cnt1+i-1]=q2[i];
	solve(l,mid,L,L+cnt1-1);
	solve(mid+1,r,L+cnt1,R);
}

int main()
{
	scanf("%d%d",&n,&m);//初始序列视为修改
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),q[++cnt]=(Query){a[i],1,0,i,1};
	for(int i=1;i<=m;i++)
	{
		int l,r,k;
		scanf("%s",op);
		scanf("%d%d",&l,&r);
		if(op[0]=='Q')
			scanf("%d",&k),q[++cnt]=(Query){l,r,k,++cntq,2};
		else q[++cnt]=(Query){a[l],-1,0,l,1},q[++cnt]=(Query){r,1,0,l,1},a[l]=r;
	}
	solve(-INF,INF,1,cnt);
	for(int i=1;i<=cntq;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

- [P3527 [POI2011]MET-Meteors](https://www.luogu.com.cn/problem/P3527)

这题就比较经典了。

操作为区间加，单点查到达某个值的时间。

这时候我们就要把区间加和单点查进行整体二分。

开始时，先把[l,mid]的区间加进行实现。

在查询时，如果当前国家的封地能量总合已经大于期望，那么证明达到满足它的期望的时间一定在[l,mid]的区间加内。

反正，则在右区间。

记得要保存每个国家的封地有哪些，可以用vector或者邻接表。

还注意破环成链，查询时记住把v和v+i的答案都算上。

记得撤销操作。

**Warning：邻接表的表头要和查询打包到一个结构体里，否则在操作下放的时候无法把表头h传递下去，即q[i]=q1[...]时要传递表头。**

代码我就放在这里????：

[$\huge\text{Code}$](https://www.luogu.com.cn/paste/jhe625l5)



---

## 作者：Juan_feng (赞：15)

小蒟蒻Jf写水题划水遭到毒瘤怒斥QAQAQ 再也不敢了.jpg
~~题解还是要水一发的~~

## 题是整体二分题， 这里提供一个分块做法qwq

**思路如下：**
对操作（区间加）进行分块， 设每T个操作为一组， 每次加入一组的操作， 在序列上差分一下求出每个位置当前的答案。  然后扫一下所有的国家（国家用vector保存这个国家的每一个位置), 如果这个国家的答案已经被求出来了， 那么直接跳过这个国家； 否则就判断一下这个国家所有位置的答案之和是否大于需求， 如果大于则说明使其达成需求的操作一定在这一组里面（不超过T个）， 这时候倒着扫一下就可以了。

因为每个位置最多只会被倒着扫一次， 没次不会扫超过T个操作， 且一共要做n/T次差分。 所以当T取sqrt(n)时， 总复杂度为m sqrt(n) + n sqrt(m)。

然后就没什么啦qwq，有什么问题可以私信小蒟蒻Jf。 

**那么代码如下**：

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define maxn 300010
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
#define DFR(i, l, r) for(re int i = l; i >= r; --i)
using namespace std;

int n, m, c, r, t, x, y, z, k;
int sq;
int a[maxn], ned[maxn], bl[maxn], siz[maxn], of[maxn], anss[maxn];
long long qwq[maxn], cha[maxn], res[maxn]; 
vector<int> ve[maxn];
struct hz {
	int l, r, k;
}q[maxn]; 

int main() {
	scanf("%d%d", &n, &m);
	FOR(i, 1, m) {
		scanf("%d", &t);
		ve[t].push_back(i),
		++siz[t],
		of[i] = t; 
	}
	FOR(i, 1, n)
	  scanf("%d", &ned[i]);
	scanf("%d", &k);
	
	sq = sqrt(k)*2.5; //可调参 
	FOR(i, 1, (k-1)/sq+1) {
		int l = (i-1)*sq+1, r = min(k, i*sq);
		FOR(j, l, r) {
			scanf("%d%d%d", &q[j].l, &q[j].r, &q[j].k);
			if(q[j].l > q[j].r)
			  qwq[q[j].l] += q[j].k, qwq[m+1] -= q[j].k, qwq[1] += q[j].k, qwq[q[j].r+1] -= q[j].k; 
			else 
			  qwq[q[j].l] += q[j].k, qwq[q[j].r+1] -= q[j].k;
		}
		FOR(j, 1, m) {
			cha[j] = qwq[j];
			cha[j] += cha[j-1];
			res[of[j]] += cha[j];  
		}
		
		FOR(u, 1, n) {
			long long pt = res[u];
			if(anss[u] || pt < ned[u])
			  continue;
			DFR(j, r, l) {
				FOR(xx, 0, siz[u]-1)
				  if(q[j].l <= q[j].r) {
				  	  if(q[j].l <= ve[u][xx] && ve[u][xx] <= q[j].r)
				        pt -= q[j].k;
				  }
				  else 
				    if(q[j].l <= ve[u][xx] || ve[u][xx] <= q[j].r)
					  pt -= q[j].k; 
				    
				if(pt < ned[u]) {
					anss[u] = j;
					break;
				}
			}
		} 
		memset(res, 0, sizeof(res));
	}
	FOR(i, 1, n) 
	  if(anss[i] == 0)
	    puts("NIE");
	  else 
	    printf("%d\n", anss[i]);
} 
```

---

## 作者：FZzzz (赞：9)

整体二分什么的神（qi）仙（ji）操（yin）作（qiao）我反正是学不会的。

分块我来写肯定也会被卡到自闭。

所以就用主席树水过啦。

------------
首先，落一个陨石看一遍显然是会T飞的，所以我们需要二分。

一个个二分的话就需要一个数据结构，支持快速查询每场陨石落下之后每段已获得样本个数。

先不谈可持久化，则这是一个区间加单点查。差分一下，就变成了一个单点加前缀和查，用树状数组或者线段树维护一下即可。

树状数组显然是不好持久化的（~~其实是我自己不会~~），所以用可持久化线段树即主席树维护就好了。

每段至多被查$\log k$次，每次是$O(\log m)$时间，所以总时间复杂度是$O(m\log m\log k)$。

code：
```cpp
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
const int M=3e5+5;
struct node{
	int l,r;
	long long sumv;
	node* ch[2];
	node(int l,int r):l(l),r(r),sumv(0){
		if(l==r) ch[0]=ch[1]=0;
		else{
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
		}
	}
	node(node* nd){*this=*nd;}
	void update(int x,int k,node* nd){
		if(ch[0]&&x<=ch[0]->r){
			if(ch[0]==nd->ch[0]) ch[0]=new node(nd->ch[0]);
			ch[0]->update(x,k,nd->ch[0]);
		}
		else if(ch[1]){
			if(ch[1]==nd->ch[1]) ch[1]=new node(nd->ch[1]);
			ch[1]->update(x,k,nd->ch[1]);
		}
		sumv+=k;
	}
	long long query(int l,int r){
		if(l==this->l&&r==this->r) return sumv;
		else{
			if(r<=ch[0]->r) return ch[0]->query(l,r);
			else if(l>=ch[1]->l) return ch[1]->query(l,r);
			else return ch[0]->query(l,ch[0]->r)+ch[1]->query(ch[1]->l,r);
		}
	}
};
int n,m,k;
vector<int> o[M];
int p[M];
vector<node*> rt;
int main(){
	#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    m=readint();
    for(int i=1;i<=m;i++) o[readint()].push_back(i);
    for(int i=1;i<=n;i++) p[i]=readint();
    k=readint();
    rt.push_back(new node(1,m));
    for(int i=1;i<=k;i++){
    	int l,r,a;
    	l=readint();
    	r=readint();
    	a=readint();
    	rt.push_back(new node(rt[i-1]));
    	if(l<=r){
    		rt[i]->update(l,a,rt[i-1]);
    		if(r<m) rt[i]->update(r+1,-a,rt[i-1]);
		}
		else{
			rt[i]->update(l,a,rt[i-1]);
			rt[i]->update(1,a,rt[i-1]);
			if(r<m) rt[i]->update(r+1,-a,rt[i-1]);
		}
	}
	for(int i=1;i<=n;i++){
		int l=1,r=k+1;
		while(l<r){
			int mid=l+(r-l)/2;
			long long ans=0;
			bool ok=0;
			for(int j=0;j<o[i].size();j++){
				ans+=rt[mid]->query(1,o[i][j]);
				if(ans>=p[i]){ok=1;break;}
			}
			if(ok) r=mid;
			else l=mid+1;
		}
		if(r<=k) printf("%d\n",r);
		else printf("NIE\n");
	}
    return 0;
}
```


------------
啥？你就直接ctrl+c了？

然后发现M了八个点只有27分？

咳咳咳，~~我说了这代码可以AC吗？~~

你算一下空间复杂度，会发现是$O(k\log m)$（大概吧）。再看一下毒瘤的空间限制62.50MB，不M才怪好吧。

~~我就是因为这个把数组改成了`vector`，想着应该没用，结果果然没用。~~

所以说，老老实实用整体二分去吧。

啥？你跟我一样不会整体二分？

那你可以试试[这道题](https://www.luogu.org/problem/SP10264)。

双倍经验什么不存在的，除非你用整体二分。

~~不过那题是黑题，经验多多了。~~

---

## 作者：walk_alone (赞：7)

这题首先一看题：求最少需要多少波就可以收集到位。那这肯定是**二分**没得跑了——答案$t$满足单调性，在$t$天前都收集不到位，在$t$天后都可以收集到数。所以肯定可以二分答案了。

要是这个题只求某一个国家的天数，这题估计就掉到黄题去了——直接关心这一个国家的陨石数。枚举波数$mid$，然后用$O(n)$的时间去模拟前$mid$场陨石，看到没到数就行。总时间复杂度$O(klogk)$

可问题是这每一个国家都要看啊！如果是把刚刚这个过程重复$n$次，那等的黄花菜都凉了——$O(nklogk)$，十万级别的$n^2$都不行了这还有个对数。因此我们要想办法优化这个东西。

那怎么优化呢？

其实我们注意到一个事儿：如果用刚刚的想法，我们其实做了很多重复的事情。考虑这样的一个极端情况：两个国家$i,j$最终天数（答案）相同。我们会做什么事情呢？

对$i$国的讨论：首先是第一次大的二分$\displaystyle \frac{k+1}{2}$，为此前面这么多波陨石全部砸下来算一遍，然后挑出第$i$国要的一些节点，算出来一个总陨石数$tot$，继续二分。假设这波去左边了，那么下一波二分就是$\displaystyle \frac{k+1}{4}$，我们再一次的计算这一部分的陨石数，然后再判断去哪边……

这里过程就是一个非常稀松平常的二分答案的流程，没什么好优化的。

然后是对$j$国的讨论：首先是第一次大的二分$\displaystyle \frac{k+1}{2}$，为此前面这么多波陨石全部砸下来算一遍，然后挑出第$j$国要的一些节点，算出来一个总陨石数$tot$，继续二分。假设这波去左边了，那么下一波二分就是$\displaystyle \frac{k+1}{4}$，我们再一次的计算这一部分的陨石数，然后再判断去哪边……

~~（别找不同了，除了$i,j$之外都是复制的。好家伙作者你居然用直接复制这种方法水长度）~~

其实并不是水长度，而是这种暴力做法就会重复这个过程。我们其实在第二波的时候做了太多的无用功——在$i$国的时候前$\displaystyle \frac{k+1}{2}$波算过的陨石数现在又得再算一遍，然后是第二次二分又重复算了一遍，接下来还有第三次第四次……

那这个其实优化想法就很明显了，重复这么多次那当然是记忆化了。这是一条路：像主席树那样，每下来一波陨石记一下当前各个站的陨石情况，然后要哪个国家直接去算就行。但是注意空间，可没有平时的128MB。当然主席树优化了可以做，但是这不是这篇题解的内容。

那不考虑记忆化那怎么处理呢？很简单，**把相同性质的国家绑起来一起处理**。

回过头来看我们整个的朴素二分过程，其实对于**每一个国家**，我们的第一次二分都是枚举$[1,\displaystyle \frac{k+1}{2}]$波陨石，朴素算法相当于在这里就多重复了$n-1$次。那我们完全没必要每次都算这几波砸下来的陨石了，可以直接让这波全部砸下来，所有国家一起处理，都去判断一下这个国家到底是分到哪边——这么多波陨石下来自己要够了没。显然这些国家会**被分成两半**，一部分是当前这波已经够了的，和当前这波还不够的。那么对于这些够了的国家，答案只会更小，它们就**整体**分去左边，去枚举更小的波数，看够不够；这波不够的，**整体**去右边更大的波数。因为朴素算法中每个国家也要多次面临这种选择，而每次这种选择（判定）的时间代价是$O(n)$。通过这种方法我们让选择的时间代价压缩到一起去了，因而就变快了。

这个方法就是**整体二分**——一种**离线化**算法，通过将**同类询问整合**来缩短**判定**用时，从而节约时间。

接下来就是代码部分了，只放主体函数的代码。

下面一些变量的约定。

```cpp
long long sum[600005], need[300005];//sum：该空间站的陨石数，用树状数组维护。need数组：该国家所需陨石数
int n, m, ans[300005];//n：国家数。m：空间站数。ans数组：每个国家所需最少时间，k+1则判定NIE
struct aerolite//一波陨石
{
    int left;
    int right;
    long long k;//陨石数
    bool opt;//判定left和right关系。0则是left-right,1则是left-n-1-right
};
struct aerolite que[300005];
vector<int> belong[300005];//存储国家空间站的位置，belong[i]表示第i个国家的空间站位置
```
关于砸陨石下来统计的方法：因为是区间修改，单点查询，因而使用树状数组配上前缀和。一个非常常用的方法，因而省去该部分代码。

然后是主体函数solve：

```cpp
void solve(int left,int right,queue<int>country)//left与right：答案区间的范围。country队列：答案在该区间的国家。初始是全体国家，答案范围是1-k+1
{
    if(country.empty())//没国家了，散了吧。保险措施。
        return;
    if(left==right)//边界条件：答案范围只有一个了，那直接把这范围内所有国家的ans全定下来
    {
        while(!country.empty())
        {
            ans[country.front()] = left;
            country.pop();
        }
        return;
    }
    int mid = (left + right) >> 1;//开始二分
    for (int i = left; i <= mid;i++)//该部分陨石全部要砸下来，统计到树状数组里
        if(!que[i].opt)
        {
            change(que[i].left, que[i].k);
            change(que[i].right + 1, -que[i].k);
        }
        else
        {
            change(que[i].left, que[i].k);
            change(1, que[i].k);
            change(que[i].right + 1, -que[i].k);
        }
    queue<int> q_left, q_right;
    while(!country.empty())//将国家分类到q_left和q_right去
    {
        int now = country.front();
        country.pop();
        long long tot = 0;
        for (int i = 0; i < belong[now].size() && tot < need[now]; i++)
        	tot += query(belong[now][i]);//统计一个国家所有空间站这波的收获
        if(tot>=need[now])
            q_left.push(now);
        else
        {
            need[now] -= tot;//注意要减：因为对于下一次二分来说mid+1前的陨石不会再统计了，起始点就是mid+1，所以它对应的前面部分的陨石数也要减去。
            q_right.push(now);
        }
    }
    for (int i = left; i <= mid;i++)//记得还原，为下一次做准备。每一次树状数组里只有区间[left,mid]的陨石被统计
        if(!que[i].opt)//就是计算的逆过程
        {
            change(que[i].left, -que[i].k);
            change(que[i].right + 1, que[i].k);
        }
        else
        {
            change(que[i].left, -que[i].k);
            change(1, -que[i].k);
            change(que[i].right + 1, que[i].k);
        }
    if(!q_left.empty())//左边存在国家，这一部分就划去左边处理
        solve(left, mid, q_left);
    if(!q_right.empty())
        solve(mid + 1, right, q_right);//右边有国家，就去右边处理
    return;
}
```


---

## 作者：Jμdge (赞：5)

这道题数据更新过了啊，原来的题解都过不了了啊，搞了一个下午才查出问题在哪里。

## 大致思路

其实这道题就是用了整体二分（又学了一招）的思想，每次二分 $mid$ ，然后用类似莫队的方法，用 **$update$** 去维护掉了 **$mid$** 次陨石后的状态，然后在 **$BIT$** 里面区间修改，单点查询。

其实思路也不是非常复杂，但还是花了一个下午 A 题，我还是太弱了...

## 要点：整体二分的思想

那么整体二分的话就是把满足条件的放到左边，不满足条件的放到右边，继续向下处理，和快排的处理方式也是蛮像的(但是由于整体二分是传四个参数：$s\ t\ l\ r$ 的, 所以递归层数最多也就是 log 级别，不会像 快排 那样会被卡成 $n^2$ )。

## 代码实现
（其实我的代码跑的还是蛮快的）

```cpp
//by Judge
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int M=3e5+11;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){
    ll x=0; char c=getchar(); while(!isdigit(c)) c=getchar();
    for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x;
} int n,m,k,now; vector<int> G[M];
int u[M],v[M],w[M],t1[M],t2[M],p[M],s[M],ans[M]; ll f[M];
inline int lowbit(int x){ return x&-x; }
inline void add(int x,int val){ for(;x<=m;x+=x&-x) f[x]+=val; }
inline ll query(int x,ll ans=0){ for(;x;x-=x&-x) ans+=f[x]; return ans; }
inline bool check(int x,ll ans=0){ //最后一个数据点主要就是卡这里
    for(int i=0;i<G[x].size();++i){
        ans+=query(G[x][i]);
		if(ans>=s[x]) return true; //也就是说最后一个点的数据是会炸long long 的,所以要随时判断是否满足条件
	} return false;
} inline void update(int x,int val){ //这里是区间更新
    add(u[x],val),add(v[x]+1,-val);
	if(u[x]>v[x]) add(1,val),add(m+1,-val);
} void solv(int s,int t,int l,int r){ //这个就是整体二分
    if(s>t || l>r) return ; int mid=l+r>>1,l1=0,l2=0;
    if(l==r){ for(int i=s;i<=t;++i) ans[p[i]]=l; return ; }
    while(now<mid)++now,update(now,w[now]); while(now>mid)update(now,-w[now]),--now;
    for(int i=s;i<=t;++i) if(check(p[i])) t1[++l1]=p[i]; else t2[++l2]=p[i];
    for(int i=1;i<=l1;++i)p[s+i-1]=t1[i]; for(int i=1;i<=l2;++i)p[s+i-1+l1]=t2[i];
    if(l1) solv(s,s+l1-1,l,mid); if(l2) solv(s+l1,t,mid+1,r);
} int main(){
    n=read(),m=read();
    for(int i=1;i<=m;++i) G[read()].push_back(i);
    for(int i=1;i<=n;++i) p[i]=i,s[i]=read();
    k=read()+1; for(int i=1;i<k;++i)
        u[i]=read(),v[i]=read(),w[i]=read();
    u[k]=1,v[k]=m,w[k]=1e9+9,solv(1,n,1,k);
    for(m=1;m<=n;++m) ans[m]==k?puts("NIE"):printf("%d\n",ans[m]);
    return 0;
}
```

---

## 作者：Newuser (赞：3)

洛谷上很早就过了，，然而在我学校的OJ上的数据很强，迫不得已重构了两次代码orz，还调整了一下算法orz
//[蒟蒻博客Newuser小站同步](http://www.newuser.top/2018/06/16/%e3%80%90poi2011met-meteors%e3%80%91%e6%95%b4%e4%bd%93%e4%ba%8c%e5%88%86%e4%b8%80%e4%ba%9b%e7%a5%9e%e5%a5%87%e4%bc%98%e5%8c%96/)

这道题有个十分显然的做法（似乎楼下们的题解好多是这样的），就是直接套入一个树状差分数组进行整体二分，然后每次加入前mid个，查询，搞完还原树状数组。看上去时间复杂度并没有什么问题，然后，愉快的被卡卡卡卡常(微笑）。

这时候就要用到一个类似于莫队里面的左移右移的东西了。我们可以将下陨石和询问分开看，设定一个类似莫队R的 东西（本题是前缀和没有L），对R跑到当前mid的位置。这样我们可以尝试去画一个图，就会惊讶发现，对于整个整体二分最多每层会移动n次。

看似对时间复杂度影响不大，其实不然，实际上我们反复用了上一次的插入树状数组后的结果，也就是说，我们节省了很多重复的，冗杂的工作，最后写出代码也其实更加精简易懂（不用处理队列类型）。

talk is cheap , show the code:

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int maxn = 300005;
int n,m,k;
int bit[maxn];
vector<int>ve[maxn];
void add(int x,int d) { for(;x<=m+2;x+=lowbit(x)) bit[x]+=d; }
int getsum(int x) { int sum=0; for(;x;x-=lowbit(x)) sum+=bit[x]; return sum; }
int ans[maxn];
struct node
{ int id,ned; };
struct chan
{
	int l,r,cha;
}z[maxn];
void modify(int po,int knd)
{
	if(knd)
	{
		if(z[po].r>=z[po].l)
		{
			add(z[po].l,z[po].cha); 
			add(z[po].r+1,-z[po].cha);
		}
		else
		{
			add(1,z[po].cha);
			add(z[po].r+1,-z[po].cha);
			add(z[po].l,z[po].cha);
		}
	}
	else
	{
		if(z[po].r>=z[po].l)
		{
			add(z[po].l,-z[po].cha); 
			add(z[po].r+1,z[po].cha);
		}
		else
		{
			add(1,-z[po].cha);
			add(z[po].r+1,z[po].cha);
			add(z[po].l,-z[po].cha);
		}
	}
}
int cur;
void query(vector<node>q,int l,int r)
{
	if(!q.size()) return;
	if(l==r)
	{
		int ss = q.size();
		for(int i=0;i<ss;i++) ans[q[i].id] = l;
		return;
	}
	int mid = (l+r)/2;
	while(cur<mid) ++cur,modify(cur,1);
	while(cur>mid) modify(cur,0),--cur;
	int ss=q.size();
	vector<node>q1,q2;
	for(int i=0;i<ss;i++)
	{
		int x = q[i].id;
		int  sd = ve[x].size();
		int summ = 0; 
		for(int j=0;j<sd;j++)
		{
			summ+=getsum(ve[x][j]);
			if(summ>=q[i].ned) break;
		}
		if(summ>=q[i].ned) q1.push_back(q[i]);
		else q2.push_back((node){q[i].id,q[i].ned});
	}
	query(q1,l,mid);
	query(q2,mid+1,r);
}
int main()
{
	vector<node>q;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		ve[x].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		q.push_back((node){i,x});
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		int ll,rr,aa;
		scanf("%d%d%d",&ll,&rr,&aa);
		z[i].l = ll ;z[i].r = rr; z[i].cha = aa;
	}
	++k; z[k].l=1; z[k].r=m; z[k].cha = 0x3f3f3f3f;
	query(q,1,k);
	for(int i=1;i<=n;i++) if(ans[i]!=k)  printf("%d\n",ans[i]);
	else printf("NIE\n"); 
}
```

---

## 作者：rainygame (赞：2)

来一篇 $O(n\log n)$ 的题解！

答案具有可二分性，考虑整体二分。设当前分治区间为 $[l,r]$，任务是判断 $Q$ 集合内的国家答案是否小于等于 $m=\dfrac{l+r}{2}$。

$O(n\log^2n)$ 的做法比较简单：将 $[l,m]$ 的操作都执行一次，然后再对于 $Q$ 国家集合内的太空站都单点求值后加起来判断，可以用 BIT 维护这个操作。最后二分到两个区间时，$(m,r]$ 的国家目标需要调整，使得 $[l,m]$ 的操作不会影响到它们。

还有一个更加暴力的做法：将 $[l,m]$ 操作转化成差分数组上的单点加，然后扫一遍整个序列，也可以求出每个太空站的值。这个做法是可以优化的，因为“关键点”个数只有 $O(\sum\limits_{i\in Q}\lvert S_i\rvert+r-l)$（其中 $S_i$ 表示属于国家 $i$ 的空间站集合），所以如果这些点排好序了，那么就可以直接扫一遍，复杂度优化为 $O(n\log n)$！

考虑在第一次分治之前就排好序，那么在后面的分治中，可以将点集有序地分为两部分，复杂度不会退化。

注意事项：

- 计算过程中可能会爆 `long long`。
- 注意有些国家可能没有空间站。

比两只 $\log$ 好写的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int128 _int;
#define MAXN 300005

int n, m, q; int a[MAXN], p[MAXN], ans[MAXN]; _int tp[MAXN];
struct Node{int x, k, id;}; vector<Node> Q;

void sol(int l, int r, vector<Node> Q){
    if (l == r){for (auto i: Q) if (!i.k) ans[a[i.x]]=l; return;} int mid((l+r)>>1);
    for (_int i(0), res(0); i<Q.size(); ++i){
        if (!Q[i].k) tp[a[Q[i].x]] += res; else if (Q[i].id <= mid) res += Q[i].k;
    }
    vector<Node> ql, qr;
    for (auto i: Q){
        if (i.k) (i.id <= mid ? ql : qr).push_back(i);
        else if (tp[a[i.x]] >= p[a[i.x]]) ql.push_back(i);
        else p[a[i.x]] -= tp[a[i.x]], tp[a[i.x]] = 0, qr.push_back(i);
    }
    for (auto i: Q) tp[a[i.x]] = 0; sol(l, mid, ql); sol(mid+1, r, qr);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> m >> n; for (int i(1); i<=n; ++i) cin >> a[i], Q.push_back({i, 0, 0});
    for (int i(1); i<=m; ++i) cin >> p[i]; cin >> q;
    for (int i(1), l, r, k; i<=q; ++i){
        cin >> l >> r >> k;
        if (l <= r) Q.push_back({l, k, i}), Q.push_back({r+1, -k, i});
        else Q.push_back({1, k, i}), Q.push_back({r+1, -k, i}), Q.push_back({l, k, i});
    }
    sort(Q.begin(), Q.end(), [](Node a, Node b){return a.x == b.x ? !a.k < !b.k : a.x < b.x;});
    memset(ans, 0x3f, sizeof(ans)); sol(1, q+1, Q);
    for (int i(1); i<=m; ++i) if (ans[i] > q) cout << "NIE\n"; else cout << ans[i] << '\n';

    return 0;
}
```

---

## 作者：RedreamMer (赞：2)

[$\Large\texttt{P3527}$](https://www.luogu.com.cn/problem/P3527)

[$\texttt{In my cnblogs}$](https://www.cnblogs.com/RedreamMer/p/14403375.html)

## 题意

一个环形被分为 $m$ 份，每份都属于 $n$ 个国家之一，有 $k$ 场陨石，每场对应环上一段区间，为此区间上每份的隶属国家增加 $a_i$ 的贡献，每个国家期望得到 $p_i$ 的陨石，问第几波陨石过后能够达成目标？

$n,m,k\le 3e5$

## 思路

因为答案具有可二分性，即可以二分在第几波陨石达成目标，因为有修改，一个一个国家二分显得有点浪费，可以联想到整体二分，二分所有国家的完成时间，而修改操作可以由树状数组（区间修改，单点查询）来实现，注意要在最后加一波无限大的陨石特判 $\texttt{NIE}$ 的情况。

对于查询，直接用树状数组暴力一个一个查询**当前块内**所有国家的所有环形上的区域。

时间复杂度为 $O(N\log^2N)$ 。

以下给出时间复杂度的证明。

## 证明

主要时间复杂度产生在修改和查询两种操作上。

注意 $n,m,k$ 同阶。

对于修改：第 $i$ 场陨石在整理二分中是从 $[1,k+1]$ 这个区间到 $[i,i]$ 这个区间，一共约有 $\log_2 k$ 层，每层都对其执行两遍（一遍修改，一遍清除）修改操作，修改操作复杂度约为 $O(\log_2 m)$ ，所以总复杂度约为 $O(N\log^2N)$ 。

对于查询：看起来是暴力一个一个查询，但是对于环形上每个区域，也都是在 $\log_2 k$ 层上每层都都做一次 $O(\log_2 m)$ 的查询，所以复杂度也是 $O(N\log^2N)$ 。

## 代码

```cpp
int a, b, c, p[N + 10], s[N + 10], ans[N + 10];
vector<int> st[N + 10], Q, L, R;
struct node
{
    int opt, id, x, y, z;
} ask[N + 10];

inline void add(int n, int k)
{
    if (!n)
        return;
    for (; n <= b; n += n & -n)
        p[n] += k;
}

inline int query(int n)
{
    int res = 0;
    for (; n; n -= n & -n)
        res += p[n];
    return res;
}

inline void change(int l, int r, int val)
{
    if (l <= r)
        add(l, val), add(r + 1, -val);
    else
        add(1, val), add(r + 1, -val), add(l, val);
}

inline void solve(int l, int r)
{
    if (l == r)
    {
        for (int i = 0; i < Q.size(); i++)
            if (ask[Q[i]].opt == 2)
                ans[ask[Q[i]].id] = l;
        return;
    }
    int mid = (l + r) >> 1;
    for (int i = 0; i < Q.size(); i++)
    {
        int n = Q[i];
        if (ask[n].opt == 1)
        {
            if (ask[n].id <= mid)
                change(ask[n].x, ask[n].y, ask[n].z), L.PB(n);
            else
                R.PB(n);
        }
        else
        {
            int tmp = 0;
            for (int j = 0; j < st[ask[n].id].size(); j++)
            {
                int m = st[ask[n].id][j];
                tmp += query(m);
                if (tmp >= s[ask[n].id])
                    break;
            }
            if (s[ask[n].id] <= tmp)
                L.PB(n);
            else
                R.PB(n), s[ask[n].id] -= tmp;
        }
    }
    for (int i = 0; i < L.size(); i++)
    {
        int n = L[i];
        if (ask[n].opt != 1)
            continue;
        change(ask[n].x, ask[n].y, -ask[n].z);
    }
    vector<int> tmp = R;
    Q = L;
    R.clear();
    L.clear();
    solve(l, mid);
    Q = tmp;
    solve(mid + 1, r);
}

signed main()
{
    // freopen("in1.in", "r", stdin);
    a = read();
    b = read();
    for (int i = 1; i <= b; i++)
        st[read()].PB(i);
    for (int i = 1; i <= a; i++)
        s[i] = read();
    c = read();
    for (int i = 1; i <= c; i++)
    {
        ask[i].opt = 1;
        ask[i].id = i;
        ask[i].x = read();
        ask[i].y = read();
        ask[i].z = read();
    }
    ask[++c].opt = 1;
    ask[c].id = c;
    ask[c].x = 1;
    ask[c].y = b;
    ask[c].z = 1e9;
    for (int i = 1; i <= a; i++)
        ask[i + c].opt = 2, ask[i + c].id = i;
    c += a;
    for (int i = 1; i <= c; i++)
        Q.PB(i);
    solve(1, c - a);
    for (int i = 1; i <= a; i++)
        if (ans[i] != c - a)
            printf("%d\n", ans[i]);
        else
            puts("NIE");
    return 0;
}
```

---

## 作者：cirnovsky (赞：1)

## 题意简述

给定 $n$ 个主体，每个主体有一个指标。给定 $m$ 个区域（环形），每个区域都分别属于不同的主体，有 $k$ 个区间加法，问每个主体在第几次区间修改后达成指标。

## 题解

这道题有一点绕，首先我们搞清楚概念，具体看题意简述。

显然每个询问都能够二分解决，于是我们考虑用整体二分来整这道题。

首先确定整体二分的值域即我们二分的答案。

因为询问问的是天数，所以我们用 1 到 $k$ 作为我们整体二分的值域。

我们设整体二分的函数为 $\mathrm{solve}(L,R,l,r)$，其中 $L,R$ 表示值域，$l,r$ 表示询问。

对于当前二分到的值域区间 $L,R,M=(L+R)/2$，如果 $[L,M]$ 的修改操作能够直接使得询问达成指标，则我们把这个询问放进询问区间 $[l,m]$ 里，其中 $m=(l+r)/2$。

最后还原一下修改即可。

修改操作可以用树状数组+差分来实现，线段树也可以。

如何判断无解的情况呢？

我们可以加入一个虚拟的修改操作，即让区间 $[1,m]$ 加上无穷大，让修改操作的个数 $k$ 加一，最后输出答案的时候判断如果等于 $k$ 即是无解。

```cpp
#include <cstdio>
#include <vector>
#define int long long
#define vec(x) (Q[x].G)

using namespace std;

const int Maxn = 3e5 + 5;
int n, m, k, qls[Maxn], qrs[Maxn], qva[Maxn], ans[Maxn], isa[Maxn];
struct Query_Node
{
	int w, id;
	vector < int > G;
} Q[Maxn], lq[Maxn], rq[Maxn];
struct Fenwick_Tree
{
	int bit[Maxn];
	
	void ins(int x, int v)
	{
		for (; x <= m; x += x & -x) 	bit[x] += v;
	}
	
	int ret(int x)
	{
		int res = 0;
		for (; x; x -= x & -x)	res += bit[x];
		return res;
	}
} fwt;

void solve(int lval, int rval, int st, int ed)
{
	if (lval > rval || st > ed) 	return ;
	if (lval == rval)
	{
		for (int i = st; i <= ed; ++i)	ans[Q[i].id] = lval;
		return ;
	}
	int mid = (lval + rval) >> 1;
	int lt = 0, rt = 0;
	for (int i = lval; i <= mid; ++i)
	{
		if (qls[i] <= qrs[i])
		{
			fwt.ins(qls[i], qva[i]);
			fwt.ins(qrs[i] + 1, -qva[i]);
		}
		else
		{
			fwt.ins(qls[i], qva[i]);
			fwt.ins(m + 1, -qva[i]);
			fwt.ins(1, qva[i]);
			fwt.ins(qrs[i] + 1, -qva[i]);
		}
	}
	for (int i = st; i <= ed; ++i)
	{
		int lim = 0;
		for (unsigned j = 0; j < vec(i).size(); ++j)
		{
			int mbr = vec(i)[j];
			int xxx = fwt.ret(mbr);
			lim += xxx;
			if (xxx > 1e9)	break;
		}
		if (lim >= Q[i].w)	lq[++lt] = Q[i];
		else	rq[++rt] = Q[i];
	}
	for (int i = 1; i <= lt; ++i)	Q[st + i - 1] = lq[i];
	for (int i = 1; i <= rt; ++i)	Q[st + lt + i - 1] = rq[i];
	if (rt) 	solve(mid + 1, rval, st + lt, ed);
	for (int i = lval; i <= mid; ++i)
	{
		if (qls[i] <= qrs[i])
		{
			fwt.ins(qls[i], -qva[i]);
			fwt.ins(qrs[i] + 1, qva[i]);
		}
		else
		{
			fwt.ins(qls[i], -qva[i]);
			fwt.ins(m + 1, qva[i]);
			fwt.ins(1, -qva[i]);
			fwt.ins(qrs[i] + 1, qva[i]);
		}
	}
	if (lt) 	solve(lval, mid, st, st + lt - 1);
}

signed main()
{
	scanf("%lld %lld", &n, &m);
	for (int i = 1, x; i <= m; ++i)
	{
		scanf("%lld", &x);
		vec(x).push_back(i);
	}
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", &Q[i].w);
		Q[i].id = i;
	}
	scanf("%lld", &k);
	for (int i = 1; i <= k; ++i)	scanf("%lld %lld %lld", &qls[i], &qrs[i], &qva[i]);
	qls[++k] = 1, qrs[k] = n, qva[k] = 1e9;
	solve(1, k, 1, n);
	for (int i = 1; i <= n; ++i)
	{
		if (ans[i] == k)	puts("NIE");
		else	printf("%lld\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：1124828077ccj (赞：1)

这题是道二分题，然而二分很巧妙。

如果单个询问，显然可以O(logk)二分然后轻松判定。

但是多个询问就不好解决了，于是可以使用整体二分的思想。

我们可以二分k，然后可行的放一边，不可行的放另外一边

如何判定呢，树状数组扫过去就可以了，需要利用上一次的结果

然后分析一下时间复杂度

首先，二分和可行不可行的扫描合起来是O(mlogk)

然后树状数组每次扫过去的话，总共会把整个区间扫一遍（这个一指的是常数遍）

然后效率是O(n\*logn\*logn)

附代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
using namespace std;
int n,m,k,a[300002],s[300002],u[300002],v[300002],w[300002];
int t1[300002],t2[300002],p[300002],ans[300002],now;
long long f[300002];
vector<int>g[300002];
void gengxin(int x,int y){
    for (;x>=1;x-=x&-x)f[x]+=y;
}
long long chaxun(int x){
    long long ans=0;
    for (;x<=m;x+=x&-x)ans+=f[x];
    return ans;
}
bool pd(int a){
    long long ans=0;
    for (int i=0;i<g[a].size();i++)
    ans+=chaxun(g[a][i]);
    return ans>=s[a];
}
void ccj(int x,int y,int l,int r){//整体二分
    if (x>y)return;
    if (l==r){for (int i=x;i<=y;i++)ans[p[i]]=l;return;}
    int mid=(l+r)/2;
    while(now<mid)
    {
        now++;
        if (u[now]<=v[now])
        {
            gengxin(v[now],w[now]);gengxin(u[now]-1,-w[now]);
        }
        else
        {
            gengxin(m,w[now]);gengxin(u[now]-1,-w[now]);
            gengxin(v[now],w[now]);
        }
    }
    while(now>mid)
    {
        if (u[now]<=v[now])
        {
            gengxin(v[now],-w[now]);gengxin(u[now]-1,w[now]);
        }
        else
        {
            gengxin(m,-w[now]);gengxin(u[now]-1,w[now]);
            gengxin(v[now],-w[now]);
        }
        now--;
    }
    int l1=0,l2=0;
    for (int i=x;i<=y;i++)
    if (pd(p[i]))t1[++l1]=p[i];else t2[++l2]=p[i];
    for (int i=x;i<x+l1;i++)p[i]=t1[i-x+1];
    for (int i=x+l1;i<=y;i++)p[i]=t2[i-x-l1+1];
    ccj(x,x+l1-1,l,mid);ccj(x+l1,y,mid+1,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {scanf("%d",&a[i]);g[a[i]].push_back(i);}
    for (int i=1;i<=n;i++)
    {p[i]=i;scanf("%d",&s[i]);}
    scanf("%d",&k);
    for (int i=1;i<=k;i++)
    scanf("%d%d%d",&u[i],&v[i],&w[i]);
    ccj(1,n,0,k+1);
    for (int i=1;i<=n;i++)
    if (ans[i]<=k)printf("%d\n",ans[i]);else puts("NIE");
    return 0;
}
```

---

## 作者：hepan (赞：0)

### 题目大意

$n$ 个国家，每个国家都有一个指标。

在某颗行星上有环形的 $m$ 个坑，每个坑都属于一个国家。

有 $k$ 次流星雨，每次将选择一段区间加上某个数。

问每个国家在第几次时到达目标。

$n,m,k\le 3\cdot10^5$

### 算法讲解

整体二分，顾名思义就是将多个二分一起考虑，具体的，有 $q$ 组询问，每组询问都可以二分，将这些询问一起考虑。

考虑 $\text{solve}(l,r,L,R)$ 考虑 $[l,r]$ 的询问，答案的值域为 $[L,R]$ ，设 $mid=\left\lfloor\frac{L+R}2\right\rfloor$，通过一些数据结构将 $[l,r]$ 询问分成两组，在进行递归即可。

时间复杂度：$\Theta(n\log w)$ 其中 $w$ 为答案的值域，假设数据结构是 $\Theta(1)$ 的。

### 题解

本题就是个模板题啦，维护的数据结构是树状数组，注意以下事项：

+ 树状数组清空不能暴力 $\Theta(n)$ 清空，要在 $\Theta((R-L)\log n)$ 的复杂度清空。
+ 先递归 $\text{solve}(l+x,r,mid+1,R)$ 因为树状数组的贡献可以累加。
+ 中途要开 long long,还要注意爆 long long
+ 尽量优化常数。

时间复杂度：$\Theta(m\log k\log m+n+k)$

### code

```c++
//my code head for OI
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<=n;i++)
#define per(i,a,n) for (int i=a;i>=n;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const int mod=1000000007;
const ll mod2=1ll*mod*mod;
const int maxn=3e5+10;
int quick(int a,int b){int res=1;a%=mod;assert(b>=0); for(;b;b>>=1){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;}return res;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int n,m,k,num1,num2,ans[maxn],aa[maxn],bb[maxn],cc[maxn];
namespace io{
	inline int read(){
		int X=0,w=0;char ch=0;
		while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
		while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
		return w?-X:X;
	}
	inline void write(int x){
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
}
struct opera{
	int w,id;
	vector<int> vc;
}ope[maxn],ope1[maxn],ope2[maxn];
struct BIT{
	ll c[maxn];
	void add(int x,ll y){
		for(;x<=m;x+=x&-x) c[x]+=y;
	}
	ll query(int x){
		ll res=0;
		for(;x;x-=x&-x) res+=c[x];
		return res;
	}
}bit;
void solve(int l,int r,int L,int R){
	if(l>r||L>R) return ;
	if(L==R){
		rep(i,l,r) ans[ope[i].id]=L;
		return ;
	}
	num1=0,num2=0;
	int mid=(L+R)/2;
	rep(i,L,mid){
		if(aa[i]<=bb[i]) bit.add(aa[i],cc[i]),bit.add(bb[i]+1,-cc[i]);
		else bit.add(aa[i],cc[i]),bit.add(m+1,-cc[i]),bit.add(1,cc[i]),bit.add(bb[i]+1,-cc[i]);
	}
	rep(i,l,r){
		ll res=0;
		for(auto x:ope[i].vc){
			ll xx=bit.query(x);
			res+=xx;
			if(xx>1e9) break;
		}
		if(res>=ope[i].w) ope1[++num1]=ope[i];
		else ope2[++num2]=ope[i];
	}
	copy(ope1+1,ope1+num1+1,ope+l);
	copy(ope2+1,ope2+num2+1,ope+l+num1);
	int orz=num1,moo=num2;
	if(moo) solve(l+orz,r,mid+1,R);
	rep(i,L,mid){
		if(aa[i]<=bb[i]) bit.add(aa[i],-cc[i]),bit.add(bb[i]+1,cc[i]);
		else bit.add(aa[i],-cc[i]),bit.add(m+1,cc[i]),bit.add(1,-cc[i]),bit.add(bb[i]+1,cc[i]);
	}
	if(orz) solve(l,l+orz-1,L,mid);
}
int main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	n=io::read(),m=io::read();
	int tmp=0;
	rep(i,1,m){
		ope[io::read()].vc.pb(i);
	}
	rep(i,1,n){
		ope[i].w=io::read();
		ope[i].id=++tmp;
	}
	cin>>k;
	rep(i,1,k) aa[i]=io::read(),bb[i]=io::read(),cc[i]=io::read();
	k++;
	aa[k]=1,bb[k]=n,cc[k]=1e9;
	solve(1,n,1,k);
	rep(i,1,tmp){
		if(ans[i]==k) puts("NIE");
		else io::write(ans[i]),putchar('\n');
	}
	return 0;
}
```



---

## 作者：GoldenPotato137 (赞：0)

[戳我获得更好的阅读体验qwq](https://www.goldenpotato.cn/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/luogu-p3527-poi2011met-meteors/)

---
# Solution
~~我是一直奉行坚决不写树状数组只写线段树理论的，直到这题.......~~

这题是一道整体二分的模板题。

.


首先，我们考虑只有一个国家的情况。~~这不SB问题么~~

我们可以二分一个答案，然后我们用线段树暴力模拟，暴力Check,复杂度$O(mlogn)$。

显然，如果我们每一个国家都这么搞一轮，复杂度达到了惊人的$O(n\cdot m logn)$，这显然是要T飞的。

.

因此，我们就得请出伟大的整体二分了。整体二分，顾名思义，就是把所有询问一起二分答案。

考虑这样做，一开始，所有询问的答案均在$1,m+1$这个范围内(+1是为了方便判断不可行的情况)。接下来，我们二分一个$mid$，然后把所有答案$<=mid$的询问丢到$1,mid$区间，把所有在mid时间内不能完成的询问丢到右区间。

怎么判断一个询问是否能在mid时间内完成呢？暴力啊。我们直接用线段树暴力做个mid次修改，然后再暴力看每个国家是否满足即可。

接下来，我们只需要把这个东西递归下去做，直到区间长度为$1$为止。

.

什么，这玩意复杂度很大？的确很大，$O(nlog^2n)$呢。

怎么证呢？显然，我们发现这个递归最多log层，每层我们会把所有的修改操作都会做一遍，因此总复杂度两个log。

再给一个参考数据，30w数据下，2个log算出来的东西接近两个亿。好了，我想你知道了要写什么数据结构了.......

啥？所以说你还是义无反馈的写了线段树？[来试试在这里交吧](https://www.luogu.org/problemnew/show/U66611),可以检验你的程序的正确性  ~~（以及究竟要跑个多久）~~

.

就酱，我们就把这题给切掉啦(～￣▽￣)～ 

~~你很有可能被卡常及卡空间，当然，这就是后话了~~

---
# Code
```cpp
//Luogu P3527 [POI2011]MET-Meteors
//Mar,27th,2019
//整体二分+树状数组
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<ctime>
using namespace std;
int read()
{
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=300000+100;
const int inf=0x3f3f3f3f;
int n,m,K,ans[N],w[N];//w[i]第i个国家需要多少个陨石
struct BIT
{
	long long t[N<<2];
	inline int lowbit(int &x){return x&(-x);}
	void Init()
	{
		memset(t,0,sizeof t);
	}
	long long Query(int x)
	{
		long long sum=0;
		while(x>0)
		{
			sum+=t[x];
			x-=lowbit(x);
		}
		return sum;
	}
	void update(int x,int dlt)
	{
		while(x<=m)
		{	
			t[x]+=dlt;
			x+=lowbit(x);
		}
	}
	void Change(int l,int r,int w)
	{
		update(r+1,-w);
		update(l,w);
	}
}bit;
struct OP
{
	int l,r,w;
}op[N];
vector <int> a[N];
struct DL
{
	int l,r;
	vector <int> c;
}mqueue[N+5000];
int main()
{
	//int t=clock();
	//freopen("3527.in","r",stdin);
	//freopen("3527.out","w",stdout);
	
	n=read(),m=read();
	for(int i=1;i<=m;i++)
		a[read()].push_back(i);
	for(int i=1;i<=n;i++)
		w[i]=read();
	K=read();
	for(int i=1;i<=K;i++)
		op[i].l=read(),op[i].r=read(),op[i].w=read();
	
	int front=0,tail=0,T=1;//T:当前执行到了T时刻
	mqueue[tail].l=1,mqueue[tail].r=K+1;
	for(int i=1;i<=n;i++)
		mqueue[tail].c.push_back(i);
	tail++;
	while(tail!=front)
	{
		if(mqueue[front].l==mqueue[front].r)
		{
			for(int i=0;i<int(mqueue[front].c.size());i++)
				ans[mqueue[front].c[i]]=mqueue[front].l;
			front=(front+1)%(K+5000);
			continue;
		}
		int mid=(mqueue[front].l+mqueue[front].r)/2;
		if(T>mid)
			T=1,bit.Init();
		for(;T<=mid;T++)
			if(op[T].l<=op[T].r)
				bit.Change(op[T].l,op[T].r,op[T].w);
			else
				bit.Change(op[T].l,m,op[T].w),
				bit.Change(1,op[T].r,op[T].w);
		vector <int> l,r;
		for(int i=0;i<int(mqueue[front].c.size());i++)
		{
			long long t_ans=0,now=mqueue[front].c[i];
			for(int j=0;j<int(a[now].size());j++)
			{
				t_ans+=bit.Query(a[now][j]);
				if(t_ans>inf) break;
			}
			if(t_ans>=w[now])
				l.push_back(now);
			else
				r.push_back(now);
		}
		mqueue[tail].l=mqueue[front].l,mqueue[tail].r=mid,mqueue[tail++].c=l;
		tail%=(K+5000);
		mqueue[tail].l=mid+1,mqueue[tail].r=mqueue[front].r,mqueue[tail++].c=r;
		tail%=(K+5000);
		front=(front+1)%(K+5000);
	}
	
	for(int i=1;i<=n;i++)
		if(ans[i]==K+1)
			printf("NIE\n");
		else
			printf("%d\n",ans[i]);
	//cerr<<clock()-t<<endl;
	return 0;
}

```





---

