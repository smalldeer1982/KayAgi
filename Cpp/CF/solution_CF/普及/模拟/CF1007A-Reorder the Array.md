# Reorder the Array

## 题目描述

You are given an array of integers. Vasya can permute (change order) its integers. He wants to do it so that as many as possible integers will become on a place where a smaller integer used to stand. Help Vasya find the maximal number of such integers.

For instance, if we are given an array $ [10, 20, 30, 40] $ , we can permute it so that it becomes $ [20, 40, 10, 30] $ . Then on the first and the second positions the integers became larger ( $ 20>10 $ , $ 40>20 $ ) and did not on the third and the fourth, so for this permutation, the number that Vasya wants to maximize equals $ 2 $ . Read the note for the first example, there is one more demonstrative test case.

Help Vasya to permute integers in such way that the number of positions in a new array, where integers are greater than in the original one, is maximal.

## 说明/提示

In the first sample, one of the best permutations is $ [1, 5, 5, 3, 10, 1, 1] $ . On the positions from second to fifth the elements became larger, so the answer for this permutation is 4.

In the second sample, there is no way to increase any element with a permutation, so the answer is 0.

## 样例 #1

### 输入

```
7
10 1 1 1 5 5 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 1 1 1 1
```

### 输出

```
0
```

# 题解

## 作者：深度产业观察 (赞：3)

这个题直接摁扫会超时……但是可以用 `upper_bound` 通过。

`upper_bound` 能返回数组中大于给定值的第一个元素的下标。

这个题主要的思想是贪心，我们可以先将数组排序，然后利用 `upper_bound` 截取数组的后半部分进行比较。

起点直接设置为 $1$ 就可以。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100010;
int n,ans,a[N];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    	cin>>a[i];
    sort(a+1,a+n+1);
    int T=upper_bound(a+1,a+n+1,a[1])-a,cnt=1;
    while(T<=n)
    {
        if(a[cnt]<a[T])
            ans++,cnt++,T++;
        else T++;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：kevin1616 (赞：2)

### 审题
给出一个有 $n$ 个元素的序列，求把它们重新排列后比原来位置大的元素个数的最大值。
***
### 方法
【贪心】每次将当前较小元素与当前最小元素比较。此方法可行。
***
### 思路
枚举最小的元素，给这个元素配对一个比它大的元素，然后这个元素要尽量小。所以可以遍历整个序列，每次判断当前较小元素是否可以配对当前最小元素。如果是，那么将答案个数加 $1$，再把这个最小元素删除（或指针右移），最后输出答案即可。

这里要找当前较小元素和当前最小元素。所以可以把数组先排序来优化这个操作。时间复杂度 $O(n \log n)$，主要来自于排序。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];
int sum = 1,ans;
int main(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    sort(a + 1,a + n + 1); //给序列排序
    for(int i = 2;i <= n;i++){ //枚举当前较小元素
        if(a[i] > a[sum]){ //判断当前较小元素是否可以配对当前最小元素
            sum++; //删除当前最小元素
            ans++; //将答案个数增加1
        }
    }
    cout << ans << endl; //输出答案
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：chenpengda (赞：2)

### 知识点：贪心。

### 题意：

`有n个数，把它们重新排列，每一个位置相对，求排列之后的数比排列之前的数大的位置个数的最大值。`

### 基本思路：

先进行一轮排序。

然后对于每个位置，向后查找一个比这个大的数，那么就将这两个数搭配。

```cpp
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)//从后面算起
		{
			if(yuan[j]>yuan[i]&&used[j]==0)//used[j]用过了没，是不是大
			{
				used[j]=1;
				sum++;//累加
				break;
			}
		} 
	}
```

（这是第一版代码，完美展现了贪心思想，唯一的问题是超时）

那么怎么改进呢？实际上，你会发现$a[i+1]$必然大于等于$a[i]$；而如果$a[j]$不能和$a[i]$匹配，那么显然更不能和$a[i+1]$匹配。

比如说：现在有数组$a[6]=\{1,1,1,1,1,2\}$，你已经发现第四位的$1$已经不能和第二位搭配，那么第三位的$1$就更不可能和第四位搭配了。

所以，不需要从头开始匹配$a[j]$，直接继续即可。

秉持刚才的思路，下面是改进：

```cpp
	int j=0;
	for(int i=0;i<n-1&&j<n;i++)
	{
		j++;//将j向后累加，原因在上面
		if(yuan[j]>yuan[i])//代表可以匹配
		{
			sum++;
		}
		else i--;//相当于还是这个i，但是是下一个j。
	}
```

其他部分大概没有问题，以下是全部代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int yuan[100005],sum;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>yuan[i];
	}
	sort(yuan,yuan+n);//从小到大排序，贪心的基本操作 
	int j=0;
	for(int i=0;i<n-1&&j<n;i++)
	{
		j++;
		if(yuan[j]>yuan[i])
		{
			sum++;
		}
		else i--;
	}//循环内内容已经解释。 
	cout<<sum;
	return 0;
}
```


---

## 作者：nightwatch.ryan (赞：1)

### 题意
给出一个有 $n$ 个元素的序列，求把它们重新排列后排列后的元素比原来位置元素大的元素个数的最大值。
### 分析和思路
一道贪心题。先将数组排序，我们能想到一个很简单但是会时间超限的思路：对于每一个数，都找出最小的没有用过的比这个数大的数。由于会时间超限，所以我们要进行一些优化。因为数组已经排过序，则一个数如果没法和 $a_i$ 匹配上，当然也无法和 $a_{i+1}$ 及 $a_{i+1}$ 后面的数字匹配上，所以我们可以直接跳过。
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
const int MAXN=1e5+5;
int n,a[MAXN],res;
int main(){
		scanf("%d",&n);
		for(register int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		std::sort(a,a+n);
		for(register int i=0,j=0;i<n;i++){
			j++;
			if(j>n){
				break;
			}
			if(a[i]<a[j]){
				res++;
			}else{
				i--;
			}
		}
		printf("%d",res);
}
```


---

## 作者：WaterSky (赞：1)

[题目传送门](https://www.luogu.com.cn/blogAdmin/article/new#CF1007A)。

点开题解时，发现一位大佬的两种方法中也有我的方法，但是有点不详细，所以我来完善它！

首先，要阅读题目：

给出一个有 $n$ 个元素的序列，求把它们重新排列后 排列后的元素比原来位置元素大的元素个数的最大值。

第一个想到的方法就是枚举！对于每一个数，都找出最小的没有用过的比这个数大的数。代码是:
```
for(int i=1;i<=n;i++)
{
	long long maxx=1e12,mx=-1;
	for(int j=1;j<=n;j++)
	{
		if(a[j]>a[i] && b[j]==0)
			if(maxx>a[j]) maxx=a[j],mx=j;
	}
	if(mx!=-1) b[mx]=1,ans++;
}
```
这个程序不可以过，所以要想出有优化的方法。

可以将找最小的没有用过的比这个数大的数的步骤用一个排序来优化，就可以减少部分的时间。

经过查找 CF 的提交记录发现，这个程序也不可以过，所以要想出有优化的方法。

通过观察或推测得知如果每个数都满足以上的条件，那么这个排序后的数列单调递增，也可以得知，如果 $a_j>a_i$ 不成立，那么往后的数也不可以使用 $a_j$，所以一个循环就可以搞定。
```
for(int i=1,j=1;i<=n,j<=n;j++)
		if(a[j]>a[i]) ans++,i++;
```

第一个程序：
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],b[100005],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
{
	long long maxx=1e12,mx=-1;
	for(int j=1;j<=n;j++)
	{
		if(a[j]>a[i] && b[j]==0)
			if(maxx>a[j]) maxx=a[j],mx=j;//找出最小的没有用过的比这个数大的数并标记。
	}
	if(mx!=-1)
	b[mx]=1,ans++;
}
	cout<<ans;
    return 0;
}

```
第二个程序：
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],b[100005],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(a[j]>a[i] && b[j]==0)//同样是找出最小的没有用过的比这个数大的数并标记。
			{
				b[j]=1;
				ans++;
				break;//但是由于排过序，所以第一个找到的数一定是最小的，直接退出。
			} 
		}
	}
	cout<<ans;
    return 0;
}
```
第三个程序：
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],b[100005],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1,j=1;i<=n,j<=n;j++)
		if(a[j]>a[i]) ans++,i++;
	cout<<ans;
    return 0;
}
```

---

## 作者：int_stl (赞：0)

这道题太水了，实现原理很简单：

- 输入 $n$ 个数，并且用 $count$ 记录每一个数的出现次数。
- 用数组长度减去出现次数最多的元素的次数，即是答案。

## AC代码：
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    unordered_map<int, int> cnt;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        cnt[arr[i]]++;//记录元素出现次数
    }

    int maxcnt = 0;

    for (const auto& pair : cnt) {
        maxcnt = max(maxcnt, pair.second);//寻找出现次数最多的元素的次数
    }

    int maxans = n - maxcnt;

    cout << maxans << endl;

    return 0;
    //求过！
}

```
![](https://cdn.luogu.com.cn/upload/image_hosting/o0x5cq14.png)

---

## 作者：PikachuQAQ (赞：0)

## Description

给出一个有 $n$ 个元素的序列，求把它们重新排列后排列后的元素比原来位置元素大 的元素个数的最大值。

## Solution

很好的贪心思维题。

这题可以先从大到小排序，再选择匹配两个数，分别是最大数和次大数，我们用 $k$ 表示和最大数匹配的次大数下标，此时分为了两种情况：

如果最大数大于次大数，说明这个排列比原来要大，答案加一，让下一个次大数和最大数匹配排列。

否则，也就是当前最大数小于等于次大数，直接让当前最大数和下一个次大数匹配，直到当前最大数大于次大数为止，回到上面的情况。

## Code

```cpp
// 2023/4/28 Accept__

#include <iostream>
#include <algorithm>

using namespace std;

const int kMaxN = 1e5 + 7;

int n, a[kMaxN], b[kMaxN], ans;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n, greater<int>());
    for (int i = 1, k = 0; i < n; i++) {
        (a[k] > a[i]) && (ans++, k++);
    }
    cout << ans;

    return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17033376.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1007A)

## 题目分析

贪心水题。

首先将原数组从小往大排序，然后不难想到一个简单但会超时的思路，即对每个位置，向后找到一个比自己大的数进行搭配。

然后是一个简单的小优化，由于数组已经排序，那么如果一个数无法与 $a_i$ 匹配，那么也不可能与 $a_{i+1}$ 及以后的数匹配，因此可以直接跳过。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define ok puts("Yes")
#define no puts(":(")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=100010;
int n;
int cnt,ans;
int a[maxn];
inline void init(){
	n=read();cnt=1;
	for(register int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1);
}
int main(){
	init();
	for(register int i=1;i<=n;++i){
		cnt++;
		if(cnt>n) break;
		if(a[i]>=a[cnt]) i--;
		else ans++;
	}
	printf("%d",ans);
}
```

---

## 作者：Aya_tt (赞：0)

这题是一道贪心题目，贪心就是要将问题的解推向最优，虽然贪心有时有弊端，不一定能求出~~最优解~~，但是面对这道题还是绰绰有余的。

题目大意：将 $n$ 个数重新排列，求排序之后比原来位置数大位置个数的最大值。

我的思路是可以先排序一下，然后从一个位置查他后面的几个比他大的数字位置，把原来的数和现在正在查询的数匹配一下，这就是排序的意义了，因为排序之后，序列可以保证他是从小到大的。

具体不好说，先上核心代码：
```c
for (int i = 1;i < n;++ i){
    cnt++;
    if(cnt > n) break;
    if (a[i] < a[cnt]) ans++;
    else i--;
}
```
$cnt$ 就是每次都在向后找，$i$ 是在便利整个循环，如果现在的数比之前的那个数大，那么这就是正确的位置，统计的 $ans$ 便加一。如果没有 $i$ 就要 $-1$，重新查询。 

总代码：
```c
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans,cnt = 1;
int main (){
    cin >> n;
    for (int i = 1;i <= n;i++){
		cin >> a[i];
	}
    sort(a + 1,a + n + 1);
    for (int i = 1;i < n;++ i){
        cnt++;
        if(cnt > n) break;
        if (a[i] < a[cnt]) ans++;
        else i--;
    }
    cout<<ans;
    return 0;
} 
```
长度不长，实现比较容易。

---

## 作者：BlanketRice (赞：0)

这道题就是一道贪心，每个数需要找一个数与自己搭配，如果找到的数比自己大，答案就自加。

我们可以假设，每个数要优先找比自己大的数，如果有多个数，要找最小的那个。那我们就可以先排序，再从数本身开始找。因为是排完序的，所以直接从数本身开始找即可。找到的第一个可行的数就 break 。为了防止有相等的数，我们加一个判断。为了防止重复（一个数只能用一次）我们用 vis 去重。

代码如下：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[100005];
bool vis[100005];
int sum;
signed main (){
    cin >> n;
    for (register int i = 1;i <= n;++ i) cin >> a[i];
    sort (a + 1,a + n + 1);
    for (register int i = 1;i <= n;++i){
    for (register int j = i + 1;j <= n;++ j){
        if (vis[j] == 0 && a[j] > a[i]){
            vis[j] = 1;
            ++ sum;
            break;
        }
    }
    cout << sum << endl;
    return 0;
} 
```

非常水，但是会 TLE 。那怎么办，我们可以优化。我们不需要找 i ，和能与之匹配的 j ，我们可以找一个数 j 找能与之匹配的 i 。

就是遍历 j ，找 i 如果能匹配就匹配，否则就 i 自减。

代码如下：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[100005];
bool vis[100005];
int sum;
signed main (){
    cin >> n;
    for (register int i = 1;i <= n;++ i) cin >> a[i];
    sort (a + 1,a + n + 1);
    int j = 1;
    for (register int i = 1;i < n && j <= n;++ i){
        ++ j;
        if (a[i] < a[j]) ++ sum;
        else -- i;
    }
    cout << sum << endl;
    return 0;
} 
```

---

## 作者：Scorilon (赞：0)

To [CF](https://codeforces.com/problemset/problem/1007/A)

这道题是排序贪心，将原序列排序后统计答案即可。

但是直接统计会超时，因为排序后具有**单调性**，所以可以进行一点优化，这样，便可以通过此题。

而这道题的优化在于单调性，因为 $a[i+1]$ 必然大于 $a[i]$，所以当 $a[j]$ 无法与 $a[i]$ 匹配时，也就可以排除掉 $a[i+1]$，原因是因为具有单调性。

因此，不需要重新开始匹配，直接向下匹配即可。

这样，也就可以通过本题，避免超时。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n;//共n个数
int s[100005];
int ans;//统计答案
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&s[i]);
	}
	sort(s,s+n);//排序
	int j=0;
	for(int i=0;i<n-1&&j<n;i++){//统计答案，优化：可以继续从s[j]进行统计
		j++;
		if(s[j]>s[i]) ans++;
		else i--;
	}
	printf("%d",ans);//输出答案
	return 0;
} 
```


---

## 作者：_Flame_ (赞：0)

## 思路

贪心思路很明显，先进行排序，对于排序后每个数，向后找第一个与其匹配的数匹配即可。

然后是一个优化思路，由于排序后数组 $a$ 单调递增，所以当一个数 $a_{tot}$ 不能与 $a_i$ 匹配时，它肯定也不能与 $a_{i+1}$ 匹配，跳过即可。

最后一个数肯定没有比它大的，跳过即可。

注意在 $tot$ 往后跳时，不能超过数组长度。

## Code

```cpp

#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int maxn=1000010;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;	
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

int n;
int a[maxn];
int ans=0;
int tot=0;

signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+1+n); 
	for(int i=1;i<n;i++){
		tot++;
		if(tot>n) break;
		if(a[i]<a[tot]) ans++;
		else i--;
	}
	write(ans);
	puts("");
	return 0;
}
```

---

