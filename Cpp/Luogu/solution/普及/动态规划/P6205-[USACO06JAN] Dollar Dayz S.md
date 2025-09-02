# [USACO06JAN] Dollar Dayz S

## 题目描述

FJ 到商场买工具。商场里有 $K$ 种工具（$1 \leq K \leq 100$），价格分别为 $1,2,\ldots,K$ 元。FJ 手里有 $N$ 元（$1 \leq N \leq 1000$），必须花完。他有多少种购买方案呢？

## 样例 #1

### 输入

```
5 3```

### 输出

```
5```

# 题解

## 作者：IntrepidStrayer (赞：11)

## 题意：
有$K$种物品，价格分别为$1,2,...,K$。每种物品可以买无限次。用$n$元钱买物品，求刚好花完的方案数。

## 题解：
### 算法：完全背包
设$f_j$为刚好花完$j$元的方案数。刚好花完$j$元，可以看做刚好花完$j-i(1\le i\le j)$元，然后买了一个价格为$i$的物品。于是可以推出状态转移方程：

$f_j=\sum\limits_{i=1}^j f_{j-i}$

其中$f_0=1$，即不花钱有一种方案。

此题的答案超出了$long long$的范围，所以要用$\_\_int128 $；而$\operatorname{printf}$不支持$\_\_int128 $，所以要手写快写。

### 代码：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
#define rei register int
#define FOR(i, l, r) for(rei i = l; i <= r; ++i)
typedef __int128 ll;
ll f[1001];
int n, m;
int print(ll x) {//快写
	if(x == 0) return putchar(48) + putchar(10);
	if(x >= 10) print(x / 10);
	putchar(x % 10 + 48);
}
signed main() {
	scanf("%d%d", &m, &n);
	f[0] = 1;
	FOR(i, 1, n)//外层循环枚举物品，内层循环枚举钱数，保证f[j-i]用到时已经计算过
		FOR(j, i, m)
			f[j] += f[j - i];
	print(f[m]);
	putchar(10);//换行
	return 0;
}
```

---

## 作者：夜枭只会舔fufu (赞：5)

## 写给DP新手的题解（好吧我也是蒟蒻（

首先，我们推一下式子

我们令$f[j]$来表示我们选择到第j元钱的方案数

那么我们枚举一个$i$表示我们当前选了$j-i$元钱的东西，然后又选了这么一个价值为i的物品

那么我们肯定要保证$i<j$吧？

 $\sum\limits_{i=1}^{k}\sum\limits_{j=i}^{n}f[j]+=f[j-i];$
 
为什么这里的是$f[j]+=f[j-i]$呢？
 
我们可以发现，当$f[j-i]$转移到$f[j]$的时候，$f[j-i]$已经有了一些情况（显而易见（因为在枚举$f[j]$之前，必定先枚举的$f[j-i]$，那么在转移的时候就不会出现像$f[j]$转移了，$f[j-i]$没转移的情况

但是我们又发现，这肯定是炸$longlong$的

所以我们用了个小技巧——int128

这是一个能存128位的东西（应该是吧？

（但是在本地编译器会炸（别问我为什么（我也不知道

~~copy~~代码时间！
```
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
__int128 f[10001];
void write(__int128 x)
{
    if(x>9) write(x/10);//如果x>9的话就递归它的最高位，再往下依次输出 
    putchar(x%10+'0');//输出这个数的末尾/kk（+'0'是为了让它转成字符类型的 
}
int main()
{
	int n,k;
	cin>>n>>k;
	f[0]=1;//初始化！让n为0时的方案数为1 
	for(int i=1;i<=k;i++)//枚举每一个物品 
	{
		for(int j=i;j<=n;j++)//必须大于i，否则买不了/kk 
		{
			f[j]+=f[j-i];//那么这个方案数就是上面所推导的一坨 
		}
	}
	write(f[n]);//要用__int128否则会炸longlong（ull也好像不行 
	return 0;
}
```


---

## 作者：Alarm5854 (赞：5)

推销一下我的新博客：https://yce3216037.github.io/post/luo-gu-p6205-ti-jie/

这道题目一看，就是一道背包裸题，用完全背包的方法求方案数即可，我以为开了LL就不会见祖宗了，我就写了这样的代码：
```cpp
#include<cstdio>
#define ll long long
using namespace std;
const int N = 1000 + 10;
FILE *fin, *fout;
inline int read(ll &x) {//快读
	char c = 0; int f = x = 0;
	while (c < 48 || c > 57) {
		if (c == -1) return 0;
		if (c == '-') f = 1; c = fgetc(fin);
	}
	while (c > 47 && c < 58) x = (x << 3) + (x << 1) + (c & 15), c = fgetc(fin);
	if (f) x = -x; return 1;
}
template<class T, class... Args> inline int read(T &x, Args&... args) {
	return read(x) + read(args...);
}
inline int write(ll x) {//快写
	if (x < 0) return fputc(45, fout), write(-x);
	if (x > 9) write(x / 10);
	return fputc((x % 10) | 48, fout), 1;
}
ll n, k, dp[N];
int main() {
	#ifdef ONLINE_JUDGE
	fin = stdin;
	fout = stdout;
	#else
	fin = fopen("P6205.in", "rb");
	fout = fopen("P6205.out", "wb");
	#endif
	read(n, k), dp[0] = 1;
	for (ll i = 1; i <= k; ++i)//完全背包模板，v[i]=i,w[i]=i
		for (ll j = i; j <= n; ++j)
			dp[j] += dp[j - i];
	write(dp[n]);
	return 0;
}
```
WTF？70分？看来不开高精见祖宗了，我为了图卡常，于是写了一个万进制的压位高精！
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1000 + 10;
const int base = 10000;
FILE *fin, *fout;
struct bigint {
	int a[11];
	bigint(){memset(a, 0, sizeof(a)), a[0] = 1;}//初始化
	inline int& operator [](int n) {
		return a[n];
	}
	inline bigint& operator =(int x) {
		a[0] = 0; if (!x) return a[0] = 1, *this;
		while (x) a[++a[0]] = x % base, x /= base;
		return *this;
	}
	inline friend bigint operator +(bigint a, bigint b) {//两个数相加
		if (b[0] > a[0]) a[0] = b[0];
		for (int i = 1; i <= a[0]; ++i) a[i] += b[i];
		for (int i = 1; i <= a[0]; ++i) if (a[i] >= base) a[i] -= base, ++a[i + 1];
		if (a[a[0] + 1]) ++a[0]; return a;
	}
	inline friend bigint& operator +=(bigint& a, bigint b) {
		return a = a + b;
	}
};
inline int read(int &x) {
	char c = 0; int f = x = 0;
	while (c < 48 || c > 57) {
		if (c == -1) return 0;
		if (c == '-') f = 1; c = fgetc(fin);
	}
	while (c > 47 && c < 58) x = (x << 3) + (x << 1) + (c & 15), c = fgetc(fin);
	if (f) x = -x; return 1;
}
template<class T, class... Args> inline int read(T &x, Args&... args) {
	return read(x) + read(args...);
}
inline int write(bigint x) {
	fprintf(fout, "%d", x[x[0]]);
	for (int i = x[0] - 1; i; --i)
		fprintf(fout, "%04d", x[i]);
	return 1;
}
int n, k;
bigint dp[N];
int main() {
	#ifdef ONLINE_JUDGE
	fin = stdin;
	fout = stdout;
	#else
	fin = fopen("P6205.in", "rb");
	fout = fopen("P6205.out", "wb");
	#endif
	read(n, k), dp[0] = 1;
	for (int i = 1; i <= k; ++i)
		for (int j = i; j <= n; ++j)
			dp[j] += dp[j - i];
	write(dp[n]);
	return 0;
}
```
于是就A了。当然，也可一用`__int128`来水，但是，只要数据范围拓展至 $N\le2000$，`__int128`就炸了，而我的高精度只需要改一点就可以继续使用了。

---

## 作者：David_H_ (赞：4)

这题嘛，是要用高精度的。（真就 DP 要写高精度咯）

**但是**，笔者很懒，所以不想写高精度的板子。

我们知道，`long long` 是等价于 `__int64` 的，那么，有没有 `__int128` 呢？

诶，还真的有。但是注意，`__int128` 不可以通过 `printf` 或者 `cout` 输出的，同时，应该只能在 Linux 系统下使用（笔者的 Windows 10 就不可以运行）。所以要打个快写的板子（至少比高精度好）：

```cpp
void print(__int128 x) {
   if (x > 0) print(x / 10);
   else putchar(48);          // "0" 的 ASCII 码为 48
   putchar(x % 10 + 48);
}
```

有了这些之后，这题就是一道 DP 的板子题，代码如下：

```cpp
#define ll __int128   // 方便起见，定义一下
#include <bits/stdc++.h>
using namespace std;
ll f[1001];
int n, m;
int print(ll x) { //快写
    if (x == 0)
        return putchar(48) + putchar(10);
    if (x >= 10)
        print(x / 10);
    return putchar(x % 10 + 48);
}
int main() {
    scanf("%d%d", &m, &n);
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= m; ++j)
            f[j] += f[j - i];
    print(f[m]);
    return 0;
}
```

这是可以 AC 的：[评测记录](https://www.luogu.com.cn/record/34177696)。

那么，如果你勤快一点，可以背一下板子：
```cpp
struct Bignum {
    short digits[100000];                           // 节省空间
    Bignum() { memset(digits, 0, sizeof(digits)); } // 初始化
    Bignum(string x) {
        memset(digits, 0, sizeof(digits));
        for (int i = 1; i <= x.length(); i++) {
            digits[i] = x[x.length() - i] - '0';
        }
    } // string 转 高精度
    friend Bignum operator+(Bignum x, Bignum y) {
        Bignum sum;
        int inc = 0;
        for (int i = 1; i <= 100000; i++) {
            sum.digits[i] = x.digits[i] + y.digits[i] + inc;
            if (sum.digits[i] >= 10) {
                inc++;
                sum.digits[i] -= 10;
            } else
                inc = 0;
        }
        return sum;
    } // 重载运算符
};
```
然后正常用就可以了。接下来就是版子题了，代码就不贴了/kk

---

## 作者：Forever1507 (赞：1)

# [传送门](https://www.luogu.com.cn/problem/P6205)
### 第一眼看过去：这不是完全背包模板吗？
### 然后非常愉快的写了一个正常的完全背包模板
```cpp
#include<bits/stdc++.h>
#define int long long//不开longlong见祖宗 
using namespace std;
int k,n,val[105],w[105];
int dp[1005];
signed main(){
	cin>>n>>k;
	dp[0]=1;//初始化
	for(int i=1;i<=k;i++){
		for(int j=i;j<=n;j++){
			dp[j]=dp[j]+dp[j-i];//状态转移方程
		}
	}
	cout<<dp[n];
	return 0;
}
```

### [然而！！！](https://www.luogu.com.cn/record/40185297)
### WA了。。。。。。
### 当我细细品味之后，我发现当输入极限数据时，出来了个负数
### 事实证明:我！要！高！精！
### 提供一个函数：
```cpp
string add(string a/*1号加数*/, string b/*2号加数*/) //利用字符串实现高精度
{
    string c;//答案
    int l1=a.length();
    int l2=b.length();
    if (l1<l2) 
    {
        for (int i=1; i<=l2-l1; i++) a='0'+a;
    }
    else 
    {
        for (int i=1; i<=l1-l2; i++) b='0'+b;
    }
    l1=a.length();
    l2=b.length();
    int tmp=0,jinwei=0;//存进位
    for (int i=l1-1; i>=0; i--) 
    {
        tmp=a[i]-'0'+b[i]-'0'+jinwei;
        jinwei=tmp/10;
        tmp%=10;
        c=char(tmp+'0')+c;
    }
    if (jinwei) c=char(jinwei+'0')+c;
    return c;//返回答案
}
```

### 那么结合模板，我们可以得到AC代码：
```cpp
#include<bits/stdc++.h>
#define int long long//不开longlong见祖宗 
using namespace std;
int k,n,val[105],w[105];
string dp[1005];
char a1[101],b1[101];
int a[101],b[101],c[101];
string add(string a, string b) //看前面注释
{
    string c;
    int l1=a.length();
    int l2=b.length();
    if (l1<l2) 
    {
        for (int i=1; i<=l2-l1; i++) a='0'+a;
    }
    else 
    {
        for (int i=1; i<=l1-l2; i++) b='0'+b;
    }
    l1=a.length();
    l2=b.length();
    int tmp=0,jinwei=0;
    for (int i=l1-1; i>=0; i--) 
    {
        tmp=a[i]-'0'+b[i]-'0'+jinwei;
        jinwei=tmp/10;
        tmp%=10;
        c=char(tmp+'0')+c;
    }
    if (jinwei) c=char(jinwei+'0')+c;//最后加上进位
    return c;
}
//如果你用宏定义来开LL，就得写signed main（因为没有long long main)
signed main(){//看前面注释
	cin>>n>>k;
	dp[0]="1";//初始化要改一下，因为要用字符串
	for(int i=1;i<=k;i++){
		for(int j=i;j<=n;j++){
			dp[j]=add(dp[j],dp[j-i]);
		}
	}
	cout<<dp[n];
	return 0;//好习惯（之前看到有人不写return 0然后OLE）
}
```


---

## 作者：BotDand (赞：1)

8.24 修改$\LaTeX$

2021.7.17 再次修改 $\LaTeX$
# Problems
FJ 到商场买工具。商场里有 $K$ 种工具（$1 \leq K \leq 100$），价格分别为 $1,2,\ldots,K$ 元。FJ 手里有 $N$ 元（$1 \leq N \leq 1000$），必须花完。他有多少种购买方案呢？
# Answer
这题跟货币系统有点像。

设 $f_i$ 为刚好花完 $i$ 的方案数，则可以推出转移方程 $\sum^i_{j=1}f_{i-j}$

初始值：$f_{0}=1$

但是这题的答案超出了 `long long` 的范围，于是用 $\text{int128}$ +快写
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
__int128 f[1001];
int n,m;
inline void write(__int128 x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}//快写
int main()
{
    cin>>m>>n;//读入m和n
    f[0]=1;//初始值
    for(int i=1;i<=n;++i)
        for(int j=i;j<=m;++j)
            f[j]+=f[j-i];//转移方程
    write(f[m]);//输出
    return 0;
}
```

---

## 作者：bovine__kebi (赞：1)

这一题可以算是个背包的练手题，看别的大佬已经讲过了__int128那个坑点，我就来讲点关于背包的东西。

先来看看题目，大致的题意就是给你一个数字N，让你把它分成k组。这不就是让我们整数拆分吗，而且还没有特殊的条件，那我们就很容易想到完全背包。

理清了题意，我们就来看看如何解这个完全背包。我们令$f[x]$为能分成的最大组数，就可以的到背包的状态：  
每次给出一个小于n的数i，并且给出枚举的总重量j  
状态转移方程：$f[j]=f[j]+f[j-i]$  
然后直接枚举，就可以得到答案了，还不理解的可以看[这里](https://www.luogu.com.cn/problem/P1616)

代码来了（~~你们想看的也只有这里吧~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
_in128 f[1005];\\为什么要_int128后面有讲到
void print(_int128 x) {\\为什么要快写后面也有讲到
    if(x < 0) putchar(48)+putchar(10);
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
} 
int main()
{
    scanf("%d %d",&n,&k);
    f[0]=1;\\如果是0的话方案数就全是是0了，可以理解为边界递推条件，所以要特殊处理为1
    for(_int128 i=1;i<=k;i++)
    {
        for(_int128 j=i;j<=n;j++)
        {
            f[j]+=f[j-i];\\状态转移方程前面有解释
        }
    }
    print(f[n]);\\输出
    printf("\n");
    return 0;
}
```

解释一下为什么要快写和__int128

大家看一下数据范围，是有可能爆long long的，而且后面没有模数，所以要__int128,不然要像那个大佬一样写高精。然而，printf不能输出__int128类型的数据，所以要自己手写快写

解释一下快写的原理

快写就是快速输出，会比printf和cout快一些，原理就是将数字转成字符类型的输出，putchar和getchar都是很高效的

解释一下为什么用一位背包

二维背包其实也是可以的，但是如果数据过大，容易爆炸，所以用一维完全背包比较保险一些。

背包题目合集：  
[采药](https://www.luogu.com.cn/problem/P1048)  
[装箱问题](https://www.luogu.com.cn/problem/P1049)  
[疯狂的采药](https://www.luogu.com.cn/problem/P1616)  
进阶题目：  
[要好好想想的题目](https://www.luogu.com.cn/problem/P6189)


管理员求过TwT

---

## 作者：Autism_ever (赞：0)

### 本题有k个物品，n元钱，全部花完
### 完全背包，上。

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,f[2005];
int main()
{
	int i,j;
	cin>>n>>k;
	f[0]=1;
	for(i=1;i<=k;i++)
	{
		for(j=0;j<=n;j++)
		{
			f[i+j]=f[i+j]+f[j];
		}
	}
	cout<<f[n]<<endl;
	return 0;
}
```

# ------------

### ???70分，啊，数据下载下来，太大了。
### 用高精带来胜利的曙光

### 加油，奥利给


# ------------

### 满分代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,f[2005][1005]={1,1};
void jiafa(int a[],int b[]){
	int i,j;
	for(i=1;i<=max(a[0],b[0]);i++)
	{
		a[i]=a[i]+b[i];
	}
	for(i=1;i<=max(a[0],b[0]);i++)
	{
		if(a[i]>=10)
		{
			a[i]-=10;
			a[i+1]++;
		}
	}
	if(a[max(a[0],b[0])+1]!=0)
	{
		a[0]=max(a[0],b[0])+1;
	}
	else
	{
		a[0]=max(a[0],b[0]);
	}
}
int main()
{
	int i,j;
	cin>>n>>k;
	for(i=1;i<=k;i++)
	{
		for(j=0;j<=n;j++)
		{
			jiafa(f[i+j],f[j]);
		}
	}
	for(i=f[n][0];i>=1;i--)
	{
		cout<<f[n][i];
	}
	return 0;
}
```
### AC在眼前，100分！！！

---

## 作者：迷残云 (赞：0)

禁言时的第一篇题解

~~再也不标题党了~~

首先，这道题是个完全背包，如果不会，请看[背包问题详解](https://www.kancloud.cn/kancloud/pack/70126)（强推）。

在这里简单介绍一下完全背包吧：

#### **完全背包问题：**
有$N$种物品和一个容量为$v$的背包，每种物品都有**无限种**可用，求解将那些物品装入背包可以使这些物品的费用总和不超过背包容量，且价值总和最大。

完全背包和01背包唯一区别的地方就在$for$的第二重循环（枚举体积），完全背包是顺序，而01背包是逆序。

那为什么是顺序呢？初学背包时相信每个同学都有这样的疑问，首先我们想一下为什么01背包中要逆序：是不是因为二维数组 $f[i][v]$是由状态$s:$ $ f[i-1][v-w[i]] $推来？？所以类似的，完全背包是无限件，在考虑当前状态时，需要一个可能已经选入第$ i $种物品的子结果$ f[i][v-w[i]] $，所以就必须用顺序循环。

但是，其实这道题的难点并不在完全背包，而是在数据的毒瘤（~~lxl~~），这道题爆了$ longlong $，所以我果断想到了[格雷码](https://www.luogu.com.cn/problem/P5657)，用了$unsigned long long$，结果跟$ long long $一样，都是70分。。。

于是我又想到了$ int 128 $，于是悲催的是$ printf $ 不支持 $  int 128  $，于是我百度搜了一下快读（~~不会~~），找到了这篇博客：[强推](https://blog.csdn.net/tianwei0822/article/details/80687466)

当然，可以使用高精度（~~但是麻烦啊~~）明明可以不用高精就最好不用，这是无数次经验告诉我们的。

好了，我们来贴代码吧：

```cpp

#include <bits/stdc++.h>
using namespace std;
__int128 f[1010];
__int128 n,m;
void scan(__int128 &x)//输入
{
    x = 0;
    int f = 1;
    char ch;
    if((ch = getchar()) == '-') f = -f;
    else x = x*10 + ch-'0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = x*10 + ch-'0';
    x *= f;
}
void _print(__int128 x)
{
    if(x > 9) _print(x/10);
    putchar(x%10 + '0');
}
void print(__int128 x)//输出
{
    if(x < 0)
    {
        x = -x;
        putchar('-');
    }
    _print(x);
}

int main()
{
    scan(m); scan(n);
    f[0]=1;
    for(int i=1;i<=n;i++)
	 for(int j=i;j<=m;j++)
	  f[j]+=f[j-i];
    print(f[m]);
    return 0;
}
```


---

## 作者：Zhou_Wingay (赞：0)

### 思路:完全背包加高精。

设$f[i]$表示花光$i$元的方案数。

每次枚举每个工具的价格$j$，则状态转移方程为：$f[i+j]+=f[i]$。

此时代码为：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,n,f[2005]={1};
int main(){
	long long i,j;
	cin>>n>>k;
	for(i=1;i<=k;i++){
		for(j=0;j<=n;j++){
			f[i+j]+=f[j];
		}
	}
	cout<<f[n];
	return 0;
}
```
但一交，70?

于是我想到了高精。

详细解释在代码中：
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,f[2005][1005]={1,1};
void jiafa(int a[],int b[]){
	int i,j;
	for(i=1;i<=max(a[0],b[0]);i++){a[i]=a[i]+b[i];}
    //逐位相加
	for(i=1;i<=max(a[0],b[0]);i++){if(a[i]>=10){a[i]-=10;a[i+1]++;}}
    //进位
	if(a[max(a[0],b[0])+1]!=0){a[0]=max(a[0],b[0])+1;}
	else{a[0]=max(a[0],b[0]);}
    //判断位数
}
int main(){
	int i,j;
	cin>>n>>k;
	for(i=1;i<=k;i++){
		for(j=0;j<=n;j++){
			jiafa(f[i+j],f[j]);
            //状态转移方程
		}
	}
	for(i=f[n][0];i>=1;i--) cout<<f[n][i];
	return 0;
}
```


---

