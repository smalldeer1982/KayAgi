# [NICA #3] 星空（Easy Version）

## 题目背景

**Easy Version 和 Hard Version 差别在于数据范围。**

## 题目描述

小 R 有一个长度为 $n$ 的序列 $a$，保证序列中的每个数都是 $2$ 的整数次幂。

小 M 有一个数 $x$，她希望重新排列序列 $a$，使得不存在一个 $i\in[1,n)$ 满足 $a_i+a_{i+1}>x$。重排的方式为：选择一个 $1\sim n$ 的排列 $p$，然后令新序列 $a'$ 满足 $a'_i=a_{p_i}$。$a'$ 即为重排后的序列。

现在你想要知道有多少种重排的方式能满足小 M 的要求。两种重排方式不同当且仅当选择的排列 $p$ 不同。答案对 $10^9+7$ 取模。

## 说明/提示

数据保证，$2 \leq n \leq 61$，$1 \leq a_i \leq 2^{60}$，$1\le x< 2^{63}$。**每一个 $a_i$ 都不重复**。

## 样例 #1

### 输入

```
4 20
2 4 8 16```

### 输出

```
12```

# 题解

## 作者：wyf1202 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/B3901)

$a$ 序列里每个元素都是 $2$ 的整数次幂，从而 $2$ 个不等于最大值的元素相加一定不大于最大值。

因此，我们只需要考虑重排后最大值与相邻位置的和是否合法。

枚举最大值所在的位置 $i$，枚举与之相邻的元素对应着数组里哪两个元素。

分析之后得到有两种情况：$1<i<n$ 和 $i=1$ 或 $i=n$。

在 $i=1$ 或 $i=n$ 时，只有当 $a_j+a_{max}\le x$ 时合法。

如果合法，那么剩下的 $n-2$ 个位置可以随意地填充剩下来的元素，共有 $(n-2)!$ 种方案。

$1<i<n$，此时与最大值相邻的有两个位置。分别枚举这个位置填放了 $a_j$ 和 $a_k(≠a_{max})$。

这个数只有当 $a_j+a_{max}\le x$ 且 $a_k+a_{max}\le x$ 时合法。

如果合法，那么剩下的 $n-3$ 个位置可以随意地填充剩下来的元素，共有 $(n-3)!$ 种方案。

这道题的数据范围很小，因此无论怎么写，都能通过本题，复杂度 $O(n)$。

```cpp
//j[i]表示i的阶乘
//a[i]表示数组里的数
const int mod=1e9+7;
long long n,x,mx,sum,ans,a[100005],j[100005];
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)if(a[i]>mx)mx=a[i];
	for(int i=1;i<=n;++i)
		if(a[i]!=mx&&a[i]+mx<=x)sum++;
	j[1]=1;
	for(int i=2;i<=n;++i)j[i]=(j[i-1]*i)%mod;
	for(int i=1;i<=n;++i){
		if(i==1||i==n)ans=(ans+sum*j[n-2])%mod;
		else ans=(ans+sum*(sum-1)*j[n-3])%mod;
	} cout<<ans;	return 0;
}
```

请各位大佬多多指教，如有不足请提出！

---

## 作者：起名字重要吗 (赞：4)

应该是本题码量最少的一篇题解了。

首先观察题目：

>保证序列中的每个数都是 $2$ 的**整数次幂**。

>**每一个** $a_i$ 都**不重复**。

简单思考一下就知道比最大值小的**任意两个** $a_i$ 相加在一起都**小于最大值**，也就是说这题只用考虑 $a_{max}$ 的位置以及 $a_{max}$ 与相邻数相加是否会超过 $x$ 即可，后面就是一些简单的排列组合。

令与 $a_{max}$ 相加不大于 $x$ 的 $a_i$ 个数为 $cnt$，以下是排列组合求解的解析：

- 当 $pos_{a_{max}} = 1$ 或 $pos_{a_{max}} = n$ 时，在 $a_{max}$ 旁边只能放 $cnt$ 个 $a_i$ 中的任意 $1$ 个，这用去了 $2$ 个空位，还剩下 $(n-2)$ 个 $a_i$，任意排序即可，这部分方案数为 $2 \times cnt \times 1 \times 2 \times \cdots \times （n-2）$。
- 当 $1 < pos_{a_{max}}< n$ 时，在 $a_{max}$ 旁边可以放 $cnt$ 个 $a_i$ 中的任意 $2$ 个，这用去了 $3$ 个空位，还剩下 $(n-3)$ 个 $a_i$，任意排序即可，这部分方案数为 $(n-2) \times cnt \times (cnt-1) \times 1 \times 2 \times \cdots \times （n-3）$。
- **答案**即为上文两式相加。

代码实现需要**注意**的地方：

1. $0! = 1$，预处理阶乘时需要写。
2. 注意开 long long，计算过程中及时取模。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,x,a[70],maxa,fac[70]= {1},cnt,mod=1e9+7;//注意a数组的初始化
int main() {
	scanf("%lld%lld",&n,&x);
	for(int i=1; i<=n; i++) scanf("%lld",&a[i]),maxa=max(maxa,a[i]);//找到最大的a[i]
	for(int i=1; i<=n; fac[i]=(fac[i-1]*i)%mod,i++) if(a[i]!=maxa&&a[i]+maxa<=x) cnt++;//预处理出n-2与n-3的阶乘并计算cnt
	printf("%lld",(2*cnt*fac[n-2]%mod+(n-2)*cnt*(cnt-1)*fac[n-3]%mod)%mod);//利用公式求解
	return 0;
}
```
时间复杂度 $O(n)$。

---

## 作者：DFM_O (赞：3)

## [B3901题目](https://www.luogu.com.cn/problem/B3901)

### 解题思路
由题意易知，若序列 $a$ 的最大值与最小值之和大于 $x$，则此题无解，输出 `0`。

因为每一个 $a_i$ 都不重复且序列中的每个数都是 $2$ 的整数次幂，所以在序列中任选两数，且这两个数均不是序列的最大值，则这两数之和一定不大于最大值。

因为我们已经对于无解的情况进行了特判，所以最大值一定小于 $x$。

即我们只需要注意最大值和与最大值相邻的数，其他数无论怎么排都小于 $x$。

最后求出可以与最大值相邻的数的数量，并用排列数求出答案即可。

### Code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
const int p=1e9+7;
long long a[62];
long long A(long long a,long long b)//排列
{
	long long s=1;
	for(int i=a;i>=a-b+1;i--)
		s=s*i%p;
	return s;
}
int main()
{
	long long n,x,max,l=-1,m=0;
	cin>>n>>x;
	for(long long i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	max=a[n];
	for(long long i=n-1;i>=1;i--)
	{
		if(a[i]+max<=x)
		{
			l=i;
			break;
		}
	}
	if(l==-1)//对于无解的情况进行特判
	{
		cout<<0;
		return 0;
	}
	l=n-1-l;//统计可以与最大值相邻的数的数量
	m+=(n-1)*l*2%p*A(n-2,n-2)%p;
	if(l>1)
		m-=(n-2)*A(l,2)%p*A(n-3,n-3)%p;
	if(m<0)	
		m+=p;	
	m=A(n,n)-m%p;
	if(m<0)	
		m+=p;		
	cout<<m;		
	return 0;
}
```

---

## 作者：Melo_DDD (赞：2)

日常水题解，然后记住要是参与运算中会爆 int 但是有的变量没有开 long long 就是小丑。

观察题目，我们发现每个数都是 $2$ 的正整数次幂，而且互不相同。

那么我们可以知道除了最大值以外任意两个数相加都小于最大值。很显然，证明略。

那么我们只用去考虑最大值和谁相邻，因为其他的相邻的两个数加起来还没有它大呢。那么我们就可以找到原序列中使得 $a_i+max\le x$ 的最大的 $a_i$。假设升序排序后它的下标是 $j$，那么一共有 $j$ 个数可以和最大值相邻。当且仅当这些情况时满足题意。

注意到排列时当最大值在开头、末尾和在序列中间是不一样的，因为如果在开头或者末尾的话只需要有一个满足条件的数和它相邻即可，否则它的左右两边的两个数必须全都满足条件。

第一种情况，我们只需要 $j$ 个数中有一个和它相邻，剩下的 $n-2$ 个数任意排列都行，那么一共 $j\times(n-2)!$ 种情况。注意开头、末尾是两种，所以还要乘一个 $2$。

第二种情况，我们需要在 $j$ 个数中选出两个和最大值相邻，另外 $n-3$ 个数做全排列。那么一共就有 $j\times(j-1)\times(n-3)!$ 种情况。最大值在序列中间一共有 $n-2$ 个不同位置，还要乘一个 $n-2$。

最后加起来就可以了。

---

## 作者：a_little_carrot (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/B3901)

## 普通解法
### 思路简述
#### 证明
观察题目，得出初步结论：方案否成立关系到最大值和其边上的值之和是否小于 $x$。\
为什么呢？

首先我们要知道一个东西：\
已知序列 $a$ 内元素都是 $2$ 的整数次幂。\
如果 $a_x > a_y$ 且 $a_x > a_z$，\
那么 $a_y + a_z < a_x$。

证明：\
假设 $a_y + a_z \ge a_x$。\
假设 $a_y > a_z$。\
因为序列 $a$ 内元素都是 $2$ 的整数次幂，所以 $a_z \le \frac{1}{2} a_y \le \frac{1}{4}a_x$。\
我们假设 $a_y$ 和 $a_z$ 都取最大值，即取 $\frac{1}{2}a_x$ 和 $\frac{1}{4}a_x$。\
可以代入到假设的式子中。
$$a_y + a_z \ge a_x$$
$$\Rightarrow \frac{1}{2}a_x + \frac{1}{4}a_x > a_x$$
$$\frac{3}{4}a_x > a_x$$
由于 $a$ 中都是正整数，所以 $a_y + a_z \ge a_x$ 显然是不成立的。

那因为 $a$ 中没有值大于最大值，所以其中任意两数（不包括最大值）的和一定小于最大值。\
因此这个方案是否成立只和最大值有关。

#### 思路
得出了如上的结论，我们就可以计算答案了。

因为最大值和其边上的值之和小于 $x$ 这个方案就是可行的，所以可以枚举最大值边上的元素，其余元素自由排列。

分类讨论最大值的位置，得出两种情况：
1. 最大值是 $a_1$ 或 $a_n$，此时只用计算最大值边上的一个元素。其余元素自由排列的方案数是 $\prod_{i=1}^{n-2}i$。
2. 最大值是 $a_i (1 < i < n)$，此时要计算最大值边上的两个元素，其余元素自由排列的方案数是 $\prod_{i=1}^{n-3}i$。

但是这样取两个元素时会达到 $n^3$ 的复杂度（左元素 $\times$ 右元素 $\times$ 阶乘），考虑优化。

优化计算。记与最大值的和小于 $x$ 的值组成的序列为 $b$，个数为 $cnt$。\
因为计算两个元素时相当于在 $b$ 中取两个元素（互不相等），即 $cnt$ 取 $2$，则方案数等于 $cnt~\cdot~(cnt-1)$。使得计算方案数的时间复杂度减少到 $O(n)$。

优化阶乘。记 $f_i$ 为 $\prod_{j=1}^{i}j$，$O(n)$ 预处理，$O(1)$ 使用。

到这里就可以用 $O(n)$ 的时间解开这题了。\
当然这题 $n$ 很小，$O(n^3)$ 也是可以过的（）。
### 代码
稍微压了点行，总计 $16$ 行。\
（$13$ 行）`For(i,2,n-1) ans=(ans+cnt*(cnt-1)*f[n-3])%mod ;` 这里是可以再优化的，但是直接用乘法再取模，`__int128` 一样会爆，所以这里就不优化了。
```cpp
#include "iostream"
using namespace std ;
#define For(i,l,r) for(int i=(l);i<=(r);++i)
typedef long long ll ;
const int mod=1e9+7,N=64 ;
ll n,x,maxn,f[N]{1,1},p[N],cnt,ans ;
ll read(ll &m) {m=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar());for(;ch>='0'&&ch<='9';ch=getchar())m=m*10+ch-'0';return m;}
void init() {For(i,2,N)f[i]=(f[i-1]*i)%mod;}
int main() {
	init();read(n),read(x) ;
	For(i,1,n) maxn=max(maxn,read(p[i])) ;
	For(i,1,n) cnt+=(p[i]!=maxn)&&(p[i]+maxn<=x) ;
	ans=(2*cnt*f[n-2])%mod;For(i,2,n-1) ans=(ans+cnt*(cnt-1)*f[n-3])%mod ;
	cout<<ans ;
	return 0 ;
}
```

---

## 作者：Ren_Hx (赞：0)

### 前言
用 DP 直接干掉。
### 分析
题目给了我们一个长度为 $n$ 的序列 $a$ ，我们要找到所有可能的排列方式，使对于每对相邻元素 $a'[i]$ 和 $a'[i+1]$ ，有：$a'[i] + a'[i+1] \leq x$ 。

而因为 $a$ 中的每个元素都是 `2` 的整数次幂，所以我们就可以利用这些元素的特性非常方便地进行有效的排列。
### Code
```cpp
const int MOD = 1e9 + 7;

// 计算阶乘
long long fac(int n) {
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result = (result * i) % MOD;
    }
    return result;
}

int main() {
    int n;
    long long x;
    cin >> n >> x;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    
    sort(a.begin(), a.end());// 对数组进行排序

    vector<long long> dp(n + 1, 0);
    dp[0] = 1; // 空序列的排列方式为 1

    for (int i = 1; i <= n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (j > 0 && a[j - 1] + a[i - 1] > x) break; // 如果不满足条件，停止
            dp[i] = (dp[i] + dp[j]) % MOD; // 更新 dp[i]
        }
    }

    long long result = (dp[n] * fac(n)) % MOD;

    cout << result << endl;

    return 0;
}
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/B3901)

$a$ 数组里每个数都是 $2$ 的整数次幂，那么 $2$ 个不是最大值的数相加一定小于或等于最大值。所以，我们要判断重排后最大值与相邻的数的和可不可行。首先，找到最大值，枚举和最大值相邻的数，对应数组里哪两个数。再分情况讨论。

- 在 $i=1$ 或 $i=n$ 时，只有当 $a_j+a_{max}\le x$ 时可行。如果可行，剩下的 $n-3$ 个位置就能随变填充剩下来的数，共有 $(n-2)$ 的阶乘种方案。

- $1<i<n$，此时与最大值相邻的有两个位置。分别枚举这个位置填放了 $a_j$ 和 $a_k(\not=a_{max})$。

- 这个数如果满足 $a_j+a_{max}\le x$ 并且 $a_k+a_{max}\le x$，那么剩下的 $n-3$ 个位置就能随变填充剩下来的数，共有 $n-3$ 的阶乘种方案。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=1e9+7;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n,x;
	cin >>n>>x;
    int ma=0,s=0,ans,a[n],b[n];//定义
	for(int i=0;i<n;i++){
        cin >>a[i];
    }//输入
	for(int i=0;i<n;i++){
        if(a[i]>ma){//判断是否比现在的最大值大
            ma=a[i];//更新
        }
    }//找最大值
	for(int i=0;i<n;i++){
		if(a[i]!=ma&&a[i]+ma<=x){//判断是否满足
            s++;//增加一
        }
    }
	b[0]=1;//初始第一个量
	for(int i=1;i<n;i++){
        b[i]=(b[i-1]*i)%mod;//计算
    }
	for(int i=0;i<n;i++){
		if(i==0||i==n-1){//如果是开头或结尾
            ans=(ans+s*b[n-2])%mod;//(n-2)!
        }else{//不是
            ans=(ans+s*(s-1)*b[n-3])%mod;//(n-3)!
        }
    }
    cout<<ans;
    return 0;
}
```

---

