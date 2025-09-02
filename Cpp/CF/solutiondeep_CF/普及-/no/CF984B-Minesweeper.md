# 题目信息

# Minesweeper

## 题目描述

One day Alex decided to remember childhood when computers were not too powerful and lots of people played only default games. Alex enjoyed playing Minesweeper that time. He imagined that he saved world from bombs planted by terrorists, but he rarely won.

Alex has grown up since then, so he easily wins the most difficult levels. This quickly bored him, and he thought: what if the computer gave him invalid fields in the childhood and Alex could not win because of it?

He needs your help to check it.

A Minesweeper field is a rectangle $ n \times m $ , where each cell is either empty, or contains a digit from $ 1 $ to $ 8 $ , or a bomb. The field is valid if for each cell:

- if there is a digit $ k $ in the cell, then exactly $ k $ neighboring cells have bombs.
- if the cell is empty, then all neighboring cells have no bombs.

Two cells are neighbors if they have a common side or a corner (i. e. a cell has at most $ 8 $ neighboring cells).

## 说明/提示

In the second example the answer is "NO" because, if the positions of the bombs are preserved, the first line of the field should be \*2\*1.

You can read more about Minesweeper in <a>Wikipedia's article</a>.

## 样例 #1

### 输入

```
3 3
111
1*1
111
```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 4
*.*.
1211
```

### 输出

```
NO```

# AI分析结果

### 题目翻译
# 扫雷

## 题目描述
有一天，亚历克斯回忆起了童年时光，那时电脑还没那么强大，很多人只玩默认游戏。亚历克斯那时很喜欢玩扫雷。他想象自己从恐怖分子埋下的炸弹中拯救了世界，但他很少获胜。

从那以后，亚历克斯长大了，所以他能轻松通关最难的关卡。这很快就让他感到厌烦了，于是他想：如果在童年时电脑给他的是无效的扫雷场，而亚历克斯因为这个才无法获胜呢？

他需要你的帮助来检查一下。

扫雷场是一个 $n \times m$ 的矩形，其中每个单元格要么是空的，要么包含一个从 $1$ 到 $8$ 的数字，要么是一个炸弹。如果对于每个单元格都满足以下条件，则该扫雷场是有效的：
- 如果单元格中有一个数字 $k$，那么恰好有 $k$ 个相邻单元格有炸弹。
- 如果单元格是空的，那么所有相邻单元格都没有炸弹。

如果两个单元格有公共边或公共角（即一个单元格最多有 $8$ 个相邻单元格），则它们是相邻的。

## 说明/提示
在第二个样例中，答案是 “NO”，因为如果炸弹的位置保持不变，扫雷场的第一行应该是 \*2\*1。

你可以在 [维基百科的文章](a) 中阅读更多关于扫雷的信息。

## 样例 #1
### 输入
```
3 3
111
1*1
111
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
2 4
*.*.
1211
```
### 输出
```
NO
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟扫雷地图的合法性检查过程，依据题目给定的两个规则（空的地方周围无雷，数字周围雷的数量与数字相等）来判断地图是否合法。各题解的主要区别在于实现细节，如边界判断的方式、记录雷数量的方法等。

### 题解评分与选择
- **sounds_666（4星）**：思路清晰，代码注释详细，易于理解。通过自定义函数进行边界判断，对不同情况（空和数字）分别处理，逻辑明确。
- **__Hacheylight__（4星）**：将判断逻辑封装在 `judge` 函数中，结构清晰。使用方向数组简化了周围单元格的遍历。
- **МiсDZ（3星）**：先建立真正的地图，再与原地图比较，思路有一定特色，但代码相对复杂，可读性稍差。
- **Eason_AC（3星）**：使用方向数组，整体逻辑简洁，但部分自定义函数未给出实现，影响理解。
- **封禁用户（3星）**：纯模拟思路，代码简单，但未处理边界情况，存在潜在风险。

### 重点代码
#### sounds_666
```cpp
bool kkl(int x,int y){//判断合法性 
    if(x<1||y<1||x>n||y>m)return true;
    return false;
}
// ...
if(mapp[i][j]=='.'){//如果是空的 
    for(int p=i-1;p<=i+1;p++){//在附近3*3寻找雷 
        for(int q=j-1;q<=j+1;q++){
            if(kkl(p,q))continue;
            if(mapp[p][q]=='*'){//如果是雷，就不合法
                cout<<"NO"<<endl; //直接输出
                return 0;//结束 
            } 
        }
    }
}
if(mapp[i][j]>='0'&&mapp[i][j]<='9'){//如果是数字
    int cnt=0;//记录雷的数量 
    for(int p=i-1;p<=i+1;p++){//在附近3*3寻找雷 
        for(int q=j-1;q<=j+1;q++){
            if(kkl(p,q))continue;
            if(mapp[p][q]=='*'){//如果是雷
                cnt++;//累加 
            } 
        }
    }
    if(cnt!=mapp[i][j]-'0'){//如果不相等 ，就不合法 
        cout<<"NO"<<endl; //直接输出
        return 0;//结束 
    }
} 
```
核心思想：通过 `kkl` 函数判断边界，对空单元格和数字单元格分别处理，检查是否满足扫雷地图的合法性规则。

#### __Hacheylight__
```cpp
int dx[8]={-1,-1,-1,0,0,1,1,1} ;
int dy[8]={-1,0,1,-1,1,-1,0,1} ;
bool judge(){
    R(i,1,n) R(j,1,m)
    if (st[i][j]=='.') //empty 
        R(k,0,7){ 
            int tx=i+dx[k],ty=j+dy[k] ;
            if (tx<1 || ty<1 || tx>n || ty>m) continue ;
            if (st[tx][ty]=='*') return false ;
        }
    else if (st[i][j]>='0' && st[i][j]<='9'){ //digits 
        int sum=0 ; 
        R(k,0,7){
            int tx=i+dx[k],ty=j+dy[k] ;
            if (tx<1 || ty<1 || tx>n || ty>m) continue ;
            if (st[tx][ty]=='*') sum++ ;
        } 
        int ch=st[i][j]-'0' ;
        if (ch!=sum) return false ;
    }
    return true ;
} 
```
核心思想：使用方向数组 `dx` 和 `dy` 遍历周围单元格，将判断逻辑封装在 `judge` 函数中，对空单元格和数字单元格分别检查是否合法。

### 关键思路与技巧
- **方向数组**：使用方向数组（如 `dx` 和 `dy`）可以简化对周围单元格的遍历，减少代码量。
- **边界判断**：在遍历周围单元格时，需要进行边界判断，避免越界访问。
- **封装函数**：将判断逻辑封装在函数中，提高代码的可读性和可维护性。

### 拓展思路
同类型题目可能会有不同的地图规则或条件，如增加特殊单元格、改变相邻单元格的定义等，但核心思路仍然是模拟地图的检查过程。类似算法套路包括对二维矩阵的遍历和条件判断，可用于解决如迷宫问题、地图标记问题等。

### 推荐洛谷题目
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：涉及对棋盘的遍历和条件判断，与本题的二维矩阵处理思路相似。
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：需要对棋盘进行遍历，判断棋子的移动是否合法，与本题的模拟思想类似。
- [P1596 [USACO10OCT]Lake Counting S](https://www.luogu.com.cn/problem/P1596)：对地图进行遍历，判断连通区域的情况，与本题的地图处理有一定相似性。

### 个人心得
封禁用户提到“不写边界判断~~我太懒了~~，因此读入时下标起始为1”，提醒我们在编写代码时要注意边界情况的处理，不能因为偷懒而忽略潜在的问题，否则可能导致程序出错。 

---
处理用时：50.37秒