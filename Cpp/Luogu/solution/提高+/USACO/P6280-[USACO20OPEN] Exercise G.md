# [USACO20OPEN] Exercise G

## 题目描述

Farmer John（又）想到了一个新的奶牛晨练方案！  
如同之前，Farmer John 的 $N$ 头奶牛站成一排。对于 $1\le i\le N$ 的每一个 $i$，从左往右第 $i$ 头奶牛的编号为 $i$。他告诉她们重复以下步骤，直到奶牛们与她们开始时的顺序相同。

给定长为 $N$ 的一个排列 $A$，奶牛们改变她们的顺序，使得在改变之前从左往右第 $i$ 头奶牛在改变之后为从左往右第 $A_i$ 头。  
例如，如果 $A=(1,2,3,4,5)$，那么奶牛们总共进行一步。如果 $A=(2,3,1,5,4)$，那么奶牛们总共进行六步。每步之后奶牛们从左往右的顺序如下：

0 步：$(1,2,3,4,5)$  
1 步：$(3,1,2,5,4)$  
2 步：$(2,3,1,4,5)$  
3 步：$(1,2,3,5,4)$  
4 步：$(3,1,2,4,5)$  
5 步：$(2,3,1,5,4)$  
6 步：$(1,2,3,4,5)$  
**求所有正整数 $K$ 的和，使得存在一个长为 $N$ 的排列，奶牛们需要进行恰好 $K$ 步。**

由于这个数字可能非常大，输出答案模 $M$ 的余数（$10^8\le M\le 10^9+7$，$M$ 是质数）。

## 说明/提示

#### 样例解释：

存在排列使得奶牛需要进行 $1$、$2$、$3$、$4$、$5$ 以及 $6$ 步。因此，答案为 $1+2+3+4+5+6=21$。

-----

对于 $100\%$ 的数据，$1\le N\le 10^4$。

共 $10$ 个测试点，其中 $1$ 为样例，其余性质如下：

测试点 $2\sim 5$ 满足 $N\le 10^2$。  
测试点 $6\sim 10$ 没有额外限制。 

----- 

出题人：Benjamin Qi

## 样例 #1

### 输入

```
5 1000000007```

### 输出

```
21```

# 题解

## 作者：rouxQ (赞：17)

首先这题和[P4161](https://www.luogu.com.cn/problem/P4161)几乎一模一样，（P4161要求k的个数，本题求所有k的和），~~所以双倍经验~~

然后我们来看这题，可以发现如果循环了几次可以回到原地，当且仅当形成了一个环，假如设每个环的长度是 $a_i$，那么可以发现 $k=\operatorname{lcm}a_i$，又知道 $\operatorname{lcm}$ 其实就是将那几个数分解质因数，然后取每个质数的**最高次幂乘起来**，所以我们可以想到枚举素数来做dp。

我们设 $f(i,j)$ 表示前 $i$ 个素数总和为 $j$ 的所有 $k$ 的总和，枚举第 $i$ 个素数的幂进行转移，因为之前并没有用过第 $i$ 个素数，所以应把上一个状态乘上 $p_i^k$，所以直接有方程 $f(i,j)=\sum f(i-1, j-p_i^k)\times p_i^k$

接着发现这个东西可以滚动数组压缩一下，于是可以省掉一维 $f(j)=\sum f(j-p_i^k)\times p_i^k$，倒序枚举即可，初始状态 $f(0)=1$，最后答案是 $\sum f(i)$

代码
```cpp
#include <bits/stdc++.h>
#define ll long long//注意开long long
using namespace std;
const int N = 1e4 + 3;
bool vis[N]; vector<int> p;
ll f[N] = {1}, m;int n;
int main (){
    p.push_back(0);//让素数的下标从一开始，使后面的转移更简洁
    cin >> n >> m;
    for (int i = 2; i <= n; i++){
        if (!vis[i])p.push_back(i);
        for (int j = i * i; j <= n; j += i)vis[j] = 1;
    }//埃筛筛素数
    for (int i = 1; i < p.size(); i++)
        for (int j = n; j >= p[i]; j--){
            int tmp = p[i];
            while(tmp <= j)
                f[j] = (f[j] + f[j - tmp] * tmp % m) % m, tmp *= p[i];
        }
    ll Ans = 0;
    for (int i = 0; i <= n; i++)Ans = (Ans + f[i]) % m;
    cout << Ans << endl;
    return 0;
}

```

---

## 作者：Tony102 (赞：10)

[Link](https://www.luogu.com.cn/problem/P6280)


[更好的阅读体验](https://tony102.xyz/index.php/2021/05/28/luogu6280-usaco20openexercise-g/)


### Sol

感觉题面写的不是很清楚,原以为是翻译的问题,结果发现是英文原题面就写的很垃圾.给 Benjamin Qi 倒一杯卡布奇诺

个人理解困难的地方在于样例解释 $0$ 步的位置, 但是反过来一想如果按照我的想法(初始排列和 $A$ 一模一样) 的话那么答案就都是 $0$ 了.

首先可以猜一波东西, 要确定两个排列,一个是原排列(也就是初始位置的排列) 和 $A$ 排列(位置每次从 $i$ 变到 $A_i$) 是比较麻烦的. 先猜想应该答案跟原排列没有什么关系, 测试一下发现是对的.也就是说, 影响答案的只有这个 $A$ 排列.

再来观察 $A$ 排列每次是怎么影响每一个数的位置的.比如说现在有原排列 `1 2 3 4 5 ` 和 $A$ 排列 `2 3 4 5 1`. 你可以发现每一个位置的改变就像一个环.每一个数位置都会在这个环中持续地改变.那么要使这个排列变回原来的排列,应当是变化中所有环有一次正好同时变完一个周期时就回到了原排列.

形式话地,我们记变化过程中所有环的长度为 $c_i$ ,那么首先 $\sum c_i = n$  . 再者,有 $lcm_{c_i} = k$ 

解释一下为什么是 $lcm_{c_i}$ . 最简单形式的 $k$ 肯定可以被表示为 $k = \prod c_i$ , 假如 $\exist\ gcd(c_i, c_j) > 1$ , 那么 $k \div gcd(c_i,c_j)$  肯定可以变得更小, 也就是有更小的 $c_i$ 满足. 所以就是 $lcm_{c_i}$

根据算数基本定理, $lcm$ 就是取唯一分解后相同质数的最高次幂的乘积.现在就是要对 $n$ 进行分解,计算有多少中这样的分解.(这就是[P4161](https://www.luogu.com.cn/problem/P4161)) 并且同时计算一下和.

那么设 $f_{i,j}$ 表示前 $i$ 个质数和为 $j$ 的答案就可以了吧.转移的时候把当先选中的质数给它乘上去就可以了.肉眼可见 $f_i$ 的状态只会由 $f_{i-1}$ 转移过来.直接滚掉一维就可以了吧



### Code

**[Code](https://tony102.xyz/index.php/2021/05/28/luogu6280-usaco20openexercise-g/)**



---

## 作者：hhhyyyfff (赞：9)

- 题意简述：  
  已知 $N,M\ (1 \le N \le 10^4,10^8 \le M \le 10^9+7,M\text{为质数})$。  
  有一个操作：给出两个排列 $\{a_i\},\{b_i\}$，得出一个排列 $\{c_i\}$，其中 $c_i=a_{b_i}$，最后 $a \gets c$。  
  初始的排列 $a$ 为 $(1,2,3,\dots,N)$，有一个排列 $(p_1,p_2,p_3,\dots,p_N)$，对 $\{a_i\},\{p_i\}$ 反复进行操作，直到排列 $a$ 又一次变成 $(1,2,3,\dots,N)$，记操作次数为 $K$。  
  对于所有的排列 $\{p_i\}$，求有多少种 $K$ 是可能的，答案对 $M$ 取模。

- 前置知识：DP，筛法

- 算法分析 $O(N^2 \times \text{小常数})$：  
  对于给定的排列 $p$，题目中的**操作**次数可以这样求：将排列 $p$ 拆分成几个部分，每个部分 $S$ 满足 $\forall i \in S, p_i \in S$，且不可再拆分。答案可表示为 $|S_i|$ 的最小公倍数。  
  例如 $p=(2,5,4,3,1)$，$(2,5,1)$ 为一部分 $(4,3)$ 为另一部分。  
  因此，我们只需要枚举 $|S_i|$ 即可，题目变成枚举 $N$ 的拆分。对于合数 $a=p_1^{c_1}p_2^{c_2} \dots p_n^{c_n}$, 对**最大公倍数**（即答案）的贡献等价于 $p_1^{c_1},p_2^{c_2},\dots,p_n^{c_n},1,1,\dots,1$（$a-\sum p_i^{c_i}$的部分用 $1$ 补全）。又因为，$1$ 对答案实际没有贡献，所以只需对 $1,2,\dots,N$ 分别用**质数**拆分。  
  例如 $N=6$，分别对 $1,2,3,4,5,6$ 用质数进行拆分。对 $5$ 的拆分有 $2+3$；对 $6$ 的拆分有 $2+2+2$ 和 $3+3$。  
  设 $f_{i,j}$ 表示对 $i$ 用质数拆分，最大的质数不超过 $p_j$，答案（$K$ 的可能数）为 $f_{i,j}$。$f_{i,j}$有两个来源：$f_{i,j-1}$ 即最大的质数小于 $p_j$ 的方案；$f_{i-kp_j,j-1}$ 即最大质数为 $p_j$，枚举这个质数在拆分中的数量 $k$。 $f_{i,j}=f_{i,j-1}+\sum f_{i-kp_j,j-1}$。  
  这样能保证不漏（所有方案都能用质数拆分表示）不重（不同的质数拆分积不同，即 $K$ 不同）。

- 代码：

``` cpp
#include <cstdio>

using namespace std;

int N, M, ans, cnt, f[10010][1300];
long long p[1300];
bool v[10010];

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    scanf("%d%d", &N, &M);
    for (int i = 2; i <= N; ++i)
        if (!v[i]) {
            p[++cnt] = i;
            for (int j = i; i * j <= N; ++j) v[i * j] = 1;
        }
    for (int i = 0; i <= cnt; ++i) f[0][i] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= cnt; ++j) {
            f[i][j] = f[i][j - 1];
            for (long long k = p[j]; k <= i; k *= p[j])
                f[i][j] = (f[i][j] + f[i - k][j - 1] * k) % M;
        }
        ans = (ans + f[i][cnt]) % M;
    }
    printf("%d\n", (ans + 1) % M);
    return 0;
}
```

---

## 作者：_zy_ (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/P6280)

题目大意：

对于所有用来变换的序列，求变换次数K可能的和。

### $Subtask1$：

~~虽然你们会觉得这很没有必要~~

$dfs$ 全排列找到每一种情况，求出所有的 $K$，然后加和。

```cpp
int Solve()
{
	int cnt=0;
	do {
		for(int i=1;i<=n;i++)
			b[a[i]]=c[i];
		for(int i=1;i<=n;i++)
			c[i]=b[i];
		cnt++;
	} while(!Judge());
	return cnt;
}
void dfs(int x)
{
	if(x==n+1) {
		int tmp=Solve();
		if(used[tmp])	{
			return ;
		}
		cout<<tmp<<endl;
		used[tmp]=1;
		ans+=tmp;
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(v[i])	continue;
		v[i]=1;
		a[x]=i;
		dfs(x+1);
		v[i]=0;
	}
}
```

可以用来过样例和~~拿去打表~~

### $subtask2-10$:

假设找到的重复区间长度是 $L_i$ ,那么 $K$=$Lcm$（$L_i$).

**关于 $Lcm$,质因数分解,对于每一个因数的最高次幂相乘即为 $Lcm$**

显然当这些所有的 $L_i$ 之和应该小于等于总长度 $n$.

于是我们就可以找到 $1,2,3,4...n$ 的作为和可能 $K$ 的加和。

先预处理除所有的素数。	[不会请左转](https://www.luogu.com.cn/problem/P3383)

跑完全背包，将质数看做物品，和为 $i$ 时就是 $f[i]$ ，也即可能的 $K$ 和。

- **状态转移**
```cpp
while(k<=j) 
{
	f[j]+=f[j-k]*k;
	f[j]%=mod;
	k*=p[i];
}

```
- $ans$ 取所有 $f_i$ 的和.

刚刚我们说过，$f_i$ 为所有可能因数和的 $K$ 的和。

$ans$ 不要忘记 $+1$

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define int long long 
#define R register
#define N 10010
using namespace std;
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int n,mod,cnt,ans;
int p[N],f[N];
bool v[N];
signed main()
{
	n=re(); mod=re();
	for(R int i=2;i<=n;i++) {
		if(!v[i]) 	p[++cnt]=i;
        for(R int j=1;j<=cnt&&i*p[j]<=n;j++) {
        	v[i*p[j]]=1;
        	if(i%p[j]==0)	break;	
		}
    }
	f[0]=1;
	for(R int i=1;i<=cnt;i++)
	for(R int j=n;j>=p[i];j--)
	{
		int k=p[i];
		while(k<=j) {
			f[j]+=f[j-k]*k;
			f[j]%=mod;
			k*=p[i];
		}
	}
	for(int i=1;i<=n;i++)
		ans+=f[i],ans%=mod;
    cout<<ans+1<<endl;
}
```

如有不妥，请不要吝啬您的评论。

-----
[双倍经验](https://www.luogu.com.cn/problem/P4161)

---

## 作者：devout (赞：4)

我看到这道题：

~~这不是[原题](https://www.luogu.com.cn/problem/P4161)改了个问法吗~~

然后就顺利的$10min$切掉了这题。。。

显然我们可以看出来，一个变换方法走多少次能变回原来的序列，就是这个序列建图之后的每个环的$\operatorname{lcm}$，比如说对于题目中给出的变换方法，$1,2,3$就构成了一个环$1-3-2-1$，$4,5$构成一个环$4-5-4$，$\operatorname{lcm}(2,3)=6$，所以他走六次就能变回原来的

那么怎么统计这个东西呢？

我们发现，最后的环的长度和一定是$n$，而对于长度为$1$的环，我们可以不管他

那么考虑$dp$

- 状态：我们用$dp_{i,j}$用了前$i$个质数表示所有**长度不为1**的环的和为$j$的时候的答案

- 初值：显然是$dp_{0,0}=1$

- 转移：我们可以考虑枚举每一个质数$p$，那么因为此前没有出现过$p$，所以把前面的每一种情况接上一个$p^k$的时候，答案一定$\times p^k$，所以我们可以推出一个转移方程

$$dp_{i,j}=\sum_{k=prime_i}^{k\leq n}dp_{i-1,j-k}\times k,j\geq k$$

$\ \ \ \ \ $然后我们发现这就是一个背包问题，所以$i$那一维可以扔掉

- 答案：$\sum_{i=0}^n dp_{n,i}$

注意要判断$j\geq k$才能转移，在$usaco$上没错因为~~评测机比较高级~~，但是在$luogu$上没判就会$wa+re$。。。

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

# define int long long

int n,m,ans;
int f[N];
int prime[N],tot;
bool isp[N];

signed main()
{
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);
    memset(isp,1,sizeof(isp));
    read(n),read(m);
    Rep(i,2,n){
        if(isp[i])prime[++tot]=i;
        for(int j=1;j<=tot&&i*prime[j]<=n;j++){
            isp[i*prime[j]]=false;
            if(i%prime[j]==0)break;
        }
    }
    f[0]=1;
    Rep(i,1,tot)
        _Rep(j,n,prime[i])
            for(int k=prime[i];k<=n;k*=prime[i])
                if(j>=k)f[j]+=f[j-k]*k%m,f[j]%=m;
    Rep(i,0,n)ans=(ans+f[i])%m;
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：2008verser (赞：2)

题意见[题面](https://www.luogu.com.cn/problem/P6280)。

- 发现由若干个环组成。设 $m$ 个环，环 $i$ 长度 $len_i$，有 $\sum len_i=n$，同时 $Ans=\text{lcm}\{len_i\}$。

问题转化为将整数 $n$ 拆成 $n=\sum len_i$，求 $\text{lcm}\{len_i\}$ 全部可能取值和。

---

- 结论：若 $p$ 是一个质数集（算上 $1$），$c$ 是自然数集，$|p|=|c|=m$。那么

$$ 
\forall i\in[1,m],len_i=p_i^{c_i}
$$ 

这一类拆分，囊括了全部答案。

---

- 证明：若存在一种划分的 $len_j$ 不符合上述条件，记 $len_j$ 有 $k$ 个不同的质因数。

那么可以把 $len_j$ 拆成 $k$ 个符合上述条件的环，对 $\text{lcm}$ 影响不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/f805zqkt.png)

而且容易证明拆出来的 $k$ 个环总长度不大于 $len_j$（$a,b\geq2\to ab\geq a+b$）。

就归到了那一类拆分里了。多余的空位填 $1$。

---

- 有了结论，解法就很显然了。

设 $f_{i,j}$ 表示枚举到质数 $i$，$(\sum_{j=1}^i len_j)=j$ 的全部可能的 $\text{lcm}$ 的和。

枚举第 $i$ 个质数 $s_i$ 次数 $k$，这次的 $\text{lcm}$ 就是上次的乘上 $s_i^k$：
$$ 
f_{i,j}=\sum_{s_i^k\leq j}f_{i-1,j-s_i^k}\times s_i^k
$$ 
滚动一下即可。

---

- 因为这里并没有考虑 $len=1$ 的情况。也就是 $\forall i\leq n$，$f_{s.len,i}$ 都是合法的。

$$ 
Ans=\sum_{i=0}^{n} f_{s.len,i}
$$ 

---

```c++
#include<bits/stdc++.h>
#define rg register
#define ll long long
using namespace std;
const int N=1e4+5;
int n,bz[N],sl;
ll mod,ans,f[N],s[N];
int main() {
//	freopen("exercise.in","r",stdin),freopen("exercise.out","w",stdout);
	scanf("%d%lld",&n,&mod);
	for(int i=2;i<=n;i++) {
		if(!bz[i]) s[++sl]=i;
		for(int j=1;s[j]*i<=n;j++) {
			bz[s[j]*i]=1;
			if(i%s[j]==0) break;
		}
	}
	f[0]=1;
	for(int i=1;i<=sl;i++) {
		for(int j=n;j>=s[i];j--) {
			ll sik=s[i];
			while(sik<=j) {
				f[j]=(f[j]+f[j-sik]*sik)%mod;
				sik*=s[i];
			}
		}
	}
	for(int i=0;i<=n;i++) ans=(ans+f[i])%mod;
	printf("%lld",ans);
}
```

---

结论是解题的重点。很多题解都一笔带过了。

---

## 作者：Purslane (赞：2)

## Solution

我们首先将每个数和他要变成的位置连接起来 , 会形成一个图 .

[![bofzOH.png](https://s1.ax1x.com/2022/03/11/bofzOH.png)](https://imgtu.com/i/bofzOH)

题面中 $A=(2,3,1,5,4)$ 的图 . 题目所求的就是图中的点沿着出边走 , 走多少步全部回到起点 . 显然一个环上的点的最少步数就是就是这个环的长度 .

考虑到 **每个点出度和入度都是1** , 所以答案就是所有环长度的最小公倍数 .

我们设每个环的大小为 $\{B\}$ , 集合大小为 $k$ . 则必有 $\sum B_i = n$ .

设 $B_i$ 的唯一分解为 $\prod p_j^{a_{i,j}}$ , 那么答案是 $\prod p_i^{\text{max} \{ a_{i,j}\}}$ . 

我们抛开环大小等于 1 的环不管 , 其它的数的和不超过 $n$ . 枚举每一个素数 , 假设答案素数质数的集合为 $\{C\}$ . 则对于 $\forall i , a_i\le C_i$ . 为了有标志性 , 我们取**大小等于 1 的环外 , 其它的数的和最小的** $\{B\}$ **作为标志**  . 显然的 , 就是 $ \sum p_i^{C_i}$ . 即下文状态转移方程的 $j$ .

可以用 $f(i,j)$ 表示前 $i$ 个质数 , 总共用了 $j$ 个节点的 $k$ 的和 .
有 $f(i,j)=\sum f(i-1,j-p^k) \times p^k$ . 无需滚动数组 .

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e4+10,MAXM=1230;
int n,m,dp[MAXM][MAXN],vis[MAXN];
vector<int> pr;
void init(int MAX) {
	pr.push_back(0);
	ffor(i,2,MAX) {
		if(!vis[i]) pr.push_back(i);
		for(int j=1;j<pr.size()&&pr[j]*i<=MAX;j++) {
			vis[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
	return ;
}
signed main() {
	scanf("%lld %lld",&n,&m);
	init(n);
	dp[0][0]=1;
	ffor(i,1,pr.size()-1) {
		int base=pr[i];
		ffor(j,0,n) dp[i][j]=dp[i-1][j];
		while(base<=n) {ffor(j,base,n) dp[i][j]+=dp[i-1][j-base]*base,dp[i][j]%=m;base*=pr[i];}
	}
	int ans=0;
	ffor(i,0,n) ans+=dp[pr.size()-1][i],ans%=m;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：VioletIsMyLove (赞：2)

按照题目描述,实质就是每个环的节点个数的最小公倍数,再进行深入思考实质就是对于每个环的节点拆分质因子,


然后每个环的节点个数拆出来的质因子次幂最大的进行连乘得到一个可行的 $k$ ,最后在对这些 $k$ 进行求和。


再一个发现就是所有环里面节点个数相加肯定是 $N$ ,反过来说就是把N拆分为几个数字而已,那这不就是典型的01背包嘛 


 $F[i][j]$ 表示前 $i$ 个素数,和为j的所有 $k$ 的总和,枚举当前点质因子 $P[i]$ 的次幂，然后往袋子里面装这件物品,计算 $lcm$ 时 $*P[i]^(1,2,3,...)$ 
最后把 $F[i][j]$ 进行累计就是当前点一个 $k$ ,如果在计算的时候把前面点所有可行的 $k$ 进行累计,就可以一步到位了啊。

Code:

```cpp
#include<bits/stdc++.h>
#define maxn 10005
#define LL long long
using namespace std;
int N,p[maxn];
LL M,Ans,F[maxn];
bool vis[maxn];
LL read(){
	LL ret=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-')f=-f;ch=getchar();}
	while (isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return ret*f;
}
void make_p(){
	memset(vis,1,sizeof vis);
	vis[0]=vis[1]=0;
	for (int i=2;i<=sqrt(N);i+=(i&1)+1) if (vis[i])
	for (int j=2;j<=N/i;j++) vis[j*i]=0;
	for (int i=2;i<=N;i+=(i&1)+1)
	  if (vis[i]) p[++p[0]]=i;
}
int main(){
    N=read(),M=read();
    make_p();
    F[0]=1;
    for (int i=1;i<=p[0];i++)
    for (int j=N;j>=p[i];j--)
    for (int k=p[i];k<=j;k*=p[i])
      F[j]=(F[j]+F[j-k]*k%M)%M;
    for (int j=0;j<=N;j++) Ans=(Ans+F[j])%M;
    printf("%lld\n",Ans);
    return 0;
}
```


---

## 作者：Space_Gold_Trash (赞：1)

很有趣的一道题

我们可以发现

我们是在一个集合里面找循环节

因为我们可以发现对于一个排列$A$

那么将$A$种的循环部分拉出来搞成集合

并且循环长度为$len$

那么相当于我们对于将$A$的所有集合的循环长度即为所有$len$的$lcm$

然后我们就可以把问题转化成把$n$个数分成任意的集合,求对于所有集合的$lcm$为多少

但这样还是会难搞出来

我可以发现$len$是一个合数时,我们考虑它拆分成质数集合,再搞到答案上面去

但是我们发现这是错误的,发现答案质因数分解后最高幂为$1$

然后发现原因是分解成质数过后,那么它会把相同的质数过滤掉

怎么解决呢?

我们把相同的质数弄到一块去



然后就是背包搞一下即可

```
#include<bits/stdc++.h>
#define ll long long
#define N 10011
using namespace std;
int n;
int cnt,pri[N];
int prime[N];
ll f[N],m;
int main( ){
	int i,j;
	scanf("%d%lld",&n,&m);
	for(i=2;i<=n;++i){
		if(!prime[i]){
			prime[i]=i;
			pri[++cnt]=i;
		}
		for(j=1;j<=cnt&&pri[j]<=n/i;++j){
			prime[i*pri[j]]=pri[j];
			if(prime[i]<=pri[j])break;
		}
	}
	f[0]=1;
	int k;
	for(i=1;i<=cnt;++i){
		for(j=n;j>=pri[i];--j){
			k=pri[i];
			while(k<=j){
				f[j]=(f[j]+f[j-k]*k)%m;
				k=k*pri[i];
			}
		}
	}
	ll ans(0);
	for(i=0;i<=n;++i)
	ans=(ans+f[i])%m;
	printf("%lld\n",ans);
}
```

---

## 作者：FeelGood (赞：0)

观察题目的变换方式，我们发现会出现若干个数字在一起组成循环节，而循环节的长度就是数字的数量。

那么推理一下会发现要变回最开始的状态，所需要的步数定是所有循环节的长度的最小公倍数。知道了这个，我们就可以开始思考怎么进行下一步操作了。
   
题目要我们求所有 $k$ 的和，总共有 $n$ 个数，那么所有循环节长度相加肯定不会超过 $n$，那么我们可以考虑动态规划。

设 $dp_{i,j}$ 表示用前 $i$ 个素数，拼成的循环节长为 $j$，所有 $k$ 的总和。那么转移方程就是 $dp_{i,j} = \sum dp_{i - 1,j - p_{i}^{k}} \times p_{i}^{k}$，注意此处的 $k$ 为枚举第 $i$ 个素数的幂，结果就是对所有 $dp_{i,j}$ 求和。
   
再考虑优化，我们发现 $dp_{i,j}$ 可以使用滚动数组优化掉一维，只需要倒序进行第二维的枚举即可，那么状态转移方程就变为了 $dp_{j} = \sum dp_{j - p_{i}^{k}} \times p_{i}^{k}$，答案为 $\sum_{i = 1}^{n} dp_i$。
   
下面是代码

```cpp
#include <bits/stdc++.h>

#define ll long long
#define lll __int128

using namespace std;

namespace FastRead
{
	void read() {}

	template<typename T1, typename ...T2>
	void read(T1 &n, T2 &...m)
	{
		T1 op = 1;
		char c;
		while (isdigit(c = getchar()) == false)
			if (c == '-')
				op = -1;
		n = c - '0';
		while (isdigit(c = getchar()))
			n = (n << 1) + (n << 3) + c - '0';
		n *= op;
		read(m...);
	}
}

using FastRead::read;

namespace Solve
{
	const int MaxN = 1e4;
	
	bitset<MaxN + 10> vis;
	int pme[MaxN + 10], cntpme;
	
	void GetPme(int n)
	{
		vis[1] = true;
		for (int i = 2; i <= n; ++i)
		{
			if (vis[i] == false)
				pme[++cntpme] = i;
			for (int j = 1; j <= cntpme && i * pme[j] <= n; ++j)
			{
				vis[i * pme[j]] = true;
				if (i % pme[j] == 0)
					break;
			}
		}
	}
	
	ll dp[MaxN + 10];
	
	void Sol()
	{
		int n;
		ll m;
		read(n, m);
		GetPme(n);
		dp[0] = 1;
		for (int i = 1; i <= cntpme; ++i)
			for (int j = n; j >= pme[i]; --j)
				for (int h = pme[i]; h <= j; h *= pme[i])
					dp[j] = (dp[j] + dp[j - h] * h) % m;
		ll ans = 0;
		for (int i = 0; i <= n; ++i)
			ans = (ans + dp[i]) % m;
		printf("%lld\n", ans);
	}
}

using Solve::Sol;

int main()
{
	Sol();
	return 0;
}
```

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/121378917)

一道 DP 题，好像有人叫这类题为数论 DP？但是不就是一个质数吗。

首先我们观察到如果这堆奶牛想要回到原位，那么对应的 $a_i$ 一定会构成一个环。换言之，如果连边 $i \to a_i$，那么就会出现若干个环。

而如果需要恰好 $k$ 步回到原位，那么就需要所有环长的最小公倍数是 $k$。

显然最小公倍数肯定只与质数最高次幂有关系，于是我们可以考虑线筛 $[1,n]$ 的质数然后 DP 。

设 $f_{i,j}$ 表示选了前 $i$ 个质数和为 $j$ 时候的答案，那么有转移方程：

$$f_{i,j}=\sum_{p \leq p^q \leq j, q \geq 1}(f_{i-1,j-p^q} \times p^q)$$

这个的大意就是说因为这里选了 $p^q$ 的数，前面方案的和是 $f_{i-1,j-p^q}$，这些和在加入 $p^q$ 之后总贡献是相乘的。

初值是 $f_{0}=1$，因为 $k=1$ 也是可以的，只不过直接我们不会统计 $k=1$ 的答案，所以要初值。

- 其实 $k=1$ 的可行性题目中不是说的很清楚，$k=1$ 是因为 $a_i=i$ 时奶牛们动了一步，但是又全部呆在原地，~~动了但完全没动~~，此时也是算一种方案的。

Code：[GitHub CodeBase-of-Plozia P6280 [USACO20OPEN]Exercise G](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E5%B8%B8%E8%A7%81%20Trick/%E5%AF%B9%E7%B4%A0%E6%95%B0%20DP%20P6280%20%5BUSACO20OPEN%5DExercise%20G.cpp)

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:P6280 [USACO20OPEN]Exercise G
    Date:2021/11/17
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e4 + 5;
int n, m, f[MAXN], Prime[MAXN];
bool book[MAXN];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
    n = Read(), m = Read();
    for (int i = 2; i <= n; ++i)
    {
        if (!book[i]) Prime[++Prime[0]] = i;
        for (int j = 1; j <= Prime[0]; ++j)
        {
            if (i * Prime[j] > n) break ;
            book[i * Prime[j]] = 1;
            if (i % Prime[j] == 0) break ;
        }
    }
    f[0] = 1;
    for (int i = 1; i <= Prime[0]; ++i)
    {
        for (int j = n; j >= 0; --j)
        {
            LL tmp = Prime[i];
            while (j - tmp >= 0) { f[j] = (f[j] + 1ll * tmp * f[j - tmp]) % m; tmp = tmp * Prime[i]; }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) ((ans += f[i]) >= m) ? (ans -= m) : 0;
    printf("%d\n", ans); return 0;
}
```

---

## 作者：_Yoimiya_ (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/P6280)

解题思路
- 先看数据范围，$n \leq 10^4$ ，一眼 DP。考试的时候想到这里就不会了，考完试看了题解才恍然大悟。 

- 循环同一个步骤直到回到原地，定义其为一个循环节。假设每个循环节长度为 $x_i$，则 $k = \operatorname{lcm}x_i$。我们要做的就是枚举素数。  

- 先用埃氏筛筛一下素数（线性筛更好），随后进行 DP 。

- 定义 $f_{i,j}$ 为前 $i$ 个素数总和为 $j$ 的所有 $k$ 的和。枚举第 $i$ 个素数的幂，这样相当于枚举每个 $\operatorname{lcm}$，状态转移方程为：  $f_{i,j} = \sum (f_{i-1,j-p^k_i} \times p^k_i)$
    
- 我们可以发现 $i$ 这一维只用了 $i$ 和 $i - 1$，那就可以通过倒序 DP 或滚动数组优化掉。最终状态转移方程为：  $f_{j} = \sum (f_{j-p^k_i} \times p^k_i)$。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M(1e4+1);
#define int long long //标配 long long 
#define pb v.push_back(i)
bool vis[M];
vector<int> v;
int f[M]={1},Mod,n,ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>Mod;
	for(register int i(2);i<=n;++i){//简洁的埃氏筛 
		if(!vis[i]) pb;
		for(register int j(i*i);j<=n;j+=i) vis[j]=1; 
	}
	for(register int i(0);i<v.size();++i){//DP 
		for(register int j(n);j>=v[i];--j){
			int pos(v[i]);
			while(j>=pos){
				f[j]=(f[j]+f[j-pos]*pos%Mod+Mod)%Mod;//注意取模 
				pos*=v[i];
			}
		}
	}
	for(register int i(0);i<=n;++i) ans+=f[i],ans%=Mod;//统计，注意取模 
	cout<<ans;return 0;
}
```

---

## 作者：SymphonyOfEuler (赞：0)

作为Gold组的T3还是可以的。这题是一道DP题。

还是[双倍经验](https://www.luogu.com.cn/problem/P4161)。

我们看一下题目给的例子：

0 步：$(1,2,3,4,5)$

1 步：$(3,1,2,5,4)$

2 步：$(2,3,1,4,5)$

3 步：$(1,2,3,5,4)$

4 步：$(3,1,2,4,5)$

5 步：$(2,3,1,5,4)$

6 步：$(1,2,3,4,5)$

从这个里面可以发现操作$6$次之后回到了原来的样子，所以这个是有循环规律的，形成了一个环。而且可以得出，操作多少次能变回来就相当于所有环长度的lcm。

枚举一些素数，一个数组表示这些素数的幂次方，一个数组记最后的答案。

所以可以发现问题就变成了$dp_{i,j}$为前$i$个数的和为$j$是操作的次数。

每次一个新的质数$p$，我们让答案乘以枚举的$p$的$k$次幂（$p^k$），并且这是一个背包问题，所以可以把这个问题压成一维，省掉“前$i$个数的和”那块。

判断素数函数：

```
bool IsPrime(long long n) { //Prime number calculator
    for (long long i = 2; i * i <= n; i++) {//起到了枚举到sqrt(n)的作用，更快
        if (n % i == 0) return false;
    }
    return true;
}
```


---

