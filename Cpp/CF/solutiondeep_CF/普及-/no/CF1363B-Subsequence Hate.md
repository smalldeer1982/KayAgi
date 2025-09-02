# 题目信息

# Subsequence Hate

## 题目描述

Shubham has a binary string $ s $ . A binary string is a string containing only characters "0" and "1".

He can perform the following operation on the string any amount of times:

- Select an index of the string, and flip the character at that index. This means, if the character was "0", it becomes "1", and vice versa.

A string is called good if it does not contain "010" or "101" as a subsequence — for instance, "1001" contains "101" as a subsequence, hence it is not a good string, while "1000" doesn't contain neither "010" nor "101" as subsequences, so it is a good string.

What is the minimum number of operations he will have to perform, so that the string becomes good? It can be shown that with these operations we can make any string good.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In test cases $ 1 $ , $ 2 $ , $ 5 $ , $ 6 $ no operations are required since they are already good strings.

For the $ 3 $ rd test case: "001" can be achieved by flipping the first character — and is one of the possible ways to get a good string.

For the $ 4 $ th test case: "000" can be achieved by flipping the second character — and is one of the possible ways to get a good string.

For the $ 7 $ th test case: "000000" can be achieved by flipping the third and fourth characters — and is one of the possible ways to get a good string.

## 样例 #1

### 输入

```
7
001
100
101
010
0
1
001100```

### 输出

```
0
0
1
1
0
0
2```

# AI分析结果

### 题目内容
# 子序列厌恶

## 题目描述
舒巴姆（Shubham）有一个二进制字符串 $s$ 。二进制字符串是仅包含字符“0”和“1”的字符串。

他可以对该字符串执行以下操作任意次数：
- 选择字符串的一个索引，并翻转该索引处的字符。这意味着，如果该字符是“0”，则变为“1”，反之亦然。

如果一个字符串不包含“010”或“101”作为子序列，则称该字符串为好字符串。例如，“1001”包含“101”作为子序列，因此它不是好字符串，而“1000”既不包含“010”也不包含“101”作为子序列，所以它是好字符串。

他最少需要执行多少次操作，才能使字符串变为好字符串？可以证明，通过这些操作我们可以使任何字符串变好。

字符串 $a$ 是字符串 $b$ 的子序列，如果 $a$ 可以通过删除 $b$ 中的几个（可能为零个或全部）字符得到。

## 说明/提示
在测试用例 $1$、$2$、$5$、$6$ 中，不需要任何操作，因为它们已经是好字符串。

对于第 $3$ 个测试用例：“001”可以通过翻转第一个字符得到，这是得到好字符串的一种可能方法。

对于第 $4$ 个测试用例：“000”可以通过翻转第二个字符得到，这是得到好字符串的一种可能方法。

对于第 $7$ 个测试用例：“000000”可以通过翻转第三个和第四个字符得到，这是得到好字符串的一种可能方法。

## 样例 #1
### 输入
```
7
001
100
101
010
0
1
001100```
### 输出
```
0
0
1
1
0
0
2```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于一个性质：好字符串最终形态为全 0、全 1 或者一边是 0 另一边是 1 。围绕这个性质，不同题解采用了不同方式来求解最小操作次数。主要区别在于实现细节和数据处理方式，有的通过维护 0 和 1 的数量动态更新最小值，有的利用前缀和、后缀和来枚举分割点计算操作次数。

### 所选的题解
- **作者：fengqiao17 (5星)**
    - **关键亮点**：思路清晰简洁，直接维护 0 和 1 的个数，在遍历字符串过程中动态更新最小操作次数，代码实现精炼。
    - **重点代码核心思想**：先统计字符串中 0 和 1 的初始个数，然后遍历字符串，每次改变当前字符并更新 0 和 1 的个数，同时取当前 0 和 1 个数的最小值与当前最小操作次数比较并更新。
    - **核心代码片段**：
```cpp
int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    int cnt0 = 0, cnt1 = 0;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '0') {
        cnt0++;
      } else {
        cnt1++;
      }
    }
    int mini = 1e9;
    for (int i = 0; i < s.size(); i++) {
      mini = min(mini, min(cnt0, cnt1));
      if (s[i] == '0') {
        cnt0--, cnt1++;
      } else {
        cnt1--, cnt0++;
      }
    }
    cout << mini << '\n';
  }
  return 0;
}
```
- **作者：SpeedStar (5星)**
    - **关键亮点**：与 fengqiao17 思路类似，代码风格简洁，利用宏定义简化循环书写，逻辑清晰明了。
    - **重点代码核心思想**：同 fengqiao17，先统计 0 和 1 个数，遍历更新 0 和 1 个数并取最小值更新最小操作次数。
    - **核心代码片段**：
```cpp
#include <iostream>

#define rep(i, n) for (int i = 0; i < n; ++i)

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		string s;
		cin >> s;
		int n = s.size();
		int c0 = 0, c1 = 0;
		
		rep(i, n) (s[i] == '0'? c0 : c1)++;
		
		int res = 1e9;
		rep(i, n) {
			res = min(res, min(c0, c1));
			if (s[i] == '0') --c0, ++c1;
			else --c1, ++c0;
		}
		
		cout << res << '\n';
	}
	
	return 0;
}
```
- **作者：Edmundino (4星)**
    - **关键亮点**：分析清晰，先分别计算全部改成 0 和全部改成 1 的情况，再通过前缀和数组来枚举分割点，计算不同分割情况下的操作次数并取最小值。
    - **重点代码核心思想**：利用前缀和数组记录 0 和 1 的个数，遍历枚举分割点，计算分割点前后不同字符转换所需操作次数并取最小值。
    - **核心代码片段**：
```cpp
for(int i=1;i<lon;i++)
{
	 sw[i]=sw[i-1],sx[i]=sx[i-1];
	 if(a[i]=='0')sa++,sw[i]++;
	 else sd++,sx[i]++;
}
for(int i=0;i<lon;i++)
{
	s=min(sx[i]+sa-sw[i],s);
	s=min(sw[i]+sd-sx[i],s);
}
```

### 最优关键思路或技巧
最优思路是利用贪心策略，基于好字符串最终形态的性质，通过维护 0 和 1 的数量，在遍历字符串过程中动态更新最小操作次数，避免了复杂的计算。

### 可拓展之处
此类题目属于字符串操作与优化问题，类似套路是先分析目标字符串的性质，再通过维护相关数据（如字符数量、前缀和等）来贪心求解最小操作次数。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)

### 个人心得摘录与总结
无个人心得相关内容。 

---
处理用时：55.36秒