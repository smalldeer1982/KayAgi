# 题目信息

# Stripe

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 样例 #1

### 输入

```
9
1 5 -6 7 9 -16 0 -2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
0 0
```

### 输出

```
1
```

# AI分析结果

### 题目内容重写

#### 题目描述

Bob 有一条由 $n$ 个方格组成的纸带（纸带的高度为 1 个方格）。他在每个方格中写了一个整数，可能是负数。他想知道有多少种方法可以将这条纸带切成两段，使得其中一段的数字之和等于另一段的数字之和，并且每一段都包含至少一个方格。你能帮助 Bob 解决这个问题吗？

#### 样例 #1

##### 输入

```
9
1 5 -6 7 9 -16 0 -2 2
```

##### 输出

```
3
```

#### 样例 #2

##### 输入

```
3
1 1 1
```

##### 输出

```
0
```

#### 样例 #3

##### 输入

```
2
0 0
```

##### 输出

```
1
```

### 题解分析与结论

#### 综合分析

本题的核心问题是如何高效地计算将纸带切成两段，使得两段的和相等。所有题解都围绕前缀和这一核心思想展开，通过预处理前缀和数组，将问题的时间复杂度从 $O(n^2)$ 优化到 $O(n)$。

#### 最优关键思路

1. **前缀和**：通过预处理前缀和数组，可以在 $O(1)$ 时间内计算任意区间的和，从而快速判断切割点是否满足条件。
2. **枚举切割点**：通过枚举所有可能的切割点，利用前缀和数组快速判断两段的和是否相等。

#### 推荐题目

1. P3131 [USACO16JAN]子共七Subsequences Summing to Sevens
2. P2280 [HNOI2003]激光炸弹
3. P1083 借教室

### 精选题解

#### 题解1：zhangyuhan (5星)

**关键亮点**：
- 简洁明了地介绍了前缀和的概念及其应用。
- 代码结构清晰，逻辑简单，易于理解。
- 时间复杂度优化到 $O(n)$，适合大规模数据处理。

**核心代码**：
```cpp
#include<iostream>
using namespace std;

int n,a[100010],s[100010];//s为记录前缀和的数组

int ans;//记录答案

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }//读入+统计前缀和
    for(int i=1;i<=n-1;i++){
        if(s[i]==s[n]-s[i])//比较两个区间的和是否一样
            ans++;//如果一样，答案++
    }
    cout<<ans<<endl;//输出答案
    return 0;//完结撒花！
}
```

#### 题解2：_FILARET_ (4星)

**关键亮点**：
- 详细解释了前缀和的概念及其应用场景。
- 提供了额外的练习题，帮助读者巩固知识。
- 代码中包含了调试输出，便于理解。

**核心代码**：
```cpp
#include <iostream>
using namespace std;
const int MAXN=100005;
//题目中数组最大限制
int N;
long long a[MAXN]={0};
long long s[MAXN]={0};
//前缀和数组
long long sum=0;
//所有数的和，其实这个也可以用s[N]代替
int ans=0;
//记录答案
int main()
{
	cin>>N;
	for(int i=1;i<=N;i++) //要从1开始循环，不然会数组溢出
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
        //处理前缀和，即将上一个数的前缀和加上目前的数
		sum+=a[i];
        //加和
			//cout<<s[i]<<" ";
        //调试用品，没有什么用
	}
	for(int i=1;i<N;i++)
	{
		if(s[i]*2==sum)
		{
       		//这里使用if(sum/s[i]==2)会炸
        	//判断是否符合条件
			ans++;
            //如果符合条件，就将ans++
		}
	}
	cout<<ans;
    //输出
	return 0;
    //回家领糖吃咯
}
```

#### 题解3：lxzy_ (4星)

**关键亮点**：
- 提供了多种解题方法，包括暴力求和、动态求和和前缀和。
- 详细分析了每种方法的时间复杂度，并给出了优化建议。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
#include<cstdio>
using namespace std;
const int N=1e5+50;
int a[N];//定义数组，废话
int s[N];//定义前缀和数组
int n;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];//求前缀和
    }

    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(s[i]==s[n]-s[i])//如果当前前段数列的和等于后段数列的和
        {
            ans++;//累加
        }
    }

    printf("%d",ans);//完美~
    return 0;
}
```

### 总结

前缀和是解决区间和问题的利器，能够将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。在处理大规模数据时，前缀和的应用尤为重要。通过枚举切割点并结合前缀和数组，可以高效地解决本题。

---
处理用时：44.12秒