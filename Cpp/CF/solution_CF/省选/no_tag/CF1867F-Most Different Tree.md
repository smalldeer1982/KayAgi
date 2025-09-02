# Most Different Tree

## 题目描述

Given a tree with $ n $ vertices rooted at vertex $ 1 $ , denote it as $ G $ . Also denote $ P(G) $ as the multiset of subtrees of all vertices in tree $ G $ . You need to find a tree $ G' $ of size $ n $ rooted at vertex $ 1 $ such that the number of subtrees in $ P(G') $ that are isomorphic to any subtree in $ P(G) $ is minimized.

A subtree of vertex $ v $ is a graph that contains all vertices for which vertex $ v $ lies on the path from the root of the tree to itself, as well as all edges between these vertices.

Two rooted trees are considered isomorphic if it is possible to relabel the vertices of one of them so that it becomes equal to the other, with the root of the first tree receiving the number of the root of the second tree.

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
1 2```

## 样例 #2

### 输入

```
3
1 2
1 3```

### 输出

```
1 2
2 3```

## 样例 #3

### 输入

```
4
1 2
1 3
3 4```

### 输出

```
1 2
2 3
3 4```

# 题解

## 作者：spdarkle (赞：6)

有意思的问题。设原树为 $G$，设 $n=|G|$。

手玩一下，不难发现，若子树 $T$ 与 $G$ 中任何一颗子树都不同构，那么对于任意树 $S$，其中 $T$ 是 $S$ 的子树，$S$ 同样不与 $G$ 中任何一颗子树同构。

进一步地，假设我们已经知道了一颗最小的 $T$，我们使得剩下的 $|G|-|T|$ 棵子树全部包含 $T$，则可以使得最大不构子树数为 $|G|-|T|+1$。这对应的构造方案就是构造长为 $|G|-|T|$ 的链，并将 $T$ 接在下面。

这显然是最优解，对这个解进行任何的改动都会导致答案变差。

那么进一步研究，可以得出 $|T_{\min}|$ 必然是一个极小的数字。为什么？设 $x=|T_{\min}|$，则设 $a_{i}$ 为 $i$ 个点构成的不同构树个数，设 $b_i$ 为 $i$ 个点构成的不同构二叉树的个数，则显然有 $a_{i}\ge b_{i}$，而我们知道后者是卡特兰数，一个增长为指数级的数列。

则必然有 $x< a_{m}$，其中 $a_{m}\ge |G|$ 且 $m$ 为满足条件的最小正整数。

这里可以推出 $x$ 的范围非常小。考虑枚举 $x$，判断是否可行。只要构造出了一个符合的 $T$，即可立即输出。

那么怎么判断呢？很简单，我们将 $x$ 可以构成的每一棵树全部枚举，然后依次判断是否同构即可。这个时间复杂度？

可以先预处理出 $G$ 中的不同构子树以便判断。

时间复杂度怎么说，设单次判断时间复杂度为 $t$，则总时间复杂度为 $O(nt)$。因为在暴力时最多枚举 $n$ 个树。

进一步地，具体实现怎么办？显然我们需要对一棵同构树进行哈希。

哈希方法不同，比较常见的有基于素数的哈希，这里介绍一种常数较大但绝无冲突的办法。（毕竟会有人对着代码卡哈希函数）

我们可以使用一个集合作为哈希函数。显然一个树必然是由更小的树组合而来。我们可以考虑对原树中每一棵不同构树标号，并且它所对应的集合为它的儿子的编号集合（注意是可重有序集）。

如下：

```cpp
#define ve vector<int>
map<ve ,int>h;
int id[N],n,t,cnt,num;
int get(ve &a){
	if(h.find(a)!=h.end())return h[a];
	int id=h.size();h[a]=id;
	return id;
}
void dfs(int u,int fa){
	ve a;a.clear();
	for(auto v:g[u]){
		if(v==fa)continue;
		dfs(v,u);
		a.push_back(id[v]);
	}
	sort(a.begin(),a.end());
	id[u]=get(a);cnt=max(cnt,id[u]);
	return ;
}
```

这样做常数是极大的，但总体时间复杂度没有影响。

然后我们考虑进行枚举拼凑这一步。先枚举 $x$ 的大小，然后我们用一个暴力的深度优先搜索找 $T$ 的子树，进行拼凑 $x$。只要最终组合的 $T$ 不存在同构树，那就找到了解，输出即可。

方案怎么输出？我们本身就记录了每一棵树的构成儿子，可以直接遍历这棵树，并且记录当前父亲编号进行输出。

注意最后如果搜不到，此时 $n$ 必然极小，直接输出原树即可。

[code](https://codeforces.com/contest/1867/submission/223148005)



---

## 作者：zzzYheng (赞：5)

#### 题意：

给定一棵大小为 $n$ 的有根树 $G$。

你要构造一棵大小也为 $n$ 的有根树 $G'$，使得 $G'$ 中存在最多的不与 $G$ 中任何子树同构的子树。

数据范围：$n \le 10^6$。

#### 思路：

重要观察：如果一个子树不与 $G$ 中任何子树同构，那么所有包含其的子树都不会与 $G$ 中的子树同构。

我得到这个观察的途径是考虑 $\text{dp}$，考虑子树合并的方式进行分步决策，容易发现如果其有一个儿子的子树不与任何 $G$ 中子树同构，那么它也就不会与任何 $G$ 中子树同构。

更进一步，我们一旦得到了一个不与 $G$ 中任何子树同构的子树，就可以直接把剩下所有点依次拼接，作为其所有祖先。这样剩下的所有点的子树就都不会与 $G$ 中的子树同构，一定是最优的。

所以现在的目标就是找到一个不与 $G$ 中的任何子树同构的最小子树。

因为包含 $k$ 个点的无标号有根树的个数是指数级别的，所以我们直接把前 $n + 1$ 小的所有无标号有根树全搜出来，然后用树哈希暴力判断即可。

搜索的话考虑按树的大小从小到大搜。

假设这次搜大小为 $k$ 的树，考虑把树分解为根和根的儿子的所有子树，问题等价于找出所有大小和为 $k-1$ 的无标号子树集合，只需要保证编号不降即可保证不重不漏。

复杂度：$\Theta(n\cdot f(n))$，$f(n)$ 是 $n$ 个节点无标号有根树个数函数的反函数，不会超过 $20$，当然这个复杂度远远跑不满。

---

## 作者：Kidding_Ma (赞：3)

当 $n=2$ 时，只能构造一条长度为 $2$ 的链。

当 $n>2$ 时，对于 $i$ $(1\le i\le n)$，以 $i$ 作为根的树记为 $h_i$，考虑枚举树找一个大小为 $s$ 的树 $t$，使得不存在任何一个 $h_i=t$，且 $s$ 尽可能小，然后从 $1$ 连一条链到该数的根节点。

这样可以保证构造出来的以 $1$ 到 $t$ 为根的树都和所给的不同。

使用树哈希。

C++ Code

```cpp
#include "bits/stdc++.h"

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const u64 mask = chrono::steady_clock::now().time_since_epoch().count();

u64 shift(u64 x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (n == 2) {
        cout << "1 2\n";
        return 0;
    }

    unordered_set<u64> st(1024);
    st.max_load_factor(0.25);

    function<u64(int, int)> dfs = [&](int cur, int pre) {
        u64 h = 1;
        for (auto &nex : g[cur]) {
            if (nex != pre) {
                h += shift(dfs(nex, cur));
            }
        }
        st.insert(h);
        return h;
    };  

    dfs(0, -1);

    vector<vector<int>> b(n);

    function<u64(int)> TreeHash = [&](int cur) {
        u64 h = 1;
        for (auto &nex : b[cur]) {
            h += shift(TreeHash(nex));
        }
        return h;
    };

    for (int s = 2; s <= n; s++) {
        function<void(int, int)> get = [&](int cur, int pre) {
            if (cur == s) {
                if (st.count(TreeHash(0))) {
                    return;
                }

                for (int i = 1; i <= n - s; i++) {
                    cout << i << ' ' << i + 1 << '\n';
                } 

                for (int i = 0; i < s; i++) {
                    for (auto &j : b[i]) {
                        cout << i + n - s + 1 << ' ' << j + n - s + 1 << '\n';
                    }
                }
                exit(0);
            }

            for (int i = pre; i < cur; i++) {
                b[i].push_back(cur);
                get(cur + 1, i);
                b[i].pop_back();
            }
        };

        get(1, 0);
    }

    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

考虑如何最小化答案。

发现叶子节点一定会造成贡献，所以说要最小化叶子，造一条链?

这是假的，考虑一条链的情况，把最后 $3$ 个点换成二叉树会更优，考虑刚刚的答案，则造链会更优。

我们考虑刚刚的构造有什么性质，发现这是由一个极小的，与原树的任何子树都不同构的树再拼上一条链得到的。

这一定能取到答案的下界，考虑选的树 $T$，因为 $T$ 不与原树中的任何子树同构，故往 $T$ 的根上加点不会影响是否同构，此时，子树大小比 $T$ 的大小小的点一定会造成贡献，易得这样的点至少有 $T$ 的大小 $-1$ 个，因此可以取到下界。

考虑求出 $T$，因为原树只有 $n$ 个子树，而大小为 $k$ 且互不同构的树的量级是指数级，所以说我们选的 $T$ 应该不会太大（大概 $15-20$？ ），因此可以考虑暴力搜索。

搜索时不能暴力枚举树的形态，互不同构的树的量级虽是指数级，但和树的总数比还差一些，所以我们要考虑更优的方式。

从小到大枚举 $T$ 的大小 $k$，考虑枚举子树，最好按哈希值从小到大枚，这样可以不重不漏，做到 $O(nk\log n)$，可以通过。

因为这里是按哈希值从小到大枚，所以使用了按哈希值排序的树哈希，即：

$$h(u)=rng(deg_u)+\sum\limits_{v\in son(u)}(h^2(v)+h(v)base^{rank(v)})$$

$rank(v)$ 表示 $v$ 在 $u$ 儿子中哈希值的排名，$rng(x)$ 表示一个只和 $x$ 有关的随机权值（代码里写的是 $x$ 异或一个定值）。

代码：


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
using namespace std;
const int N=1e6+10,base=131,mod=1011451423;
void cmx(int &a,int b){if(b>a) a=b;}
void cmn(int &a,int b){if(b<a) a=b;}
void cmx(ll &a,ll b){if(b>a) a=b;}
void cmn(ll &a,ll b){if(b<a) a=b;}
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int n,k;
vector<int> E[N];
int h[N],siz[N];
int rng(int u){
    return u^(mod+base+1);
}
map<int,int> q;
void dfs(int u,int fa){
    siz[u]=1;
    for(auto v:E[u]){
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }sort(E[u].begin(),E[u].end(),
    [](int a,int b){return h[a]<h[b];});
    int now=1;
    for(auto v:E[u]){
        if(v==fa) continue;
        //cout<<"? "<<u<<' '<<v<<' '<<h[v]<<endl;
        Add(h[u],1ll*now*h[v]%mod);
        Add(h[u],1ll*h[v]*h[v]%mod);
        Mul(now,base);
    }Add(h[u],rng((int)E[u].size()-(fa!=0)));
    //cout<<"? "<<u<<' '<<E[u].size()-(fa!=0)<<' '<<rng((int)E[u].size()-(fa!=0))<<' '<<h[u]<<endl;
    //if(siz[u]<=10) q[h[u]]=1;
}
bool ok=0;
vector<int> Son[N];
map<int,int> hs[30];
int idx=1,now=2;
int son[30];
void DfsSon(int dots,int step,int pbs,int lhsh,int hsh){
    if(ok) return ;
    if(dots==0){
        Add(hsh,rng(step));
        if(!q[hsh]) ok=1;
        ++idx;
        for(int i=1;i<=step;i++) Son[idx].push_back(son[i]);
        //for(int i=1;i<=step;i++) cout<<i<<' '<<son[i]<<endl;
        //cout<<now<<' '<<idx<<' '<<hsh<<endl<<endl;
        hs[now][hsh]=idx;
        return ;
    }
    for(int i=1;i<=dots;i++){
        for(auto j:hs[i]){
            if(j.fi<lhsh) continue;
            //cout<<"? "<<lhsh<<' '<<j.fi<<' '<<i<<endl;
            son[step+1]=j.se;
            DfsSon(dots-i,step+1,1ll*pbs*base%mod,
            j.fi,(hsh+1ll*pbs*j.fi+1ll*j.fi*j.fi)%mod);
        }
    }
}
int nodes=1,top=0;pii e[30];
void getTree(int idx,int now){
    if(idx==1) return ;
    for(auto ed:Son[idx]){
        ++nodes;e[++top]=mk(now,nodes);
        getTree(ed,nodes);
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        E[a].push_back(b);
        E[b].push_back(a);
    }dfs(1,0);
    for(int i=1;i<=n;i++) if(siz[i]<=20) q[h[i]]=1;//cout<<i<<' '<<h[i]<<endl;//cout<<h[i]<<' ';cout<<endl;
    for(int i=1;i<=n;i++) E[i].clear(),h[i]=0;
    hs[1][rng(0)%mod]=1;
    for(;now<=n;now++){
        DfsSon(now-1,0,1,0,0);
        if(ok){
            getTree(idx,1);//cout<<now<<' '<<top<<endl<<endl;
            int ad=n-now;
            for(int i=1;i<=ad;i++){
                cout<<i<<' '<<i+1<<'\n';
            }for(int i=1;i<=top;i++){
                cout<<e[i].fi+ad<<' '<<e[i].se+ad<<'\n';
            }cout.flush();
            return 0;
        }
    }for(int i=1;i<=n-1;i++) cout<<i<<' '<<i+1<<'\n';
    cout.flush();
    return 0;
}
```

---

