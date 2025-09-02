# Fedor and Essay

## 题目描述

After you had helped Fedor to find friends in the «Call of Soldiers 3» game, he stopped studying completely. Today, the English teacher told him to prepare an essay. Fedor didn't want to prepare the essay, so he asked Alex for help. Alex came to help and wrote the essay for Fedor. But Fedor didn't like the essay at all. Now Fedor is going to change the essay using the synonym dictionary of the English language.

Fedor does not want to change the meaning of the essay. So the only change he would do: change a word from essay to one of its synonyms, basing on a replacement rule from the dictionary. Fedor may perform this operation any number of times.

As a result, Fedor wants to get an essay which contains as little letters «R» (the case doesn't matter) as possible. If there are multiple essays with minimum number of «R»s he wants to get the one with minimum length (length of essay is the sum of the lengths of all the words in it). Help Fedor get the required essay.

Please note that in this problem the case of letters doesn't matter. For example, if the synonym dictionary says that word cat can be replaced with word DOG, then it is allowed to replace the word Cat with the word doG.

## 样例 #1

### 输入

```
3
AbRb r Zz
4
xR abRb
aA xr
zz Z
xr y
```

### 输出

```
2 6
```

## 样例 #2

### 输入

```
2
RuruRu fedya
1
ruruRU fedor
```

### 输出

```
1 10
```

# 题解

## 作者：zac2010 (赞：5)

### 思路

这道题很水，常见的套图题。

首先，我们把所有字符串都变成点，可以采用映射或者字典树，后者可以做到时间复杂度和输入规模一样。

接着，我们采用强连通缩点，并设 $f_u$ 为 $u$ 点可以变成的字符串的最小 R 数量，而 $g_u$ 则表示 $u$ 点在 $f_u$ 最小时最小的单词长度。的由于同一个强连通分量的点之间两两可达，所以一个强连通分量变成点后的最小 R 数量就是此强连通分量中每个点 R 数量的最小值。

最后，我们建反图跑有向无环图上动态规划即可，中间转移取他自己的 R 数量和所有能到达他的点中的动态规划数组最小值。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 3e5 + 10; int m, n, totp, tot, top, col, a[N]; ll ans1, ans2;
int stk[N], in[N], vl[N], cl[N], dfn[N], low[N], vis[N], f[N], g[N], ln[N];
queue<int> q; vector<int> eg[N], e[N]; unordered_map<string, int> mp;
void Upd(int x, int fy, int gy){
	if(fy < f[x]) f[x] = fy, g[x] = gy;
	else if(f[x] == fy) g[x] = min(g[x], gy);
}
int get(string s){
	L(i, 0, s.size() - 1) s[i] += (s[i] <= 'Z'? 32 : 0);
	if(mp[s]) return mp[s]; mp[s] = ++totp;
	L(i, 0, s.size() - 1) vl[totp] += (s[i] == 'r');
	ln[totp] = s.size(); return totp;
}
void Tarjan(int u){
	dfn[u] = low[u] = ++tot, vis[stk[++top] = u] = 1; 
	for(int v: eg[u]){
		if(!dfn[v])
			Tarjan(v), low[u] = min(low[u], low[v]);
		else if(vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]){
		col++;
		while(stk[top] != u)
			vis[stk[top]] = 0, cl[stk[top--]] = col;
		vis[u] = 0, cl[stk[top--]] = col;
	}
}
int main(){
	string s, c; scanf("%d", &m);
	L(i, 1, m) cin >> s, a[i] = get(s);
	scanf("%d", &n);
	L(i, 1, n) cin >> s >> c, eg[get(s)].push_back(get(c));
	L(i, 1, totp) if(!dfn[i]) Tarjan(i); L(i, 1, tot) f[i] = g[i] = 1e9;
	L(u, 1, totp){
		Upd(cl[u], vl[u], ln[u]);
		for(int v: eg[u]) if(cl[u] ^ cl[v])
			e[cl[v]].push_back(cl[u]), in[cl[u]]++;
	}
	L(i, 1, tot) if(!in[i]) q.push(i);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v: e[u]){
			in[v]--, Upd(v, f[u], g[u]);
			if(!in[v]) q.push(v);
		}
	}
	L(i, 1, m) ans1 += f[cl[a[i]]], ans2 += g[cl[a[i]]];
	printf("%lld %lld\n", ans1, ans2);
	return 0;
}
```


---

## 作者：LRL65 (赞：4)

这题还可以用一种类似于 $Dijkstra$ 的算法

最开始先将所有的单词变成小写。然后将单词看作点，题目中的同义词间**反向**建边（因为一开始是某单词可以换成某单词，应该变成用某单词换某单词，所以要**反向**建边）。如第一个样例建出的图就应该是这样的：
![](https://cdn.luogu.com.cn/upload/image_hosting/dg62s1vj.png)

每个节点应该有两个权值，一个是单词中 $r$ 的数量，一个是单词的长度。然后我们就要运用 $Dijkstra$ 的思想：
1. 首先将所有点和权值塞入单调队列，其中单调队列是以 $r$ 数量最少，然后长度最短排序的。
1. 弹出最上面的那个点（也就是 $r$ 数量最少，长度最短的），然后将它所有的邻点的权值都赋成它的权值。因为是单向的，所以在赋值时要**判断一下这个点权值是否比邻点小**，有可能会出现这种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/khvdjxc6.png)

最后只需要将文章中的所有单词 $r$ 的数量和，和总长度打出来即可。

本题还是有一定细节的，要小心。**比如要开 `long long`。**

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,cnt=0,name[100005];
string a,b1,b2;
map<string,int>mp;
class node{
    public:
        int r,len,name;
    bool operator < (const node & n) const {
        if(r==n.r)return len>n.len;
        else return r>n.r;
    } 
};
struct edge {
	int r,len;
}c[100005];
priority_queue<node>q;
vector<int>e[100005]; 
bool vis[100005];
void dijkstra(){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=cnt;i++) {
    	node t;
    	t.r=c[i].r;
    	t.len=c[i].len;
    	t.name=i;
    	q.push(t);
    }
    while(!q.empty()) {
        int now=q.top().name; 
        q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(int i=0;i<e[now].size();i++) {
            int v=e[now][i];
            if(c[v].r>c[now].r||(c[v].r==c[now].r&&c[v].len>c[now].len))c[v]=c[now];
            node t;
            t.r=c[v].r;
            t.len=c[v].len;
            t.name=v;
            q.push(t);
        }
    }
}
int main() {
	cin>>m;
	for(int i=1;i<=m;i++) {
		cin>>a;
		int sum=0;
		for(int j=0;j<a.size();j++) {
			if(a[j]>='A'&&a[j]<='Z')a[j]+='a'-'A';
			if(a[j]=='r')sum++;
		}
		if(!mp[a])mp[a]=++cnt,c[cnt].r=sum,c[cnt].len=a.size();
		name[i]=mp[a];
	}	
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>b1>>b2;
		int sum=0;
		for(int j=0;j<b1.size();j++) {
			if(b1[j]>='A'&&b1[j]<='Z')b1[j]+='a'-'A';
			if(b1[j]=='r')sum++;
		}
		if(!mp[b1])mp[b1]=++cnt,c[cnt].r=sum,c[cnt].len=b1.size();
		sum=0;
		for(int j=0;j<b2.size();j++) {
			if(b2[j]>='A'&&b2[j]<='Z')b2[j]+='a'-'A';
			if(b2[j]=='r')sum++;
		}
		if(!mp[b2])mp[b2]=++cnt,c[cnt].r=sum,c[cnt].len=b2.size();
		e[mp[b2]].push_back(mp[b1]);
	}
    /*for(int i=1;i<=m;i++) {
		cout<<c[name[i]].r<<" "<<c[name[i]].len<<endl;
	}*/
	dijkstra();
	long long ans1=0,ans2=0;
	for(int i=1;i<=m;i++) {
		ans1+=c[name[i]].r;
		ans2+=c[name[i]].len;
	}
    /*for(int i=1;i<=m;i++) {
		cout<<c[name[i]].r<<" "<<c[name[i]].len<<endl;
	}*/
	cout<<ans1<<" "<<ans2<<endl;
}
```


---

## 作者：是青白呀 (赞：3)

为什么是清一色的缩点？提供一个只需要 dfs 的做法。

同样地，我们把每个字符串都看成一个点，并从 $y_i$ 向 $x_i$ 连边（也就是连反边）。此时，若点 $u$ 可以走到点集 $S_u$ 中的所有点，则 $S_u$ 中的所有点都可以变换成 $u$ 对应的字符串。

我们把每个点按照其对应的字符串，以其中 `R` 字符的数量为第一关键字、其长度为第二关键字从小到大排序。由于每个单词的转换是独立的，并且 $r$ 越小越好、长度越短越好，于是我们可以按照排序后的顺序，依次以每个点为起点在图上进行 dfs。途中遍历到的所有未被标记答案的点，它们最优的变换终点的字符串都应该是当前 dfs 的起点对应的字符串。在 dfs 的过程中标记答案即可。

最终把 $n$ 个单词对应的数据加和即为答案。

### Code
```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define lowbit(x) x&(-x)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second 
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=2e5+5,mo=998244353,inf=1e18+7,bs=19491001;
const double eps=1e-8;
inline void read(int &p){
	int x=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m;
struct word{
	int id,numr,len;
	friend bool operator<(word x,word y){
		if(x.numr==y.numr)return x.len<y.len;
		else return x.numr<y.numr;
	}
}w[N];
int nid[N];
map<string,int>sid;
int cnts,targ[N];
void init(string &s){
	rep(i,0,(int)s.size()-1)
	    if(s[i]>='A'&&s[i]<='Z')s[i]+='a'-'A';
}
void count(string s){
	int cnt=0;
	rep(i,0,(int)s.size()-1)
	    if(s[i]=='r')cnt++;
	w[sid[s]]=(word){sid[s],cnt,(int)s.size()};
}
struct edge{
	int to,nxt;
}e[N];
int fir[N],np;
void add(int x,int y){
	e[++np]=(edge){y,fir[x]};
	fir[x]=np;
}
int ans[N];
void dfs(int x){
	for(int i=fir[x];i;i=e[i].nxt){
		int j=e[i].to;
		if(ans[j])continue;
		ans[j]=ans[x],dfs(j);
	}
}
signed main(){
	read(n);
	rep(i,1,n){
		string s;
		cin>>s,init(s);
		if(!sid[s])sid[s]=++cnts,count(s);
		targ[i]=sid[s];
	}
	read(m);
	rep(i,1,m){
		string x,y;
		cin>>x,init(x),cin>>y,init(y);
		if(!sid[x])sid[x]=++cnts,count(x);
		if(!sid[y])sid[y]=++cnts,count(y);
		add(sid[y],sid[x]);
	}
	sort(w+1,w+cnts+1);
	rep(i,1,cnts)
	    nid[w[i].id]=i;
	rep(i,1,cnts)
	    if(!ans[w[i].id])ans[w[i].id]=w[i].id,dfs(w[i].id);
	int sumr=0,len=0;
	rep(i,1,n)
	    sumr+=w[nid[ans[targ[i]]]].numr,len+=w[nid[ans[targ[i]]]].len;
	printf("%lld %lld\n",sumr,len);
	return 0;
}
```

---

## 作者：MWL_wma (赞：2)

### 思路
通过拓扑将含 `r` 或 `R` 较少的赋值给含 `r` 或 `R` 较多的即可。

然而又环会让拓扑难以完成，故 Tarjan 缩点是最好的方式。

---
### 细节
首先，使用 `map` 将字符串转化为数字，注意第 $4$ 至 $2+m$ 行均要转化。  
方便起见，建议大写转小写。

然后缩点。只要对第 $2$ 行中输入的字符串数，及其能转化的字符串进行缩点即可。  
存下强连通分量含第 $2$ 行中输入的字符串数 $\operatorname{cor}$，最小含 `r` 数 $\operatorname{mnr}$，含 `r` 最少时最短长度 $\operatorname{mnl}$。

建边。方便起见，反向建。

拓扑。

由于处于同一强连通分量的两点可互相抵达，故设两答案为 $\operatorname{ans_1}$，$\operatorname{ans_2}$，则
$$\operatorname{ans_1}=\operatorname{cor}\times \operatorname{mnr}$$
$$\operatorname{ans_2}=\operatorname{cor}\times \operatorname{mnl}$$

---
### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,c;
map<string,int>mp;
int f[300002];
int cr[300002],cl[300002];
vector<int>e[300002],E[300002];
int dfn[300002],low[300002];
bool vis[300002];
int st[300002],top;
int tot;
int mnr[300002],mnl[300002],cor[300002];
bool in[300002];
void tarjan(int u){
	dfn[u]=low[u]=++c;
	st[++top]=u;
	vis[u]=1;
	for(int v:e[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		++tot;
		while(1){
			int t=st[top--];
			vis[t]=0;
			f[t]=tot;
			if(cr[t]<mnr[tot]){
				mnr[tot]=cr[t];
				mnl[tot]=cl[t];
			}else if(cr[t]==mnr[tot]){
				mnl[tot]=min(mnl[tot],cl[t]);
			}
			if(t<=n){
				++cor[tot];
			}
			if(t==u){
				break;
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		cl[i]=s.length();
		for(int j=0;j<cl[i];j++){
			if(s[j]<'a'){
				s[j]+=32;
			}
			if(s[j]=='r'){
				++cr[i];
			}
		}
		mp[s]=++t;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		string x,y;
		cin>>x>>y;
		int lx=x.length(),ly=y.length();
		for(int j=0;j<lx;j++){
			if(x[j]<'a'){
				x[j]+=32;
			}
		}
		for(int j=0;j<ly;j++){
			if(y[j]<'a'){
				y[j]+=32;
			}
		}
		if(!mp[x]){
			mp[x]=++t;
			cl[mp[x]]=lx;
			for(int j=0;j<cl[mp[x]];j++){
				if(x[j]=='r'){
					++cr[mp[x]];
				}
			}
		}
		if(!mp[y]){
			mp[y]=++t;
			cl[mp[y]]=y.length();
			for(int j=0;j<cl[mp[y]];j++){
				if(y[j]=='r'){
					++cr[mp[y]];
				}
			}
		}
		e[mp[x]].push_back(mp[y]);
	}
	memset(mnr,0x3f,sizeof mnr);
	memset(mnl,0x3f,sizeof mnl);
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=t;i++){
		if(f[i]){
			for(auto v:e[i]){
				if(f[i]!=f[v]&&f[v]){
					E[f[v]].push_back(f[i]);
					in[f[i]]=1;
				}
			}
		}
	}
	queue<int>q;
	for(int i=1;i<=tot;i++){
		if(!in[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int t=q.front();
		q.pop();
		for(auto v:E[t]){
			if(mnr[v]>mnr[t]){
				mnr[v]=mnr[t];
				mnl[v]=mnl[t];
			}else if(mnr[t]==mnr[v]){
				mnl[v]=min(mnl[t],mnl[v]);
			}
		}
	}
	long long ans1=0,ans2=0;
	for(int i=1;i<=tot;i++){
		ans1+=cor[i]*mnr[i];
		ans2+=cor[i]*mnl[i];
	}
	printf("%d %d",ans1,ans2);
	return 0;
} 
```

---

## 作者：CoderCharlie (赞：2)

### 题意
给定 $n$ 个字符串 $s_1,s_2,\ldots,s_n$ 和 $m$ 个替换关系，现在想要进行若干次替换，使得替换后的 $n$ 个字符串含 `r` 数量最小。在含 `r` 数量最小的同时也要保证字符串长度总和最小。

### 解题思路
这里考虑反向建边，将题目中「把 $x$ 替换成 $y$」的关系转化成「用 $y$ 替换 $x$」

例如建出这样的一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gnew9i8t.png)

图中，`a` 的代价最小，所以我们从它开始 dfs，将其所能到达的点全部替换，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4i6b7f69.png)

同理，以此类推，直到全部替换完成，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3olhmij2.png)

然后把原来的文章逐一进行替换即可。

### 注意事项
* 字符串替换**不区分大小写**，所以可以预先把所以读进来的字符串全部转成小写。

* 在统计答案时需要开 long long。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string s[500100];
pair<pair<int,int>,string> p[500100];
map<string,bool> h;
map<string,vector<string> > a;
map<string,pair<int,int> > index;
string lower(string s)
{
	for (int i=0;i<s.size();i++)
		if (s[i]>='A'&&s[i]<='Z') s[i]+=32;
	return s;
}
int cntR(string s)
{
	int ret=0;
	for (int i=0;i<s.size();i++)
		if (s[i]=='r') ret++;
	return ret;
}
void dfs(string u,pair<int,int> val)
{
	if (h[u]) return;
	h[u]=1;
	index[u]=val;
	for (auto i:a[u])
		dfs(i,val);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,cnt=0;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>s[i];
		s[i]=lower(s[i]);
	}
	cin>>m;
	for (int i=1;i<=m;i++)
	{
		string u,v;
		cin>>u>>v;
		u=lower(u);
		v=lower(v);
		a[v].push_back(u);
		if (!h[u])
		{
			cnt++;
			p[cnt]=make_pair(make_pair(cntR(u),u.size()),u);
			h[u]=1;
		}
		if (!h[v])
		{
			cnt++;
			p[cnt]=make_pair(make_pair(cntR(v),v.size()),v);
			h[v]=1;
		}
	}
	sort(p+1,p+cnt+1);
	h.clear();
	for (int i=1;i<=cnt;i++)
		if (!h[p[i].second]) dfs(p[i].second,p[i].first);
	ll ans1=0,ans2=0;
	for (int i=1;i<=n;i++)
	{
		if (index[s[i]]==make_pair(0,0)) index[s[i]]=make_pair(cntR(s[i]),s[i].size());
		ans1+=index[s[i]].first;
		ans2+=index[s[i]].second;
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

---

## 作者：Minakami_Yuki (赞：2)

字符串太菜了。

# 题目链接

[(Luogu) CF467D Fedor and Essay](https://www.luogu.org/problem/CF467D)

# 题意简述

给你一篇文章和n对单词，可以将文中的单词按对应对换。

求对换后文章含字母'r'的最小数量，以及此时文章中所有单词长度之和的最小值。

<!--more-->

# 解题思想

单词可以看成点，然后每个单词含'r'的数量可以理解为其点权。

我们按对应关系建图后，对该图缩点，然后每个节点跑一遍树形DP，统计一下自底向上统计最小值。

懒得写哈希了，所以用了map。没想到已经是最优解了。

用哈希理论上会跑更快，~~但是出题人可能闲得无聊构造了哈希冲突~~

对于文章长度最小值，我们可以在DP时判一下两个DP值相等的情况，然后取$\min$就行了。

设$minn1[i]$为对应图上到单词$i$为止所有单词'r'的最小值，$minn2[i]$为对应图上到单词$i$位置符合题目条件的文章长度的最小值。

那么两个答案分别为：$ans_1 = \sum\limits_{1\le i\le n} minn1[scc[i]], ans_2 = \sum\limits_{1\le i\le n}minn2[scc[i]]$

要开**long long**

# 参考代码

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>
#include <map>

std::map <std::string, int> mp;

namespace FastIO {
	inline int read() {
		char ch = getchar(); int r = 0, w = 1;
		while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
		while(isdigit(ch)) {r = r * 10 + ch - '0', ch = getchar();}
		return r * w;
	}
	void _write(long long x) {
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) _write(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write(long long x) {
		_write(x);
		putchar(' ');
	}
}

using namespace FastIO;

const int N = 3e5 + 6;
const int M = N << 2;

template <typename T> inline T min(T a, T b) {return a < b ? a : b;}
template <typename T> inline T max(T a, T b) {return a > b ? a : b;}

char ch[M];
long long ans1, ans2;
int n, m, sz;
int ver[N], nxt[M], head[M], cnt, Cnt;
int Ver[N], Nxt[M], Head[M];
int scc[N], dfn[N], low[N], idx, tot;
int sta[N], stop;
int id[N], num[N], len[N];
int minn1[N], minn2[N];
bool v[N], vis[N];

inline void add(int x, int y) {
	ver[++cnt] = y, nxt[cnt] = head[x], head[x] = cnt;
}

inline void Add(int x, int y) {
	Ver[++cnt] = y, Nxt[cnt] = Head[x], Head[x] = cnt;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++idx;
	v[x] = 1;
	sta[++stop] = x;
	for(register int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if(v[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	int now = 0;
	if(low[x] == dfn[x]) {
		tot++;
		while(now != x) {
			now = sta[stop--];
			v[now] = 0;
			scc[now] = tot;
			if(num[now] < minn1[tot] || (num[now] == minn1[tot] && len[now] < minn2[tot])) {
				minn1[tot] = num[now], minn2[tot] = len[now];
			}
		}
	}
}

inline void rebuild() {
	cnt = 0;
	for(register int x = 1; x <= sz; x++) {
		for(register int i = head[x]; i; i = nxt[i]) {
			int y = ver[i];
			if(scc[x] != scc[y]) Add(scc[x], scc[y]);
		}
	}
}

void dp(int x) {
	if(vis[x]) return;
	vis[x] = 1;
	for(register int i = Head[x]; i; i = Nxt[i]) {
		int y = Ver[i];
		dp(y);
		if(minn1[y] < minn1[x]) {
			minn1[x] = minn1[y];
			minn2[x] = minn2[y];
		}
		else if(minn1[y] == minn1[x]) {
			minn2[x] = min(minn2[x], minn2[y]);
		}
	}
}

int main() {
	n = read();
	for(register int i = 1; i <= n; i++) {
		scanf("%s", ch);
		int l = strlen(ch), k = 0;
		for(register int j = 0; j < l; j++) {
			if(ch[j] >= 'A' && ch[j] <= 'Z') ch[j] = ch[j] - 'A' + 'a';
			if(ch[j] == 'r') k++;
		}
		int t = mp[ch]; if(!t) t = mp[ch] = ++sz; len[t] = l; num[t] = k;
		id[i] = t;
	}
	m = read();
	for(register int i = 1; i <= m; i++) {
		scanf("%s", ch);
		int l = strlen(ch), k = 0;
		for(register int j = 0; j < l; j++) {
			if(ch[j] >= 'A' && ch[j] <= 'Z') ch[j] = ch[j] - 'A' + 'a';
			if(ch[j] == 'r') k++;
		}
		int x = mp[ch]; if(!x) x = mp[ch] = ++sz; len[x] = l; num[x] = k;
		scanf("%s", ch);
		l = strlen(ch), k = 0;
		for(register int j = 0; j < l; j++) {
			if(ch[j] >= 'A' && ch[j] <= 'Z') ch[j] = ch[j] - 'A' + 'a';
			if(ch[j] == 'r') k++;
		}
		int y = mp[ch]; if(!y) y = mp[ch] = ++sz; len[y] = l; num[y] = k;
		add(x, y);
	}
	memset(minn1, 0x3f, sizeof(minn1));
	memset(minn2, 0x3f, sizeof(minn2));
	for(register int i = 1; i <= sz; i++) if(!dfn[i]) tarjan(i);
	rebuild();
	for(register int i = 1; i <= tot; i++) dp(i);
	for(register int i = 1; i <= n; i++) {
		ans1 += minn1[scc[id[i]]];
		ans2 += minn2[scc[id[i]]];
	}
	write(ans1);
	write(ans2);
	return 0;
}
```



---

## 作者：zyn0309 (赞：1)

# CF467D Fedor and Essay
[题目传送门](https://codeforces.com/problemset/problem/467/D)
## 思路
将每一个字符串哈希，然后每个不同的哈希值对应一个点。每个对应点都开一个 pair，第一维是该串中 R 的个数，第二维是该串的长度。若串 $x$ 可以变成串 $y$，则把 $x$ 的对应点向 $y$ 的对应点连一条边。

将对应点建出来的图缩点，其中每个强连通分量的权值就是里面所有点以第一维优先的最小值。对缩点后的图拓扑排序，每个点的 pair 的值是它能够到达的所有点的最小值。最后答案将 $n$ 个文章中的串的对应点所在的强连通分量的 pair 加起来即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define pb push_back
#define pii  pair<int,int> 
#define mk make_pair
using namespace std;
const int N=1e6+10;
int n,m,color[N],p[N],cnt,tot,len,color_cnt,in[N],dfn[N],low[N];
pii a[N],a2[N];
vector<int>e[N],e2[N];
unordered_map<ull,int>mp; 
string s[N];
inline pii change(string &s){
	int cnt=0;
	for(int i=0;i<(int)s.size();++i){
	  if(s[i]>='a'&&s[i]<='z')s[i]-='a'-'A';
	  if(s[i]=='R')++cnt;
	}
	return mk(cnt,s.size());
}
inline ull hashs(string s){
	ull res=0,p=10007;
	for(char c:s)res=res*p+c;
	return res;
}
inline void dfs(int u){
	dfn[u]=low[u]=++cnt;
	in[u]=1;
	p[++len]=u;
	for(auto v:e[u]){
	  if(!dfn[v]){
	  	dfs(v);
	  	low[u]=min(low[u],low[v]);
	  }
	  else if(in[v])low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
	  ++color_cnt;
	  a2[color_cnt]=a[u];
	  while(p[len]!=u){
	  	in[p[len]]=0;
	  	color[p[len]]=color_cnt;
	  	if(a[p[len]].first<a2[color_cnt].first||(a[p[len]].first==a2[color_cnt].first&&a[p[len]].second<a2[color_cnt].second))
		  a2[color_cnt]=a[p[len]];
	  	--len;
	  }
	  in[p[len]]=0;
	  color[p[len]]=color_cnt;
	  if(a[p[len]].first<a2[color_cnt].first||(a[p[len]].first==a2[color_cnt].first&&a[p[len]].second<a2[color_cnt].second))
		a2[color_cnt]=a[p[len]];
	  --len;
	}
}
inline void topusort(){
	queue<int>q;
	for(int i=1;i<=color_cnt;++i)if(!in[i])q.push(i);
	while(q.size()){
	  int u=q.front();
	  q.pop();
	  for(auto v:e2[u]){
	  	--in[v];
	  	if(!in[v])q.push(v);
	  	if(a2[u].first<a2[v].first||(a2[u].first==a2[v].first&&a2[u].second<a2[v].second))a2[v]=a2[u];
	  }
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
	  cin>>s[i];
	  pii id=change(s[i]);
	  ull ha=hashs(s[i]);
	  if(mp.find(ha)==mp.end()){
	    mp[ha]=++tot;
	    a[tot]=id;
	  }
	}
	string s1,s2;
	cin>>m;
	for(int i=1;i<=m;++i){
	  cin>>s1>>s2;
	  pii id=change(s1);
	  ull ha=hashs(s1);
	  if(mp.find(ha)==mp.end()){
	    mp[ha]=++tot;
	    a[tot]=id;
	  }
	  id=change(s2);
	  ull ha2=hashs(s2);
	  if(mp.find(ha2)==mp.end()){
	    mp[ha2]=++tot;
	    a[tot]=id;
	  }
	  e[mp[ha]].pb(mp[ha2]);
	}
	for(int i=1;i<=tot;++i)if(!dfn[i])dfs(i);
	for(int i=1;i<=tot;++i){
	  for(auto v:e[i]){
	  	if(color[i]!=color[v]){
		  e2[color[v]].pb(color[i]);
		  ++in[color[i]];
		}
	  }
	}
	topusort();
	pii ans=mk(0,0);
	for(int i=1;i<=n;++i){
	  ull ha=hashs(s[i]);
	  ans.first+=a2[color[mp[ha]]].first;
	  ans.second+=a2[color[mp[ha]]].second;
	}
	cout<<ans.first<<" "<<ans.second<<"\n";
	return 0;
}
```

---

## 作者：无钩七不改名 (赞：1)

直接建图，把每个单词当做一个点，用 map 记录其对应的点的编号方便简便，并记录原字符串每个单词对应的编号，注意不区分大小写。记录第 $i$ 个单词字母 ``r`` 数量为 $r_i$，长度为 $l_i$。对每个字符串能变成的字符串建一条有向边。

先用 tarjan 进行缩点，得到 DAG。然后对原字符串每个单词进行记忆化搜索，用当前点能到的每个点更新 $c_i$ 的最小值和在此情况下 $l_i$ 的最小值。如果点 $j$ 访问过了，直接返回 $c_i,l_i$ 即可。最后累加结果。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=300005;

int n,cntt,m;
int a[N],sz[N],r[N];
map<string,int> mp;
vector<int> g[N],ng[N];
long long ans1,ans2;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int dfn[N],low[N],num;
int st[N],tp,ins[N];
int c[N],cnt,cr[N],siz[N];

void tarjan(int x){
	dfn[x]=low[x]=++num;
	st[++tp]=x;ins[x]=1;
	for(int v:g[x]){
		if(!dfn[v]){
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else if(ins[v])low[x]=min(low[x],dfn[v]);
	}
	if(dfn[x]==low[x]){
		++cnt;int y;
		cr[cnt]=r[x];
		siz[cnt]=sz[x];
		do{
			y=st[tp--];c[y]=cnt;ins[y]=0;
			if(r[y]<cr[cnt])cr[cnt]=r[y],siz[cnt]=sz[y];
			else if(r[y]==cr[cnt]&&siz[cnt]>sz[y])siz[cnt]=sz[y];
		}while(x!=y);
	}
	return;
}

bool vis[N];
pair<int,int> dfs(int x){
	if(vis[x])return {cr[x],siz[x]};
	vis[x]=1;
	for(int v:ng[x]){
		pair<int,int> p=dfs(v);
		if(p.first<cr[x])cr[x]=p.first,siz[x]=p.second;
		else if(p.first==cr[x]&&siz[x]>p.second)siz[x]=p.second;
	}
	return {cr[x],siz[x]};
}

int main(){
	n=read();
	for(int i(1);i<=n;++i){
		string s;cin>>s;
		int len=s.size();
		for(int j(0);j<len;++j)
			if(s[j]<='Z')s[j]=s[j]-'A'+'a';
		int p=mp[s];
		if(!p){
			p=mp[s]=++cntt;
			sz[p]=len;
			for(int j(0);j<len;++j)
				if(s[j]=='r')++r[p];
		}
		a[i]=p;
	//	cout<<r[i]<<' ';
	}
	m=read();
	for(int i(1);i<=m;++i){
		string s;cin>>s;
		int len=s.size();
		for(int j(0);j<len;++j)
			if(s[j]<='Z')s[j]=s[j]-'A'+'a';
		int p=mp[s];
		if(!p){
			p=mp[s]=++cntt;
			sz[p]=len;
			for(int j(0);j<len;++j)
				if(s[j]=='r')++r[p];
		}
		int x=p;
		cin>>s;len=s.size();
		for(int j(0);j<len;++j)
			if(s[j]<='Z')s[j]=s[j]-'A'+'a';
		p=mp[s];
		if(!p){
			p=mp[s]=++cntt;
			sz[p]=len;
			for(int j(0);j<len;++j)
				if(s[j]=='r')++r[p];
		}
		g[x].push_back(p);
	}
	//cout<<cntt<<'\n';
	for(int i(1);i<=cntt;++i)if(!dfn[i])tarjan(i);
//	for(int i(1);i<=cnt;++i)cout<<": "<<cr[i]<<"&"<<siz[i]<<'\n';
	for(int i(1);i<=cntt;++i)
		for(int v:g[i])if(c[i]!=c[v])ng[c[i]].push_back(c[v]);
	for(int i(1);i<=n;++i){
		//cout<<a[i]<<": "<<c[a[i]]<<'\n';
		pair<int,int> p=dfs(c[a[i]]);
		ans1+=p.first,ans2+=p.second;
	}
	printf("%lld %lld",ans1,ans2);
	return 0;
}
```


---

## 作者：Epoch_L (赞：1)

## Solution
先连边 $x\to y$，得到一个有向图，再 tarjan 缩点，则每个强连通分量中可以两两互换，算出最小的 `r` 数量以及在此前提下最小长度，分别记为 $f_i$ 和 $g_i$。

缩点后得到 DAG，每个节点能到达的所有点就是其能被换成的所有单词，然后 dfs 对每个点算出其最优的 $f_i$ 和 $g_i$ 即可。

也可以对 DAG 建反图，拓扑排序 + dp，然后分情况取最小值，都是老套路了。

统计答案时累加每个单词所在 DAG 中的节点编号的 $f$ 和 $g$ 即可。

一些细节及技巧：

+ 用 map 或 hash 给每个单词编号。
+ 重复计算尽量写函数。
+ 原编号和 DAG 上的编号别弄反了。

## Code
代码压行有点猛，仅供参考。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=5e5+7;
map<string,int>mp;
string t[N];
int dfn[N],low[N],stk[N],dfn_cnt,top,sc,scc[N],in[N];
bool in_stk[N];
int n,m,cnt,len[N],r[N],f[N],g[N];
vector<int>edge[N];
vector<int>E[N];
void trans(string &a){for(int i=0;i<a.size();i++)if(a[i]>='A'&&a[i]<='Z')a[i]+=32;}
void tarjan(int u){
  dfn[u]=low[u]=++dfn_cnt;stk[++top]=u;in_stk[u]=1;
  for(int v:edge[u]){
    if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
    else if(in_stk[v])low[u]=min(low[u],dfn[v]);
  }
  if(dfn[u]==low[u]){
    ++sc;
    do{
      int x=stk[top];
      scc[x]=sc;
      if(r[x]<f[sc])f[sc]=r[x],g[sc]=len[x];
      else if(r[x]==f[sc])g[sc]=min(g[sc],len[x]);
      in_stk[x]=0;top--;
    }while(stk[top+1]!=u);
  }
}
void rebuild(){for(int i=1;i<=cnt;i++)for(int j:edge[i])if(scc[i]!=scc[j])E[scc[j]].pb(scc[i]),in[scc[i]]++;}
queue<int>q;
void topsort(){
  for(int i=1;i<=sc;i++)if(!in[i])q.push(i);
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int v:E[u]){
      if(f[u]<f[v])f[v]=f[u],g[v]=g[u];
      else if(f[u]==f[v])g[v]=min(g[v],g[u]);
      if(--in[v]==0)q.push(v);
    }
  }
}
void doit(int x,string a){
  len[x]=a.size();
  for(int i=0;i<a.size();i++)if(a[i]=='r')r[x]++;
}
main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  memset(f,63,sizeof f);
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>t[i];trans(t[i]);
    if(!mp.count(t[i]))mp[t[i]]=++cnt,doit(cnt,t[i]);
  }
  cin>>m;
  for(int i=1;i<=m;i++){
    string a,b;
    cin>>a>>b;trans(a);trans(b);
    if(!mp.count(a))mp[a]=++cnt,doit(cnt,a);
    if(!mp.count(b))mp[b]=++cnt,doit(cnt,b);
    edge[mp[a]].pb(mp[b]);
  }
  for(int i=1;i<=cnt;i++)if(!dfn[i])tarjan(i);
  rebuild();topsort();
  int ans1=0,ans2=0;
  for(int i=1;i<=n;i++)ans1+=f[scc[mp[t[i]]]],ans2+=g[scc[mp[t[i]]]];
  cout<<ans1<<' '<<ans2<<endl;
  return 0;
}
```

---

## 作者：xukehg (赞：0)

简单题。

看到字符串马上离散化，然后考虑建图，把 $m$ 个条件抽象成建边。如果一个点在强连通分量中，则它可以取到整个强连通分量中权值最小的答案，因此缩点，一个强连通分量的权值就是强连通分量上的点的权值的最小值。

缩点之后问题转变为对于每一个作文上的单词，可以在新图中走到的权值最小的位置的权值和，考虑记忆化搜索即可。

在实现中，为了省事，将单词的权值定义为 r 的数量乘一个极大值加字符串长度，输出变为答案总和除极大值和模极大值。

[记录](https://codeforces.com/contest/467/submission/288701002):
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5,bas = 1e12;

int n,m,tott;
int a[N * 10],num[N];
vector<int> e[N];
map<string,int> mp;
pair<string,int> get(string s){
	int cnt = 0;
	for (int j = 0;j < s.size();j++){
		if ('A' <= s[j] && s[j] <= 'Z') s[j] = (char)(s[j] - 'A' + 'a');
		cnt += (s[j] == 'r');
	} 
	return {s,cnt};
}
string s,s1,s2;
namespace Tarjan{
	int top,tot,scc_siz;
	int dfn[N],low[N],stk[N],instk[N],siz[N],scc[N],calc[N];
	vector<int> e2[N];
	int deg[N];
	struct node{
		int u,v;
	}edge[N];
	void tarjan(int u){
		dfn[u] = low[u] = ++tot;stk[++top] = u;instk[u] = 1;
		for (int v : e[u]){
			if (!dfn[v]){
				tarjan(v);
				low[u] = min(low[u],low[v]);
			}
			else if (instk[v]) low[u] = min(low[u],dfn[v]);
		}
		if (dfn[u] == low[u]){
			int y;scc_siz++;
			do{
				y = stk[top--];instk[y] = 0;
				calc[scc_siz] = min(calc[scc_siz],num[y]),scc[y] = scc_siz,siz[scc_siz]++;
			}while (y != u);
		}
	}
	void shrink_point(){
		memset(calc,0x3f,sizeof(calc));
		for (int i = 1;i <= tott;i++) if (!dfn[i]) tarjan(i);
		for (int i = 1;i <= m;i++){	
			if (scc[edge[i].u] != scc[edge[i].v]){
				deg[scc[edge[i].v]]++;
				e2[scc[edge[i].u]].push_back(scc[edge[i].v]);
			}
		}
	}
}using namespace Tarjan;
int dp[N * 10];
int dfs(int u,int cnt){
	cnt = min(cnt,calc[u]);
	if (dp[u]) return min(cnt,dp[u]);
	dp[u] = calc[u];
	for (int v : e2[u]){
		dfs(v,cnt);
		dp[u] = min(dp[u],dp[v]);
	}
	return dp[u];
}
signed main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for (int i = 1,cnt;i <= n;i++){
		cin >> s;pair<string,int> x = get(s);s = x.first,cnt = x.second;
		if (!mp[s]) mp[s] = ++tott;
		a[i] = mp[s],num[a[i]] = cnt * bas + s.size();
	}cin >> m;
	for (int i = 1,num1,num2,cnt1,cnt2;i <= m;i++){
		cin >> s1 >> s2;pair<string,int> x = get(s1);s1 = x.first,cnt1 = x.second;x = get(s2);s2 = x.first,cnt2 = x.second;
		if (!mp[s1]) mp[s1] = ++tott;if (!mp[s2]) mp[s2] = ++tott;num1 = mp[s1],num2 = mp[s2];
		e[num1].push_back(num2);
		num[num1] = cnt1 * bas + s1.size();num[num2] = cnt2 * bas + s2.size();
		edge[i] = {num1,num2};
	}shrink_point();
	int ans = 0;
	for (int i = 1;i <= n;i++) ans += dfs(scc[a[i]],0x3f3f3f3f3f3f3f3f);
	cout << ans / bas << " " << ans % bas;
}
```

---

## 作者：yangshengyu0719 (赞：0)

# 前言
这题唯一的难点是读题，一个优质的翻译器可以帮你轻松过掉此题，一个脑残的翻译器能让你在样例卡二十分钟（别问我怎么知道的）。拿出你的翻译器，翻译一下输入格式第二段，如果它告诉你“单词 $x_i$ 可以被单词 $y_i$ 替换（**反之亦然**）。”那么恭喜你中奖了，这边建议更换翻译器。事实上，它的本意是说只能“单词 $x_i$ 可以被单词 $y_i$ 替换（**反之不行**）。”

# 思路
由前言可想到，我们可以把字符串哈希一下当作一些点，把替换关系当作一些单向边，由此建成一个有向图，每个原文的单词 $A$ 替换为这个单词在图中能到达的 $R$ 出现最少的前提下长度最短的单词即可。对于同一个个强连通分量的单词，它们一定可以互相转换。所以我们考虑缩点然后拓扑，每个单词 $A$ 则被替换为 $A$ 所在强连通分量及其的后继强连通分量中的 $R$ 数量最小的单词。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,word[N],tot;
int DFN[N],Low[N],sign;
int st[N],top,ins[N],scc,bl[N],Min[N],len[N];
int ind[N],ans1,ans2;
vector<int> E[N],E2[N];
map<string,int> mp;
string table[N];
string change(string s){
	for(int i=0;i<s.size();i++)
		if('A'<=s[i]&&s[i]<='Z') s[i]+=32;
	return s;
}
int GetR(string s){
	int cnt=0;
	for(int i=0;i<s.size();i++)
		if(s[i]=='r') cnt++;
	return cnt;
}
void Tarjan(int x){
	DFN[x]=Low[x]=++sign;
	st[++top]=x;ins[x]=1;
	for(int v:E[x])
		if(!DFN[v]) Tarjan(v),Low[x]=min(Low[x],Low[v]);
		else if(ins[v]) Low[x]=min(Low[x],DFN[v]);
	if(DFN[x]==Low[x]){
		int t;++scc;
		do{ t=st[top--];
			bl[t]=scc; 
			ins[t]=0;
			if(Min[scc]>GetR(table[t])) Min[scc]=GetR(table[t]),len[scc]=table[t].size();
			else if(Min[scc]==GetR(table[t])) len[scc]=min(len[scc],(int)table[t].size());
		}while(top>0&&t!=x);
	}
}
void Topo(){
	queue<int> q;
	for(int i=1;i<=scc;i++)
		if(!ind[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int v:E2[x]){
			if(Min[v]>Min[x]) Min[v]=Min[x],len[v]=len[x];
			else if(Min[v]==Min[x]) len[v]=min(len[v],len[x]);
			if(!--ind[v]) q.push(v);
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		s=change(s);
		if(!mp[s]) table[mp[s]=++tot]=s;
		word[i]=mp[s];
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		string u,v;cin>>u>>v;
		u=change(u),v=change(v);
		if(!mp[u]) table[mp[u]=++tot]=u;
		if(!mp[v]) table[mp[v]=++tot]=v;
		E[mp[u]].push_back(mp[v]);
	}
	for(int i=1;i<=tot;i++) Min[i]=len[i]=N*3;
	for(int i=1;i<=tot;i++) if(!DFN[i]) Tarjan(i);
	for(int i=1;i<=tot;i++) for(int v:E[i])
		if(bl[i]!=bl[v]) E2[bl[v]].push_back(bl[i]),ind[bl[i]]++;
	Topo();
	for(int i=1;i<=n;i++)
		ans1+=Min[bl[word[i]]],ans2+=len[bl[word[i]]];
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
给定 $n$ 个字符串和 $m$ 对字符串 $x_1,y_1,x_2,y_2...x_m,y_m$，我们可以将 $n$ 个字符串中与 $x_i$ 相同的字符串（**不论大小写**）修改为 $y_i$。求修改过后，这 $n$ 个字符中的字符 `r` 的数量最少为多少，以及其最少时这 $n$ 个字符串长度总和的最小值。
# 思路
首先，在题目中有说到关于判断两个字符串是否相等的时候是**不论大小写**的，所以我们在每次读入一个字符串的时候要先统一大小写，这样方便判断字符串是否是相等的。

其次，这里很容易可以看出这道题是要跑图的，但是题目中转换的关系却是字符串间的，所以可以知道需要用给每个字符串赋序号值，这里我选择用 map。

然后有了以上的两点，我们就可以初步地根据字符串间的转换关系建边并跑图了。但是仔细读题，却发现题目中并没有限制环的存在，所以容易知道需要跑强连通缩点后，再进行操作。

最后，我们只需要对缩点过后的图用拓扑的思路去递推出从某个字符串开始所能得到的 `r` 的最小出现次数以及在 `r` 的出现次数最小的情况下字符串的最小长度。拓扑递推的过程很简单，存储出度为 $0$ 的点，跑 bfs 并且同时将 `r` 最小个数以及 `r` 出现次数最小下字符串长度最小值往回递归即可。

其他细节请看代码及其注释。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+15;
vector<int> r[N],road[N];
map<string,int> mp;
string rev[N];
int ans1,id[N],siz[N],num[N],Min[N],din[N];
long long len[N],ans2;
int stk[N],instk[N],low[N],scc[N],cnt,sfn,tot;
inline void dfs(int u){
    id[u]=low[u]=++sfn;
    stk[++tot]=u;instk[u]=1;
    for(auto v:r[u]){
        if(!id[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instk[v])
            low[u]=min(low[u],id[v]);
    }
    if(id[u]==low[u]){
        int v;cnt++;Min[cnt]=1e9;len[cnt]=1e9;
        do{
            siz[cnt]++;
            v=stk[tot--];
            if(num[v]<Min[cnt]){
            //如果r的个数比原来的更小，更新r个数以及字符长度
                Min[cnt]=num[v];
                len[cnt]=rev[v].size();
            }
            else if(num[v]==Min[cnt])
                len[cnt]=min(len[cnt],(long long)rev[v].size()); 
            //如果r个数相同，比较更新字符串长度
            instk[v]=0;
            scc[v]=cnt;
        }while(v!=u);
    }
}//tarjan SCC 强连通缩点
int n,m,ID;
string s[N/3],a,b;
int main(){
    scanf("%d",&n);
    for(int i=1,res;i<=n;i++){
        cin>>s[i];
        res=0;
        for(int j=0;j<s[i].size();j++){
            if('A'<=s[i][j]&&s[i][j]<='Z')是否为大写
                s[i][j]-='A'-'a';
            res+=(s[i][j]=='r');//判断r的个数
        }//全部最小化
        if(mp.find(s[i])==mp.end()){
            mp[s[i]]=++ID;//赋序号值
            num[ID]=res;//存储r的个数
            rev[ID]=s[i];//反差
        }
    }
    scanf("%d",&m);
    for(int i=1,res;i<=m;i++){
        cin>>a>>b;
        res=0;
        for(int j=0;j<a.size();j++){
            if('A'<=a[j]&&a[j]<='Z')
                a[j]-='A'-'a';
            res+=(a[j]=='r');
        }
        if(mp.find(a)==mp.end()){
            mp[a]=++ID;
            num[ID]=res;
            rev[ID]=a;
        }
        res=0;
        for(int j=0;j<b.size();j++){
            if('A'<=b[j]&&b[j]<='Z')
                b[j]-='A'-'a';
            res+=(b[j]=='r');
        }
        if(mp.find(b)==mp.end()){
            mp[b]=++ID;
            num[ID]=res;
            rev[ID]=b;
        }//同上处理字符串
        r[mp[a]].emplace_back(mp[b]);//建边
    }
    for(int i=1;i<=mp.size();i++)
        if(!low[i])
            dfs(i);//跑tarjan缩点
    for(int i=1;i<=mp.size();i++)
    for(auto v:r[i])
        if(scc[i]!=scc[v]){//建反边
            din[scc[i]]++;
            //存储入度数值
            road[scc[v]].emplace_back(scc[i]);
            //存储缩点后的图
        }
    queue<int> q;
    for(int i=1;i<=mp.size();i++)
        if(!din[i])
            q.push(i);//入度为0的点入队
    while(!q.empty()){//bfs从
        int u=q.front();q.pop();
        for(auto v:road[u]){
            if(Min[u]<Min[v]){
            //如果r的个数比原来的更小，更新r个数以及字符长度
                Min[v]=Min[u];
                len[v]=len[u];
            }  
            else if(Min[u]==Min[v])
                len[v]=min(len[v],len[u]);
            //如果r个数相同，比较更新字符串长度
            din[v]--;
            //判断更改入度后是否需要入队
            if(din[v]==0)
                q.push(v);
        }
    }
    for(int i=1;i<=n;i++){
        int iid=mp[s[i]];
        ans1+=Min[scc[iid]];
        ans2+=len[scc[iid]];//统计答案
    }
    printf("%d %lld\n",ans1,ans2);
    return 0;
}
```

---

## 作者：_anll_ (赞：0)

~~第一次写紫题题解有点兴奋。~~
## 题目大意
给你 $n$ 个字符串和 $m$ 个**单向**替换关系，不区分大小写，问你怎样替换能让这 $n$ 个字符串的 `'r'` 总量最小，并在 `'r'` 总量最少的基础上（后文默认已知这个大前提）让长度总和最小。

## 大体思路
其实是思路很简单的一道强连通分量，但是维护起来有点点麻烦。

对于每个字符串，不妨先化字符串为点。这里 map 就可以解决，不过注意大小写不敏感，我这里把字符串全处理成了小写。

由于替换关系是单向的，所以很容易想到强连通分量。令最少 `'r'` 为 $rrr$，最短长度为 $lll$。如果 $k$ 个点在同一个分量里，那他们的 $rrr$ 和 $lll$ 都是一样的。

于是解法就呼之欲出了。每次在记录当前强连通分量的同时存下对于当前强连通分量的 $rrr$ 和 $lll$。之后~~走一次老套路~~建反图跑动态规划更新答案即可。

最后统计答案时累加每个单词所对应的强连通分量的 $rrr$ 和 $lll$ 即可。

## 代码展示
大体思路就是这样，如果有不清楚的地方，请结合代码理解。
```cpp
#include<iostream>
#include<cstring>
#include<queue>
#include<map>
#define int long long
using namespace std;
struct Edge{
    int l,nxt;
}edges[2000005],ed[2000005];
string s1,s2;
int n,m,ans1,ans2,tt=1,ttt=1,t,head[600005],h[600005],que[600005];
int len[600005],rr[600005],du[600005];
int tot,low[600005],dfn[600005];
int top,stk[600005],instk[600005];
int cnt,scc[600005],lll[600005],rrr[600005];
map<string,int> mo;
map<pair<int,int>,int> mp;
queue<int> qo;
void add_edge(int f,int l){
    tt+=1;
    edges[tt]={l,head[f]};
    head[f]=tt;
}
void add(int f,int l){
    ttt+=1;
    ed[ttt]={l,h[f]};
    h[f]=ttt;
}
void tarjian(int x){
    tot+=1,top+=1;
    dfn[x]=low[x]=tot;
    stk[top]=x,instk[x]=1;
    for(int i=head[x];i;i=edges[i].nxt){
        int l=edges[i].l;
        if(!low[l]){
            tarjian(l);
            low[x]=min(low[x],low[l]);
        }
        else if(instk[l]) low[x]=min(low[x],dfn[l]);
    }
    if(low[x]==dfn[x]){
        int y;cnt+=1;
        do{
            y=stk[top],top-=1,instk[y]=0;
            scc[y]=cnt;
            if(rrr[cnt]>rr[y])
                rrr[cnt]=rr[y],lll[cnt]=len[y];
            else if(rrr[cnt]==rr[y]) lll[cnt]=min(lll[cnt],len[y]);
        }while(y!=x);
    }
}
signed main(){
    int awa;
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s1;
        awa=0;
        for(int j=0;j<s1.size();j++){
            if('A'<=s1[j]&&s1[j]<='Z') s1[j]=s1[j]-'A'+'a';
            if(s1[j]=='r') awa+=1;
        }
        if(!mo[s1]){
            t+=1,mo[s1]=t;
            len[mo[s1]]=s1.size(),rr[mo[s1]]=awa;
         
        }
        que[i]=mo[s1];
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>s1>>s2;
        awa=0;
        for(int j=0;j<s1.size();j++){
            if('A'<=s1[j]&&s1[j]<='Z') s1[j]=s1[j]-'A'+'a';
            if(s1[j]=='r') awa+=1;
        }
        if(!mo[s1]){
            t+=1,mo[s1]=t;
            len[mo[s1]]=s1.size(),rr[mo[s1]]=awa;   
        }
        awa=0;
        for(int j=0;j<s2.size();j++){
            if('A'<=s2[j]&&s2[j]<='Z') s2[j]=s2[j]-'A'+'a';
            if(s2[j]=='r') awa+=1;
        }
        if(!mo[s2]){
            t+=1,mo[s2]=t;
            len[mo[s2]]=s2.size(),rr[mo[s2]]=awa;
        }
        add_edge(mo[s1],mo[s2]);
    }
    memset(lll,0x3f,sizeof(lll));
    memset(rrr,0x3f,sizeof(rrr));
    for(int i=1;i<=t;i++) if(!low[i]) tarjian(i);
    for(int f=1;f<=t;f++){
        for(int i=head[f];i;i=edges[i].nxt){
            int l=edges[i].l;
            if(scc[f]==scc[l]||mp[{scc[f],scc[l]}]) continue;
            mp[{scc[f],scc[l]}]=1;
            add(scc[l],scc[f]);
            du[scc[f]]+=1;
        }
    }
    for(int i=1;i<=cnt;i++) if(!du[i]) qo.push(i);
    while(!qo.empty()){
        int x=qo.front();qo.pop();
        for(int i=h[x];i;i=ed[i].nxt){
            int l=ed[i].l;
            if(rrr[l]>rrr[x])
                rrr[l]=rrr[x],lll[l]=lll[x];
            else if(rrr[l]==rrr[x]) lll[l]=min(lll[l],lll[x]);
            du[l]-=1;
            if(!du[l]) qo.push(l);
        }
    }
    for(int i=1;i<=n;i++){
        ans1+=rrr[scc[que[i]]];
        ans2+=lll[scc[que[i]]];
    }
    cout<<ans1<<" "<<ans2<<endl;
    return 0;
}
```


---

## 作者：hhhqx (赞：0)

2023 最后 AC 的一道题，写个题解纪念一下（2023.12.31 AC 的）

# CF467D - Fedor and Essay 题解
## 题解
[题目传送门](https://www.luogu.com.cn/problem/CF467D)

由于题目不需要对输入的字符串进行操作，所以直接利用**哈希**将每个**单词化成一个数**。

题目就显然是一道**图论题**了。以题目给出单词变化方式为边，然后每个单词为点，建图。

接着我们可以将题目提出的大问题化简为小问题，即每个点变化后的最优结果。那么每个点的最优结果需要从开始的单词经过**连续的**变化后得到，即我们所建的图中一连串路径的终点。

但是这个图没有拓扑序，否则实现起来很麻烦，于是想到了 **Tarjan 缩点**。毕竟缩点后必定是一个无环图，又是有向图，拥有完美的拓扑序。

接着就可以快乐统计答案了。十分的好写。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using Pair = pair<int, int>;

const Pair B = {37, 131}; // 双哈希
const int mod = 998244353;
const int MAXN = 2e6 + 3; // 单词的总个数，我为了方便直接取了2e6

string str;
int _n, n = 0, m;
int rans[MAXN];
Pair a[MAXN];
vector<int> eg[MAXN];

map<Pair, int> mp; // 哈希
int Hash(){
  cin >> str;
  for(int i = 0; i < str.size(); i++){ // 统一化为小写字母
    if('A' <= str[i] && str[i] <= 'Z') str[i] = 'a' + str[i] - 'A';
  }
  Pair sum = {0, 0};
  for(char ch : str){ // 哈希
    sum = {(1ll * sum.first *B.first %mod+(ch - 'a' + 1))%mod,
           (1ll * sum.second*B.second%mod+(ch - 'a' + 1))%mod};
  }
  if(mp.find(sum) != mp.end()) return mp[sum];
  n++, mp[sum] = n, a[n] = {0, str.size()};
  for(char ch : str) a[n].first += (ch == 'r');
  return n;
}

int depth = 0, low[MAXN], dep[MAXN], root[MAXN]; // 缩点
vector<int> stk;
int Tarjan(int x){
  if(dep[x]) return (root[x] > 0 ? n : dep[x]);
  depth++, dep[x] = low[x] = depth;
  stk.push_back(x);
  for(int E : eg[x]) low[x] = min(low[x], Tarjan(E));
  if(low[x] == dep[x]){
    for( ; stk.size() > 0 && stk.back() != x; stk.pop_back()){
      for(int E : eg[stk.back()]) eg[x].push_back(E);
      int bck = stk.back();
      root[bck] = x;
      a[x] = min(a[x], a[bck]); // 一个环内的点可以相互到达，所以直接取最小值
    }
    root[x] = x, stk.pop_back();
  }
  return low[x];
}

bool vis[MAXN]; // 标记数组
Pair a_dfs(int x){
  if(vis[x]) return a[x];
  vis[x] = 1;

  for(int E : eg[x]){
    a[x] = min(a[x], a_dfs(root[E]));
  }
  return a[x];
}

int main(){
  cin >> _n;
  while(_n--) rans[Hash()]++;
  cin >> m;
  for(int i = 1, U, V; i <= m; i++){
    U = Hash(), V = Hash();
    eg[U].push_back(V); // 建图
  }
  for(int i = 1; i <= n; i++) Tarjan(i); // 缩点
  for(int i = 1; i <= n; i++) a_dfs(root[i]); // 统计答案
  pair<LL, LL> ANS = {0, 0}; // 注意这里需要开 long long
  for(int i = 1; i <= n; i++){
    ANS.first += 1ll * a[root[i]].first * rans[i]; // 注意这里需要开 long long
    ANS.second+= 1ll * a[root[i]].second* rans[i];
  }
  cout << ANS.first << " " << ANS.second; // 完结！
  return 0;
}

```

---

## 作者：Windy_Hill (赞：0)

## 题意
给你一个字符串，里面有 $n$ 个单词，每个单词可以被替换为另一个词（**改变是单向的!!!**），其中要使得替换后 ```R``` 和 ```r``` 在单词中的出现数量尽可能少，在 ```R``` 和 ```r``` 尽可能少的情况下使得最后所有单词长度之和最小。

## 思路
一开始将大写全部改成小写，利用 ```map``` 记录每个单词的编号，再 ```tarjan``` 把单词缩一下，因为如果单词太多，会不太好做，缩成 ```Dag``` 后会简便很多，缩的时候要记得对于每个连通分量记录 ```r``` 的最少个数以及单词的最短的长度，最后进行一次拓扑排序求出答案，如果不会 ```tarjan```，请前往 [P3387](https://www.luogu.com.cn/problem/P3387)  学习，最后输出即可。

## 代码
```cpp
#include <bits/stdc++.h>

#define int long long 

using namespace std;

const int N = 500010;

//答案
int res_l[N];
int res_r[N];

int idx;
int hr[N];
string a[N];
vector<int> P[N];
map<string, int> id;
vector<int> graph[N];
map<int, string> idxt;

//tarjan
bool in_stk[N];
int scc_cnt, top, timestamp;
int dfn[N], low[N], stk[N], idt[N], in[N];

//将大写改成小写
void do_(string& s)
{
    for (int i = 0; i < s.size(); i ++ )
        if ('A' <= s[i] && s[i] <= 'Z') s[i] = (char)(s[i] - 'A' + 'a');
}

//统计r的个数
void do__(string s)
{
    for (int i = 0; i < s.size(); i ++ )
        if (s[i] == 'r') hr[id[s]] ++ ;
}

//tarjan
void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;
    
    for (int j : graph[u])
    {
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j])
            low[u] = min(low[u], dfn[j]);
    }
    
    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            idt[y] = scc_cnt;
            if (res_r[scc_cnt] == hr[y]) 
                res_l[scc_cnt] = min(res_l[scc_cnt], (int)(idxt[y].size()));
            if (res_r[scc_cnt] > hr[y]) 
            {
                res_r[scc_cnt] = hr[y];
                res_l[scc_cnt] = idxt[y].size();
            }
        } while (y != u);
    }
}

signed main()
{
    memset(res_l, 0x3f, sizeof res_l);
    memset(res_r, 0x3f, sizeof res_r);
    
    int n;
    cin >> n;
    
    //输入处理
    for (int i = 1; i <= n; i ++ ) 
    {
        cin >> a[i]; do_(a[i]);
        if (id[a[i]] == 0) id[a[i]] = ++ idx, do__(a[i]), idxt[idx] = a[i];
    }
    
    int T;
    cin >> T;
    
    while (T -- )
    {
        string s, t;
        cin >> s >> t;
        do_(s), do_(t);
        if (id[s] == 0) id[s] = ++ idx, do__(s), idxt[idx] = s;
        if (id[t] == 0) id[t] = ++ idx, do__(t), idxt[idx] = t;
        graph[id[s]].push_back(id[t]);
    }
    
    for (int i = 1; i <= idx; i ++ )
        if (!dfn[i]) tarjan(i);
        
    //缩点
    for (int i = 1; i <= idx; i ++ )
        for (int j = 0; j < graph[i].size(); j ++ )
            if (idt[graph[i][j]] != idt[i])
                P[idt[graph[i][j]]].push_back(idt[i]), in[idt[i]] ++ ;
            
    queue<int> q;
    for (int i = 1; i <= scc_cnt; i ++ )
        if (!in[i]) q.push(i);
        
   //拓扑序
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v : P[u])
		{
			in[v] -- ;
			if (res_r[v] == res_r[u]) res_l[v] = min(res_l[v], res_l[u]);
			if (res_r[v] > res_r[u]) res_r[v] = res_r[u], res_l[v] = res_l[u];
			if (!in[v]) q.push(v);
		}
	}
	
	int res_len = 0, res_rs = 0;
	for (int i = 1; i <= n; i ++ )
	    res_len += res_l[idt[id[a[i]]]], res_rs += res_r[idt[id[a[i]]]];
	    
	cout << res_rs << " " << res_len;
    
    return 0;
}
```

---

## 作者：lzytag (赞：0)

## 前言
看到题解中的 Dijkstra 和 SCC 的做法，感觉都太麻烦了，所以来写一篇稍微简单一点的。
## sol
首先是将所有出现的单词标一个编号，可以用 map 来实现，不懂得可以直接看代码。

然后将所有同义词之间**反向**建边，接着将所有出现的单词以 **R 出现的次数**为第一关键字，**单词长度**为第二关键字排序。

这样我们就可以从小到大遍历每一个单词，沿着之前建的反向边深搜，将所有搜索到的点标记，并覆盖它们的 R 出现次数和单词长度；如果搜索到了标记过的点则退出。

很显然，这样依次搜索完后最后每个点的 R 出现次数和单词长度就是它们所能转换成的单词的最小值。

最后将每一个论文中的单词的值相加即可。

具体细节可见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5;
typedef long long ll;
int n,m,k;
string a[N+5];
int b[N+5];
map<string,int>mp;
int v1[N+5],v2[N+5];
int g[N+5];
vector<int>e[N+5];
int GetID(string str) // 转换编号
{
    for(int i = 0;i < str.size();i++) if(str[i] >= 'a') str[i] = str[i] - 'a' + 'A';
    if(mp[str]) return mp[str];
    else
    {
        mp[str] = ++k;
        v2[k] = str.size();
        for(int j = 0;j < v2[k];j++)
        {
            if(str[j] == 'R')
            {
                v1[k]++;
            }
        } 
        return k;
    }
}
void dfs(int x)
{
    g[x] = 1;
    for(auto y:e[x])
    {
        if(g[y]) continue;
        v1[y] = v1[x],v2[y] = v2[x];
        dfs(y);
    }
}
int id[N+5];
bool cmp(int i,int j)
{
    return v1[i] != v1[j] ? v1[i] < v1[j] : v2[i] < v2[j];
}
int main()
{
    cin>>n;
    for(int i = 1;i <= n;i++)
    {
        cin>>a[i];
        b[i] = GetID(a[i]);
    }
    cin>>m;
    for(int i = 1;i <= m;i++)
    {
        string a,b;
        cin>>a>>b;
        int x = GetID(a),y = GetID(b);
        e[y].push_back(x);
    }
    for(int i = 1;i <= k;i++) id[i] = i;
    sort(id+1,id+1+k,cmp);//排序
    for(int i = 1;i <= k;i++)//搜索
    {
        if(g[id[i]]) continue;
        dfs(id[i]);
    }
    ll a1 = 0,a2 = 0;
    for(int i = 1;i <= n;i++)
    {
        a1 += v1[b[i]];
        a2 += v2[b[i]];
    }
    cout<<a1<<" "<<a2<<"\n";
    return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

几个月没写 $\texttt{Tarjan}$ 缩点了，再来做这道题竟然一眼秒，一个小时内切了/jk。

# Solution
考虑以单词为点，$x_i\to y_i$ 为边把图建出来，点权就为这个字符串 `R` 的个数和字符串长度组成的二元组。

那么答案就为 $n$ 个点能到达的点权最小的点的点权之和。

直接在图上 $\texttt{DP}$ 显然不好做，考虑 $\texttt{Tarjan}$ 缩点，转化成在 $\texttt{DAG}$ 上 $\texttt{DP}$，每个 $\texttt{SCC}$ 的点权就为 $\texttt{SCC}$ 里所有点点权的最小值，记忆化搜索即可。

时间复杂度 $O(n+m+\sum\vert S\vert)$。

# Code
```c++
#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;
const int N=3e5+1;
vector<int> g[N];
int n,V,id[N];
P w[N];

namespace init
{
	string s,t; int m;
	unordered_map<string,int> a; 
	int solve(string &s,int cnt=0)
	{
		for (char &c:s) {
			if (isupper(c) ) c=c-'A'+'a';
			if (c=='r') cnt++;
		}
		return cnt;
	}
	void main()
	{
		cin>>n;
		for (int i=0;i<n;i++) {
			cin>>s; int cnt=solve(s);
			if (!a[s]) a[s]=++V,w[V]={cnt,s.size()};
			id[i]=a[s];
		}
		cin>>m;
		while (m--) {
			cin>>s>>t;
			int cnt1=solve(s),cnt2=solve(t);
			if (!a[s]) a[s]=++V,w[V]={cnt1,s.size()};
			if (!a[t]) a[t]=++V,w[V]={cnt2,t.size()};
			g[a[s] ].push_back(a[t]);
		}
	}
}
namespace build
{
	P W[N]; vector<int> G[N];
	int tot,cnt,dfn[N],low[N],belong[N];
	bool instack[N]; stack<int> s;
	void tarjan(int u)
	{
		dfn[u]=low[u]=++tot;
		s.push(u),instack[u]=true;
		for (int v:g[u]) {
			if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
			else if (instack[v]) low[u]=min(low[u],dfn[v]);
		}
		if (dfn[u]==low[u])
		{
			cnt++,W[cnt]={INT_MAX,0};
			int o;
			do {
				o=s.top(),s.pop();
				instack[o]=false,belong[o]=cnt;
				W[cnt]=min(W[cnt],w[o]);
			}while (o^u);
		}
	}
	void main()
	{
		for (int i=1;i<=V;i++) if (!dfn[i]) tarjan(i);
		for (int u=1;u<=V;u++) for (int v:g[u]) if (belong[u]^belong[v])
		G[belong[u] ].push_back(belong[v]); V=cnt;
		for (int i=1;i<=V;i++) w[i]=W[i],g[i]=G[i];
		for (int i=0;i<n;i++) id[i]=belong[id[i] ];
	}
}
namespace DP
{
	P dis[N];
	P solve(int u) {
		if (dis[u].first!=INT_MAX) return dis[u]; dis[u]=w[u];
		for (int v:g[u]) dis[u]=min(dis[u],solve(v) ); return dis[u];
	}
	void main() {
		for (int i=1;i<=V;i++) dis[i].first=INT_MAX; pair<long long,long long> ans={0,0};
		for (int i=0;i<n;i++) solve(id[i]),ans.first+=dis[id[i] ].first,ans.second+=dis[id[i] ].second;
		printf("%lld %lld\n",ans.first,ans.second);
	}
}
int main()
{
	cin.tie(0);
	init::main();
	build::main();
	DP::main();
	return 0;
}
```

---

