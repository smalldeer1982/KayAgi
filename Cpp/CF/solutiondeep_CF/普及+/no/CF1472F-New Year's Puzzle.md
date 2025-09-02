# 题目信息

# New Year's Puzzle

## 题目描述

Every year Santa Claus gives gifts to all children. However, each country has its own traditions, and this process takes place in different ways. For example, in Berland you need to solve the New Year's puzzle.

Polycarp got the following problem: given a grid strip of size $ 2 \times n $ , some cells of it are blocked. You need to check if it is possible to tile all free cells using the $ 2 \times 1 $ and $ 1 \times 2 $ tiles (dominoes).

For example, if $ n = 5 $ and the strip looks like this (black cells are blocked):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/b41649f0d0bdba5578287fa746baff1e8a9677b4.png)Then it can be tiled, for example, using two vertical and two horizontal tiles, as in the picture below (different tiles are marked by different colors).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/f3eba115e4f25b885841d9adf40142fd3358cffa.png)And if $ n = 3 $ and the strip looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/1bfdaad6e61d408b265451fa0ae69099925aea09.png)It is impossible to tile free cells.

Polycarp easily solved this task and received his New Year's gift. Can you solve it?

## 说明/提示

The first two test cases are explained in the statement.

In the third test case the strip looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/fb18b851c5e691e6cc3d6920785bdb0ec1abf74e.png) It is easy to check that the unblocked squares on it can not be tiled.

## 样例 #1

### 输入

```
3

5 2
2 2
1 4

3 2
2 1
2 3

6 4
2 1
2 3
2 4
2 6```

### 输出

```
YES
NO
NO```

# AI分析结果

### 题目内容（中文重写）
# 新年谜题

## 题目描述
每年圣诞老人都会给所有孩子送礼物。然而，每个国家都有自己的传统，送礼的过程也各不相同。例如，在伯兰，你需要解开新年谜题。

波利卡普遇到了这样一个问题：给定一个大小为 $2 \times n$ 的网格条，其中一些单元格被阻塞。你需要检查是否可以用 $2 \times 1$ 和 $1 \times 2$ 的瓷砖（多米诺骨牌）铺满所有空闲单元格。

例如，如果 $n = 5$，且网格条看起来像这样（黑色单元格是被阻塞的）：
![图片1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/b41649f0d0bdba5578287fa746baff1e8a9677b4.png)
那么它是可以被铺满的，例如，使用两个垂直和两个水平的瓷砖，如下图所示（不同的瓷砖用不同的颜色标记）。
![图片2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/f3eba115e4f25b885841d9adf40142fd3358cffa.png)
如果 $n = 3$，且网格条看起来像这样：
![图片3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/1bfdaad6e61d408b265451fa0ae69099925aea09.png)
则无法铺满空闲单元格。

波利卡普轻松地解决了这个任务并收到了他的新年礼物。你能解决它吗？

## 说明/提示
前两个测试用例在题目描述中已经解释过。

在第三个测试用例中，网格条看起来像这样：
![图片4](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/fb18b851c5e691e6cc3d6920785bdb0ec1abf74e.png)
很容易检查出上面未被阻塞的方块无法被铺满。

## 样例 #1
### 输入
```
3

5 2
2 2
1 4

3 2
2 1
2 3

6 4
2 1
2 3
2 4
2 6
```
### 输出
```
YES
NO
NO
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕判断 $2 \times n$ 网格条在部分单元格被阻塞的情况下能否用多米诺骨牌铺满展开。思路大多基于贪心策略，通过分析不同的阻塞情况（如上下都阻塞、只阻塞一个格子等），利用奇偶性、格子间距等条件来判断可行性。部分题解还涉及排序、分治、动态规划等思想辅助求解。

### 所选题解
- **作者：OMG_wc（5星）**
    - **关键亮点**：思路清晰，通过对每列的四种情况分类讨论，利用 `map` 存储信息，巧妙地根据格子的行号和列号的奇偶性判断是否能铺满，代码简洁高效。
    - **核心代码**：
```c++
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        map<int, int> mp;
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            mp[y] += x;
        }
        int ok = 1, last = -1;
        for (auto t : mp) {
            if (last == -1) {
                if (t.second != 3)
                    last = t.first + t.second;
            } else {
                if (t.second == 3) {
                    ok = 0;
                    break;
                }
                if ((last + t.first + t.second) % 2 == 0) {
                    ok = 0;
                    break;
                }
                last = -1;
            }
        }
        if (last != -1) ok = 0;
        puts(ok ? "YES" : "NO");
    }
    return 0;
}
```
    - **核心实现思想**：先将阻塞格子的信息存入 `map` 中，然后遍历 `map`，根据当前列的阻塞情况和上一个有意义的列的信息判断是否能继续铺满，若出现不满足条件的情况则标记为不可行。

- **作者：二gou子（4星）**
    - **关键亮点**：采用分治思想，通过对格子的匹配情况进行分类讨论，结合奇偶性判断可行性，同时考虑了特殊情况的特判，代码逻辑清晰。
    - **个人心得**：“`po[m + 1].y = 0, po[m + 1].x = 0;` 这一行是万恶之源，耗费了我一个小时的时间。主要原因就是因为我要用到 `m + 1`，但是上一次的 `m + 1` 没有清空，所以可能会导致错误答案。” 总结：在使用数组时，要注意对可能用到的额外元素进行初始化，避免遗留数据影响结果。
    - **核心代码**：
```c++
struct Node{
    int x,y;
}po[N];
bool cmp(Node a,Node b){
    return a.y<b.y;
}
int main()
{
    scanf("%d",&T);
    while(T--){
        flag=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&po[i].x,&po[i].y);
        }
        if(m%2==1){
            printf("NO\n");
            continue;
        }
        sort(po+1,po+1+m,cmp);
        po[m+1].y=0,po[m+1].x=0;
        for(int i=1;i<=m;i+=2){
            if(po[i].x==po[i+1].x){
                if((po[i+1].y-po[i].y-1)%2==1){
                    flag=1;
                    break;
                }
                if(po[i+1].y==po[i+2].y){
                    flag=1;
                    break;
                }
            }
            if(po[i].x!=po[i+1].x){
                if((po[i+1].y-po[i].y-1)%2==0){
                    flag=1;
                    break;
                }
                if(po[i+1].y==po[i+2].y){
                    flag=1;
                    break;
                }
            }
        }
        if(flag==1){
            printf("NO\n");
            continue;
        }
        else{
            printf("YES\n");
        }
    }
    return 0;
}
```
    - **核心实现思想**：先对阻塞格子按列排序，然后两两分组，根据格子是否在同一行以及它们之间的间距奇偶性判断是否能铺满，同时特判同一列有多个阻塞格子的情况。

- **作者：胖头鱼学员（4星）**
    - **关键亮点**：通过分类讨论上下异色、上下同色、上下无色三种情况，结合格子间距和所在行的关系判断可行性，代码结构清晰。
    - **核心代码**：
```c++
struct E {
  int r, c;
  bool operator<(const E &e) const {
    return c < e.c;
  }
} e[kMaxN];

int t, n, l;

void M() {
  int m = 0;
  for (int i = 1; i <= n; i++) {
    if (e[i].c != e[m].c) {
      e[++m] = e[i];
    } else {
      e[m].r |= e[i].r;
    }
  }
  n = m;
}

bool C() {
  bool b = 1;
  for (int i = 1, s = 3; i <= n; i++) {
    if (s == 3) {
      s = e[i].r;
    } else {
      b &= e[i].r != 3 && (e[i].r != s) ^ ((e[i].c - e[i - 1].c) & 1);
      s = 3;
    }
  }
  return b;
}

int main() {
  cin >> t;
  while (t--) {
    cin >> l >> n;
    for (int i = 1; i <= n; i++) {
      cin >> e[i].r >> e[i].c;
    }
    e[++n] = {3, l + 1};
    sort(e + 1, e + 1 + n);
    M();
    cout << (C() ? "YES" : "NO") << endl;
  }
  return 0;
}
```
    - **核心实现思想**：先对阻塞格子按列排序，合并同一列的信息，然后遍历格子，根据相邻格子的关系和间距奇偶性判断是否能铺满。

### 最优关键思路或技巧
- **贪心策略**：优先考虑竖着放多米诺骨牌，遇到单个格子被阻塞的列再考虑横着放，通过分析不同情况的可行性来判断整体是否能铺满。
- **奇偶性判断**：利用格子的行号、列号以及格子之间的间距的奇偶性来判断是否能铺满，简化了判断过程。
- **排序**：对阻塞格子按列排序，方便后续的处理和判断。

### 可拓展之处
同类型题可能会改变网格的大小、瓷砖的形状或增加更多的限制条件。类似算法套路可以应用于其他铺砖、填充类问题，通过分析不同情况的可行性，结合奇偶性、间距等条件进行判断。

### 推荐洛谷题目
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：考察对棋盘布局的分析和判断，与本题对网格的处理有相似之处。
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：需要考虑棋子的移动规则和路径的可行性，和本题判断能否铺满的思路类似。
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：通过分析不同的操作顺序和状态，判断是否满足条件，与本题的分析思路有一定的相似性。

---
处理用时：71.98秒