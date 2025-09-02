# 题目信息

# Bill Total Value

## 题目描述

Vasily exited from a store and now he wants to recheck the total price of all purchases in his bill. The bill is a string in which the names of the purchases and their prices are printed in a row without any spaces. Check has the format " $ name_{1}price_{1}name_{2}price_{2}...name_{n}price_{n} $ ", where $ name_{i} $ (name of the $ i $ -th purchase) is a non-empty string of length not more than $ 10 $ , consisting of lowercase English letters, and $ price_{i} $ (the price of the $ i $ -th purchase) is a non-empty string, consisting of digits and dots (decimal points). It is possible that purchases with equal names have different prices.

The price of each purchase is written in the following format. If the price is an integer number of dollars then cents are not written.

Otherwise, after the number of dollars a dot (decimal point) is written followed by cents in a two-digit format (if number of cents is between $ 1 $ and $ 9 $ inclusively, there is a leading zero).

Also, every three digits (from less significant to the most) in dollars are separated by dot (decimal point). No extra leading zeroes are allowed. The price always starts with a digit and ends with a digit.

For example:

- "234", "1.544", "149.431.10", "0.99" and "123.05" are valid prices,
- ".333", "3.33.11", "12.00", ".33", "0.1234" and "1.2" are not valid.

Write a program that will find the total price of all purchases in the given bill.

## 样例 #1

### 输入

```
chipsy48.32televizor12.390
```

### 输出

```
12.438.32
```

## 样例 #2

### 输入

```
a1b2c3.38
```

### 输出

```
6.38
```

## 样例 #3

### 输入

```
aa0.01t0.03
```

### 输出

```
0.04
```

# AI分析结果



# Bill Total Value 账单总金额

## 题目描述

Vasily 离开商店后想要重新核对账单总金额。账单是一个没有空格的字符串，格式为 " $ name₁price₁name₂price₂...nameₙpriceₙ $ "，其中：
- nameᵢ 是长度不超过10的小写字母串
- priceᵢ 是由数字和点组成的非空字符串
- 价格遵循特定格式：
  - 整数部分每三位用点分隔（如1.544表示1544）
  - 小数部分必须为两位（如0.99）
  - 不允许前导零（如012）和非法格式（如.333）

要求计算所有商品的总金额，并按相同格式输出。

## 算法分类
字符串处理、模拟

---

## 题解对比与结论

### 题解评分与亮点
1. **ZQIN_P（4.5星）**
   - 亮点：采用整数分存储避免浮点误差，按字符流处理输入，栈结构处理输出格式
   - 关键代码：
     ```cpp
     while(cin>>c){
         if('0'<=c&&c<='9'){
             pri*=10; pri+=c-'0'; w++;
         } else if(c=='.'){
             w=0; b=true;
         } else{
             if(w==3||!b) ans+=pri*100;
             else ans+=pri;
             pri=0; w=0; b=false;
         }
     }
     ```
   - 心得：通过将金额扩大100倍存储为整数分，解决了浮点精度问题

2. **I_will_AKIOI（4星）**
   - 亮点：通过判断最后小数点的位置识别价格类型，统一转为分处理
   - 关键实现：
     ```cpp
     if(y+2==x) ans+=sum;  // 小数处理
     else ans+=sum*100;     // 整数处理
     ```

3. **Jerrycyx（4星）**
   - 亮点：逐段解析价格，通过四舍五入处理小数精度
   - 核心代码：
     ```cpp
     int dec=(ans-inter+0.005)*100.0;  // 四舍五入处理
     ```

### 最优思路总结
1. **字符串分割**：通过遍历字符流，遇到字母时分割价格段
2. **价格类型判断**：根据最后小数点的位置判断整数/小数格式
3. **精度处理**：将金额统一转为分（扩大100倍）存储为整数
4. **格式化输出**：使用栈结构倒序处理整数部分的三位分隔符

---

## 相似题目推荐
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 字符串处理与贪心
2. [P1603 斯诺登的密码](https://www.luogu.com.cn/problem/P1603) - 字符串转换与组合
3. [P1022 计算器的改良](https://www.luogu.com.cn/problem/P1022) - 表达式解析与模拟

---

## 关键代码实现（ZQIN_P版核心逻辑）
```cpp
// 输入处理与累加
long long ans = 0;
bool b = false;  // 是否遇到小数点
int pri = 0, w = 0;  // 当前价格、小数点后位数

while(cin >> c) {
    if(isdigit(c)) {
        pri = pri * 10 + (c - '0');
        w += (b ? 1 : 0);  // 记录小数点后位数
    } else if(c == '.') {
        b = true;
        w = 0;
    } else {  // 遇到字母时处理累积的价格
        if(b && w == 2) ans += pri;      // 小数情况
        else if(b && w != 2) ans += pri * 100;  // 无效小数视为整数
        else ans += pri * 100;           // 纯整数
        pri = w = 0;
        b = false;
    }
}

// 输出格式化处理
stack<char> st;
int cnt = 1;
while(total_cents > 0) {
    st.push(total_cents % 10 + '0');
    if(cnt % 3 == 0 && total_cents / 10 != 0) 
        st.push('.');
    total_cents /= 10;
    cnt++;
}
// 处理前导零等情况
if(st.empty()) cout << "0";
while(!st.empty()) {
    cout << st.top();
    st.pop();
}
```

---
处理用时：55.94秒