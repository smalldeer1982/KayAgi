# [eJOI 2020] Fountain (Day1)

## 题目描述

大家都知道喷泉吧？现在有一个喷泉由 $N$ 个圆盘组成，从上到下以此编号为 $1 \sim N$，第 $i$ 个喷泉的直径为 $D_i$，容量为 $C_i$，当一个圆盘里的水大于了这个圆盘的容量，那么水就会溢出往下流，直到流入半径大于这个圆盘的圆盘里。如果下面没有满足要求的圆盘，水就会流到喷泉下的水池里。

现在给定 $Q$ 组询问，每一组询问这么描述：

- 向第 $R_i$ 个圆盘里倒入 $V_i$ 的水，求水最后会流到哪一个圆盘停止。

如果最终流入了水池里，那么输出 $0$。

**注意，每个询问互不影响。**

## 说明/提示

#### 样例 1 解释

前两个询问的解释如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/64e7acuq.png)

因为每个询问互不影响，对于第三个询问，第 $5$ 个圆盘里的水不会溢出。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（30 pts）：$N \le 1000$，$Q \le 2000$。
- Subtask 2（30 pts）：$D_i$ 为严格单调递增序列。
- Subtask 3（40 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $2 \le N \le 10^5$。
- $1 \le Q \le 2 \times 10^5$。
- $1 \le C_i \le 1000$。
- $1 \le D_i,V_i \le 10^9$。
- $ 1\le R_i \le N$。

#### 说明

翻译自 [eJOI 2020 Day1 A Fountain](https://ejoi2020.ge/static/assets/Day1/Problems/Fountain.pdf)。

## 样例 #1

### 输入

```
6 5
4 10
6 8
3 5
4 14
10 9
4 20
1 25
6 30
5 8
3 13
2 8```

### 输出

```
5
0
5
4
2```

# 题解

## 作者：Z1qqurat (赞：101)

嗯，这道题虽然只是绿的，但个人认为其中有重要意义。由于这道题涉及到的算法和思路比较多，我会采用循序渐进的方式来写。

### Part 1 基础做法

哈，先来理解一下题意吧。

个人是建议把题目里面滴图倒过来看看！

![Fountain](https://cdn.luogu.com.cn/upload/image_hosting/bjwxlxll.png)

可以这么理解，如果水到了一个盘子里面，会溢出到**往右第一个直径比所在盘子要大的盘子**里面。

“后面第一个比自己大的元素”，这不就是```单调栈```的用法吗，所以我们可以自然地想到单调栈所有盘子的 $d_i$ （直径）。

于是可以写出下面代码咯：

```cpp
void find_max(){
	for(ri i=1;i<=n;i++){
		while(stk.empty()==0&&d[i]>d[stk.top()]){
			b[stk.top()]=i;//记录每个盘子往右第一个直径比它大的盘子编号。
			stk.pop();
		}
		stk.push(i);
	}
	while(stk.empty()==0){
		b[stk.top()]=0;//0代表水池。
		stk.pop();
	}
}
```

那有了这个，我们再想想，接下来怎么做呢？就举一个浅显的例子，现在我们确定了一个盘子 $r$ （编号），里面装了 $v$ 的水，我们只需要不停地找它的下一个盘子，直到水不会再溢出就可以找到最后的盘子的编号了，这个过程可以用```while```循环实现：

```cpp
for(ri i=1;i<=q;i++){
	scanf("%d%d",&r,&v);
	int tmp=r;
	while(tmp!=0){	
		v-=c[tmp];
		if(v<=0)break;
		tmp=b[tmp];
	}
	printf("%d\n",tmp);
}
```
那我们这么做，可以拿到[30分](https://www.luogu.com.cn/record/75830263)（TLE），而这题在普及组中也大概有个3~4题的难度，大概会有个50分左右，也是不错的分了！

### Part2 升级版正解

单调栈的部分肯定没得改滴了，现在我们就来想想如何优化。

有单调性，可以二分？但是考虑到如果要二分，就需要任意一段距离可以承受的水量，这个也不好算，和区间内每一个盘子的直径容积都有关系，直接放弃。

既然想到了二分，其实可以很容易想到倍增。你从某个盘子开始，照理来说是会跳到下一个可以跳滴盘子，但是如果想要优化时间，可以多跳！对，这就是倍增，跳 $2$ 的幂次。于是我们可以用```ST表```维护 $nxt[i][j]$ （从盘子 $i$ 往后跳 $2^j$ 步到达的盘子编号）和 $sum[i][j]$ 区间总水量。

可以写出下面的处理代码：

```cpp
void pre_rmq(){
	for(ri j=1;(1<<j)<=n;j++){
		for(ri i=1;i+(1<<j)<=n;i++){
			nxt[i][j]=nxt[nxt[i][j-1]][j-1];
			sum[i][j]=sum[i][j-1]+sum[nxt[i][j-1]][j-1];
		}
	}
}

int query(int r,int val){
	if(c[r]>=val){
		return r;
	}
	val-=c[r];
	for(ri i=18;i>=0;i--){
		if(nxt[r][i]!=0&&val>sum[r][i]){
			val-=sum[r][i];
			r=nxt[r][i];
		}
	}
	return nxt[r][0];
}
```

于是这道题差不多就解决了！

### Part 3 完整代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
const int MAXN=1e5+10;
int n,q,d[MAXN],c[MAXN],r,v,b[MAXN],nxt[MAXN][20],sum[MAXN][20];
stack <int> stk;

void find_max(){
	for(ri i=1;i<=n;i++){
		while(stk.empty()==0&&d[i]>d[stk.top()]){
			nxt[stk.top()][0]=i;
			sum[stk.top()][0]=c[i];
			stk.pop();
		}
		stk.push(i);
	}
	while(stk.empty()==0){
		nxt[stk.top()][0]=0;
		stk.pop();
	}
}

void pre_rmq(){
	for(ri j=1;(1<<j)<=n;j++){
		for(ri i=1;i+(1<<j)<=n;i++){
			nxt[i][j]=nxt[nxt[i][j-1]][j-1];
			sum[i][j]=sum[i][j-1]+sum[nxt[i][j-1]][j-1];
		}
	}
}

int query(int r,int val){
	if(c[r]>=val){
		return r;
	}
	val-=c[r];
	for(ri i=18;i>=0;i--){
		if(nxt[r][i]!=0&&val>sum[r][i]){
			val-=sum[r][i];
			r=nxt[r][i];
		}
	}
	return nxt[r][0];
}

int main() {
	scanf("%d%d",&n,&q);
	for(ri i=1;i<=n;i++)scanf("%d%d",&d[i],&c[i]);
	memset(sum,0x3f,sizeof(sum));
	find_max();
	pre_rmq();
	for(ri i=1;i<=q;i++){
		scanf("%d%d",&r,&v);
		printf("%d\n",query(r,v));
	}
	return 0;
}
```

总结一下，做题的思路要讲究循序渐进，慢慢来，不要轻视简单基础的算法和思路！

---

## 作者：Fido_Puppy (赞：100)

## $\mathcal{Question}$

[P7167 [eJOI 2020 Day1] Fountain](https://www.luogu.com.cn/problem/P7167)

## $\mathcal{Solution}$

设水池的编号为 n+1，直径和容量设为无限。

我们可以利用单调栈来求出每一个盘子之后的第一个直径比它大的盘子。

```cpp
d[n+1]=inf; c[n+1]=inf;
s.push(1);
for(LL i=2;i<=n+1;i++) {
	while (!s.empty()&&d[i]>d[s.top()]) {
		l[s.top()]=i; s.pop();
	}
	s.push(i);
} // l[i] 表示第 i 个盘子之后的第一个直径比它大的盘子的编号
```

接着，我们考虑建一棵树。

以样例数据为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/64e7acuq.png)

建出来的树就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/solr19sz.png)

相信你已经发现了，从子节点到父亲节点就是水流的方向。

建树的代码其实很简单，这时就用到我们上面求出来的 l 数组了。

```cpp
for(LL i=1;i<=n;i++) add(l[i],i); // add 表示连边操作。
// n+1 号节点为根，不需要枚举
```

然后，我们维护两个数组：

+ f [ i ] [ j ] 表示从第 i 个节点向上走 $2^j$ 步所到的节点编号。

+ g [ i ] [ j ] 表示从 i 节点到 f [ i ] [ j ] 节点的所有节点的容量之和（不包括 i 节点）。

我们只需要遍历一遍这棵树就可以维护这两个数组。

这里就用到了倍增的思想，与倍增求 LCA 差不多。

+ [倍增求 LCA 传送门](https://www.cnblogs.com/lbssxz/p/11114819.html)

顺便的，链式前向星不会的戳下面。

+ [链式前向星传送门](https://www.cnblogs.com/lbssxz/p/10764448.html)

```cpp
LL f[N][21],g[N][21],dep[N]; // dep[i] 表示 i 节点的深度
inline void dfs(LL u,LL fa) {
	dep[u]=dep[fa]+1;
	f[u][0]=fa; g[u][0]=c[fa];
	for(LL i=1;(1<<i)<=dep[u];i++) f[u][i]=f[f[u][i-1]][i-1],g[u][i]=g[f[u][i-1]][i-1]+g[u][i-1]; // 倍增思想
	for(LL i=head[u];i;i=edge[i].next) {
		LL v=edge[i].to;
		dfs(v,u);
	}
}
```

查询的时候跟倍增求 LCA 的查询也没太大的区别。

```cpp
for(LL i=1;i<=q;i++) {
	LL r,v;
	cin>>r>>v;
	if (c[r]>=v) { //特判
		cout<<r<<endl;
		continue;
	}
	v-=c[r]; /*先把 r 盘子中的水装满 */ LL x=r; LL ans=0;
	for(LL i=20;i>=0;i--) {
		if (g[x][i]<=v&&(1<<i)<=dep[x]) {
			v-=g[x][i]; x=f[x][i];
		}
		if (v==0) ans=x; // 特判
	}
	if (ans==0) ans=f[x][0];
	if (ans==n+1) cout<<0<<endl;else cout<<ans<<endl;
}
```

总的时间复杂度 $\mathcal{O(n\ log\ n)}$。

## $\mathcal{Code}$

```cpp
%:include"bits/stdc++.h"
using namespace std;
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define N (LL)(1e5+10)
typedef long long LL;
const LL inf=1e16;
LL n,q,d[N],c[N];
stack<LL>s;
LL l[N],head[N],tot=0;
struct node {
	LL next,to;
}edge[N];
inline void add(LL x,LL y) {
	edge[++tot].to=y;
	edge[tot].next=head[x];
	head[x]=tot;
}
LL f[N][21],g[N][21],dep[N];
inline void dfs(LL u,LL fa) {
	dep[u]=dep[fa]+1;
	f[u][0]=fa; g[u][0]=c[fa];
	for(LL i=1;(1<<i)<=dep[u];i++) f[u][i]=f[f[u][i-1]][i-1],g[u][i]=g[f[u][i-1]][i-1]+g[u][i-1];
	for(LL i=head[u];i;i=edge[i].next) {
		LL v=edge[i].to;
		dfs(v,u);
	}
}
signed main() {
	IOS;
	cin>>n>>q;
	for(LL i=1;i<=n;i++) cin>>d[i]>>c[i];
	d[n+1]=inf; c[n+1]=inf;
	s.push(1);
	for(LL i=2;i<=n+1;i++) {
		while (!s.empty()&&d[i]>d[s.top()]) {
			l[s.top()]=i; s.pop();
		}
		s.push(i);
	}
	for(LL i=1;i<=n;i++) add(l[i],i);
	dfs(n+1,0);
	for(LL i=1;i<=q;i++) {
		LL r,v;
		cin>>r>>v;
		if (c[r]>=v) {
			cout<<r<<endl;
			continue;
		}
		v-=c[r]; LL x=r; LL ans=0;
		for(LL i=20;i>=0;i--) {
			if (g[x][i]<=v&&(1<<i)<=dep[x]) {
				v-=g[x][i]; x=f[x][i];
			}
			if (v==0) ans=x;
		}
		if (ans==0) ans=f[x][0];
		if (ans==n+1) cout<<0<<endl;else cout<<ans<<endl;
	}
	return 0;
}
```
完结撒花！ **^.^**

---

## 作者：Alex_Wei (赞：57)

[题目传送门](https://www.luogu.com.cn/problem/P7167)。

> 题意简述：给定 $N$ 个直径为 $D_i$，容量为 $C_i$ 的**从上到下**的空圆盘。一个圆盘溢出的水会流到下方比它大的圆盘中。$Q$ 次询问如果往第 $R$ 个圆盘倒 $V$ 体积的水，水最后会流到哪个圆盘，如果流到底则输出 $0$，每个询问独立。

> $N,Q\leq 10^5$。

---

首先考虑暴力：对于每一个询问，直接模拟，若水溢出，则枚举找出在当前圆盘 $i$ 下方最近的比当前圆盘大的圆盘 $j$，即从 $i+1$ 枚举出最小的 $j$ 使得 $i<j$ 且 $D_i<D_j$，将当前水量减去当前圆盘的容量 $C_i$ 流进下一个圆盘 $j$。

可以单调栈预处理出在每个圆盘下方最近的比它大的圆盘，然后倍增优化模拟即可。时间复杂度 $\mathcal{O}((n+q)\log n)$。

```cpp
int main(){
	n=read(),q=read(),lg=log2(n);
	for(int i=1;i<=n;i++)d[i]=read(),c[i]=read();
	for(int i=n;i;i--){
		while(top&&d[i]>=d[stc[top]])top--;
		to[i][0]=stc[top],f[i][0]=c[i],stc[++top]=i;
	} for(int j=1;j<=lg+1;j++)
		for(int i=1;i<=n;i++)
			to[i][j]=to[to[i][j-1]][j-1],f[i][j]=f[i][j-1]+f[to[i][j-1]][j-1];
	for(int i=1;i<=q;i++){
		int p=read(),r=read();
		for(int j=lg+1;~j;j--)if(r>f[p][j])r-=f[p][j],p=to[p][j];
		print(p),pc('\n');
	}
	return flush(),0;
}
```

---

## 作者：Dreamweaver (赞：23)

感谢@[douzi](/space/show?uid=278697) 大佬的 hack 数据，本题解已修正：

问题在倍增数组初始化上，当一个盘只能流到水池中时，$u$ 数组应为 $\infty$，而不是 $0$。


------------
# Preface



单调栈&倍增好题。
# Analysis
先来看一下题目描述：

------------
“当一个圆盘里的水大于了这个圆盘的容量，那么水就会溢出**往下流**，直到流入半径**大于**这个圆盘的圆盘里。”

------------

“往下流”“大于”这就很像单调栈了。

再来看样例解释里的图，我把它旋转了一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/we4n2xas.png)

向 $1$ 号圆盘中灌水，水流到 $2$ 号和 $5$ 号圆盘。

我们发现：从下往上，能接收到水的圆盘半径**严格单调递减**。

这恰恰可以用单调栈维护。

但只有单调栈是不够的，单调栈维护的过程是动态的，栈中的信息有时效性，在维护过程中我们需要记录下信息，然后在倍增的接续传递中推出全面的、静态的、便于回答询问的信息。

# Solution

开两个数组：$f[i][j]$ 表示从 $i$ 这个位置向下的第 $2^j$ 个圆盘是哪个，$u[i][j]$ 表示流满从 $i$ 这个位置向下的 $2^j$ 个圆盘（不包括 $i$）需要多少体积的水。

## 1. 单调栈求出 $f[i][0]$

维护一个**严格单调递减**的单调栈，从后向前（从下向上）扫数组，若新加入的圆盘的半径比栈顶圆盘半径大就弹出栈顶。
```cpp
	for(re int i=n;i>=1;--i)
	{
		while(size&&a[s[size]].d<=a[i].d)	size--;//不满足条件的弹出
		f[i][0]=s[size];//记录f[i][0]
		s[++size]=i;//入栈
	}	
```

## 2. 倍增出完整的 $f$ 数组和 $u$ 数组

```cpp
	for(re int i=1;i<=23;++i)
		for(re int j=1;j<=n;++j)
			f[j][i]=f[f[j][i-1]][i-1];//倍增f数组
   for(re int i=1;i<=n;++i)	
		u[i][0]=a[f[i][0]].c;//根据定义初始化
   for(re int i=1;i<=n;++i)
		if(f[i][0]==0)	
			u[i][0]=inf; //初始化u数组 
	for(re int i=1;i<=23;++i)
		for(re int j=1;j<=n;++j)
			u[j][i]=u[j][i-1]+u[f[j][i-1]][i-1];//倍增u数组
```

## 3. 利用 $u$ 数组回答询问（仿照倍增 LCA）

```cpp
		int r=read(),v=read();
		if(v<=a[r].c)
		{
			cout<<r<<'\n';
			continue;
		}//如果流不到其他盘就直接输出
		v-=a[r].c;//要减掉当前圆盘的容量，结合u数组的定义，想一想为什么
		for(re int i=23;i>=0;--i)
			if(u[r][i]<=v)	
				v-=u[r][i],r=f[r][i];
		if(v)	r=f[r][0];//如果还有剩余就会流到下面一个
		cout<<r<<'\n';
```

复杂度：单调栈 $O(N)$，倍增 $O(N\log N)$，回答询问 $O(Q\log N)$，总复杂度 $O((N+Q)\log N)$。

# Code 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define maxn 100010
#define inf 0x7f7f7f7f
#define int long long
#define Orz cout<<"stO %王队% Orz"<'\n';
int n,q;
struct node
{
	int d,c;
}a[maxn];
int s[maxn],size;
int f[maxn][25],u[maxn][25];
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0'; ch=getchar();}
    return x*f;
}
signed main()
{
	cin>>n>>q;
	for(re int i=1;i<=n;++i)
		a[i].d=read(),a[i].c=read();//读入数据
	for(re int i=n;i>=1;--i)
	{
		while(size&&a[s[size]].d<=a[i].d)	size--;
		f[i][0]=s[size];
		s[++size]=i;
	}	//单调栈
	for(re int i=1;i<=23;++i)
		for(re int j=1;j<=n;++j)
			f[j][i]=f[f[j][i-1]][i-1];
	for(re int i=1;i<=n;++i)	
		u[i][0]=a[f[i][0]].c;
	for(re int i=1;i<=n;++i)
		if(f[i][0]==0)	
			u[i][0]=inf; //初始化u数组 
	for(re int i=1;i<=23;++i)
		for(re int j=1;j<=n;++j)
			u[j][i]=u[j][i-1]+u[f[j][i-1]][i-1];//倍增
	while(q--)
	{
		int r=read(),v=read();
		if(v<=a[r].c)
		{
			cout<<r<<'\n';
			continue;
		}
		v-=a[r].c;
		for(re int i=23;i>=0;--i)
			if(u[r][i]<=v)	
				v-=u[r][i],r=f[r][i];
		if(v)	r=f[r][0];
		cout<<r<<'\n';
	}//回答询问
	return 0;
}




```


---

## 作者：StupidSeven (赞：6)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/P7167)

## Analysis
可以发现，如果一个圆盘的容积小于现在的水，那么多出来的水会流到它下面的第一个直径比它大的圆盘，那么我们就需要预处理出每一个圆盘之后第一个直径比它大的圆盘的编号，可以用单调栈 $ O(n)$ 求出。

我们把每个圆盘和第一个直径比它大的圆盘之间连边，发现是一棵树，我们要求的就是找到最老的一个祖先，使这个点到这个祖先路径上圆盘的总容积不大于水量，可以使用树上倍增解决。先预处理出每个子节点到祖先节点的路径上所有节点的容积和，可以通过遍历整棵树解决，然后倍增，每次跳祖先，只要当前总容积小于水量就往上跳，直到不能跳，那么这个节点就是答案。

还有一些具体的细节，具体见代码。
## Code
```cpp
#include<cmath>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int M=1e6+10;
const int N=30;
const int inf=0x3f3f3f3f;
inline int Read(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;    
}
vector<int> Edge[M];
int n,m,u,val,d[M],w[M],Max[M];
int stack[M],top;
int fat[M][N],dep[M];
int sum[M];
void addEdge(int u,int v){
    Edge[u].push_back(v);
    return;
}
void Dfs(int u,int fath){
    fat[u][0]=fath;
    dep[u]=dep[fath]+1;
    for(int i=1;fat[u][i-1];i++)
        fat[u][i]=fat[fat[u][i-1]][i-1];
    for(auto v:Edge[u]){
        sum[v]=sum[u]+w[v];
        Dfs(v,u);
    }
    return;
}
int Query(int u,int val){
    for(int i=21;i>=0;i--){
        if(sum[u]-sum[fat[u][i]]<val){
            val-=sum[u]-sum[fat[u][i]];
            u=fat[u][i];
        }    
    }
    return u;
}
signed main(void){
    n=Read();m=Read();
    for(int i=1;i<=n;i++){
        d[i]=Read();
        w[i]=Read();
    }
    d[n+1]=inf;
    stack[++top]=1;
    for(int i=2;i<=n+1;i++){
        while(top&&d[i]>d[stack[top]]){
            Max[stack[top]]=i;
            top--;
        }
        stack[++top]=i;
    }
    for(int i=1;i<=n;i++)
        addEdge(Max[i]==n+1?0LL:Max[i],i);
    Dfs(0,0);
    for(int i=1;i<=m;i++){
        u=Read();val=Read();
        printf("%lld\n",Query(u,val));
    }
    return 0;
}
```

---

## 作者：Feyn (赞：6)

### 先看算法标签，倍增？
### ~~想起了倍增求LCA~~
上思路：

- ### 第一步，求出每一个盘子的水流出来之后会最先流到哪里
单纯枚举复杂度过高，用单调栈优化即可，问题就转化成了求在某个元素之前的离这个元素最近且比它大的元素的位置。

w[i]表示从下往上第i个盘子的直径。
```cpp
int next[N][M];
struct node{int number,data;};
stack<node>sta;
void init_next(){
	sta.push((node){0,1e18});
	for(int i=1;i<=m;i++){
		while(!sta.empty()&&sta.top().data<=w[i])sta.pop();
		next[i][0]=sta.top().number;
		sta.push((node){i,w[i]});
	}
}
```

- ### 第二步，利用倍增的思想求出从下往上第j个盘子往下流，流过$2^i$个盘子之后会停留在哪里。

递推即可。答案储存在 $next[j][i]$ 中，i、j含义同上。

```cpp
for(int i=1;i<=size;i++){
	for(int j=1;j<=m;j++){
		next[j][i]=next[next[j][i-1]][i-1];
	}
}
```

- ### 第三步，还是利用倍增的思想，求出从下往上第j个盘子流过$2^i$个盘子需要多少水。

```cpp
int need[N][M];
void init_need(){
	for(int i=1;i<=m;i++)need[i][0]=c[i];
	for(int i=1;i<=size;i++){
		for(int j=1;j<=m;j++){
			need[j][i]=need[j][i-1]+need[next[j][i-1]][i-1];
		}
	}
}
```

- ### 第四步，对于每一个询问处理即可

```cpp
int now=0;
for(int i=size;i>=0;i--){
	if(now+need[wh][i]<th){
		now+=need[wh][i];
		wh=next[wh][i];
	}
}
```

### 完整代码：
- 由于输入的时候是从上往下一个一个盘子输入的，而本人习惯从下往上存储，所以在输入和询问的时候下标有一些小处理。
- $size$意思是最大的$size$使得$2^{size}\le m$。

```cpp
#include<cstdio>
#include<stack>
#define int long long
using namespace std;
const int N=100010;
const int M=25;

inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar(); }
    wh*=f;return;
}

int m,n,size,w[N],c[N];
 
int next[N][M];
struct node{int number,data;};
stack<node>sta;
void init_next(){
	sta.push((node){0,1e18});
	for(int i=1;i<=m;i++){
		while(!sta.empty()&&sta.top().data<=w[i])sta.pop();
		next[i][0]=sta.top().number;
		sta.push((node){i,w[i]});
	}
	while(!sta.empty())sta.pop();
	
	for(int i=1;i<=size;i++){
		for(int j=1;j<=m;j++){
			next[j][i]=next[next[j][i-1]][i-1];
		}
	}
}

int need[N][M];
void init_need(){
	for(int i=1;i<=m;i++)need[i][0]=c[i];
	for(int i=1;i<=size;i++){
		for(int j=1;j<=m;j++){
			need[j][i]=need[j][i-1]+need[next[j][i-1]][i-1];
		}
	}
}

signed main(){
	
	read(m);read(n);
	
	while((1<<size)-1<m)size++;size--;
	
	for(int i=1;i<=m;i++){
		read(w[m-i+1]);read(c[m-i+1]);
	}
	init_next();
	init_need();
	while(n--){
		int wh,th;
		read(wh);read(th);
		wh=m-wh+1;
		int now=0;
		for(int i=size;i>=0;i--){
			if(now+need[wh][i]<th){
				now+=need[wh][i];
				wh=next[wh][i];
			}
		}
		
		if(wh==0)printf("0\n");
		else printf("%lld\n",m-wh+1);
	}
	
	return 0;
} 
```
~~个人认为自己的码风还比较易懂……~~

---

## 作者：ysmlwudia (赞：5)

利用单调栈求出对每个圆盘求出第一个比该圆盘大的圆盘信息（编号和容量），为进行倍增操作的数组赋好初值，然后借助倍增找出一个圆盘与低于自己的圆盘之间的大小关系，最终根据每次输入的圆盘信息，从大到小依次减掉与该圆盘相关联的圆盘容量，详见代码
```cpp
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<map>
#include<string.h>
#include<queue>
#define ll long long
#define debug cout<<"FUCK"<<endl;
using namespace std;
const int logn=20;
int n,q,top,f[100005][logn+1],stk[100005],id[100005][logn+1],d[100005],c[100005];
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){//注意这里i越大，圆盘越低 
		cin>>d[i]>>c[i];		
	}
	for(int i=n;i>=1;i--){
		while(top&&d[stk[top]]<=d[i])top--;
		id[i][0]=stk[top];//保存第一个半径比自己大的圆盘编号 
		f[i][0]=c[i];//容量初值为自己的容量 
		//id为编号，f为容量,第id[i][j]个圆盘必定低于i且j越大越低 
		stk[++top]=i;
	}
	for(int j=1;j<=logn;j++){//倍增找出半径大于第i个圆盘的圆盘中第2^j大的（j越大,第id[i][j]的半径越大）,并保存其编号 
		for(int i=1;i<=n;i++){
			id[i][j]=id[id[i][j-1]][j-1],f[i][j]=f[i][j-1]+f[id[i][j-1]][j-1];
		}
	}
	while(q--){
		int ri,vi;
		cin>>ri>>vi;
		for(int i=20;i>=0;i--){//根据倍增信息，从最低、半径最大的圆盘开始从下往上做，依次递减 
			if(vi>f[ri][i])vi-=f[ri][i],ri=id[ri][i]; //如果跳到头了，仍没有流完，id数组未赋值，ri会自己变成0 
		}
		cout<<ri<<endl;
	}
	return 0;
}

```


---

## 作者：xiezheyuan (赞：3)

## 简要题意

有一个喷泉，由 $n$ 个圆盘构成，自上而下第 $i$ 个圆盘直径为 $D_i$，容量为 $C_i$。第 $n$ 个圆盘下方是一个直径和容量均为 $+\infty$ 的水池。

有 $q$ 次询问，每次询问给出两个正整数 $R,V$，表示在第 $R$ 个圆盘倒入 $V$ 个单位的水。如果水溢出了圆盘，就会流到下方最近的直径大于这个圆盘的圆盘或水池，以此类推。输出水最远到达的圆盘编号，如果水到达了水池，输出 $0$。注意询问与询问之间相互独立。

$2 \leq n \leq 10^5,1 \leq q \leq 2 \times 10^5,1 \leq C_i \leq 10^3,1 \leq D_i,V \leq 10^9$

### 思路

怎么题解都是倍增呀，这里贡献一个常数较小的树链剖分做法。

首先我们将水池看成第 $n+1$ 个圆盘，然后考虑如何快速求出一个圆盘里的水如果溢出了会往哪个圆盘流（下文称这样的水流流经的所有层圆盘中，从下一层走向上一层的指针为 Next 指针）。这个过程可以用单调栈完成。其他题解写的很清楚了，就不重复了。

接下来我们有一个简单但十分重要的结论，Next 指针构成了一棵以 $n+1$ 为根的树。证明也很简单：水不能往上流，所以 Next 指针是没有环的；第 $n+1$ 个圆盘里的水是不会溢出的，所以它是没有入边的，因此它就是根。

然后我们考虑询问的意义。可以看成是从第 $R$ 个节点开始向上跳祖先，每跳到一个节点 $i$（包括第 $R$ 个节点本身）就将 $V$ 减去 $C_i$。问 $V$ 第一次小于等于 $0$ 是在哪一个节点。

这个过程暴力跳肯定会 T 飞，我们可以使用树链剖分来维护。

我们可以对于每一个节点，找到它到它所在重链的顶端所组成的这一条链。先看看这一段的 $C$ 和是不是大于等于 $V$。如果大于等于 $V$ 的话答案一定在这条链上，否则一定不在。然后可以枚举一遍这个重链上的每一个点来试一试。

这个方法仍然会 T 飞，因为重链长度可以到 $O(\frac{n}{\log n})$ 级别。所以单次时间复杂度仍然是 $O(n)$。

然后我们发现 $C_i\gt 0$，这样前缀和是单调不降的，我们可以预处理一个前缀和（树链剖分一般用线段树维护，这里可以看成无修改的线段树）。然后在这个前缀和上对应链的一段二分即可。由于树链剖分的特性，这一段在数组上是连续的。

单次询问时间复杂度取决于一条从一个节点到根节点的链上重链数量，也就是 $O(\log n)$。

## 代码

截至到 2023-07-07 20:23，这个没有过分卡常（快读快写不算过分卡常吧）的代码轻松拿到最优解第一名。

```cpp
#include <bits/stdc++.h>
#define int long long
#define INLINE(type_name) inline type_name __attribute__((always_inline))
using namespace std;

const int N = 1e6+5;
int n,q,nxt[N],stk[N],stop,siz[N],son[N],seg[N],top[N],rev[N],qzh[N];

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}

struct node{
	int d,c;
	node(){}
	node(int D,int C){
		d=D,c=C;
	}
} dishes[N];

struct edge{
	int nxt,to;
} g[N<<1];
int head[N],ec;

void add(int u,int v){
	g[++ec].nxt=head[u];
	g[ec].to=v;
	head[u]=ec;
}

void dfs1(int u){
	if(!u) return;
	siz[u]=1;
	for(int i=head[u];i;i=g[i].nxt){
		int v = g[i].to;
		dfs1(v);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u]=v;
	}
}

void dfs2(int u){
	if(!u) return;
	if(son[u]){
		seg[son[u]]=++seg[0];
		top[son[u]]=top[u];
		rev[seg[0]]=son[u];
		dfs2(son[u]);
	}
	for(int i=head[u];i;i=g[i].nxt){
		int v=g[i].to;
		if(top[v])continue;
		seg[v]=++seg[0];
		rev[seg[0]]=v;
		top[v]=v;
		dfs2(v);
	}
}

INLINE(int) Query(int l,int r){
	if(!r) r=l;
	return (qzh[r]-qzh[l-1]);
}

int query(int r,int v){
	int pt = r;
	while(pt){
		int v1 = v - Query(seg[top[pt]], seg[pt]);
		if(v1 <= 0){
			int l=seg[top[pt]],r=seg[pt],ans=0;
			while(l<=r){
				int mid = (l+r)>>1;
				if(Query(mid, seg[pt]) >= v){
					ans=mid;
					l=mid+1;
				}
				else r=mid-1;
			}
			if(!ans) ans=l;
			return rev[ans]==n?0:rev[ans];
		}
		v = v1;
		pt = nxt[top[pt]];
	}
	return -1;
}

signed main(){
	n = read(); q = read();
	for(int i=1;i<=n;i++){
		dishes[i].d = read();
		dishes[i].c = read();
	}
	dishes[++n] = node(INT_MAX, INT_MAX);
	stk[++stop] = 1;
	for(int i=2;i<=n;i++){
		while(stop&&dishes[i].d>dishes[stk[stop]].d){
			nxt[stk[stop]] = i;
			stop--;
		}
		stk[++stop] = i;
	}
	for(int i=1;i<=n;i++){
		if(i!=n) add(nxt[i], i);
	}
	seg[0]=seg[n]=1;top[n]=rev[1]=n;
	dfs1(n);dfs2(n);
	for(int i=1;i<=seg[0];i++) qzh[i] = qzh[i-1] + dishes[rev[i]].c;
	while(q--){
		int r = read(),v = read();
		write(query(r,v));putchar('\n');
	}
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：3)

观察本题题干，发现制约水最终的去处的为盘子的直径与容量。若对于每次询问，都直接暴力计算，显然会超时。于是想到一种能够减少判断次数，又不影响结果的方法--倍增。

首先预处理出从第 $i$ 个圆盘开始连续 $2^j$ 个圆盘中的最大直径，记为 $pre_{i,j}$。显然 $\forall i \in [1,n],pre_{i,0} = d_i$。然后就是倍增求最值的过程，这里就不赘述了。然后给出 $f_{i,j},g_{i,j}$，分别表示从 $i$ 开始水溢出 $2^j$ 次后所到达的圆盘与求水溢出所到达的 $2^j$ 个圆盘的容量之和。

但是现在还有一个问题，如果每次遍历去求第 $i$ 个圆盘再加入水后，最终能流到的圆盘，会额外产生 $O(N)$ 的复杂度，加上对所有圆盘的求解以及预处理后的查询，会达到 $O(N^2 \log N)$ 的复杂度，无法通过此题。不难发现，这其实存在单调性，因此使用二分答案去求解。设预处理的查询函数为 `query (l,r)`，则有满足 `query(i + 1,(l + r) >> 1) <= d[i]` 的时候更新左端点为 `l = ((l + r) >> 1) + 1`，否则为 `r = (l + r) >> 1`。在得到答案 $l$ 后，就可以根据变量设置的含义去更新 $f_{i,0},g_{i,0}$，有 $f_{i,0} = l,g_{i,0} = c_{f_{i,0}}$。

由于 $N_{\max} = 10^5$，所以本题解将两个数组设置为 `f[100005][20],g[100005][20]`。则对于 $f_{i,j},g_{i,j}$ 的转移有：

```cpp
for (int j = 1;j < 20;++j)
		for (int i = 1;i <= n;++i)//i~i + 2^j = i ~ 2^(j - 1) + (i + 2^(j - 1) + 1)~2^j
			f[i][j] = f[f[i][j - 1]][j - 1],g[i][j] = g[f[i][j - 1]][j - 1] + g[i][j - 1];
```

最后就是求解的部分了。考虑到题目存在流到最终的水池的情况，所以我们可以再加入一个容积为 $\inf$ 的圆盘。对于每一组的询问，首先判断水能否溢出，若可以，则利用倍增进行处理直至无法溢出，最后特判到达底盘的情况即可。

最后利用倍增的时间复杂度为 $O(n \log n)$。完整代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,d[MAX],c[MAX];
int pre[MAX][20],f[MAX][20],g[MAX][20];
/*pre 预处理求区间最值 
f 求从 i 开始水溢出 2^j 次后所到达的圆盘
g 求水溢出所到达的 2^j 个圆盘的容量之和 */ 
int query (int x,int y);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();m = read ();
	for (int i = 1;i <= n;++i) d[i] = read (),c[i] = read ();
	for (int i = 1;i <= n;++i) pre[i][0] = d[i];//初始化 
	for (int j = 1;(1 << j) <= n;++j)//倍增求区间最值 
		for (int i = 1;i + (1 << j) - 1 <= n;++i)
			pre[i][j] = max (pre[i][j - 1],pre[i + (1 << (j - 1))][j - 1]);
	c[n + 1] = INF;f[n][0] = n + 1;g[n][0] = c[f[n][0]];//加入一个超大容积的底盘 
	for (int i = 1;i < n;++i)
	{
		int l = i + 1,r = n + 1;
		while (l < r)//二分求会流入何处 
		{
			int mid = (l + r) >> 1;
			if (query (i + 1,mid) <= d[i]) l = mid + 1;//log 的查询 
			else r = mid;
		}
		f[i][0] = l;
		g[i][0] = c[f[i][0]];//初始化 
	}
	for (int j = 1;j < 20;++j)
		for (int i = 1;i <= n;++i)
			f[i][j] = f[f[i][j - 1]][j - 1],g[i][j] = g[f[i][j - 1]][j - 1] + g[i][j - 1];
	for (int i = 1;i <= m;++i)
	{
		int x = read (),y = read ();
		if (y > c[x])
		{
			y -= c[x];
			for (int j = 19;j >= 0;--j)
				if (y > g[x][j]) y -= g[x][j],x = f[x][j];
			x = f[x][0];//注意别忘了减去一开始溢出的那一次 
		}
		printf ("%d\n",x == (n + 1) ? 0 : x);//特判 
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
int query (int x,int y)
{
	int k = (int) log2 (y - x + 1);
	return max (pre[x][k],pre[y - (1 << k) + 1][k]);
}
```

---

## 作者：Prean (赞：3)

考试的一道题，因为某些原因sb了常数翻了好几倍/px

首先我们发现，一个水池的水只会向它下边第一个直径比它大的水池流。

我们把这些流动的关系连边，很容易发现是一棵树。

问水最后会到哪个水池相当于在问最老的一个祖先，使得自己到祖先上的点权之和不大于给定的数。然后容易发现是树上倍增。

然后，其实找右边第一个比自己大的数可以用单调栈 $ O(n) $，然而我用了 $ O(n\log n) $ 的倍增+ST表。。。

其次，可以直接倍增，然后我建了树。。。

附上考场上的代码：
```cpp
#include<cstdio>
const int M=1e5+5;
typedef long long ll;
int n,m,a[M],d[M],b[M],lg2[M],f[M][22],st[M][22];
ll s[M];
struct Edge{
	int to;Edge*nx;
}e[M<<1],*h[M],*cnt=e;
inline int max(const int&a,const int&b){
	return a>b?a:b;
}
inline void Add(const int&u,const int&v){
	*cnt=(Edge){v,h[u]};h[u]=cnt++;
}
void DFS(int u){
	d[u]=d[f[u][0]]+1;
	for(int i=1;f[u][i-1];++i)f[u][i]=f[f[u][i-1]][i-1];
	for(Edge*E=h[u];E;E=E->nx){
		int v=E->to;
		s[v]=s[u]+b[v];DFS(v);
	}
}
int Find(int u,int val){
	for(int k=21;k>=0;--k){
		if(s[u]-s[f[u][k]]<val)val-=s[u]-s[f[u][k]],u=f[u][k];
	}
	return u;
}
int main(){
	register int i,j,A,B,now;
	scanf("%d%d",&n,&m);lg2[0]=-1;
	for(i=1;i<=n;++i){
		scanf("%d%d",a+i,b+i);st[i][0]=a[i];
		lg2[i]=lg2[i>>1]+1;
	}
	for(j=1;(1<<j)<=n;++j){
		for(i=1;i+(1<<j)-1<=n;++i){
			st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
	for(i=1;i<=n;++i){
		now=i;
		for(j=21;j>=0;--j){
			if(now+(1<<j)-1<=n&&st[now][j]<=a[i])now+=1<<j;
		}
		if(now==n+1)now=0;
		Add(f[i][0]=now,i);
	}
	DFS(0);
	for(i=1;i<=m;++i){
		scanf("%d%d",&A,&B);
		printf("%d\n",Find(A,B));
	}
	return 0;
}
```

---

## 作者：JoyJoyGang (赞：1)

练习倍增的题。

先利用单调栈求出每个圆盘后面第一个比他半径大的圆盘。

具体见[P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)

然后我们就可以暴力的跳，但是这样显然是会超时的，因此我们使用非常巧妙地倍增思想。

就是算出来每个喷泉盘子流 $2^i$ 个盘子可以流到哪，最多可以积攒多少的水。

代码：

```cpp
#include<bits/stdc++.h>
#define pr pair<int,int>
using namespace std;
const int MA=100005;
const int MC=25;
int n,Q,zu[MA][MC],ke[MA][MC];
struct zh{
	int x,y;
}a[MA];
priority_queue<pr,vector<pr>,greater<pr> > q;
int cha(int x,int y){
	if(a[x].y>=y){
		return x;
	}
	y-=a[x].y;
	for(int i=MC-5;i>=0;i--){
		if(zu[x][i]!=0&&y>ke[x][i]){
			y-=ke[x][i];x=zu[x][i];
		}
	}
	return zu[x][0];
}
int main()
{
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		while(q.empty()==0){
			int he=q.top().first,ha=q.top().second;
			if(he<a[i].x){
				zu[ha][0]=i;ke[ha][0]=a[i].y;
			}
			else{
				break;
			}
			q.pop();
		}
		q.push(make_pair(a[i].x,i));
	}
	for(int i=1;(1<<i)<=n;i++){
		for(int j=1;j+(1<<i)<=n;j++){
			zu[j][i]=zu[zu[j][i-1]][i-1];ke[j][i]=ke[j][i-1]+ke[zu[j][i-1]][i-1];
		}
	}
	while(Q>0){
		--Q;int x,y;scanf("%d%d",&x,&y);printf("%d\n",cha(x,y));	
	}
	return 0;
}
```



---

## 作者：phigy (赞：1)

[题目链接](https://loj.ac/p/3373)

显然复杂度要求$O(nlogn)$以下

---

![](https://loj-img.upyun.menci.memset0.cn/2020/10/22/5f913c2eaad64.png)

一个储水装置满了一定会流到固定的另一个储水装置

如图中1会流到2，2会流到5 ，6会流到地面即0。

所以用一个$Fa[i]$表示第$i$个储水装置会流到第几个储水装置。

算$Fa[i]$的方法：

用一个小根堆将没找到$Fa[i]$的储水装置的信息存起来。

以$c[i]$排序。

然后发现新的$c[i]$比堆头大，

就让$Fa[$堆头的编号$]=i$。

用到了结构体搞得复杂了一点。

代码:

```cpp
#include <queue>
#include <iostream>

using namespace std;

struct cilcle
{
    int h,w,id;
};
bool operator<(cilcle a,cilcle b)
{
    return a.h<b.h;
}
bool operator>(cilcle a,cilcle b)
{
    return a.h>b.h;
}
priority_queue <cilcle,vector<cilcle>,greater<cilcle> > q;
int n,m;
int c[100005],d[100005];
int fa[100005];
void make_fa()
{
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        cin>>c[i]>>d[i];
        if(!q.empty())
        {
            while(q.top().h<c[i]&&( !q.empty() ) )
            {
                fa[q.top().id]=i;
                q.pop();
            }
        }
        cilcle pig;
        pig.h=c[i];
        pig.w=d[i];
        pig.id=i;
        q.push(pig);
    }
                                 
                                 
                                 }
```


------

实际上会发现这是一颗以地面即0为根节点的一颗树。

每个点的点权就是$d[i]$。

询问的就是从点$R$向上爬，在经过的点的点权和不超过$V$，

的情况下最高能爬到第几个点。

马上想到ST表+倍增。

用$stp[i][j]$存$i$向上爬$2^j$条边到几号点。

用$stw[i][j]$存$i$向上爬到$stp[i][j]$的点权和。

但是不包括$stp[i][j]$的点权。


有：

$stp[i][0]=fa[i];$

$stw[i][0]=d[i];$

$stp[i][j]=stp[stp[i][j-1]][j-1];$

$stw[i][j]=stw[i][j-1]+stw[stp[i][j-1]][j-1];$

代码：

```cpp
void make_st()
{
    int i,j,k;
    for(j=1;j<=22;j++)
    {
        for(i=1;i<=n;i++)
        {
            stp[i][j]=stp[stp[i][j-1]][j-1];
            stw[i][j]=stw[i][j-1]+stw[stp[i][j-1]][j-1];
        }
    }
    
    for(i=1;i<=n;i++)
    {
        stp[i][0]=fa[i];
        stw[i][0]=d[i];
    }
}
```

---

然后再是倍增。

代码：

```cpp
int query(int x,int y)
{
    for(int i=21;i>=0;i--)
    {
        if(stp[x][i]!=0&&stw[x][i]<y)
        {
            return query(stp[x][i],y-stw[x][i]);
        }
    }
    if(fa[x]==0&&y>d[x])return 0;
    return x;
}
```

----

整体来说这题并不高，提高第2.5简单的题吧。

我的代码把一些简单的东西复杂化了。

做的时候脑子糊涂了，于是倍增用递归实现的。

导致原本50行的东西变成100多行。


完整代码：

```cpp
#include <queue>
#include <iostream>

using namespace std;

struct cilcle
{
    int h,w,id;
};
bool operator<(cilcle a,cilcle b)
{
    return a.h<b.h;
}
bool operator>(cilcle a,cilcle b)
{
    return a.h>b.h;
}
priority_queue <cilcle,vector<cilcle>,greater<cilcle> > q;
int n,m;
int c[100005],d[100005];
int fa[100005];
int stp[100005][22],stw[100005][22];
void make_fa()
{
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        cin>>c[i]>>d[i];
        stw[i][0]=d[i];
        if(!q.empty())
        {
            while(q.top().h<c[i]&&( !q.empty() ) )
            {
                fa[q.top().id]=i;
                stp[q.top().id][0]=i;
                q.pop();
            }
        }
        cilcle pig;
        pig.h=c[i];
        pig.w=d[i];
        pig.id=i;
        q.push(pig);
    }
}
void make_st()
{
    int i,j,k;
    for(j=1;j<=22;j++)
    {
        for(i=1;i<=n;i++)
        {
            stp[i][j]=stp[stp[i][j-1]][j-1];
            stw[i][j]=stw[i][j-1]+stw[stp[i][j-1]][j-1];
        }
    }
    
    for(i=1;i<=n;i++)
    {
        stp[i][0]=fa[i];
        stw[i][0]=d[i];
    }
}
int query(int x,int y)
{
    for(int i=21;i>=0;i--)
    {
        if(stp[x][i]!=0&&stw[x][i]<y)
        {
            return query(stp[x][i],y-stw[x][i]);
        }
    }
    if(fa[x]==0&&y>d[x])return 0;
    return x;
}
int main()
{
    int i,j,k;
    cin>>n>>m;
    make_fa();
    make_st();
    for(i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        cout<<query(x,y)<<endl;
    }
    return 0;
}   
```


---

