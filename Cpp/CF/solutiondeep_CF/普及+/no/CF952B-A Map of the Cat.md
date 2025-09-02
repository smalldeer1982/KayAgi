# 题目信息

# A Map of the Cat

## 题目描述

If you have ever interacted with a cat, you have probably noticed that they are quite particular about how to pet them. Here is an approximate map of a normal cat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952B/ac74b4a6b7c2f3f70f434fbbbba9b66903682fc4.png)However, some cats won't tolerate this nonsense from the humans. Here is a map of a grumpy cat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952B/8b21a0f522686b6bb86b329b669f56577afc2e8b.png)You have met a cat. Can you figure out whether it's normal or grumpy?

## 说明/提示

Please make sure to use the stream flushing operation after each query in order not to leave part of your output in some buffer.

# AI分析结果

### 题目内容
# 猫的地图

## 题目描述
如果你曾经与猫互动过，你可能已经注意到它们对于如何抚摸它们相当挑剔。这是一张普通猫的大致地图。
![普通猫地图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952B/ac74b4a6b7c2f3f70f434fbbbba9b66903682fc4.png)
然而，有些猫不会容忍人类的这种行为。这是一张脾气暴躁的猫的地图。
![脾气暴躁猫地图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952B/8b21a0f522686b6bb86b329b669f56577afc2e8b.png)
你遇到了一只猫。你能判断它是普通的还是脾气暴躁的吗？

## 说明/提示
请确保在每次查询后使用流刷新操作，以免部分输出留在某些缓冲区中。

### 算法分类
模拟

### 综合分析与结论
这几道题解的核心思路都是根据输入的字符串来判断猫是“normal”还是“grumpy”，通过对输入字符串与预定义的特征字符串进行匹配来得出结论。不同题解在细节处理上有所差异，如字符串读入方式、大小写转换以及对特殊符号的处理等。

### 所选的题解
- **作者：__main__（4星）**
  - **关键亮点**：清晰阐述题目大意及按题意模拟的思路，指出读入字符串要用`getline`解决读入缓存问题。
  - **重点代码核心思想**：通过循环不断读入字符串，使用`getline`读取整行输入，然后判断输入字符串是否匹配“normal”或“grumpy”的特征字符串，匹配则输出相应结果并结束程序。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    for (int i = 0; ; ++i)
    {
        printf("%d\n", i);
        string s;
        getline(cin, s);
        if (s == "great" || s == "don't think so"
            || s == "don't touch me" || s == "not bad" || s == "cool")
        {
            puts("normal");
            return 0;
        }
        else if (s == "no way" || s == "don't even" || s == "worse"
                 || s == "terrible" || s == "go die in a hole" || s == "are you serious")
        {
            puts("grumpy");
            return 0;
        }
    }
    return 0;
}
```
- **作者：Li_zi_wei（4星）**
  - **关键亮点**：指出题目的坑点，即忽略“！”号和大写转小写，并给出处理这些坑点的代码实现。
  - **重点代码核心思想**：定义函数`change`将字符串中的大写字母转换为小写，通过循环读入字符串，调用`change`函数处理后，判断是否匹配“normal”或“grumpy”的特征字符串，匹配则输出相应结果并结束程序。
```cpp
#include<bits/stdc++.h>

using namespace std;
string s;
int i = 1;
bool inseg(int bef,int ob,int aft)
{
    return bef <= ob && ob <= aft;
}

void change()
{
    int len = s.length();
    for(int i = 0;i < len;i ++)
        if(inseg('A',s[i],'Z')) s[i]=s[i]-'A'+'a';
}
int main()
{
    while(true)
    {
        cout << i << endl;

        getline(cin,s);

        change();

        if(s == "great"||s == "don't think so"||s == "don't touch me"||s == "not bad"||s == "cool")
        {
            cout << "normal";
            return 0;
        }
        if (s == "no way"||s == "don't even"||s == "terrible"||s == "worse"||s == "are you serious"||s == "go die in a hole")
        {
            cout << "grumpy";
            return 0;
        }
        i ++;
    }
    return 0;
} 
```
- **作者：Ludo（4星）**
  - **关键亮点**：点明这是一道交互题，并解释了交互题概念，同时考虑到令交互次数最小，找到结果就输出的优化思路。
  - **重点代码核心思想**：通过循环进行交互，每次输出询问编号，读入字符串，判断是否匹配“normal”或“grumpy”的特征字符串，匹配则输出相应结果并结束程序。
```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
string s;
int main(void)
{
    for (int i=0;i<10;i++)
    {
        cout<<i<<endl;
        getline(cin,s);
        if (s=="great"||s=="don't think so"||s=="don't touch me"||s=="not bad"||s=="cool")
        {
            cout<<"normal";
            return 0;
        }
        if (s=="no way"||s=="don't even"||s=="worse"||s=="terrible"||s=="go die in a hole"||s=="are you serious")
        {
            cout<<"grumpy";
            return 0;
        }
    }
}
```

### 最优关键思路或技巧
1. **字符串匹配**：通过将输入字符串与预定义的特征字符串进行精确匹配来判断猫的类型，这是解决问题的基础。
2. **处理输入细节**：如使用`getline`处理字符串读入缓存问题，考虑大写转小写以及忽略特殊符号（如“！”号），这些细节处理保证了程序的正确性。
3. **优化交互次数**：在交互题中，一旦找到匹配结果就立即输出并结束程序，避免不必要的交互，从而优化交互次数。

### 拓展
同类型题通常围绕字符串处理与条件判断展开，类似算法套路为仔细分析题目给定的条件，将输入数据与预定义的条件进行匹配，过程中注意处理输入数据的格式、特殊符号等细节。

### 相似知识点洛谷题目
1. [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串处理和校验计算。
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：主要考察字符串匹配与统计。
3. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：需要对输入字符串进行处理并按要求输出图形，涉及字符串操作和图形模拟。 

---
处理用时：70.60秒