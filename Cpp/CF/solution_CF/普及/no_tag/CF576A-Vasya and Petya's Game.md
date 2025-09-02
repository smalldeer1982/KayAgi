# Vasya and Petya's Game

## 题目描述

Vasya and Petya are playing a simple game. Vasya thought of number $ x $ between $ 1 $ and $ n $ , and Petya tries to guess the number.

Petya can ask questions like: "Is the unknown number divisible by number $ y $ ?".

The game is played by the following rules: first Petya asks all the questions that interest him (also, he can ask no questions), and then Vasya responds to each question with a 'yes' or a 'no'. After receiving all the answers Petya should determine the number that Vasya thought of.

Unfortunately, Petya is not familiar with the number theory. Help him find the minimum number of questions he should ask to make a guaranteed guess of Vasya's number, and the numbers $ y_{i} $ , he should ask the questions about.

## 说明/提示

The sequence from the answer to the first sample test is actually correct.

If the unknown number is not divisible by one of the sequence numbers, it is equal to $ 1 $ .

If the unknown number is divisible by $ 4 $ , it is $ 4 $ .

If the unknown number is divisible by $ 3 $ , then the unknown number is $ 3 $ .

Otherwise, it is equal to $ 2 $ . Therefore, the sequence of questions allows you to guess the unknown number. It can be shown that there is no correct sequence of questions of length 2 or shorter.

## 样例 #1

### 输入

```
4
```

### 输出

```
3
2 4 3 
```

## 样例 #2

### 输入

```
6
```

### 输出

```
4
2 4 3 5 
```

# 题解

## 作者：_NightFire666_ (赞：2)

### 推荐使用[博客](https://www.luogu.com.cn/blog/20111219zhr/solution-cf576a)食用！
### _Brief Description_
有一个正整数 $n$，你可以多次询问一个整数 $x$ **是否是** $n$ **的因子**，请求出**至少询问多少次**可以确定 $n$ 是谁，以及**需要询问的数**。
### _Solution_
可以发现当 $n=p^k (p \text{为质数} )$ 时，询问 $p^{k-1}$ 是**无法确定**的。所以就要寻找 $[1,n]$ 中的所有**质数**，然后再把计算所有质数**不大于** $n$ **的所有幂**，以上所计算的数就是最终答案。
### _About "Linear sieve"_
线性筛，可以理解为用 $\mathcal{O}(n)$ 的时间复杂度处理 $[1,n]$ 定义域范围内的质数。

而筛法的思想非常简单，就是我们要求每一个数都被且**仅被其最小的质因数筛掉**，即只有在 $pri_j\le \min(prime_i)$ 时筛 。所以我们只需要在 $i\mod pri_j = 0$ 后 `break` 掉就行了。（因为 $pri_j$ 是**从小到大**枚举的，所以如果存在 $i\mod pri_j = 0$ 就说明 $pri_j$ 已经是 $i$ 的最小质因子了）

**代码实现**
```cpp
void linearSieve(int n) {
	std::vector<bool> isPrime(n + 1, true);//筛掉没
   std::vector<int> primes;//质数集
	
	for (int i = 2; i <= n; ++i) {
		if (isPrime[i]) {//没筛掉
			primes.push_back(i);
		}
		
		for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {//它的倍数
			isPrime[i * primes[j]] = false;//不是质数
			
			if (i % primes[j] == 0) {//不满足筛的条件
				break;
			}
		}
	}
	for(auto i:primes)//输出
		cout<<i<<" ";
}
```
### _Code_
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> primes;

void linearSieve(int n) {
	vector<bool> isPrime(n + 1, true);
	
	for (int i = 2; i <= n; ++i) {
		if (isPrime[i]) {
			primes.push_back(i);
		}
		
		for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
			isPrime[i * primes[j]] = false;
			
			if (i % primes[j] == 0) {
				break;
			}
		}
	}
}

int main() {
	int n;
	cin >> n;
	linearSieve(n);
	vector<int>ans;
	for(auto i:primes){
		int k=0;
		while(pow(i,++k)<=n)//枚举次幂
			ans.push_back(pow(i,k));
	}
	cout<<ans.size()<<endl;
	if(ans.size())			//细节
		for(auto answer:ans)
			cout<<answer<<" ";
	return 0;
}
```


---

## 作者：Acc_Robin (赞：1)

### 题意

有一个正整数 $n$，你可以多次询问一个整数 $x$ 是否是 $n$ 的因子，请求出至少询问多少次可以确定 $n$ 是谁，以及需要询问的数。

$n\le 1\times 10^3$.

### 题解

注意到如果 $n=p^k$（$p$ 是素数），那么只询问 $p^{k-1}$ 是无法分辨出 $p^k$ 和 $p^{k-1}$ 的。

说明我们需要询问所有小于等于 $n$ 的素数及其幂，即 $\forall p^k\le n$.

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	int n,r,p[509],np[1009],ct;
	basic_string<int>v;
	void work(){
		cin>>n;
		for(int i=2;i<=n;i++){
			if(!np[i])p[++ct]=i;
			for(int j=1;j<=ct&&i*p[j]<=n;j++)if(np[i*p[j]]=1,i%p[j]==0)break;
		}
		for(int i=1;i<=ct;i++)for(int j=p[i];j<=n;j*=p[i])v+=j;
		cout<<v.size()<<'\n';
		for(int x:v)cout<<x<<' ';
	}
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：xxxr_2024 (赞：0)

# CF576A Vasya and Petya's Game 题解
## 分析
显然，我们可以通过统计包含各个质因数的个数来确定任何一个数。

现在我们需要通过一组询问确定 $1\sim n$ 的所有数，那么就需要确定 $1\sim n$ 所有数可能包含的质因数和包含的个数。可以先用筛法筛出 $1\sim n$ 的所有质数，再枚举它们在 $1\sim n$ 的所有次幂，来确定包含这个质因数的个数。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    const int N=1005;
    int vis[N],n;
    vector<int> p;
    void is_prime()
    {
        for(int i=2;i<=n;i++)
        {
            if(!vis[i])
            {
                int res=i;
                while(res<=n)
                    p.push_back(res),res*=i;
                for(int j=i*2;j<=n;j+=i)vis[j]=1;
            }
        }
    }
    signed work()
    {
        cin>>n;
        is_prime();
        cout<<p.size()<<endl;
        for(auto it:p)cout<<it<<" ";
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF576A)
# 题目描述
有一个正整数 $n$，你可以多次询问一个整数 $x$ 是否是 $n$ 的因子。

求至少询问多少次才可以确定唯一的 $n$，以及需要询问的数。
# 题目分析
前置知识：[算术基本定理](https://baike.baidu.com/item/%E7%AE%97%E6%9C%AF%E5%9F%BA%E6%9C%AC%E5%AE%9A%E7%90%86)。

对于一个大于一的正整数 $n$，可以被唯一分解为 $n=p_1^{a_1}\times p_2^{a_2}\times p_3^{a_3}\times\cdots\times p_k^{a_k}$，其中 $\forall p_{i}$ 为质数。

同理，知道每一个 $a$ 与 $p$，就可以反推出一个唯一的 $n$。

### 一个结论
分析 $a_1$ 与 $p_1$。因为操作必须要做完，所以类似二分的动态搜索方法就不适用了。

如果只尝试到 $p_1^{ans_1-1}$ 且 $p_1^{ans_1}\le n$，则无法区分 $a_1=ans_1$ 与 $a_1=ans_1+1$。

所以对于 $p_1$，必须尝试到 $ans_1$ 满足 $p_1^{ans_1+1}>n$ 是才能确定唯一的 $a_1$。
### 推广
对于 $k$ 个质因数 $p_i$ 都需要试 $ans_i$ 次，满足 $\left\{\begin{matrix} 
  p_i^{ans_i}\le n\\
  p_i^{ans_i+1}>n  
  \end{matrix}\right. $。

最后的答案即为 $\sum\limits_{i=1}^{k}ans_i$。

同时输出为：$p_1^{1},p_1^{2},\dots,p_1^{ans_1},\dots,p_k^{1},p_k^{2},\dots,k^{ans_k}$。

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF576A)

[CodeForces 链接](https://codeforces.com/problemset/problem/576/A)

题目大意：

给你一个数 $n$（$1\leq k\leq 1000$），让你猜出一个数 $1\leq x\leq n$，允许你以 “$y$ 是否整除 $x$”的形式发出提问。问你最少需要问多少次才能保证猜出 $x$，且计划中的问题必须全部提问出来。

思路：

这一个题显然是一个数学题。我们可以发现，当 $x=p^k$（$p\in\text{prime}$）时，我们询问 $p^{k-1}$ 时无法确定 $x$ 到底是 $p^{k-1}$ 还是 $p^k$。所以，要保证一定能确定 $x$，我们需要用[线性筛](https://oiwiki.org/math/number-theory/sieve/#%E7%BA%BF%E6%80%A7%E7%AD%9B%E6%B3%95)来把 $n$ 分解质因数，然后问所有的 $p^k$（$p|n\And p\in\text{prime}$），最终统计即可。

此算法时间复杂度为 $\Theta(n)$。

上代码：
```cpp
#include <cstring>
#include <iostream>
using namespace std;

int cnt, prime[169], ans[1001];
bool is_prime[1001];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int n;
    cin >> n;
    // 线性筛模板，不会的同学可以参考 OI-Wiki
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[1] = false;
    for (int i = 2; i <= n; i++){
        if (is_prime[i]){
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++){
            is_prime[i * prime[j]] = false;
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    // 统计问题并输出
    int cnt1 = 0;
    for (int i = 1; i <= cnt; i++){
        for (int j = prime[i]; j <= n; j *= prime[i]){
            ans[++cnt1] = j;
        }
    }
    cout << cnt1 << "\n";
    if (cnt1 != 0){
        // 可能有的坑人格式，警惕。
        cout << ans[1];
        for (int i = 2; i <= cnt1; i++){
            cout << " " << ans[i];
        }
    }
    cout << "\n";
    return 0;
}
```

---

## 作者：w9095 (赞：0)

[CF576A Vasya and Petya's Game](https://www.luogu.com.cn/problem/CF576A)

数论思维题。

根据唯一分解定理，可以知道，如果一个数的各个**质因数**的**数量**确定了，这个数也就确定了。

每次询问的中，如果 $x$ 是 $y$ 的倍数，证明 $x$ 中含 $y$ 的**所有**质因数。我们可以枚举质数，判定 $x$ 能否整除这个质数，就可以判断 $x$ 是否含有这个质因数。

但是这还不能完全确定 $x$，因为这样只能确定是否有某个质因数，而不能确定质因数的**数量**。为了确定质因数的数量，我们可以把这个质数（设 $a$ 为这个质数）的 $b$ 次方都枚举一遍，同时保证 $a^b\le n$。因为由乘方的定义，得 $a^b$ 中含有 $b$ 个 $a$，如果 $x$ 是 $a^b$ 的倍数，证明 $x$ 中**至少**含有 $b$ 个质因数 $a$。把 $\le n$ 的这类数字都枚举一遍，就可以确定 $x$ 各个质因子的**个数**了。

所以，我们先用线性筛筛出 $\le n$ 的质数，然后根据上文所述计算输出即可。

完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,pri[70000],ansd[10000];
bool a[700000];
int linear(bool a[],int pri[],int n)
{
    int cnt=0;
    a[1]=1;
    for(int i=2;i<=n;i++)
        {
            if(!a[i])pri[cnt++]=i;
            for(int j=0;j<cnt&&i*pri[j]<=n;j++)
                {
                    if(!a[i*pri[j]])a[i*pri[j]]=1;
                    if(i%pri[j]==0)break;
                }
        }
    return cnt;
}

int main()
{
	int ans=0;
	scanf("%d",&n);
	int cnt=linear(a,pri,n);
	for(int i=0;i<cnt;i++)
	    {
		int now=1;
	    while(now*pri[i]<=n)now*=pri[i],ansd[ans++]=now;
	    }
	printf("%d\n",ans);
	for(int i=0;i<ans;i++)
	    printf("%d ",ansd[i]);
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/102006203)

---

## 作者：zeekliu (赞：0)

众所周知，一个数有**唯一**的素因数分解。

因此反推：只要一种素因数分解的方式可以唯一的确定一个数。

所以他如果想要猜中 $ x $，则需要猜中其素因数分解式。

那么需要给出所有可能的底数，但这还不够，还需要猜中其指数，因此需要给出所有以此为底数的数。

所以只需考虑枚举所有 $ \le n $ 中的素数及其幂次方即可。

因此此处首先枚举那个素数，然后使用筛法，筛出需要询问的数。

所以很明显我们会发现，这是个二重循环，第一层枚举底数，它是个素数，第二层枚举指数，保证算出的数不大于 $ n $ 即可。

举个例子：

输入：$ 10 $

其中素数有 $ 2 $, $ 3 $, $ 5 $, $ 7 $。

$ 2 $ 的幂次方有 $ 2 $, $ 4 $, $ 8 $。

$ 3 $ 的幂次方有 $ 3 $, $ 9 $。

因此选出 $ 2,3,4,5,7,8,9 $，共 $ 7 $ 个。

下面代码：

```cpp
//CF576A 22-09-22
#include <bits/stdc++.h>
using namespace std;
int a[1010],b[1010];

bool prime(int m)
{
	if (m==1 || (m>2 && m%2==0)) return 0;
	else for (int i=3;i<=sqrt(m);i+=2)
		if (m%i==0) return 0;
	return 1;
}

int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,s=0; cin>>n;
	for (int i=2;i<=n;i*=2) a[i]=1;
	for (int i=3;i<=n;i+=2)
	{
		if (prime(i)) for (int j=i;j<=n;j*=i) a[j]=1;
	}
	for (int i=1;i<=n;i++)
		if (a[i]) s++,b[s]=i;
	cout<<s<<endl;
	for (int i=1;i<=s;i++) cout<<b[i]<<" ";
	exit(0);
}
```

---

## 作者：zesqwq (赞：0)

# CF576A Vasya and Petya's Game 题解

[题目传送门](https://www.luogu.com.cn/problem/CF576A)

~~最优解，嘿嘿~~

分析一下，你既然要猜出这个数，就必须把他的质因子猜出来。但是猜出质因子还是不够，因为比如说答案是 $8$，你猜了个 $2,3,5,7$ 此时你就无法确认答案到底是 $2,4,8$ 中的哪一个，所以我们要猜 $p^a(p \in \text{prime}, a \in \mathbb{Z})$。

接着你可以使用线性筛来提速这个过程，时间复杂度 $O(n)$。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 1e3 + 10;
bool vis[N], flag[N];
int prime[N], cnt, tot;
int main() {
    cin >> n, vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && prime[j] * i <= n; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    for (int i = 1; i <= cnt; i++)
        for (int j = prime[i]; j <= n; j *= prime[i]) flag[j] = 1, ++tot;
    cout << tot << endl;
    for (int i = 1; i <= n; i++)
        if (flag[i]) printf("%d ", i);
    return 0;
}c
```

---

## 作者：cachejtt (赞：0)

### 题意
小 V 在 $1\sim n$ 之间想了一个数 $x$，小 P 有一个长度为 $k$ 的询问数列 $y$，她将会问小 V $k$ 个问题，每个问题是： $x$ 是否能被 $y_i$ 整除？

小 P 希望，不论小 V 选择了怎样的 $x$，她所准备的问题都能够唯一确定 $x$，请你找出最小的 $k$，并给出询问数列。

### 思路
一开始我们考虑询问把 $1\sim n$ 之间所有数都质因数分解，把得到的所有出现过的质因数询问一次。但是考虑 $n=6$ 的情况，这时我们的询问数列 $y={2,3,5}$，我们会发现无法分辨 $2$ 和 $4$，这说明询问 $2$ 还不够，我们要询问 $4$。

由此可知，对于 $x_1=c\times {p_i}^m$ 和 $x_2=c\times {p_i}^{m-1}$，我们只询问 ${p_i}^{m-1}$ 是不够的，要询问 ${p_i}^m$ 才能分辨这两个数。

由此可知，对于每一个 $p_i$，都必须要询问 ${p_i},{p_i}^2,{p_i}^3,\dots,{p_i}^m$，我们只需要循环 $p_i$ 的指数，当 ${p_i}^m \ge n$ 时停下就行了，这时把 $k$ 加上 $m$，询问数列里加上如上数列即可。

### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
int n;
bool p[1005];//0是质数
int sum;
int k;
int ans[1005],cnt=0;
int main(){
  cin>>n;
  p[1]=1;
  p[2]=0;
  rep(i,2,n/2){
    if(p[i]==0){
      rep(j,2,n/i+2){
        if(i*j<=n)p[i*j]=1;
      }
    }
  }
  rep(i,1,n){
    if(p[i]==0){
      sum=i;
      while(sum<=n){
        k++;
        ans[++cnt]=sum;
        sum*=i;
      }
    }
  }
  cout<<k<<endl;
  rep(i,1,cnt){
    cout<<ans[i]<<" ";
  }
  return 0;
}
```

---

