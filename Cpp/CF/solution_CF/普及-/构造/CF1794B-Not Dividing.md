# Not Dividing

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . In one operation, you can choose any number of the array and add $ 1 $ to it.

Make at most $ 2n $ operations so that the array satisfies the following property: $ a_{i+1} $ is not divisible by $ a_i $ , for each $ i = 1, 2, \ldots, n-1 $ .

You do not need to minimize the number of operations.

## 说明/提示

In the first test case, the array $ [4, 5, 6, 7] $ can be achieved by applying $ 2 $ operations to the first element, $ 1 $ operation to the second element, $ 3 $ operations to the third element, and $ 1 $ operation to the last element. The total number of operations performed is $ 7 $ , which is less than the allowed $ 8 $ operations in this case.

In the second test case, the array $ [3, 2, 3] $ can be achieved by applying two operations to the first element. Another possible resulting array could be $ [2, 3, 5] $ , because the total number of operations does not need to be minimum.

In the third test case, not applying any operations results in an array that satisfies the statement's property. Observe that it is not mandatory to make operations.

## 样例 #1

### 输入

```
3
4
2 4 3 6
3
1 2 3
2
4 2```

### 输出

```
4 5 6 7
3 2 3
4 2```

# 题解

## 作者：SunnyYuan (赞：6)

如果 $a_i$ 可以整除 $a_{i - 1}$，只要在 $a_i$ 上 $+1$ 即可，这样 $a_i \bmod a_{i - 1} = 1$ 就满足题目要求了，如果这样算来最多进行 $n$ 次操作。

但同时要注意 $a_{i - 1} = 1$ 的情况。如果 $a_{i - 1}$ 为 $1$，那么怎么 $+1$ 都是 $a_i \bmod a_{i - 1} = 0$ 的。

所以如果当前数字处理完了以后为 $1$ ，一定要 $+1$ 变为 $2$，如此算来最多会进行 $2n$ 个操作，与题目相符，可以 AC。

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: B. Not Dividing
| Contest: Codeforces Round 856 (Div. 2)
| URL:     https://codeforces.com/contest/1794/problem/B
| When:    2023-03-06 08:30:31
| 
| Memory:  256 MB
| Time:    2000 ms
*******************************/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	if (a[0] == 1) a[0]++;
	for (int i = 1; i < a.size(); i++) {
		if (a[i] == 1) a[i]++;
		if (a[i] % a[i - 1] == 0) {
			a[i]++;
		}
	}
	for (auto& x : a) cout << x << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Xy_top (赞：4)

这不是很显然的一道诈骗题吗？

输入完之后从 $1$ 一直到 $n$ 扫一遍，看一下 $a_i$ 是否能整除 $a_{i+1}$。

能的话一个较为简单的方法是把 $a_{i+1}$ 加上一，但是在 $a_i=1$ 的时候会出问题，所以我们先把 $a_i$ 变成 $2$，再去改 $a_{i+1}$。

这样的话，每个数字最多被改两下，所以不会超过 $2\times n$ 啦。

代码很短：

```cpp

#include <iostream>
using namespace std;
int t, n;
int a[50005];
int main () {
	cin >>t;
	while (t --) {
		cin >>n;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		for (int i = 1; i < n; i ++) {
			if (a[i + 1] % a[i] == 0) {
				if (a[i] == 1) {
					if (a[i - 1] == 2) a[i] += 2;
					else ++ a[i];
					i --;
				}
				else ++ a[i + 1];
			}
		}
		for (int i = 1; i <= n; i ++) cout << a[i] << " ";
		cout << "\n";
	}
	return 0;
}
```


---

## 作者：没见过AC (赞：1)

第一眼很怪，再看一眼发现被骗力。

如果 $ a_{i+1} \bmod a_{i} = 0$ 那么将 $a_{i+1}$ 加上 $1$，否则不用动。

但是需要考虑 $a_{i}=1$ 的情况，如果 $a_i=1$ 那怎么改 $a_{i+1}$ 都不行，所以如果   $a_{i}=1$ 那么先将 $a_i$ 加上 $1$，然后再看 $a_{i-1}$，因为如果改 $a_i$ 为 $2$，要是 $a_{i-1}$ 也是 $2$ 就不符合要求了。所以如果 $a_{i-1}$ 为 $2$ 那就要把 $a_i$ 改成 $3$。进行完如上特判后再进行一次第二段的操作就可以了。 


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+1000;
typedef long long ll;
inline int read()
{
    int n=0,x=1;char ch=getchar();
    if(ch=='-') x=-1;
    while(ch<'0'||'9'<ch)ch=getchar();
    while(ch>='0'&&ch<='9'){n=n*10+ch-'0';ch=getchar();}
    return n*x;
}
ll m,n,a[N],t;
int main()
{
    t=read();
    while(t--)
    {
    	memset(a,0,sizeof a);
    	n=read();
    	for(int i=1;i<=n;i++)
    	{
    		a[i]=read();
		}
		for(int i=1;i<n;i++)
		{
			if(a[i+1]%a[i]==0)
			{
				if(a[i]==1)//a[i]为1的特判 
				{
					if (a[i-1]==2) a[i]+=2;//a[i-1]同时为2的特判 
					else a[i]++;
					if(a[i+1]%a[i]==0) a[i+1]++;
				}
				else
				{
					a[i+1]++;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			printf("%lld ",a[i]);
		}
		printf("\n");
	}
	return 0;
}


```


---

## 作者：Amm_awa (赞：0)

[$\color{red}\fbox{\texttt{题目链接}}$](https://www.luogu.com.cn/problem/CF1794B)

## 分析

在操作时，会出现以下情况：

1. $a_{i+1} \bmod a_i = 0$ 即 $a_{i+1}$ 为 $a_i$ 的倍数，此时让 $a_{i+1}$ 加 $1$（$a_{i+1}+1$ 一定与 $a_{i+1}$ 互质）。
2. $a_i = 1$ 时，$ a_{i+1} \bmod a_i $ 一定为 $0$，此时 $a_i$ 要加 $1$。
3. 第 $2$ 种情况发生时，$a_{i-1}$ 可能为 $2$，这个时候 $a_i$ 再加 $1$，然后 $i$（循环变量）减 $1$，重新判断 $a_{i-1}$ 与 $a_i$。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[10005];
inline int read()
{
    register int x=0,f=1;
    register char ch=getchar();
    while(!isdigit(ch))
	{if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))
	{x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}

inline void solve()
{
	register int i;
	t=read();
	while(t--)
	{
		n=read();
		for(i=1;i<=n;i++)
			a[i]=read();
	    for(i=1;i<n;i++)
	    {
    		if(a[i+1]%a[i]==0)//a[i+1] 可以整除 a[i] 时
	    	{
	    	    if(a[i]==1)//a[i] = 1 时特判
		        {
		            if(a[i-1]==2)
		            {a[i]++;}// a[i] 等于 2 时要额外加一次 1
		            a[i]++;//此情况下 a[i] 至少加1
		            i--;//返回上一次判断
		        }
                else a[i+1]++;//a[i+1] 与 a[i+1]+1 互质
	    	}
	    }
    	for(i=1;i<=n;i++)
	    	cout<<a[i]<<' ';
        cout<<'\n';
	   }
}

int main()
{
	solve();
	return 0;
}
```

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1794B) & [CF链接](http://codeforces.com/problemset/problem/1794/B)

## 思路分析：

这道题并没有那么难，没有让求最小的操作次数，只要最后合法结果。

按题意模拟即可，下面证明最多 $2n$ 次操作，即可满足题意：

1. 对于每个数 $a_i(1<i\le n)$，如果当前 $a_i\bmod a_{i-1}=0$，就让 $a_i$ 加一。这样最多 $n$ 次操作。

2. 如果当前数是 $1$，就要加一使其变为 $2$，这样就是 $2n$ 次。

3. 特别地，如果 $n$ 个数全是 $1$，那只需要改为数字 $3$ 和数字 $2$ 交替即可，需要 $\displaystyle\frac{3}{2}n$ 次。

## 代码：

```cpp
#include<iostream>
using namespace std;
int n,a[10010];
int main(){
	int T;
	cin>>T;
	while(T--){//T组数据
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1){
				a[i]+=1;//如果是1就加一
			}
			if(i==1){//第一个数不做处理
				continue;
			}
			if(a[i]%a[i-1]==0){
				a[i]+=1;//模拟
			}
		}
		for(int i=1;i<=n;i++){
			cout<<a[i]<<" ";//输出
		}
		cout<<endl;//T组数据别忘了换行
	}
	return 0;
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，要让任何 $a_{i+1}\bmod a_i=0$。遍历输入：
1. 当 $a_i=1$ 时，进行一次操作，因为任何正整数对 $1$ 取模的结果都为 $0$。

2. 当 $a_i\bmod a_{i-1}=0$ 时，进行一次操作，因为经过第一步，一定有 $a_{i-1}>1$，所以 $(a_i+1)\bmod a_{i-1}=1$。

之后就可以输出了，操作次数最多为 $n+\lfloor\frac{n}{2}\rfloor$ 次。
## 代码
```python
a = int(input())
for b in range(a):
    c = int(input())
    d = list(map(int,input().split()))
    for e in range(c):
        if d[e] == 1:
            d[e] = 2
        if e != 0 and d[e]%d[e-1] == 0:
            d[e] += 1
    print(*d)
```

---

## 作者：Neilchenyinuo (赞：0)

## Solution

1. 先扫一遍整个数组，看看 $a_{i}$ 是否能整除 $a_{i+1}$。

2. 如果行就让被除数 $a_{i+1}$ 加上一（如果除数 $a_{i}$ 是 $1$ 的话，$a_{i+1}$ 怎么改都能整除，因此我们先将 $a_{i}$ 改成 $2$ 然后将 $a_{i+1}$ 加上一就 OK 了）。

3. 然后输出修改过的 $a_{i}$ 即可。

4. 这样的话，每个数字最多被改两下，修改次数不会超过 $2 \times n$，可以通过。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[50005];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<n;i++)
		{
			if(a[i+1]%a[i]==0)
			{
				if(a[i]==1)
				{
					if(a[i-1]==2)
						a[i]+=2;
					else
						a[i]++;
					i--;
				}
				else ++ a[i + 1];
			}
		}
		for (int i=1;i<=n;i++)
			cout<<a[i]<<" ";
		cout<<"\n";
	}
	return 0;
}

```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1794B)

我们不妨将数据遍历，当 $a_{i+1} \bmod a_i=0$ 时，执行我们的操作**直到** $a_{i+1} \bmod a_i \ne 0$，否则跳过。用 while 循环即可。


执行的操作也很简单：当 $a_{i+1} \bmod a_i=0$ 时，将 $a_{i+1}$ 逐步增加 $1$。

这里有几个注意事项：

- 必须是将 $a_{i+1}$ 增加，因为你不能确定加 $a_i$ 是否会和 $a_{i-1}$ 产生矛盾。

- 当 $a_i=1$ 时，上述操作是没用的，这时我们需要将 $a_i$ 增加。但注意，当 $a_{i-1}=2$ 时，$a_i$ 要增加 $2$，其余情况增加 $1$。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,a[10010];
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<n;i++)
		{
			while(a[i+1]%a[i]==0)
			{
				if(a[i]==1)
				{
					if(a[i-1]==2)
						a[i]+=2;
					else 
						a[i]++;	
				}
				else
					a[i+1]++;
			}
		}
		for(int i=1;i<=n;i++)
			cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
} 
```


---

## 作者：Convergent_Series (赞：0)

每次读入后从 $1$ 到 $n$ 遍历。

若 $a_{i+1}\bmod a_i\ne0$，则无需调整。

否则：

若 $a_i=1$，则调整 $a_{i+1}$ 是没用的，要将 $a_i$ 加 $1$；  
但 $a_{i-1}=2,a_i=1$ 时，加 $1$ 导致 $a_i\bmod a_{i-1}=0$，所以 $a_i$ 还要加 $1$。

若 $a_i\ne1$，则直接在 $a_{i+1}$ 上加 $1$。

容易发现，这样操作时每个数最多改变两次，符合条件。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[50010];
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for (int i=1;i<=n;i++) cin>>a[i];
		for (int i=1;i<n;i++){
			if(a[i+1]%a[i]==0){
				if(a[i]==1){
					if(a[i-1]==2) a[i]+=2;
					else a[i]++;
					if(a[i+1]%a[i]==0) a[i+1]++;
				}
				else a[i+1]++;
			}
		}
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Iamzzr (赞：0)

一个很直观的想法，遍历 $1\sim n-1$，如果 $a_i$ 能整除 $a_{i+1}$，就把 $a_{i+1}$ 加一个。

不难发现，当 $a_i$ 等于 $1$ 的时候，这个方法不适用。所以要特判，如果 $a_i$ 为 $1$，就把 $a_i$ 改成 $2$。

但是问题又来了，把 $a_i$ 改成 $2$ 之后，又有可能 $a_{i-1}$ 能整除 $a_i$，所以进行第三次特判，注意这次特判是如果 $a_{i-1}$ 能整除 $a_i$，就把 $a_i$ 加一，而非对 $a_{i-1}$ 操作。

代码：

```cpp
#include <iostream>

using namespace std;

const int N = 10010;

int T;
int a[N];

int main() {
    cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i < n; i++) {
            if (a[i] == 1) a[i]++;
            if (i != 1) while (a[i] % a[i - 1] == 0) a[i]++;
            while (a[i + 1] % a[i] == 0) a[i + 1]++;
        }
        for (int i = 1; i <= n; i++) cout << a[i] << " ";
        puts("");
    }
    return 0;
}

```

---

## 作者：atomic_int (赞：0)

## 题意：
题目翻译中已有。

## 分析：
- 如果 $a_i=1$ 必须加 $1$。
- 对于 $1 \leq i < n$，如果 $a_{i+1} \bmod a_i = 0$，$a_i$ 加 $1$。
- 对于 $2 \leq i \leq n$，如果 $a_{i} \bmod a_{i-1}=0$，$a_i$ 加 $1$。

## 代码：
```cpp
inline void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i ++) {
        if (a[i] == 1) {
            a[i] ++;
        }
        if (i != n && a[i + 1] % a[i] == 0) {
            a[i] ++;
        }
        if (i != 1 && a[i] % a[i - 1] == 0) {
            a[i] ++;
        }
    }
    for (int i = 1; i <= n; i ++) {
        cout << a[i] << " \n"[i == n];
    }
}
```

---

