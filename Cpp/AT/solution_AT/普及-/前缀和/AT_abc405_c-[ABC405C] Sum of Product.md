# [ABC405C] Sum of Product

## 题目描述

给你一个数列 $A=(A_1,A_2,\cdots,A_N)$。

求 $\sum\limits_{1\le i<j\le N} A_iA_j$ 的值。

## 说明/提示

**样例 1 解释**

答案为 $\sum\limits_{1\le i<j\le N} A_iA_j=A_1A_2+A_1A_3+A_2A_3=4\times 2+4\times 3+2\times 3=26$。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3
4 2 3```

### 输出

```
26```

## 样例 #2

### 输入

```
2
9 45```

### 输出

```
405```

## 样例 #3

### 输入

```
10
7781 8803 8630 9065 8831 9182 8593 7660 7548 8617```

### 输出

```
3227530139```

# 题解

## 作者：Jerry20231029 (赞：2)

## 思路

暴力计算显然超时，所以得用公式。

### 计算公式

计算 $\displaystyle \sum_{1\leq i<j\leq N} A_iA_j$ 的公式为：

$$
\sum_{1 \leq i < j \leq N} A_i A_j = \frac{1}{2} \left( \left( \sum_{i=1}^N A_i \right)^2 - \sum_{i=1}^N A_i^2 \right)
$$

### 推导过程

先将所有元素和的平方分解一下：

$$
\left( \sum_{i=1}^N A_i \right)^2 = \sum_{i=1}^N A_i^2 + 2 \sum_{1 \leq i < j \leq N} A_i A_j
$$

然后，我们发现后面那一项包含了题目的求式，所以把它提出来：

$$
2 \sum_{1 \leq i < j \leq N} A_i A_j = \left( \sum_{i=1}^N A_i \right)^2 - \sum_{i=1}^N A_i^2
$$

接着再化简：

$$
\sum_{1 \leq i < j \leq N} A_i A_j = \frac{1}{2} \left( \left( \sum_{i=1}^N A_i \right)^2 - \sum_{i=1}^N A_i^2 \right)
$$

就得到公式了。

## 代码

[AC 记录](https://atcoder.jp/contests/abc405/submissions/65764407)

```cpp
#include<iostream>
using namespace std;

typedef long long lld;

lld a[300100];

int main(){
	int n;
	lld s1=0,s2=0;
	cin>>n;
	for(int i = 1; i <= n; i++){
		cin>>a[i];
		s1 += a[i];
		s2 += a[i]*a[i];
	}
	cout<<(s1*s1-s2)/2;
	return 0;
}
```

---

## 作者：Gilbert1206 (赞：1)

## 题解：AT_abc405_c [ABC405C] Sum of Product

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc405_c)

## 思路

这道题给定了 $N$ 个数，每个数为 $a_i$，求出答案。

很明显从样例中可以看出每个数 $a_i$ 都乘了前面的 $i-1$ 个数，这样可以我们就可以通过乘法分配律的逆运算把前 $i-1$ 个数合起来变为 $\sum_{j=0}^{j<i} a_j$ 再乘上 $a_i$ 就可以知道当前答案，最后再把所有 $a_i$ 算出的答案加上就可以了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[600500],b[600050];
signed main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){//此时用了前缀和优化
		b[i]=b[i-1]+a[i];
	}
	int ans=0;
	for(int i=0;i<n;i++){
		ans+=(b[n-1]-b[i])*a[i];
	}//把当前所有关于a[i]的算出后加在ans中
	cout<<ans;
	return 0;
}
```

---

## 作者：banglee (赞：1)

### AT_abc405_c [ABC405C] Sum of Product 题解
[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc405_c)

[AtCoder 传送门](https://atcoder.jp/contests/abc405/tasks/abc405_c)

## 题目大意
给定一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\dots,A_N)$，求 $\displaystyle\ \sum_{1\leq\ i\ <\ j\leq\ N}\ A_iA_j$。

## 思路
显然可以暴力，但观察到 $2 \le N \le 3 \times 10^5$，因此暴力是不可行的。

考虑优化。

观察到：

$$
\left(\sum_{i=1}^N A_i \right)^2 = \sum_{i=1}^N A_i^2 + 2 \sum_{1 \leq i < j \leq N} A_i A_j
$$

因此，可以推导出：

$$
\sum_{1 \leq i < j \leq N} A_i A_j = \frac{1}{2} \left( \left( \sum_{i=1}^N A_i \right)^2 - \sum_{i=1}^N A_i^2 \right)
$$

这样，我们就可以只计算 $A$ 的总和和平方和，然后带进公式计算即可。

时间复杂度为 $O(n)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,sum,sqsum;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for (int i=1,x;i<=n;i++)
		cin>>x,sum+=x,sqsum+=x*x;
	cout<<(sum*sum-sqsum)/2;
	return 0;
}
```
[通过记录](https://atcoder.jp/contests/abc405/submissions/65751743)

---

## 作者：hzxphy (赞：1)

## 思路
可以通过化简得到：$ans= \displaystyle\sum_{1\leq i<j\leq N}A_iA_j =\displaystyle\sum_{1\leq i\leq N}\left(\displaystyle\sum_{i<j\leq N}A_iA_j\right)=\displaystyle\sum_{1\leq i\leq N}\left(A_i\times\displaystyle\sum_{i<j\leq N}A_j\right)$。

所以这个可以用前缀和计算 $\displaystyle\sum_{i<j\leq N}A_j$ 的值，然后直接枚举 $i$ 的值。

时间复杂度为 $O(n)$，可以通过此题。
## Code
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAXN=3e5;
int n,a[MAXN+1];
ll s[MAXN+1],ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        s[i]=s[i-1]+a[i];
    }
    for(int i=2;i<=n;i++){
        ans+=1ll*s[i-1]*a[i];
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：linjinkun (赞：0)

题目是要求 $\sum_{i = 1}^n\sum_{j = i+1}^na_ia_j$，实际上就是 $\sum_{i = 1}^na_i(\sum_{j = i+1}^na_j)$，然后发现 $\sum_{j = i+1}^na_j$ 可以用前缀和维护，于是就没了。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int a[N];
long long sum[N];
signed main()
{
    int n;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i = n;i;i--)
    {
        sum[i] = sum[i+1]+a[i];
    }
    long long num = 0;
    for(int i = 1;i<n;i++)
    {
        num+=(long long)a[i]*sum[i+1];
    }
    printf("%lld",num);
    return 0;
}
```

---

## 作者：All_Wrong_Answer (赞：0)

[luogu 题目传送门](https://www.luogu.com.cn/problem/AT_abc405_c)

[AT 题目传送门](https://atcoder.jp/contests/abc405/tasks/abc405_c)

## 思路：

首先把题目的 $\sum\limits_{1\le i<j\le N} A_iA_j$ 用乘法分配律转化一下变成 $\sum^{N}_{i=1} A_i \times (\sum^{N}_{j=i+1} A_j) $，$A_i$ 是给出的，所以问题就转化成了如何快速求 $\sum^{N}_{i+1} A_i$，这个显然可以前缀和维护一下。

然后求和就做完了。

## 完整代码：

其实 ```long long``` 就可以，但我赛时怕炸开了 ```__int128``` 哈。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline __int128 read()
{
	__int128 x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}//快读
void out(__int128 x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}//快写
__int128 da=0;
__int128 x;
__int128 m[1000005];
__int128 qj[1000005];//前缀和
int main(){
	x=read();
	for(int i=1;i<=x;i++){
		m[i]=read();
		qj[i]=qj[i-1]+m[i];
	}
	for(int i=1;i<=x;i++){
		da+=((qj[x]-qj[i])*m[i]);
	}
	out(da);
	return 0;
}

```

---

## 作者：__CrossBow_EXE__ (赞：0)

# 题解

为了简化问题，我们先来看样例中 $N=3$ 的情形。

显然，答案可以用下面的式子表示：

$$ans=A_1A_2+A_1A_3+A_2A_3$$

把 $A_1$ 提出来，得到

$$ans=A_1\times(A_2+A_3)+A_2A_3$$

不难发现，对于每个 $A_i$，我们只需要乘上它后面的所有数之和，再全部相加即可。

换句话说，答案其实就是：

$$ans=A_1(A_2+A_3+\dots+A_n)+A_2(A_3+A_4+\dots+A_n)+\dots+A_{n-1}A_n$$

注意到公式中有区间求和，前缀和维护即可。

还有一个细节需要注意：数据范围大，需要开 `long long`。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
int n;
int a[300005];
ll sum[300005];
unsigned ll ans=0;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(NULL);
	cin.tie(0),cout.tie(0);
	cin>>n;
//	n=300000;
	for(int i=1;i<=n;i++){
		cin>>a[i];
//		a[i]=10000;
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		ans+=a[i]*(sum[n]-sum[i]);
	}
	cout<<ans<<endl;
	return 0;
}
/*
---INFORMATIONS---
TIME:2025-05-10 20:05:58
PROBLEM:abc405c
CODE BY __CrossBow_EXE__ Luogu uid967841
*/
```

---

## 作者：CCY20130127 (赞：0)

## 题目大意：
[Sum of Product](https://www.luogu.com.cn/problem/AT_abc405_c)

上方为题目传送门，请自行查看。

## 题目分析：
这边介绍两种解题方法。

**第一种：乘法分配律。**

假设一个长度为 $4$ 的序列，分别为 $A_1,A_2,A_3,A_4$。根据题意答案就是 $A_1 \times (A_2+A_3+A_4)+A_2 \times (A_3+A_4)+A_3 \times A_4$。

这时就可以用前缀和数组储存从 $A_i$ 到 $A_j$ 的总和，最后循环相加就行了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int n,a[3*N],f[3*N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	f[0]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i]=f[i-1]+a[i];
	}
	int ans=0;
	for(int i=1;i<=n-1;i++){
		int k=f[n]-f[i];
		ans+=a[i]*k;
	}
	cout<<ans<<"\n";
	return 0;
}
```
**第二种：数学公式**

给定序列 $A=(A_1,A_2,A_3, \dots A_N)$，目标计算：
$$S=\sum_{1 \le i \le j \le N} A_iA_j$$

考虑所有元素的和的平方:
$$(\sum_{i=1}^{N} A_i)^2=\sum_{i=1}^{N} A_i^2+2 \times \sum_{1 \le i \le j \le N} A_iA_j$$

将上述等式变形，可以得到：
$$2S=(\sum_{i=1}^{N} A_i)^2-\sum_{i=1}^{N} A_i^2$$

化简得：
$$S=\frac{(\sum_{i=1}^{N} A_i)^2-\sum_{i=1}^{N} A_i^2}{2}$$

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
signed main() {
	cin >> n;
	int sum = 0, ans = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		sum += x;
		ans += x * x;
	}
	ans = (sum * sum - ans) / 2;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：ccxXF (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/AT_abc405_c)
## 题目分析
希望审核大大给过。

这是一道模拟题。我们注意到，题目让我们求 $ \displaystyle\ \sum_{1\leq\ i\ <\ j\leq\ N}\ A_iA_j$ 这一坨东西，再看一眼数据大小，$O(n^2)$ 肯定会 T 掉，所以不能直接暴力 $A_i \times A_j$。下面是我的方法。

我注意到，每一个数字都要被其他数字乘 $n - 1$ 次，所以可以使用**乘法分配律**和**前缀和**来写，但是如果这样写会有部分数字重复算了，所以我认为可以按照升序进行计算，如样例：
```
3
4 2 3
```
可以用**前缀和** $(f_3 - f_1) \times a_1 + (f_3 - f_2) \times a_2$，也就是 $A_1A_2+A_1A_3+A_2A_3=4\cdot\ 2+4\cdot\ 3+2\cdot\ 3=26 $。这样就将时间复杂度从 $O(n^2)$ 降到了 $O(n)$，就不会 T 掉了。

下面是代码。（不一定 AC，请谅解）
## 题目代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int n,a[300001],f[300001],sum;
signed main(){
	speed;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],f[i]=f[i-1]+a[i];//前缀和 
	for(int i=1;i<n;i++) //最后一个数字不能匹配任何一个数 
		sum+=a[i]*(f[n]-f[i]);
	cout<<sum;
	return 0;
}

```

---

## 作者：LittleAcbg (赞：0)

简单式子推导题，感觉很[原](https://www.luogu.com.cn/problem/AT_abc143_b)，不过数据范围貌似更大了。

$$
\begin{aligned}
\sum_{1\le i<j\le N}A_iA_j&=\sum_{j=2}^N\sum_{i=1}^{j-1}A_iA_j\\
&=\sum_{j=2}^NA_j\left(\sum_{i=1}^{j-1}A_i\right)
\end{aligned}
$$

考虑对 $A$ 序列求一个前缀和，即 $S_k=\displaystyle\sum_{i=1}^kA_i$，那么所求式就变为：

$$\sum_{j=2}^NA_jS_{j-1}$$

能够在 $O(N)$ 时间内完成。

注意答案最大可能达到 $\dfrac{10^5\left(10^5-1\right)}2\times\left(10^4\right)^2\approx10^{18}$，所以需要用 $64$ 位整型变量（例如 `long long`）存储。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 3e5+9;
ll n,a[N],s[N],ans;
int main()
{
    cin >> n;
    for (ll i = 1; i <= n; ++i) cin >> a[i];
    for (ll i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
    for (ll j = 2; j <= n; ++j) ans += a[j] * s[j - 1];
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Clare613 (赞：0)

## 思路：
这道题其实很简单，我们可以把算式列出来：
$$a_1a_2+a_1a_3+a_1a_4+\dots+a_{n-1}a_n$$
把这个式子用乘法分配律化简一下可得：
$$a_1(a_2+a_3+\dots+a_n)+a_2(a_3+a_4+\dots+a_n)+\dots+a_{n-1}a_n$$
于是我们只要跑一遍循环就能过了。
## code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[300005],sum=0,ans=0;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++){
		sum-=a[i];
		ans+=sum*a[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

给你一个长度为 $n$ 的序列 $a$，求 $\displaystyle\ \sum_{1\leq\ i\ <\ j\leq\ N}\ A_iA_j$。

### 思路

这道题如果用暴力做会超时，我们考虑更优的解法。

外面的 $i$ 那层循环是不可能省去的，但里面的 $j$ 我们可以用乘法分配律，直接用 $a_i$ 乘所有满足条件的 $a_j$ 的和，而所有满足条件的 $a_j$ 的和可以用前缀和优化。

注意开 `long long`。
### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[300005],s[300005],t;//long long
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];//前缀和优化
	}
	for(int i=1;i<=n;i++)
	{
		t+=a[i]*(s[n]-s[i]);//ai乘所有满足条件的aj的和
	}
	cout<<t; 
	return 0;
} 
```

---

## 作者：Nahida_Official (赞：0)

[原题 Link](https://atcoder.jp/contests/abc405/tasks/abc405_c)

## 题目大意：
给定一个长度为 $n$ 的数组 $a$，求：
$$\sum_{1 \le i < j \le n} a_i a_j$$

## 分析：

乍一看好像直接 $O(n^2)$ 跑就行了，但是$2 \le n \le 3 \times 10^5$ 打破你的暴力梦。

可以拆开式子看看：
$$\sum_{1 \le i < j \le n} a_i a_j=a_1\times a_2+a_1\times a_3+a_1\times a_4+ \cdots +a_1\times a_n+a_2\times a_3+ \cdots a_{n-1}\times a_n=a_1 \times \sum_{i=2}^n a_i+a_2 \times \sum_{i=3}^n a_i + \cdots +a_{n-1} \times a_n$$

一目了然，有了式子，我们可以想到统计 $a$ 数组的后缀和，然后再遍历计算即可，时间复杂度 $O(n)$。

下面的代码中 $sum$ 数组第 $i$ 位保存了 $a$ 数组后 $i$ 位的和，在统计的时候第 $a[i]$ 项要乘上 $sum[n-i]$ 才是正确答案。

## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
#define Sangonomiya signed
#define Kokomi main()
#define Love return
#define Nahida 0
#define Forever ;
#define IOS cin.tie(nullptr)->sync_with_stdio(false)
#define cin std::cin
#define cout std::cout
const int N=1e6;
int n,ans,cnt=1;
int a[N],sum[N];
Sangonomiya Kokomi{
	IOS;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=n;i>=1;i--){
        sum[cnt]=sum[cnt-1]+a[i];
        cnt++;
    }
    for(int i=1;i<=n;i++){
        ans+=(a[i]*sum[n-i]);
    }
    cout<<ans;
	Love Nahida Forever;
}
```

---

## 作者：songlll (赞：0)

# 题意
对数列 $A=(A_1,A_2,\dots,A_N)$,求 $x=\displaystyle\ \sum_{1\leq\ i\ <\ j\leq\ N}\ A_iA_j$。
# 思路
设：
$$sum_i=\displaystyle\ \sum_{1\leq\ k\leq i} A_i$$

则易知：
$$x=\displaystyle\ \sum_{1\leq\ i\leq N} sum_{i-1} \times A_i$$

很明显，所谓的 $sum_i$ 就是前缀和。

所以我们只需要维护出前缀和，再与 $A_i$ 相乘求和即可。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[(int)3e5+10];
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	long long sum=0/*当前的前缀和*/,ans=0/*答案*/;
	for(int i=0;i<n-1;i++){
		sum+=a[i];/*累计到前缀和中*/
		ans+=sum*a[i+1];/*计算答案*/
	}
	cout<<ans;
  return 0;
}
```

---

