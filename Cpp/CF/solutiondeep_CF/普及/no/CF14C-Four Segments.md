# 题目信息

# Four Segments

## 题目描述

Several months later Alex finally got his brother Bob's creation by post. And now, in his turn, Alex wants to boast about something to his brother. He thought for a while, and came to the conclusion that he has no ready creations, and decided to write a program for rectangles detection. According to his plan, the program detects if the four given segments form a rectangle of a positive area and with sides parallel to coordinate axes. As Alex does badly at school and can't write this program by himself, he asks you to help him.

## 样例 #1

### 输入

```
1 1 6 1
1 0 6 0
6 0 6 1
1 1 1 0
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0 0 0 3
2 0 0 0
2 2 2 0
0 2 2 2
```

### 输出

```
NO
```

# AI分析结果



### 题目翻译
# 四条线段

## 题目描述

几个月后，Alex终于通过邮寄得到了他兄弟Bob的创作。现在，Alex想向他的兄弟炫耀一些东西。他思考了一会儿，发现自己没有现成的创作，于是决定编写一个矩形检测程序。根据他的计划，该程序需要判断给定的四条线段是否能形成一个面积为正且各边平行于坐标轴的矩形。由于Alex在学校表现不好，无法独立完成这个程序，他请求你的帮助。

## 样例 #1

### 输入

```
1 1 6 1
1 0 6 0
6 0 6 1
1 1 1 0
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0 0 0 3
2 0 0 0
2 2 2 0
0 2 2 2
```

### 输出

```
NO
```

---

### 算法分类
**模拟**

---

### 题解分析与结论

题目要求判断四条线段是否能构成平行于坐标轴的矩形。核心条件包括：
1. 线段必须平行于x轴或y轴，不能退化为点。
2. 平行于x轴和y轴的线段各两条。
3. 所有端点形成四个顶点，每个顶点出现两次。

#### 精选题解

1. **TRZ_2007（5星）**
   - **亮点**：代码简洁，利用`map`统计点出现次数，同时实时判断线段方向。
   - **核心实现**：
     ```cpp
     map <pair <int,int>,int>mp;
     int x=0,y=0,cnt=0;
     for(int i=1;i<=4;i++){
         // 输入线段端点并存入map
         if(a!=c && b!=d) return 0; // 判断斜线
         x += (a==c); y += (b==d); // 统计方向
         cnt += (mp[点]==2); // 统计顶点出现次数
     }
     if(x==2 && y==2 && cnt==4) output YES;
     ```

2. **yimuhua（4星）**
   - **亮点**：逻辑清晰，通过复合条件一次性判断所有条件。
   - **核心逻辑**：
     ```cpp
     if(存在斜线 || 平行x轴数≠2 || 平行y轴数≠2 || 顶点出现次数≠4) return NO;
     ```

3. **Mistybranch（4星）**
   - **亮点**：通过排序端点验证顶点分布模式。
   - **关键代码**：
     ```cpp
     sort(pos+1, pos+9); // 按坐标排序
     // 验证排序后的点是否形成四个两两相同的组
     if(pos[1]==pos[2] && pos[3]==pos[4] && pos[5]==pos[6] && pos[7]==pos[8])...
     ```

---

### 关键思路
- **数据结构**：使用`map`或数组统计点出现次数，验证每个顶点出现两次。
- **方向验证**：统计平行于x/y轴的线段数量，确保各两条。
- **退化检测**：检查线段起点与终点是否相同。

---

### 拓展与总结
- **类似问题**：可拓展到三维空间的立方体检测（各边平行坐标轴）。
- **调试技巧**：构造包含退化线段、斜线、端点分布异常的测试用例。

---

### 推荐题目
1. [P1885 矩形](https://www.luogu.com.cn/problem/P1885) - 二维几何条件判断
2. [CF1358C Celex Update](https://codeforces.com/problemset/problem/1358/C) - 坐标路径计数
3. [P2338 [USACO14JAN]Bessie Slows Down S](https://www.luogu.com.cn/problem/P2338) - 事件模拟与坐标处理

---
处理用时：183.54秒