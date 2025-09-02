# 题目信息

# [USACO08OCT] Wheel Rotation G

## 题目描述

Farmer John has an old-time thresher (wheat harvester) that requires belts to be installed on various gears to turn the parts. The engine drives pulley 1 in a clockwise direction which attaches via a belt to pulley 2. Pulley 2 attaches via a belt to pulley 3 and so on through a total of N (2 <= N <= 1,000) pulleys (and N-1 belts).

The diagram above depicts the two ways a belt can be installed between two gears. In this illustration, pulley 1's belt directly drives pulley 2 (a 'straight' connection) and thus they will rotate in the same direction. Pulley 3 drives pulley 4 via a 'crossed belt' that reverses the direction of the rotation.

Given a list of the belt types that connect the pulleys along with the fact that pulley 1 is driven in a clockwise direction by the engine, determine the drive direction of pulley N. Each belt is described by three integers:

```cpp
* S_i -- the driving (source) pulley 
* D_i -- the driven (destination) pulley 
* C_i -- the connection type (0=straight, 1=crossed) 
Unfortunately, FJ lists the belts in random order. 
By way of example, consider the illustration below. N = 4, and pulley 1 is driven clockwise by the thresher engine. Straight 
belts drive pulley 2 and then pulley 3, so they rotate clockwise. The crosswise belt reverses the rotation direction so pulley 4 (pulley N) rotates counterclockwise. 
```
POINTS: 70
约翰有一个过时的收割机，需要在它的各种滑轮上装配皮带才能让收割机的各个部分运作起 来.引擎能够驱动滑轮1向顺时针方向转动，滑轮1通过一条皮带又连接到滑轮2.滑轮2又通过一 条皮带连接到滑轮3，等等，总共有N(2 <= N <= 1000)个滑轮和N - 1条皮带.

皮带连接两个滑轮有两种方式：直接连接和交叉连接.直接连接的两个滑轮旋转方向相同， 即同为顺时针或同为逆时针.交叉连接的两个滑轮旋转方向相反.

现在给出一个列表，里面列出所有皮带的连接方式.已经知道滑轮1被引擎驱动着向顺时针方 向转动.每一条皮带由下面三个数定义：

•驱动滑轮S，输入驱动力的滑轮.

•被驱动滑轮D;，被驱使转动的滑轮.

•连接类型C，0表示直接连接，1表示交叉连接.

不幸的是，约翰的这个列表中，皮带的顺序是混乱的.所以请你写一个程序来求出滑轮N的 转动方向.


## 说明/提示

As in the example illustration.


## 样例 #1

### 输入

```
4 
2 3 0 
3 4 1 
1 2 0 
```

### 输出

```
1 
```

# AI分析结果



### 综合分析与结论
题目要求根据滑轮间的连接方式确定最终滑轮的旋转方向。各题解核心思路是统计所有交叉连接的次数奇偶性，等效为异或运算。正确解法无需考虑边顺序，直接统计所有连接的交叉类型总和即可。

---

### 高星题解推荐

#### 1. 题解作者：NTG_Adiord (★★★★★)
**关键亮点**：极简代码，利用异或性质直接统计结果，时间复杂度O(n)。  
**代码核心**：
```cpp
int main(){
    int n,a; bool b=0; // 初始化b为0
    scanf("%d",&n); n--;
    while(n--) scanf("%d%d%d",&a,&a,&a), b^=a; // 直接异或所有C_i
    printf("%d",b);
}
```
**注意**：代码假设所有边均在链上，正确性依赖题目结构条件。

#### 2. 题解作者：codemap (★★★★★)
**关键亮点**：思路清晰，直接统计交叉次数的奇偶性，代码简洁。  
**代码核心**：
```cpp
int main() {
    int n, s=0;
    cin >> n;
    for(int i=1; i<n; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        s += c; // 累加交叉次数
    }
    cout << (s%2); // 输出奇偶性
}
```

#### 3. 题解作者：kgory (★★★★)
**关键亮点**：通过排序构建链式处理，逻辑清晰但复杂度稍高。  
**关键代码**：
```cpp
sort(a+1, a+n+1, cmp); // 按s排序
for(int i=1; i<=n; i++) {
    if(a[i].c==0) 
        b[a[i].d] = b[a[i].s]; // 直连方向相同
    else 
        b[a[i].d] = !b[a[i].s]; // 交叉方向相反
}
printf("%d",b[n]);
```

---

### 最优思路提炼
**核心技巧**：利用链式结构中每条边必然被遍历的性质，直接统计所有交叉连接（C_i）的异或总和或奇偶次数。数学上，异或运算的累加等价于奇偶判断，无需关注边顺序。

---

### 拓展与相似题目
1. **P1469 找筷子**（异或性质应用）  
2. **P5657 格雷码**（位运算与异或）  
3. **P3912 素数个数**（数学性质统计）

---

### 个人心得摘录
- **NTG_Adiord**：发现题目隐含的链式结构，直接忽略边顺序，极大简化代码。  
- **codemap**：最初误认为需排序，后通过数学性质优化，体现思维灵活性。  
- **调试教训**：注意代码细节（如运算符优先级、变量初始化），避免低级错误。

---
处理用时：203.07秒