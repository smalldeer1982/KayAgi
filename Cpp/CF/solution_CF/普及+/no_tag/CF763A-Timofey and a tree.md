# Timofey and a tree

## 题目描述

Each New Year Timofey and his friends cut down a tree of $ n $ vertices and bring it home. After that they paint all the $ n $ its vertices, so that the $ i $ -th vertex gets color $ c_{i} $ .

Now it's time for Timofey birthday, and his mother asked him to remove the tree. Timofey removes the tree in the following way: he takes some vertex in hands, while all the other vertices move down so that the tree becomes rooted at the chosen vertex. After that Timofey brings the tree to a trash can.

Timofey doesn't like it when many colors are mixing together. A subtree annoys him if there are vertices of different color in it. Timofey wants to find a vertex which he should take in hands so that there are no subtrees that annoy him. He doesn't consider the whole tree as a subtree since he can't see the color of the root vertex.

A subtree of some vertex is a subgraph containing that vertex and all its descendants.

Your task is to determine if there is a vertex, taking which in hands Timofey wouldn't be annoyed.

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
1 2 1 1
```

### 输出

```
YES
2```

## 样例 #2

### 输入

```
3
1 2
2 3
1 2 3
```

### 输出

```
YES
2```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4
1 2 1 2
```

### 输出

```
NO```

# 题解

## 作者：lixiao189 (赞：11)

## 一道毒瘤的考验人类智慧的题目
### 题目大意：
> 现在有一个无根树，我们加入把其中的一个结点看做根，那么这个根上的每一个子树中都不能有一个结点的颜色不同，如果都相同，那么此时就是合法的，我们输出YES及这个结点。如果不存这样的根，那么输出NO。

### 思路：
因为如果一个树的子树中只要有一个点与这个子树中的其他点颜色不同，那么这样主角就会生气，所以这样**只有一种情况是合法的**，就是当这个无根树的某个结点作为根时，其连接到的结点与根的颜色不一样的个数等于所有结点与这个根颜色不同的结点个数。(有点绕，耐心理解^-^)。因为子树中一旦出现某个结点与其他结点颜色不同就会造成整个树不合法。
### 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5+5;

int n;
int col[N];
int a[N],b[N];
int sum[N];
int sum1=0;

int main(){
	
	scanf ("%d",&n);
	int temp_x,temp_y;
	for (int i=1;i<=n-1;i++){
		scanf ("%d%d",&a[i],&b[i]);
	}
	for (int i=1;i<=n;i++) scanf ("%d",&col[i]);
	
	for (int i=1;i<=n-1;i++){
		if (col[a[i]] != col[b[i]]){
			sum1++;
			sum[a[i]]++;sum[b[i]]++;
		}
	}
	
	for (int i=1;i<=n;i++){
		if (sum[i]==sum1){
			printf ("YES\n%d\n",i);
			return 0;
		}
	}
	
	printf ("NO\n");
	
	return 0;
	
}
```

---

## 作者：Erica_N_Contina (赞：2)

## 思路

思维题。

我们计算出颜色总数 $cnt$，那么我们就要知道一个点，满足这个点有 $≥cnt$ 条出边并且连接了 $cnt$ 种颜色。这样想的话我们考虑枚举每个节点。可是这样我们还要解决统计颜色等问题。并且很容易可以找到这种方法很难区分无解的情况，复杂度过高。

所以我们换一种思路来考虑。

我们还是考虑枚举那个根节点，只不过我们要从性质上来考虑这个节点是否合法。

假设一条边 $i$ 的两个节点为 $a,b$，如果 $a≠b$，那么我们把这条边的边权 $v_i$ 设置为 $1$。否则设置为 $0$。设所有边权和为 $vsum$。

那么当我们枚举到一个节点 $rt$ 时，如果 $rt$ 的出边的边权和 $=vsum$，那么这个点是满足要求的。否则，就说明除了这些出边以外，还有别的边连接了两个颜色不同的点，并且很明显这条边是在某棵子树中的，不符合要求。

对于每个点的出边边权和，我们扫描一次所有边即可，这样即可不用建图。如果一条边的 $a_i≠b_i$，那么 $cnt_a+1,cnt_b+1$。（$cnt_k$ 记录点 $k$ 的出边边权和）

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,p,q,sum,T,cnt[N],ans,a[N],b[N],c[N];

signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a[i]>>b[i];
	} 
	for(int i=1;i<=n;i++)cin>>c[i];
	
	for(int i=1;i<n;i++){
		if(c[a[i]]!=c[b[i]])cnt[a[i]]++,cnt[b[i]]++,sum++;
		//cnt[i]记录点i的出边边权和,sum记录所有边权和 
	}
	
	for(int i=1;i<=n;i++){
		if(cnt[i]==sum){
			cout<<"YES\n"<<i;
			return 0;
		}
	}
	cout<<"NO"<<endl;
	return 0;
}


```




---

## 作者：zhangqiuyanAFOon2024 (赞：1)

一道思维题。

大家最好有图论基础。

我们先读题，题意是现在让你选择一个点作为根节点，使得这个根节点的所有儿子满足以该儿子节点的作为根的子树中所有点颜色均相同。

我们观察一下，发现根节点是与其他连接的点颜色不同最多的最优（这个你要仔细思考一下）。

我们就可以找出根结点，通过深搜判断一下是否满足题意即可。

建图的话，推荐大家用 `vector`。

~~链式前向星太麻烦。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int col[maxn];//颜色
vector<int>e[maxn];//图
int dfs(int x,int fa,int nowcol){//判断是否满足题意，1表示否
	if(col[x]!=nowcol) return 1;
	for(int i=0;i<e[x].size();i++)
		if(e[x][i]!=fa){
			int flag=dfs(e[x][i],x,nowcol);
			if(flag) return 1;
		}
	return 0;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}//建图
	for(int i=1;i<=n;i++)
		cin>>col[i];
	int ans,maxn=-1;
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(int j=0;j<e[i].size();j++)
			if(col[e[i][j]]!=col[i]) tmp++;
		if(tmp>maxn) maxn=tmp,ans=i;
	}//找根节点
	int flag=0;
	for(int i=0;i<e[ans].size();i++){
		int nowcol=col[e[ans][i]];
		flag=dfs(e[ans][i],ans,nowcol);
		if(flag){
			cout<<"NO"<<endl;
			break;//不行直接输出
		}
	}//判断
	if(!flag) cout<<"YES"<<endl<<ans<<endl;//可以
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

乱搞题。

优先考虑 DP。定义状态函数 $\mathit{f}_i$ 表示在以 $1$ 为根时，$i$ 为根的子树中颜色是否相同。如果对于 $1$ 的每一个儿子 $j$，都有 $\mathit{f}_{j}=1$，则输出 $1$ 就行。

考虑换根的情况。在以 $i$（$i \ne 1$）为根的时候，原本是 $i$ 的儿子的节点还是其节点。这时候 $i$ 的父节点也将成为儿子。而 $i$ 的父节点为根的子树中的节点就是除了 $i$ 为根的子树外的所有节点。搞一个 DFS 序，定义 $w_i$ 表示在 DFS 序中，节点 $i$ 的位置；$siz_i$ 表示节点 $i$ 所在的子树节点数量。则在以 $i$ 为根的时候，其原本的父节点为根的子树就是 $[1,w_i-1]$ 与 $[w_i+siz_i,n]$ 中的所有节点。

原来的儿子判定直接像节点 $1$ 那样就行。而对于新的儿子，判定两个区间是否颜色全部相同，乱搞个分块就行。在这里，$1$ 节点是必回出现的，所以我们可以以 $1$ 的颜色为基准来判定。

复杂度 $O(n \sqrt{n})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=2e5+10;
int n,col[N];
int ne[N],e[N],h[N],idx;
int s[N],len;
int where[N],dfsx[N],siz[N],fath[N],cnt;
int f[N];

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dfs(int now,int fa){
	siz[now]=1,fath[now]=fa,
	dfsx[++cnt]=now,where[now]=cnt,
	f[now]=1;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now);siz[now]+=siz[j];
		if(col[j]!=col[now]) f[now]=0;
		f[now]=min(f[now],f[j]);
	}
}

il int get(int x){return (x-1)/len+1;}
il int query(int l,int r,int x){
	if(l>r) return 1;
	int bl=get(l),br=get(r),ans=0;
	if(bl==br){
		for(re int i=l;i<=r;++i) 
			if(col[dfsx[i]]!=x) return 0;
		return 1;
	}
	else{
		for(re int i=l;i<=bl*len;++i)
			if(col[dfsx[i]]!=x) return 0;
		for(re int i=bl+1;i<br;++i)
			if(s[i]!=len||col[dfsx[i*len]]!=x) return 0;
		for(re int i=(br-1)*len+1;i<=r;++i)
			if(col[dfsx[i]]!=x) return 0;
		return 1;
	}
}

il void solve(){
	cin>>n;len=sqrt(n);
	for(re int i=1,u,v;i<n;++i) cin>>u>>v,add(u,v),add(v,u);
	for(re int i=1;i<=n;++i) cin>>col[i];
	dfs(1,0);
	for(re int i=1;i<=n;++i) s[get(i)]+=((col[dfsx[i]]==col[dfsx[i-1]])||(!s[get(i)]));
	for(re int i=1;i<=n;++i)
		if(i==1){
			bool fl=0;
			for(re int j=h[i];j;j=ne[j]) if(!f[e[j]]) fl=1;
			if(!fl){cout<<"YES\n"<<i;return;}
		}
		else{
			bool fl=0;
			for(re int j=h[i];j;j=ne[j]) if(!f[e[j]]&&e[j]!=fath[i]) fl=1;
			if(fl) continue;
			if(query(1,where[i]-1,col[1])&&query(where[i]+siz[i]-1+1,n,col[1])){cout<<"YES\n"<<i;return;}
		}
	cout<<"NO";return;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：Bai_R_X (赞：0)

## 思路
需要认识到一个结论：选择与邻接节点颜色不同数量最多的一个节点最优。

因为在颜色数一定时，邻接节点颜色不同数越少，那么将相同颜色的节点视为子节点最优。

于是在不优化时，时间复杂度为 $O(n^2)$。优化后，时间复杂度为 $O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Edge
{
	int v,nxt;
}e[200005];
int head[100005],n,u,v,i,c[100005],tot,diff[100005],maxid;
void add(int u,int v)
{
	e[++tot].v=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
bool __dfs(int u,int fa,int color)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		if(c[v]!=color)return 0;
		if(!__dfs(v,u,color))return 0;
	}
	return 1;
}
bool dfs(int u)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(!__dfs(v,u,c[v]))return 0;
	}
	return 1;
}
signed main()
{
    cin>>n;
    for(i=1;i<n;i++)
    {
    	cin>>u>>v;
    	add(u,v);
    	add(v,u);
	}
	for(i=1;i<=n;i++)cin>>c[i];
	for(i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=e[j].nxt)
		{
			int v=e[j].v;
			if(v==i)continue;
			if(c[i]!=c[v])diff[i]++;
		}
		if(diff[i]>=diff[maxid])maxid=i;
	}
	if(dfs(maxid))cout<<"YES"<<endl<<maxid;
	else cout<<"NO";
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

这种东西可以考虑一下换根的操作。

$f_x$ 表示 $x$ 子树和 $x$ 的颜色是否相同。

考虑根为 $rt$ 的情况。显然需要 $rt$ 的所有儿子 $v$ 满足 $f_v=1$。

在判断的时候顺便存储一下当前 $rt$ 那一个子树 $V$ 使得 $f_{V}=0$，如果大于等于两个 $V$ 存在，那么显然不可以向下转移。

否则向 $V$ 转移即可。容易发现此时根 $rt$ 变成了新根的子树，这一棵子树显然是好的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, fir[N], nxt[N << 1], son[N << 1], tot, col[N], u, v, nod = -1;
bool f[N];
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline void dfs(int x, int ff = 0){
	f[x] = 1;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		if(col[x] != col[son[i]] || !f[son[i]]){
			f[x] = 0;
		}
	}
}
inline void dfs2(int x, int ff = 0, int colf = col[1]){
	int difs = -1; 
	for(int i = fir[x]; i; i = nxt[i]){
		if(son[i] == ff) continue ;
		if(f[son[i]]) continue ;
		if(difs != -1) return ;
		difs = son[i];
	}
	if(difs == -1){
		nod = x;
		return ;
	}
	if(colf != col[x]) return ;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		if(son[i] == difs) continue ;
		if(col[son[i]] != col[x]) return ;
	}
	dfs2(difs, x, col[x]);
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++) scanf("%d", &col[i]);
	dfs(1);
	dfs2(1);
	if(~nod){
		puts("YES");
		printf("%d\n", nod);
	}
	else puts("NO");
	return 0;
}
```

---

