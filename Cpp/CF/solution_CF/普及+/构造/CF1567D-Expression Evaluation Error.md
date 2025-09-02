# Expression Evaluation Error

## 题目描述

On the board, Bob wrote $ n $ positive integers in [base](https://en.wikipedia.org/wiki/Positional_notation#Base_of_the_numeral_system) $ 10 $ with sum $ s $ (i. e. in decimal numeral system). Alice sees the board, but accidentally interprets the numbers on the board as base- $ 11 $ integers and adds them up (in base $ 11 $ ).

What numbers should Bob write on the board, so Alice's sum is as large as possible?

## 说明/提示

In the first test case, $ 70_{10} + 27_{10} = 97_{10} $ , and Alice's sum is $ $$$70_{11} + 27_{11} = 97_{11} = 9 \cdot 11 + 7 = 106_{10}. $ $  (Here  $ x\_b $  represents the number  $ x $  in base  $ b $ .) It can be shown that it is impossible for Alice to get a larger sum than  $ 106\_{10} $ .</p><p>In the second test case, Bob can only write a single number on the board, so he must write  $ 17 $ .</p><p>In the third test case,  $ 3\_{10} + 4\_{10} + 100\_{10} + 4\_{10} = 111\_{10} $ , and Alice's sum is  $ $ 3_{11} + 4_{11} + 100_{11} + 4_{11} = 110_{11} = 1 \cdot 11^2 + 1 \cdot 11 = 132_{10}. $ $  It can be shown that it is impossible for Alice to get a larger sum than  $ 132\_{10}$$$.

## 样例 #1

### 输入

```
6
97 2
17 1
111 4
100 2
10 9
999999 3```

### 输出

```
70 27 
17 
3 4 100 4
10 90
1 1 2 1 1 1 1 1 1 
999900 90 9```

# 题解

## 作者：清烛 (赞：10)

学习了一下 CF 的最短解，来此分享，和官方题解不太一样但是思路是相同的。

## Description
给定一个数 $s$，要求划分成 $n$ 个数 $n_1,\cdots n_s$，要求把这些数看成 $11$ 进制的然后按照 $11$ 进制加起来使得结果最大。构造方案。

## Solution

首先考虑按位贪心：让最高位最大是显然的，让其等于 $s$ 的最高位一定是最优的。然后我们会发现这个构造出的最大结果一定不会大于 $s$ 看成 $11$ 进制表示的结果。

最优的做法是尽量让 Alice 不要产生进位：将 $s$ 表示成 $10^k$ 之和，例如 $25$ 就可以被表示为 $10 + 10 + 1 + 1 + 1 + 1 + 1$。但是难免有划分数量多的时候，那么就从高位往低位贪，让高位尽量不要进位即可，使得高位尽量大。

所以从最高位往最低位依次划分即可。

## Implementation

```cpp
int main() {
    int T; read(T);
    while (T--) {
        int s, n, p; read(s), read(n);
        while (n--) {
            if (!n) print(s), putchar('\n');
            else print(p = pow(10, (int)log10(s - n))), putchar(' ');
            s -= p;
        }
    }
    return output(), 0;
}
```

---

## 作者：dottle (赞：5)

设 $s=\overline{A_0A_1A_2...A_k},s'=(\overline{A_0A_1A_2...A_k})_{11}$。那么所有可能的情况中 Alice 和最大为 $s'$。

若 $a$ 在加起来的时候在第 $x$ 位向第 $x+1$ 位产生了 $f_x$ 次进位，则最终的 Alice 和应当为 $s'-\sum_{x=0}^kf_x11^x$（因为本来是 $11^{x+1}$，但在 $a_i$ 中被分成了 $10$ 个 $11^x$）。因此我们要尽量避免进位，若不能避免则要进尽量低的位。

那我们可以这样分：对于前 $n-1$ 个 $a$，令其形如 $10^x$；对于 $a_n$，令 $a_n=s-\sum_{i=1}^{n-1}a_i$。若 $\sum_iA_i\ge n$ 那么我们可以很容易的用上述方法解决，否则我们可以将最低的第 $x$ 位拆成 $10$ 个 $x-1$ 位，即 `A[x]--,A[x-1]+=10；` 重复直到 $\sum_iA_i\ge n$ 即可。


---

## 作者：XL4453 (赞：1)

### 解题思路：

一个十进制数拆成若干个数在十一进制下做加法时，一旦进位就会导致后来的数减小，那么就考虑如何在尽量避免进位的情况下将所有的数拆下来。

首先，如果各位上的数值和比 $n$ 大，那么一定有一解使得最后的十一进制数和原十进制数相等，可以发现，这样做是可能取到的最大值。对于这一种情况，考虑将前 $n-1$ 个数拆成 $10^x$ 的形式，然后直接用原数减去拆出的数的总和即可。

否则就要考虑将一些数再次划分使得满足拆出 $n$ 个数的条件，由于高位拆数相比低位拆数影响大，所以考虑从低位往高位拆，直接从后往前减就可以了。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int T,num[100],n,len,a,ans,now,len2,aa,nn;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&a,&n);
		aa=a;
		len=ans=0;
		while(a){
			num[++len]=a%10;
			ans+=num[len];
			a/=10;
		}
		now=1;nn=n;
		if(ans<n){
			for(int i=2;i<=len&&ans<nn;){
				while(i==1||num[i]==0)i++;
				num[i-1]+=10;num[i]--;
				i--;nn-=9;
			}
		}
		ans=0;
		while(num[len]==0)len--;
		for(int i=1;i<len;i++)now*=10;
		len2=len;
		for(int i=1;i<=n-1;i++){
			while(num[len2]==0)len2--,now/=10;
			printf("%d ",now);
			num[len2]--;
			ans+=now;
		}
		printf("%d\n",aa-ans);
	}
	return 0;
}
```



---

## 作者：wmrqwq (赞：0)

duel 到的。

# 题目链接

[CF1567D](https://www.luogu.com.cn/problem/CF1567D)

# 解题思路

发现在越高的数位上，你获取的利益就会越大。

**因此你肯定是每次将尽可能多的数分到最高的数位上是最优的。**

但是你会发现，有可能你这样分数位后后面的数就分不到权值了，你只需要保证去掉当前分掉的权值之后，剩下可以分的权值不小于还剩下没分到的数字数量即可。

接下来我们考虑一种没有损耗权值的方式。

根据前面加粗的结论，你发现，对于前 $n - 1$ 个数字，你直接分最大的能分的 $10$ 的非负整数次幂是没有损耗的，最后一个数字直接把当前能用的都用了即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n,m;
ll ans[110];
void solve()
{
	_clear();
	cin>>n>>m;
	forr(i,m-1,1)
	{
		ll pw=1;
		while(n-pw>=i)
			pw*=10;
		pw/=10;
//		ll add=n-max(num,1ll);
		cout<<pw<<' ';//max(num,1ll)<<' ';
		n-=pw;//max(num,1ll);
	}
	cout<<n<<endl;
//	cout<<endl;
}
int main()
{
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1567D 题解



## 思路分析

考虑对 $\{a_i\}$ 在 $10$ 进制下求和的过程，假如我们在 $10$ 进制下产生了一个从 $k\to k+1$ 的进位，那么在 $11$ 进制下我们就把一个 $11^{k+1}$ 变成了 $10$ 个 $11^k$，相当于损失了一个 $11^k$，因此我们应该尽可能减少进位。

首先考虑对 $S$ 的每个位拆成若干个 $10^k$，每个 `1` 数码给到一个不同的 $a_i$ 上，这样可以尽可能覆盖更多的 $a_i$，如果此时我们覆盖的 $a_i$ 仍然不足 $n$ 个，那就从 $10^1$ 开始，从小到大对于每个 $k$ 拆成 $10$ 个 $10^{k-1}$ 分给若干还是 $0$ 的 $a_i$，如果某个时刻 $>0$ 的 $a_i$ 的数量超过 $n$ 就终止。

对于每次分拆找 $k$ 的过程，注意到这样的过程至多执行 $n$ 次，因此可以直接每次对所有数码对应的 $k$ 重新排序，然后找到最小的非 $0$ 的 $k$。

时间复杂度 $\Theta(n^2\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
inline void print(vector <int> vec) {
	vector <int> ans(n);
	for(int i=0;i<n;++i) ans[i]=b[vec[i]];
	for(int i=n;i<(int)vec.size();++i) {
		for(int j=0;j<n;++j) {
			if((ans[j]/b[vec[i]])%10!=9) {
				ans[j]+=b[vec[i]];
				break;
			}
		}
	}
	for(int i:ans) printf("%d ",i);
	puts("");
	return ;
}
inline void solve() {
	vector <int> ans;
	string sum;
	cin>>sum>>n; 
	int k=sum.size();
	for(int i=0;i<k;++i) {
		for(int j='1';j<=sum[i];++j) {
			ans.push_back(k-i-1);
		}
	}
	while((int)ans.size()<n) {
		sort(ans.begin(),ans.end());
		for(int i=0;i<(int)ans.size();++i) {
			if(ans[i]>0) {
				--ans[i];
				for(int j=1;j<=9;++j) ans.push_back(ans[i]);
				break;
			}
		}
	}
	print(ans);
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```



---

