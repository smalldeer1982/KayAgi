# [COTS 2019] 排名 Vezuv

## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D2T3。$\texttt{1.5s,0.5G}$。

## 题目描述



在某场 ICPC Regional 中，组委会决定用队伍名的字典序来决定排名。不幸的是，对于队名以字母 $\texttt{z}$ 开头的队伍，这是相当不公平的。

经过讨论，组委会决定：随机抽取一个 $26$ 个字母的排列，用字母的排列对应的字典序来决定排名。

有 $N$ 支队伍参加了这场比赛，队伍名都为小写英文字母。

Etna 写了一个程序枚举了 $26!$ 个排列，以期找到能使每个队伍夺冠的排列。但是这个程序至今都没有跑出结果。

所以她找来了你，为每个队伍构造一个排列，使得这支队伍夺冠。


## 说明/提示


令 $L$ 为字符串总长度，$|\Sigma|$ 为字符串字符集大小。

对于 $100\%$ 的数据，保证：

- $1\le N\le 25\, 000$；
- $1\le L\le 10^6$；
- 队伍名两两不同；
- $1\le |\Sigma|\le 26$。


| 子任务编号 | $N\le $ | $L\le $ | $\vert\Sigma\vert\le$    | 得分 |  
| :--: | :--: |:--: |  :--: | :--: | 
| $ 1 $    | $ 100 $ |   $ 10^4 $   |  $6$ | $13$ |
| $ 2 $    | $ 350 $ |  $ 10^4 $   |  $26 $ | $32$ |
| $ 3 $    | $ 25\, 000 $ | $ 10^6 $   |  $26$ |  $55$ |

## 样例 #1

### 输入

```
3
war
zag
wro```

### 输出

```
agorwzbcdefhijklmnpqstuvxy
agorzwbcdefhijklmnpqstuvxy
gorawzbcdefhijklmnpqstuvxy```

## 样例 #2

### 输入

```
3
b
ab
aa```

### 输出

```
bacdefghijklmnopqrstuvwxyz
nemoguce
abcdefghijklmnopqrstuvwxyz```

## 样例 #3

### 输入

```
7
bcada
dbaab
bbabc
ababb
aacdf
bcdff
baddb```

### 输出

```
cbadfeghijklmnopqrstuvwxyz
cdabfeghijklmnopqrstuvwxyz
bacdfeghijklmnopqrstuvwxyz
nemoguce
abcdfeghijklmnopqrstuvwxyz
cbdafeghijklmnopqrstuvwxyz
nemoguce```

# 题解

## 作者：2018g20 (赞：3)

## [传送门](https://www.luogu.com.cn/problem/P11226)

## 思路

### 1.先判断这个字符能不能夺冠

这是一道与字典序有关的问题，能想到建一棵字典树。

如果一个字符串想要是字典序最小，首先没有别的串是他的前缀，然后对于剩下有共同部分前缀的其他的字符串的**所有共同前缀后的下一个字母**的优先级一定要比**这个字符串共同前缀后的下一个字母**低。

这时如果不能夺冠，那必然是出现了类似字符 A 比字符 B 优先级低，字符 B 比字符 C 优先级低，但字符 C 比字符 A 优先级低。发现总是一个环。

这样就可以通过拓扑判环来筛出不可能的情况。

### 2.在考虑如何排列字典序

因为我想让这个字符串夺冠，所以我让这个串上的字符越靠前排越好，接着把剩下没输出的字符随意输出。

## 代码


```cpp
#include<iostream>
#include<queue>
#include<bitset>
using namespace std;
int n,cnt=1,ans,sum;
int du[30],daan[30];
queue <int> q;
bitset <10000005> tail;
bitset <30> f[30];
string s[1000005];
int ch[1000005][30];
void insert(string ss)
{
	int u=1;
	for(int i=0;i<ss.size();i++)
	{
		int c=ss[i]-'a';
		if(!ch[u][c]) ch[u][c]=++cnt;
		u=ch[u][c];
	}
	tail[u]=1;
	return ;
}
bool check(string ss)
{
	while(!q.empty()) q.pop();
	int u=1;
	for(int i=0;i<26;i++)
	{
		du[i]=0;
		for(int j=0;j<26;j++) f[i][j]=0;
	}
	for(int i=0;i<ss.size();i++)
	{
		if(tail[u]) return 0;//若有前缀 
		int c=ss[i]-'a';
		for(int j=0;j<26;j++)
		{
			if(j==c) continue;
			if(ch[u][j]&&!f[c][j]) du[j]++,f[c][j]=1;//建边 
		}
		u=ch[u][c];
	}
	for(int i=0;i<26;i++) if(!du[i]) q.push(i);
	while(!q.empty())//拓扑 
	{
		int now=q.front();
		q.pop();
		daan[sum++]=now;
		for(int i=0;i<26;i++)
		{
			if(!f[now][i]) continue;
			du[i]--;
			if(!du[i]) q.push(i);
		}
	}
	for(int i=0;i<26;i++) if(du[i]) return 0;
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		insert(s[i]);
	}
	for(int i=1;i<=n;i++)
	{
		sum=0;
		if(check(s[i])) for(int i=1;i<=26;i++) putchar(daan[i]+'a');
		else printf("nemoguce");
		puts("");
	}
}
```


两倍经验 [P3065](https://www.luogu.com.cn/problem/P3065)

UPD:2025/3/16

---

## 作者：Redamancy_Lydic (赞：2)

挺好的题。

对于每一个串，我们贪心地考虑，让这个字符串中的字母字典序尽可能靠前，也就是说如果把它和其它字符串比较的话，当遇到第一个不同字母时，它这个字母的字典序应该是更靠前的。

找第一个不同字母的操作可以用 Trie 树维护，然后对每个刚刚才思路得出的字母大小关系我们可以联想到建有向边。具体的，设当前处理的字符串为 $t$，我们在 Trie 树上的遍历 $t$，对于遍历到的每一个节点如果在 Trie 上面有其它字母的分叉，那么显然需要让 $t$ 的这个字母向其它分叉的所有字母建有向边。

建完以后无解的情况显然就是图上有环，否则按照这张图的一个拓扑序输出节点即可。

还有一种情况就是 $t$ 是其它字符串的一个前缀，这时显然无解，特判即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=5e6+100;
const int mod=998244353;
const int inf=1e9+7;
int n;
string s[maxn];
int tot,tr[maxn][30];
int cnt[maxn],du[90];
vector<int> G[90];
void add(string t)
{
	int now=0;
	for(int i=0;i<t.size();i++)
	{
		int ch=t[i]-'a';
		if(!tr[now][ch])tr[now][ch]=++tot;
		now=tr[now][ch];
	}
	cnt[now]++;
}
bool ask(string t)
{
	int now=0;
	for(int i=0;i<t.size();i++)
	{
		int ch=t[i]-'a';
		if(cnt[now])return 1;
		now=tr[now][ch];
	}
	return 0;
}
void work(string t)
{
	int now=0;
	for(int i=0;i<t.size();i++)
	{
		int ch=t[i]-'a';
		for(int i=0;i<26;i++)
		{
			if(i==ch||!tr[now][i])continue;
			G[ch].push_back(i);
			du[i]++;
		}
		now=tr[now][ch];
	}
}
void topsort()
{
	queue<int> q;
	vector<char> ans;
	for(int i=0;i<26;i++)if(!du[i])q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		ans.push_back(char(u+'a'));
		for(auto y : G[u])
		{
			if(--du[y]==0)
				q.push(y);
		}	
	}
	if(ans.size()==26){for(auto i : ans)cout<<i;}
	else cout<<"nemoguce";
}
void Main(int x)
{
	for(int i=0;i<26;i++)du[i]=0,G[i].clear();
	if(ask(s[x])){puts("nemoguce");return ;}
	work(s[x]);
	topsort();
	puts("");
}
signed main()
{
#ifdef Lydic
    freopen(".in","r",stdin);
    freopen(".out","w",stdout); 
//#else
//	freopen("detect.in","r",stdin);
//	freopen("detect.out","w",stdout);
#endif
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		add(s[i]);
	}
	for(int i=1;i<=n;i++)Main(i);
	return 0;
}
```

---

## 作者：_qhbd_ (赞：1)

# 题意
给定 $n$ 个字符串，问对于每一个字符串是否有一种方式重排字典序使得该字符串字典序最小。若有，输出该字典序，否则输出 `nemoguce`。
# 思路
比较两个字符串，分为两个部分，其中一部分是最长相同前缀，很明显，这没有比较的必要，就像样例中的：
```
war
wro
```
`w` 就是这一部分，有必要的是最长相同前缀的后一位，也就是样例中的 `a` 和 `r`。若 `war` 要小于 `wro`，则 `a`$<$`r`。

因为每一位最多有 $26$ 种不同字母，所以对于字符串的一个前缀最多有 $25$ 种大小关系产生，维护这个大小关系即可。

大小关系可以看做一种单向边的关系，大的指向小的。如果有环，那边无解。如果有解无环便跑拓扑排序，根据拓扑排序的定义易知此时拓扑序就是最后的字典序了。

为了便捷地处理大小关系，我们可以使用字典树，先加入所有字符串，然后对于每个字符串在字典树上遍历它，对于每一个前缀分叉时，也就意味着有共同前缀但是不同后缀的字符串，根据上述规则建边，最后拓扑即可。

还有一种特殊情况，一个字符串是另一个字符串的前缀，那么无论如何另一个字符串都一定小于其前缀，特判处理即可。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2.5e4+5;
const int L=1e6+5;
int n;
int son[L][30],flag[L],cnt=1,num;
int din[30];
vector<int>e[30];
string s[N];
char ans[30];
inline void insert(string x,int u=1){
	for(auto c:x){
		if(!son[u][c-'a'])
			son[u][c-'a']=++cnt;
		u=son[u][c-'a'];
	}
	flag[u]++;
}
inline bool build(string x,int u=1){
	for(auto c:x){
		if(flag[u])return true;
		for(int i=0;i<26;i++)
			if(son[u][i]&&c-'a'!=i){
				din[i]++;
				e[c-'a'].emplace_back(i);
			}
		u=son[u][c-'a'];
	}
	return false;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s[i];
		insert(s[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<26;j++)e[j].clear(),din[j]=0;
		num=0;
		if(build(s[i])){
			puts("nemoguce");
			continue;
		}
		queue<int>q;
		for(int j=0;j<26;j++)
			if(!din[j])
				q.push(j);
		while(!q.empty()){
			int u=q.front();q.pop();
			ans[num++]='a'+u;
			for(auto v:e[u])
				if(--din[v]==0)
					q.push(v);
		}
		if(num==26){for(int j=0;j<26;j++)printf("%c",ans[j]);puts("");}
		else puts("nemoguce");
	}
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定 $n$ 个由小写英文字母组成的字符串 $S_i$，对于每一个字符串，判断是否可以重新钦定每个字符之间的大小关系，使得这个字符串字典序最小，若存在，输出一种合法的方案。

$1\leq n\leq 2.5\times 10^4,\sum |S_i|\leq 10^6$。

## 思路

这是 D2T3？感觉 COTS 的题目顺序不按常理出牌啊。

依次考虑每一个字符串 $S_i$。我们看看怎样钦定字符之间的大小关系可以使得这个字符串的字典序最小。

对于另一个字符串 $S_j$，设 $S_i,S_j$ 的最长公共前缀长度为 $k$，若 $k=S_j$ 那么肯定是无解了，否则在第 $k+1$ 个字符时必须让 $S_i$ 的字典序比 $S_j$ 小，可以钦定字符关系 $S_{i,k+1}<S_{j,k+1}$。这个过程可以在 Trie 上简单模拟。

最后我们需要找到每个字符之间的顺序，将关系建成有向图，跑一遍拓扑排序即可。如果图有环则代表无解。

时间复杂度 $O(\sum a_i\cdot C)$。其中 $C$ 表示字符集大小。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 2.5e4 + 5, M = 1e6 + 5;
int n, t[M][26], tot, deg[27];
bool edp[M];
string s[N];
vector<int> g[27];
void insert(string s){
    int cur = 0;
    for(char i : s){
        if(!t[cur][i - 'a']) t[cur][i - 'a'] = ++tot;
        cur = t[cur][i - 'a'];
    }
    edp[cur] = true;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> s[i]; insert(s[i]);
    }
    for(int i=1;i<=n;i++){
        int cur = 0; bool flag = 0;
        for(char ch : s[i]){
            if(edp[cur]){
                flag = 1;
                break;
            }
            for(int j=0;j<26;j++){
                if(!t[cur][j] || j == (ch - 'a')) continue;
                g[ch - 'a'].emplace_back(j); deg[j]++;
            }
            cur = t[cur][ch - 'a'];
        }
        if(flag){
            for(int i=0;i<26;i++) g[i].clear(), deg[i] = 0;
            cout << "nemoguce\n";
            continue;
        }
        queue<int> q; string s;
        for(int i=0;i<26;i++){
            if(!deg[i]) q.emplace(i);
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            s += (char)(u + 'a');
            for(int v : g[u]){
                if(!(--deg[v])) q.emplace(v);
            }
        }
        if(s.size() == 26) cout << s << '\n';
        else cout << "nemoguce\n";
        for(int i=0;i<26;i++) g[i].clear(), deg[i] = 0;
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：littlebug (赞：1)

字符做下标的时候忘记 `-'a'`，然后数组越界还不报错 qwq！% 你赛喜提挂 $100$ 分！

## Solution

一眼 trie。

对于一个字符串 $s$，假设现在遍历到了它的某个位置 $c$，那么就需要保证在同前缀的字符串中，$s$ 的「字典序」最大，也就是和 $c$ 同位置的字符的「字典序」都比 $c$ 小。

于是可以想到根据这个限制建边。

然后我们就得到了一个右向图，它的边 $(u,v)$ 表示 $u$ 的「字典序」需要 $>v$。我们发现，当且仅当这个图中有环时，不可能存在合法的构造满足所有限制，于是跑一遍拓扑看看有没有环即可。

但是这样 WA 了。

手搓样例可知，还需要判下是否存在一个字符串是当前字符串的前缀，若存在则无解，这个东西显然在 trie 上也可以实现。

时间复杂度是 $O(n |\Sigma| + L |\Sigma|)$ 状物，总之可过。

## Code

```cpp
int n;
string a[N];
vector <char> p[200];
int in[200];

struct trie
{
	struct node{int ch[26]={},siz=0;} v[L];
	int tot=1;
	
	il trie(){}
	
	il void upd(string s)
	{
		int pos=1; int c;
		for(auto ch:s)
		{
			c=ch-'a';
			if(!v[pos].ch[c]) v[pos].ch[c]=++tot;
			pos=v[pos].ch[c];
		}
		++v[pos].siz;
	}
	
	il void q(string s)
	{
		int pos=1; int c;
		for(auto ch:s)
		{
			c=ch-'a';
			rep(i,0,25) v[pos].ch[i] && i!=c && (p[c+'a'].pb(i+'a'),++in[i+'a']);
			if(v[pos].siz) return in['l']=20120712,void();
			pos=v[pos].ch[c];
		}
	}
} tr;

queue <char> q;
il string bfs()
{
	string ans="";
	
	clr(q);
	rep(i,'a','z') in[i] || (q.emplace(i),1);
	char u;
	while(!q.empty())
	{
		u=q.front(),q.pop(),ans+=u;
		for(auto v:p[u])
		{
			--in[v];
			in[v] || (q.emplace(v),1);
		}
	}
	
	return ans.size()==26 ? ans : "nemoguce";
}

signed main()
{
	read(n),_::r(a,n);
	
	string res;
	rep(i,1,n) tr.upd(a[i]);
	rep(i,1,n)
	{
		rep(j,'a','z') clr(p[j]),in[j]=0;
		tr.q(a[i]);
		write(bfs(),'\n');
	}
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Ericnoi (赞：0)

# P11226 题解

[题目传送门](https://www.luogu.com.cn/problem/P11226)

# 分析

首先这是一道和字典序有关的题。一切和“字典序”“前缀”有关的题目我们都可以考虑用字典树来处理。

考虑先把所有字符串插入到一个字典树里。然后一个个在树上计算答案。

对于每一个字符串，我们在字典树上一步步往下走。每走一步之前，根据我们“该字符串字典序为最大”的假设，我们可以得到一些信息：**该节点所代表的字符，比所有兄弟节点所代表的字符，在最终的表里排得都靠前**。

不难发现我们可以把每一条这种信息转化成一条有向边，$a$ 指向 $b$ 代表在字母表里 $a$ 比 $b$ 靠前。而最终得字母表就是这个有向无环图的**拓扑序**。

这时候代码就呼之欲出了，不过还有一个小细节要注意：如果存在字符串 $x$ 使得 $x$ 是 $y$ 的前缀，那么 $y$ 一定不可能夺冠。

# Code 
~~作者是封装仙人~~
```cpp
#include <bits/stdc++.h>
namespace aclib {
    class edge {
    public:
        int to, w;
        edge(int a = 0) : to(a), w(1) {}
        operator int() {return to;}
    };
    class graph {
        int n_, m_;
        std::vector<std::vector<int>> a_;
    public:
        void resize(int n) {n_ = n, m_ = 0, a_.resize(n + 1);}
        graph(int n = 0) {resize(n);}
        void addedge(int u, int v) {a_[u].push_back(v); m_++;}
        int getw(int u) const {return 0;}
        int getn() const {return n_;}
        int getm() const {return m_;}
        std::vector<int> operator [] (int u) const {
            return a_[u];
        }
    };
}
namespace aclib {
    std::vector<int> toposort(const graph& g) {
        int n = g.getn();
        std::vector<int> deg(n + 1);
        for(int i = 1 ; i <= n ; i++) {
            for(int v : g[i]) {
                deg[v]++;
            }
        }
        std::queue<int> q;
        for(int i = 1 ; i <= n ; i++) {
            if(deg[i] == 0) q.push(i);
        }
        std::vector<int> res;
        while(q.size()) {
            int u = q.front(); q.pop();
            res.push_back(u);
            for(int v : g[u]) {
                deg[v]--;
                if(deg[v] == 0) q.push(v);
            }
        }
        res.insert(res.begin(), 0);
        for(int i = 1 ; i <= n ; i++) {
            if(deg[i] > 0) return std::vector<int>();
        }
        return res;
    }
}
namespace aclib {
    class trie {
        using node = std::array<int, 26>;
        std::vector<node> tree_;
        std::vector<bool> end_;
        int f(char c) {
            return c - 'a';
        }
        int newnode() {
            tree_.push_back(node());
            end_.push_back(false);
            return tree_.size() - 1;
        }
        int getpos(const std::string& s, int& pos) {
            int n = s.size(), res, c;
            res = pos = 0;
            auto update_arrays = [&]() {
                end_[pos] = true;
            };
            for(int i = 0; i < n; i++) {
                c = f(s[i]);
                if(!tree_[pos][c]) {
                    int tmp = newnode();
                    tree_[pos][c] = tmp;
                }
                pos = tree_[pos][c];
            }
            update_arrays();
            return res;
        }
        std::vector<std::pair<int, int>> findpos(const std::string& s, int& pos) {
            int n = s.size(), c;
            pos = 0;
            std::vector<std::pair<int, int>> res;
            for(int i = 0 ; i < n ; i++) {
                c = f(s[i]);
                if(end_[pos]) {
                    pos = -2;
                    return res;
                }
                for(int j = 0 ; j < 26 ; j++) {
                    if(!tree_[pos][j]) continue;
                    if(j == c) continue;
                    res.push_back({c + 1, j + 1});
                }
                if(!tree_[pos][c]) {
                    pos = -1;
                    return res;
                }
                pos = tree_[pos][c];
            }
            return res;
        }
    public:
        trie() {
            newnode();
        }
        void insert(const std::string& s) {
            int pos;
            getpos(s, pos);
        }
        std::string query(const std::string& s) {
            int pos;
            std::vector<std::pair<int, int>> res = findpos(s, pos);
            if(pos == -2) return "nemoguce";
            graph g(26);
            for(std::pair<int, int> pr : res) {
                g.addedge(pr.first, pr.second);
            }
            std::vector<int> topo = toposort(g);
            if(topo.size() == 0) return "nemoguce";
            std::string ans;
            for(int i = 1 ; i <= 26 ; i++) {
                ans.push_back((char)('a' + topo[i] - 1));
            }
            return ans;
        }
    };
}
using namespace std;
using namespace aclib;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    trie tr;
    vector<string> a(n + 1);
    for(int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        tr.insert(a[i]);
    }
    for(int i = 1 ; i <= n ; i++) {
        cout << tr.query(a[i]) << endl;
    }
    return 0;
}
```

---

## 作者：729hao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11226)

目前最优解前来报道。

---

看到现有的题解都大多都建了 Trie 树，实际上并不需要，我们只需要按照类似基数排序的方式递归求解即可。（本质上和 Trie 是一样的）

具体地，考虑调用如下的函数：
```cpp
void Solve(vector<pair<string,int> > v,int nowd)
```

其中，$v$ 表示我们需要求解的字符串及其编号；$nowd$ 表示我们现在考虑按照字符串的第几位分类，即保证 $v$ 中所有字符串从 $0$ 到 $nowd-1$ 位上字符相同。

按照 $nowd$ 分好类以后，开 $26$ 个 vector 存对应的 pair。那么对于所有 $s_{nowd}=c$ 的字符串，如果它想成为字典序第一，则 $c$ 的字典序一定在其余所有出现了的字符之前，更新拓扑图后递归函数求解即可。

边界条件是 $v$ 中存在一个字符串的 $size<=nowd$，则这个字符串的解就是拓扑排序，除此之外的字符串必定无解。

时间复杂度 $O(|\Sigma|^2L)$。



---

作者语文水平太差了讲不清楚，还是看代码吧。
## code
此代码加了一点小小的剪枝，且 $solve$ 函数并非用 vector 存字符串而是共用 $O(N)$ 的数组，对应代码中的 $l$ 和 $r$。
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace cs{
    #define LL long long
    const int N=25000;
    const int INF=2e9;
    int n,adm[35][35];
    string s[N+5],real_ans[N+5];
    int t[N+5],tt[35][N+5];
    queue<int> qu;
    string Comple(){
        string rtn="";
        int d[26];
        for(int i=0;i<26;i++){
            d[i]=0;
            for(int j=0;j<26;j++){
                if(adm[j][i]) d[i]++;
            }
            if(d[i]==0){
                qu.push(i);
            }
        }
        int fr;
        while(!qu.empty()){
            fr=qu.front();
            qu.pop();
            rtn+=(char)(fr+'a');
            for(int j=0;j<26;j++){
                if(adm[fr][j]){
                    d[j]--;
                    if(d[j]==0) qu.push(j);
                }
            }
        }
        if(rtn.size()<26) return "nemoguce";
        return rtn;
    }
    void Solve(int l,int r,int nowd){
        // printf("Solve(%d %d %d)\n",l,r,nowd);
        // for(int i=l;i<=r;i++){
        //     printf("s[%d]:",i);
        //     cout<<s[t[i]]<<"\n";
        // }
        // for(int i=0;i<26;i++){
        //     for(int j=0;j<26;j++){
        //         if(adm[i][j]) printf("Link %c->%c\n",i+'a',j+'a');
        //     }
        // }
        if(l==r){
            real_ans[t[l]]=Comple();
            return;
        }
        int cnt[26],sid;
        for(int j=0;j<26;j++) cnt[j]=0;
        for(int i=l;i<=r;i++){
            if(s[t[i]].size()<=nowd){
                real_ans[t[i]]=Comple();
                for(int j=l;j<=r;j++){
                    if(j!=i) real_ans[t[j]]="nemoguce";
                }
                return;
            }
            sid=s[t[i]][nowd]-'a';
            // printf("cnt[%d]++\n",sid);
            tt[sid][++cnt[sid]]=t[i];
        }
        int pt=l-1;
        for(int j=0;j<26;j++){
            for(int i=1;i<=cnt[j];i++){
                t[++pt]=tt[j][i];
            }
        }
        pt=l;
        bool cant;
        for(int j=0;j<26;j++){
            if(cnt[j]==0) continue;
            cant=0;
            for(int k=0;k<26;k++){
                if(cnt[k]==0) continue;
                // printf("adm[%d][%d]:%d\n",k,j,adm[k][j]);
                if(adm[k][j]){
                    cant=1;
                    break;
                }
            }
            if(cant){
                for(int i=pt;i<pt+cnt[j];i++){
                    real_ans[t[i]]="nemoguce";
                }
                pt+=cnt[j];
                continue;
            }
            for(int k=0;k<26;k++){
                if(cnt[k]==0||j==k) continue;
                adm[j][k]++;
            }
            Solve(pt,pt+cnt[j]-1,nowd+1);
            for(int k=0;k<26;k++){
                if(cnt[k]==0||j==k) continue;
                adm[j][k]--;
            }
            pt+=cnt[j];
        }
    }
    int main(){
        ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>s[i];
            t[i]=i;
        }
        Solve(1,n,0);
        for(int i=1;i<=n;i++){
            cout<<real_ans[i]<<"\n";
        }
        return 0;
    }
}
int main(){
    cs::main();
    return 0;
}
```

---

## 作者：zwxadz (赞：0)

这道题非常的有意思，~~硬控了我好久。~~

我的做法：字典树 trie。

主要是做的时候有点蠢，一直都没往字典树上想，导致写了很久。但其实只要想到了字典树，这道题还是比较简单的。

我们先看数据范围，$n\le25000$，$L\le1000000$。这个数据范围还是挺大的。

# 非正解（暴力拓扑）

一个字符串的字典序比另一个字符串小，就只需要比较从前往后第一个不同的字符。一个字符串的字典序要比其他字符串都要小，只需一个一个比较，找到所有的第一个不同的字符，然后加一个限制，使得此字符串的字符更大。

假设最小的字符串为 $s_{i}$，正在比较的字符串为 $s_{j}$，第一个不同的位是 $k$，那么只需要让 $s_{i,k}$ 在答案序列中在 $s_{j,k}$ 前即可。这显然是一种拓扑序，直接拓扑求答案即可。如果有环，说明环内的字符自己要在自己前，显然不对，无解。

那么这样的时间复杂度就是 $O(nL)$，实测有 $45$ 分。

Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
string s[25005];
int n;
int g[25005][30][30];
int in[25005][30];
vector<int>num;
int solve(int x,int y)
{
	int l=0,r=min(s[x].length(),s[y].length());
	for(;l<=r;l++)
	{
		if(l==r)break;
		if(s[x][l]!=s[y][l])break;
	}//寻找第一个不同的字符
	if(l==s[y].length())
	{
		return -1;
	}//s[y]是s[x]的前缀
	if(l==s[x].length())return 0;//s[x]是s[y]的前缀
	g[x][s[x][l]-'a'+1][s[y][l]-'a'+1]++;//连边
	in[x][s[y][l]-'a'+1]++;//加入度
	return 0;
}
bool check(int x)
{
	num.clear();
	queue<int>q;
	int cnt=0;
	for(int i=1;i<=26;i++)if(!in[x][i])q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		num.push_back(u);//记录顺序
		q.pop();
		cnt++;
		for(int v=1;v<=26;v++)if(g[x][u][v])if(!(in[x][v]-=g[x][u][v]))q.push(v);//我的做法不是很好，可能有重边，所以才这么写
	}
	return cnt==26;//cnt=26则无环
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)
	{
		bool flag=0;
		for(int j=1;j<=n;j++)
		{
			if(i==j)continue;
			if(solve(i,j)==-1)//s[j]为s[i]的前缀，则s[i]不可能获胜
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			cout<<"nemoguce\n";
			continue;
		}
		if(check(i))
		{
			for(int i=0;i<26;i++)cout<<char(num[i]+'a'-1);//输出答案
			cout<<"\n";
		}
		else cout<<"nemoguce\n";//有环，无解
	}
	return 0;
}
```
## 我未写出来的不一定能通过的做法（哈希 + 二分）

可以考虑优化它。我刚开始想的是优化比较的部分，用哈希 + 二分求得第一个不同的地方，但考虑到需要的空间有点大（但其实可以开 vector 来做），所以没有写。时间复杂度为 $O( \text{玄学} )$，与数据有关（比较时所消耗的时间是不确定的），大概率是过不了的，很可能被卡。

# 正解（字典树）

受到前面想法的启发，我们重要的是看与 $s_{i}$ 在第 $k$ 位第一次产生不同的字符串的对应的字符有哪些。我们要保证在 $k-1$ 之前的前缀都相同。那么我们就可以考虑到字典树，它在往下查询的过程中，到了节点 $p$，$p$ 的子树对应的字符串都与 $s_{i}$ 在此时前缀相同。所以我们只需要再看是否 $p$ 有没有其他的，不等于 $s_{i,k}$ 的边，如果有，则让 $s_{i,k}$ 向此字符连边，最后一样使用拓扑排序即可。时间复杂度：$O(L)$。

Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
string s[25005];
int n;
int ch[1000005][30],cnt=1;//数组开到字符串总长
int g[25005][30][30],in[25005][30];
bitset<1000005>en;
vector<int>num;
void insert(int x)
{
	int p=1;
	for(int i=0;i<s[x].length();i++)
	{
		int k=s[x][i]-'a'+1;
		if(!ch[p][k])ch[p][k]=++cnt;
		p=ch[p][k];
	}
	en[p]=1;//有字符串在此处结束
}//插入字符串
int query(int x)
{
	int p=1;
	for(int i=0;i<s[x].length();i++)
	{
		int k=s[x][i]-'a'+1;
		for(int j=1;j<=26;j++)if(j!=k&&ch[p][j])//有不同的字符
		{
			g[x][k][j]++,in[x][j]++;//建边
		}
		if(en[p])return -1;//经过了一个字符串的结尾，说明有字符串是该字符串的前缀，无解
		p=ch[p][k];
	}
	return 0;//刚开始忘写了，直接RE了
}
bool check(int x)
{
	num.clear();
	queue<int>q;
	int cnt=0;
	for(int i=1;i<=26;i++)if(!in[x][i])q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		num.push_back(u);
		q.pop();
		cnt++;
		for(int v=1;v<=26;v++)if(g[x][u][v])if(!(in[x][v]-=g[x][u][v]))q.push(v);
	}
	return cnt==26;
}//一样的代码
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){cin>>s[i];insert(i);}
	for(int i=1;i<=n;i++)
	{
		int res=query(i);
		if(res==-1)//有前缀，无解
		{
			cout<<"nemoguce\n";
			continue;
		}
		if(check(i))
		{
			for(int i=0;i<26;i++)cout<<char(num[i]+'a'-1);//欢乐的输出答案
			cout<<"\n";
		}
		else cout<<"nemoguce\n";//一样的代码
	}
	return 0;
}
```

最后，祝各位一个月后的 NOIP 顺利。~~虽然考 NOIP 的应该都不会来做这题吧。~~

---

