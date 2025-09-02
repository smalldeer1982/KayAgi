# 题目信息

# N Problems During K Days

## 题目描述

Polycarp has to solve exactly $ n $ problems to improve his programming skill before an important programming competition. But this competition will be held very soon, most precisely, it will start in $ k $ days. It means that Polycarp has exactly $ k $ days for training!

Polycarp doesn't want to procrastinate, so he wants to solve at least one problem during each of $ k $ days. He also doesn't want to overwork, so if he solves $ x $ problems during some day, he should solve no more than $ 2x $ problems during the next day. And, at last, he wants to improve his skill, so if he solves $ x $ problems during some day, he should solve at least $ x+1 $ problem during the next day.

More formally: let $ [a_1, a_2, \dots, a_k] $ be the array of numbers of problems solved by Polycarp. The $ i $ -th element of this array is the number of problems Polycarp solves during the $ i $ -th day of his training. Then the following conditions must be satisfied:

- sum of all $ a_i $ for $ i $ from $ 1 $ to $ k $ should be $ n $ ;
- $ a_i $ should be greater than zero for each $ i $ from $ 1 $ to $ k $ ;
- the condition $ a_i < a_{i + 1} \le 2 a_i $ should be satisfied for each $ i $ from $ 1 $ to $ k-1 $ .

Your problem is to find any array $ a $ of length $ k $ satisfying the conditions above or say that it is impossible to do it.

## 样例 #1

### 输入

```
26 6
```

### 输出

```
YES
1 2 4 5 6 8 
```

## 样例 #2

### 输入

```
8 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
YES
1 
```

## 样例 #4

### 输入

```
9 4
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# K 天内完成 N 道题

## 题目描述
在一场重要的编程竞赛之前，为了提高编程技能，Polycarp 必须恰好解决 $n$ 道题。但这场竞赛很快就要开始了，确切地说，将在 $k$ 天后举行。这意味着 Polycarp 只有 $k$ 天的训练时间！

Polycarp 不想拖延，所以他希望在 $k$ 天中的每一天至少解决一道题。他也不想过度劳累，所以如果他在某一天解决了 $x$ 道题，那么在接下来的一天他解决的题目数量不应超过 $2x$ 道。最后，他希望提高自己的技能，所以如果他在某一天解决了 $x$ 道题，那么在接下来的一天他至少应该解决 $x + 1$ 道题。

更正式地说：设 $[a_1, a_2, \dots, a_k]$ 是 Polycarp 每天解决的题目数量的数组。该数组的第 $i$ 个元素是 Polycarp 在训练的第 $i$ 天解决的题目数量。那么必须满足以下条件：
- 从 $1$ 到 $k$ 的所有 $a_i$ 的和应该等于 $n$；
- 对于从 $1$ 到 $k$ 的每个 $i$，$a_i$ 应该大于 $0$；
- 对于从 $1$ 到 $k - 1$ 的每个 $i$，应该满足条件 $a_i < a_{i + 1} \leq 2 a_i$。

你的任务是找到任何满足上述条件的长度为 $k$ 的数组 $a$，或者说明无法做到这一点。

## 样例 #1
### 输入
```
26 6
```
### 输出
```
YES
1 2 4 5 6 8 
```

## 样例 #2
### 输入
```
8 3
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
1 1
```
### 输出
```
YES
1 
```

## 样例 #4
### 输入
```
9 4
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先构造一个和最小的满足部分条件的数列（通常是首项为 1、公差为 1 的等差数列），然后判断这个数列的和是否超过 n，若超过则无解。对于和小于等于 n 的情况，不同题解采用不同的调整方法，将剩余的数值合理分配到数列中，使数列满足所有条件。

各题解的主要区别在于调整数列的具体策略和处理特殊情况的方式。有的题解采用从后往前暴力加后缀的方法，有的题解通过特判特殊情况来保证数列的合法性，还有的题解通过枚举首项和二分查找合适的数值来构造数列。

### 所选题解
- **chsyao（5 星）**：
    - **关键亮点**：思路清晰，先构造最小和的等差数列，然后通过计算差值进行合理分配，复杂度低，代码简洁易懂。
- **momo5440（4 星）**：
    - **关键亮点**：详细证明了一些关键结论，如任意公差为 1 的数列相邻两项加 1 仍满足条件，对特殊情况进行了细致的特判。
- **Rainy_chen（4 星）**：
    - **关键亮点**：提供了官方和非官方两种做法，对每种做法的思路和原理进行了详细解释，分析了数列合法性和无解情况的原因。

### 重点代码及核心实现思想
#### chsyao 的代码
```cpp
#include <algorithm>
#include <cstdio>

using namespace std ;

typedef long long LL ;
const int N=2e5+10 ;

int a[N] ;
int n , k ;
LL sum ;

int main ()
{
	int i ;
	scanf("%d%d",&n,&k);
	for ( i=1 ; i<=k ; i++ ) a[i]=i,sum+=(LL)i;
	if ( sum>n ) return puts("NO")*0;
	LL d=(n-sum)/k , l=n-sum-d*k;
	while ( l )
	{
		for ( i=k ; l && i>=1 ; i-- ) 
			if ( a[i]+d+1<=2*(a[i-1]+d) ) a[i]++,l--;
		if ( l && a[k]+d+1>2*(a[k-1]+d) ) return puts("NO")*0;
	}
	puts("YES");
	for ( i=1 ; i<=k ; i++ ) printf("%lld ",a[i]+d);
	return 0 ;
}
```
**核心实现思想**：先构造首项为 1、公差为 1 的等差数列，计算其和 sum。若 sum 大于 n 则无解；否则计算差值 n - sum，将其平均分配到数列的每一项，再处理剩余的数值，从后往前依次尝试给数列的后缀加 1，直到剩余数值为 0 或无法继续加为止。

#### momo5440 的代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll a[maxn],n,k,t,l;
int main(){
	cin>>n>>k;
	if (k*(k+1)/2>n){
		cout<<"NO"<<endl;
		return 0;
	}
	if (n==k*(k+1)/2+k-1){
		if (k==1){
			cout<<"YES"<<endl;
			cout<<'1'<<endl;
			return 0;
		}
		if (k==2){
			cout<<"NO"<<endl;
			return 0;
		}
		if (k==3){
			cout<<"NO"<<endl;
			return 0;
		}
		cout<<"YES"<<endl;
		cout<<'1'<<' '<<'2'<<' ';
		for (int i=3;i<=k;i++){
			if (i==k){
				cout<<i+2<<' ';
				return 0;
			}
			cout<<i+1<<' ';
		}
		return 0;
	}
	cout<<"YES"<<endl;
	ll sum=k*(k+1)/2;
	t=(n-sum)/k,l=(n-sum)%k;
	int tp=k;
	for (int i=1;i<=l;i++){
		a[tp]++;
		tp--;
	}
	for (int i=1;i<=k;i++){
		cout<<a[i]+i+t<<' ';
	}
}
```
**核心实现思想**：同样先判断最小和的等差数列的和是否超过 n，若超过则无解。对于特殊情况 n == k * (k + 1) / 2 + k - 1 进行特判，分别处理不同 k 值的情况。对于一般情况，将差值平均分配到数列的每一项，再将剩余的数值从后往前依次加到数列的项上。

#### Rainy_chen 的非官方做法代码
```cpp
// 先将 a_i 赋值为 i
for (int i = 1; i <= k; i++) {
    a[i] = i;
    nn -= i;
}
if (nn < 0) {
    puts("NO");
    return 0;
}
// 给每个 a_i 分配 floor(nn / k)
int d = nn / k;
for (int i = 1; i <= k; i++) {
    a[i] += d;
}
nn %= k;
// 从后往前枚举，在满足要求的情况下给每个数分配上尽量多的值
while (nn) {
    for (int i = k; i >= 1 && nn; i--) {
        if (a[i] + 1 <= 2 * a[i - 1]) {
            a[i]++;
            nn--;
        }
    }
    if (nn) {
        puts("NO");
        return 0;
    }
}
puts("YES");
for (int i = 1; i <= k; i++) {
    printf("%d ", a[i]);
}
```
**核心实现思想**：先构造首项为 1、公差为 1 的等差数列，计算剩余数值 nn。将 nn 平均分配到数列的每一项，再处理剩余的数值，从后往前依次尝试给数列的项加 1，直到剩余数值为 0 或无法继续加为止。

### 最优关键思路或技巧
- 先构造和最小的满足部分条件的数列（首项为 1、公差为 1 的等差数列），通过比较其和与 n 的大小判断是否有解。
- 对于剩余的数值，采用合理的分配策略，如平均分配到每一项，再从后往前依次调整，保证数列满足所有条件。
- 对特殊情况进行特判，避免出现不合法的数列。

### 可拓展之处
同类型的构造题通常需要根据题目给定的条件，先找到一个基础的构造方案，然后通过调整和优化来满足所有要求。类似的算法套路包括先确定一个初始状态，再根据规则进行逐步调整，在调整过程中注意合法性和边界条件的判断。

### 推荐洛谷题目
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
- P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录与总结
- **NOI_O2**：刚开始企图用公式直接确定第一个数，然后找序列，但发现很难保证正确性。总结：对于此类构造题，直接用公式确定所有值可能比较困难，需要结合具体情况进行逐步调整和判断。
- **Yuno**：有一个比较显然但是不会严谨证明的结论：当 $S_{min}\leq n \leq S_{max}$ 时，一定有解。总结：在解题过程中，有时候可以先根据直觉得到一些结论，再尝试进行证明或验证，有助于开拓思路。

---
处理用时：70.63秒