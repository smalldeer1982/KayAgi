# [BalticOI 2017] Friends

## 题目背景

高中就是要交最棒的朋友！  
乌姆里奇校长要调查霍格沃茨学校的交友情况了！

## 题目描述

学校里有 $n$ 个同学，他们的交友情况满足以下的条件：

- 如果 $a$ 与 $b$ 是朋友那么 $b$ 与 $a$ 也是朋友；
- 同学们可以分成组，每个同学都恰好只在一个组里面，且：
	- 每个组的人数至少 $1$ 个最多 $p$ 个；
    - 每组都有这样最多 $q$ 对朋友满足一个人在这个组，另一个人在别的组。
    
在同一个组里的两个同学不一定必须是朋友。   
现在她来问您，想让您说出这些学生撒没撒谎。  
如果没有撒谎的话，她想让您给出一个合理的分组模式。

## 说明/提示

**数据规模与约定**

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$n \le 16$。
- Subtask 2（37 pts）：$n \le 250$，$q \le 2$。
- Subtask 3（12 pts）：$q \le 2$。
- Subtask 4（31 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 2500$，$p+q \le 15$，$\sum m_i \le 30000$，同学们不以自己为朋友。

**本题使用 Special Judge。**

**说明**

**翻译自 [BOI 2017 D2](https://boi.cses.fi/files/boi2017_day2.pdf) T2 Friends。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。

spj 提示信息说明：
- `Accepted`：答案正确。
- `Wrong Answer[0]`：判断错误。
- `Wrong Answer[1]`：某些组的大小不符合要求。
- `Wrong Answer[2]`：组里含有编号不在 $0$ 到 $n-1$ 内的人。
- `Wrong Answer[3]`：某些人属于多个组。
- `Wrong Answer[4]`：某些人不属于任何组。
- `Wrong Answer[5]`：分组不满足要求。

spj 作者：@[FZzzz](https://www.luogu.com.cn/user/174045)。

## 样例 #1

### 输入

```
4 2 1
1 1
2 0 2
2 1 3
1 2
```

### 输出

```
home
2
2 0 1
2 2 3```

## 样例 #2

### 输入

```
5 2 1
1 1
2 0 2
2 1 3
2 2 4
1 3
```

### 输出

```
detention```

## 样例 #3

### 输入

```
3 3 3
2 1 2
2 0 2
1 0
```

### 输出

```
detention```

# 题解

## 作者：Tweetuzki (赞：16)

> 给出一张 $n$ 个点，$m$ 条边的无向图。
> 
> 需要将这些点划分为若干互不相交的点集，满足：
> 
> - 集合大小不超过 $p$。
> - 这个集合内的点连出集合的边不超过 $q$ 条。
> 
> 判断是否有解并给出合法方案。
> 
> $n \le 2500$，$p + q \le 15$，$m \le 15\ 000$。

这是一道有趣的暴力题。

首先有个小细节，要先检查一遍原图是否是一张无向图（即 $u \to v$ 有边是否同时会保证 $v \to u$ 有边），如果不是需要直接输出 `detention`，详见样例 3，因为这被当做是同学撒谎（（（。

我们将算法分为两个步骤：

- 对 $1 \sim n$ 中的每个点 $i$，找出一个包含 $i$ 的合法的集合。如果找不到，说明无解，输出 `detention`。
- 对求出的所有点集，调整方案，使得原本的任意两个点集 $S, T$ 变成 $S', T'$，使得 $S' \cap T' = \emptyset$ 且 $S' \cup T' = S \cup T$。这样处理后最后每个点就仅属于一个点集。

对于第一个步骤，用暴力去枚举所有过 $i$ 的联通块，当连通块大小超过 $p$ 或连通块大小加上相邻点集大小超过 $p + q$ 时就退出递归。这样暴力复杂度可以证明是 $\mathcal{O}(2 ^ {p + q})$，做 $n$ 次就是 $\mathcal{O}(n \cdot 2 ^ {p + q})$。

一种理解是，我们首先将问题进行缩放，定义 $q'$ 为集合外的与集合内的点有连边的点数，显然 $q' \le q$。

我们给每个点四种状态：在集合内、与集合内的点相邻但还未确定是否要加入集合、与集合内的点相邻且确定不加入集合、不与集合相邻的点（前三者在我的代码中分别体现为 $\texttt{std::set<int> in, neighbor, out}$）。
  
当我们递归到连通块 $s$ 时，我们只枚举那些与集合内的点相邻但还未确定是否要加入集合的点（即 $\texttt{neighbor}$）。这样，若加入该点到集合内，则 $p$ 增加 $1$；如果不加入该点到集合内，则 $q'$ 增加 $1$。也就是说，在每步递归的过程中，共有两种选择，而每做一层 $p + q'$ 的值都会增加，故而最多做 $p + q'$ 层。又由于 $q' \le q$，因此递归次数上界为 $2 ^ {p + q}$。

对于第二个步骤，有一个结论：对于两个合法的点集 $A, B$，则 $A \setminus B$ 和 $B \setminus A$ 中必然至少有一个是合法点集。

证明为，设 $C = A \cap B$，$A, C$ 之间边数为 $a$，$B, C$ 之间边数为 $b$，$C$ 向外且不连向 $A, B$ 的边数为 $c$。则当 $A$ 变成 $A \setminus B$ 后，边数加上了 $a - b - c$，$B$ 变成 $B \setminus A$ 后，边数加上了 $b - a - c$。由于 $a - b$ 和 $b - a$ 互为相反数，则其中至少一个 $\le 0$，则 $p + q$ 的值不会变大，一定还是合法的点集。

知道了这个结论后，我们可以枚举 $n \choose 2$ 个点对，调整他们的点集 $(S, T)$ 变成 $(S \setminus T, T)$ 或 $(S, T \setminus S)$，就可以使得所有集合无交了。这里复杂度 $\mathcal{O}(n ^ 2 p)$。

总时间复杂度 $\mathcal{O}(n \cdot 2 ^ {p + q} + n ^ 2 p)$，实际很难卡满，常数不大，可以通过本题。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <vector>

const int MaxN = 2500, MaxM = 30000;
const int MaxP = 15;

struct graph_t {
  int cnte;
  int head[MaxN + 5], to[MaxM * 2 + 5], next[MaxM * 2 + 5];

  inline void addEdge(int u, int v) {
    cnte++; to[cnte] = v;
    next[cnte] = head[u]; head[u] = cnte;
  }
};

int N, P, Q;
graph_t Gr;
std::set<int> Group[MaxN + 5];
bool InGroup[MaxN + 5];

void NO() { puts("detention"); exit(0); }

void init() {
  std::set< std::pair<int, int> > edge;
  edge.clear();
  scanf("%d %d %d", &N, &P, &Q);
  for (int i = 0; i < N; ++i) {
    int m;
    scanf("%d", &m);
    if (m >= P + Q) NO();
    for (int j = 1; j <= m; ++j) {
      int x;
      scanf("%d", &x);
      Gr.addEdge(i + 1, x + 1);
      if (i < x) edge.insert(std::make_pair(i, x));
      else {
        if (edge.count(std::make_pair(x, i)) == 0) NO();
        else edge.erase(std::make_pair(x, i));
      }
    }
  }
  if (edge.empty() == false) NO();
}

inline bool validGroup(const std::set<int> &s) {
  if ((int) s.size() > P) return false;
  int cnt = 0;
  for (int u : s) {
    for (int i = Gr.head[u]; i; i = Gr.next[i]) {
      int v = Gr.to[i];
      if (s.count(v) == 0) cnt++;
    }
  }
  return cnt <= Q;
}

std::set<int> in, neighbor, out;

bool dfs(int u, int bel, std::set<int> in, std::set<int> neighbor, std::set<int> out) {
  in.insert(u);
  if (u != bel) neighbor.erase(u);
  if ((int) in.size() > P || (int) out.size() > Q || (int) in.size() + (int) neighbor.size() + (int) out.size() > P + Q) return false;
  if (validGroup(in) == true) {
    Group[bel] = in;
    for (int v : in) InGroup[v] = true;
    return true;
  }
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (in.count(v) == 0 && neighbor.count(v) == 0 && out.count(v) == 0)
      neighbor.insert(v);
  }
  while (!neighbor.empty()) {
    int v = *(neighbor.begin());
    if (dfs(v, bel, in, neighbor, out) == true) return true;
    neighbor.erase(neighbor.begin());
    out.insert(v);
  }
  return false;
}

void solve() {
  for (int i = 1; i <= N; ++i) {
    if (InGroup[i] == true) continue;
    in.clear();
    neighbor.clear();
    out.clear();
    if (dfs(i, i, std::set<int>(), std::set<int>(), std::set<int>()) == false) NO();
  }
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j < i; ++j) {
      std::set<int> s1 = Group[i], s2 = Group[j];
      for (int v : Group[i])
        if (s2.count(v) > 0) s2.erase(v);
      for (int v : Group[j])
        if (s1.count(v) > 0) s1.erase(v);
      if (validGroup(s1) == true) Group[i] = s1;
      else Group[j] = s2;
    }
  int cntGroup = 0;
  for (int i = 1; i <= N; ++i)
    if (Group[i].empty() == false) cntGroup++;
  puts("home");
  printf("%d\n", cntGroup);
  for (int i = 1; i <= N; ++i) {
    if (Group[i].empty()) continue;
    printf("%d", (int) Group[i].size());
    for (int v : Group[i]) printf(" %d", v - 1);
    putchar('\n');
  }
}

int main() {
  init();
  solve();
  return 0;
}
```

---

[参考资料](https://codeforces.com/blog/entry/51740?#comment-356943)

---

## 作者：serene_analysis (赞：6)

### update:还请各位不要点赞，补充本就应该在原本的题解之后。

---

谨以此题解作为对 Tweetuzki 神仙的题解的补充。

题解的说明顺序按照每部分在我代码中的先后顺序。

---

##### 找出合法集合的具体步骤

现在递归到了 $x$ 点，当前在找包含 $bel$ 的合法集合。已经确定要加入的元素、与当前集合某点相邻但还未确定是否加入的元素、与当前集合某点相邻且确定不加入的元素，分别存在 $\texttt{std::set<int>in,neighbor,out}$ 中。

+ 首先将 $x$ 加入 $\texttt{in}$ 中并从 $\texttt{neighbor}$ 中删除 $x$（若没有则忽略）。
+ 检查 $\texttt{in,neighbor,out}$ 的大小是否满足题意。
+ 若当前的 $\texttt{in}$ 符合条件，则此次搜索成功。将所有在 $\texttt{in}$ 中的点标记，以后不再搜索。记录下这个集合 $\texttt{in}$，直接返回 $\text{true}$。
+ 扫描所有与 $\texttt{in}$ 中某点相邻的点 $v$，若 $v$ 不在 $\texttt{in,neighbor,out}$ 的任意一个中，将其加入 $\texttt{neighbor}$。
+ 对于集合 $\texttt{neighbor}$ 中的每个元素 $v$，递归尝试能否将其加入当前集合 $\texttt{in}$ 中，若可行，直接返回 $\text{true}$，否则将其从 $\texttt{neighbor}$ 中移至 $\texttt{out}$ 中。
+ 若此次搜索完成仍未找到可行解，返回 $\text{false}$。

##### 各种无解判断

+ （Tweetuzki 神仙提及的）有两个人不是双向的朋友关系。可以使用 $\texttt{map}$ 套 $\texttt{pair}$ 来判断。
+ 某个点连出的边不小于 $p+q$。
+ 某个点找不到对应的合法集合。

##### 对于第二个步骤的证明的补充

（先照抄一小段）题设：设有两个合法点集 $A,B$，则 $A \setminus B$ 和 $B \setminus A$ 至少有一个合法。（这里的 $\setminus$ 是减去的意思）
  
证明：令 $C$ 为 $A \cap B$。考虑减去 $C$ 过后会对两个点集产生什么影响。

首先考虑增加了哪些连向集合外的边。以 $A$ 为例，它增加了本身与 $C$ 的连边数，设为 $a$，$B$ 的同理设为 $b$。

然后考虑失去了哪些边。因为失去了整个 $C$，所以 $C$ 连向外部的边全部失去。这部分既包含连向 $A,B$ 的边，也包含连向其他点的边，后者设为 $c$。

$A$ 和 $B$ 边的变化量就分别是 $a-b-c$ 和 $b-a-c$。因为 $a-b$ 和 $b-a$ 互为相反数，所以其中至少有一个非正，减去 $c$ 也非正，所以边数满足条件，而点数又变小，所以合法。
  
附一个自己的代码，为了编写方便可能与描述有些出入。

```
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<set>
const int maxn=2.5e3+5;
const int maxm=3e4*2+5;
const int maxp=15;
struct edge{
	int to;
	int next;
}qxx[maxm];
int qxx_cnt,h[maxn];
void add(int x,int y){
	qxx[++qxx_cnt]=(edge){y,h[x]};
	h[x]=qxx_cnt;
	return;
}
int n,p,q;
std::set<int>group[maxn];
bool inside[maxn];
void no_sol(){
	printf("detention");
	exit(0);
	return;
}
bool can(std::set<int>gave){
	if((int)gave.size()>p)return false;
	int cou=0;
	for(int x:gave){
		for(int i=h[x];i;i=qxx[i].next){
			int v=qxx[i].to;
			if(!gave.count(v))cou++;
		}
	}
	return cou<=q;
}
std::set<int>in,near,out;
bool search(int x,int bel,std::set<int>in,std::set<int>near,std::set<int>out){
	in.insert(x);
	if(x!=bel)near.erase(x);
	if((int)in.size()>p||(int)out.size()>q||(int)(in.size()+near.size()+out.size())>p+q)return false;
	if(can(in)){
		group[bel]=in;
		for(int x:in)inside[x]=true;
		return true;
	}
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(!in.count(v)&&!near.count(v)&&!out.count(v))near.insert(v);
	}
	while(!near.empty()){
		int v=*(near.begin());
		if(search(v,bel,in,near,out))return true;
		near.erase(near.begin());
		out.insert(v);
	}
	return false;
}
signed main(){
	std::set<std::pair<int,int>>apr;
	apr.clear();
	scanf("%d%d%d",&n,&p,&q);
	for(int i=0;i<n;i++){
		int tot;
		scanf("%d",&tot);
		if(tot>=p+q)no_sol();
		for(int j=1;j<=tot;j++){
			int x;
			scanf("%d",&x);
			add(i+1,x+1);
			if(i<x)apr.insert({i,x});
			else{
				if(!apr.count({x,i}))no_sol();
				else apr.erase({x,i});
			}
		}
	}
	if(!apr.empty())no_sol();
	for(int i=1;i<=n;i++){
		if(inside[i])continue;
		in.clear();
		near.clear();
		out.clear();
		if(!search(i,i,std::set<int>(),std::set<int>(),std::set<int>()))no_sol();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			std::set<int>ls=group[i],rs=group[j];
			for(int x:group[i])if(rs.count(x))rs.erase(x);
			for(int x:group[j])if(ls.count(x))ls.erase(x);
			if(can(ls))group[i]=ls;
			else group[j]=rs;
		}
	}
	int cou=0;
	for(int i=1;i<=n;i++)if(!group[i].empty())cou++;
	printf("home\n");
	printf("%d\n",cou);
	for(int i=1;i<=n;i++){
		if(group[i].empty())continue;
		printf("%d",(int)(group[i].size()));
		for(int x:group[i])printf(" %d",x-1);
		printf("\n");
	}
	return 0;
}
```

  
感谢您的阅读。

---

