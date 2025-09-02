# [ABC096D] Five, Five Everywhere

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc096/tasks/abc096_d

以下の条件を満たす, 長さ $ N $ の数列 $ a_1,\ a_2,\ ...,\ a_N $ を $ 1 $ つ出力してください.

- $ a_i\ (1\ \leq\ i\ \leq\ N) $ は $ 55\ 555 $ 以下の素数である.
- $ a_1,\ a_2,\ ...,\ a_N $ の値はすべて異なる.
- $ a_1,\ a_2,\ ...,\ a_N $ からどの異なる $ 5 $ 個の整数を選んでも, この合計は合成数になる.

条件を満たす数列が複数個存在するとき、条件を満たすもののうちどのような数列を出力しても正解となります.

## 说明/提示

### 備考

$ 2 $ 以上の整数 $ N $ が, $ 1 $ と $ N $ 以外のどの正の整数でも割り切れなければ $ N $ は「素数」であり, そうでない場合 $ N $ は「合成数」である.

### 制約

- $ N $ は $ 5 $ 以上 $ 55 $ 以下の整数

### Sample Explanation 1

まず, $ 3 $, $ 5 $, $ 7 $, $ 11 $, $ 31 $ は全て異なり, 全て素数です. これらから $ 5 $ 個の整数を選ぶ方法は, 「全てを選ぶ」の 1 通りのみです. $ a_1+a_2+a_3+a_4+a_5=57 $ であり, この値は合成数なので問題文の条件を満たします. 他にも, `2 3 5 7 13` `11 13 17 19 31` `7 11 5 31 3` などを出力しても正解となります.

### Sample Explanation 2

\- $ 2 $, $ 3 $, $ 5 $, $ 7 $, $ 11 $, $ 13 $ は全て異なる素数です. - $ 2+3+5+7+11=28 $ であり, 合成数です. - $ 2+3+5+7+13=30 $ であり, 合成数です. - $ 2+3+5+11+13=34 $ であり, 合成数です. - $ 2+3+7+11+13=36 $ であり, 合成数です. - $ 2+5+7+11+13=38 $ であり, 合成数です. - $ 3+5+7+11+13=39 $ であり, 合成数です. よって, `2 3 5 7 11 13` は条件を満たす数列です.

## 样例 #1

### 输入

```
5```

### 输出

```
3 5 7 11 31```

## 样例 #2

### 输入

```
6```

### 输出

```
2 3 5 7 11 13```

## 样例 #3

### 输入

```
8```

### 输出

```
2 5 7 13 19 37 67 79```

# 题解

## 作者：TLEWA (赞：1)

很玄学的一道题目，首先我们可以看到数据范围很小，而 $N$ 的范围更是在 $55$ 以内，而打表可以发现 $55555$ 以内的数共有 $5637$ 个素数。这意味着我们可以用一些玄学的，苛刻的构造方法，这里我提出一种构造方法：构造的数列中数的个位均为 $1$。

如何保证正确性呢？很好理解，这五个数相加，肯定会产生一个 $>5$ 且 $\bmod 5 = 0$ 的数，这个数必定是合数，因为肯定有一个因数 $5$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[101],ans,prime[66666];
bool vis[66666];

int main(){
	memset(vis,0,sizeof(vis));
	memset(prime,0,sizeof(prime));
	vis[0]=vis[1]=true;
	for(register int i=2; i<=55555; ++i) {
		if(!vis[i]) {
			prime[++ans]=i;
		}
		for(register int j=1; prime[j]*i<=55555&&j<=ans; ++j) {
			vis[i*prime[j]]=true;
			if(!(i%prime[j])) break;
		}
	}
	cin >> n;
	int summ=0;
	for(int i=1;i<=ans&&summ!=n;++i) {
		if(prime[i]%10==1) {
			cout << prime[i] << ' ';
			summ++;
		}
	}
	cout << endl;
	return 0;
}
```


---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc096_d)

## 思路

这题我们用枚举加上埃氏筛的方法来做。

> 序列中任意 $5$ 个数的和必须是合数。

我们可以想到，$5$ 个除以 $5$ 余 $3$ 的数加起来一定能被 $5$ 整除

枚举时，我们可以设置一个变量 $i$ 从 $3$ 开始循环枚举，一直循环到最大值 $55555$，每循环一次 $i$ 就 $+10$。 找到一个质数就输出一个，计数器 $+1$。同样，如果找到的质数个数达到 $n$，就退出循环。

循环枚举部分代码：

~~~cpp
    for(int i=3;sum<n&&i<=55555;i+=10){
        if(prime(i)){
            ++sum;
            cout<<i<<" ";//别忘空格。
        }
    }
~~~

------

埃氏筛中，由于是从 $3$ 开始枚举，所以不需要特判。另外，为了降低时间复杂度，若想判断一个数 $x$ 是不是质数时，只需要枚举到 $\sqrt{x}$ 即可。

埃氏筛代码：

~~~cpp
    bool prime(int x){
        for(int i=2;i*i<=x;++i){
            if(x%i==0)return 0;
        }
        return 1;
    }
~~~



- 最后别忘输出换行。

## 完整代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;//n 为个数，cnt 为符合要求的个数的计数器。
bool prime(int x){
    for(int i=2;i*i<=x;++i){
        if(x%i==0)return 0;
    }
    return 1;
}
int main(){
    cin>>n;
    for(int i=3;cnt<n&&i<=55555;i+=10){//注意 cnt<n。
        if(prime(i)){
            ++cnt;
            cout<<i<<" ";
        }
    }
    cout<<endl;//最后别忘换行。
    return 0;
}

~~~

[AC 记录](https://www.luogu.com.cn/record/96023661)

---

## 作者：andyli (赞：0)

考虑选择模 $5$ 等于 $1$ 的质数，则任意 $5$ 个数的和必为 $5$ 的倍数。由 $n \leq 55$，第 $55$ 个符合上述条件的质数为 $1381$，符合题目小于等于 $55555$ 的条件。


```python
def sieve(n):
    primes = set(range(2, n + 1))
    for i in range(2, int(n**0.5 + 1)):
        primes.difference_update(range(i * 2, n + 1, i))
    return list(primes)

n = int(input())
ans = []
for p in sieve(55555):
    if p % 5 == 1:
        ans.append(p)
    if len(ans) == n:
        exit(print(*ans))

```


---

## 作者：cosf (赞：0)

## [ABC096D](https://atcoder.jp/contests/abc096/tasks/abc096_d) [Five, Five Everywhere](https://www.luogu.com.cn/problem/AT_abc096_d)

思路
---
题目说任意 $5$ 个数加起来是合数，那么我就想到了，如果一个序列中每个数模 $5$ 的余数都一样，比如有 $n$ 个质数 $10k_1+1, 10k_2+1,\dots,10k_n+1$，其中 $k_i$ 是正整数，那么他们中任意 $5$ 个数的和为 $10(k_{i1}+k_{i2}+\dots+k_{i5})+5$，明显是 $5$ 的倍数。因为 $k_i > 0$，所以 $10(k_{i1}+k_{i2}+\dots+k_{i5})+5 > 5$，除了 $5$ 肯定还有其他因数，故它不是质数，所以可以依照这个方法做这道题。

经过计算，小于 $55555$ 的个位是 $1$ 的质数有 1 千多个，$1000 \gt n$，所以这个方法是可行的。~~因为数据太水，所以可以直接暴力。~~

接下来就是代码了：

[AC Code](https://www.luogu.com.cn/record/94915262)
---

```cpp
#include <iostream>
using namespace std;

bool isprime(int val) // 最原始最简单的质数判断
{
    for (int i = 2; i * i <= val; i++)
    {
        if (!(val % i))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    int val = 11; // 反证就是枚举n个末尾是1的质数就对了
    while (n--)
    {
        while (!isprime(val))
        {
            val += 10;
        }
        cout << val << ' ';
        val += 10;
    }
    return 0;
}

```


---

## 作者：DerrickLo (赞：0)

因为 $5$ 个除以 $5$ 余 $3$ 的数加起来是一定会被 $5$ 整除的，所以 $5$ 个除以 $5$ 余 $3$ 的数加起来一定不会是质数。

那么我们可以先定义一个计数器，然后在小于 $55555$ 的范围内枚举每一个 除以 $5$ 余 $3$ 的数，接着判断这个数是不是质数，如果是，就将这个数输出并将计数器加 $1$，如果不是，就跳过这个数，在计数器到达 $N$ 的时候终止程序。

因为小于 $55555$ 且除以 $5$ 余 $3$ 的质数是绝对大于 $55$ 个的，不用担心质数不够的问题。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,n;
bool isprime(int x){//判断是否是质数
	if(x==1)return 0;
	if(x==2)return 1;
	for(int i=2;i<=sqrt(x);i++){
		if(x%i==0)return 0;
	}
	return 1;
}
int main(){
	cin>>n;
	for(int i=3;i<=55555;i+=10){
		if(isprime(i)){
			cout<<i<<' ';
			cnt++;
			if(cnt==n)return 0;
		}
	}
} 
```


---

## 作者：Butterfly___qwq (赞：0)

# 题意：
输入一个 $n$，请你构造 $n$ 个数，$a_1,a_2,...,a_n$，并输出，这些数满足

$a_i$ 为素数，且不大于 $55555$。   
$a_1,a_2,...,a_n$ 的值都不同。   
任去其五个数的和为 $5$ 的倍数。   
# 思路：
仔细思考，我们首先可以把素数预处理出来，最大的问题是怎么选取这些素数呢，我们再想想应该从个位数开始考虑，发现我们只要令其个位数都为一，必然满足题目要求，也就是说只要个位模 $5$ 为 $1$ 就可以了。
# 代码：
```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define FOR(i,a,n) for(register int i=a; i<=n; ++i)
#define FDR(i,a,n) for(register int i=a; i>=n; --i)
#define mem(a) memset(a, 0, sizeof(a))
#define pb push_back()
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int maxn = 100005;
const int MOD = 1000000009;
int prime[1000005];
int Mark[1000005];
void Prime(){
    int index = 0;
    for(int i = 2; i <= 100000; i++)
    {
        if(Mark[i] == 0){
            prime[index++] = i;
        }
        for(int j = 0; j < index && prime[j] * i <= 100000; j++)
        {
            Mark[i * prime[j]] = 1;
            if(i % prime[j] == 0){
                break;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    Prime();
    int n;
    cin >> n;
    int i = 1;
    int cnt = 0;
    while(1)
    {
        if(prime[i]%5 == 1)
        {
            cout << prime[i] << ' ';
            cnt++;
        }
        if(cnt == n)break;
        i++;
    }
    return 0;
}
 


```

---

## 作者：panyanppyy (赞：0)

随题打 Virtual Contests 打到的题目。

## Problem
让你构造一个长度为 $5\le n\le55$ 的序列，要求任取其中五个数和是合数。
## Solution
看到样例可以想到 $2$ 不管怎样都可以取，因为一个偶数+四个奇数显然是一个合数。~~然后就不会了~~

感谢 @Awlgot 的神奇思路：

>对于每五个以 $7$ 结尾的数之和一定是合数（末尾是 $5$）。

然后强化一下得到以下结论：
>对于每五个以相同数字结尾的数一定是合数。

于是乎，先筛一些质数，然后直接做就完了~
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) x.begin(),x.end()
using namespace std;
const int N=2e6+7;
bool f[N];
vector<int>s;
inline void ss(){
	memset(f,1,sizeof(f)),f[0]=f[1]=0;
	for(int i=2;i<N;i++){
		if(f[i])s.emplace_back(i);
		for(int j=0;j<(int)s.size()&&s[j]*i<N;j++){
			f[i*s[j]]=0;
			if(i%s[j]==0)break;
		}
	}
}
vector<int>a={2};
int n;
int main(){ss();
	scanf("%d",&n);
	for(int i=0;i<(int)s.size();i++)
		if(s[i]%10==3)a.emplace_back(s[i]);
        //7,9（注意末尾是5的质数只有 5）
	for(int i=0;i<n;i++)printf("%d ",a[i]);
	return 0;
}
```

---

