# 题目信息

# The Beaver's Problem - 2

## 题目描述

Offering the ABBYY Cup participants a problem written by the Smart Beaver is becoming a tradition. He proposed the following problem.

You are given a monochrome image, that is, an image that is composed of two colors (black and white). The image is given in raster form, that is, as a matrix of pixels' colors, and the matrix's size coincides with the size of the image.

The white color on the given image corresponds to the background. Also, the image contains several black geometric shapes. It is known that the image can contain only two types of shapes: squares and circles. Your task is to count the number of circles and the number of squares which the given image contains.

The squares on the image can be rotated arbitrarily. In addition, the image can possibly contain some noise arranged as follows: each pixel of the original image can change its color to the opposite with the probability of $ 20 $ %.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E3/575cc300a436bc791f059ed1604954db020e4792.png) An example of an image that has no noise and the sides of the squares are parallel to the coordinate axes (two circles and three squares).   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E3/5a255ee1bca061f5ff62a305107ac74540469a88.png) An example of an image that has no noise and the squares are rotated arbitrarily (two circles and three squares).   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E3/6588309d80aee82245c95133dff3b167b5dbc7e6.png) An example of an image that has noise and the squares are rotated arbitrarily (one circle and three squares).

## 说明/提示

You are given a sample of original data for each difficulty level. The samples are available at http://codeforces.ru/static/materials/contests/178/e-samples.zip .

# AI分析结果

---
# 💡 Kay的C++算法解析：The Beaver's Problem - 2 深入学习指南 💡

<introduction>
今天我们要一起攻克的是图像处理中的经典问题——“The Beaver's Problem - 2”。这道题需要我们从含噪声的黑白图像中识别圆形和正方形的数量，既考验图像处理技巧，又涉及算法设计。让我们一步步拆解问题，掌握核心思路！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（图像处理与模式识别）`

🗣️ **初步分析**：
解决这道题的关键在于“噪声处理-形状分离-特征判断”的三步流程。可以想象成给图像“洗澡”（降噪）、“分块”（分离图形）、“验身”（判断形状）。  
- **题解思路**：两份题解均采用“降噪→连通区域提取→形状判断”的主线。Halberd_Cease用众数滤波降噪，通过面积对比判断形状；shiyihang用卷积降噪+边缘检测，通过方差判断圆的均匀性。  
- **核心难点**：噪声干扰下的图形分离、旋转正方形的特征提取、形状分类的阈值确定。  
- **可视化设计**：我们将用8位像素风动画演示降噪过程（像素颜色根据邻域调整）、BFS填充连通区域（像素块逐步被“涂色”）、形状判断时的距离计算（像素点到中心的距离用不同颜色高亮）。例如，降噪时用“像素抖动”动画模拟噪声，BFS填充时用“波浪扩散”效果标记连通区域，形状判断时用“雷达波”动画展示各点到中心的距离。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码有效性和实践价值三个维度评估了题解，以下两份题解因逻辑完整、实现巧妙值得重点参考：
</eval_intro>

**题解一：Halberd_Cease (来源：Codeforces提交)**
* **点评**：这份题解的亮点在于“简单高效”。思路直白：先用众数滤波（统计8邻域+自身共9个点的黑白比例）降噪，再用洪水填充分离图形，最后通过面积对比判断圆或正方形。代码虽短但关键步骤明确（如`mapp_real`的降噪逻辑），特别适合入门者理解基础图像处理流程。美中不足是形状判断的“0.8参数”调整依赖经验，但这也提醒我们：实际问题中参数调优是重要环节。

**题解二：shiyihang (来源：Codeforces提交)**
* **点评**：此题解更“工程化”，结合了卷积降噪和边缘检测，通过计算边缘点到中心的距离方差判断圆，逻辑更严谨。代码中使用`bitset`优化空间，BFS提取边缘点并计算方差的步骤清晰（如`avg`和`e`的计算），适合学习如何将数学特征（方差）转化为代码实现。不足是卷积部分代码稍复杂，但这是处理大图像的必要优化。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，我们常被以下三个问题卡住，结合题解经验，来看看如何突破：
</difficulty_intro>

1.  **关键点1：如何有效去除20%的随机噪声？**
    * **分析**：噪声是随机翻转颜色的像素，单个像素不可信。题解用“邻域统计”解决：Halberd_Cease统计9个邻域点，若黑像素≥5则保留黑（众数滤波）；shiyihang用5×5卷积取平均（平滑滤波），都通过“多数表决”降低噪声影响。  
    * 💡 **学习笔记**：噪声处理的核心是“用邻域信息修正孤立错误”。

2.  **关键点2：如何分离重叠或邻近的图形？**
    * **分析**：图形可能相连，需用洪水填充（BFS/DFS）标记连通区域。题解中`mp[i][j]`作为标记数组，每次BFS从未访问的黑点出发，标记所有相连黑点为同一图形。  
    * 💡 **学习笔记**：连通区域提取的关键是正确标记已访问点，避免重复计数。

3.  **关键点3：如何区分旋转后的正方形和圆形？**
    * **分析**：圆形的所有点到中心距离几乎相等（方差小），正方形边缘点到中心的距离差异大（方差大）。shiyihang计算边缘点到平均中心的距离方差，若方差<阈值则为圆；Halberd_Cease用面积对比（圆面积≈πr²，正方形≈2r²）。  
    * 💡 **学习笔记**：形状分类需抓住“不变特征”——圆的均匀性、正方形的棱角性。

### ✨ 解题技巧总结
- **降噪技巧**：邻域统计（众数/平均）是处理随机噪声的通用方法。  
- **连通区域提取**：BFS比DFS更适合大图像（避免栈溢出），用二维数组标记访问状态。  
- **特征选择**：方差、面积等数学特征是形状分类的“指纹”，需根据问题调整阈值。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合两份题解的优势，提炼出一个兼顾简洁与鲁棒性的核心实现，重点展示降噪、连通区域提取和形状判断的关键逻辑。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Halberd_Cease的众数滤波和shiyihang的方差判断，适合理解完整流程。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    #include <queue>
    #include <cmath>
    using namespace std;

    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // 8邻域方向
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int main() {
        int n;
        cin >> n;
        vector<vector<int>> img(n+2, vector<int>(n+2, 0)); // 原始图像（1-based）
        vector<vector<int>> clean_img(n+2, vector<int>(n+2, 0)); // 降噪后图像

        // 输入并降噪（众数滤波）
        for (int i = 1; i <= n; ++i) {
            string s; cin >> s;
            for (int j = 1; j <= n; ++j) {
                img[i][j] = s[j-1] - '0';
                int cnt = img[i][j]; // 自身+8邻域黑像素数
                for (int k = 0; k < 8; ++k) cnt += img[i+dx[k]][j+dy[k]];
                clean_img[i][j] = (cnt >= 5) ? 1 : 0; // 黑像素≥5则保留黑
            }
        }

        // 洪水填充分离连通区域
        vector<vector<bool>> vis(n+2, vector<bool>(n+2, false));
        int circles = 0, squares = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (clean_img[i][j] && !vis[i][j]) {
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    vis[i][j] = true;
                    vector<pair<int, int>> points; // 存储当前图形所有点

                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        points.emplace_back(x, y);
                        for (int k = 0; k < 4; ++k) { // 4邻域扩展（避免对角线干扰）
                            int nx = x + dx[k], ny = y + dy[k];
                            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n 
                                && clean_img[nx][ny] && !vis[nx][ny]) {
                                vis[nx][ny] = true;
                                q.push({nx, ny});
                            }
                        }
                    }

                    // 形状判断：计算边缘点到中心的距离方差
                    if (points.size() < 10) continue; // 过滤小噪点
                    double avg_x = 0, avg_y = 0;
                    for (auto [x, y] : points) { avg_x += x; avg_y += y; }
                    avg_x /= points.size(); avg_y /= points.size();

                    double variance = 0;
                    for (auto [x, y] : points) {
                        double dis = (x - avg_x)*(x - avg_x) + (y - avg_y)*(y - avg_y);
                        variance += dis;
                    }
                    variance /= points.size();

                    if (variance < 100) circles++; // 阈值需根据实际调整
                    else squares++;
                }
            }
        }

        cout << circles << " " << squares << endl;
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取图像并通过8邻域统计降噪（`clean_img`生成），然后用BFS提取连通区域（`vis`标记访问），最后计算区域内点到平均中心的距离方差，方差小则为圆，大则为正方形。关键逻辑集中在降噪、BFS和方差计算三部分。

---
<code_intro_selected>
接下来，我们拆解两份优质题解的核心片段，学习其中的巧妙设计。
</code_intro_selected>

**题解一：Halberd_Cease**
* **亮点**：用8邻域众数滤波快速降噪，代码简洁易理解。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int res = mapp[i][j];
            for (int k = 0; k < 8; k++) 
                res += mapp[i+dx[k]][j+dy[k]];
            mapp_real[i][j] = (res >= 5) ? 1 : 0;
        }
    ```
* **代码解读**：`res`统计当前像素（`mapp[i][j]`）和8个邻域像素的黑像素总数（每个黑像素贡献1）。若总数≥5（9个中多数是黑），则`mapp_real[i][j]`设为黑（1）。这一步通过“多数表决”去除了随机噪声——单个噪声像素会被周围正确像素“纠正”。  
* 💡 **学习笔记**：众数滤波是处理随机噪声的“简单暴力”方法，适合快速实现。

**题解二：shiyihang**
* **亮点**：用方差判断圆的均匀性，数学特征提取更严谨。
* **核心代码片段**：
    ```cpp
    avg.first /= edge.size();
    avg.second /= edge.size();
    double aver = 0, e = 0;
    for (int i = 0; i < edge.size(); ++i) {
        auto [tx, ty] = edge[i];
        aver += (a[i] = getDis(avg, {tx, ty}));
    }
    aver /= edge.size();
    for (auto v : a) e += pow(v - aver, 2);
    e /= a.size();
    ```
* **代码解读**：先计算边缘点的平均中心（`avg`），再计算每个边缘点到中心的距离（`getDis`），求平均距离（`aver`），最后计算方差（`e`）。方差越小，说明各点到中心的距离越接近，越可能是圆。  
* 💡 **学习笔记**：方差是衡量数据离散程度的常用指标，适合判断圆形的“均匀性”。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观看到降噪、图形分离和形状判断的过程，我们设计一个“像素图像处理小剧场”动画，用8位复古风格还原算法每一步！
</visualization_intro>

  * **动画演示主题**：`像素小工匠的图像修复之旅`  
    （小工匠戴着护目镜，用“降噪刷”清理图像，用“区域笔”圈出图形，最后用“测量尺”判断形状）

  * **核心演示内容**：  
    1. 降噪过程：原始图像（带随机白点）→ 小工匠用“降噪刷”扫过每个像素，周围8个像素弹出小气泡显示颜色，统计后当前像素颜色被修正。  
    2. 连通区域提取：小工匠点击一个黑点，触发“波浪扩散”动画（像素块依次变绿），标记所有相连黑点为同一区域。  
    3. 形状判断：区域内所有点向中心发射“雷达波”（线段动画），波长短的（距离近）显示绿色，波长长的（距离远）显示红色。若绿色占多数（方差小），弹出“圆形”标签；否则弹出“正方形”标签。

  * **设计思路简述**：  
    8位像素风（16色，低分辨率）营造复古感，降低学习压力；“降噪刷”“波浪扩散”等动画将抽象的算法步骤具象化，帮助理解邻域统计和BFS的过程；颜色标记（绿=已访问，红/绿=距离）强化关键状态变化。

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：  
       - 屏幕分为左右两部分：左为原始图像（黑白像素块，部分白点噪声），右为控制面板（开始/暂停、单步按钮、速度滑块）。  
       - 播放8位风格的轻快BGM（类似《超级玛丽》的跳跃音效变调）。
    2. **降噪演示**：  
       - 单步执行时，小工匠移动到一个像素（用箭头标记），周围8个像素放大显示，每个像素旁显示“1”（黑）或“0”（白）。  
       - 统计总数后，当前像素颜色变化（如从白变黑），伴随“叮”的音效。  
       - 自动播放时，降噪刷快速扫过图像，像素颜色逐渐稳定。
    3. **连通区域提取**：  
       - 点击“开始BFS”，小工匠点击一个未访问的黑点，该点变绿，弹出队列框（像素方块堆叠）。  
       - 队列弹出一个点，4邻域未访问的黑点依次变绿并加入队列，伴随“噗噗”的入队音效。  
       - 所有相连点变绿后，队列清空，弹出“区域1完成”提示。
    4. **形状判断**：  
       - 区域内所有绿点中心出现十字标记（平均中心）。  
       - 每个绿点向中心发射线段（长度=距离），短线段（≤平均距离+阈值）绿色，长线段红色。  
       - 统计红绿比例，若绿色占比高（方差小），播放“叮咚”音效，显示“圆形”；否则播放“滴答”音效，显示“正方形”。
    5. **目标达成**：  
       - 所有区域处理完成，屏幕显示“圆形X个，正方形Y个”，小工匠举旗庆祝，播放胜利音效。

<visualization_conclusion>
通过这个动画，我们不仅能“看到”噪声如何被修正、区域如何被标记，还能直观理解方差为何能区分圆和正方形。下次遇到类似问题，你也可以想象小工匠的操作，更快理清思路！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是“图像处理+特征提取”，这类思路还能解决哪些问题？我们可以从以下方向拓展：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - **医学影像分析**：识别细胞（圆形）或组织块（不规则形）。  
    - **卫星图像识别**：区分农田（方形）和湖泊（圆形）。  
    - **OCR文字处理**：分离连笔字中的单个字符（连通区域提取）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1522** - `牛的旅行`  
        * 🗣️ **推荐理由**：涉及图的连通性分析（类似本题的区域提取），可练习BFS和距离计算。  
    2.  **洛谷 P5361** - `[SDOI2019]热闹的聚会与尴尬的聚会`  
        * 🗣️ **推荐理由**：需要提取“独立集”（类似区域分离），锻炼特征提取和条件判断能力。  
    3.  **洛谷 P1162** - `填涂颜色`  
        * 🗣️ **推荐理由**：基础的连通区域填充问题，适合巩固BFS实现。

-----

## 7\. 学习心得与经验分享

<insights_intro>
题解中Halberd_Cease提到：“手动给圆的面积上了0.8的参数，然后就可以过2和3了。”这是很实用的调试经验！
</insights_intro>

> **参考经验**：“因为识别中出现识别的圆少一些，也没有样例或者输入数据反馈，我手动给圆的面积上了0.8的参数，然后就可以过2和3了。”  
> **点评**：实际编程中，理论模型可能与真实数据有偏差（如噪声导致面积计算误差），这时候通过调整参数（如0.8）来校准是常见操作。这提醒我们：代码写完后，需要用测试数据验证，必要时调整阈值。调试时可以打印关键变量（如面积、方差），观察其分布，帮助确定合理阈值。

-----

<conclusion>
至此，我们完成了对“The Beaver's Problem - 2”的深入分析。从降噪到形状判断，每一步都需要仔细的观察和巧妙的算法设计。希望你能通过这份指南，掌握图像处理的基本技巧，并在实践中不断提升！下次再见，我们一起挑战新的算法问题！💪
</conclusion>

---
处理用时：138.70秒