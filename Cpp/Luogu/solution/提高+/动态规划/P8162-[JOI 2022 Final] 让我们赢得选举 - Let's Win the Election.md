# [JOI 2022 Final] 让我们赢得选举 / Let's Win the Election

## 题目描述

JOI 共和国有 $N$ 个州，编号为 $1 \sim N$。在 2022 年，JOI 共和国将举行总统大选。选举将在每个州分别举行。每个州的获胜者将赢得该州的一张选票。

Rie 将竞选总统，她正计划赢得选举。她决定以发表演讲的方式来提高自己的可靠程度。在她发表演讲后，下列事件可能会发生。

- 如果在第 $i$ 个州的总演讲时间达到了 $A_i$ 小时，她将赢得该州的一张选票。
- 如果在第 $i$ 个州的总演讲时间达到了 $B_i$ 小时，她将获得一名来自该州的协作者。
- 有可能 Rie 在第 $i$ 个州无法获得协作者。此种情况下，$B_i = -1$，否则保证 $B_i > A_i$。

来自第 $i$ 个州的协作者可以在第 $i$ 个州外发表演讲。多个人可以同时在同一个州发表演讲。举个例子，如果两个人在某个州同时发表了 $x$ 小时的演讲，则该州的总演讲时间将增加 $2 x$ 小时。演讲的时间不必是整数个小时。我们可以忽略在两州之间的交通耗时。

大选日快到了，Rie 想要尽快得到 $K$ 张选票。

给定州的数量和每个州的信息，写一个程序计算得到 $K$ 张选票的最小耗时（以小时为单位）。

## 说明/提示

**【样例解释 \#1】**

按照如下方案进行演讲，Rie 将在 $5.5$ 小时内赢得每个州的选票。

- 在第 $2$ 个州演讲 $2$ 个小时，赢得一张选票。
- 在第 $2$ 个州再演讲 $1$ 个小时，获得一个协作者。
- 在第 $3$ 个州与协作者一起演讲 $2$ 个小时，赢得一张选票。
- 在第 $1$ 个州与协作者一起演讲 $0.5$ 个小时，赢得一张选票。

这个样例满足子任务 $3, 4, 5, 6, 7$ 的性质。

**【样例解释 \#2】**

按照如下方案进行演讲，Rie 将在 $32$ 小时内赢得 $4$ 张选票。

- 在第 $1$ 个州演讲 $4$ 个小时，赢得一张选票。
- 在第 $2$ 个州演讲 $11$ 个小时，赢得一张选票。
- 在第 $3$ 个州演讲 $6$ 个小时，赢得一张选票。
- 在第 $6$ 个州演讲 $11$ 个小时，赢得一张选票。

这个样例满足子任务 $1, 2, 3, 4, 5, 7$ 的限制。

**【样例解释 \#3】**

按照如下方案进行演讲，Rie 将在 $11.5$ 小时内赢得 $3$ 张选票。

- 在第 $4$ 个州演讲 $7$ 个小时，赢得一张选票，并获得一个协作者。
- 在第 $1$ 个州演讲 $4$ 个小时，赢得一张选票。与此同时，协作者在第 $2$ 个州演讲 $4$ 个小时。
- 在第 $2$ 个州与协作者一起演讲 $0.5$ 个小时，赢得一张选票。

这个样例满足子任务 $2, 3, 4, 5, 7$ 的限制。

**【样例解释 \#4】**

这个样例满足子任务 $3, 4, 5, 7$ 的限制。

**【样例解释 \#5】**

这个样例满足子任务 $4, 5, 7$ 的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$1 \le K \le N \le 500$，$1 \le A_i \le 1000$，$A_i \le B_i \le 1000$ 或 $B_i = -1$。

- 子任务 $1$（$5$ 分）：$B_i = -1$。
- 子任务 $2$（$5$ 分）：$B_i = -1$ 或 $B_i = A_i$。
- 子任务 $3$（$11$ 分）：$N \le 7$。
- 子任务 $4$（$12$ 分）：$N \le 20$。
- 子任务 $5$（$33$ 分）：$N \le 100$。
- 子任务 $6$（$11$ 分）：$K = N$。
- 子任务 $7$（$23$ 分）：无特殊限制。

----

**译自 [JOI 2022 Final](https://www.ioi-jp.org/joi/2021/2022-ho/index.html) T3「[選挙で勝とう](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t3.pdf) / [Let's Win the Election](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t3-en.pdf)」**

## 样例 #1

### 输入

```
3
3
1 5
2 3
4 5
```

### 输出

```
5.500000000000000
```

## 样例 #2

### 输入

```
7
4
4 -1
11 -1
6 -1
12 -1
36 -1
11 -1
20 -1
```

### 输出

```
32.000000000000000
```

## 样例 #3

### 输入

```
5
3
4 -1
5 -1
6 -1
7 7
8 8
```

### 输出

```
11.500000000000000
```

## 样例 #4

### 输入

```
7
5
28 36
11 57
20 35
19 27
31 33
25 56
38 51
```

### 输出

```
62.166666666666664
```

## 样例 #5

### 输入

```
20
14
106 277
175 217
170 227
164 245
118 254
139 261
142 270
185 200
162 241
153 239
128 264
103 299
147 248
158 236
160 232
183 205
194 197
135 260
153 234
128 260
```

### 输出

```
644.203571428571422
```

# 题解

## 作者：封禁用户 (赞：20)

容易想到一个错误的贪心：

- 一定要先得到支持者，再和支持者一起演讲。

- 集中力量办事效率高，支持者们和本人一定要在同一个州进行演讲。

- 按 $b_i$ 从小到大排序，再将剩下的按 $a_i$ 从小到大排序，算出最小值。

但这个贪心有一个问题：可能一些选中的 $b_i$ 对应的 $a_i$ 极其地小。

**明确一个问题，我们不选 $b_i$ 的原因是因为 $a_i$ 更加优秀。**

我们修改贪心策略，需要加入一些动态规划：

- 按 $b_i$ 从小到大排序。

- 枚举 $i$,对于前 $i$ 个，肯定是要么选 $a_i$，要么选 $b_i$，后面的肯定选 $a_i$ 最小的 $k-i$ 个。

代码也就呼之欲出了：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -1;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define N 510
struct node
{
	double a,b;
	inline bool friend operator<(node X,node Y)
	{
		return X.b < Y.b;
	}
}p[N],q[N];
double dp[N][N],sum[N][N];
inline bool cmp(node X,node Y)
{
	return X.a < Y.a;
}
int n,k;
int main()
{
	read(n),read(k);
	F(i,1,n) 
	{
		scanf("%lf%lf",&p[i].a,&p[i].b);
		if(p[i].b == -1) p[i].b = 1e18;	
	}
	sort(&p[1],&p[n+1]); 
	D(i,n,1)
	{
		F(i,1,n) q[i] = p[i];
		sort(&q[i],&q[n+1],cmp);
		F(j,1,n-i+1) sum[i][j] = sum[i][j-1] + q[i+j-1].a;
	} 
	double ans = 1e18;
	F(cas,0,n)
	{
		memset(dp,0x7f,sizeof(dp));	
		dp[0][0] = 0.0;
		F(i,1,n)
			F(j,0,cas)
			{
				dp[i][j] = min(dp[i][j],dp[i-1][j] + p[i].a / (cas + 1));
				if(j&&p[i].b != 1e18) dp[i][j] = min(dp[i][j],dp[i-1][j-1] + p[i].b / j);	
			}
		F(i,cas,n) ans = min(ans,dp[i][cas] + sum[i+1][k-i] / (cas + 1));
	}
	printf("%.15lf",ans);
	return 0;
}
```



---

## 作者：RyexAwl (赞：10)

因为 $
\min(\dfrac{a}{b},\dfrac{c}{d})\le \dfrac{a+c}{b+d}\le \max(\dfrac{a}{b},\dfrac{c}{d}) $，所以一定不存在多个人在不同州同时演讲的情况。集中力量办大事！

并且在最优解中，一个州 $i$ 的演讲时长要么是 $0$ ，要么是 $A_i$ 或 $B_i(B_i\not= -1)$。

考虑当前已经确定了每个州的演讲时长，确定一种演讲顺序使得时间最短。

因为每次一定是 Rie 和所有的合作者在同一个州演讲，所以时间就是每个州的演讲时长的带权和（演讲时长除以演讲人数）。

如果一个州的演讲时长是 $A_i$ 称该州为 “支持州”，如果一个州的演讲时长是 $B_i$ 称该州为 “合作州”，如果一个州的演讲时长为 $0$ 称该州是 “反对州”。

那么考虑确定一种演讲的顺序使得带权时间和最小，任意一个 “支持州”一定不会在 “合作州”之前进行演讲。

然后考虑 “合作州” 之间的顺序，根据排序不等式（顺序和>=乱序和>=反序和）一定是按 $B_i$ 排序后从小到大的顺序演讲最优。

那么我们只需要确定“合作州”的个数，“合作州”与“支持州”都是那些州就能够唯一确定该条件下的最优解了。

那么一个朴素的做法是将所有州按 $B$ 排序，枚举 “合作州” 个数，然后去做 $O(n^3)$ 的 DP $f[i,j,k]$ 为前 $i$ 个州中有恰好 $j$ 个 “合作州” $k$ 个“支持州”的最小时间。

但是我们可以发现最优解中最后一个 “合作州”与其前一个 “合作州” 之间的所有州一定是 “支持州”，因为如果之间存在一个 “反对州”，将最后一个 “合作州” 移动到该州一定更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/go8rp1vj.png)

进而可以推出：第 $i$ 个“合作州”与第 $i+1$ 个“合作州”之间的所有州均是 “支持州”。

那么我们可以将 $O(n^3)$ 的 DP 简化成 $O(n^2)$ 的 DP $f[i,j]$ 表示前 $i$ 个州中选恰好 $j$ 个 “合作州” 的最小花费。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 505;

double f[N][N];

int n,K;

int A[N],B[N],p[N],temp[N];

double get(int k) {
    rep(i,1,n) temp[i] = A[p[i]];
    rep(i,0,n) rep(j,0,n) f[i][j] = 1000000000;
    f[0][0] = 0; double res = 1000000000;
    rep(i,1,n) rep(j,0,std::min(k,i)) {
        f[i][j] = f[i-1][j] + ((double)A[p[i]]/(k+1));
        if (j >= 1 && B[p[i]] != -1) f[i][j] = std::min(f[i][j],f[i-1][j-1]+((double)B[p[i]]/j));
    }
    rep(i,K,n) res = std::min(res,f[i][k]);
    per(i,K-1,k) {
        std::sort(temp+i+1,temp+n+1);
        double val = 0;
        rep(j,1,K-i) val += temp[i+j];
        res = std::min(res,f[i][k] + ((double)val/(k+1)));
    }
    return res;
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    gin >> n >> K; rep(i,1,n) gin >> A[i] >> B[i]; rep(i,1,n) p[i] = i;
    std::sort(p+1,p+1+n,[](int x,int y){if (~B[x] && ~B[y])return B[x] < B[y]; else return B[x] > B[y];});
    double ans = 1000000000;  
    
    rep(i,0,K) ans = std::min(ans,get(i));
    prt << ans; 
}

}signed main(){wxy::main(); return 0;}
```


---

## 作者：lg_zhou (赞：7)

讲讲这道题我自己的思路。

首先因为演讲小时不必是整数，我们可以想象成所有人都在做一个演讲，再集中去下一个演讲，是不可能更劣的。

再次，非常显然，我们肯定是招揽若干个下属，再去集中揽票。这样揽票的效率高，因为如果揽票再招人，把揽票和招人的两个州交换，肯定更优。

最后，如果招揽的下属定了，剩下揽票的州肯定走时间最少的，不解释。

根据这三条性质，我一开始口胡了贪心：将所有州按招人时间排序，招 $x+1$ 个人不好从招 $x$ 个人转移答案，就直接枚举一共招了 $b$ 个人，默认招人招排序后的前 $b$ 个州，再从后面选 $k-b$ 个揽票时间最小的州进行揽票。

码完才发现假了，因为有可能由于前 $b$ 个州里面有揽票时间极短的，把它放后面揽票反而更优。

看起来这个算法错误，但其实可以微调。因为前 $b$ 个州，按贪心来说应该招人，但揽票可能让它更优，但是绝对不可能是个反对州（连揽票级别都没达到）。更一步的，我们想到，如果招人没招全，那么就不可能出现反对州。

所以排序和枚举 $b$ 都不用变，把贪心换成动规就好了，设 $f[i][j]$ 为前 $i$ 个州有 $j$ 个招人州的最短时间。再预处理一下 $g[i][j]$ 为 $i-n$ 这些州揽票时间前 $j$ 短的揽票时间和。最终合并答案即可。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 505;
struct state{
	int a,b;
}s[maxn],ss[maxn];
bool cmp(state a, state b){
	return a.b < b.b;
}
bool cmp2(state a, state b){
	return a.a < b.a;
}
double f[maxn][maxn],g[maxn][maxn];
double mnans = 1e8;
int main(){
//	freopen("a.in","r",stdin);
	int n,k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> s[i].a >> s[i].b;
		if (s[i].b == -1) s[i].b = 1e9;
	}
	
	sort(s+1,s+1+n,cmp);
	memcpy(ss,s,sizeof s);
	for (int i = n; i >= 1; i--){
		sort(s+i,s+n+1,cmp2);
		for (int j = i; j <= n; j++){
			g[i][j-i+1] = g[i][j-i]+s[j].a;
		}
	}
	memcpy(s,ss,sizeof ss);
	
	for (int b = 0; b < k; b++){ // 再找几个人 
		for (int i = 0; i <= k; i++) for (int j = 0; j <= b; j++) f[i][j] = 1e8;
		f[0][0] = 0;
		for (int i = 1; i <= k; i++){
			f[i][0] = f[i-1][0]+(double)s[i].a/(b+1);
			for (int j = 1; j <= b; j++){
				f[i][j] = min(f[i-1][j-1]+(double)s[i].b/j,f[i-1][j]+(double)s[i].a/(b+1));
			}
		}
		for (int i = 0; i <= k; i++){
			mnans = min(mnans,f[i][b]+g[i+1][k-i]/(b+1));
		}
	}
	printf("%.4f\n",mnans);
	return 0;
}
```


---

## 作者：ZM____ML (赞：5)

**题意清晰，直接开始分析。**

## 分析

有两个很显然的**结论**：

1. 先去所有获得支持者的州演讲，再去其他的州演讲；

1. 所有人集中在一个州演讲会比一人去一个州演讲要更优。

并且对于最优解来说，在第 $i$ 个州所演讲的时间只可能是 $0$，$a_i$，$b_i$ 这三种可能。所以 _直接按 $b_i$ 从小到大排序，再对剩下的 $a_i$ 从小到大排序，动规求出最大值即可_ 。

这是一个假的贪心，因为有可能对于你所选的 $b_i$ 来说，选择它对应的 $a_i$ 可能贡献更大。所以我们要在这基础上再修改一下：

- 按 $b_i$ 从小到大排序，按照这个顺序演讲；

- 但是不一定每一个 $i$ 我们都会选择，因为可能在第 $i$ 个州演讲 $a_i$ 的时间比演讲 $b_i$ 的时间更优；

- 所以我们设出 $f_{i,j}$ 表示到第 $i$ 个州时，有 $j$ 个州获得了支持者所用的最小时间；

- 然后我们从 $0 \sim j$ 进行枚举，当前已经花费的时间和剩下演讲时间求和，并且取一个最小值。

## Code

```c
#include<cstdio>
#include<algorithm>
#define min(a,b) (a<b?a:b)
using namespace std;
const int N=505,inf=1e9;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int n,k,a[N];
double ans=inf,f[N][N];
struct node{
	int a,b;
}p[N];
inline bool cmp(node x,node y){
	return x.b<y.b;
}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		p[i].a=read(),p[i].b=read();
		if(p[i].b==-1)p[i].b=inf;
	}
	sort(p+1,p+n+1,cmp);
	for(int x=0;x<=k;x++){
		for(int i=1;i<=n;i++)a[i]=p[i].a;
		for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)f[i][j]=inf;
	    f[0][0]=0;
	    double res=inf;
	    for(int i=1;i<=n;i++){
	        for(int j=0;j<=min(x,i);j++){
	            f[i][j]=f[i-1][j]+1.0*p[i].a/(x+1);
	            if(j>=1&&p[i].b!=inf)f[i][j]=min(f[i][j],f[i-1][j-1]+1.0*p[i].b/j);
	        }
	    }
	    for(int i=k;i<=n;i++)res=min(res,f[i][x]);
	    for(int i=k;i>=x;i--){
	        sort(a+i+1,a+n+1);
	        double sum=0;
	        for(int j=i+1;j<=k;j++)sum+=a[j];
	        res=min(res,f[i][x]+sum/(x+1));
	    }
	    ans=min(ans,res);
	}
	printf("%.10lf",ans);
	return 0;
}
```


---

## 作者：HT_walnut (赞：5)

考场上写的纯贪心，假了，只拿了 $10$ pts 分。

显然，对于每个州，演讲时间只有 $0$，$a_{i}$，$b_{i}$ 三种情况。

定义演讲时间为 $a_{i}$ 的州为 $\operatorname{A}$ 类州（即只获得选票），演讲时间为 $b_{i}$ 的州为 $\operatorname{B}$ 类州（即获得协作者），演讲时间为 $0$ 的州为 $\operatorname{C}$ 类州（即不去演讲）。

先去演讲 $\operatorname{B}$ 类州，再去演讲 $\operatorname{A}$ 类州是更优的。

所以我们按照 $b_{i}$ 排序。

我们枚举 $b_{i}$ ，进行 $\operatorname{dp}$。

由于是按照 $b_{i}$ 升序排列的，那么如果 $\operatorname{B}$ 类州之前存在 $\operatorname{C}$ 类州，让该C类州成为 $\operatorname{B}$ 类州，该 $\operatorname{B}$ 类州成为 $\operatorname{C}$ 类州是更优的。

那么序列的前半部分只有 $\operatorname{A}$ 类州或 $\operatorname{B}$ 类州，后半部分只有 $\operatorname{A}$ 类州或 $\operatorname{C}$ 类州。

所以定义 $dp_{i,j}$ 表示枚举到第 $i$ 个州，选了 $j$ 个 $\operatorname{B}$ 类州的最少时间。

枚举 $\operatorname{B}$ 类州的个数 $\operatorname{sum}$，然后进行 $\operatorname{dp}$。

$\operatorname{dp}$ 到 $\operatorname{sum}$ 后停止，计算剩下的州中最小的 $\operatorname{A}$ 类州的时间。

设后 $x$ 个州里，$a_{i}$ 最小的 $y$ 个州的 $a_{i}$ 之和为 $w(x,y)$。

那么答案就是 $\min_{i = sum}^{k}dp_{i,sum} + w(n - i,k - i)$。

$\operatorname{dp}$ 的时间复杂度是 $O(n^{2})$，由于要枚举 $\operatorname{B}$ 类州的个数，所以总时间复杂度 $O(n^{3})$。

```cpp
#define Kamisato_Ayaka no tui,juan
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define ll long long
#define db double
inline int in(){
    int x = 0;
    bool f = 0;
    char c = getchar();
    while(c > '9' || c < '0'){
        if(c == '-') f = 1;
        c = getchar();
    }
    while(c <= '9' && c >= '0'){
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    if(f) return -x;
    else return x;
}
const int N = 510;
int n,k;
int a[N];
db ans = 1e9;
db dp[N][N];
struct node{
    int a,b;
}q[N];
bool operator < (const node x,const node y){
    return x.b < y.b;
}
inline void work(int x){
    for(int i = 1;i <= n;++i) a[i] = q[i].a;
    for(int i = 0;i <= n;++i)
        for(int j = 0;j <= n;++j) dp[i][j] = 1e9;
    dp[0][0] = 0;
    db res = 1e9;
    for(int i = 1;i <= n;++i){
        for(int j = 0;j <= min(x,i);++j){
            dp[i][j] = dp[i - 1][j] + q[i].a * 1.0 / (x + 1);
            if(j >= 1 && q[i].b != 1e9) dp[i][j] = min(dp[i][j],dp[i - 1][j - 1] + q[i].b * 1.0 / j);
        }
    }
    for(int i = k;i <= n;++i) res = min(res,dp[i][x]);
    for(int i = k;i >= x;--i){
        sort(a + i + 1,a + n + 1);
        db sum = 0;
        for(int j = i + 1;j <= k;++j) sum += a[j];
        res = min(res,dp[i][x] + sum / (x + 1));
    }
    ans = min(ans,res);
}
int main(){
    // fre(a);
    n = in();
    k = in();
    for(int i = 1;i <= n;++i){
        q[i].a = in();
        q[i].b = in();
        if(q[i].b == -1) q[i].b = 1e9;
    }
    sort(q + 1,q + n + 1);
    for(int i = 0;i <= k;++i) work(i);
    printf("%.8lf",ans);
    return 0;
}
```

---

## 作者：duyi (赞：5)

[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/LOJ3664.html)


# LOJ3664 「JOI 2022 Final」选举

## 题目大意

[题目链接](https://loj.ac/p/3664)

有 $N$ 个州，每个州有两个参数：$A_i$, $B_i$，满足 $A_i\leq B_i$。

你在第 $i$ 个州演讲大于等于 $A_i$ 小时可以获得一张选票，演讲大于等于 $B_i$ 小时可以获得一位协作者（因为 $A_i\leq B_i$，获得协作者的同时意味着一定获得了选票）。有些 $B_i = -1$ 的州表示无法获得协作者。协作者可以帮你演讲，效果和你自己演讲一样。多个人可以同时在同一个州演讲，比如 $3$ 个人一起在某个州演讲了 $2$ 小时，就算 $6$ 个小时。

请求出获得 $K$ 张选票所需的最短时间。输出实数，要求误差不超过 $0.01$。

数据范围：$1\leq K\leq N\leq 500$，$1\leq A_i\leq 1000$，$A_i\leq B_i\leq 1000$ 或 $B_i = -1$。

## 本题题解

设我们最终在 $a$ 个州仅获得了选票，在 $b$ 个州获得了选票和协作者，在其余的 $c$ 个州里什么也没有得到。称这三种州分别为 $\texttt{A}$,$\texttt{B}$,$\texttt{C}$ 类州。显然，$a + b = K$, $a + b + c = N$。

假设我们已经确定了每个州的种类，如何安排演讲使用时最短呢？显然可以采用如下贪心策略：先按 $B_i$ 从小到大的顺序，在所有 $\texttt{B}$ 类州里演讲，则第 $i$ 个进行到的州将耗时 $\frac{B_i}{i}$ ($1\leq i\leq b$)。然后再在所有 $\texttt{A}$ 类州里演讲，第 $i$ 个州将耗时 $\frac{A_i}{b + 1}$（与顺序无关）。

不妨先将所有州按 $B_i$ 排好序。我们枚举 $b$，然后进行 DP。设 $\text{dp}(i, j, k)$ 表示考虑了前 $i$ 个州，总共获得了 $j$ 张选票，其中有 $k$ 个州获得了协作者。每个州有三种转移：要么不选（用时不变，转移到 $\text{dp}(i + 1, j, k)$），要么选择获得选票（用时增加 $\frac{A_{i + 1}}{b + 1}$，转移到 $\text{dp}(i + 1, j + 1, k)$），要么同时获得选票和协作者（用时增加 $\frac{B_{i + 1}}{k + 1}$，转移到 $\text{dp}(i + 1, j + 1, k + 1)$）。最后答案为 $\text{dp}(N, K, b)$。这个 DP 的时间复杂度是 $\mathcal{O}(N^3)$，因为外层还要枚举 $b$，总时间复杂度 $\mathcal{O}(N^4)$，无法通过。

这说明我们前面的贪心策略，研究得还不是很完备，需要继续观察问题本身的特性。不妨考虑最后两个 $\texttt{B}$ 类州，假设它们之间有一个 $\texttt{C}$ 类州，那么把最后一个 $\texttt{B}$ 类州和该 $\texttt{C}$ 类州的种类互换，一定能使答案更优（因为其它州的用时不变，而最后一个 $\texttt{B}$ 类州的用时减少了）。同理，可以证明任意两个 $\texttt{B}$ 类州之间都不存在 $\texttt{C}$ 类州，并且第一个 $\texttt{B}$ 类州前也没有 $\texttt{C}$ 类州。换言之，以最后一个 $\texttt{B}$ 类州为界，序列的前半部分只有 $\texttt{A}$ 或 $\texttt{B}$ 类州，后半部分只有 $\texttt{A}$ 或 $\texttt{C}$ 类州。

这个特性让我们可以优化原来的 DP。设 $\text{dp}_2(i, j)$ 表示考虑了前 $i$ 个州，选定了 $j$ 个 $\texttt{B}$ 类州，的最少用时。在这个 DP 中，$j = b$ 时我们不再让它往后转移，也就是它只计算到最后一个 $\texttt{B}$ 类州就停止，后半部分不归它管。DP 完成后，我们还需要在后半部分里选几个 $\texttt{A}$ 类州，显然直接选 $A_i$ 最小的若干个即可。具体来说，设后 $x$ 个州里，$A_i$ 最小的 $y$ 个州的 $A_i$ 之和为 $w(x, y)$。那么答案就是 $\min_{i = b}^{K}\{\text{dp}_2(i, b) + w(N - i, K - i)\}$。这个 DP 的时间复杂度是 $\mathcal{O}(N^2)$，$w$ 显然也可以在同样的复杂度内预处理出来。此外，外层还要枚举 $b$，所以总时间复杂度 $\mathcal{O}(N^3)$。

## 参考代码

[在本人博客查看](https://www.cnblogs.com/dysyn1314/p/LOJ3664.html)



---

## 作者：xs_siqi (赞：2)

模拟赛 T1。场上只会 $O(n^3\log n)$ 的做法。

这题其实有一个 $O(n^2\log n)$ 的做法。

首先一个结论是，众人拾柴火焰高，所有人肯定去一个地方演讲。因为天数可以是浮点数，那么去同一个地方演讲肯定不劣。并且可能存在一个人讲完然后还有一个人没讲的情况出现。所以感性理解一下，这个结论是对的。

那么我们明显有一个 $O(n^4)$ 的做法。贪心地将 $b$ 比较小的往前排，然后优先选 $b$ 比较小的作为协助者。但是要注意，可能存在 $b$ 比较小但是也排在前面，可其的 $a$ 更小的情况。这个时候优先选协助者反而更劣。此时我们可以将这个贪心方式和 dp 结合。

设 $f_{i,j,k}$ 表示考虑了前 $i$ 个人，有 $j$ 个地方拿协助者与选票，$k$ 个地方只拿选票，剩下地方什么都不拿。枚举最终协助者的总人数，然后大力转移即可。

然后我们会发现一个事情：随着 $l$ 递增，最终的最小值先减小后增加。单峰函数求峰值我们可以使用三分法。然后这样复杂度就降到了 $O(n^3\log n)$，但还是不足以通过本题。

稍微证明一下这个单峰正确性。因为你贪心的选择了前面的协助者，随着协助者的增加，你得到选票与协助者的速率会增加。

一个显然的结论是，如果上一次你选了 $l$ 个协助者，这次枚举到你要选 $l+1$ 个协助者，那么必然是从上一次的 $l$ 个协助者的基础上继续选下去的。

当你的速率与为了得到协助者所做的多余努力，达到饱和的时候，便就是峰值的出现时刻。此后做出的多余努力更多，但是增加的速率仍然是以 $1$ 递增，并且这个函数变缓幅度变小，重新上升。

那么回归正题，要如何把这个复杂度降成 $O(n^2\log n)$ 呢？首先，要想降低复杂度，那么显然是要把状态数先降下来。三维状态不可能在三次方以内转移。

可以这样考虑：我们设 $f_{i,j}$ 表示考虑前 $i$ 个地点，选取了 $j$ 个协助者的最小代价。

首先我们可以这样分割选择：肯定是首先选取一堆协助者+一堆票，然后选取一堆票+一堆不选。这个东西用贪心是好证的，因为你要选的 $b$ 只能在前面选，在后面的 $b$ 必然不优，这个前面就有提及。

所以我们用贪心的方式进一步优化了我们的 dp 转移。然后对于后面的 $k-i$ 个地点，只要拿到 $k-i$ 个选票即可。根据贪心思维，我们肯定优先选选票代价最低的 $k-i$ 个。这件事情我们直接排序然后后缀和预处理一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=505;
int n,k;
bool f1;
struct node{
	double x,y;
	friend bool operator < (node x,node y){
		if(x.y<0&&y.y<0)return x.x<y.x;
		if(y.y<0)return 1;
		if(x.y<0)return 0;
		return x.y==y.y?x.x<y.x:x.y<y.y;
	}
}a[maxn];
namespace Noel{
	double f[maxn][maxn],sum[maxn][maxn],t[maxn];
	void init(){
		for(int i=n;i>=1;i--){
			t[n-i+1]=a[i].x;
			sort(t+1,t+n-i+1+1);
			for(int j=1;j<=n-i+1;j++)
				sum[i][j]=sum[i][j-1]+t[j];
			for(int j=n-i+2;j<=n;j++)
				sum[i][j]=1e9;
		}
	} 
	double check(int l){
		double ans=10000000.0;
		for(int i=0;i<=n;++i)
			for(int j=0;j<=l;++j)
				f[i][j]=100000000.0;
		f[0][0]=0;
		for(int i=1;i<=n;++i){
			for(int j=0;j<=l;++j)
				f[i][j]=min(f[i][j],f[i-1][j]+a[i].x/(l+1));
			for(int j=1;j<=l;++j)
				if(a[i].y>=0.0)f[i][j]=min(f[i][j],f[i-1][j-1]+a[i].y/j);
		}
		for(int i=l;i<=n;i++)
			ans=min(ans,(f[i][l]+sum[i+1][k-i]/(l+1)));
		return ans;
	}
	double find(){
		double ans=2e9;
		int l=0,r=k;
		double k1=0,k2=0;
		while(l<r){
			int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
			k1=check(lmid),k2=check(rmid);
			if(k1<=k2)r=rmid-1;
			else l=lmid+1;
		}
		return min(k1,k2);
	}
}
bool f2;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	Noel::init();
	printf("%.6lf\n",Noel::find());
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：1)

**sol of P8162**

不会 $O(n ^ 2)$。

显然对于一个确定的方案先拿 $b$ 再拿 $a$ 是最优的。

考虑按 $b$ 从小到大排序然后贪心拿一个前缀的 $b$ 剩下的再后缀里找 $a$，会在两者的数量级相差很大时错掉，即对于一个前缀内部可能一些钦定的 $b$ 实际上只拿了 $a$。

但是我们会发现也不会出现一个前缀，后面有选 $b$ 但是前面有一个位置既没选 $a$ 也没选 $b$，因为此时让该没有贡献的位置选 $b$ 一定会不劣。而如果没有选 $b$ 又不能不选，就只能选 $a$ 了。

然后设 $dp_{i,j}$ 表示前 $i$ 个数有 $j$ 个选了 $b$ 其余 $i - j$ 个选了 $a$ 时一个前缀的最小花费，你就有一个看起来可以 $O(n ^ 2)$ 的做法，然后调了很久才发现是假的，但是应该是可行的只是我是滨滨。

放弃思考。发现其实可以写 $O(n ^ 3)$，索性最外层枚举一个最后有多少个数选了 $b$，内层还是做一个 $O(n ^ 2)$ dp 即可。

写一下方程以防小青蛙看不懂。

设 $dp_{i,j}$ 表示前 $i$ 个数有 $j$ 个选了 $b$ 其余 $i - j$ 个选了 $a$ 时一个前缀的最小花费，且此时知道目标状态有 $c$ 个数选了 $b$。

除去形如 $dp_{0,x}$ 的初始状态，所有状态下 $dp_{i,j} \leftarrow dp_{i - 1,j} + \frac{A_i}{c + 1}$。

若 $j \geq 1$，则 $dp_{i,j} \leftarrow dp_{i - 1,j - 1} + \frac{B_i}{j}$。

其实就是因为你的策略是确定的，选 $b$ 时的贡献是可以递推但选 $a$ 时的贡献需要由最终选择 $b$ 的位置的个数确定来做的。

同时每个 dp 对于答案的贡献还需要在后缀选 $k - i$ 个 $a$，这个贡献可以预处理。 

上述的更新取最小值，意义在按照 $b$ 从小到大排序的情况下。

时间复杂度 $O(n ^ 3)$，跪求 $O(n ^ 2)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 505;
const double Inf = 1e14;
struct Node
{
	double a,b;
	Node(){a = b = 0;}
	Node(double A,double B){a = A , b = B;}
	bool operator < (const Node &Ano) const
	{return b < Ano.b || (b == Ano.b && a < Ano.a);}
}kp[Len],pk[Len];
bool cmp(Node a,Node b){return a.a < b.a || (a.a == b.a && a.b < b.b);}
int n,k;
double dp[Len][Len],suf[Len][Len];
int main()
{
	scanf("%d %d",&n,&k);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%lf %lf",&kp[i].a,&kp[i].b);
		if(kp[i].b == -1) kp[i].b = Inf;
	}
	sort(kp + 1 , kp + 1 + n);
	for(int i = n ; i >= 1 ; i --)
	{
		int len = 0;
		for(int j = n ; j >= i ; j --) pk[++ len] = kp[j];
		sort(pk + 1 , pk + 1 + len , cmp);
		//if(i == 1) for(int j = 1 ; j <= len ; j ++) printf("%lf %lf\n",pk[j].a,pk[j].b);
		for(int j = 1 ; j <= len ; j ++) suf[i][j] = suf[i][j - 1] + pk[j].a;
	}
	double ans = Inf;
	for(int i = 0 ; i <= n ; i ++) 
		for(int j = 0 ; j <= n ; j ++) dp[i][j] = Inf;
	dp[0][0] = 0;
	for(int cs = 0 ; cs <= k ; cs ++)
		for(int i = 1 ; i <= k ; i ++)
			for(int j = 0 ; j <= i ; j ++)
			{
				dp[i][j] = Inf;
				if(!j) dp[i][j] = dp[i - 1][j] + kp[i].a / (cs + 1);
				else dp[i][j] = min(dp[i - 1][j] + kp[i].a / (cs + 1) , dp[i - 1][j - 1] + kp[i].b / j);
				if(j == cs) 
				{
					ans = min(ans , dp[i][j] + suf[i + 1][k - i] / (j + 1));
					//printf("%d %d %d %lf %lf\n",i,j,k - i,suf[i + 1][k - i],dp[i][j]+ suf[i + 1][k - i] / (j + 1));
				}
			}
	printf("%lf\n",min(ans , suf[1][k]));
	return 0;
}
```

---

## 作者：南阳刘子骥 (赞：1)

我们首先可以得出一些结论。

首先，我们不会浪费时间。因为演讲时间可以是浮点数，不需要考虑取整的问题，所以如果我们只需要选票的话，我们只会在这个州演讲 $A_i$ 的时间，不会多也不会少。

其次，我们可以将存在多个人同时在不同州演讲的情况转化为只有多个人同时在同一个州演讲的情况。所以我们只需要考虑当前人数和在哪个州演讲就可以了。

然后，我们可以确定我们的演讲顺序。对于一个已经确定了的计划（即每一个州的演讲时间已经确定），我们肯定首先在所有能拿到协作者的州演讲完拿到协作者之后再去其他州演讲。

最后，我们可以将所有的州分为三类，分别是“协作州”、“支持州”和“反对州”。“协作州”指拿到了选票和协作者的州，“支持州”指只拿到了选票的州，而“反对州”指什么也没有拿到的州。  
如果我们对所有的州按照 $B_i$ 为第一关键字，$A_i$ 为第二关键字来排序的话，我们可以发现，在最后一个“协作州”之前一定没有“反对州”。如果有的话，我们可以将两者调换一下位置，这样结果也不会变劣。

于是我们就可以想到一个 DP，$f_{i,j,k}$ 代表前 $i$ 个州中有 $j$ 个“协作州”，$k$ 个“支持州”的最小时间。  
同时根据上面的性质，我们可以忽略支持州，只枚举协作州，将 $O(n^3)$ 的 DP 优化到 $O(n^2)$。

代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, k;
struct State
{
	int a, b;
	bool operator < (const State &x)
	{
		return (~b && ~x.b) ? b < x.b : b>x.b;
	}
}p[N];
double f[N][N];
int tmp[N];
double get(int x)
{
	for(int i = 1; i <= n; i++)tmp[i] = p[i].a;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			f[i][j] = 1e9;
	f[0][0] = 0;//没有进行过任意一次演讲，耗时为 0
	double res = 1e9;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= min(x, i); j++)
		{
			f[i][j] = f[i - 1][j] + ((double)p[i].a / (x + 1));//不需要招协作者，就等到最后再演讲
			if(j >= 1 && p[i].b != -1)f[i][j] = min(f[i][j], f[i - 1][j - 1] + ((double)p[i].b / j));//需要招协作者，就立刻开始演讲罢
		}
	}
	for(int i = k; i <= n; i++)
		res = min(res, f[i][x]);
	for(int i = k - 1; i >= x; i--)
	{
		sort(tmp + i + 1, tmp + n + 1);
		double val = 0;
		for(int j = 1; j <= k - i; j++)val += tmp[i + j];
		res = min(res, f[i][x] + ((double)val / (x + 1)));//加上只要选票的耗时
	}
	return res;
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].a, &p[i].b);
	sort(p + 1, p + 1 + n);
	double ans = 1e9;
	for(int i = 0; i <= k; i++)//枚举招募协作者的数量
		ans = min(ans, get(i));
	printf("%.15lf\n", ans);
	return 0;
}
```



---

## 作者：FZzzz (赞：1)

~~考场上想了一个多小时，没救了。~~

~~题面里有一句日语原文是“大統領選挙に出馬する理恵さん”，是不是看着就很中二。~~

首先有两个很直观的结论，一是不可能同时在不同地方演讲，二是到过一个州以后就不可能再去一次。然后重写一下问题：
>有 $n$ 个元素，从中选出 $k$ 个并排序。有一个变量 $c=0$，依次对每个元素 $i$ 决策：付出 $\dfrac{a_i}c$ 的代价，或付出 $\dfrac{b_i}c$ 的代价使 $c$ 增加 $1$。

再发现更多性质。选第二种决策的元素一定在所有第一种元素之前，第二种元素肯定按 $b$ 排序，第一种元素的 $a$ 比没选的元素要小。证明都可以考虑调整，也都比较显然。

把所有元素按 $b$ 排序，枚举选了多少个第二种，设计一个 dp。dp 时要记录选到了哪一位，选了多少第二种和多少第一种，转移时考虑这一位是第二种第一种还是不选。这样单次 dp 是 $O(n^3)$，总共是 $O(n^4)$。听说答案关于第二种个数是单峰的，二分一下可以 $O(n^3\log n)$。

考虑怎么砍掉一维。再发现一个性质是按 $b$ 排序后最后一个第二种前面一定没有没选的，不然把一个第二种挪到前面去不劣。那就可以不用记录选了多少第一种，而是在 dp 到每个位置时假设当前是最后一个第二种，把后面最小的若干个 $a$ 加上即可。

这个加上二分可以 $O(n^2\log n)$，下面代码是 $O(n^3)$ 的。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=500+5;
int n,k,ord1[maxn],p[maxn],ord2[maxn];
double a[maxn],b[maxn];
const double inf=1/0.0;
double f[maxn],ans=0;
void solve(int m){
	for(int i=1;i<=m;i++) f[i]=inf;
	f[0]=0;
	for(int i=1;i<=k;i++){
		int u=ord1[i];
		for(int j=m;j>0;j--)
			f[j]=min(f[j-1]+b[u]/j,f[j]+a[u]/(m+1));
		f[0]+=a[u]/(m+1);
		int cnt=0;
		double res=f[m];
		for(int j=1;cnt<k-i;j++) if(p[ord2[j]]>i){
			res+=a[ord2[j]]/(m+1);
			cnt++;
		}
		ans=min(ans,res);
	}
}
int main(){
	freopen("election.in","r",stdin);
	freopen("election.out","w",stdout);
	n=read();
	k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
		if(b[i]<0) b[i]=inf;
	}
	for(int i=1;i<=n;i++) ord1[i]=ord2[i]=i;
	sort(ord1+1,ord1+n+1,[](int x,int y){
		return b[x]<b[y];
	});
	for(int i=1;i<=n;i++) p[ord1[i]]=i;
	sort(ord2+1,ord2+n+1,[](int x,int y){
		return a[x]<a[y];
	});
	for(int i=1;i<=k;i++) ans+=a[ord2[i]];
	for(int i=1;i<=k;i++) solve(i);
	printf("%.15f\n",ans);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：Delov (赞：0)


错误的贪心就是枚举选几个协作州，然后贪心把小的都拿了，剩下的支持州挑小的。  
可能会出现某个协作州的 $b$ 小，但是 $a$ 更小，导致将他与某个支持州交换反而更优。  

于是需要 dp，考虑我们要选出 $p$ 个支持州，设 $f_{i,j}$ 表示在前 $i$ 个州里，选出 $j$ 个协作州的最小时间，我们发现前 $i$ 个州是不可能不选的，要么是协作州，要么是支持州。因为如果有一个州没选，那么我把其后选的一个协作州换成它显然更优。于是还是枚举协作州的数量，然后做一次 dp，统计答案时枚举最后一个协作州是谁，然后从它之后的州里贪心的选 $a$ 小的即可。一次 dp 的复杂度为 $O(n^2)$，套上一层枚举，复杂度为 $O(n^3)$。

### Code

```cpp


#include <bits/stdc++.h>
typedef long long ll;typedef unsigned long long ull; typedef double db;typedef long double ldb;
#define fre(x) freopen(#x ".in","r",stdin),freopen(#x ".out","w",stdout)
#define Rep(i,a,b) for(int i=a;i<=b;++i) 
#define Dwn(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define mair make_pair
#define fir first
#define sec second
using namespace std;

const int maxn=5e2+10,INF=1e9;
const double eps=1e-4;


int n,K,mx;

struct Ver{double a,b;}E[maxn];

bool cmp1(const Ver &x,const Ver &y){return x.b<y.b;}
bool cmp2(const Ver &x,const Ver &y){return x.a<y.a;}

double pre[maxn];
double f[maxn][maxn];
double ans=INF;

multiset<double>S,rec;

void Get(int Te){
	Rep(i,0,n)Rep(j,0,n)f[i][j]=INF;
	f[0][0]=0;
	Rep(i,1,K){
		Rep(j,0,min(Te,i)){
			f[i][j]=min(f[i][j],f[i-1][j]+E[i].a/(Te+1));
			if(j>=1 && abs(E[i].b-INF)>eps)f[i][j]=min(f[i][j],f[i-1][j-1]+E[i].b/j);
		}
	}
	S=rec;
	Dwn(i,K,0){
		double te=0;
		auto it = S.begin();
		Rep(j,i+1,K)te+=(*it),++it;
		ans=min(ans,f[i][Te]+te/(Te+1));
		S.insert(E[i].a);
	}
}

void solve(){
	cin>>n>>K;
	Rep(i,1,n){ cin>>E[i].a>>E[i].b; if(E[i].b==-1)E[i].b=INF;else ++mx; } 
	sort(E+1,E+n+1,cmp1);
	Rep(i,K+1,n)rec.insert(E[i].a);
	Rep(i,0,min(K-1,mx))Get(i);
	cout<<fixed<<setprecision(10)<<ans<<"\n";
}

int main (){ ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);return solve(),0; }


```


---

