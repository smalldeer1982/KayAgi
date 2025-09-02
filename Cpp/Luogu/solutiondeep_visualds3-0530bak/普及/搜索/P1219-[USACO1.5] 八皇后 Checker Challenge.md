# 题目信息

# [USACO1.5] 八皇后 Checker Challenge

## 题目描述

一个如下的 $6 \times 6$ 的跳棋棋盘，有六个棋子被放置在棋盘上，使得每行、每列有且只有一个，每条对角线（包括两条主对角线的所有平行线）上至多有一个棋子。

![](https://cdn.luogu.com.cn/upload/image_hosting/3h71x0yf.png)

上面的布局可以用序列 $2\ 4\ 6\ 1\ 3\ 5$ 来描述，第 $i$ 个数字表示在第 $i$ 行的相应位置有一个棋子，如下：

行号 $1\ 2\ 3\ 4\ 5\ 6$

列号 $2\ 4\ 6\ 1\ 3\ 5$

这只是棋子放置的一个解。请编一个程序找出所有棋子放置的解。  
并把它们以上面的序列方法输出，解按字典顺序排列。  
请输出前 $3$ 个解。最后一行是解的总个数。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$6 \le n \le 13$。

题目翻译来自NOCOW。

USACO Training Section 1.5


## 样例 #1

### 输入

```
6
```

### 输出

```
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4
```

# AI分析结果

# DFS - 八皇后问题题解分析

## 算法分类
DFS (深度优先搜索)

## 题解思路与算法要点
八皇后问题是一个经典的DFS回溯问题，要求在N×N棋盘上放置N个皇后，使得它们互不攻击（不在同一行、列或对角线上）。主要解决思路：

1. **搜索策略**：逐行放置皇后，每行尝试所有可能的列位置
2. **冲突检测**：
   - 列冲突：使用数组标记已占用的列
   - 对角线冲突：使用两个数组分别标记"左上-右下"和"右上-左下"对角线
3. **回溯机制**：当无法在当前行放置皇后时，回溯到上一行尝试其他位置
4. **优化技巧**：
   - 位运算优化（最高效）
   - 对称性剪枝
   - 提前终止条件

## 最优题解推荐 (≥4星)

### 1. ybb756032937 (★★★★★)
- **亮点**：清晰的标记数组使用，完整注释
- **核心代码**：
```cpp
void queen(int i) {
    if(i>n) { print(); return; }
    for(int j=1;j<=n;j++) {
        if((!b[j])&&(!c[i+j])&&(!d[i-j+n])) {
            a[i]=j; b[j]=1; c[i+j]=1; d[i-j+n]=1;
            queen(i+1);
            b[j]=0; c[i+j]=0; d[i-j+n]=0;
        }
    }
}
```

### 2. XG_Zepto (★★★★☆)
- **亮点**：简洁的实现，良好的变量命名
- **核心代码**：
```cpp
void eq(int line) {
    if(line>n) {
        sum++;
        if(sum>3) return;
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        printf("\n"); return;
    }
    for(int i=1;i<=n;i++) {
        if((!check[0][i])&&(!check[1][line+i])&&(!check[2][line-i+n])) {
            ans[line]=i;
            check[0][i]=1; check[1][line+i]=1; check[2][line-i+n]=1;
            eq(line+1);
            check[0][i]=0; check[1][line+i]=0; check[2][line-i+n]=0;
        }
    }
}
```

### 3. wancong (★★★★☆)
- **亮点**：位运算优化，高性能
- **核心代码**：
```cpp
void dfs(int now,int ld,int rd,int deep) {
    if(now==upperlim) {
        if(++sum<=3) {
            for(int i=0;i<n-1;i++) printf("%d ",lg[ans[i]]);
            printf("%d\n",lg[ans[n-1]]);
        }
        return;
    }
    int pos=upperlim&(~(now|ld|rd));
    while(pos) {
        int p=pos&-pos;
        ans[deep]=p;
        dfs(now|p,(ld|p)<<1,(rd|p)>>1,deep+1);
        pos-=p;
    }
}
```

## 最优思路提炼

1. **标记数组法**：使用三个数组分别标记列和两个方向的对角线
2. **位运算优化**：将棋盘状态压缩为整数，通过位运算快速判断冲突
3. **对称性剪枝**：利用棋盘对称性减少搜索空间
4. **回溯模板**：标准DFS回溯框架，先尝试放置，递归，然后撤销

## 同类型题目推荐

1. P1219 八皇后（本题）
2. P1784 数独
3. P1074 靶形数独
4. P2329 栅栏

## 可视化设计

### 搜索过程动画方案

1. **棋盘表示**：N×N网格，用不同颜色表示：
   - 白色：可放置
   - 红色：冲突位置
   - 绿色：当前皇后位置
   - 灰色：已放置皇后

2. **搜索过程**：
   - 高亮当前尝试的行和列
   - 实时显示冲突检测（对角线和列）
   - 回溯时显示撤销的皇后位置

3. **控制面板**：
   - 播放/暂停
   - 单步执行
   - 速度调节
   - 显示当前搜索深度

4. **8位像素风格**：
   - 使用16色调色板
   - 方块式皇后表示
   - 复古音效：
     - 放置皇后：短促"滴"声
     - 冲突：低沉"嘟"声
     - 找到解：欢快音效

### 示例代码片段

```javascript
// 伪代码 - 搜索动画核心逻辑
function animateSearch(step) {
    if(step >= solution.length) return;
    
    let {row, col, action} = solution[step];
    // action: 'place' or 'remove'
    
    // 更新棋盘UI
    updateBoardUI(row, col, action);
    
    // 播放对应音效
    playSound(action);
    
    // 继续下一步
    setTimeout(() => animateSearch(step+1), speed);
}
```

## 个人心得

多位题解作者提到：
1. 对角线标记的数组大小需要特别注意，避免越界
2. N=13时需要优化否则会超时
3. 位运算虽然高效但实现难度较大
4. 输出前三个解需要特殊处理计数器

## 完整参考代码

以下是标记数组法的完整实现：

```cpp
#include<iostream>
using namespace std;

int n, total;
int col[20], diag1[40], diag2[40], ans[20];

void search(int y) {
    if(y == n) {
        total++;
        if(total <= 3) {
            for(int i=0; i<n; i++) cout << ans[i]+1 << " ";
            cout << endl;
        }
        return;
    }
    for(int x=0; x<n; x++) {
        if(col[x] || diag1[x+y] || diag2[x-y+n-1]) continue;
        col[x] = diag1[x+y] = diag2[x-y+n-1] = 1;
        ans[y] = x;
        search(y+1);
        col[x] = diag1[x+y] = diag2[x-y+n-1] = 0;
    }
}

int main() {
    cin >> n;
    search(0);
    cout << total << endl;
    return 0;
}
```

---
处理用时：56.22秒