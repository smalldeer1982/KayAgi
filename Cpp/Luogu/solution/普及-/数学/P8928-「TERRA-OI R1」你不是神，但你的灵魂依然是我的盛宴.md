# 「TERRA-OI R1」你不是神，但你的灵魂依然是我的盛宴

## 题目背景

踏在这木质的平台上，嘎吱嘎吱作响，你从包里掏出了各式各样的药水，逐一饮下后一股暖意从心底升腾起来，你拿出了精心准备的诱饵，那是用三位仆从的精华凝聚而成，你将其高举头顶，想要引出那位噬神者。天空开始弥漫着蓝紫色的迷雾，这种氛围压得你喘不过气，恍惚间，你面前的空间开始撕裂出一条裂缝，一条身披紫色外壳的巨蟒从中钻出，你拿起了手上的巨剑，听着一声又一声的嘶吼，你知道这将是一场恶战......

## 题目描述

请求出：

$\sum_{i=1}^{n} \sum_{j=1}^{m}(i\times j \bmod p)$ 

的值，其中 $n,m,p$ 为给定的值。

## 说明/提示

#### 【样例解释 #1】

很显然 $i\times j$ 只有 $[1,2,3,2,4,6,3,6,9]$ 这几种情况，这些情况的和为 $36$。

------------

#### 【数据范围】

**本题采用捆绑测试。**

| Subtask | Score | $n,m\le$ |
| :----------: | :----------: | :----------: |
| $1$ | $20$ | $10^3$ |
| $2$ | $30$ | $10^6$ |
| $3$ | $50$ | $10^{12}$ |

对于 $100\%$ 的数据，满足 $1\le n,m\le10^{12}$，$1\le p\le10^3$。


## 样例 #1

### 输入

```
3 3 10```

### 输出

```
36```

## 样例 #2

### 输入

```
114514 1919810 233```

### 输出

```
696303234```

# 题解

## 作者：MCRS_lizi (赞：20)

题目意思已经很清楚了，直接讲解思路吧。

首先瞟一眼数据范围， $n,m\le10^{12}$ 决定了这题时间复杂度与 $n,m$ 有关的可能性不大，而 $p\le10^3$ 这个范围可以让我们大胆推断这题复杂度是 $O(p^2)$。

那具体如何实现呢？

对于 $i\bmod p$ 与 $j\bmod p$ 的结果而言，组合起来一共只有 $p^2$ 种情况，意思是我们可以求出满足这两个式子为某个结果时的情况总数，再两两组合，将第一个式子情况数乘上第二个式子情况数，再乘上组合后对应的结果即可。

那么还有个要将解决的问题，这个情况总数该如何求取？

经过思考，我们不难发现每一种可能的值至少有 $\left \lfloor \dfrac{n}{p}  \right \rfloor $ 以及 $\left \lfloor \dfrac{m}{p}  \right \rfloor $ 种情况，最后再根据枚举的结果为多少确定这个情况数是否要加一（判断方式是枚举的结果数值加上刚刚算出来至少情况数乘以 $p$ 是否小于等于 $n$ 或 $m$）。

这样子这题就算解决了。

多一嘴，别忘了开 long long。

**CODE：**

```cpp
#include<bits/stdc++.h>
#define int long long//不开longlong见祖宗
using namespace std;
const int mod=1e9+7;
int n,m,p,f[1010][1010],cnt1[1010],cnt2[1010],ans;
signed main()
{
	cin>>n>>m>>p;
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<p;j++)
		{
			f[i][j]=i*j%p;//先预处理一下结果，其实不处理也没关系，不过这样后面代码会不那么shishan
		}
	}
	for(int i=0;i<p;i++)
	{
		cnt1[i]+=n/p%mod,cnt2[i]+=m/p%mod;
		if(n/p*p+i<=n)
		{
			cnt1[i]++;
		}
		if(m/p*p+i<=m)
		{
			cnt2[i]++;
		}//情况统计，理由见上方
	}
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<p;j++)
		{
			ans+=cnt1[i]*cnt2[j]%mod*f[i][j]%mod;//针对每种情况乘以结果
		}
	}
	cout<<ans%mod;
 	return 0;
}
//抄袭题解这个习惯不好哦
```


---

## 作者：IYSY2009I (赞：5)

我的做法与官方题解的不太一样。

首先我们先求出来 $a_{i,j}=i \times j \bmod p$，然后对 $a$ 求出二维前缀和 $sum$，以方便下一步的计算。

我们考虑对问题分成四部分，然后考虑每一个部分的答案再相加，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/6t26dnha.png)

对于红色部分，可以发现就是 $\left\lfloor\dfrac{n}{p}\right\rfloor \cdot \left\lfloor\dfrac{m}{p}\right\rfloor$ 个 $a$ 数组，于是这部分的答案就是 $sum_{p,p} \cdot \left\lfloor\dfrac{n}{p}\right\rfloor \cdot \left\lfloor\dfrac{m}{p}\right\rfloor$。

对于绿色部分，可以发现就是 $\left\lfloor\dfrac{n}{p}\right\rfloor$ 个 $a$ 数组的前 $m \bmod p$ 列，所以这部分的答案就是 $\left\lfloor\dfrac{n}{p}\right\rfloor \cdot sum_{p,m \bmod p}$。

黄色部分同理，答案是 $\left\lfloor\dfrac{m}{p}\right\rfloor \cdot sum_{n \bmod p,p}$。

橙色部分可以发现一个 $a$ 数组的前 $ n \bmod p$ 行和前 $m \bmod p$ 列，这部分的答案就是 $sum_{n \bmod p,m \bmod p}$。

然后加起来，然后没了。

代码：

```cpp
#include<iostream>
#include<cstdio>
#define mod 1000000007
using namespace std;
__int128 read(){
	__int128 x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
__int128 a[1005][1005];
__int128 sum[1005][1005];
int main(){
	__int128 n=read(),m=read(),p=read();
	for(__int128 i=1;i<=p;i++)
		for(__int128 j=1;j<=p;j++)
			a[i][j]=i*j%p;
	for(__int128 i=1;i<=p;i++)
		for(__int128 j=i;j<=p;j++){
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
			sum[j][i]=sum[j][i-1]+sum[j-1][i]-sum[j-1][i-1]+a[j][i];
		}
	printf("%d",int(((n/p)*(m/p)*sum[p][p]+sum[n%p][p]*(m/p)+sum[p][m%p]*(n/p)+sum[n%p][m%p])%mod));
	return 0;
}
```


---

## 作者：BlanketRice (赞：4)

### 前言

虽然我没打月赛，但是还是看到了这道水题。

### 题意

给定 $ n,m,p $，求 $ \sum_{i=1}^n \sum_{j=1}^m i \times j \bmod p $。

### 朴素思路

考虑枚（暴）举（力），枚举 $ i $ 和 $ j $，直接求，复杂度 $ O(nm) $，只能过第一个子任务。

### 正解思路

我们考虑找规律，将这个方阵的值输出一下看看，就会发现，第 $ p $ 行，第 $ p $ 列的 $ i \times j \bmod p $ 值都为 $ 0 $。原因：因为第 $ p $ 行，$ p $ 列一定存在一个 $ p $ 与另一个数相乘，取模后为 $ 0 $。接着观察，剩下的方阵全都是相等的。那我们只需要求 $ p \times p $ 的方阵就可以了，剩下的都是重复。

我们设 $ ans_{i,j} $ 表示在一个基本的方阵里的二维区间和，则我们在算重复的方阵时只需要求 $ ans_{p,p} $ 的值即可。

那重复了多少呢？$ n \times m $ 的方阵，只需要看看 $ n / p $ 和 $ m / p $ 的值，一相乘就是重复的数量，然后和 $ ans_{i,j} $ 相乘即可。

剩下的部分就是只取方阵一部分的地方了，我们看看 $ n \bmod p $ 和 $ m \bmod p $ 的值，分别是重复方阵的两遍的剩余方阵的长（宽），然后再相加，再加上一个小方形矩阵。

给一个图加深理解：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/c608min2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define endl "\n"
#define space " "
#define int LL
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int INF = 1e9;
const int N = 2 * 1e5;
struct FastIO {
    inline int read () {
        int ans = 0;
        char ch = getchar ();
        while (!isdigit (ch) && ch != '-') ch = getchar ();
        bool sign = 0;
        if (ch == '-') sign = 1, ch = getchar ();
        while (isdigit (ch)) ans = (ans << 3) + (ans << 1) + (ch ^ 48), ch = getchar ();
        return (sign == 1 ? -ans : ans);
    }
    inline void print (int x) {
        if (x < 0) putchar ('-'), x = -x;
        if (x > 9) print (x / 10);
        putchar (x % 10 + 48);
    }
    inline void printsp (int x) {
        print (x);
        cout << space;
    }
    inline void println (int x) {
        print (x);
        cout << endl;
    }
}io;
#define read io.read
#define print io.print
#define printsp io.printsp
#define println io.println
int mod = 1e9 + 7;
int n, m, p;
int ans[1005][1005];
signed main () {
    cin >> n >> m >> p;
    for (register int i = 1; i <= p; ++ i) {
        for (register int j = 1; j <= p; ++ j) {
            ans[i][j] = ans[i][j] + ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
            ans[i][j] += i * j % p;
        }
    }
    int ansi = n / p, ansj = m / p;
    int Ans = ans[p][p] * ansi % mod * ansj % mod;
    int ansmi = n % p, ansmj = m % p;
    Ans += ans[p][ansmj] * ansi % mod;
    Ans += ans[ansmi][p] * ansj % mod;
    Ans += ans[ansmi][ansmj] % mod;
    cout << Ans % mod << endl;
    return 0;
}
```

---

## 作者：Moon_Traveller (赞：4)

[-->传送门](https://www.luogu.com.cn/problem/P8928) 

# 这是一篇思路很奇葩的题解，但应该比较好理解

## 题意简述：

$i$ 从 $1$ 到 $n$ 遍历，$j$ 从 $1$ 到 $m$ 遍历，把所有 $i \times j \bmod p$ 的结果加在一起，并将结果对 $10^9+7$ 取模，输出。

## 20分做法（暴力）

直接遍历即可，就不贴代码了。

但是这样的做法面对 $10^{12} \times 10^{12}$ 的数据，是一定会超时的！

所以，我们就有了第二种做法——

## 100分做法（打表/模拟）

### 思路：

~~俗话说，打表出省一。~~

这里我们自己造一个数据：

我们先不考虑 $\bmod~p$。

```python
设 n = 5, m = 8
则暴力得出的矩阵为
 1  2  3  4  5  6  7  8
 2  4  6  8 10 12 14 16
 3  6  9 12 15 18 21 24
 4  8 12 16 20 24 28 32
 5 10 15 20 25 30 35 40
```

然后再把 $p$ 带进去，那么：

```python
当 p = 1 时:
 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0

p = 2:
 1  0  1  0  1  0  1  0
 0  0  0  0  0  0  0  1
 1  0  1  0  1  0  1  0
 0  0  0  0  0  0  0  1
 1  0  1  0  1  0  1  0

p = 3:
 1  2  0  1  2  0  1  2
 2  1  0  2  1  0  2  1
 0  0  0  0  0  0  0  0
 1  2  0  1  2  0  1  2
 2  1  0  2  1  0  2  1

p = 4:
 1  2  3  0  1  2  3  0
 2  0  2  0  2  0  2  0
 3  2  1  0  3  2  1  0
 0  0  0  0  0  0  0  0
 1  2  3  0  1  2  3  0

p = 5:
 1  2  3  4  0  1  2  3
 2  4  1  3  0  2  4  1
 3  1  4  2  0  3  1  4
 4  3  2  1  0  4  3  2
 0  0  0  0  0  0  0  0
```

什么？还没看出来？那如果把所有 $0$ 都划掉呢：

```python
p = 1:
 +  +  +  +  +  +  +  +
 +  +  +  +  +  +  +  +
 +  +  +  +  +  +  +  +
 +  +  +  +  +  +  +  +
 +  +  +  +  +  +  +  +

p = 2：
 1  |  1  |  1  |  1  |
 -  +  -  +  -  +  -  +
 1  |  1  |  1  |  1  |
 -  +  -  +  -  +  -  +
 1  |  1  |  1  |  1  |

p = 3：
 1  2  |  1  2  |  1  2
 2  1  |  2  1  |  2  1
 -  -  +  -  -  +  -  -
 1  2  |  1  2  |  1  2
 2  1  |  2  1  |  2  1

p = 4：
 1  2  3  |  1  2  3  |
 2  0  2  |  2  0  2  |
 3  2  1  |  3  2  1  |
 -  -  -  +  -  -  -  +
 1  2  3  |  1  2  3  |

p = 5：
 1  2  3  4  |  1  2  3
 2  4  1  3  |  2  4  1
 3  1  4  2  |  3  1  4
 4  3  2  1  |  4  3  2
 -  -  -  -  +  -  -  -
```

没错！整个矩阵被 $0$ 分割成了若干个 $(p-1) \times (p-1)$ 的正方形矩阵，那么这样一来，复杂度就减了不少。

所以，具体要如何实现呢？

我们取其中一个矩阵来观察：

```python
 1  2  |  1  2  |  1  2
 2  1  |  2  1  |  2  1
 -  -  +  -  -  +  -  -
 1  2  |  1  2  |  1  2
 2  1  |  2  1  |  2  1
```

首先可以看出，这个大矩阵被“完美”地分割成了六个小矩阵，且小矩阵的边长是 $p-1$。

但是，他还不够完美。为什么这样说呢？因为大矩阵的宽（$n$）和长（$m$）与小矩阵的边长（$p-1$）并没有什么倍数关系。那么，假如我们将 $n$ 和 $m$ 都加 $1$，就变成了……

```python
 1  2  |  1  2  |  1  2  |
 2  1  |  2  1  |  2  1  |
 -  -  +  -  -  +  -  -  |
 1  2  |  1  2  |  1  2  |
 2  1  |  2  1  |  2  1  |
 -  -  +  -  -  +  -  -  +
```

这个时候，$n$ 就变成了 $6$， $m$ 变成了 $8$，而它们正好是 $2$（$p$ 的值）的**整数倍**！

所以，大矩阵中就含有 $[(n+1) \div p] \times [(m+1) \div p]$ 个小矩阵。

### **但是！！！！**

如果碰到这样的矩阵：

```python
 1  2  3  |  1  2  3  |
 2  0  2  |  2  0  2  |
 3  2  1  |  3  2  1  |
 -  -  -  +  -  -  -  +
 1  2  3  |  1  2  3  |
```

最下面莫名其妙多出来一行，该怎么处理呢？

可以看出来，下面多出来的长度，就是 $n \bmod p$ 的值，那么我们只需要知道小矩阵中每一行的值的总和，就可以计算下面多出来的部分了。

```python
 1  2  3  4  |  1  2  3
 2  4  1  3  |  2  4  1
 3  1  4  2  |  3  1  4
 4  3  2  1  |  4  3  2
 -  -  -  -  +  -  -  -
```

右面与下面同理，只需要知道小矩阵中每一列的值之和，就可以求出。

### 但是！！！！

如果我们造一个稍强一点的数据，就会发现：

```python
 1  2  3  4  |  1  2  3
 2  4  1  3  |  2  4  1
 3  1  4  2  |  3  1  4
 4  3  2  1  |  4  3  2
 -  -  -  -  +  -  -  -
 1  2  3  4  |  1  2  3
（注：此时 n = 6, m = 8, p = 5）
```

右下角怎么还有一块啊？！（恼

但是只要我们稍微想一下，就不难看出：

这不就是开头的暴力吗？？

最后，将所有求出的值加起来即可，别忘了取模！！

### 你们最爱的 Code

```cpp
#include <iostream>
using namespace std;
#define int long long

const int modx = 1e9 + 7;
int n, m, p;
int nn, mm; // nn：向下延伸的长度，mm：向右延伸的长度
int pn, pm;
int pnm[10005][10005]; // 存储小矩阵中 (i,j) 位置的值
int pnn[10005]; // 存储小矩阵中第 i 行的值
int pmm[10005]; // 存储小矩阵中第 i 列的值
int a; // 存储每个小方阵中所有值的和
int ans;

int add_nm(int tn, int tm)
{
    int tmp = 0;
    for(int i = 1; i <= tn; i++)
    {
        for(int j = 1; j <= tm; j++)
        {
            tmp += pnm[i][j];
        }
    }
    return tmp;
}

void make_pnm()
{
    for(int i = 1; i <= p - 1; i++)
    {
        for(int j = 1; j <= p - 1; j++)
        {
            pnm[i][j] = (i * j) % p;
            pnn[i] += pnm[i][j];
            pmm[j] += pnm[i][j];
            a += pnm[i][j];
        }
    }
    return;
}

signed main()
{
    cin >> n >> m >> p;
    make_pnm(); // 找到小方阵，并计算每行、每列和总值
    nn = (n + 1) % p;
    mm = (m + 1) % p;
    if(nn != 0)
    {
        nn--;
    }
    if(mm != 0)
    {
        mm--;
    }
    pn = ((n + 1) / p);
    pm = ((m + 1) / p);
    ans += pn; // 这里相当于 ans = pn * pm * a，但是这样会爆 long long，所以就分开乘，并每一次都取模一下
    ans %= modx;
    ans *= pm;
    ans %= modx;
    ans *= a;
    ans %= modx;
    for(int i = 1; i <= mm; i++) // 计算下面延伸部分的总和
    {
        ans += pmm[i] * pn;
    }
    ans %= modx;
    for(int i = 1; i <= nn; i++) // 计算右面延伸部分的总和
    {
        ans += pnn[i] * pm;
    }
    ans %= modx;
    ans += add_nm(nn, mm); // 计算右下部分的总和
    ans %= modx;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：robinyqc (赞：3)

### 解题思路

题目是要求 $\bigg[\sum_{i=1}^{n} \sum_{j=1}^{m}(i\times j \bmod p)\bigg]\bmod 10^9+7$。

其实，$\sum_{i=1}^{n} \sum_{j=1}^{m}(i\times j \bmod p)$ 可以再转变成：

$$\sum_{i=1}^{n} \sum_{j=1}^{m}\bigg[(i\bmod p)\times (j\bmod p) \bmod p\bigg]$$

所以我们可以发现这些数是循环出现的，具有周期性：每个大小 $p\times p$ ，相邻排列的矩阵都是相同的。

所以我们只需要求 $S=\sum_{i=1}^p \sum_{j=1}^p(i\times j \bmod p)$ ，最后再乘上矩阵的个数即可。当然，最后有一些“边角料”（下图中的 $S',S'',S'''$），他们也具有周期性，只不过不完整罢了。通过类似的方法可以求出。

可以配着这幅图理解：

![配图](https://cdn.luogu.com.cn/upload/image_hosting/2bd5npr6.png?x-oss-process=image/resize,m_lfit,h_170,w_225,h_170,w_225,h_400,w_575)

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int calsum(int n,int m,int p){//计算 n*m 大小矩阵的和模 p
	int summatp=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			summatp+=(i*j)%p;
	return summatp;
}
signed main(){
	int n,m,p,S,S1,S2,S3;// S1 即文中的 S'，以此类推
	scanf("%lld%lld%lld",&n,&m,&p);
	const int P=1e9+7;
	S=n/p%P*(m/p)%P*calsum(p,p,p)%P;
	S1=n/p%P*calsum(p,m%p,p)%P;
	S2=m/p%P*calsum(n%p,p,p)%P;
	S3=calsum(n%p,m%p,p)%P;
	printf("%lld",(S+S1+S2+S3)%P);
	return 0;
}
```


---

## 作者：luogu_gza (赞：3)

$\ \ \ \ \sum_{i=1}^{n}\sum_{j=1}^{m}(i \times j \operatorname{mod} p)$

$=\sum_{i=1}^{n}\sum_{j=1}^{m}( (i \operatorname{mod} p) \times (j \operatorname{mod} p)\operatorname{mod} p)$

考虑枚举 $(i \operatorname{mod} p)$ 和 $(j \operatorname{mod} p)$ 。

令 $f(n,k)=\sum_{i=1}^{n} [(i \operatorname{mod} p)=k]$

则式子可以表示为： $\sum_{k_1=0}^{p-1}\sum_{k_2=0}^{p-1} (i \times j \operatorname{mod} p) \times f(n,k_1) \times f(m,k_2)$

而简单推式子可得 $f(n,k)=\lfloor \frac{n+k}{p} \rfloor$

那么代码也很简单了

```cpp
R(n,m,p);
fo(i,0,p-1) a[i]=(n+i)/p;
fo(i,0,p-1) b[i]=(m+i)/p;
fo(i,1,p-1) fo(j,1,p-1) ans+=(i*j%p)*a[i]%mod*b[j]%mod;
write(ans%mod);
```

`R` 和 `write` 分别是快读快输。

`fo(i,a,b)` 表示循环变量为 `i` ，从 `a` 循环到 `b` 。

---

## 作者：wuyonghuming (赞：3)

### 分析：
首先通过

$i \times j \bmod p$ 一定等于 $(i+p) \times j \bmod p$

$i \times j \bmod p$ 一定等于 $i \times (j+p) \bmod p$

可以知道

$(i+ap) \times (j+bp) \bmod p$ 一定等于 $i \times j \bmod p$

然后可以得到一个边长为 $p$ 方阵，其中前第 $x$ 行，第 $y$ 列，记录了方阵中

$\sum_{i=1}^x \sum_{j=1}^y (i \times j \bmod p)$

可以通过二维前缀和预处理每一个数值。

取 $p=7$

```
  1   3   6  10  15  21  21 
  3   9  18  23  31  42  42 
  6  18  29  39  48  63  63 
 10  23  39  51  66  84  84 
 15  31  48  66  85 105 105 
 21  42  63  84 105 126 126 
 21  42  63  84 105 126 126 
```

可知$s_{i,j}=s_{i-1,j}+s_{i,j-1}-s_{i-1,j-1}+i \times j \bmod p$

然后发现这个 $n$ 行 $m$ 列的矩阵里面有很多边长为 $p$ 的小正方形。

取 $n=11,m=17,p=5$
```
 1  3  6 10 10  1  3  6 10 10  1  3  6 10 10  1  3 
 3  9 13 20 20  3  9 13 20 20  3  9 13 20 20  3  9 
 6 13 21 30 30  6 13 21 30 30  6 13 21 30 30  6 13 
10 20 30 40 40 10 20 30 40 40 10 20 30 40 40 10 20 
10 20 30 40 40 10 20 30 40 40 10 20 30 40 40 10 20 
 1  3  6 10 10  1  3  6 10 10  1  3  6 10 10  1  3 
 3  9 13 20 20  3  9 13 20 20  3  9 13 20 20  3  9 
 6 13 21 30 30  6 13 21 30 30  6 13 21 30 30  6 13 
10 20 30 40 40 10 20 30 40 40 10 20 30 40 40 10 20 
10 20 30 40 40 10 20 30 40 40 10 20 30 40 40 10 20 
 1  3  6 10 10  1  3  6 10 10  1  3  6 10 10  1  3
```
左上角：
其中边长为 $p$ 的正方形共有 $\left\lfloor\dfrac{n}{p}\right\rfloor \times \left\lfloor\dfrac{m}{p}\right\rfloor=2 \times3=6$ 个。

右上角：
$\left\lfloor\dfrac{n}{p}\right\rfloor$ 个正方形第 $p$ 行，第 $m \bmod p$ 列的值。

左下角：
$\left\lfloor\dfrac{m}{p}\right\rfloor$ 个正方形第 $n \bmod p$行，第 $p$ 列的值。

右下角：正方形第 $n \bmod p$行，第 $m \bmod p$ 列的值。

一共是 $40 \times 6+20 \times 2+10 \times 3+3=313$。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int s[1001][1001];
int main()
{
	long long n,m,p,ans;
	cin>>n>>m>>p;
	for(int i=1;i<=p;i++)
		for(int j=1;j<=p;j++)
			s[i][j]=(s[i-1][j]+s[i][j-1]-s[i-1][j-1]+(i*j)%p)%int(1e9+7);
	ans=(((n/p)%int(1e9+7))*(m/p)%int(1e9+7))*s[p][p]+s[n%p][m%p]+n/p*s[p][m%p]+m/p*s[n%p][p];
	cout<<ans%int(1e9+7);
	return 0;
}

```


---

## 作者：wangzikang (赞：2)

题意：求 $\sum_{i=1}^n \sum_{j=1}^m (i\times j \bmod p)$ 的值

$n,m \le 10^{12},p \le 10^3$

我们发现 $p$ 很小，所以我们从 $p$ 入手。

先将式子拆成 $\sum_{i=1}^n \sum_{j=1}^m (i \bmod p \times (j \bmod p) \bmod p)$ 

考虑每个 $i \bmod p,j \bmod p$ 被循环到多少次，显然对于每个 $i \le n \bmod p$ 被循环到的次数为 $ \left \lfloor \frac{n}{p} \right \rfloor$ ，否则为 $ \left \lfloor \frac{n}{p} \right \rfloor + 1$，对于每个 $j \le m \bmod p$ 被循环到的次数为 $ \left \lfloor \frac{m}{p} \right \rfloor $ ，否则为 $ \left \lfloor \frac{m}{p} \right \rfloor + 1$ 。

这样，答案显然，我们只需要枚举 $i \bmod p,j \bmod p$ ，复杂度显然为$O(p^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod (int(1e9+7))
long long n,m,p,ans;
signed main(){
	cin>>n>>m>>p;
	for(long long i=0;i<p;++i){
		long long i_times=n/p%mod;//i出现的次数
		if(i<=n%p){
			i_times++;
			i_times%=mod; 
		}
		for(long long j=0;j<p;++j){
			long long j_times=m/p;//j出现的次数
			if(j<=m%p){
				j_times++;
				m_times%=mod; 
			}
			ans+=(i_times*j_times%mod)*(i*j%p)%mod;//统计答案
			ans%=mod; 
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：lilong (赞：2)

### 题意

给定 $n,m,p$，求

$$\sum_{i=1}^n \sum_{j=1}^m (i \times j \bmod p)$$

### 分析

看到 $1 \le n,m \le 10^{12}$，知道 $O(nm)$ 的暴力算法行不通。但 $1 \le p \le 10^3$，范围很小，是本题的突破口。

那怎么利用这个特点呢？这里需要用到一条同余的性质，即

$$(i \times j) \bmod p = (i \bmod p \times j \bmod p) \bmod p$$

具体证明方法这里不详解。

由此我们可以发现，$i$ 和 $j$ 取余后都满足 $0 \le i,j < p$，而 $p$ 的范围很小，因此考虑先预处理所有的 $i \times j \bmod p(0 \le i,j < p)$，然后统计不同余数出现的次数，最后运用乘法原理计数，同时取模即可。

**注意输入的 $p$ 和 $10^9+7$ 两个模数用在不同的地方，预处理时用 $p$，计数时用 $10^9+7$。**

### Code

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int MOD=1000000007;
int cnt[1001][1001];
int a[1001],b[1001],x,y;
int ans;
signed main()
{
    int n,m,p;
    cin>>n>>m>>p;
    x=n%p,y=m%p;
    for(int i=0;i<p;i++)
        for(int j=0;j<p;j++)
            cnt[i][j]=i*j%p;
    for(int i=0;i<p;i++)
    {
        a[i]=n/p;
        b[i]=m/p;
        if(i<=x) a[i]++;
        if(i<=y) b[i]++;
    }
    for(int i=0;i<p;i++)
        for(int j=0;j<p;j++)
            ans=(ans+(cnt[i][j]*a[i]%MOD*b[j])%MOD)%MOD;
    cout<<ans;
    return 0;
}
```


---

## 作者：WER_very_fox (赞：1)

## 题目描述

请求出：

$\sum_{i=1}^{n} \sum_{j=1}^{m}(i\times j \bmod p)$ 

的值，其中 $n,m,p$ 为给定的值。

## 解答

简单推式子题：

$\begin{aligned}\sum_{i=1}^{n} \sum_{j=1}^{m}(i\times j \bmod p)=&\lfloor\dfrac{n}{p}\rfloor\sum_{i=1}^{p}\sum_{j=1}^{m}(i\times j \bmod p)+\sum_{i=1}^{\{\frac{n}{p}\}}\sum_{j=1}^{m}(i\times j \bmod p)\\=&\lfloor\dfrac{n}{p}\rfloor\lfloor\dfrac{m}{p}\rfloor\sum_{i=1}^{p}\sum_{j=1}^{p}(i\times j \bmod p)+\lfloor\dfrac{n}{p}\rfloor\sum_{i=1}^{p}\sum_{j=1}^{\{\frac{m}{p}\}}(i\times j \bmod p)\\&+\lfloor\dfrac{m}{p}\rfloor\sum_{i=1}^{p}\sum_{j=1}^{\{\frac{n}{p}\}}(i\times j \bmod p)+\lfloor\dfrac{n}{p}\rfloor\lfloor\frac{m}{p}\rfloor\sum_{i=1}^{\{\frac{n}{p}\}}\sum_{j=1}^{\{\frac{m}{p}\}}(i\times j \bmod p)\end{aligned}$

下面只需 $O(p^2)$ 求出各个式子的值即可。代码见下：
```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
ll m,mr,n,nr,p,k,s,sum,sm,sn;
ll mod=1e9+7;
int main()
{
	int i,j;
    scanf("%lld%lld%lld",&n,&m,&p);
    mr=m%p;m/=p;nr=n%p;n/=p;
    for(i=1;i<p;i++)
    {
    	s=0;
    	for(j=1;j<p;j++)
    	{
    		s+=(j*i)%p;
    		s%=mod;
		}
		if(i<=mr) sm+=s,sm%=mod;
		if(i<=nr) sn+=s,sn%=mod;
		sum+=s,sum%=mod;
	}
	sum*=m;sum%=mod;
	sum*=n;sum%=mod;
	sum+=(m*sn)%mod+(n*sm)%mod;sum%=mod;
	for(i=1;i<=mr;i++)
		for(j=1;j<=nr;j++)
			sum+=(j*i)%p,sum%=mod;
	printf("%lld",sum);
    return 0;
}
```


---

## 作者：sgl654321 (赞：1)

题外话：一道挺好的数学题。赛时最优解纪念。
### 题目大意
不再赘述。
### 解题思路
我们直接考虑正解。观察到，$n,m$ 的范围很大，而 $p$ 的却很小。我们先取 $p=20$ 进行探究。枚举所有的 $n$，并遍历 $m$，看看 $n\times m \bmod p$ 是怎么变化的。

当 $n=1$ 时：$1\times 1 \mod 20=1,\cdots,1\times 20\bmod 20=0,1\times 21 \bmod 20=1$。 

当 $n=2$ 时：$2\times 1 \mod 20=2,\cdots,2\times 10 \bmod 20=0,2\times 11\bmod 20 =2$。

当 $n=3$ 时：$3\times 1\mod 20=3,\cdots,3\times 20\bmod 20=0,3\times 21\bmod 20=3$。

当 $n=4$ 时：$4\times 1\mod 20=4,\cdots,4\times 5\bmod 20=0,4\times 6\bmod 20=4$

$\cdots$

当 $n=21$ 时：与 $n=1$ 时完全一致。

通过上述枚举，我们发现了这些规律：

1. 对于每一个 $n$，我们都发现随着 $m$ 的增大，将会出现一个**循环节** $d$，就是说 $m=x+d$ 时的值与 $m=x$ 时的一样。观察到 $d\le p$。
2. $n$ 这个整体也会出现循环节，且循环节长度为 $p$，就是说 $n=x+20$ 时的情况与 $n=x$ 时完全一致。

那么现在的关键问题就是如何求出每一个 $n$ 的循环节了。由于 $n$ 也会出现循环节，那么我们只需要求出 $n\in[1,p]$ 的每一个循环节，我们一一记录为 $d_i$。同时我们还要顺便求出循环节内的元素和，记录为 $s_i$。

容易证明，$d_i=\dfrac{p}{\gcd(i,p)}$。那么区间内的元素和就可以利用等差数列求和公式了。经过推导可以得到，$s_i=\dfrac{d_i\times(p-\gcd(i,p))}{2}$。

那么对于每一个 $n$，我们就可以求出它对答案的贡献了。因为一个循环节长度为 $d_i$，那么其就存在 $\lfloor \dfrac{m}{d_i}\rfloor$ 个循环节，首先将答案加上 $\lfloor\dfrac{m}{d_i}\rfloor\times s_i$。然后剩下的长度就不足 $p$ 了，枚举计算即可。通过上述步骤，我们可以求出 $i\in[1,p],j\in[1,m]$ 的答案之和，记录为一个 $save$。

最后考虑如何累加答案，首先由规律 $2$ 可以得到，总共由 $\lfloor \dfrac{n}{p}\rfloor$ 个整体循环节，所以先把答案加上 $\lfloor\dfrac{n}{p}\rfloor\times save$。剩下的没有计算的 $n$ 就不足 $p$ 个了。接下来再枚举剩下的 $n$ 即可。

### 参考代码
注意取模。题中有两个模数 $p$ 和 $10^9+7$，务必分清。
```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
long long n,m,p,save,daan,f;
long long d[1010],s[1010],ans[1010];
long long gcd(long long x,long long y){
	if(x==0)return y;
	return gcd(y%x,x);
}
int main(){
	cin>>n>>m>>p;
	if(p==1){
		cout<<0<<endl;
		return 0;
	}
	for(int i=1;i<=p;i++){
		//计算 n=i 时的循环节长度，以及循环节内元素之和
		d[i]=p/gcd(i,p);
		s[i]=d[i]*(p-gcd(i,p))/2; 
		ans[i]=m/d[i]*s[i]%mod;
		save=m%d[i];
		for(int j=1;j<=save;j++)
			ans[i]=(ans[i]+j*i%p)%mod;
	} 
//	for(int i=1;i<=p;i++)
//		cout<<i<<" "<<ans[i]<<endl;
	for(int i=1;i<=p;i++)
		f=(f+ans[i])%mod;
	daan=n/p*f%mod;
	save=n%p;
	for(int i=1;i<=save;i++)
		daan=(daan+ans[i])%mod;
	cout<<daan%mod<<endl;
	return 0;
}
```

---

## 作者：minVan (赞：1)

**解题思路**

先让 $n,m$ 对 $p$ 进行带余除法，得 $\begin{cases}
   n\div p=b_1\dots n' \\
   m\div p=b_2\dots m'
\end{cases}$，然后记录 $1\dots p-1$ 每个值该乘多少次，$c_{1,i}=\begin{cases}
   b_1+1 &\text{if } i\le n \\
   b_1 &\text{if } i>n
\end{cases}$，$c_{2,i}=\begin{cases}
   b_2+1 &\text{if } i\le n \\
   b_2 &\text{if } i>n
\end{cases}$，最后就只需要求出 $\sum^{p-1}_{i=1}\sum^{p-1}_{j=1}(i\times j \times c_{1,i}\times c_{2,j}\mod 10^9+7)$ 就行了。

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Mod = 1e9 + 7;
ll cnt1[1005], cnt2[1005];
int main() {
	int p;
	ll n, m, base1, base2, ans = 0;
	cin >> n >> m >> p;
	base1 = n / p;
	n %= p;
	base2 = m / p;
	m %= p;
	for (int i = 1; i < p; i++) {
		cnt1[i] = base1 + (i <= n ? 1 : 0);
		cnt2[i] = base2 + (i <= m ? 1 : 0);
	}
	for (int i = 1; i < p; i++) {
		for (int j = 1; j < p; j++) {
			ans = (ans + i * j % p * cnt1[i] % Mod * cnt2[j] % Mod) % Mod;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：1)

# 前言

很好的一道题。

# 思路

根据数据发现：$n,m\le 10^{12}$，说明此题的复杂度可能与 $n,m$ 没有关系，而 $p \le 1000$，说明复杂度与 $p$ 多少沾了点关系。

别的大佬的题解都是各种推式子，在这里我给大家推荐一个蒟蒻的方法。

那就是找规律！

我们先设 $n = 20,m = 20,p = 10$（样例过于小，找不出来规律），并且输出所有的 $(i \times j \mod p)$，试着找找规律。

输出的内容如下：

![https://cdn.luogu.com.cn/upload/image_hosting/lpncm3hp.png](https://cdn.luogu.com.cn/upload/image_hosting/lpncm3hp.png)

并提供[构造程序](https://www.luogu.com.cn/paste/d4770dbq)。

我们逐行找找规律。发现每一行都是有循环节的，例如第一行的循环节为 $\left \{ 1,2,3,4,5,6,7,8,9,0 \right \} $，第二行为 $\left \{ 2,4,6,8,0 \right \}$ ，第三行为 $\left \{3,6,9,2,5,8,1,4,7,0  \right \} $。你发现了什么？没错！每个循环节都是由 $0$ 结尾的，我们只要求出一个循环节的和，再乘上循环节个数，并加上剩余部分就好了。

那么到底该怎么求一行的总和呢？设一行总和为 $S$，一个循环节的和为 $s$，循环节长度为 $c$，剩余的和为 $a$。我们有 $S = \dfrac{m}{c}\times s + a$。

好的，我们现在算出了一行的和，那么多行呢？

通过发现，每行的和也构成了一个循环节（标志是第十、二十行。）！那我们也可以通过类似的算法来求出答案。

行的和的循环节长度是多少呢？通过发现，长度为 $p$。

设全部行的和为 $S$，一行的和为 $s$，剩余的行数为 $a$。我们有 $S = \dfrac{n}{p}\times s + as$。你也可以运用乘法结合律。

好了，现在我们就可以给出代码了。



# 代码

```cpp
signed main()
{
	ll mod = 1e9+7;
	ll n,m,p;
	ll s = 0,S = 0,ans = 0;//避免变量重复，令 s 为循环节总和，
	                       //S 为行的总和，ans 为答案。 
	ll i,j;
	cin>>n>>m>>p;
	for(i=1;i<=p;i++)//p 为行总和的循环节长度，先求出一个循环节的总和。 
	{
		s = 0;//每行清空。
		ll k = 0;//k 为目前 (i*j mod p) 的值。 
		int cnt = 0;//cnt 为循环节长度。 
		for(j=1;j<=p;j++)//求出每行的循环节长度。 
		{
			cnt++;
			k += i;
			k %= p;
			s += k;
			if(k==0)//如果 k = 0，说明循环节结束了，果断退出。 
				break; 
		}
		//现在我们求出了一个行的循环节，可以算一行的总和了。 
		s = s*(m/cnt);//算出一行内除去剩余部分的和。 
		s %= mod;
		S = s;
		ll a = 0;//a 为剩余元素的和。 
		k = 0;//k 还是为当前 (i*j mod p) 的值。 
		for(j=1;j<=m%cnt;j++)//算出剩余元素的和。
		{
			k += i;
			k %= p;
			a += k;
		}
		S += a;//一行的和要加上剩余部分。
		S %= mod;
		ans += S;//总答案加上一行的和。 
		ans %= mod;
	}
	//我们现在算出了行的循环节的元素的和，该求出答案了。
	ans = ans*(n/p);//套用公式。 
	ans %= mod; 
	//算出余下部分。
	for(i=1;i<=n%p;i++)//现在就和求出一行的和十分相似，就不加注释了。 
	{
		ll cnt = 0;
		ll s = 0;
		ll k = 0;
		for(j=1;j<=p;j++)
		{
			cnt++;
			k += i;
			k %= p;
			s += k;
			if(k==0)
				break;
		}
		s = s*(m/cnt);
		s %= mod;
		S = s;
		ll a = 0;
		k = 0;
		for(j=1;j<=p%cnt;j++)//坑，防止不劳而获。 
		{
			k += i;
			k %= p;
			a += k;
		}
		S += a;
		S %= mod;
		ans += S;
		ans %= mod;
	}
	cout<<ans%mod<<endl;
   return 0;
}

```
# 附

有可能我的代码不如其他大佬的简短，但一定是非常容易理解的，顺便推荐一道类似的好题：暴龙的火锅。

---

