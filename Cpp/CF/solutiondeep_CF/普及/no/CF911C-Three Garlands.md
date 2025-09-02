# 题目信息

# Three Garlands

## 题目描述

Mishka is decorating the Christmas tree. He has got three garlands, and all of them will be put on the tree. After that Mishka will switch these garlands on.

When a garland is switched on, it periodically changes its state — sometimes it is lit, sometimes not. Formally, if $ i $ -th garland is switched on during $ x $ -th second, then it is lit only during seconds $ x $ , $ x+k_{i} $ , $ x+2k_{i} $ , $ x+3k_{i} $ and so on.

Mishka wants to switch on the garlands in such a way that during each second after switching the garlands on there would be at least one lit garland. Formally, Mishka wants to choose three integers $ x_{1} $ , $ x_{2} $ and $ x_{3} $ (not necessarily distinct) so that he will switch on the first garland during $ x_{1} $ -th second, the second one — during $ x_{2} $ -th second, and the third one — during $ x_{3} $ -th second, respectively, and during each second starting from $ max(x_{1},x_{2},x_{3}) $ at least one garland will be lit.

Help Mishka by telling him if it is possible to do this!

## 说明/提示

In the first example Mishka can choose $ x_{1}=1 $ , $ x_{2}=2 $ , $ x_{3}=1 $ . The first garland will be lit during seconds $ 1,3,5,7,... $ , the second — $ 2,4,6,8,... $ , which already cover all the seconds after the $ 2 $ -nd one. It doesn't even matter what $ x_{3} $ is chosen. Our choice will lead third to be lit during seconds $ 1,4,7,10,... $ , though.

In the second example there is no way to choose such moments of time, there always be some seconds when no garland is lit.

## 样例 #1

### 输入

```
2 2 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 2 3
```

### 输出

```
NO
```

# AI分析结果



# Three Garlands

## 题目描述

Mishka正在装饰圣诞树。他有三条彩灯，所有彩灯都会被挂在树上。之后Mishka会开启这些彩灯。

当彩灯被开启后，它会周期性地改变状态——有时亮起，有时熄灭。形式化地说，如果第$i$条彩灯在第$x$秒被开启，那么它只在$x$秒、$x+k_i$秒、$x+2k_i$秒、$x+3k_i$秒等时刻亮起。

Mishka希望以这样的方式开启彩灯：在开启后的每一秒（从三个开启时刻的最大值开始）至少有一个彩灯亮起。帮助Mishka判断是否可能实现！

## 说明/提示

样例1中，选择x1=1、x2=2、x3=1时，前两条彩灯已经覆盖所有偶数秒和奇数秒。样例2则无论如何选择都无法满足要求。

---

**算法分类**：数学（组合数学）

---

### 题解分析与结论

所有题解均基于数学推导，将问题转化为四种覆盖情形。关键思路是：三个周期系统的覆盖密度之和必须≥1（即$\frac{1}{k_1}+\frac{1}{k_2}+\frac{1}{k_3} \geq 1$），具体通过四种情况实现：

1. **存在周期1**：任意时刻全覆盖
2. **两个周期2**：奇偶交替覆盖
3. **三个周期3**：错位覆盖模3余数
4. **一个周期2+两个周期4**：通过相位调整覆盖所有时间点

---

### 精选题解

#### 1. 作者：きりと（4星）
**亮点**：使用桶计数清晰处理四种情况，代码结构严谨  
```cpp
int num[5]; // 桶数组统计各周期出现次数
if(num[1]) cout<<"YES";          // 存在周期1
else if(num[2]>=2) cout<<"YES"; // 两个周期2
else if(num[3]==3) cout<<"YES";  // 三个周期3
else if(num[2]==1&&num[4]==2) cout<<"YES"; // 2+4+4组合
```

#### 2. 作者：YuRuiH_（4星）
**亮点**：使用位标记数组快速判断，条件表达式紧凑  
```cpp
vis[k1]++; vis[k2]++; vis[k3]++;
if(vis[1] || vis[2]>=2 || vis[3]>=3 || (vis[2]==1&&vis[4]==2))
```

#### 3. 作者：Clay_L（4星）
**亮点**：将条件合并为单行判断，代码极致简洁  
```cpp
t[x]++; // 桶计数
if(t[2]>=2||t[1]||(t[4]==2&&t[2]==1)||t[3]==3) // 单行逻辑判断
```

---

### 核心实现思想
使用桶数组统计各周期出现次数，按四种覆盖情形进行条件判断。关键点：
1. 周期1可直接覆盖所有时间
2. 两个周期2需错位开启（如x=1和x=2）
3. 三个周期3需错位覆盖模3余数
4. 周期2与两个周期4需相位配合（如x=1、2、4）

---

### 拓展思考
类似周期性覆盖问题可考虑：
1. 最小公倍数与覆盖密度分析
2. 不同相位排列组合的可能性
3. 离散数学中的覆盖定理应用

---

### 推荐习题
1. P1214 等差数列（周期性覆盖）
2. P1516 青蛙的约会（模运算应用）
3. P2424 最大公约数和（周期性问题）

---
处理用时：116.92秒