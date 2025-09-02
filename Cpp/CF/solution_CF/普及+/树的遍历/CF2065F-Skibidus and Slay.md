# Skibidus and Slay

## 题目描述

我们定义一个长度为 $k$ 的序列的**多数元素**为：该序列中唯一一个出现次数严格大于 $\lfloor \frac{k}{2} \rfloor$ 的数值。如果不存在这样的数值，则称该序列没有多数元素。例如，序列 $[1,3,2,3,3]$ 的多数元素为 $3$（因为 $3$ 出现了 $3$ 次，$3 > \lfloor \frac{5}{2} \rfloor = 2$），而序列 $[1,2,3,4,5]$ 和 $[1,3,2,3,4]$ 则没有多数元素。

Skibidus 找到了一棵有 $n$ 个顶点的树 $ ^{\text{∗}} $ 以及一个长度为 $n$ 的数组 $a$。其中，顶点 $i$ 上写有数值 $a_i$，且 $a_i$ 是区间 $[1,n]$ 内的一个整数。

对于每个 $i$（$1 \le i \le n$），请判断是否存在一条非平凡的简单路径 $ ^{\text{†}} $，使得该路径上顶点构成的数值序列的多数元素为 $i$。

 $ ^{\text{∗}} $ 树指的是一个无环的连通图。
 
 $ ^{\text{†}} $ 非平凡的简单路径指的是一个顶点序列 $v_1, v_2, \dots, v_m$（其中 $m \ge 2$），满足对于所有 $1 \le i \le m-1$，顶点 $v_i$ 与 $v_{i+1}$ 之间存在一条边，并且所有顶点均互不相同。注意路径至少包含 $2$ 个顶点。

## 说明/提示

- 在第一个测试用例中，没有任何一条非平凡路径能使得 $1$、$2$ 或 $3$ 成为多数元素，因此输出的二进制字符串为 `000`。
- 在第二个测试用例中，路径 $1 \rightarrow 2 \rightarrow 4$ 是一条非平凡路径，在该路径上 $3$ 为多数元素。

## 样例 #1

### 输入

```
4
3
1 2 3
1 3
2 3
4
3 1 1 3
1 2
2 3
4 2
4
2 4 4 2
1 2
2 3
3 4
13
1 4 4 7 4 7 1 1 7 11 11 11 11
1 2
2 3
3 4
4 5
4 6
2 7
7 8
2 9
6 10
5 11
11 12
10 13```

### 输出

```
000
1010
0001
1001001000100```

# 题解

## 作者：harmis_yz (赞：6)

首先拿到这种题，发现题目是让求对于每种颜色，是否存在两个颜色相同的点，使得它们之间的点的数量不超过 $1$。这个的证明显然，如果答案是一条路径 $P$，那么 $cnt > \lfloor \frac{|P|+1}{2}\rfloor$。根据鸽巢原理，这玩意要么是颜色为 $x$，颜色不为 $x$，颜色为 $x$……要么存在两个相邻的点颜色都为 $x$。

好，现在开始抽象。我们是要对每个颜色求这个是吧，这里有个典 trick。如果我们去枚举颜色，在将 $n$ 个点都遍历一遍求答案显然时间复杂度炸裂。但是我们实际上有用的点只有 $O(cnt_x)$ 个，其中 $cnt_x$ 为颜色为 $x$ 的点的数量。那么我们对所有颜色为 $x$ 的点建虚树。则现在问题变成树上是否存在两个关键点的距离不超过 $2$。考虑 DP。定义状态函数 $f_{u}$ 表示 $u$ 为根的子树中，从 $u$ 到一个颜色为 $x$ 的点的最短距离。那么我们枚举 $u$ 的一个儿子时，可以直接用前面那些儿子的子树转移出来的 $f_u$ 来和 $v$ 这个儿子子树中最近的颜色为 $x$ 的点进行取 $\min$。那么只要最终这个最小值不超过 $2$ 就有解了。时间复杂度 $O(n)$。

说下简单的做法吧。因为两个颜色为 $x$ 的点距离不超过 $2$，那么这两个点要么直接连边，要么通过 $1$ 个中间点连边。所以记录一下每个点是否有个颜色为 $x$ 的出边就行了。时间复杂度 $O(n)$。

没有代码，看代码找我，但是我只有虚树做法的代码。

---

## 作者：_hi_ (赞：6)

## 思路

首先能想到一个暴力搜，对每一个点都跑一遍全图，但复杂度肯定是不允许的。

接着，**注意到**其实对于每个点只用往下跑三步。小蒟蒻太菜，只能给一个感性证明：若当前点是在三步以后才符合了答案，那么从第三个步开始跑也一定能成功。

但是如果还是 dfs 的话，即使用了上述的剪枝，菊花图的复杂度仍是不下来的。

所以可以考虑给每一个点开一个 map，记录它能连的点的点权，这样对于每个点，只需要搜它的出边，接着看那个点是否连过一个与当前点相同点权的点就做完了。

## AC code:


```cpp
#include<bits/stdc++.h>
using namespace std;
int _,n;
vector<int>poi[500005];
int dq[500005],ans[500005];
map<int,int>mp[500005];
int main(){
    scanf("%d",&_);
    while(_--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)mp[i].clear();
        for(int i=0;i<=n;i++){
            poi[i].clear();
            if(i!=0)scanf("%d",&dq[i]);
            ans[i]=0;
        }
        for(int i=1;i<n;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            poi[a].push_back(b);
            poi[b].push_back(a);
            mp[a][dq[b]]++,mp[b][dq[a]]++;
        }
        for(int i=1;i<=n;i++){
            if(ans[dq[i]]==1)continue;
            if(mp[i][dq[i]]){
                ans[dq[i]]=1;
                continue;
            }
            for(int j=0;j<poi[i].size();j++){
                long long nv=poi[i][j];
                if(mp[nv][dq[i]]>1){
                    ans[dq[i]]=1;
                    break;
                }
            }
        }
        for(int i=1;i<=n;i++){
            printf("%d",ans[i]);
        }
        printf("\n");
    }
}
```

---

## 作者：litjohn (赞：2)

### 猜结论
首先这个题看上去肯定不能直接枚举所有路径之类的，十分不牛。对于这种不牛的题（尤其它还来自 CF div4），我们一般认为它的背后可能藏着什么重要结论，只要猜到就可以立刻秒掉（参照“地地爱打卡”，梦熊的题）。

于是我们开始猜结论。我们注意到，长度为 2 的路径可能会使得某个值的答案为真，这时这条路径上的两个点的值相同。

我们还注意到，长度为 3 的路径如果两个端点的值相同，也会使得某个值的答案为真。但是如果是中间的点和某个端点的值相同或整条路径的值都相同，那么其中就包含一条长度为 2 的路径，已经使得这个答案为真，就不用再考虑了。

对于长度很长的路径，它们很难考虑。并且根据直觉，它们也难以对答案产生贡献。另一点是，从长度为 3 的路径中某些的答案会被长度为 2 的路径包含这一事实，我们发现更长的路径的贡献可能已经被长度为 3 和 2 的路径包含了。于是我们考虑证明这些路径对答案不产生贡献。

### 证明结论
使用反证。假设一条长度大于 3 的路径，其中有一个出现次数严格大于路径长度一半的值。则显然两个同样标着这个值的点不可能相邻。因为如果相邻，它们就构成一条长度为 2 的路径，其中该值的出现次数严格大于路径长度的一半。

于是只能间杂分布。因为出现次数严格大于一半，所以若任意标着该值的相邻的（意味着在该路径上距离最近的）两点，它们间隔的点数如果大于 1，则必定有两个标着该值的点中间没有间隔的点。

具体来说，若所有（标着该值的）点中间都有间隔，则路径总长不小于 $2c-1$，其中 $c$ 是标着该值的点在路径中的出现次数。若某两点的间隔大于 1，则路径长度不小于 $2c$，又有 
$$
c>\lfloor \frac{\mathrm{len}}{2}\rfloor
$$
由此可推出 $2c>\mathrm{len}$ ，矛盾。故没有间隔点数超过 1 的相邻点。

然后就发现一定存在一条长度为 3 的路径，它的两个端点的值都是路径中出现次数最多的点。我们只需取一个标有该值的点作为一个端点，然后再取路径上相邻的两个点就可以了。

于是最初的结论证毕，长度超过 3 的路径对答案没有贡献。

### 实现思路
发现长度为 2 的路径一定是某个点与它的父亲。

对于长度为 3 的路径，两个端点要么是某个点与它的祖父，要么是某个点与它的兄弟。

第一种长度为 3 的路径和长度为 2 的路径都很好判。记录一下父亲，然后每个点的父亲和祖父都是唯一的，于是 $O(n)$ 搞定。

第二种长度为 3 的路径不能暴力枚举每个点的兄弟，不然遇到菊花就完蛋了。我们把每个点的儿子按照标号的大小排序。然后对于每个点，在它的兄弟节点中二分有没有标号与它相等的。

于是就做完了。开始写代码吧。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
int t, n;
bool ans[500005];
array<int, 500005> a, fa;
array<vector<int>, 500005> e;

void dfs1(int u) {
	if (fa[fa[u]] != 0 && a[fa[fa[u]]] == a[u]) {
		ans[a[u]] = true;
	}

	for (auto i : e[u]) {
		if (i != fa[u]) {
			if (a[i] == a[u]) {
				ans[a[i]] = true;
			}

			fa[i] = u;
			dfs1(i);
		}
	}
}

void dfs2(int u) {
	for (int i = 0; i < e[u].size() - 1; ++i) {
		auto x = lower_bound(e[u].begin() + i + 1, e[u].end(), e[u][i], [](int x, int y) -> bool {
			return a[x] < a[y];
		});

		if (x != e[u].end() && a[*x] == a[e[u][i]]) {
			ans[a[*x]] = true;
		}
	}

	for (auto i : e[u]) {
		if (i != fa[u]) {
			dfs2(i);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> t;
	for (int _ = 0; _ < t; ++_) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			ans[i] = false;
			e[i].clear();
		}

		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
		}

		for (int i = 1; i < n; ++i) {
			int u, v;
			cin >> u >> v;
			e[u].push_back(v);
			e[v].push_back(u);
		}

		for (int i = 1; i <= n; ++i) {
			sort(e[i].begin(), e[i].end(), [](int x, int y) -> bool {
				return a[x] < a[y];
			});
		}

		dfs1(1);
		dfs2(1);

		for (int i = 1; i <= n; ++i) {
			cout << ans[i];
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：jzjr (赞：2)

## 前置知识

* 树
* lca
* 数学

## 题意

如果一个长度为 $n$ 的序列中的众数出现次数严格大于 $\lfloor\frac{n}{2}\rfloor$，那么这个序列的支配度就为其众数。

问 $1\sim n$ 中每一个值在树上是否存在一条链满足其支配度正好为当前值。

## 思路

注意到：

如果一个序列存在支配度，那么一定有两种情况之一出现：

* 存在长为 $2$ 的子段，支配度和原序列相同。

* 存在长为 $3$ 的子段，支配度和原序列相同。

证明很简单，考虑反证法，如果两个都不存在，那就不存在支配度。

题目只是问是否有支配度为 $i$ 的路径，按长度为 $2$ 和长度为 $3$ 扫一遍即可。

## 实现

长度为 $2$ 的子段考虑父节点。

长度为 $3$ 的子段考虑相同值的结点距离是否为 $2$ 即可。

求 lca 就行。

### AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,a[N];
vector<int>mp[N];
vector<int>as[N];
int fa[N],det[N],son[N];
int si[N],top[N],id[N],cnt;
inline void dfs1(int p,int f){
	fa[p]=f;det[p]=det[f]+1;si[p]=1;
	int dmax=0;
	for(auto v:mp[p]){
		if(v==f)continue;
		dfs1(v,p);si[p]+=si[v];
		if(dmax<si[v])son[p]=v,dmax=si[v];
	}
}
inline void dfs2(int p,int tp){
	top[p]=tp;id[p]=++cnt;
	if(!son[p])return ;
	dfs2(son[p],tp); 
	for(auto v:mp[p]){
		if(v==son[p]||v==fa[p])continue;
		dfs2(v,v);
	}
}
inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(det[top[x]]<=det[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(det[x]>det[y])swap(x,y);
	return x;
}
bool ans[N];
inline void solve(){
	for(int i=1;i<=n;i++)mp[i].clear(),as[i].clear(),son[i]=0,ans[i]=0;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],as[a[i]].push_back(i);
	for(int i=1;i<n;i++){
		int x,y;cin>>x>>y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	dfs1(1,0);dfs2(1,1);
	for(int i=2;i<=n;i++){
		if(a[i]==a[fa[i]])ans[a[i]]=1;
	}
	for(int i=1;i<=n;i++){
		if(ans[i])continue;
		for(auto v:as[i]){
			if(ans[i])break;
			for(auto u:as[i]){
				if(v==u)continue;
				if(ans[i])break;
				if(det[u]+det[v]-2*det[lca(u,v)]==2)ans[i]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i];
	cout<<'\n';
}
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
/*
1
13
1 4 4 7 4 7 1 1 7 11 11 11 11
1 2
2 3
3 4
4 5
4 6
2 7
7 8
2 9
6 10
5 11
11 12
10 13
*/
```

---

## 作者：Programming_Konjac (赞：1)

博客正在撰写中。

更新在：[这个 CSDN 账号上](https://blog.csdn.net/ainiyoung?type=blog)。
# 思路
1. 如果存在两个相邻的相同值节点（路径长度为 $2$），则该路径满足条件。

2. 若无相邻相同节点，检查是否存在两个相同值的节点通过一个节点连接。此时可形成长度为 $3$ 的路径 $u-w-v$，其中 $u=v=k$，且 $k$ 出现两次，$u,w$ 不同，超过半数，所以 $u-w-v$ 也是一条满足要求的路径。
## 证明：
任何满足多数条件的路径必是以下一种结构：
  - 相邻的相同值节点，因为两个节点是一个值，是非平凡的简单路径，并且 $2>\lfloor\frac{2}{2}\rfloor$（相同数字个数为 $2$，路径长度为 $2$）。
  - 两个相同值节点通过一个公共邻居连接，因为有两个节点是一个值，是非平凡的简单路径，并且 $2>\lfloor\frac{3}{2}\rfloor$（相同数字个数为 $2$，路径长度为 $3$）。
  
因为是非平凡的简单路径，所以说选中的节点编号为 $1$ 到 $m-1$ 是没有重复元素的，并且后面的“多数”的定义中要满足 $x>\lfloor\frac{n(n\ge 2)}{2}\rfloor$，因为重复元素最多 $2$ 个，所以 $x=2$，所以说，要满足 $2>\lfloor\frac{n(n\ge 2)}{2}\rfloor$，解得 $n=2$ 或 $3$，路径长度只能是 $2$ 或 $3$。
# 赛时代码
[提交记录](https://codeforces.com/contest/2065/submission/305310908)。

---

## 作者：wflhx2011 (赞：0)

结论题。

看完题目觉得十分困难，难道是树剖？但这是 Div.4，不会太困难，直接大胆猜测：对于一条路径不需要全部遍历，只需要找一部分。

那要找的长度到底是多少？考虑一条合法的路径的性质。

用 $1$ 表示多数元素，$0$ 表示非多数元素，因为 $1$ 出现了总数的一半以上，所以有很大概率会有 $2$ 个甚至更多的 $1$ 在一起，最差情况也会是 $1$ 和 $0$ 交替出现。换而言之，合法路径必然包含 $1,1$ 或 $1,0,1$ 类型的子序列。

设路径长度为 $n$，更详细的说：

若 $n$ 为奇数（这部分来源于官解），设其中有 $k$ 个 $1$，$n-k$ 个 $0$，已知 $k>n-k$，那么 $2k>n$，若不包含 $1,1$，那么每个 $1$ 之间都需要 $0$，所以 $n-k\ge k-1$，可得 $2k \le n+1$。综合可得 $n<2k \le n+1$，则 $k$ 唯一取值为 $\frac{n+1}{2}$，此时路径为 $1,0,1,0...$，包含 $1,0,1$。

若 $n$ 为偶数，则 $1$ 出现至少 $n\div 2+1$ 次，但不重叠的长度为 $2$ 的段只有 $n\div 2$ 个，根据抽屉原理，必然有至少一段出现 $2$ 个 $1$，也就是出现 $1,1$。

综上，可以得到一个一般结论：若存在一条多数元素为 $i$ 的路径，则必然存在两个相邻节点的数都为 $i$，或一条长度为 $3$ 的路径，其两端的数为 $i$。

然后就可以枚举着找了，判断数字可以用 map，具体可以看官解或别的题解，这里不放代码了。

---

## 作者：yvbf (赞：0)

![](bilibili:BV1eiNhe7EZ9?t=2004)

---

## 作者：Double_Light (赞：0)

首先观察性质。定义一条路径的多数元素表示路径上所有点的点权按顺序排成序列的多数元素。

不难发现如果一条长为 $n$ 的存在多数元素的路径长度为偶数，则必然有两个相邻点，它们的点权都为多数元素 $k$。否则 $k$ 的个数不可能达到 $\dfrac{n}{2}+1$。同理，如果长度为奇数，则必然有三个相邻点，它们的点权中至少有两个为多数元素 $k$，否则 $k$ 的个数不可能达到 $\dfrac{n-1}{2}+1$。

因此我们可以得出一条重要结论：如果存在一条多数元素为 $k$ 的路径，则一定存在一条长度为 $2$ 或 $3$ 的多数元素为 $k$ 的路径。

最终我们只需要统计长度为 $2$ 或 $3$ 的多数元素为 $k$ 的路径。容易想到枚举一个端点 $u$，如果存在边 $(u,v)$，使得 $a_u=a_v$，则 $s_{a_u}=1$。这样就考虑完了长度为 $2$ 的情况。对于长度为 $3$ 的情况，考虑将所有 $a_v$ 值的出现次数记录下来，如果存在边 $(u,v_1),(u,v_2)$ 且 $a_{v_1}=a_{v_2}$，则 $s_{a_{v_1}}=1$。这里要额外注意，枚举完一个 $u$ 之后如果暴力清空记录所有 $a_v$ 值出现次数的数组可能会导致 TLE，所以建议开一个栈记录该数组的修改情况。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#define int long long
using namespace std;
int T,n;
struct EDGE{
	int u,v,nxt;
}edge[1000005];
int a[500005];
int head[500005],tot;
void add(int u,int v){
	edge[++tot]={u,v,head[u]};
	head[u]=tot;
}
int f[500005];
int st[500005],top;
int cnt[500005];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			head[i]=0;f[i]=0;
		}
		for(int i=1;i<=tot;i++)edge[i]={0,0,0};
		tot=0;
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			add(u,v);
			add(v,u);
		}
		for(int u=1;u<=n;u++){
			for(int i=head[u];i;i=edge[i].nxt){
				int v=edge[i].v;
				if(a[v]==a[u])f[a[u]]=1;
				st[++top]=a[v];
				if(cnt[a[v]])f[a[v]]=1;
				cnt[a[v]]++;
			}
			while(top){
				cnt[st[top]]--;
				top--;
			}
		}
		for(int i=1;i<=n;i++)cout<<f[i];cout<<endl;
	}
	return 0;
}
```

---

## 作者：EternalLabyrinth (赞：0)

### 题意：

给定一个 $n$ 个节点的树，点带权。对于每一个 $i(1\leq i \leq n)$，输出是否存在一条树上路径使得路径上的点权众数为 $i$。

### 解法：

首先经过简单的观察可以得出走长度 $>3$ 的的路径一定不优。所以如果你找到了一条长度 $>3$ 的路径权值众数为 $i$，那么你一定可以找到这条路径的一个长度小于等于 $3$ 的子路径使得其众数为 $i$。

于是题目类似于联合权值。考虑枚举三个点中的中间点。对于每个中间点开一个哈希表维护自己和儿子中 $i$ 的个数。如果个数大于等于 $2$。说明存在。

这样复杂度均摊下来显然是线性的，于是我们做完了。

---

## 作者：Lele_Programmer (赞：0)

# CF2065F 题解

## 思路

长度为 $k$，要使一个数 $i$ 成为 majority，则 $i$ 出现次数必须严格大于 $\lfloor\frac{k}{2}\rfloor$。

若 $k$ 为奇数，且 $i$ 是 majority，则 $i$ 出现的位置间隔最小为 $2$。比如，分别用零和一表示不是 $i$ 和 $i$，若 $k=3$，使相邻两个 $i$ 最远，得到 `101`，接着，若 $k=5$ 则 `10101`，依此类推。所以，对于任意两个 $i$，如果它们之间的距离小于等于 $2$，则该 $i$ 能够成为 majority。

若 $k$ 为偶数，尽量让 $i$ 离得远一些，填入 $\frac{k}{2}$ 个 $i$，可以使得每个 $i$ 右边隔一个位置，然而要严格大于，则需要再放 $1$ 个 $i$，最后这个不管怎么放，都一定会和另外一个 $i$ 相邻。所以，对于任意两个 $i$，如果它们相邻，则 $i$ 能够成为 majority。

综上所述，对于一个 $i$，只要存在距离小于等于 $2$ 的一对，则这个 $i$ 有解。

于是跑一遍深搜记录一下就行了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int N=500005;
const int M=1000005;

int T,n;
int a[N];
int e[M],ne[M],h[N],tot;
bool flag[N];

void add(int a,int b) {
    e[tot]=b,ne[tot]=h[a],h[a]=tot++;
}

void dfs(int u,int fa) {
    unordered_set<int> hs;
    if (fa) hs.emplace(a[fa]);
    hs.emplace(a[u]);
    _graph(i,u) {
        if (e[i]==fa) continue;
        dfs(e[i],u);
        if (hs.count(a[e[i]])) flag[a[e[i]]]=true;
        hs.emplace(a[e[i]]);
    }
}

int main() {
    read(T);
    while (T--) {
        read(n);
        _rep(i,1,n) read(a[i]),h[i]=-1,flag[i]=false;
        tot=0;
        _rep(i,1,n-1) {
            int a,b;
            read(a),read(b);
            add(a,b),add(b,a);
        }
        dfs(1,0);
        _rep(i,1,n) write((int)flag[i]);
        putchar(10);
    }
    return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

容易发现相同数字相邻时这个数字一定正确，此时的序列为 $[x,x]$。

容易发现一个点连向的数字中有相同数字一定也正确，此时的序列为 $[x,y,x]$。

其他情况我们可以不用判断。

证明：

如果要 Hack 上面的那个做法，就需要构造出一个序列，使得其中的多数元素（定义引用的题面）不相邻且不存在一个元素左右两边都与多数元素相邻。

贪心的构造，我们一旦可以放多数元素就放多数元素，那么会发现构造出来的最优序列是这样的 $[x,y,z,x,y,z,x,\dots]$，其中 $x$ 是原本意向中的多数元素。

那么这个 $x$ 的数量只占全数列的 $\frac{1}{3}$ 左右，不符合题意。

所以如果 $x$ 在一个序列中不相邻且不存在一个元素左右两边都与 $x$ 相邻，那么 $x$ 就不是该序列的多数元素。

而如果该序列确实存在这种情况，那么我们也不用在这里进行判断。

所以上面的结论是对的。

深搜就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005];
vector<int>ve[500005];
bool ans[500005];
bool cmp(int x,int y){
    return a[x]<a[y];
}
void dfs(int x,int fa){
    sort(ve[x].begin(),ve[x].end(),cmp);
    for(int i=0;i<ve[x].size();i++){
        if(ve[x][i]!=fa)
        dfs(ve[x][i],x);
    }
    for(int i=1;i<ve[x].size();i++)
        if(a[ve[x][i]]==a[ve[x][i-1]]||a[ve[x][i-1]]==a[x])ans[a[ve[x][i-1]]]=1;
        else if(a[ve[x][i]]==a[x])ans[a[ve[x][i]]]=1;
    if(a[ve[x][0]]==a[x])ans[a[ve[x][0]]]=1;
}
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i],ans[i]=0,ve[i].clear();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)cout<<ans[i];
    cout<<endl;
}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

谁赛时没写完我不说。

---

