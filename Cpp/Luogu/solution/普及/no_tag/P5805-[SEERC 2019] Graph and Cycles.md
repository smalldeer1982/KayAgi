# [SEERC 2019] Graph and Cycles

## 题目描述

有一个 $n$ 个点的无向有边权的完全图，其中 $n$ 是奇数。

定义一个大小为 $k$ 的*环边组*为一个边构成的数组 $[e_1, e_2, \dots, e_k]$，且具有以下性质：

- $k$ 大于 $1$。
- 对于任意 $[1, k]$ 中的整数 $i$，边 $e_i$ 与 $e_{i-1}$ 和 $e_{i+1}$ 都恰好有一个相同的端点（规定 $e_0=e_k, e_{k+1}=e_1$）。

显然一个环边组中的边构成了图上的一个环。

定义一个参数为两条边 $e_1, e_2$ 的函数 $f(e_1, e_2)$，其函数值为两条边中边权的较大值。

定义一个环边组 $C=[e_1, e_2, \dots, e_k]$ 的*价值*为对于任意 $[1, k]$ 中的整数 $i$，$f(e_i, e_{i+1})$ 的值之和（规定 $e_{k+1}=e_1$）。

定义一个图的*环分割*为一组无交集的环边组，且这些环边组的并包含了图上所有的边。定义一个图的环分割的*价值*为其中所有环边组的价值之和。

一个图可能存在多组环分割。给定一个图，你的任务是找到价值最小的环分割并输出该最小价值。

## 说明/提示

以下样例解释中，边以输入顺序编号，$e_i$ 代表输入顺序中的第 $i$ 条边。

第一个样例中，唯一的环分割为 $S=\{ [e_1, e_2, e_3] \}$。$f(e_1, e_2)+f(e_2,e_3)+f(e_3,e_1)=1+1+1=3$。

第二个样例中，最优的环分割为 $S=\{ [e_3, e_8, e_9], [e_2,e_4,e_7,e_{10},e_5,e_1,e_6] \}$。环边组 $[e_3,e_8,e_9]$ 的价值为 $12$，$[e_2,e_4,e_7,e_{10},e_5,e_1,e_6]$ 的价值为 $23$，因此环分割的价值为 $35$。

## 样例 #1

### 输入

```
3
1 2 1
2 3 1
3 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
4 5 4
1 3 4
1 2 4
3 2 3
3 5 2
1 4 3
4 2 2
1 5 4
5 2 4
3 4 2```

### 输出

```
35```

# 题解

## 作者：SAMSHAWCRAFT (赞：4)

本题解旨在补充其他题解做法的推理过程。

注意本题中特别提及了点数是奇数，即 $n \bmod 2 = 1$，而本图是一个 $n$-完全图，即 $(n-1)$-正则图，这意味着每个顶点的度数都是 $n-1$，这是一个偶数，不妨设 $n-1=2i$，则在这个图的环分割当中，每个顶点都被且仅被 $i$ 个环通过，且每个环上通过这个顶点的边有且只有 $2$ 条。

接下来思考如何统计答案，通过前面分析，一个顶点的 $2i$ 条边中一定有且只有 $i$ 条被统计进了答案当中，至于这 $i$ 条边分别属于哪个环其实并不重要。可以构造性地证明：假设 $e_x$ 是被统计在答案当中的 $i$ 条边之一，$e_y$ 是未被统计在答案当中的 $i$ 条边之一，只要保证 $f(e_x,e_y)$ 就是 $e_x$ 的边权即可，这样我们就可以把 $e_x$ 和 $e_y$ 放进一个环当中而不需担心这两条边具体在哪一个环，因此这个构造转化成下面的问题：给一个长度为 $2i$ 的序列 $\{w\}$，要把这个序列分成 $i$ 对不相交的元组 $(w_{x_j},w_{y_j})$ 使得 $w_{x_j} \ge w_{y_j}$  对任意的 $j \in [1,i]$ 成立，求最小化的 
$$\sum_{j=1}^i w_{x_j}$$

这是一个贪心问题，给序列从小到大排序，然后使 $x_j=2j,y_j=2j-1$ 就可以取得最小值。这样的话本题就完成了，代码如下。

``` cpp
#include <iostream>
#include <algorithm>
#include <vector>
const int sz=1e3+9;
int n,m;
long long ans;
std::vector<int> edges[sz];
int main(){
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cout.sync_with_stdio(false);
  std::cin>>n;
  m=(n*(n-1))>>1;
  for(int cx=0,u,v,w;cx!=m;++cx){
    std::cin>>u>>v>>w;
    edges[u].push_back(w);
    edges[v].push_back(w);
  }
  for(int cx=1;cx<=n;++cx)
    std::sort(edges[cx].begin(),edges[cx].end());
  for(int cx=1;cx<=n;++cx){
    for(int cy=1;cy!=n;cy+=2)
      ans+=edges[cx][cy];
  }
  std::cout<<ans<<std::endl;
  return 0;
}

```

---

## 作者：xht_37 (赞：2)

# 本题思路

对于每条边，如果其权值大，那么尽量去接连权值较大的边。

所以，要将各条边按照其权值进行排序，之后从权值大的边开始取。

这里就是很明显的**贪心**算法。

对于当前边的左、右两个顶点，分别去判断是否可以连到之前的大权值边上，若可以则连接。

每个点有且仅有一条连上的大权值的边，另一条未能匹配而空出的边，用一个数组来一一记录。

# 本题代码

代码很简单，进行须要的几个操作即可。

```cpp
#include <iostream>
#include <vector> // 图
#include <algorithm> // sort() 排序
std::vector<int>G[1050];
int main() {
	int n;
	std::cin >> n;
	int l = n * (n - 1) / 2; // 避免多次运算
	for (int i = 1; i <= l; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back(w);
		G[v].push_back(w);
	}
	long long ans = 0; // 别忘开 long long ！
	for (int i = 1; i <= n; i++) {
		std::sort(G[i].begin(), G[i].end());
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < n; j += 2) {
			ans += G[i][j]; // 累计分割的价值
		}
	}
	std::cout << ans;
	return 0;
}
```

---

## 作者：CoronaQL (赞：2)

# 思路
每条边，如果其权值大，那么尽可能接连权值较大的边。将边按照权值排序，从大的开始取。对于当前边的左右顶点，分别去判断是否可以连到之前的大权值边上，可以就连上去，由于每个点只会有一条空出来边（没连上的大权值边），所以用一个数组来记录没有匹配的大权边。其余的大家看代码
# AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxN =1e3+2;//日常赋值骚操作，大家别介意，只是为了精简代码 
int n,m;
vector<int> vt[maxN];
int main()
{
    scanf("%d",&n);
    m=n*(n-1)/2;
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        vt[u].push_back(w);//退回操作 
        vt[v].push_back(w);
    }
    long long ans = 0;
    for(int i=1; i<=n; i++) sort(vt[i].begin(), vt[i].end());//熟悉的sort 
    for(int u=1; u<=n; u++)
    {
        for(int i=1;i<n; i+=2)
        {
            ans+=vt[u][i];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
# 注意
代码速度慢，但终归AC，勿喷。

---

## 作者：VioletIsMyLove (赞：2)

贪心的小题，一个顶点出去的 $2$ 条边，再抓一条边立马就是环。

$N$ 是奇数,那么每个顶点出去偶数条边，
不管和谁构成圈，按照由小到大的顺序对每个顶点出去的边权排序，相邻两个在同一个圈里，只有这样才能导致最后最小。


Code:
```cpp
#include<bits/stdc++.h>
#define LL long long
#define maxn 1005
#define maxe 1000005
using namespace std;
int N,M,cnt,lnk[maxn],nxt[maxe],w[maxe];
LL Ans;
struct ZS{
	int x,y,w;
	bool operator <(const ZS &B)const{return w<B.w;}
}A[maxe];
int read(){
	int ret=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-')f=-f;ch=getchar();}
	while (isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return ret*f;
}
void add_e(int x,int y,int z){w[++cnt]=z;nxt[cnt]=lnk[x];lnk[x]=cnt;} 
int main(){
	freopen("cycles.in","r",stdin);
	freopen("cycles.out","w",stdout);
	N=read();M=N*(N-1)/2;
	for (int i=1;i<=M;i++) A[i].x=read(),A[i].y=read(),A[i].w=read();
	sort(A+1,A+1+M);
	for (int i=1;i<=M;i++){
		int x=A[i].x,y=A[i].y,z=A[i].w;
		add_e(x,y,z),add_e(y,x,z);
	}
	for (int i=1;i<=N;i++)
	for (int j=lnk[i];j;){
		int w_one=w[j];j=nxt[j];
		int w_two=w[j];j=nxt[j];
		Ans+=max(w_one,w_two);
	}
	printf("%lld\n",Ans);
	return 0;
}
```


---

## 作者：Silence_World (赞：1)

# 思路

很明显的贪心，如果一个点往外引边的话，如果有两条，那再加一条一定成环，先排个序，然后把在同一个环里的加上就行了。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int>a[1000005];
int sum=0;
signed main()
{
	int n;
	cin>>n;
    for(int i=1;i<=n*(n-1)/2;i++)
    {
    	int u,v,p;
    	cin>>u>>v>>p;
		a[u].push_back(p);
		a[v].push_back(p) ;
    }
    for(int i=1;i<=n;i++)sort(a[i].begin(), a[i].end()); 
    for(int v=1;v<=n;v++)
    {
        for(int i=1;i<n;i+=2)
        {
            sum+=a[v][i];
        }
    }
    cout<<sum;
    return 0;
}

```



---

## 作者：yxy666 (赞：1)

贪心的小题，一个顶点出去的 $2$ 条边，再抓一条边立马就是环。N是奇数,那么每个顶点出去偶数条边，
不管和谁构成圈，按照由小到大的顺序对每个顶点出去的边权排序，相邻两个在同一个圈里，只有这样才能导致最后最小。

$code$ ：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1005;

struct reader{
	template<typename Type>
	reader&operator>>(Type&ret){
		int f=1; ret=0; char ch=getchar();
		for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-f;
		for(; isdigit(ch);ch=getchar()) ret=(ret<<1)+(ret<<3)+(ch-'0');
		ret*=f; return *this;
	}
}fin;

int N,x,y,z;
int edge[maxn][maxn];
long long Ans;

int main(){
	fin>>N;
	for(int i=(N-1)/2*N;i>=1;i--){
		fin>>x>>y>>z;
		edge[x][++edge[x][0]]=z;
		edge[y][++edge[y][0]]=z;
	}
	for(int i=1;i<=N;i++) sort(edge[i]+1,edge[i]+N);
	for(int i=1;i<=N;i++)
	for(int j=2;j<=N-1;j+=2) Ans=Ans+edge[i][j];
	cout<<Ans<<endl;
	return 0;
} 
```


---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P5805)
# 思路
每条边，如果其权值大，那么尽可能接连权值较大的边。

将边按照权值排序，从大的开始取。

对于当前边的左右顶点，分别去判断是否可以连到之前的大权值边上，如果可以就连上去，因为每个点有且仅有一条没有连上的大权值的边，所以用一个数组来一一记录没有匹配的大权边。
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=999+5;
vector<int> adj[N];
signed main()
{
	int n;
	cin >>n;
	int m=n*(n-1)/2;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin >>u>>v>>w;
		adj[u].push_back(w);
		adj[v].push_back(w);
	}
	for(int i=1;i<=n;i++) sort(adj[i].begin(),adj[i].end());
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<n;j+=2)
		{
			sum+=adj[i][j];
		}
	}
	cout <<sum;
	return 0;
}

```

---

## 作者：Amunet (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5805)

## 算法：

很明显的贪心。

## 思路：

一个顶点如果有 $2$ 条边，再加一条边一定就是环。只需要从小到大排序，再把同一个环里的加起来就可以了。

---

## 作者：wsh88 (赞：0)

### 思路：

很简单，这道题就是一道贪心的题。

先将各条边按照其权值进行排序，之后从权值大的边开始取。

对于一条边的左右顶点，分别去判断是否可以连到之前的大权值边上，可以就连上去。

由于每个点有且仅有一条连上的大权值的边，所以只会有一条边空出来，那么我们就可以用一个数组来记录这些空出来的边。

### 代码：


```cpp
#include <bits/stdc++.h> //万能头 
using namespace std;
vector<int> a[1101];
int n,m;
long long ans; //不开long long见祖宗 
int main(){
	int u,v,w;
	cin>>n;
	int m=n*(n-1)/2; //图的边数
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w; //u和v是这条边左右两边的点 ，w是此边的全职权值 
		a[u].push_back(w);//由于是无向图，所以要双向建边 
		a[v].push_back(w); 
	}
	for(int i=1;i<=n;i++) sort(a[i].begin(),a[i].end());
	for(int i=1;i<=n;i++)
		for(int j=1;j<n;j+=2)
			ans+=a[i][j]; //算出分割的价值 
	cout<<ans;
	return 0;
}
```

---

