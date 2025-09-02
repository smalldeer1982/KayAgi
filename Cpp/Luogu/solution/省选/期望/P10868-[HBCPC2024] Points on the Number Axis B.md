# [HBCPC2024] Points on the Number Axis B

## 题目描述

Bob 正在数轴上玩一个单人游戏。

数轴上有 $n$ 个点。每次，玩家选择两个点。这两个点将被移除，并添加它们的中点。当数轴上只剩下一个点时，游戏结束。形式上，如果选择的两个点是 $x_i$ 和 $x_j$，那么在操作后将添加 $\dfrac{x_i+x_j}{2}$。

为了愉快地玩这个游戏，Bob 总是随机选择两个相邻的点。最初，第 $i$ 个点和第 $(i+1)$ 个点是相邻的。当 Bob 添加一个新点时，它继承其左点的左相邻点和其右点的右相邻点。

现在 Bob 有一个问题：最后一个点的期望位置在哪里。

可以证明，答案可以表示为 $\dfrac{p}{q}$ 的形式，你只需要输出 $p\cdot q^{-1} \bmod 998\,244\,353$ 的值。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3
1 2 4```

### 输出

```
623902723```

# 题解

## 作者：Diaоsi (赞：6)

[Points on the Number Axis B](https://www.luogu.com.cn/problem/P10868)

很牛逼的一道题。

由期望的线性性，我们可以单独考虑每个 $x_i$ 对答案的贡献，这个贡献一定是 $k\cdot x_i$ 的形式，而 $k$ 只跟 $i$ 有关，考虑求出每个 $k$ 的期望。

设 $f_{i,j}$ 表示当前数前面有 $i$ 个数，后面有 $j$ 个数时系数的期望。按照不断消除的过程，最后一定只剩一个数，所以初始状态为 $f_{0,0}=1$。

由于对称性，先考虑消除的是前面的数。若选到前 $i-1$ 个数，则系数不变。若选到第 $i$ 个数，则系数乘 $\dfrac{1}{2}$。

消除后半部分同理，可以得到转移：

$$
f_{i,j}\leftarrow \dfrac{i-1}{i+j}\,f_{i-1,j}+\dfrac{1}{2}\cdot\dfrac{1}{i+j}\,f_{i-1,j}+\dfrac{j-1}{i+j}\,f_{i,j-1}+\dfrac{1}{2}\cdot\dfrac{1}{i+j}\,f_{i,j-1}
$$

化简一下可以得到：

$$
f_{i,j}\leftarrow \dfrac{1}{i+j}\left(i-\dfrac{1}{2}\right)\,f_{i-1,j}
+\dfrac{1}{i+j}\left(j-\dfrac{1}{2}\right)\,f_{i,j-1}
$$

发现这个 $i+j$ 在做无用功，不妨设 $g_{i,j}=(i+j)!\,f_{i,j}$，可以得到：

$$
g_{i,j}\leftarrow \left(i-\dfrac{1}{2}\right)\,g_{i-1,j}
+\left(j-\dfrac{1}{2}\right)\,g_{i,j-1}
$$

把 $(i,j)$ 当成网格图上的点，发现 $g_{i,j}$ 本质上就是网格图路径计数。具体地说，把 $\left(i-\dfrac{1}{2}\right)$ 和 $\left(j-\dfrac{1}{2}\right)$ 当成网格图上的边权，对于一个点 $(i,j)$，到这个点的所有合法路径上的边权积都是：

$$
\left(\prod_{k=1}^{i}\left(k-\dfrac{1}{2}\right)\right)\left(\prod_{k=1}^j\left(k-\dfrac{1}{2}\right)\right)
$$

而方案数是组合数 $\dbinom{i+j}{i}$，所以 $g_{i,j}$ 可以直接计算：

$$
g_{i,j}=\dbinom{i+j}{i}\left(\prod_{k=1}^{i}\left(k-\dfrac{1}{2}\right)\right)\left(\prod_{k=1}^j\left(k-\dfrac{1}{2}\right)\right)
$$

只需要预处理 $n!$ 和 $\prod\left(k-\dfrac{1}{2}\right)$ 就可以 $\mathcal{O}(n)$ 计算答案了。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=1000010,lpw=998244353,inv2=499122177;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int n,ans,fac[N],inv[N],ffac[N];
int qpow(int x,int k){
	int res=1;
	while(k){
		if(k&1)res=1ll*res*x%lpw;
		k>>=1;x=1ll*x*x%lpw;
	}
	return res;
}
int c(int n,int k){
	if(n<k)return 0;
	return 1ll*fac[n]*inv[n-k]%lpw*inv[k]%lpw;
}
int main(){
	scanf("%d",&n);
	fac[0]=inv[0]=ffac[0]=1;
	for(int i=1;i<N;i++){
		ffac[i]=1ll*ffac[i-1]*(i-inv2+lpw)%lpw;
		fac[i]=1ll*fac[i-1]*i%lpw;
	}
	inv[N-1]=qpow(fac[N-1],lpw-2);
	for(int i=N-2;i>=1;i--)
		inv[i]=1ll*inv[i+1]*(i+1)%lpw;
	for(int i=1;i<=n;i++){
		int x,res;
		scanf("%d",&x);
		res=c(n-1,i-1);
		res=1ll*res*ffac[i-1]%lpw;
		res=1ll*res*ffac[n-i]%lpw;
		res=1ll*res*inv[n-1]%lpw;
		ans=(ans+1ll*res*x%lpw)%lpw;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lngym (赞：6)

## 题目大意

对于由 $n$ 个非负整数组成的序列 $a$，要进行 $n - 1$ 次操作，每次操作需选定序列中两个相邻的数，将这两个数的均值放到原序列中这两个数之间的位置，并删除这两个数。易知进行 $n - 1$ 次操作之后只剩下一个数，求这个数的期望并对 $998244353$ 取模。

## 解题思路

易知即求不同操作顺序下期望值的平均值，得到式子：
$$\displaystyle\frac{1}{(n - 1)!}\displaystyle\sum\displaystyle\sum_{i=1}^{n}w_ia_i$$
其中 $w_i$ 表示每种情况的操作完毕后 $a_i$ 的修饰系数（即权重），由于系数一定为 $2^{-k}$（$k$ 为自然数），于是考虑将上式化简，得到：
$$\displaystyle\frac{1}{(n - 1)!2^{n - 1}}\displaystyle\sum_{i=1}^{n}weight_ia_i$$
其中 $weight_i$ 表示所有情况的 $a_i$ 修饰系数的加和。

于是问题转化为如何求 $weight_i$，枚举可知：
- 当 $n = 1$ 时，$weight_1 = 1$。
- 当 $n = 2$ 时，$weight_1 = 1$，$weight_2 = 1$。
- 当 $n = 3$ 时，$weight_1 = 3$，$weight_2 = 2$，$weight_3 = 3$。
- 当 $n = 4$ 时，$weight_1 = 15$，$weight_2 = 9$，$weight_3 = 9$，$weight_4 = 15$。
- 当 $n = 5$ 时，$weight_1 = 105$，$weight_2 = 60$，$weight_3 = 54$，$weight_4 = 60$，$weight_5 = 105$。

于是将它们写在一起即有：
$$1$$
$$1~~~1$$
$$3~~~2~~~3$$
$$15~~~9~~~9~~~15$$
$$105~~~60~~~54~~~60~~~105$$
可以看到非常像杨辉三角，实际上，它也具有与杨辉三角类似的性质：
- 每一行的首项为 $(2n - 3)!!$（$!!$ 为双阶乘）。
- 每一行都是左右对称的。
- 每一行非首项/末项的数都可由它上一行的相邻两个数推出。

例：$60 = 15 \times 1 + 9 \times 5$，$9 = 3 \times 1 + 2 \times 3$ 等等。

记第 $n$ 行第 $m$ 个数为 $Y_{n}^{m}$，则易得递推公式：
$$Y_{n}^{m} = Y_{n - 1}^{m - 1} \cdot (2m - 3) + Y_{n - 1}^{m} \cdot (2n - 2m - 1)$$
根据 $Y_1^1 = 1$，$Y_2^1 = Y_2^2 = 1$ 可求出通项公式：
$$Y_{n}^{m} = (2m - 3)!! \cdot (2n - 2m - 1)!! \cdot \binom{n - 1}{m - 1}$$
然而得到这样的结果我们是不满意的，因为暴力计算 $n$ 个组合数的时间复杂度为 $\Omicron(n^2)$，于是考虑进行作商，得到：
$$
\begin{aligned}
\displaystyle\frac{Y_{n}^{m + 1}}{Y_{n}^{m}} &= \displaystyle\frac{(2m - 1)!!}{(2m - 3)!!}\cdot \displaystyle\frac{(2n - 2m - 3)!!}{(2n - 2m - 1)!!} \cdot \displaystyle\frac{\displaystyle\binom{n - 1}{m}}{\displaystyle\binom{n - 1}{m - 1}} \\
&= \displaystyle\frac{2m - 1}{2n - 2m - 1} \cdot \displaystyle\frac{n - m}{m}
\end{aligned}
$$
于是我们可以在线性时间内计算出 $weight_i$。

~~几个需要注意的问题：~~
- 记得开 `long long`。
- 逆元开销较大，尽量将分母一次性计算完毕之后再求逆元。
- 要经常取模，否则会爆（）。

附上我的 AC 代码（500 ms 左右）：


```cpp
#include<bits/stdc++.h>

#define debug puts("bug\n")
#define int long long
#define mod 998244353
using namespace std;

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

void write(int a) {
    if (a < 0) {
        putchar('-');
        a = -a;
    }
    if (a > 9) write(a / 10);
    putchar(a % 10 + '0');
}

int quick_power(int a, int b, int p) {
    int ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans *= a;
            ans %= p;
        }
        a *= a;
        a %= p;
        b >>= 1;
    }
    return ans;
}

int inverse(int a, int b) {
    return quick_power(a, b - 2, b);
}

vector<int> weight;

int start; // 首项的分子

int down; // 分母

void init_start(int n) {
    // 处理第n+1行的首项分子 (2n-1)!!
    start = 1;
    for (int i = 1; i <= n; i++) {
        start *= (2 * i - 1);
        start %= mod;
    }
}

void init_down(int n) {
    // 处理分母 2^n·n!
    down = 1;
    for (int i = n; i >= 1; i--) {
        down *= i;
        down %= mod;
        down <<= 1;
        down %= mod;
    }
}

void init(int n) {
    // 处理第n+1行 递推系数 (n+1-i)/i · (2i-1)/(2n-2i+1)
    weight.emplace_back(start);
    for (int i = 1; i <= n; i++) {
        int temp = weight[i - 1] * (n - i + 1) % mod;
        temp = temp * (2 * i - 1) % mod;
        int now = (2 * n - 2 * i + 1) * i % mod;
        now = inverse(now, mod);
        temp = temp * now % mod;
        weight.emplace_back(temp);
    }
}

int sum;
int ans;

signed main() {
    int n = read();
    init_start(n - 1);
    init_down(n - 1);
    init(n - 1);
    for (int i = 1; i <= n; i++) {
        int temp = read();
        sum += (temp * weight[i - 1]) % mod;
        sum %= mod;
    }
    ans = inverse(down, mod);
    ans = (sum * ans) % mod;
    write(ans);
    return 0;
}
```

_**当你回首你曾经走过的路时，你会发现，这几年的付出，虽有艰辛，却换来了成长和进步。**_

---

## 作者：MiniLong (赞：4)

每次操作可以看作是把相邻两个联通块合并，并且把两个联通块种所有数都除以 $2$，那么一个数对答案的贡献就是 $\dfrac{a_i}{2^{cnt_i}}$，其中 $cnt_i$ 为它被合并的次数。

根据期望的线性性，可以对每个数的贡献算期望加起来。合并联通块可以看作是操作 $(i,i+1)$ 这个空隙，$a_j$（假设 $j\le i$） 能被影响当且仅当 $(j,j+1),(j+1,j+2)...(i-1,i)$ 空隙都在 $(i,i+1)$ 操作前被操作，然后对 $a_j$ 的影响系数是 $\dfrac{1}{2}$。显然，每个 $(i,i+1)$ 空隙对 $a_j$ 的影响也是独立的，概率显然是 $\dfrac{1}{i-j+1}$，那么 $a_j$ 的贡献系数就是 $\prod (\dfrac{1}{2(i-j+1)}+\dfrac{i-j}{i-j+1})$，$j>i$ 也同理。

预处理 $f_i = f_{i-1} \times (\dfrac{1}{2i}+\dfrac{i-1}{i})$，答案即为 $\sum\limits f_{n-i} \times f_{i-1} \times a_i$。复杂度 $\Theta(n)$。

---

## 作者：__O_v_O__ (赞：2)

首先，我们需要知道一个性质：答案一定可以表示为每个点的位置乘上一个系数再加和。

如何理解？对于每一种操作方法，它所得的答案一定可以表示为每个位置乘上某个系数后再相加。于是答案的期望是每种操作方法的答案乘上它的概率加和，同样可以表示为每个位置乘系数再相加。

根据这个性质，我们很容易想到：把每个位置的系数给算出来即可。如何算呢？打表或 dp 都可以（考试时建议打表，但这里为了严谨使用 dp）。

我们设 $f_{i,j}$ 为当前数前面有 $i$ 个数，后面有 $j$ 个数的系数。

考虑消除前面的数，后面的数同理。若选到前 $i-1$ 个数，则当前点的位置没有改变，系数只需乘上这种情况的概率。若选到第 $i$ 个数，则当前点贡献到答案里时位置乘了 $\frac{1}{2}$，所以系数乘上概率后还要乘 $\frac{1}{2}$。

于是可以得到转移：

$$f_{i,j}=\frac{i-1}{i+j}f_{i-1,j}+\frac{1}{2}\cdot\frac{1}{i+j}f_{i-1,j}+\frac{j-1}{i+j}f_{i,j-1}+\frac{1}{2}\cdot\frac{1}{i+j}f_{i,j-1}$$

设 $g_{i,j}=(i+j)!f_{i,j}$，可以得到：

$$g_{i,j}=(i-\frac{1}{2})g_{i-1,j}+(j-\frac{1}{2})g_{i,j-1}$$
 
把 $(i,j)$ 当成网格图上的点，$(i-\frac{1}{2})$ 和 $(j-\frac{1}{2})$ 当成网格图上的边权。于是 $g_{i,j}$ 就是从左上角走到 $(i,j)$ 的所有路径的边权积之和。

而对于一个点 $(i,j)$，到这个点的所有合法路径上的边权积都是：

$$(i-\frac{1}{2})^{\underline{i-1}}(j-\frac{1}{2})^{\underline{j-1}}$$

而路径总数是 $\binom{i+j}{i}$，所以 $g_{i,j}$ 可以直接计算：

$$g_{i,j}=\binom{i+j}{i}(i-\frac{1}{2})^{\underline{i-1}}(j-\frac{1}{2})^{\underline{j-1}}$$

预处理 $n!$ 和 $(k−\frac{1}{2})$ 的下降幂即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,mo=998244353;
const int i2=499122177;
int n,an,fa[N],in[N],f1[N];
int pw(int x,int k){
	int no=1;
	while(k){
		if(k&1)no=no*x%mo;
		k>>=1,x=x*x%mo;
	}
	return no;
}
int c(int n,int k){
	if(n<k)return 0;
	return fa[n]*in[n-k]%mo*in[k]%mo;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n,fa[0]=in[0]=f1[0]=1;
	for(int i=1;i<N;i++){
		f1[i]=f1[i-1]*(i-i2+mo)%mo;
		fa[i]=fa[i-1]*i%mo;
	}
	in[N-1]=pw(fa[N-1],mo-2);
	for(int i=N-2;i>=1;i--)
		in[i]=in[i+1]*(i+1)%mo;
	for(int i=1;i<=n;i++){
		int x,no;cin>>x;
		no=c(n-1,i-1)*f1[i-1]%mo*f1[n-i]%mo;
		an=(an+no*in[n-1]%mo*x%mo)%mo;
	}
	cout<<an;
	return 0;
}
```

---

## 作者：是青白呀 (赞：1)

用线性性拆期望，那么每个点的坐标对最终答案的贡献都会带一个系数 $k_i$。

考虑 dp 求系数。设 $dp_{i,j}$ 表示左边有 $i$ 个点，右边有 $j$ 个点的贡献。首先有 $dp_{0,0}=1$，转移时枚举下一步删掉的是哪两个点，有：

$$
\begin{aligned}
dp_{i,j}&=\frac{i-1}{i+j}dp_{i-1,j}+\frac 12 \frac 1{i+j}dp_{i-1,j}+\frac{j-1}{i+j}dp_{i,j-1}+\frac 12\frac 1{i+j}dp_{i,j-1}\\
&=\frac{i-\frac12}{i+j}dp_{i-1,j}+\frac{j-\frac12}{i+j}dp_{i,j-1}\\
(i+j)!dp_{i,j}&=(i-\frac12)(i+j-1)!dp_{i-1,j}+(j-\frac12)(i+j-1)!dp_{i,j-1}\\
\end{aligned}
$$

不妨设 $f_{i,j}=(i+j)!dp_{i,j}$，有 $f_{i,j}=(i-\frac12)f_{i-1,j}+(j-\frac12)f_{i,j-1}$。

这是一个经典的网格图优化形式，等价于一个带权路径和问题：一条路径从 $(i-1,j)$ 走到 $(i,j)$，会乘上一个权值 $i-\frac12$，从 $(i,j-1)$ 走到 $(i,j)$，会乘上一个权值 $j-\frac12$，所有路径初始权值均为 $1$，$f_{i,j}$ 就表示从 $(0,0)$ 走到 $(i,j)$ 的所有路径的权值和。

不难发现从 $(0,0)$ 到 $(i,j)$ 的所有路径权值均为 $\prod_{x=1}^i(x-\frac12)\prod_{y=1}^j(y-\frac12)$，总合法路径数量为 $\binom{i+j}{i}$。于是预处理 $\prod_{x=1}^i(x-\frac12)$ 之后，$f$ 和 $dp$ 都可以 $O(1)$ 求了。复杂度瓶颈在预处理阶乘逆元，为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e6+5,M=6,S=(1<<15)+5,inf=(ll)8e18+7,mo=998244353;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,a[N];
int jc[N],qj[N],val[N];
int quick_power(int base,int x){
    int res=1;
    while(x){
        if(x&1)res*=base,res%=mo;
        base*=base,base%=mo;
        x>>=1;
    }
    return res;
}
int C(int x,int y){
    if(x<y)return 0;
    return jc[x]*qj[y]%mo*qj[x-y]%mo;
}
int inv2;
signed main(){
    read(n),inv2=quick_power(2,mo-2);
    rep(i,1,n)
        read(a[i]);
    jc[0]=qj[0]=val[0]=1;
    rep(i,1,n){
        val[i]=val[i-1]*(i-inv2+mo)%mo;
        jc[i]=jc[i-1]*i%mo;
        qj[i]=quick_power(jc[i],mo-2);
    }
    int ans=0;
    rep(i,1,n){
        int le=i-1,ri=n-i;
        int k=val[le]*val[ri]%mo*C(le+ri,le)%mo*qj[le+ri]%mo;
        ans+=k*a[i]%mo,ans%=mo;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：orange_new (赞：0)

节选自：[DP做题记录（三）（2025.4.5 - 2025.4.19）](https://www.luogu.com.cn/article/tobtmxka)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18841171)

我们先从简单的情况考虑，如果只有两个点 $x_1$ 和 $x_2$，那么中点一定是 $\displaystyle\frac{x_1}{2} + \frac{x_2}{2}$，如果有三个点 $x_1, x_2, x_3$，那么第一次分两种情况：

- 先合并 $x_1, x_2$，变成 $\displaystyle\frac{x_1}{2} + \frac{x_2}{2}$，再合并 $x_3$，变成 $\displaystyle\frac{x_1}{4} + \frac{x_2}{4} + \frac{x_3}{2}$；

- 先合并 $x_2, x_3$，变成 $\displaystyle\frac{x_2}{2} + \frac{x_3}{2}$，再合并 $x_1$，变成 $\displaystyle\frac{x_1}{2} + \frac{x_2}{4} + \frac{x_3}{4}$。

因此期望就是 $\displaystyle\frac 12 \times (\frac{x_1}{4} + \frac{x_2}{4} + \frac{x_3}{2}) + \frac 12 \times (\frac{x_1}{2} + \frac{x_2}{4} + \frac{x_3}{4}) = \frac 38 x_1 + \frac 14 x_2 + \frac 38 x_3$。

其实可以发现，最后的式子一定可以表示成 $\displaystyle\sum w_k x_k$，可以感性理解一下，每次求中点时，都把两边已经得到的式子乘了一个 $\displaystyle\frac 12$，这并不会改变式子的次数，只会改变式子的系数，因此我们现在需要求出所有的 $w_i$。

设 $dp_{i, j}$ 表示当前枚举的点（可能是合并出来的）左边还剩 $i$ 个点，右边还剩 $j$ 个点，中间这个点系数的期望。考虑本次合并，如果是将左边 $i$ 个点中任意两个点合并（一共 $i - 1$ 中合并方法），对当前枚举的这个点的系数没有影响，因此 $dp_{i, j}$ 首先要加上 $\displaystyle\frac{i - 1}{i + j}dp_{i - 1, j}$（系数表示从 $i + j$ 个可合并位置中选出 $i - 1$ 个位置的概率），同理，$dp_{i, j}$ 也要加上 $\displaystyle\frac{j - 1}{i + j} dp_{i, j - 1}$。

现在来考虑将枚举到的这个点合并进来，此时就要乘以系数 $\displaystyle\frac 12$，于是 $dp_{i, j}$ 还要加上 $\displaystyle\frac 12 \times \frac{1}{i + j} \times (dp_{i - 1, j} + dp_{i, j - 1})$，因此最终的转移方程就是 $dp_{i, j} = \displaystyle\frac{i - 1}{i + j} dp_{i - 1, j} + \frac 12 \frac {1}{i + j} dp_{i - 1,j} + \frac 12 \frac{1}{i + j} dp_{i, j - 1} + \frac{j - 1}{i + j} dp_{i, j - 1}$。一个点的贡献就是 $\displaystyle\sum dp_{i - 1, n - i} x_i$

我们现在考虑优化，首先一个优化方式就是将期望改写成总和除以总方案数，那么就可以将转移方程改写为 $dp_{i, j} = \displaystyle\frac{1}{(n - 1)!} [(i - \frac 12) dp_{i - 1, j} + (j - \frac 12) dp_{i, j - 1}]$。

现在就到了要充分发扬类人智慧的时候了，考虑 $dp$ 式子的组合含义（其实也可以直接矩乘加特征向量做，不过特别难算），那就相当于从 $(i, j)$ 这个点走到 $(0, 0)$，往上走需要花费 $i - \displaystyle\frac 12$ 的代价，往左走需要花费 $j - \displaystyle\frac 12$ 的代价，所有路径的代价和。那么我们一定走了 $i + j$ 步，其中 $i$ 步向上可以随时走，因此 $dp_{i, j} = \displaystyle\binom{i + j}{i} (i - \frac 12)^{\underline{i - 1}} (j - \frac 12)^{\underline{j - 1}}$。此时我们只需要预处理一下就可以 $O(n)$ 通过此题了。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 9, MOD = 998244353;
int x[N], fac[N], inv[N], des[N], c, n, ans;
int qpow(int a, int b){
	int res = 1;
	while(b > 0){
		if(b & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &x[i]);
	c = qpow(2, MOD - 2);
	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % MOD;
	inv[n] = qpow(fac[n], MOD - 2);
	for(int i = n - 1; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1) % MOD;
	des[0] = 1;
	for(int i = 1; i <= n; i++)
		des[i] = (i - c + MOD) % MOD * des[i - 1] % MOD;
	for(int i = 1; i <= n; i++)
		ans = (ans + x[i] * des[i - 1] % MOD * des[n - i] % MOD * inv[i - 1] % MOD * inv[n - i] % MOD) % MOD;
	printf("%lld", ans);
	return 0;
}
```

---

