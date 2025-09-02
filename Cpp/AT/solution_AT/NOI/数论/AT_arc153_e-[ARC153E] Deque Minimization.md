# [ARC153E] Deque Minimization

## 题目描述

对于一个每一位都不是 $0$ 的正整数 $X$，我们通过以下步骤得到一个正整数 $Y$：

- 用空字符串初始化字符串 $S$。
- 设 $X$ 的位数为 $N$，对于 $i = 1, \ldots, N$，依次将 $X$ 的十进制表示的第 $i$ 位插入到 $S$ 的开头或末尾。
- 将字符串 $S$ 视为正整数，得到 $Y$。

在所有可以通过上述步骤从 $X$ 得到的正整数中，最小的记为 $f(X)$。

------

现在给定一个每一位都不是 $0$ 的正整数 $Y$。请你计算有多少个每一位都不是 $0$ 的正整数 $X$ 满足 $f(X) = Y$，并将答案对 $998244353$ 取模后输出。

## 说明/提示

### 限制

- $Y$ 是一个每一位都不是 $0$ 的正整数
- $1 \leq Y < 10^{200000}$

### 样例解释 1

满足条件的 $X$ 有 $1332$、$3132$、$3312$，共 $3$ 个。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1332```

### 输出

```
3```

## 样例 #2

### 输入

```
3312```

### 输出

```
0```

## 样例 #3

### 输入

```
12234433442```

### 输出

```
153```

# 题解

## 作者：Demeanor_Roy (赞：6)

- [原题链接](https://www.luogu.com.cn/problem/AT_arc153_e)。

---

怎么都是区间 dp，怎么都是网格图。这里是一个更自然的想法。

对于这一类双端队列插入队首/队尾的问题，一个经典转化是：**新序列 $Y$ 是由老序列 $X$ 选择一个子序列沿一号元素翻折得到的**。

并且注意到，为了使新序列 $Y$ 最小，在本题中我们一定会选择 $X$ 的非严格前缀最小值构成的子序列翻折。倒过来考虑这个过程，我们找到 $Y$ 的最长不下降前缀，显然这些数就是原序列 $X$ 的非严格前缀最小值。

我们从把这些非严格前缀最小值插入回去的角度来计数合法的 $X$，显然插入的限制是：

- 这些数必须是非严格前缀最小值。即每个数必须插入在第一个严格比它小的数的前面。

- 其余数不能是非严格前缀小值。即其余每个数找到前缀中最后一个比它小的数，这个数必须插入到它前面。

于是这个前缀每个数的插入限制为必须插入到某个前缀中，我们记第 $i$ 个数的限制为 $lim_i$ 。

到此已经有一个 $n^2$ 的 dp，即 $f_{i,j}$ 表示这个前缀的第 $i$ 个数插入到第 $j$ 个位置的方案，有转移：

$$f_{i,j}=\sum \limits_{k \geq j}f_{i-1,k}[j \leq lim_i]$$

注意到这个 dp 形如**做一遍前缀和，清空数组的某个前缀**（后缀翻转就是前缀）。由于本题值域为 $1 \sim 9$，并且我们只用关心前缀中每个值连续段的开头和结尾的清空限制。所以清空操作只有常数次。

没有清空操作时，该问题是一个经典问题，即数组 $a$ 前缀和 $k$ 次得到数组 $b$，有：

$$b_i = \sum\limits_{j=1}^{i}a_j{i-j+k-1 \choose k-1}$$

这是加法卷积的形式，ntt 加速即可。时间复杂度 $(nV \log n)$。其中 $V$ 是值域大小。

---

## 作者：EuphoricStar (赞：6)

我们考虑给定 $X$，如何贪心地求 $f(X)$。

- 队列为空时加入队首或队尾都是一样的。
- 队列不为空，设队首为 $c$。因为我们的目标是最小化字典序，于是如果 $X_i \le c$，我们把 $X_i$ 加入队首，否则加入队尾。由此也容易发现，加入队首的数一定单调不升。

考虑到既可以在头部加数也可以在尾部加数，套路地考虑区间 dp。设 $f_{l, r}$ 为 $Y_{l \sim r}$ 对应的 $X$ 个数。设 $n = |Y|$，初值 $\forall i \in [1, n], f_{i, i} = 1$。有转移：

$$Y_{l - 1} \le Y_l, f_{l, r} \to f_{l - 1, r}$$

$$Y_l < Y_r, f_{l, r} \to f_{l, r + 1}$$

答案为 $f_{1, n}$。

至此可做到 $O(n^2)$。

考虑一些神奇的事情。我们对于 $(l, r)$ 建出网格图，若 $(l, r)$ 可转移到 $(l - 1, r)$ 或 $(l, r + 1)$ 就在二者之间连边。例如对于 $Y = \texttt{12234433442}$ 我们可以得到以下的网格图：

![](https://img.atcoder.jp/arc153/73eee5519e98726eadeb026a76db9503.png)

现在问题转化成了求这张网格图上，$\forall i \in [1, n], (i, i) \to (1, n)$ 的路径个数之和。

观察这张图，发现很多点和边是多余的。考虑删除它们。设 $Y_{1 \sim p}$ 是极长不降子段，那我们仅保留 $l \le p$ 的点。对于一个 $l$，它延伸出去的 $r$ 满足 $[l, r]$ 中除与 $l$ 在同一个同色连续段的点后不存在 $Y_i \le Y_l$。并且与 $l$ 在同一个同色连续段的非右端点的点没有向右的转移。

简化后的网格图长这样：

![](https://img.atcoder.jp/arc153/430a57378f7bf877ed591d3c72403725.png)

考虑倒序枚举 $l$，动态维护 $f_{l, r}$。对于一个同色连续段的 $l$ 合并考虑。设连续段长度为 $k$，你每次要做这样的事情：

- 在 $f_l$ 前添加 $k$ 个 $1$；
- 做 $k$ 遍从连续段右端点到 $R$ 的前缀和，其中 $R$ 为 $f_{l, r}$ 有效的最大的 $r$。

求序列 $a_{1 \sim n}$ 的 $k$ 阶前缀和容易使用 NTT 优化至 $O(n \log n)$，这里简单讲一下。设 $b_i$ 为 $k$ 阶前缀和后的序列。考虑 $a_j$ 对 $b_i$ 的贡献系数。不难发现每次前缀和时 $j$ 可以贡献到 $\ge j$ 的所有位置。贡献系数也就是满足 $p_0 = j \le p_1 \le p_2 \le \cdots \le p_m = i$ 的 $p$ 序列个数。容易插板法得到贡献系数为 $\binom{i - j + k - 1}{k - 1}$。于是我们有 $b_i = \sum\limits_{j = 1}^i a_j \times \binom{i - j + k - 1}{k - 1}$，这是显然的加法卷积形式，NTT 优化即可。

因为有效的 $l$，$Y_l$ 单调不降，所以同色连续段个数是 $O(|\Sigma|)$ 的。因此最后的时间复杂度就是 $O(|\Sigma| n \log n)$。

[code](https://atcoder.jp/contests/arc153/submissions/43226101)

------

**启发：对于 $f_{l, r}$ 只能贡献到 $f_{l + 1, r}$ 和 $f_{l, r - 1}$ 的 区间 dp，考虑建出网格图，去除无用点和边后可能可以做到更优。**

---

## 作者：cyh_toby (赞：5)

考虑从 $Y$ 逆推回 $X$。假设 $Y$ 的开头两个字符为 $x,y$，最后一个字符为 $z$，即 $Y=xy\dots z$。考虑最后一步插入的是 $x$ 还是 $z$。

- 若 $x\le y$，则可以是 $x$；否则，一定不可以是 $x$，不然把 $x$ 插入到末尾一定得到更小的 $Y$。

- 若 $z>x$，则可以是 $z$；否则，一定不可以是 $z$，不然把 $z$ 插入到开头一定有：如果整个串都是同一个字符，则与第一种情况等效，不应重复计数；否则可以归纳证明能得到更小的 $Y$。

据此已经可以 $O(n^2)$ 区间 DP 了。

考虑一个状态 $(L,R)$，表示 $Y[L:R]$ 的 DP。

- 由于转移 $(L,R)\leftarrow (L+1,R)$ 一定要满足 $Y_L\le Y_{L+1}$，并且我们只关心 $(1,n)$，所以取出 $Y$ 的极长不降前缀 $[1,p]$，则只有 $L\le p$ 的状态是有用的。所以可以按 $p\to 1$ 的顺序枚举 $L$，这样在 $Y_L$ 上就具有了单调性，这对下一步优化很有用。
- 对于 $R\in [p+1,n]$ 的状态，如果存在 $i\in [p+1, R]$ 满足 $Y_i\le Y_L$，则这个状态的 DP 值一定是 $0$。因为结合第二种转移的条件以及上一步得到的 $Y_L$ 的单调性，可以发现怎么走都走不到 $R$。
- 对于 $R\in [L,p]$ 的状态，只要 $Y_R>Y_L$ 即可以 $(L,R)\leftarrow (L,R-1)$。

于是，每次从 $L+1\to L$，相当于继承状态，然后把 $(L,L)$ 置为 $1$，再对一段区间进行前缀和。显然，对于 $Y_L$ 相同的 $L$，做前缀和的区间时一样的，而这样的 $L$ 又恰好构成一段区间，所以可以放在一起做。从生成函数的角度看，就是卷上一个组合数序列，可以使用 NTT 优化。总共只有 $|\Sigma|=9$ 段 $L$ 构成的区间，所以复杂度是 $O(|\Sigma|n\log n)$ 的，可以通过。

[代码](https://atcoder.jp/contests/arc153/submissions/38038051)



---

## 作者：ღꦿ࿐ (赞：3)

神仙题。

首先考虑 Minimization 的策略，假设现在队首为 $f$, 如果加入的数 $Y_i < f$，放在队首是绝对更优的，如果 $y_i=f$，又因为这个数从前面放入的部分显然是不减的，所以放入一个新的相同的字符是不劣的。

计算 $X$ 的数量，相当于我们需要计算合法的 LR 序列数，但有和队首相同且整个序列都相同时 L 和 R 是等价的，所以钦定和队首相同时放到前面。

最开始的想法是：考虑枚举前面和后面放入的分界点，然后把单增的前半部分和后半部分“交叉”起来，使得每个放入后面的数都严格大于放入前面的，后来发现这样无法做到低于 $O(n^2|S|)$ 的复杂度，有很多东西被求出了很多次，没法继续下去了。

考虑一个信息利用效率高的做法——dp，令 $f[l,r]$ 表示 $Y[l,r]$ 可能对应的 $X$ 的个数，那么有转移：

$$
f[l,r]\to f[l,r+1] \quad (Y_r > Y_l)
$$


$$
f[l,r]\to f[l-1,r] \quad (Y_{l-1}\leq Y_l)
$$

于是我们可以 $O(n^2)$ 地解决这个问题了，考虑优化：

是发现很多状态是没有用的，比如对于串 $\texttt{1234543333332}$ 来说，$f[6,x]$ 都是没用的，因为结合我们前面说的，从前面插入的串一定是一个不降的串，这些状态显然无法转移到 $f[1,n]$，同样地，$f[5,7]$ 也是无用的，因为 $Y_r<Y_l$ 或 $Y_r=Y_l$ 且不是只用一种数字组成的串都是不可能出现的。

因为这个转移只和 $l,r$ 差 1 的相关，经典地，把 dp 状态看作一个网格，$f[l,r]$ 看作点 $(l,r)$，那么网格大概是这样的：

例串：$\texttt{122455452}$，有用的转移如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/79n45i3t.png)

即：保留开头一段单调不减的行，然后对于每一个行，它的最右端为它这段的末端后第一个小于等于它的数，每种数的转移都是前面的只能向上，最后一列多出来的那部分才能向右走（即图中的 $(2,3),(3,3)$，而 $(2,2)$ 不能。），求所有蓝色格子到 $(1,n)$ 的路径条数之和。

因为字符集大小 $|S|=9$，所以这个“阶梯”最多有九层，每层都形如下面这个形状：

![](https://cdn.luogu.com.cn/upload/image_hosting/mjadn25l.png)

因为这个形状的性质，左边那个三角形上方的那些点都是 $1$，总共又只有 $9$ 个阶梯，于是考虑从下往上处理每一个阶梯，并将结果代入下一个阶梯，

假设这个阶梯高 $len$，从原本的位置 $i$ 走到新阶梯开头的位置 $j$ 的方案数是 $\binom {j-i+len}{len}$， 容易发现这是一个卷积形式，即给原式的那个长方形对应的段乘上一个 $g(x)=\binom{i+len}{len}\times x^i$，再将三角形的底部赋为 $1$，传给下一个阶梯就可以解决了。

使用 NTT 进行卷积的运算，时间复杂度 $O(|S|n\log n)$。

代码：

实现很短，使用了 atcoder 库中的 ``modint998244353`` 类和 ``convolution`` 函数。

```cpp
#define Z atcoder::modint998244353
#define poly vector<Z>
signed main()
{
    init( ) ; 
    read(s) ;
    n = strlen(s);
    Z unit = 1 ,zero = 0; 
    int lim = n ;
    for(int i = 1 ; i < n ; i ++) {
        if(s[i]<s[i-1]){lim = i;break;}
    }
    poly scan(n,zero);
    fill(scan.begin( ),scan.begin()+lim,unit);
    for(char c='9';c>='1';--c) {
        lb=tr=rb=-1;
        for(int i = 0 ; i < n ; ++ i) if(s[i] == c) {lb = i;break;}
        tr = lb ; while(tr+1<n&&s[tr+1]==c) tr++;
        rb = tr + 1 ; while(rb<n&&s[rb]>c) rb++;
      	if(lb==-1||lb>=lim) continue ;
        // [lb,rb)是有值的区间        
        poly tf,tg;tf.clear() , tg.clear() ; 	
        for(int i = 0 ; i < rb - tr ; ++ i) {
           Z x ; x = C( tr - lb + i , i ) ; 
            tg.emplace_back( x );
        }
        for(int i = tr ; i < rb ; ++ i) {
            tf.emplace_back(scan[i]);
        }
        poly co = convolution(tf , tg) ;
        for(int i = tr ; i != rb ; ++ i) scan[i] = co[i - tr] ; 
        for(int i = lb ; i < tr ; ++ i) scan[i] = 1 ;
      	
    }   
    cout << scan[n-1].val( ) ;
    return 0;
}
```
---

参考了 AtCoder 原题解。

收录于[《超级无敌神仙炫酷无敌原神大王好题》](https://dreamerkk.blog.luogu.org/good-probs) 。


---

## 作者：tzc_wk (赞：1)

挺套路的一道题。

先考虑怎样对给定的 $X$ 计算 $f(X)$：贪心，每次添加一个字符时，如果它 $\le$ 最高位的值就把它添加到最高位，否则把它添加到最低位。容易证明贪心的正确性。

将整个操作倒过来，改为每次删掉最前或者最后一个字符。删掉最前一个字符是合法的当且仅当下一个字符 $\ge$ 第一个字符，删掉最后一个字符是合法的当且仅当开头的字符比它小。如此操作直到只剩一个字符为止。这样可以得到一个 $n^2$ 的做法。

考虑优化。我们还没有使用值域 $\le 9$ 的性质，因此我们尽力往这个方向思考。发现最后删除的字符可能是 $i$，当且仅当对于任意 $1\le j<i$ 都有 $a_j\le a_{j+1}$，只要最后一个字符符合这个限制就不用考虑删左端点的限制。也就是左边的部分我们其实相当于每次加入一个连续段。而加入连续段对右端点的限制是分界点必须超过右边最靠左的 $\le v$ 的位置，因此 DP 数组的变化可以使用 NTT 来求出（另一种等价的理解方式是有高度限制的[网格图计数](https://www.cnblogs.com/tzcwk/p/Codeforces-1770G.html)，你把删左边看作左移指针，删右边看作右移指针就是这个模型，只不过这题高度限制的连续段最多只有 $9$ 个，所以不用分治 NTT，普通 NTT 就行了）。

注意特判最后一个连续段，其他细节可以借助代码来理解。时间复杂度 $O(Vn\log n)$，其中 $V=9$ 表示值域。

```cpp
const int MAXN=4e5;
const int MAXP=524288;
const int pr=3;
const int ipr=332748118;
const int MOD=998244353;
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD)if(e&1)ret=1ll*ret*x%MOD;return ret;}
int n,a[MAXN+5],fac[MAXN+5],ifac[MAXN+5],res;char s[MAXN+5];
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=ifac[1]=1)+1;i<=n;i++)ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
int binom(int n,int k){if(n<0||k<0||n<k)return 0;return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;}
int rev[MAXP+5];
void NTT(vector<int>&a,int len,int type){
	int lg=31-__builtin_clz(len);
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<lg-1);
	for(int i=0;i<len;i++)if(rev[i]<i)swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		int W=qpow((type<0)?ipr:pr,(MOD-1)/i);
		for(int j=0;j<len;j+=i){
			for(int k=0,w=1;k<(i>>1);k++,w=1ll*w*W%MOD){
				int X=a[j+k],Y=1ll*w*a[(i>>1)+j+k]%MOD;
				a[j+k]=(X+Y)%MOD;a[(i>>1)+j+k]=(X-Y+MOD)%MOD;
			}
		}
	}
	if(type<0){
		int iv=qpow(len,MOD-2);
		for(int i=0;i<len;i++)a[i]=1ll*a[i]*iv%MOD;
	}
}
vector<int>conv(vector<int>a,vector<int>b){
	int LEN=1;while(LEN<a.size()+b.size())LEN<<=1;
	a.resize(LEN,0);b.resize(LEN,0);NTT(a,LEN,1);NTT(b,LEN,1);
	for(int i=0;i<LEN;i++)a[i]=1ll*a[i]*b[i]%MOD;
	NTT(a,LEN,-1);return a;
}
int dp[12][MAXN+5],flg[MAXN+5],cnt[12];
int main(){
	scanf("%s",s+1);n=strlen(s+1);init_fac(MAXN);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	flg[1]=1;for(int i=2;i<=n;i++)flg[i]=flg[i-1]&(a[i]>=a[i-1]);
	for(int i=1;i<=n;i++)if(flg[i])cnt[a[i]]++;
	dp[0][n]=1;
	for(int i=1;i<=9;i++){
		if(!cnt[i]){for(int j=1;j<=n;j++)dp[i][j]=dp[i-1][j];}
		else{
			int mn=n+1;
			for(int j=1;j<=n;j++)if(!flg[j]&&a[j]<=i)chkmin(mn,j);
			vector<int>A,B,C;
			for(int j=n;j;j--)A.pb(dp[i-1][j]*(j<mn));
			for(int j=0;j<=n;j++)B.pb(binom(j+cnt[i]-1,cnt[i]-1));
			C=conv(A,B);
			for(int j=1;j<mn;j++)dp[i][j]=C[n-j];
		}
	}
	for(int l=1,r;l<=n&&flg[l];l=r){
		r=l;while(r<=n&&a[r]==a[l])++r;
		for(int j=l;j<r;j++)res=(res+dp[a[l]-1][j])%MOD;
		for(int j=r;j<=n;j++){
			if(a[j]<=a[l])break;
			res=(res+1ll*dp[a[l]-1][j]*binom(j-l,r-l-1))%MOD;
		}
	}printf("%d\n",res);
	return 0;
}
/*
11243
*/
```



---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc153_e)

**题目大意**

> 给定十进制串 $X$，记 $f(X)$ 表示按如下方式能得到的最小十进制串 $Y$：
>
> - 从高到低考虑 $X$ 的每一位，分别加入 $Y$ 的首部或尾部。
>
> 给定 $Y$，求有多少 $X$ 使得 $f(X)=Y$。
>
> 数据范围：$|Y|\le 2\times 10^5$。

**思路分析**

考虑 $f(X)$ 的计算过程：显然对于当前位，如果小于 $Y$ 的首位就放到队头，如果大于 $Y$ 的首尾就放到队尾，如果等于 $Y$ 的首尾，由于放到队头的若干个数单调不降，因此放到队头也一定更优。

因此我们可以得到一个区间 dp：$f_{l,r}=f_{l+1,r}\times [Y_l\le Y_{l+1}]+f_{l,r-1}\times[Y_r>Y_l]$。

把整个转移写在网格图上（图源官方题解）：

![](https://img.atcoder.jp/arc153/73eee5519e98726eadeb026a76db9503.png)

要求的就是从 $(i,i)\to (1,n)$ 的路径数量和，注意到很多位置与 $(1,n)$ 不连通。

首先我们发现，如果 $Y[1,l]$ 不是单调递增的，那么 $(l,r)$ 与 $(1,n)$ 不连通。

因此我们要考虑的 $l$ 一定是前缀递增的一个连续段，这些区域有一个很好的性质，就是所有向上走的转移（$f_{l,r}\to f_{l-1,r}$）始终都是存在的，那么可以考虑倒着维护每一行，即 $l$ 递减地维护 $f_{l,*}$。

暴力转移肯定不优，不妨尝试把这段递增前缀中值相同的缩起来，这样我们就只要处理 $\mathcal O(|\Sigma|)$ 个连续段了。

对于相同的一段 $Y_{[a,b]}$，观察网格图的形状：左侧是一个只能向上走的阶梯，那么 $f_{a,a}\sim f_{a,b}=1$。

然后右侧是若干连续向右的矩形转移，直到 $(b,n]$ 中第一个 $x$ 使得 $Y_x>Y_b$，那么 $[b,x)$ 这个范围内所有 $f_{l,r}\to f_{l,r+1}$ 的转移都是存在的。

可以发现 $f_{[a,b],[x,n]}$ 这个范围内的值无法被某个 $f_{i,i}$ 转移到，也不需要考虑。

那么我们只要考虑 $f_{b,[b,x)}\to f_{a,[b,x)}$ 的过程，容易发现这就是进行了 $k=b-a+1$ 次前缀和操作。

根据插板法可以直接算出多次前缀和的转移系数：$f_{b,i}\to f_{a,j}$ 的系数为 $\binom{j-i+k-1}{k-1}$，因此直接卷积一遍就能快处理 $k$ 阶前缀和。

时间复杂度 $\mathcal O(|\Sigma|n\log n)$，其中 $|\Sigma|=9$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace P {
const int MOD=998244353,N=1<<19,G=3;
int rev[N],inv[N],w[N<<1];
int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	for(;b;a=1ll*a*a%p,b=b>>1) if(b&1) ret=1ll*ret*a%p;
	return ret;
}
void poly_init() {
	inv[1]=1;
	for(int i=2;i<N;++i) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(int k=1;k<=N;k<<=1) {
		int x=ksm(G,(MOD-1)/k); w[k]=1;
		for(int i=1;i<k;++i) w[i+k]=1ll*x*w[i+k-1]%MOD;
	}
}
int plen(int x) { int y=1; for(;y<x;y<<=1); return y;  }
void ntt(int *f,bool idft,int n) {
	for(int i=0;i<n;++i) {
		rev[i]=(rev[i>>1]>>1);
		if(i&1) rev[i]|=n>>1;
	}
	for(int i=0;i<n;++i) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int k=2,x,y;k<=n;k<<=1) {
		for(int i=0;i<n;i+=k) {
			for(int j=i;j<i+k/2;++j) {
				x=f[j],y=1ll*f[j+k/2]*w[k+j-i]%MOD;
				f[j]=(x+y>=MOD)?x+y-MOD:x+y,f[j+k/2]=(x>=y)?x-y:x+MOD-y;
			}
		}
	}
	if(idft) {
		reverse(f+1,f+n);
		for(int i=0,x=ksm(n);i<n;++i) f[i]=1ll*f[i]*x%MOD;
	}
}
void poly_mul(const int *f,const int *g,int *h,int n,int m) {
	static int a[N],b[N];
	for(int i=0;i<n;++i) a[i]=f[i];
	for(int i=0;i<m;++i) b[i]=g[i];
	int len=plen(n+m-1);
	ntt(a,0,len),ntt(b,0,len);
	for(int i=0;i<len;++i) h[i]=1ll*a[i]*b[i]%MOD;
	ntt(h,1,len);
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
}
}
const int N=1<<19,MOD=998244353;
int n,dp[N],f[N],g[N],h[N],fac[N],ifac[N];
char str[N];
int C(int x,int y) { return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD; }
void upd(int l,int r,int k) {
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(h,0,sizeof(h));
	for(int i=0;i<=r-l;++i) f[i]=dp[i+l],g[i]=C(i+k-1,k-1);
	P::poly_mul(f,g,h,r-l+1,r-l+1);
	for(int i=0;i<=r-l;++i) dp[i+l]=h[i];
}
signed main() {
	P::poly_init();
	for(int i=fac[0]=ifac[0]=1;i<N;++i) ifac[i]=P::ksm(fac[i]=1ll*fac[i-1]*i%MOD);
	scanf("%s",str+1),n=strlen(str+1);
	vector <array<int,3>> seq;
	for(int i=1;i<=n;) {
		int j=i;
		while(j<n&&str[j+1]==str[i]) ++j;
		seq.push_back({i,j,str[i]-'0'}),i=j+1;
		if(i>n||str[i-1]>str[i]) break;
	}
	reverse(seq.begin(),seq.end());
	for(auto p:seq) {
		for(int i=p[0];i<=p[1];++i) dp[i]=1;
		int i=p[1];
		while(i<n&&str[i+1]-'0'>p[2]) ++i;
		upd(p[1],i,p[1]-p[0]+1);
	}
	printf("%d\n",dp[n]);
	return 0;
}
```

---

