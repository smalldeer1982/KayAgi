# 题目信息

# Letter Exchange

## 题目描述

A cooperative game is played by $ m $ people. In the game, there are $ 3m $ sheets of paper: $ m $ sheets with letter 'w', $ m $ sheets with letter 'i', and $ m $ sheets with letter 'n'.

Initially, each person is given three sheets (possibly with equal letters).

The goal of the game is to allow each of the $ m $ people to spell the word "win" using their sheets of paper. In other words, everyone should have one sheet with letter 'w', one sheet with letter 'i', and one sheet with letter 'n'.

To achieve the goal, people can make exchanges. Two people participate in each exchange. Both of them choose exactly one sheet of paper from the three sheets they own and exchange it with each other.

Find the shortest sequence of exchanges after which everyone has one 'w', one 'i', and one 'n'.

## 样例 #1

### 输入

```
3
2
nwi
inw
3
inn
nww
wii
4
win
www
iii
nnn```

### 输出

```
0
2
2 w 3 i
3 w 1 n
3
2 w 3 i
2 w 4 n
3 i 4 n```

# AI分析结果

### 题目内容重写
**题目描述**

一个合作游戏由 $m$ 个人参与。游戏中有 $3m$ 张纸片：$m$ 张写有字母 'w'，$m$ 张写有字母 'i'，$m$ 张写有字母 'n'。

最初，每个人被分配三张纸片（可能包含相同的字母）。

游戏的目标是让每个参与者都能用他们手中的纸片拼出单词 "win"。换句话说，每个人都应该有一张 'w'、一张 'i' 和一张 'n'。

为了达到目标，参与者可以进行交换。每次交换由两个人参与，每个人从自己拥有的三张纸片中选择一张，与对方交换。

找出使每个人都能拼出 "win" 的最短交换序列。

### 算法分类
贪心

### 题解分析与结论
本题的核心是通过交换纸片，使得每个人最终都能拥有一张 'w'、一张 'i' 和一张 'n'。由于交换的次数需要最小化，因此贪心算法是一个合适的选择。贪心算法的关键在于优先处理那些能够直接互补的交换，然后再处理需要多次交换才能解决的复杂情况。

### 所选高分题解
#### 题解1：AThousandSuns (赞：11)
**星级：5星**
**关键亮点：**
1. 将字母 'w', 'i', 'n' 分别映射为 0, 1, 2，简化了问题。
2. 使用有向图表示每个人多余和缺少的字母，通过贪心策略优先处理直接互补的交换。
3. 最后处理剩余的复杂情况，确保交换次数最少。

**核心代码：**
```cpp
void solve(){
    n=read();
    FOR(i,1,n){
        scanf("%s",s);
        c[0]=c[1]=c[2]=0;
        FOR(j,0,2) c[id[s[j]]]++;
        FOR(j,0,2) FOR(k,0,2) if(c[j]>1 && c[k]<1) vec[j][k].PB(i);
    }
    FOR(i,0,2) FOR(j,0,2) while(sz(vec[i][j]) && sz(vec[j][i])){
        int x=vec[i][j].back();vec[i][j].pop_back();
        int y=vec[j][i].back();vec[j][i].pop_back();
        add(x,i,y,j);
    }
    int p=0,q=1,r=2;
    if(sz(vec[0][2])) swap(q,r);
    FOR(i,0,sz(vec[p][q])-1){
        int x=vec[p][q][i];
        int y=vec[q][r][i];
        int z=vec[r][p][i];
        add(x,p,y,q);
        add(y,p,z,r);
    }
    printf("%d\n",al);
    FOR(i,1,al) printf("%d %c %d %c\n",ans[i][0],rid[ans[i][1]],ans[i][2],rid[ans[i][3]]);
    clear();
}
```

#### 题解2：Leasier (赞：1)
**星级：4星**
**关键亮点：**
1. 将每个人多余和缺少的字母表示为二元组 $(a, b)$，优先处理可以直接互补的交换。
2. 使用 `vector<int> vec[3][3]` 存储每个人的多余和缺少情况，简化了数据处理。
3. 最后处理剩余的复杂情况，确保交换次数最少。

**核心代码：**
```cpp
void solve(){
    n=read();
    FOR(i,1,n){
        scanf("%s",s);
        c[0]=c[1]=c[2]=0;
        FOR(j,0,2) c[id[s[j]]]++;
        FOR(j,0,2) FOR(k,0,2) if(c[j]>1 && c[k]<1) vec[j][k].PB(i);
    }
    FOR(i,0,2) FOR(j,0,2) while(sz(vec[i][j]) && sz(vec[j][i])){
        int x=vec[i][j].back();vec[i][j].pop_back();
        int y=vec[j][i].back();vec[j][i].pop_back();
        add(x,i,y,j);
    }
    int p=0,q=1,r=2;
    if(sz(vec[0][2])) swap(q,r);
    FOR(i,0,sz(vec[p][q])-1){
        int x=vec[p][q][i];
        int y=vec[q][r][i];
        int z=vec[r][p][i];
        add(x,p,y,q);
        add(y,p,z,r);
    }
    printf("%d\n",al);
    FOR(i,1,al) printf("%d %c %d %c\n",ans[i][0],rid[ans[i][1]],ans[i][2],rid[ans[i][3]]);
    clear();
}
```

### 最优关键思路或技巧
1. **贪心策略**：优先处理可以直接互补的交换，确保每次交换都能最大化地减少问题的复杂度。
2. **数据结构**：使用有向图或 `vector` 存储每个人的多余和缺少情况，简化了数据处理和交换操作。
3. **映射简化**：将字母 'w', 'i', 'n' 映射为数字 0, 1, 2，简化了问题的表示和处理。

### 可拓展之处
类似的问题可以出现在其他需要最小化交换次数的场景中，例如拼图游戏、任务分配等。贪心算法在这些问题中同样适用，关键在于如何定义和优先处理可以直接互补的交换。

### 推荐相似题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：47.83秒