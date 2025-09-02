# [SEERC 2019] Absolute Game

## 题目描述

Alice 和 Bob 在玩一个游戏。Alice 有一个包含 $n$ 个整数的数列 $a$，Bob 有一个包含 $n$ 个整数的数列 $b$。每一回合中，玩家需要从他的数列中删去一个数字。玩家轮流进行回合，Alice 先手。

当两个数列中都只剩下一个数字的时候，游戏结束。令 Alice 的数列剩下的数字为 $x$，Bob 的数列剩下的数字为 $y$。Alice 想要最大化 $x$ 与 $y$ 之差的绝对值，而 Bob 想最小化这个值。两个玩家都以最优策略游戏。

请算出游戏结束时的结果。

## 说明/提示

第一个样例中，$x=14, y=10$，因此两个数之差为 $4$。

第二个样例中，两个数列都只剩下一个数字了，因此 $x=14, y=42$。

## 样例 #1

### 输入

```
4
2 14 7 14
5 10 9 22```

### 输出

```
4```

## 样例 #2

### 输入

```
1
14
42```

### 输出

```
28```

# 题解

## 作者：Miraik (赞：11)

结论：这个游戏等价于 Alice 先选一个数 $x$，Bob 再选择一个数 $y$。

证明：从 Bob 的角度出发。首先 Alice 可以选择任意数结束游戏，所以 Bob 显然得不到更好的结果。接下来我们构造地证明，无论 $x$ 取何值，Bob 一定可以选到对应最优的 $y$。

对于 Alice 手里的每个数 $a_i$，我们求出满足 $\lvert a_i - b_j \rvert$ 最小的 $j$，记为 $c_i$。

考虑每次 Alice 扔掉了一个数 $a_x$，由于此时 Bob 手里比 Alice 手里多一个数，此时 Bob 手里里必然存在至少一个数字满足其不为任何 Alice 手里的数的对应 $c_i$。那么我们将其删去后，问题变成了一个规模为 $n-1$ 的子问题，且剩余 $c$ 数组完全不变。于是我们证明了，无论 Alice 选择哪个数 $a_x$，Bob 都可以选到对应的最优值 $b_{c_x}$。

由此我们得到本题做法：求出 $c$ 数组，输出其最大值即可。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
const int inf=1000000005;
int n,a[N],b[N],ans;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	sort(a+1,a+n+1); sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		int j=lower_bound(b+1,b+n+1,a[i])-b;
		int c=inf;
		if(j<=n) c=min(c,b[j]-a[i]);
		if(j>1) c=min(c,a[i]-b[j-1]);
		ans=max(ans,c);
	}	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：FjswYuzu (赞：9)

$\ \ \ \ \ \ \ $听说 luogu 新增加了 `ACM_ICPC` 的标签，于是赶过来做了一道看起来简单一点的。

$\ \ \ \ \ \ \ $这道题属于动脑袋类型的题。对于这道题，我们首先求出 $c_i$ 使得 $c_i=\min\{abs(a_i-b_j)\}$。我们现在“重排”，存在 $b_i$ 使得 $abs(a_i-b_i)=c_i$，也就是最小。那么我们现在 Alice 删除了 $a_i$，我们删除与之相对应的 $b_i$。

$\ \ \ \ \ \ \ $关键来了：为什么？

$\ \ \ \ \ \ \ $我们只有两种情况：数组 a 和数组 b 取最小值是否对应。

- 当 a 数组与 b 数组取最小值是一一对应时，我们知道 $b_i$ 是使 $a_i$ 为最小的所以去掉 $a_i$ 后，bi不会使得a数组中其他数的最小值变得更小，所以 Bob 此时去掉相应的 $b_i$。Alice 丢弃一个数时一定是将使得 $c_i$ 值最小的数去掉，到最后我们就会发现我们得到的值就是 $c_i$ 数组的中的最大值。

- 当 a 数组与 b 数组取最小值不是一一对应时，Alice 还是会去掉使得 $c_i$ 值最小的那一个 $a_i$，当存在 $a_i=a_j$ 时就说明会有一个 $b_k$ 不会使得任何一个 $a_i$ 最小，此时Bob就会去掉这个数 $b_k$，到最后得到的值还是 $c_i$ 数组中的最大值。

$\ \ \ \ \ \ \ $综上所述，我们的策略是正确的。证明来自[这里](https://www.cnblogs.com/bqyb/p/11966493.html)。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[1005],b[1005];
int Abs(int x){return x<0?-x:x;}
int main(){
	int ans=-1;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)	scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)
	{
		int tmp=2147483647;
		for(int j=1;j<=n;++j)	tmp=min(tmp,Abs(a[i]-b[j]));
		ans=max(ans,tmp);	
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：zhangzirui66 (赞：2)

**题意**

Alice 和 Bob 在序列中各选择一数，Alice 想让它们相差的绝对值最大，Bob 想让它们相差的绝对值最小，求它们的绝对值。

---
**思路**

两个人均以最优策略进行游戏，所以他们最后剩下的两个数也是最优的。那我们枚举 Alice 最后选择的所有数，Bob 枚举与其相差的绝对值最小的数，又因 Alice 要保证绝对值最大，所以再取一个最大值。

---

**代码：**
```cpp
#include<iostream>
using namespace std;
int a[1005], b[1005], ans = -2e9;
int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    for(int i = 1; i <= n; i ++) cin >> b[i];
    for(int i = 1; i <= n; i ++){
        int minn = 2e9;
        for(int j = 1; j <= n; j ++) minn = min(minn, abs(a[i] - b[j]));
        ans = max(ans, minn);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：nightwatch.ryan (赞：2)

### 题意
Alice 和 Bob 玩删数游戏，它们各有一个长度为 $n$ 的序列，最终两人各剩下一个数。Alice 需要将两人剩下的数差的绝对值最大，而 Bob 需要将两人剩下的数差的绝对值最小，两个人以最优策略进行游戏，求剩下的两个数差的绝对值。
### 思路
题目中提到，两个人均以最优策略进行游戏，所以他们最后剩下的两个数也应是最优的。那我们枚举 Alice 最后选择的所有数，Bob 需要找到与其绝对值相差最小的数，又因 Alice 要保证绝对值相差最大，所以要取一个最大值。
### 代码
```cpp
#include<iostream>
#include<cmath>
#include<algorithm> 
const int INF=1e9;
int alice[1005],bob[1005];
int main(){
	int n;
	std::cin>>n;
	for(int i=0;i<n;i++) std::cin>>alice[i];
	for(int i=0;i<n;i++) std::cin>>bob[i];
	int res=-INF,sum=0;
	for(int i=0;i<n;i++){
		sum=INF;
		for(int j=0;j<n;j++)
			sum=std::min(sum,abs(alice[i]-bob[j]));
		res=std::max(res,sum);
	}
	std::cout<<res;
}

```


---

## 作者：Zack_zhu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P5804)
## 前言  
一个比较~~友好~~的思维题  
## 题目描述  
$A$ 与 $B$ 玩一个删数游戏，两人各有 $n$ 个数，最终两人各剩下一个数。$A$ 要保证这两个数的差的绝对值最大，$B$ 要保证这两个数的差的绝对值最小，**两个人都以最优策略游戏**。求结果（两个数的差的绝对值）。  
## 题目分析  
其实这道题比较难想的地方我认为是删数的过程。因为最优策略游戏，所以剩下的两个数一定对两个人都是最优的，同样**因为最优策略游戏，所以我们不用考虑删数过程**，最后一定会剩下最优的**两个数**。  
这时候假设我们是 $A$ ,当我们拿出一个数后，$B$ 一定会拿出一个最接近的数来保证差值最小，所以我们枚举 $A$ 剩下的每个数，并找到 $B$ 剩下的最接近 $A$ 剩下的数，求一个最大值（因为 $A$ 要保证差最大）即可。  
其实 $O(n ^ 2)$ 是可以过的，但为了~~效率~~我选择 $O(n * \log n)$ 的二分做法，但要注意的点是最接近的不一定就小于等于那个数，所以还要比较后一位，因此我们又要注意防止越界，~~所以为什么不写 $O(n ^ 2)$ 的呢~~。  
## 代码  
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
int t,n,les;
int a[MAXN],b[MAXN];

template <typename T>
inline void read(T &s)
{
	s = 0;
	T w = 1;
	char ch = getchar();
	while(ch < '0'||ch > '9')
	{
		if(ch == '-')
		w = -1;
		ch = getchar();
	}
	while(ch >= '0'&&ch <= '9')
	{
		s = (s<<3)+(s<<1)+(ch^48);
		ch = getchar();
	}
	s *= w;
	return;
}

int main()
{
	read(n);
	for(int i = 1;i <= n;i++)
		read(a[i]);
	for(int i = 1;i <= n;i++)
		read(b[i]);
	sort(b+1,b+1+n);
	for(int i = 1;i <= n;i++)
	{
		int now = lower_bound(b+1,b+1+n,a[i]) - (b+1);//这里可以换成再跑一个 O(n) 找 B 的对应值 
		if(now > 0 && now + 1 <= n)
			les = max(min(abs(a[i]- b[now]),abs(a[i] - b[now+1])),les);
		else if(now > 0)
			les = max(les,abs(a[i]- b[now]));
		else if(now + 1 <= n)
			les = max(les,abs(a[i] - b[now+1]));
	}
	printf("%d\n",les);
	return 0;
}
```

---

## 作者：Tjaweiof (赞：1)

# P5804 题解——Tjaweiof
[题目传送门](https://www.luogu.com.cn/problem/P5804)

思考了一会后，发现暴力枚举每一种取法是不行的，因为这样会 TLE，但是暴力枚举最后的两个数是可以的。那么，问题来了，那应该选择哪两个数呢？于是我们想到这种方法：枚举 Alice 最后选择的每一个数，Bob 要找到与其差最小的，而 Alice 要在 Bob 算出的差中找出最大的，输出即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[1001], b[1001];
long long ans = -1, cnt;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++){
		cin >> b[i];
	}
	for (int i = 1; i <= n; i++){
		cnt = 0x3f3f3f3f;
		for (int j = 1; j <= n; j++){
			if (abs(a[i] - b[j]) < cnt){
				cnt = abs(a[i] - b[j]);
			}
		}
		if (cnt > ans){
			ans = cnt;
		}
	}
	printf("%lld", ans);
	return 0;
}
```
#### 此代码时间复杂度 $O(n^2)$，空间复杂度 $O(n)$，完美过关！

---

## 作者：Sirkey (赞：1)

这道题有点意思。

正解是由最小值去找最大值。

原理是：从 Alice 选数 $x$ 的最差方案。在最差方案中选一个最优的。

具体：Alice 选择数 $x$，而 Bob 选择所有可以选的数的数中的最差方案。在所以方案中找到最大的那个。

不难想到有另一种做法：从 Bob 选数 $x$ 的最差方案。在最差方案中选一个最优的。

这样做恰恰相反，是寻找最小值的最大值。

但是，第二种方案是不行的。

模拟一下，我们很明显就可以发现我们把第一组样例的答案忽略了。

根本原因是没有考虑到先手。

我们不可以从后手去考虑先手。这样是不对的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],b[1005],ans=0;
int main(){
	cin>>n;for(int i=1;i<=n;i++) cin>>a[i]; for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		int ans1=1e9;
		for(int j=1;j<=n;j++) ans1=min(ans1,abs(a[i]-b[j]));
		ans=max(ans1,ans);
	}
	cout<<ans;
        return 0;
}
```
——end——

---

## 作者：xht_37 (赞：0)

# 题解：P5804 [SEERC2019] Absolute Game

## 本题解法

### 解题过程

为了最小化 $x$ 与 $y$ 之差的绝对值，每次需要进行 $i$ 从 $1$ 到 $n$ 枚举，$j$ 从 $1$ 到 $n$ 的枚举，用 $res$ 记录 $x$ 与 $y$ 之差的绝对值的最小值，使 Bob 的策略最优，再用 $ans$ 记录每一次 $res$ 的最大值，使 Alice 策略最优，即求出正确答案。

### 注意事项

不能先记录 $res$ 的最大值，再记录 $res$ 的最小值，否则最小值会被先排除掉，从而得不到正确结果。

## 本题代码

代码很简单，完成需要的几个操作即可。

```cpp
#include <iostream>
#include <algorithm> // max()函数和min()函数
#include <cmath> // abs()函数
const int N = 1050;
int main() {
	int n;
	std::cin >> n;
	int a[N] = {}, b[N] = {};
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		std::cin >> b[i];
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int res = 1e9 + 50; // 初始化为最大值
		for (int j = 1; j <= n; j++) {
			res = std::min(res, std::abs(a[i] - b[j]));
			// 记录 x 与 y 的绝对值的最小值
		}
		ans = std::max(ans, res); // 记录 sum 的最大值
	}
	std::cout << ans;
	return 0;
}
```

---

## 作者：_Above_the_clouds_ (赞：0)

# 思路：
为了最小化 $x$ 与 $y$ 之差的绝对值，每次 $i$ 从 $1$ 到 $n$ 枚举，$j$ 从 $1$ 到 $n$ 枚举，用 $sum$ 记录 $x$ 与 $y$ 之差的绝对值的最小值，使Bob的策略最优，再用 $ans$ 记录 $sum$ 的最大值，使Alice策略最优，最后输出。（注：不能先记录最大值，再记录最小值，否则，最小值会被先排除掉，从而得不到最优解。）

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,ans;
int x[1005],y[1005];
int main() {
	scanf("%d",&n);//输入
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);
	for(int i=1;i<=n;i++) scanf("%d",&y[i]);
	for(int i=1;i<=n;i++){
		sum=2e9;//初始化为最大值
		for(int j=1;j<=n;j++) sum=min(sum,abs(x[i]-y[j]));//记录x与y的绝对值的最小值
		ans=max(ans,sum);//记录sum的最大值
	}
	printf("%d",ans);//输出
	return 0;
}
```


---

## 作者：lqsy002 (赞：0)

## 题目大意
[题目链接](https://www.luogu.com.cn/problem/P5804)。
## 解题思路
不管怎么找都会剩一个，既然如此就直接选一个留下来，每个数找一遍就行了，这个数满足的要求就是 $b$ 组和它最近的两个数的最小绝对值在所有数中最大。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,now;
long long ans,a[1005],b[1005];
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++) 
		scanf("%d",&a[i]);
	for(int i=1;i<=t;i++) 
		scanf("%d",&b[i]);
	sort(b+1,b+t+1);
	for(int i=1;i<=t;i++){
		now=lower_bound(b+1,b+t+1,a[i])-b;
		if(now==1)
			ans=max(ans,b[now]-a[i]);
		else if(now>1&&now<=t){
			if(ans<b[now]-a[i]&&ans<a[i]-b[now-1]) 
				ans=min(b[now]-a[i],a[i]-b[now-1]);
		}
		else if(now>t)
			ans=max(ans,a[i]-b[now-1]);
	}
	printf("%d",ans);
	return 0;
}
```

---

