# Xor-tree

## 题目描述

Iahub is very proud of his recent discovery, propagating trees. Right now, he invented a new tree, called xor-tree. After this new revolutionary discovery, he invented a game for kids which uses xor-trees.

The game is played on a tree having $ n $ nodes, numbered from $ 1 $ to $ n $ . Each node $ i $ has an initial value $ init_{i} $ , which is either 0 or 1. The root of the tree is node 1.

One can perform several (possibly, zero) operations on the tree during the game. The only available type of operation is to pick a node $ x $ . Right after someone has picked node $ x $ , the value of node $ x $ flips, the values of sons of $ x $ remain the same, the values of sons of sons of $ x $ flips, the values of sons of sons of sons of $ x $ remain the same and so on.

The goal of the game is to get each node $ i $ to have value $ goal_{i} $ , which can also be only 0 or 1. You need to reach the goal of the game by using minimum number of operations.

## 样例 #1

### 输入

```
10
2 1
3 1
4 2
5 1
6 2
7 5
8 6
9 8
10 5
1 0 1 1 0 1 0 1 0 1
1 0 1 0 0 1 1 1 0 1
```

### 输出

```
2
4
7
```

# 题解

## 作者：泥土笨笨 (赞：5)

# 解题思路

树上 DFS。

首先，我们发现，选择一个点进行操作的时候，一个点最多只能被选一次。因为如果我们把一个点操作两次，它们会相互抵消。所以其实这个问题就变成，我们只需要考虑每个点是否要选就行了。

接下来，我们发现，这棵树的树根选或者不选，是确定的。如果树根上的目标数字，和目前实际的数字相同，那么树根就不用操作。否则树根就必须要操作，因为下面的孩子们操作不会影响树根，只能在树根上自己操作才会影响树根上的数字。

一旦树根决定了是否要操作，接下来对于树根的直接孩子们，我们发现它们是否要操作也是确定的了，原因是一样的。于是我们得到了一个暴力做法：首先确定根是否要操作，如果要，操作一下，并且修改整棵树上所有被影响的点。接下来看第二层的每个点，判断是否要操作，如果要，操作一下，然后也修改下面所有受到影响的点。这个做法的复杂度是 $O(n^2)$ 的。

如何优化一下呢？我们发现，每当对一个点进行操作的时候，它只会修改子树中，层数的奇偶性和它的层数相同的那些点。但是这些点有必要真正进行修改吗？举个例子，假设我们首先操作了深度为 $1$ 的点，子树中深度为奇数的点都需要翻转，也就是深度为 $3,5,7,9...$ 的点。但是一会儿，如果我们发现它的一个孩子，深度为 $3$ 的点，也需要操作。那么这个点子树中深度为 $5,7,9...$ 的这些点也要修改。而我们发现之前改过一次这些点，现在又改一次，就抵消了。所以其实不用真的修改子树当中的点，只需要记录一下，奇数层和偶数层是否要改就行了。

在树上从上往下递归，对于递归到的当前点 $u$，查看自己是否需要翻转，如果需要，先翻转一下。接下来看自己是否需要操作，如果是，记录一下它的编号。并且修改一下自己所在的奇偶性对应的层是否要修改的标记。这样从跟递归到叶子，每个点都计算是否要操作就行了，时间复杂度 $O(n)$。

# 代码示例

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;

int n, s[MAXN], t[MAXN], cnt;
vector<int> adj[MAXN];
vector<int> ans;

//u表示现在递归到哪个点，f0表示当前点是否需要翻转，f1表示孩子是否要翻转
void dfs(int u, int fa, int f0, int f1) {
    if ((s[u] ^ f0) != t[u]) {
        cnt++;
        f0 ^= 1;
        ans.push_back(u);
    }
    for (int v: adj[u]) {
        if (v != fa) {
            dfs(v, u, f1, f0);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> t[i];
    }
    dfs(1, 0, 0, 0);
    cout << cnt << endl;
    sort(ans.begin(), ans.end());
    for (int i: ans) {
        cout << i << endl;
    }
    return 0;
}
```


---

## 作者：VTloBong (赞：5)

[人性翻译传送门](https://www.luogu.com.cn/discuss/show/173769)  
第一眼看到题：树形dp?  
再一想：~~树形dp的题怎么能用树形dp做呢~~这是个A题  
下面提供一种非树形dp思路：
##  注释见代码：
``` 
#include<stdio.h>
const int maxn=100001;
struct edge {
	int to,next;
} e[maxn<<1];
int h[maxn],cnt,n,m;//链式前向星存图 
int gp[maxn],ans,book[maxn];//gp[i]记录i节点的(grangpa)爷爷节点，没有则为0 ;book[i]标记i节点是否该被修改 
char now[maxn],should[maxn];//now[i]记录i节点的初始值,gp[i]记录i节点的目标值
void add(int u,int v) {
	e[++cnt].next =h[u];
	e[cnt].to =v;
	h[u]=cnt;
}
int is(int x) {
	return should[x]!=now[x];//判断初始值与目标值是否不一致 
}
void dfs(int x,int fa) {
	for(int l=h[x]; l; l=e[l].next ) {
		int v=e[l].to;
		if(v==fa)continue;
		dfs(v,x);
		gp[v]=fa;//找到每个节点的爷爷 
	}
}
int main() {
	scanf("%d",&n);
	m=(n-1)<<1;
	while(cnt<m){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}for(int i=1; i<=n; i++)scanf("%d",now+i);
	for(int i=1; i<=n; i++){
		scanf("%d",should+i);
		if(is(i))ans++,book[i]++;
	}dfs(1,0);//找爷爷 
	for(int i=1;i<=n;i++){ 
		if(gp[i]&&is(i)&&is(gp[i]))ans--,book[i]=0;//若i与gp[i]都改修，只改爷爷 
		if(gp[i]&&!is(i)&&is(gp[i]))ans++,book[i]=1;//若i不该修而gp[i]改修，改完爷爷再把孙子改回来 
	}printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		if(book[i])printf("%d\n",i);
	return 0;
} 
```

---

## 作者：Maureen0124 (赞：2)

## 题意
给你一颗以1为根的数，每个点有初始值，要做若干次操作使得每个点变成目标值。初始值和目标值均为 0 或 1。

## 思路
1. 首先需要知道哪些点需要进行操作。因为操作不会影响祖先节点的值，所以应该按照深度从小到大的顺序遍历，如果当前节点的值不等于目标值，那么进行操作并将该节点加入答案。
2. 然后观察每次操作。假设选中的点是 $u$，发现一次操作会影响的点是深度的奇偶性和 $u$ 的深度的奇偶性相同的点。所以可以在 dfs 的时候记录当前点的深度的奇偶性 $dep$。
3. 那么在祖先节点可能进行过操作的情况下该如何得到当前节点的值呢？在每次节点进行操作时暴力更新显然不行。发现可以结合每个点的 $dep$，记录相同 $dep$ 的祖先更新的次数 $tag[dep][u]$，在 dfs 的时候从父节点更新过来。
```cpp
for(int v : G[u]) if(v != pre){
    tag[dep][v] = tag[dep][u];
    tag[(dep + 1) % 2][v] = tag[(dep + 1) % 2][u];
    dfs(v, u, (dep + 1) % 2);
}
```
当前节点的值就是 $(init[u] + tag[dep][u]) \bmod 2$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
// A[]是题目中的 init[], B[]是题目中的 goal[]
int n, m, A[N], B[N], tag[2][N], cnt;
vector<int> G[N], res;

void dfs(int u, int pre, int dep){
    if((A[u] + tag[dep][u]) % 2 != B[u])    // 不等于目标值需要进行操作
        cnt++, res.push_back(u), tag[dep][u]++; // 该深度的标记++
    for(int v : G[u]) if(v != pre){
        tag[dep][v] = tag[dep][u];  // tag 直接从父节点继承过来
        tag[(dep + 1) % 2][v] = tag[(dep + 1) % 2][u];
        dfs(v, u, (dep + 1) % 2);   // 更新深度
    }
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    for(int i = 1, a, b; i < n && cin >> a >> b; i++)
        G[a].push_back(b), G[b].push_back(a);
    for(int i = 1; i <= n; i++) cin >> A[i];    // 初始值
    for(int i = 1; i <= n; i++) cin >> B[i];    // 目标值
    dfs(1, 0, 1);   // 深度从 0 或 1 开始都可以
    printf("%d\n", cnt);    // 更新次数
    for(int x : res) printf("%d\n", x);
    return 0;
}
```

---

## 作者：xuchuhan (赞：2)

对于暴力做法，直接从上到下遍历整棵树，如果当前节点的数值不是目标数值，则从当前节点开始直接向下进行取反修改。

考虑如何优化。

可以使用一个类似标记的做法，每次 DFS 时记录对于整棵树的奇数或偶数层分别取反过多少次，那么对于当前节点，其实际数值就是其当前数值经过其所在层数总共进行的异或操作后所得的数值。

时间复杂度降到了 $\mathcal{O(n)}$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n;
int a[N],b[N];
vector<int>ans,v[N];//ans:记录哪些节点被操作,v:建树 
void DFS(int x,int fa,bool flg1,bool flg2,int dep){//flg1:奇数层,flg2:偶数层,dep:当前层数 
	bool nxt1=flg1,nxt2=flg2;
	if(dep%2){//当前奇数层 
		if((nxt1^a[x])!=b[x]){//不符 
			nxt1^=1;
			ans.push_back(x);
		}
	}
	else{//当前偶数层 
		if((nxt2^a[x])!=b[x]){//不符 
			nxt2^=1;
			ans.push_back(x);
		}
	}
	for(int i=0;i<v[x].size();i++)//向下遍历 
		if(v[x][i]!=fa)
			DFS(v[x][i],x,nxt1,nxt2,dep+1);
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	DFS(1,0,0,0,1);
	cout<<ans.size()<<"\n";//输出 
	for(int i=0;i<ans.size();i++)
		cout<<ans[i]<<"\n";
	return 0;
} 
```

---

## 作者：XXh0919 (赞：2)

这一题就是树上进行 dfs。我们可以在输入最后一行时判断当前位置 $i$ 的值（$i$ 表示是第 $i$ 个孙子）是否要变，即判断与上一行是否一样，若不一样就是要变，一样就可以不管它，若要变那么 $ans$ 就加一，表示初始我们认为要进行一次操作，并将该位置打上一个标记，然后就是简单的 dfs 找爷爷。

dfs 完了之后，我们就进行第二次判断。注意，这个跟读入时的判断有点不一样，不过大差不差：若当前位置（孙子）的值要变，且我们 dfs 所找到的爷爷的位置的值也要变，那我们只变爷爷即可，即我们初始的那一次计数是不需要的，$ans$ 减一，标记清除；若孙子位置的值是不用变的，但爷爷的位置的值需要改变，那我们改完爷爷再把孙子改回来即可，即我们初始的计数是不够的，我们还要把刚刚的那一次操作加上，并在孙子位置打上标记（因为爷爷改完了孙子也改了），最后输出操作次数 $ans$ 和有标记的位置 $i$ 就行了。

### AC Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+15;

int n,ans;
int head[N],nxt[N<<1],to[N<<1],idx;
int fath[N],cnt[N];
int sta[N],en[N];

void add(int u,int v){
	to[idx]=v;
	nxt[idx]=head[u];
	head[u]=idx++;
}

void dfs(int u,int fa){
	for(int i=head[u];i!=-1;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs(v,u);
		fath[v]=fa;
	}
}

signed main(){
	memset(head,-1,sizeof head);
	scanf("%lld",&n);
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%lld%lld",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;++i)scanf("%lld",&sta[i]);
	for(int i=1;i<=n;++i){
		scanf("%lld",&en[i]);
		if(en[i]!=sta[i]){
			++ans;
			cnt[i]=1;
		}
	}
	dfs(1,0);
	for(int i=1;i<=n;++i){
		int x=fath[i];
		if(x&&(en[i]!=sta[i])&&(en[x]!=sta[x])){
			--ans;
			cnt[i]=0;
		}
		if(x&&(!(en[i]!=sta[i]))&&(en[x]!=sta[x])){
			++ans;
			cnt[i]=1;
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;++i){
		if(cnt[i]){
			printf("%lld\n",i);
		}
	}
	return 0;
}
```
注：借鉴了 [VTloBong](https://www.luogu.com.cn/user/212187) 的代码思路。

---

## 作者：Zinc_acetate (赞：1)

从根节点向下搜时，假设还未搜到与目标值不相等的节点，则这些节点都不用修改~~这应该不用多说吧~~，假设搜到第一个与目标值不相等的节点，因为它的祖先节点都没有修改过，该节点一定需要修改一次，此时记录下这一节点修改过……

~~好了，我编不下去了，看代码吧（~~

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
vector<int> b[100010];
vector<int> ans;
bool k[100010];
int a[100010];
int x[100010];
int n;
void dfs(int i, int c1, int c2) // c1记录当前节点有没有修改，c2记录父/子节点有没有修改
{
    k[i] = 1;
    if (a[i] ^ c1 ^ x[i]) // 判断当前节点经过它上面节点的修改后是否与目标值相等
    {
        c1 ^= 1; // 记录当前节点进行修改
        ans.push_back(i);
    }
    for (auto j : b[i])
    {
        if (k[j])
            continue;
        dfs(j, c2, c1); // 交换c1,c2，继续dfs
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        b[u].push_back(v);
        b[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    dfs(1, 0, 0);
    cout << ans.size() << endl;
    for (auto i : ans)
    {
        cout << i << endl;
    }
    return 0;
}
```


---

## 作者：_Weslie_ (赞：0)

CF RMJ 炸了以来第一篇 CF 题解（从 vj 过的这道题）。

## Solution CF429A

### Idea

发现这个题是在树上进行操作，所以一定要进行树上 dfs，但是你会发现在这个题中正常的树上 dfs 满足不了我们的要求。

显然一个点更改 $2$ 次一定不优，所以只需要考虑一个点是否需要被更改即可。

我们不难发现根据题中的改变方式，发现如果你改变节点 $u$ 的子树，改变的点 $v$ 一定满足以下性质：$depu_u\equiv depu_v\ (\mod 2)$，其中 $depu_x$ 为以 $u$ 为根的树中，$x$ 的深度。

根据余数的可加性，我们以 $1$ 为根建立树，则改变节点 $u$ 的子树，改变的点 $v$ 一定满足以下性质：$dep_u\equiv dep_v\ (\mod 2)$，其中 $dep_x$ 为以 $1$ 为根的树中，$x$ 的深度。

接下来上一个贪心策略：以 $1$ 为根，dfs 整棵树，如果当前遍历到的点 $x$ 使得改变后的 $col_x\neq to_x$（其中 $col_x$ 为改变 $x$ 的祖先使得 $x$ 的祖先全部符合要求之后 $x$ 的颜色，$to_x$ 为 $x$ 最终期望的颜色），则改变 $x$ 的值。

正确性显然，但是为什么它具有最优性呢？

我们假如对于以 $x$ 为根的子树，单独拿出来看的话，会发现 $x$ 没有祖先，所以如果 $x$ 不符合条件，必须要把 $x$ 更改，然后把信息遗传到下面。

为什么我们可以单独拿出来看呢？因为我们在整棵树中，遍历到 $x$ 时 $x$ 的祖先一定已经被遍历过，是否被更改也已经确定。显然遗传到 $x$ 时，$x$ 的值被更改过多少次，这个是确定的。

那么接下来我们可以在遍历到一个点时，暴力修改它的后代，这样是 $\operatorname{O}(n^2)$ 的。

但是这题 $n\le 10^5$，有没有办法不进行暴力修改呢？

显然有的。我们不难发现对于两个点 $u$ 和 $v$ 满足 $u$ 是 $v$ 的祖先且 $dep_u\equiv dep_v\ (\mod 2)$，对 $u$ 和 $v$ 都进行修改，对它下面的后代修改所传递的效果和 $u$ 和 $v$ 都不修改的效果是一样的。所以我们可以直接在 dfs 的过程中分别记录奇数和偶数深度节点的 $col$ 是否已经被它的祖先们修改即可。

不难发现 $0\oplus 1=1$，$1\oplus 1=0$（其中 $\oplus$ 表示二进制下不进位加法即异或），所以我们直接对奇数和偶数深度节点的 $col$ 是否已经被它的祖先们修改的标记异或 $1$，就可以便捷的记录。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int col[N],to[N],n;
struct node{
	int u,v,nxt;
}e[N<<1];
int head[N],cnt;
void add(int u,int v){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
vector<int>ans;
void dfs(int now,int fa,int dep,int jchang,int ochang){
    if(dep&1){
        if((jchang^col[now])!=to[now]){
            ans.push_back(now);
            jchang^=1;
        }
    }
    else{
        if((ochang^col[now])!=to[now]){
            ans.push_back(now);
            ochang^=1;
        }
    }
    for(int i=head[now],v;i;i=e[i].nxt){
        v=e[i].v;
        if(v==fa)continue;
        dfs(v,now,dep+1,jchang,ochang);
    }

}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++)scanf("%d",&col[i]);
    for(int i=1;i<=n;i++)scanf("%d",&to[i]);
    dfs(1,0,1,0,0);
    printf("%d\n",ans.size());
    for(auto x:ans)printf("%d\n",x);
}
```

---

## 作者：Sylvia_starx (赞：0)

## CF429A Xor-tree 题解

显而易见的，这是一个树上 dp，每次都是将 $cur$
节点的子树中的奇数层翻转，这题也可以在[P5658 [CSP-S2019] 括号树](https://www.luogu.com.cn/problem/P5658)上稍作修改。

#### CODE
```c
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,dp[N],ans,a[N],b[N];
bool vis[N];
vector<int> nbr[N];
void dfs(int cur,int fa,int dep,int odd,int even) // cur为当前节点，fa为cur父节点，dep为cur的子树层数个数，odd为奇数层数值，even为偶数层数值 
{
	a[cur] ^= (dep % 2 ? odd : even);  // 判断奇偶性，与奇偶层所对应的数值进行异或 
	if(a[cur] != b[cur]) // 如果不相等，需要进行操作 
	{
		ans++; // 操作次数累加 
		vis[cur] = 1;
		if(dep % 2 != 0)	
			odd ^= 1;  // 奇数深度所要改变的数值翻转 
		else
			even ^= 1;  // 同理，偶数深度的数值也需要反转 
	}
	for(int i=0;i<nbr[cur].size();i++)
	{
		int nxt = nbr[cur][i];
		if(nxt == fa)
			continue;
		dfs(nxt,cur,dep+1,odd,even); // 往子节点nxt遍历，继续翻转子树，直到相等 
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		nbr[x].push_back(y);
		nbr[y].push_back(x); // 建立无向边 
	}
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	dfs(1,0,1,0,0); // 从根节点开始搜索 
	cout<<ans<<"\n";
	for(int i=1;i<=n;i++)
		if(vis[i]) 
			cout<<i<<"\n";
	return 0;
 } 
```


---

## 作者：fengqiao17 (赞：0)

### 题目大意

给定一棵点权为 0 或者 1 的树，现在需要经过若干次操作使得树上的点权变成输入要求的样子。

一次操作是指：

1. 选择一个点 $i$；
2. 将 $i$ 的点权反转（0 变为 1，1 变为 0），并且 $i$ 的子节点不反转；$i$ 的孙子节点反转，并且 $i$ 的曾孙子节点不反转……以此类推，交替进行反转。

### 思路分析

一道非常不错的练手题。

这一个题~~很明显~~可以看出来是一道树上的 dfs。那么怎么做呢？

答案是：直接模拟即可。我们在 dfs 里面带上四个参数：$cur$、$fa$、$x$、$y$。其中 $cur$ 表示当前处理的节点编号，$fa$ 表示当前节点的父亲节点，防止双向边卡死，这都是树上 dfs 的基本操作。$x$ 表示当前节点是否需要反转，$y$ 表示子节点是否需要反转，这两个可以用来统计是否当前需要进行操作。

具体可以看一下代码。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> G[N];
int s[N] , e[N];
int ans[N] , cnt = 0;
void dfs(int cur , int fa , int x , int y){
	if((s[cur] ^ x) != e[cur]){//如果按照当前修改方式修改不能达到目标 
		x = x ^ 1;//那么就可以用一次操作 
		ans[++cnt] = cur;//记录当前操作 
	}
	for(int i = 0 ; i < G[cur].size() ; i++){//常规树上dfs 
		int nxt = G[cur][i];
		if(fa == nxt){//注意双向边要判断防止卡死 
			continue;
		}
		dfs(nxt , cur , y , x);//往下一层递归 
	}
	return ;
}
int main(){
	int n;
	cin>>n;
	for(int i = 1 ; i < n ; i++){
		int x , y;
		cin>>x>>y;
		G[x].push_back(y);//常规建双向边操作 
		G[y].push_back(x);
	}
	for(int i = 1 ; i <= n ; i++){
		cin>>s[i];//输入起始状态 
	}
	for(int i = 1 ; i <= n ; i++){
		cin>>e[i];//输入终止状态 
	}
	dfs(1 , 0 , 0 , 0);//从点1开始跑dfs，一开始x和y都为0 
	cout<<cnt<<endl;
	sort(ans + 1 , ans + 1 + cnt);
	for(int i = 1 ; i <= cnt ; i++){
		cout<<ans[i]<<endl;//排序并输出答案 
	}
	return 0;
}
```

### 七嘴八舌

这一道题还是很好想的，主要是 $x$ 和 $y$ 的使用。

如果有什么问题，可以找我。~~写作不易，有误轻喷~~

---

## 作者：liwenxi114514 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF429A)。

#### 思路：
分析题目，当且仅当当前值与目标值不相等时才需要操作，而且需要变化的深度的奇偶性与操作深度的奇偶性相同，所以我们只需要记录一下深度以及上一次进行了操作的奇数深度或偶数深度，取反就行了。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,w[100005],m[100005],sum;
vector<int> v[100005],tt;
void dfs(int x,int fa,int dpt,int ji,int ou){//变量意思分别为：当前点，父亲节点，深度，上一个奇数深度对应的数值，上一个偶数深度对应的数值。
	w[x]^=((dpt%2)?ji:ou);//判断奇偶性，如果是奇数，就把它与奇数的深度的值异或，偶数一样。
	if(w[x]!=m[x]){//如果不相等，需要操作。
		sum++;//计算次数
		tt.push_back(x);//存储答案
		if(dpt%2){
			ji^=1;//改变奇数深度所对应的数值
		}else{
			ou^=1;//改变偶数深度所对应的数值
		}
	}
	for(int i=0;i<v[x].size();i++){
		if(v[x][i]!=fa){
			dfs(v[x][i],x,dpt+1,ji,ou);//遍历下一层
		}
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);//无向边
	}
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	for(int i=1;i<=n;i++){
		cin>>m[i];
	}
	dfs(1,0,1,0,0);
	cout<<sum<<"\n";
	for(int i=0;i<tt.size();i++){
		cout<<tt[i]<<"\n";
	}
	return 0;
}
```


---

## 作者：tmp_get_zip_diff (赞：0)

## 思路

本题一眼 $dp$，但是答案要寻问过程，而且改或不改是确定的，只用按题意模拟即可。

DFS 的时候统计深度奇偶、奇数深度操作次数、偶数深度操作次数即可，`0` 或 `1` 只需要异或。

## 代码
```
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,cs[N],mb[N];
vector<int>nbr[N];
bool vis[N];

void dfs(int cur,int fa,int dep,int jn,int on)
{
	int num=(dep%2==1)?jn:on,tag=0;
	if(cs[cur]^num!=mb[cur])
	{
		vis[cur]=true;
		tag=1;
	}
	for(int i=0;i<nbr[cur].size();i++)
	{
		int nxt=nbr[cur][i];
		if(nxt==fa)
			continue;
		if(dep%2==0)
			dfs(nxt,cur,1,jn,on^tag);
		else
			dfs(nxt,cur,0,jn^tag,on);
	}
	return ;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		cin>>cs[i];
	for(int i=1;i<=n;i++)
		cin>>mb[i];
	dfs(1,0,1,0,0);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(vis[i]==true)
			ans++;
	cout<<ans<<"\n";
	for(int i=1;i<=n;i++)
		if(vis[i]==true)
			cout<<i<<"\n";
	return 0;
}
```

---

## 作者：tanghg (赞：0)

对于本题，思路其实非常简单。

我们发现，如果树根不符合规定的话那么树根一定是要执行操作的。之后就**不能对树根再进行操作**（否则就重复反转了）。那么对于根的儿子也同理，由于父亲已经被操作过了，则自己如果不符合也一定要执行一次操作。

那么我们就可以发现做法——从树根开始按照 dfs 的顺序依次访问每一个节点。如果发现当前节点不符合目标，则执行一次操作。

而执行操作我们可以记录一个 `fan` 数组来代表直到当前位置翻转了多少次。之后对于节点 u，如果 `fan[u]` 为奇数，则证明当前节点是取反的状态，否则就是原状态。
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll MAXN = 2e5 + 5;
struct edge {
    ll to, nxt;
} e[MAXN];
ll n, head[MAXN], tot;

void add(ll u, ll v) {
    e[++tot].nxt = head[u];
    e[tot].to = v;
    head[u] = tot;
}

ll fa[MAXN], fan[MAXN], s[MAXN], t[MAXN], S[MAXN], sz;

void dfs(ll u, ll f) {
    if (fan[fa[f]] % 2 == 0) {
        if (s[u] != t[u]) {
            S[++sz] = u;
            fan[u]++;
        }
    } else {
        if ((!s[u]) != t[u]) {
            S[++sz] = u;
            fan[u]++;
        }
    }
    for (ll i = head[u]; i; i = e[i].nxt) {
        ll v = e[i].to;
        if (v == f) {
            continue;
        }
        fan[v] = fan[f];
        fa[v] = u;
        dfs(v, u);
    }
}

int main() {
    scanf("%lld", &n);
    for (int i = 1; i < n; ++i) {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &s[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &t[i]);
    }
    dfs(1, 0);
    printf("%lld\n", sz);
    sort(S + 1, S + sz + 1);
    for (int i = 1; i <= sz; ++i) {
        printf("%lld\n", S[i]);
    }
    return 0;
}
```


---

