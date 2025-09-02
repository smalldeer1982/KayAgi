# Problems for Round

## 题目描述

There are $ n $ problems prepared for the next Codeforces round. They are arranged in ascending order by their difficulty, and no two problems have the same difficulty. Moreover, there are $ m $ pairs of similar problems. Authors want to split problems between two division according to the following rules:

- Problemset of each division should be non-empty.
- Each problem should be used in exactly one division (yes, it is unusual requirement).
- Each problem used in division 1 should be harder than any problem used in division 2.
- If two problems are similar, they should be used in different divisions.

Your goal is count the number of ways to split problem between two divisions and satisfy all the rules. Two ways to split problems are considered to be different if there is at least one problem that belongs to division 1 in one of them and to division 2 in the other.

Note, that the relation of similarity is not transitive. That is, if problem $ i $ is similar to problem $ j $ and problem $ j $ is similar to problem $ k $ , it doesn't follow that $ i $ is similar to $ k $ .

## 说明/提示

In the first sample, problems $ 1 $ and $ 2 $ should be used in division 2, while problems $ 4 $ and $ 5 $ in division 1. Problem $ 3 $ may be used either in division 1 or in division 2.

In the second sample, all pairs of problems are similar and there is no way to split problem between two divisions without breaking any rules.

Third sample reminds you that the similarity relation is not transitive. Problem $ 3 $ is similar to both $ 1 $ and $ 2 $ , but $ 1 $ is not similar to $ 2 $ , so they may be used together.

## 样例 #1

### 输入

```
5 2
1 4
5 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 2
3 1
3 2
```

### 输出

```
1
```

# 题解

## 作者：Fuxh_18 (赞：3)

## CF673B Problems for Round题解
### 题目大意
有 $n$ 道题和 $m$ 对相似题目，把 $n$ 道题分到 div1 与 div2 中，div1 的每到题都比 div2 的难度高。并且，相似题目不能在同一组中。问有几种分法。

### 问题分析
div1 的每到题都比 div2 的难度高，也就是说，div1 中的最小值比 div2 中的最大值要大。我们能先把相似的题目分开，难度小的放 div2，大的放在 div1，同时，求出 div1 中的最小值与 div2 中的最大值，之后在这之间的题目可以随意分。

注意：若 $m=0$ 就把所有题分开。若 div1 的最小值比 div2 的最大值小，那么没有方案，输出 $0$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,mx,mn;
int main(){
	cin>>n>>m;
	if(m==0){ //特判
		cout<<n-1;
		return 0;
	}
	mx=0,mn=n+1;
	for(int i=1;i<=m;i++){
		long long a,b;
		cin>>a>>b;
		mx=max(mx,min(a,b));
		mn=min(mn,max(a,b));
	}
	if(mn>mx){ //判断是否合法 
		cout<<mn-mx;
	}
	else{
		cout<<0;
	}
	return 0;
}
```

本题讲解完毕。

---

## 作者：lhs_chris (赞：0)

# 思路
我们容易想到，要是想要把一个长度为 $n$ 的数组中的数字分成两份。其中第一份的所有数字都要大于第二份。那么会有 $n-1$ 种方案。也就是每两个数字之间划分一次。

题目输入 $m$  组 $x$ 和 $y$，要求 $x$ 和 $y$ 不能被分到一组。那么会有两种不可行的情况，$x$ 和 $y$ 同时被分到数字较小的那组，或者同时分到较大的那组。

如下图，以红色线条作为划分的情况是不可行的。

![lhs](https://cdn.luogu.com.cn/upload/image_hosting/6en5ifa3.png)

也是就 $1 \sim x$ 和 $y \sim n$ 的所有数字之间划分的情况是不可行的。那我们可以想到一个比较暴力的方法，差分标记不可行情况。

```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=3e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
int n,m; 
int x,y; 
int a[N];//a[i]表示i和i+1之间划分可不可行
int ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		if(x>y)
		{
			swap(x,y);
		}
		a[1]++;
		a[x]--;
		a[y]++;
		a[n]--;
	} 
	for(int i=1;i<=n;i++)
	{
		a[i]+=a[i-1];
	}
	for(int i=1;i<n;i++)
	{
		if(a[i]==0)
		{
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：szh_AK_all (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF673B)

这道题虽然不难，但是需要理解。

首先，我们考虑一个问题。给定一个严格递增的数组 $s$，其长度为 $len$，要求将数组里的数字分为两个部分，让第一个部分里的数字大于第二个部分里的所有数字，问，有几种方法。

但看如上问题，还是挺简单的。我们可以将第一个数放入第二个部分，其余的数放入第一部分。也可以将第一、二个数放入第二部分，其余的数放入第一部分...依此类推，我们发现，一共有 $len$ 种方法。

解决了如上问题，那么解决这道题就好办了。我们讲题目里说的 $n$ 个问题看成一个数组，因为第 $i$ 个问题的难度为 $i$，所以，这个数组其实也是递增的。如果没有相似的问题，那么可选方案肯定是 $n$ 种。

我们再回到题目，仔细思考一下。如果有两个数 $a$ 和 $b$（$a \le b$），再给定一段区间，一直区间的上限为 $n$，下限为 $1$。要让 $a$ 和 $b$，不能同时在这一个区间里。如果上限不变，那么下限如果小于 $a$，则 $a$ 和 $b$ 肯定是在同一个区间里。所以，上限的取值范围只有在 $a$ 和 $b$ 之间，才符合要求。

现在根据题目要求，依次读入第 $i$ 组相似问题。由于每组的两个问题不能再同一部分，所以，我们将难的问题放入第一部分，将简单的问题放入第二部分，就回到了了刚才所讲的。由于第一部分肯定是在第二部分右边（因为右边的数比左边的数大），而这两个数不能再同一部分，那么，下限会发生改变，并且满足下限的值不小于这组问题中简单的问题的值；同时，上限也会改变，并且满足上限的值不大于这组问题中难题的值。最后，用上限减下限，便是方案数。

# Code
```c
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,m,ans,tmp;
	cin>>n>>m;
	ans=n;
	tmp=1;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		tmp=max(tmp,min(x,y));
		ans=min(ans,max(x,y));
	}
	cout<<max(ans-tmp,0);
}
```
[感谢观看！](https://www.luogu.com.cn/blog/jdsndjknddb/solution-cf673b)


---

## 作者：Edmundino (赞：0)

# 题意

$n$ 个问题，$m$ 对题目相似，给出 $m$ 对相似的题的编号；

$n$ 个问题的难度值就为他们的编号，现在要将这 $n$ 个问题按要求放到两个题库里（div1，div2）

要求：div1中的题目难度要比div2中的每个题的难度都大，相似的题不能放到同一个题库中。

现在问有几种放法。

# 分析

首先我们需要两个数 $minx,maxx$，表示div1中的最小值和div2的最大值。

其实对每一组相似得题目，我们把小的数放在div2，大的数放在div1。

同时同步更新最大值。

最后，如果 $maxx\le minx$：这两个中间的数可以随便分配，所以就有 $minx-maxx$ 种放法，

否则就只有 $0$。

# 代码

核心部分

```cpp
while(m--){
	int a,b;
	cin>>a>>b;
	maxx=max(maxx,min(a,b));minx=min(minx,max(a,b));
}
if(minx>maxx)cout<<minx-maxx<<endl;
else cout<<0;
```


---

