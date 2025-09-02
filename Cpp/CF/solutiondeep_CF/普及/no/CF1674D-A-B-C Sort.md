# 题目信息

# A-B-C Sort

## 题目描述

You are given three arrays $ a $ , $ b $ and $ c $ . Initially, array $ a $ consists of $ n $ elements, arrays $ b $ and $ c $ are empty.

You are performing the following algorithm that consists of two steps:

- Step $ 1 $ : while $ a $ is not empty, you take the last element from $ a $ and move it in the middle of array $ b $ . If $ b $ currently has odd length, you can choose: place the element from $ a $ to the left or to the right of the middle element of $ b $ . As a result, $ a $ becomes empty and $ b $ consists of $ n $ elements.
- Step $ 2 $ : while $ b $ is not empty, you take the middle element from $ b $ and move it to the end of array $ c $ . If $ b $ currently has even length, you can choose which of two middle elements to take. As a result, $ b $ becomes empty and $ c $ now consists of $ n $ elements.

 Refer to the Note section for examples.Can you make array $ c $ sorted in non-decreasing order?

## 说明/提示

In the first test case, we can do the following for $ a = [3, 1, 5, 3] $ :

Step $ 1 $ :

$ a $  $ [3, 1, 5, 3] $  $ \Rightarrow $  $ [3, 1, 5] $  $ \Rightarrow $  $ [3, 1] $  $ \Rightarrow $  $ [3] $  $ \Rightarrow $  $ [] $

$ b $  $ [] $ $ \Rightarrow $ $ [\underline{3}] $ $ \Rightarrow $ $ [3, \underline{5}] $ $ \Rightarrow $ $ [3, \underline{1}, 5] $ $ \Rightarrow $ $ [3, \underline{3}, 1, 5] $
 
Step $ 2 $ :

$ b $  $ [3, 3, \underline{1}, 5] $  $ \Rightarrow $  $ [3, \underline{3}, 5] $  $ \Rightarrow $  $ [\underline{3}, 5] $  $ \Rightarrow $  $ [\underline{5}] $  $ \Rightarrow $  $ [] $

$ c $  $ [] $ $ \Rightarrow $ $ [1] $ $ \Rightarrow $ $ [1, 3] $ $ \Rightarrow $ $ [1, 3, 3] $ $ \Rightarrow $ $ [1, 3, 3, 5] $

As a result, array $ c = [1, 3, 3, 5] $ and it's sorted.

## 样例 #1

### 输入

```
3
4
3 1 5 3
3
3 2 1
1
7331```

### 输出

```
YES
NO
YES```

# AI分析结果

### 题目内容重写

#### A-B-C 排序

**题目描述**

给定三个数组 $a$、$b$ 和 $c$。初始时，数组 $a$ 包含 $n$ 个元素，数组 $b$ 和 $c$ 为空。

你需要执行以下由两个步骤组成的算法：

- **步骤 1**：当 $a$ 不为空时，从 $a$ 的末尾取出一个元素并将其移动到数组 $b$ 的中间。如果 $b$ 当前的长度为奇数，你可以选择将该元素放在 $b$ 中间元素的左侧或右侧。最终，$a$ 变为空，$b$ 包含 $n$ 个元素。
- **步骤 2**：当 $b$ 不为空时，从 $b$ 的中间取出一个元素并将其移动到数组 $c$ 的末尾。如果 $b$ 当前的长度为偶数，你可以选择取中间的两个元素之一。最终，$b$ 变为空，$c$ 包含 $n$ 个元素。

参考“说明/提示”部分中的示例。你能使数组 $c$ 按非递减顺序排序吗？

**说明/提示**

在第一个测试用例中，我们可以对 $a = [3, 1, 5, 3]$ 进行如下操作：

**步骤 1**：

$ a $  $ [3, 1, 5, 3] $  $ \Rightarrow $  $ [3, 1, 5] $  $ \Rightarrow $  $ [3, 1] $  $ \Rightarrow $  $ [3] $  $ \Rightarrow $  $ [] $

$ b $  $ [] $ $ \Rightarrow $ $ [\underline{3}] $ $ \Rightarrow $ $ [3, \underline{5}] $ $ \Rightarrow $ $ [3, \underline{1}, 5] $ $ \Rightarrow $ $ [3, \underline{3}, 1, 5] $
 
**步骤 2**：

$ b $  $ [3, 3, \underline{1}, 5] $  $ \Rightarrow $  $ [3, \underline{3}, 5] $  $ \Rightarrow $  $ [\underline{3}, 5] $  $ \Rightarrow $  $ [\underline{5}] $  $ \Rightarrow $  $ [] $

$ c $  $ [] $ $ \Rightarrow $ $ [1] $ $ \Rightarrow $ $ [1, 3] $ $ \Rightarrow $ $ [1, 3, 3] $ $ \Rightarrow $ $ [1, 3, 3, 5] $

最终，数组 $c = [1, 3, 3, 5]$，并且它是排序好的。

**样例 #1**

**输入**

```
3
4
3 1 5 3
3
3 2 1
1
7331```

**输出**

```
YES
NO
YES```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于通过贪心策略判断是否能够通过给定的操作使数组 $c$ 变为非递减顺序。大多数题解都采用了类似的思路，即通过分组和交换相邻元素来判断是否能够使数组有序。

### 精选题解

#### 1. 作者：include_BM (赞：13)
**星级**：5星  
**关键亮点**：通过比较 $a$ 和 $c$ 数组的末尾两个元素，判断是否能够匹配，思路清晰且代码简洁。

```cpp
n=read(),ok=1;
for(int i=1;i<=n;++i) a[i]=c[i]=read();
sort(c+1,c+n+1);
for(int i=n;i>=2;i-=2)
    ok&=((a[i]==c[i]&&a[i-1]==c[i-1])||(a[i]==c[i-1]&&a[i-1]==c[i]));
ok?puts("YES"):puts("NO");
```

#### 2. 作者：Orange_qwq (赞：11)
**星级**：4星  
**关键亮点**：通过贪心策略将每两个数排序后放入 $c$ 数组，并判断最终数组是否有序，思路清晰且代码易读。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010], n, f;
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = n; i >= (n & 1) + 1; i -= 2)
			if (a[i] < a[i - 1]) swap(a[i], a[i - 1]);
		f = 1;
		for (int i = 1; i < n; ++i)
			if (a[i] > a[i + 1]) f = 0;
		puts(f ? "YES" : "NO");
	}
}
```

#### 3. 作者：Chronomaly_Atlandis (赞：3)
**星级**：4星  
**关键亮点**：通过从后往前遍历 $a$ 和 $c$ 数组的末尾两个元素，判断是否匹配，思路清晰且代码简洁。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,a[maxn],c[maxn],T;
int main(){
	cin.tie(NULL);
	cin >> T;
    while(T--){
    	bool check=1;
    	memset(a,0,sizeof(a));
    	memset(c,0,sizeof(c));
    	cin >> n;
    for(int i=1;i<=n;i++){
    cin >> a[i];
    c[i]=a[i];
}
    sort(c+1,c+n+1);
for(int i=n;i>=2;i-=2)
if(!((a[i]==c[i]&&a[i-1]==c[i-1])||(a[i]==c[i-1]&&a[i-1]==c[i]))){
	check=0;
	break;
}
if(check)cout << "YES\n";
else cout << "NO\n";
}
return 0;
}
```

### 最优关键思路或技巧
1. **分组与交换**：将数组中的元素两两分组，通过交换组内元素使其有序，最终判断整个数组是否有序。
2. **贪心策略**：通过贪心策略，尽可能使每两个元素有序，从而保证整个数组有序。

### 可拓展之处
类似的问题可以通过分组和交换相邻元素来解决，例如某些排序问题或构造问题。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)

### 个人心得摘录
- **include_BM**：通过比较 $a$ 和 $c$ 数组的末尾两个元素，判断是否能够匹配，思路清晰且代码简洁。
- **Orange_qwq**：通过贪心策略将每两个数排序后放入 $c$ 数组，并判断最终数组是否有序，思路清晰且代码易读。

---
处理用时：49.04秒