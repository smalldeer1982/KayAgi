# 题目信息

# [NWRRC 2013] Energy Tycoon

## 题目描述



Little Vasya is playing a new computer game -- turn-based strategy `Energy Tycoon`.

The rules of the game are quite simple:

The board contains $n$ slots arranged in a line.

There are power plants, one power plant occupies one or two consecutive slots, and produces one unit of energy.

Each turn the game allows you to build one new power plant, you can put it on the board if you wish. If there is no place for the new power plant, you can remove some older power plants.

After each turn, the computer counts the amount of energy produced by the power plants on the board and adds it to the total score.

![](/upload/images2/enegrgytycoon.png)

Vasya already knows the types of power plant he will be able to build each turn. Now he wants to know, what the maximum possible score he can get is. Can you help him?



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
3
21121
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2
12
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2
211
```

### 输出

```
4
```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
题目要求在每个回合中尽可能放置能源装置，以最大化总能量产出。由于每个装置的能量产出相同，因此贪心策略是优先放置占用空间较小的装置（即占用1个位置的装置），以最大化装置的放置数量。当空间不足时，拆除占用空间较大的装置（即占用2个位置的装置）来腾出空间。

### 所选高星题解
#### 1. 作者：Wind_Smiled (4星)
**关键亮点**：
- 清晰地阐述了贪心策略的三个条件，逻辑清晰。
- 代码简洁，变量命名合理，易于理解。
- 强调了数据范围问题，提醒使用`long long`。

**核心代码**：
```cpp
for(long long i=0;i<s.size();i++){
    if(s[i]=='1'){
        if(n>=1){
            one++;
            n--;
        }
        else if(n==0&&two>=1){
            two--;
            one++;
            n++;
        }
    }
    else if(s[i]=='2'){
        if(n>=2){
            two++;
            n-=2;
        }
    }
    ans=ans+one+two;
}
```
**实现思想**：优先放置占用1个位置的装置，若空间不足则拆除占用2个位置的装置。

#### 2. 作者：ZXY赵显义 (4星)
**关键亮点**：
- 详细解释了贪心策略的三种情况，逻辑严谨。
- 代码结构清晰，变量命名合理。
- 提醒了回合数未知的问题，建议使用`string`存储。

**核心代码**：
```cpp
for(int i=0;i<str.size();i++){
    if(str[i]=='1')
        if(cnt1+2*cnt2+1<=n) cnt1++;
        else if(cnt2) cnt2--,cnt1++;
    if(str[i]=='2'&&cnt1+2*cnt2+2<=n) cnt2++;
    sum+=cnt1+cnt2; 
}
```
**实现思想**：优先放置占用1个位置的装置，若空间不足则拆除占用2个位置的装置。

#### 3. 作者：Asimplename (4星)
**关键亮点**：
- 代码简洁，逻辑清晰，易于理解。
- 强调了数据范围问题，提醒使用`long long`。

**核心代码**：
```cpp
for(int i = 0; i < str.size(); i ++){
    if(str[i] == '1'){
        if(sum + 1 <= n){
            sum += 1;
            num1 ++;
        }
        else{
            if(num2 != 0){
                sum -= 1;
                num1 ++;
                num2 --;
            }
        }
    }
    else{
        if(sum + 2 <= n){
            sum += 2;
            num2 ++;
        }
    }
    ans += num1 + num2;
}
```
**实现思想**：优先放置占用1个位置的装置，若空间不足则拆除占用2个位置的装置。

### 最优关键思路或技巧
- **贪心策略**：优先放置占用空间较小的装置，以最大化装置的放置数量。
- **空间管理**：当空间不足时，拆除占用空间较大的装置来腾出空间。
- **数据范围**：注意使用`long long`以避免溢出问题。

### 可拓展之处
- **类似题目**：可以扩展到其他资源分配问题，如背包问题、任务调度等，使用贪心策略优化资源利用。

### 推荐题目
1. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录
- **Wind_Smiled**：提醒了数据范围问题，强调了使用`long long`的重要性。
- **ZXY赵显义**：强调了回合数未知的问题，建议使用`string`存储输入数据。
- **Asimplename**：代码简洁，逻辑清晰，易于理解，适合初学者学习。

---
处理用时：28.39秒