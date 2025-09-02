# [NOI Online 2021 提高组] 积木小赛

## 题目描述

Alice 和 Bob 最近热衷于玩一个游戏——积木小赛。

Alice 和 Bob 初始时各有 $n$ 块积木从左至右排成一排，每块积木都被标上了一个英文小写字母。

Alice 可以从自己的积木中丢掉任意多块（也可以不丢）；Bob 可以从自己的积木中丢掉最左边的一段连续的积木和最右边的一段连续的积木（也可以有一边不丢或者两边都不丢）。两人都不能丢掉自己所有的积木。然后 Alice 和 Bob 会分别将自己剩下的积木按原来的顺序重新排成一排。

Alice 和 Bob 都忙着去玩游戏了，于是想请你帮他们算一下，有多少种不同的情况下他们最后剩下的两排积木是相同的。

两排积木相同，当且仅当这两排积木块数相同且每一个位置上的字母都对应相同。

两种情况不同，当且仅当 Alice（或者 Bob）剩下的积木在两种情况中不同。

## 说明/提示

对于所有测试点：$1\le n \le 3000$，$s$ 与 $t$ 中只包含英文小写字母。

测试点 $1$ 满足：$n\le3000$，$s$ 与 $t$ 中只包含同一种字母。

测试点 $2,3,4$ 满足：$n\le100$。

测试点 $5,6,7$ 满足：$n\le500$。

测试点 $8,9,10$ 满足：$n\le3000$。

感谢 [w33z8kqrqk8zzzx33](https://www.luogu.com.cn/user/220037) 提供测试数据。

## 样例 #1

### 输入

```
5
bcabc
bbcca```

### 输出

```
9```

## 样例 #2

### 输入

```
20
egebejbhcfabgegjgiig
edfbhhighajibcgfecef```

### 输出

```
34```

# 题解

## 作者：syksykCCC (赞：88)

大概是目前题解区最短的了。

因为 $s$ 串选择的是子序列，$t$ 串选择的是子串，所以显然 $t$ 的限制更严格，考虑枚举 $t$ 的子串 $t[i, j]$。

固定 $i$ 不动，$j$ 往后移动的时候，同时维护一个指针 $p$ 贪心的从前往后扫描 $s$ 串看是否还存在相同子序列。如果存在，把当前 $t[i, j]$ 的哈希值（一个 `long long` 大模数就行了）存到一个数组 $res$ 中。

枚举完了以后，把 $res$ 数组排序、去重，输出不一样的元素个数就行了。

时间复杂度其实也是 $O(n^2 \log n)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3005, BASE = 51971;
const long long M = 2005091020050911;
int n;
char a[N], b[N];
long long t[N * N];
int main()
{
	scanf("%d %s %s", &n, a + 1, b + 1);
	for(int i = 1; i <= n; i++)
	{
		long long v = 0; int p = 1;
		for(int j = i; j <= n; j++)
		{
			while(p <= n && a[p] != b[j]) p++;
			if(p > n) break;
			p++;
			v = (1LL * v * BASE + b[j] - 'a' + 1) % M;
			t[++t[0]] = v;
		}
	}
	sort(t + 1, t + t[0] + 1);
	printf("%d\n", unique(t + 1, t + t[0] + 1) - t - 1);
	return 0;
}
```

---

## 作者：一叶知秋。 (赞：31)

为啥 $\text{hash}$ 是正解啊 /baojin

像 $\text{hash}$ 这样的算法，就应当爪巴（误

算法主要流程比较简单：枚举 $T$ 左端点，右端点从左端点扫过去，看 $S$ 串中是否合法，具体实现拿个指针扫过去即可

然而这道题瓶颈在判重...

考虑 $\text{hash}$ 肯定不会是正解（然而是的），而且 $O(n^2)$ 可以通过，我们直接考虑暴力判重

设 $f_{i,j}$ 为以 $i$ 为开头的后缀跟以 $j$ 为开头的后缀的 $LCP$

转移暴力转移，倒着枚举 $i$ 可以 $O(1)$ 转移

然后边转移边做枚举，直接从 $i+\max\limits_{k>i}\{f_{k,i}\}$ 开始转移即可，时间复杂度 $O(n^2)$

```cpp
#include<cstdio>
#include<cctype>

#define maxn 3333

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

template<class T>

inline T max(T a,T b){
	return a>b?a:b;
}

int n,ans,len[maxn][maxn];

char s[maxn],t[maxn];

int main(){
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	n=read<int>();
	scanf("%s\n%s",s+1,t+1);
	for(int i=n;i>=1;i--){
		int Max=0;
		for(int j=i+1;j<=n;j++)
			Max=max(Max,len[j][i]);
		int k=1;
		for(int j=i;j<i+Max;j++){
			while(k<=n&&(s[k]^t[j]))k++;
            if(k>n)break;
			k++;
		}
		for(int j=i+Max;j<=n;j++){//枚举右端点
			while(k<=n&&(s[k]^t[j]))k++;//指针直接扫
			if(k>n)break;
			k++;
			ans++;
		}
		for(int j=1;j<=n;j++)//转移
			if(t[i]==t[j])len[i][j]=len[i+1][j+1]+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Karry5307 (赞：26)

### 题意

给定两个长度为 $n$ 的字符串 $S$ 和 $T$，求 $T$ 中有多少本质不同的子串是 $S$ 的子序列。

$\texttt{Data Range:}1\leq n\leq 3\times 10^3$。

### 题解

比较简单。

对 $S$ 建立子序列自动机，这样就可以串长复杂度的看一个串是否为 $S$ 的子序列了。

由于子序列自动机是可以一个一个加字符匹配，所以可以直接枚举左端点然后从左往右枚举右端点。

至于考虑本质不同的串的话就哈希一下就好了。

由于可以通过构造 $\texttt{ab}$ 串来使答案大小为 $3\times 10^6$ 量级，所以哈希时候模数要设的比较大。（~~我不会告诉你我随机构造 $\texttt{ab}$ 串卡掉了某位同学的双哈希~~）

然后为了常数需要手写哈希表，本机测 $n=3000$ 的 $\texttt{ab}$ 串的时候 map 4s 手写哈希 0.3s。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=9e6+51;
const li MOD1=8530716171517,MOD2=8530716771587;
struct HashTable{
	const ll MOD=8530771;
	ll tot;
	ll last[MAXN],prev[MAXN/2];
	li hsh1[MAXN/2],hsh2[MAXN/2];
	inline void insert(li hv1,li hv2);
	inline ll query(li hv1,li hv2);
};
HashTable hsh;
ll n,res,cur;
li hsh1,hsh2;
ll nxt[3051][27];
char s[3051],t[3051];
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
inline void HashTable::insert(li hv1,li hv2)
{
	ll x=hv1%MOD;
	prev[++tot]=last[x],hsh1[tot]=hv1,hsh2[tot]=hv2,last[x]=tot;
}
inline ll HashTable::query(li hv1,li hv2)
{
	ll x=hv1%MOD;
	for(register int i=last[x];i;i=prev[i])
	{
		if(hsh1[i]==hv1&&hsh2[i]==hv2)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	n=read(),scanf("%s%s",s+1,t+1);
	for(register int i=n;i;i--)
	{
		memcpy(nxt[i-1],nxt[i],sizeof(nxt[i])),nxt[i-1][s[i]-'a']=i;
	}
	for(register int i=1;i<=n;i++)
	{
		cur=hsh1=hsh2=0;
		for(register int j=i;j<=n;j++)
		{
			if(!(cur=nxt[cur][t[j]-'a']))
			{
				break;
			}
			hsh1=(hsh1*131+t[j]-'a'+1)%MOD1,hsh2=(hsh2*131+t[j]-'a'+1)%MOD2;
			!hsh.query(hsh1,hsh2)?hsh.insert(hsh1,hsh2),res++:1;
		}
	}
	printf("%d\n",res);
}
```

---

## 作者：KaguyaH (赞：20)

考虑 $\mathcal O(n^2)$ 枚举 $t$ 中的子串 $t_{[i, j]}$。

问题变为：判断此前是否枚举过本质相同的子串；判断 $t_{[i, j]}$ 是否为 $s$ 的子序列。

---

对于前者，考虑找到 $t$ 中首个与 $t_{[i, j]}$ 本质相同的子串 $t_{[x, y]}$，判断 $y=j$ 是否成立。

想到 $\mathcal O(n + m)$ 的 KMP 算法，考虑迁移到本题。

首先我们枚举 $i$，然后对于 $t_{[i, n]}$ 建出 KMP 的 $next$ 数组。

假设我们已经找到了首个与 $t_{[i, j - 1]}$ 本质相同的子串，其结尾为 $k$，那么我们利用 KMP 的思想可以找到首个与 $t_{[i, j]}$ 本质相同的子串。

---

对于后者，考虑定义 $r_{i, j}$ 为 $s_i$ 后第一个字符 $j$ 的位置，若 $s_i$ 后没有字符 $j$，则为 $n + 1$。

假设 $s$ 第一个与 $t_{[i, j - 1]}$ 相同的子序列的结尾为 $p$，则第一个与 $t_{[i, j]}$ 相同的子序列结尾为 $r_{p, t[j]}$，判断是否不大于 $n$ 即可（若大于 $n$ 则说明没有找到）。

---

还是比较简洁的做法吧，核心代码 25 行，跑得也很快。

时间复杂度 $\mathcal O(n^2)$，空间复杂度 $\mathcal O(n)$，空间上有 $26$ 的常数。

---

```cpp
# include <cstdio>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
        struct __FILE {
            __FILE() { freopen("block.in", "r", stdin), freopen("block.out", "w", stdout); }
            compl __FILE() { fclose(stdin), fclose(stdout); }
        } ____FILE;
    }
    using namespace Source;
    enum { N = 3000 };
    static hu n;
    static char s[N + 2], t[N + 2];
    static hu r[N + 1]['z' - 'a' + 1];
    static hu next[N + 1];
    static uint ans;
    static inline const void main() {
        scanf("%hu", &n);
        scanf("%s%s", s + 1, t + 1);
        for (char i('a'); i <= 'z'; ++i) r[n][i - 'a'] = n + 1;
        for (register hu i(n - 1); i < n; --i) {
            for (char j('a'); j <= 'z'; ++j) r[i][j - 'a'] = r[i + 1][j - 'a'];
            r[i][s[i + 1] - 'a'] = i + 1;
        }
        for (register hu i(1); i <= n; ++i) {
            next[1] = next[0] = 0;
            for (register hu j(2); i + j - 1 <= n; ++j) {
                next[j] = next[j - 1];
                while (next[j] and t[i + j - 1] != t[i + next[j]]) next[j] = next[next[j]];
                next[j] += t[i + j - 1] == t[i + next[j]];
                // printf("%hu %hu %hu\n", i, j, next[j]);
            }
            hu p(0);
            for (register hu j(i), k(0), l(0); j <= n and p <= n; ++j) {
                while (k <= n and i + l <= j) {
                    while (i + l <= j and l and t[k + 1] != t[i + l]) l = next[l];
                    if (t[++k] == t[i + l]) ++l;
                    // printf("%hu %hu %hu %hu\n", i, j, k, l);
                }
                p = r[p][t[j] - 'a'];
                if (k == j) ans += p <= n;
            }
        }
        printf("%u\n", ans);
    }
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：A_zjzj (赞：9)

### 题目概述：
给你两个长度为 $n$ 的字符串 $a,b$，你需要找出 $b$ 中有多少个**不同**的子串是 $a$ 的子序列

### 思路：
可以枚举 $a$ 中的子串，可是这样可能会有多个相同的子串被算了多次，那么，我们就可以用 $Trie$ 树，然后从根节点开始向下搜，枚举每一个子串，看一下在 $a$ 中有没有。

很显然，如果当前的这个子串已经不匹配了，那么就没有再搜下去的必要。

然后，我们可以用一个 $nex_{i,c='a'to'z'}$ 数组表示在字符串 $a$ 中，第 $i$ 个字符之后的最近的一个 $c$ 的字符，这个处理可以 $O(26n)$ 处理出来，具体见代码。这样就可以边向下搜，边记录匹配到 $a$ 数组的哪一位，显而易见，肯定是跳到距离当前位置最近的位置是最优的。

最后，你会发现字典树需要 $n*n$ 级别个节点，显然会 MLE，为了省去这个 $26$ 倍的常数，就用链式前向星存边，这样只不过时间上会增加 $26$ 倍，不过并无大碍。

### 代码：
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=3e3+10;
int n,inx[N],nex[N][26];
char a[N],b[N];
struct edges{
	int to,w,nex;
}edge[N*N];
int head[N*N],kk;
void add(int u,int v,int w){
	edge[++kk]=(edges){v,w,head[u]};head[u]=kk;
}
int cnt;
void clear(){cnt=0;}
void insert(int x){//将字符串b中的x-n位加入字典树
	int rt=0;
	for(int i=x;i<=n;i++){
		bool flag=0;
		for(int j=head[rt];j;j=edge[j].nex){
			if(edge[j].w==b[i]-'a'){
				flag=1;rt=edge[j].to;
				break;
			}
		}
		if(!flag){//没有下一条边
			add(rt,++cnt,b[i]-'a');
			rt=cnt;
		}
	}
}
int ans;
void dfs(int u,int x){
	for(int i=head[u];i;i=edge[i].nex){
		if(nex[x][edge[i].w]==-1)continue;
		ans++;//搜到下一个点说明匹配成功
		dfs(edge[i].to,nex[x][edge[i].w]);
	}
}
int main(){
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	clear();
	scanf("%d%s%s",&n,a+1,b+1);
	memset(inx,-1,sizeof(inx));
	for(int i=n;i>=0;i--){
		for(int j=0;j<26;j++)nex[i][j]=inx[j];
		if(i)inx[a[i]-'a']=i;
	}
	for(int i=1;i<=n;i++)insert(i);
	dfs(0,0);
	printf("%d",ans);
	return 0;
}
```
### 谢谢--zhengjun

---

## 作者：KSToki (赞：7)

# 题目大意
给定两个长度为 $n$ 的字符串 $s$ 和 $t$，问有多少 $t$ 的不同的子串是 $s$ 的子序列，定义不同为长度不同或至少有一个位置的字母不同。
# 题目分析
本场最水的题，没有之一。

先考虑不去重，由于对 $s$ 的要求比较松，直接两重循环枚举 $t$ 的子串，然后内层一个指针表示当前匹配到第几位，如果当前位匹配失败直接跳出循环。有点类似于尺取法，时间复杂度为 $O(n^2)$。

这里用的去重方法是散列表（哈希表），由于搞除法要出问题，所以直接用 $O(n^2)$ 预处理出哈希数组 $Hash[i][j]$，表示 $t$ 从 $i$ 到 $j$ 的哈希值。注意去重判断应该放在累计答案处，如果在进入循环处判断相当于跳过了当前匹配。举个例子，baa 和 aab，当到第二个 a 时由于没有进入匹配，它会认为 ab 是合法的答案。
# 代码
~~如果没人对着模数卡~~时空复杂度均为 $O(n^2)$，跑起来有一点慢，去掉宏定义代码还是很短的。

~~请忽略考场代码中用于膜人的变量名~~。
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,ans;
char s[3001],t[3001];
ull Hash[3001][3001];
const int Base=20050913,Mod=1145141;
vector<ull>Hash_table[Mod];
I bool check(int l,int r)
{
	int HC=Hash[l][r]%Mod;
	int green_orange=Hash_table[HC].size();
	bool PG=0;
	for(R int i=0;i<green_orange;++i)
		if(Hash_table[HC][i]==Hash[l][r])
		{
			PG=1;
			break;
		}
	if(PG)
		return 0;
	Hash_table[HC].push_back(Hash[l][r]);
	return 1;
}
int main()
{
	n=read();
	scanf("%s",s+1);
	scanf("%s",t+1);
	for(R int i=1;i<=n;++i)
		for(R int j=i;j<=n;++j)
			Hash[i][j]=Hash[i][j-1]*Base+t[j]-'a'+1;
	for(R int i=1;i<=n;++i)
		for(R int j=i,k=1;j<=n;++j)
		{
			while(k<=n&&s[k]!=t[j])
				++k;
			if(k>n)
				break;
			if(check(i,j))
				++ans;
			++k;
		}
	putint(ans);
	return 0;
}
```

---

## 作者：wsyhb (赞：5)

## 题意简述

给定两个长度为 $n$ 的字符串 $S$ 和 $T$，求 $S$ 中有多少个本质不同子序列是 $T$ 的子串。

**数据范围**：$n \le 3000$，字符集 $\Sigma=\{a,b,\cdots,z\}$。

## 题解

由于 $T$ 的子串只有 $O(n^2)$ 个，再加上**判断一个字符串是否是另一个字符串的子序列只需贪心选取**，我们只需**求出所有满足题意的 $T$ 的子串然后去重**。

具体来说，枚举 $T$ 子串的左端点 $l$，依次考虑右端点为 $l,l+1,\cdots,n$，每次在 $S$ 中找到上一次位置以后，第一个与 $T$ 当前字符相同的位置。对于每个左端点只会遍历一次 $S$，因此是 $O(n^2)$ 的。

而**求本质不同的字符串个数**，容易想到 Hash。直接排序或者使用 map 是 $O(n^2\log{n})$ 的，似乎不太可行。再加上正确率的考虑，笔者使用了另一种方法：**使用桶排的思想对同一长度的子串进行排序**。（当然可以使用其它字符串数据结构，但本人太菜了想不到）

具体做法：依次考虑长度为 $1,2,\cdots,n$ 的子串，设当前考虑的长度为 $l$，将长度为 $l-1$ 时被视为相同的起始位置分别进行排序。

虽然这样时间复杂度为 $O(n^2|\Sigma|)$，但注意到我们**只需求得两个字符串是否相同，而无需得知它们的字典序大小关系，因此只需给每一组相同的字符串同一个编号，而无需遍历整个桶以编号，时间复杂度** $O(n^2)$。

## 代码

有详细注释哟~

PS：将 vector 换成二维数组常数可能会小一点，但是笔者懒得改了。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=3e3+5;
char s[max_n],t[max_n];
int rk[max_n][max_n]; // rk[l][i] 是子串 t[i,i+l-1] 的编号 
vector<int> pos[max_n],pos1[max_n]; // pos[i] 存储当前编号为 i 的子串的起始位置，pos1[i] 用于临时存储下一次的 pos[i] 
int id[30]; //某一编号的子串加上新的字符所得到新子串的编号 
vector<int> p[max_n]; // p[l] 存储长度为 l 的满足题意的起始位置 
bool mark[max_n];
int st[max_n],Top; //存储访问过的位置 
int main()
{
	int n;
	scanf("%d%s%s",&n,s+1,t+1);
	int Max=1; //当前最大编号 
	for(int i=1;i<=n;++i)
		pos[1].push_back(i); //一开始所有编号为 1 
	for(int l=1;l<=n;++l)
	{
		for(int j=0;j<26;++j)
			id[j]=0; //只需在每种长度一开始清空 
		int Max1=0;
		for(int i=1;i<=Max;++i)
		{
			int Last=Max1; //这一轮开始之前的最大编号 
			for(vector<int>::iterator it=pos[i].begin();it!=pos[i].end();++it)
			{
				int x=*it;
				if(id[t[x+l-1]-'a']<=Last) //这个字符在这一轮新出现 
					id[t[x+l-1]-'a']=++Max1;
				rk[l][x]=id[t[x+l-1]-'a'];
				pos1[rk[l][x]].push_back(x);
			}
		}
		for(int i=1;i<=Max;++i)
			pos[i].clear(); //先清空 pos 
		for(int i=1;i<=Max1;++i)
		{
			for(vector<int>::iterator it=pos1[i].begin();it!=pos1[i].end();++it)
			{
				int x=*it;
				if(x+l<=n) //将 pos1 复制给 pos（去掉下一轮不再出现的起始位置） 
					pos[i].push_back(x);
			}
			pos1[i].clear();
		}
		Max=Max1; //将 Max1 复制给 Max 
	}
	for(int i=1;i<=n;++i)
	{
		int now=1;
		for(int j=i;j<=n;++j)
		{
			while(now<=n&&s[now]!=t[j]) //贪心选取 
				++now;
			if(now>n)
				break;
			p[j-i+1].push_back(i);
			++now; //下次应从下一个字符开始 
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		for(vector<int>::iterator it=p[i].begin();it!=p[i].end();++it)
		{
			int x=*it;
			if(!mark[rk[i][x]])
			{
				++ans;
				mark[rk[i][x]]=true;
				st[++Top]=rk[i][x];
			}
		}
		while(Top>0)
			mark[st[Top--]]=false; //由于编号可能会比较大，不能直接清空，只能清空访问过的部分 
	}
	printf("%d\n",ans);
    return 0;
}
```

## 后记

本人赛时写的是题解中提到的那个未经优化的桶排（代码戳[这里](https://www.luogu.com.cn/paste/ndq3qlrr)），但当时完全没意识到有一个 $|\Sigma|$ 在复杂度里，就连测民间数据 TLE 时都以为是 vector 常数太大，导致 $100 \rightarrow 70$。o(╥﹏╥)o

所以在此提醒广大 OIer：**一定要认真分析时间复杂度，且比赛时有条件的话要生成大数据测一测！**

------------

~~话说使用 Hash 的 CCF 是如何保证数据正确性的~~

---

## 作者：Saliеri (赞：5)

给一发简单的 SAM 做法。

___

简要题意：

- 给两个字符串 s,t ，求使 s 的子序列等于 t 的子串的方案数。两个方案被判定为不等当且仅当最后得到的串不等。

看到子串问题就果断 SAM。

再来考虑我们怎么来表示一个子串是否出现过。这个问题在 SAM 中是非常好回答的：知道所在状态和长度即可。

所以我们可以对于每一个状态记录出现过的长度区间，最后将所有状态的区间长度和相加就是答案。


考虑一个简单的过程：往已经有的合法串上加一个末尾字符，使得这个串仍然是 t 的子串。

实现这一个过程可以枚举状态，然后直接判断 SAM 上有没有对应的转移边。

同时，这一个状态上的所有可表出的长度 +1 都可以在转移到的状态上被表出。

然后直接在这里就莽 bitset 就是 $O(\dfrac{n^3}{w})$ 的了。~~（只要学过  SAM 都不会这样吧）~~

但是通过 SAM 本身我们发现，因为每个状态中表示的子串都为后缀关系，所以长度长的只要出现过，短的也必然出现过，bitset 很明显存了太多冗余的信息。

由上，所以对于每一个状态记录 $\text{Max}_i$ 表示到达过这个点的最长长度，最后 $\text{ans} = \sum{\text{Max}_i-len_{link_i}}$ 就完了。

时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。

____

考场代码：

```cpp
#include <cstdio>
#include <cstring>
const int maxn = 6e3+5;
inline int max(int a,int b){return a>b?a:b;}
int n,ans,maxx[maxn],tmax[maxn];
char s[maxn],t[maxn];
int ch[maxn][26],len[maxn],link[maxn],sz,last;
void append(int x){
	int cur = ++sz,p = last;
	len[cur] = len[p]+1;
	while(~p&&!ch[p][x])ch[p][x] = cur,p = link[p];
	if(p == -1)link[cur] = 0;
	else{
		int q = ch[p][x];
		if(len[q] == len[p]+1)link[cur] = q;
		else{
			int nq = ++sz;
			len[nq] = len[p]+1,link[nq] = link[q],link[q] = link[cur] = nq,memcpy(ch[nq],ch[q],104);
			while(~p&&ch[p][x]==q)ch[p][x] = nq,p = link[p];
		}
	}
	last = cur;
}
int main(){
//	freopen("block.in","r",stdin);
//	freopen("block.out","w",stdout);
	link[sz=last=0]=-1;	
	scanf("%d",&n);
	scanf("%s",s+1);
	scanf("%s",t+1);
	for(int i=1;i<=n;++i)append(t[i]-'a');
	for(int i=1;i<=sz;++i)maxx[i] = -1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=sz;++j)tmax[i] = 0;
		for(int j=0;j<=sz;++j)
			if(maxx[j] != -1 && ch[j][s[i]-'a'])
				tmax[ch[j][s[i]-'a']] = max(tmax[ch[j][s[i]-'a']],maxx[j]+1);
		for(int j=0;j<=sz;++j)maxx[j] = max(maxx[j],tmax[j]);
	}  
	for(int i=1;i<=sz;++i)
		ans += max(0,maxx[i]-len[link[i]]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：5)

考虑对 A 建立子序列自动机，B 枚举子串。

子序列自动机可以抽象为一张图，于是可以 $O(1)$ 从 $[l,r]$ 的子序列自动机节点转移到 $[l,r+1]$ 子序列自动机节点。

普通子序列自动机转移是 $O(\log n)$，由于这里字典大小是 26，可以直接维护 26 个数组，保留每一个字母的下一个出现位置。

注意 B 的子串只能统计本质不同，这步有很多方法判重，我采用了双哈希。

来维护哈希，不要用 set，直接存入一个数组，最后排序并 unique。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

//#define int ll

const int MOD1=1000000009,BASE1=220037,INV1=780782330;
const int MOD2=998244853,BASE2=69420,INV2=81432737;

int alice[3005],bob[3005];
int nx[26][3005];
long long ar[4515012];
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	int n;
	cin>>n;
	memset(nx,-1,sizeof nx);
	{
		string a,b;
		cin>>a>>b;
		rep1(i,n)alice[i]=a[i-1]-'a';
		rep1(i,n)bob[i]=b[i-1]-'a';
	}
	rep1(i,n)
		nx[alice[i]][i-1]=i;
	rep(c,26)
		for(int i=n;i>=0;i--)
			if(nx[c][i]==-1)
				nx[c][i]=nx[c][i+1];
	int cnt=0;
	rep1(i,n){
		long long curhash1=0,curhash2=0;
		int pos=0;
		iter(j,i,n+1){
			curhash1=(curhash1*BASE1+bob[j]+1)%MOD1;
			curhash2=(curhash2*BASE2+bob[j]+1)%MOD2;
			pos=nx[bob[j]][pos];
			if(pos==-1)break;
			ar[cnt++]=(curhash1<<32)|curhash2;
		}
	}
	int ans=0;
	if(cnt){
		sort(ar,ar+cnt);
		ans=1;
		rep1(i,cnt-1)ans+=1-(ar[i]==ar[i-1]);
	}
	cout<<ans<<endl;
}

```

---

## 作者：NuoCarter (赞：4)

## 简要题意：
给定两个字符串 $A,B$

求出 $B$ 的本质不同子串中是 $A$ 的子序列的个数

首先考虑将 **子串** 转化为**后缀的前缀**，我们可以枚举整个后缀来获取整个 $B$ 的 **子串**。

枚举后缀是 $O(n)$ 的，再用整个后缀去与 $A$ 匹配。

不妨设这个后缀为 $S_{1-i}$

因为 $S_{1-i}$ 是 $A$ 的子序列，那么 $S_{1-(i-1)}$ 也一定是 $A$ 的子序列。

于是可以 $O(n)$ 模拟得到这个后缀在 $A$ 中的最长匹配长度。

而整个后缀的前缀中，只要 $\leq$ 这个长度，一定都是 $A$ 的子序列。


总体复杂度 $O(n^2)$，但是答案要求的是本质不同的子串。

所以用一个双哈希判重即可。（考场上写了3个哈希。。）

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD=19260919,base=173,MOD2=23532139,base2=239,MOD3=33532139,base3=337;
const int N=3005;

template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch))  x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;
}
template <typename T>
inline void print(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10^48);
}
int n,pi[N],ans;
string a,b,tep,ptr,res;
pair<ll,ll> str[N*N];
int head[MOD+2],Next[N*N],tot;
inline void Add(int u,pair<ll,ll> ins){Next[++tot]=head[u],str[tot]=ins,head[u]=tot;}
inline bool Find(int u,pair<ll,ll> goal){
    for(register int i=head[u];i;i=Next[i]){
        if(str[i].first==goal.first&&str[i].second==goal.second)   return true;
    }
    return false;
}
ll has1,has2,has3;
int main(){
    // freopen("block.in","r",stdin);
    // freopen("block.out","w",stdout);
    read(n);
    cin>>a>>b;
    for(register int st=0;st<n;++st){
        ptr=b.substr(st,n-st);
        int loc=0;
        for(register int i=0;i<n;++i){if(a[i]==ptr[loc])  loc++;}
        res="";has1=0,has2=0,has3=0;
        for(register int i=0;i<loc;++i){
            res+=ptr[i];
            has1=(has1*base+ptr[i]-'0')%MOD;
            has2=(has2*base2+ptr[i]-'0')%MOD2;
            has3=(has3*base3+ptr[i]-'0')%MOD3;
            if(!Find(has1,make_pair(has2,has3))){
                Add(has1,make_pair(has2,has3));
                ans++;
            }
            // cout<<res<<endl;
        }
    }
    print(ans);
    // puts("");
    // printf("%.6lf\n",(clock()-st)/CLOCKS_PER_SEC);
    return 0;
}
/*
5
bcabc
bbcca
*/

```

---

## 作者：清烛 (赞：3)

## 一些废话

赛后四十分钟划了划水然后敲出能过 w33z 数据的代码。交给 ccf 的得了 80 pts。

这次题目难度明显 B < A，下面提供一个比较好理解的简单的做法。

## 题意
给定两个长度为 $n$ 的字符串 $S$ 和 $T$。进行如下操作：

- 删除 $S$ 中的任意字符
- 删除 $T$ 中的任意前缀和任意后缀

（可以选择不删，但不能删成空串）要求最终两个字符串相等，求一共有多少种这样的字符串。

## 分析

数据范围 $1\le n\le 3000$，知道需要使用 $n^2$ 的算法。

考虑枚举 $T$。发现无非就是枚举其**每个后缀的前缀**，这样枚举是 $O(n^2)$ 的，可以接受。

现在考虑怎么在 $S$ 中 $O(1)$ 判断是否能匹配。注意到我们是在枚举前缀，因此若**长度为 $m + 1$ 的前缀能匹配，那么长度为 $m$ 的前缀必然也能匹配**。考虑处理出 $p_{i,j}$ 数组表示在 $(i,n]$ 中字符 $j$ 的**第一次出现的位置**。然后就可以利用这个 $p$ 数组在枚举前缀的同时在 $S$ 里面跳指针，因为处理的是第一次出现的位置所以不需要担心漏掉情况。**若遇到不能匹配的前缀了，说明更长的前缀也肯定无法匹配**，直接 `break` 即可。

现在我们可以判断 $T$ 的一个子段是否合法了，但是这样子写是连第一个样例都过不去的，为什么呢？

> 有多少种不同的情况下他们最后剩下的两排积木是相同的

这意味着我们需要进行去重，由于 hash 的不确定性这里没有使用 hash 而是使用魔改了的 Trie。在枚举前缀的时候同时用一个指针在 Trie 上自上而下走，若走到了空点就记录一下就可以了。

## 实现
仔细分析一下，最多可以有 $3000\times 3000\div 2= 4.5\times 10^6$ 种不一样的子串，所以写 Trie 树不能像平时一样写 `int ch[maxn][26]`，这样在本题会收获 80 分的好成绩。

但如果我们只记录 Trie 上存在的边，稍加分析即可得这样是可以卡过空间的，至于时间就是 $O(|S|n^2)$（枚举 Trie 的出边），其中 $|S|$ 为字符集大小（$26$），所以相当于就是 $O(n^2)$，而且拥有一个根本卡不满的上界。

```cpp
#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 3005;

int n;
char s[maxn], t[maxn];

int pos[maxn][26];
int last[maxn][maxn];

int head[maxn * maxn / 2], to[maxn * maxn / 2], nxt[maxn * maxn / 2], cnte, tot;
char trie[maxn * maxn / 2];

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    FOR(i, 1, n)
    {
        FOR(j, i + 1, n)
            if (!pos[i][s[j] - 'a'])
                pos[i][s[j] - 'a'] = j;
        if (!pos[0][s[i] - 'a'])
            pos[0][s[i] - 'a'] = i;
    }
    int ans = 0;
    FOR(i, 1, n)
    {
        if (!pos[0][t[i] - 'a']) continue;
        int p = 0;
        FOR(j, i, n)
        {
            if (pos[last[i][j - 1]][t[j] - 'a'])
            {
                last[i][j] = pos[last[i][j - 1]][t[j] - 'a'];
                bool flag = 0;
                for (int i = head[p]; i; i = nxt[i])
                {
                    if (trie[to[i]] == t[j])
                    {
                        flag = 1;
                        p = to[i];
                        break;
                    }
                }
                if (!flag)
                {
                    ++ans, trie[++tot] = t[j];
                    add(p, tot);
                    p = tot;
                }
            }
            else break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：huayucaiji (赞：3)

### 前言

这个题我的方法天下唯一。

~~就是常数有点大，希望CCF的钱拿去买个快点的评测机orz~~

### 解法

考虑不去重。我们可以维护一个 $nxt_{i,j}$，表示第 $i$ 个位置往后最近的一个字符 $j$ 在哪个位置。我们只需要枚举 $b$ 串的起点，一个一个往后匹配。贪心的选择易证最优，我们用 $nxt$ 数组来往后找即可，只要到某一个位置没法继续了，就换一个起点，重复以上过程。

接下来就是去重了。

很多大佬提供的方案是 hash。我在考场上也想到了，由于本人 hash 不精，所以没写 hash。但是我想到另外一个方法，普及组选手也能看懂。

既然要去重，我们只要让所有有相同前缀的子串一起计算就好啦呀。我们可以用一个字符，慢慢扩展成很多字符，直到找不到为止。递归计算即可。

说得明白一点，也就是你建一颗 trie 树，直到建不下去为止。

可能看代码明白快一点吧。代码中的 stack 可以换成 queue 或者 deque，没什么大关系。

~~就是常数大了点，需要吸氧过冥间数据qwq~~

### 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=3000+10;

int n,ans;
int a[MAXN],b[MAXN],nxt[MAXN][30];
char c;
//map<string,bool> s;
stack<int> stk[MAXN][28];

void solve(int p,int lvl,int val) {
	if(p==-1||stk[lvl][val].empty()) {
		while(!stk[lvl][val].empty()) {
			stk[lvl][val].pop();
		}
		return ;
	}
	if(lvl) {
	//	cout<<s<<"\n";
		ans++;
	}
	while(!stk[lvl][val].empty()) {
		int t=stk[lvl][val].top()+1;
		if(t<=n)
			stk[lvl+1][b[t]].push(t);
		stk[lvl][val].pop();//stack可以重复利用
	}
	
	for(int i=1;i<=26;i++) {
		solve(nxt[p][i],lvl+1,i);
	}
}

signed main() {
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++) {
		cin>>c;
		a[i]=c-'a'+1;
	}
	for(int i=1;i<=n;i++) {
		cin>>c;
		b[i]=c-'a'+1;
	}
	
    //构建nxt数组
	for(int i=1;i<=26;i++) {
		nxt[n][i]=-1;
	}
	for(int i=n-1;i>=0;i--) {
		for(int j=1;j<=26;j++) {
			if(j==a[i+1]) {
				nxt[i][j]=i+1;
			}
			else {
				nxt[i][j]=nxt[i+1][j];
			}
		}
	}
	
	/*for(int i=1;i<=n;i++) {
		int p=0;
		string str="";
		for(int j=i;j<=n;j++) {
			
			p=nxt[p][b[j]];
			if(p!=-1) {
				ans++;
			}
			else {
				break;
			}
		}
	}*/
	for(int i=1;i<=n;i++) {
		stk[0][0].push(i-1);
	}
	solve(0,0,0);
	
	cout<<ans<<endl;

	fclose(stdin);
	fclose(stdout);
	return 0;
}

```

---

## 作者：滑大稽 (赞：3)

前言：

这题是考场上唯一做出来的题，t3树套树类正解，部分分都没调出来，t1暴力走人


那就把我做法讲一下吧。

对于这道题，第一眼就莫名感觉和[这道题](https://www.luogu.com.cn/problem/P4112)很像。于是就套路了。

对于a串，因为他要子序列，所以建一个子序列自动机。

对于b串，因为是子串，自然而然就建一个sam。

那该怎么统计答案呢？

我们发现，因为他相同的串只算一个，而子序列自动机，sam上面的路径正好对应了互不相同的串。所以我们就可以让子序列自动机，sam同时从起始点开始，找他们公共的路径。这个可以bfs+刷字符串表实现。

关于他的时间复杂度证明，因为子序列自动机和sam的点数都是  $n$ 级别的，而最多只有 $n^2$ 种状态，所以总复杂度上界应该是 $\mathcal O(n^2)$ 的。但绝对跑不满。

所以就半小时t2，两小时t3了...

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
const int N=3005;
using namespace std;
char a[N],b[N];
inline int r()
{
	char h=getchar();
	int y=0;
	while(h<'0'||h>'9')h=getchar();
	while(h>='0'&&h<='9')y=y*10+h-'0',h=getchar();
	return y;
}
namespace sam{
	struct node{
		int c[26],fa,len;
	}q[N<<1];
	int l=1,t=1;
	inline void jr(int c)
	{
		int x=l;int nx=l=++t;
		q[nx].len=q[x].len+1;
		for(;x&&!q[x].c[c];x=q[x].fa)q[x].c[c]=nx;
		if(!x)return (void)(q[nx].fa=1);
		int y=q[x].c[c];
		if(q[y].len==q[x].len+1)return (void)(q[nx].fa=y);
		int ny=++t;
		q[ny]=q[y];q[ny].len=q[x].len+1;
		q[y].fa=q[nx].fa=ny;
		for(;x&&q[x].c[c]==y;x=q[x].fa)q[x].c[c]=ny;
	}
}
namespace xlzdj{
	int ne[N][26];
	inline void gz(char a[],int n)
	{
		for(int i=n-1;~i;i--)
		{
			for(int j=0;j<26;j++)ne[i][j]=ne[i+1][j];
			ne[i][a[i+1]-'a']=i+1;
		}
	}
}
using namespace sam;
using namespace xlzdj;
struct gs{
	int x,y;
};
int ans=0;
inline void bfs()
{
	queue<gs>dl;
	dl.push((gs){1,0});
	while(!dl.empty())
	{
		int x=dl.front().x,y=dl.front().y;dl.pop();
		for(int i=0;i<26;i++)if(q[x].c[i]&&ne[y][i])
		{
			ans++;
			dl.push((gs){q[x].c[i],ne[y][i]});
		}
	}
}
signed main()
{
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	int n=r();
	scanf("%s",a+1);
	gz(a,n);
	scanf("%s",b);
	for(int i=0;i<n;i++)jr(b[i]-'a');
	bfs();
	printf("%d\n",ans);
	return 0;
}
/*
5
bcabc
bbcca

20
egebejbhcfabgegjgiig
edfbhhighajibcgfecef

*/
```

---

## 作者：白鲟 (赞：2)

## 前言
考场上唯一会做的题。

然而我最后发现我秀了八百年的两遍拓扑排序只需要五行 dfs 就可以解决。

自闭了。

## 题目分析
容易想到 [P4112 [HEOI2015]最短不公共子串](https://www.luogu.com.cn/problem/P4112)。

于是对两串分别建立子序列自动机与后缀自动机。然后尝试按该题思路广搜未果。于是想到两遍拓扑排序后 DP（不要问我怎么想到的）。

好，这不重要。下场之后考虑本质。

发现后缀自动机事实上只做了对子串去重的工作。于是可以深搜后缀自动机每一条路径，同时尝试在子序列自动机上匹配。

时间复杂度为 $\operatorname{O}(size\cdot n^2)$，$size$ 为字符集大小，是由 dfs 中枚举出边引起的。

## 代码
注意空串不计入答案。
```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=3000,alpha=26,base='a';
int len,total,last[alpha],trie[maxn+5][alpha];
char a[maxn+5],b[maxn+5];
struct node
{
    int maxlen,parent,to[alpha];
}SAM[maxn<<1|1];
void build_SAM(char *s)
{
    SAM[0].parent=-1;
    for(int i=0,now=0;i<len;++i)
    {
        int last=now;
        SAM[now=++total].maxlen=SAM[last].maxlen+1;
        while(~last&&!SAM[last].to[s[i]-base])
        {
            SAM[last].to[s[i]-base]=now;
            last=SAM[last].parent;
        }
        if(~last)
        {
            if(SAM[last].maxlen+1==SAM[SAM[last].to[s[i]-base]].maxlen)
                SAM[now].parent=SAM[last].to[s[i]-base];
            else
            {
                int target=SAM[last].to[s[i]-base];
                ++total;
                for(int j=0;j<alpha;++j)
                    SAM[total].to[j]=SAM[target].to[j];
                SAM[total].parent=SAM[target].parent;
                SAM[total].maxlen=SAM[last].maxlen+1;
                SAM[now].parent=SAM[target].parent=total;
                while(~last&&SAM[last].to[s[i]-base]==target)
                {
                    SAM[last].to[s[i]-base]=total;
                    last=SAM[last].parent;
                }   
            }
        }
    }
}
void build(char *s)
{
    for(int i=len;~i;--i)
    {
    	for(int j=0;j<alpha;++j)
    		trie[i][j]=last[j];
    	if(i)
    		last[s[i-1]-base]=i;
	}
    return;
}
int dfs(int node1,int node2)
{
	int ans=1;
	for(int i=0;i<alpha;++i)
		if(SAM[node1].to[i]&&trie[node2][i])
			ans+=dfs(SAM[node1].to[i],trie[node2][i]);
	return ans;
}
int main()
{
	scanf("%d%s%s",&len,a,b);
	swap(a,b);
	build_SAM(a);
	build(b);
	printf("%d\n",dfs(0,0)-1);
	return 0;
}
```

---

## 作者：Anita_Hailey (赞：2)

只会这一道题。我爬了

考虑 $O(n^2)$ 的解法。不难想到对于每个在第二个串的子串在第一个串上询问即可。我们可以做到 $O(n^3)$。

考虑顺序枚举子串的话，需要 $O(n^2)$ 就可以解决。但是会算重。那么我们考虑只计算本质不同的子串即可。这是 Suffix_Array 的经典问题


```cpp
#include <bits/stdc++.h>
const int N = 3005;
int n, nxt[26], ch[N][26];
char c1[N], c2[N];
namespace SLT {
    int n, m = 122, k, sa[N], x[N * 2], y[N * 2], rk[N], h[N], b[N];
    void solve(char *s) {
    	n = strlen(s + 1);
    	for (int i(1); i <= n; ++i) {
    		b[x[i] = s[i]]++;
    	}
    	for (int i(1); i <= m; ++i) {
    		b[i] += b[i - 1];
    	}
    	for (int i(n); i; --i) {
    		sa[b[x[i]]--] = i;
    	}
    	for (int i(1); i < n; i *= 2) {
    		int num(0);
    		for (int j(n - i + 1); j <= n; ++j) {
    			y[++num] = j;
    		}
    		for (int j(1); j <= n; ++j) {
    			if (sa[j] > i) {
    				y[++num] = sa[j] - i;
    			}
    		}
    		for (int j(1); j <= m; ++j) {
    			b[j] = 0;
    		}
    		for (int j(1); j <= n; ++j) {
    			b[x[j]]++;
    		}
    		for (int j(1); j <= m; ++j) {
    			b[j] += b[j - 1];
    		}
    		for (int j(n); j; --j) {
    			sa[b[x[y[j]]]--] = y[j];
    		}
    		std::swap(y, x);
    		x[sa[1]] = num = 1;
    		for (int j(2); j <= n; ++j) {
    			x[sa[j]] = (y[sa[j]] == y[sa[j - 1]] && y[sa[j] + i] == y[sa[j - 1] + i]) ? num : ++num;
    		}
    		if (num == n) {
    			break;
    		}
    		else {
    			m = num;
    		}
    	}
    	for (int i(1); i <= n; ++i) {
    		rk[sa[i]] = i;
    	}
    	for (int i(1), j(0); i <= n; ++i) {
    		if (rk[i] == 1) {
    			continue;
    		}
    		if (j) {
    			--j;
    		}
    		int k = sa[rk[i] - 1];
    		while (s[k + j] == s[i + j]) {
    			++j;
    		}
    		h[rk[i]] = j;
    	}
    	return;
    }
}
int main() {
	freopen("block.in", "r", stdin);
	freopen("block.out", "w", stdout);
	scanf("%d %s %s", &n, c1 + 1, c2 + 1);
	for (int i(1); i <= n; ++i) {
		for (int j(0); j < 26; ++j) {
			nxt[j] = nxt[j];
		}
		for (int j(nxt[c1[i] - 'a']); j < i; ++j) {
			ch[j][c1[i] - 'a'] = i;
		}
		nxt[c1[i] - 'a'] = i;
	}
	SLT::solve(c2);
	int ans(0);
	for (int i(1); i <= n; ++i) {
		int nw = 0;
		bool flag(1);
		for (int j(SLT::sa[i]); flag && j < SLT::sa[i] + SLT::h[i]; ++j) {
			if (!ch[nw][c2[j] - 'a']) {
				flag = 0;
			}
			else {
				nw = ch[nw][c2[j] - 'a'];
			}
		}
		for (int j(SLT::sa[i] + SLT::h[i]); flag && j <= n; ++j) {
			if (!ch[nw][c2[j] - 'a']) {
				flag = 0;
			}
			else {
				ans++;
				nw = ch[nw][c2[j] - 'a'];
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：UltiMadow (赞：1)

这题和 [P4112 [HEOI2015]最短不公共子串](https://www.luogu.com.cn/problem/P4112) 不是一模一样嘛（

考虑对 Alice 的字符串建子序列自动机，对 Bob 的字符串建后缀自动机

然后在两个自动机上一起跑一边 bfs，枚举转移的字符

如果在两个自动机上都有这个转移，那么就继续 bfs，否则停止 bfs

答案统计只要看 bfs 进行的次数即可

时间复杂度 $\mathcal O(n^2)$

考场上开了 270M 的数组，爆零了/dk/dk

```cpp
#include<bits/stdc++.h>
#define MAXN 6010
using namespace std;
int n;
struct Suffix_Auto{
	int ch[MAXN][30],len[MAXN],fa[MAXN];
	int last,tot;
	Suffix_Auto(){last=tot=1;}
	void extend(int id){
		int p=last,now=++tot;len[now]=len[last]+1;
		for(;p&&!ch[p][id];p=fa[p])ch[p][id]=now;
		if(!p)fa[now]=1;
		else{
			int q=ch[p][id];
			if(len[q]==len[p]+1)fa[now]=q;
			else{
				int clone=++tot;len[clone]=len[p]+1;
				memcpy(ch[clone],ch[q],sizeof(ch[q]));
				fa[clone]=fa[q];fa[now]=fa[q]=clone;
				for(;p&&ch[p][id]==q;p=fa[p])ch[p][id]=clone;
			}
		}last=now;
	}
};//后缀自动机
struct Sequence_Auto{
	int ch[MAXN][30],last[30];
	Sequence_Auto(){memset(last,0,sizeof(last));}
	void extend(char *c){
		int len=strlen(c+1);
		for(int i=len;i;i--){
			memcpy(ch[i],last,sizeof(last));
			last[c[i]-'a'+1]=i;
		}memcpy(ch[4000],last,sizeof(last));
	}
};//子序列自动机
Suffix_Auto b;Sequence_Auto a;
int qx[MAXN*MAXN/2],qy[MAXN*MAXN/2],l,r;
int ans;
void bfs(){
	qx[l=r=1]=4000;qy[1]=1;
	while(l<=r){
		int ua=qx[l],ub=qy[l++];
		ans++;
		for(int i=1;i<=26;i++){
			int va=a.ch[ua][i],vb=b.ch[ub][i];
			if(!va||!vb)continue;
			qx[++r]=va;qy[r]=vb;
		}
	}
}
char s[MAXN],t[MAXN];
int main(){
	freopen("block.in","r",stdin);freopen("block.out","w",stdout);
	scanf("%d%s%s",&n,s+1,t+1);
	a.extend(s);
	for(int i=1;i<=n;i++)b.extend(t[i]-'a'+1);
	bfs();printf("%d",ans-1);//空串不符合题意
	return 0;
}
```

---

## 作者：KAMIYA_KINA (赞：1)

### 各档部分分
#### 第一档：
$s$ 和 $t$ 中只有一种字母，直接输出 $n$ 就可以了，送10分。
 
#### 第二档：

$n \le 100$，这一档分应该可以用各种奇奇怪怪的暴力给过掉，考场上本人完全没有考虑改档部分分，因为下一档的部分分很明显会更好写一点。

#### 第三档：

$n \le 500$，这个数据可以用 map 给过掉，由于 $t$ 串是要求连续，所以说我们可以枚举左右端点，判断该子串是否成立，然后直接往 map 里面暴力塞判重就可以了，这个算法是可以达到 $n^3\log_2n$ 的，足以过掉这当数据点。

#### 满分做法：

大概看了一下其他的题解，大多数都是 SAM 或者子序列自动机，很明显，这些东西我都不会，所以说我使用的是十分入门的一个字符串算法， Trie树。

考虑一个显然的贪心策略，如果说一个子串被匹配成功了，那就证明这个子串的所有前缀都算是一种方案，那么我们只用枚举左端点，然后从 $l$ 扫到 $n$ ，找一个最长的前缀就可以了。这样我们就可以干掉一个 $r$ 的循环。

但是随即就又出现了一个问题，就是怎么将所有的前缀都塞到 map 里面，很显然如果这样做那么时间复杂度和第三档的时间复杂度没有区别，所以我们需要一个可以找前缀而且还可以判重的算法，那就是 Trie树。

但是如果将所有的字符串全部存进去的话， Trie树 的空间复杂度完全不够，很明显为 $4500000 * 26 = 117000000$ ，直接爆掉，所以说我们需要用存图的方式存 Trie 树，这样的话虽然做不到 $O(1)$ 时间复杂度内的转移，但是这只是加了一个小常数而已，无所谓。

### CODE
~~~cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define F(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
using namespace std;
const int N = 3e3 + 10;
char s1[N],s2[N];
int n;
int hd[N * N / 2],nxt[N * N / 2],to[N * N / 2],tot,cnt;
char ch[N * N / 2];
inline void add(const int u,const int v,const char sc) {
	nxt[++tot] = hd[u],to[tot] = v,ch[tot] = sc,hd[u] = tot;
}
long long ans = 0;
inline void input() {
	scanf("%d%s%s",&n,s1 + 1,s2 + 1);
	return ;
}
inline int Finds(const int l) {
	int pos = l;
	for(int i = 1; i <= n; i++) {
		if(s1[i] == s2[pos]) pos++;
		if(pos == n + 1) return pos;
	}
	return pos;
}
inline void insert(const int l,const int r) {
	int p = 0;
	for(int i = l; i <= r; i++) {
		bool flag = false;
		for(int eg = hd[p]; eg; eg = nxt[eg]) {
			if(ch[eg] == s2[i]) {
				flag = true;
				p = to[eg];
				break;
				
			}
		}
		if(flag) continue;
		else {
			add(p,++cnt,s2[i]);
			ans++;
			p = cnt;
		}
	}
	 return ;
}
inline void work() {
	for(int i = 1; i <= n; i++) {
		int pos = Finds(i) - 1;
		insert(i,pos);
	}
	return ;
}
inline void print() {
	printf("%lld",ans);
	return ;
}
int main() {
// 	F("block");
	input();
	work();
	print();
	return 0;
}
~~~


### 题外话
我在考场上想出了 Trie树 做法，但是被 luogu 的数据给干到只有 50 pts，后来发现因为 `end` 数组没有开到跟 `nxt` 数组一样大，所以只有 50 pts，开到了之后只有 80 pts，因为内存爆掉了。希望 CCF 的数据可以尽量水一点。

---

## 作者：warzone (赞：1)

## 题目大意
已知两个长度为 $n$ 的字符串 $s,t$。  

从 $s$ 中取出一个子序列，从 $t$ 中取出一个子串，  
使得取出的两个串相同，求本质不同的方案数。

两个方案不同当且仅当取出的串不同。

$\texttt{Data Range:}1\le n\le 3000$

## 题解
本来 T2 是签到题的，可是考场上在肝 T1 QAQ  

首先题目要求从 $t$ 中取出一个子串，要求本质不同。

由于数据范围只有 $3000$，考虑对 $t$ 建立后缀自动机，  
然后暴力往下跳枚举子串。

对于从 $s$ 中取出一个子序列的要求，建立关于 $s$ 的子序列自动机，  
然后两个自动机同步往下跳。

设字符集为 $\sum$，则时空复杂度为 $\Theta(n^2|\sum|)$，  
由于字符集只有小写字母，于是可以通过。

[关于后缀自动机的建立与原理](https://www.luogu.com.cn/blog/wangrx/sam-guang-yi-sam-yu-ac-zi-dong-ji-zhi-jian-di-guan-ji)  
（其实考试时前一个半小时一直在完善这篇 blog，根本没看题 QWQ）

```cpp
#include<stdio.h>
#include<string.h>
typedef unsigned int word;
struct READ{//快读
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator >>(register type& num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
struct SAM{//后缀自动机
    word next[6010][26];
    word link[6010],len[6010];
    word size,last;
    inline SAM(){
        size=last=0;
        link[0]=0xffffffff;
    }
    #define split()                 \
        len[++size]=len[last]+1;    \
        memcpy(next[size],next[old],sizeof(next[0]));   \
        link[size]=link[old],link[old]=size;            \
        for(;last!=0xffffffff;last=link[last])          \
            if(next[last][c]==old) next[last][c]=size;  \
            else break;
    inline void operator +=(char c){
        register word old;
        if(old=next[last][c]){
            if(len[old]==len[last]+1)
                return void(last=old);
            split();
            return void(last=size);
        }
        len[++size]=len[last]+1;
        for(;last!=0xffffffff;last=link[last])
            if((old=next[last][c])==0) next[last][c]=size;
            else if(len[old]==len[last]+1)
                return link[size]=old,void(last=size);
            else{
                split();
                return link[size-1]=size,void(last=size-1);
            }
        return link[size]=0,void(last=size);
    }
    #undef split
}sam;
word next[3010][26],tail[26],ans;
inline void dfs(word id1,word id2){//同步跳自动机
	++ans;
	for(register word i=0;i<26;++i)
		if(next[id1][i]&&sam.next[id2][i])
			dfs(next[id1][i],sam.next[id2][i]);
}
int main(){
	word n;
	cin>>n;
	while('a'>cin.c||cin.c>'z') cin.c=getchar();
	register word i=1;
	while('a'<=cin.c&&cin.c<='z'){
		cin.c-='a';
		while(tail[cin.c]<i)
			next[tail[cin.c]++][cin.c]=i;
		cin.c=getchar(),++i;
	}//子序列自动机
	while('a'>cin.c||cin.c>'z') cin.c=getchar();
	while('a'<=cin.c&&cin.c<='z')
		sam+=cin.c-'a',cin.c=getchar();
	dfs(0,0);
	printf("%u",--ans);//去掉空串的方案
	return 0;
}
```

---

## 作者：DPair (赞：1)

这道题本质上就是给你两个串，求出第二个串的所有 **本质不同子串** 在第一个串中作为 **子序列** 出现的个数。

由于这道题 $n$ 范围很小，使用哈希进行去重也可以，但是使用 SAM 更为方便。

我们对第二个串建 SAM 。

我们注意到 SAM 上每一条从起点 $t_0$ 开始的路径都表示一个本质不同的字符串，那么我们就只需要记录一个字符串是否是第一个串的子序列即可。

一种 naive 的想法是对第一个串建子序列自动机，即维护 **每一个位置下一个某一字符的出现位置** ，若不出现则为 $n + 1$ 。然后每一个扫每一个子串时维护一个指针，一旦指针到了 $n+1$ 就说明没有作为子序列出现，否则有。

然后有一个很显然的优化，一条路径上的字符串，前一个串必是后一个串的一个前缀，即我们刚才扫描的方法中，只需要 **实时维护** 这个指针，走到下一个位置时指针就可以继承然后直接 $O(1)$ 查询。

于是得到复杂度 $O(n^2)$ ，可以通过本题。

```cpp
#include <cstdio>
#include <cstring>
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
//折叠了部分代码
typedef long long LL;
#define INF 0x3f3f3f3f
#define MAXN 3005

int n;
char a[MAXN], b[MAXN];
struct SAM{
    int len[MAXN << 2], link[MAXN << 2];
    int nxt[MAXN << 2][26];
    int sz, lst;
    SAM(){
        len[0] = 0;link[0] = -1;
        ++ sz;lst = 0;
    }
    inline void extend(int c){
        int x = sz ++;
        len[x] = len[lst] + 1;
        int it = lst;
        while(~it && !nxt[it][c]){
            nxt[it][c] = x;
            it = link[it];
        }
        if(!~it) link[x] = 0;
        else{
            int t = nxt[it][c];
            if(len[it] + 1 == len[t]) link[x] = t;
            else{
                int y = sz ++;
                len[y] = len[it] + 1;
                memcpy(nxt[y], nxt[t], sizeof(nxt[y]));
                link[y] = link[t];
                while(~it && nxt[it][c] == t){
                    nxt[it][c] = y;
                    it = link[it];
                }
                link[t] = link[x] = y;
            }
        }
        lst = x;
    }
    int it = 0;
    int head[MAXN << 1], nt[MAXN * 3], e[MAXN * 3], val[MAXN * 3], cnt;
    inline void add(int u, int v, int w){
        nt[++ cnt] = head[u];
        head[u] = cnt;
        e[cnt] = v;
        val[cnt] = w;
    }
    int suc[MAXN][26], ans = 0;
    void dfs(int x){
        int mem = it;
        for (int i = head[x];i;i = nt[i]){
            if(suc[it][val[i]] <= n){
                ++ ans;it = suc[it][val[i]];
                dfs(e[i]);it = mem;
            }
        }
    }
    void init(){
        rep(i, 0, sz - 1) rep(j, 0, 25) if(nxt[i][j]) add(i, nxt[i][j], j);
        rep(i, 0, 25) suc[n][i] = n + 1;
        per(i, n - 1, 0) {
            memcpy(suc[i], suc[i + 1], sizeof(suc[i]));
            suc[i][a[i + 1] - 97] = i + 1;
        }
    }
    inline void solve(){
        init();dfs(0);print(ans);
    }
}t;

int main(){
    read(n);read(a + 1);read(b + 1);
    rep(i, 1, n) t.extend(b[i] - 97);
    t.solve();
}
```

---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7469)

前者知识：$\text{SAM}$

说点闲话，考试时先开的 T1，后来才发现 T2 简单一点。

我们可以发现 Bob 的操作就枚举所有 $t$ 的子串，所以自然而然想到建一个 $\text{SAM}$。

我们就可以遍历自动机，来得到每一个不重复的子串，在暴力匹配，就有如下代码。

时间复杂度是 $n ^ 2$ 的，你便遍历边匹配就可以过了。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 6000 + 5;

int n,ans,nxt[N][30];
char s[N],t[N],a[N];

int ncnt = 1,lst = 1;
struct SAM {
	int ch[30];
	int fa;
	long long len;
}sam[N];

void add(int c) {
	int p = lst;
	int u = lst = ++ ncnt;
	sam[u].len = sam[p].len + 1;
	for (; p && !sam[p].ch[c] ; p = sam[p].fa)
		sam[p].ch[c] = u;
	if (!p)
		sam[u].fa = 1;
	else {
		int q = sam[p].ch[c];
		if (sam[q].len == sam[p].len + 1)
			sam[u].fa = q;
		else {
			int spt = ++ ncnt;
			sam[spt] = sam[q];
			sam[spt].len = sam[p].len + 1;
			sam[q].fa = sam[u].fa = spt;
			for (; p && sam[p].ch[c] == q ; p = sam[p].fa)
				sam[p].ch[c] = spt;
		}
	}
}

void dfs(int u,int dep,int pos) {
	if (u != 1)
		ans ++;
	for (int i = 0 ; i < 26 ; ++ i) {
		if (sam[u].ch[i]) {
			int flag = -1;
			a[dep] = 'a' + i;
			if (nxt[pos][i] != -1)
				dfs(sam[u].ch[i],dep + 1,nxt[pos][i] + 1);
		}
	}
}

int main () {
//	freopen("block.in","r",stdin);
//	freopen("block.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s);
	scanf("%s",t);
	int flag = 1;
	memset(nxt,-1,sizeof nxt);
	for (int i = 0 ; i < 26 ; ++ i) {
		int pos = -1;
		for (int j = n - 1 ; ~j ; -- j) {
			if (s[j] == i + 'a')
				pos = j;
			nxt[j][i] = pos;
		}
	}
	for (int i = 0 ; i < n ; ++ i)
		add(t[i] - 'a');
	dfs(1,0,0);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：renshale (赞：0)

~~伪T2，实T1~~

### 考场想法1

考虑枚举$ t $的连续子串，在$ s $中暴力匹配，时间复杂度$ O(n^3) $

### 考场想法2

在$ t $中枚举连续子串的起点，我们发现起点相同的连续子串，当终点较后的能在$ s $中被匹配，那么终点较前的子串也一定能匹配；当终点较后的出现过，那么终点较前的也出现过。利用单调性，能够二分完成统计答案与去重（Hash），时间复杂度$ O(n^2 \ log_2 \ n)$。

没有过多考虑匹配本身的性质。

实测最慢的点$ 0.3s $

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;

#define INF 0x7FFFFFFF
#define ll long long
#define ull unsigned long long
#define ld long double
#define Rs register

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
    while (c > '9' || c < '0') { if(c == '-') f = -1; c = getchar(); }
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}

const int N = 5e3 + 10;
const int L = 9e6 + 10;
const ll Mod1 = 1e6 + 7;
const ll Mod2 = 1e9 + 7;
const ll base = 127;

string str;
char A[N], B[N];
int n, ans;

class HS
{
	public :
		
	int tot;
		
	int ls[Mod1 + 10], nx[L]; 
	ll vl[L];
	
	inline void Add(ll Key1, ll Key2)
	{
		++ tot;
		nx[tot] = ls[Key1];
		vl[tot] = Key2;
		ls[Key1] = tot;
	}
	
	inline bool Find(ll Key1, ll Key2)
	{
		for (int i = ls[Key1]; i; i = nx[i])
			if (vl[i] == Key2)
				return true;
		return false;
	}
		
} List;

ll hsh1[N], hsh2[N], power1[N], power2[N];

inline ll seg1(int l, int r)
{
	return (hsh1[r] - hsh1[l - 1] * power1[r - l + 1] % Mod1 + Mod1) % Mod1;
}

inline ll seg2(int l, int r)
{
	return (hsh2[r] - hsh2[l - 1] * power2[r - l + 1] % Mod2 + Mod2) % Mod2;
}

signed main()
{
//	freopen("block.in", "r", stdin);
//	freopen("block.out", "w", stdout);

	n = read();
	scanf("%s", A + 1);
	scanf("%s", B + 1);
	power1[0] = power2[0] = 1;
	for (int i = 1; i <= n; i ++)
	{
		power1[i] = power1[i - 1] * base % Mod1;
		power2[i] = power2[i - 1] * base % Mod2;
	}
	for (int i = 1; i <= n; i ++)
	{
		hsh1[i] = (hsh1[i - 1] * base % Mod1 + (B[i] - 'a' + 1)) % Mod1;
		hsh2[i] = (hsh2[i - 1] * base % Mod2 + (B[i] - 'a' + 1)) % Mod2;
	}
	for (int st = 1; st <= n; st ++)	
	{
		int L = st, R = n, res = 0, tst = st;
		for (; L <= R; )
		{
			int mid = (L + R) >> 1;
			if (List.Find(seg1(st, mid), seg2(st, mid)))
				tst = L = mid + 1;
			else
				R = mid - 1;
		}
		L = tst, R = n;
		for (; L <= R; )
		{
			int mid = (L + R) >> 1, k = st;
			for (int i = 1; i <= n; i ++)
				if (A[i] == B[k])
				{
					++ k;
					if (k > mid)
						break ;
				}
			if (k > mid)
				L = mid + 1, res = mid - tst + 1;
			else
				R = mid - 1;
		}
		ans += res;
		for (int i = st; i <= n; i ++)
			List.Add(seg1(st, i), seg2(st, i));
	}
	printf("%d\n", ans);
	return 0;
}

```

### 更优的想法

对$ s $做一个子序列自动机，枚举$ t $中连续子串的起点，终点一个个在$ s $中查询即可。

---

## 作者：CodingJellyfish (赞：0)

此题可以用 字典图 + 哈希 求解。

至于字典图，听上去复杂，其实核心代码只有 3 行。
```c
for(i = n; i; i --)
    for(j = 0; j < i; j ++)
        graph[j][str1[i]-'a'] = i;
        //graph[i][j] 表示 第i个字符右面最近的为'a'+j的字符。
```
这样可以快速判断二者是否有符合要求的子串。

哈希需要能够常数复杂度算出子串的哈希。

下面贴出代码：
```c
#include <stdio.h>

typedef long long I;

#define SWAP(type,a,b) ({type tmp = a; a = b; b = tmp;})

#define N 3000
#define M 26
#define HASH 131LL
I graph[N+5][M+5];
char str1[N+5],str2[N+5];
I hash[N+5],fac[N+5]={1}, n, all[N*N+5], len;
void inithash() {
	int i;
	for(i = 1; i <= n; i ++) {
		hash[i] = hash[i-1] * HASH + str2[i];
		fac[i] = fac[i-1] * HASH;
	}
}
I gethash(I l, I r) {
	return hash[r] - hash[l-1] * fac[r-l+1];
}
void sort(I l, I r) {
	I i = l, j = r;
	I m = all[(l+r)>>1];
	do {
		while(all[i] < m) ++i;
		while(all[j] > m) --j;
		if(i <= j) {
			SWAP(I,all[i],all[j]);
			++i, --j;
		}
	} while(i <= j);
	if(j > l) sort(l, j);
	if(i < r) sort(i, r);
}
int main() {
	I i, j;
	scanf("%d %s %s", &n, str1+1, str2+1);
	for(i = n; i; i --)
		for(j = 0; j < i; j ++)
			graph[j][str1[i]-'a'] = i;
	inithash();
	
	for(i = 1; i <= n; i ++) {
	    I now = 0;
		for(j = i; j <= n; j ++) {
			if(graph[now][str2[j] - 'a'] == 0)
				break;
			now = graph[now][str2[j] - 'a'];
			all[++len] = gethash(i, j);
		}
	}
	sort(1, len);
	I ans = 0;
	for(i = 1; i <= len; i ++)
		ans += (all[i+1] != all[i]);
	printf("%d", ans);
	return 0;
}
```

---

