# Katu Puzzle

## 题目描述

Katu Puzzle 以一个有向图 $G(V, E)$ 的形式给出，其中每条边 $e(a, b)$ 都被标记为一个布尔运算符 $\text{op}$（AND, OR, XOR 之一）以及一个整数 $c$（$0 \leq c \leq 1$）。如果可以为每个顶点 $V_i$ 找到一个值 $X_i$（$0 \leq X_i \leq 1$），使得对于每条边 $e(a, b)$ 由 $\text{op}$ 和 $c$ 标记的情况下，以下公式成立：

$$X_a \ \text{op} \ X_b = c$$

那么这个 Katu 是可解的。

给定一个 Katu Puzzle，你的任务是确定它是否可解。

## 样例 #1

### 输入

```
4 4
0 1 1 AND
1 2 1 OR
3 2 0 AND
3 0 0 XOR```

### 输出

```
YES```

# 题解

## 作者：_Liyx_ (赞：6)

## 思路
前置芝士：[P4782 【模板】2-SAT](https://www.luogu.com.cn/problem/P4782)

将每个点拆为「TRUE」和「FALSE」两个点。

题目给出了 $M$ 组关系，我们能发现对于每种关系，会有一些矛盾。如：$X\vee Y=1$，那么矛盾关系即为 $\neg X \wedge \neg Y=1$，所以如果我们选了 $\neg X$，那就只能选 $Y$ 而不能选 $\neg Y$；同理，如果我们选了 $\neg Y$， 就只能选 $X$ 而不能选 $\neg X$。

即如果有矛盾，则让有矛盾的两个状态，分别向另一个状态的“非”连一条边，通俗的来讲就是：
$$
A\wedge B=0
\newline
\Rightarrow (A\to \neg B),\ (B\to \neg A)
$$

这也是很多 2-SAT 题用的连边方法，可以学习一下。

这时候又有人问了：驻波驻波，那如果我是 $X\wedge Y = 1$ 或者 $X \vee Y = 0$ 怎么办呢？

这种情况即为$X=1\wedge Y=1$ 和 $X=0\wedge Y = 0$，那我们该如何规定 $X$ 与 $Y$ 的值呢？

我们考虑我们是如何确定一个点的值，我们比较 $V$ 与 $\neg V$ 的拓扑序，选定拓扑序大的一个。
所以我们如果想让 $V$ 被选中，即令 $V = 1$ 就是让 $V$ 的拓扑序比 $\neg V$ 大，那么我们就让 $\neg V\to V$，这样能保证 $V$ 的拓扑一定会比 $\neg V$ 大。

然后依照题目的要求进行建边，具体如何建边这里就不再赘述了，这种东西还是要自己想一想的。

最后再判断一下 $X$ 和 $\neg X$ 是否在同一个 scc 里即可。
## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2005
int n, m;
vector<int> g[N];
int val(int x, int s) {
	if (s == 0) return x + n;
	return x;
}
int cnt, dfn[N], low[N], buc[N], scc[N], num;
stack<int> stk;
void Tarjan(int u) {
	dfn[u] = low[u] = ++cnt;
	stk.push(u);
	buc[u] = 1;
	for (auto v : g[u]) {
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (buc[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int y;
		num++;
		do {
			y = stk.top();
			stk.pop();
			buc[y] = 0;
			scc[y] = num;
		} while (y != u);
	}
}
signed main() {
	cin >> n >> m;
	while (m--) {
		int a, b, c;
		string op;
		cin >> a >> b >> c >> op;
		a++;
		b++;
		if (op == "AND") {
			if (c) {
				g[val(a, 0)].push_back(val(a, 1));
				g[val(b, 0)].push_back(val(b, 1));
			}
			else {
				g[val(a, 1)].push_back(val(b, 0));
				g[val(b, 1)].push_back(val(a, 0));
			}
		}
		if (op == "OR") {
			if (c) {
				g[val(a, 0)].push_back(val(b, 1));
				g[val(b, 0)].push_back(val(a, 1));
			}
			else {
				g[val(a, 1)].push_back(val(a, 0));
				g[val(b, 1)].push_back(val(b, 0));
			}
		}
		if (op == "XOR") {
			if (c) {
				g[val(a, 1)].push_back(val(b, 0));
				g[val(b, 1)].push_back(val(a, 0));
				g[val(a, 0)].push_back(val(b, 1));
				g[val(b, 0)].push_back(val(a, 1));
			}
			else {
				g[val(a, 1)].push_back(val(b, 1));
				g[val(b, 1)].push_back(val(a, 1));
				g[val(a, 0)].push_back(val(b, 0));
				g[val(b, 0)].push_back(val(a, 0));
			}
		}
	}
	for (int i = 1; i <= 2 * n; i++)
		if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= n; i++) {
		if (scc[val(i, 0)] == scc[val(i, 1)]) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
	return 0;
}
```

---

## 作者：wangbinfeng (赞：6)

[![](https://img.shields.io/badge/题目-P10969_Katu_Puzzle-green)
![](https://img.shields.io/badge/难度-提高+/省选−-blue)
![](https://img.shields.io/badge/考点-2--SAT-red)
![](https://img.shields.io/badge/题型-传统题-yellow)](https://www.luogu.com.cn/problem/P10969)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

---
## 前置知识：
1. 什么是 k-SAT？
> SAT 是适定性（`Satisfiability）问题的简称。一般形式为 k - 适定性问题，简称 k-SAT。而当 $k>2$ 时该问题为 NP 完全的。所以我们只研究 $k=2$ 的情况。——摘自 [OI wiki](https://oi-wiki.org/graph/2-sat/)
2. 什么是 NP 完全问题？
> 有点多，具体可以前往[百度百科](https://baike.baidu.com/item/NP%E5%AE%8C%E5%85%A8%E9%97%AE%E9%A2%98/4934286?fromtitle=npc&fromid=658479#4)学习。

## 2-SAT：
1. 什么是 2-SAT？
> 即 $k=2$ 的 k-SAT 问题，具体地，有 $n$ 个变量，每个变量只有两种可能的取值。再给定 $m$ 个条件，每个条件都是对两个变量的限制，求是否存在对 $n$ 个变量的合法取值，使得全部的 $n$ 个条件能得到满足，这个问题就被称为 2-SAT 问题。——部分摘自《算法竞赛进阶指南（李煜东著）》
2. 如何判定 2-SAT 问题是否有解：
> 1. 建一个有 $2n$ 个点的有向图，每一个原变量对应图中的两个点，这两个点用于表示这个点的两种取值。
> 2. 对于条件“若 $x$ 取 $a$（下面简记为 $x_a$），则 $y$ 必须为 $b$（下面简记为 $y_b$）”，从结点 $x_a$ 指向 $y_b$。
> 3. 注意到，2 中的条件他的逆否命题也一定成立，即“若 $y$ 不取 $b$（下面简记为 $y_{\neg b}$），则 $x$ 必须不取 $a$（下面简记为 $x_{\neg a}$）”，即从结点 $y_{\neg b}$ 指向 $x_{\neg a}$。
> 4. 观察到，若存在一条路径经过 $x_a$，则如果变量 $x$ 取 $a$，这条路径上所有的结点对应的变量均需要取这个结点对应的值。
> 5. 由 4 得，若 $x_a$ 和 $x_{\neg a}$ 在同一个强连通分量中，那么这种情况一定无解。因为并不可能存在一个变量 $x$ 使得其能同时取值 $a$ 和 $\neg a$。
> 6. 否则可以证明一定有解。
3. 关系推导：
> “若 $P$ 则 $Q$”不一定能推出其逆命题“若 $Q$ 则 $P$”、否命题“若非 $P$ 则非 $Q$”，但是一定可以推出逆否命题“若非 $Q$ 则非 $P$”。~~[人民教育出版社高中数学 A 版必修一第一单元](https://mp.weixin.qq.com/s?__biz=MzU3NTg3MTYyMQ==&mid=2247506136&idx=2&sn=2935d0137137294b67ebe40d10d481bb&chksm=fd1e1732ca699e24a448b8e18fe29d2608685fa079110bc20addec546cfc62cca8649a715a08#rd)有详细的讲解，这里暂且省略。~~
>> 【退役半年后补充】   
>> 假设原命题 $(P\to Q)$ 成立。    
>> 考虑逆否命题 $(\neg P\to \neg Q)$ 的情况。如果 $Q$ 为假 $(\neg Q)$，根据原命题 $(P\to Q)$，如果 $P$ 为真的话，$Q$ 必须为真。但是现在 $Q$ 是假的，所以 $P$ 不能为真，即 $P$ 必须为假 $(\neg P)$。因此，逆否命题 $(\neg P\to \neg Q)$ 成立。   
>> 结论：如果原命题成立，那么逆否命题也一定成立。  
>>- 证明来源：[知乎-佐手牵鼬手](https://www.zhihu.com/question/664739613/answer/3599707985)，由于现在知乎需要强制登录故搬运过来，如果侵权私信或评论删除。 _知乎要求：著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。_ 

4. 关系的传递性：
> 显然，若 $P$ 则 $Q$、若 $Q$ 则 $R$ 可以推出若 $P$ 则 $R$，这证明了 2.4. 的正确性。
## 对于本题：
1. 题意简述：
> $n$ 个变量 $m$ 个约束的 2-SAT 问题，其中约束为 $X_a\;\text{op}\;X_b=c,\text{op}\in \{\land,\lor,\oplus\}$。
2. 分析：
> 暂时设结点 $a,\forall a\in\left[1,n\right]$ 表示变量 $X_a$ 取 $0$，结点 $a+n$ 表示变量 $X_a$ 取 $1$。那么输入的情形有以下六种：
>> 1. $X_a\land X_b=0$：意义是 $X_a,X_b$ 最少一个的值为 $0$，若 $X_a=1$ 则 $X_b=1$，若 $X_b=1$ 则 $X_a=1$。将结点 $a+n$ 向结点 $b$，结点 $b+n$ 向结点 $a$ 连边。
>> 2. $X_a\land X_b=1$：意义是 $X_a,X_b$ 必须均为 $1$，若 $X_a=1$ 则 $X_b=1$。将结点 $a+n$ 向结点 $b+n$ 连边。考虑到结点 $a$ 和结点 $b$ 均不能取到，主动将其矛盾即可（具体地，结点结点 $a$ 向结点 $a+n$ 连边，结点 $b$ 向结点 $b+n$ 连边）。
>> 3. $X_a\lor X_b=0$：与 2. 类似，结点结点 $a+n$ 向结点 $a$ 连边，结点 $b+n$ 向结点 $b$ 连边。
>> 4. $X_a\lor X_b=1$：与 1. 类似，结点结点 $a$ 向结点 $b+n$ 连边，结点 $b$ 向结点 $a+n$ 连边。
>> 5. $X_a\oplus X_b=0$：结点结点 $a$ 向结点 $b$ 连边，结点 $b$ 向结点 $a$ 连边，结点结点 $a+n$ 向结点 $b+n$ 连边，结点 $b+n$ 向结点 $a+n$ 连边。
>> 6. $X_a\oplus X_b=1$：结点结点 $a$ 向结点 $b+n$ 连边，结点 $b$ 向结点 $a+n$ 连边，结点结点 $a+n$ 向结点 $b$ 连边，结点 $b+n$ 向结点 $a$ 连边。

3. 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100+9;
vector<int>g[maxn<<1];
int n,m,low[maxn<<1],dfn[maxn<<1],tot,cnt,col[maxn<<1];
stack<int>st;
string op;
inline void tarjan(const int u){
	dfn[u]=low[u]=++tot,st.push(u);
	for(int v:g[u])
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!col[v])low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u]){
		for(col[u]=++cnt;!st.empty()&&st.top()!=u;st.pop())col[st.top()]=cnt;
		st.pop();
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1,a,b,c;i<=m;i++){
		cin>>a>>b>>c>>op;
		switch(op[0]){
		case'A':
			if(!c)g[a+n].push_back(b),g[b+n].push_back(a);
			else g[a].push_back(a+n),g[b].push_back(b+n);
		break;
		case'O':
			if(!c)g[a+n].push_back(a),g[b+n].push_back(b);
			else g[a].push_back(b+n),g[b].push_back(a+n);
		break;
		case'X':
			if(!c)g[a].push_back(b),g[b].push_back(a),g[a+n].push_back(b+n),g[b+n].push_back(a+n);
			else g[a].push_back(b+n),g[b].push_back(a+n),g[a+n].push_back(b),g[b+n].push_back(a);
		break;
		default:throw(387009);
		}
	}
	for(int i=0;i<n*2;i++)if(!dfn[i])tarjan(i);
	for(int i=0;i<n;i++)if(col[i]==col[i+n]){cout<<"NO";return 0;}
	cout<<"YES"; 
}
```
> - PS. 如果你 WA #2 80pts，可以考虑输入时是否错将 $m$ 写成了 $n$。到底是谁写错变量名调了半小时啊？
4. 其他：
> 由于本题解作者是当成学习笔记写的，如果有写错或者哪里看不懂欢迎也希望读者可以在评论区反馈。



[![](https://jrenc.azurewebsites.net/api/signature?code=zHZRCCItO-yB8t7d2KyitELFDwADnXIotkeeIQL3juyNAzFucnyrWA%3D%3D&name=thacks%20for%20reading%20%20%20%20%20%20%20%20by%20%40wangbinfeng(387009)&animate=true&speed=0.7&color=purple)](https://www.luogu.com.cn/user/387009)
$$\color{grey}{\tiny{\texttt{发现上面的签名是动图了吗？}}}$$

---

## 作者：Double_Sheep (赞：6)

提供一种不需要建虚点，更简便、清晰的建图方式。

（在 NOIP 前 2 天写题解涨涨 rp，也祝大家 2024 NOIP and 2025 赛季 Rp++！）

---

前置芝士：[P4782【模板】2-SAT](https://www.luogu.com.cn/problem/P4782)。

本题可以使用 2-SAT 求解，主要的问题是如何建边：

- 若 $op=\texttt{AND}$：
1. $c=0$：$X_a=1$ 时 $X_b=0$，$X_b=1$ 时 $X_a=0$，即 $a+n\to b, b+n\to a$。
2. $c=1$：$X_a=1$ 时 $X_b=1$，$X_b=1$ 时 $X_a=1$，即 $a+n\to b+n, b+n\to a+n$；如果 $X_a$ 或 $X_b$ 有一个是 $0$ 的话 **条件不成立**，直接让它产生矛盾即可：$a\to a+n, b\to b+n$。

- 若 $op=\texttt{OR}$：
1. $c=0$：$X_a=0$ 时 $X_b=0$，$X_b=0$ 时 $X_a=0$，即 $a\to b, b\to a$；如果 $X_a$ 或 $X_b$ 有一个是 $1$ 的话 **条件不成立**，直接让它产生矛盾即可：$a+n\to a, b+n\to b$。
2. $c=1$：$X_a=0$ 时 $X_b=1$，$X_b=0$ 时 $X_a=1$，即 $a\to b+n, b\to a+n$。

- 若 $op=\texttt{XOR}$：
1. $c=0$：$X_a=0$ 时 $X_b=0$，$X_a=1$ 时 $X_b=1$，$X_b=0$ 时 $X_a=0$，$X_b=1$ 时 $X_a=1$，即 $a\to b, a+n\to b+n, b\to a, b+n\to a+n$。
2. $c=1$：$X_a=0$ 时 $X_b=1$，$X_a=1$ 时 $X_b=0$，$X_b=0$ 时 $X_a=1$，$X_b=1$ 时 $X_a=0$，即 $a\to b+n, a+n\to b, b\to a+n, b+n\to a$。

剩下的就是 2-SAT 的板子啦，代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 205, M = 4e4 + 5;
int n, m, head[N], tot;
int idx, dfn[N], low[N], siz[N], scc[N], Scc_cnt;
bool vis[N];
stack<int> st;
struct edge {int v, nxt;} e[M];
void add(int u, int v) {
    e[++tot] = {v, head[u]};
    head[u] = tot;
}
void tarjan(int u) {
	dfn[u] = low[u] = ++idx, st.push(u), vis[u] = 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int v; Scc_cnt++;
		do {
			v = st.top(); st.pop();
			siz[Scc_cnt]++, scc[v] = Scc_cnt, vis[v] = 0;
		} while (u != v);
	}
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m; string s;
    for (int i = 1, x, y, a; i <= m; i++) {
    	cin >> x >> y >> a >> s, x++, y++;
    	if (s[0] == 'A') {
			if (!a) add(x + n, y), add(y + n, x);
			else add(x + n, y + n), add(y + n, x + n), add(x, x + n), add(y, y + n);
		} if (s[0] == 'O') {
			if (!a) add(x, y), add(y, x), add(x + n, x), add(y + n, y);
			else add(x, y + n), add(y, x + n);
    	} if (s[0] == 'X') {
			if (!a) add(x, y), add(x + n, y + n), add(y, x), add(y + n, x + n);
			else add(x, y + n), add(x + n, y), add(y, x + n), add(y + n, x);
    	} //建图方式如上所述
	}
    for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++) if (scc[i] == scc[i + n]) cout << "NO\n", exit(0);
    cout << "YES\n";
    return 0;
}
```

如果写的有任何问题或不易理解的话，欢迎提出，谢谢！(●'◡'●)

---

## 作者：I_Was_Spasmodic (赞：2)

### 题意
有 $n$ 个点和 $m$ 条边，给每个点赋值为 $0$ 或 $1$，使得每条边满足 $x_i \  \text{op} \  y_i = c_i$。

### 分析
满足 2-sat 模型，这里不做赘述。

考虑建边，对原有边分类讨论：
1. $AND = 1 : x=1,\ y=1$
2. $AND = 0 : x=1 \Rightarrow y=0 ,\ y=1 \Rightarrow x=0$
3. $OR = 1 : x=0 \Rightarrow y=1 ,\ y=0 \Rightarrow x=1$
4. $OR = 0 : x=0,\ y=0$
5. $XOR = 0 : x=0 \Leftrightarrow y=1 ,\ x=1 \Leftrightarrow y=0$
6. $XOR =1 : x=1 \Leftrightarrow y=1 ,\ x=0 \Leftrightarrow y=0$

可以发现对于 2,3,5,6，都是通过一个变量来推导出另一个变量，而对于 1,4，是直接确定了两个变量的值，是本题的一个难点。

考虑 1，发现当 $x=0$ 或 $y=0$ 时一定不能成立，于是新建一个节点 $T$，让 $x=0$ 和 $y=0$ 连向 $T$，再让 $T$ 连向所有点。这样，如果推出 $x=0$ 或 $y=0$，就一定能推出 $T$，而 $T$ 又能推出所有节点，于是成环。4 同理。

考虑判定有无一组解，先判定 $x=0 \Rightarrow x=1$ 是否成立，如果成立则无解；再判定 $x=0 \nRightarrow T$ 和 $x=1 \nRightarrow T$ 是否至少有一个成立，如果没有则无解（因为如果有一个成立，$x$ 就可以取该值而避免冲突）。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
char rdc()
{
	char c=getchar();
	while(c<'A' or c>'Z')c=getchar();
	return c;
}
int rd()
{
	char c=getchar();
	int res=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
vector<int>g[N];
int n,m,T;
int scc[N],num;
int stk[N],tp;
bool instk[N];
int low[N],dfn[N],inx;
void tar(int x) // tarjan 模板
{
	if(dfn[x])return;
	stk[++tp]=x;
	instk[x]=1;
	low[x]=dfn[x]=++inx;
	for(auto y:g[x])
	{
		if(!dfn[y])
		{
			tar(y);
			low[x]=min(low[x],low[y]);
		}
		else if(instk[y])low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x])
	{
		int p;
		num++;
		do{
			p=stk[tp--];
			instk[p]=0;
			scc[p]=num;
		}while(p!=x);
	}
}

signed main()
{
	n=rd();m=rd();
	T=n*2+1;
	for(int i=1;i<=n*2;i++)g[T].push_back(i); // T 通向所有点
	while(m--)
	{
		int x=rd()+1,y=rd()+1,c=rd();
		char op=rdc();
		if(op=='A') // 分类建边
		{
			if(c==1){
				g[x].push_back(T);
				g[y].push_back(T);
			}
			else {
				g[x+n].push_back(y);
				g[y+n].push_back(x);
			}
		}
		else if(op=='O')
		{
			if(c==1){
				g[x].push_back(y+n);
				g[y].push_back(x+n);
			}
			else {
				g[x+n].push_back(T);
				g[y+n].push_back(T);
			}
		}
		else {
			if(c==1){
				g[x].push_back(y+n);
				g[x+n].push_back(y);
				g[y].push_back(x+n);
				g[y+n].push_back(x);
			}
			else {
				g[x].push_back(y);
				g[y].push_back(x);
				g[x+n].push_back(y+n);
				g[y+n].push_back(x+n);
			}
		}
	}
	for(int i=1;i<=n*2+1;i++)tar(i);
	bool fl=1;
	for(int i=1;i<=n;i++)
	{
		if(scc[i]==scc[i+n] or (scc[i]==scc[T] and scc[i+n]==scc[T])) // 判定有无解，见分析 
		{
			fl=0;
			break;
		}
	}
	if(fl)puts("YES");
	else puts("NO");
}
```

---

## 作者：20111019Yu (赞：1)

### 题意
有 $n$ 个值，要么是 $0$，要么是 $1$。有 $m$ 条运算式。问能否找到一个解，使得满足所有式子。
### 思路
很明显，这是一道 [2-SAT](https://oi-wiki.org/graph/2-sat/) 的题。接下来我们思考当其中一个值是什么的时候能推出来另一个值。

- 当 $s=and,c=1$ 时：
  $$x=0\rightarrow x=1\\
  y=0\rightarrow y=1$$
- 当 $s=and,c=0$ 时：
  $$x=1\rightarrow y=0\\
  y=1\rightarrow x=0$$
- 当 $s=or,c=1$ 时：
  $$x=0\rightarrow y=1\\
  y=0\rightarrow x=1$$
- 当 $s=or,c=0$ 时：
  $$x=1\rightarrow x=0\\
  y=1\rightarrow y=0$$
- 当 $s=xor,c=1$ 时：
  $$x=0\rightarrow y=1\\
  x=1\rightarrow y=0\\
  y=0\rightarrow x=1\\
  y=1\rightarrow x=0$$
- 当 $s=xor,c=0$ 时：
  $$x=0\rightarrow y=0\\
  x=1\rightarrow y=1\\
  y=0\rightarrow x=0\\
  y=1\rightarrow x=1$$
除了其中第 $1$ 个和第 $4$ 个有点难想，其他都好想。
### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, a, b, c, in, cnt, dfn[205], low[205], scc[205];
string s;
vector<int> vec[205];
bool vis[205];
stack<int> st;

void tarjan(int x){
	dfn[x] = low[x] = ++in;
	vis[x] = 1, st.push(x);
	for( auto &i : vec[x] ){
		if(!dfn[i]){
			tarjan(i);
			low[x] = min(low[x], low[i]);
		}
		else if(vis[i]) low[x] = min(low[x], dfn[i]);
	}
	if(dfn[x] == low[x]){
		cnt++;
		while(st.top() != x){
			vis[st.top()] = 0;
			scc[st.top()] = cnt;
			st.pop(); 
		}
		vis[st.top()] = 0;
		scc[st.top()] = cnt;
		st.pop(); 
	}
	return;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for( int i = 1; i <= m; i++ ){
		cin >> a >> b >> c >> s;
		a++, b++;
		if(s == "AND"){
			if(c){
				vec[a + n].push_back(a);
				vec[b + n].push_back(b);
			}
			else{
				vec[a].push_back(b + n);
				vec[b].push_back(a + n);
			}
		}
		else if(s == "OR"){
			if(c){
				vec[a + n].push_back(b);
				vec[b + n].push_back(a);
			}
			else{
				vec[a].push_back(a + n);
				vec[b].push_back(b + n);
			}
		}
		else if(s == "XOR"){
			if(c){
				vec[a].push_back(b + n);
				vec[b].push_back(a + n);
				vec[a + n].push_back(b);
				vec[b + n].push_back(a);
			}
			else{
				vec[a].push_back(b);
				vec[b].push_back(a);
				vec[a + n].push_back(b + n);
				vec[b + n].push_back(a + n);
			}
		}
	}
	for( int i = 1; i <= 2 * n; i++ ){
		if(!dfn[i]) tarjan(i);
	}
	for( int i = 1; i <= n; i++ ){
		if(scc[i] == scc[i + n]){
			cout << "NO" << '\n';
			return 0;
		}
	}
	cout << "YES" << '\n';
	return 0;
}
```

---

## 作者：hjhAKIOI (赞：0)

# Katu Puzzle

## 题意分析

题目可以简化为：有 $n$ 个变量 $X_1,X_2,\cdots,X_n$，每个变量可取 $0$ 或 $1$。给定一些二元关系，问是否存在一组解满足所有关系。这其实是一个 **2-SAT** 模型。

## 做题思路

[2-SAT 模板题](https://www.luogu.com.cn/problem/P4782)

有了前置知识，这道题就不难了。

我们不妨分别考虑每个运算。

在这里，我们设节点 $a$ 表示变量 $X_a$ 取 $0$，节点 $a+n$ 表示变量 $X_a$ 取 $1$。

1. 或（OR）运算。

   若条件为 $X_a \mid X_b=1$，则说明若 $X_a=0$，则 $X_b=1$，所以连边 $(a,b+n)$。同理连边 $(b,a+n)$。

   若条件为 $X_a \mid X_b=0$，则说明 $X_a=X_b=0$。这可以用两条有向边描述，即若 $X_a$ 或 $X_b$ 取 $1$，直接产生矛盾。即连边 $(a+n,a)$ 和 $(b+n,b)$。

3. 与（AND）运算。

   若条件为 $X_a \& X_b=0$，则说明若 $X_a=1$，则 $X_b=0$，所以连边 $(a+n,b)$。同理连边 $(b+n,a)$。

    若条件为 $X_a \& X_b=1$，则说明若 $X_a=X_b=1$。类似上面 $X_a \mid X_b=0$ 连边 $(a,a+n)$ 和 $(b,b+n)$。

4. 异或（XOR）运算。

    若条件为 $X_a \oplus X_b=0$，则说明若 $X_a=0$，则 $X_b=0$，所以连边 $(a,b)$。同理连边 $(b,a)$。同时若 $X_a=1$，则 $X_b=1$，所以连边 $(a+n,b+n)$。同理连边 $(b+n,a+n)$。

   若条件为 $X_a \oplus X_b=1$，则说明若 $X_a=0$，则 $X_b=1$，所以连边 $(a,b+n)$。同理连边 $(b,a+n)$。同时若 $X_a=1$，则 $X_b=0$，所以连边 $(a+n,b)$。同理连边 $(b+n,a)$。

连完边后，按 2-SAT 的过程，用 tarjan 算法求出强连通分量，检查是否存在 $i\in [1,n]$ 满足 $i$ 和 $i+n$ 在同一个强连通分量中。若存在，则无解。否则有解。

于是，问题愉快的解决了。

## 时间/空间复杂度

### 时间复杂度

tarjan 算法的时间复杂度为 $O(n+m)$，检查的时间为 $O(n)$，所以一共是 $O(n+m)$ 的时间复杂度，可以通过本题。

### 空间复杂度

tarjan 算法需要 $O(n)$ 的额外空间，存图需要 $O(n+m)$ 的空间，所以总空间复杂度为 $O(n+m)$，可以通过本题。

## 实现细节

由于异或运算会加 $4$ 条边，所以边的空间要开 $4$ 倍。同时每个点被拆成了两个，所以点的空间要开两倍。

---

至此，所有问题得到了解决。

下面给出本题的 AC 代码：

```cpp
#include<iostream>
using namespace std;
const int N=105,M=1e4+5;
int n,m,tot,num,top,cnt;
int head[N<<1],ver[M<<2],Next[M<<2];
int dfn[N<<1],low[N<<1],st[N<<1],c[N<<1];
bool ins[N<<1];

void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x){
	dfn[x]=low[x]=++num;
	st[++top]=x;
	ins[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		cnt++;
		int y;
		do{
			y=st[top--];
			ins[y]=0;
			c[y]=cnt;
		}while(x!=y);
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b,c;
		char op[4];
		cin>>a>>b>>c>>op;
		a++;
		b++;
		if(op[0]=='A'){  //AND
			if(c){
				add(a,a+n);
				add(b,b+n);
			}
			else{
				add(a+n,b);
				add(b+n,a);
			}
		}
		if(op[0]=='O'){   //OR
			if(c){
				add(a,b+n);
				add(b,a+n);
			}
			else{
				add(a+n,a);
				add(b+n,b);
			}
		}
		if(op[0]=='X'){   //XOR
			if(c){
				add(a,b+n);
				add(b,a+n);
				add(a+n,b);
				add(b+n,a);
			}
			else{
				add(a,b);
				add(b,a);
				add(a+n,b+n);
				add(b+n,a+n);
			}
		}
	}
	for(int i=1;i<=n<<1;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(c[i]==c[i+n]){  //检查是否有解
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：donaldqian (赞：0)

1. 什么是 2-SAT？大概就是给你一些约束例如：若 $a=1$，则 $b\neq 1$ 等等，然后让你构造解。
2. 转化成图论。例如本题，我们把 $a=0$ 的状态看做 $a$ 点，$a=1$ 的状态看做 $a+n$ 点。对于一个“若 $a=1$，则 $b=0$ 的条件”，我们把它看做 $(a+n,b)$ 的边。
3. 判断是否有解。容易发现，如果我们最开始假设 $a=1$，经过一些边走到了 $a=0$ 那一定不合法。进一步地，如果 $a=0$、$a=1$（也就是 $a$ 和 $a+n$ 点）在同一个强连通分量里，则一定无解。
4. tarjan 即可。

对于这道题，假如我们要求 $a\&b=1$，那么 $a$ 一定取 $1$，$b$ 一定取 $1$，连边 $(a,a+n)$、$(b,b+n)$。假如我们要求 $a\&b=0$，那么如果 $a=1$，一定 $b=0$；如果 $b=1$，一定 $a=0$，连边 $(a+n,b)$、$(b+n,a)$。其他情况同理。

[代码](https://www.luogu.com.cn/record/189136100)。

---

## 作者：_jimmywang_ (赞：0)

拆位，每个点都能选 0 或选 1，按位操作使得选择之间有依赖关系。因此想到 **2-SAT**。

记 $u_0,u_1$ 分别表示点 $u$ 选择 0 或选择 1 所代表的点。连边抽象为 $(u,v,w)$，其中拆位完以后 $w \in \{0,1\}$。

下文记 $u_0 \to v_1$ 为：若 $u$ 选择 0，则 $v$ 必须选择 1 这样的限制。这不仅是逻辑上的关系，也是连边的方式。

- $\text{AND}$：

    - $w=0$：$(u_1 \to v_0),(v_1 \to u_0)$。
    - $w=1$：$(u_1 \to v_1),(v_1 \to u_1), (u_0 \to u_1),(v_0 \to v_1)$。

- $\text{OR}$：

  - $w=0$：$(u_0 \to v_0),(v_0 \to u_0), (u_1 \to u_0),(v_1 \to v_0)$。
  - $w=1$：$(u_0 \to v_1),(v_0 \to u_1)$。
      
- $\text{XOR}$：

  - $w=0$：$(u_0 \to v_0),(v_0 \to u_0), (u_1 \to v_1),(v_1 \to u_1)$。
  - $w=1$：$(u_0 \to v_1),(v_0 \to u_1), (u_1 \to v_0),(v_1 \to u_0)$。

解释一下同边连边 $u_0\to u_1$，这意味着 $u$ 只能取 1。

然后跑 2-SAT 判定即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace binom{
	const ll Lim=300010,mod=998244353;
	ll jc[Lim],inv[Lim],inc[Lim];
	void pre(){
		jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
		f(i,2,Lim-1)jc[i]=jc[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod,
		inc[i]=inc[i-1]*inv[i]%mod;
	}ll C(ll n,ll m){if(n<0||m<0||n<m)return 0;return jc[n]*inc[m]%mod*inc[n-m]%mod;}
}
// using namespace binom;
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m;
ll dfn[100010],low[100010],cur;
ll bel[100010],scc;
ll st[100010],tp;
bool ins[100010];
vi e[100010];
void dfs(ll u){
	dfn[u]=low[u]=++cur;
	st[++tp]=u,ins[u]=1;
	fe(i,e[u]){
		ll v=e[u][i];
		if(!dfn[v])dfs(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],dfn[v]);
	}if(low[u]==dfn[u]){
		scc++;ll now;while(1){
			now=st[tp--];
			ins[now]=0,bel[now]=scc;
			if(now==u)break;
		}
	}
}
void clear(){
    f(i,1,2*n){
        e[i].clear();
        dfn[i]=low[i]=bel[i]=0;
        ins[i]=0;
    }tp=0;cur=0;scc=0;
}
ll U[10010],V[10010],W[10010],S[10010];
void add(ll u,ll v){e[u].pb(v);}
int main(){
	n=d,m=d;
    f(i,1,m){
        string c;cin>>U[i]>>V[i]>>W[i]>>c;
        U[i]++,V[i]++;
        if(c=="AND")S[i]=0;
        else if(c=="OR")S[i]=1;
        else if(c=="XOR")S[i]=2;
    }f(bit,0,63){
        clear();
        f(i,1,m){
            ll u=U[i],v=V[i],w=W[i],s=S[i];
            w=(bool)((w>>bit)&1);
            if(s==0){
                if(w==0)add(u+n,v),add(v+n,u);
                else add(u+n,v+n),add(v+n,u+n),add(u,u+n),add(v,v+n);
            }if(s==1){
                if(w==0)add(u+n,u),add(v+n,v),add(u,v),add(v,u);
                else add(u,v+n),add(v,u+n);
            }if(s==2){
                if(w==0)add(u,v),add(v,u),add(u+n,v+n),add(v+n,u+n);
                else add(u,v+n),add(v,u+n),add(u+n,v),add(v+n,u);
            }
        }f(i,1,2*n)if(!dfn[i])dfs(i);
        f(i,1,n)if(bel[i]==bel[i+n]){puts("NO");return 0;}
    }puts("YES");
	return 0;
}
```

---

## 作者：osfly (赞：0)

2-SAT 练习题。

考虑以下的连边方式：

$$
\left\{
\begin{aligned}
a\ \text{AND}\ b =0&\Rightarrow\ (a=1)\rightarrow (b=0),\ (b=1)\rightarrow (a=0)\\
a\ \text{AND}\ b =1&\Rightarrow\ (a=1)\leftrightarrow (b=1)\\
a\ \text{OR}\ b =0&\Rightarrow\ (a=0)\leftrightarrow (b=0)\\
a\ \text{OR}\ b =1&\Rightarrow\ (a=0)\rightarrow (b=1),\ (b=0)\rightarrow (a=1)\\
a\ \text{XOR}\ b =0&\Rightarrow\ (a=1)\leftrightarrow (b=1),\ (b=0)\leftrightarrow (a=0)\\
a\ \text{XOR}\ b =1&\Rightarrow\ (a=1)\leftrightarrow (b=0),\ (b=1)\leftrightarrow (a=0)\\
\end{aligned}
\right.
$$

但是这样会有一个问题：

```
2 2
0 1 1 AND
0 1 0 OR
```

答案应该是 $\texttt{NO}$，所以我们添加一个虚点 $\text{T}$。

如果 $(a=x)$ 连向 $\text{T}$，则 $(a=x)$ 为真。

并且改一下连边方式：

$$
\left\{
\begin{aligned}
a\ \text{AND}\ b =0&\Rightarrow\ (a=0)\rightarrow (b=0),\ (b=0)\rightarrow (a=0)\\
a\ \text{AND}\ b =1&\Rightarrow\ (a=1)\leftrightarrow T,\ (b=1)\leftrightarrow T\\
a\ \text{OR}\ b =0&\Rightarrow\ (a=0)\leftrightarrow T,\ (b=0)\leftrightarrow T\\
a\ \text{OR}\ b =1&\Rightarrow\ (a=0)\rightarrow (b=1),\ (b=0)\rightarrow (a=1)\\
a\ \text{XOR}\ b =0&\Rightarrow\ (a=1)\leftrightarrow (b=1),\ (b=0)\leftrightarrow (a=0)\\
a\ \text{XOR}\ b =1&\Rightarrow\ (a=1)\leftrightarrow (b=0),\ (b=1)\leftrightarrow (a=0)\\
\end{aligned}
\right.
$$

`tarjan` 缩点后判断 $\forall i\in[0,n-1],\ (i=0)$ 和 $(i=1)$ 不在同个强连通分量内即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=1e6+10;

struct edge
{
	int u,v,nxt;
}e[N<<1];
int head[N],tot;
void add(int u,int v)
{
	e[++tot]=edge{u,v,head[u]};
	head[u]=tot;
}

int n,m;

int sta[N],top,vis[N],id[N];
int dfn[N],low[N],cur,cnt;

void tarjan(int u)
{
	dfn[u]=low[u]=++cur;
	sta[++top]=u,vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(vis[v]) low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u])
	{
		int v;cnt++;
		do
		{
			v=sta[top--];
			id[v]=cnt;
			vis[v]=0;
		}while(u!=v);
	}
}

int chk()
{
	for(int i=1;i<=n;i++)
		if(id[i]==id[i+n]) return 0;
	return 1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;char str[10];
		scanf("%d %d %d %s",&a,&b,&c,str+1);
		a++,b++;
		if(str[1]=='A')
		{
			if(c) add(a,0),add(0,a),add(b,0),add(0,b);
			else add(a,b+n),add(b,a+n);
		}
		if(str[1]=='O')
		{
			if(c) add(a+n,b),add(b+n,a);
			else add(a+n,0),add(0,a+n),add(b+n,0),add(0,b+n);
		}
		if(str[1]=='X')
		{
			if(c) add(a,b+n),add(b+n,a),add(a+n,b),add(b,a+n);
			else add(a,b),add(b,a),add(a+n,b+n),add(b+n,a+n);
		}
	}
	for(int i=0;i<=n<<1;i++)
		if(!dfn[i]) tarjan(i);
	printf(chk()?"YES":"NO");
	return 0;
}
```

---

