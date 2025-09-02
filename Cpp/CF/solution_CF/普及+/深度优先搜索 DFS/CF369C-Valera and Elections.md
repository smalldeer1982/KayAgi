# Valera and Elections

## 题目描述

The city Valera lives in is going to hold elections to the city Parliament.

The city has $ n $ districts and $ n-1 $ bidirectional roads. We know that from any district there is a path along the roads to any other district. Let's enumerate all districts in some way by integers from $ 1 $ to $ n $ , inclusive. Furthermore, for each road the residents decided if it is the problem road or not. A problem road is a road that needs to be repaired.

There are $ n $ candidates running the elections. Let's enumerate all candidates in some way by integers from $ 1 $ to $ n $ , inclusive. If the candidate number $ i $ will be elected in the city Parliament, he will perform exactly one promise — to repair all problem roads on the way from the $ i $ -th district to the district $ 1 $ , where the city Parliament is located.

Help Valera and determine the subset of candidates such that if all candidates from the subset will be elected to the city Parliament, all problem roads in the city will be repaired. If there are several such subsets, you should choose the subset consisting of the minimum number of candidates.

## 样例 #1

### 输入

```
5
1 2 2
2 3 2
3 4 2
4 5 2
```

### 输出

```
1
5 
```

## 样例 #2

### 输入

```
5
1 2 1
2 3 2
2 4 1
4 5 1
```

### 输出

```
1
3 
```

## 样例 #3

### 输入

```
5
1 2 2
1 3 2
1 4 2
1 5 2
```

### 输出

```
4
5 4 3 2 
```

# 题解

## 作者：wick (赞：2)

一道树的题目

```
题目简译（意译+瞎搞）

题目背景

瓦莱拉居住的城市将举行市议会的选举。
这个市由于议员的斗争，这个市的道路年久失修，坏了很多。为了当选，议员决定修路来获取取居民的信任（虚伪）。但议员特别抠门（好坏呀）只想修个数最少的若干区域到议会间的路（方便自己通行）,而使得所有损坏的道路都能得到修复。

题目描述

该市共有n个区域,标号1....n。其中1号为市议会所。
一共有n-1条双向管道,连通了n个区域。其中有些路了。
现在可以选择一些区域,被选择的区域到市议会所之间的道路都将被重新修整。
请选择个数最少的若干区域,使得所有损坏的道路都能得到修复.

ps:Valera是个议员，请你帮他（你到底要不要助虐为猖呢）。

输入

第一行,整数n.(1≤N≤1e5)
下面n-1行,每行描述一条道路.整数u,v,x,表示城市u和v之间有道路,x=1表示正常,x=2表示损坏.

输出

第一行,整数k,表示你选择的城市个数.
第二行,k个整数,以空格分隔,表示你选择的城市标号.
有多种方案时,应当输出字典序最小的.



```
既然是棵树，那就从1号点开始，大胆往下扫呗。

先建路，然后扫 ~~（屁话）~~

扫到一个点，它的下面是坏的，是该直接记下下面这个点吗？

应该先标记下，若下面还有坏的点，就将标记清掉，记更往下的点（如样例1）。

那么我们可以在dfs中加上father这个变量（“应该先标记下”所描述的点），下面还有就(将father的标记清掉，再更新father为当前“若下面还有坏的点”所描述的点)，下面以ans未标记。

还有个问题，就是字典序最小。

![](https://cdn.luogu.com.cn/upload/image_hosting/y0xvmuas.png)

这样选的点肯定不是3，而是2.

故要再开一个函数,将你用ans记下的点再往下扫,扫出字典序更小的点(或自己),存一下,排序,再输出。

这样又有问题啦！！

万一这玩意儿往1的方向往回扫则么办（因为加的是双向路），开个数组num记每个点的深度是多少即可（故在dfs中加了h这个变量）

这下可大功告成啦。

小细节请读者，自行把握，毕竟这道灰题，通过率100%。

有图为证：

![](https://cdn.luogu.com.cn/upload/image_hosting/67pqssjq.png)



```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k,tem;
int num[200005];
vector <int> E[200005];
map <int,int> mark[200005];
bool book[200005];
bool ans[200005];
void dfs(int now,int father,int h) {
	book[now]=1;
	num[now]=h;
	for(int k=0; k<E[now].size(); k++) {
		if(book[E[now][k]]) continue;
		if(mark[now][E[now][k]]==2) {
			ans[E[now][k]]=1;
			ans[father]=0;
			dfs(E[now][k],E[now][k],h+1);
		} else dfs(E[now][k],father,h+1);
	}
}
void findmin(int now) {
	for(int k=0; k<E[now].size(); k++) {
		if(num[E[now][k]]<num[now]) continue;
		tem=min(tem,E[now][k]);
		findmin(E[now][k]);
	}
}
int main() {
	cin>>n;
	for(int j=1; j<n; j++) {
		int e,u,w;
		cin>>e>>u>>w;
		mark[e][u]=w;
		mark[u][e]=w;
		E[e].push_back(u);
		E[u].push_back(e);
	}
	dfs(1,1,1);
	int cnt=0;
	for(int j=1; j<=n; j++)
		if(ans[j]) cnt++;
	printf("%d\n",cnt);
	vector <int> w;
	for(int j=1; j<=n; j++)
		if(ans[j]) {
			tem=j;
			findmin(j);
			w.push_back(tem);
		}
	sort(w.begin(),w.end());
	for(int j=0; j<w.size(); j++)
		printf("%d ",w[j]);
	return 0;
}
```


---

## 作者：Yexuaj (赞：1)

来康康这道目前通过率接近100%的题目

题目里说可以输出任意一种方案，那么不管字典序是否最小都能过，本人亲测。

为了让答案有顺序，我用了优先队列（其实不需考虑顺序，用队列也可）

这里先用bfs从上往下搜索，记录对于每个点到1区之间有多少条坏的道路，再根据坏掉的道路数从大到小排序，再进行深搜。

我用的是从下往上搜，所以用数组记录了父节点。

具体见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n;
vector <int> E[maxn],L[maxn];//用邻接矩阵记录
int dis[maxn],father[maxn];
bool v[maxn];

priority_queue <int , vector < int > , greater< int > > PRO;//用于记录最终答案

struct o {
	int num;
	int p;
} um[maxn];//用于记录点p（或者说议员p）到1区之间有多少条坏的道路

void s(int a,int b,int x) {
	E[a].push_back(b);
	L[a].push_back(x);
}

void dfs(int p,int m,bool flag) {//m是p向下得到的最小的点，flag是记录是否下面的点有一个被修复，如果有则不需要再修复
	if(p==1)return;
	int i;
	for(i=0;i<E[p].size();++i)
		if(E[p][i]==father[p])break;
	if(flag==false) {
		if(L[p][i]==2) {
			PRO.push(m);
			flag=true;
		}
	}
	if(v[father[p]]==false) {
		v[father[p]]=true;
		dfs(father[p],min(father[p],p),flag);
	}
}

void bfs() {
	for(int i=1; i<=n; ++i)
		um[i].p=i;
	queue <o> q;
	o a;
	a.num=0;
	a.p=1;
	q.push(a);
	v[1]=true;
	while(!q.empty()) {
		o b=q.front();
		um[b.p].num=b.num;
		q.pop();
		for(int i=0; i<E[b.p].size(); i++) {
			if(!v[E[b.p][i]]) {
				o c;
				father[E[b.p][i]]=b.p;
				c.num=b.num+L[b.p][i]-1;
				c.p=E[b.p][i];
				v[E[b.p][i]]=true;
				q.push(c);
			}
		}
	}
}

bool cmp(o A,o B) {
	if(A.num!=B.num)return A.num>B.num;
	else return A.p<B.p;
}

void solve() {
	bfs();
	sort(um+1,um+1+n,cmp);
	memset(v,0,sizeof(v));
	for(int i=1; i<=n; ++i) {
		if(dis[um[i].p]==1) {
			dfs(um[i].p,um[i].p,false);
		}
	}
}

int main() {
	scanf("%d",&n);
	for(int i=1; i<n; ++i) {
		int u,v,x;
		scanf("%d%d%d",&u,&v,&x);
		dis[u]++;
		dis[v]++;
		s(u,v,x);
		s(v,u,x);
	}
	solve();
	cout<<PRO.size()<<'\n';
	while(!PRO.empty()) {
		cout<<PRO.top()<<' ';
		PRO.pop();
	}
	return 0;
}

```

当然，上面这个代码感觉bug还是很多，也不是很好理解，如果想看如何输出字典序最小的方案，那就继续往下看吧。

------------

显然，对于深度较浅的点，如果再往下走还有要修的边的话，这个点是不需要修的，因为修了下面的点，这条边自然会被修好。

那么，有一种操作是自然而正确的，那就是：

#### 如果向下走还有需要修的点的话，可以直接把这条边标记为不用修的边。

那么最后计算答案时，就不用再考虑这条边了。

那么找到一个要修的点，再往下寻找数码最小的即可。

这个思路是比较清晰的，比上面的思路好理解一些，正确性也是显然的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n;
vector <int> E[maxn],L[maxn];
bool v[maxn];

priority_queue <int, vector <int> , greater <int> > ans;//同样用优先队列记录答案，保证最后输出的答案是有序而字典序最小的

bool sign(int a,int b,int x) {
	E[a].push_back(b);
	L[a].push_back(x);
}

bool pre(int now,int last) {//使向下还要修的边变为不用修，因为是一棵树，所以访问只要不访问到上次来的点就不会死循环
	bool flag=false;
	for(int i=0; i<E[now].size(); ++i) {
		if(E[now][i]==last)continue;
		if(pre(E[now][i],now)==true) {
			L[now][i]=1;
			flag=true;
		}
		if(L[now][i]==2)
			flag=true;
	}
	return flag;
}

int getmin(int p,int l) {//向下寻找最小值
	int tmp=p;
	for(int i=0; i<E[p].size(); ++i) {
		if(E[p][i]==l) continue;
		tmp=min(tmp,getmin(E[p][i],p));
	}
	return tmp;
}

void dfs(int p,int l) {
	for(int i=0; i<E[p].size(); ++i) {
		if(E[p][i]!=l) {
			if(L[p][i]==2) 
				ans.push(getmin(E[p][i],p));
			else dfs(E[p][i],p);
		}

	}
}

void prepare() {
	scanf("%d",&n);
	for(int i=1; i<n; ++i) {
		int u,v,x;
		scanf("%d%d%d",&u,&v,&x);
		sign(u,v,x);
		sign(v,u,x);
	}
	pre(1,0);
}

int main() {
	prepare();
	v[1]=true;
	dfs(1,0);
	cout<<ans.size()<<'\n';
	while(!ans.empty()) {
		cout<<ans.top()<<' ';
		ans.pop();
	}
	return 0;
}

```


---

