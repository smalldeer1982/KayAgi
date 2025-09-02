# [KTSC 2021] 铁路 / railroad

## 题目背景

本题翻译自 [2021년도 국제정보올림피아드 대표학생 선발고사](https://www.ioikorea.or.kr/archives/ioitst/2021/) 1차 선발고사 [#4 철도](https://assets.ioikorea.or.kr/ioitst/2021/1/railroad/railroad_statement.pdf)。

受评测技术限制，本题采用交互题实现，即两个函数会在同一次运行中被调用。

**请注意，你不需要也不应该实现 `main` 函数。具体实现方式见【实现细节】部分。**

提交时，请在程序开头添加如下内容，并且无需引用 `railroad.h`：

```cpp
#include <vector>
#include <utility>

std::vector< std::pair<int, int> > encode_map(int N, int K, int &X, std::vector< std::pair<int, int> > E);
std::vector< std::pair<int, int> > decode_map(int N, int K, int X, std::vector< std::pair<int, int> > E);
```


**警告：滥用本题评测将被封号。**

## 题目描述

有两个关系恶劣的国家 A 和 B。A 国为了侵略 B 国，试图获取 B 国的铁路网络信息。

A 国多次派遣间谍，但总是在获取有意义的信息前被捕，因此 A 国目前掌握的信息仅有以下内容：

- B 国的铁路网络由 $N$ 个车站组成，每个车站编号为 $1$ 到 $N$。
- 任意两个不同的车站之间要么直接通过铁路相连，要么通过其他车站（一个或多个）间接相连。
- 任意两个车站之间只有唯一的一条路径相连。
- 不存在车站与自身直接相连的铁路。

意识到派遣间谍的局限性后，A 国决定收买 B 国铁路公司的高管，以获取铁路网络图。为了避免暴露叛徒身份，叛徒会对图纸进行如下修改：

1. 在铁路网络图上添加 $K$ 条假铁路。即，选择图中原本不直接相连的两个车站 $a$ 和 $b$，用假铁路将它们直接连接。此操作重复 $K$ 次。
2. 在其中一个车站上做**特殊标记**。
3. 最后，抹去所有车站的编号。

叛徒将最终修改后的图纸发送给 A 国。仅凭这些信息，很难判断图纸是 B 国的铁路网络图，因此无人会察觉信息泄露。

为了使计划成功，需要解决以下问题：

- A 国收到的图纸中车站编号被抹去，且无法区分真假铁路。唯一可知的是哪个车站有**特殊标记**，以及假铁路的总数为 $K$ 条。
- 因此，发送方需要在图纸中以适当方式添加假铁路，并选择适当的车站做**特殊标记**，以便接收方仅凭图纸就能区分真假铁路。
- 接收方需要理解发送方的修改方法，并从收到的图纸中还原出原始铁路网络图。

如上所述，需要一个用于修改铁路网络图的函数和一个从图纸中还原原始铁路网络的函数。A 国将这项任务交给了你。

### 实现细节

你需要实现以下两个函数：

```cpp
vector< pair<int, int> > encode_map(int N, int K, int &X, vector< pair<int, int> > E)
```

- 参数 $N$ 表示 B 国铁路网络中的车站数量 $N$。所有车站用 $1$ 到 $N$ 的整数表示。
- 参数 $K$ 表示需要添加的假铁路数量 $K$。
- 参数 $X$ 用于记录特殊标记的车站编号。函数结束时，$X$ 必须存储一个 $1$ 到 $N$ 之间的整数。
- 参数 $E$ 是一个大小为 $N-1$ 的数组，表示 B 国的铁路网络。每个二元组 $(a, b)$ 表示车站 $a$ 和 $b$ 直接通过铁路相连。
- 此函数返回一个包含 $K$ 个二元组 $(a, b)$ 的数组，表示添加的假铁路连接的车站。无论是真铁路还是假铁路，都不能重复连接同一对车站。

```cpp
vector< pair<int, int> > decode_map(int N, int K, int X, vector< pair<int, int> > E)
```

- 参数 $N$ 表示B国铁路网络中的车站数量 $N$。由于车站编号被抹去，此函数中使用的编号可能与原始编号不同（即通过某种双射函数重新编号）。
- 参数 $K$ 表示添加的假铁路数量 $K$。
- 参数 $X$ 表示带有特殊标记的车站编号。
- 参数 $E$ 是一个大小为 $N+K-1$ 的数组，表示 A 国收到的图纸。每个二元组 $(a, b)$ 表示车站 $a$ 和 $b$ 直接通过真或假铁路相连。注意，$E$ 中元素是无序的。
- 此函数从 `encode_map` 生成的图纸中还原原始铁路网络，返回一个大小为 $N-1$ 的数组，包含 B 国的真实铁路网络。

提交的源代码中不得执行任何输入输出函数。

每个测试用例包含一个或多个独立场景。对于一个包含 $T$ 个场景的测试用例，调用上述函数的程序将按以下方式执行两次：

第一次执行时：

- `encode_map` 函数被调用 $T$ 次。
- `encode_map` 函数的执行结果被评分系统保存。
- `decode_map` 函数不会被调用。

第二次执行时：

- `decode_map` 函数被多次调用。每次调用时随机选择一个场景，并将该场景中 `encode_map` 生成的图纸作为输入。
- `encode_map` 函数不会被调用。

本题的程序运行时间和内存使用量以两次执行的总和计算。


## 说明/提示

### 约束条件

- $1 \leq T \leq 200$
- $3 \leq N \leq 200$
- $1 \leq K < \frac{N}{2}$

### 子任务

1. （$4$ 分）
   - $N \leq 4$
2. （$13$ 分）
   - $K = 1$
3. （$11$ 分）
   - 每个车站连接的铁路不超过两条。
4. （$29$ 分）
   - 任意一个车站最多通过 $\lfloor \frac{N}{2} \rfloor$ 条铁路可以到达另一个任意车站。
5. （$43$ 分）
   - 无额外约束。

### 评分标准

只有当 `encode_map` 生成的图纸正确，且 `decode_map` 准确还原铁路网络时，该数据点才被视为正确。特别地，如果 `decode_map` 返回的数组中包含任何假铁路，则该数据点得分为 $0$。两个函数返回的数组中元素的顺序不重要。

注意：每个子任务的得分是该子任务所有数据点得分的最小值。

### 示例

- 考虑当 $N=6$，$K=1$，铁路 $E=[(1,2),(1,3),(1,4),(4,5),(4,6)]$ 的情形时：

  评分系统调用以下函数：

  ```cpp
  encode_map(6, 1, X, [(1,2), (1,3), (1,4), (4,5), (4,6)])
  ```

  左图为 B 国的铁路网络。添加假铁路 $(4,2)$ 并在 $1$ 号车站做特殊标记后，得到右图。此时，`encode_map` 返回 $[(4,2)]$，且 $X$ 存储为 $1$。其他答案也可能存在。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/htrfiyns.png)

  接着，评分系统调用以下函数（注意最后一个参数的顺序可能变化）：

  ```cpp
  decode_map(6, 1, 2, [(1,5), (2,3), (2,4), (2,5), (3,5), (5,6)])
  ```

  输入对应的图如下（注意车站编号与 `encode_map` 中不同）。此函数返回 $[(3,2),(4,2),(5,6),(1,5),(5,2)]$，元素顺序可变化。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/90h8t153.png)

  此示例满足子任务 $2, 4, 5$ 的条件。


## 样例 #1

### 输入

```
2
6 1
1 2
1 3
1 4
4 5
4 6
5 2
2 3
4 3
4 5
1 3```

### 输出

```
```

# 题解

## 作者：ainivolAGEM (赞：1)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/article/29xobtf5)

## 题意

[题目](https://www.luogu.com.cn/problem/P11978)给出一颗 $N$ 个点的树，要求设计一种方案，在上面添加 $K$ 条边（要求原本不相连），可以将一个点标记，并且将全部点重新编号；然后在这个新图中以之前的信息复原出原树，即删除全部添加的边。

## 分析

首先，如果重新编号所有点变成图的话我们就无法确认原来的根、叶子之类的节点，所以我们考虑先把所有 $K$ 条边的一端都接在同一个节点上，我们称该节点为“总节点”。但如果直接标记该节点会发现我们无法得知与该点相连的是原来的树还是新加的边。我们尝试以别的方式确认那个点。

我们发现，如果我们把总节点放在一个叶子节点，那么该点相连的边有 $K + 1$ 条，会比较好确认，因为叶子节点是树中相连边最少的点。那么我们标记叶子节点的父亲节点，不仅同时确认总节点的位置也确认哪个是原树边，会是一个比较好的方案。

但其实还有个问题，如果还有一个与标记节点直接相连的点原本也连接了 $K + 1$ 条边的话，我们怎么确认哪个是真的叶子节点呢？考虑以下情况：

- 如果是与总节点同父亲的节点，那么可证明我们必定有比当前总节点深度更大的叶子节点，我们选择深度最大的叶子节点作为总节点就可以让所有同父亲叶子节点都只连 $1$ 条边，也就不可能达到 $K +1$。

- 如果是标记节点的父亲节点，由于 $K \leq 1$，我们可以直接将其中一条新边连接总节点和标记节点的父亲节点，那么我们就可以辨认哪个是总节点了。

还有一个小的误区：对于 $K = 1$ 的情况，如果总节点连接了与其同父亲的另一个节点，那么两者相连边数量一致，如何判断哪个是总节点呢？其实不用判断啊，反正 $K = 1$，只要找出相连的一条新边即可。

## AC code


```cpp
#include<bits/stdc++.h>
#include<utility>
using namespace std;
typedef int ll;
typedef pair<ll,ll> pir;
const int N=304;
ll rt,id,tid,mdep,d[N];
ll tot,head[N];
struct Edge{
	ll to,nxt;
}e[N<<1];
void add_edge(ll u,ll v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
void init(){
	for(int i=1;i<=tot;i++){
		e[i].to=e[i].nxt=0;
	}
	rt=id=tid=mdep=tot=0;
	memset(head,0,sizeof(head));
	memset(d,0,sizeof(d));
}
void dfs(ll u,ll fa,ll dep){
	bool flag=true;
	for(int i=head[u];i;i=e[i].nxt){
		ll v=e[i].to;
		if(v==fa){
			d[u]++;
			continue;
		}
		dfs(v,u,dep+1);
		flag=false;
		d[u]++;
	}
	if(flag&&dep>mdep){
		id=u;
		rt=fa;
		mdep=dep;
	}
}
vector<pir> encode_map(ll N,ll K,ll &X,vector<pir> E){
	init();
	for(int i=0;i<E.size();i++){
		add_edge(E[i].first,E[i].second);
		add_edge(E[i].second,E[i].first);
	}
	dfs(1,0,1);
	vector<pir> ans;
	X=rt;
	for(int i=head[rt];i;i=e[i].nxt){
		ll v=e[i].to;
		if(d[v]!=1){
			if(d[v]-1==K){
				ans.push_back(make_pair(v,id));
			}
			tid=v;
		}
	}
	for(int i=1;ans.size()<K;i++){
		if(i!=rt&&i!=id&&i!=tid){
			ans.push_back(make_pair(id,i));
		}
	}
	return ans;
}
vector<pir> decode_map(ll N,ll K,ll X,vector<pir> E){
	init();
	for(int i=0;i<E.size();i++){
		add_edge(E[i].first,E[i].second);
		add_edge(E[i].second,E[i].first);
	}
	for(int i=head[X];i;i=e[i].nxt){
		ll v=e[i].to;
		for(int j=head[v];j;j=e[j].nxt){
			d[v]++;
		}
		if(d[v]-1==K){
			id=v;
		}
	}
	vector<pir> ans;
	for(int i=0;i<E.size();i++){
		if(E[i].first==id||E[i].second==id){
			if(E[i].first!=X&&E[i].second!=X){
				continue;
			}
		}
		ans.push_back(make_pair(E[i].first,E[i].second));
	}
	return ans;
}
```

### 一些易错点：

- 在统计与之相连的边数时别忘记考虑根节点。

- **通信题，别写错了，真的。**

- 记得初始化。

---

