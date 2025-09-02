# 题目信息

# Time to Run

## 题目描述

Bashar was practicing for the national programming contest. Because of sitting too much in front of the computer without doing physical movements and eating a lot Bashar became much fatter. Bashar is going to quit programming after the national contest and he is going to become an actor (just like his father), so he should lose weight.

In order to lose weight, Bashar is going to run for $ k $ kilometers. Bashar is going to run in a place that looks like a grid of $ n $ rows and $ m $ columns. In this grid there are two one-way roads of one-kilometer length between each pair of adjacent by side cells, one road is going from the first cell to the second one, and the other road is going from the second cell to the first one. So, there are exactly $ (4 n m - 2n - 2m) $ roads.

Let's take, for example, $ n = 3 $ and $ m = 4 $ . In this case, there are $ 34 $ roads. It is the picture of this case (arrows describe roads):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301D/f8acc1bb44bf67b8a6e82d8abf101031f5e398f8.png)

Bashar wants to run by these rules:

- He starts at the top-left cell in the grid;
- In one move Bashar may go up (the symbol 'U'), down (the symbol 'D'), left (the symbol 'L') or right (the symbol 'R'). More formally, if he stands in the cell in the row $ i $ and in the column $ j $ , i.e. in the cell $ (i, j) $ he will move to: 
  - in the case 'U' to the cell $ (i-1, j) $ ;
  - in the case 'D' to the cell $ (i+1, j) $ ;
  - in the case 'L' to the cell $ (i, j-1) $ ;
  - in the case 'R' to the cell $ (i, j+1) $ ;
- He wants to run exactly $ k $ kilometers, so he wants to make exactly $ k $ moves;
- Bashar can finish in any cell of the grid;
- He can't go out of the grid so at any moment of the time he should be on some cell;
- Bashar doesn't want to get bored while running so he must not visit the same road twice. But he can visit the same cell any number of times.

Bashar asks you if it is possible to run by such rules. If it is possible, you should tell him how should he run.

You should give him $ a $ steps to do and since Bashar can't remember too many steps, $ a $ should not exceed $ 3000 $ . In every step, you should give him an integer $ f $ and a string of moves $ s $ of length at most $ 4 $ which means that he should repeat the moves in the string $ s $ for $ f $ times. He will perform the steps in the order you print them.

For example, if the steps are $ 2 $ RUD, $ 3 $ UUL then the moves he is going to move are RUD $ + $ RUD $ + $ UUL $ + $ UUL $ + $ UUL $ = $ RUDRUDUULUULUUL.

Can you help him and give him a correct sequence of moves such that the total distance he will run is equal to $ k $ kilometers or say, that it is impossible?

## 说明/提示

The moves Bashar is going to move in the first example are: "RRLL".

It is not possible to run $ 1000000000 $ kilometers in the second example because the total length of the roads is smaller and Bashar can't run the same road twice.

The moves Bashar is going to move in the third example are: "RRDDLLRR".

The moves Bashar is going to move in the fifth example are: "RRRLLLDRRRDULLLD". It is the picture of his run (the roads on this way are marked with red and numbered in the order of his running):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301D/eda2cf93789d47332ff1838d0a037b6665e63145.png)

## 样例 #1

### 输入

```
3 3 4```

### 输出

```
YES
2
2 R
2 L```

## 样例 #2

### 输入

```
3 3 1000000000```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 3 8```

### 输出

```
YES
3
2 R
2 D
1 LLRR```

## 样例 #4

### 输入

```
4 4 9```

### 输出

```
YES
1
3 RLD```

## 样例 #5

### 输入

```
3 4 16```

### 输出

```
YES
8
3 R
3 L
1 D
3 R
1 D
1 U
3 L
1 D```

# AI分析结果

### 题目翻译
# 跑步时间

## 题目描述
巴沙尔正在为国赛编程竞赛进行训练。由于长时间坐在电脑前，缺乏身体运动且饮食过量，巴沙尔变得胖了许多。巴沙尔打算在国赛结束后放弃编程，像他父亲一样成为一名演员，所以他需要减肥。

为了减肥，巴沙尔打算跑 $k$ 公里。他将在一个看起来像 $n$ 行 $m$ 列网格的地方跑步。在这个网格中，每对相邻的单元格之间有两条单向的一公里长的道路，一条从第一个单元格通向第二个单元格，另一条从第二个单元格通向第一个单元格。所以，总共有 $ (4 n m - 2n - 2m) $ 条道路。

例如，当 $ n = 3 $ 且 $ m = 4 $ 时，这里有 $ 34 $ 条道路。这是这种情况的图示（箭头表示道路）：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301D/f8acc1bb44bf67b8a6e82d8abf101031f5e398f8.png)

巴沙尔想要按照以下规则跑步：
- 他从网格的左上角单元格开始；
- 在一次移动中，巴沙尔可以向上（用符号 'U' 表示）、向下（用符号 'D' 表示）、向左（用符号 'L' 表示）或向右（用符号 'R' 表示）移动。更正式地说，如果他站在第 $i$ 行第 $j$ 列的单元格，即单元格 $ (i, j) $ ，他将移动到：
  - 若为 'U'，则移动到单元格 $ (i - 1, j) $；
  - 若为 'D'，则移动到单元格 $ (i + 1, j) $；
  - 若为 'L'，则移动到单元格 $ (i, j - 1) $；
  - 若为 'R'，则移动到单元格 $ (i, j + 1) $；
- 他想要恰好跑 $k$ 公里，所以他想要恰好移动 $k$ 次；
- 巴沙尔可以在网格的任何单元格结束跑步；
- 他不能跑出网格，所以在任何时候他都必须在某个单元格上；
- 巴沙尔不想在跑步时感到无聊，所以他不能两次经过同一条道路。但他可以多次访问同一个单元格。

巴沙尔问你是否可以按照这些规则跑步。如果可以，你应该告诉他该如何跑。

你应该给他 $a$ 个步骤，并且由于巴沙尔记不住太多步骤，$a$ 不应超过 $3000$。在每个步骤中，你应该给他一个整数 $f$ 和一个长度最多为 $4$ 的移动字符串 $s$ ，这意味着他应该将字符串 $s$ 中的移动重复 $f$ 次。他将按照你打印的顺序执行这些步骤。

例如，如果步骤是 $2$ RUD，$3$ UUL，那么他要移动的顺序是 RUD + RUD + UUL + UUL + UUL = RUDRUDUULUULUUL。

你能帮助他并给他一个正确的移动序列，使他总共跑的距离等于 $k$ 公里，还是说这是不可能的？

## 说明/提示
在第一个示例中，巴沙尔要移动的顺序是："RRLL"。

在第二个示例中，不可能跑 $1000000000$ 公里，因为道路的总长度更小，而且巴沙尔不能两次跑同一条道路。

在第三个示例中，巴沙尔要移动的顺序是："RRDDLLRR"。

在第五个示例中，巴沙尔要移动的顺序是："RRRLLLDRRRDULLLD"。这是他跑步的图示（这条路线上的道路用红色标记，并按他跑步的顺序编号）：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301D/eda2cf93789d47332ff1838d0a037b6665e63145.png)

## 样例 #1
### 输入
```
3 3 4
```
### 输出
```
YES
2
2 R
2 L
```

## 样例 #2
### 输入
```
3 3 1000000000
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
3 3 8
```
### 输出
```
YES
3
2 R
2 D
1 LLRR
```

## 样例 #4
### 输入
```
4 4 9
```
### 输出
```
YES
1
3 RLD
```

## 样例 #5
### 输入
```
3 4 16
```
### 输出
```
YES
8
3 R
3 L
1 D
3 R
1 D
1 U
3 L
1 D
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断总边数是否小于 $k$，若小于则无解，否则构造一种遍历边的方案，在遍历过程中若达到 $k$ 步则停止。各题解的不同在于构造的具体走法和代码实现细节。
- **思路对比**：多数题解利用图是欧拉图的性质，构造一种能遍历所有边的走法；部分题解强调找到一种万能走法，能覆盖所有长度。
- **算法要点**：判断总边数是否足够，构造走法并在走的过程中检查剩余步数。
- **解决难点**：处理边界情况（如 $n = 1$ 或 $m = 1$），确保走法不重复经过边，满足输出格式要求（步数不超 3000，字符串长度不超 4）。

### 所选题解
- **作者：Kelin (赞：9)，4星**
  - **关键亮点**：思路清晰，利用欧拉图性质，给出简单可行的走法，代码简洁。
- **作者：CXY07 (赞：2)，4星**
  - **关键亮点**：详细分析输出格式特点，构造万能走法，对特殊情况（$m = 1$）进行特判。
  - **个人心得**：这是一道趣味题，作为 $Div2$ 的 $D$ 题，有种让人耳目一新的感觉，注意特判就没什么难的了。

### 重点代码
#### Kelin 的代码
```cpp
inline void Out(){
    printf("%d\n",(int)Ans.size());
    for(auto i:Ans)printf("%d %c\n",i.first,i.second);
    exit(0);
}
inline void Run(int s,char c){
    if(!s)return;
    if(k<=s)Ans.push_back({k,c}),Out();
    k-=s;Ans.push_back({s,c});
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    if(k>2*(2*n*m-n-m))return puts("NO"),0;
    puts("YES");Run(m-1,'R');
    for(int i=1;i<m;++i)
        Run(n-1,'D'),Run(n-1,'U'),Run(1,'L');
    fp(int i=1;i<n;++i)
        Run(1,'D'),Run(m-1,'R'),Run(m-1,'L');
    Run(n-1,'U');
    return 0;
}
```
**核心实现思想**：先判断总边数是否小于 $k$，若小于则输出 "NO"，否则输出 "YES"。然后按照特定的走法（先向右，再上下左右循环，最后向上）进行移动，每走一步检查剩余步数，若剩余步数不足则输出结果并退出。

#### CXY07 的代码
```cpp
inline void print() {
    puts("YES");
    int len = cnt.size(),tmp;
    cout << len << endl;
    for(register int i = 0;i < len; ++i) {
        cout << cnt[i] << ' ' << ans[i] << endl;
        tmp += cnt[i] * ans[i].length();
    }
    return;
}
int main () {
    cin >> n >> m >> k; savk = k;
    if(k > 4 * n * m - 2 * n - 2 * m) {puts("NO"); return 0;}
    if(m == 1) {
        lim = n - 1;
        if(k <= lim) {
            cnt.push_back(k),ans.push_back("D");
            k = 0;
            print();
            return 0;
        }
        k -= lim;
        cnt.push_back(lim),ans.push_back("D");
        if(k <= lim) {
            cnt.push_back(k),ans.push_back("U");
            k = 0;
            print();
            return 0;
        } 
        k -= lim;
        cnt.push_back(lim),ans.push_back("U");
        if(!k) print();
        else puts("NO");
        return 0;
    }
    lim = m - 1;
    for(register int i = 1;i <= n; ++i) {
        if(k <= lim) {
            cnt.push_back(k),ans.push_back("R");
            k = 0;
            break;
        }
        k -= lim;
        cnt.push_back(lim),ans.push_back("R");
        if(i < n && k <= lim * 3) {
            int tmp = k / 3,_;
            if(tmp) {
                cnt.push_back(tmp),ans.push_back("DUL");
            }
            _ = k - tmp * 3;
            if(_ == 1) cnt.push_back(1),ans.push_back("D");
            else if(_ == 2) cnt.push_back(1),ans.push_back("DU");
            k = 0;
            break;
        }
        if(i < n) {
            k -= lim * 3;
            cnt.push_back(lim),ans.push_back("DUL");
            cnt.push_back(1),ans.push_back("D");
            k--;
        } else {
            if(k <= lim) {
                cnt.push_back(k),ans.push_back("L");
                k = 0;
                break;
            } else {
                k -= lim;
                cnt.push_back(lim),ans.push_back("L");
            }
        }
        if(!k) break;
    }
    if(!k) {
        print();
        return 0;
    }
    if(k <= n - 1) {
        cnt.push_back(k),ans.push_back("U");
        print();
    } else puts("NO");
    return 0;
}
```
**核心实现思想**：先判断总边数是否小于 $k$，若小于则输出 "NO"。对于 $m = 1$ 的特殊情况进行特判。然后按照构造的走法（先向右，再上下左循环，最后向左）进行移动，每走一步检查剩余步数，若剩余步数不足则输出结果并退出。

### 扩展思路
同类型题或类似算法套路：
- 网格图中的路径规划问题，如判断是否存在满足特定条件的路径，输出路径方案等。
- 图的遍历问题，要求不重复经过边或点，构造合适的遍历顺序。

### 推荐题目
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)

---
处理用时：72.30秒