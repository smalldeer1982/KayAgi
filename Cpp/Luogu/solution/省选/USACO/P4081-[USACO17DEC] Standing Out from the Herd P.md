# [USACO17DEC] Standing Out from the Herd P

## 题目描述

就像人类一样，奶牛也常常希望在某些方面感到自己与众不同。由于 Farmer John 的奶牛都来自同一品种且外观非常相似，它们希望通过名字来衡量独特性。

每头奶牛的名字都有一些子字符串。例如，"amy" 的子字符串为 {a, m, y, am, my, amy}，而 "tommy" 的子字符串为 {t, o, m, y, to, om, mm, my, tom, omm, mmy, tomm, ommy, tommy}。

一头奶牛的名字有一个“独特性因子”，即该名字中不与任何其他奶牛共享的子字符串的数量。例如，如果 amy 独自在一个牛群中，她的独特性因子为 6。如果 tommy 独自在一个牛群中，他的独特性因子为 14。然而，如果它们在一个牛群中，amy 的独特性因子为 3，而 tommy 的独特性因子为 11。

给定一个牛群，请计算每头奶牛的独特性因子。

## 样例 #1

### 输入

```
3
amy
tommy
bessie```

### 输出

```
3
11
19```

# 题解

## 作者：yy1695651 (赞：17)

广义SAM 如果你还不会SAM强烈建议看看hiho上的解释http://www.hihocoder.com/problemset/problem/1441

直接对原串做一个广义SAM，广义SAM就是能做到多字符串匹配。和普通SAM区别就是在插入一个新的字符串时，把起始位置last=1就行了。

关于如何遍历子串：建好广义SAM之后，每一个模板串都从根节点开始遍历，然后按下面的代码来可以每次都跑到这个模板串的开头到现在位置所代表的节点，然后它的这个前缀的所有子串都是它parent树上的父亲$$Update(x = ch[x][s[++tot]], i);$$Update函数：对于每一个模板串把它在SAM上的所有子串代表的节点标记一下，如果曾经没有出现过则标记为当前子串的编号,如果曾经标记过得说明子串出现在不同的两个串中即不满足“独特性”重置为-1$$if (vis[x] != 0) vis[x] = -1;$$else$$vis[x] = y;$$

构造完成后，最后答案就是统计SAM上每个节点集合对应的串求和，节点集合对应串的个数就是mxl[i]-mxl[pre[i]]，答案就是$$sum[vis[i]]+=mxl[i]-mxl[pre[i]]$$

感谢bztMinamoto指导

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
inline void read(register int &x){
	x = 0; register int f = 1;
	register char c = getchar();
	while (!(c >= '0' && c <= '9')){ if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9'){ x = x * 10 + c - '0'; c = getchar(); }
	x *= f;
}
const int N = (int)2e5 + 10;
int s[N];
int len[N], n, tot;
struct SAM{
	int ch[N][26], pre[N], mxl[N], vis[N], last, cnt, ans[N];
	SAM(){ last = cnt = 1; }
	inline void Insert(register int c){
		register int p = last, np = ++cnt; last = np;
		mxl[np] = mxl[p] + 1;
		for (; p && !ch[p][c]; p = pre[p]) ch[p][c] = np;
		if (!p){ pre[np] = 1; return; }
		register int q = ch[p][c], nq = ++cnt;
		if (mxl[q] == mxl[p] + 1) { pre[np] = q; --cnt; return; }
		memcpy(ch[nq], ch[q], sizeof(ch[q]));
		mxl[nq] = mxl[p] + 1; pre[nq] = pre[q]; pre[q] = pre[np] = nq;
		for (; ch[p][c] == q; p = pre[p]) ch[p][c] = nq;
	}
	inline void Update(register int x, register int y){
		for (; x && vis[x] != y && vis[x] != -1; x = pre[x]){
			if (vis[x] != 0) vis[x] = -1;
			else vis[x] = y;
		}
	}
	inline void Solve(){
		tot = 0;
		//遍历所有串
		for (register int i = 1; i <= n; i++)
		for (register int j = 1, x = 1; j <= len[i]; j++)
			Update(x = ch[x][s[++tot]], i);
		for (register int i = 1; i <= cnt; i++) if (vis[i] != -1){
			register int x = vis[i];
			ans[x] += mxl[i] - mxl[pre[i]];
		}
		for (register int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	}
}sam;
int main(){
	read(n);
	for (register int i = 1; i <= n; i++){
		register char c; sam.last = 1;//新串last重置为1
		while ((c = getchar()) != '\n' && c != EOF){
			c -= 'a'; ++len[i]; s[++tot] = c;
			sam.Insert(c);
		}
	}
	sam.Solve();
	return 0;
}


```

附上自己画的SAM图，均由graphviz生成，有自动生成图形代码，博客中有(https://www.luogu.org/blog/yy1695651/yong-graphviz-hua-sam)

![样例1](https://cdn.luogu.com.cn/upload/pic/47591.png)

![样例2](https://cdn.luogu.com.cn/upload/pic/47592.png)

Sevenk Love Oimaster(https://www.luogu.org/problemnew/show/SP8093)

有兴趣再看看这道题，差不多做法

---

## 作者：elijahqi (赞：15)

 http://www.elijahqi.win/2018/02/08/bzoj5137/ ‎
 http://blog.csdn.net/elijahqi/article/details/79289548

题目描述

Just like humans, cows often appreciate feeling they are unique in some way. Since Farmer John's cows all come from the same breed and look quite similar, they want to measure uniqueness in their names.

Each cow's name has some number of substrings. For example, "amy" has substrings {a, m, y, am, my, amy}, and "tommy" would have the following substrings: {t, o, m, y, to, om, mm, my, tom, omm, mmy, tomm, ommy, tommy}.

A cow name has a "uniqueness factor" which is the number of substrings of that name not shared with any other cow. For example, If amy was in a herd by herself, her uniqueness factor would be 6. If tommy was in a herd by himself, his uniqueness factor would be 14. If they were in a herd together, however, amy's uniqueness factor would be 3 and tommy's would be 11.

Given a herd of cows, please determine each cow's uniqueness factor.

定义一个字符串的「独特值」为只属于该字符串的本质不同的非空子串的个数。如 "amy" 与 “tommy” 两个串，只属于 "amy" 的本质不同的子串为 "a" "am" "amy" 共 3 个。只属于 "tommy" 的本质不同的子串为 "t" "to" "tom" "tomm" "tommy" "o" "om" "omm" "ommy" "mm" "mmy" 共 11 个。 所以 "amy" 的「独特值」为 3 ，"tommy" 的「独特值」为 11 。

给定 N (

N≤105N \leq 10^5

N≤105 ) 个字符集为小写英文字母的字符串，所有字符串的长度和小于

10510^5

105 ，求出每个字符串「独特值」。
输入输出格式

输入格式：

The first line of input will contain

NN

N (

1≤N≤1051 \le N \le 10^5

1≤N≤105 ). The following

NN

N lines will each contain the name of a cow in the herd. Each name will contain only lowercase characters a-z. The total length of all names will not exceed

10510^5

105 .

输出格式：

Output

NN

N numbers, one per line, describing the uniqueness factor of each cow.
输入输出样例

输入样例#1： 复制

3
amy
tommy
bessie

输出样例#1： 复制

3
11
19

蒟蒻我不会sam只能用学习leoly 用sa来搞

那么针对每个串首先把他们连起来 然后加上分隔符 跑后缀数组 然后得到了按照字典序排序的这个东西 那么我想起了之前一道题 要求求自己这个字符串中本质不同的子串有多少个 可以想到直接n^2-height即可 这个其实可以同理 在自己中出现的只能算一次 如果在其他串中也出现了对答案的贡献就是0 那么我同理 直接减去 就可以了 但是还要注意一点 就是 针对 我一个字串如果他的后缀在sa中是一串连续的区间比如l~r那么我们这儿做之后别忘了加上lcp(l-1,r+1)  因为我相当于针对每个后缀都减掉了他们的lcp 那么是不是减多了 如果上与下匹配是aaa aaaaa 那么是不是这个对答案的贡献还有一个aaa而不是两个 所以要加回来
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 220000
#define ll long long
using namespace std;
int n,m,s[N],cnt[N],rk[N<<1],rk1[N],height[N],sa[N],pos[N],tmp[N],r[N];
char s1[N];ll ans[N];
int main(){
	freopen("bzoj5137.in","r",stdin);
	scanf("%d",&m);int st=26,k=0;
	for (int i=1;i<=m;++i){
		scanf("%s",s1+1);int nn=strlen(s1+1);
		for (int j=1;j<=nn;++j) s[++n]=s1[j]-'a'+1,pos[n]=i;r[i]=n;s[++n]=++st;
	}
	for (int i=1;i<=n;++i) cnt[s[i]]=1;
	for (int i=1;i<=st;++i) cnt[i]+=cnt[i-1];
	for (int i=1;i<=n;++i) rk[i]=cnt[s[i]];
	for (int p=1;k!=n;p<<=1,st=k){
		for (int i=1;i<=st;++i) cnt[i]=0;
		for (int i=1;i<=n;++i) ++cnt[rk[i+p]];
		for (int i=1;i<=st;++i) cnt[i]+=cnt[i-1];
		for (int i=n;i;--i) tmp[cnt[rk[i+p]]--]=i;
		for (int i=1;i<=st;++i)  cnt[i]=0;
		for (int i=1;i<=n;++i) ++cnt[rk[i]];
		for (int i=1;i<=st;++i) cnt[i]+=cnt[i-1];
		for (int i=n;i;--i) sa[cnt[rk[tmp[i]]]--]=tmp[i];
		memcpy(rk1,rk,sizeof(rk)>>1);rk[sa[1]]=k=1;
		for (int i=2;i<=n;++i){
			if (rk1[sa[i]]!=rk1[sa[i-1]]||rk1[sa[i]+p]!=rk1[sa[i-1]+p]) ++k;
			rk[sa[i]]=k;
		}
	}k=0;int mn=0;
	for (int i=1;i<=n;++i) {
		if (rk[i]==1) continue;
		k=k==0?0:k-1; 
		while(s[i+k]==s[sa[rk[i]-1]+k]) ++k;height[rk[i]]=k;
	}
	for (int i=1;i<=n;++i){
		if (s[sa[i-1]]>=27) break;int x=pos[sa[i]],y=pos[sa[i-1]];
		mn=min(mn,height[i]);ans[x]+=r[x]-sa[i]+1-height[i];
		if (x!=y) ans[y]-=height[i],ans[y]+=mn,mn=height[i];
	}
	for (int i=1;i<=m;++i) printf("%lld\n",ans[i]);
	return 0;
}

```

---

## 作者：LroseC (赞：13)

### 前言

貌似这题的后缀数组题解较少，排名第一的后缀数组题解排版炸了，排第二的太复杂了，所以我来贡献一篇题解。



### 前置知识

* [后缀数组](https://oi-wiki.org/string/sa/)
* [后缀数组求本质不同的子串数量](https://oi-wiki.org/string/sa/#_14)



### 思路

首先观察题目，抽象题意如下：

给定 $n$ 个串，求出每个串不出现在其他串中的本质不同子串数量。

我们想起我们曾经学过的后缀数组求本质不同的子串数量，与这题十分相仿。所以我们可以尝试模仿这种思路。

首先把这 $n$ 个串首尾相接，中间加上**各不相同**的分隔符，防止出现横跨不同串的最长公共前缀，这是后缀数组处理多个串的常用思路。

对于每个后缀，我们可以求出它所在原串的编号，设 $id[i]$ 表示第 $i$ 个后缀所在的原串。

按 $sa$ 的顺序从前往后枚举每一个后缀，新增的子串就是当前后缀**除去与上一个 $id$ 相同的后缀的 $lcp$** 后剩下的前缀。当然我们还要**排除掉和其他 $id$ 不同的后缀的 $lcp$**，于是取一个 $max$ 即可。

因此，对于每一个后缀 $x$，它排除的答案为 $\max(lcp(x, i), lcp(x, j), lcp(x, k))$，其中 $i$ 是满足 $rk[i] < rk[x],id[i]\neq id[x]$ 中排名最大的一个后缀，$j$ 是满足 $rk[j] > rk[x], id[j] \neq id[x]$ 中排名最小的后缀，$k$ 是满足 $id[k] = id[x]$ 中排名最大的后缀。

我们可以对于每一个 $x$ 预处理出 $lcp(x, i), lcp(x, j)$，然后仿照后缀数组求本质不同子串数量的方式，将每个串的初始答案设为 $\cfrac{len \times (len +1)} {2}$，接着对于每个 $i$，让其对应串的答案减去应排除的答案即可。



### 代码实现

```cpp
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

using LL = long long;
const int N = 4e5 + 10;

int n, m;
int sa[N], rk[N], height[N], x[N], y[N], c[N];
int id[N], len[N];
int str[N]; char tmp[N];
int a[N], b[N];
int st[N][31], lg2[N];
int string_cnt;
LL ans[N];

void buildSA(void) // 后缀数组模板
{
	m = 400000;
	for (int i = 0; i <= m; ++i) c[i] = 0;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i)
			y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++num] = sa[i] - k;
		for (int i = 0; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		swap(x, y);
		x[sa[1]] = num = 1;
		for (int i = 2; i <= n; ++i) {
			int ynow = sa[i] + k <= n ? y[sa[i] + k] : 0;
			int ynex = sa[i - 1] + k <= n ? y[sa[i - 1] + k] : 0;
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && ynow == ynex) ? num : ++num;
		}
		if (num == n) break;
		m = num;
	}

	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (k) --k;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k])
			++k;
		height[rk[i]] = k;
	}
}
void buildST(void)// ST 表模板
{
	for (int i = 2; i <= n; ++i)
		lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= n; ++i)
		st[i][0] = height[i];
	for (int k = 1; k <= 30; ++k)
		for (int i = 1; i + (1 << k - 1) <= n; ++i)
			st[i][k] = min(st[i][k - 1], st[i + (1 << k - 1)][k - 1]);
}
int queryHeight(int l, int r) // ST 表查询操作
{
	++l; int t = lg2[r - l + 1];
	return min(st[l][t], st[r - (1 << t) + 1][t]);
}

int main(void)
{
	scanf("%d", &string_cnt);
	for (int i = 1; i <= string_cnt; ++i) {
		scanf("%s", tmp + 1);
		for (len[i] = 1; tmp[len[i]]; ++len[i])
			str[++n] = tmp[len[i]], id[n] = i;
		str[++n] = 'z' + i;
		--len[i];
		ans[i] = 1ll * len[i] * (len[i] + 1) / 2;
	}
	str[n--] = 0;

	buildSA();
	buildST();

	int last = 0, llast = 0;
	// 预处理出 a[x], a[x] 表示本文中的 lcp(x, j)
	for (int i = n; i >= 1; --i) {
		if (id[sa[i]] != id[sa[last]])
			llast = last;
		last = i;
		a[i] = llast <= i ? 0 : queryHeight(i, llast);
	}

	for (int i = 1; i <= n; ++i) {
		int tmp = max(a[i], height[i]); // 容易证明, height[x] 等于本文中的 max(lcp(x, i), lcp(x, k))
		ans[id[sa[i]]] -= tmp;
	}
	for (int i = 1; i <= string_cnt; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
```



---

## 作者：灵乌路空 (赞：10)

# 知识点: 广义 SAM

原题面 [Luogu](https://www.luogu.com.cn/problem/P4081)

---

前置知识

在线构造广义 SAM，推荐：[【学习笔记】字符串—广义后缀自动机 - 辰星凌](https://www.cnblogs.com/Xing-Ling/p/12038349.html)  

---

## 题意简述

>给定 $n$ 个仅包含小写字母的字符串 $S_1\sim S_n$。  
>定义字符串 $S_i$ 的 「独特值」为只属于该串的本质不同的非空子串的个数。  
>求字符串 $S_1\sim S_n$ 的「独特值」。  
>$1\le n\le 10^5, 1\le \sum|S_i|\le 10^5$。  

---

## 分析题意

### 算法一

多串子串问题，考虑广义 SAM。

若 $n$ 较小，直接维护每个状态 包含几个串的信息。  
parent 树上 DP 更新祖先信息，直接更新答案即可。  
但 $n\le 10^5$ 空间爆炸，做不得，考虑乱搞一波。  

---

### 算法二

用 string 存字符串，建广义 SAM。  
在动态建立 SAM 时，$\operatorname{only}_i$ 记录每个状态 $i$ 包含哪一个串的信息。  
若某状态包含多个串信息，则$\operatorname{only}_i = - 1$。  
parent 树上 DP 更新祖先信息。  

先考虑一波 无脑暴力：   
对于 $S_i$，枚举其所有子串，在 SAM 上跑出对应状态 $u$。  
若有 $\operatorname{only}_u\not = 1$， 对应状态只维护了一个串的信息，一定为该子串。  
这样的子串数，即为 $S_i$ 的「独特值」。 

---

上述算法瓶颈是枚举子串。发现前缀有一些好性质：  

1. 连续前缀 对应状态在 SAM 上也是连续的，实现时直接把串扔到 SAM 上跑 即得对应状态。  
2. 前缀对应状态到 parent 树根的链上 包含该前缀所有后缀，可以包含所有子串信息。  

考虑仅枚举前缀，枚举复杂度变为线性。

---

发现一些结论：  

1. parent 树上一条从叶到根的链，维护的串的个数，是单调不减的。   
2. 若某状态 $i$ 的 $\operatorname{only}_i\not = -1$， 则对于其子树中所有状态 $j$，有 $\operatorname{only}_j=\operatorname{only}_i$。

考虑维护状态 $i$ 的 parent 树上距它最远的，$\operatorname{only}\not= -1$ 的祖先 $\operatorname{top}_i$。  
由结论 1，若某状态 $i$ 的 $\operatorname{only}_i=-1$，$\operatorname{top}_i=0$。  

由结论 2，跑到的 $\operatorname{only}\not= - 1$ 的节点对答案有贡献，在其子树中所有节点都会有贡献。  
可预处理子树 $\operatorname{len}(i)-\operatorname{len}(\operatorname{link}(i))$ 之和 $\operatorname{sum}$，即某子树中的子串数量。  

统计答案时，统计 跑到的状态 $u$ 的 $\operatorname{sum}(\operatorname{top}_u)$，一个 $\operatorname{top}_u$ 只能统计一次，去重可用排序实现。  
这样为什么是对的？考虑前缀的性质 2 感性理解一下。

每个串都在 SAM 上进行一匹配 并进行一次排序，总复杂度大概是 $O(\sum\limits_{i}^{n} |S_i|\log |S_i|)$，可过。  

---

### 算法三

瞅了一眼题解，发现自己做麻烦了。  
DP 求得 $\operatorname{only}$ 后，直接遍历所有状态，若存在 $\operatorname{only}_i \not= -1$，则令 $ans _{\operatorname{only}_i}$ 加上 $\operatorname{len}(i)-\operatorname{len}(\operatorname{link}(i))$即可。

复杂度 $O(\sum|S_i|)$，少一个排序的复杂度。

---

## 代码实现

### 算法三

```cpp
//知识点：广义 SAM
/*
By:Luckyblock  
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define ll long long
const int kMaxn = 2e5 + 10;
const int kMaxm = 26;
//=============================================================
std :: string S[kMaxn];
int only[kMaxn << 1], ans[kMaxn];
int num, node_num = 1, ch[kMaxn << 1][kMaxm], len[kMaxn <<1], link[kMaxn << 1];
int edge_num, head[kMaxn], v[kMaxn << 1], ne[kMaxn << 1]; 
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void AddEdge(int u_, int v_) {
  v[++ edge_num] = v_, ne[edge_num] = head[u_], head[u_] = edge_num;
}
int Insert(int c_, int last_) {
  if (ch[last_][c_]) {
    int p = last_, q = ch[p][c_];
    if (len[p] + 1 == len[q]) {
      only[q] = - 1;
      return q;
    }
    int newq = ++ node_num;
    memcpy(ch[newq], ch[q], sizeof(ch[q])); 
    len[newq] = len[p] + 1; 
    link[newq] = link[q];
    link[q] = newq; 
    for (; p && ch[p][c_] == q; p = link[p]) ch[p][c_] = newq;
    only[newq] = num;
    return newq;
  }
  int p = last_, now = ++ node_num;
  only[now] = num;
  len[now] = len[p] + 1;
  for (; p && ! ch[p][c_]; p = link[p]) ch[p][c_] = now;
  if (! p) {link[now] = 1; return now;} 
  int q = ch[p][c_];
  if (len[q] == len[p] + 1) {link[now] = q; return now;}
  int newq = ++ node_num;
  memcpy(ch[newq], ch[q], sizeof(ch[q])); 
  link[newq] = link[q], len[newq] = len[p] + 1; 
  link[q] = link[now] = newq;
  for (; p && ch[p][c_] == q; p = link[p]) ch[p][c_] = newq;
  return now;
}
void Dfs1(int u_) {
  for (int i = head[u_]; i; i = ne[i]) {
    Dfs1(v[i]);
    if (only[u_] == - 1) continue ;
    if (! only[u_]) {
      only[u_] = only[v[i]]; 
    } else if (only[u_] != only[v[i]]) {
      only[u_] = - 1; 
    }
  }
}
//=============================================================
int main() {
  int T = read();
  for (num = 1; num <= T; ++ num) {
    std :: cin >> S[num];
    int n = S[num].length(), last = 1;
    for (int j = 0; j < n; ++ j) last = Insert(S[num][j] - 'a', last);
  }
  for (int i = 2; i <= node_num; ++ i) AddEdge(link[i], i);
  Dfs1(1);
  for (int i = 2; i <= node_num; ++ i) {
    if (only[i] != - 1) ans[only[i]] += len[i] - len[link[i]];
  }
  for (int i = 1; i <= T; ++ i) printf("%d\n", ans[i]);
  return 0; 
}
```

---

### 算法二

```cpp
//知识点：广义 SAM
/*
By:Luckyblock  
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define ll long long
const int kMaxn = 2e5 + 10;
const int kMaxm = 26;
//=============================================================
std :: string S[kMaxn];
int only[kMaxn << 1], top[kMaxn << 1], sum[kMaxn << 1];
int num, node_num = 1, ch[kMaxn << 1][kMaxm], len[kMaxn <<1], link[kMaxn << 1];
int edge_num, head[kMaxn], v[kMaxn << 1], ne[kMaxn << 1]; 
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void AddEdge(int u_, int v_) {
  v[++ edge_num] = v_, ne[edge_num] = head[u_], head[u_] = edge_num;
}
int Insert(int c_, int last_) {
  if (ch[last_][c_]) {
    int p = last_, q = ch[p][c_];
    if (len[p] + 1 == len[q]) {
      only[q] = - 1;
      return q;
    }
    int newq = ++ node_num;
    memcpy(ch[newq], ch[q], sizeof(ch[q])); 
    len[newq] = len[p] + 1; 
    link[newq] = link[q];
    link[q] = newq; 
    for (; p && ch[p][c_] == q; p = link[p]) ch[p][c_] = newq;
    only[newq] = num;
    return newq;
  }
  int p = last_, now = ++ node_num;
  only[now] = num;
  len[now] = len[p] + 1;
  for (; p && ! ch[p][c_]; p = link[p]) ch[p][c_] = now;
  if (! p) {link[now] = 1; return now;} 
  int q = ch[p][c_];
  if (len[q] == len[p] + 1) {link[now] = q; return now;}
  int newq = ++ node_num;
  memcpy(ch[newq], ch[q], sizeof(ch[q])); 
  link[newq] = link[q], len[newq] = len[p] + 1; 
  link[q] = link[now] = newq;
  for (; p && ch[p][c_] == q; p = link[p]) ch[p][c_] = newq;
  return now;
}
void Dfs1(int u_) {
  for (int i = head[u_]; i; i = ne[i]) {
    Dfs1(v[i]);
    if (only[u_] == - 1) continue ;
    if (! only[u_]) {
      only[u_] = only[v[i]]; 
    } else if (only[u_] != only[v[i]]) {
      only[u_] = - 1; 
    }
  }
}
void Dfs2(int u_, int top_) {
  if (! top_ && only[u_] != - 1) top_ = u_;
  top[u_] = top_;
  if (top_) sum[u_] += len[u_] - len[link[u_]];
  for (int i = head[u_]; i; i = ne[i]) {
    Dfs2(v[i], top_);
    sum[u_] += sum[v[i]]; 
  }
}
void Work(std :: string S_) {
  std :: vector <int> node;
  ll ans = 0;
  int n = S_.length(), now = 1;
  for (int i = 0; i < n; ++ i) {
    now = ch[now][S_[i] - 'a'];
    if (only[now] != - 1) node.push_back(top[now]);
  }
  std :: sort(node.begin(), node.end());
  for (int i = 0, n = node.size(); i < n; ++ i) {
    if (i != 0) {
      if (node[i] == node[i - 1]) continue;
    }
    ans += sum[node[i]];
  }
  printf("%lld\n", ans);
}
//=============================================================
int main() {
  int T = read();
  for (num = 1; num <= T; ++ num) {
    std :: cin >> S[num];
    int n = S[num].length(), last = 1;
    for (int j = 0; j < n; ++ j) last = Insert(S[num][j] - 'a', last);
  }
  for (int i = 2; i <= node_num; ++ i) AddEdge(link[i], i);
  Dfs1(1), Dfs2(1, 0);
  for (int i = 1; i <= T; ++ i) Work(S[i]);
  return 0; 
}
```

---

## 作者：LYYY (赞：9)

最近刚学了后缀自动机，本蒟蒻对这道题没什么很巧妙的算法，但是有一个很暴力DP的做法。**整个算法不用parent树，仅在SAM的DAG（有向无环图）中动态规划。**



------------------------------------

# 算法思路：

## 第一步

将每个字符串连起来，并用不同的分隔符Ui隔开，构造一个后缀自动机。

### SS = S(1) + U(1) + S(2) + U(2) + S(3) + U(3) + ... + S(n) + U(n)

**1. 由于我们要对每一个S(i)的子串进行分析，所以首先考虑如何将所有的子串表示出来。**

考虑从节点1（即后缀自动机的根节点，表示空串，**下面用root表示**）开始的一条路径，显然其经过所有转移就形成了总串SS一个子串。

然后我们对这条路径加一些限制，要求这条路径必须以某个U(i)结束，且路径不经过U(j) ( j != i )，即以一个分隔符U结尾且不经过其他分隔符，易知，所有这样的路径都是S(i)的后缀，而Si的所有后缀必然都是这样的路径，后缀与路径一一对应，**称之为“后缀路径”**。

## 下文所说的“路径”均指 “除了结束点不经过任何分隔符” 的从root开始的在后缀自动机上的路径！！！一定注意！！

所以S(i)的所有子串可以通过它的后缀的前缀来表示，在后缀自动机中，子串就是后缀路径的一部分（同样以root开头，但是结束点不同的路径）。

这样我们就找到了S(i)的所有子串的表示方法，之后就是用动态规划的方式对S(1~n)的子串进行操作。

**2. 因为题目要求子串是不公共的，所以我们来分析一下公共子串的性质**

我们称刚才找到的后缀路径为path(i)。

根据上面的操作，我们再找到一个以U(j)为结尾的后缀路径path(j)，如果path(i)与path(j)有一部分前缀是重合的，那么这一部分就是S(i)与S(j)的公共子串。

**由于上述我们考虑的对答案有贡献的路径仅是最多只在结尾处有一个分隔符U的路径，因此在下一步的DP中，点fro如果有一条表示分隔符U的边连向点to（设这条边是从fro指向to的），那么当前就不再对to进行操作（但是to仍有可能被别的不是分隔符的边更新到）。**


## 第二步

 愉快地DP


### 整个DP过程分为三个阶段，就叫它们DP1，DP2，DP3吧QWQ


### （1）DP1（实现方式：记忆化搜索）———— 预处理合法节点

OK数组有三个值：

OK[x]==0 : 点x没有被遍历过；

OK[x]==1 : **从点x出发的所有路径**只能以同一个分隔符U为结尾，换句话说，**以x为结尾的所有路径**都是不公共子串。

OK[x]==2 : 与OK[x]==1相反。**从x出发的所有路径**中，结束字符不都是同一个分隔符，换句话说，**以x为结尾的所有路径**都被至少两个S包含。

我们用ID[x]来表示当前点x所能达到的U是哪个，即以x为结尾的所有路径都是S(ID[x])的子串。

通过记忆化搜索完成OK与ID的更新（最终OK==2的点的ID是没有意义的）：

分类讨论：

一. 当前边不是U

1. DP下一个点并判断下个点OK是否为2，若是，则当前点也为2；

else 2. 如果如果当前点ID未被更新（初值为-1），则用**下一个点的ID**（能到达的分隔符编号）更新ID；

else 3. 如果当前点的ID已被更新过，直接判断；

二. 当前边是U，则不继续DP；如果OK[x]已经为2，也不用再更新ID了（详见代码）

1. 如果当前点ID未被更新（初值为-1），则用**当前边**表示的分隔符编号更新ID；

else 2. 如果当前点的ID已被更新过，直接判断；


```cpp
int DP1(int x)
{
	if(OK[x]) return OK[x];
	for(map<int,int> ::iterator i=mp[x].begin();i!=mp[x].end();++i)
	{
		if(i->first<26)
		{
			if(DP1(i->second)==2||OK[x]==2) OK[x]=2;
			else if(ID[x]==-1) ID[x]=ID[i->second];
			else if(ID[x]!=ID[i->second]) OK[x]=2;
		}
		else if(OK[x]!=2)
		{
			if(ID[x]==-1) ID[x]=i->first;
			else if(ID[x]!=i->first) OK[x]=2;
		}
	}
	if(OK[x]) return 2;
	return OK[x]=1;
}
```
### （2）DP2（实现方式：拓扑排序）———— 预处理方案数

这一阶段我们来更新T数组，T[x]表示从root到x的不同路径有多少条，很简单：

```cpp
void DP2()
{
	for(int i=1;i<=cnt;++i)
	{
		for(map<int,int> ::iterator j=mp[i].begin();j!=mp[i].end();++j)
		{
			++IN[j->second];
		}
	}
	Q[++tail]=1;
	while(tail>=head)
	{
		int q=Q[head++];
		for(map<int,int> ::iterator i=mp[q].begin();i!=mp[q].end();++i)
		{
			if(!(--IN[i->second])) Q[++tail]=i->second;
		}
	}
	T[1]=1;
	for(int i=1;i<=tail;++i)
	{
		for(map<int,int> ::iterator j=mp[Q[i]].begin();j!=mp[Q[i]].end();++j)if(j->first<26)
		{
			T[j->second]+=T[Q[i]];
		}
	}
}
```
### （3）DP3（实现方式：记忆化搜索）———— 统计答案

Ans[x]表示S(x)的不公共子串数量。

我们来考虑以某条边为终止边的路径集合对答案的贡献，

设这条边edge是从fro指向to的，代表字符为c；

1. 如果c==U，那么edge对答案没有贡献且不向下搜索；

2. 如果OK[to]==2,那么edge对答案没贡献但是向下搜索，因为可能会搜索到对答案有贡献的边；

2. 如果OK[to]==1,那就意味着以edge为结尾的所有路径都是不公共的，对答案的贡献：Ans[ID[to]]+=T[fro]；并继续向下搜索。

我们在搜索的同时，用vis来表示是否访问过当前节点，以避免对答案Ans的重复计算和超时问题（所以才叫记忆化搜索嘛）；

```cpp
void DP3(int x)
{
	if(vis[x]) return;
	vis[x]=true;
	for(map<int,int> ::iterator i=mp[x].begin();i!=mp[x].end();++i)if((i->first)<26)
	{
		DP3(i->second);
		if(OK[i->second]&1) Ans[ID[i->second]-25]+=T[x];
	}
}
```

由于不能用数组存SAM上的边，否则MLE，所以用了map；

算法时间复杂度O(nlogn)，空间复杂度n；

本人自带大常数（雾

完整代码：

```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
typedef long long LL;
const int maxn=222222;
int N;
char ss[maxn];
int read()
{
	int s=0,c=getchar();
	while(c<48||c>57) c=getchar();
	while(c>=48&&c<=57) s=(s<<3)+(s<<1)+(c^48),c=getchar();
	return s;
}
void write(LL x)
{
	if(x>=10) write(x/10);
	putchar(x%10+48);
}
struct suffixautomation
{
	int cnt,lst,fa[maxn],len[maxn],OK[maxn],ID[maxn],Q[maxn],head,tail,T[maxn],IN[maxn];
	LL Ans[maxn];
	bool vis[maxn];
	map<int,int> mp[maxn];
	suffixautomation()
	{
		lst=cnt=head=1;
		memset(ID,0xff,sizeof(ID));
	}
	void Insert(int c)
	{
		int p=lst;len[lst=++cnt]=len[p]+1;
		for(;p&&!mp[p].count(c);p=fa[p])mp[p][c]=lst;
		if(!p){fa[lst]=1;return;}int q=mp[p][c];
		if(len[p]+1==len[q]){fa[lst]=q;return;}
		len[++cnt]=len[p]+1;
		mp[cnt]=mp[q];fa[cnt]=fa[q];fa[q]=fa[lst]=cnt;
		for(;mp[p].count(c) && mp[p][c]==q;p=fa[p]) mp[p][c]=cnt;
	}
	int DP1(int x)
	{
		if(OK[x]) return OK[x];
		for(map<int,int> ::iterator i=mp[x].begin();i!=mp[x].end();++i)
		{
			if(i->first<26)
			{
				if(DP1(i->second)==2||OK[x]==2) OK[x]=2;
				else if(ID[x]==-1) ID[x]=ID[i->second];
				else if(ID[x]!=ID[i->second]) OK[x]=2;
			}
			else if(OK[x]!=2)
			{
				if(ID[x]==-1) ID[x]=i->first;
				else if(ID[x]!=i->first) OK[x]=2;
			}
		}
		if(OK[x]) return 2;
		return OK[x]=1;
	}
	void DP2()
	{
		for(int i=1;i<=cnt;++i)
		{
			for(map<int,int> ::iterator j=mp[i].begin();j!=mp[i].end();++j)
			{
				++IN[j->second];
			}
		}
		Q[++tail]=1;
		while(tail>=head)
		{
			int q=Q[head++];
			for(map<int,int> ::iterator i=mp[q].begin();i!=mp[q].end();++i)
			{
				if(!(--IN[i->second])) Q[++tail]=i->second;
			}
		}
		T[1]=1;
		for(int i=1;i<=tail;++i)
		{
			for(map<int,int> ::iterator j=mp[Q[i]].begin();j!=mp[Q[i]].end();++j)if(j->first<26)
			{
				T[j->second]+=T[Q[i]];
			}
		}
	}
	void DP3(int x)
	{
		if(vis[x]) return;
		vis[x]=true;
		for(map<int,int> ::iterator i=mp[x].begin();i!=mp[x].end();++i)if((i->first)<26)
		{
			DP3(i->second);
			if(OK[i->second]&1) Ans[ID[i->second]-25]+=T[x];
		}
	}
	void Print(){for(int i=1;i<=N;++i) write(Ans[i]),puts("");}
}sam;
int main()
{
	N=read();
	for(int i=1;i<=N;++i)
	{
		scanf("%s",ss+1);
		int len=strlen(ss+1);
		for(int j=1;j<=len;++j) sam.Insert(ss[j]-'a');
		sam.Insert(25+i);
	}
	sam.DP1(1);
	sam.DP2();
	sam.DP3(1);
	sam.Print();
	return 0;
}
```
 _谢谢阅览！_ 

---

## 作者：Fading (赞：5)

不知道为什么楼下写$SAM$的写得这么奇怪啊

这个题目看到多模式串又是什么本质不同的串个数，一眼广义$SAM$啊

然后还有一个限制，这个串必须只在一个模式串中出现。

所以在添加每一个模式串的时候，给每一个节点覆盖上这一种模式串的标记就好啦！

如果这个节点被多个模式串覆盖过的话，我们就设他的覆盖标记$($代码里是数组$\texttt{fg})$为$-1$，否则就为覆盖过这个节点的模式串的编号。

特别地，我们在建立广义$SAM$的时候，设虚节点的覆盖标记为$0$。

然后最后基数排序一下，从后往前遍历。如果一个节点被覆盖，说明他的$parent$节点也被覆盖过了，就给他的$parent$打标记。

最后看看哪些节点只被覆盖过一次，给答案加上$len[i]-len[parent[i]]$就好啦！

这题还是十分套路的。

代码如下：

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char s[2000001];
ll ans[200001];
struct Suffix_Automaton{
    int cnt,last,g[2000001][27],c[2000001],pa[2000001],id[2000001],fg[2000001],len[2000001];
    inline void init(){
        cnt=last=1;
    }
    inline void insert(int ch,int tr){
        if (g[last][ch]&&len[last]+1==len[g[last][ch]]){
            last=g[last][ch];
            fg[last]=-1;//之前有这个节点产生了而且可以到达说明这个节点一定会被被覆盖多次
            return;
        }//广义SAM基本操作
        int np=++cnt,pos=last;last=cnt;len[np]=len[pos]+1;
        if (fg[cnt]==0) fg[cnt]=tr;
        else fg[cnt]=-1;//打上覆盖标记
        for (;pos&&!g[pos][ch];pos=pa[pos]) g[pos][ch]=np;
        if (!pos) pa[np]=1;
        else{
            int posx=g[pos][ch];
            if (len[pos]+1==len[posx]) pa[np]=posx;
            else{
                int q=++cnt;
                len[q]=len[pos]+1;
                for (int i=0;i<26;i++) g[q][i]=g[posx][i];
                pa[q]=pa[posx];pa[posx]=pa[np]=q;
                for (;g[pos][ch]==posx;pos=pa[pos]) g[pos][ch]=q;
            }
        }
    }
    inline void Sort(){
        for (int i=1;i<=cnt;i++) c[len[i]]++;
        for (int i=1;i<=cnt;i++) c[i]+=c[i-1];
        for (int i=1;i<=cnt;i++) id[c[len[i]]--]=i;//基数排序
        for (int i=cnt;i>=1;i--){
            int X=id[i];
            if (~fg[X]) ans[fg[X]]+=len[X]-len[pa[X]];//满足条件
            if (fg[pa[X]]==0) fg[pa[X]]=fg[X];//虚节点特判
            else if (fg[pa[X]]!=fg[X]) fg[pa[X]]=-1;//不等的话就是被多个串覆盖过
        }
    }
}sam;
int main(){
    int T;
    cin>>T;
    sam.init();
    char s[100005];
    for (int ii=1;ii<=T;ii++){
        sam.last=1;
        scanf("%s",s);
        int Le=strlen(s);
        for (int i=0;i<Le;i++){
            sam.insert(s[i]-'a',ii);
        }
    }
    int ANS=0;
    sam.Sort();
    for (int ii=1;ii<=T;ii++){
        printf("%lld\n",ans[ii]);
    }
    return 0;
}
```

---

## 作者：creation_hy (赞：4)

广义 SAM 板子题。

## 思路

首先对所有串建广义 SAM。

本题和模版唯一不同的一点就是，模版是统计总共有多少子串，多个相同串虽然不算，但是起码算一个，而这题是一个都不算。。。

考虑在 parent 树上染色。

做法：

- 建广义 SAM。

- 对于每个字符串，往上跳 father 指针。
  
  如果 parent 树当前节点已经染过其他颜色了，因为多个相同串一个都不算，那么就把它设为不可用。
  
  否则，将该节点染色为当前字符串编号。

最后统计答案的时候，直接按照染上的颜色统计即可。

如果当前颜色不可用，那就不管。否则把对应颜色的答案加上子串数量。

如果你不知道怎么求子串数量，~~说明你根本不会用 SAM~~，请参考 P2408 和 P6139。
  
还是很简单的。

具体实现（`update` 即染色函数）：

```cpp
inline void update(int x, int id)
{
    while (~x && ~num[x] && num[x] != id)
    {
        num[x] = num[x] ? -1 : id;
        x = fa[x];
    }
}
inline void solve()
{
    int p = 0;
    for (int i = 1; i <= n; i++, p = 0)
        for (char c : s[i])
            update(p = t[p][c - 'a'], i);
    for (int i = 0; i <= tot; i++)
        if (~num[i] && ~fa[i])
            ans[num[i]] += len[i] - len[fa[i]];
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}
```

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
string s[N];
int n;
struct SAM
{
    int tot, last, fa[N << 1], len[N << 1], t[N << 1][26];
    int num[N << 1], ans[N << 1];
    inline SAM()
    {
        tot = last = 0;
        fa[0] = -1;
    }
    inline void insert(char c)
    {
        c -= 'a';
        int cur = ++tot;
        len[cur] = len[last] + 1;
        int p = last;
        last = cur;
        while (~p && !t[p][c])
            t[p][c] = cur, p = fa[p];
        if (!~p)
        {
            fa[cur] = 0;
            return;
        }
        int x = t[p][c];
        if (len[p] + 1 == len[x])
            fa[cur] = x;
        else
        {
            len[++tot] = len[p] + 1;
            fa[tot] = fa[x];
            memcpy(t[tot], t[x], sizeof(t[x]));
            while (~p && t[p][c] == x)
                t[p][c] = tot, p = fa[p];
            fa[x] = fa[cur] = tot;
        }
    }
    inline void update(int x, int id)
    {
        while (~x && ~num[x] && num[x] != id)
        {
            num[x] = num[x] ? -1 : id;
            x = fa[x];
        }
    }
    inline void solve()
    {
        int p = 0;
        for (int i = 1; i <= n; i++, p = 0)
            for (char c : s[i])
                update(p = t[p][c - 'a'], i);
        for (int i = 0; i <= tot; i++)
            if (~num[i] && ~fa[i])
                ans[num[i]] += len[i] - len[fa[i]];
        for (int i = 1; i <= n; i++)
            cout << ans[i] << '\n';
    }
} sam;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        sam.last = 0;
        for (char c : s[i])
            sam.insert(c);
    }
    sam.solve();
    return 0;
}
```

---

## 作者：ctj12461 (赞：3)

看到题解区里没有后缀数组的题解，我就来发一篇。

在阅读之前，你需要对后缀数组和 $height$ 数组有一定的理解。

#### Part 1

如何求一个串的本质不同的子串个数？我们可以考虑用子串总数减去重复的子串个数。

处理出 $height$ 后，按照字典序从小到大枚举每个后缀，设当前后缀的排名为 $i$，可以发现后缀 $sa[i]$ 与后缀 $sa[i-1]$ 的 $LCP$ 为 $height[i]$，这也就是枚举时的前后两个串重复的部分，将其从答案中扣除即可。

所以一个串的本质不同的子串个数为:
$$
\frac{n(n+1)}{2}-\sum_{i=2}^{n}height[i]
$$

#### Part 2

如何求每个串的只属于自己的本质不同的子串个数？可以限求出每个子串的本质不同子串个数，在扣除公共的部分。

首先把每个串拼接起来，中间插入不同的分隔符，同时对每个部分进行染色。

我们仍然考虑按照字典序枚举，考虑两个相邻的后缀 $sa[i-1]$ 和 $sa[i]$，如果它们属于不同的串，那么它们的 $LCP$ 就应该被扣除。

但是现在我们就要考虑重复的问题，因为我们要从本质不同子串中扣除答案，重复的部分只能减去一次，我们可以通过下面的图形象地理解那些部分要被减掉。

![](https://cdn.luogu.com.cn/upload/image_hosting/ezq2u8tq.png)

我们用 $A,B$ 来表示不同的串，柱状图的高度表示两个串的 $height$。

当 $i=3$ 时，出现了公共的部分，此时 $A,B$ 都要减去 $height[3]$。

当 $i=5$ 时，又出现了公共部分，从图中显然可以看出与上一次减去的部分有重复，且重复的部分完全覆盖了现在的 A,B 串的公共部分，所以这次不能减去。

当 $i=7$ 时，$height[7]>height[5]$，所以我们这次减去 $height[7]-height[5]$，只有在 $height[5]$ 之上的部分是不重复的。为什么不是减去 $height[7]-height[3]$ 呢？因为后缀 $sa[3]$ 与后缀 $sa[7]$ 的 $LCP$，也就是它们相同的部分只有 $height[5]$ 及以下的部分，上面都是不同的。

当 $i=14$ 时，这次不是要减去 $height[14]-height[7]$，而是减去 $height[14]-height[11]$，因为 $LCP(13,7)=height[11]$，只有这部分是与前面减掉的部分有重复。

#### Part 3

现在有一个大体的思路：按照字典序枚举，考虑两个相邻的后缀 $sa[i-1]$ 和 $sa[i]$，如果它们属于不同的串，则减去它们的 $LCP$，同时考虑 $LCP$ 与先前减去的部分有多少是重叠的，把这部分再加回去。我们可以维护对每个串维护一个单调栈，维护一个从栈底到栈顶单调递增的序列，表示对于这个串的每次减去的长度（不考虑重复应减去的长度，这个东西其实就是 $height$）。

显然对于一个串，会重复的部分只可能是 $LCP$ 的部分。考虑 $LCP$ 长度为区间中 $height$ 的最小值的性质，其中不单调的部分不可能是 $LCP$ 的长度，对答案没有贡献，所以我们只要维护单调栈，重复的部分就是栈顶。

同时，若当前要减去的地方与上一次减去的地方这个区间里有更小的 $height$ （上图 $i=14$），公共的部分就变为这个 $height$，因此还要维护一个 `ST` 表。

#### Part 4

由于要为每个串维护一个单调栈，所以要用链表实现单调栈，或使用 `std::stack<T, std::list<T>>` 定义一个使用 `std::list<T>` 为的底层数据结构的栈。若没有使用这个定义，`std::stack<T>` 等价于 `std::stack<T, std::deque<T>>`，`std::deque<T>` 本质上是一个块状数据结构，容易 `MLE`。

```cpp
#include <cstdio>
#include <cstring>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

constexpr int maxn = 2e5 + 10;

/** 单调栈 */
class SteadyStack {
public:
    void push(int x) {
        while (!st.empty() && st.top() >= x)
            st.pop();

        st.push(x);
    }

    int top() {
        return (st.empty() ? 0 : st.top());
    }
private:
    /** 注意 stack 的定义 */
    stack<int, list<int>> st;
};

class SparseTable {
public:
    void preprocess(int a[], int n) {
        logv[0] = -1;

        for (int i = 1; i <= n; ++i)
            logv[i] = logv[i / 2] + 1;

        for (int i = 1; i <= n; ++i)
            data[i][0] = a[i];

        for (int j = 1; j <= 17; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                data[i][j] = min(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        if (l > r)
            return 0x3f3f3f3f;

        int s = logv[r - l + 1];
        return min(data[l][s], data[r - (1 << s) + 1][s]);
    }
private:
    int data[maxn][18];
    int logv[maxn];
};

int n, len, dat[maxn * 2]; /** dat 为拼接后的串 */
char str[maxn];
int sa[maxn * 4], buf[2][maxn * 4], *rk, height[maxn * 4];
int cnt[maxn * 4], id[maxn * 4], *old, tmp[maxn * 4];
int col[maxn * 2]; /** col[i] 表示在拼接后的串中 i 的属于那个串 */
long long ans[maxn];
SteadyStack st[maxn];
SparseTable mi;
int las[maxn]; /** 上一次减去的位置 */

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(int dat[], int n, int m) {
    for (int i = 1; i <= m; ++i)
        cnt[i] = 0;

    for (int i = 1; i <= n; ++i)
        ++cnt[rk[i] = dat[i]];

    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = n; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;

    for (int w = 1, p;; w *= 2, m = p) {
        p = 0;

        for (int i = n; i > n - w; --i)
            id[++p] = i;

        for (int i = 1; i <= n; ++i)
            if (sa[i] > w)
                id[++p] = sa[i] - w;

        for (int i = 1; i <= m; ++i)
            cnt[i] = 0;

        for (int i = 1; i <= n; ++i)
            ++cnt[tmp[i] = rk[id[i]]];

        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];

        for (int i = n; i >= 1; --i)
            sa[cnt[tmp[i]]--] = id[i];

        swap(rk, old);
        p = 0;

        for (int i = 1; i <= n; ++i)
            rk[sa[i]] = (equal(sa[i - 1], sa[i], w) ? p : ++p);

        if (p == n) {
            for (int i = 1; i <= n; ++i)
                sa[rk[i]] = i;

            break;
        }
    }

    for (int i = 1, j = 0; i <= n; ++i) {
        if (j)
            --j;

        while (dat[i + j] == dat[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }
}

/** 拼接字符串并计算出本质不同子串个数 */
void add(char str[], int id) {
    int start = len, l = strlen(str);

    for (int i = 0; i < l; ++i) {
        dat[++len] = str[i];
        col[len] = id;
    }

    dat[++len] = id + 127;
    preprocess(dat + start, l, 127);

    ans[id] = 1ll * l * (l + 1) / 2;

    for (int i = 1; i <= l; ++i)
        ans[id] -= height[i];
}

/** 扣除重复部分 */
void remove(int id, int l, int p) {
    ans[id] -= max(l - min(st[id].top(), mi.query(las[id] + 1, p - 1)), 0);
    st[id].push(l);
}

int main() {
    rk = buf[0], old = buf[1];

    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str);
        add(str, i);
    }

    preprocess(dat, len, 127 + n);
    mi.preprocess(height, len);

    for (int i = 2; i <= len; ++i) {
        if (col[sa[i - 1]] != col[sa[i]]) {
            remove(col[sa[i - 1]], height[i], i);
            remove(col[sa[i]], height[i], i);
            las[col[sa[i - 1]]] = i - 1;
            las[col[sa[i]]] = i;
        }
    }

    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);

    return 0;
}
```



---

## 作者：CTime_Pup_314 (赞：3)

更好的阅读体验

[CTime_Pup_314的博客](https://ctp314.github.io/)

# [P4081 [USACO17DEC]Standing Out from the Herd](https://www.luogu.org/problemnew/show/P4081)
>给定字符串集合，求只属于该字符串的本质不同的非空子串的个数

难度一般，建一个广义 $SAM$ 在 $Parent$ 树上对 $endpos$ 全部属于同一个字符串的统计即可

关键是下面的错误和解决方法

大部分直接按照 $maxlen$ 拓扑序会 $WA$，是因为如果字符串具有相同前缀则在广义 $SAM$ 中会出现 $maxlen(parent(A))= maxlen(A)$ 

主要是因为大部分广义 $SAM$ 的写法每次都必须新建一个 $np$ 节点，但实际上这个 $np$ 节点所表示的原串的前缀有可能在 $SAM$ 上出现了，但由于 $Parent$ 树的性质两者间有边相连，导致了 $maxlen$ 非严格单调递增的父子关系，可以通过 $\lbrace ab, abc\ \rbrace$ 体会一下

所以当 $maxlen$ 相同时，后加入的节点要靠后

但是按照我这种写法又 $WA$ 第 $2$ 个点，是由于新建的 $nq$ 节点应该继承 $np$ 节点的某一个 $endpos$ 而不是 $q$ 节点的 $endpos$

原因是我们会认为在某次加入操作时 $nq$ 的加入顺序晚于 $np$，导致 $np$ 最后不能及时更新 $nq$，那么一开始我们就应该将更晚的 $np$ 的某一个 $endpos$ 赋值给 $nq$
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
const int N = 2e5+5;
typedef long long int64;
int last = 1, tot = 1, pre, pos[N], len[N], fa[N], ch[N][26];
int tax[N], p[N];
int64 ans[N];
inline void insert(int c, int p)
{
    int cur = ++tot, pre = last; last = cur;
    len[cur] = len[pre]+1; pos[cur] = p;
    while(pre&&!ch[pre][c]) ch[pre][c] = cur, pre = fa[pre];
    if(!pre) return void(fa[cur] = 1);
    int x = ch[pre][c];
    if(len[pre]+1 == len[x]) return void(fa[cur] = x);
    int y = ++tot; fa[y] = fa[x]; pos[y] = p;
    fa[x] = fa[cur] = y; len[y] = len[pre]+1;
    memcpy(ch[y], ch[x], sizeof(ch[x]));
    while(pre&&ch[pre][c] == x) ch[pre][c] = y, pre = fa[pre]; 
}
int n;
char s[N];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    {
        last = 1; scanf("%s", s);
        for(int k = 0; s[k]; ++k) insert(s[k]-'a', i);
    }
    for(int i = 1; i <= tot; ++i) ++tax[len[i]];
    for(int i = 1; i <= tot; ++i) tax[i] += tax[i-1];
    for(int i = tot; i; --i) p[tax[len[i]]--] = i;
    for(int i = tot; i; --i) if(pos[fa[p[i]]] != pos[p[i]]) pos[fa[p[i]]] = 0;
    for(int i = 1; i <= tot; ++i) ans[pos[i]] += len[i]-len[fa[i]];
    for(int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
    return 0;
}
```

---

## 作者：ywy_c_asm (赞：3)

发现楼下两位大神一个用了$SA$而另一个用了$SAM$，这里来一个$SA+SAM$的做法~~我怕不是有毒~~

首先看到子串匹配果断就是后缀自动机，而且这个匹配涉及到所有字符串，就先对所有串建一个广义$SAM$，然后考虑答案怎么求，我们可以对这个字符串的每个位置求出以他为结尾的完美子串**最长**有多长，如果他是完美子串那么他的后缀也一定是完美子串就可以统计答案了，这个可以在$SAM$上运行这个字符串，然后这个位置会跑到一个节点，我们可以考虑对$SAM$上的每个节点都搞出一个区间，他的在这个长度区间内的字符串都是完美子串。

考虑广义$SAM$的构造过程，我们是一个串一个串往里插的，插的时候会新建一些一定在当前的串内出现过的节点，显然他出现过的位置他的$Parent$树上的祖先也一定出现过，并且可能会比后代出现在更多的位置上，那么我们可以通过在$Parent$树上$dfs$来判断这个节点是否仅出现在一个字符串内，一个非常简单的方法就是维护他出现在的字符串的最大与最小编号（相等那肯定就只出现在一个字符串里），这个可以从子树转移过来。如果一个点仅在一个字符串里出现的话，那么他肯定存在某个祖先开始在多个字符串内出现（我们认为根在所有字符串内都出现过），这是有单调性的，那么我们可以再进行一遍$dfs$维护一个栈存从根到他的所有祖先，我们在这个栈内二分出第一个不满足要求的祖先，那么这个点对应的答案区间就是从那个祖先往下到他的本来的区间（因为$SAM$上每个节点本来都有一个长度区间）的并集。

然后我们注意到一个严重的问题，就是这样做会把相同的子串都算一遍（因为我们统计$SAM$上每个点的时候算的不仅仅是他自己的字符串），然后我就受到后缀数组求不同子串个数的启发，对反串（因为我们统计的是以每个位置结尾的串的个数，如果算重的话就是两个前缀的最长公共后缀，也就是反串的两个后缀的$LCP$，这个就可以用后缀数组做了）跑一遍$SA$，然后我们把这个位置在反串对应位置的$Height$找到，这相当于给了你一个长度区间表示以这个位置结尾的多长的字符串是重复计算的，我们减去它与当前$SAM$节点上长度区间的交集就行了。

~~写到这里突然发现貌似只从$Parent$树上的父亲找区间然后栈内二分跑反串的后缀数组什么的好像就都不用了……细思极恐……~~

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
namespace ywy
{
	char str[100002];
	inline int get()
	{
		register int ptr=1;
		char c;
		while((c=getchar())||23333)if(c>='a'&&c<='z')break;
		str[ptr]=c;
		ptr++;
		while((c=getchar())||23333)
		{
			if(c>='a'&&c<='z')str[ptr]=c,ptr++;
			else return(ptr-1);
		}
	} char s[2000001];
	int sam[2100001][26],fa[2100001],len[2100001],mins[2100001],maxs[2100001],stk[2100001];
	typedef struct _b
	{
		int dest;
		int nxt;
	} bian;
	bian memchi[1000001];
	int gnn=1,heads[2100001];
	inline void add(int s,int t)
	{
		memchi[gnn].dest=t;
		memchi[gnn].nxt=heads[s];
		heads[s]=gnn;
		gnn++;
	} int gn=2;
	inline int zhuanyi(int p,int x,int cjr)
	{
		int me=gn;
		gn++;
		len[me]=len[p]+1;
		maxs[me]=cjr;
		mins[me]=cjr;
		while(p&&!sam[p][x])sam[p][x]=me,p=fa[p];
		if(!p)
		{
			fa[me]=1;
			return(me);
		}
		int q=sam[p][x];
		if(len[q]==len[p]+1)
		{
			fa[me]=q;
			return(me);
		}
		int nq=gn;
		gn++;
		len[nq]=len[p]+1;
		fa[nq]=fa[q];
		fa[q]=fa[me]=nq;
		maxs[nq]=cjr;
		mins[nq]=cjr;
		for(register int i=0; i<26; i++)sam[nq][i]=sam[q][i];
		while(p&&sam[p][x]==q)sam[p][x]=nq,p=fa[p];
		return(me);
	} int f[2100001];
	int poss[1000001],lens[1000001];
	void dfs(int pt)
	{
		for(register int i=heads[pt]; i; i=memchi[i].nxt)
		{
			dfs(memchi[i].dest);
			mins[pt]=min(mins[pt],mins[memchi[i].dest]);
			maxs[pt]=max(maxs[pt],maxs[memchi[i].dest]);
		}
	} int minl[1000001];
	void efs(int pt,int deep)
	{
		stk[deep]=pt;
		for(register int i=heads[pt]; i; i=memchi[i].nxt)efs(memchi[i].dest,deep+1);
		if(pt!=1&&mins[pt]==maxs[pt])
		{
			int ans=deep,l=1,r=deep;
			while(l<=r)
			{
				int mid=(l+r)>>1;
				if(maxs[stk[mid]]==mins[stk[mid]])ans=mid,r=mid-1;
				else l=mid+1;
			}
			f[pt]=len[pt]-len[stk[ans-1]];
			minl[pt]=len[stk[ans-1]]+1;
		}
	}
	void print(ll num)
	{
		if(num>=10)print(num/10);
		putchar(num%10+'0');
	} int sa[1000001],sums[1000001],rk[1000001],temp[1000001],lst[1000001],tsa[1000001],trk[1000001];
	int lstcnt[1000001],h[1000001];
	unsigned char bv[1000001];
	inline int getrank(int a,int b)
	{
		if(lst[a]==b)
		{
			lstcnt[a]++;
			return(sums[a]);
		}
		sums[a]-=lstcnt[a];
		lstcnt[a]=1;
		lst[a]=b;
		return(sums[a]);
	}
	inline void SA(int n)
	{
		for(register int i=1; i<='z'; i++)sums[i]=0;
		for(register int i=1; i<=n; i++)sums[str[i]]++;
		for(register int i=1; i<='z'; i++)sums[i]+=sums[i-1];
		for(register int i=1; i<=n; i++)rk[i]=sums[str[i]-1]+1;
		for(register int i=1; i<=n; i++)sa[sums[str[i]]]=i,sums[str[i]]--;
		for(register int i=1; i<='z'; i++)sums[i]=0;
		for(register int bit=1; (1<<(bit-1))<=n; bit++)
		{
			unsigned char bswitch=1;
			for(register int i=1; i<=n; i++)sums[i]=0,bv[i]=0;
			for(register int i=1; i<=n; i++)sums[rk[i]]++;
			for(register int i=1; i<=n; i++)sums[i]+=sums[i-1],lst[i]=-1,lstcnt[i]=0,temp[i]=sums[i];
			for(register int i=n; i>=1; i--)
			{
				if(sa[i]<=(1<<(bit-1)))continue;
				trk[sa[i]-(1<<(bit-1))]=getrank(rk[sa[i]-(1<<(bit-1))],rk[sa[i]]);
				tsa[temp[rk[sa[i]-(1<<(bit-1))]]]=sa[i]-(1<<(bit-1));
				temp[rk[sa[i]-(1<<(bit-1))]]--;
			}
			for(register int i=n; i>n-(1<<(bit-1)); i--)
			{
				trk[i]=getrank(rk[i],0);
				tsa[temp[rk[i]]]=i;
				temp[rk[i]]--;
			}
			for(register int i=1; i<=n; i++)
			{
				sa[i]=tsa[i];
				if(bv[rk[i]=trk[i]])bswitch=0;
				bv[rk[i]]=1;
			}
			if(bswitch)break;
		}
	}
	inline void Height(int n)
	{
		for(register int i=1; i<=n; i++)
		{
			h[i]=max(0,h[i-1]-1);
			while(rk[i]!=1&&h[i]<min(n-i+1,n-sa[rk[i]-1]+1)&&str[i+h[i]]==str[sa[rk[i]-1]+h[i]])h[i]++;
		}
	}
	void ywymain()
	{

		memset(mins,0x7f,sizeof(mins));
		int cnt;
		cin>>cnt;
		poss[0]=1;
		int p=1;
		for(register int a=1; a<=cnt; a++)
		{
			int n=get();
			poss[a]=poss[a-1]+lens[a-1];
			lens[a]=n;
			p=1;
			int ptr=poss[a];
			for(register int i=1; i<=n; i++)p=zhuanyi(p,str[i]-'a',a),s[ptr]=str[i],ptr++;
		}
		for(register int i=2; i<gn; i++)add(fa[i],i);
		dfs(1);
		efs(1,0);
		for(register int a=1; a<=cnt; a++)
		{
			for(register int i=lens[a]; i>=1; i--)sums[i]=0,str[lens[a]-i+1]=s[poss[a]+i-1];
			SA(lens[a]);
			Height(lens[a]);
			int cur=1;
			ll ans=0;
			for(register int i=poss[a]; i<poss[a]+lens[a]; i++)
			{
				cur=sam[cur][s[i]-'a'];
				ans+=f[cur];
				if(f[cur])ans-=max(0,h[lens[a]-(i-poss[a]+1)+1]-minl[cur]+1);
			}
			printf("%lld",ans);
			if(a!=cnt)cout<<endl;
		}
	}
}
int main()
{
	ywy::ywymain();
	return(0);
}
```

---

## 作者：_ctz (赞：2)

[$My\ blog$](https://ctz45562.github.io/2019/04/27/%E6%B4%9B%E8%B0%B7-P4081-USACO17DEC-Standing-Out-from-the-Herd/)

[传送门](https://www.luogu.org/problemnew/show/P4081)

感觉我的做法好鬼畜啊。。。是不是错了啊

不过~~可爱的~~$asuldb$跟我做法一样诶$QwQ$

把所有串用特殊字符隔开，拼一块造$SAM$。

$endpos$集合就是子串出现位置，如果一个节点的$endpos$只在一个串里出现过，它就可以算进独特值里。

造$SAM$的时候可以给节点染个色，然后在$parent\ tree$上向上合并，如果某个节点只有一种颜色$x$，就可以给$x$产生贡献。

因为把所有串拼了起来，会有不是$x$的子串出现，就要记录一下最大的$endpos$值$ma$，显然$ma[i]=\max\{ma[j]\}(fa[j]=i)$，再记录一下每个串左端点的位置$ll[x]$，贡献就是$(ma[i]-len[fa[i]])-max\{ma[i]-len[i]+1,ll[x]\}+1$

有可能该节点没有一个子串属于$x$，就会有负数，对$0$取个$\max$就好啦。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 200005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
#define son(x,y) son[x][y]
int h[maxn],col[maxn],ll[maxn],ma[maxn],son[maxn][27],fa[maxn],len[maxn],ans[maxn],last=1,cnt=1,all,num,n;
char s[maxn];
struct edge{
	int pre,to;
}e[maxn];
inline void add(int from,int to){
	e[++num].pre=h[from],h[from]=num,e[num].to=to;
}
inline void merge(int &x,int y){
	if(x==y)return;
	if(x==-1||y==-1||x&&y)x=-1;
	else x=x|y;
}//合并颜色
void insert(int c,int i=0){
	int p=last,ne=last=++cnt;
	len[ne]=len[p]+1,ma[ne]=len[ne],col[ne]=i;//染色
	while(p&&!son(p,c))son(p,c)=ne,p=fa[p];
	if(!p)fa[ne]=1;
	else {
		int q=son(p,c);
		if(len[q]==len[p]+1)fa[ne]=q;
		else {
			int sp=++cnt;
			memcpy(son[sp],son[q],sizeof son[q]);
			fa[sp]=fa[q],len[sp]=len[p]+1,fa[q]=fa[ne]=sp;
			while(p&&son(p,c)==q)son(p,c)=sp,p=fa[p];
		}
	}
}
void dfs(int node=1){
	int x;
	for(register int i=h[node];i;i=e[i].pre)
		x=e[i].to,dfs(x),merge(col[node],col[x]),ma[node]=max(ma[node],ma[x]);
	x=col[node];
	if(~x)ans[x]+=max((ma[node]-len[fa[node]])-max(ma[node]-len[node]+1,ll[x])+1,0);
}
int main(){
	n=read();
	int m,N=0;
	for(register int i=1;i<=n;++i){
		scanf("%s",s+1),m=strlen(s+1);
		for(register int j=1;j<=m;++j)insert(s[j]-'a',i);
		ll[i]=N+1,N+=m+1;//记录左端点
		if(i!=n)insert(26);//特殊字符
	}
	for(register int i=2;i<=cnt;++i)add(fa[i],i);
	dfs();
	for(register int i=1;i<=n;++i)printf("%d\n",ans[i]);
}

```



---

## 作者：Cgod (赞：2)

菜鸡我玩SA玩得很烂，只好写SAM。。。

这题难度怕是有鬼   ~~我不会告诉你我也评了NOI+CTSC的~~

步入正题，就是建广义SAM，不会自行度娘。

一个节点有贡献，当且仅当它只属于一个字符串。

每个非克隆节点保存该字符串编号。

然后parent树上dfs，i能属于的字符串fa[i]也必然属于;当i已经不满足条件了，fa[i]也不会满足;当fa[i]没被标记过就可以直接用i标记;当fa[i]被标记且i标记与fa[i]标记不同时，fa[i]显然会被一个以上的字符串包含，无贡献。

又每个节点表示的子串个数为len[i]-len[fa[i]];

统计一下就好啦。。。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 300055
#define gt getchar()
char s[N];int n,kk,len[N],ch[N][26],fa[N],ans[N],lz[N],p,q,np,nq,last=1,cnt=1;
int head[N],to[N],nxt[N],tot;
inline void add(int u,int v){to[++tot]=v,nxt[tot]=head[u],head[u]=tot;}
inline void extend(int c)
{
    p=last;len[np=++cnt]=len[p]+1;lz[np]=kk;
    while(p&&!ch[p][c])ch[p][c]=np,p=fa[p];
    if(!p)fa[np]=1;
    else
    {
        q=ch[p][c];
        if(len[p]+1==len[q])fa[np]=q;
        else
        {
            len[nq=++cnt]=len[p]+1;
            fa[nq]=fa[q];
            memcpy(ch[nq],ch[q],sizeof ch[q]);
            fa[q]=fa[np]=nq;
            while(p&&ch[p][c]==q)ch[p][c]=nq,p=fa[p];
        }
    }
    last=np;
}
void dfs(int u)
{
    for(int i=head[u];i;i=nxt[i])dfs(to[i]);
    for(int i=head[u];i;i=nxt[i])
    {
        if(lz[to[i]]==-1){lz[u]=-1;break;}
        if(!lz[to[i]])continue;
        if(!lz[u])lz[u]=lz[to[i]];
        else if(lz[u]!=lz[to[i]]){lz[u]=-1;break;}
    }
}
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        ++kk;
        scanf("%s",s+1);last=1;
        int lll=strlen(s+1);
        for(int i=1;i<=lll;++i)extend(s[i]-'a');
    }
    for(int i=2;i<=cnt;++i)add(fa[i],i);
    dfs(1);
    for(int i=1;i<=cnt;++i){if(lz[i]==-1)continue;ans[lz[i]]+=len[i]-len[fa[i]];}
    for(int i=1;i<=kk;++i)printf("%d\n",ans[i]);
    return 0;
}

```

---

## 作者：asuldb (赞：1)

不会广义$SAM$啊

但信仰插入特殊字符就可以搞定一切了

我们先把所有的串搞在一起建出一个$SAM$，记得在中间插入特殊字符

对于$parent$树上的一个节点，只有当其$endpos$集合中的所有元素都来自于同一个串的时候我们才对它进行统计

所以我们需要维护一个$parent$树上子树最大值和最小值，这样我们就能很快的判断这个$endpos$是否合法了

但是非常棘手的一类情况是我们插进去的特殊字符，显然$SAM$里有一些奇奇怪怪的子串中含有特殊字符

那也好办，我们存好每个串的起始位置只要那些没有跨越特殊字符的就好了

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 200005
#define re register
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
struct E{int v,nxt;} e[maxn];
char S[maxn];
int m,n,lst=1,cnt=1,num;
int len[maxn],fa[maxn],son[maxn][27],mx[maxn],ml[maxn];
int f[maxn],head[maxn],d[maxn],Ans[maxn],li[maxn];
inline void add(int x,int y) {e[++num].v=y;e[num].nxt=head[x];head[x]=num;}
void dfs(int x) {
	for(re int i=head[x];i;i=e[i].nxt) 
		dfs(e[i].v),mx[x]=max(mx[e[i].v],mx[x]),ml[x]=min(ml[e[i].v],ml[x]),d[x]|=d[e[i].v];
}
inline void ins(int c,int o)
{
	int f=lst,p=++cnt; lst=p;
	len[p]=len[f]+1,mx[p]=ml[p]=o;
	if(c==26) d[p]=1;
	while(f&&!son[f][c]) son[f][c]=p,f=fa[f];
	if(!f) {fa[p]=1;return;}
	int x=son[f][c];
	if(len[f]+1==len[x]) {fa[p]=x;return;}
	int y=++cnt;
	len[y]=len[f]+1,fa[y]=fa[x],fa[x]=fa[p]=y;
	for(re int i=0;i<27;i++) son[y][i]=son[x][i];
	while(f&&son[f][c]==x) son[f][c]=y,f=fa[f];
}
int main()
{
	memset(ml,20,sizeof(ml));
	scanf("%d",&m);
	for(re int i=1;i<=m;i++)
	{
		scanf("%s",S+1);
		int len=strlen(S+1);li[i]=n+1;
		for(re int j=1;j<=len;j++) ins(S[j]-'a',++n),f[n]=i;
		ins(26,++n);
	}
	for(re int i=2;i<=cnt;i++) add(fa[i],i);
	dfs(1);
	for(re int i=2;i<=cnt;i++)
	{
		if(d[i]) continue;
		if(f[mx[i]]!=f[ml[i]]) continue;
		int minlen=len[fa[i]]+1;
		if(f[mx[i]-minlen+1]!=f[mx[i]]) continue;
		if(f[mx[i]-len[i]+1]==f[mx[i]]) Ans[f[mx[i]]]+=len[i]-len[fa[i]];
			else Ans[f[mx[i]]]+=mx[i]-li[f[mx[i]]]-minlen+2;
	}
	for(re int i=1;i<=m;i++) printf("%d\n",Ans[i]);
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

建广义 SAM，考虑标记 $e_i$ 表示 $i$ 点属于哪个串（特别地，若 $i$ 点属于多个串，则 $e_i=-1$）。

也就是说，对于 $T$ 串的每个前缀，将其对应节点的 link 树根链“染上” $T$ 色，

（注意这里的“染色”与传统的染色不同，若一个点被染上多种颜色，则其颜色为 $-1$）

可以将其树上差分为单点染色，子树求颜色并，最终可以得到每个点的颜色。

考虑每个点的贡献，显然 $e_i=-1$ 时 $i$ 无贡献，否则 $i$ 对 $e_i$ 串的答案有 $\text{len}(i)-\text{len}(\text{link}(i))$ 的贡献。

```cpp
#include <queue>
#include <string>
#include <iostream>
using namespace std;
queue<int> q;
int T, n, o, z, e[200050], l[200050], f[200050], d[200050], c[200050][26];
long long Q[200050];
string u[200050];
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
int U(int x, int y)
{
    if (!x)
        return y;
    if (!y)
        return x;
    if (x == y)
        return x;
    return -1;
}
int main()
{
    f[0] = -1;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i)
    {
        cin >> u[i];
        z = 0;
        for (auto j : u[i])
            I(j - 'a');
    }
    for (int i = 1; i <= T; ++i)
        for (int j = 0, p = 0; j < u[i].size(); ++j)
            p = c[p][u[i][j] - 'a'], e[p] = U(e[p], i);
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
        if (~e[u])
            Q[e[u]] += l[u] - l[f[u]];
        e[f[u]] = U(e[f[u]], e[u]);
        if (!--d[f[u]])
            q.push(f[u]);
    }
    for (int i = 1; i <= T; ++i)
        printf("%lld\n", Q[i]);
    return 0;
}
```


---

## 作者：lgswdn_SA (赞：0)

Ukkonen 算法

多串问题考虑把所有字符串用分隔符拼起来，这样我们很快就能知道对于每个叶节点，它属于是哪个串的后缀。对于一个节点，如果其子树中的所有叶节点都只属于同一个串，那么这个节点及其边所代表的子串就是 unique 的，计入答案贡献。

注意，我们在计算答案的时候，如果遇到了一个分隔符，就不能继续往下 dfs 下去并统计答案了，因为这些子串都已经不是原子串而是若干个串加上分隔符拼成的一个辅助串了。

分隔符不需要每个串都不同，只需要结束符和分隔符不同就可以，然后记录一下每一个分隔符代表第几个串的结束。

```cpp
int n,m,c,s[N],col[N],endd[N],ans[N];
char str[N];

int sz,cnt=1,now=1,rem,ch[N<<1][28],link[N<<1],st[N<<1],len[N<<1]={inf},f[N<<1];
int newn(int s,int l) {return link[++cnt]=1,st[cnt]=s,len[cnt]=l,cnt;}
void extend(int x) {
	int last=1; sz++, rem++;
	while(rem) {
		while(rem>len[ch[now][s[sz-rem+1]]])
			rem-=len[now=ch[now][s[sz-rem+1]]];
		int &v=ch[now][s[sz-rem+1]], c=s[st[v]+rem-1];
		if(x==c||!v) {
			link[last]=now, last=now;
			if(!v) v=newn(sz-rem+1,inf);
			else break;
		} else {
			int u=newn(st[v],rem-1);
			ch[u][x]=newn(sz,inf), ch[u][c]=v;
			st[v]+=rem-1, len[v]-=rem-1;
			link[last]=v=u, last=u;
		}
		(now==1)?rem--:now=link[now];
	}
}
void dfs1(int u,int dep,bool leaf=1) { //求叶节点属于哪个串，然后判断每个节点子树的叶节点是否都是属于同一子串
	rep(i,0,27) if(ch[u][i]) {
		int v=ch[u][i]; leaf=0;
		dfs1(v,dep+len[v]);
		if(f[v]==-1||f[u]&&f[u]!=f[v]) f[u]=-1;
		else f[u]=f[v];
	}
	if(leaf) f[u]=col[n-dep+1];
}
void dfs2(int u,int dep,bool leaf=1) {
	if(col[st[u]]==col[st[u]+len[u]-1]&&s[st[u]]<26&&s[st[u]+len[u]-1]<26) {
		rep(i,0,27) if(ch[u][i]) dfs2(ch[u][i],dep+len[ch[u][i]]);
	}
	if(f[u]>0) ans[f[u]]+=min(len[u],endd[f[u]]-st[u]);
}

int main() {
	c=read();
	rep(i,1,c) {
		scanf("%s",str+1); m=strlen(str+1);
		rep(j,1,m) s[++n]=str[j]-'a', col[n]=i;
		s[++n]=(i==c?27:26), col[n]=i, endd[i]=n;
		rep(j,n-m,n) extend(s[j]);
	}
	rep(i,1,cnt) if(len[i]>n) len[i]=n-st[i]+1;
	dfs1(1,0);
	dfs2(1,0);
	rep(i,1,c) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Polaris_Dane (赞：0)

考虑我们会用的东西，如果对一个串建后缀树

那么后缀树中所有边的长度和即为不同字串个数

那么考虑我们的样例

![](https://cdn.luogu.com.cn/upload/image_hosting/z7xvzbfv.png)

~~通过大量观察~~

我们发现如果一个节点子树中叶节点所处后缀属于同一个串

那么答案加上该点上方属于该串的长度

所以不允许经过分隔符

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 400100
#define N 500100
#define inf 2e9
#define LL long long
const int mod=998244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int n,q,strl,strcnt,ref[M],ans[M],ed[M],lens[M];
char str[200100];
struct Suffix_Tree{
	int	link[M<<1],len[M<<1],ch[M<<1][28],start[M<<1],tot,rem,now,s[M<<1],col[M<<1];
	inline void reset(void){
		memset(ch[tot],0,sizeof(ch[tot])); 
		while (tot--) memset(ch[tot],0,sizeof(ch[tot]));
		len[0]=inf,tot=1,n=rem=0,now=1;	
	}
	inline int New(int st,int le){start[++tot]=st,len[tot]=le,link[tot]=1;return tot;}
	inline void extend(int x){
		s[++n]=x,rem++;
		for (int last=1;rem;){
			while (rem>len[ch[now][s[n-rem+1]]])
				rem-=len[now=ch[now][s[n-rem+1]]];
			int &v=ch[now][s[n-rem+1]],c=s[start[v]+rem-1];
			if (!v||x==c){
				link[last]=now,last=now;
				if (!v) v=New(n-rem+1,inf);
				else break;
			}
			else{
				int u=New(start[v],rem-1);
				ch[u][c]=v,ch[u][x]=New(n,inf);
				start[v]+=rem-1,len[v]-=rem-1;
				link[last]=v=u,last=u;
			}
			if (now==1) rem--;else now=link[now];
		}
	}
	inline void adjust(int x){
		int cnt=0;
		for (register int i=0;i<=27;++i)
			if (ch[x][i]) cnt++,adjust(ch[x][i]);
		if (!cnt) len[x]=strl-start[x]+1;
	}
	inline void redfs(int x,int dep){
		int cnt=0;
		for (register int i=0;i<=27;++i)
			if (ch[x][i]){
				cnt++,redfs(ch[x][i],dep+len[ch[x][i]]);
				if ((col[x]!=col[ch[x][i]]&&col[x]!=0)||col[ch[x][i]]==-1){col[x]=-1;continue;}
				col[x]=col[ch[x][i]];
			}
		if (!cnt) col[x]=ref[strl-dep+1];
	}
	inline void dfs(int x,int dep){
		if (!(ref[start[x]]!=ref[start[x]+len[x]-1]||!ref[start[x]]||!ref[start[x]+len[x]-1])||x==1){
			for (int i=0;i<=27;i++)
				if (ch[x][i])
					dfs(ch[x][i],dep+len[ch[x][i]]);
		}	
		if (col[x]>0) ans[col[x]]+=min(len[x],ed[col[x]]-start[x]+1);
	}
}tree;
signed main(void){
//	freopen("P4081_3.in","r",stdin);
//	freopen("myout.out","w",stdout);
	strcnt=read(),tree.reset();
	for (int i=1;i<=strcnt;i++){
		scanf("%s",str+1);
		lens[i]=strlen(str+1);ed[i]=strl+lens[i];
		for (int j=strl+1;j<=strl+lens[i];j++) ref[j]=i;
		for (int j=1;j<=lens[i];j++) tree.extend(str[j]-'a');
		tree.extend(i==strcnt?27:26),strl+=lens[i]+1;
	}strl--;
	tree.adjust(1);
	tree.redfs(1,0);
	tree.dfs(1,0);
	for (int i=1;i<=strcnt;i++) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：zhengrunzhe (赞：0)

建个广义sam

我不会用什么vis数组打标记

我也没写什么set启发式合并

这里提供一个线段树合并的

建广义sam的时候判重会好点，就是看是否需要新建np类节点，因为如果已经有了可以直接共用，这个节点同时享有两种颜色(颜色即串的编号)

然后在parent树上一波线段树合并，就可以知道每个点的子树内有多少种颜色，如果一个点代表的子串是独特的，那它子树内必然只有一种颜色，一个节点能够代表$len[p]-len[fa[p]]$个子串，把该种颜色的答案加上这个玩意即可

```cpp
#include<cstdio>
#include<cstring>
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)out=-out,putchar('-');
	write(out);
	putchar('\n');
}
const int N=1e5+10;
typedef long long ll;
int n;
ll *ans;
char s[N];
template<int maxn>class Segment_Tree
{
	private:
		struct tree
		{
			int sum;
			tree *lson,*rson;
			inline const void pushup()
			{
				sum=lson->sum+rson->sum;
			}
			inline const int findonly(int l,int r)
			{
				if (l==r)return l;
				int mid=l+r>>1;
				if (lson->sum)return lson->findonly(l,mid);
				return rson->findonly(mid+1,r);
			}
		}*root[maxn],memory_pool[maxn*40],*tail,*null;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			null->lson=null->rson=null;
			for (int i=1;i<maxn;i++)root[i]=null;
		}
		inline tree *spawn()
		{
			tree *p=tail++;
			p->lson=p->rson=null;
			return p;
		}
		inline const void insert(tree *&p,int l,int r,int pos)
		{
			if (p==null)p=spawn();
			p->sum++;
			if (l==r)return;
			int mid=l+r>>1;
			if (pos<=mid)insert(p->lson,l,mid,pos);
			else insert(p->rson,mid+1,r,pos);
		}
		inline tree *merge(tree *a,tree *b,int l,int r)
		{
			if (a==null&&b==null)return null;
			if (a==null)return b;
			if (b==null)return a;
			tree *p=spawn();
			if (l==r)return p->sum=a->sum|b->sum,p;
			int mid=l+r>>1;
			p->lson=merge(a->lson,b->lson,l,mid);
			p->rson=merge(a->rson,b->rson,mid+1,r);
			p->pushup();
			return p;
		}
	public:
		inline Segment_Tree(){init();}
		inline const void insert(int p,int k)
		{
			insert(root[p],1,n,k);
		}
		inline const int query(int p)
		{
			return root[p]->sum;
		}
		inline const void merge(int a,int b)
		{
			root[a]=merge(root[a],root[b],1,n);
		}
		inline const int findonly(int p)
		{
			return root[p]->findonly(1,n);
		}
};
template<int maxn,int maxc>class Suffix_Automaton
{
	private:
		static const int maxs=maxn<<1;
		ll ans[maxn];
		vector<int>own[maxs];
		Segment_Tree<maxs>sgt;
		int head[maxs],edc,to[maxs],next[maxs];
		int len[maxs],last,cnt,son[maxs][maxc],fa[maxs];
		inline const void addedge(int u,int v)
		{
			next[++edc]=head[u];to[head[u]=edc]=v;
		}
		inline const void extend(int id,int c)
		{
			int p=last;
			if (!son[p][c])
			{
				int np=++cnt;
				sgt.insert(np,id);
				len[last=np]=len[p]+1;
				for (;p&&!son[p][c];p=fa[p])son[p][c]=np;
				if (!p)return fa[np]=1,void();
				int q=son[p][c];
				if (len[q]==len[p]+1)return fa[np]=q,void();
				int nq=++cnt;len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof(son[q]));
				fa[nq]=fa[q];fa[q]=fa[np]=nq;
				for (;son[p][c]==q;p=fa[p])son[p][c]=nq;
				return;
			}
			int q=son[p][c];
			if (len[q]==len[p]+1)return sgt.insert(last=q,id);
			int nq=++cnt;len[nq]=len[p]+1;
			memcpy(son[nq],son[q],sizeof(son[q]));
			fa[nq]=fa[q];fa[q]=nq;
			for (;son[p][c]==q;p=fa[p])son[p][c]=nq;
			sgt.insert(last=nq,id);
		}
		inline const void dfs(int p)
		{
			for (int i=head[p];i;i=next[i])dfs(to[i]),sgt.merge(p,to[i]);
		}
	public:
		inline Suffix_Automaton():cnt(1){}
		inline const void insert(int id,char *s)
		{
			last=1;
			int n=strlen(s+1);
			for (int i=1;i<=n;i++)extend(id,s[i]-'a');
		}
		inline ll *build()
		{
			for (int i=2;i<=cnt;i++)addedge(fa[i],i);
			dfs(1);
			for (int i=1;i<=cnt;i++)
				if (sgt.query(i)==1)
					ans[sgt.findonly(i)]+=len[i]-len[fa[i]];
			return ans;
		}
};
Suffix_Automaton<N,26>sam;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%s",s+1),sam.insert(i,s);
	ans=sam.build();
	for (int i=1;i<=n;i++)writeln(ans[i]);
	return 0;
}
```

---

## 作者：Jμdge (赞：0)

比较裸的 sam ，争取一遍 A 

三倍经验： 

[脖子oj 3277 串](https://www.lydsy.com/JudgeOnline/problem.php?id=3277)

[洛咕 SP8093  JZPGYZ](https://www.luogu.org/problemnew/show/SP8093)

（注意只是类似的做法而已）


# noteskey


同上，类似的做法就是所有串跑一个 sam （有点像广义 sam 但又不是广义 sam 的建法），顺便记录一下 np 

然后一通乱搞搞出所有节点的 num 值（当前串 p 只在一个串中出现则是 $len[p]-len[fa[p]]$，否则为 0）

然后我们询问的时候去找当前串所有记录下来的节点，每个节点我们考虑跑它 parent 树上的 fa，如果说当前访问过就 break 

然后复杂度是 $O(\sum_{i=1}^n{len_s})$ 的，也就是 1e5

询问的时候有点清新...


# code

```
//by Judge
#include<cstdio>
#include<cstring>
#include<iostream>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define go(G,u) for(Rg int i=G.head[u],v=G.e[i].to;i;v=G.e[i=G.e[i].nxt].to)
#define ll long long
using namespace std;
const int M=2e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} inline void reads(string& s){ char c=getchar();
	for(;!isalpha(c);c=getchar()); s=" ";
	for(;isalpha(c);c=getchar()) s+=c;
} char sr[1<<21],z[20];int CCF=-1,Z;
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(ll x,char chr='\n'){
    if(CCF>1<<20)Ot();if(x<0)sr[++CCF]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} int n; string s[M];
struct SAM{ int las,cnt; SAM(){las=cnt=1;}
	arr fa,len,c,sa,num,vis; int to[M][26];
	inline void insert(int c,int now){
		int p=las,np=las=++cnt;
		len[np]=len[p]+1; F.add(now,np);
		for(;p&&!to[p][c];p=fa[p]) to[p][c]=np;
		if(!p) return fa[np]=1,void(); int q=to[p][c];
		if(len[q]==len[p]+1) return fa[np]=q,void();
		int nq=++cnt; len[nq]=len[p]+1,fa[nq]=fa[q];
		fa[q]=fa[np]=nq,memcpy(to[nq],to[q],sizeof to[q]);
		for(;p&&to[p][c]==q;p=fa[p]) to[p][c]=nq;
	}
	struct Gr{ int pat,head[M]; struct Edge{int to,nxt;}e[M];
		inline void add(int u,int v){e[++pat]={v,head[u]},head[u]=pat;}
	}G,F;
	void dfs(int u){ num[u]+=num[fa[u]]; go(G,u) dfs(v); }
	inline void calc(){
		fp(i,1,n){ int now=1;
			fp(j,1,s[i].length()-1){
				int p=now=to[now][s[i][j]-'a'];
				for(;p&&vis[p]^i;p=fa[p]) vis[p]=i,++num[p];
			}
		} memset(vis,0,(cnt+2)<<2);
		fp(i,1,cnt) G.add(fa[i],i); num[0]=num[1]=0;
		fp(i,1,cnt) num[i]=(num[i]==1)?len[i]-len[fa[i]]:0;
	}
	inline void solv(int u){ ll ans=0;
		go(F,u){ int p=v;
			for(;p&&vis[p]^u;p=fa[p])
				vis[p]=u,ans+=num[p];
		} print(ans);
	}
}p;
int main(){ n=read();
	fp(i,1,n) reads(s[i]);
	fp(i,1,n){ p.las=1;
		fp(j,1,s[i].length()-1)
			p.insert(s[i][j]-'a',i);
	} p.calc();
	fp(i,1,n) p.solv(i);
	return Ot(),0;
}
```



---

## 作者：温词 (赞：0)

## BZOJ5137&&lg4081(广义后缀自动机，set启发式合并) ##
### 题面
自己找去
### HINT
给定多个文本串，让你查询每个文本串中有多少个本质不同的子串且这个子串只出现在当前这个文本串中。
把题目拆成两个部分，你要先确定这个子串出现在多少个文本串中，这个可以用set启发式合并查询出来，求本质不同的子串的数目也就是$\sum_{u=1}^{tot}{node[u].len-node[fa].len}$那么我们也就只要筛选出哪些节点满足条件然后求个和就好了
#### tips
我自己写了个奇怪做法，就是在启发式合并的时候，如果这个点的$size()==1$我们也就记录一下这一个是什么，因为，在启发式合并的时候，**set[v]会被修改**
```cpp
#include<bits/stdc++.h>
#include<set>
using namespace std;
const int maxn=200010;
inline int read(){
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        w=(w<<3)+(w<<1)+ch-48;
        ch=getchar();
    }
    return w*f;
}
int n,m;
bool debug;
set<int> s[maxn];
set<int>::iterator it;
struct SUFFIXAUTOMATON{
	struct Node{
		int len,fa;
		map<int,int> ch;
	}node[200010];
	int lst,tot,root;
	inline void init(){
		lst=tot=root=1;return;
	}
	inline void extend(int now,int id){
        int p=lst;tot++;lst=tot;int np=tot;
        node[np].len=node[p].len+1;s[np].insert(id);
        while(p&&!node[p].ch[now]){
            node[p].ch[now]=np;
            p=node[p].fa;
        }
        if(!p) node[np].fa=1;
        else{
            int q=node[p].ch[now];
            if(node[q].len==node[p].len+1){
                node[np].fa=q;
            }
            else{
                int nq=++tot;node[nq]=node[q];
                node[nq].len=node[p].len+1;
                node[q].fa=nq;node[np].fa=nq;
                while(p&&node[p].ch[now]==q){
                    node[p].ch[now]=nq;
                    p=node[p].fa;
                }
            }
        }
    }
}SAM;
string ch[200010];
int cnt,head[200010],sum[200010];
int id[200010];
struct Edge{
	int from,to,next;
}edge[1200010];
inline void addedge(int u,int v){
	cnt++;
	edge[cnt].from=u;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
inline void dfs(int u){
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;dfs(v);
		if(s[u].size()<s[v].size()) swap(s[u],s[v]);
		for(it=s[v].begin();it!=s[v].end();it++){
			s[u].insert(*it);
		}
	}
	sum[u]=s[u].size();
	if(sum[u]==1){
		it=s[u].begin();id[u]=*it;
	}
}
int ans[200010];
int main(){
	n=read();SAM.init();
	for(int i=1;i<=n;i++){
		cin>>ch[i];int len=ch[i].length();
		for(int j=0;j<len;j++){
			SAM.extend(ch[i][j]-'a'+1,i);
		}
		SAM.lst=1;
	}
	for(int i=2;i<=SAM.tot;i++){
		addedge(SAM.node[i].fa,i);
	}
	dfs(1);
	//debug=true;
	if(debug){
		for(int i=1;i<=SAM.tot;i++){
			for(int j=1;j<=26;j++){
				if(SAM.node[i].ch[j]){
					cout<<i<<" "<<SAM.node[i].ch[j]<<" "<<(char)('a'+j-1)<<endl;
				}
			}
		}
	}
	if(debug){
		for(int i=1;i<=SAM.tot;i++){
			cout<<i<<" "<<id[i]<<endl;
		}
	}
	for(int u=1;u<=SAM.tot;u++){
		if(sum[u]!=1) continue;
		int f=SAM.node[u].fa;
		ans[id[u]]+=SAM.node[u].len-SAM.node[f].len;
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	if(debug){
		int cur=0;
		for(int i=1;i<=SAM.tot;i++){
			int f=SAM.node[i].fa;
			cur+=SAM.node[i].len-SAM.node[f].len;
		}
		cout<<cur<<endl;
	}
	return 0;
}
```

---

## 作者：Hyscere (赞：0)

对这些串建立广义后缀自动机。

对于每个串在自动机上跑一下，然后把经过的点以及他们的$parent$树上的祖先全部标记上当前串的编号，如果一个点被标记了两次，那么这个点所代表的子串必然不是本质相同的，就不能算。

然后统计答案就直接枚举自动机上的每个点，如果这个点只被标记了一次就给答案统计上当前点代表的本质不同的子串个数，即$maxl[p]-maxl[par[p]]$。

时间复杂度$O(\sum len_i)$。

```c++
#include<bits/stdc++.h>
using namespace std;
 
void read(int &x) {
    x=0;int f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-f;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';x*=f;
}
 
void print(int x) {
    if(x<0) putchar('-'),x=-x;
    if(!x) return ;print(x/10),putchar(x%10+48);
}
void write(int x) {if(!x) putchar('0');else print(x);putchar('\n');}

const int maxn = 3e5+10;

char ss[maxn],s[maxn];
int n,qs=1,cnt=1,lstp=1,tot;
int tr[maxn][27],par[maxn],ml[maxn],vis[maxn],len[maxn],ans[maxn];

void append(int x) {
	int p=lstp,np=++cnt;lstp=np,ml[np]=ml[p]+1;
	for(;p&&tr[p][x]==0;p=par[p]) tr[p][x]=np;
	if(p==0) return par[np]=qs,void();
	int q=tr[p][x];
	if(ml[p]+1<ml[q]) {
		int nq=++cnt;ml[nq]=ml[p]+1;
		memcpy(tr[nq],tr[q],sizeof tr[nq]);
		par[nq]=par[q],par[q]=par[np]=nq;
		for(;p&&tr[p][x]==q;p=par[p]) tr[p][x]=nq;
	} else par[np]=q;
}

int main() {
	read(n);
	for(int i=1;i<=n;i++) {
		scanf("%s",ss+1);len[i]=strlen(ss+1);lstp=qs;
		for(int j=1;j<=len[i];j++) s[++tot]=ss[j],append(ss[j]-'a'+1);
	}
	tot=0;
	for(int p,i=1;i<=n;i++)
		for(int now=qs,j=1;j<=len[i];j++) {
			now=tr[now][s[++tot]-'a'+1];
			for(p=now;p&&vis[p]!=-1&&vis[p]!=i;p=par[p])
				if(vis[p]!=0) vis[p]=-1;else vis[p]=i;
		}
	for(int i=1;i<=cnt;i++) if(vis[i]!=-1) ans[vis[i]]+=ml[i]-ml[par[i]];
	for(int i=1;i<=n;i++) write(ans[i]);
	return 0;
}
```

---

