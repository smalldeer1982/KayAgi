# 题目信息

# Absent Remainder

## 题目描述

You are given a sequence $ a_1, a_2, \dots, a_n $ consisting of $ n $ pairwise distinct positive integers.

Find $ \left\lfloor \frac n 2 \right\rfloor $ different pairs of integers $ x $ and $ y $ such that:

- $ x \neq y $ ;
- $ x $ and $ y $ appear in $ a $ ;
- $ x~mod~y $ doesn't appear in $ a $ .

Note that some $ x $ or $ y $ can belong to multiple pairs.

 $ \lfloor x \rfloor $ denotes the floor function — the largest integer less than or equal to $ x $ . $ x~mod~y $ denotes the remainder from dividing $ x $ by $ y $ .

If there are multiple solutions, print any of them. It can be shown that at least one solution always exists.

## 说明/提示

In the first testcase there are only two pairs: $ (1, 4) $ and $ (4, 1) $ . $ \left\lfloor \frac 2 2 \right\rfloor=1 $ , so we have to find one pair. $ 1~mod~4=1 $ , and $ 1 $ appears in $ a $ , so that pair is invalid. Thus, the only possible answer is a pair $ (4, 1) $ .

In the second testcase, we chose pairs $ 8~mod~2=0 $ and $ 8~mod~4=0 $ . $ 0 $ doesn't appear in $ a $ , so that answer is valid. There are multiple possible answers for that testcase.

In the third testcase, the chosen pairs are $ 9~mod~5=4 $ and $ 7~mod~5=2 $ . Neither $ 4 $ , nor $ 2 $ , appears in $ a $ , so that answer is valid.

## 样例 #1

### 输入

```
4
2
1 4
4
2 8 3 4
5
3 8 5 9 7
6
2 7 5 3 4 8```

### 输出

```
4 1
8 2
8 4
9 5
7 5
8 7
4 3
5 2```

# AI分析结果

### 题目内容
# 缺失的余数

## 题目描述
给定一个由 $n$ 个两两不同的正整数组成的序列 $a_1, a_2, \dots, a_n$ 。

找到 $\left\lfloor \frac{n}{2} \right\rfloor$ 个不同的整数对 $x$ 和 $y$ ，使得：
- $x \neq y$ ；
- $x$ 和 $y$ 出现在 $a$ 中；
- $x \bmod y$ 不出现在 $a$ 中。

注意，某些 $x$ 或 $y$ 可以属于多个数对。

$\lfloor x \rfloor$ 表示向下取整函数 —— 小于或等于 $x$ 的最大整数。$x \bmod y$ 表示 $x$ 除以 $y$ 的余数。

如果有多个解，输出任意一个。可以证明至少总有一个解存在。

## 说明/提示
在第一个测试用例中只有两对：$(1, 4)$ 和 $(4, 1)$ 。$\left\lfloor \frac{2}{2} \right\rfloor = 1$ ，所以我们必须找到一对。$1 \bmod 4 = 1$ ，并且 $1$ 出现在 $a$ 中，所以该数对无效。因此，唯一可能的答案是数对 $(4, 1)$ 。

在第二个测试用例中，我们选择数对 $8 \bmod 2 = 0$ 和 $8 \bmod 4 = 0$ 。$0$ 不出现在 $a$ 中，所以该答案有效。对于该测试用例有多个可能的答案。

在第三个测试用例中，所选的数对是 $9 \bmod 5 = 4$ 和 $7 \bmod 5 = 2$ 。$4$ 和 $2$ 都不出现在 $a$ 中，所以该答案有效。

## 样例 #1
### 输入
```
4
2
1 4
4
2 8 3 4
5
3 8 5 9 7
6
2 7 5 3 4 8
```
### 输出
```
4 1
8 2
8 4
9 5
7 5
8 7
4 3
5 2
```
### 算法分类
构造

### 综合分析与结论
所有题解的核心思路均基于余数性质：$x \bmod y < y$ 。利用此性质，选择序列中的最小数作为 $y$ ，其他数作为 $x$ ，就能构造出满足条件的数对。由于 $n - 1 \geq \left\lfloor \frac{n}{2} \right\rfloor$ ，这样构造出的 $n - 1$ 对数对中选取 $\left\lfloor \frac{n}{2} \right\rfloor$ 对即可满足题目要求。不同题解在具体实现上略有差异，部分通过排序找最小值，部分直接用 `min_element` 找最小值，但整体思路一致。

### 所选的题解
- **作者：Jerrlee✅ (5星)**
    - **关键亮点**：思路清晰简洁，直接利用 `min_element` 找到最小值，代码简洁明了，对时间复杂度分析准确。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>a(n);
        for(int &x:a) cin>>x;
        int mn=*min_element(a.begin(),a.end()); //取最小值
        for(int i=0,k=0;k<n/2;i++) if(a[i]!=mn){
            cout<<a[i]<<' '<<mn<<'\n';
            k++;
        }
    }
}
```
    - **核心实现思想**：先通过 `min_element` 找到数组 `a` 中的最小值 `mn` ，然后遍历数组，将不等于最小值的数与最小值组成数对输出，直到输出 `n/2` 对数对。
- **作者：沉石鱼惊旋 (4星)**
    - **关键亮点**：对思路解释详细，通过具体例子展示过程，便于理解。
    - **重点代码**：
```cpp
void solve()
{
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++) 
	{
		cin>>a[i];
	}
	sort(a,a+n);
	for(int i=0;i<n/2;i++)//n/2组数据即可 
	{
		cout<<a[n-i-1]<<" "<<a[0]<<endl;//分别输出x与y,注意顺序，必须x在前y在后 
	}
}
```
    - **核心实现思想**：先对数组 `a` 排序，使得最小值在 `a[0]` 位置，然后从数组末尾开始取数与 `a[0]` 组成数对输出，共输出 `n/2` 对。
- **作者：AFewSuns (4星)**
    - **关键亮点**：对题目分析详细，明确指出难点及解决方法，对性质证明清晰，代码规范。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200020];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n/2;i++) printf("%d %d\n",a[n-i+1],a[1]);
	}
}
```
    - **核心实现思想**：先对数组 `a` 排序，最小值在 `a[1]` 位置，从数组末尾开始取数与 `a[1]` 组成数对输出，共输出 `n/2` 对。

### 最优关键思路或技巧
利用余数小于除数这一数学性质，巧妙地选择序列中的最小数作为除数 $y$ ，其他数作为被除数 $x$ 来构造满足条件的数对，简化了问题的求解过程。

### 拓展
此类题目属于构造类型，常见套路是挖掘题目中的隐藏性质，利用这些性质来构造符合要求的解。类似题目通常需要对数学概念（如本题中的取模运算）有深入理解，并灵活运用其性质。

### 推荐题目
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学分析，利用等差数列求和公式构造满足条件的连续自然数序列。
 - [P1464 Function](https://www.luogu.com.cn/problem/P1464)：需要根据题目给定的函数性质，构造符合条件的函数值，考查对函数和数学性质的运用。
 - [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：利用二分查找构造满足条件的跳跃距离，与本题一样需要挖掘题目性质来辅助解题。 

---
处理用时：49.56秒