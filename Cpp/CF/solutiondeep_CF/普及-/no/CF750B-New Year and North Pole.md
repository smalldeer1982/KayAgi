# 题目信息

# New Year and North Pole

## 题目描述

In this problem we assume the Earth to be a completely round ball and its surface a perfect sphere. The length of the equator and any meridian is considered to be exactly $ 40000 $ kilometers. Thus, travelling from North Pole to South Pole or vice versa takes exactly $ 20000 $ kilometers.

Limak, a polar bear, lives on the North Pole. Close to the New Year, he helps somebody with delivering packages all around the world. Instead of coordinates of places to visit, Limak got a description how he should move, assuming that he starts from the North Pole. The description consists of $ n $ parts. In the $ i $ -th part of his journey, Limak should move $ t_{i} $ kilometers in the direction represented by a string $ dir_{i} $ that is one of: "North", "South", "West", "East".

Limak isn’t sure whether the description is valid. You must help him to check the following conditions:

- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the North Pole, he can move only to the South.
- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the South Pole, he can move only to the North.
- The journey must end on the North Pole.

Check if the above conditions are satisfied and print "YES" or "NO" on a single line.

## 说明/提示

Drawings below show how Limak's journey would look like in first two samples. In the second sample the answer is "NO" because he doesn't end on the North Pole.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750B/9bb594fe352848bbba36035935a49c02ad65109a.png)

## 样例 #1

### 输入

```
5
7500 South
10000 East
3500 North
4444 West
4000 North
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
15000 South
4000 East
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
20000 South
1000 North
1000000 West
9000 North
10000 North
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3
20000 South
10 East
20000 North
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
2
1000 North
1000 South
```

### 输出

```
NO
```

## 样例 #6

### 输入

```
4
50 South
50 North
15000 South
15000 North
```

### 输出

```
YES
```

# AI分析结果

### 题目翻译
# 新年与北极

## 题目描述
在这个问题中，我们假设地球是一个完全的圆球，其表面是一个完美的球体。赤道和任何子午线的长度都被认为恰好是 40000 千米。因此，从北极到南极或从南极到北极的旅行恰好需要 20000 千米。

北极熊利马克（Limak）生活在北极。临近新年时，他帮助某人在世界各地运送包裹。利马克得到的不是要访问地点的坐标，而是关于他应该如何移动的描述，假设他从北极出发。该描述由 n 个部分组成。在他旅程的第 i 部分，利马克应该沿着由字符串 $dir_i$ 表示的方向移动 $t_i$ 千米，$dir_i$ 是以下之一：“North”（北）、“South”（南）、“West”（西）、“East”（东）。

利马克不确定这个描述是否有效。你必须帮助他检查以下条件：
- 如果在任何时刻（在任何指令之前或执行其中一个指令时）利马克在北极，他只能向南移动。
- 如果在任何时刻（在任何指令之前或执行其中一个指令时）利马克在南极，他只能向北移动。
- 旅程必须在北极结束。

检查上述条件是否满足，并在一行上打印 “YES” 或 “NO”。

## 说明/提示
下面的图展示了利马克在前两个样例中的旅程情况。在第二个样例中，答案是 “NO”，因为他没有在北极结束旅程。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750B/9bb594fe352848bbba36035935a49c02ad65109a.png)

## 样例 #1
### 输入
```
5
7500 South
10000 East
3500 North
4444 West
4000 North
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
2
15000 South
4000 East
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
5
20000 South
1000 North
1000000 West
9000 North
10000 North
```
### 输出
```
YES
```

## 样例 #4
### 输入
```
3
20000 South
10 East
20000 North
```
### 输出
```
NO
```

## 样例 #5
### 输入
```
2
1000 North
1000 South
```
### 输出
```
NO
```

## 样例 #6
### 输入
```
4
50 South
50 North
15000 South
15000 North
```
### 输出
```
YES
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟利马克的移动过程，判断是否满足给定的三个条件。由于地球是完美球体，东西方向的移动对结果无影响，所以重点在于处理南北方向的移动。

- **思路**：用一个变量记录利马克当前离北极的距离，在每次移动时，检查是否在北极点却不向南走、在南极点却不向北走、是否越过了南北极点，最后检查是否回到北极点。
- **算法要点**：模拟移动过程，根据方向更新距离，同时进行条件判断。
- **解决难点**：准确处理边界条件，如在南北极点的特殊移动限制和越过极点的情况。

### 较高评分题解
- **作者：Hanghang (赞：2)，4星**
    - **关键亮点**：思路清晰，代码注释详细，易于理解。
    - **个人心得**：无
- **作者：一只大龙猫 (赞：1)，4星**
    - **关键亮点**：考虑到数据范围小，采用一步一步模拟的方法，逻辑简单。
    - **个人心得**：无
- **作者：zljhenry (赞：1)，4星**
    - **关键亮点**：指出了题目中的多个坑点，代码简洁。
    - **个人心得**：无

### 重点代码
以下是 Hanghang 的代码核心部分：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;string y;cin>>x>>y;
        if(s==0&&y!="South")
        {
            cout<<"NO"<<endl;return 0;
        }
        if(s==20000&&y!="North")
        {
            cout<<"NO"<<endl;return 0;
        }
        if(y=="South")s+=x;
        if(y=="North")s-=x;
        if(s<0||s>20000)
        {
            cout<<"NO"<<endl;return 0;
        }
    }
    if(s==0)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}
```
**核心实现思想**：使用变量 `s` 记录当前离北极的距离，在每次移动时，根据方向更新 `s` 的值，并检查是否违反规则，最后判断是否回到北极点。

### 可拓展之处
同类型题通常是模拟类题目，需要根据特定规则模拟某个过程并判断结果是否符合要求。类似算法套路包括模拟游戏过程、模拟物理运动等，关键在于准确理解规则并处理好边界条件。

### 推荐题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563)

### 个人心得摘录与总结
- **zljhenry**：指出题目坑点，如不需要考虑东西方向、在南北极点的特殊限制、不能越过极点等，提醒做题时要仔细考虑边界条件。 

---
处理用时：41.32秒