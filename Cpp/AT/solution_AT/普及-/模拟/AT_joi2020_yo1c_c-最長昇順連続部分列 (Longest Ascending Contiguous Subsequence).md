# 最長昇順連続部分列 (Longest Ascending Contiguous Subsequence)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020yo1c/tasks/joi2020_yo1c_c

長さ $ N $ の正整数列 $ A=(A_1,\ A_2,\ \ldots,\ A_N) $ が与えられる．正整数列 $ A $ の連続部分列の中で昇順に並んでいるもののうち，最長のものの長さを求めよ．

すなわち，$ A_l\ \leqq\ A_{l+1}\ \leqq\ \cdots\ \leqq\ A_r $ を満たすような $ 2 $ つの整数 $ l,\ r $ ( $ 1\ \leqq\ l\ \leqq\ r\ \leqq\ N $ ) について，$ r-l+1 $ の最大値を求めよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 100 $．
- $ 1\ \leqq\ A_i\ \leqq\ 2020 $ ($ 1\ \leqq\ i\ \leqq\ N $)．

### Sample Explanation 1

正整数列 $ A $ の $ 4 $ 項目から $ 6 $ 項目までに対応する連続部分列は $ 1,\ 5,\ 9 $ であり，これは昇順である．これより長い昇順な連続部分列は存在しない．

### Sample Explanation 2

正整数列 $ A $ の $ 5 $ 項目から $ 6 $ 項目までに対応する連続部分列は $ 5,\ 5 $ であり，これは昇順である．これより長い昇順な連続部分列は存在しない．

## 样例 #1

### 输入

```
10
3 1 4 1 5 9 2 6 5 3```

### 输出

```
3```

## 样例 #2

### 输入

```
10
9 8 7 6 5 5 4 3 2 1```

### 输出

```
2```

## 样例 #3

### 输入

```
9
1 2 2 12 120 210 202 1010 2020```

### 输出

```
6```

# 题解

## 作者：封禁用户 (赞：1)

## 题目翻译
给定长度为 $N$ 的正整数列，求正整数列 $A$ 的连续部分列中升序排列的最长长度。
## 思路
我们枚举数组，找出每一个升序排列的元素个数，再求一个最大值即可。

## CODE
```cpp
#include<bits/stdc++.h>

using namespace std;

int n;
int a[10000];

int maxx=-1e6,ans;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}

	for(int i=1;i<=n;i++)
	{
		if(a[i]<=a[i+1])
		{
			ans++;
		}
		else
		{
			maxx=max(maxx,ans+1);
			ans=0;
		}
	}
	
	cout<<maxx<<endl;
	
    return 0;
}
```


---

## 作者：NOI_AK_dreeeam (赞：0)

这题用 `for` 循环遍历整个数组，找出每一个升序排列的元素个数，如果这个数小于等于后面的数，说明这还是一个升序排列；否则就用 $ans$ 找出长度最大的升序排列。最后输出 $ans$。

**_AC code_**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],ans=-114514,sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	a[n+1]=a[n]-1;//边界处理
	for(int i=1;i<=n;i++){
		sum++;
		if(a[i]>a[i+1]){//说明这个升序排列已结束
			ans=max(sum,ans);//求最大值
			sum=0;//记得赋值为0
		}
	}
	cout<<ans<<"\n";//输出最大值
    return 0;
}
```


---

