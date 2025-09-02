# [ABC136C] Build Stairs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc136/tasks/abc136_c

左右一列に $ N $ 個のマスが並んでおり、左から $ i $ 番目のマスの高さは $ H_i $ です。

あなたは各マスについて $ 1 $ 度ずつ次のいずれかの操作を行います。

- マスの高さを $ 1 $ 低くする。
- 何もしない。

操作をうまく行うことでマスの高さを左から右に向かって単調非減少にできるか求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ H_i\ \leq\ 10^9 $

### Sample Explanation 1

左から $ 2 $ 番目のマスのみ高さを $ 1 $ 低くすることで目的を達成できます。

## 样例 #1

### 输入

```
5
1 2 1 1 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4
1 3 2 1```

### 输出

```
No```

## 样例 #3

### 输入

```
5
1 2 3 4 5```

### 输出

```
Yes```

## 样例 #4

### 输入

```
1
1000000000```

### 输出

```
Yes```

# 题解

## 作者：Kvaratskhelia (赞：2)

首先，看到题目中有一句话 ：您将**一次**执行以下任一操作。

也就是说，使得数列没有符合题目条件的那些数字最多只能减一。

所以只要那个最大的数减去他后面某数的值大于$2$，这个序列就无法符合题目中的条件。

然后代码就出来了，读入一个数，每次记录最大值，然后用这个最大值减去这个数比较一下即可。

~~简洁的代码~~

```cpp
#include<bits/stdc++.h>
#define ft(i,l,r) for(register int i=l;i<=r;i++)
#define fd(i,r,l) for(register int i=r;i>=l;i--)
using namespace std;
int n,x,mx,bo;
int main()
{
	cin>>n;
	ft(i,1,n)
	{
		scanf("%d",&x);
		mx=max(mx,x); //记录最大值
		if(mx-x>=2) bo=1; //判断，bo=1表示不符合条件
	}
	if(bo==1) cout<<"No";
	else cout<<"Yes";
	cout<<endl; //换行加着保险
	return 0;
}
```

[AC记录](https://atcoder.jp/contests/abc136/submissions/15779481)

---

## 作者：Zirnc (赞：1)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)

> 从左到右连续排列 $N$ 个正方形。从左起第 $i$ 个正方形的高度为 $H_i$。
>
> 对于每个正方形，您将一次执行以下任一操作：
>
> - 将正方形的高度减少 $1$。
> - 什么都不做
>
> 确定是否可以执行操作，以使正方形的高度从左到右不减小。

输入完之后，从后往前推，如果 $h_{i-1}$ 和 $h_i$ 的差大于 $1$，说明怎么操作也不可以了，输出 `No`。

如果 $h_{i-1}-1==h_i$，说明还可以~~抢救一下~~通过操作变成一样多，也就是不减小，把 $h_{i-1}-1$ 之后继续推下去。

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;
int n;
long long h[100005];
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }

  for (int i = n - 1; i > 0; i--) {
    if (h[i - 1] - 1 > h[i]) {
      cout << "No\n";
      return 0;
    } else if (h[i-1]-1 == h[i]) {
      h[i-1]--;
    }
  }

  cout << "Yes\n";
  return 0;
}

```

---

## 作者：heaksicn (赞：0)

## 1 题意
给定一个数组 $a$，对于每个 $a_i$，可以将它减一或什么都不做。

问能否是这个数组非递减。
## 2 思路
我们发现，对于每个数 $a_i$，只有 $a_{i-1}$ 对其有影响。所以我们分类讨论两者的关系。

1. 当 $a_i>a_{i-1}$ 时，为了使 $a_i$ 尽量小，我们可以将 $a_i$ 减一。

2. 当 $a_i=a_{i-1}$ 时，$a_i$ 不可能再变动，所以不做任何变动。

3. 当 $a_i<a_{i-1}$ 时，不符合条件，输出 No。

最后输出 Yes。

时间复杂度 $O(n)$。
## 3 code
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
		if(a[i]<a[i-1]){//不符合条件
			cout<<"No";
			return 0;
		}
		if(a[i]>a[i-1]) a[i]--;//a[i]可以减
	}
	cout<<"Yes";
	return 0;
}
```


---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4894)

小学生又双叒叕来写题解啦！

翻了一下大家的思路，都用了数组，其实根本不用，可以一边读入一边判断。

由于只需考虑前后两个数，所以只用两个变量就能实现滚动数组。

若前数大于后数，由于前数已经执行过操作，而后数无法改变大小关系，因**此直接爆掉**。

若前数等于后数，再改变后数时便不符合要求，所以**什么都不做**。

若前数小于后数，根据贪心的思路，直接**给后数减一**比什么都不做好。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#define Error {printf("No\n"); return 0;}
using namespace std;

int main()
{
	int n, now, last;
	scanf("%d", &n);
	scanf("%d", &now);
	for (int i = 2; i <= n; i++)
	{
		last = now;
		scanf("%d", &now);
		if (last < now) now--;
		else if (last > now) Error
	}
	printf("Yes\n");  //千万别忘了换行。
	return 0;		
}
```


---

## 作者：wjk2020 (赞：0)

给大家讲一个 O(n) 的蒟蒻方法

首先，这道题是让我们判定一个序列是否是不下降序列。

所以，每遇到一个数时，总有两种情况：

1. $a[i]-a[i-1] \le -1$ 时：	

	意味着这个序列不是不下降序列，输出，结束。
    
2. $a[i]-a[i-1] \ge 0$ 时：继续

所以，这是一个 n 。为了节约时间，我们再看输入：
 
1. 用 $string$ 输入

就不给代码了，总共30多行……

2. 用数组输入，总共 2n  , 但可以优化成 n , 个人认为挺好的。

```
#include<bits/stdc++.h>
using namespace std;
int a[100010];int main(){
    int n;cin >> n;cin >> a[1];
    for(int i = 2;i <= n;i++){
        cin >> a[i];//边输入边看能不能输出
        if(a[i] - a[i-1] <= 0)//坑
            cout << "No", exit(0);
    }
    cout << "Yes";
}
```
别抄，小心有坑。

最后说一句，空间也可以优化成 1，像这样：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{	
	int a, mx;
	bool f = false;
	int n;cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a;maxx = max(maxx, a);
		if(maxx - a >= 2)f = 1;
  		//已经无药可救时，标记
	}
	if(f) puts("No");
	else puts("Yes");
}
```


---

## 作者：Wuyanru (赞：0)

一道比较简单的题目。

首先我们来考虑暴力，时间复杂度为 $ \Theta\left(2^n\right) $,整个人当场去世。

下来考虑正解：

首先我们从左到右来判断每个方块能不能符合要求。

假设当前考虑的方块为第 $ i $ 个，那么有如下三种情况：

1.  $ H_{i-1}>H_i $

此时没有方法满足要求（第 $ i-1 $ 个方块已经进行操作），所以直接输出 `No` 并结束程序。

2.  $ H_{i-1}<H_i $

此时如果将第 $ i $ 个方块减少 $ 1 $,仍然会有 $ H_{i-1}\le H_i $,满足题目要求，此时进行操作显然会比不操作更优。

3.  $ H_{i-1}=H_i $

此时如果进行操作则不能满足题目要求，所以不进行任何操作。

最后，如果程序还在运行，则说明可以经过一系列操作满足题目要求，输出 `Yes`并结束程序。

AC代码：
```
#include<cstdio>
using namespace std;
int n;
int a[100001];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d",a+i);
	for(int i=1; i<=n; i++) {
		if(a[i-1]>a[i]) {
			printf("No");
			return 0;
		}
		if(a[i-1]<a[i])
			a[i]--;
	}
	printf("Yes");
	return 0;
}
```
感谢观看！

---

## 作者：zjr027 (赞：0)

这道题可以这样理解：

+ 有一个数列，对每一个数我们可以只能把它减 1 或减 0。

+ 能否使这个数列操作完后从左到右依次递增。

对于第 i 个数，如果它后面有比它至少大 2 的数，

那么答案就是否！

因为如果它后面有比它至少大 2 的数，

我们最多只能让这两个数的差至少变为 1，

前者减0，后者减1。

可是如果这题用暴力解的话，时间复杂度 $O(n^2)$。

$(10^5)^2 > 10^8$，会超时。

所以要优化，那怎么优化呢？

我们可以做一个后缀 max 的预处理。（相当于以空间换时间）

这样时间复杂度就会变成 $O(n)$， 也就可以过了！

代码如下：

+ 暴力（超时）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, h[100005];
int main(){
	scanf("%d\n", &n); // 输入 
	for(int i = 1;i <= n;i++){
		scanf("%d", &h[i]);
	}
	for(int i = 1;i <= n;i++){ // 判断
		for(int j = n;j > i;j++){
			if(h[j] - h[i] > 1){
				printf("No");
				return 0;
			}
		}
	}
	printf("Yes");
	return 0;
}
```

+ 预处理：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, h[100005];
int main(){
	scanf("%d\n", &n); // 输入 
	for(int i = 1;i <= n;i++){
		scanf("%d", &h[i]);
	}
	for(int i = 1;i <= n;i++){ // 判断
		for(int j = n;j > i;j++){
			if(h[j] - h[i] > 1){
				printf("No");
				return 0;
			}
		}
	}
	printf("Yes");
	return 0;
}
```



---

