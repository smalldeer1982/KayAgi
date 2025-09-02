# Cashier

## 题目描述

Vasya has recently got a job as a cashier at a local store. His day at work is $ L $ minutes long. Vasya has already memorized $ n $ regular customers, the $ i $ -th of which comes after $ t_{i} $ minutes after the beginning of the day, and his service consumes $ l_{i} $ minutes. It is guaranteed that no customer will arrive while Vasya is servicing another customer.

Vasya is a bit lazy, so he likes taking smoke breaks for $ a $ minutes each. Those breaks may go one after another, but Vasya must be present at work during all the time periods he must serve regular customers, otherwise one of them may alert his boss. What is the maximum number of breaks Vasya can take during the day?

## 说明/提示

In the first sample Vasya can take $ 3 $ breaks starting after $ 2 $ , $ 5 $ and $ 8 $ minutes after the beginning of the day.

In the second sample Vasya can take $ 2 $ breaks starting after $ 0 $ and $ 2 $ minutes after the beginning of the day.

In the third sample Vasya can't take any breaks.

## 样例 #1

### 输入

```
2 11 3
0 1
1 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
0 5 2
```

### 输出

```
2```

## 样例 #3

### 输入

```
1 3 2
1 2
```

### 输出

```
0```

# 题解

## 作者：封禁用户 (赞：6)

嗯，很水的一道题。

但是当时没看清题，搞得白白少了200分。

做法就是一边读入一边计算，对于每一个时间点，我们算出它和上一个时间点的差距，然后除以每次休息的时间就是休息的最大值。

注意最后有一段时间也要算进休息时间里。当时就是没想到这个玩意。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,a;
int ans;
int main(){
	scanf("%d%d%d",&n,&l,&a);
	int tmp=0; 
	for(int i=1;i<=n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		ans+=(x-tmp)/a; 
		tmp=x+y;
		//printf("%d\n",ans); 
	}
	ans+=(l-tmp)/a;
	printf("%d",ans);
}
```

# Orz zjt

# Orz yww 

# Orz myh

---

## 作者：WsW_ (赞：1)

### 思路：
客人来的时候不能休息，只有没客人的时候休息。  
因为题目中保证 $t_i+l_i\le t_{i+1}$，因此当第 $i$ 个客人走，但第 $i+1$ 个客人还没来的时候就可以休息 $t_{i+1}-(t_i+l_i)$ 分钟。  
题目中说每次休息时间为 $a$ 分钟，问能完整地休息几次，所以在第 $i$ 个客人和第 $i+1$ 个客人之间的间隙，可以完整休息 $\left\lfloor\dfrac{t_{i+1}-(t_i+l_i)}{a}\right\rfloor$ 次。我用变量 $last$ 记录上一个客人走的时间（这样不用开数组），即 $last=t_i+l_i$，那么原式化为 $\left\lfloor\dfrac{t_{i+1}-last}{a}\right\rfloor$。  
注意：第 $0$ 分钟到第一个客人来 $t_1$ 之间可以休息，最后一个客人走到第 $L$ 分钟之间也可以休息。

---
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,L,a;
int last;//last初始值为0，第一次循环计算第一个客人来之前的休息
int t,l;
int ans;

int main(){
	scanf("%d%d%d",&n,&L,&a);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&t,&l);
		ans+=(t-last)/a;//int自动向下取整
		last=t+l;
	}
	ans+=(L-last)/a;//最后人都走了还可以休息
	printf("%d",ans);
	return 0;
}
```

---
[$\mathtt{AC}$ 记录](https://codeforces.com/problemset/submission/1059/214451911)

---

## 作者：䒛夢 (赞：1)

努力努力再努力的䒛夢他又来了，

今天的我依旧在写题解
 
 # 题意
 给你 $n$ 个顾客，你一天一共是 $l$ 小时，每次休息是连续 $a$ 个小时不能停，停了就废了，每个顾客再 $ti$ 来，待 $li$ 小时,求一下能休息几次。
 # 思路
 首先看到这题的时候吧，我是第一时间以为是贪心的
 做完发现不对，$ti+li<=ti+1$ 已经保证了我们的数据范围不会卡重，就与贪心并没有任何关系。
 
 我们就是只要把区间空隙留出来就行。
 
 **例如第一个样例**
 
 0表示空闲，1表示顾客来了
 
 0 1 1 0 0 0 0 0 0 0 0 0
 
 可以看出来，从第二秒之后就有大把的时间用来休息，
 一共有九秒时间用来休息，$9/a=3$ 所以输出了3。
 
 在中间一部分空闲时间判断能否休息，在判断最开始和最后能否休息，能就增加次数。
 
 # 代码附上
 ```
 #include<iostream>
#include<cstdio>
using namespace std;
int l,a,n,ans=0;
struct node{
	int t,l;
}v[100100];
int main()
{
	scanf("%d%d%d",&n,&l,&a);
	for(int i=1 ; i<=n ; ++i)
		scanf("%d%d",&v[i].t,&v[i].l);
	v[0].t=0;//将开始时间设为0
	v[0].l=0;
	for(int i=1 ; i<=n ; ++i)
		ans=ans+(v[i].t-v[i-1].t-v[i-1].l)/a;//判断每一次能否休息
	ans+=(l-v[n].t-v[n].l)/a;最后再加一遍结尾的时间
	printf("%d",ans);
	return 0;
}
 ```
 完结撒花

---

## 作者：Silence_World (赞：0)

# 思路

较为简单的贪心题，比较好想出来，我们可以把整个时间看成一个数轴，每个客人在 $t$ 时来，占用 $l$ 的时间，问未被占用的空间有多少个连续的 $a$，很明显，每个人与前一个人之间的空闲就是当前人的空间 $-$ 前一个人来的时间 $-$ 持续的时间，再除以 $a$ 即贡献的次数，累加即为答案。

# AC 代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005];
int b[1000005];
signed main(){
	int n,t,l;
	cin>>n>>l>>t;
	a[n+1]=l;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	int ans=0;
	int sum=0;
	for(int i=1;i<=n+1;i++){
		ans+=(a[i]-sum)/t;
		sum=a[i]+b[i];
	}
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现这是一道模拟题。我们设 $n$ 为客人数，每次休息时间为 $a$，一天长度为 $L$，$t_i$ 表示第 $i$ 名客人到来的时间，$l_i$ 表示第 $i$ 名客人持续占用的时间，$sum$ 表示 $t_{i-1}+l_{i-1}$，则休息的次数为 $\sum\limits_{i=1}^{n+1}{\frac{t_i-sum}{a}}$，其中 $t_{n+1}=L$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,L,a,sum,t,l,ans;
int main(){
	cin>>n>>L>>a;
	for(int i=1;i<=n;i++){
		cin>>t>>l;
		ans+=(t-sum)/a;
		sum=t+l;
	}
	cout<<ans+(L-sum)/a;
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1059A)

一道贪心题。

我们可以记录每一位客人离开的时间，当下一位客人来临时，他们之间空闲的时间就是我们休息的时间。
```cpp
for (int i = 1; i <= n; i++) {
    int t, l;
    cin >> t >> l;
    ans += (t - endt) / a;
    endt = t + l;
}
```
最后再加上所有客人都走后的空闲时间即可。

```cpp
ans += (L - endt) / a;
```
#### 最后给出代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int  n, L, a, endt, ans; // endt 表示上一位客人离开的时间
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> L >> a;
    for (int i = 1; i <= n; i++) {
        int t, l;
        cin >> t >> l;
        ans += (t - endt) / a; // 计算空闲时间能休息多少次
        endt = t + l; // 更新 endt
    }
    ans += (L - endt) / a; // 最后计算所有客人都走后的空闲时间能休息多少次
    cout << ans;
    return 0;
}
```




---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[点我返回题目](https://www.luogu.com.cn/problem/CF1059A)

这道题题意十分好理解。给定一天的长度 $ L $ ，每段休息的时间 $ a $ ，客人的人数 $n$ ，每位客人到来的时间 $t_i$ 和离去的时间 $l_i$ ，保证 $t_i$ $+$ $l_i$ $\leq$ $t_{i+1}$ （就是说不会有两位客人同时在店中）。求最多能休息几次。

使用一个循环来输入 $t_i$ 和 $l_i$ ，建一个变量 $breaktime$ 来记录时间，每次输入后答案加上上一个客人离去与这一个客人到来之间的时间可以休息多少次，再更新时间就行了。注意算上最后一个客人离去后的时间。

说的有点绕口，没关系，直接看代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,L,a,t[100010],l[100010],breaktime=0,ans=0;
//breaktime是计时器 
int main(){
    cin>>n>>L>>a;
    for(int i=1;i<=n;i++)
    {
        cin>>t[i]>>l[i];
        ans=ans+(t[i]-breaktime)/a;
        breaktime=t[i]+l[i];
    }
    ans=ans+(L-breaktime)/a;
    cout<<ans;
    return 0;
}
```


---

## 作者：_HiKou_ (赞：0)

因为题目输入是按照从小到大的顺序读入的，所以不用排序啦！

思路：

1. 输入三个数。
2. 进入循环，每次都把这次的开始时间和上次的结束时间之间的差值算出来（即没有客人的空闲时间）。因为一次休息的时间为 $a$，要想得到每个区间的最大值就用差值除以 $a$。
3. 因为最后一个客人离开后还有一段空闲时间，所以要把这一段的休息时间也加上。
4. 输出 $ans$。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int st[114514],len[114514];//恶臭数组
int main(){
	int n,l,a,ans=0,i;
	scanf("%d%d%d",&n,&l,&a);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&st[i],&len[i]);
		ans+=(st[i]-(st[i-1]+len[i-1]))/a;//可以休息的区间个数
	}
	ans+=(l-(st[n]+len[n]))/a;//再算一次
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：I_m_FW (赞：0)

这道题很简单 ， 没有区间类的贪心 ， 只要模拟就行了 。 

只要求出上次你完成任务的结尾时间然后和当前任务时间相减就是你的空闲时间 ， 但是一定要注意最后一步要处理 $l$ 和最后一个任务的差值 ， 要不然会出你做完任务干站着的问题 。 建议此题变红 。 

代码 ：
```
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int l,a,n;
int t[N],k[N];
int main(){
	cin>>n>>l>>a;
	int ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&t[i],&k[i]);
		ans+=floor((t[i]-t[i-1]-k[i-1])/a);
	}
	ans+=floor((l-t[n]-k[n])/a);
	cout<<ans;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
定义一天长度为 $L$，每次休息的时间为 $a$。一天会有 $n$ 个客人到访，第 $i$ 个客人会在 $t_i$ 的时刻到访，会停留 $l_i$ 的时间。只有在没有客人的时候才能够休息，求最多能够休息的次数。

**数据范围：$0\leqslant n\leqslant 10^5,1\leqslant a\leqslant L\leqslant 10^9,0\leqslant t_i\leqslant L-1,1\leqslant l_i\leqslant L,t_i+l_i\leqslant t_{i+1},t_n+l_n\leqslant L$。**
## Solution
我们求出每两个客人到访之间的空闲时间，然后依次可以求出每段空闲时间可以休息的次数，最后求和即可。
## Code
```cpp
int n, len, per, t[100007], l[100007], rest[100007], ans;

int main() {
	scanf("%d%d%d", &n, &len, &per);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &t[i], &l[i]);
		rest[i] = t[i] - (t[i - 1] + l[i - 1]);
	}
	rest[n + 1] = len - (t[n] + l[n]);
	for(int i = 1; i <= n + 1; ++i) ans += (rest[i] / per);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：帅到报警 (赞：0)

## 热爱发水题题解的我又来了！！！

### 【题意描述】
Vasya 在商店里找到一份工作，他每天要接待 n 个客人，第 i 个客人要从 ti 开始接待 li 分钟，而 Vasya 要在有空时吸烟（这个习惯似曾相识），每根烟要抽 a 分钟，问他一天最多抽几根烟。（数据保证前一个客人接待结束时下一个客人没来）

### 【分析】
除法原理

每个时间间隔除以 a ，求个和就好了

### 【正解】
```cpp
#include <bits/stdc++.h>
#define N 100001
using namespace std;

int n, m, a, ans;
struct Node{
	int st, le, ed;
	bool operator < (const Node b)
	const {return st < b.st;}
}p[N];

int main()
{
	cin >> n >> m >> a;
	for(int i = 1; i <= n; i++)
		cin >> p[i].st >> p[i].le,
		p[i].ed = p[i].st + p[i].le;
	sort(p + 1, p + n + 1);
	ans += p[1].st / a;
	for(int i = 2; i <= n; i++)
		ans += (int)((p[i].st - p[i - 1].ed) / a);
	ans += (int)((m - p[n].ed) / a);
	cout << ans;
		
	return 0;
}
```

---

