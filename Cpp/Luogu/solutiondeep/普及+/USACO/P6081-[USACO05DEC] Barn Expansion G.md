# 题目信息

# [USACO05DEC] Barn Expansion G

## 题目描述

Farmer John 有 $N$（$1 \leq N \leq 25000$）个矩形牛棚，它们的墙与坐标轴平行，且坐标在 $[0,10^6]$ 范围内。保证任意两个牛棚不重叠，但可能有公共的墙。

由于奶牛数量不断增加，FJ 打算扩张牛棚。一个牛棚是可以扩张的，当且仅当它的墙与其他牛棚的墙没有公共部分。如果两个牛棚有一个公共角，这两个牛棚均不可扩张。

请你求出有多少牛棚是可以扩张的。

## 说明/提示

前两个牛棚可以扩张。

## 样例 #1

### 输入

```
5
0 2 2 7
3 5 5 8
4 2 6 4
6 1 8 6
0 0 8 1```

### 输出

```
2```

# AI分析结果

### 综合分析与结论
这些题解主要围绕判断矩形是否可扩张展开，核心在于找出与其他矩形有公共边（包括公共角）的矩形。各题解思路和实现方法多样，复杂度也有所不同。部分题解通过拆边、扫描线、双指针、排序等方法优化暴力枚举，降低复杂度。

### 所选题解
- **作者：Tang_chao（4星）**
  - **关键亮点**：思路清晰，将矩形拆边后利用可重集和二分查找，代码实现简洁，复杂度虽最坏为 $O(n^2)$ 但实际跑不满。
- **作者：Henry_C（4星）**
  - **关键亮点**：使用双指针和树状数组，时间复杂度为 $O(n\log_2n)$，能有效处理矩形相接情况，思路独特。
- **作者：ycy1124（4星）**
  - **关键亮点**：利用矩形顶边和底边的匹配关系，通过 vector 存储和排序，结合剪枝优化，复杂度最坏为 $O(n^2)$ 但能通过评测。

### 重点代码及核心思想
#### Tang_chao 的题解
```cpp
struct range{ int l,r,id; };
bool operator < (range x,range y){ return x.l < y.l; }
multiset<range> s[2][M];
void check(int op,int x,int l,int r,int id){
    IT L = s[op][x].lower_bound((range){l,0,0});
    IT R = s[op][x].upper_bound((range){r,0,0});
    for(IT it = L;it != R;it++)
        if(it->id != id){
            ans[id] = 0;
            ans[it->id] = 0;
        }
}
```
**核心思想**：把每个矩形拆成四条边，将同一行的边存入可重集并按左端点排序，对于每条边，二分查找可能有公共边的边，若存在其他矩形的边则标记为不可扩张。

#### Henry_C 的题解
```cpp
struct BIT{
    int c[Nmax];
    int n; 
    void init(int n){
        memset(c, 0, sizeof(c));
        this->n = n;
    }
    inline int lowBit(int x){
        return x&(-x);
    }
    void add(int x, int v){
        while(x<=n){
            c[x] += v;
            x += lowBit(x);
        }
    }
    int get(int x){ 
        int sum = 0;
        while(x>=1){
            sum += c[x];
            x -= lowBit(x);
        }
        return sum;
    }
};
void findYparTouch(int cntN) { 
    int front = 1, back = front;
    while (front <= cntN || back <= cntN) {
        while (front <= cntN && back <= cntN && nArr[front].x != nArr[back].x) {
            front++;
            back++;
        }
        while (front <= cntN && back <= cntN && nArr[front].x == nArr[back].x) {
            back++;
        }
        back--;
        if (front != back) { 
            map<int, int> mStCnt;
            map<int, int> mEnCnt;
            for (int i = front; i <= back; i++) {
                int idCur = nArr[i].id;
                if (nArr[i].at == 0) {
                    mStCnt[idCur] = i - front + 1;
                    if (bTree.get(n) > 0)
                        tou[idCur] = 1; 
                    bTree.add(nArr[i].id, 1);
                } else { 
                    mEnCnt[idCur] = i - front + 1;
                    bTree.add(idCur, -1);
                }
            }
            for (auto iter: mStCnt) { 
                int idCur = iter.first;
                if (mEnCnt[idCur] - mStCnt[idCur] > 1)
                    tou[idCur] = 1;
            }
            front = back = back + 1;
        }
    }
}
```
**核心思想**：用双指针确定 $x$ 值相同的点的区间，利用树状数组统计边的状态，结合 map 处理长区间包含短区间的情况，找出与 $Y$ 轴平行的边相接的矩形。

#### ycy1124 的题解
```cpp
struct Node{
    int l,r,id;
};
vector<Node>a[1000005];
bool bj[25005];
inline bool cmp(Node x1,Node x2){
    return x1.l<x2.l;
}
for(int i=1;i<=n;i++){
    a[y[i][0]].push_back({x[i][0],x[i][1],i});
}
for(int i=1;i<=1000000;i++){
    sort(a[i].begin(),a[i].end(),cmp);
}
for(int i=1;i<=n;i++){
    for(auto it:a[y[i][1]]){
        if(it.l>x[i][1]){
            break;
        }
        if(it.id==i){
            continue;
        }
        if(it.r>=x[i][0]){
            if(!bj[i]){
                bj[i]=1;
                ans--;
            }
            if(!bj[it.id]){
                bj[it.id]=1;
                ans--;
            }
        }
    }
}
```
**核心思想**：将矩形的顶边存到对应 $y$ 坐标的 vector 中并排序，对于每个矩形的底边，枚举对应 $y$ 坐标的 vector 中的顶边，若有重叠则标记为不可扩张。

### 最优关键思路或技巧
- **拆边处理**：将矩形拆成边，便于对边进行操作和比较，如 Tang_chao 和 ycy1124 的题解。
- **排序与二分**：对边按一定规则排序，利用二分查找提高查找效率，如 Tang_chao 的题解。
- **双指针与树状数组**：用双指针确定区间，树状数组统计边的状态，处理矩形相接情况，如 Henry_C 的题解。

### 可拓展之处
同类型题如矩形覆盖问题、矩形相交计数问题等，可使用类似的拆边、排序、扫描线等方法解决。对于更复杂的情况，可能需要使用线段树、平衡树等数据结构优化。

### 推荐题目
- P1856 [USACO5.5] 矩形周长 Picture
- P2774 方格取数问题
- P1387 最大正方形

### 个人心得
无。

---
处理用时：47.18秒