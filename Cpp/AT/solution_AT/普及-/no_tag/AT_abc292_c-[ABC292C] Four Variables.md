# [ABC292C] Four Variables

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc292/tasks/abc292_c

正整数 $ N $ が与えられます。  
 正整数の組 $ (A,B,C,D) $ であって、$ AB\ +\ CD\ =\ N $ を満たすものの個数を求めてください。

なお、本問の制約の下、答えが $ 9\ \times\ 10^{18} $ 以下であることが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N $ は整数
 
### Sample Explanation 1

$ (A,B,C,D) $ として以下の $ 8 $ 個が考えられます。 - $ (A,B,C,D)=(1,1,1,3) $ - $ (A,B,C,D)=(1,1,3,1) $ - $ (A,B,C,D)=(1,2,1,2) $ - $ (A,B,C,D)=(1,2,2,1) $ - $ (A,B,C,D)=(1,3,1,1) $ - $ (A,B,C,D)=(2,1,1,2) $ - $ (A,B,C,D)=(2,1,2,1) $ - $ (A,B,C,D)=(3,1,1,1) $

## 样例 #1

### 输入

```
4```

### 输出

```
8```

## 样例 #2

### 输入

```
292```

### 输出

```
10886```

## 样例 #3

### 输入

```
19876```

### 输出

```
2219958```

# 题解

## 作者：lsz_ (赞：8)

### 题目大意

给定一个整数 $N$，求出满足 $AB+CD=N$ 的整数数对 $(A,B,C,D)$ 的个数。$(1\leq A,B,C,D\leq N)$。

注意，$(1,1,2,1)$ 和 $(1,1,1,2)$ 算两组数对。

### 思路

对于每一个 $N$，可将它拆分成 $t$ 和 $N-t$ 两个整数 $(1\leq t<N)$ 并且找到 $AB=t,CD=N-t$ 的方案数，所有的拆分方案的结果和即等于答案。

所以答案为 $\sum\limits_{i=1}^{N-1}count(i)count(N-i)$。

其中 $count(x)$ 为拆分 $x$ 的方案个数。

不难发现，$count(x)$ 就是 $x$ 的因数个数，证明附后面。

所以只需预处理出 $count(x)$ 即可，复杂度为 $O(N\sqrt{N})$。

### 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,i;
int yin[229028]={0,1};
LL ans;
void zhiyin(int x)
{
	int ans=1,x1=x;
	for(int i=2;i<=sqrt(x);i++)
	{
		int temp=0;
		while(x1%i==0)
		{
			x1/=i;
			temp++;
		}
		ans=ans*(temp+1);
	}
	if(x1==x)	yin[x]=min(2,x);
	else if(x1>1)	yin[i]=ans*2;
	else	yin[x]=ans;
	return ;
}
int main()
{
	cin>>n;
	for(i=2;i<n;i++)	zhiyin(i);
	for(i=1;i<n;i++)	ans+=yin[i]*yin[n-i];
	cout<<ans;
	return 0;
}
```

### 证明

设 $X$ 的所有因数为 $x_1,x_2,x_3...x_{x\_yin}$。

其中 $x\_yin$ 为 $X$ 的因数个数。

那么，所有的拆分方案为 $(x_1,X/x_1)~(x_2,X/x_2)...(x_{x\_yin},X/x_{x\_yin})$。

易得个数为 $x\_yin$，也与 $count(X)$ 的定义方法一致。

证毕。

---

## 作者：NightStriker (赞：3)

题意：

> 给定一个整数 $n$（$2\le n\le 10^5$），找出四元组 $(A,B,C,D)$ 使得 $AB+CD=n$ 的个数。
>
> 可以证明答案最多是 $9\times 10^{18}$。

直接枚举 $(A,B,C,D)$ 的复杂度是 $\mathcal{O}(n^4)$，通过 $(A,B,C)$ 的值来算出 $D$ 是 $\mathcal{O}(n^3)$，都不足以通过本题。

我们将 $AB$ 设为 $x$，$CD$ 设为 $y$，我们可以枚举 $x$，通过 $n-x$ 算出 $y$。

现在如果想知道 $AB$ 和 $CD$ 的值就需要把 $x$ 和 $y$ 的因数个数算出来，直接累加起来就好。

分解因数的时候要注意不能把平方数重复算，算一次就好。

分解因数的时间复杂度是 $\mathcal{O}(\sqrt n)$，枚举 $x$ 时间复杂度为 $\mathcal{O}(n)$，总共的时间复杂度就是 $\mathcal{O}(n\sqrt n)$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long//
using namespace std;
int n,ans;
int d(int x){//分解因数
    int ans = 0;
    for(int i = 1;i*i<=x;i++){
        if(x%i==0){
        	ans++;
            if(i*i!=x) ans++;//p,q可能交换赋值A,B
        }
    }
    return ans;
}
signed main(){
    cin>>n; 
    for(int i = 1;i<=n;i++){
        ans+=d(i)*d(n-i);
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：incra (赞：2)

## 题意
给定一个数 $n$，求有多少组 $(A,B,C,D)$ 满足 $AB+CD=n$。

**注意** $(1,1,1,3)\neq (1,1,3,1)$。
## 题解
把 $n$ 拆成两个数后把两个数的因数个数相乘即可。

举个例子，假设把 $n$ 拆成 $a +b$。那么把 $a$  拆成 $XY$ 的形式，一共有 $count(a)$ 种，其中 $count(x)$ 表示 $x$ 的因子个数。$b$ 同理有 $count(b)$ 种拆法，所以把 $n$ 拆成 $a+b$ 时有 $count(a)\times count(b)$ 种。

**注意**，把 $n$ 拆成 $(n-1)+1$ 和 $1+(n-1)$ 并不是同一种拆法。
## 代码
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
LL n;
LL count (LL x) {
	LL cnt = 0;
	for (int i = 1;i <= x / i;i++) {
		if (x % i == 0) {
			cnt++;
			if (x / i != i) cnt++;
		}
	}
	return cnt;
}
int main () {
	cin >> n;
	LL ans = 0;
	for (int i = 1;i <= n - 1;i++) ans += count (i) * count (n - i);
	cout << ans << endl;
    return 0;
}
```

---

## 作者：zzx0102 (赞：1)

给定 $1$ 个整数 $n$，求所有满足方案的正整数 $a,b,c,d$，满足 $ab+cd=n$。

$1\leq n\leq 2\times10^5$

暴力做法 $1$：

枚举 $a,b,c,d$，暴力求总方案数。

复杂度 $O(n^2 \log^2 n)$。

```cpp
for(int a = 1; a <= n; a++) {
	for(int b = 1; a * b <= n; b++) {
		for(int c = 1; c <= n; c++) {
			for(int d = 1; c * d <= n; d++) {
				if(a * b + c * d == n) ans++;
			}
		}
	}
}
cout << ans;
```

暴力做法 $2$：

枚举 $a,b,c$，可得 $d=(n-ab)\div c$。

复杂度 $O(n^2 \log n)$。

```cpp
for(int a = 1; a <= n; a++) {
	for(int b = 1; a * b <= n; b++) {
		for(int c = 1; c <= n; c++) {
			if((n - a * b) % c == 0) ans++;
		}
	}
}
cout << ans;
```


暴力做法 $3$：

枚举 $a,b$，令 $x=n-ab$。

那么答案就要加 $x$ 的约数个数。

约数个数需要预处理，可以做到 $O(n\log n)$ 。

看起来复杂度 $O(n^2)$，好像不满，但仔细分析一下，其实是 $O(n\log n)$ 的，和最暴力的素数筛的复杂度其实是一样的，所以 AC 了。


预处理：
```cpp
for(int i = 1; i <= n; i++) {
	for(int j = i; j <= n; j += i) cnt[j]++;
}
```

实现：

```cpp
for(int a = 1; a <= n; a++) {
	for(int b = 1; a * b <= n; b++) {
		int x = n - a * b;
		ans += cnt[x];
	}
}
cout << ans;
```

当然，你可以枚举 $ab$，那么 $cd=n-ab$，所以这组答案就是 $cnt_{ab}\times cnt_{cd}$。求和即可，复杂度同样是 $O(n\log n)$。

你还可以 $O(n)$ 的线性筛求素数个数，然后 $O(n)$ 地求 $cnt_{ab}\times cnt_{cd}$，复杂度 $O(n)$，但是没有必要。

---

## 作者：liangbob (赞：1)

### AT_abc292_c 题解

#### 思路分析

一道挺不错的思维题。

首先，题目要求求出满足 $A \times B+ C \times D = N$ 的四元组 $(A,B,C,D)$，且顺序不同，数相同的不算同一种。于是，我们可以先枚举 $A \times B$ 与 $C \times D$ 的值，随后我们就可以通过分解因数对的方式枚举出 $(A,B)$ 与 $(C,D)$ 各有多少组（计顺序）。最后根据乘法原理，将两者统计出来的结果相乘即可。

那么其次，如何通过分解因数对的方式枚举出 $(A,B)$ 与 $(C,D)$ 各有多少组（计顺序）呢？我们以 $(A,B)$ 为例。可以发现，由于两者乘积固定且已知，如果设其为 $k$。则 $(A,B)$ 可以表示为 $(A,\dfrac{k}{A})$，也就是确定了 $A$ 就确定了整个组 $(A,B)$ 。由于又有 $A \mid k$，即 $A$ 为 $k$ 的因数，因数与整个组 $(A,B)$ 一一对应。也就是说，乘积有多少个因数个数，就有有多少组（计顺序）。

然后就是实现了。题解区中的大佬们都是用 $O(N \sqrt{N})$ 的算法直接在程序中来预处理因数个数的。事实上，这样子并不稳健，因为如果不加任何优化的话，$2 \times 10^5$ 的范围中很可能会被卡常。所以我认为最好直接打表处理出来范围中所有数的因数个数，这样子就可以实现在 $O(N)$ 的复杂度内计算出正确结果。

#### 代码

打表代码：

```cpp
for(int i = 1;i <= 200000;i++) //遍历每个数
{
	int cnt = 0; //因数个数计数器
	for(int j = 1;j * j <= i;j++) //遍历每个因数
	{
		if(i % j == 0) //如果能被整除
		{
			cnt += 2; //加入两个因数
		}
		if(j * j == i) //如果是平方数
		{
			cnt--; //要进行去重
		}
	}
	cout << cnt << ",";
}
```

计算结果部分关键代码：

```cpp
long long kkk = 0; //总结果计数器
for(int i = 1;i <= n;i++) //枚举AB乘积
{
	int j = n - i; //由 AB+CD=N，CD=N-AB 得来。
	kkk += (ys[i] * ys[j]); //根据乘法原理计算结果
}
cout << kkk << endl;
```



---

## 作者：Unnamed114514 (赞：0)

先枚举 $AB$，那么我们可以求出 $CD=N-AB$，然后对于一个数 $k$ 我们可以 $O(\sqrt{k})$ 地求出 $k$ 的因子数。

那么我们可以得到 $m=AB,n=CD$ 分别的因子数，此处记作 $a,b$，因为对于 $m$ 的每一个因子 $A=w$，都可以取对应的 $B=\dfrac{m}{w}$，那么 $m$ 就一共有 $a$ 种分解方式。同理，$n$ 有 $b$ 种分解方式。

乘法原理：对于一个 $(m,n)$ 答案就是 $ab$，时间复杂度 $O(n\sqrt{n})$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
inline int f(int x){
	int tot=0;
	for(int i=1;i<=sqrt(x);++i){
		if(x%i==0){
			++tot;
			if(x/i!=i)
				++tot;
		}
	}
	return tot;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;++i)
		ans+=f(i)*f(n-i);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Escapism (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc292_c)

# 题意

对于一个 $4$ 个数的序列 $(A,B,C,D)$，问存在多少个 $A\times B+C\times D=N$。

# 思路

**$O(N^4)$ 算法** 

暴力枚举所有的 $A,B,C,D$，显然太慢了。

**$O(N^3)$ 算法**

由于已知 $CD=N-AB$，因而只需要枚举 $A,B,C$。仍然很慢。

**$O(N\sqrt N)$ 算法**

设 $X=AB,Y=N-X=CD$，显然有 $X+Y=N$。通过使用 $O(\sqrt N)$ 的算法枚举 $X$ 和 $Y$ 的因子可以使整体复杂度达到 $O(N\sqrt N)$。可以通过。

# 代码

这里的代码放的是 $O(N\sqrt N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int main() {
	long long N,ans = 0;
	cin>>N;
	for(int i = 1;i < N;i++){
		long long X = i,Y = N - i,x = 0,y = 0 ;
		for(int j = 1;j * j <= X;j++){ //枚举 X 的因子
			if(X % j == 0){
				x++;
				if(X != j * j)x++;
			}
		}
		for(int j = 1;j * j <= Y;j++){ //枚举 Y 的因子
			if(Y % j == 0){
				y++;
				if(Y != j * j)y++;
			}
		}
		ans += x * y; //注意由于 X 和 Y 都可以选择因子，所以要加 X * Y
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Enoch006 (赞：0)

### 题目描述：
此题的题目描述大概是：给定一个正整数 $N$，一个正整数四元组 $(A,B,C,D)$ 满足 $N=AB+CD$。求正整数四元组的个数。

### 题目分析：
我们发现 $AB,CD$ 一定是正整数，所以 $AB$ 可以在 $1$ 至 $N-1$ 中任意取值。$CD$ 则为对应的 $N-AB$。根据乘法原理，$(A,B,C,D)$ 四元组的数量即为 $(A,B)$ 的数量乘对应的 $(C,D)$ 的数量，再将所有的乘出来的值相加即为答案。

问题转变为找到 $(A,B)$ 与 $(C,D)$ 的数量，因为他们都是正整数，并且乘起来的值一定，所以易得这个双元组的数量为他们乘起来的定值的因数。

### 题目代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000000],sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			a[j]++;//预处理每个数的因数。
		}
	}
	for(int i=1;i<=n-1;i++){//循环遍历AB的值。
		sum+=a[i]*a[n-i];//将(A,B)双元组的数量与(C,D)双元组的数量相乘。
	}
	cout<<sum;
	return 0;
} 
```
[AC 记录](https://www.luogu.com.cn/record/103787286)

---

## 作者：Mabangjie6789 (赞：0)

## 题意简述

给你一个数 $N$ ，求有多少个四元组 $(A, B, C, D)$ 满足 $AB + CD = N$。

答案在 $9 \times 10^{18}$ 以内。

## 题目思路

直接**暴力枚举**即可。

- 枚举 $AB$ 的值（即 $1$ 至 $N - 1$）。
- 对于每一个 $AB$ 的值 $i$：
	1. 算出 $CD$ 的值 $j$；
   1. 枚举 $i$ 的因数，作为 $A$ 的值，$B$ 的值就是 $i / A$;
   1. 同理，枚举 $j$ 的因数，作为 $C$ 的值，$D$ 的值就是 $j / C$;
   1. 把 $A$ 的方法数和 $C$ 的方法数乘起来，累加到 `cnt` 中。
- 注意：因为答案在 $9 \times 10^{18}$ 以内，所以需要开 `long long`。

## 代码

```cpp
#include <iostream>
using namespace std;

int main(){
    long long n, cnt = 0;//统计和
    cin >> n;
    for (int i = 1; i < n; i++){
        long long j = n - i, x = 0, y = 0;//x，y分别代表i, j的因数
        for (int k = 1; k * k <= i; k++)
            if (i % k == 0){
                x += 2;
                if (k * k == i)
                    x--;//特判：如果是平方数，因数个数-1
            }
        for (int k = 1; k * k <= j; k++)
            if (j % k == 0){
                y += 2;
                if (k * k == j)
                    y--;//同上
            }
        cnt += x * y;//累加
    }
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：aCssen (赞：0)

### Solution
如果 $AB$ 的值确定了，则因为 $AB+CD=n$，所以 $CD$ 的值也就被确定为 $n-AB$，因为两部分之间没有影响，所以两部分的答案应用乘法原理组合在一起。我们枚举 $AB$ 的值，将每部分的答案加到一起即可。

设 $f_k$ 表示满足 $AB=k$ 且 $A,B\ge1$ 的数对 $(A,B)$ 的数量，则本题的答案就是 $\sum_{i=1}^n f_i \times f_{n-i}$，本式的推导已在上文提出。

讨论 $f$ 数组的求法。对于每个数 $k$，将其分解因数，每得到一个不超过 $\lfloor\sqrt n\rfloor$ 的因数 $i$，就得到了两个数对 $(i,\frac{n}{i})$ 和 $(\frac{n}{i},i)$。但当 $\frac{n}{i}=i$ 时，两个数对相同，所以答案只会加 $1$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
long long f[maxn],ans;
int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	scanf("%d",&n);
 	for(int i=1;i<=n;i++){
 		for(int j=1;j*j<=i;j++){
			if(i%j==0){
				f[i]++;
				if(i/j!=j) f[i]++;
			}
		}
	}
	for(int i=1;i<=n;i++)
		ans+=(f[i]*f[n-i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc292_c)

## 题意
- 现在有一个正整数 $N$。
- 现在有一个正整数组 $(A,B,C,D)$，问有多少种取值能让 $AB+CD=N$

## 思路

- 通过题目所问的问题，不难想出这题是一道枚举题。
- 如果我们采用四层循环的方式来解决这道题，时间复杂度为 $O(N^4)$，这显然会超时。这时我们可以减少最后一层循环，时间复杂度为 $O(N^3)$，但是还是会超时。
- 但是，如果我们考虑**通过枚举 $AB$ 和 $CD$ 这两个积的所有可能来算出种数**，时间复杂度就会大大降低，变成 $O(N^2)$。在这基础上，我们还可以将时间复杂度将为 $O(N\sqrt{N})$，即将**内部的 $N$ 次循环降到 $\sqrt{N}$ 次循环**。

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int n;
	long long ans = 0;//存储答案;
	cin >> n;
	int l = 1, r = n - 1;
	while(l != n){
		int ans1 = 0, ans2 = 0;
		for(int a = 1; a * a <= l; a++){//枚举当AB为l时的方案数
			if(l % a == 0){
				ans1++;
				if(l != a * a)ans1++;
			}
		}
		for(int c = 1; c * c <= r; c++){//枚举当CD为r时的方案数
			if(r % c == 0){
				ans2++;
				if(r != c * c)ans2++;
			}
		}
		ans += ans1 * ans2;//方案数相乘
		l++;r--;//下一种可能
	}
	cout << ans << endl;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/103722556)

---

## 作者：zajasi (赞：0)

## 题意
给你一个整数 $n$，问能找到多少个四元组 $a,b,c,d$，满足 $a \times b + c \times d = n$。
## 解题思路 
利用求解约数和的方法。首先枚举 $a\times b$，$c\times d$ 也就是用 $n$ 去减前者。然后就是枚举两个的约数后乘积加到答案里去。
## AC 代码 1
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int __int128 
inline __int128 read()
{
    __int128 x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(__int128 x)
{
    if (x<0)
    {
        putchar('-');
        x=-x;
    }   
    if (x>9) write(x/10);
    putchar(x%10+'0');
}
int n,z;
int gao(int x){
    int z=0;
    for(int i=1;i*i<=x;i++){
        if(x%i==0){
            if(i*i==x)z++;
            else z+=2;
        }
    }return z;
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    n=read();
    for(int i=0;i<=n;i++){
        int x=i,y=n-i;
        z+=gao(x)*gao(y);
    }
    write(z);
    return 0;
}
```
## 解题思路 2 
分解质因数，用因数个数定理求解，和上方法很相似，就不过多赘述了。
## AC 代码 2
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,z;
int gao(int x){
    int y=2;
    int l=x,c=0;
    int z=1;
    while(y<=sqrt(l)+1){
        c=0;
        while(x%y==0){
            c++;
            x/=y;
        }
        z*=(c+1);
        y++;
    }
    if(x!=1)z*=2;
    return z;
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int x=i,y=n-i;
        z+=gao(x)*gao(y);
    }
    cout<<z;
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

### 题意

给你一个数 $n$，求方程 $ab+cd=n$ 有多少组正整数解。

### 解法

暴力枚举 $a,b,c,d$ 复杂度太大，我们可以考虑先枚举 $a,b$ 再枚举 $c,d$。

因为要求 $a,b,c,d$ 都是正整数，所以肯定有 $a,ab,b,c,cd,d < n$。

所以我们可以先把符合要求的 $ab$ 存到桶里，然后枚举 $cd$，看看 $n-cd$ 中是否有符合要求的 $ab$，统计答案即可。

时间复杂度？我不知道，但经测试在 $6\times 10^6$ 范围内，[跑的挺快](https://atcoder.jp/contests/abc292/submissions/39422912)。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll n,q,buc[maxn];
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n;
    ll a,b,c,d,ans=0;
    for(a=1;a<n;a++){
    	for(b=1;a*b<n;b++) buc[a*b]++;
	}
	for(c=1;c<n;c++){
		for(d=1;c*d<n;d++) ans+=buc[n-c*d];
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：ダ月 (赞：0)

### 题意概要：

给定一个 $n$，求所有满足以下性质的正整数四元组 $(A,B,C,D)$,满足 $AB+CD=n$。问有多少不同的该四元组。

### 题目分析：

$AB,CD$ 位置等价。所以我们从 $AB$ 入手。

首先 $n$ 可以拆成 $(n-1,1),(n-2,2),(n-3,3),\dots(x,n-x)\dots,(1,n-1)$。

我们研究 $x$，对于所有满足 $AB=x$ 的组数，我们只需要统计 $x$ 的因数个数。

根据乘法原理，对于 $(x,n-x)$ 的拆分，只需要让 $AB=x$ 的解的组数乘上 $CD=n-x$ 解的组数。最后所有拆分求和就行。

我们先预处理出所有数的因数个数，最后统计就行。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans=0;
const int N=2e5+10;
ll f[N]; 
int n;
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		for(int j=1;j*j<=i;j++)
			if(i%j==0){
				if(i!=j*j)
					f[i]+=2;
				else f[i]++;
			}
	}
	for(int i=1;i<n;i++)
		ans+=f[i]*f[n-i];
	cout<<ans;
	return 0;
}
```
时间复杂度：$O(n\sqrt n)$。

---

