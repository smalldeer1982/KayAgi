# [ICPC 2020 Nanjing R] K Co-prime Permutation

## 题目描述

给定两个整数 $n$ 和 $k$，构造一个 $1 \sim n$ 的排列 $p_1,p_2,\cdots,p_n$，使得存在 $k$ 个整数 $i$ 满足 $1 \le i \le n$ 且 $\text{gcd}(p_i,i)=1$。

$\text{gcd}(x,y)$ 表示 $x$ 和 $y$ 的最大公约数。

## 样例 #1

### 输入

```
5 3```

### 输出

```
1 4 5 2 3```

## 样例 #2

### 输入

```
1 0```

### 输出

```
-1```

# 题解

## 作者：Larryyu (赞：2)

## _Description_

给定 $n$ 和 $k$，求一个 $n$ 的排列 $p_1,p_2\dots p_n$，使得有恰好有 $k$ 个 $i$，满足 $\gcd(i,p_i)=1$。

## _Solution_

前置芝士：[最大公约数 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/math/number-theory/gcd/#过程)

我们知道：$\gcd(a,b)=\gcd(b,a\bmod b)$

因此当 $a=b+1$ 时，$\gcd(a,b)=\gcd(b,a\bmod b)=\gcd(b,1)=1$。

所以对于任意一对相邻的数，它们的最大公约数为 $1$。

那我们在 $i\in [1,k-1]$ 的位置上放 $i+1$，在 $k$ 的位置放 $1$，在 $i\in[k+1,n]$ 的位置上放 $i$，就能满足条件。

对于 $k=0$ 的特殊情况，我们输出 ```-1``` 即可。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	if(k==0) cout<<-1<<endl;
	else {
		for(int i=1;i<=k;i++){
			cout<<i%k+1<<" ";
		}
		for(int i=k+1;i<=n;i++){
			cout<<i<<" ";
		}
	}
	return 0;
	
}
```



---

## 作者：hjqhs (赞：2)

游戏发生在一个被称作“提瓦特”的幻想世界，在这里，被神选中的人将被授予“神之眼”，导引元素之力。  
NJCPC 的签到题。  
[link](https://codeforces.com/gym/102992/problem/K)。  
首先特判 $k=0$，输出 `-1` 即可。  
考虑 $\gcd$ 的性质：$\gcd(x,x-1)=1,\gcd(1,x)=1$，所以前 $k$ 个格子错位一下，其他不变即可。  
[AC code](https://codeforces.com/gym/102992/submission/222674222)。
```cpp
#include<bits/stdc++.h>
// #define int long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
#define pv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
#define mp make_pair
#define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=100005;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9'){
    if(ch=='-')f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<3)+(x<<1)+(ch^48);
    ch=getchar();
  }
  return x*f;
}
int n,k;
void solve(){
  cin>>n>>k;
  if(k==0){cout<<-1;}
  else{
    for(int i=2;i<=k;++i){
      cout<<i<<' ';
    }
    cout<<1<<' ';
    for(int i=k+1;i<=n;++i){
      cout<<i<<' ';
    }
  }
}
signed main(){
  // freopen(,,stdin);
  // freopen(,,stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}
```

---

## 作者：Ryan_Yu (赞：1)

这种解法有点复杂，但是应该是比较好理解的一种解法。

题意：给定整数 $n,k$，构造出含有 $n$ 个各不相同的正整数的数列 $p_1,p_2,⋯,p_n$，要求其中恰好有 $k$ 个元素满足 $\operatorname{gcd(p_i,i)=1}$，若无法构造输出 $−1$。

注：本题有多种答案。

由于有多种答案，所以把相邻两个数调换一下就会得到两个与索引互质的数。

所以开始令 $a_1,a_2,\cdot\cdot \cdot,a_n$ 为其索引。

这时候会发现多了一个 $\operatorname{gcd(a_1,1)=1}$。

故可以根据 $k$ 的奇偶性判断。

1. $k$ 为偶数，则：$\operatorname{swap(a_1,a_n)}$。

2. $k$ 为奇数，则：不需要调换，因为 $\operatorname{gcd(a_1,1)=1}$。

所以就会无意间多一个。

最后 $\operatorname{swap\ \left\lfloor\dfrac{n}{2}\right\rfloor}-1$ 次就行了。

当然，注意 $k=0$ 时无解，输出 $-1$。

$\operatorname{Code:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int a[maxn],n,k,cnt;
int main()
{
	cin>>n>>k;
	if(k==0)
		{
			cout<<"-1";
			return 0;
		}
	for(int i=1; i<=n; i++)
		a[i]=i;
	if(k%2==1)
		{
			for(int i=2; i<=n; i=i+2)
				{
					if(cnt==(k-1)/2)
						break;
					cnt++;
					swap(a[i],a[i+1]);
				}
		}
	else
		{
			swap(a[1],a[n]);
			for(int i=2; ; i=i+2)
				{
					if(cnt==(k-1)/2)
						break;
					cnt++;
					swap(a[i],a[i+1]);
				}
		}
	for(int i=1; i<n; i++)
		cout<<a[i]<<" ";
	cout<<a[n];
	return 0;
}
```

---

## 作者：WhitD (赞：1)

## 题目大意
给定整数 $n,k$，构造出含有 $n$ 个各不相同的正整数的数列 $p_1,p_2,⋯,p_n$，要求其中恰好有 $k$ 个元素满足 $\gcd(p_i,i)=1$，若无法构造输出 $-1$。
## 思路
我们知道：对于任意正整数 $x$，$\gcd(x,x+1)=1$，任何数与 $1$ 的 $\gcd$ 一定是 $1$。

那就可以令 $p_1=k,p_2=1,p_3=2,⋯,p_k=k-1$，剩下的的就令 $p_{k+1}=k+1,⋯,p_n=n$，这样可以保证构造出的数列一定合法，显然当 $k=0$ 的时候无法构造，特判就可以了。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
	cin>>n>>k;
	if(k==0)
	{
		cout<<-1;
		return 0;
	}
	cout<<k<<" ";
	for(int i=1;i<k;i++)
		cout<<i<<" ";
	for(int i=k+1;i<=n;i++)
		cout<<i<<" ";
	return 0;
}
```


---

## 作者：skyskyCCC (赞：1)

## 前言。
一道基础的签到题。
## 分析。
题意：请您构造一个长度为 $n$ 的序列，使得序列中的 $p_i$ 使得 $\gcd( p_i,i) = 1$ 成立，同时要求满足要求的 $p_i$ 的数目严格等于 $k$ 并输出这个序列。

其实通俗来讲，就是使得该排列中的 $k$ 个 $p_i$ 的数目与其下标互质，并且要求该序列中元素个数为 $n$ 个，同时 $p_i$ 要从 $1$ 到 $n$ 中选择。

因为存在 $n$ 最小等于 $1$ 的情况，所以序列中必定有 $1$ 的存在，并且当它在第一位时 $\gcd(1,1) = 1$ 必然满足题意，故有 $k \neq 0$ 必然成立，在开始时考虑上它即可。

而 $\gcd(x,x+1) = 1$ 必然成立，故我们只需要将第一项后面的数从 $2$ 到 $n$ 排列并依次两两互换，就可以每次互换增加 $2$ 直到等于 $k$ 为止。

当 $k$ 为奇数时令 $p_1=1$ 然后排列后面的数并两两互换即可。

若 $k$ 为偶数时直接进行两两互换即可。

注意输出的最后不能有空格。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
int n,k;
int main(){
	cin>>n>>k;
	if(k==0){
		cout<<"-1";
		return 0;
	}
	if(k%2==0){//接下来的if语句都是判断最后的空格的。
		for (int i=1;i<=k/2;i++){//因为每次交换增加2，所以只要交换k/2次就可以到达k。
			if(k+1>n&&i==k/2) cout<<i*2<<" "<<i*2-1; 
			else cout<<i*2<<" "<<i*2-1<<" ";
		}
		for (int i=k+1;i<=n;i++){
			if(i==n) cout<<i;
			else cout<<i<<" ";
		}
		return 0;
	}
	cout<<"1 ";//情况1
	for (int i=2;i<=k;i+=2){
		if(k+1>n&&i==k/2) cout<<i+1<<" "<<i;
		else cout<<i+1<<" "<<i<<" ";
	}
	for (int i=k+1;i<=n;i++){
		if(i==n) cout<<i;
		else cout<<i<<" ";
	}
	return 0;
}
```
但是我们发现，我们其实还有另一种构造方法。

我们可以先从 $2$ 输出直到输出到 $k$ 为止，这时每个 $p_i$ 都满足 $\gcd(p_i,i) = 1$ 的要求，同时构造了 $k-1$ 个满足题意的序列元素。

然后输出 $1$ 使 $\gcd(1,k)=1$ 满足题意同时构造出了 $k$ 个满足题意的元素，再将还剩下的数在它后面输出即可，因为在 $1$ 后面，每个 $p_i$ 的下标也是 $p_i$ 故 $\gcd(p_i,i) = p_i$ 不满足题意。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,k;
int main(){
    cin>>n>>k;
    if(k==0){    
        cout<<"-1";
        return 0;
    }
    for(int i=2;i<=k;i++){
    	cout<<i<<" ";
    }
    cout<<"1 ";
    for(int i=k+1;i<=n;i++){
    	if(i==n) cout<<i;
    	else cout<<i<<" ";
    }
    return 0;
}
```
经测试，两份代码都能通过本题。
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：sevenki (赞：1)

# 题意

给出 $n$ 和 $k$，构造一个 $1$ 到 $n$ 的排列 $p$ 使得排列中有且只有 $k$ 个数满足 $\gcd{(p_i,i)}=1$。（即 $p_i$ 与 $i$ **互质**。）如果没有符合条件的排列则输出 $-1$。

# 思路

小学我们都学过：相邻的两个正整数互质。
 具体证明如下：

假设 $a$ 是 $b$ 的倍数。那么，最小的比 $a$ 大的 $b$ 的倍数一定比 $a$ 大 $b$。

而 $a+1$ 只比 $a$ 大了 $1$，所以，$\gcd{(a,a+1)}\le 1$。所以 $a$ 与 $a+1$ 互质。

（部分参考了[这个问题下的回答](https://www.zhihu.com/question/28214423)）

那么了解了以上，我们就可以这样构造了：

首先，对于前 $k-1$ 个数，令 $p_i\gets i+1$。这样我们就有了 $k-1$ 个数满足题目条件。

然后，对于第 $k$ 个数，令 $p_k\gets 1$。

最后，容易发现，此时刚好使用了 $1$ 到 $k$ 中的数字。我们只需要令剩下的 $p_i\gets i$ 即可，此时剩下的 $\gcd{(p_i,i)}=i$，都不满足 $\gcd{(p_i,i)}=1$。

通过以上方法即可构造出满足题意的排列。

考虑无解情况。

容易发现，对于任意的排列 $p$，排列中总存在 $1$ 这个数，而所对应的 $p_i$ 满足 $\gcd{(p_i,i)}=1$，即排列中总存在至少 $1$ 个数满足 $\gcd{(p_i,i)}=1$。所以，$k=0$ 的情况无解。输出 `-1`。

至此是本题的所有思路。

# 代码

思路有了，代码就很简单了：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int main() {
  scanf("%d%d", &n, &k);
  if (k < 1) {
    printf("-1");
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    if (i < k)
      printf("%d", i + 1);
    else if (i == k) {
      printf("1");
    } else {
      printf("%d", i);
    }
    if (i < n) putchar(' ');
  }
  return 0;
}
```



---

## 作者：_5t0_0r2_ (赞：1)

## 题意：

构造一个长为 $n$ 的排列，使其**恰好**有 $k$ 个数跟其下标互质。

## 分析：
因为 $\gcd(x,x + 1) = 1$，所以我们可以让前 $k - 1$ 个数，第 $i$ 个数为 $i + 1$，第 $k$ 个数为 $1$（$1$ 跟任何数都互质），其余数都设为下标即可。

特别的，当 $k$ 等于 $0$ 时，是无解的，因为 $1$ 跟任何数都互质。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
	scanf("%d%d", &n, &k);
	if(k == 0){
		printf("-1\n");
		return 0;
	}
	if(k == 1){
		for(int i = 1;i <= n;i++){
			printf("%d", i);
			if(i != n)
				printf(" ");
		}
		printf("\n");
		return 0;
	}
	int i;
	for(i = 1;i <= k - 1;i++){
		printf("%d ",i + 1);
	}
	i++;
	printf("1");
	if(i != n)
		printf(" ");
	for(;i <= n;i++){
		printf("%d", i);
		if(i != n)
			printf(" ");
	}
	printf("\n");
	return 0;
}
```


---

## 作者：Vct14 (赞：0)

若 $k=0$，则一定无解，输出 `-1`。

我们知道 $\gcd(1,x)=1$，且 $\gcd(x,x+1)=1$，还有 $\gcd(x,x)=x$，所以对于 互质的那 $k$ 个数，对于 $i$ 满足 $2\leqslant i\leqslant k$，我们可以让 $g_i=i-1$；当然，在 $i=1$ 时，我们让 $g_i$ 等于 $k$ 就可以了。而剩下的 $n-k$ 个数，我们使 $g_i=i$，则它们一定不互质。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,k;
	cin>>n>>k;
	if(k==0) cout<<-1;
	else{
		cout<<k<<" ";
		for(int i=2; i<=k; i++) cout<<i-1<<" "; 
		for(int i=k+1; i<=n; i++) cout<<i<<" ";
	} 
	return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：0)

真正的签到题。

显然 $x$ 和 $x-1$ 互质，$1$ 和任何数互质，任何数和它本身不互质

那么直接对每一项进行两两交换就行了。特别的，如果 $k$ 是奇数，那么让结果的第一项为 $1$，后面的依旧两两交换。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int n, k; cin >> n >> k;
	if(!k) return (cout << -1), 0;
	cout << k;
	for(int i = 1;		i < k ; ++ i) cout << ' ' << i;
	for(int i = k + 1;	i <= n; ++ i) cout << ' ' << i;
}
```

---

## 作者：lraM41 (赞：0)

小清新构造。

无解： $k=0$，因为排列中的 $1$ 放到哪里最大公约数都是 $1$。

思路：分类讨论 $k$ 的奇偶性。
- $k$ 为偶数：由于每次交换相邻的两个数都能保证能产生两个  ```gcd(i,p[i])=1```，所以只需要交换 $\tfrac{k}{2}$ 次即可，剩下的数只需要输出 $i$ 就行了。

- $k$ 为奇数：与 $k$ 为偶数时类似，排列的第一个数为 $1$，接着从 $2$ 开始交换 $\tfrac{k}{2}$ 次即可，剩下的数还是输出 $i$。


```
#include<bits/stdc++.h> 
using namespace std; 
int n,k;
int main() { 
   cin>>n>>k;
   if(!k) return puts("-1"),0;//无解。
   if(k%2){
      cout<<1<<' ';
      for(int i=1;i*2<=k;i++) cout<<i*2+1<<' '<<i*2<<' ';//交换。
      for(int i=k+1;i<=n;i++) cout<<i<<' ';//剩下的数不用交换。
   }else{
      for(int i=1;i*2<=k;i++) cout<<i*2<<' '<<i*2-1<<' ';//交换。
      for(int i=k+1;i<=n;i++) cout<<i<<' ';//剩下的数不用交换。
   }
   return 0; 
}

---

## 作者：XBaiC (赞：0)

### 题意

给定 $n,k$，构造一个 $1\sim n$ 的全排列 $a$。保证有 $k$ 个数满足 $\gcd(a_i,i)=1$。

### 思路

就是构造题。只要 $\gcd(i-1,i)=1$ 就行。

入门题难度。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd( int x , int y )
{
    return ( y > 0 ) ? gcd( y , x % y ) : x;
}
int main()
{
    int n , k;
    cin >> n >> k;
    if( !k )
    {
        puts( "-1" );
        return 0;
    }
    cout << k << " ";
    for( int i = 1;i < k; i++ ) 
    {
        cout << i << " ";
    }
    for( int i = k + 1; i <= n; i++ ) 
    {
        cout << i << " ";
    }
    return 0;
}
```


---

## 作者：lemon_qwq (赞：0)

签到题。

$x$ 和 $x-1$ 必定互质，$x$ 和 $1$ 也必定互质。

先输出前 $2\sim k-1$ 的数，然后再输出 $1$，最后按顺序输出没输出的数。

另外，只要 $k=0$ 就肯定无解。

代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,k,a;
int main(){
	cin>>n>>k;
	if(k){
		for(int i=1;i<k;i++)cout<<i+1<<" ";
		cout<<1<<" ";
		for(int i=k+1;i<=n;i++){
			cout<<i<<" ";
		}
		cout<<endl;
	}else{
		cout<<-1<<endl;
	}
	return 0;
}
```
完结撒花！

---

## 作者：Shunpower (赞：0)

比较简单的构造题。

## 题意

构造一个长度为 $n$ 的排列 $p$，满足存在恰好 $k$ 个 $i(1\leqslant i\leqslant n)$ 使得 $\gcd(p_i,i)=1$。

## 思路

首先可以想到互质的两种比较特殊的情况：

1. 两个相邻的奇数互质。

2. 两个相邻的数互质。

你发现这些性质都和相邻有关，自然想到交换相邻。这样做一次可以增加 $2$ 个满足条件的位置。

考虑使用性质 $2$。如果从左往右依次交换 $(1,2)(3,4)\cdots $，可以构造出非零偶数个互质位置。

奇数可以考虑保留 $1$，从左往右依次交换 $(2,3)(4,5)\cdots$，于是构造出了奇数个互质位置。

然后可以发现如果想要 $k=0$，因为 $1$ 的存在，所以一定有一个位置是互质的，因此永远不可能做到 $k=0$。

于是 $k$ 是奇数、非零偶数都构造出来了，$k=0$ 时无解。

---

