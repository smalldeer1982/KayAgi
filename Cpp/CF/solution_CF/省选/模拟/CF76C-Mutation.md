# Mutation

## 题目描述

Scientists of planet Olympia are conducting an experiment in mutation of primitive organisms. Genome of organism from this planet can be represented as a string of the first $ K $ capital English letters. For each pair of types of genes they assigned $ a_{i,j} $ — a risk of disease occurence in the organism provided that genes of these types are adjacent in the genome, where $ i $ — the 1-based index of the first gene and $ j $ — the index of the second gene. The gene 'A' has index 1, 'B' has index 2 and so on. For example, $ a_{3,2} $ stands for the risk of 'CB' fragment. Risk of disease occurence in the organism is equal to the sum of risks for each pair of adjacent genes in the genome.

Scientists have already obtained a base organism. Some new organisms can be obtained by mutation of this organism. Mutation involves removal of all genes of some particular types. Such removal increases the total risk of disease occurence additionally. For each type of genes scientists determined $ t_{i} $ — the increasement of the total risk of disease occurence provided by removal of all genes having type with index $ i $ . For example, $ t_{4} $ stands for the value of additional total risk increasement in case of removing all the 'D' genes.

Scientists want to find a number of different organisms that can be obtained from the given one which have the total risk of disease occurence not greater than $ T $ . They can use only the process of mutation described above. Two organisms are considered different if strings representing their genomes are different. Genome should contain at least one gene.

## 说明/提示

Explanation: one can obtain the following organisms (risks are stated in brackets): BACAC (11), ACAC (10), BAA (5), B (6), AA (4).

## 样例 #1

### 输入

```
5 3 13
BACAC
4 1 2
1 2 3
2 3 4
3 4 10
```

### 输出

```
5
```

# 题解

## 作者：syksykCCC (赞：17)

感谢 https://blog.csdn.net/V5ZSQ/article/details/81051401

考虑前缀和

用一个$k$位$01$集合表示删字母情况，$0$表示不删，$1$表示删

令$f_i$表示删去集合为$i$后的字符串代价，如果我们求出了每一个$f_i$，就可以像这样统计答案

```cpp
int ans = 0;
for(int i = 0; i < 1 << k; i++)
    if((i & all) == i /* 删去字符在集合中 */ && f[i] <= T /* 符合代价要求 */ && i != all /* 剩余字符串不为空 */)
        ans++;
printf("%d\n", ans);
```
其中$all$表示所有出现字符全集，$T$为代价上限

以下为读入及预处理
```cpp
scanf("%d%d%d%s", &n, &k, &T, s);                          
for(int i = 0; i < n; i++)                                 
{                                                          
	s[i] -= 'A';                                           
	all |= 1 << s[i];                                      
}                                                          
for(int i = 0; i < k; i++) scanf("%d", &t[i]);             
for(int i = 0; i < k; i++)                                 
    for (int j = 0; j < k; j++) scanf("%d", &a[i][j]);     
memset(can, -1, sizeof(can));                              
for(int i = 0; i < k; i++) f[1 << i] = t[i];               
```
将每一种字符的损耗$t_i$存进$f_{2^i}$里，最后使用前缀和累加就可以将其加入每一种情况了

累加$f_i$就是从每一个比$f_i$少一个元素的子集里累加（当然还有自己本来存储的值）

例如$f_{10110} = f_{10110} + f_{00110} + f_{10010} + f_{10100}$
```cpp
for(int i = 0; i < k; i++)           
    for(int j = 0; j < 1 << k; j++)  
        if((j >> i) & 1)             
            f[j] += f[j ^ (1 << i)]; 
```
注意这里累加的其实是$f_j$

**前方高能**

下面考虑如何求出每一个$f$

用$can_i$表示从最近的字符$i$，到当前字符之间的字符集（两端不含），$can$初始化为$-1$，表示该字符自身还没出现过

我们遍历这个字符串，对于每一个字符$s_i$，将它视为删去字符集的右端点（不含），再枚举所有的$k$个字符$j$，将离$s_i$最近的$j$视为删去字符集的左端点（不含），则删去的字符状态即为它们之间的所有种类的字符

注意，并不是所有的$j$都可以和$s_i$匹配，一个合法的$j$应有如下条件

1. 在$s_i$之前出现了字符$j$，代码中体现为`can[j] >= 0`
2. $can_j$中不包含字符$j$和$s_i$，代码中体现为`!((can[j] >> j) & 1) && !((can[j] >> s[i]) & 1)`

如果合法，那么删去两者之间的字符集后，该两个字符将会产生一个新的代价$a_{s_i,j}$，将这个代价加入$f_{can_j}$中，但需要注意的是$f_{can_j|2^{s_i}}$和$f_{can_j|2^j}$这两个不应该存在这个代价的状态将在最终被累加这个代价，所以将它们都减去$a_{s_i,j}$，那此时$f_{can_j|2^j|2^{s_i}}$其实被减去了两遍代价，那么将它加上$a_{s_i,j}$

也就是一个容斥啦
```cpp
f[can[j]] += a[j][s[i]];                         
f[can[j] | (1 << j)] -= a[j][s[i]];              
f[can[j] | (1 << s[i])] -= a[j][s[i]];           
f[can[j] | (1 << j) | (1 << s[i])] += a[j][s[i]];
```

还有两个细节，一是一个$s_i$处理完后，就要将该$can_{s_i}$清空，因为出现了一个新的$s_i$，就是`can[s[i]] = 0`

二是在遍历$k$个字符时，只要该字符出现了，则在容斥（也有可能不容斥）后要标记$j$可以和$s_i$匹配，即`can[j] |= (1 << s[i])`

那么AC代码就出来啦，时间复杂度$\mathcal{O}(nk+k\times 2^k)$，[AC记录](https://www.luogu.org/recordnew/show/19969853)

```cpp
#include <cstdio>
#include <cstring>
const int K = 25;
int n, k, T, all, can[K], t[K], a[K][K], f[1 << K];
char s[200005];
int main() 
{
    scanf("%d%d%d%s", &n, &k, &T, s);
	for(int i = 0; i < n; i++)
	{
		s[i] -= 'A';
		all |= 1 << s[i];
	}
    for(int i = 0; i < k; i++) scanf("%d", &t[i]);
    for(int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) scanf("%d", &a[i][j]);
    memset(can, -1, sizeof(can));
    for(int i = 0; i < k; i++) f[1 << i] = t[i];               
    for(int i = 0; i < n; i++) 
	{
        for(int j = 0; j < k; j++)
            if(can[j] >= 0) 
			{
                if(!((can[j] >> j) & 1) && !((can[j] >> s[i]) & 1)) 
				{
                    f[can[j]] += a[j][s[i]];
                    f[can[j] | (1 << j)] -= a[j][s[i]];
                    f[can[j] | (1 << s[i])] -= a[j][s[i]];
                    f[can[j] | (1 << j) | (1 << s[i])] += a[j][s[i]];
                }
                can[j] |= (1 << s[i]);
            }
        can[s[i]] = 0;
    }
    for(int i = 0; i < k; i++)
        for(int j = 0; j < 1 << k; j++)
            if((j >> i) & 1)
                f[j] += f[j ^ (1 << i)]; 
    int ans = 0;
    for(int i = 0; i < 1 << k; i++)
        if((i & all) == i && f[i] <= T && i != all)
            ans++;
    printf("%d\n", ans);
    return 0;
}
```

### 一些问题

Q： 初始代价好像并没有预处理啊？  
A： 当访问到$s_i$时$can_{s_{i-1}}$必定为$0$，这时就会把$a_{s_i,s_{i-1}}$加入$f_0$中啦，其它情况也同理。

Q： 还不是很清楚怎么办   
A： 可以去看原博客，以及CF上此题的题解

欢迎大家指正，也希望**点个赞**哦！

---

## 作者：Limit (赞：8)

# 题目大意

给出一个由大写字母构成的字符串,定义一个长度为 $n$ 的字符串 $s$ 的代价为 $\sum\limits_{i=1}^{n}g_{s_i,s_{i+1}}$,其中 $g$ 为一个长宽都为字符集大小的矩阵.现在有一种操作可以将某一种字符从字符串中删去,删除每一种字符有不同的代价,求有多少的删字符方案满足代价和小于 $t$.

# 分析

最暴力做法显然是 $\mathcal{O}(2^k\cdot n^2)\sim\mathcal{O}(2^k\cdot n)$ 而且非常不好优化,所以需要换一种思路去考虑.先不去考虑方案而是去考虑删去的字符集,对于一个字符,如果这个字符想要和自己前面的某一个字母连接并产生代价显然这两个字符之间的其他字符必须删除,而且可以与它产生代价的字符的位置必然是前面最后一次出现的位置,否则中间删除字符的时候也会被删去,也就是说对于一个位置他最多只有字符集大小种($\leq22$)不同的代价.现在知道了某次代价这连个字符之间需要删去的字符集为 $S$,产生的代价为 $c=g_{s_x,s_y}$,那么对于所有的 $T$ 满足 $S\subseteq T,s_x\not\in T,s_y\not\in T$ 的集合 $T$ 都要加上这个代价,其中 $s_x\not\in T,s_y\not\in T$ 这两个条件显然可以直接容斥后去除.于是问题转化成了形如「给出一个集合 $S$,要给所有包含 $S$ 的集合 $T$ 都加上一个代价 $c$」这样的问题,可以直接用高维前缀和解决(在一个 $k$ 维,每维只有 $0,1$ 的数组上做的 $k$ 维前缀和(显然任意的一个集合 $S$ 都可以在这个数组中找到一个对应的位置),显然如果某一维中代价在 $0$ 处,那么对于这维为 $0,1$ 的集合都可能产生代价.反之,如果代价在 $1$ 处,那么只要当这维为 $1$ 的集合才可能得到代价,这与转化后的问题相同).

时间复杂度 $\mathcal{O}(nk\log_2k+2^k\cdot k)\sim\mathcal{O}(nk+2^k\cdot k)$.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;last<=i;--i)
namespace IO
//快读模板
using namespace IO;
using namespace std;
const int MAXN=2e5+5;
int n,k,t;
int s[MAXN];
int val[MAXN];
int v[26][26];
bool app[26];
LL sum_=0;
int answer=0;
LL link[5000005];
bool Check(int mask)
{
	LL sum=0;
	REP(i,0,k-1)
	{
		if(!app[i]&&(mask&(1<<i)))
		{
			return 0;
		}
		if(mask&(1<<i))
		{
			sum+=val[i];
		}
	}
	if(sum==sum_)//不能全部删去
	{
		return 0;
	}
	return sum+link[mask]<=t;//将字符串的代价和删除的代价相加与 t 比较
}
int last[MAXN];
int main()
{
	Read(n,k,t);
	char ch;
	REP(i,1,n)
	{
		Read(ch);
		app[ch-'A']=1;
		s[i]=ch-'A';
	}
	REP(i,0,k-1)
	{
		Read(val[i]);
	}
	REP(i,0,k-1)
	{
		if(app[i])
		{
			sum_+=val[i];
		}
	}
	REP(i,0,k-1)
	{
		REP(j,0,k-1)
		{
			Read(v[i][j]);
		}
	}
	PII sor[23];
	REP(i,1,n)
	{
		REP(j,0,k-1)
		{
			sor[j]=make_pair(last[j],j);
		}
		sort(sor,sor+k);
		int mask=0;
		DOW(j,k-1,0)//一次枚举这个可以与 s[i] 产生贡献的在 i 前面的字符
		{
			if(!sor[j].first||sor[j].first<last[s[i]])
			{
				break;
			}
			link[mask]+=v[sor[j].second][s[i]];//容斥部分
			link[mask|1<<sor[j].second]-=v[sor[j].second][s[i]];
			link[mask|1<<s[i]]-=v[sor[j].second][s[i]];
			link[mask|1<<sor[j].second|1<<s[i]]+=v[sor[j].second][s[i]];
			mask|=1<<sor[j].second;
		}
		last[s[i]]=i;
	}
	int top=(1<<k)-1;
	REP(i,0,k-1)//高维前缀和部分
	{
		REP(j,0,top)
		{
			if(j&(1<<i))
			{
				link[j]+=link[j^(1<<i)];
			}
		}
	}
	REP(i,0,top)//最后依次判断每一种删字符方案即可
	{
		answer+=Check(i);
	}
	Writeln(answer);
	return 0;
}
```



---

## 作者：GYHL (赞：1)

~~本蒟蒻第一次写紫题题解，大佬轻喷。~~

[洛谷传送门](https://www.luogu.com.cn/problem/CF76C)

[codeforces传送门](https://codeforces.com/problemset/problem/76/C)

## 题目大意：

题目写的很直白明了，这里不写了。

## 思路：

我们即询问有多少种删除的字符集是合法的，只需要对于每种删除的字符集计算出相邻字符产生的代价即可。

考虑对于两个位置 $(i,j)$，其能产生代价当旦仅当中间的字符被删光且 $i,j$ 都没被删，考虑中间的字符集为 $T$，那么产生贡献的即为所有 $T$ 的不包含 $s_i,s_j$ 的超集 $S$。

首先显然要有 $T$ 不包含 $s_i,s_j$。于是乎我们发现，如果我们钦定了 $i$，再枚举一个字符 $C$，那么 $i$ 右侧第一个字符 $c$ 才有可能产生贡献，那么有贡献的 $(i,j)$ 就只有 $O(nk)$ 对。

考虑对于一组 $(S,a,b)$ 产生的贡献,其中 $a,b$ 表示 $s_i,s_j$，即为不可删的字符。我们只需要对 $f_s,f_{s\cup a,b}$ 进行一个 $+m_{a,b}$ 的贡献，$f_{s\cup \{a\}},f_{s\cup \{b\}}$，进行一个 $-m_{a,b}$ 的贡献即可。

然后我们对 $f$ 进行[高维前缀和](https://www.luogu.me/article/1ttf3bxa)即可得到代价数组 $g$。

这样的话时间复杂度为 $O(n\cdot k+2^k\cdot k)$。

## 代码：
[AC记录](https://vjudge.net/solution/58496382)

```cpp
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10, K = 25;
int n, k, T, sum, b[K], t[K], a[K][K], f[1 << K], ans;
string s;

void init() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k >> T >> s;
	for (int i = 0; i < n; i++) {
		s[i] -= 'A';
	}
	for (int i = 0; i < n; i++) {
		sum |= 1 << s[i];
	}
	for (int i = 0; i < k; i++) {
		cin >> t[i];
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cin >> a[i][j];
		}
	}
	return ;
}

int main() {
	init();
	memset(b, -1, sizeof b);
	for (int i = 0; i < k; i++) {
		f[1 << i] = t[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (b[j] >= 0) {
				if (!((b[j] >> j) & 1) && !((b[j] >> s[i]) & 1)) {
					f[b[j]] += a[j][s[i]];
					f[b[j] | (1 << j)] -= a[j][s[i]];
					f[b[j] | (1 << s[i])] -= a[j][s[i]];
					f[b[j] | (1 << j) | (1 << s[i])] += a[j][s[i]];
				}
				b[j] |= (1 << s[i]);
			}
		}
		b[s[i]] = 0;
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 1 << k; j++) {
			if ((j >> i) & 1) {
				f[j] += f[j ^ (1 << i)];
			}
		}
	}
	for (int i = 0; i < 1 << k; i++) {
		if ((i & sum) == i && f[i] <= T && i != sum) {
			ans++;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：wurzang (赞：1)

考场上傻逼没做出来这题，于是来写个题解

首先发现复杂度在 $2^k \times k$ 的时候是能过的（

考虑 dfs 每个字符的删除状态，发现瓶颈在于如何求出删除后相邻两个字符的贡献。

这个贡献可以先考虑一个 naive 的 $n^2$ 预处理，枚举两个点对 $(i,j)$ ，发现只有在 $[i+1,j-1]$ 字符全部删除的时候才能造成贡献，于是算一下 $[i+1,j-1]$ 字符的状态。然而，点对 $(i,j)$ 也可以对以 $[i+1,j-1]$ 字符为子集的删除状态造成贡献。对于这部分的贡献直接上 FWT 即可。

然而还有一个限制是 $i$ 字符和 $j$ 字符不能被删除任意一个，套上一个小容斥即可。具体看代码。

考虑怎么把 $n^2$ 优化。枚举 $i$ 的过程中，同时有两个点 $j_1$,$j_2$ 满足 $ch_{j_1}=ch_{j_2}$ 时，显然这个 $j_2$ 是没有用处的。

所以每个字符只需要找一遍即可，也就是说我们可以以 $\mathcal{O}(nk)$ 的复杂度去预处理。

时间复杂度为 $\mathcal{O}(2^k \times k)$，瓶颈在于 FWT。顺便一提 FWT 在 $k\le 22$ 的时候都是能过的，$k=23$ 就不行。~~自己sb觉得过不去就没写头铁去刚另一题~~


代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pii pair<int,int>
#define poly vector<int>
typedef long long ll;
const int N=2e5+5,M=30;
int chr[N],R[N];
ll b[M][M],a[M],val[1<<22],vv[M];
int vis[M],n,k,T,ans,all;
void dfs(int x,int st,ll sum){
	if(sum>T) return;
	if(x==k) return (void)(ans+=(sum+val[st]<=T && st!=all));
	if(vis[x]) dfs(x+1,st|(1<<x),sum+a[x]);
	dfs(x+1,st,sum+vv[x]);
}
poly pos[M];
pii p[M];int cnt;
void FWT(ll *f,int n){
	for(int p=2;p<=n;p<<=1){
		int len=p>>1;
		for(int i=0;i<n;i+=p)
			for(int st=i;st<i+len;++st)
				f[st+len]+=f[st];		
	}

}
signed main(){
	//freopen("untitled.in","r",stdin);
	//freopen("untitled.out","w",stdout);
	cin>>n>>k>>T;char ch;
	for(int i=1;i<=n;++i){
		cin>>ch;
		chr[i]=ch-'A';
		vis[chr[i]]=1;
		all|=(1<<chr[i]);
		pos[chr[i]].push_back(i);
	}
	for(int i=0;i<k;++i)
		sort(pos[i].begin(),pos[i].end());
	for(int i=0;i<k;++i)
		cin>>a[i];
	for(int i=0;i<k;++i)
		for(int j=0;j<k;++j)
			cin>>b[i][j];
	for(int i=2;i<=n;++i)
		if(chr[i]==chr[i-1]) vv[chr[i]]+=b[chr[i]][chr[i-1]];
		else R[i]=i+1;
	for(int i=1;i<n;++i){
		if(chr[i]==chr[i+1]) continue;
		int st=0;
		cnt=0;
		for(int j=0;j<k;++j)
			if(!pos[j].size() || pos[j].back()<=i) continue;
			else{
				int Pos=lower_bound(pos[j].begin(),pos[j].end(),i)-pos[j].begin();
				if(chr[i]==j && pos[j].size()>1) p[++cnt]=make_pair(pos[j][Pos+1],j);
				else p[++cnt]=make_pair(pos[j][Pos],j);
				//cout<<i<<" "<<char(j+'A')<<" "<<pos[j][Pos]<<endl;
			}
		sort(p+1,p+cnt+1);
		for(int j=1;j<=cnt;++j){
			if(i==p[j].fi) continue;
			int tmp=b[chr[i]][p[j].se];
		//	cout<<i<<" "<<p[j].fi<<" "<<char(p[j].se+'A')<<" "<<tmp<<" "<<st<<" shabi\n";
			val[st]+=tmp;
			val[st|(1<<chr[i])]-=tmp;
			val[st|(1<<p[j].se)]-=tmp;
			val[st|(1<<p[j].se)|(1<<chr[i])]+=tmp;
			if(p[j].se==chr[i]) break;
			st|=(1<<p[j].se);
		} 
	}
//	for(int i=0;i<1<<k;++i)
//		cout<<val[i]<<" ";cout<<endl;
	FWT(val,(1<<k));
//	for(int i=0;i<1<<k;++i)
//		cout<<val[i]<<" ";cout<<endl;
	dfs(0,0,0);
	cout<<ans;
	return 0;
}
```


---

## 作者：xtx1092515503 (赞：1)

考试时写出正解，然后忘记把离散化的代码某个地方处理一下避免越界，然后就RE了……

------------

首先，看到 $k=22$，我们第一反应就是 $2^k$ 枚举所有集合检验（正常人的想法）。但是，我们检验不可能真的每次 $O(|s|)$ 地扫一遍整个串。考虑进行一些预处理。

我们考虑某个字符 $s_i$。在删除某个集合 $S_1$ 中所有字符后，它后面的字符成了 $s_{j_1}$；在删掉某个 $S_2$ 中所有字符后，它后面的字符就成了 $s_{j_2}$……

假设我们删去了某个集合 $S$。则，只要 $S_k\subseteq S$，我们就存在一对邻字符 $(s_i,s_{j_k})$；

但是，这个的前提必须是 $s_i$ 与 $s_{j_k}$ 均未被删去。于是，我们得出了，假设存在一个三元组 $(s_i,S_k,s_{j_k})$，则所有具有 $S_k\subseteq S$ 且 $s_i\notin S$ 且 $s_{j_k}\notin S$ 的 $S$ 均是会得到一个贡献 $a_{s_i,s_{j_k}}$ 的 $S$。

我们考虑令 $f_S$ 表示删去集合 $S$ 中的所有字符后，剩余串的答案。则我们发现，三元组 $(s_i,S_k,s_{j_k})$——假如我们把整个 $f_S$ 看作一个 $n$ 维的超立方体（其中第 $i$ 维表示第 $i$ 个字符有无被删去）的话——会对 $f_S$ 中某个子超立方体做出贡献（准确地说，是 $S_k$ 中所有维恒为 $1$，同时 $s_i,s_{j_k}$ 维恒为 $0$ 的子超立方体）。显然这个可以通过一个**高维前缀和**在 $O(k2^k)$ 时间内得出（不懂高维前缀和的自行百度）。

则我们现在的问题就转变成了如何求出所有的 $(s_i,S_k,s_{j_k})$。显然对于一个位置 $s_i$，我们可以找出它之后第一个出现的字符 $c$ 出现在哪个位置，记作 $nex_c$。则我们对于 $s_i$，将所有字符 $c$ 按照 $nex_c$ 从小到大排序，记顺序为 $ord$。则删去 $ord$ 的一个前缀 $[ord_1,ord_p]$，便会出现邻字符 $(s_i,ord_{p+1})$，而要删去的东西就是前缀里的东西。即，对于位置 $i$，它所有的三元组即为

$$(s_i,\bigvee\limits_{q=0}^{p-1}ord_q,ord_p)$$

注意到当 $s_i=ord_p$ 时是最后一个三元组，因为此时删完 $ord_p$ 后，字符 $s_i$ 便不再存在了。

则在求出每个位置的 $ord$ 后即可 $O(k)$ 地扫一遍求出所有的三元组。

现在关键在于如何求出 $ord$。显然 $nex$ 数组直接倒着扫一遍即可得到。则 $ord$ 数组直接排序即可，可以 $O(k\log k)$ 直接 ```sort``` 一遍；当然观察到位置 $i$ 的 $nex$ 比起位置 $i+1$ 来看只有一个位置改变了，也可以 $O(k)$ 地插入排序；不过都能过就是了。图方便当然选择直接 ```sort```。

注意到删去每个字符的代价也可以在高维前缀和的过程中就一并求出了。同时注意到未出现的字符不能被删去，注意离散化一下即可。

时间复杂度 $O\Big(k(2^k+|s|)\Big)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,S,lim,res,ord[30],nex[30],g[30][30],id[30];
ll f[1<<22];
char s[200100];
int main(){
	scanf("%d%d%d",&S,&n,&m);
	scanf("%s",s);for(int i=0;i<S;i++)s[i]-='A',id[s[i]]=1;
	for(int i=1;i<=n;i++)id[i]+=id[i-1];
	for(int i=0;i<n;i++)id[i]--;
	for(int i=n-1;i>=1;i--)if(id[i]==id[i-1])id[i]++;
	id[0]=0; 
	for(int i=0;i<n;i++)scanf("%lld",&f[1<<id[i]]),ord[i]=i;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)scanf("%d",&g[id[i]][id[j]]);
	n=id[n],lim=(1<<n);
//	for(int i=0;i<n;i++)printf("%d ",f[1<<id[i]]);puts("");
//	for(int i=0;i<n;i++){for(int j=0;j<n;j++)printf("%d ",g[i][j]);puts("");}
	for(int i=0;i<S;i++)s[i]=id[s[i]];
	for(int i=0;i<n;i++)nex[i]=0x3f3f3f3f;
	for(int i=S-2;i>=0;i--){
		nex[s[i+1]]=i+1;
		sort(ord,ord+n,[](int u,int v){return nex[u]<nex[v];});
		for(int j=0,k=0;j<n&&nex[ord[j]]!=0x3f3f3f3f;j++){
			f[k]+=g[s[i]][ord[j]];
			f[k|(1<<s[i])]-=g[s[i]][ord[j]];
			f[k|(1<<ord[j])]-=g[s[i]][ord[j]];
			f[k|(1<<s[i])|(1<<ord[j])]+=g[s[i]][ord[j]];
			if(ord[j]==s[i])break;
			k|=(1<<ord[j]);
		}
	}
	for(int j=0;j<n;j++)for(int i=1;i<lim;i++)if(i&(1<<j))f[i]+=f[i^(1<<j)];
	for(int i=0;i<lim-1;i++)res+=(f[i]<=m);
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：KingPowers (赞：0)

因为 $k\le 22$，容易想到暴力枚举删除了哪些字符，然后接下来要做的就是快速统计代价。

考虑删完后的相邻字符比较困难，因此我们拆下贡献，思考点对 $(l,r)$ 的贡献。如果 $s_l,s_r$ 最终是挨在一起的，那么首先需要满足 $\forall i\in[l+1,r-1]$，$s_i$ 不能和 $s_l$ 或 $s_r$ 相等，因为我们需要将中间删空，相等会把两个端点一块删掉。

继续深入分析，我们可以发现一点：有效的 $(l,r)$ 对数只有 $O(nk)$ 种！考虑固定 $r$，那么所有合法的 $l$ 一定是当前每种字符出现得最靠右的位置，否则 $[l+1,r-1]$ 之间一定就会出现和 $s_l$ 相同的字符。

因为点对数不多，所以我们就可以考虑每种点对会对哪些删除方式造成贡献了。我们记 $[l+1,r-1]$ 的字符集合为 $mask$，那么对于所有删除集合 $S$，所有满足 $mask$ 是 $S$ 子集且 $S$ 没有删除 $s_l$ 和 $s_r$ 的 $S$ 代价要加上 $s_l$ 和 $s_r$ 相邻的贡献。

稍微容斥一下，包含了 $mask$ 的状态加上，包含了 $mask$ 和 $s_l$ 的状态减去，包含了 $mask$ 和 $s_r$ 的状态也减去，最后再给同时包含 $msk,s_l,s_r$ 的状态加回来。

可以通过先单点加再算子集和的方式来统计贡献，子集和直接使用高维前缀和。

小细节：枚举删除集合的时候要判掉包含了原串中没有的字符的情况。

时间复杂度实现精细可以做到 $O(nk+k2^k)$，但是我比较懒直接写的 $O(nk^2+k2^k)$。

```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define deb(x) cerr << #x"=" << x << '\n';
using namespace std;
const int N = 5e5 + 5;
int n, k, lim;
int t[26], c[26][26], f[(1 << 22) + 5], pos[26];
string s;
void Solve(){
	cin >> n >> k >> lim >> s;
	s = ' ' + s; int all = 0;
	For(i, 1, n) all |= (1 << s[i] - 'A');
	For(i, 0, k - 1) cin >> t[i];
	For(i, 0, k - 1) For(j, 0, k - 1) cin >> c[i][j];
	For(r, 1, n){
		For(tmp, 0, k - 1){
			if(!pos[tmp]) continue;
			int msk = 0, l = pos[tmp];
			int cl = s[l] - 'A', cr = s[r] - 'A';
			if(pos[cr] > l) continue;
			For(tt, 0, k - 1) if(pos[tt] > l && pos[tt] < r) msk |= 1 << tt;
			//cerr << "l:" << l << " r:" << r << " " << s[l] << cl << " " << s[r] << cr << '\n';
			f[msk] += c[cl][cr];
			//assert(msk < (1 << 22));
			f[msk | (1 << cl)] -= c[cl][cr];
			f[msk | (1 << cr)] -= c[cl][cr];
			f[msk | (1 << cl) | (1 << cr)] += c[cl][cr];
		}
		pos[s[r] - 'A'] = r;
	}
	For(j, 0, k - 1) For(i, 0, (1 << k) - 1)
		if((i >> j) & 1) f[i] += f[i ^ (1 << j)];
	int ans = 0;
	For(i, 0, (1 << k) - 1){
		int cost = f[i], app = 1;
		For(j, 0, k - 1)
			if((i >> j) & 1) cost += t[j], app &= (all >> j) & 1;
		if(app && cost <= lim && (i & all) != all) ans++;
	}
	cout << ans << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：chenxia25 (赞：0)

这是当年模拟赛的题，当时我不会高维前缀和，被 ymxdd 了/kk

---

**[Portal]( https://www.luogu.com.cn/problem/CF76C )**

首先我们考虑枚举每个删除字符的集合，对于每个集合都算出代价判一下。代价显然分为删除字符后得到的字符串中相邻字符对的总代价，加上删除字符的代价。后者显然随便求就可以了，难点在于前者。

如果想对于每个删除集合，单独算出前者代价，那是没有前途的。我们注意到，在删除一些字符后剩下来的字符串中，我们可以看做每个相邻字符对的左边那个字符对它做了一些贡献。于是我们考虑转换贡献体，换成左边字符，就是说对于每个字符，我们考虑它能作为相邻字符对中的左边字符影响哪些删除集合并贡献上去。

于是我们枚举字符，对于每个字符，考虑它后面能够接哪些字符（或是最后一个，后面不接，或当前字符不存在），对于接不同字符的贡献是不同的。对于它后面接字符 $x$，那么它在原串中的位置显然是当前枚举到的字符后的第一个 $x$，中间那些全要删掉，$x$ 和当前字符必须留下，其他的字符就删不删没关系，这时候贡献是当前字符与 $x$ 相邻时的代价。那么显然一共有 $\mathrm O(m)$ 种情况，随便维护一下即可。

那么对于每种情况，它能贡献到的删除集合的集合显然是：那些必须删和那两个必须不删的是固定的，其他 $0/1$ 均可。这个该如何维护呢？这个范围显然是个 $m$ 维超立方，考虑高维差分，最后再高维前缀和回去。但是众所周知，高维差分是我所不会 $\mathrm O(m)$（或者可能根本就不可做），那怎么办呢？注意到差分中的一个特例，如果某维的 $r+1$ 要大于值域，那它就不会起效果，可以忽略；在本题中，如果超立方的某维的右端点等于 $1$ 那就不用给总复杂度乘以 $2$。那显然 $0/1$ 均可和必须删的都是 $r=1$，只有两个是 $r=0$，那差分就是常数级别了。注意这两个可能重合，讨论一下即可。

**_[code]( https://www.luogu.com.cn/paste/uot8yv3i )_**

---

