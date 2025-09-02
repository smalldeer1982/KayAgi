# 【MX-X5-T2】「GFOI Round 1」Interstellar

## 题目背景

原题链接：<https://oier.team/problems/X5C>。

---

> [Interstellar - PIKASONIC](https://music.163.com/#/song?id=1900207101)

## 题目描述

你有一个正整数 $x$，你可以对它进行如下操作：
- 选择一个正整数 $y$，把 $x$ 变为它的 $\gcd(x, y)$ 倍，即 $x \gets x \times \gcd(x, y)$。  
  （$\gcd(x, y)$ 表示 $x, y$ 的最大公因数。）

$x$ 的初始值为 $n$，你想通过若干次操作（也可不操作）将它变为 $m$。你想知道至少要多少次操作才能达成目标，或报告无解。

## 说明/提示

**【样例解释】**

对于第一组数据，无需进行任何操作，答案是 $0$。

对于第二组数据，可以选择 $y = 6$，那么 $x$ 会变成 $2 \times \gcd(2, 6) = 4$。

对于第三组数据，容易证明无论如何进行操作都不可能达成目标，所以输出 $-1$。

对于第四组数据，可以：

- 选择 $y = 16$，那么 $x$ 会变成 $12 \times \gcd(12, 16) = 48$；
- 选择 $y = 6$，那么 $x$ 会变成 $48 \times \gcd(48, 6) = 288$。

**【数据范围】**

| 测试点编号 | $n \le$ | $m \le$ | 分值 |
| :-: | :-: | :-: | :-: |
| $1$ | $100$ | $2 \times 10^3$ | $21$ |
| $2$ | $2$ | $10^{18}$ | $17$ |
| $3$ | $10^5$ | $10^5$ | $14$ |
| $4$ | $10^7$ | $10^7$ | $16$ |
| $5$ | $10^{18}$ | $10^{18}$ | $32$ |

对于所有数据，满足 $1 \le T \le 2 \times 10^5$，$1 \le n \le m \le 10^{18}$。

## 样例 #1

### 输入

```
6
1 1
2 4
2 6
12 288
30 144000
114 5141919810```

### 输出

```
0
1
-1
2
3
-1```

# 题解

## 作者：what_can_I_do (赞：10)

[传送门](https://www.luogu.com.cn/problem/P11130)

首先，如果 $m$ 不是 $n$ 的倍数的话，那么显然输出 $-1$。

在最开始设 $d=\frac{m}{n}$，那么 $n$ 每次要乘的数必定是 $d$ 的因数且必定是 $n$ 的因数。由于我们要次数最少，所以每次乘的要尽可能地多，又因为显然的每次最多也就只能乘上 $d$，所以就考虑每次 $n$ 乘上 $\gcd(d,n)$，最多只能乘上 $d$ 保证了这样子做的正确性，最后 $d$ 也要相应地除以 $\gcd(d,n)$。当 $\gcd(d,n)=1$ 时，退出循环。

如果退出循环后，$n$ 还不到 $m$，那就输出 $-1$，在代码里我是直接判 $d$ 是否大于 $1$，否则输出乘的次数。

不太理解为什么这题能评到绿。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
ll n,m;
inline ll gcd(ll a,ll b)
{
	while(b^=a^=b^=a%=b);
	return a;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		if(m%n)
		{
			puts("-1");
			continue;
		}
		ll d=m/n,ans=0;
		while(1)
		{
			ll g=gcd(n,d);
			if(g==1) break;
			d/=g,n*=g,ans++;
		}
		if(d>1) puts("-1");
		else printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Brilliant11001 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18440715)

~~场外选手口胡~~

## [题目传送门](https://www.luogu.com.cn/problem/P11130)

### 题目大意：

$T$ 组询问，每次给定两个正整数 $a, b$。

定义一种操作为：选择一个正整数 $y$，将 $x$ 变成 $x\times \gcd(a, y)$。

对每组询问回答：将 $a$ 变成 $y$ 最少需要几次操作。

数据范围：$1\le T\le 2\times 10^5,1\le a\le b\le 10^{18}$。

### 思路：

读完题确定思考方向应该是选择一种策略使得每次 $a$ 的增长尽量大，考虑贪心。

考虑到 $\gcd(a, y)$ 是整数，所以首先判掉一种无解情况：当 $a\nmid b$ 时，必定无解。

接着令 $c = \frac{a}{b}$。

因为操作中的 $y$ 是自己指定的，所以 $a$ 每次扩大的倍数和它自己的质因子及其指数相关，我们想让它扩大的幅度尽量大，就得每次尽量选择**它和 $c$ 的质因子重合的尽量多的质因子，即 $\gcd(a, c)$**。

通俗来讲就是每次尽量增大一点，多囊括一点质因数，在更靠近目标的过程中顺便拥有更多的选择权。

所以做法就是每次求出 $d = \gcd(a, c)$，然后 $a\leftarrow a \times d$，$c\leftarrow\frac{c}{d}$，直到 $a = b$。

在此过程中还要判断 $d$ 是否为 $1$，若 $d = 1$ 且 $a \ne b$，那么就不可能成功了，因为此时 $c$ 中**存在被垄断的质因子**。

#### 以上都为感性理解，接下来开始严谨（可能不那么严谨）证明。

这里从**决策包容性**来证明。

从质因数分解的方向来思考。

**在操作进行的任意时刻**，设

$$a = p_{1}^{\alpha_1}\times p_{2}^{\alpha_2}\times\cdots\times p_{k}^{\alpha_k}$$

设 $d = \gcd(a, c)$，是最优策略 $y$ 所产生的贡献，$d'$ 为选择另外一个 $y'$ 带来的贡献，且 $d'< d$。

设

$$d = p_{1}^{a_1}p_{2}^{a_2}\cdots p_{k}^{a_k}$$

$$d' = p_{1}^{b_1}p_{2}^{b_2}\cdots p_{k}^{b_k}$$

因为 $d' < d$，所以 $\forall i\in[1, k],b_i\le a_i$，并且 $\exists i\in[1, k],b_i < a_i$.

按两种方式将 $a$ 操作之后分别得到：

$$a = p_{1}^{\alpha_1 + a_1}\times p_{2}^{\alpha_2 + a_2}\times\cdots\times p_{k}^{\alpha_k + a_k}$$

$$a' = p_{1}^{\alpha_1 + b_1}\times p_{2}^{\alpha_2 + b_2}\times\cdots\times p_{k}^{\alpha_k + b_k}$$

所以 $\exists i\in[1, k], \alpha_i + b_i < \alpha_i + a_i$.

接着考虑这一次操作对下一次操作的影响。

设从 $a$ 中取出来若干质因数组成的集合 $S = \{n_1\cdot p_1, n_2\cdot p_2\cdots n_k\cdot p_k\}$，是由 $n_1$ 个 $p_1$，$n_2$ 个 $p_2,\cdots,n_k$ 个 $p_k$ 组成的多重集，其中 $\forall i\in [1, k], 0\le n_i\le \alpha_i + a_i$。

同理可设从 $a'$ 中取出来若干质因数组成的集合 $S' = \{n'_1\cdot p_1, n'_2\cdot p_2\cdots n'_k\cdot p_k\}$，是由 $n'_1$ 个 $p_1$，$n'_2$ 个 $p_2,\cdots,n'_k$ 个 $p_k$ 组成的多重集，其中 $\forall i\in [1, k], 0\le n'_i\le \alpha_i + b_i$。

定义 $t$ 为下一次操作选择 $y\in \mathbb{N}$ 可产生的贡献，从 $S$ 中选择产生的所有 $t$ 值组成不可重集合 $S_1$，从 $S'$ 中选择产生的所有 $t$ 值组成不可重集合为 $S_2$。

由于 $\exists i\in[1, k], \alpha_i + b_i < \alpha_i + a_i$，所以容易得出 $S_2\subsetneqq S_1$。

所以选择乘上 $d'$ 后未来能做到的，选择乘上 $d$ 后未来也能达到，即 $d$ 的的**适用性更广**。

因此**在任意局面下，做出局部最优解后，这个局部最优策略提供的可能性包含其他所有的策略提供的可能性，此贪心策略是正确的。**

证毕。

同时，再此贪心策略下，每次 $a$ 至少要乘二，所以时间复杂度为 $O(T\log b)$。

$\texttt{Code:}$

```cpp
#include <iostream>

using namespace std;
typedef long long ll;
int T;
ll a, b;

ll gcd(ll a, ll b) {
    if(!b) return a;
    return gcd(b, a % b);
}

void solve() {
    scanf("%lld%lld", &a, &b);
    if(b % a != 0) {
        puts("-1");
        return ;
    }
    ll c = b / a;
    if(c % a != 0) {
        puts("-1");
        return ;
    }
    int res = 0;
    while(a != b) {
        ll d = gcd(a, c);
        a *= d, c /= d;
        ++res;
    }
    printf("%d\n", res);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：wangboyue_740325 (赞：5)

# 思路
明显可以看出每次操作令 $n\gets\gcd(n,\frac{m}{n})$ 即可，若 $\gcd(n,\frac{m}{n})=1$ 或 $m\nmid n$，报告无解。  
证明：  
1. 选择 $\gcd(n,\frac{m}{n})$ 保证了每次操作时能够尽可能多地保留 $n$ 中与 $m$ 相关的成分。因此在每次操作中，能快速向 $m$ 靠近。  
2. 如果选择的让 $x$ 扩大的倍数没有把 $d$ 作为因子，那么每次增量都可能会减少，使得无法有效接近 $m$。

综上所述，选择 $\gcd(n,\frac{m}{n})$ 是最优的，因为它确保了在每一步中最大程度地利用 $n$ 中的成分。这样可以通过最少的步骤将 $n$ 变为 $m$。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int gcd(int a,int b){
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
int help(){
	int n,m;
	cin>>n>>m;
	if(m%n!=0){
		return -1;
	}
	if(n==m){
		return 0;
	}
	if(gcd(n,m/n)==1){
		return -1;
	}
	int ans=0;
	while(n<m){
		if(gcd(n,m/n)==1){
			return -1;
		}
		n*=gcd(n,m/n);
		ans++;
	}
	return ans;
}
signed main(){ 
	int t;
	cin>>t;
	while(t--){
		cout<<help()<<"\n";
	}
	return 0;
}
```

---

## 作者：xiaoke2021 (赞：3)

说实在的，建议评黄。

---

如果你想把 $x$ 变为 $m$，那你需要保证 $x$ 和 $m$ **不** 互质。这很好理解：将 $x$ 乘上 $x$ 和 $y$ 的最大公因数，这个最大公因数至少是 $x$ 的因数。很像废话对不对？但如果 $x$ 与 $m$ 互质，也就是说 $m$ 中的任何一个因数，$x$ 中都没有，那么 $x$ 将永远不可能变为 $m$，因为 $x$ 所乘的数 **必然为 $x$ 的因数**。

那代码就很好写了。每次将 $x$ 乘上 $\gcd(x,m)$ 并将答案加一直到 $x=m$，期间若出现 $x$ 与 $m$ 互质则报告无解。

没了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long n,m;
int main(){
	cin>>T;
	while(T--){
		long long ans=0;
		cin>>n>>m;
		if(n==m){
			puts("0");
			continue;
		}
		if(m%n!=0||__gcd(n,m/n)==1){
			puts("-1");
			continue;
		}
		while(n!=m){
			if(__gcd(n,m/n)==1){
				ans=-1;
				break;
			}
			n*=__gcd(n,m/n);
			ans++;
		}cout<<ans<<endl;
	}
}
```

---

## 作者：飞升的海绵bb (赞：2)

> ### 题目描述
>
> 你有一个正整数 $x$，你可以对它进行如下操作：
> - 选择一个正整数 $y$，把 $x$ 变为它的 $\gcd(x, y)$ 倍，即 $x \gets x \times \gcd(x, y)$。  
  （$\gcd(x, y)$ 表示 $x, y$ 的最大公因数。）
>
> $x$ 的初始值为 $n$，你想通过若干次操作（也可不操作）将它变为 $m$。你想知道至少要多少次操作才能达成目标，或报告无解。

由题意可知，$n$ 每次只能乘上其本身一个的因数，所以显而易见的是若 $n$ 不是 $m$ 的因数的话，无解。其次，该题目要求操作次数最少，那么每次扩大的倍数则应该尽可能大。

首先应该明确：贪心地找每一步的最优策略是没有问题的。因为每次 $n$ 找到最优策略并扩大后，下一次能选取的因数总是更多、更大的，所以总是不劣的。

然后我们考虑 $n$ 应该怎么扩大至 $m$。首先令 $k=\frac m n$，则 $k$ 为 $n$ 应该乘的数。但是由于 $n$ 每次只能乘上其本身一个的因数，贪心地来找，就应该是乘上 $\gcd(n, k)$。所以综合下来的最优决策应该就是每一步：$k\gets \frac m n,n \gets n \times \gcd(n,  k)$。

当然，由于 $n$ 每次只能乘上其本身一个的因数。那么如果 $k$ 中有 $n$ 中不含的因数的话，也是无解的。这其实只需要在扩大途中检查是否有：$n<m$ 但 $\gcd(n, k)=1$ 即可。

时间复杂度 $O(T \log n)$ 当然是能过啦。 

其它就没有什么需要特别注意的了，详见 AC 代码。

### AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long //开 long long
using namespace std;
void solve()
{
    ll n,m;
    cin>>n>>m;
    if(n==m) return cout<<0<<"\n",void();
    if(m%n!=0) return cout<<-1<<"\n",void();
    ll cnt=0;
    while(n!=m)
    {
        ll tmp=__gcd(n,m/n); //自带的 gcd
        if(n<m&&tmp==1) return cout<<-1<<"\n",void();
        n*=tmp;
        cnt++;
    }
    cout<<cnt<<"\n";
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        solve();
    }
}
```

---

## 作者：Caged_Bird (赞：1)

# P11130 解题报告
## 题意简述
给出两个非负整数 $n$，$m$，定义一次操作为将 $n$ 变为 $n\times\gcd(n,x)$，其中 $x$ 为任意非负整数，求最小使 $n=m$ 的操作次数。  
 
## 解题思路
转化一下题意：可以发现，$\gcd(n,x)$ 其实就是 $n$ 的因子，因此就是将 $n$ 每次乘以 $n$ 的因子以达到 $m$，使得操作数最少。 

考虑对 $n$ 与 $m$ 质因数分解的结果，若 $m$ 与 $n$ 有不同的质因数，那么输出 $-1$，因为这样 $n$ 无法通过乘以自己的因子来得到 $m$。否则每次乘 $\gcd(n,m\div n)$，直到$n=m$ 为止。  

为什么每次乘 $\gcd(n,m\div n)$ 是最优的呢？我们想到考虑要让多次操作的数的乘积等于 $m\div n$，每次操作的数就必须要是 $m\div n$ 的因子。于是就每次选取 $n$ 与 $m$ 的公因数，这样既**不会**导致乘数**不被** $m\div n$ 整除，又能保证是 $n$ 的因子。为了使增加效率最高，乘的数要尽可能大，于是就选取了它们的最大公因数。  

判断无解时，如果暴力分解时间复杂度为 $\mathcal{O}(\sqrt n)$，无法通过。直接在乘 $\gcd(n,m\div n)$ 的过程中检查，如果 $\gcd(n,m\div n)=1$，那么 $n$ 与 $m\div n$ 没有大于 $1$ 的公约数，$n$ 无法继续增大，输出 $-1$ 即可。
## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n,m,t;
signed main(){
	t=read();
	while(t--){
		n=read();
		m=read();
	    int ans=0;
		while(n!=m){
			if(__gcd(m/n,n)==1){
				cout<<-1<<endl;
				break;
			}
			n*=__gcd(m/n,n);
			ans++;
		} 
		if(n==m)cout<<ans<<endl;
	}
	return 0;
}
```
That's all. Thank you for listening.

---

## 作者：_H17_ (赞：1)

## 前言

赛时爆切绿题，爽！

## 题目分析

显然题目是让 $n$ 扩大若干倍，显然假设某一次要扩大 $k$ 倍。

首先要保证 $(k\times n)\mid m$，不然没办法继续乘了。

显然当 $n\nmid m$ 时无解，其他时候 $k$ 取 $\gcd(n,m\div n)$ 最优。

为啥呢？首先一定要是 $n$ 的约数，其次乘完了是 $m$ 的约数。然后最大的就是它们的最大公约数。

所以每次让 $n\gets n\times \gcd(n,m\div n)$。

当 $k=1$ 并且 $n\ne m$ 时无解。

时间复杂度 $O(T\log n)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,m,ans,tmp;
signed main(){
    for(cin>>T;T;--T){
        cin>>n>>m;
        if(m%n){
            cout<<"-1\n";
            continue;//无解
        }
        ans=0;
        while(n<m){
        	n*=(tmp=__gcd(n,m/n));//变化
            ans++;
            if(tmp==1&&n!=m){
                cout<<"-1\n";
                goto g;
            }//判断无解
        }
        cout<<ans<<'\n';//输出答案
        g:;
    }
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

首先，$n\times \gcd(y,n)=n^2\div (n\div \gcd(y,n))$ 也就是相当于令 $n\leftarrow n^2\div x$，其中 $x$ 可以视为一个数。

那么一旦操作 $a$ 次可以令 $n=m$，此时 $n^{2^a}\div(x_1\times x_2\times \cdots\times x_a)=m$，也就是说，$n^{2^a}\bmod m=0$。

那么我们充分发挥人类智慧，猜测答案一定很小，所以我们可以每次暴力枚举 $a$，再判断 $n^{2^a}$ 是否整除 $m$ 即可。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;

int msc(int x,int y,int z){
	int ans=0;
	while(y){
		if(y&1) (ans+=x)%=z;
		(x+=x)%=z;
		y>>=1;
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--){
		int n,m;cin>>n>>m;
		int cnt=0;
		if(m%n){
			cout<<-1<<'\n';
			continue;
		}
		n%=m;
		while(n){
			if(cnt>=80){
				cnt=-1;
				break;
			}
			n=msc(n,n,m);
			cnt++;
		}
		cout<<cnt<<'\n';
	}
	return 0;
}
```

---

## 作者：Hungry_STS (赞：0)

# [MX-X5-T2](https://www.luogu.com.cn/problem/P11130)

# 题意叙述
给你两个正整数 $N$ 和 $M$，$N$ 每次可以变成它和任意一个正整数与他的最大公约数的积，也就是 $N \gets N \times \gcd(N, x) (x \in \mathbb Z)$。

问 $N$ 能否变成 $M$。

# 题目思路
经过思考，我们发现一个数与任意一个正整数的最大公约数肯定是这个数的任意一个因数。于是 $N$ 的转移就变为每次可以变成自己与自己的一个因数的乘积。

有了这一理论，大致思路就出来了。首先，如果 $N > M$ 或者 $M$ 不整除 $N$，肯定是行不通的。接下来我们设 $x = \frac{M}{N}$，依次从大到小遍历 $N$ 的因数 $y$，如果能被 $x \mid y$，就 $x \gets \frac{x}{y}$，$N \gets N \times y$。如果 $N$ 的因数用完了，$x \ne 1$，那就证明也是行不通的。

我们成功获得了一份TLE的代码，$N \le 10^9$ 对它来说太大了，我们考虑把寻找因数的部分省掉。仔细想想，既是 $N$ 的因数，也能被 $x$ 整除，又是最大的，这不就是 $\gcd(N, x)$ 吗？

于是思路就变为每次找到 $y = \gcd(N, x)$，还是 $x \gets \frac{x}{y}$，$N \gets N \times y$。最后再判断。

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int solve() {
	int n,m;
	cin>>n>>m;
	if(n==m)return 0;
	if(n>m||m%n!=0)return -1;//不行的两种情况
	int x=m/n,ans=0;
	while(x!=1&&__gcd(x,n)!=1)x/=__gcd(x,n),n*=__gcd(x,n),ans++;//每次除gcd(x,n)
	if(x==1)return ans;//除完了
	else return -1;
}
signed main() {
	cin>>T;
	while(T--)cout<<solve()<<'\n';
}
```

---

## 作者：donghanwen1225 (赞：0)

首先，由于每次只能给 $x$ 乘上一个数，所以 $x$ 只能变成它的倍数。这说明：如果 $\dfrac{y}{x}$ 不是整数，则已经必然无解。

否则，记 $d=\dfrac{y}{x}$，我们希望给 $x$ 乘出一个 $d$ 来。设 $x$ 的质因数分解形式为 $x=\prod\limits_{i=1}^{m} p_i^{c_i}\;(c_i>0)$，由于 $\gcd(x,y)$ 始终整除 $x$，不论如何操作都不会凭空变出一个新的质因子来。这说明：如果 $d$ 不是仅由 $p_1,p_2,\cdots,p_m$ 乘出来的，那么也必然无解。

否则，$d$ 是仅由 $p_1,p_2,\cdots,p_m$ 乘出来的，此时可以设 $d=\prod\limits_{i=1}^{m}p_i^{c'_i}\;(c'_i\geq 0)$。为了用尽量少的次数把 $d$ 补回来，我们每一次都做最大的努力：记 $p=\gcd(x,d)$，并令 $x$ 乘上 $p$、$d$ 除以 $p$。从每个质因子来考虑，这样做可以最大程度的补上 $d$ 中的差距，故一定是最优的。

但是，$x,y$ 的范围大到 $10^{18}$，显然无法对其进行质因子分解。然而从上述分析来看，写出质因子形式只是对理解做法起到了帮助，实际上不需要用到。我们只要不断地取 $\gcd(x,d)$ 就好了。如果到最后 $\gcd(x,d)=1$ 时还有 $d\neq 1$，就说明 $d$ 有多出来的质因子，自然判断为无解。

理论最坏复杂度大致为 $O(T\log n\log\log n)$，第一个 $\log n$ 是 $\gcd$ 的复杂度、第二个 $\log\log n$ 是最大的乘 $\gcd$ 次数。

code：


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
int t;ll n,m;
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		if(m%n!=0) cout<<"-1\n";
		else
		{
			ll to=m/n;
			int ans=0,ok=1;
			while(n!=m)
			{
				ans++;
				ll c=gcd(to,n);
				if(c==1){ok=0;break;}
				n*=c,to/=c;
			}
			cout<<(ok?ans:-1)<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：zhoumurui (赞：0)

### 题面展示

你有一个正整数  $n$，你想通过若干次操作将它变为 $m$。

每次操作，你可以选择一个正整数 $y$，将 $x$ 变为 $x \times \gcd(x,y)$。

你想知道至少要多少次操作才能达成目标。

如果无解，输出 $-1$，如果无需操作，输出 $0$。

### 解题思路

命题 $1$：每次操作等价于：选择 $x$ 的一个正因数 $y$，将 $x$ 变为 $x \times y$。

这很显然，因为如果是选择 $y$，将 $x$ 变为 $x \times \gcd(x,y)$，那我选择 $\gcd(x,y)$ 也是同样的结果，所有的情况都可以简化成选择 $x$ 的因数的情况。

而在选择 $x$ 的因数时，与 $x$ 相乘的自然是选择的数本身。于是命题 $1$ 得证。

命题 $2$：进行 $k$ 次操作可以将 $x$ 变为 $y$ 当且仅当 $y$ 是 $x$ 的倍数且是 $x^{2^k}$ 的因数。

用数学归纳法。

当 $k=1$ 时，由命题 $1$，进行一次操作得到的最大数是 $x \times y$，其中 $y$ 是 $x$ 的因数。想让满足 $x \times y$ 是 $x$ 的倍数，且是 $x^2$ 的因数。所以当 $k=1$ 时原命题成立。

假设 $k=t$ 时原命题成立，我们进行前 $t$ 次操作得到了数 $x_t$，它是 $x$ 的倍数且是 $x^{2^t}$ 的因数。

如果我们再进行一次操作，它会变成数 $x_{t+1}$。它是 $x_t$ 的倍数，那么它显然是 $x$ 的倍数；它是 $x_t^2$ 的因数，那么它显然是 $x^{2^t}$ 的因数。

所以当原命题在 $k=t$ 时成立，那么它在 $k=t+1$ 时也成立，由数学归纳法，命题 $2$ 得证。

命题 $2$ 足够我们使用了。我选择直接暴力枚举 $k$ 并判断是否满足条件。

### 核心代码展示

我的想法需要用到高精度，这里贴出简洁的 Python 版本。

```python
for i in range(t):
    n,m=input().split()
    n=int(n)
    m=int(m)
    if n==m:
        print(0)
    
    elif n==1 or m%n!=0:
        print(-1)
    else:
        for i in range(1,8):
            if n**(2**i) %m==0:
                print(i)
                break
        else:
            print(-1)
```

---

## 作者：Your_Name (赞：0)

## 题意
给出 $n$ 和 $m$，每次操作可以选一个数 $x$ 把 $n$ 变成 $n \times \gcd(x,n)$，问最少要几次操作能把 $n$ 变成 $m$。
## 思路
因为一共要乘上 $m\div n$，设其为 $k$，然后直接贪心，当前最大能乘的就是 $\gcd(k,n)$，每次维护 $k$ 和 $n$ 即可。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, t, k, ans;
int main(){
    cin >> t;
    while(t --){
        cin >> n >> m;
        k = m / n;
        if(k * n != m || (n == 1 && m != 1)){
            cout << "-1" << endl;
            continue;
        }//无解
        ans = 0;
        while(k != 1){
            if(__gcd(k, n) == 1){
                ans = -1;
                break;
            }//无解
            ans ++;
            k /= __gcd(k, n);
            n *= __gcd(k, n);//维护当前数和当前还要乘的数
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Kazeno_Akina (赞：0)

前情提要：我打比赛的设备是手机。因为是手机所以打字巨大麻烦。

首先看到这个题会想到一个显然性质，就是在 $y$ 是 $x$ 的因数时，$x\times \gcd (x,y) = x \times y$。所以可以说这 $\gcd$ 就没啥用。

然后你考虑 $\gcd$ 本质上就是对二者的各个质数指数取 $\min$。所以单拆一个质数出来的话其实每次操作指数的上限会乘二，而且因为这玩意有很显然的贪心，所以对于单独的质数来说只要目标指数小于等于指数上限就可做。

于是产生一个想法，就是对每个质因数分别做，每次指数乘二比大小再取所有质数的 $\max$ 就行了。

但是我是手机啊，这玩意它不好打字，我绝对没有用手机搓质因数分解的兴趣。

所以考虑一种简化做法，就是你每次给整体平方再对 $m$ 取模。啥时候取到 $0$ 了就操作成功了。而这玩意你发现就算是 $2$ 操作 $6$ 次也已经爆上限了，所以你直接循环 $6$ 次判就行了。总复杂度 $O(T \log \log W)$，其中 $W$ 是值域，本题内是 $10^{18}$。

记得开 `__int128`！！

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long n1,m;
__int128 n;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n1 >> m,n=n1;
        if(n1==m){cout << 0 << '\n';continue;}
        if(m%n1!=0){cout << -1 << '\n';continue;}
        for(int i(1);i<=6;++i){
            n=n*n%m;
            if(n==0){cout << i << '\n';goto lab;}
        }
        cout << -1 << '\n';
        lab:continue;
    }
}
```

---

## 作者：cheng2010 (赞：0)

## 思路

首先，$m$ 一定要可以写成 $kn$ 的形式，否则一定不可能，所以，可以把 $m$ 除上 $n$ 求出 $k$，再做思考。

随后，怎么求出最小操作次数呢？设 $g=\gcd(n,k)$ 每一次把 $n \times g,k/g$ 直到 $k=1$ 即可，若 $g=1$ 但 $k \neq 1$，一定无解。

为什么呢？因为要使得 $n$ 总共乘上 $k$，所以每一次必须乘上 $k$ 的因数，又因为乘上的数一定要可以表示为 $\gcd(n,y)$ 的形式，所以，$\gcd(n,k)$ 自然就是最优的了。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld %lld",&n,&m);
		int res=0;
		if(m%n!=0)
		{
			puts("-1");
			continue;
		}
		m/=n;
		while(m!=1)
		{
			int g=__gcd(n,m);
			res++;
			m/=g;
			n*=g;
			if(g==1)
			{
				res=-1;
				break;
			}
		}
		printf("%lld\n",res);
	}
}
```

---

## 作者：keatsli (赞：0)

先考虑无解情况：

首先 $\gcd(n,y)$ 一定是 $n$ 的因子。

1. 若 $n\nmid m$，即 $n$ 无论如何怎么乘东西都会有一些其他的 $m$ 没有的质因子，故此时无解。
2. $m$ 有一些 $n$ 没有的质因子，而乘的都是 $n$ 的因子，故无论如何无法得到这些质因子。

第一种情况是容易判断的，但质因数分解是困难的。

考场上我想了一种根号分治，注意到 $\dfrac{m}{n}$ 和 $n$ 总有一个 $\leq10^9$。

而通过计算这两个中任意一个的质因数分解我们都可以得到我们需要的 $n$ 和 $m$ 中需要倍增的质因子，同时我们也可以检查合法性。

### 若 $n\leq 10^9$

直接对 $n$ 质因数分解，把 $m$ 中每一个 $n$ 的质因子除掉，如果最后 $m\neq 1$ 就意味着 $m$ 有一些 $n$ 没有的质因子，此时无解。

若 $m=1$，此时我们就得到了 $n$ 和 $m$ 的质因数分解，故我们对每个质因子考虑：

整个过程就像一个倍增的过程，可以在一开始取满质因子的指数，这样指数 $k$ 次可以到 $2^k$ 倍，然而最后一次需要恰好达到，故对于这个质因子我们需要 $\lceil\log_2(\lceil\dfrac{k_m}{k_n}\rceil)\rceil$，其中 $k_n$ 和 $k_m$ 是这个质因子在 $n$ 和 $m$ 中的指数。

最后的答案是对每个质因子的答案取 `max`。

### 若 $\dfrac{m}{n}\leq 10^9$

考虑 $\dfrac{m}{n}$ 的质因数分解，若其中有非 $n$ 的因子的话，那么不论怎么乘 $n$ 的因子都达不到。

否则我们仍可以考虑这个倍增的过程，并取出对于每个 $\dfrac{m}{n}$ 因子的 $n$ 中指数和 $m$ 中指数，做法同上。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mi(int x,int&y){
	int num=0;
	while(y%x==0)++num,y/=x;
	return num;
}
vector<pair<int,int>>fj(int x){
	vector<pair<int,int>>vec;
	for(int i=2;i*i<=x;++i){
		int num=0;
		while(x%i==0)x/=i,++num;
		if(num)vec.push_back({i,num});
	}
	if(x>1)vec.push_back({x,1});
	return vec;
}
signed main(){
	ios::sync_with_stdio(0);
	int T;cin>>T;
	while(T--){
		int n,m;cin>>n>>m;
		int x=__gcd(n,m);
		if(x!=n){cout<<"-1\n";continue;}
		int t=m/n;
		if(t<=1e9){
			vector<pair<int,int>>tmp=fj(t);
			bool flg=0;
			int ans=0,nn=n;
			for(auto i:tmp)if(n%i.first!=0){flg=1;break;}else{
				int tmp=mi(i.first,nn);
				ans=max(ans,(int)(ceil(log2((i.second+2*tmp-1)/tmp))+1e-6));
			}
			if(flg){cout<<"-1\n";continue;}
			cout<<ans<<'\n';
		}
		else{
			vector<pair<int,int>>tmp=fj(n);
			bool flg=0;
			int mm=m;
			int ans=0;
			for(auto i:tmp){
				int tmp=mi(i.first,mm);
				ans=max(ans,(int)(ceil(log2((tmp+i.second-1)/i.second))+1e-6));
			}
			if(mm!=1){cout<<"-1\n";continue;}
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

闲话：这个做法非常劣，现在可以做到 $O(T\log\log V)$，[做法](https://www.luogu.com/article/rd5wpycw) 来自 [Kazeno_Akina](https://www.luogu.com.cn/user/612567)

---

