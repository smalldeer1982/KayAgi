# 题目信息

# Magic Box

## 题目描述

One day Vasya was going home when he saw a box lying on the road. The box can be represented as a rectangular parallelepiped. Vasya needed no time to realize that the box is special, as all its edges are parallel to the coordinate axes, one of its vertices is at point $ (0,0,0) $ , and the opposite one is at point $ (x_{1},y_{1},z_{1}) $ . The six faces of the box contain some numbers $ a_{1},a_{2},...,a_{6} $ , exactly one number right in the center of each face.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF231D/891b16d62b99e19e4dbbcc1ffa7c6345c322e404.png)The numbers are located on the box like that:

- number $ a_{1} $ is written on the face that lies on the ZOX plane;
- $ a_{2} $ is written on the face, parallel to the plane from the previous point;
- $ a_{3} $ is written on the face that lies on the XOY plane;
- $ a_{4} $ is written on the face, parallel to the plane from the previous point;
- $ a_{5} $ is written on the face that lies on the YOZ plane;
- $ a_{6} $ is written on the face, parallel to the plane from the previous point.

At the moment Vasya is looking at the box from point $ (x,y,z) $ . Find the sum of numbers that Vasya sees. Note that all faces of the box are not transparent and Vasya can't see the numbers through the box. The picture contains transparent faces just to make it easier to perceive. You can consider that if Vasya is looking from point, lying on the plane of some face, than he can not see the number that is written on this face. It is enough to see the center of a face to see the corresponding number for Vasya. Also note that Vasya always reads correctly the $ a_{i} $ numbers that he sees, independently of their rotation, angle and other factors (that is, for example, if Vasya sees some $ a_{i}=6 $ , then he can't mistake this number for $ 9 $ and so on).

## 说明/提示

The first sample corresponds to perspective, depicted on the picture. Vasya sees numbers $ a_{2} $ (on the top face that is the darkest), $ a_{6} $ (on the right face that is the lightest) and $ a_{4} $ (on the left visible face).

In the second sample Vasya can only see number $ a_{4} $ .

## 样例 #1

### 输入

```
2 2 2
1 1 1
1 2 3 4 5 6
```

### 输出

```
12
```

## 样例 #2

### 输入

```
0 0 10
3 2 3
1 2 3 4 5 6
```

### 输出

```
4
```

# AI分析结果



# Magic Box

## 题目描述

某天Vasya在回家路上看到一个盒子，这个盒子可以表示为直角六面体（长方体）。所有棱边都与坐标轴平行，其中一个顶点位于原点$(0,0,0)$，对角顶点位于$(x_1,y_1,z_1)$。六个面上各有一个数字$a_1,a_2,...,a_6$，每个面中心恰好写有一个数字。

数字的分布如下：
- $a_1$写在ZOX平面所在的面上
- $a_2$写在与之平行的对面
- $a_3$写在XOY平面所在的面上 
- $a_4$写在与之平行的对面
- $a_5$写在YOZ平面所在的面上
- $a_6$写在与之平行的对面

当Vasya从点$(x,y,z)$观察盒子时，计算他能看到的数字之和。注意：
1. 若观察点位于某面所在的平面，则不可见该面数字
2. 只需看到面中心即可读取数字

## 说明/提示

第一个样例对应图示视角，Vasya能看到$a_2$（顶部面）、$a_6$（右侧面）和$a_4$（左侧面）

## 样例 #1

### 输入
```
2 2 2
1 1 1
1 2 3 4 5 6
```

### 输出
```
12
```

## 样例 #2

### 输入
```
0 0 10
3 2 3
1 2 3 4 5 6
```

### 输出
```
4
```

---

**算法分类**：模拟

**综合题解分析**：  
所有题解均采用坐标比较法，核心思路是判断观察点是否位于各面的外侧。关键点在于正确理解三维坐标系中六个面的空间关系：

1. 当观察点坐标在某个轴的负方向（如y<0）时，可见该轴基准面（如ZOX面$a_1$）
2. 当观察点坐标超过该轴正方向边界（如y>y1）时，可见该轴对向面（如ZOX对面$a_2$）
3. 六个面需按x/y/z轴分别处理，注意输入顺序与坐标轴的对应关系

**精选题解**（评分≥4星）：

1. **zhangqiuyanAFOon2024**（⭐⭐⭐⭐⭐）  
   亮点：代码最简洁，变量命名清晰，直接对应题意中的坐标轴关系  
   ```cpp
   if(y<0) sum+=a[1];
   if(y>y1) sum+=a[2];
   if(z<0) sum+=a[3];
   if(z>z1) sum+=a[4];
   if(x<0) sum+=a[5];
   if(x>x1) sum+=a[6];
   ```

2. **Vibration886**（⭐⭐⭐⭐）  
   亮点：注释明确，输入处理规范，结构清晰  
   ```cpp
   if (my.y < 0) ans += a[1];
   if (my.y > box.y) ans += a[2];
   if (my.z < 0) ans += a[3];
   if (my.z > box.z) ans += a[4];
   if (my.x < 0) ans += a[5];
   if (my.x > box.x) ans += a[6];
   ```

3. **naroto2022**（⭐⭐⭐⭐）  
   亮点：使用标准输入输出优化，变量命名规范  
   ```cpp
   if(y<0) ans+=a[1];
   if(y>y1) ans+=a[2];
   if(z<0) ans+=a[3];
   if(z>z1) ans+=a[4];
   if(x<0) ans+=a[5];
   if(x>x1) ans+=a[6];
   ```

**关键技巧**：  
- 建立三维坐标系的空间想象，将六个面映射到x/y/z轴的边界条件
- 注意输入顺序的特殊性：第二行输入的是立方体在x/y/z轴的延伸长度（即对角顶点坐标）
- 严格处理等于边界的情况（如题设明确说明坐标位于平面时不可见）

**同类题目推荐**：  
1. [P1058 立体图](https://www.luogu.com.cn/problem/P1058) - 三维投影的模拟
2. [P1023 拼数](https://www.luogu.com.cn/problem/P1012) - 多维度的条件比较
3. [P1327 数列排序](https://www.luogu.com.cn/problem/P1327) - 坐标映射与排序结合

**调试心得摘录**：  
- "输入顺序容易混淆，第二行是立方体尺寸而非对角顶点坐标"（多篇题解强调）
- "必须严格判断>和<，等号情况要排除"（样例2验证边界条件）
- "把六个面的判断独立处理，避免复杂的三维向量运算"（简化实现的关键）

---
处理用时：54.65秒