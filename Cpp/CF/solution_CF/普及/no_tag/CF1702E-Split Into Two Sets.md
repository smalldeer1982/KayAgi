# Split Into Two Sets

## 题目描述

Polycarp was recently given a set of $ n $ (number $ n $ — even) dominoes. Each domino contains two integers from $ 1 $ to $ n $ .

Can he divide all the dominoes into two sets so that all the numbers on the dominoes of each set are different? Each domino must go into exactly one of the two sets.

For example, if he has $ 4 $ dominoes: $ \{1, 4\} $ , $ \{1, 3\} $ , $ \{3, 2\} $ and $ \{4, 2\} $ , then Polycarp will be able to divide them into two sets in the required way. The first set can include the first and third dominoes ( $ \{1, 4\} $ and $ \{3, 2\} $ ), and the second set — the second and fourth ones ( $ \{1, 3\} $ and $ \{4, 2\} $ ).

## 说明/提示

In the first test case, the dominoes can be divided as follows:

- First set of dominoes: $ [\{1, 2\}, \{4, 3\}] $
- Second set of dominoes: $ [\{2, 1\}, \{3, 4\}] $

 In other words, in the first set we take dominoes with numbers $ 1 $ and $ 2 $ , and in the second set we take dominoes with numbers $ 3 $ and $ 4 $ .In the second test case, there's no way to divide dominoes into $ 2 $ sets, at least one of them will contain repeated number.

## 样例 #1

### 输入

```
6
4
1 2
4 3
2 1
3 4
6
1 2
4 5
1 3
4 6
2 3
5 6
2
1 1
2 2
2
1 2
2 1
8
2 1
1 2
4 3
4 3
5 6
5 7
8 6
7 8
8
1 2
2 1
4 3
5 3
5 4
6 7
8 6
7 8```

### 输出

```
YES
NO
NO
YES
YES
NO```

# 题解

## 作者：tzyt (赞：19)

题目链接[（CF](https://codeforces.com/problemset/problem/1702/E)，[洛谷）](https://www.luogu.com.cn/problem/CF1702E) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1702/)中观看。
## 题意
给你 $n$ （$n$ 为偶数，$2 \le 2 \cdot 10^5$）个，数对。数对中的每个数字都是从 $1$ 到 $n$ 的。

现在问你是否能将这些数对分到两个集合中。使得每个集合中没有任何一个重复的数字。

比如有下面这四个数对：$\{1, 4\}, \{1, 3\}, \{3, 2\}, \{4, 2\}$。

那么可以这样分配这些数对：
- 第一个集合包含数对 $\{1, 4\}$ 和 $\{3, 2\}$。第二个包含 $\{1, 3\}$ 和 $\{4, 2\}$。

## 思路
看起来是个贪心，能放一个集合的就放，不能就放另一个，另一个还不行就输出 $\texttt{NO}$ ，但毕竟是个 E 题，所以没那么简单。（~~别学我直接交了个贪心上去，还半天都想不明白为什么错~~）。

要证明这个贪心是错的，只需要举一个反例，顺便吐槽一下，这个题的样例还是挺坑的，你用贪心完全能过。

比如给你下面这样一个数据：
```
6
1 2    
5 4
2 3 
4 3  
5 6
6 1
```

如果我们用贪心做，设第一个集合为 $A$，第二个为 $B$，就可以把前两个，也就是 $\{1, 2\}$ 和 $\{5, 4\}$ 放到 $A$ 中。到第三个，就会发现 $\{2, 3\}$ 中的 $2$ 和 $\{1, 2\}$ 的 $2$ 重复了，于是放到 $B$ 中。

而对于第四个数对 $\{4, 3\}$ ，可以发现不管放到哪里都有重复的。

然而，这个数据是可以合法的分到两个集合的：

$$
A: \{1, 2\} \ \{4, 3\} \ \{5, 6\} \\
B: \{2, 3\} \ \{5, 4\} \ \{6, 1\}
$$


我们可以把数对拆称每个数字来看。

从 $1$ 开始，所有数对中，包含 $1$ 的有两个：$\{1, 2\}$ 和 $\{6, 1\}$。那么我们知道，因为两个数对都有 $1$，所以肯定不能放到一个集合里。

按照相同的方式来看 $2$。包含 $2$ 的数对有两个：$\{2, 3\}$ 和 $\{1, 2\}$。所以这两个也一定在不同的集合中。

按照这样的方法从 $1$ 到 $n$ 的列出包含这些数字的集合，可以得到：

$$
1 \to \{1, 2\} \ \{6, 1\}\\
2 \to \{2, 3\} \ \{1, 2\}\\
3 \to \{2, 3\} \ \{4, 3\}\\
4 \to \{4, 3\} \ \{5, 4\}\\
5 \to \{5, 4\} \ \{5, 6\}\\
6 \to \{5, 6\} \ \{6, 1\}
$$

然后我们检查这些条件，发现似乎没有矛盾的，并且你可以根据这些条件得到我之前给出的分配方法。

这样一看，告诉你两个东西在不同的集合中，并且让你判断这些规则是否能满足，那不就是一种带逻辑关系的并查集吗？ 

如果你不熟悉，可以去看看这些题目：
- [洛谷P1892 [BOI2003]团伙](https://www.luogu.com.cn/problem/P1892)
- [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)

的确，这个题是可以用带逻辑关系的并查集来做的，tourist 就是[这么做的](https://codeforces.com/contest/1702/challenge/163478635)。

不过，我们还可以从图论的角度来思考。

如果我们给一个数对中的两个数字连上一条边，就可以得到下面这样的图：

```
1 <--> 2 <--> 3
|             |
6 <--> 5 <--> 4
```

可以发现，因为和之前一样的原因，对于一个数字，比如 $2$。我们不可能把包含 $2$ 的两个数对，也就是 $\{2, 3\}$ 和 $\{1, 2\}$，放到一个集合里。

也就是说可以从边的角度思考，$2$ 这个节点连了两个边，而我们不能同时选 $2$ 的两条边放到一个集合里。

那么唯一能满足这个要求的办法就是交替的把边分配到集合中。

比如：

```
1 <--> 2 <==> 3    or     1 <==> 2 <--> 3 
||            |   <--->   |             ||
6 <==> 5 <--> 4           6 <--> 5 <==> 4
```

其中 `<-->` 这样的边和 `<==>` 这样的边代表边上的两个节点会被放到不同的集合中。

接下来我们可以分类讨论一下，不同的图是否能满足要求。

首先，如果一个节点连了三个及以上的边，那么一定是不能满足交替放入不同集合中的。

比如：

```
    A 
   /|\
  / | \
 B  C  D
```

因为如果要把这三条边放入两个集合中, $A$ 会不可避免的出现了两次。

其次，如果图中只有一个链，那么交替的放入不同集合中是一定能满足的。

最后，如果图是一个环，并且有偶数的边（就像上面那样），那是一定可以满足交替出现的要求的。而奇数就不行了。

判断环奇偶的办法其实比较直观，我们给每个边设置一个颜色的属性，共有两种颜色，然后用 dfs 去遍历一遍这个环。

遍历时尝试给边交错的染上颜色，如果我们不能成功的交错染色，那一定是奇环，反之亦然。（如果能交错的染色，那么两种颜色的数量一定是相等的，因此一定是偶环）。

还有一点在具体实现时需要注意，我们建出来的图不一定是联通的，所以需要尝试对每一个节点 dfs，同时，之间按照输入建图可能有重边，而我们需要避免。

## 代码
整体来说，代码还是比较简洁的。

```cpp
// author: ttzytt (ttzytt.com)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct E {
    int to, color;
};

const int MAXN = 2e5 + 10;

vector<E> e[MAXN];
set<int> have_e[MAXN];

bool iseven_cycle(int cur, int fa, bool cur_color) {
    if (e[cur].size() < 2) return true;
    // 小优化，size 小于 2 说明是一个链的终点。
    // 那么一个链是一定可以交错的染色的，这时候直接返回 true
    for (E &nex : e[cur]) {
        if (nex.to == fa) continue;
        if (nex.color == -1) // -1 是初始值，所以直接给它染和当前边不同的颜色
            nex.color = !cur_color;
        else if (nex.color == cur_color)// 如果发现下一个边和当前边同色，那肯定是不能成功染色的
            return false;
        else if (nex.color == !cur_color)// 有颜色了，但是是我们想染的。
            return true;
        if (!iseven_cycle(nex.to, cur, !cur_color)) return false;
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for_each(e + 1, e + 1 + n, [](vector<E> &a) { a.clear(); });
        for_each(have_e + 1, have_e + 1 + n, [](set<int> &a) { a.clear(); });
        // 每次清空一下数据。

        bool isable = true;
        map<int, int> bkt; // 记录每个节点的度，如果大于 2 那一定不行（原因如上文）
        for (int i = 1; i <= n; i++) {
            int x, y;
            cin >> x >> y;
            bkt[x]++, bkt[y]++;
        
            if (bkt[x] > 2 || bkt[y] > 2 || x == y) isable = false; // 发现度大于 2
        
            if (!have_e[x].count(y)) { //用于避免重边
                e[x].push_back({y, -1});
                have_e[x].insert(y);
            }
            if (!have_e[y].count(x)) {
                e[y].push_back({x, -1});
                have_e[y].insert(x);
            }
        }
        for (int i = 1; i <= n && isable; i++) {
            if (e[i][0].color == -1) 
                isable = iseven_cycle(i, 0, 1); 
                // 建出来的图不一定联通，所以尝试对每个节点 dfs   
        }
        if (isable)
            cout << "yes\n";
        else
            cout << "no\n";
    }
}
```
最后，希望这篇题解对你有帮助，如果有问题可以通过评论区或者私信联系我。

---

## 作者：8atemak1r (赞：11)

~~赛时差了几秒没交上去气的我连夜把题解写了~~

## Description

有 $n$ 张多米诺骨牌（$n$ 保证为偶数），每张上面有两个属于 $[1,n]$  的数字，问能否将这 $n$ 张多米诺骨牌分成数量相同的两组且每组内牌上的数字互不相同。

## Solution

首先有一个明显的结论：如果一个数字的出现次数不等于 $2$ 次，那么是不可以完成分组的，这个结论可以在最开始判断是否可行。

接下来就是重点了，如果两个数字在一张牌上，将这两个数字之间连一条边，于是可以得到形如这样的几个联通块：

[![jgbQNq.md.jpg](https://s1.ax1x.com/2022/07/12/jgbQNq.md.jpg)](https://imgtu.com/i/jgbQNq)

显然通过最开始的判断，我们构造的图中任意一个点的度数都等于 $2$，即每个联通块必定是环的形式。将分组的操作看做给边打上 $l$ 或者 $r$ 的标记，以表示分到了第一个组或第二组，那么要满足题意，则与任意一个点任意一个点相连的两条边的标记一定不一样，再考虑到环的限制，显然只要存在点数（边数）为奇数的环就不能完成分组，否则可以。

这样，这道题就转化成了一道找奇环的题目，这里我用的是并查集来维护。

## Code

```cpp
#include<iostream>
#include<set>
using namespace std;
const int maxn = 200005;
int t, n, ans;
int fa[maxn];
set<int> f;
set<int> :: iterator it;
int find(int k) {
    if(fa[k] == k) return k;
    return fa[k] = find(fa[k]);
}
int vis[maxn], to[maxn];
int main() {
    cin >> t;
    while(t --) {
        cin >> n; ans = 1;
        for(int i = 1; i <= n; ++ i) fa[i] = i;
        for(int i = 1, a, b; i <= n; ++ i) {
            cin >> a >> b; ++ vis[a]; ++ vis[b];
            fa[find(a)] = find(b);
        }
        for(int i = 1; i <= n; ++ i) 
            if(vis[i] != 2) ans = 0;
        for(int i = 1; i <= n; ++ i) {
            int fi = find(i);
            if(f.count(fi) == 0) f.insert(fi);
            ++ to[fi];
        }
        for(it = f.begin(); it != f.end(); ++ it) if(to[*it] & 1) ans = 0;
        cout << (ans ? "YES\n" : "NO\n");
        for(it = f.begin(); it != f.end(); ++ it) to[*it] = 0;
        for(int i = 1; i <= n; ++ i) vis[i] = 0;
        f.clear();
    }
    return 0;
}
```

---
PS. 感谢 @[胖娃儿二号](https://www.luogu.com.cn/user/263576) 提供的帮助

---

## 作者：Wonder_Fish (赞：4)

## 题意

$t$组数据（$1 \le t \le 10^{4} $），每组数据给一个偶数 $n$（$2 \le n \le 2 \cdot 10^{5}$），有 $n$ 个多米诺骨牌 ，每块多米诺骨牌包含两个整数 $a_{i}$ 和 $b_{i}$ （$1 \le a_{i},b_{i} \le n$），要求把这 $n$ 块多米诺骨牌分入两个集合使得每个集合中的数互不相同，每个多米诺骨牌都必须被分入一个集合。

## 解题思路

由题意得每个集合中有 $n$ 个数，每个数互不相同且都在 $1$ 和 $n$ 之间，所以 $1$ 到 $n$ 之间的每个数都会在每个集合中出现且只出现一次，因此总共的 $2 \cdot n$ 个数中，$1$ 到 $n$ 都出现两次，所以如果有同一个数出现的次数不等于 $2$ 的数据，就可以直接输出 `NO` 。 

有题目可以得到一个显然的结论：如果有两块多米诺骨牌都包含同一个数，那它们一定不在同一个集合中。

有这样的关系，还有这题两个集合，就很容易想到[二分图](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E5%9B%BE/9089095?fr=aladdin)。

可以把多米诺骨牌的编号作为节点编号，由于每个数出现两次，所以对于包含同一个数的第 $i$ 块和第 $j$ 块多米诺骨牌（$1 \le i,j \le n$ 且 $i \neq j$），在编号为 $i$ 的节点和编号为 $j$ 的节点之间连双向边。很明显相邻的两个点不会分到同一个集合中。

建好图后就可以用染色法跑一遍二分图判定。具体来说就是用黑白两种颜色标记图中的点，如果一个点被标记了，那它周围的点都要被标记上相反的颜色（在此题中就表示分到另一个集合）。如果染色过程中出现矛盾，就说明无法按照题目要求分成两个集合，所以输出 `NO` ，反之输出 `YES` 。此题解用 bfs 实现。

## Code

```cpp
#include<bits/stdc++.h>
#define maxn 200010
#define pii pair<int,int>
#define fi first
#define sc second
using namespace std;
int T,n,c[maxn],flag; pii a[maxn];
vector<int> g[maxn],p[maxn];
bool check(){ //二分图判定（染色法）
	queue<int> q;
	memset(c,0,sizeof(c)); //初始时都没有颜色
	for(int i=1;i<=n;i++){
		if(!c[i]){ //如果没有被染过色
			q.push(i); c[i]=1; //放入队列，先染上颜色1
			while(!q.empty()){ //bfs枚举相邻的点
				int x=q.front(); q.pop();
				for(int j=0;j<g[x].size();++j){
					int y=g[x][j];
					if(!c[y]){ //没染过色
						q.push(y);
						if(c[x]==1) c[y]=2;
						else c[y]=1; //染上相反的颜色并放入队列
					}
					else if(c[y]==c[x]) return false; //出现矛盾，不是二分图
				}
			}
		}
	}
	return true;//染色成功，是二分图
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n); flag=0;
		for(int i=1;i<=n;++i){
			g[i].clear(); p[i].clear(); //多测不清空，爆零两行泪
		}
		for(int i=1;i<=n;++i){
			scanf("%d%d",&a[i].fi,&a[i].sc);
			p[a[i].fi].push_back(i);
			p[a[i].sc].push_back(i); //p[i]表示包含i的多米诺骨牌的编号
		}
		for(int i=1;i<=n;++i)
			if(p[i].size()!=2) flag=1; //判定是否所有数都出现2次
		if(flag){
			puts("NO"); continue;
		}
		for(int i=1;i<=n;++i){
			g[p[i][0]].push_back(p[i][1]);
			g[p[i][1]].push_back(p[i][0]); //建图
		}
		if(check()) puts("YES"); //二分图判定
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 1600}$
---
谨以此篇题解，纪念我掉到 $\text{1680}$ 的 $\text{rating}$。

---
### 解题思路：

考虑将所有的不能放到一起的多米诺骨牌之间连上一条边，然后将整个图分成一个二分图就行了。

注意到这种方法可能会被有较多同样数字的多米诺骨牌的情况卡到 $O(n^2)$ 条边，于是想到如果出现有三个或者更多的相同数字的情况时直接判断无解，正确性显然。

总复杂度 $O(n)$。

---
### 代码：

```
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2000005;
int T,a[MAXN],b[MAXN],v[MAXN],flag,head[MAXN],num[MAXN*3],nxt[MAXN*3],tot,n,vis[MAXN];
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void work(int num,int p){
	if(v[num]==-1){flag=1;return;}
	if(v[num]==0){v[num]=p;return;}
	add(v[num],p);
	add(p,v[num]);
	v[num]=-1;
}
void dfs(int now,int p){
	vis[now]=p;
	for(int i=head[now];i;i=nxt[i]){
		if(vis[num[i]]==p)flag=1;
		if(vis[num[i]]==0)dfs(num[i],3-p);
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		head[i]=0,v[i]=0,vis[i]=0;
		for(int i=1;i<=tot;i++)
		num[i]=nxt[i]=0;
		tot=0;flag=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i],&b[i]);
			work(a[i],i);work(b[i],i);
			if(a[i]==b[i])flag=1;
		}
		for(int i=1;i<=n;i++)
		if(v[i]!=-1)flag=1;
		for(int i=1;i<=n;i++)
		if(vis[i]==0)dfs(i,1);
		if(flag==1)printf("NO\n");
		if(flag==0)printf("YES\n");
	}
	return 0;
}
```


---

## 作者：EXODUS (赞：2)

# Part 1：前言
来篇更容易理解的 `2-SAT` 题解。

场上十几分钟码了个 `2-SAT`，考完看见官方题解是二分图染色判奇环，心里立刻麻了。

还好没有被 hack。 /kk

# Part 2：正文
首先读题，很容易想到，对于任意一个数字，若出现次数超过 $3$ 次，一定不合法（抽屉原理）。

那么在判掉这种情况后，每个数字都会恰好出现 $2$ 次，且上面有这种数字的两块骨牌一定分属于不同集合。

那不就直接裸 `2-SAT` 了吗。

建模，如果两块骨牌 $i$ 和 $j$ 上出现相同数字，则有 $i=0\vee j=0,\ i=1\vee j=1$，其中 $i=0$ 表示骨牌 $i$ 属于第一个集合， $i=1$ 表示骨牌 $i$ 属于第二个集合。

跑 `2-SAT` 判断可行性即可，时间复杂度 $O(\sum n)$。


# Part 3：代码
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define np pair<int,int>
using namespace std;
int n,m,t;
const int MAXN=4e5+7;
struct Edge{
	int to,next;
}e[MAXN<<1];
int tot;
int head[MAXN];
np app[MAXN];

void add_edge(int u,int v){
	e[++tot].to=v;
	e[tot].next=head[u];
	head[u]=tot;
}

int sta[MAXN],type[MAXN];
bool insta[MAXN];
int dfn[MAXN],low[MAXN];
int a[MAXN],b[MAXN];
int cnt;
int top;
int tmp;

void tarjan(int x){
	dfn[x]=low[x]=++cnt;
	insta[x]=1;
	sta[++top]=x;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(insta[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		tmp++;
		do{
			type[sta[top]]=tmp;
			insta[sta[top]]=0;
			top--;
		}while(x!=sta[top+1]);
	}
	return;
}
int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
int main(){
	t=read();
	while(t--){
		tot=0;cnt=0,top=0,tmp=0;bool flag=0;
		n=read();
		for(int i=1;i<=2*n;i++){
			head[i]=0;low[i]=0,dfn[i]=0;insta[i]=0;
			app[i].fi=app[i].se=0;
		}
		for(int i=1;i<=n;i++){
			a[i]=read(),b[i]=read();
			if(!app[a[i]].fi)app[a[i]].fi=i;
			else if(!app[a[i]].se)app[a[i]].se=i;
			else flag=1;
			if(!app[b[i]].fi)app[b[i]].fi=i;
			else if(!app[b[i]].se)app[b[i]].se=i;
			else flag=1;
		}
		if(flag){
			puts("NO");
			continue;
		}else{
			for(int i=1;i<=n;i++){
				add_edge(app[i].fi+n,app[i].se);
				add_edge(app[i].se+n,app[i].fi);
				add_edge(app[i].fi,app[i].se+n);
				add_edge(app[i].se,app[i].fi+n);
			}
			//for(int i=1;i<=tot;i++){
			//	printf("%d %d\n",e[i].to,e[i].next);
			//}
			for(int i=1;i<=(n<<1);i++){
				if(!dfn[i]){
					tarjan(i);
				}
			}
			for(int i=1;i<=n;i++){
				//cout<<type[i]<<" "<<type[i+n]<<endl;
				if(type[i]==type[i+n]){
					puts("NO");
					goto there;
				}
			}
			puts("YES");
			there:;
		}
	}
	return 0;
}


```
# Part 4：后文
点赞再走呗（逃~

---

## 作者：Daidly (赞：1)

直接贪心模拟是错的，题解中一位同学也给出了反例。

考虑什么情况一定不行：

- 同一个数对中 $a=b$；

- 一个数的出现次数超过 $2$ 次。

以上情况直接输出 `NO`。

然后可以发现对于任意一个数其在所有数对中出现次数不超过 $2$ 次，且有矛盾关系。

考虑用并查集维护，建立二倍数组。定义 $i$ 与 $i+n$ 始终为敌人，将相同的数出现的不同数对编号作为敌人合并。也就是说，若 $x$ 出现在第 $i,j$ 数对中，则合并 $(i,j+n),(j,i+n)$ 作为朋友。不会的可以看 [P1892 [BOI2003]团伙](https://www.luogu.com.cn/problem/P1892) 和 [P1525 [NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)。

观察到，当 $i,i+n$ 被作为朋友合并到一起时，产生矛盾，即不可能完成。

我这里使用了路径压缩与按秩合并。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

const int MAXN=2e5+5;
int T,n,t[MAXN],a[MAXN],b[MAXN],f[MAXN<<1],p[MAXN][2],siz[MAXN<<1];

int find(int x){
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	if(siz[fx]>siz[fy])f[fy]=fx,siz[fx]+=siz[fy];
	else f[fx]=fy,siz[fy]+=siz[fx];
}

int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;++i)p[i][0]=p[i][1]=t[i]=0,f[i]=i,f[i+n]=i+n,siz[i]=siz[i+n]=1;
		bool flag=1;
		for(int i=1;i<=n;++i){
			a[i]=read(),b[i]=read();
			if(a[i]==b[i])flag=0;
			t[a[i]]++,t[b[i]]++;
			if(t[a[i]]>2||t[b[i]]>2)flag=0;
			if(p[a[i]][0])p[a[i]][1]=i;
			else p[a[i]][0]=i;
			if(p[b[i]][0])p[b[i]][1]=i;
			else p[b[i]][0]=i;
		}
		if(!flag){puts("NO");continue;}
		for(int i=1;i<=n;++i){
			if(!t[p[i][1]])continue;
			int x=p[i][0],y=p[i][1];
			merge(x+n,y);
			merge(x,y+n);
			if(find(x)==find(x+n)){
				flag=0;break;
			}
			if(find(y)==find(y+n)){
				flag=0;break;
			}
		}
		if(flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：baiABC (赞：1)

首先，可以排除一些显然无解的情况：若某个数在所有数对中出现次数大于 $2$，则无解。

否则，设 $l_i$ 为数 $i$ 第一次出现的数对的编号， $r_i$ 为数 $i$ 第二次出现的数对的编号，则由题意，数对 $l_i$、$r_i$ 不在同一集合中。

设两集合编号为 $0$、$1$，则原问题转化为：已知 $n$ 个变量（每个变量取 $0$ 或 $1$）和一些不等关系，求这些关系是否能全部满足。

这其实是经典问题，可以用种类并查集或带权并查集解决（[洛谷原题 P5937](https://www.luogu.com.cn/problem/P5937) ~~啊 CF 出原题~~）。

种类并查集代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, fa[400010]; // 种类并查集空间开 2 倍
vector <int> P[200010];
int fnd(int k){return k==fa[k]?k:fa[k]=fnd(fa[k]);}
int main()
{
   ios::sync_with_stdio(0); int T;
   cin >> T;
   for(int i = 0; i < T; ++i)
   {
      cin >> n;
      for(int i = 1; i <= n; ++i) P[i].clear();
      for(int i = 1; i <= n; ++i)
      {
         int a, b; cin >> a >> b;
         P[a].push_back(i);
         P[b].push_back(i);
      }
      bool ok = true;
      for(int i = 1; i <= n; ++i)
         if(P[i].size() > 2)
         {// 排除显然无解的情况
            ok = false;
            break;
         }
      if(!ok) {cout<<"NO"<<'\n'; continue;}
      for(int i = 1; i <= n*2; ++i) fa[i] = i;
      for(int i = 1; i <= n; ++i)
      {
         int u = fnd(P[i][0]), v = fnd(P[i][1]);
         if(u == v)
         {
            ok = false;
            continue;
         }
         fa[fnd(P[i][0]+n)] = v;
         fa[fnd(P[i][1]+n)] = u;
      }
      cout << (ok?"YES":"NO") << '\n';
   }
   return 0;
}
```

---

## 作者：辰云 (赞：1)

题意可以转化为：将每一个多米诺骨牌看作一个结点，将具有相同数字的骨牌之间连一条边，判断这个图是否是二分图。

本题中，图的边数较大，直接dfs二分图染色可能会超时。

这里采用了类似[关押罪犯](https://www.luogu.com.cn/problem/P1525)这题的方式，用扩展域并查集来判定二分图。

每加入由一条边连接的一对新的结点，如果这两个结点已经属于一个同一个集合内，则与二分图每条边的两个结点属于不同集合的性质冲突，此图不为二分图。否则将两个结点插入到不属于对方集合的集合，即：

```cpp
f[find(x+n)]=find(y);
f[find(y+n)]=find(x);
```

其中 $x+n$ 结点表示 $x$ 结点所在的边连接的另一边的端点。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN=2e5+5;
int f[MAXN<<1];
vector<int> ve[MAXN];

struct jjy{
	int x,y;
}a[MAXN];

int find(int x){return f[x]==x ? x : f[x]=find(f[x]);}

int main(){
	int t=read();
	while(t--){
		int n=read();
		for(int i=1;i<=n;i++)ve[i].clear();
		for(int i=1;i<=n;i++)f[i]=i,f[i+n]=i+n;
		for(int i=1;i<=n;i++){
			a[i].x=read(),a[i].y=read();
			ve[a[i].x].push_back(i);
			ve[a[i].y].push_back(i);
		}
		int ok=0;
		for(int i=1;i<=n;i++)//显然，有三个以上骨牌的数字相同时，一定不能划分为数字不同的两堆。
			if(ve[i].size()>=3){ok=1;break;}
		for(int i=1;i<=n;i++){
			if(ve[i].size()<2)continue; 
			if(find(ve[i][0])==find(ve[i][1])||find(ve[i][1]+n)==find(ve[i][0]+n)){ok=1;break;}
			f[find(ve[i][0]+n)]=find(ve[i][1]);
			f[find(ve[i][1]+n)]=find(ve[i][0]);
		}
		if(ok)printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}

```


---

## 作者：qwq___qaq (赞：1)

首先，一个数字出现二次以上是无解的（显然）。

所以，我们记录一个数字出现的两个骨牌 $(x,y)$（如果没有就不管），那么 $x$ 和 $y$ 不能再同一个集合中，我们此时在 $(x,y)$ 连上一条边。

然后，我们要将骨牌分为两个集合，两个集合之内没有数共存。

也就是说，两个集合之内没有边。

于是，满足的条件为：原图是个二分图。

判定一下即可，时间复杂度 $O(n)$。

---

## 作者：yeshubo_qwq (赞：1)

## Description

有 $n$ 张牌，每张牌上有两个数，要求将 $n$ 张牌分成两组，使得每组牌上的数没有重复，问是否存在一种可行的方案。

## Solution

首先考虑明显无解的情况：

- 一张牌上的两个数相同。

- 一个数出现三次及以上。

然后进行分组：

如果一张牌上的数为 $x$ 和 $y$ 且分到了第一组，那么另一张有 $x$ 的和另一张有 $y$ 的牌就必须分到第二组。 

以此进行搜索，最后根据第一组和第二组牌的数量进行判断即可。

注意：要以每张牌进行一次搜索，防止有牌没有做到。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node{int x,y;}b[200005];
int a[200005][2],cnt[2],n,flag,x,y,v[200005],i;
void dfs(int x,int s){
	int z;
	if (v[x]==1) {return;}//搜过了 
	v[x]=1;cnt[s]++;
	if (a[b[x].x][0]!=x) z=a[b[x].x][0]; else z=a[b[x].x][1];
	dfs(z,s^1);
	if (a[b[x].y][0]!=x) z=a[b[x].y][0]; else z=a[b[x].y][1];
	dfs(z,s^1);
}
void solve(){
	cin>>n;
	flag=1;
	cnt[0]=cnt[1]=0;
	for (i=1;i<=n;i++) a[i][0]=a[i][1]=0,v[i]=0;
	for (i=1;i<=n;i++){
		cin>>x>>y;
		if (a[x][0]==0) a[x][0]=i;
		else if (a[x][1]==0) a[x][1]=i;//记录值为 x 的牌，方便搜索 
		else flag=0;//一个数出现三次及以上
		if (a[y][0]==0) a[y][0]=i;
		else if (a[y][1]==0) a[y][1]=i;//同上
		else flag=0;
		b[i].x=x,b[i].y=y;
		if (x==y) flag=0;//一张牌上的两个数相同 
	}
	if (!flag) {cout<<"NO\n";return;}
	for (i=1;i<=n;i++) dfs(i,0);//每张牌搜一次
	if (cnt[0]==cnt[1]) cout<<"YES\n";
	else cout<<"NO\n";
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int tests=1;
	cin>>tests;
	while (tests--)
		solve();
	return 0;
}
```


---

## 作者：hcywoi (赞：0)

#### 题目大意
给我们一些多米诺骨牌，然后让我们把这些多米诺骨牌分成两组，使得这两组多米诺骨牌上的数都不重复。

****

#### 解题思路

如果不满足每个数都出现两次，就说明无解。

如果一个多米诺骨牌上与另一个多米诺骨牌上有重复，那么就把这两个多米诺骨牌上的数连一条边。

连完边后，就判断是否有一种方案使得每一条边的两个端点都需要在两个不同的集合，也就等价于判定该图是否为二分图，如果是二分图就说明有解，否则无解。

#### Ac Code
```cpp
#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 200010, M = N * 4;

int n;
PII q[N];
int color[N];
int h[N], e[M], ne[M], idx;

void add(int a, int b)　// 从a->b连一条边
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool dfs(int u, int c) // 染色法判定二分图
{
	color[u] = c;

	for (int i = h[u]; ~i; i = ne[i])
	{
		int j = e[i];
		if (!color[j])　// 如果该点没有遍历过，就遍历j
		{
			if (!dfs(j, 3 - c)) return false;
		}
		else if (color[j] == c) return false;　// 出现矛盾
	}
	
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T -- )
	{
		scanf("%d", &n);
		unordered_map<int, int> a, b;
		unordered_map<int, int> cnt;
		for (int i = 1; i <= n; i ++ )
		{
			scanf("%d%d", &q[i].x, &q[i].y);
			cnt[q[i].x] ++, cnt[q[i].y] ++ ;
			if (!a.count(q[i].x)) a[q[i].x] = i;
			else b[q[i].x] = i;
			if (!a.count(q[i].y)) a[q[i].y] = i;
			else b[q[i].y] = i;
		}

		memset(h, -1, (n + 1) * 4);
		idx = 0;
		for (int i = 1; i <= n; i ++ ) // 建图
		{
			if (a[q[i].x] != i) add(i, a[q[i].x]);
			else add(i, b[q[i].x]);
			if (a[q[i].y] != i) add(i, a[q[i].y]);
			else add(i, b[q[i].y]);
		}

		bool success = true;
		memset(color, 0, (n + 1) * 4);
		for (int i = 1; i <= n; i ++ )
			if (!color[i])　// 如果当前点没有被遍历过，遍历一下
			{
				if (!dfs(i, 1))
				{
					success = false;
					break;
				}
			}
		for (auto [x, y] : cnt)　// 判断每个数出现的次数是否都等于2
			if (y != 2)
			{
				success = false;
				break;
			}
		puts(success ? "YES" : "NO");
	}

	return 0;
}
```

---

## 作者：codemap (赞：0)

#### 基本题意
- 给定 $n$（偶数）个二元集，每个元素属于 $[1,n]$
- 要求判断能否将这些二元集对半分成两组，使得每组中都没有两个相同的元素
- $ 2 \le n \le 2 \cdot 10^5 $

#### 题目分析
这道题有一个错误的思路是直接从前往后枚举进行贪心，既对于每一个二元集，两个都没有被放过的话放在第一组，否则进行判断再放，但这道题处理二元集的顺序对最终答案有影响，所以这个做法是错误的。

为了改变这个错误的做法，只需将这些二元集按序处理。

具体来说，我们在枚举时，如果当前这个二元集可以随便放，将其放在第一组。

否则的话，前往第二个元素的另外一个对应集合（显然为了有解，每个元素当且仅当出现两遍），然后对这个对应的集合进行放置。

像这样形成一条处理的链式结构，直到发现二元集的两个元素都被放置过时返回，然后前往下一个可以随便放置的二元集。

这里我使用了一个方法来区分一下两次出现的同一个元素，当一个元素 $x$ 第二次出现的时候，我将其标记为 $x+2 \cdot 10^5$，这样之后表示的时候会方便一些。

然后注意一下在有元素只出现了一次直接输出 NO 就可以了。


#### 代码

具体实现方面，我定义了五个数组，$a$ 数组和 $b$ 数组代表输入的二元集，$c$ 数组是计数数组，代表每个数出现的次数，可用来判断是否有明显的 NO，$d$ 数组记录每个数最终放在哪个组里，$e$ 数组记录每个数在二元集中的对应数。

我用了一个 while 循环来模拟 dfs，因为 dfs 的话可能会因为层数过多而爆栈。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,a[200001],b[200001],c[400001],d[400001],e[400001];
int oppo(int x)//计算本是同一个数的数现在是什么
{
    if(x<200000)
        return x+200000;
    return x-200000;
    //两个本是同样的数现在差2e5
}
int opp(int x)//两个可以放的组，一个为1一个为2
{
    if(x<2)
        return 2;
    return 1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t,p,i,side;
    bool f;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(i=1;i<=n;i++)
            cin>>a[i]>>b[i];
        f=0;
        memset(c,0,sizeof(c));
        memset(d,0,sizeof(d));
        for(i=1;i<=n;i++)
        {
            c[a[i]]++;
            c[b[i]]++;
            if(c[a[i]]==2)//第二次出现
            {
                c[a[i]]--;
                a[i]+=200000;
                c[a[i]]=1;//用多2e5的数来记录
            }
            if(c[b[i]]==2)
            {
                c[b[i]]--;
                b[i]+=200000;
                c[b[i]]=1;
            }
            e[a[i]]=b[i];//记录对应关系
            e[b[i]]=a[i];
        }
        for(i=1;i<=n;i++)
            if(c[i]!=1||c[i+200000]!=1)//明显错误
            {
                cout<<"NO\n";
                f=1;
                break;
            }
        if(f)
            continue;
        p=1;//p记录当前位置
        side=1;//side记录当前是哪一组
        while(1)
        {
            if(d[e[p]]==opp(side))//出现矛盾
            {
                cout<<"NO\n";
                f=1;
                break;
            }
            d[p]=side;//记录当前side
            if(!d[e[p]])//如果下一组没选过
            {
                d[e[p]]=side;
                p=oppo(e[p]);
                side=opp(side);
                continue;
            }
            bool f1=0;
            for(i=min(p,oppo(p));i<=n;i++)//这里可以直接从min(p,oppo(p))开始枚举的原因是前面的过程必然形成环，否则必有矛盾
                if(!d[i])//如果还没枚举过
                {
                    p=i;
                    side=1;
                    f1=1;
                    break;
                }
            if(f1)
                continue;
            break;//说明已经全枚举完
        }
        if(!f)
            cout<<"YES\n";//没问题就YES
    }
    return 0;
}
```


---

