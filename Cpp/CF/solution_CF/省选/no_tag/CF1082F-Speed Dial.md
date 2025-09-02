# Speed Dial

## 题目描述

Polycarp神犇的电话册里有$n$个电话号码，每一个号码都被描述为$s_i$，即号码本身，以及$m_i$​，就是Polycarp神犇每天拨打这个电话的次数。

Polycarp刚刚购买了一个手机，拥有极其优秀的快速拨号的功能！（这很惊人吗？）准确的说，这个手机上有$k$个按钮可以绑定一个数字（不一定是电话册里的）。为了输入一个号码，Polycarp神犇可以先按$k$个按钮中的一个，然后再用数字按钮完成这个号码（输入的一个号码只用数字键打出也是可能的）。

快速拨号键只可以在没有输入任何数字时使用，且其数字不可以被重新绑定。

那么Polycarp神犇在ta已经向快拨键赋值后将号码簿里的所有号码拨他应该拨的次数（即$m_i$​）后，他最少要按多少次数字键？

## 说明/提示

---

样例一：

唯一的快拨按钮应有“0001”与之绑定。总数为14。

---

样例二：

唯一的快拨按钮应有“00”与之绑定。总数为18。

## 样例 #1

### 输入

```
3 1
0001 5
001 4
01 1
```

### 输出

```
14
```

## 样例 #2

### 输入

```
3 1
0001 5
001 6
01 1
```

### 输出

```
18
```

# 题解

## 作者：Winniechen (赞：8)

这个题是一道非常经典的DP了。

把这些串建在Trie树上，然后可以将问题转化为每个叶子节点有一个权值，然后在树上选择$K+1$个点，使得从叶子到最近一个选择的节点的距离乘以点权最小。

其中根节点必须选。

这个问题就和IOI2005 riv 的DP方程一样了

[题目链接](https://www.luogu.org/problemnew/show/P3354)

然后设出$f[i][j][k]$表示$i$的子树里，距离$i$最近的被选中的节点为$j$，子树中选择的节点数为$K$的最小代价。

转移即可。

附上代码，BY suika

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 505
char w[N];
int fa[N][N],ans,val[N],n,K,cnt=1,ch[N][12];
int len[N],tmp[N][12],siz[N];
int f[N][N][12],dep[N],wa[N];
inline void upd(int &x,int y) {
    x=x>y?x:y;
}
void dfs(int x) {
    int i,j,k,l;
    fa[x][0]=x;
    siz[x]=1;
    for(i=0;i<=len[x];i++) {
        f[x][i][!i]=dep[fa[x][i]]*wa[x];
    }
    for(i=0;i<10;i++) if(ch[x][i]) {
        int t=ch[x][i];
        dep[t]=dep[x]+1;
        for(j=0;j<=len[x];j++) fa[t][++len[t]]=fa[x][j];

        dfs(t);
        for(j=0;j<=len[x];j++) {
            for(k=0;k<=siz[x]&&k<=K;k++) {
                tmp[j][k]=f[x][j][k];
                f[x][j][k]=-0x3f3f3f3f;
            }
        }
        for(j=0;j<=len[x];j++) {
            for(k=0;k<=siz[x]&&k<=K;k++) {
                for(l=0;l<=siz[t]&&k+l<=K;l++) {
                    upd(f[x][j][k+l],tmp[j][k]+max(f[t][j+1][l],f[t][0][l]));
                }
            }
        }
        siz[x]+=siz[t];
    }
}
int main() {
    memset(f,0xc0,sizeof(f));
    scanf("%d%d",&n,&K); K++;
    int i,j;
    for(i=1;i<=n;i++) {
        scanf("%s%d",w+1,&val[i]);
        int l=strlen(w+1);
        ans+=l*val[i];
        int p=1;
        for(j=1;j<=l;j++) {
            int &k=ch[p][w[j]-'0'];
            if(!k) k=++cnt;
            p=k; 
        }
        wa[p]+=val[i];
    }
    dfs(1);
    int mx=0;
    for(i=1;i<=K;i++) mx=max(mx,f[1][0][i]);
    printf("%d\n",ans-mx);
}


```

---

## 作者：Cry_For_theMoon (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1082F)

**upd：我竟然把IOI2005打成了IOI2015（）**

很久没做小清新树形DP题了。这题其实和IOI2005 Riv.是一道题，但是之前做过原题的我由于理解不扎实还是不会做..... 希望大家可以透彻理解，不要犯和我一样的问题。

第一眼望上去这个题是非常不可做的。但是我们高亮标出：

Speed dial button can only be used when no digits are entered.（手动 highlight）

翻译过来，就是说，快捷按键只能在一个电话号码还**没有输入的时候按一次**。换言之，对于每个电话号码，我们只能最多选取其一个**前缀**用快捷键输入。然后我们考虑到多个电话号码，可能还会有相同前缀。那么很明朗了：我们把这些电话号码插入字典树。那么我们选择一个前缀作为快捷键就等价于标记字典树上某个点。

然后考虑怎么计算贡献。对于一个单词节点 $i$。她的贡献应该是 $w_i$（即 $m$）乘上 $i$ 到最近的带有标记的祖先的距离（默认根节点 $0$ 是选择的，不占用 $k$ 次机会的一个）。我们需要最小化总贡献。到这里就转化成了 [P3354](https://www.luogu.com.cn/problem/P3354).

这个东西还是挺难的，稍微讲一下好了。

不难想到尝试树形DP：设 $f(i,j)$ 是 $i$ 子树中选 $j$ 个节点标记的最小贡献。然后我们在转移的时候会遇到一个问题：我们无法统计子树 $v$ 对答案的贡献，因为我们不知道 $v$ 中有哪些点要继续上到 $u$ 上来。

也就是说向下这条路已经行不通了，我们考虑向上。如果我们加一维 $f(i,j,k)$，表示 $i$ 子树选 $j$ 个，祖先里最近的标记节点要走 $k$ 步（注意到这个祖先节点是不占用 $j$ 个名额的，除非 $k=0$）此时这颗子树的最小贡献。我们不难列出方程：

$$f(i,j,k)=\min\{f(i,j-x,k)+f(v,x,k+1)\}$$

这个时候 $v$ 中向上的贡献我们会惊喜地发现已经统计出来了。但是还没有结束。$k$ 最小是 $0$，所以 $f(v,x,k+1)$ 的第三维最小是 $1$. 但是并没有任何限制要求这一维不能为 $0$. 所以我们还要特别考虑 $f(v,x,0)$. 但是再次注意到这里的 $j$ 不包括根节点，所以实际上是 $f(v,x-1,0)$. 当然，还有一个更方便的方法，就是我们 dp 完以后，让 $f(i,j,k)$ 和 $f(i,j-1,0)$ 取 $\min$. 这样同样可以让上层的转移正确。（反正你只需要让上层状态调用下层状态时可以考虑 $k=0$ 就行，但是大家都写的合并，所以就会让人很迷惑）。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=510,INF=1e9;
int n,k,m[MAXN];
char str[MAXN];
struct Trie{
	int ch[MAXN][10];
	int tot,w[MAXN],dp[MAXN][MAXN][15];
	char H(char ch){return ch-'0';}
	void Insert(char* s,int val){
		int u=0;
		for(int i=0;s[i];i++){
			if(!ch[u][H(s[i])])ch[u][H(s[i])]=++tot;
			u=ch[u][H(s[i])];
		}
		w[u]+=val;
	}
	void dfs(int u,int depth){
		rep(j,0,9){if(!ch[u][j])continue;
			dfs(ch[u][j],depth+1);
		}
		rep(i,0,depth)rep(j,0,k)dp[u][i][j]=i*w[u];
		rep(j,0,9){if(!ch[u][j])continue;
			int v=ch[u][j];
			rep(i,0,depth){
				per(x,k,0){
					dp[u][i][x]+=dp[v][i+1][0];
					rep(use,1,x)dp[u][i][x]=Min(dp[u][i][x],dp[u][i][x-use]+dp[v][i+1][use]),
					dp[u][i][x]=Min(dp[u][i][x],dp[u][i][x-use]+dp[v][0][use-1]);
				}
			}
		}
	}
}trie;
int main(){
	cin>>n>>k;
	rep(i,1,n){
		cin>>str>>m[i];
		trie.Insert(str,m[i]);
	}
	trie.dfs(0,0);
	cout<<trie.dp[0][0][k];
	return 0;
}
```


---

## 作者：mqmhaaaa1 (赞：1)

首先看得出来，快捷键只能设置成前缀，于是想到可以把字典树建出来，点权为以这个点为末尾的号码需要的总拨打次数。

接下来，我们的目标就是求选出 $k$ 个点，令所有节点到其祖先上离它最近被选中的点的距离与这个结点点权的乘积之和最小。

很显然，根节点一开始就是被选的，不占次数。

我之前尝试过贪心，不过是假的，所以使用 dp。

既然点数和 $k$ 都不大，所以状态很好设计，可以设 $f_{i,j}$ 表示在节点 $i$ 的子树中，选了 $j$ 个点，令其求得的上述乘积和最小。这里注意，$i$ 的子树外的被选的节点也会影响这里面的答案。

为了表示选了 $i$ 的祖先对 $f_{i,j}$ 的影响，我们多加一维 $up$，表示在 $i$ 往上走 $up$ 步的那个祖先被选了。

转移方程不难。我们设现在设当前节点为 $u$，正在进行转移的儿子为 $v$，$usd$ 表示 $v$ 子树中选出点的数量，于是有转移方程：

$ f_{u,j,up}=\min( f_{u,j-usd,up}+ \min(f_{v,usd,up+1},f_{v,usd,0})) $。

其中 $f_{v,usd,0}$ 表示点 $v$ 就是被选点的情况，其他很好理解。

这样的话转移就是 $O(S^2 \times k^2)$，$S$ 表示字符串总长，也就是点数的上限。

不过这题有很多很多细节要考虑。

首先是边界条件。因为当 $up=0$ 时，表示点 $i$ 就是被选点，所以 $j$ 一定大于 $0$。同时，这种情况下，$usd$ 的上限也得调到 $j-1$。但是，当 $i$ 为根节点时，因为不占选取次数，所以不受上述影响，$j$ 可以等于 $0$，$usd$ 的上限也不用调整。

还有，我们发现当 $up$ 选的点在 $i$ 的子树外面且不为根节点的话，就会占用一个次数，所以 $j$ 的上限便要变为 $k-1$。

其次，在 dp 时，要把没有进行转移，也就是不可能出现的状态的值赋值为 $\inf$，防止在转移时多出很多的不合法状态转移来的 $0$。但这个过程我没有用 ```memset```，因为转移的时候是相当于合并上这个点儿子的 $f$ 的，所以一开始合法状态的值应是 $0$。

但是，我们要预处理出所有有点权结点 $f$ 的初始值，很明显，$f_{i,(up=0),up}=sm_i \times up$，$sm$ 表示点权，$up=0$ 就是逻辑运算，因为当 $up=0$ 时 $j>0$。

接下来看注释：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define i8 __int128
void write1(ll x) {if (x < 0) putchar('-'), x = -x;if (x > 9) write1(x / 10);putchar(x % 10 + '0');}
void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const ll N=1e3+10,inf=0x3f3f3f3f3f3f3f3f;
ll to[N<<1],nxt[N<<1],bh[N],tot=1;
ll n,k;
void add(ll u,ll v){
	to[++tot]=v;
	nxt[tot]=bh[u];
	bh[u]=tot;
}//我比较喜欢把字典树单独建一个正常的图出来 
ll fa[N],dep[N];
ll sm[N];
ll son[N][10],ct=0;//根节点为0 
void insert(string s,ll val){
	ll u=0;
	for(ll i=0;i<s.size();i++){
		ll v=s[i]-'0';
		if(!son[u][v]){
			son[u][v]=++ct,dep[son[u][v]]=dep[u]+1,fa[son[u][v]]=u;
			add(u,son[u][v]);
		}
		u=son[u][v];
	}
	sm[u]+=val;
}//trie
ll f[N][11][N];
void dfs(ll u){
	if(u)f[u][0][0]=inf;//只有根节点以外这个才是不可能状态 
	for(ll i=0;i<=dep[u];i++){
		f[u][(ll)(!i)][i]=i*sm[u];
	}//预处理 
	for(ll i=bh[u];i;i=nxt[i]){
		ll v=to[i];
		if(v==fa[u])continue;
		dfs(v);
		for(ll up=0;up<=dep[u];up++){
			for(ll hv=k-(up!=dep[u]&&up);hv>=(!up&&u);hv--){//注意边界和顺序 
				ll mi=inf;
				for(ll usd=0;usd<=hv-(!up&&u);usd++){//注意边界 
					mi=min(mi,f[u][hv-usd][up]+min(f[v][usd][up+1],f[v][usd][0]));
				}
				f[u][hv][up]=mi;
			} 
			if(up!=dep[u]&&up)f[u][k][up]=inf;
			if(!up&&u)f[u][0][up]=inf;
			//两种不可能情况 
		}
	}
}
int main(){
	n=read(),k=read();
	for(ll i=1;i<=n;i++){
		string s;cin>>s;
		ll val=read();
		insert(s,val);
	}
	dfs(0);
	ll as=inf;
	for(ll i=0;i<=k;i++){
		as=min(as,f[0][k][0]);//取最小 
	}
	cout<<as<<'\n';
}

```

本人第一篇 dp 题解，感谢观看。

白庭就是神曲，都给我去玩除你字母。

---

## 作者：睿智的憨憨 (赞：0)

# CF1082F Speed Dial 解题报告

## 题目链接

https://codeforces.com/problemset/problem/1082/F

## 题目大意

给定 $n$ 个由 $0 \sim 9$ 组成的字符串 $s_i$ 以及它们的使用次数 $m_i$。请设计 $p$ 个字符串 $t_i$，使得每个字符串的使用次数 $\times$ (串的长度减 $t$ 中串的最长前缀的长度）之和最小，输出最小的和。

## 解法分析

既然是与前缀有关的问题，那么就不难联想到字典树。我们对 $s$ 建立一颗字典树，并且将点的权值设为对应字符串的出现次数。于是问题就转化为：在字典树上选 $p+1$ 个节点（根节点必选）使得**所有点的权值 $\times$ 这个点的最近被选祖先与这个点的距离之和**最小。

考虑树形 dp 解决转化后的问题。$dp_{i,j,k}$ 表示 $i$ 与最近的被选祖先的距离为 $j$ 且 $i$ 的子树中有 $k$ 点被选中时，$i$ 的子树中上面标粗部分的最小值（$j=0$ 就是 $i$ 被选了），转移时要注意 dp 的顺序，很重要！时间复杂度 $O(S^2k^2)$，其中 $S$ 是所有字符串的总长度，不超过 500。

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 510, inf = 0x3f3f3f3f;
int n, K, m[N];
string s[N];
int id[N][20], dth[N], val[N], tot, ans = inf;
void add(string &t, int v){
	int p = 0;
	for (int i = 0; i < t.size(); i++){
		if (!id[p][t[i] - '0']){
			id[p][t[i] - '0'] = ++tot;
			dth[tot] = dth[p] + 1;
		}
		p = id[p][t[i] - '0'];
	}
	val[p] += v;
}
int dp[N][20][N];
void dps(int u){
	for (int k = 0; k <= dth[u]; k++)
		dp[u][(k == 0)][k] = val[u] * k;
	for (int i = 0; i <= 9; i++){
		int v = id[u][i];
		if (!v)
			continue;
		dps(v);
		for (int k = 0; k <= dth[u]; k++){
			for (int j = K; j >= (k == 0); j--){
				int mn = inf;
				for (int w = 0; w <= j - (k == 0); w++)
					mn = min(mn, dp[u][j - w][k] + min(dp[v][w][k + 1], dp[v][w][0]));
				dp[u][j][k] = mn;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> K, K++;
	for (int i = 1; i <= n; i++){
		cin >> s[i] >> m[i];
		add(s[i], m[i]);
	}
	memset(dp, inf, sizeof(dp));
	dps(0);
	for (int j = 0; j <= K; j++)
		ans = min(ans, dp[0][j][0]);
	cout << ans << endl;
	return 0;
}
```

---

