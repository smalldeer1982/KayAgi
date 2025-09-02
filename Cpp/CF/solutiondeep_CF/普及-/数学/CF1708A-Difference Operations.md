# 题目信息

# Difference Operations

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers.

You are allowed to perform this operation any number of times (possibly, zero):

- choose an index $ i $ ( $ 2 \le i \le n $ ), and change $ a_i $ to $ a_i - a_{i-1} $ .

Is it possible to make $ a_i=0 $ for all $ 2\le i\le n $ ?

## 说明/提示

In the first test case, the initial array is $ [5,10] $ . You can perform $ 2 $ operations to reach the goal:

1. Choose $ i=2 $ , and the array becomes $ [5,5] $ .
2. Choose $ i=2 $ , and the array becomes $ [5,0] $ .

In the second test case, the initial array is $ [1,2,3] $ . You can perform $ 4 $ operations to reach the goal:

1. Choose $ i=3 $ , and the array becomes $ [1,2,1] $ .
2. Choose $ i=2 $ , and the array becomes $ [1,1,1] $ .
3. Choose $ i=3 $ , and the array becomes $ [1,1,0] $ .
4. Choose $ i=2 $ , and the array becomes $ [1,0,0] $ .

In the third test case, you can choose indices in the order $ 4 $ , $ 3 $ , $ 2 $ .

## 样例 #1

### 输入

```
4
2
5 10
3
1 2 3
4
1 1 1 1
9
9 9 8 2 4 4 3 5 3```

### 输出

```
YES
YES
YES
NO```

# AI分析结果

### 题目内容重写
# 差分操作

## 题目描述

给定一个由 $n$ 个正整数组成的数组 $a$。

你可以执行以下操作任意次（包括零次）：

- 选择一个下标 $i$（$2 \le i \le n$），并将 $a_i$ 修改为 $a_i - a_{i-1}$。

是否可以通过这些操作使得 $a_i=0$ 对于所有 $2\le i\le n$ 都成立？

## 说明/提示

在第一个测试用例中，初始数组为 $[5,10]$。你可以执行 $2$ 次操作来达到目标：

1. 选择 $i=2$，数组变为 $[5,5]$。
2. 选择 $i=2$，数组变为 $[5,0]$。

在第二个测试用例中，初始数组为 $[1,2,3]$。你可以执行 $4$ 次操作来达到目标：

1. 选择 $i=3$，数组变为 $[1,2,1]$。
2. 选择 $i=2$，数组变为 $[1,1,1]$。
3. 选择 $i=3$，数组变为 $[1,1,0]$。
4. 选择 $i=2$，数组变为 $[1,0,0]$。

在第三个测试用例中，你可以按顺序选择下标 $4$、$3$、$2$。

## 样例 #1

### 输入

```
4
2
5 10
3
1 2 3
4
1 1 1 1
9
9 9 8 2 4 4 3 5 3
```

### 输出

```
YES
YES
YES
NO
```

### 综合分析与结论
该题的核心在于判断是否可以通过多次差分操作将数组中除第一个元素外的所有元素变为0。所有题解都指出，只有当数组中所有元素都是第一个元素的倍数时，才能通过操作达到目标。这一结论可以通过数学归纳法证明，且时间复杂度为 $O(n)$，适用于多组数据。

### 所选高星题解
#### 1. 作者：Dry_ice (5星)
**关键亮点**：思路清晰，代码简洁，时间复杂度为 $O(n)$，适用于多组数据。通过数学归纳法证明了结论的正确性。

**核心代码**：
```cpp
#include <stdio.h>
const int N = 105;
int n, a[N];
int main(void) {
    int t;
    for (scanf("%d", &t); t--; ) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        bool flag = true;
        for (int i = 2; i <= n; ++i)
            if (a[i] % a[1]) flag = false;
        puts (flag ? "YES" : "NO");
    }
    return 0;
}
```

#### 2. 作者：Jeremiahy (4星)
**关键亮点**：代码实现简洁，通过逐个检查元素是否为第一个元素的倍数来判断结果，时间复杂度为 $O(n)$。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a, a1;
bool flag;
signed main() {
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		flag = false;
		cin >> n >> a1;
		for (int i = 2; i <= n; i++) {
			cin >> a;
			if (a % a1 && !flag) {
				flag = true;
				cout << "NO\n";
			}
		}
		if (!flag)
			cout << "YES\n";
	}
	return 0;
}
```

#### 3. 作者：cachejtt (4星)
**关键亮点**：代码简洁，通过逐个检查元素是否为第一个元素的倍数来判断结果，时间复杂度为 $O(n)$。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
int t,n,a[105],flag; 
int main(){
  std::ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    flag=1;
    rep(i,1,n){
      cin>>a[i];
      if(i>1){
        if(a[i]%a[1]!=0)flag=0;
      }  
    }
    if(flag==1)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
  }
  return 0;
}
```

### 最优关键思路或技巧
1. **数学归纳法**：通过归纳法证明所有元素必须是第一个元素的倍数。
2. **时间复杂度优化**：通过逐个检查元素是否为第一个元素的倍数，确保时间复杂度为 $O(n)$。
3. **代码简洁性**：通过使用布尔变量和简洁的条件判断，减少代码复杂度。

### 可拓展之处
1. **类似题目**：可以考察其他类型的差分操作，如累加操作、乘法操作等。
2. **算法套路**：类似的问题可以通过数学归纳法或递推法来解决。

### 推荐相似题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

### 个人心得摘录
- **Dry_ice**：通过数学归纳法证明了结论的正确性，代码简洁且高效。
- **Jeremiahy**：通过逐个检查元素是否为第一个元素的倍数，代码实现简洁。
- **cachejtt**：通过逐个检查元素是否为第一个元素的倍数，代码简洁且高效。

---
处理用时：47.47秒