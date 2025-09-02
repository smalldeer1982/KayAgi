# [ABC288D] Range Add Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc288/tasks/abc288_d

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ と正整数 $ K $ が与えられます。

各 $ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ A $ の連続部分列 $ (A_{l_i},\ A_{l_i+1},\ \ldots,\ A_{r_i}) $ が**良い数列**かどうかを判定してください。

ここで、長さ $ n $ の数列 $ X\ =\ (X_1,\ X_2,\ \ldots,\ X_n) $ は、下記の操作を好きな回数（ $ 0 $ 回でも良い）だけ行うことによって、$ X $ のすべての要素を $ 0 $ にすることができるとき、かつ、そのときに限り**良い数列**です。

> $ 1\ \leq\ i\ \leq\ n-K+1 $ を満たす整数 $ i $ および、整数 $ c $ （負の数でも良い）を選び、$ K $ 個の要素 $ X_{i},\ X_{i+1},\ \ldots,\ X_{i+K-1} $ のそれぞれに $ c $ を加算する。

なお、すべての $ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ r_i\ -\ l_i\ +\ 1\ \geq\ K $ が保証されます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ \min\lbrace\ 10,\ N\ \rbrace $
- $ -10^9\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ l_i,\ r_i\ \leq\ N $
- $ r_i-l_i+1\ \geq\ K $
- 入力はすべて整数
 
### Sample Explanation 1

数列 $ X\ \coloneqq\ (A_1,\ A_2,\ A_3,\ A_4,\ A_5,\ A_6)\ =\ (3,\ -1,\ 1,\ -2,\ 2,\ 0) $ は良い数列です。 実際、下記の手順で操作を行うことで、すべての要素を $ 0 $ にすることができます。 - まず、$ i\ =\ 2,\ c\ =\ 4 $ として操作を行う。その結果、$ X\ =\ (3,\ 3,\ 5,\ 2,\ 2,\ 0) $ となる。 - 次に、$ i\ =\ 3,\ c\ =\ -2 $ として操作を行う。その結果、$ X\ =\ (3,\ 3,\ 3,\ 0,\ 0,\ 0) $ となる。 - 最後に、$ i\ =\ 1,\ c\ =\ -3 $ として操作を行う。その結果、$ X\ =\ (0,\ 0,\ 0,\ 0,\ 0,\ 0) $ となる。 よって、$ 1 $ 行目には `Yes` を出力します。 一方、数列 $ (A_2,\ A_3,\ A_4,\ A_5,\ A_6,\ A_7)\ =\ (-1,\ 1,\ -2,\ 2,\ 0,\ 5) $ は、 どのような手順で操作を行ってもすべての要素を $ 0 $ にすることはできないため、良い数列ではありません。 よって、$ 2 $ 行目には `No` を出力します。

## 样例 #1

### 输入

```
7 3
3 -1 1 -2 2 0 5
2
1 6
2 7```

### 输出

```
Yes
No```

## 样例 #2

### 输入

```
20 4
-19 -66 -99 16 18 33 32 28 26 11 12 0 -16 4 21 21 37 17 55 -19
5
13 16
4 11
3 12
13 18
4 10```

### 输出

```
No
Yes
No
Yes
No```

# 题解

## 作者：_cyle_King (赞：7)

> 蛮简单的一道题。~~但是因为杨康后被降智，5 分钟想出的思路调了半个个小时。~~
## 题意
给定一个正整数 $k$。

定义一个长度为 $m$ 的整数序列  $B$ 是合法的，当且仅当 $B$ 中元素能通过有限次数的以下操作，使得 $B$ 以内的所有元素变为 $0$。

- 选定 $B$ 的一个长度为 $k$ 的子串，将这个子串内的数同时加上一个整数 $c$（可能小于 $0$）。

给定一个长度为 $n$ 的整数序列 $A$，有  $Q$ 次询问，每次询问给出一个区间 $[L,R]$，询问 $A$ 下标在 $[L,R]$  内的子串是否合法，**每次询问不会真正进行操作，即 $A$ 不会变化**。
### 数据范围
- $1\leq n,Q\leq 2\times10^5$
- $1\leq k\leq \min\{n,10\}$
- $|A_i|\leq 10^9$
- $1\leq L\leq L+k-1\leq R\leq n$
## 分析
~~好吧我承认上面的内容基本上是搬运题面。~~

设 $D$ 为 $A$ 的差分数组，受个人习惯影响，定义 $D_i=\begin{cases}A_i&,i=1\\ A_i-A_{i-1}&,i>1\end{cases}$，观察考虑上提到的操作对 $D$ 的影响。

发现，$[l,r](l=r-k+1)$ 区间加上 $c$，对 $D$ 的影响只有
$$
\begin{aligned}
	D_{l}&\leftarrow D_{l}+c\\
   D_{r+1}&\leftarrow D_{r+1}-c
\end{aligned}
$$
不难察觉，相当于从 $D_{r+1}$ 中抽出一个 $c$ 给到 $D_{l}$，而由于 $l+k=r+1$，因此一次操作相当于从 $D_{l+k}$ 中抽出一个 $c$ 给到 $D_{l}$。

发现 $k$ 很小，于是在 $k$ 上做文章，将序列 $D$ 按照下标 $i\bmod k$ 分成 $k$ 类，按照原来顺序连接，则一次操作相当于在某一类相邻的两个数之间转移一个 $c$。

~~语文不好，美术来凑，~~ 给张图更便于理解，下面是 $n=9,k=4$ 时的分类情况，相同的类用一样的颜色连起来。

![抱歉，图炸了。](https://cdn.luogu.com.cn/upload/image_hosting/osty6f6j.png)
$\tiny{\color{White}{\text{可是你美术也不好。}}}$

$\tiny{\text{未经本人许可，请不要引用。}}$

操作前后同一类中的数的和为定值，记为 $V$。不难证明通过操作，能使得这一类组成的序列变成任何和为 $V$ 的等长序列。

下面来考虑什么时候区间 $[L,R]$ 会全为 $0$。

发现要满足：$D_L=-A_{L-1}$，而对于 $L<i\leq R$，都有 $D_{i}=0$。

其实就是判定每一个类在区间 $[L,R]$ 中的和是否为 $0$，这里有两种特殊情况。
1. $D$ 中下标 $i$ 满足 $i\equiv R+1\pmod k$ 的部分所在的类。此类中的所有的数可以转移到 $R+1$，从而转移出 $[L,R]$，因此这一部分一定合法。
2. $D$ 中下标 $i$ 满足 $i\equiv L\pmod k$ 的部分所在的类。此类中的和为 $-A_{L-1}$。

其他的类的和为 $0$ 即可。

预处理每一个类的前缀和，可以做到 $O(k(n+Q))$。

### Code
赛场代码，有一些地方写的相当地憨批，仅供借鉴。
```cpp
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<climits>
#include<ctime>
#include<chrono>
#include<cassert>
#include<algorithm>
#include<iterator>
#include<numeric>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<bitset>
#include<functional>
#include<random>

using namespace std;
template<class T1,class T2>inline bool cmax(T1 &a,T2 b) {return a<b?a=b,1:0;}
template<class T1,class T2>inline bool cmin(T1 &a,T2 b) {return b<a?a=b,1:0;}
typedef pair<int,int> pii;
typedef long long LL;

const int N=2e5+10,M=10;

int n,m,k,a[N+1],b[N+1];
LL s[M+1][N+1];

inline int
id(int x){
    return (x-1)%k+1;
}

int
main(){
    ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    memcpy(b,a,sizeof(a));
    for(int i=n;i>=1;i--)a[i]-=a[i-1];
    //for(int i=1;i<=k;i++)s[i][i]=a[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++)s[j][i]=s[j][i-1];
        s[id(i)][i]+=a[i];
    }
    cin>>m;
    while(m--){
        int l,r;cin>>l>>r;
        bool flg=0;
        for(int j=l;j<=l+k-1;j++){
        	int i=id(j);
        	if(i!=id(r+1)){
	        	if(i!=id(l)){
	        		if((s[i][r]-s[i][l-1])!=0){
	        			flg=1;break;
					}
				}else{
					if((s[i][r]-s[i][l])+b[l]!=0){
						flg=1;break;
					}
				}
			}
		}
        if(flg)cout<<"No"<<'\n';
        else cout<<"Yes"<<'\n';
    }
    cout<<endl;
    return 0;
}

```

## 提醒
1. 语文不好，感性理解。

2. 尽管我没有写防抄袭，请不要 Ctrl A + Ctrl C + Ctrl V，这并不是一件好事。$\tiny{\color{White}\text{因为不想让你看见隐藏文字。}}$

 # End
 
 
 
 
 
 

---

## 作者：Down_syndrome (赞：5)

**这里给出一种目前其它题解都没有的时空复杂度 $O(n)$ 的方法，目前是洛谷最优解。当然 $O(nk)$ 的方法也会详细说明。**

## $O(nk)$ 

令 $f_i$ 表示对于区间 $[i,i+k-1]$ 要减小的数使得 $a_l=a_{l+1}=……=a_r=0$。容易发现，$f_l=a_l$，因为只有 $[l,l+k-1]$ 的操作能改变 $a_l$ 的值。这里先探讨 $k=3$ 的情况，可以发现，$f_{l+1}=a_{l+1}-a_l$，因为第一次的操作令 $a_{l+1}\gets a_{l+1}-a_l$，所以第二次的操作要减去对应的值。然后可以发现，$f_{l+2}=a_{l+2}-a_l-(a_{l+1}-a_{l})=a_{l+2}-a_{l+1}$。有没有发现什么规律？令 $b$ 作为 $a$ 的差分数组，也就是 $b_i=a_i-a_{i-1}$，那么可以发现一个规律：
$$
f_i=\left\{
\begin{aligned}
&a_l\ (i=l)\\
&b_i\ (l<i\le l+k-1)
\end{aligned}
\right.
$$
**为什么是差分？**

为什么有以上差分的规律？

可以发现，当 $l<i\le l+k-1$ 的时候，前面的 $i-l$ 次操作都会影响到 $a_i$ 的值。而显然的是，$\sum\limits_{j=l}^{i-1}f_j=a_{i-1}\ (l<i\le l+k-1)$，因为要让 $a_{i-1}$ 清空，所以 $f_i=a_i-\sum\limits_{j=l}^{i-1}f_j=a_i-a_{i-1}=b_i\ (l<i\le l+k-1)$。

那为什么当 $i>l+k-1$ 时就不会奏效了呢？

**当 $i>l+k-1$ 时**

有以上差分规律的前提是，前面的 $i-l$ 次操作都会影响到 $a_i$ 的值。而 $i>l+k-1$ 时，显然不具备这种条件。所以我们来推一推式子：
$$f_i=a_i-\sum\limits_{j=i-k+1}^{i-1}f_j=a_i-\left(\left(\sum\limits_{j=i-k}^{i-2}f_j\right)-f_{i-k}+f_{i-1}\right)=a_i-(a_{i-1}-f_{i-1}-f_{i-k}+f_{i-1})=f_{i-k}+b_i\ (l+k-1<i\le r)$$
总结一下，结合上面的式子，可以得到：
$$
f_i=\left\{
\begin{aligned}
&a_l\ (i=l)\\
&b_i\ (l<i\le l+k-1)\\
&f_{i-k}+b_i\ (l+k-1<i\le r)
\end{aligned}
\right.
$$
仔细观察一下，可以发现，$i\equiv i-k\pmod{k}$，那第三条式子就像同余的差分的前缀和，所以其实还能吧上述式子改写：
$$f_i=\left(\sum\limits_{j=l}^{i-1}[i\equiv j\pmod{k}]\times b_j\right)+[i\equiv l\pmod{k}]\times a_{l-1}\ (l\le i\le r)$$
这样我们就能很好地预处理出一个二维 $s$ 数组：
$$s_{i,j}=\sum\limits_{l=1}^{i}[l\equiv j\pmod{k}]\times b_l\ (1\le i\le n,0\le j<k)$$
那么 $f$ 就是：
$$f_i=s_{i,i\bmod k}-s_{l-1,i\bmod k}+[i\equiv l\pmod{k}]\times a_{l-1}\ (l\le i\le r)$$

**问题的解决**

说了那么多，$f$ 和问题有什么关系呢？不难推出，$[l,r]$ 是 good 序列，当且仅当 $f_{r-k+2}=f_{r-k+3}=……=f_r=0$，因为后面 $k-1$ 位操作不了，会突出区间，所以，每次用 $O(k)$ 判断是否为 $0$ 就行了！
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k,q,l,r,a[N],s[N][10];
bool flag;
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		for(int j=0;j<k;j++) s[i][j]=s[i-1][j];
		s[i][i%k]+=a[i]-a[i-1];
	}
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld",&l,&r);
		flag=1;
		for(int i=max(r-k+2,l);i<=r;i++){
			if(i%k==l%k&&s[i][i%k]-s[l-1][i%k]+a[l-1]!=0){
				flag=0;
				break;
			}
			if(i%k!=l%k&&s[i][i%k]-s[l-1][i%k]!=0){
				flag=0;
				break;
			}
		}
		if(flag) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```
## 从 $O(nk)$ 到 $O(n)$
虽然 $O(nk)$ 的算法已经很优秀了，并且能够轻松通过本题，但是当 $k$ 很大时，就会时空双炸。实际上，可以对此进行优化。

先说较为简单的空间的优化。容易发现，我们只需要查询 $s_{i,i\bmod k}$ 的值，也就是说对于 $i\bmod k\ne j$，$s_{i,j}$ 的值是没有用的，所以我们考虑对 $s$ 数组进行优化。事实上，只存一个 $s$ 是没有用的，我们考虑重新定义两个一维数组 $s$ 和 $sk$。我们预处理出 $s$ 和 $sk$：
$$s_i=\sum\limits_{j=1}^ib_j$$
$$sk_i=\sum\limits_{j=1}^i[i\equiv j\pmod{k}]\times b_j$$
或许有人会说：这个 $s$ 数组有什么用呢？不就是 $a$ 吗？我们一会说。

再来考虑时间优化。想想时间复杂度的瓶颈在哪？在 $k$ 次的比较。那么有什么办法可以优化这 $k$ 次比较的时间？事实上，如果 $a_1=a_2=……=a_m=0$，那么一定有 $a_1+a_2+……+a_m=0$。但是如果反过来，知道了 $a_1+a_2+……+a_m=0$，是不能推出 $a_1=a_2=……=a_m$ 的。但是如果乘上一个随机的权值呢？或许你已经想到我在说什么了。没错，优化的方法就是哈希。如果 $a_1\times Hash_1+a_2\times Hash_2+……+a_m\times Hash_m=0$，那么大概率就有 $a_1=a_2=……=a_m=0$。所以，对于每一个 $i\in[0,k)$，随机赋一个哈希值，再更改一下 $s$ 和 $sk$ 的定义：
$$s_i=\sum\limits_{j=1}^ib_j\times Hash_{j\bmod k}$$
$$sk_i=\sum\limits_{j=1}^i[i\equiv j\pmod{k}]\times b_j\times Hash_{j\bmod k}$$
每次 $O(1)$ 算出后 $k-1$ 个数的哈希值的和（用 $s$ 的值减 $sk$ 的值），如果为 $0$，就输出 `YES`，否则输出 `NO`。

顺带一提，这时候 $s$ 与 $sk$ 的调用就比较复杂了，需要知道小于等于 $x$ 的最大的模 $y$ 余 $z$ 的值是多少，不知道怎么求可以[戳这里](https://www.luogu.com.cn/paste/0tq64lpv)。

具体的实现可以看看代码。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template <class I>
	inline void read (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	template <class I>
	inline void write (I x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: write;
using io :: putc;
const int N=2e5+5;
const int mod=998244353;
int n,k,q,l,r,w,ans,a[N],b[N],s[N],sk[N],val[10];
signed main(){
	srand((int)time(0));
	read(n);
	read(k);
	for(int i=0;i<k;i++) val[i]=rand()*rand()%mod;
	for(int i=1;i<=n;i++){
		read(a[i]);
		b[i]=((a[i]-a[i-1])%mod+mod)%mod;
	}
	for(int i=1;i<=n;i++){
		s[i]=(s[i-1]+b[i]*val[i%k])%mod;
		sk[i]=(sk[max(i-k,0ll)]+b[i]*val[i%k])%mod;
	}
	read(q);
	while(q--){
		read(l);
		read(r);
		if(r-l+1<k){
			if((s[r]-s[l-1]+mod)%mod==0) printf("Yes\n");
			else printf("No\n");
		}
		else{
			w=(r-k+1)%k;
			if(l-1>=(w==0?k:w)) ans=((s[r]-s[l-1]-sk[r-k+1]+sk[l-1-(l-1-w)%k])%mod+mod)%mod;
			else ans=((s[r]-s[l-1]-sk[r-k+1])%mod+mod)%mod;
			if(w!=l%k) ans=(ans+(a[l-1]*val[l%k]%mod)+mod)%mod;
			if(ans==0) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}
```

---

## 作者：Rainsleep (赞：1)

先考虑将原序列差分一下，事实上，我们对于这类每次可以操作一个区间减去固定值的时候，我们一般都需要差分，因为差分后，我们的操作实际上相当于 **在差分序列上修改两个点**，这个时候的问题是好考虑的。

这时候问题转化为，我们每次可以选择两个距离恰好为 $k + 1$ 的点，将 $l$ 加上 $w$，将 $l + k$ 减去 $w$。

这个长度的限制很棘手，但是我们发现，**对 $k \ \bmod $ 同余的点我们都可以相互转移到**，这个是显然的。

那么如果想让最终的差分序列为全 $0$，我们必须让所有下标同余的位置和为 $0$。

细节上，对于 区间 $[l, r]$ 我们其实还有一种操作。对于同余于 $r + 1$ 的点而言，我们可以全部转移到 $r + 1$，并且由于我们要求只需要 $[l, r]$ 区间合法，所以实现上我们不需要考虑与 $r + 1$ 同余的点。

事实上，当原序列真的全变成 $0$ 时，$l$ 处应该为 $0 - w_{l - 1}$，所以对于同余 $l$ 的也需要特殊处理。

时间复杂度 $O(nk + qk)$。

[code](https://atcoder.jp/contests/abc288/submissions/47624981)



---

## 作者：MMXIandCCXXII (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc288_d)
## 1.题目大意
给定一个长为 $n$ 的数组，再给一个常数 $k$，表示每次进行改变的一段数字的长度，然后进行 $m$ 次询问，每次对 $\left[l,r \right]$ 的区间进行操作，求能不能通过若干次把其中 $\left[i,i+k-1\right]$ 的区间减去任意数的操作使 $\left[l,r\right]$ 这个区间的数全部变为 $0$。
## 2.解题思路
用**差分数组**来进行增减操作的时间不能满足这个时间复杂度，所以要用**前缀和**优化，因为每次进行修改都相当于把前面的数放到它后面的第 $k$ 个位置上，而我们想要它们变为 $0$ 只需要统计每组前缀和是不是 $0$ 就行了（最后一组和第一组要特殊判断）。

### code
[link](https://www.luogu.com.cn/record/125748606)

```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[200010], b[200010];
long long s[200010][15];

int main()
{
	int n, k;
	scanf ("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
	    scanf ("%lld", a + i);
	    b[i] = a[i] - a[i-1];
	    for (int j = 0; j < k; j++)
	    {
	        s[i][j] = s[i-1][j];
	    }
	    s[i][i%k] += b[i];
	}
	int m;
	cin >> m;
    for (int i = 1; i <= m; i++)
    {
        bool flag = true;
        int l, r;
        scanf ("%d %d", &l, &r);
        for (int j = 0; j < k; j++)
        {
            long long v = s[r][j] - s[l-1][j];
            if(j == l % k) v += a[l-1];
			if (j == (r - k + 1) % k) continue;
            if (v != 0)
            {
                flag = false;
                break;
            }
        }
        if (flag) puts ("Yes");
        else puts ("No");
    }
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc288_d)

# 1.题目大意
给你 $ N $ 个数，有 $ M $ 次询问，问你第 $ j $ 次操作是否满足 在 $ [l,r] $ 这个区间内选定两个整数 $ c $ 和 $ i $ 使得区间 $ [i,i+k-1] $ 内的所有元素减去 $ c $ 后使该序列的所有元素均变为零。

# 2.解题思路
这道题是在学校听学长讲的，因为我们要在这个序列中选取一些区间进行模拟操作，所以需要另外一个数组 $ b $ 和 $ dev $ 数组来存储数将输入的区间进行范围缩小查找，用 $ dev $ 存储区间分段后 good 序列的区间数据，最后遍历进行判断。

# 3.代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5+10;
int n,k,q;
ll a[N],b[N],dev[N];//dev数组作为最终数据，b数组作为模拟数据
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=a[i];//存储数据
		if(i>=k)
			b[i]+=b[i-k];//区间分段
	}
	scanf("%d",&q);
	for(int p=0;p<q;p++){
		int l,r;
		scanf("%d%d",&l,&r);
		for(int i=0;i<k;i++){
			int x=l,y=r;
			while(x%k != i) x++;//区间内进行good序列查找，左端点
			while(y%k != i) y--;//区间内进行good序列查找，右端点
			dev[i] = b[y];//数据储存
			if(x >= k)
				dev[i]-=b[x-k];//如果左端点大于区间分段，则dev的数据要变化
		}
		bool op=true;
		for(int i=0;i<k;i++)
			op&=(dev[i]==dev[0]);//是否为good序列
		if(op)
			printf("Yes\n");//是
		else
			printf("No\n");//否
	}
	return 0;//完结撒花
}
```


---

## 作者：ZBH_123 (赞：1)

### 1.简化题意
给定长为 $N$ 的序列和操作的区间长度 $k$，再给定 $M$ 次询问，每次询问给定一个区间 $[l,r]$，判断该区间能否通过若干次修改操作使区间所有元素变为 $0$，每次操作指定一个 $i$（$l \le i \le r-k+1$）和一个常数 $c$，将区间 $[i,i+k-1]$ 的所有元素加上 $c$。
### 2.大体思路
既然要区间修改，那我们就考虑使用差分。差分是什么呢？它是基于原数组计算的另一个数组。我们设差分数组为 $B$，原数组为 $A$，那么对于差分数组的所有位置 $B_i$，都有：
$$B_i = \begin{cases}A_1 & i=1\\A_i-A_{i-1} & i>1\end{cases}$$
那么，对区间 $[l,r]$ 的修改操作就变成了给 $B_l$ 减去 $c$，给 $B_{r+1}$ 加上 $c$，也就相当于把 $B_l$ 移除 $c$，转移到 $B_{r+1}$ 当中。在本题中，good 序列的定义是能通过给定的修改操作将 $A$ 的子序列 $[l,r]$ 变成 $0$。在 $A$ 的 $[l,r]$ 变成 $0$ 后，$B_l$ 就会变成 $-A_{l-1}$，$B_{l+1} \sim B_{r}$ 就会变成 $0$，而 $B_{r+1}$ 不管变成什么数都行。在本题中，我们可以考虑把区间 $[l,r]$ 按照模 $k$ 的余数分成 $k$ 类，每次转移都是在同一类中转移。那么，要将 $B_l$ 变成 $-A_{l-1}$，就需要让差分数组区间 $[l,r]$ 中和 $l$ 同类的数加起来等于 $-A_{l-1}$，如果想要让 $B_{l+1} \sim B_r$ 变成 $0$，就需要让差分数组区间 $[l,r]$ 中和它们同类的元素加起来等于 $0$。而至于和 $r+1$ 同类的元素，就不用管了。而这个求出区间和的操作很明显可以使用前缀和来维护。

综上所述，这道题就被我们做出来了。

**并不完全正确的 code:**
```cpp
#include<iostream>
using namespace std;
int n,k,q,l,r,a[200001],b[200001],sum[11][200001];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<k;j++){
			sum[j][i]=sum[j][i-1];
		}
		b[i]=a[i]-a[i-1];
		sum[i%k][i]=sum[i%k][i-1]+b[i];
	}
	cin>>q;
	while(q--){
		cin>>l>>r;
		bool flag=true;
		int tmp=l%k,temp=(r+1)%k;
		for(int i=0;i<k;i++){
			if(i!=temp){
				if(i!=tmp&&sum[i][r]-sum[i][l-1]!=0){
					flag=false;
					break;
				}
				else if(sum[i][r]-sum[i][l-1]!=-a[l-1]){
					flag=false;
					break;
				}
			}
		}
		if(!flag){
			cout<<"No"<<endl;
		}
		else{
			cout<<"Yes"<<endl;
		}
	}
	return 0;
}
```
不完全正确的地方请读者自行检查。

---

## 作者：Iratis (赞：1)

首先，题目要求区间加法，我们发现这跟差分很有关系，所以自然联想到记录差分数组。

对于每个询问，只要看判断对于每个模 $ k $ 意义下的同余系的答案，但是对于第一项以及最后一项，需要特殊判断。

代码如下：

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define int long long
#define md(a) a=(a%mod+mod)%mod
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
const int N=200005;
int n,Q,ned;
int a[N],d[N],sum[N][11];
signed main()
{
	scanf("%lld%lld",&n,&ned);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),d[i]=a[i]-a[i-1];
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=ned-1;j++)sum[i][j]=sum[i-1][j];
		sum[i][i%ned]+=d[i];
	}
	scanf("%lld",&Q);
	while(Q--)
	{
		int l,r;scanf("%lld%lld",&l,&r);
		bool f=1;
		for(int i=0;i<=ned-1;i++)
		{
			int v=sum[r][i]-sum[l-1][i];
			if(l%ned==i)v+=a[l-1];
			if((r+1)%ned==i)continue;
			if(v!=0)
			{
				f=0;
				break;
			}
		}
		if(f)puts("Yes");else puts("No");
	}
	return 0;
}
```


---

## 作者：FReQuenter (赞：1)

考虑 $A$ 的差分序列 $b_i=A_i-A_{i-1}$。

于是修改操作转化成了 $b_l=b_l+c$，$b_{r+1}=b_{r+1}-c$。

考虑每 $k$ 个位置相隔的所有数为一组。

不难发现，要使 $A'$ 为好序列，必须使得 $A'_{xk+i}(xk+i\leq r-l+1)$ 之和相等。

那么这个玩意用二维前缀和维护下就行了。

复杂度 $O((N+Q)k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,q,sum[10][200005];
signed main(){
  cin>>n>>k;
  for(int i=1;i<=n;i++){
    int x;cin>>x;
    for(int j=0;j<k;j++) sum[j][i]=sum[j][i-1]+(i%k==j?x:0);
  }
  cin>>q;
  while(q--){
    int l,r;cin>>l>>r;
    int v=sum[0][r]-sum[0][l-1],f=1;
    for(int i=1;i<k;i++){
      if(sum[i][r]-sum[i][l-1]!=v){
        f=0;break;
      }
    }
    cout<<(f?"Yes":"No")<<'\n';
  }
}
```

---

## 作者：iamajcer (赞：0)

# 大意

一些数，选一个区间 $A$，并再选一个长度为 $k$ 的区间 $B$，这个区间 $B$ 的每个数加减一个数，最终使得区间 $A$ 全部数为 $0$。

# 思路

可以想到是差分，因为是区间加减数。
最终，$A$ 数组加减一堆数，肯定全为 $0$ 了（输出 `Yes` 的情况），那么 $B$ 数组也会变。具体地，$B_1=-a1$，$B_2=0$，$B_3=0$ $\cdots$ $B_n=0$。

由于我们要选长度为 $k$ 的区间 $B$，考虑加减一个数。所以每个数（$A$ 数组）可以对应一个余数 $k$，来方便我们找规律，如下：

```
A数组 a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12
余数  1  2  3  4   1 2  3  4  1   2  3    4
B数组 b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12
B最终 -a1 0 0  0  0  0  0  0  0   0  0    0
```

这里我们定，$S_{i,j}$ 表示前 $i$ 个数余数为 $j$ 的差分数组的和，会发现有 3 种情况，区间内同余数和一定为 $0$，肯定相同，但是还有左右端点要特判，所以分情况。

情况 1，当 $i=(R+1)%k$，此时 $L+B_{L}=0$，这种情况在区间内，是很自然的。

情况 2，当 $i=L \bmod k$，$S_{R,余}-S_{L-1,余}=-A_{L-1}$，像 $B_{1}$ 最终为 $-A_{1}$ 一样，不过这里的位置不固定，换成 $A_{L-1}$。

情况 3，当下标 $i$ 区间 $L，R$ 内，$S_{R,余}-S_{L-1,余}=0$，在区间外没余数这个值了，具体可以看代码，里面的注释也很详细了。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N=2e5+5, M=11;
int n, k, a[N], b[N], s[N][M], m, L, R;
//s[i][j]:前i个数余数为j的差分数组的和
//b:差分数组
int yu(int x) //求余 例如4%3=1, 4%4=4
{
    return (x-1)%k+1;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        b[i]=a[i]-a[i-1];
    }
    //b最终:  -a1 0 0 0 ... 0
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=k; j++) s[i][j]=s[i-1][j]; //余数相等，必然有 i=i-1
        s[i][yu(i)]+=b[i]; //余数不同，加上此差分数组的数
    }
    scanf("%d", &m);
    while (m--)
    {
        int flag=0;
        scanf("%d%d", &L, &R);
        for (int i=L; i<=L+k-1; i++) //遍历区间，不用全部跑，因为余数最多为L+k-1
        {
            int j=yu(i);
            if (j==yu(R+1)) continue;//情况1不考虑，因为b数组都为0，在区间内无影响
             
            if (j==yu(L)) //情况2
            {
                if (s[R][j]-s[L-1][j]!=-a[L-1])
                {
                    flag=1;
                    break;
                }
            }
            else //情况3
            {
                if (s[R][j]-s[L-1][j]!=0)
                {
                    flag=1;
                    break;
                }
            }
         
         
        }  
        if (flag==1) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}
/*
A数组 a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12
余数  1  2  3  4   1 2  3  4  1   2  3    4
B数组 b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12
B最终 -a1 0 0  0  0  0  0  0  0   0  0    0
区间     2                       10              (选2~10)
         2           2            2             情况2，当下标为i==L mod k    S[R][余]-s[L-1][余]==-a[L-1]
            3          3            3           情况1，当下标为i=(R+1)%k     L+b[L]==0
               4           4              4     情况1，同上
                  1           1                 情况3，当下标i区间L,R内      s[R][余]-s[L-1][余]==0
*/
```

---

## 作者：yqr123YQR (赞：0)

### 题意
给定常数 $k$ 及序列 $\{a_n\}$，支持多次查询给定区间 $[l,r]$ 能否通过以下操作全部归零：
- 选择区间 $[i,i+k-1]$ 且 $[i,i+k-1]\subseteq[l,r]$，整体加上任意常数。

### 思路
套路地，转化为差分。对于区间 $[l,r]$，记差分数组为 $b$，则操作变为：
- 选择一点 $i$，$i+k-1\leqslant r$，$b_i\leftarrow b_i+c,b_{i+k}\leftarrow b_{i+k}-c$。其中 $c$ 为任意常数

此时，我们可以这么想：先选择的点一定满足前面没有可以影响该点的点，则选择的顺序一定是从左至右。

因此，我们只考虑 $[l,r]$ 的末尾 $k-1$ 个数。只需验证经过尽可能地操作后，这 $k-1$ 个数的新值是否均为 $0$。即，$\forall i\in[r-k+2,r],b_i'=\sum_{j\equiv i\pmod k}b_j$，$b_i'$ 是否等于 $0$。这就很简单了。

还有一个需要思考的地方：左端点怎么处理？~~自己去想~~
### 代码
```cpp
#include<stdio.h>
#include<ctype.h>
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 200000;
namespace IO {
	const int bufsize = 230005;
	char gtchar()
	{
		static char buf[bufsize], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin), p1 == p2)? EOF: *p1++;
	}
	ll read()
	{
		ll ret = 0;
		char ch = gtchar();
		bool f = false;
		while(!isdigit(ch)) f = ch == '-', ch = gtchar();
		while(isdigit(ch)) ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
		return f? -ret: ret;
	}
}
using IO::read;
int n, K, m, num[2][maxn + 5];
struct segment_tree {
	struct node {
		ll sum[10];
		void init() {for(int i = 0; i < K; i++) sum[i] = 0;}
		friend node operator + (const node &a, const node &b)
		{
			node ret;
			for(int i = 0; i < K; i++) ret.sum[i] = a.sum[i] + b.sum[i];
			return ret;
		}
	}s[maxn * 4 + 5];
	#define l(k) k << 1
	#define r(k) k << 1 | 1
	void build(int k, int sl, int sr)
	{
		if(sl == sr) return s[k].sum[sl % K] = num[1][sl], void();
		int mid = sl + sr >> 1;
		build(l(k), sl, mid), build(r(k), mid + 1, sr);
		pushup(k);
	}
	void pushup(int k) {s[k] = s[l(k)] + s[r(k)];}
	node query(int k, int sl, int sr, int ql, int qr)
	{
		if(ql <= sl && sr <= qr) return s[k];
		node ret;
		ret.init();
		int mid = sl + sr >> 1;
		if(ql <= mid) ret = query(l(k), sl, mid, ql, qr);
		if(qr > mid) ret = ret + query(r(k), mid + 1, sr, ql, qr);
		return ret;
	}
	#undef l
	#undef r
}tree;
int max(int a, int b) {return a < b? b: a;}
bool check(int l, int r)
{
	segment_tree::node t = tree.query(1, 1, n, l, r);
	t.sum[l % K] += num[0][l - 1];
	for(int i = max(r - K + 2, l); i <= r; i++) if(t.sum[i % K]) return false;
	return true;
}
int main()
{
// 	freopen("good.in", "r", stdin);
// 	freopen("good.out", "w", stdout);
	n = read(), K = read();
	for(int i = 1; i <= n; i++) num[0][i] = read();
	for(int i = 1; i <= n; i++) num[1][i] = num[0][i] - num[0][i - 1];
	tree.build(1, 1, n);
	m = read();
	for(int i = 1, l, r; i <= m; i++)
	{
		l = read(), r = read();
		puts(check(l, r)? "Yes": "No");
	}
	return 0;
}
```
~~或许不用写线段树？~~

---

## 作者：CQ_Bab (赞：0)

# 思路

我们首先思考暴力，我们发现只留下最后的 $k-1$ 个然后看是否都归零了即可，因为我们最后如果留下的个数是小于 $k$ 的且不全为 $0$ 那么一定不可行，因为我们一次变得一定是 $k$ 个数的值而剩下的数不足 $k$ 个。那么我们发现这么做是 $n^2$ 的所以我们果断打表找规律。

```
n=7,k=3
a1,a2,a3,a4,a5,a6
a1-a1,a2-a1,a3-a1,a4,a5,a6
0,a2-a1-a2+a1,a3-a2,a4-a2+a1,a5,a6
0,0,a3-a2-a3+a2,a4-a3+a1,a5-a3+a2,a6
0,0,0,a4-a3+a1-a4+a3-a1,a5+a2-a4-a1,a6
```

那么发现了什么规律，我们发现对于第 $i$ 个数当将 $i-1$ 个数减成 $0$ 之后此数会加上在它前面且模 $k$ 等于 $i\bmod k$ 的会减去前面模 $k$ 等于 $(i-1)\bmod k$ 的，所以就很好写了，只需要将最后的 $k-1$ 个数的只算出来然后判断是否为零即可（可以预处理）。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
int n,k,q;
const int N=2e5+10;
int a[N],b[N],f[N][30];
void solve() {
	in(n),in(k);
	rep(i,1,n) in(a[i]);
	rep(i,1,n) {
		rep(j,0,k-1) {
			if(i%k==j) f[i][j]=f[i-1][j]+a[i];
			else f[i][j]=f[i-1][j];
		}
	}
	in(q);
	while(q--) {
		int l,r;
		in(l),in(r);
		int now=r-k+2,ff=0;
		rep(i,now,r) {
			int x=-f[i-1][(i-1)%k]+f[i][i%k]+f[l-1][(i-1)%k]-f[l-1][i%k];
			if(x!=0) {
				ff=1;
				break;
			}
		}
		if(ff) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]AT_abc288_d%20[ABC288D]%20Range%20Add%20Query)

# 思路

首先你可以发现，如果一个区间 $[l,r]$ 是一个好的序列，那么一定 $i$ 能从 $l$ 开始 一直到 $r - k + 1$，将 $a_{i \sim (i + k - 1)}$ 减掉 $a_i$。

那么，当 $l = 1$ 时，对于每一个 $i$，我们可以 $\Theta(n)$ 算出减到 $a_{i - 1}$ 时，$a_i$ 的值，记作 $c_i$。

例如，样例 1 的 $c$ 数组为：

```
3 -4 2 0 0 0 5
```

在区间 $[l,r]$ 中，$a_{(r - k + 2) \sim r}$ 在减掉 $a_{r - k + 1}$ 之后就不会修改了。那么这个 $c$ 数组的作用就可以体现了，如果 $[l,r]$ 区间是好的序列，当且仅当 $c_{(r - k + 2) \sim r}$ 全都为 $0$，因为满足上述条件意味着无需操作 $a_{(r - k + 2) \sim r}$ 就可以满足题意。

考虑动态维护 $c$ 数组。显然的是 $l = i + 1$ 的 $c$ 数组可以由 $l = i$ 的 $c$ 数组转移。再观察一下，转移的时候，是将 $i \bmod k = t$ 的减去 $\Delta$，$i \bmod k = (t + 1) \bmod k$ 的加上 $\Delta$，其中 $t = i \bmod k$。

那么，你用按照下标模 $k$ 的元素分别用一个树状数组维护其 $c$ 数组的值。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10;
int n,k,q;
int arr[N],c[N];
bool ans[N];

struct Query{
    int r,id;
};
vector<Query> Q[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct BIT{
    #define lowbit(x) (x & -x)

    int tr[N];

    inline void modify(int x,int k){
        for (re int i = x;i <= n;i += lowbit(i)) tr[i] += k;
    }

    inline int query(int x){
        int res = 0;
        for (re int i = x;i;i -= lowbit(i)) res += tr[i];
        return res;
    }

    #undef lowbit
}T[11];

signed main(){
    n = read(),k = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i <= n;i++){
        c[i] = arr[i];
        for (re int j = i;j <= i + k - 1;j++) arr[j] -= c[i];
    }
    for (re int ty = 0;ty < k;ty++){
        int be = ty;
        if (!be) be = k;
        for (re int i = be;i <= n;i += k){
            T[ty].modify(i,c[i]); T[ty].modify(i + 1,-c[i]);
        }
    }
    q = read();
    for (re int i = 1;i <= q;i++){
        int l,r;
        l = read(),r = read(); Q[l].push_back({r,i});
    }
    for (re int i = 1;i <= n;i++){
        int be = i % k;
        for (auto p:Q[i]){
            bool falg = true;
            int x = p.r - k + 2;
            for (re int j = x;j <= p.r;j++){
                int val = T[j % k].query(j);
                if (val){
                    falg = false; break;
                }
            }
            ans[p.id] = falg;
        }
        int del = T[be].query(i);
        T[be].modify(1,-del); T[(be + 1) % k].modify(1,del);
    }
    for (re int i = 1;i <= q;i++){
        if (ans[i]) puts("Yes");
        else puts("No");
    }
    return 0;
}
```

---

