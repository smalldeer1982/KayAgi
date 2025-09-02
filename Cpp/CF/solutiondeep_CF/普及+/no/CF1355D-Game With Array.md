# 题目信息

# Game With Array

## 题目描述

Petya and Vasya are competing with each other in a new interesting game as they always do.

At the beginning of the game Petya has to come up with an array of $ N $ positive integers. Sum of all elements in his array should be equal to $ S $ . Then Petya has to select an integer $ K $ such that $ 0 \leq K \leq S $ .

In order to win, Vasya has to find a non-empty subarray in Petya's array such that the sum of all selected elements equals to either $ K $ or $ S - K $ . Otherwise Vasya loses.

You are given integers $ N $ and $ S $ . You should determine if Petya can win, considering Vasya plays optimally. If Petya can win, help him to do that.

## 样例 #1

### 输入

```
1 4```

### 输出

```
YES
4
2```

## 样例 #2

### 输入

```
3 4```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 8```

### 输出

```
YES
2 1 5
4```

# AI分析结果

【题目内容（中文重写）】
# 数组游戏

## 题目描述

Petya 和 Vasya 像往常一样在玩一个新的有趣游戏，互相竞争。

游戏开始时，Petya 必须想出一个由 $N$ 个正整数组成的数组。数组中所有元素的和应该等于 $S$。然后 Petya 必须选择一个整数 $K$，使得 $0 \leq K \leq S$。

为了获胜，Vasya 必须在 Petya 的数组中找到一个非空子数组，使得所选元素的和等于 $K$ 或 $S - K$。否则 Vasya 输。

给定整数 $N$ 和 $S$。你应该确定在 Vasya 发挥最优水平的情况下，Petya 是否能获胜。如果 Petya 能获胜，请帮助他实现。

## 样例 #1

### 输入
```
1 4
```

### 输出
```
YES
4
2
```

## 样例 #2

### 输入
```
3 4
```

### 输出
```
NO
```

## 样例 #3

### 输入
```
3 8
```

### 输出
```
YES
2 1 5
4
```

【算法分类】
构造

【综合分析与结论】
这些题解的核心都是围绕构造满足条件的数组来解决问题。主要思路是先判断 $S$ 与 $2N$ 的大小关系，以此确定是否有解，若有解则构造出相应数组。
- **思路对比**：多数题解在 $S \geq 2N$ 时，采用构造前 $n - 1$ 个元素为 $2$，最后一个元素为 $S - 2(n - 1)$ 的数组，取 $K = 1$ 的方法；vigza 题解尝试通过贪心构造 $\{1,1,1,\cdots,S-(n - 1)\}$ 的数组；Zhao_daodao 题解则通过奇偶分析 $S$ 来构造数组。
- **算法要点**：各题解的关键在于找到合适的数组构造方式，使得不存在和为 $K$ 或 $S - K$ 的子数组。部分题解还给出了 $S < 2N$ 时无解的证明。
- **解决难点**：难点在于证明 $S < 2N$ 时无解，以及找到合适的构造方法保证有解时能满足条件。

【所选题解】
- 一扶苏一（5星）：思路清晰，给出了 $S < 2N$ 时无解的详细证明，代码简洁。
- sto_5k_orz（4星）：简洁地给出了分类讨论和构造方法，代码精炼。
- oimaster（4星）：思路明确，对构造方法的解释清晰。

【重点代码】
```cpp
// 一扶苏一的代码
namespace Fusu {
int n, s;
void Main() {
  qr(n); qr(s);
  if ((n << 1) > s) {
    puts("No");
  } else {
    puts("Yes");
    for (int i = 1; i < n; ++i) {
      qw(2, ' ');
      s -= 2;
    }
    qw(s, '\n');
    puts("1");
  }
}
} // namespace Fusu

// sto_5k_orz的代码
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, s; cin >> n >> s; if(s < 2 * n) puts("NO"), exit(0); puts("YES");
	for(int i = 1; i < n; i++) cout << 2 << ' '; cout << s - 2 * n + 2 << endl << 1;
	return 0;
}

// oimaster的代码
#include <iostream>
using namespace std;
int main() {
	int n, s;
	cin >> n >> s;
	if (2 * n <= s) {
		cout << "YES\n";
		for (int i = 0; i < n - 1; i++) {
			cout << 2 << ' ';
			s -= 2;
		}
		cout << s << '\n' << 1;
	} else {
		cout << "NO";
	}
	return 0;
}
```
【核心实现思想】
这些代码的核心思想是先判断 $S$ 与 $2N$ 的大小关系，若 $S < 2N$ 则输出 `NO`；若 $S \geq 2N$，则输出 `YES`，接着输出 $n - 1$ 个 $2$，再输出 $S - 2(n - 1)$，最后输出 $K = 1$。

【关键思路或技巧】
- **分类讨论**：通过判断 $S$ 与 $2N$ 的大小关系来确定是否有解，简化问题。
- **构造特定数组**：在有解的情况下，构造前 $n - 1$ 个元素为 $2$，最后一个元素为 $S - 2(n - 1)$ 的数组，取 $K = 1$，可保证不存在和为 $K$ 或 $S - K$ 的子数组。

【拓展思路】
同类型题可能会有不同的构造要求和限制条件，解题关键在于分析题目特点，找到合适的构造方法。类似的构造题可能会涉及到图形构造、序列构造等，解题时需要灵活运用数学知识和逻辑推理。

【推荐题目】
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径构造问题。
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：需要构造合法的出栈序列。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：可通过构造路径来求解最大和。

【个人心得】
- Zhao_daodao：提到自己没想到其他题解的做法，采用了奇偶分析的方法，说明解题时可以从不同角度思考问题。 

---
处理用时：39.30秒