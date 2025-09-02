# K-Sort

## 题目描述

You are given an array of integers $ a $ of length $ n $ .

You can apply the following operation any number of times (maybe, zero):

- First, choose an integer $ k $ such that $ 1 \le k \le n $ and pay $ k + 1 $ coins.
- Then, choose exactly $ k $ indices such that $ 1 \le i_1 < i_2 < \ldots < i_k \le n $ .
- Then, for each $ x $ from $ 1 $ to $ k $ , increase $ a_{i_x} $ by $ 1 $ .

Find the minimum number of coins needed to make $ a $ non-decreasing. That is, $ a_1 \le a_2 \le \ldots \le a_n $ .

## 说明/提示

In the first test case, $ a $ is already sorted, so you don't have to spend any coins.

In the second test case, the optimal sequence of operations is:

- Choose $ k = 2 $ and the indices $ 2 $ and $ 5 $ : $ [ 2, \color{red}{1}, 4, 7, \color{red}{6} ] \rightarrow [2, 2, 4, 7, 7] $ . This costs $ 3 $ coins.

 It can be proven that it is not possible to make $ a $ non-decreasing by spending less than $ 3 $ coins.

## 样例 #1

### 输入

```
5
3
1 7 9
5
2 1 4 7 6
4
1 3 2 4
1
179
9
344 12 37 60 311 613 365 328 675```

### 输出

```
0
3
2
0
1821```

# 题解

## 作者：mystic_qwq (赞：5)

前言：赛时想了一个小时才想出 $O(n\log n)$ 的做法，wtcl（

给一个序列 $\{a_1,a_2,\cdots,a_n\}$。每次可以令任意 $x$ 个数自增，代价是 $x+1$。问要令 $a$ 单调不降，花费的最小代价是多少？

考虑取前缀 $\max$。循环一次，取前缀 $\max=mx$。若有数字小于他，则贡献加 $mx-a_i$。考虑自增次数：发现是最大的 $mx-a_i$。因为每次都把所有能取的取了。共取最大的差值那么多次。于是令 $mx1=\max\{mx-a_i\}$ ，最终加上 $mx1$ 即可。

---

## 作者：luckyqwq (赞：3)

# CF1987B K-Sort 题解

### 大致意思：

你可以进行 $x$ 次操作，每次操作你可以选择一个数 $k$，在序列中选择 $k$ 个数，对它们进行加 $1$ 操作，每次选择数 $k$，就要花费代价 $k + 1$，问至少花费多少代价，能使序列变为一个单调不减序列。

### 大致思路：

这题思路十分明显，不递减序列，也就是满足除序列第一位以外，剩余的数满足 $a_i \ge a_{i - 1}$。我们可以利用一个类似贪心的策略，我们现在把目前数看为 $x$，前一个数看为 $y$：

- $x \ge y$，完全不用管，已经达成不递减关系。

- $x < y$，这种情况数 $x$ 就需要变化了，从贪心的角度看，我们要将 $x$ 变成 $y$。其实很好证明，想要达成不递减，最少起码得和前一个数相等，这样用的次数最少。

这时候，答案其实很明显了，如果他问的是最少次数，那么只需要输出，在最优方案下，扩大次数最多的数，它要加上多少个 $1$ 即可。

而这里他问我们的是，最少代价，最朴素的办法是对于每次的变化，存入一个数组 $b$，计算出 $b$ 的总和，对 $b$ 从大到小进行排序，第一位也就是上面我们讲的最大次数，这也就是在题目中的代价里 $k + 1$ 中的 $1$ 的个数，加上它就是我们的答案。

这也就诞生了我的第一版代码，更加好理解：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
inline int read()
{
	int r = 0, w = 1;
	char c = getchar();
	while(c < '0' || c > '9'){if(c == '-'){w = -1;}c = getchar();}
	while (c >= '0' && c <= '9'){r = (r << 3) + (r << 1) + (c ^ 48);c = getchar();}
	return r * w;
}
int T, n, a[N], b[N];
signed main()
{
	T = read();
	while (T --)
	{
		n = read();
		int tp = 0;
		bool f = 0;
		for (int i = 1;i <= n; ++ i)
		{
			a[i] = read();
			b[i] = 0;
			if(a[i] < a[i - 1])
			{
				f = 1;
			}
		}
		if (f == 0)
		{
			cout << "0\n";
			continue;
		}
		for(int i = 2;i <= n; ++ i)
		{
			if(a[i] < a[i - 1])
			{
				b[ ++ tp] = a[i - 1] - a[i];
				a[i] = a[i - 1];
			}
		}
		sort(b + 1, b + tp + 1);
		int s = 0;
		for(int i = 1;i <= tp; ++ i)
		{
			s += b[i];
			//cout << b[i] << " ";
		}
		cout << s + b[tp] << "\n";
	}
	return 0;
}
```

这个代码适用于初学者，每次询问时间复杂度为 $O(n \log n)$，可以过，显然的，这个代码的瓶颈在于那个 $\log$，也就是排序。接下来，进行小小的优化，我们可以发现根本不需要开 $b$ 数组，只需要在中间找最大值和记录即可，每次询问时间复杂度为 $O(n)$，变为线性，更快一些，虽然没啥用，不过在有一些题目中压缩合并还是非常有用的。

### 代码实现：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
inline int read()
{
	int r = 0, w = 1;
	char c = getchar();
	while(c < '0' || c > '9'){if(c == '-'){w = -1;}c = getchar();}
	while (c >= '0' && c <= '9'){r = (r << 3) + (r << 1) + (c ^ 48);c = getchar();}
	return r * w;
}
int T, n, a[N], b[N];
signed main()
{
	T = read();
	while (T --)
	{
		n = read();
		int tp = 0, s = 0;
		bool f = 0;
		for (int i = 1;i <= n; ++ i)
		{
			a[i] = read();
			b[i] = 0;
			if(a[i] < a[i - 1])
			{
				f = 1;
			}
		}
		if (f == 0)
		{
			cout << "0\n";
			continue;
		}
		int x = 0, mx = -1;
		for(int i = 2;i <= n; ++ i)
		{
			if(a[i] < a[i - 1])
			{
				x = a[i - 1] - a[i];
				s += x;
				mx = max(mx, x);
				a[i] = a[i - 1];
			}
		}
		cout << s + mx << "\n";
	}
	return 0;
}
```

这样这道题就完成啦！！！

---

## 作者：Scean_Tong (赞：2)

### 思路

若当前的数小于前缀 $\max$，就将当前的数与前缀 $\max$ 补齐，答案每次都要加上补齐的值，即代码中的 `ans+=(mx-a[i])`，并记录补齐的最大值。

答案最后别忘了加上补齐的最大值。

### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> p;
const int N=2e5+5;
int a[N];
inline int read(){
	int xr=0,f=1;
	char cr;
	while(cr=getchar(),cr<'0' || cr>'9'){
		if(cr=='-'){
			f=-1;
		}
	}
	while(cr>='0' && cr<='9'){
		xr=(xr<<3)+(xr<<1)+(cr^48);
		cr=getchar();
	}
	return xr*f;
}
signed main()
{
    int t;
    t=read();
    while(t--)
    {
        int n;
        n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        int ans=0;
        int mx_diff=0;
        int mx=a[1];
        for(int i=2;i<=n;i++)
        {
            mx=max(mx,a[i]);
            mx_diff=max(mx_diff,mx-a[i]);
            ans+=(mx-a[i]);
        }
        ans+=mx_diff;
        cout<<ans<<'\n';
    }
}
```

---

## 作者：InfiniteRobin (赞：1)

## 题目大意  
给你一个长度为 $n$ 的序列 $a$，每一次操作可以使序列中任意的 $k$ 个数自增 $1$，花费为 $k+1$。要想使该序列**单调不降**，求最小的花费。本题多测。  
## 思路  
在序列中，除了序列中的最后一个数，如果出现 $a_{x}>a_{x+1}$，那就要使 $a_{x+1}$ 的值变为 $a_{x}$，这样既满足单调不降，又可以使花费最小。我们可以将每个数的变化量储存在数组 $b$ 中。 
  
因为每次操作的花费与修改元素个数有关，所以每次修改的区间长度应尽可能的长，这样才可以使加 $1$ 的数量最小。 
  
可以先将变化量由小到大排序，逐一进行修改。对于其中的第 $i$ 个数而言，前面的数都已经处理完，$b_{i}$ 也会被前面的操作影响，因此 $b_{i}$ 的值要减去当前完成的操作次数。此时要对 $b_{i}\sim b_{n}$ 进行 $b_{i}$ 次修改，使 $b_{i}$ 变为 $0$。由题可知，花费为  
$$ b_{i} \times (n-i+1+1)。  $$  
逐个累计即可求得答案。  
## Code  
```cpp
#include<bits/stdc++.h>
using namespace std;

long long t,n,a[100005]; //这里用 a 表示变化量

int main(){
    cin>>t;
    while(t--){
        cin>>n;
        int now=0,last=0; //当前数 和 前一个数
        for(int i=1;i<=n;i++){
            cin>>now;
            if(now<last){  //如果不符合要求
                a[i]=last-now; //记录变化量
                now=last;  //更改当前数
            }
            last=now;
        }
        sort(a+1,a+1+n);  //排序
        long long ans=0,sum=0; //sum 为已完成的操作次数
        for(int i=1;i<=n;i++){
            a[i]-=sum;  //当前数要减去 sub
            if(a[i]<=0){ //等于0就跳过
                continue;
            }
            ans+=(n-i+1+1)*a[i]; //更改花费 
            sum+=a[i]; //累计操作次数
        }
        cout<<ans<<endl;
        memset(a,0,sizeof(a)); //记得清空
    }
    return 0;
}
```  

------------
### THE END

---

## 作者：fwtv_24 (赞：0)

这道题其实很简单，就是当 $a_i<a_{i-1}$ 时，让每个 $a_i$ 都变成前一个数（即保证数列不递减），答案即为所有增加的数据与最大增加的数据的和。

记得开 `long long`。

详细看注释。

```cpp
#include<bits/stdc++.h>
#define int long long//不开longlong见祖宗
using namespace std;
int n,a[100005],y,T,ans=0,x=0,maxx=0;
signed main()
{
	cin>>T;
	while(T--)//多组数据
	{
    	ans=0,x=0,maxx=0;
    	cin>>n;
    	for(int i=1;i<=n;i++)
		{
    		cin>>a[i];
		}
    	for(int i=1;i<=n;i++)
		{
    		ans+=max(0ll,maxx-a[i]);//使数列保证不递减
    		x=max(x,maxx-a[i]);//记录最大增加的数据
    		maxx=max(maxx,a[i]);
		}
		cout<<ans+x<<endl;//输出
    }
	return 0;//完结撒花~~
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
不管怎么操作，不难得出 $\sum k=\sum a_i$。所以，我们只要求最少可以取走几个连续线段即可（显然，答案就是所有最长上升子串的最高峰之和）。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, x, lst, maxx;
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> lst;
		sum = maxx = 0;
		while (-- n) {
			cin >> x;
			if (x < lst)
				maxx = max (maxx, lst - x), sum += lst - x;
			else
				lst = x;
		}
		cout << maxx + sum << '\n';
	}
	return 0;
}
```

---

## 作者：xcms (赞：0)

如果 $a_{i-1}>a_i$，为了让花费的次数最少且数组 $a$ 是一个单调不减序列，就使 $a_i$ 变成 $a_{i-1}$ 即可。

实际上只需要计算花费最多的次数要加上多少个 $1$。要加上多少个 $1$，就是在 $a_{i-1}>a_i$ 的时候，$a_{i-1}-a_i$ 的总和。

```cpp
for(int i=1;i<n;i++){
	if(a[i]>a[i+1]){
		sum+=(a[i]-a[i+1]);
		maxn=max(maxn,a[i]-a[i+1]);
		a[i+1]=a[i];
	}
}
```
记得判断 $a$ 数组是否已经符合题目要求，如果已经符合就直接输出 $0$，而且要开 long long。

---

## 作者：yangdezuo (赞：0)

## 题意
当 $a_i$ 小于 $a_{i-1}$ 时，要把 $a_i$ 增加到 $a_{i-1}$，也就是前面最大的那个数。

最后输出的答案既是每次增加的量加上最大增加的量。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗 
using namespace std;
int t,n,a[100005],y;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
    	cin>>n;
    	bool f=true;
    	for(int i=1;i<=n;i++){
    		cin>>a[i];
    		if(a[i]<a[i-1]) f=false;//判断是否递增 
		}
    	if(f){//特判，但其实没用 
    		cout<<0<<endl;
    		continue;
		}
    	int ans=0,x=0,maxx=0;
    	for(int i=1;i<=n;i++){
    		ans+=max(y,maxx-a[i]);//max里的数的类型要相同！ 
    		x=max(x,maxx-a[i]);//记录最大操作 
    		maxx=max(maxx,a[i]);//记录目前的最大数 
		}
		cout<<ans+x<<endl;//输出硬币 
    }
}
/*

*/
```

---

## 作者：junee (赞：0)

# CF1987B 题解

## 题目分析

如果一个数小于前面的最大数，那么他就要增长到这个最大数。否则就更新一下最大数，轮数即为最大数与此数差值的最大值。

答案即为每个数的最大数与该数的差值加上差值最大。

## Code

```cpp
#include<iostream>
#include<cstring>
using namespace std;
typedef long long LL;
const int N=1e5+10;
LL a[N],T,n,maxn[N];
int main(){
    cin>>T;
    while(T--){
        memset(maxn,0,sizeof maxn);
        LL ans=0,res=0;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        if(n==1){
            cout<<0<<'\n';
            continue;
        }
        maxn[1]=a[1];
        for(int i=2;i<=n;i++){
            if(a[i]<=maxn[i-1])maxn[i]=maxn[i-1];
            else maxn[i]=a[i];
        }
        for(int i=1;i<=n;i++){
            ans=max(maxn[i]-a[i],ans);
            res+=maxn[i]-a[i];
        }
        cout<<ans+res<<'\n';
    }
}
```

---

