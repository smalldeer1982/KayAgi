# Multithreading

## 题目描述

Emuskald is addicted to Codeforces, and keeps refreshing the main page not to miss any changes in the "recent actions" list. He likes to read thread conversations where each thread consists of multiple messages.

Recent actions shows a list of $ n $ different threads ordered by the time of the latest message in the thread. When a new message is posted in a thread that thread jumps on the top of the list. No two messages of different threads are ever posted at the same time.

Emuskald has just finished reading all his opened threads and refreshes the main page for some more messages to feed his addiction. He notices that no new threads have appeared in the list and at the $ i $ -th place in the list there is a thread that was at the $ a_{i} $ -th place before the refresh. He doesn't want to waste any time reading old messages so he wants to open only threads with new messages.

Help Emuskald find out the number of threads that surely have new messages. A thread $ x $ surely has a new message if there is no such sequence of thread updates (posting messages) that both conditions hold:

1. thread $ x $ is not updated (it has no new messages);
2. the list order 1, 2, ..., $ n $ changes to $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ .

## 说明/提示

In the first test case, threads 2 and 5 are placed before the thread 1, so these threads must contain new messages. Threads 1, 3 and 4 may contain no new messages, if only threads 2 and 5 have new messages.

In the second test case, there may be no new messages at all, since the thread order hasn't changed.

In the third test case, only thread 1 can contain no new messages.

## 样例 #1

### 输入

```
5
5 2 1 3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
4 3 2 1
```

### 输出

```
3
```

# 题解

## 作者：___define___ (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF270B)

## 题目大意

有一个序列，每次操作可以把第一个数插到任意位置，求使得这个序列变为有序的最小操作次数。

## 思路

其实推出这题的解法有两种方法（

第一种是看样例凭直觉写出正解，而第二种就是推出来的了。

我们的每一次操作都要尽量把数放到最终的位置，由于每次只能操作第一个数，所以只需找到最后一次操作的位置，就可以知道最少的操作次数了，那么这个位置就是序列中最后一个 $a_{i-1} > a_i$。

知道这些，这道题就可以很轻松地写出代码了。

[AC 代码](https://codeforces.com/contest/270/submission/287925454)

---

## 作者：FeiYu32 (赞：4)

## 思路解析

因为最后要求的是单调递增的序列，所以只需要找出处于末尾的最长上升子序列即可，然后再把它前面的所有元素全部插入这个最长上升子序列中就能满足条件，并且没有更优解。

那么最终答案就是这个最长上升子序列前面所有元素的总数，即前一个元素的下标，不断比较枚举即可得出。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
long long n,a[100009],b=0;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]<a[i-1])b=i-1;
    }
    cout<<b<<endl;
}
```

---

## 作者：Never_care (赞：4)

### 思路
有一个序列 $a$，每次操作可以把 $a_1$ 插到任意位置，至少需要多少次操作才能把序列变成一个有序序列。  

最少的次数，每一次操作都要尽量把数放到最后序列的最终位置，且序列保证单调递增，而每个 $a_i$ 都是不相同的。通过以上推论，可以得出最后的操作在最后一个 $a_i>a_{i+1}$ 的位置，用 $ans$ 保存答案即可。

### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
const int N=1e5+5;
int n;
int a[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int ans=0;
	for(int i=1;i<n;i++){
        if(a[i]>a[i+1])
            ans=i;
    }
	cout<<ans;
    return 0;
}
```

---

## 作者：Wendy_Hello_qwq (赞：3)

[题目传送门。](https://www.luogu.com.cn/problem/CF270B)

[原文食用效果更佳。](https://www.luogu.com/article/k5yqctkm)

## 题意

给定 $n$ 和长度为 $n$ 的数组，操作第一个数，插入到任意位置，至少几次能使这个序列有序。

## 分析

每一次操作时，我们要确定最后一次的操作位置，这样才不会导致当 $a=\{1,3,2,4,5\}$ 时，不移动的情况了。

所以我们要找到最后一次的操作位置，就是 $a_i>a_{i+1}$，在循环过程中记录下来就可以了。

## Code

```cpp
#include <cstdio>
using namespace std;
int n, res, a[100007];
int main() {
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf ("%d", &a[i]);
	for(int i = 1; i < n; i++) {
		// 确定每一次最后一个 a[i] > a[i + 1]
		if (a[i] > a[i + 1])
		// 确定 res 
			res = i;
	}
	printf ("%d", res);
	return 0;
}
```

[$AC$ 记录。](https://codeforces.com/problemset/submission/270/292624741)

完结撒花。

作者写题解不易，点个赞再走呗。

---

## 作者：Leap_Frog (赞：3)

### P.S.
这篇题解已经写的事无巨细了，如果还不能过审那就是我水平太低了。  

### Problem.
给定一个初始序列，初始状态为 $\{1,2,...,n\}$。  
每次可以选择一个数把他提到最前面。  
求至少进行多少次操作来把这个序列变成 $\{a_1,a_2,...,a_n\}$。  

### Solution.

#### Step1. 转化题意
首先，我们倒过来考虑，我们考虑把 $\{a_1,a_2,...,a_n\}$ 这个序列变成 $\{1,2,...,n\}$。  
那么这样操作就应该是把当前这个序列地第一号元素插到序列的任意一个地方  

#### Step2. 观察性质
我们发现，最终序列是单调递增的，初始序列不一定是。  
同时，根据贪心地思想，我们对于每个第一个元素，如果存在它后面有一个比它小的 $a_k$，那么当前这个序列还没变成最终的 $\{1,2,...,n\}$ 序列。  
又因为转化后的题意告诉我们，当前只能对第1个数进行操作，所以此时我们必须操作。  
然后，由于题目保证了 $a_i$ 之间互不相同，那么我们总能找到当前 $a_1$ 的最终位置，然后把 $a_1$ 插入到最终位置。  
所以对于每个不符合条件的 $a_i$，我们至多只需要一次把它变对。  

#### Step3. 得出结论
由于转化后的题意只允许我们操作第一个元素，所以即使当前这一位已经满足了，它后面还有没有满足地元素，那它也必须被操作。  
所以我们只需要找出最后一个不满足题意的数，那它之前地所有数必须要被操作。  

### Coding.
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r,a[100005];
int main()
{
	scanf("%d",&n),r=0;//答案
	for(int i=1;i<=n;i++) scanf("%d",a+i);//读入
	for(int i=2;i<=n;i++) if(a[i-1]>a[i]) r=i-1;//找到最后面的不满足它后面的小于它的位置
	return printf("%d\n",r),0;//那个位置就是答案
}
```

---

## 作者：zhouchuer (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF270B)
### 题意
给定一个长度为 $n$ 的序列 $a$，保证每个 $a_i$ 互不相同，每次可以移动 $a_1$ 至任何位置，问至少需要多少次操作可以将该序列变为 $1$ 至 $n$ 的全排列序列 $\{1,2,\cdots,n\}$。

### 思路
这题结论非常简单，每个 $a_i$ 互不相同，易证操作 $a_1$ 时只用一次操作便可确定其位置，后续不用再更改。由于序列保持单调递增，因此可以确定最后一次操作在最后一个 $a_k>a_{k+1}$ 的位置，因此得操作次数 $t=k$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,t,a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
        cin>>a[i];
    }
	for(int k=1;k<n;k++){
        if(a[k]>a[k+1])
            t=k;
    }
	cout<<t;
    return 0;
}
```

---

## 作者：monkeyking_houshan (赞：1)

一道非常非常水的黄题。

## 题目大意： ## 

一个序列，每次操作可以将第一个数插到任意位置，求将这个序列变为一个从小到大的有序的数列的最少次数。

## 思路： ##

每次操作我们都要尽量把第一个数放在最终位置，但我们每次只能操作第一个数，所以可以得出结论：我们只需找到最后一次操作的位置，就可以求出最少的操作次数，而最后一次操作就在最后一次判断 $a_i > a_{i+1}$ 的位置。

### AC Code: ###
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114514],n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		if(a[i]>a[i+1]){
			ans=i;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：天使宝贝 (赞：1)

[原题面传送门](https://codeforces.com/problemset/problem/270/B)

### 题意简述
有一个长度为 $n$ 的序列，每次操作可以将该序列的第一个数插入到任意位置，问至少要操作多少次才能使该序列有序。

### 思路&分析
不难发现，对于每次操作我们都能只用一次操作就让该数到达最终位置，由此确定最后的操作一定是在最后一个 $a_i > a_{i + 1}$ 的位置。

### code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false), cin.tie(0)
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define dep(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
constexpr int MAXN = 1e5 + 5;
int n, a[MAXN], ans;
int main()
{
	IOS;
	cin >> n;
	rep(i, 1, n)
		cin >> a[i];
	rep(i, 1, n - 1)
	{
		if (a[i] > a[i + 1])
			ans = i; 
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：monkeyking_QAQ (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/CF270B)   
[原题快速传送通道。](https://codeforces.com/problemset/problem/270/B)
### 大意：

一个序列，每次操作可以把第一个数插到任意位置，求将这个序列变为一个有序的数列的最少次数。

-------------------

### 思路：

每次操作都要尽量把第一个数放在最终位置，由于每次只能操作第一个数，所以得出结论：只需找到最后一次操作的位置，就可以求出最少的操作次数，而最后一次操作就在 $a_i > a_{i+1}$ 的位置。

---------------------

### AC Code:

![](https://cdn.luogu.com.cn/upload/image_hosting/0uv5cbia.png)

---

## 作者：陈嘉逸2012 (赞：1)

## 思路
题目说只能对第一个元素进行操作，那么需要比较每次的第一个元素和第二个元素进行比较，当 $a_i>a_{i+1}$ 时，让计数器自增 $1$。

显然这是不正确的。举个例子：

设 $a=\{5,4,1,3,2\}$。

1. 将 $5$ 进行操作，此时 $a=\{4,1,3,2,5\}$。
2. 将 $4$ 进行操作，此时 $a=\{1,3,2,4,5\}$。
3. * 有人说：这时候 $1<3$，所以不用进行操作，显然是错的。
   * **再次强调，题目说只能对第一个元素进行操作**，当 $a_i>a_{i+1}$ 时，按理来讲不用改变顺序，可是如果后面的序列顺序是不正确的话（比如此序列），那就必须得进行操作。
   * 所以需要记录最后一次 $a_i>a_{i+1}$ 的位置，此元素也要进行操作，此时 $a=\{3,1,2,4,5\}$。
4. 将 $3$ 进行操作，此时 $a=\{1,2,3,4,5\}$。

经过以上分析后，写代码变得巨简单。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int a[maxn],n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++){
		if(a[i]>a[i+1]) ans=i;//套公式
	}
	cout<<ans;
}
```
## 闲话
* 此题非常简单，感觉 $\color{yellow}黄$ 有点过了，建议降 $\color{orange}橙$ 或 $\color{red}红$。
* 洛谷`CF`的 $\text{RemoteJudge}$ 啥时候能修好？

---

## 作者：RAY091016 (赞：0)

### 1. 题目解释

给出一个长为 $n$ 的序列，求最少的操作次数使得序列变为一个 $1$ 到 $n$ 的序列。

一次操作：将队首元素放至队内任意位置。

### 2. 思路

由于最后的序列单调递增，故没有经过操作的数必然也单调递增。

所以我们考虑寻找最长上升子序列。

但这题不一样的地方是它寻找的子序列必然是连续的。

原因在于假如不连续，中间断开的地方无法取出（因为必须从队首取元素）。

因而我们寻找最长连续上升子序列。

### 3. 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100100],cnt=1,maxn=-1e9;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		if(a[i+1]>a[i]){
			cnt++;
		}
		else{
			maxn=max(maxn,cnt);
			cnt=1;
		}
	}
	maxn=max(maxn,cnt);
	cout<<n-maxn;
	return 0;
}
```

---

## 作者：programmer330 (赞：0)

## 题解：CF270B Multithreading

### 题意复述

给定一个长度为 $n$ 的序列 $a$，每次可以选择序列的最开头，将其插入至 $a$ 中的任意位置。请问最少经过多少次操作，可以使得原序列变为一个 $1$ 到 $n$ 的全排列序列。




### 正解思路

假设这个数列中的各个数依次为 $a_1,a_2,a_3,\cdots,a_n$。

因为最后要形成全排列序列，所以没有经过操作的数**一定单调不递减**。但是这题与最长上升子序列不同，**无需**动态规划。

从序列 $a_n$ 开始遍历，初始设 $i=n$，假如对于 $i$，$a_i<a_{i-1}$，那么中断，此时 $a_1,a_2,a_3,\cdots,a_n$
 就是需要操作的数，那么 $i-1$ 即为需要输出的答案，在下面的代码中以 $ans$ 表示。否则 $i$ 减去 $1$。


### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define N 105
int n;
int a[1000001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int num;
	int ans;
	int i;
	for(i=n;i>=2;i--){
		if(a[i]<a[i-1])break;
	}
	ans=i-1;
	cout<<ans;

	return 0;
}

```

---

## 作者：TiAmo_qwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF270B)

也是一道很水的黄题，推一下思路就出来了。

# 题意：

给你长度 $n$ 的序列，每次选择序列开头将其插入至 $a$ 中的任意位置。请问最少经过多少次操作，可以使得原序列变为一个单调递增序列。

# 思路：

由于 $a$ 中的元素各不相同，并且每次只操作 $a[1]$，说明操作 $a[1]$ 只需一次就可以把他调整到对应的位置。

这样就可以知道每次操作在 $a[i]>a[i + 1]$ 的位置，最后一次操作便在最后一个 $a[i]>a[i + 1]$ 的位置。又因为每次操作只需要一次就可以把 $a[i]$ 调整到对应位置，得出 $ans=i$。$ans$ 表示答案。

所以可以得出这个代码：

```
for(int i = 1; i <= n; i++)
{
    if(a[i] > a[i + 1]) 
    {
        ans = i;
    }
}
```
# 完整CODE


```
#include <bits/stdc++.h>

using namespace std;

int a[100005];

int main()
{
    long long n, ans;
    cin >> n;
    
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    
    for(int i = 1; i <= n; i++)
    {
        if(a[i] > a[i + 1]) 
        {
            ans = i;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Guoliyuan2023 (赞：0)

### 题外话（可以跳过）：
本蒟蒻的第~~十一万四千五百一十~~四篇题解，烦请管理员包容亿下……

找到一篇能写的题解真不容易啊……
# 正题：CF270B Multithreading
## 题目
[CF270B 原题传送门](https://www.luogu.com.cn/problem/CF270B)

给定一个初始序列 $\{1 , 2 , 3 , \dots , n\}$。

每次指定一个数，让它到最前面。

求至少进行多少次操作，把这个序列变成 $\{a_1 , a_2 , a_3 , \dots , a_n\}$（$a_i$ 互不相同）。
## 思路
直接上结论：只需要找出最后一个不满足题意的数，那它之前所有的数都要操作。

证明：考虑反证法，题意变成：把 $\{1 , 2 , 3 , \dots , n\}$ 变成 $\{a_1 , a_2 , a_3 , \dots , a_n\}$，这样操作，应该把当前序列的第一个元素插到序列的任意一个地方。

经过观察和思考，发现：

1. 最终序列是单调递增的，但初始序列不一定。

2. 根据贪心，对于每个第一个元素，如果它后面存在比它小的 $a_k$，那么当前序列就不是最终序列。

3. 转化后的题意告诉我们，只能对第一个数进行操作，所以此时必须操作。

4. 由于题目保证了 $a_i$ 互不相同，所以我们总能找到这时第一个元素的最终位置，并且插入进去。

所以对于每个不符合要求的 $a_i$，最多一次操作就能令其符合要求。

因为反证的题意只允许我们操作第一个元素，所以即使当前这一位已经满足了，它后面还有没有满足的元素，那它也必须操作。

得证：只需要找出最后一个不满足题意的数，那它之前所有的数都要操作。
## 上代码（码风奇特，勿喷）
```
#include <bits/stdc++.h>	//万能头 
using namespace std;	//命名空间 
int a[100001];	//定义数组 
int main()	//主函数 
{
	int n , ans = 0;	//变量不多解释 
	cin >> n;	//输入n 
	for(int i = 1; i <= n; i++)	//输入a数组 
	{
		cin >> a[i];
	}
	for(int i = 2; i <= n; i++)	//遍历一遍找答案，注意不要遍历a[1] 
	{
		if(a[i - 1] > a[i])	//判断如果符合条件 
		{
			ans = i - 1;	//更新ans 
		}
	}
	cout << ans << endl;	//输出答案
	return 0;	//完美结束 
}
```

## 温馨提示：

题目千万条，诚信第一条，代码不规范，棕名两行泪。别抄了昂，就这题你也抄？看看思路行了昂
## The End

---

