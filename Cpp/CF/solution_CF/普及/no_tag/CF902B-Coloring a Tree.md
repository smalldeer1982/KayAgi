# Coloring a Tree

## 题目描述

You are given a rooted tree with $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , the root is the vertex number $ 1 $ .

Each vertex has a color, let's denote the color of vertex $ v $ by $ c_{v} $ . Initially $ c_{v}=0 $ .

You have to color the tree into the given colors using the smallest possible number of steps. On each step you can choose a vertex $ v $ and a color $ x $ , and then color all vectices in the subtree of $ v $ (including $ v $ itself) in color $ x $ . In other words, for every vertex $ u $ , such that the path from root to $ u $ passes through $ v $ , set $ c_{u}=x $ .

It is guaranteed that you have to color each vertex in a color different from $ 0 $ .

You can learn what a rooted tree is using the link: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>.

## 说明/提示

The tree from the first sample is shown on the picture (numbers are vetices' indices):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/9fd1d55fa8fc46341a8b892f02c91e5845a9cee1.png)

On first step we color all vertices in the subtree of vertex $ 1 $ into color $ 2 $ (numbers are colors):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e11b694106163670fb12fdde15a9f65a4e1cb530.png)

On seond step we color all vertices in the subtree of vertex $ 5 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e36a2cbd1ae067ab6fd537cd6badf9d7433ee5c6.png)

On third step we color all vertices in the subtree of vertex $ 2 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e700d0bc8664e90658b34cd2376df32d0611fede.png)

The tree from the second sample is shown on the picture (numbers are vetices' indices):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/67ba592a2c43f57a4f90fbf32ea9b4099ae3ce16.png)

On first step we color all vertices in the subtree of vertex $ 1 $ into color $ 3 $ (numbers are colors):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/a70897e485cd2f798f1fbdf16aad3be9100baa22.png)

On second step we color all vertices in the subtree of vertex $ 3 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/00b2012fb6c63cf50c8cbb62275892a14d90331b.png)

On third step we color all vertices in the subtree of vertex $ 6 $ into color $ 2 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/cbb680be6f7f4a3785c9124a3b69bfeceadc9ad8.png)

On fourth step we color all vertices in the subtree of vertex $ 4 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/2dab5297c24ff5c2f70dfec33f37cb0e4b4866c7.png)

On fith step we color all vertices in the subtree of vertex $ 7 $ into color $ 3 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/8a33180d0bd5c28d2385265618229c6952307c3c.png)

## 样例 #1

### 输入

```
6
1 2 2 1 5
2 1 1 1 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
1 1 2 3 1 4
3 3 1 1 1 2 3
```

### 输出

```
5
```

# 题解

## 作者：pikabi (赞：5)

感觉其他大佬的题解有些麻烦了，身为蒟蒻的我还是写一篇简单的吧

[原题链接](https://www.luogu.org/problem/CF902B)

### 题外话：

感觉这道题的翻译要加上原树颜色全为0，不然一些蒟蒻（比如我）会以为原色是编号QAQ（然后WA

这道题给予了我神秘的Unknow Error和永恒的judging（雾

标签有误？好像和期望无关吧。。。

### 正题：

“一个树，每次可以选择一个子树染成同一个颜色，求染成目标状态的最小操作次数。”显然可知，将父亲染色是最优的，否则会改变子树的颜色导致步数增加。因此，我们的步骤是：建树——>从根开始染色，与预期不同则ans++——>输出结果。这里我们不需要将子树颜色改变，只需要传递父节点的颜色就行了。

具体内容详见代码

```cpp
#include <cstdio>

using namespace std;

struct EDGE{
	int to, nxt;
}e[100005];

int n, c[100005],a[100005], head[100005], cnt, son[100005], ans;

void dfs(int now, int cl){//now为子树编号，cl为父亲的颜色
	if(cl != c[now]){//颜色不同就答案加
		ans++;
		cl = c[now];//变色
	}
	if(!son[now]) return ;//没儿子，走
	for(int i = head[now]; i; i = e[i].nxt )//有儿子，搜
		dfs(e[i].to , cl);
}

int main(){
	scanf("%d",&n);
	for(int i = 2; i <= n; i++){//建树
		int x;
		scanf("%d",&x);
		e[++cnt].nxt = head[x];
		e[cnt].to = i;
		head[x] = cnt;
		son[x]++;
	}
	for(int i = 1; i <= n; i++) scanf("%d",&c[i]);
	dfs(1, 0);//开始搜，初始父亲颜色为0
	printf("%d",ans);
	return 0;
}
```

）应该比较短的说（

完结撒花*(੭*ˊᵕˋ)੭*ଘ

---

## 作者：hank0402 (赞：4)

### 题目大意：
将一棵树的每个节点染成目标颜色，每次可将一棵子树内的每一个节点染成同样的颜色，求最小的染色次数。

### 思路详解：

显然，如果我们考虑染色，一定要从最大的子树开始，递归下去一棵一棵染色，否则，如果你把所有的小子树都染完了，你又要染大子树，小子树就白费了。

那么，如果要判定这棵子树要染成什么颜色，必定要看根节点，因为他的子树可以之后染。这样，算法的过程也就清晰了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[10010];
int ans, p[10010], c[10010], n;
void dfs(int x, int cc, int from) { //递归染树
	if(c[x] != cc) ans ++;			//如果根节点与目标颜色相同，必定要染
	int len = g[x].size();
	for(int i = 0; i < len; ++i) { //遍历每棵子树
		int v = g[x][i];
		if(v == from) continue;
		
		dfs(v, c[x], x);       //递归求解
	}
}
int main() {
	cin >> n;
	for(int i = 1; i < n; ++i) {
		cin >> p[i];
		g[i + 1].push_back(p[i]);  //用vector存树
		g[p[i]].push_back(i + 1);
	}
	for(int i = 1; i <= n; ++i) cin >> c[i];
	dfs(1, -1, -1);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：天南星魔芋 (赞：3)

~~今天没事来水一发tj~~


------------
我们看题：

* 一个树，每次可以选择一个子树染成同一个颜色，求染成目标状态的最小操作次数。

由于是在树上着色 ，所以可以得出以下两个结论：

* 若节点在祖先染色后未染色，则节点颜色与祖先相同。

* 若节点和这个节点的子节点都要染色，必定先染这个节点。（因为染完父亲后会毁坏儿子的颜色）

所以我们用 $dfs$ 按先父亲后儿子的顺序，将每个节点的颜色染成目标颜色就行了。

直接上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int bcj[15000];// 并查集  记录 每个节点的父亲
 
int fir[15000],nxt[30000],to[30000],top=0;//前向星  记录 每个节点的儿子 

int color[15000];// 记录 每个节点的目标颜色 

int ans=0;//染了几次 

//---------------------------------------------// 快读 
int read(){
	int x=0,t=1;
	char f=getchar();
	while(!isdigit(f)){
		t=(f^'-')? t:-1;
		f=getchar();
	}
	while(isdigit(f)){
		x=x*10+f-'0';
		f=getchar();
	}
	return x*t;
}
//--------------------------------------------// 快读
 
void add(int x,int y){//-----------------------------//前向星存边 
	top++;nxt[top]=fir[x];fir[x]=top;to[top]=y;
}

void dfs(int x){//---------------------------------//dfs 

	if(color[x]!=color[bcj[x]]){//由于 染儿子时 父节点 已染好 
	    ans++;                 // 所以 儿子颜色 若不是 最近父节点颜色 要重染 
	}

	for(register int i=fir[x];i;i=nxt[i]){//染完父亲染儿子 
		dfs(to[i]);
	}
}
int main(){
	n=read();
	for(register int i=2;i<=n;i++){
		bcj[i]=read();// 并查集 存边 
		add(bcj[i],i);// 前向星 存边 
	}
	for(register int i=1;i<=n;i++){
		color[i]=read();
	}
	dfs(1);
	printf("%d\n",ans);
}
```

~~于是就完美的跑了最优解。~~


这篇题解就到这里了，如有不足请大家多多指教。

---

## 作者：wangyi_c (赞：1)

## 0.前言

[题目传送门](https://www.luogu.com.cn/problem/CF902B)

## 1.题目大意

对根节点编号为 $1$ 的一棵树进行染色，每次可以选择一个子树染成同一个颜色，求染成目标状态的最小操作次数。

## 2.思路讲解

我们这里可以运用一个**贪心**的想法：当染完一个子树后，再染它的根节点，那么所有之前的操作都白费了，所以看染什么颜色就要先看它对应的根节点。

我们只需要搜索一直往下搜，如果根节点与本来就要染的颜色一样，那就一定要染，再继续搜自己的儿子们。

## 3.AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
#define push push_back
using namespace std;
const int maxn=1e4+10;
int ans,col[maxn],n;
bool is_gone[maxn];
vector <int> g[maxn]; 
void faster(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	return ;
}
void dfs(int from,int color){
	is_gone[from]=true;//只能走一边
	if(col[from]!=color){//如果与原来的颜色一样，那就一定要染色
		ans++;
		color=col[from];
	}
	for(auto y:g[from]){
		if(y!=from && !is_gone[y]){ //找儿子
			dfs(y,color);
		} 
	}
	return ;
}
signed main(){
	faster();
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v=i+1;
		cin>>u;
		g[u].push(v);
		g[v].push(u);
	}
	for(int i=1;i<=n;i++) cin>>col[i];
	dfs(1,0);//从根节点开始搜，颜色为0
	cout<<ans;
	return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：PtrZ (赞：1)

### Coloring a Tree
[题目传送门](https://www.luogu.com.cn/problem/CF902B)

~~标签是期望，本蒟蒻直接吓一跳，其实根本不用期望~~

题目大意：给你一棵树，每次可以染一棵子树，让你求染到目标状态的最小次数。

思路：由题意分析，我们肯定要从根来染色，因为我们把根染色才能把树首先定义一个颜色，然后从根出发每次往下遍历整棵树，如果此时这个节点和现在的颜色不同就修改此时的颜色，那么$ans$++，直到全部搜完。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[20000],ans;
vector<int> g[20000];
void dfs(int x,int cc) //递归遍历树
{
	if(a[x]!=cc) ans++; //颜色不同修改
	int len=g[x].size();
	for(int i=0;i<len;i++) //往下子树遍历
	{
		int v=g[x][i];
		dfs(v,a[x]);
	}
	return ;
}
int main()
{
	cin>>n;
	for(int i=2;i<=n;i++)
	{
		int pi; cin>>pi;
		g[pi].push_back(i); //邻接矩阵存树
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]); //输入颜色
	}
	dfs(1,-1); //递归入口
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：JBLee (赞：1)

看题目的方法是期望，但直接dfs就能够做

原谅蒟蒻太弱不懂期望，尽管听了课但还是不怎么会用。

就可以先建一棵树，然后在树上进行dfs即可

我在这里用了一个vis数组来标记，如果当前要染色的那个点已经是目标颜色了，那么就可以不管它了，有一个类似于贪心的思路

如果没有成为目标规定的颜色，就必须要去染他，然后染色的次数就加一，我在代码里面的tot值就始终是染色的最小次数(貌似不算太严谨的证明)。

代码奉上
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
const int mxx=0x3f3f3f3f;
struct node
{
	int next;
	int to;
	int se;
}edge[3*maxn];//结构体,保存当前节点信息 
int head[maxn],cnt,maxx,tot;
int color[maxn];//要染的颜色 
void add(int x,int y)//前向星不用多说 
{
	edge[++cnt].next=head[x];
	edge[cnt].to=y;
	head[x]=cnt;
}
bool vis[maxn];//标记数组 
void dfs(int now,int yanse,int father)//dfs当前的节点，要染的颜色，该节点的父亲节点 
{
	vis[now]=true;
	yanse=color[now];
	if(edge[now].se!=color[now])//没有成为目标颜色，无论如何也要染 
	{
		tot++;
	}
	else
	{
		vis[now]=true;
	}//如果已经成为了，标记为true 
	for(int i=head[now];i;i=edge[i].next)//树上遍历 
	{
		int v=edge[i].to;
		if(!vis[v])//只用去遍历那些没有成为目标色的点 
		{
			edge[v].se=color[now];
			dfs(v,yanse,now);//递归 
		}
	}
}
int n,x;
int root;
int main()
{
	scanf("%d",&n);
	root=1;
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		add(i,x);
		add(x,i);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&color[i]);
	} 
	dfs(root,0,0);//递归入口 
	printf("%d",tot);
	return 0;
} 
```
希望能通过吧qwq

如果有意见欢迎各位大佬指出

蒟蒻的路还很长啊



---

## 作者：AC_Automation (赞：1)

题面：一颗树，每次可以选择一个子树染成同一个颜色，求染成目标状态的最小操作次数。

首先，如果对于一个子树，这个子树的根节点需要被染色，那么这个根节点一定要先被染色，然后他的孩子们才会被染色。因为给这个根节点染色的时候，它下面的孩子们同时也会被染色，若是之前就给他的孩子们染色，那么这样的染色是会被浪费掉的。

其次，对于两个兄弟子树，他们染色的先后顺序是不影响染色的次数的。

知道的这两点之后，就有了一种很容易设计出的算法了。从根节点开始遍历整棵树，如果某个子树的根节点需要被染色，则ans++，并将这个子树染成这种颜色（打标记），然后再遍历它的所有孩子，重复以上操作。

代码（注释应该比较清晰）
```
#include<iostream>
using namespace std;
struct edge{
	int v,nxt;
}a[20005];
int head[10005],clr[10005],cnt=0;
void add_edge(int u,int v){
	cnt++;
	a[cnt].v=v;
	a[cnt].nxt=head[u];
	head[u]=cnt;
}//链式前向星
int dfs(int u,int color,int fa){//color代表它这个子树之前被染成什么颜色了，u是节点编号
	int ans=0;
	if(color!=clr[u])ans++;//需要被染色一次
	for(int i=head[u];i;i=a[i].nxt){
		if(a[i].v==fa)continue;
		ans+=dfs(a[i].v,clr[u],u);//递归下去，此时这个子树一定被染成了clr[u]这个颜色，因为如果没有将当前节点的子树染色，则这个子树一定在之前被染过一次色
	}
	return ans;
}
int main(){
	int n,v;
	cin>>n;
	for(int i=2;i<=n;i++){
		cin>>v;
		add_edge(i,v);
		add_edge(v,i);
	}
	for(int i=1;i<=n;i++)cin>>clr[i];
	cout<<dfs(1,0,-1);
	return 0;
}


```

---

## 作者：meisr (赞：1)

我们可以发现，对于任意一棵树，从根节点开始染色显然是最优的。如果我们从子树开始染色，这些被染过色的点总会在染根节点时被再次染色，所以在染根节点之前染子树的点显然是不必要的。于是乎，本题完美的变成了一道dfs遍历树的题目。

染色的方案：每当遍历到一个点的时候，若这个点的父节点的颜色与它所期望的颜色相同，则把它的颜色变成它父节点的颜色；否则把它的颜色变成它期望的颜色，同时使染色次数+1。

```
#include<iostream>
using namespace std;
bool vis[10001];
int n,cnt,want[10001],color[10001],h[10001],to[20001],nxt[20001];
inline void add(int x,int y){
	to[++cnt]=y;
	nxt[cnt]=h[x];
	h[x]=cnt;
}
int dfs(int now){
	int tot=0;
	vis[now]=true;
	if(color[now]!=want[now])
		tot++,color[now]=want[now];
	for(int i=h[now];i;i=nxt[i])
		if(!vis[to[i]]){
			color[to[i]]=color[now];
			tot+=dfs(to[i]);
		}
	return tot;
}
int main(){
	cin>>n;
	for(int i=2,to;i<=n;i++){
		cin>>to;
		add(i,to);
		add(to,i);
	}
	for(int i=1;i<=n;i++)
		cin>>want[i];
	cout<<dfs(1);
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

## 题目大意

一个树，每次可以选择一个子树染成同一个颜色，求染成目标状态的最小操作次数。

## 思路分析

贪心和深搜。

深搜过程中如果发现当前节点颜色与目标不一致，则改变，$\texttt{cnt++}$，并且往下递归过程中修改参数为目标颜色。

最后输出 $\tt cnt$ 即可。

## 主要坑点

貌似没有。输入格式比较感人，请自行理解。

## 完整代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 1; 

namespace FastIO
{
    struct instream
    {
        int base = 10;

        friend instream &operator>>(instream &in, int &num)
        {
            int flag = 1;
            int ans = 0;
            char ch = getchar();
            while (ch < '0' || ch > '9')
            {
                if (ch == '-')
                {
                    flag = -flag;
                }
                ch = getchar();
            }

            while (ch >= '0' && ch <= '9')
            {
                ans = ans * in.base + (ch - '0');
                ch = getchar();
            }
            num = ans * flag;
            return in;
        }
    };

    struct outstream
    {
        template<typename _CharT, typename _Traits = char_traits<_CharT>>
        struct typ {
            typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
        };

        int base = 10;

        friend outstream &operator<<(outstream &out, int num)
        {
            if (num < 0)
            {
                putchar('-');
                num = -num;
            }
            if (num >= 10)
            {
                out << num / 10;
            }
            putchar(num % 10 + '0');
            return out;
        }

        friend outstream &operator<<(outstream &out, const char * s) {
            printf("%s", s);
            return out;
        }

        friend outstream &operator<<(outstream &out, string s) {
            cout << s;
            return out;
        }

        friend outstream &operator<<(outstream &out, typ<char>::end e) {
            puts("");
            return out;
        }
    };

    instream fin;
    outstream fout;
}

using namespace FastIO;

int n, tmp;
vector<int> tree [maxn];
int to[maxn];
int cnt = 0;

void dfs(int node, int k) {
	if (to[node] != k) {
		k = to[node];
		cnt++;
	}
	for (int i = 0; i < tree[node].size(); i++) {
		dfs(tree[node][i], k);
	}
}

int main() {
	fin >> n;
	for (int i = 2; i <= n; i++) {
		fin >> tmp;
		tree[tmp].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		fin >> to[i];
	}
	dfs(1, 0);
	fout << cnt << endl;
	return 0;
}
```

---

## 作者：吴思诚 (赞：0)

## CF902B Coloring a Tree
[题目传送门](https://www.luogu.com.cn/problem/CF902B)

如果一棵子树的根没有改变颜色，则它的子树如何修改都不能对根节点进行修改，最后还是要对根节点修改，前功尽弃了。所以可以证明，一定要先按照深度修改颜色是最优的。于是，思路就很明确了：从树根 $1$ 开始搜索，每次判断与父亲节点颜色是否相同，不同则染色，直到所有点都染完色为止。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c[10001],ans,x;
vector<int>g[10001];
void dfs(int x,int cc){
	if(c[x]!=cc)
		ans++;
	int len=g[x].size();
	for(int i=0;i<len;i++){
		int v=g[x][i];
		dfs(v,c[x]);
	}
}
int main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		scanf("%d",&x);
		g[x].push_back(i);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	dfs(1,-1);
	cout<<ans;
	return 0;
}
```


---

## 作者：Unordered_OIer (赞：0)

# CF902B 题解
差点又要 fst /jk /jk /jk

## 题意
一棵 $n$ 节点的树，每个点颜色都为 $0$，每次可以把一个节点的子树染成同一种颜色，求达成目标状态的最小操作次数。

## 题解
这道题就是一个贪心，但是不知道为什么被打了一个期望的 tag？

由于要达到最终状态，如果一次完全染完一棵子树里的大部分颜色，里面还是有一些颜色需要重新染的，所以干脆直接考虑**从根节点开始染色，遇到一种不同的颜色就染成新的颜色**，可以保证这种方法是最优的。

复杂度 $\mathcal O(n)$，期望得分 $100$ 分。

## Code
个人认为马蜂更清晰（？
```cpp
#include<bits/stdc++.h>
#define N 10005
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(ll x){write(x),putchar('\n');}
struct edge{ll t,nxt;}es[N<<1];
ll n,hd[N],tot,c[N],ans,sonc[N];
inline void add(ll u,ll v){es[++tot]=(edge){v,hd[u]},hd[u]=tot;}
inline void dfs(ll u,ll fc){
	if(fc!=c[u])ans++,fc=c[u];
	if(!sonc[u])return;
	for(ll i=hd[u];i;i=es[i].nxt)
		dfs(es[i].t,fc);
}
int main(){
	n=read();
	for(ll i=2,p;i<=n;i++)
		p=read(),add(p,i),sonc[p]++;
	for(ll i=1;i<=n;i++)c[i]=read();
	dfs(1,0);
	writeln(ans);
	return 0;
}
```

---

