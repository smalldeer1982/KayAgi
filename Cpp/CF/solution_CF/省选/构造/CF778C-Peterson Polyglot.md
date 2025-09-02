# Peterson Polyglot

## 题目描述

Peterson loves to learn new languages, but his favorite hobby is making new ones. Language is a set of words, and word is a sequence of lowercase Latin letters.

Peterson makes new language every morning. It is difficult task to store the whole language, so Peterson have invented new data structure for storing his languages which is called broom. Broom is rooted tree with edges marked with letters. Initially broom is represented by the only vertex — the root of the broom. When Peterson wants to add new word to the language he stands at the root and processes the letters of new word one by one. Consider that Peterson stands at the vertex $ u $ . If there is an edge from $ u $ marked with current letter, Peterson goes through this edge. Otherwise Peterson adds new edge from $ u $ to the new vertex $ v $ , marks it with the current letter and goes through the new edge. Size of broom is the number of vertices in it.

In the evening after working day Peterson can't understand the language he made this morning. It is too difficult for bored Peterson and he tries to make it simpler. Simplification of the language is the process of erasing some letters from some words of this language. Formally, Peterson takes some positive integer $ p $ and erases $ p $ -th letter from all the words of this language having length at least $ p $ . Letters in words are indexed starting by 1. Peterson considers that simplification should change at least one word, i.e. there has to be at least one word of length at least $ p $ . Peterson tries to make his language as simple as possible, so he wants to choose $ p $ such that the size of the broom for his simplified language is as small as possible.

Peterson is pretty annoyed with this task so he asks you for help. Write a program to find the smallest possible size of the broom and integer $ p $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778C/f15fa0cc8758e6866285fb29653e592b9e8e324d.png)

Broom from the second sample test can be built using language "piece", "of", "pie", "pretty", "prefix". Its simplification with $ p=2 $ obtains the language of words "pece", "o", "pe", "petty", "pefix". This language gives us the broom with minimum possible size.

## 样例 #1

### 输入

```
5
1 2 c
2 3 a
3 4 t
2 5 t
```

### 输出

```
3
2
```

## 样例 #2

### 输入

```
16
1 2 o
2 3 f
1 4 p
4 5 i
5 6 e
6 7 c
7 8 e
4 9 r
9 10 e
10 11 t
11 12 t
12 13 y
10 14 f
14 15 i
15 16 x
```

### 输出

```
12
2
```

# 题解

## 作者：Aonynation (赞：6)

[my cnblogs](https://www.cnblogs.com/Oier-GGG/articles/16211508.html)

~~题目连接就不放了，人类应该反对阴间题目描述~~

下面给出一个作为正常人能够看懂的题面描述：

* 给一棵 $\text{trie}$ 树，可以删掉某一层的所有节点和边。

* 被删除的节点的子节点会代替当前节点,形成新的一层节点,如果有相同的可以合并。

* 求删掉哪一层边后合并出的 $\text{trie}$ 树最小？

-----

考虑 $\text{trie}$ 的合并。

我们假设已经删去了一个节点，观察下一步会发生什么。

那么接下来一定是这个节点的儿子们所代表的子树合并成一个$\text{trie}$ 然后和当前节点的父亲相连。


然后我们来考虑这样一段 $\text{Trie}$ 树合并的代码：

```cpp
inline int merge(int x, int y) {
  if (x == 0 || y == 0) 
    return x + y;
  int now = ++cnt;
  for (int i = 0; i < 26; i++)
    son[now][i] = merge(son[x][i], son[y][i]);
  return now;
}
```
相信大家对 $\text{merge}$ 的流程已经非常熟悉了。

--------

下面我们来考虑新建一个节点的意义：

我们发现在进行一次新建节点时一定是把其中的两个节点合并成为一个点。

所以也就可以直接等价于是删除了原来 $\text{Trie}$ 树上的一个节点。

---------

我们用 $num$ 来记录一下此时新删除的节点的数量。

这是删除一个点的情况。

那么我们要删除整整一个层怎么办呢？

直接用 $\text{dfs}$ 跑一边即可，记得带入 $\text{deep}$ 记录当前的深度。

#### Code
```cpp
#include <bits/stdc++.h>

#define file(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)

#define Enter putchar('\n')
#define quad putchar(' ')

const int N = 600005;

int n, son[N][30], root, ans, maxn, sum[N], cnt;
char c[10];

inline int merge(int x, int y) {
  if (x == 0 || y == 0) 
    return x + y;
  int now = ++cnt;
  for (int i = 0; i < 26; i++)
    son[now][i] = merge(son[x][i], son[y][i]);
  return now;
}

inline void dfs(int now, int deep) {
  int num;
  num = cnt = n + 1;
  for (int i = 0; i < 26; i++)
    if (son[now][i])
      num = merge(num, son[now][i]);
  sum[deep] += cnt - n - 1;
  for (int i = 0; i < 26; i++)
    if (son[now][i]) dfs(son[now][i], deep + 1);
}

signed main(void) {
  // file("CF778C");
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin >> n;
  root = 1;
  for (int i = 1, x, y; i < n; i++) {
    std::cin >> x >> y >> c;
    son[x][c[0] - 'a'] = y;
  }
  dfs(1, 1);
  for (int i = 1; i <= n; i++) 
    if (sum[i] > maxn) {
      maxn = sum[i];
      ans = i;
    }
  std::cout << n - maxn << std::endl << ans << std::endl;
}
```

---

## 作者：dead_X (赞：5)

## 前言
dsu on tree 好题。

当时在 vp，然后大概是这样的。

* 啊我会 $O(n^2)$
* 啊我觉得这能 dsu on tree
* 啊这怎么 dsu on tree
* 啊这不能 dsu on tree 吧
* （zhouAKngyang 写了一发 dsu on tree 然后立马 A 掉了）


## 思路
首先考虑 $O(n^2)$ 的暴力。

我们对于每一个节点合并子树，在合并的过程中计算有几条边不需要。

于是你想有哪些信息可以上传。

然后你发现什么信息都不需要上传！

由于我们只需要合并一个点的所有子树，我们只需要考虑怎么**不遍历考虑重儿子所在的子树。**

然后你发现这个异常简单，只需要在**重儿子所在的子树的基础上**合并其余子树即可。

然后复杂度就和启发式合并一样了，即 $O(n\log n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int nxt[1500003][26];
int v[1500003];
int w[1500003],hs[1500003];
int X[1500003],Y[1500003],C=0;
int CNT=700000;
int qwq;
void merge(int x,int y)
//merge x to y
{
	//printf("%d %d\n",x,y);
	for(int i=0; i<26; ++i)
	{
		if(nxt[x][i])
		{
			if(!nxt[y][i]) 
			{
				X[++C]=y,Y[C]=i;
				nxt[y][i]=++CNT;
				//return ;
			}
			else ++v[qwq];
			merge(nxt[x][i],nxt[y][i]);
		}
	}
	return ;
}
void clear()
{
	for(int i=1; i<=C; i++)
	nxt[X[i]][Y[i]]=0;
	C=0;
	return ;
}
void dfs(int d,int x)
{
	for(int i=0; i<26; i++) 
	if(nxt[x][i]) ++v[d],dfs(d+1,nxt[x][i]);
	qwq=d;CNT=700000;
	for(int i=0; i<26; i++) 
	if(nxt[x][i]&&(nxt[x][i]!=hs[x])) merge(nxt[x][i],hs[x]);
	clear(); 
	return ;
}
void init(int x)
{
	for(int i=0,g=-1; i<26; i++) 
	if(nxt[x][i]) 
	{
		init(nxt[x][i]),w[x]+=w[nxt[x][i]];
		if(w[nxt[x][i]]>g) hs[x]=nxt[x][i],g=w[nxt[x][i]];
	}
	return ;
}
int to[1000003],Nxt[1000003],c[1000003],head[1000003];
int Q=0;
void DFS(int x,int y)
{
	for(int i=head[x]; i; i=Nxt[i]) if(to[i]!=y)
	{
		nxt[x][c[i]]=to[i];
		DFS(to[i],x);
	}
	return ;
}
signed main()
{
    int n=read();
    char s;
    for(int i=1; i<=n; i++) w[i]=1;
    for(int i=1,u,v; i<n; i++) 
    {
    	u=read(),v=read(),s=getchar();
    	while(!islower(s)) s=getchar();
    	s-='a';
    	to[++Q]=v,Nxt[Q]=head[u],head[u]=Q,c[Q]=s;
    	//nxt[u][s-'a']=v;c=c;
    }
    DFS(1,1);
	init(1);
    dfs(1,1);
    int mx=99999999,id=1;
    for(int i=n; i>=1; i--)
    {
    	if(n-v[i]<=mx)
    	{
    		mx=n-v[i];
    		id=i;
    	}
    }
    printf("%d\n%d\n",mx,id);
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑 trie 树合并的复杂度到底是什么？

不难发现，合并时每遍历到一个节点，这个点必然同时在两棵树中出现，所以不难发现的是合并大小为 $sz_a,sz_b$ 的 trie 树复杂度为 $\min(sz_a,sz_b)$。

于是在枚举断掉哪一层的节点时，考虑直接将所有儿子依次合并，并计算出带来的贡献，这个过程时间复杂度等价于启发式合并，因此是 $O(n \log n)$ 的。

记得在合并后撤销掉合并操作。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 3e5+114;
int son[maxn][26],dep[maxn];
int answer[maxn];
int n;
string S[maxn];
int rt;
int sum;
vector< pair< pair<int,int> ,int> > del;
int merge(int u,int v){
	if(u==0||v==0) return u+v;
	sum++;
	for(int i=0;i<26;i++) del.push_back(make_pair(make_pair(u,i),son[u][i])),son[u][i]=merge(son[u][i],son[v][i]);
	return u;
}
void dfs(int u){
	int cnt=0;
	for(int i=0;i<26;i++){
		int v=son[u][i];
		if(v==0) continue;
		cnt++;
		dep[v]=dep[u]+1;
		dfs(v);
	}
	if(cnt==0) return ;
	sum=1;
	rt=0;
	for(int i=0;i<26;i++) rt=merge(rt,son[u][i]);
	while(del.size()>0){
		int u=del.back().first.first,i=del.back().first.second,w=del.back().second;
		son[u][i]=w;
		del.pop_back();
	}
	answer[dep[u]+1]-=sum;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) answer[i]=n;
	for(int i=1;i<n;i++){
		int u,v;
		char c;
		cin>>u>>v>>c;
		son[u][c-'a']=v;
	}
	dfs(1);
	int mi=answer[1];
	for(int i=1;i<=n;i++) mi=min(mi,answer[i]);
	cout<<mi<<'\n';
	for(int i=1;i<=n;i++){
		if(answer[i]==mi){
			cout<<i<<'\n';
			return 0;
		}
	}
	return 0;
}

```

---

## 作者：localhost (赞：1)

题意: 

给一棵trie树，可以删掉某一层的所有节点和边

被删除的节点的子节点会代替当前节点,形成新的一层节点,如果有相同的可以合并

求删掉哪一层边后合并出的trie树最小？

解法: 

trie的启发式合并

```cpp
int mg(int x,int y){
    if(!x||!y)return x+y;
    int now=++cnt;
    Fur(i,0,25)c[now][i]=mg(c[x][i],c[y][i]);
    return now;
}
```

这个合并的复杂度是$\Theta(\log n)$的

证明:

> 每次合并向下递归的时候规模$n$会变成原来的一半$\frac n2$
> 
> 所以最多需要合并$\log_2 n$次

完整代码: 

```cpp
const int N=600011;
int n,cnt,c[N][26],a[N];
int mg(int x,int y){
    if(!x||!y)return x+y;
    int now=++cnt;
    Fur(i,0,25)c[now][i]=mg(c[x][i],c[y][i]);
    return now;
}
void dfs(int x,int d){
    int now=n+1;cnt=n+1;
    Fur(i,0,25)if(c[x][i])
        now=mg(now,c[x][i]);
    a[d]+=cnt-n-1;
    Fur(i,0,25)if(c[x][i])
        dfs(c[x][i],d+1);
}
int main(){
    in(n);
    int x,y,ans=0,as=0;char w;
    Fur(i,2,n)in(x,y,w),c[x][w-'a']=y;
    dfs(1,1);
    Fur(i,1,n)if(a[i]>ans)as=i,ans=a[i];
    printf("%d\n%d\n",n-ans,as);
}
```

---

