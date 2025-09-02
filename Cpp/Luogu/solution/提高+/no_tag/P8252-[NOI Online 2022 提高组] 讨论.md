# [NOI Online 2022 提高组] 讨论

## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

**这一题中出现了评测记录测试点编号错乱的问题，是民间数据命名方式冲突导致的。但是我们保证其相对顺序没有混乱。**

民间数据提供者：@AutumnKite，由 @tiger2005 进行加强。

## 题目描述

有 $n$ 个人正在打模拟赛，模拟赛有 $n$ 道题目。  
有两人都会的题目并且没有人会的题目包含另一个人时，两者之间才会讨论。  
（定义第 $i$ 个人会的题目的集合为 $S_i$ ，即当 $S_x\cap S_y\neq\varnothing\land S_x\not\subseteq S_y\land S_y\not\subseteq S_x$ 时，第 $x$ 人和第 $y$ 人会讨论）  
为了让模拟赛的效果更好，希望你可以找出一对会讨论的人或判断不存在。

## 说明/提示

**【样例 2】**

见附件中的 `discuss/discuss2.in` 与 `discuss/discuss2.ans`。

**【数据范围与提示】**

对于所有测试点：令一组数据中 $m=\sum k_i$，则 $1\le T\le 5$，$1\le \sum n\le {10}^6$，$1\le \sum m\le 2\times {10}^6$，$0\le k_i\le n$。

每个测试点的具体限制见下表：

![](https://cdn.luogu.com.cn/upload/image_hosting/zmkoxviw.png)

## 样例 #1

### 输入

```
2
5
4 1 2 3 5
3 1 2 3
2 1 2
1 1
1 4
4
3 1 2 3
3 2 3 4
0
4 1 2 3 4```

### 输出

```
NO
YES
1 2```

# 题解

## 作者：unputdownable (赞：36)

文中 $k_x$ 和 $S_x$ 的定义与题目相同。

文中所有 $x,y,z$ 都指人的编号，$i$ 都指题目的编号。

-------

首先考虑一个暴力：

> 对于每一个题目 $i$，找出会 $i$ 这道题的所有人，将其按会的题目数 $k_x$ 从小到大排序。
>
> 然后我们检查上述排序后相邻的两个人是否会讨论即可。

这个暴力的正确性证明：

> 因为每次被排序的人都至少会同一道题 $i$，所以只要考虑是否完全包含即可。
>
> 假设 $x,y,z$ 三个人会同一题 $i$ 并且 $k_x \leq k_y \leq k_z$，那么如果 $x,y$  和 $y,z$ 间都不会讨论，那么必然有 $S_x \subseteq S_y \subseteq S_z$，那么 $x,z$ 也必然不会讨论。

考虑优化上述暴力。

首先将所有人按 $k_x$ 从小到大排序，依次插入。

如果我们对于每一道题 $i$ 记录下会 $i$ 这道题的上一个人 $lst_i$，那么每次插入一个人 $x$ 的时候只需要检查 $\forall i \in S_x$，$lst_i$ 与 $x$ 会不会讨论。

但是这样由于每一个 $S_x$ 会被多次检查，复杂度仍然不对。

随后我们发现，在遍历 $S_x$ 的时候可以顺便求出 $S_x$ 与所有 $S_{lst_i}$ 的交集大小，于是我们可以直接通过交集大小是否为 $k_{lst_i}$ 来判断两个集合是否完全包含，即会不会讨论。

这样每次插入一个人的时间复杂度变为 $\Theta(|S_x|)$。

总体复杂度 $\Theta(n \log n +m)$，使用桶排可以去掉 $\log$。

**Code：**

```cpp
int n;
int k[1000006],a[1000006];
vector <int> p[1000006];
int cnt[1000006];
inline void clear(vector <int> X) {
    vector <int> e;
    e.swap(X);
}
inline bool cmp(int x,int y) {
    return k[x]<k[y];
}
int vis[1000006];
inline void work() {
    for(int i=1; i<=n; ++i) vis[i]=0;
    for(int i=1; i<=n; ++i) cnt[i]=0;
    n=read();
    for(int i=1; i<=n; ++i) {
        k[i]=read();
        clear(p[i]);
        p[i].resize(k[i]);
        for(int u=0; u<k[i]; ++u) p[i][u]=read();
        a[i]=i;
    }
    sort(a+1,a+n+1,cmp);
    for(int t=1; t<=n; ++t) {
        int i=a[t];
        if(k[i]==0) continue;
        for(int u=0; u<k[i]; ++u) {
            ++cnt[vis[p[i][u]]];
        }
        for(int u=0; u<k[i]; ++u) {
            int g=vis[p[i][u]];
            if(g!=0&&cnt[g]<k[g]&&cnt[g]<k[i]) {
                puts("YES");
                write(i); putchar(' '); write(g); puts("");
                return ;
            }
        }
        for(int u=0; u<k[i]; ++u) {
            --cnt[vis[p[i][u]]];
            vis[p[i][u]]=i;
        }
    }
    puts("NO");
}
```

---

## 作者：qwqUwU (赞：29)

## 讨论 题解报告

### 题意简述

$T$ 组询问，每次给出 $n$ 个集合 $S_1\sim S_n$ ，求是否**存在**两个集合 $S_i,S_j$ 满足 

- $S_i\cap S_j\ne \emptyset$

- $S_i \not\subseteq S_j$

- $S_j\not\subseteq S_i$

即两个集合有交集且不互相包含。

### 分析

很容易想到の一种做法，就是用一个**值域**数组 $vis$ 记录每个节点被哪个集合覆盖，然后每次访问集合后就**覆盖** $vis$ 数组。

这听起来就是一个口胡的算法，会有很多的 $bug$ 。

但事实上，这个算法是有正确性的，但要加一个约束：**集合要以元素数量从大到小访问。**

下面是更具体的算法过程与证明。

首先对于每个集合，排序后从大到小访问。

对于 $S_i$ ，对其进行 $3$ 次扫描。

1. 判断整个集合的元素是否都没被访问过。如果是，那这个集合与前面的集合的交集就必是 $\emptyset$ ，不满足条件，直接覆盖 $vis$ 即可。

1. 如果不是，那扫描第二遍判断当前集合的所有元素的 $vis$ 是否相同。**如果是**，说明它被 $S_{vis_i}$ 覆盖了。**如果不是**，则在 $S_i$ 的所有元素的 $vis$ 中的任意两个中**编号较大的**绝对没有覆盖 $S_i$（因为这两个集合要不就**不互相包含**，要不**编号较大的被较小的覆盖**，而 $S_i$ 都与这两个集合有交集，因此**不可能**同时被这两个集合覆盖）。直接输出答案。

1. 覆盖 $vis$。

用语言描述可能有些枯燥，看代码可能会更好理解。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
int T,n;
struct People{
	int k,id;
	vector<int>G;
}p[N];
int vis[N],tot;
inline void init(){
	tot=0;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)p[i].G.clear();
}
inline bool cmp(People a,People b){
	return a.k>b.k;
}
int main(){
//	freopen("discuss.in","r",stdin);
//	freopen("discuss.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		init();
		for(int i=1;i<=n;i++){
			scanf("%d",&p[i].k);
			for(int j=0;j<p[i].k;j++){
				int x;scanf("%d",&x);
				p[i].G.push_back(x);
			}
			if(p[i].k)sort(p[i].G.begin(),p[i].G.end());
			p[i].id=i;
		}
		sort(p+1,p+n+1,cmp);//排序
		bool exist_ans=0;
		for(int i=1;i<=n&&!exist_ans;i++){
			int flag1=0;
			for(int j=0;j<p[i].k;j++)
				if(vis[p[i].G[j]]){//存在先前被覆盖
					flag1=vis[p[i].G[j]];
					break;
				}
			if(flag1==0){
				for(int j=0;j<p[i].k;j++)vis[p[i].G[j]]=i;
				continue;
			}//覆盖
			for(int j=0;j<p[i].k&&!exist_ans;j++)
				if(vis[p[i].G[j]]!=flag1){//存在答案
					printf("YES\n%d %d\n",p[i].id,p[max(vis[p[i].G[j]],flag1)].id);
					exist_ans=1;
				}
			for(int j=0;j<p[i].k&&!exist_ans;j++)vis[p[i].G[j]]=i;//覆盖
		}
		if(!exist_ans)printf("NO\n");//没有答案
	}
//	fclose(stdin);
//	fclose(stdout); 
	return 0;
}
```


---

## 作者：FelFa_1414666 (赞：14)

自己现场想的屑解法，望指点。

[传送门](https://www.luogu.com.cn/problem/P8252)

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-p8252)

---

## Description

这种求集合交、并、包含的问题画一个 **Venn 图**对思考很有帮助，我现场用这种方法很快切了这道（有和我一样第一道没拿满分第二道拿满了的吗）。

用这种方式，我们来转换一下问题：

> 给若干个集合，输出两个有交集但没有包含关系的集合。

像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/lwnrlus4.png)

---

## Solution

首先方便起见，我们对所有集合**按元素个数 $k$ 降序排序**。这样的好处是：我们按顺序处理每个集合，**之前的集合只有可能包含当前集合，而不可能被当前集合包含**，一定程度地简化了问题。

接着，我们每次处理一个集合。我们可以数一下之前处理过的集合中，与它有交的集合个数 $cnt$。分为 3 种情况：

1. $cnt=0$

   没有集合与其有交，那就先放这不管。

2. $cnt=1$

   有且仅有一个集合与其有交，设它为 $A$，当前集合为 B。那么检查 $B\subseteq A$ 是否成立。

   $B\nsubseteq A$：这两个集合有交且没有包含关系，直接输出答案。

   $B\subseteq A$：令 $A\gets\complement_AB$，相当于把 $A$ 中 $B$ 的部分挖去。这样做能**保证当前存在的所有集合两两无交**，且不影响运算结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/vqp7dcqb.png)

3. $cnt=2$

   有多个集合与其有交。设当前集合为 $B$，我们可以证明，至少存在一个集合 $D$ 满足 $D\nsubseteq B$ 且 $D\cap B\neq \varnothing$。

   我们选取**与 $B$ 有交的集合中元素个数 $k$ 最小的**，一定合法，直接输出 $B$ 和此集合作为答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/fulb9vuc.png)

这样我们就得到了整个的解法过程。接下来的问题就是如何去维护这个 Venn 图。

因为在操作的过程中，我们保证了当前存在的**所有集合两两之间无交**，所以我们只需要定义一个 $t_i$ 表示**元素 $i$ 当前属于哪个集合**，如果元素 $i$ 当前未被覆盖，则 $t_i=-1$。

---

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
inline ll read()//快读快写
{
	ll x=0,f=0;
	char ch=getchar();
	while(!isdigit(ch))
		f|=ch=='-',ch=getchar();
	while(isdigit(ch))
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
template<typename T>inline void write(T x)
{
     if(x<0)x=-x,putchar('-');
     if(x>9)write(x/10);
     putchar(x%10^48);
}
int n,t[1000005];
struct Person//定义集合结构体
{
	int sz,id;
	vector<int> v;
}a[1000005];
bool cmp(Person &A,Person &B)
{
	return A.sz>B.sz;
}
void run()
{
	n=read();
	for(int i=0;i<n;i++)
		t[i]=-1;//初始化
	for(int i=0;i<n;i++)
	{
		a[i].v.clear();
		a[i].sz=read();
		a[i].id=i+1;
		a[i].v.resize(a[i].sz);
		for(int j=0;j<a[i].sz;j++)
			a[i].v[j]=read()-1;
	}
	sort(a,a+n,cmp);//将所有集合按元素个数降序排序
	unordered_set<int> se;
	for(int i=0;i<n;i++)
	{
		se.clear();
		for(auto x:a[i].v)//找与当前集合有交集的所有集合
		{
			if (t[x]!=-1)
				se.insert(t[x]);
		}
		if ((int)se.size()>1)//cnt>1
		{
			int cur=*se.begin();
			for(auto it=next(se.begin());it!=se.end();it++)
				if (a[*it].sz<a[cur].sz)
					cur=*it;//找到有交的集合中，元素个数最小的，直接输出答案
			puts("YES");
			write(a[i].id),putchar(' '),write(a[cur].id),putchar('\n');
			return;
		}
		else if ((int)se.size()==1)//cnt=1
		{
			int b=*se.begin();
			for(auto x:a[i].v)//检查是否有包含关系
				if (t[x]!=b)
				{
					puts("YES");
					write(a[i].id),putchar(' '),write(a[b].id),putchar('\n');
					return;
				}
			for(auto x:a[i].v)//有包含关系，挖去当前集合部分
				t[x]=i;
		}
		else//cnt=0
		{
			for(auto x:a[i].v)
				t[x]=i;
		}
	}
	puts("NO");
}
int main()
{
	//freopen("discuss.in","r",stdin);
	//freopen("discuss.out","w",stdout);
	int TT=read();//多测
	while(TT--)
		run();
	return 0;
}
```

时间复杂度：$O(n\log n+\sum k)$

空间复杂度：$O(n+\sum k+m)$

---

挺玄乎的思路，不知道大家有没有更好的做法...

希望题解对你有帮助！

---

## 作者：staly (赞：6)

题目的意思可以简化为：给定 $n$ 个集合，求集合中是否存在交叉关系。

我们先假设如果不存在交叉关系，集合 $A$ 小于集合 $B$，集合 $A$ 要么是 $B$ 的子集，要么与 $A$ 没有交集。如果存在交叉关系又有一种新的情况，即集合 $A$ 与集合 $B$ 成交叉关系。

因此我们得出集合中存在交叉关系的判定：如果对于所有的集合，满足所有比它小的集合要么是它的子集，要么与它没有交集，则它们之间不存在交叉关系。即，比它小的集合与该集合不会增大该集合所在的连通块大小。

而这一问题很容易用带权的并查集解决：用 $1\sim n$ 表示集合编号，用 $n\sim 2n$ 表示集合元素。按集合大小从小到大枚举，并合并元素和对应的集合编号。如果存在一个集合，使得并查集合并出的连通块的大小大于该集合的元素数目，也就是说存在比它小的集合对它的大小产生了贡献，有交叉关系存在，我们再枚举判断贡献的点和对应的集合编号，输出答案。

对集合进行排序时间复杂度为 $O(n\log{n})$，并查集的添加和查询时间复杂度为 $O((n+m)\operatorname{\alpha}{(n)})$，而统计答案时，由于需要用并查集判断，时间复杂度仍然为 $O((n+m)\operatorname{\alpha}{(n)})$。综合来看，总共的时间复杂度为 $O(n\log{n})$。

代码如下：

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 2e6 + 7, maxm = 4e6 + 7;
int head[maxn], nxt[maxm], to[maxm], ecnt;
void add(int u, int v)
{
    nxt[++ecnt] = head[u];
    head[u] = ecnt;
    to[ecnt] = v;
}
int t, n;
int k[maxn];
int fa[maxn], siz[maxn];
int get_fa(int x)
{
    if (x == fa[x])
        return x;
    return fa[x] = get_fa(fa[x]);
}
void merge(int a, int b)
{
    int f_a = get_fa(a), f_b = get_fa(b);
    if (f_a != f_b)
    {
        siz[f_a] += siz[f_b];
        fa[f_b] = f_a;
    }
}
int ord[maxn];
int mark[maxn];
bool comp(int a, int b)
{
    return k[a] < k[b];
}
int main()
{
    freopen("discuss.in", "r", stdin);
    freopen("discuss.out", "w", stdout);
    int _t;
    scanf("%d", &t);
    while (t--)
    {
        for (int i = 1; i <= n; i++)
            head[i] = 0;
        scanf("%d", &n);
        bool flag = false;
        int ansa, ansb;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &k[i]);
            for (int j = 1; j <= k[i]; j++)
            {
                scanf("%d", &_t);
                add(i, n + _t);
            }
        }
        for (int i = 1; i <= n * 2 + 2; i++)
        {
            fa[i] = i;
            siz[i] = 1;
        }
        for (int i = 1; i <= n; i++)
        {
            ord[i] = i;
            siz[i] = 0;
        }
        sort(ord + 1, ord + n + 1, comp);
        for (int i = 1; i <= n; i++)
        {
            int c = ord[i];
            for (int j = head[c]; j; j = nxt[j])
                merge(c, to[j]);
            if (siz[get_fa(c)] > k[c])
            {
                flag = true;
                ansa = c;
                for (int j = head[c]; j; j = nxt[j])
                    mark[to[j]] = (t + 1) << 1;
                for (int j = n + 1; j <= n * 2; j++)
                    if (get_fa(j) == get_fa(c) && mark[j] != ((t + 1) << 1))
                        mark[j] = ((t + 1) << 1) | 1;
                bool flaga = 0, flagb = 0;
                for (int j = 1; j <= n; j++)
                {
                    flaga = 0, flagb = 0;
                    if (get_fa(c) == get_fa(j))
                        for (int l = head[j]; l; l = nxt[l])
                            if (mark[to[l]] == ((t + 1) << 1))
                                flaga = 1;
                            else if (mark[to[l]] == (((t + 1) << 1) | 1))
                                flagb = 1;
                    if (flaga && flagb)
                    {
                        ansb = j;
                        break;
                    }
                }
                break;
            }
        }
        if (flag == false)
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
            printf("%d %d\n", ansa, ansb);
        }
    }
}
```

---

## 作者：约瑟夫用脑玩 (赞：5)

数据没出，于是口胡线性做法没问题吧。（其实是从游记里面搬的）

先假装全都不能讨论发现是个包含树的关系，于是有了一个自然的想法：

判断给定关系是否形成包含树，并在判断失败的时候输出这两个点。

对每道题考虑，包含它的按长度排序，相同长度必须相同，否则形不成包含树。

然后长度相邻的两个点必定是父子关系，祖先关系都不行，只能有一个父亲的连边，先把边连上再去重即可。

然后暴力判父子是否包含，暴力遍历儿子长度相关的复杂度，于是 $\sum$ 起来还是 $O(m)$ 的。

但这样实现出来有排序，去重和 `map/unordered_map` 或二分来判断两个点是否包含，是 $O(m\log)$ 的，考虑更优秀的实现：

首先排序换成提前桶排，然后直接对相邻长度连边，看是否有父亲完全包含儿子。

去重也不用，只用保证每个点只走一次即可，同上只能有一个父亲，可以通过记录父亲是谁来判定。

直接从根往下做，对于每个点暴力遍历它有的元素判断全都是父亲的标记，表示被包含。

同时打标记上自己的标记，用于处理它自己的儿子，显然线性。

对于长度相同的在桶排时会自动按编号排序（意思是桶排是 stable 的）于是一定形成一条链，当成长度不同的正常判断即可。

---

## 作者：滑稽生物 (赞：3)

 显然，“不存在可以讨论的人” 相当于 $S_i$ 可以形成树结构（儿子是父亲的子集）,一个节点的各个儿子代表的集合不交。
 
 定义颜色数组 $a_{1..n}$ ，初始时全为0。按 $k_i$ 从大到小考虑每个人，如果其 $S$ 中题目的颜色不止一种，则输出```YES```，并找到可以讨论的人（暴力就行）。否则将 $S$ 中的题目设为一种新的颜色。最后没输出```YES```就输出```NO```。
 
$k_i$ 从大到小是为了保证前面的不是后面的子集。
 
我的代码（希望别挂）：
 ```cpp
 #include<bits/stdc++.h>
#define N 1000005
using namespace std;
int T,n,a[N];
bool b[N];
vector<int> s[N];int k[N],id[N];
bool cmp(const int&a,const int&b){
	return k[a]>k[b];
}
int main(){
	freopen("discuss.in","r",stdin);
	freopen("discuss.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)a[i]=0,s[i].clear(),id[i]=i;
		for(int i=1;i<=n;++i){
			scanf("%d",k+i);
			for(int j=0,t;j<k[i];++j){
				scanf("%d",&t);
				s[i].push_back(t);
			}
		}
		sort(id+1,id+1+n,cmp);
		int c=0;
		for(int i=1;i<=n;++i){
			if(k[id[i]]==0)break;
			bool flag=true;
			int x=a[s[id[i]][0]];
			for(int j=1;j<k[id[i]];++j){
				if(a[s[id[i]][j]]!=x){flag=false;break;}
			}
			if(flag){
				++c;
				for(int j=0;j<k[id[i]];++j){
					a[s[id[i]][j]]=c;
				}
			}else{
				puts("YES");
				printf("%d ",id[i]);
				for(int j=0;j<k[id[i]];++j){
					b[s[id[i]][j]]=1;
				}
				int Cnt=k[id[i]];
				for(int i=1;i<=n;++i){
					if(k[i]==0)continue;
					int cnt=b[s[i][0]];
					bool x=b[s[i][0]],fl=true;
					for(int j=1;j<k[i];++j){
						if(b[s[i][j]])++cnt;
						if(b[s[i][j]]!=x){fl=false;}
					}
					if((!fl)&&cnt!=Cnt){printf("%d\n",i);break;}
				}
				for(int j=0;j<k[id[i]];++j){
					b[s[id[i]][j]]=0;
				}
				goto ed;
			}
		}
		puts("NO");
		ed:;
	}
	return 0;
}
 ```

---

## 作者：huayucaiji (赞：2)

## 解题思路

我们考虑什么时候不存在合法集合对。

两个集合不合法当且仅当他们有包含关系或无交集。我们考虑对集合排序，这样若 $B⊆C,C⊆A$，那么有 $B⊆A$。这显然。所以排序可以简化计算。

我们从小到大枚举一遍，把现在所有扫过了的，包含元素 $i$ 的最大集合标记到 $i$ 上。每次我们检查一个新的集合，我们只需要验证是否对于 $i\in S$，$i$ 标记的集合的所有元素都在 $S$ 中。这扫一遍即可验证。若存在一个标记不满足条件，那么这个集合和 $S$ 就满足题目要求，输出即可。

我们的时间复杂度来到了 $O(n\log n)$，瓶颈是排序。这个复杂度已经可以通过了。

但是我们可以用桶排序优化这个进程，复杂度来到 $O(n+m)$ 。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
char read_char() {
	char ch=getchar();
	while(!isalpha(ch)) {
		ch=getchar();
	}
	return ch;
}

const int MAXN=1e6+10; 

int n;
int inc[MAXN],sz[MAXN],bel[MAXN];
vector<int> s[MAXN],buc[MAXN]; 

void work() {
	for(int i=1;i<=n;i++) {
		sz[i]=read();
		for(int j=1;j<=sz[i];j++) {
			s[i].push_back(read());
		}
		buc[sz[i]].push_back(i);
	}
	
	for(int i=1;i<=n;i++) {
		int siz=buc[i].size();
		for(int j=0;j<siz;j++) {
			int u=buc[i][j];
			for(int k=0;k<sz[u];k++) {
				int x=s[u][k];
				inc[bel[x]]++;
			}
			for(int k=0;k<sz[u];k++) {
				int x=s[u][k];
				if(bel[x]&&inc[bel[x]]!=sz[bel[x]]) {
					puts("YES");
					printf("%d %d\n",u,bel[x]);
					return ;
				}
			}
			for(int k=0;k<sz[u];k++) {
				int x=s[u][k];
				inc[bel[x]]--;
				bel[x]=u;
			}
		}
	}
	puts("NO");
}
void clean() {
	fill(sz+1,sz+n+1,0);
	fill(inc+1,inc+n+1,0);
	fill(bel+1,bel+n+1,0);
	for(int i=1;i<=n;i++) {
		buc[i].clear();
		s[i].clear();
	}
}

int main() {
	int t=read();
	while(t--) {
		cin>>n;
		work();
		clean();
	}
	
	return 0;
}

```



---

## 作者：simple_dream (赞：2)

看到这道题有一个显然的想法，就是先将集合按大小从小到大排序。然后遍历每个集合，每个集合都塞进集合中每个元素所对应的桶。显然一个桶中的所有集合都包含着这个桶所对应的元素，之后只需要判断一个桶中是否有互相不包含的两个集合即可。

记一个桶中的集合分别是 $a_1$,$a_2$,$a_3$ $...$ 如果集合 $a_i$ 和集合 $a_j$ 是答案，并且 $i < j$ 且 $a_i \subseteqq a_{i+1}$ 那么 $a_{i+1}$ 和 $a_j$ 也是答案。这里你会发现一个结论，你只需要判断桶中相邻长度的两个集合是否可行即可。

但是这里会出现一个问题。由于一个集合被塞进了很多个桶里面，所以一个集合最多可能会判断 $k$ 次。怎么解决这个问题呢？你会发现，有很多个集合都被塞进了多个桶里，这就导致在不同桶中，有一个集合可能会与另一个集合多次进行判断。这时，可以开一个哈希表判断同样的两个集合是否被判断过，如果是，跳过即可。

这个的复杂度是 $O(t(n\log n+m))$

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

const int Mod1 = 1e7 + 7;
const int Mod2 = 1e7 + 9;

int t;

int n;

bool mp1[Mod1],mp2[Mod2];

void Hash(long long val)
{
	mp1[val % Mod1] = 1;
	mp2[val % Mod2] = 1;
}

bool in_hash(long long val)
{
	return mp1[val % Mod1] && mp2[val % Mod2];
}

struct node
{
	int k,id;
	vector<int> ve;
	void clear()
	{
		k = 0;
		ve.clear();
	}
}a[N];

vector<int> ve[N];

bool cmp(const node &x,const node &y)
{
	return x.k < y.k;
}

bool check(const node &x,const node &y)
{
	int i = 0,j = 0;
	while(i < x.k)
	{
		if(x.ve[i] == y.ve[j])
		{
			i++;
		}
		else
		{
			j++;
			if(j >= y.k)
			{
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		memset(mp1,0,sizeof(mp1));
		memset(mp2,0,sizeof(mp2));
		for(int i = 1;i <= n;i++)
		{
			a[i].clear();
			ve[i].clear();
			scanf("%d",&a[i].k);
			a[i].id = i;
			bool flag = 0;
			for(int j = 1;j <= a[i].k;j++)
			{
				int val;
				scanf("%d",&val);
				a[i].ve.push_back(val);
			}
			for(int j = 1;j < a[i].k;j++)
			{
				if(a[i].ve[j] < a[i].ve[j - 1])
				{
					flag = 0;
					break;
				}
			}
			if(!flag) sort(a[i].ve.begin(),a[i].ve.end());
		}
		sort(a + 1,a + n + 1,cmp);
		for(int i = 1;i <= n;i++)
		{
			for(int j = 0;j < a[i].k;j++)
			{
				ve[a[i].ve[j]].push_back(i);
			}
		}
		int ans1 = 0,ans2 = 0;
		for(int i = 1;i <= n;i++)
		{
			int len = ve[i].size();
			len--;
			for(int j = 0;j < len;j++)
			{
				long long x = 1ll * ve[i][j] * N + ve[i][j + 1];
				if(in_hash(x))
				{
					continue;
				}
				Hash(x);
				if(check(a[ve[i][j]],a[ve[i][j + 1]]))
				{
					ans1 = ve[i][j];
					ans2 = ve[i][j + 1];
					break;
				}
			}
			if(ans1)
			{
				break;
			}
		}
		if(ans1)
		{
			printf("YES\n%d %d\n",a[ans1].id,a[ans2].id);
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
```


---

## 作者：Harry27182 (赞：1)

比赛没打，赛后看题，第一反应是按照 k 从大到小排序，然后只要排在后面的有排在前面的没有的题，那么排在前面的一定也有排在后面的没有的题（很显然），题目有没有出现过可以用一个布尔数组实现，然后剩下的问题就是判断有没有公共的题目，然后......就没有然后了。

然后我看了巨佬同学@Iam1789 的[题解](https://www.luogu.com.cn/blog/Iam1789/solution-p8252)，又经过自己的一番思考，明白了我的问题出在哪里。

问题就在，如果我记录的只是布尔数组的 01，那么就无法记录每一道题是最先（或最后）在哪一个人身上出现过，自然无法解决下面的问题。对此，我的解决方法就是，把布尔数组改成一个记录颜色的 ```int``` 类型数组 ```col[]``` ，表示每一道题最后是哪一个人会做，然后不难发现一个结论。如果一个人 $A$ 会做的题里面，有被标记为两种以上颜色的题（假设分别是 $B$ 会做的和 $C$ 会做的），那么 $max(B,C)$ 和 $A$ 一定是可以讨论的，证明如下：

假设 $B<C$，$A$ 会的题里面有标记为 $C$ 的，说明一定有他们都会的题，然后还有标记为 $B$ 的，这些题既然被标记为 $B$ ，说明在 $B$ 后面的 $C$ 是一定不会这些题的，否则这些题会被标记为 $C$ ，所以有 $A$ 会而 $C$ 不会的题，所以一定也有 $C$ 会而 $A$ 不会的题（$A$ 会的题比 $C$ 少），证毕。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int num,pla;
	vector<int>k;
}a[1000005];
int t,n,x,col[1000005];
bool vis[1000005];
bool cmp(node a,node b)
{
	return a.num>b.num;
}
int read()
{ 
	int f=1,x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main()
{
	t=read();
	while(t--)
    {
    	n=read();
    	for(int i=1;i<=n;i++)
    	{
    		a[i].num=read();
    		a[i].k.clear();
    		for(int j=1;j<=a[i].num;j++)
    		{
    			x=read();
    			a[i].k.push_back(x);
    		}
    		a[i].pla=i;
    		col[i]=0;
    	}
    	sort(a+1,a+n+1,cmp);
    	int flag=0;
    	for(int i=1;i<=n;i++)
    	{
    		int sum=0,maxn=0;
    		for(int j=0;j<a[i].num;j++)
    		{
    			if(!vis[col[a[i].k[j]]])
    			{
    				sum++;
    				vis[col[a[i].k[j]]]=1;
    				maxn=max(maxn,col[a[i].k[j]]);
    			}
    		}
    		for(int j=0;j<a[i].num;j++)
    		{
    			vis[col[a[i].k[j]]]=0;
    			col[a[i].k[j]]=i;
    		}
    		if(sum>=2)
    		{
    			flag=1;
    			printf("YES\n");
    			printf("%d %d\n",a[maxn].pla,a[i].pla);
    			break;
    		}
    	}
    	if(!flag)printf("NO\n");
    }
	return 0;
}
```

---

## 作者：Doubeecat (赞：1)

> 有 $n$ 个人正在打模拟赛，模拟赛有 $n$ 道题目。  有两人都会的题目并且没有人会的题目包含另一个人时，两者之间才会讨论。  
>
> （定义第 $i$ 个人会的题目的集合为 $S_i$ ，即当 $S_x\cap S_y\neq\varnothing\land S_x\not\subseteq S_y\land S_y\not\subseteq S_x$ 时，第 $x$ 人和第 $y$ 人会讨论）  
>
> 为了让模拟赛的效果更好，希望你可以找出一对会讨论的人或判断不存在。
>
> $m=\sum k_i$，$1\le n\le {10}^6$，$1\le m\le 2\times {10}^6$

## 思路

首先按照集合的大小从大到小排序，依次处理每个集合。

我们可以维护一个数组 $f_i$ 代表当前题目 $i$ 最后被哪个集合包含了。对于当前集合 $S$，我们考虑元素 $x \in S$ ，如果存在不同的 $f_x$ 并且 $S$ 与这个集合不是包含关系，那么我们的问题就解决了。如果不存在的话，考虑包含那么原来储存的那个集合就没有用了，因为后面若交了肯定还是包含，就把原来那个删掉，把当前集合塞进去。

现在就来解决如何查询 $f_x$ 的问题，这部分有两种方法。

第一种方法：

比如 $S_1= \{1, 2, 4\}$ 和 $S_2 = \{3\}$ 就表示成 $f = [1, 1, 2, 1]$。然后判断的时候就可以直接判断了，比如插入了 $\{1, 2, 5\}$，然后发现 $f_1 = 1$，则把 $S_1$ 拿出来，把 $S_1$ 加入桶里，然后统计 $\{1, 2, 5\}$ 中有几个元素在桶中，这里有两个，$2 < 3$ 说明没有完全包含。

每个集合只会被塞入一次，也只会被检查和删除一次，所以复杂度是 $\mathcal{O}(n)$的。

第二种方法：

我们依然采用最上边上面维护 $f_i$ 的方法，但是我们考虑我们插入一个集合的时候，如果这个集合有全新的元素我们是不是就解决了这个问题？那么如何判断？记当前集合 $S$ 集合内为元素 $x$ ：

- 若存在 $f_x = 0$ 则说明这个集合相较之前的所有集合有新元素。
- 若至少存在两个不同的 $f_x$ ，那么相对于题量较少的 $f_x$ ， $S$ 肯定是有新题的。因为对于题量少的那个 $f_x$ ，其必然不会另一道交叉的题。

所以我们只要记录和谁有共同题目，然后最终的答案就是题量较少的那个集合以及当前集合。时间复杂度同第一种方法。

## 代码

这里给出第二种方法的参考实现：

```cpp
const int N = 1e6 + 10;

int n,k[N],c[N],f[N];
vector <int> p[N];

bool cmp(int x,int y) {
    return k[x] > k[y];
}

void solve() {
    read(n);
    memset(f,0,sizeof f);
    for (int i = 1;i <= n;++i) {
        read(k[i]);c[i] = i;
        p[i].clear();
        for (int j = 1;j <= k[i];++j) {
            int x;read(x);
            p[i].push_back(x);
        }
    }
    sort(c+1,c+1+n,cmp);
    bool flag = 1;
    int ans1,ans2;
    for (int i = 1;i <= n;++i) {
        int x = c[i];
        int f1=0,f2=0;
        if (!flag) break;
        for (auto y : p[x]) {
            int las = f[y];f[y] = x;
            if (!las) las = x;
            if (!f1) f1 = las;
            else if (f1 != las) f2 = las;
            if (f1&&f2) {
                if (f1 != x && f2 != x) {
                    //printf("%d %d %d\n",f1,f2,x);
                    if (k[f1] > k[f2]) f1 = x;
                    else f2 = x;
                }
                ans1 = f1,ans2 = f2;
                flag = 0;
                break;
            }
        }
    }
    if (flag) puts("NO");
    else {
        puts("YES");
        printf("%d %d\n",ans1,ans2);
    }
}

signed main() {
    int T;read(T);
    while (T--) solve();
	return 0;
}

```



---

## 作者：Iam1789 (赞：1)

先说做法。定义每个题有一个颜色，初始颜色为 $0$。把每个人按照 $k$ 从大到小排序后扫一遍。对于第 $i$ 个人，先判断他会的题中是否有两种不相同的颜色 $j,k$，则说明 $i$ 与 $\text{max}(j,k)$ 满足题目要求。判断完之后，将他会的题染上颜色 $i$。

接着考虑这个做法为什么是对的。首先证明该做法的充分性。设 $j<k$，$i$ 与 $j$ 相同的部分则为 $i$ 与 $k$ 不相交的部分，$i$ 与 $k$ 相同的部分为相交的部分。由于 $k<i$，所以 $i$ 不会包含 $k$。因此满足题目要求。接着证明必要性。根据题目要求，不难发现对于满足条件的 $i,k$，他们一定可以产生相交。

时间复杂度 $\Theta(n\log n +m)$。

---

## 作者：Xu_brezza (赞：1)

## 题意：

有 $n$ 个人，有 $n$ 道题，每个人有一个自己会的题的集合，求是否存在任意两个人他们的集合相交且互不包含。

## 分析：

我们从无解的情况开始考虑，那么任意两个人之间要么没有交集，要么包含，所以我们可以设计这样的算法：贪心地想，按集合从大到小找，建一个树形结构（感性理解吧，想象一下），结点是题的编号。首先把最大的那一坨染成他的编号，然后再依次插入每个人，在遍历的过程中我们记录出现的颜色，记录之后顺便把他染成当前的编号，如果在遍历过程中出现了两种不同的颜色，证明我们找到了合法解，输出即可。

```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<vector>
#include<string>
using namespace std;
const int N = 1e6 + 5;
int id[N],k[N],col[N],n,t;
vector<int>v[N];
inline bool cmp(int x,int y){
	return k[x] > k[y];	
}
int main(){
	//freopen("discuss2.in","r",stdin); 
	scanf("%d",&t);
	while(t--){
		memset(k,0,sizeof(k));
		memset(col,0,sizeof(col));
		memset(id,0,sizeof(id));
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",k+i);
			id[i] = i;
			v[i].clear();	
			for(int x,j=1;j<=k[i];++j){
				scanf("%d",&x);
				v[i].push_back(x);
			}
		}
		sort(id+1,id+1+n,cmp);//按集合大小降序 
		for(int x : v[id[1]])col[x] = id[1];//最大的一坨染色 
		int cnt = 1;
		k[0] = 1e9;
		for(int i=2;i<=n;++i){
			cnt++;
			int flag = 0,color = 0;
			for(int x : v[id[i]]){
				if(color != col[x] && flag){//第二种颜色 
					printf("YES\n%d %d\n",id[i],k[col[x]] < k[color] ? col[x] : color);//避免颜色为0 
					goto QWQ;	
				}
				if(flag == 0)flag = 1;//第一种颜色 
				color = col[x];//记录颜色 
				col[x] = id[i];//染色 
			}
		}
		puts("NO");
		QWQ:;
	}
}

```


---

## 作者：Rushroom (赞：1)

小清新图论。

### 做法

我们考虑枚举 $x,y$ 都会的题目编号为 $i$，则可以列举出所有会第 $i$ 道题目的人会的题目的集合。通过题意可知，这些集合之间任何两个都是包含关系。

又因为一定是大的集合包含小的集合，所以我们可以将它们按照大小排序，在相邻两个集合 $x,y(\left| x \right| \le \left| y \right|)$ 之间，连一条从 $x$ 到 $y$ 的边，表示 $x \subseteq y$。

如果所有边都符合，那么就不会有人讨论。我们接下来就要判断这个。

判断一条边是 $O(k)$ 的，而一共有 $O(m)$ 条边，所以显然会 TLE。

我们再想一想，发现有很多的 **返祖边**（即有 $x \rightarrow y,y \rightarrow z$，则 $x \rightarrow z$ 就是返祖边）。这些边是可以省略的（因为如果 $x \subseteq y,y \subseteq z$，则一定有 $x \subseteq z$）。

这样一来，图就变成了一棵树。我们只需要用 `std::set` 维护每个节点所有儿子节点代表集合的并，就可以在 $O(m)$ 的时间内判断所有边了。

最后说一下，如果答案是 `YES`，如何找出一对 $x,y$。假设我们在节点 $i$ 找到了矛盾：儿子集合的并包含 $p$，但 集合 $i$ 不包含 $j$，只需要对每个儿子依次判断是否含有 $j$ 即可。

### Code

```cpp
/*
 * @Description: How is the foundation so poor ah, I think FGgirl should go back to popularize group to learn again
 * @Author: FGgirl
 * @Date: 2022-03-26 08:35:21
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T_, case_;
int n, m[1000006], siz[1000006], a, b;
int fa[1000006], id[1000006];
bool cmp(int x, int y) {
    return m[x] < m[y];
}
vector<vector<int>>x, y, v;
vector<set<int>>s;
void solve() {
    cin >> n;
    x.resize(n + 2);
    v.resize(n + 2);
    rep(i, n) {
        cin >> m[i];
        x[i].clear();
        rep(j, m[i]) {
            cin >> a;
            a--;
            x[i].pb(a);
        }
        sort(x[i].begin(), x[i].end());
    }
    rep(i, n)fa[i] = -1, id[i] = i;
    sort(id, id + n, cmp);
    y.resize(n + 2);
    rep(i, n)y[i] = x[id[i]], siz[i] = m[id[i]];
    rep(i, n)v[i].clear();
    rep(i, n) {
        rep(j, siz[i])v[y[i][j]].pb(i);
    }
    rep(i, n) {
        if (v[i].size()) {
            if (v[i].size() >= 2)
                rep(j, v[i].size() - 1) {
                a = v[i][j], b = v[i][j + 1];
                if (fa[a] == -1)fa[a] = b;
                else if (siz[fa[a]] > siz[b])fa[a] = b;
            }
        }
    }
    s.resize(n + 2);
    rep(i, n)s[i].clear();
    rep(i, n) {
        if (fa[i] == -1)continue;
        rep(j, siz[i]) {
            s[fa[i]].insert(y[i][j]);
        }
    }
    rep(i, n) {
        set<int>::iterator it = s[i].begin();
        if (it == s[i].end())continue;
        rep(j, siz[i]) {
            if (y[i][j] == (*it))it++;
            if (it == s[i].end())break;
        }
        if (it != s[i].end()) {
            a = (*it);
            rep(j, n) {
                if (fa[j] == i) {
                    rep(k, siz[j]) {
                        if (y[j][k] == a) {
                            cout << "YES\n";
                            cout << id[i] + 1 << ' ' << id[j] + 1 << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << "NO\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    T_ = 1;
    cin >> T_;
    for (case_ = 1;case_ <= T_;case_++)solve();
    return 0;
}

```


---

## 作者：CodingJellyfish (赞：1)

这是一篇时空复杂度 $\Theta(\Sigma m+\Sigma n)$ 的题解。

根据题意得，任意两个集合只能一者包含另一者，或者不相交。而包含关系是一种偏序关系，A 包含 B，B 包含 C，那么 A 包含 C **(1)** 。而 A 的集合大小不小于 B 是 A 包含 B 的必要条件。

所以可以考虑将所有集合按 ki 从小到大排序，前面的一定不包含后面的 **(2)**。

然后我们考虑将集合 k 和前面的集合们合并。不妨设前面的集合们是合法的。那么它们一定可以分成 tot 组，每一组中最大的集合（后文称“大集合”）都包含了组内的其它集合，而这些大集合都互不相交。

我们先把每一个大集合放到桶里，用不同的数字标记。然后考虑新加入的集合（后文称“新集合”），这个集合一定比所有大集合大，所以只能是新集合包含大集合 **(goto (2))**。

然后由于集合间互不相交，所以对于每一种大集合都有两种可能：完全包含或者互不相交。可以发现：假如

```
siz(新集合) - siz(所有与新集合相交的大集合的并) < siz(新集合 - 所有与新集合相交的大集合的并)
```

那么这个集合会和其中一个大集合形成非法关系，否则直接加入，变成新的大集合，对于其它不是大集合的集合也一定是合法的 **(goto (1))**。

上述等式可以用桶以 $\Theta(ki)$ 的时间复杂度维护。

而找到与新集合形成非法关系的大集合可以暴力扫桶， $\Theta(n)$ 的时间复杂度。

排序可以用计数排序或基数排序，$\Theta(n)$ 的时间复杂度。

综上，时间复杂度为 $\Theta(\Sigma m+\Sigma n)$ 的。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RN 3000005

typedef int I;
typedef char C;
typedef unsigned U;

// IO

#include <ctype.h>

#define IO 4096

static inline char getC(void)
{
	static C ibuf[IO], *i = ibuf + IO;
	if (i == ibuf + IO) 
	{
		memset(ibuf, 0, sizeof(ibuf));
		fread(ibuf, IO, sizeof(C), stdin);
		i = ibuf;
	}
	return *i++;
}

static inline I getI(void)
{
	I num = 0, fac = 1;
	C ch = getC();
	while (!isdigit(ch))
	{
		fac = ch == '-' ? -1 : 1;
		ch = getC();
	}
	while (isdigit(ch))
	{
		num = num * 10 + ch - '0';
		ch = getC();
	}
	return num * fac;
}

// Utility

typedef struct
{
	I x, y;
}
PII;

// Sort

U _bu[256];

#define SORTBYTE(TYP, PAR, FR, TO, LEN, BIT)            \
{                                                       \
	memset(_bu, 0, sizeof(_bu));                        \
	for (TYP *it = (FR) + (LEN); it != (FR); it--)      \
		++_bu[(it[-1]PAR >> BIT) & 255];                \
	for (U *it = _bu; it != _bu + 255; it++)            \
		it[1] += it[0];                                 \
	for (TYP *it = (FR) + (LEN); it != (FR); it--)      \
		(TO)[--_bu[(it[-1]PAR >> BIT) & 255]] = it[-1]; \
}

// Main

PII all[RN], buf[RN];
I *p[RN];
I can[RN], buc[RN], buc2[RN];
I colpre[RN];
I stk[RN], top;

int main(void)
{
	freopen("discuss.in", "r", stdin);
	freopen("discuss.out", "w", stdout);
	I t = getI();
	while (t--)
	{
		I n = getI();
		I *st = can + 1;
		
		memset(buc, 0, sizeof(I) * (n + 2));
		memset(buc2, 0, sizeof(I) * (n + 2));
		memset(colpre, 0, sizeof(I) * (n + 2));
		
		for (I i = 1; i <= n; i++)
		{
			all[i].x = getI();
			all[i].y = i;
			
			p[i] = st, st += all[i].x;
			
			for (I j = 1; j <= all[i].x; j++)
			{
				p[i][j] = getI();
			}
		}
		SORTBYTE(PII, .x, all + 1, buf + 1, n, 0);
		SORTBYTE(PII, .x, buf + 1, all + 1, n, 8);
		SORTBYTE(PII, .x, all + 1, buf + 1, n, 16);
		SORTBYTE(PII, .x, buf + 1, all + 1, n, 24); // 排序
		
		I color = 0;
		top = 0;
		
		for (I i = 1; i <= n; i++)
		{
			I len = all[i].x;
			I delta = len;
			I *pi = p[all[i].y];
			I col = 0;
			
			for (I j = 1; j <= len; j++)
			{
				if (buc[pi[j]])
				{
					if (!buc2[buc[pi[j]]])
					{
						stk[++top] = buc[pi[j]];
						col = buc[pi[j]];
						delta -= all[colpre[buc[pi[j]]]].x;
						buc2[buc[pi[j]]] = 1; // 找到所有相交的颜色
					}
					buc2[buc[pi[j]]]++;
				}
			}
			if (!col) col = ++color; // 假如没有与任何集合相交就染新颜色
			
			for (I j = 1; j <= len; j++)
			{
				if (!buc[pi[j]])
				{
					delta--; // 判断不等式是否成立
				}
			}
			if (delta < 0) // 不成立
			{
				puts("YES");
				for (I j = 1; j <= n; j++)
				{
					if (buc2[buc[j]]) // 暴力扫桶
					{
						buc2[buc[j]]--;
						if (!buc2[buc[j]])
						{
							printf("%d %d\n", all[i].y,
							                  all[colpre[buc[j]]].y);
							goto END;
						}
					}
				}
			}
			for (I j = 1; j <= len; j++)
			{
				buc[pi[j]] = col; // 覆盖旧集合
			}
			colpre[col] = i;
			
			while (top) buc2[stk[top--]] = 0; // 清空桶
		}
		puts("NO");
	END:;
	}
	return 0;
}

```


---

## 作者：LAWArthur (赞：1)

场外选手乱搞题解（并写挂5次真考早就寄了）

# 题意
给定 $n$ 个集合 $S_n\subseteq U=\{1,2,\cdots,n\}$，求出两个相交且不包含的集合或输出无解。

# 正解
先考虑怎么求无解的情况，即所有的集合要么包含，要么不交。

考虑对集合由大至小排序，依次枚举，这样就不用考虑当前集合包含已枚举集合的情况。

考虑到若有 $S_j\subseteq S_k$，则 $S_i\subseteq S_j\Rightarrow S_i\subseteq S_k$，我们对每个全集 $U$ 中的元素 $x$ 维护包含它的大小最小的集合 $T_x$，那么对于每个集合 $S_i$ 只需验证所有 $x\in S_i$ 的 $T_x$ 都相等。

因为我们从大到小枚举，所以维护 $T$ 只需对每个集合 $S_i$ 覆写集合中元素的 $T_x=i$。

而若集合 $S_i$ 验证失败了，我们也可以十分轻易地找出一组解：

考虑找到大小最小的 $S_{T_x}(x\in S_i)$（记作 $S_j$），那么对于所有 $S_{T_x}(x\in S_i,T_x\ne j)$ 必然要么包含 $S_j$，要么与 $S_j$ 不交。所以对于 $T_x\ne j,x\in S_i$，$x$ 一定不属于 $S_j$，于是 $i,j$ 便是一对相交且不包含的集合。

复杂度 $O(nT+m)$（排序使用计数排序）。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000005
int T,n,id[N],k[N];
vector<int> xs[N];
int cnt[N],rnk[N],bel[N];

void solve(){
	scanf("%d",&n);
	int x;
	fill(cnt,cnt+n+1,0);
	for(int i=1;i<=n;i++){
		scanf("%d",k+i);
		xs[i].clear();
		cnt[k[i]]++;
		for(int j=1;j<=k[i];j++){
			scanf("%d",&x);
			xs[i].push_back(x);
		}
	}
	
	
	for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
	rnk[0]=N-1;
	for(int i=1;i<=n;i++)id[cnt[k[i]]]=i,rnk[i]=cnt[k[i]]--;
	
	fill(bel+1,bel+n+1,0);
	for(int i=n;i>=1;i--){
		if(k[id[i]]==0)continue;
		int u=bel[xs[id[i]][0]];
		bool flag=0;
		for(int j=0;j<k[id[i]];j++){
			if(bel[xs[id[i]][j]]!=u){
				flag=1;
				if(rnk[u]>rnk[bel[xs[id[i]][j]]])u=bel[xs[id[i]][j]];//选择所有相交集合中大小最小的
			}else bel[xs[id[i]][j]]=id[i];
		}
			
		if(flag){
			printf("YES\n%d %d\n",u,id[i]);
			return;
		}
	}
	printf("NO\n");
}

int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```


---

## 作者：WeLikeStudying (赞：1)

- 如此简单的题目，如此简明的性质，我却思考了相当的时间，导致我 $T3$ 没有足够的时间实现。
- 这次的情况处处值得反思，所以蒟蒻将该题解写成。
- 我对此的总结是：我需要合理安排训练时间，尽量覆盖广泛的活动，以免产生细节上的差错。
- 希望各位能圆梦考场，不留遗憾。

**题意**
- [链接](https://www.luogu.com.cn/problem/P8252)。
- 给定 $n$ 个值域为 $1$ 到 $n$ 的数集，判断两个集合是否满足有交且不互相包含。
- 保证集合的总大小不大于 $2\times 10^6$。

**分析**
- 问题已经足够简化了，接下来是寻找性质。
- 很容易想到的性质是，如果集合从小到大一个一个扫，且所有集两两有交且不互相包含，那么集合的包含关系会形成一棵树形结构，即有根树森林。
- 如果我们从小到大扫，我们的目标是判断所有与该集合有交的集合是否被该集合包含。
- 容易发现，只有树根是必要的，因为如果任何儿子满足要求，那么父亲一定满足要求。
- 所以我们暴力扫：每次维护被每个集合包含的最大集合，然后在扫描的时候统计第 $i$ 个集合有没有将所有一开始属于的元素所在的集合包含，如果没有，找到一组解，如果有，重新覆盖集合。
- 另外有一种做法，是[这位大佬](https://www.luogu.com.cn/user/53118)提出的，倒着做，本质上一样，但是判定更加方便，只需要判断是否覆盖了多种颜色。
- 这两个做法都很容易做到线性，但对于这题，没必要。
```cpp
#include<bits/stdc++.h>
const int N=1100000;
using namespace std;
int T,n,id[N],fa[N],gd[N];
map<int,int>ccf;
struct good
{
	int m;
	vector<int>to;
}e[N];
bool cmp(int x,int y)
{
	return e[x].m<e[y].m;
}
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&e[i].m);
		e[i].to.clear();
		e[i].to.resize(e[i].m);
		for(int z=0;z<e[i].m;++z)
			scanf("%d",&e[i].to[z]);
		id[i]=i,fa[i]=0;
	}
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		ccf.clear();
		for(auto z:e[id[i]].to)
			++ccf[fa[z]];
		for(auto z:e[id[i]].to)
			if(fa[z]!=id[i]&&ccf[fa[z]]>0&&ccf[fa[z]]<e[fa[z]].m)
			{
				printf("YES\n%d %d\n",fa[z],id[i]);
				return;
			}
			else fa[z]=id[i];
	}
	puts("NO");
}
int main()
{
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：Little09 (赞：0)

先把所有集合按大小排序，设排序后的为新编号。

考虑所有会做第 $i$ 题的人，如果存在两个人 $x,y$ 满足 $x$ 的新编号小于 $y$ 且存在一道题 $x$ 会 $y$ 不会，$(x,y)$ 就是答案。否则就不存在。

考虑不存在的情况，一定形成了一条包含关系的链。所以条件可以转化为考虑 $x,y$ 满足 $y$ 是 $x$ 的后继就可以了。

如果再某一题中 $x$ 的后继为 $y$，而在另一题中 $x$ 的后继为 $z$（或者没有后继）。那么只要比较 $y,z$ 新编号的大小，会发现 $(x,y)$ 或者 $(x,z)$ 一定满足条件了。

否则每道题 $x$ 的后继都是一样的，肯定找不到答案了，因此不存在。

时间复杂度 $O(n\log n)$，瓶颈在排序。可以换用桶排变为 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2000005;
int n;
vector<int>v[N];
int a[N],ans[N];
bool cmp(int x,int y)
{
	if (a[x]==a[y]) return x<y;
	return a[x]<a[y];
}

inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}

void work()
{
	n=read();
	for (int i=1;i<=n;i++) v[i].clear();
	for (int i=1;i<=n;i++) ans[i]=0;
	for (int i=1;i<=n;i++) 
	{
		a[i]=read();
		for (int j=1;j<=a[i];j++)
		{
			int x=read();
			v[x].push_back(i);
		}
	}
	a[n+1]=n+1;
	for (int i=1;i<=n;i++) v[i].push_back(n+1);
	for (int i=1;i<=n;i++) sort(v[i].begin(),v[i].end(),cmp);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<(int)v[i].size();j++)
		{
			if (ans[v[i][j-1]]==0) ans[v[i][j-1]]=v[i][j];
			else if (ans[v[i][j-1]]!=v[i][j])
			{
				int res=ans[v[i][j-1]];
				if (cmp(v[i][j],res)) res=v[i][j];
				printf("YES\n%d %d\n",v[i][j-1],res);
				return;
			}
		}
	}
	printf("NO\n");
}

int main()
{
	int T=read();
	while (T--) work();
	return 0;
}

```


---

## 作者：LinkyChristian (赞：0)

首先把集合按大小从大到小排序，这里给出一个推论，在于当前集合有交的集合中，如果存在满足条件的集合，则大小最小的集合一定是其中一个。

考虑反证：如果当前集合与比与他有交的最小的集合不满足条件，而与一个更大的集合满足条件，则那个更大的集合和与他有交的最小的集合一定也满足条件。但我们之所以会处理到当前集合是因为之前的集合没有满足条件的，矛盾。

记下覆盖每一个位置的最小的集合编号，每次查看与自己有交的最小集合是否满足条件即可。

```cpp
#include<bits/stdc++.h>
#define N 2000010
using namespace std; 
int T,n,m;
struct node{
	int c,id;
	vector<int> a;
	void init() {c=id=0;a.clear();}
	bool operator <(const node o) {return c>o.c;}
}p[N];
int bel[N],mp[N];
int read() {
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0',ch=getchar();
	return f*res;
}
void work() {
	n=read();
	for(int i=1; i<=n; i++) {
		p[i].init(),bel[i]=0,p[i].c=read(),p[i].id=i;
		for(int j=0; j<p[i].c; j++) p[i].a.push_back(read());
	}
	sort(p+1,p+n+1);int x,y;
//	for(int i=1; i<=n; i++) printf("%d\n",p[i].c);
	int tmp=0;
	for(int i=1; i<=n; i++) {
		x=y=0,tmp=p[i].id,mp[p[i].id]=i;
		for(int j=0; j<p[i].c; j++) {
			int t=p[i].a[j],v=bel[t];bel[t]=tmp;
			if(v==0) v=tmp;
			if(!x) x=v;
			else if(x!=v) y=v;
			if(x&&y) {n=p[i].c=-1;}
		}
	}
	if(n!=-1) printf("NO\n");
	else {
		if(x==tmp||y==tmp) ;
		else if(p[mp[x]].c>p[mp[y]].c) x=tmp;
		else y=tmp;
		printf("YES\n%d %d\n",x,y);
	}
}
int main() {
	T=read();
	while(T--) work();
}
```


---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/P8252)

赛时随机化无果后暴力跑路。

## 题目分析

官方正解是对序列上树，用 `bitset` 或哈希表维护包含关系。

一种更巧妙但且更可想的做法则是用桶构造答案。

### 构造方法：

首先对集合从大到小排序，然后枚举集合。

标记每一道题属于哪个集合。若该题已标记则将其覆盖。

两种情况下有解：

1. 该集合中存在题目已标记，存在题目未标记。

2. 该集合的题目已分别被两个或以上的集合标记。

满足以上两种情况之一，则跳出枚举，输出答案。

否则无解。

时间复杂度 $O(m)$。

### 说明：

情况 1 容易理解，未标记的题目肯定没有其它集合染指，有题目被标记则证明与先前某一集合有交集，符合题意。

对于情况 2，当前集合可以同标记它的集合中大小最小的那个讨论。

因为标记题目是小集合可覆盖大集合，大集合仍标记的题目一定是小集合不包含的。因此当前集合与大集合和小集合都有重合。又因为小集合大小大于当前集合，可得当前集合与小集合有重合题目但不互相包含。

终上，构造方法是正确的。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 1000010
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int T, n, b[N];
struct node {int len, id;} a[N];

inline bool cmp(const node &a, const node &b) {return a.len > b.len;}

inline void WORK()
{
	read(n);
	bool flg = 0; int ansa, ansb; vector<int> g[N];
	memset(b, 0, sizeof(b));
	for (rei i = 1; i <= n; i++)
	{
		read(a[i].len); a[i].id = i;
		for (rei j = 1; j <= a[i].len; j++)
		{
			int x; read(x);
			g[i].push_back(x);
		}
	}
	sort(a + 1, a + 1 + n, cmp);
	for (rei i = 1; i <= n; i++)
	{
		int u = a[i].id; bool flga = 0, flgb = 0;
		for (rei j = 0; j < g[u].size(); j++)
		{
			int x = g[u][j];
			if (i == 1) b[x] = i;
			else if (!b[x]) flgb = 1, b[x] = i;
			else 
			{
				if (flga && ansa != b[x])
				{
					ansa = max(ansa, b[x]);
					flgb = 1; break;
				}
				flga = 1, ansa = b[x];
				b[x] = i;
			}
		}
		if (flga && flgb) {ansa = a[ansa].id; flg = 1; ansb = a[i].id; break;}
	}
	if (flg) printf("YES\n%d %d\n", ansa, ansb);
	else printf("NO\n");
}

int main()
{
	read(T); 
	while (T--) WORK();
	return 0;
}
```


---

## 作者：novax (赞：0)

提供两种~~不同于[官方题解](https://www.noi.cn/xw/2022-03-28/759692.shtml)的~~思路！

[题面](https://www.luogu.com.cn/problem/P8252)。

### 题意

有一场 $N$ 道题，$N$ 个人参加的模拟赛，给出每人会做的题目集合 $S_i$，问是否存在 $A,B$ 两人，他们会做的题的集合满足如下关系：

![](https://cdn.luogu.com.cn/upload/image_hosting/2cme3y3b.png)

### 思路

根据题意，若 $S_A,S_b$ 有交集且都不是对方的子集，那么 $A,B$ 一定构成一组合法解。大小为 $0$ 或 $1$ 的集合一定不会成为答案，所以可以在开始时将其剔除。

#### 一

首先我们将 $S$ 按照集合内元素个数从大到小排序并重新编号，然后记 $last_i$ 为当前上一个会做第 $i$ 题的人的编号。

对于第 $i$ 个人，遍历 $S_i$，如果 $S_i$ 中存在两道题 $x,y$ 的 $last$ 不同，则 $last_x$ 或 $last_y$ 中元素数较少的能与 $i$ 构成合法解；否则 $S_i$ 一定完全包含于此前某集合中，则再次遍历 $S_i$，将其中所有元素的 $last$ 的值都更新为 $i$。

因为已经将集合按照元素数排序，所以含元素多的集合必然先处理。且每次更新的 $last$ 都必然是覆盖已有某个集合的子集，则实质上维护了若干互不相交的小集合，若有集合跨越了此前两个不同集合，则有解。时间复杂度为 $O(T\times (n\log n + (n+m)))$

#### 二

我们可以先使用``vector``或链表记录第 $i$ 题会做人的集合 $B_i$，然后同样对 $S$ 按照大小排序。

每次取出当前剩下未判断的集合中元素最多的集合 $i$，然后将其中元素使用哈希或``set``维护出来。这时再次遍历 $S_i$，对于 $S_i$ 中的元素 $j$，遍历 $B_j$。若元素 $k \in B_j$ 且集合 $S_k$ 还未被判断过，则遍历 $S_{k}$，判断其中是否存在元素不属于 $S_i$。若不存在，则 $S_{k} \subseteq S_i$，不合法，对集合 $S_{k}$ 打上删除标记；否则 $i$ 与 $k$ 构成一组合法解。维护集合是否已判断可使用链表实现序列元素快速删除。

通过从遍历会做 $i$ 会做的某道题的人的集合，即遍历了所以尚未判断的与 $i$ 有交集的集合，保证了“有交集”这一条件；且每个集合最多被判断一次。用哈希实现，时间复杂度为 $O(T\times (n\log n + (n+m)))$。

---

## 作者：PrincessQi (赞：0)

由于两个集合交集不为空是两个集合有一个共同元素的充要条件，所以考虑每个集合对单个数的覆盖的情况即可。

对于每个数 $x$，维护一个集合 $t_x$ 表示这个数被哪些集合覆盖。把 $S$ 按集合大小从大到小排序，并依次枚举，若当前集合 $S_i$ 覆盖的数的集合 $t_{x\in S_i}$不完全相同，则找到了答案。

你发现这样需要对 $t$ 进行哈希，而且不方便统计答案，于是你发现了一个性质：对数 $x$ 的集合 $t_x$，记录最后一个覆盖这个数的集合 $l_x$ 即可。若找到答案，则一组可行解为当前集合以及 $\max l_{x\in S_i}$。

code：

```
#include<bits/stdc++.h>
using namespace std;
struct xf{
    int k,id;
    vector<int>qwq;
}a[2000005];
int T,n,lst[2000005];
int cmp(xf x,xf y){
    return x.k>y.k;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].k);
            int x;
            vector<int>().swap(a[i].qwq);
            for(int j=1;j<=a[i].k;j++)
                scanf("%d",&x),a[i].qwq.push_back(x);
            a[i].id=i;
        }
        sort(a+1,a+1+n,cmp);
        memset(lst,0,sizeof(lst));
        int f=0,tmp;
        for(int i=1;i<=n;i++){
            for(int j=0;j<a[i].k;j++){
                if(j==0)tmp=lst[a[i].qwq[j]];
                if(lst[a[i].qwq[j]]!=tmp){
                    puts("YES");
                    printf("%d %d\n",a[i].id,a[max(tmp,lst[a[i].qwq[j]])].id);
                    f=1;
                    break;
                }
                lst[a[i].qwq[j]]=i;
            }
            if(f==1)break;
        }
        if(f==0)puts("NO");
    }
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Preface

这题简单啊，考场上一堆人放弃……

### Analysis

为简便，设两集合 $A\Box B$ 表示满足

$$A\cap B\ne\varnothing\ \land\ A\nsubseteq B\ \land\ B\nsubseteq A$$

这些条件，即**交叉且不包含**。

------------

**请一定认真仔细阅读此结论，因为这是本题解的核心。**

#### 结论 A：

$$S_x\Box S_y\ \land\ S_x\subseteq S_z\ \land\ |S_z|\le|S_y|\implies S_z\Box S_y$$

#### 证明：

$$\begin{aligned}
S_x\cap S_y\ne\varnothing\ \land\ S_x\subseteq S_z &\implies S_z\cap S_y\ne\varnothing
\\
S_x\nsubseteq S_y\ \land\ S_x\subseteq S_z &\implies S_z\nsubseteq S_y
\\
|S_z|\le|S_y|\ \land\ S_x\nsubseteq S_y\ \land\ S_x\subseteq S_z &\implies S_y\nsubseteq S_z
\end{aligned}$$

------------

由此，我们可以将 $S_1,S_2,\dots,S_n$ **排序**，使得 $|S_1|\le|S_2|\le|S_3|\le\dots\le|S_n|$（**注意**最后输出方案时要输出排序前的编号）。

我们遍历第 $x=1\to n$ 个人。

我们维护数组 $a_i$ 表示第 $i$ 道题目现在第 $a_i$ 个人会做（$i\in S_{a_i}$）。特别地，$a_i=0$ 表示第 $i$ 道题目目前没有人会做。

我们**开桶统计** $a_i\ |\ i\in S_x$。若 $\exists y<x\ |\ S_x\Box S_y$，则 $y$ 在桶中出现的次数一定 $>0$ 且 $<|S_y|$（因为与 $S_x$ 交叉且不包含）。存在 $y$ 的话直接输出 $(x,y)$ 作为答案即可。否则把所有 $i\in S_x$，$a_i$ **都赋值**为 $x$（由结论 A，**这些被 $S_x$ 包含的集合就无用了**）。

上文「无用了」的含义是：设某个被 $S_x$ 包含的集合为 $S_c$。**若之后存在**集合 $S_k$ 使得 $S_k\Box S_c$，则有 $S_k\Box S_x$，即 $(x,k)$ **也为答案**，所以 $S_c$ **变得无用**。

时间 $O(n\log n+m)$

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb emplace_back
#define For(i,j,k) for(int i=j;i<=k;i++)
#define N 1000010
int n,sz[N],p[N],a[N],t[N];
vector<int> e[N];
inline bool cmp(int x,int y){return sz[x]<sz[y];}
void work(){
	cin>>n;
	For(i,1,n) e[i].clear();
	For(i,1,n) a[i]=t[i]=0;
	int x;
	For(i,1,n){
		cin>>sz[i];
		For(j,1,sz[i]) cin>>x,e[i].pb(x);
	}
	For(i,1,n) p[i]=i;
	sort(p+1,p+1+n,cmp);//sort S_1~n,but just sort id 
	For(i,1,n){
		x=p[i];
		for(int j:e[x]) if(a[j]) t[a[j]]++;
		for(int j:e[x]) if(t[a[j]]){
			if(t[a[j]]!=sz[a[j]]){cout<<"YES\n"<<x<<" "<<a[j]<<"\n";return ;}
			t[a[j]]=0;
		}
		for(int j:e[x]) a[j]=x;
	}
	cout<<"NO\n";
}
signed main(){IOS;int T;cin>>T;while(T--)work();return 0;}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

一个人要能参与讨论，一定会跟另一个人有共同题目，且大家都各自会做不同的题目。

首先，一个贪心的思路是从题目数多的向题目数少的排序。这样能保证如果后面出现了新的题目，一定不会被前面的包含。

然后，记录一个 $bel$ 数组，$bel_i$ 表示当前第 $i$ 题谁会了。如果 $bel_i = 0$，那么就是新题； 如果属于至少 2 个人，那么相对于题量更少的那个，下一个人也是有新题的，可以跟题量少的那个讨论。所以就动态的记录两个数 $x,y$，表示那两个人。如果 $x$ 和 $y$ 同时不为 0，说明找到了一组答案，输出就是题量较小的和当前的的组合。

时间复杂度 $O(n \log n+m)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> p[1000005];
int bel[1000005];

bool cmp(vector<int> a,vector<int> b)
{
	return a.size()>b.size();
}
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		int n,k,x; scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			p[i].clear();
			scanf("%d",&k);
			for(int j=1;j<=k;j++)
				scanf("%d",&x),p[i].push_back(x);
			sort(p[i].begin(),p[i].end());
			p[i].push_back(i); // 这样方便在排序之后找回原来的编号
		}
		sort(p+1,p+1+n,cmp); // 好像是可以直接对一个 vector 排序的。
		
		int fir,sec,flag=0,now;
		for(int i=1;i<=n;i++)
		{
			fir=0,sec=0,now=i;
			int tmp=p[i].size()-1;
			for(int j=0;j<p[i].size()-1;j++)
			{
				int v=p[i][j],lst=bel[v];
				bel[v]=i;
				if(!lst) lst=i;
				if(!fir) fir=lst; // 如果第一个还没有
				else if(fir!=lst) sec=lst; // 如果第二个还没有
				if(fir && sec) // 如果齐活了
				{
					flag=1;
					break;
				}
			}
			if(flag) break;
		}
		if(!flag) puts("NO");
		else
		{
			puts("YES");
			if(fir!=now && sec!=now) // 选取一个 size 较小的组合。
				if(p[fir].size()>p[sec].size()) fir=now;
				else sec=now;
			printf("%d %d\n",p[fir][p[fir].size()-1],p[sec][p[sec].size()-1]);
		}
		for(int i=1;i<=n;i++) bel[i]=0; // 一定记得清空，我因为不清空 pj + tg 一共挂了小 100 分。
	}
	return 0;
}
```

---

