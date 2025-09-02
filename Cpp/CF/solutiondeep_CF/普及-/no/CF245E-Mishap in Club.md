# 题目信息

# Mishap in Club

## 题目描述

Polycarpus just has been out of luck lately! As soon as he found a job in the "Binary Cat" cafe, the club got burgled. All ice-cream was stolen.

On the burglary night Polycarpus kept a careful record of all club visitors. Each time a visitor entered the club, Polycarpus put down character "+" in his notes. Similarly, each time a visitor left the club, Polycarpus put character "-" in his notes. We know that all cases of going in and out happened consecutively, that is, no two events happened at the same time. Polycarpus doesn't remember whether there was somebody in the club at the moment when his shift begun and at the moment when it ended.

Right now the police wonders what minimum number of distinct people Polycarpus could have seen. Assume that he sees anybody coming in or out of the club. Each person could have come in or out an arbitrary number of times.

## 样例 #1

### 输入

```
+-+-+
```

### 输出

```
1
```

## 样例 #2

### 输入

```
---```

### 输出

```
3```

# AI分析结果

### 题目内容
# 俱乐部的不幸事件

## 题目描述
波利亚科普斯最近运气不佳！他刚在“二进制猫”咖啡馆找到一份工作，咖啡馆就遭遇了盗窃。所有的冰淇淋都被偷走了。

在盗窃发生的那个晚上，波利亚科普斯仔细记录了咖啡馆所有访客的情况。每当有访客进入咖啡馆，波利亚科普斯就在他的记录中写下字符“+”。同样，每当有访客离开咖啡馆，波利亚科普斯就在记录中写下字符“-”。我们知道所有进出事件都是连续发生的，也就是说，没有两个事件是同时发生的。波利亚科普斯不记得在他轮班开始和结束时咖啡馆里是否有人。

现在警方想知道波利亚科普斯最少可能看到了多少不同的人。假设他能看到任何进出咖啡馆的人。每个人进出咖啡馆的次数可以是任意的。

## 样例 #1
### 输入
```
+-+-+
```
### 输出
```
1
```
## 样例 #2
### 输入
```
---
```
### 输出
```
3
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕对咖啡馆人员进出情况的模拟来计算最少的不同人数。不同题解在实现模拟的方式上略有差异。
 - **思路方面**：多数题解采用两个变量分别记录咖啡馆内和外的人数，根据字符“+”“-”进行相应增减，并通过判断当前内外人数是否为0来决定是否需要新增一个人。如“_zexal_”“hopeless_hope”“zwye”等题解。而“L_zaa_L”的思路是通过记录咖啡馆人数的最大值和最小值，用最大值减最小值来得到答案。“YuTianQwQ”的思路是将“+”视为深度加一，“-”视为深度减一，计算最大深度，但其对题意理解可能有偏差，与题目所求最少不同人数的要求不符。
 - **算法要点**：关键在于合理处理人员进出的逻辑，即当咖啡馆内或外无人，却发生相应进出操作时，需新增一个人。不同题解在变量命名和具体实现细节上有所不同。
 - **解决难点**：难点在于理解如何通过模拟人员进出情况，在满足题目条件下求出最少的不同人数，避免重复计算或遗漏情况。

### 所选的题解
 - **作者：L_zaa_L (5星)**
    - **关键亮点**：思路清晰独特，通过记录咖啡馆人数的最值来求解，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    int n=s.size(),minx=1e+8,maxx=-1,p=200;
    for(int i=1;i<=n;i++){
        maxx=max(maxx,p);
        minx=min(minx,p);
        if(s[i-1]=='+') p++;
        else p--;
    }
    maxx=max(maxx,p);
    minx=min(minx,p);
    cout<<maxx-minx;
    return 0;
} 
```
    - **核心实现思想**：初始化咖啡馆人数`p`，遍历字符串，每次遇到“+”咖啡馆人数加1，遇到“-”减1，同时更新人数的最大值`maxx`和最小值`minx`，最后用最大值减去最小值得到最少不同人数。
 - **作者：_zexal_ (4星)**
    - **关键亮点**：思路直接，按照人员进出的实际情况进行模拟，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    string s;
    int in=0,out=0;
    cin>>s;
    for(int i=0; i<s.size(); i++) {
        if(s[i]=='+') {
            in++;
            if(out) out--;
            else in++;
        } else {
            out++;
            if(in) in--;
            else out++;
        }
    }
    cout<<in+out;
    return 0;
}
```
    - **核心实现思想**：用`in`和`out`分别记录咖啡馆内和外的人数，遍历字符串，遇到“+”时，若外面有人则外面人数减1，里面人数加1，否则里面人数加2；遇到“-”时，若里面有人则里面人数减1，外面人数加1，否则外面人数加2，最后输出内外人数之和。
 - **作者：hopeless_hope (4星)**
    - **关键亮点**：同样是直观的模拟思路，代码逻辑清晰，注释详细。
    - **核心代码**：
```cpp
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int main(){
    cin.tie(0);
    cout.tie(0);
    int ins=0,outs=0,len=0;
    string s;
    cin>>s;
    len=s.length();
    for(int i=0;i<len;i++){
        if(s[i]=='+'){
            ins++;
            if(outs) outs--;
        }
        else if(s[i]=='-'){
            outs++;
            if(ins) ins--;
        }
    }
    cout<<ins+outs<<endl;
    return 0;
}
```
    - **核心实现思想**：用`ins`和`outs`分别记录咖啡馆内和外的人数，遍历字符串，遇到“+”时，若外面有人则外面人数减1，里面人数加1；遇到“-”时，若里面有人则里面人数减1，外面人数加1，最后输出内外人数之和。

### 最优关键思路或技巧
可以通过两种主要思路来解决此类问题。一种是像“L_zaa_L”那样，通过记录状态的最值来求解，这种方法较为巧妙，代码简洁。另一种是像多数其他题解，用变量模拟人员的内外分布情况，直观易懂。在实现过程中，合理利用条件判断来避免重复计算是关键技巧。

### 拓展思路
同类型题通常围绕对特定场景下的状态变化进行模拟求解。类似算法套路是先明确状态的表示（如本题中咖啡馆内、外人数），再根据给定的规则（如人员进出规则）进行状态转移，并在转移过程中统计所需结果。

### 洛谷相似题目推荐
 - [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：通过模拟陶陶摘苹果的过程，根据苹果高度和陶陶能够到的高度来统计摘到的苹果数量。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：模拟不同包装铅笔的购买情况，根据所需铅笔数量和不同包装的价格，计算最少花费。
 - [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)：模拟小鱼游泳的开始和结束时间，通过时间计算得出小鱼的游泳时长。

### 个人心得摘录
无

---
处理用时：44.18秒