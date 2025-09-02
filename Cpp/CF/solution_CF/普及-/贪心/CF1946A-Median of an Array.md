# Median of an Array

## 题目描述

You are given an array $ a $ of $ n $ integers.

The median of an array $ q_1, q_2, \ldots, q_k $ is the number $ p_{\lceil \frac{k}{2} \rceil} $ , where $ p $ is the array $ q $ sorted in non-decreasing order. For example, the median of the array $ [9, 5, 1, 2, 6] $ is $ 5 $ , as in the sorted array $ [1, 2, 5, 6, 9] $ , the number at index $ \lceil \frac{5}{2} \rceil = 3 $ is $ 5 $ , and the median of the array $ [9, 2, 8, 3] $ is $ 3 $ , as in the sorted array $ [2, 3, 8, 9] $ , the number at index $ \lceil \frac{4}{2} \rceil = 2 $ is $ 3 $ .

You are allowed to choose an integer $ i $ ( $ 1 \le i \le n $ ) and increase $ a_i $ by $ 1 $ in one operation.

Your task is to find the minimum number of operations required to increase the median of the array.

Note that the array $ a $ may not necessarily contain distinct numbers.

## 说明/提示

In the first test case, you can apply one operation to the first number and obtain the array $ [3, 2, 8] $ , the median of this array is $ 3 $ , as it is the number at index $ \lceil \frac{3}{2} \rceil = 2 $ in the non-decreasing sorted array $ [2, 3, 8] $ . The median of the original array $ [2, 2, 8] $ is $ 2 $ , as it is the number at index $ \lceil \frac{3}{2} \rceil = 2 $ in the non-decreasing sorted array $ [2, 2, 8] $ . Thus, the median increased ( $ 3 > 2 $ ) in just one operation.

In the fourth test case, you can apply one operation to each of the numbers at indices $ 1, 2, 3 $ and obtain the array $ [6, 6, 6, 4, 5] $ , the median of this array is $ 6 $ , as it is the number at index $ \lceil \frac{5}{2} \rceil = 3 $ in the non-decreasing sorted array $ [4, 5, 6, 6, 6] $ . The median of the original array $ [5, 5, 5, 4, 5] $ is $ 5 $ , as it is the number at index $ \lceil \frac{5}{2} \rceil = 2 $ in the non-decreasing sorted array $ [4, 5, 5, 5, 5] $ . Thus, the median increased ( $ 6 > 5 $ ) in three operations. It can be shown that this is the minimum possible number of operations.

In the fifth test case, you can apply one operation to each of the numbers at indices $ 1, 3 $ and obtain the array $ [3, 1, 3, 3, 1, 4] $ , the median of this array is $ 3 $ , as it is the number at index $ \lceil \frac{6}{2} \rceil = 3 $ in the non-decreasing sorted array $ [1, 1, 3, 3, 3, 4] $ . The median of the original array $ [2, 1, 2, 3, 1, 4] $ is $ 2 $ , as it is the number at index $ \lceil \frac{6}{2} \rceil = 3 $ in the non-decreasing sorted array $ [1, 1, 2, 2, 3, 4] $ . Thus, the median increased ( $ 3 > 2 $ ) in two operations. It can be shown that this is the minimum possible number of operations.

## 样例 #1

### 输入

```
8
3
2 2 8
4
7 3 3 1
1
1000000000
5
5 5 5 4 5
6
2 1 2 3 1 4
2
1 2
2
1 1
4
5 5 5 5```

### 输出

```
1
2
1
3
2
1
2
3```

# 题解

## 作者：baokun (赞：6)

## part 1 中位数
~~学过初中数学的都知道~~，[中位数](https://shinehouse.net/article/4538)就是在排过序后，若是总数为奇数，则中位数就是中间那个数。若总数为偶数，则中位数为中间两个数的平均值。

但是和其不同的是，本题在**从小到大**排序过后，若是总数为偶，则中位数为中间两个值中靠左的那个数。
## part 2 思路
[原题链接](https://www.luogu.com.cn/problem/CF1946A)

很明显（~~根据题目标签~~），我们要用贪心 AC 这道题，那么为了要使得中位数变大，那么我们就要直接修改中位数（+1），这样才能使 $ans$ 最小。

那么我们就出现了一个问题：如果中位数在改完后还是不变呢。

因此我们就要把中位数后面所有和中位数相等的值 +1，这样才能解决这个问题。

如果中位数变小呢。

很显然不可能，因为我们并没有去除任何一个值，且中位数前面的值没有修改，因此新的中位数不可能变小。
## part 3 code
[AC](https://www.luogu.com.cn/record/163136551)。

```cpp
#include<bits/stdc++.h> 
#define int long long
#define man main
using namespace std;
int t,n,a[114514];
signed man(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		int ans=0;
		memset(a,0,sizeof(a));
		cin>>n;
		int mid=(n>>1)+n%2;
		int now=mid;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		while(a[now]){
			if(a[mid]==a[now])ans++;
			else if(a[mid]<a[now])break;
			now++;
		}cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：lpx666666 (赞：2)

## 题面
题目有多组数据，每组数据给定一个长度 $n$ 的数组 $a$，每次能给一个数加一，求给中位数加一至少要加几次。
## 思路
首先我们先了解一下中位数，中位数其实就是数组中间大小的数，奇数就是最中间，偶数是中间两个数中靠左的。

我们从小到大排序不难发现，如果中位数右侧的数和中位数相同，那么如果中位数加一，就会大于右侧的数此时中位数的大小就不再是中位数了，要想它还是中位数，只能将其右侧也加一，但右侧数可能可能出现和中位数相同的情况，那我们就只能继续向右判断，统计所有需要加一的数，直到那个数加一小于等于他右侧的数或枚举完毕。

## 代码
同思路。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int t,arr[100005];
int main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
		}
		sort(arr+1,arr+1+n);//排序 
		int cnt=0;
		if(n%2==0){//数量为偶数 
			for(int i=n/2+1;i<=n;i++){
				if(arr[i]!=arr[n/2]){//判断是否与中位数相等 
					break;//结束 
				}
				cnt++;//继续统计 
			}
		}
		else{//数量为奇数 
			for(int i=n/2+2;i<=n;i++){
				if(arr[i]!=arr[n/2+1]){//同上，只是中位数计算位置不同 
					break;
				}
				cnt++;
			}
		}
		cout<<cnt+1<<endl;//加上中位数自己 
	}
	return 0;//完结撒花 
}

```

---

## 作者：Ending_Now23 (赞：1)

题意：有一个整型数组，每次操作可以选择数组里任意一个数，这个数的值增加一。

需要输出最少的操作次数，使操作后数组的中位数大于操作前数组的中位数。
# 前置芝士：中位数
中位数表示在一组数据中，居于中间的数。

奇数就在最中间，偶数在中间偏左的位置。

也就是说，例如在这组数据中，
```
 5 4 6 3 2
```
数据数量为**奇数**。

排序后为：

```
 2 3 4 5 6
```

所以中位数就是 $4$。

如果数量为**偶数**。

```
 5 4 6 2 3 1
```

```
 1 2 3 4 5 6//排序后
```

中位数就是 $3$。
# 思路
我们不难发现，当数组从小到大排序时。

中位数右侧数可能与中位数相等，所以当中位数增加，就会移到右侧。

那么我们只需要从中位数开始，右枚举与中位数相同的数，把它们加上一就可以了。
```cpp
void check(int Now,int mid){
	int ans=0;
	while(a[Now]){
		if(a[Now]==a[mid]) ans++;
		else if(a[mid]<a[Now]) break;
		Now++;
	}
	cout<<ans<<"\n";
}
```
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n;
int a[100005];

inline int read(){// 细节快读 
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){// 如果不是数字 
		if(ch=='-')f=-1;// 判断符号 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){// 如果是数字 
		x=x*10+ch-48;// x * 10 将个位空出 ch - 48 将 char 变为 int 类型 
		ch=getchar();
	}
	return x*f;// 返回数值 
}

void check(int Now,int mid){
	int ans=0;
	while(a[Now]){
		if(a[Now]==a[mid]) ans++;
		else if(a[mid]<a[Now]) break;
		Now++;
	}
	cout<<ans<<"\n";
}

int main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		memset(a,0,sizeof(a));// 有多组数据，注意清空数组 
		n=read();
		int mid=ceil(double(n)/2);
		//如果 n 是偶数， mid 表示中间偏左的数；
		//如果 n 是奇数， mid 表示中间的数； 
		int Now=mid;
		for(int j=1;j<=n;j++){
			a[j]=read();
		}
		sort(a+1,a+n+1);
		check(Now,mid);
	}
	return 0;
}
```

---

## 作者：kind_aunt (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1946A)
## Part 0（前置芝士）：
**中位数**，是有序的一组数据中居于中间位置的数。
~~相信大多数读者都是来看中位数是什么东东~~。

------------
## Part 1：
既然题目让我们修改数值后的序列的中位数，比原序列的中位数**大**，那么我们改变中位数的大小不就好了。


先浅浅排个序：
```
bool cmp(int a,int b){
	return a>b;
	......
sort(a+1,a+n+1,cmp);//这里从小往大还是从大往小排序都一样
```  

如果我们想令现中位数的数值比原中位数值大，原中位数下标及他以后与他相等的数全部改变：
```

int ans=0;
for(int i=zhong;i<=n;i++)
	if(a[i]==a[zhong])
		ans++;//这里zhong是原中位数的下标
```

---

## 作者：Bc2_ChickenDreamer (赞：1)

## CF1946A

### Sol

我们可以进行分讨：

1. 中位数等于最后一个数。显然，必须把中位数到最后一个数全相加才能使操作后数组的中位数大于操作前数组的中位数。

2. 中位数不等于最后一个数。我们发现，只要有一个与中位数相等的数且在比当前中位数下标大的没有 $+1$，那么中位数还是当前数。所以，我们必须把当前中位数相等的数且在比当前中位数下标大的 $+1$。

分讨完毕，但我们发现情况一是与情况二相等的，因为中位数到最后一个数也满足“与当前中位数相等的数且在比当前中位数下标大的”条件。但我了保险还是加了。

注意，中位数的**下标**在 C++ 里要写为 `n / 2 + n % 2`。还有，记得**排序**。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
 
using namespace std;
 
using ll = long long;
 
const int kMaxN = 2e5 + 20, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18; 
 
ll n, a[kMaxN];
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1); // 排序
    ll pos = n / 2 + n % 2; // 求出中位数位置
    if (a[pos] == a[n]) { // 情况一
      cout << n - pos + 1 << '\n';
    } else {
      ll ans = 0; // 计数器
      for (int i = pos; a[i] == a[pos]; ++ ans, ++ i); // 寻找与当前中位数相等的数且在比当前中位数下标大的数
      cout << ans << '\n';
    }
  }
  return 0;
}
```

---

## 作者：AK_400 (赞：1)

# [CF1946A](https://codeforces.com/problemset/problem/1946/A) 题解
我们首先想到将数组排序后 $a_{\lceil n/2\rceil}\gets a_{\lceil n/2\rceil}+1$，但是样例中答案不都是一！

我们手模一组样例：
|  | $a_1$ | $a_2$ | $a_3$ | $a_4$ | $a_5$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 初始 | $5$ | $5$ | $5$ | $4$ | $5$ | 
| 排序后 | $4$ | $5$ | $5$ | $5$ |$5$  |
| 操作后 | $4$ | $5$ | $6$ | $5$ |$5$  |

我们发现此时中位数并不是 $6$，因为后面还有相同的数，修改一个时会被挤到相同的数后。所以我们要对所有的与原中位数相等的，排序后不在原中位数前的数操作。 
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005];
int main(){
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+1+n);
        int cnt=0;
        int mid=(n+1)/2;
        for(int i=mid;i<=n;i++){
            cnt+=a[i]==a[mid];
        }
        cout<<cnt<<endl;
    }
    return 0;
}
```

---

## 作者：OJ_killer (赞：0)

简单贪心题，题意非常简单就不说了。
## 解法
先把数组排好序，设 $k$ 是满足 $a_k = a⌈\frac{n}{2}⌉$ 的最大值，子数组 $a[⌈\frac{n}{2}⌉:k]$ 的值都相等。

如果要使这个子数组中的每个数都增大才能使中间值增大。

最后得出结论：要操作 $k−⌈\frac{n}{2}⌉+1$ 次。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int T;

int main() {
	cin >> T;
	while (T--) {
		int n, a[100100], ans = 1;
		cin >> n;
		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		sort(a + 1, a + n + 1);
		int m = (n + 1) / 2;
		for (int i = m + 1; i <= n; ++i) {
			if (a[i] == a[i - 1])
				++ans;
			else
				break;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：hexuchen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1946A)

[更好的阅读体验？](https://www.luogu.com.cn/article/9gk1mgmk)

## 题目大意

给出很多个长度为 $n$ 的数组 $a$，每次可以选择一个元素加一，求最少操作几次，能使数组中位数大于操作前的中位数？

## 思路分析

题目翻译有些小坑。

首先，英文体面说：

>The median of an array $ q_1, q_2, \ldots, q_k $ is the number $ p_{\lceil \frac{k}{2} \rceil} $ 

从中可以得到：

1. 数组的下表是从 $1$ 开始的。

2. 中位数不是数学中的中位数，而是数组 $a$ 的 $a_{\lceil \frac{k}{2} \rceil}$。

其次，英文体面中又说：

>where $p$ is the array $q$ sorted in non-decreasing order. 

所以取中位数时要先排序。

这些要素理清后，思路就很好想了：由于数组中可能有许多与中位数相同的元素，一旦更改完中位数，排序后中位数会浮到后面去，所以要将中位数以及后面所有与中位数相同的书全部加 $1$。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[200001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>k;
		for(int i=1;i<=k;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+k); //先从小到大排序
		int cnt=(k%2==0?k/2:k/2+1); //中位元素的下表
		int ans=1; //本来就要改原中位数，所以初始值为一
		for(int i=cnt+1;i<=k;i++){ //从中位数开始往后的元素，一旦与中位数相同，就也要加一
            if(a[i]==a[cnt])
                ans++;
        }
		cout<<ans<<endl; //记得要加换行
	}
	return 0;
}
```

---

## 作者：I_will_AKNOI (赞：0)

CF1946A 题解

第一篇题解。

题意翻译很清楚，就是有个地方有点漏洞：题中的“中位数”其实指的是数组排序后第 $\lceil\frac n2\rceil$ 个数，其中 $n$ 指的是数组中数的个数，和数学中的中位数概念不同。以下提到的中位数都指的是数组排序后第 $\lceil\frac n2\rceil$ 个数。

然后容易想到只需要找出数组中位数将其加上 $1$ 即可。例如：`a[]={1,2,3,4,5,6,7}` 变为 `a[]={1,2,3,5,5,6,7}`，中位数增加了 $1$。

但是有一种特殊情况需要考虑：`a[]={1,2,3,4,4,4,5}`，中位数加上 $1$ 后会变为 `a[]={1,2,3,5,4,4,5}`，排序后为 `a[]={1,2,3,4,4,5,5}`，中位数仍然为 $4$，没有增加。要将中位数变为 $5$，只需要将原数组的所有与中位数相同且在中位数后的数像中位数一样加上 $1$ 即可。代码中可以用 `while` 语句实现。

注意事项：先排序再算中位数，多测清空。

代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[200001];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,h=1;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+n+1);
        int k=(n+1)/2;
        while(a[k]==a[k+1])h++,k++;
        cout<<h<<endl;
        for(int i=1;i<=n;i++)a[i]=0;
    }
    return 0;
}
```

---

## 作者：xk2013 (赞：0)

题目传送门：[CF1946A Median of an Array](/problem/CF1946A)

## 前置知识
- 中位数；
- 向上取整；
- 排序。

## 题意简述
本题给我们一个数组，让我们求让中位数变高最少需要添加多少个 $1$。

## 解题思路
首先来解释一下什么是中位数。设一个数组 $S$，$S'$ 为 $S$ 排序后的数组，那么 $S$ 的中位数就是 $S'_i$，$i = \left\lceil\dfrac{|S|}{2}\right\rceil$，$|S|$ 表示 $S$ 的长度。

那在什么情况下中位数会变大呢？注意哦，中位数不是平均数，不是只改变一个数字就会变化的，而是要大小处在最中间的数变化才会变化。比如说：
```plain
6
1 1 4 5 1 4
```
这个数组的中位数是 $1$，排序后会更直观：
```plain
6
1 1 1 4 4 5
```
那如何让中位数变大呢？很明显，只要让中位数加一就可以了。那如果中位数后面有相同的数呢？
```plain
5
4 5 5 5 5
```
那我们就需要把所有和中位数相等的数加一才可以让中位数增大了，因此我们只需要统计在中位数后面与中位数相同的数有多少个就行了（包括中位数自己）。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <algorithm>
#include <cstdio>

int main(void)
{
	int T;
	scanf("%d", &T);
	
	while (T--)
	{
		int n, ans = 0, a[100001];
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}
		
		std::sort(a, a + n); // 排序
		
		for (int i = (n + 1) / 2 - 1; i < n; i++) // (n + 1) / 2 是为了向上取整
		{
			if (a[i] != a[(n + 1) / 2 - 1])
			{
				break; // 遍历完成
			}
			
			ans++; // 累加
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}

```
----------------------
这是本四升五蒟蒻小学生的第 13 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2024/07/02：初版。

---

## 作者：BDFZ_lzq (赞：0)

## 题意
题目有多组数据，每组数据给定一个长度 $n$ 的数组 $a$，每次操作能使任意一个数加一，求使中位数加一至少要操作几次。

## 分析

很显然，这是一道贪心题。

首先，我们给数组排序一下再分析。

考虑暴力，每次都给当前数组的中位数加一，直到当前数组的中位数比原始的大一。

>中位数，即 $a_{n/2+(n \bmod 2)}$，下文简称 $a_{mid}$

尝试枚举一下。

如果 $a_{mid}$ 比 $a_{mid+1}$ 小，那么输出一。

如果 $a_{mid}= a_{mid+1}$ 且 $a_{mid+1}$ 比 $a_{mid+2}$ 小，那么输出二。

……

我们就可以得出，只有在 $a_i = a_{mid}$ 且 $mid \leq i$ 时，$a_i$ 才会在接下来的操作中成为中位数。

于是我们只需要枚举 $a_{mid}$ 到 $a_n$ 之间有多少个 $a_i=a_{mid}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[114514];
int main()
{
	long long T,n,sum;
	cin>>T;
	for(int i=0;i<T;i++)
	{
		cin>>n;
		sum=0;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
		}
		sort(a+1,a+n+1);
		int mid=n/2+(n%2);
		for(int j=mid;j<=n;j++)
		{
			if(a[j]==a[mid])
			{
				sum++;
			}
			else
			{
				break;
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：BJqxszx_zhuyukun (赞：0)

# 写在前面

本人是个蒟蒻，第 $2$ 次发题解，写的不好或码风很烂请见谅。

# 中位数

相信很多人都不太清楚“中位数”到底是个啥，其实很简单。\
有一个数列 $a$，长度为 $n$，里面的数都排好了序。\
如何找到这个数列的中位数呢？\
很简单，这个数列的中位数就是 $a_{\lceil \frac{n}{2} \rceil}$。
举个栗子：
1. $n=3,a=1\ 3\ 5$，则 $a$ 的中位数为 $a_{\lceil \frac{3}{2} \rceil}=3$。
2. $n=4,a=1\ 3\ 5\ 6$，则 $a$ 的中位数为 $a_{\lceil \frac{4}{2} \rceil}=3$。

知道了中位数是啥，这题就不难了。

# 思路

注意，由于中位数必须在一个有序数组内才能求，所以对于每组输入，都要先排个序。\
排完序之后，我们就可以开始考虑了。

首先拿一个样例来分析一下，样例第 $2$ 个就很合适：$7\ 3\ 3\ 1$，排序后是 $1\ 3\ 3\ 7$。

思考一下，为什么答案会是 $2$ 呢？这是因为，将中位数 $3$ 加上 $1$ 之后，数组变成了：$1\ 3\ 4\ 7$。此时，该数列的中位数将会是 $3$，显然是没有变化的。这是为什么呢？因为第 $1$ 个 $3$“走了”之后，第 $2$ 个 $3$“顶上来了”。我们还需要重复一遍 $+1$ 操作，把顶上来的 $3$“送走”。

那么，有哪些数是需要被重复操作的呢？显然，是与中位数相同的数。考虑一下，中位数在 $+1$ 之后，只会变大。换句话说，中位数只会与右面的数交换位置。所以，只要从中位数的位置开始循环找同样的数就行了。就像这样：\
`for(int i=1+n>>1;i<=n;i++) if(a[i]==a[1+n>>1]) ans++;`

# 代码

接下来给大家放出完整代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1e5+15;
int t,n,ans;
int a[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);
		for(int i=1+n>>1;i<=n;i++) if(a[i]==a[1+n>>1]) ans++;
		cout<<ans<<'\n';
		ans=0;
	}
	return 0;
}
```

---

## 作者：qusia_MC (赞：0)

很简单。

先说一下什么是中位数，中位数就是：

对于一个单调不递减数组，即对于所有的 $1\le i\le n$，都有 $a_i\le a_{i+1}$，则中位数等于 $n\div 2+n\bmod 2$，为了方便讲述，我们设中位数的下标为 $k$。

---
要让中位数变大，那么每次操作就不能减，必须加。

我们在这个的前提下，我们还要让这个中位数在数组中的位置不变（前后排序）。不难想到，加的话，就要将满足条件 $i$ 的位置都加 $1$：

- $k\le i\le n$。

- $a_i=a_k$。

因为如果有任意的 $l$ 满足 $k\le l\le n$ 且 $a_l=a_k$ 这样的话，如果 $a_k$ 加了 $1$ 但是 $a_l$ 没加的话，那么 $a_l$ 就会成为新的中位数，就前功尽弃了。

----
经证明，我们只需要统计 $\sum^{a_i=a_k}_{i=k}1$ 就可以了。

## CODE
```
#include<bits/stdc++.h>
using namespace std;
#define kkksc03chen_zhe ios::sync_with_stdio(0);cout.tie(0);cin.tie(0);

int main()
{
	kkksc03chen_zhe//大佬助力
	int T,n,a[114514],ans,zws;
    cin>>T;
    while(T--)
    {
    	cin>>n;
    	ans=0;
    	for(int i=1;i<=n;i++)
    	{
    		cin>>a[i];
		}
		sort(a+1,a+n+1);
		zws=n/2+n%2;//中位数
	    for(int i=zws;i<=n;i++)
		{
			if(a[i]==a[zws])ans++;
			else break;//满足条件累加否则break。
		 } 
	    cout<<ans;
		cout<<"\n";
	} 
}
```

---

