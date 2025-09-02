# Magnitude (Easy Version)

## 题目描述

### **题目翻译描述**

这个问题的两个版本是不同的。你可能想阅读这两个版本。这样，只有两个版本都解决了，你才能成为黑客。

您将获得一个长度n的数组。C=0.然后，对于从i到n（按升序排列）执行以下操作之一：

选项1：将c设置为c+$a_{i} $。
 
选项2：放c到∣c+$a_{i}$∣，其中∣x∣表示x的绝对值。

你要使运行上述过程之后的c的最大最终值等于k，并且找到输出k。

## 样例 #1

### 输入

```
5
4
10 -9 -3 4
8
1 4 3 4 1 4 3 4
3
-1 -2 -3
4
-1000000000 1000000000 1000000000 1000000000
4
1 9 8 4```

### 输出

```
6
24
6
4000000000
22```

# 题解

## 作者：ikunTLE (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF1984C1)

### 思路

题目中有两个选项：

1. 如果选择第一个选项，就要使两个数和最大，就是使 $c$ 最大。

2. 如果选择第二个选项，如果 $c$ 的值很大，那么与第一个选项没有区别，所以就要使 $c$ 最小。

**贪心**思路比较简单，就是维护每次操作后的最大值和最小值。最后的**最大值**即为所求。

**注意事项**

- 不开 `long long` 见祖宗。

**AC CODE**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define llabs(x) (long long)(abs(x))
const int N=2e5+10;
int	t,n,a[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		long long max_c=0,min_c=0;
		for(int i=1;i<=n;++i){
			long long maxx=max_c+a[i],minn=min_c+a[i];
			max_c=max(max(maxx,llabs(maxx)),max(minn,llabs(minn)));
			min_c=min(min(minn,llabs(minn)),min(maxx,llabs(maxx)));
		}
		printf("%lld\n",max_c);
	}
	return 0;
}
```

---

## 作者：littlebug (赞：3)

## Solution

对于 $a$ 维护一个前缀和数组 $sum$。

证明：只能进行一次操作二。

显然，只有在 $sum_i < 0$ 的时候进行操作二才有意义。若进行两次操作二，分别在位置 $i,j$，则在位置 $i$ 处 $sum_i$ 变大，所以到了 $j$ 处时，$sum_j$ 会比不进行 $i$ 处操作的 $sum_j$ 小（考虑绝对值的性质），就不会成为最优解。

那么，只需要在计算 $sum$ 的时候看一下哪个位置 $i$ 的 $sum_i$ 最小（设为 $mn$），在这一步进行操作二即可，因为对一个负数取绝对值就是将其减去自己的两倍，所以最终答案为 $sum_n-mn \times 2$。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
#define ll long long
using namespace std;
const ll mod=998244353;
const int MAXN=2e5+5;
int n;
ll a[MAXN];
ll sum[MAXN];
il void solve()
{
	cin>>n;
	ll mn=0;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		mn=min(mn,sum[i]);
	}
	cout<<sum[n]-mn*2<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：2)

~~看到 Hard version 要求方案数~~，考虑 dp。

结论：第 $i$ 次操作能够变为最大值的只有 $i-1$ 次操作前的最大值 $c_{\max}$ 与最小值 $c_{\min}$。

> 证明：考虑 $c_{\min}\le c'\le c_{\max}$，则 $c'+a_i\le c_{\max}+a_i$。\
> 当 $c'+a_i\ge 0$ 时 $|c'+a_i|\le |c_{\max}+a_i|$，当 $c'+a_i< 0$ 时 $|c'+a_i|\le |c_{\min}+a_i|$。\
> 证毕。

于是我们设 $f_{i,0/1}$ 表示在第 $i$ 次操作后 $c$ 能取得的最小/最大值。

显然 $f_{i,0/1}$ 都可以由 $f_{i-1,0/1}$ 分别按取不取绝对值转移而来。

$$
f_{i,0}=\min(f_{i-1,0}+a_i,|f_{i-1,0}+a_i|,f_{i-1,1}+a_i,|f_{i-1,1}+a_i|)\\
f_{i,1}=\max(f_{i-1,0}+a_i,|f_{i-1,0}+a_i|,f_{i-1,1}+a_i,|f_{i-1,1}+a_i|)
$$

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
#define mkt make_tuple
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=200007,ee=1000000000000000007ll,p=998244353;
ll n,a[maxn],f[maxn][2];
ll myabs(ll a){return (a<0?-a:a);}
signed main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(;T--;){
		cin>>n; f[0][0]=0,f[0][1]=0;
		for(int i=1;i<=n;i++) cin>>a[i],f[i][0]=ee,f[i][1]=-ee;
		for(int i=1;i<=n;i++){
			f[i][0]=min(min(f[i-1][0]+a[i],myabs(f[i-1][0]+a[i])),
			min(f[i-1][1]+a[i],myabs(f[i-1][1]+a[i])));
			f[i][1]=max(max(f[i-1][0]+a[i],myabs(f[i-1][0]+a[i])),
			max(f[i-1][1]+a[i],myabs(f[i-1][1]+a[i])));
		}
		cout<<f[n][1]<<"\n";
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
首先，用 $1$ 操作时，最大值肯定是从之前最大值转移过来的；用 $2$ 操作时，最大值则是从之前的最小值转移过来的。两个比一比就可以了。然后，最小值的计算显然一定不能要绝对值，最小值只会让它变大，所以直接加和就行啦。

[Code](https://codeforces.com/problemset/submission/1984/264891886)。

---

## 作者：ttq012 (赞：1)

### C1

发现要么一直不用 $2$ 操作，要么在答案取到最小值的时候使用一遍 $2$ 操作让其变为相对大一些的值。显然使用多遍 $2$ 操作是不优的。然后还能发现若存在一个位置 $p$ 使得前缀和 $<0$，那么这个地方不用 $2$ 操作肯定不如用 $2$ 操作优。因此若不存在一个前缀和的值 $<0$ 那么就不应该使用 $2$ 操作。否则一定在任意一个值最小的位置使用 $2$ 操作即可。

时间复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100;
int a[N],pre[N];
signed main() {
    int T;
    cin>>T;
    while(T--){
        int n,id=-1;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i],pre[i]=pre[i-1]+a[i];
        int mi=0;
        for(int i=n;i;i--)if(pre[i]<mi){
            mi=pre[i];
            id=i;
            // break;
        }
        if(id==-1)cout<<pre[n]<<'\n';
        else{
            int s=0;
            for(int i=1;i<=n;i++){
                if(i<=id)s-=a[i];
                else s+=a[i];
            }
            cout<<s<<'\n';
        }
    }
}
```

---

## 作者：Dream_Mr_li (赞：0)

## 题意

给你一个长度为 $n$ 的数组 $a$ 和一个 $c$，对于第 $i$ 次操作，可以将 $c+a_i$，然后你可以让 $c$ 取绝对值或不取，让你算最后 $c$ 最大是多少。

## 思路

一个负数越小，它的绝对值就越大。所以对于每一次 $i$，我们都需要取一个最大值和一个最小值，如果最小值的绝对值大于最大值，那就将最大值改为最小值的绝对值。最后输出第 $n$ 次循环结果的最大值即可。

时间复杂度 $O(tn)$，可以通过此题。

**注意：不开 `long long` 见祖宗。**
## 代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t,n,a,xx[N],nn[N],mx,mn; 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			mx=xx[i-1]+a;
			mn=nn[i-1]+a;
			xx[i]=max(abs(mx),abs(mn));
			nn[i]=min(mx,mn);
		}
		cout<<xx[n]<<endl;
	}
	return 0;
}
```

---

## 作者：_weishiqi66_ (赞：0)

# 题意
给你一个长度为 $n$ 的数组 $a$（按递增顺序）。从 $c = 0$ 开始。然后，对于从 $1$ 到 $n$ 的每个 $i$ 做以下项中的项：
- 选项 $1$：将 $c$ 设为 $c + a_i$
- 选项 $2$：将 $c$ 设为 $|c + a_i|$ 

设上述步骤后 $c$ 的最大最终值等于 $k$，求 $k$。

# 题解
对于这道题，我们要得到最大的最终值，每次操作肯定要加尽可能大的数字，或者是减尽可能小的数字，使得 $|c|$ 尽量大。因此我们可以贪心的考虑。记录下对于每个 $i$ 能得到的 $cmax$ 和 $cmin$，最后得到的 $cmax$ 就是答案。

简单证明一下，对于最大最终值来说，它一定由题目中的两个选项中的来的。如果是选项一，则在它操作之前的 $c$ 越大越好。如果是选项二，则在它操作之前的 $c$ 越小越好。

代码：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N=1e6;
int t,n,a[N];
signed main() {
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int cmax=0,cmin=0;
		for(int i=1;i<=n;i++) {
			int cmaxa=cmax+a[i],cmina=cmin+a[i];
			cmax=max(max(cmaxa,abs(cmaxa)),max(cmina,abs(cmina)));
			cmin=min(min(cmina,abs(cmina)),min(cmaxa,abs(cmaxa)));
		}
		cout<<max(cmax,cmin)<<endl;
	}
	return 0;
}
```

---

## 作者：ztksc07 (赞：0)

# 题解：CF1984C1 Magnitude (Easy Version)

## 题目大意

给定一个长度为 $n$ 的数组 $a$ 和一个变量 $c$（初始为 $0$），对于第 $i$ 次操作，需要把 $c$ 加上 $a_i$，然后可以选择将 $c$ 取或不取绝对值。求累加完成后最大的 $c$ 是多少。

## 解题思路

我们知道，一个负数越小，它的绝对值就越大。那么我们分别计算 $c$ 在第 $i$ 次操作中的最大值和最小值，每次操作完成后把最小值取绝对值与最大值比较，把最大值替换成更大的那个，所有操作完成后输出最后一次操作的最大值即可。

题目告诉我们所有的 $n$ 加起来小于等于 $3 \times 10^5$，所以可以忽略 $t$，时间复杂度即为 $O(n)$，其中 $n$ 代表题目中所有 $n$ 的和，$n \le 3 \times 10^5$，稳过。

## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=2e5+10;
int t,n,a;
long long maxc[maxn],minc[maxn],maxa,mina; 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a);
			maxa=maxc[i-1]+a;
			mina=minc[i-1]+a;
			maxc[i]=max(abs(maxa),abs(mina));
			minc[i]=min(maxa,mina);
		}
		printf("%lld\n",maxc[n]);
	}
	return 0;
}
```

## 注意事项

还是需要开 `long long`。

---

## 作者：wly09 (赞：0)

## 题意简述

给定一个长为 $n$ 的数组 $a$，一个初值为 $0$ 的变量 $c$，对于第 $i$ 次操作，您可以选择一种：

+ $c\gets c+a_i$
+ $c\gets |c+a_i|$

求完成所有操作后，$c$ 的最大值。

## 思路

考虑贪心，但是无脑取最大值显然不对，因为绝对值运算可能会使非常小的值在操作后变得非常大。

于是思路很清晰了，我们维护每次操作后的最大值和最小值。每次操作，我们分别对最小值和最大值进行两种操作，得到总共 $4$ 个数字，从中取最小值和最大值即可。

## Code

```cpp
const int N = 3e5;
int n;
long long a[N], g[N], l[N];
 
void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) {
    long long u = g[i - 1] + a[i];
    long long v = l[i - 1] + a[i];
    g[i] = max(abs(u), abs(v));
    l[i] = min(u, v);
  }
  cout << g[n] << '\n';
}
```

---

