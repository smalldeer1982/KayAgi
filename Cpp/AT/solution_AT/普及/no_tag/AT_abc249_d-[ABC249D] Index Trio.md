# [ABC249D] Index Trio

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc249/tasks/abc249_d

長さ $ N $ の整数列 $ A\ =\ (A_1,\ \dots,\ A_N) $ が与えられます。

以下の条件を全て満たす整数の組 $ (i,\ j,\ k) $ の総数を求めてください。

- $ 1\ \leq\ i,\ j,\ k\ \leq\ N $
- $ \frac{A_i}{A_j}\ =\ A_k $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

$ (i,\ j,\ k)\ =\ (1,\ 2,\ 3),\ (1,\ 3,\ 2) $ が条件を満たします。

## 样例 #1

### 输入

```
3
6 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
1
2```

### 输出

```
0```

## 样例 #3

### 输入

```
10
1 3 2 4 6 8 2 2 3 7```

### 输出

```
62```

# 题解

## 作者：_qingshu_ (赞：1)

# 题意：

给定序列 $a_n$，求满足 $\frac{a_i}{a_j}=a_k$ 的不同三元组 $(i,j,k)$ 的数量。

# 思路：

首先，这种带有除的式子不方便处理，我们将其转化为 $a_i=a_j \times a_k$。

那么我们现在需要求得的问题就很简单了，在序列中取两个数使得这两个数的乘积依然存在在数列之中。

因为本题值域较小，所以考虑用桶记录每一种值的个数，然后遍历 $a_j$ 与 $a_k$ 的值就好了。

# 优化：

当前思路时间复杂度为 $O(n^2)$ ，不足以支撑通过此题，所以考虑优化。我们发现当 $2\times10^5<a_j \times a_k $ 的时候是一定没有答案的，所以我们可以剪枝减去所有超限情况，更改遍历的值从下标到具体的值。

# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ton[5200010],ans,n,a;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a,ton[a]++;
	for(int i=1;i<=200000;i++)
	for(int j=1;i*j<=200000;j++)
	ans+=ton[i]*ton[j]*ton[i*j];
	cout<<ans;
}
```

---

## 作者：Tsawke (赞：1)

# [[ABC249D] Index Trio](https://www.luogu.com.cn/problem/AT_abc249_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC249D)

## 题面

给定序列 $ a_n $，求满足 $ \dfrac{a_i}{a_j} = a_k, 1 \le i, j, k \le n $ 的不同三元组 $ (i, j, k) $ 的个数。

## Solution

不难想到，原题式子不好处理，转换为 $ a_j \times a_k = a_i $，于是不难想到一定满足 $ a_j \mid a_i $，并且发现值域很小，所以显然建桶，$ buc_i $ 表示值为 $ i $ 的数量。不难想到 $ O(n) $ 枚举值域里每个数，然后再枚举值域范围内其所有倍数，每次枚举的贡献即为 $ buc_i \times buc_j \times buc_k $。

然后不难发现这东西就是个埃筛，所以复杂度显然 $ O(n \log \log n) $，通过调和级数等即可证明，这里略。

然后记得开 `long long`。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MAX (201000)

template < typename T = int >
inline T read(void);

int N;
int a[210000];
int buc[210000];
ll ans(0);

int main(){
    N = read();
    for(int i = 1; i <= N; ++i)buc[a[i] = read()]++;
    for(int i = 1; i <= MAX; ++i)
        for(int j = 1; i * j <= MAX; ++j)
            ans += (ll)buc[i] * buc[j] * buc[i * j];
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_11_30 初稿

update-2022_12_02 修改了公式里的一点细节

---

## 作者：InversionShadow (赞：0)

对于 $\dfrac{a_i}{a_j}=a_k$，我们可以将其转换为 $a_j \times a_k = a_i$，然后可以两重循环枚举 $a_j$ 和 $a_k$ 的值，开个桶记录一下 $a_i$ 出现了多少次（这里的 $a_i$ 指 $a_j \times a_k$），求和即可。

时间复杂度 $\mathcal{O(V \log V \log V)}$，$\mathcal{V}$ 指值域 $2 \times 10^5$。  

注意：不能用 `map` 记录，因为再乘了个 $\log n$ 后时间复杂度约为 $10^{10}$ 会爆炸。

[code.](https://atcoder.jp/contests/abc249/submissions/46933239)

---

## 作者：skyskyCCC (赞：0)

## 前言。
今天正好在家休息，于是写一篇题解庆祝一下。

这个题是一个简单的暴力题。
## 分析。
由题目得 $\frac{a_i}{a_j}=a_k$ 然后进行变换，等式两边同时乘 $a_j$ 得 $a_k \times a_j=a_i$ 的式子。因为 $N$ 的范围比较小，且值域比较小，所以考虑暴力枚举。

那么最朴素的做法就是直接暴力 $3$ 层循环，很显然，我们将收获一个超时大礼包。

那么如何优化呢？考虑桶。我们用桶去存 $a_i,a_j,a_k$ 这三个数是否存在，然后先遍历选定的数 $a_j$ 作为第一层循环，再遍历可以与它相搭配的数 $a_k$ 作为第二层循环，最后去找是否有一个数 $a_i$ 正好等于 $a_k\times a_j$ 的值。

如果您没有看懂这个步骤，那请您再看一眼最初提出的式子。

最后加上可能性，注意到数字有可能重复，所以相同数字的三元组但组合方式不同时，有**每个数乘积**个可能结果，所以答案可能很大。

代码如下，仅供参考：
```
#include<iostream>
#include<vector>
using namespace std;
int n,a[200005];
vector<int> t(200005);
//用变长数组去存这些数。
long long ans;
int main(){
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a[i];
        t[a[i]]++;
    }
    //开始暴力枚举。
    for (int i=1;i<=200000;i++){
        for (int j=1;i*j<=200000;j++){
            ans+=(long long)t[i]*t[j]*t[i*j];
        }
    }
    //注意类型转换。
    cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_zhx (赞：0)

# [ABC249D] Index Trio 题解

## 题意 

有数列 $a_n$，求满足 $\frac{a_i}{a_j}=a_k$ 的三元组个数。

### 解法

本题我们可以使用桶来记录 $a_{i},a_{j},a_i\times a_j$ 这三个数是否存在，和在序列中存在的次数，这样可以为了避免三层循环，防止超时。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
long long n,a,x,f[200055];
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
	{
        scanf("%lld",&a);
        f[a]++;//桶
    }
    for(int i=1;i<=N;i++) for(int j=1;j*i<=N;j++) x+=(f[i]*f[j]*f[i*j]);//求和
    cout<<x<<'\n';//输出
    return 0;
}
```


---

## 作者：LBYYSM_123 (赞：0)

## 题面翻译
给定序列 $ a_n $，求满足 $ \dfrac{a_i}{a_j} = a_k, 1 \le i, j, k, \le n $ 的不同三元组 $ (i, j, k) $ 的个数。
## 思路
我们可以从 $ \dfrac{a_i}{a_j} = a_k$ 推出 $a_i=a_j \times a_k$ 这个式子。接下来就好办了，用桶存储出现次数就行，此处我用 `map`。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200000
using namespace std;
int lin,n,ans=0;
map<int,int> m;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>lin;
		m[lin]++;
	}
	for(int i=1;i<=MAXN;i++)
		for(int j=1;i*j<=MAXN;j++)
			ans+=m[i]*m[j]*m[i*j];
	cout<<ans;
	return 0;
}
```


---

## 作者：Lemonlwl (赞：0)

## AT_abc249_d [ABC249D] Index Trio 题解
### 题意：
对于给定序列 $a$ 中的 $n$ 个元素，找出满足 $a_i=a_j \times a_k$ 的下标三元组 $(i,\ j,\ k)$ 的个数。

------------

### 分析：
本题我们可以使用桶标记的做法来记录 $a_i$，$a_j$，$a_i \times a_j$ 三个值是否存在以及在序列中存在的次数（注：这里我们用两个相乘的数来表示第三个数，为了避免三层循环）

因为题目中问的是下标的三元组，所以相同的数可以存在于不同的三元组，所以我们只需要依次枚举 $a_i$ 和 $a_j$ 出现的次数，再将表示出来的 $a_i \times a_j$ 出现的次数与前两个相乘就能得到不一定只出现一次的这三个值能够组成的所有不同的下标三元组。

最后再用一个变量进行累加即可。

------------

附上 [AC](https://www.luogu.com.cn/record/118238267) 代码：
```cpp
#include<iostream>
using namespace std;
long long n,sum;
long long a[1000005];  //记得开long long。
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		long long v;
		cin>>v;   //输入。
		a[v]++;   //用桶标记该值出现的次数。
	}
	for(long long i=1;i<=200005;i++){  //第一个值。
		for(long long j=1;i*j<=200005;j++){  //第二个值，因为三个值取值范围一样，所以可以优化。
			sum+=(a[i]*a[j]*a[i*j]);  //累加这三个值所组成的不同的下标三元组的数量。
		}
	}
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：Erica_N_Contina (赞：0)

# [ABC249D] Index Trio


给定序列 $a_n$，求满足 $\dfrac{a_i}{a_j} = a_k, 1 \le i, j, k, \le n$ 的不同三元组 $(i, j, k)$ 的个数。

**输入格式**

输入通过标准输入进行，格式如下。

> $N$ $A_1$ $\ldots$ $A_N$

**限制条件**

- $1\ \leq\ N\ \leq\ 2\ \times\ 10^5$

- $1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5\ \,\ (1\ \leq\ i\ \leq\ N)$

- 所有的输入都是整数。


## 解说

我们将这个式子进行变形 $\dfrac{a_i}{a_j} = a_k$ 得到 $a_i=a_j \times a_k$。

我们发现该题 $a_i$ 的值域很小，于是我们就可以用一个桶 $t_i$ 统计 $i$ 出现的次数，然后枚举每一个 $a_j$ 和 $a_k$，查询是否存在 $a_i$ 满足 $a_i=a_j \times a_k$，如果有满足的就将 $ans$ 加上 $t_i\times t_j\times t_k$。

在统计完每个数的个数后，我们使用一个函数 **unique** 对数组进行去重。

## **函数 unique**

`unique()` 是 C++ 标准库函数里面的函数，其功能是去除**相邻**的重复元素（只保留一个），所以使用前需要对数组进行排序。

```C++
l = unique(a+1,a+n+1) - (a+1);
//or
l = unique(a,a+n) - (a);
```

上面的一个使用中已经给出该函数的一个使用方法，对于长度为 $n$ 数组 $a$，`unique(a,a+n) - a - 1` 返回的是去重后的**数组长度**。

那它是怎么实现去重的呢？删除？

不是，它并没有将重复的元素删除，而是把重复的元素放到数组的最后面藏起来了。

eg. 原来的数组 1 2 2 3 3 3 4

unique 后 **1 2 3 4** 2 3 3

## 解说续

在对 $a$ 数组去重后，我们就可以使用一个二层循环枚举 $a_j$ 和 $a_k$ 了，然后特判一下是否存在 $a_i$ 满足 $a_i=a_j \times a_k$ 如果有，那么就把 $ans$ 加上 $t_i\times t_j\times t_k$。

这里注意一个小问题，就是 $O(2\times10^{10})$ 复杂度是过不去的，考虑到 $a_i\le 2\times10^{5}$，是否可以考虑到在循环中加入 一个 if 判断 $a_i\le 2\times10^{5}$ 是否成立，若否，则跳过。

但我们发现，这个 if 语句也是有复杂度的！所以在循环内加入 if 是不可取的。（如下）
```c++
for(int i=1;i<=l;i++){
        for(int j=1;j<=l&&;j++){
            if(1ll*a[i]*a[j]>200000)continue;
            ans+=t[a[i]*a[j]]*t[a[i]]*t[a[j]];
        }
    }
```

我们发现，$a$ 数组是从小到大排好序的（因为我们用 `sort()` 进行了一次排序），所以在一个固定的 $i$ 下，一旦枚举到一个 $j$ 使得 $a_i \times a_j>200000$，我们就停止这层循环，因为后面的 $a_j$ 一定大于当前的 $a_j$，那么后面的 $a_i \times a_j$ 就会更大，一定不满足要求。

我们只需要将上面的代码中的 `continue;` 改成 `break;` 即可，或者像如下写法：

```c++
/*/
       . Coding by Ntsc .
       . Chargcy required.
/*/

#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e6+5;

int n,ans,a[N],t[N];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        t[a[i]]++;
    }
    sort(a+1,a+n+1);
    int l=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=l;i++){
        for(int j=1;j<=l;j++){
            if(1ll*a[i]*a[j]>200000)continue;
            ans+=t[a[i]*a[j]]*t[a[i]]*t[a[j]];
        }
    }
    cout<<ans<<endl;
    return 0;
}

```






---

## 作者：TLEWA (赞：0)

将 $\frac{a_i}{a_j}  = a_k$ 变形为 $a_i = a_j \times a_k$，注意到值域很小，考虑对值域建桶，并枚举所有可能的 $a_i,a_j$ 的值，计算三元组的数量，值域为 $M$ 时，时间复杂度为 $O(\sum_{j=1}^{M}  \frac{M}{j} )$，当值域取最大值时，这个数字也不是很大，不会超时。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=200000;
long long n,a,t[maxn+5];
long long ans; 

int main() {
	cin >> n;
	for(int i=1;i<=n;++i) {
		cin >> a;
		t[a]++;
	}
	for(int i=1;i<=maxn;++i) {
		if(t[i]==0) continue; //优化，然而可以不加
		for(int j=i;j<=maxn;j+=i) {
			ans+=t[i]*t[j]*t[j/i];
		}
	}
	cout << ans;
	return 0;
}

```


---

## 作者：fish_love_cat (赞：0)

小修改：把博客的隐藏状态改掉了。

---

首先，我们得把这句话：

$\frac{a_{i}}{a_{j}}=a_{k}$

换个形式，理解为：

$a_{j} \times a_{k}=a_{i}$

那么，整个题目就好做多了。从小到大把数据用桶存起来，遍历每一个数字（$a_{j}$），再遍历每一种可能和第一个数字组合的数字（$a_{k}$），然后看看有没有对应这两个数的积（$a_{i}$），有则增加 $ans$，否则不变。

**需要注意的是，数字有可能重复，相同数字的三元组，实际上能组合出的数量足足有：**

$f_{j} \times f_{k} \times f_{i}$

（$f$ 是用来统计 $i,j,k$ 个数的）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;
long long f[210000];
int main(){
    long long n;
    cin>>n;
    for(long long x,i=1;i<=n;i++){
        cin>>x;
        f[x]++;//计数
    }
    for(long long i=1;i<=201000;i++){
        for(long long j=1;i*j<=201000;j++){
            ans+=f[i]*f[j]*f[i*j];//不用if什么的，如果是0的话，结果也是0。
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

[Accepted.](https://www.luogu.com.cn/record/105220143)

~~欢迎捉虫~~

---

