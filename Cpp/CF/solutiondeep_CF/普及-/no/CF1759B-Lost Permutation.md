# 题目信息

# Lost Permutation

## 题目描述

A sequence of $ n $ numbers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

Polycarp lost his favorite permutation and found only some of its elements — the numbers $ b_1, b_2, \dots b_m $ . He is sure that the sum of the lost elements equals $ s $ .

Determine whether one or more numbers can be appended to the given sequence $ b_1, b_2, \dots b_m $ such that the sum of the added numbers equals $ s $ , and the resulting new array is a permutation?

## 说明/提示

In the test case of the example, $ m=3, s=13, b=[3,1,4] $ . You can append to $ b $ the numbers $ 6,2,5 $ , the sum of which is $ 6+2+5=13 $ . Note that the final array will become $ [3,1,4,6,2,5] $ , which is a permutation.

In the second test case of the example, $ m=1, s=1, b=[1] $ . You cannot append one or more numbers to $ [1] $ such that their sum equals $ 1 $ and the result is a permutation.

In the third test case of the example, $ m=3, s=3, b=[1,4,2] $ . You can append the number $ 3 $ to $ b $ . Note that the resulting array will be $ [1,4,2,3] $ , which is a permutation.

## 样例 #1

### 输入

```
5
3 13
3 1 4
1 1
1
3 3
1 4 2
2 1
4 3
5 6
1 2 3 4 5```

### 输出

```
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容
# 丢失的排列

## 题目描述
一个由 $n$ 个数组成的序列如果恰好包含从 $1$ 到 $n$ 的所有整数各一次，则称其为一个排列。例如，序列 \[ 3, 1, 4, 2 \]、\[ 1 \] 和 \[ 2,1 \] 是排列，但 \[ 1,2,1 \]、\[ 0,1 \] 和 \[ 1,3,4 \] 不是。

Polycarp 丢失了他最喜欢的排列，只找到了其中的一些元素 —— 数字 $b_1, b_2, \dots b_m$ 。他确定丢失元素的和为 $s$ 。

判断是否可以在给定序列 $b_1, b_2, \dots b_m$ 后追加一个或多个数字，使得追加数字的和等于 $s$ ，并且得到的新数组是一个排列？

## 说明/提示
在示例的测试用例中，$m = 3$，$s = 13$，$b = [3,1,4]$ 。你可以在 $b$ 后追加数字 $6,2,5$ ，它们的和为 $6 + 2 + 5 = 13$ 。注意最终数组将变为 $[3,1,4,6,2,5]$ ，这是一个排列。

在示例的第二个测试用例中，$m = 1$，$s = 1$，$b = [1]$ 。你不能在 $[1]$ 后追加一个或多个数字，使得它们的和等于 $1$ 且结果是一个排列。

在示例的第三个测试用例中，$m = 3$，$s = 3$，$b = [1,4,2]$ 。你可以在 $b$ 后追加数字 $3$ 。注意得到的数组将是 $[1,4,2,3]$ ，这是一个排列。

## 样例 #1
### 输入
```
5
3 13
3 1 4
1 1
1
3 3
1 4 2
2 1
4 3
5 6
1 2 3 4 5
```
### 输出
```
YES
NO
YES
NO
YES
```
### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕判断能否通过补充数字使给定序列成为排列且补充数字和为 $s$ 。大部分题解先找出给定序列 $b$ 中的最大值 $mx$ ，确保 $1$ 到 $mx$ 之间缺失的数字都被考虑，计算其和并与 $s$ 比较。若小于 $s$ ，则从 $mx + 1$ 开始按顺序累加数字，看是否能使总和等于 $s$ 。不同之处在于实现细节和代码风格，比如有的使用数组标记已出现数字，有的用 `map` ；有的通过循环逐步判断，有的利用等差数列求和公式先计算理论总和再判断。

### 所选的题解
 - **作者：zajasi (4星)**
    - **关键亮点**：思路清晰，利用等差数列求和公式先算出最小总和，再通过循环调整长度判断能否达到目标和 $s$ ，代码简洁高效。
    - **重点代码核心实现思想**：先计算 $b$ 序列中数的和 $s$ 与最大值 $ma$ ，得到以 $ma$ 为最大数的排列的最小总和 $z$ ，算出与已有和的差值 $zz$ ，判断 $zz$ 与 $s$ 的关系，通过循环增加总和看是否能等于 $s$ 。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,m;
int x;
int s,ma;
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		s=ma=0;
		for(int i=1;i<=n;i++){
			cin>>x;
			s+=x;
			ma=max(ma,x);
		}
		int z=(ma+1)*ma/2;
		int zz=z-s;
		if(zz>m){
			cout<<"NO\n";
			continue;
		}
		int f=0;
		int c=ma;
		while(zz<=m){
			if(zz==m){
				f=1;
				cout<<"YES\n";
				break;
			}
			zz+=++c;
		}
		if(f==0)cout<<"NO\n";
	}
	return 0;
}
```
 - **作者：sw2022 (4星)**
    - **关键亮点**：代码简洁明了，直接从 $1$ 开始枚举缺少的元素并加入序列，在和大于等于 $s$ 时直接判断是否构成排列。
    - **重点代码核心实现思想**：用数组 `f` 标记已出现数字，先读入数据并标记，同时记录最大值 `mx` ，从 $1$ 开始枚举，若数字未出现则加入总和 `s` 并标记，最后根据 `s` 是否为 $0$ 且元素个数是否足够判断结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
bool f[101];
int main()
{
	int t,m,mx,s,c,b,i;
	cin>>t;
	while(t--)
	{
		memset(f,false,sizeof(f));
		cin>>m>>s;mx=0,c=0;
		for(i=1;i<=m;i++)
		{
			cin>>b,f[b]=true;
			c++,mx=max(mx,b);
		}
		for(i=1;i<=100&&s>0;i++)
		if(!f[i]) f[i]=true,s-=i,c++;
		printf(s||c<mx?"NO\n":"YES\n");
	}
	return 0;
}
```
 - **作者：隐仞Mrsu (4星)**
    - **关键亮点**：分析过程详细，分情况逐步判断，逻辑严谨，先计算 $1$ 到 $mx$ 缺失数字和，再根据与 $s$ 的大小关系进一步处理。
    - **重点代码核心实现思想**：用布尔数组 `b` 标记已出现数字，读入数据同时记录最大值 `mx` ，计算 $1$ 到 `mx` 缺失数字和 `sum` ，根据 `sum` 与 `s` 的大小关系，或直接判断结果，或继续从 `mx + 1` 累加判断。
```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int N = 1e6+5;
LL _,n,s,sr;
bool b[N];
void work(){
	for(LL i=1;i<=100;i++)b[i]=0;//清空数组
	cin>>n>>s;
	LL mx=0;
	for(LL i=1;i<=n;i++){
		cin>>sr;
		b[sr]=1;
		mx=max(mx,sr);
	}
	LL sum=0;
	for(LL i=1;i<=mx;i++){
		if(!b[i])sum+=i;
	}
	if(sum==s){
		cout<<"YES\n";
		return;
	}
	if(sum>s){
		cout<<"NO\n";
		return;
	}
	for(LL i=mx+1;i<=100;i++){
		if(!b[i])sum+=i;
		if(sum==s){
			cout<<"YES\n";
			return;
		}
		if(sum>s){
			cout<<"NO\n";
			return;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
} 
```

### 最优关键思路或技巧
1. **利用等差数列求和公式**：如 `zajasi` 的题解，通过计算以已知最大数为边界的排列最小总和，快速确定初始范围，减少不必要的枚举。
2. **标记法**：多数题解使用数组或 `map` 标记已出现数字，方便判断缺失数字，简化逻辑。

### 拓展
同类型题通常围绕排列组合、数字规律判断等，类似算法套路是先确定必要数字范围，再根据给定条件（如和、数量等）进行调整和判断。

### 推荐题目
1. **P1036 [NOIP2002 普及组] 选数**：通过枚举组合判断是否为质数，与本题枚举补充数字思路类似。
2. **P1157 组合的输出**：考察排列组合的生成与输出，与本题对排列的判断相关。
3. **P1219 [USACO1.5] 八皇后 Checker Challenge**：经典的搜索与判断排列是否符合条件的题目，锻炼逻辑判断能力。 

---
处理用时：65.75秒