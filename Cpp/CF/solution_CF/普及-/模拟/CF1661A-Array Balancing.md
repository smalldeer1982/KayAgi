# Array Balancing

## 题目描述

You are given two arrays of length $ n $ : $ a_1, a_2, \dots, a_n $ and $ b_1, b_2, \dots, b_n $ .

You can perform the following operation any number of times:

1. Choose integer index $ i $ ( $ 1 \le i \le n $ );
2. Swap $ a_i $ and $ b_i $ .

What is the minimum possible sum $ |a_1 - a_2| + |a_2 - a_3| + \dots + |a_{n-1} - a_n| $ $ + $ $ |b_1 - b_2| + |b_2 - b_3| + \dots + |b_{n-1} - b_n| $ (in other words, $ \sum\limits_{i=1}^{n - 1}{\left(|a_i - a_{i+1}| + |b_i - b_{i+1}|\right)} $ ) you can achieve after performing several (possibly, zero) operations?

## 说明/提示

In the first test case, we can, for example, swap $ a_3 $ with $ b_3 $ and $ a_4 $ with $ b_4 $ . We'll get arrays $ a = [3, 3, 3, 3] $ and $ b = [10, 10, 10, 10] $ with sum $ 3 \cdot |3 - 3| + 3 \cdot |10 - 10| = 0 $ .

In the second test case, arrays already have minimum sum (described above) equal to $ |1 - 2| + \dots + |4 - 5| + |6 - 7| + \dots + |9 - 10| $ $ = 4 + 4 = 8 $ .

In the third test case, we can, for example, swap $ a_5 $ and $ b_5 $ .

## 样例 #1

### 输入

```
3
4
3 3 10 10
10 10 3 3
5
1 2 3 4 5
6 7 8 9 10
6
72 101 108 108 111 44
10 87 111 114 108 100```

### 输出

```
0
8
218```

# 题解

## 作者：_Kouki_ (赞：1)

### 题目思路：
我们可以发现交换，只会交换**同位置**的两个值。 

也就是说产生了两种情况。  
1. $ | a_i - a_{ i + 1 } | + | b_i - b_{ i + 1 } | $
1. $ | a_i - b_{ i + 1 } | + | b_i - a_{ i + 1 } | $

对两种情况**取最小**即可！     


### 题目代码：
**有注释。**   
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//定义！
int t,n,a[30],b[30];
ll ans;
int main()
{
    scanf("%d",&t);//输入 组数
    while(t--){
        scanf("%d",&n);//输入 n 
        for(int i=1;i<=n;++i) scanf("%d",&a[i]);//输入 a[i];
        for(int i=1;i<=n;++i) scanf("%d",&b[i]);//输入 b[i];
        ans=0;//初始化
        /*
        * 弱弱的吐槽一句
        * CodeForest的评测机
        * 基本爬不回来
        */
        for(int i=1;i<n;++i){//循环
            ans+=min(abs(a[i]-a[i+1])+abs(b[i]-b[i+1]),abs(a[i]-b[i+1])+abs(b[i]-a[i+1]));
            /*
            * 就是我在上面讲的公式
            * 对他们取min 
            */
        }
        printf("%lld\n",ans);//输出
    }
    // cin>>t;
    return 0;//完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。
}
```

---

## 作者：In_The_Shadow (赞：1)

## 题目翻译
你有两个长度为 $n$ 的数组：$a_1$,$a_2$,$\dots$,$a_n$ 和 $b_1$,$b_2$,$\dots$,$b_n$。
你可以任意次进行以下操作：
1. 选择整数下标 $i(1\le i\le n)$;
2. 交换 $a_i$ 和 $b_i$。

问什么是你在进行多次（可能没有）操作后 $\sum\limits_{i=1}^{n - 1}{\left(|a_i - a_{i+1}| + |b_i - b_{i+1}|\right)}$ 的最小值。

## 思路
可以看出用动态规划来做。对于状态 $f_{i,j}$，它代表 $a$ 数组和 $b$ 数组前 $i$ 个这样的和，而 $j$ 代表是否交换 $a_i$ 和 $b_i$。此时，状态转移方程就是
$$f_{i,0}=min(f_{i-1,0}+|a_i - a_{i+1}|+|b_i - b_{i+1}|,f_{i-1,1}+|b_i - a_{i+1}|+|a_i - b_{i+1}|)$$
$$f_{i,1}=min(f_{i-1,0}+|b_i - a_{i+1}|+|a_i - b_{i+1}|,f_{i-1,1}+|a_i - a_{i+1}|+|b_i - b_{i+1}|)$$

### 代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a[30],b[30];
long long f[30][2];
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		for(int i=2;i<=n;i++)
		{
			f[i][0]=min(f[i-1][0]+abs(a[i]-a[i-1])+abs(b[i]-b[i-1]),f[i-1][1]+abs(a[i]-b[i-1])+abs(b[i]-a[i-1]));
			f[i][1]=min(f[i-1][0]+abs(b[i]-a[i-1])+abs(a[i]-b[i-1]),f[i-1][1]+abs(a[i]-a[i-1])+abs(b[i]-b[i-1]));
		}
		cout<<min(f[n][0],f[n][1])<<endl;
	} 
	return 0;
}

```

---

## 作者：LYqwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1661A)

# 题目大意

给定两个长度为 $n$($2 \le n \le 25$) 的数列 $a,b$($1 \le a_i,b_i \le 10^9$)，你可以进行任意次操作：选择一个下标 $i$，并交换 $a_i$ 与 $b_i$。

经过若干次操作后，最小的 $\sum\limits^{n-1}_{i=1}(|a_i-a_{i+1}|+|b_i-b_{i+1}|)$ 是多少？

# 思路

两个数相减的绝对值，就是这两个数相差多少。

那么计算 $|a_i-a_{i+1}|$ 时，要让它最小，那么用 $a_i,a_{i+1}$ 分别与 $b_i,b_{i+1}$ 比大小，将小的放在 $a$ 中，大的都放在 $b$ 中，这样计算出来的绝对值一定是最小的。

我们只需要遍历一遍数组，计算一下相邻两项是 $|a_i-a_{i+1}|+|b_i-b_{i+1}|$ 小还是 $|a_i-b_i+1|+|b_i-a_i+1|$ 小，若是后者小，把 $a_{i+1}$ 和 $b_{i+1}$ 交换一下就行了。

最后再循环一遍，统计答案，这里注意要开 `long long`。

# 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
template<typename T=int>
inline T read(){
    T X=0; bool flag=1; char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
    if(flag) return X;
    return ~(X-1);
}

template<typename T=int>
inline void write(T X){
    if(X<0) putchar('-'),X=~(X-1);
    T s[20],top=0;
    while(X) s[++top]=X%10,X/=10;
    if(!top) s[++top]=0;
    while(top) putchar(s[top--]+'0');
    putchar('\n');
}

const int N=30;
int t,n,a[N],b[N];
long long ans;

int main(){
    t=read();
    while(t--){
        n=read();
        for(int i=1; i<=n; i++){
            a[i]=read();
        }
        for(int i=1; i<=n; i++){
            b[i]=read();
        }
        for(int i=1; i<n; i++){
            if(abs(a[i]-a[i+1])+abs(b[i]-b[i+1])>abs(a[i]-b[i+1])+abs(b[i]-a[i+1])){
                swap(a[i+1],b[i+1]); // 交换
            }
        }
        for(int i=1; i<n; i++){
            ans+=abs(a[i]-a[i+1])+abs(b[i]-b[i+1]);
        }
        write(ans);
        ans=0;
    }
    return 0;
}
```



---

## 作者：Exber (赞：1)

## 题意

给两个长度为 $n$ 的数组 $a$ 和 $b$，你可以进行以下操作任意次：

1. 选择一个 $i$

2. 交换 $a_i$ 和 $b_i$

求 $\sum\limits_{i=1}^{n-1}|a_i-a_{i+1}|+|b_i-b_{i+1}|$ 的最小值。

## 做法

贪心。

题面显然可以转换为求 $\sum\limits_{i=2}^{n}|a_i-a_{i-1}|+|b_i-b_{i-1}|$ 的最小值，那么在位置 $i$ 的交换操作对 $i$ 及它之后的序列没有影响。

所以我们可以顺序枚举每一个满足 $i\ge 2$ 的 $i$，若 $|b_i-a_{i-1}|+|a_i-b_{i-1}|<|a_i-a_{i-1}|+|b_i-b_{i-1}|$ 即交换后更优，那么就交换 $a_i$ 和 $b_i$。

可以证明这样做总是最优的，因为我们可以操作任意多次。

## AC 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <cstring>

using namespace std;

struct node
{
};

int n;
long long a[1919810],b[1919810];

inline void slove()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]); 
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
	}
	for(int i=2;i<=n;i++)
	{
		if(abs(b[i]-a[i-1])+abs(a[i]-b[i-1])<abs(a[i]-a[i-1])+abs(b[i]-b[i-1]))
		{
			swap(a[i],b[i]);
		}
	}
	long long ans=0;
	for(int i=1;i<n;i++)
	{
		ans+=abs(a[i]-a[i+1])+abs(b[i]-b[i+1]);
	}
	printf("%lld\n",ans);
}

int main()
{
	int _=1;
	scanf("%d",&_);
	while(_--)
	{
		slove();
	}
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

[本人的翻译](https://www.luogu.com.cn/paste/iutf4vqz)

我们贪心的枚举每一个 $i$ 从 $1$ 到 $n-1$ 查询局部最优解。我们发现，不管怎么交换，所有可能的情况都可以被表示为一下两种形式：
1. $\left|a_i-a_{i+1}\right|+\left|b_i-b_{i+1}\right|$
2. $\left|a_i-b_{i+1}\right|+\left|b_i-a_{i+1}\right|$

又因为不管如何交换，只会交换或不交换 $a$ 和 $b$ 的位置，并不会改变元素的值，所以每一个局部最优解都不会对其它的局部最优界产生影响。所以我们只需要把它们加起来即可。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int read(){
	int x=0,f=1;
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
bool cmp(int x,int y){
	return x<y;
}
void cf(){
	int n=read();
	long long a[n+1];
	long long b[n+1];
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	long long ans=0;
	for(int i=2;i<=n;i++)
		ans+=min(abs(a[i-1]-a[i])+abs(b[i-1]-b[i]),abs(a[i-1]-b[i])+abs(b[i-1]-a[i]));
	printf("%lld\n",ans);
	return;
}
int main(){
    int t=read();
    for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1661A)

## 题意

给出两个 $n$ 个数的数组 $a_{1\sim n},b_{1\sim n}$，你可以交换任意的 $a_i$ 和 $b_i(1\le i\le n)$，求 $\sum_{i=1}^n(|a_i-a_{i+1}|+|b_i-b_{i+1}|)$ 的最小值。

## 分析

分别考虑每一个 $|a_i-a_{i+1}|+|b_i-b_{i+1}|(1\le i<n)$，可以发现不管 $a_i,b_i$ 的值如何改变，$a_{i+1},b_{i+1}$ 都能通过交换位置或不换位置达到可能的两种取值 $|a_i-a_{i+1}|+|b_i-b_{i+1}|$ 或 $|a_i-b_{i+1}|+|b_i-a_{i+1}|$，所以对两种情况取最小值再求和即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=30;
int t,n;
ll sum,a[N],b[N];
int main(){
	t=read();
	while(t--){
		n=read();
		sum=0;
		for(int i=1;i<=n;i++)
			a[i]=read();
		for(int i=1;i<=n;i++)
			b[i]=read();
		for(int i=1;i<n;i++)
			sum+=min(abs(a[i]-a[i+1])+abs(b[i]-b[i+1]),abs(a[i]-b[i+1])+abs(b[i]-a[i+1]));
		write(sum);
		puts("");
	}
	return 0;
}
```


---

## 作者：CodeMao (赞：0)

本蒟蒻又来发题解啦~

本题只需要那么一丢丢的思维，其实还是比较简单的~

**思路**：

- 不管怎么交换，解只会存在这两种情况：
  
  - $|a_i-a_{i+1}|+|b_i-b_{i+1}|$
    
  - $|a_i-b_{i+1}|+|b_i-a_{i+1}|$
    
- 不管怎么交换都不会改变 $a$ 数组和 $b$ 数组中的元素的值，所以我们只需要在上面列举的两种情况中取最小值加起来就可以了。
  

**注意**：记得开 `long long` 。

上代码：

```cpp
#include <cstdio>
#include <cstring>
#define maxn 35
#define ll long long //简易定义long long类型
ll t,n,ans,k1,k2;
ll a[maxn],b[maxn];
inline void swap(ll &a,ll &b){ //交换两个元素的值
    a^=b^=a^=b;
}
inline ll min(ll a,ll b){ //求两个元素中较小值
    return a<b?a:b;
}
inline ll abs(ll a){ //求一个数的绝对值
    if(a<0) return ~a+1;
    return a;
}
inline void in(ll &a){ //快速读入
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
        a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
}
inline void op(ll a){ //快速输出 
    if(a>9) op(a/10);
    putchar(a%10+'0');
}
int main(){
    in(t);
    while(t--){
        in(n);ans=0; //注意ans要初始化
        std::memset(a,0,sizeof(a));
        std::memset(b,0,sizeof(b));
        for(int i=1;i<=n;++i) in(a[i]);
        for(int i=1;i<=n;++i) in(b[i]);
        for(int i=1;i<n;++i) //同思路
            ans+=min(abs(a[i]-a[i+1])+abs(b[i]-b[i+1]),abs(a[i]-b[i+1])+abs(b[i]-a[i+1]));
        op(ans),puts("");
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

本题可以使用动态规划解决。

设 $dp[i][0]$ 为考虑到第 $i$ 个数字，并且不会交换第 $i$ 个的最优解；$dp[i][1]$ 则为会交换第 $i$ 个的最优解。

可以得出：

+ 当 $i=1$ 时，$dp[i][0]=dp[i][1]=0$

+ 否则：

	$dp[i][0]=\operatorname{min}(|a[i]-a[i-1]|+|b[i]-b[i-1]|+dp[i-1][0],|a[i]-b[i-1]|+|b[i]-a[i-1]|+dp[i-1][1])$
    
   $dp[i][1]=\operatorname{min}(|a[i]-b[i-1]|+|b[i]-a[i-1]|+dp[i-1][0],|a[i]-a[i-1]|+|b[i]-b[i-1]|+dp[i-1][1])$
   
答案为 $\operatorname{min}(dp[n][0],dp[n][1])$

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 25
int t;
int n;
long long a[max_n+2];
long long b[max_n+2];
long long dp[max_n+2][2];
long long mi(long long a,long long b){
	return a<b?a:b;
}
long long absi(long long a){
	return a>=0?a:-a;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1661A_1.in","r",stdin);
	freopen("CF1661A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lld",a+i);
		for(int i=1;i<=n;++i)scanf("%lld",b+i);
		dp[1][0]=dp[1][1]=0;
		for(int i=2;i<=n;++i){
			dp[i][0]=mi(absi(a[i]-a[i-1])+absi(b[i]-b[i-1])+dp[i-1][0],absi(a[i]-b[i-1])+absi(b[i]-a[i-1])+dp[i-1][1]);
			dp[i][1]=mi(absi(a[i]-b[i-1])+absi(b[i]-a[i-1])+dp[i-1][0],absi(a[i]-a[i-1])+absi(b[i]-b[i-1])+dp[i-1][1]);
		}
		printf("%lld\n",mi(dp[n][0],dp[n][1]));
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/73707023)

By **dengziyue**

---

