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

### 题目翻译
本题题目和描述已经是中文，无需翻译。

### 综合分析与结论
这些题解的核心思路基本一致，都是基于“0 和 2 相对位置不变，1 可以任意挪动”这一特性，将所有的 1 提取出来，然后放在第一个 2 之前以得到字典序最小的字符串，同时都考虑了字符串中没有 2 的特殊情况。

算法要点：
1. 统计字符串中 1 的数量。
2. 找出第一个 2 的位置。
3. 根据是否有 2 来决定 1 的插入位置。

解决难点：
1. 特判没有 2 的情况，避免遗漏 1 的输出。
2. 高效地找出第一个 2 的位置。

### 评分较高的题解
- **作者：shurongwang（5 星）**
    - 关键亮点：思路清晰，代码简洁，使用 `string` 类型和 `insert` 函数，易于理解和实现。
    - 核心代码：
```cpp
#include <bits/stdc++.h>
#define loop(i, to)  for (int i = 0; i < to; ++i)
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
核心实现思想：先遍历字符串，将 1 以外的字符存入 `ans` 中并统计 1 的数量，然后找到 `ans` 中第一个 2 的位置，最后将所有 1 插入到该位置之前。

- **作者：Fearliciz（5 星）**
    - 关键亮点：代码短小精悍，通过一个标志位 `flag` 来判断是否是第一个 2，避免了额外的循环和存储。
    - 核心代码：
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
核心实现思想：先统计 1 的数量，然后遍历字符串，遇到 1 跳过，遇到第一个 2 时先输出所有 1 再输出 2，之后遇到 2 直接输出，最后若没有 2 则输出所有 1。

- **作者：小闸蟹（4 星）**
    - 关键亮点：使用 `for (const auto &c : Str)` 遍历字符串，代码风格简洁，同时详细统计了 0、1 的数量和是否有 2，逻辑清晰。
    - 核心代码：
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
核心实现思想：先遍历字符串统计 0、1 的数量和是否有 2，若没有 2 则先输出所有 0 再输出所有 1，否则再次遍历字符串，遇到 0 输出，遇到 1 跳过，遇到第一个 2 时输出所有 1 再输出 2，之后遇到 2 直接输出。

### 最优关键思路或技巧
- 分析交换规则，发现 0 和 2 相对位置不变，1 可任意挪动，将问题简化为插入 1 的问题。
- 使用标志位判断是否是第一个 2，避免多次遍历。
- 利用 `string` 类型的 `insert` 函数和 `find` 函数，简化代码实现。

### 可拓展之处
同类型题或类似算法套路：
- 其他字符串变换问题，如给定特定交换规则，求字典序最大或最小的字符串。
- 可以将字符扩展到更多种类，分析不同字符之间的交换规则，寻找最优排列。

### 洛谷相似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，通过每次合并最小的两个元素来得到最优解。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：也是贪心算法的应用，根据每个元素的某个属性进行排序，以得到最优结果。
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：同样是贪心算法，通过选择单位价值最高的物品来填充背包。

### 个人心得摘录与总结
- **作者：帅到报警**：做这道题花了半个小时才想出思路，感叹自己可能太菜，提示大家对于简单情况可以进行特判，节省时间。
- **作者：HPXXZYY**：尝试用贪心交换的思路失败，发现存在反例，如 `201` 不能通过每次交换使字典序变小的方式得到正确结果，从而转变思路，将 1 提取出来插入第一个 2 之前。总结为在解题时不能盲目使用贪心交换，要考虑特殊情况，通过分析字符间的交换规则找到更合适的解法。 

---
处理用时：36.23秒