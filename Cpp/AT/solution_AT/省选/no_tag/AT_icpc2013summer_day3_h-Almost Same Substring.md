# Almost Same Substring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2013summer-day3/tasks/icpc2013summer_day3_h



# 题解

## 作者：xukehg (赞：0)

好题。

声明：$\operatorname{lens}$ 为 $s$ 的长度，$\operatorname{lent}$ 为 $t$ 的长度，$s$ 的下标从 $0$ 开始，$s[l,r]$ 表示 $s$ 在 $l$ 到 $r$ 范围内的子串，$\operatorname{lcp_{s,t}}$ 为两个字符串的最长公共前缀。

记 $s1_i$ 为 $s[0,i]$ 的反串，$s2_i$ 为 $s[i,\operatorname{lens} - 1]$，$\operatorname{ss}$ 为 $s$ 的反串，$\operatorname{tt}$ 为 $t$ 的反串。尝试将 $s[i,i + lent - 1]$ 去匹配 $t$，注意到该字串合法当且仅当 $\operatorname{lcp_{s2_i,t}} + \operatorname{lcp_{s1_{i + lent - 1},tt}} + 1 = \operatorname{lent} - 1$，这很明显是正确的。现在就变成了一个如何快速求 $\operatorname{lcp}$ 的问题。

考虑构造字符串 $tmp1 = s + t$ 并将其翻转，$tmp2 = t + s$，我们就可以用 exKMP 解决。

[记录。](https://atcoder.jp/contests/jag2013summer-day3/submissions/60412825)

---

## 作者：sunkuangzheng (赞：0)

$\textbf{AT\_icpc2013summer\_day3\_h}$

> - 给定串 $s,t$，问 $s$ 有多少长为 $|t|$ 的子串 $s'$ 满足 $s'$ 和 $t$ **恰好**有一个字符不同。
> - $1 \le |t| \le |s| \le 3\cdot10^5$，字符串只包含大小写字母。

你说的对，但是哈希将会臭名昭著。

我们先计算**至多**有一个字符的匹配数量，最后减去多算的。考虑枚举 $s',t$ 不同的字符在 $s$ 中的位置 $i$，则条件等价于寻找 $k_1,k_2$ 满足 $[k_1,i-1],[i+1,k_2]$ 是 $t$ 的前缀、后缀且 $k_2-k_1+1=|t|$ 的 $k_1,k_2$ 对数。这一部分的计算类似于 CF1801G，对 $t,t^R$ 建 **KMP 自动机**和其 fail 树，记 $p_1$ 是 $s$ 从前往后走到 $i-1$ 时在 $t$ 的 KMP 自动机上的位置，$p_2$ 是 $s$ 从后往前走到 $i+1$ 时在 $t^R$ 的 KMP 自动机上的位置，则 $k_1$ 应在 $t$ 的 $1 \sim p_1$ 的链上，$k_2$ 应在 $t^R$ 的 $1 \sim p_2$ 的链上，离线 BIT 即可。具体的，对 $t$ 的 fail 树 dfs，到 $u$ 时给 $t^R$ 的 fail 树 $n-u-1$ 子树加，然后处理 $u$ 点的询问单点查即可。

注意到我们会把 $t$ 和 $s$ 匹配的时候计入贡献 $|t|$ 次，因此计算 $t$ 在 $s$ 中出现多少次后减去这个次数乘 $|t|$ 即可。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 15.03.2024 09:11:02
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int n,ccnt,w1[N],w2[N],m; string s,t; ll ans;char mp[N]; vector<int> qu[N];
struct KMPAM{
    int ch[N][52],ed[N],fa[N],tot,dfn[N],cnt,siz[N]; vector<int> g[N];
    void ins(int x,string t){
        int s = 0;
        for(char c : t) ch[s][mp[c]] = ++tot,s = tot;
        ed[x] = s;
    }void build(){
        queue<int> q; 
        for(int i = 0;i < 52;i ++) if(ch[0][i]) q.push(ch[0][i]);
        while(q.size()){
            int u = q.front(); q.pop();
            for(int i = 0;i < 52;i ++)
                if(ch[u][i]) fa[ch[u][i]] = ch[fa[u]][i],q.push(ch[u][i]);
                else ch[u][i] = ch[fa[u]][i];
        }for(int i = 1;i <= tot;i ++) g[fa[i]].push_back(i);
    }void dfs(int u){
        dfn[u] = ++cnt,siz[u] = 1;
        for(int v : g[u]) dfs(v),siz[u] += siz[v];
    }
}A,AR;
struct fen{
    int t[N],re;
    void upd(int x,int p){for(;x <= AR.cnt;x += x & -x) t[x] += p;}
    int qry(int x){for(re = 0;x;x -= x & -x) re += t[x]; return re;}
    void rupd(int l,int r,int k){upd(l,k),upd(r+1,-k);}
}T;
void dfs(int u){
    int v = n - u - 1;
    if(v >= 0) T.rupd(AR.dfn[v],AR.dfn[v] + AR.siz[v] - 1,1);
    for(int r : qu[u]) ans += T.qry(AR.dfn[r]);
    for(int v : A.g[u]) dfs(v);
    if(v >= 0) T.rupd(AR.dfn[v],AR.dfn[v] + AR.siz[v] - 1,-1);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> s >> t,n = t.size(),m = s.size(),s = " " + s;
    for(int i = 0;i < 128;i ++) if(i >= 'A' && i <= 'Z' || i >= 'a' && i <= 'z')
        mp[i] = ccnt ++;
    A.ins(1,t),AR.ins(1,string(t.rbegin(),t.rend())); A.build(),AR.build(),A.dfs(0),AR.dfs(0);
    int p = 0;
    for(int i = 1;i <= m;i ++) p = A.ch[p][mp[s[i]]],w1[i] = p,ans -= (p == A.ed[1]);p = 0;
    ans *= n;
    for(int i = m;i >= 1;i --) p = AR.ch[p][mp[s[i]]],w2[i] = p;
    for(int i = 0;i < m;i ++) qu[w1[i]].push_back(w2[i+2]); dfs(0);
    cout << ans << "\n";
}
```

---

