# DeadLee

## 题目描述

Lee bought some food for dinner time, but Lee's friends eat dinner in a deadly way. Lee is so scared, he doesn't want to die, at least not before seeing Online IOI 2020...

There are $ n $ different types of food and $ m $ Lee's best friends. Lee has $ w_i $ plates of the $ i $ -th type of food and each friend has two different favorite types of food: the $ i $ -th friend's favorite types of food are $ x_i $ and $ y_i $ ( $ x_i \ne y_i $ ).

Lee will start calling his friends one by one. Whoever is called will go to the kitchen and will try to eat one plate of each of his favorite food types. Each of the friends will go to the kitchen exactly once.

The only problem is the following: if a friend will eat at least one plate of food (in total) then he will be harmless. But if there is nothing left for him to eat (neither $ x_i $ nor $ y_i $ ), he will eat Lee instead $ \times\_\times $ .

Lee can choose the order of friends to call, so he'd like to determine if he can survive dinner or not. Also, he'd like to know the order itself.

## 说明/提示

In the first example, any of the following orders of friends are correct : $ [1, 3, 2] $ , $ [3, 1, 2] $ , $ [2, 3, 1] $ , $ [3, 2, 1] $ .

In the second example, Lee should call the second friend first (the friend will eat a plate of food $ 1 $ ) and then call the first friend (the friend will eat a plate of food $ 2 $ ). If he calls the first friend sooner than the second one, then the first friend will eat one plate of food $ 1 $ and food $ 2 $ and there will be no food left for the second friend to eat.

## 样例 #1

### 输入

```
3 3
1 2 1
1 2
2 3
1 3```

### 输出

```
ALIVE
3 2 1```

## 样例 #2

### 输入

```
3 2
1 1 0
1 2
1 3```

### 输出

```
ALIVE
2 1```

## 样例 #3

### 输入

```
4 4
1 2 0 1
1 3
1 2
2 3
2 4```

### 输出

```
ALIVE
1 3 2 4```

## 样例 #4

### 输入

```
5 5
1 1 1 2 1
3 4
1 2
2 3
4 5
4 5```

### 输出

```
ALIVE
5 4 1 3 2```

## 样例 #5

### 输入

```
4 10
2 4 1 4
3 2
4 2
4 1
3 1
4 1
1 3
3 2
2 1
3 1
2 4```

### 输出

```
DEAD```

# 题解

## 作者：7KByte (赞：8)

VP的时候被当场降智。。。

首先我们假设每个人都吃两道菜。

这样有些菜会吃到负数（现实中时不可能的

没有被吃到负数的菜，说明无论如何怎么排列都不会被吃完。

如果一个人最喜爱的两道菜中，有一道菜没有被吃到负数，说明这个人不论排在哪一个位置都不会吃掉$Lee\ \ \ \texttt{(OvO}$

所以我们先把每个人的两道菜都吃掉。然后对于有剩的菜直接忽略，同时把这道菜相关联的人排到最后，然后把这个人吃掉的菜补回来。

这样我们发现构成一个子问题。

每次找有剩的菜，把与之相关联的人删掉，再把这个人吃的菜吐出来（不是

重复这个过程，知道没有剩下的菜。

最后，如果所有人都被删了，输出构造的排列即可。否则$Lee$就要被吃啦/cy

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,m,w[N];
queue<int>q;
typedef pair<int,int> Pr;
int h[N],tot,del[N],v[N];
struct node{
	int to,nxt,val;
}e[N<<1];
void add(int x,int y,int z){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;
}
int sta[N],top;
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d",&w[i]);
	rep(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y,i);add(y,x,i);
		w[x]--;w[y]--;
	}
	rep(i,1,n)if(w[i]>=0)q.push(i),v[i]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=e[i].nxt)if(!del[e[i].val]){
			del[e[i].val]=1;sta[++top]=e[i].val;
			w[e[i].to]++;
			if(w[e[i].to]==0)q.push(e[i].to);
		}
	}
	if(top<m)puts("DEAD");
	else {
		puts("ALIVE");
		while(top)printf("%d ",sta[top--]);
	}
	return 0;
}
```

---

## 作者：chen_qian (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF1369E)

非常好的一道拓扑排序变式，个人认为光是思维就可以上蓝
~~（可能是我太弱了)~~

如果从正面思考，我们虽然可以暴力确认每一个位置应该放哪一个人，但是这洋肯定是行不通的。

但是题中，有一个重要的点就是对于每一个人，其所喜欢的两样食材中只要有一种，就可以了。那么我们就尽量让每一个人都只吃一种食材。

这个时候我们开一个桶$t[x]$表示需求食材$x$的人的数量。

如果$t[x]<=w[x]$ 那么需求食材$x$的人不管处于序列中的哪一个位置，他的需求都一定会被满足。这时如果我们把他放在前面，那他可能就会两种食材都吃，这可能会使后面有人吃不到。那我们就把它放在最后，并且他也不再需求另一种食材。那么另一种食材的需求量$-1$。

如果此时另一种食材$y$的需求量$t[y]<=w[y]$那么我们就可以把要吃它的所有人往序列后扔。但放在已确定的人的前面。

```
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,m;
int w[N],t[N];
int stk[N],top;
vector<pair<int,int> > v[N];
bool vis[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		t[x]++;
		t[y]++;
		v[x].push_back(make_pair(y,i));
		v[y].push_back(make_pair(x,i));
	}
	queue<int> q;
	for(int i=1;i<=N-2;i++)
		if(t[i]<=w[i]&&t[i]) q.push(i);
		
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<v[x].size();i++){
			pair<int,int> now=v[x][i];
			if(!vis[now.second]){
				vis[now.second]=1;
				stk[++top]=now.second;
				if(--t[now.first]<=w[now.first])
					q.push(now.first);
			}
		}
	}
	if(top<m){
		cout<<"DEAD"<<endl;
	}
	else{
		cout<<"ALIVE"<<endl;
		for(int i=top;i>=1;i--) cout<<stk[i]<<' ';
	}
	return 0;
}
```


---

## 作者：Caro23333 (赞：5)

运用贪心的思想。我们维护一个栈，初始为空，希望算法结束后，从栈顶至栈底保存答案序列。

对于某种食物 $i$，假设当前需要吃这种食物的人数为 $s_i$。初始时认为每个人喜欢的两种食物他都需要吃。算法流程如下：

1. 首先检查是否存在一种未被使用过的食物 $i$ 使得 $s_i \le w_i$。

- 如果不存在，跳出循环。

- 如果存在，意味着喜欢吃这种食物的人无论如何都不会挨饿。基于此种考虑，我们将这些人都放到答案的栈顶，避免消耗额外的资源。同时，将食物 $i$ 标记为“使用过的”。

2. 值得注意的是，当我们将一个人 $k$ 放入栈顶时，假设它一定能吃到的是 $x_k$，那我们要将 $s_{y_k}$ 减去 $1$，因为 $k$ 已经不需要 $y_k$ 这种食物了。依据此原则，我们更新 $s$ 数组。

3. 更新结束后，进入下一次循环。

循环结束时，如果栈中包含所有的 $m$ 个人，则输出 `ALIVE` 并自栈顶至栈底输出序列；否则输出 `DEAD`。

可以证明这样的贪心策略一定不亏。

不难发现这个算法的过程与拓扑序列的构造十分相似，所以利用一个 `queue` 来维护即可。实现见代码。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const int MAXN = 200005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
int n,m,w[MAXN],x[MAXN],y[MAXN],sum[MAXN];
int ans[MAXN],q[MAXN],front,rear,tot;
int col[MAXN],vis[MAXN];
vector<int> p[MAXN];

int main()
{
	n = readint(), m = readint();
	for(int i = 1; i<=n; i++)
		w[i] = readint();
	for(int i = 1; i<=m; i++)
	{
		x[i] = readint(), y[i] = readint();
		sum[x[i]]++, sum[y[i]]++;		
		p[x[i]].push_back(i), p[y[i]].push_back(i);
	}
	front = rear = 0;
	for(int i = 1; i<=n; i++)  
		if(sum[i]<=w[i])
		{
			vis[i] = 1;
			for(int j = 0; j<p[i].size(); j++)
				if(!col[p[i][j]])
					col[p[i][j]] = i, q[rear++] = p[i][j];
		}
	while(front<rear)
	{
		int u = q[front++];
		ans[++tot] = u;
		if(x[u]!=col[u])
			swap(x[u],y[u]);
		sum[y[u]]--;
		if(sum[y[u]]<=w[y[u]]&&!vis[y[u]])
		{
			vis[y[u]] = 1;
			for(int i = 0; i<p[y[u]].size(); i++)
				if(!col[p[y[u]][i]])
					col[p[y[u]][i]] = y[u], q[rear++] = p[y[u]][i];
		}
	}
	if(tot<m)
		cout << "DEAD" << endl;
	else
	{
		cout << "ALIVE" << endl;
		for(int i = tot; i>=1; i--)
			cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}

```


---

## 作者：endswitch (赞：0)

考察要点：

* 图论建模。
* 无向图拓扑排序。

首先分析得到，一个菜品无论怎么选的个数都不会低于 $0$，那么喜欢这个菜品的人一定可以选这个菜使得策略最优。

于是我们将这个菜品和这些人删去，迭代解决这个问题即可。

一个人有且仅有两个喜欢的菜品，那么我们将菜品看作点，将人看作边，对于上述过程，用拓扑排序刻画即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;

const int N = 2e5 + 5;
int n, m, u[N], v[N], deg[N];
bool is[N], vis[N];
queue<int> q;
stack<int> ans;
vector<pair<int, int> > g[N];

inline void toposort() {
    for(int i = 1 ; i <= n ; ++ i)
        if(deg[i] >= 0) q.push(i);
    
    while(! q.empty()) {
        int u = q.front();

        q.pop();

        for(auto [v, i] : g[u])
            if(! vis[i]) {
                ans.push(i);
                vis[i] = true;
                ++ deg[v];

                if(deg[v] == 0) q.push(v);
            }

    }
}

signed main() {
    ios_base :: sync_with_stdio(NULL);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i)
        cin >> deg[i];
    for(int i = 1 ; i <= m ; ++ i) {
        cin >> u[i] >> v[i];

        g[u[i]].pb({v[i], i}), g[v[i]].pb({u[i], i});

        -- deg[u[i]], -- deg[v[i]];
    }
    
    toposort();

    cerr << ans.size() << '\n';

    if((int)ans.size() < m) cout << "DEAD";
    else {
        cout << "ALIVE\n";

        while(! ans.empty()) {
            cout << ans.top() << ' ';
            
            ans.pop();
        }
    }

    return 0;
}
```

---

## 作者：xfrvq (赞：0)

*2400，拓扑排序变式好题。

---

设菜品 $i$ 的**必需量**为 $b_i$。初始假定每对 $x,y$ 都要被用到。$b_i$ 等于将所有 $(x,y)$ 连边建图后，每个点的度数。

当菜品 $i$ 满足 $b_i\le a_i$ 时，此时**必须吃菜品 $i$ 的客人**已经满足，**他们对另一种菜品的要求就不再必需**，我们修改对应的 $b_i$。

对于这些已经满足的客人，为避免其影响让他们尽量靠后。于是我们顺序记录这些客人并倒序输出即可。

证明当 $\forall i,b_i\gt a_i$ 时原问题无解：一旦进入这类局面，无论如何安排顺序 $\forall i,b_i\gt a_i$ 都总是成立。最终来到 $b_i=1\gt a_i$ 时就无解了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n,m,a[N],b[N],P[N],t;
bool vis[N];
vector<pair<int,int>> G[N];
queue<int> Q;

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%d",a + i);
	for(int i = 1,x,y;i <= m;++i){
		scanf("%d%d",&x,&y),++b[x],++b[y];
		G[x].emplace_back(y,i),G[y].emplace_back(x,i);
	}
	for(int i = 1;i <= n;++i)
		if(b[i] && b[i] <= a[i]) Q.push(i);
	while(Q.size()){
		int u = Q.front(); Q.pop();
		for(auto[v,i] : G[u]) if(!vis[i]){
			vis[P[++t] = i] = 1;
			if(--b[v] <= a[v]) Q.push(v);
		}
	}
	if(t < m) return puts("DEAD"),0;
	puts("ALIVE");
	for(;t >= 1;--t) printf("%d ",P[t]);
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
和 $\text{wyx}$ 哥哥思路一样好耶！

---
### 解题思路：

不算很难的贪心。

不妨先将只吃正的改成吃所有的（也就是可以存在负数权值），但是要求吃的中至少有一个是正的。

然后考虑这个过程的逆过程，也就是先将所有的菜减去所有的想要吃掉它的人，然后每一次可以选择一些人加入，但是要求加入后至少有一个菜是的权值是正的。

贪心地考虑这个问题，一定是每一次选择一个权值非负的菜，将所有吃菜的权值加上去。如果在中途出现了无法操作的情况就一定无解。否则只需要将刚才给出的答案反向输出就是一个可行的解。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=200005;
int n,m,x,y,w[MAXN],vis[MAXN],ans[MAXN],tot,flag,q[MAXN],l,r;
vector <pair<int,int> > v[MAXN];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		v[x].push_back(make_pair(y,i));
		v[y].push_back(make_pair(x,i));
	}
	l=1;
	for(int i=1;i<=n;i++){
		w[i]-=v[i].size();
		if(w[i]>=0)q[++r]=i;
	}
	while(l<=r){
		for(int i=0;i<v[q[l]].size();i++){
			if(vis[v[q[l]][i].second]==0){
				vis[v[q[l]][i].second]=1;
				w[v[q[l]][i].first]++;
				ans[++tot]=v[q[l]][i].second;
				if(w[v[q[l]][i].first]==0)
				q[++r]=v[q[l]][i].first;
			}
		}
		l++;
	}
	if(tot==m){
		printf("ALIVE\n");
		for(int i=tot;i>=1;i--){
			printf("%d ",ans[i]);
		}
		printf("\n");
		return 0;
	}
	printf("DEAD\n");
	return 0;
}
```


---

