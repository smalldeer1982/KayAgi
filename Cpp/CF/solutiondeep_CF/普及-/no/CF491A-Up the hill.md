# 题目信息

# Up the hill

## 题目描述

Hiking club "Up the hill" just returned from a walk. Now they are trying to remember which hills they've just walked through.

It is known that there were $ N $ stops, all on different integer heights between $ 1 $ and $ N $ kilometers (inclusive) above the sea level. On the first day they've traveled from the first stop to the second stop, on the second day they've traveled from the second to the third and so on, and on the last day they've traveled from the stop $ N-1 $ to the stop $ N $ and successfully finished their expedition.

They are trying to find out which heights were their stops located at. They have an entry in a travel journal specifying how many days did they travel up the hill, and how many days did they walk down the hill.

Help them by suggesting some possible stop heights satisfying numbers from the travel journal.

## 样例 #1

### 输入

```
0
1
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
2
1```

### 输出

```
1 3 4 2```

# AI分析结果

### 题目内容（中文重写）
# 上山

## 题目描述
“上山”徒步俱乐部刚刚结束一次徒步旅行。现在他们试图回忆刚刚走过了哪些山丘。

已知这次旅行共有 $N$ 个休息站，所有休息站的海拔高度均为 $1$ 到 $N$ 千米（包含 $1$ 和 $N$）之间的不同整数。第一天他们从第一个休息站走到第二个休息站，第二天从第二个走到第三个，依此类推，最后一天从第 $N - 1$ 个休息站走到第 $N$ 个休息站，成功完成了这次探险。

他们试图找出这些休息站所在的海拔高度。他们的旅行日记中有一条记录，说明了他们上山的天数和下山的天数。

请帮助他们，给出一些可能的休息站海拔高度，使其满足旅行日记中的数字。

## 样例 #1

### 输入
```
0
1
```

### 输出
```
2 1 
```

## 样例 #2

### 输入
```
2
1
```

### 输出
```
1 3 4 2
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是根据输入的上山天数 $a$ 和下山天数 $b$，构造出一个满足条件的序列。具体做法是先升序输出前 $a$ 个数，再降序输出从 $a + b + 1$ 到 $a + 1$ 的数。

- **思路**：通过两个循环分别处理上升和下降的部分，保证序列中上升的数有 $a$ 个，下降的数有 $b$ 个。
- **算法要点**：先升序输出前 $a$ 个数，这部分会产生 $a - 1$ 个上升；降序输出从 $a + b + 1$ 到 $a + 1$ 的数，其中第一个数 $a + b + 1$ 比升序部分的最后一个数 $a$ 大，会产生 $1$ 个上升，总共 $a$ 个上升；降序部分会产生 $b$ 个下降。
- **解决难点**：关键在于确定降序部分的起始和结束数字，即从 $a + b + 1$ 到 $a + 1$，这样能保证满足上升和下降的数量要求。

### 所选题解
- **作者：Squirrel_GZQ (赞：5)，4星**
  - **关键亮点**：思路分析详细，不仅给出了常规思路，还提供了另一种理解方式，代码简洁明了。
- **作者：XH1111 (赞：4)，4星**
  - **关键亮点**：对题意和思路的解释清晰易懂，代码实现简单直接。
- **作者：yeshubo_qwq (赞：4)，4星**
  - **关键亮点**：对为什么这样构造序列进行了详细的数学分析，逻辑严谨。

### 重点代码
```cpp
// 以 Squirrel_GZQ 的代码为例
#include<bits/stdc++.h>
using namespace std;
int up,down;
int main(){
    cin>>up>>down;
    for(int i=1;i<=up;i++) cout<<i<<" ";
    for(int i=up+down+1;i>=up+1;i--) cout<<i<<" ";
    return 0;
}
```
**核心实现思想**：先通过第一个循环升序输出前 `up` 个数，再通过第二个循环降序输出从 `up + down + 1` 到 `up + 1` 的数。

### 可拓展之处
同类型题可能会有更多的限制条件，比如要求序列中的数字满足某些特定的数学关系，或者要求构造的序列是字典序最小或最大的。类似算法套路就是根据给定的条件，合理地安排数字的顺序来满足要求。

### 洛谷题目推荐
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)

### 个人心得
题解中未包含个人心得内容。

---
处理用时：24.54秒