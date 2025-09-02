# 题目信息

# Beauty Pageant

## 题目描述

General Payne has a battalion of $ n $ soldiers. The soldiers' beauty contest is coming up, it will last for $ k $ days. Payne decided that his battalion will participate in the pageant. Now he has choose the participants.

All soldiers in the battalion have different beauty that is represented by a positive integer. The value $ a_{i} $ represents the beauty of the $ i $ -th soldier.

On each of $ k $ days Generals has to send a detachment of soldiers to the pageant. The beauty of the detachment is the sum of the beauties of the soldiers, who are part of this detachment. Payne wants to surprise the jury of the beauty pageant, so each of $ k $ days the beauty of the sent detachment should be unique. In other words, all $ k $ beauties of the sent detachments must be distinct numbers.

Help Payne choose $ k $ detachments of different beauties for the pageant. Please note that Payne cannot just forget to send soldiers on one day, that is, the detachment of soldiers he sends to the pageant should never be empty.

## 样例 #1

### 输入

```
3 3
1 2 3
```

### 输出

```
1 1
1 2
2 3 2
```

## 样例 #2

### 输入

```
2 1
7 12
```

### 输出

```
1 12 
```

# AI分析结果



# Beauty Pageant 题解中文翻译

## 题目描述

佩恩将军麾下有 $n$ 名士兵，将参加持续 $k$ 天的选美比赛。每个士兵的美观值为互不相同的正整数 $a_i$。每天需派遣一个非空小队，所有 $k$ 天的小队美观值之和必须互不相同。请构造 $k$ 种满足条件的小队方案。

## 输入样例 #1
```
3 3
1 2 3
```

## 输出样例 #1
```
1 1
1 2
2 3 2
```

## 输入样例 #2
```
2 1
7 12
```

## 输出样例 #2
```
1 12
```

---

**算法分类**: 构造

---

## 题解分析与结论

### 核心思路对比
两篇题解均采用**分层构造法**：
1. 将士兵按美观值升序排序
2. 按小队人数分层构造，每层保证：
   - 前 $x-1$ 个成员固定为最大的 $x-1$ 个元素
   - 最后一位依次选取剩余最小元素
3. 通过这种构造方式，不同层的小队和必然递增，同层内因末位元素递增而和递增，从而保证全局唯一性

### 最优题解亮点

#### Bai_R_X 题解（★★★★☆）
**关键亮点**：
- 简洁的变量控制逻辑，直接通过双重循环实现分层构造
- 及时终止机制（当输出满k个后立即return）
**核心代码**：
```cpp
for(i=1;i<=n;i++) {
    for(j=1;j<=n-i+1;j++) {
        cout<<i<<" ";
        for(kk=n;kk>n-i+1;kk--) cout<<a[kk]<<" ";
        cout<<a[j]<<endl;
        if(!(--k)) return 0;
    }
}
```

#### OIerZhao_1025 题解（★★★★☆）
**关键亮点**：
- 更明确的变量命名（x表示小队人数）
- 加入输入输出优化（ios::sync_with_stdio）
**核心代码**：
```cpp
for(x=1;x<=n;x++) {
    for(j=1;j<=n-x+1;j++) {
        cout<<x<<" ";
        for(i=n;i>n-x+1;i--) cout<<a[i]<<" ";
        cout<<a[j]<<endl;
        if(!(--k)) return 0;
    }
}
```

---

## 关键技巧总结
1. **排序预处理**：升序排列为分层构造奠定基础
2. **分层构造法**：按小队人数分层，每层利用最大元素保证层间差异
3. **末位轮换机制**：通过改变最后一个元素实现同层内的差异
4. **及时终止优化**：满足k个条件后立即退出，减少冗余计算

---

## 同类题目推荐
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）
2. P1223 排队接水（贪心排序）
3. P1106 删数问题（构造最小数）

---
处理用时：63.09秒