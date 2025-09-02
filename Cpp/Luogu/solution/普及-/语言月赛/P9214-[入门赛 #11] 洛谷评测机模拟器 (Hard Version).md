# [入门赛 #11] 洛谷评测机模拟器 (Hard Version)

## 题目背景

**本题与 Easy Version 题意完全相同，不同的地方在于数据范围。**

现在假装你是洛谷评测机。这一天，洛谷同时进行了 PION 自测、SCP 自测、ION 自测等等比赛。成千上万的评测落到了你的身上！

## 题目描述

现在已经知道你有 $n$ 个相同性能的评测节点，它们被分别标号为 $1, 2, \cdots, n$。一个评测节点在同一时间只能处理一个评测任务。

在某一时刻，$m$ 个评测任务同时涌入了你。我们将这些任务分别标号为 $1, 2, \cdots, m$。这些评测任务需要的评测时间分别为 $t _ 1 , t _ 2, \cdots, t _ m$。每个评测任务**需要且仅需要一个**评测节点来运行，因此你会按照如下方式按照 $1 \sim m$ 的顺序依次将这些评测任务分配到评测节点上：

对于某个耗时 $t _ i$ 的评测任务，你需要找到目前**累积评测时间**最小的评测节点将任务放入。如果有多个评测节点**累积评测时间**相同且最小，则找一个**标号最小**的节点将任务放入。

> 「累积评测时间」定义：假设对于某个评测节点，其被分配了 $a _ 1, a _ 2, \cdots, a _ k$ 共 $k$ 个任务。那么这个评测节点的「累积评测时间」就是 $t _ {a _ 1} + t _ {a _ 2} + \cdots + t _ {a _ k}$。显然的，如果某个评测节点从未被分配过这 $m$ 个任务中的任何一个，那么这个评测节点的「累积评测时间」是 $0$。

现在，你需要统计出，你的这 $n$ 个评测节点分别接受了哪一些评测任务。

## 说明/提示

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 5 \times 10 ^ 5$，$0 \leq t _ i \leq 10 ^ 9$。

## 样例 #1

### 输入

```
5 10
13 50 90 38 60 64 60 77 6 24```

### 输出

```
1 6
2 8
3
4 7
5 9 10```

## 样例 #2

### 输入

```
12 7
85 99 82 90 14 11 15```

### 输出

```
1
2
3
4
5
6
7
0
0
0
0
0```

# 题解

## 作者：2021sunzishan (赞：8)

一道不错的练优先队列的题目。

这篇题解讲得比较细，非常适合新手。
## 题目大意：
有 $n$ 个评测节点来完成 $m$ 个评测任务，每个任务需要时间 $t$，每次将第 $i$ 个任务分配给总用时最少的评测节点，若总用时相同则分配到编号较小的节点，输出每个节点所分配的任务编号，没分配到任务则输出 $0$。

## 思路：

看到“每次都分配到总用时最少的评测节点”这句话，我想都没想，直接用优先队列。

### 步骤：
1. 开一个小根堆。堆中要维护两个元素，一个是节点编号，一个是总用时，所以直接开一个结构体。

2. 将 $n$ 个节点全部压入堆，此时总用时为 $0$。

3. 每次读入一个时间 $t$，就弹出堆顶元素，将此节点的总用时加上 $t$，再压回堆中，用一个 vector 来存储每次分配到的编号。

4. 最后输出 vector 当中存储的值就可以了。

如果还是不懂，就看代码吧！

### 切勿抄袭！！！
## 代码：
```
#include <bits/stdc++.h>
using namespace std;
inline int read(){//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int n,m;
vector<int>a[500005];//记录答案的vector(不能用数组，n*m会爆空间)
struct node{//结构体
	long long s;//总用时，别忘了开long long(t<=10^9,m<=10^5,爆int了)
	int op;//节点编号
	bool operator >(const node &k)const{//重载运算符
		if(s!=k.s)return s>k.s;//如果用时不相同，就按用时排
		else return op>k.op;//否则按节点编号排
	}
};
priority_queue<node,vector<node>,greater<node> >q;//小根堆
//以上为步骤1
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++){//初始化(步骤2)
		node k;
		k.op=i,k.s=0;
		q.push(k);
	}
	for(int i=1;i<=m;i++){//处理(步骤3)
		int t=read();
		node k=q.top();//弹出堆顶
		q.pop();
		k.s+=t;//总用时加上t
		q.push(k);//压回堆
		a[k.op].push_back(i);//加入答案中
	}
	for(int i=1;i<=n;i++){//输出答案(步骤4)
		for(int j=0;j<a[i].size();j++)
			printf("%d ",a[i][j]);
		if(a[i].size()==0)printf("0");//如果没有分配到，输出0
		printf("\n");
	}
	return 0;
}


```
完结~

---

## 作者：dyyzy (赞：6)

内容简述：STL 优先队列，多种方式实现小根堆。

## 思路

首先，最朴素的思路是用数组记录每个评测点所用时间，每当有一个新任务开始测评时，$O(n)$ 查找当前用时最短的评测点并统计答案。复杂度 $O(nm)$ ~~（显然过不了）~~。

不过对于每个任务，我们只关心当前所用时间最少的评测点，所以我们可以考虑使用堆优化查找过程。

~~为了图省事~~，我们使用 STL 的 `priority_queue` 代替手写堆，但由于 STL 默认为大根堆，我们需要一些操作把它变成小根堆。怎么实现呢，我们有以下几种方法：

### 使用STL小根堆

```cpp
priority_queue<int, vector<pair<long long,int> >,greater<pair<long long,int> > > pq;
```

不多解释了，只需要注意一下连续的尖括号 `>` 中间需要有空格，否则就会 CE。

### 结构体重载小于号

```cpp
struct Node {
	long long data;//用时 
	int num;//编号 
};
bool operator <(const Node &a,const Node &b) {
	return (a.data==b.data)?a.num>b.num:a.data>b.data;
}
 ```

我们可以这么理解这个函数的返回值，如果返回值为 `true`，则说明 $a$ 的优先级比 $b$ 的优先级小，因为 `priority_queue` 是大根堆，所以 $b$ 就会被放到堆顶。

### 使用一种神奇的思想

引理： 对于两个正数 $a$ , $b$ 若 $ a \lt b $ ， 则 $ -a \gt -b $。

证明：~~显而易见~~。

所以我们可以依旧使用大根堆，不过将所有要插入的元素以相反数的形式插入，就可以使用大根堆实现小根堆了。不过值得一提的是，取出元素是别忘了取相反数。

## Code

```cpp
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#define mp make_pair
using namespace std;
inline int read() {
	int x=0;
	char ch=getchar();
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();//使用位运算优化的快读，感兴趣的可以查度娘
	return x;
}
const int N=5e5+10;
priority_queue<pair<long long,int> > pq;//不开long long见祖宗
vector<int> e[N];//必须使用vector，否则空间复杂度达到O(nm)，会MLE
int a[N];
int main() {
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) pq.push(mp(0,-i));//取相反数
	for(int i=1; i<=m; ++i) a[i]=read();
	for(int i=1; i<=m; ++i) {
		pair<long long,int> tmp=pq.top();
		pq.pop();
		tmp.first-=a[i];//取相反数*2
		e[-tmp.second].push_back(i);//统计答案（取相反数*3）
		pq.push(tmp);
	}
	for(int i=1; i<=n; ++i) {
		if(!e[i].size()) cout<<"0\n";
		else {
			for(int j:e[i])
				cout<<j<<' ';
			cout<<'\n';
		}
	}
}
```

---

## 作者：zzx114514 (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/P9214)
## 题目大意
当前共有 $n$ 个节点来完成任务，给出 $m$ 个任务，每个任务需要 $t_i$ 时间，每次将第 $i$ 个任务分配给当前总用时最少的节点，若总用时相同则分配到编号较小的节点，输出每个节点所分配的任务编号，没分配到任务则输出 $0$。
## 解题思路
拿到本题第一想法就是暴力解决，时间复杂度为 $O(nm)$，显然超时。  
考虑优化。在暴力算法中，对于每个任务 $m_i$，我们都要对节点进行遍历，找出总用时最少的节点，每次查询的时间复杂度为 $O(n)$，导致超时。这里我采用了堆的数据结构。堆是一种处理最值的类似树的数据结构，可以很快地找出总用时最少的节点。使用小根堆，每次查询，只需将节点压入堆中，堆顶元素就是最小值。我个人习惯使用 `STL` 库中的优先队列来实现堆。
## 解题代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,t;
vector<long long> v[500005];//使用vector存储节点完成的任务编号 
struct Node
{
	long long id,time;//所有数据开long long,不开long long见祖宗，我在这里卡了好久QwQ 
	bool operator>(const Node &a) const
	{
		if (time==a.time) return id>a.id;
		return time>a.time;
	}//重载大于号运算符，实现小根堆 
};
priority_queue<Node,vector<Node>,greater<Node> > node;//建立一个小根堆存放节点 
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++) node.push({i,0});//初始化所有节点用时为0 
	for (int i=1;i<=m;i++)
	{
		cin>>t;
		Node x=node.top();//记录当前堆顶 
		x.time+=t;//加上当前用时 
		node.pop();//弹出堆顶 
		node.push(x);//压入更新后编号为i的节点 
		v[x.id].push_back(i);//记录当前节点所完成的任务 
	}
	for (int i=1;i<=n;i++)
	{
		if (v[i].empty()) cout<<0;
		else for (int j=0;j<v[i].size();j++) cout<<v[i][j]<<' ';
		cout<<endl;
	}//输出，注意特判当前节点未完成任务的状况 
	return 0;//华丽的结尾 
}


```


---

## 作者：HHYQ_07 (赞：1)

# 题解

## 题目大意

当前共有 $n$ 个节点来完成 $m$ 个任务，每个任务需要 $t_i$ 时间，每次将第 $i$ 个任务分配给当前总用时最少的节点，若总用时相同则分配到编号较小的节点，输出每个节点所分配的任务编号，没分配到任务则输出 $0$。

## 思路

看到题目，我们发现要求的是每个时刻一组数据中的的最小值，且数据在不停变化。首先想到排序，但排序的时间复杂度很高，冒泡排序、插入排序等都是 $O(n^3)$ 的复杂度，即使是快一点的归并排序、桶排序也是 $O(n^2\log{n})$ 的复杂度，而题目中 $n \leq 5 \times 10^5$，所以这样是肯定不行的。紧接着想到每次暴力枚举一遍，但它是 $O(mn)$ 的时间复杂度，也不行。最后想到 STL 中的[优先队列](https://oi.wiki/lang/csl/container-adapter/)，复杂度 $O(n \log n)$ 可以过，于是就开开心心地去实现了。

## 一些细节

1. 要存评测节点编号和完成时间，所以要用结构体储存。

2. 结构体要自己写仿函数，比较式第一关键字为时间，第二关键字为编号。

3. 本题会爆 int，需开 long long。

## $AC code$

详细代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,x;
vector<int>ans[500005];//方便储存最后的答案
struct node
{
	int v,num;
};
struct cmp//仿函数
{
	operator ()(node a,node b)
	{
		if(a.v==b.v)return a.num>b.num;
		return a.v>b.v;
	}
};
priority_queue<node,vector<node>,cmp>a;
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		a.push((node){0,i});//预处理，先开出n个节点，以后就只用更改了
	for(int i=1;i<=m;i++)
	{
		cin>>x;
		ans[a.top().num].push_back(i);//存答案
		int vv=a.top().v+x,numm=a.top().num;
		a.pop();
		a.push((node){vv,numm});
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i].size())
			for(int j=0;j<ans[i].size();j++)
				cout<<ans[i][j]<<" ";
		else cout<<"0";//如果没有一个任务的话别忘了要输出0
		puts("");
	}
	return 0;
}
```
请求管理员大大通过。

---

## 作者：ssSSSss_sunhaojia (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P9214)
# 大致思路：
根据题意，我们从 $1$ 到 $m$ 枚举每一个任务，取出此时累积评测时间最短的评测节点，将当前任务存入此评测节点所要评测的任务中，然后更新此评测节点的累积评测时间。最后输出就行了。

另外，为了快速地求出累积评测时间最短的评测节点，我们要维护一个优先队列来存储评测节点的累积评测时间以及编号。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL n, m, a[1001001]; 
vector <LL> v[550000]; 
struct no {
	LL x, id; 
};
priority_queue<no> q; 
bool operator < (const no x, const no y) {return x.x > y.x || x.x == y.x && x.id > y.id; }//优先队列的排序规则
in void read(LL &x){
	x = 0;LL f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + (ch - 48),ch = getchar();}
	x *= f;
}
in void write(LL x){
    if(x < 0){putchar('-');x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int main(){
	IOS;
	cin >> n >> m; 
	for(re int i = 1; i <= m; i ++) cin >> a[i];//输入
	for(re int i = 1; i <= n; i ++) q.push(no{0, i});//初始化，0为时间总和，i位编号
	for(re int i = 1; i <= m; i ++) {
		no now = q.top(); //取出此时累积评测时间最短的评测节点
		v[now.id].push_back(i); //将当前任务存入此评测节点所要评测的任务中
		q.pop(); q.push(no{now.x + a[i], now.id}); //更新累积评测时间
	}
	for(re int i = 1; i <= n; i ++, cout << "\n") {
		for(re int j = 0; j < v[i].size(); j ++)
			cout << v[i][j] << " ";	//输出
		if(v[i].size() == 0) cout << 0; //细节，如果为空的话要输出一个0
	}
	return 0;
}


```

---

## 作者：Darkworldmystery (赞：0)

原题链接：[P9214 [入门赛 #11] 洛谷评测机模拟器 (Hard Version)](https://www.luogu.com.cn/problem/P9214)

## 题意

一个评测机有 $n$ 个节点，现在出现 $m$ 个评测任务，每个评测任务需要时间 $t_i$，每次都会把第 $i$ 个任务分配给当前用时最少的节点。特别地，若时间相同则分配给编号较小的节点，输出每个节点所分配的任务编号，没分配到任务则输出 $0$。

## 思路

首先注意数据范围 $1 \le n,m \le 5 \times 10^5$，如果运用暴力算法解决时间复杂度为 $O(nm)$，一定超时，那我们怎么优化呢？

对于每个任务，我们只考虑当前所用时间最少的节点，所以我们可以使用小根堆来优化查找过程。

1. 题目里就可以知道，这个堆里需要有两个元素：节点编号和节点总用时。

2. 初始化评测节点，`for` 循环将编号和用时压入堆，这里的用时是 $0$，编号就是 $i$。

3. 循环评测任务数量，输入的任务时间和堆顶的元素加起来，就是现在的节点时间了，用一个 `vector` 储存编号，然后再入堆。

4. 格式输出 `vector` 中的数。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e5 + 5;
int n, m;
vector<int> vt[N];
struct Edge
{
	int tim, id;
	bool operator > (const Edge &x)const
    {
		if(tim != x.tim)
            return tim > x.tim;
		else
			return id > x.id;
	}
};
priority_queue<Edge, vector<Edge>, greater<Edge> >pq;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		Edge cur;
		cur.tim = 0;
		cur.id = i;
		pq.push(cur);
	}	
	for(int i = 1, x; i <= m; i++)
    {
		cin >> x;
		Edge tot = pq.top();
		pq.pop();
		tot.tim += x;
		pq.push(tot);
		vt[tot.id].push_back(i);
	}
	for(int i = 1; i <= n; i++)
    {
		for(int j = 0; j < vt[i].size(); j++)
			cout << vt[i][j] << " ";
		if(vt[i].size() == 0)
            cout << 0;
        cout << "\n";
	}
	return 0;
}

```

---

## 作者：__zfy__ (赞：0)

### 题意

有 $n$ 个评测节点来完成 $m$ 个评测任务，每个任务需要时间 $t_i$，每次将第 $i$ 个任务分配给总用时最少的评测节点，若总用时相同则分配到编号较小的节点，输出每个节点的编号，没分配到任务则输出 $0$。
### 前置知识

[STL 优先队列](https://blog.csdn.net/ray_kong/article/details/121786748)，[C++多关键字排序](https://blog.csdn.net/m0_63613132/article/details/128769113)[C++多关键字排序](https://blog.csdn.net/m0_63613132/article/details/128769113)。
### 思路

本题可以用优先队列来实现：

- 预处理：开出 $n$ 个节点。
- 每读入一个 $x$ 就要把答案存进到队列中。
- 排序：优先考虑时间（第一关键字），时间相同就考虑第二关键字（编号）。
- 输出答案，把每个任务输出，如果没有任务的话输出 $0$。
### 注意事项

1. 本题因精度要开 `long long`。
2. 结构体排序可以用 `cmp` 也可以用重载运算符。
3. 要注意输出零的情况，加一个特判。

### 代码

观众大哥，自己写吧，思路已经讲的很清楚了。

---

