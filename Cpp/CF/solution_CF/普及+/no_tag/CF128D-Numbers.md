# Numbers

## 题目描述

One day Anna got the following task at school: to arrange several numbers in a circle so that any two neighboring numbers differs exactly by 1. Anna was given several numbers and arranged them in a circle to fulfill the task. Then she wanted to check if she had arranged the numbers correctly, but at this point her younger sister Maria came and shuffled all numbers. Anna got sick with anger but what's done is done and the results of her work had been destroyed. But please tell Anna: could she have hypothetically completed the task using all those given numbers?

## 样例 #1

### 输入

```
4
1 2 3 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6
1 1 2 2 2 3
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
6
2 4 1 1 2 2
```

### 输出

```
NO
```

# 题解

## 作者：封禁用户 (赞：2)

## 题解：CF128D Numbers

### 解题思路

一眼**构造**题。

首先，我们可以减去一些明显不可能的情况，也就是**排序**后任意两个相邻的数差 $\ge 2$ 的情况。

接下来，我们可以缩小数据范围，也就是将所有值都减去最小值。

以上两步可得：$0 \le a_i < n$。证明也很简单，这里可以感性理解一下。若最大的 $a_i \ge n$，且经第二步操作，最小的 $a_i$ 总等于 $0$。此时，若想保证排序后的任意两个相邻的数的差 $\le 1$，则必须有至少 $n + 1$ 个元素，所以可以证明。

其实，前面所有的转化都是为了能够将所有的数装进桶里面，方便后续运算。

这时，我们就可以推出一个类似转移的**贪心**。将现在的位置记为 $t$ 后，初始时 $t = 0$，则整个转移可表示为：

+ 若 $t + 1$ 位置仍有数字，则 $t \gets t + 1$。
+ 若 $t + 1$ 位置的桶为空时，可以分以下情况：
	- 若 $t - 1$ 位置仍有数字，则 $t \gets t - 1$。
   - 若 $t - 1$ 位置的桶为空且 $t = 1$ 时：跳出转移。
   - 若 $t - 1$ 位置的桶为空且 $t \ne 1$ 时：说明没有可行的数列。
   
最后，我们检查桶里面还有没有剩余的元素，如果有，则代表没有可行的数列，可以理解为在以上所有构造中构造的可行数列丢下了这几个元素。

如果一个数列闯过了以上所有判断，那么就证明这个数列是可行的，输出"`YES`"，开心结束程序。

### 参考代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , a[100005] , b[100005] , cnt;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i];
	}
	sort(a + 1 , a + n + 1);
	for(int i = 2 ; i <= n ; i++)
	{
		if(a[i] - 1 > a[i - 1])
		{
			cout << "NO";
			return 0;
		}
	}
	for(int i = n ; i >= 1 ; i--)
	{
		a[i] -= a[1];
		b[a[i]]++;
	}
	while(1)
	{
		b[cnt]--;
		if(b[cnt + 1])
		{
			cnt++;
		}
		else if(cnt == 1 && !b[0])
		{
			break;
		}
		else if(b[cnt - 1])
		{
			cnt--;
		}
		else
		{
			cout << "NO";
			return 0;
		}
	}
	for(int i = 1 ; i <= 100000 ; i++)
	{
		if(b[i])
		{
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
	return 0;
}
```

---

## 作者：rui_er (赞：2)

简单构造题。

题意：给定 $n$ 个数，是否能排成一圈，使相邻两个数差 $1$。

---

根据题意，为了使相邻两个数差 $1$，圆圈中 $+1$ 和 $-1$ 的次数必定相等才能组成闭环，因此 $n$ 必须是偶数，对于奇数可以直接输出无解（代码注释 `{1}`）。

然后同样根据相邻两个数差 $1$ 的性质，我们将原数列排序，枚举相邻两个下标的数，如果差大于 $1$ 也输出无解（代码注释 `{2}`）。

之后找到数列最小值，把每个数减去最小值再加 $1$，即可得到一串与原数列等效的、最小值为 $1$ 的数列，经过前面两个特判，可以保证最大值不超过 $10^5$。然后从最小值开始，可以 $+1$ 时选择 $+1$，否则看看是否可以 $-1$，若不可以就跳出循环。

由于闭环性质，要形成环则最后一个数必定是 $2$，如果不是 $2$ 则不能成环，输出无解（代码注释 `{3}`）。

否则将整个桶扫一遍，如果有地方不为 $0$ 则代表成环失败，输出无解（代码注释 `{4}`）。

否则即代表我们构造出了一个符合题意的环，输出有解即可。

这样就水过了一道 CF `*2000` 的构造题（

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 1e5+5, inf = 1e9;

int n, a[N], buc[N], mi = inf;

int main() {
	scanf("%d", &n);
	if(n & 1) return puts("NO"), 0; // {1}
	rep(i, 1, n) scanf("%d", &a[i]), mi = min(mi, a[i]);
	sort(a+1, a+1+n);
	rep(i, 2, n) if(a[i] - a[i-1] > 1) return puts("NO"), 0; // {2}
	rep(i, 1, n) ++buc[a[i]-mi+1];
	int u = 1; --buc[1];
	loop {
		if(buc[u+1]) --buc[++u];
		else if(buc[u-1]) --buc[--u];
		else break;
	}
	if(u != 2) return puts("NO"), 0; // {3}
	rep(i, 0, N-1) if(buc[i]) return puts("NO"), 0; // {4}
	return puts("YES"), 0;
}
```

---

## 作者：b2314huangruizhong (赞：1)

# 思路
先给原数组排序，如果相邻元素的差 $>1$ 就直接输出 `NO`。然后存进一个桶里。然后从 $1$ 开始暴力排环判断即可。

注意 $n\le10^5 $ 但每个正整数 $\le10^9$，所以我们应对桶进行优化。
 
暴力排环时，我们应先尽量将排环数字递加排列（读后思考：为什么？），如果没有更大的数字，再将小的数字接在后面，如果没有就说明无解或结束。


[评测记录](https://codeforces.com/problemset/submission/128/298678428)

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],c[100005],cnt;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);//排序
	for(int i=2;i<=n;i++)
		if(a[i]-a[i-1]>1)return cout<<"NO",0;//如果相邻的两个数差大于1就不可能了
	for(int i=1;i<=n;i++)c[a[i]-a[1]+1]++;//用桶存+优化，避免爆内存 
	cnt=1;c[cnt]--;n--;
	while(n--){//暴力排环
		if(c[cnt+1])c[++cnt]--;//优先选大1的数
		else if(c[cnt-1])c[--cnt]--;//否则选小1的数
		else break;}//否则无解或者结束

	if(cnt!=2)cout<<"NO";
	else if(n==-1)cout<<"YES";
	else cout<<"NO";//请读者自行思考
	return 0;}
```

---

## 作者：Exber (赞：1)

不错的一道 *2000 构造题。

首先离散化，若这些数在值域上不连续则无解。设离散化后 $i$ 出现了 $cnt_i$ 次。

由于这是一个环，不是很好维护，那么考虑断环为链。显然在哪里断都是一样的，所以我们不妨在某个 $1$ 的前面断开，断开后即需要构造一个这样的东西：

![](https://cdn.luogu.com.cn/upload/image_hosting/ac17ox31.png)

也就是一条相邻两点高度恰好相差 $1$ 的折线，满足从 $1$ 出发，最后到达 $2$ 并且高度为 $i$ 的点出现了 $cnt_i$ 次。

考虑最大的高度 $tot$，显然高度为 $1,2,3,\dots,tot$ 的点都至少需要一个才能到达这个高度，那么不妨让这段“上坡路”在最前面，显然不影响答案：

![](https://cdn.luogu.com.cn/upload/image_hosting/c4an3bn6.png)

那么考虑高度同为 $tot$ 的剩余 $cnt_{tot}-1$ 个最高点，显然从当前点出发遍历完它们的折线应该是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/lhyrdvvk.png)

那么不妨把省略号部分的折线都移到最后，显然也不会影响答案：

![](https://cdn.luogu.com.cn/upload/image_hosting/0dump4dn.png)

也就是说，我们用 $cnt_{tot}$ 个高度为 $tot-1$ 的点，完成了所有高度为 $tot$ 的点的遍历。

接下来如法炮制处理高度为 $tot-1$ 的点，高度为 $tot-2$ 的点，高度为 $tot-3$ 的点，$\dots$，高度为 $2$ 的点即可。

完整代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int S=100005;

int n,a[S],b[S],cnt[S];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[i-1])
		{
			if(i!=1&&a[i]!=a[i-1]+1)
			{
				puts("NO");
				return 0;
			}
			tot++;
		}
		cnt[tot]++;
	}
	for(int i=1;i<=tot;i++)
	{
		if(--cnt[i]<0)
		{
			puts("NO");
			return 0;
		}
	}
	for(int i=tot;i>=2;i--)
	{
		if(cnt[i]<0)
		{
			puts("NO");
			return 0;
		}
		cnt[i-1]-=cnt[i]+1;
	}
	puts(cnt[1]==-1?"YES":"NO");
	return 0;
}
```

---

## 作者：zsyyyy (赞：1)

# CF128D 2000 贪心

## 题意

给你 $n$ 个正整数 $(3 <= n <= 10^5)$ ，每个正整数都不超过$10^9$，问是否能将这 $n$ 个数排成一个环, 使得换上相邻两个数的差都是 $1$。

## 思路

将给的 $n$ 个数存入桶中，可以将最终构造出的环看做从最小的数递增到最大的数，再从最大的数递减到最小的数，这样，最大的数和最小的数都用了一次，其他数都用了两次。

例子：

a：1 2 2 3 3 4 4 5

ans：1 2 3 4 5 4 3 2

然后如果还有剩余的数的话，可以在两个相邻的数间反复。

例子：

a：1 2 2 3 3 |3 3 4 4| 4 4 5

ans：1 2 3 |4 3 4 3| 4 5 4 3 2

解释：竖杠内的数字表示比第一个例子（标准形式）多出来的数，也就是用在两个相邻的数间反复解决的。

容易发现，最小的数的最大的数用了一次，其他数用了两次，总数是偶数，如果有多出来的数用来在两个相邻的数间反复，也不会改变奇偶性，总数依然是偶数。所以，$n$ 必须是偶数才能构造出来。

时间复杂度：$O(n)$


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+10;
int n,a[MAXN],minn=LONG_LONG_MAX,maxx,tmp;
map<int,int> book;
//book[i]表示a数组中i的个数，因为a[i]小于10^9，所以要开map
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
	if(n%2) //n为奇数直接无法构造
	{
		puts("NO");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		book[a[i]]++;
		minn=min(a[i],minn);
		maxx=max(a[i],maxx);
	}
	for(int i=minn;i<=maxx;i++)
	{
		if(!book[i]) //也就是数列不连续的情况，显然无法构造
		{
			puts("NO");
			return 0;
		}
	}
	for(int i=minn+1;i<=maxx-1;i++)  book[i]-=2;
	book[minn]--;
	book[maxx]--;
  	//中间的数个数减2，其他数个数减1
	for(int i=minn;i<=maxx;i++)
	{
		if(book[i]==0)  continue;
		if(book[i]<0)
		{
			puts("NO");
			return 0;
		}
		tmp=min(book[i],book[i+1]); //在i和i+1间反复
		book[i]-=tmp;
		book[i+1]-=tmp;
		tmp=min(book[i-1],book[i]); //在i和i-1间反复
		book[i-1]-=tmp;
		book[i]-=tmp;
	}
	for(int i=minn;i<=maxx;i++)
	{
		if(book[i]!=0) //也就是依然有剩余的数
		{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
```


---

## 作者：Tjaweiof (赞：1)

# CF128D 题解
[题目传送门](https://www.luogu.com.cn/problem/CF128D)

首先先给原数组排序，如果相邻元素的差 $>1$ 就直接输出 `NO`。然后存进一个桶里。然后从 $1$ 开始暴力排环即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n, a[100001], c[100001], cnt;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; i++){
		if (a[i] - a[i - 1] > 1){
			cout << "NO";
			return 0;
		}
	}
	for (int i = 1; i <= n; i++){
		c[a[i] - a[1] + 1]++;
	}
	cnt = 1;
	c[cnt]--;
	n--;
	while (n--){
		if (c[cnt + 1]){
			c[++cnt]--;
		} else if (c[cnt - 1]){
			c[--cnt]--;
		} else {
			break;
		}
	}
	if (cnt != 2){
		cout << "NO";
	} else if (n == -1){
		cout << "YES";
	} else {
		cout << "NO";
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

## 思路

很容易想到 $O(n)$ 的做法。

先把数组从小到大排序，首先如果每个数之间的差不是 $1$，那么显然这组数据是不能组成环的。

再用一个桶数组把数据离散化后丢到桶里面。

离散化大概就是把最小的离散化成 $1$，再把后面的数减去最小的数后再加 $1$，以便存到桶里面（这样桶的内存最大只要开到 $1e5 + 5$ 就好了）。

然后 $O(n)$ 模拟一遍连环即可，优先用 $now + 1$ 组成环，其次是 $now - 1$，但如果二者都没有了，那么这组数据也是不合法的。

最后如果组成环的数据不是 $n$ 个，亦不合法。如果最后一个数据不是 $2$，亦不合法（解释在代码里）。

最后剩下的就是合法的方案。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n;
int a[maxn], t[maxn];

inline int read() {
	int ret = 0, f = 1;char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (f == '-') f = -f;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		ret = (ret << 3 + ret << 1) + ch - '0';
		ch = getchar();
	}
	return ret * f;
}

int main() {
	n = read();
	if (n & 1) {
		puts("NO");
		return 0;
	}
	for (int i = 1;i <= n;i++) a[i] = read();
	sort(a + 1, a + 1 + n);
	for (int i = 1;i <= n;i++) {
		if (a[i] - a[i - 1] > 1) {
			puts("NO");
			return 0;
		}
		t[a[i] - a[1] + 1]++;//改下标，丢进桶里面(防止爆内存) 
	}
    int now = a[1];
    t[1]--;
    int i = 0;
    while (++i) {
        if (t[now + 1]) now++, t[now]--;
        else if (t[now - 1]) now--, t[now]--;
        else break;
    }
    if (i != n) {//没用完就不合法
        puts("NO");
        return 0;
    }
    if (now != 2) {//由于离散化后没有-1，所以最后一个不为2也不合法
        puts("NO");
        return 0;
    }
    puts("YES");
    return 0;
} 
```

---

## 作者：qusia_MC (赞：0)

## 题目分析
就是能不能把 $n$ 个数排成一列，使得每一列上的数的差都为 $1$。要注意的是起点终点也要是。

## 思路

首先我们既然要他们排成一列，我们尽量让前面都是升序的后面都是降序的（这样简单容易理解）由于数据范围太大了（$a_i \le 10^9$） 开这么多的数据一定要爆炸的。~~（计算机：运行不了一点）~~ 就用map存了。每一个数据有对应的，具体占多少内存我也不知道，但是空间一定够了。

我们把每一个数都存在图里，由于题目没规定环的顺序，所以存就完事了不用排序。

怎么构建环呢？

我们先将 $a_1$ 加入环中。

然后优先让这个环升序，所以先把每一个数据看看有没有比他大一的数。如果有的话就优先把那个数接到环上。

否则就找有没有比他小一的，如果有，直接把他整上。

如果都没有的话，就是没有了，直接输出不行。

## 特判
首先就是 $n$ 为奇数时不行。

举两个例子吧：（假设 $n$ 为奇数）。

$a$ 数组 $={1,2,3}$。

连到最后发现 $3 - 1=2$ 不行。

$a$ 数组 $={1,2,3,4,5,4,5,4,3}$。

发现最后 $3-1=2$，不行。

这是第一个特判条件。

再就是如果把一个数组快排后出现了不连续的数字就不行，连到这里就断了。

## 举例
我们根据上面讲的思路举个例子：

$n=8$，$a$ 数组 $={1,5,4,4,3,2,3,2}$

第一步，排序：

排完后的 $a$ 数组 $={1,2,2,3,3,4,4,5}$

特判 $1$ ：$n$ 不是奇数，可以过关。

特判 $2$ 每个数字都是连续的，过关！

首先，把 $a_1$ 加入环里。当前的环：${1}$，当前的 $a$ 数组：${2,2,3,3,4,4,5}$。

然后，判断 $a$ 数组里有没有 $2$。发现有 $2$，把他接到环上。

目前的环：$1,2$ 目前的 $a$ 数组：$2,3,3,4,4,5$。

第 $3$ 步，判断数组里有没有 $3$，发现有，直接把他接到环上。

目前的环：$1,2,3$ 目前的 $a$ 数组：$2,3,4,4,5$。

第 $4$ 步，判断数组里有没有 $4$，发现有，直接把他接到环上。

目前的环：$1,2,3,4$ 目前的 $a$ 数组：$2,3,4,5$。

第 $5$ 步，判断数组里有没有 $5$，发现有，直接把他接到环上。

目前的环：$1,2,3,4,5$ 目前的 $a$ 数组：$2,3,4$。

第 $6$ 步，判断数组里有没有 $6$，发现没有，在找 $4$，发现有，直接把他接到环上。

目前的环：$1,2,3,4,5,4$ 目前的 $a$ 数组：$2,3$

第 $7$ 步，判断数组里有没有 $5$，发现没有，在找 $3$，发现有，直接把他接到环上。

目前的环：$1,2,3,4,5,4,3$ 目前的 $a$ 数组：$2$。

第 $8$ 步，判断数组里有没有 $4$，发现没有，在找 $2$，发现有，直接把他接到环上。

目前的环：$1,2,3,4,5,4,3,2$ 目前的 $a$ 数组：没有了。

判断头尾能否相连：$2-1=1$，可以。

## 代码
有了例子的证明很容易就能写出代码：

```
#include<bits/stdc++.h>
//十年OI九年亡，不用万能头你就狂
using namespace std;
#define no cout<<"NO"<<endl
#define yes cout<<"YES"<<endl
#define br break
//究极偷懒
int main()
{
	map<int,int> q;//记录信息
	int n,a[114514];
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		q[a[i]]++;
	}//输入数据并统计
	if(n%2!=0)
	{
		no;return 0;
	}//是奇数就不行了
	sort(a+1,a+n+1);
    //排序
	for(int i=2;i<=n;i++)
	{
		if(a[i]-a[i-1]>=2)
		{
			no;return 0;
		}//出现了不连续的，不行。
	}
	int jd=a[1],sum=0;
	while(1)
	{
		if(sum+1>=n)br;
		if(q[jd+1]>0)
		{
			q[jd+1]--;
			jd++;sum++;
		}//有没有比他大一的
		else if(q[jd-1]>0)
		{
			q[jd-1]--;
			jd--;sum++;
		}//没找到再找小一的
		else
		{
			no;return 0;
		}//都没找着就不行了
	}
	if(abs(jd-a[1])!=1)no;
    //最后判断一下首尾能不能相连
	else yes;
    //历经千难万难终于OK了，勇士我敬佩你
	return 0;
}
```

---

## 作者：Rose_Melody (赞：0)

## Solution：CF128D Numbers
[题目传送门](https://www.luogu.com.cn/problem/CF128D)

### 题目分析

对这个数组先排个序，容易发现：**当相邻两数之差 $>1$ 时，是无解的**。

然后再开一个桶出来，存进去，从 $1$ 开始枚举，扫一遍过去，暴力排环即可。（注意：由于闭环性质，成环的最后一个数必须是 $2$）

这样就能轻松通过了。

### AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
const int N = 1e5 + 5 ;
int n , a[N] , b[N] , cnt; 
inline int read(){
	int x = 0 , f = 1 ;
	char ch = getchar() ;
	while(ch < '0' || ch > '9'){
		ch = getchar() ;
	}
	while('0' <= ch && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48) ; 
		ch = getchar(); 
	}
	return x * f ;
}

signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	n = read() ;
	for(int i = 1;i <= n;i ++){
		a[i] = read() ;
	}
	stable_sort(a + 1 , a + n + 1) ;
	for(int i = 2;i <= n;i ++){
		if(a[i] > a[i - 1] + 1){
			cout << "NO" ;
			return 0 ;
		} 
	}
	for(int i = 1;i <= n;i ++){
		b[a[i] - a[1] + 1] ++ ;
	}
	cnt = 1 ;
	b[1] -- , n -- ;
	while(n --){
		if (b[cnt + 1]){
			b[++ cnt] --;
		}
		else if (b[cnt - 1]){
			b[-- cnt] --;
		}
		else {
			break;
		}
	}
	if (cnt != 2){
		cout << "NO";
	}
	else if (n == -1){
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	return 0;
}
```

---

## 作者：crzcqh (赞：0)

## 思路

由于不关系数值的顺序，所以先排序一遍，存一下所有数值的出现次数，我们先从最小值开始贪心，如果有 $a_i+1$ 或 $a_i-1$，就删掉这个数，遍历到下一个数，以此类推，如果有遍历不下去的地方，既为 `No`，遍历到最后，既为 `Yes`。

**注意**：

1. 最后遍历到的数应该是最小值 $+1$，不然构不成环。
2. $n$ 为奇数可以直接判断不行，因为 $+1$ 和 $-1$ 数量不等，必然构不成环。
3. $a_i\le 10^9$，用 map 或离散化存数字出现的次数。

然后就可以快乐的 AC 了。

---

## 作者：Allanljx (赞：0)

## 题意
有 $n$ 个数，问这 $n$ 个数能否构成环，即构成的环任意两数的差都为一。

## 思路
简单的贪心。当这 $n$ 个数排序后有两个数之差大于一时显然不行，当 $n$ 是奇数时也不行。判完这两种情况后就可以从最小的开始模拟，每次选一个比它大一且没有用过的，如果没有就选一个比它小一且没有用过的，如果也没有，就不可能构成环。当所有数都被用过后还要判一下是否和第一个数差一，即首尾是否可以相连。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],now,sum;
map<int,int> mp;//map记录，数组开不下
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(n%2)//n为奇数
	{
		cout<<"NO";
		return 0;
	}
	sort(a+1,a+n+1);//排序
	now=a[1];//从最小的开始，now是当前的数
	for(int i=2;i<=n;i++)
	{
		if(a[i]-a[i-1]>=2) return puts("NO"),0;//差大于一
	}
	for(int i=2;i<=n;i++)
	{
		mp[a[i]]++;//统计个数
	}
	while(1)
	{
		if(sum>=n-1) break;
		if(mp[now+1]) mp[now+1]--,now++,sum++;//往大连
		else if(mp[now-1]) mp[now-1]--,now--,sum++;//往小连
		else return puts("NO");//不能连了
	}
	if(abs(now-a[1])!=1) return puts("NO"),0;//首尾是否可以相连
	cout<<"YES";
}
```

---

