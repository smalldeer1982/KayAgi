# Potions (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ n \leq 2000 $ . You can make hacks only if both versions of the problem are solved.

There are $ n $ potions in a line, with potion $ 1 $ on the far left and potion $ n $ on the far right. Each potion will increase your health by $ a_i $ when drunk. $ a_i $ can be negative, meaning that potion will decrease will health.

You start with $ 0 $ health and you will walk from left to right, from first potion to the last one. At each potion, you may choose to drink it or ignore it. You must ensure that your health is always non-negative.

What is the largest number of potions you can drink?

## 说明/提示

For the sample, you can drink $ 5 $ potions by taking potions $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ and $ 6 $ . It is not possible to drink all $ 6 $ potions because your health will go negative at some point

## 样例 #1

### 输入

```
6
4 -4 1 -3 1 -3```

### 输出

```
5```

# 题解

## 作者：Hilte (赞：5)

# 一.算法选择
- 这道题可以使用DP，也可以用贪心。
- 但是DP的时间复杂度为 $O(n^2)$ ，而贪心只有 $O(n\log n)$ 。
- 所以我们最好使用贪心。

# 二.思路
~~众所周知~~，如果想要喝多点药的话，那么就要拼劲全力去喝。  
**但是**，如果在这道题中喝药喝死了，我们就要将它~~WA的一声~~**吐出来**

1. 设置一个**优先队列** $\mathbf{Q}$ ,按照**从小到大**的顺序出队。
2. 每喝一瓶药就将它压入 $\mathbf{Q}$ 。
3. 如果凉了，就将 $\mathbf{Q}$ 里最小的药吐出来，并设置少喝一瓶药

# 三.代码

```cpp
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
priority_queue<ll,vector<ll>,greater<ll> > q;//从小到大
ll a[200001];

int main()
{
	ll n,cur=1,ans=0,tot=0;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	ans=n;//答案
	while(cur<=n)//没有喝到n瓶药
	{
		tot+=a[cur];//将血量增加a[i]
		q.push(a[cur]);//压入Q
		if(tot<0)//如果凉了
		{
			tot-=q.top();//反（后）悔一次，不喝这瓶药
			q.pop();
			ans--;//少喝一瓶药
		}
		cur++;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Morax2022 (赞：2)

# CF1526C1 题解
思路

本题要求喝的药越多越好，所以我们可以假设每瓶都喝，但如果喝这瓶药导致了死亡，就选择先喝此药，后将答案减一并将毒性最大的药吐出来，最后加回体力。

那如何实现呢？

可以构造一个大根堆，每喝一瓶药就存进大根堆里，当喝死时就将队首弹出，而此时的队首一定是最毒的，将此瓶消耗你的体力再加回就行了。

# AC Code
```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
priority_queue<ll, vector<ll>, greater<ll> >q;//大根堆 
ll a[200001], n, cnt = 0, ans = 0, tot = 0;
int main()
{
	cin >> n;
	for(ll i = 1; i <= n; i++) cin >> a[i];
	ans = n;//假设全喝 
	while(cnt <= n)
	{
		cnt++;
		tot += a[cnt];//来了就喝 
		q.push(a[cnt]);
		if(tot < 0)//喝死了 
		{
			tot -= q.top(); q.pop();//弹出最毒的并加回体力 
			ans--;//因为假设全喝，现在吐出一瓶，故减一 
		}
	}
	cout << ans;
}
```
希望本题解能给大家带来帮助！

---

## 作者：songge888 (赞：1)

## 前置知识：01 背包

给定 $n$ 种物品和一背包。物品 $i$ 的重量是 $w_i$，价值是 $v_i$，背包的容量为 $c$。  
对于每种物品 $i$ 只有两种选择，装入或者不装入。  
则第 $i$ 个物品，背包的重量为 $j$ 时，可以得到状态转移方程：
$$DP_{i,j}=\max (DP_{i-1,j},DP_{i-1,j-w_i}+v_i)$$

## 题意

给你一个长度为 $n$ 的序列 $A$，要求你找出最长的一个**子序列**使得这个子序列任意前缀和都非负。

## 思路
观察到数据范围 $n \le 2000$，并且对于每瓶药水，只有**喝**和**不喝**两种选择，可以想到用 **01 背包**来做，$j$ 表示喝了 $j$ 瓶药，$DP_j$表示喝了 $j$ 瓶药后的健康值，其中：
$$DP_j=\max(DP_{j-1}+a_i,DP_j)$$ 
最后从后往前遍历，当遇到第一个大于 $0$ 的 $DP_i$，则 $i$ 是可以喝的最大的瓶数。
## 关键代码
```
for(int i=n;i>=0;i--){
	if(dp[i]>=0){
        printf("%d",i);
        break;
    } 
}
```
- 外层循环遍历每一个药水。  
- 内层循环从 $i$ 向下遍历，确保不会覆盖当前的状态。  
- 如果饮用当前药水后健康值仍然非负，则更新 $DP_j$。

## Code

```
#include<bits/stdc++.h>
#define bug cout<<"!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
#define int long long
using namespace std;
const long long INF=-2e15;
long long n,a[2222],dp[2222];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]); 
		dp[i]=INF;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j>0;j--){
			if(dp[j-1]+a[i]<0){
				continue;
			}
			
			dp[j]=max(dp[j-1]+a[i],dp[j]);
		}
	}
	for(int i=n;i>=0;i--){
		if(dp[i]>=0){
			printf("%d",i);
			break;
		} 
	}
	return 0;
}
```

[提交记录](https://codeforces.com/problemset/submission/1526/286213191)

---

## 作者：heyZZZ (赞：1)

思路 1：

使用动态规划算法，$f_i$ 是表示喝 $i$ 瓶药的最大值。

可以得出：$f_j=\max(f_j,f_{j-1}+a_j)$。

关键代码：

```cpp
for(int i=1;i<=n;i++)
    for(int j=i;j;j--)
        if(f[j-1]+a[i]>=0)
             f[j]=max(f[j],f[j-1]+a[i]);
```

时间复杂度：$O(n^2)$。

思路 2：

使用贪心算法+优先队列。


先拼劲全力去喝，如果在这道题中喝药喝死了，我们就要将他把药吐出来。

关键代码：


```cpp
for(int i=1;i<=n;i++){
    sum+=f[i],q.push(-f[i]);
    if(sum<0){
        p=q.top(),q.pop();
        p=-p,sum-=p,t++;
    }
}
```

时间复杂度：$O(n \log_2 n)$。

---

## 作者：_Andy_Lin_ (赞：1)

[在博客园食用更佳](https://www.cnblogs.com/andy-lin102/p/16320649.html)

打了 vp 后打算来写一篇题解。

感觉我的思路还是比较特殊。

将正值的药称为保健品，负值的药称为毒药。

首先保健品是肯定要喝的。毒药的要尽量多喝。

要多喝毒药，就要尽量喝毒性弱的（也就是绝对值小的）。

可以倒序循环，找到毒药就将其放入一个堆中，堆中毒性弱的在上。

找到保健品时，努力将其透支。用保健品的效果从毒性的弱到强吃毒药。如果保健品不足以将毒药吃掉，那么用保健品将毒药的毒性削弱。

可以证明：此时的保健品只能用于此时堆中的毒药，方法一定最优。

如果没看懂，请看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200001
int n,a[N],t[N],num,ans;
priority_queue<int>heap;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
		if(a[i]>=0)++ans;
	}
	for(int i=n;i>=1;--i){
		if(a[i]<0)heap.push(a[i]);
		if(a[i]>0){
			while(!heap.empty()&&a[i]>=-heap.top()){
				a[i]+=heap.top();heap.pop();++ans;
			}
			if(!heap.empty()){
				int x=heap.top();heap.pop();
				x+=a[i];heap.push(x);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Da_un (赞：1)

这篇题解可能会有重复的地方，但我会把我做这道题所学到的和所研究的分享给大家，建议新手观看。~~大佬跳过~~

首先，了解一下题目中出现的关键词：子序列和前缀和。

### 子序列

> 子序列就是在原来序列中找出一部分组成的序列。

要注意的是，子序列是由原来序列中符合条件的元素按从前往后的顺序添加到新序列中所组成的序列，顺序是不能变的。比如说有一个序列 $1 2 3 4 5$，它的子序列可以是 $124$，也可以是 $135$，但不可以是 $231$，也不可以是 $342$。

### 前缀和

>前缀和是一个数组的某个元素的下标之前(包括此元素)的所有数组元素的和。

这道题知道这些前缀和知识就足够了，如果还想了解更多，可以去这位大佬的博客学习：
[https://www.cnblogs.com/-Ackerman/p/11162651.html#](https://www.cnblogs.com/-Ackerman/p/11162651.html#)

知道了这些，就可以~~很轻松地~~把这道题切掉了~~

这道题的大体意思就是给出一个序列，求出最长子序列使得这个子序列的每一个元素的前缀和均不为负。

## 思路
这道题我用的是贪心，非负数一定要在这个子序列中，至于负数怎么选，要紧扣子序列定义来做，我们可以建一个优先队列，并按顺序依次将原序列的元素取反入队(优先队列优先弹出队列中数值大的元素)，并且用一个累加器累加，当这个累加器变为负数时，弹出栈顶元素，其实就是当时最小的负数，如果子序列中有这个数，那么这个方案一定不是最优，所以必须舍弃，到最后，看一看舍弃了几个数，用原序列个数减去即为最终答案。

看数据范围，还是开 long long 比较保险。
### Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
int n;
ll f[2010],tot,t,p,sum;
priority_queue<ll> q;//优先队列 
int main()
{
	scanf("%d",&n);
	tot=n;//先记录原序列个数 
	for(int i=1;i<=n;i++)
		scanf("%lld",&f[i]);
	for(int i=1;i<=n;i++){
		sum+=f[i];//累加器不断累加 
		q.push(-f[i]);//取反入队 
		if(sum<0){//累加器小于0，要删元素了 
			p=q.top();
			q.pop();
			p=-p;//变回原来的数值 
			sum-=p;//清除这个非最优选择 
			t++;//统计删除数字的个数 
		}
	}
	printf("%lld",tot-t);//总数减删除数字的个数即为答案 
	return 0;
}
```
完结撒花~~

---

## 作者：风清醉逍遥 (赞：1)

### 此题的简单版本可以用 $O(n^2)$ 的 DP(01背包) 解决
#### 属性
$dp_{i,j}$ 为前 $i$ 瓶药水中，喝下了 $k$ 瓶药水所能达到的最大血量
#### 状态转移方程:
$dp_{i,j} =
\begin{cases} 
\max \{dp_{i-1,j},\ dp_{i - 1, j - 1} + potions_i\},\ when\ \ dp_{i - 1, j - 1}+potions_i \geqslant 0\\
dp_{i - 1, j},\ when\ \ dp_{i - 1, j - 1}+potions_i < 0
\end{cases}$
#### 滚动数组优化空间(第二维要逆序枚举)
$dp_{j} =\max \{dp_{j},\ dp_{j - 1} + potions_i\},\ when\ \ dp_{j - 1}+potions_i >= 0$
#### 初始化时要注意：
此题让我们求最多可以喝下的药水数量，而不是求最大血量。因此，除 $dp_0 = 0$ 以外， $dp_{1\sim n}$ = -0x3f3f3f3f3f3f3f3f，以保证我们会在血量不为负数的情况下，尽量喝下多的药水。PS： $dp_{1\sim n}$ 赋值为 -0x7fffffff 不够小，会WA。

#### 最后答案
$ans = \max \{ans,k\},when\ \ dp_k\geqslant0$
#### 代码:
```
#include <stdio.h>
#define LL long long

LL Max(LL x, LL y){
    return x > y ? x : y;
}

const int maxn = 2e3 + 10;
int n;
LL dp[maxn], potions[maxn];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &potions[i]);
    }
    dp[0] = 0;
    for(int j = 1; j <= n; j++){
        dp[j] = -0x3f3f3f3f3f3f3f3f;
    }
    for(int i = 1; i <= n; i++){
        for(int j = i; j > 0; j--){
            if(dp[j - 1] + potions[i] >= 0){
                dp[j] = Max(dp[j], dp[j - 1] + potions[i]);
            }
        }
    }
    for(int i = n; i >= 0; i--){
        if(dp[i] >= 0){
            printf("%d", i);
            return 0;
        }
    }
    
    return 0;
}
```

---

## 作者：wurang (赞：0)

这题要求最多能喝几瓶药，那么我们会尽可能多的去喝。

令喝药后的生命值为 ${qz}$ ，若 $qz<0$ ，则从之前（包括这瓶）喝过的所有药中，放弃扣除血量最多的药（最小的），直到生命值为正。

因为每次都会去除最小的，不难想到使用优先队列优化。

其他细节见代码吧。


```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long>q;
long long a[200001];
long long n;
long long qz;//前缀和记录此时生命值 
int sum;//此时喝药的数量 
int ans;
int op; 

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)cin >> a[i];
	for(int i = 1; i <= n; i++)
	{
		if(a[i] < 0)//只有<0的药可能会被放弃，将其压入队中 
		{
			q.push(abs(a[i]));//取反（无需小根堆） 
		}
		qz += a[i];
		sum++;
		while(qz<0)
		{
			sum--;
			op = -q.top();//最小的药水 
			qz -= op;//放弃药水 
			q.pop();
		}
		ans = max(ans,sum);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：nytyq (赞：0)

## Part1.分析

注意到这句话:

> 这个子序列任意前缀和都非负。

考虑进行顺次取数以满足每一时刻的前缀非负。

我们在选取一个数的时候，如果使得当前的前缀为负数，考虑反悔贪心舍去最小的数而接着选取最优选择。

贪心算法成立易证明，不做赘述。

由于舍去最小值，考虑维护最小值，使用优先队列维护。

时间复杂度为 $O(n \log n)$。

## Part2.ACcode

```
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N=2e3+10;
int a[N];
int n;

priority_queue<int,vector<int>,greater<int> > q;


signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	
	int ans=0;
	int cnt=n;
	
	for(int i=1;i<=n;i++){
		q.push(a[i]);
		ans+=a[i];
		if(ans<0){
			cnt--;
			ans-=q.top();
			q.pop();
		}
	}
	cout<<cnt;
	return 0;
}

```

---

## 作者：cwd2023 (赞：0)

# CF1526C1题解
#### by cwd2023 

---

### 题目大意：

有一些药品，有的加血，有的扣血。你需要喝尽可能多的药，使你在喝的过程中血量**非负**。

---

### 算法:
贪心地想，如果我喝一瓶药会挂，罪魁祸首不一定是这瓶药，而是对我伤害最大的药。  
我可以反悔，即不喝伤害最大的那瓶，而是喝这瓶，这样血量最少也是 $0$，且对答案没有消耗（去掉 $1$ 又加上 $1$）。

**解释**：设伤害最大的药品的值为 $x$，当前喝的药品值为 $y$，当前血量为 $z$。

则： 

$0 \ge y\ge x$ 

$z\ge 0$ 

$z+y<0$

所以： 

$-x+y\ge 0$ 

$z-x+y\ge 0$

---

### 总结：
需要实现：实时维护最小值 -> 小根堆。

---

### Code:
#### 详细注释版：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,cur,ans;//cur记录血量，ans记录答案
ll a[200010];
priority_queue<ll,vector<ll>,greater<ll> >q;
//小根堆
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cin.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=n;i++){
		cur+=a[i],q.push(a[i]),ans++;
//如果要喝掉，血量改变，答案加一。并将这瓶要放入堆中。
		if(cur<0)
			cur-=q.top(),q.pop(),ans--;
//发现血量不够，就删去最毒的药。血量改变，答案减一。
	}
	cout<<ans;
	return 0;
}
```
#### 无注释版：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,cur,ans;
ll a[200010];
priority_queue<ll,vector<ll>,greater<ll> >q;
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cin.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=n;i++){
		cur+=a[i],q.push(a[i]),ans++;
		if(cur<0)
			cur-=q.top(),q.pop(),ans--;
	}
	cout<<ans;
	return 0;
}
```
最后，希望我的题解对你有所帮助，感谢观看。   
### 望管理员通过！

---

## 作者：_xxxxx_ (赞：0)

### 分析

题意在题面上已经很清楚了。

我们可以选择 **贪心** 或者 **DP** 实现这道题。

1. 贪心做法。

时间复杂度 $O(n \log n)$，因此可以通过[加强版](https://www.luogu.com.cn/problem/CF1526C2)。

从头开始，假设全部取，分两种情况。

1. $a_i$ 是非负数。

选择它显然会使得当前的值变大或不变，无脑选非负数。

2. $a_i$ 是负数。

先直接把 $a_i$ 给取走，$a_i$ 会导致当前答案变小。把负数全部压入一个堆里，当当前值变负时，拿出堆中最有贡献的，即堆中最小值，把它~~吐出来~~减掉，因为 $a_i$ 也在堆中，所以减一次一定就会使当前值变正，同时答案长度减一。

堆可以用优先队列实现。

下面给出贪心代码，此代码同时可以通过加强版。

```cpp
#include <iostream>
#include <cmath>
#include <map>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <algorithm>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n;
int a[N];
priority_queue<int> p;//优先队列默认从大到小 
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int now = 0, ans = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] >= 0)
		{
			now += a[i];
			ans++;
			continue;
			//拿这个数变大或不变显然拿了更优 
		}
		now += a[i];
		ans++;
		p.push(-a[i]);
		//因为插入值全部是负数
		//所以插入-a[i]可以使得优先队列的自动从大到小排变成从小到大 
		if(now < 0)//变负了
		{
			now += p.top();//插入的是-a[i]，少减即为加，负负得正 
//			cout << p.top() << " ";
			p.pop();//弹出 
			ans--;//长度-- 
		}
	}
	cout << ans << endl;
	return 0;
}
```

2. DP 做法。

时间复杂度 $O(n^2)$，不能通过[加强版](https://www.luogu.com.cn/problem/CF1526C2)。

$dp_i$ 表示到了 $i$ 时的选取的序列之和最大值。

转移时，看转移后是否变负，是正数才转移，转移方程为如下。

$$dp_j=\max(dp_j,dp_{j-1}+a_i)$$

输出时，找到最后一个可以取到的地方即可。

```cpp
#include <iostream>
#include <cmath>
#include <map>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <algorithm>
#define int long long
using namespace std;
const int N = 2e3 + 10;
int n;
int a[N];
int f[N];
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		f[i] = -1e15;//初始化极小 
	}
	f[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j >= 1; j--)//要倒着枚举 
		{
			if(f[j - 1] + a[i] >= 0)
			{
				f[j] = max(f[j], f[j - 1] + a[i]);//转移 
			}
		}
	}
	for(int i = n; i >= 0; i--)
	{
		if(f[i] >= 0)//最后一个可以取的 
		{
			cout << i << endl;
			exit(0);
		}
	}
	return 0;
}
```

---

## 作者：xuduang (赞：0)

提供一种不用堆或者动态规划的算法，本质上就是贪心。

贪心，每个数字向后取，每当加到负数时，在已经遍历过中的最小值，就是减的最多的一个数，找出来减掉，当作不选这个数。每次答案加一，达到负数减一。

对于遍历中的最小值，我们用一个数组 $c$ 来存储，每次用一个快排把 $c$ 变为递增的，当前的 $c_1$ 就是最小值。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long a[2005], c[2005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	long long s=0,cnt=0,num=0;
	for(int i=1;i<=n;i++)
	{
		cnt++;
		s+=a[i];
		if(a[i]>=0)continue;//只存负数 
		c[++num]=a[i];
		if(s<0)
		{
			sort(c+1,c+num+1);
			cnt--;//答案减一 
			s-=c[1];
			c[1]=1e12;//取了，变成最大值 
		}
	}
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：zhangqiuyanAFOon2024 (赞：0)

首先，我们想到了用一维 dp 来做。

我们需要先知道转移方程。

$dp_i$ 表示喝 $i$ 瓶体力的最大值。


$i$ 从 $1$ 到 $n$ 枚举一遍，然后若 $j<i$ 则判断一遍是否能喝 $a_i$，如果能喝，那么我们就取喝或不喝生命值大的，可以得出：$dp_j\gets\max(dp_j,dp_{j-1}+a_i)$。

然后枚举一遍 $dp_i$ 求出最多能喝几瓶即可。

思路还是挺简单的。

下面是代码：

```cpp
#define int long long
signed main(){
      int n;
      cin>>n;
      for(int i=1;i<=n;i++)
          cin>>a[i];//n 个数
      dp[0]=0;//注意，如果没喝，体力就是 0
      for(int i=1;i<=n;i++)
          dp[i]=-1e18;// 后面要取 max
      for(int i=1;i<=n;i++)
          for(int j=i;j>=1;j--)
              if(dp[j-1]+a[i]>=0) 
                    dp[j]=max(dp[j],dp[j-1]+a[i]);//把 a[i] 喝掉
      for(int i=1;i<=n;i++){
          if(dp[i]<0){
              cout<<i-1;// 如果会死，则这瓶不喝，输出 i-1
              return 0;
          }
      }
      cout<<n<<endl;//都能喝，输出 n
      return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

这题有两种方法，如果想要更优的解法可以看加强版的 [题解](https://www.luogu.com.cn/blog/715244/solution-cf1526c2)。

# 思路
我们可以用一个 $dp$ 数组存储状态，$dp_i$ 表示长度为 $i$ 的序列和的最大值。

我们可以很简单的写出方程，$dp_j=\max(dp_j, dp_{j-1}+a_i)$。

这里可以根据定义知道 $dp_0=0$。

答案去个最大值就行了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 2050;
i64 dp[maxn], a[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		dp[i] = -1e18;
	}
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j > 0; j--) {
			if (dp[j - 1] + a[i] >= 0) {
				dp[j] = max(dp[j], dp[j - 1] + a[i]);
			}
		}
	}
	for (int i = n; i >= 0; i--) {
		if (dp[i] >= 0) {
			cout << i << "\n";
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：

给您一个数组，在其中选择若干个数使得：

- 任意前缀和  $\ge 0$
- 数量尽可能的大   

我们可以使用**贪心**策略，策略如下：

- 如果当前数为**非负**，必喝。
- 而毒药尽可能的多喝，如果喝没了，就把最小的吐了。   

以上操作可以采用优先队列去优化。    
**重载运算符**
```cpp
struct node{
	ll v;
	bool operator <(const node &x)const{
		return x.v<v;
	}
};

priority_queue<node> q;
```

既然理解了思路可以动手了。

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=2e3+50;
const int M=1e5+50;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll n;
ll a[N];

struct node{
	ll v;
	bool operator <(const node &x)const{
		return x.v<v;
	}
};

priority_queue<node> q;

int main()
{
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	ll ans=n,res=1,cnt=0;
	while(res<=n)
	{
		cnt+=a[res];
		q.push((node){a[res]});
		if(cnt<0){
			node tmp=q.top();
			cnt-=tmp.v;
			q.pop();
			--ans;
		}
		++res;
	}
	printf("%lld\n",ans);	
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1526C1)

## 题意
从一个长度为 $n$ 的序列中选出任意个，使这个序列的和非负，求这个序列的长度

## 解题思路
输入，如果这个数就是非负整数，那么就加上这个数，否则就判断加上这个数是否为负数，如果不是负数，就将序列之和加上这个数，否则如果之前选的数比现在选这个数损失大，那么就把损失大的改成这个数。 

[AC Code](https://www.luogu.com.cn/record/63800496)
## 废话少说，上代码：
```cpp
#include <bits/stdc++.h>//万能头
using namespace std;
#define ll long long
inline int read() {//快读模板 
    register char k = getchar();
    register int x = 0 , flg = 1;
    while (k < '0' || k > '9') {
        if (k == '-')flg = -1;
        k = getchar();
    }
    while (k >= '0' && k <= '9') {
        x = x * 10 + k - '0';
        k = getchar();
    }
    return x * flg;
}
inline void print(ll num) {//快输模板 
    if (num < 0)putchar('-') , num = -num;
    if (num > 9)print(num / 10);
    putchar(num % 10 + '0');
} 
int n;//有n个数 
int main() {
    n = read();
    priority_queue <int> q;//默认大根堆 
    ll sum = 0 , ans = 0;//sum是当前序列的和，ans是序列的长度 
    for (int i = 1 , a; i <= n; ++ i) {//循环 
        a = read();//输入 
        if (a >= 0) ++ans , sum += a;//如果当前这个数本来就是非负的，那么就加上这个数，序列长度加一 
        else {
            if (abs(a) <= sum) {//如果当前的和加上a还是非负的， 那么就加上这个数，序列长度加一 
                sum -= abs(a);//减去个数 
                q.push(abs(a));//加入大根堆 
                ++ ans;//序列长度加一 
            }else {
                if (!q.empty() && q.top() > abs(a)) {//如果大根堆非空且之前选的数比这个负数小，就改成这个数 
                    ll f = q.top();q.pop(); 
                    sum += f - abs(a);//换，因为是覆盖掉之前选的数，所以序列长度不加 
                    q.push(abs(a));//把当前更好的方案入堆 
                }
            }
        }
    }
    print(ans);//输出序列长度 
    return 0;
}
```
### 如果有哪里有错请大佬指出。

---

