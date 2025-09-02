# [AGC024C] Sequence Growing Easy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc024/tasks/agc024_c

長さ $ N $ の数列 $ X $ があり、最初はすべての要素が $ 0 $ です。$ X $ の $ i $ 項目を $ X_i $ で表すことにします。

長さ $ N $ の数列 $ A $ が与えられます。$ A $ の $ i $ 項目は $ A_i $ です。 以下の操作を繰り返すことで $ X $ を $ A $ と等しくすることができるかどうか判定し、できるなら最小の操作回数を求めてください。

- $ 1\leq\ i\leq\ N-1 $ なる整数 $ i $ を選ぶ。$ X_{i+1} $ の値を $ X_i $ の値に $ 1 $ を足したもので置き換える。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9(1\leq\ i\leq\ N) $
- 入力はすべて整数である

### Sample Explanation 1

次のようにして、$ X $ を $ A $ と等しくすることができます。 - $ i=2 $ に対して操作する。$ X $ は $ (0,0,1,0) $ となる。 - $ i=1 $ に対して操作する。$ X $ は $ (0,1,1,0) $ となる。 - $ i=3 $ に対して操作する。$ X $ は $ (0,1,1,2) $ となる。

## 样例 #1

### 输入

```
4
0
1
1
2```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1
2
1```

### 输出

```
-1```

## 样例 #3

### 输入

```
9
0
1
1
0
1
2
2
1
2```

### 输出

```
8```

# 题解

## 作者：ytb2024 (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc024_c)

附：[AT原题目](https://atcoder.jp/contests/agc024/tasks/agc024_c)

题意：最初有一个每位为 $0$，长度为 $n$ 的 $a$ 数组。每次可以选一个 $i$ ( $2$ $\leq$ $i$  $\leq$ $n$ )，$a_i$ $\gets$ $a_{i-1}+1$。最终，要使 $a$  数组等于 $A$ 数组。输出最小操作步数，不行则输出 $-1$。

我们先来考虑 $-1$ 的情况。

- 当 $A_1$ 不为 $0$ 时，由于 $a_1$ 无法改变值，所以此种情况为 $-1$。
- 当 $A_i$ $-$ $A_{i-1}$ $>$ $1$ 时，由于 $a_i$ 最多比 $a_{i-1}$ 大 $1$，所以此种情况为 $-1$。

```cpp
if(a[1]!=0){cout<<-1;return;}
for(int i=2;i<=n;i++)if(a[i]>=a[i-1]+2){cout<<-1;return;}
```

如果不是 $-1$ 的情况，我们考虑对 $A$ 进行遍历( $2$ $\leq$ $i$  $\leq$ $n$ )。

- 当 $A_i$ $=$ $A_{i-1}$ $+$ $1$ 时，此时非常理想，可以直接由前一位转移，代价为 $1$。
- 当 $A_i$ $\leq$ $A_{i-1}$ 时，有一个显然的结论：$A_i$ $<$ $i$。所以每一个这个条件的数可以从 $a_{i-A_i+1}$ 开始累加，最终使 $a_i$ 成为 $A_i$，代价为 $A_i$。

这里多说一句，整个序列的处理顺序应为倒着处理 $A_i$ $\leq$ $A_{i-1}$ 的情况后，再正着处理 $A_i$ $=$ $A_{i-1}$ $+$ $1$ 的情况。
```cpp
for(int i=2;i<=n;i++)if(a[i]==a[i-1]+1)ans++;else ans+=a[i];
cout<<ans;
```
最后输出 $ans$ 或者 $-1$ 就可以 AC 啦，记得要用 long long 哦。

## AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200001],ans;
inline void init()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
}
inline void solve()
{
	if(a[1]!=0){cout<<-1;return;}
	for(int i=2;i<=n;i++)if(a[i]>=a[i-1]+2){cout<<-1;return;}
	for(int i=2;i<=n;i++)if(a[i]==a[i-1]+1)ans++;else ans+=a[i];
    cout<<ans;
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	init(),solve();
	return 0;
}
```

---

## 作者：FFTotoro (赞：4)

这里提供一种比较新奇的做法。

做这种题首先要特判：如果 $x_1>0$，那么肯定无解（因为没有 $x_0$ 供给 $x_1$ 变换）。如果相邻两数 $a_{i+1}-a_{i}>1$，那么也无解——因为题目中说了 $x_{i+1}$ 若要变成非 0 的 $a_{i+1}$，必须使用操作 $x_{i+1}=x_i+1$，显然做不到。

特判完就可以开始思考正解。我们先从样例 1 出发。

样例输入 #1：

```
4
0
1
1
2
```

该如何操作才能使 $x$ 变为这一串序列呢？

我们先这么操作： $x_3=x_2+1=1$；

接着：$x_2=x_1+1=1$；

最后：$x_4=x_3+1=2$。

可以观察到，当 $a_{i+1}-a_i=1$ 时，我们先变 $x_i$，再变 $x_{i+1}$ 时就只需一次操作。

但如果 $a_{i+1}\le a_i$ 呢？很显然，$x_{i+1}$ 的变换依赖于 $x_i$ 的变换，$x_i$ 的变换又依赖于 $x_{i-1}$ 的变换……直到扫描到某个 $a_j$。为满足 $x_{i+1}=a_{i+1}$ 需要先将 $x_j$ 变换为 $a_{i+1}-(i-j)-1$，然后 $x_{j+1}=x_j+1$，$x_{j+2}=x_{j+1}+1$……运用这种思想不断往下递归，一共需要 $x_{i+1}$ 次操作。

放代码：

```cpp
#include<iostream>
#include<vector>
#define int long long
using namespace std;
signed main(){
    int n,c=0; cin>>n;
    vector<int> v(n);
    for(auto &i:v)cin>>i; // C++11 福利——auto，节省码量
    if(v[0]){cout<<-1<<endl; return 0;} // 如果第一个数就不为 0 那么肯定无解
    for(int i=1;i<n;i++){
        if(v[i]>v[i-1]+1){cout<<-1<<endl; return 0;} // 无解的第二种情况
        c+=v[i]>v[i-1]?1:v[i]; // 分类讨论
    }
    cout<<c<<endl;
    return 0;
}
```

---

## 作者：gyh20 (赞：4)

在整个过程中，同一个位置的 $x_i$ 是不降的。

考虑对于一个位置我们需要进行怎么样的操作。

假设当前位置为 $i$，那么从 $i-a_i+1$ 到 $i$ 轮流执行操作即可。

至于操作的顺序，我们保证中途到达每个位置的数不降即可。

无解即为无法找到一个开始位置即 $i-a_i\leq 0$ 或者之中存在某一个位置的值小于了它在过程中会达到的值，简单讨论发现即为 $a_i>a_{i-1}+1$。

对于这个位置，我们不一定要从 $i-a_i+1$ 开始执行操作。

我们发现，可能有很多 $i-a_i+1$ 在同一个位置，中间的很多操作也是在做同样的操作，具体的，如果 $i<j,j-a_j+1=i-a_i+1$ 那么 $a_j$ 可以直接继承 $a_i$ 的值从 $i+1$ 开始操作，找到上一个 $i-a_i=j-a_j$ 的位置即可，时间复杂度 $O(n)$。

```cpp
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#define re register
using namespace std;
const int Mxdt=200000;	//单次大小 
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	re int t=0;re char v=gc();
	while(v<'0')v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return t;
}
int pos,n,a[200002],L[200002];
long long ans;
int main(){
	n=read(),a[0]=-1;
	for(re int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]>a[i-1]+1)return puts("-1"),0;
		if(a[i])ans+=i-L[a[i]-i+n];
		L[0-i+n]=L[a[i]-i+n]=i;
	}
	printf("%lld",ans);
}


```


---

## 作者：zzwdsj (赞：1)

### 思路
先来看看无解的情况。
+ 当 $a_1\not=1$ 时无解。因为选择任何一个 $i(1\le i<N)$ 进行操作都影响不到 $a_1$，$a_1$ 只能是初始值 $0$。
+ 当 $a_{i+1}>a_i+1(1\le i <N)$ 时无解。因为只有选择 $i$ 进行操作才能影响到 $a_{i+1}$，$a_{i+1}$ 最大也只能是 $a_i+1$。

当有解时，对于每个数 $a_i$ 分两种情况讨论。
+ $a_i-a_{i-1}=1$ 答案增加 $1$。因为只需要选择 $i-1$ 进行一次操作就行。
+ $a_1-a_{i-1}=0$ 答案增加 $a_i$。因为 $a_{i-1}>a_i+1(1\le i <N)$ 且 $a_1=0$。所以 $a_i<i(1\le i\le N)$。此时可以依次选择 $i-a_i,i-a_i+2,...,i-a_i+a_i-1$ 进行操作，共 $a_i$ 次。
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
long long ans;//不开 long long 见祖宗。
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(a[1]){cout<<-1;return 0;}
	for(int i=1;i<=n;ans+=(a[i]==a[i-1]+1?1LL:1LL*a[i]),i++)if(a[i]>a[i-1]+1){cout<<-1;return 0;}
	cout<<ans;
	return 0;
}
```

---

## 作者：Steadywelkin (赞：1)

### 题意

有两个长度为 $n$ 的序列 $a,x$ ，给定序列 $a$ ，$x$ 初始全部为 $0$ ，每次可以进行如下操作： $x_i=x_{i-1}+1$，询问需要进行几次操作才可以将 $x$ 转为 $a$，如果不可以就输出 $-1$ 。

### 思路

因为每一次操作只能增加而不能减少，所以必须要保证 $a$ 是单调不下降的，同时由于每一次操作只能增加 $1$ ，所以 $a_i$ 不可能大于 $i$ ，这是对于无解的特判。

对于有解的情况只要判断这个位置对于前一个变化了没有，最终结果取加和即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <ctime>
#include <algorithm>
using namespace std;
typedef long long ll;

inline ll read()
{
	ll a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

const ll mod=1e9+7;
const ll N=2e5+5;
ll a[N],b[N],n,m,ans;

signed main()
{
	n=read();
	for(ll i=1;i<=n;i++)
	{
		a[i]=read();
		b[i]=i-a[i];
		if(a[i]-a[i-1]>1||b[i]<=0)
		{
			puts("-1");
			return 0;
		}	
	}	
	for(ll i=n;i>0;i--)
	{
		if(i!=n&&b[i]==b[i+1])continue;
		ans+=a[i];
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Harp_Skier (赞：0)

做了好久，可能超过半小时。

看样子就是手玩题目，先手玩一下试试。

玩了 $1,2,3$ 到 $1,1,2,2,3,3$ 感觉差不多会了，就是全部加起来，然后 $a_i \leq a_{i+1}$ 的时候把 $a_i$ 从答案里面减去。这是找到的规律，发现玩错了几次，然后感性证明了一下：

首先，从空的数组到 $1,2 \dots n$ 一定只用 $n$ 次。我们考虑从后往前做，当 $a_i>a_{i+1}$ 的时候我们重新分一个段，对于每一段，我们发现它们是互不干扰的。

发现 $1,1,2,2,3,3$ 的时候，先变成 $0,0,1,2,3,3$ 是最快的，要 $6$ 次，然后发现这里的分解处的 $2$ 已经被写好了。也就是，连续的一些 $n$ 在构造出来之前，一定需要一个 $n-1$ 在上一个位置，这就能解释为什么要把分界处的 $a_i$ 减出答案。

再发现 $1,2,\dots n,n,n,n$ 这个东西实现的最小次数是 $n$ 乘上 $n$ 出现次数的。那我们就可以得到每一段的答案。

每一段是互不干扰的证明是容易的，我们发现每一段一定形如 $1 \dots ,1,2 \dots ,2 , \dots , n , \dots n $ 的，那最后一定是 $1$ ，所以当我们执行最优策略的时候，从后向前做，一定不会存在靠后的一个段影响前一个的情况。

这样就可以证明刚刚统计答案的方法是对的。

然后是判无解，显然地，我们发现其实终态相邻两项的差不会大于 $1$ 。

发现 $a_1$ 一定为 $0$ ，再发现，如果存在一个数 $x$ ，他的前面一定出现过所有 $y \leq x$ ，但是实际上上面两条是这一条的充要条件。

所以直接算答案就好了。

~~ 判无解WA了几发 ~~

---

## 作者：1zhangziheng2023 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_agc024_c)

### 题目大意
给定 $n$ 和一个长度为 $n$ 的序列 $a$，现在你有一个每一项都是 $0$ 的序列 $x$，现在有一种操作：

$x_{i+1} \gets x_i+1 (1 \le i \le n)$

求最少的操作次数使 $a_i = x_i$。

### 思路
先看满足什么情况无解。

- $a_1 \ne 0$。很显然，因为 $i \ge 1$，所以 $a_1$ 无法从 $a_0$ 转移过来。

- $a_{i+1} - a_i > 1$。根据操作容易得出，$a_{i+1} a_i$ 最多为 $1$，所以这种情况也无解。

再看有解的情况。

- $a_{i+1} - a_i =1$。这种情况最好处理，$s \gets s + 1$ 即可。

- $a_{i+1} \le a_i$。这种情况需要累加 $a_i$ 次，即 $s \gets s + a_i$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,s;
int a[200005]; 
signed main(){
	cin>>n>>a[1];
	if(a[1]>0){
		cout<<-1;
		return 0;
	}
	for(int i=2;i<=n;i++){
		cin>>a[i];
		if(a[i]-a[i-1]>1){
			cout<<-1;
			return 0;
		}
		else if(a[i]-a[i-1]==1)s++;
		else s+=a[i];
	}
	cout<<s;
	return 0;
}
```
### 后记
看到那个~~可爱的~~数据范围了吗？$0 \le a_i \le 10^9$ 哟！

~~不开 long long 见祖宗~~

## 此贴结

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

首先考虑无解情况，发现有两种：

- 当 $a_1$ 不为零时，显然不行，因为 $a_1$ 无法从上一项转移过来。

- 当 $a_i$ 和 $a_{i-1}$ 的差 $x$ 大于等于 $2$ 时，显然也不行，因为每次转移时，$a_i$ 等于 $a_{i-1}+1$，其差最多为 $1$。

然后可以发现，当 $a_i$ 和 $a_{i-1}$ 的差 $x$ 等于 $1$ 时，$a_i$ 可以从 $a_{i-1}$ 花一步转移过来，当 $a_i=a_{i-1}$ 时，显然什么都不用做，当 $a_i\lt a_{i-1}$ 时，$a_i$ 可以从最开始的全零的数组上累加 $a_i$ 次得来，代价为 $a_i$。

### $\text{code}$


```cpp

int n;

int a[maxn];

int ans=0;

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=n;i++){
		if(i==1){
			if(a[i]!=0){
				puts("-1");
				return ;
			}
		}
		if(a[i]-a[i-1]>=2){
			puts("-1");
			return ;
		}
		else{
			if(a[i]==a[i-1]+1){
				ans++;
			}
			else{
				ans+=a[i];
			}
		}
	}
	write(ans);
	puts("");
	return ;
}

```

---

