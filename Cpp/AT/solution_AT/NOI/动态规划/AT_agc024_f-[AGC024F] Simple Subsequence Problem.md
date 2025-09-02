# [AGC024F] Simple Subsequence Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc024/tasks/agc024_f

`0`,`1` からなる文字列からなる集合 $ S $ と整数 $ K $ が与えられます。 $ S $ に属する異なる $ K $ 個以上の文字列の部分列であるような最長の文字列を求めてください。 条件を満たすものが複数ある場合、辞書順で最小になるものを求めてください。

ただし、$ S $ は以下の形式で与えられます。

- 整数 $ N $ と、$ N+1 $ 個の文字列が与えられる。$ N+1 $ 個の文字列は順に $ X_0,X_1,...,X_N $ であり、全ての $ i(0\leq\ i\leq\ N) $ に対し、$ X_i $ の長さは $ 2^i $ である。
- どの整数の組 $ (i,j)(0\leq\ i\leq\ N,0\leq\ j\leq\ 2^i-1) $ に対しても、$ X_i $ の $ j $ 文字目(ただし、最初の文字を $ 0 $ 文字目、最後の文字を $ 2^i-1 $ 文字目とする)が `1` であることと、$ j $ を(必要なら最初に $ 0 $ を補って) $ i $ 桁からなる二進表記で表してできる文字列が $ S $ に属することが同値である。
- 長さ $ N+1 $ 以上の文字列は、$ S $ には含まれない。

また、文字列 $ A $ が 文字列 $ B $ の部分列であるとは、ある整数列 $ t_1\ <\ ...\ <\ t_{|A|} $ が存在して、全ての $ i(1\leq\ i\leq\ |A|) $ に対し $ A $ の $ i $ 文字目と $ B $ の $ t_i $ 文字目が等しいことを指します。

## 说明/提示

### 制約

- $ 0\ \leq\ N\ \leq\ 20 $
- $ X_i(0\leq\ i\leq\ N) $ の長さは $ 2^i $ であり、`0` と `1` のみからなる
- $ 1\ \leq\ K\ \leq\ |S| $
- $ K $ は整数である

### Sample Explanation 1

$ S $ に属する文字列は、(空文字列),`1`,`00`,`10`,`11`,`001`,`100`,`101`,`110` です。 これらのうち $ 4 $ つ以上の部分列となる最長の文字列のうち辞書順最小のものは、`10` です。

### Sample Explanation 3

空文字列が答えになります。

## 样例 #1

### 输入

```
3 4
1
01
1011
01001110```

### 输出

```
10```

## 样例 #2

### 输入

```
4 6
1
01
1011
10111010
1101110011111101```

### 输出

```
100```

## 样例 #3

### 输入

```
2 5
0
11
1111```

### 输出

```
```

# 题解

## 作者：小粉兔 (赞：27)

我们直接考虑所有 $(2^{N + 1} - 1)$ 个长度在 $0 \sim N$ 之间的 $01$ 串，计算它们到底是多少个 $S$ 中的串的子序列。

当枚举的串为 $A$ 时，令这个值为 $\mathrm{val}(A)$，这样直接枚举所有 $01$ 串就能得到答案了。

我们考虑子序列自动机，也就是在判定一个串 $A$ 是不是另一个串 $B$ 的子序列时：

比如 $A = \mathtt{011001}$，$B = \mathtt{110110101}$，因为 $A$ 中的第一个字符是 $\texttt{0}$，考虑 $B$ 中第一个 $\texttt{0}$ 的位置。

用 $A$ 的第一个字符 $\texttt{0}$ 去匹配 $B$ 中的第一个 $\texttt{0}$，则转化为 $A = \mathtt{11001}$，$B = \mathtt{110101}$。

所谓“子序列自动机”的好处在于它的匹配过程是唯一的。

那么，我们这样考虑：对于一个 $01$ 串 $C \in S$，我们希望 $C$ 的所有子序列 $A$ 的 $\mathrm{val}$ 值都加上 $1$。

那么考虑 DP：令 $\mathrm{dp}(A | B)$ 表示使用 $A$ 去匹配某个原串 $C \in S$，匹配剩下的串是 $B$，原串 $C$ 的方案数。

比如 $\mathrm{dp}(\mathtt{00} | \mathtt{110110101})$ 可以转移到：

1. 匹配了第一个 $\mathtt{0}$：$\mathrm{dp}(\mathtt{000} | \mathtt{110101})$。
2. 匹配了第一个 $\mathtt{1}$：$\mathrm{dp}(\mathtt{001} | \mathtt{10110101})$。
3. 停止匹配：$\mathrm{dp}(\mathtt{00} | \varepsilon)$。

则可以发现，$\mathrm{val}(A) = \mathrm{dp}(A | \varepsilon)$。关于边界条件，令 $\mathrm{dp}(\varepsilon | C) = 1$ 即可（$C \in S$）。

这样 DP 的话，因为过程中 $|A| + |B| \le N$，所以状态总数是 $\mathcal O (N 2^N)$ 的。

使用合适的方法存储状态，就可以做到 $\mathcal O (N 2^N)$ 的复杂度。

时间复杂度为 $\mathcal O (N 2^N)$，[评测链接](https://atcoder.jp/contests/agc024/submissions/10785792)。

---

## 作者：GuanYunchang_ (赞：4)

## 题意
给定一个 $01$ 串集合 $S$，其中每个串的长度都不超过 $N$，求出至少是 $S$ 中 $K$ 个串的子序列的最长串，如果有多解，输出字典序最小的那组解。
## 数据范围
$ 0\leq N\leq 20$，$0\leq K\leq \vert S\vert$

## 分析
由于初始给定的集合 $S$ 比较大，我们考虑自动机DP。

首先考虑子序列匹配的过程，假设我们有两个串 $A=10$，$B=00110$，要判断 $A$ 是否是 $B$ 的子序列：

在 $B$ 中找到 $A$ 的第一个字符 $1$ 的位置 ，在从这个位置的下一个位置开始找 $A$ 中的第二个字符 $0$（即在剩下的 $10$ 中匹配 $0$），如果都找得到就匹配成功。本质上是一个贪心的过程，能匹配就匹配肯定是最优的。

知道了如何匹配后，我们就可以据此来设计状态，令 $f_{A,B}$ 表示已经匹配的子序列为 $A$，剩下还可以用来匹配的串为 $B$ 的状态下 $A$ 是多少个串的子序列。转移时，枚举下一个匹配的字符是 $0$ 还是 $1$，在 $B$ 中找第一个 $0$ 或 $1$ 位置即可。

代码实现上，显然不能直接记录 $A,B$ ，考虑到我们只需要知道 $A,B$ 分别的长度和他们合在一起的状态 $T$，而在转移时我们会从小到大枚举 $A$ 的长度，所以只用记录 $A+B$ 的长度即可。这样时空复杂度就都是 $O(n2^n)$。

## 注意事项
开数组尽量保证转移时访问地址连续，这样会快很多（对我而言，三倍），下面的代码把 ans 数组去掉（只用 f 来判定是否大于等于 k）在洛谷上就是目前 rk1 了。

## 代码

```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,b,a) for(int i=b;i>=a;i--)
using namespace std;
inline int read(){
	int x=0;char s=gc;
	while('0'>s||s>'9')s=gc;
	while('0'<=s&&s<='9'){x=x*10+s-48;s=gc;}
	return x;
} 
int n,Ans,ansb,kk,ans[1<<20],A1[21][1<<20],f[21][1<<20],nxt[21][1<<20];
char s[1<<20];
int main(){
	n=read(),kk=read();
	FOR(i,0,n){
		cin>>s;
		FOR(j,0,(1<<i)-1)if(s[j]=='1')f[i][j]=1;
	}	
	FOR(i,1,n)
		FOR(j,0,(1<<i)-1){
			int p=(j>>(i-1))&1;
			nxt[i][j]=-1;
			ROF(k,i-2,0)if((j>>k&1)!=p){nxt[i][j]=k+1;break;}
		}
	FOR(i,0,n){
		FOR(j,0,(1<<i)-1)ans[j]=0;
		FOR(k,0,n-i)FOR(j,0,(1<<(i+k))-1)ans[j>>k]+=f[i+k][j];
		ROF(j,(1<<i)-1,0)if(ans[j]>=kk)Ans=j,ansb=i;
        
		FOR(k,1,n-i)
			FOR(j,0,(1<<(i+k))-1){
				int p=nxt[k][j&((1<<k)-1)];
				if(p!=-1){
					int t=j&((1<<p)-1);
					f[i+p][((j>>k)<<p)+t]+=f[i+k][j];
				}
			}
	}
	ROF(i,ansb-1,0)cout<<((Ans>>i)&1);
	return 0;
} 
/*
3 4
1
01
1011
01001110
*/ 
```




---

## 作者：GavinZheng (赞：4)

我们注意到字符串长度很短，但是个数很多。所以我们可以考虑暴力把所有子序列跑出来，然后看看哪些子序列是K个以上字符串的公共子序列。

我们定义二元组$(S,T)$代表开头为$S$，后面加上$T$的一个子序列得到的子序列的个数。令字符串集合为$P$那么初始化的时候有：$\forall T\in P,\space (\varnothing, T)=1$。然后每次转移就考虑三种决策：

1. 直接结束，将$T$置为$empty$
2. 将$T$中的第一个1及其之前部分删除，$S$加上1
3. 将$T$中的第一个0及其之前部分删除，$S$加上0

然后我们扫描所有$(S,\varnothing)$，在计数器$\geq k$的部分中寻找字典序列最小的即可。因为我们每次选择转移都选择的是第一个规定的字符，是按照子序列自动机的方式进行的转移。因为一个子序列在子序列自动机上的路径唯一，所以我们这种方法是不会算重的。

一共有$N\cdot 2^N$种状态，进过预处理之后的转移是$O(1)$的。因此复杂度是$N\cdot 2^N$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=1<<22;
typedef long long ll;
typedef unsigned long long ull;
int data[maxn][21],n,k;
int mem[maxn*2];
char s[maxn];
int mx=1000000000,mxl=0;
void update(int sta,int nums,int len) {
    mem[sta|(1<<len)]+=nums;
    if(mem[sta|(1<<len)]>=k)
        if(mxl<len)mxl=len,mx=sta;
        else if(mxl==len)mx=min(mx,sta);

}
int main() {
    scanf("%d%d",&n,&k);
    for(int i=0;i<=n;i++) {
        scanf("%s",s);//len=2^i
        for(int j=0;j<(1<<i);j++) {
            int tmp=j;
            tmp|=1<<i;
            data[tmp][0]+=(s[j]=='1');
        }
    }
    for(int i=0;i<=n;i++) {//枚举已经拿了多少个
        for(int j=0;j<(1<<(n+1));j++) {//一共有n+1位
            if(!data[j][i])continue;//t-s
            ull s=j&((1<<i)-1),t=j>>i;int l=(32-__builtin_clz(t))-1;//有t多少位
            if(i)update(s,data[j][i],i);
            if(!l){continue;}
            t^=(1<<l);
            int first1=(32-(t?__builtin_clz(t):32));//第一个1在第几位
            unsigned int num=t<<(32-l);
            int first0=l?(l-((~num)?__builtin_clz(~num):l)):0;
            int newt,news;
            if(first1>0){//去掉一个1
                newt=t&((1<<first1)-1);
                newt|=(1<<first1-1);
                news=(s<<1)|1;
                data[(newt<<(i+1))|news][i+1]+=data[j][i];
            }
            if(first0>0){//去掉一个0
                newt=t&((1<<first0)-1);
                newt|=(1<<first0-1);
                news=(s<<1);
                data[(newt<<(i+1))|news][i+1]+=data[j][i];
            }
        }
    }
    if(mx==1000000000){puts("");return 0;}
    for(int i=mxl;i>=1;i--) {
        printf("%d",(mx&(1<<i-1))?1:0);
    }
    printf("\n");
    return 0;
}
```

---

## 作者：樱雪喵 (赞：2)

Tags: 子序列自动机，dp

发现可能作为答案的字符串总数不多，只有 $2^{n+1}$，统计答案时可以暴力枚举。因此我们只要想办法求出每个 $01$ 串是 $S$ 中多少个字符串的子序列就可以了。

设 $f_i$ 表示字符串 $i$ 是 $S$ 中多少个字符串的子序列。但这样显然是没法转移的：下一个状态由字符串 $i$ 添加一个字符得到，会重复计数。

考虑把子序列自动机的匹配过程压进 dp 状态。设 $f(A \texttt{|} B)$ 表示 $S$ 集合中，满足子序列自动机上已匹配的部分为 $A$，未匹配的部分为 $B$ 的方案数。  
举个例子，$f(\texttt{10|1101})$ 可以向以下状态转移：

- 匹配一个 $\texttt{1}$，有 $f(\texttt{10|1101})\to f(\texttt{101|101})$；
- 匹配一个 $\texttt{0}$，有 $f(\texttt{10|1101})\to f(\texttt{100|1})$；
- 在当前位置结束匹配，有 $f(\texttt{10|1101})\to f(\texttt{10|})$。

那么字符串 $s$ 作为子序列的出现次数为 $f(s\texttt{|})$。  
对于初始属于 $S$ 的字符串 $t$，有初始状态 $f(\texttt{|}t)=1$。

一个状态可以由整个字符串和分隔线位置唯一确定。但因为字符串有前导 $0$，直接记序列长度会使空间复杂度变成 $\mathcal{O}(2^nn^2)$，存不下。不过实际上的总字符串数只有 $2n$，可以通过预处理标号将空间复杂度去掉一个 $n$。

```cpp
const int N=(1<<20)+5;
int n,K;
int id[21][N],f[21][N<<1];
int len[N<<1],s[N<<1];
int main()
{
    n=read(),K=read(); int tot=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<(1<<i);j++)
        {
            char c; cin>>c;
            id[i][j]=++tot,f[0][tot]=c-'0';
            len[tot]=i,s[tot]=j;
        }
    for(int i=0;i<=n;i++)
    {
        for(int j=1;j<=tot;j++)
        {
            int l=len[j],s=::s[j];
            if(!f[i][j]||i>=l) continue;
            int A=0;  //none
            for(int k=l-1;k>=l-i;k--) A=(A<<1)|(s>>k&1);
            f[i][id[i][A]]+=f[i][j];

            int pos=-1; //1
            for(int k=l-i-1;k>=0;k--) if(s>>k&1) {pos=k;break;}
            if(pos!=-1)
            {
                int B=A<<1|1;
                for(int k=pos-1;k>=0;k--) B=(B<<1)|(s>>k&1);
                f[i+1][id[i+1+pos][B]]+=f[i][j];
            }

            pos=-1; //0
            for(int k=l-i-1;k>=0;k--) if(!(s>>k&1)) {pos=k;break;}
            if(pos!=-1)
            {
                int B=A<<1;
                for(int k=pos-1;k>=0;k--) B=(B<<1)|(s>>k&1);
                f[i+1][id[i+1+pos][B]]+=f[i][j];
            }
        }
    }
    int ans=0,anslen=0;
    for(int i=1;i<=tot;i++)
        if(f[len[i]][i]>=K&&anslen<len[i]) anslen=len[i],ans=s[i];
    for(int i=anslen-1;i>=0;i--) printf("%d",ans>>i&1); printf("\n");
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc024_f)

**题目大意**

> 给定若干长度 $\le n$ 的 01 串，求一个 01 串至少是其中 $k$ 个串的子序列，且长度最长，同长度字典序最小。
>
> 数据范围：$n\le 20$。

**思路分析**

可以考虑计算出每个 01 串 $s$ 是多少个串的子序列。

一个比较复杂的问题是如何让每个串恰好计算一次，可以考虑用子序列自动机进行判定。

对每个串建子序列自动机，$f_{s,t}$ 表示当前取出的模式串是 $s$，在子序列自动机上匹配后，文本串的剩余部分是 $t$，这样的文本串有多少个。

转移就是 $s\to s+c$（$c\in\{0,1\}$），然后 $t$ 删除从前往后第一个 $c$ 以及其前面的部分，可以用位运算优化转移。

我们可以发现 $|s|+|t|\le n$，因此总状态数只有 $\mathcal O(n2^n)$ 级别，转移可以做到线性。

时间复杂度 $\mathcal O(n2^n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,K,f[21][1<<21],g[1<<21];
int hb(int x) { return 31-__builtin_clz(x); }
void add(int x,int i,int y,int w) { f[i][x<<i|y]+=w; }
signed main() {
	cin>>n>>K;
	for(int i=0;i<=n;++i) for(int s=0;s<(1<<i);++s) {
		char op; cin>>op;
		if(op=='1') ++f[i][1<<i|s];
	}
	for(int i=n;~i;--i) for(int s=0;s<(1<<(n+1));++s) if(f[i][s]) {
		int x=s>>i,y=s&((1<<i)-1);
		g[x]+=f[i][s];
		if(y) {
			int j=hb(y);
			add(x<<1|1,j,y&((1<<j)-1),f[i][s]);
		}
		if(y!=(1<<i)-1) {
			int j=hb(y^((1<<i)-1));
			add(x<<1,j,y&((1<<j)-1),f[i][s]);
		}
	}
	for(int i=n;i>=1;--i) for(int s=0;s<(1<<i);++s) if(g[1<<i|s]>=K) {
		for(int o=i-1;~o;--o) cout<<(s>>o&1);
		cout<<"\n";
		return 0;
	}
	cout<<"\n";
	return 0;
}
```

---

## 作者：xht (赞：0)

## [Simple Subsequence Problem](https://atcoder.jp/contests/agc024/tasks/agc024_f)

### 题意

- 给定一个 $0/1$ 字符串组成的集合 $s$ 和一个整数 $k$。
- 求出最长的字符串 $t$，满足 $t$ 是 $s$ 中至少 $k$ 个字符串的子序列，在最长的基础上最小化字典序。
- $s$ 并不直接给出，而是通过以下方式给出：
  - 给定 $n$ 和 $n+1$ 个 $0/1$ 字符串 $x_{0\dots n}$，其中对于 $i \in [0,n]$，$x_i$ 的下标从 $0$ 开始，长度为 $2^i$。
  - 对于每对满足 $i \in [0,n], j \in [0,2^i)$ 的二元组 $(i,j)$，若 ${x_i}_j = 1$ 则 $j$ 的 $i$ 个字符的二进制表示（可能有前导零）$\in s$，否则 $\not\in s$。
  - $s$ 中不存在长度 $>n$ 的字符串。
- $n \le 20$，$k \le |s|$。

### 题解

考虑直接枚举所有可能的 $0/1$ 串，计算它们是多少个 $s$ 中的串的子序列，设串 $a$ 的答案为 $ans_a$。

考虑对于每个 $c \in s$，将 $c$ 的所有子序列 $a$ 的 $ans_a$ 都 $+1$。

考虑 DP 完成这个过程，令 $f(a|b)$ 表示使用 $a$ 去匹配某个原串 $c \in s$，匹配剩下的串为 $b$ 的方案数。

比如 $f(00 | 110110101)$ 可以转移到：

- 匹配了一个 $0$：$f(000 | 110101)$。
- 匹配了一个 $1$：$f(001 | 10110101)$。
- 停止匹配：$f(00 |)$。

则 $ans_a = f(a | )$，边界为 $f(| c) = 1(c \in s)$。

因为 $|a|+|b| \le n$，所以状态数为 $\mathcal O(n2^n)$，转移为 $\mathcal O(1)$。

总时间复杂度 $\mathcal O(n2^n)$。

### 代码

```cpp
const int N = 21;
int n, k, b[1<<N|1], t[1<<N|1][2], f[N][1<<N|1], ans = 1;
char c;

int main() {
	rd(n, k);
	for (int i = 0; i <= n; i++)
		for (int x = 0; x < 1 << i; x++)
			rdc(c), f[i][1<<i^x] = c - '0';
	b[0] = -1;
	for (int x = 1; x < 2 << n; x++) b[x] = b[x>>1] + 1;
	for (int x = 2; x < 2 << n; x++)
		if (x >> (b[x] - 1) & 1) t[x][1] = x ^ 1 << b[x], t[x][0] = t[t[x][1]][0];
		else t[x][0] = x ^ 3 << (b[x] - 1), t[x][1] = t[t[x][0]][1];
	for (int i = n; i; i--)
		for (int x = 1 << i; x < 2 << n; x++)
			if (f[i][x]) {
				int o = x >> i, B = (x & ((1 << i) - 1)) ^ 1 << i;
				if (t[B][0]) f[b[t[B][0]]][(o<<1^1)<<b[t[B][0]]^t[B][0]] += f[i][x];
				if (t[B][1]) f[b[t[B][1]]][(o<<1^0)<<b[t[B][1]]^t[B][1]] += f[i][x];
				f[0][o] += f[i][x];
			}
	for (int x = 2; x < 2 << n; x++)
		if (f[0][x] >= k && b[x] > b[ans]) ans = x;
	int i = n;
	while (!(ans >> i & 1)) i--;
	while (i--) printc((ans >> i & 1) + '0');
	return 0;
}
```

---

