# 题目信息

# Zebra Tower

## 题目描述

Little Janet likes playing with cubes. Actually, she likes to play with anything whatsoever, cubes or tesseracts, as long as they are multicolored. Each cube is described by two parameters — color $ c_{i} $ and size $ s_{i} $ . A Zebra Tower is a tower that consists of cubes of exactly two colors. Besides, the colors of the cubes in the tower must alternate (colors of adjacent cubes must differ). The Zebra Tower should have at least two cubes. There are no other limitations. The figure below shows an example of a Zebra Tower.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF159E/f33171cfff84c23150eb82e578a37293690a12de.png)A Zebra Tower's height is the sum of sizes of all cubes that form the tower. Help little Janet build the Zebra Tower of the maximum possible height, using the available cubes.

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
3 3
```

### 输出

```
9
3
2 3 1 
```

## 样例 #2

### 输入

```
2
1 1
2 1
```

### 输出

```
2
2
2 1 
```

# AI分析结果

# 💡 Kay的C++算法解析：Zebra Tower 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举与动态规划结合（编程技巧应用）

🗣️ **初步分析**：  
解决“Zebra Tower”的关键，就像我们帮 Janet 从一堆彩色立方体中挑出最搭的两套颜色，交替叠成最高的塔。核心思路是**枚举每个颜色作为“主色”，找到能与之搭配的“最佳副色”**，通过动态规划记录选k个主色时的最大价值，再结合副色的对应价值计算总高度。  

- **题解思路**：先将同色立方体按大小排序（大的在前），统计每个颜色的数量；然后枚举每个颜色，计算选1、2、…k个该颜色时的最大总大小（用`c[k]`记录），同时对比副色的`c[k]`或`c[k+1]`，找到最大组合；最后根据主副色的数量差异，输出对应的立方体序列。  
- **核心难点**：如何高效枚举颜色对（避免重复计算）、如何记录选k个同色的最大价值（动态规划）、如何处理主副色数量不同的情况（输出时调整顺序）。  
- **可视化设计思路**：用8位像素风格展示立方体排序（颜色块按大小排列）、枚举过程（当前主色高亮）、动态规划更新（`c[k]`数值跳动），以及最终塔的搭建（颜色交替的像素块堆叠）。关键步骤用“叮”音效提示（如排序完成、找到最大价值），胜利时播放上扬的“通关”音效。  


## 2. 精选优质题解参考

**题解一：来源：7KByte**  
* **点评**：这份题解的思路非常清晰，用“枚举主色+动态规划”的组合解决了问题。首先通过`map`统计每个颜色的数量，再将立方体按“颜色数量降序+颜色升序+大小降序”排序，确保前面的颜色数量更多，方便后续处理。`calc`函数用动态规划记录选k个同色的最大价值（`c[k]`），同时对比副色的对应价值，找到最大组合。代码结构合理（分`calc`、`solve`函数处理核心逻辑），变量命名（如`h`统计数量、`c`记录最大价值）符合直觉，特别是处理主副色数量不同的`solve`函数，考虑了两种情况（数量相等/不等），边界处理严谨。虽然`map`的使用增加了一点时间复杂度，但整体逻辑简洁，适合初学者理解“枚举+动态规划”的结合应用。  


## 3. 核心难点辨析与解题策略

### 1. **关键点1：如何高效枚举颜色对？**  
* **分析**：题解通过排序将同色立方体集中，并按颜色数量降序排列，确保前面的颜色数量≥后面的颜色数量。这样，当处理后面的颜色时，前面的颜色数量一定更多，无需重复计算反向组合（如主色A+副色B与主色B+副色A），减少了枚举次数。  
* 💡 **学习笔记**：排序是优化枚举的常用技巧，通过有序性避免重复计算。  

### 2. **关键点2：如何记录选k个同色的最大价值？**  
* **分析**：题解用`c[k]`数组记录选k个当前颜色的最大总大小（`c[k].first`）和对应的颜色（`c[k].second`）。在`calc`函数中，遍历当前颜色的所有立方体，累加大小更新`c[k]`，同时对比副色的`c[k]`或`c[k+1]`，找到最大组合。这种动态规划的方式避免了重复计算，提高了效率。  
* 💡 **学习笔记**：动态规划的核心是“记录中间结果，避免重复计算”，`c[k]`数组就是中间结果的载体。  

### 3. **关键点3：如何处理主副色数量不同的情况？**  
* **分析**：题解的`solve`函数处理了两种情况：① 主副色数量相等（如样例2），此时交替排列，总数量为2*k；② 主副色数量不等（如样例1），此时副色数量多1，总数量为2*k+1。输出时根据情况调整立方体的顺序（主色在前或副色在前）。  
* 💡 **学习笔记**：边界情况需要仔细考虑，特别是数量差异导致的排列顺序变化。  

### ✨ 解题技巧总结  
- **技巧A：排序优化枚举**：通过排序将同色元素集中，减少枚举次数。  
- **技巧B：动态规划记录中间结果**：用数组记录选k个元素的最大价值，避免重复计算。  
- **技巧C：分情况处理边界**：针对主副色数量不同的情况，设计不同的输出逻辑，确保正确性。  


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：本代码综合了题解的核心思路，保留了排序、动态规划和输出逻辑，结构清晰。  
* **完整核心代码**：  
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int N = 100005;
struct Cube { int color, size, id; };
Cube cubes[N];
map<int, int> colorCount;
pair<long long, int> c[N]; // c[k] = (max_sum, color)
int ll[N], rr[N]; // 每个颜色的起始和结束索引
long long maxHeight;
int mainColor,副Color;

bool compare(const Cube& a, const Cube& b) {
    if (a.color != b.color) {
        if (colorCount[a.color] != colorCount[b.color])
            return colorCount[a.color] > colorCount[b.color];
        return a.color < b.color;
    }
    return a.size > b.size;
}

void calculate(int l, int r) {
    long long sum = 0;
    for (int i = l; i <= r; ++i) {
        sum += cubes[i].size;
        // 对比副色的c[k]或c[k+1]
        if (i - l + 1 >= 1 && c[i - l + 1].second != 0 && sum + c[i - l + 1].first > maxHeight) {
            maxHeight = sum + c[i - l + 1].first;
            mainColor = cubes[i].color;
            副Color = c[i - l + 1].second;
        }
        if (i - l + 2 >= 1 && c[i - l + 2].second != 0 && sum + c[i - l + 2].first > maxHeight) {
            maxHeight = sum + c[i - l + 2].first;
            mainColor = cubes[i].color;
            副Color = c[i - l + 2].second;
        }
        // 更新c[k]
        if (sum > c[i - l + 1].first) {
            c[i - l + 1].first = sum;
            c[i - l + 1].second = cubes[i].color;
        }
    }
}

void outputResult() {
    int lenMain = rr[mainColor] - ll[mainColor] + 1;
    int lenSub = rr[副Color] - ll[副Color] + 1;
    long long total = 0;
    vector<int> sequence;
    if (lenMain == lenSub) {
        total = c[lenMain].first + c[lenSub].first;
        for (int i = 0; i < lenMain; ++i) {
            sequence.push_back(cubes[ll[mainColor] + i].id);
            sequence.push_back(cubes[ll[副Color] + i].id);
        }
    } else {
        total = c[lenMain].first + c[lenSub].first;
        for (int i = 0; i < lenMain; ++i) {
            sequence.push_back(cubes[ll[副Color] + i].id);
            sequence.push_back(cubes[ll[mainColor] + i].id);
        }
        sequence.push_back(cubes[ll[副Color] + lenMain].id);
    }
    cout << total << endl;
    cout << sequence.size() << endl;
    for (int id : sequence) cout << id << " ";
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> cubes[i].color >> cubes[i].size;
        cubes[i].id = i;
        colorCount[cubes[i].color]++;
    }
    sort(cubes + 1, cubes + n + 1, compare);
    // 记录每个颜色的起始和结束索引
    int pre = 1;
    for (int i = 2; i <= n; ++i) {
        if (cubes[i].color != cubes[i-1].color) {
            ll[cubes[i-1].color] = pre;
            rr[cubes[i-1].color] = i-1;
            calculate(pre, i-1);
            pre = i;
        }
    }
    ll[cubes[n].color] = pre;
    rr[cubes[n].color] = n;
    calculate(pre, n);
    outputResult();
    return 0;
}
```  
* **代码解读概要**：  
  1. 读取输入并统计每个颜色的数量；  
  2. 将立方体按“颜色数量降序+颜色升序+大小降序”排序；  
  3. 遍历每个颜色，用`calculate`函数计算选k个该颜色的最大价值（`c[k]`），并找到最大组合；  
  4. 根据主副色的数量差异，用`outputResult`函数输出结果。  


### 针对优质题解的片段赏析  
**题解一：来源：7KByte**  
* **亮点**：排序策略与动态规划的结合，高效枚举颜色对。  
* **核心代码片段**（排序函数）：  
```cpp
bool operator<(const node o)const{
    if(c!=o.c){
        if(h[c]!=h[o.c])return h[c]>h[o.c];
        return c<o.c;
    }
    return s>o.s;
}
```  
* **代码解读**：  
  这个排序函数是题解的关键！它先按颜色数量降序排列（`h[c] > h[o.c]`），确保数量多的颜色排在前面；如果数量相同，按颜色升序排列（`c < o.c`），避免重复；同一颜色内按大小降序排列（`s > o.s`），保证选大的立方体优先。这样排序后，处理后面的颜色时，前面的颜色数量一定更多，无需重复计算反向组合。  
* 💡 **学习笔记**：排序条件的设计直接影响算法效率，要根据问题需求合理选择排序键。  


## 5. 算法可视化：像素动画演示 (核心部分)

### 动画演示主题：《Janet的彩色塔挑战》（8位像素风）  
### 核心演示内容：  
展示立方体排序、枚举主色、动态规划更新`c[k]`、最终塔搭建的全过程，融入复古游戏元素（如“通关”音效、像素方块动画）。  

### 设计思路简述：  
采用FC红白机的8位像素风格（如《超级马里奥》的配色），用不同颜色的方块代表立方体（如红色=颜色1，蓝色=颜色2），大小用方块的高度表示（大的方块更高）。通过“单步执行”“自动播放”控制动画，关键步骤用音效提示（如排序完成的“叮”声、找到最大价值的“胜利”声），增加学习趣味性。  

### 动画帧步骤与交互关键点：  
1. **场景初始化**：屏幕左侧显示未排序的立方体（颜色随机，大小不一），右侧是“控制面板”（开始/暂停、单步、重置按钮，速度滑块），背景是Janet的房间（像素风格的桌子、椅子）。  
2. **排序过程**：立方体按“颜色数量降序+大小降序”排列，每个立方体移动时伴随“滑动”音效。排序完成后，同色立方体集中，大小从大到小排列。  
3. **枚举主色**：当前处理的主色立方体高亮（如边框闪烁），屏幕上方显示“当前主色：颜色X”。  
4. **动态规划更新**：`c[k]`数组用像素数字显示（如`c[1]=5`，`c[2]=8`），累加大小时光标移动，数字跳动，伴随“滴”音效。  
5. **找到最大组合**：当找到最大总高度时，屏幕弹出“找到最大高度：Y”的提示框，播放“胜利”音效（如《魂斗罗》的通关音乐片段）。  
6. **搭建塔**：立方体按交替颜色排列，从下往上堆叠，每堆一个方块伴随“咚”的音效，最终塔的高度显示在屏幕上方。  

### 旁白提示：  
- “现在我们要给立方体排序啦！数量多的颜色排在前面，大的立方体也排在前面～”（排序时）  
- “当前主色是颜色1，我们来计算选1个、2个…的最大大小～”（枚举时）  
- “看！`c[3]`变成了10，这表示选3个颜色1的立方体总大小是10～”（动态规划更新时）  
- “太棒了！找到最大高度9，我们来搭建塔吧～”（找到最大组合时）  


## 6. 拓展练习与相似问题思考

### 通用思路/技巧迁移：  
本题的“枚举+动态规划”思路可迁移到以下场景：  
- **选两种水果搭配**：比如选苹果和香蕉，交替排列，最大化总重量；  
- **选两种衣服搭配**：比如选上衣和裤子，交替穿着，最大化总价值；  
- **选两种数字组合**：比如选奇数和偶数，交替排列，最大化总和。  

### 练习推荐 (洛谷)：  
1. **洛谷 P1090** - 《合并果子》  
   🗣️ **推荐理由**：这道题需要选择最优的合并顺序，最大化总价值，类似本题的“选择最优组合”思路，能帮助你巩固动态规划的应用。  
2. **洛谷 P1156** - 《垃圾陷阱》  
   🗣️ **推荐理由**：这道题需要动态规划记录不同高度的最大能量，类似本题的`c[k]`数组记录中间结果，能帮助你理解动态规划的“状态转移”。  
3. **洛谷 P2051** - 《中国象棋》  
   🗣️ **推荐理由**：这道题需要状态压缩动态规划，处理棋盘上的棋子放置，类似本题的“枚举+动态规划”组合，能帮助你拓展思维。  


## 7. 学习心得与经验分享 (若有)  
本次分析的题解中未发现明确的作者个人心得分享部分。  


## 结语  
本次关于“Zebra Tower”的C++解题分析就到这里啦！希望这份指南能帮助你理解“枚举+动态规划”的结合应用，掌握排序、动态规划和边界处理的技巧。记住，编程就像搭塔，每一步都要仔细思考，才能搭出最高的塔～下次我们再一起探索新的编程挑战！💪

---
处理用时：140.16秒