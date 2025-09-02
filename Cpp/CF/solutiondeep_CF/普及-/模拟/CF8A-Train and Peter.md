# 题目信息

# Train and Peter

## 题目描述

Peter 很喜欢坐火车去旅行。他实在是太喜欢坐火车了，以至于在火车上睡着了（雾）。

在一个夏天，Peter 正在一个从 A 城开往 B 城的列车上。像往常一样，他睡着了。突然，他醒了过来（?），开始看窗外的景物。他发现每一个火车站都有一面彩旗（旗上只有一种颜色）。

Peter 开始记忆他看到的彩旗的顺序。但是很快地，他又睡着了。不幸地，他没睡多久又醒来了，并且他开始继续记他看到的彩旗。一段时间以后，他又睡着了，这次直到旅途结束都没醒来。

到站以后，他告诉了他的父母他在旅途中看到的彩旗的顺序——在他中途睡着之前和中途睡着之后分别看到的两个颜色序列。

他的父母知道 Peter 特别喜欢幻想，所以他们把 Peter 说的序列给了你，并请你判断他的乘车方向。

他的父母用不同的小写字母表示不同的颜色。相同字母表示相同颜色，不同字母表示不同颜色。

## 说明/提示

列车一直都在移动，所以一面同样的旗子不可能被看到两次。

## 样例 #1

### 输入

```
atob
a
b
```

### 输出

```
forward
```

## 样例 #2

### 输入

```
aaacaaa
aca
aa
```

### 输出

```
both
```

# AI分析结果

### 题目翻译
题目已为中文，无需翻译。

### 综合分析与结论
这些题解的核心思路基本一致，都是在原字符串和反转后的字符串中依次查找两个子串，根据查找结果判断乘车方向。主要区别在于代码实现方式和细节处理。

#### 思路对比
- **使用 STL 函数**：大部分题解使用了 `string` 的 `find` 函数和 `reverse` 函数，代码简洁高效。
- **手动实现查找**：如 Loner_Knowledge 的题解，通过循环手动实现子串查找，代码相对复杂。
- **Pascal 实现**：LuckyCloud 使用 Pascal 语言，利用 `Pos` 和 `delete` 函数处理字符串。

#### 算法要点
- **查找子串**：在原字符串和反转后的字符串中依次查找两个子串。
- **判断结果**：根据查找结果判断乘车方向，有 `forward`、`backward`、`both`、`fantasy` 四种情况。

#### 解决难点
- **顺序问题**：确保第二个子串在第一个子串之后出现。
- **边界判断**：处理查找失败的情况。

### 评分较高的题解
1. **SIXIANG32（5星）**
    - **关键亮点**：代码简洁，仅 9 行，使用三目运算符简化判断逻辑。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{ 
    string s1,s2,s3,cs1;
    cin>>s1>>s2>>s3,cs1=s1,reverse(cs1.begin(),cs1.end());
    int pos1=s1.find(s2),pos2=cs1.find(s2),f1=s1.find(s3,pos1+s2.size()),f2=cs1.find(s3,pos2+s2.size());
    cout<<((pos1==-1&&pos2==-1)?("fantasy"):((f1!=-1&&f2==-1)?("forward"):((f1==-1&&f2!=-1)?("backward"):((f1!=-1&&f2!=-1)?("both"):("fantasy"))))); 
}
```
2. **Forever1507（4星）**
    - **关键亮点**：代码注释详细，适合初学者，逻辑清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    bool forward=0,backward=0;
    string a,b,c;
    getline(cin,a);
    getline(cin,b);
    getline(cin,c);
    int a1=a.size();
    if(a.find(b)<=a1&&a.find(c,a.find(b)+b.size())<=a1){
        forward=1;
    }
    reverse(a.begin(),a.end());
    if(a.find(b)<=a1&&a.find(c,a.find(b)+b.size())<=a1){
        backward=1;
    }
    if(forward==1&&backward==1){
        cout<<"both";
    }
    else if(forward==1){
        cout<<"forward";
    }
    else if(backward==1){
        cout<<"backward";
    }
    else{
        cout<<"fantasy";
    }
    return 0;
}
```
3. **冰糖鸽子（4星）**
    - **关键亮点**：使用三目运算符简化代码，代码量少。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s,x,y;
int xl,yl,a,b;
int main(){
    cin >> s >> x >> y;
    xl = s.find(x),yl = s.find(y,xl+x.length());
    a = ((yl!=string::npos&&xl!=string::npos)? 1 : 0);
    reverse(s.begin(),s.end());
    xl = s.find(x),yl = s.find(y,xl+x.length());
    b = ((yl!=string::npos&&xl!=string::npos)? 1 : 0);
    cout << ((a == 1 && b == 1)?"both":((a==1 && b == 0)?"forward":((a == 0 && b == 1)?"backward":"fantasy"))) << endl;
    return 0;
}
```

### 最优关键思路或技巧
- **使用 STL 函数**：`string` 的 `find` 函数和 `reverse` 函数可以简化字符串处理。
- **三目运算符**：可以简化判断逻辑，减少代码量。

### 拓展思路
同类型题可考察字符串匹配、子串查找等，类似算法套路有 KMP 算法、Boyer-Moore 算法等。

### 洛谷相似题目推荐
1. P1308 [统计单词数](https://www.luogu.com.cn/problem/P1308)
2. P2249 【深基13.例1】查找
3. P3375 【模板】KMP字符串匹配

### 个人心得摘录与总结
- **Forever1507**：刚开始卡了 5 分钟，原因是没注意第二个串要在第一个串后面，提醒做题时要注意顺序问题。
- **Soshine_溯闪**：强调做题时要注意输出条件的逻辑判断，避免错误。 

---
处理用时：30.13秒