# 题目信息

# Memory and Trident

## 题目描述

Memory is performing a walk on the two-dimensional plane, starting at the origin. He is given a string $ s $ with his directions for motion:

- An 'L' indicates he should move one unit left.
- An 'R' indicates he should move one unit right.
- A 'U' indicates he should move one unit up.
- A 'D' indicates he should move one unit down.

But now Memory wants to end at the origin. To do this, he has a special trident. This trident can replace any character in $ s $ with any of 'L', 'R', 'U', or 'D'. However, because he doesn't want to wear out the trident, he wants to make the minimum number of edits possible. Please tell Memory what is the minimum number of changes he needs to make to produce a string that, when walked, will end at the origin, or if there is no such string.

## 说明/提示

In the first sample test, Memory is told to walk right, then right, then up. It is easy to see that it is impossible to edit these instructions to form a valid walk.

In the second sample test, Memory is told to walk up, then down, then up, then right. One possible solution is to change $ s $ to "LDUR". This string uses 1 edit, which is the minimum possible. It also ends at the origin.

## 样例 #1

### 输入

```
RRU
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
UDUR
```

### 输出

```
1
```

## 样例 #3

### 输入

```
RUUR
```

### 输出

```
2
```

# AI分析结果

### 题目中文重写
# 记忆与三叉戟

## 题目描述
Memory 在二维平面上从原点开始行走。他得到了一个字符串 $ s $ 来指示他的移动方向：
- 'L' 表示他应该向左移动一个单位。
- 'R' 表示他应该向右移动一个单位。
- 'U' 表示他应该向上移动一个单位。
- 'D' 表示他应该向下移动一个单位。

但现在 Memory 想回到原点。为此，他有一个特殊的三叉戟。这个三叉戟可以将 $ s $ 中的任何字符替换为 'L'、'R'、'U' 或 'D' 中的任意一个。然而，因为他不想过度使用三叉戟，所以他希望进行最少的修改。请告诉 Memory 他最少需要做多少次更改才能生成一个字符串，按照这个字符串行走后能回到原点，如果不存在这样的字符串则输出相应结果。

## 说明/提示
在第一个样例测试中，Memory 被要求先向右走，再向右走，最后向上走。很容易看出，不可能通过编辑这些指令形成一个能回到原点的行走方案。
在第二个样例测试中，Memory 被要求先向上走，再向下走，然后向上走，最后向右走。一个可能的解决方案是将 $ s $ 改为 "LDUR"。这个字符串只使用了 1 次修改，这是最少的可能次数，并且最终能回到原点。

## 样例 #1
### 输入
```
RRU
```
### 输出
```
-1
```

## 样例 #2
### 输入
```
UDUR
```
### 输出
```
1
```

## 样例 #3
### 输入
```
RUUR
```
### 输出
```
2
```

### 题解综合分析与结论
#### 思路对比
所有题解思路核心一致，先判断字符串长度奇偶性，若为奇数则无法回到原点，输出 -1；若为偶数，统计 'L'、'R'、'U'、'D' 各自数量，计算左右和上下偏移量的绝对值之和并除以 2 得到最少修改次数。

#### 算法要点对比
- **计数方式**：部分题解用数组存储各方向计数，部分用单独变量。
- **代码实现**：部分题解将判断字符操作封装成函数，部分直接在主函数处理。

#### 解决难点对比
难点主要在于理解为何偏移量绝对值之和要除以 2，各题解均有解释，如每次修改造成 2 的改变。

### 所选题解
- **Keep_RAD（5星）**
    - **关键亮点**：思路清晰，代码注释详细，易于理解。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int u=0,r=0,l=0,d=0; 
string a;
int main()
{
    cin>>a;
    int s=a.size();
    if(s%2==1)
    {
        cout<<-1;
        return 0; 
    }
    for(int i=0;i<s;++i)
    { 
        if(a[i]=='U') u++;
        if(a[i]=='D') d++;
        if(a[i]=='R') r++;
        if(a[i]=='L') l++;
    }
    cout<<(abs(l-r)+abs(u-d))/2;
    return 0;
}
```
核心实现思想：先判断字符串长度奇偶性，若为奇数输出 -1；若为偶数，遍历字符串统计各方向移动次数，最后计算左右、上下偏移量绝对值之和并除以 2 输出。

- **Galaxy_Q（4星）**
    - **关键亮点**：题目分析详细，代码结构清晰。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
string st;
int cnt1, cnt2; 
void f(char x){
    if(x == 'L')
        cnt1--;
    if(x == 'R')
        cnt1++;
    if(x == 'U')
        cnt2--;
    if(x == 'D')
        cnt2++;
    return; 
}
int main(){
    cin>>st;
    if(st.length()%2)
        cout<<"-1"<<endl; 
    else{
        for(int i=0;i<st.length();i++)
            f(st[i]);
        cout<<(abs(cnt1)+abs(cnt2))/2<<endl; 
    }
    return 0;
} 
```
核心实现思想：将字符判断操作封装在函数中，主函数先判断字符串长度奇偶性，若为偶数则遍历字符串调用函数统计偏移量，最后计算偏移量绝对值之和并除以 2 输出。

- **_Felix（4星）**
    - **关键亮点**：对答案公式有推理过程。
    - **个人心得**：2 年以后再看这题，感慨小孩子有灵感，现在难以根据样例猜出结论。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int len=s.size();
    if(len%2==1)
    {
        printf("-1\n");
        return 0;
    }
    int l=0,r=0,u=0,d=0;
    for(int i=0;i<len;i++)
    {
        if(s[i]=='L')
            l++;
        else if(s[i]=='R')
            r++;
        else if(s[i]=='U')
            u++;
        else if(s[i]=='D')
            d++;
    }
    int lr=abs(l-r);
    int ud=abs(u-d);
    cout<<(abs(lr+ud))/2<<endl;
    return 0;
 } 
```
核心实现思想：先判断字符串长度奇偶性，若为偶数则遍历字符串统计各方向移动次数，计算左右、上下偏移量绝对值，最后求和并除以 2 输出。

### 最优关键思路或技巧
- **奇偶性判断**：快速排除无法回到原点的情况。
- **抵消思想**：利用左右、上下移动可相互抵消的特性，计算偏移量。

### 可拓展之处
同类型题如在二维平面上根据指令移动，判断能否到达指定位置、计算最少移动次数等。类似算法套路为分析移动规则，找出可相互抵消或等效的操作，通过计数和计算偏移量解决问题。

### 推荐洛谷题目
- P1002 过河卒
- P1420 最长连号
- P1047 校门外的树

---
处理用时：34.44秒