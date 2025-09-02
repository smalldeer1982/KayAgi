# [ABC349G] Palindrome Construction

## 题目描述

我们称长度为 $M$ 的正整数序列 $T=(T_1,T_2,\dots,T_M)$ 是**回文**的，当且仅当对于每个 $i=1,2,\dots,M$，都有 $T_i=T_{M-i+1}$。

给定一个长度为 $N$ 的非负整数序列 $A=(A_1,A_2,\dots,A_N)$。请判断是否存在一个满足下述条件的长度为 $N$ 的正整数序列 $S=(S_1,S_2,\dots,S_N)$，如果存在，请输出所有满足条件的序列中字典序最小的一个。

- 对于每个 $i=1,2,\dots,N$，都满足以下两点：
  - 序列 $(S_{i-A_i},S_{i-A_i+1},\dots,S_{i+A_i})$ 是回文的。
  - 如果 $2\leq i-A_i$ 且 $i+A_i\leq N-1$，则序列 $(S_{i-A_i-1},S_{i-A_i},\dots,S_{i+A_i+1})$ 不是回文的。

## 说明/提示

## 限制条件

- $1\leq N\leq 2\times 10^5$
- $0\leq A_i\leq \min\{i-1,N-i\}$
- 输入均为整数

## 样例解释 1

可以确认 $S=(1,1,2,1,1,1,2)$ 满足条件。
- $i=1$：$(A_1)=(1)$ 是回文。
- $i=2$：$(A_2)=(1)$ 是回文，且 $(A_1,A_2,A_3)=(1,1,2)$ 不是回文。
- $i=3$：$(A_1,A_2,\dots,A_5)=(1,1,2,1,1)$ 是回文。
- $i=4$：$(A_4)=(1)$ 是回文，且 $(A_3,A_4,A_5)=(2,1,1)$ 不是回文。
- $i=5$：$(A_3,A_4,\dots,A_7)=(2,1,1,1,2)$ 是回文。
- $i=6$：$(A_6)=(1)$ 是回文，且 $(A_5,A_6,A_7)=(1,1,2)$ 不是回文。
- $i=7$：$(A_7)=(2)$ 是回文。

除此之外，$S=(2,2,1,2,2,2,1)$ 等也满足条件，但字典序最小的是 $(1,1,2,1,1,1,2)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
0 0 2 0 2 0 0```

### 输出

```
Yes
1 1 2 1 1 1 2```

## 样例 #2

### 输入

```
7
0 1 2 3 2 1 0```

### 输出

```
Yes
1 1 1 1 1 1 1```

## 样例 #3

### 输入

```
7
0 1 2 0 2 1 0```

### 输出

```
No```

# 题解

## 作者：Eraine (赞：6)

编号：AT_abc349_g

tag：manacher

难度：*2560（$\texttt{Clist}$ 数据）

又双叒叕赛后独立切橙 G。而且仅用 35min。

说实在，我第一眼看成给定 $S$ 求 $A$。

然后发现是给定 $A$ 求 $S$，最小字典序化 $S$。

给定 $S$ 求 $A$ 是 Manacher 模板。之后就很难不往 Manacher 的方面想了。

我们考虑模拟 Manacher，与原来 Manacher 不同的是，我们知道了 $p$ 和 $len$ 将要变成什么，然后要连接中间回文串对应位置使之一一相等。容易用并查集维护。

我们先想一想暴力的思路，即对于每一个位置 $i$，枚举 $p\in[1,a_i]$，在并查集中连接 $(i-p,i+p)$。记得处理 $\texttt{No}$ 的情况，即存在 $i$ 使得 $i-a_i-1$ 和 $i+a_i+1$ 在同一连通块。这个可以暴力 $\Theta(n)$ 判断。至于输出，只要贪心枚举未赋颜色联通块与哪些已染色的联通块互斥，取最小未出现的正整数即可。

我们想一想为什么暴力是错的。瓶颈在连接 $(i-p,i+p)$。总共要连接 $\Theta(\sum a_i)$ 个合法二元组（这里的合法二元组 $(i,j)(i\lt j)$ 指使得 $s[i\dots j]$ 是回文串的二元组）。对于特殊数据 $\texttt{aaa\dots aaa}$，发现 $\sum a_i$ 是 $\Theta(n^2)$ 级别的，很容易发现时间复杂度是 $\Theta(n^2\alpha)$。

考虑优化。即我们要如何运用模拟 Manacher 使得时间复杂度正确。我们发现，在上述特殊样例中，对于任意的 $i$ 与之相关的合法二元组（即两个元素中有一个为 $i$ 的合法二元组）都有多组，而在暴力思想中，出现 $x$ 组合法二元组就要执行 $x$ 次的并查集合并操作。很容易发现，对于一个大小 $n$ 联通块中，最多执行了 $\Theta(n^2)$ 次的并查集合并操作。要构成联通块只需执行 $n-1$ 次并查集合并操作即可。也就意味着，我们要删掉一些无用的二元组。一个很明显的 trick 就是对于相同的 $j$，最多执行一次的二元组合并操作，就能使得复杂度正确，为 $\Theta(n\alpha)$。Manacher 算法的复杂度正确的原因正是因为如此，所以我们可以采用模拟 Manacher。

接下来讲解具体细节。下文的 $p$ 表示为 Manacher 算法中的辅助回文区间的位置，$len$ 为区间长度。

当 $i\gt p+len$ 时，暴力拓展即可。

当 $i\le p+len$ 时，$j=2p-i$ 为在区间 $[p-len,p+len]$ 中 $i$ 对应的位置，在区间 $[i+1,\min(p+len,i+\min(a_i,a_j))]$ 中的所有元素在之前已经执行过合并操作了，就没有必要再次转移了。这步保证了正确的时间复杂度。根据 Manacher 模拟即可。

接下来考虑 $\texttt{No}$ 的情况。我们可以沿用暴力的判断方式。但是会发现是错的。为什么呢？当 $i\le p+len$ 时，理论上在区间 $[i+1,\min(p+len,i+\min(a_i,a_j))]$ 中所有的与回文相关信息都被传上去。可是当 $a_j\lt a_i$ 时，$[i+a_j+1,\min(i+a_i,p+len)]$ 的回文信息为了保证时间复杂度是直接略过的，但是事实上，若存在这样的区间要输出 $\texttt{No}$，所以特判即可。

$\Theta(n\alpha)$。

[submission](https://atcoder.jp/contests/abc349/submissions/52404995)

37ms，跑得还是很快的。

若有误请指出，虚心听取您的意见，谢谢。

---

## 作者：HHH6666666666 (赞：4)

一种暴力：

按照回文半径将每个回文串上的字符间连边，使字符必须相同的位置在同一连通块内。再根据极长的性质在连通块间连边表示有边相连的连通块字符不能相同，贪心地给图染色即可。

第一步的边数是 $O(n^2)$ 的，考虑优化。

题目条件让人联想到 `manacher` 算法，我们可以使用类似的方法将边数优化为 $O(n)$：只需在最右端点扩展时连边。其他情况下根据回文串的对称性，边是不用连的。注意判断无解情况。

时间复杂度 $O(n\alpha(n))$。

```cpp
#include<bits/stdc++.h>
#define ep emplace
#define eb emplace_back

using namespace std;

const int MAXN = 2e5 + 10;

int n;
int a[MAXN];
int pa[MAXN];
vector<int> to[MAXN];
int co[MAXN];

int find(int x) { return x == pa[x] ? x : pa[x] = find(pa[x]); }

bool dfs(int x, int c) {
    if (~co[x]) return co[x] == c;
    for (int y : to[x])
        if (!dfs(y, !c)) return false;
    return true;
}

int main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    iota(pa + 1, pa + n + 1, 1);
    for (int i = 1, mid = 0, r = 0; i <= n; ++i) {
        if (r < i) {
            for (int j = i + 1; j <= i + a[i]; ++j) pa[find(j)] = find(2 * i - j);
            r = i + a[i], mid = i;
        }
        else if (r <= i + a[i]) {
            int t = r - i;
            if (a[2 * mid - i] < t) {
                cout << "No" << endl;
                return 0;
            }
            for (int j = r + 1; j <= i + a[i]; ++j) pa[find(j)] = find(2 * i - j);
            r = i + a[i], mid = i;
        }
        else {
            if (a[2 * mid - i] != a[i]) {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (i + a[i] == n || i - a[i] == 1) continue;
        int x = find(i + a[i] + 1), y = find(i - a[i] - 1);
        if (x == y) {
            cout << "No" << endl;
            return 0;
        }
        to[x].eb(y), to[y].eb(x);
    }
    cout << "Yes" << endl;
    for (int i = 1; i <= n; ++i) co[i] = -1;
    for (int i = 1; i <= n; ++i) {
        int t = find(i);
        if (~co[t]) continue;
        set<int> s;
        for (int j : to[t]) s.ep(co[j]);
        for (int j = 1; ; ++j)
            if (!s.count(j)) {
                co[t] = j;
                break;
            }
    }
    for (int i = 1; i <= n; ++i) cout << co[find(i)] << ' ';
    cout << endl;
    return 0;
}

```

---

## 作者：tobie (赞：2)

我们定义 $s_i=s_j$ 为“相等限制”，$s_i\neq s_j$ 为“不等限制”

不妨假设答案存在，考虑在 Manacher 的过程中计算答案。

假如现在已知的最右端下标最大的回文串中心为 $x$，那么考虑 $s_i$ 的取值：

如果 $x+A_{x}\ge i$，那么根据回文的定义，$s_i$ 已经由 $s_{2x-i}$ 确定。

否则，$s_i$ 不被之前的“相等限制”约束，我们可以在 $s_i$ 内填一个最小的满足之前添加的的所有“不等限制”的数。

现在我们确定了 $s_i$，那么我们接下来要考虑增加限制，即 $s_{i+A_i+1}\neq s_{i-A_i-1}$。

事实上这个算法的本质是在维护所有的“相等”与“不等”限制。不同于朴素算法的是，我们只维护了 $O(n)$ 个“不等”限制，而相等限制可以直接递推计算，根据并查集的正确性可以证明本算法的正确性。

当然，因为以上算法正确的前提是答案存在，所以最后还要跑一遍 Manacher 判断，如果构造方案不满足题意则无解。

```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int N=200009;
int n,a[N],s[N],s0[N];
set<int> lim[N];
signed main()
{
	scanf("%d",&n);
	for(int i=1,mid,r=0;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(i<=r) s[i]=s[mid*2-i];
		else
		{
			bool flg=0;
			int lst=0;
			for(set<int>::iterator it=lim[i].begin();it!=lim[i].end();it++)
			{
				if((*it)>lst+1) {flg=1;s[i]=lst+1;break;}
				else lst=(*it);
			}
			if(!flg) s[i]=lst+1;
		}
		if(1<i-a[i]&&i+a[i]<n) lim[i+a[i]+1].insert(s[i-a[i]-1]);
		if(i+a[i]>r) mid=i,r=i+a[i];
	}
	s[0]=-1,s[n+1]=-2;
	for(int i=1,mid,r=0;i<=n;i++)
	{
		s0[i]=0;
		if(r>=i) s0[i]=min(s0[mid*2-i],r-i);
		while(s[i-s0[i]-1]==s[i+s0[i]+1]) s0[i]++;
		if(i+s0[i]>r) mid=i,r=i+s0[i];
	}
	for(int i=1;i<=n;i++) if(a[i]!=s0[i]) return puts("No"),0;
	puts("Yes");
	for(int i=1;i<=n;i++) printf("%d ",s[i]);
}
```

---

## 作者：sunzz3183 (赞：2)

# [ABC349G] Palindrome Construction 题解

## 题意

给定一个长度为 $n$ 的序列 $a$，求一个字典序最小的序列 $s$，使得 $\forall_i$ 区间 $[i-a_i,i+a_i]$ 为回文串，且不能再向两边扩展。

## 分析

算法：**ST 表、并查集**。

其实就是[P3295萌萌哒](https://www.luogu.com.cn/problem/P3295)，因为相等这种东西可以多次做，所以可以用 ST 表维护。

考虑对于回文，利用上述算法维护哪些元素相等即可。

具体维护方法如下：如下图，将红色段拆成两种：橙色和蓝色，分别**倒序相等**（即 $a_l=a_r,a_{l+1}=a_{r-1},\dots,a_{l-2^d+1}=a_{r+2^d-1}$），然后不断递推下去直到区间长度为 $1$。

![](https://cdn.jsdelivr.net/gh/sunzz3183/szzphoto@img/img/202404182158718.png)

### 复杂度证明

显然，对于每一层，每一次操作都会把一对点合并，然后递推，否则直接返回。所以相当于每一层有 $n$ 个点，不断建边，最后成为一个联通块。可得每一层操作只有 $n$ 次，一共有 $\log(n)$ 次，然后查询带上并查集的复杂度。

### 构造

由此，我们可以维护出那些元素相同，然后就是构造。

如果存在 $i$，使得 $i-a_i-1$ 和 $i+a_i+1$ 为相同元素，则输出 `No`，否则 $i-a_i-1$ 和 $i+a_i+1$ 一定不相同，我们可以用邻接表或者 `vector` 把并查集之间的这种不同关系存下来，然后从头开始遍历，如果当前元素所在并查集已经赋值，就使用当前数就行，否则把和他不同的元素且已经赋值的元素标记，然后从 $1$ 开始枚举，直到没有被标记过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();int x=0;bool f=1;
	while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f?x:-x;
}
const int N=2e5+2;
int n;
struct dsu{
	int fa[N];
	int find(int v){return v==fa[v]?v:fa[v]=find(fa[v]);}
	void merge(int x,int y){
		x=find(x);y=find(y);
		if(x!=y)fa[x]=y;
	}
	bool check(int x,int y){return find(x)==find(y);}
	void init(){iota(fa+1,fa+n+1,1);}
}d[18];
int ans[N],a[N];
bool vis[N];
vector<int>G[N];
void dfs(int l,int r,int t){
	if(d[t].check(l,r))return;
	if(!t)return d[0].merge(l,r);
	d[t].merge(l,r);
	dfs(l,r,t-1);
	dfs(l+(1<<(t-1)),r-(1<<(t-1)),t-1);
}
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	n=read();
	for(int i=0;i<18;i++)d[i].init();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]){
			int t=__lg(a[i]);
			int l1=i-a[i],r1=i-1,l2=i+1,r2=i+a[i];
			dfs(l1,r2,t);
			dfs(r1-(1<<t)+1,l2+(1<<t)-1,t);
		}
	}
	for(int i=1;i<=n;i++){
		if(i-a[i]-1>=1&&i+a[i]+1<=n&&d[0].check(i-a[i]-1,i+a[i]+1))return puts("No"),0;
		if(i-a[i]-1>=1&&i+a[i]+1<=n){
			int l=i-a[i]-1,r=i+a[i]+1;
			G[d[0].find(l)].push_back(d[0].find(r));
			G[d[0].find(r)].push_back(d[0].find(l));
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++){
		if(!ans[d[0].find(i)]){
			for(int v:G[d[0].find(i)])vis[ans[v]]=1;
			int now=1;
			while(vis[now])now++;
			ans[d[0].find(i)]=now;
			for(int v:G[d[0].find(i)])vis[ans[v]]=0;
		}
		printf("%d ",ans[d[0].find(i)]);
	}
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

题意：给出每个位置为中心的回文半径，构造一个字典序最小的满足条件的字符串。

对于 $i$ 位置的回文半径 $d_i$，能够得到 $a_{i-1}=a_{i+1},a_{i-2}=a_{i+2},\dots,a_{i-d_i-1}\neq a_{i+d_i+1}$。

我们猜测，只用这些关系就能推出所有确定的关系。包含相等的都显然，我们只考虑下面的情况：

若 $i<j<k$，$a_i\neq a_j,a_i\neq a_k$，则 $a_j$ 和 $a_k$ 关系确定。

**证明**：根据上面的连边策略，我们能够知道 $[i+1,k-1]$ 以及 $[i+1,j-1]$ 都是回文的。把 $[i+1,j-1]$ 在 $[i+1,k-1]$ 中看，可以对称到另外一个一样的回文串 $[k-j+i+1,k-1]$，以及 $a_{k-j+i}= a_j$。

如果 $[k-j+i+1,k-1]$ 是极长的，那么说明有 $a_{k-j+i}\neq a_k$，即 $a_j\neq a_k$，否则有 $a_j=a_k$。

---

由此我们可以对于所有推出的相等全都用并查集维护，不等的建出图。之后直接按 $1$ 到 $n$ 的顺序遍历所在等价类（如果计算过结果就不用再考虑），找出最小的不与相邻等价类重复的数，即为答案。

```cpp
int n,d[200005],f[200005];
int zx(int x){return f[x]==x?x:f[x]=zx(f[x]);}
vector<int>v[200005];
int col[200005],vis[200005];

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>d[i],f[i]=i;
	int p=0,mx=0;
	for(int i=1,st;i<=n;i++){// manacher
		if(i<mx)st=min(d[(p<<1)-i],mx-i);
		else st=1;
		if(st>d[i]+1)return NO();// 记得判一些可能导致 T 飞的不合法情况
		while(st<=d[i])f[zx(i-st)]=zx(i+st),st++;
		if(i-st&&zx(i-st)==zx(i+st))return NO();
		v[i-st].push_back(i+st),v[i+st].push_back(i-st);
		if(i+st>mx)mx=i+st,p=i;
	}
	for(int i=1;i<=n;i++)zx(i);
	for(int i=1;i<=n;i++)for(auto j:v[i])if(f[i]==f[j])return NO();// 这里要再判一遍
	YES();
	for(int i=1;i<=n;i++)if(col[f[i]])cout<<col[f[i]]<<" \n"[i==n];
	else{
		set<int>s;
		for(auto j:v[i])if(col[f[j]])if(vis[f[j]]<i)vis[f[j]]=i,s.insert(col[f[j]]);
		for(col[f[i]]=1;s.count(col[f[i]]);col[f[i]]++);// 类似求 mex
		cout<<col[f[i]]<<" \n"[i==n];
	}
}
```

---

## 作者：GY程袁浩 (赞：0)

直接转化，题目意思就是对于 $A_{i}$，$(i-A_{i},i+A_{i})$ 是以 $i$ 为中心的最长回文串。那么就是有，回文串上的每个相对字符相等，$i-A_{i}-1$ 和 $i+A_{i}+1$ 不相等。先考虑相等，使用并查集维护。这个时候是区间并查集连边，之后贪心考虑每个集合，值取所有互斥集合的值的最小未出现过的正整数即可。一个关系最多制造两个互斥关系。

但是这样复杂度不对。考虑区间并查集连边，我们有套路萌萌哒可以倍增区间连边在均摊 $O(\log^2 n)$ 内完成一次。这样是一种做法。

但是我们还可以考虑回文串的性质，即对称，也就是说根据对称性，我们对每个点最多连 $O(1)$ 的边，在 Manacher 算法的过程中，对于 $r<i$ 来说，我们暴力扩展，由于 $r<i$，只会有重复的半段。而对于 $r\ge i$，如果 $d_{i}+i\le r$，那么已经连过边了，否则继续暴力扩展 $[r,d_{i}+i]$ 这一段（之前的在对称区间已经连过边了），$r$ 也会被更新。

最后，由于我们省去了 $r\ge i$ 的部分连边，所以我们不能够只检查 $i-A_{i}-1$ 和 $i+A_{i}+1$ 的所在集合关系。而我们还需要特判有 $r\ge i,d_{i}<\min(d_{l+r-i},r-i)$，这也是不合法的。

```cpp
// 这回只花了 1s 就打完了。
// 真好。记得多手造几组。最好有暴力对拍。

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int N = 2e5 + 10;
int n, d[N], p[N], num[N];
vector<int> op[N];
int find(int x) {
    if (p[x] != x) return p[x] = find(p[x]);
    return x;
}
void solve() {
    cin >> n;
    upp(i, 1, n) cin >> d[i];
    upp(i, 1, n) p[i] = i;
    int l = 0, r = 0;
    upp(i, 1, n) {
        if (i > r) {
            upp(j, 0, d[i]) p[find(i + j)] = find(i - j);
        } else {
            if (d[i] < min(d[l + r - i], r - i)) {
                cout << "No" << endl;
                return;
            }
            if (d[i] > min(d[l + r - i], r - i)) {
                upp(j, min(d[l + r - i], r - i), d[i]) {
                    p[find(i + j)] = find(i - j);
                }
            }
        }
        if (i + d[i] > r) r = i + d[i], l = i - d[i];
    }
    upp(i, 1, n) {
        int x = i - d[i] - 1, y = i + d[i] + 1;
        if (x > 0 && y <= n) {
            x = find(x), y = find(y);
            if (x == y) {
                cout << "No" << endl;
                return;
            }
            op[x].pb(y);
            op[y].pb(x);
        }
    }
    upp(i, 1, n) {
        if (!num[find(i)]) {
            unordered_map<int, int> ha;
            upp(j, 0, (int)op[find(i)].size() - 1) {
                ha[num[op[find(i)][j]]] = 1;
            }
            int now = 1;
            while (ha[now]) now++;
            num[find(i)] = now;
        }
    }
    cout << "Yes" << endl;
    upp(i, 1, n) cout << num[find(i)] << ' ';
    cout << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tt = 1;
    while (tt--) solve();
    return 0;
}
```

---

## 作者：cwfxlh (赞：0)

# [AT_abc349_g](https://www.luogu.com.cn/problem/AT_abc349_g)         

无解比较难，先不考虑，接下来一小段的做法都基于有解。    

首先有一个朴素的做法，对于每个 $i$，将 $[i-A_i,i-1]$ 的点向 $[i+1,i+A_i]$ 的点连边合并，使用并查集维护合并。合并完之后一个连通块内的字符必须相同，并且有 $O(n)$ 对连通块是不能用相同颜色的。为了字典序最小，从前往后钦定每个字符的颜色，如果这个字符所在连通块已被钦定颜色，则输出这个颜色，否则找到其可以选的最小颜色染上色即可。         

上面的做法，问题在于连边的复杂度过高。考虑 manacher 的过程，维护一个当前回文串最右边界，发现这样可以把连边次数减少到 $O(n)$。即只有在扩展最右回文边界的时候才连边，其他时候因为其对称位置已经连过边，所以已经被合并过了。这样可以做到 $O(n\alpha)$ 的合并。        

最后需要解决的就是无解的判定。按上述方式连边后，如果存在一个 $i$，其 $i-a_i-1$ 与 $i+a_i+1$ 是一个连通块，则不合法。但这不是充分的，因为如果无解，上述连边可能不等价于暴力连边。于是在每次增加一个 $i$ 的时候，当前右边界对应的中心为 $j$，考虑 $i$ 回文半径与 $j\times 2-i$ 回文半径的关系，两个不能同时大于 $j+a_j-i$，如果两个不等则一定有一个大于 $j+a_j-i$，一个等于 $j+a_j-i$。除此之外不会再出现其他位置的不合法情况了，因为都可以通过对称分析掉。         

代码：    

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500003],bcj[500003],col[500003];
int stk[500003],tots;
vector<int>nt[500003];
int finf(int now){
    if(bcj[now]!=now)bcj[now]=finf(bcj[now]);
    return bcj[now];
}
int main(){
    freopen("ABC349G.in","r",stdin);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)bcj[i]=i;
    for(int i=2,j=1,j2=1;i<=n;i++){
        if(a[i]==0)continue;
        if(i+a[i]<=j){
            if(i+a[i]==j){
                if(a[j2*2-i]<a[i]){
                    cout<<"No";
                    return 0;
                }
            }
            else{
                if(a[j2*2-i]!=a[i]){
                    cout<<"No";
                    return 0;
                }
            }
            continue;
        }
        if(a[j2*2-i]<j-i){
            cout<<"No";
            return 0;
        }
        if(j>i){
            for(int u=j;u<=i+a[i];u++)bcj[finf(i*2-u)]=finf(u);
        }
        else{
            for(int u=1;u<=a[i];u++)bcj[finf(i+u)]=finf(i-u);
        }
        j=i+a[i];
        j2=i;
    }
    for(int i=1;i<=n;i++){
        if(i-a[i]-1>0&&i+a[i]+1<=n){
            if(finf(i+a[i]+1)==finf(i-a[i]-1)){
                cout<<"No";
                return 0;
            }
            nt[finf(i+a[i]+1)].emplace_back(finf(i-a[i]-1));
            nt[finf(i-a[i]-1)].emplace_back(finf(i+a[i]+1));
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        if(col[finf(i)]!=0){
            cout<<col[finf(i)]<<" ";
            continue;
        }
        int j=1;
        tots=0;
        for(auto u:nt[finf(i)])if(col[u]!=0)stk[++tots]=col[u];
        sort(stk+1,stk+tots+1);
        for(int u=1;u<=tots;u++)if(stk[u]==j)j++;
        col[finf(i)]=j;
        cout<<col[finf(i)]<<" ";
    }
    return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[abc349g](https://www.luogu.com.cn/problem/AT_abc349_g)

### 思路

从前往后枚举 $i$，每次对 $i+1\le j\le i+a_i$ 的 $j$  赋值 $b_j=b_{i\times 2-j}$。同时有 $b_{i+a_i+1}\ne b_{i-a_i-1}$。用 $ban_{i,j}$ 记录 $i$ 不能是 $j$，如果要给 $i$ 赋值就选最小的。

最直接的就是并查集倍增将两段区间并起来。

可以用类似马拉车的思路得到一个贪心算法。枚举，维护 $r$ 表示当前已知 $b_1\dotsb b_r$。如果 $i+a_i\ge r$ 就把 $r$ 更新到 $i+a_i$，否则什么也不做。最后用 hash 判断所有 $a_i$ 是不是都满足条件。

### code

```cpp
int n,a[maxn],b[maxn];
int h[maxn],h2[maxn],pw[maxn],bas,val[10];
int calc(int l,int r){return (h[r]-h[l-1]*pw[r-l+1]%mod+mod)%mod;}
int calc2(int l,int r){return (h2[l]-h2[r+1]*pw[r-l+1]%mod+mod)%mod;}
vector<int> ban[maxn];bool vis[10];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2,r=1;i<=n;i++){
		if(i>r){
			int mex=10;
			for(int j:ban[i])vis[j]=1;
			for(int j=0;j<10;j++)if(!vis[j]){mex=j;break;}
			for(int j:ban[i])vis[j]=0;
			if(mex==10){printf("No\n");return ;}
			b[r=i]=mex;
		}
		if(i+a[i]>r){
			for(int j=r+1;j<=i+a[i];j++)b[j]=b[i*2-j];
			r=i+a[i];
		}
		if(i-a[i]-1){ban[i+a[i]+1].push_back(b[i-a[i]-1]);}
	}
	srand(time(0));
	bas=rand()*rand()%mod;
	for(int i=0;i<10;i++)val[i]=rand()*rand()%bas;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++)h[i]=(h[i-1]*bas+val[b[i]])%mod;
	for(int i=n;i;i--)h2[i]=(h2[i+1]*bas+val[b[i]])%mod;;
	for(int i=1;i<=n;i++){
		if(calc(i-a[i],i)!=calc2(i,i+a[i])){printf("No");return ;}
		if(i-a[i]>1&&i+a[i]<n){
			if(b[i-a[i]-1]==b[i+a[i]+1]){printf("No");return ;}
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++)printf("%lld ",b[i]+1);
}
```

---

## 作者：gdf_yhm (赞：0)

[abc349g](https://www.luogu.com.cn/problem/AT_abc349_g)

### 思路

从前往后枚举 $i$，每次对 $i+1\le j\le i+a_i$ 的 $j$  赋值 $b_j=b_{i\times 2-j}$。同时有 $b_{i+a_i+1}\ne b_{i-a_i-1}$。用 $ban_{i,j}$ 记录 $i$ 不能是 $j$，如果要给 $i$ 赋值就选最小的。

最直接的就是并查集倍增将两段区间并起来。

可以用类似马拉车的思路得到一个贪心算法。枚举，维护 $r$ 表示当前已知 $b_1\dotsb b_r$。如果 $i+a_i\ge r$ 就把 $r$ 更新到 $i+a_i$，否则什么也不做。这样每个位置只被更新一次。最后 hash 判断所有 $a_i$ 是不是都满足条件。

### code

```cpp
int n,a[maxn],b[maxn];
int h[maxn],h2[maxn],pw[maxn],bas,val[10];
int calc(int l,int r){return (h[r]-h[l-1]*pw[r-l+1]%mod+mod)%mod;}
int calc2(int l,int r){return (h2[l]-h2[r+1]*pw[r-l+1]%mod+mod)%mod;}
vector<int> ban[maxn];bool vis[10];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2,r=1;i<=n;i++){
		if(i>r){
			int mex=10;
			for(int j:ban[i])vis[j]=1;
			for(int j=0;j<10;j++)if(!vis[j]){mex=j;break;}
			for(int j:ban[i])vis[j]=0;
			if(mex==10){printf("No\n");return ;}
			b[r=i]=mex;
		}
		if(i+a[i]>r){
			for(int j=r+1;j<=i+a[i];j++)b[j]=b[i*2-j];
			r=i+a[i];
		}
		if(i-a[i]-1){ban[i+a[i]+1].push_back(b[i-a[i]-1]);}
	}
	srand(time(0));
	bas=rand()*rand()%mod;
	for(int i=0;i<10;i++)val[i]=rand()*rand()%bas;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++)h[i]=(h[i-1]*bas+val[b[i]])%mod;
	for(int i=n;i;i--)h2[i]=(h2[i+1]*bas+val[b[i]])%mod;;
	for(int i=1;i<=n;i++){
		if(calc(i-a[i],i)!=calc2(i,i+a[i])){printf("No");return ;}
		if(i-a[i]>1&&i+a[i]<n){
			if(b[i-a[i]-1]==b[i+a[i]+1]){printf("No");return ;}
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++)printf("%lld ",b[i]+1);
}
```

---

## 作者：fydj (赞：0)

### 鸣谢

感谢 @[lnw143](https://www.luogu.com.cn/user/767819)。

### 思路

把区间翻转后接在原区间后面，即原来的点 $x$ 对应点 $2n+1-x$。

这样，一个回文串 $[l,r]$ 就相当于 $[l,r]$ 中每个点和 $[2n+1-r,2n+1-l]$ 中每个点按顺序从左到右对应连边。

考虑倍增。第 $t$ 个并查集中点 $x$ 和 $y$ 在同一集合，就说明 $[x+2^t-1]$ 和 $[y+2^t-1]$ 中的点一一对应连边。

如果要将 $[l,r]$ 和 $[L,R]$ 中的点一一对应连边，那么可以把区间分成若干段，每一段的长度都是 $2^t$，其中 $t$ 为非负整数，然后在第 $t$ 个并查集中把点 $l$ 和点 $L$连边。

要在第 $t$ 个并查集中把点 $x$ 和点 $y$ 连边，如果两个点已经在同一集合里了，那么不用理睬；否则连边，并且在第 $t-1$ 个集合里把 $x$ 和 $y$，以及 $x+2^{t-1}$ 和 $y+2^{t-1}$ 连边。

这样连边时间复杂度是 $O(n \alpha \log^2 n)$ 的。

然后利用点 $i-a_i-1$ 和 $i+a_i+1$ 不同求一个 $\operatorname{mex}$ 就可以了。

### 代码

```cpp
const int N=400099,LogN=20;
int n,a[N]={},s[N]={},em=0,e[N]={},nx[N]={},ls[N]={}; bool did[N]={};
void insert(int x,int y) { e[++em]=y,nx[em]=ls[x],ls[x]=em; return ; }
struct Utility {
	int fa[N]={};
	void setup() { for(int i=1;i<=2*n;++i) fa[i]=i; return ; }
	int father(int x) { return fa[x]=fa[x]==x?x:father(fa[x]); }
	void link(int x,int y) { x=father(x),y=father(y); fa[x]=fa[y]=min(x,y); return ; }
	bool same(int x,int y) { return father(x)==father(y); }
} U[LogN]={};
#define lowbit(x) ((x)&-(x))
void link(int x,int y,int t) { if(U[t].same(x,y)) return ; else { U[t].link(x,y); if(t) link(x,y,t-1),link(x+(1<<t-1),y+(1<<t-1),t-1); } return ; }
void Link(int x,int y,int t) { while(t) link(x,y,__lg(lowbit(t))),x+=lowbit(t),y+=lowbit(t),t-=lowbit(t); return ; }
void LINK(int l,int r) { Link(l,2*n-r+1,r-l+1); return ; }
int main()
{
//	usefile("hui");
	int i,j;
	read(n);
	for(i=0;i<LogN;++i) U[i].setup();
	for(i=1;i<=n;++i)
		read(a[i]),LINK(i-a[i],i+a[i]);
	for(i=1;i<=n;++i)
		if(i-a[i]>1&&i+a[i]<n) {
			if(U[0].same(i-a[i]-1,i+a[i]+1)) {
				printf("No\n");
				return 0;
			} else insert(i+a[i]+1,i-a[i]-1);
		}
	for(i=1;i<=n;++i)
		if(U[0].father(i)==i) {
			for(j=ls[i];j;j=nx[j]) did[s[e[j]]]=true;
			s[i]=1; while(did[s[i]]) ++s[i];
			for(j=ls[i];j;j=nx[j]) did[s[e[j]]]=false;
		} else s[i]=s[U[0].father(i)];
	printf("Yes\n"); for(i=1;i<=n;++i) printf("%d ",s[i]); printf("\n");
	return 0;
}
```

---

## 作者：Forg1weN (赞：0)

## [[ABC349G] Palindrome Construction](https://www.luogu.com.cn/problem/AT_abc349_g)

与[P3295 [SCOI2016] 萌萌哒](https://www.luogu.com.cn/problem/P3295)类似的思路。

考虑对于回文串的以 $x$ 为中心左右对称的串可以转换为字符的单点相同问题，例如 $x+k$ 和 $x-k$ 必须相同。

那么运用倍增优化并查集的方法，先将原序列 $A$ 扩展到原来的两倍，且是以原序列为左半边的回文串，然后将 $i$ 位置长度为 $x$ 的限制，即 $[i-x,i-1]$ 必须等于 $[i+1,i+x]$ 转换为等于其在回文串的映射位置，即 $[2n-(i+x)+1,2n-(i+1)+1]$。

然后按照套路的将大并查集区间的相等转换为小并查集区间的相等，可以发现两个区间相等的限制的传递相当于大区间的左边的一一对应以及右边的一一对应。

最后将位置 $i$ 和 $2n-i+1$ 合并，这时一定要相同的位置有相同的祖先，不合法的情况就是存在一个位置，其左右两边相等的区间长度超过了限制，考虑如何判断字典序最小。

将一定不能相同的位置相互连边，位置 $i$ 能够使用的数字是 $1$ 到 $n$ 的集合中除去与 $i$ 相连的位置上填的数字后，第一个没出现的数字，用 set 维护。

时间复杂度 $O(n\log^2 n)$。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
const int mod=1e9+7;
int n,m,tot;
int lg[maxn],a[maxn];
int fa[maxn][25],bs[maxn][25],re[maxn*25];
vector<int>G[maxn];
map<int,int>mp;
set<int>s;
int find(int x,int k) {
	if(fa[x][k]==bs[x][k])return bs[x][k];
	return fa[x][k]=find(re[fa[x][k]],k);
}
void merge(int x,int y,int k) {
	int f1=find(x,k),f2=find(y,k);
	if(f1!=f2)fa[re[f1]][k]=f2;
}
int main() {
	scanf("%d",&n);
	for(int i=2;i<=2*n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=2*n;i++)
		for(int k=0;k<=lg[2*n];k++)
			fa[i][k]=bs[i][k]=++tot,re[tot]=i;
	for(int i=1;i<=n;i++) {
		int x,l1,r1,l2,r2;
		scanf("%d",&a[i]);
		if(a[i]==0)continue;
		x=a[i];
		l1=i-x,r1=i-1,r2=2*n-(i+1)+1,l2=2*n-(i+x)+1;
		for(int k=lg[2*n];k>=0;k--)
			if(l1+(1<<k)-1<=r1) 
				merge(l1,l2,k),l1+=(1<<k),l2+=(1<<k);					
	}
	for(int k=lg[2*n];k>0;k--) {
		for(int i=1;i<=2*n;i++) {
			int pos=re[find(i,k)];
			if(pos==i)continue;
			merge(i,pos,k-1);
			merge(i+(1<<k-1),pos+(1<<k-1),k-1); 
		}
	}
	for(int i=1;i<=n;i++) merge(i,2*n-i+1,0);
	for(int i=1;i<=2*n;i++)find(i,0);
	for(int i=1;i<=n;i++) {
		if(i-a[i]>=2&&i+a[i]<=n-1) {
			if(fa[i-a[i]-1][0]==fa[i+a[i]+1][0]){printf("No");return 0;} 
			G[i-a[i]-1].push_back(i+a[i]+1);
			G[i+a[i]+1].push_back(i-a[i]-1);	
		}
	}
	for(int i=1;i<=n;i++)s.insert(i);
	for(int i=1;i<=n;i++) {
		if(mp[fa[i][0]])continue;
		for(int v:G[i]) 
			if(mp[fa[v][0]])s.erase(mp[fa[v][0]]);
		mp[fa[i][0]]=*s.begin();
		for(auto v:G[i]) {
			if(mp[fa[v][0]])
			s.insert(mp[fa[v][0]]);
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++)
		printf("%d ",mp[fa[i][0]]);
	return 0;
}
```

---

## 作者：RabbieWjy (赞：0)

**题意**

定义一个序列 $T = (T_1,T_2,\cdots,T_M)$ 是回文的，当且仅当 $\forall i = 1,2,\cdots,M : T_i = T_{M - i + 1}$，即翻转过来之后一样。

给定一个长度为 $N$ 的序列 $A$，问是否存在一个长度为 $N$ 的序列 $S$，使得：

- 对于所有 $i = 1,2,\cdots,N$，$(S_{i - A_i},S_{i - A_i + 1},\cdots,S_{i + A_i - 1},S_{i + A_i})$ 是回文的，且 $(S_{i - A_i - 1},\cdots,S_{i + A_i + 1})$ 不是回文的。

如果存在，输出字典序最小的一个。

$1 \le N \le 2 \times 10 ^ 5$，$0 \le A_i \le \min\{i - 1,N - i\}$。

**解法**

看见这个限制，容易想到并查集。发现每个限制是两端长度相等的区间合并，考虑用倍增优化。

类似 [[SCOI2016] 萌萌哒](https://www.luogu.com.cn/problem/P3295)，可以建 $O(\log n)$ 层并查集，把两段区间类似 ST 表合并起来，最后一层一层下传，就把每个点和其他点的关系求出来了。

具体地，第 $i$ 层并查集中，$j$ 这个点代表 $[j,j + 2^i - 1]$ 这个区间。由于合并这个操作是可重复贡献的，合并两段区间 $[L_1,R_1]$ 和 $[L_2,R_2]$ 相当于在第 $k$ 层分别合并 $[L_1,L_1 + 2^k - 1]$ 和 $[L_2,L_2 + 2 ^ k - 1]$ 以及合并 $[R_1 - 2 ^ k + 1,R_1]$ 和 $[R_2 - 2 ^ k + 1,R_2]$，这里的 $k=\lfloor \log _{2} (R_1 - L_1 + 1) \rfloor$。对于下传操作，如果第 $i$ 层中，$[L_1,R_1]$ 和 $[L_2,R_2]$ 在一个并查集里，则在第 $(i - 1)$ 层中，它们的前一半和后一半分别在两个个并查集里。所以，此时要分别合并它们的前一半和后一半。每次合并的时间复杂度是 $O(1)$，下传只需要对每一层，枚举每个区间，时间复杂度是 $O(n\log n)$。

代码：

```cpp
int fnd(int x,int k) {return fa[k][x] = (fa[k][x] == x ? x : fnd(fa[k][x],k));}

void Merge(int l,int r,int k) // 在第 k 层上合并 [l, l + 2^k - 1] 和 [r, r + 2^k - 1]
{
	// printf("*Merge %d %d %d\n",l,r,k);
	l = fnd(l,k),r = fnd(r,k);
	if (l == r) return ;
	if (l < r) swap(l,r);
	fa[k][l] = r;
}

void merge(int l,int ll,int len) // 合并 [l, l + len - 1] 和 [ll, ll + len - 1]
{
	// printf("merge %d %d %d\n",l,ll,len);
	if (l == ll) return ;
	int r = l + len - 1,rr = ll + len - 1;
	int L = (len == 1 ? 0 : log2(len));
	Merge(l,ll,L);
	Merge(r - (1 << L) + 1,rr - (1 << L) + 1,L);
}
```

由于合并的两端区间一个是从前往后的，一个是从后往前的，可以把整个序列反过来拼在后面，把其中一个区间翻到后一半，顺序就一样了。这样就可以直接用上面的东西做了。

在算出点与点之间的关系后，只需要对于每个 $i$，判断 $(i - A_i - 1)$ 和 $(i + A_i + 1)$ 在不在一个并查集里面就行了。最后要输出字典序最小的解，只需要贪心地从前往后放当前能放的、不矛盾的最小数就行了。判断矛不矛盾可以直接暴力做，因为总共只有 $O(n)$ 条这样的限制。

合并的总时间复杂度是 $O(n)$，下传是 $O(n \log n)$，求解是 $O(n)$，总时间复杂度为 $O(n \log n)$。

[AC 提交记录](https://atcoder.jp/contests/abc349/submissions/52398116)。

---

## 作者：Disjoint_cat (赞：0)

# [ABC349G Palindrome Construction](https://www.luogu.com.cn/problem/AT_abc349_g)

注：对于一个序列 $A$，我们令 $\{A_{l,r}\}$ 表示 $A$ 中第 $l$ 到 $r$ 个元素组成的序列。

## 题意

给出长为 $n$ 的序列 $s$，要求构造字典序最小的满足下列条件的，长为 $n$ 的正整数序列 $a$（或报告无解）：

- 对任意的 $1\le i\le n$，$\{a_{i-s_i,i+s_i}\}$ 是回文序列，但 $\{a_{i-s_i-1,i+s_i+1}\}$ 不是（或该区间不合法）。

Data range：$n\le2\times10^5$。

## 题解

前置知识：[Manacher（马拉车）算法](https://www.luogu.com.cn/problem/P3805)。

首先将「回文」的限制转换为元素间的相等和不等的限制：

> 对于任意的 $1\le i\le n$，满足：
>
> 对于任意的 $1\le j\le s_i$，有 $a_{i-j}=a_{i+j}$；但是 $a_{i-s_i-1}\ne a_{i+s_i+1}$。

即使不管「不等」的限制，相等关系也可能有 $\Theta(n^2)$ 组，直接暴力维护显然是不行的。

考虑一个类似马拉车的构造过程。

我们从前向后贪心确定 $a$ 的每一位，同时维护匹配的右端点 $r$ 和该匹配的中点 $p$。

现在我们考虑确定 $a_i$。

- 如果 $i\le r$，那么有 $a_i=a_{2p-i}$，其立刻被确定。
- 如果 $i>r$，那么其与前面的元素没有「相等」的限制。注意到「不等」的限制一共只有 $\Theta(n)$ 组，所以此时求出 $i$ 所有「不等」的位置，求一个 $\operatorname{mex}$ 就能保证字典序最小。

确定之后，再根据 $s_i$ 更新 $r$ 和 $p$ 就可以了。

当所有位确定之后，我们就得到了一个可能的答案 $a$，我们再跑一遍马拉车来 check 是否合法即可。

时间复杂度 $\Theta(n)$。

## 实现

[Submission](https://atcoder.jp/contests/abc349/submissions/52452000)。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define PB emplace_back
#define PPB pop_back
#define MP make_pair
#define ALL(Name) Name.begin(),Name.end()
#define PII pair<int,int>
#define VI vector<int>
#define GI greater<int>
#define fi first
#define se second

const int N=200005;
int n,f[N],a[N],g[N];
VI neq[N];
bool occ[N];

int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
//	int _;cin>>_;while(_--)

	cin>>n;
	for(int i=1;i<=n;i++)cin>>f[i],neq[i+f[i]+1].PB(i-f[i]-1);
	int mxr=0,mxp=0;
	for(int i=1;i<=n;i++)
	{
		if(mxr>=i)a[i]=a[mxp*2-i];
		else
		{
			fill(occ+1,occ+neq[i].size()+2,0);
			for(int j:neq[i])occ[a[j]]=1;
			while(occ[++a[i]]);
		}
		if(i+f[i]>mxr)mxr=i+f[i],mxp=i;
	}
	mxr=1,mxp=1,g[1]=0;a[0]=114514,a[n+1]=1919810;
	for(int i=2;i<=n;i++)
	{
		g[i]=min(mxr-i,g[2*mxp-i]);
		while(a[i+g[i]+1]==a[i-g[i]-1])mxr=i+(++g[i]),mxp=i; 
		if(g[i]!=f[i]){puts("No");return 0;}
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";

	return 0;
}
```

---

