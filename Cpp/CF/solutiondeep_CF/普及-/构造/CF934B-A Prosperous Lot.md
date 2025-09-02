# 题目信息

# A Prosperous Lot

## 题目描述

Apart from Nian, there is a daemon named Sui, which terrifies children and causes them to become sick. Parents give their children money wrapped in red packets and put them under the pillow, so that when Sui tries to approach them, it will be driven away by the fairies inside.

Big Banban is hesitating over the amount of money to give out. He considers loops to be lucky since it symbolizes unity and harmony.

He would like to find a positive integer $ n $ not greater than $ 10^{18} $ , such that there are exactly $ k $ loops in the decimal representation of $ n $ , or determine that such $ n $ does not exist.

A loop is a planar area enclosed by lines in the digits' decimal representation written in Arabic numerals. For example, there is one loop in digit $ 4 $ , two loops in $ 8 $ and no loops in $ 5 $ . Refer to the figure below for all exact forms.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF934B/ef09358ad2ff9bd7af31e67d589f7cc1105bcc74.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
462```

## 样例 #2

### 输入

```
6
```

### 输出

```
8080```

# AI分析结果

### 题目中文重写
# 幸运的金额

## 题目描述
除了年兽，还有一种叫“祟”的妖怪，它会吓唬孩子，让孩子们生病。父母会给孩子用红包包着钱，放在枕头底下，这样当“祟”靠近孩子时，就会被里面的神仙赶走。

大斑斑正在犹豫要给多少钱。他认为数字中的圈是幸运的，因为它象征着团结与和谐。

他想找到一个不大于 $10^{18}$ 的正整数 $n$，使得 $n$ 的十进制表示中恰好有 $k$ 个圈，或者判断这样的 $n$ 不存在。

圈是指用阿拉伯数字书写的数字的十进制表示中，由线条围成的平面区域。例如，数字 $4$ 有一个圈，数字 $8$ 有两个圈，数字 $5$ 没有圈。具体形式请参考下图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF934B/ef09358ad2ff9bd7af31e67d589f7cc1105bcc74.png)

## 样例 #1
### 输入
```
2
```
### 输出
```
462
```

## 样例 #2
### 输入
```
6
```
### 输出
```
8080
```

### 题解综合分析与结论
- **思路**：各题解均采用贪心策略，优先使用圈数最多的数字 8 来构造满足圈数要求的数。因为要使构造的数位数尽可能少，这样才能保证不超过 $10^{18}$。
- **算法要点**：
    - 首先判断输入的圈数 $k$ 是否大于 36，若大于 36 则直接输出 -1，因为即使全部用 8 构造，最多也只能有 36 个圈（18 个 8）。
    - 若 $k$ 为偶数，直接输出 $\frac{k}{2}$ 个 8。
    - 若 $k$ 为奇数，先输出 $\frac{k - 1}{2}$ 个 8，再输出一个圈数为 1 的数字（如 4、6、9）。
- **解决难点**：
    - **范围判断**：要明确不超过 $10^{18}$ 这个条件限制了最大圈数为 36。
    - **正整数要求**：不能使用数字 0 来凑圈数，因为题目要求输出正整数。

### 评分较高的题解
- **作者：Anguei（5 星）**
    - **关键亮点**：思路清晰，代码简洁易懂，直接点明本题是贪心算法入门题，对解题思路的描述简洁明了。
    - **核心代码**：
```cpp
#include <iostream>

int main() {
    int k;
    std::cin >> k;
    if (k > 36) {
        std::cout << -1 << std::endl;
        return 0;
    }
    for (int i = 1; i <= k / 2; ++i)
        std::cout << 8;
    if (k % 2)
        std::cout << 4;
    std::cout << std::endl;
}
```
核心实现思想：先判断 $k$ 是否大于 36，若大于则输出 -1；否则先输出 $\frac{k}{2}$ 个 8，若 $k$ 为奇数再输出一个 4。

- **作者：wuwenjiong（4 星）**
    - **关键亮点**：思路清晰，代码简洁，对解题步骤的描述清晰，先判断 $k$ 的范围，再根据奇偶性输出相应的数字。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int k,i;
    cin>>k;
    if(k>36)
        cout<<-1;
    else
    {
        if(k%2==1)
            cout<<4;
        for(i=1;i<=k/2;i++)
            cout<<8;
    }
    return 0;
}
```
核心实现思想：先判断 $k$ 是否大于 36，若大于则输出 -1；若 $k$ 为奇数先输出 4，再输出 $\frac{k}{2}$ 个 8。

- **作者：Creroity（4 星）**
    - **关键亮点**：思路清晰，代码精简，对解题思路的描述简洁明了，先进行特判，再根据奇偶性输出相应的数字。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
int main(){
    cin>>k;
    if(k>36){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=k/2;i++)cout<<8;
    if(k%2==1)cout<<6;
    return 0;
}
```
核心实现思想：先判断 $k$ 是否大于 36，若大于则输出 -1；先输出 $\frac{k}{2}$ 个 8，若 $k$ 为奇数再输出一个 6。

### 最优关键思路或技巧
- **贪心策略**：优先使用圈数最多的数字 8 来构造满足圈数要求的数，使构造的数位数尽可能少。
- **奇偶分类处理**：根据圈数 $k$ 的奇偶性分别进行处理，偶数时全部用 8 构造，奇数时先构造偶数个 8 再加上一个圈数为 1 的数字。

### 拓展思路
同类型题可能会改变数字的范围、圈数的定义或者要求输出满足条件的所有数等。类似算法套路为贪心算法，在满足一定条件下，优先选择最优的元素来构造结果。

### 推荐洛谷题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法，通过合理安排顺序使总等待时间最短。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：运用贪心策略，每次合并最小的两堆果子，使总代价最小。
- [P2240 食草动物的盛宴](https://www.luogu.com.cn/problem/P2240)：根据贪心思想，优先选择性价比高的草来满足动物的需求。

### 个人心得摘录与总结
- **GusyNight**：原代码未考虑 $k$ 大于 36 时无解的情况，经过特判后才能正确通过。总结：在解题时要充分考虑题目中的条件限制，避免因遗漏条件而导致错误。
- **李至擎**：强调不能使用 0 来凑数，因为题目要求输出正整数，若使用 0 在 $k = 1$ 时会输出 0 不符合要求。总结：要仔细审题，注意题目中的特殊要求，避免因疏忽而犯错。 

---
处理用时：37.44秒