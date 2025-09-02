# [ABC293D] Tying Rope

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc293/tasks/abc293_d

一方の端が赤に塗られており、もう一方の端が青に塗られているロープが $ N $ 本あります。ロープには $ 1 $ から $ N $ までの番号がつけられています。

これからロープの端を結ぶ操作を $ M $ 回行います。$ i $ 回目の操作ではロープ $ A_i $ の色 $ B_i $ の端とロープ $ C_i $ の色 $ D_i $ の端を結びます。ただし、色 `R` は赤を意味し、色 `B` は青を意味します。各ロープについて、同じ色の端が複数回結ばれることはありません。

すべての操作を終えた後に、ひとつながりになっているロープの組について環状になっているものとそうでないものの個数を出力してください。

ただし、ひとつながりになっているロープの組 $ \lbrace\ v_0,\ v_1,\ \ldots,\ v_{x-1}\ \rbrace $ が環状になっているとは、$ v $ の要素の順序を適切に入れ替えることで各 $ 0\ \leq\ i\ <\ x $ についてロープ $ v_i $ とロープ $ v_{(i+1)\ \bmod\ x} $ が結ばれているようにできることをいいます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ C_i\ \leq\ N $
- $ (A_i,\ B_i)\ \neq\ (A_j,\ B_j),\ (C_i,\ D_i)\ \neq\ (C_j,\ D_j) $ $ (i\ \neq\ j) $
- $ (A_i,\ B_i)\ \neq\ (C_j,\ D_j) $
- $ N,\ M,\ A_i,\ C_i $ は整数
- $ B_i,\ D_i $ は `R` か `B` のいずれか
 
### Sample Explanation 1

ひとつながりになっているロープの組は $ \lbrace\ 1\ \rbrace $、$ \lbrace\ 2,4\ \rbrace $、$ \lbrace\ 3,5\ \rbrace $ の $ 3 $ つです。 ロープ $ \lbrace\ 3,5\ \rbrace $ の組は環状になっており、ロープ $ \lbrace\ 1\ \rbrace $ と $ \lbrace\ 2,4\ \rbrace $ の組は環状になっていません。したがって、$ X\ =\ 1,\ Y\ =\ 2 $ です。

## 样例 #1

### 输入

```
5 3
3 R 5 B
5 R 3 B
4 R 2 B```

### 输出

```
1 2```

## 样例 #2

### 输入

```
7 0```

### 输出

```
0 7```

## 样例 #3

### 输入

```
7 6
5 R 3 R
7 R 4 R
4 B 1 R
2 R 3 B
2 B 5 B
1 B 7 B```

### 输出

```
2 1```

# 题解

## 作者：hloixyh (赞：3)

### 思路：

本题的绳子可以看做一个点，两端实际上没有任何用处。

每次连接相当于把两根绳子所在的集合合并。

合并可以分为两种情况：

1. 合并后没增加环，则两根绳子变成一根绳子，不是环的绳子数减一。

2. 合并后增加环了，则一根绳子变成了一根环形绳子，环的数量加一，不是环的绳子数减一。


### 代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
int fa[200005];
int ans1=0,ans2;//ans1表示环的数量，ans2表示不是环的数量。
int f(int x){
    if(x==fa[x]){
        return x;
    }
    return fa[x]=f(fa[x]);
}
void jo(int x,int y){
    int o1=f(x);
    int o2=f(y);
    ans2--;//每合并一次，不是环的绳子数量减一。
    if(o1!=o2){
        fa[o1]=o2;
    }else{
    	ans1++;//碰到环。
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	ans2=n;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=0;i<m;i++){
		int x,y;
		char a,b;
		cin>>x>>a>>y>>b;
		jo(x,y);//合并
	}
	cout<<ans1<<" "<<ans2;
	return 0;
}
```


---

## 作者：Neil_Qian (赞：2)

# [ABC293D] Tying Rope 题解

## 题目描述

有 $n$ 条绳子，每个绳子有两端，用字母 ```R``` 和 ```B``` 表示。有 $m$ 个操作，将两条绳子各自的一端（给定）连接，保证不重复、不自己连接。最后输出两个整数，第一个代表联通的绳子中形成环的数量，第二个是没有形成环的，单独的绳子也算。

## 解决方案

仔细一想会发现，一条绳子看成一个点就行了，并不需要看成两端。

将连接起来的绳子建图，不妨考虑暴力深搜，一直走下去，不能回头，如果发现下一个点被遍历过了，显然形成环了。如果一直没有上述情况的话，就不是环。统计答案即可。可以用 $vis$ 数组标记每个点是否被遍历过。

只用遍历整张图，时间复杂度 $O(n+m)$。

弱弱地问一句：题目中的颜色有什么用呢？

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=2e5+2;
int n,k,x,y,s1,s2;bool vis[N],f;vector<int> v[N];char a,b;
inline bool dfs(int x,int last){//深搜
	vis[x]=1;
	for(int t:v[x])if(t!=last){
		if(vis[t])return 1;//环
		if(dfs(t,x))return 1;//后面发现环
	}
	return 0;//后面发现链
}
int main(){
	scanf("%d%d",&n,&k);//读入
	while(k--)scanf("%d %c%d %c",&x,&a,&y,&b),
		v[x].push_back(y),v[y].push_back(x);
	for(int i=1;i<=n;i++)if(!vis[i])f=dfs(i,0),s1+=f,s2+=(f^1);//每个点判断，注意不能重复统计答案
	return printf("%d %d\n",s1,s2),0;//输出
}
```

---

## 作者：luqyou (赞：1)

# 思路

简单并查集。

每次执行连接操作的时候就把这两个绳子所在的集合连接起来。如果这两个绳子已经在一个集合中，那么显然是一个环，我们打上一个标记。

最后统计一下有几个集合，其中是环和不是环的分类处理就行了。

因为每一头最多被打结一次，所以不需要担心重复计算的问题。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m,f[maxn],iscycle[maxn],cycle,notcycle;
int find(int x){
	if(x!=f[x]) f[x]=find(f[x]);
	return f[x];
}
int main(){
 	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		f[i]=i;
	}
	for(int i=1;i<=m;i++){
		int a1,a2;
		char col1,col2;
		cin>>a1>>col1>>a2>>col2;
		int fa1=find(a1),fa2=find(a2);
		if(fa1==fa2){
			iscycle[fa1]=1;
		}
		else{
			f[fa1]=fa2;
		}
	}
	for(int i=1;i<=n;i++){
		if(iscycle[i]) cycle++;
		else if(f[i]==i) notcycle++;
	}
	cout<<cycle<<" "<<notcycle;
	return 0;
}
```

---

## 作者：Eleveslaine (赞：1)

基础图论题。  
值得一提的是，此题与 [ABC292D](https://www.luogu.com.cn/problem/AT_abc292_d) 有异曲同工之妙：都是无向图，都是并查集。  
由[这篇题解](https://www.luogu.com.cn/blog/fbi-blogs/solution-abc292d)，得前置知识：[并查集](https://www.luogu.com.cn/problem/P3367)。

## 题意

有 $n$ 根绳子，编号为 $1\sim n$，每根绳子都一端是蓝色，一端是红色。  
有 $m$ 次操作，每次操作给定 $a\ b\ c\ d$（其中字符 $b,d$ 表示颜色），表示将第 $a$ 根绳子颜色为 $b$ 的一端与第 $c$ 根绳子颜色为 $d$ 的一端连接。  
操作完成后形成了一些连通块，问这些连通块中有几个是环，有几个不是环。  
**保证同一条绳子的同一端不会被连接两次。**

例如，本题第一个样例：

![img](https://cdn.luogu.com.cn/upload/image_hosting/14ejwqh5.png)

其中橙色线段为原来的绳子，灰色为之后进行的连接。

## 分析

我们可以把绳子的端点看作点，绳子或绳子之间的连接看作边来建立无向图。图中共有 $2n$ 个点，存储时设第 $i$ 条绳子红色端点的编号为 $\operatorname{red}(i)=2i$，蓝色的为 $\operatorname{blue}(i)=2i+1$。  
题中：保证同一条绳子的同一端不会被连接两次，即**任意点的度数 $\boldsymbol{\le 2}$**。这就是说，**一个连通块要么是环，要么是链。**  
无向图连通块问题，可以使用并查集解决：连接 $u,v$，等价于在并查集中合并 $u,v$ 所在集合。如果在连接 $u,v$ 前发现 $u,v$ 已经在同一个集合里了，那么这个集合（连通块）就是一个环，计数器 $ans+1$。

之后看第二个输出，它等于**连通块个数减去环的个数**，即 $t-ans$（$t$ 为最后的集合数量）。  
如果计算 $t$？显然，最初（没有绳子，仅有端点）时，$t=2n$；之后每合并两个集合，$t$ 均减一。可以在合并集合时顺便计算 $t$ 的值。

依次操作完后，输出 $ans$ 和 $t-ans$ 的值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a,c,ans=0,t;
char b,d;
#define maxn 400002
#define maxm 400002
#define red(k) (k<<1)
#define blue(k) (k<<1|1)
int f[maxn];
inline int find(int k)
{
    if(f[k]==k)
        return k;
    return f[k]=find(f[k]);
}
// add(u,v) 合并 u,v 所在的两个集合，顺便统计 ans 和 t
inline void add(const int &u,const int &v)
{
    if(find(u)==find(v))
    {
        // 找到环
        ++ans;
        return;
    }
    f[find(u)]=find(v);
    --t;
}
int main()
{
    cin >> n >> m;
    t=2*n;
    // 初始化勿忘
    for(int i=1;i<=2*n+2;++i)
        f[i]=i;
    for(int i=1;i<=n;++i)
        add(red(i),blue(i));
    for(int i=1;i<=m;++i)
    {
        cin >> a >> b >> c >> d;
        // u,v 为 a,b 上对应颜色的点编号
        int u,v;
        if(b=='R') u=red(a);
        else u=blue(a);
        if(d=='R') v=red(c);
        else v=blue(c);
        add(u,v);
    }
    cout << ans << " " << t-ans << endl;
    return 0;
}
```

完成此题后可以试试 [ABC292D](https://www.luogu.com.cn/problem/AT_abc292_d)，同样的思路，同样的方法，~~顺便给我的题解点个赞~~。

---

## 作者：zhyou (赞：0)

## 思路
考虑并查集。

如果要连接的两条绳子本身就已经在同一个集合里了，说明其所在的联通块形成了一个环（易证，可以画图理解）。

否则就把这两条绳子所在集合合并。

注意：一个联通块可能会有多个环，不要重复统计。

之后，我们再扫描所有的点。如果这个点所在集合没有形成环且未被统计过，则让统计没有形成环的联通块的数量的数 $res + 1$。

## 代码
```
#include <bits/stdc++.h>

using namespace std;

const int N = 2 * 1e5 + 3;
int n, m;
int fa[N];
bool a[N], b[N];

int find(int x){
    if (x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}

int main(){
    scanf("%d %d", &n, &m);
    
    if (m == 0){
        printf("0 %d", n);
        return 0;
    }
    
    for (int i = 1; i <= n; i ++ ) fa[i] = i; //初始化
    
    int ans = 0, res = 0; 
    
    while ( m -- ){
        int x, y;
        char ch;
        
        cin >> x >> ch >> y >> ch;
        
        int fx = find(x), fy = find(y);
        
        if (fx == fy) {
            if (!a[fx]) { //如果未被标记有环
                ans ++;
                a[fx] = 1; //表示以 fx 为祖先的集合已经有环
            }
        }
        
        else fa[fx] = fy;
    }
    
    for (int i = 1; i <= n; i ++ ){
        int fi = find(i);
        if (!a[fi] && !b[fi]) { 
            b[fi] = 1;
            res ++;
        }
    }
    
    printf("%d %d", ans, res);
    
    return 0;
}
```

---

## 作者：liangbob (赞：0)

### AT_abc293_d 题解

#### 思路分析

一道并查集裸题。

为什么要使用并查集呢？因为题目要求连接两条绳子，同时还要判环，所以我们把绳子抽象成点，连接两条绳子抽象为用一条边连接两个点。于是就可以参考克鲁斯卡尔算法的思路，使用并查集来判环：如果两条绳子已经被连接在一条链（由绳子连接而成的连通分量）上的话，又被连接一次，就产生了环，此时产生了环的链数加一。

那么题目又要求统计非环链数，又该怎么办呢？很简单，同样使用并查集统计所有链数，一个祖先代表一条链。然后用总链数减去产生了产生了环的链数就可以了。接着按照上述步骤实现即可，注意并查集要初始化。

#### 代码

```cpp
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
 
int fa[N]; //并查集父亲数组
bool vis[N]; //判断祖先是否重复的数组
 
int find(int x) //寻找祖先
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
 
void init(int p) //初始化并查集
{
	for(int i = 1;i <= p;i++)
	{
		fa[i] = i;
	}
}
 
void merge(int i, int j) //合并两条绳子
{
	fa[find(i)] = find(j);
}
 
 
int main()
{
	int n, m;
	cin >> n >> m;
	int x = 0, z = 0; //x 用于记录有环个数，z 用来记录总链数
	init(n); //初始化并查集
	for(int i = 1;i <= m;i++)
	{
		int q, p;
		char c;
		cin >> q >> c >> p >> c; 
		if(find(q) != find(p)) //如果不在同一个链上
		{
			merge(q, p); //合并
		}
		else
		{
			x++; //已经在同一个链上，又要连接一次，就会形成环，此时有环个数加一。
		}
	}
    for(int i = 1;i <= n;i++) //遍历所有点，分别查找其祖先
    {
        int r = find(i); //查找祖先
        if(!vis[r]) //如果祖先没有计算过
        {
            z++; //计算该祖先，一个祖先代表一条链。
            vis[r] = true; //标记改祖先已被访问。
        }
    }
	cout << x << " " << z - x << endl; //输出答案，非环链数为总链数减有环链数的差
	return 0;
}
```



---

## 作者：ForgotDream_CHN (赞：0)

# ATABC293D Tying Rope

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17208530.html)

### 题意

有 $N$ 根一端涂成红色，另一端涂成蓝色的绳子，现进行 $M$ 次操作，第 $i$ 次操作给出两个整数 $A_i$，$C_i$ 与两个字符 $B_i$，$D_i$，表示将第 $A_i$ 根绳子的 $B_i$ 端与第 $C_i$ 根绳子的 $D_i$ 端连接起来。若字符为 $\texttt{R}$，则表示红色端，否则为蓝色端。

现在问你 $M$ 次操作之后绳子形成的环的数量与未能形成环的绳子段数量。

$N, M \le 2 \times 10^5$。

### 思路

看到这种有关连通性的问题，我们首先想到的肯定就是 DSU，也就是并查集。

初始化一个大小为 $2N$ 的并查集，考虑把第 $i$ 条绳子拆成 $i$ 与 $i + N$ 两个点，分别表示红段与蓝端，并把它们合并，表示他们在一开始就属于同一根绳子。

然后根据每一个操作进行合并，在合并过程中，如果出现了待合并的两个点已经属于同一个绳子段（也就是父亲相同）的情况，则说明出现了环。这样我们就求出了环的数量。

非环的数量也很好做，对每一个点都查询出它的父亲并在桶中打上标记，这样，最后被标记的数量就是总的绳子段的数量，然后再用这个数减去上边所得的环的数量，就是非环的数量。

我个人始终认为只写路径压缩的并查集时间复杂度为 $\log$ 级别的，因此总体的时间复杂度为 $O(M \log N)$。

### 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int n) {
    this->n = n;
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    return;
  }

  int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  }

  int merge(int u, int v) {
    int fau = find(u), fav = find(v);
    if (fau == fav) {
      return 1;
    }
    fa[fau] = fav;
    return 0;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  DSU dsu(2 * n + 50);
  for (int i = 1; i <= n; i++) {
    dsu.merge(i, i + n);
  }

  int ans = 0;
  for (int i = 1; i <= m; i++) {
    int u, v;
    char a, b;
    std::cin >> u >> a >> v >> b;
    ans += dsu.merge(u + (a == 'B') * n, v + (b == 'B') * n);
  }

  std::bitset<(int) 4e5 + 50> b;
  for (int i = 1; i <= 2 * n; i++) {
    b[dsu.find(i)] = true;
  }

  std::cout << ans << " " << b.count() - ans << "\n";

  return 0;
}
```

---

## 作者：Paris_Commune (赞：0)

### 分析

dfs 暴力搜索， check 函数判断是否有相同的数字，注意边界情况。 $dp_i$ 存储这条路径中数字 $i$ 是否出现过。

### AC 代码

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans;
int a[15][15];
int dp[30];
bool check(int x,int y){
	for(int i=1;i<=x+y-1;i++){
		for(int j=1;j<=x+y-1;j++){
			if(i!=j&&dp[i]==dp[j]){
				return true;
			}
		}
	}
	return false;
}
void dfs(int x, int y){
	dp[x+y-1]=a[x][y];
	if(check(x,y)||x>n||y>m){
		return;
	}
	if(x==n&&y==m){
		ans++;
	}
	if(x<n){
		dfs(x+1,y);
	}
	dp[x+y]=0;
	if(y<m){
		dfs(x,y+1);	
	}
	dp[x+y]=0;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}	
	dfs(1,1);
	cout<<ans;
	return 0;
}
```

---

## 作者：Jasper08 (赞：0)

由于一根绳子的一端至多被连接一次，所以一个连通块要么是环，要么是链。我们可以对每一个没有访问过的绳子进行一次 dfs，若遍历到已经遍历过的点说明是环，否则说明是链。

时间复杂度 $O(n+m)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5+10;

int n, m, ans1, ans2;
bool st[N];
vector<int> e[N];

bool dfs(int u, int fa) {
    st[u] = 1;
    bool check = 0;
    for (auto v : e[u]) {
        if (v == fa) continue;
        if (st[v]) return 1;
        check |= dfs(v, u);
    }
    return check;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    while (m -- ) {
        int u, v; char c1, c2;
        cin >> u >> c1 >> v >> c2;
        e[u].push_back(v), e[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (!st[i]) {
            bool check = dfs(i, -1);
            if (check) ans1 ++;
            else ans2 ++;
        }
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}
```

---

## 作者：RandomLife (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc293_d)

## 题意

有 $N$ 条绳子，每条绳子有两头，一头为红色，一头为蓝色。现在，我们要进行 $M$ 次系绳，每次讲一个绳子的红头或蓝头寄到另一条绳子的红头或蓝头上。求问所有绳子系完后，形成了环的连在一起的绳子和没形成环的连在一起的绳子各有几条？

## Solution

首先，我们要明白，题目只求环的数量和非环的数量，并没有对绳子头的颜色进行限制，因此颜色啥的只是干扰信息，可以忽略。那么剩下的就可以转换一下题意：就是给你一个无向图，问有几个连通图存在环，几个连通图不存在环。我们可以用dfs找出连通图，对于每个无向连通图，如果它边的数量大于等于点的数量，那么他就存在环，否则不存在。只需要dfs时统计一下即可得到答案。

## AC code

```c++
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <string.h>
#include <vector>
#include <math.h>
#include <stdio.h>
using namespace std;
const int N = 200010;
int n, m, cnt1, cnt2, ans1 = 0, ans2 = 0;
bool vis[N];
vector<int> adj[N];
void dfs(int x) {
    cnt1++, vis[x] = true;
    for (int i = 0; i < adj[x].size(); ++i) {
        int v = adj[x][i];
        cnt2++;
        if (!vis[v]) {
            dfs(v);
        }
    }
}
signed main() {
    memset(vis, 0, sizeof vis);
    cin >> n >> m;
    while (m--) {
        int a, b;
        char c, d;
        cin >> a >> c >> b >> d;
        adj[a].push_back(b), adj[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            cnt1 = 0, cnt2 = 0;
            dfs(i);
            if (cnt1 <= cnt2 / 2) { //很重要：无向图边会统计两次，需要除以2
                ans1++;
            } else {
                ans2++;
            }
        }
    }
    cout << ans1 << ' ' << ans2;
    return 0;
}
```

---

## 作者：incra (赞：0)

### 题意
有 $n$ 根绳子，每根有红和蓝两头，每次操作把两根绳子的某两头连接，求有多少根绑在一起的多根绳子是形成环和没有形成环的。
### 题解
考虑环的基本性质：多根绑在一起绳子若形成环则这几根绳子一定满足以下几点：

1. 绳子的红蓝两头都被绑了。（题目里说了，一个绳子的某一头最多绑一次）
2. 在连接后，所有的绳子都连通。


第 $1$ 点可以直接用数组统计，第 $2$ 点可以用并查集统计。

**注意**：单独一根绳子不成环，但是以上两点都满足，这个必须要特判。

### 代码
```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 200010;
int n,m;
int p[N];
vector <int> v[N];
int cnta[N],cntb[N];
int find (int x) {
	if (p[x] != x) p[x] = find (p[x]);
	return p[x];
}
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) p[i] = i;
	while (m--) {
		int a,b;
		char ca,cb;
		cin >> a >> ca >> b >> cb;
		if (ca == 'R') cnta[a]++;
		else cntb[a]++;
		if (cb == 'R') cnta[b]++;
		else cntb[b]++;
		p[find (a)] = find (b);
	}
	for (int i = 1;i <= n;i++) v[find (i)].push_back (i);
	int ansa = 0,ansb = 0;
	for (int i = 1;i <= n;i++) {
		if (!v[i].size ()) continue;
		bool flag = true;
		for (int x : v[i]) {
			if (cnta[x] != cntb[x] || !cnta[x] || !cntb[x]) flag = false;
		}
		if (flag) ansa++;
		else ansb++;
	}
	cout << ansa << ' ' << ansb << endl;
    return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

比赛时这题竟然没做出来！

（一）

题意：

给你 $n$ 个绳子，每个绳子两端有不同的颜色，$m$ 处打了结，形成条。

求形成环的条数和没有形成环的条数。

（二）

第 $i$ 条绳子颜色为 $R$ 的一端下标为 $i$。

第 $i$ 条绳子颜色为 $B$ 的一端下标为 $i+n$。

$a_i$ 表示 $i$ 条绳子颜色为 $R$ 的一端连的下标。

$a_{i+n}$ 表示 $i$ 条绳子颜色为 $B$ 的一端连的下标。

用 $vis_i$ 表示绳子 $i$ 是否被访问。

$ans1$ 表示形成环的条数。

$ans2$ 表示没有形成环的条数。

其余的代码里都有。

（三）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[400001],ans1,ans2;
bool vis[200001];
bool ss(int x,int fa,int s){
	if(x>n)vis[x-n]=1;
	else vis[x]=1;//访问过
	int y;
	if(x<=n)y=x+n;
	else y=x-n;//找该绳子的另一端
	if(!a[y])return 0;//没连
	if(a[y]==fa){
		return 1;//找到了
	}
	if((a[y]>n&&!vis[a[y]-n])||(a[y]<=n&&!vis[a[y]]))return ss(a[y],fa,s+1);
	return 0;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		char ch1,ch2;
		cin>>x>>ch1>>y>>ch2;
		if(ch1=='R'&&ch2=='R')a[x]=y,a[y]=x;
		if(ch1=='R'&&ch2=='B')a[x]=y+n,a[y+n]=x;
		if(ch1=='B'&&ch2=='R')a[x+n]=y,a[y]=x+n;
		if(ch1=='B'&&ch2=='B')a[x+n]=y+n,a[y+n]=x+n;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]){//没被访问过
			if(ss(i,i,1))ans1++;//形成环
			else{
				ss(i+n,i+n,1);//没有形成，把这一条剩下的搜完
				ans2++;
			}
		}
	cout<<ans1<<" "<<ans2;
	return 0;
}
```


---

## 作者：rui_er (赞：0)

颜色是不好处理的，我们不妨不区分绳子的两个端点，将每条绳子作为一个节点，每条边直接将两个节点连接起来。每个绳子的端点本质上是保证了每个点的度数不超过 $2$，也就是说图的每个连通块要么是环要么是链。题目即统计有多少个环、多少个链。

洪水填充统计每个连通块的点数、边数即可。

时间复杂度 $\mathcal O(n+m)$。

```cpp
// Problem: D - Tying Rope
// Contest: AtCoder - AtCoder Beginner Contest 293
// URL: https://atcoder.jp/contests/abc293/tasks/abc293_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 2e5+5;

int n, m, vis[N], cntV, cntE, ansA, ansB;
vector<int> e[N];

void dfs(int u) {
	vis[u] = 1;
	++cntV;
	for(int v : e[u]) {
		if(!vis[v]) dfs(v);
		++cntE;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m) {
		int u, v; char s[2], t[2];
		scanf("%d%s%d%s", &u, s, &v, t);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	rep(i, 1, n) {
		if(!vis[i]) {
			cntV = cntE = 0;
			dfs(i);
			cntE >>= 1;
			if(cntV == cntE) ++ansA;
			else ++ansB;
		}
	}
	printf("%d %d\n", ansA, ansB);
	return 0;
}
```

---

