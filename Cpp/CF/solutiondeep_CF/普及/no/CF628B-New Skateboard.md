# 题目信息

# New Skateboard

## 题目描述

Max wants to buy a new skateboard. He has calculated the amount of money that is needed to buy a new skateboard. He left a calculator on the floor and went to ask some money from his parents. Meanwhile his little brother Yusuf came and started to press the keys randomly. Unfortunately Max has forgotten the number which he had calculated. The only thing he knows is that the number is divisible by $ 4 $ .

You are given a string $ s $ consisting of digits (the number on the display of the calculator after Yusuf randomly pressed the keys). Your task is to find the number of substrings which are divisible by $ 4 $ . A substring can start with a zero.

A substring of a string is a nonempty sequence of consecutive characters.

For example if string $ s $ is 124 then we have four substrings that are divisible by $ 4 $ : 12, 4, 24 and 124. For the string 04 the answer is three: 0, 4, 04.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use gets/scanf/printf instead of getline/cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
124
```

### 输出

```
4
```

## 样例 #2

### 输入

```
04
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5810438174
```

### 输出

```
9
```

# AI分析结果



# New Skateboard

## 题目描述

Max 想买一个新的滑板。他计算好了购买所需金额，却将计算器留在地上离开。他的弟弟 Yusuf 随机按下了按键。Max 只记得原数字能被 4 整除。

给定由数字组成的字符串 s，求其中能被 4 整除的非空连续子串数量（允许前导零）。

样例 #1 输入 124 输出 4（12,4,24,124）
样例 #2 输入 04 输出 3（0,4,04）

## 算法分类
数学

## 题解分析与结论

所有题解均基于数学特性：末两位数能被4整除的整数必能被4整除。核心思路分为两部分：
1. 检查所有两位子串，若能被4整除则其前所有延伸子串均有效
2. 单独处理单个字符（0/4/8）的情况

### 高星题解推荐

#### 1. Marsrayd（★★★★☆）
**关键亮点**：预生成末两位判断表优化性能，边读入边处理节省内存
**代码核心**：
```cpp
for(int i=0;i<=96;i+=4) is[i/10][i%10]=1; // 预生成末两位合法组合
while(ch>='0'&&ch<='9') {
    // 处理末两位组合
    if(is[pre-'0'][ch-'0']) ans += sum; 
    // 处理单字符
    if(ch=='0'||ch=='4'||ch=='8') ++ans;
}
```

#### 2. Engulf（★★★★☆）
**关键亮点**：逆向遍历简化索引计算，代码简洁直观
**代码核心**：
```cpp
for(int i=s.size()-1;i>=1;i--) {
    int x = (s[i-1]-'0')*10 + (s[i]-'0');
    if(x%4==0) ans += i; // 前i个位置均可作为子串起点
}
```

#### 3. chlchl（★★★★☆）
**关键亮点**：分离单字符与双字符处理逻辑，结构清晰
**代码核心**：
```cpp
for(int i=0;i<n;i++) if(a%4==0) ans++; // 单字符
for(int i=0;i<n-1;i++) if((a*10+b)%4==0) ans+=i+1; // 双字符
```

## 最优实现思路
1. **数学特性应用**：利用末两位判断法则将时间复杂度降至 O(n)
2. **分治策略**：单独处理长度为1和>=2的子串
3. **预计算优化**：提前生成合法末两位组合表（如Marsrayd解法）
4. **流式处理**：边读取字符边计算，适用于超长字符串

## 拓展延伸
类似题目套路：
- 判断被3/9整除（数字和性质）
- 判断被25整除（末两位00/25/50/75）
- 回文数判断（对称性特征）

## 推荐练习
1. [P1217 [USACO1.5] 回文质数](https://www.luogu.com.cn/problem/P1217)（数学特性+字符串处理）
2. [P1591 阶乘数码](https://www.luogu.com.cn/problem/P1591)（大数处理+数位统计）
3. [CF550C Divisibility by Eight](https://www.luogu.com.cn/problem/CF550C)（同类整除问题变式）

## 调试心得摘录
- **Marsrayd**：注意最后一位字符需单独判断是否合法，循环边界易出错
- **EthanOI**：发现初始代码漏判单字符情况导致样例错误，强调全面性测试
- **hxhhxh**：下标从1开始的处理方式能简化索引计算，降低思维负担

---
处理用时：63.57秒