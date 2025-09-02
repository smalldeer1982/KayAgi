# XY Sequence

## 题目描述

You are given four integers $ n $ , $ B $ , $ x $ and $ y $ . You should build a sequence $ a_0, a_1, a_2, \dots, a_n $ where $ a_0 = 0 $ and for each $ i \ge 1 $ you can choose:

- either $ a_i = a_{i - 1} + x $
- or $ a_i = a_{i - 1} - y $ .

Your goal is to build such a sequence $ a $ that $ a_i \le B $ for all $ i $ and $ \sum\limits_{i=0}^{n}{a_i} $ is maximum possible.

## 说明/提示

In the first test case, the optimal sequence $ a $ is $ [0, 1, 2, 3, 4, 5] $ .

In the second test case, the optimal sequence $ a $ is $ [0, 10^9, 0, 10^9, 0, 10^9, 0, 10^9] $ .

In the third test case, the optimal sequence $ a $ is $ [0, -3, -6, 1, -2] $ .

## 样例 #1

### 输入

```
3
5 100 1 30
7 1000000000 1000000000 1000000000
4 1 7 3```

### 输出

```
15
4000000000
-10```

# 题解

## 作者：沉石鱼惊旋 (赞：0)

###  题目翻译

四个整数，$n,B,x,y$，每次可以选择 $a_i=a_{i-1}+x$ 或者 $a_i=a_{i-1}-y$，必须保证 $a_i\leq B$，问 $a$ 数组的元素和。

### 题目思路

这道题可以贪心。

每次尽可能加上 $x$，如果超过就减掉 $y$。

这肯定是对的贪心策略；

因为，这样肯定保证多加上少减去。

每次都是加 $x$，减 $y$，所以多加少减肯定正确。

### AC 代码

```cpp
void solve()
{
	int n,b,x,y;
	cin>>n>>b>>x>>y;
	ll ans=0,last=0;
	for(int i=1;i<=n;i++)
	{
		last=(last+x>b?last-y:last+x);
		ans+=last;
	}
	cout<<ans<<endl;
}
```



---

## 作者：CodeMao (赞：0)

主算法：**贪心**。

思路：

- 很容易想到，每次加法的贡献一定比减法多。
  
- 所以我们要尽可能多的用加法。
  
- 所以只要当 $a_{i-1}+x\le B$ 时 , $a_i=a_{i-1}+x$ ; 否则只能 $a_i=a_{i-1}-y$ 。
  

注意：记得开 `long long` 。   

上代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
int t,n,b,x,y,ans,last;
inline void in(int &a){ //快速读入
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9')   
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        a=(a<<1)+(a<<3)+(ch^48);
        ch=getchar();
    }
}
inline void op(int a){ //快速输出
    if(a<0) {a=~a+1,putchar('-');}
    if(a>9) op(a/10);
    putchar(a%10+'0');
}
signed main(){
    in(t);  
    while(t--){
        in(n),in(b),in(x),in(y);ans=last=0;
        //这里有一个内存优化：仔细想一想，这题并不需要开一个a数组，因为答案只取决于a[i-1]，所以在每次循环时开个变量记录下a[i-1]的值即可。
        for(int i=1;i<=n;++i){
            if(last+x<=b) ans+=last+=x; //日常压行好习惯
            else ans+=last-=y;
        }
        op(ans),puts("");
    }
    return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

这是一个不难的贪心。

顺序确定 $a_i$，如果 $a_{i-1}+x\le B$，则 $a_i=a_{i-1}+x$。否则 $a_i=a_{i-1}-y$。

```
#include<cstdio>
using namespace std;
#define int long long
int t;
int n,b,x,y;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld",&n,&b,&x,&y);
		int now=0,ans=0;
		for(int i=1;i<=n;i++)
		{
			if(now+x<=b)
			{
				now+=x;
			}
			else
			{
				now-=y;
			}
			ans+=now;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

贪心即可。

首先 $a[0]=0$。

然后，依次确定 $a[1]$ 到 $a[n]$。

如果 $a[i-1]+x\le B$，那么 $a[i]=a[i-1]+x$；否则 $a[i]=a[i-1]-y$。

我们可以证明此算法正确性。

如果 $a[i-1]+x\le B$ 但是 $a[i]=a[i-1]-y$，那么，找到满足 $a[j-1]+x=a[j]$ 且 $j\ge i$ 的最小的 $j$：

+ 如果不存在这个 $j$，那么让 $a[i]=a[i-1]+x$ 也能够使答案更大，并且绝对不会有问题；

+ 如果存在这个 $j$，那么让 $a[i]=a[i-1]+x$，然后对于所有的 $k(i<k<j)$ 都不改变其**操作**（注意不是具体数据）（事实上操作都是 $a[k]=a[k-1]-y$），然后让 $a[j]=a[j-1]-y$。可以证明这不会有任何问题，并且答案必定提高。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 200000
int t;
int n;
long long b,x,y;
long long a[max_n+2];
long long ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1657B_1.in","r",stdin);
	freopen("CF1657B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%lld%lld%lld",&n,&b,&x,&y);
		a[0]=0;
		ans=0;
		for(int i=1;i<=n;++i){
			if(a[i-1]+x>b)a[i]=a[i-1]-y;
			else a[i]=a[i-1]+x;
			ans+=a[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/72287786)

By **dengziyue**

---

## 作者：MeowScore (赞：0)

题意：多次询问。每次给出四个数 $n,B,x,y$。你需要构造一个数列 $a_0,a_1,a_2,...,a_n$，满足以下条件：

+ $a_0=0$

+ 对于 $\forall i \in [1,n]$，你可以将 $a_i$ 的值赋为 $a_{i-1}+x$ 或者 $a_{i-1}-y$。

+ 对于 $\forall i \in [1,n]$，$a_i \le B$。

+ 最大化 $\sum_{i=0}^n a_i$。

输出 $\sum_{i=0}^n a_i$。

贪心即可，对每个位置都优先使用加法。对于 $i$ 位置，若 $a_{i-1}+x>B$，则令 $a_i=a_{i-1}-y$，否则令 $a_i=a_{i-1}+x$。

求和输出即可。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200010];
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,x,y;
		cin>>n>>m>>x>>y;
		a[0]=0;
		for(int i=1;i<=n;i++){
			if(a[i-1]+x>m)
				a[i]=a[i-1]-y;
			else
				a[i]=a[i-1]+x;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			ans+=a[i];
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：ajhuhe (赞：0)

# 题目简述

给定 $T$ 组测试数据，每组 $4$ 个整数，$n$，$B$，$x$，$y$，以及 $n+1$ 个数，规定他们集合于 $a$，有 $a_0=0$，现在可以将 $a_i = a_{i-1}+x$ 或 $a_i = a_{i-1}-y$ 。无论选择怎样的操作，必须保证 $\max a_i ≤ B$，最后输出 $\sum\limits_{i=0}\limits^n \max a_i$ 。

# 题目分析

由于 $a_0 = 0$，最后只需输出 $\sum\limits_{i=1}\limits^n \max a_i$ 即可，那么此题解法为：

- 从 $1$ 至 $n$ 遍历 $a$ 数组。
- 如果 $a_{i-1}+x ≤ B$，$a_i = a_{i-1}+x$，否则 $a_i = a_{i-1}-y$。
- 输出 $\sum\limits_{i=1}\limits^n a_i$ 即可。

## 简单证明

当 $a_{i-1}+x ≤ B$ 时，若使 $a_i = a_{i-1}+x$。那么 $a_i+x > B$(如果 $a_i+x ≤ B$ 与前面情况相同，没有讨论的必要)，此时 $a_{i+1} = a_i-y = a_{i-1}+x-y$。若使 $a_i = a_{i-1}-y$，那么 $a_i+x ≤ B$，此时 $a_{i+1} = a_i+x = a_{i-1}-y+x$。结果并没有变化。但是前者的 $a_{i+1}$ 更小，所以 $a_{i+2}$ 相应更大，这说明当 $a_{i-1}+x ≤ B$，应立即使 $a_i = a_{i-1}+x$。否则，使 $a_i = a_{i-1}-y$。

## 优化
- 用 $last$ 记录 $a_{i-1}$，从而取代 $a$ 数组，新增变量 $sum$，记录 $\sum\limits_{i=1}\limits^n a_i$。
- 如果 $a_{i-1}+x ≤ B$，$a_i = a_{i-1}+x$，否则 $a_i = a_{i-1}-y$。
- 输出 $sum$ 即可。

## 温馨提示
记得开 long long。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,b,x,y,last,sum; //long long 很重要
int main()
{
	cin>>t;
	while(t--)
	{
		sum=last=0;
		cin>>n>>b>>x>>y;
		for(int i=1;i<=n;i++)//遍历 1~n
		{
			if(last+x<=b)//判断
			{
				sum+=last+x;
				last+=x;//更新last
			}
			else
			{
				sum+=last-y;
				last-=y;
			}
		}
		cout<<sum<<endl;//输出
	}	
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1657B)

题意：输入 $n,B,x,y$，令 $a_0=0$，之后 $a_{i+1}$ 可以取 $a_i+x$ 或 $a_i-y$，且 $\forall1\le i\le n,a_i\le B$。要求$\max \sum\limits_{i=1}^{n} a_i$。

这道题只要贪心就可以了。如果 $a_i+x\le B$，则令 $a_{i+1}=a_i+x$，否则$a_{i+1}=a_i-y$。

简单的证明一下：

如果令 $a_{i+1}=a_i+x$（如果可以），即使只能 $a_{i+2}=a_{i+1}-y$，则 $a_{i+2}=a_i+x-y$。

但如果令 $a_{i+1}=a_i-y$，即使可以 $a_{i+2}=a_{i+1}+x$，$a_{i+2}$ 还是为 $a_i+x-y$。

也就是说，这样不影响 $a_{i+2}$ 的值，但是前者的 $a_{i+1}$ 比后者的大 $(x+y)$，所以前者一定优于后者。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,B,n;
ll x,y,ans,t;
int main()
{
	cin>>T;
	while(T--)
	{
		scanf("%d%d%lld%lld",&n,&B,&x,&y);
		ans=t=0;
		for(int i=1;i<=n;i++)
		{
			if(t+x<=B)t+=x;
			else t-=y;
			ans+=t;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：hereiszd (赞：0)

## 题意分析
给定一个数列 $a$，和常数 $z,n,x,y$，其中 $a_0=0$，构造这个数列，使得 $S_n$ 最大化。

构造方法：
1. 对于任意 $i \in N,i\le n$，都有 $a_i \le z$ 。
2. $a_i$ 可以等于 $a_{n-1}+x$，也可以等于 $a_{n-1}-y$。

## 题目解决

考虑贪心：

显然，加法一定比减法贡献更大。

如果当前元素可以加，那么一定加，如果不能加，那就减去。

若当前元素可以加却没有加的时候，构造出的数列总和一定会更小。

考虑证明：

假设序列的最后一个可以加，却用了减法，显然会更劣。

那么所有可以加却没有加的方案一定会比能加的都加的优。

所以贪心成立。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200001
int a[N],T,b,x,y,n;
int main(){
    cin>>T;
    while(T--){
        long long sum=0;
        memset(a,0,sizeof(a));//多测不清空，亲人两行泪(虽然这里可以不清空)
        cin>>n>>b>>x>>y;
        a[0]=0;
        for(int i=1;i<=n;i++){
            if(a[i-1]+x>b){
                a[i]=a[i-1]-y;
            }
            else{
                a[i]=a[i-1]+x;
            }
            sum+=a[i];
        }
        cout<<sum<<endl;
    }
    return 0;
}
```





---

## 作者：win10 (赞：0)

 ### 解析

可以发现，对于当前的数 $a_i$ ，在满足条件的情况下，令 $a_{i+1} = a_i+x$ ,一定要比令 $a_{i+1}=a_i-y$ 要优，因为每次 $a_{i+1}$ 对答案的贡献会多 $x + y$ 。
 
所以当 $a_i + x \le B$ 时，我们令 $a_{i+1} = a_i+x$ ；

当 $a_i + x > B$ 时，我们只可以令 $a_{i+1}=a_i-y$ 。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long //注意数据范围，本题需要开long long

inline int read() {
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int T,n,b,x,y,ans,a;

signed main() {
	T = read();
	while(T--) {
		n = read(); b = read();
		x = read(); y = read();
		a = ans = 0; //注意多测的初始化
		for(int i = 1;i <= n;i++) {
			if(a + x <= b) {
				a += x;
				ans += a;
			}
			else {
				a -= y;
				ans += a;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

