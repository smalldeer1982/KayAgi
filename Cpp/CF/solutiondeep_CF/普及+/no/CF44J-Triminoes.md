# 题目信息

# Triminoes

## 题目描述

给出一个$n \times m$的棋盘，棋盘用黑白两色染色（染色规则与国际象棋棋盘相同），其上某些格子被挖掉了，问能否使用$1 \times 3$和$3 \times 1$的矩形不重不漏地覆盖没有挖空的棋盘部分。

注意：矩形放置的中间的格子必须要是黑色

## 样例 #1

### 输入

```
6 10
.w.wbw.wbw
wbwbw.w.w.
bw.wbwbwbw
w.wbw.wbwb
...wbw.w.w
..wbw.wbw.
```

### 输出

```
YES
.a.aaa.ccc
baccc.c.a.
ba.dddcbab
b.aaa.cbab
...bbb.b.b
..ccc.ddd.```

## 样例 #2

### 输入

```
2 2
wb
bw
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 3
wbw
```

### 输出

```
YES
bbb
```

## 样例 #4

### 输入

```
1 3
...
```

### 输出

```
YES
...
```

# AI分析结果

### 题目内容
# Triminoes

## 题目描述
给出一个$n \times m$的棋盘，棋盘用黑白两色染色（染色规则与国际象棋棋盘相同），其上某些格子被挖掉了，问能否使用$1 \times 3$和$3 \times 1$的矩形不重不漏地覆盖没有挖空的棋盘部分。

注意：矩形放置的中间的格子必须要是黑色。

## 样例 #1
### 输入
```
6 10
.w.wbw.wbw
wbwbw.w.w.
bw.wbwbwbw
w.wbw.wbwb
...wbw.w.w
..wbw.wbw.
```
### 输出
```
YES
.a.aaa.ccc
baccc.c.a.
ba.dddcbab
b.aaa.cbab
...bbb.b.b
..ccc.ddd.
```

## 样例 #2
### 输入
```
2 2
wb
bw
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
1 3
wbw
```
### 输出
```
YES
bbb
```

## 样例 #4
### 输入
```
1 3
...
```
### 输出
```
YES
...
```

### 算法分类
贪心

### 综合分析与结论
目前仅一题解，该题解思路明确，抓住“放置在中间的格子必须是黑色”这一关键要求，采用贪心策略，从左到右、从上到下遍历棋盘。对于未处理的白色格子，优先尝试横着放置骨牌，若无法横着放则尝试竖着放，若都不行则判定无解。在处理骨牌字母输出时，依据四色定理，通过比较骨牌四周已放置骨牌的字母来确定当前骨牌字母。但代码部分较为繁琐，可读性欠佳。

### 所选的题解
 - **星级**：3星
 - **关键亮点**：利用贪心策略，优先横着放置骨牌，思路直接对应题目要求。
 - **个人心得**：无

### 重点代码及核心实现思想
```
bool solve(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(tu[i][j]=='.')continue;
            if(used[i][j])continue;
            if(tu[i][j]=='b')return 0;
            if(tu[i][j+1]=='b'&&!used[i][j+1]){
                if(tu[i][j+2]!='w'||used[i][j+2])return 0;
                used[i][j+1]=used[i][j+2]=1;
                cl[i][j]='a';
                int x=i,y=j;
                for(int k=1;k<=3;k++){
                    if(cl[x][y-1]==cl[x][y])cl[x][y]++;
                    if(cl[x-1][y]==cl[x][y])cl[x][y]++;
                    if(cl[x-1][y+1]==cl[x][y])cl[x][y]++;
                    if(cl[x-1][y+2]==cl[x][y])cl[x][y]++;
                    if(cl[x][y+3]==cl[x][y])cl[x][y]++;
                    if(cl[x+1][y]==cl[x][y])cl[x][y]++;
                    if(cl[x+1][y+1]==cl[x][y])cl[x][y]++;
                    if(cl[x+1][y+2]==cl[x][y])cl[x][y]++;
                }
                cl[x][y+1]=cl[x][y+2]=cl[x][y];
            }
            else{
                if(tu[i+1][j]!='b'||used[i+1][j]||tu[i+2][j]!='w'||used[i+2][j])return 0;
                used[i+1][j]=used[i+2][j]=1;
                int x=i,y=j;
                cl[x][y]='a';
                for(int i=1;i<=3;i++){
                    if(cl[x][y-1]==cl[x][y])cl[x][y]++;
                    if(cl[x-1][y]==cl[x][y])cl[x][y]++;
                    if(cl[x+1][y-1]==cl[x][y])cl[x][y]++;
                    if(cl[x+2][y-1]==cl[x][y])cl[x][y]++;
                    if(cl[x][y+1]==cl[x][y])cl[x][y]++;
                    if(cl[x+3][y]==cl[x][y])cl[x][y]++;
                    if(cl[x+1][y+1]==cl[x][y])cl[x][y]++;
                    if(cl[x+2][y+1]==cl[x][y])cl[x][y]++;
                }
                cl[x+1][y]=cl[x+2][y]=cl[x][y];
            }
        }
    }
    return 1;
}
```
核心实现思想：遍历棋盘每个未处理且未挖空的格子，若为黑色直接判定无解；若为白色，优先尝试横着放骨牌，检查右边两个格子是否符合条件，若符合则标记已使用并确定骨牌字母；若不能横着放则尝试竖着放，检查下方两个格子是否符合条件，若符合同样标记并确定字母。字母确定通过比较四周已放置骨牌的字母，避免重复。

### 最优关键思路或技巧
利用贪心策略，优先横着放置骨牌，简化问题求解过程，同时利用四色定理解决骨牌字母输出问题。

### 可拓展之处
同类型题可关注棋盘覆盖类问题，类似算法套路是根据题目给定的放置规则，寻找合适的贪心策略，优先满足某种放置条件。

### 洛谷题目推荐
 - [P1249 最大乘积](https://www.luogu.com.cn/problem/P1249)：通过贪心策略解决数字拆分求最大乘积问题。
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：利用贪心思想对纪念品进行分组。
 - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：涉及区间分配的贪心问题。 

---
处理用时：56.02秒