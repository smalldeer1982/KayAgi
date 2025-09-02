# The Great Julya Calendar

## 题目描述

Yet another Armageddon is coming! This time the culprit is the Julya tribe calendar.

The beavers in this tribe knew math very well. Smart Beaver, an archaeologist, got a sacred plate with a magic integer on it. The translation from Old Beaverish is as follows:

"May the Great Beaver bless you! May your chacres open and may your third eye never turn blind from beholding the Truth! Take the magic number, subtract a digit from it (the digit must occur in the number) and get a new magic number. Repeat this operation until a magic number equals zero. The Earth will stand on Three Beavers for the time, equal to the number of subtractions you perform!"

Distinct subtraction sequences can obviously get you different number of operations. But the Smart Beaver is ready to face the worst and is asking you to count the minimum number of operations he needs to reduce the magic number to zero.

## 说明/提示

In the first test sample the minimum number of operations can be reached by the following sequence of subtractions:

  $ 24→20→18→10→9→0 $

## 样例 #1

### 输入

```
24
```

### 输出

```
5```

# 题解

## 作者：fengqiao17 (赞：3)

# Solution

这是一道类似于贪心的题目。要想减去一个数位上的数，肯定是越大越快。
那么下面是我的思路：
1. 首先定义一个 $cnt$，用来记录次数；
2. 只要 $n$ 不为 $0$，就设置一个最大值 $maxi$，进行数位打擂台；
3. 用 $n$ 减去最大值 $maxi$ 即可。

### 坑点
注意不要直接拿 $n$ 取数位，要复制一份 $tmp$，否则会影响结果！！！

## Code
```cpp
//author:fengqiao17
//转载请标明地址：https://616673.blog.luogu.org/solution-cf331c1
#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, cnt = 0; //n以及操作数量cnt
  cin >> n;
  while (n != 0) {
    int tmp = n, maxi = -1;//复制一份（坑点）
    while (tmp != 0) { //打擂台求最大值
      maxi = max(maxi, tmp % 10);
      tmp /= 10;
    }
    n -= maxi; //减去最大值（贪心重点）
    cnt++;
  }
  cout << cnt;
  return 0;//完结撒花
}
```

---

## 作者：RainFestival (赞：3)

记 $x\in i$ 当且仅当 $i$ 中有某一位数字是 $x$。显然，若 $i\neq 0$，必 $\exists x\in\{1,2,3,4,5,6,7,8,9\},x\in i$。

注意到每次必将使得数值减少 $1$，所以我们最多删除 $n$ 次。

设 $dp_i$ 表示 $i$ 至少需要删除 $dp_i$ 次。

首先 $dp_0=0$。

我们可以从 $1$ 到 $i$ 枚举，$dp_i=\min\limits_{1\le x\le 9,x\in i}dp_{i-x}+1$。

$dp_n$ 即为答案。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
int n,dp[1000005];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		dp[i]=1000000000;
		int x=i;
		while (x)
		{
			int p=x%10;x=x/10;
			if (!p) continue;
			dp[i]=std::min(dp[i-p]+1,dp[i]);
		} 
	}
	printf("%d\n",dp[n]);
	return 0;
}
```


---

## 作者：Auto_Accepted (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF331C1)

这道题就是一个很简单的贪心

首先，我们发现， $n$ 每次只要减去 $n$ 所有位上最大的数子，就可以得到最小的次数了。

那问题来了：那如何快速得到 $n$ 每个数位上的数字呢？

这里我选择了用一个堆，因为他可以 $O(\log n)$ 插入， $O(1)$ 查询最大值。

以样例为例：

step 0: $n=24$

step 1: $n=24-4=20$

这时，我们发现，$n$ 减去了他各个数位上数字的最大值（ $4$ ）,变成了 $20$ 。

step 2: $n=20-2=18$

这时， $n$ 数位上数字的最大值为 $2$ ，于是 $n$ 减去了   $2$ ，变为了 $18$ ；

step 3: $n=18-8=10$

现在， $n$ 数位上数字最大值变为了 $8$ ，于是 $n$ 变为了   $18-8$ ，也就是 $10$ 。

step 4: $n=10-1=9$

又经过了一次变换， $n$ 数位上数字的最大值变为了 $1$ ， $n$ 变为了 $10 - 1$ ，就是 $9$ 。

step 5: $n=9-9=0$

最后， $n$ 只剩一位了，数位上数字的最大值自然就是 $n$ ，也就是 $9$ 。

 $n$ 花费了 $5$ 次变为 $0$ ,所以结果为 $5$ 。

最后的最后，贴一下我的代码：
```cpp
#include <bits/stdc++.h>//头文件
using namespace std;
int cnt;
int main(){
	int n;
	cin >> n;
	while(n){
		priority_queue <int> p;//定义堆
		int j = n;//防止n变为0,找一个“替身”
		while(j){
			p.push(j % 10);//把n各个数位的数字放入堆中
			j /= 10;
		}
		n -= p.top();//减去最大值
		cnt++;//次数加一
	}
	cout << cnt;
   	return 0;//好习惯
}
```


---

## 作者：pikabi (赞：2)

### 简单的搜索+贪心问题

题意：给你一个数字 $n$，称作幻数，并进行操作：选出**当前幻数中的某一位作为减数**，并将当前幻数减去该选中的一位数字，得到新的幻数，直至幻数为 0。

C1：$n <= 10^6$

很容易想到，找到一个数每一位上的数字。如 **1833** 可以得到 **1 、 3 、 8** 这三个数字；依次搜索减去每一位上的数字即可， 如上栗子搜索 **1833 - 1 、 1833 - 3 、 1833 - 8** 。

那我们要如何贪心加快速度呢？

我们发现，令 $f_{now}$ 表示数字 $now$ 按题目要求操作的最小步数，则 $f_{now} > f_{now - 1}$ ,**即 $f_{now}$ 是单调递增的**。可以这么想，如果 $now$ 和 $now - 1$ 只有个位数不同，那么$now$ 和 $now - 1$ 可减去的数只有最后一位不同，而 $now $ 二者相差 1 ，减去此数显然相等，当 $now$ 最后一位是 $0$ 时，$now - 1$最多减到个位为0， 而 $now$ 则不能（如果减 0 显然步数增加，不是最优）。综上，**$f_{now}$ 递增**。所以我们从大到小枚举，找到第一个可以减的数就好了。

下面贴上代码--->

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define ll long long
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

int n, f[1000006]; 

inline int dfs(int p){
	if(p < 0) return inf;
	if(p == 0) return 0;
	if(f[p]) return f[p];
	int cnt[10] = {0};
	for(int i = 0; i <= 9; i++) cnt[i] = 0;
	int x = p, t;
	while(x){
		if(x < 10) t = x;
		cnt[x % 10]++;
		x /= 10;
	}
	int now = inf;
	for(int i = 9; i >= 1; i--){
		if(cnt[i]){
			now = min(dfs(p - i) + 1, now);
			break;
		}
	}
	f[p] = now;
	return now;
}

int main(){
	n = read();
	dfs(n);
	printf("%d\n",f[n]);
    return 0;
}

```



完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：Colorful_Unicorn (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF331C1)

这题是一道贪心题。

贪心策略是每次选择所有位置上中最大的数。

设当前遍历到的位数上的值为 $x$，用 $ans$ 记录所有位置上的最大值，$a_i$ 为 $n$ 的第 $i$ 个位置所代表的数，$x$ $\in$ {$a_1,a_2,......,a_i$}，$ans$ 应更新为 $\max$ ($ans,x$)。

拿 $12$ 举例：

首先减去最大的 $2$，成为 $10$。 

再减去 $1$，成为 $9$。

最后减去 $9$，成为 $0$。

需要操作 $3$ 次。

好，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,cnt,q;//cnt 记录每次更新后所有位置的最大值 
int main()
{
	cin >> n;
	q=n; //预处理 q
	while (n>0)//判断边界 
	{
		cnt=-1; //cnt的初始值
		while (q)//枚举每个位置 
		{
			cnt=max(cnt,q%10);//求出每个位置上的最大值 
			q/=10;//更新位置 
		}
		n-=cnt;//更新 n 
		ans++;
		q=n;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：XCH_0803 (赞：0)

这是一道简单的贪心。

只要我们每次减去剩下的数 $n$ 中最大的数字, 就可以得到最优解。

我们来举个例子：

比如说输入 $32$ ;

第一次先减去 $3$，剩下 $29$ ;

第二次减去 $9$，剩下 $20$ ;

第三次减去 $2$，剩下 $18$ ;

第四次减去 $8$，剩下 $10$ ;

第五次减去 $1$，剩下 $9$ ;

最后一次减去 $9$，变成 $0$ 。

所以输入 $32$，我们最少要进行 $6$ 次操作。

话不多说，上代码！

```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int sum=0;
	while(n){
		int u=n;
		int maxn=0;
		while(u){//找到剩余n里面的最大数字 
			maxn=max(maxn,u%10);
			u/=10;
		}
		n-=maxn;
		sum++;
	}
	cout<<sum;
    return 0;
}
```


---

