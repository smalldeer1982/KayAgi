# National Property

## 题目描述

You all know that the Library of Bookland is the largest library in the world. There are dozens of thousands of books in the library.

Some long and uninteresting story was removed...

The alphabet of Bookland is so large that its letters are denoted by positive integers. Each letter can be small or large, the large version of a letter $ x $ is denoted by $ x' $ . BSCII encoding, which is used everywhere in Bookland, is made in that way so that large letters are presented in the order of the numbers they are denoted by, and small letters are presented in the order of the numbers they are denoted by, but all large letters are before all small letters. For example, the following conditions hold: $ 2&lt;3 $ , $ 2'&lt;3' $ , $ 3'&lt;2 $ .

A word $ x_{1},x_{2},...,x_{a} $ is not lexicographically greater than $ y_{1},y_{2},...,y_{b} $ if one of the two following conditions holds:

- $ a<=b $ and $ x_{1}=y_{1},...,x_{a}=y_{a} $ , i.e. the first word is the prefix of the second word;
- there is a position $ 1<=j<=min(a,b) $ , such that $ x_{1}=y_{1},...,x_{j-1}=y_{j-1} $ and $ x_{j}&lt;y_{j} $ , i.e. at the first position where the words differ the first word has a smaller letter than the second word has.

For example, the word " $ 3' $ $ 7 $ $ 5 $ " is before the word " $ 2 $ $ 4' $ $ 6 $ " in lexicographical order. It is said that sequence of words is in lexicographical order if each word is not lexicographically greater than the next word in the sequence.

Denis has a sequence of words consisting of small letters only. He wants to change some letters to large (let's call this process a capitalization) in such a way that the sequence of words is in lexicographical order. However, he soon realized that for some reason he can't change a single letter in a single word. He only can choose a letter and change all of its occurrences in all words to large letters. He can perform this operation any number of times with arbitrary letters of Bookland's alphabet.

Help Denis to choose which letters he needs to capitalize (make large) in order to make the sequence of words lexicographically ordered, or determine that it is impossible.

Note that some words can be equal.

## 说明/提示

In the first example after Denis makes letters $ 2 $ and $ 3 $ large, the sequence looks like the following:

- $ 2' $
- $ 1 $
- $ 1 $ $ 3' $ $ 2' $
- $ 1 $ $ 1 $

The condition $ 2'&lt;1 $ holds, so the first word is not lexicographically larger than the second word. The second word is the prefix of the third word, so the are in lexicographical order. As the first letters of the third and the fourth words are the same, and $ 3'&lt;1 $ , then the third word is not lexicographically larger than the fourth word.

In the second example the words are in lexicographical order from the beginning, so Denis can do nothing.

In the third example there is no set of letters such that if Denis capitalizes them, the sequence becomes lexicographically ordered.

## 样例 #1

### 输入

```
4 3
1 2
1 1
3 1 3 2
2 1 1
```

### 输出

```
Yes
2
2 3 ```

## 样例 #2

### 输入

```
6 5
2 1 2
2 1 2
3 1 2 3
2 1 5
2 4 4
2 4 4
```

### 输出

```
Yes
0
```

## 样例 #3

### 输入

```
4 3
4 3 2 2 1
3 1 1 3
3 2 3 3
2 3 1
```

### 输出

```
No
```

# 题解

## 作者：CharlieCai (赞：9)

大致题意：给定一些字符串，字符串中的字母开始时均为小写，你可以将其中若干**种**字母全部改为大写，问能否使得操作后给定的字符串满足按字典序升序（**可以等于**）排列。如果能，则输出方案。

这里提供一个拓扑排序的解法。

首先，由于影响两个字符串的字典序大小关系的只有两个字符串的第一个不同的字母，所以我们只需要让所有两个相邻字符串的第一个不同的字母升序排列。

由于一个字母可能要满足与其它多个字母的大小关系，所以我们可以考虑建图以处理字母之间的大小关系，并开一个 $b$ 数组记录字母的大小写状态， $b_i$ 为 $0$ 为不确定是否要改，为 $1$ 为必须为大写，为 $2$ 为必须为小写。对于字母 $x,y$，若操作后字母 $x$ 必须小于字母 $y$，则建边 $x \to y$。

建图后不难发现若该图有环或某个字母的大小写状态存在矛盾则无解。除了有环的情况，对于一条边 $x \to y$ 上的点 $x,y$，当存在以下情况时无解：

- 若当前字母 $x$ 的值大于某个必须大于当前字母的字母 $y$ 的值且该字母 $y$ 已定为大写，即 $b_y = 1$ 且 $x > y$；

- 若当前字母 $x$ 的值大于某个必须大于当前字母的字母 $y$ 的值且当前字母 $x$ 已定为小写，即 $b_x = 2$ 且 $x > y$；

- 若某个必须大于当前字母的字母 $y$ 已定为大写且当前字母 $x$ 已定为小写，即 $b_x = 2$ 且 $b_y = 1$；

在拓扑排序时，按照拓扑排序的顺序依次遍历所有节点，若当前节点状态为不确定是否要改，则定为大写以方便后续字母的操作。定下当前节点的状态后依次遍历当前节点指向的节点，并根据当前节点的状态定下当前节点指向的节点的状态，并判断是否矛盾，在拓扑排序结束后判断是否有环即可。

最后不要忘记判断若当前字符串是上一个字符串的前缀且当前字符串的长度小于上一个字符串的长度，则当前字符串必定小于上一个字符串，无解。

代码：

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#define MAXN 100005
#define int long long
using namespace std;
//b数组：0为不确定是否要改 1为必须为大写 2为必须为小写 
int n,m,head[MAXN],d[MAXN],cnt,tmp,ans[MAXN],sum,b[MAXN];
vector<int>v[MAXN];
struct Node{
	int value,next;
}adj[MAXN];
void insert(int a,int b){
	tmp++;
	adj[tmp].value=b;
	adj[tmp].next=head[a];
	head[a]=tmp;
}
bool topsort(){ //返回0为无解 返回1为有解 
	cnt=0; 
	queue<int>q;
	for(int i=1;i<=m;i++){
		if(d[i]==0){
			q.push(i);
		}
	}
	while(q.size()){
		int t=q.front();
		cnt++;
		if(b[t]==0){ //若当前字母不确定是否要改 
			b[t]=1;  //则将状态改为大写以方便后面的字母操作 
			sum++;   
			ans[sum]=t;
			for(int i=head[t];i!=0;i=adj[i].next){
				int j=adj[i].value;
				if(j<t){ //若当前字母的值大于某个必须大于当前字母的字母的值 
					if(b[j]==1){ //且该字母已定为大写 
						return 0; //则无解 
					}
					b[j]=2; //该字母必须小写 
				}
			}
		}else{
			for(int i=head[t];i!=0;i=adj[i].next){
				int j=adj[i].value;
				if(j<t){ //若当前字母的值大于某个必须大于当前字母的字母的值
					return 0; //由于当前字母必须为小写，所以当前字母无法小于该字母，无解 
				}else{           //否则 
					if(b[j]==1){ //若某个必须大于当前字母的字母已定为大写 
						return 0;//则当前字母无法小于该字母，无解
					}
					b[j]=2; //该字母必须小写
				}
			}
		}
		q.pop();
		for(int i=head[t];i!=0;i=adj[i].next){
			d[adj[i].value]--;
			if(d[adj[i].value]==0){
				q.push(adj[i].value);
			}
		}
	}
	if(cnt<m)return 0; //若有环，则无解 
	else return 1;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		int l;
		scanf("%lld",&l);
		for(int j=1;j<=l;j++){
			int x; 
			scanf("%lld",&x);
			v[i].push_back(x); 
		}
		if(i>1){ 
			int flag=0,lastl=v[i-1].size(),minn=min(lastl,l);
			for(int j=0;j<minn;j++){
				if(v[i-1][j]!=v[i][j]){ //将两个字符串的第一个不同的字母建边 
					flag=1;
					insert(v[i-1][j],v[i][j]);
					d[v[i][j]]++;
					break;
				}
			}
			if(!flag&&lastl>l){ //若当前字符串是上一个字符串的前缀且当前字符串的长度小于上一个字符串的长度 
				printf("No");   //则当前字符串必定小于上一个字符串，无解 
				return 0;
			}
		}
	}
	if(!topsort()){
		printf("No");
		return 0;
	}
	printf("Yes\n%lld\n",sum);
	for(int i=1;i<=sum;i++){
		printf("%lld ",ans[i]);
	}
	return 0;
} 
```

感谢管理员辛苦审核。

---

## 作者：fighter (赞：9)

# CF875C National Property

## 题意

给定一些字符串，其中字母用数字表示，并且初始是小写的。你可以把一些小写字母改成大写，但同时你要把所有同种字母全部改成大写。问是否能经过一些操作使得最终的字符串序列满足按字典序升序排列。如果能，则需要输出方案。

## 题解

可以发现每种字母只有两种状态：大写或者小写。并且状态受到相邻字符串的大小约束，于是我们可以朝2-SAT的方向思考~~（其实要不是这是我们2-SAT作业题，还真想不到）~~。

我们发现只要能维护好相邻字符串的大小，那么整个序列也就自动排完序了，于是我们仅考虑相邻两个字符串比较的情况。

先判断一种特殊情况：$a[i+1]$是$a[i]$的一个不与$a[i]$相等的前缀。那么显然无论怎么操作，$a[i]$始终大于$a[i+1]$，直接输出0。

那么接下来每一位上就不需要考虑相等的情况了。如果$a[i+1][j]<a[i][j]$，那么显然$a[i][j]$需要变成大写，同时$a[i+1][j]$必须为小写，这样才能满足字典序要求；如果$a[i+1][j]>a[i][j]$，那么当$a[i][j]$是小写时，$a[i+1][j]$必须小写,同时如果$a[i+1][j]$为大写，则$a[i][j]$也为大写。

那么就可以按照上述规则建边，设$u$表示$a[i][j]$大写，$u+n$表示$a[i][j]$小写，$v$表示$a[i+1][j]$大写，$v+n$表示$a[i+1][j]$小写

1. 如果$u<v$：``add(v,u), add(u+n,v+n)``。
2. 如果$u>v$：``add(u+n,u), add(v,v+n)``。

## 代码

建图后一波$tarjan$跑2-SAT搞定。

```cpp
#include <bits/stdc++.h>
#define MAX 200005
using namespace std;

int n, m, cnt, tot;
int len, lst[MAX], a[MAX], col[MAX];
int head[MAX], Next[MAX*2], vet[MAX*2];

void add(int x, int y){
    cnt++;
    Next[cnt] = head[x];
    head[x] = cnt;
    vet[cnt] = y;
}

int low[MAX], dfn[MAX], vis[MAX], T;
stack<int> s;
void tarjan(int x){
    low[x] = dfn[x] = ++T;
    vis[x] = true;
    s.push(x);
    for(int i = head[x]; i; i = Next[i]){
        int v = vet[i];
        if(!dfn[v]){
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if(vis[v]){
            low[x] = min(low[x], dfn[v]);
        }
    }
    if(low[x] == dfn[x]){
        tot++;
        int t = -1;
        while(t != x){
            t = s.top();
            s.pop();
            vis[t] = false;
            col[t] = tot;
        }
    }
}

int main()
{
    cin >> m >> n;
    for(int i = 1; i <= m; i++){
        int t;
        scanf("%d", &t);
        for(int j = 1; j <= t; j++){
            scanf("%d", &a[j]);
        }
        for(int j = 1; j <= min(len, t); j++){
            if(lst[j] < a[j]){
                add(a[j], lst[j]);
                add(lst[j]+n, a[j]+n);
                break;
            }
            else if(lst[j] > a[j]){
                add(lst[j]+n, lst[j]);
                add(a[j], a[j]+n);
                break;
            }
            if(j == min(len, t) && len > t){
                puts("No");
                return 0;
            }
        }
        len = t;
        for(int j = 1; j <= t; j++) lst[j] = a[j];
    }
    
    for(int i = 1; i <= n*2; i++){
        if(!dfn[i]) tarjan(i);
    }
    for(int i = 1; i <= n; i++){
        if(col[i] == col[i+n]){
            puts("No");
            return 0;
        }
    }
    
    puts("Yes");
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(col[i] < col[i+n]){
            ans++;
        }
    }
    cout << ans << endl;
    for(int i = 1; i <= n; i++){
        if(col[i] < col[i+n]){
            printf("%d ", i);
        }
    }
    
    return 0;
}
```



---

## 作者：_yjh (赞：6)

这里提供一个不需要 $2-sat$ 的做法。

显而易见的，若将相邻两个字符串排为升序，则整体必然合法。对于相邻两个字典序不同的字符串，只需对其不同的第一位进行修改即可。分是否升序进行讨论，若升序则说明若修改第二个，第一个则必须修改，否则则说明第一个必须修改，第二个不可修改。

考虑建立两个点 $s,t$。对于必须修改的点 $x$，建边 $s \rightarrow x$，对不可修改的点 $y$，建边 $y \rightarrow t$。若修改点 $x$ 则必须修改点 $y$，则建边 $x \rightarrow y$。

建完图后跑dfs染色，若 $t$ 被染色则说明非法，否则必然合法。

同时莫忘判断靠后的字符串长度短，且前面部分完全相同的情况。

$Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
	ll f=1,x=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll n,m;
bool vis[100005];
vector <int> v[100005];
vector <int> g[100005];
void dfs(int x,int fa) {
	if(vis[x]) return ;
	vis[x]=true;
	for(unsigned int i=0;i<g[x].size();i++) {
		if(g[x][i]==fa) continue;
		dfs(g[x][i],x);
	}
}
int main() {
	n=read();m=read();
	for(int i=1;i<=n;i++) {
		int sum=read();
		for(int j=1;j<=sum;j++) {
			int x=read();
			v[i].push_back(x);
		}
	}
	for(int i=1;i<=n-1;i++) {
		bool chg=false;
		for(unsigned int j=0;j<min(v[i].size(),v[i+1].size());j++) {
			if(v[i][j]==v[i+1][j]) continue;
			if(v[i][j]<v[i+1][j]) {
			    g[v[i+1][j]].push_back(v[i][j]);
			}
			else {
				g[0].push_back(v[i][j]);
				g[v[i+1][j]].push_back(m+1);
			}
			chg=true;
			break;
		}
		if(!chg&&v[i].size()>v[i+1].size()) {
			cout<<"No"<<'\n';
			return 0;
		}
	}
	dfs(0,0);
	if(vis[m+1]) {
		cout<<"No"<<'\n'; 
	}
	else {
		cout<<"Yes"<<'\n';
		ll ans=0;
		for(int i=1;i<=m;i++) if(vis[i]) ans++;
		cout<<ans<<'\n';
		for(int i=1;i<=m;i++) {
			if(vis[i])
			    cout<<i<<' ';
		}
		cout<<'\n';
	}
	return 0;
}

```
谢谢管理员的辛苦审核。

---

## 作者：gdf_yhm (赞：0)

[CF875C](https://www.luogu.com.cn/problem/CF875C)

[Royal Questions](https://codeforces.com/contest/875/problem/F)

### 思路

这种问题是关于多个限制的。

显然，满足 $S_{i-1}\leq S_i$ 即可使整体升序。对于每个 $S_{i-1}\leq S_i$，都需要满足一些限制，只要所有限制前后不矛盾，则输出是。

分析 $S_{i-1}\leq S_i$。枚举位置 $j$ 为第一个两者不等的位置，有几种情况：

- 不存在 $j$。此时如果 $len_{S_{i-1}}\leq len_{S_i}$，则 $S_{i-1}\leq S_i$，没有额外限制。否则 $S_i$ 一定小于 $S_{i-1}$，无解。

- $S_{i-1,j}$ 小于 $S_{i,j}$，则 $S_{i-1}$ 暂时小于 $S_i$，满足条件。此时只要 $S_{i,j}$ 不改，或 $S_{i-1,j}$ 和 $S_{i,j}$ 同时改即可。也就是说，$S_{i,j}$ 如果改了，$S_{i-1,j}$ 必须改。

- $S_{i-1,j}$ 大于 $S_{i,j}$，则 $S_{i-1}$ 暂时大于 $S_i$，不满足条件。此时必须改 $S_{i-1,j}$，$S_{i,j}$ 一定不能改。

由上分析，可以建图解决。

令 $s$ 表示一定改的起点，$t$ 表示一定不改的终点。

情况 $1$ 没有额外要求。情况 $2$ 要求改 $S_{i,j}$ 必须改 $S_{i-1,j}$，即 $S_{i,j}$ 向 $S_{i-1,j}$ 连边。情况 $3$ 要求改 $S_{i-1,j}$，不改 $S_{i,j}$，即 $s$ 向 $S_{i,j}$ 连边，$S_{i-1,j}$ 向 $t$ 连边。

从 $s$ 开始搜索，如果能走到 $t$ 则矛盾，否则能走到的点即为要改的点。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans;
int s,t,cur;
int a[2][maxn];
bool vis[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			dfs(v);
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	s=0;t=m+1;
	for(int i=1;i<=n;i++){
		a[cur][0]=read();
		for(int j=1;j<=a[cur][0];j++){
			a[cur][j]=read();
		}
		if(i!=1){
			for(int j=1;j<=min(a[cur^1][0],a[cur][0]);j++){
				if(a[cur^1][j]>a[cur][j]){
					add(s,a[cur^1][j]);
					add(a[cur][j],t);
					break;
				}
				if(a[cur^1][j]<a[cur][j]){
					add(a[cur][j],a[cur^1][j]);
					break;
				}
				if(j==min(a[cur^1][0],a[cur][0])&&a[cur^1][0]>a[cur][0]){
					printf("No\n");
					return 0;
				}
			}
			
		}
		cur^=1;
	}
	dfs(s);
	if(vis[t]){
		printf("No\n");
	}
	else{
		printf("Yes\n");
		for(int i=1;i<=m;i++)if(vis[i])++ans;
		printf("%lld\n",ans);
		for(int i=1;i<=m;i++)if(vis[i])printf("%lld ",i);
	}
}
```


---

## 作者：Leap_Frog (赞：0)

### P.S.
妙妙题  
[cnblogs 的阅读体验](https://www.cnblogs.com/pealfrog/p/15012727.html)  

### Description.
给定一些字符串，你需要给他们确定大小写，使得字符串字典序递增。　　

### Solution.
首先很显然，递增只需要 $n-1$ 对相邻字符串都满足 $S_{i-1}<S_{i}$。  
那么我们比较相邻字符串，发现必定有一段两个字符串相同。  
我们分类讨论下一位：  
1. 下一位在第一个字符串中不存在——必定成立
2. 下一位在第二个字符串中不存在——必定无解
3. 下一位在两个字符串中都存在——比较复杂，是后文重点解决的问题。  

那么我们现在需要考虑如何计算第三类的答案。  
如果想到了 2-sat，那这题就做完了。  
就考虑分类讨论：
1. $a<b$，那 $a$ 取小写能推出 $b$ 取小写，$b$ 取大写能推出 $a$ 取大写。  
2. $a>b$，那只可能是 $a$ 取大写，$b$ 取小写。  

然后套上 2-sat 模板即可。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
struct edge{int to,nxt;}e[400005];int n,m,et,head[200005];
int buf[200005],*a[100005],ln[100005],tt,st[200005],tp;
int dfn[200005],dt,low[200005],cl[200005],ct;char v[200005];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
inline void add(int x,int y)
{//x表示大写，x+m表示小写，x<y
	if(x<y) adde(x+m,y+m),adde(y,x);
	if(x>y) adde(x+m,x),adde(y,y+m);
}
inline void tarjan(int x)
{
	dfn[x]=low[x]=++dt,v[x]=1,st[++tp]=x;
	for(int i=head[x];i;i=e[i].nxt)
		if(!dfn[e[i].to]) tarjan(e[i].to),low[x]=min(low[e[i].to],low[x]);
		else if(v[e[i].to]) low[x]=min(dfn[e[i].to],low[x]);
	if(dfn[x]==low[x]) {int y=++ct;do v[y=st[tp--]]=0,cl[y]=ct;while(y^x);}
}
int main()
{
	read(n),read(m),a[1]=buf;for(int i=1;i<=n;i++)
	{
		read(ln[i]),a[i+1]=a[i]+ln[i];
		for(int j=1;j<=ln[i];j++) read(a[i][j]);
	}
	for(int i=2;i<=n;i++)
	{
		char fg=1;for(int j=1;j<=ln[i]&&j<=ln[i-1]&&fg;j++)
			if(a[i][j]^a[i-1][j]) add(a[i-1][j],a[i][j]),fg=0;
		if(fg&&ln[i]<ln[i-1]) return puts("No"),0;
	}
	for(int i=1;i<=m+m;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=m;i++) if(cl[i]==cl[i+m]) return puts("No"),0;
	int cnt=0;puts("Yes");for(int i=1;i<=m;i++) if(cl[i]<cl[i+m]) cnt++;
	printf("%d\n",cnt);for(int i=1;i<=m;i++) if(cl[i]<cl[i+m]) printf("%d ",i);
	return putchar('\n'),0;
}
```

---

## 作者：两年打铁 (赞：0)

## 题意
题目中给定n个字符串,m个字符，现在将这些字符用数字来表示。

现在可以将这些数字中的任意几个变成大写，（字符变成大写后小于任何小写的字符，但是两个大写字符按数值进行比较）

## 使得：

### 在变换后，按顺序给定的n个字符串是按字典序升序排列的。

## 分析

每个字符只有小写大写两种状态，可以转换成2-SAT问题。
暴力拆点，第i个点表示i取大写，i+n表示i取小写

由于是升序，所以我们只要处理前后两个字符串，对于每一位：

#### 1.如果当前这一位大于前一个串的这位
那么前面串的这位大写，后面的大写小写都可以，如果后面的大写，前面的就必须大写



#### 2.如果当前这一位小于前一个串的这位
那么前面串的这位必须大写，后面串必须小写



------------

还有就是要特判全部一样但前一个串的长度大

连边就和2-SAT没什么区别了。

```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;

inline void read(int &x)
{
	x=0;
	char ch=getchar();
	int pd=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			pd=-pd;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=pd;
}
inline void write(const int &x)
{
	char ggg[10001];
	int s=0;
	int tmp=x;
	if(tmp==0)
	{
		putchar('0');
		return;
	}
	if(tmp<0)
	{
		tmp=-tmp;
		putchar('-');
	}
	while(tmp>0)
	{
		ggg[s++]=tmp%10+'0';
		tmp/=10;
	}
	while(s>0)
	{
		putchar(ggg[--s]);
	}
}
const int N=3e5+7,M=3e6+7;
int t,h[N],dfn[N],low[N],id[N],num,cnt,cc,ans[N],n,m;
bool vis[N];
int a[2][1000001];
struct dd
{
	int end,nt;
}e[M];
inline void add(int begin,int end)
{
	++t;
	e[t].end=end;
	e[t].nt=h[begin];
	h[begin]=t;
}
stack<int >st;
void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	st.push(x);
	for(register int i=h[x];i;i=e[i].nt)
	{
		int u=e[i].end;
		if(!dfn[u])
		{
			tarjan(u);
			low[x]=min(low[x],low[u]);
		}
		else 
		{
			if(!id[u])
			{
				low[x]=min(low[x],dfn[u]);
			}
		}
	}
	if(dfn[x]==low[x])
	{
		id[x]=++cnt;
		while(st.top()!=x)
		{
			id[st.top()]=cnt;
			st.pop();
		}
		st.pop();
	}
}

void wrl(const int &x)
{
	write(x);
	puts("");
}
void wrs(const int &x)
{
	write(x);
	putchar(' ');
}
int main()
{
	read(m);
	read(n);
	int lasta;
	for(register int i=1;i<=m;++i)
	{
		int aa;
		read(aa);
		int now=(i&1);
		bool flag=false;
		for(register int j=1;j<=aa;++j)
		{
			read(a[now][j]);
			if(i>1&&!flag)
			{
				if(j>lasta)continue;
				if(a[now][j]<a[now^1][j])
				{
					add(a[now^1][j]+n,a[now^1][j]);
					add(a[now][j],a[now][j]+n);
					flag=1;
				}
				if(a[now][j]>a[now^1][j])
				{
					add(a[now^1][j]+n,a[now][j]+n);
					add(a[now][j],a[now^1][j]);
					flag=1;
				}
				if(j==aa&&lasta>aa&&!flag)
				{
					puts("No");
					return 0;
				}
			}
		}
		lasta=aa;
	}
	for(register int i=1;i<=2*n;++i)
	{
		if(!dfn[i])
		{
			tarjan(i);
		}
	}
	for(register int i=1;i<=n;++i)
	{
		if(id[i]==id[i+n])
		{
			puts("No");
			return 0;
		}
		
	}
	puts("Yes");
	int cc=0;
	for(register int i=1;i<=n;++i)
	{
		if(id[i]<id[i+n])
		{
			ans[++cc]=i;
		}
	}
	wrl(cc);
	for(register int i=1;i<=cc;++i)
	{
		wrs(ans[i]);
	}
}










```





---

