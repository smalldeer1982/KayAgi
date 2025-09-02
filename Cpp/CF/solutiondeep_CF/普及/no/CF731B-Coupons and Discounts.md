# 题目信息

# Coupons and Discounts

## 题目描述

The programming competition season has already started and it's time to train for ICPC. Sereja coaches his teams for a number of year and he knows that to get ready for the training session it's not enough to prepare only problems and editorial. As the training sessions lasts for several hours, teams become hungry. Thus, Sereja orders a number of pizzas so they can eat right after the end of the competition.

Teams plan to train for $ n $ times during $ n $ consecutive days. During the training session Sereja orders exactly one pizza for each team that is present this day. He already knows that there will be $ a_{i} $ teams on the $ i $ -th day.

There are two types of discounts in Sereja's favourite pizzeria. The first discount works if one buys two pizzas at one day, while the second is a coupon that allows to buy one pizza during two consecutive days (two pizzas in total).

As Sereja orders really a lot of pizza at this place, he is the golden client and can use the unlimited number of discounts and coupons of any type at any days.

Sereja wants to order exactly $ a_{i} $ pizzas on the $ i $ -th day while using only discounts and coupons. Note, that he will never buy more pizzas than he need for this particular day. Help him determine, whether he can buy the proper amount of pizzas each day if he is allowed to use only coupons and discounts. Note, that it's also prohibited to have any active coupons after the end of the day $ n $ .

## 说明/提示

In the first sample, Sereja can use one coupon to buy one pizza on the first and the second days, one coupon to buy pizza on the second and the third days and one discount to buy pizzas on the fourth days. This is the only way to order pizzas for this sample.

In the second sample, Sereja can't use neither the coupon nor the discount without ordering an extra pizza. Note, that it's possible that there will be no teams attending the training sessions on some days.

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
1 0 1
```

### 输出

```
NO
```

# AI分析结果



【中文重写题目】

# 优惠券与折扣

## 题目描述

ICPC训练季已经开始，Sereja需要为连续n天的训练订购披萨。每天恰好有a_i支队伍参加，因此每天需要订购恰好a_i个披萨。披萨店提供两种优惠：

1. **当日双份优惠**：同一天购买两个披萨
2. **连续日优惠券**：在连续两天各购买一个披萨（共两个）

Sereja可以使用任意数量的优惠券，但必须满足两个条件：① 每天订购量刚好满足需求；② 第n天结束后不得有任何未完成的连续日优惠券。请判断是否存在合法购买方案。

## 说明/提示

样例1解释：第一天使用连续券覆盖第1-2天，第二天再使用连续券覆盖第2-3天，第四天使用当日双份优惠。这是唯一合法方案。

样例2解释：第1天需要1个披萨，但第二天为0，无法使用任何优惠券完成。

## 样例 #1

### 输入
```
4
1 2 1 2
```

### 输出
```
YES
```

## 样例 #2

### 输入
```
3
1 0 1
```

### 输出
```
NO
```

【算法分类】
贪心

---

### 综合题解分析

关键思路：**奇偶性处理+逆序贪心**。每个奇数需求必须通过连续日优惠券与前一天配对，逆序处理确保合法性。

---

### 精选题解

#### 1. 作者：chenyanbo123（⭐⭐⭐⭐⭐）
**核心思路**：逆序处理每个元素，遇到奇数时前项减1，最终验证首项合法性。
```cpp
for(int i=n;i>=2;i--) {
    if(a[i]<0) return cout<<"NO",0;
    if(a[i]%2) a[i-1]--;
}
cout << (a[1]%2 ? "NO" : "YES");
```
**亮点**：代码简洁，时间复杂度O(n)。逆序处理天然避免残留优惠券问题。

#### 2. 作者：DengDuck（⭐⭐⭐）
**核心思路**：维护奇偶标记，遇到0时验证区间和为偶数。
```cpp
for(int i=1;i<=n;i++) {
    if(a==0 && flag) ans=false;
    if(a%2) flag = !flag;
}
```
**亮点**：正向遍历，空间O(1)。但需注意末尾特判，代码逻辑稍隐晦。

#### 3. 作者：LLGZ（⭐⭐⭐）
**逆向思路**：与chenyanbo123类似，但缺少边界处理注释。
```cpp
for(int i=n-1;i>=0;i--) {
    if(a[i]%2) a[i-1]--;
    if(a[i]<0) return "NO";
}
```
**不足**：数组下标从0开始，易引发越界问题。

---

### 最优思路提炼
1. **逆序处理**：从最后一天倒推，强制每个奇数需求必须由前一天的连续券覆盖。
2. **奇偶转换**：当a[i]为奇数时，a[i-1]减1（相当于强制使用一次连续券）。
3. **合法性验证**：处理过程中出现负数或首项为奇数时立即终止。

---

### 拓展建议
类似问题可考虑：
1. 链式依赖问题（如[CF12B Correct Solution]）
2. 奇偶性贪心（如[洛谷P1106 删数问题]）

---

### 相似题目推荐
1. [CF978B File Name](https://www.luogu.com.cn/problem/CF978B)（贪心消除）
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心排序）
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针贪心）

---
处理用时：63.17秒