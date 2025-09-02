# Math Show

## 题目描述

Polycarp takes part in a math show. He is given $ n $ tasks, each consists of $ k $ subtasks, numbered $ 1 $ through $ k $ . It takes him $ t_{j} $ minutes to solve the $ j $ -th subtask of any task. Thus, time required to solve a subtask depends only on its index, but not on the task itself. Polycarp can solve subtasks in any order.

By solving subtask of arbitrary problem he earns one point. Thus, the number of points for task is equal to the number of solved subtasks in it. Moreover, if Polycarp completely solves the task (solves all $ k $ of its subtasks), he recieves one extra point. Thus, total number of points he recieves for the complete solution of the task is $ k+1 $ .

Polycarp has $ M $ minutes of time. What is the maximum number of points he can earn?

## 说明/提示

In the first example Polycarp can complete the first task and spend $ 1+2+3+4=10 $ minutes. He also has the time to solve one subtask of the second task in one minute.

In the second example Polycarp can solve the first subtask of all five tasks and spend $ 5·1=5 $ minutes. Also he can solve the second subtasks of two tasks and spend $ 2·2=4 $ minutes. Thus, he earns $ 5+2=7 $ points in total.

## 样例 #1

### 输入

```
3 4 11
1 2 3 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 5 10
1 2 4 8 16
```

### 输出

```
7
```

# 题解

## 作者：naroto2022 (赞：5)

### 原题链接：[Math Show](https://www.luogu.com.cn/problem/CF846B)
## 话归原题，接下来就是快乐的解题时间啦~
（博客里食用更佳）

首先，我们可以发现 $n$ 和 $k$ 的数据范围都非常小，其次，每个子任务分值相同，设 $dp[i]$ 为做了 $i$ 个完整的任务(其余做的是单独子任务)的最多分数将  $t$ 数组排序后暴力求解

也不多说了，剩下的注释都在代码里了~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> //sort需要的 
using namespace std;
int n,k,N,sum,ans,nim,s,t[55],a[55];//a[i]为做了i个完整的任务（其余做的事单独子任务）最多的分数 
int main(){
	cin>>n>>k>>N;
	for(int i=1; i<=k; i++){scanf("%d",&t[i]);sum+=t[i];}
	sort(t+1,t+1+k);//给t数组排序 
	for(int i=0; i<=n; i++){//暴力 
		if(sum*i>N) break;
		a[i]=i*k+i;
		nim=n-i;
		s=sum*i;
		for(int j=1; j<=k; j++){
			for(int sss=1; sss<=nim; sss++){
				s+=t[j];
				if(s>N) break; 
				a[i]++;
			}
			if(s>N) break;
		}
		ans=max(a[i],ans);//如果做了i个完整的任务最多分数比ans大，那他就是最多能挣的分数 
	}
	cout<<ans;
	return 0;
}
//P上水印
//┭┮﹏ ┭┮ 
```


---

## 作者：CaiXY06 (赞：4)

# Math Show
这是一道非常裸的模拟+贪心题

如楼上所说，由于 $M≤2×10^9$ ,而 $n,k≤45$ 

所以$DP$肯定$TLE$，甚至循环中不能带有$M$

因此我们想到暴力枚举完成的任务数，然后贪心选取剩余可选任务中花费最小的子任务，以达到获得价值最大的效果


------------
#  _Code_


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int score,ans=0,n,K,r,m,t,a[50],sum;
signed main(){
	scanf("%lld%lld%lld",&n,&K,&m);
	for(int i=1;i<=K;i++){
		scanf("%lld",&a[i]);
		sum+=a[i];
	}
	sort(a+1,a+K+1);
        //让花费小的子任务排在前面进行选取
	for(int i=0;i<=n;i++){//枚举已经完成的完整任务的数量
		score=i*K+i,t=sum*i,r=n-i;
                //score表示完成任务获得的价值
                //t表示已经花费的时间
                //r表示剩余可选任务的数量
		if(t>m)break;
		for(int j=1;j<=K;j++){
			for(int k=1;k<=r;k++){
			    t+=a[j];
			    if(t>m)break;
			    score++;
		    }
		    if(t>=m)break;
		}
		ans=max(ans,score);//取得最大价值
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：ZSYZSYZSYZSY (赞：2)

# Math Show（CF846B）
## 题意
有 $n$ 个任务，每个任务都有 $k$ 个子任务，每个任务的子任务所用时间都是一样的，每完成一个子任务得到 $1$，一个任务中子任务全完成，那么得到价值 $k+1$，现在有 $m$ 分钟，求能得到的最大价值。
## 思路
枚举一共可以完成 $i$ 个任务，然后用剩下的时间去枚举能完成多少子任务。子任务要按照时间排好序。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() // 快读
{
    register ll x = 0, f = 1;
    register char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - 48;
        c = getchar();
    }
    return x * f;
}

// 定义变量
ll n, k, M;
ll t[50];
ll sum;

int main()
{
    n = read(), k = read(), M = read();
    for (ll i = 1; i <= k; i++)
    {
        t[i] = read();
        sum += t[i];
    }
    sort(t + 1, t + k + 1); // 对时间点进行排序
    ll ans = 0;
    for (ll a = 0; a <= n; a++) // 假设可以完成a个完整的任务
    {
        ll res = (k + 1) * a;  // 如果完全解决了这个问题（解决了它所有的子任务的K），他会多得一分。这样，他所得到的任务完全解的总点数为K+1。
        ll time = M - a * sum; // time:剩余的时间
        if (time < 0)          // 如果剩余时间不足，跳出循环
            break;
        bool f = 1;
        for (ll i = 1; i <= k; i++)
        {
            for (ll j = 1; j <= n - a; j++)
            {
                if (time >= t[i])
                {
                    res++;
                    time -= t[i];
                    if (time < 0) // 如果剩余时间不足，跳出循环
                        break;
                }
            }
            if (time <= 0)
                break;
        }
        ans = max(res, ans); // 更新答案
    }
    cout << ans;
    return 0;
}

```

---

## 作者：泠小毒 (赞：1)

# Math Show
多鱼参加了一个数学节目。他被赋予n个任务，每个由k个子任务组成，编号为1到k。这需要他用t[i]分钟解决第i个子任务。多鱼可以按任何顺序解子任务。

通过解决任意人物的子任务，他得了一分。这样，任务的点数就等于其中解出的子任务的个数。此外，如果聚鱼完全解决了这个任务（解决了它所有的子任务），他会多得一分。这样，他所得到的任务完全解出的总点数为k+1。

多鱼有m分钟的时间。他最多能挣多少分？
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190514/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190514.html)
## 解法
本来想到背包，结果容量有2e9，不太现实

n和k很小，又因为每个子任务分值相同，设dp[i]为做了i个完整的任务(其余做的是单独子任务)的最多分数

将t数组排序后暴力求解
## ac代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,k,m,sum=0,ans=0,lim,s,a[50],dp[50];
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=k;i++)scanf("%d",&a[i]),sum+=a[i];
	sort(a+1,a+1+k);
	for(int i=0;i<=n;i++)
	{
		if(sum*i>m)break;
		dp[i]=i*k+i,lim=n-i,s=sum*i;
		for(int j=1;j<=k;j++)
		{
			for(int kk=1;kk<=lim;kk++)
				{s+=a[j];if(s>m)break;dp[i]++;}
			if(s>m)break;
		}
		ans=max(dp[i],ans);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：LouYiYang1 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF846B)
## 思路：
考虑用模拟得到最优的方式。首先枚举可以完成 $i$ 个大的任务，然后循环找到从时间到最大的，其实就是暴力求解，数据不大。

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long//注意不开long long见祖宗
using namespace std;
int a[45], n, k, m;
signed main() {
	while (cin >> n >> k >> m) {
		int sum = 0;
		for (int i = 1; i <= k; i++) {
			cin >> a[i],
			    sum += a[i];
		}
		stable_sort(a + 1, a + k + 1);//稳定排序一下
		int ans = 0;
		for (int i = 0; i <= n; i++) {
			if (m < i * sum) break;
			int cnt = m - i * sum, t = i * (k + 1);
			for (int j = 1; j < k; j++) {
				for (int p = 1; p <= n - i; p++) {
					if (cnt >= a[j]) t++,
					cnt -= a[j];
				}
			}
			ans = max(ans, t);
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：czh___ (赞：0)

题意：给定你 $n$ 个相同任务，每个包含 $k$ 个小任务，从 $1$ 到 $k$，$n$ 个相同任务的完成时间相同，但每个小任务的完成时间不相同。当你完成了一个大的任务之后，$ans$ 在原来的基础上加 $1$，让你求最大的 $ans$。

思路：本来考虑是 dp 的，但看了一眼数据范围， dp 必超时，就想着用贪心求，考虑模拟得到最优的方式吧。首先枚举可以完成 $i$ 个大的任务，然后循环找到从时间到最大的，其实就是暴力求解，数据不大。

注意：不开 long long 见祖宗！

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[46],n,k,m;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    while(cin>>n>>k>>m){
        int sum=0;
        for(int i=1;i<=k;i++)
            cin>>a[i],
            sum+=a[i];
        stable_sort(a+1,a+k+1);
        int ans=0;
        for(int i=0;i<=n;i++){
        	if(m<i*sum)
        		break;
            int temp=m-i*sum,t=i*(k+1);
            for(int j=1;j<k;j++)
                for(int p=1;p<=n-i;p++)
                    if(temp>=a[j])
						t++,
                        temp-=a[j];
            ans=max(ans,t);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```
拜拜！

---

## 作者：Walrus (赞：0)

## [CF846B](https://codeforces.com/problemset/problem/846/B) 

一道 CF 评分 $1800$ 的题，相比于官方题解砍掉了一个 $N$。

## 题意

有 $n$ 个相同的任务，其中有 $k$ 个互不干扰的子任务，每个子任务都有对应的完成时间，第 $i$ 个任务需要 $t_i$ 的时间完成，每完成一个子任务，计 $1$ 分，如果一个大任务内的所有子任务全部完成，则额外加 $1$ 分。



## 思路

看到 $0\leq m \leq 2\times 10^9$，并且 DP 的状态也不好设计，于是放弃背包的想法。又看到 $1\leq n \leq 45$，$1\leq k \leq 45$，考虑直接枚举一些东西。

先从 $n$ 下手，定义一个状态，设 $f_i$ 表示只**全部完成** $i$ 个任务可获得的最大得分，不难看出贪心思想，因为题目描述提到**可以用任何顺序完成子任务**，于是自然将 $t$ 数组从小到大排序，每次优先从**未全部完成的大任务中选取完成时间最小的子任务，并判断当前是否可以将剩下 $n-i$ 个大任务中对应的所有子任务完成，如果不行，计算还可以满足多少个，简单统计答案即可。**

假设最多只能全部完成 $T$ 个大任务。

答案显然是 $\max\limits_{0\leq i \leq T}\{f_i\}$。

时间复杂度为 $O(N\times K)$。

最后证明一下为什么可以砍掉一个 $N$。

分为两种情况讨论：
	
- 如果当前剩下的时间可以满足剩下的 $n-i$ 个尚未完成的任务中所有对应枚举到的子任务，则当前全选一定是最优的。
- 如果不能全部选到，则当然是能选多少选多少，至于剩下的时间，一定不会产生贡献了。这里使用反证法，如果还可以为后面的子任务产生贡献，则一定可以对当前不够选的任务产生贡献，因为 $t$ 数组是从小到大排序的。

简单来说，如果当前能为靠后的子任务做贡献，则一定能为比它所花费时间小的子任务做贡献，具体实现还是要看代码。
	




## Code

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;

const int N = 50;
int n, k, m, ans, cnt;
int t[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> k >> m;
	
	for(int i = 1;i <= k;i++)
		cin >> t[i], cnt += t[i];
	
	sort(t + 1, t + 1 + k);
	
	for(int T = 0;T <= n;T++) {
		int sum = m - T * cnt,	
			now = 0;
		
		if(sum < 0)
			break;
		
		for(int i = 1;i <= k;i++) {
			if(sum >= t[i] * (n - T))
				now += n - T, sum -= t[i] * (n - T);
			else {
				now += sum / t[i];
				break;//显然，如果当前最小的已经不够全部满足了，直接结束循环。
			}
				
		}
		
		ans = max(ans, now + (k + 1) * T);
	}
	
	cout << ans;
	return 0;
	
}

```

## 


---

## 作者：small_turtle (赞：0)

首先，这道题看上去很像一个背包，但是考虑到 $m \leq 2\times 10^9$，显然不可取。

我们可以发现，如果没有完成整个操作而多加的一分，我们可以将数组从小到大排序后暴力去做。

但对于样例一，正规的做法是先做完一组获得 $5$ 分，再取第二组的第一个获得 $1$ 分，总共 $6$ 分。而上面的做法做了三次 $1$，两次 $2$，仅有 $5$ 分。

因为取完一组的得分为 $(k+1)i$，我们可以枚举取了多少组，剩下的就贪心去做。

最后我们只需按上述思路模拟即可。

```cpp
/*
Author:xwg
Time:2023.2.5
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define unordered_map map
const int inf=2147483647;
const double eps=1e-6;
using namespace std;

ll n,k,m,a[49],s,ans;

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	scanf("%lld%lld%lld", &n, &k, &m);
	for(int i=1;i<=k;++i)
	{
		scanf("%lld", &a[i]);
		s+=a[i];
	}
	sort(a+1, a+k+1);
	
	for(int i=0;i<=n;++i)
	{
		ll t=s*i,cnt=(k+1)*i,tmp=n-i;
		if(t>m)
		{
			break;
		}
		for(int j=1;j<=k;++j)
		{
			for(int _=1;_<=tmp;++_)
			{
				t+=a[j];
				if(t>m)
				{
					break;
				}
				++cnt;
			}
		}
		ans=max(cnt, ans);
	}
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：zplqwq (赞：0)

这题诈骗题，乍一看背包，实际上就是个模拟。

我们发现 $n,k$ 都非常的小，因此我们先将 $t$ 数组排序（将时间花费小的放在前面考虑）。之后考虑枚举这 $n$ 个任务，然后选取剩余未选择的任务中最优的任务，然后暴力计算最大值即可。

```cpp
		if(sum*i>m)break;
		cnt[i]=i*k+i;//表示做了i个完整的任务的最多分数
		tmp=sum*i;
		int mm=n-i;
		for(int j=1;j<=k;j++)
		{
			int tmpp=mm;
			while(tmpp>0)
			{
				tmpp--;
				tmp+=t[j];
				if(tmp>m)
				{
					break;
				}
				cnt[i]++;
			}
			if(tmp>m) break;
		}
		ans=max(cnt[i],ans);
        
```

---

