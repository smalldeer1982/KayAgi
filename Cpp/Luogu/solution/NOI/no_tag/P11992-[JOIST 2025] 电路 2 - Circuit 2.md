# [JOIST 2025] 电路 2 / Circuit 2

## 题目背景

请使用 C++ 17 / C++ 20 提交。

**不要** `#include "circuit.h"`。

请在文件头粘贴如下的语句：

```cpp
#include <string>
#include <vector>

std::string solve(int N, int R, std::vector<int> U, std::vector<int> V);

int query(std::string s);
```

## 题目描述

**这是一道交互题。本题中，交互库是非自适应的。**

JOI 君正在玩一个电子积木。  

该电子积木由 $N$ 个 $\texttt{AND}$ 组件、$N$ 个 $\texttt{OR}$ 组件和一个电路板组成。电路板包含 $2N + 1$ 个开关和 $N$ 个组件插槽，每个组件插槽可以放置一个 $\texttt{AND}$ 组件或 $\texttt{OR}$ 组件。根据放置的组件和开关状态，电路板会输出 $0$ 或 $1$。

### 电路说明

- 每个开关被分配一个从 $0$ 到 $2N$ 的编号，且每个开关有 $\texttt{ON}$（开启）或 $\texttt{OFF}$（关闭）两种状态。每个开关会按以下规则输出 $0$ 或 $1$。
- 每个组件插槽被分配一个从 $0$ 到 $N - 1$ 的编号。每个组件插槽也会按以下规则输出 $0$ 或 $1$。
- 每个开关和组件插槽的输出值按**从高编号到低编号的顺序**确定。若开关和组件插槽编号相同，则**先确定组件插槽的输出值**。
    - 对于 $j = 2N, 2N - 1, \ldots, N$ 的开关：
        - 若开关 $j$ 为 $\texttt{OFF}$，则输出 $0$。
        - 若开关 $j$ 为 $\texttt{ON}$，则输出 $1$。

    - 对于 $j = N - 1, N - 2, \ldots, 0$ 的开关：
        - 设组件插槽 $j$ 的输出值为 $x$。
        - 若开关 $j$ 为 $\texttt{OFF}$，则输出 $x$。
   		- 若开关 $j$ 为 $\texttt{ON}$，则输出 $1 - x$。
    - 对于组件插槽 $i = N - 1, N - 2, \ldots, 0$：
        - 它连接到两个开关 $U_i$ 和 $V_i$（满足 $i < U_i < V_i \leq 2N$）。
        - 设开关 $U_i$ 的输出为 $x$，开关 $V_i$ 的输出为 $y$。
        - 若组件插槽 $i$ 放置的是 $\texttt{AND}$ 组件，则输出 $\min(x, y)$。
        - 若组件插槽 $i$ 放置的是 $\texttt{OR}$ 组件，则输出 $\max(x, y)$。
- 对于每个 $j = 1, 2, \ldots, 2N$，存在且仅存在一个 $i$（$0 \leq i \leq N - 1$）满足 $U_i = j$ 或 $V_i = j$。
- 电路板的最终输出值等于开关 $0$ 的输出值。

当 $N=3$，且 $U_0=1, V_0=2, U_1=3, V_1=4, U_2=5, V_2=6$ 时，若在组件插槽 $0$ 和 $1$ 放置 $\texttt{AND}$ 组件，在组件插槽 $2$ 放置 $\texttt{OR}$ 组件，其电路结构如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/pyxqah4j.png)


JOI 君原本试图在所有组件插槽中放置 $\texttt{AND}$ 组件，但实际混入了最多 $R$ 个 $\texttt{OR}$ 组件。由于两种组件外观相同，必须通过电路板的输出值来识别。你的任务是通过最多 $1000$ 次查询，确定哪些组件插槽包含 $\texttt{OR}$ 组件。每次查询的格式为：

- 指定所有 $2N + 1$ 个开关的状态。
- JOI 君将根据此配置返回电路板的输出值。

请根据电路板的连接结构和 $\texttt{OR}$ 组件的数量上限，编写一个程序来解决此问题。

### 实现细节

你不需要，也不应该实现 `main` 函数。你应当实现以下的函数：

```cpp
std::string solve(int N, int R, std::vector<int> U, std::vector<int> V)
```
- 此函数在每个测试点中**仅被调用一次**。
- 参数 `N` 表示组件插槽的数量 $N$。
- 参数 `R` 表示 $\texttt{OR}$ 组件的数量上限 $R$。
- 参数 `U` 和 `V` 是长度为 $N$ 的数组，其中 `U[i]` 和 `V[i]`（$0 \leq i \leq N - 1$）表示组件插槽 $i$ 连接的开关编号 $U_i$ 和 $V_i$。
- 此函数必须返回一个长度为 $N$ 的字符串 `t`，且满足以下条件：
  - 对每个 $i = 0, 1, \ldots, N - 1$，若组件插槽 $i$ 包含 $\texttt{AND}$ 组件，则 `t[i]` 必须为 $\texttt{\&}$（`&`）；若包含 $\texttt{OR}$ 组件，则 `t[i]` 必须为 $\texttt{|}$（`|`）。
- 若返回的字符串 `t` 长度不为 $N$，程序将被判为 $\texttt{Wrong Answer [1]}$。
- 若 `t` 包含 $\texttt{\&}$ 或 $\texttt{|}$ 以外的字符，程序将被判为 $\texttt{Wrong Answer [2]}$。
- 若实际组件类型与 `t` 描述不符，程序将被判为 $\texttt{Wrong Answer [3]}$。

你可以调用以下的函数：

```cpp
int query(std::string s)
```

- 此函数用于向 JOI 君发起查询。
- 参数 `s` 必须是一个长度为 $2N + 1$ 且仅由 `'0'` 和 `'1'` 组成的字符串。对每个 $j = 0, 1, \ldots, 2N$：
  - 若 `s[j]` 为 $\texttt{0}$，则开关 $j$ 设为 $\texttt{OFF}$；
  - 若 `s[j]` 为 $\texttt{1}$，则开关 $j$ 设为 $\texttt{ON}$。
- 若 `s` 长度不为 $2N + 1$，程序将被判为 $\texttt{Wrong Answer [4]}$。
- 若 `s` 包含 `'0'` 或 `'1'` 以外的字符，程序将被判为 $\texttt{Wrong Answer [5]}$。
- 此函数最多调用 $1000$ 次。若超过此限制，程序将被判为 $\texttt{Wrong Answer [6]}$。
- 函数返回值是按 `s` 配置开关后电路板的输出值。


### 注意事项
- 你可以定义额外的辅助函数或全局变量以供内部使用。
- 你的程序不得使用标准输入/输出或其他文件交互，但可将调试信息输出到标准错误流。
- 实际评测程序是非自适应的（non-adaptive），即交互过程开始时答案已固定。



### 编译运行

你可以从【附件】中下载包含 Sample Grader 的压缩文件以测试程序。压缩文件中还包含一个示例源代码文件。

Sample Grader 为 `grader.cpp`。测试时需将 `grader.cpp`、`circuit.cpp` 和 `circuit.h` 置于同一目录。使用以下命令编译：
```bash
g++ -std=gnu++20 -O2 -o grader grader.cpp circuit.cpp
```
或执行压缩包中的 `compile.sh` 脚本。
```bash
./compile.sh
```
编译成功后，将生成可执行文件 `grader`。

注意：实际评测程序与 Sample Grader 不同。 Sample Grader 以单进程运行，从标准输入读取数据并将结果写入标准输出。


## 说明/提示


### 样例交互

#### 样例交互 $1$

| 交互库调用 | 返回值 | 选手程序调用  | 返回值 |
|-----------------------------------|------------------|-------------------------|------------------|
| `solve(1, 1, [1], [2])`           |                  |                         |                  |
|                                   |                  | `query("010")`          | $1$                |
|                                   |                  | `query("011")`          | $1$                |
|                                   |                  | `query("111")`          | $0$                |
|                                   | "$\texttt{\char124}$"  | | |


首次调用 `query` 时的输出计算过程：  

- 开关 $1$ 设为 $\texttt{ON}$，开关 $2$ 设为 $\texttt{OFF}$，因此开关 $1$ 输出 $1$，开关 $2$ 输出 $0$。  
- 组件插槽 $0$ 包含 $\texttt{OR}$ 组件，连接的开关 $1$ 和 $2$ 分别输出 $1$ 和 $0$，因此组件插槽 $0$ 输出 $\max(1, 0) = 1$。  
- 开关 $0$ 设为 $\texttt{OFF}$，而组件插槽 $0$ 输出 $1$，因此开关 $0$ 输出 $1$。  
- 最终，电路板的输出为 $1$。  

该样例满足所有子任务的限制。  

#### 样例交互 $2$

| 交互库调用    | 返回值 | 选手程序调用            | 返回值 |
|------------------------------------------|------------------|----------------------------|------------------|
| `solve(3, 3, [1, 3, 5], [2, 4, 6])`       |                  |                            |                  |
|                                          |                  | `query("0001001")`         | $0$                |
|                                          |                  | `query("0001110")`         | $1$                |
|                                          |                  | `query("0000011")`         | $0$                |
| | "$\texttt{\&\&\char124}$"  |         |     |


题目描述中的电路图对应此示例。

该样例满足子任务 $3,6\sim 9$ 的限制。

附件中：  
- $\texttt{sample-01-in.txt}$ 对应样例 1；
- $\texttt{sample-02-in.txt}$ 对应样例 2；
- $\texttt{sample-03-in.txt}$ 满足子任务 $3,4,5,8,9$ 的限制；
- $\texttt{sample-04-in.txt}$ 满足子任务 $3,6\sim 9$ 的限制。


### 数据范围

- $1 \leq N \leq 8\,000$；
- $1 \leq R \leq \min(N, 120)$；
- 对每个 $i$（$0 \leq i \leq N - 1$），满足 $i < U_i < V_i \leq 2N$；
- 对于每个 $j = 1, 2, \ldots, 2N$，存在且仅存在一个 $i$（$0 \leq i \leq N - 1$）满足 $U_i = j$ 或 $V_i = j$。


### 子任务

- $\text{Subtask 1 (1 pts)}$：$N = 1$；
- $\text{Subtask 2 (4 pts)}$：$N \leq 1\,000$ 且 $R = 1$；
- $\text{Subtask 3 (5 pts)}$：$N \leq 1\,000$；
- $\text{Subtask 4 (17 pts)}$：$U_i = i + 1$，$V_i = N + 1 + i$（$0 \leq i \leq N - 1$），且 $R \leq 70$；
- $\text{Subtask 5 (8 pts)}$：$U_i = i + 1$，$V_i = N + 1 + i$（$0 \leq i \leq N - 1$）；
- $\text{Subtask 6 (23 pts)}$：$U_i = 2i + 1$，$V_i = 2i + 2$（$0 \leq i \leq N - 1$），且 $R \leq 70$；
- $\text{Subtask 7 (8 pts)}$：$U_i = 2i + 1$，$V_i = 2i + 2$（$0 \leq i \leq N - 1$）；
- $\text{Subtask 8 (27 pts)}$：$R \leq 70$；
- $\text{Subtask 9 (7 pts)}$：无额外限制。





## 样例 #1

### 输入

```
1 1
1 2
|```

### 输出

```
|```

## 样例 #2

### 输入

```
3 3
1 2
3 4
5 6
&&|```

### 输出

```
&&|```

# 题解

## 作者：cwfxlh (赞：0)

## [P11992 [JOIST 2025] 电路 2 / Circuit 2](https://www.luogu.com.cn/problem/P11992)    

可能没有黑啊，感觉不太难。    

先考虑没有次数限制，胡一个简单的做法。     

我们尝试从上往下确定符号。考虑怎么区分一个节点是 $\texttt{AND}$ 还是 $\texttt{OR}$，显然可以通过输入 $01$ 来确认。如果是 $\texttt{AND}$，输出就是 $0$，否则是 $1$。但是发现，如果返回值的位置不是根节点，是无法读取返回值的。考虑怎么通过确定的元件来把这个值保留地传到根节点。如果接下来一个元件是 $\texttt{OR}$，在这个元件的另一侧传入 $0$。否则将这个返回值取反，在另一侧传入 $1$，同时最终的值取个反。      

上面操作涉及到一个问题：怎么做到在传入固定的值。这是简单的，将子树内所有输入全部改为 $0$ 或全部改为 $1$。      

这样就做到了线性。确认好的点构成了一个包含根的连通块，每次加入一个儿子，可以确定这个儿子的编号。     

考虑能不能更高效一点。我们每次取若干个点，判断其中有没有 $\texttt{OR}$，然后这样就可以二分了。发现，这些点由于不知道符号，所以它们是不适合作为传递关键信息的节点的。     

尝试一点简单的结构：取若干条链，并且这些链的链头的祖先链与其他链都不相交。这样的话，对于每条链，我们尝试在链头给出返回值。具体做法如下：在链尾输入 $0$，然后在所有链的另一侧输入 $1$，这样如果里面有 $\texttt{OR}$，那么就会返回 $1$，否则返回 $0$。    

剩下的任务就是通过一些确定的符号将这些点的信息合并传到根部。考虑树形 DP 求转移方法，$dp_{i,j}$ 表示子树 $i$ 内的询问点是否有 $\texttt{OR}$ 时，返回的值是多少，要求 $dp_{i,0}$ 与 $dp_{i,1}$ 能够区分。通过做一些反转操作，容易发现这样是必然可以合并的。     

于是我们实现了询问。考虑具体该问哪些点，尝试这样做：每次在一个点集里二分第一个 $\texttt{OR}$。令当前确定符号的连通块为 $S$，考虑所有挂在 $S$ 上的链，选若干条长链出来，将这些长链拼在一起二分。但是这样二分的次数太多，设计一个阈值 $B$，每次最多选 B 个点二分。于是询问次数为 $O(R\log B+\frac{n-C}{B}+\sqrt{C})$。     

上面询问次数的分析如下：$R\log B$ 指每次二分出一个 $\texttt{OR}$ 所需的次数，剩余的情况就是指询问的所有点都没问题。考虑询问的时候有多少次没问满，令这些没问满的大小和为 $C$，那么问满的次数就是 $\frac{n-C}{B}$，没问满的那些，根据长链的性质，大小一定严格递减，所以询问次数不超过 $\sqrt{C}$。     

上面那个式子在 $C$ 取 $O(B^2)$ 大小的时候取到最大，不过那个界没有卡特别满，所以不需要特别精细的分析，我的代码里 $B$ 取了 60 就过了，最多的问了 920 次左右，比较充裕。询问一次时间复杂度是 $O(n)$ 的。    

代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
std::string solve(int NN, int RR, std::vector<int> U, std::vector<int> V);
int query(std::string s);
int n,R,ans[20003],fa[20003],k1,k2,k3,k4,k5,k6,k7,k8,k9,mxdep[20003],qrymk[20003],rev[20003],lft,rgt,mid;
int stk[20003],tots,dp[20003][2],dep[20003];
vector<int>son[20003];
void dfs(int now){
	mxdep[now]=now;
	for(auto i:son[now]){
		if(i>=n)continue;
		dfs(i);
		if(dep[mxdep[i]]>dep[mxdep[now]])mxdep[now]=mxdep[i];
		if(ans[now]!=-1&&ans[i]==-1){
			int u=tots;
			for(int j=mxdep[i];;j=fa[j]){
				stk[++tots]=j;
				if(j==i)break;
			}
			reverse(stk+u+1,stk+tots+1);
		}
	}
	if(ans[now]==-1&&now==0){
		int u=tots;
		for(int j=mxdep[now];;j=fa[j]){
			stk[++tots]=j;
			if(j==now)break;
		}
		reverse(stk+u+1,stk+tots+1);
	}
	return;
}
void mdf(int pos){
	dp[pos][0]^=1;dp[pos][1]^=1;rev[pos]^=1;
	return;
}
void dfs2(int now){
	if(now>=n){
		dp[now][0]=dp[now][1]=0;
		return;
	}
	int u=son[now][0],v=son[now][1];
	dfs2(u);dfs2(v);
	if(qrymk[now]){
		if(dp[v][0]==dp[v][1])swap(u,v);
		if(dp[u][0]==0)mdf(u);
		if(dp[v][0]==1)mdf(v);
		dp[now][0]=0;
		dp[now][1]=1;
	}
	else{
		if(dp[v][0]==dp[v][1])swap(u,v);
		if(dp[u][0]==dp[u][1]&&dp[v][0]==dp[v][1]){
			if(dp[u][0]==0)mdf(u);
			if(dp[v][0]==0)mdf(v);
			dp[now][0]=dp[now][1]=1;
			return;
		}
		if(dp[u][0]==dp[u][1]){
			if(ans[now]==0){if(dp[u][0]==0)mdf(u);}
			else if(dp[u][0]==1)mdf(u);
			dp[now][0]=dp[v][0];dp[now][1]=dp[v][1];
		}
		else{
			if(ans[now]==0){
				if(dp[u][0]==0)mdf(u);
				if(dp[v][0]==0)mdf(v);
				dp[now][0]=1;dp[now][1]=0;
			}
			else{
				if(dp[u][0]==1)mdf(u);
				if(dp[v][0]==1)mdf(v);
				dp[now][0]=0;dp[now][1]=1;
			}
		}
	}
	return;
}
int Query(int pos){
	for(int i=0;i<=n*2;i++)rev[i]=qrymk[i]=0;
	for(int i=1;i<=pos;i++)qrymk[stk[i]]=1;
	dfs2(0);
	string qs="";
	for(int i=0;i<=n*2;i++)qs+=(char)('0'+rev[i]);
	return (query(qs)==dp[0][1]);
}
string solve(int NN,int RR,vector<int> U,vector<int> V) {
	n=NN;R=RR;
	dep[0]=1;
	for(int i=0;i<n;i++){
		son[i].emplace_back(U[i]);
		son[i].emplace_back(V[i]);
		dep[U[i]]=dep[V[i]]=dep[i]+1;
		fa[U[i]]=fa[V[i]]=i;
	}
	for(int i=0;i<n;i++)ans[i]=-1;
	while(1){
		k1=1;
		for(int i=0;i<n;i++)if(ans[i]==-1)k1=0;
		if(k1)break;
		tots=0;
		dfs(0);
		tots=min(tots,60);
		if(!Query(tots)){
			for(int i=1;i<=tots;i++)ans[stk[i]]=0;
			continue;
		}
		lft=1;rgt=tots;
		while(lft<rgt){
			mid=((lft+rgt)/2);
			if(Query(mid))rgt=mid;
			else lft=mid+1;
		}
		for(int i=1;i<lft;i++)ans[stk[i]]=0;
		ans[stk[lft]]=1;
	}
	string ret="";
	for(int i=0;i<n;i++){
		if(ans[i])ret+='|';
		else ret+='&';
	}
    return ret;
}
```

---

