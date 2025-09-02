# 题目信息

# Hacking Cypher

## 题目描述

Polycarpus participates in a competition for hacking into a new secure messenger. He's almost won.

Having carefully studied the interaction protocol, Polycarpus came to the conclusion that the secret key can be obtained if he properly cuts the public key of the application into two parts. The public key is a long integer which may consist of even a million digits!

Polycarpus needs to find such a way to cut the public key into two nonempty parts, that the first (left) part is divisible by $ a $ as a separate number, and the second (right) part is divisible by $ b $ as a separate number. Both parts should be positive integers that have no leading zeros. Polycarpus knows values $ a $ and $ b $ .

Help Polycarpus and find any suitable method to cut the public key.

## 样例 #1

### 输入

```
116401024
97 1024
```

### 输出

```
YES
11640
1024
```

## 样例 #2

### 输入

```
284254589153928171911281811000
1009 1000
```

### 输出

```
YES
2842545891539
28171911281811000
```

## 样例 #3

### 输入

```
120
12 1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 破解密码

## 题目描述
Polycarpus 参加了一场破解一款新型安全即时通讯软件的竞赛。他几乎就要赢了。

在仔细研究了交互协议后，Polycarpus 得出结论：如果他能恰当地将该应用程序的公钥分成两部分，就能得到密钥。公钥是一个很长的整数，甚至可能由一百万个数字组成！

Polycarpus 需要找到一种方法，将公钥分成两个非空部分，使得第一部分（左边）作为一个单独的数能被 $a$ 整除，第二部分（右边）作为一个单独的数能被 $b$ 整除。这两部分都应该是没有前导零的正整数。Polycarpus 知道 $a$ 和 $b$ 的值。

请帮助 Polycarpus 找到任何合适的分割公钥的方法。

## 样例 #1
### 输入
```
116401024
97 1024
```
### 输出
```
YES
11640
1024
```

## 样例 #2
### 输入
```
284254589153928171911281811000
1009 1000
```
### 输出
```
YES
2842545891539
28171911281811000
```

## 样例 #3
### 输入
```
120
12 1
```
### 输出
```
NO
```

### 算法分类
枚举

### 综合分析与结论
这几道题解思路基本一致，都是通过维护两个数组来记录前 $i$ 位和后 $n - i + 1$ 位分别对 $a$ 和 $b$ 取模的结果，然后枚举分割点，判断是否存在合法的分割方式。主要难点在于处理大数取模避免溢出，题解们都通过在递推过程中不断对 $a$ 和 $b$ 取模来解决。

### 所选的题解
- **作者：wxzzzz (5星)**
    - **关键亮点**：思路清晰，代码简洁，详细给出递推式并通过自定义取模函数处理可能出现的负数情况。
    - **重点代码**：
```cpp
for (int i = 1; i <= n; i++)
    na[i] = moda(moda(na[i - 1] * 10) + s[i] - '0');

for (int i = n; i >= 1; i--) {
    nb[i] = modb(nb[i + 1] + modb(p * (s[i] - '0')));
    p = modb(p * 10);
}

for (int i = 1; i < n; i++)
    if (s[i + 1]!= '0' &&!na[i] &&!nb[i + 1]) {
        pos = i;
        break;
    }
```
核心实现思想：通过递推计算以 $i$ 结尾的前半部分对 $a$ 取模结果 `na[i]` 和以 $i$ 结尾的后半部分对 $b$ 取模结果 `nb[i]`，然后枚举分割点判断是否合法。
- **作者：CSP_Sept (4星)**
    - **关键亮点**：简洁明了地阐述思路和递推式，代码结构清晰。
    - **重点代码**：
```cpp
for(int i = 1 ; i <= n ; i++){
    d[i] = s[i] - '0';
    x[i] = (x[i - 1] * 10 % a + d[i]) % a;
}
int base = 1;
for(int i = n ; i > 1 ; i--){
    y[i] = (y[i + 1] + base * d[i] % b) % b;
    base *= 10;
    base %= b;
    if(d[i] == 0) continue;
    if(x[i - 1] == 0 && y[i] == 0){
        puts("YES");
        // 输出部分省略
        return 0;
    }
}
```
核心实现思想：利用递推式计算前 $i$ 位对 $a$ 取模结果 `x[i]` 和后 $n - i + 1$ 位对 $b$ 取模结果 `y[i]`，并在循环中判断是否存在合法分割点。
- **作者：FutaRimeWoawaSete (4星)**
    - **关键亮点**：清晰转化题意，代码实现完整。
    - **重点代码**：
```cpp
for(int i = 1 ; i <= n ; i ++) pre[i] = pre[i - 1] * 10 % a + (s[i] - '0'), pre[i] %= a;
p = 1;bool flag = true;
for(int i = n ; i >= 1 ; i --) 
{
    flag = flag && (s[i] == '0');
    suf[i] = suf[i + 1] + p * (s[i] - '0') % b, suf[i] %= b;
    p = p * 10 % b;
    if(i!= 1 && pre[i - 1] == 0 && suf[i] == 0 &&!flag) 
    {
        puts("YES");
        // 输出部分省略
        return 0;
    }
}
```
核心实现思想：通过两个循环分别计算前 $i$ 位对 $a$ 取模结果 `pre[i]` 和后 $i$ 位对 $b$ 取模结果 `suf[i]`，并在循环中判断是否存在合法分割点，同时注意处理前导零情况。

### 最优关键思路或技巧
利用递推关系计算大数对 $a$ 和 $b$ 的取模结果，避免直接处理大数导致的溢出问题，同时在递推过程中不断取模保证数据在可处理范围内。

### 可拓展之处
同类型题可考察不同的分割条件或对更多部分进行分割，类似算法套路可应用于处理其他涉及大数运算且需判断特定条件的字符串或数字处理问题。

### 推荐洛谷题目
- [P1116 车厢重组](https://www.luogu.com.cn/problem/P1116)：通过交换相邻车厢使车厢编号从小到大排序，考察对数组元素操作及计数。
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：从 $n$ 个整数中任选 $k$ 个整数相加，判断有多少种选择方法使得和为质数，涉及枚举与质数判断。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：根据给定的条件模拟小玉游泳的过程，判断游到对岸所需天数，考察模拟与简单数学运算。

### 个人心得
无。

---
处理用时：70.34秒