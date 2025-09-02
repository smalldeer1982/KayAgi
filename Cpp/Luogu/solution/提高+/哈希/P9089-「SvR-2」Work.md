# 「SvR-2」Work

## 题目背景

 

## 题目描述

给定 $n$ 个**由小写字母组成**的字符串，定义第 $i$ 个字符串的价值为其有意义的子串的数量（**如果有多个本质相同的子串也统计多次**），第 $i$ 个字符串的一个子串有意义，当且仅当这个子串能被分成若干个串，其中每个串都是这 $n$ 个字符串中任意一个字符串的任意一个后缀。

这里有一个 $n=4$ 的例子：
```plain
int
printf
scanf
ntnt
```

- 对于 `printf` 这个字符串而言，`intf` 是有意义的，因为可以表示成 `int` 和 `f` ，分别是 `int` 和 `scanf` 的后缀，而 `rint` 则不是。

- 对于 `ntnt` 这个字符串而言，`ntnt` 也是有意义的，因为可以表示成 `nt` 和 `nt`，它们都是 `int` 同一个后缀，或者可以表示成 `ntnt`，是 `ntnt` 的一个后缀。

现在，小 Z 想知道这 $n$ 个字符串价值之和。

## 说明/提示

#### 数据规模与约定

**本题开启捆绑测试和 O2 优化。**

令 $s_i$ 表示第 $i$ 个字符串长度。
| Subtask | 数据范围/特殊性质 | 分值 |
| :------: | :------: | :------: |
| $1$ |  $n\le 3$，$\sum\limits \lvert s_i\rvert\le10$| $5 \operatorname{pts}$ |
| $2$ | $n=26$，每种字符串均由一种字符组成 | $5 \operatorname{pts}$ |
| $3$ |$n=1$ | $15 \operatorname{pts}$ |
| $4$ | $\sum\limits \lvert s_i \rvert \le 2000$ | $15 \operatorname{pts}$ |
| $5$ | $\sum\limits \lvert s_i \rvert \le 2\times10^5$ | $30 \operatorname{pts}$ |
| $6$ | $\sum\limits \lvert s_i \rvert \le 10^6$ | $30 \operatorname{pts}$ |

对于 $100\%$ 的数据，$1\le n \le 5\times10^5$，$n\le \sum\limits \lvert s_i \rvert \le 10^6$。

## 样例 #1

### 输入

```
4
int
printf
scanf
ntnt```

### 输出

```
23```

## 样例 #2

### 输入

```
4
ireallywanttobemissjiaransdog
butmissjiaransaidthatshelikedcatsandicried
iknowwhyicrywheniamneitheradognoracatbecauseimactuallyamouse
ineverexpectedmissjiarantolikeherselfiunderstandthatallpeopleliketounderstandthecutedogorcatthatyuyuusestomakemoneyandnoonelikesthemousewithwetandwetdiseases```

### 输出

```
391```

# 题解

## 作者：do_while_true (赞：6)

来个时间复杂度真的线性的做法。

前面的部分和题解区那个 AC 自动机做法相同。先都 reverse 一下，找下充分条件，一个串 $S$ 合法当且仅当它的所有前缀都存在一个后缀在 Trie 里面出现过。必要性构造就是每次删掉当前这个前缀的最短的后缀。

然后考虑根据这个必要性的构造划分等价类来 dp。

首先 $g_u$ 表示 $u$ 节点代表字符串在 Trie 中出现过的最短后缀，当 $fail_u$ 存在时 $g_u\gets g_{fail[u]}$，否则 $g_u$ 没有真后缀，那么这个最短后缀就是它自己。

然后 $f_i$ 表示当前这个串以 $s_i$ 为结尾的后缀有多少个是合法的，首先 $s[:i]$ 是合法的，然后删掉它看它前面能接上几个，就是 $f_{i-g[u]}$，这里 $u$ 是 $s[:i]$ 在 Trie 中代表的节点。

注意到这里并不需要求出 AC 自动机的转移边，仅需要 Trie 边以及 fail 树。所以这样构建：

> 考虑 $x$ 是由 Trie 中的父亲 $fa$ 通过 $c$ 转移边得到的。那么检索 $y=fail_{fa}$，若 $y$ 存在字符 $c$ 的转移边，则令 $x$ 指向 $tr_{y,c}$；否则，令 $y\gets fail_y$ 即不断跳 fail 检查是否有 $c$ 出边。若到了初始节点（Trie 的根节点）依然没有 $c$ 出边，则令 $fail_x$ 指向初始节点。

对于每个串在 Trie 中自顶向下考虑尝试寻找 fail 的 $y$ 在最终 fail 树中的深度变化，每次向下走一个儿子 $y$ 深度最多 $+1$，每次暴力跳 fail 深度都会 $-1$，均摊下来总的时间复杂度就是 $\mathcal{O}(\sum |s|)$．

所以总的时间复杂度是 $\mathcal{O}(\sum |s|)$，并不会乘上一个字符集大小。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef pair<int,int> pii;
const int N=1000010;
int n;
int tr[N][26],fa[N],fail[N],dep[N],g[N],tot;
int head[N],ent;
struct Edge{
	int nxt,to,col;
}e[N];
int f[N];
void add(int x,int y,int c){
	tr[x][c]=y;fa[y]=x;dep[y]=dep[x]+1;
	e[++ent]={head[x],y,c};head[x]=ent;
}
void Ins(string &s){
	int u=0,l=s.size();
	for(int i=0;i<l;i++){
		if(!tr[u][s[i]-'a'])add(u,++tot,s[i]-'a');
		u=tr[u][s[i]-'a'];
	}
}
void build(){
	queue<pii>q;
	for(int i=0;i<26;i++)if(tr[0][i])q.push(mp(tr[0][i],i));
	while(!q.empty()){
		int u=q.front().fi,c=q.front().se;q.pop();
		int x=fail[fa[u]];
		while(x&&!tr[x][c])x=fail[x];
		if(x!=fa[u])fail[u]=tr[x][c];
		g[u]=fail[u]?g[fail[u]]:dep[u];
		for(int i=head[u];i;i=e[i].nxt)q.push(mp(e[i].to,e[i].col));
	}
}
string s[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> s[i];
		reverse(s[i].begin(),s[i].end());
		Ins(s[i]);
	}
	build();
	long long ans=0;
	for(int o=1;o<=n;o++){
		int m=s[o].size(),u=0;f[0]=0;
		for(int i=0;i<m;i++){
			u=tr[u][s[o][i]-'a'];
			f[i]=f[i-g[u]]+1;
			ans+=f[i];
		}
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Mikefeng (赞：5)

# P9089「SvR-2」Work

## 题目描述

给定 $n$ 个**由小写字母组成**的字符串，定义第 $i$ 个字符串的价值为其有意义的子串的数量（**如果有多个本质相同的子串也统计多次**），第 $i$ 个字符串的一个子串有意义，当且仅当这个子串能被分成若干个串，其中每个串都是这 $n$ 个字符串中任意一个字符串的任意一个后缀。

求这 $n$ 个字符串价值之和。

## 做法

这里由没打比赛人给出官方题解不屑于给出的 SAM 做法，这里默认大家会广义 SAM。

此外下文中复杂度的 $n$ 即表示 $\sum|s_i|$。

先手玩一下样例，发现答案大致与每一个位置 $i$ 最多向前延伸的合法串长度 $f_i$ 有关。详细研究一下，可以利用单调栈+二分实现找到以 $i$ 为末尾向前拼出的最长合法串，并且由于后缀的连续性，$i$ 对答案的贡献就是 $f_i$，复杂度 $O(n\log n)$。

考虑如何找到 $f_i$。

笔者本来想用 hash+unordered_map 实现，复杂度 $O(n\log n)$，但是常数太大，跑不过去，只好上科技。

我们知道，如果在一个等价类为 $pos_i$ 的子串前删一个字符，那么新子串的等价类一定是 $pos_i$ 或 $pos_{fa_i}$，那么找字符串的所有后缀子串的等价类并打上标记可以暴力跳 $fa_i$ 实现，时间复杂度 $O(n)$。

由上述性质也可知，对于以 $i$ 为结尾的子串的等价类在 SAM 的 parent 树上形成了一条从 $1$ 到 $pos_i$ 的链。

于是找到 $f_i$ 就变成了找到 $1$ 到 $pos_i$ 这条链上深度最大的有标记的点 $j$，$f_i$ 即为 $len_j$，可以离线 $dfs$ 实现，复杂度 $O(n)$。

总复杂度 $O(26n+n\log n)$，不过因为 SAM 跑得满（以及个人常数原因），只能勉强通过。

属于一道理解 SAM 的 parent 树的性质的好题。

## 代码

```cpp
const int N=1e6+5;
ll ans;
int n,t;
string s[N];
int st[N],len[N];
vector<int> a[N],l[N];
struct Trie{
	int cnt=1;
	int to[N][26],fa[N];
	inline void add(string s,int n){
		int u=1;
		F(i,1,n){
			int k=s[i]-'a';
			if(!to[u][k]){
				to[u][k]=++cnt;
				fa[cnt]=u;
			}
			u=to[u][k];
		}
	}
}T;
struct SAM{
	int cnt=1;
	int tr[N<<1][26],fa[N<<1],len[N<<1],pos[N<<1];
	inline int add(int c,int lst){
		int p=lst,u=++cnt;
		len[u]=len[p]+1;
		for(;p&&!tr[p][c];p=fa[p]) tr[p][c]=u;
		if(!p) fa[u]=1;
		else{
			int q=tr[p][c];
			if(len[q]==len[p]+1) fa[u]=q;
			else{
				int s=++cnt;
				fa[s]=fa[q];
				fa[q]=fa[u]=s;
				len[s]=len[p]+1;
				F(i,0,25) tr[s][i]=tr[q][i];
				for(;p&&tr[p][c]==q;p=fa[p]) tr[p][c]=s;
			}
		}
		return u;
	}
	queue<pii> q;
	inline void build(){
		F(i,0,25) if(T.to[1][i]) q.push({T.to[1][i],i});
		pos[1]=1;
		while(!q.empty()){
			pii tmp=q.front();q.pop();
			int u=tmp.fi,c=tmp.se;
			pos[u]=add(c,pos[T.fa[u]]);
			F(i,0,25) if(T.to[u][i]) q.push({T.to[u][i],i});
		}
	}
}S;
struct parent_tree{
	vector<int> e[N<<1];
	vector<pii> q[N<<1];
	bool vis[N<<1];
	inline void build(){
		F(i,1,S.cnt) e[S.fa[i]].push_back(i);
	}
	inline void dfs(int u,int topf){
		if(vis[u]) topf=u;
		for(pii x:q[u]) a[x.fi][x.se]=S.len[topf];
		for(int v:e[u]) dfs(v,topf);
	}
}P;
inline int get_id(string s,int id){
	int p=1,n=len[id];
	F(i,1,n){
		int k=s[i]-'a';
		p=S.tr[p][k];
		P.q[p].emplace_back(id,i);
	}
	return p;
}
int main(){
	n=read();
	F(i,1,n){
		cin>>s[i];
		len[i]=s[i].size();
		a[i].resize(len[i]+5);
		l[i].resize(len[i]+5);
		s[i]=" "+s[i];
		T.add(s[i],len[i]);
	}
	S.build();
	P.build();
	F(i,1,n){
		int p=get_id(s[i],i);
		while(p){
			P.vis[p]=1;
			p=S.fa[p];
		}
	}
	P.dfs(1,0);
	F(i,1,n){
		st[t=1]=0;
		l[i][0]=1;
		F(j,1,len[i]){
//			cout<<a[i][j]<<" ";
			l[i][j]=j+1;
			if(a[i][j]){
				int k=lower_bound(st+1,st+t+1,j-a[i][j])-st;
				l[i][j]=l[i][st[k]];
				ans+=j-l[i][j]+1;
			}
			while(t&&l[i][st[t]]>=l[i][j]) t--;
			st[++t]=j;
		}
//		puts("");
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Alarm5854 (赞：4)

这道题目显然与字符串相关，而处理一段子串与所有的后缀库中是否有匹配的最简便方式就是哈希。因此，一个做法就是先把所有的后缀的哈希值都丢进一个集合里面，然后枚举子串尝试去和集合里面的哈希值匹配，但是，这样做，复杂度是 $O((\sum |s_i|^2)\log(\sum|s_i|))$ 的，复杂度过高。

然而，真的有必要枚举所有的子串吗？其实没必要，原因在于假设一个非空字符串 $\texttt{A}$ 是不满足条件的，那么字符串 $\texttt{cA}$ 也是不满足条件的（$\texttt{c}$ 为任意字符）。这很好理解，假设 $\texttt{cA}$ 满足条件了，那么去掉前面的那个字符，更容易匹配上。而且，还有一个性质就是对于两个均满足条件的字符串 $\texttt{A}$ 和 $\texttt{B}$，那么加上一个字符 $\texttt{c}$ 以后，只要长度较小的字符串满足条件，那么长度较大的那个字符串一定满足条件。因此，我们可以得到这样的做法：对于每个字符串，维护一个栈表示右端点，从最后一个字符开始枚举，如果加上这一字符后，栈顶的字符串不再满足条件，那么就可以将其踢出，直到栈空或栈顶的字符串满足条件。这样，时间复杂度可以优化至 $O((\sum |s_i|)\log(\sum |s_i|))$。瓶颈在于把后缀插入集合。若你真想把这个 $\log$ 去掉，可以再用一个挂链哈希优化，代码长度只有官方题解的约 $70\%$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=5e5+7;
const ll B=1327;
const ll X=1321321327;//建议双哈希，否则容易寄（字符串个数约为10^6）
const ll Y=1431431437;//同时建议用生僻一点的模数，否则被针对
ll px[N*2],py[N*2];
void init(){//初始化两种模数
	px[0]=py[0]=1;
	for(ll i=1;i<=1e6;++i){
		px[i]=px[i-1]*B%X;
		py[i]=py[i-1]*B%Y;
	}
}
struct H{//双哈希
	ll l,x,y;
	H(ll l=0,ll x=0,ll y=0):l(l),x(x),y(y){}
	friend H operator +(H a,char c){//插入字符
		return H(a.l+1,(a.x*B+c)%X,(a.y*B+c)%Y);
	}
	friend H operator -(H a,H b){//区间哈希
		return H(a.l-b.l,(a.x-b.x*px[a.l-b.l]%X+X)%X,(a.y-b.y*py[a.l-b.l]%Y+Y)%Y);
	}
	friend bool operator <(H a,H b){
		if(a.x^b.x)
			return a.x<b.x;
		return a.y<b.y;
	}
};
ll n,tp,res;
char s[N*2];
string str[N];
set<H>st[N*2];
H stk[N*2];
int main(){
	init();
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i){
		scanf("%s",s);
		str[i]=s;
	}
	for(ll i=1;i<=n;++i){
		ll pos=str[i].length();
		H cur;//初始默认为空串
		while(pos){//倒序枚举
			--pos;
			cur=cur+str[i][pos];
			st[cur.l].insert(cur);
		}
	}
	for(ll i=1;i<=n;++i){
		while(tp)
			stk[tp--]=H();
		ll pos=str[i].length();
		H cur;
		tp=1;//注意初始需要加入一个空串
		while(pos){
			--pos;
			cur=cur+str[i][pos];
			while(tp&&!st[cur.l-stk[tp].l].count(cur-stk[tp]))//不满足条件，出栈
				stk[tp--]=H();
			res+=tp;
			stk[++tp]=cur;//无论如何都要入栈一次
		}
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：4)

验题人做法。

首先容易发现，以每个位置为结尾的所有有意义的子串，它们的开头一定是连续的一段，这样只需要求出最小的可行开头即可。之后考虑设 $f_{i,j}$ 表示最小的 $k$，满足 $S_{i,k}S_{i,k+1}...S_{i,j-1}S_{i,j}$ 是这 $n$ 个字符串中任意一个字符串的任意一个后缀，$g_{i,j}$ 表示第 $i$ 个字符串以 $j$ 为结尾的最长的有价值的段的开头，不难发现，$g_{i,j}=\min(f_{i,j},\min\limits_{k=f_{i,j}-1}^{j-1}g_{i,k})$，所以可以在 SAM 上跑匹配求出 $f$，再利用并查集维护 $g$，即可通过本题。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Wilson_Inversion {
void main();
}
int main() {
	Wilson_Inversion::main();
	return 0;
}
namespace Wilson_Inversion {
constexpr int N(1000010);
int n, ld[N], rd[N], tot1(1), tot2(1), f[N], lp[N];
long long ans;
char s[N];
vector<int> e[N << 1];
struct TrieNode {
	int son[26], p, ed;
} trie[N];
struct SamNode {
	int son[26], len, ed, fa;
} sam[N << 1];
void insert(int l, int r) {
	int now(1);
	for (int i(l); i <= r; ++i) {
		int op(s[i] - 'a');
		if (!trie[now].son[op]) trie[now].son[op] = ++tot1;
		now = trie[now].son[op];
	}
	trie[now].ed = max(trie[now].ed, r - l + 1);
}
void ins(int op, int &np, int p, int ed) {
	np = ++tot2, sam[np].len = sam[p].len + 1, sam[np].ed = ed;
	while (p && (!sam[p].son[op])) sam[p].son[op] = np, p = sam[p].fa;
	if (!p)
		sam[np].fa = 1;
	else {
		int q(sam[p].son[op]);
		if (sam[q].len == sam[p].len + 1)
			sam[np].fa = q;
		else {
			int nq(++tot2);
			memcpy(sam[nq].son, sam[q].son, sizeof(sam[q].son)),
				sam[nq].fa = sam[q].fa, sam[nq].len = sam[p].len + 1,
				sam[q].fa = sam[np].fa = nq;
			while (p && sam[p].son[op] == q) sam[p].son[op] = nq, p = sam[p].fa;
		}
	}
}
void build() {
	queue<int> q;
	q.push(1), trie[1].p = 1;
	while (!q.empty()) {
		int u(q.front());
		q.pop();
		for (int i(0); i < 26; ++i)
			if (trie[u].son[i]) {
				q.push(trie[u].son[i]), ins(i, trie[trie[u].son[i]].p,
											trie[u].p, trie[trie[u].son[i]].ed);
			}
	}
	for (int i(2); i <= tot2; ++i) e[sam[i].fa].emplace_back(i);
}
void dfs(int x) {
	for (auto i : e[x]) {
		dfs(i);
		if (sam[i].ed) sam[x].ed = sam[x].len;
	}
}
void dfs2(int x) {
	sam[x].ed = max(sam[x].ed, sam[sam[x].fa].ed);
	for (auto i : e[x]) dfs2(i);
}
int find(int x) { return ((f[x] == x) ? x : (f[x] = find(f[x]))); }
void match(int l, int r) {
	int now(1), len(0);
	for (int i(l); i <= r; ++i) {
		int op(s[i] - 'a');
		while (now && (!sam[now].son[op]))
			now = sam[now].fa, len = sam[now].len;
		if (!now)
			now = 1;
		else
			now = sam[now].son[op], ++len;
		int t(min(len, sam[now].ed));
		if (!t) continue;
		int ls(i - t + 1);
		if (lp[find(ls - 1)])
			lp[i] = lp[find(ls - 1)];
		else
			lp[i] = ls;
		for (int j(find(ls - 1)); j < i; j = find(j + 1)) f[j] = j + 1;
		ans += i - lp[i] + 1;
	}
}
void main() {
	scanf("%d", &n);
	for (int i(1); i <= n; ++i) {
		scanf("%s", s + rd[i - 1] + 1);
		int len(strlen(s + rd[i - 1] + 1));
		ld[i] = rd[i - 1] + 1, rd[i] = rd[i - 1] + len;
		insert(ld[i], rd[i]);
	}
	build();
	dfs(1);
	dfs2(1);
	for (int i(1); i <= rd[n]; ++i) f[i] = i;
	f[rd[n] + 1] = rd[n] + 1;
	for (int i(1); i <= n; ++i) match(ld[i], rd[i]), lp[rd[i]] = 0;
	printf("%lld\n", ans);
}
}
```


---

## 作者：why_cb (赞：3)

题外话：一开始看错题目了理解成至少两个，在坑老师的帮助下才会做的。

在此膜拜 @tianhangj。

---

这里是 SAM 严格 $O(n)$ 做法 ~~（虽然被 nlogn 薄纱）~~。

首先现将问题分成：

- 子串中所有与后缀相同的数量。

- 考虑将子串合并。

---

考虑问题一，

看到后缀，容易联想到将所有文本串建一颗后缀自动机，

**因为一个子串可以被表示，它的后缀也必然可以，贡献就是子串的长度**。

此时我们统计出以每个串的每个字符为结束符最长的可以被表示的子串长。

先进行字符串匹配在 SAM 上找到以当前字符为结束的最长子串，

再从当前节点往后缀连上跳，直到跳到一个节点所表示的子串是一个后缀，此时最大的长度即为所求（预处理或者记忆化可以做到严格 $O(n)$ ，不过暴力也差不多，感觉很难卡）。

- 关于如何标记所有的后缀：类似 SAM 统计个数一样，将每个串的最后一个字符所代表的节点打上标记，那么它的后缀连往上的节点均为后缀。

---

此时我们对每个字符串都得到了一个 $pre$ 数组，接下来考虑问题二，

基于之前得出的结论，我们现在要用 $pre$ 数组求出以每个字符为结束符的符合条件的最长子串，它们的长度和便是答案。

我们可以用单调栈 $O(n)$ 求解（再次%%%@tianhangj）。

从左到右遍历 $pre$ 数组，

如果以当前位置为结束符的最长子串可以覆盖栈顶的结束符位置，

那么它可以与栈顶相拼接，也就是它比栈顶更优，把栈顶弹出，更新当前点的 $pre$ 直到不能再与栈顶拼接，将当前位置加入栈中，此时栈中必然满足单调性。

所有 $pre$ 之和便是答案。

---
Code：
```cpp
#include<algorithm>
#include<math.h>
#include<string.h>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<iostream>
using namespace std;

#define fi first
#define se second
#define pb push_back
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
typedef pair<ll,ll> pll;
const int N=1e6+86,M=5e5+86;

ll ans,pre[N];

struct SAM
{
	struct edge{int to,nxt;}e[N<<1];
	int head[N<<1],tot;
	void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
	struct node
	{
		int len,link,val,ch[26];
        bool f;
		void init()
		{
			len=link=f=val=0;
			memset(ch,0,sizeof(ch));
		}
	}atm[N<<1];
	int siz,last;
	void init()
	{
		memset(head,0,sizeof(head));
		tot=siz=last=0;
		atm[0].init();
		atm[0].link=-1;
	}
	void insert(int x,bool f)
	{
		int now=++siz;
		atm[now].init();
		atm[now].len=atm[last].len+1;
        atm[now].f=f;//标记每个串最后一个字符
		int p=last;
		while(p!=-1&&!atm[p].ch[x])
			atm[p].ch[x]=now,p=atm[p].link;
		if(p==-1) atm[now].link=0;
		else
		{
			int q=atm[p].ch[x];
			if(atm[q].len==atm[p].len+1)
				atm[now].link=q;
			else
			{
				int tmp=++siz;
				atm[tmp].init();
				atm[tmp]=atm[q];
				atm[tmp].len=atm[p].len+1;
				while(p!=-1&&atm[p].ch[x]==q)
					atm[p].ch[x]=tmp,p=atm[p].link;
				atm[q].link=atm[now].link=tmp;
			}
		}
		last=now;
	}
	void dfs1(int u)
	{
		for(int i=head[u];i;i=e[i].nxt)
			dfs1(e[i].to),atm[u].f|=atm[e[i].to].f;//将包含最后一个字符的所有子串（即后缀）的结点进行标记
	}
	void dfs2(int u,int len)//将每个结点向上跳到达的第一个后缀的长度预处理
	{
		if(atm[u].f) len=atm[u].len;
		atm[u].val=len;
		for(int i=head[u];i;i=e[i].nxt)
			dfs2(e[i].to,len);
	}
	void calc()
	{
		for(int i=1;i<=siz;i++)
			add(atm[i].link,i);
		dfs1(0);
		dfs2(0,0);
	}
    void solve(string s)
	{
		memset(pre,0,s.size()<<2);
		int now=0;
		for(int i=0;i<s.size();i++)
		{
			while(now&&atm[now].ch[s[i]-'a']==0)//先找到当前字符为结束符的最大子串的结点
				now=atm[now].link;
			if(atm[now].ch[s[i]-'a'])
			{
				now=atm[now].ch[s[i]-'a'];
				pre[i]=atm[now].val;
			}
		}
		stack<int> stk;//单调栈
		for(int i=0;i<s.size();i++)
		{
			while(!stk.empty()&&i-pre[i]<=stk.top()) 
				pre[i]=max(pre[i],i-stk.top()+pre[stk.top()]),stk.pop();
			ans+=pre[i];
			stk.push(i);
		}
	}
}sam;

string s[M];
int n,len;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
    sam.init();
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
        sam.last=0;//伪广义SAM
        for(int j=0;j<s[i].size();j++)
            sam.insert(s[i][j]-'a',j==(s[i].size()-1));
    }
    sam.calc();
    for(int i=1;i<=n;i++)
		sam.solve(s[i]);
    cout<<ans<<endl;
	return 0;
}
```

---

## 作者：FISHER_ (赞：3)

基于 AC 自动机的线性解法。

把所有串都反过来，这样一个串有意义当且仅当它可以分解成若干个前缀。

定义一个串的匹配是它的一个后缀与某个 $s_i$ 的前缀相同，这个后缀就是它的一个匹配。

考虑一个串 $S$ 有意义的充分条件是 $S$ 的每一个前缀都有匹配。容易发现这也是必要条件。

由此给出一个验证一个串是否有意义的方法：选择 $S$ 的一个匹配，删掉它，重复这个过程。如果删光了就是有意义的。

现在给你一个字符串 $S$，问你 $S$ 有几个后缀有意义。沿用刚才的办法，贪心地每次删掉一个最短的匹配，直到删光或者不存在匹配，容易发现删除次数就是所求。

对于每一个串的每一个前缀，都要求出答案，考虑简单 DP： 
$$f_i=\left\{
\begin{matrix}
0 & \text{MinMatching}(i)=0\\
f_{i-\text{MinMatching}(i)}+1 & \text{else}
\end{matrix}
\right.$$

其中 $\text{MinMatching}(i)$ 是 $S$ 长度为 $i$ 的前缀的最短匹配。

最短匹配可以用 AC 自动机来求。至此我们得到了一个 $O(|\Sigma|\sum |s_i|)$ 的解法。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 500000, maxs = 1000000;
string s[maxn + 5];
int pcnt;
int nxt[maxs + 5][26];
int len[maxs + 5];
int fail[maxs + 5], mf[maxs + 5];
int insert(const string& str) {
	int n = str.size(), p = 0;
	for (int i = 0; i < n; i++) {
		int c = str[i] - 'a';
		if (!nxt[p][c]) nxt[p][c] = ++pcnt;
		len[p = nxt[p][c]] = i + 1;
	}
	return p;
}
void build() {
	queue<int> q;
	for (int i = 0; i < 26; i++)
		if (nxt[0][i]) q.push(nxt[0][i]);
	while (q.size()) {
		int u = q.front();
		q.pop();
		mf[u] = fail[u] ? mf[fail[u]] : len[u];
		for (int i = 0; i < 26; i++) {
			if (nxt[u][i]) {
				fail[nxt[u][i]] = nxt[fail[u]][i];
				q.push(nxt[u][i]);
			} else nxt[u][i] = nxt[fail[u]][i];
		}
	}
}
int f[maxs + 5];
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		reverse(s[i].begin(), s[i].end());
		insert(s[i]);
	}
	build();
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		int m = s[i].size(), p = 0;
		fill(f, f + m + 1, 0);
		for (int j = 0; j < m; j++) {
			int c = s[i][j] - 'a';
			p = nxt[p][c];
			if (mf[p]) f[j + 1] = f[j - mf[p] + 1] + 1;
			ans += f[j + 1];
		}
	}
	printf("%lld", ans);
}
```

---

## 作者：cryozwq (赞：3)

官方题解。


### subtask1

暴力即可。

### subtask2

显然所有字符串都可以表示出来。

### subtask3

$n=1$
 
留给一些贪心。 
 
### subtask4，5


下文未说明均是对于每个串分别考虑答案。

注意到对于每个 $i$ 可以预处理 $f_i$ 表示 $S_{f_i...i}$ 是以 $i$ 为右端点中最长的一个可以被表示为其中一个后缀的，则左端点在 $[f_i,i]$ 之间的子串均可以表示为其中一个后缀。也就是说，$f_i$ 具有单调性。

因此可以二分 $f_i$，存下每个后缀的哈希值，看是否跟有 $[f_i,i]$ 相同哈希值的，根据 check 复杂度在 $O(|S|^2)$ 到 $O(|S| \log |S|)$ 不等，如果想要通过本题全部测试点，可以使用 `map` 判断，复杂度 $O(|S| \log^2 |S|)$。

考虑如何不重的 dp，一种办法是，对 $f_i$ 进行一点微妙的改动，在一遍求 $f_i$ 后，如果存在 $j<i,f_j \le f_i$ 就把 $f_i$ 改变为 $j+1$，就是说再往后可以拿 $j$ 去替代 $i$。这样一来，记 $ans_i$ 表示以 $i$ 结尾的有价值子串数量，有 $ans_i=ans_{f_i-1}+(i-f_i+1)$。

通过一些简单的数据结构技巧，可以在一个 $\log$ 的复杂度内完成一个 $f_i$ 的更新，所以不影响复杂度。

### subtask 6

如果你会 SAM，SA 之类的后缀数据结构，可以直接做到 $c \sum |S|+\sum |S| \log \sum |S|$ ，$c$ 为字符集大小。~~但是超纲了。~~

考虑 $f_i$ 变化之后的性质，我们相当于去除了所有 $[f_i,i]$ 相交的部分，因此有任意两个 $[f_i,i]$ 不交或包含。据此提出一个更快的算法
：

从左往右考虑，维护当前没有被覆盖的 $[f_i,i]$ ，假设当前考虑到一个 $i$，往前扫未覆盖的连续段，因为不存在相交，所以只有目前的 $[f_i,i]$ 覆盖原来的或者停在某个地方不动，中间未被覆盖的可以暴力往前扫，具体可以参考代码实现。

分析复杂度，每个连续段只会被删一次，每个未被覆盖的地方也只会被扫一次，瓶颈在于查询一个子串，所以复杂度为 $O(\sum |S|\log |S|)$。当然 std 通过挂链哈希能做到线性，不过不在本题考察范围之内。

---

## 作者：Demeanor_Roy (赞：2)

- [原题链接](https://www.luogu.com.cn/problem/P9089)。

- 似乎我的做法是目前最好想好写的？并且严格线性。


------------

首先考虑到后缀不是那么美观，我们将所有字符串翻转。某个子串合法的条件变为可以拆分成若干个前缀。

由于是合法子串计数，我们不难想到经典计数套路：对于某个字符串 $s$，令 $f_i$ 表示以 $i$ 结尾的合法子串个数，答案就是 $\sum_{i=1}^{\vert s \vert}f_i$。最后再对所有字符串求和。

思考如何求解 $f_i$。手玩一下很容易联想到 CSP2023 T2，令 $g_i$ 表示以 $i$ 结尾的最短合法子串的长度，我们猜想：$f_i=f_{i-g_i}+1$。

不妨证明这个结论。注意到，这等价于证明对于任意 $i,j(i<j)$，若 $s[i \dots i-g_j]$ 不是合法子串，则对于任意 $k \in (i,j)$，$s[i \dots k]$ 与 $s[k+1 \dots j]$ 不可能同时为合法子串。接着不妨考虑反证，假设成立，则可以通过调整得到  $s[i \dots i-g_j]$ 是合法子串，与假设不符，故结论成立。 

最后考虑如何求解 $g_i$，而这显然是个套路化的东西。我们重申一遍 $g_i$ 的定义：字符串 $s$ 与当前所有字符串匹配，能匹配上的最短前缀。这不就是做一遍 AC 自动机后，当前结点一直跳 $fail$ 跳到根之前的最后一个结点的深度吗？在做 AC 自动机时顺便维护一下即可。

时间复杂度 $O(\sum \vert s_i \vert)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,q[N];
string s[N];
int id,tr[N][26],fail[N],f[N],g[N];
inline void insert(string t)
{
	int p=0;
	for(int i=0;i<(int)t.size();i++)
	{
		int to=t[i]-'a';
		if(!tr[p][to]) tr[p][to]=++id,g[id]=g[p]+1;p=tr[p][to]; 
	}
}
inline void build()
{
	int head=0,tail=-1;
	for(int i=0;i<26;i++) if(tr[0][i]) q[++tail]=tr[0][i];
	while(head<=tail)
	{
		int p=q[head++];
		for(int i=0;i<26;i++)
		{
			if(!tr[p][i]) continue;
			int x=fail[p];
			q[++tail]=tr[p][i];
			while(x&&!tr[x][i]) x=fail[x];
			if(tr[x][i]) x=tr[x][i];
			if(x) fail[tr[p][i]]=x,g[tr[p][i]]=g[x];
 		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		reverse(s[i].begin(),s[i].end());insert(s[i]);
	}
	build();
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int p=0;
		for(int j=0;j<(int)s[i].size();j++)
		{		
			p=tr[p][s[i][j]-'a'];
			ans+=(f[j+1]=f[j+1-g[p]]+1);
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Little09 (赞：1)

先把所有串翻转。对 $n$ 个串建 AC 自动机，那么每个子串合法的条件等价于把这个子串拎出来在 AC 自动机上走，除了起点以外没有走到 $0$。证明可以考虑调整，讨论一下每步是否沿着 Trie 边走。

由于数据水，赛时直接写暴力即可通过，而且可以获得最优解。事实上 $n=1$ 一个长度较大的全 `a` 的串就可以卡飞。

考虑什么时候会走到 $0$。假设对于一个串，起点为 $l$，但在走到节点 $r$ 时走到了 $0$，我们希望计算 $l$ 的范围。我们在 fail 树上从 $1\to r$ 走到的节点开始往上跳父亲，那么跳到 $0$ 的时候应该是满足 $r-l+1<len$，其中 $len$ 表示最上面一个非 $0$ 祖先状态的长度。

也就是每个 $r$ 对应的会到 $0$ 的 $l$ 是一段区间，那么就是每次对一段区间取 $\min$，最后查询每个位置的值。

用堆或 set 或并查集或你喜欢的数据结构维护。时间复杂度 $O(c\sum |S|+\sum |S|\log \sum |S|)$，其中 $c$ 为字符集大小。

---

## 作者：_edge_ (赞：0)

来种实现简单的 $O(n)$。

容易发现可以将后缀插到哈希表内。

容易发现 $f_i$ 如果设成以 $i$ 结尾的合法串的个数，然后 $f_i = \sum f_j$ 同时 $[j,i]$ 为合法的，以及 $f_j$ 需要清空。

容易发现清空只会发生一次，所以用链表维护即可。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define pb push_back
using namespace std;
const int INF=1e6+5;
const int Mod=1e9+7;
const int base=233;
const int Mod3=1e6+7;
struct Ha{
    vector < pair<ull,int> > ha[Mod3+5];
    void insert(ull x,int y) {
        pair<ull,int> it={x,y};
        int xx=x%Mod3;
        for (auto i:ha[xx])
            if (i==it) return ;
        ha[xx].pb(it);
        return ;    
    }
    int query(ull x,int y) {
        pair<ull,int> it={x,y};
        int xx=x%Mod3;
        for (auto i:ha[xx])
            if (i==it) return 1;
        return 0;   
    }
}T1;
string s1[INF];
int n,id,hash1[INF],ba1[INF],f[INF],sum[INF],L[INF],R[INF];
ull hash2[INF],ba2[INF];
int Get1(int l,int r) {return (hash1[r]-hash1[l-1]*ba1[r-l+1]%Mod+Mod)%Mod;}
ull Get2(int l,int r) {return (hash2[r]-hash2[l-1]*ba2[r-l+1]);}
void del(int x) {
    L[R[x]]=L[x];
    R[L[x]]=R[x];
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;int sum3=0;
    for (int i=1;i<=n;i++) {
        cin>>s1[i];
        sum3=max(sum3,(int)s1[i].size());
    }
    ba2[0]=1;
    for (int i=1;i<=sum3;i++) ba2[i]=ba2[i-1]*base;
    ba1[0]=1;
    for (int i=1;i<=sum3;i++) ba1[i]=ba1[i-1]*base%Mod;
    for (int i=1;i<=n;i++) {
        int len=s1[i].size();
        s1[i]=" "+s1[i];
        for (int j=1;j<=len;j++) {
            hash1[j]=(hash1[j-1]*base+s1[i][j])%Mod;
            hash2[j]=(hash2[j-1]*base+s1[i][j]);
        }
        for (int j=1;j<=len;j++)
            T1.insert(Get2(j,len),Get1(j,len));
    }
    int res=0;
    for (int i=1;i<=n;i++) {
        int len=s1[i].size()-1;
        for (int j=1;j<=len;j++) {
            hash1[j]=(hash1[j-1]*base+s1[i][j])%Mod;
            hash2[j]=(hash2[j-1]*base+s1[i][j]);
        }
        for (int j=1;j<=len;j++)
            L[j]=j-1,R[j]=j+1;
        f[0]=1;
        int la=1;
        for (int j=1;j<=len;j++) {
            f[j]=1;
            for (int k=j;k>=1;k=L[k]) {
                if (T1.query(Get2(k,j),Get1(k,j))) {
                    f[j]+=f[k-1],del(k);
                }
                else break;
            }
            res+=f[j]-1;
        }
    }
    cout<<res<<"\n";
    return 0;
}
```


---

## 作者：meyi (赞：0)

提供一种理论线性的做法。

前置知识：后缀数组。

首先先套路地把所有串的反串都连在一起，中间加上分隔符，定义 $n$ 为总串的长度，$ans_i$ 表示以 $i$ 为开头的满足要求的子串数量，那么答案为 $\sum\limits_{i=1}^{n}ans_i$。

有一个很 naive 的想法，就是定义 $l_i$ 为满足 $sa_{l_i}\leq sa_i$ 的 $sa_{l_i}$ 最大且 $l_i$ 为某个输入串的末位的位置，同理定义 $r_i$ 为满足 $sa_{r_i}\geq sa_i$ 的 $sa_{r_i}$ 最小且 $r_i$ 为某个输入串的末位的位置，并令 $\text{lcp}(x,y)$ 表示以 $x$ 为开头的后缀与以 $y$ 为开头的后缀的最长公共前缀，那么 $ans_i=max(\text{lcp}(l_i,i),\text{lcp}(i,r_i))$，这个东西可以通过 $height$ 数组 $O(n)$ 计算。

但是这个思路写完发现能过样例一但过不了样例二，重新读题发现合法子串可以由其他合法子串拼接而成，很自然地考虑到动态规划。

具体来说，若 $s_{i..j-1}$ 可以和 $s_{j..x}$ 拼成一个合法子串，那么一定有 $j-1<=i+ans_i-1$，故我们可以令 $ans'_i$ 表示最大的满足 $s_{i..ans'_i}$ 合法的位置，那么 $ans'_i=\max(i+ans_i-1,\max\limits_{j=i+1}^{i+ans_i}ans'_j)$。

最终答案即为 $\sum\limits_{i=1}^n (ans_i-i+1)$。

使用 sa_is 算法求后缀数组和四毛子算法实现线性 rmq 可以做到 $O(n)$。

代码是 0-indexed 的，而且求 rmq 用的是线段树，可能没有什么参考价值，但还是放出来方便读者 debug 或是 hack。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#define ALL(v) v.begin(),v.end()
#define For(i,_) for(int i=0,i##end=_;i<i##end;++i) // [0,_)
#define FOR(i,_,__) for(int i=_,i##end=__;i<i##end;++i) // [_,__)
#define Rep(i,_) for(int i=(_)-1;i>=0;--i) // [0,_)
#define REP(i,_,__) for(int i=(__)-1,i##end=_;i>=i##end;--i) // [_,__)
typedef long long ll;
typedef unsigned long long ull;
#define V vector
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
#define fi first
#define se second
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},inf=0x3f3f3f3f,mod=1e9+7;
const ll infl=0x3f3f3f3f3f3f3f3fll;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int init=[](){return cin.tie(nullptr)->sync_with_stdio(false),0;}();
std::vector<int> sa_naive(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        if (l == r) return false;
        while (l < n && r < n) {
            if (s[l] != s[r]) return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}

std::vector<int> sa_doubling(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        std::swap(tmp, rnk);
    }
    return sa;
}

template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper) {
    int n = int(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }
    if (n < THRESHOLD_NAIVE) {
        return sa_naive(s);
    }
    if (n < THRESHOLD_DOUBLING) {
        return sa_doubling(s);
    }

    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper) sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int>& lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n) continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    std::vector<int> lms_map(n + 1, -1);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }

    induce(lms);

    if (m) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (int v : sa) {
            if (lms_map[v] != -1) sorted_lms.push_back(v);
        }
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r]) same = false;
            }
            if (!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa =
            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

std::vector<int> suffix_array(const std::vector<int>& s, int upper) {
    assert(0 <= upper);
    for (int d : s) {
        assert(0 <= d && d <= upper);
    }
    auto sa = sa_is(s, upper);
    return sa;
}

template <class T>
std::vector<int> lcp_array(const std::vector<T>& s,
                           const std::vector<int>& sa) {
    int n = int(s.size());
    assert(n >= 1);
    std::vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    std::vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0) h--;
        if (rnk[i] == 0) continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}
template<class T,T e,T(*merge)(T,T)>
struct SGT{
    int n;
    V<T>t;
    inline void resize(int n_){V<T>((n=n_)<<2).swap(t);}
    inline SGT(int n_=0){resize(n_);}
    inline void push_up(int p){t[p]=merge(t[p<<1],t[p<<1|1]);}
    void build(int p,int l,int r,const V<T>&v){
        if(l==r){t[p]=v[l];return;}
        int mid=l+r>>1;
        build(p<<1,l,mid,v),build(p<<1|1,mid+1,r,v);
        push_up(p);
    }
    inline void build(const V<T>&v){
        assert(v.size()==n);
        build(1,0,n-1,v);
    }
    void build(int p,int l,int r){
        if(l==r){t[p]=e;return;}
        int mid=l+r>>1;
        build(p<<1,l,mid),build(p<<1|1,mid+1,r);
    }
    inline void build(){
        build(1,0,n-1);
    }
    void query(int p,int l,int r,int ql,int qr,T &ret){
        if(ql<=l&&r<=qr){ret=merge(ret,t[p]);return;}
        int mid=l+r>>1;
        if(ql<=mid)query(p<<1,l,mid,ql,qr,ret);
        if(qr>mid)query(p<<1|1,mid+1,r,ql,qr,ret);
    }
    inline T query(int l,int r){
        assert(0<=l),assert(l<=r),assert(r<n);
        T ret=e;
        query(1,0,n-1,l,r,ret);
        return ret;
    }
    void modify(int p,int l,int r,int k,const T &v){
        if(l==r){t[p]=v;return;}
        int mid=l+r>>1;
        k<=mid?modify(p<<1,l,mid,k,v):modify(p<<1|1,mid+1,r,k,v);
        push_up(p);
    }
    inline void modify(int k,const T& v){
        assert(0<=k),assert(k<n);
        modify(1,0,n-1,k,v);
    }
};
int merge(int x,int y){return max(x,y);}
int main(){
	int t_case=1;
//	scanf("%d",&t_case);
	while(t_case--){
		int ed=255,n;
		cin>>n;
		V<int>a,len;
		V<bool>tl;
		For(i,n){
			string t;
			cin>>t;
			reverse(ALL(t));
			int m=a.size();
			a.resize(m+t.size()+1),len.resize(m+t.size()+1);
			For(j,t.size())a[m+j]=t[j],len[m+j]=t.size();
			a[m+t.size()]=++ed;
			tl.resize(m+t.size()+1);
			tl[m]=true;
		}
		V<int>sa=suffix_array(a,ed),ht=lcp_array(a,sa);
		V<int>ans(a.size());
		int mx=0;
		For(i,a.size()){
			if(tl[sa[i]])mx=len[sa[i]];
			if(a[sa[i]]<256)ckmax(ans[sa[i]],mx);
			if(i+1<a.size())ckmin(mx,ht[i]);
		}
		mx=0;
		Rep(i,a.size()){
			if(tl[sa[i]])mx=len[sa[i]];
			if(a[sa[i]]<256)ckmax(ans[sa[i]],mx);
			if(i)ckmin(mx,ht[i-1]);
		}
		V<int>st;
		SGT<int,0,merge>t(a.size());
		Rep(i,a.size())if(a[i]<256&&ans[i])ckmax(ans[i],t.query(i+1,i+ans[i])-i+1),t.modify(i,i+ans[i]-1);
		printf("%lld\n",accumulate(ALL(ans),0ll));
	}
	return 0;
}
```

---

