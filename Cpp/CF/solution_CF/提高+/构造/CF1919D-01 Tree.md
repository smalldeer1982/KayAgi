# 01 Tree

## 题目描述

There is an edge-weighted complete binary tree with $ n $ leaves. A complete binary tree is defined as a tree where every non-leaf vertex has exactly 2 children. For each non-leaf vertex, we label one of its children as the left child and the other as the right child.

The binary tree has a very strange property. For every non-leaf vertex, one of the edges to its children has weight $ 0 $ while the other edge has weight $ 1 $ . Note that the edge with weight $ 0 $ can be connected to either its left or right child.

You forgot what the tree looks like, but luckily, you still remember some information about the leaves in the form of an array $ a $ of size $ n $ . For each $ i $ from $ 1 $ to $ n $ , $ a_i $ represents the distance $ ^\dagger $ from the root to the $ i $ -th leaf in dfs order $ ^\ddagger $ . Determine whether there exists a complete binary tree which satisfies array $ a $ . Note that you do not need to reconstruct the tree.

 $ ^\dagger $ The distance from vertex $ u $ to vertex $ v $ is defined as the sum of weights of the edges on the path from vertex $ u $ to vertex $ v $ .

 $ ^\ddagger $ The dfs order of the leaves is found by calling the following $ \texttt{dfs} $ function on the root of the binary tree.

```
<pre class="verbatim"><br></br>dfs_order = []<br></br><br></br>function dfs(v):<br></br>    if v is leaf:<br></br>        append v to the back of dfs_order<br></br>    else:<br></br>        dfs(left child of v)<br></br>        dfs(right child of v)<br></br><br></br>dfs(root)<br></br>
```

## 说明/提示

In the first test case, the following tree satisfies the array.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1919D/2af3796cd4a2a9733f8a3c061e8120f70b3cbf6a.png)

In the second test case, it can be proven that there is no complete binary tree that satisfies the array.

## 样例 #1

### 输入

```
2
5
2 1 0 1 1
5
1 0 2 1 3```

### 输出

```
YES
NO```

# 题解

## 作者：MaxBlazeResFire (赞：11)

被一道简单题卡了 $2$ 个小时，导致场上没时间写 $\rm F1$ 了。

注意到我们可以将本题看作：给你一个序列 $[0]$，每次可以任选数列中的一个数 $x$，然后将 $x+1$ 插入 $x$ 的左侧或右侧，问最终的序列能否得到。具体来说，就是相当于拆分一个当前的叶子并生成两个新的叶子的操作。

对于样例，可以进行操作 $[0]\rightarrow[0,1]\rightarrow[1,0,1]\rightarrow[1,0,1,1]\rightarrow[2,1,0,1,1]$。

观察规律，可得有解的判据为：

$1.$ $0$ 有且仅有一个。

$2.$ 对于所有非 $0$ 数 $a_i$，记左侧第一个小于它的数 $a_{L_i}$（需存在），右侧第一个小于它的数 $a_{R_i}$（需存在），需要满足 $a_{L_i}$ 与 $a_{R_i}$ 中至少有一个为 $a_i-1$。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

int n,a[MAXN],L[MAXN],R[MAXN],st[MAXN],top = 0;

inline void solve(){
	scanf("%lld",&n); int cnt0 = 0;
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]),cnt0 += !a[i];
	if( cnt0 != 1 ){ puts("NO"); return; }
	for( int i = 1 ; i <= n ; i ++ ){
		while( top && a[i] < a[st[top]] ) R[st[top]] = i,top --;
		st[++top] = i;
	} while( top ) R[st[top]] = n + 1,top --;
	for( int i = n ; i >= 1 ; i -- ){
		while( top && a[i] < a[st[top]] ) L[st[top]] = i,top --;
		st[++top] = i;
	} while( top ) L[st[top]] = 0,top --;
	for( int i = 1 ; i <= n ; i ++ ){
		if( !a[i] ) continue;
		if( !( L[i] > 0 && a[L[i]] == a[i] - 1 ) && !( R[i] < n + 1 && a[R[i]] == a[i] - 1 ) ){ puts("NO"); return; }
	}
	puts("YES");
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：FFTotoro (赞：8)

赛时做掉一个 \*2100 却没有上紫名。怎么回事呢。

考虑如何快速减少树上的结点以简化问题。记 $w_i$ 为结点 $i$ 的权值；对于一个结点 $x$，如果它有儿子 $x_1,x_2$，那么两个儿子的权值必然一个是 $w_x$，一个是 $w_x+1$。这启发我们把两个儿子结点合并成一个父结点；这个操作等价于删除权值为 $w_x+1$ 的结点。

但是我们不知道哪些节点是同父亲的两个叶子之一。于是从具有最大的权值的结点开始枚举（可以证明它一定是同父亲的两个叶子之一），如果在序列中相邻位置有权值比它小 $1$ 的那么把它本身**删掉**，继续进行以上的过程；否则无解。

但是有可能有权值相同的结点，此时我们只需对于每种权值用一个 `std::vector` 把结点存下来。因为我们不知道它们的删除顺序，所有有一种暴力做法：每次从序列中找到可以删的删掉，然后再扫一遍序列继续删……这种做法是 $O(n^2)$ 的，有两种优化方式可以供参考：

- 使用 BFS 优化：显然一个结点被删了只会影响到左右两边离它最近（这里的距离定义为数组间的下标之差）的权值相同的结点，于是每次如果将可以删的数入队，向两边拓展即可，本人考场上写的是该做法；

- 正反扫两遍：注意到每次不需要把整个序列都遍历一遍，因为每次可能影响它的只有它左边或右边最近的权值相等的结点，该做法更容易实现。

最后注意特判数列中必须有且仅有 $1$ 个 $0$。

删数的实现可以借助链表。总时间复杂度 $O(n)$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n; bool f=true; cin>>n;
    vector<int> a(n),l(n),p(n);
    for(int i=0;i<n;i++)l[i]=i-1,p[i]=i+1; // 链表初始化
    vector<vector<int> > v(n);
    for(auto &i:a)cin>>i;
    auto pd=[&](int x){
      return l[x]>=0&&a[l[x]]==a[x]-1||p[x]<n&&a[p[x]]==a[x]-1;
    }; // 判断是否可以删
    auto del=[&](int c){
      if(l[c]>=0)p[l[c]]=p[c];
      if(p[c]<n)l[p[c]]=l[c];
    }; // 删数过程
    for(int i=0;i<n;i++)
      v[a[i]].emplace_back(i);
    for(int i=n-1;i&&f;i--){
      if(v[i].empty())continue;
      vector<bool> b(v[i].size());
      queue<int> q;
      for(int j=0;j<v[i].size();j++)
        if(pd(v[i][j]))b[j]=true,q.emplace(j);
      while(!q.empty()){
        int x=q.front(); q.pop(),del(v[i][x]);
        if(x&&!b[x-1]&&pd(v[i][x-1]))b[x-1]=true,q.emplace(x-1);
        if(x+1<v[i].size()&&!b[x+1]&&pd(v[i][x+1]))b[x+1]=true,q.emplace(x+1);
      } // 广搜过程
      if(!*min_element(b.begin(),b.end()))f=false; // 是否都搜到了
    }
    cout<<(f&&v[0].size()==1?"Yes\n":"No\n");
  }
  return 0;
}
```

---

## 作者：Sampson_YW (赞：5)

考察最特殊的叶子：权值为 $0$ 的叶子。

在这棵树上一定只有一个这样的叶子 $x$，根到 $x$ 的路径上的边权全都是 $0$。

并且这条路径上的非叶子节点的另一条边的权值为 $1$。也就是说将剩下的数减 $1$ 就递归到了一个类似的问题：序列被 $0$ 分割成了若干个区间，将每个区间中的数减 $1$ 并递归。如果找不到 $0$ 就无解。

注意一开始必须恰好有一个 $0$。递归之后可以有多个 $0$，因为根到 $x$ 的非叶子节点可以有很多个，将这些 $0$ 依次分给每个非叶子节点就行了。

可以用 ST 表找区间最小值。复杂度 $O(n\log n)$。

[submisson](https://codeforces.com/contest/1919/submission/240632278)

---

## 作者：Luzhuoyuan (赞：3)

闲话：赛时调不出来，死因是没打标记，赛后一发过。心态崩了。

![](https://cdn.luogu.com.cn/upload/image_hosting/pstne4ls.png)

### 题目链接

[[to Luogu]](https://www.luogu.com.cn/problem/CF1919D) [[to Codeforces]](https://codeforces.com/contest/1919/problem/D)

### 题意简述

有一棵特殊的二叉树，满足它除了叶子节点的每个节点都有两个儿子，且连向儿子的边中有一条边权为 $0$，另一条边权为 $1$，注意边权为 $0$ 的边可能连向左儿子和右儿子中的任意一个。现在你忘记树长什么样了，你只记得一个长为 $n$ 的序列 $a$，其中 $a_i$ 表示 DFS 序为 $i$ 的叶子节点与根节点的距离。求对于给定的 $a$ 是否存在一棵合法的树。每个测试点 $t$ 组测试用例。

$$t\le 10^4,2\le n\le 2\cdot 10^5,\sum n\le 2\cdot 10^5$$

### 做法

首先如果两个叶子节点是兄弟，那么显然它们与根的距离差为 $1$，且它们的父节点的距离等于它们距离的较小值。因此我们考虑把两个 DFS 序相邻的差为 $1$ 的点合起来，将它们的父节点再扔回去，并且可以证明父节点的 DFS 序还是在它们原来的位置，那么就能等价于把较大的那个点删掉，就转化为一个子问题。

由于我们每次要删掉较大的点，如果先从值较小的组开始删，有可能后面会接不上。所以我们考虑从最大的组开始删，也就是找数列中最大值，如果它旁边有比它小 $1$ 的数就把它删掉继续考虑。有一个结论：如果序列合法，那么满足其中恰好有一个 $0$，且必然存在一个数列中的最大值与最大值减一相邻。前半个证明很简单，因为恰好存在一个叶节点满足从根到它的每条边都为 $0$。后半个假设数列中最大值没有与任何一个最大值减一相邻，首先连向最大值点的边边权一定是 $1$，否则它兄弟的距离就比它大了。那么如果最大点的兄弟也是叶节点，它的距离恰好是最大值减一。所以最大点的兄弟一定有儿子，但是这样最大点兄弟较大的儿子的距离值与最大值相等了，这又会进入新一轮的讨论，如果一直讨论下去就会有无穷多个节点了。所以原命题得证。

既然只是删点，不改变相对顺序，那么有多个最大值时先删哪个也无所谓。可以先把能删的点插入一个队列，然后一个个处理，每次删之前判断一下删掉这个点会不会产生新的能删的最大点，如果能就也加入队列。数列中删点可以用双向链表简单维护。注意：**一定要在插入队列前判断这个点是否已经进过队**，因为有些点可以被它两边的点都更新，~~不要问我怎么知道的~~。时间复杂度 $O(n)$。具体细节见代码。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=2e5+5;
int T,n,a[N],nx[N],la[N],fl[N];
vector<int> ve[N];
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
queue<int> q;
signed main(){
	T=read();
	while(T--){
		n=read();a[0]=-1;
		for(int i=0;i<n;i++)ve[i].clear();
		for(int i=1;i<=n;i++)a[i]=read(),ve[a[i]].pb(i),nx[i-1]=i,la[i]=i-1,fl[i]=false;
        //构建链表，把每个值对应的位置塞进 vector
		nx[n]=0;
		if(ve[0].size()!=1){puts("NO");continue;}
		bool c=true;
		for(int i=n-1;i;i--){
			for(int v:ve[i])if(a[nx[v]]==i-1||a[la[v]]==i-1)q.push(v),fl[v]=true;
            //把能删的加入队列，fl 是入队标记
			int num=0;
			while(!q.empty()){
				int x=q.front();q.pop();num++;
				if(a[la[x]]==i&&a[nx[x]]==i-1&&!fl[la[x]])q.push(la[x]),fl[la[x]]=true;
				if(a[la[x]]==i-1&&a[nx[x]]==i&&!fl[nx[x]])q.push(nx[x]),fl[nx[x]]=true;
				la[nx[x]]=la[x],nx[la[x]]=nx[x];
			}//删点
			if(num<(int)ve[i].size()){c=false;break;}
            //没删光不合法
		}
		puts(c?"YES":"NO");
	}
	return 0;
}
```

（逃

---

## 作者：Y_ATM_K (赞：2)

[传送门](https://codeforces.com/problemset/problem/1919/D)

这题似乎有很多做法。

### 思路

观察一个性质：对于任意一棵子树，到根节点路径长为 0 的点恰好有一个。

先把有多个 0 的情况判掉。

再把整个树的 0 点找到，此时树分成了两部分：dfs 序小于它的点和大于它的点。

这两部分显然互不干扰，分治地求其中一部分。

我们把 0 点到根地路径删掉，会剩下很多子树，因为删掉的路径权值为 0，而这些子树的根与路径的边边权是 1，那么剩下的点到它子树根的距离就是它的权值减 1。

把所有点权减 1，若此时分治的区间没有 0。由性质可知一定无解。

判掉没有 0 的情况后，我们继续把 0 点到根的路径删掉，递归下去做。如果有多个 0，按照上面的判断，区间越大被判无解的机会越小，所以把 0 之间的点全部分配到其中一个 0 的子树中，也就是把 0 之间的区间整个递归下去。

每个点只会被删一次，时间复杂度 $O(n)$。

[通过记录](https://codeforces.com/contest/1919/submission/240785754)

---

## 作者：Petit_Souris (赞：1)

睡前来点近期 CF 小清新思维题。这种题做了快半小时，还因为愚蠢错误罚了两发罚时，感觉将近一年不打 CF 严重退化了，我们文化课是这样的。

首先，完全二叉树是一个关键条件，这意味着对于两个相邻的叶子节点 $u,v$，他们共用父亲节点 $f$。

这是一个判断可行性的问题，一种可能的思路是尝试把问题规模不断缩小直到一个边界情况可以确定答案。假设我们知道了删除叶子 $u,v$ 之后的树是可行的，那么加上 $u,v$ 也一定是可行的；而如果删除叶子 $u,v$ 不可行，说明当 $u,v$ 被 $f$ 替换的时候不合法，那么再加回 $u,v$ 显然也不合法。

我们可以用这样的方式缩减序列长度：对于 $u,v$ 两个点，他们的路径长度差必定为 $1$。删除 $u,v$，加入新的叶子节点 $f$，$f$ 的距离为 $u,v$ 距离中的较小者。

因此问题就变成：每次选择序列中相邻两项差为 $1$ 的元素，替换为两者中较小值，问最终是否可以只留下一个 $0$。

这个问题容易解决：从大到小枚举值域，对于当前值 $v$ 的所有位置，拆分出若干个极长连续段。对于每个连续段，只要左侧或右侧有一个 $v-1$，这段就可以全部消去了。用链表维护这个过程，时间复杂度 $\mathcal O(n)$。

```cpp
const ll N=1e6+9;
ll T,n,a[N],pre[N],nxt[N];
vector<ll>vec[N];
void Del(ll u){
	pre[nxt[u]]=pre[u],nxt[pre[u]]=nxt[u];
	pre[u]=nxt[u]=0;
}
void solve(){
	n=read();
	rep(i,1,n)a[i]=read();
	rep(i,0,n)vec[i].clear();
	ll c=0;
	rep(i,1,n)c+=(a[i]==0);
	if(c!=1)return puts("NO"),void();
	ll mx=*max_element(a+1,a+n+1);
	rep(i,1,n)vec[a[i]].push_back(i);
	pre[0]=0;
	rep(i,1,n+1)pre[i]=i-1;
	rep(i,0,n)nxt[i]=i+1;
	nxt[n+1]=n+1;
	per(i,mx,1){
		ll sz=vec[i].size();
		if(!sz)continue;
		rep(j,0,sz-1){
			ll k=j;
			while(k<sz-1&&vec[i][k+1]==nxt[vec[i][k]])k++;
			ll fl=0;
			if(pre[vec[i][j]]&&a[pre[vec[i][j]]]==i-1)fl=1;
			if(nxt[vec[i][k]]<=n&&a[nxt[vec[i][k]]]==i-1)fl=1;
			if(!fl){
				puts("NO");
				return ;
			}
			rep(o,j,k)Del(vec[i][o]);
			j=k;
		}
	}
	puts("YES");
}
```

---

## 作者：Cynops (赞：1)

考虑将题目转化为：

> $D'$：对于一对相邻的差值为一的数，可以只留下较小的那个，问是否能使得只剩一个 $0$

为什么可以这么转化？

![](https://cdn.luogu.com.cn/upload/image_hosting/e0skozxb.png)

考虑删去 $1,2$ 两点，他们的权值上浮为 $b$ 号店，容易发现不影响这颗二叉树的构成。

![](https://cdn.luogu.com.cn/upload/image_hosting/tr9d2b14.png)


接下来考虑如何解决 $D'$。

考虑到序列最大值只能被其他值删去，而且对于一个最大值极长连续段，只要端点可以被删，那么一定可以删去这个连续段。

我们用一个 `vector v[x]` 存储值为 $x$ 的所有点在链表中的迭代器位置。

我们考虑删除 `v[x]` 中的所有元素：

如果某点可以被删除，那么删掉，继续检查后面的点，如果有没被删掉的节点，那么说明不合法，输出 `no`。

最后检查链表中是否只有一个 $0$，若是，那么合法，否则不合法。

每个点只会被删除一次，时间复杂度 $\mathcal{O}(n)$，[代码](https://codeforces.com/problemset/submission/1919/240928753)

---

## 作者：robinyqc (赞：1)

昨天切掉了，但是因为 4 发罚时和巨久的调试，没能拿到满意的名次呜呜呜。

### 题意简述

给你一颗完全二叉树（每个非叶子结点都有两个儿子），与儿子相连的两条边权恰好一个是 $0$ 一个是 $1$，但是不知道是哪个。你也不知道树的形态。但是你记忆中，按照 dfs 序（先左儿子再右儿子），叶子结点的深度是长度为 $n$ 的序列 $a$。

你需要判断你有没有记错：是否确实存在一颗满足要求的二叉树，按照 dfs 序，叶子结点的深度是序列 $a$。

### 解题思路

转化题意！树真的比较抽象。发现，你可以按照这样的方法来尝试解构一颗完全二叉树：找到两个兄弟叶子节点，删掉它们。此时它们的父亲变为叶子结点。由于是一颗完全二叉树，每次一定能找到两个叶子兄弟节点，知道只剩一个点。

题目中的树还有一个特点，就是兄弟节点的深度差为 $1$。结合两个特点，反映到序列上就是：每次选择 $i$，满足 $|a_i - a_{i + 1}| = 1$，删掉 $a_i$ 和 $a_{i + 1}$（兄弟叶子结点），然后在这个位置加入 $\min(a_i, a_{i + 1})$（父亲节点）。

再简化一下，问题就转化为：每次选择一个位置，满足存在相邻的位置权值比它小 $1$，然后删掉它，最终能否得到 $a = [0]$。

可以发现，序列的最大值，不管有没有多个，都不能删掉别的元素，只能被其它元素删掉。这意味着我们可以贪心地删除所有序列最大值。如果有元素不能被删掉，那么一定不合法。

删除的一个比较简单的写法是，注意到一个最大值连续段，只要某个端点能被删除，就可以全被删除；否则，删不掉。

如果我们删完了序列最大值，问题就变成了子问题，同样地解决就好了。至于删点，可以用链表。

最后判断 $a$ 是否等于 $[0]$ 就好了。

### 代码实现

```cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;

vector<list<int>::iterator> v[200005];

bool solve()
{
    int n;
    list<int> a;
    cin >> n;
    for (int i = 0; i < n; i++) v[i].clear();
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        a.push_back(x);
        v[x].push_back(--a.end());
    }
    for (int i = n - 1; i >= 1; i--) {
        for (auto &it: v[i]) {
            if ((it != a.begin() && *prev(it) == i - 1) 
            || (it != --a.end() && *next(it) == i - 1)) {
                a.erase(it);
                it = a.end();
            }
            else if (it == --a.end() || *next(it) != i) return false;
        }
        for (auto &it: v[i]) {
            if (it != a.end()) {
                a.erase(it);
            }
        }
    }
    return a.size() == 1 && a.back() == 0;
}

signed main()
{
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) cout << (solve()? "Yes\n": "No\n");
    return 0;
}
```

---

## 作者：解方橙 (赞：1)

[link](https://codeforces.com/contest/1919/problem/D)

题意简述：给定一棵完全二叉树（注意，这里的完全二叉树的定义为每个节点都有 0 或 2 个儿子），每个非叶子节点到儿子的两条边一条权值为 0，一条权值为 1，给出从左到右每个叶子到根路径上的权值，求是否有可能复原这棵二叉树。 $n\leq 2\times 10^5$ 。

官方题解给出了 $\mathcal{O}(n\log)$ 的做法！于是我们就用个 $\mathcal{O}(n)$ 的把它碾了吧。

首先是题意的转化：每次相当于可以把共用父亲的两个叶子节点删除，这要求这两个叶子节点的值分别为 $x$ 和 $x+1$ （因为这样的话它们的父亲一样，两条连向它们的边差 $1$ ，所以最后的值要差 $1$ ），删除两个节点后，注意到它们的父亲节点的值可被表示为 $x$ 。

所以我们要做的其实就是这样一个事情：不停把 $a$ 数组里的相邻的，值相差为 $1$ 的两项合并，合并后的值为两项的较小值，问是否存在一个方法使得最后 $a$ 数组只剩下一个 $0$ 。（为什么是 $0$ 呢？因为最后合并完会剩下根节点；根节点的权值当然就是 $0$ 了。）

我们记一次合并两个节点的操作为一次**消除**。

首先容易发现，如果 $a$ 数组里没有 $0$ ，那最后一定不会到 $0$ （显然）。如果 $a$ 数组里有多个 $0$ ，那最后一定会剩一堆 $0$ 打架。（这也是显然的，因为 $0$ 与任何其它数合并都会得到 $0$ ，因此 $0$ 的数目始终不会减少）。

把 $0$ 判掉后，就可以开始我们伟大的贪心了。

维护一个栈，满足栈里的元素**单调不减**（为什么可以保证单调不减？之后会说到），从左到右依次遍历 $a$ 数组。设当前元素为 $u$ ，栈顶元素为 $v$ ，栈顶的下面的元素为 $w$ 。（即如果执行一次 $\operatorname{pop}$ 操作，栈顶会变成 $w$ ）。

一个重要的基本的思想是，由于我们是从左到右遍历的，所以能对接下来的答案产生影响的只有栈顶元素，**因此我们在保证栈顶元素不改变的情况下随便消除栈里的节点**。

为方便起见，我们先把 $u$ 也推进栈里，然后不断判定消除（现在，栈里的元素是 ``...-...-...-w-v-u``，右侧为顶）。

然后，我们进行大力分讨：
- 如果 $u=v-1$ 会怎样？那么如果对 $u$ 和 $v$ 执行消除操作后栈顶元素还为 $u$ ，对接下来的答案不会产生影响，因此消就完了。
- 如果 $u<v-1$ 会怎样？这个时候我们发现可以把栈里所有 $>u$ 的元素都弹掉（因为栈顶已经是 $u$ 了），于是不断尝试消除 $v$ 和 $w$ 。注意这时候可能会出现无解的情况（比如，$u=1,v=3,w=1$），如果这时候无解了，因为我们的贪心绝对保证正确性，所以最终的答案就是无解。另外，注意到如果成功进行完了本操作，把 $>u$ 的都消掉了，这个栈的单调不减性质是保持了的。
- 有了上面两个操作，我们就成功维护了栈的单调不减性质。
- 如果 $u>v$ 会怎样？啥也不用管即可。如果把 $u$ 消了那么就会对后续的答案产生影响。

总结我们的思路：我们发现当栈单调不减的条件可能将要不能满足的时候，必然有可以执行的不会劣化答案的消除操作。维护这样的一个单调不减栈，就可以在保证不会失误的情况下维护最佳的消除操作。

最后栈里会剩一堆东西。判一下相邻两项的差是否都 $<2$ 即可。

时间复杂度 $\mathcal{O}(n)$ 。代码（注：赛时代码，可能含有一些冗余的判定）：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
int T,n,a[N];
int st[N],top;
bool solve(){
    int cntzero=0;
    for(int i=1;i<=n;i++) cntzero+=(a[i]==0);
    if(cntzero!=1) return false;
    top=0;
    for(int i=1;i<=n;i++){
        st[++top]=a[i];
        while(top){
            int u=st[top],v=st[top-1];
            if(top==1) break;
            if(u>v) break;
            if(u==v-1){st[--top]=u;continue;}
            if(top==2){
                if(u<v) return false;
                break;
            }
            int w=st[top-2];
            bool flag=(w==v-1);
            if(u==v){
                if(flag){st[--top]=u;continue;}
                else break;
            }
            if(u<v-1){
                if(!flag) return false;
                st[--top]=u;continue;
            }
            assert(0);
        }
    }
    for(int i=1;i<top;i++) if(st[i]<st[i+1]-1) return false;
    return true;
}
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        printf("%s\n",solve()?"YES":"NO");
    }
}

```

---

## 作者：User_Unauthorized (赞：1)

考虑深度最大的叶子节点，不难发现其兄弟节点一定是一个深度比其小 $1$ 的叶子节点，这就意味着他们的 dfs 序是相邻的。

因此我们可以每次选取深度最大的叶子节点，检查其 dfs 序两侧是否存在深度比其小 $1$ 的叶子节点，若存在则将这两个叶子节点删去，会产生一个新的深度比最大深度小 $1$ 的叶子节点即其原来的父亲节点，将其插入到 dfs 序列中继续执行删除操作即可。若其 dfs 序两侧不存在深度比其小 $1$ 的叶子节点，那么我们可以将其删去，那么不存在合法的方案。

具体实现时，可以使用一个堆来维护当前深度最大的叶子节点，使用链表来维护 dfs 序列。


---

## 作者：Priestess_SLG (赞：0)

一个神经的单 $\log$ 做法。直接做十分神秘，考虑先转化问题：考虑到对于两个有共同父亲结点的叶子结点，她们到根节点的距离的差的绝对值必然为 $1$。因此问题转化为：

> 给定一个长度为 $n$ 的序列 $a$，现每一次可以选择相邻的两个位置，满足她们的差的绝对值为 $1$，删去她们中值较大的那个。问是否存在一组合法的删除方案，使得最终序列中恰好存在 $1$ 个数，且这个数的值为 $0$。

现在这个问题就简单多了：考虑套路贪心，维护一个双向链表，链表中按下标顺序存储所有当前未被删除的序列元素，再维护一个 `set` 表示当前所有可以删除其和其后继元素的位置。每一次贪心的从 `set` 中取出当前值最大的位置，并将其删除。重复上述操作，若最终可以使得序列满足条件，则可以构造出合法解，否则不可以构造出合法解。

于是该题做完了，时间复杂度为 $O(n\log n)$ 可以通过。

```cpp
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500010;
int a[N],pre[N],nxt[N];
signed main(){
    cin.tie(0)->sync_with_stdio(false);
    int T,ca=1;
    cin>>T;
    int tc=T;
    while(T--){
        int n;cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)pre[i]=i-1,nxt[i]=i+1;
        nxt[0]=1,pre[n+1]=n;
        int cnt=n,idx=n+1;
        set<pair<int,int>>pos;
        //pos 存储当前所有可以删除的左侧位置
        for(int i=1;i<n;++i)
            if(abs(a[i]-a[i+1])==1)pos.emplace(a[i]+a[i+1],i);
        while(cnt>1){
            if(pos.empty())break;
            --cnt;
            int id=pos.rbegin()->second;pos.erase(--pos.end());
            int id2=nxt[id];
            a[++idx]=min(a[id],a[id2]);
            pre[idx]=id,nxt[idx]=id2;
            nxt[id]=idx,pre[id2]=idx;
            pre[nxt[id]]=pre[id];
            nxt[pre[id]]=nxt[id];
            pre[nxt[id2]]=pre[id2];
            nxt[pre[id2]]=nxt[id2];
            if(pos.count({a[id2]+a[nxt[id2]],id2}))pos.erase(pos.find({a[id2]+a[nxt[id2]],id2}));
            if(pos.count({a[pre[id]]+a[id],pre[id]}))pos.erase(pos.find({a[pre[id]]+a[id],pre[id]}));
            if(pre[idx]&&abs(a[idx]-a[pre[idx]])==1)pos.emplace(a[pre[idx]]+a[idx],pre[idx]);
            if(nxt[idx]!=n+1&&abs(a[idx]-a[nxt[idx]])==1)pos.emplace(a[idx]+a[nxt[idx]],idx);
        }
    }
    return 0;
}
```

---

## 作者：Chillturtle (赞：0)

# 题意

给你一个长度为 $n$ 的数组 $a$。同时以如下方式遍历一棵二叉树：

```
dfs_order = []

function dfs(v):
    if v is leaf:
        append v to the back of dfs_order
    else:
        dfs(left child of v)
        dfs(right child of v)

dfs(root)
```

对于一个节点连向其左右儿子的路径必有一条为 $1$，另一条为 $0$。令一个叶子结点的点权为其到根节点的简单路径上所有边的边权和。对这颗二叉树进行遍历，第 $i$ 个访问到的叶子结点点权为 $a_i$。求：能否构造出这棵树。

# 思路

我们首先可以得到这个结论：对于一个能构造成功的树有且只有一个 $0$。这个很显然：对于一棵满足每个节点连向其左右儿子的路径必有一条为 $1$，另一条为 $0$ 的二叉树。其有且仅有一条到根节点的路径，且路径上所有边的边权全为 $0$。所以对于 $a$ 中含有多个 $0$ 或者说根本没有 $0$ 的，我们可以直接 ban 掉。

其次尝试转化题意：

其实就是给你一个初始序列：$[0]$。然后每次对于一个 $x$ 每次在这个数的左边或者右边插入 $x+1$。

为什么可以这么做？因为对于一个叶子节点，假设往左儿子连的路径的边权为 $0$ 则往右儿子连的路径的边权为 $1$。那么相当于左儿子的点权就是当前节点的点权（因为加 $0$ 不影响点权），而右儿子的点权就是当前节点的点权加 $1$。

这个结论有什么用？考虑一下，这个结论就相当于说，对于一个合法的数组 $a$，我们要求：每一个 $a_i$ 左边第一个小于 $a_i$ 的数 $L_i$ 等于 $a_i-1$，或者右边第一个小于 $a_i$ 的数 $R_i$ 等于 $a_i-1$（两者必须满足其一）。

怎么维护？考虑使用栈直接维护。复杂度 $O(n)$。

# AC code

[Code](https://www.luogu.com.cn/paste/zba2l2nt)

# 写在后面的话

现在是 2024 年 12 月 31 日。🎇 Happy New Year!

---

## 作者：kczw (赞：0)

# 题意
给定一个有 $n$ 个叶节点的带权二叉树，树上除叶节点外的节点有两个子节点，且到子节点边的边权其一为零，其二为一。叶子节点的权值为到根节点路径上边权和。

共 $t$ 组数据，每组数据给定 $n$ 个叶节点的权值，问是否可以构造出类上文所言的二叉树。
# 思路
这棵树有两个特性：
- 有子节点的节点有两个子节点。
- 连接字节点边的边权一个是零，一个是一。

由此特性一可以知道肯定存在兄弟节点。而由特性二兄弟节点的权值肯定是相差一的。

于是可从叶节点往上推导，若有相邻两个节点权值为 $a$ 和 $a+1$，意味着它们可由同一个父节点延申得到，那么可删除这两个子节点，留下它们的父节点 $a$ 当作叶节点继续推导。

不难明白若经推导最后可只剩一个节点，即可以构造出类上述说明的树。

推导过程因为是从叶到根，自然是从权值大的叶节点开始推导到权值小的叶节点结束。同时由上文的推导过程不难发现，删子留父的操作可看作删除较大数。

所以，推导过程就成了从大权值叶节点到小权值的叶节点的遍历，每次检查与被遍历叶节点 $i$ 相邻的叶节点 $i-1,i+1$ 的权值 $a_{i-1}$ 和 $a_{i+1}$ 能否等于 $a_i-1$，如果可以，就将被遍历的叶节点删去（删去操作用链表维护）。

最后有一个代码上的重点，类以下的样例。
```
5
3 3 2 1 0
```
对于这个样例的答案肯定是肯定的，可按上述思路还过不去。原因是第一个 $3$ 的左无叶节点但右叶节点权值为 $3$ 又不满足删去的条件，所以不会被删去。

但逻辑上，按上述思路删点过程中，当有一区间的叶节点都为一个数时，它们可以被看作一个点，因为若区间边缘的点可删，说明区间内每一个都可以删，否则，即使合并成一个点。

所以为可删点的条件应多一个，若相邻节点的权值相同，那么此点可删去。
# 实现
```cpp
#include<iostream>
#include<vector>
#define N 200005
using namespace std;
vector<int> id[N];
int t,n,num,a[N],l[N],r[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		num=n;
		int k=1,mx=0;
		for(int i=1;i<=n;i++)
			id[i].clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			mx=max(mx,a[i]);
			if(!a[i])
				k=0;
			else 
				id[a[i]].push_back(i);
			l[i]=i-1;
			r[i]=i+1;
		}
		a[0]=a[n+1]=N; 
		if(k){
			printf("NO\n");
			continue;
		}
		for(int i=mx;i>=1;i--){
			if(id[i].size()){
				for(int I:id[i]){
					if(a[l[I]]==a[I]-1||a[r[I]]==a[I]-1||a[l[I]]==a[I]||a[r[I]]==a[I]){
						r[l[I]]=r[I];
						l[r[I]]=l[I];
						l[I]=r[I]=0;
						num--;
					}
				}
			}
			else{
				num=2;
				break;
			}
		}
		if(num>1)
			printf("NO\n");
		else 
			printf("YES\n");
	}
	return 0;
}
```

---

## 作者：henrytb (赞：0)

容易发现，一定至少存在一组相邻的两个叶子互为兄弟。这样的两个叶子到根的距离一定相差 $1$。

这启发我们将这两个叶子缩成一个到根距离为这两个叶子中到根的距离的 $\min$ 的叶子。

那么按 $a$ 数组的大小从大到小检查，对于一个同深度的连续段，它左右两边应当至少有一个值的深度为当前检查的深度 $-1$，这样才可以将这个连续段缩起来。使用链表实现即可。

特判 $0$ 的个数 $> 1$ 的情况。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 2e5 + 5;
int _, n, a[N];
int nxt[N], lst[N];
vector<int> pos[N];
int main() {
    for (scanf("%d", &_); _; --_) {
        scanf("%d", &n);
        rep(i, 0, n - 1) pos[i].clear();
        rep(i, 1, n) {
            scanf("%d", &a[i]);
            lst[i] = i - 1; nxt[i] = i + 1;
            pos[a[i]].emplace_back(i);
        }
        if (pos[0].size() > 1) { puts("NO"); continue; }
        lst[n + 1] = n; nxt[0] = 1;
        per(i, n - 1, 1) {
            int llst = -1;
            bool flg = 0;
            for (auto &x: pos[i]) {
                if (llst != lst[x]) {
                    if (~llst) {
                        if (!flg) {
                            int tmp = nxt[llst];
                            if (tmp <= n && a[tmp] == i - 1) flg = 1;
                        }
                        if (!flg) { puts("NO"); goto fail; }
                    }
                    llst = x;
                    if (lst[llst] && a[lst[llst]] == i - 1) flg = 1;
                    else flg = 0;
                } else llst = x;
            }
            if (~llst) {
                if (!flg) {
                    int tmp = nxt[llst];
                    if (tmp <= n && a[tmp] == i - 1) flg = 1;
                }
                if (!flg) { puts("NO"); goto fail; }
            }
            for (auto &x: pos[i]) {
                int l = lst[x], r = nxt[x];
                nxt[l] = r; lst[r] = l;
            }
        }
        puts("YES");
        fail: ;
    }
    return 0;
}
```

---

