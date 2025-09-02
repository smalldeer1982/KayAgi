# Kuroni and the Celebration

## 题目描述

This is an interactive problem.

After getting AC after 13 Time Limit Exceeded verdicts on a geometry problem, Kuroni went to an Italian restaurant to celebrate this holy achievement. Unfortunately, the excess sauce disoriented him, and he's now lost!

The United States of America can be modeled as a tree (why though) with $ n $ vertices. The tree is rooted at vertex $ r $ , wherein lies Kuroni's hotel.

Kuroni has a phone app designed to help him in such emergency cases. To use the app, he has to input two vertices $ u $ and $ v $ , and it'll return a vertex $ w $ , which is the lowest common ancestor of those two vertices.

However, since the phone's battery has been almost drained out from live-streaming Kuroni's celebration party, he could only use the app at most $ \lfloor \frac{n}{2} \rfloor $ times. After that, the phone would die and there will be nothing left to help our dear friend! :(

As the night is cold and dark, Kuroni needs to get back, so that he can reunite with his comfy bed and pillow(s). Can you help him figure out his hotel's location?

## 说明/提示

Note that the example interaction contains extra empty lines so that it's easier to read. The real interaction doesn't contain any empty lines and you shouldn't print any extra empty lines as well.

The image below demonstrates the tree in the sample test:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1305D/3f777a34971aedf6bf2be87025826d252775cf29.png)

## 样例 #1

### 输入

```
6
1 4
4 2
5 3
6 3
2 3

3

4

4```

### 输出

```
? 5 6

? 3 1

? 1 2

! 4```

# 题解

## 作者：xht (赞：8)

每次询问两个点的 LCA，最多询问 $\lfloor \frac{n}{2} \rfloor$ 次确定根。

很傻的一道交互题。

注意到如果一个叶子和另一个点的 LCA 就是这个叶子，那么这个叶子一定为根；如果不是，则这个叶子一定不是根。

那么我们每次询问两个叶子的 LCA 即可，如果是其中某一个点，则那个点就是根；否则删掉两个点，注意可能产生新的叶子。

最坏情况下，每次询问会删掉两个叶子，那么 $\lfloor \frac{n}{2} \rfloor$ 次后最多只剩下一个点，这个点显然就是根了。

```cpp
const int N = 1e3 + 7;
int n, d[N], v[N];
vi e[N];

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1, x, y; i < n; i++)
		cin >> x >> y, e[x].pb(y), e[y].pb(x), d[x]++, d[y]++;
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (d[i] == 1) q.push(i);
	for (int i = 1; i <= n / 2; i++) {
		int x = q.front();
		q.pop();
		int y = q.front();
		q.pop();
		cout << "? " << x << " " << y << endl;
		fflush(stdout);
		int z;
		cin >> z;
		if (z == x || z == y) {
			cout << "! " << z << endl;
			return 0;
		}
		for (int z : e[x])
			if (!v[z] && (--d[z] == 1)) q.push(z);
		for (int z : e[y])
			if (!v[z] && (--d[z] == 1)) q.push(z);
		v[x] = v[y] = 1;
	}
	for (int i = 1; i <= n; i++)
		if (!v[i]) cout << "! " << i << endl;
	return 0;
}
```

---

## 作者：ix35 (赞：4)

我这题的做法和其他题解不同。

考虑一条长度为 $2$ 的路径 $a\to b\to c$，询问 $a,c$ 的 $\mathrm{LCA}$，如果 $\mathrm{LCA}(a,c)=a$，那么 $b,c$ 一定不是根，同理如果 $\mathrm{LCA}(a,c)=b$，那么 $a,c$ 一定不是根，如果 $\mathrm{LCA}(a,c)=c$，那么 $a,b$ 一定不是根。

于是每次可以排除两个点，可以在 $\dfrac{n}{2}$ 次以内得到根结点。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2010;
int n,ans,x,y,nw,eg,tot,hd[MAXN],ver[2*MAXN],nx[2*MAXN],vis[MAXN],dep[MAXN],fa[MAXN],siz[MAXN],dfn[MAXN],ed[MAXN],rev[MAXN];
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void dfs (int x,int fat) {
	fa[x]=fat,dep[x]=dep[fat]+1,siz[x]=1,dfn[x]=ed[x]=++tot;
	rev[tot]=x;
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fat||vis[ver[i]]) {continue;}
		dfs(ver[i],x);
		siz[x]+=siz[ver[i]],ed[x]=ed[ver[i]];
	}
	return;
}
int main () {
	scanf("%d",&n);
	nw=n;
	for (int i=2;i<=n;i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,y),add_edge(y,x);
	}
	while (1) {
		if (nw==1) {
			for (int i=1;i<=n;i++) {
				if (!vis[i]) {printf("! %d\n",i);break;}
			}
			return 0;
		} else if (nw==2) {
			int a=0,b=0,c=0;
			for (int i=1;i<=n;i++) {
				if (!vis[i]) {
					if (a) {b=i;}
					else {a=i;}
				}
			}
			printf("? %d %d\n",a,b);
			fflush(stdout);
			scanf("%d",&c);
			if (c==-1) {return 0;}
			printf("! %d\n",c);
			return 0;
		} else {
			int rt=0,c=0,nflg=0;
			tot=0;
			for (int i=1;i<=n;i++) {
				if (!vis[i]) {rt=i;break;}
			}
			dep[rt]=1;
			dfs(rt,0);
			for (int i=1;i<=n;i++) {
				if (!vis[i]&&dep[i]==3) {
					printf("? %d %d\n",i,rt);
					fflush(stdout);
					scanf("%d",&c);
					if (c==-1) {return 0;}
					if (c==rt) {
						nw-=siz[fa[i]];
						for (int j=dfn[fa[i]];j<=ed[fa[i]];j++) {vis[rev[j]]=1;}
					}
					if (c==i) {
						nw=siz[i];
						for (int j=dfn[rt];j<=ed[rt];j++) {vis[rev[j]]=1;}
						for (int j=dfn[i];j<=ed[i];j++) {vis[rev[j]]=0;}
					}
					if (c==fa[i]) {
						nw=siz[fa[i]]-siz[i];
						for (int j=dfn[rt];j<=ed[rt];j++) {vis[rev[j]]=1;}
						for (int j=dfn[fa[i]];j<=ed[fa[i]];j++) {vis[rev[j]]=0;}
						for (int j=dfn[i];j<=ed[i];j++) {vis[rev[j]]=1;}
					}
					nflg=1;
					break;
				}
			}
			if (nflg) {continue;}
			int a=0,b=0;
			c=0;
			for (int i=1;i<=n;i++) {
				if (!vis[i]&&dep[i]==2) {
					if (a) {b=i;}
					else {a=i;}
				}
			}
			printf("? %d %d\n",a,b);
			fflush(stdout);
			scanf("%d",&c);
			if (c==-1) {return 0;}
			if (c==a) {
				printf("! %d\n",a);
				return 0;
			}
			if (c==b) {
				printf("! %d\n",b);
				return 0;
			}
			vis[a]=vis[b]=1,nw-=2;
			continue;
		}
	}
	return 0;
}
```


---

## 作者：peterwuyihong (赞：3)

题意：交互题，给定一棵树，让你交互，你可以询问一对点，会返回它们的 lca，让你在 $\lfloor\frac n 2\rfloor$ 次询问中找到树根。

你维护一个队列，里面装着所有叶子节点，你每次询问两个叶子节点，问他们的 lca，如果是其中之一，就是 lca，否则就删掉两个节点，维护新的叶子节点，每次删掉两个点，所以操作数不会超过 $\lfloor\frac n 2\rfloor$。

现在是 $11:21$，我看我什么时候写完。

现在是 $11:30$，我写完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1010
int n,in[maxn],x,y,lca;
int head[maxn],Next[maxn<<1],ver[maxn<<1],tot;
void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
int q[maxn*maxn],l,r;
bitset<maxn>no;
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		add(x,y),add(y,x);
		in[x]++,in[y]++;
	}
	r=-1;
	for(int i=1;i<=n;i++)if(in[i]==1)q[++r]=i;
	for(int j=1;j<=n/2;j++){
		x=q[l++],y=q[l++];
		cout<<"? "<<x<<' '<<y<<endl;
		cin>>lca;
		if(lca==x||lca==y){
			cout<<"! "<<lca<<endl;
			return 0;
		}
		for(int i=head[x];i;i=Next[i])in[ver[i]]--,(in[ver[i]]==1&&!no[lca])&&(q[++r]=ver[i]);
		for(int i=head[y];i;i=Next[i])in[ver[i]]--,(in[ver[i]]==1&&!no[lca])&&(q[++r]=ver[i]);
		no[x]=no[y]=1;
	}
	for(int i=1;i<=n;i++)
	if(!no[i])cout<<"! "<<i<<endl;
}
```
就是要注意强制执行 $\lfloor\frac n 2\rfloor$ 次，不能 naive ``` while(l<=r)```

---

## 作者：gyh20 (赞：3)

考虑一种朴素的方法，自定义一个树根，如果它有两个及以上子结点则询问这两个点，如果得到的 LCA 是根，则删除这两个点所在子树，否则保留得到的 LCA 的子树。

如果只有一个子结点，则询问根和子结点，得到的是根的话就直接输出答案，否则找到这个子结点。

这样的期望询问次数不高，但会被一条链轻松卡掉，因为只有一个子结点的情况可能有浪费。

主要原因是，字树大小不均匀，导致左偏或者右偏，回忆一下解决其他树问题时是怎么做的。

运用点分治的思想，每次找到重心，再执行之前的操作，可知，如果树上的节点数大于等于 $3$，则将重心设为根后一定存在至少两个子结点。如果只剩两个点，询问一次即可。

可知这样的询问次数是远低于 $n/2$（仅在菊花图时达到$n/2$），时间复杂度为 $O(n^2)$，可过。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
struct edge{
	int to,next;
}e[2002];
int n,head[1002],cnt,del[1002],zx,siz[1002],mns;
inline void add(re int x,re int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}
inline void get(re int x,re int y){
	siz[x]=1;
	int mxs=0;
	for(re int i=head[x];i;i=e[i].next){
		if(e[i].to!=y&&!del[e[i].to]){
			get(e[i].to,x);
			siz[x]+=siz[e[i].to];
			mxs=max(mxs,siz[e[i].to]);
		}
	}
	mxs=max(mxs,n-siz[x]);
	if(mxs<mns){
		mns=mxs;
		zx=x;
	}
}
inline void dfs(re int x,re int y){
	siz[x]=1;
	for(re int i=head[x];i;i=e[i].next){
		if(e[i].to!=y&&!del[e[i].to]){
			dfs(e[i].to,x);
			siz[x]+=siz[e[i].to];
		}
	}
}
inline void find(re int x){
	mns=1e9;
	get(x,x);
	x=zx;
	dfs(x,x);
	if(siz[x]==1){
		printf("! %d\n",x);
		fflush(stdout);
		return;
	}
	else if(siz[x]==2){
		int y;
		for(re int i=head[x];i;i=e[i].next){
			
			if(!del[e[i].to]){
				y=e[i].to;
				break;
			}
		}
		printf("? %d %d\n",x,y);
		fflush(stdout);
		x=read();
		printf("! %d\n",x);
		fflush(stdout);
		return;
	}
	else{
		int lst=0,lst1=0;
		for(re int i=head[x];i;i=e[i].next){
			if(!del[e[i].to]){
				if(!lst)lst=e[i].to;
				else lst1=e[i].to;
			}
		}putchar('\n');
		printf("? %d %d\n",lst,lst1);
		fflush(stdout);
		int tmp=read();
		if(tmp==lst){
			del[x]=1;
			n=siz[lst];
			find(lst);
		}
		else if(tmp==lst1){
			del[x]=1;
			n=siz[lst1];
			find(lst1);
		}
		else{
			del[lst]=del[lst1]=1;
			n-=siz[lst];
			n-=siz[lst1];
			find(x);
		}
	}
}
int x,y;
int main(){
	n=read();
	for(re int i=1;i<n;++i){
		x=read();
		y=read();
		add(x,y);
		add(y,x);
	}
	find(1);
}
```


---

## 作者：LB_tq (赞：3)

# Solution
一道交互题：给定 $n$ 个节点一棵树，每次可以询问任意两点的最近公共祖先，使用不超过 $\frac{n}{2}$ 次询问求得树的根节点。

由于要求根节点，所以我们可以确定一个询问顺序：

- 每次询问一对叶子节点的$LCA$，若$LCA$为叶子节点中的一个，那这个节点必定是根节点。

- 若$LCA$不是叶子节点，那么我们可以删除这两个叶子，同时更新其他节点的度，产生新的叶子。

 由于每次可以删除2个节点，那么在 $\frac{n}{2}$ 次后要么已经得知根节点，要么只剩一个根节点未删除。
 
 于是可以 $O(n)$ 解决本题。
 
 # Code
 ```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=1e3+10;
struct edge{
	int t;
	int v;
}e[maxn<<1];
int n,s,hd,tl,f[maxn],q[maxn],d[maxn];
bool flag=false;
void add(int x,int y){
	s++;
	e[s].t=f[x];
	e[s].v=y;
	f[x]=s;
}
int main(){
	int x,y,z;
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		add(x,y),add(y,x);
		d[x]++,d[y]++;
	}
	for(int i=1;i<=n;i++)
		if(d[i]==1)
			q[++tl]=i;
	for(int i=1;i<=n/2;i++){
		x=q[++hd];
		y=q[++hd];
		cout<<"? "<<x<<" "<<y<<endl;
		fflush(stdout);
		cin>>z;
		if(z==x||z==y){
			flag=true;
			cout<<"! "<<z;
			break;
		}
		for(int j=f[x];j!=0;j=e[j].t){
			d[e[j].v]--;
			if(d[e[j].v]==1)
				q[++tl]=e[j].v;
		}
		for(int j=f[y];j!=0;j=e[j].t){
			d[e[j].v]--;
			if(d[e[j].v]==1)
				q[++tl]=e[j].v;
		}
	}
	if(!flag)
		cout<<"! "<<q[tl];
	return 0;
}
```


---

## 作者：liqiqi (赞：2)

记录一下第一次做交换题。

交换题与平常题不同的是你可以输出想要的查询，题目会通过输入给你查询的结果，最后要记得每一次查询后要刷新缓冲区。

对于这题来说，要找到n个点，n-1条边的树的根。可以每次从度为1的节点查询
1.如果这两个节点的lca为这两者之一，则该lca为树的根。

2.如果这两个节点的lca不为这两者之一，删除与这两个简单的边，重新从度为1的节点查询

3.如果度为1的节点只剩下一个，则该点为根节点。
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[20000];
int a[100001];
vector<int> p;
void dele(int x)
{
	for (int i = 0; i < g[x].size(); i++)
	{
		a[g[x][i]]--;
		if (a[g[x][i]] == 1)
			p.push_back(g[x][i]);
	}
}
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
		a[x]++;
		a[y]++;
		
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 1)
			p.push_back(i);

	}
	while (p.size()>1)
	{
		int x = p[0];
		int y = p[1];
		int ans;
		cout << "? " << x << " " << y << endl;
		cin >> ans;
		if (ans == x || ans == y)
		{
			cout << "! " << ans << endl;
			return 0;
		}
		dele(x);
		dele(y);
		p.erase(p.begin());
		p.erase(p.begin());

	}
	cout <<"! "<<p[0] << endl;

}
```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1305D)

注意到树的形态和标号都是给定的，所以做法都写在题面上了。

然后你注意到如果你随便问两个点没法确定顺序，所以应该问叶子。

每次询问两个叶子，如果返回其中一个叶子那它显然是 LCA。如果都不是那你就排除了两个点。

然后如果你询问次数用完了还没出结果，那最多就剩一个点没问过，答案就是那个点。

---

