# 「GMOI R1-T4」Rain

## 题目背景

> **求雨**
>
>玉皇爷爷也姓张，
>
>为啥为难俺张*昌？
>
>三天之内不下雨，
>
>先扒龙皇庙，
>
>__再用大炮轰你娘。__

如果再不下雨，张大帅就会轰掉全亚洲所有的宗教场所！

博丽神社因为可以在外界被看到，自然也无法幸免于难，灵梦十分着急，准备使用祖传秘法求雨……

## 题目描述

为了防止神社被“大炮开兮轰他娘”，灵梦需要求雨。

求雨需要在一条笔直的路上建 $n$ 个法阵，编号为 $1,2,\cdots,n$。

给定一个长度为 $n$ 的数组 $a$，表示在 $a_1$ 到 $a_n$ 的位置建法阵，你要干的是给法阵编号。

灵梦需要来检测法阵效果，她会从 $1$ 号法阵走到 $2$ 号，从 $2$ 号再走到 $3$ 号，直到走到 $n$ 号，再从 $n$ 号走回 $1$ 号。

由于法阵的特殊效果，从 $i$ 个走到 $i+1$ 个的距离是 $\left|a_i\times p-a_{i+1}\times q\right|$。特别的，从 $n$ 号走回到 $1$ 号的距离是 $\left|a_n\times p-a_1\times q\right|$。$p,q$ 是给定的两个常数，$a_i,a_{i+1}$ 是两个法阵的位置。

灵梦希望你来求一下最大的行走距离，并输出对应法阵从 $1$ 号到 $n$ 号的位置排列。（多个只需输出一个即可）

## 说明/提示

**本题开启 SPJ。**

**本题读入量较大，建议使用较快的读入方式。**

对于 $100\%$ 的数据满足 $10\le n\le 10^6$，$1\le p,q \le 10^{5}$，$1\le a_i\le 10^{5}$。

| 编号 | $n$ | $p,q$ | $a_i$ | 分数 |
| :----------: | :----------: | :----------: | :----------:  | :----------: |
| $1$ | $n=10$ | $p,q\le 10^{3}$ | $a_i\le 10^{3}$ | $4$ |
| $2$ | $n=10$ | $p,q\le 10^{3}$ | $a_i\le 10^{3}$ | $5$ |
| $3$ | $n=10$ | $p,q\le 10^{3}$ | $a_i\le 10^{3}$ | $5$ |
| $4\sim 6$  | $n=19$ | $p,q\le 10^{5}$ | $a_i\le 10^{5}$ | $10$ |
| $7$ | $n\le 10^{4}$ | $p,q\le 10^{5}$ | $a_i\le 10^{5}$ | $8$ |
| $8$ | $n\le 10^{4}$ | $p,q\le 10^{5}$ | $a_i\le 10^{5}$ | $9$ |
| $9$ | $n\le 10^{4}$ | $p,q\le 10^{5}$ | $a_i\le 10^{5}$ | $9$ |
| $10\sim 12$ | $n\le 10^{6}$ | $p,q\le 10^{5}$ | $a_i\le 10^{5}$ | $10$ |


## 样例 #1

### 输入

```
10
2 3
1 2 3 4 5 6 7 8 9 10```

### 输出

```
131
5 6 7 1 8 2 9 3 10 4```

# 题解

## 作者：yinhy09 (赞：3)

## 官方题解

本题是求 一个 $a$ 的排列使得 $\left|pa_1-qa_2\right|+\left|pa_2-qa_3\right|+\cdots+\left|pa_{n-1}-qa_n\right|+\left|pa_n-qa_1\right|$ 最大。

将式子拆开：

$(p\times a_1,q\times a_2)$  
$(p\times a_2,q\times a_3)$  
$(p\times a_3,q\times a_4)$  
$\vdots$  
$(p\times a_{n-2},q\times a_{n-1})$  
$(p\times a_{n-1},q\times a_{n})$  
$(p\times a_{n},q\times a_{1})$  

（下简记第 $i$ 个括号对内第 $j$ 个数为 $x_{i,j}$。）

上面的 $2n$ 个数，当我们把绝对值按照实际情况拆开以后，会有 $n$ 项前面系数为 $+1$，$n$ 项前面的系数为 $-1$。由于我们希望原式尽可能大，所以希望大的 $n$ 个都是正，小的是负；这样取到一个理论最大值。（不希望大的和大的放在同一行，这样相减会降低大数的价值）

但是自然会有一个问题，这个理论最大值是否能取到？

我们构造两个集合 $A,B$，记录上面 $2n$ 个数中较大的一半和较小的一半。

显然，只要 $x_{i,2}$ 的分解（此处不说数是因为 $2\times 6$ 和 $3\times 4$ 结果一样，但是分解方式不一样）确定，$x_{i+1,1}$ 的分解也就确定了。我们假设从 $x_{1,2}$ 开始填，先随机选一个分解填入（不管在 $A,B$ 哪个集合当中），那么 $x_{2,1}$ 就确定了。如果 $x_{2,1}$ 是在 $A$ 集合中的分解，那么我们就从 $B$ 中随便找一个填到 $x_{2,2}$。

如此反复，直到表格被填满，因为我们是从 $A,B$ 集合中交替取数，所以不可能有某时刻需要某个集合的数但是没有的情况。

故理论最大值可以被取到。

构造方法只需找一个地方开始填表即可。

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P8927)


## 思路

简单题，放在 $\rm pj \ T4$ 的位置稍微有点奇怪。

第一眼看到题目可能没有什么思路，不妨拆一拆绝对值。

每个数的贡献可以拆成两部分：$(i-1,i)$ 和 $(i,i+1)$，这两部分贡献分别是与 $p,q$ 有关的，所以我们不妨列表（例如样例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/q8rwyobn.png)

如果我们把 $a_i$ 按从小到大的顺序排序，发现总有一段前缀是 $\text{YYNN}$，以及一段长度相同的后缀是 $\text{NNYY}$，中间的数都是 $\text{YNNY}$，我们直接枚举这一段前缀的长度，取个 $\max$ 即可。

接下来考虑构造方案，设三种数分别为 $\text{YN}$ 类，$\text{NY}$ 类，$\text{YNY}$ 类，编号分别为 $1,2,3$。我们可以如此构造：$121212..33333...$。不难发现这样是正确的。

注意，我们上面讨论的都是 $p \le q$ 的情况，$p>q$ 直接 $\rm reverse$ 即可。

这里有个坑点，我比赛时就被坑到了，输出的方案是具体的数，而不是每个数在原数组中的位置。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int Ans[N],n,p,q;
struct node{int x,id;}a[N];
inline bool cmp(node a,node b){return a.x<b.x;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>p>>q;
	for (int i=1;i<=n;++i) cin>>a[i].x,a[i].id=i;
	sort(a+1,a+n+1,cmp);int ans=0,k=0;
	for (int i=1;i<=n;++i) ans-=a[i].x*min(p,q),ans+=a[i].x*max(p,q);
    for (int i=1;i<=n/2;++i)
        if (2*(-a[i].x*max(p,q)+a[n-i+1].x*min(p,q))>0) ans+=2*(-a[i].x*max(p,q)+a[n-i+1].x*min(p,q)),k=i;
        else break;
    cout<<ans<<'\n';
    for (int i=1;i<=k;++i) Ans[2*i-1]=a[i].x,Ans[2*i]=a[n-k+i].x;
    for (int i=2*k+1;i<=n;++i) Ans[i]=a[i-k].x;
    if (p>=q);else reverse(Ans+1,Ans+n+1);
    for (int i=1;i<=n;++i) cout<<Ans[i]<<' ';
    cout<<'\n';
	return 0;
}
```

---

## 作者：irris (赞：1)

### Preface

乱猜结论**并且懒得 implement**害人不浅。

### Problem

给 $a_1 \sim a_n$ 重排列，最大化 $\sum\limits_{i=1}^n \lvert pa_i - qa_{i+1} \rvert$，其中 $a_{n+1} = a_1$。

$n$ 很大，状压过不了而且比正解麻烦，$p,q$ 没有特殊性质。

### Solution

感觉 [官解](https://www.luogu.com.cn/blog/yinhy09/gmoi-r1-t4-solution) 都没有说为什么就是这样做。下面默认你读过这篇文章（不用全读懂，比如我就没读懂然后写了这个）。

**贪心的原则基于一个前提：$\lvert a \rvert = \max\{a, -a\}$**。

这告诉我们，以后遇到带绝对值再最大化的题目，先考虑拆掉绝对值。

---

感觉讲的有点少，那么来聊点别的，比如这题如何构造方案。

我们假设 $p \lt q$，最后一定是留下这些元素：

+ $a_i : +p, +q$，记为 $\text A$ 类元素
+ $a_i : -p, +q$，记为 $\text B$ 类元素
+ $a_i : -p, -q$，记为 $\text C$ 类元素

有人看不懂，说一句，比如 $\text A$ 类元素的记号就是我们要留下 $+pa_i$ 和 $+qa_i$ 这种。

因为 $+p$ 和 $+q$ 的总和是 $n$ 个，$+q$ 和 $-q$ 的总和也是 $n$ 个，所以 $\text A$ 的个数 $= \text C$ 的个数。

那么构造就比较显然了：先把 $\text B$ 连起来，然后一个 $\text C$ 一个 $\text A$ 的选。

这个是对的，证明就是你写一下确实 $+p$ 对应 $-q$，$-p$ 对应 $+q$，只要你是严格按照这个顺序写的都不会有问题，毕竟前 $n$ 大肯定大于后 $n$ 大。注意 $p \gt q$ 的时候 $\text A, \text C$ 顺序要反一下。

### Code

```cpp
#include <bits/stdc++.h>

#define MAXN 1000001
int a[MAXN];
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int N; long long p, q; std::cin >> N >> p >> q;
	for (int i = 1; i <= N; ++i) std::cin >> a[i];
	std::sort(a + 1, a + N + 1);
	for (int i = N, j = N; ; ) {
		(p * a[i] >= q * a[j] ? i : j) -= 1;
		if (i + j == N) {
//			assume i < j :
			// [1, i] : C
			// [i + 1, j] : B
			// [j + 1, N] : A
//			i > j, swap(C, A)
			std::vector<int> s;
			for (int k = std::min(i, j) + 1; k <= std::max(i, j); ++k) s.push_back(a[k]);
			int c = (i < j ? 1 : i + 1), d = (i < j ? j + 1 : 1);
			for (; std::max(c, d) <= N; ++c, ++d) 
				s.push_back(a[c]), s.push_back(a[d]);
			long long ans = std::abs(p * s[N - 1] - q * s[0]);
			for (int i = 0; i + 1 < N; ++i) 
				ans += std::abs(p * s[i] - q * s[i + 1]);
			std::cout << ans << '\n';
			for (int i = 0; i < N; ++i) 
				std::cout << s[i] << " \n"[i + 1 == N];
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Daidly (赞：1)

**$14$ 分**

全排列枚举即可。

**$44$ 分**

发现满足答案的方案数很多，考虑随机化，时限之内能跑多少跑多少。

**$70$ 分**

发现对于 $a_i$ 对答案的影响与 $a_{i-1}$ 有关，不妨考虑前 $i-1$ 个 $a$ 所组成的答案，枚举 $a_i$ 放在哪一个的后面，可以用链表维护。由于哪一个开头无影响（环形），不妨钦定以 $a_1$ 开头，并且在链表尾部也放上 $a_1$。复杂度 $O(n^2)$。

代码如下：

```cpp
#define int long long

const int N=1e6+5;
int n,p,q,a[N],nxt[N],pre[N],lst,ans;

signed main(){
	n=read(),p=read(),q=read();
	for(int i=1;i<=n;++i)a[i]=read();
	a[n+1]=a[1];
	nxt[1]=n+1,pre[n+1]=1,ans=abs(p*a[1]-q*a[1]);
	lst=n+1;
	for(int i=2;i<=n;++i){
		int maxn=0,nowlst=pre[lst];
		for(int j=pre[lst];j;j=pre[j]){
			if(maxn<ans-abs(p*a[j]-q*a[nxt[j]])+abs(p*a[j]-q*a[i])+abs(p*a[i]-q*a[nxt[j]])){
				nowlst=j,maxn=ans-abs(p*a[j]-q*a[nxt[j]])+abs(p*a[j]-q*a[i])+abs(p*a[i]-q*a[nxt[j]]);
			}
		}
		pre[i]=nowlst,nxt[i]=nxt[nowlst];
		pre[nxt[nowlst]]=i,nxt[nowlst]=i;
		ans=maxn;
	}
	print(ans),putchar('\n');
	int tmp;
	for(tmp=1;nxt[tmp];tmp=nxt[tmp])print(a[tmp]),putchar(' ');
	return 0;
}
```

**$100$ 分**

需要换一种方式思考，我们尝试拆开绝对值，则对于 $2n$ 个数（$n$ 个 $pa_i$，$n$ 个 $qa_i$）赋 $n$ 个正号，$n$ 个负号。

理想情况下当然是前 $n$ 大的赋正号，后 $n$ 大的赋负号，我们称前 $n$ 大为“大”，其余为“小”。

我们可以将放置抽象成一个 $2\times n$ 的网格。

对于 $n$ 组数，每组两个 $(pa_i,qa_i)$，分析其大小情况。

1. 两个都是“大”；

2. 两个都是“小”

3. 一大一小，因 $p,q$ 而定，若 $p\leq q$ 则 $pa_i\leq qa_i$ 前者为“小”，后者为“大”，$p>q$ 同理。显然不可能同时出现“大+小”和“小+大”的情况。

由于“大”“小”总数相同，所以情况 1 和情况 2 的出现次数相同，我们考虑一种构造方案：

先放“大小”或“小大”（注意此时为 $ans$ 数组，记录最终答案的下标，以“小大”举例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/wwqr9jc9.png)

根据排放的是“小大”还是“大小”确定“小小”和“大大”谁先摆（此时“小大”之后应该“小小”先摆）。然后交替。

![](https://cdn.luogu.com.cn/upload/image_hosting/npmkje1k.png)

由于“大”和“小”一共 $2n$ 个，“大大”和“小小”个数相同，所以这样放一定正确。

实现方面，我们先把“大小”或“小大”放上去，再交替放“大大”“小小”即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e6+5,V=1e5+5;
int n,p,q,a[N],ans[N],m,p1[N],cnt1,p2[N],cnt2,sum;
bool pa[N],qa[N];
struct node{
	int val,pos;
	bool operator<(const node &p)const{return val<p.val;}
}tmp[N<<1];

signed main(){
	n=read(),p=read(),q=read();
	for(int i=1;i<=n;++i)a[i]=read(),tmp[(i<<1)-1]=(node){p*a[i],i},tmp[i<<1]=(node){q*a[i],i};
	sort(tmp+1,tmp+(n<<1)+1);
	for(int i=1;i<=n;++i)sum-=tmp[i].val;
	for(int i=n+1;i<=(n<<1);++i){
		if(tmp[i].val==p*a[tmp[i].pos])pa[tmp[i].pos]=1;
		else qa[tmp[i].pos]=1;
		sum+=tmp[i].val;
	}
	for(int i=1;i<=n;++i){
		if(pa[i]^qa[i])ans[++m]=i;
		else if(pa[i]&&qa[i])p2[++cnt2]=i;
		else p1[++cnt1]=i;
	}
	for(int i=1;i<=cnt1;++i){
		if(p<=q)ans[++m]=p2[i],ans[++m]=p1[i];
		else ans[++m]=p1[i],ans[++m]=p2[i];
	}
	printf("%lld\n",sum);
	for(int i=1;i<=m;++i)print(a[ans[i]]),putchar(' ');
	return 0;
}
```
如果觉得有帮助就点个赞吧。

---

## 作者：_shy (赞：0)

### 思路
经过绝对值运算后，将**会有 $n$ 项符号为正，$n$ 项符号为负**。为了使答案尽可能地大，我们希望，$pa_1,pa_2\dots pa_n,qa_1,qa_2\dots qa_n$ 中**前 $n$ 大项的符号全为正，其余较小的项符号全为负**。

以 $n=2k$ 和 $p\ge q$ 的情况为例，我们对 $a_1,a_2\dots a_{2k}$ 进行由大到小的排序，得到新的 $a_1,a_2\dots a_{2k}$。令 $b_{1,2\dots2k}$ 为 $a_{1,2k,2,2k-1,\dots k,k+1}$。下面证明序列 $b$ 满足期望。

先不考虑从 $2k$ 到 $1$ 产生的距离，对其他距离进行讨论。当 $i$ 为奇数时，$\lvert bi-b_{i+1}\rvert=pb_i-qb_{i+1}$；当 $i$ 为偶数时，由于 $pb_i$ 递增且 $qb_{i+1}$ 递减，设 $i_0$（如果存在的话），使得 $pb_{i_0}\ge qb_{i_0+1}$，则当 $i<i_0$ 时，$\lvert pb_i-qb_{i+1}\rvert=qb_{i+1}-pb_i$；当 $i\ge i_0$ 时，$\lvert pb_i-qb_{i+1}\rvert=p{b_i}-qb_{i+1}$。

故符号为正的 $2k-1$ 项为，$pb_{1,3,\dots, 2k-1},qb_{3,5,\dots,i_0-1},pb_{i_0,\dots, 2k-2}$。
即，$pa_{1,2,\dots, k,k+2,\dots,2k-\frac{i_0}{2}+1},qa_{2,3,\dots,\frac{i_0}{2}}$。

符号为负的 $2k-1$ 项为，$pa_{2k-\frac{i_0}{2}+2,\dots,2k},qa_{\frac{i_0}{2}+1,\dots,2k}$。

根据 $a$ 的排序方式和 $i_0$ 的意义可知，正项中的每一个大于负项中的每一个。又 $qa_1$ 与 $pa_{k+1}$ 无论哪项为正，肯定大于上述的负项。故序列 $b$ 符合期望。当 $n$ 为奇数时，同理可得；当 $p<q$ 时，同理可得，但对 $a$ 的排序方式改为“小大小大……”。

 时间复杂度为 $\mathcal O(n\log{n})$。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 100;
int n, p, q, a[maxn], cnt, b[maxn];
long long ans;
int read () 
{
	int s = 0, w = 1;
	char ch = getchar ();
	while (ch < '0' || ch > '9') 
	{
		if (ch == '-') w = -1;
		ch = getchar ();
	}
	while (ch >= '0' && ch <= '9') 
	{
		s = s * 10 + ch - '0';
		ch = getchar ();
	}
	return s * w;
}
int main ()
{
	n = read (), p = read (), q = read ();
	for (int i = 1; i <= n; i++)
		a[i] = read ();
	sort (a + 1, a + n + 1);
	for (int i = 1, j = n; i <= j; i++, j--) 
	{
		if (i == j) b[++ cnt] = a[i];
		if (p >= q) 
			b[++ cnt] = a[i], b[++ cnt] = a[j];
		else 
			b[++ cnt] = a[j], b[++ cnt] = a[i];
	}
	for (int i = 1; i <= n; i++) 
	{
		int to = (i == n ? 1 : i + 1);
		ans += abs (1ll * p * b[i] - 1ll * q * b[to]);
	}
	printf ("%lld\n", ans);
	for (int i = 1; i <= n; i++)
		printf ("%d ", b[i]);
	return 0;
}

```



---

## 作者：JackMerryYoung (赞：0)

# 前言

T4, 环形的构造题，一开始没有任何思路。

考虑过状压 DP, 但复杂度太高了，不可行。

# 正文

感觉又是什么鬼贪心，于是决定瞎搞一下。

先尝试改符号。拆开所有绝对值，发现有一个特性，就是有 $N$ 项系数是正的，还有 $N$ 项系数是负的。

**这很重要。** 这时对于贪心很有利，我们认为令大的 $N$ 项为正的，小的 $N$ 项为负的，这样可以最优。

但是我们总是以翻转符号为代价，请问这个想法一定可行吗？我们来思考一下。

对于上述的想法，我们直接取两个集合 $S_{bg}, S_{sm}$ 代表大的 $N$ 项与小的 $N$ 项。

我们用 $E_i(x, y)$ 来表示建的第 $i$ 条边为 $x \to y$。 若 $E_i(x, y)$ 中的 $y$ 给定，则下一条边就是 $E_{i + 1}(y, z)$。 这个 $y$ 与 $E_i(x, y)$ 中的 $y$ 是一样的。

那么我们从 $E_1(x, y)$ 中的 $y$ 开始随便填一个位置，这样子下个便确定了，一定是这轮取的 $S$ 相对的另一个 $S$ 中的数。

由于我们在 $S_{bg}, S_{sm}$ 交替取数，所以恰好能完成这个最优的解。

# 后言

感觉并没有很难，可以说是下位绿了。

看到绝对值考虑先把绝对值拆掉再做题，对于你做题有很大好处。

---

