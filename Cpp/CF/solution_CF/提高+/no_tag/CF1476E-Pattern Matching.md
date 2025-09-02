# Pattern Matching

## 题目描述

给定 $n$ 个模式串 $p_i$ 和 $m$ 个字符串 $s_i$，其中 $p_i$ 两两不同。每个模式串和字符串都包含 $k$ 个字符。其中模式串中可以含通配符（用下划线表示，可以匹配任何字符），剩余字符都为小写英文字母。同时给定 $n$ 个数 $mt_i$，要求重新排列模式串使得 $s_j$ 匹配到的第一个模式串为 $p_{mt_j}$。请判断是否存在排列方案满足如上要求，能的话请输出方案。

## 说明/提示

$1\le n,m\le 1\times 10^5$，$1\le k\le 4$，对于所有的 $mt$ 都有 $1\le mt\le n$。

## 样例 #1

### 输入

```
5 3 4
_b_d
__b_
aaaa
ab__
_bcd
abcd 4
abba 2
dbcd 5```

### 输出

```
YES
3 2 4 5 1```

## 样例 #2

### 输入

```
1 1 3
__c
cba 1```

### 输出

```
NO```

## 样例 #3

### 输入

```
2 2 2
a_
_b
ab 1
ab 2```

### 输出

```
NO```

# 题解

## 作者：Cutest_Junior (赞：1)

## 题解 CF1476E 【Pattern Matching】

### 题意

+ $n$ 个模式串 $p$ 和 $m$ 个字符串 $s$，字符串有小写字母组成，模式串由小写字母和通配符组成；
+ 相同字母可以相匹配，通配符可以与任何字母相匹配；
+ 一个模式串和一个字符串相匹配，当且仅当两串每一位上的字符都相匹配；
+ 给出大小为 $m$ 的数组 $mt$，对模式串重新排列，使与 $s_i$ 相匹配的排在最前面的模式串原编号为 $mt_i$。
+ $n,m\le10^5$，字符串长度 $\le4$，$1\le mt_i\le n$。

### 做法

满足 $mt_i$，则需使 $p_{mt_i}$ 在其它与 $s_i$ 相匹配的模式串之前。

考虑连边，跑拓扑排序。

但是有 $10^5$ 个模式串，直接枚举会炸时间。

发现长度只有 $4$，对任意字符串最多只有 $2^4=16$ 个模式串可能与之相匹配。

可以对每个字符串建虚点，再向所有与之匹配的模式串连边，断掉向 $p_{mt_i}$ 的边，重建一条反向边。

### 代码

```cpp
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int id(string str) {
	int a = 0;
	for (int i = 0; i < (int)str.size(); ++i) {
		a = a * 27;
		if (str[i] >= 'a' && str[i] <= 'z') {
			a += str[i] - 'a' + 1;
		}
	}
	return a;
}

const int N = 1e5 + 5;

int a[N];

const int Str = 6e5 + 5;

vector<int> edge[Str];

void add(int u, int v) {
	edge[u].push_back(v);
}

int in[Str];

void dfs(int str1, int str2, int now) {
	if (!str2) {
		int x = 0;
		str2 = str1;
		while (str2) {
			x = x * 27 + now % 27;
			str2 /= 27;
			now /= 27;
		}
		++in[x];
//		printf("%d %d\n", str1, x);
		add(str1, x);
		return;
	}
	dfs(str1, str2 / 27, now * 27);
	dfs(str1, str2 / 27, now * 27 + str2 % 27);
}

int val[Str];

int ans[N], tot;

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i) {
		string str;
		cin >> str;
		a[i] = id(str);
		val[a[i]] = i;
	}
	for (int i = 1; i <= m; ++i) {
		string str;
		cin >> str;
		int x;
		scanf("%d", &x);
//		++in[id(str)];
		add(a[x], id(str));
		--in[a[x]];
		dfs(id(str), id(str), 0);
	}
	queue<int> q;
	for (int i = 1; i <= n; ++i) {
		if (!in[a[i]]) {
			q.push(a[i]);
		}
//		printf("%d ", in[a[i]]);
	}
//	printf("\n");
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		if (val[x]) {
			ans[++tot] = val[x];
//			printf("%d\n", val[x]);
		}
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int to = edge[x][i];
			--in[to];
//			printf("%d %d\n", to, in[to]);
			if (in[to] == 0) {
				q.push(to);
			}
		}
	}
	if (tot < n) {
		printf("NO");
//		printf("%d\n", tot);
	}
	else {
		printf("YES\n");
		for (int i = 1; i <= n; ++i) {
			printf("%d ", ans[i]);
		}
	}
}//
```

---

## 作者：7KByte (赞：1)

观察一下发现 $k$ 很小。

所以对于给定的 $m$ 个串，最多只有 $2^k\le16$ 个模式串与之匹配。

对于每个给定串，限制条件可以转换为与之匹配的串中，指定某个串必须排在其他串前面。

这显然是图论拓扑模型，并且边数不会超过 $2^k\times m$。

我们只用快速找出与之匹配的串，这可以用 $\texttt{Trie}$ 树快速解决，下划线可以当作一个通配符插入。

时间复杂度$\rm{O(2^km+kn)}$，空间复杂度$\rm{O(27kn+2^km)}$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 400005
using namespace std;
int n,m,k,ch[N][27],idx,ed[N];char s[6];
int h[N],tot,in[N],op;bool flag;
struct edge{
	int nxt,to;
}e[N<<4];
void add(int x,int y){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;
}
void dfs(int x,int y){
	if(y>k){
		if(ed[x]==op)flag=true;
		else add(op,ed[x]),in[ed[x]]++;
		return;
	}
	if(ch[x][s[y]-'a'])dfs(ch[x][s[y]-'a'],y+1);
	if(ch[x][26])dfs(ch[x][26],y+1);
}
queue<int>q;
int ans[N],top;
void topo(){
	rep(i,1,n)if(!in[i])q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		ans[++top]=x;
		for(int i=h[x];i;i=e[i].nxt){
			in[e[i].to]--;
			if(!in[e[i].to])q.push(e[i].to);
		}
	}
	if(top!=n)puts("NO");
	else{
		puts("YES");
		rep(i,1,n)printf("%d ",ans[i]);
		putchar('\n');
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	rep(T,1,n){
		scanf("%s",s+1);
		int now=0;
		rep(i,1,k)
			if(s[i]=='_'){
				if(!ch[now][26])ch[now][26]=++idx;
				now=ch[now][26];
			}
			else{
				if(!ch[now][s[i]-'a'])ch[now][s[i]-'a']=++idx;
				now=ch[now][s[i]-'a'];
			}
		ed[now]=T;
	}
	rep(i,1,m){
		scanf("%s",s+1);
		scanf("%d",&op);
		flag=false;dfs(0,1);
		if(!flag){puts("NO");return 0;}
	}
	topo();
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较简单的题，还算是比较套路。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
首先考虑如何处理字符串匹配。

不难想到 trie 树，把通配符当做第 $27$ 个英文字母扔进去建树。

查询的时候如果存在通配符的边无脑跑尝试匹配即可。

因为字符串长度 $k$ 很短，所以最多匹配上的字符串也只会有 $2^k\le2^4=16$。

接着考虑如何处理匹配顺序问题。

假设一个字符串匹配到的字符串编号集合为 $S$，并把它要求的字符串拿掉了。

设要求的字符串为 $x$，原编号 $i$ 的字符串在答案中对应的位置为 $id_i$，那么必然要满足的关系就是：$\forall i\in S,id_i>id_x$。

考虑怎么来判断这个东西。

不难想到拓扑。

把这个关系建图之后拓扑一次，如果还有点没被拓展到说明有环，绝对不行。

否则就是可行，方案即为拓扑到节点的顺序。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,k,tot,in[N],ed[N],t[N][27];char s[N];vector<int>e[N],ans;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='_'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void insert(char s[],int n,int i)
{
	int u=0;
	for(int i=1;i<=n;i++)
	{
		int v=(s[i]=='_')?26:s[i]-'a';
		if(!t[u][v]) t[u][v]=++tot;
		u=t[u][v];
	}ed[u]=i;
}
inline bool dfs(int u,int dep,int x)
{
	int f=0;
	if(dep==k+1)
	{
		if(ed[u]==x) return true;
		e[x].emplace_back(ed[u]);in[ed[u]]++;
	}if(t[u][s[dep]-'a']) f|=dfs(t[u][s[dep]-'a'],dep+1,x);
	if(t[u][26]) f|=dfs(t[u][26],dep+1,x);return f;
}
inline void toposort()
{
	queue<int>q;
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(!q.empty())
	{
		auto u=q.front();q.pop();ans.emplace_back(u);
		for(auto v:e[u]) if(!--in[v]) q.push(v);
	}if(ans.size()!=n) return put("NO");
	put("YES\n");for(auto v:ans) print(v),put(' ');
}
signed main()
{
	n=read(),m=read(),k=read();
	for(int i=1,l;i<=n;i++) l=0,rd(s,l),insert(s,l,i);
	for(int i=1,l;i<=m;i++)
	{
		l=0,rd(s,l);
		if(!dfs(0,1,read())){put("NO");goto genshin;}
	}toposort();
	genshin:;flush();return 0;
}
```

---

## 作者：Rain_chr (赞：0)

### 前言

做任何一道题，都得先观察数据范围，因为它能够告诉你算法的时间复杂度。

### 题意

+ $n$ 个模式串 $p$ 和 $m$ 个字符串 $s$，字符串只由小写字母组成，模式串只由小写字母和通配符组成

+ 相同字母可以相匹配，通配符可以与任何字母相匹配

+ 给出大小为 $m$ 的数组 $mt$，对模式串重新排列，使第一个与 $s_i$ 相匹配的模式串原编号为 $mt_i$

### 分析

一看数据范围，$n,m \leq 10^5$，肯定是 $O(n)$ 的时间。

再看 $k \leq 4$，肯定是 ~~乱搞~~ 等暴力算法。

首先解答一个问题，为什么不能用并查集。

我一开始的想法字典树进行相似模式串的匹配，然后用并查集连通，同一联通块的被标记的字符串只能有一个，否则就会冲突。之后将每个连通块内被标记的字符串第一个输出，然后再输出连通块内其它字符串。

后来一想，不太对劲。字符串之间没有传递性，也就是说，这是一个 **有向图**。

所以，我们就可以用字典树判断字符串与模式串之间是否匹配，然后再图论建模上拓扑排序即可。

上代码：

```cpp
#include<bits/stdc++.h>
#define go(i) i=='_'?0:i-'a'+1
using namespace std;
inline int read()
{
	char x=getchar();
	int ans=0,f=1;
	while(x>'9'||x<'0') 
	{
		if(x=='-')
			f=-f;
		x=getchar();
	}
	while(x>='0'&&x<='9') 
	{
		ans=(ans<<3)+(ans<<1)+(x^48);
		x=getchar();
	}
	return ans*f;
}
int cnt;
int ch[400010][30];
int book[400010];
void insert(string s,int id)
{
	int p=0;
	for(int i=0;i<s.size();i++)
	{
		if(ch[p][go(s[i])])
			p=ch[p][go(s[i])];
		else
			p=ch[p][go(s[i])]=++cnt;
	}
	book[p]=id;
}
vector<int> a[100010];
int in[100010];
bool tag;
void dfs(int p,string s,int now,int k)
{
	if(book[p])
	{
		tag=1;
		if(book[p]==k)	
			return ;
		in[book[p]]++;
		a[k].push_back(book[p]);
		return ;    
	}
	if(now==s.size())
		return ;
	if(ch[p][go(s[now])])
		dfs(ch[p][go(s[now])],s,now+1,k);
	if(ch[p][0])
		dfs(ch[p][0],s,now+1,k);
}
int ans[100010];
string t[100010];
bool check(string s,string t)
{
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='_'||t[i]=='_')
			continue;
		if(s[i]!=t[i])
			return 0; 
	}
	return 1;
} 
int main()
{
	int n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
	{
		cin>>t[i];
		insert(t[i],i);
	}
	for(int i=1;i<=m;i++)
	{
		string s;
		cin>>s;
		tag=0;
		int x=read();
		if(!check(s,t[x])) 
		{
			puts("NO");
			return 0;
		}
		dfs(0,s,0,x);
		if(!tag)
		{
			puts("NO");
			return 0;
		}
	}
	queue<int> q;
	int tot=0;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(q.size())
	{
		int x=q.front();
		q.pop();
		ans[++tot]=x;
		for(int i=0;i<a[x].size();i++)
		{
			in[a[x][i]]--;
			if(!in[a[x][i]])
				q.push(a[x][i]);
		}
	}
	if(tot!=n)
		puts("NO");
	else
	{
		puts("YES");
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<" ";
	}
	return 0;
}
```



---

## 作者：Y_ATM_K (赞：0)

### [CF1476E Pattern Matching](https://www.luogu.com.cn/blog/Y-ATM-K-NB-666/cf1476e-pattern-matching)

## 题意
- 给你长度均为 $k$ 的 $n$ 个模式串 $p_i$ 和 $m$ 个字符串 $s_i$，每个 $s_i$ 有一个对应的 $mt_i$，模式串中 `_` 可以匹配任意字符。
- 要求重新排列模式串使得每个 $s_i$ 匹配的第一个模式串是 $p_{mt_i}$。
- $n,m\le10^5,k\le4$

## 分析
我们发现对于一种符合题意的模式串的排列，满足 $p_{1\sim mt_i-1}$ 和 $s_i$不匹配，$p_{mt_i}$ 和 $s_i$ 匹配。可以想到从 $p_{mt_i}$ 向每个与 $s_i$ 匹配的模式串连边，再跑一遍拓扑排序就可以判断是否有解。

然而 $n,m$ 都很大，直接匹配肯定超时，观察到 $k$ 很小，我们想到对于一个长度为 $k$ 的字符串 $s_i$，他最多可能有 $2^k$ 种匹配串，于是我们发现只要找到每个 $s_i$ 的可能匹配的字符串，用哈希存下来，再求出每个模式串的哈希值，从小到大排序，让 $s_i$ 匹配的哈希值在上面二分查找，就能找到每个与 $s_i$ 匹配的模式串了。

时间复杂度为 $O(2^km\log{n})$，空间复杂度为 $O(2^km)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define N 100005
#define ull unsigned long long
using namespace std;
int n,m,k,ls[N],lp[N],mt[N];
char s[N][10],p[N][10];
void init() {
	for(int i=1;i<=n;++i) {
		scanf("%s",p[i]+1);
		lp[i]=strlen(p[i]+1);
	}
	for(int i=1;i<=m;++i) {
		scanf("%s%d",s[i]+1,&mt[i]);
		ls[i]=strlen(s[i]+1);
	}
}
int cm[N];
struct node {ull dat;int id;} mp[N];
bool operator <(node x,node y) {
	return x.dat<y.dat;
}
ull base=13331,mat[N][17];
void dfs(int x,int d,ull ha) {//dfs找到与s匹配的串
	if(d>ls[x]) {
		mat[x][++cm[x]]=ha;
		return;
	}
	dfs(x,d+1,ha*base+s[x][d]);
	dfs(x,d+1,ha*base+'_');
}
vector<int> edge[N];
int ind[N],ans[N];
queue<int> q;
bool bfs() {//拓扑排序
	int cnt=0;
	for(int i=1;i<=n;++i) {
		if(!ind[i]) q.push(i);
	}
	while(!q.empty()) {
		int u=q.front();
		ans[++cnt]=u;
		q.pop();
		int sz=edge[u].size();
		for(int i=0;i<sz;++i) {
			int v=edge[u][i];
			ind[v]--;
			if(!ind[v]) {
				q.push(v);
			}
		}
	}
	return cnt==n;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	init();
	for(int i=1;i<=m;++i) {
		dfs(i,1,0);
	}
	for(int i=1;i<=n;++i) {
		ull ha=0;
		for(int j=1;j<=lp[i];++j) {
			ha=ha*base+p[i][j];
		}
		mp[i].dat=ha,mp[i].id=i;//记录编号防止自环
	}
	sort(mp+1,mp+1+n);//按hash值排序
	for(int i=1;i<=m;++i) {
		bool flg=0;
		for(int j=1;j<=cm[i];++j) {
			node tmp;
			tmp.dat=mat[i][j];
			int l=lower_bound(mp+1,mp+1+n,tmp)-mp;
			while(l<=n&&mp[l].dat==mat[i][j]) {
				if(mp[l].id!=mt[i]) {//不要让mt向自己连边
					edge[mt[i]].push_back(mp[l].id);
					ind[mp[l].id]++;
				} else flg=1;
				l++;
			}
		}
		if(!flg) {
			puts("NO");//如果模式串本身都不与s匹配，肯定无解
			return 0;
		}
	}
	if(bfs()) {
		puts("YES");
		for(int i=1;i<=n;++i) printf("%d ",ans[i]);
		puts("");
	}
	else puts("NO");
	return 0;
}
```

---

