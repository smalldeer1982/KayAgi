# Kill Anton

## 题目描述

After rejecting $ 10^{100} $ data structure problems, Errorgorn is very angry at Anton and decided to kill him.

Anton's DNA can be represented as a string $ a $ which only contains the characters "ANTON" (there are only $ 4 $ distinct characters).

Errorgorn can change Anton's DNA into string $ b $ which must be a permutation of $ a $ . However, Anton's body can defend against this attack. In $ 1 $ second, his body can swap $ 2 $ adjacent characters of his DNA to transform it back to $ a $ . Anton's body is smart and will use the minimum number of moves.

To maximize the chance of Anton dying, Errorgorn wants to change Anton's DNA the string that maximizes the time for Anton's body to revert his DNA. But since Errorgorn is busy making more data structure problems, he needs your help to find the best string $ B $ . Can you help him?

## 说明/提示

For the first testcase, it takes $ 7 $ seconds for Anton's body to transform NNOTA to ANTON:

NNOTA $ \to $ NNOAT $ \to $ NNAOT $ \to $ NANOT $ \to $ NANTO $ \to $ ANNTO $ \to $ ANTNO $ \to $ ANTON.

Note that you cannot output strings such as AANTON, ANTONTRYGUB, AAAAA and anton as it is not a permutation of ANTON.

For the second testcase, it takes $ 2 $ seconds for Anton's body to transform AANN to NAAN. Note that other strings such as NNAA and ANNA will also be accepted.

## 样例 #1

### 输入

```
4
ANTON
NAAN
AAAAAA
OAANTTON```

### 输出

```
NNOTA
AANN
AAAAAA
TNNTAOOA```

# 题解

## 作者：FwbAway (赞：13)

想要交换次数最少，逆序对必须放好。

$P=[2,7,2,4,3]$ 的逆序对需要 $10$ 次比较。

这题要用字符串，$O(N log N)$ 复杂度来算算。

设立 $T_i$ 和 $T_j$，在中间加上个字符 $k$。

$M$ 顶一个常量，赋值 $10000$ 不能少。

判断到底换不换，最少要 $0$ 次交换。

原来值赋值给 $a$，后来值赋值给 $b$。

判断如果 $a$ 等于 $b$，那么输出 $sum$ 值。

否则 $sum$ 再加 $1$，记录新的字符串！

---

## 作者：Acc_Robin (赞：9)

之前的题解已经详细地介绍了核心思想，我就不再赘述了。本篇题解旨在提供一个 $O(n)$ 级别计算逆序对的算法。

上一篇题解中求逆序对数是使用的归并排序，复杂度为 $O(n\log n)$。但考虑到只有四种字母，我们可以借此为突破口。

设数组 $rp[i][j]$ 表示字母 $i$ 在字母 $j$ 之前出现的次数，那么易预处理之。

在统计逆序对时，只要统计字母 $i,j$ 使得 $i<j$ 但 $i$ 却在 $j$ 之后出现的次数和就是逆序对数。

如果表述不清，可以康康代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace HMJ8S{
	#define int long long
    const int N = 1e5+10;
    int rp[4][4],a[N],mx,n,cnt[4];
    char s[N],opt[5]="ANOT";
    map<char,int>mp={{'A',0},{'N',1},{'O',2},{'T',3}};
    void work(){
        cin>>s,n=strlen(s),mx=0,memset(rp,0,sizeof rp),memset(cnt,0,sizeof cnt);
        for(int i=0;i<n;i++)a[i]=mp[s[i]],cnt[a[i]]++;
        for(int c=0,res;res=0,c<4;c++)for(int i=0;i<n;i++)if(rp[c][a[i]]+=res,a[i]==c)res++;
        vector<int>v={0,1,2,3},ans=v;
        do{
            int res=0;
            for(int i=0;i<4;i++)for(int j=i+1;j<4;j++)res+=rp[v[j]][v[i]];
            if(mx<res)mx=res,ans=v;
        }while(next_permutation(v.begin(),v.end()));
        for(auto i:ans)while(cnt[i]--)cout<<opt[i];
    }
    #undef int
}
int main(){
	int T;
	for(cin>>T;T--;puts(""))HMJ8S::work();
	return 0;
}
```

其中
```cpp
for(int c=0,res;res=0,c<4;c++)
	for(int i=0;i<n;i++)
		if(rp[c][a[i]]+=res,a[i]==c)res++;
```

是在预处理 $rp$ 数组。

```cpp
for(int i=0;i<4;i++)
	for(int j=i+1;j<4;j++)
		res+=rp[v[j]][v[i]];
```
是在统计逆序对数。

---

## 作者：Cry_For_theMoon (赞：8)

[传送门](https://codeforces.com/problemset/problem/1526/D)

神仙 2D，构造 2200 恐怖如斯

题意：给定长度为 $n$ 的仅含 ```A,N,O,T``` 的字符串 $S$，重新排列 $S$ 得到一个 $T$，使得 $T$ 还原 $S$ 所需操作最少。一次操作指的是交换 $T$ 的两个**相邻**字符。

$n<=2\,\times 10^5$

虽然这题很神仙但是还是有切入点的。明显有两个方向：直接构造 $T$ / 研究一个串 $T$ 还原成 $S$ 的性质。

注意到每次只能交换相邻字符，容易让我们想到逆序对。所以考虑 $T$ 如何还原成 $S$. 如果我们给 $T$ 每个字符都指定一个确定的目标位置 $p_i$，那么 $p$ 的逆序对数目就是最少交换次数。

问题是，相同字符之间，我们怎么分配它们的目标。不难~~猜测~~得到：

引理1：若 $i<j$ 且 $T_i=T_j$，则 $p_i<p_j$. 即两个相同字符，左边那个字符的目标位置肯定在右边那个字符的目标位置的左边。

证明：如果我们交换 $p_i,p_j$ 则会多出至少一个逆序对，同时我们只需要研究交换后有关 $p_i,p_j$ 的逆序对数目变化。容易发现以前所有以 $p_j$ 结尾的逆序对由于 $p_i<p_j$ 的缘故依旧存在；以前所有以 $p_i$ 开头的逆序对由于 $p_j>p_i$ 的缘故依旧存在；而以 $p_j$ 开头，$p_i$ 结尾的逆序对同理可证依旧存在。所以交换后至少会多出 $1$ 步，不优，证毕。

所以从 ```Anton``` 的角度来看，不管 ```Errorgorn``` 给出了什么字符串，我们都可以 $O(n \log n)$ 的计算出最少步数。同时这个最少步数就是逆序对而不是什么乱七八糟的式子。二维偏序又给了我们点数据结构上的灵光（）。但是在构造 $T$ 最大化 $p$ 的逆序对方面我们却没有什么思路。

考虑继续研究相同字符 $T_i,T_j(i<j)$，不妨假设 $(i,j)$ 里不再有相同字符。同时考虑它们中间的一个字符 $k$，不难发现 $p$ 中 $<i,k>$ 和 $<k,j>$ 中的逆序对个数最多只有一个（因为引理 $1$，有 $p_i<p_j$） 。而 $i<k<j$ 的字符与 $i,j$ 的逆序对数量关系其实等价与我们把 $i$ 一路交换到 $j-1$ 或者把 $j$ 一路交换到 $i+1$ 的逆序对数量关系。两种方案与原方案的逆序对个数比较，体现在 $<i,k>$ 与 $<k,j>$ 上，最多只会损失 $0$ 个逆序对（这两个过程一个使 $<i,k>$ 的逆序对关系发生反转，一个使 $<k,j>$ 的逆序对关系发生反转）。具体说来，有了这条性质，把 $i$ 换到 $j-1$ 和把 $j$ 换到 $i+1$ 两种方法总有一条不会减少逆序对个数。也就是说我们可以在保证最优性的前提下把两个相同字符放在一起。由此得到：

引理2：**最优方案里相同字母放在一起**。

我们又发现一共只有 $4$ 种字母。枚举字母出现的顺序，对这 $24$ 个字符串求出 $p$ 后 $n \log n$ 树状数组后计算逆序对即可。

复杂度：$O(24 \sum n \log n)$

```c++
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
const int MAXN=1e5+10;
int T,n;
int sum[5],per[5],use[5];
ll ans;
char s[MAXN],t[MAXN],res[MAXN];
int bucket[26],nxt[MAXN],p[MAXN],start[26];
struct BIT{
	int n,tree[MAXN];
	void reset(int n){
		this->n=n;
		rep(i,1,n)tree[i]=0;	
	}
	void add(int k){
		for(int x=k;x<=n;x+=lowbit(x)){
			tree[x]++;
		}
	}
	int query(int k){
		int sum=0;
		for(int x=k;x;x-=lowbit(x)){
			sum+=tree[x];
		}
		return sum;
	}
}tree;
ll calc(){
	//计算t->s的答案
	memset(bucket,0,sizeof bucket);
	per(i,n,1){
		nxt[i]=bucket[s[i]-'A'];
		bucket[s[i]-'A']=i;
	}
	rep(i,0,25)start[i]=bucket[i];
	rep(i,1,n){
		p[i]=start[t[i]-'A'];
		start[t[i]-'A']=nxt[start[t[i]-'A']];
	}
	//计算p的逆序对数量
	tree.reset(n+10);
	ll sum=0;
	per(i,n,1){
		sum+=tree.query(p[i]);
		tree.add(p[i]);
	}
	return sum;
}
void dfs(int r){
	if(r==5){
		//计算当前排列 
		int cnt=1;
		rep(i,1,4){
			char ch;
			if(per[i]==1)ch='A';
			else if(per[i]==2)ch='N';
			else if(per[i]==3)ch='O';
			else ch='T';
			rep(j,1,sum[per[i]])t[cnt++]=ch;
		}
		ll ret=calc();
		if(ret>ans){
			ans=ret;
			rep(i,1,n)res[i]=t[i];
		}
		return;
	}
	rep(i,1,4){
		if(use[i])continue;
		per[r]=i;use[i]=1;
		dfs(r+1);
		use[i]=0;
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);n=strlen(s+1);
		rep(i,1,n+1)t[i]=0,res[i]=0;
		sum[1]=sum[2]=sum[3]=sum[4]=0;
		use[1]=use[2]=use[3]=use[4]=0;
		rep(i,1,n){
			if(s[i]=='A')sum[1]++;
			else if(s[i]=='N')sum[2]++;
			else if(s[i]=='O')sum[3]++;
			else sum[4]++;
		}
		ans=-1;
		dfs(1);
		printf("%s\n",res+1);
	}

	return 0;
}
```



---

## 作者：YCS_GG (赞：4)

### CF1526D Kill Anton

应该能发现交换次数是和逆序对有关的，具体来说是原串的字符在构造的串中下一次出现的位置的数组的逆序对

比如 $s=\mathrm{ANTON} \ t=\mathrm{NNOTA}$ 位置数组为 $P=[5,1,4,3,2]$ 逆序对数为 $7$ 需要交换七次

手玩或者口胡一下会发现如果相同的字符放在一起不会更劣

证明：

设我们现在找到的字符串长这样 $\mathrm{....AAA_x....A_yAA...}$ ($A_x,A_y$ 仅用于标记，这两个字符 $P$ 中分别位于 $i,j$)

考虑两种合并方式 $\mathrm{....AAA_xA_y...AA...}$ 和 $\mathrm{...AA...A_xA_yAA}$ 

考虑第一种产生/消除的逆序对数量和为 $D_1=\sum\limits_{k=i+1}^{j-1} \mathrm{sign}(P_k-P_i)$

其中 $\mathrm{sign}(x)=\dfrac{x}{|x|}$ 就是取符号

第二种为 $D_2=\sum\limits_{k=i+1}^{j-1}\mathrm{sign}(P_j-P_k)$

事实上不可能有 $D_1+D_2 < 0$

这样就意味着至少存在有某个 $k$ 使得 $\mathrm{sign}(P_k-P_i)+\mathrm{sign}(P_j-P_k) < 0$

即 $P_k < P_i $ 且 $P_k > P_j \Rightarrow P_j <P_i$ 矛盾

那么有 $D_1+D_2 \ge 0$ 意味着这两者中至少有一个大于等于 $0$ 

那么按同样的方法把所有的相同字符放在一起不会更劣

枚举放每种字符的顺序共 $4!$ 种，每种 $n\log n$ 求逆序对比较大小即可

复杂度 $O(n\log n)$

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int N = 100004;
string s;
int t;
int tmp[N];
long long qres;
int a[N];
void msort(int l, int r) {
    if (l >= r)
        return;
    int m = l + r >> 1;
    msort(l, m);
    msort(m + 1, r);
    int i = l, j = m + 1;
    int k = 0;
    while (i <= m && j <= r) {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            qres += 1ll * m - i + 1ll;
        }
    }
    while (i <= m)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = tmp[k];
}
int main() {
    cin >> t;
    auto turn = [&](char c) -> int {
        if (c == 'A') {
            return 1;
        }
        if (c == 'N') {
            return 2;
        }
        if (c == 'O') {
            return 3;
        }
        if (c == 'T') {
            return 4;
        }
    };
    while (t--) {
        cin >> s;
        vector<int> v[5];
        for (int i = 0; i < s.length(); i++) {
            v[turn(s[i])].push_back(i + 1);
        }
        char chr[]     = {'A', 'N', 'O', 'T'};
        string ans     = "";
        long long mmax = 0;
        do {
            qres       = 0;
            string res = "";
            int cnt    = 0;
            for (int i = 0; i < 4; i++) {
                for (auto p : v[turn(chr[i])]) {
                    res += chr[i];
                    a[++cnt] = p;
                }
            }
            msort(1, cnt);
            if (qres >= mmax) {
                mmax = qres;
                ans  = res;
            }
        } while (next_permutation(chr, chr + 4));
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours
```



---

## 作者：Exber (赞：3)

这种题都有两个方向：直接构造 $T$ 和研究 $T$ 还原到 $S$ 的性质。

发现直接构造不好做，那么考虑研究 $T$ 还原到 $S$ 的性质。

显然**若知道了 $p_i$ 表示 $T_i$ 最终要去的位置，那么把 $T$ 还原到 $S$ 所需的操作就是 $p$ 的逆序对个数**。

不难发现，对于两个满足 $x<y,T_x=T_y$ 的位置 $x,y$，$p_x<p_y$ 显然是最优的，因为 $p_x>p_y$ 会增加至少一对逆序对，并且由于一个更大的数被放到前面了，所以逆序对个数并不会减少。

继续研究两个满足 $x<y,T_x=T_y,T_{[x+1,y-1]}\not=T_x$ 的两个位置 $x,y$，考虑 $x<k<y$，令 $Sx=\{k|x<k<y,p_x>p_k\},Sy=\{k|x<k<y,p_y<p_k\}$，显然有 $Sx\cap Sy=\varnothing$，那么令 $Sz=\{k|x<k<y\}-Sx-Sy$。

显然所有 $k\in Sx$ 和 $k\in Sy$ 的 $k$ 对逆序对个数都有 $1$ 的贡献，所有 $k\in Sz$ 的 $k$ 对逆序对个数都没有贡献。那么考虑把 $T_x$ 换到 $T_{y-1}$ 和把 $T_{y}$ 换到 $T_{x+1}$ 这两种操作：

- 把 $T_x$ 换到 $T_{y-1}$，此时逆序对个数会减少 $|Sx|$，但是又会加上 $|Sy|$；
- 把 $T_y$ 换到 $T_{x+1}$，此时逆序对个数会减少 $|Sy|$，但是又会加上 $|Sx|$；

并且两种操作都会造成一些额外的非负的来自 $k\in Sz$ 的逆序对个数贡献，这两种操作中对逆序对贡献更多的操作的贡献肯定至少为 $0$，那么让 $T_x$ 和 $T_y$ 相邻显然更优。

所以**所有相同的字符相邻肯定是最优的**。

那么枚举所有 $4!=24$ 种字符串，$O(n\log n)$ 计算逆序对个数即可。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int S=200005;

int n;
char a[S];
vector<int> pos[4];
int b[S],c[S];
char res[S];

inline int id(char x)
{
	return x=='A'?0:(x=='N'?1:(x=='T'?2:3));
}

inline char di(int x)
{
	return x==0?'A':(x==1?'N':(x==2?'T':'O'));
}

inline void add(int pos,int val)
{
	for(int i=pos;i<=n;i+=i&-i) c[i]+=val;
}

inline int que(int pos)
{
	int res=0;
	for(int i=pos;i>=1;i-=i&-i) res+=c[i];
	return res;
}

inline void slove()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	for(int i=0;i<4;i++) pos[i].clear();
	for(int i=1;i<=n;i++) pos[id(a[i])].push_back(i);
	long long mx=-1;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(i==j) continue;
			for(int k=0;k<4;k++)
			{
				if(i==k||j==k) continue;
				for(int l=0;l<4;l++)
				{
					if(i==l||j==l||k==l) continue;
					int p=0;
					for(int &u:pos[i]) b[++p]=u;
					for(int &u:pos[j]) b[++p]=u;
					for(int &u:pos[k]) b[++p]=u;
					for(int &u:pos[l]) b[++p]=u;
					for(int o=1;o<=n;o++) c[o]=0;
					long long pre=0;
					for(int o=n;o>=1;o--)
					{
						pre+=que(b[o]-1);
						add(b[o],1);
					}
					if(pre>mx)
					{
						mx=pre;
						p=0;
						for(int &u:pos[i]) res[++p]=di(i);
						for(int &u:pos[j]) res[++p]=di(j);
						for(int &u:pos[k]) res[++p]=di(k);
						for(int &u:pos[l]) res[++p]=di(l);
					}
				}
			}
		}
	}
	res[n+1]=0;
	printf("%s\n",res+1);
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T-->0) slove();
	return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：1)

# CF1526D 题解



## 思路分析

记 $S-S_i$ 为 $S$ 中删除 $S_i$ 后得到的字符串，记 $|S|=n$。

首先考虑在给定了 $S$ 和 $T$ 的情况下如何计算 $T$ 到 $S$ 的距离，记为 $\operatorname{dist}(S,T)$，注意到如下的观察：

> 观察一：
>
> $\operatorname{dist}$ 满足对于任意字符串 $A,B,C$ 满足 $|A|=|B|=|C|$ 均有 $\operatorname{dist}(A,C)\le\operatorname{dist}(A,B)+\operatorname{dist}(B,C)$。
>

注意到如下的观察：

> 观察二：
>
> 对于 $S$ 的最后一个字符 $c$，设 $c$ 在 $T$ 中最后一次出现是在位置 $x$ 上，那么 $\operatorname{dist}(S,T)=(n-x)+\operatorname{dist}(S-S_n,T-T_x)$。
>

为了维护 $\operatorname{dist}(S,T)$，我们对每个位置 $i$ 维护 $T_i$ 是否已经匹配，然后倒序考虑每个 $x$，$x$ 移动到匹配位置的代价事实上就等于 $(x,n]$ 中未匹配的位置数量，显然这个用一棵树状数组可以在 $\Theta(n\log n)$ 的时间内解决。

事实上，考察上面计算 $\operatorname{dist}(S,T)$ 的过程，假如我们记录下每个 $x$ 何时候被匹配，记为 $c_i$，事实上 $\operatorname{dist}(S,T)$ 与序列 $\{c_i\}$ 的逆序对数是相等的。

不过在这题中，$T$ 的可能性太多了，逐一验证的复杂度显然会超时，考虑剪枝。

而我们注意到如下的观察：

> 观察三：
>
> 最大化 $\operatorname{dist}(S,T)$ 的 $T$ 中相同的字符一定连续。
>

根据上面的观察，我们只需要枚举 $\texttt{a},\texttt{t},\texttt{o},\texttt{n}$ 的先后顺序即可。

时间复杂度 $\Theta(\alpha(S)!\times n\log n)$，其中 $\alpha(S)$ 表示 $S$ 的字符集大小（$\alpha(S)\le 4$）。

对于上面的三个观察的严格证明，由于博客长度限制，请点击[此处](https://www.luogu.com.cn/paste/rwz1c768)阅读

## 代码呈现

```cpp
#include<bits/stdc++.h> 
#define int long long
#define pci pair<char,int>
using namespace std;
const int MAXN=1e5+1;
struct BitTree {
	int len,tree[MAXN];
	inline int lowbit(int x) { return x&-x; }
	inline void Modify(int x,int v) {
		for(;x<=len;x+=lowbit(x)) tree[x]+=v;
	}
	inline int Query(int x) {
		int ret=0;
		for(;x;x-=lowbit(x)) ret+=tree[x];
		return ret;
	}
}	B;
inline int dist(string ori,string tar) {
	int n=tar.size(),ans=0;
	B.len=n;
	ori="#"+ori,tar="#"+tar;
	map <char,vector <int> > lst;
	for(int i=1;i<=n;++i) lst[ori[i]].push_back(i);
	for(int i=1;i<=n;++i) B.Modify(i,1);
	for(int i=n;i>=1;--i) {
		int x=lst[tar[i]].back();
		ans+=B.Query(n)-B.Query(x);
		B.Modify(x,-1),lst[tar[i]].pop_back();
	}
	return ans;
}
inline void solve() {
	string str,res;
	int ans=0;
	cin>>str;
	map <char,int> cnt;
	int n=str.length();
	for(int i=0;i<n;++i) ++cnt[str[i]];
	vector <int> p; vector <pci> sec;
	for(int i=0;i<(int)cnt.size();++i) p.push_back(i);
	for(auto x:cnt) sec.push_back(x);
	do {
		string tmp;
		for(int i:p) {
			for(int j=1;j<=sec[i].second;++j) {
				tmp.push_back(sec[i].first);
			}
		}
		int val=dist(tmp,str);
		if(val>=ans) ans=val,res=tmp;
		
	} while(next_permutation(p.begin(),p.end()));
	cout<<res<<endl;
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：鱼跃于渊 (赞：0)

一道很不错的构造题。  

## 解法

首先我们先不管求最大值这个问题，先考虑如何从一个 $t$ 还原成给定的 $s$。  
设 $p_i$ 表示位置 $i$ 上的字符最终要移到哪里，显然一次操作最多可以减少一个 $p$ 序列的逆序对。  
并且除非 $\forall i\in[1,n],p_i=i$，一定存在一个操作可以减少逆序对数。  
所以最小的交换次数等于 $p$ 序列的逆序对数。  

那么如何构造 $p_i$ 呢？容易发现若 $i,j(i<j)$ 上的字符相同，令 $p_i<p_j$ 一定最优。  
因为此时若交换 $p_i,p_j$，序列中的逆序对数显然不会减少，也就是说一定不会更优。  

接着考虑 $[i,j]$ 内的一些性质，方便起见设区间 $(i,j)$ 内没有位置使得上面的字符与 $i,j$ 上的字符相同。  
考虑 $\forall k \in (i,j),p_k$ 的贡献：  

1. 若 $p_k>p_j$，则贡献了 $1$ 对逆序对。  
2. 若 $p_k<p_i$，也贡献了 $1$ 对逆序对。  
3. 其他时候不产生贡献。  

观察上述性质，我们可以发现：  

+ 当 $p_k>p_j$ 时，如果交换 $p_i,p_k$，就会贡献 $2$ 对逆序对。  
+ 当 $p_k<p_i$ 时，如果交换 $p_k,p_j$，就会贡献 $2$ 对逆序对。  

我们不难想到一个结论：存在一个 $t$ 满足其最小交换次数最大，并且所有相同的字母都挨在一起。  
那么我们直接枚举字母的排列，然后使用树状数组计算逆序对即可。  
时间复杂度 $O(\lvert\Sigma\rvert!n\log \Sigma)$。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define epb emplace_back
#define lowbit(x) ((x)&(-(x)))
const int N=1e5+5,S=6;
char s[N];
int T,n,t[S];
int vis[S],chos[S];
int num,ans[S];
vector <int> p;
int get(char x){
	switch(x){
		case 'A':return 1;
		case 'T':return 2;
		case 'O':return 3;
		case 'N':return 4;
		default :return 5;
	}
}
char get(int x){
	switch(x){
		case 1:return 'A';
		case 2:return 'T';
		case 3:return 'O';
		case 4:return 'N';
		default:return ' ';
	}
}
void add(int i,int k){
	for(;i<=4;i+=lowbit(i)) t[i]+=k;
}
int query(int i){
	int res=0;
	for(;i;i-=lowbit(i)) res+=t[i];
	return res;
}
void solve(){
    fill(&t[1],&t[4]+1,0);
    int res=0;
    for(auto x:p){
        res+=query(chos[x]-1);
        add(chos[x],1);
    }
    if(res>num){
        num=res;
        per(i,1,4) ans[i]=chos[i];
    }
}
void dfs(int w){
	if(w==5) return solve();
	per(i,1,4) if(!vis[i]){
		chos[w]=i;vis[i]=1;
		dfs(w+1);
		vis[i]=0;
	}
}
void main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		cin>>(s+1);n=strlen(s+1);
        p.clear();num=-1;
        rep(i,n,1) p.epb(get(s[i]));
		dfs(1);
        sort(p.begin(),p.end(),[](const int &x,const int &y){
            return ans[x]<ans[y];
        });
        for(auto x:p) cout<<get(x);
        cout<<'\n';
	}
}}
signed main(){
	fisher::main();
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

[CF1526D Kill Anton](https://www.luogu.com.cn/problem/CF1526D)\
感觉是比较神的构造，直接构造答案，比较困难，思考 $b$ 串到 $a$ 的最大代价，因为交换相邻的元素，可以想到逆序对，给序列 $a$ 依次标号，这样由 $b$ 到 $a$ 的交换次数就是 $b$ 的逆序对数量。题目就转化为了求逆序对数量最多的 $b$ 串，但是同种字母之间是没有区别的，所以在最优策略下，同种字母直接是不会进行交换的，不属于逆序对，所以不能简单的将 $a$ 串翻转。\
有引理：**一定存在所有同类字母相邻的最优答案。**\
感性理解：因为字母之间只会不同类交换，所以考虑把不同类的字母尽量放前面，同类在一起。\
证明：
- 在最优策略下，同类字母不会发生交换，所以对于任意排列，同类字母之间的标号都是递增的。
- 对于同类字母 $a_i$ 与 $a_j$ 之间的所有相邻异类字母 $a_k$ 到 $a_q$ 来说，如果 $a_k$ 这种字母中 $w$ 个字母与前面的 $a_i$ 这种字母共构成了 $v_1$ 个逆序对，$s$ 个与后面的 $a_i$ 这种字母共构成了 $v_2$ 个逆序对，有 $v_1\le (k-i)\times w,v_2\le (j-q)\times s$。如果将所有的 $a_k$ 交换到前面，此时新增了 $[(k-i)\times s-v_1]$ 个逆序对，如果将他们交换到后面，此时新增了 $[(j-q)\times w-v_2]$ 个逆序对。
- 当 $(k-i)\times s-v_1\le 0$，即 $(k-i)\times s\le (k-i)\times w$ 时，有 $s\le w$，则 $v_2\le(j-q)\times s\le(j-q)\times w$，即 $(j-q)\times w-v_2\ge 0$。同理，如果 $(j-q)\times w-v_2\le 0$，则 $(k-i)\times s-v_1\ge 0$。
- 所以对于任何一种情况，我们总能使得同类字母相邻且逆序对数量单调不减，即**一定存在所有同类字母相邻的最优答案。**

由于不确定字母之间的顺序，我们可以直接枚举排列，然后每次用树状数组查询逆序对数量（当然也可以 $\mathcal{O}(n)$ 直接计算交换次数），取最大即可，时间复杂度 $\mathcal{O}(24n\log n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=1e5+10;
int n,a[N],ans[N],_ans,t[N];
char s[N];
bool vis[N];
std::vector<int> v[5];
inline void add(int x){
	for(;x<=n;x+=x&-x)t[x]+=1;
}
inline int query(int x){
	int res=0;
	for(int i=n;i;i-=i&-i)res+=t[i];
	for(int i=x;i;i-=i&-i)res-=t[i];
	return res;
}
inline void solve(){
	for(int i=1;i<=n;++i)t[i]=0;
	int res=0;
	for(int i=1;i<=4;++i){
		for(int x:v[a[i]]){
			res+=query(x);
			add(x);
		}
	}
	if(_ans<=res){
		for(int i=1;i<=4;++i)ans[i]=a[i];
		_ans=res;
	}
}
inline void dfs(int len,int x){
	if(len)a[len]=x;
	if(len==4){
		solve();
		return;
	}
	for(int i=1;i<=4;++i){
		if(!vis[i]){
			vis[i]=1;
			dfs(len+1,i);
			vis[i]=0;
		}
	}
}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	int t;std::cin>>t;
	while(t--){
		_ans=0;
		for(int i=1;i<=4;++i)v[i].clear();
		std::cin>>s+1;
		n=strlen(s+1);
		for(int i=1;i<=n;++i){
			if(s[i]=='A')v[1].push_back(i);
			if(s[i]=='N')v[2].push_back(i);
			if(s[i]=='T')v[3].push_back(i);
			if(s[i]=='O')v[4].push_back(i);
		}
		dfs(0,0);
		for(int i=1;i<=4;++i){
			for(int j=1;j<=v[ans[i]].size();++j){
				if(ans[i]==1)std::cout<<'A';
				if(ans[i]==2)std::cout<<'N';
				if(ans[i]==3)std::cout<<'T';
				if(ans[i]==4)std::cout<<'O';
			}
		}
		std::cout<<'\n';
	}
}
```

---

