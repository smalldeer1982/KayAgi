# [ARC148C] Lights Out on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc148/tasks/arc148_c

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点の根付き木があります。頂点 $ 1 $ が根で、頂点 $ i $ $ (2\ \leq\ i\ \leq\ N) $ の親は頂点 $ P_i $ です。  
 表裏のあるコインが $ N $ 枚あります。コインは全ての頂点の上に $ 1 $ 枚ずつ載っています。  
 また、$ 1 $ から $ N $ までの番号がついた $ N $ 個のボタンがあります。ボタン $ n $ を押すと $ n $ を根とする部分木に含まれる頂点に載っている全てのコインが裏返ります。

以下で説明するクエリを $ Q $ 個処理してください。

$ i $ 番目のクエリではサイズ $ M_i $ の頂点集合 $ S_i\ =\ \lbrace\ v_{i,1},\ v_{i,2},\dots,\ v_{i,M_i}\ \rbrace $ が与えられます。  
 今、$ S_i $ に含まれる頂点の上に載っているコインは表を、それ以外のコインは裏を向いています。ボタンを $ 1 $ つ選んで押すことを繰り返して、$ N $ 枚のコイン全てを裏向きにするには、最小で何回ボタンを押す必要がありますか？答えを出力してください。ただし、どのようにボタンを押しても $ N $ 枚のコイン全てが裏向きにならない場合は $ -1 $ を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ P_i\ \lt\ i $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M_i $
- $ \displaystyle\ \sum_{i=1}^Q\ M_i\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ v_{i,j}\ \leq\ N $
- $ v_{i,1},\ v_{i,2},\dots,v_{i,M_i} $ は互いに異なる
- 入力される値はすべて整数

### Sample Explanation 1

$ 1 $ 番目のクエリについて、以下に説明するようにボタンを $ 1 $ 回押すことで条件を満たすことができて、これが最小です。 - ボタン $ 1 $ を押す。頂点 $ 1,2,3,4,5,6 $ に載っているコインが裏返る。 $ 2 $ 番目のクエリについて、以下に説明するようにボタンを $ 2 $ 回押すことで条件を満たすことができて、これが最小です。 - ボタン $ 4 $ を押す。頂点 $ 4 $ に載っているコインが裏返る。 - ボタン $ 2 $ を押す。頂点 $ 2,4,5,6 $ に載っているコインが裏返る。

## 样例 #1

### 输入

```
6 6
1 1 2 2 5
6 1 2 3 4 5 6
3 2 5 6
1 3
3 1 2 3
3 4 5 6
4 2 3 4 5```

### 输出

```
1
2
1
3
2
3```

# 题解

## 作者：mlvx (赞：8)

一个节点想要单独改变颜色，显然可以对自己进行一次操作，然后对其所有儿子进行一次操作。

一个节点偶数次操作等于没操作，故每次把该节点的操作次数 $0$ 变 $1$，$1$ 变 $0$ 即可。

问题转化为单个节点及其所有儿子全体异或 $1$，求全局和。

建线段树，显然要让儿子在线段树对应的数组上是一段连续的区间。

考虑 bfs 标号，这样同一深度的节点的编号都是连续的，可以对某个节点的儿子进行操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pl (p<<1)
#define pr (p<<1|1)
const int N=2e5+10;
int n,q,cnt,id[N],x[N];vector<int>g[N];
void bfs(int rt){
    queue<int>q;q.push(rt);
    while(!q.empty()){
        int t=q.front();q.pop(),id[t]=++cnt;
        for(int i:g[t])q.push(i);
    }
}struct SGT{
    int inv[N<<2],sum[N<<2][2];
    void pushup(int p){sum[p][0]=sum[pl][0]+sum[pr][0],sum[p][1]=sum[pl][1]+sum[pr][1];}
    void Inv(int p){swap(sum[p][0],sum[p][1]),inv[p]^=1;}
    void pushdown(int p){if(inv[p]){Inv(pl),Inv(pr),inv[p]=0;}}
    void build(int l,int r,int p){
        if(l==r)return sum[p][0]=1,void();
        int mid=l+r>>1;build(l,mid,pl),build(mid+1,r,pr),pushup(p);
    }void update(int l,int r,int le,int ri,int p){
        if(l>=le&&r<=ri)return Inv(p);
        int mid=l+r>>1;pushdown(p);
        if(le<=mid)update(l,mid,le,ri,pl);
        if(ri>mid)update(mid+1,r,le,ri,pr);
        pushup(p);
    }int query(int l,int r,int le,int ri,int p){
        if(l>=le&&r<=ri)return sum[p][1];
        int mid=l+r>>1,ret=0;pushdown(p);
        if(le<=mid)ret+=query(l,mid,le,ri,pl);
        if(ri>mid)ret+=query(mid+1,r,le,ri,pr);
        return ret;
    }
}T;
int main(){
    cin>>n>>q;
    for(int i=2,f;i<=n;i++)cin>>f,g[f].push_back(i);
    bfs(1),T.build(1,n,1);
    for(int s;q--;){
        cin>>s;
        for(int i=1;i<=s;i++)cin>>x[i],T.update(1,n,id[x[i]],id[x[i]],1),g[x[i]].size()&&(T.update(1,n,id[g[x[i]][0]],id[g[x[i]].back()],1),1);
        cout<<T.query(1,n,1,n,1)<<'\n';
        for(int i=1;i<=s;i++)T.update(1,n,id[x[i]],id[x[i]],1),g[x[i]].size()&&(T.update(1,n,id[g[x[i]][0]],id[g[x[i]].back()],1),1);
    }return 0;
}
```

---

## 作者：ccxswl (赞：3)

# [ARC148C] Lights Out on Tree

[原题](https://www.luogu.com.cn/problem/AT_arc148_c)

---

对于一个黑色节点想要将他变成白色，可以将它翻转，再将它所有儿子节点翻转，这样就做到只将这个黑色节点翻转成白色。因此不存在无解情况。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/g09s0x5j.png)

对于一组样例，先考虑顶点 $u$ 为黑色的部分，想要把 $u$ 变白色**必须**对 $u$ 进行一次操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/gfn6yylq.png)

操作完后变成这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/mscmahhg.png)

然后一直处理顶点为黑色节点的部分。因为每次进行的操作都是**必须**进行的，所以最后的答案就是最少次数。

通过模拟刚才的样例发现，如果一个节点的父亲和它是一个颜色，那么在它的父亲翻转后它就也翻转了，所以它不贡献答案。也就是说如果一个节点和它父亲颜色不同那么它才就会翻转一次，贡献一次答案。最后的答案为和自己父亲颜色不一样的节点个数。

观察数据范围发现 $\Sigma_{i=1}^QM_i\le2\times10^5$，也就是说对于每个单独的询问，黑点的个数是相当少的，白色节点个数很多，因此我们只能枚举黑色节点。父亲为黑色的白色节点个数和黑色节点的白色儿子个数是相等的，所以可以统计每个黑色节点的黑色儿子个数，它的白色儿子个数为总的儿子个数减黑色儿子个数。

默认根节点 $1$ 的父亲为一个白色节点 $0$，细节见代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read() {
	int s = 0, w = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') w = -w; c = getchar();}
	while (isdigit(c)) {s = s * 10 + c - 48; c = getchar();}
	return s * w; 
}

const int maxN = 2e5 + 7;

int n, Q, q[maxN];

int fa[maxN];
vector<int> son[maxN];

bool blk[maxN];
int cnt[maxN];

int main() {
	n = read(), Q = read();
	for (int i = 2; i <= n; i++)
		fa[i] = read(),
		son[fa[i]].push_back(i);
	while (Q--) {
		int m = read(), ans = 0;
		for (int i = 1; i <= m; i++)
			blk[q[i] = read()] = true;
		for (int i = 1; i <= m; i++)
			if (blk[fa[q[i]]]) cnt[fa[q[i]]]++;
			else ans++;//一个黑色节点父亲为白色，答案＋1
		for (int i = 1; i <= m; i++)
			ans += son[q[i]].size() - cnt[q[i]];
            //加上每个黑色节点的白色儿子个数
		cout << ans << '\n';
		
		for (int i = 1; i <= m; i++)
			blk[q[i]] = false, cnt[q[i]] = 0;
	}
}
```

---

## 作者：AThls123 (赞：2)


[link](https://www.luogu.com.cn/problem/AT_arc148_c)

 这题容易想到一种 $O(nq)$ 的算法。从根出发，如果当前节点是黑的就把翻转一下，然后一直下去，计数即可。~~所以不可能无解~~。可以发现，如果一个节点的儿子们都不在集合中，在他翻转之后，他的儿子们必须要翻转一下，这样操作的结果就是他的子树中没有变化就他变了。若考虑有存在儿子是集合中元素的情况，在父亲节点翻转的时候，这个儿子就会变白。

所以只需要这样统计。令 $sum$ 为答案。如果当前节点是集合中的元素，先看他的父亲是否是集合中的元素，如果不是说明要翻转一下并把儿子都翻转一下，然后计入次数。但是这样计算会多算，所以如果父亲是集合中的元素还要撤销一次操作。

code 

```cpp
#include <cstdio>
using namespace std;
const int N = 2e5 + 7;
int fa[N], v[N], son[N];
int n, m;
int a[N];

int main(){
  scanf("%d %d", &n, &m);

  for(int i = 2; i <= n; ++i) {
    scanf("%d", &fa[i]);
    son[fa[i]]++;
  }
  
  for(int o = 1; o <= m; ++o) {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      v[a[i]] = 1;
    }
    int sum = 0;
    for(int i = 1; i <= n; ++i) {
      int x = a[i];
      if(!v[fa[x]]) ++sum;
      else --sum;
      sum += son[x];
    }
    printf("%d\n", sum);
    for(int i = 1; i <= n; ++i) v[a[i]] = 0;
  }
  
  return 0;
}
```


---

## 作者：Phartial (赞：2)

动动脑子就能知道根本不可能无解。

考虑写一个非常暴力的做法：从 $1$ 开始遍历这棵树，同时记一下当前子树有没有被翻转。统计答案直接看当前节点要不要翻转即可。

参考实现（`c[x]` 表示第 $x$ 个点的颜色）：

```cpp
void D(int x, bool r) {
  ans += c[x] != r;
  for (int i : e[x]) {
    D(i, r ^ (c[x] != r));
  }
}
```

不难发现 `r ^ (c[x] != r)` 就相当于 `c[x]`。所以这份代码本质上是在统计有多少个节点的颜色不等于父节点的颜色。

每个被染成黑色的节点对答案的贡献即为它有多少个白色的儿子节点和多少个白色的父亲节点。直接维护一下即可。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int kN = 2e5 + 1;

int n, q, c, f[kN], s[kN];
bool v[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> q;
  for (int i = 2; i <= n; ++i) {
    cin >> f[i];
    ++s[f[i]]; // 有多少个儿子的颜色是白色
  }
  for (int l; q--; ) {
    cin >> l;
    vector<int> ql(l);
    for (int &i : ql) {
      cin >> i;
      --s[f[i]];
      v[i] = 1;
    }
    c = 0;
    for (int i : ql) {
      c += s[i] + !v[f[i]]; // 每个黑色节点的贡献：对儿子的和对父亲的
    }
    cout << c << '\n';
    for (int i : ql) { // 还原
      v[i] = 0;
      ++s[f[i]];
    }
  }
  return 0;
}
```


---

## 作者：zerc (赞：2)

有生之年，你谷终于爬到新题了（（（

---

**题意：**

给你一颗有根树，每个节点是黑色或白色，初始全为白色。

每次询问给出一个点集 $S$，把点集中的点全部染成黑色，问至少需要翻转多少个节点使整棵树全为白点，无解输出 `-1`。

翻转的定义为：将节点 $u$ 及其子树中所有节点颜色翻转。

**输入：**

第一行 $N$，$Q$ 表示节点数和询问次数；

第二行 $N-1$ 个整数 $P_i$ 表示节点 $i$ 的父节点；

之后 $Q$ 行，每行第一个整数 $M_i$ 表示点集 $S$ 大小，余下 $M_i$ 个整数 $v_{i,j}$ 表示点集 $S$。

---

**题解：**

非常显然的性质是：

- 对一个节点操作一次以上是没有意义的；

- 操作的顺序没有影响；

- 一定有解并只有一种可行方案；

好，我们可以枚举每个节点操作或不操作，时间复杂度是 $O(2^n)$。

这是暴力的解法，我们考虑正解：

首先预处理每个顶点的儿子节点数 $t$，然后对于每次询问，$ans=m_i+\sum_{j=1}^{m_i} t_{v_{j}}$，需要注意的是更改父节点是会更改子节点的状态，如果子节点也需要更改，就减去它的贡献。

```cpp
int main() {
    scanf("%d %d", &n, &q);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &p[i]), t[p[i]]++;
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d", &m), ans = m;
        for (int j = 1; j <= m; j++) {
            scanf("%d", &v[j]), t[p[v[j]]] -= 2;
        }
        for (int j = 1; j <= m; j++) {
            ans += t[v[j]];
        }
        for (int j = 1; j <= m; j++) {
            t[p[v[j]]] += 2;
        }
        printf("%d\n", ans);
    }
}
```

---

## 作者：Fa_Nanf1204 (赞：1)

### 分析：
考虑使一个黑点变成白点并且不影响当前其他的点的状态，可以翻转这个点和这个点的所有儿子，那么这样跑完所有的黑点，对翻转次数为奇数次的点统计答案。

考虑优化以上的算法：
- 一个黑点它的父亲也是黑点，那么这个点不会产生任何贡献。
- 一个黑点它的父亲是白点，那么这个点会产生 $1$ 的贡献。
- 一个白点它的父亲是黑点，那么这个点会产生 $1$ 的贡献。
- 一个白点它的父亲也是白点，那么这个点不会产生任何贡献。

根据以上的分类讨论即可快速统计答案，答案为每个黑点儿子的白点数量加上其父亲如果不为黑点的贡献。
### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int n,m,a[N],vis[N],ans,fa[N],son[N],sum[N];
int main(){
	cin.tie(),cout.tie(),ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		fa[i]=x;
		son[x]++;
	} 
	fa[1]=0;
	while(m--){
		int q;
		cin>>q;
		ans=0;
		for(int i=1;i<=q;i++){
			cin>>a[i];
			sum[fa[a[i]]]++;
			vis[a[i]]=1;
		}
		for(int i=1;i<=q;i++){
			ans+=son[a[i]]-sum[a[i]]+(!vis[fa[a[i]]]);
		}
		for(int i=1;i<=q;i++){
			sum[fa[a[i]]]--;
			vis[a[i]]=0;
		}
		cout<<ans<<'\n';
	}
	return 0;
} 
```

---

## 作者：xyin (赞：1)

首先我们思考会不会出现无解的清况：对于一个黑色节点，我们先翻转该节点，再翻转它的所有儿子节点，就能做到**只**翻转该黑色节点，所以明显是不存在无解情况的。

然后我们再来思考怎么安排黑色节点的翻转顺序，能使结果更优呢？通过一些手模和直观想象，也能发现先翻转深度小的点要比先翻转深度大的点更优，同一深度是互不影响的。

接下来我们就有了一份暴力代码：从根节点开始遍历，利用一个节点翻转两次相当于没翻转的性质，每次判断该节点是否需要翻转

```cpp
//vis[x]=1 表示该节点为黑，反之则为白
//tag=1 表示目前该节点以翻转，反之则没翻转
void dfs(int x,int fa,int tag){
    if (tag^vis[x]) ans++;
    for (auto to:he[x])
        if (to!=fa) 
            dfs(to,fa,tag^(tag^vis[x]))
            //等价于 dfs(to,fa,vis[x])
}
```

但是我们一共有 $Q$ 次询问，不允许我们每次做一遍 dfs。从我们上面的“等价”可以发现，每次 $tag$ 传的值其实就 $vis_{fa}$，每次 $ans$ 只会在 $vis_{fa}\operatorname{xor}vis_x=1$ 的时候更新答案。所以我们只需要对于每个点维护有多少个子节点与它的颜色不同即可，每次枚举黑色节点并判断它的父亲和儿子即可，时间复杂度和输入的复杂度相同。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int INF=1e9;
int read(int x=0,bool f=1,char c=0){
    while (!isdigit(c=getchar())) f=c^45;
    while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?x:-x;
}
int n,q,m,fa[maxn];
int son[maxn],bla[maxn];
bool vis[maxn];
//son 数组记录 x 的子节点数量
//vis 数组记录 x 的颜色
//bla 数组记录 x 有多少颜色为黑的子节点
signed main(){
	n=read();q=read();
	for (int i=2;i<=n;i++)
	    fa[i]=read(),son[fa[i]]++;
	while (q--){
		memset(vis,0,sizeof(vis));
		m=read();queue<int>h;
		for (int i=1,x;i<=m;i++){
		    x=read(),vis[x]=1;
            bla[fa[x]]++,h.push(x);
        }
		int ans=0;
		while (!h.empty()){
			int x=h.front();h.pop();
			if (vis[x]!=vis[fa[x]])//如果父亲是白色 
				ans++,bla[fa[x]]=0;//统计答案，因为是多测顺便清空数组
			ans+=son[x]-bla[x];bla[x]=0;//统计子节点中与它颜色不一样的答案
		}
		printf("%d\n",ans);
	 } 
	return 0;
}
```

---

## 作者：AqrDAD (赞：1)

## 题意：
给你一颗树，树根为 1，初始所有点都是白色，每次询问给出一个点集，若把点集中的点全部染成黑色，问至少需要翻转多少个节点才能使整棵树全为白点。无解输出 -1。询问之间相互独立

翻转的定义为：将节点 u 及其子树中所有节点颜色翻转。

## 赛时分析：（可跳过）

赛时不会，想到了时间复杂度 $O(n * m)$ 的树上 DP，以为是正解（时间复杂度想假了 $n$ 按 $\log n$ 算的），打完才发现时间复杂度不对，之后就只想着怎么在这个基础上优化了，一直在思考把 $n$ 变成 $\log{n}$，本地跑大样例从 $36s$ 卡常优化到了 $1.9s$，但时间复杂度没变，大概调了一个多小时急了，直接交了，想着能拿个 $30pts$，特殊性质也没想，结果捆绑测试实际得分 $0pts$。

以后模拟赛不能一个思路耗死，不能太高估自己，像这个题，性质也没那么难想，但自己完全就是没想着会有什么性质，一直在优化自己的 dp，看来以后要及时否定自己多换思路。

## 正解：

注：下文“染黑某个点”等说法皆指染黑以该点为根的子树。

### 思想：

我们枚举每个被染黑的点，设为 $u$，由于 $u$ 已经被染黑了，所以我们肯定要把它染回来，如果 $u$ 的父亲节点 $fa$ 也为黑点，那么我们在进行将 $fa$ 染为白点的操作后，自然也一起把 $u$ 染白了；
再枚举 $u$ 的子节点 $son$，如果 $son$ 为白色，那么在把 $u$ 染回来的操作中，$son$ 点便被染黑了，所以还需要再染一次 $son$ 点。

计算答案 $ans$ 时，那么我们只需遍历每个被染黑的点，若它的父亲节点不是黑点，则需要染一次，`ans++`，再遍历它的子节点，若子节点是白点，则还需染子节点一次，`ans++`。

这便是我们的思想，不过较容易发现，时间复杂度为 $O(Q  n  m)$，（$Q$ 为询问的次数），会 $T$ 掉。

<details>
<summary>暴力代码</summary>

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
using namespace std;

const int N = 2e5 + 10;

int n, Q, m, in[N];
int color[N], fa[N];
map<pair<int, int>, int>son;

signed main(){
	// freopen("in.in", "r", stdin); freopen("a.out", "w", stdout);

	scanf("%d%d", &n, &Q);
	for(int i=2; i<=n; i++){
		scanf("%d", &fa[i]);
		son[mp(fa[i], ++son[mp(fa[i], 0)])] = i;
	}


	while(Q--)
	{
		scanf("%d", &m);
		for(register int i=1; i<=m; i++){
			scanf("%d", &in[i]);
			color[in[i]] = 1;
		}

		int ans = 0;
		for(int i=1; i<=m; i++){
			if(!color[fa[in[i]]]) ans++;
			for(int j=1; j<=son[mp(in[i], 0)]; j++){
				if(!color[son[mp(in[i], j)]]) ans++;
			}
		}

		printf("%d\n", ans);

		for(register int i=1; i<=m; i++) color[in[i]] = 0;
	}


	return 0;
}
```
</details>


<br/>

### 考虑优化：

时间复杂度多的那个 $n$ 是枚举每个黑点的儿子节点导致的，所以我们考虑能不能不枚举每个儿子，我们可以预处理出来的时每个节点儿子的数量，这些数量是不会变化的，“别管黑儿子还是白儿子都是儿子”。

所以在枚举每个黑点的时候，我们可以直接加上该点儿子的数量。但这样就多加了黑儿子啊，按照我们的思路只加白儿子，但别忘了，黑儿子是被染黑的点，所以我们枚举所有黑点时总会枚举到这些多加的黑儿子，那么我们枚举时，判断枚举点的父亲节点是否为黑，若为父亲节点为白，则加一次操作，否则把减去一次操作，这样就把多加的黑儿子减去了。

成功优化到 $O(Q  n)$ 了！

### 最终代码：

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
using namespace std;

const int N = 2e5 + 10;

int n, Q, m, in[N];
int color[N], fa[N], son[N];

signed main(){
	// freopen("in.in", "r", stdin); freopen("a.out", "w", stdout);

	scanf("%d%d", &n, &Q);
	for(int i=2; i<=n; i++){
		scanf("%d", &fa[i]);
		son[fa[i]]++;
	}


	while(Q--)
	{
		scanf("%d", &m);
		for(register int i=1; i<=m; i++){
			scanf("%d", &in[i]);
			color[in[i]] = 1;
		}

		int ans = 0;
		for(int i=1; i<=m; i++){
			if(!color[fa[in[i]]]) ans++;
			else ans--;
			ans += son[in[i]];
		}

		printf("%d\n", ans);

		for(register int i=1; i<=m; i++) color[in[i]] = 0;
	}


	return 0;
}
```

---

## 作者：white_tiger_yyyy (赞：1)

在考场遇到了这道题，感觉很有意思。

当时直接想到的就是虚树，可惜打挂了。

后来改对了，写篇题解纪念一下。

---
首先看到 $\sum M_i\le 2\times 10^5$，很容易想到虚树的数据范围。

我们设 $dp_i,fg_i$ 表示将 $i$ 的子树全部染白或染黑需要多少次，$vis_i=1/2$ 表示该点为黑 $/$ 白，则有：

$$
\begin{cases}\begin{cases}
dp_i=\sum fg_j+1\\
fg_i=\sum fg_j
\end{cases}(vis_x=1)\\\\\begin{cases}
dp_i=\sum dp_j\\
fg_i=\sum dp_j+1\end{cases}(vis_x=2)\end{cases}
$$

很容易发现，假如在虚树上的父子在原树上且父亲为黑点，则有：

$$
\begin{cases}
dp_i=\sum dp_j+sz_i+1\\
fg_i=\sum dp_j+sz_i
\end{cases}
$$

其中 $sz_i$ 表示节点儿子数。加之在虚树上，儿子不一定都在，所以原先的方程改为：

$$
\begin{cases}\begin{cases}
\begin{cases}
dp_i=\sum (fg_j-1)+sz_i+1\\
fg_i=\sum (fg_j-1)+sz_i
\end{cases}(fa_j=i)\\\\
\begin{cases}
dp_i=\sum dp_j+sz_i+1\\
fg_i=\sum dp_j+sz_i
\end{cases}(fa_j\ne i)
\end{cases}(vis_x=1)\\\\
\begin{cases}dp_i=\sum dp_j\\fg_i=\sum dp_j+1\end{cases}(vis_x=2)\end{cases}
$$

我用 $\text{lca}$ 建虚树，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e5+5;
int n,q,rt,d,dep[N],c[N];
int id,f[N][25],dfn[N];
int dp[N],fg[N],vis[N];
vector<int>g[N],ve[N];
int cmp(int x,int y){
	return dfn[x]<dfn[y];
}void dfs(int x,int fa){
	dep[x]=dep[fa]+1;
	f[x][0]=fa;dfn[x]=++id;
	for(int i=0;i<24;i++)
		f[x][i+1]=f[f[x][i]][i];
	for(int i=0;i<g[x].size();i++)
		dfs(g[x][i],x);
}int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=24;~i;i--)
		if(dep[x]-dep[y]>=(1<<i))
			x=f[x][i];
	if(x==y) return x;
	for(int i=24;~i;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}void build(){
	if(!vis[1]) vis[c[++d]=1]=2;
	int dd=d;sort(c+1,c+d+1,cmp);
	for(int i=1;i<dd;i++){
		int lc=lca(c[i],c[i+1]);
		if(vis[lc]) continue;
		vis[lc]=2;c[++d]=lc;
	}sort(c+1,c+d+1,cmp);
	for(int i=1;i<d;i++){
		int x=c[i],y=c[i+1];
		int lc=lca(x,y);
		ve[lc].push_back(y);
	}
}void dp_(int x){
	for(int i=0;i<ve[x].size();i++){
		int y=ve[x][i];dp_(y);
		if(vis[x]==1){
			if(f[y][0]==x)
				fg[x]+=fg[y]-1,dp[x]+=fg[y]-1;
			else fg[x]+=dp[y],dp[x]+=dp[y];
			continue;
		}dp[x]+=dp[y];fg[x]+=dp[y];
	}if(vis[x]==1){
		dp[x]+=g[x].size();
		fg[x]+=g[x].size();
		dp[x]+=1;
	}else fg[x]+=1;
}int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=2;i<=n;i++){
		int fa;cin>>fa;
		g[fa].push_back(i);
	}dfs(1,0);
	while(q--){
		for(int i=1;i<=d;i++){
			ve[c[i]].clear();
			dp[c[i]]=fg[c[i]]=0;
			vis[c[i]]=0;
		}cin>>d;
		for(int i=1;i<=d;i++)
			cin>>c[i],vis[c[i]]=1;
		build();dp_(1);
		cout<<dp[1]<<"\n";
	}return 0;
}
```

---

## 作者：SamHH0912 (赞：0)

Update on 2024/12/30：发现一处笔误。增加了翻法正确性说明和代码中关于 `son[0]` 的说明。

---

题目传送门：

[Luogu](https://www.luogu.com.cn/problem/AT_arc148_c) | [AtCoder](https://atcoder.jp/contests/arc148/tasks/arc148_c)

### 解题思路

自下而上翻，我们总能将任意一棵子树翻成同一个颜色，因此肯定有解。不难猜到，自下而上翻一定是最优解决法。

> 对于翻法正确性的简单说明：
>
> 首先，每个颜色与父亲不同的节点，一定会被翻转奇数次，也就是至少翻一次。
>
> 考虑如下的翻法：先将该节点的所有以其子节点为根的子树翻成和此节点同色的，然后再翻转此节点。如果节点与父亲同色，就无需翻转了。
>
> 这样子的话，这个节点最多只翻了一次，为最优。
>
> 在每次操作过后，无需翻转或者翻转结束的每棵子树的节点颜色都将在各自内部保持一致，确保了不会有重复的翻转操作。


因此，整道题就变成了：给定 $Q$ 组询问，每组询问给出 $M$ 个节点 $v_1,v_2,...,v_M$，将树上这些节点染黑，其余染白，求 **颜色与父节点不同的节点个数**（钦定 $1$ 的父节点为 $0$，且 $0$ 永远染白）。

如何快速统计呢？

对于每个节点 $i$，算出其子节点个数 $son_i$。显然，颜色与父节点不同的节点**只可能是黑节点或黑节点的儿子**。所以我们查这些节点就好了。

然而一个节点的儿子可能有千千万万，怎么办？我们可以转换一下这个问题！每个节点的父亲都是唯一的，所以我们把统计的部分放在父亲上就可以了！

对于每个节点 $i$，记 $t_i$ 为**点 $i$ 的黑子节点的个数**。显然：

- 当点 $i$ 为白点时，其对答案的贡献为 $t_i$；
- 当点 $i$ 为黑点时，其对答案的贡献为 $son_i-t_i$。

当且仅当一个白点有至少一个黑儿子时，其对答案产生的贡献才不会是 $0$，因此有贡献的白节点一定是一个或一些黑节点的父亲。

计算最终答案时，需要布尔数组 `vis` 来标记已经将贡献算入过答案的节点。在输出答案后，需要将 $col$ 数组（颜色数组）、$t$ 数组和 $vis$ 数组（黑点**和它们各自的父亲**都要）清空，以备下一组询问。

时间复杂度 $\mathcal{O}\bigg(N+\displaystyle\sum_{i=1}^{Q} M_i\bigg)$，可过。

### 参考代码

仅供参考，请勿抄袭！


```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long

#define N 200007
int p[N],son[N];

int v[N],t[N];
bool col[N],vis[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	int n,q;
	cin>>n>>q;
	for(int i=2;i<=n;i++) cin>>p[i],son[p[i]]++;//计算 son 数组
	
	while(q--){
		int m;
		cin>>m;//节点集大小
		for(int i=1;i<=m;i++)//黑节点染色，统计 t 数组
            cin>>v[i],col[v[i]]=1,t[p[v[i]]]++;
		int ans=0;//答案初始化
		for(int i=1;i<=m;i++){//计算最终答案
			int x=v[i],f=p[v[i]];//黑点和它的父亲
			if(!vis[x]) vis[x]=1,ans+=son[x]-t[x];//黑点贡献计入答案，打标记
			if(!vis[f]){//黑点父亲
				vis[f]=1;//打标记
				if(col[f]) ans+=son[f]-t[f];//也是黑点
				else ans+=t[f];//是白点
			}
		}
		cout<<ans<<'\n';//输出答案
		for(int i=1;i<=m;i++)//清空数组
            col[v[i]]=vis[v[i]]=vis[p[v[i]]]=0,t[p[v[i]]]=0;
	}
	
	return 0;
}

```

> 眼尖的网友或许已经发现了，`son[0]` 的值一直为 $0$，不会改变。不用担心，由于 `son[i]` 只有在计算黑节点对答案的贡献时才有用，而点 $0$ 永远是白的，因此 `son[0]` 的值不会被使用。

---

谢谢阅读！

---

## 作者：Ratio_Y (赞：0)

感觉现有的几篇题解不是很叙述不是很完备，所以来分享一下自己的想法。

------------
## 思路
首先比较易得的是，不会出现无解的情况：因为任意一个节点我们都可以通过先翻转自身再翻转所有子节点的方式将其单独翻转。

其次，按暴力的方法找到思路：对于一个点集 $S$ 内的点 $m_i$，若他的父节点及以上已经进行了奇数次翻转操作，那么就不需要在该点翻转；若点集 $S$ 之外的点的父节点及以上进行了奇数次翻转操作，此时该点处于翻转状态，我们需要在这里进行一次翻转操作。设 $P=\sum_{i=1}^Q M_i$，则暴力的时间复杂度为 $O(nP)$，显然是会 TLE 的。

考虑到要求反转的点的数量很小，我们尝试着枚举这些点求解。

读入时标记这些点，枚举时判断其父节点是否被标记，若不是意味着我们需要翻转该点，若是则说明他已经被翻转过。我们若仅翻转枚举的该点，那么对答案的贡献应为其子节点的数量之和加上 $1$。

简单画个图模拟一下，发现这样做会产生很多次无用操作。我们在翻转一个被标记的节点时，默认将其子节点再次翻回来，也就是上述的操作；如果一个点的父节点被标记，那么此时该点已经被翻转了两次，我们不用再次翻转该节点，且是要在操作其父节点时不将其二次翻转，这样才能得到最优操作次数。因此在遇到父节点被标记的节点时，我们要将答案减去 $1$。

## 细节处理
这道题搬到我们题库上只给了 $1s$ 的时限，而标记用的数组每次只用了很少的一部分，所以操作完成后手动清零比使用 `memset` 要快很多。

数据的点集中会有父节点后被标记的情况，所以不能边读边做，要把点集先存下来。

## 代码实现

```
#include<bits/stdc++.h>

const int Ratio=0;
const int N=2e5+5;
int n,m,tot,ans;
int fx[N],son[N];
int tag[N],s[N];

namespace Wisadel
{
	short main()
	{
		scanf("%d%d",&n,&m);
		for(int i=2;i<=n;i++)
			scanf("%d",&fx[i]),son[fx[i]]++;
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&tot);ans=0;
			for(int j=1;j<=tot;j++)
				scanf("%d",&s[j]),tag[s[j]]=1;
			for(int j=1;j<=tot;j++)
			{
				if(tag[fx[s[j]]]) ans--;
				else ans++;
				ans+=son[s[j]];
			}
			printf("%d\n",ans);
			for(int j=1;j<=tot;j++) tag[s[j]]=0;
		}
		return Ratio;
	}
}
int main(){return Wisadel::main();}
```

不是很难，但控我一个半小时 ~~（我太蒻了~~

完结撒花~

---

