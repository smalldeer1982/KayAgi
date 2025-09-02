# 题目信息

# Secret Combination

## 题目描述

You got a box with a combination lock. The lock has a display showing $ n $ digits. There are two buttons on the box, each button changes digits on the display. You have quickly discovered that the first button adds 1 to all the digits (all digits 9 become digits 0), and the second button shifts all the digits on the display one position to the right (the last digit becomes the first one). For example, if the display is currently showing number 579, then if we push the first button, the display will show 680, and if after that we push the second button, the display will show 068.

You know that the lock will open if the display is showing the smallest possible number that can be obtained by pushing the buttons in some order. The leading zeros are ignored while comparing numbers. Now your task is to find the desired number.

## 样例 #1

### 输入

```
3
579
```

### 输出

```
024
```

## 样例 #2

### 输入

```
4
2014
```

### 输出

```
0142
```

# AI分析结果



# Secret Combination

## 题目描述

你得到一个带有密码锁的盒子。锁的显示屏显示 $n$ 位数字。盒子上有两个按钮，每个按钮都会改变显示屏上的数字。你很快发现第一个按钮会将所有数字加 1（所有数字 9 变为 0），第二个按钮会将显示屏上的所有数字向右循环移动一位（最后一位变为第一位）。例如，若当前显示为 579，按第一个按钮会变成 680，接着按第二个按钮会显示 068。

已知当显示屏显示通过某种操作顺序得到的最小可能数字时锁会打开。现在你需要找到这个最小数字。

## 样例 #1

### 输入
```
3
579
```

### 输出
```
024
```

## 样例 #2

### 输入
```
4
2014
```

### 输出
```
0142
```

---

**算法分类**：枚举、字符串处理

---

### 综合分析与结论
题目本质是在所有可能的移位与加法组合中寻找字典序最小的字符串。各题解核心思路均为枚举所有移位情况，并计算使首字符最小化的加法次数，最终比较所有候选方案。关键优化点在于：
1. 将循环移位转换为字符串拼接处理
2. 通过数学计算直接确定使首字符变0的增量
3. 利用字符串比较特性简化字典序判断

---

### 精选题解

#### 1. 作者：HoshizoraZ（★★★★☆）
**关键亮点**：
- 分步处理移位与加法操作，逻辑清晰
- 使用数学计算直接确定增量，避免暴力枚举
- 字符数组操作效率较高

**核心思路**：
```cpp
for(int i=0; i<n; i++){ // 枚举所有移位可能
    for(int j=i; j<i+n; j++) // 构建移位后的字符串
        s2[j - i] = s1[j % n];
    solve(); // 计算使首字符变0的增量
}
void solve(){
    int las = 10 - (s2[0] - '0');
    s2[0] = '0';
    for(int i=1; i<n; i++) // 计算后续字符
        s2[i] = (s2[i] - '0' + las) % 10 + '0';
    if(strcmp(s2, ans) < 0) // 更新答案
        strcpy(ans, s2);
}
```

#### 2. 作者：ztytql（★★★★☆）
**关键亮点**：
- 利用字符串拼接处理循环移位
- 直接使用字符串比较运算符
- 代码简洁易理解

**核心思路**：
```cpp
s += s; // 双倍字符串处理循环移位
for(int i=0; i<n; i++){
    string cnt = s.substr(i, n); // 获取移位后的子串
    for(int j=0; j<=9; j++){ // 枚举加法次数
        for(int k=0; k<n; k++) // 执行加法操作
            cnt[k] = (cnt[k] == '9') ? '0' : cnt[k]+1;
        ans = min(ans, cnt); // 更新答案
    }
}
```

#### 3. 作者：Level_Down（★★★★☆）
**创新点**：
- 预处理所有移位情况后统一处理加法
- 利用排序直接获取最小值
- 适合新手理解的直观实现

**核心思路**：
```cpp
for(int i=1; i<=n; i++){ // 预处理所有移位情况
    cnt = i-1;
    for(int j=1; j<=n; j++){ 
        if(cnt == n) cnt = 0;
        a[i] += s[cnt++]; 
    }
}
for(int i=1; i<=n; i++){ // 统一处理加法
    cnt = '9' - a[i][0] + 1;
    for(int j=0; j<n; j++)
        a[i][j] = (a[i][j]-'0' + cnt) % 10 + '0';
}
sort(a+1, a+1+n); // 直接排序取最小
```

---

### 关键技巧总结
1. **循环移位处理**：通过字符串拼接或双倍数组实现O(1)复杂度的移位操作
2. **增量计算优化**：数学计算代替暴力枚举加法次数（(10 - 首字符值) % 10）
3. **字典序比较**：直接使用字符串比较运算符或strcmp函数
4. **预处理思想**：提前处理所有可能的移位情况后再统一处理加法

---

### 拓展训练
1. [P1709 最小表示法](https://www.luogu.com.cn/problem/P1709) - 循环字符串的最小表示
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略应用
3. [P1368 工艺](https://www.luogu.com.cn/problem/P1368) - 循环移位与字典序结合

---
处理用时：81.26秒