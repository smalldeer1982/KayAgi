# 题目信息

# [ABC357C] Sierpinski carpet

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc357/tasks/abc357_c

非負整数 $ K $ に対して、以下のようにレベル $ K $ のカーペットを定義します。

- レベル $ 0 $ のカーペットは黒いマス $ 1 $ 個のみからなる $ 1\times\ 1 $ のグリッドである。
- $ K\ >\ 0 $ のとき、レベル $ K $ のカーペットは $ 3^K\times\ 3^K $ のグリッドである。 このグリッドを $ 3^{K-1}\times\ 3^{K-1} $ のブロック $ 9 $ 個に分割したとき、
  - 中央のブロックはすべて白いマスからなる。
  - 他の $ 8 $ 個のブロックは、レベル $ (K-1) $ のカーペットである。
 
非負整数 $ N $ が与えられます。  
 レベル $ N $ のカーペットを出力の形式に従って出力してください。

## 说明/提示

### 制約

- $ 0\leq\ N\ \leq\ 6 $
- $ N $ は整数
 
### Sample Explanation 1

レベル $ 1 $ のカーペットは次のような $ 3\times\ 3 $ のグリッドです。 !\[\](https://img.atcoder.jp/abc357/78b18b1b75ea7862c1c216499221b9e8.png) これを出力形式にしたがって出力すると出力例のようになります。

### Sample Explanation 2

レベル $ 2 $ のカーペットは $ 9\times\ 9 $ のグリッドとなります。

## 样例 #1

### 输入

```
1```

### 输出

```
###

#.#

###```

## 样例 #2

### 输入

```
2```

### 输出

```
#########

#.##.##.#

#########

###...###

#.#...#.#

###...###

#########

#.##.##.#

#########```

# AI分析结果

### 题目翻译
#### [ABC357C] 谢尔宾斯基地毯

#### 题目描述
[problemUrl]: https://atcoder.jp/contests/abc357/tasks/abc357_c

对于非负整数 $K$，按以下方式定义 $K$ 级地毯：
- 0 级地毯是一个仅由 1 个黑色格子组成的 $1\times1$ 网格。
- 当 $K > 0$ 时，$K$ 级地毯是一个 $3^K\times3^K$ 的网格。将这个网格分割成 9 个 $3^{K - 1}\times3^{K - 1}$ 的块时：
  - 中间的块全部由白色格子组成。
  - 其他 8 个块是 $(K - 1)$ 级地毯。

给定非负整数 $N$，请按照输出格式输出 $N$ 级地毯。

#### 说明/提示
##### 限制条件
- $0\leq N\leq6$
- $N$ 是整数

##### 样例解释 1
1 级地毯是如下的 $3\times3$ 网格：![图片](https://img.atcoder.jp/abc357/78b18b1b75ea7862c1c216499221b9e8.png)
按照输出格式输出时，就会得到样例输出的结果。

##### 样例解释 2
2 级地毯是一个 $9\times9$ 的网格。

#### 样例 #1
##### 输入
```
1
```
##### 输出
```
###
#.#
###
```

#### 样例 #2
##### 输入
```
2
```
##### 输出
```
#########
#.##.##.#
#########
###...###
#.#...#.#
###...###
#########
#.##.##.#
#########
```

### 综合分析与结论
这些题解的核心思路都是利用递归的方法来生成谢尔宾斯基地毯。由于地毯的定义具有明显的递归特性，即 $K$ 级地毯由 9 个 $(K - 1)$ 级地毯组成，中间的部分为白色，所以递归是解决该问题的自然选择。

各题解的算法要点主要包括：
1. **递归函数的设计**：通常包含当前地毯的级别、左上角坐标等参数，用于确定当前处理的区域。
2. **边界条件的处理**：当级别为 0 时，将对应位置标记为黑色。
3. **中间空白部分的处理**：在递归过程中，标记或跳过中间的部分。

解决的难点在于准确计算每个子区域的位置和大小，以及正确处理递归的边界条件。

### 所选题解
- **作者：LuukLuuk (赞：5)，4星**
  - **关键亮点**：思路清晰，代码注释详细，通过递归标记中间空白部分，然后递归处理四周区域，最后根据标记输出结果。
  - **核心代码**：
```cpp
#include <cmath>
#include <cstdio>
using namespace std;

int mp[10010][10010];//数组开到3^6+1
int n;

void dfs(int a, int b, int k) {
    if (k == 0) return ;
    int len = pow(3, k - 1);
    for (int i = a + len; i < a + 2 * len; ++i) {
        for (int j = b + len; j < b + 2 * len; ++j) {
            mp[i][j] = 1;
        }
    }
    dfs(a, b, k - 1);
    dfs(a + len, b, k - 1);
    dfs(a + 2 * len, b, k - 1);
    dfs(a, b + len, k - 1);
    dfs(a + 2 * len, b + len, k - 1);
    dfs(a, b + 2 * len, k - 1);
    dfs(a + len, b + 2 * len, k - 1);
    dfs(a + 2 * len, b + 2 * len, k - 1);
}

int main() {
    scanf("%d", &n);
    dfs(1, 1, n);
    for (int i = 1; i <= pow(3, n); ++i) {
        for (int j = 1; j <= pow(3, n); ++j) {
            if (mp[i][j] == 1) {
                printf(".");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
    return 0;
}
```
- **作者：XXh0919 (赞：2)，4星**
  - **关键亮点**：使用深搜，通过双重循环枚举子区域，递归处理非中间区域，先将矩阵全部初始化为白色，再将黑色部分标记。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=3e5+15,M=1e3+15;

int n;
char C[M][M];

void dfs(int k,int x1,int y1,int xx,int yy){
    if(k==0){
        C[x1][y1]='#';
        return;
    }
    for(int i=x1;i<=xx;i+=pow(3,k-1)){
        for(int j=y1;j<=yy;j+=pow(3,k-1)){
            if(i!=x1+pow(3,k-1)||j!=y1+pow(3,k-1))
               dfs(k-1,i,j,i+pow(3,k-1)-1,j+pow(3,k-1)-1);
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    memset(C,'.',sizeof C);
    cin>>n;
    int m=pow(3,n);
    dfs(n,1,1,m,m);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            cout<<C[i][j];
        }
        cout<<endl;   
    }
    return 0;
}
```
- **作者：Genius_Star (赞：0)，4星**
  - **关键亮点**：递归处理 `#` 的情况，将初始矩阵全部赋值为 `.`，然后通过递归缩小问题规模，处理 8 个子问题。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const int N = 1005;
char ans[N][N];
void dfs(int n, int x, int y) {
    if (n == 0) {ans[x][y] = '#'; return ;}
    int l = pow(3, n - 1);
    dfs(n - 1, x, y);
    dfs(n - 1, x + l, y);
    dfs(n - 1, x + 2 * l, y);
    dfs(n - 1, x, y + l);
    dfs(n - 1, x + 2 * l, y + l);
    dfs(n - 1, x, y + 2 * l);
    dfs(n - 1, x + l, y + 2 * l);
    dfs(n - 1, x + 2 * l, y + 2 * l);
}
int main() {
    memset(ans, '.', sizeof(ans));
    int n;
    cin >> n;
    dfs(n, 1, 1);
    for (int i = 1; i <= pow(3, n); i ++) {
        for (int j = 1; j <= pow(3, n); j ++)   
            cout << ans[i][j];
        cout << endl;
    }  
    return 0;
}
```

### 最优关键思路或技巧
- **递归思想**：利用地毯的递归定义，将大问题分解为小问题，通过递归函数处理每个子区域。
- **标记法**：可以通过标记中间空白部分，或者先将矩阵全部初始化为白色，再标记黑色部分，最后根据标记输出结果。

### 拓展思路
同类型题或类似算法套路包括分形图形的生成，如科赫雪花、康托集等。这些问题都具有自相似性，可以使用递归的方法来解决。

### 洛谷相似题目
1. [P5461 赦免战俘](https://www.luogu.com.cn/problem/P5461)：同样是通过递归处理矩阵的分块问题。
2. [P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)：涉及递归和分治的思想。
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)：需要将一个数分解为幂次方的形式，也可以使用递归的方法。

### 个人心得摘录与总结
- **作者：YuYuanPQ**：赛时调了八十多分钟，说明在实现递归算法时，可能会遇到边界条件处理不当、子区域位置计算错误等问题，需要仔细调试。

---
处理用时：55.48秒