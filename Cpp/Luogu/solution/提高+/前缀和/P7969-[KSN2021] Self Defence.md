# [KSN2021] Self Defence

## 题目描述

定义一个字符串的权值为它长度为 $M$ 且只包含一种字符的子串数量。

例如字符串 ``ABBB``，在 $M=2$ 时的权值为 $2$。

给定一个长度为 $N$ 的字符串，每个字符为 ``?``，``A`` 和 ``B`` 中的一个，你需要求出将每个 ``?`` 替换为 ``A`` 或 ``B`` 后，可以得到多少个权值为 $K$ 的字符串。

答案对 $10^9+7$ 取模。

## 说明/提示

**【样例解释】**

对于第一组样例，以下为所有合法字符串：

```plain
AAAAB
ABBBB
BAAAA
BBBBA
```

对于第二组样例，以下为所有合法字符串：

```plain
AAABA
AABAA
AABBA
ABAAA
ABBAA
ABBBA
```

**【数据范围】**

**本题采用捆绑测试。**

* Subtask 1（5 points）：只存在一组数据，满足 $N=10$，$M=3$，$K=5$，$S=\texttt{????A???B?}$。
* Subtask 2（9 points）：$N\le 20$。
* Subtask 3（11 points）：$N\le 200$。
* Subtask 4（6 points）：$M=2$，$K=0$。
* Subtask 5（9 points）：$K=0$。
* Subtask 6（8 points）：$K\le 1$。
* Subtask 7（27 points）：$S$ 只包含 ``?``.
* Subtask 8（25 points）：无特殊限制。

对于所有数据，$1\leq N\leq 3000$，$1\leq M\leq N$，$0\leq K\leq N$。

## 样例 #1

### 输入

```
5 4 1
?????```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2 2
A????```

### 输出

```
6```

## 样例 #3

### 输入

```
5 3 4
AAAAA```

### 输出

```
0```

# 题解

## 作者：Elma_ (赞：7)

难得一见的 CNOI 风巨大套路题。

设 $f_{i,j,0/1}$ 为填了前 $i$ 个字符，此时字符串权值为 $j$，第 $i$ 个字符是 A/B 的方案数。

转移时枚举上一个连续段的结尾 $k$ 进行转移，我们以第 $i$ 个字符为 A 的情况为例，设上一个 B 出现的位置为 $p_i$，不难发现合法的 $k$ 满足 $k \in [p_i,i-1]$。分类讨论：

- 当 $i - p_i < m$ 时，新划分出的这一段对权值没有贡献，转移如下：

$$f_{i,j,0}= \sum_{k=p_i}^{i-1} f_{k,j,1}$$

- 当 $i - p_i \geq m$ 时，我们将对权值有贡献的部分和对权值没有贡献的部分分两段进行转移。对于一个长为 $l(l \geq m)$ 的连续段，其对权值的贡献为 $l-m+1$。因此转移如下：

$$f_{i,j,0} = \sum_{k=i-m+1}^{i-1}f_{k,j,1}+\sum_{k=p_i}^{i-m}f_{k,j-[(i-k)-m+1],1}$$

第 $i$ 个字符为 B 的情况同理。边界 $f_{0,0,0/1} =1$。然而这样是 $O(n^3)$ 的，我们还得想办法优化上面的东西。

对于对权值没有贡献的部分用前缀和优化即可。比较棘手的是对权值有贡献的部分。我们观察一下转移时用到的状态的两个下标 $i,j$ 之差：

$$j - [(i-k)-m+1]-k = j - i + m - 1$$

而这个东西和 $k$ 是无关的。这启发我们多设一个 $h_{i,k,0/1}$ 表示前 $i$ 位中，所有 $j-i = k$ 的 $f_{i,j,0/1}$ 之和，前缀和搞一下就能做到 $O(n^2)$ 了。边界 $g_{0,0,0/1}=h_{0,0,0/1}= 1$。

然后需要注意的是 $j-i$ 可能减出负数，我们把下标平移 $n$ 就可以避免这个问题了。

```cpp
const int MN = 3e3 + 5, Mod = 1e9 + 7;

int N, M, K, f[MN][MN][2], g[MN][MN][2], h[MN][2 * MN][2], pA[MN], pB[MN];
char s[MN];

signed main(void) {
    N = read(), M = read(), K = read(), scanf("%s", s + 1);
    for (int i = 1, A = 0, B = 0; i <= N; i++) {
        if (s[i] == 'A') A = i;
        if (s[i] == 'B') B = i;
        pA[i] = A, pB[i] = B;
    }
    g[0][0][0] = g[0][0][1] = h[0][N][0] = h[0][N][1] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            if (s[i] != 'B') {
                if (i - pB[i] < M) {
                    f[i][j][0] = (f[i][j][0] + ((g[i - 1][j][1] - (pB[i] ? g[pB[i] - 1][j][1] : 0)) % Mod + Mod) % Mod) % Mod;
                } else {
                    int x = j - i + M - 1 + N;
                    f[i][j][0] = (f[i][j][0] + ((g[i - 1][j][1] - g[i - M][j][1]) % Mod + Mod) % Mod) % Mod;
                    f[i][j][0] = (f[i][j][0] + ((h[i - M][x][1] - (pB[i] ? h[pB[i] - 1][x][1] : 0)) % Mod + Mod) % Mod) % Mod;
                }
            }
            if (s[i] != 'A') {
                if (i - pA[i] < M) {
                    f[i][j][1] = (f[i][j][1] + ((g[i - 1][j][0] - (pA[i] ? g[pA[i] - 1][j][0] : 0)) % Mod + Mod) % Mod) % Mod;
                } else {
                    int x = j - i + M - 1 + N;
                    f[i][j][1] = (f[i][j][1] + ((g[i - 1][j][0] - g[i - M][j][0]) % Mod + Mod) % Mod) % Mod;
                    f[i][j][1] = (f[i][j][1] + ((h[i - M][x][0] - (pA[i] ? h[pA[i] - 1][x][0] : 0)) % Mod + Mod) % Mod) % Mod;
                }
            }
            g[i][j][0] = (g[i - 1][j][0] + f[i][j][0]) % Mod;
            g[i][j][1] = (g[i - 1][j][1] + f[i][j][1]) % Mod;
            h[i][j - i + N][0] = (h[i - 1][j - i + N][0] + f[i][j][0]) % Mod;
            h[i][j - i + N][1] = (h[i - 1][j - i + N][1] + f[i][j][1]) % Mod;
        }
    }
    int Ans = 0;
    Ans = (f[N][K][0] + f[N][K][1]) % Mod;
    printf("%d\n", Ans);
    return 0;
}
```


---

## 作者：MoYuFang (赞：5)

本文起笔于```2022.01.08```。

[P7969 [KSN2021] Self Defence](https://www.luogu.com.cn/problem/P7969) 

首先很容易可以想到一个 $O(n^3)$ 的套路 $\text{dp}$，设 $f(i,j,k,0/1)$ 表示当前处理到第 $i$ 个字符，已经有了 $j$ 个单位的权值，第 $i$ 个字符为 $\text{A/B}$，且第 $i$ 个字符所在的极长连续段长度为 $k$ 时的方案数，转移很简单，略过。

前两维难以优化掉，那只好优化掉第三维，方法是通过增加决策量来减少状态。

为了方便 $\text{dp}$ 的转移我们设 $m=M-1$，则长度为 $l$ 的连续段（全部由同一种字符组成）的权值为 $\max\{l-m,0\}$。

设 $f(i,j,0/1)$ 表示当前处理到第 $i$ 个字符，已经有了 $j$ 个单位的权值，且第 $i$ 个字符所在的极长连续段由 $\text{A/B}$ 组成，则决策时枚举上一个极长连续段（由与目前字符相反的字符 $\text{B/A}$ 组成）的末尾位置，然后转移。
$$
f(i,j,fg)=\sum_{k=0}^{i-1}f(k,j-\max\{i-k-m,0\},fg\oplus 1)
$$
然而上面的转移不完全正确，我们还要特判一下字符串子段 $str[k+1,i]$ 是否能构成由全部由 $fg$ 对应字符组成的极长连续段，于是设 $s(i,fg)$ 为 $k$ 所能取到的最小值，即为满足 $str[k+1,i]$ 为由 $fg$ 对应字符组成的极长连续段的最小的 $k$，$s$ 是很容易预处理的。

还要注意 $j-\max\{i-k-m,0\}$ 不能为负数，即 $k\ge i-m-j$，于是正确的转移方程为
$$
f(i,j,fg)=\sum_{k=\max\{s(i,fg),i-m-j\}}^{i-1}f(k,j-\max\{i-k-m,0\},fg\oplus 1)
$$
然后根据 $\max$ 取左边的，还是取右边的进行分段
$$
\begin{aligned}
f(i,j,fg)&=\sum_{k=\max\{s(i,fg),i-m-j\}}^{i-m-1}f(k,k+(m+j-i),fg\oplus 1)\\
&+\sum_{k=\max\{s(i,fg),i-m\}}^{i-1}f(k,j,fg\oplus 1)\\
\end{aligned}
$$
显然，这个转移是可以通过前缀和优化的

设
$$
\begin{aligned}
&g(i,j,fg)=\sum_{k=0}^{\min\{i,j\}}f(i-k,j-k,fg)\\
&h(i,j,fg)=\sum_{k=0}^{i}f(k,j,fg)\\
\end{aligned}
$$
再设
$$
\begin{aligned}
&b_1=\max\{s(i,fg),i-m-j\},&t_1=i-m-1\\
&b_2=\max\{s(i,fg),i-m\},&t_2=i-1\\
&x=m+j-i&\\
\end{aligned}
$$
所以有
$$
\begin{aligned}
f(i,j,fg)&=\sum_{k=b_1}^{t_1}f(k,k+x,fg\oplus 1)\\
&+\sum_{k=b_2}^{t_2}f(k,j,fg\oplus 1)\\
&=g(t_1,t_1+x,fg\oplus1)-g(b_1-1,b_1-1+x,fg\oplus1)\\
&+h(t_2,j,fg\oplus1)-h(b_2,j,fg\oplus1)
\end{aligned}
$$
而当 $b_i>t_i$ 时，对应的求和式为 $0$，这个要特判一下。

边界条件为 
$$
\begin{aligned}
&f(0,j,fg)=g(0,j,fg)=h(0,j,fg)=[j=0]\\
&f(i,j,fg)=0\quad(j>\max\{i-m,0\})\\
\end{aligned}
$$
最终答案为
$$
ans = f(N,K,0)+f(N,K,1)
$$
代码

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <assert.h>
using namespace std;

#define re register
#define sf scanf
#define pf printf
#define nl() putchar('\n')
#define ms(x, val) memset(x, val, sizeof(x))
#define ll long long
#define db double
#define ull unsigned long long
#define _for(i, a, b) for(re int (i) = (a); (i) < (b); ++(i))
#define _rfor(i, a, b) for(re int (i) = (a); (i) <= (b); ++(i))
#define _fev(p, u) for(re int (p) = head[(u)]; (p); (p) = nex[(p)])
#define inf 0x7fffffff
#define maxn 3005
#define mod 1000000007ll

template <class T>
void print(string name, T arr[], int n, int flag = 1){
	cout<<name<<":";
	_for(i, 0, n)cout<<" "<<arr[i+flag];
	cout<<endl;
}

int rdnt(){
	re int x = 0, sign = 1;
	re char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') sign = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (c ^ 48), c = getchar();
	return x * sign;
}

char str[maxn];
int s[maxn][2], f[maxn][maxn][2], g[maxn][maxn][2], h[maxn][maxn][2];

bool yes(char x, char c){
	return x == '?' || x == c;
}

int cg(re int b, re int t, re int k, re int fg){
	if (b > t) return 0;
	else return (g[t][t+k][fg]+(b>0?mod-g[b-1][b-1+k][fg]:0))%mod;
}

int ch(re int b, re int t, re int j, re int fg){
	if (b > t) return 0;
	else return (h[t][j][fg]+(b>0?mod-h[b-1][j][fg]:0))%mod;
}

void print(int arr[maxn][maxn][2], int n, int k){
	_rfor(i, 0, n){
		pf("(%d):", i);
		_rfor(j, 0, k) pf(" %d|%d", arr[i][j][0], arr[i][j][1]);
		nl();
	}nl();
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("sample.in", "r", stdin);
	//freopen("sample.out", "w", stdout);
	#endif
	
	re int n = rdnt(), m = rdnt()-1, K = rdnt();
	sf("%s", str+1);
	s[0][0] = s[0][1] = 0;
	_rfor(i, 1, n){
		if (yes(str[i], 'A')) s[i][0] = yes(str[i-1], 'A')?s[i-1][0]:i-1;
		if (yes(str[i], 'B')) s[i][1] = yes(str[i-1], 'B')?s[i-1][1]:i-1;
		if (str[i] == 'A') s[i][1] = i;
		if (str[i] == 'B') s[i][0] = i;
	}
	
	re int b1, b2, t1, t2;
	f[0][0][0] = f[0][0][1] = g[0][0][0] = g[0][0][1] = h[0][0][0] = h[0][0][1] = 1;
	_rfor(i, 1, n) _rfor(j, 0, K) _rfor(fg, 0, 1){
		b1 = max(s[i][fg], i-m-j); t1 = i-m-1;
		b2 = max(s[i][fg], i-m); t2 = i-1;
		
		if (j <= max(0, i-m)) f[i][j][fg] = (cg(b1, t1, m+j-i, fg^1) + ch(b2, t2, j, fg^1))%mod;
		else f[i][j][fg] = 0;
		g[i][j][fg] = (f[i][j][fg] + (j>0?g[i-1][j-1][fg]:0))%mod;
		h[i][j][fg] = (f[i][j][fg] + h[i-1][j][fg])%mod;
	}
	
//	print(f, n, K);
//	print(g, n, K);
//	print(h, n, K);
	
	re int ans = (f[n][K][0] + f[n][K][1])%mod;
	pf("%d\n", ans);

	return 0;
}
```







---

## 作者：gyh20 (赞：2)

设 $f_{i,j,0/1}$，表示前 $i$ 个字符，权值为 $j$，最后一个是 $A/B$ 的方案数。

转移可以一段一段转移，假设当前新增的连续段长度为 $k$，那么会转移到 $f_{i+k,j+\max(0,k-K+1)}$。

每次选择的 $k$ 下界是 $1$，上界是下一个不同字符到当前位置的距离。

将 $\max$ 拆开，变成两部分，都可以用差分优化转移，具体的，为每个状态打两个标记，分别维护贡献。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=1e9+7;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int f[3002][3002][2],n,m,K,sa[3002],sb[3002],tg[3002][3002][2],nxta[3002],nxtb[3002],tg1[3002][3002][2];
char s[3002];
int main(){
	n=read(),m=read(),K=read(),scanf("%s",s+1);
	for(re int i=1;i<=n;++i)sa[i]=sa[i-1]+(s[i]=='A'),sb[i]=sb[i-1]+(s[i]=='B');
	nxta[n+1]=nxtb[n+1]=n+1;
	for(re int i=n;~i;--i){
		nxta[i]=nxta[i+1],nxtb[i]=nxtb[i+1];
		if(s[i+1]=='A')nxta[i]=i+1;
		if(s[i+1]=='B')nxtb[i]=i+1;
	}
	f[0][0][0]=f[0][0][1]=1;
	for(re int i=0;i<=n;++i)
		for(re int j=0;j<=min(K,i);++j){
			if(i)add(tg[i][j][0],tg[i-1][j][0]);
			if(i)add(tg[i][j][1],tg[i-1][j][1]);
			if(i&&j)add(tg1[i][j][0],tg1[i-1][j-1][0]),add(tg1[i][j][1],tg1[i-1][j-1][1]);
			add(f[i][j][0],tg[i][j][0]);
			add(f[i][j][1],tg[i][j][1]);
			add(f[i][j][0],tg1[i][j][0]);
			add(f[i][j][1],tg1[i][j][1]);
			if(s[i+1]!='A'){
				add(tg[i+1][j][1],f[i][j][0]);
				add(tg[min(nxta[i],i+m)][j][1],M-f[i][j][0]);
			}
			if(s[i+1]!='B'){
				add(tg[i+1][j][0],f[i][j][1]);
				add(tg[min(nxtb[i],i+m)][j][0],M-f[i][j][1]);
			}
			if(i+m<=n&&sa[i+m]==sa[i])add(tg1[i+m][j+1][1],f[i][j][0]),add(tg1[nxta[i]][j+nxta[i]-i-m+1][1],M-f[i][j][0]);
			if(i+m<=n&&sb[i+m]==sb[i])add(tg1[i+m][j+1][0],f[i][j][1]),add(tg1[nxtb[i]][j+nxtb[i]-i-m+1][0],M-f[i][j][1]);
		}
	printf("%d",Mod(f[n][K][0]+f[n][K][1]));
}


```


---

## 作者：ethan0328 (赞：0)

## 思路

可以想到一个 DP，令 $f_{i,j,0/1}$ 表示第 $i$ 位的字母填 $A/B$ 是权值为 $j$ 的情况数。

考虑预处理 $pre_{i,0/1}$ 表示第 $i$ 位前第一个已经填好的 $A/B$。

当 $i-pre_i<m$ 时，最新的一段连续的 $A/B$ 没有贡献。枚举前一个连续段的最后一位 $l$。

### $f_{i,j}=\sum_{l=pre_i}^{i-1} f_{l,j}$

当 $i-pre_i\ge m$ 时，我们把答案分为两部分，一部分有贡献，另一部分没有。

### $f_{i,j}=\sum_{l=i-m+1}^{i-1} f_{l,j}+\sum_{l=pre_i}^{i-m} f_{l,j-(i-k-m+1)}$

显然 $f_{0,0,0/1}=1$，最后答案为 $f_{n,k,0}+f_{n,k,1}$。

但这样时间是 $n^3$ 的，我们考虑前缀和优化。

没贡献的那部分用 $s_{i,j,0/1}$ 记录所有 $f_{l,j,0/1}$ 的值。

对于有贡献的部分，我们发现 $j-(i-k-m+1)-l=j-i+m-1$，所以可以令 $p_{i,x,0/1}$ 表示所有 $l-j=x$ 的 $f_{l,j,0/1}$ 的值。于是时间复杂度是 $n^2$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+10,mod=1e9+7;
int n,m,k,pre[N][2],f[N][N][2],s1[N][N][2],s2[N][N*2][2];
string s;
int main()
{
	int x,y;
	cin>>n>>m>>k;
	cin>>s;
	s=" "+s;
	x=y=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='A')
		{
			x=i;
		}else if(s[i]=='B')
		{
			y=i;
		}
		pre[i][0]=x;
		pre[i][1]=y;
	}
	f[0][0][0]=f[0][0][1]=1;
	s1[0][0][0]=s1[0][0][1]=1;
	s2[0][n][0]=s2[0][n][1]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=k;j++)
		{
			if(s[i]=='?')
			{
				for(x=0;x<2;x++)
				{
					if(i-pre[i][1-x]<m)
					{
						f[i][j][x]=((s1[i-1][j][1-x]-(pre[i][1-x]? s1[pre[i][1-x]-1][j][1-x]:0))%mod+mod)%mod;
					}else
					{
						f[i][j][x]=((s1[i-1][j][1-x]-s1[i-m][j][1-x])%mod+mod)%mod;
						f[i][j][x]=(((f[i][j][x]+s2[i-m][j-i+m-1+n][1-x])%mod-(pre[i][1-x]? s2[pre[i][1-x]-1][j-i+m-1+n][1-x]:0))%mod+mod)%mod;
					}
				}
			}else
			{
				x=s[i]-'A';
				if(i-pre[i][1-x]<m)
				{
					f[i][j][x]=((s1[i-1][j][1-x]-(pre[i][1-x]? s1[pre[i][1-x]-1][j][1-x]:0))%mod+mod)%mod;
				}else
				{
					f[i][j][x]=((s1[i-1][j][1-x]-s1[i-m][j][1-x])%mod+mod)%mod;
					f[i][j][x]=(((f[i][j][x]+s2[i-m][j-i+m-1+n][1-x])%mod-(pre[i][1-x]? s2[pre[i][1-x]-1][j-i+m-1+n][1-x]:0))%mod+mod)%mod;
				}
			}
			s1[i][j][0]=(s1[i-1][j][0]+f[i][j][0])%mod;
			s1[i][j][1]=(s1[i-1][j][1]+f[i][j][1])%mod;
			s2[i][j-i+n][0]=(s2[i-1][j-i+n][0]+f[i][j][0])%mod;
			s2[i][j-i+n][1]=(s2[i-1][j-i+n][1]+f[i][j][1])%mod;
		}
	}
	cout<<(f[n][k][0]+f[n][k][1])%mod;
}
```


---

