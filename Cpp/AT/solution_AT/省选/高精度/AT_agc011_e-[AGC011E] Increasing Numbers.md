# [AGC011E] Increasing Numbers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc011/tasks/agc011_e

10 進法で表記したとき，桁同士が隣り合っているところではすべて，右にある桁の値のほうが左にある桁の値以上であるような $ 0 $ 以上の整数を，増加的と呼ぶことにします． たとえば，$ 1558 $ や $ 11 $ や $ 3 $ や $ 0 $ は増加的ですが，$ 10 $ や $ 20170312 $ は増加的ではありません．

すぬけ君は，整数 $ N $ を持っています． $ N $ が最小で何個の増加的な数の和として表されるかを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{500000} $

### Sample Explanation 1

例えば，$ 80\ =\ 77\ +\ 3 $ として表すことができます．

### Sample Explanation 2

$ 123456789 $ はそれ自体が増加的なので，$ 1 $ 個の増加的な数の和で表すことができます．

## 样例 #1

### 输入

```
80```

### 输出

```
2```

## 样例 #2

### 输入

```
123456789```

### 输出

```
1```

## 样例 #3

### 输入

```
20170312```

### 输出

```
4```

## 样例 #4

### 输入

```
7204647845201772120166980358816078279571541735614841625060678056933503```

### 输出

```
31```

# 题解

## 作者：Orion545 (赞：15)

# 广告 && 吐槽

[蒟蒻のblog](https://www.cnblogs.com/dedicatus545/p/9715288.html)

### 请各位同学不要忽略这题的想出来的思维难度，再怎么说普及-也太过分了，代码难度不是决定题目难度的唯一标准！

# 思路

首先，我们观察一下上升数的性质

可以发现，它一定可以表示为最多9个全是1的数字的和

那么我们设$N$可以被表示成$k$个上升数的和，同时我们设$p_i=\underbrace{111\cdots 11}_{i}$

我们令$a_{i,j}$表示构成$N$的第$I$个上升数的第$j$个全1数的位数

那么可以写出这样的式子

$N=\sum_{i=1}^k\sum_{j=1}^9 p_{a[i][j]}$

我们发现，$p_{i,j}$这样子摆在这里非常不好操作，那么我们继续观察$p_i$的性质，发现：

$p_i=\frac{10^i - 1}{9}$

所以上式可以写成：

$N=\sum_{i=1}^k\sum_{j=1}^9 \frac{10^{a[i][j]}-1}{9}$

我们把9乘过去，再把右边的$9k$个1加过去，得到：

$9N+9k=\sum_{i=1}^k\sum_{j=1}^910^{a[i][j]}$

我们发现：右边这个东西，如果在所有的10的幂加起来的过程中，能够不进位的话，那么它的数位和一定是9k

如果它发生了进位，因为1次进位一定是-10+1，总数位和-9，而9k是9的倍数，所以这个东西的数位和一定是一个小于9k的9的倍数

再看左边，我们发现，实际上我们需要满足的就是$9N+9k$的数位和小于9k且是9的倍数，而$9N+9k$一定是9的倍数

所以我们只需要求出最小的$k$，使得$9N+9k$的数位和小于等于$9k$即可

由数学归纳法不难证明，本题中$k\leq len(N)$，所以我们只需要枚举$k=1\cdots 5e5$，只要维护一个高精度+即可，复杂度是担此操作均摊$O(1)$，总复杂度$O(n)$

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[1000010];int a[1000010];
int main(){
	scanf("%s",s);int n=strlen(s),i,j,sum=0,k;
	for(i=1;i<=n;i++) a[i]=(s[n-i]-'0')*9;
	for(i=1;i<=n;i++){
		a[i+1]+=a[i]/10;a[i]%=10;
	}
	if(a[n+1]) n++;
	for(i=1;i<=n;i++) sum+=a[i];
	for(k=1;k<=n*10;k++){
		a[1]+=9;sum+=9;
		j=1;
		while(j<=n){
			if(a[j]<10) break;
			sum-=10;a[j]-=10;
			sum++;a[j+1]++;
			j++;
			if(j==n&&a[j+1]) n++;//别忘了有可能加一位
		}
		if(sum<=9*k){//注意这里一定不要写成等于了
			printf("%d\n",k);return 0;
		}
	}
}
```

---

## 作者：Ebola (赞：4)

# 【AGC011E】Increasing Numbers

首先，显然所有“上升数”都可以表示成$9$个$111...111$的和（包括$0$个$1$这种数）

那么如果我们用了$k$个上升数，就有：$N=\sum\limits_{i=1}^{9k}111...111(p_i\;is\;the\;number\;of\;'1')$

进一步得：$N=\sum\limits_{i=1}^{9k}\frac{10^{p_i}-1}{9}$

然后进行一些初等变换，就得到了非常美妙的：$9N+9k=\sum\limits_{i=1}^{9k}10^{p_i}$

于是我们可以枚举$k$，每当$k$加一，左边这个数就加$9$，然后判断式子能否成立即可。

发现右边这个式子的意义就是十进制下各个数位的数字之和不能超过$9k$，然后由于左边这个数要是$9$的倍数，所以十进制下各个数位的数字之和必须要是$9$的倍数，这样判断起来就非常方便了

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=501010;
char s[N];

struct Bigint
{
    int a[N],n;
    int& operator [] (const int &x){return a[x];}
    Bigint(){memset(a,0,sizeof(a));n=0;}
    Bigint(char *s){n=strlen(s);for(int i=0;i<n;i++)a[i]=s[n-i-1]-'0';}
    void carry()
    {
        for(int i=0;i<n;i++)
        {
            if(a[i]<=9) continue;
            a[i+1]+=a[i]/10;
            a[i]%=10;
            if(i==n-1) n++;
        }
    }
    Bigint& operator *= (int x){for(int i=0;i<n;i++)a[i]*=x;carry();return *this;}
    int get(){int res=0;for(int i=0;i<n;i++)res+=a[i];return res;}
    void gao(int &sum)
    {
        a[0]+=9;sum+=9;
        for(int i=0;a[i]>9;i++)
        {
            sum-=a[i];sum-=a[i+1];
            a[i+1]+=a[i]/10;a[i]%=10;
            sum+=a[i];sum+=a[i+1];
            if(i==n-1) n++;
        }
    }
} A;

int main()
{
    scanf("%s",s);
    A=s;A*=9;
    int sum=A.get(),k;
    for(k=1;true;k++)
    {
        A.gao(sum);
        if(sum<=9*k&&sum%9==0) break;
    }
    cout<<k<<endl;
    return 0;
}
```



---

## 作者：irris (赞：3)

## Preface

> 数学 / 拆位 / 高精度 / 均摊

$*1600$，$7$。典中典的、但是又是我不会的题。

## Solution

注意到一个数位单调不降的数 $p$ 一定满足可以拆分成 $\leq 9$ 个 $11{\dots}1$ 的和，证明显然。又因为 $11{\dots}1 = \frac{10^s - 1}{9}$（其中 $s$ 为正整数），那么设我们能把原数 $n$ 拆成 $k$ 个 $\frac{10^s - 1}{9}$ 的和的形式，答案即为 $\lceil \frac{k_{\min}}{9}\rceil$。

如何求 $k_{\min}$？因为 $k_{\min} = \mathcal O(\log n)$，我们考虑枚举这个 $k$，则

$$\sum_{k \text{ 个可能不同的 }s} \frac{10^s - 1}{9} = n$$

$$\sum_{k \text{ 个可能不同的 }s} 10^s = 9n + k$$

显然这个等式成立当且仅当 $\text{popcount}(9n + k)$（在 $10$ 进制下）大于 $k$，并且 $9n + k$ 与 $k$ 模 $9$ 同余（显然成立），因此我们就做完了。

具体实现只需要一次高精乘 $9$ 和 $\mathcal O(ans)$ 次高精 $+1$，而高精 $+1$ 的复杂度是均摊 $\mathcal O(1)$ 的（等比数列求和）。因此时空复杂度为 $\mathcal O(\log n)$。

---

## 作者：serene_analysis (赞：2)

提供一个更好证明正确性的解法。

---

假设我们认为最少用 $k$ 个数就可以表示出来原数，尝试通过把原数减到 $0$ 还原一组方案。从低位往高位贪心，初始时 $k$ 个数最低位都不超过 $9$，我们的目标是从低到高依次构造出原数的每一位并尽可能的把 $k$ 个数的限制留得松一点。为了构造出当前位，我们可能需要令这 $k$ 个数中的某些在这一位的值比上一位小，但是注意到实际上我们并不关心这些数是多少而只关心它们的和，那么只需要留的和最大即可。证明考虑我们选择的 $k$ 个数的当前位之和的上界就是构造的上一位之和，只要保证和最大，如果有一种合法的构造方案的当前位之和小于这个最大的和，那么可以直接复制这个方案。

为了保证和最大，我们在某一位确定的这 $k$ 个数之和可能加起来会越过当前位，为了避免这种情况，需要考虑原数的更高的一些位。朴素的实现是直接写高精度维护经过了前面的减法之后的原数变成了多少。但是实际上并不需要高精度，设考虑了所有较低位的减法之后，从当前位和往前若干位得到的数为 $got$，当前的和为 $sum$，从低到高把每一位加入 $got$ 直到 $got \gt sum$，然后令 $sum$ 最低位为原数的当前位，注意为此可能需要将 $sum$ 倒数第二位减 $1$，如果不够了就说明不合法。于是判定的复杂度就是 $\mathcal{O}(n)$。注意到上面的证明同时说明了答案具有可二分性，于是直接二分答案判定就做完了……吗？

注意可能出现连续的多个 $0$，但是这个也不需要高精度，只要在出现连续的第 $7$ 个 $0$ 的时候从上面借位即可。设 $n$ 为原数长度，时间复杂度 $\mathcal{O}(n \log n)$。如果你写朴素高精度应该是 $\mathcal{O}(n \log n \log_{10} n)$，不过压个位就好了。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
const int maxn=5e5+5;
char str[maxn];
int n;
int val[maxn];
int po[9];
bool can(int gave){
	gave*=9;
	int nwz=n,got=0,dw=n,dec=0;
//	printf("can:%d\n",gave);
	while(true){
		while(nwz&&got<=gave){
			if(dec){
				if(val[nwz])val[nwz]--,dec=0;
				else val[nwz]=9;
			}
			if(dw-nwz==7&&val[nwz]==0)dec=1,val[nwz]=10;
			/*printf("dw=%d,nwz=%d,po=%d\n",dw,nwz,po[nwz-dw]),*/got+=po[dw-nwz]*val[nwz],nwz--;
		}
//		printf("got=%d,gave=%d\n",got,gave);
		if(got<=gave)return true;
		if(got%10>gave)return false;
		gave=(gave%10>=got%10?gave/10*10+got%10:(gave/10-1)*10+got%10),got=(got-gave)/10,dw--;
//		printf("aft,gave=%d,got=%d\n",gave,got);
	}
	return true;
}
signed main(){
	scanf("%s",str+1);
	po[0]=1;
	for(int i=1;i<=8;i++)po[i]=po[i-1]*10;
	while(str[n+1]>='0'&&str[n+1]<='9')n++,val[n]=str[n]-'0';
	int ef_lef=0,ef_rig=n,ef_ans=-1;
	while(ef_lef<=ef_rig){
		int ef_mid=(ef_lef+ef_rig)>>1;
		if(can(ef_mid))ef_ans=ef_mid,ef_rig=ef_mid-1;
		else ef_lef=ef_mid+1;
	}
	printf("%d",ef_ans);
	return 0;
}
/*
1000000000000
*/
//namespace burningContract
```

感谢你的阅读。

---

## 作者：zhiyangfan (赞：2)

### 题意
定义「上升数」为在十进制表示下从高位到低位数位值单调不降的数，如 $11,1234$ 等。给出 $n$，将 $n$ 分解为如下形式，其中 $A$ 表示「上升数」集合：
$$\sum_{i=1}^k a_i,a_i\in A$$
求 $k$ 的最小值。($1\le n\le10^{5\times10^5}$)

### 题解
我们定义「递归数」为所有数位均为 $1$ 的数，则一个数是「上升数」当且仅当它能被分解为至多 $9$ 个「递归数」之和，所以一个数能被分为 $k$ 个「上升数」之和当且仅当它能被至多 $9k$ 个「递归数」表示。又因为「递归数」可以被 $\dfrac{10^r-1}{9}$ 的形式表示，所以题目中给出的式子相当于：
$$n=\sum_{i=1}^{9k}\dfrac{(10^{r_i}-1)}{9}$$
也即：
$$9n+9k=\sum_{i=1}^{9k}10^{r_i}$$
也就是说，对于一个 $k$ 其有解的充要条件是 $9n+9k$ 的十进制表示数位和不超过 $9k$（等于 $9k$ 是在上述式子中没有进位，而进位了只会让和变得更小）。

有了这个结论后，我们就可以尝试求解了。下文中令 $L=\log_{10}n$ 首先注意到答案满足单调性，可以二分一个 $k$，高精算出 $9n+9k$，之后计算数位和求解。显然计算的时间复杂度是 $\mathcal{O}(L)$，那二分呢？注意到 $k=L$ 一定可行（每次只用「上升数」消掉一位可以构造），那我们二分的范围只需要是 $[1,L]$ 即可，总时间复杂度 $\mathcal{O}(L\log L)$。

我们也可以不用二分，朴素枚举 $9n,9n+9k,9n+18k,\cdot\cdot\cdot,9n+9L$ 分别进行计算，乍一看复杂度是 $\mathcal{O}(L^2)$ 的，但注意到我们只关心数位和，而会影响数位和的只是进位，每次至多进一位，所以可以实现出时间复杂度 $\mathcal{O}(L)$ 的算法。（也就是加的时候维护数位和）
```cpp
#include <cstdio>
#include <cstring>
const int N = 5e5 + 10; char s[N];
int a[N], len, b[N], lenb, ss;
inline void plus(const int& k)
{
    a[1] += k; ss += k; int now = 1, d = 0;
    while (a[now] >= 10)
        d = a[now] / 10, ss -= (a[now] - a[now] % 10), 
        a[now] %= 10, a[++now] += d, ss += d;
    if (now > len) len = now;
}
inline void times(const int& k) 
{
    int d = 0;
    for (int i = 1; i <= len; ++i)
    {
        a[i] *= k; a[i] += d;
        d = a[i] / 10; a[i] %= 10;
    }
    while (d) a[++len] = d % 10, d /= 10;
}
inline int sum()
{
    int s = 0;
    for (int i = 1; i <= len; ++i) s += a[i];
    return s;
}
inline void init(int l) { for (int i = 1; i <= l; ++i) a[i] = s[l - i + 1] - '0'; len = l; }
inline void print()
{
    for (int i = len; i; --i) printf("%d", a[i]);
    putchar('\n');
}
int main()
{
    scanf("%s", s + 1); init(strlen(s + 1));
    int k = 0; times(9); ss = sum();
    while (ss > 9 * k) ++k, plus(9);
    printf("%d\n", k); return 0;
}
```
~~说句闲话，二分那个解法也不是不好，它好就好在它可以用 Python 写，而方法二必须实现个高精度。~~

~~upd，自己去试了试发现 Python 写会 T~~

---

## 作者：MatrixGroup (赞：2)

Apply binary search on the answer, one only needs to check whether $N$ can be represented as the sum of $M$ increasing numbers. The key observation is that a number is increasing if and only if it can be represented as the sum of exactly $9$ repunits, where a repunit is a number in the form $0$ or $11\cdots1$. Therefore, one only needs to check whether $N$ can be represented as the sum of $9M$ repunits. Since all repunits has the form of $\dfrac{10^K-1}{9}$, the condition holds if and only if $9N$ can be represented as the sum of $9M$ numbers of the form $10^K-1$, which is equivalent to whether the digit sum of $9N+9M$ is no more than $9M$. This can be easily checked. With a trivial greedy algorithm which decreases the number by the maximum possible repdigit, one can easily show that the answer has an upper bound of $O(\log N)$. Therefore, the problem can be solved in the time complexity of $O(\log N\log \log N)$.

---

## 作者：D_F_S (赞：2)

	一种需要线段树的神必解法。

## Solution：

考虑一个数位和序列 $s$，$s_i$ 表示答案集合中的“递增的数”从高到低第 $i$ 位的数字之和。可知只要保证 $s_i\le s_{i+1}$，就一定能构造出一些“递增的数”满足 $s$ 的限制，且最少个数为 $\lceil\frac{s_n}9\rceil$。

现在需要通过原数求得最优的 $s$ 序列使 $s_n$ 尽可能小，考虑从低位到高位依次遍历原数以确定 $s$。设 $a_i$ 表示原数第 $i$ 位，初始时令 $s_n=a_n$，假设现在已经遍历到了 $a_i$，且 $s_{i+1}\sim s_n$ 均已满足限制，若 $a_i\le s_{i+1}$，则直接令 $s_i=a_i$。否则需要将 $a_i$“退位”，令 $s_i=a_i-1$；还需要增大 $s_{i+1}\sim s_n$ 使它们能向 $a_i$“进位”，相当于确定 $j$，令 $s_{i+1}\sim s_{j-1}$ 均 $+9$，令 $s_j+10$。

用一个例子演示上述流程：
```
a=	2	1	7	0	3	2	0
s:							0			s[n] = a[n]
						1	10			j = n
					2	10	20			j = n
				0	2	10	20			a[i] <= s[i+1]
			6	9	11	20	20			j = n-1
		1	6	9	11	20	20			a[i] <= s[i+1]
	1	10	15	18	20	29	30			j = n
```
为使 $s_n$ 尽可能小，可贪心地考虑 $j$ 的选取，若不存在 $i<n,s_i+10\le s_{i+1}$，则 $j$ 只能取 $n$。否则令 $j$ 满足 $<n$ 的同时尽可能大。用线段树维护 $s$ 的差分即可快速得到 $j$。复杂度为 $O(n\log n)$。

## Code1:
```cpp
#include<bits/stdc++.h>
#define inl inline
using namespace std;
const int N=5e5+5;
int n,an,tr[N*4]; char a[N];
#define L (p<<1)
#define R (L|1)
inl void Add(int p,int l,int r,int po,int v)
{
	if(l==r) return tr[p]+=v, void(); int md=(l+r)>>1;
	po<=md?Add(L,l,md,po,v):Add(R,md+1,r,po,v); tr[p]=max(tr[L],tr[R]);
}
inl int Query(int p,int l,int r)
{
	if(tr[p]<10) return 0; if(l==r) return l; int md=(l+r)>>1,t;
	return (t=Query(R,md+1,r))?t:Query(L,l,md);
}
#undef L
#undef R
int main()
{
	scanf("%s",a+1); n=strlen(a+1); an=a[n]-'0';
	for(int i=n-1;i>=1;--i)
		if(a[i]<=a[i+1]) Add(1,1,n,i,a[i+1]-a[i]);
		else
		{
			int t=Query(1,1,n);
			if(t) Add(1,1,n,t-1,1), Add(1,1,n,t,-10);
			else Add(1,1,n,n-1,1), an+=10;
			--a[i]; Add(1,1,n,i,a[i+1]+9-a[i]);
		}
	printf("%d\n",(an+8)/9); return 0;
}
```

## Updata:
考虑差分数组的操作，每次只有一个位置 $+1$，因此同时至多只有一个位置 $=10$。可用一个指针快速维护，做到 $O(n)$。

## Code2:
```cpp
#include<bits/stdc++.h>
const int N=5e5+5;
int n,an,a[N]; char s[N];
int main()
{
	scanf("%s",s+1); n=strlen(s+1); an=s[n]-'0';
	for(int i=n-1,j=n;i>=1;--i)
		if(s[i]<=s[i+1]) a[i]+=s[i+1]-s[i];
		else
		{
			a[j-1]==10?--j:j=n;
			++a[j-1]; j==n?an+=10:a[j]-=10;
			a[i]+=s[i+1]+9-(--s[i]);
		}
	printf("%d\n",(an+8)/9); return 0;
}
```


---

## 作者：xtx1092515503 (赞：1)

[[AGC011E] Increasing Numbers](https://www.luogu.com.cn/problem/AT2341)

一种乍一看很对但是证明比较麻烦的解法。

------

首先显然可以套一个二分。

设当前二分的答案是 $K$。令 $s_i$ 表示第 $i$ 位上的元素（$0$ 为最高位，$n-1$ 为最低位），令 $t_i$ 表示选中的 $K$ 个数在第 $i$ 位上的元素和（不进位）。则，当前 $K$ 合法当且仅当存在一种填数方法使得：

- $t_{n-1}\leq9K$（最后一位就算全填 $9$ 也只能是 $9K$）。
- $t_i\leq t_{i+1}$（所有数都递增，所以该条件必须满足；且只要满足该条件就存在合适的填数方法）。
- 在考虑进位后有 $s=t$。

我们发现一个非常讨厌的地方，也即我们同时要满足 $t$ 的递增以及进位的信息。

从右往左扫，维护当前 $t_i$ 以及低位进位上来的东西。调小 $t_i$ 直到 $t_i$ 加上低位的进位恰好满足 $s_i$ 的限制，然后进入下一位（并同时维护进位）。假如直到最后都没有发生 $t_i$ 被调到负数，则我们声称当前 $K$ 合法。

乍一看上述算法是没有问题的，但是事实上最大的问题是，到最高位时还有若干进位没用掉，导致当前和与目标和虽然在低 $n$ 位均相同，但是更高位上还有若干进位。

这些进位可以被简单忽略掉吗？似乎不太行的样子，但是交上去就过了。

下面我们来证明一下其正确性。

首先我们考虑 $t$ 在进位中的变化。每进一位，$t$ 至多减小 $9$。

然后考虑对 $t$ 作一些变化使得进位减小。显然，我们可以对某个 $t_i$ 减 $10$ 并令 $t_{i-1}$ 加一。因为相邻两位间差不超过 $9$，所以该操作会使得 $t_{i-1}$ 立刻与 $t_{i-2}$ 变得不合法，我们需要将 $t_{i-1}$ 也减 $10$ 并将 $t_{i-2}$ 加一。两个合起来，$t_{i-1}$ 减小了 $9$ 而 $t_{i-2}$ 增大了 $1$，差仍然大于 $9$，会继续下去。直到 $t_0$ 减小了 $9$，此时理应要 $t_{-1}$ 增加 $1$；但是我们如果忽略这一步，就等价于进位减少了一。

换句话说，我们可以执行这样的操作：

- 对于一段前缀，令其中每个 $t$ 都减 $9$。令该前缀的下一个 $t$ 减 $10$。

每执行一次该操作，都会让进位的数减小 $1$。目标是把进位的数变成零。

我们考虑找到一组操作序列，使得在每次操作后均 **不改变相邻两个 $t$ 的差不超过九** 的性质。这样不断执行该操作，直到无法再进行。此时显然进位就被消成了零。

> 事实上，该操作只不过是把一个进位给它重新拆回每一位中。

找到最靠后的满足 $t_i<t_{i+1}$ 的位置 $i$，令 $t_{0\sim i}$ 减小 $9$、$t_{i+1}$ 减小 $10$。因为是最靠后的所以再往后的后缀必然全部相同，进而这一步必然不破坏差的性质。进而不断进行即可最终消掉进位。

这样，我们便证明了上述流程的正确性，也即只要上述流程得到了 $t_0\geq0$ 的一组解，就可以通过上述调整使得最终不会往前进位，换句话说就是得到了合法解。

不排除有省掉二分的可能性，但是我太懒不管了。

时间复杂度线性对数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[500100];
int S;
bool che(int ip){
	int sum=9*ip,rem=0;
	for(int i=S-1;i>=0;i--){
		while(sum&&((sum+rem)%10)!=s[i]-'0')sum--;
		if(((sum+rem)%10)!=s[i]-'0')return false;
		rem+=sum;
		rem/=10;
	}
	return true;
}
int main(){
	scanf("%s",s),S=strlen(s);
	int l=1,r=S<<1;
	while(l<r){
		int mid=(l+r)>>1;
		if(che(mid))r=mid;else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
```



---

## 作者：Seanq (赞：0)

**AT2341 Increasing Numbers题解**  
这是一道高精+贪心=水题  
邻座北京大哥哥抄了网上的题解，我表示要让洛谷上也多一篇题解  
哈哈哈~

------------

一句话题目：给定一个大数，问至少用几个数位不下降的数才可以组成这个大数？

------------

目标：贪心+二分答案+高精度  
每次二分答案，可知答案必为单调不下降的  
每次二分答案时贪心：
从小到大枚举?，即每次给9?加上一个9，我们知道?≤?，所以 9?+9?在我们的算法过程中≤9?+9?，位数是在可以承受的范围内的  
再用高精度，就可以AC了！  
std:  
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000001];
char t;
int	ans;
int a[1000001];
bool check(int x)
{
    int n=strlen(s+1),kum=0;
    for(int i=1;i<=n;i++) a[i]=(s[i]-'0')*9;
    a[1]+=9*x;//加上需求值
    for(int i=1;i<=n;i++)
    {
        if(a[i]>9)//进位
        {
            if(i==n) a[++n]=0;//增位
            a[i+1]+=a[i]/10;//进位
            a[i]%=10;
        }
    }
    for(int i=1;i<=n;i++) kum+=a[i];//求和
    return kum<=x*9;// 比较
}
int main()
{
    scanf("%s",s+1); //输入原数组
    int l=1,r=strlen(s+1);
    reverse(s+1,s+r+1);//反转顺序
    while(l<=r)//二分答案
    {
        int mid=(l+r)/2;//二分
        if(check(mid)==1)//如果可行
            ans=mid,r=mid-1;
        else
            l=mid+1;
    }
    cout << ans << endl;//愉快输出
    return 0;
} 
```
（时间复杂度：O(nlogn)）

---

