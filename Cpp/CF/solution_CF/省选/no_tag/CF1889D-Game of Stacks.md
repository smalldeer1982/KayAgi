# Game of Stacks

## 题目描述

You have $ n $ stacks $ r_1,r_2,\ldots,r_n $ . Each stack contains some positive integers ranging from $ 1 $ to $ n $ .

Define the following functions:

```
function init(pos):
    stacks := an array that contains n stacks r[1], r[2], ..., r[n]
    return get(stacks, pos)

function get(stacks, pos):
    if stacks[pos] is empty:
        return pos
    else:
        new_pos := the top element of stacks[pos]
        pop the top element of stacks[pos]
        return get(stacks, new_pos)
```

You want to know the values returned by $ \texttt{init(1)}, \texttt{init(2)}, \ldots, \texttt{init(n)} $ .

Note that, during these calls, the stacks $ r_1,r_2,\ldots,r_n $ don't change, so the calls $ \texttt{init(1)}, \texttt{init(2)}, \ldots, \texttt{init(n)} $ are independent.

## 说明/提示

In the first example:

- When you call $ \texttt{init(1)} $ , set $ \texttt{stacks := [[1,2,2],[3,1,2],[1,2,1]]} $ , and then call $ \texttt{get(stacks, 1)} $ . 
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1,2],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 3} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2,1]] $ , and then call $ \texttt{get(stacks, 3)} $ .
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[],[],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is empty, return $ 1 $ .
- When you call $ \texttt{init(2)} $ , set $ \texttt{stacks := [[1,2,2],[3,1,2],[1,2,1]]} $ , and then call $ \texttt{get(stacks, 2)} $ . 
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2,2],[3,1],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2,2],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 3} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[],[1,2,1]] $ , and then call $ \texttt{get(stacks, 3)} $ .
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is empty, return $ 2 $ .
- When you call $ \texttt{init(3)} $ , set $ \texttt{stacks := [[1,2,2],[3,1,2],[1,2,1]]} $ , and then call $ \texttt{get(stacks, 3)} $ . 
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1,2,2],[3,1,2],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1,2],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1],[3],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 3} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2]] $ , and then call $ \texttt{get(stacks, 3)} $ .
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is empty, return $ 2 $ .

## 样例 #1

### 输入

```
3
3 1 2 2
3 3 1 2
3 1 2 1```

### 输出

```
1 2 2```

## 样例 #2

### 输入

```
5
5 1 2 4 3 4
6 1 2 5 3 3 4
6 1 1 4 4 4 2
9 3 1 4 2 3 5 5 1 2
4 4 4 1 3```

### 输出

```
1 1 1 1 1```

# 题解

## 作者：Leasier (赞：10)

好优雅的题啊 /tyt

------------

首先考虑 $c_i = 1$ 的情况。

转化为图论模型，连边 $i \to c_{i, 1}$，则 `init(i)` 的返回值为从 $i$ 开始走到的第一个重复点。

注意到此时的图为**内向基环树**，于是答案为 $i$ 向上走到的环上第一个点——因为你会在上环后绕一圈回到这里。

乍看没有什么启发性，因为推广到 $k_i > 1$ 的情况后连成的图会长得很抽象。

但注意到对于基环树的情况，我们实际上可以**忽略环**。对于一般情况，若在中间出现环 $v_{i + 1} = c_{v_i, top_i}$，则环上的项也可以被类似地消除——即你只要**首次**走到环上的任意一项，必然都会绕一圈并 pop 掉后回到原点。

于是我们 dfs 时用栈维护走过的点即可。时间复杂度为 $O(n + \sum k_i)$。

代码：
```cpp
#include <iostream>
#include <stack>
#include <cstdio>

using namespace std;

int top;
int c[100007], stk[100007], ans[100007];
bool vis[100007];
stack<int> s[100007];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int dfs(int u){
	if (ans[u] != 0) return ans[u];
	if (vis[u]){
		while (true){
			int cur = stk[top--];
			vis[cur] = false;
			s[cur].pop();
			if (cur == u) break;
		}
	}
	vis[u] = true;
	stk[++top] = u;
	if (s[u].empty()) return u;
	return dfs(s[u].top());
}

int main(){
	int n = read();
	for (int i = 1; i <= n; i++){
		int k = read();
		for (int j = 1; j <= k; j++){
			int c = read();
			s[i].push(c);
		}
	}
	for (int i = 1; i <= n; i++){
		if (ans[i] == 0){
			int cur_ans;
			top = 0;
			cur_ans = dfs(i);
			for (int j = 1; j <= top; j++){
				ans[stk[j]] = cur_ans;
			}
		}
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：lzqy_ (赞：5)

不会的时候真不会，会了之后不知道为什么不会/qd/qd

在任意时刻，暂时有效的边一共有 $\le n$ 条，即每个栈的栈顶。容易发现这是一个基环树和树组成的森林。

如果是树，答案就是根，可以丢掉；问题是基环树的处理。

一个最核心的观察是，基环树上的环删掉是不会有影响的，所以删环之后迭代处理子问题即可。

删环需要一些精细处理以免退化到 $O(n^2)$。

代码中用了 set，时间复杂度 $O(k\log n)$。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=100010;
il int read(){
    int x=0;
    char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;
}
set<int>s;
int ans[maxn];
int st[maxn],top;
int n,len[maxn];
vector<int>v[maxn];
bool vis[maxn];
int dfs(int x){
    // printf("!!!%d(%d)\n",x,len[x]);
    if(vis[x]){
        st[top+1]=0;
        while(st[top+1]!=x)
            vis[st[top]]=0,len[st[top]]--,top--;
        return -x;
    }
    if(ans[x]) return ans[x];
    if(!len[x]) return s.erase(x),ans[x]=x;
    st[++top]=x,vis[x]=1;
    int w=dfs(v[x][len[x]]);
    if(w>0&&!ans[x]) ans[x]=ans[w],s.erase(x);
    return w;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++) v[i].push_back(0);
    for(int i=1;i<=n;i++){
        len[i]=read();
        for(int j=1;j<=len[i];j++)
            v[i].push_back(read());
        s.insert(i);
    }
    while(!s.empty())
        for(int j=*s.begin();j>0;j=-dfs(j))
            while(top) vis[st[top--]]=0;
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：wallace_QwQ (赞：3)

发现其他题解都没有仔细地讲解实现。

所以特地来补充一下造福后人。


---

直接暴力深搜，建立一个栈 st，每遍历到一个栈，就将栈的编号塞入 st 中。

如果第 $i$ 个栈的栈顶为 $c_{i,j}$，那么就建立一条 $i\to c_{i,j}$ 的边，并走过去。

此时有四种情况
- 第 $c_{i,j}$ 个栈已经为空，那么所有留存在 st 中的栈的答案均为 $c_{i,j}$
- 第 $c_{i,j}$ 个栈已经记录了答案 $ans_{c_{i,j}}$，那么所有留存在 st 中的栈的答案均为 $ans_{c_{i,j}}$
- 第 $c_{i,j}$ 个栈已经被遍历过了，那么对 st 进行弹栈操作直到 $c_{i,j}$ 被弹出，对于每个被弹出的栈的编号 $st_i$，我们将第 $st_i$ 个栈的栈顶**永久性**的弹出（因为显然此时构成了一个**环**，无论你从这个环的哪一处开始遍历，这一个环都一定会被消去）。
- 否则，继续搜索。

显然总复杂度为 $O(n+\sum k_i)$


```cpp
int n,k[N],ans[N];
stack<int> c[N],st;
bool vis[N];
int dfs(int u){
	if(ans[u]) return ans[u];
	if(vis[u])
		while(1){
			int v=st.top(); st.pop();
			vis[v]=0;
			c[v].pop();
			if(v==u) break;
		}
	vis[u]=1,st.push(u);
	if(c[u].empty()) return u;
	return dfs(c[u].top());
}
void solve(){
	cin>>n;
	for1(i,1,n){
		cin>>k[i];
		for1(j,1,k[i]){
			int _c;
			cin>>_c;
			c[i].push(_c);
		}
	}
	for1(i,1,n){
		if(!ans[i]){
			ans[i]=dfs(i);
			while(!st.empty())
				ans[st.top()]=ans[i],st.pop();
		}
		cout<<ans[i]<<" ";
	}
	return ;
}

```

---

## 作者：phoenixzhan (赞：3)

设在栈顶的数为 $a_i$，连边 $i\to a_i$ 构成基环内向树。

操作过程可以等价地描述为，从一个起点 $u$ 出发，不断跳出边，同时删掉经过的边，加上 $i\to$ 新的栈顶 $a'_i$ 的边，直到走到一个没有出边的点，这个点就是答案。

注意到，如果当前局面上有环，那么从 **每 个 点** 出发，必定会经过环上的每一个点，又回到环上走过的一点，同时删去环上的边，加上新边。这等价于直接把环消掉。于是我们可以把环消掉，弹掉对应的栈顶，加上连向新栈顶的边，不断消环直到图变成森林，每个点的答案就容易求了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<int, int>
#define piii tuple<int, int, int>
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define deb(var) cerr << #var << '=' << (var) << "; "
#define int long long
namespace Loser {
	stack<int> a[100010], st;
	int n, ans[100010], vis[100010];
	int dfs(int u) {
		if (ans[u]) return ans[u];
		if (vis[u]) {
			while (1) {
				int v = st.top(); st.pop();
				ans[v] = 0, vis[v] = 0, a[v].pop(); if (v == u) break;
			}
		}
		if (a[u].empty()) return u; 
		st.push(u); vis[u] = 1; return dfs(a[u].top());
	}
	void main() {
		cin >> n;
		for (int i = 1, k, x; i <= n; i++) {
			cin >> k; while (k--) cin >> x, a[i].push(x);
		}
		for (int i = 1; i <= n; i++) {
			ans[i] = dfs(i);
			cout << ans[i] << ' ';
			while (st.size()) ans[st.top()] = ans[i], st.pop();
		} cout << '\n';
	}
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1; while (T--) Loser::main(); return 0;
}
```

---

## 作者：win114514 (赞：0)

很有趣的题目。

### 思路

我们考虑如果每一个栈里只有一个数怎么办。

这个时候，我们会形成一个基环树森林。

我们的操作相当于每走一步就删掉来时的路。

那么每个点最终会停在离它最近的环上的点。

我们可以发现一个性质，一个环是不会影响结果的，因为它总能走回来。

所以我们可以不断的删掉一个环，直到它变成一个树。

此时，树上的所有点的答案就都是根。

实现可以拿一个栈进行 dfs。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, tp;
int ns[100010];
int st[100010];
int vs[100010];
vector<int> to[100010];

inline int dfs(int x) {
  if (ns[x]) return ns[x];
  if (vs[x]) {
    do {
      vs[st[tp]] = 0, tp--;
    } while (st[tp + 1] != x);
  }
  vs[st[++tp] = x] = 1;
  if (to[x].empty()) return x; 
  int y = to[x].back();
  to[x].pop_back();
  return dfs(y);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int k;
    cin >> k;
    to[i].resize(k);
    for (int j = 0; j < k; j++)
      cin >> to[i][j];
  }
  for (int i = 1; i <= n; i++) {
    if (ns[i]) continue;
    int s = dfs(i);
    while (tp) {
      ns[st[tp]] = s, tp--;
    }
  }
  for (int i = 1; i <= n; i++) cout << ns[i] << " \n"[i == n];
}
```

---

## 作者：orz_z (赞：0)



当每个栈只有一个元素时，我们连接 $i\to p_i$，$p_i$ 为第 $i$ 个栈的栈顶。

现在是一棵内向基环树了。

此时询问的答案是每个点对应的树的处在环上的根。

回到原问题，其实我们不断消环，即找到环，将环上的栈顶弹出，并新建连边 $i\to p_i$，并维护每个点的根。


参考代码理解。

```cpp
int n, tp, st[_], fg[_], vis[_];

stack<int> s[_];

int dfs(int u) {
	if(fg[u]) return fg[u];
	if(s[u].empty()) return u;
	if(vis[u]) {
		while(1) {
			int nw = st[tp];
			--tp;
			s[nw].pop();
			vis[nw] = 0;
			if(nw == u) break;
		}
		return dfs(u);
	}
	st[vis[u] = ++tp] = u;
	return dfs(s[u].top());
}

bool Med;
signed main() {
	// Mry;
	n = ri();
	F(i, 1, n) {
		int k = ri();
		while(k--) {
			int c = ri();
			s[i].push(c);
		}
	}
	F(i, 1, n) {
		tp = 0;
		int ok = dfs(i);
		F(j, 1, tp) fg[st[j]] = ok;
		printf("%d%c", ok, " \n"[i == n]);
	}
	// Try;
	return 0;
}
```

---

