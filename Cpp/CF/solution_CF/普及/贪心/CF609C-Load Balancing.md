# Load Balancing

## 题目描述

In the school computer room there are $ n $ servers which are responsible for processing several computing tasks. You know the number of scheduled tasks for each server: there are $ m_{i} $ tasks assigned to the $ i $ -th server.

In order to balance the load for each server, you want to reassign some tasks to make the difference between the most loaded server and the least loaded server as small as possible. In other words you want to minimize expression $ m_{a}-m_{b} $ , where $ a $ is the most loaded server and $ b $ is the least loaded one.

In one second you can reassign a single task. Thus in one second you can choose any pair of servers and move a single task from one server to another.

Write a program to find the minimum number of seconds needed to balance the load of servers.

## 说明/提示

In the first example two seconds are needed. In each second, a single task from server #2 should be moved to server #1. After two seconds there should be 3 tasks on server #1 and 4 tasks on server #2.

In the second example the load is already balanced.

A possible sequence of task movements for the third example is:

1. move a task from server #4 to server #1 (the sequence $ m $ becomes: 2 2 3 3 5);
2. then move task from server #5 to server #1 (the sequence $ m $ becomes: 3 2 3 3 4);
3. then move task from server #5 to server #2 (the sequence $ m $ becomes: 3 3 3 3 3).

The above sequence is one of several possible ways to balance the load of servers in three seconds.

## 样例 #1

### 输入

```
2
1 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
10 11 10 11 10 11 11
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
3
```

# 题解

## 作者：no2lxs (赞：1)

# CF609C题解

这是道比较简单的贪心，求出平均数后再逐次计算。

以下是思路:

1. 首先将输入的数字进行升序或降序排列；

2. 算出输入数的平均值；

3. 依次计算出步数，注意绝对值；

4. 因为每次一加一减，所以在输出时记得除以二；

## Part 2 Code

 
 ```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<bits/stdc++.h>
#include<map>
#define gets(S) fgets(S,sizeof(S),stdin)
#pragma optimize GCC(2)
using namespace std;
int num[100000];
int main()
{	
	int n;
	cin>>n;
	int avrg=0;//平均数 
	for(int i=1;i<=n;i++)
	{
		cin>>num[i];
		avrg+=num[i];
	}
	int s=n-avrg%n;
	avrg/=n;
	sort(num+1,num+n+1);//升序排列;
	int ans=0;//记录次数;
	if(num[n]-num[1]<=1)
	{
		cout<<0;return 0;//如果最小和最大相差小于等于1，即可直接判定; 
	}
	for(int i=1;i<s;i++)
	{
		ans+=abs(avrg-num[i]);//注意是绝对值;
	}
	for(int i=s;i<=n;i++)
	{
		ans+=abs(avrg-num[i]-1);//再次强调绝对值;
	}
	cout<<ans/2;//总共算了两次所以要除以2; 
		return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：1)

## 题意

有 $n$ 个服务器，第 $i$ 个服务器有 $m_i$ 个任务。

你可以对服务器的任务分配做多次调整，每次可以将一个任务从一个服务器 $a$ 调整到另一个服务器 $b$，让 $m_a-1,m_b+1$，并耗费 1 秒的时间。

请求出最少用多少秒可以最小化 $m_{max}-m_{min}$。

## 思路

既然要最小化 $m_{max}-m_{min}$，那一定是平均分摊给每一个服务器，$m_{max}-m_{min}$ 的值只会有两种情况，要么$m_{max}-m_{min}=0$，要么$m_{max}-m_{min}=1$。

我们可以先计算 $S=\sum_{i=1}^n m_i$，如果 $S \equiv 0(\operatorname{mod} n)$，那么每个服务器最后都应是有 $\frac{S}{n}$ 个任务，此时 $m_{max}-m_{min}=0$。如果 $S\not\equiv0(\operatorname{mod} n)$，那么 $S\operatorname{mod}n$ 台服务器有 $\frac{S}{n}+1$ 个任务，剩下的服务器有 $\frac{S}{n}$ 个任务。合并起来看，就是 $S\operatorname{mod}n$ 台服务器有 $\frac{S}{n}+1$ 个任务，剩下的服务器有 $\frac{S}{n}$ 个任务。因为如果 $S \equiv 0(\operatorname{mod} n)$，那么 $S\operatorname{mod}n=0$，是成立的。

这下就很简单了，我们可以先把 $m$ 数组排序，然后对于前 $n-S \operatorname{mod}n$ 个服务器，$ans+\lvert m_i-\frac{S}{n} \rvert$，对于剩下的 $S\operatorname{mod}n$ 个服务器，$ans+\lvert m_i-(\frac{S}{n}+1)\rvert$。最终因为题面中给出调整一个只要一秒，就能让一个加一，一个减一，而我们算出了调整的总数，因此最后答案为 $\frac{ans}{2}$。

## 代码

接下来贴我的代码，希望大家能够掌握思路，自己写出来，不必复制粘贴这么短的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m[100005],sum,ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>m[i];
    for(int i=1;i<=n;i++)sum+=m[i];
    sort(m+1,m+n+1);
    for(int i=1;i<=n-sum%n;i++)ans+=abs(m[i]-sum/n);
    for(int i=n-sum%n+1;i<=n;i++)ans+=abs(m[i]-(sum/n+1));
    cout<<ans/2<<endl;
    return 0;
}
```


---

## 作者：Miraik (赞：1)

### UPDATE:2020.9.18 修正Latex

简单贪心。

## 思路：

题目要求平均，因此我们设所有任务之和为 $tot$ 。

最平均的方案就是：$ tot \bmod n $ 台服务器处理 $tot/n+1$ 个任务, $n-tot \bmod n $  台服务器处理 $tot/n$ 个任务

所以将每个 $a_{i}$ 进行降序排序，再将前 $tot \bmod n$ 项累加 $a_{i}$ 与 $ tot/n+1 $的差的绝对值，后 $ n-(tot \bmod n) $项累加 $a_{i}$ 与$ tot/n$ 的差的绝对值，即可求出答案

### 注意:因为题目中写每次 $m_{a}$ 减少 $1$、$m_{b}$ 增加 $1$，所以答案最后要除以 $2$！！！

完整代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,a[100005],tot,bal,ans;
inline int _abs(int x){return x>0?x:-x;}
bool cmp(int x,int y){
	return x>y;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),tot+=a[i];
	sort(a+1,a+n+1,cmp);
	bal=tot%n,tot/=n;
	for(int i=1;i<=n;i++)
		if(bal)bal--,ans+=_abs(a[i]-tot-1);
		else ans+=_abs(a[i]-tot);
	ans/=2;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：The_Lost_09 (赞：1)

## [传送门](https://www.luogu.com.cn/problem/CF609C)

### 题目描述：
给你 $ n $ 个数，第 $i$ 个数为 $m_{i}$，每次让 $m_{a}+1$, 并让 $m_{b}-1$	\($1 \le a,b \le n$\)。

求在多少次后 ， $n$ 个数均等于它们的平均值 。

### 思路：

**1. 简单贪心**

2. 易知$ \sum^{n}_{i=1} m_{i}$ = $ \sum^{s1}_{i=1} m_{i}$ \+ $ \sum^{n}_{i=s1+1} m_{i}  (s1 \le n)$ 。因为平均数不一定为整数，我们设 $b1$ 为平均数下取整 ，$b2$ 为平均数上去取整即 $b1+1$ ,$s1$ 为 $b1$ 个数 ，$s2$ 为 $b2$ 个数。则:

    $b1= \lfloor  \frac{\sum^{n}_{i=1} m_{i}}{n}\rfloor$ 
    
    $b2=b1+1 $
    
    $s2= (\sum^{n}_{i=1} m_{i}) \mod n$
    
    $s1= n-s2 $
    
3. 进行贪心必不可少的排序

4. 求出 $s1$ 个较小值与 $b1$ 的差与 $s2$ 个较大值与 $b2$ 的差的总和

5. 因为每次修改会改变 $2$ 个值 ，所以将答案除以 $2$ 输出

#### 接下来就是你们最喜欢的 $Code$

$My Code$:

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

int a[100005];

void in(int &x){ //快读
	x=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	x*=f;
}

int abs(int a,int b){ //a,b差的绝对值
	return a>b?a-b:b-a;
}

int main(){
	int n,sum=0;
	in(n);
	for(int i=0;i<n;++i){
		in(a[i]);
		sum+=a[i];
	}//sum为所有元素的和
	sort(a,a+n);//即3.
	int b1,b2,s1,s2;
	b1=sum/n;
	b2=b1+1;
	s2=sum%n;
	s1=n-s2;
        //即2.
	int ans=0;
	for(int i=0;i<s1;++i){int cc=abs(a[i],b1);ans+=cc;}
	for(int i=s1;i<n;++i){int cc=abs(a[i],b2);ans+=cc;}
        //即4.
	printf("%d\n",ans/2);//即5.
	return 0;
}

---

## 作者：I_am_kunzi (赞：0)

# CF609C 题解

### 题目翻译

$ n $ 个服务器，第 $ i $ 个服务器有 $ m _ i $ 个任务，求最小的操作次数使得服务器之间任务差距最大为 $ 1$？

一次操作指将一个任务从 $ a $ 分配到 $ b$，其中 $ 1 \le a , b \le n$，此操作会耗费 $ 1 $ 秒。

### 题目思路

注：本题是我和同学打完 abc313_c 后发现的题目，一样的思路和代码，说明多刷题可能遇到原题。

容易得出，在整个分配任务的过程中，总任务数不会发生变化，发生变化的只有数个节点的任务数。在此过程中，我们为了让每个节点交换的任务数尽量少，可以让最终交换完时，本来任务较少的服务器最终的任务也较少；本来任务较多的服务器任务也较多，例如原来各服务器任务分别为 ``` 4 7 4 7```，交换完变成 ``` 5 6 5 6```。我们可以对原数组 $ a $ 排序，并计算出对应的交换后的数组 $ b$，又因为每交换一次会改变两个位置的值，所以计算出 $ \displaystyle \frac {\sum_{i = 1} ^ n \left | a_i - b_i \right |} 2 $ 即可。

### 题目代码

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
long long a[200005]; // 原数组
long long b[200005]; // 交换后的数组
signed main()
{
	int n;
	cin >> n;
	long long sum = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i];
		sum += a[i];
	}
	sort(a + 1 , a + n + 1); // 排序，方便后续操作
	for(int i = 1 ; i <= n ; i++)
	{
		b[i] += sum / n; // 前面的位置小，所以都是 sum / n（但是后面的位置已经被修改，所以要用 += 而不是 =）
		if(i - 1 < sum % n) // i - 1 是因为 sum % n 的值下限为 0 而不是 1
		{
			b[n - i + 1]++; // 对应的位置增加 1
		}
	}
	long long cha = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		cha += abs(a[i] - b[i]); // cha 的值就应该是需要变动的值的总和
	}
	cout << cha / 2 << endl; // 因为操作一次会改变两个位置，因此此处输出 cha / 2 即可
    return 0;
}
```


---

## 作者：hxhhxh (赞：0)

## 大意

给你一个有 $ n $ 个整数的数组 $ a $ ，每一秒可以选择两个整数 $ 1 \leq i,j \leq n $ ，使`a[i]++,a[j]--`，求最少多少秒后，可以使

$$ t = \max_{i=1}^n a_i - \min_{i=1}^n a_i $$

最小。

## 思路

首先， $ S = \sum_{i=1}^n a_i $ 不变。可以看出， $ t= 0 $ 或 $ 1 $ 。

要想使 $ t $ 最小，~~感性理解~~ $ S \bmod n $ 个数取 $ \lfloor \frac{S}{n} \rfloor $ ， $ n-(S \bmod n) $ 个数取 $ \lfloor \frac{S}{n} \rfloor + 1 $ 。

我们看不大于 $ \lfloor \frac{S}{n} \rfloor $ 的数。

有 $ S \bmod n $ 个位置，应该尽量让小的数增加到这里。

如果满了，那就取 $ S \bmod n+1 $ 的位置，让剩下较小的数到那里。

与此同时，因为 $ S $ 不变，大的数同样可以减到合适的位置。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],cnt[200005],sum,avg,upt,dwt,ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		cnt[a[i]]++;
		sum+=a[i]; 
	}
	avg=sum/n;
	upt=sum%n;
	dwt=n-upt;
	for(int i=avg;i>=1;i--){
		if(dwt>=cnt[i]){
			ans+=cnt[i]*(avg-i);
			dwt-=cnt[i];
		}
		else if(dwt!=0){
			ans+=dwt*(avg-i);
			ans+=(cnt[i]-dwt)*(avg-i+1);
			dwt=0;
		}
		else ans+=cnt[i]*(avg-i+1);
	}
	printf("%lld",ans);
}
```

---

## 作者：Dry_ice (赞：0)

~~本人**灰题**搜索专门户。~~

## 大致思路：贪心

## Details

- 首先将任务尽量平均地分配到每个机器
- 剩余的任务分配到任务最少的机器
- 答案为最小极差
- 记得求差要用绝对值哦

## CODE
```cpp
#include<stdio.h>
#include<algorithm> //sort要用
int a[100005]; //巨大无比的数组
int main() {
	int n, sum = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		sum += a[i]; //求所有任务数量和
	}
	int p = sum / n, rem = sum % n, ans = 0;
	std:: sort(a, a + n); //按任务数量升序排序
	for(int i = 0; i < n - rem; ++i)
		ans += abs(a[i] - p); //绝对值！
	for(int i = n - rem; i < n; ++i)
		ans += abs(a[i] - p - 1); //绝对值！
	printf("%d\n", ans >> 1); //答案要除以2
	return 0;
}
```

~~这题竟然有58个测试点~~

## The end. Thanks.

---

## 作者：Carotrl (赞：0)

简单的贪心水题。

大致思路：**因为要让任务分配得尽量平衡，所以我们先让每台服务器的任务相同。随后，我们把剩下的任务放到原来任务多的服务器上，这样能保证耗费时间最小。**

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t,n,a[100005],ans;
bool cmp(int q,int w){return q>w;}
int main(){
	scanf("%d",&n);
	int s=0;ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		s+=a[i];//求和
	}
	sort(a+1,a+1+n,cmp);//排序，为接下来的扫描做准备
	int p=s/n;//平均数，保留整数
	int k=s-p*n;//平均后剩下的任务
	for(int i=1;i<=k;i++){
		if(a[i]>p+1)ans+=a[i]-p-1;//原来任务多的服务器要多分一个任务，移动次数就是原来的任务减现在的任务
	}
	for(int i=k+1;i<=n;i++){
		if(a[i]>p)ans+=a[i]-p;//同上
	}
	printf("%d",ans);
}
```


---

