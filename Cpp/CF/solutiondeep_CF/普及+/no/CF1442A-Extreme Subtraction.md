# 题目信息

# Extreme Subtraction

## 题目描述

You are given an array $ a $ of $ n $ positive integers.

You can use the following operation as many times as you like: select any integer $ 1 \le k \le n $ and do one of two things:

- decrement by one $ k $ of the first elements of the array.
- decrement by one $ k $ of the last elements of the array.

For example, if $ n=5 $ and $ a=[3,2,2,1,4] $ , then you can apply one of the following operations to it (not all possible options are listed below):

- decrement from the first two elements of the array. After this operation $ a=[2, 1, 2, 1, 4] $ ;
- decrement from the last three elements of the array. After this operation $ a=[3, 2, 1, 0, 3] $ ;
- decrement from the first five elements of the array. After this operation $ a=[2, 1, 1, 0, 3] $ ;

Determine if it is possible to make all the elements of the array equal to zero by applying a certain number of operations.

## 样例 #1

### 输入

```
4
3
1 2 1
5
11 7 9 6 8
5
1 3 1 3 1
4
5 2 1 10```

### 输出

```
YES
YES
NO
YES```

# AI分析结果

### 题目翻译
## 极端减法

### 题目描述
给定一个包含 $n$ 个正整数的数组 $a$。

你可以根据需要多次使用以下操作：选择任意整数 $1 \le k \le n$，然后执行以下两项操作之一：
- 将数组的前 $k$ 个元素都减 1。
- 将数组的后 $k$ 个元素都减 1。

例如，如果 $n = 5$ 且 $a = [3, 2, 2, 1, 4]$，则可以对其应用以下操作之一（以下未列出所有可能的选项）：
- 对数组的前两个元素执行减 1 操作。此操作之后，$a = [2, 1, 2, 1, 4]$。
- 对数组的后三个元素执行减 1 操作。此操作之后，$a = [3, 2, 1, 0, 3]$。
- 对数组的前五个元素执行减 1 操作。此操作之后，$a = [2, 1, 1, 0, 3]$。

判断是否可以通过执行一定次数的操作使数组的所有元素都等于 0。

### 样例 #1
#### 输入
```
4
3
1 2 1
5
11 7 9 6 8
5
1 3 1 3 1
4
5 2 1 10
```

#### 输出
```
YES
YES
NO
YES
```

### 算法分类
差分

### 综合分析与结论
这些题解主要围绕如何判断能否通过给定操作将数组元素全部变为 0 展开，大部分题解都运用了差分的思想。通过将原问题转化为差分数组的操作问题，利用差分的性质来简化判断过程。不同题解在具体实现和思路细节上有所差异，但核心都是基于差分来处理。

### 所选题解
- **作者：_Ezreal (赞：15)，4星**
    - **关键亮点**：思路清晰，直接利用差分数组的性质，将问题转化为判断差分数组中小于 0 的数的绝对值之和是否小于等于 $a[1]$，代码简洁易懂。
- **作者：LeavingZzz (赞：9)，4星**
    - **关键亮点**：将问题转化为构造单调不减和单调不增的两个序列，通过贪心策略进行构造，思路独特且清晰。
- **作者：LEle0309 (赞：3)，4星**
    - **关键亮点**：详细解释了差分的概念和作用，结合本题对差分数组的操作进行分析，逻辑严谨。

### 重点代码
#### _Ezreal 的代码
```cpp
# include <cstdio>

const int N=1e5+5;
int a[N];
int n;

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		for(int i=n;i>=1;i--)
		a[i]-=a[i-1];
		
		int sum=0;
		for(int i=2;i<=n;i++)
		if(a[i]<0) sum-=a[i];
		
		if(a[1]>=sum)
		printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```
**核心实现思想**：先求出原数组的差分数组，然后统计差分数组中小于 0 的数的绝对值之和，最后判断该和是否小于等于 $a[1]$ 来确定是否可以将数组元素全部变为 0。

#### LeavingZzz 的代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;
const int maxn=30007;
int T,N;
int A[maxn],inc[maxn],dec[maxn];
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=1;i<=N;i++)
            scanf("%d",&A[i]);
        dec[1]=A[1];
        inc[1]=0;
        bool f=true;
        for(int i=2;i<=N;i++)
        {
            dec[i]=min(dec[i-1],A[i]-inc[i-1]);
            if(dec[i]<0) {f=false;break;}
            inc[i]=A[i]-dec[i];
        }
        if(f) puts("YES");
        else puts("NO");
    }
    return 0;
}
```
**核心实现思想**：将问题转化为构造单调不减的序列 `inc` 和单调不增的序列 `dec`，使得它们对应位置的和等于原数组元素。通过贪心策略，让 `inc` 序列的值尽量小，`dec` 序列的值尽量大，若构造过程中出现负数则无解。

#### LEle0309 的代码
```cpp
#include<iostream>
using namespace std;
const int maxn=3e4+7;
int t,a[maxn],d[maxn],n,s,i,ans;
int main()
{
	cin>>t;
	while(t--)//t组数据
	{
		cin>>n;ans=0;s=0;//多测不清空，提交两行泪（WA了一次QAQ）
		for(i=1;i<=n;i++)//输入
		{
		    cin>>a[i];
			d[i]=a[i]-a[i-1];//求差分数组
		}
		for(i=2;i<=n;i++)if(d[i]<0)s+=(-1*d[i]);//差分数组中负数绝对值之和
		if(s<=a[1])cout<<"YES\n";//情况1
		else cout<<"NO\n";//情况2
	}
	return 0;//完结撒花！
}
```
**核心实现思想**：先求出原数组的差分数组，统计差分数组中负数的绝对值之和，若该和小于等于 $a[1]$ 则可以将数组元素全部变为 0，否则不行。

### 最优关键思路或技巧
- **差分思想**：将原问题转化为差分数组的操作问题，利用差分的性质简化判断过程。
- **贪心策略**：在构造序列时，通过贪心策略让序列满足一定的条件，从而判断是否有解。

### 拓展思路
同类型题或类似算法套路：涉及区间操作的题目，如区间加减、区间修改等，都可以考虑使用差分来优化时间复杂度。

### 推荐题目
- [P3397 地毯](https://www.luogu.com.cn/problem/P3397)
- [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)
- [P1083 借教室](https://www.luogu.com.cn/problem/P1083)

### 个人心得摘录与总结
- **LEle0309**：提到“多测不清空，提交两行泪（WA了一次QAQ）”，总结出在处理多组测试数据时，要注意清空相关变量，避免数据干扰导致错误。
- **ql12345**：分享了自己在考场上的思考过程，从错误的思路逐渐发现正确的方向，强调了遇到问题时要冷静思考，将问题统一起来，并且理解不同部分之间的独立性。 

---
处理用时：48.36秒