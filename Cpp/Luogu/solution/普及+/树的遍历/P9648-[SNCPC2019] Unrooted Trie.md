# [SNCPC2019] Unrooted Trie

## 题目描述

### 题目背景

trie 的定义是这样的：

- 一棵大小为 $n$ 的 trie，是一棵有着 $n$ 个节点和 $(n-1)$ 条边的有根树，每一条边上都标有一个字符；

- 在 trie 中，从根结点到树上某一结点的路径代表一个字符串，节点 $x$ 代表的字符串记为 $s(x)$，特别地，根节点代表的字符串为空串。

- 若节点 $u$ 是节点 $v$ 的父节点，且 $c$ 是连接 $u$ 与 $v$ 的边上的字符，则有 $s(v) = s(u) + c$（这里的 $+$ 表示字符串的连接，而非普通的加法运算）。

当每一个节点代表的字符串互不相同时，该 trie 是合法的。


给出一个无根的 trie，求其中有多少节点可作为该 trie 的根，使得该 trie 合法。

## 说明/提示

【样例解释】

对于第一组测试数据，只能选择节点 $1$ 或节点 $2$ 作为根，否则 $s(1)$ 和 $s(2)$ 相同。

对于第二组测试数据，无论如何选择节点作为根，$s(1)$ 和 $s(2)$ 或 $s(5)$ 和 $s(6)$ 相同。


对于每组数据，$1 \le n \le 2 \times 10^5$，$1 \le u_i,v_i \le n$，$c_i$ 都是小写字母。

对于每个测试点，保证给出的图是一棵树，所有的 $n$ 之和不会超过 $10^6$。

## 样例 #1

### 输入

```
2
6
3 1 a
3 2 a
3 4 b
4 5 c
4 6 d
6
3 1 a
3 2 a
3 4 b
5 4 c
6 4 c
```

### 输出

```
2
0
```

# 题解

## 作者：Y_QWQ_Y (赞：6)

NOIP 模拟赛 T1，同学都 dfs 序差分人均了，就我寄了，甚至有人 $\Theta(n^2)$ 艹过去了。

### 解题思路
好了废话不多说，进入主题。~~虽然这句话貌似也是句废话。~~

我们可以发现，对于任意一个点，当它有三条同样字符的边时，是没有满足条件的根的。因为对于其他点，到达该点之后就会不满足题意，当从这三边连接的三点为根时，到达该点也会不满足，综上，当任意一个点有三条同样字符的边时，无解。

类似的，对于有两对相同字符的边时，也无解，证明类似上面，就不赘述了。

那么接下来就是只有一对相同字符的边时，那么合法的根就在这两条边连接的点的子树中。那么就可以把这个问题转化成字数覆盖问题，我们可以对原树 dfs 序进行区间修改，静态修改很容易想到用差分来写。

### 代码部分
那么就可以写出代码，但是记住 $\lceil$ 多测不清空，亲人两行泪 $\rfloor$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, n, h[N], c, l[N], r[N], id[N], num, sum[N], cnt, s;
struct Edge{int v, nxt;}e[N << 1];
vector <int> col[N][30];
void add (int a, int b, char w)
{
	e[++ c] = Edge{b, h[a]};
	h[a] = c;
	col[a][w - 'a'].push_back (c);
}
void dfs (int d, int fa)
{
	l[d] = ++ num;//子树左端点。
	id[num] = d;
	for (int i = h[d]; i; i = e[i].nxt)if (e[i].v != fa)dfs (e[i].v, d);
	r[d] = num;//子树右端点。
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> t;
	while (t --)
	{
		cin >> n;
		cnt = n;
		for (int i = 1; i <= n; ++ i)
		{
			h[i] = sum[i] = 0;//不能用 memset，会超时。
			for (int j = 0; j < 26; ++ j)col[i][j].clear ();
		}
		num = s = c = 0;
		for (int i = 1, a, b; i < n; ++ i)
		{
			char w;
			cin >> a >> b >> w;
			add (a, b, w);
			add (b, a, w);
		}
		dfs (1, 0);
		bool f = 0;
		for (int i = 1; i <= n; ++ i)
		{
			int k = -1;
			for (int j = 0; j < 26; ++ j)
			{
				int len = col[i][j].size ();
				if (! len)continue;
				if (len == 2 && k != -1 || len == 3)//判断无解。
				{
					f = 1;
					break;
				}
				if (k == -1 && len == 2)k = j;
			}
			if (f)break;
			if (k != -1)
			{
                //差分修改。
				int to = e[col[i][k][0]].v;
				if (l[to] < l[i])-- sum[l[i]], ++ sum[r[i] + 1], -- cnt;
				else ++ sum[l[to]], -- sum[r[to] + 1];
				to = e[col[i][k][1]].v;
				if (l[to] < l[i])-- sum[l[i]], ++ sum[r[i] + 1], -- cnt;
				else ++ sum[l[to]], -- sum[r[to] + 1];
			}
			else -- cnt;
		}
		if (f)
		{
			cout << "0\n";
			continue;
		}
		for (int i = 1; i <= n; ++ i)
		{
			sum[i] += sum[i - 1];//前缀和统计。
			if (sum[i] == cnt)++ s;
		}
		cout << s << '\n';
	}
	return 0;
}
```

---

## 作者：ycy1124 (赞：6)

### 题意
在一棵有 $n$ 个节点，$n-1$ 条边的树上，每一条边都有一个字符作为它的权值，也就是经过它时代表权值的字符串加上这个字符。现在求一共有多少个节点作为根时，它到达所有节点的最小权值（也就是它所表示的字符串）互不相等。
### 思路+分析
首先考虑，在什么情况下会出现相同的字符串。显然，当一个节点所连的所有边中，假如有**大于等于** $2$ 条边的字符相等，当取这个节点为根时，就会出现相同的字符串。

我们可以将一个点所连的两条相同边权的边看作一对。对于每一对这样的边，最终合法的节点一定在以这个点为根这两条边所连的另外两个点的子树内，反之，**除了**这两个子树内的所有节点都是不合法的。不难得知，当一个节点连着**两对及以上**的这样的边时，没有节点会是合法的了。

对于最终统计答案，最终合法的节点一定是对于每一对边合法的点集的交集的大小，也就是它们之间重复的。我们可以通过树上差分来求每个点分别满足多少对边，当它满足**任意**一对边，就是合法节点。
### 实现过程
先以 $1$ 节点为根 dfs 一遍将每个节点的深度求出来，然后看每个节点上是否存在这样的一对边，假如对数大于 $1$ 就退出，否则就正常差分就行了。
### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 200001
using namespace std;
inline int rint(){//快读
	int ch=getchar(),x=0,f=1;
	for(;ch<'0'||ch>'9';ch=getchar())f=ch=='-'?-1:1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^'0');
	return x*f;
}
int t,n,sum[Maxn],h[Maxn],ans,num;//sum表示差分数组，h表示深度，ans是统计答案，num是边的对数
vector<int>a[Maxn][26];//存图
void dfs(int p,int w,int fa){//dfs求深度
	h[p]=w;
	for(int i=0;i<26;i++){
		for(auto it:a[p][i]){
			if(it==fa){
				continue;
			}
			dfs(it,w+1,p);
		}
	}
}
void dfs1(int p,int w,int fa){//dfs一遍求出最终的值
	sum[p]=w+sum[p];
	for(int i=0;i<26;i++){
		for(auto it:a[p][i]){
			if(h[it]<=h[p]){
				continue;
			}
			dfs1(it,sum[p],p);
		}
	}
}
int main(){
	t=rint();
	while(t){
		t--;
		n=rint();
		ans=0;
		num=0;
		for(int i=1;i<=n;i++){//多测清空
			for(int j=0;j<26;j++){
				a[i][j].clear();
			}
			sum[i]=0;
		}
		bool bj=0;
		for(int i=1;i<n;i++){//存图
			int u=rint(),v=rint();
			char ch;
			cin>>ch;
			a[u][ch-'a'].push_back(v);
			a[v][ch-'a'].push_back(u);
			if(a[u][ch-'a'].size()>=3||a[v][ch-'a'].size()>=3)bj=1;//一个节点多于2对边
		}
		if(bj){
			printf("0\n");
			continue;
		}
		dfs(1,0,0);
		bj=0;
		for(int i=1;i<=n&&!bj;i++){
			int js=0;//每个节点边的对数
			for(int j=0;j<26&&!bj;j++){
				if(a[i][j].size()==2){
					num++;
					js++;
					for(auto it:a[i][j]){
						if(h[it]<h[i]){//假如是父亲节点，差分与儿子节点不同，可以画个图感性理解一下
							sum[1]++;
							sum[i]--;
						}
						else{//儿子节点差分比较简单
							sum[it]++;
						}
					}
					if(js>=2){//对数大于2退出
						bj=1;
						break;
					}
				}
			}
		}
		if(bj){
			printf("0\n");
			continue;
		}
		dfs1(1,0,0); 
		for(int i=1;i<=n;i++){
			if(sum[i]==num){
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/182323534)。

---

## 作者：gghack_Nythix (赞：5)

## 前言：

我是入机，模拟赛题解看不懂一点，最后学了 zjh 大佬做法也是一看就懂了。

## 分析：

可以考虑换根 $\text{dp}$。设 $dp_i$ 表示以 $i$ 为根的子树中有没有重复的，那么首先判掉一定无解的情况：

- 同层有两个及以上的相同字符。

把这个判掉之后还要考虑：

- 他的儿子里面是否有重复的。

那么 $\text{dp}$ 方程也就自然而然的出来了。

$$
dp_{now} = \left\{\begin{matrix}
  0& \exists s_{x\in{son}} > \text{2}
\\
  \min_{} \{dp_{x\in{son}}\} & \text{otherwise} & 
\end{matrix}\right.
$$

$son$ 表示 $now$ 的儿子集合。

当把子树搜完之后，记得还原最初的 $\text{dp}$ 数表的值，不然会影响到下次换根。

```cpp
// EXpert实力！
# include <bits/stdc++.h>
# define pb push_back
# define cl clear
using namespace std;
const int N = 2e5 + 5;
int n;
struct node {
	int v;
	char w;
};
vector <node> g[N] ;
int vec[N],cnt;//vec记录方案
int mp[N][27];
bool dp[N];
void pre_dfs (int now , int fa) {
	dp[now] = 1; 
	for (auto x : g[now]) {
		if (x.v == fa) continue; 
		pre_dfs (x.v , now);
		dp[now] &= dp[x.v];
		mp[now][x.w - 'a'] ++;
	}
	for (int i = 0;i < 26;++i) if (mp[now][i] > 1) dp[now] = 0;
}
void cgroot (int now , int fa , int op ,int EX, int pert, char pre) {
	mp[now][pre - 'a'] += op, mp[fa][pre - 'a'] -= op;
	dp[now] = dp[fa] = 1;
	if (op == -1) return dp[now] = EX , dp[fa] = pert,void();
	for (int i = 0;i < 26;++i) {
		if (mp[now][i] > 1) dp[now] = 0;
		if (mp[fa][i] > 1) dp[fa] = 0;
	}
	for (auto x : g[fa]) if (x.v != now) dp[fa] &= dp[x.v];
	for (auto x : g[now]) dp[now] &= dp[x.v];		
	if (dp[now] && op == 1) vec[++cnt] = now;
}
void dfs (int now,int fa ,char pre) {
	int EX = dp[now],pert = dp[fa];
	if (now != 1) cgroot(now , fa , 1 ,EX , pert ,pre);
	for (auto x : g[now]) if (x.v != fa) dfs (x.v , now , x.w);
	if (now != 1) cgroot (now , fa , -1 ,EX , pert , pre);
}
void solve () {
	bool Lian = 1;
	cnt = 0;
	cin >> n;
	memset (dp,0,sizeof dp);
	memset (mp,0,sizeof mp);
	for (int i = 1;i <= n;++i) g[i].cl();
	for (int i = 1;i < n;++i) {
		int u,v; char w;
		cin >> u >> v >> w , g[u].pb(node {v,w} ) , g[v].pb(node {u,w} );
	}
	pre_dfs (1 , -1);
	if (dp[1]) ++cnt;
	dfs (1 , -1 , -1);
	cout << cnt << "\n";
	return void();
}
signed main () {
	ios::sync_with_stdio(false);
	cin.tie (0);
	cout.tie (0);
	int T;
	cin >> T;
	while (T -- >0) solve ();
	return 0;
}
/*
5
1 2 a
1 3 a
3 4 b
4 5 c
*/
```
upd:添加了对"入机"一词的解释，免得被认为是错别字。

---

## 作者：Nuyoah_awa (赞：4)

### 题目大意
给定一棵无根的 trie 树，求有多少点可以作为根，使得这颗 trie 树合法。
### 题目分析
首先观察一颗合法的 trie 树，题目中所给出的“合法”定义为从根到所有节点的路径所连成的字符串互不相同。

容易发现，对于距离根的深度不一样的两点，他们所连成的字符串长度就不一样，所以不可能一样。

而对于深度相同的两点，如果他们的父亲节点不一样，也就是说他们的字符串之前就不一样，即使边权一样，最终也不会一样。

于是，问题就转化为了同一个节点下，不能有两条边权一样的边。
#### 暴力：

于是，对于这颗无根树，我们可以枚举根节点然后判断。

但是时间复杂度是 $\mathcal O(n^2)$ 的。

#### 正解：

我们可以考虑先找一个节点为根，将其化为一颗有根树，然后尽可能一次求出所有点是否可以作为根。

主要分为 $3$ 种情况：

1. 在一个节点下有两边边权相同。

对于这种情况，根节点只有可能在这两条边所连的节点的子树中。

2. 一个节点中有一边边权与这个点与父亲节点的边权相同。

那么根节点只有可能在这条边所连节点的子树中。

3. 在一个节点下有大于两边边权相同或有两边边权相同且与这个点与父亲节点的边权相同。

即一个点有多于两条边的边权相同，则无论根节点在哪都无法合法，直接输出 $0$。

于是问题就简化为了树上打标记，很容易想到用树上差分。

最终时间复杂度是 $\mathcal O(n)$ 的。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

const int N = 1e5 + 5;
struct node{
	int id;
	char val;
};
int T, n, u, v, a[N], sum, ans;
char w;
bool tot;
map <char, int> mp, cnt;
vector <node> e[N];

inline void dfs(int x, int last, char w)
{
	cnt.clear(), mp.clear();
	for(register int i = 0;i < e[x].size();i++)
	{
		if(e[x][i].id == last)
			continue;
		if(e[x][i].val == w)
		{
			a[x]--;
			a[e[x][i].id]++;
		}
		if(cnt[e[x][i].val] == 1)
		{
			if(e[x][i].val == w)
				tot = true;
			else
				a[mp[e[x][i].val]]++, a[e[x][i].id]++, sum++;
		}
		else if(cnt[e[x][i].val] > 1)
			tot = true;
		cnt[e[x][i].val]++;
		mp[e[x][i].val] = e[x][i].id;
	}
	for(register int i = 0;i < e[x].size();i++)
		if(e[x][i].id != last)
			dfs(e[x][i].id, x, e[x][i].val);
	return ;
}

inline void get_ans(int x, int last)
{
	a[x] += a[last];
	if(a[x] == sum)
		ans++;
	for(register int i = 0;i < e[x].size();i++)
		if(e[x][i].id != last)
			get_ans(e[x][i].id, x);
	return ;
}

signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		memset(a, 0, sizeof(a));
		ans = sum = 0;
		for(register int i = 1;i <= n;i++)
			e[i].clear();
		scanf("%d", &n);
		for(register int i = 1;i < n;i++)
		{
			scanf("%d %d", &u, &v);
			cin >> w;
			e[u].push_back({v, w});
			e[v].push_back({u, w});
		}
		tot = false;
		dfs(1, 0, ' ');
		if(tot)
			printf("0\n");
		else
		{
			get_ans(1, 0);
			printf("%d\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：_maple_leaf_ (赞：3)

noip 模拟赛 T1，很简单，场切了。
## 题意
我们定义一个以 $i$ 为根的合法 trie 为从点 $i$ 到任意点的路径上的边的字符拼起来的字符串互不相同，求有多少个点为根，使得给出的无根 trie 成为为合法 trie。
## 思路
首先考虑无解的情况，如果一个点连出的边有三条的字符是相同的或有两个及以上对边的字符相同是无解的。

紧接着发现如果当前点没有任意两条边的字符相同，那么它对合法根就没有限制；如果当前点只有一对边上的字符相同，不难发现，合法根只可能出现在以这两条边连着的那两个点为根的子树内。

因此我们每次可对对于每个点可以成为合法根的点加上 $1$ 的标记，那最后统计时只要被加了 $n$ 次标记就是一个合法根。

考虑暴力，每次对于限制，暴力对子树加标记，时间复杂度 $O(n^2)$。

考虑优化，只有全子树加可以使用 dfs 序，在 dfs 序下，树上的任意一棵子树在一个区间，那么每次全子树加就是给 dfs 序下的数组区间加，无在线查询，只有区间加减，所以使用差分，时间复杂度 $O(n)$。
## code
```c++
#include<bits/stdc++.h>
#define FAST true
#define FIO true
#define DEBUG false
using namespace std;
#if FIO
void fio(string s,int i=0){
    freopen(((s+(i?to_string(i):""))+".in").c_str(),"r",stdin);
    freopen(((s+(i?to_string(i):""))+".out").c_str(),"w",stdout);
}
#endif
//#define int long long
//#define int unsigned int
//#define int __int128
#if DEBUG
bool Memory_start;
void debug();
#endif
#if FAST
inline int read(){
    char c=getchar();
    int ret=0,f=1;
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        ret=(ret<<3)+(ret<<1)+c-'0';
        c=getchar();
    }return ret*f;
}
inline void write(int x,int op=0){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10,0);
    putchar((char)(x%10+'0'));
    if(op){
        if(op>0)puts("");
        if(op<0)putchar(' ');
        if(op==0)puts("114514");
    }
}
#endif
const int N=2e5+10;
int T;
int n;
int m;
bool fl;
int tot;
int cnnt;
int f[N];
int l[N],r[N];
struct node{
    int v,n;
}e[N<<1];
int head[N],cnt;
vector<int>cb[N][30];
void add(int u,int v,char c){
    e[++cnt]={v,head[u]};
    head[u]=cnt;
    cb[u][c-'a'+1].push_back(cnt);//记录每种字符的边
}
void dfs(int nw,int fa){
    l[nw]=++cnnt;//记录以 nw 为根的子树在 dfs 序下的区间左右端点（dfn 和 low）。
    for(int i=head[nw];i;i=e[i].n){
        int to=e[i].v;
        if(to==fa)continue;
        dfs(to,nw);
    }r[nw]=cnnt;
}
signed main(){
    T=read();
    while(T--){
		fl=0;
        tot=0;
        cnt=0;
        cnnt=0;
        memset(l,0,sizeof l);
        memset(r,0,sizeof r);
        memset(f,0,sizeof f);
        memset(head,0,sizeof head);
        for(int i=1;i<=n;i++)for(int j=1;j<=26;j++)cb[i][j].clear();//初始化
        m=n=read();
        for(int i=1;i<n;i++){
            int u=read(),v=read();char c;cin>>c;
            add(u,v,c);
            add(v,u,c);
        }dfs(1,0);
        for(int i=1;i<=n;i++){
            int tmp=0;
            for(int j=1;j<=26;j++){
                if(cb[i][j].empty())continue;
                if(cb[i][j].size()==2&&tmp||cb[i][j].size()>=3){
                    fl=1;
                    break;//无解
                }
                if(cb[i][j].size()==2&&!tmp)tmp=j;
            }if(fl)break;
            if(!tmp)m--;//给整颗树加上标记就是给最后的判断合法标记数减一
            else{
                int v=e[cb[i][tmp][0]].v;
                if(l[v]<l[i])m--,f[l[i]]--,f[r[i]+1]++;//考虑返祖边，事实上就是给整颗数加上一个标记（处理方法同上），给以 i 为根的子树减一个标记
                else f[l[v]]++,f[r[v]+1]--;
                v=e[cb[i][tmp][1]].v;
                if(l[v]<l[i])m--,f[l[i]]--,f[r[i]+1]++;//同上
                else f[l[v]]++,f[r[v]+1]--;
            }
        }if(fl){//无解
            puts("0");
            continue;
        }
        for(int i=1;i<=n;i++){
            f[i]+=f[i-1];
            if(f[i]==m)tot++;
        }
        write(tot,1);
    }
#if DEBUG
    debug();
#endif
    return 0;
}
#if DEBUG
bool Memory_end;
void debug(){
    cerr<<"Time: "<<clock()<<" ms\n";
    cerr<<fixed<<setprecision(6)<<"Memory: "<<abs(&Memory_start-&Memory_end)/1024.0/1024.0<<" MB";
}//~*完结撒花*~
#endif
```

---

## 作者：StayAlone (赞：3)

### 题意

对于一棵 trie，设 $s(x)$ 表示从根到点 $x$ 的路径上的字符拼接而成的字符串。

一棵 trie 合法，当且仅当 $s(x)$ 互不相同。

给定一棵边上有字母的树，询问以它的多少个点为根，形成的 trie 合法。

### 思路

容易发现，若一个点有三条边上的字母相同，一定无解。

若一个点，它有两条边上的字母相同，设这个点为关键点。

设关键点数量为 $m$。

为了方便操作，先定义 $1$ 为根。

如图。

![](https://z1.ax1x.com/2023/09/17/pPhM7i6.png)

对于关键点 $4$，为了满足它的要求，根只有可能是 $6$ 子树内的点或者 $5$ 子树内的点。因为以任何其它的点当做根，都会出现 $5$ 号点和 $6$ 号点同时作为 $4$ 号点儿子的情况，显然不满足 trie 的性质。

对于关键点 $3$，按照刚才的分析，$2$ 号点有可能成为根。但同时，蓝框内的所有点也有可能成为根。蓝框内的点就是整张图减去关键点为根的子树。

那么，对于每个关键点，可以找到所有为了满足**这个关键点的要求**而可能成为根的点。那么最终真正可以成为根的点，就是这些点的交。

于是子树修，单点查。dfs 序上放一个数据结构即可。

代码队友是写的。

---

## 作者：guozhetao (赞：3)

## 题面
[P9648](https://www.luogu.com.cn/problem/P9648)，因测试数据过少且不支持下载，可前往我自己造的[相应题目](https://www.luogu.com.cn/problem/U364800)进行调试。

trie 的定义是这样的：

- 一棵大小为 $n$ 的 trie，是一棵有着 $n$ 个节点和 $(n−1)$ 条边的有根树，每一条边上都标有一个字符；

- 在 trie 中，从根结点到树上某一结点的路径代表一个字符串，节点 $x$ 代表的字符串记为 $s(x)$，特别地，根节点代表的字符串为空串。

- 若节点 $u$ 是节点 $v$ 的父节点，且 $c$ 是连接 $u$ 与 $v$ 的边上的字符，则有 $s(v)=s(u)+c$（这里的 $+$ 表示字符串的连接，而非普通的加法运算）。

当每一个节点代表的字符串互不相同时，该 trie 是合法的。
给出一个无根的 trie，求其中有多少节点可作为该 trie 的根，使得该 trie 合法。


## 思路
首先容易想到枚举根节点再依次判断，但是复杂度无法通过本题。考虑以下性质：

-  对于一个以 $i$ 号节点为根的树，如果存在 $a,b,c$ 使得 $b,c$ 为 $a$ 儿子，且从 $a$ 到 $b$ 与从 $a$ 到 $c$上的字符相等，那么 $i$ 为根的树非法，因为 $s(b) = s(c)$。 $(1)$
- 对于一个节点，如果与其相连的节点中有 $3$ 个满足边上的字符都相同，那么这个图中任意一个点做节点都是非法的，因为无论以谁为根节点都无法满足（见 $(1)$）。
- 如果存在 $a,b,c$ 使得 $a,b$ 与 $a,c$ 均联通，且从 $a$ 到 $b$ 与从 $a$ 到 $c$上的字符相等，如果 $i$ 节点到 $a$ 节点的路径上不经过 $b$，$c$ 两点，则 $i$ 节点为根的树非法，因为会造成 $b,c$ 均为 $a$ 儿子（见 $(1)$）。

通过以上性质，我们可以从 $1$ 号节点遍历，枚举判断每一个节点时候合法。
## 代码
[AC 记录](https://www.luogu.com.cn/record/169486119)
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,head[200005],nex[400005],to[400005],cnt = 0;
char w[400005]; 
bool can[200005];
int num;
//清空 
void qk() {
	cnt = 0,num = n;
	for(int i = 0;i <= 200000;i++) head[i] = 0,can[i] = true;
	for(int i = 0;i <= 400000;i++) nex[i] = 0,to[i] = 0,w[i] = ' ';
	return;
}
//加边
void add(int x,int y,char z) {
	nex[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
	w[cnt] = z;
} 
bool dfs(int now,int fa,bool ok) {
	//ok 代表当前点是否合法 
	int xt = 0;
	if(!ok) xt++;
	bool get = ok;
	if(num == 0) return false;
	bool return_ok = true,return_ok2 = true;
	int have[27][3];
	for(int i = 0;i <= 26;i++) have[i][1] = -1,have[i][2] = -1;
	// 找到与父亲连接的边对应的字符 
	for(int i = head[now];i;i = nex[i]) {
		if(to[i] == fa) {
			have[int(w[i] - 'a')][1] = fa;
			break;
		}
	}
	//找到剩下的边 
	for(int i = head[now];i;i = nex[i]) {
		if(to[i] == fa) continue;
		if(have[int(w[i] - 'a')][1] == -1) have[int(w[i] - 'a')][1] = to[i];
		else if (have[int(w[i] - 'a')][2] != -1) {
			num = 0;
			return false;
		}
		else {
			have[int(w[i] - 'a')][2] = to[i];
			if(!(have[int(w[i] - 'a')][1] == fa and !ok)) xt++;
			if(have[int(w[i] - 'a')][1] == fa) return_ok2 = true;
			else return_ok2 = false;
			if(xt == 2) {
				num = 0;
				return false;
			}
		}
	}
	if(xt) ok = false;
	for(int i = head[now];i;i = nex[i]) {
		if(to[i] == fa) continue;
		if(!return_ok) {
			dfs(to[i],now,return_ok);
			continue;
		}
		if(ok) {
			if(!dfs(to[i],now,ok)) {
				return_ok = false;
				for(int j = head[now];j != i;j = nex[j]) {
					if(to[j] != fa) dfs(to[j],now,return_ok);
				}
			}
		}
		else {
			if(have[int(w[i] - 'a')][2] == to[i]) {
				if(!dfs(to[i],now,get)) {
					return_ok = false;
					for(int j = head[now];j != i;j = nex[j]) {
						if(to[j] != fa) dfs(to[j],now,return_ok);
					}
				}
			}
			else if(have[int(w[i] - 'a')][1] == to[i] and have[int(w[i] - 'a')][2] != -1){
				if(!dfs(to[i],now,get)) {
					return_ok = false;
					for(int j = head[now];j != i;j = nex[j]) {
						if(to[j] != fa) dfs(to[j],now,return_ok);
					}
				}
			}
			else if(!dfs(to[i],now,ok)) {
				return_ok = false;
				for(int j = head[now];j != i;j = nex[j]) {
					if(to[j] != fa) dfs(to[j],now,return_ok);
				}
			}
		}
		if(num == 0) return false;
	}
	if(!ok or !return_ok or !return_ok2) {
		if(num == 0) return false;
		if(can[now]) can[now] = false,num--;
	}
	return (return_ok && return_ok2);
}
signed main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		qk();
		for(int i = 1;i < n;i++) {
			int x,y;
			char z;
			scanf("%d %d",&x,&y);
			cin >> z;
			add(x,y,z),add(y,x,z);
		}
		dfs(1,1,1);
		printf("%d\n",num);
	}
    return 0;
}
```

---

## 作者：xuchuhan (赞：2)

## Preface

模拟赛题。赛时一直想着做换根 dp，但是转移不出来。

## Solution

首先判无解：对于任意一个点，当它有三条及以上同样字符的边时，是没有满足条件的根的；当它有两对及以上相同字符的边时，也没有满足条件的根。

那么现在对于一个点 $x$，只剩下最多一对有相同字符的边。我们在当前钦定一个全局根节点，设这一对边所连向的 2 个节点分别为 $y,z$，那么这一对相同字符的边有 2 种情况：

- $y$ 为 $x$ 的父亲，$z$ 为 $x$ 的儿子，此时合法的根在 $z$ 的子树内和 $x$ 的子树外。
- $y,z$ 均为 $x$ 的儿子，此时合法的根在 $y,z$ 的子树内。

那么问题转化为树上子树覆盖问题，可以将子树转化为一段连续的 dfs 序进行覆盖。因为是静态问题，可以使用差分前缀和维护。

最后，若存在节点被所有操作覆盖，则它是合法的根。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,n,tot,num;
int dfn[N],siz[N],diff[N];
vector<int>ans,v[N],col[N][30];//col[i][j]:节点i,j颜色 
void DFS(int x,int fa){//求dfs序 
	dfn[x]=++tot,siz[x]=1;
	for(int i=0;i<v[x].size();i++){
		int to=v[x][i];
		if(to==fa)continue;
		DFS(to,x);
		siz[x]+=siz[to]; 
	}
	return;
}
void upd(int x,int y,int val){diff[x]+=val,diff[y+1]-=val;return;}//差分:将[x,y]加上val 
void work(){
	cin>>n;tot=num=0;ans.clear();
	for(int i=1;i<=n;i++){//多测清空 
		v[i].clear();diff[i]=0;
		for(int j=0;j<26;j++)col[i][j].clear();
	}
	for(int i=1;i<n;i++){
		int x,y;char c;
		cin>>x>>y>>c;
		v[x].push_back(y);
		v[y].push_back(x);
		col[x][c-'a'].push_back(y);
		col[y][c-'a'].push_back(x);
	}
	DFS(1,0);
	for(int i=1;i<=n;i++){
		bool flg=0;
		int pos=26;
		for(int j=0;j<26;j++){
			int siz=col[i][j].size();
			if(!siz)continue;
			if(siz>=3||(siz==2&&flg)){cout<<"0\n";return;}//不合法 
			if(siz==2)flg=1,pos=j;
		}
		if(pos!=26){
			num++;//记录总操作数量 
			int t1=col[i][pos][0],t2=col[i][pos][1];
			if(dfn[t1]<dfn[i]||dfn[t2]<dfn[i]){//一父亲一儿子 
				if(dfn[t2]<dfn[t1])swap(t1,t2);
				upd(1,dfn[i]-1,1),upd(dfn[i]+siz[i],n,1);//注意这里:不覆盖字数内相当于覆盖子树外,也就是除了子树内的dfs序都要被修改 
				upd(dfn[t2],dfn[t2]+siz[t2]-1,1);
			}
			else upd(dfn[t1],dfn[t1]+siz[t1]-1,1),upd(dfn[t2],dfn[t2]+siz[t2]-1,1);//2个儿子
		}
	}
	for(int i=1;i<=n;i++){
		diff[i]+=diff[i-1];//前缀和 
		if(diff[i]==num)ans.push_back(i);//记录答案 
	}
	cout<<ans.size()<<"\n";
	return;
}
signed main(){
	cin>>T;
	while(T--)work();
	return 0;
}
```

## Summary

不错的题目，需要挖掘部分性质，还有一个静态 $\mathcal{O(1)}$ 修改子树的 trick。

## Afterword

听说赛前写题解会 rp++，也祝自己和大家 CSP-J/S2024 rp++！

---

## 作者：_Flame_ (赞：2)

### $\text{solution}$
模拟赛场切了。

观察性质可以发现，在一棵 trie 树上只有父节点相同且当前边上的字母相同时才会出现相同的串，回到这题来，可以发现当一个点周围有三条字母相同的边时，一定不合法。

对于合法的条件，我们分类讨论：

- 若一个点 $u$ 有两个儿子 $v_1$ 和 $v_2$ 使得边 $\lbrace u,v_1\rbrace=\lbrace u,v_2\rbrace$，可以证明合法的根一定在以 $v_1$ 和 $v_2$ 为根的子树里。

- 若一个点 $u$ 使得其父亲 $fa$ 和其一个儿子 $v$ 使得边 $\lbrace u,v\rbrace=\lbrace fa,u\rbrace$，此时合法的根一定在 $v$ 的子树中。

直接钦定一个根节点，对于以上两种情况在树上用差分给合法根打标记，若一个点被所有的情况标记了，则其可以为根。

---

## 作者：SDLTF_凌亭风 (赞：2)

来自某不愿意透露姓名的队友。

---
有点意思。

首先有一个很显然的性质：如果一个节点与另两个节点有同样字母的边，那么必然这三个节点是父子孙的关系，而不是一个父节点和两个子节点的关系。

所以，如果一个节点跟另外三个节点有同样字母的边，或是跟两个节点有同样字母的边，跟另两个节点有另外一种字母的边，肯定是不合法的情况，直接判掉。

然后对于一个无根树来说不是很好处理，所以把它转化为以 $1$ 为根的有根树。这时，一个节点（以下设为 $x$）与另两个节点（以下设为 $u,v$）同种字母的边，要么形成父子孙关系，要么是一个父节点和两个子节点。

- 对于父子孙关系（比如说 $u\to x\to v$），所有节点中，只有在 $x$ 的子树内但不在 $v$ 的子树内的节点不可能成为根，否则会变成 $x\to u,x\to v$ 就寄了。
- 对于一个父节点两个子节点（比如说 $x\to u,x\to v$），只可能是 $u$ 和 $v$ 的子树内的节点才可能成为根，原因同理。

对于一个节点只有满足所有这样的约束才有可能成为根，所以我们可以打标记。由于只涉及到子树内所有点的加法操作，所以可以用 dfs 序转化为区间加，然后离线单点查询，差分就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
struct Edge{
	ll to,prev;
	char ch;
};
Edge ed[MAXN<<1];
map<char,ll>mp;
ll test,n,x,y,tot,df,t,tag,rres;
char ch;
ll last[MAXN],fa[MAXN],dfn[MAXN],sz[MAXN],res[MAXN];
char c[MAXN];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline void addEdge(ll u,ll v,char ch)
{
	ed[++tot]=(Edge){v,last[u],ch},last[u]=tot;
}
inline void dfs(ll x,ll f)
{
	ll to;
	fa[x]=f,sz[x]=1,dfn[x]=++df;
	for(register int i=last[x];i;i=ed[i].prev)
	{
		(to=ed[i].to)!=f?dfs(to,x),sz[x]+=sz[ed[i].to]:1;
	}
}
inline void calc(ll x)
{
	ll u=0,v=0;
	for(register int i=last[x];i;i=ed[i].prev)
	{
		ed[i].ch==c[x]?(!u?u=ed[i].to:v=ed[i].to):1;
	}
	if(u==fa[x]||v==fa[x])
	{
		u!=fa[x]?swap(u,v):(void)1;
		res[dfn[x]]++,res[dfn[x]+sz[x]]--;
		res[dfn[v]]--,res[dfn[v]+sz[v]]++;
		return;
	}
	res[1]++,res[n+1]--;
	res[dfn[u]]--,res[dfn[u]+sz[u]]++;
	res[dfn[v]]--,res[dfn[v]+sz[v]]++;
}
inline void solve()
{
	n=read(),tot=df=rres=0;
	for(register int i=1;i<=n;i++)
	{
		last[i]=res[i]=c[i]=0;
	}
	for(register int i=1;i<n;i++)
	{
		x=read(),y=read(),scanf("%c",&ch),addEdge(x,y,ch),addEdge(y,x,ch);
	}
	for(register int i=1;i<=n;i++)
	{
		mp.clear(),t=tag=0;
		for(register int j=last[i];j;j=ed[j].prev)
		{
			if(++mp[ed[j].ch]==2)
			{
				t++,c[i]=ed[j].ch;
			}
			tag=max(tag,mp[ed[j].ch]);
		}
		if(tag>=3||t>=2)
		{
			return (void)(puts("0"));
		}
	}
	dfs(1,0);
	for(register int i=1;i<=n;i++)
	{
		c[i]?calc(i):(void)1;
	} 
	for(register int i=1;i<=n;i++)
	{
		rres+=((res[i]+=res[i-1])==0);
	}
	printf("%d\n",rres); 
}
int main()
{
	test=read();
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```

---

## 作者：RainySoul (赞：1)

*挺有意思的一道题，模拟赛第一题，赛时看错题，垫底了，写个题解纪念一下。*

[题目传送门](https://www.luogu.com.cn/problem/P9648)

### 题意

给定一颗树，每条边上有一个小写字母，定义一个节点表示的字符串为根节点到它的简单路径上每条边的小写字母顺次拼接起来得到的字符串。

选定一个点作为根节点，它是合法的当且仅当所有节点表示的字符串均不相同。

求一共有多少个点可以作为根节点。

### 思路

首先一个显而易见的性质是：我的所有儿子边中不能出现相同的字母，否则他们俩表示的字符串一定相同。

那么你思考：如果一个点所有连边中出现了相同的字母，我可以使它合法吗？

如果只有一种字母出现重复并且只重复出现了一次，那么是可行的。如我所有连边上的字母分别是 $\{a,a,b,c\}$，你只要不让两个 $a$ 同时作为儿子边就好了，就是说根节点只能出现在两个 $a$ 通往的点中。

而其他情况，如果相同的字母对不止一个，如 $\{a,a,b,b\}$ 你不管选谁都会出现不合法情况；还有同一个字母出现两次以上的，如 $\{a,a,a,b\}$，也是选谁都不合法。就是说根节点在哪个方向上都不符合条件，你直接输出 $0$。

那么现在你有了一个比较明确的思路，随便选一个点作为起点，到达一个点之后判断它的所有连边中有无相同字母，把不合法的直接判掉。接下来就是存在合法情况，如果没有相同字母的话就每条边都走，如果有相同字母的话你就只有相同字母的那两条边可以走了。

直接做是 $O(Tn^2)$ 的。但是你发现其实可以随便找一个点作为起点，遍历一遍把所有对于根节点位置的限制跑出来。

一个点对根节点位置的限制应该形似这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/idz7js4j.png)

如果你的儿子边中有两个 $a$，那么根节点只能在这两条边所连儿子的子树内，就是红色框出的区域。

---

同样的，遍历的时候也有可能是我到我父亲的边和我的一条子边相同，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/7fv8yzpu.png)

对于这条连向父亲的边，除了我的子树内的点都可以选。对于另一条儿子边，只能选这个儿子的子树内的点。

如果给整棵树标上 dfn 序，你发现你每次给限制的那些点的 dfn 序是连续的，可以差分维护。

将所有限制标完之后还原差分数组，如果有哪个点所有的限制都满足它就可以作为根节点。

时间复杂度 $O(Tn)$。

#### 提醒

> 多测不清空，爆零两行泪。

AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
struct zyx{
	int to;
	char c;
};
struct csq{
	int now,fa,dep;
};
vector<zyx> e[N];
int T,n,cs,cnt,ans,f;
int dfn[N],sz[N],flag[30],cf[N],qz[N];
void dfs(int now,int fa){
	dfn[now]=++cnt;sz[now]=1;
	for(int i=0;i<e[now].size();i++){
		int to=e[now][i].to;
		if(to!=fa)dfs(to,now),sz[now]+=sz[to]; 
	} 
}
void dfs1(int now,int fa){
	if(f==0)return;
	memset(flag,0,sizeof flag);
	for(int i=0;i<e[now].size();i++){
		char c=e[now][i].c;
		flag[c-'a']++;
	}
	int temp=0;
	for(int i=0;i<26;i++){
		if(flag[i]==2)temp++;//统计字母对的个数 
		else if(flag[i]>2)temp+=2;//这里是为了让它直接跳到 temp>1 
		if(temp>1)break;
	}
	if(temp>1){
		f=0;
		return;
	}
	if(temp==1){//仅有一个字母对 
		cs++;//记录总限制个数 
		int color;
		for(int i=0;i<26;i++){
			if(flag[i]==2){
				color=i;
				break;
			}
		}
		for(int i=0;i<e[now].size();i++){
			int to=e[now][i].to;
			if(e[now][i].c-'a'==color){
				if(to==fa)cf[1]++,cf[dfn[now]]--,cf[dfn[now]+sz[now]]++;//将所有数全都加一后将 now的子树减一 
				else cf[dfn[to]]++,cf[dfn[to]+sz[to]]--;//to的子树的 dfn序为 dfn[to]到 dfn[to]+sz[to]-1 
				//上面两行是精髓，可以认真看看 
			}
		}
	}
	for(int i=0;i<e[now].size();i++){
		int to=e[now][i].to;
		if(to!=fa)dfs1(to,now);
	}
}
void init(){
	ans=cnt=cs=0;f=1;
	memset(dfn,0,sizeof dfn);
	memset(qz,0,sizeof qz);
	memset(cf,0,sizeof cf);
	memset(sz,0,sizeof sz);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--){
		init();//一定要清干净！调了我好一会/(ㄒoㄒ)/~~
		cin>>n;
		for(int i=1;i<=n;i++)e[i].clear();
		for(int i=1;i<n;i++){
			int u,v;
			char c;
			cin>>u>>v>>c;
			e[u].push_back((zyx){v,c});
			e[v].push_back((zyx){u,c});
		}	
		dfs(1,0);dfs1(1,0); 
		//第一遍 dfs跑出 dfn序并求出每个点子树大小
		//第二遍 dfs1遍历每个点求限制 
		for(int i=1;i<=n;i++)qz[i]=qz[i-1]+cf[i];//还原差分数组 
		for(int i=1;i<=n;i++)
			if(qz[dfn[i]]==cs)ans++;
		if(f==0)cout<<0<<'\n';
		else cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

模拟赛 T1，来水个题解。

### 思路：

考虑一个与点 $u$ 相连的所有边的边权，需要满足：

- 不存在两个及以上个字母出现了 $2$ 次以上。

- 不存在一个字母出现了 $3$ 次以上。

否则就无解。

那么对于与一个点 $u$ 相连的边权中只可能出现两种情况：

- 没有任何字母重复出现，任意

- 只有一个字母重复出现，设 $x,y$ 表示那边权重复的两条边的另一个短短，则若以 $rt$ 为根时，需要满足 $x$ 或 $y$ 中有一个必须为 $u$ 的父亲。

首先考虑以 $1$ 为根跑一遍，然后分类讨论：

- 若 $x,y$ 都是 $u$ 的儿子，则根 $rt$ 必须在 $x$ 子树或 $y$ 子树内。

- 若 $x$ 是 $u$ 的父亲，则根 $rt$ 必须在 $y$ 子树内或者除了 $u$ 子树外的任意节点；若 $y$ 是 $u$ 父亲同理。

这些条件我们都要满足，那么可以求出树上的 dfn 序，上面满足条件的是几段区间，要求出交集，可以转化为区间覆盖，使用差分维护即可。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const ll N=2e5+10,M=26; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
inline char get(){
	char c;
	while(1){
		c=getchar();
		if(c>='a'&&c<='z')
		  break;
	}
	return c;
}
char c;
ll n,u,v,cnt,sum,ans;
ll dfn[N],siz[N],fa[N],d[N],s[M],id[N],g[N][2];
vector<pair<ll,char>> E[N];
void add(ll u,ll v,char w){
	E[u].push_back({v,w});
	E[v].push_back({u,w});
}
void get(ll l,ll r){
	if(l>r)
	  return ;
	if(l<1||r>n)
	  return ;
	d[l]++;
	d[r+1]--;
}
void dfs1(ll u,ll f){
	siz[u]=1;
	dfn[u]=++cnt;
	id[cnt]=u;
	for(auto t:E[u]){
		ll v=t.fi;
		if(v==f)
		  continue;
		fa[v]=u;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
}
void solve(){
	cnt=ans=0;
	n=read();
	For(i,1,n){
		g[i][0]=g[i][1]=d[i]=0;
		E[i].clear();
	}
	For(i,1,n-1){
		u=read(),v=read(),c=get();
		add(u,v,c);
	}
	For(u,1,n){
		sum=0;
		For(i,0,M-1)
		  s[i]=0;
		for(auto t:E[u]){
			c=t.se;
			if((++s[c-'a'])>1)
			  sum++;
		}
		if(sum>1){
			puts("0");
			return ;
		}
		if(sum==1){
			for(auto t:E[u]){
				v=t.fi,c=t.se;
				if(s[c-'a']==2){
					if(g[u][0])
					  g[u][1]=v;
					else
					  g[u][0]=v;
				}
			}
		}
	}
	sum=0;
	dfs1(1,1);
	For(u,1,n){
		if(!g[u][0])
		  continue;
		sum++;
		if(g[u][0]==fa[u]||g[u][1]==fa[u]){
			if(g[u][1]==fa[u])
			  swap(g[u][0],g[u][1]);
			get(1,dfn[u]-1);
			get(dfn[u]+siz[u],n);
			get(dfn[g[u][1]],dfn[g[u][1]]+siz[g[u][1]]-1);
		}
		else{
			get(dfn[g[u][0]],dfn[g[u][0]]+siz[g[u][0]]-1);
			get(dfn[g[u][1]],dfn[g[u][1]]+siz[g[u][1]]-1);
		}
	}
	For(i,1,n){
		d[i]+=d[i-1];
		if(d[i]==sum)
		  ans++;
	}
	write(ans);
	putchar('\n');
}
int main(){
//	open("trie.in","trie.out");
	ll T=read();
	while(T--)
	  solve();
	return 0;
}
```

---

## 作者：__lzx__ (赞：0)

# 洛谷 P9648
## 题目大意
给定一个 $n$ 个结点的无根 tire 树。求其中有多少个点可以作为根。
## 题目分析
先考虑 trie 树的性质，可以发现对于 trie 树的每个结点，其与儿子所连接的边中，不存在代表字母相同的两条边。因而可以将结点分为以下几种情况：
1. 所有连接的边中，代表同一字母的边个数大于 $2$。这样不管以谁为根对会导致该节点出现代表字母相同的边数量大于等于 $2$。所以如果出现这样的点，答案为 $0$。
2. 所有连接的边中，代表同一字母的边个数等于 $2$，现称这样的两条边为合法边对。对于这种点，延代表同一字母的边遍历树，能遍历到的点才可能成为根。因而可以想到**标记**可能的根，最后如果一个点被标记的次数等于**合法边对**的数量，那么它可以为根。
3. 所有连接的边中，代表同一字母的边个数小于 $2$。这样的点可能成为根，也不会影响其他点成为根，不做特殊处理。

接下来要解决标记问题。首先不用将可能的根全部遍历，会导致时间复杂度太大。可以考虑将无根树当做有根树做，这样一来，一个点只会标记**它的子树**，或**整棵树挖掉以其为根的子树后的树**。因而可以使用一个数组 mk，$mk[i]$ 表示以 $i$ 为根的子树被标记的次数。对于标记子树直接更新子结点，对于父结点，给根更新，再把当前结点挖掉，以此实现 $O(1)$ 标记。查询类似线段树，遍历整棵树，将标记下传到子节点在遍历到结点时计算答案。
## 代码
```c++
#include<bits/stdc++.h>
#define S 200005
using namespace std;
//快读,不打也行
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int T=read();//如题意 
int fg;//判断第一种点 
int sum;//合法边对数量 
int ans;//存答案 
int mk[S];//以i为根的子树被标记的次数 
struct edge{
	int to;//边走向的点 
	char ch;//边代表的字母 
};
vector<edge>g[S];
//标记 
inline void dfs1(int p,int f,char ch){
	int cnt[26]={0};//每个字母出现的次数 
	int pt[26][3];//字母对应的点 
	//记录与父结点相连的边 
	if(p!=1){//根要特判 
		cnt[ch-'a']=1;
		pt[ch-'a'][1]=f;
	}
	//遍历子树 
	for(auto v:g[p]){
		if(v.to==f)continue;
		int id=v.ch-'a';
		//记录连接子树的边 
		++cnt[id]; 
		if(cnt[id]>=3){//判掉第一种点 
			fg=1;
			return;
		}
		pt[id][cnt[id]]=v.to;
		dfs1(v.to,p,v.ch);
		if(fg)return;
	}
	//处理第二种点 
	for(int i=0;i<26;++i){
		if(cnt[i]!=2)continue;
		++sum;
		int p1=pt[i][1],p2=pt[i][2];
		//标记 
		if(p1==f){ 
			++mk[1];//标记整棵树 
			--mk[p];//挖掉以当前点为根的子树 
		}else ++mk[p1];//否则直接更新 
		if(p2==f){
			++mk[1];
			--mk[p];
		}else ++mk[p2];
	}
}
//算答案 
inline void dfs2(int p,int f){
	//下传标记 
	mk[p]+=mk[f];
	//计算答案 
	if(mk[p]==sum)++ans;
	for(auto v:g[p]){
		if(v.to==f)continue;
		dfs2(v.to,p);
	}
}
signed main(){
	while(T--){
		int n=read();//如题意
		//初始化 
		memset(mk,0,sizeof mk);
		ans=sum=fg=0;
		for(int i=1;i<=n;++i)g[i].clear();
		//输入,建边 
		for(int i=0;i<n-1;++i){
			int u=read(),v=read();
			char ch;
			cin>>ch;
			g[u].push_back({v,ch});
			g[v].push_back({u,ch});
		}
		dfs1(1,0,'a');
		if(!fg)dfs2(1,0);
		if(fg)puts("0");//第一种点存在 
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

