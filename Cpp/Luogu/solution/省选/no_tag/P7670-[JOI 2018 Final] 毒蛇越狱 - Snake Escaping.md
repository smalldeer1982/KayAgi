# [JOI 2018 Final] 毒蛇越狱 / Snake Escaping

## 题目背景

**请注意本题特殊的内存限制。**

## 题目描述

JOI 实验室有 $2^L$ 条毒蛇。蛇的编号为  $0,1,\cdots,2^L−1$。每条蛇从头到尾分为  $L$ 个部分。每个部分的颜色是蓝色或红色。 对于毒蛇 $i$，令 $i = \sum_{k=1}^{L} c_k2^{L-k}$（$0 \leq c_k \leq 1$）为 $i$ 的二进制表达式。那么，  
- 如果 $c_k=0$，毒蛇 $i$ 从头开始的第 $k$ 部分的颜色是蓝色，  
- 如果 $c_k=1$，毒蛇 $i$ 从头开始的第 $k$ 部分的颜色是红色。  

每条毒蛇都有一个 $0$ 到 $9$ 之间的整数，包括 $0$ 和 $9$，为毒性。给出一个由 $\texttt{0,1,2,3,4,5,6,7,8,9}$ 组成的长度为  $2^L$ 的字符串 $S$。第 $i$ 个字符（$1 \leq i \leq 2^L$）是毒蛇 $i−1$ 的毒性。由于毒蛇行动迅速，所以经常从 JOI 实验室逃走。住在实验室附近的人向 JOI 实验室投诉，他们看到毒蛇从实验室逃逸。您将收到 $Q$ 天的投诉清单。 第 $d$ 天的投诉（$1 \leq d \leq Q$）是一个长度为 $L$ 的字符串 $T_d$，由 $\texttt{0,1,?}$ 组成。  
- 如果 $T_d$ 的第 $j$ 个字符（$1 \leq j ≤ L$）为 $\texttt{0}$，这意味着第 $d$ 天从实验室逃出的每条毒蛇的第 $j$ 个部分是蓝色的，  
- 如果 $T_d$ 的第 $j$ 个字符（$1 \leq j \leq L$）为 $\texttt{1}$，这意味着第 $d$ 天从实验室逃出的每条毒蛇的第 $j$ 部分是红色的，并且  
- 如果 $T_d$ 的第 $j$ 个字符（$1 \leq j \leq L$）为 $\texttt{?}$，这意味着人们没有提供关于第 $d$ 天从实验室逃逸的毒蛇的第 $j$ 部分的信息。  

所有的投诉都是准确的信息。所有从实验室逃逸的毒蛇都在同一天被 JOI 实验室的工作人员收留。可能发生同一条蛇在不同的日子逃脱。  
JOI 实验室执行主任 K 教授为了估计毒蛇逃逸的风险，想知道可能逃出实验室的毒蛇的毒性总和。 你的任务是编写一个程序，根据 $Q$ 天的投诉列表，计算每天可能从实验室逃逸的蛇的毒性总和。  
现给定描述毒蛇毒性的字符串 $S$ 和 $Q$ 天的投诉列表，请编写一个程序来计算每天可能从实验室逃逸的蛇的毒性总和。  


## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq L \leq 20$，$1 \leq Q \leq 10^6$，$S$ 是长度为 $2^L$ 的字符串，字符串 $S$ 由 $\texttt{0,1,2,3,4,5,6,7,8,9}$ 组成，$T_d$ 是长度为 $L$（$1 \leq d \leq Q$）的字符串，字符串 $T_d$ 由 $\texttt{0,1,?}$（$1 \leq d \leq Q$）组成。  
- Subtask $1$（$5$ points）：$L \leq 10$，$Q \leq 1000$。  
- Subtask $2$（$7$ points）：$L \leq 10$。  
- Subtask $3$（$10$ points）：$L \leq 13$。  
- Subtask $4$（$53$ points）：$Q \leq 5000$。  
- Subtask $5$（$25$ points）：没有额外的限制。  

#### 样例说明  
**对于样例 $1$**：$L=3$，共 $2^3=8$条毒蛇，它们中的每一条都分为 $3$ 个部分。 投诉时间为 $5$ 天。  
- 第一天，可能逃出实验室的毒蛇只有毒蛇 $0$。毒性总和为 $1$。  
- 第二天，可能从实验室逃逸的毒蛇是毒蛇 $0,1,2,3$。毒性总和为 $10$。  
- 第三天，可能从实验室逃逸的毒蛇是毒蛇  $4,6$。毒性总和为 $12$。  
- 第四天，可能从实验室逃逸的毒蛇是毒蛇 $3,7$。毒性总和是 $12$。  
- 第五天，可能从实验室逃逸的毒蛇是毒蛇 $0,1,2,3,4,5,6,7$。毒性总和为 $36$。  
#### 题目说明：  
来源于 The 17th Japanese Olympiad in Informatics (JOI 2017/2018) Final Round 的 [T5：Snake Escaping](https://www.ioi-jp.org/joi/2017/2018-ho/2018-ho-t5-en.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
3 5
12345678
000
0??
1?0
?11
???```

### 输出

```
1
10
12
12
36```

## 样例 #2

### 输入

```
4 8
3141592653589793
0101
?01?
??1?
?0??
1?00
01?1
??10
????```

### 输出

```
9
18
38
30
14
15
20
80```

# 题解

## 作者：ix35 (赞：21)

这是一种经典的做法，题解里竟然没有。

设 $S$ 中 $0,1,\texttt{?}$ 的个数分别为 $a,b,c$。

算法一：暴力将每个 $\texttt{?}$ 换成 $0$ 或 $1$ 求和，时间复杂度 $O(2^c)$。

算法二：对 $0$ 容斥，也就是写成 $(\times s(0))=(\times (s(\texttt{?})-s(1)))$ 的形式，将每个 $0$ 换成 $\texttt{?}$ 和 $1$，而对于只有 $\texttt{?}$ 和 $1$ 的情况可以直接预处理高维后缀和后计算，时间复杂度 $O(2^a)$。

算法三：对 $1$ 容斥，过程同上，用高维前缀和计算，时间复杂度 $O(2^b)$。

选取最优的算法，单次询问时间复杂度 $O(\min(2^a,2^b,2^c))$，而由于 $a+b+c=n$ 所以我们有 $\min(a,b,c)\leq \dfrac{n}{3}$，加上高维前后缀和的复杂度，总的时间复杂度为 $O(q2^{\frac{n}{3}}+n\times 2^n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1200010;
int l,q,ans,cnt0,cnt1,cntq,sz0,sz1,cq[30],c0[30],c1[30],a[MAXN],b[MAXN],c[MAXN];
char t[30],s[MAXN];
void dfsq (int x,int msk) {
	if (x==cntq+1) {ans+=a[msk];return;}
	dfsq(x+1,msk);
	dfsq(x+1,msk|(1<<cq[x]));
	return;
}
void dfs0 (int x,int flg,int msk) {
	if (x==cnt0+1) {ans+=c[msk]*flg;return;}
	dfs0(x+1,flg,msk);
	dfs0(x+1,-flg,msk|(1<<c0[x]));
	return;
}
void dfs1 (int x,int flg,int msk) {
	if (x==cnt1+1) {ans+=b[msk]*flg;return;}
	dfs1(x+1,flg,msk|(1<<c1[x]));
	dfs1(x+1,-flg,msk);
	return;
} 
int main () {
	scanf("%d%d%s",&l,&q,s+1);
	for (int i=0;i<(1<<l);i++) {a[i]=b[i]=c[i]=s[i+1]-'0';}
	for (int i=1;i<(1<<l);i<<=1) {
		for (int j=0;j<(1<<l);j+=(i<<1)) {
			for (int k=0;k<i;k++) {b[i+j+k]+=b[j+k];}
		}
	}
	for (int i=1;i<(1<<l);i<<=1) {
		for (int j=0;j<(1<<l);j+=(i<<1)) {
			for (int k=0;k<i;k++) {c[j+k]+=c[i+j+k];}
		}
	}
	for (int i=1;i<=q;i++) {
		scanf("%s",t+1);
		for (int i=1;i<=l/2;i++) {swap(t[i],t[l-i+1]);}
		cnt0=0,cnt1=0,cntq=0,sz0=0,sz1=0;
		for (int i=0;i<l;i++) {
			if (t[i+1]=='0') {c0[++cnt0]=i;}
			else if (t[i+1]=='1') {c1[++cnt1]=i,sz1|=(1<<i);}
			else {cq[++cntq]=i,sz0|=(1<<i);}
		}
		ans=0;
		if (cntq<=6) {dfsq(1,sz1);}
		else if (cnt0<=6) {dfs0(1,1,sz1);}
		else {dfs1(1,1,sz0);}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Aestas16 (赞：11)

我们先来考虑一个很暴力的做法：显然每个位置上只有 `0`、`1`、`?` 三种可能，我们考虑通过递推或记搜预处理出 $3^L$ 种状态，然后直接查询即可，这样做的时间复杂度是 $\Theta(3^L + q)$，可以通过 $L \le 13$ 的数据。

我们再来考虑一个更暴力的做法：对于每个询问暴力枚举每个 `?` 是 `0` 还是 `1`，时间复杂度 $\Theta(q2^L)$。

我们发现第一个暴力的瓶颈在于预处理，第二个暴力的瓶颈在于询问，那么结合这两个暴力是不是就可以得到一个复杂度正确的算法了呢？

答案是肯定的，我们考虑预处理 $L-k$ 位的答案，对于每一个询问将前 $k$ 位单独提出来枚举 `?` 的所有情况，然后对于后 $L-k$ 位直接在预处理出的数据里查询即可。这样子时间复杂度就是 $\Theta(q2^k + 2^k3^{L-k})$ 的，当 $L=20$ 时在 $k=7$ 时取到最小值。

实现起来与上面所讲的略有不同，具体如下所述：

记一个二进制数 $i$ 与一个由 `0`、`1`、`?` 组成的字符串 $j$ 相似，当且仅当枚举 $j$ 中 `?` 的所有情况，其中有一种情况的二进制形式等于 $i$，例如 $(101)_2$ 与 `?0?` 是相似的，$(101)_2$ 与 `?1?` 则不是相似的。

我们将询问存储下来离线处理，先枚举 $2^k$ 种状态 $i$，然后根据 $i$ 预处理 $3^{L-k}$ 种状态，最后对于每个询问 $j$，如果 $j$ 的前 $k$ 位与 $i$ 是相似的，那么这一组询问的答案就加上 $j$ 的后 $L-k$ 位预处理出的答案。

现在剩下两个问题：
1. 如何快速判断一个二进制数 $i$ 与一个由 `0`、`1`、`?` 组成的字符串 $j$ 相似？
2. 如何预处理后 $3^{L-k}$ 种状态？

对于第一个问题，我们考虑先把 $j$ 中的问号当作 `1`，然后将 $j$ 转换为二进制形式（记为 $f$），我们再把 $j$ 中的问号当作 `0`，其他当作 `1`，将 $j$ 转换为二进制形式（记为 $g$），如果 $(f \oplus i)\ \text{AND}\ g$ 的值为 $0$ 则 $i$ 与 $j$ 相似（其中 $\oplus$ 为按位异或运算，$\text{AND}$ 为按位与运算）。

对于第二个问题，我们每次将状态中的一个 `?` 分别替换成 `0` 和 `1` 计算答案再加起来，可以通过记搜或递推实现。

代码如下：
```cpp
/*
    I will never forget it.
*/
 
// 392699
 
#include <bits/stdc++.h>

#define reg register

using namespace std;

#define getchar() (__S == __T && (__T = (__S = __B) + fread(__B, 1, 1 << 23, stdin), __S == __T) ? EOF : *__S++)
#define putchar(c) (_P == _Q && (fwrite(_O, 1, 1 << 23, stdout), _P = _O), *_P++ = c)

char __B[1 << 23], *__S = __B, *__T = __B;
char _O[1 << 23], *_P = _O, *_Q = _O + (1 << 23);
 
template <class T> inline void fr(reg T &a, reg bool f = 0, reg char ch = getchar()) {
    for (a = 0; ch < '0' || ch > '9'; ch = getchar()) ch == '-' ? f = 1 : 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) a = a * 10 + ch - '0';
    a = f ? -a : a;
}

template <class T> inline void fw(reg T x) {
    reg int tot = 0;
    reg char TMP[20];
    if (x == 0) return (void)(putchar('0'));
    if (x < 0) putchar('-'), x = -x;
    while (x) TMP[++tot] = x % 10 + '0', x /= 10;
    for (; tot; tot--) putchar(TMP[tot]);
}
 
const int N = 20, M = 1e6, K = 7, L = 20 - K, F = (1 << K) - 1;
 
int n, q, o2, o, a[(1 << N) + 10], ans[M + 10], pow3[N + 10] = {1}, pow32[N + 10] = {2};
int d[M + 10], cc[M + 10], bbb[M + 10], aaaa[1594323 + 10];
int lb[1594323 + 10], ts[1594323 + 10], td[(1 << N) + 10];
char str[N + 10];
 
int dfs(reg int x) {
    reg int t = x - o;
    if (aaaa[t] != -1) return aaaa[t];
    if (lb[t] == -1) return aaaa[t] = a[ts[t] + o2];
    return aaaa[t] = dfs(x - pow3[lb[t]]) + dfs(x - pow32[lb[t]]);
}

inline void getS() {
    reg char ch = getchar();
    reg int tot = 0;
    while (ch == '\n' || ch == ' ') ch = getchar();
    while (ch != '\n' && ch != ' ' && ch != EOF) str[++tot] = ch, ch = getchar();
}

struct OI {
    int RP, score;
} CSPS2021, NOIP2021;
 
int main() {
    CSPS2021.RP++, CSPS2021.score++, NOIP2021.RP++, NOIP2021.score++, 392699;
    memset(lb, -1, sizeof(lb));
    for (reg int i = 0; i < 1594323; i++) i % 3 == 2 ? lb[i] = 0 : ~lb[i / 3] ? lb[i] = lb[i / 3] + 1 : 0;
    for (reg int i = 0; i < 1594323; i++) ts[i] = ts[i / 3] << 1 | i % 3, td[ts[i]] = i;
    fr(n), fr(q);
    int n2 = 1 << n;
    for (reg int i = 0; i < n2; i++) a[i] = getchar() - '0';
    for (reg int i = 1; i <= N; i++) pow3[i] = pow3[i - 1] * 3, pow32[i] = pow3[i] * 2;
    if (n <= L) {
        memset(aaaa, -1, sizeof(aaaa));
        for (int i = 0; i < pow3[n]; i++) dfs(i);
        for (int i = 1; i <= q; i++) {
            getS();
            int k = 0;
            for (int j = 1; j <= n; j++) {
                if (str[j] == '?') k = k * 3 + 2;
                else k = k * 3 + str[j] - '0';
            }
            fw(aaaa[k]), putchar('\n');
        }
        return fwrite(_O, 1, _P - _O, stdout), 0;
    }
    for (reg int i = 1; i <= q; i++) {
        getS(), cc[i] = F;
        for (reg int j = 1; j <= K; j++) {
            int k = str[j] == '0' ? 0 : 1;
            d[i] = d[i] * 2 + k;
            if (str[j] == '?') cc[i] = cc[i] ^ (1 << (K - j));
        }
        for (reg int j = K + 1; j <= n; j++) {
            int k;
            if (str[j] == '?') k = 2;
            else k = str[j] - '0';
            bbb[i] = bbb[i] * 3 + k;
        }
    }
    int awsl = 1 << K;
    for (reg int i = 0; i < awsl; i++) {
        o2 = i << (n - K), o = td[i] * pow3[n - K];
        memset(aaaa, -1, sizeof(aaaa));
        for (reg int j = 0; j < pow3[n - K]; j++) dfs(o + j);
        for (reg int j = 1; j <= q; j++)
            if (((d[j] ^ i) & cc[j]) == 0) ans[j] += aaaa[bbb[j]];
    }
    for (reg int i = 1; i <= q; i++) fw(ans[i]), putchar('\n');
    return fwrite(_O, 1, _P - _O, stdout), 0;
}

---

## 作者：封禁用户 (赞：9)

看到某管理大大的题解后：

![](https://i.loli.net/2018/10/29/5bd644bb4f0ba.gif)

但是管理的题解一般都需要细品才可以品出来个味儿。身为学习团团长，我要写一篇更容易蒟蒻理解的题解。

题目题面不说了，现在讲正式。如果我们死搜的话，时间复杂度 $O(q 2^L)$，但是你觉得 $10^{12}$ 的计算次数是在宽容计算机吗。。。而如果纯预处理的话，预处理所有可能出现的问题，所以空间复杂度 $O(3^L)$，足以达到出题人的上限。。。

借鉴到高维前缀和和高维后缀和的思路，我们可以利用它们来对问题进行优化，前提是我们要知道什么是高维前后缀和。

**前缀和**

顾名思义，就是一个数列上前面一段数的和。

**后缀和**

就是数列上后面一段数的和。

**二维前缀和**

就是在二维上的前缀和，只不过不仅仅是一段。例如如果把数组画成一个矩阵，位置在 $a$ 和 $b$ 的前缀和就是第一行第一列到第 $a$ 行第 $b$ 列的一个长方形里数字的和。

**二维后缀和**

就是第 $a$ 行第 $b$ 列到最右下角的格子的长方形里的数字的和。

**三维前缀和**

把三维数组想成一个长方体，那么位置在 $a,b,c$ 的三维前缀和就是第一层第一行第一列到第 $a$ 层第 $b$ 行第 $c$ 列的长方体内数字的和。

**三维后缀和&......&高维前缀和&高维后缀和**

现在大家知道了吧。

设这里每个维度表示的是毒蛇编号二进制上的每一个位，那么维度数就是 $n$ 。其中高位前缀和是在一个位置上前面毒蛇毒性的前缀，后缀和同理。那么我们可以通过以下方法求出清单中符合条件的毒蛇的毒性和（设 $a,b,c$ 分别表示清单中 $0,1,?$ 的个数）：

- 死算，把所有 $?$ 代换成任何字符，将值加起来，时间复杂度 $O(2^c)$。

- 在 $0$ 上巧算，先把所有 $0$ 换成 $?$，这样清单就会成为一个仅由 $1$ 和 $?$ 构成的字符串，可以使用高维后缀和进行计算。然后使用容斥原理依次排除原来是 $0$ 被改成 $?$ 多出来的 $1$ 的贡献即可。时间复杂度是容斥原理的时间复杂度，为 $O(2^a)$。

- 在 $1$ 上巧算，同理，使用前缀和进行容斥原理。时间 $O(2^b)$。

现在可以直观的看到，以上三种策略按照 $a,b,c$ 的大小选择一个最优的方案，将时间复杂度开下三次根。总共时间复杂度 $O(q2^{\frac{L}{3}})$，当然得加上 $O(L2^L)$ 的预处理前后缀和时间。

现在是~~抄~~代码时间，如果预处理部分不懂可以直接使用。

```
#include<bits/stdc++.h>
#define mxt 1048576
using namespace std;

int n,q,mxn,a[mxt],b[mxt],c[mxt];
char str[mxt],fk[25];

int dfs0(int now,int val){//0上巧算
	if(now==n){
		return c[val];
	}
	if(fk[now]=='0'){
		return dfs0(now+1,val)-dfs0(now+1,val+(1<<n-now-1));
	}
	return dfs0(now+1,val);
}

int dfs1(int now,int val){//1上巧算
	if(now==n){
		return b[val];
	}
	if(fk[now]=='1'){
		return dfs1(now+1,val)-dfs1(now+1,val-(1<<n-now-1));
	}
	return dfs1(now+1,val);
}

int dfsq(int now,int val){//死算
	if(now==n){
		return a[val];
	}
	if(fk[now]=='?'){
		return dfsq(now+1,val)+dfsq(now+1,val+(1<<n-now-1));
	}
	return dfsq(now+1,val);
}

int main(){
//	以下是预处理时间，若有不懂可以直接使用
	cin>>n>>q;
	scanf("%s",str);
	mxn=1<<n;
	for(int o=0;o<mxn;o++){
		a[o]=b[o]=c[o]=str[o]-48;
	}
	for(int i=1;i<mxn;i*=2){
		for(int j=0;j<mxn;j+=(i<<1)){
			for(int k=0;k<i;k++){
				b[i+j+k]+=b[j+k];
			}
		}
	}
	for(int i=1;i<mxn;i*=2) {
		for(int j=0;j<mxn;j+=(i<<1)) {
			for(int k=0;k<i;k++){
				c[j+k]+=c[i+j+k];
			}
		}
	}
//	以上就是预处理时间
	while(q--){
		scanf("%s",fk);
		int A=0,B=0,C=0,q0=0,q1=0;
		for(int i=0;i<n;i++){
			q0*=2,q1=q1*2+1;
			if(fk[i]=='0'){
				A++;
				q1--;
			}
			if(fk[i]=='1'){
				B++;
				q0++;
			}
			if(fk[i]=='?'){
				C++;
			}
		}
//      以下是选择最优策略时间
		if(A<=min(B,C)){
			printf("%d\n",dfs0(0,q0));
		}
		else if(B<=min(A,C)){
			printf("%d\n",dfs1(0,q1));
		}
		else{
			printf("%d\n",dfsq(0,q0));
		}
//      以上就是选择最优策略时间
	}
	return 0;
}
```

撰文不易，请一箭三连666！然后呢，抄我题解的这辈子跟你没完。

---

## 作者：FjswYuzu (赞：4)

思维定势属于是，怎么又被 $2^L,Q$ 之类的东西搞乱了啊。

首先根据鸽巢原理，一个询问中出现次数最小的字符出现次数最多是 $\lfloor \frac{L}{3} \rfloor$ 嘛，然后分类考虑：

- 如果这个字符是 `?`：那很好办，暴力枚举 `?` 分别代表什么就好了；   
- 否则，
  - 如果这个字符是 $0$：我们将 $0$ 看作这一位是 `?` 的答案减去这一位是 $1$ 的答案；    
  - 如果这个字符是 $1$：跟上面的差不多。

现在构建出一个大致的框架，我们思考出现次数最少的字符是 $0$ 怎么做。

考虑容斥，答案就是没有 $0$ 转成 $1$ 的方案数，减去有一个 $0$ 转成 $1$ 的方案数，加上有两个 $0$ 转成 $1$ 的方案数……容易发现枚举哪些 $0$ 变成了 $1$ 的时间复杂度是 $O(2^{p})$（其中 $p$ 为 $0$ 的个数）。

然后现在的问题是，我们确定了一些位置是 $1$，另外一些位置可以随便填的答案。记确定的位置的状态为 $S$，我们要求的就是编号为 $S$ 的超集的蛇毒性和。高维前缀和就可以做到 $O(1) \times O(2^{p}) = O(2^{p})$。

最后是出现次数最少的字符是 $1$ 怎么做。沿用上面的方法变成一个求子集和的问题，也可以用高维前缀和来处理。

具体实现可以采用 FMT/FWT 实现，代码里用的是 FWT。

```cpp
#include<bits/stdc++.h>
using namespace std;
int l,q;
void FWT_or(int *f){for(int o=2,k=1;o<=(1<<l);o<<=1,k<<=1)	for(int i=0;i<(1<<l);i+=o)	for(int j=0;j<k;++j)	f[i+j+k]+=f[i+j];}
void FWT_and(int *f){for(int o=2,k=1;o<=(1<<l);o<<=1,k<<=1)	for(int i=0;i<(1<<l);i+=o)	for(int j=0;j<k;++j)	f[i+j]+=f[i+j+k];}
int f[(1<<20)+5],g[(1<<20)+5],a[(1<<20)+5];
char s[(1<<20)+5],snk[25];
int cq[25],c0[25],c1[25],pq,p0,p1;
int dfs(int S,int p)
{
	if(p==pq)	return a[S];
	return dfs(S,p+1)+dfs(S|(1<<cq[p]),p+1);
}
int dfs0(int S,int p)
{
	if(p==p0)	return g[S];
	return dfs0(S,p+1)-dfs0(S|(1<<c0[p]),p+1);
}
int dfs1(int S,int p)
{
	if(p==p1)	return f[S];
	return dfs1(S|(1<<c1[p]),p+1)-dfs1(S,p+1);
}
int main(){
	scanf("%d %d",&l,&q);
	scanf("%s",s);
	for(int i=0;i<(1<<l);++i)	f[i]=g[i]=a[i]=(s[i]-'0');
	FWT_or(f),FWT_and(g);
	while(q-->0)
	{
		scanf("%s",snk);
		reverse(snk,snk+l);
		pq=p0=p1=0;
		int S0=0,S1=0;
		for(int i=0;i<l;++i)
		{
			if(snk[i]=='?')	cq[pq++]=i,S0|=(1<<i);
			if(snk[i]=='0')	c0[p0++]=i;
			if(snk[i]=='1')	c1[p1++]=i,S1|=(1<<i);
		}
		int st=min({pq,p0,p1}),ans;
		if(st==pq)	ans=dfs(S1,0);
		else if(st==p0)	ans=dfs0(S1,0);
		else	ans=dfs1(S0,0);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：NOI_Winner (赞：3)

先考虑暴力做法，我们枚举询问字符串所有可能的情况，直接统计答案。这种做法的时间复杂度为 $O(Q\cdot2^L)$ 。

考虑如何优化，注意到 $\texttt{0,1,?}$ 三种字符出现次数最少的最多只有 $\frac{n}{3}$ 个，因此我们可以对三种可能的最少的字符分别用不同方式处理。

1. 最少的字符为 $\texttt{?}$ ，直接用暴力方法即可。

2. 最少的字符为 $\texttt{1}$ ，我们将编号的每一位作为一个维度，预处理高维前缀和。查询时将 $\texttt{?}$ 的位置改为 $\texttt{1}$ ，并对 $\texttt{1}$ 的位置应用容斥原理即可。

3. 最少的字符为 $\texttt{0}$ ，同理，我们预处理高维后缀和，同样处理就行了。

时间复杂度降为 $O(Q\cdot2^\frac{n}{3})$ 。

具体实现方式请见代码：

```cpp
#include <iostream>

using namespace std;

const int maxl = 20, maxn = 1 << maxl;
int val[maxn + 5], s1[maxn + 5], s2[maxn + 5];
char str[maxn + 5];

void fwt1(int* a, int k)           //  预处理高维前缀和 
{
	if (!k)
		return;
	
	fwt1(a, k - 1); fwt1(a + (1 << (k - 1)), k - 1);
	for (int i = 0; i < 1 << (k - 1); ++i)
		a[i + (1 << (k - 1))] += a[i];
}

void fwt2(int* a, int k)           //  预处理高维后缀和 
{
	if (!k)
		return;
	
	fwt2(a, k - 1); fwt2(a + (1 << (k - 1)), k - 1);
	for (int i = 0; i < 1 << (k - 1); ++i)
		a[i] += a[i + (1 << (k - 1))];
}

inline int f(int x)
{
	return (x & 1) ? -1 : 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int k, q; cin >> k >> q;
	for (int i = 0; i < 1 << k; ++i)
	{
		char ch; cin >> ch;
		val[i] = ch - '0';
	}
	for (int i = 0; i < 1 << k; ++i)
		s1[i] = s2[i] = val[i];
	fwt1(s1, k); fwt2(s2, k);           //  预处理 
	
	while (q--)
	{
		cin >> str;
		int cnt0 = 0, cnt1 = 0;
		for (int i = 0; i < k; ++i)
			if ('0' == str[i])
				++cnt0;
			else if ('1' == str[i])
				++cnt1;
		if (k - cnt0 - cnt1 <= cnt0 && k - cnt0 - cnt1 <= cnt1)
		{
			int v1 = 0, v2 = 0;        //  最少的是 ? 
			for (int i = 0; i < k; ++i)
			{
				v1 <<= 1; v2 <<= 1;
				if ('?' == str[i])
					v2 |= 1;
				else if ('1' == str[i])
					v1 |= 1;
			}
			int ans = val[v1];
			for (int s = v2; s; s = (s - 1) & v2)
				ans += val[s | v1];    //  直接统计 
			cout << ans << endl;
		}
		else if (cnt1 <= cnt0)
		{
			int v1 = 0, v2 = 0;      //  最少的是 1 
			for (int i = 0; i < k; ++i)
			{
				v1 <<= 1; v2 <<= 1;
				if ('?' == str[i])
					v1 |= 1;
				else if ('1' == str[i]) 
					v2 |= 1;
			}
			int c = __builtin_popcount(v2), ans = s1[v1] * f(c);
			for (int s = v2; s; s = (s - 1) & v2)
				ans += s1[s | v1] * f(c - __builtin_popcount(s));  // 容斥原理
			cout << ans << endl;
		}
		else
		{
			int v1 = 0, v2 = 0;     // 最少的是 0 
			for (int i = 0; i < k; ++i)
			{
				v1 <<= 1; v2 <<= 1;
				if ('0' == str[i])
					v2 |= 1;
				else if ('1' == str[i])
					v1 |= 1;
			}
			int ans = s2[v1];
			for (int s = v2; s; s = (s - 1) & v2)
				ans += s2[s | v1] * f(__builtin_popcount(s));  //  容斥原理 
			cout << ans << endl;
		}
	}
	
	return 0;
}
```

---

## 作者：Mr_罗 (赞：3)


# 题解 [P7670 [JOI2018] Snake Escaping](https://www.luogu.com.cn/problem/P7670)

[TOC]

## Part -1

update on 2024/1/30 进行了一下细节的微调。（$\times2$，辛苦了管理员）

update on 2024/2/5 改掉了两个 bug。

## Part 0

~~每一道黑题的通过都值得庆祝【撒花】~~

提供一种比题解区目前所有题解都简便的高维前缀和写法，并解释一些细节。

如果只想看本题题解，请跳过 Part 2，这个子目是介绍高维前缀和的。

## Part 1

首先发现虽然 $\mathcal{O}(q2^n)$ 会炸，但 $\mathcal{O}(q2^{n/3})$ 可以过，于是~~一点也不自然地~~考虑抽屉原理（也可以叫鸽巢原理~~咕咕咕~~），即三种字符出现次数最少的那个不会出现超过 $\dfrac{n}{3}$ 次。

然后就像众大佬说的那样，设 $a,b,c$ 分别为 $T_d$ 中字符 `0,1,?` 的个数，讨论其中的最小值：

- 若 $c$ 最小，直接暴力枚举每个 `?` 处填什么（`0` 或 `1`），$\mathcal{O}(2^c)$。
- 若 $a$ 最小，考虑容斥：将所有 `0` 变成 `1` 或 `?`，容斥掉 `0` 变成 `1` 的贡献。
- 若 $b$ 最小，类似于上一种情况处理。

现在问题变成如何求 $a=0$ 或 $b=0$ 的情况以及如何容斥。

不过，有一个前置知识亟待解决。

## Part 2 高维前缀和

粽锁粥汁，前缀和有容斥的写法，例如：

二维：

```cpp
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= n; j++)
        s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
        // 容斥指这一坨
}
```

三维：

```cpp
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= n; j++)
    {
        for (int k = 1; k <= n; k++)
            s[i][j][k] = s[i-1][j][k] + s[i][j-1][k] + s[i][j][k-1]
                       - s[i-1][j-1][k] - s[i-1][j][k-1] - s[i][j-1][k-1]
                       + s[i-1][j-1][k-1] + a[i][j][k];
            // 容斥指这一大坨
    }
}
```

然而这样肥肠不优雅。

考虑另一种思路：一次把一个维度累加起来，下一次累加下一个维度，这样就把之前的维度都累加起来了；如此重复，就可以统计出来了。

~~说不明白，请自行感悟。~~

于是我们可以这样写三维前缀和：

```cpp
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= n; j++)
    {
        for (int k = 1; k <= n; k++)
            s[i][j][k] = s[i][j][k - 1] + a[i][j][k];
    }
}
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= n; j++)
    {
        for (int k = 1; k <= n; k++)
            s[i][j][k] += s[i][j - 1][k];
    }
}
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= n; j++)
    {
        for (int k = 1; k <= n; k++)
            s[i][j][k] += s[i - 1][j][k];
    }
}
```

更进一步：对于如下所定义的子集和
$$\operatorname{sum}(S)=\sum_{T\subseteq S}\operatorname{val}(T)$$

可以当作 $|S|$ 维前缀和，每一维度有两个可能的取值（对应 $S$ 中维度对应的值取或不取）。利用状压，可以这么写：

```cpp
for (int i = 1; i <= n; i++)
{
    for (int st = 0; st < (1 << n); st++)
    {
        if ((st >> (i - 1)) & 1)
            s[st] += s[st ^ (1 << (i - 1))];
    }
}
```

就很快乐。

## Part 3

回来解决原题剩下的三个问题。

### 处理 $a=0$ 的情况

现在剩下了一堆 `1` 和 `?`，考虑到 `?` 可以填 `0` 或 `1`，也就是说 `?` 的贡献为 `0` 的贡献加上 `1` 的贡献。

注意到可以把这个贡献当成一个后缀和，具体来说把 `?` 当作 `0` 求高维后缀和，这样就自然包括了 `?` 为 `0` 或 `1` 的情况。

### 处理 $b=0$ 的情况

类似，把 `?` 换成 `1` 求高维前缀和。

### 容斥

首先举个例子：把 $3$ 个 `0` 换成 `?` 或 `1`：

```
??? : 000 001 010 011 100 101 110 111
??1 : 001 011 101 111
?1? : 010 011 110 111
...
111 : 111
```

于是贡献是：

```
??? + ??1 + ?1? + 1?? - ?11 - 1?1 - 11? + 111
```

（不信自己试试）

其实本质就是
$$\textsf{全不选}=\textsf{全部随便}-\textsf{仅强制选一个}+\textsf{仅强制选两个}-\cdots$$

~~反正容斥是说不明白的，自己领悟叭~~

## Part 4

正如那句名言：

$$\mathcal{T}\textsf{alk is cheap, }\mathcal{SHOW}\ \mathcal{ME}\textsf{ the }\Huge\mathscr{CODE}$$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 25, K = (1 << 20) + 10;
int n, m, ans;
char s[K], c[N];
int sp[K], ss[K];
vector<int> v0, v1, v2;

void init()
{
    for (int i = 0; i < (1 << n); i++)
        sp[i] = ss[i] = s[i] - '0';
    for (int i = 0; i < n; i++)
    {
        for (int st = 0; st < (1 << n); st++)
        {
            if ((st >> i) & 1)
                sp[st] += sp[st ^ (1 << i)];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int st = 0; st < (1 << n); st++)
        {
            if (!((st >> i) & 1))
                ss[st] += ss[st ^ (1 << i)];
        }
    }
    #ifdef cooluo
    for (int st = 0; st < (1 << n); st++)
        printf ("init: %d: %d %d\n", st, sp[st], ss[st]);
    #endif
}

int main()
{
    // freopen ("Test.in", "r", stdin);
    // freopen ("Test.out", "w", stdout);
    
    scanf ("%d%d", &n, &m);
    scanf ("%s", s);
    init();
    while (m--)
    {
        v0.clear();
        v1.clear();
        v2.clear();
        scanf ("%s", c);
        reverse (c, c + n);
        int bs = 0;
        for (int i = 0; i < n; i++)
        {
            if (c[i] == '0')
                v0.push_back (i);
            else if (c[i] == '1')
            {
                v1.push_back (i);
                bs |= (1 << i);
            }
            else
                v2.push_back (i);
        }
        int c0 = v0.size();
        int c1 = v1.size();
        int c2 = v2.size();
        ans = 0;
        #ifdef cooluo
        printf (" - %d %d %d\n", c0, c1, c2);
        #endif
        int mn = min (min (c0, c1), c2);
        if (c2 == mn)
        {
            for (int st = 0; st < (1 << c2); st++)
            {
                int ba = bs;
                for (int i = 0; i < c2; i++)
                    ba |= (((st >> i) & 1) << v2[i]);
                ans += s[ba] - '0';
                #ifdef cooluo
                printf (" | %d: %d\n", st, ba);
                #endif
            }
        }
        else if (c0 == mn)
        {
            for (int st = 0; st < (1 << c0); st++)
            {
                int ba = bs;
                int op = 1;
                for (int i = 0; i < c0; i++)
                {
                    int bt = ((st >> i) & 1);
                    ba |= (bt << v0[i]);
                    op ^= bt;
                }
                if (op)
                    ans += ss[ba];
                else
                    ans -= ss[ba];
            }
        }
        else
        {
            bs = 0;
            for (int i = 0; i < n; i++)
                bs |= ((c[i] == '?') << i);
            #ifdef cooluo
            printf (" ~ %d\n", bs);
            #endif
            for (int st = 0; st < (1 << c1); st++)
            {
                int ba = bs;
                int op = 1;
                for (int i = 0; i < c1; i++)
                {
                    int bt = ((st >> i) & 1);
                    ba |= (bt << v1[i]);
                    op ^= (bt ^ 1);
                }
                if (op)
                    ans += sp[ba];
                else
                    ans -= sp[ba];
            }
        }
        printf ("%d\n", ans);
    }
    return 0;
}
/*

2^{#?} : ? -> 0/1
2^{#0} : 0 -> ? => (?) - (1)
2^{#1} : 1 -> ? => (?) - (0)

00:
- 11
| 11
- 1?
| 10
| 11
- ?1
| 01
| 11
- ??
| 00
| 01
| 10
| 11

??-?1-1?+11

000:
- 111
| 111
- 11?
| 110 111
- 1?1
| 101 111
- ?11
| 011 111
- 1??
| 100 101 110 111
- ?1?
| 010 011 110 111
- ??1
| 001 011 101 111
- ???
| 000 001 010 011 100 101 110 111

+ 000 001 010 011 100 101 110 111
-     001 010 011 100 101 110 111
- 011 111 101 110 111
+ 011 111 101 110 111
+ 111
- 111

*/
```

## Part 5 闲话

刚刚 [Galois_Field_1048576](https://www.luogu.com.cn/user/360265) 大佬指出这是 FWT-OR，反正我也不懂 ╮(╯▽╰)╭


---

## 作者：wYYSZLwSSY (赞：2)

~~好像不是很难，是我降智了。~~

## 题意
给定 $2^L$ 个数表示 $0$ 到 $2^L-1$ 的权值。

$q$ 次询问，每次给定一个由 $0,1,?$ 组成的长度为 $L$ 的字符串，$?$ 可以表示为 $1$ 或 $0$，求所有二进制表示下和字符串匹配的数的权值之和。
  
$1\leq L\leq 20$，$1 \leq q \leq 10^6$。

## 题解
前三个 sub 可以 dp 转移得到每一个字符串对应的答案，时间复杂度是 $3^n$ 乘上什么东西，下面直接说正解。

### 基本思路
思考，如果询问串中的 $?$ 很少，显然可以暴力地将每一个 $?$ 变成 $1$ 或 $0$，然后计算答案，假设 $?$ 有 $a$ 个，复杂度是 $O(q2^a)$。

但显然 $?$ 不可能总是很少。反过来，如果 $?$ 很多，那么 $1$ 和 $0$ 的个数就不会很多。我们可以类似的想，能不能将 $1$ 或 $0$ 替换成 $0$ 或 $1$ 和 $?$ 呢？似乎是可以的。难点有两个，第一是替换后如何 $O(1)$ 计算当前的答案，第二是替换后如何重复计数。

先看第一个，比如我们要求 $f_{??000}$（表示 `??000` 的答案，后面一样），实际就是求 $v_{00000}+v_{10000}+v_{01000}+v_{11000}$。如果我们把 $?$ 看作 $1$，那么就是求所有被“偏序”的 $v$ 的和。这实际就是求高维前缀和，可以使用求高维前缀和的方式 $O(L2^L)$ 求出。仅含 $1$ 和 $?$ 的也类似。

再看第二个，假设我们要求 $f_{??11000}$，显然它等于 $f_{????000}-f_{???0000}-f_{??0?000}+f_{??00000}$，不难发现这是一个容斥的过程。

至此，我们可以在 $O(2^a)$ 的时间内将某个出现次数为 $a$ 的字符替换为其他字符求解答案。假设 $?,1,0$ 的出现次数分别为 $a,b,c$，选择出现次数最少的替换，可以每次询问做到 $O(2^{\min(a,b,c)})$。由于有 $a+b+c=L$，所以 $\min(a,b,c) \leq \frac{L}{3}$。总的时间复杂度是 $O(L2^L+q2^\frac{L}{3})$。可以通过本题。

### 一些实现细节
容斥应该不难，这里主要说高维前缀和的预处理。

假设我们要求 $f_{??000}$，一个直观的思路是求 $f_{?0000}+f_{0?000}-f_{00000}$，也就是做一个简单的容斥。

但这个复杂度显然太高。事实上，我们可以按位加。按照上面的例子，就是将 $f_{?0000}$ 加入时（计算到第 $4$ 位）还不算 $f_{00000}$ 的答案。这样就避免了容斥。

具体地，我们从低到高枚举转移的位置 $k$，然后枚举状态 $s$，将 $f_s$ 加到 $f_{s+(1<<k)}$ 上（以求仅含 $?,0$ 的为例，注意 $s$ 第 $k$ 位必须为 $0$）。

预处理时间复杂度 $O(L2^L)$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int l,q;
int ans;
string s;
int a[1300006];
int b[1300006];
int c[1300006];
void dfsq(int t,int i){
    if(t==l)return (void)(ans+=c[i]);
    if(s[t]!='1')dfsq(t+1,i);
    if(s[t]!='0')dfsq(t+1,i+(1<<t));
    return ;
}
void dfs0(int t,int i,int flag){
    if(t==l)return (void)(ans+=b[i]*flag);
    if(s[t]!='?')dfs0(t+1,i+(1<<t),flag);
    if(s[t]!='1')dfs0(t+1,i,-flag);
    return ;
}
void dfs1(int t,int i,int flag){
    if(t==l)return (void)(ans+=a[i]*flag);
    if(s[t]!='?')dfs1(t+1,i,flag);
    if(s[t]!='0')dfs1(t+1,i+(1<<t),-flag);
    return ;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // freopen("1.in","r",stdin);
    cin>>l>>q>>s;
    for(int i=0;i<(1<<l);++i)a[i]=b[i]=c[i]=s[i]-'0';
    for(int i=1;i<(1<<l);i<<=1){
        for(int s=0;s<(1<<l);++s){
            if(s&i)continue;//注意这个
            a[i+s]+=a[s],b[s]+=b[i+s];
        }
    }
    while(q--){
        cin>>s;
        reverse(s.begin(),s.end());//
        int cnt0=0,cnt1=0,cntq=0;
        for(int i=0;i<l;++i){
            if(s[i]=='0')++cnt0;
            else if(s[i]=='1')++cnt1;
            else ++cntq;
        }
        ans=0;
        if(cntq<=l/3)dfsq(0,0);
        else if(cnt0<=l/3)dfs0(0,0,1);//这里其实不能直接传 1，有时是 -1，不过可以最后输出时判一下。
        else dfs1(0,0,1);//同上
        cout<<(ans>0?ans:-ans)<<'\n';//输出时候判定
    }
    return 0;
}
```

---

## 作者：Arghariza (赞：2)

好神奇的做法，我称其为猪猪（猪笼原理）分治。

记 $0,1,?$ 的个数分别为 $a,b,c$。有一个显然的 $O(2^c)$ 做法，对每个 $?$ 枚举其为 $0/1$ 即可。

然后我们考虑只有 $?,1$ 的情况，把所有 $?$ 当成 $0$，答案就是一个超集和；同理，对于只有 $?,0$ 的情况，把所有 $?$ 当成 $1$，答案就是一个子集和。两者都可以用 FWT 预处理出来。

于是我们考虑把 $0$ 和 $1$ 的其中一个用 $?$ 来替换。比方说 $0$ 换成 $?$，根据容斥，应该减去 $?$ 为 $1$ 的情况。这同样可以轻易地解决，于是我们得到了 $O(2^a)$ 和 $O(2^b)$ 的做法。

综合一下，如果我们**每次只选 $a,b,c$ 中较小的做法**来做，复杂度为 $O(2^{\min\{a,b,c\}})$。根据猪笼（抽屉）原理，$\min\{a,b,c\}\le \left\lfloor\dfrac{L}{3}\right\rfloor$，所以总复杂度为 $O(n2^n+q2^{L/3})$，能过。

```cpp
int dfs0(int st, int dep) {
	if (dep == n) return g[st];
	if (s[dep] == '0') return dfs0(st << 1, dep + 1) - dfs0(st << 1 | 1, dep + 1);
	if (s[dep] == '?') return dfs0(st << 1, dep + 1);
	return dfs0(st << 1 | 1, dep + 1);
}

int dfs1(int st, int dep) {
	if (dep == n) return f[st];
	if (s[dep] == '1') return dfs1(st << 1 | 1, dep + 1) - dfs1(st << 1, dep + 1);
	if (s[dep] == '?') return dfs1(st << 1 | 1, dep + 1);
	return dfs1(st << 1, dep + 1);
}

int dfs2(int st, int dep) {
	if (dep == n) return a[st];
	if (s[dep] == '?') return dfs2(st << 1, dep + 1) + dfs2(st << 1 | 1, dep + 1);
	return dfs2(st << 1 | (s[dep] - '0'), dep + 1);
}

int main() {
	n = read(), q = read(), S = (1 << n);
	for (int i = 0; i < S; i++) scanf("%1d", &a[i]), f[i] = g[i] = a[i];
	for (int o = 2, k = 1; o <= S; o <<= 1, k <<= 1)
		for (int i = 0; i < S; i += o)
			for (int j = 0; j < k; j++)
				f[i + j + k] += f[i + j], g[i + j] += g[i + j + k];
	while (q--) {
		scanf("%s", s);
		int a = 0, b = 0, c = 0;
		for (int i = 0; i < n; i++) 
			a += (s[i] == '0'), b += (s[i] == '1'), c += (s[i] == '?');
		if (c <= n / 3) write(dfs2(0, 0));
		else if (a <= n / 3) write(dfs0(0, 0));
		else write(dfs1(0, 0));
		puts("");
	}
	return 0;
}
```

---

## 作者：Aurie (赞：0)

显然有一种方法，可以暴力枚举“?”是“$1$”还是“$0$”，然后统计上每一种结果，复杂度：$O(q2^{\operatorname{number\_of“?”}(S)})=O(q2^l)$。

但还有一种方法，预处理高位前缀和。对于一次只有“$0$”和“?”的询问，将“?”改为“$1$”，查询该位置的前缀和即可。如果同时有“$0$”、“$1$”、“?”可以把“$1$”当作“?”统计结果，此时多统计了很多为“$0$”的情况，通过容斥原理把“$0$”的情况都减去即可，复杂度：$O(l2^l+q2^{\operatorname{builtin\_popcount}(S)})=O(l2^l+q2^l)$。

以此类推还有一种方法，预处理高维后缀和。把“$0$”当作“$?$”……第二种方法反过来即可，复杂度：$O(l2^l+q2^{\operatorname{builtin\_popcount}(\overline{S})})=O(l2^l+q2^l)$。

可以发现上面三种做法都通过不了这道题，怎么办呢？平衡一下它们。

显然有：

$$\min\{\operatorname{number\_of“?”}(S),\operatorname{builtin\_popcount}(S),\operatorname{builtin\_popcount}(\overline{S})\} \le \lfloor\dfrac{l}{3}\rfloor=6$$

哪个方法最小用哪种方法，复杂度：$O(l2^l+q2^{\lfloor\dfrac{l}{3}\rfloor})$。

代码（粘一个火车头跑飞快）：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace __FastIO
{
    static constexpr size_t BUFFER_SIZE = 1 << 18;
    struct InputHelper
    {
        char buf[BUFFER_SIZE];
        char *end, *cursor;
        bool ok;
        explicit InputHelper() : end(buf + BUFFER_SIZE), cursor(buf + BUFFER_SIZE), ok(true) {}
        static bool is_blank(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
        static bool is_endline(char c) { return c == '\n' || c == EOF; }
        static InputHelper &get_instance()
        {
            static InputHelper in;
            return in;
        }
        void next() { cursor++; }
        InputHelper &set_bad() { return ok = false, *this; }
        template <class T, typename BinaryOperation>
        InputHelper &fill_integer(T &res, BinaryOperation op)
        {
            if (!isdigit(*cursor))
                return set_bad();
            res = op(T(0), *cursor - '0');
            size_t len = 1;
            while (isdigit(*(cursor + len)))
                res = op(res * 10, *(cursor + len++) - '0');
            cursor += len;
            return *this;
        }
        template <size_t BlockSize>
        void reserve()
        {
            size_t a = end - cursor;
            if (a >= BlockSize)
                return;
            if (a > 0)
                memmove(buf, cursor, a);
            cursor = buf;
            size_t b = a + fread(buf + a, 1, BUFFER_SIZE - a, stdin);
            if (b < BUFFER_SIZE)
            {
                end = buf + b;
                *end = EOF;
            }
        }
        const char &getchar_checked() { return reserve<1>(), *cursor; }
        const char &getchar_unchecked() const { return *cursor; }
        template <class T, typename enable_if<is_same<T, __int128_t>::value | (is_signed<T>::value & is_integral<T>::value)>::type * = nullptr>
        InputHelper &operator>>(T &num)
        {
            while (is_blank(getchar_checked()))
                next();
            reserve<40>();
            if (getchar_unchecked() != '-')
                return fill_integer(num, plus<T>());
            next();
            return fill_integer(num, minus<T>());
        }
        template <class T, typename enable_if<is_same<T, __uint128_t>::value | (is_unsigned<T>::value & is_integral<T>::value)>::type * = nullptr>
        InputHelper &operator>>(T &num)
        {
            while (is_blank(getchar_checked()))
                next();
            reserve<40>();
            return fill_integer(num, plus<T>());
        }
        template <class T, typename enable_if<is_same<T, __float128>::value | is_floating_point<T>::value>::type * = nullptr>
        InputHelper &operator>>(T &num)
        {
            bool neg = false, integer = false, decimal = false;
            while (is_blank(getchar_checked()))
                next();
            reserve<50>();
            if (getchar_unchecked() == '-')
            {
                neg = true;
                next();
            }
            if (!isdigit(getchar_unchecked()) && getchar_unchecked() != '.')
                return set_bad();
            if (isdigit(getchar_unchecked()))
            {
                integer = true;
                num = getchar_unchecked() - '0';
                while (next(), isdigit(getchar_unchecked()))
                    num = num * 10 + (getchar_unchecked() - '0');
            }
            if (getchar_unchecked() == '.')
            {
                if (next(), isdigit(getchar_unchecked()))
                {
                    if (!integer)
                        num = 0;
                    decimal = true;
                    T unit = 0.1;
                    num += unit * (getchar_unchecked() - '0');
                    while (next(), isdigit(getchar_unchecked()))
                        num += (unit *= 0.1) * (getchar_unchecked() - '0');
                }
            }
            if (!integer && !decimal)
                return set_bad();
            if (neg)
                num = -num;
            return *this;
        }
        InputHelper &operator>>(char &c)
        {
            while (is_blank(getchar_checked()))
                next();
            if (getchar_checked() == EOF)
                return set_bad();
            c = getchar_checked(), next();
            return *this;
        }
        InputHelper &operator>>(string &s)
        {
            while (is_blank(getchar_checked()))
                next();
            if (getchar_checked() == EOF)
                return set_bad();
            s.clear();
            do
            {
                s += getchar_checked();
                next();
            } while (!is_blank(getchar_checked()) && getchar_checked() != EOF);
            return *this;
        }
        explicit operator bool() { return ok; }
    };
    struct OutputHelper
    {
        char buf[BUFFER_SIZE], temp_buf[50];
        char *end, *cursor, *temp_dot, *temp_cursor;
        uint64_t float_reserve, float_ratio;
        explicit OutputHelper() : end(buf + BUFFER_SIZE), cursor(buf), temp_cursor(temp_buf)
        {
            set_precision(6);
        }
        ~OutputHelper() { flush(); }
        OutputHelper &flush() { return write(), fflush(stdout), *this; }
        static OutputHelper &get_instance()
        {
            static OutputHelper out;
            return out;
        }
        void set_precision(size_t prec)
        {
            float_reserve = prec;
            float_ratio = uint64_t(pow(10, prec));
            temp_dot = temp_buf + prec;
        }
        void putchar(const char &c)
        {
            if (cursor == end)
                write();
            *cursor++ = c;
        }
        void write() { fwrite(buf, 1, cursor - buf, stdout), cursor = buf; }
        template <size_t BlockSize>
        void reserve()
        {
            size_t a = end - cursor;
            if (a >= BlockSize)
                return;
            write();
        }
        template <class T, typename enable_if<is_same<T, __int128_t>::value | (is_signed<T>::value & is_integral<T>::value)>::type * = nullptr>
        OutputHelper &operator<<(T res)
        {
            reserve<40>();
            size_t len = 0;
            if (res >= 0)
            {
                do
                {
                    *(cursor + len++) = '0' + res % 10;
                    res /= 10;
                } while (res);
            }
            else
            {
                putchar('-');
                do
                {
                    *(cursor + len++) = '0' - res % 10;
                    res /= 10;
                } while (res);
            }
            for (int i = 0, j = len - 1; i < j;)
            {
                swap(*(cursor + i++), *(cursor + j--));
            }
            cursor += len;
            return *this;
        }
        template <class T, typename enable_if<is_same<T, __uint128_t>::value | (is_unsigned<T>::value & is_integral<T>::value)>::type * = nullptr>
        OutputHelper &operator<<(T res)
        {
            reserve<40>();
            size_t len = 0;
            do
            {
                *(cursor + len++) = '0' + res % 10;
                res /= 10;
            } while (res);
            for (int i = 0, j = len - 1; i < j;)
            {
                swap(*(cursor + i++), *(cursor + j--));
            }
            cursor += len;
            return *this;
        }
        template <class T, typename enable_if<is_same<T, __float128>::value | is_floating_point<T>::value>::type * = nullptr>
        OutputHelper &operator<<(T res)
        {
            if (res < 0)
            {
                putchar('-');
                return *this << -res;
            }
            res *= float_ratio;
            uint64_t integer = res;
            if (res - integer >= 0.5 - 1e-10)
                integer++;
            do
            {
                *temp_cursor++ = '0' + integer % 10;
                integer /= 10;
            } while (integer);
            if (temp_cursor > temp_dot)
            {
                do
                {
                    putchar(*--temp_cursor);
                } while (temp_cursor > temp_dot);
                putchar('.');
            }
            else
            {
                putchar('0');
                putchar('.');
                for (int i = temp_dot - temp_cursor; i--;)
                {
                    putchar('0');
                }
            }
            do
            {
                putchar(*--temp_cursor);
            } while (temp_cursor > temp_buf);
            return *this;
        }
        OutputHelper &operator<<(const char &res)
        {
            putchar(res);
            return *this;
        }
        OutputHelper &operator<<(const char *res)
        {
            while (res && *res)
                putchar(*res++);
            return *this;
        }
        OutputHelper &operator<<(const string &res) { return *this << res.data(); }
    };
}
template <typename T>
inline void _db(T x) { cerr << " [" << x << "]"; }
template <typename T, typename... Args>
inline void _db(T x, Args... temps) { _db(x), _db(temps...); }
#define de(...) cerr << " " << __FUNCTION__ << "(): line " << __LINE__ << " >  " << #__VA_ARGS__ << " =", _db(__VA_ARGS__), cerr << endl
// #define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define cin __FastIO::InputHelper::get_instance()
#define cout __FastIO::OutputHelper::get_instance()
#define endl '\n'
#endif
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
int n, q, a[N], top, sum[N], fsum[N];
string s;

int main() {
    cin >> top >> q;
    n  = 1 << top;
    cin >> s;
    
    for (int i = 0; i < n; i++) fsum[i] = sum[i] = a[i] = s[i] - '0';
    for (int i = 0; i < top; i++) {
        for (int S = 0; S < n; S++) {
            if ((S >> i) & 1) sum[S] += sum[S ^ (1 << i)];
        }
    }
    for (int i = 0; i < top; i++) {
        for (int S = n - 1; S >= 0; S--) {
            if (!((S >> i) & 1)) fsum[S] += fsum[S ^ (1 << i)];
        }
    }
    while (q--) {
        cin >> s;
        int cnt = 0, cnt1 = 0, cnt0 = 0;
        for (int i = 0; i < top; i++) {
            cnt <<= 1; cnt1 <<= 1; cnt0 <<= 1;
            if (s[i] == '?') cnt |= 1;
            else if (s[i] == '0') cnt0 |= 1;
            else cnt1 |= 1;
        }
        int ans = 0, x = __builtin_popcount(cnt), y = __builtin_popcount(cnt1), z = __builtin_popcount(cnt0);
        if (x <= y && x <= z) {
            for (int S = cnt; ; S = (S - 1) & cnt) {
                ans += a[S | cnt1];
                if (S == 0) break;
            }
        } else if (y < x && y < z) {
            ans = sum[cnt |= cnt1];
            for (int S = cnt1; S; S = (S - 1) & cnt1) {
                ans += (__builtin_popcount(S) & 1 ? -1 : 1) * sum[~S & cnt];
            }
        } else {
            ans = fsum[cnt1];
            for (int S = cnt0; S; S = (S - 1) & cnt0) {
                ans += (__builtin_popcount(S) & 1 ? -1 : 1) * fsum[S |  cnt1];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：chenhouyuan (赞：0)

注意到 $L\le20$。

~~直接暴力。~~

直接暴力的时间复杂度是 $O(3^L)$ 的，显然不可接受，考虑如何优化。假如询问串的 $\texttt{0}$ 个数非常少，实际可以存储所有只由 $\texttt{1,?}$ 构成的串的答案 $f_s$，其中 $s$ 状压记录 $\texttt{1}$ 的位置。然后对 $\texttt{0}$ 进行容斥，具体的，先将询问串中的 $\texttt{0}$ 全部改为 $\texttt{?}$ 并记为 $s$，再枚举原串 $\texttt{0}$ 的位置，是 $\texttt{1}$ 则这位为 $1$，否则为 $0$，记为 $t$。记 $\left|t\right|$ 为 $t$ 中 $1$ 的个数，然后贡献为 $(-1)^{\left|t\right|}f_{s-t}$。这样就可以用高维前缀和做了。

同理，如果 $\texttt{1}$ 数量特别少，也可以类似做。如果 $\texttt{?}$ 数量特别少，直接暴力即可。综合三种算法，复杂度为 $O(Q2^\frac{L}{3}+L2^L)$。
##### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=21;
int L,Q,c0,c1,c2,ans,a[1<<N],b[1<<N],bj0[N],bj1[N],bj2[N],x1,x2;
char s[1050000],t[1050000];
void dfs(int x,int k){
	if(k==c2){
		ans+=s[x]-'0';
		return;
	}
	dfs(x,k+1);
	dfs(x|(1<<bj2[k]),k+1);
}
void dfs1(int x,int k,int f){
	if(k==c1){
		ans+=a[x]*f;
		return;
	}
	dfs1(x,k+1,-f);
	dfs1(x|(1<<bj1[k]),k+1,f);
}
void dfs0(int x,int k,int f){
	if(k==c0){
		ans+=b[x]*f;
		return;
	}
	dfs0(x,k+1,f);
	dfs0(x|(1<<bj0[k]),k+1,-f);
}
int main(){
	scanf("%d%d",&L,&Q);
	scanf("%s",s);
	for(int i=0;i<(1<<L);i++)a[i]=s[i]-'0';
	for(int i=0;i<L;i++){
		for(int j=0;j<(1<<L);j++){
			if((j>>i)&1)a[j]+=a[j^(1<<i)];
		}
	}
	for(int i=0;i<(1<<L);i++)b[i]=s[i]-'0';
	for(int i=0;i<L;i++){
		for(int j=0;j<(1<<L);j++){
			if(!((j>>i)&1))b[j]+=b[j^(1<<i)];
		}
	}
	while(Q--){
		scanf("%s",t);
		c0=0;
		c1=0;
		c2=0;
		x1=0;
		x2=0;
		for(int i=0;i<L;i++){
			if(t[i]=='0')bj0[c0++]=L-i-1;
			if(t[i]=='1'){
				bj1[c1++]=L-i-1;
				x1|=(1<<(L-i-1));
			}
			if(t[i]=='?'){
				bj2[c2++]=L-i-1;
				x2|=(1<<(L-i-1));
			}
		}
		ans=0;
		if(c0<7){
			dfs0(x1,0,1);
		}
		else if(c2<7){
			dfs(x1,0);
		}
		else{
			dfs1(x2,0,1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

黑色的双倍经验！[AT_joi2018ho_e](https://www.luogu.com.cn/problem/AT_joi2018ho_e) 

前置定义：$k_0$ 表示 $0$ 的数量，$k_1$ 表示 $1$ 的数量，$k_?$ 表示 $?$ 的数量。

前置知识：数据点分治，快速沃尔什变换（FWT）。

首先考虑一个非常 trival 的暴力，对于每一个 `?` 字符，将其暴力替换为 `0` 和 `1` 然后判断答案。因此获得了一个 $O(Q2^{k_?})$ 的暴力。

然后考虑其的一个子问题：若字符串中只含有 `0` 字符和 `?` 字符，那怎么做？考虑将该状态用二进制数表示，`0` 字符所对应的位置固定，`?` 字符可以对应 $0/1$。因此问题转化为给定固定集合求其子集的和，这个东西可以使用 FWT 来解决。`1` 和 `?` 也同理。

如果字符串中同时含有 `0`，`1`，`?` 呢？考虑容斥，将所有的 `1` 转化为 `?`，然后问题转化为 `0` 和 `?` 的部分，可以用 FWT 解决。但是这样显然算多了，`1` 的部分已经固定，不能用 $0$ 来代替。因此暴力容斥掉 $0$ 的部分即可，获得了一个 $O(Q2^{k_1})$ 的暴力。

同样的，考虑将 `0` 转化为 `?`，然后 FWT 套容斥，此时获得了一个 $O(Q2^{k_0})$ 的暴力。

但是问题是这三个暴力都可以被卡掉！因此考虑将她们数据点分，每一次找到其中期望跑的最快的一个跑，即比较 $k_0,k_1,k_?$ 中最小的元素然后跑暴力。这样就可以在 $O(n2^n+Q2^{\min(k_0,k_1,k_?)})$ 的时间复杂度内十分暴力的过题啦。代码很好写就不放了。

---

## 作者：dAniel_lele (赞：0)

记 $0,1,?$ 各有 $x,y,z$ 个。

枚举每个 $?$ 是 $0$ 还是 $1$，然后暴力将所有对应位置的值加起来，这样做是 $O(2^z)$ 的。

钦定每个位置大于等于 $0$ 或 $1$，算出对应的和，使用高维后缀和可以做到 $O(L2^L)$。在此之后，$?$ 对应该位 $\geq0$，$1$ 对应该位 $\geq1$，$0$ 无法很好解决，但是可以使用 $\geq0$ 的方案减去 $\geq1$ 的方案，枚举钦定每个 $0$ 变成 $\geq0$ 还是 $\geq1$，这样做是 $O(2^x)$。

钦定每个位置小于等于 $0$ 或 $1$，算出对应的和，使用高维前缀和可以做到 $O(L2^L)$。在此之后，$?$ 对应该位 $\leq1$，$0$ 对应该位 $\leq0$，$1$ 无法很好解决，但是可以使用 $\leq1$ 的方案减去 $\leq0$ 的方案，枚举钦定每个 $1$ 变成 $\leq1$ 还是 $\leq0$，这样做是 $O(2^y)$。

注意到 $\min(x,y,z)\leq\frac{L}{3}$，于是我们可以在 $O(L2^L)$ 时间预处理，$O(2^{\min(x,y,z)})$ 时间单次查询，总 $O(L2^L+2^{\frac{L}{3}})$ 时间内解决本题。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f[1048576],g[1048576],h[1048576];
signed main(){
	int n,q; cin>>n>>q;
	for(int i=0;i<(1<<n);i++){
		char c; cin>>c;
		f[i]=g[i]=h[i]=c-'0';
	}
	for(int i=1;i<=n;i++) for(int j=0;j<(1<<n);j++) if((j>>(i-1))&1) g[j]+=g[j^(1<<(i-1))],h[j^(1<<(i-1))]+=h[j];
	while(q--){
		int a[n+1],cnt[3],pre=0,ans=0; cnt[0]=cnt[1]=cnt[2]=0;
		for(int i=1;i<=n;i++){
			char c; cin>>c;
			a[i]=((c=='?')?2:(c-'0'));
		}
		reverse(a+1,a+n+1);
		for(int i=1;i<=n;i++) cnt[a[i]]|=(1<<(i-1));
		if(__builtin_popcount(cnt[0])<=7){
			for(int i=1;i<=n;i++) if(a[i]==1) pre|=(1<<(i-1));
			for(int i=cnt[0];;i=(i-1)&cnt[0]){
				ans+=h[pre|i]*(-2*(__builtin_popcount(i)&1)+1);
				if(i==0) break;
			}
		}
		else if(__builtin_popcount(cnt[1])<=7){
			for(int i=1;i<=n;i++) if(a[i]==2) pre|=(1<<(i-1));
			for(int i=cnt[1];;i=(i-1)&cnt[1]){
				ans+=g[pre|i]*(-2*((__builtin_popcount(i)^__builtin_popcount(cnt[1]))&1)+1);
				if(i==0) break;
			}
		}
		else if(__builtin_popcount(cnt[2])<=7){
			for(int i=1;i<=n;i++) if(a[i]==1) pre|=(1<<(i-1));
			for(int i=cnt[2];;i=(i-1)&cnt[2]){
				ans+=f[pre|i];
				if(i==0) break;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Hypercube (赞：0)

应该算是一篇比较详尽的题解。

首先本题显然有 $O(3^n + q)$ 的 dp 做法，即处理出所有询问的答案，然后使用经典套路 `lowbit` 转移，但和本题解做法无关，不作赘述。

然后进行观察。不难发现 `?` 数量很少的时候是可以暴力 dfs 的。更具体的，上限大概在 $6$ 左右。而我们又发现一个长度为 $20$ 的串，三种字符必然存在一种出现次数不超过 $6$。于是我们猜想可能能通过类似根号分治的方法解决这道题。

实际上 $1$ 和 $0$ 是两个对称的情况，只需要考虑其中一种即可。以下假设 $1$ 出现的次数不超过 $6$。

于是又是一个经典套路了。对于每次询问，要使 $1$ 的位置全部合法其实比较麻烦，不如计算钦定 $0$ 合法的情况下 $1$ 不合法的答案。这部分如果我们能预处理出一个 $f_S$，表示 $S$ 中为 $0$ 的位置全部为 $0$，其余任意填的答案便可以简单容斥计算了。

其实这个 $f_S$ 还是有点难算。于是我们不妨做一个转化，将所求转化为子集求和。原因显然。但直接枚举似乎仍旧是 $O(3^n)$ 的。

这时候便可以上点科技了。众所周知子集求和是可以利用 [高维前缀和](https://www.cnblogs.com/nightsky05/p/15545568.html) 做到 $O(n2^n)$ 的。于是这部分便可以快速解决了。

同理，$0$ 的情况对称一下即可。

总复杂度 $O(n2^n+2^{\min}q)$，$\min$ 表示三种字符数量的最小值。

代码写得比较丑，就不放了。需要的话可以私信我要。

---

