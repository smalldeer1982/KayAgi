# MIN = GCD

## 题目描述

给定一个长度为 $n$ 的正整数序列 $a$。判断是否可以重新排列 $a$，使得存在一个整数 $i$（$1 \le i < n$）满足：
$$
\min([a_1, a_2, \ldots, a_i]) = \gcd([a_{i+1}, a_{i+2}, \ldots, a_n]).
$$
其中，$\gcd(c)$ 表示 $c$ 的[最大公约数](https://en.wikipedia.org/wiki/Greatest_common_divisor)，即能整除 $c$ 中所有整数的最大正整数。

## 说明/提示

- 在第一个测试用例中，将 $a$ 重新排列为 $[1, 1]$ 并令 $i=1$，则 $\min([1]) = \gcd([1])$。  
- 在第二个测试用例中，可以证明不可能满足条件。  
- 在第三个测试用例中，将 $a$ 重新排列为 $[3, 2, 2]$ 并令 $i=2$，则 $\min([3, 2]) = \gcd([2])$。  
- 在第五个测试用例中，将 $a$ 重新排列为 $[3, 4, 5, 6, 9]$ 并令 $i=3$，则 $\min([3, 4, 5]) = \gcd([6, 9])$。  

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
2
1 1
2
1 2
3
2 2 3
3
2 3 4
5
4 5 6 9 3
3
998244359987710471 99824435698771045 1000000007
6
1 1 4 5 1 4```

### 输出

```
Yes
No
Yes
No
Yes
Yes
Yes```

# 题解

## 作者：hongshixiaobai (赞：3)

# CF2084B MIN = GCD 题解
[传送门](https://www.luogu.com.cn/problem/CF2084B)
## 思路
分类讨论整个数组的最小值在 $\min$ 的部分还是 $\gcd$ 的部分：

1.最小值在 $\min$ 的部分

此时要求 $\gcd$ 等于最小值，显然 $\gcd$ 的部分每个数都是最小值的倍数，考虑贪心，把所有的最小值的倍数（除了一个最小值以外）都放到后面，其他数都放在前面，判断 $\gcd$ 是否等于最小值即可，感性理解贪心的正确性：增加一个数肯定不会使 $\gcd$ 增大，同时保证了所有数都是最小值的倍数，所以正确。

2.最小值在 $\gcd$ 的部分

此时若有一个最小值在 $\min$ 则可以归纳到上一种情况，否则 $\min$ 的部分的值一定大于最小值，$\gcd$ 的值一定小于等于最小值，所以此时无解。

综上所述，最小值一定有至少一个在 $\min$ 的部分，所以两侧的值一定都是最小值。

判断是否存在一些序列中的数使得 $\gcd$ 等于最小值即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200005],i,g;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(i = 1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		g = 0;
		for(i = 2;i<=n;i++)
            if(a[i]%a[1] == 0)g = __gcd(g,a[i]);
		if(g>a[1]||g == 0)cout<<"NO\n";
		else cout<<"YES\n";
	}
}
```

---

## 作者：Eason_cyx (赞：3)

假设 $\displaystyle\min_{j=1}^{i}a_j=\displaystyle\gcd_{j=i+1}^{n}a_j=a_x$。那么根据 $\min$ 函数和 $\gcd$ 函数的性质，我们可以得到对于 $1 \le k \le n$，且 $k\not =x$ 的所有 $k$，均有 $a_k\ge a_x$。

所以，$a_x$ 就是 $a$ 中的最小值。

那么为了让 $a_x$ 可以成为答案，最优的策略就是将所有 $a_x$ 的倍数全部放到等式右边；然后我们判断右边是不是最大公约数等于 $a_x$ 即可。

时间复杂度 $O(n\log V)$，此处 $V$ 为值域，$V=10^{18}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll a[200005], b[200005];
int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n; for(int i = 1;i <= n;i++) cin >> a[i];
        sort(a+1, a+n+1); if(a[2] == a[1]) { cout << "Yes\n"; continue; }
        int cur = 0; for(int i = 2;i <= n;i++) 
            if(a[i] % a[1] == 0) b[++cur] = a[i] / a[1];
        if(cur == 1) { cout << "No\n"; continue; } 
        ll x = b[1]; for(int i = 2;i <= cur;i++) x = __gcd(x, b[i]);
        cout << (x == 1 ? "Yes" : "No") << endl;
    } return 0;
}
```

---

## 作者：alice_c (赞：2)

## 思路

显然，在任意一个正整数序列 $a$ 里，$\gcd(a) \le \min(a)$。我们让 $x$ 为 $\min(a)$，那么有一个 $x$ 必须放在左边。我们需要选择一些数字，使右边那些数的 $\gcd$ 等于 $x$。

考虑贪心，我们把除去一个 $x$ 的所有 $x$ 的倍数都放在右边，这样可以使 $\gcd$ 尽可能小且还是 $x$ 的倍数。

最后，我们只需要判断 $\gcd$ 是否等于 $x$ 即可。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int t,n;
long long a[100005],gcd;
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        sort(a+1,a+n+1);
        gcd=0;
        for(int i=2;i<=n;i++)
            if(a[i]%a[1]==0) gcd=__gcd(gcd,a[i]);
        if(gcd==a[1]) puts("Yes");
        else puts("No");
    }
}
``````

---

## 作者：NTT__int128 (赞：1)

很简单的一道 B 题。

讨论一下：

若 $a$ 中最小值放在 $\gcd$ 那一堆，发现等式右边小于左边，矛盾。所以最小值 $mn$ 放左边。

为了使右式等于 $mn$，取出所有 $mn$ 的倍数（除了**一个** $mn$）放在右边。不难发现，多取一些 $mn$ 的倍数一定不劣。

如果取出的数的 $\gcd$ 等于 $mn$，则可行，否则不行。

代码放个链接：https://codeforces.com/contest/2084/submission/323188099

---

## 作者：ZAYNAab (赞：1)

## 题意
给你 $n$ 个自然数。

将他们分为两组，使得第一组的最小值等于第二组的最大公约数。

## 解题分析
先设这 $n$ 个自然数最小的一个为 $c$。

若在 $n$ 个自然数中有 $2$ 个及以上等于 $c$ 的数。

将其中一个放在求最大公约数那组，再将剩下的放最小值那组即可。

若在 $n$ 个自然数中有且仅有一个等于 $c$ 的数。

则对这 $n$ 个自然数进行如下处理。

设当前处理的数为 $x$，已经分到求最大公约数那组的最大公约数为 $y$。

1. 若 $x=c$ 跳过讨论。

2. 若 $\gcd(y,x)<c$，则将 $x$ 放在最小值那组。

3. 若 $\gcd(y,x)>c$，则将 $x$ 放在求最大公约数那组。

最后看分组完成后 $y$ 是否等于 $c$ 即可。
 

## 赛时代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n,flag=0;cin>>n;
		ll minn=1000000000000000001;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			minn=min(a[i],minn);
		}
		for(int i=1;i<=n;i++)if(a[i]==minn and flag==1){
			flag=2;
			break;
		}else if(a[i]==minn){
			flag++;
		}
		if(flag==2){
			cout<<"YES\n";
			continue;
		}
		flag=0;ll x=0;
		for(int i=1;i<=n;i++){
			if(a[i]==minn)continue;
			ll p=__gcd(a[i],x);
			if(p<minn)continue;
			else if(p%minn==0 and p!=minn){
				x=p;
			}else if(p==minn){
				flag=1;
				break;
			}
		}
		if(flag==1)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：cqbzhzf (赞：1)

[vjudge 中文翻译](https://vjudge.net/problem/CodeForces-2084B#author=DeepSeek_zh)
### 思路
考虑最简单的构造方式，令 $x = \min_{i=1}^{n}a_i$，可以把 $x$ 和数组中非 $x$ 倍数的元素分为第一组（保证了 $x$ 是其中最小的元素），$x$ 倍数的元素分为第二组，判断第二组的最大公因数是否为 $x$ 即可。  
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n,a[N],x,y;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		x=1,y=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]<a[x])
				x=i;
		}
		for(int i=1;i<=n;i++)
		{
			if(i!=x&&a[i]%a[x]==0)
				y=__gcd(y,a[i]);
		}
		if(y==a[x])
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：ccxXF (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF2084B)
## 题目分析
希望审核大大给过。

一道模拟题目。可以先给 ```a``` 数组排序并整理出数组的最小值，再判断一个数字是否能被 $\min([a_1 , a_2 , a_3 , \dots , a_{n-1} , a_n])$ 整除，如果整除不了，那就不考虑那个数，因为这个数字一旦加入进 $\gcd$ 的序列里，那 $\gcd$ 的值就为 $1$，明显不符合要求。最后判断答案是否为 Yes 或 No 时，如果超过了 ```a``` 数组的最小值或者 $\gcd$ 没有数据，那么就无解，否则输出 Yes。

上代码！！！
## 题目代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
int t,n,a[200005],g;
signed main(){
	speed;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i = 1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		g = 0;
		for(int i = 2;i<=n;i++)
            if(a[i]%a[1] == 0)g = __gcd(g,a[i]);//__gcd为最大公因数的系统自带函数
		if(g>a[1]||g == 0)cout<<"NO\n";
		else cout<<"YES\n";
	}
}
```

---

