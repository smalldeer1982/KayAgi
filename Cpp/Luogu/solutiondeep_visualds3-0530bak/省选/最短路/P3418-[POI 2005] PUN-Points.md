# 题目信息

# [POI 2005] PUN-Points

## 题目描述

A set of grid points in a plane (points whose both cartesian coordinates are integers) which we shall refer to as the pattern, as well as a group of other sets of grid points on the plane are given. We would like to know which of the sets are similar to the pattern, i.e. which of them can be transformed by rotations, translations, reflections and dilations so that they are identical to the pattern. For instance: the set of points $\{(0,0),(2,0),(2,1)\}$ is similar to the set $\{(6,1),(6,5),(4,5)\}$, it is however not similar to the set $\{(4,0),(6,0),(5,-1)\}$.

TaskWrite a programme which:

reads from the standard input the description of the pattern and the family of the investigated sets of points,determines which of the investigated sets of points are similar to the pattern,writes the outcome to the standard output.

题目描述：


给出一个包含平面上格点的集合（格点的定义是xy坐标均为整数），我们将其称作“模式集合”。


接下来给出另外的几个包含平面上点的集合。我们想要考察后面给出的哪些集合和“模式集合”是“相似”的，即：该集合可以通过 旋转，平移，翻转，和缩放 使得该集合和“模式集合”完全相同。


例：{(0,0),(2,0),(2,1)}这个集合和{(6,1),(6,5),(4,5)}这个集合是相似的，但和{(4,0),(6,0),(5,-1)}这个集合是不相似的。


任务：


写一个程序，使得


能从标准输入读取“模式集合”和需要考察（是否相似）的集合，判断哪些集合和“模式集合”相似，并将结果输出到标准输出


输入格式：


标准输入的第一行有一个整数 k (1<=k<=25000)，代表“模式集合”中的点数


接下来k行，每行两个数，用一个空格分隔，第i+1行的两个数分别代表“模式集合”中第i个点的x坐标和y坐标(-20000<=x,y<=20000)


“模式集合”中的点两两不同。


接下来一行一个整数n，代表有n个需要考察的集合


接下来有n个对需要考察的集合的描述：


每个描述的第一行包含一个整数l，代表该集合中的点数(1<=l<=25000)


接下来l行每行包含该集合中一个点的x坐标和y坐标，用一个空格分隔(-20000<=x,y<=20000，为整数)


包含在同一集合中的点两两不同。


输出格式：


你的程序应该向标准输出流输出n行，每行代表对于一个需要考察的集合的结果。


如果第i个需要考察的集合与“模式集合”相似，则第i行应包含单词TAK，即波兰语中的yes


否则第i行应包含单词NIE，即波兰语中的no


## 样例 #1

### 输入

```
3
0 0
2 0
2 1
2
3
4 1
6 5
4 5
3
4 0
6 0
5 -1```

### 输出

```
TAK
NIE```

# AI分析结果



**唯一算法分类**  
计算几何 + 模式匹配

---

### **综合分析与结论**  
**核心思路**：通过平移、缩放将点集标准化，利用极角差分序列进行旋转/反射模式匹配。  
**难点**：处理浮点精度、极角排序、循环序列匹配、特殊点（重心重合点）处理。  
**算法流程**：  
1. **平移**：将点集重心移至原点，排除与重心重合的点。  
2. **缩放**：以最长边长度为基准，将所有点缩放至单位长度。  
3. **极角差分**：对极角排序后的点计算角度差，形成唯一性特征序列。  
4. **循环匹配**：暴力枚举旋转偏移，判断是否与模式序列或其镜像匹配。  

**可视化设计**：  
- **像素化坐标**：用16位色块表示点位置，平移/缩放时显示动态移动。  
- **极角射线**：以不同颜色绘制极角排序后的连接线。  
- **差分序列**：在Canvas右侧以条形图展示角度差，匹配时高亮对比区域。  
- **音效**：匹配成功时播放8-bit胜利音效，失败时短促蜂鸣。  

---

### **题解清单**  
**4星题解（作者：oscar）**  
- **亮点**：极角差分+暴力循环匹配简化问题，特判重心重合点，规避KMP复杂度。  
- **优化**：使用相对角度差而非绝对极角，避免固定旋转角计算。  
- **心得**：通过浮点精度控制（eps=1e-10）解决卡精度问题。  

---

### **代码核心逻辑**  
```cpp
// 标准化点集（模式集预处理）
point c1(0,0);
for(int i=1;i<=n;i++) c1 += set1[i];
c1 /= n;
// 平移至重心，排除重合点
for(int i=1;i<=n;i++) {
    set1[i] -= c1;
    if(set1[i] == point(0,0)) { /* 处理重合点 */ }
    // 计算极角与长度
    arr1[i].deg = atan2(set1[i].y, set1[i].x); 
}
sort(arr1, arr1+n); // 极角排序
// 生成差分序列
for(int i=n;i>=2;i--) 
    arr1[i].deg -= arr1[i-1].deg;
arr1[1].deg += 2*PI - maxdeg;

// 匹配检测（查询集处理类似）
bool match(atom a[], atom b[], int len) {
    for(int delta=0; delta<len; delta++) {
        bool flag = true;
        for(int i=0; i<len; i++) 
            if(a[i] != b[(i+delta)%len]) { flag=false; break; }
        if(flag) return true;
    }
    return false;
}
```

---

### **同类型题推荐**  
1. **P2945** [Symmetric Cross](https://www.luogu.com.cn/problem/P2945) - 二维模式对称检测  
2. **P3829** [信用卡凸包](https://www.luogu.com.cn/problem/P3829) - 几何变换与形状匹配  
3. **P7297** [Teleport](https://www.luogu.com.cn/problem/P7297) - 坐标系转换与路径相似性  

---

### **可视化实现要点**  
1. **像素动画**：  
   - 使用<canvas>绘制网格，点坐标映射到32x32像素块。  
   - 平移时显示拖尾效果，缩放时点大小渐变。  
2. **极角射线**：  
   - 极角排序后，用不同颜色线段连接点与原点，显示角度顺序。  
3. **差分条形图**：  
   - 在画面右侧绘制角度差直方图，匹配时触发颜色脉冲。  
4. **音效系统**：  
   - 使用Web Audio API生成方波音效，匹配成功时播放3音阶上升旋律。  

**交互示例**：  
```javascript
// 伪代码：极角射线绘制
function drawPolarLines(ctx, points) {
    points.sort((a,b) => a.deg - b.deg);
    points.forEach(p => {
        ctx.beginPath();
        ctx.moveTo(origin.x, origin.y);
        ctx.lineTo(p.x*scale, p.y*scale);
        ctx.strokeStyle = `hsl(${p.deg*180/PI}, 80%, 50%)`;
        ctx.stroke();
    });
}
```

---
处理用时：74.38秒