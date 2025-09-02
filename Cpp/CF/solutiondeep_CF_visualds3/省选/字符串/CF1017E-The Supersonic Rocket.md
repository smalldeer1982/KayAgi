# 题目信息

# The Supersonic Rocket

## 题目描述

After the war, the supersonic rocket became the most common public transportation.

Each supersonic rocket consists of two "engines". Each engine is a set of "power sources". The first engine has $ n $ power sources, and the second one has $ m $ power sources. A power source can be described as a point $ (x_i, y_i) $ on a 2-D plane. All points in each engine are different.

You can manipulate each engine separately. There are two operations that you can do with each engine. You can do each operation as many times as you want.

1. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i+a, y_i+b) $ , $ a $ and $ b $ can be any real numbers. In other words, all power sources will be shifted.
2. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i \cos \theta - y_i \sin \theta, x_i \sin \theta + y_i \cos \theta) $ , $ \theta $ can be any real number. In other words, all power sources will be rotated.

The engines work as follows: after the two engines are powered, their power sources are being combined (here power sources of different engines may coincide). If two power sources $ A(x_a, y_a) $ and $ B(x_b, y_b) $ exist, then for all real number $ k $ that $ 0 \lt k \lt 1 $ , a new power source will be created $ C_k(kx_a+(1-k)x_b,ky_a+(1-k)y_b) $ . Then, this procedure will be repeated again with all new and old power sources. After that, the "power field" from all power sources will be generated (can be considered as an infinite set of all power sources occurred).

A supersonic rocket is "safe" if and only if after you manipulate the engines, destroying any power source and then power the engine, the power field generated won't be changed (comparing to the situation where no power source erased). Two power fields are considered the same if and only if any power source in one field belongs to the other one as well.

Given a supersonic rocket, check whether it is safe or not.

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/1f54366cb2efd6f1fd1d0617b722b5e3979dfd89.png)Those near pairs of blue and orange points actually coincide.First, manipulate the first engine: use the second operation with $ \theta = \pi $ (to rotate all power sources $ 180 $ degrees).

The power sources in the first engine become $ (0, 0) $ , $ (0, -2) $ , and $ (-2, 0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/d9732486b953667a46772450be0d244f2cb20626.png)Second, manipulate the second engine: use the first operation with $ a = b = -2 $ .

The power sources in the second engine become $ (-2, 0) $ , $ (0, 0) $ , $ (0, -2) $ , and $ (-1, -1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/f5d3a1ffc842f837240530d5f9c0ef57b3d408b7.png)You can examine that destroying any point, the power field formed by the two engines are always the solid triangle $ (0, 0) $ , $ (-2, 0) $ , $ (0, -2) $ .

In the second sample, no matter how you manipulate the engines, there always exists a power source in the second engine that power field will shrink if you destroy it.

## 样例 #1

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
0 0
```

### 输出

```
NO
```

# AI分析结果



---
# 💡 Kay的C++算法解析：The Supersonic Rocket 深入学习指南 💡

<introduction>
今天我们要分析的题目是“The Supersonic Rocket”，这道题需要判断两个引擎的动力源经过平移和旋转后是否满足“安全”条件。核心在于理解如何通过几何变换和模式匹配解决问题。让我们一步步拆解！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`几何与字符串匹配综合应用`

🗣️ **初步分析**：
解决这道题的关键在于判断两个点集的凸包是否“旋转同构”（即通过平移和旋转可以重合）。简单来说，就像判断两个多边形是否“长得一样，只是方向不同”。  
- **核心思路**：先对两个点集分别求凸包，然后将凸包的边、角等特征转化为序列（类似给凸包“拍照”成字符串），再通过KMP算法判断这两个序列是否循环同构（即一个序列旋转后能匹配另一个）。  
- **核心难点**：如何将凸包的几何特征转化为可比较的序列？如何处理旋转带来的循环同构问题？优质题解通常通过提取边长度、角度等不变量，生成序列后用KMP匹配解决。  
- **可视化设计**：我们将用8位像素风格展示凸包构建过程（点排序、上下凸壳形成），用像素方块动态显示边和角的序列生成，并用箭头动画演示KMP匹配时的模式串滑动过程。关键步骤（如凸包点入栈、序列元素生成）会伴随“叮”的音效，匹配成功时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法有效性等维度评估，以下3篇题解（评分≥4星）值得重点学习：
</eval_intro>

**题解一：cjlak1o1的凸包+三角形序列解法**  
* **点评**：此题解思路清晰，将凸包的每三个连续点构成三角形，用三边长度生成序列，利用三角形的稳定性（SSS全等）保证序列唯一性。代码中使用Andrew算法求凸包，KMP匹配序列，边界处理（如凸包退化为直线的情况）严谨。亮点在于用“三角形三边”替代单一的边或角，避免了浮点数角度计算的精度问题，代码可读性高（变量名如`cnt1`、`cnt2`明确表示序列长度）。

**题解二：KKarshilov的边+角序列解法**  
* **点评**：此题解直接提取凸包的边长度和相邻边的夹角，生成“边-角-边-角”序列，再通过KMP判断循环同构。代码中凸包构建（`ConvexHull`函数）和KMP匹配（`KmpSearch`函数）逻辑清晰，注释详细。亮点是将几何特征转化为序列的思路直观，适合理解凸包与字符串匹配的结合。

**题解三：Nelofus的哈希匹配解法**  
* **点评**：此题解用哈希函数将凸包的角信息压缩为哈希值，通过比较哈希值判断循环同构。代码中使用双哈希（pair类型）降低冲突概率，随机生成哈希基数增加鲁棒性。亮点是哈希方法高效，避免了长序列的存储和匹配，适合处理大规模数据。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决此题时，我们常遇到以下核心难点，结合优质题解的经验，总结应对策略：
</difficulty_intro>

1.  **关键点1：如何求凸包？**  
    * **分析**：凸包是点集的最小凸多边形，包含所有点。Andrew算法通过排序后分别构建上下凸壳，是最常用的凸包算法。优质题解中，凸包构建时需注意去重（所有点不同）和边界处理（如点共线时凸包退化为线段）。  
    * 💡 **学习笔记**：凸包构建的关键是排序后用叉积判断点是否在当前凸壳的“右侧”，若在则弹出栈顶。

2.  **关键点2：如何将凸包转化为可比较的序列？**  
    * **分析**：直接比较凸包点坐标无意义（因可旋转平移），需提取“不变量”。优质题解中，边长度（平移旋转后不变）和相邻边夹角（旋转后不变）是常用不变量。例如，cjlak1o1用三个边构成三角形（SSS全等），KKarshilov用“边-角”交替序列。  
    * 💡 **学习笔记**：选择不变量时，需保证不同构的凸包生成不同序列，同构的生成循环同构序列。

3.  **关键点3：如何判断两个序列是否循环同构？**  
    * **分析**：循环同构指一个序列旋转后与另一个相同（如ABC和BCA）。优质题解中，将其中一个序列倍长（如ABC→ABCABC），用KMP算法匹配另一个序列。若能匹配，则说明循环同构。  
    * 💡 **学习笔记**：KMP的next数组预处理模式串，可高效实现循环匹配。

### ✨ 解题技巧总结
- **几何特征提取**：选择平移、旋转下不变的量（如边长、夹角）作为序列元素。  
- **循环同构处理**：倍长序列+KMP匹配是解决循环同构的经典方法。  
- **精度处理**：浮点数比较时需设置`eps`（如`1e-8`），避免因精度误差导致错误。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，采用凸包构建+边序列生成+KMP匹配的经典思路：
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码综合了cjlak1o1和KKarshilov的思路，先求凸包，再生成边长度序列，最后用KMP判断循环同构。  
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double eps = 1e-8;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

typedef Point Vector;
Vector operator-(Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
double Length(Vector A) { return sqrt(A.x * A.x + A.y * A.y); }

// 凸包构建（Andrew算法）
vector<Point> ConvexHull(vector<Point> p) {
    int n = p.size(), k = 0;
    if (n <= 1) return p;
    sort(p.begin(), p.end());
    vector<Point> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) 
        while (k >= 2 && Cross(ch[k-1] - ch[k-2], p[i] - ch[k-2]) <= eps) k--;
    for (int i = n - 2, t = k; i >= 0; ch[k++] = p[i--]) 
        while (k > t && Cross(ch[k-1] - ch[k-2], p[i] - ch[k-2]) <= eps) k--;
    ch.resize(k - (n > 1));
    return ch;
}

// 生成边长度序列
vector<double> getEdges(const vector<Point>& ch) {
    vector<double> edges;
    int n = ch.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        edges.push_back(Length(ch[j] - ch[i]));
    }
    return edges;
}

// KMP预处理next数组
void getNext(const vector<double>& pat, vector<int>& next) {
    int m = pat.size();
    next.resize(m, 0);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && fabs(pat[i] - pat[j]) > eps) j = next[j - 1];
        if (fabs(pat[i] - pat[j]) <= eps) ++j;
        next[i] = j;
    }
}

// KMP匹配
bool kmp(const vector<double>& txt, const vector<double>& pat, const vector<int>& next) {
    int n = txt.size(), m = pat.size();
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && fabs(txt[i] - pat[j]) > eps) j = next[j - 1];
        if (fabs(txt[i] - pat[j]) <= eps) ++j;
        if (j == m) return true;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Point> p1(n), p2(m);
    for (int i = 0; i < n; ++i) cin >> p1[i].x >> p1[i].y;
    for (int i = 0; i < m; ++i) cin >> p2[i].x >> p2[i].y;

    vector<Point> ch1 = ConvexHull(p1);
    vector<Point> ch2 = ConvexHull(p2);
    if (ch1.size() != ch2.size()) { cout << "NO" << endl; return 0; }
    if (ch1.size() <= 1) { cout << "YES" << endl; return 0; }

    vector<double> edges1 = getEdges(ch1);
    vector<double> edges2 = getEdges(ch2);
    vector<double> txt = edges1;
    txt.insert(txt.end(), edges1.begin(), edges1.end()); // 倍长序列

    vector<int> next;
    getNext(edges2, next);
    bool matched = kmp(txt, edges2, next);
    cout << (matched ? "YES" : "NO") << endl;
    return 0;
}
```
* **代码解读概要**：代码首先读取输入点集，用Andrew算法求凸包；若凸包大小不同直接返回NO。然后提取凸包的边长度生成序列，将第一个序列倍长后，用KMP算法匹配第二个序列，判断是否循环同构。

---
<code_intro_selected>
接下来，赏析优质题解的核心代码片段：
</code_intro_selected>

**题解一：cjlak1o1的三角形序列生成**  
* **亮点**：用三个连续点构成三角形，提取三边长度，利用SSS全等保证序列唯一性。  
* **核心代码片段**：
```cpp
void build1(int n) {
    for(int i=3; i<=n; i++) {
        a[cnt1++] = _dis(st[i-1], st[i-2]);
        a[cnt1++] = _dis(st[i], st[i-1]);
        a[cnt1++] = _dis(st[i], st[i-2]);
    }
}
```
* **代码解读**：`st`数组存储凸包点，`i`从3开始遍历凸包点。每三个连续点`st[i-2], st[i-1], st[i]`构成三角形，计算三边长度并存入数组`a`。这样生成的序列包含三角形的三边信息，同构的凸包会生成相同的三角形序列。  
* 💡 **学习笔记**：三角形的三边长度是SSS全等的关键，能唯一确定三角形形状，避免角度计算的精度问题。

**题解二：KKarshilov的边+角序列生成**  
* **亮点**：直接提取边长度和相邻边的夹角，生成“边-角”交替序列，直观反映凸包形状。  
* **核心代码片段**：
```cpp
for(int i = 0; i < sum1; i++) {
    S[cnts++] = Length(c1[i + 1] - c1[i]);
    S[cnts++] = Angle(c1[i + 2] - c1[i + 1], c1[i + 1] - c1[i]);
}
```
* **代码解读**：`c1`存储凸包点，`i`遍历凸包边。`Length`计算当前边长度，`Angle`计算当前边与下一条边的夹角（弧度值）。序列`S`由“边长度+夹角”交替组成，同构的凸包会生成循环同构的序列。  
* 💡 **学习笔记**：边和角是凸包的基本特征，交替存储能全面反映形状，适合KMP匹配。

**题解三：Nelofus的哈希匹配**  
* **亮点**：用双哈希压缩角信息，高效判断循环同构。  
* **核心代码片段**：
```cpp
Hash ans = {0, 0};
for (int i = 1; i < Conv2.size() - 1; i++) {
    Vector v1 = ft(Conv2[i], Conv2[i - 1]), v2 = ft(Conv2[i], Conv2[i + 1]);
    i64 val = reg(Dot(v1, v1)) * reg(Dot(v1, v2)) % mod;
    ans = ans * base + make_pair(val, val);
}
```
* **代码解读**：`Conv2`是第二个凸包，`v1`和`v2`是当前点的前后向量。`val`由向量点积计算得到，作为哈希值的一部分。通过累乘基数（`base`）和累加`val`，将角信息压缩为哈希值。同构的凸包会生成相同的哈希值。  
* 💡 **学习笔记**：哈希方法将长序列压缩为短值，适合快速比较，但需注意哈希冲突（双哈希降低概率）。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解凸包构建和KMP匹配过程，我们设计一个“像素几何探险”动画，用8位像素风格展示关键步骤！
</visualization_intro>

  * **动画演示主题**：`像素几何探险——凸包与序列的秘密`  
  * **核心演示内容**：凸包构建（点排序、上下凸壳形成）→ 序列生成（边长度/夹角提取）→ KMP匹配（模式串滑动匹配）。  
  * **设计思路简述**：8位像素风格（FC红白机色调）营造复古氛围；凸包点用不同颜色方块表示，边用虚线连接，序列用像素条动态生成；关键步骤（如凸包点入栈、序列元素生成）伴随“叮”音效，匹配成功时播放胜利音效，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕左半部分为“点集区”（像素网格背景），右半部分为“序列区”（水平排列的像素条）。  
        - 控制面板：单步/自动播放按钮、速度滑块（1-5倍速）、重置按钮。  
        - 播放8位风格BGM（如《超级马里奥》经典旋律变奏）。

    2.  **凸包构建演示**：  
        - 输入点集用彩色像素方块随机分布（如红色代表第一个引擎，蓝色代表第二个）。  
        - 排序动画：点按x坐标（y坐标辅助）从左到右滑动到排序位置。  
        - 上下凸壳构建：栈顶点用金色边框高亮，若新点导致凸壳“右转”（叉积≤0），栈顶点弹出（像素方块消失），新点入栈（滑入栈顶），伴随“咔嚓”音效。

    3.  **序列生成演示**：  
        - 凸包边用绿色虚线连接，边长度用数字标签显示（如“长度=3”）。  
        - 序列区逐帧生成像素条（高度=边长，颜色=边长度的哈希色）。例如，第一条边生成时，像素条从左到右扩展，伴随“滴”音效。

    4.  **KMP匹配演示**：  
        - 倍长序列（如原序列ABC→ABCABC）用黄色像素条显示，模式串（如BCA）用紫色像素条覆盖。  
        - 匹配时，模式串从左到右滑动，当前比较位置用红色箭头标记。若匹配成功（像素条高度相同），箭头变绿；若失败，箭头变红并回退（根据next数组）。  
        - 完全匹配时，所有像素条闪烁金色，播放“胜利”音效（如《超级玛丽》吃金币音效）。

  * **旁白提示**：  
    - （凸包构建时）“看！点按x坐标排好队了，现在要构建下凸壳，栈顶的点如果让凸壳右转，就要弹出哦～”  
    - （序列生成时）“每条边的长度是不变量，平移旋转都不会改变它！现在把这些长度存成序列吧～”  
    - （KMP匹配时）“模式串在倍长序列中滑动，找到匹配就说明两个凸包是旋转同构的！”

<visualization_conclusion>
通过这样的动画，我们能直观看到凸包如何从点集“生长”出来，序列如何记录凸包特征，以及KMP如何高效匹配循环同构。像素风格和音效让学习过程更有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是凸包构建与循环同构判断，这类思路还能解决以下问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 多边形相似性判断（如判断两个多边形是否旋转缩放后重合）。  
    - 点集特征提取（如提取轮廓的边、角序列用于图像识别）。  
    - 字符串循环同构问题（如判断两个字符串是否为循环移位）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P2742** - `【模板】凸包`  
        * 🗣️ **推荐理由**：直接练习凸包构建，巩固Andrew算法实现。  
    2.  **洛谷 P3375** - `【模板】KMP字符串匹配`  
        * 🗣️ **推荐理由**：掌握KMP算法核心，为解决循环同构问题打基础。  
    3.  **洛谷 P1379** - `八数码难题`  
        * 🗣️ **推荐理由**：涉及状态空间搜索和模式匹配，训练将问题转化为序列匹配的思维。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，对我们很有启发：
</insights_intro>

> **参考经验 (来自Hoks)**：“在计算角度时，直接用`acos`会因浮点数精度问题出现`nan`，需要特判或设置`eps`。”  
> **点评**：浮点数计算的精度问题是几何题的常见坑。设置`eps`（如`1e-8`）比较两个浮点数是否相等，能有效避免`nan`错误。这提醒我们，处理几何问题时需特别注意精度控制。

-----

<conclusion>
通过分析“The Supersonic Rocket”，我们掌握了凸包构建、序列生成和KMP匹配的综合应用。编程的关键在于将复杂问题拆解为可处理的子问题（如凸包→序列→匹配）。希望大家多练习，在实践中深化理解！下次再见～💪
</conclusion>

---
处理用时：143.79秒