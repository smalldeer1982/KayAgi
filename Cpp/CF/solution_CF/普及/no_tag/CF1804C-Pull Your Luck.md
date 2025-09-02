# Pull Your Luck

## 题目描述

While James is gone on business, Vesper takes her time and explores what the legendary Casino Royale has to offer to people who are fond of competitive programming.

Her attention was grabbed by the very new "Pull Your Luck" roulette which functions in a pretty peculiar way. The roulette's wheel consists of $ n $ sectors number from $ 0 $ to $ n - 1 $ . There is no ball and the winning sector is determined by a static arrow pointing to one of the sectors. Sectors' indexes go in the natural order and the wheel always spins in the direction of indexes increment. That means that sector $ i + 1 $ goes right after sector $ i $ for all $ i $ from $ 0 $ to $ n - 2 $ , and sector $ 0 $ goes right after sector $ n - 1 $ .

After a bet is made, the player is allowed to pull the triggering handle herself and cause the wheel to spin. If the player's initial pull is made with the force equal to positive integer $ f $ , the wheel will spin for $ f $ seconds. During the first second it will advance $ f $ sectors, the next second it will advance $ f - 1 $ sectors, then $ f - 2 $ sectors, and so on until it comes to a complete stop. After the wheel comes to a complete stop, the sector which the arrow is pointing to is the winning one.

The roulette's arrow currently points at sector $ x $ . Vesper knows that she can pull the handle with any integer force from $ 1 $ to $ p $ inclusive. Note that it is not allowed to pull the handle with force $ 0 $ , i. e. not pull it all. The biggest prize is awarded if the winning sector is $ 0 $ . Now Vesper wonders if she can make sector $ 0 $ win by pulling the triggering handle exactly once?

## 说明/提示

In the first example, the only possible way to pull the handle is with force $ 1 $ . That is not enough to make the arrow point at sector $ 0 $ , at least force $ 2 $ is required to do so.

In the second example, Vesper can pull the handle with the force $ 2 $ so the wheel will spin $ 2 + 1 = 3 $ sectors ahead and the arrow will point at sector $ 0 $ .

In the third example, Vesper can pull the handle with the force $ 4 $ so the wheel will spin $ 4 + 3 + 2 + 1 = 10 $ sectors and will point at sector $ 0 $ again.

In the fourth example, Vesper can pull the handle with the force $ 5 $ so the wheel will spin $ 5 + 4 + 3 + 2 + 1 = 15 $ sectors. That will make the wheel make one full turn plus $ 4 $ more sectors.

In the fifth example, whatever force Vesper chooses to pull the handle with, she can only make sectors $ 1 $ and $ 2 $ win.

## 样例 #1

### 输入

```
7
5 2 1
5 2 2
10 0 100
11 7 100
3 1 1000
31 0 10
100 49 7```

### 输出

```
No
Yes
Yes
Yes
No
No
No```

# 题解

## 作者：LOVE_Ynoi (赞：6)

### 形式化题意
- 给定三个正整数 $n,x,p$。
- 求一个正整数 $0 < a \le p$ 使得 $(x +\sum_{i=1}^{a}i) \bmod n = 0$。
- $1 \le p \le 10^9 , 1\le \sum n \le 2\times10^5$


### 题目解析


对于暴力，我们可以从 $1$ 到 $p$ 枚举 $a$。

但是我们需要一个复杂度为 $O(n)$ 的算法。

注意到当 $a = 2n$ 时：

$\sum_{i=1}^{a}i = \dfrac{2n(2n+1)}{2} = 2n^2+n = n(2n + 1)$，为 $n$ 的倍数。

所以当操作数 $a = 2n$ 时，$(x + \sum_{i=1}^{a}i) \bmod n = x \bmod n$。

即当 $a = 2n$ 开始，转盘的指针指向的位置开始循环。

由此我们只需要从 $1$ 到 $\min(2n,p)$ 枚举 $a$，逐个验证即可。

时间复杂度 $O(n)$。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,w,m;
int a[200010];
void solve(){
    cin>>n>>k>>w;
    int t = 0;
    for(int i = 1;i<=min(2 * n,w);i++){
        t += i;
        if((k + t) % n == 0){
            cout<<"YES"<<endl;
            return;
        } 
    }
    cout<<"NO"<<endl;
}
signed main(){
    int _;
    cin>>_;
    while(_--){
        solve();
    }
    return 0;
}
```

---

## 作者：Withershine (赞：5)

翻译清晰，这里就不吐槽了。

根据轮盘转动的方法，可以看出这是一个简单的[高斯求和](https://baijiahao.baidu.com/s?id=1744730383586891590&wfr=spider&for=pc)。

因为这是一个轮盘，在轮盘中转动了 $now$ 个格子与转动了 $now \bmod n$ 所到达的格子是一样的（这就没必要证明了吧），因此我们很容易就能得到一个最朴素的代码：

```cpp
	cin >> T;
	while(T--)
	{
		cin >> n >> x >> p;
		ll flag = 0;
		fr(i , 1 , p)
		{
			ll now = (1 + i) * i / 2;
			if((x + now) % n == 0)
			{
				printf("Yes\n");
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			printf("No\n");
		}
	}
```
然后非常愉快地在第二个点超时。

回看数据才发现 $p \le 10^9$……

我们要解决的其实就是 $p$ 的上界，下界没得商量，从 $1$ 开始。

不妨多出几组小数据模拟一下就会发现，$p$ 的上界与 $n$ 貌似有点关系，当 $p$ 超过某个值时，所能到达的格子便会开始陷入循环，只要找出这个值就解决问题了。

先列一个长度大于 $n$ 的三倍的序列：

$\displaystyle \frac{1 \times (1+1)}{2}$，
$\displaystyle \frac{2 \times (2+1)}{2}$
……
$\displaystyle \frac{n \times (n+1)}{2}$，
……
$\displaystyle \frac{2n \times (2n+1)}{2}$，
……
$\displaystyle \frac{3n \times (3n+1)}{2}$……

这个序列其实就表示移动的步数，表示最终位置需要化简并对 $n$ 取模，得到通项公项：

$\displaystyle \frac{hi \times (hi+1)}{2} \bmod n$，其中 $1 \le i \le n$，$h \in N$。

~~用来表示的字母没有特殊意义，不要追问 doge。~~

接下来只要找到最小的 $h$ 满足 $\displaystyle \frac{hi \times (hi+1)}{2} \bmod n=\displaystyle \frac{i \times (i+1)}{2} \bmod n$ 即可。

设存在一个数 $k$，使 $\displaystyle \frac{ki \times (ki+1)}{2} \bmod n=\displaystyle \frac{i \times (i+1)}{2} \bmod n$，其中 $1 \le i \le n$，在解出 $k$ 后，$p$ 的上界也可以确定。（其实 $k$ 就是上面的 $h$）

解出 $k$ 为大于 $0$ 的 $n$ 的偶数倍。所以 $p$ 就只需要取 $n$ 的偶数倍就行了。$k$ 表示的其实就是能完成从 $0$ 到 $n-1$ 循环的数。

但是以上所有情况都是建立在一开始从零号位开始并且至少使用一点力气的情况下。实际上并不一定是从零开始，在通过上述方式算出 $p$ 后，减去初始的格子位置，也是题目中的 $x$，才最符合推理。（其实减不减去 $x$ 都无所谓，只是减去后会严谨一点）

如果 $p$ 本身就很小的话，也没有必要更新它的值。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define mod 1e9 + 7
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i) //-(~i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i) //~(-i)
using namespace std;
inline ll QuickPow(ll a , ll b)
{
	if(b == 0)
	{
		return 1;
	}
	ll k = QuickPow(a , b >> 1);
	if(b & 1)
	{
		return k * k * a;
	}
	return k * k;
}
ll T , n , x , p;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n >> x >> p;
		ll flag = 0;
		fr(i , 1 , min(p , 2 * n - x))
		{
			ll now = (1 + i) * i / 2;
			if((x + now) % n == 0)
			{
				cout << "Yes" << '\n'; 
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			cout << "No" << '\n';
		}
	}
	return 0;
}
```


---

## 作者：_GJM_ (赞：3)

###### [更好的阅读体验？](https://www.luogu.com.cn/blog/GeJiamu/solution-cf1804c)

## 题意
给出 $n$、$x$、$p$，判断是否存在一个 $f(1 \le f \le p)$，使得 $x + \frac{f(f+1)}{2}$ 是 $n$ 的倍数。

## 思路
看到 $(1 \le p \le 10^9)$ 就知道直接遍历会 **TLE**。

所以，我们得**优化**。

不难发现，如果你的力气 $= 2 \times n + x$，那么和使出  $x$ 的力气得到的结果是一样的。

所以，遍历的范围是 $1$ 到 $\min (p,2 \times n)$。

## [AC Code](https://www.luogu.com.cn/paste/u4j05lwc)


---

## 作者：shiyihang (赞：2)

### 题意

给定 $n$，$x$，$p$，询问是否有一个 $1 \le k \le p$，使得 $\sum_{i = 1}^{k}{i} \equiv n - x \ (\bmod \ n)$。

### 分析

首先考虑暴力做法，可以想到定义 $t = 0$ 和 $cnt$（从一开始递增），然后进行一个循环，每次将 $t$ 减去一个 $cnt$ 再对 $n$ 求余（注意不是 `t%n`， 而是 `(t%n+n)%n`），判断该变量是否与 $x$ 相等。

然后观察样例一中的第五组数据，发现虽然 $p$ 很大，却无法让 $t$ 推到 $x = 1$ 的位置，大胆猜测一下对于递增的 $k$，原式中存在循环节。

但是手推一下第五组数据会发现，$t$ 的规律是这样的：

```plain
0 2 0 0 2 0 0 2 0 ...
```

显然，$t$ 重复并不一定代表后面不会更新到其他的位置，但如果在 $t$ 重复的同时 $cnt \bmod n$ 也发生了重复，则显然无法对其他的位置进行更新了（因为以前已经更新过了）。

现在考虑对于暴力进行一定的优化，如果当前枚举的 $t$ 和 $cnt \bmod n$ 在之前已经出现过的话，就直接退出，不可能枚举到 $x$ 的位置了。  
期望复杂度为 $O(n)$，在本地进行测试发现循环节长度不超过 $2 \times n$，所以可以通过本题。

代码如下：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
int T;
int n, x, p;
set<int> vis[200005];
int main()
{
    cin >> T;
    while (T--) {
        cin >> n >> x >> p;
        for (int i = 0; i < n; ++i) {
            vis[i].clear();
        }
        int cnt = 1, now = n - 1;
        while (cnt < p && now != x) {
            vis[now].insert(cnt % n);
            ++cnt;
            now = ((now - cnt) % n + n) % n;
            // cout << cnt << " " << now << endl;
            if (vis[now].find(cnt % n) != vis[now].end()) {
                break;
            }
        }
        if (now == x) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}
```

PS： 由于使用了 stl 中的 set，代码常数较大，可以考虑换用哈希表等其他数据结构。 ~~（也许能被 Hack? ）~~  


---

## 作者：huangmingyi (赞：0)

### 题目思路
方法一：  
1. 枚举每一种方案，从 $1$ 枚举到 $q$ 再枚举 $1$ 到 $i$ 求和。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
signed main(){
	cin>>T;
	while(T--){
		int n,x,p;
		bool f=0;
		cin>>n>>x>>p;
		for(int i=1;i<=p;i++){
			int r;
			for(int j=1;j<=i;j++){
				r+=j;
			}
			if((r+x)%n==0){
				cout<<"Yes";
				f=1;
				break;
			}
		}
		if(!f){
			cout<<"No";
		}
		cout<<endl;
	}
}
```

~~超时~~。  
2. 剪枝，用高斯求和来少一个循环（公式就不讲了）。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
signed main(){
	cin>>T;
	while(T--){
		int n,x,p;
		bool f=0;
		cin>>n>>x>>p;
		for(int i=1;i<=p;i++){
			int r=(i+1)*i/2;
			if((r+x)%n==0){
				cout<<"Yes";
				f=1;
				break;
			}
		}
		if(!f){
			cout<<"No";
		}
		cout<<endl;
	}
}
```

~~又在同一个地方 TLE 了，这方法成功的失败了~~。

方法二：结论来自 LOVE_Ynoi。
注意到当 $a = 2 \times n$ 时：   
 $ \sum_{i=1}^n i=\frac{2 \times n \times (2 \times n + 1)}{2} = n \times (2 \times n + 1)$ 为 $n$ 的倍数。由此我们只需要从 $1$ 到 $\min(2 \times n,p)$ 枚举 $a$，逐个验证即可。
 
 ```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,p;
signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>x>>p;
	    int sum=0;
	    bool f=0;
	    for(int i=1;i<=min(2*n,p);i++){
	        sum+=i;
	        if((x+sum)%n== 0){
	            cout<<"Yes";
	            f=1;
	            break;
	        } 
	    }
	    if(!f){
	    	cout<<"No";
	    }
	    cout<<endl;
    }
    return 0;
}
```


---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF1804C)
## 题意：
一个转盘有 $n$ 个格子分别为 $0 1 2 \cdots n-1$，初始时在 $x$ 号格子，你希望转动一次转盘来使它回到 $0$ 号位置，（转盘转到 $n-1$ 后再转就会回到 $0$）。

你有一个可以使出的最大力气 $p$，你可以使出任意的力气 $f$ 满足 $f \le p$。然后，转盘会转动 $f$ 秒，第一秒转动 $f$ 个格子，第二秒转动 $f-1$  个格子，以此类推，第 $f$ 秒就会转动 $1$ 个格子，之后转盘就会停止转动。

现在给你 $n$，$x$，$p$，请你判断能否使出一次一个力气 $f$，使得转盘能够转到 $0$ 号格子，$T$ 组数据，用 ```No``` 和 ```Yes``` 回答
## 思路：
我们先看用 $f$ 个力气一共转了多少格，很简单为 $1+2+3+\cdots+(f-1)+f$,化简得 $\frac{f \cdot (f+1)}{2}$

如果你的力气 $=2 \cdot n+x$，那么和使出 $x$ 的力气得到的结果是一样的。，那么每次询问，我们只需循环到 $\min(2\cdot n,p)$ 即可。
## Code:
```cpp
//非洛谷题_CodeForces_CF1804C_Pull Your Luck
#include<bits/stdc++.h>
#pragma GCC/*G++*/ optimize(1)
#pragma GCC/*G++*/ optimize(2)
#pragma GCC/*G++*/ optimize(3)
using namespace std;
long long t=0,n=0,x=0,p=0;
bool flag=0;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>x>>p;
        flag=0;
        for(long long i=1;i<=min(2*n,p);i++){
            if(((i+1)*i/2)%n==(n-x)%n){
                cout<<"Yes\n";
                flag=1;
                break;
            }
        }
        if(!flag){
          cout<<"No\n";
        }
    }
    return 0;
}
```

---

## 作者：Not_defined (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1804C)
### 题目简化
判断是否存在一个 $f$，满足 $1\le f\le p$，使得 $x+\frac{f(f+1)}{2}$ 是 $n$ 的倍数，存在则输出 $\texttt Yes$，不存在则输出 $\texttt No$。
### 本题思路
本题很显然是模拟，但是一看数据范围暴力会 T，所以我们要思考可不可以省去一些不必要的部分，因此自然而然想到返回原点时，此时 $f=2 \times n$。
### 证明
根据等差数列求和公式可以求得可以经过  $\frac{2n(2n+1)}{2}$ 格，很显然这是 $n$ 的倍数。
### My code
```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,x,p,sum;
bool flag;
signed main()
{
	cin>>T;
	while(T--)
	{
		flag=sum=0;
		cin>>n>>x>>p;
		for(int i=1;i<=min(p,n<<1);i++)
		{
			sum+=i;
			if((x+sum)%n==0)
			{
				puts("Yes");
				flag=1;
				break;
			}
		}
		if(!flag)puts("No");
	}
	return 0;
}
```





---

