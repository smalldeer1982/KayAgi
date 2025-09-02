# 题目信息

# Traps

## 题目描述

There are $ n $ traps numbered from $ 1 $ to $ n $ . You will go through them one by one in order. The $ i $ -th trap deals $ a_i $ base damage to you.

Instead of going through a trap, you can jump it over. You can jump over no more than $ k $ traps. If you jump over a trap, it does not deal any damage to you. But there is an additional rule: if you jump over a trap, all next traps damages increase by $ 1 $ (this is a bonus damage).

Note that if you jump over a trap, you don't get any damage (neither base damage nor bonus damage). Also, the bonus damage stacks so, for example, if you go through a trap $ i $ with base damage $ a_i $ , and you have already jumped over $ 3 $ traps, you get $ (a_i + 3) $ damage.

You have to find the minimal damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 说明/提示

In the first test case it is allowed to jump over all traps and take $ 0 $ damage.

In the second test case there are $ 5 $ ways to jump over some traps:

1. Do not jump over any trap.Total damage: $ 5 + 10 + 11 + 5 = 31 $ .
2. Jump over the $ 1 $ -st trap.Total damage: $ \underline{0} + (10 + 1) + (11 + 1) + (5 + 1) = 29 $ .
3. Jump over the $ 2 $ -nd trap.Total damage: $ 5 + \underline{0} + (11 + 1) + (5 + 1) = 23 $ .
4. Jump over the $ 3 $ -rd trap.Total damage: $ 5 + 10 + \underline{0} + (5 + 1) = 21 $ .
5. Jump over the $ 4 $ -th trap.Total damage: $ 5 + 10 + 11 + \underline{0} = 26 $ .

To get minimal damage it is needed to jump over the $ 3 $ -rd trap, so the answer is $ 21 $ .

In the third test case it is optimal to jump over the traps $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 7 $ :

Total damage: $ 0 + (2 + 1) + 0 + 0 + 0 + (2 + 4) + 0 = 9 $ .

## 样例 #1

### 输入

```
5
4 4
8 7 1 4
4 1
5 10 11 5
7 5
8 2 5 15 11 2 8
6 3
1 2 3 4 5 6
1 1
7```

### 输出

```
0
21
9
6
0```

# AI分析结果



# Traps

## 题目描述

有 $n$ 个编号为 $1$ 到 $n$ 的陷阱，你需要按顺序逐个通过。第 $i$ 个陷阱会对你造成 $a_i$ 点基础伤害。

你可以跳过最多 $k$ 个陷阱。跳过陷阱时不会受到其伤害，但会导致后续所有陷阱的伤害增加 $1$（此效果可叠加）。例如，若已跳过 $3$ 个陷阱，后续每个陷阱的伤害都会增加 $3$。

求可以承受的最小总伤害。

## 说明/提示

样例说明见原题。

---

## 题解综合分析

### 关键思路总结
所有优质题解均基于贪心策略，核心在于准确计算跳过陷阱的净收益。正确计算方式为：跳过第 $i$ 个陷阱的收益为 $a_i + i$。选择收益最大的前 $k$ 个陷阱跳过，总伤害需修正 $\frac{k(k-1)}{2}$ 的叠加误差。

### 最优题解推荐

#### 1. Eric998（5星）
**核心亮点**：
- 推导出收益公式 $a_i - (n-i) +1$，等价于 $a_i + i - (n-1)$
- 发现并修正 $\frac{k(k-1)}{2}$ 的叠加误差
- 代码简洁高效（时间复杂度 $O(n \log n)$）

**关键代码**：
```cpp
sort(a.rbegin(),a.rend()); // 按收益降序排序
for(int i=0;i<k;i++)sum-=a[i]; // 减去前k大收益
cout<<sum-(k-1)*k/2<<"\n"; // 修正叠加误差
```

#### 2. happy_dengziyue（4星）
**核心亮点**：
- 通过结构体排序维护陷阱位置信息
- 显式模拟伤害叠加过程，逻辑更直观

**关键代码**：
```cpp
sort(x+1,x+n+1,cmp); // 按a[i]+i排序
for(int i=1,cnt=0;i<=n;++i){
    if(ch[i])++cnt;   // 记录已跳过次数
    else ans += a[i] + cnt; // 计算实际伤害
}
```

#### 3. qscisQJing（4星）
**核心亮点**：
- 使用双排序策略（先按收益排序标记，再按位置排序遍历）
- 代码结构清晰易扩展

---

## 举一反三

### 类似题目推荐
1. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220) - 区间DP与贪心结合
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) - 双指针贪心策略
3. [P1209 [USACO1.3]修理牛棚](https://www.luogu.com.cn/problem/P1209) - 间隔选择贪心

### 调试心得摘录
Eric998在题解中分享："样例结果比标准答案大，差值为 $\frac{k(k-1)}{2}$，由此发现跳过的陷阱之间存在相互影响"。这提示我们：当贪心策略出现系统性偏差时，应深入分析元素间的相互作用，往往能发现隐藏的修正项。

---
处理用时：45.94秒