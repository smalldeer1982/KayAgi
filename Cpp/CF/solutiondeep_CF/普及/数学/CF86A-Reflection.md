# 题目信息

# Reflection

## 题目描述

For each positive integer $ n $ consider the integer $ ψ(n) $ which is obtained from $ n $ by replacing every digit $ a $ in the decimal notation of $ n $ with the digit $ (9-a) $ . We say that $ ψ(n) $ is the reflection of $ n $ . For example, reflection of $ 192 $ equals $ 807 $ . Note that leading zeros (if any) should be omitted. So reflection of $ 9 $ equals $ 0 $ , reflection of $ 91 $ equals $ 8 $ .

Let us call the weight of the number the product of the number and its reflection. Thus, the weight of the number $ 10 $ is equal to $ 10·89=890 $ .

Your task is to find the maximum weight of the numbers in the given range $ [l,r] $ (boundaries are included).

## 说明/提示

In the third sample weight of $ 8 $ equals $ 8·1=8 $ , weight of $ 9 $ equals $ 9·0=0 $ , weight of $ 10 $ equals $ 890 $ .

Thus, maximum value of the product is equal to $ 890 $ .

## 样例 #1

### 输入

```
3 7
```

### 输出

```
20```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
8```

## 样例 #3

### 输入

```
8 10
```

### 输出

```
890```

# AI分析结果

### 题目内容重写

对于每个正整数 $n$，考虑整数 $ψ(n)$，它是通过将 $n$ 的十进制表示中的每个数字 $a$ 替换为数字 $(9-a)$ 得到的。我们称 $ψ(n)$ 为 $n$ 的反射。例如，$192$ 的反射是 $807$。注意，前导零（如果有）应被省略。因此，$9$ 的反射是 $0$，$91$ 的反射是 $8$。

我们将一个数的权重定义为该数与其反射的乘积。因此，$10$ 的权重等于 $10 \times 89 = 890$。

你的任务是在给定的范围 $[l, r]$（包括边界）内找到权重的最大值。

### 样例

#### 样例 #1
输入：
```
3 7
```
输出：
```
20
```

#### 样例 #2
输入：
```
1 1
```
输出：
```
8
```

#### 样例 #3
输入：
```
8 10
```
输出：
```
890
```

### 题解分析与结论

各题解的思路主要集中在利用二次函数的性质来求解最大值。具体来说，权重的计算公式可以看作是一个开口向下的二次函数，其最大值出现在对称轴附近。因此，大多数题解都通过计算对称轴的位置，并根据区间 $[l, r]$ 与对称轴的关系来确定最大值。

### 所选高星题解

#### 题解1：作者：luojien (赞：11)
**星级：5星**
**关键亮点：**
- 通过观察二次函数的性质，直接计算对称轴的位置，并根据区间与对称轴的关系确定最大值。
- 代码简洁，逻辑清晰，处理了边界情况。

**核心代码：**
```cpp
int n9 = pow(10, ceil(log10(r + 1))) - 1;
if (l <= n9 / 2 && r >= n9 / 2) {
    cout << (n9 / 2) * (n9 / 2 + 1) << endl;
} else if (r < n9 / 2) {
    cout << (n9 - r) * r << endl;
} else {
    cout << (n9 - l) * l << endl;
}
```

#### 题解2：作者：DiDi123 (赞：6)
**星级：4星**
**关键亮点：**
- 通过几何画板绘图直观展示了二次函数的性质，帮助理解最大值的出现位置。
- 详细讨论了不同位数情况下的最大值计算。

**核心代码：**
```cpp
long long l,r,rr,t,xx;
double x;
cin>>l>>r;
rr=r;
while(rr)
    rr/=10,t=t*10+9;
x=t*0.5,xx=x;
if(l>x) cout<<t*l-l*l;
else if(x>r) cout<<t*r-r*r;
else cout<<t*xx-xx*xx;
```

#### 题解3：作者：naroto2022 (赞：4)
**星级：4星**
**关键亮点：**
- 详细推导了二次函数的对称轴位置，并分类讨论了区间与对称轴的关系。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
long long l,r,wr,cnt;
scanf("%lld %lld",&l,&r);
wr=log10(r);
cnt=pow(10,wr+1)-1; 
if(l>=cnt/2) printf("%lld",l*(cnt-l));
else if(r<cnt/2) printf("%lld",r*(cnt-r));
else printf("%lld",cnt/2*(cnt-cnt/2));
```

### 最优关键思路与技巧

1. **二次函数性质**：利用二次函数的对称轴位置来确定最大值，避免暴力枚举。
2. **分类讨论**：根据区间 $[l, r]$ 与对称轴的关系，分类讨论最大值的出现位置。
3. **位数处理**：通过计算数的位数，确定反射数的最大值。

### 可拓展之处

- 类似的问题可以通过分析函数的性质来优化求解，例如在区间内寻找函数的最大值或最小值。
- 可以扩展到其他进制下的反射数问题，或者考虑更复杂的函数形式。

### 推荐题目

1. **P1003 铺地毯**：考察区间覆盖与最大值问题。
2. **P1045 麦森数**：涉及大数处理与数学计算。
3. **P1059 明明的随机数**：区间内的数据处理与排序。

### 个人心得摘录

- **luojien**：通过观察二次函数的性质，直接计算对称轴的位置，避免了暴力枚举，大大提高了效率。
- **DiDi123**：通过几何画板绘图，直观展示了二次函数的性质，帮助理解最大值的出现位置，增强了题解的可读性。
- **naroto2022**：详细推导了二次函数的对称轴位置，并分类讨论了区间与对称轴的关系，代码结构清晰，易于理解。

---
处理用时：37.93秒