# [ABC189D] Logical Expression

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc189/tasks/abc189_d

$ N $ 個の文字列 $ S_1,\ldots,S_N $ が与えられます。各文字列は `AND` または `OR` です。

値が $ \text{True} $ または $ \text{False} $ であるような $ N+1 $ 個の変数の組 $ (x_0,\ldots,x_N) $ であって、 以下のような計算を行った際に、$ y_N $ が $ \text{True} $ となるようなものの個数を求めてください。

- $ y_0=x_0 $
- $ i\geq\ 1 $ のとき、$ S_i $ が `AND` なら $ y_i=y_{i-1}\ \land\ x_i $、$ S_i $ が `OR` なら $ y_i=y_{i-1}\ \lor\ x_i $

$ a\ \land\ b $ は $ a $ と $ b $ の論理積を表し、$ a\ \lor\ b $ は $ a $ と $ b $ の論理和を表します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 60 $
- $ S_i $ は `AND` または `OR`

### Sample Explanation 1

例えば $ (x_0,x_1,x_2)=(\text{True},\text{False},\text{True}) $ のとき - $ y_0=x_0=\text{True} $ - $ y_1=y_0\ \land\ x_1\ =\ \text{True}\ \land\ \text{False}=\text{False} $ - $ y_2=y_1\ \lor\ x_2\ =\ \text{False}\ \lor\ \text{True}=\text{True} $ となり、$ y_2 $ は $ \text{True} $ になります。 $ y_2 $ が $ \text{True} $ となるような $ (x_0,x_1,x_2) $ の組み合わせは、 - $ (\text{True},\text{True},\text{True}) $ - $ (\text{True},\text{True},\text{False}) $ - $ (\text{True},\text{False},\text{True}) $ - $ (\text{False},\text{True},\text{True}) $ - $ (\text{False},\text{False},\text{True}) $ の $ 5 $ 通りで全てです。

### Sample Explanation 2

全てが $ \text{False} $ のときを除く $ 2^6-1 $ 通りで $ y_5 $ は $ \text{True} $ になります。

## 样例 #1

### 输入

```
2
AND
OR```

### 输出

```
5```

## 样例 #2

### 输入

```
5
OR
OR
OR
OR
OR```

### 输出

```
63```

# 题解

## 作者：Elairin176 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc189_d)      
## 题意
给你 $n$ 个符号，只包括 `AND` 和 `OR`。现在要求插入 $n+1$ 个 $0$ 或 $1$，并从左往右依次计算结果。现在要求求出结果为 $1$ 的数字填法数量。   
## 解法
显然的 dp。    
我们设 $dp_{i,j}$ 为第 $i$ 个操作符之后，结果为 $j$ 的方案数。特别地，$dp_{0,j}$ 表示最左边结果 $j$ 的方案数，即总是等于 $1$。     
接下来考虑转移。我们扫一遍所有的符号即可。接下来我们设扫到第 $i$ 位：    
### 符号是 `AND`   
先考虑结果为 $0$ 的情况。如果结果为 $0$，那么上一位结果和这一位所填数字只有以下几种情况：   
- 上一位结果是 $0$，这一位无论填什么结果都是 $0$。    
- 上一位结果是 $1$，这一位只能填 $0$ 才能使结果为 $0$。   

那么我们的式子为 $dp_{i,0}=2\times dp_{i-1,0}+dp_{i-1,1}$。   
接下来考虑结果为 $1$ 的情况。   
显然，结果为 $1$ 的话，我们上一位的结果和这一位填的都必须为 $1$。   
那么我们只需要继承上一次的结果即可：$dp_{i,1}=dp_{i-1,1}$。   

### 符号是 `OR`   
推导过程和上面的类似，这里只放转移。   
$dp_{i,0}=dp_{i-1,0}$   
$dp_{i,1}=dp_{i-1,0}+2\times dp_{i-1,1}$    

## 总结
这个算法的时间复杂度为 $O(n)$，可以通过。   
注意要开 long long。   
[CODE](https://www.luogu.com.cn/paste/q1pklhvd)

---

## 作者：NightStriker (赞：1)

我来写一篇蒟蒻的二维 dp 题解。

---

题意：

> 给定 $n$ 个运算符：$\&$ 或 $|$（为 $\texttt{AND}$ 和 $\texttt{OR}$），让你插入 $n+1$ 个 $0$ 或 $1$ 使得最终结果为真。求方案数。

$n \le 60$，很明显我们使用 $\mathcal{O}(2^n)$ 的暴力枚举每个位置是不可行的。这其实是一道很套路的分类讨论 $\operatorname{dp}$。

考虑二维 $\operatorname{dp}$。$f_{i,j}$ 表示第 $i$ 个空填后，值为 $j$ 的方案个数。

我们设原先求出来的值为 $x$，也就说每次有四种情况，我们就需要对这 $4$ 种情况进行分类讨论：

$\begin{cases}x\&0\\x\&1\\x |0 \\ x| 1\end{cases}$

$\&$ 的性质是：只有两个参数都是 $1$，值才能为 $1$。

如果当前的符号是 $\&$：

 $\large f_{i,1}=f_{i-1,1}$

$\large f_{i,0}=f_{i-1,1}+f_{i-1,0} \times 2$

$|$ 的性质是：只要有一个参数是 $1$，值就为 $1$。

如果当前的符号是 $|$：

$\large f_{i,0}=f_{i-1,0}+f_{i-1,1}\times 2$

$\large f_{i,0}=f_{i-1,0}$

由于方案数可能会高达 $2^{60}-1$，明显需要开 `long long`。

最后我们就只需要输出 $f_{n,1}$ 的值，代表第 $n+1$ 个数字填完后返回值为真的方案个数。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,f[61][2];
string s[61];
int main() {
	cin>>n;
	for(int i = 0; i<n; i++) {
		cin>>s[i];
	}
	f[0][0] = 1;
	f[0][1] = 1;
	for(int i = 0; i<n; i++) {
		if(s[i]=="AND") {
			f[i+1][1]+=f[i][1];
			f[i+1][0]+=2*f[i][0]+f[i][1];
		}
		else if(s[i]=="OR") {
			f[i+1][1]+=f[i][0]+2*f[i][1];
			f[i+1][0]+=f[i][0];
		}
	}
	cout<<f[n][1]<<endl;
	return 0;
}
```



---

## 作者：卷王 (赞：0)

这是一篇不用 dp 的题解。

正序 dp 当然可以，但是可以利用二进制的性质倒序枚举，只要当前字符是 `O` 就加上 $2^i$，最后输出答案即可。

主函数不加关流同步只需要 $8$ 行，没有那么复杂。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n; ll ans = 1;
string a[67];

int main() {
	speed: std::ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = n; i >= 1; i--)
		if(a[i][0] == 'O') ans += (1ll << i);
	cout << ans;
	return 0;
}
```

---

## 作者：Tang_poetry_syndrome (赞：0)

## [ABC189D] Logical Expression 
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc189_d) [Atcoder 题面](https://atcoder.jp/contests/abc189/tasks/abc189_d)
### 思路
看到题目，很容易想到二维动归。  
设 $dp_{i,j}$ 为前 $i$ 项结果为 $j$ 的方案数。  
根据 $1\&1=1$，可得 $dp_{i,1}=dp_{i-1,1}$。  
$0\&1=0$ 与 $1\&0=0$ 与 $0\&0=0$，可得 $dp_{i,0}=dp_{i-1,1}+dp_{i-1,0} \times 2$。  
$1\mid1=1$ 与 $0\mid1=0$ 与 $1\mid0=1$，可得 $dp_{i,1}=dp_{i-1,1} \times 2+dp_{i-1,0}$。  
$0\mid0=0$，可得 $dp_{i,0}=dp_{i-1,0}$。  
整合一下：  
$dp_{i,0}=\begin{cases}dp_{i-1,1}+dp_{i-1,0} \times 2(st=AND)\\dp_{i-1,0}(st=OR)\end{cases}$  
$dp_{i,1}=\begin{cases}dp_{i-1,1}(st=AND)\\dp_{i-1,1} \times 2+dp_{i-1,0}(st=OR)\end{cases}$  
同时，输入字符串皆为 `OR` ，答案会达到 $2^{60}-1$，需要开 long long。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define ll long long
const int N=65;
ll n,dp[N][2];
string s;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    dp[0][0]=dp[0][1]=1;
    f(i,1,n){
        cin>>s;
        dp[i][0]=(s=="AND")?2*dp[i-1][0]+dp[i-1][1]:dp[i-1][0],dp[i][1]=(s=="AND")?dp[i-1][1]:dp[i][1]=dp[i-1][0]+2*dp[i-1][1];
    }
    cout<<dp[n][1];
	return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc189/submissions/45957384)

---

## 作者：Dr_Octopus (赞：0)

### 题意

有 $n$ 个运算符：$\And$ 或 $\mid$，让你往里填入 $n+1$ 个值（true 或 false），使最终的结果为 true，问有多少种方案数。

------------

### 思路

考虑 dp。

首先，设 dp 数组 $f\left[i\right]\left[j\right]$，表示第 $i$ 个空填后，值为 $j$ 的方案数。接着，考虑初始状态 $f\left[0\right]\left[0\right]=f\left[0\right]\left[1\right]=1$。

然后，枚举下一步填的位置进行 dp 转移即可（具体实现见 code）。

------------

### 提醒

[不熟悉 and 和 or 的可以看一下](https://oi-wiki.org/math/bit/)

------------

### code

```cpp
#include <bits/stdc++.h>
#define int long long

const int N = 10e5 + 5;
using namespace std;

int f[N][2], v[N];
char ch[5];
int n;

signed main() {
	
    cin >> n;
    for (int i = 1;i <= n; i ++ ) {
    	 cin >> ch;
        if (ch[0] == 'A') v[i] = 1;
        else v[i] = 2;            // ch[0] == 'O'
    }
    
    f[0][0] = f[0][1] = 1;    // 初始状态 
    
    for (int i = 1;i <= n;i ++ ) {         // 开始转移 
        if (v[i] == 1) {  // 若是 And 
            f[i][0] += f[i - 1][0]; f[i][0] += f[i - 1][1];
            f[i][0] += f[i - 1][0]; f[i][1] += f[i - 1][1];
        }
	 else {  // 是 Or 
            f[i][0] += f[i - 1][0]; f[i][1] += f[i - 1][1];
            f[i][1] += f[i - 1][0]; f[i][1] += f[i - 1][1];
        }
    }
    printf("%lld", f[n][1]);
    
    return 0; 
}

```

---

## 作者：fish_love_cat (赞：0)

**难的一匹の动态规划！**

我们开一个 $dp$ 数组，用 $dp_{i,j}$ 表示前 $i+1$ 个位置上填了数后，值为 $j$ 的方案数。我们发现，在填第 $1$ 个数（位置 $0$）时，值为 $1$ 和值为 $0$ 的方案均为 $1$。

---

此后，如果是遇上 ```AND```，那么值为真的数量就是上一个值为真的数量。因为当前就必须填真，而原来的也必须填真，所以数量就还是原来为真的数量。用式子表示：

$$f_{i,1}=f_{i-1,1}$$

而值为假的数量呢？其实就是原来为真的数量加原来为假的数量乘二。因为原来是真，那么这里选假就可以变成假，有一种选择；原来是假，那这里选真选假都一样，有两种选择，乘二。用式子表示：

$$f_{i,0}=f_{i-1,1}+f_{i-1,0} \times 2$$

---

如果碰上 ```OR```，要想值为假，就必须两边都是假才行。那么值为假的方案数就等同于上一个假的方案数。用式子：

$$f_{i,0}=f_{i-1,0}$$

要使值为真，方案数就会是原来真的数量乘二加上原来假的数量。因为原来如果是真，那么这里不管选什么，答案不影响，所以乘二；原来如果是假，那为了让答案为真，所以只有填真一种选择。这里用式子来讲就是：

$$f_{i,1}=f_{i-1,0}+f_{i-1,1} \times 2$$

---

四种情况，四个式子都推完了，代码就不用多说了吧……

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[65][5];
bool a[65];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        if(s=="AND") a[i]=true;
    }
    dp[0][0]=1;
    dp[0][1]=1;
    for(int i=1;i<=n;i++){
        if(a[i]){
            dp[i][1]=dp[i-1][1];
            dp[i][0]=dp[i-1][0]*2+dp[i-1][1];
        }else{
            dp[i][1]=dp[i-1][1]*2+dp[i-1][0];
            dp[i][0]=dp[i-1][0];
        }
    }
    cout<<dp[n][1]<<endl;
    return 0;//完结撒花！
}
```

---

## 作者：loser_seele (赞：0)

显然是一个分类讨论题。

考虑设 $ dp_n $ 表示前 $ n $ 位的答案，讨论第 $ N $ 个操作符的情况：

如果第 $ N $ 个操作符是 AND，则 $ y_{n-1},x_n $ 都应该是真，否则不符合题意，于是有 $ dp_n=dp_{n-1} $。

如果第 $ N $ 个操作符是 OR，则如果 $ x_n $ 为真 $ y_{n-1} $ 是什么并不影响答案，意味着前面的位数可以随便填，有 $ 2^{n} $ 种情况，否则 $ x_n $ 确定为假，则 $ y_{n-1} $ 一定为真，答案为 $ dp_{n-1} $。

于是按照上面的方法转移，时间复杂度 $ \mathcal{O}(n) $。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
long long n, dp[69];
string op[69];
int main()
{
  cin>>n; 
  for(int i=1; i<=n; i++)
  cin>>op[i];
  dp[1]=1;
  for(int i=2; i<=n+1; i++)
    if(op[i-1]=="AND")
      dp[i]=dp[i-1];
    else
      dp[i]=dp[i-1]+(1LL<<(i-1));
  cout<<dp[n+1];
}
```


---

