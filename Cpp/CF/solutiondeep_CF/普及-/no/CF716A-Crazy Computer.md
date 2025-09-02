# 题目信息

# Crazy Computer

## 题目描述

ZS the Coder is coding on a crazy computer. If you don't type in a word for a $ c $ consecutive seconds, everything you typed disappear!

More formally, if you typed a word at second $ a $ and then the next word at second $ b $ , then if $ b-a<=c $ , just the new word is appended to other words on the screen. If $ b-a&gt;c $ , then everything on the screen disappears and after that the word you have typed appears on the screen.

For example, if $ c=5 $ and you typed words at seconds $ 1,3,8,14,19,20 $ then at the second $ 8 $ there will be $ 3 $ words on the screen. After that, everything disappears at the second $ 13 $ because nothing was typed. At the seconds $ 14 $ and $ 19 $ another two words are typed, and finally, at the second $ 20 $ , one more word is typed, and a total of $ 3 $ words remain on the screen.

You're given the times when ZS the Coder typed the words. Determine how many words remain on the screen after he finished typing everything.

## 说明/提示

The first sample is already explained in the problem statement.

For the second sample, after typing the first word at the second $ 1 $ , it disappears because the next word is typed at the second $ 3 $ and $ 3-1&gt;1 $ . Similarly, only $ 1 $ word will remain at the second $ 9 $ . Then, a word is typed at the second $ 10 $ , so there will be two words on the screen, as the old word won't disappear because $ 10-9<=1 $ .

## 样例 #1

### 输入

```
6 5
1 3 8 14 19 20
```

### 输出

```
3```

## 样例 #2

### 输入

```
6 1
1 3 5 7 9 10
```

### 输出

```
2```

# AI分析结果

### 题目翻译
# 疯狂的电脑

## 题目描述
ZS程序员正在一台疯狂的电脑上编程。如果你连续 $ c $ 秒没有输入一个单词，那么你之前输入的所有内容都会消失！

更正式地说，如果你在第 $ a $ 秒输入了一个单词，然后在第 $ b $ 秒输入了下一个单词，那么如果 $ b - a <= c $，新输入的单词就会被追加到屏幕上已有的单词后面。如果 $ b - a > c $，那么屏幕上的所有内容都会消失，之后你输入的单词会单独显示在屏幕上。

例如，如果 $ c = 5 $，你在第 $ 1、3、8、14、19、20 $ 秒输入了单词，那么在第 $ 8 $ 秒时，屏幕上会有 $ 3 $ 个单词。之后，在第 $ 13 $ 秒时，由于没有输入任何内容，屏幕上的所有内容都会消失。在第 $ 14 $ 秒和第 $ 19 $ 秒又输入了两个单词，最后，在第 $ 20 $ 秒又输入了一个单词，此时屏幕上总共会剩下 $ 3 $ 个单词。

给定 ZS 程序员输入单词的时间，确定他输入完所有单词后屏幕上还剩下多少个单词。

## 说明/提示
第一个样例在题目描述中已经解释过了。

对于第二个样例，在第 $ 1 $ 秒输入第一个单词后，由于下一个单词在第 $ 3 $ 秒输入，且 $ 3 - 1 > 1 $，所以第一个单词会消失。同样，在第 $ 9 $ 秒时，屏幕上只会剩下 $ 1 $ 个单词。然后，在第 $ 10 $ 秒输入了一个单词，此时屏幕上会有两个单词，因为旧的单词不会消失，因为 $ 10 - 9 <= 1 $。

## 样例 #1
### 输入
```
6 5
1 3 8 14 19 20
```
### 输出
```
3
```

## 样例 #2
### 输入
```
6 1
1 3 5 7 9 10
```
### 输出
```
2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟输入单词的过程，通过比较相邻两次输入的时间差与给定时间 $ c $ 的大小关系，来判断屏幕上的内容是否清空，进而统计最后屏幕上剩余的单词数量。

各题解的算法要点基本一致，都是在输入时间的过程中进行判断和更新答案。主要难点在于要注意答案变量的初始值应设为 $ 1 $，因为第一个单词输入时屏幕上就有一个单词；并且每次清屏时，答案变量也应该赋值为 $ 1 $，因为清屏后新输入了一个单词。

### 所选题解
- **k3v1n070828（4星）**
    - **关键亮点**：思路清晰，对坑点有明确提示，适合萌新。
    - **个人心得**：指出这道题虽然不难，但有一些坑点，如答案变量的初始值应设为 $ 1 $，每次清屏时答案变量也应赋值为 $ 1 $。
- **ZolaWatle（4星）**
    - **关键亮点**：提出不需要开数组，用两个变量分别存储当前和上一次输入的时间，节省空间。
    - **个人心得**：分享了在和机房同学颓废时发现这道题的经历。

### 重点代码
#### k3v1n070828的核心代码
```cpp
#include<cstdio> 
using namespace std;
int n,m,ans=1;
int a[100010];
int main(){
    scanf("%d%d",&n,&m);
    scanf("%d",&a[1]);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]-a[i-1]>m) ans=1;
        else ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```
**核心实现思想**：先单独输入第一个打字时间，然后循环输入其他时间，比较相邻两次输入的时间差与 $ m $ 的大小关系，若大于 $ m $ 则清屏（答案变量赋值为 $ 1 $），否则答案变量自增 $ 1 $。

#### ZolaWatle的核心代码
```cpp
#include <iostream>
#include <cstdio>
#define re register int
using namespace std;

int n,m,ans,last;  

int main()
{
    std::scanf("%d%d",&n,&m);
    for(re i=1;i<=n;i++)
    {
        re temp;
        std::scanf("%d",&temp);
        if(temp-last<=m)
            ans++;
        else
            ans=1; 
        last=temp;  
    }
        
    std::printf("%d",ans);
    return 0;
}
```
**核心实现思想**：用 $ last $ 存储上一次按键盘的时间，$ temp $ 存储当前按键盘的时间，比较 $ temp - last $ 与 $ m $ 的大小关系，若小于等于 $ m $ 则答案变量自增 $ 1 $，否则答案变量赋值为 $ 1 $，最后将 $ temp $ 赋值给 $ last $ 以便下一次使用。

### 最优关键思路或技巧
- 注意答案变量的初始值设为 $ 1 $，每次清屏时答案变量也赋值为 $ 1 $。
- 可以不使用数组，用两个变量分别存储当前和上一次输入的时间，节省空间。

### 拓展思路
同类型题或类似算法套路通常是模拟某个过程，根据一定的规则进行状态的更新和判断。例如模拟游戏过程、模拟事件的发生和处理等。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)
- [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563)

---
处理用时：38.89秒