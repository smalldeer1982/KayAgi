# [NWRRC 2015] Distribution in Metagonia

## 题目描述

在梅塔戈尼亚国有一百个贵族家庭，每年这些家庭中的一些会从“唯一者”的先知那里收到几个仪式立方体。“唯一者”对立方体的分配有几个规则：如果一个家庭收到至少一个立方体，那么收到的立方体数量的所有质因数应该是 $2$ 或 $3$。此外，如果一个家庭收到 $a > 0$ 个立方体，而同一年另一个家庭收到 $b > 0$ 个立方体，那么 $a$ 不应该能被 $b$ 整除，反之亦然。

你是“唯一者”的先知。你提前知道未来 $t$ 年将有多少立方体可供分配。你想为这些年中的每一年找到任何有效的立方体分配方案。每年你必须分配掉该年所有可用的立方体。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
1
2
3
10
```

### 输出

```
1
1
1
2
1
3
2
4 6
```

# 题解

## 作者：VitrelosTia (赞：4)

假设第 $i$ 家分到了 $2^{x_i} \times 3^{y_i}$ 块，由于互相不能整除，那么对于两家 $i,j$，$x_i, x_j$ 和 $y_i, y_j$ 的大小关系是不同的，那不妨让 $x$ 单调递增，$y$ 单调递减。

将 $n$ 分解为 $a \times 2^x \times 3^y$ 的形式。为了使 $y$ 单调递减，我们找到最大的 $k$ 满足 $3^k \le a$，此时还剩 $n - 2^x \times 3^{q+k} = (a - 3^k) \times 2^x \times 3^y $，再去做右边的式子，由唯一分解定理显然有 $a \equiv 3^k \equiv 1 \pmod{2}$，所以 $2 \mid a - 3^k$，于是剩下的个数中 $x$ 是会增加的。那么这就满足了 $x$ 单增，$y$ 单减的条件。

实现的时候，每次先同时求出 $a$ 和 $2^x \times 3^y$，然后找 $3^k$，就可以更新 $a$ 了。$2^x \times 3^y$ 由之前贡献的更新过来，再补上现在 $a$ 的贡献。

```cpp
ll n; 
vector <ll> ans;
void solve() {
	ans.clear();
	cin >> n;
	ll now = 1; // 2^x * 3^y
	while (n) { // n 实际上是 a
		ll m = 1; // 3^k
		while (n % 2 == 0) now *= 2, n /= 2;
		while (n % 3 == 0) now *= 3, n /= 3;
		while (m * 3 <= n) m *= 3;
		ans.push_back(now * m);
		n -= m;
	}
	cout << ans.size() << '\n';
	for (auto x : ans) cout << x << ' ';
	cout << '\n';
}
```

---

## 作者：Sheep_YCH (赞：3)

## 洛谷 P7051
[题目传送门](https://www.luogu.com.cn/problem/P7051)
## 题目大意
给定一个整数 $n$，将 $n$ 分解成若干个只含质因数 $2$ 和 $3$ 的数的和，并且两两之间没有倍数关系。
## 题目分析
在分析之前，先介绍一下什么是**质因数**。

质因数（素因数或质因子）：指能整除给定正整数的质数。

例如 $2$ 是 $4$ 的质因数，而不是 $9$ 的质因数。

知道了什么是质因数，就可以来分析这道题了。

1. 如果某年一个家庭收到 $m$ 个小方块，则 $m$ 的质因数只能是 $2$ 和 $3$。
2. 如果某年有一个家庭收到了 $a$ 个小方块，另一个家庭收到了 $b$ 个小方块，则 $a$ 不整除 $b$，$b$ 不整除 $a$。

观察 $1$，不难得出 $m$ 可以表示成 $2^x×3^y$。

观察 $2$，发现 $a$ 和 $b$ 互质。我们可以让接下来要找的数的 $2$ 的幂次单调递增。$3$ 的幂次单调递减。或者反之。

对于当前的 $n$，我们从中拆出的数 $num = 2^x×3^y$ ，并且一定要满足 $2^x$ 能整除 $n$ 且 $y$ 最大。则 $n$ 变成 $n - num$。然后继续拆分 $n - num$ 直到 $n = 0$ 。观察 $n - num$，发现 $n - num$ 是偶数，并且至少含有 $(x+1)$ 个 $2$ 的积，即 $n - num$ 的 $2$ 的次幂大于 $x$，$3$ 的幂次小于 $y$。这样就满足接下来的数的 $2$ 的幂次单调递增，$3$ 的幂次单调递减。

接下来再用上述结论推出 $n = 2^x×3^y + 2×2^x… = 2^x(3^y + 2…)$。$num$ 表示公式的前边部分，$n - num$ 表示公式的后面部分。

至此，本题结束。
## Code

```cpp
#include <iostream>
using namespace std;
long long tmp, tn, ans[1005];//注意本题要开long long
int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(0);//关闭同步流
	
	long long t;
	cin >> t;
	while(t --) {
		long long n, num = 0;
		cin >> n;
		while(n > 0) {
			tmp = 1;
			tn = n;
			while(tn && tn % 2 == 0) tmp *= 2, tn /= 2;//或者改成 while(tn && tn % 3 == 0) tmp *= 3, tn /= 3;
			while(tmp * 3 <= tn) tmp *= 3;//或者改成 while(tmp * 2 <= tn) tmp *= 2;
			n -= tmp;
			ans[++num] = tmp;
			
		}
		cout << num << "\n";
		for(int i = 1; i <= num; i ++) cout << ans[i] << " ";
		cout << "\n";
	}
	
	return 0;
}
```
~~完结散花o(*￣▽￣*)ブ~~

**upd：** $2024.8.21$ 修改了格式错误。

---

## 作者：bellmanford (赞：3)

每个数一定是 $2^a\times 3^b$ 的形式，如果要满足不存在两个数存在整除关系，那么就不能有一个数的 $a,b$ 非严格大于另一个数的 $a,b$ 。

考虑从一边入手，接下来找的数在 $2$ 的幂次要求单调递增， $3$ 的幂次要求单调递减，那么对于一个数 $n$ ，找到一个数 $2^a\times 3^b$ ，一定要满足 $n-2^a\times 3^b \equiv 0 \pmod{2^a}$ ，因为 接下来选的数都是 $2^a$ 的倍数，如果不满足就一定不可能凑齐。

由于 $3^b$ 是个奇数，所以每次选到最大的 $a$ 使得 $2^a|n$ ，然后取到在这个 $a$ 下最大的 $b$ ，这样就可以满足 $b$ 的单调递减了。

```cpp
int Ans[105];
void solve(){
	int n=read(),mi2=1;
	Ans[0]=0;
	while(n>0){
		while(n%(mi2*2)==0) mi2=mi2*2;
		int mi3=mi2;
		while(mi3*3<=n) mi3*=3;
		n-=mi3;
		Ans[++Ans[0]]=mi3;
	}
	printf("%lld\n",Ans[0]);
	for(int i=1;i<=Ans[0];i++) printf("%lld ",Ans[i]);
	printf("\n");
}
```

---

## 作者：U•ェ•*U (赞：1)

## 思路

拆分每个数，发现一定可以拆成 $2^x \times 3^y \times a$ 的样子。

那么我们可以找到一个指数 $t$ 使得 $3^t \lt a \lt 3^{t+1}$，那么 $ans = 2^x\times 3^{y+t} + 2^x \times3^y\times (a-3^t)$。

对了，对于每次操作，选取 $\max\ a$ 使得 $a^2\ \mid\ n$，然后选取 $a$ 下的 $\max b$，就满足单调递减了。

## 核心代码

```cpp
while (n) {
	base = 1ll;
	while (!(n % 2)) tmp *= 2, n /= 2;
	while (!(n % 3)) tmp *= 3, n /= 3;
	while (base * 3 <= n) base *= 3;
	ans[++ cnt] = tmp * base, n -= base;
}
```

---

## 作者：joker_opof_qaq (赞：0)

## 题目大意：
给定一个整数 $n$，将 $n$ 分解成若干个只含质因数 $2$ 和 $3$ 的数的和，并且都不含没有倍数关系。

## 思路 && 实现

设两数为 $2^a  \times 3^b$ 和 $2^c \times 3^d$，如果含有倍数关系，当且仅当 $a \ge c$ 且 $b \ge d$。所以只能构造使得这两个条件仅能满足一个。

所以让 $a$ 开始设置为最大，$b$ 设置为最小，在过程中使得 $a$ 不断变小，$b$ 不断增大，不会出现倍数情况。

---

## 作者：Amunet (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7051)
# 题目大意：

给定一个整数 $n$，将 $n$ 分解成若干个只含质因数 $2$ 和 $3$ 的数的和，并且都不含没有倍数关系。

# 思路分析：

因为每次分出了 $2^a \times 3^b$，所以第一次取数在剩余的数量 $N$ 可以最多取出的 $2$，让 $a$ 最初尽可能的大，而 $b$ 尽可能的小。

不难发现 $a$ 不断变小，$b$ 不断变大。不会出现倍数情况。

我们不断通过这样的过程，直到把 $N$ 分解完成即可。

---

## 作者：XIxii (赞：0)

### 题意：

   给定一个 $N$ ，让你把它拆成若干个只含素因子 $2$ 和 $3$ 的数之和，且两两之间没有倍数关系。

### 思路：

   是 $2$ 的因子的幂递增，$3$ 的因子的幂递减；或者反之。

   对于当前的 $N$ ，我们拆分出的数为  $num = 2^x \times 3^y$ ；同时满足 $2^x \mid N$ ，而且 $y$ 最大，然后继续拆分 $N - num$ 。不难推出， $N - num$为偶数，且至少含有 $x + 1$ 个 $2$ 之积，那么 $N - num$的 $2$ 的幂一定大于 $x$ ；而 $3$ 的幂一定小于 $y$ 。
   
   用公式不难推出 $N  = 2^x (3^y + 2 \times ....)$ 。  $num$ 等于前面部分，$N-num$ 等于后面部分，$2$ 因子至少多出来一个，而 $3$ 因子肯定会变少。
   
### 代码：

```
#include <bits/stdc++.h>
using namespace std;
int T; 
long long n,tmp,tn;
long long ans[1000010],num;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n; 
        num=0; 
        while(n)
        {
            tmp=1; 
            tn=n;
            while(tn && tn%2==0)  
            {
                tmp*=2;
                tn/=2;
            }
            while(tmp*3<=n) 
            {
                tmp*=3;
            }
            n-=tmp; 
            ans[++num]=tmp;
        }
        cout<<num<<endl;
        for(int i=1;i<=num;i++) 
        {
            cout<<ans[i]<<" "; 
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：smydahaoren (赞：0)

### 题目大意：

这道题基本意思就是给定一个整数 $n$，要求把这个整数分成尽可能多个互不整除的数，每个数的质因数只有 $2$ 和 $3$。

### 基本思路：

因为每次分出了 $2^a\times3^b$，所以第一次取数在剩余的数量 $n$ 可以最多取出的 $2$ 就会导致 $a$ 最初可以保证尽可能大，而 $b$ 尽可能的小。不断重复这个过程就可以发现 $a$ 在不断变小，$b$ 在不断变大，这样也就可以实现每个数之间互相不整除。

```
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define antirep(i,a,b) for(int i=a;i>=b;i--)
#define speed ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6;
int t,a,ans[N],cnt;
signed main(){
	speed;
	cin>>t;
	while(t--){
		cin>>a;
		memset(ans,0,sizeof(ans));
		cnt=0;
		while(a>0){
		int tmp1=1,tmp2=1;
			while(a%(tmp1*2)==0)tmp1*=2;
			tmp2=tmp1;
			while(tmp2*3<a)tmp2*=3;
			a-=tmp2;
			ans[cnt]=tmp2;
			cnt+=1; 
		}
		cout<<cnt<<endl;
		rep(i,0,cnt-1) cout<<ans[i]<<" ";
		cout<<endl;
	} 
	return 0;
}

```

---

## 作者：Flaw_Owl (赞：0)

# P7051 [NWRRC2015] Distribution in Metagonia 题解

原题链接：[P7051 [NWRRC2015] Distribution in Metagonia](https://www.luogu.com.cn/problem/P7051)。

## 题目分析

### 抽象数学模型

分析原题目的情景，我们可以将其抽象成数学模型。

> 每年，这些贵族家庭都要收到来自先知之首的若干个典礼用的小方块。

假设小方块共有 $N$ 个，分配给 $n$ 个家庭，每个家庭收到 $x_i$ 个小方块（$1 \leq i \leq 100$），那么有 $\sum_{i = 1}^n x_i = N$。

> 如果某年有一个家庭收到了小方块，那么这个家庭所收到的小方块的个数的**质因数只能是 $2$ 和 $3$**。

假设该家庭收到了 $x_i$ 个小方块，那么**有 $x = 2^{a_i} \times 3^{b_i}$**，其中 $a_i,b_i$ 都是自然数。

> 如果某年有一个家庭收到了 $a > 0$ 个小方块，同年另一个家庭收到了 $b > 0$ 个小方块，那么 **$a$ 不整除 $b$，$b$ 也不整除 $a$**。

对于任意的 $1 \leq i,j \leq n$，都有 **$2^{a_i - a_j} \times 3^{b_i - b_j}$ 不为整数**。

> 现在，你作为先知之首，你知道你接下来的 $t$ 年中，你每年有多少个小方块。你现在想要找到任意一个可行的方案，以便在接下来 $t$ 年中能够进行按规则分配。

对于接下来的 $t$ 组数据，每年给定小方块个数 $N$（$1 \leq N \leq 10^{18}$），求分配方案。

### 分析思路

在上文中我们已经将原题拆解成了多个信息，接下来我们逐个进行解决。

首先，对于任意的 $1 \leq i,j \leq n$，都有 $2^{a_i - a_j} \times 3^{b_i - b_j}$ 不为整数。这意味着 $a_i - a_j$ 和 $b_i - b_j$ **至少有一组是负数**。考虑到最后的结果应该为一个整数，那么这两组代数式应该**只有一组是负数**。

不妨令 $a_i - a_j$ 始终为负数， $b_i - b_j$ 始终为正数。也就是说，$a_i < a_j$ 是恒成立的，即 $a_i$ 单调递增。同理，$b_i$ 单调递减。

分析过程，假设我们已经找到了一个组合 $(a,b)$，那么接下来就是在剩下的数 $N - 2^a \times 3^b$ 中继续找下一个组合。这个数 $N - 2^a \times 3^b$ 有什么特点呢？考虑到上面提到 $a,b$ 的单调性，下一个组合可以写成 $(a+p,b-q)$ 的形式（其中 $p,q$ 都是自然数），即下一个数是 $2^{a+p} \times 3^{b-q} = 2^a \times 2^p \times 3^{b-q}$，它一定是 $2^a$ 的倍数。

更数学的，我们可以写成 $N - 2^a \times 3^b \equiv 0 \pmod {2^a}$，它等价为 $N \equiv 2^a \times 3^b \pmod {2^a}$，即 $N$ 一定是 $2^a$。请注意，这里的 $N$ 是相当于每一次分解而言的，并不是总和。

我们假设在一次分解中，当前的数字是 $N$，我们预备将其分解成 $2^a \times 2^b$ 的形式，而 $N$ 必然是 $2^a$ 的倍数。我们不妨**先枚举 $a$ 的大小，找到能取到最大的 $a$，再枚举范围内能取到最大的 $b$**，这样我们就得到了当次的分解结果 $2^a \times 2^b$。显然，下一次的 $a$  会比这一次更小，这使得 $a$ 单调递减（换个方向看也就是上面提到的单调递增，下同），而因为 $2^a$ 的减小，$b$ 相应的也会取得更大，也满足条件。

我们不断通过这样的过程，直到把 $N$ 分解完成即可。

## 程序实现

我们直接用程序模拟出上面的操作，注意开 `long long` 存储数据。值得注意的是，我们并不用完全按照上面的“枚举”思想枚举除 $a$ 的大小，详情参见代码部分。

```cpp
#include <iostream>
#include <cctype>
#define ll long long

using namespace std;

ll read()
{
    ll x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 105;

int T;
int tot;
ll N;

ll ans[maxN];

int main()
{
    T = read();
    while (T--)
    {
        N = read();
        tot = 1;
        while (N > 0)
        {
            ll temp = 1; // 当次分解的 2^a
            while (N % (temp * 2) == 0)
                temp *= 2;
            ll now = temp;
            while (now * 3 < N)
                now *= 3;
            N -= now;
            ans[tot++] = now;
        }
        printf("%d\n", tot - 1);
        for (int i = 1; i < tot; i++)
            printf("%lld ", ans[i]);
        printf("\n");
    }
}
```

---

