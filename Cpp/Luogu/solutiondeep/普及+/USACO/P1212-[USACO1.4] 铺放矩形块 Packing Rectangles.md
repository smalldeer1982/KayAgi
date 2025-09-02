# 题目信息

# [USACO1.4] 铺放矩形块 Packing Rectangles

## 题目描述

给定 $4$ 个矩形块，找出一个最小的封闭矩形将这 $4$ 个矩形块放入，但不得相互重叠。所谓最小矩形指该矩形面积最小。

![](https://cdn.luogu.com.cn/upload/image_hosting/gu39gbyb.png)

$4$ 个矩形块中任一个矩形的边都与封闭矩形的边相平行，上图显示出了铺放 $4$ 个矩形块的 $6$ 种方案。  

这 $6$ 种方案是唯一可能的基本铺放方案。因为其它方案能由基本方案通过旋转和镜像反射得到。

可能存在满足条件且有着同样面积的各种不同的封闭矩形，你应该输出所有这些封闭矩形的边长。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，输入的所有数在 $[1,50]$ 内。

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
1 2
2 3
3 4
4 5
```

### 输出

```
40
4 10
5 8
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过枚举所有可能的矩形排列和方向，再依据题目给定的 6 种基本铺放方案计算封闭矩形的面积，进而找出最小面积的封闭矩形。各题解在实现细节上存在差异，如采用 DFS 或多重循环来枚举排列，使用不同的数据结构记录结果等。主要难点在于准确计算 6 种铺放方案下封闭矩形的长和宽，尤其是第 6 种方案需分多种情况讨论。

### 所选题解
- **作者：七喜 (赞：19) - 4星**
    - **关键亮点**：思路清晰，代码注释详细，使用 DFS 生成排列，易于理解。
- **作者：Chiesl (赞：7) - 4星**
    - **关键亮点**：对 6 种情况的分析详细，配有图片辅助理解，代码结构清晰。
- **作者：ChampionCyan (赞：1) - 4星**
    - **关键亮点**：代码模块化程度高，将不同排列方案的计算封装成独立函数，便于维护和扩展。

### 重点代码及核心实现思想
#### 七喜的题解
```c
void check()//x表示宽//就是横着的线，y表示高//就是竖着的线咯;
{
    int x,y;
    // 按照 6 种方案计算封闭矩形的长和宽
    x=tmpx[1]+tmpx[2]+tmpx[3]+tmpx[4];
    y=max(max(tmpy[1],tmpy[2]),max(tmpy[3],tmpy[4]));
    alter(x,y);
    // 其他方案省略...
}

void dfs(int yj)//dfs生成排列
{
    if(yj==4)
    {
        check();return ;
    }
    for(int i=1;i<5;i++)
        if(!vis[i])
        {
            tmpx[yj+1]=x[i],tmpy[yj+1]=y[i],vis[i]=1;
            dfs(yj+1);
            tmpx[yj+1]=y[i],tmpy[yj+1]=x[i];
            dfs(yj+1);
            vis[i]=tmpx[yj+1]=tmpy[yj+1]=0;
        }
}
```
核心思想：利用 DFS 生成 4 个矩形的所有排列和方向，每次生成后调用 `check` 函数计算 6 种方案下封闭矩形的长和宽，并更新最小面积。

#### Chiesl 的题解
```cpp
void f (int s1, int s2, int s3, int s4) {
    int x, y;
    // 按照 6 种方案计算封闭矩形的长和宽
    x = a[s1][1] + a[s2][1] + a[s3][1] + a[s4][1], y = max(max(a[s1][0], a[s2][0]), max(a[s3][0], a[s4][0]));
    answer(x, y);
    // 其他方案省略...
}

void dfs (int k) {
    if (k == 5) {
        f(num[1], num[2], num[3], num[4]);
        return;
    }
    for (int i = 1; i <= 4; i++) {
        if (vis[i]) continue;
        vis[i] = true;
        num[k] = i;
        dfs(k + 1);
        swap(a[i][0], a[i][1]);//把矩阵转90°再搜
        dfs(k + 1);
        swap(a[i][0], a[i][1]);
        vis[i] = false;//回溯
    }
}
```
核心思想：同样使用 DFS 生成排列和方向，每次生成后调用 `f` 函数计算 6 种方案下的长和宽，并更新结果。

#### ChampionCyan 的题解
```cpp
inline void part1() {
    update(rl(0) + rl(1) + rl(2) + rl(3), max(max(rw(0), rw(1)), max(rw(2), rw(3))));
}

inline void part2() {
    update(max(rl(0) + rl(1) + rl(2), rl(3)), max(rw(0), max(rw(1), rw(2))) + rw(3));
}

// 其他 part 函数省略...

inline void do_it() {
    part1();
    part2();
    part3();
    part4();
    part5();
    part6();
}

inline void work(int depth) {
    if (depth == 5) {
        do_it();
        return;
    }
    for (int i = 0; i < 4; i++) {
        swap(rec[order[i]].length, rec[order[i]].width);//旋转
        work(depth + 1);//下一种排列
        swap(rec[order[i]].length, rec[order[i]].width);//回溯
        work(depth + 1);//下一种排列
    }
}
```
核心思想：将 6 种排列方案的计算封装成独立的 `part` 函数，`do_it` 函数依次调用这些函数，`work` 函数使用 DFS 生成排列和方向。

### 最优关键思路或技巧
- **DFS 枚举**：利用 DFS 生成 4 个矩形的所有排列和方向，确保不遗漏任何可能的情况。
- **分类讨论**：对 6 种基本铺放方案分别进行分析，准确计算封闭矩形的长和宽，尤其是第 6 种方案的多种子情况。
- **模块化编程**：将不同功能的代码封装成独立的函数，提高代码的可读性和可维护性。

### 可拓展之处
同类型题目可能会增加矩形的数量或改变铺放规则，解题思路依然是枚举所有可能的排列和方向，再根据具体规则计算封闭图形的面积。类似算法套路包括全排列枚举、分类讨论等。

### 推荐题目
- [P1007 独木桥](https://www.luogu.com.cn/problem/P1007) - 涉及枚举和思维转换。
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012) - 全排列枚举的应用。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047) - 分类讨论和区间处理。

### 个人心得摘录与总结
- **cwocw**：提到这题做起来一波三折，但最终成功解决。总结是要仔细分析题目给定的 6 种方案，对于复杂情况要耐心分类讨论，注意细节处理。 

---
处理用时：47.32秒