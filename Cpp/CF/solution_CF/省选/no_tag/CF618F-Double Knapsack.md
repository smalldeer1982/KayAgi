# Double Knapsack

## 题目描述

You are given two multisets $ A $ and $ B $ . Each multiset has exactly $ n $ integers each between $ 1 $ and $ n $ inclusive. Multisets may contain multiple copies of the same number.

You would like to find a nonempty subset of $ A $ and a nonempty subset of $ B $ such that the sum of elements in these subsets are equal. Subsets are also multisets, i.e. they can contain elements with equal values.

If no solution exists, print $ -1 $ . Otherwise, print the indices of elements in any such subsets of $ A $ and $ B $ that have the same sum.

## 样例 #1

### 输入

```
10
10 10 10 10 10 10 10 10 10 10
10 9 8 7 6 5 4 3 2 1
```

### 输出

```
1
2
3
5 8 10
```

## 样例 #2

### 输入

```
5
4 4 3 3 3
2 2 2 2 5
```

### 输出

```
2
2 3
2
3 5
```

# 题解

## 作者：_LHF_ (赞：34)

大家都在从连续段的角度考虑啊。

讲一种与众不同的处理方法。

令 $x$ 为 $A,B$ 集合选的数的差。

然后每次如果 $x<n$，那么随便从 $A$ 集合中选一个数。

否则的话，从 $B$ 集合中选一个数。

不难发现任意时刻 $x\in[0,2n)$。

如果存在两个时刻满足对应的 $x$ 相等，那么就直接做了。

不难发现如果 $A$ 集合所有数都被选了，那么 $x=0,1,2,\cdots,n-1$ 都被遍历过一遍了，所以下次 $x\le n$ 时就结束了，对于 $x>n$ 同理。

---

## 作者：Leasier (赞：28)

~~高考引流。~~

看到“选子集”，考虑弱化条件，**随意排列后改成选子段**。

设 $suma_i, sumb_i$ 表示 $a, b$ 的前缀和，则我们需要选出 $[l_1, r_1], [l_2, r_2]$，使得 $suma_{r_1} - sumb_{r_2} = suma_{l_1 - 1} - sumb_{l_2 - 1}$。

注意到 $a_i, b_i \in [1, n]$，这启发我们：

- 假设 $suma_n < sumb_n$。
- 对于每个 $i$，选出最小的 $j$ 使得 $sumb_j \geq suma_i$，此时 $sumb_j - suma_i \in [0, n)$。由于这样的 $(i, j)$ 共有 $n + 1$ 对，一定会产生重复。
- 我们把这样的 $(i, j)$ 拿去当上面的 $(r_1, r_2), (l_1 - 1, l_2 - 1)$，选两对前缀和之差相同的作为答案即可。

上面的构造方式同样证明了随意排列后一定存在至少一组合法子段。$suma_n \geq sumb_n$ 时操作基本一致，此处略去。

双指针即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int lsta[1000007], lstb[1000007];
ll suma[1000007], sumb[1000007];
bool vis[1000007];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

void write(int n){
	if (n >= 10) write(n / 10);
	putchar(n % 10 + '0');
}

int main(){
	int n = read();
	for (int i = 1; i <= n; i++){
		int a = read();
		suma[i] = suma[i - 1] + a;
	}
	for (int i = 1; i <= n; i++){
		int b = read();
		sumb[i] = sumb[i - 1] + b;
	}
	vis[0] = true;
	if (suma[n] < sumb[n]){
		for (int i = 1, j = 1; i <= n; i++){
			int diff;
			while (j <= n && suma[i] > sumb[j]) j++;
			diff = sumb[j] - suma[i];
			if (!vis[diff]){
				vis[diff] = true;
				lsta[diff] = i;
				lstb[diff] = j;
			} else {
				write(i - lsta[diff]);
				putchar('\n');
				for (int k = lsta[diff] + 1; k <= i; k++){
					write(k);
					putchar(' ');
				}
				putchar('\n');
				write(j - lstb[diff]);
				putchar('\n');
				for (int k = lstb[diff] + 1; k <= j; k++){
					write(k);
					putchar(' ');
				}
				break;
			}
		}
	} else {
		for (int i = 1, j = 1; i <= n; i++){
			int diff;
			while (j <= n && sumb[i] > suma[j]) j++;
			diff = suma[j] - sumb[i];
			if (!vis[diff]){
				vis[diff] = true;
				lsta[diff] = j;
				lstb[diff] = i;
			} else {
				write(j - lsta[diff]);
				putchar('\n');
				for (int k = lsta[diff] + 1; k <= j; k++){
					write(k);
					putchar(' ');
				}
				putchar('\n');
				write(i - lstb[diff]);
				putchar('\n');
				for (int k = lstb[diff] + 1; k <= i; k++){
					write(k);
					putchar(' ');
				}
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：SDqwq (赞：28)

[博客食用更佳](https://www.luogu.com.cn/blog/Sham-Devour/solution-cf618f)

[CF618F Double Knapsack](https://www.luogu.com.cn/problem/CF618F)

# $\texttt{Description}$

题面很友好，略。

# $\texttt{Solution}$

看到这种题没什么思路，我首先就输出了 `-1`，结果 $0pts$。

于是我大胆猜想，每一个都有解，并且在两个集合中都是一个子段。

尝试证明。

---

设 $suma$ 表示 $a$ 数组的前缀和，$sumb$ 表示 $b$ 数组的前缀和。

不妨设 $suma_n\le sumb_n$。

定义 $c_i$ 为 $suma_i\ge sumb_j$ 的最大的 $j$，显然 $0\le c_i\le n$。

容易发现，$suma_i<sumb_{c_i+1}$，即 $suma_i<sumb_{c_i}+b_{c_i+1}$。

移项得 $suma_i-sumb_{c_i}<b_{c_i+1}$。

因为 $1\le b_{c_i+1}\le n$，所以 $0\le suma_i-sumb_{c_i}<n$，有 $n$ 种可能，而 $0\le i\le n$，有 $n+1$ 种可能。

根据抽屉原理，可知至少有两个 $suma_i-sumb_{c_i}$ 是相等的，于是就证明了都有解的猜想。

假设 $suma_{i1}-sumb_{c_{i1}}=suma_{i2}-sumb_{c_{i2}}$，不妨设 $i1>i2$。

移项可得 $suma_{i1}-suma_{i2}=sumb_{c_{i1}}-sumb_{c_{i2}}$。

此时一组答案就可以是 $a$ 中的 $[i2+1,i1]$ 和 $b$ 中的 $[c_{i2}+1,c_{i1}]$，于是证明了答案都是两个集合中的一个子段。

---

至于如何快速求出每个 $c_i$，由于 $c_i$ 是单调不下降的，所以弄个指针就行了。

---

时间复杂度：$\mathcal{O}(n)$

# $\texttt{Code}$

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;
template <typename T>
inline void Swap (T &x, T &y) {x ^= y ^= x ^= y;}

int a[1000005], b[1000005], c[1000005], id[1000005][2];
ll suma[1000005], sumb[1000005], flag[1000005];

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), suma[i] = suma[i - 1] + 1ll * a[i];
	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]), sumb[i] = sumb[i - 1] + 1ll * b[i];
	bool isSwap = false;
	if (suma[n] > sumb[n]) {
		isSwap = true;
		for (int i = 1; i <= n; i++)
			Swap(a[i], b[i]), Swap(suma[i], sumb[i]);
	}
	int j = 0, al, ar, bl, br;
	for (int i = 0; i <= n; i++) {
		for (; suma[i] >= sumb[j] && j <= n; j++);
		j--;
		if (flag[suma[i] - sumb[j]]) {
			al = id[suma[i] - sumb[j]][0] + 1;
			ar = i;
			bl = id[suma[i] - sumb[j]][1] + 1;
			br = j;
			break;
		}
		flag[suma[i] - sumb[j]] = true;
		id[suma[i] - sumb[j]][0] = i;
		id[suma[i] - sumb[j]][1] = j;
	}
	if (isSwap)
		Swap(al, bl), Swap(ar, br);
	printf("%d\n", ar - al + 1);
	for (int i = al; i <= ar; i++)
		printf("%d ", i);
	printf("\n%d\n", br - bl + 1);
	for (int i = bl; i <= br; i++)
		printf("%d ", i);
	return 0;
}
```

---

## 作者：KaisuoShutong (赞：21)

## CF618F Double Knapsack 题解

感觉有的题解懂了但完全没懂，说个前提条件都能说反……

### 题意
略。

### 题解
尝试证明相等的两个子集在 $a$ 和 $b$ 中一定是连续的。

不妨设 $sa$ 和 $sb$ 为 $a$ 和 $b$ 数组的前缀和。  
那么，对于 $\forall i\in[0,n]$，找到最大的 $t$ 使得 $sa_i>sb_t$。  
此时考虑求出 $sb_{t+1}-sa_i$ 的值，因为 $t+1$ 不一定存在，所以可以强行要求 $sa_n\leq sb_n$，这样就有 $t<n$。  
因为 $0\leq b_i\leq n$，就有 $0\leq sb_{t+1}-sa_i<n$。  
那么从 $0$ 到 $n$ 共 $n+1$ 个数，放进大小为 $n$ 的盒子中，根据抽屉原理，一定存在两个数在同一盒子中。有：  
$sa_i-sb_{t_i}=sa_j-sb_{t_j}$  
$sa_i-sa_j=sb_{t_i}-sb_{t_j}$  
得证。

点个赞吧。
```cpp
//月亮照耀青窗，窗里窗外皆有青色的光。
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 1000010;
int n,sa[maxn],sb[maxn],v[maxn],fl;
pair<int,int>ton[maxn];
signed main() {
	n=read();
	for(int i=1;i<=n;i++) sa[i]=sa[i-1]+read();
	for(int i=1;i<=n;i++) sb[i]=sb[i-1]+read();
	if(sa[n]>sb[n]) swap(sa,sb),fl=1;
	ton[0]=make_pair(0,0),v[0]=1;
	for(int i=1,t=0;i<=n;i++) {
		while(sb[t+1]<sa[i]) ++t;
		if(v[sb[t+1]-sa[i]]) {
			if(fl) {
				cout<<t+1-ton[sb[t+1]-sa[i]].second<<'\n';
				for(int j=ton[sb[t+1]-sa[i]].second+1;j<=t+1;j++) cout<<j<<' ';cout<<'\n';
				cout<<i-ton[sb[t+1]-sa[i]].first<<'\n';
				for(int j=ton[sb[t+1]-sa[i]].first+1;j<=i;j++) cout<<j<<' ';cout<<'\n';
			} else {
				cout<<i-ton[sb[t+1]-sa[i]].first<<'\n';
				for(int j=ton[sb[t+1]-sa[i]].first+1;j<=i;j++) cout<<j<<' ';cout<<'\n';
				cout<<t+1-ton[sb[t+1]-sa[i]].second<<'\n';
				for(int j=ton[sb[t+1]-sa[i]].second+1;j<=t+1;j++) cout<<j<<' ';cout<<'\n';
			}
			return 0;
		} else v[sb[t+1]-sa[i]]=1,ton[sb[t+1]-sa[i]]=make_pair(i,t+1);
	}
	return 0;
}
```

---

## 作者：MY（一名蒟蒻） (赞：10)

[原题传送门](https://www.luogu.com.cn/problem/CF618F)

第一道黑题祭！

拿到这一题有些人啪的一下就输出无解，很快啊！

但是这作为一道构造题，无脑骗分是很容易被偷袭的。

大胆猜(kou)想(hu)：一定有解，且一定存在连续子序列的解。

接下来尝试证明。

---
令 $A_i$ 表示 $a_n$ 的前缀和，$B_i$ 表示 $b_n$ 的前缀和。

不失一般性，我们假设 $A_n ≤ B_n$ 。对于 $0 ≤ i ≤ n$ ，我们定义 $j$ 是满足 $A_i ≥ B_j$ 的最大整数，显然 $j < n$。

由于 $A_n ≤ B_n$ ，则 $A_i ≤ B_j + b_{j+1}$ ，故 $0 ≤ A_i - B_j < n$。

$0 ≤ i ≤ n$ 共有 $n + 1$ 种不同的 $i$，而 $0 ≤ A_i - B_j < n$ 意味着只有 $n$ 种不同的 $A_i - B_j$ 。

由鸽笼原理，一定存在 $i_1 \not= i_2$，满足 $A_{i_1}$ - $B_{j_1}$ = $A_{i_2}$ - $B_{j_2}$ 。

同样不失一般性假定 $i_1 > i_2$，那么 $A_{i_1}$ - $A_{i_2}$ = $B_{j_1}$ - $B_{j_2}$。则连续子序列 
{$a_{i_2+1}$, · · · , $a_{i_1}$} 和 {$b_{j_2+1}$, · · · , $b_{j_1}$} 就是一个合法的方案。

两个数列中分别找到子序列起点和终点，对于子序列的值开个桶记录一下即可，值域从 $1$ 到 $\text{n}$ 。

时间复杂度 $\text{O(n)}$ 。

---
## Code
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

const int N=1e6+10;

int n,l[N][2],la,lb,ra,rb;
long long a[N],b[N];
bool modify,cnt[N];
void swap(int &x,int &y) {x^=y^=x^=y; return ;}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {scanf("%lld",&a[i]); a[i]+=a[i-1];}
	for(int i=1;i<=n;i++) {scanf("%lld",&b[i]); b[i]+=b[i-1];}
	if(a[n] > b[n]) {modify=true; for(int i=1;i<=n;i++) swap(a[i],b[i]);}//不失一般性
	for(int i=0,j=0;i<=n;i++)
	{
		for(;a[i]>=b[j] && j<=n;j++); j--;//移动j的位置
		if(cnt[a[i]-b[j]]) {la=l[a[i]-b[j]][0]+1; lb=l[a[i]-b[j]][1]+1; ra=i; rb=j; break;}//找到答案
		l[a[i]-b[j]][0]=i; l[a[i]-b[j]][1]=j;//记录
		cnt[a[i]-b[j]]=true;//这个值已经搞出来
	}
	if(modify) {swap(la,lb); swap(ra,rb);}
	printf("%d\n",ra-la+1);
	for(int i=la;i<=ra;i++) printf("%d ",i);
	printf("\n%d\n",rb-lb+1);
	for(int i=lb;i<=rb;i++) printf("%d ",i);
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
这里解释一下为什么需要 $\text{cnt}$ 数组而不能直接`l[a[i]-b[j]][0]`判断是否在桶中已经存在值。

例如这种数据。
```
10
9 9 9 9 9 9 9 9 9 9
10 10 10 10 10 10 10 10 10 10
```
数列从第一项开始，而此时桶中会存下 $\text{0}$ ，而这个 $\text{0}$ 是有效数据。

## $\text{Thank you for your reading!}$
您的点赞和评论是对作者最大的支持！

---

## 作者：dfkdsmbd (赞：6)

今晚第三次试图抢一血，这个题目甚是神仙啊QAQ。

假设$a$数组算到最后总和比$b$大，我们现在考虑对于每一个$i$，找出最大的$ta$满足$sa_i>=sb_{ta}$，其中$sa$是$a$数组的前缀和，$sb$是$b$数组的前缀和。

这个不等式可以写成$0 \leq sa_i - sb_{ta} < n$，因为只要大于等于$n$我们就可以继续向前移动$ta$。

我们从0开始统计这个$sa_i - sb_{ta} $的值，那么根据鸽巢原理，一共$n+1$个数字分配在$n$个笼子里，至少有两对是相等的，也就说不存在无解的情况。
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <set>
#define ri register int
#define pi acos(-1.0)

using namespace std;

inline char gch()
{
    static char buf[100010], *h = buf, *t = buf;
    return h == t && (t = (h = buf) + fread(buf, 1, 100000, stdin), h == t) ? EOF : *h ++;
}

typedef long long lo;

typedef unsigned int uint;

template<typename inp_typ>

inline void re(inp_typ &x)
{
    x = 0;
    char a; bool b = 0;
    while(!isdigit(a = getchar()))
        b = a == '-';
    while(isdigit(a))
        x = x * 10 + a - '0', a = getchar();
    if(b == 1)
        x = - x;
}

const int ms = 1e6 + 10;

int n, lx;

lo sa[ms], sb[ms];

struct in
{
    int x, y;
}pos[ms];

int main()
{
    re(n);
    for(ri i = 1; i <= n; i ++)
        re(sa[i]), sa[i] += sa[i - 1];
    for(ri i = 1; i <= n; i ++)
        re(sb[i]), sb[i] += sb[i - 1];
    for(ri i = 0; i <= n; i ++)
        pos[i] = (in){-1, -1};
    bool f = 0;
    if(sa[n] < sb[n])
        swap(sa, sb), f = 1;
    ri i, ta = 0; lo v;
    for(i = 0; i <= n; i ++)
    {
        while(sa[i] >= sb[ta + 1] && ta + 1 <= n)
            ta ++;
        v = sa[i] - sb[ta];
        //cout << i << ' ' << ta << ' ' << v << '\n';
        if(pos[v].x == -1)
            pos[v] = (in){i, ta};
        else
            break;
    }
    if(f)
        swap(sa, sb), swap(i, ta), swap(pos[v].x, pos[v].y);
    printf("%d\n", i - pos[v].x);
    for(ri j = pos[v].x + 1; j <= i; j ++)
        printf("%d ", j);
    printf("\n");
    printf("%d\n", ta - pos[v].y);
    for(ri j = pos[v].y + 1; j <= ta; j ++)
        printf("%d ", j);
    system("pause");
}
```

---

## 作者：dbxxx (赞：4)

[欢迎您到我的博客阅读本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf618f.html)

我们从 $A$，$B$ 中两个集合依次选数，维护一个量 $d$，表示 $A$ 中所选数的和 $- B$ 中所选数的和，初始为 $0$。

当 $d \le 0$ 时，我们从 $A$ 中选数，当 $d > 0$ 时，我们从 $B$ 中选数，直至我们试图选的时候，发现集合已经空了为止。

考虑 $d$ 的变化。$d \le 0$ 时，它会加上一个 $[1, n]$ 的正整数，因此 $d$ 会变大成一个不超过 $n$ 的整数。

$d > 0$ 时，它会减去一个 $[1, n]$ 的正整数，因此 $d$ 会变小成一个不少于 $-n + 1$ 的整数。

也即 $d$ 的变化值域是 $(-n, n]$。 

如果 $d$ 在变化的过程中，某次的值和先前某一次的值相同，那么这个变化过程中两个集合分别新增的数就分别是答案集合。比如 $\{3\}$ 和 $\{1\}$ 差 $2$，$\{3, 4, 5\}$ 和 $\{1, 9\}$ 也差 $2$，那么我们就找到了答案 $\{4, 5\}$ 和 $\{9\}$。

现在我们试图证明 $d$ 一定会有两次相同。

如果试图取 $A$ 中的数时发现取完了，也即我们从 $A$ 中取了 $n$ 次数，并且现在 $d \in (-n ,0]$。

取数的前提条件就是 $d \le 0$，因此这 $n$ 次取数，每次取数 **之前** 的那个时刻都是一个 $d \in (-n ,0]$ 的时刻。而最后我们又有一次时刻 $d \in (-n, 0]$，意味着我们已经有了 $n + 1$ 次 $d \in (-n, 0]$ 的时刻。而 $(-n, 0]$ 中的整数仅有 $n$ 个，根据抽屉原理，一定有两次 $d$ 相同。

如果试图取 $B$ 中的数发现取完了，同理可证（注意到 $(0, n]$ 也是 $n$ 个整数）。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2023-06-14 13:42:39 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2023-06-14 14:52:39
 */
#include <bits/stdc++.h>
inline int read() {
	int x = 0;
	bool f = true;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-')
			f = false;
	for (; isdigit(ch); ch = getchar())
		x = (x << 1) + (x << 3) + ch - '0';
	return f ? x : (~(x - 1));
}

const int N = (int)1e6 + 5;
int a[N], b[N];
typedef std :: pair <int, int> pii;
pii st[N << 1];

int main() {
	int n = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	for (int i = 1; i <= n; ++i)
		b[i] = read();
	st[n] = {1, 1};
	for (int d = n, i = 1, j = 1; ; ) {
		if (d <= n)
			d += a[i++];
		else
			d -= b[j++];
		
		if (st[d].first) {
			int p = st[d].first, q = st[d].second;
			auto f = [](int l, int r) {
				printf("%d\n", r - l);
				for (int i = l; i < r; ++i)
					printf("%d ", i);
				puts("");
			};
			f(p, i);
			f(q, j);
			return 0;
		} else
			st[d] = {i, j};
	}
	return 0;
}

```



---

## 作者：FutaRimeWoawaSete (赞：4)

同学提醒到最后一步才知道怎么做（（（（               

我们发现找子集肯定做不了，我们考虑找两端区间和拼在一起。             

令 $Suma$ 表示 $a$ 序列的前缀和，$Sumb$ 表示 $b$ 序列的前缀和，如果 $Suma_n < Sumb_n$ 就交换一下两个序列。               

接着我们考虑要从 $a$ 序列里面选出两个不同的位置 $i , j$ ，从 $b$ 序列里面选出两个不同的位置 $x , y$ 使得 $| Suma_i - Suma_j | = | Sumb_x - Sumb_y |$ 即可。            

我们考虑去掉绝对值，先假设 $j < i , y < x$ 得到：            

$Suma_i - Suma_j = Sumb_x - Sumb_y$         

我们考虑移项：            

$Suma_i - Sumb_x = Suma_j - Sumb_y$            

我们发现，我们现在只需要选出来满足这个等式的四元组后原来的 $i , j , x , y$ 大小关系并不重要，结合题目给的值域我们考虑构造求解。        

令 $Lim_i$ 表示最大的 $x$ 使得 $Sumb_x \leq Suma_i$ ，其中 $0 \leq x \leq n$ 。那么可以得知 $Sumb_x + b_{x + 1} > Suma_i$ ，移项可以得到 $b_{x + 1} > Suma_i - Sumb_x$ 。由于 $1 \leq b_{x + 1} \leq n$ ，所以可以得到 $0 \leq Suma_i - Sumb_x < n$ 。            

考虑对于所有的 $0 \leq i \leq n$ 求解 $Suma_i - Sumb_{Lim_i}$ ，那么现在就有 $n + 1$ 对，根据鸽巢原理必定有两两一对匹配。               

现在考虑证明匹配的两两一对不是空集，显然 $a$ 序列下选择的两个下标不相同，而由于最后两者的结果相等，所以两者的 $Lim_i$ 也不相等，即 $b$ 序列选择的两个下标不相同，两个序列里面选出来的不是空集。                   

注意一下都要从 $0$ 开始求。 

```cpp
/*

*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
#define int long long
int n,m,a[Len],b[Len],suma[Len],sumb[Len];
struct node
{
	int l,r;
	node(){l = -1 , r = -1;}
	node(int L,int R){l = L , r = R;}
}lst[Len];
signed main()
{
	scanf("%lld",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%lld",&a[i]);
		suma[i] = suma[i - 1] + a[i];
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%lld",&b[i]);
		sumb[i] = sumb[i - 1] + b[i];
	}
	bool flag = false;
	if(suma[n] > sumb[n]) 
	{
		for(int i = 0 ; i <= n ; i ++) swap(suma[i] , sumb[i]);
		flag = true;
	}
	int idx = 0;
	for(int i = 0 ; i <= n ; i ++) 
	{
		while(idx < n && sumb[idx + 1] <= suma[i]) idx ++;
		if(lst[suma[i] - sumb[idx]].l == -1) lst[suma[i] - sumb[idx]] = node(i , idx);
		else
		{
			if(flag)
			{
				printf("%lld\n",max(idx , lst[suma[i] - sumb[idx]].r) - min(idx , lst[suma[i] - sumb[idx]].r));
				for(int j = min(idx , lst[suma[i] - sumb[idx]].r) + 1 ; j <= max(idx , lst[suma[i] - sumb[idx]].r) ; j ++) printf("%lld ",j);
				puts("");
				printf("%lld\n",max(i , lst[suma[i] - sumb[idx]].l) - min(i , lst[suma[i] - sumb[idx]].l));
				for(int j = min(i , lst[suma[i] - sumb[idx]].l) + 1 ; j <= max(i , lst[suma[i] - sumb[idx]].l) ; j ++) printf("%lld ",j);
			}
			else
			{
				printf("%lld\n",max(i , lst[suma[i] - sumb[idx]].l) - min(i , lst[suma[i] - sumb[idx]].l));
				for(int j = min(i , lst[suma[i] - sumb[idx]].l) + 1 ; j <= max(i , lst[suma[i] - sumb[idx]].l) ; j ++) printf("%lld ",j);
				puts("");
				printf("%lld\n",max(idx , lst[suma[i] - sumb[idx]].r) - min(idx , lst[suma[i] - sumb[idx]].r));
				for(int j = min(idx , lst[suma[i] - sumb[idx]].r) + 1 ; j <= max(idx , lst[suma[i] - sumb[idx]].r) ; j ++) printf("%lld ",j);
			}					
			break;
		}
	}
	return 0;
}
/*
3
3 3 3
1 1 1
*/
```

---

## 作者：Mevinsp (赞：3)

构造！

显然对于这道（大部分）构造题高兴地输出 $-1$，会得到 $0$ 分的好成绩。

既然是选子集，猜想可以限制更严格：**选子段使每个子段和相同**。

设 $suma$ 为 $a$ 的前缀和，$sumb$ 为 $b$ 的前缀和，不妨设 $suma_n \le sumb_n$。

对于每一个 $i$，我们找出最小的 $k$ 使 $suma_i \le sumb_k$。由题意，每个元素 $x \in [1,n]$。所以 $0 \le sumb_k - suma_i < n$。

因为 $sumb_k - suma_i$ 共有 $n+1$ 个 $[0,n)$ 的数，根据**鸽巢原理**，至少有两个相同的数。所以证明了本题都有解的结论。

现在只需找到 $[l,r],[l',r']$ 使得 $suma_l - sumb_{l'} = suma_r - sumb_{r'}$，移项得 $suma_l - suma_r = sumb_{l'} - sumb_{r'}$ 即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int inf=0x3f3f3f3f;
const int mod=1e4;
inline void read(int &x) {
	x=0;
	int f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=f;
}
inline void write(int x) {
	if (x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);
	putchar(x%10+'0');
}
int n,a[N],b[N],sa[N],sb[N],t,k,p[N],q[N],l,r,_l,_r;
bool f[N];
signed main() {
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]),sa[i]=sa[i-1]+a[i];
	for(int i=1;i<=n;i++)
		read(b[i]),sb[i]=sb[i-1]+b[i];
	if(sa[n]>sb[n])//设sa[n]<=sb[n] 
		swap(sa,sb),t=1;
	//严格为找连续的一段 
	for(int i=0;i<=n;i++) {
		while(k+1<=n&&sb[k+1]<=sa[i])
			k++;
		if(f[sa[i]-sb[k]]) {//找显然的l,r 
			l=p[sa[i]-sb[k]]+1;
			r=i;
			_l=q[sa[i]-sb[k]]+1;
			_r=k;
			break;//找到就跑路 
		}
		f[sa[i]-sb[k]]=1;
		p[sa[i]-sb[k]]=i;
		q[sa[i]-sb[k]]=k;
	}
	if(t)
		swap(l,_l),swap(r,_r);
	write(r-l+1);
	puts("");
	for(int i=l;i<=r;i++)
		write(i),printf(" ");
	puts("");
	write(_r-_l+1);
	puts("");
	for(int i=_l;i<=_r;i++)
		write(i),printf(" ");
	puts("");
	return 0;
}
```


---

## 作者：XenonWZH (赞：2)

[更好的阅读体验请点这！](https://xenonwzh.github.io/cf-618f/)

# 题意描述

[Codeforces 链接](https://codeforces.com/problemset/problem/618/F)

给你两个可重集 $A, B$，$A, B$ 的元素个数都为 $n$，它们中每个元素的大小 $x\in [1,n]$。请你分别找出 $A, B$ 的子集，使得它们中的元素之和相等。

数据范围：$1 \leq n \leq 10^6$

# 解题思路

~~我甚至菜到这是我做的第一道紫题~~

## 构造方法

本题显然需要构造。

首先我们维护 $A$ 的前缀和 $\text{sA}$，$B$ 的前缀和 $\text{sB}$。然后维护双指针指向两前缀和的第一个元素。这时我们将指向 $\text{sA}$ 的指针不停加 $1$，同时指向 $\text{sB}$ 的指针在满足下一个位置指的数小于等于 $\text{sA}$ 的指针所指的数时不停向前移动，最后记录下 $\text{sA}$ 的指针指向的值和 $\text{sB}$ 指针指向的值的差及下标。若差已经存在，将存在的差的下标的前面的数删去后后面的差即可变为 $0$，故两差坐标之间的数即为答案。

## 正确性证明

接下来我们需要证明本题绝对有解，且所有解中至少有一种解所取的子集在原集合中是相邻的。

设指针下标为 $p$，$q$。该题始终满足 $\text{sA}_p - \text{sB}_q < n$，若两差大于 $n$，则 $q$ 必定可以后移，不为最优。因为集合中的所有数都小于等于 $n$。

所以我们目前有 $sA_0 - sB_q, sA_1 - sB_q, sA_3 - sB_q, \cdots, sA_n - sB_q$ 总共 $n + 1$ 个差。但所有差只有 $0, 1, 2, \cdots, n - 1$ 总共 $n$ 种。根据鸽巢原理可知至少有一种差出现了不止一次。故用该方法本题保证有解。

# 代码演示

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAXN = 1000000;

int main() {
    int n;
    static int a[MAXN + 1], b[MAXN + 1];

    std::cin >> n;

    static long long sa[MAXN + 1], sb[MAXN + 1];
    sa[0] = sb[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sa[i] = sa[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        sb[i] = sb[i - 1] + b[i];
    }

    static bool vis[MAXN + 1];
    static std::pair<int, int> pos[MAXN + 1];
    memset(vis, false, sizeof(vis));
    int p = 1, q = 0;
    vis[0] = true;
    bool find = false;

    for (; p <= n; p++) {
        while (q < n && sb[q + 1] <= sa[p]) q++;
        if (vis[sa[p] - sb[q]]) {
            find = true;
            break;
        } else {
            vis[sa[p] - sb[q]] = true;
            pos[sa[p] - sb[q]] = std::make_pair(p, q);
        }
    }

    if (find) {
        std::cout << p - pos[sa[p] - sb[q]].first << std::endl;
        for (int i = pos[sa[p] - sb[q]].first + 1; i <= p; i++) printf("%d ", i);
        std::cout << std::endl;
        std::cout << q - pos[sa[p] - sb[q]].second << std::endl;
        for (int i = pos[sa[p] - sb[q]].second + 1; i <= q; i++) printf("%d ", i);
        std::cout << std::endl;
    } else std::cout << "-1" << std::endl;

    return 0;
}
```

---

## 作者：Dzhao (赞：1)

首先，这个要求的解的形式太过自由，选择一个子集不是很好处理。于是我们可以套路地对其加以限制，变成选择两段区间，使他们和相同。

令 $sa_i$ 和 $sb_i$ 分别表示 $a$ 和 $b$ 序列的前缀和，此处我们假设 $sa_n\le sb_n$。

那么我们可以枚举 $i$，找到一个最大的满足 $sb_j\le sa_i$ 的 $j$，由于 $sa_n\le sb_n$，所以容易发现，$sa_i-sb_j \in [0,n-1]$。对于 $n+1$ 种 $sa_i-sb_j$ 只有 $n$ 种取值，根据抽屉原理可知肯定有两对 $sa_i-sb_j$ 是相同的：$sa_{i_1}-sb_{j_1}=sa_{i_2}-sb_{j_2}$，可以得到 $sa_{i_2}-sa_{i_1}=sb_{j_2}-sb_{j_1}$ 所以所求答案的区间即为 $a[i_1+1...i_2]$ 和 $b[j_1+1...j_2]$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const int N = 1e6 + 5;
int n, a[N], b[N], buki[N], bukj[N], ok;
ll sa[N], sb[N];

int main() {
	memset(buki, -1, sizeof(buki));
	memset(bukj, -1, sizeof(bukj));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), sa[i] = sa[i - 1] + a[i];
	for(int i = 1; i <= n; i++)
		scanf("%d", &b[i]), sb[i] = sb[i - 1] + b[i];
	if(sa[n] > sb[n]) {
		ok = 1;
		for(int i = 1; i <= n; i++)
			swap(a[i], b[i]), swap(sa[i], sb[i]);
	}
	for(int i = 0, j = 0; i <= n; i++) {
		while(j + 1 <= n && sa[i] >= sb[j + 1]) j++;
		if(buki[sa[i] - sb[j]] != -1) {
			if(!ok) {
				printf("%d\n", i - buki[sa[i] - sb[j]]);
				for(int k = buki[sa[i] - sb[j]] + 1; k <= i; k++) printf("%d ", k);
				printf("\n%d\n", j - bukj[sa[i] - sb[j]]);
				for(int k = bukj[sa[i] - sb[j]] + 1; k <= j; k++) printf("%d ", k);
				printf("\n");	
			} else {
				printf("%d\n", j - bukj[sa[i] - sb[j]]);
				for(int k = bukj[sa[i] - sb[j]] + 1; k <= j; k++) printf("%d ", k);
				printf("\n%d\n", i - buki[sa[i] - sb[j]]);
				for(int k = buki[sa[i] - sb[j]] + 1; k <= i; k++) printf("%d ", k);
				printf("\n");
			}
			return 0;
		}
		buki[sa[i] - sb[j]] = i, bukj[sa[i] - sb[j]] = j;
	}
	return 0;
}
```

---

## 作者：Light_snow (赞：1)

**题目**

[CF618F Double Knapsack](https://www.luogu.com.cn/problem/CF618F)

**思路**

很不错的一个构造题（我不会。

考虑计两个数组 $ A,B $ 作为前缀和。

令 $j$ 为满足 $A_i \leq B_j$ 且最小的值。

由此得出： $ A_i > B_{j - 1} $。

再得出 $ B_j - A_i \leq n $。

 $ i $ 从 $ 0 $ 开始计，所以以鸽笼原理，必有 $A_{i1} - B_{j1} = A_{i2} - B_{j2}$。

于是移项，得出答案。

然后就是一些细节上的处理。

审核管理辛苦了

#代码
```
// code by Dix_
#include<bits/stdc++.h>
#define ll long long

inline ll read(){
    char C=getchar();
    ll N=0 , F=1;
    while(('0' > C || C > '9') && (C != '-')) C=getchar();
    if(C == '-') F=-1 , C=getchar();
    while('0' <= C && C <= '9') N=(N << 1)+(N << 3)+(C - 48) , C=getchar();
    return F*N;
}

ll n,a[1000010],b[1000010];
ll A[1000010],B[1000010];

struct P{
	ll x,y;
}QWQ[1000010];

ll num = 0;

ll lb = 0;

int main(){
	scanf("%lld",&n);
	for(int i = 1;i <= n;++i){
		scanf("%lld",&a[i]);
		A[i] = A[i - 1] + a[i];
	}
	for(int i = 1;i <= n;++i){
		scanf("%lld",&b[i]);
		B[i] = B[i - 1] + b[i];
	}
	bool f = 0;
	if(B[n] < A[n]){
		f = 1;
		std::swap(A,B);
	}
	for(int i = 0;i <= n;++i)
	QWQ[i].x = -1,QWQ[i].y = -1;
	ll v;
	for(int i = 0;i <= n;++i){
		while(B[lb] < A[i] && lb + 1 <= n)
		lb += 1 ;
		v = B[lb] - A[i];
		if(QWQ[v].x == -1)
			QWQ[v].x = i,QWQ[v].y = lb;
		else{
			num = i;
			break;
		}
 	}
 	if(f)
 	std::swap(A,B),std::swap(num,lb),std::swap(QWQ[v].x,QWQ[v].y);
	std::cout<<num - QWQ[v].x<<std::endl;
	for(int i = QWQ[v].x + 1;i <= num;++i){
		std::cout<<i<<" ";
	}
	puts("");
	std::cout<<lb - QWQ[v].y<<std::endl;
	for(int i = QWQ[v].y + 1;i <= lb;++i){
		std::cout<<i<<" ";
	}
}

```

---

## 作者：Jayun (赞：0)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF618F)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/15426445.html)

# 题目大意：

给你两个可重集 $a,b$，$a,b$ 的元素个数都为 $n$，它们中每个元素的大小 $x\in [1,n]$。请你分别找出 $a, b$ 的子集，使得它们中的元素之和相等。

# 正文：

这是一道非常牛逼的构造题。

设 $A,B$ 分别为 $a,b$ 的前缀和。猜想有解且一定**连续**。

若 $A_n\leq B_n$，对于每个 $i\in[1,n]$，都能找到对应的 $j\leq n$ 使得 $B_j\leq A_i,B_{j+1}>A_i$。也就是 $A_i<B_j+b_{j+1}$，得到 $0\leq A_i-B_j<n$，所以一共有 $n+1$ 个 $A_i-B_j$。但又因为只有 $n$ 个 $i$，鸽笼原理，必有 $A_{i_1}-B_{j_1}=A_{i_2}-B_{j_2}$。$\mathcal{O}(n)$ 桶排即可。

# 代码:

```cpp
const int N = 2e6 + 10;

inline ll Read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int n;
ll a[N], b[N];
ll bucket[N][2];
bool flag;

void Sol1(int i, int j)
{
	printf ("%d\n", i - bucket[a[i] - b[j]][0]);
	for (int k = bucket[a[i] - b[j]][0] + 1; k <= i; k++)
		printf ("%d ", k);
}

void Sol2(int i, int j)
{
	printf ("%d\n", j - bucket[a[i] - b[j]][1]);
	for (int k = bucket[a[i] - b[j]][1] + 1; k <= j; k++)
		printf ("%d ", k);
}

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	memset (bucket, -1, sizeof bucket);
	n = Read();
	for (int i = 1; i <= n; i++) a[i] = Read() + a[i - 1];
	for (int i = 1; i <= n; i++) b[i] = Read() + b[i - 1];
	if (a[n] < b[n]) swap (a, b), flag = 1;
	for (int i = 0, j = 0; i <= n; i++)
	{
		for (; b[j] <= a[i] && j <= n; j++);
		j--;
		if (~bucket[a[i] - b[j]][0]) 
		{
			if (flag) {Sol2(i, j); putchar(10); Sol1(i, j);} 
			else {Sol1(i, j); putchar(10); Sol2(i, j);} 
			break;
		}
		else bucket[a[i] - b[j]][0] = i, bucket[a[i] - b[j]][1] = j;
	}
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

事实上，一定有解，而且不需要找子序列，找子段就可以了。

怎么想的？~~我也不知道~~。构造题有一种解法是主动加强条件来减少决策量，尽量简化问题。

现在我们来证明为什么只需要找子段就有解。设原序列为 $a,b$，其前缀和序列为 $A,B$，并令 $A_n\le B_n$（反之同理）。

定义 $j_i$ 代表满足 $A_i\ge B_x$ 的最大的 $x$，那么有 $A_i<B_{j_i}+b_{j_{i}+1}\Rightarrow A_i-B_{j_i}<b_{j_i+1}$，而 $1\le b_{j_i+1}\le n$，因此 $0\le A_i-B_{j_i}<n$，有 $n$ 种取值，由于下标 $i$ 有 $0\sim n$ 共 $n+1$ 种取值。根据鸽笼原理，一定存在一组 $i_0,i_1(i_0<i_1)$ 使得 $A_{i_0}-B_{j_{i_0}}=A_{i_1}-B_{j_{i_1}}$。因此答案就是 $[i_0+1,i_1],[j_{i_0}+1,j_{i_1}]$ 两个子段。


```cpp

#include <algorithm>
#include <cstdio>
#include <iostream>
#define i64 long long

using namespace std;

int n;
int a[1000005], b[1000005];
i64 A[1000005], B[1000005];
int j[1000005], cnt[1000005];

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), A[i] = A[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) scanf("%d", b + i), B[i] = B[i - 1] + b[i];
    int is_swap = 0;

    if (A[n] > B[n]) {
        for (int i = 1; i <= n; ++i) swap(a[i], b[i]), swap(A[i], B[i]);
        is_swap = 1;
    }

    for (int i = 0, q = 0; i <= n; ++i) {
        while (q < n && B[q + 1] <= A[i]) ++q;
        j[i] = q;
    }

    int finder = -1, p[2], q[2];
    for (int i = 0; i <= n; ++i) {
        if (cnt[A[i] - B[j[i]]]) {
            finder = A[i] - B[j[i]]; p[1] = i, q[1] = j[i];
            break;
        }
        ++cnt[A[i] - B[j[i]]];
    }

    for (int i = 0; i <= n; ++i)
        if (A[i] - B[j[i]] == finder) {
            p[0] = i, q[0] = j[i];
            break;
        } 
    if (is_swap) swap(p[0], q[0]), swap(p[1], q[1]);

    cout << p[1] - p[0] << "\n";
    for (int i = p[0] + 1; i <= p[1]; ++i) printf("%d ", i);
    putchar('\n');
    cout << q[1] - q[0] << "\n";
    for (int i = q[0] + 1; i <= q[1]; ++i) printf("%d ", i);
    putchar('\n');

    return 0;
}
```

---

