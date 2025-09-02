# [SDCPC 2023] Trie

## 题目描述

请回忆字典树的定义：

- 一棵大小为 $n$ 的字典树是一棵有 $n$ 个节点和 $(n - 1)$ 条边的有根树，每一条边都标有一个字符。
- 字典树中的每个节点都代表一个字符串，令 $s(x)$ 表示节点 $x$ 代表的字符串。
- 字典树的根代表的是空字符串。设节点 $u$ 为节点 $v$ 的父节点，设 $c$ 表示节点 $u$ 和 $v$ 之间的边上标有的字符，则 $s(v) = s(u) + c$。这里的 $+$ 代表字符串连接，而不是普通的加法。
- 所有节点代表的字符串互不相同。

给定一棵有 $(n + 1)$ 个节点的有根树，节点编号为 $0, 1, \cdots, n$，其中节点 $0$ 是根节点。树上共有 $m$ 个关键节点，其中第 $i$ 个关键节点的编号为 $k_i$。保证所有叶子节点都是关键节点。

请为每一条边标上一个小写字母，使得这棵有根树变为一棵大小为 $(n + 1)$ 的字典树。考虑所有关键节点代表的字符串构成的序列 $A = \{s(k_1), s(k_2), \cdots, s(k_m)\}$，设 $B = \{w_1, w_2, \cdots, w_m\}$ 是由序列 $A$ 中所有字符串按字典序从小到大排序后得到的字符串序列，您需要找到一个标记字母的方案，使得序列 $B$ 最小。

称长度为 $x$ 的字符串 $P = p_1p_2\cdots p_x$ 的字典序小于长度为 $y$ 的字符串 $Q = q_1q_2\cdots q_y$，若

- $x < y$ 且对于所有 $1 \le i \le x$ 有 $p_i = q_i$，或者
- 存在一个整数 $1 \le t \le \min(x, y)$，对于所有 $1 \le i < t$ 有 $p_i = q_i$，且 $p_t < q_t$。

称长度为 $m$ 的字符串序列 $F = \{f_1, f_2, \cdots, f_m\}$ 小于长度为 $m$ 的字符串序列 $G = \{g_1, g_2, \cdots, g_m\}$，若存在一个整数 $1 \le t \le m$，对于所有 $1 \le i < t$ 有 $f_i = g_i$，且 $f_t$ 的字典序小于 $g_t$ 的字典序。

## 样例 #1

### 输入

```
2
5 4
0 1 1 2 2
1 4 3 5
1 1
0
1```

### 输出

```
abaab
a```

# 题解

## 作者：do_while_true (赞：5)

orz negiizhao

自底向上确定每个点的所有出边上挂的字符，那么问题就是比较 $x,y$ 两个子树的字典序大小。直接一起往下 dfs，先找到标记点的子树更小，如果 dfs 过程中一棵树找完了而另一棵树没找完并且还没确定大小，这时还没找完的那棵树应当排到前面。在递归的最浅层也就是比较 $x,y$ 时最后特判下标号大小即可。

这里排序使用归并排序 `stable_sort`，现在来分析一下复杂度：

单独考虑每一层：在归并两个队头分别为 $u,v$ 的子树序列 $p,q$ 时，花费 $\min(size_u,size_v)$ 的时间代价，将其中之一 pop 掉。先把代价放缩成 pop 掉的那个子树的 $size$，但如果 pop 掉的是重儿子是把代价记成没有被 pop 掉的那个轻儿子上。这样每个轻儿子计算代价时最多被计算两次，所以同一层所花费的是轻儿子子树和级别的。再算上归并排序一共有 $\log$ 层，那么时间复杂度就是 $\mathcal{O}(n\log^2 n)$．

```cpp

const int N=200010;
int n,m;
int fa[N],vis[N],col[N],siz[N];
vi eg[N];
void dfs1(int x){
	siz[x]=1;
	for(auto v:eg[x])dfs1(v),siz[x]+=siz[v];
	stable_sort(eg[x].begin(),eg[x].end(),[&](const int &x,const int &y){
		function<int(int,int)>cmp=[&](int u,int v){//u<v:1  v<u:-1  u=v:0
			if(vis[u]+vis[v]==1)return vis[u]?1:-1;
			int len=min(eg[u].size(),eg[v].size());
			for(int i=0;i<len;i++){
				int t=cmp(eg[u][i],eg[v][i]);
				if(t)return t;
			}
			if(siz[u]==siz[v]){
				if(u==x&&v==y)return u<v?1:-1;
				return 0;
			}
			else return siz[u]>siz[v]?1:-1;
		};
		return cmp(x,y)==1?1:0;
	});
	int len=eg[x].size();
	for(int i=0;i<len;i++)col[eg[x][i]]=i;
}
void solve(){
	read(n,m);
	for(int i=0;i<=n;i++)vi().swap(eg[i]),vis[i]=0;
	for(int i=1;i<=n;i++)read(fa[i]),eg[fa[i]].pb(i);
	for(int i=1,x;i<=m;i++)vis[read(x)]=1;
	dfs1(0);
	for(int i=1;i<=n;i++)putchar('a'+col[i]);
	puts("");
}
```

---

## 作者：_Ch1F4N_ (赞：0)

打杭电时发现的 $O(n \log n)$ 做法。

考虑自下而上地给每个点的所有儿子定序，当你决策儿子 $u,v$ 之间的顺序时，考虑将 $u,v$ 子树内已经定好序的所有字符串记为 $S_{u,1},S_{u,2},\dots,S_{u,k}$ 与 $S_{v,1},S_{v,2},\dots,S_{v,l}$，如果两个字符串序列不构成前后缀关系，找到第一个不同的位置 $S_{u,i},S_{v,i}$，显然哪个小就应该把其所在的子树放在前面，而若构成前后缀关系就会把序列长度更长的放在前面。

注意到我们可以借助字典树的结构刻画这个比较过程，比较节点 $u,v$ 时先按照顺序一一比较其对应位置上的儿子，如果儿子子树完全相同（利用树哈希可以快速实现判断）则跳过，并向第一个不同的儿子子树去递归，如果没有找到不同的儿子子树就比完了就认为儿子数量多的优先，不难发现这么比较和上文的比较方法完全等价。

下面来分析复杂度：记录 $w_u$ 表示点 $u$ 的儿子数，记录 $g_u$ 表示选出一条从 $u$ 出发向子树内节点的链最大的链上点 $w$ 和，注意到比较 $u,v$ 优先级的复杂度不超过 $\min(g_u,g_v)$，也就是可以把比较代价挂到 $u,v$ 中任意一个点上，注意到对儿子归并排序的过程中不难构造出除去一个最大的 $g$ 以外其他所有的 $g$ 上都挂了 $O(\log n)$ 次比较代价的方案，结合长剖的结论以及 $O(\sum w_u) = O(n)$，可以得到总时间复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
const int maxn = 2e5+114;
int fa[maxn];
vector<int> son[maxn];
int n,m;
int leaf[maxn];
int vis[maxn];
void dfs1(int u){
    for(int v:son[u]){
        dfs1(v);
        leaf[u]+=leaf[v];
    }
}
ll val[maxn];
mt19937_64 rd(time(0));
ll C1,C2;
ll g(ll x){
    return (x^C1)*(x^C1)+(x^C2);
}
ll C3,C4;
bool cmp(int x,int y){
    if(val[x]==val[y]) return x<y;
    if((vis[x]^vis[y])==1) return vis[x]>vis[y];
    for(int i=0;i<min(son[x].size(),son[y].size());i++){
        if(val[son[x][i]]!=val[son[y][i]]){
            return cmp(son[x][i],son[y][i]);
        }
    }
    return son[x].size()>son[y].size();
}
char ans[maxn];
void dfs2(int u){
    for(int v:son[u]) dfs2(v);
    sort(son[u].begin(),son[u].end(),cmp);
    for(int v:son[u]) val[u]+=g(val[v]);
    val[u]+=(vis[u]==1?C3:C4);
    char c='a';
    for(int v:son[u]){
        ans[v]=c;
        c++;
    }
}
void work(){
    cin>>n>>m;
    C1=rd(),C2=rd(),C3=rd(),C4=rd();
    for(int i=1;i<=n;i++){
        cin>>fa[i];
        son[fa[i]].push_back(i);
    }
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        leaf[x]=1;
        vis[x]=1;
    }
    dfs1(0);
    dfs2(0);
    for(int i=1;i<=n;i++) cout<<ans[i];
    cout<<"\n";
    for(int i=0;i<=n;i++){
        leaf[i]=vis[i]=0;
        son[i].clear();
        fa[i]=0;
        val[i]=0;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work(); 
    return 0;
}
```

---

