# New Language

## 题目描述

Living in Byteland was good enough to begin with, but the good king decided to please his subjects and to introduce a national language. He gathered the best of wise men, and sent an expedition to faraway countries, so that they would find out all about how a language should be designed.

After some time, the wise men returned from the trip even wiser. They locked up for six months in the dining room, after which they said to the king: "there are a lot of different languages, but almost all of them have letters that are divided into vowels and consonants; in a word, vowels and consonants must be combined correctly."

There are very many rules, all of them have exceptions, but our language will be deprived of such defects! We propose to introduce a set of formal rules of combining vowels and consonants, and include in the language all the words that satisfy them.

The rules of composing words are:

- The letters are divided into vowels and consonants in some certain way;
- All words have a length of exactly $ n $ ;
- There are $ m $ rules of the form ( $ pos_{1},t_{1},pos_{2},t_{2} $ ). Each rule is: if the position $ pos_{1} $ has a letter of type $ t_{1} $ , then the position $ pos_{2} $ has a letter of type $ t_{2} $ .

You are given some string $ s $ of length $ n $ , it is not necessarily a correct word of the new language. Among all the words of the language that lexicographically not smaller than the string $ s $ , find the minimal one in lexicographic order.

## 说明/提示

In the first test word "aa" is not a word of the language, but word "ab" is.

In the second test out of all four possibilities only word "bb" is not a word of a language, but all other words are lexicographically less, so there is no answer.

In the third test, due to the last rule, "abac" doesn't belong to the language ("a" is a vowel, "c" is a consonant). The only word with prefix "ab" that meets the given rules is "abaa". But it is less than "abac", so the answer will be "acaa"

## 样例 #1

### 输入

```
VC
2 1
1 V 2 C
aa
```

### 输出

```
ab
```

## 样例 #2

### 输入

```
VC
2 1
1 C 2 V
bb
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
VCC
4 3
1 C 2 V
2 C 3 V
3 V 4 V
abac
```

### 输出

```
acaa
```

# 题解

## 作者：TTpandaS (赞：13)

枚举强制前 $i$ 位与 $s$ 相同，第 $i+1$ 位严格大于 $s$，后面随便填。

每个位置只有元音和辅音两种，所以可以 2-SAT 解决。

时间复杂度最坏 $O(n^2m)$，但实际上是 $O(\text{稳过})$。

---

## 作者：installb (赞：7)

## CF568C
[题](https://codeforces.com/problemset/problem/568/C)  
一眼 2-SAT，字典序最小就贪心，然后全是细节。  

根据贪心从左到右逐位考虑，虽然看起来后面对前面会有限制，但是通过 2-SAT 转成前面对后面的限制了。如果前面每一位都是顶上界的（和给定字符串相等）首选就是对应字符串的那一位，否则就是 `a`。  

但这样很可能是不合法的，也就是说后面不管怎么填也没法合法，不过这个并不难判断，有以下两种情况，假设目前判断第 $i$ 位能不能填给定字符。  
- 无法满足有解：前 $i$ 位决定后，后面出现既必须为 `V` 又必须为 `C` 的位  
- 无法满足字典序大于等于：前 $i$ 位决定后，前面仍然顶上界，假设第 $i+1$ 到 $i+k$ 位选 `C` 还是选 `V` 已经确定，而 $i+k+1$ 位没确定或者这位已经是字符串以外的位置，并且这一段无论怎么选也选不出字典序比给定字符串那段大的字符串（比如 `V` 最大选 `b`，$i+1$ 位只能选 `V`，而给定字符串要求 `c`）

第二种有点复杂  

然后看最优情况下不行的话，还有什么选项可以填，会决定一个位置对后面是否有解的影响的，无非就两个。  
- 前 $i$ 位是否顶上界
- 第 $i$ 位是 `C` 还是 `V`  

四种情况枚举一下，即可，如果前面不顶上界了后面就不可能再顶了，注意字典序从小到大，我这里实现的比较复杂。

```cpp
using namespace std;
typedef long long LL;

LL n,e[405][405];
void floyd(){
	for(LL k = 1;k <= n + n;k ++){
		for(LL i = 1;i <= n + n;i ++){
			for(LL j = 1;j <= n + n;j ++){
				e[i][j] |= (e[i][k] && e[k][j]);
			}
		}
	}
}

LL acv[405],tcv[405];
LL mxp[2],vc[35],nxt[35],nxu[35];
string s;
LL chk(LL pos,LL now,LL x,LL id){
	LL tmp;
	if(acv[pos] != -1 && acv[pos] != vc[now]) return 0;
	for(LL i = 1;i <= n;i ++) if(e[x][i] && e[x][i + n]) return 0;
    // 无解 1
	for(LL i = 1;i <= n;i ++){
		tcv[i] = -1;
		if(e[x][i]) tcv[i] = 0;
		if(e[x][i + n]) tcv[i] = 1;
	}
	if(!id){
		for(LL i = 1;i <= n;i ++){
			if(pos + i > n) break;
			tmp = max(tcv[pos + i],acv[pos + i]);
			if(tmp == -1) break;
			if(mxp[tmp] < s[pos + i] - 'a' + 1) return 0;
			if(mxp[tmp] > s[pos + i] - 'a' + 1) break;
		}
	} // 无解 2
	for(LL i = 1;i <= n;i ++) acv[i] = max(acv[i],tcv[i]);
    // 把限制加进总限制
	return 1;
}

LL ans[405];
int main(){
	LL len,m,l1,l2,c1,c2,fla;
	char ch1,ch2;
	cin >> s; len = s.length(); s = ' ' + s;
	for(LL i = 1;i <= len;i ++) vc[i] = (s[i] == 'C' ? 0 : 1);
	vc[len + 1] = -1;// 防止后面 mi + 1 爆字符集上限
	mxp[0] = mxp[1] = -1; for(LL i = 1;i <= len;i ++) mxp[vc[i]] = i;
	for(LL i = 1;i <= len;i ++){
		nxt[i] = 0;
		for(LL j = i + 1;j <= len;j ++){
			if(vc[i] != vc[j]){ nxt[i] = j; break; }
		}
	} // 下一个不同 C/V
	for(LL i = 1;i <= len;i ++){
		nxu[i] = 0;
		for(LL j = i + 1;j <= len;j ++){
			if(vc[i] == vc[j]){ nxu[i] = j; break; }
		}
	} // 下一个同 C/V
	
	memset(acv,-1,sizeof(acv));
	memset(tcv,-1,sizeof(tcv));
	cin >> n >> m;
	while(m --){
		cin >> l1 >> ch1 >> l2 >> ch2;
		c1 = (ch1 == 'C') ? 0 : 1;
		c2 = (ch2 == 'C') ? 0 : 1;
		e[l1 + c1 * n][l2 + c2 * n] = 1;
		e[l2 + (!c2) * n][l1 + (!c1) * n] = 1;
        // 2-SAT
	} floyd();
	
	cin >> s; s = ' ' + s;
	fla = 0;
	for(LL i = 1;i <= n;i ++){
		LL mi = fla ? 1 : s[i] - 'a' + 1;
        // 顶上界优先走，此是这位的 C/V 已经确定记为 mi
        // 这里先看 mi+1 和 mi 是同 C/V 还是不同的
        // 相同就先走同 C/V 不顶上界
        // 不同就先走不同 C/V 而且这种情况无论如何都不顶上界
		if(chk(i,mi,i + vc[mi] * n,fla)) ans[i] = mi;
		else if(vc[mi] == vc[mi + 1] && chk(i,mi + 1,i + vc[mi + 1] * n,1)) ans[i] = mi + 1,fla = 1;
		else if(nxt[mi] && chk(i,nxt[mi],i + vc[nxt[mi]] * n,1)) ans[i] = nxt[mi],fla = 1;
		else if(nxu[mi] > nxt[mi] && nxu[mi] && chk(i,nxu[mi],i + vc[nxu[mi]] * n,1)) ans[i] = nxu[mi],fla = 1;
		else{ cout << -1 << '\n'; return 0; }
	}
	for(LL i = 1;i <= n;i ++) cout << (char)(ans[i] + 'a' - 1); cout << '\n';
	return 0;
}
```

这题居然写了一个多小时，废了废了。

---

## 作者：xht (赞：6)

> [CF568C New Language](https://codeforc.es/contest/568/problem/C)

## 题意

- 将 $\texttt{a} \sim \texttt{a} + l - 1$ 这 $l$ 个字符分成 $\texttt{V,C}$ 两个集合。
- 你需要构造一个**长度为 $n$** 且**满足 $m$ 个限制**且**不小于另一个长度为 $n$ 的字符串 $s$** 的**最小**字符串。
- 每一个限制为**若字符串的第 $p_1$ 个位置上的字符 $\in t_1$，则第 $p_2$ 个位置上的字符 $\in t_2$**。
- $l \le 26$，$n \le 200$，$m \le 4n(n-1)$。

## 题解

限制的形式提示了显然要 2-SAT，建图之后贪心的选择能选的即可，时间复杂度 $\mathcal O(nm)$。

## 代码

```cpp
const int N = 207, L = 33;
int n, m, k, a[L], b[L][2], v[N<<1];
char s[N];
vi e[N<<1];

bool dfs(int x) {
	if (v[x>n?x-n:x+n]) return 0;
	v[x] = 1;
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (!v[y] && !dfs(y)) return 0;
	}
	return 1;
}

inline bool pd(int o) {
	for (int i = 1; i <= n << 1; i++) v[i] = 0;
	for (int i = 1; i <= o; i++)
		if (!dfs(i + a[s[i]-'a'+1] * n)) return 0;
	for (int i = o + 1; i <= n; i++) {
		if (v[i]) s[i] = b[1][0] + 'a' - 1;
		else if (v[i+n]) s[i] = b[1][1] + 'a' - 1;
		else {
			int x = min(b[1][0], b[1][1]), y = max(b[1][0], b[1][1]);
			if (dfs(i + a[x] * n)) s[i] = x + 'a' - 1;
			else if (dfs(i + a[y] * n)) s[i] = y + 'a' - 1;
			else return 0;
		}
	} 
	return 1;
}

int main() {
	rds(s, k);
	map< char, int > p;
	p['V'] = 0, p['C'] = 1;
	b[k+1][0] = b[k+1][1] = k + 1;
	for (int i = k, t[2] = {k + 1, k + 1}; i; i--)
		t[a[i]=p[s[i]]] = i, b[i][0] = t[0], b[i][1] = t[1];
	rd(n), rd(m);
	for (int i = 1, x, y, s1, t1, s2, t2; i <= m; i++) {
		rd(x), rds(s, y), s1 = x + p[s[y]] * n, s2 = s1 > n ? s1 - n : s1 + n;
		rd(x), rds(s, y), t1 = x + p[s[y]] * n, t2 = t1 > n ? t1 - n : t1 + n;
		e[s1].pb(t1), e[t2].pb(s2);
	}
	rds(s, n);
	if (pd(n)) return prints(s, n), 0;
	else if (b[1][0] == k + 1 || b[1][1] == k + 1) return print(-1), 0;
	for (int i = n; i; i--) {
		int c = s[i] - 'a' + 2, x = min(b[c][0], b[c][1]), y = max(b[c][0], b[c][1]);
		if (x != k + 1) {
			s[i] = x + 'a' - 1;
			if (pd(i)) return prints(s, n), 0;
		}
		if (y != k + 1) {
			s[i] = y + 'a' - 1;
			if (pd(i)) return prints(s, n), 0;
		}
	}
	print(-1);
	return 0;
}
```

---

## 作者：loveJY (赞：4)

## UPD on 2020/11/7

> 完善了部分叙述,通过了hack数据

首先要注意题面不能读错,我一开始看错了题就郁闷半天...

他是已经给出了每个字母的划分方案,我们只需要构造

其次我们看向题目中给出的限制条件,应该非常眼熟吧,就是2-SAT题里面给出的限制条件啊...所以这题和2-SAT一定有关系,具体地:

1. 我们每个位置要么属于V要么属于C,这个说明每个变量有2个取值

2. 我们每个限制只是关于两个变量

所以这个是2-SAT-2啦,也就是说,如果我们能建立一个图的话,就能够判断一个串是否满足题目限制

先考虑怎么建出图...如果有一个第i个选V第j个就选C我们就这样连边![](https://cdn.luogu.com.cn/upload/image_hosting/y3kdavlv.png)

然后我们显然对于一个固定串,他的集合都已经定好了,而2-SAT跑出来的合法性判定不合法的话,说明这个串不符合要求

在考虑构造...好像没啥很快的做法?看一眼数据范围n<=200,我们直接枚举哪一位比他大吧!

也就是说枚举哪一位刚好比s大,那之后的是任意位置,只要满足2-SAT的合法性判定每个位置放的尽可能小(不难发现就是每个集合的第一个字符qwq),那之前的和S相同即可

这样子我们好像就可以构建出一个串了?又因为我们从最后向前枚举哪一位比题目要求的大,所以构造出来的第一个串一定是最小的!

这个题也就做完了!复杂度..由于$m$是$n^2$级别,所以$O(n^3)$

最后要感谢xht37神仙提供灵感

code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;

const int MAXN = 207, L = 33, MAXM = 3e5;
int n, m, k, a[L], b[L][2], vis[MAXN << 1];
char s[MAXN];
int home[MAXM], nxt[MAXM], to[MAXM], ccnt;

inline void ct(int x, int y) {
	ccnt++;
	nxt[ccnt] = home[x];
	home[x] = ccnt;
	to[ccnt] = y;
}

int st[MAXM], tp;

bool dfs(int x) {
	if(vis[x > n ? x - n : x + n])return 0;
	//如果他已经有v了
	vis[x] = 1;
	st[++tp] = x;
	for(int i = home[x]; i; i = nxt[i]) {
		int v = to[i];
		if(!vis[v] && !dfs(v))return 0;
	}
	return 1;
}

inline bool pd(int C) {
	for(int i = 1; i <= n << 1; ++i)vis[i] = 0;
	for(int i = 1; i <= C; ++i) {
		if(!dfs(i + a[s[i] - 'a' + 1]*n))return 0;
		//之前已经填好的
	}
	for(int i = C + 1; i <= n; ++i) {
		if(vis[i])s[i] = b[1][0] + 'a' - 1;
		else if(vis[i + n])s[i] = b[1][1] + 'a' - 1;
		//这一部分是处理后面任意的填的部分
		else {
			int x = min(b[1][0], b[1][1]), y = max(b[1][0], b[1][1]);
			tp = 0;
			if(dfs(i + a[x]*n))s[i] = x + 'a' - 1;
			else {
				while(tp)vis[st[tp--]] = 0;//要清空....
				if(dfs(i + a[y]*n))s[i] = y + 'a' - 1;
				else return 0;
			}  //不行了,这个位置放啥都不行
		}
	}
	return 1;
}


map<char, int> p;
int main() {
	scanf("%s", s + 1);
	k = strlen(s + 1);
	p['V'] = 0, p['C'] = 1;//真,假
	b[k + 1][0] = b[k + 1][1] = k + 1;
	for(int i = k, t[2] = {k + 1, k + 1}; i; i--) {
		t[a[i] = p[s[i]]] = i;
		b[i][0] = t[0];
		b[i][1] = t[1];
	}//预处理每个位置靠后能放的第一个不同集合字符
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y, s1, t1, s2, t2; i <= m; ++i) {
		scanf("%d", &x);
		scanf("%s", s + 1);
		y = strlen(s + 1);
		s1 = x + p[s[y]] * n;
		s2 = s1 > n ? s1 - n : s1 + n;
		scanf("%d", &x);
		scanf("%s", s + 1);
		y = strlen(s + 1);
		t1 = x + p[s[y]] * n;
		t2 = t1 > n ? t1 - n : t1 + n;
		//这个是2-SAT建图,s2t2只是转化到另一个点
		ct(s1, t1);
		ct(t2, s2);

	}
	scanf("%s", s + 1);
	n = strlen(s + 1);
	if(pd(n))return printf("%s\n", s + 1), 0;
	else if(b[1][0] == k + 1 || b[1][1] == k + 1)return puts("-1"), 0;
	for(int i = n; i; --i) {
		int c = s[i] - 'a' + 2, x = min(b[c][0], b[c][1]), y = max(b[c][0], b[c][1]);
		//c刚好填比他大的
		if(x != k + 1) {
			s[i] = x + 'a' - 1;
			if(pd(i))return printf("%s\n", s + 1), 0;
		}
		if(y != k + 1) {
			s[i] = y + 'a' - 1;
			if(pd(i))return printf("%s\n", s + 1), 0;
		}
	}
	puts("-1");
	return 0;
}

```

像2-SAT这样的神仙算法就是支持边填边构造方案啊

EX : 被hack原因是我们在尝试去填每个集合的最小字符后,没有及时清空..

---

## 作者：panyf (赞：4)

upd:修改了两个地方，现在可以通过讨论区 hack 数据了。

[2-SAT 学习笔记](https://www.luogu.com.cn/blog/221955/post-2-sat)，建议先阅读其中“DFS 求解 2-SAT”以及“2-SAT 建图的对称性”的部分。

考虑一个弱化版问题：求字典序最小的解。

做法是从前到后贪心，每一位先搜字典序较小的，再搜字典序较大的，用上文提到的 dfs 做法，两次 dfs 都失败则直接判断无解，时间复杂度 $O(nm)$。

**正确性证明**：

当前考虑到第 $i$ 位，若 $b_i=b_{i+n}=0$（数组名和变量名在学习笔记中有解释），从 $i$ 和 $i+n$ 搜索均失败，则改变前 $i-1$ 位的取值也一定无解。

原因：若 $i$ 和 $i+n$ 在同一个强连通分量，显然一定无解。否则不妨设从 $i$ 开始 dfs 到点 $x$ 时 $b_{inv_x}=1$，因为 $i$ 到 $x$ 有路径相连，根据 2-SAT 的对称性，$inv_x$ 到 $i+n$ 也有路径相连，所以 $b_{i+n}=1$，与条件 $b_{i+n}=0$ 矛盾。

**本题做法**：

本题新增了不小于字符串 $s$ 的限制。依然从前到后贪心，但要像数位 dp 一样维护一个 bool 变量 $f$ 表示当前确定的部分是否为 $s$ 的前缀（$f=0$ 表示是前缀）。

若前 $i-1$ 位 $f=0$，则需要判断第 $i$ 位继续 $f=0$ 是否有解，若有解则优先 $f=0$。判断方法是从前到后考虑 $i+1$ 及之后的位 $j$，若 $j$ 可以取到大于 $s_j$ 的值，直接判断有解；若 $j$ 只能取到小于 $s_j$ 的值，直接判断无解；否则继续下一位。每次判断是 $O(n)$ 的，所以不影响总复杂度。

以上贪心过程之前需要先预处理出所有不能选元音或者不能选辅音的点。

时间复杂度是遍历图 $n$ 遍的复杂度，即 $O(nm)$。

实现时分类讨论较复杂，具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=409,M=4e5+3;
char s[N];
int a[N],n0[N],n1[N],he[N],to[M],ne[M],t,n,st[N*2],tp;
bool b[N],b2[N];
void add(int x,int y){ne[++t]=he[x],to[t]=y,he[x]=t;}
void ins(int x,int y){add(x,y),add(y>n?y-n:y+n,x>n?x-n:x+n);}
bool dfs(int x){
	if(b[x>n?x-n:x+n])return 0;
	if(b[x])return 1;
	b[x]=1,st[++tp]=x;
	for(int i=he[x];i;i=ne[i])if(!b[to[i]]&&!dfs(to[i]))return b[x]=0;
	return 1;
}
bool wk(int x){
	while(tp)b[st[tp--]]=0;
	return dfs(x);
}
int main(){
	int m,l,i,j=1e9,k=1e9;
	bool f=0;
	char c1,c2;
	scanf("%s",s+1),l=strlen(s+1),n0[l+1]=n1[l+1]=j;
	for(i=l;i;--i){
		if(s[i]=='V')j=i;else k=i;
		n0[i]=j,n1[i]=k;//不小于 i 的元音和辅音
	}
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d %c%d %c",&i,&c1,&j,&c2);
		ins(c1=='C'?i:i+n,c2=='C'?j:j+n);
	}
    for(i=1;i<=n;++i)if(!wk(i)){
		if(!wk(i+n))return puts("-1"),0;
		b2[i+n]=1;
	}else if(!wk(i+n))b2[i]=1;
	memcpy(b,b2,sizeof b);//预处理不能选元音或不能选辅音的点
	scanf("%s",s+1);
	for(i=1;i<=n;++i)a[i]=s[i]-96;
	for(i=1;i<=n;++i){
		tp=0;
		if(f)a[i]=1;
		gg:;
		if(n0[a[i]]>1e8){//不存在元音
			if(n1[a[i]]>1e8||b[i+n]||!dfs(i))return puts("-1"),0;
		}else if(n1[a[i]]>1e8){//不存在辅音
			if(b[i]||!dfs(i+n))return puts("-1"),0;
		}else if(!b[i]&&!b[i+n]){//当前位还没确定
			if(n0[a[i]]>n1[a[i]]){//先搜字典序小的
				if(!dfs(i))if(f=1,!dfs(i+n))return puts("-1"),0;
			}else{
				if(!dfs(i+n))if(f=1,!dfs(i))return puts("-1"),0;
			}
		}else if(b[i]?n1[a[i]]>a[i]:n0[a[i]]>a[i])f=1;//当前位已确定
		if(!f){//判断 f=0 是否有解
			for(j=i+1;j<=n;++j){
				if(b[j]){
					if(n1[a[j]]>1e8){
						f=1,++a[i];
						break;
					}
					if(n1[a[j]+1]<1e8)break;
				}else if(b[j+n]){
					if(n0[a[j]]>1e8){
						f=1,++a[i];
						break;
					}
					if(n0[a[j]+1]<1e8)break;
				}else if(n1[a[j]+1]<1e8||n0[a[j]+1]<1e8)break;
			}
			if(f){//若 f=0 无解则清空标记重新 dfs
				while(tp)b[st[tp--]]=0;
				goto gg;
			}
		}
	}
	for(i=1;i<=n;++i)putchar(96+(b[i]?n1[a[i]]:n0[a[i]]));
	return 0;
}
```

---

## 作者：Annihilation_y (赞：2)

## 题意
给你一个串，表示字母的元音辅音状态。

给你一个 $n$，$m$，让你构造一个长度为 $n$ 的字符串，满足这 $m$ 条限制。

再给你一个字符串 $s$，要求你构造的字符串必须大于等于该字符串。

## 思路
思路很冗余，并求 hack。

首先一眼 2-SAT。由于是枚举最小的，所以只能用 $O(nm)$ 的 2-SAT。

假设从第 $1$ 位到第 $u-1$ 位选的数就已经大于当前的字符串 $s$ 了，那么他就可以选任意的元音或者辅音，否则的话需要从 $s_{u}$ 开始选。我用 $lst$ 为 $0$ 表示可以随便选，为 $1$ 表示要有限制。

经过观察可以发现，对于都是元音或者都是辅音的字母，他们对后面的 $vis$ 数组的贡献是一样的，所以只需要选择最小的元音和辅音来讨论。

但是经过观察我们发现，如果当前 $lst$ 当 $s_{u}$ 与最小的元音相等，即向后传的 $lst$ 为 $1$，且没有解的时候，我们要考虑在次小元音和最小辅音中选择较小的那个，因为此时这两个向后传的 $lst$ 都为 $0$。当然最小的辅音同理。

算法的正确性已经没问题了，但是在无解且只有最后几步有限制的时候有限制的时候会退化成 $O(2^n)$。所以考虑玄学优化。

我们发现，如果一个点在 $m$ 个限制条件中都没有出现，那么这个点的贡献是可以忽略不计的。

然后判断一下，当这个点取元音和辅音的代价是一样的时候，且向后传递的 $lst$ 都是 $0$，那么我们可以只考虑较小的元音或者辅音，因为他们对后面的贡献是完全一样的。这样能保证不被数据点 hack。

## Code
~~~c++
#include <bits/stdc++.h>
using namespace std;
namespace yhy{
	const int MAXN=400+5;
	vector<int> G[MAXN];
	stack<int> st;
	int n,m;
	string s0;
	string s;
	int never[MAXN];
	int vis[MAXN];
	void Get_vis(int u) {
		if(!never[u]) return ;
		vis[u]=1;
		for(auto v:G[u]) {
			if(!vis[v]) {
				Get_vis(v);
			}
		}
	}
	bool check() {
		for(int i=1;i<=n;i++) {
			if(vis[i] && vis[i+n]) {
				return 0;
			}
		}
		return 1;
	}
	int ans[MAXN];
	int dfs(int u,int lst) {
		if(u==s.size()) return 1;
		int lst_vis[MAXN];
		int vis_1[MAXN],vis_2[MAXN];
		memcpy(lst_vis,vis,sizeof vis);
		Get_vis(u);
		memcpy(vis_1,vis,sizeof vis);
		memcpy(vis,lst_vis,sizeof lst_vis);
		Get_vis(u+n);
		memcpy(vis_2,vis,sizeof vis);
		int flag=1;
		memcpy(vis,lst_vis,sizeof lst_vis);
		for(int i=1;i<=2*n;i++) {
			if(vis_1[i]!=vis_2[i]) {
				flag=0;
				break;	
			}
		}
		int Minn_c=0,Minn_v=0,second_Minn_c=0,second_Minn_v=0;
		int st=(s[u]-'a'+1)*lst;
		for(int i=st;i<s0.size();i++) {
			if(s0[i]=='C') {
				if(!Minn_c) {
					Minn_c=i;	
				}
				else if(!second_Minn_c) {
					second_Minn_c=i;
				}
			}
			if(s0[i]=='V') {
				if(!Minn_v) {
					Minn_v=i;
				}
				else if(!second_Minn_v) {
					second_Minn_v=i;	
				}
			}
		}
		if(lst) {
			if(Minn_c==st) {
				Minn_c=second_Minn_c;
				if(vis[u+n]==1) goto Solve;
				Get_vis(u);
			}
			else {
				Minn_v=second_Minn_v;
				if(vis[u]==1) goto Solve; 
				Get_vis(u+n);
			}
			if(!check()) {
				memcpy(vis,lst_vis,sizeof lst_vis);
				goto Solve;	
			}
			else {
				if(!dfs(u+1,1)) {
					memcpy(vis,lst_vis,sizeof lst_vis);
					goto Solve;
				}
				else {
					ans[u]=st;
					return 1;	
				}
			}
		}
		else {
			Solve:
				if(vis[u]==1 || !Minn_v) {
					if(!Minn_c) {
						memcpy(vis,lst_vis,sizeof lst_vis);
						return 0;	
					}
					Get_vis(u);
					if(!check()) {
						memcpy(vis,lst_vis,sizeof lst_vis);
						return 0;	
					}
					else {
						if(!dfs(u+1,0)) {
							memcpy(vis,lst_vis,sizeof lst_vis);
							return 0;	
						}
						else {
							ans[u]=Minn_c;
							return 1;	
						}
					}
				}
				else if(vis[u+n]==1 || !Minn_c) {
					if(!Minn_v) {
						memcpy(vis,lst_vis,sizeof lst_vis);
						return 0;	
					}
					Get_vis(u+n);
					if(!check()) {
						memcpy(vis,lst_vis,sizeof lst_vis);
						return 0;	
					}
					else {
						if(!dfs(u+1,0)) {
							memcpy(vis,lst_vis,sizeof lst_vis);
							return 0;	
						}
						else {
							ans[u]=Minn_v;
							return 1;	
						}
					}
				}
				else if(Minn_c<Minn_v) {
					Get_vis(u);
					if(!check()) {
						memcpy(vis,lst_vis,sizeof lst_vis);
					}
					else {
						if(dfs(u+1,0)) {
							ans[u]=Minn_c;
							return 1;	
						}
						else {
							memcpy(vis,lst_vis,sizeof lst_vis);
						}
					}
					if(flag) return 0;
					Get_vis(u+n);
					if(!check()) {
						memcpy(vis,lst_vis,sizeof lst_vis);
						return 0;	
					}
					else {
						if(!dfs(u+1,0)) {
							memcpy(vis,lst_vis,sizeof lst_vis);
							return 0;
						}
						else {
							ans[u]=Minn_v;
							return 1;	
						}
					}
				}
				else {
					Get_vis(u+n);
					if(!check()) {
						memcpy(vis,lst_vis,sizeof lst_vis);
					}
					else {
						if(dfs(u+1,0)) {
							ans[u]=Minn_v;
							return 1;	
						}
						else {
							memcpy(vis,lst_vis,sizeof lst_vis);
						}
							
					}
					if(flag) return 0;
					Get_vis(u);
					if(!check()) {
						memcpy(vis,lst_vis,sizeof lst_vis);
						return 0;	
					}
					else {
						if(!dfs(u+1,0)) {
							memcpy(vis,lst_vis,sizeof lst_vis);
							return 0;
						}
						else {
							ans[u]=Minn_c;
							return 1;	
						}
					}
				}
		}
		return 0;
	}
	int main() {
		std::ios::sync_with_stdio(false);
		cin.tie(0);cout.tie(0);
		cin>>s0;
		cin>>n>>m;
		memset(ans,-1,sizeof ans);
		for(int i=1;i<=m;i++) {
			int x,y;
			char a,b;
			cin>>x>>a>>y>>b;
			never[x]=never[y]=never[x+n]=never[y+n]=1;
			if(a=='C' && b=='C') {
				G[x].push_back(y);
				G[y+n].push_back(x+n);
			}
			if(a=='C' && b=='V') {
				G[x].push_back(y+n);
				G[y].push_back(x+n);
			}
			if(a=='V' && b=='C') {
				G[x+n].push_back(y);
				G[y+n].push_back(x);
			}
			if(a=='V' && b=='V') {
				G[x+n].push_back(y+n);
				G[y].push_back(x);
			}
		}
		cin>>s;
		s0=" "+s0;
		s=" "+s;
		if(!dfs(1,1)) {
			cout<<"-1\n";
			return 0;	
		}
		else {
			for(int i=1;i<s.size();i++) {
				cout<<char(ans[i]-1+'a');	
			}
			cout<<'\n';
		}
		
		return 0;
	}
}
signed main() {
	yhy::main();
	return 0;
}
~~~

[AC](https://codeforces.com/contest/568/submission/309190827)

---

## 作者：木xx木大 (赞：2)

 [CF568C New Language](https://www.luogu.com.cn/problem/CF568C) 
 
 首先吐槽：题目的中文翻译真的看不懂啊。。。
 
 本篇题解的思路应该是和题解区的几篇题解基本相同的，但因为我花了很久才看懂那几篇题解，所以决定自己写一篇

* 显然是2-SAT问题。要注意一点：对于一条限制，要连两条边。例如`1 V 2 C` 这样一条限制，其实是`1 V`向`2 C`连一条边，同时`2 v`向`1 C`连一条边。因为如果2为`V`时1为`V`，就不符合上面的限制了，所以2为`v`时1只能为`c`。由于$n\le 200$ ，我们甚至不需要缩点，直接dfs即可。
* 建图后，贪心地选最优：首先判原串是否合法，如果合法直接输出；否则，只需要有一个位置上的字符比原串大，这个位置之前的按原串填，之后在满足 $m$ 个限制的条件下尽量选最小的即可。
* 具体实现见代码及注释，有点麻烦（毕竟是cf的题啊）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inl inline
using namespace std;
namespace FGF
{
	int n,m,L;
	const int N=405;
	char s[N],ans[N]; 
	int num,head[N],cnt,b[N][2],a[N];
	bool vis[N];
	struct edg{
		int to,nxt;
	}e[N*N*16];
	void add(int u,int v)
	{
		cnt++;
		e[cnt].to=v;
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
	bool dfs(int u)
	{
		if(vis[u>n? u-n:u+n])return 0;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
			if(!vis[e[i].to]&&!dfs(e[i].to))return 0;
		return 1;
	}
	bool check(int u)
	{
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=u;i++)//首先看前几位按原串填是否互相矛盾 
			if(!dfs(i+a[s[i]-'a'+1]*n))return 0;//顺便处理出前面按原串填时后面受到的限制 
		for(int i=u+1;i<=n;i++)
		{
			if(vis[i])s[i]=b[1][0]+'a'-1;//这一位只能填V中的 
			else if(vis[i+n])s[i]=b[1][1]+'a'-1;//这一位只能填C中的 
			else
			{//这一位可以填V或C中的，就填合法的尽量小的 
				int x=min(b[1][0],b[1][1]),y=max(b[1][0],b[1][1]);
				if(dfs(i+a[x]*n))s[i]=x+'a'-1;
				else if(dfs(i+a[y]*n))s[i]=y+'a'-1;
				else return 0;
			}
		}
		return 1;
	}
	void work()
	{
		scanf("%s",s+1);
		L=strlen(s+1);
		b[L+1][0]=b[L+1][1]=L+1;
		int t[2]={L+1,L+1};
		for(int i=L;i;i--)
		{//a： 每个字母属于哪个集合 
			if(s[i]=='V')a[i]=0,t[0]=i;
				else a[i]=1,t[1]=i;
			b[i][0]=t[0],b[i][1]=t[1]; 
		}//b:0/1分别表示在V/C两个集合中>=当前字母的最小字母 
		scanf("%d%d",&n,&m);
		char c[5],h[5];int x,y;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%s%d%s",&x,c,&y,h);
			if(c[0]=='V'&&h[0]=='C')add(x,y+n),add(y,x+n);
			if(c[0]=='V'&&h[0]=='V')add(x,y),add(y+n,x+n);
			if(c[0]=='C'&&h[0]=='V')add(x+n,y),add(y+n,x);
			if(c[0]=='C'&&h[0]=='C')add(x+n,y+n),add(y,x);
		}
		scanf("%s",s+1);
		if(check(n))//判断原串是否合法 
		{
			printf("%s",s+1);
			return;
		}
		if(b[1][0]==L+1||b[1][1]==L+1)
		{
			puts("-1");
			return;
		}
		for(int i=n;i;i--)
		{//从后向前枚举每一位，判断如果修改这一位为V/C集合中比原串大的最小的字母是否合法 
			int c=s[i]-'a'+2,x=min(b[c][0],b[c][1]),y=max(b[c][0],b[c][1]);
			if(x!=L+1)
			{
				s[i]=x+'a'-1;
				if(check(i))//如果合法直接输出 
				{
					printf("%s",s+1);
					return;
				}
			}
			if(y!=L+1)
			{
				s[i]=y+'a'-1;
				if(check(i))
				{
					printf("%s",s+1);
					return;
				}
			}
		}
		puts("-1");
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：1)

## 题意
把 $\texttt{a}\sim\texttt{a}+l-1$ 这些字符划分成  $\texttt{V},\texttt{C}$ 两个集合，给出 $m$ 条限制形如 $r_{p_1}\in t_1\to r_{p_2}\in t_2$，且 $r\ge s$，求字典序最小的 $r$。
## 题解
首先直接从前往后贪心，如果前面是紧贴下界的话，当前位置有三个可能：取下界，取第一个大于下界并且和下界在同一个集合的，取第一个大于下界并且和下界不在同一个集合的。如果之前已经超过下界了，那么现在要么选 $\texttt{a}$ 要么选第一个和 $\texttt{a}$ 不在同一个集合的。

然后我们现在只需要判断后面是否合法即可。首先这个很明显是一个 2-SAT 问题，那么我们可以先建出图，跑传递闭包得到推出关系。然后我们需要判断后面能否合法。如果已经推导出矛盾了后面显然不合法，否则就直接在后面贪心地选字典序最大的，如果这样的字典序能够比给出的串大或相等就是合法否则就是不合法。

直接写就好了没什么细节。

复杂度 $\mathcal O(n^3)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
#define pc putchar
#define chkmx(a,b) (a)=max((a),(b))
#define chkmn(a,b) (a)=min((a),(b))
#define fi first
#define se second
using namespace std;
template<class T>
void read(T&x){x=0;char c=getchar();bool f=0;for(;!isdigit(c);c=getchar())f^=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<class T,class ...ARK>void read(T&x,ARK&...ark){read(x);read(ark...);}
template<class T>void write(T x){if(x<0)pc('-'),x=-x;if(x>=10)write(x/10);pc(x%10+'0');}
template<class T,class ...ARK>void write(T x,ARK...ark){write(x);pc(' ');write(ark...);}
template<class ...ARK>void writeln(ARK...ark){write(ark...);pc('\n');}
void get(char&c){c=getchar();while(!isalpha(c))c=getchar();}
typedef long long ll;
const int mod=998244353;
struct mint{
	int x;mint(int o=0){x=o;}mint&operator+=(mint a){return(x+=a.x)%=mod,*this;}mint&operator-=(mint a){return(x+=mod-a.x)%=mod,*this;}
	mint&operator*=(mint a){return(x=1ll*x*a.x%mod),*this;}mint&operator^=( int b){mint a=*this;x=1;while(b)(b&1)&&(*this*=a,1),a*=a,b>>=1;return*this;}
	mint&operator/=(mint a){return*this*=(a^=mod-2);}friend mint operator+(mint a,mint b){return a+=b;}friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}friend mint operator/(mint a,mint b){return a/=b;}friend mint operator^(mint a, int b){return a^=b;}
};
#define lowbit(x) ((x)&-(x))
#define mid ((l+r)>>1)
#define lc (x<<1)
#define rc (x<<1|1)
#define orz write(-1),exit(0)
const int N=2e3+100;
int n,m,l;bool e[N][N];
//C = 0 V = 1
int bel[30],diff[30],same[30],lst[2];
char str[N];
int ans[N];
bool lim=1;//跟下界贴贴
int must[N];
bool chk(int pos,int now){
	ans[pos]=now;
	//在pos加了now
	//首先看看有没有矛盾
	if(e[pos+bel[now]*n][pos+(bel[now]^1)*n])return 0;
	for(int i=1;i<pos;i++)if(e[pos+bel[now]*n][i+(bel[ans[i]]^1)*n])return 0;
	for(int i=pos+1;i<=n;i++)if(e[pos+bel[now]*n][i]&&e[pos+bel[now]*n][i+n])return 0;
	//然后矛盾是没有了
	//但是还有字典序的限制
	//我们直接构造后面字典序最大即可
	memset(must,0xff,sizeof must);
	for(int i=1;i<=pos;i++)for(int j=pos+1;j<=n;j++)for(int k=0;k<2;k++)
		if(e[i+bel[ans[i]]*n][j+k*n])must[j]=k;
	for(int i=pos+1;i<=n;i++){
		int choice=must[i];
		if(choice==-1)choice=bel[l-1];
		if(e[i+choice*n][i+(choice^1)*n])choice^=1;
		ans[i]=lst[choice];
		for(int j=i+1;j<=n;j++)for(int k=0;k<2;k++)
			if(e[i+choice*n][j+k*n])must[j]=k;
	}
	for(int i=1;i<=n;i++)
		if(ans[i]>str[i]-'a')return 1;
		else if(ans[i]<str[i]-'a')return 0;
	return 1;
}
signed main(){
	//freopen("1.in","r",stdin);
	scanf("%s",str);l=strlen(str);
	for(int i=0;i<l;i++)bel[i]=(str[i]=='V');
	for(int i=0;i<l;i++)lst[bel[i]]=i;
	memset(same,0xff,sizeof same);
	memset(diff,0xff,sizeof diff);
	for(int i=0;i<l;i++)for(int j=i+1;j<l;j++)if(bel[j]!=bel[i]){diff[i]=j;break;}
	for(int i=0;i<l;i++)for(int j=i+1;j<l;j++)if(bel[j]==bel[i]){same[i]=j;break;}
	read(n,m);
	for(int SJYAK=1;SJYAK<=m;SJYAK++){
		int x,y;char a,b;
		read(x);get(a);read(y);get(b);
		a=(a=='V');b=(b=='V');
		// x a -> y b   y !b -> x !a
		e[x+a*n][y+b*n]=e[y+(b^1)*n][x+(a^1)*n]=1;
	}
	scanf("%s",str+1);
	for(int k=1;k<=2*n;k++)for(int i=1;i<=2*n;i++)for(int j=1;j<=2*n;j++)e[i][j]|=(e[i][k]&e[k][j]);
	for(int i=1;i<=n;i++){
		if(lim){
			//优先选str[i]-'a'
			vector<int>arr={str[i]-'a',same[str[i]-'a'],diff[str[i]-'a']};
			sort(arr.begin(),arr.end());
			for(auto x:arr)if(~x)
				if(chk(i,x)){
					ans[i]=x;
					lim&=(x==str[i]-'a');
					goto wyhaknoi;
				}
			orz;
			wyhaknoi:;
		}else{
			if(chk(i,0))ans[i]=0;
			else if(~diff[0]&&chk(i,diff[0]))ans[i]=diff[0];
			else orz;
		}
	}
	for(int i=1;i<=n;i++)pc(ans[i]+'a');
}
```
                                   ```

---

## 作者：Shunpower (赞：0)

很久没写过细节这么多的题了。

---------------

一眼考虑枚举前缀相等，则我们只需判定使得某一位变大是否有解。如果有解则保留前缀，进一步地向后确定，也是从小到大枚举位能选则选。这部分是 $\mathcal O(n\Sigma)$ 的，如果只枚举是 `V` 还是 `C` 的字母也是可以的，这样枚举部分就可以 $\mathcal O(n)$ 了。

然后考虑怎么判定。

考虑这个问题形如一个 2-SAT，每次查询确定前缀的情况下是否有解实际上等价于我们钦定了一些选法。所以不妨先按照 2-SAT 的方式去连限制，每个限制两条边，表示它本身和它的逆否。

我们对连出来的图预处理传递闭包。判定时，我们先扫钦定的点的传递闭包把所有能推出来的点推完，推完后检验是否有不合法的位置（使用了不存在的类型的字母，或者同时是两种类型）。

然后考虑剩下的点我们就可以随便选了，换句话说，我们只需检验剩下点的导出子图是否有解即可。

这里的无解仍然有两种可能性：

- $i$ 是 `C` 和 $i$ 是 `V` 互相可达。可以发现这种情况我们无需只判定导出子图，因为直接判定原图是这种情况的必要条件，但是在充分的情况下也是无解的，所以没有问题。
- 有一种类型不存在，但是会推到这种类型上。显然这种也只需要全局判定。

容易说明，只要判断掉这两种情况就一定有解。只需讨论是否有一种类型不存在就行了。

```cpp
string alp;
int n,m;
int cv,cc;
bool type[27];
string s;
vector <pii> p[210][2];
vector <pii> avd[210][2];
bool vis[210][2];
int col[210];
bool check(string pre){
	fr1(i,0,n-1) vis[i][0]=vis[i][1]=0;
	fr1(i,0,n-1) col[i]=-1;
	fr1(i,0,(int)pre.length()-1){
		for(auto j:avd[i][type[pre[i]-'a']]){
			if(~col[j.fi]){
				if(col[j.fi]!=j.se) return 0;
			}
			else col[j.fi]=j.se;
		}
	}
	fr1(i,0,n-1){
		if(!cv&&col[i]==0) return 0;
	}
	fr1(i,0,n-1){
		if(!cc&&col[i]==1) return 0;
	}
	return 1;
}
bool checksat(){
	fr1(i,0,n-1){
		int c=0;
		for(auto j:avd[i][0]) c+=(j==mp(i,1));
		for(auto j:avd[i][1]) c+=(j==mp(i,0));
		if(c==2) return 0;
	}
	if(!cc){
		fr1(i,0,n-1){
			fr1(j,0,n-1) col[j]=-1;
			for(auto j:avd[i][0]){
				if(j.se) return 0;
			}
		}
	}
	if(!cv){
		fr1(i,0,n-1){
			fr1(j,0,n-1) col[j]=-1;
			for(auto j:avd[i][1]){
				if(!j.se) return 0;
			}
		}
	}
	return 1;
}
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>alp;
	fr1(i,0,(int)alp.size()-1){
		if(alp[i]=='V') cv++,type[i]=0;
		else cc++,type[i]=1;
	}
	cin>>n>>m;
	fr1(i,1,m){
		int x,y;
		char op1,op2;
		cin>>x>>op1>>y>>op2;
		x--,y--;
		p[x][(op1=='V'?0:1)].pb({y,(op2=='V'?0:1)});
		p[y][(op2=='V'?1:0)].pb({x,(op1=='V'?1:0)});
	}
	fr1(i,0,n-1){
		fr1(op,0,1){
			fr1(j,0,n-1) vis[j][0]=vis[j][1]=0;
			queue <pii> q;
			q.push({i,op});
			while(!q.empty()){
				int x=q.front().fi,y=q.front().se;
				q.pop();
				if(vis[x][y]) continue;
				avd[i][op].pb({x,y});
				vis[x][y]=1;
				for(auto to:p[x][y]){
					q.push(to);
				}
			}
		}
	}
	if(!checksat()) return cout<<"-1\n",0;
	cin>>s;
	string tmp=s;
	if(check(s)) goto label;
	fr2(i,n-1,0){
		tmp.pop_back();
		fr1(j,s[i]-'a'+1,alp.size()-1){
			if(check(tmp+(char)('a'+j))){
				tmp+=(char)('a'+j);
				goto label;
			}
		}
	}
	cout<<"-1\n";
	ET;
	label:
	while(tmp.length()!=n){
		bool flg=0;
		fr1(i,0,alp.size()-1){
			if(check(tmp+(char)('a'+i))){
				flg=1;
				tmp+=(char)('a'+i);
				break;
			}
		}
		assert(flg);
	}
	cout<<tmp<<'\n';
	ET;
}
//ALL FOR Zhang Junhao.
```

复杂度 $\mathcal O(n^3\Sigma)$，修改枚举方式就能做到 $\mathcal O(n^3)$。

---

## 作者：yizhiming (赞：0)

补充说明一下枚举第一个比原序列大的位置的 $n^3$ 做法。

实际上有个老哥写了这样的题解，但是他判断的时候没有用 tarjan 复杂度退化了。

我没有太理解其他 $n^3$ 的做法，感觉贪心构造很容易假，已过题解评论区的 `hack`。

[链接](https://www.luogu.com.cn/problem/CF568C)。

## 题目大意

~~太麻烦了看链接吧。~~

## 题目分析

首先这个限制形式很容易想到 2-sat 去做，这里不赘述连边方式。

考虑如何贪心，先给出一种我一开始想的错误贪心。

从头开始枚举，若钦定这一位和原串相同，则判断一下钦定前 $i$ 个位置的值其他任意填是否合法，若合法则往下走，否则，考虑让这个点作为第一个比原串大的位置，然后往下扫，后续的点优先选最小，每次只判断是否有解。

但是如何判断是否有解呢？直接跑 2-sat 很合理，但是我们此时并没有考虑到字典序的情况，我们拿第三个样例来看。

这个样例有什么问题呢？实际上在我们扫到第二个位置的时候，钦定了前 $2$ 个的集合选择情况为 $VC$ 是合法的，这从输出可以看出来，也就是说，我们没办法在当前这一步确定是否满足字典序限制，只是在不考虑字典序的前提下有解。

这样就有了两种解决方法，第一种考虑维护每个节点是否能作为较大点，若当前点后续再无较大点，那么就要钦定这个位置较大。

这个当然还是错的，因为可能还未到达满足这个条件的点的时候就已经无法满足字典序了。当然这个做法可以在不合法的时候回退到上一个能变较大的点，重新调整，这样应该能做到 $n^5$ 或者 $n^4$。

第二种方法就是枚举最大值位置在哪里，我们从后往前开始钦定最大值的位置 $k$，则 $[1,k-1]$ 与原串完全相同，$k$ 位置分两种情况 $VC$，若取值较小的合法则优先较小的，否则判断一下较大的是否合法，若不合法则判断下一位。

只要我们找到了一个合法的 $k$，满足他在取 $V/C$ 的时候，有解，且 $V/C$ 中存在一个值比原串的 $k$ 位置大，那么就可以用这个点来更新答案，具体的，我们从 $k+1$ 开始贪心，此时就不需要判断字典序的限制了，直接考虑钦定这个位置为 $a$ 是否可行，否则当前位置为另外一个集合的最小值。

再就是注意一点小小的细节，我们判断钦定前 $k$ 位固定，后面任选的时候，是意味着后面既能选 $V$ 又能选 $C$，所以当初始只有 $C$ 或只有 $V$ 的时候会被卡掉，需要特判这种情况。

复杂度就考虑第一种找 $k$ 的次数只会进行最多 $2n$ 次，每次一遍建图一遍 tarjan，第二种贪心确定答案只会进行一次，每次 $n$ 遍 tarjan，所以复杂度即为 $O(nm)$。

## Code

注意特判完全相等的情况。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 405;
char s[30],a[N];
int n,m;
bool op(char x){
	if(x=='V'){
		return 0;
	}else{
		return 1;
	}
}
struct aa{
	int p1,x1,p2,x2;
}in[N*N];
int id[30];
vector<int>ed[N];
int rk(int x,int y){
	return x+y*n;
}
int lim;
int val[N];
int pan=-1;
void build(int x){
	for(int i=1;i<=2*n;i++){
		ed[i].clear();
	}
	if(pan>=0){
		for(int i=1;i<=n;i++){
			ed[rk(i,pan^1)].push_back(rk(i,pan));
		}
	}
//	cout<<"X:"<<x<<" "<<lim<<"\n";
	for(int i=1;i<=x-1;i++){
		int y = id[a[i]-'a'];
//		cout<<"I:"<<x<<" "<<i<<" "<<y<<"\n";
		ed[rk(i,y^1)].push_back(rk(i,y));
	}
	if(x<=n){
		int y = val[x];
		ed[rk(x,y^1)].push_back(rk(x,y));
	}
	if(lim!=n+1){
		for(int i=x+1;i<=lim;i++){
			int y = val[i];
			ed[rk(i,y^1)].push_back(rk(i,y));
		}
	}
	for(int i=1;i<=m;i++){
		ed[rk(in[i].p1,in[i].x1)].push_back(rk(in[i].p2,in[i].x2));
		ed[rk(in[i].p2,in[i].x2^1)].push_back(rk(in[i].p1,in[i].x1^1));
	}
}
int dfn[N],low[N],cnt,sta[N],top;
bool vis[N];
int bel[N],col;
void tarjan(int u){
	dfn[u] = low[u] = ++cnt;
	vis[u] = 1;sta[++top] = u;
	for(auto x:ed[u]){
		if(!dfn[x]){
			tarjan(x);
			low[u] = min(low[u],low[x]);
		}else if(vis[x]){
			low[u] = min(low[u],dfn[x]);
		}
	}
	if(low[u]==dfn[u]){
		bel[u] = ++col;
		vis[u] = 0;
		while(sta[top]!=u){
			bel[sta[top]] = col;
			vis[sta[top--]] = 0;
		}
		top--;
	}
}
bool check(){
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(bel,0,sizeof(bel));
	cnt = 0;col = 0;
	for(int i=1;i<=2*n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
//		cout<<"BEL:"<<bel[rk(i,0)]<<" "<<bel[rk(i,1)]<<"\n";
		if(bel[rk(i,0)]==bel[rk(i,1)]){
			return false;
		}
	}
	return true;
}
int main(){
//	freopen("data.txt","r",stdin);
	scanf("%s",s);
	int sz = strlen(s);
	for(int i=0;i<sz;i++){
		id[i] = op(s[i]);
		if(pan==-1){
			pan = id[i];
		}else if(pan!=id[i]){
			pan = -2;
		}
	}
	n = read();m = read();
	lim = n+1;
	for(int i=1;i<=m;i++){
		char opt[5];
		in[i].p1 = read();scanf("%s",opt);in[i].x1 = op(opt[0]);
		in[i].p2 = read();scanf("%s",opt);in[i].x2 = op(opt[0]);
	}
	scanf("%s",a+1);
	build(0);
	if(!check()){
		cout<<-1<<"\n";
		return 0;
	}
	for(int i=n+1;i>=1;i--){//枚举第一个变大位置 
		if(i==n+1){
			build(i);
			if(check()){
				cout<<a+1<<"\n";
				return 0;
			}
			continue;
		}
		int c=27,d=27;
		lim = n+1;
//		cout<<"I:"<<i<<" "<<c<<" "<<d<<" "<<a[i]-'a'+1<<"\n";
		for(int j=a[i]-'a'+1;j<sz;j++){
			if(id[j]==0&&c==27){
				c = j;
//				break;
			}
			if(id[j]==1&&d==27){
				d = j;
//				break;
			}
		}
		if(c==27&&d==27){
			continue;
		}
		val[i] = (c>d);
		build(i);
//		cout<<"I:"<<i<<" "<<c<<" "<<d<<"\n";
		if(check()){
			for(int j=i+1;j<=n;j++){
				lim = j;
				val[j] = id[0];
				build(i);
				if(!check()){
					val[j]^=1;
				}
			}
			for(int j=1;j<i;j++){
				cout<<a[j];
			}
			cout<<(char)(min(c,d)+'a');
			for(int j=i+1;j<=n;j++){
				for(int k=0;k<sz;k++){
					if(id[k]==val[j]){
						cout<<(char)(k+'a');
						break;
					}
				}
			}
			return 0;
		}else if(max(c,d)!=27){
			val[i]^=1;
			build(i);
			if(!check()){
				continue;
			}
			for(int j=i+1;j<=n;j++){
				lim = j;
				val[j] = id[0];
				build(i);
				if(!check()){
					val[j]^=1;
				}
			}
			for(int j=1;j<i;j++){
				cout<<a[j];
			}
			cout<<(char)(max(c,d)+'a');
			for(int j=i+1;j<=n;j++){
				for(int k=0;k<sz;k++){
					if(id[k]==val[j]){
						cout<<(char)(k+'a');
						break;
					}
				}
			}
			return 0;
		}
	}
	cout<<"-1\n";
	return 0;
}
```


---

