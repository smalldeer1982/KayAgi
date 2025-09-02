# Not Assigning

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ , with edges numbered from $ 1 $ to $ n-1 $ . A tree is a connected undirected graph without cycles. You have to assign integer weights to each edge of the tree, such that the resultant graph is a prime tree.

A prime tree is a tree where the weight of every path consisting of one or two edges is prime. A path should not visit any vertex twice. The weight of a path is the sum of edge weights on that path.

Consider the graph below. It is a prime tree as the weight of every path of two or less edges is prime. For example, the following path of two edges: $ 2 \to 1 \to 3 $ has a weight of $ 11 + 2 = 13 $ , which is prime. Similarly, the path of one edge: $ 4 \to 3 $ has a weight of $ 5 $ , which is also prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/3add991eaafca4c0491e3513c8ebd38f1627bca9.png)Print any valid assignment of weights such that the resultant tree is a prime tree. If there is no such assignment, then print $ -1 $ . It can be proven that if a valid assignment exists, one exists with weights between $ 1 $ and $ 10^5 $ as well.

## 说明/提示

For the first test case, there are only two paths having one edge each: $ 1 \to 2 $ and $ 2 \to 1 $ , both having a weight of $ 17 $ , which is prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/22666e3c2f70cbd5edc23fd608081fffda0715fc.png)The second test case is described in the statement.

It can be proven that no such assignment exists for the third test case.

## 样例 #1

### 输入

```
3
2
1 2
4
1 3
4 3
2 1
7
1 2
1 3
3 4
3 5
6 2
7 2```

### 输出

```
17
2 5 11
-1```

# 题解

## 作者：LEE114514 (赞：3)

## 思路

首先，质数中除了 $2$ 都是大于 $1$ 的奇数。

其次，两个大于 $1$ 的奇数的和一定是大于 $2$ 的偶数，绝对不会是质数。

因此，如果满足条件，相邻的两条边一定**一个是二，另一个是奇质数**。

假如一个点连了超过两条边，那么就不能满足条件，因为假如第三条边是偶数就会和 $2$ 冲突，是奇数就会和奇质数冲突。

于是我们发现，原图必然是一条链，否则无解。

对于链上的边，由于可以有重复权值，$2$，$3$ 交替构造即可。

---

## 作者：wosile (赞：3)

自己VP了这场，做到了C，赛后做到了E

**引理**：这棵树必然是链的结构，否则无法填数

**证明**：如果这棵树中有一个点的度数 $>2$，设此点所连接的边中的三条赋的值分别为 $a,b,c$

首先，$a,b,c$ 中最多有 $1$ 个 $2$，否则有 $2+2=4$，$4$ 不是质数

又因为 $a,b,c$ 都是质数，不是 $2$ 就是奇数，则 $a,b,c$ 中有 $2$ 个奇质数

不妨设这两个奇质数为 $a,b$，则 $a+b$ 是一个 $\geq 6$ 的偶数，不是质数，不成立

---
既然这棵树已经退化成链，那就简单了

我们只需要交替着给这条链上的边赋上 $2$ 和 $3$，那么 $2,3,2+3$ 都是质数，符合题意

---
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int d[100005];
int u[100005],v[100005];
vector<pair<int,int> >T[100005];
int ans[100005];
void dfs(int rt,int fa,int col){
	for(int i=0;i<T[rt].size();i++)if(T[rt][i].first!=fa){
		ans[T[rt][i].second]=col+2;//由于col是0和1，所以col+2就是2和3，当然可以不这么写
		dfs(T[rt][i].first,rt,col^1);//col交替着变为0和1
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<n;i++)scanf("%d%d",&u[i],&v[i]);
		for(int i=1;i<=n;i++)d[i]=0;
		for(int i=1;i<=n;i++)T[i].clear();
		for(int i=1;i<n;i++){
			d[u[i]]++;
			d[v[i]]++;
			T[u[i]].push_back(make_pair(v[i],i));
			T[v[i]].push_back(make_pair(u[i],i));
		}
		int f=0;
		for(int i=1;i<=n;i++)if(d[i]>=3)f=1;//不是链
		if(f==1){
			printf("-1\n");
			continue;
		}
		int s=-1;
		for(int i=1;i<=n;i++)if(d[i]==1)s=i;//找到这个链的一端
		dfs(s,0,0);
		for(int i=1;i<n;i++)printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：zhaoyp (赞：2)

# Solution
 
首先给出一个结论：**如果存在满足要求的权值分配方案，则树的形态一定是一条链。**

考虑反证法，如果不是一条链，那么在树中必然会存在如图所示的分界点。

由于每条边权都为质数且相邻两条边边权和为质数，所以相邻两条边其中一条边的边权一定是 $2$，另一条边的边权一定是偶数。

假定连接节点 $1$ 和 $2$ 的边的边权为 $2$，那么另两条边边权都是偶数，所以连接节点 $3$ 和 $4$ 的边的边权和为合数，矛盾。

最后只用将链上的边权依次构造为 $2,3,2,3\dots$ 即可。（当然还有其它的构造方法。）

![](https://cdn.luogu.com.cn/upload/image_hosting/g7xd5cup.png)

---

## 作者：LRL65 (赞：2)

可以发现，**满足条件的图必定是一条链**。因为如果有分叉，必会不满足条件。

那么对于链，我们只需使每条边 `2 3 2 3……2 3` 即可，因为相邻两边之和 `2+3=5` 是一个质数。这样是满足条件的。

所以分为两步：

1. 判断是否是链，如不是，输出 `-1` 。
1. 如果是链，那么就 `2 3 2 3……2 3` 赋值。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans[100005];
vector<pair<int,int> >e[100005];
void dfs(int x,int fa,int la) {
    for(int i=0;i<e[x].size();i++) {
        if(e[x][i].first==fa)continue;
        if(fa==0&&i==1)la=5-la;
        ans[e[x][i].second]=5-la;
        dfs(e[x][i].first,x,5-la);
    }
}
int main() {
    cin>>t;
    while(t--) {
        cin>>n;
        for(int i=1;i<=n;i++)e[i].clear();
        for(int i=1;i<n;i++) {
            int u,v;
            cin>>u>>v;
            e[u].push_back(make_pair(v,i));
            e[v].push_back(make_pair(u,i));
        }
        bool flag=0;
        for(int i=1;i<=n;i++) 
            if(e[i].size()>2)flag=1;
        if(flag==1) {
            cout<<-1<<endl;
            continue;
        }
        dfs(1,0,2);
        for(int i=1;i<n;i++)cout<<ans[i]<<" ";
        cout<<endl;
    }
}
```


---

## 作者：zzhbpyy (赞：1)

### [原题传送门](https://www.luogu.com.cn/problem/CF1627C)

## 思路

考虑两个中间包含两条边的点，显然每条边的边权都得是质数，又两边的边权之和为质数，故任意相邻两边之中必有一条边的边权为 $2$。仔细观察猛然发现当且仅当整个图是一条链时有解，因为若有一个度为 $3$ 的点，与之相连的三条边的中必有两条边权之和为非 $2$ 的偶数，故不符合条件。

对于一条链的构造就非常简单了，直接交替填入 $2$ 和 $17$ 即可。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int u,v,nxt;
}a[200005];
int t,u,ct,n,head[100005],v,c[200005],deg[100005];
void add(int u,int v){
	a[++ct]={u,v,head[u]};
	head[u]=ct;
}
void dfs(int u,int fa,int id){//fa是父节点，id是上一条边的编号
	for(int i=head[u];i;i=a[i].nxt){
		int v=a[i].v;
		if(v==fa)continue;
		if(c[id]==2)c[i]=17;
		else c[i]=2;
		dfs(v,u,i);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		ct=0;
		memset(head,0,sizeof head);
		memset(deg,0,sizeof deg);
		memset(c,0,sizeof c);
		cin>>n;
		for(int i=1;i<n;i++){
			cin>>u>>v;
			deg[u]++,deg[v]++;
			add(u,v);
			add(v,u);
		}
		for(int i=1;i<=n;i++){
			if(deg[i]>=3){
				cout<<"-1\n";
				goto A;
			}
		}
		for(int i=1;i<=n;i++){
			if(deg[i]==1){
				dfs(i,0,0);break;
			}
		}
		for(int i=1;i<n;i++){
			cout<<(c[i*2]?c[i*2]:c[i*2-1])<<' ';
		}cout<<'\n';
		A:;
	}
}
```

---

## 作者：Purslane (赞：1)

## Solution

构造题 . 题目翻译有些坑害人 , 大意应为 :

给定一颗树 , 请您给每个边赋上一个权值 , 使所有长度不大于 2 的链中 , 组成这条链的边的边权和是质数 .

显然 , 每一条边都是一个长度为 1 的链 , 所以每一条边的长度都是质数 .

每一条长度为 2 的链都是由两条长度为 1 的链拼接而成的 .

也就出现了经典的 **质数+质数=质数** .

由小学奥数 , 加数中肯定有一个为 **2** .

考虑每一个点 , 长度为 2 的链肯定是由这个点的两条边组成的 . 

把每一个点的边分成 2 个集合 : 边权为 2 和边权不为 2 .

显然 , 因为每个边的边权都是质数 , 所以边权不为 2 的都是奇数 .

如果有 2 个数在同一个集合 , 那么它们的和一定为大于等于 4 的偶数 , 也就是有边权和不为质数的长度为 2 的链存在 !

那么一个点最多连有 2 条边 , 说明整棵树都是一条链 !

那么自顶往下 2 和 3 交替赋值即可 .

[code](https://codeforces.com/contest/1627/submission/144919050)

---

## 作者：PosVII (赞：1)

**前言**

------------

自己整了场VP，打完发发题解。样例诈骗差评。

本题是构造题，建议评蓝/绿。

**思路**

------------

我们可以知道，若两个质数之和还是质数，那么其中一个质数一定是 $2$。

那么，当树上只要有一个点度数大于 $2$ 的话显然不可行（连接到同一点上的任意两边之和都为质数那么有且只有一条边可以为 $2$ 于是不行）。这就意味着这个树是一条链。那么搜索找到链的头部然后交叉赋值即可，我是使用 $2$、$5$ 交叉赋值。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
template<typename G>inline void read(G&x){x=0;G f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();x*=f;}
template<typename G>inline void write(G x){if(x<0) putchar('-'),x=-x;G y=10,len=1;while(y<=x){y*=10;++len;}while(len--){y/=10;putchar(x/y^48);x%=y;}}
const int MAXN=2e5+5;
int t,n,u,v,r;
int head[MAXN],nxt[MAXN],to[MAXN],val[MAXN],cnt;
bool f;
void add(int x,int y) {
	nxt[++cnt]=head[x];
	head[x]=cnt;
	to[cnt]=y;
}
void dfs(int p,int las) {
	int sum=0;
	for(int i=head[p];i;i=nxt[i]) {
		++sum;
		int t=to[i];
		if(t!=las) dfs(t,p);
	}
	if(sum>2) f=1;
	if(sum==1) r=p;
}
void push(int p,int las,int s) {
	for(int i=head[p];i;i=nxt[i]) {
		int t=to[i];
		if(t!=las) {
			if(s==2) val[i]=val[(i&1?i+1:i-1)]=5;
			else val[i]=val[(i&1?i+1:i-1)]=2;
			push(t,p,val[i]);
		}
	}
}
int main() {
	read(t);
	while(t--) {
		read(n);
		cnt=f=0;
		for(int i=1;i<=n;++i) head[i]=0;
		for(int i=1;i<n;++i) {
			read(u),read(v);
			add(u,v),add(v,u);
		}
		dfs(1,0);
		if(f) {
			puts("-1");
			continue;
		}
		push(r,0,5);
		for(int i=1;i<=cnt;i+=2) printf("%d ",val[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：2021hych (赞：0)

# 简要/形式化题意
给定一个无边权无根树，请为每条边赋边权，使得所有边数不大于 $2$ 的树链中，边权和为质数。
# 题解
对于所有边数为 $1$ 的树链，显然，此边权一定是质数，因此树上的所有边的边权均为质数。

对于所有边数为 $2$ 的树链，需要满足两条边权相加仍然是质数，即质数加质数仍为质数。如果是两个奇（偶）质数相加必然会得到一个大于 $2$ 的偶数（合数，舍去）。那么必然一个是偶素数 $2$，另一个是奇质数 $p$，满足 $p+2 \in \mathbb{P}$。

对于一个度数为 $3$ 的点 $k$，设与其相邻的三个点为 $a,b,c$。则 $a \rightarrow k \rightarrow b$（树链 $1$），$a \rightarrow k \rightarrow c$（树链 $2$），$b \rightarrow k \rightarrow c$（树链 $3$），三条树链必然都只包含一个边权 $2$。如果 $a \rightarrow k$ 的边权为 $2$，则在树链 $1$ 中，$k \rightarrow b$ 不为 $2$，在树链 $2$ 中，$k \rightarrow c$ 不为 $2$，那么与树链 $3$ 的约束条件矛盾。同理可证其他情形均不成立。当度数大于 $3$ 时，由于包含了度数为 $3$ 这个子集，故也是无解。综上可得，有解的充要条件为树的形态是一条链。

那么一个简单的构造方案是从度数为 $1$ 的点开始遍历整条链，按 $2,p,2,p\cdots$ 的顺序给边赋边权。由于是构造一组可行解，这里就取 $p=3$ 了。
# AC code
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T,n,u,v,ans[N];
int deg[N],flag[N];
map<pair<int,int>,int>Map;
vector<int>G[N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--) {
		memset(deg,0,sizeof(deg));
		memset(flag,0,sizeof(flag));
		cin>>n;
		for(int i=1;i<=n;i++) G[i].clear();
		for(int i=1;i<n;i++) {
			cin>>u>>v;
			if(u>v) swap(u,v);
			Map[make_pair(u,v)]=i;
			G[u].push_back(v);
			G[v].push_back(u);
			deg[u]++;
			deg[v]++;
		}
		bool f=false;
		for(int i=1;i<=n;i++)
			if(deg[i]>=3) {
				cout<<-1<<endl;
				f=true;
				break;
			}
		if(f) continue;
		int st;
		for(int i=1;i<=n;i++) 
			if(deg[i]==1) {
				st=i;
				break;
			}
		int cnt=0,pre;
		while(cnt<=n-1) {
			cnt++;
			pre=st;
			flag[pre]=1;
			for(int i=0;i<G[pre].size();i++) {
				int now=G[pre][i];
				if(flag[now]) continue;
				st=now;
			}
			if(cnt&1) ans[Map[make_pair(min(st,pre),max(st,pre))]]=2;
			else ans[Map[make_pair(min(st,pre),max(st,pre))]]=3;
		}
		for(int i=1;i<n;i++) cout<<ans[i]<<" ";
		cout<<endl;
		for(int i=1;i<=n;i++) 
			for(int j=0;j<G[i].size();j++)
				Map[make_pair(min(i,G[i][j]),max(i,G[i][j]))]=0;
	}
	return 0;
}

```

---

## 作者：ArrogHie (赞：0)

## 题解

由于多于两个质数的情况下必然有至少两个奇数，奇数之和为偶数，所以每个节点最多连两条边，故该树是一条链，否则无解。构造链之后将边依次赋值 $2$ 和 $3$ 即可。

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1627C](https://www.luogu.com.cn/problem/CF1627C)

* **【解题思路】**

有一个结论：符合条件的树，它每个结点的度不超过 $2$，即，这棵树是一条链。

证明很简单。假如有一个点连着一些的边，那么这棵树要合法必须让这些边两两的权值和均为质数，且这些边本身权值也要是质数。那么，显然如果连着 $3$ 条及以上的边，必定有两条边的奇偶性相同，又因为它们均为质数，所以和必定为大于 $2$ 的偶数，显然不是质数。

那么，我们想要构造方案就很简单了：从这条链的一个端点开始依次给交替边的权值赋上 $2$ 与 $3$。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

array<pair<int,int>,100001> links,edges;
array<int,100001> degs,vals,vised;

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int cnt;
		int startp,cntp=1;
		cin>>cnt;
		for(int i=0;i<=cnt;i++)
			degs[i]=vals[i]=vised[i]=0,links[i]=edges[i]=make_pair(0,0);
		for(int i=1;i<cnt;i++)
			cin>>edges[i].first>>edges[i].second,++degs[edges[i].first],++degs[edges[i].second];
		for(int i=1;i<=cnt;i++)
			if(degs[i]>2)
			{
				cout<<-1;
				goto endcase;
			}
		for(int i=1;i<=cnt;i++)
			if(degs[i]==1)
			{
				startp=i;
				break;
			}
		vals[startp]=vised[startp]=1;
		for(int i=1;i<cnt;i++)
		{
			if(!links[edges[i].first].first)
				links[edges[i].first].first=edges[i].second;
			else
				links[edges[i].first].second=edges[i].second;
			if(!links[edges[i].second].first)
				links[edges[i].second].first=edges[i].first;
			else
				links[edges[i].second].second=edges[i].first;
		}
		while(cntp<cnt)
		{
			int tmp=(vised[links[startp].first]?links[startp].second:links[startp].first);
			vals[tmp]=vals[startp]+1;
			vised[tmp]=1;
			startp=tmp;
			cntp++;
		}
		for(int i=1;i<cnt;i++)
			cout<<(min(vals[edges[i].first],vals[edges[i].second])%2?2:3)<<' ';
		endcase:cout<<'\n';
	}
 	return 0;
}


```

---

