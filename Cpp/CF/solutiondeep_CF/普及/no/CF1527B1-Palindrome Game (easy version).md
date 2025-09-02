# 题目信息

# Palindrome Game (easy version)

## 题目描述

The only difference between the easy and hard versions is that the given string $ s $ in the easy version is initially a palindrome, this condition is not always true for the hard version.

A palindrome is a string that reads the same left to right and right to left. For example, "101101" is a palindrome, while "0101" is not.

Alice and Bob are playing a game on a string $ s $ (which is initially a palindrome in this version) of length $ n $ consisting of the characters '0' and '1'. Both players take alternate turns with Alice going first.

In each turn, the player can perform one of the following operations:

1. Choose any $ i $ ( $ 1 \le i \le n $ ), where $ s[i] = $ '0' and change $ s[i] $ to '1'. Pay 1 dollar.
2. Reverse the whole string, pay 0 dollars. This operation is only allowed if the string is currently not a palindrome, and the last operation was not reverse. That is, if Alice reverses the string, then Bob can't reverse in the next move, and vice versa.

Reversing a string means reordering its letters from the last to the first. For example, "01001" becomes "10010" after reversing.

The game ends when every character of string becomes '1'. The player who spends minimum dollars till this point wins the game and it is a draw if both spend equal dollars. If both players play optimally, output whether Alice wins, Bob wins, or if it is a draw.

## 说明/提示

In the first test case of the example,

- in the $ 1 $ -st move Alice has to perform the $ 1 $ -st operation, since the string is currently a palindrome.
- in the $ 2 $ -nd move Bob reverses the string.
- in the $ 3 $ -rd move Alice again has to perform the $ 1 $ -st operation. All characters of the string are '1', game over.

 Alice spends $ 2 $ dollars while Bob spends $ 0 $ dollars. Hence, Bob always wins.

## 样例 #1

### 输入

```
2
4
1001
1
0```

### 输出

```
BOB
BOB```

# AI分析结果

### 题目内容重写

**题目名称：回文游戏（简单版）**

**题目描述：**

简单版和困难版的唯一区别在于，简单版中给定的字符串 $s$ 最初是一个回文串，而困难版中这一条件并不总是成立。

回文串是指从左到右和从右到左读都相同的字符串。例如，"101101" 是回文串，而 "0101" 不是。

Alice 和 Bob 在一个由字符 '0' 和 '1' 组成的长度为 $n$ 的字符串 $s$（在简单版中，$s$ 最初是一个回文串）上玩游戏。两人轮流操作，Alice 先手。

在每次操作中，玩家可以执行以下两种操作之一：

1. 选择任意 $i$（$1 \le i \le n$），其中 $s[i] = $ '0'，并将 $s[i]$ 改为 '1'。支付 1 美元。
2. 反转整个字符串，支付 0 美元。此操作仅在字符串当前不是回文串且上一次操作不是反转时允许。即，如果 Alice 反转了字符串，则 Bob 在下一回合不能反转，反之亦然。

反转字符串意味着将其字符从最后一个到第一个重新排列。例如，"01001" 反转后变为 "10010"。

游戏在字符串的每个字符都变为 '1' 时结束。花费最少美元的玩家获胜，如果双方花费相同则为平局。如果双方都采取最优策略，输出 Alice 获胜、Bob 获胜或平局。

**说明/提示：**

在第一个测试用例中，

- 在第 1 步，Alice 必须执行第 1 种操作，因为字符串当前是回文串。
- 在第 2 步，Bob 反转字符串。
- 在第 3 步，Alice 再次执行第 1 种操作。字符串的所有字符都变为 '1'，游戏结束。

Alice 花费了 2 美元，而 Bob 花费了 0 美元。因此，Bob 总是获胜。

**样例 #1**

**输入：**

```
2
4
1001
1
0
```

**输出：**

```
BOB
BOB
```

### 算法分类

**博弈论**

### 题解分析与结论

1. **核心思路**：所有题解都围绕字符串中 '0' 的个数进行讨论，特别是其奇偶性。通过分析 '0' 的个数，可以确定 Alice 和 Bob 的胜负关系。
2. **难点对比**：大多数题解都正确地识别了 '0' 的个数为奇数和偶数时的不同策略，但部分题解在细节处理上不够清晰，尤其是在处理奇数个 '0' 时的情况。
3. **最优思路**：当 '0' 的个数为偶数时，Bob 可以通过对称操作获胜；当 '0' 的个数为奇数且大于 1 时，Alice 可以通过修改中间的 '0' 来获得优势；当只有一个 '0' 时，Bob 必胜。

### 高星题解推荐

#### 题解1：作者：Aw顿顿 (赞：21)

**星级：★★★★★**

**关键亮点**：
- 清晰地分析了 '0' 的个数为奇数和偶数时的不同策略。
- 通过举例说明了 Alice 和 Bob 的操作过程，使得思路更加直观。

**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,t,cnt,j,al;
string a;
int main()
{
	cin>>t;
	for(j=1; j<=t; j++)
	{
		cnt=0;
		cin>>al>>a;
		for(i=0; i<al; i++)
			if(a[i]=='0')
				cnt++;
		if(cnt==0)
			cout<<"draw"<<endl;
		else if(cnt%2==0||cnt==1)
			cout<<"BOB"<<endl;
		else
			cout<<"ALICE"<<endl;
	}
}
```

#### 题解2：作者：灵茶山艾府 (赞：10)

**星级：★★★★☆**

**关键亮点**：
- 通过博弈论的套路，简洁地总结了 '0' 的个数为奇数和偶数时的胜负关系。
- 代码实现简洁，逻辑清晰。

**代码实现**：
```go
package main
import("bufio";."fmt";."os";."strings")

func main() {
	in := bufio.NewReader(Stdin)
	var T, n int
	var s string
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n, &s)
		c := Count(s, "0")
		if c&1 > 0 && c > 1 {
			Println("ALICE")
		} else {
			Println("BOB")
		}
	}
}
```

#### 题解3：作者：Ryan_Yu (赞：4)

**星级：★★★★☆**

**关键亮点**：
- 通过具体的例子详细说明了 Alice 和 Bob 的操作过程，使得读者更容易理解。
- 总结了不同情况下的胜负关系，逻辑清晰。

**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,t,cnt,j,al;
string a;
int main()
{
	cin>>t;
	for(j=1; j<=t; j++)
	{
		cnt=0;
		cin>>al>>a;
		for(i=0; i<al; i++)
			if(a[i]=='0')
				cnt++;
		if(cnt==0)
			cout<<"draw"<<endl;
		else if(cnt%2==0||cnt==1)
			cout<<"BOB"<<endl;
		else
			cout<<"ALICE"<<endl;
	}
}
```

### 最优关键思路

1. **奇偶性分析**：通过分析 '0' 的个数的奇偶性，可以快速确定 Alice 和 Bob 的胜负关系。
2. **对称操作**：当 '0' 的个数为偶数时，Bob 可以通过对称操作确保自己获胜。
3. **中间策略**：当 '0' 的个数为奇数且大于 1 时，Alice 可以通过修改中间的 '0' 来获得优势。

### 可拓展之处

1. **类似题目**：可以扩展到非回文串的情况，分析 Alice 和 Bob 的策略。
2. **博弈论应用**：可以进一步研究博弈论中的其他策略，如 Nim 游戏等。

### 推荐题目

1. **洛谷 P1002 过河卒**：考察博弈论中的策略分析。
2. **洛谷 P1003 铺地毯**：考察博弈论中的最优策略。
3. **洛谷 P1004 方格取数**：考察博弈论中的双人博弈策略。

---
处理用时：43.04秒