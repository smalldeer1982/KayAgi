# 题目信息

# And

## 题目描述

There is an array with $ n $ elements $ a_{1},a_{2},...,a_{n} $ and the number $ x $ .

In one operation you can select some $ i $ ( $ 1<=i<=n $ ) and replace element $ a_{i} $ with $ a_{i}&x $ , where $ & $ denotes the [bitwise and](https://en.wikipedia.org/wiki/Bitwise_operation#AND) operation.

You want the array to have at least two equal elements after applying some operations (possibly, none). In other words, there should be at least two distinct indices $ i≠j $ such that $ a_{i}=a_{j} $ . Determine whether it is possible to achieve and, if possible, the minimal number of operations to apply.

## 说明/提示

In the first example one can apply the operation to the last element of the array. That replaces 7 with 3, so we achieve the goal in one move.

In the second example the array already has two equal elements.

In the third example applying the operation won't change the array at all, so it is impossible to make some pair of elements equal.

## 样例 #1

### 输入

```
4 3
1 2 3 7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 228
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 7
1 2 3
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写

有一个包含 $n$ 个元素的数组 $a_{1},a_{2},...,a_{n}$ 和一个数 $x$。

在一次操作中，你可以选择某个 $i$（$1<=i<=n$）并将元素 $a_{i}$ 替换为 $a_{i} \& x$，其中 $\&$ 表示按位与操作。

你希望在应用一些操作（可能不操作）后，数组中至少有两个相等的元素。换句话说，应该存在至少两个不同的索引 $i≠j$ 使得 $a_{i}=a_{j}$。确定是否可以实现这一目标，如果可能，输出应用的最小操作次数。

### 算法分类
位运算

### 题解分析与结论

所有题解的核心思路都是利用按位与操作的性质，即 $a \& x = a \& x \& x \& \dots \& x$，这意味着对一个数多次进行按位与操作不会改变结果。因此，答案只可能是 $-1$、$0$、$1$ 或 $2$。

大多数题解通过使用桶（数组）来记录原始数组和按位与操作后的数组中的元素，然后根据桶中的情况判断最小操作次数。具体来说：

1. **答案 $0$**：原始数组中已经存在两个相同的元素。
2. **答案 $1$**：存在一个元素，其按位与操作后的结果等于另一个元素。
3. **答案 $2$**：存在两个元素，它们的按位与操作后的结果相同。
4. **答案 $-1$**：以上情况均不满足。

### 评分较高的题解

#### 题解作者：Surge_of_Force (评分：5星)
**关键亮点**：
- 思路清晰，代码简洁，直接通过两个桶来记录原始数组和按位与操作后的数组中的元素。
- 优化了判断逻辑，遇到答案为 $0$ 时直接输出，减少了不必要的计算。

**核心代码**：
```cpp
int tong1[100010],tong2[100010];
int main()
{
	int n=read(),x=read(),ans=3;
	for(int i=1;i<=n;i++)
	{
		int a=read();
		if(tong1[a])
		{
			cout<<0;
			return 0;
		}
		if(tong2[a]||tong1[a&x]) ans=min(ans,1);
		if(tong2[a&x]) ans=min(ans,2);
		tong1[a]=tong2[a&x]=1;
	}
	cout<<(ans==3?-1:ans);
	return 0;
}
```

#### 题解作者：peppaking8 (评分：4星)
**关键亮点**：
- 详细解释了按位与操作的性质，并给出了清晰的分类讨论。
- 代码结构清晰，逻辑严谨，易于理解。

**核心代码**：
```cpp
int n,x;
int a[N],b[N];
int t[N];
int main(){
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		t[a[i]]++;
		if(t[a[i]]>=2){
			printf("0\n");
			exit(0);
		}
	}
	for(int i=1;i<=n;i++){
		b[i]=a[i]&x;
		if(t[b[i]]&&b[i]!=a[i]){
			printf("1\n");
			exit(0);
		}
	}
	memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++){
		t[b[i]]++;
		if(t[b[i]]>=2){
			printf("2\n");
			exit(0);
		}
	}
	printf("-1\n");
	exit(0);
}
```

#### 题解作者：Cappuccino_mjj (评分：4星)
**关键亮点**：
- 通过找规律得出答案只可能是 $-1$、$0$、$1$ 或 $2$，并给出了详细的分类讨论。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
int n,x;
const int N=5e5+10;
int a[N],b[N],c[N],d[N];
int main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(b[a[i]]>1)
		{
			cout<<0;
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		c[i]=a[i]&x;
		d[c[i]]++;
		if(b[c[i]]&&c[i]!=a[i])
		{
			cout<<1;
			return 0;
		}
	}
	for(int i=1;i<=500005;i++)
	{
		if(d[c[i]]>1)
		{
			cout<<2;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

### 最优关键思路或技巧
- **按位与操作的性质**：利用 $a \& x = a \& x \& x \& \dots \& x$ 的性质，避免重复计算。
- **桶的使用**：通过桶记录原始数组和按位与操作后的数组中的元素，快速判断是否存在重复元素。

### 可拓展之处
- 类似的问题可以扩展到其他位运算操作，如按位或、按位异或等。
- 可以结合其他数据结构（如哈希表）来进一步优化查找效率。

### 推荐题目
1. [P1013 进制位](https://www.luogu.com.cn/problem/P1013)
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)

### 个人心得摘录
- **Surge_of_Force**：通过优化判断逻辑，减少了不必要的计算，提高了代码效率。
- **peppaking8**：详细解释了按位与操作的性质，并给出了清晰的分类讨论，有助于理解问题本质。

---
处理用时：48.22秒