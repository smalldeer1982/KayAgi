# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
13
```

# 题解

## 作者：chlchl (赞：1)

## 题意简化
翻译已经很简洁了，给定 $n$、$p$、$a_1\sim a_n$，将 $a$ 分成两段非空区间（设分界点为 $k$），使得 $\sum_{i=1}^{k}a_i\ \bmod p+\sum_{i=k+1}^{n}a_i\ \bmod p$ 最大。

## 做法
本题难度预估 ``普及-``（~~其实入门也不过分，只不过有前缀和罢了~~）。

暴力枚举求和明显是 $O(n^2)$ 的，所以考虑使用前缀和维护区间，每次枚举分割点时可以 $O(1)$ 求和，时间复杂度 $O(n)$，可以通过本题。

- 不要以为取模有分配率！
- 分割点不能是 $n$，这样一个区间是 $\lbrack 1,n\rbrack$，另一个就是空区间了，不符合条件。

## 代码
珍爱生命，远离抄袭。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10;
int n;
ll p, ans, s[N];

int main(){
	scanf("%d%lld", &n, &p);
	for(int i=1;i<=n;i++)	scanf("%lld", &s[i]), s[i] += s[i - 1];
	for(int i=1;i<n;i++){//不能到 n，如果到 n 则后面为空区间
		ans = max(ans, s[i] % p + (s[n] - s[i]) % p);//第二段是 [i+1,n]，减去 s[i]而不是 s[i-1]
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：CrazyWisdom (赞：0)

### 前言

题目传送门：[Encryption (easy)](https://www.luogu.com.cn/problem/CF958C1)

### 思路

题目要求把数组分为两个非空段，求取模最大值。显然利用前缀和可以在 $O(n)$ 的复杂度解决问题。

写一个前缀和数组，那么数组的第 $N$ 个元素就代表着长度为 $N$ 的前缀之元素和，也就是第一个非空段之元素和；数列总和与前缀和之差就是当前前缀后面的所有元素组成的后缀之元素和，也就是第二个非空段之元素和；分别取模，加起来得到当前的价值。重复这种操作跑循环找最大价值即可。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 100005
int N, s[MAXN], mod, Sum=0, Maxn=-1;
signed main () {
	cin>>N>>mod;
	int num;
	s[0]=0;
	for(int i=1;i<=N;i++) {
		cin>>num;
		Sum+=num;
		s[i]=s[i-1]+num;//预处理前缀和
	}
	for(int i=1;i<=N;i++) {
		Maxn=max(Maxn,(Sum-s[i])%mod+s[i]%mod);//比较已经算出的最大价值和当前两个非空段的价值和的大小
	}
	cout<<Maxn;
	return 0;
}
```

### 后记

是个前缀和板子。

如有问题欢迎指出。

---

## 作者：Milthm (赞：0)

## CF958C1 题解

### 题目大意
 
有一个包含 $n$ 个正整数的数列，将这个数列分成 $2$ 个非空段，每段的价值为这段的所有数总和 $\bmod$ $p$，你需要使 $2$ 段价值总和最大，请求出这个最大值。

### 需要算法（本题解）：

- 前缀和

### 题目思路

拿到这道题，看到“总和“两个字，我这个蒟蒻一下子就想到了大名鼎鼎的前缀和。那么就简单了，首先是一个简单的前缀和：

```cpp
for(int i=1;i<=n;++i){
    cin>>a[i];
    f[i]=f[i-1]+a[i];//累加前缀和
}
```
然后就是计算最大的总和了，容易发现，在选定第一个段的情况下，剩下一个段一定是唯一的，而选定第一个段的方法一共有 $n$ 种，所以我们可以枚举第一段的最后一个元素，那么这种情况下，第一段的和就是 `f[i]`，而第二段的和就是序列总和减去第一段的和，即为 `f[n]-f[i]`。定义一个变量，取最大值即可。

### AC代码

```cpp
#include<iostream>
#define int long long//一定要开long long啊！
using namespace std;
int n,p,a[100005],f[100005],ans;
signed main(){
	cin>>n>>p;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		f[i]=f[i-1]+a[i];//累加前缀和
	}
	for(int i=1;i<=n;++i){
		ans=max(ans,f[i]%p+(f[n]-f[i])%p);//计算最大值（上面有具体讲解）
	}
	cout<<ans<<endl;//输出
	return 0;
} 
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

给定 $n,p$ 和序列 $a$，求 $\max\{(\sum\limits_{j=1}^ia_j)\bmod p+(\sum\limits_{j=i+1}^na_j)\bmod p\}$。

# 题目分析

显然有线段树做法，不过杀鸡焉用牛刀。。。时间复杂度还是 $\mathcal{O(n\log n)}$ 的。

众所周知模运算满足 $(a+b)\bmod p=a\bmod p+b\bmod p$，所以可以差分成前缀和和后缀和。遍历求最大即可。

时间复杂度 $\mathcal{O(n)}$。

# 代码

```cpp
// Problem: CF958C1 Encryption (easy)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF958C1
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Date:2022-05-21 15:22
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 1e5 + 5;
int a[N],sum[N],suc[N];
int n,m;
int main(void) {
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) {
		a[i] = read();
		sum[i] = (sum[i - 1] + a[i]) % m;
	}
	for (register int i = n;i >= 1; -- i) {
		suc[i] = (suc[i + 1] + a[i]) % m;
	}
	int ans = 0;
	for (register int i = 1;i <= n; ++ i) {
		ans = std::max(ans,sum[i] + suc[i + 1]);
	}
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：Noby_Glds (赞：0)

~~话说这么简单的题为什么没人写题解啊~~

### 思路：
很简单，输入时处理一下前缀和。

接着再枚举从哪个地方断开就行了。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,ans,a[100010],s[100010];
int main(){
	cin>>n>>p;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]%=p,s[i]=s[i-1]+a[i];
	for(int i=1;i<n;i++) ans=max(ans,s[i]%p+(s[n]-s[i])%p);
	cout<<ans;
	return 0;
}
```


---

## 作者：智子 (赞：0)

## 题意

输入 $n$ 个数和一个数 $p$，将这 $n$ 个数分为前后两段，每段的价值为这段数的总和模 $p$，使两段总和最大。输出最大总和。

## 思路

在学校模拟赛中遇到了这道题，当时看错题面导致想了 10 分钟。（逃

因为是分为前后两段，所以直接预处理出前缀和和后缀和，再枚举断开的位置 $i$ 计算价值和，取最大值即可，时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int a[MAXN], pre[MAXN], suf[MAXN];
int n, p;

int main() {
    scanf("%d%d", &n, &p);
    for(int i = 1; i <= n; i++) {
    	scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++) {
        pre[i] = (pre[i - 1] + a[i]) % p;
    }
    for(int i = n; i; i--) {
        suf[i] = (suf[i + 1] + a[i]) % p;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, pre[i] + suf[i + 1]);
    }
    printf("%d", ans);
    
    return 0;
}
```

---

