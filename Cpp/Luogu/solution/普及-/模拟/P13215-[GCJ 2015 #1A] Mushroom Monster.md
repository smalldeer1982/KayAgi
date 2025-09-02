# [GCJ 2015 #1A] Mushroom Monster

## 题目描述

Kaylin 喜欢蘑菇。只要把蘑菇放到她的盘子里，她就会把它们吃掉！在本题中，她正在吃一盘蘑菇，而 Bartholomew 会不断往她的盘子里加蘑菇。

我们每隔 $10$ 秒观察一次她盘子里的蘑菇数量。Bartholomew 可以在任何时刻往盘子里加任意个（非负整数）蘑菇，蘑菇离开盘子的唯一方式就是被 Kaylin 吃掉。

请你用两种不同的方法计算出 Kaylin 至少吃了多少个蘑菇：

1. 假设 Kaylin 可以在任何时刻吃掉任意数量的蘑菇。
2. 假设从第一次观察开始，只要盘子里有蘑菇，Kaylin 就以一个恒定的速度吃蘑菇。

例如，若输入为 $10$ $5$ $15$ $5$：

用第一种方法，Kaylin 至少吃了 $15$ 个蘑菇：她先吃掉 $5$ 个，然后 Bartholomew 又加了 $10$ 个蘑菇，然后她又吃掉了 $10$ 个。无论如何，她都不可能吃得更少。

用第二种方法，Kaylin 至少吃了 $25$ 个蘑菇。我们可以确定她吃蘑菇的速度至少为每秒 $1$ 个。她一开始盘子里有 $10$ 个蘑菇。在前 $10$ 秒内，她吃掉 $10$ 个蘑菇，Bartholomew 又加了 $5$ 个蘑菇。接下来的 $5$ 秒，她吃掉 $5$ 个蘑菇，然后盘子在 $5$ 秒内保持空，接着 Bartholomew 又加了 $15$ 个蘑菇。最后 $10$ 秒，她又吃掉了 $10$ 个蘑菇。

## 说明/提示

**数据范围**

- $1 \leq T \leq 100$。

**小数据集（7 分）**

- 时间限制：5 秒。
- $2 \leq N \leq 10$。
- $0 \leq m_i \leq 100$。

**大数据集（8 分）**

- 时间限制：10 秒。
- $2 \leq N \leq 1000$。
- $0 \leq m_i \leq 10000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
4
10 5 15 5
2
100 100
8
81 81 81 81 81 81 81 0
6
23 90 40 0 100 9```

### 输出

```
Case #1: 15 25
Case #2: 0 0
Case #3: 81 567
Case #4: 181 244```

# 题解

## 作者：alice_c (赞：2)

## 思路

### 第一种方法

因为蘑菇离开盘子的唯一方法是被吃掉，当我们看到蘑菇数量在一段时间内减少时，肯定是因为它们被 Kaylin 吃掉了。Kaylin 吃的蘑菇的最小数量是每个 $10s$ 的减少数量的总和，即 $\sum_{i=1}^{n} a_{i-1}-a_i$。

### 第二种方法

在每个 $10s$ 里，我们可以计算 Kaylin 吃蘑菇的速度 $v$。这个 $v$ 必须足够大，以满足我们看到的蘑菇减少情况，它的最小值就是 `max(a[i-1]-a[i])`。如果 $a_i \ge v$，那么她就吃了 $v$ 个蘑菇；否则，她只吃了 $a_i$ 个就没有蘑菇可以吃了。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int t,n,a[1005];
int main()
{
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int ans1=0,v=0,ans2=0;
        scanf("%d",&n);
        for(int j=1;j<=n;j++)
            scanf("%d",&a[j]);
        //第一种方法
        for(int j=2;j<=n;j++)
            if(a[j]<a[j-1]) ans1+=a[j-1]-a[j];
        //第二种方法
        for(int j=2;j<=n;j++)
            v=max(v,a[j-1]-a[j]);
        for(int j=1;j<n;j++)
            ans2+=min(v,a[j]);
        printf("Case #%d: %d %d\n",i,ans1,ans2);
    }
}
``````

---

求过qwq！

---

## 作者：YangFangYe (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/P13215)

### 思路
模拟题

- 问题一：假设这个十秒盘子里的蘑菇比上一个十秒少，此时我们假设 Bartholomew 不加蘑菇，将答案加上两次蘑菇数的差值，否则我们假设 Kaylin 不吃蘑菇。

- 问题二：我们要先找出最少的恒定速度，对于 $1\le i\le n-1$，恒定速度为 $v$，求出最大的 $m_i-m_{i-1}$，如果 $v>m_i$，给答案加上 $m_i$，否则按恒定速度来吃，给答案加上 $v$。
### Code
```cpp
#include<iostream>
int t, m[1005], n, ans, v;

int main() {
	scanf("%d", &t);
	for (int k = 1; k <= t; k++) {
		ans = 0, v = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &m[i]); // Kaylin 盘子里在每个 10 秒时刻的蘑菇数量（包括初始时刻）
			if (i == 1) {
				continue;
			}
			v = std::max(v, m[i - 1] - m[i]);
			if (m[i - 1] - m[i] >= 0) { ans += m[i - 1] - m[i]; }
		}
		printf("Case #%d: %d ", k, ans);
		ans = 0;
		for (int i = 1; i <= n - 1; i++) {
			if (m[i] >= v) { ans += v; }
			else { ans += m[i]; }
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：hlb44 (赞：1)

~~吃蘑菇不怕躺板板吗？~~

[题目传送门](https://www.luogu.com.cn/problem/P13215)

阅读题目，我们发现两方案间有明显区别并且有隐藏条件：

方法一：Kaylin 可在任意时刻吃任意数量的蘑菇。

分讨下：

若后一次观察的蘑菇数量 $m_i$ 小于前一次 $m_{i-1}$，则减少的部分 $m_{i-1}-m_i$ 必须是被吃掉的。

若后一次观察的蘑菇数量 $m_i$ 大于或等于前一次 $m_{i-1}$，则 Kaylin 在此期间可以不吃蘑菇，因此这一阶段吃掉的蘑菇数量为 $0$。

方法二：Kaylin 以固定速度吃蘑菇（只要有蘑菇就持续吃）。

当 Kaylin 以固定速度吃蘑菇，我们为了方便，设速度为每 $10$ 秒吃 $v$ 个，那么每个 $10$ 秒间隔内，吃掉的蘑菇数量为 $v$ 和 $m_{i-1}$ 加上添加的蘑菇数量的和取较小值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fo(i,begin,end) for(int i=begin;i<=end;++i)
#define of(i,begin,end) for(int i=begin;i>=end;--i)
#define fos(i,begin,end,ADD) for(int i=min(begin,end);i<=max(begin,end);i+=ADD)
#define ofs(i,begin,end,ADD) for(int i=max(begin,end);i>=min(begin,end);i-=ADD)
#define debug(val) cout<<#val<<':'<<(val)<<'\n'
#define debug_1(name,i,x) cout<<#name<<"["<<i<<"]:"<<x<<'\n';
#define debug_2(name,i,j,x) cout<<#name<<"["<<i<<"]["<<j<<"]:"<<x<<"\n";
#define ll long long
int main() {
	int T;
	cin>>T;
	for(int case_num=1; case_num<=T; ++case_num) {
		int N;
		cin>>N;
		vector<int>m(N);
		for(int i=0; i<N; ++i) {
			cin>>m[i];
		}
		int y=0;
		for(int i=1; i<N; ++i) {
			y+=max(0,m[i-1]-m[i]);
		}
		int v_max=0;
		for(int i=1; i<N; ++i) {
			v_max=max(v_max,m[i-1]-m[i]);
		}
		v_max=max(v_max,0);
		int z=0;
		for(int i=1; i<N; ++i) {
			z+=min(v_max,m[i-1]);
		}
		cout<<"Case #"<<case_num<<": "<<y<<" "<<z<<endl;
	}
	return 0;
}
```

---

## 作者：RN_GH (赞：1)

作为一个~~合格的萌新~~，只拿了十五分的我找了半天错误，才发现原来满分 15 分！！！

# 1、题目描述
概括一下，题目要求用两种方法计算 Kaylin 至少吃了多少蘑菇：

已知每隔 10 秒观察一次盘子里的蘑菇数量，Bartholomew 会随时加蘑菇，蘑菇仅被 Kaylin 吃掉。

第一种方法：假设 Kaylin 可在任意时刻吃任意数量的蘑菇，求她至少吃的数量。

第二种方法：假设 Kaylin 从第一次观察开始，若盘子有蘑菇则以恒定速度吃，求她至少吃的数量。
# 2、思路
首先我们先来解决第一个问题，也就是方法一：

这里我们可以运用一种贪心的策略：

如果前一个时间段的蘑菇比后一段的蘑菇少，那么就默认他是加上去的，这样**一个都不用吃**；如果前面的比后面多那么就是**只吃不加**，这样可以最小化吃的数量。具体如下：
```cpp
for (int i = 1; i < n; i++){
    way1 += max(m[i - 1] - m[i],0);
}
```
对于第二个问题，也就是方法二：

我们可以先求出每 10 分钟吃的最少蘑菇，不难发现，吃蘑菇的最小速度就是**方法一中每次吃的蘑菇个数的最大数量**

然后再用速度与剩余蘑菇数量作比：如果 10 分钟吃的蘑菇（即速度）大，那么剩余蘑菇不够，**则吃的数量加上剩余蘑菇**即可；如果剩余蘑菇多，也就是够吃，那么**就只能最大速度**。如下：
```cpp
int maxn = 0;
for (int i = 1; i < n; i++){
    maxn = max(maxn,m[i - 1] - m[i]);
}
for (int i = 0; i < n - 1; i++){
  	way2 += min(maxn,m[i]);
}
```
# 3、AC CODE
奉上我丑陋的代码（巨佬勿喷）：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
	cin >> t;
	int cnt = 0;
	while(t--){
		int n;
		cin >> n;
		vector<int> m(n);
		for (int i = 0; i < n; i++){
			cin >> m[i];
		}
		
		int way1,way2;
		way1 = way2 = 0;
		
		// 计算方法1：每次观察间的最大可能减少量之和
		for (int i = 1; i < n; i++){
			way1 += max(m[i - 1] - m[i],0);
		}
		
		int maxn = 0;// 计算方法2：确定恒定的最大吃蘑菇速度
		for (int i = 1; i < n; i++){
			maxn = max(maxn,m[i - 1] - m[i]);
		}
		// 根据恒定速度计算总消耗量
		for (int i = 0; i < n - 1; i++){
			way2 += min(maxn,m[i]);// 每10秒内吃掉的蘑菇数
		}
		
		printf("Case #%d: %d %d\n",++cnt,way1,way2);
	}
	return 0;
}
```

---

## 作者：tujiaqi12 (赞：1)

## 思路
贪心。下文中的 $a[i]$ 相当于题面中的 $m[i]$，~~写题时习惯了~~。  

第一问。由于要使吃的蘑菇数量最少，所以因仅在 $a[i-1] > a[i]$ 时将答案增加 $a[i-1] - a[i]$，具体见以下代码。

```cpp
ans = 0;
for(ll i = 1;i <= n;i++){
    if(a[i-1] > a[i]){//能不吃就不吃 
	ans += a[i-1] - a[i]; 
    }
} 
```
第二问。既然是恒速的，那么可以先求出最小速度。
```cpp
ll v = 0;//最快速度（10秒） 
for(ll j = 2;j <= n;j++){
	v = max(v,a[j-1] - a[j]);
}
```
然后利用求出的最小速度得出答案，具体如下。

```cpp
ans = 0; 
for(ll j = 1;j < n;j++){
	if(a[j] <= v){//吃完，并在10秒时放 
		ans += a[j];
	}
	else{
		ans += v;
	}	
}
```
## 代码  

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n,a[1005],ans;
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		scanf("%lld",&n);
		for(ll j = 1;j <= n;j++){
			scanf("%lld",&a[j]);
		}
		//第一问
		ans = 0;
		for(ll i = 1;i <= n;i++){
			if(a[i-1] > a[i]){//能不吃就不吃 
				ans += a[i-1] - a[i]; 
			}
		} 
		printf("Case #%lld: %lld ",i,ans);
		//第二问
		ll v = 0;//最快速度（10秒） 
		for(ll j = 2;j <= n;j++){
			v = max(v,a[j-1] - a[j]);
		}
		//遍历得出答案 	
		ans = 0; 
		for(ll j = 1;j < n;j++){
			if(a[j] <= v){//吃完，并在10秒时放 
				ans += a[j];
			}
			else{
				ans += v;
			}	
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：SatoruXia (赞：1)

考虑贪心。  
在方法一的情况下，每次吃掉的蘑菇数量不受限制，因此想要确保吃掉的最少就要保证没有溢出，每次刚好吃完。因此在下一次吃完的数量小于上一次时，将**两数之差数量的蘑菇全部吃掉**；否则不吃，让这些多出来的蘑菇全是添加的。至少吃的蘑菇数量就是所有数据执行该操作后的数值之和。  
在方法二的情况下，每次吃的数量一定，因此就要在合理的情况下尽可能溢出。解释一下：如果每次吃的少的话，添的蘑菇就要变多，而最后剩余的是相等的，因此多出来的还是得全吃了，显然不划算。所以每次吃的数量就取**相邻数据之差的最大值**。然后模拟即可。
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int T, N, m[1010];
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> N;
        for (int j = 0; j < N; j++) cin >> m[j];
        int ans1 = 0, ans2 = 0, MAXM = 0;
        //一点小技巧：将两个操作压在一个循环里以节省时间
        for (int j = 1; j < N; j++) {
            if (m[j] < m[j-1]) { //这个判定并不影响第一个操作
                ans1 += (m[j-1] - m[j]);
                MAXM = max(MAXM, m[j-1] - m[j]); //打擂台
            }
            //后一个大于前一个时加0，不用进行操作
        }
        //计算方案二的总和
        for (int j = 0; j < N-1; j++) ans2 += min(m[j], MAXM);
        //输出
        cout << "Case #" << i << ": " << ans1 << " " << ans2 << endl;
    }
    return 0;
}
```

---

## 作者：Lg2307 (赞：0)

## 原题链接：[P13215 \[GCJ 2015 #1A\] Mushroom Monster](https://www.luogu.com.cn/problem/P13215)

**总体思路**：首先建立一个向量 $m$ 用于储存每时刻剩余的磨菇数，再从两种方案入手具体计算再分步输出。

从第一种方案入手，可以看出当第 $i$ 个 $10s$ 时刻所剩余的蘑菇数大于第 $i + 1$ 个 $10s$ 时刻剩余的蘑菇数时，Kaylin 吃了蘑菇且吃的蘑菇数 $=$ $i$ 时刻所吃的蘑菇数 $-$ $i + 1$ 时刻所吃的蘑菇数，依次累加可得出在方案一的条件下至少吃的蘑菇数。

从第二种方案入手，先找出 Kaylin 吃蘑菇的速度 $cnt$，也就是相邻两个时间点蘑菇数量的最大差值，单位为 个 $/10s$，再通过 `min(cnt,m[i - 1])` 依次累加可得出在方案二的条件下至少吃的蘑菇数。

ACcode:

```cpp
#include <bits/stdc++.h>
using namespace std;
long long f,s,cnt;//f：第一种方案，s：第二种方案
int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++ t) {// ++ t 要快于 t ++
        f = s = cnt = 0;
		int N;
		cin >> N;
		vector<int> m(N);
		for (int i = 0; i < N; ++ i) cin >> m[i];
        //第一种方案
		for (int i = 1; i < N; ++ i) {
			if (m[i] < m[i - 1]) {
				f += (m[i - 1] - m[i]);
				cnt = max(cnt, (long long) (m[i - 1] - m[i]));//要转为 long long 型，下同
			}
		}
        //第二种方案
		for (int i = 0; i < N - 1; ++i) if (m[i] > 0)  s += min((long long)m[i], cnt);//累加
		cout << "Case #" << t << ": " << f << " " << s << "\n";
	}
	return 0;
}
```

---

## 作者：yangdezuo (赞：0)

## 解析
### 题目大意
分别输出方法一与方法二的 Kaylin 至少吃掉的蘑菇数量。

### 做法
这其实是一道~~简单~~的模拟题。

我们可以分别分析两种吃蘑菇方法。

#### 方法一
我们要计算相邻时间点蘑菇数量的减少量之和，即 Kaylin 在每个间隔内至少吃掉的蘑菇数‌。

因此，首先遍历数组，比较相邻两个时间点的蘑菇数量，如果后一个时间点蘑菇更少，差值即为该间隔内吃掉的数量，最后累加所有间隔的减少量即可。

#### 方法二
我们需要先确定最大减少速率，再按此速率计算总消耗量‌。

因此，首先遍历数组，计算所有相邻间隔的减少速率，取所有速率中的最大值作为恒定吃蘑菇速率，对每个间隔，按该速率计算 10 秒内吃掉的蘑菇数，**但是不能超过当前蘑菇量**。

---

## 作者：shiziyu111 (赞：0)

# 题目大意

有两个人，其中 Kaylin 吃蘑菇，Bartholomew 在盘子中加入蘑菇。给定你每十秒钟盘子里剩下的蘑菇个数，在两种情况下计算出 Kaylin 最少吃的蘑菇数量。

1. Kaylin 吃蘑菇的数量任意。
2. Kaylin 以恒定的速度吃蘑菇（盘子里有蘑菇时才吃）。

# 分析

问题一：很简单，假如这个十秒盘子里的蘑菇比上一个十秒少，此时我们假设 Bartholomew 不加蘑菇，将答案加上两次蘑菇数的差值，否则我们假设 Kaylin 不吃蘑菇。

问题二：我们要先找出最少的恒定速度，对于 $1\leq i\leq n-1$（最后一次不用吃），求出最大的 $m_i-m_{i-1}$，令恒定速度为 $a$，如果 $a>m_i$，我们就设 Bartholomew 是在观察的前一刻加入蘑菇，即给答案加上 $m_i$，否则按恒定速度来吃，即加上 $a$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		int n,ans1=0,ans2=0,maxn=0;
		int a[1001];
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(i!=1)
			{
				maxn=max(maxn,a[i-1]-a[i]);
				if(a[i-1]-a[i]>=0)
				{
					ans1+=a[i-1]-a[i];
				}
			}
		}
		for(int i=1;i<=n-1;i++)
		{
			if(a[i]>=maxn)
			{
				ans2+=maxn;
			}
			else
			{
				ans2+=a[i];
			}
		}
		//ans2+=a[n]; 千万不要加 
		cout<<"Case #"<<t<<": "<<ans1<<" "<<ans2<<"\n";
	}
	return 0;
}
```

---

