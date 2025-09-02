# 题目信息

# Blown Garland

## 题目描述

Nothing is eternal in the world, Kostya understood it on the 7-th of January when he saw partially dead four-color garland.

Now he has a goal to replace dead light bulbs, however he doesn't know how many light bulbs for each color are required. It is guaranteed that for each of four colors at least one light is working.

It is known that the garland contains light bulbs of four colors: red, blue, yellow and green. The garland is made as follows: if you take any four consecutive light bulbs then there will not be light bulbs with the same color among them. For example, the garland can look like "RYBGRYBGRY", "YBGRYBGRYBG", "BGRYB", but can not look like "BGRYG", "YBGRYBYGR" or "BGYBGY". Letters denote colors: 'R' — red, 'B' — blue, 'Y' — yellow, 'G' — green.

Using the information that for each color at least one light bulb still works count the number of dead light bulbs of each four colors.

## 说明/提示

In the first example there are no dead light bulbs.

In the second example it is obvious that one blue bulb is blown, because it could not be light bulbs of other colors on its place according to the statements.

## 样例 #1

### 输入

```
RYBGRYBGR
```

### 输出

```
0 0 0 0```

## 样例 #2

### 输入

```
!RGYB
```

### 输出

```
0 1 0 0```

## 样例 #3

### 输入

```
!!!!YGRB
```

### 输出

```
1 1 1 1```

## 样例 #4

### 输入

```
!GB!RG!Y!
```

### 输出

```
2 1 1 0```

# AI分析结果

### 题目内容中文重写
# 坏掉的花环

## 题目描述
世界上没有什么是永恒的，科斯特亚在1月7日看到部分坏掉的四色花环时就明白了这一点。

现在他的目标是更换坏掉的灯泡，然而他不知道每种颜色需要多少个灯泡。不过可以保证的是，四种颜色中每种颜色至少有一个灯泡是亮着的。

已知花环包含四种颜色的灯泡：红色、蓝色、黄色和绿色。花环的排列规则是：任意四个连续的灯泡颜色都不相同。例如，花环可以是 “RYBGRYBGRY”、“YBGRYBGRYBG”、“BGRYB” 这样的，但不能是 “BGRYG”、“YBGRYBYGR” 或 “BGYBGY” 这样的。字母代表颜色：'R' 表示红色，'B' 表示蓝色，'Y' 表示黄色，'G' 表示绿色。

根据每种颜色至少有一个灯泡还亮着这一信息，计算出四种颜色中每种颜色坏掉的灯泡数量。

## 说明/提示
在第一个样例中，没有坏掉的灯泡。

在第二个样例中，很明显有一个蓝色灯泡坏掉了，因为根据规则，这个位置不可能是其他颜色的灯泡。

## 样例 #1
### 输入
```
RYBGRYBGR
```
### 输出
```
0 0 0 0
```

## 样例 #2
### 输入
```
!RGYB
```
### 输出
```
0 1 0 0
```

## 样例 #3
### 输入
```
!!!!YGRB
```
### 输出
```
1 1 1 1
```

## 样例 #4
### 输入
```
!GB!RG!Y!
```
### 输出
```
2 1 1 0
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是利用花环颜色每四个一循环的规律来解题。具体做法是先找出每种颜色在模 4 意义下的位置，再统计未知字符（'!'）在对应位置出现的次数，从而得到每种颜色坏掉的灯泡数量。
- **思路对比**：大部分题解思路相似，都是通过遍历字符串确定颜色位置和统计未知字符；`Steve_xh` 的题解考虑了特殊情况，通过交换变量避免下标冲突。
- **算法要点**：利用颜色循环规律，通过取模运算确定颜色位置和统计未知字符。
- **解决难点**：主要难点在于确定每种颜色在循环中的位置，部分题解通过交换变量解决特殊情况。

### 题解评分
| 作者 | 评分 | 思路清晰度 | 代码可读性 | 优化程度 |
| --- | --- | --- | --- | --- |
| x1489631649 | 4星 | 清晰，明确指出颜色每四个一循环 | 较高，代码结构简单 | 一般 |
| _byta | 4星 | 清晰，逻辑明确 | 较高，代码简洁 | 一般 |
| DiDi123 | 4星 | 清晰，有详细分析 | 较高，代码结构合理 | 一般 |

### 所选题解
- **x1489631649（4星）**：关键亮点是思路清晰，直接利用颜色循环规律解题。
- **_byta（4星）**：关键亮点是代码简洁，逻辑明确。
- **DiDi123（4星）**：关键亮点是有详细的分析过程，代码结构合理。

### 重点代码
#### x1489631649
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[5];
char n[1000];
int main()
{
    cin.get(n,1000);
    int l=strlen(n),a,b,c,d;
    for(int i=0;i<l;i++)
    {
        if(n[i]=='R')
            a=i%4;
        if(n[i]=='B')
            b=i%4;
        if(n[i]=='Y') 
            c=i%4;
        if(n[i]=='G')
            d=i%4;
        if(n[i]=='!')
            f[i%4]++;
    }
    cout<<f[a]<<" "<<f[b]<<" "<<f[c]<<" "<<f[d]<<" "<<endl;
}
```
核心实现思想：遍历字符串，记录每种颜色在模 4 意义下的位置，统计未知字符在对应位置的数量。

#### _byta
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105];
int a[5];
int main()
{
    scanf("%s",s);
    int len = strlen(s);
    int r,b,y,g;
    for(int i=0;i<len;i++)
    {
        if(s[i]=='R') r = i % 4;
        else if(s[i]=='B') b = i % 4;
        else if(s[i]=='Y') y = i % 4;
        else if(s[i]=='G') g = i % 4;
        else a[i%4]++;
    }
    printf("%d %d %d %d\n",a[r],a[b],a[y],a[g]);
}
```
核心实现思想：与上一题解类似，通过遍历字符串确定颜色位置和统计未知字符。

#### DiDi123
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int ans[4];
int trans(char ch)
{
    if(ch=='R') return 0;
    if(ch=='B') return 1;
    if(ch=='Y') return 2;
    if(ch=='G') return 3;
}
int main()
{
    cin>>s;
    for(int i=0;i<=min(int(s.length()-1),3);i++)
    {
        int cnt=0,opt;
        for(int j=i;j<s.length();j+=4)
        {
            if(s[j]=='!') cnt++;
            else opt=trans(s[j]);
        }
        ans[opt]+=cnt;
    }
    for(int i=0;i<=3;i++)
        cout<<ans[i]<<' ';
}
```
核心实现思想：先分组，位置除以 4 余数一样的数一组，统计每组中未知字符的数量并累加到对应颜色的答案中。

### 最优关键思路或技巧
利用花环颜色每四个一循环的规律，通过取模运算确定每种颜色在循环中的位置，从而统计出每种颜色坏掉的灯泡数量。

### 拓展思路
同类型题可能会有不同的循环规律或条件限制，解题时可以先找出规律，再根据规律进行统计和计算。类似算法套路可以应用于处理周期性问题，如密码解密、图案填充等。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)

### 个人心得
部分题解提到了特殊情况的处理，如 `Steve_xh` 的题解中提到的 `R!!!!` 情况，需要考虑初始值和下标冲突问题，通过交换变量来解决。这提醒我们在解题时要考虑全面，注意特殊情况的处理。 

---
处理用时：43.87秒