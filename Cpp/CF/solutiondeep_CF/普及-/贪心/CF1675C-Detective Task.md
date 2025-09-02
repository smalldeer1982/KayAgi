# 题目信息

# Detective Task

## 题目描述

Polycarp bought a new expensive painting and decided to show it to his $ n $ friends. He hung it in his room. $ n $ of his friends entered and exited there one by one. At one moment there was no more than one person in the room. In other words, the first friend entered and left first, then the second, and so on.

It is known that at the beginning (before visiting friends) a picture hung in the room. At the end (after the $ n $ -th friend) it turned out that it disappeared. At what exact moment it disappeared — there is no information.

Polycarp asked his friends one by one. He asked each one if there was a picture when he entered the room. Each friend answered one of three:

- no (response encoded with 0);
- yes (response encoded as 1);
- can't remember (response is encoded with ?).

Everyone except the thief either doesn't remember or told the truth. The thief can say anything (any of the three options).

Polycarp cannot understand who the thief is. He asks you to find out the number of those who can be considered a thief according to the answers.

## 说明/提示

In the first case, the answer is $ 1 $ since we had exactly $ 1 $ friend.

The second case is similar to the first.

In the third case, the suspects are the third and fourth friends (we count from one). It can be shown that no one else could be the thief.

In the fourth case, we know absolutely nothing, so we suspect everyone.

## 样例 #1

### 输入

```
8
0
1
1110000
?????
1?1??0?0
0?0???
??11
??0??```

### 输出

```
1
1
2
5
4
1
1
3```

# AI分析结果



# 侦探任务

## 题目描述

Polycarp 购买了一幅昂贵的画作，并邀请他的 $n$ 位朋友依次进入房间观赏。每位朋友离开后下一位才能进入。最后发现画作被盗。每位朋友在被询问时回答以下三种情况之一：
- 0（进入时画不在）
- 1（进入时画在）
- ?（不记得）

除小偷外，其他人必须说真话或回答?。小偷可以说任意答案。求可能的小偷人数。

## 样例输入输出

见原题描述。

---

## 题解分析与结论

### 关键思路
1. **时间轴约束**：小偷必须满足其之前的所有回答为1或?，之后的回答为0或?。
2. **边界确定**：找到最后一个1（保证其后无真实存在的画）和第一个0（保证其前无存在的画），这两个位置之间的区间即为可能的小偷范围。
3. **区间计算**：若最后一个1的位置为`left`，第一个0的位置为`right`，则答案区间为`right - left + 1`。

### 最优题解

#### 题解作者：Adolfo_North（⭐⭐⭐⭐⭐）
**亮点**：代码简洁高效，时间复杂度O(n)，完美处理所有边界情况。
```cpp
#include <bits/stdc++.h>
using namespace std;
string a;
int main() {
    int T; cin >> T;
    while(T--) {
        cin >> a;
        int sizea = a.size();
        int left = 0, right = sizea - 1;
        // 找最后一个1的位置
        for(int i = 0; i < sizea; i++) 
            if(a[i] == '1') left = i;
        // 找第一个0的位置（从left开始）
        for(int i = left; i < sizea; i++)
            if(a[i] == '0') { right = i; break; }
        cout << right - left + 1 << endl;
    }
    return 0;
}
```
**核心思想**：通过两次遍历确定关键边界点，直接计算区间长度。处理全?、全0/1等特殊情况的逻辑隐含在变量初始值中。

#### 题解作者：FReQuenter（⭐⭐⭐⭐）
**亮点**：预处理前后缀数组，系统化验证每个位置的合法性。
```cpp
// 预处理a数组（前i位是否合法）
for(int i=0; i<s.length(); i++)
    a[i+1] = a[i] && (s[i]=='1'||s[i]=='?');
// 预处理b数组（后i位是否合法）
for(int i=s.length()-1; i>=0; i--)
    b[s.length()-i] = b[s.length()-i-1] && (s[i]=='0'||s[i]=='?');
// 统计合法位置
for(int i=0; i<s.length(); i++)
    if(a[i] && b[s.length()-i-1]) ans++;
```
**核心思想**：通过两个数组分别记录前后缀合法性，遍历时验证双重条件。空间换时间，思路更易理解。

#### 题解作者：ryanright（⭐⭐⭐⭐）
**亮点**：分类讨论各种情况，逻辑清晰。
```cpp
int l = 0, r = 0;
for (int i = 1; i <= n; i++)
    if (str[i] == '1') l = i;
    else if (str[i] == '0' && !r) r = i;
// 分类输出不同情况的结果
if (l && r) printf("%d\n", r - l + 1);
else if (!l && !r) printf("%d\n", n);
...
```
**核心思想**：显式处理无1/0的边界情况，逻辑分支完整。

---

## 关键技巧总结
1. **边界标记法**：通过标记关键节点（最后1/首个0）快速确定区间，无需复杂数据结构。
2. **逆向思维**：小偷的存在会分割时间轴为前后两部分，利用此特性简化验证条件。
3. **预处理优化**：通过前后缀数组预处理合法性，可快速判断任意位置的可行性。

## 拓展练习
1. [CF977D 交替子序列](https://codeforces.com/problemset/problem/977/D)（利用边界条件判断）
2. [洛谷P1563 覆盖统计](https://www.luogu.com.cn/problem/P1563)（区间合并与边界处理）
3. [LeetCode 152. 乘积最大子数组](https://leetcode.com/problems/maximum-product-subarray/)（动态维护极值与边界）

---
处理用时：61.32秒