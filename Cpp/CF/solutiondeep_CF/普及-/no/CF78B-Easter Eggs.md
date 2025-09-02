# 题目信息

# Easter Eggs

## 题目描述

The Easter Rabbit laid $ n $ eggs in a circle and is about to paint them.

Each egg should be painted one color out of 7: red, orange, yellow, green, blue, indigo or violet. Also, the following conditions should be satisfied:

- Each of the seven colors should be used to paint at least one egg.
- Any four eggs lying sequentially should be painted different colors.

Help the Easter Rabbit paint the eggs in the required manner. We know that it is always possible.

## 说明/提示

The way the eggs will be painted in the first sample is shown on the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF78B/89e74426378989547383b9ed8ec253c74d4ce7d9.png)

## 样例 #1

### 输入

```
8
```

### 输出

```
ROYGRBIV
```

## 样例 #2

### 输入

```
13
```

### 输出

```
ROYGBIVGBIVYG
```

# AI分析结果

【题目内容（中文重写）】
# 复活节彩蛋

## 题目描述
复活节兔子在一个圆圈里放了 $n$ 个彩蛋，准备给它们上色。

每个彩蛋都要从 7 种颜色中选一种来涂：红色、橙色、黄色、绿色、蓝色、靛色或紫色。此外，还需满足以下条件：
- 7 种颜色每种都至少要用来涂一个彩蛋。
- 任意连续的 4 个彩蛋必须涂不同的颜色。

请帮助复活节兔子按照要求给彩蛋上色。我们知道这总是可行的。

## 说明/提示
第一个样例中彩蛋的涂色方式如图所示：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF78B/89e74426378989547383b9ed8ec253c74d4ce7d9.png)

## 样例 #1
### 输入
```
8
```
### 输出
```
ROYGRBIV
```

## 样例 #2
### 输入
```
13
```
### 输出
```
ROYGBIVGBIVYG
```

【算法分类】
构造

【综合分析与结论】
这些题解的核心目标都是构造出满足条件的彩蛋涂色方案。不同题解的思路和方法各有不同：
- **分类讨论法**：以 Colead 的题解为代表，根据 $n$ 对 7 取余的不同情况进行分类讨论，分别确定每种情况下的涂色方案。这种方法逻辑清晰，但代码量较大。
- **循环节拼接法**：如 SUNCHAOYI 的题解，以 `ROGYBIV` 为循环节，对于非整除情况，通过拼接 `YBIV` 等部分来避免颜色重复。
- **固定模式法**：多数题解采用先循环输出 `ROYG`，最后输出 `BIV` 的方式，保证 7 种颜色都出现且相邻 4 个彩蛋颜色不同。

难点在于处理环的情况，即要保证首尾相连处的 4 个彩蛋颜色也不同。

【所选题解】
- **Colead（5星）**
    - **关键亮点**：思路清晰，通过详细的分类讨论，对每种余数情况进行了严谨的分析和推导，代码实现也很规范，注释详细。
    - **个人心得**：无
- **翼德天尊（4星）**
    - **关键亮点**：先指出了常见的错误做法及原因，然后给出正确的构造方法，逻辑严谨，代码实现中使用了快读优化。
    - **个人心得**：看到题目第一感觉很水，按 7 种颜色轮流枚举会出错，原因是没考虑 $n\%7\ne0$ 时首尾颜色可能相同的情况。
- **江山_远方（4星）**
    - **关键亮点**：先展示了错误的做法及错误原因，然后通过简单修改代码得到正确的构造方案，过程清晰。
    - **个人心得**：一开始以为 7 种颜色轮流枚举就能解决问题，后来发现是环的问题，首尾也要判断是否重复。

【重点代码】
### Colead 的核心代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int k=n/7;
    if(n%7==0)
    {
        for(int i=1;i<=k;i++)
        {
            cout<<"ROYGBIV";
        }
        return 0;
    }
    if(n%7==1)
    {
        for(int i=1;i<=k;i++)
        {
            cout<<"ROYGBIV";
        }
        cout<<"G";
        return 0;
    }
    // 其他余数情况代码类似，省略
    return 0;
}
```
**核心实现思想**：根据 $n$ 对 7 取余的不同情况，分别确定输出的涂色方案。

### 翼德天尊的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char ans[105],color[8]={'a','R','O','Y','G','B','I','V'};
int read(){
    int w=0,f=1;
    char c=getchar();
    while (c>'9'||c<'0'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        w=(w<<3)+(w<<1)+(c^48);
        c=getchar();
    }
    return w*f;
}

int main(){
    n=read();
    for (int i=0;i<n-3;i++)
        ans[i]=color[i%4+1];
    for (int i=5;i<=7;i++)
        ans[n+i-8]=color[i];
    for (int i=0;i<n;i++)
        putchar(ans[i]);
    return 0;
}
```
**核心实现思想**：前 $n - 3$ 个彩蛋循环使用前 4 种颜色，最后 3 个彩蛋使用剩下的 3 种颜色。

### 江山_远方的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const char c[]={' ','R','O','Y','G','B','I','V'};
int n;
int main()
{
    cin>>n;
    for(int i=1;i<=n-3;i++)putchar(c[(i-1)%4+1]);
    for(int i=5;i<=7;i++)putchar(c[i]);
    return 0; 
}
```
**核心实现思想**：前 $n - 3$ 个彩蛋按 `ROYG` 循环输出，最后 3 个彩蛋输出 `BIV`。

【关键思路或技巧】
- 处理环的问题时，通过先固定前面的涂色模式，再处理剩余的彩蛋，保证首尾相连处的颜色要求。
- 利用取余运算实现颜色的循环输出。

【拓展思路】
同类型题可能会改变颜色数量、相邻不同颜色的个数或其他限制条件，但整体思路还是通过构造满足条件的方案来解决问题。类似的算法套路可以应用在其他需要构造特定序列或排列的题目中。

【推荐题目】
- P1002 过河卒
- P1048 采药
- P1216 [USACO1.5] 数字三角形 Number Triangles

---
处理用时：44.41秒