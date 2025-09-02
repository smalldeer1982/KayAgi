# Police Patrol

## 题目描述

## 题面描述
在一条数轴上有 $n$ $(1<=n<=10^6)$ 个罪犯，第 $i$ 个罪犯的坐标为 $a_i$ $(\left|a_i\right|<=10^9)$ 。警察们要选择一个地点作为警察局。他们有一辆警车，可容纳 $m$ $(1<=m<=10^6)$ 个罪犯。那么问题来了，把警察局建在哪能使警察抓捕这些罪犯的行程总和最短。

注意：罪犯**不会**逃走。

## 样例 #1

### 输入

```
3 6
1 2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 5
-7 -6 -3 -1 1
```

### 输出

```
16
```

## 样例 #3

### 输入

```
1 369
0
```

### 输出

```
0
```

## 样例 #4

### 输入

```
11 2
-375 -108 1336 1453 1598 1892 2804 3732 4291 4588 4822
```

### 输出

```
18716
```

# 题解

## 作者：_Kimi_ (赞：0)

# CF427E题解

### 前言

这道题作为 $E$ 还是太水了，甚至比 $D$ 简单

### 题意

在 $X$ 轴上选择一个点建一座警局。有 $n$ 个罪犯，现在警局有一辆最多装载 $m$ 个人的警车，求这辆警车把所有罪犯运回警察局需要行驶的最短距离。

### 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/1qazry9z.png)

#### 警局肯定是建在这些罪犯坐标的中位数。

如上图，显示了当 $m$ 为 $2$ 时，在 $1$ 位置建警局和在 $3$ 位置建警局的路程。

可以证明，中位数最优，因为无论 $m$ 为多少，都要到达最左边的罪犯和最右边的罪犯，离两头罪犯距离最小的就是中位数。

#### 考虑抓罪犯的策略

既然已经确定了警局的位置，就要去抓罪犯了，每次能抓 $m$ 个，优先抓最远的，为什么呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/brcodegl.png)

如上图，是当 $m$ 为 $2$ 时，在 $3$ 处建警局抓右边罪犯的示意图。如果先抓距离近的罪犯，路程为 $10$，如果先抓远的罪犯，路程为 $8$，先抓近的罪犯会导致抓远的罪犯时重复走，所以我们先抓远的罪犯。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define sept fixed << setprecision(4)
#define endl '\n' 
#define WA AC
using namespace std;
const int maxn = 1e6 + 10; 
int n, m, ans;
int A[maxn];
void input(){
	srand(19491001);
    ios::sync_with_stdio(0);
	cin.tie(0);
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> A[i];
}
signed main(){
	input();
	int midpos = n + 1 >> 1, mid = A[midpos];//mid 为中位数
	for(int i = n; i >= midpos; i -= m){//每次抓 m 个 
		ans += A[i] - mid;//累加路程 
	}
	for(int i = 1; i < midpos; i += m){//每次抓 m 个 
		ans += mid - A[i];//累加路程 
	} 
	cout << (ans << 1) << endl;//实际上我们只需要算单程结果在乘二即可 
	return 0;
}
```

---

## 作者：zhimao (赞：0)

## 题意
### 题面描述
在一条数轴上有 $n$ $(1<=n<=10^6)$ 个罪犯，第 $i$ 个罪犯的坐标为 $a_i$ $(\left|a_i\right|<=10^9)$ 。警察们要选择一个地点作为警察局。他们有一辆警车，可容纳 $m$ $(1<=m<=10^6)$ 个罪犯。那么问题来了，把警察局建在哪能使警察抓捕这些罪犯的行程总和最短。

注意：罪犯**不会**逃走。

### 输入格式
第一行两个整数 $n$ , $m$ 。分别为罪犯个数和警车容纳罪犯个数。

第二行 $n$ 个整数，为罪犯的坐标。

### 输出格式
输出一个数，即最短行程和。

## 题解
做此题关键是发现其中隐含的单调性。

显然把警局建在最左边罪犯的左边和最右边罪犯的右边都不如建在一端。

假设建在一端（如左端），最优方案是什么呢？不管怎样警车都要到最右端，所以我们不如先让警车跑到最右端，抓所有最右边能抓的罪犯，回来。这样一直重复到抓完，是最优的。

假设建在中间就分开算左右加起来。

警局从坐标 $p$ 到 $p+1$ ，左边增加的路程为原要开车出去次数$\times$2 , 假如加上 $p$ 处的罪犯数最后一车乘不下再加二。右边减少的路程同理。可以看出增加的路程从 0 变大 ，减少的路程减小到 0 ，因此行程和从左端点到右端点是个V型的单峰函数，三分即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10000000];
long long check(int x)
{
	int l=1,r=n;
	long long ans=0;
	while(a[l]<=x&&l<=n)
	{
		ans+=(long long)(x-a[l]);
		ans+=(long long)(x-a[l]);
		l+=m;
	}
	while(r>0&&a[r]>=x)
	{
		ans+=(long long)(a[r]-x);
		ans+=(long long)(a[r]-x);
		r-=m;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int l=a[1],r=a[n],mid=(l+r)>>1;
	while(l+1<r)
	{
		long long t1=check(mid-1),t2=check(mid),t3=check(mid+1);
		if(t1>=t2)
		{
			if(t2<t3)
			{
				printf("%lld",t2);
				return 0;
			}
			else l=mid;
		}
		else r=mid;
		mid=(l+r)>>1;
	}
	long long t1=check(l-1),t2=check(l),t3=check(l+1);
	printf("%lld",min(min(t1,t2),t3));
}
```


---

