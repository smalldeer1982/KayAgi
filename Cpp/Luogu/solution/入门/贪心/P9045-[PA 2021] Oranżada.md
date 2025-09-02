# [PA 2021] Oranżada

## 题目描述

有一排共 $n$ 瓶橙汁，其中第 $i$ 瓶的品牌为 $a_i$。

你可以花费 $1$ 个单位的的代价交换两瓶相邻的橙汁。

求最小代价使得最左边 $k$ 瓶橙汁品牌两两不同。

## 说明/提示

#### 样例 #1 解释
最优方案为先交换位置 $3$ 和 $4$ 的瓶子、再交换位置 $4$ 和 $5$ 的瓶子，接着交换位置 $2$ 和 $3$ 的瓶子，最后交换位置 $3$ 和 $4$ 的瓶子，共 $4$ 次操作。
#### 样例 #2 解释
显然无解。
#### 数据范围
对于 $100\%$ 的数据，$1 \leq k, a_i \leq n \leq 5 \times 10^5$。

## 样例 #1

### 输入

```
5 3
3 3 3 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2
1 1 1```

### 输出

```
-1```

# 题解

## 作者：lichenzhen (赞：16)

## 题目大意
有 $n$ 瓶品牌不同的橙汁，其中第 $i$ 瓶的品牌是 $a_i$，求出使前 $k$ 瓶橙汁品牌不相同的最少操作的次数（只能交换两瓶相邻的橙汁）

## 题目解法
可以看出来，这是一道入门的贪心题目，但是还是有一定的思维难度的。还要用道桶思想。

首先，我们考虑一下什么时候是无解的。我们把橙汁出现的品牌的数量定义为 $d$，那么如果 $d<k$，此时无论如何都会有相同的品牌也就是无解。其他情况都是有解的。

之后考虑一下有解的时候如何做才能使操作次数最少，我们考虑想办法把没有出现过的品牌尽量往左边也就是前面移动，用一个桶来存储这个品牌是否出现，如何输入的是一个新的品牌，就把 $d+1$，之后就是计算将这个品牌移动需要的次数（也就是代价），次数就是 $i-(d+1)$，去括号可得 $i-d-1$，也就是用当前的位置减去已经出现的品牌再减去 $1$。

之后就是有两点值得注意的
- 要注意开`long long`，最终的操作次数会爆`int`（惨痛的教训，实测能得到 $86$ 分的高分）。
- 这道题目读入的数据量很大，最多可以读入 $10^5$ 个数据，使用`cin`速度比较慢（虽然也可以过），建议使用快读，提升的速度很大。截止到我发文前我使用快读的代码是最优解。
### 参考代码（不带快读）
```cpp
#include<bits/stdc++.h>
using namespace std;
bool book[500001];//只需要两个数据就可以，开bool节省空间
long long ans;
int a,n,k,d;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(book[a]==0)
		{
			book[a]=1;
			ans+=i-d-1;
			d++;
		}
		if(d==k)//橙汁已经出现的品牌数已经满足了要求，直接输出代价并结束循环就可以了，后面的数据不用读了，节省时间。
		{
			cout<<ans;
			return 0;
		}
	}
	cout<<-1;
}
```
[使用快读的参考代码](https://www.luogu.com.cn/paste/ivchugsk)


---

## 作者：ivyjiao (赞：7)

首先，我们思考：什么时候无解？

当所有橙汁品牌数 $\geq k$ 时，我们总能把 $k$ 种品牌不同的橙汁移到 $a_1$ 至 $a_k$ 去，但是当品牌数 $\leq k$ 时，我们无论如何也做不到。

那么，对于一个位置靠左的且之前没有出现过的品牌的橙汁，我们把它移到 $a_{p+1}$（$p$ 为之前出现过的品牌数），这样是次数最小的（因为我们每一次移动肯定是要让这个橙汁离目标更近的，这样才能最优，所以我们不能往右移），次数就是 $i-(p+1)$，拆括号得 $i-p-1$。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
using namespace std;
bool f[500001];
long long p,c,n,k,a;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a;
        if(!f[a]){
            c+=i-p-1;
            p++;
            f[a]=1;
        }
		if(p==k){
		    cout<<c;
		    return 0;
		}
	}
	cout<<-1;
}
```


---

## 作者：ryf_loser (赞：3)

此题蠢蠢的模拟即可通过。

用贪心的思维思考这道题，我们可以轻松的出一个显而易见的结论：
当 $a_{i}$ 在之前从未出现过的情况下，我们可以把它往前挪，这样就可以得到局部最优解。

显然这也是全局最优解，我们把 $a_{i}$ 前出现的商品种类记为 $tot$，易得此商品到达 $tot+1$ 位置上需要 $i-tot-1$ 步，这样一次下去，即可的到最优解。

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,x,tot;
long long ans;
bool a[500005];
int main(){
	scanf ("%d%d",&n,&k);
	for (int i=1;i<=n;i++){
		scanf ("%d",&x);
		if (!a[x])a[x]=1,ans+=i-tot-1,tot++;//记录。
		if (tot==k){printf ("%lld",ans);return 0;}//输出最优解。
	}
	puts("-1");
	return 0;
}
```


---

## 作者：gloomy_ (赞：3)

一道求最少操作数的题。  
**算法选取**  
由于数据范围不大，考虑使用贪心以及类似桶排序的存储方法。  
**变量定义**  
`int a[]` 存储每瓶橙汁的品牌。  
`bool dis[]` 存储每瓶橙汁是否在左边已排好的区域中出现过。  
`bool fin` 存储是否有解。  
`int s` 存储已排好的瓶数。  
`long long ans` 存储答案。  
**计算**  
从左往右遍历，如果第 i 瓶果汁的品牌（$a_i$）没有在左边已排好的 $s$ 瓶中出现过，即 $dis_{a_i}$=false,那么将他移到左起第 $s+1$ 的位置上，须要移动 $i-s+1$ 次。   
接下来:   
```cpp
dis[a[i]]=true;
s++;
```
**AC代码**  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500001];
bool dis[500001],fin=false;
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int s=0;
	long long ans=0;
	memset(dis,false,sizeof(dis));
	for(int i=1;i<=n;i++)
	{
		if(dis[a[i]]==false)
		{
			ans=ans+i-s-1;
			dis[a[i]]=true;
			s++; 
		}
		if(s==k)
		{
			fin=true;
			break;
		}
	}
	if(fin==false)
	{
		printf("-1");
	}
	else
	{
		printf("%lld",ans);
	}
	return 0;
} 
```


---

## 作者：Light_Star_RPmax_AFO (赞：1)

## [PA2021] Oranżada

### 前言

[传送门](https://www.luogu.com.cn/problem/P9045)

[更好的阅读体验](https://www.luogu.com.cn/blog/JJL0610666/p9045-pa2021-oranada-ti-xie)

### 题目描述

有一排共 $n$ 瓶橙汁，其中第 $i$ 瓶的品牌为 $a_i$。

你可以花费 $1$ 个单位的的代价交换两瓶相邻的橙汁。

求最小代价使得最左边 $k$ 瓶橙汁品牌两两不同。

## 思路

前 $k$ 个需要不一样的地方一个一个确定，我们肯定先从最左边找起（这样就可以最小），找到与前 $x$ 个已经确定的不同的，我们就把他放到 $x+1$ 的位置上，其实与插入排序思想差不多。

### 踩雷

交换位数之大，需要开一个 long long，不然就只有 $86$ 分。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[500010];
bool b[500100];
int main(){
	int n,g=0,k;
	long long ans=0;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(!b[a[i]]){
			ans+=i-g-1;//记录要到交换几次才可以到，加在 ans。
			g++;//记录确定了多少个。
			b[a[i]]=1;//记录已有。
		}
		if(g==k){
			cout<<ans;
			return 0;//找完了，因为我们从左边开始找起，所以这就是最小值。
		} 
	}
	cout<<-1;//如果选了一遍还是没有解，就是无解了。
	
}
```

---

## 作者：zzy0618 (赞：1)

### 题目大意

有一排共 $n$ 瓶橙汁，其中第 $i$ 瓶的品牌为 $a_i$，求最小的相邻交换次数使得最左边 $k$ 瓶橙汁品牌两两不同。

### 大体思路

比较简易的贪心题。

首先是无解的情况，如果品牌数目小于 $k$，此时无解，反之我们肯定可以通过一定次数的交换使得其符合要求。

然后是如何交换，要注意一个点，是**最左边**的 $k$ 瓶，那么我们肯定选择靠左但是之前没有出现过的品牌移动至左边。

通过一个我们定义的 $cnt$ 记录目前**符合要求**的橙汁数量，一个桶（因为 $n\le 5 \times 10^5$，很适合用桶）记录已经出现过的品牌。每次我们将一个橙汁向左移动共需 $i-(cnt+1)$ 也就是 $i-cnt-1$ 次。

还有几个优化和注意事项：

- 输入有 $ 5 \times 10^5 $ 的数量级别，使用快读能让单位从秒变为毫秒。

- 如果 $n<k$ 直接输出 $-1$，少浪费时间。

- 当 $cnt=k$ 时，直接输出，减少时间。

- 惨痛教训，要开 **long long**。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}//快读 
bool f[500001];
signed main() {
	register int cnt = 0, ans = 0, n, k, x, i;
	n = read(); k = read();
	if (n < k) {//不符合直接结束掉 
		cout << -1;
		return 0;
	}
	for (i = 1; i <= n; i++) {
		x = read();//由于前面的情况已经用桶记录，无需再用数组 
		if (!f[x]) {//前面没出现过 
			ans += i - cnt - 1;
			cnt++;
			f[x] = true;
		}
		if (cnt == k) {//已经满足直接输出 
			cout << ans;//一次输出就不必在意优化啦 ^_^ 
			return 0;
		}
	}
	cout << -1;
}
```



---

## 作者：BlackPanda (赞：1)

**[Problem](https://www.luogu.com.cn/problem/P9045)**

------------
## Description

给定 $n$ 个整数，其中第 $i$ 个数表示为 $a_i$。
你可以花费 $1$ 代价交换相邻的两个数，请你求出用最小代价使得左边 $k$ 个数各不相同，如果无解输出 $\verb!-1!$。

------------
## Solution

简单的模拟题。

首先，如果将 $a$ 数组去重后的数量小于 $k$，也就是不同数的数量小于 $k$，一定无解。

然后，从左边开始遍历，如果 $a_i$ 在遍历过的数中还没出现过，那么我们可以通过 $i - sum$ 次操作将 $a_i$ 移到前 $k$ 个数中，其中 $sum$ 表示遍历到第 $i$ 个数时选定的前 $k$ 的数的数量。

------------
## Code

```cpp
#include <iostream>
#include <map>
using namespace std;

#define int long long

int n, k;
map<int, int> mp, vis;
int c, res, sum;
int a[500005];

signed main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i ++ )
	{
		cin >> a[i];
		if (mp.find(a[i]) == mp.end())
			c ++ ;
		mp[a[i]] ++ ;
	}
	if (c < k)
	{
		cout << -1;
		return 0;
	}
	for (int i = 1; i <= n; i ++ )
	{
		if (vis.find(a[i]) == vis.end())
		{
			sum ++ ;
			res = res + i - sum;
		}
		vis[a[i]] ++ ;
		if (sum >= k)
		{
			cout << res;
			return 0;
		}
	}
	cout << -1;
	return 0;
}
```

---

## 作者：small_john (赞：1)

## 分析

首先设 $s$ 表示橙汁品牌数（变输入边增加）。如果最后 $s<k$，那么肯定不行（不能凑齐 $k$ 个两两不同的橙汁）。所以分析 $s\ge k$ 的情况。

对于每个满足 $1\le i\le n$ 的 $i$，如果 $a_i$ 没有出现过，那么就可以把 $a_i$ 通过交换放在第 $s$ 个位置（移到离 $i$ 最近的位置），由于一次只能交换相邻的两瓶果汁，所以要换 $i-s-1$ 次。

~~总而言之，大水题。~~

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n,k,s;
long long ans;//不开long long见祖宗 
bool vis[N];//vis[i]等于0表示i品牌没出现过 
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1;i<=n;i++)
	{
		int a;//在线操作：每读入一个操作数据，就进行一次操作 
		scanf("%d",&a);
        if(!vis[a])//等同于vis[a]==0 
           ans+=i-s-1,s++,vis[a] = 1;
		if(s==k)//品牌数达到了 
		    return printf("%lld",ans),0;//输出后return 0 
	}
	printf("-1");//s<k的情况，输出-1 
}
```

---

## 作者：封禁用户 (赞：0)

## 思路
在所有品牌的总数小于 $k$ 时，如样例二的解释所说，显然无解。考虑贪心，因为我们是要求最少步数，所以我们移动的饮料必定是其品牌中最靠左的。然后，对于每个品牌的饮料 $i$，我们一定能够将其移动到位置 $i$。所以我们直接将每个需要移动的饮料与它的品牌之差累加即可。

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
int a[1000000];
bool vis[1000000];
int cnt,idx;
int b[1000000];
int ans;
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(!vis[a[i]]) 
		{
			vis[a[i]]=1;
			cnt++;
			if(idx+1<=k) b[++idx]=i;
		}
	}
	if(cnt<k) return cout<<-1,0;
	for(int i=1;i<=idx;i++) ans+=b[i]-i;
	return cout<<ans,0;
}
```


---

