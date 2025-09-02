# Road Map

## 题目描述

There are $ n $ cities in Berland. Each city has its index — an integer number from $ 1 $ to $ n $ . The capital has index $ r_{1} $ . All the roads in Berland are two-way. The road system is such that there is exactly one path from the capital to each city, i.e. the road map looks like a tree. In Berland's chronicles the road map is kept in the following way: for each city $ i $ , different from the capital, there is kept number $ p_{i} $ — index of the last city on the way from the capital to $ i $ .

Once the king of Berland Berl XXXIV decided to move the capital from city $ r_{1} $ to city $ r_{2} $ . Naturally, after this the old representation of the road map in Berland's chronicles became incorrect. Please, help the king find out a new representation of the road map in the way described above.

## 样例 #1

### 输入

```
3 2 3
2 2
```

### 输出

```
2 3 ```

## 样例 #2

### 输入

```
6 2 4
6 1 2 4 2
```

### 输出

```
6 4 1 4 2 ```

# 题解

## 作者：yewanxingkong (赞：4)

题意很简单，**就是给一个树换一个根节点。**

这样理解起来可能有点难受，那么再换一种说法：**给你一个 $n$ 个节点 $n-1$ 条边的无向连通图，让你以一个节点为根节点建树。**

这样就很简单了，深搜建树吗。

告诉你每个节点的父亲，其实就是这两个节点有一条边，存边后就可以愉快的深搜建树了。

具体细节可以看我代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<string>
#include<vector>
using namespace std;
int n,a,b,chu[100000];
vector<int>cun[100000];
inline void dfs(int xu,int fa){
	chu[xu]=fa;
	for(int i=0;i<cun[xu].size();++i)
		if(cun[xu][i]!=fa)dfs(cun[xu][i],xu);
}
inline int read(){
	int date=0,w=1;char c=0;
	while(!isdigit(c)){if(c=='-')w=-1;c=getchar();}
	while(isdigit(c)){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int main(){
	n=read();
	a=read();
	b=read();
	for(int i=1;i<=n;i++){
		if(i==a)continue;
		int c=read();
		cun[i].push_back(c);
		cun[c].push_back(i);
	}
	dfs(b,0);
	for(int i=1;i<=n;i++){
		if(i==b)continue;
		printf("%d ",chu[i]);
	}
	return 0;
} 
```


---

## 作者：Honor誉 (赞：3)

这道题其实是一道非常基础的图论题。

我们可以用vector进行存边，然后进行深搜遍历，用一个vis数组去存它是否被遍历过，并记录他的父亲节点。

上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[100001];
vector<int> a[100001];
int n,m,k,x,fa[100001];
void dfs(int u)//遍历
{
    for(int i=0;i<a[u].size();i++)
    {
        int v=a[u][i];
        if(!vis[v])
        {
            vis[v]=1;
            fa[v]=u;
            dfs(v);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<n;i++)
    {
        scanf("%d",&x);
        if(i>=m)//存边
        {
            a[i+1].push_back(x);
            a[x].push_back(i+1);
        }else{
            a[i].push_back(x);
            a[x].push_back(i);
        }
    }
    dfs(k);//遍历
    vis[k]=1;
    for(int i=1;i<=n;i++)
    {
        if(i!=k)
        {
            printf("%d ",fa[i]);//输出
        }
    }
    return 0;
}
```

---

## 作者：Reobrok_Kk (赞：3)

这题是一道很基础图论题。

### 题目大意

给一颗以 $root1$ 为根 $n$ 个结点的树，求把它转化成以 $root2$ 为根的树后，每个点的父结点。

### 思路

输入这棵树的时候，把每一条树边都建成双向边，使其变成一个图，然后从 $root2$ 开始遍历图，每次遍历都记录这个点的父亲结点。

输入的是每个点的父亲结点，但是 $root1$ 是没有父亲结点的，所以要特判掉。

输出也是，$root2$ 没有父亲结点，也是特判掉。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x; bool flag = 1; char c = getchar();
    while (!isalnum(c)) {if (c == '-') flag = 0; c = getchar();}
    x = c - '0'; c = getchar();
    while (isalnum(c)) {x = (x << 3) + (x << 1) + c - '0'; c = getchar();}
    if (flag) return x; else return ~(x - 1);
}
inlin void write(int x) {
    if (x < 0) {putchar('-'); x = ~(x - 1);}
    int stk[30], top = 0;
    while (x) {stk[++top] = x % 10; x /= 10;}
    while (top) {putchar(stk[top--] ^ 48);}
    putchar(' ');
    return ;
}
//第一次压行写快读快输，有点不习惯
const int N = 5e4 + 5;
const int M = 1e5 + 5;
struct Edge{
    int to, front, nxt;
}edge[M]; //链式前向星存图
int fa[N], head[N], tot; //fa[]来记录答案
void add(int x, int y) { //这里是建边
    edge[++tot] = (Edge){y, x, head[x]}; //结构体赋值（注意要按结构体变量定义的顺序写）
    head[x] = tot; //更新head[]
}
void dfs(int x, int f) { //遍历
    fa[x] = f; //记录父亲结点
    for (int i = head[x]; i; i = edge[i].nxt) { //往下遍历
        if (edge[i].y == f) continue; //跳过父结点
        dfs(edge[i].y, x);
    }
}
int main() {
    int n, root1, root2;
    n = read(), root1 = read(), root2 = read();
    for (int i = 1; i <= n; ++i) {
        if (i == root1) continue; //root1没有父亲结点
        int y = read(); //输入i的父亲结点
        add(i, y);
        add(y, i);
        //双向建边
    }
    dfs(root2, 0); //从root2开始遍历
    for (int i = 1; i <= n; ++i) {
        if (i == root2) continue; //跳过root2
        write(fa[i]); //输出答案
    }
    puts("");
}
```



---

## 作者：叶枫 (赞：2)

~~一道十分基础的图论题~~

思路很简单：
- 先将给出的父亲节点存下来。
- 从$r2$开始$dfs$到$r1$，将这条路径上所有点的父节点改一下。

没了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<vector>
#define re register
#define ll long long
#define maxn 50010
#define inf 2147483647
#define mod 998244353
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int ans[maxn];
int n,r1,r2;
inline void dfs(int x,int last){
	if(x==r1) {ans[x]=last; return;}
	dfs(ans[x],x);
	ans[x]=last;
}
signed main(){
	n=read(); r1=read(); r2=read();
	for(int i=1;i<=n;i++){
		if(i==r1) {ans[i]=r1;wihle(1) continue;}
		ans[i]=read();
	}
	dfs(r2,r2);
	for(int i=1;i<=n;i++){
		if(i==r2) continue;
		printf("%d ",ans[i]);
	}
	return 0;
}
```
$\color{ForestGreen}{}\sout{\text{粘贴代码会给你意想不到的惊喜}}$

---

## 作者：皮卡丘最萌 (赞：2)

这道题目最好的理解方式就是**按题意模拟**一遍。

例如这个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/n6qehjhe.png)

此时$f_1=3,f_2=3,f_3=0,f_4=1,f_5=1$。**(默认根的父亲为$0$)**

我们如果把根从$3$换为$4$，就是这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/l0iyzgqs.png)

此时$f_1=4,f_2=3,f_3=1,f_4=0,f_5=1$。

我们可以发现$f_1,f_3,f_4$的值发生了变化。

仔细观察可以看出$f_1-f_3-f_4$就是**从原根到新根的路径**。

所以我们只需要遍历**从原根到新根的路径**，并把这条路径上**所有的点的父亲设为自己的儿子**。

代码：
```pascal
var n,x,y,i,p:longint;
f:array[0..100001] of longint;
procedure huan(p,q:longint);
begin
if p=x then
  begin
  f[p]:=q;
  exit;
  end;               //如果遍历完了,就退出
huan(f[p],p);        //继续遍历
f[p]:=q;             //把自己的父亲设为自己的儿子
end;

begin
readln(n,x,y);
for i:=1 to n do
  if i<>x then
    begin
    read(p); f[i]:=p;
    end;                    //读入每个点的父亲
huan(y,0);                       //换根操作
for i:=1 to n do
  if i<>y then write(f[i],' ');  //输出每个点的父亲
end.
```


---

## 作者：Na2PtCl6 (赞：1)

## 分析题目
此题主要考的是图的存储。

### 存图
翻译已经讲得很明白了——给一棵树换根，换根意味着某些点的“辈分”关系会改变。因此，我们在存储树时可以双向加边，这样就只记录了这棵树节点的联通情况。

### 跑图
我们从新的根节点出发，先把当前节点标记一下，以便确定父子关系，然后遍历当前节点能到达的节点，进行递归。

## 代码实现
```cpp
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=50004;
int n,r1,r2,t,f,father[maxn];
vector < int > con[maxn];

void dfs(int node){
	for(int i=0;i<con[node].size();i++){
		int s=con[node][i];
		//如果不是返回根节点就继续往下遍历 
		if(s!=father[node]){
			father[s]=node;
			dfs(s);
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&r1,&r2);
	for(int i=1;i<=n;i++)
		if(i!=r1){   
			scanf("%d",&t);
			con[t].push_back(i);
			con[i].push_back(t);
		}
	dfs(r2);
	for(int i=1;i<=n;i++)
		if(i!=r2)
			printf("%d ",father[i]);
	return 0;
}
```

---

## 作者：fls233666 (赞：1)

首先我们发现，换掉树根，**树上的边是不变的**。

那么，我们完全可以根据原来的树根和每个节点的父节点，把树构造出来。

然后，我们以新的根节点为起点，做一遍搜索，就做完了。

再看一遍数据范围： $2 \le n \le 5 \times 10^4$ 搜索能过。

下面是本人的代码，采用广度优先搜索算法实现。

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;
const int mxn = 5e4+4;
int nxt[mxn*2],v[mxn*2],lst[mxn],que[mxn],newfa[mxn];
int n,tot,rt1,rt2,hd,tl;
bool fw[mxn];  //标记是否有被访问过
  
inline void add(int a,int b){
	tot++;
	v[tot]=b;
	nxt[tot]=lst[a];
	lst[a]=tot;
}  //边链表加边函数
  
int main(){
	scanf("%d%d%d",&n,&rt1,&rt2);
  //读入节点数，旧根，新根
  
	for(rgt fa,i=1;i<=n;i++){
		if(i==rt1)
			continue;  //跳过根节点
                             
		scanf("%d",&fa);  //读入每个节点的父节点
		add(fa,i);  //加边
		add(i,fa);  //无向边加两次
	}
                             
	tl++;
	que[tl]=rt2;   //新根入队列
	fw[rt2]=true;  //标记
                             
	while(hd!=tl){
		hd++;
		for(rgt to,i=lst[que[hd]];i;i=nxt[i]){
			to=v[i];
			if(fw[to])
				continue;
			fw[to]=true;  //找到没有标记的节点
                             
			newfa[to]=que[hd];  //设置新的父节点
			tl++;
			que[tl]=to;  //入队
		}
	}
                             
	for(rgt i=1;i<=n;i++){
		if(i==rt2)
			continue;  //跳过新的根节点
		printf("%d ",newfa[i]);  //输出
	}
  
	return 0;
}
```


---

## 作者：partychicken (赞：1)

### 很基础的图论题
先建图 ，然后跑一遍dfs
具体看代码吧
```
#include<bits/stdc++.h>

using namespace std;

struct Edge
{
	int to,next;
}e[100001];

int head[50001],cnt;

void addedge(int u,int v)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}

int ans[50001];

int dfs(int x,int fa)
{
	ans[x]=fa;
	for(int i=head[x];i;i=e[i].next)
	{
		int vv=e[i].to;
		if(vv==fa)
		{
			dfs(vv,x);
		}
	}
}

int main()
{
	int n,r1,r2;
	cin>>n>>r1>>r2;
	for(int i=1;i<=n;i++)
	{
		int temp;
		if(i==r1) continue;
		cin>>temp;
		addedge(i,temp);
		addedge(temp,i);
	}
	dfs(r2,0);
	for(int i=1;i<=n;i++)
	{
		if(i!=r2)
		cout<<ans[i]<<" ";
	}
    while（1）
	return 0;
}
```
提示：贸然抄题解会死的很惨

---

## 作者：xgwpp6710 (赞：0)

感谢@Ninelife_cat @orz_MSQ 对我这篇题解的帮助。

看到给树换根，第一个想到的是 Splay。~~然而我 Splay 只会写挂~~

其实这题没那么复杂，直接一个 dfs 遍历就行了，从新根开始，每搜到一个点把它的父亲节点标记为上一个搜到的节点就行了。

然后因为树的边数恰等于点数 $-1$，而每一条边只会被搜到一次，因此不会 TLE。

```cpp
#include<bits/stdc++.h>
int n,f[500009],r1,r2,fa[500009],cnt;
int j;
using namespace std;
vector<int> link[500009];
void dfs(int pos,int pre)
{
	fa[pos]=pre;
	for(j=0;j<link[pos].size();j++)
		if(link[pos][j]!=pre) dfs(link[pos][j],pos);
}
int main()
{
	cin>>n>>r1>>r2;
	for(int i=1;i<=n;i++)
	{
		if(i==r1) continue;
		else {cin>>f[i];link[i].push_back(f[i]);link[f[i]].push_back(i);}
	}
	dfs(r2,0);
	for(int i=1;i<=n;i++) if(!fa[i]) fa[i]=r2;//防止有点没搜到
	for(int i=1;i<=n;i++) if(i!=r2) cout<<fa[i]<<" ";
	return 0;
}
```

---

## 作者：naroanah (赞：0)

### 简述题意：
给出一棵树，对它进行换根，并求出换根后每个节点的父亲（除根节点外）。
### 思路：
为了后续重建，需要无向图存边。然后dfs遍历每个节点，记录下它们的父亲（**要记录是否访问过**）。
### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, od, nw;
vector<int> edge[50010];
bool vis[50010];
int ans[50010];

void dfs(int x) {
	vis[x] = 1; 
	for (int i = 0; i < edge[x].size(); i++) {
		if (vis[edge[x][i]] == 1) //判断是否访问过
			continue;
		ans[edge[x][i]] = x; //记录答案
		vis[edge[x][i]] = 1; //标记
		dfs(edge[x][i]);
	}
}

int main() {
	scanf("%d%d%d", &n, &od, &nw);
	for (int i = 1; i <= n; i++) {
		if (i == od)
			continue;
		int t;
		scanf("%d", &t);
		edge[i].push_back(t);
		edge[t].push_back(i); //双向建边
	}
	dfs(nw);
	for (int i = 1; i <= n; i++) {
		if (i == nw)
			continue;
		printf("%d ", ans[i]);
	}
	return 0;

}
```


---

## 作者：王炸拆开打 (赞：0)

这个题还是~~比较好想~~的，主要在于对树的理解
# 核心思路：搜索
###          重要思想：树的建立




------------
题中说到边数为$(n-1)$,根据树的特性，得出此图是一棵树，也就是说我们可以用各种**树的思路**在上面~~为所欲为~~了

（但是也不要被树的思想固化哦）


------------


首先，通过输入和邻接表将各个节点建立关系

又因为**树的搜索遍历是类似于线性的特点**，直接进行深搜即可

从新的根节点开始搜索，让先搜到的点变为下个节点的爹

根据这个，就可以得到一棵新的树了（可以手模试试）

这样就$OK$了

下为代码，多多指教：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int newf,oldf,n;
int fa[50001],vis[50001];
vector<int> v[50001];
void dfs(int x){
	for(int i=0;i<v[x].size();i++){
		int t=v[x][i];
		if(t==fa[x]) continue;//防止又找回他爹 
		fa[t]=x;
		dfs(t);
	}
}
int main(){
	scanf("%d%d%d",&n,&oldf,&newf);
	int x;
	for(int i=1;i<=n;i++){
		if(i==oldf) continue;
		scanf("%d",&x);
		v[i].push_back(x);
		v[x].push_back(i);
	}
	dfs(newf);//开始搜索建树 
	for(int i=1;i<=n;i++){
		if(i!=newf) printf("%d ",fa[i]);
	}
	return 0;	
}
```


---

