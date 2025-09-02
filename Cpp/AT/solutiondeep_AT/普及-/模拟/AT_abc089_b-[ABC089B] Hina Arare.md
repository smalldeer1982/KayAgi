# 题目信息

# [ABC089B] Hina Arare

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc089/tasks/abc089_b

日本では、$ 3 $ 月 $ 3 $ 日にひなあられという、色のついたお菓子をお供えする習慣があります。

$ 1 $ つの袋があり、ひなあられが $ N $ 個入っています。

この袋には、桃色、白色、緑色の $ 3 $ 種類か、桃色、白色、緑色、黄色の $ 4 $ 種類のひなあられが入っていることが分かっています。

桃色を `P`、白色を `W`、緑色を `G`、黄色を `Y` と表したとき、袋からひなあられを $ 1 $ 粒ずつ取り出していったところ、$ i $ 番目に取り出したひなあられの色は $ S_i $ でした。

この袋に $ 3 $ 種類のひなあられが入っていた場合は `Three`、$ 4 $ 種類のひなあられが入っていた場合は `Four` と出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ S_i $ は `P` か `W` か `G` か `Y`
- $ S_i= $`P`、$ S_j= $`W`、$ S_k= $`G` を満たす $ i,j,k $ が必ず存在する

### Sample Explanation 1

袋に $ 4 $ 種類のひなあられが入っていたので `Four` と出力するとよいです。

### Sample Explanation 2

袋に $ 3 $ 種類のひなあられが入っていたので `Three` と出力するとよいです。

## 样例 #1

### 输入

```
6

G W Y P Y W```

### 输出

```
Four```

## 样例 #2

### 输入

```
9

G W W G P W P G G```

### 输出

```
Three```

## 样例 #3

### 输入

```
8

P Y W G Y W Y Y```

### 输出

```
Four```

# AI分析结果

### 题目中文重写
# [ABC089B] 雏霰

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc089/tasks/abc089_b

在日本，有在3月3日供奉名为雏霰的彩色点心的习俗。

有一个袋子，里面装有 $N$ 个雏霰。

已知这个袋子里装的雏霰有桃色、白色、绿色这3种，或者桃色、白色、绿色、黄色这4种。

当把桃色表示为 `P`、白色表示为 `W`、绿色表示为 `G`、黄色表示为 `Y` 时，从袋子里逐个取出雏霰，第 $i$ 个取出的雏霰颜色为 $S_i$。

如果这个袋子里装的是3种雏霰，则输出 `Three`；如果是4种雏霰，则输出 `Four`。

## 说明/提示

### 制约
- $ 1 \leq N \leq 100 $
- $ S_i $ 为 `P`、`W`、`G` 或 `Y`
- 必定存在满足 $ S_i = $`P`、$ S_j = $`W`、$ S_k = $`G` 的 $ i, j, k $

### 样例解释1
因为袋子里装的是4种雏霰，所以输出 `Four` 即可。

### 样例解释2
因为袋子里装的是3种雏霰，所以输出 `Three` 即可。

## 样例 #1
### 输入
```
6
G W Y P Y W
```
### 输出
```
Four
```

## 样例 #2
### 输入
```
9
G W W G P W P G G
```
### 输出
```
Three
```

## 样例 #3
### 输入
```
8
P Y W G Y W Y Y
```
### 输出
```
Four
```

### 综合分析与结论
这些题解的核心思路都是统计输入中不同颜色的雏霰种类数，然后根据种类数输出 `Three` 或 `Four`。不同题解采用了不同的数据结构和方法来实现去重和计数：
- **使用 `set` 容器**：利用 `set` 自动去重的特性，将输入的字符插入 `set` 中，最后根据 `set` 的大小判断种类数。
- **使用多个变量标记**：定义多个变量分别标记不同颜色是否出现过，最后统计出现的颜色个数。
- **使用计数器**：为每种颜色设置一个计数器，统计每种颜色出现的次数，最后根据计数器的值判断种类数。
- **使用 `map` 容器**：利用 `map` 将字符与数字建立映射，统计每种颜色出现的次数，最后根据映射的值判断种类数。

### 所选题解
- **作者：昒昕 (赞：2)  4星**
    - **关键亮点**：思路清晰，代码简洁，使用 `set` 容器自动去重，通过打表的方式输出结果，减少了判断逻辑。
```cpp
#include <bits/stdc++.h>
using namespace std;

set <char> s; //value的类型为char
string ch[6]={"","","","Three","Four"};
int main() {
    int n; char c;
    cin >>n;
    while (n--) {
        cin >>c;
        s.insert(c); //插入花色
    }
    cout <<ch[(int)s.size()]<< endl; //自动去重，所以只需转换大小
    return 0;
}
```
核心实现思想：使用 `set` 容器存储输入的字符，`set` 会自动去重。最后根据 `set` 的大小，通过打表的方式输出对应的结果。

- **作者：封禁用户 (赞：2)  4星**
    - **关键亮点**：详细解释了使用 `set` 去重的思路，代码结构清晰，通过多个 `if-else` 判断输出结果。
```cpp
#include <iostream>
#include <set>

using namespace std;
typedef long long l;

set<char> st;//注意要存字符型！

int main() {
    l n;
    cin >> n;
    for (l i = 1; i <= n; ++i) {
        char ch;
        cin >> ch;
        st.insert(ch);
    }
    if (st.size() == 1) {
        cout << "One" << endl;
    } else if (st.size() == 2) {
        cout << "Two" << endl;
    } else if (st.size() == 3) {
        cout << "Three" << endl;
    } else if (st.size() == 4) {
        cout << "Four" << endl;
    }
    return 0;
}
```
核心实现思想：使用 `set` 容器存储输入的字符，`set` 会自动去重。最后根据 `set` 的大小，通过多个 `if-else` 判断输出对应的结果。

- **作者：AgrumeStly (赞：1)  4星**
    - **关键亮点**：提供了两种不同的实现方法，思路清晰，代码规范。
```cpp
// 法一
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#define ll long long
using namespace std;
int n, p, w, g, y;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (c == 'P') p = 1;
        if (c == 'W') w = 1;
        if (c == 'G') g = 1;
        if (c == 'Y') y = 1;
    }
    if (p + w + g + y == 3) cout << "Three" << endl;
    else cout << "Four" << endl;
    return 0;
}

// 法二
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#define ll long long
using namespace std;
int n;
bool p, w, g, y;
int main() {
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (c == 'P' && !p) ans++, p = true;
        if (c == 'W' && !w) ans++, w = true;
        if (c == 'G' && !g) ans++, g = true;
        if (c == 'Y' && !y) ans++, y = true;
    }
    if (ans == 3) cout << "Three" << endl;
    else cout << "Four" << endl;
    return 0;
}
```
核心实现思想：
- 法一：定义四个变量分别标记不同颜色是否出现过，最后将四个变量的值相加，根据和判断种类数。
- 法二：定义四个布尔变量分别标记不同颜色是否出现过，若未出现则计数器加1并标记为已出现，最后根据计数器的值判断种类数。

### 最优关键思路或技巧
- **使用 `set` 容器**：`set` 容器具有自动去重的特性，可以方便地统计不同元素的个数。
- **打表**：通过打表的方式可以减少判断逻辑，使代码更加简洁。

### 可拓展之处
同类型题可以是统计字符串中不同字符的个数、统计数组中不同元素的个数等。类似算法套路可以是使用 `set`、`map` 等数据结构进行去重和计数。

### 推荐洛谷题目
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：统计不同元素的个数。
2. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：使用布尔变量标记状态。
3. [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：简单的输入输出和数组操作。

### 个人心得
题解中未包含个人心得。

---
处理用时：52.86秒