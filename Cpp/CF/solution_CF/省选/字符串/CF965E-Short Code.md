# Short Code

## 题目描述

Arkady's code contains $ n $ variables. Each variable has a unique name consisting of lowercase English letters only. One day Arkady decided to shorten his code.

He wants to replace each variable name with its non-empty prefix so that these new names are still unique (however, a new name of some variable can coincide with some old name of another or same variable). Among such possibilities he wants to find the way with the smallest possible total length of the new names.

A string $ a $ is a prefix of a string $ b $ if you can delete some (possibly none) characters from the end of $ b $ and obtain $ a $ .

Please find this minimum possible total length of new names.

## 说明/提示

In the first example one of the best options is to shorten the names in the given order as "cod", "co", "c".

In the second example we can shorten the last name to "aac" and the first name to "a" without changing the other names.

## 样例 #1

### 输入

```
3
codeforces
codehorses
code
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
abba
abb
ab
aa
aacada
```

### 输出

```
11
```

## 样例 #3

### 输入

```
3
telegram
digital
resistance
```

### 输出

```
3
```

# 题解

## 作者：「已注销」 (赞：15)

先建立`trie`树，问题变为：

给一棵树，有一些黑点。可以把黑点移到祖先处，但两个黑点不能在同一个位置。求最小的黑点深度和。

用堆维护每个子树中黑点的深度，如果根上没用黑点就把最深的移到根。一遍`dfs`即可完成。

每个黑点$x$会被计算$deep_x$次，而$\sum deep_x=n$，再乘上堆的时间

$\mathcal O(n\log n)$

```cpp
#include<bits/stdc++.h>
const int N=100010;
int n,m,id,ans,tr[N][26];
bool b[N]; //串结束标记
char s[N];
std::priority_queue<int>q[N]; //每个点维护大根堆
void dfs(int x,int d){
    for(int y,i=0;i<26;++i)if(y=tr[x][i]){
        dfs(y,d+1);
        while(q[y].size()){
            q[x].push(q[y].top());
            q[y].pop();
        } //合并子节点信息
    }
    if(x&&!b[x]){
        ans-=q[x].top()-d;
        q[x].pop();
        q[x].push(d);
    } //把最深的点移到根
}
int main(){
    scanf("%d",&n);
    for(int x,i=1;i<=n;++i){
        x=0;
        scanf("%s",s+1);
        m=strlen(s+1);
        for(int j=1;j<=m;++j){
            if(!tr[x][s[j]-97])tr[x][s[j]-97]=++id;
            x=tr[x][s[j]-97]; //建trie树，97=='a'
        }
        b[x]=true;
        q[x].push(m);
        ans+=m;
    }
    dfs(0,0);
    printf("%d",ans);
}
```


---

## 作者：「QQ红包」 (赞：8)

## 题目大意

给你n个不同的串，要你找n个串的某个前缀来表示这n个串，并且要求互不相同。

## 题解

~~一眼题，直接看一位可以不可以，如果不可以就两位，以此类推~~

这样贪心是正确的，然后复杂度是错误的。

把所有的数建立个trie。首先所有的串取的前缀都是原串。

每一个点搞一个set，存当前子树，所有的串，取的前缀的长度。

然后如果一个点是空的，就取出当前子树里的串取的前缀长度最大的，放到当前点。

每个点往上转移的时候，启发式合并。

因为有重复的，所以要用multiset。

时间复杂度是$ O(n\log n^2) $ 

```cpp
/*
 * Author: ylx
 * LANG: c++
 * PROG: 965E
 */
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void qmax(int &x,int y) {if (x<y) x=y;}
void qmin(int &x,int y) {if (x>y) x=y;}
inline int read()
{
    char s;
    int k=0,base=1;
    while ((s=getchar())!='-'&&s!=EOF&&!(isdigit(s)));
    if (s==EOF) exit(0);
    if (s=='-') base=-1,s=getchar();
    while (isdigit(s)) k=k*10+(s^'0'),s=getchar();
    return k*base;
}
inline dangqiandianvoid write(int x)
{
    static char cnt,num[15];cnt=0;
    if (!x)
    {
        putchar('0');
        return;
    }
    for (;x;x/=10) num[++cnt]=x%10;
    for (;cnt;putchar(num[cnt--]+48));
}
const int maxn=1e5+100;
int n,m;
char c[maxn];
int fa[maxn],ch[maxn][26],bj[maxn],dep[maxn],id,root,now;
multiset<int> a[maxn];
ll ans;
void add()//插入到trie中
{
    m=strlen(c+1);
    now=root;
    for (int i=1;i<=m;i++)
    {
        if (ch[now][c[i]-'a']==0)
        {
            ch[now][c[i]-'a']=++id;
            fa[id]=now;dep[id]=dep[fa[id]]+1;
        }
        now=ch[now][c[i]-'a'];
    }
    bj[now]=1;
}
multiset<int>::iterator it;
void hb(int x,int y)//启发式合并
{
    if (a[y].empty()) return;
    if (a[y].size()>a[x].size()) a[x].swap(a[y]);
    it=a[y].begin();
    for (;it!=a[y].end();++it)
    {
        a[x].insert(*it);
    }
    a[y].clear();
}
void dfs(int x)
{
    int f2=0;
    for (int i=0;i<26;i++) 
    if (ch[x][i])
    {
        f2=1;
        dfs(ch[x][i]);
    }//遍历子树
    for (int i=0;i<26;i++)
    {
        if (ch[x][i]) hb(x,ch[x][i]);
    }
    if (x==root) return;
    if (bj[x])
    {//插入当前串
        a[x].insert(dep[x]);
        ans+=dep[x];
        return;
    }//取出最大的
    it=a[x].end();--it;
    ans-=*it;
    a[x].erase(it);
    a[x].insert(dep[x]);
    ans+=dep[x];
}
int main()
{
#ifdef ylx
    freopen("965e.in","r",stdin);
    freopen("965e.out","w",stdout);
#endif
    n=read();root=id=1;
    for (int i=1;i<=n;i++) scanf("%s",c+1),add();
    dfs(root);
    printf("%lld\n",ans);
    return 0;
}
//2018年 05月 24日 星期四 19:41:52 CST
```



---

## 作者：Coffee_zzz (赞：2)

有趣题。

不难想到把 $n$ 个字符串都放到 Trie 上维护，这样问题就转化为了：对于一棵有若干个结点的树，其中一些结点上有一个球，每次可以把球移动至它到根结点的路径中没有球的结点上，问最终所有球的深度之和的最小值。

可以考虑对每个结点维护一个大根堆，记录其子树内球的深度。合并子树时，只需要把其每个子结点的大根堆进行启发式合并即可。同时，如果根结点上没有球，可以贪心地把子树内深度最深的球移动至根结点上，正确性显然。

答案即为 Trie 的根结点的大根堆中所有元素之和。要注意需要特殊处理 Trie 的根结点，不能把球移到 Trie 的根结点上。

```c++
#include <bits/stdc++.h>

#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
using namespace std;
typedef long long ll;
const int N=1e5+5,V=26;
string s[N];
int n,r=1,tot=1;
int c[N][V];
priority_queue <int> q[N];
void build(string s){
	int u=r;
	for(int i=0;i<s.size();i++){
		if(!c[u][s[i]-'a']) c[u][s[i]-'a']=++tot;
		u=c[u][s[i]-'a'];
	}
	q[u].push(s.size());
}
void dfs(int u,int dep){
	bool flag=0;
	if(q[u].size()==0) flag=1;
	for(int i=0;i<V;i++){
		int v=c[u][i];
		if(v==0) continue;
		dfs(v,dep+1);
		if(q[u].size()<q[v].size()) swap(q[u],q[v]);
		while(!q[v].empty()) q[u].push(q[v].top()),q[v].pop();
	}
	if(flag) q[u].pop(),q[u].push(dep);
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++) build(s[i]);
	q[r].push(0);
	dfs(r,0);
	ll sum=0;
	while(!q[r].empty()) sum+=q[r].top(),q[r].pop();
	cout<<sum<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：夏色祭 (赞：2)

提供一种分治+贪心的算法。

先把所有字符串按字典序排序。我们可以贪心一下，如果前i位字符都相同的字符串中肯定有且只有一个字符串的保留的前缀长度为i，那么我们就把当前最长的那个字符串保留前i个。然后用递归实现即可。

时间复杂度：$O(n)$ （可能sort的复杂度有点迷）

然后楼下redbag小姐姐的算法吼像不用启发式合并，每个串的长度只会合并它的length次，而length和是$O(n)$的，所以总操作的次数应该就是O(n)的。

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#define rg register
#define il inline
#define vd void
#define ll long long
#define N 100010
#define For(i,x,y) for (rg int i=(x);i<=(y);i++)
#define Dow(i,x,y) for (rg int i=(x);i>=(y);i--)
#define cross(i,k) for (rg int i=first[k];i;i=last[i])
using namespace std;
il ll max(ll x,ll y){return x>y?x:y;}
il ll min(ll x,ll y){return x<y?x:y;}
il ll read(){
    ll x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
int n,ans,a[N];
string s[N];

il vd solve(int dep,int l,int r){
	int L=l,R,Max=0,id;
	while (a[L]<dep&&L<=r) L++;
	if (L>r) return;
	if (L==r){a[L]=dep;return;}
	while (L<=r){
		R=L;
		while (s[L][dep-1]==s[R][dep-1]&&R<=r) R++;
		R--,solve(dep+1,L,R);
		if (a[L]!=dep||L==R){
			Max=0;
			For(i,L,R)
				if (a[i]>Max) Max=a[i],id=i;
			if (Max) a[id]=dep;
		}
		L=R+1;
	}
}

int main(){
	n=read();
	For(i,1,n) cin>>s[i];
	sort(s+1,s+1+n);
	For(i,1,n) a[i]=s[i].length();
	solve(1,1,n);
	For(i,1,n) ans+=a[i];
	printf("%d",ans);
}
```

---

## 作者：Null_h (赞：1)

## 题目大意

给定 $n$ 个字符串，将它们缩减为互不相同的非空前缀，最小化总长度。

## 思路

不难想到，可以使用字典树维护字符串，优先队列维护长度，最后使用从长到短缩减的贪心方法进行 DFS，从而达到最小总长度。当然，如果你会的话，也可以使用启发式合并，此处不赘述。

## 实现方式&&创举

普通字典树实现简单，在时间上很难再优化，但是考虑到如果只有一个很长的字符串，对于每个节点，都会造成其他 $25$ 个空间的浪费。于是可以想到，通过 unordered_map 维护，动态开空间，达到最小空间浪费。

同时为了增加其普适性，我们可以通过记录节点对应下标的方式，建立它与字符的映射，这样，无论对于多么奇怪的字符，都可以直接查询。当然，如果题目要求压缩字典树，我们可以将映射类型改为字符串，非常方便。

在此之上，对于记录节点是否为单词结尾的问题，我们可以在映射中加入特殊判断标记，例如在只有小写字母的情况下，将结尾字符改为大写，通过这种方法，又可以节省一个数组！

本文介绍的字典树构造方法虽然不会优化时间复杂度，但在所需记录内容复杂，或范围较大时有更好的空表现，并且由作者原创，在解决各种问题时有较强的扩展性。

事实上，相对其他代码，这种方法在空间上已经较优，更多的优化并不是必须的。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x=1,ans;
unordered_map<int,unordered_map<int,int> > g;
bool l[100010];
char h[100010];
priority_queue<int> q[100010];
string s;
void dfs(int m,int e){
	for(int i=0;i<g[m].size();i++){
		if(h[g[m][i]]==s[e]){
			dfs(g[m][i],e+1);
			return;
		}
	}
	while(e<s.size()){
		g[m][g[m].size()]=x;
		h[x++]=s[e];
		e++;
		m=g[m][g[m].size()-1];
	}
	q[m].push(s.size());
	l[m]=1;
	ans+=s.size();
	return;
}
void dfs2(int x,int d){
    for(int i=0;i<g[x].size();i++){
        dfs2(g[x][i],d+1);
        while(q[g[x][i]].size()){
            q[x].push(q[g[x][i]].top());
            q[g[x][i]].pop();
        } 
	}
    if(x&&!l[x]){
        ans-=q[x].top()-d;
        q[x].pop();
        q[x].push(d);
    } 
}
int main(){
    ios::sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		dfs(0,0);
	}
	dfs2(0,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：Jorisy (赞：1)

模拟赛考了这题，写发题解。

首先容易想到用 trie 维护。

然后我们记 trie 是用 $ed_i$ 来标记的。

于是我们认为一开始每个字符串前缀的末尾都在 $ed$ 标记的位置。

接着我们从下往上搜。

对于每个子树，如果其根节点有字符串，那么我们直接累加深度；如果没有，我们贪心地考虑将深度最大的提到该根节点然后再累加。

那我们就可以用堆维护。

在往上搜时，就把以节点为根的子树中的堆全部合并。记得要启发式合并。
```cpp
#include<bits/stdc++.h>
using namespace std;

priority_queue<int>q[100005];
int n,trie[100005][35],dep[100005],t;
long long ans;
bool ed[100005];

void insert(string s)//trie 插入
{
	int p=0;
	for(int i=0;i<s.size();i++)
	{
		int id=s[i]-97;
		if(!trie[p][id])
		{
			trie[p][id]=++t;
			dep[t]=dep[p]+1;
		}
		p=trie[p][id];
	}
	ed[p]=1;
}

void merge(int u,int v)
{
	if(q[u].size()<q[v].size()) swap(q[u],q[v]);//启发式合并
	while(!q[v].empty())
	{
		q[u].push(q[v].top());
		q[v].pop();
	}
}

void dfs(int p)
{
	for(int i=0;i<26;i++)
	{
		if(trie[p][i]) dfs(trie[p][i]);//先往下搜
	}
	for(int i=0;i<26;i++)
	{
		if(trie[p][i]) merge(p,trie[p][i]);//然后合并
	}
	if(!p) return;//是 trie 总的 root 就可以不做了
	if(ed[p])//子树根节点有东西
	{
		ans+=dep[p];
		q[p].push(dep[p]);
		return;
	}
	ans-=q[p].top()-dep[p];
	q[p].pop();
	q[p].push(dep[p]);
    //子树根节点没东西
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		insert(s);
	}
	dfs(0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：hellolin (赞：0)

# CF965E Short Code 题解

评紫还是虚高了。

看到字符串前缀，不难想到可以结合 trie 来做。

问题相当于在 trie 树上，把一些标记（字符串结尾节点）向根移动，一个节点不能有多个标记，问最终标记深度之和的最小值。

我们贪心地去考虑，对于一个子树，显然把深度最深的点拉到当前子树根节点是最优的。

注意转换后的字符串非空，所以不能跳到根节点。

``` cpp
multiset<int> *uni(multiset<int> *x, multiset<int> *y) {
  if (x->size() < y->size()) swap(x, y);
  for (const int &i : *x)
    y->insert(i);
  delete x;
  return y;
}
// dfs 返回一个带有所有标记节点深度的 multiset
multiset<int> *dfs(node *cur, int dep) {
  multiset<int> *now = new multiset<int>;
  for (int i = 0; i < 26; ++i) {
    if (cur->son[i] != nullptr) now = uni(now, dfs(cur->son[i], dep + 1));
  }
  if (cur->end)
    now->insert(dep);
  else if (cur != rt) { // 不能跳到根节点
    now->insert(dep);
    now->erase(--now->end());
  }
  return now;
}
```

---

## 作者：Purslane (赞：0)

# Solution

自底向上贪心。

对于 trie 树上的每个节点，把它子树中所有的关键点找出来。如果当前节点是空的，把最深的关键点提出来放到当前节点上。

不需要写启发式合并，因为 $\sum_{i=1}^n dep_{id_i} = \sum_{i=1}^m |S_i|$ 可以接受。但是当时没有意识到。

复杂度 $O(n \log n)$。（认为 $\sum len$ 和 $n$ 同阶）

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,tot,tr[MAXN][27],flg[MAXN],dep[MAXN];
multiset<int> st[MAXN];
void merge(multiset<int>& x,multiset<int>& y) {
    if(x.size()<y.size()) swap(x,y);
    for(auto id:y) x.insert(id);
    y.clear();
    return ;
}
void insert(string S) {
    int u=0;
    for(auto ch:S) {
        if(!tr[u][ch-'a']) tr[u][ch-'a']=++tot,dep[tot]=dep[u]+1;
        u=tr[u][ch-'a'];
    }
    flg[u]=1;
    return ;
}
void dfs(int u) {
    ffor(i,0,25) if(tr[u][i]) dfs(tr[u][i]),merge(st[u],st[tr[u][i]]);
    if(u) {
        if(flg[u]) st[u].insert(dep[u]);
        else st[u].erase(--st[u].end()),st[u].insert(dep[u]);
    }
    return ;
}
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;
    ffor(i,1,n) {
        string S;
        cin>>S,insert(S);
    }
    dfs(0);
    int sum=0;
    for(auto id:st[0]) sum+=id;
    cout<<sum;
    return 0;
}
```

---

## 作者：EricWan (赞：0)

我们看到这题（的标签）肯定要先创建字典树，之后使用启发式合并进行结果的计算。

创建字典树的过程我就不赘述了，我们来看看建立树之后怎样计算。

抽象成一个树后，我们假想每个有字符串的地方有一个不受重力影响的小球（总根也有），我们重新放置小球（小球只能在它的原始祖先或它自己的位置上，不能重合）后想让小球的深度和最小。

我们从叶子向上遍历，对于某一个点，如果它是空的那么让他的子树中现在深度最深的小球来到它的位置上，这样贪心是正确的，我们可以使用优先队列（堆）维护最深的小球，对于优先队列的合并，我们使用启发式合并。

代码：

```
#include <bits/stdc++.h>
using namespace std;
int n, ans, trie[100005][29], sum[100005], fa[100005], deepth[100005], cnt, vis[100005], sumstr;
string s[100005];
void merge_EricWanAKCSPJ(priority_queue<int> &now, priority_queue<int> son) {
	if (now.size() <= son.size()) swap(now, son);
	while (!son.empty()) {
		now.push(son.top());
		son.pop();
	}
}
priority_queue<int> dfs(int id, const int de) {
	priority_queue<int> now;
	for (int i = 0; i < 26; i++) {
		if (trie[id][i] == 0) continue;
		merge_EricWanAKCSPJ(now,dfs(trie[id][i],de + 1));
	}
	for (int i = 1; i <= vis[id]; i++) now.push(de);
	if (!vis[id] && !now.empty()) {
		ans += now.top() - de;
		now.pop();
		now.push(de);
	}
	return now;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		int x = 0;
		for (int j = 0; j < s[i].size(); j++) {
			if (trie[x][s[i][j] - 'a'] == 0) {
				cnt++;
				fa[cnt] = x;
				deepth[cnt] = j + 1;
				trie[x][s[i][j] - 'a'] = cnt;
			}
			x = trie[x][s[i][j] - 'a'];
			sum[x]++;
		}
		sum[0]++;
		vis[x]++;
		sumstr += s[i].size();
	}
    vis[0] = 1;
	dfs(0,0);
	cout << sumstr - ans;
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

就我用左偏树写了？/ng

看到前缀啥的就先把 trie 建出来！问题变成了在 trie 树上选 $n$ 个点，对于这 $n$ 个点与给定字符串的尾结点两两匹配，使得每组中选的点都是给定字符串的祖先。

那我们考虑一棵树如何从其所有子树合并。发现子树若已经有选定的点集的话，如果当前树根节点是字符串结尾，那么这个点选上；否则，这个点显然是这棵树内任意结点的祖先，于是我们贪心将当前子树内选定深度最大的点删掉，并将当前点选上即可。

这个怎么维护呢？左偏树（可并堆）！！！11

然后 dfs 一遍就做完了。

$\Theta(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e5 + 10;

struct Node { int dep, end, siz, ch[26]; };
int n, ans;
string s;
Node tr[maxn];
int d[maxn], tot = 1;
int dis[maxn];
int ls[maxn], rs[maxn];
int del[maxn], fa[maxn];

int merge(int u, int v) {
	if (!u || !v) return u + v;
	if (tr[u].dep < tr[v].dep) swap(u, v);
	rs[u] = merge(rs[u], v);
	if (dis[ls[u]] < dis[rs[u]]) swap(ls[u], rs[u]);
	dis[u] = dis[rs[u]] + 1;
	return u;
}

int find(int u) {
	if (fa[u] == u) return fa[u];
	return fa[u] = find(fa[u]);
}

void insert(string s) {
	int u = 1;
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!tr[u].ch[c]) tr[u].ch[c] = ++tot, tr[tot].dep = tr[u].dep + 1;
		u = tr[u].ch[c];
	}
	tr[u].end++;
}

int rem(int u) {
	u = find(u);
	int k = u;
	del[u] = true;
	fa[ls[u]] = fa[rs[u]] = fa[u] = merge(ls[u], rs[u]);
	ls[u] = rs[u] = dis[u] = 0;
	return k;
}

void dfs(int u) {
	for (int i = 0; i < 26; i++) {
		if (tr[u].ch[i]) {
			dfs(tr[u].ch[i]);
			int x = find(u), y = find(tr[u].ch[i]);
			if (x != y) fa[x] = fa[y] = merge(x, y);
		}
	}
	if (!tr[u].end && u != 1) rem(u);
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s, insert(s);
	for (int i = 1; i <= tot; i++) fa[i] = i;
	dfs(1);
	int ans = 0;
	while (!del[1]) ans += tr[rem(1)].dep;
	cout << ans;
	return 0;
}
```

---

## 作者：xyf007 (赞：0)

### 题目大意
给出$n$个字符串$s_i$，要求为每个字符串分配它的一个非空前缀$pre_i$，使得所有的$pre_i$互不相同，且使得$pre_i$的长度和最小。
### 题解
- 首先我们要建出$n$个串的字典树，现在的问题是给定了树上的一些点，要给每个点在它到根的路径上分配一个点使得这些点的深度和最小。
- 那么首先每个点都可以选自己所在的位置。我们设$f_i$为在$i$为根的子树里的点都被分配了一个在子树里的点的最小方案。
- 注意到如果$i$这个点有东西，那么$f_i$就等于所有儿子之和。而若$i$没东西,那么可以从所有的儿子里选择一个深度最深的点放到根上。所以我们需要对每个$f_i$维护一个堆。并每次把所有儿子的堆都合并起来。
- 对于合并，我们只需要启发式即可，利用priority_queue相对来说比较方便一些。时间复杂度$O(nlog^2(n))$.
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
int n, trie[100001][26], dep[100001], tot, ans;
bool f[100001];
priority_queue<int> a[100001];
void insert(string s)
{
	int root = 0;
	for (int i = 0; i < (int)s.size(); i++)
	{
		int id = s[i] - 'a';
		if (!trie[root][id])
		{
			trie[root][id] = ++tot;
			dep[tot] = dep[root] + 1;
		}
		root = trie[root][id];
	}
	f[root] = 1;
}
void merge_heap(int x, int y)
{
	if (a[x].size() < a[y].size())
	{
		a[x].swap(a[y]);
	}
	while (!a[y].empty())
	{
		a[x].push(a[y].top());
		a[y].pop();
	}
}
void dfs(int u)
{
	for (int i = 0; i < 26; i++)
	{
		if (trie[u][i])
		{
			dfs(trie[u][i]);
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (trie[u][i])
		{
			merge_heap(u, trie[u][i]);
		}
	}
	if (!u)
	{
		return;
	}
	if (f[u])
	{
		ans += dep[u];
		a[u].push(dep[u]);
		return;
	}
	ans -= a[u].top() - dep[u];
	a[u].pop();
	a[u].push(dep[u]);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		insert(s);
	}
	dfs(0);
	printf("%d", ans);
	return 0;
}
```

---

