# [ICPC 2021 Macao R] LCS Spanning Tree

## 题目描述

给定一个有 $n$ 个顶点的完全无向图和 $n$ 个字符串 $s_1, s_2, \cdots, s_n$，连接顶点 $i$ 和 $j$ 的边的权重等于字符串 $s_i$ 和 $s_j$ 的最长公共子串（LCS）的长度。计算此图上任意生成树的最大总权重。

一个字符串的子串可以通过从该字符串的开头和/或结尾删除一些（可能为零）字符来获得。例如，“maca”、“aca” 和“cau”都是“macau”的子串，而“acu”不是。

## 样例 #1

### 输入

```
4
icpc
macau
regional
contest```

### 输出

```
4```

## 样例 #2

### 输入

```
3
ababa
babab
aba```

### 输出

```
7```

# 题解

## 作者：Register_int (赞：3)

先来考虑我们需要什么来求最大生成树。根据 Kruskal 的过程，我们需要将边按边权从大到小插入图中。本题的两点间边权为点上的字符串的 LCS 长度，不妨将所有串放到广义 SAM 上。

建出自动机后，首先预处理出自动机上每一个节点对应的串的编号，然后按长度排序，枚举每个子树里的点，自底向上合并。

然而这样显然是 $n^2$ 的，如何优化？考虑我们处理完一个节点后，并不在乎转移时由他所在 parent 树的子树内的哪个节点合并。所以处理完一个节点后，任取一个在节点对应的子树内的点上传到父亲即可。

之后的步骤与 Kruskal 相同，瓶颈在于并查集，时间复杂度 $O(n\alpha(n))$。实现没有使用基数排序。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e6 + 10;
const int MAXM = 4e6 + 10;

int t[MAXN][26], pos[MAXN], cnt = 1;

inline 
void add(string s, int d) {
	int len = s.length(), k = 1;
	for (int i = 0; i < len; i++) {
		if (!t[k][s[i] - 'a']) t[k][s[i] - 'a'] = ++cnt;
		k = t[k][s[i] - 'a'];
	}
}

int ch[MAXM][26], fa[MAXM], len[MAXM];

int tot = 1;

inline 
void insert(char c, int k, int &last) {
	int p = k; len[last = ++tot] = len[p] + 1;
	for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = last;
	if (!p) return fa[last] = 1, void();
	int q = ch[p][c];
	if (len[p] + 1 == len[q]) return fa[last] = q, void();
	len[++tot] = len[p] + 1;
	for (int i = 0; i < 26; i++) ch[tot][i] = ch[q][i];
	fa[tot] = fa[q], fa[q] = fa[last] = tot;
	for (; ch[p][c] == q; p = fa[p]) ch[p][c] = tot;
}

queue<int> q; vector<int> g[MAXM];

inline 
void build() {
	q.push(1), pos[1] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; i++) {
			if (!t[u][i]) continue;
			insert(i, pos[u], pos[t[u][i]]), q.push(t[u][i]); 
		}
	}
}

int p[MAXN];

int find(int k) {
	return k == p[k] ? k : p[k] = find(p[k]);
}

int n, a[MAXM]; ll ans;

string s[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= n; i++) cin >> s[i], add(s[i], i); build();
    for (int i = 1; i <= n; i++){
        for (int j = 0, k = 1; j < s[i].size(); j++){
            g[k = ch[k][s[i][j] - 'a']].push_back(i);
        }
    }
	for (int i = 2; i <= tot; i++) a[i] = i;
	sort(a + 2, a + tot + 1, [](int x, int y) { return len[x] > len[y]; });
	for (int i = 2; i <= tot; i++) {
		for (int j = 1, u, v; j < g[a[i]].size(); j++) {
			u = find(g[a[i]][j - 1]), v = find(g[a[i]][j]);
			if (u != v) p[u] = v, ans += len[a[i]];
		}
		if (fa[a[i]]) g[fa[a[i]]].push_back(g[a[i]][0]);
	}
	printf("%lld", ans);
}
```

---

## 作者：sunkuangzheng (赞：2)

$\textbf{P9664}$

> - 给定 $n$ 个字符串 $s_1,s_2,\ldots,s_n$，构造 $n$ 个点的无向完全图 $G$，边 $i,j$ 的边权是 $\operatorname{LCS}(s_i,s_j)$，其中 $\operatorname{LCS}$ 指最长公共**子串**。
> - 求 $G$ 的最大生成树边权和。
> - $1 \le n,\sum |s_i| \le 2 \cdot 10^6$。

后缀数组做这题应该是最简单的吧。

回忆一下我们是怎么用 SA 求两串 $\operatorname{LCS}$ 的，我们是直接拼起来，然后枚举 $rk$ 相邻的归属串不同的两个后缀计算 $\operatorname{LCP}$ 后取 $\max$。

把所有 $s_i$ 拼起来用不同的分隔符隔开，我们有结论有用的边只有 $(sa_i,sa_{i+1})$ 这 $\mathcal O(\sum |s_i|)$ 条。考虑一条边 $(sa_i,sa_{i+k}) \; (k \ge 2)$，其边权等于 $(sa_i,sa_{i+1}),\ldots,(sa_{i+k-1},sa_{i+k})$ 边权的最小值，我们在 Kruskal 合并的过程中一定会先把中间的边都考虑完，而此时 $sa_i,sa_{i+k}$ 必然已经连通，因此 $(sa_i,sa_{i+k})$ 这条边没有用。

令 $m = \sum |s_i|$，时间复杂度 $\mathcal O(m \log m)$。

---

## 作者：lfxxx (赞：0)

介绍两种做法。

下文 $n = \sum |S_i|$。

## 基于广义后缀自动机的做法

将所有串插入广义后缀自动机，合并两个串的代价是两个串各选一个点（前缀），其 LCA 代表的节点的长度最大值，考虑去模拟 Kruskal 的过程，我们按照长度从大往小枚举节点，将这个节点自身挂着的颜色和儿子子树内挂着的颜色合并，看似不好维护，实则我们发现儿子一定比父亲先处理，因此实际上儿子子树内只会有一种颜色，暴力合并，并查集维护即可做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6+114;
struct SAM{
    int fa,len;
    int son[26];
}nd[maxn<<1];
int rt,lst,tot;
vector<int> col[maxn<<1];
vector<int> E[maxn<<1];
int fa[maxn];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
void ins(char c,int id){
    if(nd[lst].son[c-'a']==0){
        int u=++tot,v=lst;
        col[u].push_back(id);
        lst=u;
        nd[u].len=nd[v].len+1;
        while(v!=0&&nd[v].son[c-'a']==0) nd[v].son[c-'a']=u,v=nd[v].fa;
        if(v==0){
            nd[u].fa=rt;
        }else{
            int q=nd[v].son[c-'a'];
            if(nd[q].len==nd[v].len+1){
                nd[u].fa=q;
            }else{
                int nq=++tot;
                nd[nq]=nd[q];
                nd[nq].len=nd[v].len+1;
                while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
                nd[u].fa=nd[q].fa=nq;
            }
        }
    }else{
        int v=lst,q=nd[v].son[c-'a'];
        if(nd[q].len==nd[v].len+1){
            col[q].push_back(id);
            lst=q;
        }else{
            int nq=++tot;
            lst=nq;
            nd[nq]=nd[q];
            col[nq].push_back(id);
            nd[nq].len=nd[v].len+1;
            while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
            nd[q].fa=nq;
        }
    }   
}
int p[maxn<<1];
void dfs(int u){
    p[u]=u;
    for(int v:E[u]) dfs(v);
}
bool cmp(int x,int y){
    return nd[x].len>nd[y].len;
}
int C[maxn<<1];
long long ans;
void solve(){
    sort(p+1,p+tot+1,cmp);
    for(int i=1;i<=tot;i++){
        int u=p[i];
        if(col[u].size()>0) C[u]=found(col[u][0]);
        for(int j=1;j<col[u].size();j++){
            int v=col[u][j];
            v=found(v);
            if(C[u]==0){
                C[u]=v;
            }
            if(v!=C[u]){
                ans+=nd[u].len;
                fa[v]=C[u];
            }
        }
        for(int v:E[u]){
            C[v]=found(C[v]);
            if(C[v]==0) continue;
            if(C[u]==0) C[u]=C[v];
            if(C[v]!=C[u]){
                ans+=nd[u].len;
                fa[C[v]]=C[u];
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    rt=++tot;
    lst=rt;
    for(int i=1;i<=t;i++){
        lst=rt;
        fa[i]=i;
        string S;
        cin>>S;
        for(char x:S) ins(x,i);
    }
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
    dfs(rt);
    solve();
    cout<<ans<<'\n';
    return 0;
}
```

## 基于后缀数组的做法

考虑将每个串后面加个分割字符然后拼起来，合并两个串的代价是两个串各选一个后缀，其 LCP 的最小值，还是考虑去模拟 Kruskal 的过程，当我们加入后缀 $i,j$ 构成的边时，其权值是 $\min_{k=rk_i+1}^{rk_j} h_k$，由于是从大往小枚举，而你将区间范围减少后 $\min$ 一定不减，所以其实可以认为 $rk_i,rk_j$ 之间所有的区间代表的边都在加入 $i,j$ 前被加入，也就是这条边无用，除非 $rk_j = rk_i+1$，也就是我们只需要对这 $O(n)$ 条边跑一遍 Kruskal 即可，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e6+214;
int n;
int T;
int S[maxn];
int x[maxn],y[maxn],sa[maxn],t[maxn];
int h[maxn];
int id[maxn];
int m;
int fa[maxn];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
int s[maxn];
void resort(){
    for(int i=1;i<=m;i++) t[i]=0;
    for(int i=1;i<=n;i++) t[x[i]]++;
    for(int i=1;i<=m;i++) t[i]+=t[i-1];
    for(int i=n;i>=1;i--) sa[t[x[y[i]]]--]=y[i];
}
bool cmp(int x,int y){
    return h[x]>h[y];
}
long long ans;
void build(){
    for(int i=1;i<=n;i++){
        x[i]=S[i],y[i]=i;
    }
    resort();
    for(int k=1;k<=n;k<<=1){
        int p=0;
        for(int i=n-k+1;i<=n;i++) y[++p]=i;
        for(int i=1;i<=n;i++){
            if(sa[i]>k) y[++p]=sa[i]-k;
        }
        resort();
        swap(x,y);
        x[sa[1]]=p=1;
        for(int i=2;i<=n;i++){
            x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
        }
        m=p;
    }
    int k=0;
    for(int i=1;i<=n;i++){
        if(k>0) k--;
        while(S[i+k]==S[sa[x[i]-1]+k]) k++;
        h[x[i]]=k;
    }
    for(int i=1;i<=n;i++) s[i]=i;
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++){
        int p=s[i];
        if(p!=1){
            int u=found(id[sa[p-1]]),v=found(id[sa[p]]);
            if(u!=v){
                fa[u]=v;
                ans+=h[p];
            }   
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    m=maxn-1;
    for(int i=1;i<=T;i++){
        fa[i]=i;
        string s;
        cin>>s;
        for(char x:s) S[++n]=x,id[n]=i;
        S[++n]='z'+i,id[n]=i;
    }
    build();
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：柳易辰 (赞：0)

## 题意

给定 $n$ 个字符串 $S_1,\dots,S_n$，和一张 $n$ 个点的**有边权完全图**，连接点 $i$ 和点 $j$ 的边的边权为 $\text{LCS}(S_i,S_j)$。其中 $\text{LCS}$ 表示**最长公共子串**。求这张图的**最大生成树边权和**。

$1\leqslant n\leqslant \sum|S|\leqslant 2\times 10^6$

&nbsp;

## 思路

多个串的 $\text{LCS}$ 问题，考虑 $\text{SAM}$。建一个**广义 $\text{SAM}$**，在上面做**最大生成树**。

对于广义 $\text{SAM}$ 上的一个节点，我们可以维护经过此点的字符串集合。节点 $p$ 对应的字符串长度区间为 $[l_{fp}+1,l_p]$，由于要求最大生成树，可以认为该节点的长度即为 $l_p$。如果节点 $p$ 对应的字符串集合中有多个元素，那么可以认为这些字符串之间存在边权为 $l_p$ 的边。

类似于 $\text{Kruskal}$ 的本原理，直接**贪心**，按照 $l_p$ 从大到小遍历每个节点，如果一个节点维护的字符串集合在图上对应的点不联通，直接连边即可，联通性用**并查集**维护。

当然，维护字符串集合也有一定的小细节，因为在广义 $\text{SAM}$ 中，孩子节点的信息可以更新父亲节点，所以集合需要向上合并，直接维护是 $O(n^2)$ 的。但考虑到 $l_p>l_{fp}$，也就是说孩子节点一定比父亲节点先遍历到，那么此时孩子维护的字符串集合在图上已经联通，只需要向上合并任意一个字符串即可。

时间复杂度 $O(n\alpha(n))$，空间复杂度 $O(n|\sum|)$。

&nbsp;

## 代码

```cpp
#include <vector>
#include <stdio.h>
using namespace std;
typedef const int ci; ci _(4000004); vector<int> v[_];
int a, b(1), c[_][26], e[_], f[_], g[_], h[_], l[_]; char s[_ >> 1];
void insert(ci d) // 在线建广义 SAM
{
    int p(a);
    if (int q(c[p][d]); q) {
        if (l[p] + 1 == l[q]) a = q;
        else {
            l[a = ++b] = l[p] + 1; f[b] = f[q]; f[q] = b;
            for (int i(0); i < 26; ++i) c[b][i] = c[q][i];
            for (; c[p][d] == q; p = f[p]) c[p][d] = b;
    }   } else {
        l[a = ++b] = l[p] + 1;
        for (; p && !c[p][d]; p = f[p]) c[p][d] = a;
        if (!p) f[a] = 1;
        else if (l[p] + 1 == l[q = c[p][d]]) f[a] = q;
        else {
            l[++b] = l[p] + 1; f[b] = f[q]; f[a] = f[q] = b;
            for (int i(0); i < 26; ++i) c[b][i] = c[q][i];
            for (; c[p][d] == q; p = f[p]) c[p][d] = b;
}   }   }
int find(const int p) { return p ^ e[p] ? e[p] = find(e[p]) : p; } // 并查集
int main()
{
    int n; scanf("%d", &n);
    for (int i(1); i <= n; e[i] = i, ++i)
    {
        scanf("%s", s + 1); int m(a = 1); while (s[m]) ++m; --m;
        for (int j(1); j <= m; s[j++] = 0) insert(s[j] - 'a'), v[a].emplace_back(i);
    }
    for (int i(1); i <= b; ++i) ++g[l[i]];
    for (int i(1); i <= b; ++i) g[i] += g[i - 1];
    for (int i(b); i; --i) h[g[l[i]]--] = i; // 按 l 排序
    long long w(0);
    for (int i(b); i; --i) if (ci j(h[i]); !v[j].empty())
    {
        for (int k : v[j]) if (find(k) != find(v[j].back())) w += l[j], e[find(k)] = find(v[j].back()); // 连边
        v[f[j]].emplace_back(v[j].back()); // 更新父节点信息
    }
    return !printf("%lld\n", w);
}
```

---

