# 题目信息

# Minimum Ternary String

## 题目描述

给定一个由 '0', '1', '2' 组成的字符串  $S$ 。可以交换相邻'0', '1'或'1', '2'的位置（例如：'12' - '21'  $\;$  '01' - '10'）请输出原字符串经过任意转换后字典序最小的字符串。原字符串长度不超过  $10^5$ 。

## 样例 #1

### 输入

```
100210
```

### 输出

```
001120
```

## 样例 #2

### 输入

```
11222121
```

### 输出

```
11112222
```

## 样例 #3

### 输入

```
20
```

### 输出

```
20
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路基本一致，都是基于题目中“0 和 2 不能交换，1 可以任意挪动”这一特性，先提取出所有的 1，再将 1 插入到第一个 2 之前，以此得到字典序最小的字符串，同时对没有 2 的情况进行特判。

- **思路对比**：多数题解思路相同，zxqwq 的思路有所不同，他根据序列中是否同时出现 0 和 2 进行分类讨论，在出现 0 和 2 时对第一个 2 前后的部分分别处理。
- **算法要点**：大部分题解先统计 1 的个数，再遍历字符串处理 0 和 2，在遇到第一个 2 时插入 1。部分题解使用了字符串的查找和插入函数简化操作。
- **解决难点**：主要难点在于考虑没有 2 的特殊情况，以及如何高效地插入 1。各题解通过特判和标记等方式解决了这些问题。

### 所选题解
- **shurongwang（5 星）**：
  - **关键亮点**：思路清晰，代码简洁，使用 `insert` 函数直接在第一个 2 前插入 1，逻辑简单易懂。
```cpp
#include <bits/stdc++.h>
#define loop(i, to)  for (num i = 0; i < to; ++i)
using namespace std;
int n, cnt, pos;
string dat, ans;
int main() {
    cin >> dat;
    loop (i, dat.size()) {
        if (dat[i] == '1') {
            ++cnt;
            continue;
        }
        ans += dat[i];
    }
    pos = ans.size();
    loop (i, ans.size()) {
        if (ans[i] == '2') {
            pos = i;
            break;
        }
    }
    loop (j, cnt) {
        ans.insert(ans.begin() + pos, '1');
    }
    cout << ans << endl;
}
```
核心实现思想：先遍历原字符串，将非 1 的字符存入 `ans` 中并统计 1 的个数，再找到 `ans` 中第一个 2 的位置，最后在该位置插入所有的 1。

- **Fearliciz（4 星）**：
  - **关键亮点**：代码短小精悍，通过一个标记 `flag` 来判断是否是第一个 2，直接在输出时处理 1 的插入，避免了额外的字符串操作。
```cpp
#include<bits/stdc++.h>
using namespace std;
string c; bool flag=1;
int main()
{
    cin>>c; int len=c.length(),cnt1=0;
    for(int i=0;i<len;i++) if(c[i]=='1') cnt1++;
    for(int i=0;i<len;i++){
        if(c[i]=='1') continue;
        if(c[i]=='2'&&flag){ for(int j=1;j<=cnt1;j++) cout<<"1"; cout<<"2"; flag=0;}
        else cout<<c[i];
    }
    if(flag) for(int j=1;j<=cnt1;j++) cout<<"1";
}
```
核心实现思想：先统计 1 的个数，再遍历原字符串，遇到 1 跳过，遇到第一个 2 时先输出所有 1 再输出 2，最后处理没有 2 的情况。

- **小闸蟹（4 星）**：
  - **关键亮点**：代码逻辑清晰，通过标记 `HasTwo` 和 `Met` 分别处理是否有 2 和是否第一次遇到 2 的情况，可读性强。
```cpp
#include <iostream>
#include <string>
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string Str;
    std::cin >> Str;
    int One = 0, Zero = 0;
    bool HasTwo = false;
    for (const auto &c : Str)
    {
        if (c == '0') ++Zero;
        else if (c == '1') ++One;
        else if (c == '2') HasTwo = true;
    }
    if (!HasTwo)
    {
        for (int i = 0; i < Zero; ++i) std::cout << 0;
        for (int i = 0; i < One; ++i) std::cout << 1;
        std::cout << std::endl;
        return 0;
    }
    bool Met = false;
    for (const auto &c : Str)
    {
        if (c == '0') std::cout << 0;
        else if (c == '1') continue;
        else if (c == '2')
        {
            if (!Met)
            {
                Met = true;
                for (int i = 0; i < One; ++i) std::cout << 1;
                std::cout << 2;
            }
            else std::cout << 2;
        }
    }
    std::cout << std::endl;
    return 0;
}
```
核心实现思想：先遍历原字符串统计 0、1 的个数和是否有 2，若没有 2 则直接输出 0 和 1，否则再次遍历原字符串，遇到 0 输出，遇到 1 跳过，遇到第一个 2 时输出所有 1 再输出 2，后续遇到 2 直接输出。

### 最优关键思路或技巧
- **核心思维**：抓住“0 和 2 相对位置不变，1 可任意挪动”这一特性，将问题简化为提取 1 并插入到合适位置。
- **代码技巧**：使用标记变量（如 `flag`、`Met` 等）来判断是否是第一个 2，避免复杂的逻辑判断；利用字符串的查找和插入函数（如 `find`、`insert`）简化操作。

### 可拓展之处
同类型题目可能会给出不同的字符和交换规则，解题关键在于分析字符之间的交换关系，找出不变量和可移动的元素，再根据字典序的要求进行处理。

### 推荐洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，需要根据一定规则合并元素以达到最优结果。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：同样是贪心算法的应用，通过合理安排顺序使总等待时间最短。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：利用贪心策略解决区间覆盖问题。

### 个人心得摘录与总结
- **帅到报警**：做这道题花了半个小时才想出思路，说明贪心类型的题目需要多思考，找到关键的解题点。
- **HPXXZYY**：尝试使用贪心模拟交换的方法失败，发现存在反例，提醒我们在解题时要考虑全面，对思路进行验证。 

---
处理用时：50.78秒