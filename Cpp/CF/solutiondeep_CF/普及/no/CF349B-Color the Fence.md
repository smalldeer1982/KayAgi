# 题目信息

# Color the Fence

## 题目描述

Igor has fallen in love with Tanya. Now Igor wants to show his feelings and write a number on the fence opposite to Tanya's house. Igor thinks that the larger the number is, the more chance to win Tanya's heart he has.

Unfortunately, Igor could only get $ v $ liters of paint. He did the math and concluded that digit $ d $ requires $ a_{d} $ liters of paint. Besides, Igor heard that Tanya doesn't like zeroes. That's why Igor won't use them in his number.

Help Igor find the maximum number he can write on the fence.

## 样例 #1

### 输入

```
5
5 4 3 2 1 2 3 4 5
```

### 输出

```
55555
```

## 样例 #2

### 输入

```
2
9 11 1 12 5 8 9 10 6
```

### 输出

```
33
```

## 样例 #3

### 输入

```
0
1 1 1 1 1 1 1 1 1
```

### 输出

```
-1
```

# AI分析结果



# 颜色篱笆

## 题目描述

伊戈尔想用$v$升颜料在篱笆上写一个数字来追求塔尼娅。每个数字$d$需要$a_d$升颜料，且不能使用数字0。求能写出的最大数字。

## 算法分类
贪心

---

## 题解对比与结论

### 最优思路提炼
1. **贪心分两步**：先构造最长可能位数（选择单位消耗最小的数字），再逐步提升高位数值（用剩余颜料替换更大数字）
2. **关键技巧**：
   - 选择最小消耗时若多个数字相同，取数值最大的
   - 替换时从高位到低位，每次尽可能替换为最大的可行数字
   - 处理余数时利用`剩余颜料=总余量+回收的颜料`进行计算

### 精选题解（评分≥4星）

#### Showball（5星）
**亮点**：
- 明确分步处理构造与优化阶段
- 代码结构清晰，包含错误调试经验
- 采用vector存储结果便于操作

**核心代码**：
```cpp
int minn = 1e6, val = 1;
// 找最小消耗且最大的数字
for(int i=1;i<=9;i++) if(a[i]==minn) val = max(val, i); 

vector<int> ans(v/a[val], val); // 初始构造
v %= a[val];

// 从高位开始替换
for(int i=0; i<ans.size(); i++){
    for(int j=9; j>val; j--){
        if(v + a[val] >= a[j]){
            ans[i] = j;
            v -= (a[j] - a[val]);
            break;
        }
    }
}
```

#### Special_Tony（4星）
**亮点**：
- 代码简洁高效，使用goto优化流程
- 优先处理无解情况

**核心实现**：
```cpp
int minx = 1e9, mini;
for(int i=1; i<=9; i++){
    if(a[i] <= minx){
        minx = a[i];
        mini = i; // 自动取最大的i（因遍历顺序）
    }
}
while(v >= minx) 构造数字...

// 替换逻辑
for(int i=1; i<=len; i++){
    for(int j=9; j>mini; j--){
        if(a[j] - minx <= x){
            x -= (a[j] - minx);
            cout << j;
            goto there; // 跳转优化流程
        }
    }
    // 未替换时输出原数字
    there:;
}
```

#### wkjwkj（4星）
**亮点**：
- 使用vector存储结果
- 明确标注两个贪心阶段

**关键代码**：
```cpp
vector<int> ans;
while(v >= minv) ans.push_back(id), v -= minv;

for(int i=0; i<ans.size(); i++){
    for(int j=9; j>id; j--){
        if(a[j] - minv <= v){
            ans[i] = j;
            v -= a[j] - minv;
            break;
        }
    }
}
```

---

## 同类题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略选择
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 构造最大数
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 贪心+排序组合

---
处理用时：72.08秒