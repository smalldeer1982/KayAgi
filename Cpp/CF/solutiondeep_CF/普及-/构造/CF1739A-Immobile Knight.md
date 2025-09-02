# 题目信息

# Immobile Knight

## 题目描述

There is a chess board of size $ n \times m $ . The rows are numbered from $ 1 $ to $ n $ , the columns are numbered from $ 1 $ to $ m $ .

Let's call a cell isolated if a knight placed in that cell can't move to any other cell on the board. Recall that a chess knight moves two cells in one direction and one cell in a perpendicular direction:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1739A/a0d7d8c62ba0d8d73d58490b8d2222f35ced96b2.png)Find any isolated cell on the board. If there are no such cells, print any cell on the board.

## 说明/提示

In the first testcase, all cells are isolated. A knight can't move from any cell of the board to any other one. Thus, any cell on board is a correct answer.

In the second testcase, there are no isolated cells. On a normal chess board, a knight has at least two moves from any cell. Thus, again, any cell is a correct answer.

In the third testcase, only the middle cell of the board is isolated. The knight can move freely around the border of the board, but can't escape the middle.

## 样例 #1

### 输入

```
3
1 7
8 8
3 3```

### 输出

```
1 7
7 2
2 2```

# AI分析结果

### 题目中文重写
# 静止的骑士

## 题目描述
有一个大小为 $ n \times m $ 的棋盘。行从 $ 1 $ 到 $ n $ 编号，列从 $ 1 $ 到 $ m $ 编号。

如果一个格子上放置的骑士（马）无法移动到棋盘上的其他任何格子，我们称这个格子为孤立格。回顾一下，国际象棋中的骑士移动规则是：在一个方向上移动两格，在垂直方向上移动一格。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1739A/a0d7d8c62ba0d8d73d58490b8d2222f35ced96b2.png)
找出棋盘上的任意一个孤立格。如果不存在这样的格子，则输出棋盘上的任意一个格子。

## 说明/提示
在第一个测试用例中，所有格子都是孤立的。骑士无法从棋盘上的任何一个格子移动到其他格子。因此，棋盘上的任何一个格子都是正确答案。

在第二个测试用例中，不存在孤立格。在普通的棋盘上，骑士从任何一个格子至少有两种移动方式。因此，同样，任何一个格子都是正确答案。

在第三个测试用例中，只有棋盘的中间格子是孤立的。骑士可以在棋盘的边界自由移动，但无法离开中间格子。

## 样例 #1
### 输入
```
3
1 7
8 8
3 3
```
### 输出
```
1 7
7 2
2 2
```

### 综合分析与结论
这些题解主要围绕寻找 $n\times m$ 棋盘上使马无法移动到其他格子的孤立格，若不存在则输出任意一格展开。思路可分为分类讨论和暴力枚举两种。
- **分类讨论**：多数题解通过分析不同棋盘大小得出规律，如 $n$ 或 $m$ 为 $1$ 时输出 $(1,1)$，其他情况输出 $(2,2)$ ；也有通过输出棋盘中间格 $( (n + 1) / 2, (m + 1) / 2 )$ 来解决。
- **暴力枚举**：通过遍历棋盘每个格子，检查马从该格子出发的八个可能移动位置是否越界，若都越界则该格子为孤立格。

### 所选题解
- **作者：zhujiangyuan（5星）**
    - **关键亮点**：思路清晰，结合图形详细分析不同棋盘大小下的情况，代码简洁易懂。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
       int n,m;
       cin>>n>>m;
       if (n==1||m==1) cout<<1<<' '<<1<<endl;
       else cout<<2<<' '<<2<<endl;
    }
    return 0;
}
```
核心实现思想：根据输入的棋盘大小 $n$ 和 $m$ ，判断若 $n$ 或 $m$ 为 $1$ ，输出 $(1, 1)$ ，否则输出 $(2, 2)$ 。

- **作者：undefined_Ryan（4星）**
    - **关键亮点**：提供两种思路，一种是分类讨论得出规律，另一种从棋盘区域划分角度分析，具有创新性。
    - **核心代码**：
```cpp
// 思路一
#include <bits/stdc++.h>
using namespace std;
int t,n,m;
int main() {
    cin>>t;
    for (int i=1;i<=t;i++) {
        cin>>n>>m;
        if (n==1||m==1) cout<<"1 1\n";
        else cout<<"2 2\n";
    }
    return 0;
}
// 思路二
#include <bits/stdc++.h>
using namespace std;
int t,n,m;
int main() {
    cin>>t;
    for (int i=1;i<=t;i++) {
        cin>>n>>m;
        cout<<(n+1)/2<<' '<<(m+1)/2<<endl;
    }
    return 0;
}
```
核心实现思想：思路一与上述分类讨论思路一致；思路二通过输出棋盘中间格 $( (n + 1) / 2, (m + 1) / 2 )$ 来解决问题。

- **作者：zzy0618（4星）**
    - **关键亮点**：在分类讨论基础上，考虑了输入输出优化，使用快读快写提高效率。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch > '9' || ch < '0') { if (ch == '-')f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}//快读模板 
int main() {
    register int t, n, m;
    t = read();
    while (t--) {
        n = read(); m = read();
        if (n == 1 || m == 1) {// n 或 m 为 1 的情况 
            putchar('1'); putchar(' ');
            putchar('1'); putchar('\n');//加快输出 
        }
        else {// 大于等于 2 的情况 
            putchar('2'); putchar(' ');
            putchar('2'); putchar('\n');
        }
    }
    return 0;
}
```
核心实现思想：先使用快读读取输入数据，再根据 $n$ 和 $m$ 的值判断输出 $(1, 1)$ 或 $(2, 2)$ ，并使用快写输出结果。

### 最优关键思路或技巧
- 分类讨论时，通过分析不同棋盘大小下骑士的移动情况，总结出通用规律，避免复杂的计算。
- 对于此类存在多种情况的问题，输出棋盘中间格是一种简洁有效的解决方法。
- 当数据量较大时，使用快读快写可以优化输入输出效率。

### 拓展思路
同类型题可能会改变棋子的移动规则或棋盘的形状，解题时可采用类似的分类讨论或暴力枚举方法。例如，改变棋子为象、车等，分析其移动规则和在不同棋盘大小下的可达性。

### 推荐题目
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：考察棋盘上棋子的放置和冲突判断。
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：涉及在棋盘状迷宫中寻找路径，可类比骑士在棋盘上的移动。
- [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)：需要枚举所有可能的情况，与暴力枚举思路类似。

### 个人心得
- **abensyl**：提到当情况较少时，枚举有时是最快的证明方法，强调了枚举在某些情况下的实用性。 

---
处理用时：39.54秒