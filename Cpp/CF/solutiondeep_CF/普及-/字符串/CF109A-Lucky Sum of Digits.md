# 题目信息

# Lucky Sum of Digits

## 题目描述

Petya喜欢幸运数字。我们都知道幸运数字是只含有$4$ 和$7$ 的正整数。例如数字$47$ ，$744$ ，$4$ 是幸运数字，而$5$ ，$17$ ，$467$ 不是。

Petya急切的想知道各个数位上数字的和为$n$ 的最小幸运数字是多少。帮助他完成这个任务。

## 样例 #1

### 输入

```
11
```

### 输出

```
47
```

## 样例 #2

### 输入

```
10
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写
# 幸运数字的位数和

## 题目描述

Petya喜欢幸运数字。我们都知道幸运数字是只含有$4$ 和$7$ 的正整数。例如数字$47$ ，$744$ ，$4$ 是幸运数字，而$5$ ，$17$ ，$467$ 不是。

Petya急切的想知道各个数位上数字的和为$n$ 的最小幸运数字是多少。帮助他完成这个任务。

## 样例 #1

### 输入

```
11
```

### 输出

```
47
```

## 样例 #2

### 输入

```
10
```

### 输出

```
-1
```

### 题解分析与结论

#### 综合分析
1. **贪心算法**：大多数题解都采用了贪心算法，优先使用$7$，因为$7$可以减少数字的位数，从而使得数字更小。这是解决该问题的核心思路。
2. **动态规划**：部分题解尝试使用动态规划，但相比贪心算法，动态规划的复杂度较高，且实现较为复杂，不推荐。
3. **模拟与枚举**：部分题解通过枚举$4$和$7$的数量，判断是否满足条件，这种方法虽然直观，但效率较低。

#### 最优思路
- **贪心算法**：优先使用$7$，尽可能减少数字的位数，然后再使用$4$。这种方法既简单又高效，是解决该问题的最佳选择。

#### 可拓展之处
- **类似问题**：可以扩展到其他类似的问题，例如使用其他数字组合（如$3$和$5$）来构造满足特定条件的数字。
- **优化技巧**：在贪心算法中，可以通过提前判断是否满足条件来减少不必要的计算。

### 推荐题目
1. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

### 所选高星题解

#### 题解1：作者：MZY666 (赞：9)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，贪心算法实现得当，且通过优化减少了不必要的计算。
- **个人心得**：作者在实现过程中提到通过将$7$个$4$转换为$4$个$7$来优化结果，这一点在贪心算法中非常重要。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll n,i=0,j=0;
	scanf("%lld",&n);
	i=n/4;n-=i*4;
	if(n){
		while(i>0){
			n+=4;i--;
			if(n%7==0){j=n/7;n=0;break;}
		}
	}
	if(n)printf("-1\n");
	else{
		while(i>=7){i-=7;j+=4;}
		while(i--)printf("4");
		while(j--)printf("7");
		printf("\n");
	}
	return 0;
}
```

#### 题解2：作者：Laser_Crystal (赞：5)
- **星级**：4星
- **关键亮点**：代码简洁，贪心算法实现得当，且通过枚举$4$的数量来找到最优解。
- **个人心得**：作者提到通过枚举$4$的数量来找到最优解，这种方法虽然简单，但在实际应用中非常有效。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<=n/4;i++) 
	{
		int f,s;
		f=i*4;
		s=n-f;
		if(s%7==0) 
		{
			for(int j=0;j<i;j++) cout<<'4';
			s/=7;
			for(int j=0;j<s;j++) cout<<'7';
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

#### 题解3：作者：PC_DOS (赞：0)
- **星级**：4星
- **关键亮点**：代码结构清晰，贪心算法实现得当，且通过从最多的$7$开始枚举来优化结果。
- **个人心得**：作者提到通过从最多的$7$开始枚举来优化结果，这种方法在贪心算法中非常有效。

```cpp
#include <iostream>
#include <string>
using namespace std;
string CreateRequiedString(long long nCount, char chrChrarater){
	int i;
	string sAns;
	for (i = 1; i <= nCount; ++i)
		sAns += chrChrarater;
	return sAns;
}
int main(){
	ios::sync_with_stdio(false);
	int iSum, nSeven, nFour;
	cin >> iSum;
	for (nSeven = iSum / 7; nSeven>=0; --nSeven){
		nFour = iSum - 7 * nSeven;
		if (nFour % 4 == 0){
			cout << CreateRequiedString(nFour / 4, '4') << CreateRequiedString(nSeven, '7');
			goto endapp;
		}
	}
	cout << -1;
	endapp:
	return 0;
}
```

---
处理用时：32.74秒