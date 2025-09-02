# 题目信息

# [USACO05JAN] The Wedding Juicer G

## 题目描述

约翰的奶牛们找到了一份不错的兼职一设计冲压式榨汁机．榨汁机设计如下：

一个 $W \times H$ 的底座（$3\leq W,H \leq 300$），每一个 $1 \times 1$ 的方格上都放有一个高度为 $B$（$1 \leq B \leq 10^9$）的柱子，用来榨汁。假设柱子之间都被完美地粘合了，这样水不会顺着柱子与柱子之间的空隙流走。

但是约翰一直不知道，这么一个榨汁机，到底能装多少果汁？假设榨汁机周围没有任何东西，也就是说，边界上的水都会流走，有些榨汁机则根本不能装下任何的果汁。

## 样例 #1

### 输入

```
4 5
5 8 7 7
5 2 1 5
7 1 7 1
8 9 6 9
9 8 9 9```

### 输出

```
12```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何计算由不同高度柱子构成的容器能盛装的液体量展开。思路大多是利用 FloodFill 算法，结合优先队列来优化计算过程。难点在于如何确定计算顺序，保证果汁不会洒出，避免时间复杂度过高。多数题解先将边界点加入优先队列，每次取出高度最小的点向四周扩展，根据扩展点与当前点的高度关系更新答案和队列。

### 所选题解
- 作者：☆木辛土申☆ (赞：13)，4星
  - 关键亮点：思路清晰，先介绍 FloodFill 算法及相关例题，再逐步分析本题的朴素做法、改进思路，最后给出正解，且对正解的正确性进行了说明，代码注释详细。
  - 个人心得：作者表示想出正解花了很久，强调自己很弱，同时感谢相关博客给予思路。

### 重点代码
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<queue>

typedef long long LL;
const int SIZE=301;
const int fx[]={0,0,0,1,-1};
const int fy[]={0,1,-1,0,0}; 
int map[SIZE][SIZE],h,w;
bool vis[SIZE][SIZE];

struct Node {
    int x,y,z;
    Node(const int &key1,const int &key2,const int &key3):x(key1),y(key2),z(key3) {}
    inline bool operator <(const Node &in)const {
        return in.z<this->z;
    }
};

template<typename T>inline void read(T &res){
    res=0;char ch=getchar();bool neg=false;
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') neg=true;
    for(; isdigit(ch);ch=getchar()) res=(res<<1)+(res<<3)+(ch^48);
    if(neg) res=-res;
}

inline bool illegal(int x,int y){
    return x<1||x>h||y<1||y>w||vis[x][y];
}

std::priority_queue<Node> q;

inline void init(int w,int h){
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            read(map[i][j]);
            if(i==1||j==1||i==h||j==w){
                q.push(Node(i,j,map[i][j]));
                vis[i][j]=true;
            }
        }
    }
}

inline LL floodfill(){
    LL res=0;
    while(!q.empty()){
        int x=q.top().x;
        int y=q.top().y;
        int h=q.top().z;
        q.pop();
        for(int i=1;i<=4;i++){
            int xx=x+fx[i];
            int yy=y+fy[i];
            if(illegal(xx,yy)) continue;
            if(map[xx][yy]<h) res+=h-map[xx][yy],map[xx][yy]=h;
            q.push(Node(xx,yy,map[xx][yy]));
            vis[xx][yy]=true;
        }
    }
    return res;
}

signed main() {
    read(w),read(h),init(w,h);
    printf("%lld\n",floodfill());
    return 0;
}
```
**核心实现思想**：
1. `init` 函数：读入矩阵信息，将边界点加入优先队列并标记为已访问。
2. `floodfill` 函数：每次从优先队列中取出高度最小的点，向四周扩展。若扩展点未被访问且高度小于当前点，则更新答案并将扩展点高度设为当前点高度，然后将扩展点加入优先队列并标记为已访问。
3. `main` 函数：调用 `init` 函数初始化，调用 `floodfill` 函数计算结果并输出。

### 最优关键思路或技巧
- **数据结构**：使用优先队列维护边界点，每次取出高度最小的点进行扩展，保证了计算顺序的正确性，避免果汁洒出。
- **算法优化**：避免对每个高度的平面进行 FloodFill，通过优先队列优化，时间复杂度降为 $O(nm\log(nm))$。
- **思维方式**：从边界向中间扩展，利用边界的最小高度来确定内部点的盛水量。

### 可拓展之处
同类型题或类似算法套路：这类题目通常涉及到在二维矩阵中计算某种容量或面积，可使用 FloodFill 算法结合优先队列来解决。例如，计算降水后积水的体积、计算岛屿的面积等。

### 推荐题目
1. [P5930 [POI1999] 降水](https://www.luogu.com.cn/problem/P5930)
2. [SP212 WATER - Water among Cubes](https://www.luogu.com.cn/problem/SP212)
3. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)

### 个人心得总结
作者☆木辛土申☆表示想出正解花费了较多时间，强调自己能力有限，同时感谢相关博客给予的思路启发，这提醒我们在解题过程中遇到困难是正常的，多参考他人的思路和经验有助于解决问题。 

---
处理用时：38.50秒