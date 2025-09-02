# 题目信息

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
14
```

## 样例 #3

### 输入

```
9 3
```

### 输出

```
14
```

## 样例 #4

### 输入

```
3 6
```

### 输出

```
12
```

## 样例 #5

### 输入

```
506 2708
```

### 输出

```
3218
```

# AI分析结果

### 题目内容（中文重写）
# 多色马克笔

## 题目描述
有一个无限大的正方形瓷砖板。最初，所有瓷砖都是白色的。
沃娃（Vova）有一支红色马克笔和一支蓝色马克笔。红色马克笔可以涂 $a$ 块瓷砖，蓝色马克笔可以涂 $b$ 块瓷砖。如果某块瓷砖不是白色的，那么任何颜色的马克笔都不能再涂它。每支马克笔都必须用完，所以最终整个板上应该正好有 $a$ 块红色瓷砖和正好 $b$ 块蓝色瓷砖。
沃娃想要涂这样一组瓷砖：
 - 它们将形成一个矩形，由正好 $a + b$ 块涂色瓷砖组成；
 - 至少有一种颜色的所有瓷砖也形成一个矩形。

以下是一些正确涂色的例子：
![正确例子](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)
以下是一些错误涂色的例子：
![错误例子](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)
在所有正确的涂色方案中，沃娃想选择周长最小的那个。沃娃能得到的最小周长是多少？
保证至少存在一种正确的涂色方案。

## 说明/提示
前四个例子对应于题目描述中的第一张图片。
注意，对于所有例子都存在多种正确的涂色方案。
在第一个例子中，你也可以制作一个边长为 $1$ 和 $8$ 的矩形，尽管它的周长将是 $18$，大于 $8$。
在第二个例子中，你可以制作相同的边长为 $3$ 和 $4$ 的结果矩形，但红色瓷砖将形成边长为 $1$ 和 $3$ 的矩形，蓝色瓷砖将形成边长为 $3$ 和 $3$ 的矩形。

## 样例 #1
### 输入
```
4 4
```
### 输出
```
12
```

## 样例 #2
### 输入
```
3 9
```
### 输出
```
14
```

## 样例 #3
### 输入
```
9 3
```
### 输出
```
14
```

## 样例 #4
### 输入
```
3 6
```
### 输出
```
12
```

## 样例 #5
### 输入
```
506 2708
```
### 输出
```
3218
```

### 题解综合分析与结论
所有题解的核心思路都是基于数学原理，通过枚举矩形的边长来寻找满足条件的最小周长矩形。主要围绕以下要点：
 - **枚举大矩形边长**：利用矩形面积与边长关系，由于矩形面积为 \(a + b\)，其边长必然是 \(a + b\) 的因数，所以只需枚举到 \(\sqrt{a + b}\)，且为使周长最小，从 \(\lfloor\sqrt{a + b}\rfloor\) 开始从大到小枚举。
 - **判断颜色矩形可行性**：对于当前枚举的大矩形边长，判断 \(a\) 或 \(b\) 能否构成矩形，即找到满足 \(j\leq i\) 且 \(j\mid a\)（或 \(j\mid b\)），同时 \(\frac{a}{j}\leq \frac{a + b}{i}\)（或 \(\frac{b}{j}\leq \frac{a + b}{i}\)）的 \(j\)。部分题解通过预处理因数、利用单调性等方式优化此判断过程。

各题解在实现细节和优化程度上存在差异，以下是对各题解的评分：
 - **作者：Siyuan**：5星。思路清晰，先点明枚举矩形形态数量及贪心枚举较短边思路，再阐述判断颜色矩形可行性时利用单调性优化，时间复杂度分析准确，代码简洁且注释清晰。
 - **作者：BLUESKY007**：4星。对题意理解准确，阐述从数学原理反推枚举方式，代码实现直接，但在优化方面不如Siyuan的题解，如判断部分可进一步优化。
 - **作者：guanyf**：4星。分析思路详细，先给出朴素思路再阐述优化点，提供两种代码实现，后一种利用单调性优化，代码可读性较好。

### 所选题解
 - **作者：Siyuan**
    - **星级**：5星
    - **关键亮点**：思路清晰，利用贪心从大到小枚举矩形较短边，且指出判断颜色矩形可行性时利用因子单调性优化，时间复杂度分析准确，代码简洁明了。
    - **核心代码**：
```cpp
long long solve(long long tot,long long a) {
    std::vector<int> f;
    for(int i=1;1LL*i*i<=a;++i) if(a%i==0) f.push_back(i);
    int p=(int)f.size()-1;
    for(int i=sqrt(tot);i>=1;--i) {
        if(tot%i) continue;
        while(f[p]>i) --p;
        if(a/f[p]<=tot/i) return 2LL*(i+tot/i);
    }
    return 1LL<<60;
}
int main() {
    long long n,m;
    scanf("%lld%lld",&n,&m);
    printf("%lld\n",std::min(solve(n+m,n),solve(n+m,m)));
    return 0;
}
```
    - **核心实现思想**：`solve` 函数中，先预处理出 \(a\) 的因子存于 `f` 数组，从 \(\sqrt{tot}\) 开始枚举大矩形较短边 \(i\)，对于每个 \(i\)，利用指针 \(p\) 找到满足条件的最大因子 \(f[p]\)，若满足 \(a/f[p]<=tot/i\)，则返回当前矩形周长，最后在 `main` 函数中对 \(a\) 和 \(b\) 分别调用 `solve` 函数取最小值。
 - **作者：BLUESKY007**
    - **星级**：4星
    - **关键亮点**：从数学原理出发，根据矩形周长与长宽关系反推枚举方式，代码实现简洁直接。
    - **核心代码**：
```cpp
bool check(int u,long long v){
    for(int i=1;i<=u;i++){
        if(a%i==0){
            long long rep=a/i;
            if(i<=u&&rep<=v){
                return true;
            }
        }
    }
    for(int i=1;i<=u;i++){
        if(b%i==0){
            long long rep=b/i;
            if(i<=u&&rep<=v){
                return true;
            }
        }
    }
    return false;
}

int main(){
    scanf("%lld%lld",&a,&b);
    c=a+b;
    for(int i=(int)sqrt(c);i;i--){
        if(c%i==0){
            d=c/i;
            if(check(i,d)){
                printf("%lld",(d+i)*2);
                return 0;
            }
        }
    }
    return 0;
}
```
    - **核心实现思想**：`check` 函数用于判断当前大矩形边长 \(u\) 和 \(v\) 下，\(a\) 或 \(b\) 是否能构成矩形，在 `main` 函数中从 \(\sqrt{a + b}\) 开始枚举大矩形宽 \(i\)，若满足条件则输出最小周长。
 - **作者：guanyf**
    - **星级**：4星
    - **关键亮点**：先给出朴素思路，再详细阐述优化点，提供两种代码实现，后一种利用单调性优化判断过程。
    - **核心代码（优化后）**：
```cpp
LL a, b, id[2] = {INT_MAX, INT_MAX};
bool check(LL tot, LL x, LL y) {
    LL& i = id[tot == b];
    for (i = min(i, x); tot % i; i--) {
    }
    return (tot / i <= y);
}
int main() {
    ios::sync_with_stdio(0);
    cin >> a >> b;
    for (LL i = sqrt(a + b); i >= 1; i--) {
        if ((a + b) % i == 0) {
            LL j = (a + b) / i;
            if (check(a, i, j) || check(b, i, j)) {
                cout << 2 * (i + j), exit(0);
            }
        }
    }
    return 0;
}
```
    - **核心实现思想**：`check` 函数利用 `id` 数组记录上次枚举位置，从 \(\min(i,x)\) 开始枚举，找到满足条件的因子，在 `main` 函数中枚举大矩形边长，判断是否满足条件，满足则输出最小周长。

### 最优关键思路或技巧
 - **利用数学性质缩小枚举范围**：通过矩形面积与边长的关系，将大矩形边长的枚举范围缩小到 \(\sqrt{a + b}\)，并且根据周长与长宽差的关系，从大到小枚举边长以更快找到最小周长。
 - **利用单调性优化判断**：在判断某种颜色能否构成矩形时，利用因子的单调性，通过记录上次枚举位置等方式避免重复无效枚举，提高效率。

### 可拓展之处
此类题目属于基于数学性质的枚举优化类型，类似题目通常围绕几何图形的面积、周长与数量关系，通过分析数学性质来优化暴力枚举过程。常见套路是先确定枚举对象，再利用相关数学性质（如因数关系、单调性等）缩小枚举范围或优化判断条件。

### 洛谷相似题目推荐
 - [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：涉及数论知识，通过分析斐波那契数列的性质优化计算最大公约数的过程，与本题利用数学性质优化枚举类似。
 - [P2619 神奇的幻方](https://www.luogu.com.cn/problem/P2619)：根据幻方的数学特性，通过特定规律填充数字，与本题依据矩形数学性质进行枚举判断有相似思维方式。
 - [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：通过分析数的因数、最大公约数和最小公倍数的关系来枚举求解，和本题利用因数关系解决问题思路相近。

### 个人心得摘录与总结
暂无题解包含个人心得。 

---
处理用时：46.54秒