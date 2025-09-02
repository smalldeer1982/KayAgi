# [CCC 2020]  Swapping Seats

## 题目描述

有 $N$ 个人坐在一张**圆**桌旁。

共有三个派别，每一个人属于一个派别。

现在，您想使属于同一派别的人坐到一起。

您可以每次将两个人交换位置，输出最小的交换次数。

## 说明/提示

#### 样例解释
$\texttt{BABCBCACCA}\to\texttt{AABCBCBCCA}\to\texttt{AABBBCCCCA}$。

#### 子任务
**本题采用捆绑测试，且本题的 Subtask 分数有微调。**
- Subtask 1（$26$ 分）：$s_i\in\{$`A`$,$`B`$\}$ 且 $N\le 5\times 10^3$。
- Subtask 2（$27$ 分）：$s_i\in\{$`A`$,$`B`$\}$。
- Subtask 3（$27$ 分）：$N\le 5\times 10^3$。
- Subtask 4（$20$ 分）：无特殊限制。

对于 $100\%$ 的数据，保证 $s_i\in\{$`A`$,$`B`$,$`C`$\}$，$1\le N\le 10^6$。

#### 说明
本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Senior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/seniorEF.pdf) T4 Swapping Seats。

## 样例 #1

### 输入

```
BABCBCACCA```

### 输出

```
2```

# 题解

## 作者：gznpp (赞：6)

本题解在博客页面显示正常。

原题链接：<https://dmoj.ca/problem/ccc20s4>

CCC 2020 题组：<https://cemc.math.uwaterloo.ca/contests/computing/2020/ccc/seniorEF.pdf>

本题解默认排序为从小到大排。


题意：给定一个 $N$ 元环，环上值域只有 $3$，现要求值相同的元素必须在环上相邻，求最少交换次数。

首先，考虑一下交换次数问题。

可以看看 USACO Training 的 Sorting a Three-Valued Sequence 这题，洛谷 [P1459](https://www.luogu.com.cn/problem/P1459)。

记：不在 排序之后 $d$ 的范围的 $d$ 的个数为 $Non_d$。如 `1 3 2 1` 中 $Non_1 = 1, Non_2 = 0, Non_3 = 1$；

记：在排序之后 $f$ 的范围的 $e$ 的个数为 $Num_{e, f}$。如 `1 3 1 2` 中 $Num_{1, 3} = 0, Num_{3, 1} = 1, Num_{1, 1} = 1$。

它启示我们：

值域仅为 $2$ 的排序，交换次数就是：$Non_1 = Non_2 = Num_{1, 2} = Num_{2, 1}$。我们本应该大动干戈把不在范围中的 $1$ 和 $2$ 全都交换到应该在的位置，答案为 $Non_1 + Non_2$；但这是交换，可以省下 $\min(Num_{1, 2},  Num_{2, 1})$ 的操作次数。因为 $1, 2$ 之间交换，换好一个 $2$ 的同时就把一个 $1$ 换好了。故正确答案为 $Non_1 + Non_2 - \min(Num_{1, 2},  Num_{2, 1})$，也就是前面那一堆。

推广到值域为 $3$ 的排序，交换次数还是：$Non_1 + Non_2 - \min(Num_{1, 2} + Num_{2, 1})$。$3$ 跟 $1, 2$ 交换当然能省次数，但是我们只用考虑 $1$ 跟 $2$ 换好就行了，因为这样 $3$ 一定换好了。

又因为这是个环，所以枚举 $1$（这里是 `A`）的起始位置，同时破环成链用前缀和维护前 $i$ 个元素中分别有多少个 `A, B, C` 即可。注意还要讨论一下 `A` 后面跟的是 `B` 还是 `C`，因为本题 `A, B, C` 的排列顺序不定。时间复杂度 $O(n)$。

这里还有一个小技巧，同时可以拓展一下思维。我们可以稍微化简一下式子。（这里 `B` 和 `C` 是对称的，只写一个）

$$
\begin{aligned}
& Non_A + Non_B - \min(Num_{A, B} + Num_{B, A})\\
=& Num_{A, B} + Num_{A, C} + Num_{B, A} + Num_{B, C} - \min(Num_{A, B} + Num_{B, A})\\
=& \max(Num_{A, B} + Num_{B, A}) + Num_{A, C} + Num_{B, C}\\
=& \max(Num_{A, B} + Num_{B, A}) + Non_C
\end{aligned}
$$

可以稍微简化一点代码。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000002;
int n, sa[maxn], sb[maxn], sc[maxn], suma, sumb, sumc, ans = INT_MAX;
char a[maxn];

int mo(int x) { return x % (n + 1) + 1; }

signed main() {
	scanf("%s", a + 1); n = strlen(a + 1);
	for (int i = n + 1; i <= (n << 1); ++i)
		a[i] = a[i - n];
	for (int i = 1; i <= n; ++i)
		if (a[i] == 'A') ++suma;
		else if (a[i] == 'B') ++sumb;
		else ++sumc;
	for (int i = 1; i <= (n << 1); ++i) {
		sa[i] = sa[i - 1] + (bool)(a[i] == 'A');
		sb[i] = sb[i - 1] + (bool)(a[i] == 'B');
		sc[i] = sc[i - 1] + (bool)(a[i] == 'C');
	}
	for (int i = 1; i <= n; ++i) { // positions for A begins
		int nx1 = i + suma, nx2;
		// B is next
		nx2 = nx1 + sumb;
		ans = min(ans, max(sb[nx1 - 1] - sb[i - 1], sa[nx2 - 1] - sa[nx1 - 1]) + sumc - sc[i + n - 1] + sc[nx2 - 1]);
		// C is next
		nx2 = nx1 + sumc;
		ans = min(ans, max(sc[nx1 - 1] - sc[i - 1], sa[nx2 - 1] - sa[nx1 - 1]) + sumb - sb[i + n - 1] + sb[nx2 - 1]);
	}
	return cout << ans << endl, 0;
}
```

参考 DMOJ 官方题解：<https://dmoj.ca/problem/ccc20s4/editorial>

---

## 作者：Y_ATM_K (赞：5)

[题面](https://www.luogu.com.cn/problem/P6709)

## 分析

上来先考虑简化的问题：只有 $\texttt{A,B}$ 且是一条链的情况。只要统计序列中 $\texttt{A,B}$ 的数量，把序列分成 $\texttt{A,B}$ 两组，交换次数就是 $\texttt{A}$ 组中 $\texttt{B}$ 的数量。

然后变成一个环，因为上面做法可以用前缀和预处理，单次是 $O(1)$ 的，所以只要枚举 $\texttt{A}$ 组左端点，即枚举每种分组方案，分别统计，这样是 $O(N)$ 的。

原问题就类似上面的做法，把 $\texttt{A,B,C}$ 分组，因为我们枚举了 $\texttt{A}$ 组左端点，那么分组方案就是 $\texttt{ABC}$ 和 $\texttt{ACB}$ 两种。

问题是如何统计最少交换次数。以分成 $\texttt{ABC}$ 为例。

我们假设有 $\texttt{A}$ 组中有 $s_1$ 个 $\texttt{B}$，$s_2$ 个 $\texttt{C}$，$\texttt{B}$ 组中有 $s_3$ 个 $\texttt{A}$，$s_4$ 个 $\texttt{C}$。

我们先把 $\texttt{A}$ 组中的 $\texttt{B,C}$ 交换出去，显然的贪心策略是尽量把 $\texttt{B}$ 换到 $\texttt{B}$ 组。这里交换了 $s_1+s_2$ 次。


如果 $s_3 \le s_1$，那么交换后 $\texttt{B}$ 组中 $\texttt{C}$ 数量不变，$\texttt{B,C}$ 组交换的次数是 $s_4$。

否则，交换后 $\texttt{B}$ 组中 $\texttt{C}$ 多了 $s_3-s_1$ 个，$\texttt{B,C}$ 组交换次数是 $s_4+s_3-s_1$。

分成 $\texttt{ACB}$ 的方案同理。

时间复杂度 $O(N)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define N 2000005
using namespace std;
int n,ans=1e9,sa[N],sb[N],sc[N];char s[N];
#define A(x,y) (sa[y]-sa[x-1])
#define B(x,y) (sb[y]-sb[x-1])
#define C(x,y) (sc[y]-sc[x-1])
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i) {
		sa[i]=sa[i-1]+(s[i]=='A');
		sb[i]=sb[i-1]+(s[i]=='B');
		sc[i]=sc[i-1]+(s[i]=='C');
	}
	for(int i=1;i<=n;++i) {
		sa[i+n]=sa[i+n-1]+(s[i]=='A');
		sb[i+n]=sb[i+n-1]+(s[i]=='B');
		sc[i+n]=sc[i+n-1]+(s[i]=='C');
	}
	for(int i=1;i<=n;++i) {
		int s1=B(i,i+sa[n]-1),s2=C(i,i+sa[n]-1),s3=A(i+sa[n],i+sa[n]+sb[n]-1),s4=C(i+sa[n],i+sa[n]+sb[n]-1);
		ans=min(ans,s1+s2+s4+(s3>s1?s3-s1:0));
		s1=B(i,i+sa[n]-1),s2=C(i,i+sa[n]-1),s3=A(i+sa[n],i+sa[n]+sc[n]-1),s4=B(i+sa[n],i+sa[n]+sc[n]-1);
		ans=min(ans,s1+s2+s4+(s3>s2?s3-s2:0));
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Melo_qwq (赞：2)

好题。

提供一种和 [PZY0415](https://www.luogu.com.cn/user/149031) 大佬思路相仿的题解。将会侧重于证明正确性，不依赖于两个种类的部分。

首先发现一件事情，当我们把环转换成链的形式的时候，合法方案要么形如 ``CCCBBBAAA``，要么形如 ``ACCCBBBAA``，也就是说，除了在链首尾的种类之外，剩下的两个种类应该是连续在一起的，并且不会跨越链首和链尾，就是例子中的 ``CCCBBB``。

发现了这一点之后我们不难想到去枚举这两种连续的种类和他们的起点。

假设我们要凑成 ``ACCCBBBAA`` 的形式，那么我们要做的就是对于原始的字符串，把第 $2$ 到 $4$ 个位置的不是 ``C`` 的东西扔了把 ``C`` 换过来，第 $5$ 到 $7$ 个位置的 ``B`` 同理。

考虑如何求出最小数目，我们不妨以 ``ACCCBBBAA`` 为例，那么我们枚举的是种类 ``B`` 和 ``C``，他们的起点是第二个位置。那么我们要进行的操作就是交换一些字符使得满足题意，注意到我们并不用去管种类 ``A``，因为其余两个种类搞好之后它一定自然而然的排好了。

一个不显然的贪心策略是首先把 ``C`` 中的 ``B`` 和 ``B`` 中的 ``C`` 交换。下面口胡证明。

注意到对于我们任意的交换操作，每一次**可能**只能新增一个符合答案的位置，**至多**增加两个，同时我们的贪心策略**保证**可以增加两个，一定不劣。

这种贪心操作最多进行位置 $2$ 到 $4$（也就是 ``C`` 的位置）中的 ``B`` 的个数和位置 $5$ 到 $7$ 中的 ``C`` 的个数的较小者。

其余只能老老实实地一次一次交换了。

可以利用前缀和优化。

其余看代码：


```cpp
inline int calc (int l ,int r ,int t) {
	return sum[r][t] - sum[l - 1][t] ;
}
inline void query (int st ,int t1 ,int t2) {
	if (st + tot[t1] + tot[t2] - 1 > n) return ; // st + t1 + t2 - 1 是结尾 
	int sum = min (calc (st ,st + tot[t1] - 1 ,t2) ,calc (st + tot[t1] ,st + tot[t1] + tot[t2] - 1 ,t1)) ; // 就是我说的贪心的最多操作次数
	int op1 = tot[t1] - calc (st ,st + tot[t1] - 1 ,t1) - sum ,op2 = tot[t2] - calc (st + tot[t1] ,st + tot[t1] + tot[t2] - 1 ,t2) - sum ; // 贪心完两个位置还需要多少交换
	return (void) (ans = min (ans ,op1 + op2 + sum)) ; // 记得加上贪心的操作数 
}
f (i ,1 ,n ,1) {
	char ch = c[i] ;
	int num = ch - 'A' ;
	f (j ,0 ,2 ,1) sum[i][j] = sum[i - 1][j] ;
	sum[i][num] ++ ;
}
f (i ,0 ,2 ,1) tot[i] = sum[n][i] ;
f (i ,1 ,n ,1) {
	f (j ,0 ,2 ,1) {
		f (k ,0 ,2 ,1) {
			if (j == k) continue ; 
			query (i ,j ,k) ;
		}
	}
} // 枚举遍历纳那两个种类以及开头
```

---

## 作者：Nero_Claudius (赞：2)

这道题有一定思维性，可以一层层加限制条件来思考。

首先答案肯定是可以断环的，那么我们先考虑简单一点的线性情况。

然后为了进一步简化，先研究更简单的两派别情况。

## 线性+两派别

显然，完成了交换之后肯定是$A$聚集在一起，$B$聚集在一起。如果已经知道结束情况下$A$聚集的区间，那么只需要把这个区间里所有$B$扔出去就是最小次数。但问题是我们不知道。

所以可以考虑枚举$A$完成情况下的区间。统计$B$的数量显然可以使用前缀和完成。这个复杂度是$O(n)$的。

## 线性+三派别

接下来把问题拓展到三个派别。这比两派别稍复杂一些。

假设我们思路和原来完全一样，那么先枚举$A$的区间。但是接下来发现我们不知道$A$区间里的$B$和$C$具体是怎么扔出去的，所以会影响接下来的处理。在简单一些的情况里只有一种杂质（$B$），所以不影响答案。

经过思考，可以想到：在确定了一个区间的位置后，所有区间的位置都（几乎）是确定的。这里需要分两种情况讨论，即答案是$A+B+C$还是$A+C+B$。由对称性原理可知不需要考虑$B$开头和$C$开头的情况。

先看$A+B+C$。一种自然的想法是，$A$区间中混杂的所有$B$都尽量与$B$区间里的$A$交换。然后剩下的内容就和简单一些的情况完全一致了。

用稍微形式化一些的语言描述：

设$A$区间中的$B,C$数量为$tmpb,tmpc$。$B$区间中$A,C$数量为$ainnext,cinnext$。$C$区间中的则是$aainnext,binnext$。

将$A$区间中的杂质剔除是$tmpb+tmpc$。

$B$区间中可以省去的步数是$min(ainnext,tmpb)$，$B$区间总共需要$ainnext-min(ainnext,tmpb)$。

$B$区间剩下的$C$需要的步数$cinnext$。

将另外一种情况也加入，总共是$tmpb + tmpc + min(ainnext - min(ainnext, tmpb) + cinnext,aainnext - min(aainnext, tmpc) + binnext)$。

## 环形+三派别

显然，只要断环成链就行了。

## 代码

```cpp
/*
By Nero Claudius Caeser Augustus Germanicus,
Imeratorum Romanorum.
*/
#include <bits/stdc++.h>

using namespace std;

namespace StandardIO {

template <typename T>
void read(T &x) {
    x = 0;
    T f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T>
void write(T x) {
    if (x < 0)
        putchar('-'), x *= -1;
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}
}
using namespace StandardIO;

namespace Project {

const int N = 2000000 + 10;

int n, f1, f2, f3, c1, c2, c3, ans = 2147483647;
char s[N];
int e[N], f[N], g[N];

void MAIN() {
    cin >> s + 1;
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        s[i + n] = s[i];
        if (s[i] == 'A')
            f1 = 1, ++c1;
        else if (s[i] == 'B')
            f2 = 1, ++c2;
        else
            f3 = 1, ++c3;
    }
    for (int i = 1; i <= 2 * n; ++i) {
        e[i] = e[i - 1] + (s[i] == 'B');
        f[i] = f[i - 1] + (s[i] == 'C');
        g[i] = g[i - 1] + (s[i] == 'A');
    }
    for (int i = 1; i <= n; ++i) {
        int tmpb = e[i + c1 - 1] - e[i - 1];
        int tmpc = f[i + c1 - 1] - f[i - 1];
        int ainnext = g[i + c1 + c2 - 1] - g[i + c1 - 1];
        int cinnext = f[i + c1 + c2 - 1] - f[i + c1 - 1];
        int aainnext = g[i + c1 + c3 - 1] - g[i + c1 - 1];
        int binnext = e[i + c1 + c3 - 1] - e[i + c1 - 1];
        //				cout<<i<<endl<<"    ";
        //				cout<<tmpb<<' '<<tmpc<<' '<<ainnext<<' '<<cinnext<<endl;
        ans = min(ans, tmpb + tmpc + min(ainnext - min(ainnext, tmpb) + cinnext,
                                         aainnext - min(aainnext, tmpc) + binnext));
    }
    write(ans);
}
}

int main() {
    freopen("seat.in", "r", stdin);
    freopen("seat.out", "w", stdout);
    Project::MAIN();
}
```

---

## 作者：PZY0415 (赞：2)

学校模拟赛$T1$

~~关于不读题~~，一看题目就以为是相邻交换，类似树状数组求逆序对的题

结果发现是交换任意两个的位置$OTZ$

# **进入正题**

首先我们注意到这题的派别只有$3$种$A,B,C$

考虑最终情况，一定是有至少两个派别连续排列在一起，然后由于环的特性

第三个派别在首尾两段也是合法的

# **问题分析**


#### 观察$subtask2$，只有$A,B$两种

若确定了最终排列情况，如$BBAAAAABB$

那么对于区间$[3,7]$我们就需要把非$A$的全都扔出去，则此时$ans$就是区间非$A$的数量

这样子做法就是枚举一遍起始点，然后$O(1)$算非$A$数量求最小值

---

#### 对于$all$ $task$

先考虑$ABC$全排列$6$种情况，对于一种排列$CAB$，则令$CA$是完整在$1-n$区间内的连续排序

然后对于$CA$进行求解，枚举起始点，因为区间值都是固定的，所以可以直接求出当前起始点下，每个派别的区间

接下来例如上述思路，在$C$,$A$中要把非$C$，非$A$的扔出去

但是根据贪心，$C$与$A$中可以互换$AC$使得次数更少

那么减去互换的次数$min($ $C$ 中 $A$ , $A$ 中 $C$ $)$即为答案

$eg:$

```cpp
void solve(int x,int tag,int tag2){
	if(x+tot[tag]+tot[tag2]-1>n)return;
	int i=x+tot[tag]-1,j=i+tot[tag2];
	int oth1=i-x+1-calc(x,i,tag);
	int oth2=j-i-calc(i+1,j,tag2);
	ans=min(ans,oth1+oth2-min(calc(x,i,tag2),calc(i+1,j,tag)));
}

```

$the Last:$ 关于区间数量显然用$3$个前缀和就可以解决:

```#define calc(l,r,x) (sum[r][x]-sum[l-1][x])```

---

# 代码如下

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define gc getchar()
#define idg(ch) isdigit(ch)
#define N 1000010
using namespace std;

inline void read(int &x,int f=1){
	x=0;char ch=gc;
	while(!idg(ch))f=ch=='-'? -1:1,ch=gc;
	while(idg(ch))x=(x<<3)+(x<<1)+ch-'0',ch=gc;
	x*=f;
}

int n,ans=19260817;
int be[N<<1],sum[N][3],tot[3];

char str[N];

#define calc(l,r,x) (sum[r][x]-sum[l-1][x])

void solve(int x,int tag,int tag2){
	if(x+tot[tag]+tot[tag2]-1>n)return;
	int i=x+tot[tag]-1,j=i+tot[tag2];
	int oth1=i-x+1-calc(x,i,tag);
	int oth2=j-i-calc(i+1,j,tag2);
	ans=min(ans,oth1+oth2-min(calc(x,i,tag2),calc(i+1,j,tag)));
}

void init(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++){
		be[i]=str[i]-'A';
	}
	for(int i=1;i<=n;i++){
		sum[i][0]=sum[i-1][0];
		sum[i][1]=sum[i-1][1];
		sum[i][2]=sum[i-1][2];
		sum[i][be[i]]++;
	}
	tot[0]=sum[n][0],tot[1]=sum[n][1],tot[2]=sum[n][2];
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				if(j==k)continue;
				solve(i,j,k);
			}
		}
	}
	printf("%d\n",ans);
}

int main(){
//	freopen("seat.in","r",stdin);
//	freopen("seat.out","w",stdout);
	init();
}
```


---

## 作者：JK_LOVER (赞：1)

## 题意
圆桌上有一串由 $A,B,C$ 组成的字符串，求问最少做几次交换可以使每一类字母在一起。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p6709)
## 分析
像这种交换，直接考虑贪心。根据套路先破环成链。那么问题转化为在一个长度为 $2n$ 的串上，找到一个任意一个长度为 $n$ 的串字母在一起的最小次数。

- 先考虑排列，是 $A,B,C$ 还是 $A,C,B...$ 这个直接用手模拟只有 $6$ 种情况。

- 再考虑交换方式，如果应该是 $A$ 的地方出现了 $B$ ，而又刚好 $B$ 的地方出现了 $A$ ，那么直接交换是最优的。

- 那如果没有这样的情况，那么我们可以先交换这两个，根据抽屉原理，一定又出现了上述情况，可以直接交换。 这样就是 $2$ 次交换完成了 $3$ 个字母的操作。

那么我们可以做个前缀和维护一下序列的字母的个数。时间复杂度为 $O(3!\times n)$ 。
~~思维难度还是有一点的。~~
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6+100;
char ch[N];
int sum[N][3],len,ans = 0x3f3f3f3f;
void solve(int a,int b,int c,int l,int r)
{
	int Ans1 = 0,Ans2 = 0,A,B,C,dp[3][3]={0};
	A = sum[r][a] - sum[l-1][a];
	dp[a][c] = (sum[l-1+A][c] - sum[l-1][c]);
	dp[a][b] = (sum[l-1+A][b] - sum[l-1][b]);
	B = sum[r][b] - sum[l-1][b];
	dp[b][c] = (sum[l-1+A+B][c] - sum[l-1+A][c]);
	dp[b][a] = (sum[l-1+A+B][a] - sum[l-1+A][a]);
	C = sum[r][c] - sum[l-1][c];
	dp[c][a] = (sum[l-1+A+B+C][a] - sum[l-1+A+B][a]);
	dp[c][b] = (sum[l-1+A+B+C][b] - sum[l-1+A+B][b]);
	int mi1,mi2,mi3;
	mi1 = min(dp[a][b],dp[b][a]);mi2 = min(dp[a][c],dp[c][a]);mi3 = min(dp[c][b],dp[b][c]);
	Ans1 += mi1;dp[a][b] -= mi1,dp[b][a] -= mi1;
	Ans1 += mi3;dp[c][b] -= mi3,dp[b][c] -= mi3;
	Ans1 += mi2,dp[a][c] -= mi2,dp[c][a] -= mi2;
	Ans2 = dp[a][b] + dp[b][a] + dp[a][c] + dp[c][a] + dp[b][c] + dp[c][b];
//	cout<<Ans1<<" "<<Ans2<<endl;
	ans = min(ans,Ans1+Ans2*2/3);  
}
int main()
{
	scanf("%s",ch+1);
	len = strlen(ch+1);
	for(int i = 1;i <= len*2;i++)
	{
		sum[i][0] = sum[i-1][0] + (ch[(i-1)%len+1] == 'A');
		sum[i][1] = sum[i-1][1] + (ch[(i-1)%len+1] == 'B');
		sum[i][2] = sum[i-1][2] + (ch[(i-1)%len+1] == 'C');
//		cout<<sum[i][0]<<endl;
	}
	for(int i = 1;i <= len;i++)
	{
		solve(0,1,2,i,i+len-1);
		solve(0,2,1,i,i+len-1);
		solve(1,0,2,i,i+len-1);
		solve(1,2,0,i,i+len-1);
		solve(2,1,0,i,i+len-1);
		solve(2,0,1,i,i+len-1);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：wbs200 (赞：0)

做法：破环成链，三值排序。

依题意，我们每次以 $i$ 为初点，破环成链后，在环上 `ABC` 只有两种顺序，分别是 `ABC` 和 `ACB`。所以只要将任意两段排好，则另一个会自然排好。

考虑对 `A` 段开始的索引 $i$ 进行枚举，则 `[i, i + num_A]` 区间内必须都是 `A`，对于不是 `A` 的字母，必须通过交换将其移出。设环上非 `A` 的元素为 `!A`，则至少需要 `!A` 次交换，才能将 `[i, i + num_A)` 内的元素全部变为 `A`。

接下来，`A` 段下一段要么是 `B` 段，要么是 `C` 段。我们以 `B` 段举例，同理，需要 `!b` 次交换将 `B` 段变成全 `B`，其中 `!B` 表示环上非 `B` 的元素。`A`、`B` 段都排好了，`C` 显然也聚集到了一起。

但这里有一个问题：将 `A` 段中所有其它字符交换出去和将 `B` 段中所有其它字符交换出去时，这两段操作显然有重复。而对于 `A` 中的 `B`，可以与 `B` 中的 `A` 交换，这样就能省一次交换操作。因此最少的交换次数为 `!A + !B - min(a_b, b_a)`，其中 `a_b` 和 `b_a` 表示多枚举的部分。

参考代码如下：
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#define x first
#define y second
using namespace std;

const int N = 2e6 + 10;
int n;
char str[N];
int s[4][N], cnt[4];

int get(pair<int, int> p, int t)
{
    return s[t][p.y - 1] - s[t][p.x - 1];
}

int solve(int u, int a, int b, int c)
{
    int x = cnt[a], y = cnt[b], z = cnt[c];
    pair<int, int> A(u, u + x), B(u + x, u + x + y), C(u + x + y, u + n);
    int res = get(A, a) + get(B, b) + get(C, c);
    res += min(get(A, b), get(B, a));
    res += min(get(A, c), get(C, a));
    res += min(get(B, c), get(C, b));
    res += get(A, b) + get(B, a) - 2 * min(get(A, b), get(B, a));
    return n - res;
}

int main()
{
    cin >> str + 1;
    n = strlen(str + 1);
    memcpy(str + 1 + n, str + 1, n);
    for (int i = 1; i <= n * 2; i++)
    {
        int t = 0;
        if (str[i] == 'B') t = 1;
        else if (str[i] == 'C') t = 2;
        for (int j = 0; j < 3; j++) s[j][i] = s[j][i - 1];
        s[t][i]++;
        if (i <= n) cnt[t]++;
    }
    int ans = n;
    for (int i = 1; i <= n; i++)
        ans = min(ans, min(solve(i, 0, 1, 2), solve(i, 0, 2, 1)));
    cout << ans << endl;
    return 0;
}
```

---

## 作者：counselor (赞：0)

# 题意

给定一个 $n$ 元环，环上元素只有 $A$、$B$、$C$ 三种，求将同类字母放一起的最少交换次数

# 题目分析
1. 交换任意两个的位置
2. 只有三种类型
3. 由于是环，所以类型在首尾两段也是合法情况

# 问题分析

题目只有三种类型，我们自然想到将序列分成三个部分，分别由 $A$、$B$、$C$ 组成

因为 $A$、$B$、$C$ 有六种排列，这里就用 $A$、$B$、$C$ 这种排列来说

若统计出 $A$、$B$、$C$ 的个数后，用个数来作为部分的分界，那么就会想到将问题转化成 $A$ 部分里有多少个不匹配的，也就是 $B$、$C$ 的个数，通过交换来完成匹配， $B$ 部分、 $C$ 部分同理。

分析情况，我们发现其实只有两种情况，（其他同种情况其实都在轮换当中解决了）

   1. $A$ 中有 $B$ ，$B$ 中有 $C$ ，$C$ 中有 $A$ ，此时的交换的次数由什么决定呢？
      显然是 $A$ 、 $B$ 部分中失配个数最少的那个。（不然都没有失配你给人家交换岂不是没有道理）
      
      设 $A$ 部分中有 $x1$ 个 $B$ ， $B$ 部分中有 $y2$ 个 $C$ ，记 $t$ = min（x1，y2） 则交换次数为 $t$ ，此时可以推出， $C$ 部分中必然会有 $t$ 个 $A$ ，这 $t$ 个 $A$ 就可以在这种情况的交换下完成
   
      所以有结论：这 $3*t$ 的失配可以用 $2*t$ 次交换来完成
   
2.  $A$ 中有 $B$ ，$B$ 中有 $A$ ， $C$ 中只有 $C$ ，那么这种情况仅需将 $A$ 与 $B$ 互换，同时因为 $ABC$ 的排列顺序，交换次数还要除以 $2$ 

	## 核心代码
    ```cpp
	int cal(){
	int S=cnt[0][1]+cnt[0][2]+cnt[1][0]+cnt[1][2]+cnt[2][0]+cnt[2][1];
	int t=abs(cnt[0][1]-cnt[1][0]);
	return (S-t*3)/2+t*2;
	}
	```
   其他的细节都已经在代码注释里了~~
    
# 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1000005
using namespace std;
int n;
string s;
int num[maxn];
int lunhuan[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
int a[maxn],col[maxn],cnt[3][3];
int ans;
int cal(){
	int S=cnt[0][1]+cnt[0][2]+cnt[1][0]+cnt[1][2]+cnt[2][0]+cnt[2][1];
	int t=abs(cnt[0][1]-cnt[1][0]);
	return (S-t*3)/2+t*2;
}
void preset(int tp){//统计各部分的颜色个数 
	for(int i=1;i<=n;i++) a[i]=lunhuan[tp][num[i]];//用途如变量名 
	memset(col,0,sizeof(col)); memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++) col[a[i]]++;
	for(int i=1;i<=col[0];i++) cnt[0][a[i]]++;
	for(int i=col[0]+1;i<=col[0]+col[1];i++) cnt[1][a[i]]++;
	for(int i=col[0]+col[1]+1;i<=n;i++) cnt[2][a[i]]++;
} 
void loop(int i){
	cnt[0][a[i]]--;
	cnt[1][a[i]]++;
	cnt[1][a[i+col[1]]]--;
	cnt[2][a[i+col[1]]]++;
	cnt[2][a[i+col[1]+col[2]]]--;
	cnt[0][a[i+col[1]+col[2]]]++;	
	//因为是环，A部分可以在首尾两端，所以需要列举个数向前移的情况 
}
void solve(int tp){
	preset(tp);
	ans=min(ans,cal());
	for(int i=col[0];i>=1;i--){
		loop(i);
		ans=min(ans,cal());		
	}
}
int main(){
	cin>>s;
	n=s.size();
	for(int i=0;i<n;i++) num[i+1]=s[i]-'A';
	ans=n;
	for(int tp=0;tp<6;tp++) solve(tp);
	cout<<ans<<endl;
	return 0;
}
```


---

