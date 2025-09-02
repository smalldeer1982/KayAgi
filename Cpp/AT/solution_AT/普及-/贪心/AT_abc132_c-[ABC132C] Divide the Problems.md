# [ABC132C] Divide the Problems

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc132/tasks/abc132_c

高橋君は、 $ N $ 個の競技プログラミング用の問題をつくりました。 それぞれの問題には $ 1 $ から $ N $ の番号がついており、問題 $ i $ の難易度は整数 $ d_i $ で表されます(大きいほど難しいです)。

高橋君はある整数 $ K $ を決めることで、

- 難易度が $ K $ 以上ならば「 $ ARC $ 用の問題」
- 難易度が $ K $ 未満ならば「 $ ABC $ 用の問題」

という風に、これらの問題を二種類に分類しようとしています。

「$ ARC $ 用の問題」と「$ ABC $ 用の問題」が同じ数になるような整数 $ K $ の選び方は何通りあるでしょうか。

## 说明/提示

### 制約

- $ 2\ \leqq\ N\ \leqq\ 10^5 $
- $ N $ は偶数である。
- $ 1\ \leqq\ d_i\ \leqq\ 10^5 $
- 入力は全て整数である。

### Sample Explanation 1

$ K=5,6 $ としたとき、問題 $ 1,5,6 $ が「$ ARC $ 用の問題」、問題 $ 2,3,4 $ が「$ ABC $ 用の問題」となり、条件を満たします。 よって、答えは $ 2 $ 通りです。

### Sample Explanation 2

「$ ARC $ 用の問題」と「$ ABC $ 用の問題」が同じ数になるような整数 $ K $ の選び方が存在しない場合もあります。

## 样例 #1

### 输入

```
6
9 1 4 4 6 7```

### 输出

```
2```

## 样例 #2

### 输入

```
8
9 1 14 5 5 4 4 14```

### 输出

```
0```

## 样例 #3

### 输入

```
14
99592 10342 29105 78532 83018 11639 92015 77204 30914 21912 34519 80835 100000 1```

### 输出

```
42685```

# 题解

## 作者：chu_K (赞：4)

题目要让我们求出 $k$ 的取值个数，实际上等于求 $k$ 上下限制的范围。

知道了范围，我们就可以知道 $k$ 的取值个数，同样，知道了 $k$ 的取值个数，我们也可以知道 $k$ 的范围。

所以问题等价于求 $k$ 能取到的一个范围。

那么如何求这样一个范围？我们来仔细分析一下题目！

- 在 ARC 中， $k$ 一定是小于等于其中的最低分数的
- 在 ABC 中， $k$ 则一定是大于等于其中的最高分数的

啊！这里有最大和最小的问题！

有人说，涉及了最大值最小值的问题， $99\%$ 都是二分，所以我们来考虑一下能不能进行二分呢？

二分依赖的一个重要性质就是单调性。~~看我的主页，没有人比我更懂单调~~，单调是什么意思？单调就是一个东西，只是朝单一的方向变化，比如一直增加，一直减少。

那么这里有没有单调性？

有的！看，$k$ 增加，ARC 的题目是不是少，$k$ 减少，ARC 的题目是不是多？单调啊！单调！单调啊！单调！

所以我们就考虑进行二分，但是这里的条件有些不一样啊！不是一下子就能判断是否可以的。

我们仔细阅读题目，发现题目让我们求的是 ARC 和 ABC 题目数相同。这个便是条件了。

但这又有些不同，因为求最大最小值比较难控制，感觉比较像 [SHOI2015 自动刷题机](https://www.luogu.com.cn/problem/P4343), 那里也是要控制范围。

其实就是把普通的二分改一下，多增加一种判断，在条件完全符合的时候如果求解右端点就把左端点往右，求左端点就把右端点往左。

核心代码(二分左边界，右边同理):

```cpp
while(l<=r){
	int mid=(l+r)/2;
	if(check(mid)>k) l=mid+1;
	else if(check(mid)<k) r=mid-1;
	else ans=mid,r=mid-1;
}
```

现在来总结一下这道题。

这题考查了我们对于二分是否真正理解，如果不理解，肯定是想不到这样修改的，只有真正理解了，才能想到这样魔改一个二分，这真是一道练习二分的好题目啊！都有一点省选题的风范了。

但是，二分需要我们很好的理解，那我们没有很好的理解怎么办？

那就不二分了，换种正常的做法:

```cpp
 std::sort(a, a + n);
 printf("%d\n", a[n/2] - a[n/2-1]);
```

这样好想也好写。

---

## 作者：·糯· (赞：1)

## 题目分析
此题我们先将整个数列进行排序，然后计算中间两数之差，这就是答案。原因是中间偏右的数及在它以下且比中间偏左的数大的数必定能将这个序列等分成两部分。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);//排序
	cout<<a[n/2+1]-a[n/2]<<endl;//可行的数量
	return 0;
}
```


---

## 作者：WHJ___ (赞：1)

对于这道题目，我们考虑使用 **前缀和** 解决。

由于 $di<=100000$，所以我们可以直接枚举 $k$ 的范围。
因此我们使用前缀和，将每个难度的题目总和保存在 $a[i]$ 数组里，并在输入过程中得到题目难度的最大值 $maxn$，然后对于每个 $i\in[1,maxn]$ 将难度 $\le i$ 的题目总数存在 $sum[i]$ 中，然后从 $1$ 到 $maxn$ 枚举 $k$，显然判断条件是难度 $\in [1,k) $ 与难度 $\in [k,maxn]$ 的题目总量是相等的，也就是说难度 $\in [1,k) $ 的题目占题目总量的$\frac{1}{2}$,即$2*sum[k]=n$。

代码：

```cpp
#include<bits/stdc++.h>
#define I long long
#define RI register int
#define il inline
#define rt return
using namespace std;
const int N=1e5+7;

I n,a[N],sum[N],ans,maxn=-1,di;

il I d(){
	I x=0,f=1;
	char c=0;
	while(!isdigit(c=getchar()))f-=(c=='-')*2;
	while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
	rt x;
}

signed main()
{
	RI i,j;
	n=d();
	for(i=1;i<=n;++i){
		di=d();
		maxn=di>maxn?di:maxn;//判断maxn
		++a[di];
	}
	for(i=1;i<=maxn;++i)sum[i]=sum[i-1]+a[i];//前缀和 
	for(i=1;i<=maxn;++i)if(2*sum[i-1]==sum[maxn])++ans;//判断答案
	cout<<ans<<endl;
	rt 0;
}
```


---

## 作者：崔化博 (赞：0)

## 思路
题目中说道要使低于 $k$ 和 高于或等于 $k$ 相等，问这样的 $k$ 最多有几个。

**所以可以知道，$k$ 必须是这些数中中间大小的两个数的差之间，而答案也就是中间两数的差。**
## 代码
```cpp
#include <iostream>
#include <string>
#include <cmath> 
#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(){
	int n,a[100005];
	cin>>n;
	for(int i=1;i<=n;++i)	
		cin>>a[i];
	sort(a+1,a+n+1);
	cout<<a[n/2+1]-a[n/2];
	return 0;
}

---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)

> 高桥在竞争性编程中提出了 $N$ 个问题，问题编号为 $1$ 至 $N$，问题 $i$ 的难度表示为整数 $d_i$（越高难度越大）。

> 他通过选择整数 $K$ 将问题分为两类，如下所示：

> - 对于 _ARC_，难度为 K 或更高的问题。
> - 难度低于 K 的问题将是 _ABC_。

> 整数 $K$ 有多少种选择可以使 $ARC$ 的问题数和 $ABC$ 的问题数相同？

$k$ 的范围可以是整个数组中最接近平均数的两个数的差，比平均数小的都是 _ABC_，其他都是 _ARC_。

我们把 $d$ 数组排序，然后求中间两个数之间的差即可。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n;
int a[100005];
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);

  sort(a, a + n);

  printf("%d\n", a[n / 2] - a[n / 2 - 1]);

  return 0;
}
```

---

