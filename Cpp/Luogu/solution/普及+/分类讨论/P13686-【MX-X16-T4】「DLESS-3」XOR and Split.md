# 【MX-X16-T4】「DLESS-3」XOR and Split

## 题目描述

你有一个长度为 $n$ 的整数序列 $a_1, \ldots, a_n$，初始全为 $0$。你可以将其划分成任意段且每一段都非空，对每个下标 $i$（$1 \le i \le n$），若 $a_i$ 位于从左向右数的第 $j$ 段中，则我们令 $a_i=j$。

定义这个序列的权值为所有 $a_i$ 按位异或的值。

你需要求出所有对序列的划分中，权值最大的划分的权值。

## 说明/提示

**【样例解释 #1】**  

$n=2$ 的时候，可能得到的 $a$ 是 $[1,2]$；$n=3$ 的时候，可能得到的 $a$ 是 $[1,1,2]$；$n=7$ 的时候，可能得到的 $a$ 是 $[1,2,2,3,4,4,5]$。

**【数据范围】**

对于所有数据，保证 $1\le T\le 10^5$，$1\le n \le 10^{18}$。

各测试点特殊限制如下：

|  测试点编号  | $n\le$  | 特殊性质  |
|:-:|:-:|:-:|
| $1$  | $10$  | 无  |
| $2$  | $50$  | 无  |
| $3$  | $400$  | 无  |
| $4$  | $10^{18}$  | $n$ 为 $2$ 的非负整数次幂  |
| $5$  | $10^{18}$ | 无  |

## 样例 #1

### 输入

```
4
2
3
7
8```

### 输出

```
3
2
7
8```

## 样例 #2

### 输入

```
2
500000000000
100000000000000000```

### 输出

```
549755813887
144115188075855871```

# 题解

## 作者：紊莫 (赞：6)

出题人题解。

## Subtask 1

可以暴力枚举划分，然后按照题意判断，复杂度是 $\mathcal O(n2^n)$ 的。

## Subtask 2

可以采用 DP 的方式求解所有可能异或出的权值。

设 $f_{i,j,k}$ 表示前 $i$ 个位置，分出了 $j$ 段，当前异或和为 $k$ 是否可行。

转移枚举一下上一个位置即可。

时间复杂度是 $\mathcal O(n^4)$ 的。

## Subtask 3

此处提出一个观察，一个段的长度至多为 $2$，可以通过调整的方法来说明，若有一个段的长度 $>2$，将其中两个位置放到最后形成一个贡献为 $0$ 的段，答案不变。

所以上文的转移是 $\mathcal O(1)$ 的，时间复杂度是 $\mathcal O(n^3)$ 的。

## Subtask 4

$n=2^k$ 的时候，直接分出 $n$ 段，$n>2$ 答案就是 $1\oplus 2\oplus ...\oplus n = n$，$n=2$ 答案是 $3$。

## Subtask 5

我们说明，当 $n\ge 4$ 时，$n$ 是 $2^k$ 的时候，答案是 $n$，否则是第一个满足 $2^i>n$ 的 $2^i-1$。

$n=2^k$ 的时候已经在 Subtask4 说明，现在我将证明 $n$ 不是二的幂次时的答案。

首先答案上界一定不超过 $2^i-1$，因为可能的最高位也是小于 $2^i$ 的。

下面给出一种可能的方法达到这个上界：

先看 $n=2^k+1$ 的情况，我们知道 $1\oplus 2\oplus ...\oplus (2^k-1)$ 是 $0$，所以可以这样构造：前 $2^k-2$ 段，每段长度是 $1$，然后一段长度是 $2$，最后一段长度是 $1$。

比如 $n=17$ 的时候，方案就是 ``1 2 3... 14 15 15 16``。

这样就得到了 $2^k\oplus (2^k-1) = 2^{k+1}-1$。

然后和 $2^k+1$ 奇偶性相同的 $n$ 也是容易的，可以在后面加入两个元素构成的无用段。

再看 $2^k+2$ 的情况，我们把多一个的 $2^k-1$ 换成 $2^{k-1}$ 和 $2^{k-1}-1$，效果相同。

该做法在 $n$ 较小的时候没有足够的元素用来调整，所以特判 $n\le 4$ 即可。

时间复杂度 $\mathcal O(1)$，期望得分 $100$。

---

## 作者：Vct14 (赞：4)

下文中“位”均指二进制位。

$n\le10^{18}$，考虑 $O(1)$ 做法。

可以发现答案上界为 $2^{\lfloor\log_2n\rfloor+1}-1$，因为最多只有 $\lfloor\log_2n\rfloor+1$ 位。

考虑能否通过构造达到这个值。

当 $n$ 为 $2$ 的非负整数次幂时，设 $\log_2 n=k\ge0$，可以发现只有取到 $n$ 段的时候，权值 $\oplus_{i=1}^n i=\begin{cases}3&k=1\\n&k\ne1\end{cases}$ 最大，因为它有 $k+1$ 位；如果取 $x<n$ 段，那么权值最大为 $n-1$，因为最多只有 $k$ 位。

当 $n$ 不为 $2$ 的非负整数次幂时，先特判 $n=3$ 时答案为 $2$（$1\oplus 1\oplus2=2$ 最大）。下面考虑 $n\ge5$ 即 $\lfloor\log_2n\rfloor\ge2$ 的情况。注意到 $\oplus_{i=1}^{2^{\lfloor\log_2n\rfloor}-2}i=2^{\lfloor\log_2n\rfloor}-1$（首尾配对很容易得到），又有 $(2^{\lfloor\log_2n\rfloor}-1)\oplus2^{\lfloor\log_2n\rfloor}=2^{\lfloor\log_2n\rfloor+1}-1$，所以有 $(\oplus_{i=1}^{2^{\lfloor\log_2n\rfloor}-2}i)\oplus2^{\lfloor\log_2n\rfloor}=2^{\lfloor\log_2n\rfloor+1}-1$。此时通过这 $2^{\lfloor\log_2n\rfloor}-1$ 个数的构造我们已经取到了上界。我们要让剩下的 $n-2^{\lfloor\log_2n\rfloor}+1$ 个数的异或和为 $0$。

为了分出 $2^{\lfloor\log_2n\rfloor}$ 段，我们一定会异或若干个 $2^{\lfloor\log_2n\rfloor}-1$。注意到 $(2^{\lfloor\log_2n\rfloor}-1)\oplus (2^{\lfloor\log_2n\rfloor}-1)=0$。也就是说，如果 $n-2^{\lfloor\log_2n\rfloor}+1$ 为偶数，那么我们直接取 $n-2^{\lfloor\log_2n\rfloor}+1$ 个 $2^{\lfloor\log_2n\rfloor}-1$ 即可；若 $n-2^{\lfloor\log_2n\rfloor}+1$ 为奇数，注意到 $1\oplus2\oplus3=0$，我们取 $n-2^{\lfloor\log_2n\rfloor}-2$（偶数）个 $2^{\lfloor\log_2n\rfloor}-1$，再取 $1,2,3$ 即可。

综上，当 $n$ 为 $2$ 的非负整数次幂时，答案为 $n$，否则为 $2^{\lfloor\log_2n\rfloor+1}-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		long long n;cin>>n;
        if(n==2) puts("3");
        else if(n==3) puts("2");
        else{
            long long s=1;while(s*2<=n) s*=2;
    		if(s==n) cout<<n<<"\n";
    		else cout<<2*s-1<<"\n";
        }
	}
	return 0;
}
```

---

## 作者：xingkong1 (赞：4)

## 思路
我先枚举出了 $n$ 是10以内时的所有答案，从 $1$ 到 $10$ 的答案分别是 ${1,3,2,4,7,7,7,8,15,15}$。我们可以发现，除了 $2$ 和 $3$ 这两个特殊情况外，若 $n$ 是 $2$ 的正整数次方，答案就是 $n$，否则答案就是第一个大于 $n$ 的 $2$ 的正整数次方**减 $1$**。由此可直接出答案。

## code
```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define cfs cout << fixed << setprecision
#define ll unsigned long long
#define int long long
//#define int __int128
#define endl '\n'
using namespace std;
signed main(void)
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	IO
	int T;
	cin >> T;
	while(T--)
	{
		int n;
		cin >> n;
		if(n==3)
		{
			cout << 2 << endl;//特判
			continue;
		}
    if(n==2)
		{
			cout << 3 << endl;
			continue;
		}
		int ans=1;
		for(int i=1;i<=n;i++)
		{
			ans*=2;
			if(ans>n)//若大于，输出第一个大于他的2的次方减1
			{
				cout << ans-1 << endl;
				break;
			}
			else if(ans==n)//若n是2的正整数次方，输出n
			{
				cout << ans << endl;
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：Null_h (赞：2)

## 前言

看到一个很像构造的东西就害怕了，其实挺简单？

## 思路

转换一下角度，实际上就是所有 $n$ 个数异或，你可以选择将最大的 $k$ 个移除，同时获得 $k$ 次添加数的机会，添加的数不能超过当前的最大数。

那么发现当 $n$ 为 2 的次幂的时候，为了保留最大的一位，一个数都不可以删，可以直接求出答案，为其本身。

如果不是，那么有个显然的上界，考虑 $n$ 的二进制表示，因为异或对每个位是独立的，所以超过其最高位的位是不可能产生变化的，于是尝试构造这个二进制下全为 1 的答案。因为不是 2 的次幂，所以去掉 $n$ 不会影响最高位，然后获得了一次添加数的机会，一定可以将答案构造为这个上界。

发现数据很小的时候会有些边界情况，判掉即可，出题人很良心的放在了样例里。

然后位运算可以让我们的代码美观很多。

推荐一下判断 $n$ 是否为 2 的次幂的位运算写法，非常简洁。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while (T--) {
		int x;
		cin>>x;
		if(!(x&(x-1))){
			if(x==2){
				cout<<3<<'\n';
			}else cout<<x<<'\n';
		} else {
			if (x==3){
				cout<<2<<'\n';
			}else{
                x|=(x>>1);
                x|=(x>>2);
                x|=(x>>4);
                x|=(x>>8);
                x|=(x>>16);
                x|=(x>>32);
                cout<<x<<'\n';
            }
		}
	}
	return 0;
}
```

---

## 作者：ylch (赞：1)

首先写一个爆搜暴力跑一遍打个表，就会发现答案其实很有规律。

设 $k$ 为满足 $2^k \leq n$ 的最大整数（即 $k = \lfloor \log_2 n \rfloor$ 对应的 $2^k$）：

- 若 $n$ 是 $2$ 的幂（即 $n = 2^k$），则答案为 $n$。
- 否则，答案为 $2^{k+1} - 1$（即大于 $n$ 的最小 $2$ 的幂减 $1$）。

## 证明

1. **证明上界**：序列每一段的标记都是不超过 $n$ 的正整数，所以异或和的二进制位数不超过 $\lfloor \log_2 n \rfloor + 1$ 位，设 $t = 2^{k+1}$ 为大于 $n$ 的最小 $2$ 的幂，则异或和不可能超过 $t - 1$（即二进制下 $k+1$ 位全 $1$）。

2. **构造性证明**：对于任意 $n \geq 4$，构造一种划分方案，使异或和达到上界 $t - 1$：

   - **Case 1**：$n=2^k(k \ge 2) \\$
     将序列划分为 $n$ 段，分别标记为 $1,2,\dots,n$。此时异或和为 $\bigoplus_{i=1}^{n} i = n$（因为 $n=2^k$ 时，前 $n$ 个连续正整数的异或和为 $n$）。
   - **Case 2**：$n \neq 2^k \\$
     构造方法：
     + 对前 $2^{k}-2$ 个位置：每段一个元素，标记为 $1,2,\dots,2^k-2$，异或和记为 $S_1=2^k-1$。$\\$
     + 随后两个位置：作为一段，标记为 $2^k-1$，异或和为 $0$。（因为 $a \oplus a=0$）$\\$
     + 下一个位置：作为一段，标记为 $2^k$，异或和为 $2^k$。$\\$
     + 剩余位置：每两个相邻位置成对作为一段（标记递增），每段的异或和为 $0$。

     总异或和：$S = S_1 \oplus 0 \oplus 2^k = (2^{k}-1) \oplus 2^k = 2^{k+1} - 1$。

     > 这样构造的原因：要想两数异或后二进制上全为 $1$，在题干要求**大小连续**的情况下，可以用一个只有最高位二进制为 $1$ 的数异或一个只有最高位二进制为 $0$（其余低位为 $1$）的数，这样就能得到一个二进制位全 $1$ 的答案。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve()
{
	ll n; cin >> n;
	if(n < 4){ // 特判
		cout << (map<int,int>{{1,1}, {2,3}, {3,2}})[n] << '\n';
	}
	else if((n & (n - 1)) == 0) cout << n << '\n'; // n=2^k
	else{
		ll k = 1; // 计算大于n的最小的2^k
		while(k < n) k <<= 1;
		cout << k - 1 << '\n';
	}
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T; cin >> T;
	while(T --) solve();
	return 0;
}
```

---

## 作者：Dollartree (赞：1)

### 解题思路

1. 首先可以发现，当 $n=2^{k}$ 时，答案最大为 $n$，因为更大位数需要更大的长度，可以分成 $n$ 段使得第 $m$ 位上为 $1$ 的数有 $\frac{n}{2^{m}}$ 个，发现第 $1$ 位至第 $k-1$ 位都有偶数个，被异或消掉了，而第 $k$ 位只有一个，所以 $n=2^{k}$ 时答案为 $n$。

2. 当 $n$ 不是 $2$ 的非负整数次幂时，需要分情况考虑。$n$ 为奇数时，可以在 $n$ 为 $2$ 的非负整数次幂的基础上，异或 $n-2^{k}$ 个 $2^{k}-1$，其中 $k$ 是最大的整数使得 $2^{k} < n$，从第一条的结论可以看出答案为 $2^{k}$ 异或 $n-2^{k}$ 个 $2^{k}-1$，因为奇数减偶数等于奇数，奇数个 $2^{k}-1$ 被异或消成 $2^{k}-1$，最终答案是 $2^{k+1}-1$。

3. $n$ 为偶数时，可以将 $2^{k}-1$ 拆分，拆成 $2^{k-1}-1$ 和 $2^{k-1}$，其他与第二条同理。

### 注意事项
1. 要开 longlong。

2. 手动模拟 log，否则容易爆精度。

3. 根据样例可知 $3$ 以内的数要特判。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long//开longlong
using namespace std;
void solve()
{
    long long n;
    cin>>n;
    int cnt=0;
    long long n1=n-1;
    while(n1)//模拟log2
    {
    	n1/=2;
    	++cnt;
	}
//	cout<<cnt<<"\n";
	long long temp=cnt;
//    long long temp=(long long)ceil(log2(n));
    if(n==1)//特判123
    {
    	cout<<1<<"\n";
    	return;
	}
	if(n==2)
	{
		cout<<3<<"\n";
		return;
	}
	if(n==3)
	{
		cout<<2<<"\n";
		return;
	}
    if((1LL<<temp)==n)
    {
    	cout<<n<<"\n";
    	return;
	}
//    if((1LL<<temp)+1==n)
//    {
//    	cout<<n<<"\n";
//    	return;
//	}
    cout<<(1LL<<(long long)temp)-1<<"\n";
}
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}
```

---

## 作者：cfkk (赞：0)

很好的思维题。

首先，在 $n\le3$ 时，直接特判。

然后我们要知道两个式子：
- $\oplus_{i=1}^{2^k-1} i=0$
- $2^k\oplus(2^k-1)=2^{k+1}-1$

接下来我们讨论 $n>3$ 的情况：

- 当 $n=2^k(k\in \mathbb{N})$ 时：显然每段长度为 $1$ 是异或和最大，最大值为 $n$。
- 当 $n=2^k-1+x$ 且 $x\equiv 0\pmod 2$：根据以上两个式子，我们可以把前 $2^k-1$ 个元素的长度划为 $1$，然后放 $x-2$ 个 $2^k-1$，这样前面所有的元素异或和为 $0$，这时插入 $2^k-1$ 和 $2^k$ 就可以达到最大值。
- 当 $n=2^k-1+x$ 且 $x\equiv 1\pmod 2$：和上种情况同理，多插个 $1$ 就可以了。

主要代码：
```
void solve()
{
	int n=read();
	if(n==1){puts("1");return;}
	if(n==2){puts("3");return;}
	if(n==3){puts("2");return;}
	if(qpow(2,log2(n),inf)==n)print(n),puts("");
	else print(qpow(2,log2(n)+1,inf)-1),puts("");
}
signed main()
{
	int T=read();
	while(T--)solve();
    return 0;
}
```

---

## 作者：Tiger_Rory (赞：0)

约定：本题解中的所有数的二进制下表示均忽略前导零。

我们发现求最大权值最重要的是保证其二进制下位数尽可能多。考虑从特殊性质入手求解。

若数列长度 $n$ 可以表示为 $2^p$（$p$ 为非负整数），则将数列分为 $2^p$ 段时，它的最大权值刚好为 $2^p(n\ne2)$ 或 $3(n=2)$。因为此时它的最大权值的二进制下后 $p$ 位都被异或成零了，$n=2$ 时除外。如果分的段数不足 $2^p$，则由 $\operatorname{xor}$ 运算不进位的性质得知该答案一定不优。

那如果是一般情况呢？我们又发现数列长度 $n$ 一定可以表示为 $2^p+k(k<2^p)$ 的形式，此时分 $2^p$ 段是最优的，因为此时最大权值二进制下最多只能有 $p+1$ 位。而我们可以用 $k$ 次操作通过增加 $1\sim2^p-1$ 之间的若干数的数量将 $2^p$ 二进制下的后 $p$ 位改为 $1$，这样最终答案就是 $2^{p+1}-1$。求出 $p$ 就好了。此时需要特判 $n=3$ 时的情况。

下面是参考代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;  
ll n;
void Solve() {
	cin >> n; 
    if(n == 1) {
        cout << 1 << '\n'; 
        return; 
    }
    if(n == 2) {
        cout << 3 << '\n'; 
        return; 
    }
    if(n == 3) {
    	cout << 2 << '\n'; 
    	return; 
	}
    int p = 0; 
	for(int i = 0; i <= 63; i++) { 
        if((1ll << i) == n) {
            cout << (1ll << i) << '\n'; 
            return; 
        }
        if((1ll << i) > n) {
            p = i - 1; 
            break; 
        }
    } 
	cout << 1ll * (1ll << (p + 1)) - 1 << '\n'; 
    return; 
} 
signed main(){
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0); 
	int T; cin >> T; while(T--) Solve(); 
	return 0;
}

```

---

