# 【MX-X16-T3】「DLESS-3」XOR and Impossible Problem

## 题目描述

给定长度为 $n$ 的非负整数序列 $a_1, \ldots, a_n$，求：

$$\prod_{i=1}^n\prod_{j=i+1}^n(a_i\oplus a_j)$$

其中 $\oplus$ 表示按位异或运算。

答案对 $2^{64}$ 取模。

## 说明/提示

**【样例解释】**

对于第一组数据，答案为 $a_1\oplus a_2=1\oplus 1=0$；

对于第二组数据，答案为 $(a_1\oplus a_2)\times (a_1\oplus a_3)\times (a_2\oplus a_3)=(1\oplus 2)\times(1\oplus 3)\times(2\oplus 3)=6$。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\le T\le 10^5$，$2\le n,\sum n\le 10^6$，$0\le a_i<2^{64}$。

各子任务特殊限制如下：

|子任务编号|$\sum n\le$|$a_i<$|分值|
|:-:|:-:|:-:|:-:|
|$1$|$5000$|$2^{64}$|$12$|
|$2$|$10^6$|$2^5$|$32$|
|$3$|$10^6$|$2^{64}$|$56$|



## 样例 #1

### 输入

```
4
2
1 1
3
1 2 3
5
1 4 5 2 6
13
1 2 3 4 5 6 7 8 9 10 11 12 13```

### 输出

```
0
6
423360
8286623314361712640```

# 题解

## 作者：luogu_gza (赞：10)

我们令集合 $A=\{a_i|1 \leq i \leq n \land a_i \bmod 2=1\}$，$B=\{a_i|1 \leq i \leq n \land a_i \bmod 2=0\}$。

显然 $A$ 中任意两个数异或值一定是 $2$ 的倍数，$B$ 中任意两个数异或值也一定是 $2$ 的倍数，因此答案至少是 $2^{\frac{|A|(|A|-1)}{2}+\frac{|B|(|B|-1)}{2}} \geq 2^{\lfloor \frac n2 \rfloor(\lfloor \frac n2 \rfloor- 1)}$ 的倍数，因此在 $n \geq 70$（这个界很松我乱取的）的时候直接输出 $0$，其他时候跑暴力就行了。

核心代码：

```cpp
const int N=1e6+10;
int n;
int a[N];
void solve()
{
  n=R;
  fo(i,1,n) a[i]=R;
  if(n>=70) puts("0");
  else
  {
    unsigned int ans=1;
    fo(i,1,n) fo(j,i+1,n) ans*=(a[i]^a[j]);
    write(ans),puts("");
  }
}
void main(){
  MT solve();
}
```

---

## 作者：Vct14 (赞：2)

对 $2^{64}$ 取模即 `unsigned long long` 自然溢出。

直接计算单组数据是 $O(n^2)$ 的，显然无法通过。

我们发现任意一组同奇偶的数异或起来一定是 $2$ 的倍数，所以只要有 $64$ 组同奇偶的数答案一定为 $0$。

由 $x$ 个同奇偶的数可以凑出 $\dfrac{x(x-1)}2$ 组，计算得到 $x_{\min}=12$，即只要 $a$ 中有 $12$ 个同奇偶的数，那么答案为 $0$。判断一下即可。

判完后我们发现，此时 $n$ 最大为 $11+11=22$。此时可以暴力计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N=1e6+2;
ull a[N];

int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;int odd=0;
		for(int i=1; i<=n; i++){
			cin>>a[i];
			if(a[i]%2) odd++;
		}
		if(odd>=12 || n-odd>=12){
			puts("0");
			continue;
		} // max n =22
		ull ans=1;
		for(int i=1; i<=n; i++) for(int j=i+1; j<=n; j++) ans*=a[i]^a[j];
		cout<<ans<<"\n";
	} 
	return 0;
}
```

---

## 作者：qz1zzmx (赞：2)

# Subtask 1

暴力计算 $\prod\limits_{i=1}\limits^{n}{\prod\limits_{j=i+1}\limits^{n}{(a_i \operatorname{xor} a_j)}}$ 即可

时间复杂度 $O(n^2)$

期望得分 $12$ 分

# Subtask 2

首先我们考虑当一个奇数异或上一个偶数时会发生什么

不难发现答案的末位为 $0$，即答案为 $2$ 的倍数

所以只要有大于 $64$ 个的 $2$ 的倍数相乘，那这个答案在对 $2^{64}$ 取模后的答案即为 $0$

而在确保有 $64$ 对奇数和偶数异或的条件下，最坏情况即为有 $1$ 个奇数和 $64$ 个偶数或有 $64$ 个奇数和 $1$ 个偶数，此时 $n=65$，所以如果 $n \ge 65$，直接输出 $0$ 即可，而对于 $n < 65$，暴力枚举即可

代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define endl '\n'
using namespace std;
int read();
int t,n,a[1000010];
void solve() {
	int ans=1;
	n=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
	}
	if(n>=65) {
		cout<<0<<endl;
		return;
	}
	for(int i=1;i<=n;i++) {
		for(int j=i+1;j<=n;j++) {
			ans=ans*(a[i] xor a[j]);
		}
	}
	cout<<ans<<endl;
}
signed main(){
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	t=read();
	while(t--) {
		solve();
	}
    return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```

---

## 作者：LTTXiaochuan (赞：2)

**题目大意**：求 $\displaystyle \prod_{i=1}^{n-1} \prod_{j=i+1}^n(a_i \oplus a_j) \bmod 2^{64}$.

~~诈骗，妥妥的诈骗！！！~~

反复尝试展开化简操作，发现无从下手，转而开始分析式子的本质。

观察模数，发现如果乘项中含有超过 $64$ 个的 $2$ 因子，就会导致答案变为 $0$，于是考虑分析乘项关于 $2$ 的幂次。



### Part.1 下界

考虑分析序列 $a$ 的奇偶性，如果全为偶数，那肯定再好不过了，很快就能达到要求。如果全为奇数呢？那也再好不过了，因为奇数的异或和为偶数。那如果有奇有偶呢？最坏情况是一半奇数一半偶数，设奇数和偶数各有 $x$ 个，容易发现一个数会在一半的乘项当中出现，也就是一个乘项中出现两个偶数的概率为 $\frac{1}{4}$，出现两个奇数的概率也为 $\frac{1}{4}$，也就是有一半的乘项都含有 $2$ 这个因子。

于是解不等式
$$
\frac{n(n-1)}{4}\geq64
$$
得到整数解 $n=17$，但是我们一开始假设有一半奇数一半偶数，也就是项数为偶数，于是取 $n=18$。

这就意味着，对于任意 $n\geq 18$，答案都为 $0$，$n<18$ 时直接算即可。



这就结束了吗？

如果进一步分析，我们会发现，这样还是太保守了——有一些乘项的贡献可能不止 $1$ 个 $2$。接下来我们将分析一个更紧的下界：$n\geq14$.



### Part.2 紧下界

我们设所有乘项的 $2$ 的次幂和为 $T$。

首先，我们把形如 $(a_i\oplus a_j)$ 的数对 $(a_i,a_j)$ 分类，分类依据为其对总次幂 $T$ 作出的贡献。对 $T$ 作出 $k$ 的贡献时，说明 $(a_i\oplus a_j)$ 含有 $2^k$ 这个因子，或者说，$a_i$ 和 $a_j$ 的最低的 $k$ 位是相同的。

如果我们对从 $1$ 开始的所有的符合 $k$ 的数对都做一遍统计，$k>1$ 的数对就会被重复统计很多遍，此时我们需要将每次统计所得的贡献设为 $1$。对于一个给定的 $k$，我们设所有由这个 $k$ 给出的贡献为 $c_k$，那么 $T=\sum_{k=1}^∞ c_k$.

我们还没有确定 $a_i$ 是哪些数，但是——为了求得紧下界，对于给定的 $n$ 我们需要让 $T$ 尽可能小，也就是要让每个 $c_k$ 都尽可能小。

那么，对于一个给定的 $k$，为了得到满足条件的数对的数量，我们可以先对数分类，也就是根据最低 $k$ 位对 $a_i$ 进行分类（最低 $k$ 位相同的 $a_i$ 分到同一类），至多能分出 $2^k$ 类。对于每一类，从里面任选 $2$ 个数组成的数对都是符合条件的。设 $m=2^k$，第 $i$ 类中有 $p_i$ 个数的话，则有 $c_k=\sum_{i=1}^m \binom{p_i}{2}$ 个数对满足要求。

那么如何令 $c_k$ 尽可能小呢？只要想办法构造序列 $a$，使得每类的数都尽可能一样，因为组合数函数显然是凹函数，对每个类当然是越少越好。将 $n$ 个元素分到 $m$ 个桶中，我们令 $n=qm+r$ $(0\leq r <m)$，然后令 $r$ 个类包含 $(q+1)$ 个数，其余 $(m-r)$ 个类包含 $q$ 个数即可。那么，此时有
$$
c_k=r\binom{q+1}{2}+(m-r)\binom{q}{2}=m\binom{q}{2}+rq
$$
这便是最小的 $c_k$。

最终地，我们得到了 $T_{\min}$ 的计算公式：（其中有 $n=qm+r$）
$$
T_{\min}=\sum_{k=1}^∞ c_k=\sum_{k=1}^∞ \left(m\binom{q}{2}+rq \right)
$$
啊对了，别看它有个 $∞$，由于 $k$ 大了以后 $m=2^k$ 就大了，足够大时 $q=0$ 即 $c_k$ 为 $0$，这个式子显然是收敛的，所以能算。

由此公式代入 $n=13$ 计算得 $T_{\min}=56$，代入 $n=14$ 得 $T_{\min}=66$，由 $66>64$ 得到我们最终的紧下界！



### Part.3 结语喵

虽然算出紧下界对时间复杂度几乎没有影响，但是这么做对于深入理解题目还是有很大帮助的喵。觉得这篇题解不错的话别忘了点赞喵~！有需要改进的地方也可以留言或私信喵！谢谢喵~




```c++
#include <bits/stdc++.h>
using namespace std;

const int N=1e6+10;

typedef unsigned long long ull;

ull a[N];

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        for(int i=1; i<=n; i++) cin>>a[i];

        ull ans=0;
        if(n<=13)
        {
            ans=1;
            for(int i=1; i<=n; i++)
                for(int j=i+1; j<=n; j++)
                    ans*=(a[i]^a[j]);
        }
        cout<<ans<<"\n";
    }

    return 0;
}
```

---

## 作者：__CJY__ (赞：2)

玄学！
## 思路
直接暴力即可，但需要一点剪枝。时间复杂度 $\Theta(n^2)$，但其实不足 $n^2$ 次，在 $2$ 秒内可以跑过（实际半秒都不用）！

需要注意的是，模数为 $2^{64}$，爆了 `unsigned long long`，所以我们可用使用 `unsigned long long` 自然溢出的特性。例如，$2^{64} \bmod 2^{64}=0,(2^{64}+1) \bmod 2^{64}=1$，结果和自然溢出一致。

我们每次让 $res \gets res \times (a_i \oplus a_j)$，若 $a_i=a_j$，即 $a_i \oplus a_j=0$，那么 $\prod\limits_{i=1}^n\prod\limits_{j=i+1}^n(a_i \oplus a_j)=0$，直接退出即可，可以省不少时间呢。
## Code
```cpp lines=2-2,12-12
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn=1e6+5;
ull T,a[maxn],n,res;
void solve(){
	cin>>n,res=1;
	for(ull i=1;i<=n;i++) cin>>a[i];
	for(ull i=1;i<=n;i++){
		for(ull j=i+1;j<=n;j++){
			res*=(a[i]^a[j]);
			if(!res){cout<<"0\n";return;}//不加 TLE
		}
	}
	cout<<res<<'\n';
}
int main(){
	cin>>T;
	while(T--) solve();
}
```
:::warning[警告]{open}
**十年 OI 一场空，不开 `unsigned long long` 见祖宗！**

---

## 作者：ChampionCyan (赞：2)

本题直接求值极不容易，因为 $O(N^2)$ 的代码是难以接受的。

但是发现答案对 $2^{64}$ 取模，这是一个突破口。

考虑到取模 $2$ 余数为 $1$ 的数两两异或均为 $2$ 的倍数，取模 $2$ 余数为 $0$ 的数两两异或也均为 $2$ 的倍数。所以它们相乘必然**大致**（没必要太精确，不影响结论）会是 $O(2^N)$，所以 $N$ 只要很大，就输出 $0$，或者用 `unsigned long long` 让答案自然溢出，出现 $0$ 直接跳出循环。

代码：
```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
ll a[1000001], ans;

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ans = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            ans *= (a[i] ^ a[j]);
            if (ans == 0)
                goto out;
        }
    out:;
    cout << ans << '\n';
}

int main() {
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：ylch (赞：1)

## Subtask 1

直接按照题面意思模拟即可。

```cpp
void solve()
{
	int n; cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	ll sum = 1; // unsigned long long 自然溢出
	for(int i = 1; i <= n; i ++){
		for(int j = i + 1; j <= n; j ++){
			sum *= (a[i] ^ a[j]);
		}
	}
	cout << sum << '\n';
}
```

## Subtask 2

题目要求 $a_i < 2^5$，即 $a_i \in [0,31]$。当 $n > 32$ 时，根据鸽巢原理必有两个相同元素，此时 $a_i \oplus a_j = 0$，整个乘积为 $0$。

代码略。

## 正解

看到这里你可能会感觉这道题是一个诈骗，那么恭喜你猜对了！

如果根据上一个 Subtask，去想异或和什么时候会为零，那么~~你恐怕就会绕进去永远也出不来了……~~

这道题真正的诈骗点在：**答案对 $2^{64}$ 取模**！也就是说，只要乘积里有至少 $64$ 个偶数，那么取模过后它就是 $0$，从而整个式子的答案也就是 $0$。

设偶数个数为 $x$，奇数个数为 $y$。根据二进制奇偶性可以通过最低位判断的规律，可以得出参与异或运算的两个数的**奇偶性相同**时结果为偶数。

则出现的偶数个数应为 $cnt=\frac{x(x-1)}{2}+\frac{y(y-1)}{2}$，当 $cnt \ge 64$ 时答案一定为 $0$。根据 $x+y=n$ 列出关于 $x$ 的一元二次方程：

$$
f(x) = 2x^2 - 2nx + (n^2 - n - 128)
$$

其开口向上（二次项系数为正），最小值在顶点处取得。顶点的 $x$ 坐标为 $x = \frac{n}{2}$，代入得最小值：  

$$
f\left(\frac{n}{2}\right) = \frac{n^2}{2} - n - 128
$$  

要使不等式成立，需存在 $x$（满足 $0 \leq x \leq n$）使得 $f(x) \geq 0$。当二次函数的最小值 $\geq 0$ 时，所有 $x$ 均满足不等式，此时 $\frac{n^2}{2} - n - 128 \geq 0$，解得 $n \geq 1 + \sqrt{257} \approx 17.03$。

结论：**当 $n \ge 17$ 时**答案一定为 $0$。

对其他部分暴力跑一遍即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int maxn = 1e6 + 7;

ll a[maxn];

void solve()
{
	int n; cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	if(n >= 17){
		cout << "0\n"; return ;
	}
	ll sum = 1; // unsigned long long 自然溢出
	for(int i = 1; i <= n; i ++){
		for(int j = i + 1; j <= n; j ++){
			sum *= (a[i] ^ a[j]);
		}
	}
	cout << sum << '\n';
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

## 作者：wenqinghua1001 (赞：1)

## 前言

[题目传送门](https://www.luogu.com.cn/problem/P13685)

## 思路

看到这题，大家都想暴力。对！就是暴力，但要优化。

先打个暴力，双层循环，枚举 $i$ 和 $j$，然后累乘 $a_i \oplus a_j$。

暴力代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10000001];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int ans=1;
		for(int i=1;i<n;i++){
			for(int j=i+1;j<=n;j++){
				ans=ans*(a[i]^a[j]);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

[0 pts](https://www.luogu.com.cn/record/230022450)，答案错误，我回头看了一下题目，要答案对 $2^{64}$ 取模。那 `long long` 存不下了，要用 `unsigned long long`，它可以自动对 $2^{64}$ 取模。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int a[10000001];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int ans=1;
		for(int i=1;i<n;i++){
			for(int j=i+1;j<=n;j++){
				ans=(ans*(a[i]^a[j]));
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

[12 pts](https://www.luogu.com.cn/record/230084887)，超时，这题好像没有更好的思路了（~~或者我没想到~~）。那只能优化，累乘起来的时候，如果乘到了 $0$，那不就成了吗，直接输出 $0$。所以在循环的时候判断一下累乘器，是否为 $0$。

把循环改成：

```cpp
int ans=1;
for(int i=1;i<n&&ans!=0;i++){
    for(int j=i+1;j<=n&&ans!=0;j++){
        ans=(ans*(a[i]^a[j]));
    }
}
```

然后就 AC 了。

## 代码

[AC 记录](https://www.luogu.com.cn/record/230082534)

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int a[10000001];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int ans=1;
		for(int i=1;i<n&&ans!=0;i++){
			for(int j=i+1;j<=n&&ans!=0;j++){
				ans=(ans*(a[i]^a[j]));
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：XingYueLi (赞：1)

## 思路

### 结论一

在 $\prod_{i<j}(a_i\oplus a_j)$ 中，一个因数若是偶数就会为结果贡献至少 1 个 2 的因数。只要**总的 2 的因数的个数** $\ge 64$，模 $2^{64}$ 后结果就是 0。

对于 $\prod_{i<j}(a_i\oplus a_j)$ 中的每个因数 $(a_i\oplus a_j)$，如果 $a_i$ 和 $a_j$ 的奇偶性相同，则 $(a_i\oplus a_j)$ 为偶数，反之为奇数。

易得：当 $n\ge18$ 时，$a$ 的最坏情况为 9 个奇数和 9 个偶数，其中奇偶性相同的配对 $\ge64$，则答案为 0。

结论二

对于 $\prod_{i<j}(a_i\oplus a_j)$ 中的每个因数 $(a_i\oplus a_j)$，如果 $a_i$ 和 $a_j$ 相同，则 $(a_i\oplus a_j)$ 为 0，0 乘任何数都等于 0，于是答案为 0。

> 总结：  
> **若 $n\ge18$，答案为 `0`。**  
> **若存在相等元素，答案为 `0`。**  
> 其余情况直接暴力。


## Code

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
unsigned long long T, n, a[1000005], ans;

int main(){
	cin>>T;
	while(T--){
		ans = 1;
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}
		if(n >= 18){
            cout << "0\n";
            continue;
        }
        sort(a + 1, a + n + 1);
        bool yn = 0;
        for(int i = 1; i < n; i++){
            if(a[i] == a[i+1]){
            	yn = 1;
                cout << "0\n";
                break;
            }
        }
        if(yn) continue;
		for(int i = 1; i <= n; i++){
			for(int j = i + 1; j <= n; j++){
				ans = ans * (a[i] ^ a[j]);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

好题！

直接看式子估计不可做，数据范围也没啥破绽，因此从模数入手。

（以下“位”均指二进制位。）

注意到 $2^{64}$，所以注意到二进制下末尾假如堆了超过 $64$ 个 $0$，，最后答案绝对是 $0$。

而且，你会发现，根据 xor 的性质，末位相同的两个数绝对能为答案末尾贡献一个 $0$。

那么设末尾为 $0$ 的有 $a$ 个数，$1$ 的有 $b$ 个数，那么会贡献出 $\frac{a(a-1)}2+\frac{b(b-1)}2$ 个 $0$。

那么 $n$ 太大这个贡献直接超出 $64$ 了，因此你直接把 $n$ 特别大的直接输出 $0$，$n$ 很小的直接暴力求就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long

const int N=1e6+5;
int n,a[N];

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(n>=20) cout<<0<<endl;
		else{
			int ans=1;
			for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) (ans*=a[i]^a[j]);
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：M1__ (赞：0)

# 题解：P13685 【MX-X16-T3】「DLESS-3」XOR and Impossible Problem

[Link](https://www.luogu.com.cn/problem/P13685)

## 题目思路

求：

$$\prod_{i=1}^n\prod_{j=i+1}^n(a_i\oplus a_j) \bmod 2^{64}$$

令 $A=\{a_i| \bmod 2=1\}$，$B=\{a_i|1  \bmod 2=0\}$，用 $f(a)$ 表示 $\prod_{i=1}^n\prod_{j=i+1}^n(a_i\oplus a_j)$ 中因子 $2$ 的最小数量。数的总数为 $|a|$。

根据异或的性质，$A$ 和 $B$ 中任意两个数异或一定含有因子 $2$。考虑确定一个界，在此情况下 $|A|+|B|$ 为最小值且此时 $f(a) \ge 64$。当 $f(a) > 64$ 时，$\prod_{i=1}^n\prod_{j=i+1}^n(a_i\oplus a_j) \bmod 2^{64} \equiv 0 \pmod{2^{64}}$。直接输出 $0$ 即可。我们可得：

$$\min_a f(a)= \binom{|A|}{2} +\binom{|B|}{2}=\frac{|A|(|A|-1)}{2}+\frac{|B|(|B|-1)}{2}$$

当 $|A|=8,|B|=9$ 时：

$$\min_a f(a)= \binom{|A|}{2} +\binom{|B|}{2}=\binom{8}{2} + \binom{9}{2}= 64$$

综上，$|a| <17$ 时，$f(a)<64$。$|a| \ge 17 $ 时，$f(a) \ge 64$。

故答案为：

$$
\prod_{i=1}^n\prod_{j=i+1}^n(a_i\oplus a_j) \bmod 2^{64} = 
\begin{cases} 
0 & \text{if } |a| \ge 17 \\
\prod_{i=1}^n\prod_{j=i+1}^n(a_i\oplus a_j) \bmod 2^{64} & \text{if } |a| < 17
\end{cases}
$$

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long LL;
const int N=1e6+10;
ll T,n;
LL a[N],b;
int main() {
    cin>>T;
    while(T--){
        cin>>n;
        if(n>=17){
            for(int i=0;i<n;i++) cin>>b;
            cout<<"0\n";
        } 
		else{
            for(int i=0;i<n;i++) cin>>a[i];
            LL ans=1;
            for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                    ans=ans*(a[i]^a[j]);
                }
            }
            cout<<ans<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：Kingsley1116 (赞：0)

## 題目描述
給定 $T$ 組數據，每組數據包含一個長度為 $n$ 的非負整數序列 $a_1, a_2, \ldots, a_n$。要求計算所有滿足 $1 \leq i < j \leq n$ 的異或值 $a_i \oplus a_j$ 的乘積，並將結果對 $2^{64}$ 取模後輸出。

其中，$\oplus$ 表示按位異或運算，對 $2^{64}$ 取模的結果可通過無符號 64 位整數的自然溢出行為直接實現。

## 思路
直接暴力計算所有兩兩異或的乘積會因 $n$ 過大而超時，因此需要通過異或和乘積的特性優化。

若序列中存在重複元素（即存在 $i \neq j$ 使得 $a_i = a_j$），則 $a_i \oplus a_j = 0$，此時整個乘積必然為 $0$。因此，第一步可檢查是否有重複元素，若有則直接輸出 $0$。

對於兩個數 $x$ 和 $y$，$x \oplus y$ 的二進制最低位為 $0$ 當且僅當 $x$ 和 $y$ 的最低位相同。此時 $x \oplus y$ 是偶數，即包含因子 $2$。

設序列中最低位為 $0$ 的元素有 $c_0$ 個，最低位為 $1$ 的元素有 $c_1$ 個，則最低位相同的對數 $m$ 為：

$$m = \mathrm{C}_{c_0}^{2} + \mathrm{C}_{c_1}^{2} = \frac{c_0 \times (c_0 - 1)}{2} + \frac{c_1 \times (c_1 - 1)}{2}$$

這 $m$ 對元素的異或結果均為偶數，即乘積中至少包含 $m$ 個因子 $2$。

若 $m \geq 64$，則乘積中至少包含 $64$ 個因子 $2$，此時乘積必然是 $2^{64}$ 的倍數，對 $2^{64}$ 取模的結果為 $0$，可直接輸出 $0$。

若 $m < 64$，則序列中元素個數 $n$ 必然較小。此時可直接暴力計算所有兩兩異或的乘積，利用無符號 64 位整數的溢出行為自動完成對 $2^{64}$ 的取模。

## 代碼實現
```cpp
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<unsigned long long> a(n);
        unordered_set<unsigned long long> seen;
        bool has_duplicate = false;
        
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (seen.count(a[i])) {
                has_duplicate = true;
            }
            seen.insert(a[i]);
        }
        
        if (has_duplicate) {
            cout << "0\n";
            continue;
        }
        
        int c0 = 0, c1 = 0;
        for (auto x : a) {
            if (x & 1) {
                c1++;
            } else {
                c0++;
            }
        }
        
        long long m = (1LL * c0 * (c0 - 1)) / 2 + (1LL * c1 * (c1 - 1)) / 2;
        if (m >= 64) {
            cout << "0\n";
            continue;
        }
        
        unsigned long long ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans *= (a[i] ^ a[j]);
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```

---

## 作者：sunpengyu (赞：0)

该解决方案的核心思路基于对 $2^{64}$ 取模的特性和异或运算的性质：

- 当乘积中包含至少 64 个因子 2 时，结果对 $2^{64}$ 取模一定为 0
- 偶数与偶数、奇数与奇数的异或结果为偶数，偶数与奇数的异或结果为奇数（不含因子 2）

通过统计序列中偶数 $m$ 和奇数 $k$ 的数量，计算出能产生偶数异或结果的对数 $s$ （见代码）

- 若 $s \geq 64$ ，直接输出0
- 否则直接暴力计算

利用无符号长整型的自动溢出特性实现对 $2^{64}$ 的取模（不开unsigned long long见祖宗，像我赛时0分，改完满分）

大多数情况下时间复杂度为 $\mathcal{O}(n)$ ，当 $n$ 较小时为 $\mathcal{O}(n^2)$



```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define endl '\n'
const int maxn=1e6+7;
const int mod=pow(2,64);
int T,n,a[maxn],m,ans;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		m=0;ans=1;
		for(int i=0;i<n;i++){
			cin>>a[i];
			if(a[i]%2==0) m++;
		}
		int s=m*(m-1)/2+(n-m)*(n-m-1)/2;//计算对数
		if(s>=64) cout<<0<<endl;
		else{
			for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) ans*=(a[i]^a[j]),ans%=mod;
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

