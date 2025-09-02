# [COCI 2024/2025 #1] 等级 / Hijerarhija

## 题目背景


译自 [COCI 2024/2025 #1](https://hsin.hr/coci/) T3。$\texttt{3s,0.5G}$。满分为 $90$。

## 题目描述


有 $n$ 个节点，给定 $(n-1)$ 对点之间的父子关系。

有 $m$ 个修改，每次给定一对父子，将它们的关系反转（即，原来的父亲变成儿子，儿子变成父亲）。

在第一次修改前，和每次修改后，输出这张图是否是一棵有根树。

## 说明/提示

对于 $100\%$ 的数据，保证：

- $2\le n\le 3\times 10^5$；    
- $0\le m\le 10^6$；
- $1\le u,v\le n$，$u\neq v$。
- **至少有一个回答是 $\texttt{DA}$**。


| 子任务编号 | $n,m\le$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $300$ | A    |   $ 7 $   |  
| $ 2 $    | $300$ |  |  $ 12 $   |  
| $ 3 $    | $10^3$  |  | $ 16 $   |
| $ 4 $    | $3\times 10^5$  | A | $ 15 $   |
| $ 5 $    | $3\times 10^5$  | B | $ 23 $   |
| $ 6 $    | $3\times 10^5$  | | $ 17 $   |

- 特殊性质 A：$m=0$。
- 特殊性质 B：对于 $\forall 1\le i\lt n$，$(i,i+1)$ 间有父子关系。




## 样例 #1

### 输入

```
3
1 2
1 3
3
1 2
1 2
1 3```

### 输出

```
DA
DA
DA
DA```

## 样例 #2

### 输入

```
4
2 1
2 3
1 4
4
4 1
4 1
3 2
1 4```

### 输出

```
DA
NE
DA
DA
NE```

# 题解

## 作者：lcfollower (赞：1)

首先你要明白有根树的定义：对于一棵树当且仅当只有一个节点的入度为 $0$。

于是你就会想到统计每个节点的入度个数。

对于一开始未修改的询问，答案为 $[\left (\sum\limits_{i=1}^n [deg_i = 1]\right) = 1]$，其中尖括号为括号内等式成立则为真（$1$），否则为假（$0$）；$deg_i$ 为节点 $i$ 的入度。

然后对于每次修改 $u$，$v$，为了方便起见，需要使得 $u$ 是 $v$ 的父亲节点，所以开一个数组 $fa_i$ 记录节点 $i$ 的父亲节点。如果 $fa_u = v$ 则交换 $u$，$v$。

对于交换一对父子节点的关系，相当于让 $deg_u\to deg_u + 1$，$deg_v\to deg_v - 1$。

具体可见下图，它将树的节点 $1$，$2$ 的父子情况交换：

![](https://cdn.luogu.com.cn/upload/image_hosting/xz6lcyxo.png)

然后有如下两种影响根的数量的情况：

- $u$ 为修改前的根节点（$deg_u = 0$），但是由于修改后 $deg_u = 1$，所以根的数量减 $1$。

- $v$ 原本的度数为 $1$，但是减少 $1$ 后 $deg_v = 0$，所以根的数量加 $1$。

注意这两种情况是并列的。

接着更改两点的 $fa$ 值。

最后看看是否根的数量为 $1$ 即可，就这么点了。

时间复杂度为 $\mathcal O(n + m)$。

```cpp
# include <bits/stdc++.h>

# define int long long

using namespace std;

const int N = 3e5 + 10;
int n ,m ,fa[N] ,deg[N] ,tot;
bool vis[N];

signed main (){
  cin >> n;
  for (int i = 1 ; i < n ;i ++){
    int u ,v;
    cin >> u >> v;
    fa[v] = u;
    deg[v] ++;//入度加 1。
  }

  for (int i = 1 ; i <= n ;i ++)
    if (!deg[i]) vis[i] = 1 ,++ tot;
  
  if (tot > 1) puts("NE");
  else puts ("DA");

  cin >> m;
  
  for (int i = 1 ; i <= m ; i ++){
    int u ,v;
    cin >> u >> v;

    if (fa[u] == v) swap (u ,v);

    deg[u] ++ ,deg[v] --;//根节点入度减 1，儿子节点入度增加 1。

/* 两种情况。*/

    if (vis[u]) vis[u] = 0 , -- tot;

    if (!deg[v]) vis[v] = 1 ,++ tot;

/*更改 fa[u] 和 fa[v]*/

    int t = fa[u];
    fa[u] = v ,fa[v] = t;

    if (tot == 1) puts ("DA");
    else puts ("NE");
  }
  return 0;
}
```

---

## 作者：Lagrange_NoAria (赞：0)

这道题选比较简单，把每个子节点的父亲记录下来，再计数每个节点的出入度。

然后对根节点计数，记为 $cnt$，并对此进行判断，输出第一组答案。  
紧接着，对于每一次父子交换的操作，判断辈分情况，然后对 $cnt$ 进行修改，再次判断，输出。

代码如下：

```cpp
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
int n,m,u,v,cnt,ine[300005],oute[300005],father[300005];
int main(){
	cin>>n;
	for(int i = 1; i < n; i++){
		cin>>u>>v;
		father[v]=u;//u->v
		ine[u]++;oute[v]++;
	}
	for(int i = 1; i <= n; i++){
		if(oute[i]==0){
			cnt++;
		}
	}
	if(cnt==1) cout<<"DA"<<endl;
	else cout<<"NE"<<endl;
	cin>>m;
	for(int i = 1; i <= m; i++){
		cin>>u>>v;
		if(father[v]==u){//u--true--v
			father[u]=v;
			father[v]=0;
			if(++oute[u]==1) cnt--;
			if(--oute[v]==0) cnt++;
		}
		else{
			father[v]=u;
			father[u]=0;
			if(--oute[u]==0) cnt++;
			if(++oute[v]==1) cnt--;
		}
		if(cnt==1) cout<<"DA"<<endl;
		else cout<<"NE"<<endl; 
	}
	return 0;
}
```

---

## 作者：VelvetChords (赞：0)

# P11389 [COCI 2024/2025 #1] 等级 / Hijerarhija
## 0.前言
上午写题下午发。
## 1.题目大意
核心是维护一个有向无环图的结构，并且在每次反转父子关系后判断该图是否为一棵有根树。
## 2.思路
一个有 $n$ 个节点，$n-1$ 条边的图，这本质上是一个树。

树是一个连通无环图，有且仅有一个根节点。

对于一棵树，所有节点中，**只有一个节点**的出度为 $0$（即没有父亲节点），这个节点是根节点，其他节点的出度大于 $0$。

所以我们通过 $n-1$ 条边和父子关系建立起树的结构。

用数组记录每个节点的父节点，初始化时我们可以看出，所有边 $u$ 和 $v$ 都是有向的，且指向 $v$ 是 $u$ 的子节点。

我们需要维护每个节点的出度（即一个节点有多少子节点），用于判断是否有根节点。

如何判断树是否为有根树？

众所周知，根节点的特征是出度为 $0$。

所以，遍历所有节点，统计出度为 $0$ 的节点数量。根节点的数量应该恰好为 $1$。

如果根节点数为 $1$，图是有根树；否则不是。

那反转怎么搞？

因为反转会改变父子关系，影响节点的出度，所以在每次反转前，需要维护每个节点的出度，更新根节点的数量。

## 3.代码
```C++
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,rt,u,v,ru_du[300010],chu_du[300010],parents[300010];
int main() 
{
	int n;
	cin>>n;
	// 读入初始树的边，建立父子关系
	for(int i=1;i<n;i++) 
	{
		cin>>u>>v;
		parents[v]=u;//v的父节点是u
		ru_du[u]++;//u的入度增加
		chu_du[v]++;//v的出度增加
	}
	//统计初始根节点数量
	for(int i=1;i<=n;i++)
		if(chu_du[i]==0) rt++;  // 出度为0的是根节点
	// 判断初始状态是否为一棵有根树
	if(rt==1) cout << "DA\n";
	else cout<<"NE\n";
	cin>>m;
	//处理每一次反转操作
	for (int i=1;i<=m;i++) 
	{
		int u,v;
		cin>>u>>v;
		// 判断父子关系是u -> v还是v -> u
		if(parents[v]==u) 
		{
			parents[u]=v; 
			parents[v]=0;//反转，u成为v的子节点
			if(++chu_du[u]==1) rt--; //如果u的出度变为1，则原本的根数量减少
			if(--chu_du[v]==0) rt++; //如果v的出度变为0，则根节点数量增加
		} 
		else 
		{
			parents[v]=u; 
			parents[u]=0;//反转，v成为u的子节点
			if(--chu_du[u]==0) rt++;//如果u的出度变为0，则根节点数量增加
			if(++chu_du[v]==1) rt--;//如果v的出度变为1，则根节点数量减少
		}
		//输出当前图是否为有根树
		if (rt==1) cout << "DA\n";
		else cout<<"NE\n";
	}
	return 0;
}

```

---

## 作者：PCSJZ (赞：0)

## 思路

因为一棵树的本质是一个图，所以我们可以认为入度为 $0$ 的节点就是这个树的根。

所以我们统计有几个根，以及是已经作为根的。最后去统计有多少个根就行了。

存储父子关系可以用 unordered_map。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

const int N = 3 * 1e5 + 5;
int n, m;
int in[N];
bool root[N];
unordered_map<int, int> fa[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		fa[u][v] = 0; // 为了更清楚的统计，我们只计算 u -> v 这条边，即 fa[v][u] 
		fa[v][u] = 1;
		in[v]++; // 孩子的入度加 1 
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) { // 统计 
		if (!in[i]) { // 入度为 0 
			root[i] = 1;
			cnt++;
		}
	}
	if (cnt == 1) printf("DA\n");
	else printf("NE\n");
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (fa[u][v]) swap(u, v); // 默认 u 是 v 的父亲，否则交换 
		in[u]++, in[v]--;
		if (root[u]) { // 本来是根的现在不是 
			root[u] = 0;
			cnt--;
		} 
		if (!in[v]) { // 新的根 
			root[v] = 1;
			cnt++;
		}
		if (fa[u][v] == 0) fa[u][v] = 1; // 更新父子关系 
		else fa[u][v] = 0;
		if (fa[v][u] == 0) fa[v][u] = 1;
		else fa[v][u] = 0;
		if (cnt == 1) printf("DA\n");
		else printf("NE\n");
	}
	return 0;
}
``````

---

## 作者：songzhixin (赞：0)

### 题目大意

给你一棵树，每次操作翻转一对父子关系的节点的关系，问反转后能否构成一棵有根树。

### 解题思路

我们先回顾在**能形成一棵有根树的条件：每个节点的入度不超过 $2$**，这也是有根树的定义。

每次翻转会让子节点的入度减少一，父节点的入度增加一。这一次操作可能会让原父节点变得不合法，也可能让原子节点变得合法，可以维护其入度。

如何寻找这一条边？肯定不能暴力去找，可以用一个 `map` 来存边，要记得记录这条边的方向。

那又如何维护有哪些点不合法呢？这里可以发现是一次只会加入一个数或删除一个数，可以开一个 `set` 来存一下。

最后，如何判断是否为有根树呢？只需要判断一下我们的 `set` 里面有没有数即可，因为这里面存的是不合法的点。

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define s first
#define t second
const long long N=3*1e5+5;
int d[N];
struct node {
	int s,t;
};
map<pair<int,int>,bool> m;//用于记录边 
set<int> s;//用于记录不合法的点 
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n-1; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		d[y]++;
		if(d[y]>=2) {//记录初始时每个节点的入度 
			s.insert(y);
		}
		pair<int,int> u;
		u.s=x;
		u.t=y;
		m[u]=true;
	}
	if(s.empty()) {
		printf("DA\n");
	} else {
		printf("NE\n");
	}
	int k;
	scanf("%d\n",&k);
	while(k--) {
		int x,y;
		scanf("%d%d",&x,&y); 
		pair<int,int> u;
		u.s=x;
		u.t=y;
		pair<int,int> v;
		v.s=y;
		v.t=x;
		if(m[u]==true) {//让反转后y是x的子节点 
			m[u]=false;
			m[v]=true;
		} else {
			m[v]=false;
			m[u]=true;
			swap(x,y);
		}
		d[y]--;//原子节点的入度减一 
		if(d[y]<=1) {//判断是否已经变得合法 
			s.erase(y);
		}
		d[x]++;//原父节点的入度加一 
		if(d[x]>1) {//判断是否不合法
			s.insert(x);
		}
		if(s.empty()) {
			printf("DA\n");
		} else {
			printf("NE\n");
		}
	}
	return 0;
}
```

### 注意事项

- 一开始也要判断一次是否为有根树。

- 翻转父子节点的这一对数不一定前者为后者的父亲。

---

## 作者：queenbee (赞：0)

# P11389 [COCI 2024/2025 #1] 等级 / Hijerarhija 题解

## 思路
[题目传送门](https://www.luogu.com.cn/problem/P11389)，入度为 $0$ 的点可以被看作这个树的一个根，当且仅当正好有一个入度为 $0$ 的点时，这棵树是一颗有根树，每次操作切换父子关系可以看作将原先的父亲节点入度加一，儿子节点入度减一，如果在这个过程中增加或减少了一个根就进行记录，最后判断是否只有一个根节点即可。

## 程序
```cpp
#include<bits/stdc++.h> //我爱万能头
using namespace std;
const int N=3e5+10;
int n,m;
int u,v;
int rt[N],cnt;
int in_edge[N];
unordered_map<int,int>fa[N];    //map存储两点间关系
int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        fa[u][v]=0; //初始化两点关系，注意要双向初始
        fa[v][u]=1;
        in_edge[v]++;   //子节点入度加1
    }
    for(int i=1;i<=n;i++){  //统计一开始有几个根
        if(!in_edge[i]){
            rt[i]=1;    //给根打标记
            cnt++; //根数量加1
        }
    }
    if(cnt==1){
        puts("DA");
    }
    else{
        puts("NE");
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        if(fa[u][v]){
            swap(u,v);
        }
        in_edge[u]++;
        in_edge[v]--;
        if(rt[u]){  //如果根节点入度加1则其不为根节点
            rt[u]=0;
            cnt--;  
        }
        if(!in_edge[v]){    //如果入度为0则产生新的根
            rt[v]=1;
            cnt++;
        }
        fa[u][v]^=1;    //切换父子关系，注意要双向修改
        fa[v][u]^=1;
        if(cnt==1){ //答案判断
            puts("DA");
        }
        else{
            puts("NE");
        }
    }
    return 0;   //完结撒花
}
```

---

## 作者：N0_1 (赞：0)

### 题意
给定 $n$ 个点，$n - 1$ 条边的图，对于每一条边 $u, v$，表示 $u$ 是 $v$ 的父亲节点。

接下来有 $m$ 次操作，对于每一次操作 $u, v$，反转 $u,v$ 之间的父子关系（保证 $u,v$ 是父子关系）。

在第一次修改前，和每次修改后，输出这张图是否是一棵有根树。

### 思路
对于本题中的图是不是一棵有根树，有以下几个结论：

假设该图有 $n$ 个节点，$outDep_i$ 表示点 $i$ 的出度。

- 该图是一个具有 $n-1$ 条边的有向无环图。
- 仅存在一个点满足 $outDep_i$ 的值为 $0$，该点为根节点。

根据上面结论，不难得出第一次修改前的答案。

关于每一次修改，可以根据 $u, v$ 之间的父子关系，在线更新 $u, v$ 的出度，并维护根的数量。

关于 $u, v$ 之间的父子关系，可以用一个 $fa_i$ 数组表示 $i$ 的父亲为 $fa_i$，则对于每一次修改：

假设 $fa_i$ 的值为 $0$，则 $i$ 无父亲节点。

- 若 $fa_u = v$，则 $fa_v \leftarrow u$，$fa_u \leftarrow 0$，$outDep_u \leftarrow outDep_u - 1$，$outDep_v \leftarrow outDep_v + 1$。
- 若 $fa_v = u$，则 $fa_u \leftarrow v$，$fa_v \leftarrow 0$，$outDep_v \leftarrow outDep_v - 1$，$outDep_u \leftarrow outDep_u + 1$。

然后根据每一次修改后根的数量来判断该图是否是一棵有根树即可。

### code

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;
int inDep[N], outDep[N], fa[N];

int main() {
    int n, cnt = 0;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        fa[v] = u;
        inDep[u]++; outDep[v]++;
    }
    int rt = 0;
    for (int i = 1; i <= n; i++) {
        if (outDep[i] == 0) rt++;
    }

    if (rt == 1) cout << "DA\n";
    else cout << "NE\n";

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (fa[v] == u) {
            fa[u] = v; fa[v] = 0;
            if (++outDep[u] == 1) rt--;
            if (--outDep[v] == 0) rt++;

        } else {
            fa[v] = u; fa[u] = 0;
            if (--outDep[u] == 0) rt++;
            if (++outDep[v] == 1) rt--;
        }
        if (rt == 1) cout << "DA\n";
        else cout << "NE\n";
    }
    return 0;
}

---

