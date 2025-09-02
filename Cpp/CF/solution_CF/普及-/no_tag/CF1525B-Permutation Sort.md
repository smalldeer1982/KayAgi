# Permutation Sort

## 题目描述

You are given a permutation $ a $ consisting of $ n $ numbers $ 1 $ , $ 2 $ , ..., $ n $ (a permutation is an array in which each element from $ 1 $ to $ n $ occurs exactly once).

You can perform the following operation: choose some subarray (contiguous subsegment) of $ a $ and rearrange the elements in it in any way you want. But this operation cannot be applied to the whole array.

For example, if $ a = [2, 1, 4, 5, 3] $ and we want to apply the operation to the subarray $ a[2, 4] $ (the subarray containing all elements from the $ 2 $ -nd to the $ 4 $ -th), then after the operation, the array can become $ a = [2, 5, 1, 4, 3] $ or, for example, $ a = [2, 1, 5, 4, 3] $ .

Your task is to calculate the minimum number of operations described above to sort the permutation $ a $ in ascending order.

## 说明/提示

In the explanations, $ a[i, j] $ defines the subarray of $ a $ that starts from the $ i $ -th element and ends with the $ j $ -th element.

In the first test case of the example, you can select the subarray $ a[2, 3] $ and swap the elements in it.

In the second test case of the example, the permutation is already sorted, so you don't need to apply any operations.

In the third test case of the example, you can select the subarray $ a[3, 5] $ and reorder the elements in it so $ a $ becomes $ [2, 1, 3, 4, 5] $ , and then select the subarray $ a[1, 2] $ and swap the elements in it, so $ a $ becomes $ [1, 2, 3, 4, 5] $ .

## 样例 #1

### 输入

```
3
4
1 3 2 4
3
1 2 3
5
2 1 4 5 3```

### 输出

```
1
0
2```

# 题解

## 作者：EuphoricStar (赞：9)

## 思路

简单结论题。

显然，如果数组已经排好序了，答案为 $0$；

如果第一个元素为 $1$ 或者最后一个元素为 $n$，答案为 $1$。例如：$1,3,5,2,4$，无论第 $2$ 到第 $5$ 个元素是按怎样的顺序排列，我们都可以将其变为 $2,3,4,5$。

如果最后一个元素为 $1$ 且第 $1$ 个元素为 $n$，答案为 $3$。例如：$5,3,4,2,1$ --> $2,3,4,5,1$ --> $2,1,3,4,5$ --> $1,2,3,4,5$。

否则答案为 $2$。例如：$2,5,3,1,4$ --> $1,2,3,5,4$ --> $1,2,3,4,5$。

## 代码

```cpp
        bool flag = 1;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] != i) {
                flag = 0;
            }
        }
        if (flag) {
            cout << 0 << endl;
            continue;
        }
        if (a[1] == 1 || a[n] == n) {
            cout << 1 << endl;
        } else if (a[n] == 1) {
            if (a[1] != n) {
                cout << 2 << endl;
            } else {
                cout << 3 << endl;
            }
        } else {
            cout << 2 << endl;
        }
```


---

## 作者：miraculously (赞：4)

题目大意：

有一个包含 1 到 $n$ 数列，每一次能选择一段区间排序（不能选择整个数列），至少需要几次才能使这个数列从小到大排序。

分析：

这道题需要找一下规律，当这个数列已经从小到大排序时，不用排序，当第一个数为 1，第 $n$ 个数为 $n$ 时，显然只要 1 次（把 2 到 $n-1$ 进行排序），当第一个数为 $n$，第 $n$ 个数为 1 时要三次（把 1 到 $n-1$ 排一遍，再把 $n$ 到 2 排一遍，最后交换 1 和 2），剩下的要两次。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[51];
int main()
{
	int t,n,f;
	scanf("%d",&t);
	while(t--)
	{
		f=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]!=i)
			f=1;
		}
		if(f==0)
		printf("0\n");
		else if(a[1]==n&&a[n]==1)
		printf("3\n");
		else if(a[1]!=1&&a[n]!=n)
		printf("2\n");
		else
		printf("1\n");
	}
}
```


---

## 作者：翼德天尊 (赞：1)

题目给定一个序列，要求每次选定任意一个区间进行排序，求出最小排序次数使得序列升序。

首先显而易见，如果序列初始升序排列，则次数为 $0$。

然后我们贪心地考虑，由于每次排序不能选择整个序列，为了使得排序的范围尽可能地大，我们可以每次选择 $n-1$ 个元素进行排序，这 $n-1$ 个可以是前 $n-1$ 个，也可以是后 $n-1$ 个，而我们将每次排序的方案都设定为排成升序。

1. 序列第一个元素为 $1$，则排后 $n-1$ 个元素；最后一个元素为 $n$ 同理。次数为 $1$。

2. 序列第一个元素为 $n$，最后一个元素为 $1$。这应该是最复杂的情况。我们不妨先排序前 $n-1$ 个元素，得到一个由 $2$ 到 $n$，末尾为 $1$ 的序列，然后再排序后 $n-1$ 个元素，得到一个开头为 $2$ 和 $1$，后面升序排列的序列，最后再排序前 $n-1$ 个元素即可。次数为 $3$。

3. 剩下的情况就是序列第一个元素和最后一个元素非 $1$ 非 $n$，则先排前 $n-1$ 个元素将 $1$ 排到首位，再按照第一种情况排后 $n-1$ 个元素即可。次数为 $2$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 205
int t,a[N]; 
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
int gcd(int x,int y){
	if (y==0) return x;
	return gcd(y,x%y); 	
}
int main(){
	t=read();
	while (t--){
		int n=read(),ans=0;
		bool pd=0;
		for (int i=1;i<=n;i++){
			a[i]=read();
			if (a[i]!=i) pd=1;
		}
		if (pd==0) puts("0");
		else if (a[1]==1||a[n]==n) puts("1");
		else if (a[1]==n&&a[n]==1) puts("3");
		else puts("2");
	}
	return 0;
}
```


---

## 作者：Doqin07 (赞：1)

$\mathbf{Tutorial}$：

结论题，分为 $4$ 种情况：
	
    
- 如果数组已经有序，那么直接输出 $0$

- 如果数组第一个元素为 $1$, 或者最后一个元素为 $n$，答案为 $1$. 例如：

$\begin{array}{c |c}1&1\\5&2\\4&3\\3&4\\2&5\end{array}$

- 如果数组的最后一个元素为 $1$, 且第一个元素为 $n$，答案为 $3$. 例如:

$\begin{array}{c |c|c|c}5&2&2&1\\3&3&1&2\\4&4&3&3\\2&5&4&4\\1&1&5&5\end{array}$

- 若上述条件均不满足，则输出 $2$, 因为我们可以把它变成第二种情况，然后同理就好了

----
$\mathbf{Solution}$：

```cpp
/*Coder:DongYinuo*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7;
#define F(i, l, r) for (int i = l; i <= r; ++i)
#define REP(i, r, l) for (int i = r; i >= l; --i)
#define mem(a,b) memset(a, b, sizeof(a));
#define MP make_pair
#define PB push_back
#define PII pair<int, int>
#define PLL pair<ll, ll>
#define all(a) begin(a), end(a)
#define sz(a) ((int)a.size())
#define lson ind * 2 
#define rson ind * 2 + 1

const int N = 100010;

namespace IO{
    int I(){
        char c; int x = 0, f = 1;
        while (c = getchar()){ if (c == '-') f = -1;if (isdigit(c)) break;}
        while (isdigit(c)){ x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();}
        return x * f;
    }
    template <typename T>
    void Rd(T& arg){
        arg = I();
    }
    template <typename T, typename...Types>
    void Rd(T& arg, Types&...args){
        arg = I();
        Rd(args...);
    }

    ll L(){
        char c; int x = 0, f = 1;
        while (c = getchar()){ if (c == '-') f = -1;if (isdigit(c)) break;}
        while (isdigit(c)){ x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();}
        return x * f;
    }
    template <typename T>
    void RLd(T& arg){
        arg = L();
    }
    template <typename T, typename...Types>
    void RLd(T& arg, Types&...args){
        arg = L();
        Rd(args...);
    }

}

namespace REGULAR{
    void test(int x){
        cout << x << " ";
    }
    template <typename T>
    void debug(T& arg){
        test(arg);
    }
    template <typename T, typename...Types>
    void debug(T& arg, Types&...args){
        test(arg);
        debug(args...);
    }

    ll qpow(ll a, ll b, ll c){
        ll ans = 1 % c; a = a % c;
        while (b){
            if (b & 1){
                ans = ans * a % c;
            }
            b = b >> 1, a = a * a % c;
        }
        return ans;
    }

    struct ufSet{
        int f[N];
        void init(){
            F(i, 1, N){
                f[i] = i;
            }
        }
        int find(int x){
            return x ^ f[x] ? f[x] = find(f[x]) : x;
        }
        void merge(int x, int y){
            f[find(x)] = find(y);
        }
    };

}

using namespace IO;
using namespace REGULAR;

namespace SOLVE{
    
    int n, a[55];
    bool flag = 1;

    void main(){
        Rd(n); flag = 1; mem(a, 0);
        F (i, 1, n){
            Rd(a[i]);
            if (a[i] != i){
                flag = 0;
            }
        }

        if (flag){
            puts("0");
        } else if (a[1] == 1 || a[n] == n){
            puts("1");
        } else if (a[1] == n && a[n] == 1){
            puts("3");
        } else{
            puts("2");
        }
    }
}

// #define int long long

// signed main(){
int main(){

#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    int t = 1;
    cin >> t;
    while (t--){
        SOLVE::main();
    }

    return 0;
}

```


---

## 作者：GoldenFishX (赞：1)

### 题目大意

给定一个排列，每次可以选一个子段，随意调整子段内元素的顺序，求最少几次操作可以排序。子段不能是全部数组。

### 主要思路

1. 显然，如果这个排列是有序的，那么无须排序，直接输出$0$

1. 然后我们可以发现，要使得操作数最少， 就要让排序的范围尽量大。但题目规定，不能一次排序全部的，所以就只能排序前 $n-1$ 个或者后 $n-1$ 个。

1. 可是还有一个数没有被排序，这个数可以分 $3$ 种情况讨论

> ##### 1. 这个数就在它应该待的位置，无须继续排序，输出$1$
> 
> ##### 2.第一个数在第$n$位且第$n$个数在第一位，我们就需要先将后$n-1$个数排序(前$n-1$个也行),再第一个数排序到中间，然后再排序到最后一位。(以下是例子)
>```
> 4 2 3 1
> 4 1 2 3 (将后3个数排序)
> 1 2 4 3 (对前3个数排序，将最大值排序到中间)
> 1 2 3 4 (对后3个数排序，将最大值移动到后面)
> ```
> ##### 3.这个数应该待在中间，只需再将这个数排序到中间即可

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50 + 5;

int a[MAXN];
int n;

int main() {
  int t;
  cin >> t;
  while (t--) {
    bool f = 1;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (a[i] != i + 1) {
        f = 0;
      }
    }
    if (f) {  //无须排序
      cout << 0 << endl;
    } else if (a[0] == 1 || a[n - 1] == n) {  //剩下的数在应该待的位置上
      cout << 1 << endl;
    } else if (a[0] == n && a[n - 1] == 1) {  //第一个数在第n位且第n个数在第一位
      cout << 3 << endl;
    } else {
      cout << 2 << endl;
    }
  }
  return 0;
}

```

---

## 作者：山田リョウ (赞：1)

- 如果已经是升序了，输出 $0$。
- 如果第一个是最小的或者最后一个是最大的 $1$ 次就够，因为第一个或最后一个已经到位了，把剩下的排一下就好了。
- 如果第一个不是最大的或者最后一个不是最小的就 $2$ 次就够，只说第一个不是最大的情况吧，最后一个不是最小的也差不多：把 $2 \sim n$ 先排一下，再排 $1 \sim n-1$。
- 任何情况 $3$ 也够了，可以先排 $2 \sim n$，再排  $1 \sim n-1$，最后排 $n-1 \sim n$。
```cpp
#include<cstdio>
int main(){
	int t,n,a[50],ans;std::scanf("%d",&t);
	for(;t--;){ans=0,std::scanf("%d",&n);for(int i=0;i<n;++i)std::scanf("%d",a+i),ans|=(a[i]!=i+1);ans+=(a[0]>1&&a[n-1]<n)+(a[0]==n&&a[n-1]==1);std::printf("%d\n",ans);}
	return 0;
}
```

---

## 作者：oimaster (赞：1)

分类一下数据的几种情况。

- 序列刚开始就已经排好序了。这时候保持即可，输出 $0$。结束程序。

否则，我们就知道这个序列一定是需要重排列的。

- 序列最后一个位置就是 $n$，说明 $[1,n)$ 中一定有不合法的东西。所以我们只需要重排列 $[1,n)$ 即可。
- 序列第一个位置是 $1$，说明 $(1,n]$ 中有不合法的东西。我们需要重排列 $(1,n)$。

上面两种情况输出 $1$ 即可。如果还是不满足要求，就还剩一点情况。

- 序列最后一个字符是 $1$，第一个字符是 $n$，那么显然需要重排 $3$ 次：
1. 排成 $2,3,4,5,\dots,n,1$
2. 排成 $2,1,3,4,5,\dots,n$
3. 排成 $1,2,3,4,5,\dots n$

- 否则，我们只需要排列两次即可。

代码：

```cpp
#include<iostream>
using namespace std;
void solve(){
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;++i)
		cin>>a[i];
	bool flag=true;
	for(int i=1;i<=n;++i)
		if(a[i]!=i){
			flag=false;
			break;
		}
	if(flag){
		cout<<0<<endl;
		return;
	}
	if(a[1]!=1&&a[n]!=n)
		if(a[1]==n&&a[n]==1)
			cout<<3<<endl;
		else
			cout<<2<<endl;
	else
		cout<<1<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--)
		solve();
}
```

---

## 作者：听取MLE声一片 (赞：0)

万恶的出题人说不能交换整个数组，所以我们就要交换长度为 `n-1` 的区间。

注：翻译中漏了一句“**不能一次性操作整个区间**”。

每次操作可以把一段区间排成升序，显然就可以分情况讨论：


-  已经是升序了

显然输出 `0` 即可。

- 第一个数是 `n` 且第 `n` 个数为 `1`

第一次操作将 `n` 移到中间（将区间 `1` 到 `(n-1)` 排为升序）；第二次操作把 `n` 移动到最右边且把`1` 移到中间（将区间 `2` 到 `n` 排为升序）；第三次操作把 `1` 移动到最左边（将区间 `1` 到 `(n-1)` 排为升序）。

输出 `3` 即可。


- 第一个数不为 `1` 且第 `n` 个数不为 `n`


区间 `1` 到 `(n-1)` 和区间 `2` 到 `n-1` 升序排两次即可。

输出 `2` 即可。

- 其他情况（第一个数为 `1` 或第 `n` 个数为 `n`等）

输出 `1` 即可。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,a[51],t;
int main()
{
	t=read();
	while(t--){
		int p=0;
		n=read();
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(a[i]!=i)
				p=1;
		}
		if(p==0){
			cout<<0<<endl;
			continue;
		}
		if(a[1]==n&&a[n]==1){
			cout<<3<<endl;
			continue;
		}
		if(a[1]!=1&&a[n]!=n){
			cout<<2<<endl;
			continue;
		}
		cout<<1<<endl;
	}
	return 0;
}

```

---

## 作者：斜揽残箫 (赞：0)

## Description

给你一个长度为 $n$ 的排列，每次可以任意调动一个连续子区间的元素，求把这个区间变成一个升序排列的最小次数。

水 ： 一开始就以为只有 0，1，2 这三种情况，之后就 $\color{red}{\text{Wrong answer on test 2}}$，几分钟后才发现有 3 的情况，菜鸡实锤了。

## Solution

一道结论题，分情况来讨论。

首先给你的就是一个升序排列，输出 0。

给你的排列第一个数是 1，或者最后一个数是 $n$，这种情况下无论这中间有多么乱，都是可以一次排完，因为我们可以任意调动 $1 \sim n - 1$ 或者是 $2 \sim n$ 之间的元素。

给你的排列第一个数是 $n$，并且最后一个数是 1，这种情况下需要 3 次排序，因为每次只能调动一段连续的子区间，并且不能调动整个区间，必须第一步先将 1 或者 $n$ 从最后或者最前面换出来，再把分别把这两个放到应该放的地方，总共三步，其余的元素只需要在这之中顺便排完就行了。

最后就是其余情况了，因为最边上的不是 1 或者 $n$，我们又没法一次性调动全部区间，所以我们可以先排 $n - 1$ 个，使得就两个元素不在位，之后在排一下就行了。

总共就这四种情况。

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int Maxk = 100;
int a[Maxk];
int cnt = 0;
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
signed main()
{
  int T = read();
  while(T --) {
    int n = read();
    bool f = false;
    for(int i = 1;i <= n;i ++) a[i] = read();
    for(int i = 1;i <= n;i ++) if(a[i] != i) f = true;
    if(!f) {
      cout << 0 << endl;
    }
    else {
      if(a[1] == 1 || a[n] == n) cout << 1 << endl;//正向为 1 
      else if(a[1] == n && a[n] == 1) cout << 3 << endl;//反向为 3  
      else cout << 2 << endl;
    }
  }
  return 0;
}


```

---

## 作者：qfpjm (赞：0)

- 简单题
1. 对于排序好的数组，直接输出 $0$。
1. 对于头尾为 $n$ 或 $1$ 的数组，输出 $1$。无论 $1$ 到 $n - 1$, 还是 $2$ 到 $n$，我们都可以将其变为要求顺序。
1. 如果第一个位置是 $n$，最后一个位置是 $1$，输出 $3$。
1. 否则输出 $2$。
- 这题因该不需要代码了吧，几个 $if\ for$ 就可以了。
- 也不知道为什么这题的时间限制是 $2s$.

---

## 作者：FutaRimeWoawaSete (赞：0)

# [B](https://www.luogu.com.cn/problem/CF1525B)

刚开始的时候没发现性质（                  

想了一会儿发现一种很~~流氓~~的方法，直接考虑暴力草 $[1 , n - 1]$ 和 $[2 , n]$ 两个区间不就好了，于是开始写。                 

这时候旁边的LJS来了一句：              

- 你就没考虑答案有 $3$ 的情况吗？                  

这句话瞬间把我点醒了，多特判了一下就过掉了。                

整理出来就是这么个分类讨论：               

- 对于排好序的情况答案就是 $0$ ；                

- 如果首/尾已经合法了答案就是 $1$ ；                   

- 如果首/尾位置反过来了答案就是 $3$ ；             

- 其余情况可以直接暴力草 $[1 , n - 1]$ 和 $[2 , n]$ 两个区间，答案是 $2$ 。                   

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Len = 1e5 + 5;
int n,m,a[Len];
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d",&n);bool flag = false;
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
		for(int i = 1 ; i <= n ; i ++) if(a[i] != i) flag |= 1;
		if(!flag) puts("0");
		else if(a[1] == 1 || a[n] == n) puts("1");
		else if(a[n] == 1 && a[1] == n) puts("3");
		else puts("2");
	}
	return 0;
}
```

---

## 作者：dalao_see_me (赞：0)

## 题目大意
给一个长度为 $n$ 的全排列，要求你对任意的连续区间（长度小于 $n$）任意调换顺序，求把序列变为升序的最小操作次数。
## 题解
这是一道结论题。我们来分类讨论。

当整个序列已经有序时，答案显然为 $0$。

当 $a_1=1$ 或 $a_n=n$ 时，只需要排序剩下的位置即可，答案是 $1$。

当 $a_1=n$ 且 $a_n=1$ 时，我们需要将第一个 $n$ 输送到中间位置，再把 $1$ 输送到中间位置顺便把 $n$ 给最后一位，再对 $1$ 排序，也就是说需要 $3$ 次操作。

对于剩下的情况，一定只需要两次~~读者自证不难~~。

然后就可以愉快地写代码了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=55;
int _,n;
int a[N];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	_=read();
	while(_--){
		n=read();int flag=1;
		for(int i=1;i<=n;i++)a[i]=read(),flag&=(a[i]==i);
		if(flag){//已经有序
			puts("0");
			continue;
		}
		if(a[1]==1||a[n]==n){//只需要一次的情况
			puts("1");
			continue;
		}
		if(a[1]==n&&a[n]==1){//需要3次的情况
			puts("3");
			continue;
		}
		puts("2");//另外的情况（需要2次）
	}//记得别打错||和&&
	return 0;
}
```

---

