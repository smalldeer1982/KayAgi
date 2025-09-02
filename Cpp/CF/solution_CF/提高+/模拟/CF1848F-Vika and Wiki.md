# Vika and Wiki

## 题目描述

Recently, Vika was studying her favorite internet resource - Wikipedia.

On the expanses of Wikipedia, she read about an interesting mathematical operation [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR), denoted by $ \oplus $ .

Vika began to study the properties of this mysterious operation. To do this, she took an array $ a $ consisting of $ n $ non-negative integers and applied the following operation to all its elements at the same time: $ a_i = a_i \oplus a_{(i+1) \bmod n} $ . Here $ x \bmod y $ denotes the remainder of dividing $ x $ by $ y $ . The elements of the array are numbered starting from $ 0 $ .

Since it is not enough to perform the above actions once for a complete study, Vika repeats them until the array $ a $ becomes all zeros.

Determine how many of the above actions it will take to make all elements of the array $ a $ zero. If this moment never comes, output $ -1 $ .

## 说明/提示

In the first example, after one operation, the array $ a $ will become equal to $ [3, 3, 3, 3] $ . After one more operation, it will become equal to $ [0, 0, 0, 0] $ .

In the second example, the array $ a $ initially consists only of zeros.

In the third example, after one operation, the array $ a $ will become equal to $ [0] $ .

## 样例 #1

### 输入

```
4
1 2 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2
0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
1
14```

### 输出

```
1```

## 样例 #4

### 输入

```
8
0 1 2 3 4 5 6 7```

### 输出

```
5```

# 题解

## 作者：tZEROちゃん (赞：9)

为了简便起见，下标全部对 $n$ 取模。

不妨记 $f_{i, j}$ 表示第 $i$ 次操作后第 $j$ 个数是什么。

显然 $f_{0}$ 就是 $a$ 数组。

经过一次操作以后，$f_{1, i} = f_{0, i}\ {\rm xor}\ f_{0, i + 1}$。

第二次操作后，$f_{2, i} = f_{1, i}\ {\rm xor}\ f_{1, i + 1}$，然后再把上面那个式子带进来转化一下就会变成 $f_{2, i} = f_{0, i}\ {\rm xor}\ f_{0, i + 1}\ {\rm xor}\ f_{0, i + 1}\ {\rm xor}\ f_{0, i + 2}$，你发现有两个 $f_{0, i + 1}$，然后异或起来变成 $0$，所以 $f_{2, i} = f_{0, i}\ {\rm xor}\ f_{0, i + 2}$。

这个性质很有意思啊！

我们可以发现一个规律就是 $2^k$ 次操作之后，$f_{2^k, i}$ 就会变成 $f_{0, i}\ {\rm xor} \ f_{0, i + 2^k}$。


然后我们注意到当 $2^k = n$ 时，这玩意肯定已经变成 $0$ 了，所以必定有解。

倍增解决即可。

```cpp
int solve(int n) {
  for (int i = n >> 1; i >= 1; i >>= 1) {
    _rep (j, 0, n) b[j] = a[j] xor a[(j + i) % n];
    int qwq = 0;
    _rep (j, 0, n) qwq += b[j] == 0;
    if (qwq != n) {
      _rep (i, 0, n) a[i] = b[i];
      ans += i;
    }
  }
  _rep (j, 0, n) if (a[j] != 0) {
    ++ans; break;
  }
  return ans;
}
```

---

## 作者：StarLbright40 (赞：7)

隔壁怎么用高维前缀和啊，有点高端的，想不到。给个只用想到杨辉三角的。

>[F. Vika and Wiki](https://codeforces.com/contest/1848/problem/F)
>
>给定长为 $n$ 且从零标号的数组 $\{a\}$，满足 $n=2^k$。
>
>每次操作为同时令所有 $a_i\gets a_i\oplus a_{(i+1)\bmod n}$。
>
>求最少进行多少次操作能使 $\{a\} $ 变为全零，如果不能做到输出 $-1$。
>
>$0\le k\le 20,0\le a_i\le10^9$。

记 $c_{i,j}$ 表示操作 $i$ 次后，$a_0$ 的值变为 $\bigoplus_{j=0}^\infty c_{i,j}\times a_j$，下标对 $n$ 取模。其余的位置循环对称，不再赘述。

尝试计算即可发现其为 $\bmod~2$ 意义下的杨辉三角。

进而可以发现，在杨辉三角的第 $n=2^k$ 行，仅有的两个 $1$ 分别出现在第 $0$ 和第 $n$ 列，于是 $\{a\}$ 中的每一项均与自己异或，一定得到全零。所以那个 $-1$ 是诈骗。

注意到操作次数的合法性显然是单调的，且容易计算操作 $2^p$ 次后数组的状态，所以我们考虑倍增，令 $p$ 从 $k-1$ 取到 $0$，计算在操作 $2^p$ 次后数组是否全零，若不能全零则累加进答案，并覆盖原数组。

注意到在如上的每次计算之后，数组再进行 $2^p$ 次操作一定会变成全零，也就是说数组的前后两半部分一定完全相同。所以我们可以在每次计算后将数组长度减半，不影响结果。时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1<<20;
int n,k,a[N],b[N],ans;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i];
	if(!*max_element(a,a+n)) cout<<0;
	else{
		while(n/=2){
			for(int j=0;j<n;++j) b[j]=a[j]^a[j^n];
			if(*max_element(b,b+n))
				ans|=n,copy(b,b+n,a);
		}
		cout<<ans+1;
	}
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：7)

## 思路

设 $f_{i,j}$ 表示 $i$ 次操作后 $j$ 位置上是啥。

显然有

$$\large f_{i,j}=\operatorname{xor}_{k=0}^{i}(\small\binom ik\large\bmod 2)\times a_{j+k\bmod n}$$

如果你康了 UNR 的 D1T2，那么你会知道 $\binom ij$ 是奇数当且仅当二进制位上 $j$ 是 $i$ 的子集。

因为 $n$ 是 $2$ 的幂，所以操作 $n$ 次后一定全是 $0$。所以一定有解，且上界为 $n$。

直接做一遍高维前缀异或和就能得到 $f_{0,0},f_{1,0},\cdots,f_{n,0}$。

要找一个 $ans$ 使 $f_{ans,0}=f_{ans,1}=\cdots=f_{ans,n-1}=0$。

首先要 $f_{ans,0}=0$。

如果在 $x$ 次操作后位置 $0$ 清零了但是存在别的位置没清零，取 $i$ 为第一个没清零的位置，则有 $f_{x+i,0}\neq 0$。

所以

$$f_{x,0}=f_{x,1}=\cdots=f_{x,n-1}=0\Leftrightarrow f_{x,0}=f_{x+1,0}=\cdots=f_{\infty,0}=0$$

## code

```cpp
#include<stdio.h>
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,a[1048576];
main()
{
	read(n);for(int i=0;i<n;read(a[i++]));
	for(int i=0;i<20;++i)for(int j=0;j<1048576;++j)if(j>>i&1)
		a[j]^=a[j^1<<i];
	for(int i=n-1;i>=0;--i)if(a[i]){printf("%d",i+1);return 0;}
	putchar('0');
}
```

---

## 作者：BreakPlus (赞：4)

+ 考虑进行 $2^x$ 次操作等价于 $a_i = a_i \oplus a_{i+2^x}$。

+ 如果答案为 $A$，那么操作大于 $A$ 次序列仍然全 $0$。这意味着可以二分或倍增。

+ 由于我们只会做 $2^x$ 次操作，那么倍增并 check 是否全 $0$ 即可。

```cpp
ll n,a[1048576],b[1048576]; 
void solve(){
	n=read();
	ll cnt = 0;
	for(ll i=0;i<n;i++) a[i]=read(), cnt += (a[i]==0);
	if(cnt==n){
		cout<<"0"<<endl;
		return;
	} 
	ll k = log2(n), ans = 0; 
	for(ll i=k-1;i>=0;i--){
		ll cnt = 0;
		for(ll j=0;j<n;j++){
			b[j]=a[j]^a[(j+(1ll<<i))%n];
			cnt += (b[j]==0);
		}
		if(cnt<n){
			ans = ans + (1ll<<i);
			for(ll j=0;j<n;j++){
				a[j] = b[j];
			}
		}
	} 
	printf("%lld\n", ans+1);
}
```

---

## 作者：IceKylin (赞：3)

### CF1848F Vika and Wiki 题解

所有下标均对 $n$ 取模。

一些 Tircks：

1. 若进行 $k$ 次操作使得序列 $a$ 都变化为 $0$，那么进行 $k+1$ 次操作后序列 $a$ 依然都为 $0$，这就启示我们采取二分或倍增的思路来做题。

2. 进行 $2k$ 次操作等价于先进行 $k$ 次操作，再进行 $k$ 次操作（废话，但有点用）。

3. 设 $f_{i,j}$ 表示进行 $i$ 次操作后 $a_j$ 的值，那么有 $f_{2^k,i}=a_i\oplus a_{i+2^k}$。

4. 由 Trick 3 可知必然有解，且操作次数至多为 $n$ 次。

综上，倍增即可。

~~这看起来太水了~~。

考虑用数学归纳法，对 Trick 3 进行证明：

当 $k=0$ 时，$f_{1,i}=a_i\oplus a_{i+1}$，显然成立。

假设当 $k\le p$ 时均成立，考虑当 $k=p+1$ 时的情况。

由 Trick 2 和假设可知，$f_{2^k,i}=f_{2^{k-1},i}\oplus f_{2^{k-1},i+2^{k-1}}$。

进一步展开得，$f_{2^k,i}=\left(a_i\oplus a_{i+2^{k-1}}\right)\oplus \left(a_{i+2^{k-1}}\oplus a_{i+2^k}\right)=a_i\oplus a_{i+2^k}$。

故知当 $k=p+1$ 时也成立。

故原命题成立。证毕。

AC 代码：[link](https://codeforces.com/contest/1848/submission/250626838)。

---

## 作者：TerryWang (赞：2)

## CF1848F. Vika and Wiki 题解

简要题意：记 $f(a)$ 为序列 $a$ 循环相邻的每个数的异或值依次组成的序列，对 $a$ 迭代进行 $c$ 次 $f$ 操作的结果记为 $f^c(x)$。求满足 $f^c(a)$ 中每一个数均为 $0$ 的最小的 $c$。序列 $a$ 的长度 $n$ 一定是 $2$ 的整次幂且 $n\le 2^{20},0\le a_i\le10^9$。

这道题有多种解法，现汇总并列出我知道的几种，如有更多解法欢迎补充：

法 1. 二分。易发现若最初的 $a$ 不全为 $0$ 时不断迭代后一定是先连续出现有限个非全 $0$ 的序列，到达某个分界点后一直出现全 $0$ 序列。题目要求找这个分解点，所以我们可以二分。我们我们可以发现一个结论， $f^{2^l}(a)_i=a_i\oplus a_{i+2^l}$（$l\in \mathbb Z$，下同；证明考虑数学归纳法，在比赛时也可打表观察；由此式也可得知当 $c\ge n$ 时 $f^c(x)$ 一定全为 $0$ 从而为二分找到了一个上界），也就是说当 $c=2^l$ 求 $f^c(a)$ 时，每一个元素都只会贡献至多两个位置（当前和循环往前 $2^l$ 个的位置），因此此时我们暴力计算的时间复杂度也是可接受的。类比快速幂等算法，我们发现将 $c$ 的二进制表示法中为 $1$ 的位依次执行 $a\larr f^{2^l}(a)$ 即可。时间复杂度 $\Theta(n\log^2 n)$。

法 2. 仍然沿用法 1 的二分做法。将上面我们找到的结论推广到一般情况。我们有 $f^c(a)_i=\bigoplus_m [c\ \operatorname{and}\ m=m]a_{i+m}$（证明可以考虑和上述算法一样将 $c$ 的二进制表示法中为 $1$ 的位从高往低依次迭代）。我们又发现这个式子是个差卷积的形式，所以判定 $f^c(a)$ 可以直接拆位后 NTT 硬卷，不过应该跑得很慢。

法 3. 我们发现二分的判定过程中有很多不必要的重复计算。类比逐位贪心、倍增求 LCA 等算法，我们可以倍增。发现找迭代过程中第一次 $a$ 全为 $0$ 不太好倍增，我们可以找最后一次非全 $0$（注意一开始就全 $0$ 的要特判）。依次尝试 $c=n/2,n/4,\cdots,1$，如果迭代 $c$ 次后仍不全为 $0$ 那么就把 $a$ 替换成迭代后的数组，否则就原封不动。时间复杂度是 $\Theta(n\log n)$ 的。

法 4. 仍然沿用法 3 的二分做法。我们发现由在倍增过程进行到 $2^l$ 时再迭代 $2^l$ 次一定变全 $0$（因为答案上界为 $n$），也就是说此时原串变为循环节为 $2^l$ 的周期串了，因此可以只用保留一段循环节（具体实现可以每次倍增后砍掉右边部分只留左边），可以做到理论最优的复杂度 $\Theta(n)$。

Code ($\Theta(n)$):

```cpp
#include<bits/stdc++.h>
#define all(c) (c).begin(),(c).end()
signed main(){
	std::ios::sync_with_stdio(0);
	int n;
	std::cin>>n;
	std::vector<int> a(n);
	for(auto&x:a)std::cin>>x;
	if(std::none_of(all(a),std::identity())){
		std::puts("0");
		return 0;
	}
	int ans=0;
	for(int of=n/2;of;of/=2){
		// std::vector<int> tmp(n);
		std::vector<int> tmp(of*2);//法4的优化在于把上面一条语句替换为这条语句。
		
		for(int i=0;i<int(tmp.size());++i){
			tmp[i]=a[i]^a[(i+of)%a.size()];
		}
		if(std::any_of(all(tmp),std::identity())){
			ans|=of;
			a=tmp;
		}
	}
	std::printf("%d\n",ans+1);
}
```



法 5. 高维前缀和。

若一开始不全为 $0$ 则在第一次迭代到全 $0$ 的前一次一定满足 $a_i$ 全相同且不为 $0$（即这个时刻一定与 $a_0$ 最后一个不为 $0$ 的值的出现时刻相同，因此只用计算 $a_0$ 每次迭代的结果即可）。继续观察我们找到的结论 $f^c(a)_i=\bigoplus_m [c\ \operatorname{and}\ m=m]a_{i+m}$。注意到当 $i=0$ 时这个式子就是一个累加改成异或的高维前缀和（也叫子集和、Zeta 变换，就是 Or 卷积时做的那个变换），所以直接在高维前缀和板子上改就行了。

---

## 作者：ZMQ_Ink6556 (赞：1)

### 解题思路

首先分析操作，尝试找到规律：

- 操作 $0$：$p_{0,x} = a_i$
- 操作 $1$：$p_{1,x} = p_{0 , x} \operatorname{xor} p_{0 , x + 1} = a_i \operatorname{xor} a_{i + 1}$
- 操作 $2$：$p_{2,x} = p_{1,x} \operatorname{xor} p_{1 , x + 1} = a_i \operatorname{xor} a_{i + 1} \operatorname{xor} a_{i + 1} \operatorname{xor} a_{i + 2} = a_i \operatorname{xor} a_{i + 2}$
- 操作 $3$：$p_{3,x} = p_{2,x} \operatorname{xor} p_{2 , x + 1} = a_i \operatorname{xor} a_{i + 2} \operatorname{xor} a_{i + 2} \operatorname{xor} a_{i + 4} = a_i \operatorname{xor} a_{i + 4}$
- $\cdots \ \! \cdots$
- 操作 $k$：$p_{k , x} = p_{k - 1 , x} \operatorname{xor} p_{k - 1 , x + 1} = a_i \operatorname{xor} a_{i + 2^k}$

因此，不存在无解（$2^k = n$ 时一定清空）。

从大到小对于每个二进制位上的值，都更新处理即可。如果会变成全 $0$，则说明答案大了，否则说明还能继续更新。这里直接枚举即可。

复杂度 $O(n \log n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , k , a[2000005] , b[2000005] , ans;
int makek()
{
	int cnt = 0 , tmp = n;
	while(tmp > 1)
	{
		tmp /= 2;
		cnt++;
	}
	return cnt;
}
bool all0()
{
	for(int i = 1 ; i <= n ; i++)
	{
		if(b[i])
		{
			return 0;
		}
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i];
	}
	k = makek();
	for(int i = k - 1 ; i >= 0 ; i--)
	{
		for(int j = 1 ; j <= n ; j++)
		{
			b[j] = a[j] ^ a[(j + (1 << i) - 1) % n + 1];
		}
		if(all0())
		{
			continue;
		}
		ans += (1 << i);
		for(int j = 1 ; j <= n ; j++)
		{
			a[j] = b[j];
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		b[i] = a[i];
	}
	if(all0())
	{
		cout << ans;
	}
	else
	{
		cout << ans + 1;
	}
	return 0;
}
```

---

## 作者：_HCl_ (赞：1)

比较水的 F 题。感觉本场 E 题比这题要复杂很多。

# CF1848F 题解

**题意简述**

给定长度为 $n$ 的数组 $a$，每次操作可以将所有的 $a_i$ 变为 $a_i\oplus a_{i+1}$。特别地，$a_{n-1}$ 变为 $a_{n-1}\oplus a_0$。

求出要经过几次操作可以使所有数都变成 $0$。

**思路引导**

定义 $f_{k,i}$ 为经过 $k$ 次操作后 $a_i$ 的值。其中 $f_0=a$，$f_{k,i}=f_{k-1,i}\oplus f_{k-1,i+1}$。

然后递推地考察 $f_k$。我们有 $f_{1,i}=a_i\oplus a_{i+1}$，$f_{2,i}=f_{1,i}\oplus f_{1,i+1}=(a_i\oplus a_{i+1})\oplus(a_{i+1}\oplus a_{i+2})=a_i\oplus a_{i+2}$。

同理递推，不难发现 $f_{2^t,i}=a_{i}\oplus a_{i+2^t}$。那么经过 $n$ 次操作后，$f_{n,i}=a_{i}\oplus a_{i+n}=0$。所以一定有解，~~那个让我们判断无解就是纯诈骗~~。

然后就可以就可以递归+倍增地去做。如果当前数组长度是 $len$，那么就进行 $\frac{len}{2}$ 次操作，就可以将左半边和右半边变成一样的。然后递归下去，长度减半后的数组。直到长度减半为 $1$。另外还要注意，如果左边和右边已经一样了，就不用再进行操作了，直接递归即可。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[50000001];
int solve(int len){
	if(len==1){
		if(a[0])return 1;//a[0]>0，再进行一次操作
		return 0;
	}
	int flag=0,half=len>>1;
	for(int i=0;i<half;++i)
		if(a[i]!=a[i+half]){
			flag=1;
			break;
		}
	if(!flag)return solve(half);//左右已经一样了
	for(int i=0;i<half;++i)
		a[i]^=a[i+half];
	return half+solve(half); //长度减半，递归下去
}
int main(){
	cin>>n;
	for(int i=0;i<n;++i)scanf("%d",a+i);
	cout<<solve(n);
} 
```

---

## 作者：jasonliujiahua (赞：1)

# CF1848F

[题目传送门](https://www.luogu.com.cn/problem/CF1848F)
## 题意简述：
给定长度为 $n$ 的数组 $a$，每次将所有的 $a_i$ 变化为 $a_i \oplus a_{i+1}$，特别的，对于 $a_{n-1}$，其变化为 $a_{n-1} \oplus a_0$。求经过几次变化能使数组 $a$ 都变化为 $0$，如果永远无法将 $a$ 都变化为 $0$ 则输出 $-1$。(此处 $\oplus$ 指异或，数组下标 $i$ 由 $0$ 开始)。
## 题目分析：
### Step 1：推导
设 $b_{i,j}$ 表示 $a_i$ 经过 $j$ 次变换得到的答案，显然：
$$b_{i,j}=b_{i,j-1} \oplus b_{i+1,j-1}$$
将上式运用在自己身上，可得：
$$b_{i,j}=(b_{i,j-2} \oplus b_{i+1,j-2}) \oplus (b_{i+1,j-2} \oplus b_{i+2,j-2})$$

$$∴b_{i,j}=b_{i,j-2} \oplus (b_{i+1,j-2} \oplus b_{i+1,j-2}) \oplus b_{i+2,j-2}$$

$$∴b_{i,j}=b_{i,j-2} \oplus  b_{i+2,j-2}$$

再将上式运用在自己身上，可得：
$$b_{i,j}=(b_{i,j-4} \oplus b_{i+2,j-4}) \oplus (b_{i+2,j-4} \oplus b_{i+4,j-4})$$

$$∴b_{i,j}=b_{i,j-4} \oplus (b_{i+2,j-4} \oplus b_{i+2,j-4}) \oplus b_{i+4,j-4}$$

$$∴b_{i,j}=b_{i,j-4} \oplus  b_{i+4,j-4}$$

以此类推，对 $j \ge 2^k$ 可得：
$$b_{i,j}=b_{i,j-2^k} \oplus  b_{id(i+2^k),j-2^k}$$

### Step 2：倍增
由于本题的两个操作前后之间除了数变了之外并无关联，因此可以将答案拆成二进制，倍增寻找答案即可。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e6+10;
int n,ans,a[maxn],b[maxn];
bool dp[maxn][21];
void init()
{
    cin>>n;
    int tmp=0;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),tmp+=(a[i]==0);
    if(tmp==n)
    {
        putchar('0');
        exit(0);
    }
}
inline int nxt(int i,int j)
{
    int x=i+(1<<j),y=x%n;
    if(!y) return n;
    return y;
}
void work()
{
    int x=log2(n);
    for(int j=x;j>=0;j--)
    {
        int res=0;
        for(int i=1;i<=n;i++)
        {
            b[i]=(a[i]^a[nxt(i,j)]);
            if(b[i]==0) res++; 
        }
        if(res<n) 
        {
            ans+=(1<<j);
            for(int i=1;i<=n;i++) a[i]=b[i];
        }
    }
    printf("%lld",ans+1);
}
signed main()
{
    init();
    work();
    return 0;
}
```

---

## 作者：2022dyx (赞：0)

通过这个 $n=2^k$ 的性质不难想到倍增维护。下面下标全部在模 $n$ 意义下讨论，我们设 $f_{i,j}$ 为 $i$ 位置在 $2^j$ 轮后的值，手玩后有性质 $f_{i,j}=a_i\oplus a_{i+2^j}$，归纳证明显然。

由于在成为全 $0$ 序列后再操作无法使之脱离全 $0$ 序列，也就是说合法的操作数是连续的，因此可以直接倍增跳，判断是否是全 $0$ 序列即可。

复杂度 $O(n\log n)$。

下面是代码。
```
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define file(x) freopen(#x ".in", "r", stdin); freopen(#x ".out", "w", stdout);
using namespace std;
constexpr int N = 11e5 + 5;
int n, a[N], tmp[N], ans;
bool chk;
signed main() {
    cin.tie(0) -> sync_with_stdio(false); 
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i], chk |= a[i];
    if (!chk) { cout << 0; return 0; }
    for (int i = n; i >= 1; i >>= 1) {
        for (int j = 0; j < n; ++j) tmp[j] = a[j] ^ a[(j + i) % n];
        bool flg = false;
        for (int j = 0; j < n; ++j) flg |= tmp[j];
        if (!flg) continue;
        for (int j = 0; j < n; ++j) a[j] = tmp[j];
        ans += i;
    }
    cout << ans + 1;
}
```

---

## 作者：MSqwq (赞：0)

第一次赛时过 F，很激动。  
就是先拆位，然后按位二分，第 $2^k$ 次操作是 $a_i \oplus a_{i+2^k}$ 有点像 fwt 那样，其实写出来就是 fwt，但是少了层循环，然后就可以得到一个 $O(n\log^2)$ 的做法，赛时是这样做的。  
赛后听了@[泷泽三月](https://www.luogu.com.cn/user/115936) 说，可以把二分改成从大到小按位不归零的情况下最多次数，从大到小枚举 $k$ 然后就可以单 $\log$ 了，好智慧。  
然后你就会发现，无论怎样下一层都只需要考虑一边，就是如果上一层全是 $0$，那说明两半是完全对称的，如果不是，那变完就成一样的了，所以下一次只需要切一半判断就行，然后就可以得到超级无敌吊炸天的 $O(n)$ 做法，好有道理，好强大。  
最后奉上我最低贱的 $O(n\log^2)$ 代码：  
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

const int N=5e6+10;
int n,k;
int a[N],b[N];
bool check(int x)//fwt
{
	for(int i=0;i<n;i++)b[i]=b[n+i]=a[i];
	for(int j=k-1;j>=0;j--)
	{
		if((x&(1<<j))==0)continue;
		int len=1<<(j+1);
		for(int i=0;i<(n<<1);i+=len)
		{
			for(int now=i;now<(i+len/2);now++)
				b[now]^=b[now+(len/2)],b[now+(len/2)]=0;
		}
	}
	for(int i=0;i<n;i++)if(b[i])return false;
	return true;
}
void solve()
{
	n=read();k=0;int mx=0;
	while((1<<k)<n)k++;
	for(int i=0;i<n;i++)a[i]=read(),mx=max(mx,a[i]);
	if(mx==0){cout<<0<<endl;return;}
	int l=1,r=n-1,ans=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans<<endl;
}

signed main()
{
	int T=1;
	while(T--)solve();
	return 0;
}
```


---

## 作者：114514xxx (赞：0)

## 思路
设 $f_{i,j}$ 表示 $a_i$ 进行了 $j$ 次操作后得到的数。

可以注意到 $f_{i,0}=a_i$ 和 $f_{i,1}=f_{i,0} \oplus f_{i+1,0}$ 这两条基本事实。基于此可以推导到 $f_{i,k}=f_{i,0} \oplus f_{i+k,0}$。证明只需根据上述式子的递推性可得。

又有 $n=2^k$，所以在 $2^k$ 次操作后数组 $a$ 一定全为 $0$。综上所述可以用倍增的方法去解决此题即可（题目中的无解纯纯障眼法）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+25;
int n,a[N],g[N];
bool scan(){
    int ans=0;
    for(int i=0;i<n;i++)
        if(g[i])return 0;
    return 1;
}
signed main(){
    std::ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int tot=0;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(!a[i])++tot;
    }
    if(tot==n){
        cout<<0;
        return 0;
    }
    int k=log2(n)-1;
    int ans=0;
    while(k>=0){
        for(int i=0;i<n;i++)
            g[i]=a[i]^a[(i+(1<<k))%n];
        if(!scan()){
            ans=ans+(1<<k);
            for(int i=0;i<n;i++)
                a[i]=g[i];
        }
        k--;
    }
    cout<<ans+1;
}

```

---

