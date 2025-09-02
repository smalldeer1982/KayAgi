# 数列と計算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/bcu30/tasks/bcu30_f

ある町に、数列が大好きな黒猫と計算が大好きな狼が住んでいます。今日は、二人である数列をもとに計算をして遊ぶことにしました。

黒猫は、長さ $ N $ の整数列 {$ a_i $} を持っていて、この数列の隣り合う項の間に $ + $ または $ \times $ を挿入した式を作り、狼がその値を計算しようとしています。 二人はこの整数列を使いできるだけ長く遊びたいので、作ることができる全ての式 ($ 2^{N-1} $ 通りある) を作り、それらの式の値の合計を求めることにしました。

最終的に答えが合っているかどうかをチェックしたいので、二人はこれらの合計を $ 1,000,000,007\ (=\ 10^9\ +\ 7) $ で割ったあまりを求めるプログラムを作ることを、プログラミングコンテストで日々鍛錬を続けているあなたに頼んできました。

あなたはこの値を計算するプログラムを作ることで、二人を助けてください。

ただし、 $ \times $ は $ + $ よりも計算の優先順序が高いことに注意してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $ $ (1\ \leq\ i\ \leq\ N) $
- $ a_i $ $ (1\ \leq\ i\ \leq\ N) $ は整数である。

### Sample Explanation 1

考えられる数式は、 $ 1+2+3 $ と $ 1+2\ \times\ 3 $ と $ 1\ \times\ 2+3 $ と $ 1\ \times\ 2\ \times\ 3 $ の $ 4 $ 種類です。 これらの式を計算すると、それぞれ答えは $ 6 $、$ 7 $、$ 5 $、$ 6 $ となるので、合計は $ 6+7+5+6=24 $ です。

### Sample Explanation 2

求める合計は $ 1000000007\ (=\ 10^9+7) $ となるので、これを $ 10^9+7 $ で割ったあまりである $ 0 $ を出力します。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
24```

## 样例 #2

### 输入

```
2
28055 35642```

### 输出

```
0```

## 样例 #3

### 输入

```
12
31415926 535897932 38462643 383279502 884197 169399375 105820974 944592307 81640628 620899862 803482534 21170679```

### 输出

```
626713706```

# 题解

## 作者：Shawk (赞：2)

* 一个式子里既有加号又有乘号，不好处理，可以想最后一个加号的位置，有$n-1$种情况：

* 定义`f[i]`为前i个数据题意求出的和，有：

$f_i \doteq \sum_{j=1}^{i-1}(f_j+\prod_{k=j+1}^{i}a_k\times 2^{j-1})+\prod_{k=1}^{i}a_k$

* 将第一项拆开，得到

$f_i \doteq \sum_{j=1}^{i-1}f_j+\sum_{j=1}^{i-1}(\prod_{k=j+1}^{i}a_k\times 2^{j-1})+\prod_{k=1}^{i}a_k$

* 然后就根据这个式子求就可以了

`f[i] = s[i-1] + sp[i] + p[i];//一一对应`

* 代码
```cpp
#include <cstdio>
#define int long long
using namespace std;
const int N = 1e5+5, M = 1e9+7;
int n, a[N], f[N], s[N], sp[N], p[N];
int qpow(int a, int x) {
        int ans = 1;
        while (x) {
                if (x & 1) ans = ans * a % M;
                a = a * a % M;
                x >>= 1;
        }
        return ans;
}
signed main() {
        scanf("%lld", &n);
        for (int i = 1; i <= n; ++i)
                scanf("%lld", &a[i]);
        f[1] = s[1] = p[1] = a[1] % M;
        for (int i = 2; i <= n; ++i) {
                sp[i] = (sp[i-1] * a[i] % M + a[i] * qpow(2, i-2) % M) % M;
                p[i] = p[i-1] * a[i] % M;
                f[i] = (s[i-1] + sp[i] + p[i]) % M;
                s[i] = (s[i-1] + f[i]) % M;
        }
        printf("%lld\n", f[n]);
        return 0;
}

```


---

## 作者：Hisaishi_Kanade (赞：1)

不难想到，以加号为划分，设 $S_{i}$ 表示前 $i$ 个个数的结果之和。

+ $S_{i}=\left(\prod\limits_{k=1}^{i} a_i\right)+\sum\limits_{k=1}^{i-1}\left(S_k+2^{k-1}\times{}\prod\limits_{p=k+1}^{i} a_{p}\right)$

$k$ 就是枚举最后一个加号的断点位置，$\prod\limits_{p=k+1}^{i} a_{p}$ 是分割后后半段的贡献，乘 $2^{k-1}$ 是因为 $S_{k}$ 中有这么多种情况。

这个式子 $O(n^2)$，所以得推一推。

+ 原式 $\to$ $\left(\prod\limits_{k=1}^{i} a_i\right)+\sum\limits_{k=1}^{i-1}S_k+\sum\limits_{k=1}^{i-1}\left(2^{k-1}\times{}\prod\limits_{p=k+1}^{i} a_{p}\right)$

发现：

1. $\prod\limits_{k=1}^{i} a_i$ 可以前缀和求出。
2. $\sum\limits_{k=1}^{i-1}S_k$ 同理可以前缀和求出。
3. $\sum\limits_{k=1}^{i-1}\left(2^{k-1}\times{}\prod\limits_{p=k+1}^{i} a_{p}\right)$ 可以在第一条的基础上再套一个前缀和求出。

这样，三层前缀和糊脸上，大概可以 $O(n)$ 求出 $S_n$。

但是你有没有发现求 $2^{k-1}$ 用快速幂，这个东西就 $O(n\log n)$ 了，所以预处理 $2^n$ 保证复杂度为 $O(n)$。

```cpp
#include <stdio.h>
const int p=1e9+7;
int n,i;
int a[100005],sum[100005];
long long f[100005],pre[100005],prod[100005],pw[100005];
int main()
{
	pw[0]=1;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		pw[i]=(pw[i-1]<<1)%p;
	}
	f[1]=sum[1]=prod[1]=a[1]%p;
	for(i=2;i<=n;++i)
	{
		prod[i]=prod[i-1]*a[i]%p;
		pre[i]=(pre[i-1]*a[i]%p+a[i]*pw[i-2]%p)%p;
		f[i]=(sum[i-1]+pre[i]+prod[i])%p;
		sum[i]=(sum[i-1]+f[i])%p;
	}
	printf("%lld\n",f[n]);
	return 0;
}


```

---

## 作者：_Cheems (赞：0)

来篇小清新的题解。

考虑让每个极大连续乘积段（即全用 * 连接的）的贡献挂在它最后一个元素上，记 $f_i$ 表示以 $i$ 为结尾的乘积段在所有情况下的价值之和，那么答案就是 $\sum 2^{\max(0,n-i-1)}f_i$。

$f$ 的转移是容易的：$f_i\gets a_if_{i-1}+a_i2^{\max(0,i-2)}$。即分讨 $a_i$ 前面是 * 还是 +。

复杂度 $O(n)$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 5, mod = 1e9 + 7;
int n, a, f[N], pw[N], ans;

signed main(){
	pw[0] = 1;
	for(int i = 1; i < N; ++i) pw[i] = pw[i - 1] * 2ll % mod;
	cin >> n;
	for(int i = 1; i <= n; ++i){
		scanf("%lld", &a);
		f[i] = (f[i - 1] * a % mod + pw[max(0ll, i - 2)] * a % mod) % mod;
		ans = (ans + f[i] * pw[max(0ll, n - i - 1)] % mod) % mod;
	}
	cout << ans;
	return 0;
}

```

---

## 作者：dead_X (赞：0)

## 思路
我们考虑套路把答案拆成**每个数贡献**的和，再将**总和**拆为**总数乘期望**的形式。。

一开始我想拆的是 $a_i$ 对答案的总贡献，但是发现这样形如 $a_3\times a_4\times a_5$ 的式子会被算很多遍。对于这个问题，我并没有什么好方法。

因此，我换了个思路：我们计算 $a_i$ 是乘法最后一个数的贡献。

这样我们就豁然开朗了。假设前 $i$ 个数的平均贡献为 $f_i$，第 $i+1$ 个数的贡献就为 $\frac{1}{2}(f_i+1)a_{i+1}$，原因是前一个符号有 $\frac{1}{2}$ 的概率取乘，$\frac{1}{2}$ 的概率取加，而加号前的贡献我们已经算过了。

最后，我们把平均贡献乘上 $2^{n-2}$ 之后求和就是最终答案了，因为我们只固定了第 $i$ 位后面的符号，而其余 $n-2$ 个符号可以随便取，因此方案数是 $2^{n-2}$。特别地，最后一位后面没有符号，因此要乘 $2^{n-1}$。

注意 $n=1$ 特判。
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+(ch&15),ch=getchar();
    return x;
}
const int p=1000000007,inv2=500000004;
int qp(int x,int y)
{
    int res=1;
    for(int now=x; y; now=now*now%p,y>>=1) (y&1)&&(res=res*now%p);
    return res;
}
int a[100003],pre[100003];
signed main()
{
    int n=read();
    if(n==1) printf("%lld\n",read()),exit(0);
    int t=qp(2,n-2),ans=0;
    for(int i=1; i<=n; ++i) a[i]=read();
    pre[0]=1;
    for(int i=1; i<=n; ++i) pre[i]=a[i]*(pre[i-1]+1)%p*inv2%p,ans=(ans+pre[i])%p;
    ans=(ans+pre[n])%p;
    printf("%lld\n",ans*t%p);
    return 0;
}
```

---

