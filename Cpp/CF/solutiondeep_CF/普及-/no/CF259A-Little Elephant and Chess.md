# 题目信息

# Little Elephant and Chess

## 题目描述

The Little Elephant loves chess very much.

One day the Little Elephant and his friend decided to play chess. They've got the chess pieces but the board is a problem. They've got an $ 8×8 $ checkered board, each square is painted either black or white. The Little Elephant and his friend know that a proper chessboard doesn't have any side-adjacent cells with the same color and the upper left cell is white. To play chess, they want to make the board they have a proper chessboard. For that the friends can choose any row of the board and cyclically shift the cells of the chosen row, that is, put the last (rightmost) square on the first place in the row and shift the others one position to the right. You can run the described operation multiple times (or not run it at all).

For example, if the first line of the board looks like that "BBBBBBWW" (the white cells of the line are marked with character "W", the black cells are marked with character "B"), then after one cyclic shift it will look like that "WBBBBBBW".

Help the Little Elephant and his friend to find out whether they can use any number of the described operations to turn the board they have into a proper chessboard.

## 说明/提示

In the first sample you should shift the following lines one position to the right: the 3-rd, the 6-th, the 7-th and the 8-th.

In the second sample there is no way you can achieve the goal.

## 样例 #1

### 输入

```
WBWBWBWB
BWBWBWBW
BWBWBWBW
BWBWBWBW
WBWBWBWB
WBWBWBWB
BWBWBWBW
WBWBWBWB
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
WBWBWBWB
WBWBWBWB
BBWBWWWB
BWBWBWBW
BWBWBWBW
BWBWBWWW
BWBWBWBW
BWBWBWBW
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 小象与国际象棋

## 题目描述
小象非常喜欢下国际象棋。
有一天，小象和它的朋友决定下棋。他们有棋子，但棋盘却有问题。他们有一个8×8的方格棋盘，每个方格被涂成黑色或白色。小象和它的朋友知道，一个标准的棋盘没有任何两个相邻的方格颜色相同，并且左上角的方格是白色的。为了下棋，他们想把现有的棋盘变成一个标准棋盘。为此，朋友们可以选择棋盘的任意一行，并循环移动该行的方格，也就是说，把最后（最右边）的方格放在该行的第一个位置，其他方格向右移动一个位置。你可以多次执行上述操作（也可以一次都不执行）。
例如，如果棋盘的第一行是这样的“BBBBBBWW”（该行的白色方格用字符“W”标记，黑色方格用字符“B”标记），那么经过一次循环移动后，它将变成“WBBBBBBW”。
帮助小象和它的朋友找出他们是否可以通过任意次数的上述操作，将现有的棋盘变成一个标准棋盘。

## 说明/提示
在第一个样例中，你应该将以下几行向右移动一个位置：第3行、第6行、第7行和第8行。
在第二个样例中，你无法实现目标。

## 样例 #1
### 输入
```
WBWBWBWB
BWBWBWBW
BWBWBWBW
BWBWBWBW
WBWBWBWB
WBWBWBWB
BWBWBWBW
WBWBWBWB
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
WBWBWBWB
WBWBWBWB
BBWBWWWB
BWBWBWBW
BWBWBWBW
BWBWBWWW
BWBWBWBW
BWBWBWBW
```
### 输出
```
NO
```

### 算法分类
字符串

### 题解综合分析与结论
这几道题解的核心思路都是基于目标棋盘的特性，即每一行只有“WBWBWBWB”和“BWBWBWBW”两种形式，且这两种形式可以通过题目所给的循环移动操作相互转换。所以判断输入棋盘能否变成标准棋盘，只需判断每一行是否为这两种形式之一。
其中LongDouble、ruruo、alex_liu三位作者的题解思路清晰，代码简洁，直接判断每一行是否符合要求，质量较高。hensier的第一种方法使用队列模拟移动过程，虽然逻辑正确但代码相对复杂，效率也不高；其第二种方法与其他简洁解法思路一致。

### 所选的题解
- **LongDouble的题解**：
  - **星级**：5星
  - **关键亮点**：思路清晰，直接点明目标棋盘每一行的两种固定形式，代码简洁明了，通过一次遍历每一行并判断是否为指定字符串来得出结论。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a[10];

int main()
{
	for (int i = 1; i <= 8; i++)
	{
		cin >> a[i];
		if (a[i]!= "WBWBWBWB" && a[i]!= "BWBWBWBW")
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}
```
  - **核心实现思想**：逐行读取输入的棋盘数据，判断每一行是否为“WBWBWBWB”或“BWBWBWBW”，只要有一行不符合则输出“NO”并结束程序，若所有行都符合则输出“YES”。
- **ruruo的题解**：
  - **星级**：5星
  - **关键亮点**：同样思路简洁，代码实现直接，通过`getline`逐行读取棋盘数据并进行判断，逻辑清晰。
  - **重点代码**：
```cpp
#include<iostream>
using namespace std;

string s; 

int main() {
    for(int i = 1; i <= 8; i++) { 
        getline(cin, s); 
        if(s!= "WBWBWBWB" && s!= "BWBWBWBW") { 
            cout << "NO" << endl; 
            return 0;
        }
    }
    cout << "YES" << endl; 
    return 0;
}
```
  - **核心实现思想**：利用`getline`函数逐行获取棋盘数据，判断每行数据是否符合两种目标形式，不符合则输出“NO”并结束，全部符合则输出“YES”。
- **alex_liu的题解**：
  - **星级**：5星
  - **关键亮点**：思路阐述清晰，代码风格简洁，通过数组存储棋盘各行数据并逐行判断，符合要求则输出“YES”，否则输出“NO”。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a[9];

int main(){
	for(int i=1;i<=8;i++){
		cin>>a[i];
		if(a[i]!="WBWBWBWB"&&a[i]!="BWBWBWBW"){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
```
  - **核心实现思想**：循环读入棋盘的每一行数据，判断每行是否为特定的两种字符串之一，若有不符则输出“NO”并结束程序，全符合则输出“YES”。

### 最优关键思路或技巧
通过观察目标棋盘的特征，总结出每行只有两种固定的字符串形式，从而将复杂的棋盘变换问题简化为对每行字符串的判断问题，极大地简化了代码实现。

### 可拓展思路
此类题目属于字符串判断与简单变换类型，类似套路是通过观察目标状态的特征，找到输入数据与目标状态之间的关键联系，从而简化问题。同类型题可能会改变棋盘大小、变换规则或目标状态的特征等。

### 洛谷相似题目推荐
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串的查找与统计。
- [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：结合数学知识与字符串处理。
- [P2219 黑匣子](https://www.luogu.com.cn/problem/P2219)：综合了数据结构（优先队列）与字符串处理。 

---
处理用时：55.94秒