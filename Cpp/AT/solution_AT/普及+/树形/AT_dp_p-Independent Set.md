# Independent Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_p

$ N $ 頂点の木があります。 頂点には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N\ -\ 1 $) について、$ i $ 番目の辺は頂点 $ x_i $ と $ y_i $ を結んでいます。

太郎君は、各頂点を白または黒で塗ることにしました。 ただし、隣り合う頂点どうしをともに黒で塗ってはいけません。

頂点の色の組合せは何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ N $
- 与えられるグラフは木である。

### Sample Explanation 1

頂点の色の組合せは次図の $ 5 $ 通りです。 !\[\](https://img.atcoder.jp/dp/indep\_0\_muffet.png)

### Sample Explanation 2

頂点の色の組合せは次図の $ 9 $ 通りです。 !\[\](https://img.atcoder.jp/dp/indep\_1\_muffet.png)

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
9```

## 样例 #3

### 输入

```
1```

### 输出

```
2```

## 样例 #4

### 输入

```
10
8 5
10 8
6 5
1 5
4 8
2 10
3 6
9 2
1 7```

### 输出

```
157```

# 题解

## 作者：EnofTaiPeople (赞：6)

不得不说，此题对学树形 dp 的新人很友好，我就是那个新人。

AC 时间：5分钟。

考察知识点：

1. 邻接表（没学的快去学！）； 
2. 树形 dp 板子；
3. 乘法原理，可参考[这篇文章](https://www.luogu.com.cn/blog/lwxde/solution-cf630i)。

对于动态规划问题，第一个考虑的就是状态转移方程了，为了简化问题，在此默认节点 $1$ 是树根。

对于一个节点 $a$，我们用 $dp[a][0]$ 表示 节点 $a$ 染白色时以它为树根的子树的合法染色方案数，用 $dp[a][1]$ 表示染成黑色时。

根据乘法原理及题意，不难推出如下状态转移方程：$dp[a][0]=\prod\limits_{b \in a}(dp[b][0]+dp[b][1])$；$dp[a][1]=\prod\limits_{b \in a}dp[b][0]$

AC 代码就出来啦！
```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1e5+5,M=1e9+7;
inline int read(){
	int an=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-f;c=getchar();
	}while(c>='0'&&c<='9'){
		an=an*10+c-'0';c=getchar();
	}return an*f;
}
long long dp[N][2],ans;//1表示黑，0表示白。注意开long long！
vector<int>edge[N];//用vector存邻接表。
void DFS(int a,int pre){
	int siz=edge[a].size();
	dp[a][0]=dp[a][1]=1;
	register int i,y;
	for(i=0;i<siz;++i){//枚举每一棵子树。
		y=edge[a][i];
		if(y==pre)continue;
		DFS(y,a);
		dp[a][0]=(dp[a][0]*(dp[y][0]+dp[y][1]))%M;
		dp[a][1]=(dp[a][1]*dp[y][0])%M;
	}
	return;
}
int main(){
	int n=read();register int i,x,y;
	for(i=1;i<n;++i){//有n-1条边。
		x=read();y=read();
		edge[x].push_back(y);
		edge[y].push_back(x);  
	}
	DFS(1,-1);//默认1为树根，没有父亲。
	ans=(dp[1][0]+dp[1][1])%M;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

### 思路

类似[P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)的分类讨论。

我们设 $f_{u,0}$ 为 $u$ 结点为白色时的方案数， $f_{u,1}$ 为 $u$ 结点为黑色时的方案数 ，那么根据小学教过的排列组合，显然有 

$$f_{u,0}=\prod_{v\in G_u}{f_{v,0}+f_{v,1}}(\text{mod } 10^9+7)$$

$$f_{u,1}=\prod_{v\in G_u}{f_{v,0}}(\text{mod } 10^9+7)$$

（ $G_u$ 为 $u$ 结点的儿子集合），那么最终答案就是 $f_{1,0}+f_{1,1}$ 。

需要注意的是，题目没有规定输入那个是父节点，那个是子节点（就为这个，我看了好久翻译）。加双向边即可，先遍历的即是父节点。

### Code

```cpp
#include <bits/stdc++.h>
using namesapce std;
const int N = 1e6 + 5, mod = 1e9 + 7;
long long a[N], f[N][2], cnt[N], n, m, x, y;
vector<int> G[N];
bool vis[N];
void dfs(int u) {
	f[u][0] = f[u][1] = 1;
	for (int v : G[u]) 
		if (!vis[v]) {
			vis[v] = true, dfs(v);
			f[u][0] *= f[v][0] + f[v][1], f[u][0] %= mod;
			f[u][1] *= f[v][0], f[u][1] %= mod;
		}
}
int main() {
	cin >> n;
	for (int i = 1; i < n; i ++)
		cin >> x >> y, G[x].push_back(y)， G[y].push_back(x);
	vis[1] = true, dfs(1);
	cout << (f[1][0] + f[1][1]) % mod << '\n';
	return 0;
}
```


---

## 作者：Hehe_0 (赞：1)

很好的树形dp入门练手题
树形dp大部分都是从子树状态来考虑

#### 题目要方案数   
根据 乘法原理 定义很容易得知是二者相乘  
我们知道怎么运算后，可以考虑状态了



------------
注意这里是要相乘


### dp [i] [j]    记录 i 根节点染色方案为 j 的方案数   
 

这个题真的可以和其他的‘染色’的题联系起来  

###   黑  的状态来自  白  ；  
### 而  白  的状态来自  黑和白  。  

	dp[x][1] = (dp[x][1] * (dp[y][2]) % mod) % mod;   
        
	dp[x][2] = (dp[x][2] * (dp[y][2] + dp[y][1])) %mod;  
    
        
 比较弱的树形dp  
##### 具体看代码注释

```cpp
#include<bits/stdc++.h>

#define int long long
using namespace std;
const int mod=1e9+7;
//审题：
//跟一般的树形dp很像，染色是个金典的问题
//二维，记录i根节点染色方案为j的方案数 
int n; 
int dp[100101][5];
//1黑2白 

int head[200030],nxt[200030],to[200030];

int _;
void add(int x,int y)//加边
{
	_++;
	to[_]=y;
	nxt[_]=head[x];
	head[x]=_;
	return ;
}

void makedp(int x,int fa)
{
	dp[x][1]=1;//初始状态 
	dp[x][2]=1;//一个点只有黑白两种状态 
	for(int i=head[x];i;i=nxt[i] )
	{
		int y=to[i];
		if(y==fa)//跳过父亲
		continue;
        //对树dfs 
		makedp(y,x);
		//黑色只能由白儿子转移过来 
		dp[x][1]=(dp[x][1]*(dp[y][2])%mod)%mod;
		dp[x][2]=(dp[x][2]*(dp[y][2]+dp[y][1]))%mod;
		//而白色可以来自黑白儿子转移 
	}//方案数转移时：当前方案和子树方案* 
	
	return ;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int q,w;
		cin>>q>>w;
		add(q,w);//加双向
		add(w,q);
	}
	//以1为根dfs 
	makedp(1,0);
	
	cout<<(dp[1][1]+dp[1][2])%mod;
	//根节点黑白两种方案之和 
	return 0;
}
```


---

## 作者：Phartial (赞：0)

设 $f_{i,j}$ 表示将点 $i$ 染成 $j$（$0$ 表示白色，$1$ 表示黑色）时以点 $i$ 为根的子树的染色方案数。

分类讨论如下：

- $j=0$ 时，$f_{i,j}=\prod\limits_{k\in E}f_{k,0}+f_{k,1}$。

- $j=1$ 时，$f_{i,j}=\prod\limits_{k\in E}f_{k,0}$。

（其中 $E$ 表示点 $i$ 的儿子集合）

然后记忆化搜索就可以了。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 1e5 + 1;
const LL kM = 1e9 + 7;

int n;
vector<int> e[kN];
LL f[kN][2];

LL D(int x, int d, int _f) {
  if (~f[x][d]) {    // 如果之前已经算过答案了
    return f[x][d];  // 直接返回
  }
  f[x][d] = 1;
  for (int i : e[x]) {                                               // 枚举出点
    if (i != _f) {                                                   // 如果不是父亲节点
      f[x][d] = f[x][d] * (D(i, 0, x) + (d ? 0 : D(i, 1, x))) % kM;  // 统计答案
    }
  }
  return f[x][d];
}

int main() {
  cin >> n;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    e[x].push_back(y), e[y].push_back(x);  // 建图
  }
  fill(&f[0][0], &f[n][1] + 1, -1);        // 初始化
  cout << (D(1, 0, 0) + D(1, 1, 0)) % kM;  // 由于题目给出的是无根树，因此需要选一个点做根（这里我选的是点1）
  return 0;
}
```



---

