# Hot Days

## 题目描述

### 题意简述
$A$ 地和 $B$ 地由一条贯穿 $n$ 个区域的公路连接起来。每个区域都有独特的气候，所以第 $i$  $\left(1\le i \le n\right)$ 个区域的夏季气温会稳定在 $t_i$ 度。

有 $m$ 个学生要从 $A$ 地到 $B$ 地去旅游，他们乘坐大巴车旅游，但巴士内的温度会随地区与车内人数的变化而变化，行驶在第 $i$ 个地区的温度为 $t_i+k$ ( $k$ 为车内人数)，但当车内温度超过 $T_i$ 时，学生会要求组织旅行的人赔偿，需赔偿每人 $x_i$ 元。

组织者需要在每个地区**都**购买任意数量公交车以完成旅行，且他们可以分配孩子到公交车上，分配不需要代价，在第 $i$ 个地区买一辆公交车需 $cost_i$ 。

## 样例 #1

### 输入

```
2 10
30 35 1 100
20 35 10 10
```

### 输出

```
120
```

## 样例 #2

### 输入

```
3 100
10 30 1000 1
5 10 1000 3
10 40 1000 100000
```

### 输出

```
200065
```

# 题解

## 作者：Y_zhao111 (赞：5)

> **You can go and read the [English version](https://www.luogu.com.cn/article/pl0ey9sk) of this solution.**

### Description

题目传送门：[CF215D Hot Days](http://codeforces.com/problemset/problem/215/D)。

有 $n$ 个地区和 $m$ 个学生，在第 $i$ 个地区时，车上有 $k_{i}$ 个学生，车内温度（当前城市的温度 $t_i$ $+$ 当前车上的学生 $k_{i}$）不能超过 $t_{i}$，否则，赔偿每个学生 $x_{i}$ 元，没经过一个地方，要花费 $cost_{i}$ 元，求通过 $n$ 个地区所需要的最少花费（车上可以坐无限多的人，每经过一个地方，学生可以不坐在车上）。

显然易见是到贪心题目。

### Analysis

贪两种：

+ 我们一块钱都不赔。
> 租的大巴车数量为 $S1$，那么数量就是 $S1=\lceil\dfrac{m}{T_{i} - t_{i}}\rceil$。
>
> 该方案花的钱数为 $MS1$，钱数为 $S1\times cost_{i}$。

+ 我们只租一辆大巴车。
> 只租一辆车，那么我们要赔偿 $S2$ 元，$S2 = m\times x_{i}$ 元。
> 
> 该方案花的钱数为 $MS2$，是 $S2 + cost_{i}$。

最后 $Ans = \min{(MS1,MS2)}$。

**特殊情况**：当 $T_{i}\le t_{i}$ 的时候，无论如何都必须要赔钱，**考虑最小，只能租一辆，见上面的第二种方法**。

相乘会爆 $10^{9}$，记得开 `long long`，**而且相乘的时候一定要强制性转换成** `long long` **类型**。

时间复杂度 $\mathcal{O}{(n)}$。

### Code

```cpp
#include <bits/stdc++.h>

using ll = long long;
using namespace std;

int main()
{
	ll n , m , sum = 0;
	cin >> n >> m;
	
	for(int i = 1 ; i <= n ; i ++)
	{
		ll t , T , x , cost;
		cin >> t >> T >> x >> cost;
		
		if(T <= t)
			sum += cost + m * x;
		
		else
			sum += min((ll)(ceil(1.0 * m / (T - t)) * cost) , (cost + m * x));
	}
	
	cout << sum << endl;
	return 0;
}
```

---

## 作者：szh_AK_all (赞：2)

在决斗中通过了本题。

## 分析
由于当温度超标时，对每个人的赔偿一定，所以对于每个地区 $i$，有两种选择：

- 交车费，不赔偿，需要购买的车的数量至少为 $p=\lceil \frac{m}{T_i-t_i}\rceil$，注意到此时应满足 $T_i>t_i$，否则，需要且仅需要租一辆车。这种情况的花费为 $p\times cost_i$。

- 赔偿，不过此时仍需交一辆车子的车费。此时可以默认温度超标，否则最优情况会被上面那种情况考虑掉。这种情况的花费为 $cost_i+m\times x_i$。

答案取两种情况最小值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t[100005], T[100005], x[100005], a[100005];

signed main() {
	int n, m;
	cin >> n >> m;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> t[i] >> T[i] >> x[i] >> a[i];
		int k = a[i] + m * x[i];
		if (T[i] <= t[i])
			ans += k;
		else {
			int p = ceil(m * 1.0 / (T[i] - t[i])) * a[i];
			ans += min(p, k);
		}
	}
	cout << ans;
}
```

---

## 作者：xf20280111 (赞：1)

我的代码在 Codeforces 上已经通过。

***

## 题目分析
虽然有 $n$ 个地方，每个地方其实是相互独立的，因为要重新买公交车。所以就分为了 $n$ 个子问题，答案就是所有子问题答案之和。

## 思路

观察数据范围，我们可以想到贪心，怎么贪？

两种贪心策略：

- 只交罚金，注意：此时也需要租一辆车。
  
- 不交罚金，而且还要使租的车尽可能少并且温度尽可能靠近 $T_{i}$。

第一种策略的花费是 $m \times x_{i} + cost_{i}$。

第二种策略的花费是 $\lceil \frac{m}{T_{i} - t_{i}} \rceil + cost_{i}$。

这两种策略得到的结果我们取最小值即可。

还需要考虑一种特殊情况，就是肯定会赔钱的情况，即 $T_ {i} \leq t_ {i}$，由公式我们可以发现 $T_ {i} - t_ {i} \leq 0 $，最后得到的总钱数就成负数了，取最小值时就会出错，所以要单独考虑。

最后，注意开 `long long` 哟。

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N = 100000 + 10;
long long t[N],T[N],x[N],cost[N];
long long n,m;
long long sum = 0;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (long long i = 1;i <= n;i++){
		cin >> t[i] >> T[i] >> x[i] >> cost[i];
	}
	for (long long i = 1;i <= n;i++){
		long long k = cost[i] + m * x[i];
		long long kk = ceil(1.0 * m / (T[i] - t[i])) * cost[i];//为什么要向上取整？剩下的人也是需要单独一辆车的
		if (T[i] <= t[i]) sum += k;
		else sum += min(k,kk);//取最小值
	}
	cout << sum << "\n"; 
	return 0;
}
```

代码的时间复杂度为 $\mathcal{O}(n)$。

---

## 作者：tonyre (赞：1)

# CF215D 题解

## 1 题面

洛谷上的[翻译](https://www.luogu.com.cn/problem/CF215D)非常良心，需要注意到每一个站点都需要重新租大巴车，而且大巴车的容量是无限大的。

## 2 题解

### 2.1 分析

很容易看出来，本题各个站点互不相关。求出每一个站点的最小花费就可以求出总最小花费，也就是贪心。

已知有 $m$ 个学生，给定 $t_i,T_i,x_i,cost_i$，接下来考虑最小花费。

首先找到一种特殊情况：

* 若 $T\le t$，无论如何都需要赔钱，所以只买一辆车，再赔 $mx_i$，最小花费即 $cost_i+mx_i$。

对于其它情况，有两种安排方法：

* 一块钱不赔。则需要租 $\lceil\dfrac{m}{T-t}\rceil$ 大巴车，所以该方案花费 $a=\lceil\dfrac{m}{T-t}\rceil\times cost_i$。
* 只租一辆大巴车。则需要赔 $mx_i$，所以该方案花费 $b=cost_i+mx_i$。

则该站点的最小花费为 $\min(a,b)$。

### 2.2 实现

按照上述做法，时间复杂度 $O(n)$。由于 $1\le n\le 10^5$，所以可以通过。

**注意开 `long long`。**

## 3 代码

```c++
#include<iostream>
#include<cmath>
#define int long long//不开 long long 见祖宗
using namespace std;
signed main()
{
    int n,m;
    cin>>n>>m;
    int tot=0;
    for(int i=1;i<=n;i++)
    {
        int t,T,x,cost;
        cin>>t>>T>>x>>cost;
        if(T<=t) tot+=cost+m*x;//特殊情况
        else
        {
            int a=ceil(1.0*m/(T-t))*cost;
            int b=cost+m*x;
            tot+=min(a,b);
        }
    }
    cout<<tot<<endl;
    return 0;
}
```



---

## 作者：wkjwkj (赞：1)

对于这道题目，我们可以采用贪心的策略来解决。

首先很容易证明，每个地区之间的决策是互相独立的，不会相互影响，因为你在每个地区都需重新购买公交车。

因此，接下来我们便可以直接考虑单个地区的方案。而单个地区的决策是明显的，若有一辆车温度低于 $T_i$ 度，而此时有另一辆车温度高于 $T_i$ 度，那么显然将温度高的车上的人安排到温度低的车上去更优，因为这时在购买公交车上的花费不变，而在罚金上的花费则会变少，故我们应该在只买一辆车和尽量将每辆车的温度都卡到 $T_i$ 度的花费上做出决策。

下面给出代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
ll ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int t,T,x,cost;
		scanf("%d%d%d%d",&t,&T,&x,&cost);
		if(T<=t)ans+=(ll)x*m+cost;
		else if(t+m<=T){
			ans+=cost;
			continue;
		}
		else{
			ll res=(ll)x*m+cost;
			res=min(res,(ll)ceil(m*1.0/(T-t))*cost);
			ans+=res;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：ZJle (赞：0)

### CF评分：1900
#### tags：greedy（贪心）
感觉这题评绿还是太高了。

纯粹就是加减数题，贪心只要把一个地区是交罚单的钱还是买车的钱取 $\min$ 再加就行了。

注意：如果 $(T\leq t)$ 的时候，只用租一辆车，其他全交罚单就行了（交罚单的总量不变，但是如果租的越多需要的代价越高）。

$$
ans=ans+
\begin{cases}
m\times x_i+cost_i(t\leq T)\\
\min(\frac{m}{t_i-T_i}\times x_i,x_i\times m+d)(t> T)
\end{cases}
$$
### 代码 （记得开 long long）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void file(){
   ios::sync_with_stdio(false);
   cin.tie(0),cout.tie(0);
}int m,T,ans=0;
auto main() ->signed{
    file();
    cin>>T>>m;
    while(T--){
        int z,t,x,d;
        cin>>z>>t>>x>>d;
        if(t<=z){
            ans+=(d+m*x);
        }
        else {int op=ceil(1.0*(m)/(t-z))*d;
        ans+=min(op,x*m+d);}
        // cout<<ans<<endl;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：AstaSunch_ (赞：0)

# 0x00 前言
蒟蒻的第 $\color{red}{\mathbf{17}}$ 篇题解。
# 0x10 题面
[Link](https://www.luogu.com.cn/problem/CF215D)
# 0x20 方法
很明显，一看就知道是贪心。

在每个地区，我们都最小化当前地区的总费用，由此得到整个旅行的最小费用。在每个地区之间有独立性，因为每个地区的费用不会影响其他地区的费用。

## 0x21 模拟过程

初始化总费用 $y$ 为 $0$。

遍历每个地区：

- 首先计算在不支付赔偿费用的情况下，可以容纳的最大学生数量 $k$，即 $T - t$。

- 然后，可以计算在这个地区至少需要购买的公交车数量 $b$，即 $\lceil\frac{m}{k}\rceil$。

- 通过比较购买 $b$ 辆公交车和购买 $b-1$ 辆公交车再支付赔偿费用的总费用，我们可以选择较小的那个。即 $\min(b \cdot cost_i, (b - 1)cost_i + mx_i)$。

- 累加（将这个地区的最小费用累加到 $y$ 中）。

- 输出。

## 0x22 注意事项

- 累加可能会爆 `int`，记得开 `long long`。
- 如果 $T\leqslant t$，则无论如何都要赔钱，因此只能买一辆车，花费 $mx_i$，总费用即 $cost_i+mx_i$。
- 时间复杂度 $\Theta(n)$，可通过。
# 0x30 Code
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int main(){
    ll n,m,sum=0;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        ll t,T,x,c;
        cin>>t>>T>>x>>c;
        if(T<=t) sum+=c+m*x;
		else sum+=min(ll(ceil(1.0*m/(T-t))*c),(c+m*x));
    }
    cout<<sum<<endl;
}
```



---

