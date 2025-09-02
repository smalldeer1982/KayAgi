# Mainak and Interesting Sequence

## 题目描述

### 题目大意

认定一个长度为 $n$ 的序列 $a$ 是有趣的有且仅当满足以下条件：

- 对于**任意**一个整数 $a_i$，所有**严格小于**它的数的异或和为 $0$。( 假定所有满足条件的数为 $b_j$，则异或和为 $0$ 表示 $b_1 \; xor \; b_2 \; xor \; \dots \; xor \; b_j = 0$，xor 表示按位异或 )

请求出满足 $\sum_{i = 1}^n a_i = m$ 的长度为 $n$ 有趣的序列。 若有多种构造方式，则任意输出一种即可。

例如：$[1,3,2,3,1,2,3] , [4,4,4,4] , [25]$ 是有趣的，而 $[1,2,3,4] \; (p_2 = 1 \neq 0), \; [4,1,1,2,4] \; (p_4 = 1 \; xor \; 1 \; xor \; 2 = 2 \neq 0), \; [29,30,30] \; (p_{30} = 29 \neq 0)$不是有趣的。( 其中 $p_i$ 表示题目要求中的异或和 )。

## 样例 #1

### 输入

```
4
1 3
6 12
2 1
3 6```

### 输出

```
Yes
3
Yes
1 3 2 2 3 1
No
Yes
2 2 2```

# 题解

## 作者：MoyunAllgorithm (赞：2)

### 题目大意
对于数列 $a_{1..N}$ ，如果他满足：

1. 对于 $a_{i} \in a $ , $a$ 内所有小于 $a_{i}$ 的元素的异或和为 $0$；

2. $\sum ^ {N} _ {i=1} a_{i} = M$。

那么我们认为 $a$ 是有趣的。

给你 $N$、$M$，任意构造一个有趣的 $a$（或者判断无解）。

### 思路

首先，如果 $N>M$，无解。

我们可以想到，偶数个相同的数的异或和是0。那么，如果 $N$ 是奇数，显然可以构造一个

$ a=\left \{ 1,1,1,1,....,M-N+1 \right \} $

其中，里面有 $N-1$ 个 $1$，也就是偶数个 $1$，异或和是 $0$。

如果 $N$ 是偶数呢？这时，如果 $M$ 是偶数，也可以类似的构造

$ a = \left \{ 1,1,1,1,....,\dfrac{M-N+2}{2},\dfrac{M-N+2}{2}  \right \} $

因为 $N$、$M$ 是偶数，所以 $\dfrac{M-N+2}{2}$  是整数。因此，如果 $M$ 是奇数，那么是无解的，因为这时你无法将 $M-N+2$ 分成两个相等元素。

### 代码


```c
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int T,N,M;
int a[MAXN];
int ans;
int main()
{
	scanf("%d",&T);//多组输入数据哦
	while(T--)
	{
		scanf("%d %d",&N,&M);
		if(N>M)
		{
			puts("No");
			continue;
		}
		if(N%2==1)//N是奇数肯定可以
		{
			puts("Yes");
			for(int i=1;i<N;i++) printf("1 ");
			printf("%d\n",M-N+1);
			continue;
		}
		if(N%2==0&&M%2==0)
		{
			puts("Yes");
			for(int i=1;i<N-1;i++) printf("1 ");
			printf("%d %d\n",(M-N+2)/2,(M-N+2)/2);
			continue;
		}
		if(N%2==0&&M%2==1)
		{
			puts("No");
			continue;
		}
	}
	return 0;
}
```
**撒花**


---

## 作者：__bjxx0201__ (赞：0)

## 题面大意

给定一个长度为 $n$ 的 $a$ 数列，如果满足总和为 $m$ 且所有元素的异或和为 $0$，就是一个有趣的数列。

请问是否可以构造出一个有趣的数列，无法构造时输出 `No`。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1726B)

$n>m$ 时，无解，输出 `No`。

异或的性质不多说了，不熟悉的同学可以[看一下这里](https://www.luogu.com.cn/paste/argis0zi)。这里就不多阐述了。

接下来我们需要分类讨论。

当 $n$ 为奇数时，偶数个 $1$ 组成的数列再加上最后一个非 $1$ 的数字即可以组成一个异或和为 $0$ 的数列，输出 `Yes`。

当 $n$ 为偶数时，如果 $m$ 也为偶数，那么可以构造一个最后两个数是偶数，其余的都是奇数的一个数列，也是可以的。其余方案，就不可以了。

最后注意以下几点：

- 有 $T$ 组数据，$1\le T \le 10^5$。
- 最好使用快读快输来写。

---

## 作者：TemplateClass (赞：0)

文中使用符号 $\oplus$ 表示按位异或操作。

---

英文题面中提到要求构造的 $a _ i \ge 1$，那么 $\sum \limits _ {i = 1} ^ n a _ i$ 的最小值是 $n$，所以当 $m < n$ 时无解。

考虑异或的定义：相同的数对应位上是 $0$，不同的是 $1$。所以得到：

- $a \oplus b = 0$ 当且仅当 $a = b$。  
  因为要使一个数与 $a$ 异或的结果 $= 0$，显然每一个对应的二进制位上都要与 $a$ 相同，那么这个数整体也与 $a$ 相等。

- $a \oplus b = a$ 当且仅当 $b = 0$。  
  考虑 $a$ 的每一个二进制位，若此位为 $0$，要使结果的位仍然为 $0$，只有 $0 \oplus 0 = 0$；同理，也只有 $1 \oplus 0 = 1$，所以 $b = 0$。

由上面两个结论，我们得到：**偶数个相同的数的异或结果 $\bm{= 0}$。**

不难发现当 $n$ 是奇数时，构造 $a = (1, 1, 1, \cdots, 1, m - (n - 1))$ 即可。在这个序列中，只有 $a _ n$ 存在严格小于它的数，而这些数的异或值正好是 $0$。

再考虑 $n$ 是偶数的情况，我们可以先仿照 $n$ 是奇数的情况，即将 $a _ 1 \sim a _ {n - 2}$ 都填充为 $1$。由于题目要求的是严格小于，我们则可以直接将最后两个数填充为 $\dfrac{m - (n - 2)}{2}$，但是题目要求 $a _ i \in \Z ^ +$，所以当 $n$ 是偶数且 $m - (n - 2) \equiv 1 \pmod 2$ 时，无解。

```cpp
int n, m;

void solve(){
	std::cin >> n >> m;
	
	if(m < n || (!(n & 1) && ((m - (n - 2)) & 1))) {
		std::cout << "No\n";
		return ;
	}
	
	std::cout << "Yes\n";
	for(int i = 1; i <= n - 2; ++i) {
		std::cout << "1 ";
	}
	
	if(n & 1) {
		std::cout << (n - 1 > 1 ? "1 " : "") << m - (n - 1) << "\n"; 
	} else {
		int p = (m - (n - 2)) >> 1;
		std::cout << p << " " << p << "\n";
	}
}
```

---

## 作者：I_like_play_eggy (赞：0)

这是一道**构造题**。

## 题意简述

定义『有趣的数列』：对于一个数列 $a$ 中的每个 $a_i$，若 $a$ 中所有**严格小于** $a_i$ 的元素的 $\operatorname{xor}$ 和为 $0$，称数列 $a$ 是『有趣的』。

有 $T$ 组数据，每组数据给定数列长度 $n$ 与数列元素和 $m$，要求构造一个『有趣的数列』，无解输出 `No`。

## 思路

显然的，当 $N>M$ 时一定无解。

考虑到异或的性质：偶数个相同的数的 $\operatorname{xor}$ 和为 $0$。

当 $N$ 为奇数时，显然可以构造一个序列，前 $N-1$ 个数是 $1$，最后一个数是 $M-N+1$。

同理，$N$ 为偶数时，构造的序列前 $N-2$ 个数是 $1$，后 $2$ 个数是 $\frac{M-N+2}{2}$。若 $M$ 为奇数，则 $\frac{M-N+2}{2}$ 为小数，此时无解。

即：

$$
\begin{cases}
  \text{No Solution} & N>M \operatorname{or} (N \bmod 2=0 \operatorname{and} M \bmod 2 = 1) \\
  \{1,1,1,\dots,M-N+1\} & N\le M\operatorname{and} N \bmod 2=1 \\
  \{1,1,1,\dots,\frac{M-N+2}{2}，\frac{M-N+2}{2}\}\ & N\le M\operatorname{and} N \bmod 2=0 \operatorname{and} M \bmod 2 = 0
\end{cases}
$$

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

void read(int& x)
{
	char s = getchar();
	int sign = 1;
	x = 0;
	while (s < '0' || s > '9')
	{
		if (s == '-') sign = -1;
		s = getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = x * 10 + s - '0';
		s = getchar();
	}
	x *= sign;
}

int main()
{
	int T, n, m;
	read(T);
	while (T --)
	{
		read(n), read(m);
		if (n > m || !(n & 1) && (m & 1))
		{
			printf("No\n");
			continue;
		}
		printf("Yes\n");
		if (n & 1)
		{
			for (int i = 1; i < n; i ++)
			{
				printf("1 ");
			}
			printf("%d\n", m - n + 1);
		}
		else
		{
			for (int i = 2; i < n; i ++)
			{
				printf("1 ");
			}
			printf("%d ",  (m - n + 2) >> 1);
			printf("%d\n", (m - n + 2) >> 1);
		}
	}
	return 0;
}
```

---

## 作者：xiaokang_suancai (赞：0)

# CF1726B 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1726B)
## 题目大意
给定一个长度为 $n$ 的数组 $a$，如果该数组同时满足以下条件，我们认定该数组是有趣的：
1. 该数组所有数的和为 $m$。
2. 对于数组 $a$ 中的任意一个元素 $a_i$，该数组内所有小于 $a_i$ 的元素的异或之和为 $0$。\
现在给定 $n,m$，要求我们任意构造出一个有趣的数组 $a$，使 $a$ 符合以上条件。
## 思路分析
很明显，当 $n > m$ 时，无解。\
我们知道，偶数个相同数的异或之和为 $0$。\
所以，当 $n$ 为奇数时，前 $n-1$ 个元素为 $1$，第 $n$ 个元素为 $m-n+1$；\
当 $n$ 为偶数时，同理可得，前 $n-2$ 个元素为 $1$，第 $n-1$ 和第 $n$ 个元素均为 $\frac{m-n+2}{2}$。\
由于 $n$ 为偶数，所以 $m$ 必须也为偶数才能使第 $n-1$ 和第 $n$ 个元素均为整数。因此，如果 $m$ 为奇数，那么也是无解的。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int main()
{
	cin>>t; // 注意多组数据
	while(t--)
	{
		cin>>n>>m;
		if(n>m)
			cout<<"No"<<endl; // n > m 的时候
		else if(n%2!=0)
		{
			cout<<"Yes"<<endl;
			for(int i=1;i<n;i++)
				cout<<1<<" ";
			cout<<m-n+1<<endl;
		} // n 为奇数的时候
		else if(m%2==0)
		{
			cout<<"Yes"<<endl;
			for(int i=1;i<n-1;i++)
				cout<<1<<" ";
			cout<<(m-n+2)/2<<" "<<(m-n+2)/2<<endl;
		} // n 为偶数， m 为奇数的时候
		else
			cout<<"No"<<endl; // n 为偶数， m 为偶数的时候
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1726B)

---

# 思路：
首先我们很容易想到一种使异或和为 $0$ 的简单方法：偶数个相同的数进行异或。

所以第一种方法就出来了：当 $n$ 为奇数的时候，$n - 1$ 一定是偶数，这时候我们就维护前 $n - 1$ 个数都为 $1$，然后第 $n$ 个数字 就维护为 $m - n + 1$ 即可。这时候即满足 $n$ 个数，也满足和为 $m$。

$n$ 无非奇数或者偶数，讨论完 $n$ 为奇数接下来就讨论 $n$ 为偶数：我们的思路大概还是凑出偶数个相同的数，这样异或和就是 $0$。

$n$ 为 偶数的时候，$m$又分为奇偶数两种情况：

1. $m$ 为偶数的时候，此时 $n$ 和 $m$ 都为偶数，很容易一种想法：

      将 $m$ 均分为 $n$ 份，这样就是 $m \div n$ 个相同的数了，他们只有一个空序列，而空序列的异或和为 $0$，但是这种在不能整除时是错误的，最后的数组之和不是 $m$。

      既然这种不行，但是我们可以发现 $n$ 是个偶数，我们可以设一个 $x$，肯定有 $n = 2 + x$，而且此时的 $x$ 一定是个偶数，$2$ 也是偶数

      这样就分成了 $x$ 个相等的数加上 $2$ 个相等的数了，偶数个相同的数异或和一定是 $0$，这时候只用满足分出的这些数之和是 $m$ 即可。

    很简单的方法，我们先分出 $x$ 个 $1$，再分出来两个 $(m - x) \div 2$ 即可。

---

2. $m$ 为奇数的时候，此时 $m$ 为奇数，$n$ 为偶数，这个显然是不成立的，从 $1$ 就可以看出，分出来 $x$ 个 $1$ 后，还有 $2$ 个数，这两个数的和要是奇数，因为偶数加奇数才是奇数。

    所以一个数为偶数，一个数为偶数。两个数肯定是不一样的，异或和的序列肯定不是 $0$。

---

3. 最后一种是最简单的，如果 $n$ 大于 $m$ 显然是不成立的，因为所有的 $a_i \geq 1$，如果 $n$ 大于 $m$，数组和一定大于 $m$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int t,n,m;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
        if(n>m){
            cout<<"NO"<<endl;
            continue;
        }
        if(n&1){
            cout<<"YES"<<endl;
            for(int i=1;i<=n-1;i++){
                cout<<"1 ";
            }
            cout<<m-n+1<<endl;
            continue;
        }
        if(!(n&1)&&!(m&1)){
            cout<<"YES"<<endl;
            int ans=(m-n+2)>>1;
            for(int i=1;i<=n-2;i++){
                cout<<"1 ";
            }
            cout<<ans<<" "<<ans<<endl;
            continue;
        }
        if(!(n&1)&&(m&1)){
            cout<<"NO"<<endl;
            continue;
        }
	}
	return 0;
}
```
完结撒花~

---

## 作者：Brute_Force (赞：0)

### 思路
考虑以下情况：
- 当 $n>m$ 时，显然无解，无证自明。
- 当 $n$ 是奇数时，有解。证明：前 $n-1$ 项都是 $1$，最后一项是 $m-n+1$。
- 当 $n$ 和 $m$ 都是偶数时，有解。证明：前 $n-2$ 都是 $1$，后 $2$ 项都是 $\frac{m-n+2}{2}$。
- 当 $n$ 是偶数且 $m$ 是奇数时，无解。证明：$n$ 为偶数必满足 $\frac{m-n+2}{2}$ 为整数，但 $m$ 是奇数，根据奇偶性质可知，此条无法满足，所以无解。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T,n,m;
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        cin>>n>>m;
        if(n>m)cout<<"No\n";
        else if(n%2!=0)
        {
            cout<<"Yes\n";
            for(int j=1;j<n;j++)cout<<1<<' ';
            cout<<m-n+1<<'\n';
        }
        else if(m%2==0)
        {
            cout<<"Yes\n";
            for(int j=1;j<n-1;j++)cout<<1<<' ';
            cout<<(m-n+2)/2<<' '<<(m-n+2)/2<<'\n';
            
        }
        else cout<<"No\n";
        
    }
}
```

---

## 作者：王逸辰 (赞：0)

# CF1726B Mainak and Interesting Sequence 题解
## 思路
如何判断是否有趣？

- 当 $N$ 大于 $M$ 时，它是无趣的。

- 当 $N$ 是奇数时，它是有趣的，最后一项输出 $M-N+1$ 即可。

- 当 $N$ 不是奇数，$M$ 是偶数时，它是有趣的，最后两项输出 $(M-N+2)/2$ 和 $(M-N+2)/2$ 即可。

- 当不满足上述条件时，它是无趣的。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int NN=1e6+10;
int a[NN],T,N,M,ans;
int main(){
	cin>>T;
	while(T--){
		cin>>N>>M;
		if(N>M)
			puts("No");
		else if(N%2==1){
			puts("Yes");
			for(int i=1;i<N;i++) 
				cout<<"1 ";
			cout<<M-N+1<<endl;
		}
		else if(M%2==0){
			puts("Yes");
			for(int i=1;i<N-1;i++) 
				cout<<"1 ";
			cout<<(M-N+2)/2<<" "<<(M-N+2)/2<<endl;
		}
		else
			puts("No");
	}
	return 0;
}
``````

---

## 作者：Rookie_t (赞：0)

首先要判断怎样不是有趣的。

当 $n>m$ 时，不是有趣的。

还有，如果 $n$ 是奇数，有解，输出一个前 $n-1$ 项为 $1$，最后一项为 $m-n+1$ 的数列即可。

如果 $n$ 为偶数，可以分两种情况。

当 $m$ 为奇数时，那么无解。

当 $m$ 为偶数时，是有解的。输出前 $n-2$ 项为 $1$，后两项为 ${m-n+2}\over2$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m;
signed main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		if(n>m){
			cout<<"No"<<endl;
			return 0;
		} 
		if(n%2 == 1){
			cout<<"Yes"<<endl;
			for(int i = 1;i<n;i++){
				cout<<1<<' ';
			}
			cout<<m-n+1;
			return 0;
		}
		if(n%2 == 0){
			if(m%2 == 1){
				cout<<"No";
				return 0;
			}
			else{
				for(int i = 1;i<=n-2;i++){
					cout<<1<<' ';
				}
				cout<<(m-n+2)/2<<' '<<(m-n+2)/2;
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：Shimotsuki (赞：0)

题意：构造一个数列 $a$，使序列的和为 $m$，且要求对于任意 $a_i(1 \le i \le n)$，记序列中严格小于 $a_i$ 的数的异或和为 $p_i$，$p_1=p_2=...=p_{n-1}=p_n=0$。

首先，因为偶数个相同的数的异或和为 $0$，所以，可以将序列中的偶数个数设为 $1$，所以接下来只需要分讨 $n$ 和 $m$ 的奇偶性。如果 $n$ 和 $m$ 的奇偶性相同，那就存在解：如果都是奇数，构造 $n-1$ 个 $1$，剩下一位填上 $m-(n-1)$；如果都是偶数，就构造 $n-2$ 个 $1$，因为偶数减偶数还是偶数，所以剩下两位填 $(m-(n-2)) \div 2$。如果 $n$ 是奇数，$m$ 是偶数，也存在构造方案，填 $n-1$ 个 $1$，剩下一位填 $m-(n-1)$；如果 $n$ 是偶数，$m$ 是奇数，那么无解，因为填完 $n-2$ 个 $1$ 后，$m-(n-2)$ 是奇数，无法平分，所以无解。

注意判断 $n > m$ 的情况。

```cpp
inline void solve(){
		int n,m;
		cin>>n>>m;
		if(n>m){
			cout<<"No"<<'\n';
			return;
		} 
		if((n&1)==(m&1)){
			cout<<"Yes"<<'\n';
			if(n&1){
				for(int i=1;i<n;++i) cout<<1<<' ';
				cout<<m-(n-1)<<'\n';
				return;
			}
			else{
				for(int i=1;i<=n-2;++i) cout<<1<<' ';
				cout<<(m-(n-2))/2<<' '<<(m-(n-2))/2<<'\n';
				return;
			}
		}
		else{
			if(n&1){
				cout<<"Yes"<<'\n';
				for(int i=1;i<n;++i) cout<<1<<' ';
				cout<<m-(n-1)<<'\n';
				return;
			}
			else cout<<"No"<<'\n';
		}
	}
```


---

## 作者：Zigh_Wang (赞：0)

推荐[博客](https://blog.csdn.net/YunYuanWang/article/details/126757806?spm=1001.2014.3001.5501)内食用哦

# 题面

> ### 题目大意
> 
> 认定一个长度为 $n$ 的序列 $a$ 是有趣的有且仅当满足以下条件：
> 
> - 对于**任意**一个整数 $a_i$，所有**严格小于**它的数的异或和为 $0$。( 假定所有满足条件的数为 $b_j$，则异或和为 $0$ 表示 $b_1 \; xor \; b_2 \; xor \; \dots \; xor \; b_j = 0$，xor 表示按位异或 )
> 
> 请求出满足 $\sum_{i = 1}^n a_i = m$ 的长度为 $n$ 有趣的序列。 若有多种构造方式，则任意输出一种即可。
> 
> 例如：$[1,3,2,3,1,2,3] , [4,4,4,4] , [25]$ 是有趣的，而 $[1,2,3,4] \; (p_2 = 1
> \neq 0), \; [4,1,1,2,4] \; (p_4 = 1 \; xor \; 1 \; xor \; 2 = 2 \neq
> 0), \; [29,30,30] \; (p_{30} = 29 \neq 0)$不是有趣的。( 其中 $p_i$ 表示题目要求中的异或和
> )。
> 
> ### 输入格式
> 
> 第一行一个整数 $T \; (1 \leqslant T \leqslant 10^5)$ ，表示测试样例组数。
> 
> 对于每组测试样例，包含一行两个整数 $n \; (1 \leqslant n \leqslant 10^5)$ 和 $m \; (1
> \leqslant m \leqslant 10^9)$，含义见题目。
> 
> 数据保证 $\sum n \leqslant 10^5$。
> 
> ### 输出格式
> 
> 对于每组测试样例，如果第一行为一个字符串。如果存在满足条件的有趣的序列则输出Yes ，否则输出 No。
> 
> 如果你的输出是 Yes，则接下来的一行包含 $n$ 个数，表示你构造的序列，否则不输出这一行。
> 
> $Translated \; by \; Zigh$

# 分析
首先，如果 $m < n$ 则显然直接输出 No。

其次，如果 $n | m$ ，那么显然直接输出 $n$ 个 $\frac{m}{n}$。

剩下的情况我们分四种情况讨论。

1. 由于要求异或和为 $0$ ，所以所有小于最大数的数都要成对出现，所以当 $m$ 为奇数而 $n$ 为偶数时直接输出 No，因为无论如何都不能保证除去最大数后都成对出现。
2. 而$m$ 为奇数而 $n$ 也为奇数时，我们可以直接输出 $n - 1$ 个 $1$ 和一个 $m - (n - 1)$ 即可。
3. $m$ 为偶数而 $n$ 为奇数时，我们同样可以直接输出 $n - 1$ 个 $1$ 和一个 $m - (n - 1)$ 。
4.  $m$ 为偶数而 $n$ 也为偶数时，我们可以直接输出 $n - 2$ 个 $1$ 和两个 $\frac{m - (n - 2)}{2}$，这样就可以保证除去最大数都成对出现 。

# 代码
```cpp
//省略快读和头文件
int T;
int n, m;
int a[MAXN];

int main()
{
	T = inpt();
	while(T--) {
		n = inpt(), m = inpt();
		if(m < n) {
			puts("No");
			continue;
		}
		if(m % n == 0) {
			puts("Yes");
			for(int i = 1; i <= n; i++)
				printf("%d ", m / n);
			puts("");
			continue;
		}
		if(m & 1) {
			if((n & 1) == 0) {
				puts("No");
				continue;
			}else {
				puts("Yes");
				for(int i = 1; i <= n - 1; ++i, --m)
					printf("1 ");
				printf("%d\n", m);
				continue;
			}
		}else {
			if((n & 1) == 0) {
				puts("Yes");
				int tmp = (m - (n - 2)) >> 1;
				for(int i = 1; i <= n - 2; ++i)
					printf("1 ");
				printf("%d %d\n", tmp, tmp);
				continue;
			}else {
				puts("Yes");
				for(int i = 1; i <= n - 1; ++i, --m)
					printf("1 ");
				printf("%d\n", m);
				continue;
			}
		}
		
	}

 	return 0;
}
```

最后再来猜一猜题目翻译里的 $Zigh$ 是谁呢Qwq

---

## 作者：菲斯斯夫斯基 (赞：0)

## CF1726B Mainak and Interesting Sequence 题解

更新：2023.9.9 感谢指正细节错误。

题意就不解释了，还是很好理解的。

这是一道构造题，因为看到有 Special Judge，所以肯定会有巧妙的构造方法，~~并且样例大部分都是迷惑你的~~。

因为题目要求异或和，异或有个很重要的性质：$x \operatorname{xor} x=0$。

题目要求异或和为零，所以显然离不开这个性质。

思考：是要**严格小于**的数异或和为零，所以如果没有**严格小于**当前的数就好了。那么就要所有数都相等，即 $m$ 整除 $n$。

这样太麻烦了，所有肯定不是正解。换个方向想，那么是不是**只有一个数不同也行**（当然这个数要大于其它数）。

所以我们不难想到前面 $n-1$ 个数都可以是 $1$，然后第 $n$ 个数是 $n-m+1$。然后想都没想，直接交，发现连样例都没过！

检查，发现当 $n-1$ 为奇数时，前 $n-1$ 个数的异或和会多出 $1$。这个很容易处理，只要把最后两个数变成相同的数即可。

问题又来了，$m-n+2$ 为奇数的时候无法除尽，这个时候就是无解了，因为无法使得最大的数相同。

特别的是，当 $m<n$ 的时候也是无解，因为连每一位都是 $1$ 都无法满足。

为了方便代码的编写，于是我们可以将 $n$ 和 $m$ 分奇偶讨论，原理跟上面的是一样的。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		if(m<n)//特判 
		{
			cout<<"No\n";
			continue;
		}
		if(n%2==1)//n为奇数 
		{
			cout<<"Yes\n";
			for(int i=1;i<n;i++)
				cout<<1<<' ';
			cout<<m-n+1<<endl;
		}
		else //n为偶数 
		{
			if(m%2==0)//m为偶数 
			{
				cout<<"Yes\n";
				for(int i=1;i<=n-2;i++)
					cout<<1<<' ';
				int k=m-n+2;
				cout<<k/2<<' '<<k/2<<endl;
			}
			else cout<<"No\n";//m为奇数无解 
		}
	} 
	return 0;
}
```

---

