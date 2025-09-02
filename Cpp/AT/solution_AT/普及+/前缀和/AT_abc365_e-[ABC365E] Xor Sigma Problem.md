# [ABC365E] Xor Sigma Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc365/tasks/abc365_e

長さ $ N $ の整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。次の式の値を求めてください。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ (A_i\ \oplus\ A_{i+1}\oplus\ \ldots\ \oplus\ A_j) $

 ビット単位 xor とは 非負整数 $ A,\ B $ のビット単位 xor 、$ A\ \oplus\ B $ は、以下のように定義されます。 - $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。

 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の整数 $ p_1,\ \dots,\ p_k $ の排他的論理和は $ (\cdots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \cdots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^8 $
- 入力される数値は全て整数
 
### Sample Explanation 1

$ A_1\oplus\ A_2\ =\ 2,\ A_1\ \oplus\ A_2\oplus\ A_3\ =\ 0,\ A_2\oplus\ A_3\ =\ 1 $ なので答えは $ 2+0+1=3 $ です。

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
3```

## 样例 #2

### 输入

```
7
2 5 6 5 2 1 7```

### 输出

```
83```

# 题解

## 作者：xwh_hh (赞：6)

奇迹般地独立过了 E 题，发篇题解纪念一下。  
注：本文中均使用小写字母作变量名，请注意与题目的微小区别。  
不难想到维护前缀异或和（此处记 $b_i=a_1\oplus a_2\oplus\cdots\oplus a_i$，特殊的，$b_0=0$），则所求的式子即为 $\sum_{i=0}^{n-2} \sum_{j=i+2}^nb_i\oplus b_j=(\sum_{i=0}^{n-1} \sum_{j=i+1}^nb_i\oplus b_j)-(\sum_{i=1}^na_i)$，后面一部分明显可以 $O(n)$ 求出，问题转化为求 $\sum_{i=0}^{n-1} \sum_{j=i+1}^nb_i\oplus b_j$ 的值。

直接暴力求解是 $O(n^2)$ 的，无法通过，我们考虑快速求出 $\sum_{i=0}^{x-1}b_i\oplus b_x$。

因为这是位运算，不难想到按位考虑。记 $g_{i,j}$ 表示当前考虑范围内的数中满足二进制表示中第 $i$ 位为 $j$ 的数的个数（记最低位为第 $0$ 位），每次更新 $g$ 数组时只需 $O(\log a_{\max})$ 的复杂度，统计答案单次也是 $O(\log a_{\max})$，总时间复杂度 $O(n\log a_{\max})$，可以通过本题。  
代码如下（比较通俗易懂）：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-f;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ans=(ans<<3)+(ans<<1)+c-48;
		c=getchar();
	}
	return ans*f;
} 
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x<10) putchar(x+48);
	else{
		write(x/10);
		putchar(x%10+48);
	}
}
long long n;
long long a[200005],b[200005];
long long g[35][2];
long long ans;
signed main(){
	n=read();
	for(long long i=1;i<=n;i++){
		a[i]=read();
		b[i]=a[i]^b[i-1];
	}
	for(long long i=0;i<=28;i++) g[i][0]++;//将b[0]加进去 
	for(long long i=1;i<=n;i++){
		for(long long j=0;j<=28;j++){
			ans+=g[j][bool((b[i])&(1<<j))^1]*(1<<j);//按位统计答案 
		}
		for(long long j=0;j<=28;j++){
			g[j][bool((b[i])&(1<<j))]++;//按位更新g数组 
		}
	}
	for(long long i=1;i<=n;i++) ans-=a[i];//除去长度为1的区间 
	write(ans);
	return 0;
}
```
小插曲：赛时我把 $a_i$ 的上限看成了 $10^{18}$，害得我开了 `__int128`，赛后才发现 `long long` 就够了。

---

## 作者：Sorato_ (赞：4)

# ABC365E Xor Sigma Problem 题解

## 题目大意

给定长度为 $n$ 的序列 $A$，求 $\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N (A_i \oplus A_{i+1}\oplus \ldots \oplus A_j)$。

## Solve

看到异或不难想到按位枚举，按位枚举时维护什么信息呢？

考虑对于序列 $A$，我们倒序枚举，那么在加入 $A_i$ 之前得到的区间异或和之和形如：
$$
(A_{i+1}\oplus A_{i+2}\oplus \dots\oplus A_n)+(A_{i+1}\oplus A_{i+2}\oplus \dots\oplus A_{n-1})+\dots+(A_{i+1}\oplus A_{i+2})
$$
加入 $A_i$ 后，这个表达式的每个括号里都要异或上 $A_i$。那么从结果上看，若 $A_i$ 的第 $j$ 位是 $1$，则异或和的第 $j$ 位就要反转。

故我们考虑维护如下信息：对于第 $i$ 位，$cnt_{i,1}$ 表示有多少段异或和（上式中每一个括号内的值）这一位是 $1$，$cnt_{i,0}$ 表示有多少段异或和这一位是 $0$。统计答案时直接加上 $2^i\times cnt_{i,1}$ 即可。

加入 $A_i$ 后，按位扫一遍，如果 $A_i$ 第 $j$ 位是 $1$，就交换 $cnt_{j,0}$ 和 $cnt_{j,1}$。同时别忘了，加入 $A_{i-1}$ 时多了一段 $A_{i-1}\oplus A_i$，故我们还要让 $cnt_{j,A_{i,j}}$ 加上 $1$ 方便后面统计答案。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=2e5+10;
int n,a[N],ans,cnt[35][2];
signed main()
{
	n=read();
	for(int i=1;i<=n;i=-~i)	a[i]=read();
	for(int i=n;i;i--)
	{
		for(int j=30;j>=0;j--)
			ans+=cnt[j][(a[i]>>j&1)^1]*(1<<j);
		for(int j=30;j>=0;j--)
		{
			if(a[i]>>j&1)	swap(cnt[j][1],cnt[j][0]);
			cnt[j][a[i]>>j&1]++;
		}
	}
	return printf("%lld",ans),0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：4)

这题应该有更简便的解法，但还是发一下赛时想到但在实现细节上差一口气的思路来纪念……

把二进制的每一位拆开计算，使问题变为在一个 $01$ 串上的简单版。

（可以借鉴的地方到此为止，下面的思路有些清奇，建议学习正常的思路之后再来观看）。

![](https://cdn.luogu.com.cn/upload/image_hosting/a0ga7bng.png)

当我们要求箭头位置的 $1$ 的贡献时，显然其在异或过程中为 $1$（可以统计进答案）的数量为紫色划线部分的长度（即 $4$）。

稍微观察并思考即可得出一个显然的结论：对于每一个为 $1$ 的位置，其所能在异或过程中为 $1$ 的数量，与这个数是从前往后数的第奇数个还是第偶数个 $1$ 有关。

语言不是很好解释，看图吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/enrl97y7.png)

那么对于 $0$ 咋办？

赛时脑子抽了直接和 $1$ 一样，第二个样例都过不去……

还是看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/j2e1rr13.png)

最终将统计的结果乘以该二进制位的权值，将所有得到的值相加即可。

上面的做法会给每一个 $A_i$ 多统计一次，最终全部去掉即可。

至于怎么求后面几个 $1$ 几个 $0$，可以用后缀和解决。

小插曲：交的时候没开 `long long`，然后错了一大堆，看提交记录所有用时少的都过了，盲猜是数据大了，检查一下 `long long`，还真没开……

代码过于答辩，不建议学习，放一下：


```
#include<bits/stdc++.h>
//#define int long long
using namespace std;
int a[200005];
int f[200005][30];
int val[200005][2][2];
signed main(){
	int n;
	cin>>n;
//	long long ans=0;
	long long sum=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		sum+=x;
		for(int j=29;j>=0;j--){
			if(x>=(1ll<<j)){
				x-=(1ll<<j);
				f[i][j]++;
			}
		}
	}
	unsigned long long ans=0;
	for(int j=0;j<=29;j++){
		memset(val,0,sizeof(val));
		int cnt=0;
		for(int i=1;i<=n;i++){
			cnt+=f[i][j];
		}
		if(cnt==0)continue;
		int ccnt=cnt;
		for(int i=n;i>=1;i--){
			val[i][cnt%2][1]++;
			cnt-=f[i][j];
		}
		for(int i=n;i>=1;i--){
			val[i][0][1]+=val[i+1][0][1];
			val[i][1][1]+=val[i+1][1][1];
			val[i][0][0]+=val[i+1][0][0];
			val[i][1][0]+=val[i+1][1][0];
			if(f[i][j]==1){
				val[i][0][0]=val[i][0][1];
				val[i][1][0]=val[i][1][1];
			}
			ans+=val[i][(ccnt+f[i][j]+1)%2][f[i][j]]*1ll*(1<<j);
			ccnt-=f[i][j];
		}
	}
	cout<<ans-sum;
	return 0;
}

```

---

## 作者：Special_Tony (赞：4)

# 思路
按位拆解求答案。若 $r$ 二进制第 $j$ 位为 $1$，则 $r$ 之前的第 $j$ 位全部反转，即变为 $r-s_j\to s_j$ 有贡献了。最后注意把答案减去 $\sum a_i$，因为要求 $l<r$。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, x, s[35];
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> x, sum -= x;
		for (int j = 0; j < 30; ++ j) {
			if (x >> j & 1)
				s[j] = i - s[j];
			sum += ((ll) s[j]) << j;
		}
	}
	cout << sum;
	I AK IOI
}
```

---

## 作者：Lele_Programmer (赞：2)

# AT_abc365_e 题解

## 思路

求 $\sum\limits_{i=1}^{N-1} \sum\limits_{j=i+1}^N (A_i \oplus A_{i+1} \oplus \ldots \oplus A_j)$ 的值。

发现又有异或又有求和，式子不大好拆开，看看能不能统计每一个值对答案做出的贡献。

首先，异或操作不同位之间不会产生影响，所以不妨将输入的每个数按二进制位拆出来，假设第 $i$ 个数的二进制个位记为 $B_{1,i}$，那就转化成了求 $\sum\limits_{k=1}^{31} ( \sum\limits_{i=1}^{N-1} \sum\limits_{j=i+1}^N (B_{k,i} \oplus B_{k,i+1} \oplus \ldots \oplus B_{k,j})\times 2^{k-1} )$ 的值。

那一个位怎样才会产生贡献呢？

首先，我们知道 $1 \oplus 1 = 0, 0 \oplus 0 = 0, 0 \oplus 1 = 1, 1 \oplus 0 = 1$，所以如果当前位是 $1$，则添加到前面值为 $0$ 的区间，如果是 $0$，则添加到前面一个值为 $1$ 的区间，当然，当前不产生贡献的情况也要记录，因为它在后面的枚举中可能产生贡献，记 $zero_{i,j}$ 为第 $i$ 位的 $\text{01}$ 序列中，以第 $j$ 个数为结尾，异或值为 $0$ 的情况数量，$one_{i,j}$ 同理，所以这样将该过程转化成了类似 DP 的转移。

如果这一位是 $1$，则 $zero_{i,j}=one_{i,j-1}, one_{i,j}=zero_{i,j-1}+1$，如果这一位是 $0$，则 $zero_{i,j}=zero_{i,j-1}+1, one_{i,j}=one_{i,j-1}$。

接下来考虑答案统计，我们要记录产生贡献的部分，所以只与 $one$ 数组有关，枚举相加即可，这里要注意的是，我们刚才所说的“区间”包含长度为 $1$ 的情况，但这是不合法的，我们需要将它减去。

时间复杂度：$O(NM)$，这里 $M$ 指的是二进制的位数。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N=200005;
const int M=35;

int n;
int arr[N];
int num[M][N];
int one[M][N],zero[M][N];
int ans;

signed main() {
    scanf("%lld",&n);
    for (int i=1;i<=n;++i) {
        scanf("%lld",&arr[i]);
    }
    for (int i=1;i<=n;++i) {
        int k=arr[i];
        int idx=0;
        while (k) {
            num[++idx][i]=k&1;
            k>>=1;
        }
    }
    for (int i=1;i<=31;++i) {
        for (int j=1;j<=n;++j) {
            if (num[i][j]) {
                zero[i][j]=one[i][j-1];
                one[i][j]=zero[i][j-1]+1;
            } else {
                zero[i][j]=zero[i][j-1]+1;
                one[i][j]=one[i][j-1];
            }
        }
        int sum=0;
        for (int j=1;j<=n;++j) {
            if (num[i][j]==1) one[i][j]--;
            else zero[i][j]--;
            sum+=one[i][j];
            // cout<<zero[i][j]<<" "<<one[i][j]<<" "<<num[i][j]<<endl;
        }
        ans+=(1<<(i-1))*sum;
        // cout<<sum<<endl;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：2)

### 题意
给一个长度为 $N$ 的序列 $A$，求 $ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ (A_i\ \oplus\ A_{i+1}\oplus\ \ldots\ \oplus\ A_j) $。     
数据范围：$2 \le N \le 2 \times 10^5,A_i \le 10^8$。  
### 分析
笑点解析：如果你做过[P3917 异或序列](https://www.luogu.com.cn/problem/P3917)这道题，那么你可以把你的代码复制一下，再把这份代码求出的答案减去 $\displaystyle \sum_{i=1}^{N}A_i$，就可以获得 $100$ pts 的好成绩。    
众所周知，对于异或和的计算，我们可以把二进制位一个个拆开来进行计算。      
对于每一位，我们维护一个前缀异或和，统计里面 $1$ 的个数和 $0$ 的个数。由于 $1$ 和 $0$ 两两配对才能产生贡献，我们两两相乘再乘上这一位对应的数值即可。   
这样干巴巴讲起来有点奇怪，看代码理解一下吧。
### 代码
```cpp
#include<stdio.h>
long long n,s[200005],sum1[200005],sum2[200005],ans,ls;
int main()
{
    scanf("%lld",&n);
    for(int i=0;i<=30;i++) sum2[i]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&s[i]),ls+=s[i],s[i]^=s[i-1];
        for(int j=30;j>=0;j--)
        {
            if((1<<j)&s[i]) ans+=(1<<j)*sum2[j],sum1[j]++;
            else ans+=(1<<j)*sum1[j],sum2[j]++;
        }
    }
    printf("%lld",ans-ls);
}
```

---

## 作者：GoldSpade (赞：1)

### 大致题意

给一个长为 $N$ 的序列 $A$，让你求所有长度 $\ge2$ 的区间异或和的和。

### solution

~~至少看到西格玛必须瞟一瞟可不可做。~~

首先想到了前缀和，发现异或也有前缀和，那么我们直接给整个序列做一次前缀异或和操作，此时得到的序列记为 $B$，有 $B_i=\bigoplus \limits _{j=1}^{i}A_j$，那么原序列 $A$ 中区间 $[l,r]$ 的异或和即为 $B_{l-1} \oplus B_r$ 的值。

那么序列 $B$ 是一个长为 $n+1$、下标从 $0$ 开始的序列，问题转化成求：

$$
\sum _{i=0}^{n-2} \sum _{j=i+2}^{n} B_{i} \oplus B_j
$$

这是一个天真的做法。如何优化它？考虑一下位运算的性质：每一位的运算**不会**影响其他位。

因此考虑对每一位分别计算。异或运算的规则告诉我们，相同为 $0$，不同为 $1$，那只有**对应数位不同**的才能带来贡献。

那就定义 $c_{i,j}$ 表示 $B_1,B_2,\dots,B_i$ 在数位 $j$ 上出现了多少次 $1$。令 $V=\max\{B_i\}$，那么这个可以 $O(n \lceil\log_2 V\rceil)$ 预处理。

接下来的问题就简单了，枚举每一个右端点 $r$，直接算贡献即可，这个过程仍然是 $O(n \lceil\log_2 V\rceil)$。具体：

- 枚举每一数位 $j$，如果 $B_l$ 的二进制下第 $j$ 位（这里 $j$ 从 $0$ 开始）为 $0$，答案加上 $c_{r-2,j} \times2^j$；反之，同理。

### code

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, r, l) for (int i = r; i >= l; i--)
using namespace std;
typedef long long LL;
const int N = 2e5 + 5, TP = 28, mod = 1e4 + 7;
int n, A[N], B[N], c[30][N];
int main() {
  FASTIO;
  cin >> n;
  rep(i, 1, n) cin >> A[i], B[i] = B[i - 1] ^ A[i];
  LL ans = 0;
  rep(i, 1, n) rep(j, 0, TP) {
      int id = B[i] >> j & 1;
      if (i > 1) {
        if (id) ans += (i - 1ll - c[j][i-2]) << j;//id=1 时计算 0 的个数
        else ans += ((LL)c[j][i-2])<<j;// id=0 时计算 1 的个数
      }
      c[j][i] = id + c[j][i - 1];
    }
    cout << ans;
    return 0;
}
```

---

## 作者：mystic_qwq (赞：1)

拆位算贡献。

问题：求 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(a_i\oplus a_{i+1}\oplus\cdots\oplus a_j)$。

显然可以前缀异或和，设 $a$ 的前缀疑惑和数组为 $s$，问题转化为求 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n s_j\oplus s_{i-1}$。于是，我们可以记录所有 $s_x$ 的每个二进制位有多少个 $1$，然后和 $s_{i-1}$ 的当前二进制位比对算贡献，问题就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[300001], s[300001];
//, s1[300001];
int sums[300001][30];
main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i], s[i] = s[i - 1] ^ a[i];
    for (int j = 0; j < 30; ++j) {
      sums[i][j] = sums[i - 1][j] + (s[i] >> j & 1);
      //cout << sums[i][j] << " \n"[j == 29];
    }
  }
  long long ans = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < 30; ++j) {
      if (s[i - 1] >> j & 1) {
        int z = n - i - (sums[n][j] - sums[i][j]);
        ans += (1ll * z) << j;
      } else {
        int p = sums[n][j] - sums[i][j];
        ans += (1ll * p) << j;
      }
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Engulf (赞：1)

简单题。

区间异或和可转化为前缀和，记 $s_i = \oplus_{j = 1}^i a_j$，则 $\oplus_{i=l}^ra_j = s_r \oplus s_{l - 1}$，令 $s_0 = 0$，这个根据 $x \oplus x$ 可以推出来，相当于把前 $l-1$ 个数去掉。

所以我们要求的 $\sum\limits_{i = 1}^{n - 1}\sum\limits_{j = i + 1}^n (a_i \oplus a_{i + 1} \oplus \cdots \oplus a_j) = \sum\limits_{i = 0}^{n - 2}\sum\limits_{j = i + 2}^n s_i \oplus s_j$。

由于异或运算是独立的，对于 $s_i$，考虑它的第 $k$ 位何时会对答案产生贡献，讨论：
- 若 $s_i$ 的第 $k$ 位为 $0$，则对于每个 $j \in [i + 2, n]$ 且满足 $s_j$ 的第 $k$ 位为 $1$ 的都有 $2^k$ 的贡献。
- 若 $s_i$ 的第 $k$ 位为 $1$，则对于每个 $j \in [i + 2, n]$ 且满足 $s_j$ 的第 $k$ 位为 $0$ 的都有 $2^k$ 的贡献。

只需要用个前缀和维护区间每一位的 $0$ 和 $1$ 的个数即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n;
int a[N];

int sum[N][27];

inline int query(int l, int r, int k) {return sum[r][k] - (!l ? 0 : sum[l - 1][k]);}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i] ^= a[i - 1];

    for (int i = 0; i <= n; i++)
        for (int j = 26; ~j; j--)
            sum[i][j] = sum[i - 1][j] + (a[i] >> j & 1);

    ll ans = 0;

    for (int i = 0; i <= n - 2; i++) {
        for (int j = 26; ~j; j--) {
            int v = a[i] >> j & 1;
            if (!v) ans += 1ll * query(i + 2, n, j) * (1 << j);
            else ans += 1ll * (n - (i + 2) + 1 - query(i + 2, n, j)) * (1 << j);
        }
    }

    cout << ans << "\n";

    return 0;
}
```

---

## 作者：fengxiaoyi (赞：1)

考虑拆位计算，算每一位的答案。

那原题就转化成在 $0,1$ 序列上的求值。

对于快速求一段区间的异或和，显然想到先对每一位做个前缀异或和。

举样例 $2$ 的第三位为例子：

$$0,1,1,1,0,0,1$$

做完前缀异或和后变为：

$$0,1,0,1,1,1,0$$

显然异或和为 $0$ 是不会对答案有贡献。因为这是个 $0,1$ 序列，所以对于每一个数，对答案的贡献是这个数之前与其值不同的个数。

例如：第 $4$ 个数，它前面有 $2$ 个与其不同（第 $1$ 和第 $3$ 个），所以贡献是 $2$（区间是 $[2,4],[4,4]$）。

然后就可以算了。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline void ri(int &_a){
	int res=0,f=1;
	char c;
	for(;(c=getchar())<'0'||c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9') res=(res<<1) + (res<<3) + c-'0',c=getchar();
	_a=res*f;
}
inline void rll(long long &_a){
	long long res=0ll,f=1;
	char c;
	for(;(c=getchar())<'0'||c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9') res=(res<<1) + (res<<3) + c-'0',c=getchar();
	_a=res*f;
}
/*-----------------*/
int n;
long long a[200010],ans;
int main(){
	ri(n);
	for(int i=1;i<=n;i++) rll(a[i]);
	for(int i=0;i<40;i++){
		int p=0,q=0,now=0;
		long long sum=0;
		for(int j=1;j<=n;j++){
			int up=now;
			now^=(a[j]&1);
			sum+=(now?p:q);
			a[j]>>=1;
			up?q++:p++;
		}
		ans+=1ll*sum*(1ll<<i);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Liyunze123 (赞：1)

# 题意
对于所有的 $1\le i<j \le n$，求 $a_i$ 到 $a_j$ 的异或和之和。
# 题解
暴力，时间复杂度 $O(n^3)$，通过前缀异或和优化 $O(n^2)$。超时。

我们观察到，对于所有的 $i$，要求的是 $i<j\le n$ 的异或和中，每一个二进制位乘上有多少个异或和该位为 $1$ 之和。

对于每个二进制位 $2^x$，求 $a_x$ 数组为所有二进制第 $x$ 位为一的数的下标。$s_{0,x}$ 数组存的是 $a_{x,i}$ 和 $a_{x,i+1}$ 的差的前缀和，其中 $i$ 是奇数。同样的存 $s_{1,i}$ 数组，$i$ 是偶数。

求和呢，对于每个起点 $i$ 和二进制位 $2^x$，答案增加 $2^x \times f(i,x)$，$f(i,x)$ 为多少个异或和 $2^x$ 位为 $1$，也就是从 $i$ 开始，满足到 $j$ 出现奇数个 $2^x$ 位为一的 $j$ 的个数。

接下来自己找找规律，要求的和是存在 $s_0$ 里还是 $s_1$ 里，用前缀和即可。如果不会实现的话，可以参考代码。

时间复杂度是 $O(n \log a_i)$ 的。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],e[30][200010],t[30],p[2][30];
long long ans,s[2][30][200010];
int main(){
	scanf("%d",&n);
	for(int w=1;w<=n;w++){
		scanf("%d",&a[w]);
		for(int x=0;x<30;x++)if((a[w]>>x)&1)e[x][++t[x]]=w;
	}
	for(int x=0;x<30;x++)if(t[x])e[x][++t[x]]=n+1;
	for(int w=0;w<30;w++)
		for(int x=1;x<t[w];x++)
			if(x%2)s[0][w][p[0][w]+1]=s[0][w][p[0][w]]+e[w][x+1]-e[w][x],p[0][w]++;
			else s[1][w][p[1][w]+1]=s[1][w][p[1][w]]+e[w][x+1]-e[w][x],p[1][w]++;
	for(int w=1;w<=n;w++)
		for(int x=0;x<30;x++){
			int u=lower_bound(e[x]+1,e[x]+t[x]+1,w)-e[x];
			if(e[x][t[x]]<w)continue;
			int y=(u+1)%2;
			ans+=(s[y][x][p[y][x]]-s[y][x][(u+1)/2-1]-(a[w]>>x&1))*(1<<x);
		}
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

记 $s_i=\oplus_{j=1}^i A_j$，题目可以转化为：$\sum\limits_{i=0}^{n-1}\sum\limits_{j=i+2}^ns_i\oplus s_j$。

这个东西拆位之后是 $0,1$ 序列然后求异或和是 $1$ 的位置，对于 $i$，计算 $j\le i-2$ 的 $j$ 产生的贡献即可，使用变量记录前缀和是容易的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N], cnt0, cnt1, ans;
signed main(){
	// freopen("data.in", "r", stdin);
	// freopen("code.out", "w", stdout);
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
		a[i] ^= a[i - 1];
	}
	for(int bit = 0; bit < 30; bit++){
		cnt0 = cnt1 = 0;
		for(int i = 1; i <= n; i++){
			if(a[i] >> bit & 1){
				ans += cnt0 * (1 << bit);
			}
			else{
				ans += cnt1 * (1 << bit);
			}
			if(a[i - 1] >> bit & 1){
				cnt1++;
			}
			else{
				cnt0++;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

# 三倍经验

[P3917 异或序列](https://www.luogu.com.cn/problem/P3917)

[P9236 [蓝桥杯 2023 省 A] 异或和之和](https://www.luogu.com.cn/problem/P9236)

## 类似题目

[XOR on Segment](https://www.luogu.com.cn/problem/solution/CF242E)

[Sum of XOR Functions](https://www.luogu.com.cn/problem/CF1879D)

# 题解

显然 $a \bigoplus b \bigoplus b =a$，所以考虑记录一个 $pre$ 数组记录前缀异或和。

则

$$
\begin{aligned}
\sum_{i=1}^{i<n} \sum_{j=i+1}^{j\le n} \bigoplus_{k=i}^{k \le j} a_k &=\sum_{i=1}^{i\le n} \sum_{j=i}^{j\le n} \bigoplus_{k=i}^{k \le j} a_k - \sum_{i=1}^{i\le n} a_i \\
&= \sum_{i=1}^{i\le n} \sum_{j=i}^{j\le n} pre_{i} \bigoplus pre_{j} - \sum_{i=1}^{i\le n} a_i
\end{aligned}
$$

其中 $\sum_{i=1}^{i\le n} a_i$ 可以 $O(n)$ 计算，重点是计算前面这部分。

考虑把每个数按二进制拆分，逐位记录贡献，统计异或后二进制位为 $1$ 的贡献。

$\sum_{i=1}^{i\le n} \sum_{j=i}^{j\le n} pre_{i} \bigoplus pre_{j}$ 的意思是两两异或，所以可以用乘法原理，枚举二进制位 $d$，再设 $pre$ 中有 $s_0$ 个二进制第 $d$ 位为 $0$ 的，有 $s_1$ 个二进制第 $d$ 位为 $1$ 的，枚举前缀异或 $j$，第 $i$ 位贡献为 $2^i s_{1-pre_j}$。

时间复杂度 $O(n \log w)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 200005
int n, a[N], pre[N];

void _main() {
	cin >> n;
	long long tot = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], tot += a[i], pre[i] = pre[i - 1] ^ a[i];
	long long res = 0;
	for (int i = 27; i >= 0; i--) {
		int s[2] = {0, 0};
		for (int j = 1; j <= n; j++) {
			int u = pre[j - 1] >> i & 1, v = pre[j] >> i & 1;
			s[u]++;
			res += (1LL << i) * s[v ^ 1];  
		}
	}
	cout << res - tot;
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	_main();
	return 0;
}
```

---

## 作者：HasNoName (赞：0)

### 思路
统计出每一项的前缀异或和，记为 $s_i$。

将 $s_i$ 的每一二进制位分类讨论。

由于异或每一位是分开的，只用记录前面每一项中 $1$ 的个数，将当前前缀异或和的每位二进制是 $0$ 还是 $1$ 分类讨论即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
ll f[N],sum[N][35],s[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,x;
	ll ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		s[i]=s[i-1]^x;
		int t=s[i];
		for(int j=0;j<=30;j++)
		{
			sum[i][j]=t&1;
			t>>=1;
			sum[i][j]+=sum[i-1][j];//记录下每一项前缀之前这一二进制位的1出现个数
		}
		if(i==1)continue;
		t=s[i];
		for(int j=0;j<=30;j++)
		{
			if(!(t&1))ans+=(1<<j)*sum[i-2][j];
			else ans+=(1<<j)*(i-1-sum[i-2][j]);//将这一项是0还是1分类讨论异或和
			t>>=1;
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Guizy (赞：0)

考虑拆位算贡献。

如果在该位上某段区间有奇数个 $1$，这段区间的贡献就是 $1$ 乘上这位的位权，否则是 $0$。

问题就变成处理多少段有奇数个 $1$ 了。

可以用一个 $dp$ 数组解决。设 $dp_j$ 表示对于当前枚举到的 $i$，在第 $j$ 位上有多少 $[x,i]$，区间中有奇数个 $1$。

事实上这个数组也很好求，只要我们每次遇到 $1$ 就令 $dp_j\leftarrow i-dp_j$ 即可。

但是这样所有的区间 $[x,x]$ 都会被统计两遍，我们发现这些重复的区间拼起来正好是 $\sum a_i$，统计时要减掉。

具体实现及答案统计看代码：

```cpp
int n,a,dp[40],ans;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		for(int j=31;j>=0;j--){
			if(a&(1<<j)) dp[j]=i-dp[j];//反转
			ans+=dp[j]*(1<<j);//区间数乘上位权
		}
		ans-=a;//重复了，减掉
	}
	cout<<ans;
}
```

---

## 作者：imljw (赞：0)

我们很快的就可以想出暴力做法，枚举区间，复杂度 $O(n^2)$。很明显不能通过。

再仔细一思考，我们发现，每个数位其实是单独，互不关联的，所以我们可以把它当成 $n$ 个 $01$ 串，每个去算异或和。

具体计算方式如下:

预处理前缀 $1$ 的个数，然后再预处理前缀 $1$ 的个数为奇数的个数，根据他们就可以对于每个数的每个数位 $O(1)$ 算出他们的贡献了。

代码如下，仅供参考：

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n, a[30][200005], x, l[200005], mal, o[200005], b[200005];
long long an;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);

        while (x)
        {
            a[l[i]][i] = x & 1;
            x >>= 1;
            l[i]++;
        }
        l[i]--;
        mal = max(mal, l[i]);
    }
    for (int i = 0; i <= mal; i++)
    {
        long long cn = 0, x = 0;
        for (int j = 1; j <= n; j++)
            b[j] = b[j - 1] + a[i][j], o[j] = o[j - 1] + (b[j] % 2 == 1);
        for (int j = 1; j < n; j++)
        {
            if (b[j - 1] % 2 == 0)
                cn += o[n] - o[j];
            else
                cn += n - j - o[n] + o[j];
        }
        an += cn * (1ll << i);
    }
    printf("%lld\n", an);
    return 0;
}
```

---

## 作者：PigNotFound (赞：0)

首先，令 $sum_i$ 表示 $A$ 数组的异或前缀和。则原问题等价于求 $\sum_{i=1}^{N}\sum_{j=i+1}^{N}(sum_i \oplus sum_j)$

因此，记录所有 $sum_i$ 在二进制下第 $j$ 为是否为 1。

对于每一个 $sum_i$，枚举二进制下的每一位 $j$。若这一位值为 1，则加上 $sum_1$ 到 $sum_{i - 2}$ 每一个 $j$ 位为 0 的数乘上 $2^j$。若这一位值为 0，则加上 $sum_1$ 到 $sum_{i - 2}$ 每一个 $j$ 位为 1 的数乘上 $2^j$。求个数只需要二分即可。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Pig = 2e5 + 10;
ll sum[Pig], sum2[Pig];
vector<ll> nums[100];
int main() {
    ll n, ans = 0, tot = 0;
    cin >> n;
    vector<int> s;
    for (int i = 0, cur; i < n; i++) {
        cin >> cur;
        s.emplace_back(cur);
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i - 1] xor s[i - 1]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 62; j++) {
            if ((sum[i] >> j) & 1) {
                nums[j].emplace_back(i);
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 60; j++) {
            ll l = upper_bound(nums[j].begin(), nums[j].end(), i - 2) - nums[j].begin();
            if ((sum[i] >> j) & 1) {
                ans += ((i - l - 1) << j);
            } else {
                ans += (l << j);
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

本题与 [P9236 异或和之和](/problem/P9236) 极为相似，建议先把它切了。这里我就以 P9236 再讲一遍方法。至于为什么叫“极为相似”而不叫“一模一样”，这是因为两者题目描述略有不同。P9236 要求答案将每个元素进行累加，而此题没有涉及到单独一个元素作为区间的情况。

也就是说，两者答案的差就是 $a$ 数组的元素之和。

进入正题。首先我们需要把区间异或和转化为两个数的异或。注意到异或和满足类似前缀和的性质。先预处理一个前缀异或和 $s$ 数组，则 $a_l$ 至 $a_r$ 的异或和变为了 $s_r$ 与 $s_{l-1}$ 的异或值。于是就转化成了所有两个数的异或之和。

接着我们需要用一个二维数组来记录每一位上的 $0$ 或 $1$ 出现个数（记录的是 $s$）。这样算答案的时候只需要一位一位地看，第 $i$ 位（从右往左，从 $0$ 开始）的答案贡献极为当前位 $0$ 的个数和 $1$ 的个数的乘积再乘上 $2^i$。

因为这里其实是把 $a_i$ 全都算了一遍的，所以最后要减去 $a$ 数组之和。
```cpp
N=2e5+5,M=30;
for(int i=1;i<=n;i++) s[i]=s[i-1]^a[i];
for(int i=0;i<=n;i++){
  for(int j=M;j>=0;j--){
    if((s[i]>>j)&1) f[j][1]++;
    else f[j][0]++;
  }
}
for(int i=0;i<=M;i++){
  ans+=f[i][0]*f[i][1]*t;
  t<<=1;
}
cout<<ans-ss<<'\n';
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

你会发现，如果 $O(n^2)$ 地枚举左端点，右端点递推，会 T 飞的！

所以我们只能按位考虑。

设 $f_{i, j}$ 表示现在从后往前到了第 $i$ 个，第 $j$ 个二进制位的异或和（即后缀的异或值）。

设 $g_{i, j}$ 表示 $\sum_{k=i}^{n} f_{k, j}$，即后缀异或值的后缀和。

我们需要计数的是第 $j$ 位以 $i$ 为结尾有多少个 $1$，所以对于右端点 $i$ 固定的区间，答案就是 $g_{1, j} - g_{i, j}$。为什么不是减去 $g_{i + 1, j}$ 呢？因为不包括 $i$ 这一个数本身。

我们把所有位的 $1$ 的个数乘上各自的次方数，输出即可。

但是这样就结束了吗？你会发现，样例 WA 掉啦！

为什么？因为有可能 $f_{i + 1, j}$ 是 $1$，此时后面的异或值全部取反了，所以我们这时候不是计数 $1$ 的个数，而是计数 $0$ 的个数。

最后，这道题就做完了。

注意，其实可以前缀和，但是作者赛时想到的是后缀和。

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
观察到式子与二进制相关，考虑分开位数计算，将每一位包含 $1$ 的数统计次数，那么该点的贡献就为前面一段 $0$ 的个数，再乘上这一位的二进制的大小，取和即可。
## code：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long a[5000005],sum;
int main()
{
	int n,i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)cin>>a[i],sum+=a[i];
	long long s,m,ans=0;
	for(j=0;j<32;j++)
    {			
		s=m=0;
		for(i=1;i<=n;i++)
        {		
			if((a[i]>>j)&1)	s=i-s;		
			m+=s;		
		}
		ans+=m*(1<<j);			
	}
	cout<<ans-sum;//没有长度为1的序列
}

```

---

## 作者：luogu_gza (赞：0)

拆位。

问题转化为对一个 01 序列 $b$ 求：

$$\sum_{1 \leq i<j \leq n}[\sum_{k=i}^{j}b_k \equiv 1 \pmod 2]$$

这个问题不难有 dp。

设 $f_{i,0/1}$ 表示结尾位置为 $i$，当前和对二取模是 $0/1$ 的方案数。初始 $f_{i,b_i}=1$，转移不难，答案为 $\sum_{i=1}^{n}f_{i,1}$。

[code](https://atcoder.jp/contests/abc365/submissions/56269890)。

---

## 作者：__O_v_O__ (赞：0)

首先，异或有一个性质：$a\oplus b\oplus b=a$。

我们可以求出每一项的前缀异或和 $p_i$，根据上面的性质，区间 $[l,r]$ 的异或和就是 $p_r\oplus p_{l−1}$。

有了这个式子，我们就可以把所求答案转变为：$\sum\limits_{i=1}^n\sum\limits_{j=0}^{i-1}p_i\oplus p_j$。

但这个做法的复杂度是 $O(n^2)$，还需要优化。

我们考虑处理出 $w_{i,j}$ 表示在所有数中，第 $i$ 个二进制位上为 $j$ 的有 $w_{i,j}$ 个。

使用乘法原理，我们很容易就可以求出该位最终为 $1$ 的个数，最后乘上该位的权值就可以了。所以最后的答案为：$\sum\limits_{i=0}^{31}w_{i,0}\times w_{i,1}\times 2^i$。

时间复杂度 $O(n)$，可以通过。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,an,a[1000001],su;
signed main(){
	ios::sync_with_stdio(0),cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],su+=a[i];
	for(int i=1;i<=n;i++)a[i]^=a[i-1];
	for(int d=0;d<31;d++){
		int c[2]={0,0};
		for(int i=0;i<=n;i++)c[a[i]>>d&1]++;
		an+=(1<<d)*c[0]*c[1];
	}
	cout<<an-su;
	return 0;
}
```

---

