# 题目信息

# Help Victoria the Wise

## 题目描述

Vasilisa the Wise from a far away kingdom got a present from her friend Helga the Wise from a farther away kingdom. The present is a surprise box, yet Vasilisa the Wise doesn't know yet what the surprise actually is because she cannot open the box. She hopes that you can help her in that.

The box's lock is constructed like that. The box itself is represented by an absolutely perfect black cube with the identical deepening on each face (those are some foreign nanotechnologies that the far away kingdom scientists haven't dreamt of). The box is accompanied by six gems whose form matches the deepenings in the box's faces. The box can only be opened after it is correctly decorated by the gems, that is, when each deepening contains exactly one gem. Two ways of decorating the box are considered the same if they can be obtained one from the other one by arbitrarily rotating the box (note that the box is represented by a perfect nanotechnological cube)

Now Vasilisa the Wise wants to know by the given set of colors the following: in how many ways would she decorate the box in the worst case to open it? To answer this question it is useful to know that two gems of one color are indistinguishable from each other. Help Vasilisa to solve this challenging problem.

## 样例 #1

### 输入

```
YYYYYY
```

### 输出

```
1
```

## 样例 #2

### 输入

```
BOOOOB
```

### 输出

```
2
```

## 样例 #3

### 输入

```
ROYGBV
```

### 输出

```
30
```

# AI分析结果



# Help Victoria the Wise

## 题目描述

瓦西里萨智者收到了一个神秘立方体礼盒，需用六颗宝石镶嵌其六个面。两个镶嵌方案视为相同若可通过立方体旋转相互得到。给定宝石颜色序列（同色宝石不可区分），求不同镶嵌方案数。

## 样例

### 样例输入1
```
YYYYYY
```
### 样例输出1
```
1
```

### 样例输入2
```
BOOOOB
```
### 样例输出2
```
2
```

### 样例输入3
```
ROYGBV
```
### 样例输出3
```
30
```

---

## 算法分类
组合数学

---

## 题解分析与结论

### 关键思路
1. **颜色分布归一化**：统计各颜色出现次数并排序，生成唯一标识码（如`114`表示各颜色出现次数为1,1,4）
2. **预计算等价类**：通过数学分析/暴力枚举确定11种颜色分布对应的等价类数目
3. **查表法**：将归一化的颜色分布映射到预计算的方案数

### 高分题解推荐

#### 1. ikunTLE（4星）
**亮点**：清晰的预处理映射表，利用字符频率直接计算标识码  
**核心代码**：
```cpp
sort(a+1,a+7); // 排序颜色出现次数
int x=0;
for(int i=1;i<=6;++i) x=x*10+a[i]; // 生成标识码
ans[x] = precomputed_value; // 查表输出
```

#### 2. Mint_Flipped（4星）
**亮点**：详细说明颜色分布与方案数的对应关系  
**个人心得**："建议dfs一下"提示了数学分析的替代方案  
**核心实现**：
```cpp
sort(b+1,b+7); // 同前
int ans = 0;
fo2(i,6) ans=ans*10+b[i]; // 生成标识码
printf("%d\n",a[ans]); // 查表
```

#### 3. _int123_（4星）
**亮点**：代码极简，直接硬编码映射关系  
**关键技巧**：将颜色转换为数字索引处理  
**代码片段**：
```cpp
sort(b+1,b+6+1);
for(int i=1;i<=6;i++) num=num*10+b[i];
// 直接根据num值输出对应方案数
```

---

## 拓展与相似题目
1. [CF1081D] (需处理旋转对称性的最大值问题)  
2. [洛谷P1976] 套圈游戏（二维旋转等价类）  
3. [CF232D] 立方体染色方案扩展版  

---

## 关键实现代码
```cpp
// 以ikunTLE代码为例的核心逻辑
int main(){
    scanf("%s",s+1);
    for(int i=1;i<=6;++i) ++tong[s[i]]; // 统计颜色
    int a[] = {0, tong['R'], tong['O'], ...}; // 填充各颜色计数
    sort(a+1,a+7); // 非零部分排序
    int x = 0;
    for(int i=1;i<=6;++i) x = x*10 + a[i]; // 生成标识码
    printf("%d\n", ans[x]); // 查预定义表输出
}
```

---

## 总结技巧
1. **立方体对称性处理**：24种旋转等价类可通过数学分析预先计算
2. **标准化思想**：通过排序将分布转化为唯一标识
3. **打表法的合理应用**：当数学推导复杂时，小规模数据可预计算答案

---

## 个人心得摘录
"我这蒟蒻太菜，只知道打表" —— boluo2014  
"建议dfs一下" —— Mint_Flipped（提示暴力验证的可能性）  
"绕体对角线旋转的12种情况" —— Ghosty_Neutrino（详细分析旋转对称性）

---
处理用时：57.97秒