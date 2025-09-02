# [ABC275D] Yet Another Recursive Function

## 题目描述

定义函数 $f(x)$ 有如下定义

- $ f(0)\ =\ 1 $
- 对于任意正整数 $k$ 有 $f(k)\ = f(\lfloor\frac{k}{2}\rfloor)\ +\ f(\lfloor\frac{k}{3}\rfloor) $

$ \lfloor A\rfloor $ 代表小于等于 $A$ 的最大整数。

求 $f(x)$。

## 说明/提示

- $ 0\ \le\ N\ \le\ 10^{18} $

### 样例一解释

$ f(2)\ =\ f(\lfloor\frac{2}{2}\rfloor)\ +\ f(\lfloor\frac{2}{3}\rfloor)\ =\ f(1)\ +\ f(0)\ =(f(\lfloor\frac{1}{2}\rfloor)\ +\ f(\lfloor\frac{1}{3}\rfloor))\ +\ f(0)\ =(f(0)+f(0))\ +\ f(0)=\ 3 $。

## 样例 #1

### 输入

```
2```

### 输出

```
3```

## 样例 #2

### 输入

```
0```

### 输出

```
1```

## 样例 #3

### 输入

```
100```

### 输出

```
55```

# 题解

## 作者：_Haoomff_ (赞：4)

题目很简单，函数如下：
```cpp
inline ll f(ll n){//ll为long long
	if(n==0)return 1;
	return f(n/2)+f(n/3);	
}
```
但是肯定不能过，因为 $n$ 最大可以取到 $10^{18}$。

于是，我们就可以用到容器 map 进行记忆化，用 map 把值存下来，我们设关键字为 $a$，接下来有三种情况：第一种，$n$ 为 $0$，返回 $1$；第二种，$n$ 在 $a$ 中已经有值，返回；第三种，正常情况，即 $n$ 不为 $0$ 且 $n$ 在 $a$ 中没有值，递归并返回。时间复杂度 $\text O(\log^2n)$。
```cpp
//十年OI一场空， 不开long long见祖宗。被忘了开long long！！！ 
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
map<ll,ll> a;
inline ll f(ll n){
	if(n==0)return a[0]=1;//n为0 
    if(a[n])return a[n];//n在a中已经有值 
	return a[n]=f(n/2)+f(n/3);//正常情况 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	cout<<f(n);
	return 0;
}
```

---

## 作者：Laffey (赞：3)

## Solution

看题解大佬们都是用记忆化过的，这里提供一个暴力做法。

注意到题目数据范围为 $10^{18}$，直接暴力肯定会超时，在本地测试发现暴力可以通过大约 $10^{10}$ 的数据，于是我们线性递推求解 $1 \sim 10^8$ 时的函数，再暴力计算剩余的部分，就可以成功在允许时间内卡过。

## Code

```cpp
#include <iostream>
using namespace std;

long long a[100000100];

long long f(long long x)
{
    if (x <= 100000000) return a[x];
    return f(x / 2) + f(x / 3);
}

int main()
{
    long long x;
    a[0] = 1;
    for (int i = 1; i <= 100000000; i++) {
        a[i] = a[i / 2] + a[i / 3];
    }
    cin >> x;
    cout << f(x);
}
```

---

## 作者：FFTotoro (赞：3)

本题可以使用记忆化搜索。

用一个 `std::map` 来存储 $f(i)$ 的值。

具体地，按照题目要求，$f(i)=f\left(\left\lfloor\frac{i}{2}\right\rfloor\right)+f\left(\left\lfloor\frac{i}{3}\right\rfloor\right)$，每计算到一个答案，就将它存入 `map` 中。下次再求解到同样的直接返回 `map` 中存储的元素即可。

时间复杂度 $O(\log^2 N)$，可以轻易地通过本题。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int> m; // 存储答案的 map
int f(int n){
    if(m[n])return m[n]; // 存储过答案
    if(!n)return m[0]=1; // 递归边界
    return m[n]=f(n>>1ll)+f(n/3);
}
main(){
    int n; cin>>n;
    cout<<f(n)<<endl;
    return 0;
}
```

---

## 作者：FReQuenter (赞：2)

## 思路

按题意，我们可以写出 $f$ 函数：

```cpp
long long f(long long x){
    if(x==0ll) return 1ll;
    return f(x/2)+f(x/3);
}
```

但这样复杂度不足以通过。

我们发现这颗搜索树有很多重合的地方，可以使用 ```std::map``` 记忆化：把每次 $f$ 函数的值存下来，调用时，如果当前的 $x$ 已经在 ```map``` 里面有值，就不用再次递归，直接返回即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
std::map<int,int> mp;
int f(int x){
  if(!x) return 1;//边界
  if(mp[x]) return mp[x];//如果有值就返回
  int ans=f(x/2)+f(x/3);
  mp[x]=ans;//记忆化
  return ans;
}
signed main(){
  int n;
  std::cin>>n;
  std::cout<<f(n);
}
```

---

## 作者：andyli (赞：1)

在 Python 语言中可以使用 `functools` 中的 `lru_cache` 进行记忆化加速。
```python
from functools import lru_cache
@lru_cache
def f(n):
    return n == 0 and 1 or f(n // 2) + f(n // 3)
print(f(int(input())))
```

---

## 作者：lnwhl (赞：1)

做法就是记忆化搜索，不说了，这里给一份复杂度的证明。

先考虑暴力，搜索树的形态是一颗二叉树，树的深度 $k$ 介于 $\log_3^n\sim \log n$ 之间，共有约 $2^k$ 个节点。考虑最优的情况，$k=\log_3^{10^{18}}=38$，$2^{38}$ 的复杂度也肯定会超时。

再考虑记忆化，所有可能搜到的节点都是形如 $\lfloor \dfrac{n}{2^p3^q}\rfloor$ 的形式，$p,q$ 都是 $\log$ 级别的，所以总的状态数只有 $\log^2$ 种，复杂度 $\mathcal O(\log^2 n)$，这里把 $map$ 当作常数看了。

---

## 作者：Hisaishi_Kanade (赞：0)

考虑暴力的瓶颈在哪里。

$f(n)$ 会由 $2\times n\le i<4\times n$ 的数访问，而这就是时间的瓶颈。

发现 $f(x)$ 的值恒定，所以可以记录下来避免多次访问，这就是记忆化。

发现访问次数是 $\log^2 n$ 级别的，则总复杂度大概是 $O(\log^2 n\log n)$ 这样的。

```cpp 
#include <map>
#include <stdio.h>
std::map<long long,long long> q;
long long f(long long x)
{
	if(!x) return 1;
	if(q[x]) return q[x];
	else
		return q[x]=f(x/2)+f(x/3);
}
int main()
{
    long long n;
    scanf("%lld",&n);
    printf("%lld",f(n));
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc275_d)     
很简单的一道 dfs。          
首先，我们很容易模拟出题面给的 $f$ 函数：       
```cpp
inline ll dfs(ll x){
	if(x==0){
		return 1;
	}
	return dfs(x/2)+dfs(x/3);
}
```
但是，这份代码明显会 TLE。       
为什么呢？     
因为，在 $n=36$ 的时候，$6$ 会被重复计算几次，在 $n$ 更大的时候，会被重复计算的次数就会更多。     
但是 $f(n)$ 值永远不会变，所以我们引入记忆化。        
这里用 unordered_map，速度快且可以存任意的值。      
[CODE](https://www.luogu.com.cn/paste/p2gbdra9)

---

## 作者：Magic_World (赞：0)

# ABC_275D 题解

对 $10^{18}$ 打表可看出递归级别是 $O(\log N)$ 的，于是记忆化即可，使用 `unordered_map` 充当记忆化数组。

`unordered_map`  对应哈希表，哈希表的特点就是查找效率高，时间复杂度为常数级别 $O(1)$。

故总时间复杂度 $O(\log N)$ 

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
unordered_map<ll,ll> mp;
ll f(int x)
{
	if(x==0) return 1;
	if(mp[x]) return mp[x];
	return mp[x] = f(x/2)+f(x/3);
}
int main()
{
	ll n; cin>>n;
	cout<<f(n);
	return 0;
}

```



---

## 作者：二叉苹果树 (赞：0)

依据题目中给定的递归函数，计算即可。

注意到数据范围较大，使用 $\rm{map}$ 记录全部的 $f(x)$。

每一次记忆化的时间取决于 $\rm{map}$ 的 $\mathcal{O}(\log n)$， 计算的次数约为 $\mathcal{\log n}$，故最终的时间复杂度为 $\mathcal{O}(\log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
map<long long,long long>mem;
int calc(long long x)
{
    if(x==0)
        return 1;
    if(!mem[x])	//如果mem数组未赋值
        mem[x]=calc(x/2)+calc(x/3);
    return mem[x];
}
int main()
{
    cin>>n;
    cout<<calc(n)<<endl;	//通过calc函数计算
    return 0;
}
```


---

