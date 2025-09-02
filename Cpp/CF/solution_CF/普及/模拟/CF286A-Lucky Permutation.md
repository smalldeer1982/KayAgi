# Lucky Permutation

## 题目描述

A permutation $ p $ of size $ n $ is the sequence $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct integers, each of them is from $ 1 $ to $ n $ $ (1<=p_{i}<=n) $ .

A lucky permutation is such permutation $ p $ , that any integer $ i $ $ (1<=i<=n) $ meets this condition $ p_{pi}=n-i+1 $ .

You have integer $ n $ . Find some lucky permutation $ p $ of size $ n $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
1 
```

## 样例 #2

### 输入

```
2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
```

### 输出

```
2 4 1 3 
```

## 样例 #4

### 输入

```
5
```

### 输出

```
2 5 3 1 4 
```

# 题解

## 作者：liuyifan (赞：5)

## 找规律
找规律，发现四个一组，如果多一个，则中间那个对应为自己

code:
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")//玄学优化
#define reg register//register卡常
#define ll long long
#define y1 liuifan_y1
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3f
#define data liuyifan_data
#define next liuyifan_next//避免关键字
#define ture true
#define flase false
#define lowbit(x) x&(-x)
using namespace std;
int ans[100005],n;
int main()
{
    scanf("%d", &n);
    if(n%4!=0&&n%4!=1)return puts("-1"),0;//不满足的情况
    for(reg int i=1;i<=n>>1;i+=2)
    {
        ans[i]=i+1;
        ans[i+1]=n-i+1;
        ans[n-i+1]=n-i;
        ans[n-i]=i;
    }//按题意模拟
    if(n%4)ans[(n>>1)+1]=(n>>1)+1;
    /*位运算是一种特别快的运算,上述代码中n<<1相当于n*2，n>>1相当于n/2
    在NOIP等需要卡常的比赛中特别实用*/
    for(reg int i=1;i<=n;i++)printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：IAKIOI__ (赞：1)

### 吐槽

结论推错了好几个，成功被无语到了。

## 易犯错解

以为知道了第一个数是 $2$ 就可以推出所有数。其实程序只会在前 $2$ 个数与后 $2$ 个数之间循环，无法推出正确答案。

# 正解思路

首先，当 $n$ 对 $4$ 取模等于 $2$ 或 $3$ 时，输出 `-1`。

我们可以发现 $p_i+p_{n-i+1}=n+1$，且前 $\frac{n}{2}-1$ 项的奇数项都是从 $2$ 开始连续的偶数。对 $\frac{n}{2}+1$ 项到 $n-1$ 项的，如果 $n$ 是奇数，则偶数项是奇数，
如果 $n$ 是偶数，则奇数项是奇数，奇数应从大到小输出。
最后，如果 $n$ 是奇数，就将 $p_{\frac{n}{2}+1}$ 设为 $\frac{n}{2}+1$。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e6;
int n,x,p[MAXN];
int main(){
	cin>>n;
	if(n%4==2||n%4==3){
		cout<<-1;
		return 0;
	}else{
		x=2;
		for(int i=1;i<n/2;i+=2){//处理偶数
			p[i]=x;
			p[n-i+1]=n-x+1;
			x+=2;
		}
		x=1;
		for(int i=n-1;i>n/2;i-=2){//处理奇数
			p[i]=x;
			p[n-i+1]=n-x+1;
			x+=2;
		}
		if(n%2==1){
			p[n/2+1]=n/2+1;
		}
		for(int i=1;i<=n;i++){
			cout<<p[i]<<" ";
		}
	}
}
```

---

## 作者：lhs_chris (赞：0)

# 思路
这题是一道找规律的题目。一眼看不出规律可以先写个暴力输出一下。
```cpp
bool check()
{
	for(int i=1;i<=n;i++)
	{
		if(a[a[i]]!=n-i+1)
		{
			return 0;
		}
	}
	return 1;
}
void dfs(int now)
{
	if(flag)return;
	if(now==n+1)
	{
		if(check())
		{
			flag=1;
			for(int i=1;i<=n;i++)
			{
				cout<<a[i]<<" ";
			}
			exit(0);
		}
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			a[now]=i;
			dfs(now+1);
			vis[i]=0;
		}
	}
}
```
输出前十四个答案，答案如下。
```
1
-1
-1
2 4 1 3

2 5 3 1 4
-1
-1
2 8 4 6 3 5 1 7

2 9 4 7 5 3 6 1 8
-1
-1
2 12 4 10 6 8 5 7 3 9 1 11

2 13 4 11 6 9 7 5 8 3 10 1 12
-1
```
我们发现答案是四个为一轮。当 $n$ 取模 $4$ 等于 $2$ 或者 $3$ 时答案为 $-1$。那剩下的两种答案直接构造数组。

数组构造方法，详细见图与代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/s1wu7lr2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=3e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
int n,a[N];
int main()
{
	scanf("%d",&n);
	if(n%4==2 or n%4==3)
	{
		printf("-1");
		return 0;
	} 
	if(n%4)
	{
		int mid=(1+n)/2;
		a[mid]=mid;
		for(int i=1;i<mid;i+=2)
		{
			a[i]=i+1;
		}
		for(int i=mid+2;i<=n;i+=2)
		{
			a[i]=i-1;
		}
		for(int i=n-1;i>mid;i-=2)
		{
			a[i]=n-i;
		}
		for(int i=mid-1;i>1;i-=2)
		{
			a[i]=n-i+2;
		}
		for(int i=1;i<=n;i++)
		{
			printf("%d ",a[i]);
		}
	}
	else
	{
		int mid=n/2;
		a[mid]=mid+2;
		for(int i=1;i<mid;i+=2)
		{
			a[i]=i+1;
		}
		for(int i=mid-2;i>=2;i-=2)
		{
			a[i]=n-i+2;
		}
		for(int i=n-1;i>mid;i-=2)
		{
			a[i]=n-i;
		}
		for(int i=mid+2;i<=n;i+=2)
		{
			a[i]=i-1;
		}
		for(int i=1;i<=n;i++)
		{
			printf("%d ",a[i]);
		}
	}
	return 0;
}
/*
1
-1
-1
2 4 1 3

2 5 3 1 4
-1
-1
2 8 4 6 3 5 1 7

2 9 4 7 5 3 6 1 8
-1
-1
2 12 4 10 6 8 5 7 3 9 1 11

2 13 4 11 6 9 7 5 8 3 10 1 12
*/
```

---

## 作者：pyz51 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF286A)

[CF传送门](https://codeforces.com/problemset/problem/286/A)

[AC记录](https://codeforces.com/contest/286/submission/282001599)

# 题意简述
输出长度为 $n$ 的幸运数列，没有就输出 $-1$。  
若数列 $p$ 满足 $p_{p_i}=n-i+1$，那么 $p$ 就是幸运数列。
# 题解
**样例十分良心。**
  
对于长度为 $4$ 的幸运数列，$p_1 \gets 2$，$p_2 \gets 4$，$p_3 \gets 1$，$p_4 \gets 3$。

对于长度为 $5$ 的幸运数列，$p_1 \gets 2$，$p_2 \gets 5$，$p_3 \gets 3$，$p_4 \gets 1$，$p_5 \gets 4$。

接下来看一下长度为 $8$ 的：  
1. 首先让 $p_1 \gets 2$
2. 那么 $p_2$ 就要满足 $p_2 \gets 8-1+1=8$
3. $p_8 \gets 8-2+1=7$
4. $p_7 \gets 8-8+1=1$
   
这时候已经形成了一个闭环。  
从下一个没有被赋值的位置开始。

1. 首先让 $p_3 \gets 4$
2. 那么 $p_4$ 就要满足 $p_4 \gets 8-3+1=6$
3. $p_6 \gets 8-4+1=5$
4. $p_5 \gets 8-6+1=3$

最后输出：`2 8 4 6 3 5 1 7`。
## 规律
规律是四个一组：

  - $p_i \gets i+1$
  - $p_{i+1} \gets n-i+1$
  - $p_{n-i+1} \gets n-i$
  - $p_{n-i} \gets i$

证明：
  - $p_{p_i}=p_{i+1}=n-i+1$
  - $p_{p_{i+1}}=p_{n-i+1}=n-i=n-(i+1)+1$
  - $p_{p_{n-i+1}}=p_{n-i}=i=n-(n-i+1)+1$
  - $p_{p_{n-i}}=p_{i}=i+1=n-(n-i)+1$

**显然都是满足条件的。**

**若最后剩 $1$ 个（位置为 $\dfrac{n}{2}+1$），则 $p_{\frac{n}{2}+1} \gets \dfrac{n}{2}+1=n-(\dfrac{n}{2}+1)+1$。**  
**若最后剩 $2 \sim 3$ 个，则输出 $-1$。**

有了规律就可以做题了。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
int n,a[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void print(ll x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
    return;
}
int main(){
    cin>>n;
    int m=n;
    if(n==1){
        cout<<1;
        return 0;
    }
    if(n==2||n==3){
        cout<<-1;
        return 0;
    }
    int i;
    for(i=1;i+1<n-i;i+=2){
        a[i]=i+1;
        a[i+1]=n-i+1;
        a[n-i+1]=n-i;
        a[n-i]=i;
        m-=4;
    }
    if(m==1) a[i]=i;
    if(m==2||m==3){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定 $n$，构造一个序列 $p$ 使得任意 $i\in[1,n]$ 满足 $p_{p_{i}}=n-i+1$。

如果不存在，则输出 `-1`。

**解题思路**

四个一组，即 $(i,i+1,n-i,n-i+1)$，$p_i=i+1,p_{i+1}=n-i+1,p_{n-i+1}=n-i,p_{n-i}=i$。

验证：$p_{p_{i}}=p_{i+1}=n-i+1,p_{p_{i+1}}=p_{n-i+1}=n-i,p_{p_{n-i+1}}=p_{n-i}=i,p_{p_{n-i}}=p_i=i+1$，满足条件。

所以，$n=4k$ 时满足条件，除此之外 $n=4k+1$ 时 剩下的 $p_{2k+1}=2k+1$ 即可。

即 $n=4k+2$ 或 $n=4k+3$ 时不存在满足条件的 $p$，输出 `-1`。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, a[N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  if(n % 4 > 1) { cout << "-1"; return 0; }
  if(n == 1) { cout << "1"; return 0; }
  for(int i = 1; i <= (n >> 1); i += 2) {
    a[i] = i + 1, a[i + 1] = n - i + 1;
    a[n - i + 1] = n - i, a[n - i] = i;
  }
  if(n % 4) { a[(n >> 1) + 1] = (n >> 1) + 1; }
  for(int i = 1; i <= n; i++) {
    cout << a[i] << ' ';
  }
  return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF286A)

# First 题意

题意是说，给你一个 $n$，让你求一个长度为 $n$ 的序列 $p$，让序列 $p$ 满足以下条件。

1.序列 $p$ 中要出现 $1-n$ 中的所有数。

2.序列 $p$ 中，要让 $p_{p_i} = n - i + 1$。

# Second 思路

这题是一道**找规律**的题目，让我们看一下下列表格。

[表格](https://www.luogu.com.cn/paste/8y6g72wl)

大家发现没有，当 $n\bmod4 = 2$ 或 $n\bmod4 = 3$ 时，$p$ 序列不存在。

于是我们就有了一个特判。

```cpp
if (n % 4 == 2 || N % 4 == 3){
	printf ("-1");
   return 0;
}
```

然而这还不够，我们每一次找到一个还没有放数字的空位时，我们~~就可以乱放~~要判断一下，我们可以先放下 $i+1$。

为什么只放 $i+1$，而不放 $i$ 呢。

原因很简单，当 $p_i=i$ 时，$p_{p_i}=p_i=i=n-i+1$，但显然，对于许多情况，他是不满足的，所以 $p$ 不一定等于 $i$。

而当 $p_i = i + 1$ 之后，就有如下推导。

### $p_i = i$
### $p_{i+1} = n - i + 1$
### $p_{n - i + 1} = n - i$
### $p_{n - i} = i$

嘿，这样就构成了一个循环。

所以思路就出来了，先特判输出 ```-1``` 的情况，然后找到空位就按照上面的规则放数字。

但是，请大家回到表格看一下 $n = 5$ 的情况，如果按照上面的方法放数字的话，应该输出 $2 5 0 1 4$，所以最后输出时还有空的话，就补上 $i$。

这是为什么，因为我们每次都是 4 个一起处理，而只有 $n \bmod 4 = 0$ 和 $n \bmod 4 = 1$ 有解，所以只会出现 1 个这种情况，而且是在中间的，是因为我们每次都处理的时两端的数。

# Third Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, a[100005];
il void putt(ll x, ll v){
	if (a[x])
		return;
	a[x] = v;
	putt(v, n - x + 1);
}
int main(){
	scanf ("%lld", &n);
	if (n % 4 == 2 || n % 4 == 3){
		printf ("-1");
		return 0;
	}
	if (n == 1){
		printf ("1");
		return 0;
	}
	for (int i = 1; i <= n >> 1; i += 2){
		a[i] = i + 1;
		a[i + 1] = n - i + 1;
		a[n - i + 1] = n - i;
		a[n - i] = i;
	}
	for (int i = 1; i <= n; i++)
		printf ("%lld ", a[i] == 0 ? i : a[i]);
	return 0;
}

```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF286A)

### $\texttt{Description}$

输入一个正整数 $n$ ，输出一个长度为 $n$ 的幸运数列，若没有输出 $-1$ 。

### $\texttt{Solution}$

这题一眼 DFS 全排列，不过 $n \le 10^5$ ，深搜时间复杂度肯定爆炸。

所以我们可以**找规律**。

如果 $n=1$，直接输出 $1$，因为当 $n$ 为 $1$ 时，唯一的幸运排列就是 $1$。

如果 $n$ 是奇数，输出 $-1$ 。因为在幸运排列的定义中，对于任何整数 $i \ (1 \le i \le n)$ 都要满足特定条件，而当 $n$ 为奇数时无法找到满足条件的排列。

如果 $n$ 是偶数，进入循环生成幸运排列。循环从 $1$ 开始，每次增加 $2$，遍历所有的奇数位置 $i$ 。在每次循环中，先输出 $i + 1$ ，再输出 $i$ ，这样就可以保证满足幸运排列的条件。

举个例子：

当 $n = 4$ 时，先输出 $2$（即 $i + 1$ ，此时 $i = 1$），再输出 $1$（即 $i$），然后输出 $4$ 和 $3$，形成 `2 4 1 3` 的排列，满足幸运排列的条件。

### $\texttt{Code}$

代码很简单，就不贴了。

---

