# Lexichromatography

## 题目描述

Pak Chanek loves his faculty, the Faculty of Computer Science, University of Indonesia (Fasilkom). He wants to play with the colours of the faculty's logo, blue and red.

There is an array $ a $ consisting of $ n $ elements, element $ i $ has a value of $ a_i $ . Pak Chanek wants to colour each element in the array blue or red such that these following conditions are satisfied:

- If all blue elements are formed into a subsequence $ ^\dagger $ and so are all the red elements, the blue subsequence is strictly less than the red subsequence lexicographically $ ^\ddagger $ .
- Array $ a $ does not have any subarray that is imbalanced. A subarray is imbalanced if and only if there is a value $ k $ such that the absolute difference between the number of blue elements with value $ k $ and the number of red elements with value $ k $ in this subarray is $ 2 $ or more.
- Note that it is possible to colour every element of the array the same colour.

How many different colourings satisfy all those conditions? Since the answer can be very big, print the answer modulo $ 998\,244\,353 $ . Two colourings are different if and only if there is at least one element that is blue in one colouring, but red in the other.

 $ ^\dagger $ A subsequence of an array is a sequence that can be obtained from the array by deleting some elements (possibly none), without changing the order of the remaining elements.

 $ ^\ddagger $ Let $ p $ and $ q $ be two different sequences. Sequence $ p $ is said to be lexicographically less than sequence $ q $ if and only if $ p $ is a prefix of $ q $ or there is an index $ i $ such that $ p_j=q_j $ holds for every $ 1\leq j<i $ , and $ p_i<q_i $ . In particular, an empty sequence is always lexicographically less than any non-empty sequence.

## 说明/提示

In the first example, the $ 3 $ ways for colouring all elements from index $ 1 $ to index $ 8 $ are:

- Blue, red, red, blue, blue, red, red, blue.
- Blue, red, red, red, blue, blue, red, blue.
- Red, red, blue, blue, blue, red, red, blue.

As an example, if we colour the elements from index $ 1 $ to index $ 8 $ to be red, red, blue, red, red, blue, blue, blue, it is not valid colouring, because for subarray $ a[2..6] $ , there are $ 0 $ blue elements with value $ 3 $ and $ 2 $ red elements with value $ 3 $ , making subarray $ a[2..6] $ an imbalanced subarray.

## 样例 #1

### 输入

```
8
1 3 1 2 3 2 3 3```

### 输出

```
3```

## 样例 #2

### 输入

```
1
265```

### 输出

```
1```

# 题解

## 作者：EuphoricStar (赞：9)

这说明你的能力还不足以维持 IM。

显然 balanced 的充要条件是，对于每个值，染色一定是 RB 交替。然后一种值只会有先染红或先染蓝两种情况。

然后还剩下字典序严格小于的条件。我场上的想法是枚举 $\text{LCP}$，然后推出来一个巨大麻烦做法，根本写不出来。

但是实际上字典序严格小于就是诈骗。考虑遇到第一个红蓝组成的子序列不等的值，此时我们存在唯一一种是否交换这两种颜色的方案，使得红子序列字典序严格小于（或大于）蓝子序列。

所以，如果设 $a$ 为红小于蓝的方案数，$b$ 为红大于蓝的方案数，$c$ 为红等于蓝的方案数（这里均指字典序），$k$ 为序列中出现的不同的值的个数，那么有 $a = b, a + b + c = 2^k$，所以 $a = b = \frac{2^k - c}{2}$。问题来到如何求 $c$。

既然红等于蓝，那么如果有一种值出现奇数次就寄了。

然后我们考虑把每种值第奇数次出现和第偶数次出现的位置连起来，这样组成了若干条线段，并且线段的左端点和右端点染的颜色一定不同。

若线段存在包含关系，那么一定不能做到字典序相等。

否则，对于一对相交的线段，一定是形如 $l_1 < l_2 < r_1 < r_2$ 的形式，那么由字典序相等的限制，可知此时 $l_2$ 位置的颜色和 $l_1$ 位置的颜色相等。那么 $a_{l_1}$ 和 $a_{l_2}$ 这两种值先染红还是先染黑的选择是一样的。那么最后我们会得到若干个等价类，设等价类的个数为 $d$，那么 $c = 2^d$。

时间复杂度 $O(n \log n)$。

[code](https://codeforces.com/contest/1876/submission/227263858)

---

## 作者：Alex_Wei (赞：5)

#### *[CF1876D Lexichromatography](https://www.luogu.com.cn/problem/CF1876D)

被杀死了。

约定：当提到 “下标” 时，谈论的是 $a$ 的下标。当提到 “位置” 时，谈论的是同一种颜色的数组成的序列的下标。

第二个条件等价于：将值相同的下标按顺序取出来，相邻两个下标的颜色相反。因此，对于每个值，只有两种染色方案：要么蓝色开头，要么红色开头。

染色方案取反导致字典序大小关系取反，所以答案就等于染色方案数减去使得字典序相同的染色方案数，再除以 $2$（关键）。前者等于 $2$ 的不同的数的个数次幂，对于后者，可以这样考虑：

称两个下标匹配表示它们的 $a$ 值相等，颜色不同但位置相同。一对匹配 $(x, y)$（其中 $x$ 是蓝色）有两种方向：$x < y$ 或 $x > y$。

按位置顺序考虑所有匹配，如果第 $i$ 个位置的匹配 $(x_i, y_i)$ 和第 $i + 1$ 个位置的匹配 $(x_{i + 1}, y_{i + 1})$ 的方向不同，不妨设 $x_i < y_i$ 且 $y_{i + 1} < x_{i + 1}$，那么 $x_i < y_i < y_{i + 1} < x_{i + 1}$。因此，将所有匹配方向相同的极长段取出，每个极长段都对应 $a$ 的一段下标，且该下标区间内每个值都出现了偶数次。

反过来，称一个序列是好的，当且仅当其中每个数都出现了偶数次。如果 $a$ 不是好的，显然方案数为 $0$。考虑 $a$ 的长度最小的好的前缀，那么这段前缀中 **如果存在合法匹配**，则所有匹配的方向相同：若不同，则根据上述分析，存在更小的好的前缀，矛盾。将这段前缀删去，剩余序列也是好的，继续考虑它的长度最小的好的前缀，以此类推。由此可得原序列的分割，一个下标只会和同一段的下标匹配，且同一段的匹配方向相同，不同段的匹配方向可以不同。

考虑第二个条件对匹配的约束。由于值相同的所有下标的颜色是蓝红交替的，对应到匹配上就是：值相同的所有匹配的方向相同。由此可定义一个值的方向为它的所有匹配的方向。

结合上述两条限制，考虑用并查集维护所有值的等价类，其中两个值等价当且仅当这两个值的方向必须相同。考虑分割得到的每一段，那么这一段所有出现的值的方向必须相同，用并查集将它们合并。

需要注意，每一段不一定存在合法匹配，如序列 $\{1, 2, 2, 1\}$。若某一段不存在合法匹配，则方案数为 $0$。同一段内两种颜色等价，可以这样检查：维护两个序列 $x, y$，依次考虑当前段的每个数 $a_i$。若 $|x| > |y|$ 且 $x_{|y| + 1} = a_i$，则将 $a_i$ 加入 $y$，否则加入 $x$。这样，一个匹配合法 **当且仅当** 最终的 $x, y$ 长度相等。

进一步地，可以通过该方法求出分割的每一段：当 $|x| = |y|$ 时，说明找到一个合法段，将 $x$ 内所有值合并，并清空 $x, y$。如果分割的某一段不合法或者原序列不合法，那么最终 $|x|\neq |y|$（否则就找到了一组合法匹配，但一定不存在合法匹配），否则最终 $x, y$ 一定为空，这就使得我们不需要首先显式地找出分割的每一段再分别判定，而是通过该方法最终的 $x, y$ 直接判断是否存在合法匹配。

时间复杂度 $\mathcal{O}(n\log n)$ 或 $\mathcal{O}(n\alpha(n))$ 或 $\mathcal{O}(n)$（连边后求连通块数量）。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 998244353;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- templates above ----------

constexpr int N = 2e5 + 5;

int n, a[N], fa[N];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
vector<int> x, y;
void mian() {
  cin >> n;
  int tot = 0, cnt = 0;
  for(int i = 1; i <= n; i++) cin >> a[i], tot += !fa[a[i]], fa[a[i]] = a[i];
  for(int i = 1; i <= n; i++) {
    if(x.size() > y.size() && x[y.size()] == a[i]) y.push_back(a[i]);
    else x.push_back(a[i]);
    if(x.size() == y.size()) {
      int z = find(x.front());
      for(int it : x) fa[find(it)] = z;
      x.clear(), y.clear();
    }
  }
  if(x != y) return cout << ksm(2, tot - 1) << "\n", void();
  for(int i = 1; i < N; i++) cnt += find(i) == i;
  cout << (ksm(2, tot - 1) + mod - ksm(2, cnt - 1)) % mod << "\n";
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  while(T--) mian();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：樱雪喵 (赞：5)

被诈骗了 & 不能觉得不会下分就过完 C 摆烂啊！

## Description

给定长度为 $n$ 的序列 $a$，要求将序列每个位置染成红色或蓝色，且满足以下条件：

- 将染成红色和蓝色的数分别拼成两个序列，蓝色序列的字典序小于红色；
- $a$ 的每个子段都满足对于子段内任意的 $x$，$a_i=x$ 的所有位置 $i$ 染成红色和蓝色的数量相差不超过 $1$。

求不同的染色方案数，答案对 $998\,244\,353$ 取模。$n,a_i\le 2\times 10^5$。

## Solution

有字典序大小的限制是不好计算答案的，但是这条性质是诈骗。对于任意一种两序列不相等的染色方案，我们把红蓝对调一下，发现这两种方案里一定恰好有一个满足字典序的限制。

也就是说在满足第二条限制的情况下，设总染色方案数为 $All$，两序列相等的方案数为 $cnt$，则 $ans=\frac{All-cnt}{2}$。

第二条限制实际就是说我们对于每个 $x$，把 $a_i=x$ 的位置取出来拼成一个序列，序列里相邻的两个数颜色相反。令不同的 $a_i$ 为 $col$，对于每种 $a_i$ 确定第一个的颜色就可以确定所有，即 $All=2^{col}$。

考虑如何求红蓝序列相同的方案数。

首先如果某种 $a_i$ 出现了奇数次就直接寄了，否则我们把 $a_i$ 相同的位置从左到右两两分组形成一些线段，限制是每条线段的左右端点不同色。

分类讨论线段 $[a,b]$ 和 $[c,d]$ 的位置关系。  
如果两条线段没有交集，它们怎么染色互不影响；如果有包含关系，怎么染色都不能让序列相等，令 $cnt=0$。  
否则就是它们有交集的情况，设 $a<c<b<d$。那么 $a,c$ 一定同色，$b,d$ 一定同色。

发现我们的限制的形式都是某两点颜色相同 / 相反，使用形如食物链一题的扩展域并查集维护。那么设连通块个数为 $block$，则 $cnt=2^{block}$。

实现上，我们对每个线段不用向所有与它有交的线段连边。因为两个与它有交的线段之间也有交，它们一定之前已经连通。所以在其中随便找一个连即可，这样时间复杂度就对了，为 $O(n\log n)$。

```cpp
#define int long long 
const int N=4e5+5,mod=998244353;
const int inv2=((mod+1)>>1);
int n,a[N];
int lst[N],tot[N],fa[N];
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y)
{
    if(find(x)==find(y)) return;
    fa[find(x)]=find(y);
}
struct node{int l,r;} e[N];
vector<int> t[N];
int cnt,all=1,ans=1,b[N];
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=b[i]=read();
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    for(int i=1;i<=(n<<1);i++) fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        if(lst[a[i]])
        {
            merge(lst[a[i]],i+n),merge(lst[a[i]]+n,i);
            if(tot[a[i]]&1) e[++cnt]={lst[a[i]],i};
        }
        tot[a[i]]++,lst[a[i]]=i;
    }
    for(int i=1;i<=cnt;i++) t[e[i].l].push_back(e[i].r);
    for(int i=1;i<=n;i++) if(tot[i]) all=all*2%mod;
    for(int i=1;i<=n;i++) if(tot[i]&1) {printf("%lld\n",all*inv2%mod);return 0;}
    set<int> s;
    for(int i=1;i<=n;i++)
    {
        for(auto j:t[i])    
        {
            if(s.upper_bound(j)!=s.end()) {printf("%lld\n",all*inv2%mod);return 0;}
            if(!s.empty())
            {
                int r=*s.begin();
                merge(j,r),merge(j+n,r+n);
            }
            s.insert(j);
        }
        s.erase(i);
    }
    for(int i=1;i<=n;i++) if(find(i)==i) ans=(ans<<1)%mod;
    ans=(all-ans+mod)%mod*((mod+1)/2)%mod;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：_ZSR_ (赞：2)

### [CF1876D Lexichromatography](https://www.luogu.com.cn/problem/CF1876D)

首先，我们考虑字典序的约束。乍一看不会做，其实细想一下就会发现，任意两个不相同的序列一定有一个字典序更小。这样的话就启发我们用容斥，拿总方案数减去序列相同的方案数。再来看另外一个约束。这个约束就是说对于所有值相同的位置，一定是红蓝交替的。

看懂了两个约束后那么就考虑怎么求答案。假设有 $cnt$ 种不同的值，那么总方案数为 $2^{cnt}$。主要是如何求两个序列相同的方案数。显然，如果某个值出现了奇数次那必然没有满足的方案。不然的话，我们就把所有值相同的位置两两配对。如果两条线段 $[a,b],[c,d]$ 没有交集，那么它们怎么染色都互不相关。如果有一个包含于另一个，那么就无解。如果相交，那么一定是 $a,c$ 同色，$b,d$ 同色。所以问题就可以转化成给定一些相同和不同的关系，求满足条件的方案数。这就是典型的扩域并查集。

假设最后剩下 $b$ 个联通快，那么两个序列相同的方案数就为 $2^b$。最后拿总方案数减去相同的方案数就是答案了。

code 
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10,mod=998244353;
int n,m;
ll ans=1,inv;
int a[N],cnt[N],pre[N],fa[N<<1],another[N];
struct Seg{
    int l,r;
}seg[N];
vector<int> num;
set<int> S;
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void merge(int x,int y)
{
    x=find(x),y=find(y);
    if (x!=y) fa[x]=y;
}
inline ll ksm(ll a,int b)
{
    ll res=1;
    while (b)
    {
        if (b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]),num.emplace_back(a[i]);
    sort(num.begin(),num.end());
    num.erase(unique(num.begin(),num.end()),num.end());
    for (int i=1;i<=n;++i) a[i]=lower_bound(num.begin(),num.end(),a[i])-num.begin()+1;
    for (int i=1;i<=(n<<1);++i) fa[i]=i;
    for (int i=1;i<=n;++i)
    {
        if (pre[a[i]])
        {
            merge(pre[a[i]]+n,i),merge(pre[a[i]],i+n);
            if (cnt[a[i]]&1) seg[++m]={pre[a[i]],i};
        }
        ++cnt[a[i]],pre[a[i]]=i;
    }
    inv=ksm(2,mod-2);
    for (int i=1;i<=n;++i) if (cnt[i]) ans=ans*2%mod;
    for (int i=1;i<=n;++i) 
    {
        if (cnt[i]&1)
        {
            printf("%lld\n",ans*inv%mod);
            return 0;
        }
    }
    for (int i=1;i<=m;++i) another[seg[i].l]=seg[i].r;
    for (int i=1;i<=n;++i)
    {
        if (another[i])
        {
            if (S.upper_bound(another[i])!=S.end())
            {
                printf("%lld\n",ans*inv%mod);
                return 0;
            }
            if (S.size())
            {
                int j=*S.begin();
                merge(another[i],j),merge(another[i]+n,j+n);
            }
            S.insert(another[i]);
        }
        S.erase(i);
    }
    ll res=1;
    for (int i=1;i<=n;++i) if (find(i)==i) res=res*2%mod;
    printf("%lld\n",(ans-res+mod)%mod*inv%mod);
    return 0;
}
```


---

## 作者：蒟蒻君HJT (赞：1)

先考虑第二个条件。容易发现对于数值相同的若干数字，必须红蓝间隔地染色。假设一共出现了 $m$ 种不同的数字。则共有 $2^m$ 种方案。

假设红蓝字典序相等的染色方案为 $x$ 种。

那么对于任意一种字典序不相等的染色方案，和其相反的方案，二者必有其一满足条件一，因此合法方案是 $\displaystyle \frac{2^m-x}{2}$ 种。

考虑求出红蓝字典序相等的染色方案数 $x$。首先每个数字必须出现偶数次。称两个数字匹配，当且仅当它们分别在红蓝序列中下标相同的位置。则匹配方案一定确定。

匹配共有 $n/2$ 组。看作线段 $[l_i,r_i],1\leq i\leq n/2$。则若存在两线段互相包含，$x$ 为 $0$。这个的求法是维护 $m_i$ 表示左端点在 $i$ 及其左边的线段，右端点的最大值。若 $m_{l_i-1}>r_i$，则有包含的情况。

对于没有线段互相包含的情况，可能会存在相交的线段。假设是 $[l_i,r_i],[l_j,r_j],l_i<l_j<r_i<r_j$。可知 $a_{l_i}$ 与 $a_{l_j}$ 颜色必须相同，否则顺序不对。建一个初始边集为空的 $2\times 10^5$ 个点的无向图 $G$。对于这样的 $a_{l_i}$ 与 $a_{l_j}$，在 $a_{l_i}$ 与 $a_{l_j}$ 之间连边。则 $x=2^t$，$t$ 为存在出现在序列中的数字的连通块个数。

显然不能暴力连边。考虑实时维护一个 ```std::set``` 表示前 $i$ 个数字中，匹配的数字在 $i$ 之后的所有数值。则对于 $[l_i,r_i]$，对 ```std::set``` 中任意一个元素连边即可。

[for reference only.](https://codeforces.com/contest/1876/submission/227193641)

---

## 作者：Prophesy_One (赞：0)

大家的题解为啥都要用扩展域并查集哇，普通的并查集就可以呀。

从条件入手，对于染色，每个值的下标集合是独立的，而且它合法当且仅当它是红蓝交替的，即每个值有 $2$ 种染色方案。

于是问题转化成了：记不同值种类数为 $k$，求 $2^k$ 种染色方案中有多少个合法方案。

先忽略颜色，如果一个方案划分得到的两个序列不同，那么这种划分一定对应着一个合法方案和一个不合法方案。即存在一个字典序更大的，将其染成红的即可。

那我们得到了思路：序列不同的划分数不好求，那我们只需求序列相同的划分数 $S$，用序列总划分数 $\frac{2^k}{2}=2^{k-1}$ 减去 $S$ 即可。

若存在某个值出现了奇数次，则不存在这样的方案。

否则所有值都出现了偶数次，将第 $2k+1$ 次和第 $2k+2$ 次相连看作一条线段，对线段间的位置关系讨论：

若线段不相交，则它们之间不会产生影响；

相交的线段染色顺序就锁死了，即若存在两条线段 $(l,r),(a,b)$ 满足 $l<a<r<b$，那么 $col_l=col_a$，更进一步的，$val_l,val_a$ 的染色顺序相同；

若线段为包含关系，对比上一种情况发现不存在这样的方案。

所以我们只需要维护相交的线段，用并查集维护哪些值的染色顺序是相同的，不同连通块之间是独立的，记块数为 $count$，那么划分数为 $\frac{2^{count}}{2}=2^{count-1}$，那么最后的答案即为 $2^{k-1}-2^{count-1}$。

[link](https://codeforces.com/contest/1877/submission/285124047)

---

## 作者：_Diu_ (赞：0)

小清新题目。

题目大意：

给一个长度为 $n$ 的序列，要求将其划分成两个子序列 $A,B$，要求：

- $A$ 的字典序严格小于 $B$。

- 不存在原序列上的一个区间内某个颜色在 $A,B$ 中出现次数只差 $\ge2$。

求方案数对 $998244353$ 取模。

---

容易发现第二个条件要求每种颜色染色是 `01` 交替。

假设有 $m$ 种颜色，那么答案实际上是 $\frac{2^m-same}{2}$，因此我们要求的实际上是划分成相同两个序列的方案数。

首先如果某种颜色出现奇数次，那么显然不存在相同情况。

否则和[喵 2](https://www.luogu.com.cn/problem/P9139) 类似，我们发现对于一种颜色，设它的出现位置分别为 $b_1,b_2,\dots,b_{2k}$，那么在两个序列中，$b_1,b_2$ 会互相对应，$b_3,b_4$ 会互相对应。因此我们强制要求 $(b_3,b_4)$ 和 $(b_1,b_2)$ 颜色不同，那么并不影响相同方案的存在性。

因此问题变成一个长度为 $2n$ 的序列，每种颜色出现两次，问是否能划分成两个完全相同的序列。对于每种颜色找到 $l_i,r_i$，如果这些 $l_i,r_i$ 没有包含关系那么就合法。因为如果存在包含关系，那么两种颜色在两个序列中出现的先后顺序不同；否则我们可以把所有 $l_i$ 划分到一个序列；所有 $r_i$ 划分到一个序列就是一种方案。

现在我们要求方案数了。其实我们实际上是找 $l_i,r_i$ 之间是否会互相影响。其实容易发现，两个区间相离则互相不影响。但是如果同色那么还是会影响，因此可以用并查集维护连通块，先把相交的区间合并，再把颜色相同的区间合并。

但是我赛时降智了，直接用线段树维护剩下的颜色，每次拿出一个颜色出来，把 $[b_1,b_2],[b_3,b_4],\dots$ 中的颜色标记为一个等价类。每次找完当前颜色后如果还有颜色就随便找一个计数器加一，最终答案就是 $2^k$。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10,p=998244353,inv2=p+1>>1;
int T,n,a[N];
int lst[N];
struct node{
	int l,r;
	bool operator<(const node h){
		if(l^h.l)return l<h.l;
		return r>h.r;
	}
}b[N];
int c[N],vis[N];
int qpow(int x,int y=p-2){
	int m=1;
	for(;y;y>>=1,x=1ll*x*x%p)if(y&1)m=1ll*m*x%p;
	return m;
}
vector<int> g[N];
namespace seg{
	int mx[N<<2];
	#define ls (o<<1)
	#define rs (o<<1|1)
	void bld(int o,int l,int r){
		mx[o]=r;
		if(l==r)return;
		int mid=l+r>>1;
		bld(ls,l,mid),bld(rs,mid+1,r);
	}
	void upd(int o,int l,int r,int x){
		if(l==r)return void(mx[o]=0);
		int mid=l+r>>1;
		if(x<=mid)upd(ls,l,mid,x);
		else upd(rs,mid+1,r,x);
		mx[o]=max(mx[ls],mx[rs]);
	}
	int qry(int o,int l,int r,int x,int y){
		if(mx[o]==0)return 0;
		if(x<=l&&r<=y)return mx[o];
		int mid=l+r>>1;
		if(x>mid)return qry(rs,mid+1,r,x,y);
		if(y<=mid)return qry(ls,l,mid,x,y);
		return max(qry(ls,l,mid,x,y),qry(rs,mid+1,r,x,y));
	}
}
int st[N],tp;
void ins(int x){
	for(int v:g[x])seg::upd(1,1,n,v);
	st[++tp]=x;
}
void del(int x){
	for(int i=0;i<g[x].size();i+=2){
		int l=g[x][i],r=g[x][i+1],v=a[seg::qry(1,1,n,l,r)];
		while(v!=0)ins(v),v=a[seg::qry(1,1,n,l,r)];
	}
}
signed main(){
	scanf("%d",&n);
	int tot=0,m=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(lst[a[i]])b[++tot]={lst[a[i]],i},lst[a[i]]=0;
		else lst[a[i]]=i;
		if(!g[a[i]].size())++m;
		g[a[i]].push_back(i);
	}
	bool flg=0;
	for(int i=1;i<N;i++)if(lst[i])flg=1;
	if(!flg){
		for(int i=1;i<=tot;i++){
			if(b[i-1].l>b[i].l)flg=1;
		}
	}
	int ans=qpow(2,m);
	if(!flg){
		int k=0;
		seg::bld(1,1,n);
		int x=a[seg::qry(1,1,n,1,n)];
		while(x!=0){
			ins(x);++k;
			while(tp)--tp,del(st[tp+1]);
			x=a[seg::qry(1,1,n,1,n)];
		}
		ans=(ans-qpow(2,k)+p)%p;
	}
	ans=1ll*ans*inv2%p;
	printf("%d\n",ans);
}
```

---

