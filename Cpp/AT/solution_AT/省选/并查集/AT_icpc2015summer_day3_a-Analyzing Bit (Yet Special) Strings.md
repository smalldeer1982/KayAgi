# Analyzing Bit (Yet Special) Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2015summer-day3/tasks/icpc2015summer_day3_a



# 题解

## 作者：sunkuangzheng (赞：0)

$\textbf{AT\_icpc2015summer\_day3\_a}$

> - 给定 $01$ 串 $s$，寻找一个合法子串 $t$ 满足其出现次数乘长度最大。
> - 我们定义一个字符串 $t$ 是合法的，当且仅当：
>    - $t$ 的每一个前缀里 $0$ 的数量大于等于 $1$ 的数量，每一个后缀里 $1$ 的数量大于等于 $0$ 的数量。
> - $|s| \le 2 \cdot 10^5$。

容易发现一个字符串是合法的，当且仅当将 $0$ 视作 $1$，$1$ 视为 $-1$ 后满足和为 $0$ 且前缀和非负。

> - 由条件 $1$，其所有前缀的前缀和非负。
> - 由条件 $1,2$，全局的 $1$ 的数量和 $-1$ 的数量相等。

那么我们对原串求前缀和，容易对每个 $l$ 二分一个 $R$ 满足 $\max(sm_l,\ldots,sm_R) \ge sm_{l-1}$，则以 $l$ 开头的所有合法端点 $r$ 需要满足 $sm_r = sm_{l-1},l \le r \le R$。

建后缀数组，并查集维护 $\text{Beginpos}$，对于每个 $\text{Beginpos}$ 维护任意一个起点 $l_x$，则右端点 $r_x$ 有额外限制 $r_x \le l_x + len_x - 1$，其中 $len_x$ 是这个等价类的长度，那么在这个范围内二分出最大的 $r_x$ 即可。

时间复杂度 $\mathcal O(n \log n)$。

使用 `atcoder::suffix_array` 和 `atcoder::segtree`，代码非常短。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 28.05.2024 17:31:57
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
#include <atcoder/string>
#include <atcoder/segtree>
const int N = 5e5+5;
using namespace std;
int T,n,sa[N],rk[N],h[N],p[N],sm[N],r[N],fa[N],nxt[N],tp,siz[N],le[N],lf,len; string s; vector<int> gr[N]; ll ans;
int fd(int x){return x == fa[x] ? x : fa[x] = fd(fa[x]);}
bool sb(int x){return x >= tp;}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> s,n = s.size();
    auto _sa = atcoder::suffix_array(s);
    vector<int> *g = gr + n;     s = " " + s; 
    atcoder::segtree<int,[](int a,int b){return min(a,b);},[](){return (int)1e9;}> sg(n + 1);
    for(int i = 1;i <= n;i ++) rk[sa[i] = _sa[i-1] + 1] = i,sm[i] = sm[i - 1] + (s[i] == '1' ? -1 : 1),
        sg.set(i,sm[i]),g[sm[i]].push_back(i);
    for(int i = 1,k = 0;i <= n;h[rk[i ++]] = k) for(k --,k = max(k,0);s[i + k] == s[sa[rk[i] - 1] + k];k ++);
    for(int i = 1;i <= n;i ++) tp = sm[i-1],nxt[i] = sg.max_right<sb>(i);
    auto mg = [&](int u,int v,int w){
        u = fd(u),v = fd(v);
        if(u != v) siz[u] += siz[v],fa[v] = u,le[u] = w;
        int fk = sm[sa[u]] - 1;
        int it = lower_bound(g[fk].begin(),g[fk].end(),min(le[u] + sa[u],nxt[sa[u]])) - g[fk].begin() - 1;
        if(it < 0 || g[fk][it] <= sa[u]) return ; int t = g[fk][it];
        ll tmp = 1ll * siz[u] * (t - sa[u] + 1);
        if(tmp > ans) ans = tmp,lf = sa[u],len = t - sa[u] + 1;
    }; iota(p+1,p+n+1,1),sort(p+1,p+n+1,[&](int x,int y){return h[x] > h[y];});
    for(int i = 1;i <= n;i ++) le[i] = n - sa[i] + 1,siz[i] = 1,fa[i] = i;
    for(int i = 1;i <= n;i ++) mg(i,i,1e9);
    for(int i = 1;i <= n;i ++){
        int u = p[i] - 1,v = p[i];
        if(u) mg(u,v,h[v]);
    }cout << ans << "\n";
    cout << s.substr(lf,len) << "\n";
}
```

---

