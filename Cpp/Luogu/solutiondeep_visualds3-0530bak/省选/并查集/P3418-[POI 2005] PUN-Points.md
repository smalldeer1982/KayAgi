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



---

### 算法分类
计算几何（标准化处理与极角序列匹配）

---

### 综合分析与结论

#### 核心算法流程
1. **标准化处理**  
   - 平移：计算点集重心，将所有点平移至以重心为原点  
   - 缩放：找到最长边长度，将所有点坐标按比例缩放到最长边为1  
   - 去重：排除与重心重合的点（若有）  
2. **极角序列生成**  
   - 计算每个点的极角（角度）和归一化后的长度  
   - 按极角排序（第二关键字为长度）  
   - 计算相邻极角的差值，形成差分序列  
3. **旋转/翻转匹配**  
   - 将测试集的差分序列与原序列及其镜像序列进行循环移位匹配  
   - 若存在匹配的循环偏移量则判定相似

#### 解决难点
- **精度控制**：通过 `eps=1e-10` 处理浮点误差  
- **翻转处理**：生成镜像极角序列（按角度降序排列）  
- **循环匹配优化**：暴力遍历所有可能的循环偏移量，依赖特征唯一性快速判断  

#### 可视化设计
1. **关键步骤高亮**  
   - 平移：用红色标记重心点，其他点向重心移动的动画  
   - 缩放：动态展示最长边的缩放过程  
   - 极角排序：用不同颜色标记不同角度区间的点  
2. **循环匹配演示**  
   - 将原序列和测试序列排列成圆环，动态展示循环移位过程  
   - 匹配成功时触发绿色闪光，失败时显示红色标记  

---

### 题解评分（4⭐️）
**关键亮点**：
1. 通过标准化将问题简化为序列匹配  
2. 极角差分处理巧妙解决旋转问题  
3. 镜像序列生成处理翻转情况  

**个人心得**：
- 调试时发现必须严格处理极角计算中的象限判断（Y坐标符号）  
- 浮点精度需统一用 `eps` 比较而非直接判等  

---

### 核心代码实现
```cpp
// 标准化处理与极角计算
void preprocess(point set[], atom arr[], int &n, bool &has_center) {
    point centroid(0,0);
    for(int i=1; i<=n; i++) centroid += set[i];
    centroid /= n;

    has_center = false;
    int cnt = n;
    for(int i=1; i<=cnt; ) {
        set[i] -= centroid;
        if(set[i] == point(0,0)) {
            has_center = true;
            swap(set[i], set[cnt]);
            cnt--;
        } else {
            arr[i].len = sqrt(set[i].x*set[i].x + set[i].y*set[i].y);
            arr[i].deg = atan2(set[i].y, set[i].x); // 更稳健的极角计算
            if(arr[i].deg < 0) arr[i].deg += 2*PI;
            i++;
        }
    }
    n = cnt;
    // ...后续处理...
}

// 循环匹配检测
bool match(const atom a[], const atom b[], int n) {
    for(int delta=0; delta<n; delta++) {
        bool valid = true;
        for(int i=0; i<n; i++) {
            int j = (i + delta) % n;
            if(fabs(a[i].deg - b[j].deg) > eps || 
               fabs(a[i].len - b[j].len) > eps) {
                valid = false;
                break;
            }
        }
        if(valid) return true;
    }
    return false;
}
```

---

### 相似题目推荐
1. [P3829 [SHOI2012]信用卡凸包](https://www.luogu.com.cn/problem/P3829)  
   （计算几何标准化处理）  
2. [CF598C Nearest vectors](https://www.luogu.com.cn/problem/CF598C)  
   （极角排序与精度处理）  
3. [P1221 最多因子数](https://www.luogu.com.cn/problem/P1221)  
   （数学变换与特征匹配）  

---

### 可视化设计示例
**8位像素风格演示**：
1. 点集显示为不同颜色的像素方块  
2. 标准化过程伴随经典红白机音效  
3. 循环匹配时用闪烁箭头指示当前比对位置  
4. 成功时播放《超级马里奥》过关音效  

**Canvas动画特性**：
```javascript
// 伪代码示例
function drawRotationMatch(a, b) {
    ctx.clearRect(0, 0, W, H);
    drawCircularArrangement(a, {color: "#FF0000"}); // 红队
    drawCircularArrangement(b, {color: "#00FF00"}); // 绿队
    requestAnimationFrame(() => {
        if(currentDelta < n) checkDelta(currentDelta++);
    });
}
```

---

### 关键思路提炼
**几何问题代数化**：  
将复杂的几何变换转化为标准坐标系下的序列匹配，通过以下步骤：  
1. 平移至共同原点（重心）  
2. 缩放至统一尺度（最长边归一）  
3. 极角排序建立旋转不变性  
4. 差分序列解决循环匹配  

**模式特征提取**：  
极角+长度的双重特征保证了唯一性，使得暴力匹配在合理时间内完成。

---
处理用时：198.30秒