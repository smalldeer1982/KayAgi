# Changing Array

## 题目描述

At a break Vanya came to the class and saw an array of $ n $ $ k $ -bit integers $ a_1, a_2, \ldots, a_n $ on the board. An integer $ x $ is called a $ k $ -bit integer if $ 0 \leq x \leq 2^k - 1 $ .

Of course, Vanya was not able to resist and started changing the numbers written on the board. To ensure that no one will note anything, Vanya allowed himself to make only one type of changes: choose an index of the array $ i $ ( $ 1 \leq i \leq n $ ) and replace the number $ a_i $ with the number $ \overline{a_i} $ . We define $ \overline{x} $ for a $ k $ -bit integer $ x $ as the $ k $ -bit integer such that all its $ k $ bits differ from the corresponding bits of $ x $ .

Vanya does not like the number $ 0 $ . Therefore, he likes such segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ) such that $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Determine the maximum number of segments he likes Vanya can get applying zero or more operations described above.

## 说明/提示

In the first example if Vasya does not perform any operations, he gets an array that has $ 5 $ segments that Vanya likes. If he performs the operation with $ i = 2 $ , he gets an array $ [1, 0, 0] $ , because $ \overline{3} = 0 $ when $ k = 2 $ . This array has $ 3 $ segments that Vanya likes. Also, to get an array with $ 5 $ segments that Vanya likes, he can perform two operations with $ i = 3 $ and with $ i = 2 $ . He then gets an array $ [1, 0, 3] $ . It can be proven that he can't obtain $ 6 $ or more segments that he likes.

In the second example, to get $ 19 $ segments that Vanya likes, he can perform $ 4 $ operations with $ i = 3 $ , $ i = 4 $ , $ i = 5 $ , $ i = 6 $ and get an array $ [1, 4, 3, 0, 4, 3] $ .

## 样例 #1

### 输入

```
3 2
1 3 0
```

### 输出

```
5```

## 样例 #2

### 输入

```
6 3
1 4 4 7 3 4
```

### 输出

```
19```

# 题解

## 作者：灵茶山艾府 (赞：5)

### 提示 1

定义前缀异或和 $s$，其中 $s[0] = 0$，$s[i] = s[i-1] \oplus a[i]$。

子数组的异或和转换成 $s$ 中两个元素的异或值。

我们需要让 $s$ 中的不同数对尽量的多。（不同数对：数对中的两个数字不同）

### 提示 2

正难则反（所有数对个数减去相同数对的个数），让 $s$ 中的相同数对尽量的少。（相同数对：数对中的两个数字相同）

### 提示 3

对于 $a$ 的某个前缀，如果其中的元素修改了偶数次，那么它的前缀和不变；如果修改了奇数次，那么它的前缀和要额外异或 $2^k-1$。

换句话说，题目的操作相当于选择一个 $s[i]$（$i>0$），把它异或上 $2^k-1$。

### 提示 4

修改了一个 $a[i]$，虽然会影响后面的所有 $s[j]$，但 $s[j]$ 可以通过异或 $2^k-1$ 抵消掉修改 $a[i]$ 所产生的影响。

因此，每个 $s[i]$ 是互相独立的。由于求的是不同数对的数量，$s[i]$ 在 $s$ 中的位置是不重要的，我们只需要关心 $s[i]$ 的出现次数。

### 提示 5-1

看上去用一个 `map` 统计 $s[i]$ 的出现次数就行了，但是 $s[i]$ 和 $s[i] \oplus (2^k-1)$ 可以互相转换，如果相同的 $s[i]$ 很多，可以转换一部分为 $s[i] \oplus (2^k-1)$，从而减少相同数对的个数。

### 提示 5-2

为了方便计算，统计 $\min(s[i], s[i]\oplus (2^k-1))$ 的出现次数。

设 $x$ 出现了 $\textit{cnt}[x]$ 次。为了让不同数对尽可能地多，应当把 $\left\lfloor\dfrac{\textit{cnt}[x]}{2}\right\rfloor$ 个 $x$ 异或 $2^k-1$，其余的 $\left\lceil\dfrac{\textit{cnt}[x]}{2}\right\rceil$ 个 $x$ 保持不变。

因此答案为

$$
\binom{n}{2} - \sum_{x}\binom{\lfloor\textit{cnt}[x]/2\rfloor}{2} - \sum_{x}\dbinom{\lceil\textit{cnt}[x]/2\rceil}{2}
$$

代码实现时，可以一边读入数组 $a$，一边计算 $s$（用一个变量）。

### 注

你可能会认为这样算会把 $s[0]$ 改成 $s[0]\oplus (2^k-1)$。这是不会的，因为始终可以让 $s[0]$ 在提示 5-2 的「其余的」当中。

也可以这样理解，由于 $s[0]$ 肯定要和另外一个 $s[i]$ 异或，就算 $s[0]$ 变成了 $s[0]\oplus (2^k-1)$，也可以理解成是在 $s[i]$ 上异或 $2^k-1$。

### AC 代码（Go）

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, k, v, s int
	Fscan(in, &n, &k)
	ans := c2(n + 1)
	m := 1<<k - 1
	cnt := map[int]int{s: 1} // s[0]
	for ; n > 0; n-- {
		Fscan(in, &v)
		s ^= v
		cnt[min(s, s^m)]++
	}
	for _, c := range cnt {
		ans -= c2(c/2) + c2(c-c/2)
	}
	Print(ans)
}

func c2(n int) int64 { return int64(n) * int64(n-1) / 2 }
func min(a, b int) int { if a > b { return b }; return a }
```


---

## 作者：花里心爱 (赞：4)

这是一道~~duliu~~贪心题。

这道题让我们求最多构成的异或和不为0的连续区间数。然而这并不好求……

于是正难则反，我们可以用总的区间数减去异或和为0的区间数。由$n$个数可以取的总的区间数为$\displaystyle \frac{n \times (n+1)}{2}$。

然后我们考虑怎么样才能使异或和为0的区间尽量少。

我们知道区间和可以用一种"前缀和"的形式来实现（也就是$a_l+a_{l+1}+a_{l+2}+...+a_{r} = s_r-s_{l-1}$）。因为加法的"反运算"为减法。

相对应的，异或的"反运算"为异或本身。于是  
$a_l \oplus a_{l+1} \oplus a_{l+2} \oplus...\oplus a_{r} = s_r \oplus s_{l-1}$

所以只有$s_r = s_{l-1}$的时候，区间$[l, r]$的异或和为0。

所以我们可以用`map`来维护前面的数前缀和，记录当前数的前缀和与进行取反操作后的前缀和，每次取最小的已经有的前缀和并记录。

注意到没有数的时候前缀和为0，所以初始化`map[0]=1`。

因为`map`的复杂度是带$log$的，所以总时间复杂度为$O(nlogn)$。

下面是代码 :
```
#include <cstdio>
#include <cctype>
#include <map>
#define ll long long
inline int read() {
    int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
    while(isdigit(ch)){d=d*10+ch-48;ch=getchar();}return d;
}

int n, k, a, mx;
int pre, nowa, nowb;
ll ans;
std::map<int, int> mp;

int main() {
    n = read(), k = read();
    mx = (1<<k)-1; // 为了方便进行取反操作这里记录一下后k为均为1的值
    mp[0] = 1;
    for(int i = 1; i <= n; ++i) {
        a = read();
        nowa = pre^a;
        nowb = nowa^mx;
        if(mp[nowa] < mp[nowb]) {
            ans += (mp[nowa]++); // 取最小的前缀和
            pre = nowa;
        }
        else {
            ans += (mp[nowb]++);
            pre = nowb;
        }
    }
    printf("%lld", ((ll)n*(n+1))/2 - ans); // 用总数减去最小的区间异或和为0的区间数
    return 0;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF1054D)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;题目要求$\ne 0$的区间，这限制太弱了，不好做。如果把条件反过来，$=0$，就会强一些。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以考虑求出最少能有多少个区间的异或为$0$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;得到了区间，我们不难想到使用异或前缀和$s_i=\bigoplus_{j=1}^i a_j$，这样，一个区间$[l,r]$的异或就变成了$s_r\oplus s_{l-1}$。一个区间的异或为$0$就说明$s_r=s_{l-1}$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下面观察操作，$a\oplus (2^k-1)$就相当于翻转$a$的二进制后$k$位，由于$a<2^k$，所以就是它的$k$位二进制码全部翻转。不难发现，对于一个数，这个操作最多只需要进行一次。    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;假设当前我们已经知道了前$i-1$个位置的最优前缀$s_1,s_2,...,s_{i-1}$，并且还有一个桶$b$，$b_i$记录有多少个前缀为$i$。考虑当前应该操作还是不操作。设不操作得到了$s_i'$，操作得到了$s_i''$。考虑最终答案中，$s_i'$这种前缀的贡献就是$C_{b_{s_i'}}^2$，$s_i''$这种前缀的贡献就是$C_{b_{s_i''}}^2$。我们现在就是要最小化：  
$$C_{b_{s_i'}}^2+C_{b_{s_i''}}^2$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;令$p=b_{s_i'},q=b_{s_i''}$。  
$$=\frac{p(p-1)}2+\frac{q(q-1)}2$$  
$$=\frac12(p^2+q^2-p-q)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;根据均值不等式我们可以知道，$p,q$越接近，这个值越小。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以我们应该选择$b_{s_i'}$和$b_{s_i''}$中较小的一个，作为$s_i$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于$map$有一个$\log$，所以总时间是$O(n\log_2n)$  
# 代码
```cpp
#include <map>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAXN = 2e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

map<int, int> mp;

int N, K;

int main()
{
	mp[0] = 1;
	read( N ), read( K );
	LL res = 0;
	int upper = ( 1 << K ) - 1, pXor = 0, fir, sec; 
	for( int i = 1, a ; i <= N ; i ++ )
	{
		read( a );
		fir = pXor ^ a, sec = pXor ^ a ^ upper;
		if( mp[fir] < mp[sec] ) res += mp[pXor = fir] ++;
		else res += mp[pXor = sec] ++;
	}
	write( 1ll * N * ( N + 1 ) / 2 - res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：小周猪猪 (赞：1)



## 题解
一道看了题解很好懂~~但是自己死都想不出来的题~~ 。

在这里，对于某一个数字取反相当于这个数$⊕2^k-1$。

我们知道，一道题目可以转化为有多少个前缀和的$l$和$r$满足$sum_r⊕sum_{l-1}=0$.

我们可以一次枚举每一个$r$，如果$sum_{i-1}⊕a_i$的个数比较小，则$sum_i=sum_{i-1}⊕a_i$,并统计这样的数字有多少个，并累加答案。否则累加$sum_{i-1}⊕a_i⊕(2^k-1).$

我们考虑一下，对于相同的$sum_i$有$cnt1$个，$sum_i⊕(2^k-1)$有$cnt_2$个，显然答案是：$$C_{cnt1}^{2}+C_{cnt2}^{2}$$
所以$cnt1$和$cnt2$尽可能接近就可以让答案尽可能小。因此我们的每一步都要选较小的。

我们思考这样的每一步能优就优的贪心策略为什么不会对后面的决策产生影响的，思考一下，每一步对异或数组异或了一个$(2^k-1)$,对于每一个$sum_i$只有前i个数字异或起来和异或了一个$(2^k-1)$,因为同一个数字异或两遍相当于没有异或。因此当前做了那种决策，对于下一步都是不受影响的。

最后我们用总个数 $\frac{n\times (n+1)}{2}-异或和为0的方案数$ 即可。

小坑点：$cnt_0=1$,一开始异或和为$0$.(卡了我好久)

代码如下：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;
const int N = 300000;

int n, k;
int a[N], sum[N];
long long ans = 0;

map <int,int> cnt;

signed main(void)
{
	cin>>n>>k;
	for (int i=1;i<=n;++i)
		scanf("%lld", a+i);
	cnt[0] = 1;
	for (int i=1;i<=n;++i)
	{
		sum[i] = sum[i-1] ^ a[i];
		int num1 = sum[i], num2 = sum[i] ^ ((1<<k)-1);
		if (cnt[num1] >= cnt[num2]) {
			ans += cnt[num2] ++;
			sum[i] = num2;
		}
		else ans += cnt[num1] ++;
	}
	cout<<1LL * n * (n+1) / 2 - ans<<endl;
	return 0;
}
```



---

## 作者：f_x_f (赞：0)

[洛谷题面](https://www.luogu.com.cn/problem/CF1054D)
[ CF 题面](https://www.luogu.com.cn/problem/CF1054D)

这道题是一道不错的贪心题目。

题目大意：首先给你一个长度为 $n$ 的序列 $a$ ，可以对于任意一个 $a_i$ 进行操作，将 $a_i$ 变成 $ a_i \oplus 2^k-1 $ ，请问最多能够有多少个连续子段 $[l,r]$ ，使得 $a_{l} \oplus a_{i+1} \dots \oplus a_{r} \not = 0$ 。

思路：
1. 我们要求的是连续子串异或和，所以先处理出这个序列的前缀和，用变量 $pre$ 表示前缀和。
1. 如果按照题意单单的从正面考虑，看样子十分的困难，所以我们考虑先从反面进行考虑。
1. 对于第 $i$ 位，对应的 $pre$ 的值为 $pre \oplus a_i$ ，我们可以考虑是否对其进行操作。如果进行操作，那么 $pre$ 的值将会变为 $pre \oplus 2^{k}-1$ ，对于每一个值，所减少的个数为两数中在该位置前面所处理过的值的个数，比较大小，根据贪心可知，选取的是两个大小中最小的那一个，并将 $pre$ 的值进行更改。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a,w,mx,pre,nowa,nowb,ans;
map<int,int>mp;
signed main(){
	cin>>n>>k,mx=(1<<k)-1,mp[0]=1;
	for(int i=1;i<=n;i++){
		cin>>a;
		nowa=pre^a;
		nowb=nowa^mx;
		if(mp[nowa]<mp[nowb]){
			ans+=mp[nowa]++;
			pre=nowa;
		}
		else{
			ans+=mp[nowb]++;
			pre=nowb;
		}
	}
	cout<<n*(n+1)/2-ans<<endl;
}
```

---

## 作者：滑蒻稽 (赞：0)

## Des

给你一个序列 $a$, $0 \le a_{i}\le2^{k}-1$,你可以修改里面的任意元素任意次,修改方法为把序列里的一个数$ai⊕$ $2^{k}-1$ 其中$⊕$为异或运算,求最多可以构成多少个连续区间$[l,r]$使得$a_{l}⊕a_{l+1}⊕\dots\oplus a_{r-1} ⊕ a_r≠0$

$\texttt{Data Range:}$

$n\le 2\times 10^5,k\le 30$.

## Sol

最大化异或和不等于 0 这个限制太弱，转成最小化等于 0 的个数就会好做一些。

在每一个位置都可以选择异或上 $2^k-1$，那么对于位置 $i$，$a_1$ 到 $a_i$ 的不同异或和的数量是 $2^i$ 量级的吗？并不是。由于异或的自反性 $a\oplus a=0$，所以 $a_1$ 到 $a_i$ 的异或和只可能有两种不同的值。

令异或前缀和为 $s_i$，对于一个右端点 $r$，会与前面的 $l$ 组成一个异或和为 0 的区间当且仅当 $s_{l-1}\oplus s_r=0$。那么如果在最终的答案中某一种相同的前缀和有 $m_i$ 种，那么产生的异或和为 0 的区间数量就是 $\binom{m_i}2$。

我们需要最小化 $\sum_{i=1}^p\binom{m_i}2$，其中 $p$ 为不同的前缀和的数量。

要最小化的是 $\sum_{i=1}^p\frac{m_i^2-m_i}2$，而 $\sum_{i=1}^pm_i=n$，是一个定值。根据均值不等式，$m_i$ 应当尽量平均，才能使 $\sum_{i=1}^p\frac{m_i^2-m_i}2$ 尽量小。

那么对于一个位置 $i$，设两种前缀和为 $s_{i,1}$ 和 $s_{i,2}$. 如果 $i$ 前面已经有的等于 $s_{i,1}$ 的前缀和数量比等于 $s_{i,2}$ 的多，就选择 $s_{i,1}$ 作为前缀和。反之，选择 $s_{i,2}$。这样便能使得 $m_i$ 尽量平均。

使用 `std::map` 即可记录某种前缀和的出现次数。

## My code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, add, k, S, a[N];
ll cnt;
map<int, int> m;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> k;
	S = (1 << k);
	for(int i = 1; i <= n; i++) cin >> a[i];
	m[0] = 1;
	for(int i = 1; i <= n; i++) {
		int x = add ^ a[i], y = x ^ (S - 1);
		if(m[x] > m[y]) swap(x, y);
		cnt += m[x]++;
		add ^= a[i];
	}
	cout << 1ll * n * (n + 1) / 2 - cnt << '\n';
	
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

[原CSDN博客地址](https://blog.csdn.net/qq_42101694/article/details/104139952)

# 题目
[传送门 to luogu](https://www.luogu.com.cn/problem/CF1054D)

[传送门 to CF](http://codeforces.com/problemset/problem/1054/D)

[传送门 to VJ](https://vjudge.net/contest/354554#problem/A)

# 思路
虽然题解都喊着“正难则反”，但是，你知道的，我是一个硬汉。

假设我们有异或前缀和 $s_0,s_1,s_2,\dots,s_n(s_0=0,s_x=s_{x-1}\oplus a_i)$，我们的答案就是，求 $s_x\ne s_y$ 的数量。可以认为 $x,y$ 无序；输出答案时除以二即可。

考虑翻转操作带来的影响。不妨这样：将 $a_x$ 翻转后，立刻将 $a_{x+1}$ 也翻转（除非 $x=n$）。不难发现，这样一来，异或前缀和的影响，恰好是 $s_x$ 翻转了一次。

由于翻转两次，便可回到原样，所以，如果 $s_i\oplus s_j\ne 0,s_i\oplus s_j\ne 2^k-1$，无论怎样翻转，二者都不可能相同。那么我就可以直接统计答案，而无需考虑翻转带来的影响。

所以我们要解决的，只是“翻转后可以相同”的值。反正可以复原，不妨直接将其翻转成相同的吧！

假设有 $m$ 个相同的值。如果其中有 $x$ 个被翻转，则贡献为 $2x(m-x)$（$2$源于其无序性）。将其最大化。

显然 $x=\lfloor\frac{m}{2}\rfloor$ 即可。为了方便查找数量，将数组排序，时间复杂度 $\mathcal O(n\log n)$。

另：不用担心 $s_0$ 的问题。没人想让它发生变化。

附注：如果使用基数排序，可以将复杂度降至$\mathcal O(n)$。但是，在实际运行中，二者跑出了一样的速度。（图：上为基数排序版本，下为快排版本）

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200202001733909.png)

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0' or c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c and c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
# define MuBan template < class T >
MuBan void getMin(T &a,const T &b){ if(b < a) a = b; }
MuBan void getMax(T &a,const T &b){ if(a < b) a = b; }

const int MaxN = 200005;
int a[MaxN], n, k;

int bucket[10][MaxN], p[10];
void sort(){
	for(int base=1; base<=k; base*=10){
		for(int i=0; i<=n; ++i){
			int x = (a[i]/base)%10;
			bucket[x][++p[x]] = a[i];
		}
		for(int i=0,cnt=0; i<10; p[i++]=0)
			for(int j=1; j<=p[i]; ++j)
				a[cnt++] = bucket[i][j];
	}
}

int main(){
	n = readint(), k = (1<<readint())-1;
	for(int i=1; i<=n; ++i){
		a[i] = a[i-1]^readint();
		getMin(a[i],a[i]^k); // 直接翻转为相同的
	}
	sort(); long long ans = 0;
	for(int i=0; i<=n; ++i){
		long long cnt = 1;
		while(i+1 <= n and a[i+1] == a[i])
			++ i, ++ cnt;
		ans += 2*(cnt>>1)*(cnt-(cnt>>1)); // 内部贡献
		ans += cnt*(n+1-cnt); // 外部贡献
	}
	printf("%lld\n",ans>>1);
	return 0;
}
```

---

## 作者：PPL_ (赞：0)

# 前言

来自教练的**寒假康复训练day1**

# 题目

[洛谷](https://www.luogu.com.cn/problem/CF1054D)

[CF](http://codeforces.com/problemset/problem/1054/D)

# 正题

这题最大的障碍其实是题面为英文，但是谷谷很贴心地解决了这个问题

## 思路

题目说要使得有最多的子区间异或和不为$0$

$\text{emmmmm....}$

正难则反

于是我们考虑：

**总的子区间个数** - **最少的异或和为0的子区间的个数**

= 答案

## 1.总的子区间个数

很明显是$(n+1)*n/2$

为什么？

我们考虑长度为$1$的子区间有$n$个，长度为$2$的子区间有$n-1$个...长度为$n$的子区间有$1$个

总的子区间个数为：$1+2+...+n=(n+1)*n/2$(别告诉我你不会等差数列求和公式)

## 2.最少的异或和为0的子区间的个数

这咋搞？

我们可以很快想到关于异或的题的常见套路：异或前缀和

如果异或前缀和$s[i]\oplus s[j-1]=0(j-1 <= i)$

那么元素$a[j]\oplus a[j+1]\oplus ... \oplus a[i]=0$

那么$s[i]=s[j-1]$

我们要做的就是使相同的异或前缀和最少

这个地方**贪心**就好了

我们记如果使用原始元素$a[i]$的异或前缀和为$s_1$

之前出现过的异或前缀和为$s_1$的个数记为$c_1$

记使用$a[i]\oplus 2^k-1$的异或前缀和为$s_2$

之前出现过的异或前缀和为$s_2$的个数记为$c_2$

如果我们选择$s1,ans-=c1,c1++$

如果我们选择$s2,ans-=c2,c2++$

由此看来，选$c$小的那个就可以使得答案最大

当然$ans$的初始值为$(n+1)*n/2$

# 代码
```cpp
//12252024832524
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std; 

typedef long long LL;
const int MAXN = 200005;
int n,k,now;
int a[MAXN];
map<int,int> m;

int Read()
{
	int x = 0,f = 1;char c = getchar();
	while(c > '9' || c < '0'){if(c == '-')f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
void Put1(LL x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
void Put(LL x,char c = -1)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x);
	if(c >= 0) putchar(c);
}
template <typename T>T Max(T x,T y){return x > y ? x : y;}
template <typename T>T Min(T x,T y){return x < y ? x : y;}
template <typename T>T Abs(T x){return x < 0 ? -x : x;}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = Read();
	k = Read();
	for(int i = 1;i <= n;++ i)
		a[i] = Read();
	k = (1 << k) - 1;
	LL ans = 1ll * (n+1) * n / 2;
	m[0] = 1;//注意事项！！！
	for(int i = 1;i <= n;++ i)
	{
		int dz = a[i] ^ now;
		int fan = dz ^ k;
		if(m[fan] > m[dz])
		{
			ans -= m[dz];
			m[dz]++;
			now = dz;
		}
		else
		{
			ans -= m[fan];
			m[fan]++;
			now = fan;
		}
	}
	Put(ans);
	return 0;
}
```

---

