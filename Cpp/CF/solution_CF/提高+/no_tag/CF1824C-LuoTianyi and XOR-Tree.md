# LuoTianyi and XOR-Tree

## 题目描述

LuoTianyi gives you a tree with values in its vertices, and the root of the tree is vertex $ 1 $ .

In one operation, you can change the value in one vertex to any non-negative integer.

Now you need to find the minimum number of operations you need to perform to make each path from the root to leaf $ ^{\dagger} $ has a [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) value of zero.

 $ ^{\dagger} $ A leaf in a rooted tree is a vertex that has exactly one neighbor and is not a root.

## 说明/提示

The tree in the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824C/f5037f32236cd0c12f91d642bcd0ee6276190035.png) If we change the value in the vertex $ 2 $ to $ 3 $ , the value in the vertex $ 5 $ to $ 4 $ , and the value in the vertex $ 6 $ to $ 6 $ , then the tree will be ok.

The bitwise XOR from the root to the leaf $ 2 $ will be $ 3 \oplus 3=0 $ .

The bitwise XOR from the root to the leaf $ 5 $ will be $ 4 \oplus 7 \oplus 3=0 $ .

The bitwise XOR from the root to the leaf $ 6 $ will be $ 6 \oplus 5 \oplus 3=0 $ .

The tree in the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824C/d9dc7271f6c9662a7281b9aced7a2291ed846421.png) If we change the value in the vertex $ 2 $ to $ 4 $ , the value in the vertex $ 3 $ to $ 27 $ , and the value in the vertex $ 6 $ to $ 20 $ , then the tree will be ok.

The bitwise XOR from the root to the leaf $ 6 $ will be $ 20 \oplus 19 \oplus 7=0 $ .

The bitwise XOR from the root to the leaf $ 8 $ will be $ 11 \oplus 27 \oplus 4 \oplus 19 \oplus 7=0 $ .

The bitwise XOR from the root to the leaf $ 4 $ will be $ 16 \oplus 4 \oplus 19 \oplus 7=0 $ .

The bitwise XOR from the root to the leaf $ 7 $ will be $ 16 \oplus 4 \oplus 19 \oplus 7=0 $ .

In the third example, the only leaf is the vertex $ 4 $ and the bitwise XOR on the path to it is $ 1 \oplus 2 \oplus 1 \oplus 2 = 0 $ , so we don't need to change values.

In the fourth example, we can change the value in the vertex $ 1 $ to $ 5 $ , and the value in the vertex $ 4 $ to $ 0 $ .

Here $ \oplus $ denotes the bitwise XOR operation.

## 样例 #1

### 输入

```
6
3 5 7 5 8 4
1 2
1 3
1 4
3 5
4 6```

### 输出

```
3```

## 样例 #2

### 输入

```
8
7 10 7 16 19 9 16 11
1 5
4 2
6 5
5 2
7 2
2 3
3 8```

### 输出

```
3```

## 样例 #3

### 输入

```
4
1 2 1 2
1 2
2 3
4 3```

### 输出

```
0```

## 样例 #4

### 输入

```
9
4 3 6 1 5 5 5 2 7
1 2
2 3
4 1
4 5
4 6
4 7
8 1
8 9```

### 输出

```
2```

# 题解

## 作者：离散小波变换° (赞：21)

萌萌题。

## 题解

考虑随便树上一个节点 $u$，以及 $u$ 子树内某个叶子节点 $x$。从 $1$ 到 $x$ 的路径可视为 $1\to\cdots\to u\to \cdots \to x$，所以从 $u$ 到任意一个 $x$ 的路径，异或和都要是相等的。

记 $f_u$ 表示从 $u$ 出发，到达 $u$ 子树内每个叶子节点，路径权值相同，至少需要修改多少个节点。显然，只是为了达成「路径权值相同」这一个条件的话，$u$ 的权值没有必要修改。

下面考虑转移。假设 $u$ 有一堆儿子 $v_1,v_2,\cdots,v_k$，那么首先要让 $v_i$ 到 $v_i$ 子树内的叶子的路径权值相等，所以首先要操作 $\sum f_{v_i}$ 次；接着此时 $v_i$ 的权值肯定都没有修改，所以我们要修改尽可能少的 $v_i$ 的权值，这样才能使得 $u$ 到 $u$ 子树内叶子结点的权值相等。

此时出现了困难。因为花费最少次数让 $v_i$ 到 $v_i$ 内叶子节点的权值相等，最终相等的权值可能有很多种情况。我们记「**在修改次数最少的情况下**」可以取得的相等的值，组成的集合为 $M_{v_i}$。为什么非得是修改次数最少？这是因为，在修改次数不是最小的情况下，即使可以使得所有权值都等于某个值 $w$，也不如任取某个修改次数最小的情形，通过修改 $v_i$ 的权值使得相等的权值为 $w$。

那么就变成了这样一个过程：

- 先递归计算出 $M_{v_1},M_{v_2},\cdots,M_{v_k}$；
- 维护可重集 $S=M_{v_1}\cup M_{v_2}\cup\cdots\cup M_{v_k}$；
- 找到 $S$ 中出现次数最多的那一些元素，记最多的出现次数为 $t$，那么 $f_u=(\sum f_{v_i})+k-t$。同时将这些出现次数最多的元素，**异或上** $u$ 的权值，放到 $M_u$ 里。

如此操作，直到计算出 $f_1$ 和 $M_1$，检查 $M_1$ 里有没有元素 $0$。如果有元素 $0$，答案就是 $f_1$，否则答案为 $f_1+1$。

于是可以考虑启发式合并。先计算出 $u$ 的重儿子 $g$ 的相等值集合 $M_g$，然后考虑将其他儿子的答案合并进去。我们可以先将 $g$ 以外的儿子的 $M$ 值合并进 $S$，合并完后，**对于 $\bm S$ 内的每个键值**查询在不在 $M_g$ 里，如果在，就把对应的次数 $+1$。（如果遍历 $M_g$ 更新 $S$ 的值，复杂度就成了 $O(\mathit{size}_u \log n)$，但是遍历 $S$ 内的元素来更新 $S$，复杂度就成功降到了 $O((\mathit{size}_u-\mathit{size}_g) \log n)$）。如果出现次数最多的元素，出现次数超过了 $1$，那么这些元素**一定是在 $\bm S$ 里的**，那么就可以抛弃 $M_g$，遍历 $S$ 内的元素放到 $M_u$ 里；否则，如果出现次数最多的元素只出现了 $1$ 次，就说明 $M_u=M_g\cup S$。这个时候，仍然是遍历 $S$ 的元素插入到 $M_g$ 里，接着把 $M_u$ 指向 $M_g$。

但是这时又有最后一个问题。我们需要把 $M_u$ 内所有元素异或上 $u$ 的权值。解决起来很简单，维护一个标记 $K_u$，$M_u$ 里实际存储的元素是代码里写着的 $M_u$ 里的值异或上 $K_u$。所以，在把 $M_{v_i}$ 合并进 $S$ 时，要把对应元素异或上 $K_{v_i}$ 再合并；在 $u$ 直接拿来 $M_g$ 充当 $M_u$ 时，也需要精细考虑对应的标记。

上文提到的 $M$ 和 $S$ 都可以直接用 $\text{map}$ 实现。复杂度最坏为 $\mathcal O(n\log ^2n)$，在原树是一棵完全二叉树时取得。

实现细节有点多，可以看代码。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 1e5 + 3;
vector <int> V[MAXN];
int G[MAXN], T[MAXN], K[MAXN], A[MAXN], F[MAXN], S[MAXN];
void dfs0(int u, int f){
    S[u] = 1;
    for(auto &v : V[u]) if(v != f){
        dfs0(v, u), S[u] += S[v];
        if(S[v] > S[G[u]]) G[u] = v;
    }
}
map<int, bool> M[MAXN];
void dfs(int u, int f){
    if(V[u].size() == 1 && f){
        T[u] = u, M[T[u]][0] = true, K[u] = A[u], F[u] = 0;
    } else {
        map<int, int> S;
        dfs(G[u], u);
        T[u] = T[G[u]];
        K[u] = K[G[u]];
        int c = 1, sum = F[G[u]], w = 1;
        for(auto &v : V[u]) if(v != f && v != G[u]){
            dfs(v, u);
            for(auto &x : M[T[v]]){
                S[x.first ^ K[v]] ++;
            }
            ++ c, sum += F[v];
        }
        for(auto &x : S){
            if(M[T[u]].count(x.first ^ K[u])) ++ x.second;
            w = max(w, x.second);
        }
        if(w == 1){
            for(auto &x : S){
                M[T[u]][x.first ^ K[u]] = true;
            }
        } else {
            M[T[u]].clear();
            for(auto &x : S){
                if(x.second == w)
                    M[T[u]][x.first ^ K[u]] = true;
            }
        }
        K[u] ^= A[u];
        F[u] = sum + c - w;
    }
}
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int main(){
    int n = qread();
    up(1, n, i) A[i] = qread();
    up(1, n - 1, i){
        int u = qread(), v = qread();
        V[u].push_back(v);
        V[v].push_back(u);
    }
    dfs0(1, 0);
    dfs(1, 0);
    for(auto &x : M[T[1]]){
        if((x.first ^ K[1]) == 0){
            printf("%d\n", F[1]); exit(0);
        }
    }
    printf("%d\n", F[1] + 1);
    return 0;
}
```

---

## 作者：activeO (赞：14)

## 题目大意

给定一棵 $ n $ 个节点的树，根节点为 $ 1 $，每个点有一个点权 $ a_i $，每次操作可以选择一个点任意修改点权，求最少的操作次数，使得每一条根结点到叶子结点的路径上的异或和都为 $ 0 $。

## 思路

首先只要让整棵树的各条根到叶子节点的异或和变成相等的，最后调节根节点 $ 1 $ 的值使异或和变为 $ 0 $ 就可以了。

所以现在考虑子树 $ u $，我们目标将这颗子树内的每一条从根到叶子结点的路径的异或和相等。

这里我们记录数组 $ b_v $ 为 $ 1 $ 到 $ v $ 的异或和，如果两个点都在 $ u $ 这颗子树内，显然 $ b_{v1} $ 就会和 $ b_{v2} $ 相等了，因为他们都将 $ 1 $ 到 $ u $ 上的值异或了一遍。

回归正题，每次我们显然儿子 $ v $ 的这颗子树变为都相等的值，这个时候，显然 $ a_v $ 是没有变过的，我们就可以通过调节 $ a_v $ 来使所有的路径都变成同一个值。变成的值我们就贪心地选择出现次数最多的那个值。为什么呢？因为如果你不选择次数最多的那个值，你最少会比本来的多做 $ 1 $ 步，这和本来的最优解的如果以后再调节祖先的值是一样的，所以这样选择肯定不劣。

然后最后在判断一下需不需要调节 $ a_1 $ 就可以了。

实现方面可以用 map 记录可以修改的值的集合，可以开多个 map，每次交换两个 map 的地址更新（实际上这里也是启发式合并，每次从别的儿子节点往信息最多的信息节点合并信息，~~刚开始蠢笨了~~）。具体看代码。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=1e5+5;
int a[maxn],id[maxn],n,res=0;
struct edge{
	int to,nxt;
}e[maxn<<1];
int head[maxn],len;
map<int,int> mp[maxn],tmp;

inline void init(){
	memset(head,-1,sizeof(head));
	len=0;
}
void add(int u,int v){
	e[++len].to=v;
	e[len].nxt=head[u];
	head[u]=len;
}

void dfs(int u,int f){
	if(f&&e[head[u]].nxt==-1){
		// printf("kkkk%d\n",u);
		mp[id[u]][a[u]]++;
		return;
	}
	int maxx=1,cnt=0;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		a[v]^=a[u];
		dfs(v,u);
		if(mp[id[u]].size()<mp[id[v]].size()) swap(id[u],id[v]);
		for(auto now : mp[id[v]]){
			mp[id[u]][now.first]+=now.second;
			maxx=max(maxx,mp[id[u]][now.first]);
		}
		cnt++;
	}
	res+=cnt-maxx;
	// map<int,in>
	tmp.clear();
	if(maxx>1){
		for(auto now : mp[id[u]]){
			if(now.second==maxx) tmp[now.first]=1;
		}
		swap(mp[id[u]],tmp);
	}
}

int main(){
	
	int n;
	
	init();
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		id[i]=i;
	}
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		add(u,v);
		add(v,u);
	}
	
	dfs(1,0);
	
	printf("%d\n",res+(!mp[id[1]][0]));
	
	return 0;
}
```


---

## 作者：Maverik (赞：10)

### Statement

给定一棵 $n$ 个节点的树，根节点为 $1$，每个点有一个点权 $a_i$，每次操作可以选择一个点任意修改点权，求最少的操作次数，使得每一条根结点到叶子结点的路径上的异或和都为 $0$。  

$n\le 10^5,a_i\le 10^9$

### Solution


可以先弱化问题为让各条叶子路径异或相等的代价，再对根进行调整。直接考虑树形 dp，$g_{x,i}$ 表示只操作 $x$ 子树内，使经过 $x$ 的所有叶子路径异或和变为 $i$ 的最小操作次数。由于可以对 $x$ 进行操作，所以 $\max_i\{g_{x,i}\}-\min_i\{g_{x,i}\}\le 1$。

设 $f_x=\min_i\{g_{x,i}\}$，$S_x=\{i~|~f_x=g_{x,i}\}$，$y\in son_x$，考虑如何转移它们：对于 $\cup S_y$，可以直接把一种元素上传到 $S_x$，其余都需要额外为1的代价，贪心的，直接取出现次数最多的上传到 $S_x$ 即可，即：

$$
f_x=\sum_y (f_y+1)-\max_{i\in\cup S_y}\{\sum_y [i\in S_y]\}
$$

用 set 维护集合，map 维护出现次数，启发式合并 set，复杂度 $O(n\log^2 n)$，代码很短。


### code
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int maxn=1e5+10;
int n,a[maxn],f[maxn];
vector<int>e[maxn];
set<int>s[maxn];
inline void dfs(int x,int fa,int oplus)
{
    map<int,int>cnt;int mx=0;
    if(e[x].size()==1 && x!=1) return s[x].insert(oplus),f[x]=0,void();
    for(auto y:e[x]) if(y!=fa)
    {
        dfs(y,x,oplus^a[y]),f[x]+=(f[y]+1);
        if(s[x].size()<s[y].size()) swap(s[x],s[y]);
        for(auto v:s[y]) if(s[x].count(v)) cnt[v]++; else s[x].insert(v);
    }
    if(!cnt.empty()) 
    {
        for(auto [num,ct]:cnt) mx=max(mx,ct);
        f[x]-=(mx+1),s[x].clear();
        for(auto [num,ct]:cnt) if(ct==mx) s[x].insert(num);
    } 
    else f[x]--; 
}
signed main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);
    cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,x,y;i<n;i++) cin>>x>>y,e[x].pb(y),e[y].pb(x);
    dfs(1,0,a[1]),cout<<f[1]+(!s[1].count(0));
    return 0;
}
```

---

## 作者：小木虫 (赞：8)

### Preface  
我提供的是一种非官方的大常数单 $\log$ 做法。  
### Problem  
给你一颗树，每一次操作可以更改一个点权，问你最少需要多少次操作使得所有根到叶子节点的路径异或值为 $0$。  
### Solution  
先树上前缀和，路径转点权，容易发现更改一个点的权相当于更改其子树的所有权。  
考虑从下往上改点权。  
由于题目要求都为 $0$，而一个更改会牵连整个子树，所以说在一个点 $u$ 被操作之前它的所有子树应当是统一权值的。  

那么，容易设出 dp 状态 $f_{u,c}$ 为 $u$ 点的子树内的叶子节点的点权全为 $c$ 的最小操作次数。  

然后你发现，转移方程如下：  
$$f_{u,c}=\sum_{v\in e_u}f_{v,c},\space f_{u,c}=\min(f_{u,c},\min_{j<2^{30}}f_{u,j}+1)$$  
意义为，所有子树的权值应统一，所以先进行一次同颜色加法转移。  
然后，你可以同时更改所有子树权值一次，所以进行第二次取异颜色最小值的转移。  

然后你发现这个 dp 数组是可以线段树维护的，两个转移可以通过线段树合并来实现。  

这个线段树合并还和一般的线段树合并不一样，它会下传，而这个过程会新建节点，为了防止复杂度退化，我们需要多做一个标记，用来做线段树合并操作的懒惰标记，同时将下传建出来的节点和普通插入节点区分开，因为它只需要一个点就可以存储所有信息，线段树合并时直接并上去即可。  

具体来说，我们要设一个存储区间 $\min f$ 的树信息，一个存储集体加法（即线段树合并懒惰）的区间标记，一个存储集体取 $\min$ 的区间标记，注意下传顺序的问题，实现细节较多，常数较大，具体见 $O(n\log n)$ 代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int V=(1<<30);
const int maxv=1e9;
int n,a[N],u,v,root[N],cnt;
vector <int> edge[N];
void pre_solve(int u,int fa){
    a[u]^=a[fa];
    for(auto v:edge[u]){
        if(v==fa)continue;
        pre_solve(v,u);
    }
}int l[N*61],r[N*61],tag[N*61],val[N*61],lzy[N*61];
void pushup(int rt){val[rt]=min(val[l[rt]],val[r[rt]]);}
void pushdown(int rt){
	if(lzy[rt]){
    	lzy[l[rt]]+=lzy[rt];lzy[r[rt]]+=lzy[rt];
    	lzy[l[rt]]=min(lzy[l[rt]],maxv);
    	lzy[r[rt]]=min(lzy[r[rt]],maxv);
        val[l[rt]]+=lzy[rt];val[r[rt]]+=lzy[rt];
        val[l[rt]]=min(val[l[rt]],maxv);
        val[r[rt]]=min(val[r[rt]],maxv);
        if(tag[l[rt]])tag[l[rt]]+=lzy[rt],tag[l[rt]]=min(tag[l[rt]],maxv);
        if(tag[r[rt]])tag[r[rt]]+=lzy[rt],tag[r[rt]]=min(tag[r[rt]],maxv);
    	lzy[rt]=0;
	}
    if(tag[rt]){
        if(!l[rt])l[rt]=++cnt,val[l[rt]]=tag[rt];
        tag[l[rt]]=min(tag[l[rt]],tag[rt]);
        if(!tag[l[rt]])tag[l[rt]]=tag[rt];
        val[l[rt]]=min(val[l[rt]],tag[rt]);
        //if(val[l[rt]]==tag[rt])lzy[l[rt]]=0;
        if(!r[rt])r[rt]=++cnt,val[r[rt]]=tag[rt];
        tag[r[rt]]=min(tag[r[rt]],tag[rt]);
        if(!tag[r[rt]])tag[r[rt]]=tag[rt];
        val[r[rt]]=min(val[r[rt]],tag[rt]);
        //if(val[r[rt]]==tag[rt])lzy[r[rt]]=0;
        tag[rt]=0;
    }
}
void update(int &rt,int left,int right,int x,int y){
    if(!rt)rt=++cnt,val[rt]=maxv;
    if(left==right){val[rt]=y;return;}
    pushdown(rt);int mid=(left+right)/2;
    if(x<=mid)update(l[rt],left,mid,x,y);
    else update(r[rt],mid+1,right,x,y);
    pushup(rt);
}
int merge(int rt1,int rt2,int left,int right){
    if(!rt1)return rt2;if(!rt2)return rt1;
    if((l[rt1]||r[rt1])&&(l[rt2]||r[rt2])){
        pushdown(rt1),pushdown(rt2);
	}else{
        if(l[rt2]||r[rt2])swap(rt1,rt2);
        if(tag[rt1])tag[rt1]+=val[rt2];
		val[rt1]+=val[rt2];lzy[rt1]+=val[rt2];
		tag[rt1]=min(tag[rt1],maxv);
		val[rt1]=min(val[rt1],maxv);
		lzy[rt1]=min(lzy[rt1],maxv);
		return rt1;
    }int mid=(left+right)/2;
    l[rt1]=merge(l[rt1],l[rt2],left,mid);
    r[rt1]=merge(r[rt1],r[rt2],mid+1,right);
    pushup(rt1);return rt1;
}
int query(int rt,int left,int right,int x){
    if(left<right)pushdown(rt);
	int mid=(left+right)/2;
    if(left==right)return val[rt];
    if(x<=mid)return query(l[rt],left,mid,x);
    else return query(r[rt],mid+1,right,x);
}
void dfs(int u,int fa){
    if(edge[u].size()==1&&fa!=0)
        update(root[u],0,V,a[u],0);
    for(auto v:edge[u]){
        if(v==fa)continue;dfs(v,u);
        root[u]=merge(root[u],root[v],0,V);
    }int p=val[root[u]];tag[root[u]]=p+1;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;val[0]=maxv;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<n;i++){
        cin>>u>>v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }pre_solve(1,0);dfs(1,0);
    cout<<query(root[1],0,V,0);
    return 0;
}
```


---

## 作者：james1BadCreeper (赞：6)

对于一个子树内的所有到叶子节点的路径的异或值我们都必须把它处理成一个，否则接下来无法操作。不难发现这个过程是可以贪心的，因为对于相同的步数所可以改成的不同异或值，我们只需要调整根节点的修改值即可变成同样的情况。

设 $f_{i,j}$ 代表对于当前节点 $i$ 来说，其子树中用最小步数满足条件后的异或值可以为 $j$ 的节点数量个数。那么贪心地，答案在 $i$ 节点就要加上它地儿子个数减去异或值相同的节点数量的最大值。

启发式合并维护 $f$ 即可，可以证明时间复杂度为 $O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans, a[100005]; 
vector<int> G[100005]; 
map<int, int> f[100005]; 

void dfs(int x, int fa) { 
    if (fa && G[x].size() == 1) return f[x][a[x]] = 1, void(); 
    int mx = 1, cnt = 0; 
    for (int y : G[x]) if (y != fa) {
        a[y] ^= a[x], dfs(y, x), ++cnt; 
        if (f[x].size() < f[y].size()) swap(f[x], f[y]); 
        for (auto [v, k] : f[y]) mx = max(mx, f[x][v] += k); 
    }
    ans += cnt - mx; 
    map<int, int> tmp; 
    if (mx > 1) {
        for (auto it : f[x]) if (it.second == mx) tmp[it.first] = 1; 
        swap(f[x], tmp); 
    }
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n; 
    for (int i = 1; i <= n; ++i) cin >> a[i]; 
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v; 
        G[u].emplace_back(v); G[v].emplace_back(u); 
    }
    dfs(1, 0); 
    cout << ans + (!f[1][0]) << "\n"; 
    return 0;
}
```

---

## 作者：DengDuck (赞：5)

给 @james1BadCreeper 补充一个时间复杂度的证明。

首先启发式合并的时间复杂度证明是容易的，考虑你每次合并到别人都是别人比你大的情况，这是整个连通块的大小对于你来说显然翻倍，翻倍的次数最多 $\log n$ 次。

那么我们发现末尾我们要提取所有最大的元素，这个时间复杂度怎么分析呢？

考虑如果出现次数都是 $1$，那么我们不做操作，没有影响。

否则，最大的出现次数比 $1$ 大，其他的出现次数的元素就会被删除，由于这种情况下最大的元素不超过 $\lfloor \frac n 2\rfloor$ 个，所以对于一个连通块，这种操作不会超过 $\log n$ 次。

所以时间复杂度是 $\mathcal O(n\log ^2 n)$ 的，时间复杂度瓶颈在于维护出现次数的 `map`。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define fir first
#define sec second
using namespace std;
//const LL inf;
const LL N=2e5+5;
//const LL M;
//const LL mod;
//const LF eps;
//const LL P;
LL n,ans,a[N];
vector<LL>v[N];
map<LL,LL>f[N];
void dfs(LL x,LL fa)
{
	if(fa&&v[x].size()==1)
	{
		f[x][a[x]]=1;
		return;
	}
	LL mx=1,cnt=0;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		a[i]^=a[x],cnt++;
		dfs(i,x);
		if(f[x].size()<f[i].size())swap(f[x],f[i]);
		for(pLL j:f[i])f[x][j.fir]+=j.sec,mx=max(mx,f[x][j.fir]);
	}
	ans+=cnt-mx;
	map<LL,LL>tmp;
	if(mx>1)
	{
		for(pLL j:f[x])
			if(j.sec==mx)tmp[j.fir]=1;
		swap(f[x],tmp);
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<n;i++)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		v[x].pb(y),v[y].pb(x);
	}
	dfs(1,0);
	printf("%lld",ans+(f[1][0]==0));
	return 0;
}
//RP++
```

---

## 作者：BYR_KKK (赞：2)

神秘贪心题真不简单吧。

对于一个子树而言，所有叶子到子树根的路径异或和必须相同。令 $f_{i,j}$ 代表子树根是 $i$，子树内所有叶子到 $i$ 的异或和为 $j$ 的最小代价，对于任意 $j$ 和 $k$，$|f_{i,j}-f_{i,k}|\le 1$，因为我们可以通过到达某个状态后修改子树根即可。

因此我们只需维护所有让 $f_{i,j}$ 最小的 $j$，转移就是取在儿子中出现次数最多的 $j$ 转移过来。考虑时间复杂度，最坏情况显然是每个 $j$ 都只出现一次，此时所有 $j$ 都要保留，否则必然会有 $j$ 被丢弃，时间复杂度不会劣于没有 $j$ 被丢弃的情况。对于最坏情况我们考虑启发式合并，不难发现时间复杂度为 $O(n\log^2 n)$。

---

## 作者：BINYU (赞：2)

## 题意

给定一棵有 $n$ 个点且根为 $1$ 的树，点有点权，你每次可以修改一个点的点权为任意值，最后要使得叶子节点到根路径上的点的点权异或和全为 $0$，求最小的修改次数。

## 思路

发现在以任意点为根的子树内，所有叶子结点到当前节点路径的点权异或和是相等的，可以用反证法证明。所以我们可以给每一棵子树定义一个权值：子树内的所有叶子结点到该子树根路径的异或和，改变这个值与改变当前子树根的值等价，这说明当前问题能递归成多个子问题分别求解，在每一层的计算中，我们**只改变当前节点儿子的值**。

先考虑最末一层子问题：假设根在 $u$，$u$ 的儿子全为叶子结点。这个问题等价于：一共有 $cntson_u$ 个值，问至少需要修改多少个值才能把所有值变相等（其中 $conson_u$ 表示 $u$ 的子节点数）。显然变成众数最优，考虑用一个集合 $S_u$ 表示在以 $u$ 为根的情况下的所有众数，这个集合就是在子树 $u$ 代价取最小时的的所有可能权值。

再考虑向上返回时的情况，这里每个子节点的权值变为了集合，但我们不能求集合的众数，我们反向思考，先选取一个数，让他在当前节点 $u$ 的所有儿子的集合中出现次数最高，这样一定可以保证到目前为止的修改次数最小。

最后如果 $0 \in S_1$，说明不用修改 $1$ 的权值，否则要修改。

接下来考虑实现这个过程：

对于每一个节点 $u$，我们建一个 set：$S_u$ 来存储上述集合，一个 map：$cnt_u$ 来存储每个数在 $u$ 儿子集合中的出现次数。转移时直接暴力查找$cnt_u$ 中的最大值加入 $S_u$，这个时间复杂度最坏是 $O(n^2)$ 的。

考虑优化，发现这个算法在众数出现次数不为 $1$ 时，每次往上传的 set 的大小都至少减半，这时是 $O(n\log n)$ 的，所以它的瓶颈在所有儿子集合内所有数均不相等的情况，我们考虑优化这种情况。我们对于每个节点 $u$ 把他的重儿子 $son_u$ 单独拿出来，不计入 $cnt_u$ 内，先算其它儿子。

此时如果众数出现次数不为 $1$，则一定在 $cnt_u$ 内，我们依然可以枚举 $cnt_u$，如果众数出现次数不为 $1$，按上述方法处理即可。

如果众数出现次数为 $1$，我们可以把 $cnt_u$ 中的所有数加入到 $S_{son_u}$ 中，然后把 $S_{son_u}$ **直接** 赋给 $S_u$。

但这样会忘了算 $u$ 的点权，我们可以打上一个懒标记 $lz_u = lz_{son_u} \otimes a_u$ 在把 $u$ 的儿子 $v$ 加入 $cnt_u$ 这一步时先把值异或上 $lz_v$，把 $cnt_u$ 加入 $S_{son_u}$ 时要异或上 $lz_{son_u}$，这样能抵消在清空懒标记时多异或的一次，不会把 $lz_{son_u}$ 算到 $u$ 的其它儿子中。

此时每次计算第二种情况时不会再去动重儿子，所以一共会进行 $O(n\log n)$ 次 set 和 map 的插入操作，总时间复杂度 $O(n\log^2 n)$。

空间上我们可以动态处理，不建全局的 set 和 map，在 DFS 返回时返回所需的值，空间复杂度为 $O(n)$ 的。


---

## 作者：Mirasycle (赞：1)

首先有一个观察就是对于同一个子树下的叶子节点，他们到子树的根的时候，权值应该变成一样的。



于是设 $f_{u,i}$ 表示将 $u$ 子树内的权值全部调整为 $i$ 的最小代价。

转移方程也很好写出 $f_{u,i}=\min (\sum\limits_v f_{v,i},f_{u,j}+1)$。

$+1$ 是代表我们可以在 $u$ 这个点修改 $a_u$ 的值，达到整体变化的一个效果。

可以发现其实所有的 $f_u$ 值就分成两种，一种是最小值，还有一种是最小值 $+1$。于是我们直接维护所有能取到最小值的点的集合即可，不难发现这些点只有可能是从根到叶子节点一路异或出来的值。

每次在 $u$ 点，我们启发式合并所有儿子的集合。合并出来的是一个可重集，看看哪种取值出现次数最多，就很显然为本次的最小值取值点（可能有多个）。

可以发现每次都调成最小值肯定是最优的，因为如果后续需要别的值，只需要 $1$ 的代价就可以立刻变成别的值，而如果我们没取到最小值，本身就比最小值多花了至少 $1$ 的代价。故直接取最小值，答案直接累加 $son-num$ 即可，其中 $son$ 是该点儿子的个数，$num$ 是相同儿子最小值点的个数的最大值。

现在有一个问题就是启发式合并之后，如何清楚哪些非最小值点。反正我是没想到，看了题解证明才会的。就是如果 $num=1$ 的话所有点都是最小值点就不用动了，如果 $num\ge 2$ 的时候，我们暴力遍历集合，剔除掉非最小值元素还有把最小值的出现次数设置为 $1$。复杂度正确的原因是将出现次数 $\ge 2$ 的最小值元素设置为 $1$ 个至少将最小值个数减半，而同时清空了所有非最小值，所以整个集合大小至少也是减半了，这个最多进行 $\log $ 次。

时间复杂度 $O(n\log^2 n)$。

---

## 作者：DeepSeaSpray (赞：1)

# CF1824C LuoTianyi and XOR-Tree

[LuoTianyi and XOR-Tree](https://www.luogu.com.cn/problem/CF1824C)

略去题面。

想到树形 DP ，$f[u]$ 表示将 $u$ 的子树中所有叶子节点到根节点的异或值变得一致所需要的最少操作次数（只改变子树中的值即可做到）。

为什么不记录到任意数所需要的操作次数？因为在 $f[u]$ 的基础上只需要在做一步就可以变成任意数。

同时因为可能有很多种可能的异或值都可以通过相同的最少操作次数取得，所以我们需要而外记录集合 $M[u]$。

接下来考虑转移。设可重集合 $S[u] = M[v_1] \cup M[v_2] \cup \dots \cup M[v_m]$ 其中 $v$ 是 $u$ 的儿子。

找到 $S[u]$ 中出现最多的数出现的次数 $w$。

那么有转移：

$$
f[u] = f[v_1] + f[v_2] + \dots + f[v_m] + m - w
$$

意思就是出现最多的数不变，将其他数改过来。

最后需要将所有的数异或上该点的权值。

时间瓶颈在集合操作上。

先看合并操作，仿照重链剖分的思想，重儿子集合不动，先把轻儿子合并到 $S[u]$。

根据重链剖分的原理，从一个点开始不会跳超过 $\log n$ 条轻链，所以合并次数不超过 $n \log n$ 次。

接着遍历 $S[u]$ 在 $M[sn[u]]$（$sn[u]$ 为 $u$ 的重儿子）查找与其相同的值，就可以求出 $w$。（注意此处 $M[sn[u]]$ 为不可重集）。

如果 $w = 1$，那么说明 $S[u] = S[u] \cup M[sn[u]]$。将 $S[u]$ 插入 $M[sn[u]]$ ，再将 $M[u]$ 指向 $M[sn[u]]$ 即可。

如果 $w \gt 1$，那么舍弃 $S[sn[u]]$，将 $S[u]$ 插入 $M[u]$。

因为我们只操作 $S[u]$ 所以时间复杂度仍然有保证。

对于集体异或，打个懒标记之类的即可。

代码实现上，需要注意：

- 使用 map 代替 set，可以极大减小常数。
- 不要使用 unordered_map。
- 叶子节点的处理
- 懒标记的处理。

如果无法正常提交，尝试使用 c++17 及以上的语言。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn=1e5;
int n;
int a[maxn+5];
struct Edge{int u,v,nxt;};
Edge e[2*maxn+5];
int hd[maxn+5],et;
int sz[maxn+5],sn[maxn+5];
int f[maxn+5];
map<int,int> S[maxn+5];
map<int,int> M[maxn+5];
int T[maxn+5];//指针数组
int V[maxn+5];//异或数组
inline void Adde(int u,int v){
	e[et].u=u,e[et].v=v;
	e[et].nxt=hd[u],hd[u]=et++;
}
void Dfst(int u,int fa){//求重儿子
	int v;
	sz[u]=1;
	for(int i=hd[u];~i;i=e[i].nxt){
		v=e[i].v;
		if(v==fa) continue;
		Dfst(v,u);
		sz[u]+=sz[v];
		if(sz[sn[u]]<sz[v]) sn[u]=v;
	}
}
void Dfsf(int u,int fa){
	int v;
	T[u]=u;
	for(int i=hd[u];~i;i=e[i].nxt){
		v=e[i].v;
		if(v==fa) continue;
		Dfsf(v,u);
		if(sn[u]!=v)
			for(pii j:M[T[v]]) S[u][j.fi^V[v]]++;
		f[u]+=f[v]+1;
	}
	if(f[u]){
		int mx=1;
		for(pii i:S[u]){
			mx=max(mx,(int)(i.se
				+M[T[sn[u]]][i.fi^V[sn[u]]]));
		}
		f[u]-=mx;
		if(mx==1){
			for(pii i:S[u])
				M[T[sn[u]]][i.fi^V[sn[u]]]++;
			T[u]=T[sn[u]];
			V[u]^=V[sn[u]];
		}
		else{
			for(pii i:S[u]){
				if((int)(i.se
					+M[T[sn[u]]][i.fi^V[sn[u]]])==mx)
					M[T[u]][i.fi]++;
			}
		}
	}
	else M[u][0]++;//特判叶子节点
	V[u]^=a[u];
}
signed main(){
	int u,v;
	memset(e,-1,sizeof(e));
	memset(hd,-1,sizeof(hd));
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		Adde(u,v),Adde(v,u);
	}
	Dfst(1,0);
	Dfsf(1,0);
	printf("%d",(int)(f[1]-M[T[1]][V[1]]+1));
	return 0;
}
```

---

## 作者：ricky_lin (赞：1)

# CF1824C LuoTianyi and XOR-Tree

我们可以证明，如果需要异或，取一个点的子树内异或次数更少的一定不会更劣。

**prove:**

> 如果说在一个点处取次数更多的方案，在它的父亲处最多只会减少该点所在子树的一次异或，所以取最少的次数的方案一定不会更劣。

因为我们已经证明了每次去子树内异或次数更小的，一定不会更劣，所以我们可以用 `DP` 解决异或次数的问题。

我们设 $f_u$ 表示以 $v$ 为根的子树，最小的异或次数，$cnts_u$ 记为 $u$ 的儿子个数，$maxs_u$ 记为 $u$ 的所有儿子中出现最多的异或值的出现次数。
$$
f_u \gets \sum f_v + cnts_u - maxs_u
$$


然而，我们最小异或次数相同的方案，显然不能直接在当前子树处理，需要将所有方案给到他的父亲，让他的父亲决定。

所以我们需要对于每个节点开一个 `map`，并且使用启发式合并对所有方案进行合并。

写启发式合并的时候需要注意：

- 如果说 $maxs$ 为 $1$，那么我们就直接将儿子中最大的 `map` 和 父亲的 `map` 交换，并且给父亲整体打一个 `tag` （因为此时如果去遍历最大的那个 `map` 会使复杂度退化）。

- 如果说 $maxs$ 大于 $1$，那么我们就直接去暴力更新父亲的 `map`（因为如果 $maxs$ 大于 $1$，那么这个儿子中最大的 `map` 的大小一定是小于 $\frac {siz_u} 2$ 的，满足启发式合并维持时间复杂度的条件）。

- 如果是叶节点，需要进行特判对 `map` 赋值。

最后一个小知识：`swap` 交换两个 `STL` 容器时间复杂度近似 $O(1)$。

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 2e5 + 8;
#define st first
#define ed second
int n;
int a[NN];
struct Edge{
	int to,next;
}edge[NN << 1];
int head[NN],cnt;
int tag[NN];
int f[NN];
map<int,int> m[NN]; 
void init(){
	memset(head,-1,sizeof(head));
	cnt = 1;
}
void add_edge(int u,int v){
	edge[++cnt] = {v,head[u]};
	head[u] = cnt;
}
void dfs(int u,int fa){
	int maxs = 0,pos = 0,cnts = 0;
	for(int i = head[u]; i != -1; i = edge[i].next){
		int v = edge[i].to;
		if(v == fa) continue;
		++cnts;
		dfs(v,u);
		f[u] += f[v];
		if(m[v].size() > maxs) maxs = m[v].size(),pos = v;
	}
	if(cnts == 0) return m[u][a[u]] = 1,void(0);//如果是叶节点，需要进行特判对 map 赋值
	maxs = 1;
	for(int i = head[u]; i != -1; i = edge[i].next){
		int v = edge[i].to;
		if(v == fa || v == pos) continue;
		for(auto it : m[v]) maxs = max(maxs,m[pos][it.st ^ tag[v] ^ tag[pos]] += it.ed);
	}
	f[u] += cnts - maxs;
	if(maxs > 1){
		for(auto it : m[pos]){//暴力更新父亲的 map
			if(it.ed != maxs) continue;
			m[u][it.st ^ a[u] ^ tag[pos]] = 1;
		}
		m[pos].clear();//防止 MLE
	}
	else swap(m[u],m[pos]),tag[u] = a[u] ^ tag[pos];//将儿子中最大的 map 和 父亲的 map 交换，并打上标记
}
int main(){
	scanf("%d",&n);init();
	for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	for(int i = 1,u,v; i < n; ++i){
		scanf("%d%d",&u,&v);
		add_edge(u,v);add_edge(v,u);
	}
	dfs(1,1);
	printf("%d",f[1] + (!m[1].count(tag[1])));
}
```

---

## 作者：shinkuu (赞：0)

duel 随到了这个之前 div2 场上没过的题，30min 取之，记录一下。

记 $f_i$ 表示 $i$ 到根的点权异或和，考虑一些特殊一点的情况，比如一个菊花。此时你的策略一定是先把全部子节点的 $f_i$ 变一样，然后一次操作根。

然后考虑拓展成一般的树。注意到进行完一个子树内的操作后，子树内所有叶子的 $f_i$ 一定全部相等。

这启示我们进行 dp：设 $dp_{u,i}$ 表示已经进行完 $u$ 子树内的操作，所有叶子的 $f_v$ 都为 $i$ 的最少操作数。转移为 $dp_{u,i}=\sum_{v\in son}dp_{v,i},dp_{u,i}=\min dp_{u,j}+1$。这样是 $O(nV)$ 的。

然后观察性质。不难发现 $dp_{u,*}$ 的极差为 $1$，并且取到 $\min dp_{u,i}$ 的 $i$ 个数不超过子树内叶子个数。于是考虑用一个 set 记录当前有哪些 $i$ 为 $\min$。

然后转移，我们需要求出 $\min dp_{u,i}$ 以及对应的 $i$。考虑这样的 $i$，不难发现它一定是在所有儿子的 set 中出现次数最多的。设其出现了 $x$ 次，儿子有 $y$ 个，则 $\min dp_{u,i}=y-x+\sum\min dp_{v,j}$。

然后考虑维护每个 $i$ 在儿子中的出现次数。考虑把上面的 set 换成 map，储存每个 $i$ 的出现次数。合并时启发式合并，同时记录上述的 $x$。

但是发现，若 $x>1$，在回溯之前需要把 $dp_{u,i}\not=x$ 的删掉，然后把剩下的出现次数设为 $i$。事实上这一部分可以暴力做，因为所有这样的出现次数之和，即 map 第二维的和为 $O(n)$ 的，每次 $x>0$ 暴力枚举就是用了 $O(k)$ 的时间使这个和至少减少 $\frac x2$，所以总的枚举次数不会超过 $O(n)$。

最后判断 $dp_{1,i}$ 是否为 $\min$，将答案加上 $1$。总时间复杂度 $O(n\log^2 n)$。

code：

```cpp
int n,m,c[N],mx[N],dp[N],deg[N];
map<int,int> mp[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void dfs(int u,int f){
	c[u]^=c[f];
	if(deg[u]==1&&f){
		mp[u][c[u]]=1;
		mx[u]=1;
		return;
	}
	int son=0;
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs(v,u);
		if(mp[u].size()<mp[v].size()){
			swap(mp[u],mp[v]);
			swap(mx[u],mx[v]);
		}
		for(auto [x,y]:mp[v]){
			mp[u][x]+=y;
			mx[u]=max(mx[u],mp[u][x]);
		}
		dp[u]+=dp[v];
		son++;
	}
	dp[u]+=son-mx[u];
	if(mx[u]>1){
		vector<int> g,h;
		for(auto [x,y]:mp[u]){
			if(y==mx[u]){
				g.eb(x);
			}
		}
		mp[u].clear();
		for(int i:g){
			mp[u][i]=1;
		}
		mx[u]=1;
	}
}
void Yorushika(){
	read(n);
	rep(i,1,n){
		read(c[i]);
	}
	rep(i,1,n-1){
		int u,v;read(u,v);
		add(u,v),add(v,u);
		deg[u]++,deg[v]++;
	}
	dfs(1,0);
	if(!mp[1].count(0)){
		dp[1]++;
	}
	printf("%d\n",dp[1]);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

