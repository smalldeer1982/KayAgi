# Gifts by the List

## 题目描述

Sasha lives in a big happy family. At the Man's Day all the men of the family gather to celebrate it following their own traditions. There are $ n $ men in Sasha's family, so let's number them with integers from $ 1 $ to $ n $ .

Each man has at most one father but may have arbitrary number of sons.

Man number $ A $ is considered to be the ancestor of the man number $ B $ if at least one of the following conditions is satisfied:

- $ A=B $ ;
- the man number $ A $ is the father of the man number $ B $ ;
- there is a man number $ C $ , such that the man number $ A $ is his ancestor and the man number $ C $ is the father of the man number $ B $ .

Of course, if the man number $ A $ is an ancestor of the man number $ B $ and $ A≠B $ , then the man number $ B $ is not an ancestor of the man number $ A $ .

The tradition of the Sasha's family is to give gifts at the Man's Day. Because giving gifts in a normal way is boring, each year the following happens.

1. A list of candidates is prepared, containing some (possibly all) of the $ n $ men in some order.
2. Each of the $ n $ men decides to give a gift.
3. In order to choose a person to give a gift to, man $ A $ looks through the list and picks the first man $ B $ in the list, such that $ B $ is an ancestor of $ A $ and gives him a gift. Note that according to definition it may happen that a person gives a gift to himself.
4. If there is no ancestor of a person in the list, he becomes sad and leaves the celebration without giving a gift to anyone.

This year you have decided to help in organizing celebration and asked each of the $ n $ men, who do they want to give presents to (this person is chosen only among ancestors). Are you able to make a list of candidates, such that all the wishes will be satisfied if they give gifts according to the process described above?

## 说明/提示

The first sample explanation:

- if there would be no $ 1 $ in the list then the first and the third man's wishes would not be satisfied $ (a_{1}=a_{3}=1) $ ;
- if there would be no $ 2 $ in the list then the second man wish would not be satisfied $ (a_{2}=2) $ ;
- if $ 1 $ would stay before $ 2 $ in the answer then the second man would have to give his gift to the first man, but he wants to give it to himself $ (a_{2}=2) $ .
- if, at the other hand, the man numbered $ 2 $ would stay before the man numbered $ 1 $ , then the third man would have to give his gift to the second man, but not to the first $ (a_{3}=1) $ .

## 样例 #1

### 输入

```
3 2
1 2
2 3
1 2 1
```

### 输出

```
-1```

## 样例 #2

### 输入

```
4 2
1 2
3 4
1 2 3 3
```

### 输出

```
3
2
1
3
```

# 题解

## 作者：water_tomato (赞：3)

## 题意
[题目链接](https://www.luogu.com.cn/problem/CF681D)

需要寻找一种可行的候选人列表并输出，注意每个人在候选人列表找出第一个自己的祖先就会送出礼物。
## 解析
首先，如果一个人是某一个人的送礼物目标，则这个人就**一定会出现在答案序列里**。

而如果一个人的祖先已经出现在名单里了的话，则这个祖先的所有儿子即使后续再在列表中出现，也是**无意义**的。因此我们考虑**拓扑排序**，建一张**反图**，并得出该图的拓扑序，再除去其中**不成为任何人的礼物目标**的无意义序号。

这样我们得到了一张图，根据上述性质，如果当前根据拓扑拟定的方案无法满足每个人的要求，则**一定不存在一种方案能够满足**，因为该方案已经让需要较早出现的点尽可能早出现了。因此，我们只需要判断该方案能否满足要求，若不能，输出 $-1$。

我们用拓扑序（已去掉不需要的点），即目前的方案遍历每一个点，每一次将该点以及该点跑**正图**能够到达的点，也就是该点的所有儿子的实际送礼物目标都标记为这个点。当然，已经标记过的点不会被覆盖。

最后再将得到的这个目标与每个人的原始要求一一对比，若出现不符合的，输出 $-1$ ,否则输出该方案即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
struct edge{
	int to,next,from,pre;
}e[N<<1];
int head[N],cnt,prehead[N];
inline void add(int x,int y){//反图为 next，正图为 pre。 
	e[++cnt].to=y;
	e[cnt].next=head[x];
	e[cnt].from=x;
	e[cnt].pre=prehead[y];
	head[x]=cnt;
	prehead[y]=cnt;
}
int a[N],ru[N];
bool inans[N];
int tp[N],tot,Cnt;//tp[]表示拓扑序 
int ans[N];
inline void topo(){//找拓扑序 
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(!ru[i]) q.push(i);
	}
	while(!q.empty()){
		int u=q.front();
		tp[++tot]=u;
		q.pop();
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			ru[v]--;
			if(!ru[v]) q.push(v);
		}
	}
}
int fa[N];//表示每个点实际的送礼物目标 
void dfs(int u, int f) {
    if (fa[u]) {
        return;
    }
    fa[u] =f;
    for (int i=prehead[u];i;i=e[i].pre) {
        int v=e[i].from;
        dfs(v,f);
    }
}
 
int main() {
   scanf("%d%d",&n,&m);
    for (int i=1,x,y;i<=m;i++) {
        scanf("%d%d",&x,&y);
        add(y,x);
        ru[x]++;
    }
    for (int i=1;i<=n;i++) {//统计那些点需要出现在答案里 
        scanf("%d",&a[i]);
        inans[a[i]]=true;
    }
    topo();
    for (int i=1;i<=n;i++) {
        if (inans[tp[i]]) {//只有需要成为目标的点才需要遍历。 
            dfs(tp[i],tp[i]);
            ans[++Cnt]=tp[i];//记录答案方案 
        }
    }
    for (int i=1;i<=n;i++) {//将实际目标与需求目标对比 
        if (fa[i]!=a[i]) {
            cout<<-1;
            return 0;
        }
    }
    printf("%d\n",Cnt);
    for (int i=1;i<=Cnt;i++) 
		printf("%d\n",ans[i]);
    return 0;
}
```


---

## 作者：封禁用户 (赞：2)

对于任意一个人，其在列表里面找到的第一个祖先一定为他想送的人。限制有图上的拓扑关系，想送礼物欲望与人的双射以及列表本身的先后关系。

- 结论：如果一个结点的爱慕比自己的祖先前，祖先肯定要和它抢爱慕。比祖先后同理。所以一个结点和自己的所有祖先拥有同一个喜欢的人！

对于每个祖先，向自己的后代连边。形成一棵树，自底而上的，对于自己送自己礼物的直接进入列表，对于结点到没有祖先结点的那一段，都应该被爱慕的人贡献到。那么根据规则，我们只需要对自恋的人入表即可！

正确性：自底而上的入表顺序是不会影响到上层结点的。

```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#include <immintrin.h>
#include <emmintrin.h>
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e6 + 5;
const int Max = 0x3f3f3f3f3f3f3f3f;
int n, m;
int deg[inf];
int want[inf];
vector<int> g[inf];
queue<int> qwq;

void dfs(int x, int fa)
{
	for (int v : g[x])
		dfs(v, x);
	if (want[x] == x)
		qwq.push(x);
	else if (want[x] != want[fa])
		cout << "-1\n", exit(0);
}


signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		deg[v]++;
	}
	for (int i = 1; i <= n; i++)
		cin >> want[i];
	for (int i = 1; i <= n; i++)
		if (deg[i] == 0)
			dfs(i, 0);
	cout<<qwq.size()<<'\n';
	while (!qwq.empty()) {
		cout << qwq.front() << '\n';
		qwq.pop();
	}
	return 0;
}
```

---

## 作者：xzggzh1 (赞：1)

我感觉现有的那一篇题解的做法复杂了。

题意:

一个家族有 $n$ 个人， $m$ 种关系，每一种关系表示 $x$ 是 $y$ 的祖先，祖先具有传递性，然后有 $n$ 个数，表示第 $i$ 个人想把礼物送给 $a[i]$ , 你需要构造一张表这张表上的人代表收礼物的人，并且其他人送礼物是按表上的顺序找，找到的第一个祖先就是他要送礼的人，同时需要满足这个人是他想送礼的人，如果存在这张表输出人数及编号，否则输出 $-1$ （题意中自己也算是自己的一个祖先）。

---

题解：

稍微读一读题目，反复理解一下题意，就会发现其实这个题目这么长其实说的就是一件事情：

对于甲的祖先里和甲不是同一个目标的人乙必有甲的目标不是乙的祖先。

用反证法证明：

若甲的目标是乙的祖先，那么要是甲送给他的目标礼物，乙也必须送给这个人礼物而不是他原来的目标。

如何用程序来解决这个事情。

建图时先将所有祖先向他儿子建里单向变，然后从零入度的点开始遍历。

使得对于所有点都有 他的目标为他自己 或 他的父亲和他是同一个目标，那么就可以构造出一个合理的方案。

到这里，题目已经可以解决了，但是其实上面那个条件我这里只证明了他是有合理方案的必要条件，而这个条件的充分性可以留给读者自己思考，这里不多赘述。

下面是代码：

```cpp
#include <bits/stdc++.h>
#define For(pos) for(int k=First[pos];k;k=Next[k]) 
inline int R(){char c;int res,sign=1;while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';return res*sign;}
int n,m,First[Maxn],Next[Maxn*2],to[Maxn*2],cnt,ind[Maxn],aim[Maxn],ans[Maxn],top;
inline void add(int z,int y){Next[++cnt]=First[z];First[z]=cnt;to[cnt]=y;++ind[y];}
using namespace std;
const int Maxn=1e5+5;
inline void dfs(int pos,int father)
{
    For(pos) dfs(to[k],pos); 
    if(aim[pos]==pos) ans[++top]=pos;
    else if(aim[pos]!=aim[father])//我父亲的祖先不能比我的祖先近 
    {puts("-1");exit(0);}
}
int main()
{
    n=R();m=R();int x,y;
    for(int i=1;i<=m;i++)
    {
        x=R();y=R();
        add(x,y);//祖先到自己 
    }
    for(int i=1;i<=n;i++) aim[i]=R();
    for(int i=1;i<=n;i++) if(!ind[i]) dfs(i,0);
    printf("%d\n",top);
    for(int i=1;i<=top;i++) printf("%d\n",ans[i]);
}


```

---

