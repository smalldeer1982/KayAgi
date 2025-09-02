# Game with Two Trees

## 题目描述

The Smart Beaver from ABBYY has come up with a new developing game for children. The Beaver thinks that this game will help children to understand programming better.

The main object of the game is finite rooted trees, each of their edges contains some lowercase English letter. Vertices on any tree are always numbered sequentially from $ 1 $ to $ m $ , where $ m $ is the number of vertices in the tree. Before describing the actual game, let's introduce some definitions.

We'll assume that the sequence of vertices with numbers $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ ( $ k>=1 $ ) is a forward path, if for any integer $ i $ from $ 1 $ to $ k-1 $ vertex $ v_{i} $ is a direct ancestor of vertex $ v_{i+1} $ . If we sequentially write out all letters from the the edges of the given path from $ v_{1} $ to $ v_{k} $ , we get some string ( $ k=1 $ gives us an empty string). We'll say that such string corresponds to forward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ .

We'll assume that the sequence of tree vertices with numbers $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ ( $ k>=1 $ ) is a backward path if for any integer $ i $ from $ 1 $ to $ k-1 $ vertex $ v_{i} $ is the direct descendant of vertex $ v_{i+1} $ . If we sequentially write out all the letters from the edges of the given path from $ v_{1} $ to $ v_{k} $ , we get some string ( $ k=1 $ gives us an empty string). We'll say that such string corresponds to backward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ .

Now let's describe the game that the Smart Beaver from ABBYY has come up with. The game uses two rooted trees, each of which initially consists of one vertex with number $ 1 $ . The player is given some sequence of operations. Each operation is characterized by three values ( $ t $ , $ v $ , $ c $ ) where:

- $ t $ is the number of the tree on which the operation is executed ( $ 1 $ or $ 2 $ );
- $ v $ is the vertex index in this tree (it is guaranteed that the tree contains a vertex with this index);
- $ c $ is a lowercase English letter.

The actual operation is as follows: vertex $ v $ of tree $ t $ gets a new descendant with number $ m+1 $ (where $ m $ is the current number of vertices in tree $ t $ ), and there should be letter $ c $ put on the new edge from vertex $ v $ to vertex $ m+1 $ .

We'll say that an ordered group of three integers ( $ i $ , $ j $ , $ q $ ) is a good combination if:

- $ 1<=i<=m_{1} $ , where $ m_{1} $ is the number of vertices in the first tree;
- $ 1<=j,q<=m_{2} $ , where $ m_{2} $ is the number of vertices in the second tree;
- there exists a forward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ such that $ v_{1}=j $ and $ v_{k}=q $ in the second tree;
- the string that corresponds to the forward path in the second tree from vertex $ j $ to vertex $ q $ equals the string that corresponds to the backward path in the first tree from vertex $ i $ to vertex $ 1 $ (note that both paths are determined uniquely).

Your task is to calculate the number of existing good combinations after each operation on the trees.

## 说明/提示

After the first operation the only good combination was $ (1,1,1) $ . After the second operation new good combinations appeared, $ (2,1,2) $ and $ (1,2,2) $ . The third operation didn't bring any good combinations. The fourth operation added good combination $ (1,3,3) $ . Finally, the fifth operation resulted in as much as three new good combinations — $ (1,4,4) $ , $ (2,3,4) $ and $ (3,1,4) $ .

## 样例 #1

### 输入

```
5
1 1 a
2 1 a
1 2 b
2 1 b
2 3 a
```

### 输出

```
1
3
3
4
7
```

# 题解

## 作者：myee (赞：4)

### 思路

考虑答案的两种描述：
* $t_1$ 的叶到根的路径，与 $t_2$ 的祖先往叶的路径相等。
* $t_1$ 的根到叶的路径，与 $t_2$ 的叶往上的路径相等。

第二种信息更好维护，考虑按第二种方式计算答案。

先假设 $t_2$ 一开始给定，不会修改。

我们考虑加 $t_1$ 中叶子的操作，如何快速查询答案变化量。

对 $t_2$ 做[树上后缀排序](https://www.luogu.com.cn/problem/P5353)，查询操作可以描述为在后缀数组上查找一段合法的区间。

再考虑上加 $t_2$ 叶子的操作，我们把操作离线。

然后我们把每次的加 $t_1$ 叶子操作带来的贡献分为两类。
1. 其加入时带来的贡献。
2. 其对未来的贡献。

其加入时的贡献可以在后缀数组上二分找到合法区间，查询其中时间戳不大于插入时间的数的个数；同时给区间打上 “当区间内加入新节点时，对答案整体加 $1$” 的标记。

这个可以用 BIT 维护。

于是核心问题在于：如何二分？

注意到其二分的左右端点均不大于父亲，我们只用考虑新的一位带来的贡献。

这个东西就容易二分了；查找区间内向上为某位的方案数，可以用树上 $k$ 级祖先的方法快速查询。

不过如果用树剖实现 $k$ 级祖先，常数会很小，比 $O(1)$ 的长剖还要快些。

因此核心问题在于树上后缀排序，这个可能会恶心一点。

如果用后缀平衡树实现会很难写（要手写替罪羊树），而且一个不巧就爆 `double` 精度了。

直接写倍增法，即可在 $O(n\log n)$ 时间内离线建出树上后缀数组。

总复杂度 $O(n\log n)$ 或 $O(n\log^2n)$，瓶颈在二分。

空间复杂度为线性，且与字符集无关。

（听说有高明哈希做法与高明广义 SAM 做法）


### Code

这个能做到 $n_1,n_2\le300000$ 的情况。

```cpp
uint FathA[300005],FathB[300005],SA[300005],Rank[300005],tp1,tp2;
chr C_A[300005],C_B[300005];
voi build(){
    static uint Fath[300005],Fath2[300005];
    uint n=tp2;for(uint i=0;i<n;i++)Fath[i]=FathB[i],SA[i]=i;
    std::sort(SA,SA+n,[&](uint a,uint b){return C_B[a]<C_B[b];});
    for(uint i=0;i<n;i++)Rank[SA[i]]=i&&C_B[SA[i]]==C_B[SA[i-1]]?Rank[SA[i-1]]:i;
    for(uint len=1;len<n;len<<=1){
        static std::pair<uint,uint>W[300005];
        bol ok=true;
        for(uint i=0;i<n;i++){
            W[i]={Rank[i],~Fath[i]?Rank[Fath[i]]+1:0u};
            if(~Fath[i])Fath2[i]=Fath[Fath[i]],ok=false;
            else Fath2[i]=Fath[i];
        }
        for(uint i=0;i<n;i++)Fath[i]=Fath2[i];
        if(ok)break;
        static uint Cnt[300005];
        for(uint i=0;i<=n;i++)Cnt[i]=0;
        for(uint i=0;i<n;i++)Cnt[W[i].second]++;
        for(uint i=1;i<=n;i++)Cnt[i]+=Cnt[i-1];
        for(uint i=n-1;~i;i--)Rank[--Cnt[W[i].second]]=i;
        for(uint i=0;i<n;i++)Cnt[i]=0;
        for(uint i=0;i<n;i++)Cnt[W[i].first]++;
        for(uint i=1;i<n;i++)Cnt[i]+=Cnt[i-1];
        for(uint i=n-1;~i;i--)SA[--Cnt[W[Rank[i]].first]]=Rank[i];
        for(uint i=0;i<n;i++)Rank[SA[i]]=i&&W[SA[i]]==W[SA[i-1]]?Rank[SA[i-1]]:i;
    }
    for(uint i=0;i<n;i++)SA[i]=i;
    std::sort(SA,SA+n,[&](uint a,uint b){return Rank[a]<Rank[b];});
    for(uint i=0;i<n;i++)Rank[SA[i]]=i;
}
uint Siz[300005],Heavy[300005],Dep[300005],Rot[300005],Dfn[300005],Back[300005];
voi build2(){
    static std::vector<uint>Son[300005];
    static uint Fath[300005],Cur[300005];
    uint n=tp2;
    for(uint i=0;i<n;i++)Fath[i]=FathB[i],Heavy[i]=Rot[i]=Cur[i]=-1,Siz[i]=1;
    for(uint i=1;i<n;i++)Dep[i]=Dep[Fath[i]]+1,Son[Fath[i]].push_back(i);
    for(uint i=n-1;i;i--){
        if(!~Heavy[Fath[i]]||Siz[Heavy[Fath[i]]]<Siz[i])Heavy[Fath[i]]=i;
        Siz[Fath[i]]+=Siz[i];
    }
    std::vector<uint>P{0};uint cnt=0;
    while(P.size()){
        uint p=P.back();
        if(!~Rot[p])Rot[p]=p;
        if(!~Cur[p]){
            Cur[p]=0,Back[Dfn[p]=cnt++]=p;
            if(~Heavy[p]){Rot[Heavy[p]]=Rot[p],P.push_back(Heavy[p]);continue;}
        }
        while(Cur[p]<Son[p].size()&&Son[p][Cur[p]]==Heavy[p])Cur[p]++;
        if(Cur[p]==Son[p].size()){P.pop_back();continue;}
        P.push_back(Son[p][Cur[p]++]);
    }
}
chr kthFath(uint p,uint d){
    if(d>=Dep[p])return'\0';
    while(Dfn[p]-Dfn[Rot[p]]<d)d-=Dfn[p]-Dfn[Rot[p]]+1,p=FathB[Rot[p]];
    return C_B[Back[Dfn[p]-d]];
}
uint L[300005],R[300005];
voi build3(){
    static uint Dep[300005];
    L[0]=0,R[0]=tp2,Dep[0]=-1;
    for(uint p=1;p<tp1;p++){
        Dep[p]=Dep[FathA[p]]+1;
        uint l=L[FathA[p]],r=R[FathA[p]];
        while(l<r){
            uint mid=(l+r)>>1;
            if(kthFath(SA[mid],Dep[p])>=C_A[p])r=mid;else l=mid+1;
        }
        L[p]=l;
        r=R[FathA[p]];
        while(l<r){
            uint mid=(l+r)>>1;
            if(kthFath(SA[mid],Dep[p])>C_A[p])r=mid;else l=mid+1;
        }
        R[p]=l;
    }
}
namespace BIT1{
    const uint Lim=400000;
    ullt B[Lim+5];
    voi add(uint p,ullt v){
        p++;while(p<=Lim)B[p]+=v,p+=lowbit(p);
    }
    ullt find(uint l,uint r){
        ullt ans=0;
        while(r)ans+=B[r],r-=lowbit(r);
        while(l)ans-=B[l],l-=lowbit(l);
        return ans;
    }
}
namespace BIT2{
    const uint Lim=400000;
    ullt B[Lim+5];
    voi add(uint l,uint r,ullt v){
        l++,r++;
        while(l<=Lim)B[l]+=v,l+=lowbit(l);
        while(r<=Lim)B[r]-=v,r+=lowbit(r);
    }
    ullt find(uint p){
        p++;
        ullt ans=0;
        while(p)ans+=B[p],p-=lowbit(p);
        return ans;
    }
}
uint Op[600005];ullt Ans[600006];
int main()
{
    uint q;scanf("%u",&q);Op[0]=1,Op[1]=2,tp1=tp2=1,q+=2,FathA[0]=FathB[0]=-1;
    for(uint i=2;i<q;i++){
        scanf("%u",Op+i);
        if(Op[i]==1)scanf("%u%s",FathA+tp1,C_A+tp1),FathA[tp1++]--;
        else scanf("%u%s",FathB+tp2,C_B+tp2),FathB[tp2++]--;
    }
    build();
    build2();
    build3();
    for(uint i=0,p1=0,p2=0;i<q;i++){
        if(Op[i]==1){
            Ans[i]=BIT1::find(L[p1],R[p1]);
            BIT2::add(L[p1],R[p1],1);
            p1++;
        }
        else{
            Ans[i]=BIT2::find(Rank[p2]);
            BIT1::add(Rank[p2],1);
            p2++;
        }
    }
    for(uint i=1;i<q;i++)Ans[i]+=Ans[i-1];
    for(uint i=2;i<q;i++)printf("%llu\n",Ans[i]);
    return 0;
}
```


---

## 作者：MeteorFlower (赞：4)

[更好的阅读体验。](https://www.cnblogs.com/DRPLANT/p/CF207C3_solution.html)

脑子不够，科技来凑。

不过好像也没有用多么高级的科技……

首先这个题目很坏，它让你翻转 $S_{t_2}$。即从 $t_2$ 某个节点往下走到另一个节点的路径所表示的字符串。这个非常难以维护。因此我们不翻转 $S_{t_2}$，转而翻转 $S_{t_1}$。两者的效果是相同的。于是询问就变成了从 $t_1$ 的根走到某个节点的路径，以及从 $t_2$ 某个节点向上走的路径，两者相等的情况数。

由于节点只加不删，考虑算出加入每个节点会产生的贡献，最后再滚一遍前缀和得到答案。由于 $t_2$ 询问的是从某个节点向上的路径。考虑离线建出两棵树并把边权下放到点，对 $t_2$ 进行树上后缀排序。按深度从小到大处理每个 $t_1$ 节点 $i$。显然 $i$ 能够匹配到的 $t_2$ 的 SA 区间只会比其父亲更小。在其父亲能够匹配到的 SA 区间内二分。由于 $i$ 所代表的字符串长度只比其父亲多 1，所以在二分时只需要判断 $SA_{mid}$ 的第 $k$ 级祖先是否与 $i$ 的字符相等即可（$k=dep_i$，$dep_1=-1$，$dep_i=dep_{fa_i}+1$）。这样就可以得到每个 $t_1$ 节点 $i$ 能够匹配到的 $t_2$ 的 SA 区间。记作 $[L_i, R_i)$。

现在来具体分析一下插入一个节点时会产生的贡献。

当插入一个 $t_1$ 节点时：

1. 每个之前插入的能与其匹配的 $t_2$ 节点会对答案产生贡献。因此要记录 $rec1_i$ 表示 $SA_i$ 有无被插入。这部分是对 $rec1$ 进行一个区间求和。
2. 该点将与未来每个能与其匹配的 $t_2$ 节点产生贡献。考虑记录 $rec2_i$ 表示每个 $t_2$ 节点 $i$ 能与多少个 $t_1$ 节点匹配。这部分是对 $rec2$ 进行一次区间加 1。

当插入一个 $t_2$ 节点时：

1. 每个之前插入的能与其匹配的 $t_1$ 节点会对答案产生贡献。这部分是对 $rec2$ 进行一个单点求值。
2. 该点将与未来每个能与其匹配的 $t_1$ 节点产生贡献。这部分是对 $rec1$ 进行一次单点加 1。

以上操作均能用树状数组简单地维护。于是问题只剩下如何进行树上后缀排序了。因为我没有脑子，所以我直接用后缀平衡树了。感觉没那么难写。

若使用长剖求树上 k 级祖先，则复杂度 $O(n\log n)$。然而长剖常数太大，实际跑起来不如重剖。因此实现时使用了朴素的重剖求树上 k 级祖先。复杂度 $O(n\log^2 n)$。常数不大。

Code：
```cpp
constexpr int maxn = 100010;
int faA[maxn], faB[maxn], SA[maxn], Rank[maxn], *_p = SA, cntA, cntB, op[maxn];

typedef long long i64;
typedef unsigned long long u64;
constexpr u64 INF = 1ull << 62;
#define isNull(x) (x->son[0] == x)
char sA[maxn], sB[maxn];

struct Suffix_n {
  constexpr static double ALPHA = 0.75;
  Suffix_n *son[2];
  int id, size;
  u64 val;

  inline void pushup() {
    if (isNull(this))
      return;
    size = son[0]->size + son[1]->size + 1;
  }
  inline bool need_rebuild() {
    return ALPHA * size <= max(son[0]->size, son[1]->size);
  }
} *rec[maxn];

struct Suffix_t {
  constexpr static int SIZE = maxn;
  Suffix_n MemoryPool[SIZE], *const null = MemoryPool, *root = null, *pointer = null;
  Suffix_t() {
    rec[0] = null->son[0] = null->son[1] = null;
  }
  inline bool cmp(int a, int b) {
    return sB[a] ^ sB[b] ? sB[a] < sB[b] : rec[faB[a]]->val < rec[faB[b]]->val;
  }
  inline Suffix_n *allocate(int id, u64 num) {
    return *++pointer = {null, null, id, 1, num}, pointer;
  }
  vector<Suffix_n *> _need;
  void pre_rebuild(Suffix_n *r) {
    (r->son[0] != null) && (pre_rebuild(r->son[0]), 0), _need.emplace_back(r),
        (r->son[1] != null) && (pre_rebuild(r->son[1]), 0);
  }
  Suffix_n *rebuild_main(int left, int right, u64 L, u64 R) {
    if (left > right)
      return null;
    int mid     = (left + right) >> 1;
    u64 vmid    = (L + R) >> 1;
    Suffix_n *r = _need[mid];
    r->val      = vmid;
    r->son[0] = rebuild_main(left, mid - 1, L, vmid), r->son[1] = rebuild_main(mid + 1, right, vmid, R);
    r->pushup();
    return r;
  }
  inline void rebuild(Suffix_n *&r, u64 L, u64 R) {
    _need.clear(), pre_rebuild(r), r = rebuild_main(0, _need.size() - 1, L, R);
  }
  void insert(Suffix_n *&r, int id, u64 L = 0, u64 R = INF) {
    if (r == null) {
      rec[id] = r = allocate(id, (L + R) >> 1);
      return;
    }
    cmp(id, r->id) ? insert(r->son[0], id, L, r->val) : insert(r->son[1], id, r->val, R);
    r->pushup();
    if (r->need_rebuild())
      rebuild(r, L, R);
  }
  inline void dfs(Suffix_n *r) {
    (r->son[0] != null) && (dfs(r->son[0]), 0), *++_p = r->id, (r->son[1] != null) && (dfs(r->son[1]), 0);
  }
} Suffix;

basic_string<int> edge[maxn];
int size[maxn], fa[maxn], dep[maxn], son[maxn], top[maxn], dfn[maxn], MAP[maxn], _id, root;
void dfs1(int u, int _fa) {
  size[u] = 1, fa[u] = _fa, dep[u] = dep[_fa] + 1;
  for (const int &v : edge[u])
    dfs1(v, u), size[u] += size[v], (size[v] > size[son[u]]) && (son[u] = v);
}
void dfs2(int u, int _top) {
  dfn[u] = ++_id, MAP[_id] = u, top[u] = _top;
  if (!son[u])
    return;
  dfs2(son[u], _top);
  for (const int &v : edge[u])
    (v != son[u]) && (dfs2(v, v), 0);
}
inline char kthF(int x, int k) {
  if (dep[x] <= k)
    return 0;
  int tmp;
  while (k) {
    tmp = dep[x] - dep[top[x]] + 1;
    if (tmp <= k)
      x = fa[top[x]], k -= tmp;
    else
      return sB[MAP[dfn[x] - k]];
  }
  return sB[x];
}

int L[maxn], R[maxn];
inline void build() {
  for (int i = 1; i <= cntB; i++)
    Rank[SA[i]] = i;
  static int _dep[maxn];
  L[1] = 1, R[1] = cntB + 1, _dep[1] = -1;
  for (int i = 2; i <= cntA; i++) {
    _dep[i]  = _dep[faA[i]] + 1;
    int left = L[faA[i]], right = R[faA[i]], mid;
    while (left < right)
      mid = (left + right) >> 1, (kthF(SA[mid], _dep[i]) >= sA[i]) ? right = mid : left = mid + 1;
    L[i] = left, right = R[faA[i]];
    while (left < right)
      mid = (left + right) >> 1, (kthF(SA[mid], _dep[i]) > sA[i]) ? right = mid : left = mid + 1;
    R[i] = left;
  }
}

namespace BIT1 {
#define lowbit(x) (x & -x)
i64 tree[maxn];
inline void update(int id, int val) {
  for (int i = id; i <= cntB; i += lowbit(i))
    tree[i] += val;
}
inline i64 query(int l, int r) {
  l--, r--;
  i64 res = 0;
  for (int i = r; i; i -= lowbit(i))
    res += tree[i];
  for (int i = l; i; i -= lowbit(i))
    res -= tree[i];
  return res;
}
}  // namespace BIT1
namespace BIT2 {
i64 tree[maxn];
inline void update(int l, int r, int val) {
  for (int i = l; i <= cntB; i += lowbit(i))
    tree[i] += val;
  for (int i = r; i <= cntB; i += lowbit(i))
    tree[i] -= val;
}
inline i64 query(int id) {
  i64 res = 0;
  for (int i = id; i; i -= lowbit(i))
    res += tree[i];
  return res;
}
}  // namespace BIT2
i64 ANS[maxn];

int main() {
  int q;
  in(q);
  op[1] = 1, op[2] = 2, cntA = cntB = 1, q += 2;
  for (int i = 3; i <= q; i++)
    in(op[i]), (op[i] == 1) ? (cntA++, in(faA[cntA], sA[cntA])) : (cntB++, in(faB[cntB], sB[cntB]));

  for (int i = 1; i <= cntB; i++)
    Suffix.insert(Suffix.root, i), edge[faB[i]] += i;
  Suffix.dfs(Suffix.root), dfs1(1, 0), dfs2(1, 1);
  build();

  for (int i = 1, p1 = 0, p2 = 0; i <= q; i++)
    if (op[i] == 1)
      p1++, ANS[i] = BIT1::query(L[p1], R[p1]), BIT2::update(L[p1], R[p1], 1);
    else
      p2++, ANS[i] = BIT2::query(Rank[p2]), BIT1::update(Rank[p2], 1);
  for (int i = 2; i <= q; i++)
    ANS[i] += ANS[i - 1];
  for (int i = 3; i <= q; i++)
    out(ANS[i]), enter;
}
```


---

## 作者：Miraik (赞：2)

确定一个看上去较为简单的计数方式：对于 $t_1$ 上的每个根到节点上的路径，统计 $t_2$ 上节点到祖先的路径与其相等的方案数。

不妨先离线，得到 $t_1,t_2$ 的形态。考虑对 $t_1$ 建 trie，然后以 $t_2$ 上的每个节点为起点向上跳，看最多能在 $t_1$ 的 trie 树上匹配到哪个位置，假设 $t_2$ 上的节点 $u$ 最终匹配到了 trie 上的节点 $v$，那么 trie 上根到 $v$ 的路径上的所有节点与 $u$ 都可以产生贡献。

计算贡献是简单的，可以直接分别维护 $t_1$ 上之前的节点对 $t_2$ 上新节点的贡献与 $t_2$ 上之前的节点对 $t_1$ 上新节点的贡献，用两个树状树组就可以完成（分别只需要子树加单点查值与单点加子树求和）。

我们考虑怎么维护找匹配点的过程。

我们使用倍增+重剖维护这个过程。具体地，我们对 trie 树重剖一下，然后从 $t_2$ 上的节点 $u$ 向上跳使用倍增维护。每次在 trie 树一条重链上与 $t_2$ 当前节点倍增匹配，匹配到头再跳轻边，重复这个过程直到无法匹配即可。这个过程的复杂度是 $O(n\log^2 n)$ 的。

另一种做法（来自 [@_•́へ•́╬_ ](https://www.luogu.com.cn/user/90693) /bx）是将 trie 上节点的值对应位置存下来，匹配的时候二分一下就好。复杂度相同但是常数略大，不过应该会好写一些。

因此我们就在 $O(n\log^2 n)$ 的时间内解决了本题，瓶颈即找匹配点的过程。

代码比题解清楚。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
const int mod=998244353;
typedef long long ll;
int m,op[N],to[N],u,n1,n2,idx,a[N],b[N]; char ch; ll ans;
int val[N],siz[N],id[N],top[N],dfn[N],son[N],len[N],dep[N];
int lg[N],fa[17][N],h[N],pw[N],tr[N][27];
inline void dfs1(int u){
	siz[u]=1;
	for(int i=0;i<26;i++){
		int v=tr[u][i];
		if(!v) continue;
		val[v]=(131ll*val[u]+i+47)%mod;
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
inline void dfs2(int u){
	dfn[u]=++idx; id[idx]=u;
	if(!son[u]) return;
	dfs2(son[u]); len[u]=len[son[u]]+1;
	for(int i=0;i<26;i++){
		int v=tr[u][i];
		if(!v || v==son[u]) continue;
		dfs2(v);
	}
}
inline int find(int u,int v,int s){
	for(int i=lg[min(len[v],dep[u])];~i;i--)
	if((h[s]-h[fa[i][u]]+mod)%mod==1ll*val[id[dfn[v]+(1<<i)]]*pw[dep[fa[i][u]]]%mod)
	u=fa[i][u],v=id[dfn[v]+(1<<i)];
	if(u==1 || !tr[v][to[u]]) return v;
	return find(fa[0][u],tr[v][to[u]],s);
}
struct BIT{
	int c[N];
	#define lowbit(x) (x&(-x))
	inline void update(int x,int y){ while(x<=n1) c[x]+=y,x+=lowbit(x); }
	inline int query(int x){ int r=0; while(x) r+=c[x],x-=lowbit(x); return r; }
}T1,T2;
int main(){
	read(m); n1=n2=1; dep[1]=a[1]=1;
	pw[0]=1; for(int i=1;i<=m;i++) pw[i]=131ll*pw[i-1]%mod;
	for(int i=1;i<=m;i++){
		read(op[i]),read(u),getc(ch);
		if(op[i]==1){
			int ru=a[u]; n1++;
			if(!tr[ru][ch-'a'])
				tr[ru][ch-'a']=n1;
			a[n1]=tr[ru][ch-'a'];
		}
		else{
			n2++;
			fa[0][n2]=u;
			to[n2]=ch-'a';
			dep[n2]=dep[u]+1;
			h[n2]=(h[u]+(to[n2]+47ll)*pw[dep[u]])%mod;
		}
	}
	dfs1(1); dfs2(1);
	lg[0]=-1; for(int i=2;i<=m;i++) lg[i]=lg[i>>1]+1;
	for(int j=1;j<=lg[n2];j++)
		for(int i=1;i<=n2;i++)
			fa[j][i]=fa[j-1][fa[j-1][i]];
	b[1]=1; for(int i=2;i<=n2;i++) b[i]=find(i,1,i);
	T1.update(dfn[1],1); T1.update(dfn[1]+siz[1],-1);
	T2.update(dfn[b[1]],1); ans=1;
	for(int i=1,x=1,y=1;i<=m;i++){
		if(op[i]==1){
			int u=a[++x];
			ans+=T2.query(dfn[u]+siz[u]-1)-T2.query(dfn[u]-1);
			T1.update(dfn[u],1); T1.update(dfn[u]+siz[u],-1);
		}
		else{
			int u=b[++y];
			ans+=T1.query(dfn[u]);
			T2.update(dfn[u],1);
		}
		print(ans); putc('\n');
	}
	return 0;
}
```


---

## 作者：binbin_200811 (赞：1)

# [CF207C3 Game with Two Trees](https://www.luogu.com.cn/problem/CF207C3)

妙到家的树上字符串问题。

### 约定

* 树 $1$：$t_1$。

* 树 $2$：$t_2$。

* $S_{1/2}(i,l)$ 为树 $1/2$ 上节点 $i$ 沿父亲走经过 $l$ 条边所构成的字符串。
* $E_{1/2}(u,v)$ 为树 $1/2$ 上，连接节点 $u,v$ 的边的字符。
* $fa_{1/2}u$ 为树 $1/2$ 上 $u$ 的父亲。

### 前置

* trie 树
* 字符串哈希
* 树上倍增
* 树链剖分

### 思路

#### part 1：寻找对应点

我们先把树 $1$ 建成一棵 trie 树，把树 $2$ 建成一棵正常的树。

我们对于每个树 $2$ 上的点 $u$ 寻找一个第一颗树上的点 $i$（$l$ 为 $i$ 的深度，根深度为 $0$），满足：

* $S_1(i,l)=S_2(u,i)$。
* $l$ 最大。

两个条件必须都满足，由于树 $1$ 是一棵 trie 树，所以 $i$ 是唯一存在的，我们把这样的 $i$ 称为对应点。

我们可以枚举树 $2$ 的节点 $u$，节点 $i$ 从树 $1$ 的根开始，如果 $i$ 的儿子 $v$ 使得 $E_2(u,fa_2u)=E_1(rt,v)$，那么我们把 $u$ 向上走，把 $i$ 走向 $i$ 的儿子 $v$。

这样可以暴力的找到我们需要的点。

~~但是肯定也会获得 TLE 的好成绩~~。

我们考虑优化这个过程，可以树上的做字符串 hash 判断某一段链（从祖先到子孙）是否相等，现在要解决的问题是怎么速的爬树（寻找点）。

首先 $u$ 是向上跳，我们可以想到倍增，但 $i$ 需要向下，怎么解决呢？

其实 $i$ 的主要问题在于需要判断下一条边是否有需要的边，我们可以对树 $1$ 进行树链剖分，这样子每次肯定是向下走一条链，确定了 $i$ 的方向。

然后枚举 $k$（$k$ 从大到小，且 $2^k$ 小于 $i$ 所在重链向下的长度）表示 $u$ 向上爬 $2^k$ 个点，$i$ 向下跳 $2^k$ 个点，然后判断跳的这一段边的字符串是否相等，相等就跳过去。

如果 $1$ 个节点都跳不了，那么我们就手动判断 $i$ 是否可以向下，如果可以，就向下；如果不行，则 $i$ 点以是最优选择。

分析一下这里的复杂度，如果可以沿着重链向下跳，那么这条重链最多跳 $\log n$ 次。跳完重链或者重链无法向下以后，跳一条轻边，而根据树剖的性质，最多跳 $\log n$ 条轻边，也就是最多换 $\log n$ 条重链。

总时间复杂度 $O(\log^2 n)$。

```cpp
inline int fr(int u,int v,int s)//树 1 点 u；树 2 点 v
{
    for(int i=lg[min(len[v],dep[u])];~i;i--)
        if((h[s]-h[fa[u][i]]+mod)%mod==val[id[dfn[v]+(1<<i)]]*base[dep[fa[u][i]]]%mod)//沿重链跳
            u=fa[u][i],v=id[dfn[v]+(1<<i)];
    if(u==1||!tr[v][to[u]]) return v;//判断有没有轻边可以跳
    return fr(fa[u][0],tr[v][to[u]],s);//跳轻边
}
```

这里树 $1$ 是 trie 树进行了树剖，树 $2$ 是正常树进行了倍增。

#### part 2 反馈询问

求得了上面的对应点，我们要怎样利用对应点去求答案呢？

##### part 2.1 树 2 加入点

![](https://cdn.luogu.com.cn/upload/image_hosting/thdu904j.png)

假设这个是树 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/m50bkued.png)

这个是树 $2$。

现在树 $2$ 的 $9$ 号节点的对于点是树 $1$ 的 $6$ 号节点。

我们有 $S_1(6,5)=$`abccc`，有 $S_2(9,5)=$`cccba`。

假设其余节点已经加入，现在加入的节点是 $9$ 号节点。

那么 $9$ 号节点在树 $1$ 上的答案可以是 $1、2、3、4、5、6$ 号节点共 $6$ 个。

不难发现树 $1$ 上对于点所在的到根的链上的任意一个点都可以成为 $9$ 号点的答案。

也很好证明，因为树 $1$ 从上到下需要匹配树 $2$ 从下到上，那么树 $1$ 到对应点的每一个前缀，都是树 $2$ 向上爬的后缀。

但有些时候，树 $1$ 上的对应点可能还没有加入，所以我们对于树 $1$ 我们需要动态的维护一条链上的点是否加入。

这里可以搭配 dfn 序食用树状数组，每次插入一个树 $1$ 的节点，我们对于它子树这一个 dfn 序区间整体加 1，查询直接单点查询该点的值，是不是动态维护出了一条链上的节点。

##### part 2.2 树 1 加入节点

这个会稍微复杂一点点，我们还是先画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/r8capitw.png)

这棵树是树 $1$，圈住的红色点还没有加入。

至于边上的字母呢？~~这不重要~~。

假设图中蓝色的节点是被树 $2$ 上的节点定为对应点。

![](https://cdn.luogu.com.cn/upload/image_hosting/ebp8xuc1.png)

你说这种对应不可能？~~对不起，这也不重要~~。

假设我们现在插入了树 $1$ 中的 $2$ 号节点，那么所有在 $2$ 号节点的子树内，被树 $2$ 对应的次数就是 $2$ 号节点答案。

分析和 part 2.1 朴素情况下的分析一致。

每次树 $2$ 中插入一个节点，我们就向树 $1$ 对应点 dfn 序的位置加 $1$，每次查询区间查询子树即可。

这个就是单点修改区间查询。

还是可以食用树状数组。

```cpp
//T1 树 2 查询使用的；T2 是树 1 查询使用的
	b[1]=1;for(int i=2;i<=n2;i++) b[i]=fr(i,1,i);//求对应点
    T1.updata(dfn[1],1),T1.updata(dfn[1]+siz[1],-1);//区间加
    T2.updata(dfn[b[1]],1);//单点加
	ans=1;//两个 1 号节点互相匹配，答案为 1
    for(int i=1,x=1,y=1;i<=m;i++)
    {
        if(op[i]==1)//加入树 1 点
        {
            int u=a[++x];//a 为 trie 树上点编号
            ans+=T2.getsum(dfn[u]+siz[u]-1)-T2.getsum(dfn[u]-1);
            T1.updata(dfn[u],1),T1.updata(dfn[u]+siz[u],-1);
        }
        else//加入树 2 点
        {
            int u=b[++y];//b 为对应点编号
            ans+=T1.getsum(dfn[u]);
            T2.updata(dfn[u],1);
        }
        printf("%lld\n",ans);
    }
```

如果看不懂树状数组的话，也可以手搓线段树。

本部分复杂度 $O(n\log n)$。

总复杂度 $O(n\log^2 n)$。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define N 3e5
#define mod 998244353

const int maxn=3e5+5;

inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

struct treearray
{
    int tree[maxn];
    inline int lowbit(int x){return x&(-x);}
    inline void updata(int x,int y){for(;x<=N;x+=lowbit(x)) tree[x]+=y;}
    inline int getsum(int x){int sum=0;for(;x;x-=lowbit(x)) sum+=tree[x];return sum;}
}T1,T2;

int n1,n2,m;
int a[maxn],b[maxn];

int idx;
int tr[maxn][27],siz[maxn],hso[maxn],dfn[maxn],id[maxn],len[maxn];
int op[maxn*2],to[maxn],fa[maxn][20],dep[maxn];

int lg[maxn*2];
ll base[maxn*2],h[maxn],val[maxn];

ll ans;

inline void dfs1(int u)
{
    siz[u]=1;
    for(int i=0;i<26;i++)
    {
        int v=tr[u][i];
        if(!v) continue;
        val[v]=(131*val[u]+i+47)%mod;
        dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[hso[u]]) hso[u]=v;
    }
}
inline void dfs2(int u)
{
    dfn[u]=++idx;id[idx]=u;
    if(!hso[u]) return;
    dfs2(hso[u]);len[u]=len[hso[u]]+1;
    for(int i=0;i<26;i++)
    {
        int v=tr[u][i];
        if(!v||v==hso[u]) continue;
        dfs2(v);
    }
}
inline int fr(int u,int v,int s)
{
    for(int i=lg[min(len[v],dep[u])];~i;i--)
        if((h[s]-h[fa[u][i]]+mod)%mod==val[id[dfn[v]+(1<<i)]]*base[dep[fa[u][i]]]%mod)
            u=fa[u][i],v=id[dfn[v]+(1<<i)];
    if(u==1||!tr[v][to[u]]) return v;
    return fr(fa[u][0],tr[v][to[u]],s);
}

int main()
{
    // scanf("%d",&m);
    m=read();
    n1=n2=1;dep[1]=a[1]=1;
    base[0]=1;for(int i=1;i<=m;i++) base[i]=base[i-1]*131%mod;
    for(int i=1;i<=m;i++)
    {
        char c;int u;
        // scanf("%d%d",&op[i],&u);
        op[i]=read(),u=read();
        while(1){c=getchar();if('a'<=c&&c<='z') break;}
        if(op[i]==1)
        {
            n1++;
            if(!tr[a[u]][c-'a']) tr[a[u]][c-'a']=n1;
            a[n1]=tr[a[u]][c-'a'];
        }
        else
        {
            n2++;
            dep[n2]=dep[u]+1;fa[n2][0]=u;to[n2]=c-'a';
            h[n2]=(h[u]+(47ll+to[n2])*base[dep[u]])%mod;
        }
    }
    dfs1(1);dfs2(1);
    lg[0]=-1;for(int i=2;i<=m;i++) lg[i]=lg[i>>1]+1;
    for(int j=1;j<=lg[n2];j++) for(int i=1;i<=n2;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
    b[1]=1;for(int i=2;i<=n2;i++) b[i]=fr(i,1,i);
    T1.updata(dfn[1],1),T1.updata(dfn[1]+siz[1],-1);
    T2.updata(dfn[b[1]],1); ans=1;
    for(int i=1,x=1,y=1;i<=m;i++)
    {
        if(op[i]==1)
        {
            int u=a[++x];
            ans+=T2.getsum(dfn[u]+siz[u]-1)-T2.getsum(dfn[u]-1);
            T1.updata(dfn[u],1),T1.updata(dfn[u]+siz[u],-1);
        }
        else
        {
            int u=b[++y];
            ans+=T1.getsum(dfn[u]);
            T2.updata(dfn[u],1);
        }
        printf("%lld\n",ans);
    }
}
```

最后代码就懒得注释喽。

### 后记

实际上如果要做出这题，更多时候应该是先想：

1. 要怎么求答案得出对应点。
2. 对应点要怎么求得出树剖加倍增。

还是一道很有启发性的题目。

---

## 作者：向晚大魔王 (赞：1)

只用哈希就可以做的串串题好耶！

考虑这样的一个暴力：

- 如果要将 $n_2$ 增大 $1$，对于目标节点 $x$，提取出到根的串 $S_x$。
- 使用这个串插入 $T_1$，对于所有路径上的节点都 $+1$。
- 如果要将 $n_1$ 增大 $1$，直接查新增的点的权值即可。

考虑怎么快速维护匹配的过程，直接将 $T_1$ 离线之后树剖，对于每条重链求一个 LCP。

这需要一个树上后缀排序科技，不过不会也没关系，直接跳树上 $k$ 级祖先哈希也是 $O(n\log^3 n)$ 的。

实测跑的飞快，只需要 340ms。

```cpp
//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define ll long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int _=310000;
struct BIT
{
	int tr[310003];
	inline void add(int x,int k)
	{
		++x;
		while(x<=_) tr[x]+=k,x+=x&(-x);
		return ;
	}
	inline int find(int x)
	{
		int r=0;
		++x;
		while(x) r+=tr[x],x-=x&(-x);
		return r;
	}
}T1,T2;
int t1[300003][26],f1[300003],c1=1;
char o[300003];
int t2[300003][26],f2[300003],c2=1;
int op[600003];
int id1[300003],id2[300003];
int sz[300003],hs[300003],hid[300003];
void dfs1(int x)
{
	sz[x]=1;
	for(int i=0; i<26; ++i)
		if(t1[x][i])
			dfs1(t1[x][i]),sz[x]+=sz[t1[x][i]],
			(sz[t1[x][i]]>sz[hs[x]])
			&&(hid[x]=i,hs[x]=t1[x][i],0);
	return ;
}
const int p=1019260817;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
const int b=131,ib=qp(b,p-2);
int dfn[300003],to[300003];
int inv[300003],pw[300003];
int H[300003],len[300003],cb=1,N;
inline int H1(int l,int r)
{return 1ll*(p+H[r]-H[l-1])*inv[l-1]%p;}
void dfs2(int x)
{
	dfn[x]=++N,to[N]=x,
	H[N]=(H[N-1]+1ll*cb*hid[x])%p,cb=1ll*cb*131%p;
	if(hs[x]) dfs2(hs[x]),len[x]=len[hs[x]]+1;
	for(int i=0; i<26; ++i)
		if(t1[x][i]&&i!=hid[x])
			dfs2(t1[x][i]);
}
int dep[300003],f[300003][19],G[300003];
void dfs3(int x)
{
	G[x]=(G[f[x][0]]+1ll*inv[dep[x]]*(o[x]-'a'))%p;
	for(int i=1; i<19; ++i)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=0; i<26; ++i)
		if(t2[x][i])
			dep[t2[x][i]]=dep[x]+1,
			f[t2[x][i]][0]=x,
			dfs3(t2[x][i]);
}
int kth(int x,int y)
{
	for(int i=18; i>=0; --i)
		if((y>>i)&1) x=f[x][i];
	return x;
}
inline int G1(int x,int len)
{return 1ll*(p+G[x]-G[kth(x,len)])*pw[dep[x]]%p;}
signed main()
{
	int n1=1,n2=1,T=read();
	id1[1]=id2[1]=inv[0]=pw[0]=1;
	for(int i=1; i<=300000; ++i)
		inv[i]=1ll*inv[i-1]*ib%p;
	for(int i=1; i<=300000; ++i)
		pw[i]=1ll*pw[i-1]*b%p;
	for(int i=1,fa; i<=T; ++i)
	{
		char ch;
		op[i]=read(),fa=read(),ch=getchar();
		if(op[i]==1)
		{
			fa=id1[fa];
			if(!t1[fa][ch-'a'])
				t1[fa][ch-'a']=++c1,
				f1[c1]=fa;
			id1[++n1]=t1[fa][ch-'a'];
		}
		else
		{
			fa=id2[fa];
			if(!t2[fa][ch-'a'])
				t2[fa][ch-'a']=++c2,
				f2[c2]=fa,o[c2]=ch;
			id2[++n2]=t2[fa][ch-'a'];
		}
	}
	dfs1(1),dfs2(1),dfs3(1),T1.add(dfn[1],1);
	ll ans=1;
	for(int z1=1,z2=1,i=1; i<=T; ++i)
	{
		if(op[i]==1)
			ans+=T2.find(dfn[id1[++z1]]),
			T1.add(dfn[id1[z1]],1);
		else
		{
			int t=1;
			for(int i=id2[++z2]; i>=1; i=f2[i])
			{
				int l=1,r=min(len[t],dep[i]),res=0;
				while(l<=r)
				{
					int mid=(l+r)>>1;
					if(H1(dfn[t],dfn[t]+mid-1)==G1(i,mid))
						res=mid,l=mid+1;
					else r=mid-1;
				}
				i=kth(i,res),++res,
				ans+=T1.find(dfn[t]+res-1)
				-T1.find(dfn[t]-1),
				T2.add(dfn[t],1),
				T2.add(dfn[t]+res,-1),
				t=to[dfn[t]+res-1];
				if(i>1&&t1[t][o[i]-'a'])
					t=t1[t][o[i]-'a'];
				else break;

			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_edge_ (赞：0)

不懂啊，这题 1log 不是挺好想的么。

注意到在 $t_1$ 上的有用串仅有 $O(n)$ 个。

对于同一个节点延伸出来的权值相同的边，我们把他缩起来，然后每一个节点维护他被加一的时间，这样方便处理。
 
然后我们去定位 $t_2$ 上每一个点 $x$ 往上找到最浅的点 $l$，使得这个 $[l,x]$ 字符串出现过。

如果该字符串在 $t_1$ 出现过，假设是 $z$ 点，那么所有可能的点则是 $z$ 到根的那条链，然后到根查询 $\le d$ 的点，子树内查询 $\le d$ 的点，然后就搞个二维数点完事。

下面得 code 用了 map ，换成哈希表就是 1log 的。

[code](https://codeforces.com/problemset/submission/207/310496717)

---

