# [HNOI2002] Kathy函数

## 题目描述

Tiger 非常喜欢数学，所以他参加了学校组织的数学课外兴趣小组。在兴趣小组的学习当中，老师向 Tiger 介绍了 Kathy 函数，Kathy 函数是这样定义的：

$$
\left\{
\begin{aligned}
&f(1)=1\\
&f(3)=3\\
&f(2n)=f(n)\\
&f(4n+1)=2f(2n+1)-f(n)\\
&f(4n+3)=3f(2n+1)-2f(n)
\end{aligned}
\right.
$$

Tiger 对 Kathy 函数产生了浓厚的兴趣，他通过研究发现有很多的数 $n$ 都满足 $f(n)=n$。

对于一个给定的数 $m$，他希望你求出所有的满足 $f(n)=n$ 的正整数 $n$ 的个数，其中 $n\leq m$。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq m \leq 10^{100}$。

## 样例 #1

### 输入

```
5```

### 输出

```
3```

# 题解

## 作者：xyz32768 (赞：28)

首先，在二进制意义下，$f(n)$为$n$的各位数翻转，即$f((\overline{a_1a_2...a_{x-1}a_x})_2)=(\overline{a_xa_{x-1}...a_2a_1})_2$。

网上好多题解里都没有给出上面命题的具体证明，所以这里就介绍一下证明过程吧（以下的证明过程中的数位全部为二进制意义，$n'$为$n$在二进制意义下的各位数翻转）。

基本思想是数学归纳法。首先，可以发现$n$取$1,2,3$时原命题都成立。

第一个递推式：$f(2n)=f(n)$。

设$n=\overline{a_1a_2...a_{x-1}a_x}$，那么$2n=\overline{a_1a_2...a_{x-1}a_x0}$。显然有$n'=(2n)'$（去掉前导$0$）。所以当$f(n)=n'$时一定有$f(2n)=(2n)'$。

第二个递推式：$f(4n+1)=2f(2n+1)-f(n)$。

设$n=\overline{a_1a_2...a_{x-1}a_x}$，那么$2n+1=\overline{a_1a_2...a_{x-1}a_x1}$，$4n+1=\overline{a_1a_2...a_{x-1}a_x01}$。

显然，

$2(2n+1)'-n'=\overline{1a_xa_{x-1}...a_2a_1}+\overline{1a_xa_{x-1}...a_2a_1}-\overline{a_xa_{x-1}...a_2a_1}$

$=\overline{10a_xa_{x-1}...a_2a_1}=(4n+1)'$。

也就是说，当$f(2n+1)=(2n+1)',f(n)=n'$时，$f(4n+1)=(4n+1)'$。

第三个递推式：$f(4n+3)=3f(2n+1)-2f(n)$。

还是设$n=\overline{a_1a_2...a_{x-1}a_x}$。此时有：

$2n'=\overline{a_xa_{x-1}...a_2a_10}$

$(2n+1)'=\overline{1a_xa_{x-1}...a_2a_1}$

$(4n+3)'=\overline{11a_xa_{x-1}...a_2a_1}$

$3(2n+1)'-2n'=\overline{1a_xa_{x-1}...a_2a_1}+\overline{1a_xa_{x-1}...a_2a_1}+\overline{1a_xa_{x-1}...a_2a_1}-\overline{a_xa_{x-1}...a_2a_10}$

$=\overline{11a_xa_{x-1}...a_2a_1}+\overline{a_xa_{x-1}...a_2a_10}-\overline{a_xa_{x-1}...a_2a_10}$

$=\overline{11a_xa_{x-1}...a_2a_1}=(4n+3)'$。

也就是说，当$f(2n+1)=(2n+1)',f(n)=n'$时，$f(4n+3)=(4n+3)'$。

归纳得出，对于任意一个$n\geq1$，$f(n)=n'$。

也就是说，$f(n)=n$的充分必要条件是$n$在二进制意义下是回文串。

将$m$化为二进制之后数位DP或者乱搞。

代码：

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 605;
struct cyx {
    int n, a[N];
    cyx() {}
    cyx(int _n) :
        n(_n) {memset(a, 0, sizeof(a));}
} a, b, f[N], g[N];
cyx read() {
    int i = 1, j; cyx res = cyx(0); char c; bool flag = 0;
    while ((c = getchar()) < '0' || c > '9');
    if (c - 48) res.a[res.n = 1] = c - 48, flag = 1;
    while ((c = getchar()) >= '0' && c <= '9') {
        if (c - 48) flag = 1;
        if (flag) res.a[++res.n] = c - 48;
    }
    if (!res.n) res.a[res.n = 1] = 0;
    for (j = res.n; i < j; i++, j--) swap(res.a[i], res.a[j]);
    return res;
}
void write(cyx num) {
    int i; for (i = num.n; i; i--) putchar(num.a[i] + 48);
    putchar('\n');
}
cyx div2(cyx a) {
    int i; cyx b = a;
    for (i = b.n; i; i--) {
        if (b.a[i] & 1) b.a[i - 1] += 10;
        b.a[i] >>= 1;
    }
    while (b.n > 1 && !b.a[b.n]) b.n--;
    return b;
}
cyx add(cyx a, cyx b) {
    int i; cyx c = cyx(max(a.n, b.n));
    for (i = 1; i <= c.n; i++) {
        c.a[i] += a.a[i] + b.a[i];
        if (c.a[i] > 9) c.a[i + 1]++, c.a[i] -= 10;
    }
    if (c.a[c.n + 1]) c.n++; return c;
}
cyx pow2(int x) {
    int i, j, tmp; cyx res = cyx(1); res.a[1] = 1;
    for (i = 1; i <= x; i++) {
        tmp = 0;
        for (j = 1; j <= res.n; j++) {
            res.a[j] <<= 1; res.a[j] += tmp;
            if (res.a[j] > 9) res.a[j] -= 10, tmp = 1;
            else tmp = 0;
        }
        if (tmp) res.a[++res.n] = 1;
    }
    return res;
}
cyx plus1(cyx x) {
    int i = 1;
    while (i <= x.n && x.a[i] == 9) x.a[i++] = 0;
    if (i > x.n) x.a[++x.n] = 1; else x.a[i]++;
    return x;
}
cyx trans(cyx x) {
    int i; cyx res = cyx(1);
    for (i = 1; i <= x.n; i++)
        if (x.a[i]) res = add(res, pow2(i - 1));
    return res;
}
cyx solve(cyx v) {
    if (v.n == 1 && v.a[1] == 1) return pow2(0);
    f[0] = pow2(0);
    int i, j, k, h, n = v.n; for (i = 1; i <= v.n; i++)
        f[i] = pow2(i & 1 ? (i >> 1) + 1 : i >> 1),
        g[i] = i == 1 ? pow2(0) : f[i - 2];
    if (v.n & 1) {
        for (i = j = (v.n >> 1) + 1; j <= v.n; i--, j++)
            if (v.a[i] != v.a[j]) break;
        if (i) {
            if (v.a[i] > v.a[j]) for (k = h = (v.n >> 1) + 1; h <= v.n; k--, h++)
                v.a[k] = v.a[h];
            else {
                if (v.a[(v.n >> 1) + 1]) {
                    v.a[(v.n >> 1) + 1] = 0;
                    for (k = h = (v.n >> 1) + 1; h <= v.n; k--, h++)
                        v.a[k] = v.a[h];
                }
                else {
                    bool flag = 1;
                    for (k = 1; k < v.n; k++) if (v.a[k]) {flag = 0; break;}
                    if (flag) {
                        v.a[v.n--] = 0;
                        for (k = 1; k <= v.n; k++) v.a[k] = 1;
                    }
                    else {
                        k = (v.n >> 1) + 1;
                        while (!v.a[k]) v.a[k++] = 1; v.a[k]--;
                        for (i = 1; i <= (v.n >> 1); i++)
                            v.a[i] = v.a[v.n - i + 1];
                    }
                }
            }
        }
    }
    else {
        for (i = (v.n >> 1), j = (v.n >> 1) + 1; j <= v.n; i--, j++)
            if (v.a[i] != v.a[j]) break;
        if (i) {
            if (v.a[i] > v.a[j])
            for (k = (v.n >> 1), h = (v.n >> 1) + 1; h <= v.n; k--, h++)
                v.a[k] = v.a[h];
            else {
                bool flag = 1;
                for (k = 1; k < v.n; k++) if (v.a[k]) {flag = 0; break;}
                if (flag) {
                    v.a[v.n--] = 0;
                    for (k = 1; k <= v.n; k++) v.a[k] = 1;
                }
                else {
                    k = (v.n >> 1) + 1;
                    while (!v.a[k]) v.a[k++] = 1; v.a[k]--;
                    for (i = 1; i <= (v.n >> 1); i++)
                        v.a[i] = v.a[v.n - i + 1];
                }
            }
        }
    }
    cyx res = cyx(1); for (i = 1; i < n; i++) res = add(res, g[i]);
    if (n != v.n) return res; int mid = (n & 1) ? (n >> 1) + 1 : (n >> 1);
    cyx uu = cyx(0); for (i = mid; i >= 2; i--) uu.a[++uu.n] = v.a[i];
    while (uu.n > 1 && !uu.a[uu.n]) uu.n--; cyx vv = plus1(trans(uu));
    return add(res, vv);
}
int main() {
    a = read(); b = cyx(0);
    while (a.n != 1 || a.a[1]) b.a[++b.n] = a.a[1] & 1,
        a = div2(a); write(solve(b));
    return 0;
}
```

---

## 作者：Natsume_Rin (赞：11)

这一题其实想通了就不是很难。

根据规律发现，$f(1),f(3),f(5),f(7),f(9),f(15)$ 等数字都满足条件。

然后可以证明出来，如果 $f(n)=n$，那么 $n$ 的二进制下一定是一个回文数。~~但是我不会证233~~。

然后考虑怎么统计答案。

题目范围：$m \leqslant 10^{100}$。

首先，我们记 $p(i)$ 为 $i$ 在二进制下的位数。

##  部分 $1$：

对于 $1 \leqslant p(i) < p(m)$ 的所有数，求回文数数量。如果一个正整数 $x$ 位数 $p(x) < p(m)$，固定二进制下两端的数字（定为 $1$），接下来 $p(x)$ 如果为奇数，回文数数量就是 $2^{\frac{x-1}{2}}$，如果 $p(x)$ 为偶数，回文数数量就是 $2^{\frac{x}{2}-1}$。

然后归纳一下，长度为 $r$ 的二进制数，回文数数量为 $2^ {\left\lfloor{\frac{r-1}{2}}\right\rfloor}$。

也就是，最后的回文数数量就是：

$$
\sum_{i=1}^{i<p(m)} 2^ {\left\lfloor{\frac{i-1}{2}}\right\rfloor}
$$

## 部分 $2$

既然算出了位数小于 $p(m)$ 的回文数数量，接下来考虑怎么算位数等于 $p(m)$ 的回文数数量。

考虑回文数具有对称性。

也就是说一个回文数的后半部分翻转过来，应该要和前半部分相同。

那么，将 $m$ 转成二进制，分成前后两个部分。

例如 $m=(1001001001011111)_2$

将它分成 $(10010010)_2$ 和 $(01011111)_2$，用高精度算出前面一个部分 **除去首位的 $1$** 所代表的二进制数。

如果一个数字转成二进制数字后和前半部分位数相同，并且小于前半部分的总和，那么这一个数字化成二进制后可以当成回文数字的前半部分，后半部分肯定可以找到相应部分。

也就是，这一个的贡献就是前半部分代表的数字(要除去首位的 $1$)的总和。

最后再考虑一下前半部分的一个总体和后半部分是否可以构成回文数即可。



---

## 作者：xiaolilsq (赞：9)

[题目链接](https://www.luogu.com.cn/problem/P2235)

这道题里的$Kathy$函数是相当于是二进制的翻转，至于证明，上面的大佬已经讲得很清楚了，因为我的做法和其他几位大佬做法不太一样，所以过来发~~水~~篇题解

下面讲一下我的思路

对于一个数，我们首先把它分解成二进制，如果有一个数的二进制位数（以下简称位数）比这个数要少，那么这个数肯定是小于该数的，于是我们便可以预处理出位数比这个数小的二进制为回文串的数的个数（即合法的数）

$Q:$对于一个给定的位数，如何求该位数的合法数个数?

> 我们可以把一个合法数从中间断开，于是这个数变分成了两部分，右半部分是什么样，左半部分对称过去就可以了，而右半部分的可选方案数便是所求的合法数个数，这样便可以保证所求的数不重复，不遗漏

举个栗子：求位数为$5$的合法数个数，所求范围为$(10000)_2$到$(11111)_2$，分成两半，右半部分有$3$个数，其中最后一位必须是$1$，则有以下可能情况：$(001)_2$，$(011)_2$，$(101)_2$，$(111)_2$，对称过去分别对应$(10001)_2$，$(11011)_2$，$(10101)_2$，$(11111)_2$，共有四个合法数

于是我们便可以得到计算公式，对于给定的位数$n$，合法数个数为
$2$的$\frac{\lfloor n-1 \rfloor}{2}$次幂

如此预处理，时间复杂度$O(log_2m)$

关键来了，如何求位数和$m$位数相同的数的个数?

同样地，我们也把一个合法数和$m$分成两半部分，如果这个数左半部分小于$m$的左半部分，则这个数必然小于$m$，所以我们可以先求左半部分小于$m$左半部分的数的个数，即$m$左半部去掉最高位个；如果这个数左半部分等于$m$的左半部分，我们单独特判一下大小就可以了

举个栗子：若$m=(110110)_2$，求小于等于$m$的合法数个数

先处理出位数小于$m$的合法数，有$4+2+2+1+1=10$个，$m$左半部分为$(110)_2$，小于的有：$(100)_2$和$(101)_2$（对应$(100001)_2$和$(101101)_2$），$2$个，即$(10)_2=2$个，设$q$为左半部分等于$m$的合法数，则$q=(110011)_2<=m$，于是共有$10+2+1=13$个合法数

于是便可以$A$掉了，总时间复杂度$O(log_2m)$

没有高精应该是这样写的：

```cpp
bool judge(long long m,int len){
	int l=len/2,r=len-l-1;
	while(l<len&&r>=0){
		if(((m>>l)&1)<((m>>r)&1))return true;
		if(((m>>l)&1)>((m>>r)&1))return false;
		++l,--r;
	}
	return true;
}
int main(){
	long long m,n=1,ans=0;
	scanf("%lld",&m);int len;
	for(len=1;n<m;++len,n=n<<1|1){
		ans+=(1<<(len-1)/2);
	}
	ans+=(m&(n>>1))>>(len/2);
	if(judge(m,len))++ans;
	printf("%lld\n",ans);
	return 0;
}
```
~~然而，恶心题目强制高精~~

$AC$代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
template<typename T>void read(T &x){
	x=0;int f(1);char c(getchar());
	for(;!isdigit(c);c=getchar())if(c=='-')f=-f;
	for(; isdigit(c);c=getchar())x=(x<<3)+(x<<1)+c-'0';
	x*=f;
}
template<typename T>void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)write(x/10),x%=10;
	putchar(x+'0');
}
int m[1005],ans[1005],ANS[1005];
void add(int *a,int x){
	while(a[x])a[x++]=0;
	a[x]=1;a[0]=max(a[0],x);
}
void read(void){
	//输入直接转二进制
	memset(m,0,sizeof m);
	memset(ans,0,sizeof ans);
	memset(ANS,0,sizeof ANS);
	char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(; isdigit(c);c=getchar()){
		if(m[0]!=0){
			m[0]+=3;
			for(int i=m[0];i>=1;--i){
				m[i]=0;
				if(i>3&&m[i-3])add(m,i);
				if(i>1&&m[i-1])add(m,i);
			}
		}
		switch(c){
			case '0':break;
			case '1':add(m,1);break;
			case '2':add(m,2);break;
			case '3':add(m,1);add(m,2);break;
			case '4':add(m,3);break;
			case '5':add(m,3);add(m,1);break;
			case '6':add(m,3);add(m,2);break;
			case '7':add(m,3);add(m,2);add(m,1);break;
			case '8':add(m,4);break;
			case '9':add(m,4);add(m,1);break;
		}//感觉自己在打模拟？？？
	}
}
bool judge(void){
	int l=m[0]/2+1,r=m[0]-l+1;
	while(l<=m[0]&&r>=1){
		if(m[r]>m[l])return true;
		if(m[r]<m[l])return false;
		--r,++l;
	}
	return true;
}
const int base=100000000;
int main(){
	read();//输入
	for(int i=1;i<m[0];++i){
		int pos=(i-1)/2+1;
		add(ans,pos);
	}
	for(int i=m[0]/2+1,j=1;i<m[0];++i,++j){
		if(m[i])add(ans,j);
	}
	if(judge())add(ans,1);
	while(ans[0]){//转十进制
		int ad=ans[ans[0]--];
		for(int i=1;i<=ANS[0];++i){
			ANS[i]=ANS[i]*2+ad;
			ad=ANS[i]/base;
			ANS[i]%=base;
		}
		while(ad){
			ANS[++ANS[0]]+=ad;
			ad=ANS[ANS[0]]/base;
			ANS[ANS[0]]%=base;
		}
	}
	printf("%d",ANS[ANS[0]--]);
	while(ANS[0]){
		printf("%08d",ANS[ANS[0]--]);//输出
	}
	return 0;
}
```

~~蒟蒻语言表达不好请谅解~~

---

## 作者：辰星凌 (赞：6)

~~第一次发题解，写得不好请见谅~~
------------


这几疯狂刷数位$dp$的题，~~刷到这道题时被卡了一天~~，一看大佬的讲解发现居然是求回文数。。。

~~废话~~到此结束，进入正题：
------------


满足$f(n)=n$的$n$在二进制的形式下一定是一个回文数

#### 例如:
$f(1)=1$ ($1$)  
$f(3)=3$ ($11$)  
$f(5)=5$ ($101$)  
$f(7)=7$ ($111$)

至于为什么会有这个性质，上面的大佬已经讲得很清楚了，这里就不再赘述

那么问题就变成了在$[1,n]$中找到符合二进制形式为回文数的总个数，这里我提供一种用$dfs$实现数位$dp$的思路

可以先写一下这道题（~~不需要高精~~）：
输出区间内回文数的总个数
###  [LightOJ1205](http://lightoj.com/volume_showproblem.php?problem=1205)


------------

### 用$dfs$找回文数个数：

### 一：转进制
首先我们需要把$n$转化为二进制存储在一个数组$num[lenn]$中

### 二：DFS
$dfs(st,pos,ok,limit)$


#### 记搜，状态表示：
用一个数组记录已经搜过的地方，$dp[pos][ok][st]$ 示已经选到了第$pos$位，前已经选好的是否满足回文$ok$，去前导$0$后共有$st$位，并且前面已选的并未全部达到上限（$pos$开始后面可以随意选$0$或$1$），此时的回文数总数。

$limit$表示前面已选的是否全达到上限，如果是，那么这一位的可以选的数的上限为$num[pos]$，否则可以随意选，$ed=limit?num[pos]:1$。

如果当前状态并未受限，且当前状态的$dp$值已经被记录，直接返回这个值

#### 如何枚举递归

每当选了一个数$i$时， $tmp[pos]=i$。

1.
如果前面都没选（即全是前$0$，$st=pos$），
$ans+=dfs$($st-1$,$pos-1$,$ok$,$limit$&&$i==ed$)

2.
如果前面选了（即$st>pos$）

（1）
如果
当前状态是回文数，且当前选的这位在$st$的后半段，
（即$ok$&&$pos<=st/2$），
$okk=tmp[st-pos+1]==i$  
（2）
否则 $okk=ok$。       
$ans+=dfs$($st$,$pos-1$,$okk$,$limit$&&$i==ed$)

#### $dfs$边界

当$pos==0$（即已经选完了所有位）
如果满足回文数（即$ok=1$）且选了数（即并非全是$0$，$st>0$）  
$return 1$。

### 三.高精

推荐写结构体，~~用起来方便~~，不会的可以参考一下大佬的[~~高精模板~~](https://www.cnblogs.com/Iowa-Battleship/p/9869499.html)

### 最后附上$AC$代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int base = 1e8;
const int N = 20;
int aux[N << 3];
struct bigint {
    int s[N], l;
    void CL() { l = 0; memset(s, 0, sizeof(s)); }
    void pr()
    {
        printf("%d", s[l]);
        for (int i = l - 1; i; i--)
            printf("%08d", s[i]);
    }
    void re_l()
    {
        int i, x = 0, k = 1, L = 0, fl, o;
        char c = getchar();
        for (; c < '0' || c > '9'; c = getchar());
        for (; c >= '0' && c <= '9'; c = getchar())
        {
            if (!(L - 1) && !aux[L])
                L--;
            aux[++L] = c - '0';
        }
        CL();
        l = L / 8 + ((o = L % 8) > 0);
        for (i = 1; i <= o; i++)
            x = x * 10 + aux[i];
        if (o)
            s[l] = x;
        fl = !o ? l + 1 : l;
        for (i = o + 1, x = 0; i <= L; i++, k++)
        {
            x = x * 10 + aux[i];
            if (!(k ^ 8))
            {
                s[--fl] = x;
                x = k = 0;
            }
        }
        if (!l)
            l = 1;
    }
    ll toint()
    {
        ll x = 0;
        for (int i = l; i; i--)
            x = x * base + s[i];
        return x;
    }
    bigint operator = (int b)
    {
        CL();
        do
        {
            s[++l] = b % base;
            b /= base;
        } while (b > 0);
        return *this;
    }
    bigint operator = (ll b)
    {
        CL();
        do
        {
            s[++l] = b % base;
            b /= base;
        } while (b > 0);
        return *this;
    }
    bigint operator + (const int &b)
    {
        bigint c = *this;
        ll x = b;
        for (int i = 1; i <= l && x; i++)
        {
            x = x + c.s[i];
            c.s[i] = x % base;
            x /= base;
        }
        if(x)c.s[++c.l] = x;
        return c;
    }
    bigint operator + (const ll &b)
    {
        bigint c = *this;
        ll x = b;
        for (int i = 1; i <= l && x; i++)
        {
            x = x + c.s[i];
            c.s[i] = x % base;
            x /= base;
        }
        if (x)
            c.s[++c.l] = x;
        return c;
    }
    bigint operator + (bigint &b)
    {
        if (b.l < 3)
            return *this + b.toint();
        bigint c;
        ll x = 0;
        int k = l < b.l ? b.l : l;
        c.CL();
        c.l = k;
        for (int i = 1; i <= k; i++)
        {
            x = x + s[i] + b.s[i];
            c.s[i] = x % base;
            x /= base;
        }
        if (x)
            c.s[++c.l] = x;
        return c;
    }
    bigint operator / (const int &b)
    {
        bigint c;
        ll x = 0;
        c.CL();
        for (int i = l; i; i--)
        {
            c.s[i] = (x * base + s[i]) / b;
            x = (x * base + s[i]) % b;
        }
        for (c.l = l; !c.s[c.l] && c.l > 1; c.l--);
        return c;
    }
    bigint operator % (const int &b)
    {
        bigint c;
        ll x = 0;
        c.CL();
        for (int i = l; i; i--)
            x = (x * base + s[i]) % b;
        return c = x;
    }
    bool operator > (const bigint &b) const
    {
        if (l ^ b.l)
            return l > b.l;
        for (int i = l; i; i--)
            if (s[i] ^ b.s[i])
                return s[i] > b.s[i];
        return false;
    }
    bigint operator += (bigint &b)
    {
        return *this = *this + b;
    }
    bool operator > (int b) const{
        bigint c;return *this > (c = b);
    }
};

bigint a;
int num[350],tmp[350];bigint dp[350][2][350];
bool pan[350][2][350];
inline bigint dfs(int st,int len,int ok,bool limit){
    bigint ans,pp;ans=0;pp=0;
	if(len<1){//边界 
    	if(ok&&st>0)ans=1;
    	return ans;
    }
    if(!limit&&pan[len][ok][st])return dp[len][ok][st];//返回所记录的值 
    int ed=limit?num[len]:1;//处理枚举上限 
    for(int i=0;i<=ed;i++){
        tmp[len]=i;//记录每次选的数，方便判断是否满足回文 
        if(st==len&&!i)pp=dfs(st-1,len-1,ok,limit&&i==ed),ans+=pp;//如果一直都没选数 
        else pp=dfs(st,len-1,(ok&&len<=st/2)?tmp[st-len+1]==i:ok,limit&&i==ed),ans+=pp;//如果选了数 
	}
    if(!limit)dp[len][ok][st]=ans,pan[len][ok][st]=1;//记录 
    return ans;
}
int main(){
    a.re_l();ll Lenn=0;
    while(a>0){num[++Lenn]=(a%2).toint();a=(a/2);}//转成2进制存起来 
    bigint ans=dfs(Lenn,Lenn,1,1);
    ans.pr();
    return 0;
}
```

---

## 作者：Exschawasion (赞：2)

由于 $n \leq 10^{100}$，本题肯定是一个找规律的题目。对于找规律的题，第一步要做的是先打一个小规模的表来寻找规律。打表代码如下：

```
int f(int x) {
	if(d[x]) return d[x]; // 记忆化，加快打表速度
	if(x == 1) return 1;
	if(x == 3) return 3;
	if(x % 2 == 0) return d[x] = f(x / 2);
	if(x % 4 == 1) {
		int n = (x - 1) / 4;
		return d[x] = 2 * f(2 * n + 1) - f(n);
	}
	if(x % 4 == 3) {
		int n = (x - 3) / 4;
		return d[x] = 3 * f(2 * n + 1) - 2 * f(n);
	}
	return 0;
}
```

计算出 $[1, 100]$ 内符合要求的数，包括：${1,3,5,7,9,15...}$。它们都是奇数，然而具体是什么奇数并没有明显的规律。考虑它们的二进制表示：

![](https://i.bmp.ovh/imgs/2022/04/04/17ba9bfa189358eb.png)

这下规律就明显了：当 $f(x)=x$ 时，$x$ 的二进制表示是**回文**的。具体证明可见其他题解，

本题转化成求 $[1, m]$ 中二进制表示为回文串的数字个数。因为是在二进制意义下且跟数位有关，很自然的想到使用数位 $\texttt{dp}$。用一个四元组 $(l,\text{pos},k_1,k_2)$ 表示状态，其中 $l$ 表示**数位长度**；$\text{pos}$ 表示当前计算的**位置**；$k_1$ 和 $k_2$ 分别表示当前数字是否**不大于** $m$、当前数字是否是**回文串**，取值范围均为 $0$ 或 $1$。设 $m$ 在二进制表示下的第 $i$ 位为 $a_i$，状态转移为 $(l,\text{pos},k_1,k_2) \rightarrow (l',\text{pos}',k_1',k_2')$，则有：

1. 如果 $\text{pos} > \frac{l}{2}$ ，此时保持 $k_2'=k_2$，即

$$(l,\text{pos},k_1,k_2) \rightarrow (l,\text{pos}-1,\Delta(k_1),k_2)$$

2. 如果 $\text{pos} \leq \frac{l}{2}$ ，说明已经递归到**当前二进制串的前半部分**。这是一个回文串，前半部分的二进制位应当和后半部分完全一致，而后半部分已经递归计算出来了。所以，当且仅当  时 $k_2'=1$；


$$
(l,\text{pos},k_1,k_2) \rightarrow \begin{cases}
(l,\text{pos}-1,\Delta(k_1),1) && a_{l-\text{pos}+1}=a_{\text{pos}} \text{ 且 } k_2=1 \\
(l,\text{pos}-1,\Delta(k_1),0)
\end{cases} 
$$


请注意，在这里没有加入前导零的处理。处理方式不难想到，当 $l=\text{pos}$ 时，如果令第 $\text{pos}$ 位为 $0$ 且**第 $\text{pos}$ 位是当前数字的第一位时**，说明出现了前导零。此时应当将 $l$ 也减去 $1$，即

$$(l,\text{pos},k_1,k_2) \rightarrow (l-1,\text{pos}-1,\Delta(k_1),k_2) ~~~~~~ (\text{pos}=l)$$

在状态转移中引入了新符号 $\Delta(x)$，它用来表示 $k_1$ 的维护方式。$k_1$ 表示的是当前数是否不大于 $m$。这是数位 $\texttt{dp}$ 的基础操作，不多赘述。

***

本题并没有取模，所以需要一个高精度类来保存二进制数字及答案。此外还有一些细节，比如需要额外的一个数组 `vis` 来保存“当前状态是否被访问过”，因为有可能有的状态计算出的值是 $0$，无法直接使用记忆的值判断，关键 $\texttt{dp}$ 代码如下：

```
BigInteger dp(int use, int pos, bool limit, bool pam) {
	if(pos == 0) {
		return pam && use > 0;
	}
	if(!limit && vis[use][pos][pam]) return f[use][pos][pam];
	BigInteger ans = 0, k;
	int lim = limit ? a[pos] : 1;
	for(int i = 0; i <= lim; i++) {
		chose[pos] = i;
		if(!i && use == pos) {
			k = dp(
				use - 1,
				pos - 1,
				limit && i == lim,
				pam
			);
			ans = ans + k;
		}
		else {
			k = dp(
				use,
				pos - 1,
				limit && i == lim,
				(pos <= use / 2 && pam) ? chose[use - pos + 1] == i : pam
			);
			ans = ans + k;
		}
	}
	f[use][pos][pam] = ans, vis[use][pos][pam] = true;
	return ans;
}
```

其中出现的 `BigInteger` 是高精度类，实现较长就不放了。完整代码可见[剪贴板](https://www.luogu.com.cn/paste/f94kt6dv)。

---

## 作者：SDNetFriend (赞：1)

## P2235 [HNOI2002]Kathy函数 题解

[题目链接](https://www.luogu.com.cn/problem/P2235)

题意不再赘述。

这个数据范围一看就知道是数位 DP，而且肯定要写高精度。（难点在于高精度（逃））

那这个又和普通的数位 DP 感觉没什么关系，可以按照定义打个表，然后十进制下感觉看不出什么东西，只能得到 $n$ 都是奇数。

既然是奇数，说明二进制最高位和最低位都是 $1$，那二进制会不会有什么性质？

然后我打了个表，然后惊喜地跟我旁边人说我打表打出个塔楼，像这样：

![真·塔楼](https://cdn.luogu.com.cn/upload/image_hosting/f0gi1jyr.png)

然后想一会，发现一个东西：

**这个东西长得这么好看是因为它左右对称啊**

然后看一下，发现除了最高低这两位就是从 $1$ 开始把二进制数正着放一遍反着再放一遍。

也就是中间这些是二进制回文串（两边也是）

然后就是个非常裸的数位 DP，不算高精比一般数位 DP 简单得多，但有几个小细节：

1.如果 $m$ 是偶数就直接 $-1$ 使之最高、低位都是 $1$。

2.求的时候预先求出所有二进制长度比 $m$ 要小的答案。

3.最后的答案相当于是取一半的串，直接把这个数加到答案里面，只不过最后加个特判，即看看右侧全部顶位时左边如果是回文串会不会超限，不会最后一位贡献为 $1$，否则为 $0$。

**打表真是个好东西**

### 贴代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#define lint long long
#define rint register int
using namespace std;
namespace hpc{
	const int L=405;
	struct num{short a[L]={0},nd=0;};
	inline num t(string s){
		num x;x.nd=s.size();
		for(rint i=0;i<x.nd;++i)
			x.a[x.nd-i-1]=s[i]-'0';
		return x;
	}
	inline num operator+(num x,num y){
		num z;z.nd=max(x.nd,y.nd);
		for(rint i=0;i<z.nd;++i){
			z.a[i]+=x.a[i]+y.a[i];
			z.a[i+1]+=z.a[i]/10;
			z.a[i]%=10;
		}
		if(z.a[z.nd])++z.nd;
		return z;
	}
	inline num operator*(num x,num y){
		num z;z.nd=x.nd+y.nd-1;
		for(rint i=0;i<x.nd;++i)
			for(rint j=0;j<y.nd;++j)
				z.a[i+j]+=x.a[i]*y.a[j];
		for(rint i=0;i<z.nd;++i){
			z.a[i+1]+=z.a[i]/10;
			z.a[i]%=10;
		}
		if(z.a[z.nd])++z.nd;
		return z;
	}
	inline void print(num x){
		if(!x.nd)cout<<"0";
		else
			for(rint i=x.nd-1;i>=0;--i)
				cout<<x.a[i];
		cout<<endl;
	}
	inline void upd(num &x){
		if(x.a[0]&1)return;
		--x.a[0];
		for(rint i=0;i<x.nd;++i)
			if(x.a[i]<0)--x.a[i+1],x.a[i]+=10;
		if(!x.a[x.nd-1])--x.nd;
	}//对十进制 -1 如果是奇数 
	inline num tb(num d){
		num b;
		while(d.nd){
			b.a[b.nd++]=d.a[0]&1;
			for(rint i=0;i<d.nd;++i){
				if((d.a[i]&1)&&i>0)
					d.a[i-1]+=5;
				d.a[i]/=2;
			}
			if(!d.a[d.nd-1])--d.nd;
		}
		return b;
	}//十进制转二进制 
	num mi[L];
	inline void init(){
		mi[0]=t("1");
		mi[1]=t("2");
		for(rint i=2;i<L;++i)
			mi[i]=mi[i-1]*mi[1];
	}//获取 2 的次幂 
}
hpc::num m,ans;
string s;
inline bool ck(){
	int lt,rt;
	if(m.nd&1)lt=m.nd/2-1,rt=m.nd/2+1;
	else lt=m.nd/2-1,rt=m.nd/2;
	while(lt>=1&&rt<=m.nd-2){
		if(m.a[lt]>m.a[rt])
			return true;
		if(m.a[lt]<m.a[rt])
			return false;
		--lt;++rt;
	}
	return true;
}
inline void solve(){
	m=hpc::t(s);
	hpc::upd(m);
	m=hpc::tb(m);
	ans=hpc::t("1");
	for(rint i=2;i<=m.nd-1;++i){
		int tmp=(i-2)/2;
		if((i-2)&1)++tmp;
		ans=ans+hpc::mi[tmp];
	}
	if(m.nd>=2){
		int rt=m.nd-2,lt=m.nd/2;
		for(rint i=rt;i>=lt;--i)
			if(m.a[i])
				ans=ans+hpc::mi[i-lt];
		if(ck())ans=ans+hpc::t("1");	
	}
	hpc::print(ans);
}
int main(){
	hpc::init();
	cin>>s;
	solve();
	return 0;
}

```


---

## 作者：huangzirui (赞：1)

[题意](https://www.luogu.com.cn/problem/P2235)

---

发个奇怪的找规律题解（

因为比赛时候推出规律其实很困难，所以对于经过一些大数据验证的性质万不得已时可以不用证明直接使用。这是在比赛时的补救（骗分）方法。

首先玩几个小样例找一下规律，这里首先观察到因为递推式子大概是四个一遍循环，于是我们每四个数排列一次：

```
1 1 3 1
5 3 7 1
9 5 13 3
11 7 15 1
17 9 25 5
21 13 29 3
19 11 27 7
23 15 31 1
33 17 49 9
41 25 57 55
37 21 53 13
45 29 61 3
35 19 51 11
43 27 59 7
39 23 55 15
47 31 63 1
...

```

如果有数感的同学可能已经看出来了：首先奇数列以 $2^x$ 次幂为一个规律，把所有的奇数从小到大的行数依次排列起来就是：

```
1 | 1 | 2 2 | 3 4 3 4 | 5 7 6 8 5 7 6 8 | ...
```

把同一个块里面的最小数变成以 $1$ 开始：

```
1 | 1 | 1 1 | 1 2 1 2 | 1 3 2 4 1 3 2 4 | ...
```

那么随便设点什么（比如数的大小，行数，块的编号）（大概）都可以写出一个和 $2^x$ 有关的递推式，这时我们发现答案可能和 $2$ 进制有关。

打出前几个答案的二进制的表，可以得到：

```
1

11

101
111

1001
1111

10001
10101
11011
11111

100001
101101
110011
111111
...
```

可以发现都是回文数，而且包括了所有的回文二进制数。

所以答案就是 —— 小于等于 $m$ 的二进制数中，回文数的个数。

---

## 作者：EthanOI (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P2235)

随机跳题进来的，就写一个思路。首先看到递推式就很容易联想到二进制，因此我们将 $n$ 的二进制设出为 $(\overline{a_ka_{k-1}\cdots a_1a_0})_2$。方便起见用 $g(a_k\cdots a_0)$ 表示 $f(n)$，下对递推式进行翻译：

(1) $g(1)=(1)_2,g(11)=(11)_2$。

(2) $g(\boxed{\quad}0)=g(\boxed{\quad})$，其中 $\boxed{\quad}$ 为一些二进制数码。

(3) $g(\boxed{\quad}01)=2g(\boxed{\quad}1)-g(\boxed{\quad})$。

(4) $g(\boxed{\quad}11)=3g(\boxed{\quad}1)-2g(\boxed{\quad})$。

好像化完效果也没有那么好（还是我菜），做几个小情况试一下：
$$g(10)=g(1)=(01)_2,\quad g(101)_2=2g(11)-g(1)=(101)_2$$
$$g(1011)=3g(101)-2g(10)=(1101)_2$$
好像挺神奇的，到这里自然的会有猜测 $g(x_k\cdots x_1)=(\overline{x_1x_2\cdots x_k})_2$，事实上如果有这个即可得到 $f(n)=n$ 的充要条件为 $n$ 在二进制下是回文数，还是挺好判断的，乱做都行。

这个结论估计有什么深层背景，但我只能想到归纳法，这是直接的。小情况随便验证一下就可以了。下面分三种情况用归纳假设验证即可：

(1) $g(x_k\cdots x_1 0)=g(x_k\cdots x_1)=(0x_1\cdots x_k)_2$，成立。

(2) $\begin{aligned}g(x_k\cdots x_101)&=2g(x_k\cdots x_11)-g(x_k\cdots x_1)\\&=(1x_1\cdots x_k0)_2-(x_1\cdots x_k)_2\\&=(10x_1\cdots x_k)_2\end{aligned}$，成立。

(3) $\begin{aligned}g(x_k\cdots x_111)&=3g(x_k\cdots x_11)-2g(x_k\cdots x_1)\\&=3(1x_1\cdots x_k)_2-(x_1\cdots x_k0)_2\\&=(11x_1\cdots x_k)_2\end{aligned}$，成立。
那就证完了。剩下的数位 dp 就好了，贴一个这部分的[相关问题](https://www.luogu.com.cn/problem/B3883)。如果实在不懂可以参考其他题解，在这一部分有较详细的介绍。

---

## 作者：D2T1 (赞：0)

结论：$f(n)$ 为 $n$ 的二进制翻转。

证明：

发现题面给出的后两个式子都有 $f(2n+1)-f(n)$ 这个部分，那么我们不妨设这个为 $g(n)$。考虑算一下 $g(n)$ 的值。

若 $n$ 为非 $1$ 奇数，不妨设 $n=2k+1$，有：

$$
\begin{aligned}
g(n)&=f(2n+1)-f(n)\\&=f(4k+3)-f(2k+1)\\&=3f(2k+1)-2f(k)-f(2k+1)\\&=2[f(2k+1)-f(k)]\\&=2g(k)
\end{aligned}
$$

若 $n$ 为偶数，不妨设 $n=2k$，有：

$$
\begin{aligned}
g(n)&=f(2n+1)-f(n)\\&=f(4k+1)-f(2k)\\&=2f(2k+1)-f(k)-f(k)\\&=2[f(2k+1)-f(k)]\\&=2g(k)
\end{aligned}
$$

又易得 $g(1)=2$。

综上可得，若 $n$ 的二进制表示有 $p$ 位，则 $g(n)=2^p$。

再考虑 $f(4n),f(4n+1),f(4n+2),f(4n+3)$ 的值。

$$
f(4n)=f(n)
$$

$$
f(4n+1)=f(n)+2g(n)
$$

$$
f(4n+2)=f(2n+1)=f(n)+g(n)
$$

$$
f(4n+3)=f(n)+3g(n)
$$

可以发现，$f(n)$ 转移到 $f(4n+k),k\in\{0,1,2,3\}$，就相当于把 $k$ 的二进制表示翻转，然后把 $f(n)$ 的二进制表示接到后面。

又 $f(1),f(2),f(3)$ 均满足结论，所以该结论成立。

------------

然后就比较简单了，高精度预处理然后数位 dp 一下即可。

---

## 作者：pengyule (赞：0)

[link](https://www.luogu.com.cn/problem/P2235)

看到这道题第一思路就是先打个表再说，事实证明确实非常有用，利用 win10 下的“计算器-程序员”容易方便地发现每一个满足条件的数都在二进制下回文。大量经验证明，不完全归纳法具有普遍的可靠性，因此题目转为求 $\le m$ 的二进制回文数个数。

为什么要数位 DP 呢？直接计算即可。下面 $|m|$ 代表二进制下 $|m|$ 长度。

枚举回文串二进制下不含前导零的长度 $i(1\le i<|m|)$，那么新增的答案即为 $2^{(i+1)/2}$（`/` 表示整除，下同）。现在考虑 $i=n$ 的情况。以下“第 $k$ 位”指的是从最低位开始数。

假如第 $j+1\sim |m|(j>|m|/2)$ 位都跟 $m$ 的一样，考虑剩余的 $n(n<m)$ 有几种方案。显然容易计算出回文中心到 $j$ 的字符数 $l=j-(|m|/2)$，由于要保证 $n<m$，所以限定第 $j$ 位只能填 $0$，那么答案增加 $2^{l-1}$。

但是这还没有统计完。假如第 $(|m|/2)+1$ 位填 $1$（$(|m|/2)+2\sim |m|$ 位还是跟 $m$ 保持一致）是不是一定就会让 $n>m$ 了呢？显然不是。但这个时候的 $n$ 已经固定了，只需要特判它是不是 $\le m$ 即可。

代码实现中，高精需要实现：
- 十进制转二进制（其中需要用到高精整除 $2$）
- 输入、输出
- 高精加
- 高精乘
- 高精快速幂

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=405;
struct Integer{
	int a[102],len;
	Integer(){len=0,memset(a,0,sizeof(a));}
	inline void read(){
		register string str;
		cin>>str,len=str.length();
		for(int i=0;i<str.length();i++)a[len-i]=str[i]-'0';
	}
	inline void print(){
		for(int i=len;i;i--)cout<<a[i];puts("");
	}
	inline int mod(){return a[1]&1;}
}num,ans,_1;
Integer div2(Integer A){
	Integer B;
	int k=0;
	for(int i=A.len;i;i--){
		k=k*10+A.a[i];
		B.a[i]=k>>1,k&=1;
		if(B.a[i]&&!B.len)B.len=i;
	}
	return B;
}
Integer operator*(Integer A,Integer B){
	Integer C;
	for(int i=1;i<=A.len;i++)
		for(int j=1,k,f=0;f||j<=B.len;j++){
			k=A.a[i]*B.a[j]+C.a[i+j-1]+f;
			f=k/10;
			C.a[i+j-1]=k%10;
			C.len=max(C.len,i+j-1);
		}
	return C;
}
Integer operator+(Integer A,Integer B){
	Integer C;
	for(int i=1,k,f=0;i<=max(A.len,B.len)||f;i++){
		k=A.a[i]+B.a[i]+f;
		f=k/10;
		C.a[i]=k%10;
		C.len=i;
	}
	return C;
}
Integer qp2(int b){
	Integer A,Ans;A.len=1,A.a[1]=2;Ans.len=1,Ans.a[1]=1;
	for(;b;b>>=1,A=A*A)if(b&1)Ans=Ans*A;
	return Ans;
}
int n,b[N],_b[N];
bool leq(){
	for(int i=n;i;i--)if(_b[i]<b[i])return 1;else if(b[i]<_b[i])return 0;
	return 1;
}
int main(){
	num.read();
	while(num.len)b[++n]=num.mod(),num=div2(num);
	for(int i=1;i<n;i++)ans=ans+qp2(((i+1)>>1)-1);
	for(int i=n-1;i>n/2;i--){
		if(!b[i])continue;
		ans=ans+qp2(i-1-n/2);
	}
	_1.len=1,_1.a[1]=1;
	for(int i=1;i<=n/2;i++)_b[i]=b[n-i+1];
	for(int i=n/2+1;i<=n;i++)_b[i]=b[i];
	if(leq())ans=ans+_1;
	ans.print();
}
```

---

## 作者：风随逐影 (赞：0)

## 数位DP（dfs）

高精部分就请你们省略吧……

```c
#include<bits/stdc++.h>
using namespace std;
#define go(i,a,b) for(int i=(a);i<=(b);++(i))
#define com(i,a,b) for(int i=(a);i>=(b);--(i))
#define mem(a,b) memset((a),(b),sizeof(a))
#define inf 0x3f3f3f3f
#define fin freopen("input.txt","r",stdin)
#define fout freopen("output.txt","w",stdout)
typedef long long ll;
const int maxn=100010;
int num[500],p[500],n;

const int base = 1e8;
const int N = 20;
int aux[N << 3];
struct bigint {
    int s[N], l;
    void CL() { l = 0; memset(s, 0, sizeof(s)); }
    void pr()
    {
        printf("%d", s[l]);
        for (int i = l - 1; i; i--)
            printf("%08d", s[i]);
    }
    void re_l()
    {
        int i, x = 0, k = 1, L = 0, fl, o;
        char c = getchar();
        for (; c < '0' || c > '9'; c = getchar());
        for (; c >= '0' && c <= '9'; c = getchar())
        {
            if (!(L - 1) && !aux[L])
                L--;
            aux[++L] = c - '0';
        }
        CL();
        l = L / 8 + ((o = L % 8) > 0);
        for (i = 1; i <= o; i++)
            x = x * 10 + aux[i];
        if (o)
            s[l] = x;
        for (fl = !o ? l + 1 : l, i = o + 1, x = 0; i <= L; i++, k++)
        {
            x = x * 10 + aux[i];
            if (!(k ^ 8))
                s[--fl] = x, x = k = 0;
        }
        if (!l)
            l = 1;
    }
    ll toint()
    {
        ll x = 0;
        for (int i = l; i; i--)
            x = x * base + s[i];
        return x;
    }
    bigint operator = (int b)
    {
        CL();
        do
        {
            s[++l] = b % base;
            b /= base;
        } while (b > 0);
        return *this;
    }
    bigint operator = (ll b)
    {
        CL();
        do
        {
            s[++l] = b % base;
            b /= base;
        } while (b > 0);
        return *this;
    }
    bigint operator + (const int& b)
    {
        bigint c = *this;
        ll x = b;
        for (int i = 1; i <= l && x; i++)
        {
            x = x + c.s[i];
            c.s[i] = x % base;
            x /= base;
        }
        if (x)
            c.s[++c.l] = x;
        return c;
    }
    bigint operator + (const ll & b)
    {
        bigint c = *this;
        ll x = b;
        for (int i = 1; i <= l && x; i++)
        {
            x = x + c.s[i];
            c.s[i] = x % base;
            x /= base;
        }
        if (x)
            c.s[++c.l] = x;
        return c;
    }
    bigint operator + (bigint & b)
    {
        if (b.l < 3)
            return *this + b.toint();
        bigint c;
        ll x = 0;
        int k = l < b.l ? b.l : l;
        c.CL(); c.l = k;
        for (int i = 1; i <= k; i++)
        {
            x = x + s[i] + b.s[i];
            c.s[i] = x % base;
            x /= base;
        }
        if (x)
            c.s[++c.l] = x;
        return c;
    }
    bigint operator - (const bigint & b)
    {
        bigint c, d = *this;
        ll x = 0;
        c.CL();
        for (int i = 1; i <= l; i++)
        {
            if ((x = d.s[i]) < b.s[i])
            {
                d.s[i + 1]--;
                x += base;
            }
            c.s[i] = x - b.s[i];
        }
        c.l = l;
        for (; !c.s[c.l] && c.l > 1; c.l--);
        return c;
    }
    bigint operator - (const int& b) { bigint c; return *this - (c = b); }
    bigint operator - (const ll & b) { bigint c; return *this - (c = b); }
    bigint operator * (const int& b)
    {
        bigint c;
        ll x = 0;
        c.CL();
        for (int i = 1; i <= l; i++)
        {
            x = x + 1LL * s[i] * b;
            c.s[i] = x % base;
            x /= base;
        }
        for (c.l = l; x; x /= base)
            c.s[++c.l] = x % base;
        return c;
    }
    bigint operator * (bigint & b)
    {
        if (b.l < 2)
            return *this * b.toint();
        bigint c;
        ll x;
        int i, j, k;
        c.CL();
        for (i = 1; i <= l; i++)
        {
            x = 0;
            for (j = 1; j <= b.l; j++)
            {
                x = x + 1LL * s[i] * b.s[j] + c.s[k = i + j - 1];
                c.s[k] = x % base;
                x /= base;
            }
            if (x)
                c.s[i + b.l] = x;
        }
        for (c.l = l + b.l; !c.s[c.l] && c.l > 1; c.l--);
        return c;
    }
    bigint operator * (const ll & b)
    {
        bigint c;
        if (b > 2e9)
        {
            c = b;
            return *this* c;
        }
        ll x = 0;
        c.CL();
        for (int i = 1; i <= l; i++)
        {
            x = x + b * s[i];
            c.s[i] = x % base;
            x /= base;
        }
        for (c.l = l; x; x /= base)
            c.s[++c.l] = x % base;
        return c;
    }
    bigint operator / (const int& b)
    {
        bigint c;
        ll x = 0;
        c.CL();
        for (int i = l; i; i--)
        {
            c.s[i] = (x * base + s[i]) / b;
            x = (x * base + s[i]) % b;
        }
        for (c.l = l; !c.s[c.l] && c.l > 1; c.l--);
        return c;
    }
    bigint operator / (const ll & b)
    {
        bigint c;
        ll x = 0;
        c.CL();
        for (int i = l; i; i--)
        {
            c.s[i] = (x * base + s[i]) / b;
            x = (x * base + s[i]) % b;
        }
        for (c.l = l; !c.s[c.l] && c.l > 1; c.l--);
        return c;
    }
    bigint operator / (bigint & b)
    {
        if (b.l < 2)
            return *this / b.toint();
        bigint c, d;
        int i, j, le, r, mid, k;
        c.CL(); d.CL();
        for (i = l; i; i--)
        {
            for (j = ++d.l; j > 1; j--)
                d.s[j] = d.s[j - 1];
            d.s[1] = s[i];
            if (d < b)
                continue;
            le = k = 0; r = base - 1;
            while (le <= r)
            {
                mid = (le + r) >> 1;
                b * mid <= d ? le = mid + 1, k = mid : r = mid - 1;
            }
            c.s[i] = k; d = d - b * k;
        }
        for (c.l = l; !c.s[c.l] && c.l > 1; c.l--);
        return c;
    }
    bigint operator % (const int& b)
    {
        bigint c;
        ll x = 0;
        c.CL();
        for (int i = l; i; i--)
            x = (x * base + s[i]) % b;
        return c = x;
    }
    bigint operator % (const ll & b)
    {
        bigint c;
        ll x = 0;
        c.CL();
        for (int i = l; i; i--)
            x = (x * base + s[i]) % b;
        return c = x;
    }
    bigint operator % (bigint & b)
    {
        if (b.l < 2)
            return *this % b.toint();
        bigint c;
        int i, j, le, r, mid, k;
        c.CL();
        for (i = l; i; i--)
        {
            for (j = ++c.l; j > 1; j--)
                c.s[j] = c.s[j - 1];
            c.s[1] = s[i];
            if (c < b)
                continue;
            le = k = 0; r = base - 1;
            while (le <= r)
            {
                mid = (le + r) >> 1;
                b * mid <= c ? le = mid + 1, k = mid : r = mid - 1;
            }
            c = c - b * k;
        }
        for (; !c.s[c.l] && c.l > 1; c.l--);
        return c;
    }
    bigint operator += (bigint & b) { return *this = *this + b; }
    bigint operator += (ll b) { return *this = *this + b; }
    bigint operator += (int b) { return *this = *this + b; }
    bigint operator -= (bigint & b) { return *this = *this - b; }
    bigint operator -= (ll b) { return *this = *this - b; }
    bigint operator -= (int b) { return *this = *this - b; }
    bigint operator *= (bigint & b) { return *this = *this * b; }
    bigint operator *= (ll b) { return *this = *this * b; }
    bigint operator *= (int b) { return *this = *this * b; }
    bigint operator /= (bigint & b) { return *this = *this / b; }
    bigint operator /= (ll b) { return *this = *this / b; }
    bigint operator /= (int b) { return *this = *this / b; }
    bigint operator %= (bigint & b) { return *this = *this % b; }
    bigint operator %= (ll b) { return *this = *this % b; }
    bigint operator %= (int b) { return *this = *this % b; }
    bool operator < (const bigint & b) const
    {
        if (l ^ b.l)
            return l < b.l;
        for (int i = l; i; i--)
            if (s[i] ^ b.s[i])
                return s[i] < b.s[i];
        return false;
    }
    bool operator <= (const bigint & b) const
    {
        if (l ^ b.l)
            return l < b.l;
        for (int i = l; i; i--)
            if (s[i] ^ b.s[i])
                return s[i] < b.s[i];
        return true;
    }
    bool operator > (const bigint & b) const
    {
        if (l ^ b.l)
            return l > b.l;
        for (int i = l; i; i--)
            if (s[i] ^ b.s[i])
                return s[i] > b.s[i];
        return false;
    }
    bool operator >= (const bigint & b) const
    {
        if (l ^ b.l)
            return l > b.l;
        for (int i = l; i; i--)
            if (s[i] ^ b.s[i])
                return s[i] > b.s[i];
        return true;
    }
    bool operator == (const bigint & b) const
    {
        if (l ^ b.l)
            return false;
        for (int i = l; i; i--)
            if (s[i] ^ b.s[i])
                return false;
        return true;
    }
    bool operator != (const bigint & b) const
    {
        if (l ^ b.l)
            return true;
        for (int i = l; i; i--)
            if (s[i] ^ b.s[i])
                return true;
        return false;
    }
    bool operator < (ll b) const { bigint c; return *this < (c = b); }
    bool operator <= (ll b) const { bigint c; return *this <= (c = b); }
    bool operator > (ll b) const { bigint c; return *this > (c = b); }
    bool operator >= (ll b) const { bigint c; return *this >= (c = b); }
    bool operator == (ll b) const { bigint c; return *this == (c = b); }
    bool operator != (ll b) const { bigint c; return *this != (c = b); }
    bool operator < (int b) const { bigint c; return *this < (c = b); }
    bool operator <= (int b) const { bigint c; return *this <= (c = b); }
    bool operator > (int b) const { bigint c; return *this > (c = b); }
    bool operator >= (int b) const { bigint c; return *this >= (c = b); }
    bool operator == (int b) const { bigint c; return *this == (c = b); }
    bool operator != (int b) const { bigint c; return *this != (c = b); }
};
bigint f[500][500];
bool pan[500][500];

bigint dfs(int len,int st,bool limit){
	bigint ret,pp;ret=0;
	if(!len){
		ret=1;
		return ret;
	}
	if(!limit&&pan[len][st]) return f[len][st];
	int up;
	up=limit?num[len]:1;
	go(i,0,up){
		p[len]=i;
		int pos=st>>1;
		if(st==n+1) pp=dfs(len-1,i?len:st,limit&&i==num[len]),ret+=pp;
		else if(len>pos) pp=dfs(len-1,st,limit&&i==num[len]),ret+=pp;
		else{
			if(len<=pos&&i!=p[st+1-len]) continue;
			pp=dfs(len-1,st,limit&&i==num[len]),ret+=pp;
		}
	}
	f[len][st]=ret,pan[len][st]=1;
	return ret;
}


signed main(){ 
	//fin;
	bigint m;
	m.re_l();
	n=0;
	while(m>0){
		num[++n]=(m%2).toint();
		m=(m/2);
	}
	bigint ans=dfs(n,n+1,1);
	ans=ans-1; 
	ans.pr();
	return 0;
}
```


---

