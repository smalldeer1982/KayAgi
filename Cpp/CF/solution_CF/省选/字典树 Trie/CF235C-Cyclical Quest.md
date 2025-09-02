# Cyclical Quest

## 题目描述

Some days ago, WJMZBMR learned how to answer the query "how many times does a string $ x $ occur in a string $ s $ " quickly by preprocessing the string $ s $ . But now he wants to make it harder.

So he wants to ask "how many consecutive substrings of $ s $ are cyclical isomorphic to a given string $ x $ ". You are given string $ s $ and $ n $ strings $ x_{i} $ , for each string $ x_{i} $ find, how many consecutive substrings of $ s $ are cyclical isomorphic to $ x_{i} $ .

Two strings are called cyclical isomorphic if one can rotate one string to get the other one. 'Rotate' here means 'to take some consecutive chars (maybe none) from the beginning of a string and put them back at the end of the string in the same order'. For example, string "abcde" can be rotated to string "deabc". We can take characters "abc" from the beginning and put them at the end of "de".

## 样例 #1

### 输入

```
baabaabaaa
5
a
ba
baa
aabaa
aaba
```

### 输出

```
7
5
7
3
5
```

## 样例 #2

### 输入

```
aabbaa
3
aa
aabb
abba
```

### 输出

```
2
3
3
```

# 题解

## 作者：ouuan (赞：16)

欢迎到[我的博客](https://ouuan.github.io/CF235C-Cyclical-Quest%EF%BC%88SAM%EF%BC%89/)阅读。

# 题目链接

[洛谷](https://www.luogu.org/problemnew/show/CF235C)

[CF problemset](https://codeforces.com/problemset/problem/235/C)

[CF contest](https://codeforces.com/contest/235/problem/C)

# 题意简述

给你一个字符串 $s$ 和 $n$ 个字符串 $x_{1..n}$，对每个 $x_i$，求有多少个 $s$ 的子串可以由 $x_i$ 旋转得到。

旋转一个字符串就是把它的一个前缀移到后面，如 `abcd` 可以旋转得到的字符串有 `abcd`，`bcda`，`cdab`，`dabc`。

# 简要做法

对 $s$ 建 SAM，把 $x_i$ 旋转得到的每个字符串用 SAM 读入，就可以求答案了。（SAM 求子串出现次数是经典问题，可以参考[我的博客](https://ouuan.github.io/%E5%90%8E%E7%BC%80%E8%87%AA%E5%8A%A8%E6%9C%BA%EF%BC%88SAM%EF%BC%89%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/#%E5%AD%90%E4%B8%B2%E5%87%BA%E7%8E%B0%E6%AC%A1%E6%95%B0)）

分开读入每个 $x_i$ 旋转得到的字符串显然会超时，然而，SAM 读入字符串是支持删除首字符的：记录当前读入的长度 $l$ 以及所处状态 $u$，删除字符就把 $l$ 减一，若减一后 $l=len(parent(u))$，则转移到 $parent(u)$（把 $u$ 赋值为 $parent(t)$）。需要注意的是，如果读入一个字符的时候当前状态没有这个字符的出边，就需要在 $parent$ 树上向上跳，直到有这个字符的出边，同时更新 $l$ 。这样的话，删除字符前就要先判断 $l$ 与需要保留的字符串的长度的关系。具体细节可以参考代码及注释。

所以，先读入 $x_i$ 统计答案，再删去首字符读入 $x_i[0]$ 统计答案，删去首字符读入 $x_i[1]$ 统计答案……就只用读入 $O(len(x_i))$ 个字符。

还有一个问题，就是去重。$s$ 的一个子串可能可以和 $x_i$ 不同的旋转匹配。解决这个问题有两个方法，第一个是求出 $x_i$ 的周期（可以用 kmp 求），第二个方法是在 SAM 上打标记。我用的是打标记的方法，具体细节还是可以参考代码及注释。

# 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdio>

using namespace std;

const int N=1000010;

struct Node
{
	int len,par,ch[26],vis,cnt;
} sam[N<<1];

void insert(int x);
void read(int x);
void del();
void calc();
void add(int u,int v);
void dfs(int u);

char s[N];
int head[N<<1],nxt[N<<1],to[N<<1],cnt;
int p,tot,n,m,l,u,tim,ans;

int main()
{
	int i;
	
	scanf("%s%d",s,&n);
	
	sam[0].par=-1;
	for (i=0;s[i];++i) insert(s[i]-'a');
	for (i=1;i<=tot;++i) add(sam[i].par,i);
	dfs(0);
	
	for (tim=1;tim<=n;++tim)
	{
		scanf("%s",s);
		m=strlen(s);
		ans=u=l=0;
		for (i=0;i<m;++i) read(s[i]-'a');
		calc();
		for (i=0;i<m-1;++i)
		{
			read(s[i]-'a');
			del();
			calc();
		}
		printf("%d\n",ans);
	}
	
	return 0;
}

void read(int x) //读入一个字符
{
	while (u&&!sam[u].ch[x]) l=sam[u=sam[u].par].len; //向上跳直至有这个字符的出边
	if (sam[u].ch[x])
	{
		++l;
		u=sam[u].ch[x];
	}
}

void del() //删除首字符
{
	if (l>m&&--l==sam[sam[u].par].len) u=sam[u].par; //m表示当前xi的长度，只有l>m的时候才删除
}

void calc() //计算当前的答案
{
	if (l==m&&sam[u].vis<tim) //只有当前读入的串长度恰好为m且当前状态没有打上标记时才统计答案
	{
		ans+=sam[u].cnt;
		sam[u].vis=tim; //打标记
	}
}

void insert(int x) //向SAM中插入字符，有人把这个函数叫做extend
{
	int np=++tot;
	sam[np].len=sam[p].len+1;
	sam[np].cnt=1;
	while (~p&&!sam[p].ch[x])
	{
		sam[p].ch[x]=np;
		p=sam[p].par;
	}
	if (p==-1) sam[np].par=0;
	else
	{
		int q=sam[p].ch[x];
		if (sam[q].len==sam[p].len+1) sam[np].par=q;
		else
		{
			int nq=++tot;
			sam[nq].len=sam[p].len+1;
			memcpy(sam[nq].ch,sam[q].ch,sizeof(sam[q].ch));
			sam[nq].par=sam[q].par;
			sam[q].par=sam[np].par=nq;
			while (~p&&sam[p].ch[x]==q)
			{
				sam[p].ch[x]=nq;
				p=sam[p].par;
			}
		}
	}
	p=np;
}

void add(int u,int v) //加边，用于遍历parent树
{
	nxt[++cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}

void dfs(int u) //遍历parent树，计算每个状态的出现次数
{
	int i,v;
	for (i=head[u];i;i=nxt[i])
	{
		v=to[i];
		dfs(v);
		sam[u].cnt+=sam[v].cnt;
	}
}
```

---

## 作者：issue_is_fw (赞：10)

[LINK](https://www.luogu.com.cn/problem/CF235C)

**题意**

给定一个主串$S$和$n$个询问串，求每个询问串的所有循环同构在主串中出现的次数总和。

---

对$s$建立$SAM$,顺便求出$siz[p]$表示$p$代表的集合在$s$中出现了多少次

把每个询问串$t$复制一份接在后面,我们匹配这个新串$T$

**那么问题转化为,能匹配多少$T$的子串长度为$|t|$**

就是$T$串在$SAM$上跑,看看对于$T$每个前缀$[1,i]$是否最大匹配长度大于等于$|t|$

设匹配$[1,i]$跑到了$SAM$上的$p$点,匹配长度是$l$

若当前匹配长度$l$大于等于$|t|$就是匹配成功

那么对答案的贡献是多少呢??是加上$siz[p]$吗??

当然不是,$siz[p]$是$[i-l+1,i]$的出现次数,我们需要求的是$[i-|t|+1,i]$的

那就简单了,我们直到$parent$树上的祖先是孩子的后缀,我们一直往上$father$

直到父亲的$longest$小于$|t|$

此时的$p$点的集合中必然包括$[i-|t|+1,i]$这个子串,加上$siz[p]$即可

不过循环同构可能相等啊...打个标记即可,每个节点只算一次贡献

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6+10;
int n,id=1,ed=1,len;
char a[maxn];
struct SAM
{
	int zi[26],len,fa;
}sam[maxn]; int siz[maxn];
void insert(int c)
{
	int p = ed, np = ++id; ed = id;
	sam[np].len = sam[p].len+1; siz[np] = 1;
	for( ;p&&!sam[p].zi[c];p=sam[p].fa )	sam[p].zi[c] = np;
	if( p==0 )	sam[np].fa = 1;
	else
	{
		int q = sam[p].zi[c];
		if( sam[q].len==sam[p].len+1 )	sam[np].fa = q;
		else
		{
			int nq = ++id; 
			sam[nq] = sam[q], sam[nq].len = sam[p].len+1;
			sam[q].fa = sam[np].fa = nq;
			for( ;p&&sam[p].zi[c]==q;p=sam[p].fa )	sam[p].zi[c] = nq;
		}
	}
} 
int c[maxn],rk[maxn],vis[maxn];
void tuopu()
{
	for(int i=1;i<=id;i++)	c[sam[i].len]++;
	for(int i=1;i<=id;i++)	c[i] += c[i-1];
	for(int i=1;i<=id;i++)	rk[c[sam[i].len]--] = i;
	for(int i=id;i>=1;i--)
	{
		int u = rk[i], fa = sam[u].fa;
		siz[fa] += siz[u];
	}
}
int main()
{
	cin >> ( a+1 ); len = strlen( a+1 );
	for(int i=1;i<=len;i++)	insert( a[i]-'a' );
	tuopu();
	cin >> n;
	for(int w=1;w<=n;w++)
	{
		cin >> ( a+1 ); len = strlen( a+1 );
		for(int i=1;i<=len;i++)	a[i+len] = a[i];
		int ans = 0, p = 1, l = 0;
		for(int i=1;i<=len+len;i++)
		{ 
			int c = a[i]-'a';
			if( sam[p].zi[c] )	p = sam[p].zi[c],l++;
			else
			{
				while( p&&!sam[p].zi[c] )	p = sam[p].fa;
				if( p==0 )	p = 1, l = 0;
				else	l = sam[p].len+1, p = sam[p].zi[c];
			}
			if( l>=len )
			{
				while( sam[sam[p].fa].len>=len )	p = sam[p].fa;
				if( vis[p]!=w )
					ans+=siz[p],vis[p] = w;
				l = len;
			}
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Alex_Wei (赞：8)

> [CF235C Cyclical Quest 题目传送门](https://www.luogu.com.cn/problem/CF235C)

> 题意简述：给出 $s$，多次询问给出字符串 $t$ 所有循环同构串**去重**后在 $s$ 中出现次数之和。

本文节选自 [我的 SAM 做题笔记](https://www.cnblogs.com/alex-wei/p/Suffix_Automaton_Involution.html)，标号为 XII。

---

如果没有循环同构那么就是 ACAM/SA/SAM 板子题。关于循环同构的一个常见套路就是将 $t$ 复制一份在后面。那么我们如法炮制，用 $2t$ 在 SAM 上跑匹配。如果**当前长度大于 $|t|$**，那么就不断**将匹配长度 $d$ 减一**，同时判断**当前状态是否能表示长度为 $d$ 的字符串**（即是否有 $len(link(p))<d\leq len(p)$），如果没有就要向上跳。

注意到题目需要去重，同时两个长度为 $|t|$ 的 $s$ 的不同子串一定被不同的状态表示，所以计算一个位置贡献后打上标记，后面再遇到这个位置就不算贡献了，每次查询后撤销标记即可（可以用 vector 记录打上标记的位置）。

时间复杂度为 $\mathcal{O}(|s||\Sigma|+\sum|t|)$，其中 $\Sigma$ 为字符集。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb emplace_back

const int N=2e6+5;
const int S=26;

int las,cnt;
int son[N][S],len[N],fa[N],ed[N];
int buc[N],id[N],vis[N];
void ins(char s){
	int p=las,cur=++cnt,it=s-'a';
	len[cur]=len[p]+1,ed[cur]++,las=cur;
	while(p&&!son[p][it])son[p][it]=cur,p=fa[p];
	if(!p)return fa[cur]=1,void();
	int q=son[p][it];
	if(len[p]+1==len[q])return fa[cur]=q,void();
	int cl=++cnt;
	fa[cl]=fa[q],fa[q]=fa[cur]=cl,len[cl]=len[p]+1;
	memcpy(son[cl],son[q],sizeof(son[q]));
	while(son[p][it]==q)son[p][it]=cl,p=fa[p];
} void build(char *s){
	int n=strlen(s+1); las=cnt=1;
	for(int i=1;i<=n;i++)ins(s[i]);
	for(int i=1;i<=cnt;i++)buc[len[i]]++;
	for(int i=1;i<=cnt;i++)buc[i]+=buc[i-1];
	for(int i=cnt;i;i--)id[buc[len[i]]--]=i;
	for(int i=cnt;i;i--)ed[fa[id[i]]]+=ed[id[i]];
}

int n;
char s[N];
int main(){
	scanf("%s%d",s+1,&n),build(s);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		ll p=1,l=strlen(s+1),d=0,ans=0;
		vector <int> del; 
		for(int i=1;i<l*2;i++){
			int it=s[i>l?i-l:i]-'a';
			while(p&&!son[p][it])p=fa[p],d=len[p];
			if(p){
				p=son[p][it],d++;
				while(d>l)if((--d)<=len[fa[p]])p=fa[p];
				if(d>=l&&!vis[p])ans+=ed[p],vis[p]=1,del.pb(p);
			} else p=1;
		} cout<<ans<<endl;
		for(int it:del)vis[it]=0;
	}
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：4)

## 后缀数组这么没排面的吗？这个题都没有 SA 题解？

题意略。

循环同构，按照套路我们把每个 $x_i$ 倍长后得到 $y_i$ 顺次连接，再与 $S$ 连接起来建立后缀数组。

倍长后每个可能的循环同构就成为了 $y_i$ 的长为 $|x_i|$  的子串。如何判断它们是否循环同构？只要查询 $lcp$ 是否大于等于 $|x_i|$ 就可以了。那么我们可以按照后缀排序从前往后扫一遍后缀数组，记录每个 $y_i$ 上次出现的位置，当再遇到 $y_i$ 的子串时，判断是否是一个新的循环同构。如果是的话再统计在 $S$ 中的出现次数。这也是后缀数组的基本操作：预先把后缀数组上每个是 $S$ 的某一字符开头的位置 $+1$，查询时两边二分得出与该串 $lcp$ 大于等于 $|x_i|$ 的后缀数组上的区间，再查询区间和就可以了。这就是简单的前缀和相减。

时空复杂度均为 $O(n\log n)$。

---

## 作者：xtx1092515503 (赞：4)

大家都是打标记解法的说……因此本题解采用的是找出最小循环节的解法。

------------

考虑对原串建出SAM。

假如我们要求出某个子串本身的出现次数，只需要在SAM上按顺序走到其所对应的节点，然后该节点的 $\text{endpos}$ 集合大小就是其出现次数。

现在要你求出其所有循环同构的出现次数总和。在初学SAM时，大家可能听说过这样一句话：

“在SAM上沿着边走相当于往字符串后面加字符，在parent tree上沿着边走相当于往字符串前面加字符”

于是我们现在考虑已经求出了某个询问串在SAM上所对应的节点。在parent tree上往下走是往前面加字符，那么在上面跳父亲就相当于在前面删字符了。于是考虑删除最前面一个字符所得到的新串所对应的 $\text{endpos}$ 集合，若其与当前串所对应集合不同，则明显其只有可能是当前集合的父亲，于是往上跳一步即可。上跳一步后，便可以对向右移位一位的同构串进行处理了。

为了避免重复计算，我们只处理询问串的最小循环节内的同构串。最小循环节可以通过KMP/Z/哈希处理，这里使用Z算法。

总复杂度 $O(n|\Sigma|)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1001000;
int cnt=1;
struct Suffix_Automaton{int ch[26],fa,len;}t[N<<1];
char s[N];
int S,q,sz[N<<1],Z[N];
int Add(int x,int c){
	int xx=++cnt;t[xx].len=t[x].len+1,sz[xx]=1;
	for(;x&&!t[x].ch[c];x=t[x].fa)t[x].ch[c]=xx;
	if(!x){t[xx].fa=1;return xx;}
	int y=t[x].ch[c];
	if(t[y].len==t[x].len+1){t[xx].fa=y;return xx;}
	int yy=++cnt;t[yy]=t[y],t[yy].len=t[x].len+1;
	t[y].fa=t[xx].fa=yy;
	for(;x&&t[x].ch[c]==y;x=t[x].fa)t[x].ch[c]=yy;
	return xx;
}
vector<int>v[N<<1];
void dfs(int x){for(auto y:v[x])dfs(y),sz[x]+=sz[y];}
void Zalgorithm(){
	int Centre=-1,Rpos=-1;
	for(int i=1;i<S;i++){
		if(i<=Rpos)Z[i]=min(Rpos-i,Z[i-Centre]);else Z[i]=0;
		while(i+Z[i]<S&&s[Z[i]]==s[i+Z[i]])Z[i]++;
		if(i+Z[i]>Rpos)Rpos=i+Z[i],Centre=i;
	}
}
ll Cyclical(){
	ll ret=0;
	for(int i=0,j=0,x=1;i<S&&(i+Z[i]<S||!i||S%i);i++){
		if(!x)x=1;
		for(j=max(i,j);j!=i+S;j++)if(t[x].ch[s[j%S]-'a'])x=t[x].ch[s[j%S]-'a'];else break;
//		printf("%d %d %d %d\n",i,j,x,sz[x]);
		if(j==i+S)ret+=sz[x];
		if(j-i==t[t[x].fa].len+1)x=t[x].fa;
	}
	return ret;
}
int main(){
	scanf("%s%d",s,&q),S=strlen(s);
	for(int i=0,las=1;i<S;i++)las=Add(las,s[i]-'a');
	for(int i=2;i<=cnt;i++)v[t[i].fa].push_back(i);
	dfs(1);
//	for(int i=1;i<=cnt;i++)for(int j=0;j<26;j++)if(t[i].ch[j])printf("%d %d %c\n",i,t[i].ch[j],'a'+j);
//	for(int i=1;i<=cnt;i++)printf("%d %d\n",t[i].fa,t[i].len);
//	for(int i=1;i<=cnt;i++)printf("%d ",sz[i]);puts("");
	while(q--){
		scanf("%s",s),S=strlen(s);
		Zalgorithm();
		printf("%lld\n",Cyclical());
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

首先对 $s$ 建 SAM，设 $m = |t|$，然后考虑断环为链，把询问串 $t$ 再复制一份拼接在后面，然后相当于问现在 $t$ 的所有长度为 $m$ 的**本质不同**子串在 $s$ 中的出现次数之和。

考虑枚举子串的右端点，维护当前在 SAM 上的结点 $u$，每次尝试将匹配长度 $+1$。如果匹配长度 $> m$ 那么需要“删除”开头的一些字符，如果匹配长度 $= m$ 那么就将 $\text{sz}(u)$ 累加进答案，同时标记 $u$ 为了不重复访问（所有长度固定的串在 SAM 上对应的结点一定两两不同）。

考虑如何“删除”字符。我们发现 $\text{link}(u)$ 恰好满足我们的需求，因为 $\text{link}(u)$ 的定义为 SAM 上对应于 $u$ 代表的集合的串的最长后缀的另一个 $\text{endpos}$ 等价类的状态，所以当 $\text{len}(\text{link}(u)) \ge m$ 时我们就令 $u \gets \text{link}(u)$ 即可。

所以总时间复杂度就是 $O(n + \sum m)$。

[code](https://codeforces.com/contest/235/submission/236763321)

---

## 作者：__gcd (赞：2)

翻了一下题解区似乎没有和我一样的做法？

## 题意

给定主串 $S$ 和多个询问，每次询问一个串的所有本质不同循环同构在 $S$ 中的出现个数。

## 题解

考虑对 $S$ 建出 SAM，并把询问串复制一份解决循环同构问题。我们用得到的新串在 SAM 上跑匹配，如果当前匹配长度大于等于询问串的长度，我们就需要找到当前串属于哪个 $\rm endpos$ 等价类并统计答案。具体地，就是找到 $\rm parent$ 树上面的一个结点 $u$，满足 $\text{len}(u)\geq l\land \text{len}(\text{link}_u)<l$。倍增跳即可。因为需要本质不同，所以统计完之后需要打上标记。因为 $\rm endpos$ 集合只有包含和不交关系，而此处不可能包含，所以不会算重。

时间复杂度 $O((|S|+\sum x_i)\log |S|)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
using namespace std;
inline int read() {
	int x = 0; bool op = 0;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x;
}
const int N = 2000010;
int tot, lst, top;
int lk[N], nxt[N], len[N], cnt[N], sz[N], p[N], tr[N][26], stk[N], vis[N], dp[N][25];
char s[N];
void extend(int c) {
	int p = lst, cur = ++tot;
	len[cur] = len[lst] + 1; sz[cur] = 1;
	while(p != -1 && tr[p][c] == 0)tr[p][c] = cur, p = lk[p];
	if(p == -1)lk[cur] = 0;
	else {
		int q = tr[p][c];
		if(len[q] == len[p] + 1)lk[cur] = q;
		else {
			int cp = ++tot;
			lk[cp] = lk[q]; len[cp] = len[p] + 1;
			memcpy(tr[cp], tr[q], sizeof(tr[q]));
			while(p != -1 && tr[p][c] == q)tr[p][c] = cp, p = lk[p];
			lk[q] = lk[cur] = cp;
		}
	}
	lst = cur;
	return ;
} 
void build(char *s) {
	int l = strlen(s); lk[0] = -1;
	for(int i = 0; i < l; i++)extend(s[i] - 'a');
	for(int i = 1; i <= tot; i++)cnt[len[i]]++;
	for(int i = 1; i <= tot; i++)cnt[i] += cnt[i - 1];
	for(int i = tot; i; i--)p[cnt[len[i]]--] = i;
	for(int i = 1; i <= tot; i++) {
		int now = p[i];
		dp[now][0] = lk[now];
		for(int j = 1; j <= 20; j++)dp[now][j] = dp[dp[now][j - 1]][j - 1];
	} 
	for(int i = tot; i; i--) {
		int now = p[i];
		sz[lk[now]] += sz[now];
	}
	return ;
}
int calc(int u, int l) {
	for(int i = 20; i >= 0; i--) {
		if(len[dp[u][i]] >= l)u = dp[u][i];
	}
	if(vis[u] == 0) {vis[u] = 1; stk[++top] = u; return sz[u];}
	return 0;
}
void solve() {
	scanf("%s", s);
	int l = strlen(s), res = 0;
	for(int i = 0; i < l; i++)s[i + l] = s[i];
	for(int i = 0, u = 0, ml = 0; i < l * 2; i++) {
		int c = s[i] - 'a';
		while(u != -1 && tr[u][c] == 0)u = lk[u], ml = len[u];
		if(u == -1) {u = ml = 0;}
		else {u = tr[u][c]; ml++;}
		if(ml >= l)res += calc(u, l);
	}
	printf("%d\n", res);
	while(top)vis[stk[top--]] = 0;
	return ;
}
int main() {
	scanf("%s", s);
	build(s);
	int test = read();
	while(test--)solve();
	return 0;
}


```


---

## 作者：SFlyer (赞：1)

首先，是循环同构，所以可以把这个串复制一遍，$x\rightarrow x+x$。把 $S$ 的 SAM 建出来，然后我们要找到的就是 SAM 上匹配长度 $\ge |x|$ 的位置。

在匹配的时候设现在在 SAM 上点 $p$。如果 $trans(p,c)\neq null$，可以直接走，匹配长度加一；否则就要一直跳 $fa(p)$ 直到有，如果没有，就直接设为 $p=t_0$，反之长度变为 $len(p)+1$，$p\leftarrow trans(p,c)$。这个时候，也许长度 $>|x|$，我们真正匹配不是现在的。这个时候就要 $p\leftarrow fa(p)$ 直到 $len(fa(p))<|x|$。

因为 $x$ 有可能有循环节，所以要去重。这个呢直接用一个 $vis$ 数组记录上一个访问这个状态的是哪一个询问的 $x$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e6+6;

int tot=1,lst=1,vis[N];

struct sam {
	int len,ch[27],fa;
} t[N];

int n;
string s;
vector<int> g[N];
ll ans,dp[N];

void ins(int c){
	int p=lst,np=++tot;
	t[np].len=t[p].len+1;
	dp[np]=1;
	lst=np;
	while (p && !t[p].ch[c]){
		t[p].ch[c]=np;
		p=t[p].fa;
	}
	if (!p){
		t[np].fa=1;
		return;
	}
	int q=t[p].ch[c];
	if (t[q].len==t[p].len+1){
		t[np].fa=q;
		return;
	}
	int nq=++tot;
	t[nq]=t[q];
	t[nq].len=t[p].len+1;
	t[q].fa=t[np].fa=nq;
	while (p && t[p].ch[c]==q){
		t[p].ch[c]=nq;
		p=t[p].fa;
	}
}

void dfs(int u){
	for (auto v : g[u]){
		dfs(v);
		dp[u]+=dp[v];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>s;
	n=s.size();
	s=" "+s;
	for (int i=1; i<=n; i++){
		ins(s[i]-'a');
	}
	for (int i=2; i<=tot; i++){
		g[t[i].fa].push_back(i);
	}
	dfs(1);
	int T;
	cin>>T;
	for (int tc=1; tc<=T; tc++){
		string x;
		cin>>x;
		int m=x.size();
		x+=x;
		x=" "+x;
		int p=1,l=0,ans=0;
		for (int i=1; i<=2*m; i++){
			int c=x[i]-'a';
			if (t[p].ch[c]){
				l++;
				p=t[p].ch[c];
			}
			else{
				while (p && !t[p].ch[c]){
					p=t[p].fa;
				}
				if (p==0){
					p=1,l=0;
				}
				else{
					l=t[p].len+1;
					p=t[p].ch[c];
				}
			}
			if (i>=m && l>=m){
				while (t[t[p].fa].len>=m){
					p=t[p].fa;
				}
				if (vis[p]<tc){
					ans+=dp[p];
					vis[p]=tc;
				}
				l=m;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

**CF235C sol**

考虑对于循环重构串直接暴力建出来，然后在 SAM 上面匹配即可。

一个加快询问的方法是，我们知道对于单一串的匹配在 SAM 上是可以做到线性的（势能取决于串长），所以对于构成滑动区间的字符串，如果挪动了首字符其在 SAM 上的表现形式为在 parent tree 上是否要挪到父亲去。

写双指针，显然在 parent tree 上和 SAM 上的走势能都是串长相关的。对于同构的串由于同长所以在 SAM 上是不会存在于同一节点上的，所以一个节点如果加了之后可以暂时把当前节点的贡献去掉方便去重。

时间复杂度为 $O(|S| + \sum |Q|)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Len = 1e6 + 5;
#define ll long long
int n,m;
char s[Len],ss[Len],sss[Len];
struct node
{
    int ch[26],len,fa;
    node(){memset(ch , 0 , sizeof ch);len = fa = 0;}
};
struct Node
{
    int next,to;
};
struct Suf
{
    node t[Len << 1];int tot;int sz[Len << 1];
    Node edge[Len << 2];int head[Len << 1],cnt;
    inline void add(int from,int to)
    {
        edge[++ cnt].to = to;
        edge[cnt].next = head[from];
        head[from] = cnt;
    }
    Suf(){tot = 1;}
    inline int ins(int c,int lst)
    {
        if(t[lst].ch[c])
		{
			int p = lst , q = t[lst].ch[c];
			if(t[q].len == t[p].len + 1) return q;
			else
			{
				int nq = ++ tot;t[nq] = t[q];
				t[nq].len = t[p].len + 1;
				t[q].fa = nq;
				for( ; p && t[p].ch[c] == q ; p = t[p].fa) t[p].ch[c] = nq;
				return nq;
			}
		}
		int p = lst;
		int np = lst = ++ tot;t[np].len = t[p].len + 1;
		for( ; p && !t[p].ch[c] ; p = t[p].fa) t[p].ch[c] = np;
		if(!p) t[np].fa = 1;
		else
		{
			int q = t[p].ch[c];
			if(t[q].len == t[p].len + 1) t[np].fa = q;
			else
			{
				int nq = ++ tot;t[nq] = t[q];
				t[nq].len = t[p].len + 1;
				t[np].fa = t[q].fa = nq;
				for( ; p && t[p].ch[c] == q ; p = t[p].fa) t[p].ch[c] = nq;
			}	
		}
		return np;
	}
    inline int down(int x,int c){return t[x].ch[c];}
    inline void bt(){for(int i = 2 ; i <= tot ; i ++) add(t[i].fa , i);}
    void dfs(int x,int f)
    {
        for(int e = head[x] ; e ; e = edge[e].next)
        {
            int to = edge[e].to;
            if(to == f) continue;
            dfs(to , x);
            sz[x] += sz[to];
        }
        //printf("%d %d %d %d\n",x,f,sz[x],t[x].len);
    }
}At;
#define mk(x , y) make_pair(x , y)
int fg[Len << 1];vector<int> Ps;
int main()
{
    //freopen("F.in","r",stdin);
    scanf("%s",s + 1);n = strlen(s + 1);int lst = 1;
    for(int i = 1 ; i <= n ; i ++){lst = At.ins(s[i] - 'a' , lst);At.sz[lst] ++;}
    At.bt() , At.dfs(1 , 0);
    scanf("%d",&m);
    while(m --)
    {
        //printf("#%d\n",i);
        scanf("%s",sss + 1);const int len = strlen(sss + 1);
        for(int j = 1 ; j <= len ; j ++) ss[j] = sss[j];
        for(int j = len + 1 ; j <= (len << 1) ; j ++) ss[j] = sss[j - len];
        int now = 1 , l = 1 , r = 0;ll asss = 0;
        while(r < (len << 1))
        {
            if(r <= (len << 1) && r - l + 1 == len && !fg[now]) 
            {
                asss += At.sz[now];
                fg[now] = 1;
                Ps.push_back(now);
            }
            while(r - l + 1 < len && r + 1 < (len << 1)) 
            {
                int to = At.down(now , ss[r + 1] - 'a');
                if(!to) break;
                now = to;
                r ++;
            }
            if(r <= (len << 1) && r - l + 1 == len && !fg[now]) 
            {
                asss += At.sz[now];
                fg[now] = 1;
                Ps.push_back(now);
            }
            while((r - l + 1 >= len || !At.down(now , ss[r + 1] - 'a')))
            {
                if(r >= (len << 1)) break;
                l ++;r = max(r , l - 1);
                if(At.t[now].fa && r - l + 1 <= At.t[At.t[now].fa].len) now = At.t[now].fa;
            }
            if(r != (len << 1)) now = At.down(now , ss[r + 1] - 'a');
            r ++;
            if(r <= (len << 1) && r - l + 1 == len && !fg[now]) 
            {
                asss += At.sz[now];
                fg[now] = 1;
                Ps.push_back(now);
            }
        }
        printf("%lld\n",asss);
        for(int j = 1 ; j <= (len << 1) ; j ++) ss[j] = 0;
        for(int j = 0 ; j < Ps.size() ; j ++) fg[Ps[j]] = 0;
        Ps.clear();
    }
    return 0;
}
```

---

## 作者：KAMIYA_KINA (赞：1)

## Tag

后缀自动机，字符串。

## Description

给定一个主串 $S$ 和 $n$ 个询问串 $T$，求每个询问串的所有循环同构在主串中出现的次数总和。

$\texttt{data range:} n\leq 10^5, |S| \leq 10^6, \sum |T| \leq 10^6$.

## Solution

循环同构可以将字符串复制一遍放在后面，然后询问每一个长度为 $|T|$ 的子串在 $S$ 中出现的次数就可以了，注意两个相同的只能算一个，比如 `aaaaa` 这样一个串只能算一个。

然后思考怎么做询问出现次数这个操作。

显然我们可以对主串建立一个 SAM，处理出每一个节点的 $sz$，然后在这个 SAM 上面直接匹配就可以了，不难发现一个子串只会在一个节点里面出现，如果在这个节点计算了一次答案，那就把这个节点打个标记就可以了。

时间复杂度 $O(n)$.

## Code

```cpp
using ll = long long;

const int N = 2e6 + 10;

namespace SAM {

    int lst = 1, tot = 1;
    int ch[N][26], fa[N], len[N], sz[N];
    int vis[N];

    inline void cpy(int x, int y) {
        FOR(i, 0, 25) ch[x][i] = ch[y][i];
    }

    inline void ins(int x) {
        int p(lst), np, q, nq;
        len[np = lst = ++tot] = len[p] + 1, sz[np] = 1;
        while(p && !ch[p][x]) ch[p][x] = np, p = fa[p];
        if (!p) return void (fa[np] = 1);
        if (len[q = ch[p][x]] == len[p] + 1) return void (fa[np] = q);
        cpy(nq = ++tot, q), fa[nq] = fa[q];
        len[nq] = len[p] + 1, fa[np] = fa[q] = nq;
        while (p && ch[p][x] == q) ch[p][x] = nq, p = fa[p];
        return ;
    }

    int top;
    int stk[N], d[N];
    inline void init() {
        top = 0;
        FOR(i, 2, tot) d[fa[i]]++;
        FOR(i, 1, tot) if (!d[i]) stk[++top] = i;
        while (int u = stk[top--]) {
            sz[fa[u]] += sz[u];
            if (!--d[fa[u]]) stk[++top] = fa[u];
        }
        return ;
    }

    inline ll solve(char *s, int tim) {
        int n = strlen(s + 1), slen = 0, p = 1;
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            int v = s[i] - 'a';
            while (p > 1 && !ch[p][v]) p = fa[p], slen = len[p];
            if (ch[p][v]) p = ch[p][v], slen++;
        }
        for (int i = 1; i <= n; i++) {
            if (slen == n) {
                if (vis[p] != tim) ans += sz[p];
                vis[p] = tim, slen--;
                if (slen == len[fa[p]]) p = fa[p];
            }
            int v = s[i] - 'a';
            while (p > 1 && !ch[p][v]) p = fa[p], slen = len[p];
            if (ch[p][v]) p = ch[p][v], slen++;
        }
        return ans;
    }
}

char s[N];

inline void solve() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) SAM::ins(s[i] - 'a');
    SAM::init();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        cout << SAM::solve(s, i) << '\n';
    }
    return ;
}
```



---

## 作者：Infiltrator (赞：1)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](http://codeforces.com/problemset/problem/235/C)

------------

# Solution

考虑循环同构的性质，每次相当于从最前面删去一个字符，从最后面加上一个字符。在$SAM$里对应着往上跳$fa$或不跳和走对应的字符串转移边。

考虑对于长度为$l$的串，最多删$l$次，最多加$l$次，所以直接在$SAM$上暴力删除添加字符的复杂度就是$O(l)$的。

那么先把字符串在后面将自己复制一遍，然后丢到$SAM$上跑，如果没有对应的转移边就不停地跳$fa$，直到第一个满足是字符串的循环同构串的节点。那么这时考虑删除最前面的字符，就有两种情况，一种是$len_{fa_{now}} + 1 =$原字符串串长，也就是说，删去最前面的一个字符后，要往上跳$fa$；另一种是$len_{fa_{now}} + 1 < $当前匹配长度，这就说明删除一个字符后的$endpos$集合没有改变，直接转移下一个边就行。

然后因为要求本质不同，所以打上时间戳标记，确保每种子串只被算一次贡献即可。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1000000;

int l, fa[N * 2 + 50], son[N * 2 + 50][26], len[N * 2 + 50], vis[N * 2 + 50], siz[N * 2 + 50], num, head[N * 2 + 50], last = 1, cnt = 1;

char st[N * 2 + 50];

struct Node
{
	int next, to;
} edge[N * 2 + 50];

void Addedge(int u, int v)
{
	edge[++num] = (Node){head[u], v};
	head[u] = num;
	return;
} 

void Insert(int c)
{
	int p = last, ne = last = ++cnt;
	len[ne] = len[p] + 1; siz[ne] = 1; 
	while (!son[p][c] && p) son[p][c] = ne, p = fa[p];
	if (!p) { fa[ne] = 1; return; }
	int q = son[p][c];
	if (len[q] == len[p] + 1) { fa[ne] = q; return; }
	int sp = ++cnt;
	for (int i = 0; i < 26; i++) son[sp][i] = son[q][i];
	len[sp] = len[p] + 1;
	fa[sp] = fa[q];
	fa[q] = fa[ne] = sp;
	while (p && son[p][c] == q) son[p][c] = sp, p = fa[p];
	return;
}

void Dfs(int x)
{
//	cout << x << " len:" << len[x] << " " << endl;
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		Dfs(v);
		siz[x] += siz[v];
	}
//	cout << x << " " << siz[x] << endl;
	return;
}

int main()
{
	scanf("%s", st + 1);
	l = strlen(st + 1);
	for (int i = 1; i <= l; i++) Insert(st[i] - 'a');
//	cout << cnt << endl;
	for (int i = 2; i <= cnt; i++) Addedge(fa[i], i);
	Dfs(1);
	int t;
	//for (int i = 1; i <= cnt; i++) printf("%d ", siz[i]); puts("");
	scanf("%d", &t);
	for (int i = 1; i <= cnt; i++) vis[i] = t;
	while (t--)
	{
		int ans = 0; 
		scanf("%s", st + 1);
		int now = 1, length = 0;
		l = strlen(st + 1);
		int yl = l;
		for (int i = yl + 1; i <= yl * 2 - 1; i++) st[i] = st[i - yl];
		l = 2 * l - 1;
		for (int i = 1; i <= l; i++)
		{
			int c = st[i] - 'a';
		//	cout << st[i] << " " << length << " " << now << endl;
			while (!son[now][c] && now) now = fa[now], length = len[now];
			if (son[now][c]) length++, now = son[now][c]; else now = 1, length = 0;
			if (length == yl) 
			{
				if (vis[now] > t) ans += siz[now], vis[now] = t;
				if (len[fa[now]] + 1 == yl) now = fa[now];
				length--;
			} 
		//	cout << now << endl;
		}
		printf("%d\n", ans);
	}
	return 0;
} 
```

---

## 作者：linjingxiang (赞：0)

# Description

[题目来源-洛谷](https://www.luogu.com.cn/problem/CF235C)

[题目来源-CF](https://codeforces.com/problemset/problem/235/C)

定义文本串 $S'$ 和 匹配串 $x_i$ 同构：$x_i$ 经过循环移位（可以不移）与 $S'$ 相同。

给定一个 $S$ 和许多 $x_i$，询问对于每一个 $x_i$ 有多少个 $S$ 的子串 $S'$ 与 $x_i$ 同构。

# Solution

先对 $S$ 构建[后缀自动机](https://oi-wiki.org/string/sam/)。

首先，题目中的问题可以转化为：设 $l_i=len(x_i)$，将 $x_i$ 自我复制一份后，有多少个 $S$ 与 $x_i$ 之间的长为 $l_i$ 的公共子串。

接下来使用一个 SAM 上很重要的技巧：把 SAM 当作 AC 自动机一样进行字符串匹配。

匹配方法：对于当前已经匹配到的状态，如果有转移边，就直接转移并将当前匹配长度 $+1$，否则一直跳 link  指针，并修改当前匹配长度为当前状态的 len。

于是直接匹配就好，注意同一个节点的贡献只能算一次，打个标记就好。

时间复杂度 $O(\left| S \right| + \sum \left| x_i \right|)$。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define F(i,j,k) for(int i=j;i<=k;i++)
using namespace std;
struct state{int to[26],link,cnt,len;}st[N<<1];
int sz,lst,n;
long long ans;
string s,x;
inline void insert(int c){
	int cur=++sz,p=lst;
	st[cur].len=st[lst].len+1,st[cur].cnt=1,lst=cur;
	while(p!=-1&&!st[p].to[c])st[p].to[c]=cur,p=st[p].link;
	if(p==-1)return;
	int q=st[p].to[c];
	if(st[p].len+1==st[q].len)return st[cur].link=q,void();
	int clone=++sz;
	st[clone]=st[q],st[clone].len=st[p].len+1,st[clone].cnt=0;
	while(p!=-1&&st[p].to[c]==q)st[p].to[c]=clone,p=st[p].link;
	st[cur].link=st[q].link=clone;
}
vector<int>t[N<<1];
inline void dfs(int u){for(int v:t[u])dfs(v),st[u].cnt+=st[v].cnt;}
int stk[N<<1],tt;
bool vis[N<<1];
int main(){
	st[0].link=-1;
	cin>>s>>n;
	F(i,0,(int)s.length()-1)insert(s[i]-'a');
	F(i,1,sz)t[st[i].link].push_back(i);
	dfs(0);
	while(n--){
		cin>>x;
		ans=0;
		int u=0;
		tt=0;
		int len=0,L=x.length();
		F(i,0,(int)x.length()-1){
			int c=x[i]-'a';
			while(u&&!st[u].to[c])u=st[u].link,len=st[u].len;
			if(st[u].to[c])len++,u=st[u].to[c];
		}
		F(i,0,(int)x.length()-1){
			int c=x[i]-'a';
			while(u&&!st[u].to[c])u=st[u].link,len=st[u].len;
			if(st[u].to[c])len++,u=st[u].to[c];
			if(len>L){
				len--;
				if(len==st[st[u].link].len)u=st[u].link;
			}
			if(len==L)stk[++tt]=u,vis[u]=1;
		}
		F(i,1,tt)if(vis[stk[i]])vis[stk[i]]=0,ans+=st[stk[i]].cnt;//,cout<<stk[i]<<' '<<st[stk[i]].cnt<<' '<<st[stk[i]].len<<'\n';;
		cout<<ans<<'\n';
	}
}
```

---

## 作者：liujiaxi123456 (赞：0)

题不难，简单补充一下大部分题解未提到的势能分析。

处理循环问题，显然考虑倍长后做类似双指针的东西。

相当于在 SAM 上做匹配，假设现在匹配到了：$t[i-len+1, i] $，状态为 $t$。

- 若 $len > |t| $ 则尝试 $fail_t$，相当于把左端点删掉。

- 否则统计答案，记得打标记以去重。

- 若 $son_{t, c}$ 为空，则一直跳 $fail$ 直到有。

P.S. 由于跳一次 $fail$，必然让 $len-1$，所以有势能。

---

## 作者：JimmyLee (赞：0)

# 题意

> 给定一个主串 $S$ 和 $n$ 个询问串，求每个询问串的所有循环同构在主串中出现的次数总和。

# 分析

后缀自动机好题。

循环同构的过程可以看作从该串的头部删除一个字符，并在尾部加入一个字符。

在后缀自动机上，跳 parent 树的过程就相当于删除头部的若干个字符。

所以我们可以套路地把询问串 $s_i$ 复制一遍首尾相接，然后模拟 SAM 匹配子串的过程，有以下两种情况：

- 如果无法继续匹配，那么跳 parent 树直至可以匹配并更新长度。
- 如果长度 $l$ 大于该询问串的长度，删除首字母并更新当前长度，同时跳 parent 树找到当前节点。

另外一个问题是循环同构可能产生相同的子串，比如 $\texttt{abab}$ 将前两位拼到最后得到的字符串也是 $\texttt{abab}$。

此时就要在节点上存储一个标记，判断该子串有没有被访问过。

也可以使用哈希等方法求出最小循环节再处理。

时间复杂度 $O(|S|+\sum|s_i|)$。

[AC 记录](https://codeforces.com/contest/235/submission/278029456)

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000006

namespace SAM
{
    struct node
    {
        int fa, len, ch[26];
        node() {memset(this, 0, sizeof *this);}
    }st[maxn<<1];

    int siz[maxn<<1];

    int la=1, cnt=1;

    void insert(int c)
    {
        int p=la, u=la=++cnt;
        siz[u]=1;
        st[u].len=st[p].len+1;
        for(;p&&!st[p].ch[c];p=st[p].fa)
            st[p].ch[c]=u;
        if(!p) return st[u].fa=1, void();
        int q=st[p].ch[c];
        if(st[q].len==st[p].len+1) 
            return st[u].fa=q, void();
        int v=++cnt;
        st[v]=st[q];
        st[v].len=st[p].len+1;
        st[q].fa=st[u].fa=v;
        for(;p&&st[p].ch[c]==q;p=st[p].fa)
            st[p].ch[c]=v;
    }

    vector<int> e[maxn<<1];

    void build_tree()
    {
        for(int i=2;i<=cnt;i++)
            e[st[i].fa].emplace_back(i);
    }

    void dfs(int u)
    {
        for(auto v:e[u])
            dfs(v), siz[u]+=siz[v];
    }

    bitset<maxn<<1> vis;

    int query(string &s)
    {
        vis.reset();
        int p=1, l=0, ret=0;
        int n=s.size();
        for(int i=1;i<=2;i++) for(auto c:s)
        {
            while(p&&!st[p].ch[c-'a']) l=st[p=st[p].fa].len;
            if(st[p].ch[c-'a']) p=st[p].ch[c-'a'], l++;
            while(l>n) l--, p=(l==st[st[p].fa].len)?st[p].fa:p; 
            if(l==n&&!vis[p]) ret+=siz[p], vis[p]=1;
        }
        return ret;
    }

    void insert(string &s)
    {
        for(auto c:s) insert(c-'a');
    }
}

string s;

int main()
{
    cin>>s;
    SAM::insert(s);
    SAM::build_tree();
    SAM::dfs(1);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) 
        cin>>s, cout<<SAM::query(s)<<'\n';
}#include<bits/stdc++.h>
using namespace std;
#define maxn 1000006

namespace SAM
{
    struct node
    {
        int fa, len, ch[26];
        node() {memset(this, 0, sizeof *this);}
    }st[maxn<<1];

    int siz[maxn<<1];

    int la=1, cnt=1;

    void insert(int c)
    {
        int p=la, u=la=++cnt;
        siz[u]=1;
        st[u].len=st[p].len+1;
        for(;p&&!st[p].ch[c];p=st[p].fa)
            st[p].ch[c]=u;
        if(!p) return st[u].fa=1, void();
        int q=st[p].ch[c];
        if(st[q].len==st[p].len+1) 
            return st[u].fa=q, void();
        int v=++cnt;
        st[v]=st[q];
        st[v].len=st[p].len+1;
        st[q].fa=st[u].fa=v;
        for(;p&&st[p].ch[c]==q;p=st[p].fa)
            st[p].ch[c]=v;
    }

    vector<int> e[maxn<<1];

    void build_tree()
    {
        for(int i=2;i<=cnt;i++)
            e[st[i].fa].emplace_back(i);
    }

    void dfs(int u)
    {
        for(auto v:e[u])
            dfs(v), siz[u]+=siz[v];
    }

    bitset<maxn<<1> vis;

    int query(string &s)
    {
        vis.reset();
        int p=1, l=0, ret=0;
        int n=s.size();
        for(int i=1;i<=2;i++) for(auto c:s)
        {
            while(p&&!st[p].ch[c-'a']) l=st[p=st[p].fa].len;
            if(st[p].ch[c-'a']) p=st[p].ch[c-'a'], l++;
            while(l>n) l--, p=(l==st[st[p].fa].len)?st[p].fa:p; 
            if(l==n&&!vis[p]) ret+=siz[p], vis[p]=1;
        }
        return ret;
    }

    void insert(string &s)
    {
        for(auto c:s) insert(c-'a');
    }
}

string s;

int main()
{
    cin>>s;
    SAM::insert(s);
    SAM::build_tree();
    SAM::dfs(1);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) 
        cin>>s, cout<<SAM::query(s)<<'\n';
}
```

---

## 作者：WrongAnswer_90 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/18007071)

[CF235C Cyclical Quest](https://www.luogu.com.cn/problem/CF235C)

SAM 做法：

对于主串建 SAM，然后 parent tree 上 DP 出 $f_i$ 表示节点 $i$ 后缀等价类的出现次数。询问先用 KMP 求最小循环元 $m$，然后接下来需要把 $[1,n],[2,n]\dots[m-1,n+m-1]$ 扔进 SAM 里跑。

暴力显然过不去，但是跑完一次可以删去最开始的字符然后继续跑。删去开头字符等价于在 parent tree 上向上跳，即当 $len_{fa_now}\geq n$ 时 $now\rightarrow fa_{now}$。同时跑不动的时候也向上跳，并把当前的 $len$ 设为 $len_{fa}$。

总复杂度线性。

后缀数组做法：

离线，把主串和询问串加循环元拼在一起，对于每个不是主串的后缀前后二分找到满足 LCP 长度为 $n$ 的区间然后前缀和相见即可。

好像比 SAM 简单一些，但是复杂度带一只 $\log$。

提供 SAM 代码：

```cpp
	int n,TT,m,now,r,ans,nex[1000010],f[2000010];
	char x[2000010],s[1000010];
	vector<int> T[2000010];
	namespace SAM
	{
		int last=1,cnt=1;
		struct{int ch[26],fa,len;}t[2000010];
		inline int add(int x)
		{
			int np=++cnt,p=last,q,nq;t[last=np].len=t[p].len+1,f[np]=1;
			while(p&&!t[p].ch[x])t[p].ch[x]=np,p=t[p].fa;
			if(!p)return t[np].fa=1,np;
			if(t[q=t[p].ch[x]].len==t[p].len+1)return t[np].fa=q,np;
			t[nq=++cnt]=t[q],t[nq].len=t[p].len+1,t[np].fa=t[q].fa=nq;
			while(p&&t[p].ch[x]==q)t[p].ch[x]=nq,p=t[p].fa;
			return np;
		}
	}
	using namespace SAM;
	void dfs(int x){for(auto to:T[x])dfs(to),f[x]+=f[to];}
	inline void mian()
	{
		read(s,TT),n=strlen(s+1);
		for(int i=1;i<=n;++i)add(s[i]-'a');
		for(int i=2;i<=cnt;++i)T[t[i].fa].eb(i);
		dfs(1);
		while(TT--)
		{
			read(x),n=strlen(x+1);
			for(int i=1;i<=n;++i)x[n+i]=x[i];
			for(int j=0,i=2;i<=n;nex[i++]=j)
			{
				while(j&&x[j+1]!=x[i])j=nex[j];
				if(x[j+1]==x[i])++j;
			}
			if(n%(n-nex[n])==0)m=n-nex[n];else m=n;
			now=1,r=0,ans=0;
			for(int i=n,r=0,len=0;now&&i<n+m;++i)
			{
				while(r<i)
				{
					++r;
					while(now&&!t[now].ch[x[r]-'a'])now=t[now].fa,len=t[now].len;
					now=t[now].ch[x[r]-'a'],++len;
				}
				while(t[t[now].fa].len>=n)now=t[now].fa;
				if(len>=n)ans+=f[now];
			}
			write(ans,'\n');
		}
	}
```

---

## 作者：5k_sync_closer (赞：0)

对主串建 SAM。

对于一次询问，考虑枚举询问串的所有循环同构，

问题变为维护串 $u$（初始为询问串），每次从 $u$ 开头删去一个字符，在 $u$ 结尾加入这个字符，然后求 $u$ 在主串中的出现次数，

类似 LCS 地，维护 $u$ 在主串中出现过的最长后缀长度 $z$ 及其对应节点 $p$，考虑修改 $u$ 时如何更新 $z,p$。

首先 $z\ne|u|$ 时从 $u$ 开头删去一个字符对 $z,p$ 无影响，否则 $z$ 应该减一，$p$ 应该变为此时整个 $u$ 对应的节点，

则原来的 $u$ 若为原来的 $p$ 中最短的串，则 $p\gets\text{link}(p)$，否则 $p$ 不变。

在 $u$ 结尾加入字符 $c$ 时，考虑不断缩短原来 $u$ 在主串中出现过的最长后缀，直到其后接上 $c$ 在主串中出现过，

即不断令 $p\gets\text{link}(p)$，直到 $p$ 有 $c$ 孩子，然后将 $p$ 更新为其 $c$ 孩子即可。途中顺便更新 $z$。

每次修改 $u$、更新 $z,p$ 后，若 $z=|u|$，则 $p$ 对应的 $\text{endpos}$ 集合大小就是 $u$ 在主串中的出现次数，否则 $u$ 在主串中的出现次数为 $0$。

发现这样做会重复统计本质相同的循环同构，于是标记 $b_p$ 表示 $p$ 是否对答案产生过贡献，每次更新答案时若 $b_p=1$ 则 $p$ 不再对答案产生贡献。

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
bool b[2000050];
char s[2000050], v[2000050];
int T, n, o, z, e[2000050], d[2000050], l[2000050], f[2000050], c[2000050][26];
long long Q;
queue<int> q, O;
void I(int x)
{
    int u = ++o, p = z;
    l[u] = l[z] + 1;
    while (p != -1 && !c[p][x])
        c[p][x] = u, p = f[p];
    if (p == -1)
        f[u] = 0;
    else
    {
        int q = c[p][x];
        if (l[p] + 1 == l[q])
            f[u] = q;
        else
        {
            int w = ++o;
            l[w] = l[p] + 1;
            f[w] = f[q];
            for (int i = 0; i < 26; ++i)
                c[w][i] = c[q][i];
            while (p != -1 && c[p][x] == q)
                c[p][x] = w, p = f[p];
            f[q] = f[u] = w;
        }
    }
    z = u;
}
int main()
{
    f[0] = -1;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        I(s[i] - 'a');
    for (int i = 1, u = 0; i <= n; ++i)
        e[u = c[u][s[i] - 'a']] = 1;
    for (int i = 1; i <= o; ++i)
        ++d[f[i]];
    for (int i = 1; i <= o; ++i)
        if (!d[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (!u)
            continue;
        e[f[u]] += e[u];
        if (!--d[f[u]])
            q.push(f[u]);
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", v + 1);
        n = strlen(v + 1);
        int z = 0, p = 0;
        Q = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (p && !c[p][v[i] - 'a'])
                p = f[p], z = l[p];
            if (c[p][v[i] - 'a'])
                ++z, p = c[p][v[i] - 'a'];
        }
        if (z == n)
            Q += e[p], b[p] = 1, O.push(p);
        for (int i = 1; i <= n; ++i)
        {
            if (z == n)
            {
                if (n == l[f[p]] + 1)
                    p = f[p];
                --z;
            }
            while (p && !c[p][v[i] - 'a'])
                p = f[p], z = l[p];
            if (c[p][v[i] - 'a'])
                ++z, p = c[p][v[i] - 'a'];
            if (z == n && !b[p])
                Q += e[p], b[p] = 1, O.push(p);
        }
        printf("%lld\n", Q);
        while (!O.empty())
            b[O.front()] = 0, O.pop();
    }
    return 0;
}
```


---

## 作者：SoyTony (赞：0)

对模式串建 $\text{SAM}$。

循环同构类型的题目，多数可以“断环成链”即复制一次解决。

维护左右指针 $lpos,rpos $ 以及当前状态 $u$，当枚举 $lpos\in [1,n]$ 时更新 $rpos$ 与 $u$ 并在 $rpos-lpos+1=n$ 时更新答案，这个答案为预处理出的 $\operatorname{endpos}$ 集合大小，也即出现次数。

考虑匹配时有以下几种情况：

- 失配，以当前枚举到的左指针不可能存在答案。
- 继续匹配，且区间长度小于 $n$。
- 匹配结束，区间长度等于 $n$。

匹配结束自然可以更新当前状态的答案，并打上标记（样例 $2$ 中相同循环同构只计算一次），而失配则直接进行下一次枚举。

关键处理就是继续匹配的状态移动以及左指针右移的状态移动。

对于继续匹配（也即右指针右移），实际上就是在 $\text{SAM}$ 上转移，转移到 $ch(u,c)$。

而左端点右移有两种情况，每个节点表示的等价类集合中子串长度有：$[\operatorname{len}(\operatorname{link}(u))+1,\operatorname{len}(u)]$，若删去首字母后长度仍在这个区间内则状态不变，反之移动到 $\operatorname{link}(u)$ 即可。

复杂度 $O(|S|+\sum|T|)$。

```cpp
int n,m;
char s[maxn];

struct SuffixAutomaton{
    int tot,last;
    int len[maxn],link[maxn],cnt[maxn];
    int ch[maxn][26];
    int mark[maxn];
    inline void init(){
        tot=0,last=0;
        len[0]=0,link[0]=-1,cnt[0]=0;
    }
    inline void extend(int c){
        int cur=++tot;
        len[cur]=len[last]+1,cnt[cur]=1;
        int p=last;
        while(p!=-1&&!ch[p][c]){
            ch[p][c]=cur;
            p=link[p];
        }
        if(p==-1) link[cur]=0;
        else{
            int q=ch[p][c];
            if(len[p]+1==len[q]) link[cur]=q;
            else{
                int clone=++tot;
                len[clone]=len[p]+1,link[clone]=link[q];
                for(int k=0;k<26;++k) ch[clone][k]=ch[q][k];
                while(p!=-1&&ch[p][c]==q){
                    ch[p][c]=clone;
                    p=link[p];
                }
                link[cur]=link[q]=clone;
            }
        }
        last=cur;
    }
    vector<int> E[maxn];
    inline void build(){
        for(int i=1;i<=tot;++i){
            E[link[i]].push_back(i);
        }
    }
    void dfs(int u){
        for(int v:E[u]){
            dfs(v);
            cnt[u]+=cnt[v];
        }
    }
    inline int solve(int id){
        for(int i=1;i<=n;++i){
            if(!ch[0][s[i]-'a']) return 0;
        }
        int u=ch[0][s[1]-'a'],lpos=1,rpos=1,ans=0;
        for(lpos=1;lpos<=n;++lpos){
            while(rpos-lpos+1<n){
                if(ch[u][s[rpos+1]-'a']){
                    u=ch[u][s[rpos+1]-'a'],++rpos;
                }
                else break;
            }
            if(rpos-lpos+1==n){
                if(mark[u]<id) ans+=cnt[u];
                mark[u]=id;
            }
            if(len[link[u]]==rpos-(lpos+1)+1) u=link[u];
        }
        return ans;
    }
}SAM;

int main(){
    scanf("%s",s+1);
    n=strlen(s+1),m=read();
    SAM.init();
    for(int i=1;i<=n;++i) SAM.extend(s[i]-'a');
    SAM.build();
    SAM.dfs(0);
    for(int k=1;k<=m;++k){
        scanf("%s",s+1);
        n=strlen(s+1);
        for(int i=1;i<=n;++i) s[i+n]=s[i];
        printf("%d\n",SAM.solve(k));
    }
    return 0;
}
``

---

## 作者：wcyQwQ (赞：0)

SA 被卡掉了，怄火。

对主串建立 SAM，然后把每一个模式串丢到 SAM 上去匹配。

考虑怎么去匹配循环同构串，观察到每一个循环同构串本质上就是把当前字符串删去第一个字符加到最后，而我们惊喜地发现 SAM 是支持删除第一个字符的，因为当前节点 $p$ 存的是一段连续的后缀，如果我们把第一个字符删去后 $p$ 匹配不了，根据后缀链接的定义，这时我们会跳到 $fa_p$，然后继续匹配就可以了，注意去重，可以通过 kmp 处理出循环节，或是通过在 SAM 上打标记处理。

[Code](https://codeforces.com/contest/235/submission/236062748)

---

## 作者：BlankAo (赞：0)

**广义后缀树** 题解。对 $S$ 建立 广义后缀树。

设询问的串长度为 $m$。把字符串复制一倍，那么就相当于每次都查询 $[i,i+m-1]$ 这一段询问串在主串 $S$ 中出现多少次。那么就相当于每次插入后一个字符，删除最前面的字符，查询对应后缀树节点的子树上有多少个叶子节点（就是有多少个后缀的前缀是当前询问串）。插入就是 $len+1$，删除就是跳后缀链接。

注意走边、跳后缀链接可能会执行不止一次。

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define mar(o) rep(i,1,27)
#define v dot[o].son[i]
#define sn dot[nowz].son[ cz[i-len+1] ]
#define lon long long
using namespace std;
const int l7=1012345,inf=1e8;
struct beer{int sta,len,fail;bool islaf;int son[29];}dot[l7*2];
struct dino{int id,len;}b[l7];
int n,m,T,now,las,cnt,rem,cr[l7],cz[l7*2],siz[l7*2];

int rd(){
	int shu=0;bool fu=0;char ch=getchar();
	while( !isdigit(ch) ){if(ch=='-')fu=1;ch=getchar();}
	while( isdigit(ch) )shu=(shu<<1)+(shu<<3)+ch-'0',ch=getchar();
	return fu?-shu:shu;
}

int rdstr(int *a,bool sys){
	char ch=getchar();int len=0;
	while( !isalpha(ch) )ch=getchar();
	while( isalpha(ch) ){
		len++,a[len]=ch-'a'+1,ch=getchar();
	}
	if(sys)len++,a[len]=27;
	return len;
}

void sesmet(){
	cnt=1,now=1,dot[0].len=inf;
}

int Dnew(int sta,int len){
	cnt++,dot[cnt]=(beer){sta,len,1,(len==inf)};
	return cnt;
}

void isert(int id){
	rem++,las=1;
	while(rem){
		while(rem>dot[ dot[now].son[ cr[id-rem+1] ] ].len){
			now=dot[now].son[ cr[id-rem+1] ];
			rem-=dot[now].len;
		}
		int &z=dot[now].son[ cr[id-rem+1] ];
		int ch=cr[ dot[z].sta+rem-1 ];
		if(!z||ch==cr[id]){
			dot[las].fail=now,las=now;
			if(!z)z=Dnew(id,inf);
			else return;
		}
		else{
			int fut=Dnew(dot[z].sta,rem-1);
			dot[fut].son[ch]=z;
			dot[fut].son[ cr[id] ]=Dnew(id,inf);
			dot[z].sta+=rem-1,dot[z].len-=rem-1;
			z=fut,dot[las].fail=fut,las=fut;
		}
		if(now==1)rem--;
		else now=dot[now].fail;
	}
}

int dfs(int o){
	if(dot[o].islaf){
		siz[o]=!(o==cnt);return siz[o];
	}
	mar(o){
		if(v)siz[o]+=dfs(v);
	}
	return siz[o];
}

bool cmp(dino p,dino q){
	return p.id==q.id?p.len<q.len:p.id<q.id;
}

lon work(){
	int nowz=1,len=0,poi=1,cntz=0;
	lon ans=0;
	rep(i,1,m+m-1){
		len++;
		while(poi<=i){
			while(len>dot[sn].len){
				nowz=sn,len-=dot[nowz].len;
			}
			if(!sn||cr[dot[sn].sta+len-1]^cz[i]){
				if(nowz==1)len--;
				poi++,nowz=dot[nowz].fail;
				continue;
			}
			if(i-poi+1>=m){
				cntz++,b[cntz]=(dino){sn,len};
				if(nowz==1)len--;
				poi++,nowz=dot[nowz].fail;
			}
			break;			
		}
	}
	sort(b+1,b+cntz+1,cmp);
	rep(i,1,cntz){
		if(b[i].id^b[i-1].id||b[i].len^b[i-1].len)ans+=siz[ b[i].id ];
	}
	return ans;
}

int main(){
	sesmet();
	n=rdstr(cr,1),T=rd();
	rep(i,1,n)isert(i);
	dot[1].fail=1;
	dfs(1);
	while(T--){
		m=rdstr(cz,0);
		rep(i,1,m)cz[i+m]=cz[i];
		printf("%lld\n", work() );
	}
	return 0;
}
```

---

## 作者：asuldb (赞：0)

厚颜无耻的发一篇可能是全网最劣解法

我们发现要求给定的串所有不同的循环同构出现的次数，可以直接暴力啊

因为一个长度为$n$的串，不同的循环同构次数显然是不会超过$n$的，所以我们可以直接对每一个循环通过分别求一下其出现次数

求其出现次数当然可以交给$SAM$来搞了

于是我们把所有的串都插入$SAM$里去，但是我们只计算$S$串产生的贡献，对于每一个$T$串我们要将其倍长之后再插入，这样我们就可以在$parent$树上直接树上倍增求出一个循环同构出现次数了

同时为了去重，我们每次跳出来一个循环同构之后给它打上标记，之后就不要再跳了

这样的做法当让是喜提$MLE$

于是我们甚至可以直接那$map$来存边，之后不用树上倍增直接暴力往上跳，于是就能以全luogu最慢的好成绩通过这道题

代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
#include<vector>
#define maxn 6000005
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
std::map<int,int> son[maxn];
struct E{int v,nxt;}e[maxn];
int n,lst=1,cnt=1,num,m;
int len[maxn],head[maxn],sz[maxn],deep[maxn],vis[maxn],fa[maxn];
inline void add(int x,int y) {e[++num].v=y;e[num].nxt=head[x];head[x]=num;}
void dfs(int x) {for(re int i=head[x];i;i=e[i].nxt) deep[e[i].v]=deep[x]+1,dfs(e[i].v),sz[x]+=sz[e[i].v];}
int st[1000005],top;
std::vector<int> a[100005];
int L[100005];
char S[1000005];
inline void ins(int c,int o,int t)
{
	int f=lst,p=++cnt; lst=p;
	len[p]=len[f]+1; if(!o) sz[p]=1;
	if(o&&t) a[o].push_back(p);
	while(f&&!son[f][c]) son[f][c]=p,f=fa[f];
	if(!f) {fa[p]=1;return;}
	int x=son[f][c];
	if(len[f]+1==len[x]) {fa[p]=x;return;}
	int y=++cnt;
	len[y]=len[f]+1,fa[y]=fa[x],fa[x]=fa[p]=y;
	for(std::map<int,int>::iterator it=son[x].begin();it!=son[x].end();it++) son[y].insert(*it);
	while(f&&son[f][c]==x) son[f][c]=y,f=fa[f];
}
inline int find(int x,int li) {while(len[fa[x]]>=li) x=fa[x];return x;} 
int main()
{
	scanf("%s",S+1),n=strlen(S+1);scanf("%d",&m);
	for(re int i=1;i<=n;i++) ins(S[i]-'a',0,0);
	for(re int i=1;i<=m;i++)
	{
		scanf("%s",S+1);L[i]=strlen(S+1);lst=1;
		for(re int j=1;j<L[i];j++) ins(S[j]-'a',i,0);ins(S[L[i]]-'a',i,1);
		for(re int j=1;j<L[i];j++) ins(S[j]-'a',i,1);
	}
	for(re int i=2;i<=cnt;i++) add(fa[i],i);deep[1]=1;dfs(1);
	for(re int i=1;i<=m;i++)
	{
		int ans=0;top=0;
		for(re int j=0;j<a[i].size();j++)
		{
			int t=find(a[i][j],L[i]);
			if(vis[t]) continue;
			st[++top]=t;ans+=sz[t];vis[t]=1;
		}
		printf("%d\n",ans);
		for(re int j=1;j<=top;j++) vis[st[j]]=0;
	}
	return 0;
}
```

---

