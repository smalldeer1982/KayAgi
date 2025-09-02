# Contests

## 题目描述

[problemUrl]: https://atcoder.jp/contests/aising2019/tasks/aising2019_b

あなたはプログラミングコンテストを開催するため問題を $ N $ 問作成しました。 このうち $ i $ 問目をコンテストに出題する場合、配点は $ P_i $ 点となります。

これらの問題を使って、以下の条件を満たすコンテストをできるだけ多く開催したいと思います。 異なるコンテストの間で問題の重複があってはいけません。 最大で何回のコンテストを開催できますか。

- 問題が $ 3 $ 問出題され、$ 1 $ 問目の配点は $ A $ 点以下、$ 2 $ 問目の配点は $ A\ +\ 1 $ 点以上 $ B $ 点以下、$ 3 $ 問目の配点は $ B\ +\ 1 $ 点以上である。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ P_i\ \leq\ 20 $ ($ 1\ \leq\ i\ \leq\ N $)
- $ 1\ \leq\ A\ <\ B\ <\ 20 $
- 入力値はすべて整数である。

### Sample Explanation 1

$ 1,\ 2,\ 3 $ 問目の問題、$ 4,\ 5,\ 6 $ 問目の問題をそれぞれ組み合わせることで $ 2 $ 回のコンテストを開催できます。

### Sample Explanation 2

$ A\ =\ 3 $ 点以下の問題が存在しないので、コンテストを開催できません。

## 样例 #1

### 输入

```
7
5 15
1 10 16 2 7 20 12```

### 输出

```
2```

## 样例 #2

### 输入

```
8
3 8
5 5 5 10 10 10 15 20```

### 输出

```
0```

## 样例 #3

### 输入

```
3
5 6
5 6 10```

### 输出

```
1```

# 题解

## 作者：alm_crax (赞：1)

## 分析
### 1. 题目大意：

有 $N$ 个问题，现有各个问题的分值和每道比赛题目分值的限制 $A$ 和 $B$，满足条件的情况下，能举行多少场比赛。

### 2. 比赛条件：
- 第一题的分值不超过 $A$。

- 第二题的分值大于 $A$ 且不超过 $B$。

- 第三题的分值大于 $B$。
## 思路
将所有问题分为三组，分别为满足第一题，第二题，第三题的条件。比赛数取决于数量最少的一组。
## 代码
代码不多说，简单易懂。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,p[105],s1,s2,s3;
int main()
{
	ios::sync_with_stdio(0);
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		if(p[i]<=a)
		{
			s1++;
		}
		else if(p[i]<=b)
		{
			s2++;
		}
		else
		{
			s3++;
		}
	}
	printf("%d",min(s1,min(s2,s3)));
    return 0;
}
```


---

## 作者：Daniel_7216 (赞：1)

额，正解就是看一下每一道题应该分类成一场比赛的第几题，然后三种题中最小的储备量就是可以举办的比赛场数。

没啥好说的：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int n, p, a, b, c, A, B;
int main(){
	scanf("%d", &n);
	scanf("%d%d", &A, &B);
	for (int i = 0; i < n; i++){
		scanf("%d", &p);
		if (p <= A){
			a++;
		}
		if (p >= A + 1 && p <= B){
			b++;
		}
		if (p >= B + 1){
			c++;
		}
	}
	printf("%d", min(min(a, b), c));
	return 0;
}
```

~~简直是最水一眼题~~

---

## 作者：封禁用户 (赞：1)

这道题，乍看啥也看不懂，但是我们换一个角度，就会变得很容易。

题目要我们输出组成比赛的个数，依据题目描述，一场比赛需要一个题目分数 $\le A$、一个题目分数 $> A$ 且 $\le B$、一个题目分数 $> B$。

所以，我们可以将数组 $p$ 排序，然后分别算出三种分数区间的题目各有多少个，再输出最小的一个区间题目数量，输出就可以了。

听不懂？无码无真相嘛。。

$\mathsf{My}$ $\mathsf{Code}$

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, p[110], a, b, cnt1 = 0, cnt2 = 0, cnt3 = 0, ans = 998244353;
int main(){
    // 输入
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i ++) cin >> p[i];
    
	sort(p + 1, p + n + 1); // 排序
    
	for (int i = 1; i <= n; i ++){ // 计数
		if (p[i] <= a) cnt1 ++; // 小于等于 a 的区间
		else if (p[i] > a && p[i] <= b) cnt2 ++; // 大于 a 且 小于等于 b 的区间
		else cnt3 ++; // 大于 b 的区间
	}
    
    // 无脑输出最小区间值↓↓
	if (cnt1 < ans) ans = cnt1;
	if (cnt2 < ans) ans = cnt2;
	if (cnt3 < ans) ans = cnt3;
	cout << ans << endl; // 输出
    return 0;
}
```

就是这样，谢谢大家！

---

## 作者：kaceqwq (赞：1)

# 题目大意：
有 $N$ 个题目，每一道题目有一下三种情况：

$1.$ 该问题的分数不超过 $A$ 分

$2.$ 问题的分值在 $A+1$ 分和 $B$ 分之间 $（$ 包括 $B$ 分 $）$ 

$3.$ 问题的分值不小于 $B+1$ 分。

求出题人用这些题最多能举行几场比赛。

# 分析:
首先，根据题意先输入，接着我们可以把满足每一种情况的数量存在三个计数器中，最后输出三个计数器中最小的一个即可。


# Code:
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int t[1000005];
signed main()
{
	ios::sync_with_stdio(0);   //加速器
	int n,a,b,suma=0,sumb=0,sumc=0;  //三个计数器,分别存储三种情况的题数
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
	{
	cin>>t[i];
	if(t[i]<=a)  //满足各种情况就在其计数器累加
	suma++;
	if(a+1<=t[i]&&t[i]<=b)
	sumb++;
	if(t[i]>=b+1)
	sumc++;
	}
	cout<<min(min(suma,sumb),sumc)<<'\n';  //最后输出最小值
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# 题目大意

有 $ N $ 个问题，第 $ i $ 题的分数值为 $ P_i $ 

举行比赛的要求：

1. 第一题分数 $ \leq A $ 分

2. $ A \leq $ 第二题分数 $ \leq B $ 分

3. 第三题分数 $ \geq B $ 分

求最多能举行几场比赛

# 分析

每次统计题目的个数，取最小值就可以了

# 代码
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN = 1e5 + 10;
const int INF = 0x3f;
int a = 0, b = 0, c = 0;//第一题，第二题，第三题 
int n, A, B;
int main(){
	cin >> n >> A >> B;
    int x;
	for(int i = 1;i <= n; i++){
		cin >> x;
		if(x <= A)a++;//第一种 
		if(A<=x && x<=B)b++;//第二种 
		else if(x >= B) c++;//第三种 
	}
	cout << min(a, min(b ,c));//输出最小值 
}
```
~~看懂了再ctj~~

---

## 作者：happybob (赞：0)

~~跟同机房的抢题解啦！~~

# 简略题意

给定 $n, a, b$ 和序列 $p_1, p_2, p_3, ……, p_n$，定义 $x = \sum_{i=1}^n \begin{cases} 1 & p_i \le a  \\ 0 & \text{otherwise} \end{cases}, y = \sum_{i=1}^n \begin{cases} 1 & a < p_i \le b \\ 0 & \text{otherwise} \end{cases}, z= \sum_{i=1}^ n\begin{cases} 1 & p_i > b \\ 0 & \text{otherwise} \end{cases} $，求 $\min(x,y,z)$ 为多少。

# 解法

对每个 $p_i$ 进行统计并处理即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int cnt[5], n, a, b;

int main()
{
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        cnt[1] += (x <= a);
        cnt[2] += (x > a && x <= b);
        cnt[3] += (x >= b + 1);
    }
    printf("%d\n", min({ cnt[1], cnt[2], cnt[3] }));
    return 0;
}
```


补充一个知识，很多人不知道，C++11 中可以使用 `min({a, b, c, ……})` 获取多个值的最小值，`max` 同理。

---

## 作者：xiaoqinglang11 (赞：0)

### 题目大意
有N个问题，第 $i$ 个问题的分值是 $P_i$ 。

举行比赛的题目要求：
1. 第一题分值 $\leq A$ 分；
2. $A$ 分 $<$ 第二题分值 $\leq B$ 分；
3. 第三题分值 $\geq A$ 分。

求最多能举行几场比赛。

### 思路
很简单，只要统计出每种题目的个数，在取最小值就行了！

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a,b;
int cnt[4];//用此数组统计每种题目的个数
int main()
{
	scanf("%d",&n);
	scanf("%d%d",&a,&b);
	for(int i=1;i<=n;i++)
	{
		int p;
		scanf("%d",&p);
		if(p<=a)
			cnt[1]++;//第一种
		else if(p>b)
			cnt[3]++;//第三种
		else
			cnt[2]++;//第二种
	}
	printf("%d\n",min(cnt[1],min(cnt[2],cnt[3]));//注意min不能有3个参数
	return 0;
}
```

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4573)

小学生又双叒叕来写题解啦！

我来介绍一种与众不同的~~跑得更慢的~~方法，那就是**排序加二分**。

排序的作用是为了二分，因为二分的前提是数组有序。

因此读入完数据后排序一下。

然后调用算法库的二分函数。

二分函数指[这些](https://blog.csdn.net/weixin_43237242/article/details/90450726)，不会的童鞋自己了解。

思路是先算出第一个问题的数量，即使用二分卡出范围。

再算出第一、二个问题的总数量，再与上面的相减。

第三个问题就是用总数减去前两个问题的数量。

最后输出三个问题数量中的最小值即可。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>  //调用二分函数。
using namespace std;
int a[105];
int main()
{
	int n, A, B;
	scanf("%d%d%d", &n, &A, &B);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a+1, a+n+1);
	int one = upper_bound(a+1, a+n+1, A) - a - 1;
	int two = upper_bound(a+1, a+n+1, B) - a - 1 - one;
	int three = n - one - two;
	int t = min(one, two);
	printf("%d\n", min(t, three));  //别漏掉祖传换行。
	return 0;
}
```

---

## 作者：Obviathy (赞：0)

## 题意简述：
给出一个有 $n$ 个元素的集合，将它们分成三类（就是三个小集合），分别是：

- $\{ x \in N | A \le x \}$
- $\{ x \in N | A +  1\le x \le B\}$
- $\{ x \in N | B \le x \}$

求这三个集合中元素个数最小的个数是几。
## 解题思路：
其实，根据题意简述，思路就已经很清晰了，直接用三个计数器，判断加统计这三种集合中的元素个数，最后求最小值即可。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,p;
int cnt1,cnt2,cnt3;
void work(int x){//判断集合
	if(x <= a)cnt1++;
	if(a < x && x <= b)cnt2++;
	if(x > b)cnt3++;
}
int main(){
	cin >> n >> a >> b;
	for(int i = 0;i < n;i ++){
		cin >> p;
		work(p);	
	}
	cout<<min(cnt1,min(cnt2,cnt3))<<endl;	
	return 0;
}

```
[AC！](https://www.luogu.com.cn/record/68462458)


---

## 作者：20100202w (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4573)

这道题非常简单，只要充分理解题意就行了 。

### 题意：

这题就是说每个比赛都有三道题，每道题的得分都要满足一个条件，最后让你判断最多有多少个比赛 。

### 分析：

文最多有多少个比赛，首先要弄清楚，比赛的多少是根据最少的得分段而决定的，最少的得分段是几，答案就是几。

代码：
```cpp
#include<iostream>
#include<cstdio>//头文件
using namespace std;
int minn(int a,int b,int c)//
{
	return a<b?(a<c?a:c):(b<c?b:c); //三个数比谁小
}
int main()
{
	int a1=0,b1=0,c1=0,a,b,n,s;
	cin>>n>>a>>b;//输入
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s);
		if(s<=a)a1++; //分别计算得分段
		else if(s>=a+1&&s<=b)
				b1++;
			else c1++; 
	} 
	cout<<minn(a1,b1,c1);//输出最小得分段
	return 0;//养成好习惯
                                  
}

```


---

## 作者：eEfiuys (赞：0)

题目：[AT4573](https://www.luogu.com.cn/problem/AT4573)

只需要边输入，边统计三种情况的分数的个数，对应的情况个数加 $1$，分别用一个变量存，最后输出三种情况的最小值即可（三个数取最小值，就是其中两个数的最小值与另一个数的最小值）。~~应该没有人爆搜吧~~

```cpp
while(n--){
	cin>>p;
	if(p<=a)x1++; //T1
	else if(p<=b)x2++; //T2
	else x3++; //T3
}
cout<<min(x1,min(x2,x3))<<endl; //两次最小值
```

---

