# Polycarp at the Radio

## 题目描述

Polycarp is a music editor at the radio station. He received a playlist for tomorrow, that can be represented as a sequence $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is a band, which performs the $ i $ -th song. Polycarp likes bands with the numbers from $ 1 $ to $ m $ , but he doesn't really like others.

We define as $ b_{j} $ the number of songs the group $ j $ is going to perform tomorrow. Polycarp wants to change the playlist in such a way that the minimum among the numbers $ b_{1},b_{2},...,b_{m} $ will be as large as possible.

Find this maximum possible value of the minimum among the $ b_{j} $ ( $ 1<=j<=m $ ), and the minimum number of changes in the playlist Polycarp needs to make to achieve it. One change in the playlist is a replacement of the performer of the $ i $ -th song with any other group.

## 说明/提示

In the first sample, after Polycarp's changes the first band performs two songs ( $ b_{1}=2 $ ), and the second band also performs two songs ( $ b_{2}=2 $ ). Thus, the minimum of these values equals to $ 2 $ . It is impossible to achieve a higher minimum value by any changes in the playlist.

In the second sample, after Polycarp's changes the first band performs two songs ( $ b_{1}=2 $ ), the second band performs three songs ( $ b_{2}=3 $ ), and the third band also performs two songs ( $ b_{3}=2 $ ). Thus, the best minimum value is $ 2 $ .

## 样例 #1

### 输入

```
4 2
1 2 3 2
```

### 输出

```
2 1
1 2 1 2 
```

## 样例 #2

### 输入

```
7 3
1 3 2 2 2 2 1
```

### 输出

```
2 1
1 3 3 2 2 2 1 
```

## 样例 #3

### 输入

```
4 4
1000000000 100 7 1000000000
```

### 输出

```
1 4
1 2 3 4 
```

# 题解

## 作者：Ninelife_Cat (赞：4)

不难证明 $n$ 个数中 $1$ 到 $m$ 出现次数最小值的最大值为 $\lfloor \frac{n}{m} \rfloor$。

有一个比较显然的贪心思想就是保持尽可能多的数不变。

那么我们就开个桶统计一下每个数出现的次数，如果次数还没到最大值说明这个数不用被更改。

然后因为 $n$ 和 $m$ 的范围比较小，所以我们完全可以枚举 $1$ 到 $m$ 中的每个数判断它出现次数是否到达最大值，如果没有，那么就从当前可更改的数中随便选一个改成它就行了。

核心代码：

```cpp

const int N=2e3+10;
int n,m,a[N],cnt[N],ans,vis[N];
//ans记录更改次数,cnt记录某个数的出现次数
signed main()
{
	n=read();m=read();ri int p=n/m;//p为最大值
	for(ri int i=1;i<=n;++i)
	{
		a[i]=read();
		if(a[i]<=m&&cnt[a[i]]<p)
			++cnt[a[i]],vis[i]=1;//vis记录这个数是否需要更改
	}
	for(ri int i=1;i<=m;++i)
		while(cnt[i]<p) for(ri int j=1;j<=n;++j)
			if(!vis[j]) {vis[j]=1,a[j]=i,++cnt[i],++ans;break;}
	cout<<p<<" "<<ans<<endl;
	for(ri int i=1;i<=n;++i)
		cout<<a[i]<<" ";
	return 0;
}

```

---

## 作者：XXh0919 (赞：1)

我就直接照搬楼上的了！

这道题可以用贪心。本题的贪心思想就是尽可能让更多的数不变。于是我们就可以用一个桶来装每个数出现的次数，若这个数的出现次数还没到最大值就说明这个数不用被更改。接着我们再枚举 $1$ 至 $m$ 每一个数并判断这个数的出现次数是否达到最大值，若没有达到最大值，就从当前可更改的数里面选一个改成当前数即可。

关于这个最大值的计算，通过观察样例，我们干脆就大胆假设最大值就是 $\lfloor \frac{n}{m} \rfloor$ 就行了，直接输出即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e6 + 15;

int n, m, ans;
int d[N], a[N], vis[N];

signed main() {
	scanf ("%lld%lld", &n, &m);
	int t = n / m;
	for (int i = 1; i <= n; i ++) {
		scanf ("%lld", &d[i]);
		if (d[i] <= m && a[d[i]] < t) {
			a[d[i]] ++;
			vis[i] = 1;
		}
	}
	for (int i = 1; i <= m; i ++) {
		while (a[i] < t){
			for (int j = 1; j <= n; j ++) {
				if (!vis[j]) {
					a[i] ++;
					ans ++;
					vis[j] = 1;
					d[j] = i;
					break;
				} 
			}
		}
	}
	printf ("%lld %lld\n",t, ans);
	for (int i = 1; i <= n; i ++) {
		printf ("%lld ", d[i]);
	}
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

考虑贪心。

要放置 $n$ 个数，同时 $m$ 个数中出现次数最少的要最大，显然这 $n$ 个位置要尽量均匀的分配给这 $m$ 个数。则出现次数最小的应为 $\left\lfloor \frac{n}{m}\right\rfloor $。

则此时问题在于如何分配均匀且修改次数尽量小。首先判断每一个数的出现次数是否已经达到最低标准显然可以维护桶记录出现次数解决。随后如果未满足要求显然要寻找富余位置进行更改，但看到 $1\le n,m\le 2000$ 显然可以想到暴力寻找空余位置（即循环查看位置对应的桶所记录的出现次数是否比标准多，如果多了直接更改即可），随后更改下更改位置对应的桶的出现次数即可（把不满足的数对应的桶加一，已经满足的减一）。

代码请自行编写，难度较低。

---

