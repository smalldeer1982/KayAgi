# Programming Competition

## 题目描述

BerSoft is the biggest IT corporation in Berland. There are $ n $ employees at BerSoft company, numbered from $ 1 $ to $ n $ .

The first employee is the head of the company, and he does not have any superiors. Every other employee $ i $ has exactly one direct superior $ p_i $ .

Employee $ x $ is considered to be a superior (direct or indirect) of employee $ y $ if one of the following conditions holds:

- employee $ x $ is the direct superior of employee $ y $ ;
- employee $ x $ is a superior of the direct superior of employee $ y $ .

The structure of BerSoft is organized in such a way that the head of the company is superior of every employee.

A programming competition is going to be held soon. Two-person teams should be created for this purpose. However, if one employee in a team is the superior of another, they are uncomfortable together. So, teams of two people should be created so that no one is the superior of the other. Note that no employee can participate in more than one team.

Your task is to calculate the maximum possible number of teams according to the aforementioned rules.

## 说明/提示

In the first test case, team $ (3, 4) $ can be created.

In the second test case, no team can be created, because there are only $ 2 $ employees and one is the superior of another.

In the third test case, team $ (2, 3) $ can be created.

In the fourth test case, teams $ (2, 4) $ , $ (3, 5) $ and $ (6, 7) $ can be created.

In the fifth test case, teams $ (2, 3) $ , $ (6, 4) $ and $ (5, 7) $ can be created.

## 样例 #1

### 输入

```
6
4
1 2 1
2
1
5
5 5 5 1
7
1 2 1 1 3 3
7
1 1 3 2 2 4
7
1 2 1 1 1 3```

### 输出

```
1
0
1
3
3
3```

# 题解

## 作者：cpchenpi (赞：13)

使用树形 DP，$dp_i$ 表示以 $i$ 为根节点的子树的答案。

考虑如何计算 $dp_u$：根节点不能与任何节点匹配，因此只要考虑子树之间和子树内部的匹配，匹配数的上界是 $\lfloor \dfrac{sz_u - 1} {2}\rfloor $。

若所有子树的大小均不超过它们总大小 $sz_u - 1$ 的一半，根据经典的结论可知，匹配数能够达到上界。

否则，记大小最大的子树是 $v$，由调整法可知，存在一种最优方案使所有子树之间的匹配，存在于 $v$ 和其它子树之间。那么我们只需优先在 $v$ 的子树内部匹配，之后将剩余节点与其它子树匹配。答案即为 $\min(\lfloor \dfrac{sz_u - 1} {2}\rfloor, dp_v + (sz_u - 1 - sz_v))$。

通过代码：

``` cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

#define int i64
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> sons(n + 1);
    vector<int> sz(n + 1), ans(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        sons[p].push_back(i);
    }
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        int mxi = 0;
        for (int v : sons[u]) {
            dfs(v);
            sz[u] += sz[v];
            if (sz[v] > sz[mxi]) { mxi = v; }
        }
        if (sz[mxi] > (sz[u] - 1) / 2) {
            ans[u] = min((sz[u] - 1) / 2, ans[mxi] + (sz[u] - 1 - sz[mxi]));
        } else {
            ans[u] = (sz[u] - 1) / 2;
        }
    };
    dfs(1);
    cout << ans[1] << "\n";
}
#undef int

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
```

---

## 作者：Composite_Function (赞：6)

给出了一个较为抽象的贪心。

------------

由于要求 $(u,v)$ 中 $u$ 和 $v$ 必须不互为祖先，容易想到贪心只要选两个叶子节点就行了。因为如果 $(u,v)$ 不互为祖先，那么选一个 $u$ 的子节点 $u_0$，$(u_0, v)$ 满足条件且更优。但是具体叶子该怎么选呢？

会发现，取两个深度最大的节点时，能保证这颗树剩下的节点中深度尽量平衡，也就是能构成祖先的 $(u,v)$ 会更少，故贪心可以那么做。

------------

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
int T, n, f[N], dep[N], in[N];
vector<int> to[N];
void dfs(int u, int depth)
{
	dep[u] = depth;
	for (int v : to[u]) dfs(v, depth + 1);
}
signed main()
{
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 2; i <= n; ++i) {
			cin >> f[i];
			to[f[i]].push_back(i);
			++in[f[i]];
		}
		dfs(1, 1);
		priority_queue<pair<int, int> > q;
		for (int i = 1; i <= n; ++i)
			if (in[i] == 0) q.push(make_pair(dep[i], i));
		int ans = 0;
		while (q.size() >= 2) {
			auto [depx, x] = q.top(); q.pop();
			auto [depy, y] = q.top(); q.pop();
			if (--in[f[x]] == 0 && dep[f[x]] != 1) q.push(make_pair(dep[f[x]], f[x]));
			if (--in[f[y]] == 0 && dep[f[y]] != 1) q.push(make_pair(dep[f[y]], f[y]));
			++ans;
		}
		cout << ans << endl;
		for (int i = 1; i <= n; ++i) {
			in[i] = 0;
			vector<int> ().swap(to[i]);
		}
	}
	return 0;
}
```

---

## 作者：int_R (赞：4)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/CF1914F.html)

[原题链接](https://www.luogu.com.cn/problem/CF1914F)

感觉有点类似 [agc034e Complete Compress](https://www.luogu.com.cn/problem/AT_agc034_e)，但那题比这个难得多。

定义 $f_x$ 为以 $x$ 为根的子树中，尽可能组队后最多剩下多少人，$siz_x$ 为子树大小。

记 $y\in son(x)$ 中 $f_y$ 最大的点为 $hson_x$。

当 $\sum\limits_{y\in son(x),y\not=hson_x} siz_y < f_{hson_x}$ 时，说明即使其他子树中的人都来跟 $hson_x$ 子树中的点配对，也无法配对完，还是会剩下 $f_{hson_x}-\sum\limits_{y\in son(x),y\not=hson_x} siz_y$ 即 $f_{hson_x}-(siz_x-1-siz_{hson_x})$ 个人。

否则就是尽可能可以配对完，那么这时会剩下 $(siz_x-1)\bmod 2$ 个人。证明考虑每次选出所有剩余 $f_y$ 中最大的两个，一起 $-1$，这样就相当于最后只会剩 $0\sim 1$ 个 $1$，就等于 $siz_x-1$ 的奇偶性。

最后要使 $f_x$ 加上 $x$ 自己。综上

$f_x=\begin{cases} f_{hson_x}-(siz_x-1-siz_{hson_x})+1 & f_hson_x>(siz_x-1-siz_{hson_x}) \\ (siz_x-1)\bmod 2 +1 & f_hson_x\leq (siz_x-1-siz_{hson_x}) \end{cases}$

答案为 $\dfrac{n-f_{root}}{2}$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=2e5+10;
int t,n,fa[MAXN],siz[MAXN],f[MAXN],hson[MAXN];
vector <int> v[MAXN];
void dfs(int x)
{
    for(int y:v[x])
    {
        dfs(y),siz[x]+=siz[y];
        if(f[y]>f[hson[x]]) hson[x]=y;
    }
    if(f[hson[x]]>siz[x]-siz[hson[x]])
        f[x]=f[hson[x]]-(siz[x]-siz[hson[x]]);
    else f[x]=(siz[x]&1);f[x]+=1,siz[x]+=1;return ;
}
int main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=2;i<=n;++i)
            cin>>fa[i],v[fa[i]].push_back(i);
        dfs(1);cout<<(n-f[1])/2<<'\n';
        for(int i=1;i<=n;++i)
            v[i].clear(),fa[i]=siz[i]=f[i]=hson[i]=0;
    }
    return 0;
}
```

---

## 作者：—_—_—_ (赞：3)

考虑贪心。

这里可以发现一个比较明显的性质:
- 在你选择一个点后，跟他处于同一层的点是肯定可以与他匹配的
- 进一步考虑。对于某一层来说，如果在它下面的层里存在点不能被匹配，那这些点一定构成一条直链。而在这层内只会有一个点（也就是这条直链的父节点）不能参与与下面点的匹配。由于我们要求最大点对数量，所以我们希望每次往下一层传的节点尽可能少。

于是贪心的思路就完成了：
我们先用 dfs 求出每层内的节点数量，然后 $deep$ 从大到小遍历，把传上来的节点与当前层节点数减一取 $\min$，这些点是可以匹配的。将这部分节点加到 $ans$，再将本层内的节点进行匹配，如果匹配后多出来一个点，就将其传到下一层。

虽然说着很复杂，但实际上写起来比较简单，代码也比较容易看懂：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
vector<int> sons[maxn];
int mx,dep[maxn];
void dfs(int x,int deep)
{
    dep[deep]++;
    mx=max(mx,deep);
    int len=sons[x].size()-1;
    for(int i=0;i<=len;i++)
    {
        dfs(sons[x][i],deep+1);
    }
}
void solve()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) sons[i].clear(),dep[i]=0;
    for(int i=2;i<=n;i++)
    {
        int p;
        scanf("%d",&p);
        sons[p].push_back(i);
    }
    mx=-1;
    dfs(1,1);
    int ans=0,els=0;
    for(int i=mx;i>0;i--)
    {
        int tmp=min(els,dep[i]-1); 
        ans+=tmp;                       //将匹配好的点对加入答案 
        els-=tmp;
        dep[i]-=tmp;
        ans+=dep[i]/2;
        if(dep[i]&1)
        {
            els++;                      //如果有剩余出来节点就传到下一层 
        }
    }
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
}
```

---

## 作者：ZLCT (赞：1)

# CF1914F Programming Competition
## 题目翻译
给定一棵树，求最多划分出多少点对 $(u,v)$ 使得互不为祖先，每个点只能包含在一个点对里。
## solution
这个题拿道题我们无法一下想到如何处理，所以不妨先自己找几棵树试一试。\
![](https://cdn.luogu.com.cn/upload/image_hosting/9qzahgaj.png)\
我们拿这棵树去考虑每棵子树都能最多划分多少（这样可以考虑一棵树相当于考虑很多树）。\
我们记录 $f_u$ 表示点 $u$ 子树能划分成多少点对。
$$
f_6=f_4=f_3=f_7=f_5=0
$$
$$
f_2=1
$$
$$
f_1=3
$$
我们发现子树结点个数 $\le2$ 个的子树都无法划分出点对，我们思考这是为什么。\
我们思考一下会发现一个树的树根一定是所有点的祖先，所以假设一棵树的大小为 $siz_u$，那么我们最多构成 $\lfloor{\frac{siz_u-1}{2}}\rfloor$ 对点对。\
那么接下来我们如何确定我们的思考方向呢？\
这个时候就要抓住题目的重要信息：祖先。\
这代表着我们在点 $u$ 为根的子树中，只要两个点不是 $u$ 的同一个儿子，那就一定可以构成一个点对。\
这就启示我们要考虑从下往上更新。\
我们根据上面的思路，如果我们能使得两个点分别在 $u$ 的不同儿子那是最好的。\
这不难想到只要 $u$ 最大的儿子的大小 $\le\lfloor{\frac{siz_u-1}{2}}\rfloor$，那我们就可以将这个儿子的每个点都和其他儿子的点连边，至于其他儿子 $v$ 由于都有 $siz_v\le\lfloor{\frac{siz_u-1}{2}}\rfloor$，所以我们可以通过调整使得每个点都与其他不同儿子中的点连边，此时的答案也就是 $\lfloor{\frac{siz_u-1}{2}}\rfloor$。\
如果不是这种情况就说明最大的儿子比其他子树加起来还大，那我们肯定选择其余子树中的所有点都与这棵子树中的点连边。\
但是我们不要忽略子树 $v$ 内部本身就可以处理掉 $f_v\times 2$ 的点。\
那么我们此时需要判断子树 $v$ 处理剩下的点数与其他子树的点数的关系。
- $siz_v-2\times f_v=f_{other}$：那我们正好剩余点一一对应，答案为 $\lfloor{\frac{siz_u-1}{2}}\rfloor$。
- $siz_v-2\times f_v<f_{other}$：此时我们可以把 $f_v$ 中的点对先自我匹配了，然后情况就转化为了最大子树大小 $\le\lfloor{\frac{siz_u-1}{2}}\rfloor$ 的情况了，答案就是 $f_v+\lfloor{\frac{siz_u-1-2\times f_v}{2}}\rfloor=\lfloor{\frac{siz_u-1}{2}}\rfloor$。
- $siz_v-2\times f_v>f_{other}$：此时我们最好的情况就是先 $v$ 子树内部消化掉 $f_v$ 对点，然后其余点都与其余子树中的点匹配，这样对于子树 $v$ 而言是能匹配点数最多的方案，对于其余子树的点也都匹配了，所以这肯定是最优方案，此时答案就为 $f_v+siz_{other}$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+666;
int read(){
    int res=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(isdigit(c)){
        res=10*res+c-'0';
        c=getchar();
    }
    return res*f;
}
void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int n,f[N],siz[N],mst[N];
vector<int>G[N];
void clear(){
    for(int i=1;i<=n;++i){
        G[i].clear();
    }
    memset(f,0,sizeof(int)*(n+5));
}
void dfs(int u,int fa){
    siz[u]=1;
    mst[u]=0;
    for(int v:G[u]){
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[mst[u]])mst[u]=v;
    }
    if(siz[mst[u]]<=siz[u]/2){
        f[u]=(siz[u]-1)/2;
    }else{
        if((siz[mst[u]]-f[mst[u]]*2)<=(siz[u]-siz[mst[u]]))f[u]=(siz[u]-1)/2;
        else f[u]=f[mst[u]]+siz[u]-siz[mst[u]]-1;
    }
}
void solve(){
    clear();
    n=read();
    for(int i=2;i<=n;++i){
        int fa=read();
        G[fa].push_back(i);
    }
    dfs(1,1);
    write(f[1]);
    putchar('\n');
    return;
}
signed main(){
    int T=read();
    while(T--)solve();
    return 0;
}
/*
 1 2
 1 3
 3 4
 2 5
 2 6
 4 7
 */
```

---

## 作者：_yi_ (赞：0)

[原题传送门-Luogu](https://www.luogu.com.cn/problem/CF1914F)

在树中找互不为祖先的点对的最大个数。

不妨先考虑以 $i$ 为根的子树，其中的点对仅有两种：

- 子树内的两点

- 子树内的一点和子树外的一点

显然，子树内的一点若要匹配子树外的节点，只需要匹配兄弟子树内的节点就可以满足不互为祖先。（若一个可匹配的节点不在该子树的兄弟子树内，则必然在该子树祖先的兄弟子树内）

而子树内的两点显然对该子树外的点对无影响，即为无后效性。

不妨将子树不断两两合并。

合并时，可以贪心的将两个子树内的节点互相匹配（优先匹配未被匹配的），则最大的匹配节点数量为两个子树大小的较小值分别加两个子树的最大匹配节点数量。

由于维护的时最大匹配节点数量，需要将其除以二并输出。

附上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll p[200001];
vector<ll> son[200001];
ll s[200001],f[200001];
void dfs(int i){
	for(int j:son[i]){
		dfs(j);
		ll t=min(s[i],s[j]);
		f[i]=min(t+f[i],s[i])+min(t+f[j],s[j]);
		s[i]+=s[j];
	}
	s[i]++;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		ll n;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			son[i].clear();
		}
		for(int i=2;i<=n;i++){
			scanf("%lld",&p[i]);
			son[p[i]].push_back(i);
		}
		for(int i=1;i<=n;i++){
			f[i]=s[i]=0;
		}
		dfs(1);
		printf("%lld\n",f[1]/2);
	}
	return 0;
}
```


---

## 作者：Sunny郭 (赞：0)

考虑 dp。

设 $f_i$ 为 $i$ 的子树里匹配了多少对，$g_i$ 为 $i$ 的子树里还有多少个点没有匹配。

考虑结合贪心的思想来 dp。

从 1 开始树形 dp 每次加入一颗子树时，把当前已经加入过的点全部拿出来和新加入这颗匹配，匹配形态为 1 个点在已加入的点中，另一个点在新加入的子树中，那么匹配对数为 $\min(2 \times f_a+g_a,2 \times f_b+g_b)$，即 $\min$ 的加入过的点数和新加入的点数。贪心的先将之前未匹配过的点拿出来匹配，但是这样可能会伤及之前匹配过的点，于是把之前匹配过的对数也要重新算一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
int i, j, n, m, k, f[N], g[N];
vector<int> v[N];
void dfs(int a) {
	g[a] = f[a] = 0;
	for(int b : v[a]) {
		dfs(b);
		int x = 2 * f[a] + g[a], y = 2 * f[b] + g[b];
		int z = min(x, y);//最大直接匹配对数
		if(z == x) {
			f[a] = (2 * f[b] + min(0, g[b] - z)/*加入前未匹配的点数-直接匹配的点数=要从匹配过的点对中取的点数*/) / 2 + z;//重新计算匹配过的对数
			g[a] = x + y - 2 * f[a];
		} else {
			f[a] = (2 * f[a] + min(0, g[a] - z)) / 2 + z;
			g[a] = x + y - 2 * f[a];
		}
	}
	++g[a];
}
void solve() {
	for(i=1; i<=n; i++) v[i].clear();
	cin >> n;
	for(i=2; i<=n; i++) cin >> k, v[k].push_back(i);
	dfs(1), cout << f[1] <<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
?
```

---

