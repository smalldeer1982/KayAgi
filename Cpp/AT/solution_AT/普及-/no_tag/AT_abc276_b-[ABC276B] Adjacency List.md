# [ABC276B] Adjacency List

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_b

$ 1,\ \dots,\ N $ と番号付けられた $ N $ 個の都市と、都市間を結ぶ $ M $ 本の道路があります。  
$ i\ \,\ (1\ \leq\ i\ \leq\ M) $ 番目の道路は都市 $ A_i $ と都市 $ B_i $ を結んでいます。

以下の指示に従い、$ N $ 行にわたって出力してください。

- 都市 $ i\ \,\ (1\ \leq\ i\ \leq\ N) $ と道路で直接結ばれた都市が $ d_i $ 個あるとし、それらを**昇順**に都市 $ a_{i,\ 1},\ \dots,\ a_{i,\ d_i} $ とおく。
- $ i\ \,\ (1\ \leq\ i\ \leq\ N) $ 行目には、$ d_i\ +\ 1 $ 個の整数 $ d_i,\ a_{i,\ 1},\ \dots,\ a_{i,\ d_i} $ を、この順番で空白区切りで出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \lt\ B_i\ \leq\ N\ \,\ (1\ \leq\ i\ \leq\ M) $
- $ (i\ \neq\ j) $ ならば $ (A_i,\ B_i)\ \neq\ (A_j,\ B_j) $
- 入力される値は全て整数

### Sample Explanation 1

都市 $ 1 $ と道路で直接結ばれているのは都市 $ 2,\ 3,\ 6 $ です。よって、$ d_1\ =\ 3,\ a_{1,\ 1}\ =\ 2,\ a_{1,\ 2}\ =\ 3,\ a_{1,\ 3}\ =\ 6 $ であるので、$ 1 $ 行目には $ 3,\ 2,\ 3,\ 6 $ をこの順番で空白区切りで出力します。 $ a_{i,\ 1},\ \dots,\ a_{i,\ d_i} $ は昇順に並んでいなければならないことに注意してください。例えば、$ 1 $ 行目に $ 3,\ 3,\ 2,\ 6 $ をこの順番で出力した場合、不正解となります。

## 样例 #1

### 输入

```
6 6
3 6
1 3
5 6
2 5
1 2
1 6```

### 输出

```
3 2 3 6
2 1 5
2 1 6
0
2 2 6
3 1 3 5```

## 样例 #2

### 输入

```
5 10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5```

### 输出

```
4 2 3 4 5
4 1 3 4 5
4 1 2 4 5
4 1 2 3 5
4 1 2 3 4```

# 题解

## 作者：Acit (赞：5)

### 题目大意:

给定一张 $n$ 点 $m$ 边的双向图，输出每个点所连接的点的个数及这张图所对应的邻接表。

### 分析：

本题比较简单，用一个数组 $b$ 存储每个点邻接点的数量，再用一个动态数组 $a$ 存储邻接点的序号，排序输出即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
vector<int>a[N];
int b[N];
//上文已给出数组含义
int n,m;
int x,y;
int main() {
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
		b[x]++;
		b[y]++;
                // 存储
	}
	for(int i=1;i<=n;i++){
		cout<<b[i]<<' ';
		sort(a[i].begin(),a[i].end());
		for(int j=0;j<a[i].size();j++){
			cout<<a[i][j]<<' ';
		}
                //排序+输出
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Fire_flame (赞：2)

## 简要翻译：

有 $n$ 个城市，它们之间有 $m$ 条双向高速公路连接。

现在请输出每一个与该城市**由高速公路直接连接**的所有城市，**城市编号升序排列输出**。

## $\mathtt{Solution}$

首先我们第一时间肯定会去建一个图，然后再排序…

这样是肯定不行的，因为 $n,m\le 10^5$，我们得想一个更好的办法。

其实到这里基本上可以想到了，把每一条边存下来，按照边两端节点的编号从小到大排个序，最后用队列存储。

**注意！！！因为是双向边，空间要开两倍！！！**

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt;
struct road{
	int a,b;
}e[200005];//注意！！！因为是双向边，空间要开两倍！！！
bool cmp(road p,road q){
	if(p.a!=q.a)return p.a<q.a;
	else return p.b<q.b;
}
struct Q{
	queue<int>q;
}pq[200005];
int num[200005];
int main(){
	scanf("%d%d",&n,&m);
	cnt=m+1;
	for(int i=1;i<=m;i++)scanf("%d%d",&e[i].a,&e[i].b);
	for(int i=cnt;i<=2*m;i++)e[i]={e[i-m].b,e[i-m].a};
	cnt=2*m;
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)num[e[i].a]++,pq[e[i].a].q.push(e[i].b);
	for(int i=1;i<=n;i++){
		printf("%d ",num[i]);
		while(num[i]--){
			printf("%d ",pq[i].q.front());
			pq[i].q.pop();
		}
		puts("");
	}
	return 0;
}

```


---

## 作者：李宇涵 (赞：1)

## 图的遍历

这是一道图论题。要求输出每个节点 $i$ 连接的节点的数量 $d_i$，再从小到大输出它连接的节点编号。

首先我们用 $n$ 个 `vector` 存储这张图，记第 $i$ 个 `vector` 为 $e_i$，代表点 $i$ 连接的所有节点。一个 `vecotr` 可以看做一个可变长度的数组，也可以像数组一样用下标访问。

然后处理 $m$ 条边。对于每条边，连接两个点 $t_1,t_2$，则添加这条边时，点 $t_1$ 所连接的点里面多了 $t_2$，点 $t_2$ 所连接的点里面也多了 $t_1$。所以把 $t_2$ 放进 $e_{t_1}$ 里面，再把 $t_1$ 放进 $e_{t_2}$ 里面。

输出节点 $i$ 连接的节点编号时，要从小到大输出，所以还要对每个节点 $i$ 的 $e_i$ 里面的数进行排序。对第 $i$ 个 `vector` 进行排序的方法如下：

`sort(e[i].begin(),e[i].end());`

输出时，扫描每个 `vector`，先输出连接节点数量，也就是 `vector` 的大小。第 $i$ 个 `vector` 的大小是 `e[i].size()`。再遍历 $e_i$，输出排好序的每个节点编号（注意 `vector` 从 $0$ 开始）。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
vector<ll> e[100010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=m;i++)
	{
		ll t1,t2;
		cin>>t1>>t2;
		e[t1].push_back(t2);
		e[t2].push_back(t1);
	}
	for(ll i=1;i<=n;i++) sort(e[i].begin(),e[i].end());
	for(ll i=1;i<=n;i++)
	{
		cout<<e[i].size()<<' ';
		for(ll j=0;j<e[i].size();j++) cout<<e[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：xiaohaoaibiancheng66 (赞：0)

# 思路
题目让我们按照邻接表的顺序输出，我们即可建一个邻接表。

这个邻接表用什么来建呢？这里使用 STL 中的 vector 来建。因为 vector 长度不固定，空间复杂度只有 $O(M)$。

最后，该怎么排序呢？将一个 vector $v$ 排序也可以用 sort。用法是 `sort(v.begin(),v.end())`。

时间复杂度为小常数+$O(M\log M)$，空间复杂度为 $O(M)$，可以通过。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
 
vector<int> bian[1000000];
 
int main()
{
	ios::sync_with_stdio(0);
	int n,m,x,y;
	cin>>n>>m;
    //建表
	while(m--)
	{
		cin>>x>>y;
		bian[x].push_back(y);
		bian[y].push_back(x);
	}
    //排序
	for(int i=1;i<=n;i++)sort(bian[i].begin(),bian[i].end());
    //输出
	for(int i=1;i<=n;i++)
	{
		cout<<bian[i].size()<<' ';
		for(auto v:bian[i])cout<<v<<' ';
		cout<<endl;
	}
	return 0;
 } 
```


---

## 作者：sunzz3183 (赞：0)

# [ABC276B] Adjacency List 题解

## 题意

给定一张无向图，输出每个点的度并按编号从小到大输出与它相连第边，没有重边。

## 分析

不需要建图，我们可以开一个队列，每次加边时，把每个点加入另一个点的队列。因为要从小到大输出与它相连的点，所以我们可以把队列改为优先队列。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+5;
int n,m;
priority_queue<int>q[N];//这里其实是小根堆，因为存的时候是用负数存的
signed main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int a=read(),b=read();
		q[a].push(-b);q[b].push(-a);
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",q[i].size());
		while(!q[i].empty())printf("%lld ",-q[i].top()),q[i].pop();
		puts("");
	}
	return 0;
}		
```


---

## 作者：hyc1026 (赞：0)

本题是一道不错的邻接表入门题。

看到题目描述：

- 给定一张 $n$ 个点 $m$ 条边的双向图。
- 你需要输出一张邻接表，按照邻居编号单调递增存储。

让我们依次来实现。

---

存储一张双向图：

看到 $n,m\le 10^5$，我们很容易可以想到不可以用邻接矩阵去做，我们应该使用邻接表。

邻接表可以用 `vector` 存储。以下是代码示例：

```cpp
vector<int> a[N];

int begin, end;
cin >> begin >> end;

a[begin].push_back(end);
a[end].push_back(begin);

```

通过以上代码，我们就可以从 `begin` 节点到 `end` 节点建立一条双向边。

---

按顺序输出：

首先我们需要知道，`vector` 可以用 `std::sort` 进行排序，排序方法为：

```cpp
sort(vec.begin(), vec.end());
```

以上代码可以将整个 `vec` 这一个 `vector` 从小到大排序。

遍历输出：

使用 `vec.size()` 可以获得 `vec` 的长度。所以以下代码可以遍历并输出。

```cpp
for(int i=0; i<vec.size(); i++)
	cout << vec[i] << " ";

```

---

综上所述，我们做完了这道题。

AC 的思路（不是代码）

```cpp
vector<int> a[100001];
 
int main()
{
	int n, m;
	cin >> n >> m;
	while(m--)
	{
	    在 begin 和 end 间建立一个双向边。
	}
	对于每一个 vector, 进行排序。
	遍历输出。
}
```

[Code](https://www.luogu.com.cn/paste/dhoqzkts)

---

