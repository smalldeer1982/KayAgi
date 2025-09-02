# 题目信息

# Gargari and Bishops

## 题目描述

Gargari is jealous that his friend Caisa won the game from the previous problem. He wants to prove that he is a genius.

He has a $ n×n $ chessboard. Each cell of the chessboard has a number written on it. Gargari wants to place two bishops on the chessboard in such a way that there is no cell that is attacked by both of them. Consider a cell with number $ x $ written on it, if this cell is attacked by one of the bishops Gargari will get $ x $ dollars for it. Tell Gargari, how to place bishops on the chessboard to get maximum amount of money.

We assume a cell is attacked by a bishop, if the cell is located on the same diagonal with the bishop (the cell, where the bishop is, also considered attacked by it).

## 样例 #1

### 输入

```
4
1 1 1 1
2 1 1 0
1 1 1 0
1 0 0 1
```

### 输出

```
12
2 2 3 2
```

# AI分析结果

### 题目内容
# Gargari和象

## 题目描述
Gargari嫉妒他的朋友Caisa赢得了上一题的游戏。他想证明自己是个天才。

他有一个 $n×n$ 的棋盘。棋盘的每个格子都写有一个数字。Gargari想在棋盘上放置两个象，使得没有一个格子同时被它们两个攻击。考虑一个写有数字 $x$ 的格子，如果这个格子被其中一个象攻击，Gargari将从中获得 $x$ 美元。告诉Gargari如何在棋盘上放置象以获得最大金额。

我们假设一个格子被象攻击，如果该格子与象位于同一条对角线上（象所在的格子也被认为被它攻击）。

## 样例 #1
### 输入
```
4
1 1 1 1
2 1 1 0
1 1 1 0
1 0 0 1
```
### 输出
```
12
2 2 3 2
```
### 算法分类
贪心
### 题解综合分析与结论
这些题解的核心思路均基于贪心策略，利用国际象棋中象的走法特点，即象斜向移动，若将棋盘黑白染色，两个象分别放置在不同颜色格子上就不会相互攻击。因此通过黑白染色，分别计算黑白格子放置象所能获得的最大收益，最后将两者相加。

各题解的算法要点在于先预处理出每条斜线上数字的总和，这样在枚举每个格子时能快速计算放置象在该格时的收益。难点在于如何高效地预处理斜线和以及准确计算每个格子的收益。所有题解在思路上较为一致，主要差异体现在代码实现细节与优化程度上。

### 所选的题解
- **作者：Yizhixiaoyun (5星)**
    - **关键亮点**：思路阐述清晰，结合象的走法图示，便于理解。代码实现上通过宏定义简化代码书写，在输入部分采用了自定义的快速读入函数，整体代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define lf i+j
#define rt i-j+2500
#define int long long
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}while(c>='0' && c<='9') {x=x*10+c-48;c=getchar();}return x*f;}
const int maxn=5002;
int n;
int tot1,tot2;
int x,y,xx,yy;
int a[maxn][maxn];
int p[maxn],q[maxn];
inline void init(){
    n=read();
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=n;++j) a[i][j]=read();
    }
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=n;++j){
            p[lf]+=a[i][j];q[rt]+=a[i][j];
        }
    }
}
inline void print(){
    cout<<tot1+tot2<<endl;
    cout<<x<<" "<<y<<" "<<xx<<" "<<yy<<" ";
}
signed main(){
    init();
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=n;++j){
            if((i+j)%2==1){
                if(tot1<=p[lf]+q[rt]-a[i][j]){
                    tot1=p[lf]+q[rt]-a[i][j];
                    x=i;y=j;
                }
            }
            else if(tot2<=p[lf]+q[rt]-a[i][j]){
                tot2=p[lf]+q[rt]-a[i][j];
                xx=i;yy=j;
            }
        }
    }
    print();
}
```
    - **核心实现思想**：通过宏定义 `lf` 和 `rt` 分别表示象所在格子横纵坐标之和与横纵坐标之差加上偏移量，在 `init` 函数中读入棋盘数据并预处理每条斜线的和，在 `main` 函数中枚举每个格子，根据格子颜色（横纵坐标之和的奇偶性）分别计算并更新放置象在该格时的最大收益及对应坐标，最后通过 `print` 函数输出结果。
- **作者：Nephren_Sakura (4星)**
    - **关键亮点**：对时间复杂度分析清晰，指出暴力计算每个点值的时间复杂度为 $O(n^3)$ 无法通过题目，进而提出通过处理每条斜线和来优化的方法。代码逻辑清晰，变量命名具有一定可读性。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[2005][2005],s[4005],S[4005],maxi[2],x[2]={1,1},y[2]={1,2};//2~2*n
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            cin>>a[i][j];
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            s[i+j]+=a[i][j];
            S[i-j+1+n]+=a[i][j];
        }
    }
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(maxi[(i+j)%2]<s[i+j]+S[i-j+1+n]-a[i][j])
                maxi[(i+j)%2]=s[i+j]+S[i-j+1+n]-a[i][j],x[(i+j)%2]=i,y[(i+j)%2]=j;
    cout<<maxi[0]+maxi[1]<<'\n'<<x[0]<<' '<<y[0]<<' '<<x[1]<<' '<<y[1];
    return 0;
}
```
    - **核心实现思想**：定义数组 `s` 和 `S` 分别记录象所在格子横纵坐标之和与横纵坐标之差加上偏移量对应的斜线和。先读入棋盘数据并预处理斜线和，然后枚举每个格子，根据格子颜色计算放置象在该格时的收益，更新最大收益及对应坐标，最后输出结果。
- **作者：I_am_big_SB (4星)**
    - **关键亮点**：对思路的讲解详细，适合初学者理解。在代码注释中指出了容易出错的地方，如要开 `long long`，更新答案时判断条件要用大于等于等，具有很好的提示作用。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, x, y, x2, y2, ans1, ans2, a[2005][2005], b[4005], c[4005];//b,c 数组要开两倍，不然会当场 RE
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) scanf("%lld", &a[i][j]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            b[i + j - 1] += a[i][j];
            c[n + j - i] += a[i][j];//加 n 防越界
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if ((i + j) % 2) {
                if (b[i + j - 1] + c[n + j - i] - a[i][j] >= ans1) {
                    ans1 = b[i + j - 1] + c[n + j - i] - a[i][j];
                    x = i;
                    y = j;
                }
            } else {
                if (b[i + j - 1] + c[n + j - i] - a[i][j] >= ans2) {
                    ans2 = b[i + j - 1] + c[n + j - i] - a[i][j];
                    x2 = i;
                    y2 = j;
                }
            }
        }
    }
    printf("%lld\n%lld %lld %lld %lld", ans1 + ans2, x2, y2, x, y);
    return 0;
}
```
    - **核心实现思想**：定义数组 `b` 和 `c` 分别记录象所在格子横纵坐标之和减1与横纵坐标之差加 `n` 对应的斜线和。读入棋盘数据并预处理斜线和后，枚举每个格子，根据格子颜色计算放置象在该格时的收益，更新最大收益及对应坐标，最后输出结果。

### 最优关键思路或技巧
利用棋盘黑白染色，将问题转化为两个独立的子问题，分别求黑白格子放置象的最大收益。通过预处理每条斜线上数字的总和，优化计算每个格子收益的时间复杂度，从 $O(n^3)$ 降低到 $O(n^2)$。

### 同类型题或类似算法套路拓展
此类题目通常基于某种棋盘布局或特定规则，利用规则特性将问题简化，通过预处理关键信息（如本题的斜线和）来优化计算。类似套路可应用于其他棋盘类策略问题，比如在棋盘上放置多种棋子且有不同限制条件的情况。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：同样是基于贪心策略，在特定规则下（不同大臣的左右手数字不同，国王分发金币）求最大金币数，与本题类似，需要分析规则并找到合适的贪心策略。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：通过合理安排生产顺序来优化总时间，也是贪心算法的应用，与本题思路类似，需找到关键信息（如本题斜线和，该题机器加工时间）并据此进行策略选择。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：每次选择最小的两堆果子合并，以达到最小总代价，同样是贪心策略的体现，与本题一样，要根据题目条件确定贪心方向。

### 个人心得摘录与总结
- **作者：I_am_big_SB**：强调了一些容易忽略的细节，如要开 `long long`，更新答案判断条件要用大于等于，否则会被全 0 数据 hack，这些细节对于 AC 题目很关键。 

---
处理用时：99.78秒