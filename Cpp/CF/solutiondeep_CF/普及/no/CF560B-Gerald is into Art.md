# 题目信息

# Gerald is into Art

## 题目描述

Gerald bought two very rare paintings at the Sotheby's auction and he now wants to hang them on the wall. For that he bought a special board to attach it to the wall and place the paintings on the board. The board has shape of an $ a_{1}×b_{1} $ rectangle, the paintings have shape of a $ a_{2}×b_{2} $ and $ a_{3}×b_{3} $ rectangles.

Since the paintings are painted in the style of abstract art, it does not matter exactly how they will be rotated, but still, one side of both the board, and each of the paintings must be parallel to the floor. The paintings can touch each other and the edges of the board, but can not overlap or go beyond the edge of the board. Gerald asks whether it is possible to place the paintings on the board, or is the board he bought not large enough?

## 说明/提示

That's how we can place the pictures in the first test:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF560B/a420fb4a39004e44f1aae29f62afa4982709f4ea.png)

And that's how we can do it in the third one.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF560B/c256a9120b8a1034b03a87f01ea4cc344f10e71d.png)

## 样例 #1

### 输入

```
3 2
1 3
2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 5
3 3
3 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 2
2 3
1 2
```

### 输出

```
YES
```

# AI分析结果



【题目翻译】
# Gerald 喜欢艺术

## 题目描述

Gerald 在苏富比拍卖会上买了两幅罕见的画作，现在想把它们挂在墙上。为此他买了一块特殊板子固定在墙上放置画作。板子形状为 $a_{1}×b_{1}$ 的矩形，两幅画的形状分别为 $a_{2}×b_{2}$ 和 $a_{3}×b_{3}$ 的矩形。

由于这些画作采用抽象艺术风格，具体如何旋转并不重要，但板子和每幅画的一边必须平行于地面。画作可以相互接触和接触板子边缘，但不能重叠或超出板子边缘。Gerald 想知道他买的板子是否足够大来放置这两幅画？

## 说明/提示

第一组测试样例的摆放方式：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF560B/a420fb4a39004e44f1aae29f62afa4982709f4ea.png)

第三组测试样例的摆放方式：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF560B/c256a9120b8a1034b03a87f01ea4cc344f10e71d.png)

## 样例 #1

### 输入
```
3 2
1 3
2 1
```

### 输出
```
YES
```

## 样例 #2

### 输入
```
5 5
3 3
3 3
```

### 输出
```
NO
```

## 样例 #3

### 输入
```
4 2
2 3
1 2
```

### 输出
```
YES
```

【算法分类】  
枚举

【题解分析】  
所有题解均基于暴力枚举思想，通过尝试两个画作的所有旋转组合（每个画作有 2 种方向）与两种基础摆放方式（横向并排、纵向叠放），共 8 种情况。核心判断条件为：
1. 横向总长度 ≤ 板子长度 且 纵向最大高度 ≤ 板子宽度
2. 纵向总高度 ≤ 板子宽度 且 横向最大长度 ≤ 板子长度

【优质题解推荐】  
1. **JHR100330（★★★★★）**  
   关键亮点：  
   - 图文并茂解释 8 种情况，直观展示所有旋转组合  
   - 代码采用清晰的条件分支结构，每个条件对应一种旋转组合  
   - 包含完整的数学推导说明，解释横向/纵向的判定逻辑  

   核心代码：  
   ```cpp
   if(a2 + a3 <= a1 && max(b2, b3) <= b1) return true;
   if(a2 + a3 <= b1 && max(b2, b3) <= a1) return true;
   // 其他 6 种情况类似...
   ```

2. **Alex_Wei（★★★★☆）**  
   关键亮点：  
   - 通过 swap 操作实现优雅的旋转枚举  
   - 代码结构紧凑，利用 exit(0) 提前终止检测  
   - 每行 swap 对应一种旋转状态，逻辑层次清晰  

   核心代码：  
   ```cpp
   swap(a2,b2);  // 旋转第二幅画
   if(a2+a3<=a1&&max(b2,b3)<=b1) puts("YES"),exit(0);
   swap(a3,b3);  // 旋转第三幅画
   // 继续其他组合...
   ```

3. **Eterna（★★★★☆）**  
   关键亮点：  
   - 极致简洁的代码风格，单函数完成所有判断  
   - 利用逗号运算符压缩代码行数，适合竞赛速写  
   - 通过 exit(0) 实现快速返回，提升执行效率  

   核心代码：  
   ```cpp
   is(),swap(a2,b2),is(),swap(a3,b3),is(),swap(a2,b2),is();
   ```

【关键思路总结】  
1. **旋转枚举技巧**：通过交换长宽实现 90° 旋转，每个画作有 2 种状态，共 $2^3=8$ 种组合  
2. **双模式检测**：对每个旋转组合同时检测横向并排（总长约束）和纵向叠放（总高约束）两种布局方式  
3. **极值处理**：使用 max() 函数处理两画作另一维度的极值约束  
4. **快速返回优化**：发现合法情况立即输出结果并终止程序，减少不必要的计算  

【拓展延伸】  
相似题目推荐：  
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 二维空间覆盖检测  
2. [P1059 矩形覆盖](https://www.luogu.com.cn/problem/P1059) - 多个矩形的最小包围盒  
3. [P1514 引水入城](https://www.luogu.com.cn/problem/P1514) - 二维区域覆盖与连通性判断  

调试技巧：  
- 在纸上绘制坐标系辅助理解旋转后的尺寸变化  
- 使用对称性减少代码量（如板子自身旋转等价于交换其长宽）  
- 注意输入顺序（第一个尺寸是板子，后两个是画作）

---
处理用时：71.93秒