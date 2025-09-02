# 题目信息

# Sereja and Bottles

## 题目描述

Sereja and his friends went to a picnic. The guys had $ n $ soda bottles just for it. Sereja forgot the bottle opener as usual, so the guys had to come up with another way to open bottles.

Sereja knows that the $ i $ -th bottle is from brand $ a_{i} $ , besides, you can use it to open other bottles of brand $ b_{i} $ . You can use one bottle to open multiple other bottles. Sereja can open bottle with opened bottle or closed bottle.

Knowing this, Sereja wants to find out the number of bottles they've got that they won't be able to open in any way. Help him and find this number.

## 样例 #1

### 输入

```
4
1 1
2 2
3 3
4 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
4 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Sereja和瓶子

## 题目描述
Sereja和他的朋友们去野餐。他们为此准备了 $n$ 个汽水瓶。像往常一样，Sereja忘记带开瓶器了，所以大家不得不另想办法打开瓶子。

Sereja知道第 $i$ 个瓶子来自品牌 $a_{i}$ ，此外，可以用它来打开品牌为 $b_{i}$ 的其他瓶子。可以用一个瓶子打开多个其他瓶子。Sereja既可以用已打开的瓶子，也可以用未打开的瓶子来开瓶。

知道这些信息后，Sereja想找出无论如何都无法打开的瓶子数量。请帮助他找出这个数量。

## 样例 #1
### 输入
```
4
1 1
2 2
3 3
4 4
```
### 输出
```
4
```

## 样例 #2
### 输入
```
4
1 2
2 3
3 4
4 1
```
### 输出
```
0
```

### 算法分类
枚举

### 题解综合分析与结论
这些题解的核心思路都是通过枚举来解决问题，即通过两层循环遍历所有瓶子组合，判断一个瓶子能否打开另一个瓶子。主要差异在于实现细节和对无法打开瓶子的统计方式。

- **思路方面**：多数题解直接暴力枚举所有瓶子对，判断条件为一个瓶子的“可打开品牌”与另一个瓶子的“所属品牌”相同且不是同一个瓶子。部分题解还使用了标记数组来记录已打开的瓶子。
- **算法要点**：利用双重循环遍历所有瓶子组合，根据给定的瓶子开启关系判断能否打开，统计可打开或不可打开的瓶子数量。
- **解决难点**：主要难点在于理解题意，明确自己不能打开自己这一条件，并正确实现对可打开瓶子的判断和统计。

### 所选的题解
#### 作者：封禁用户 (星级：4星)
- **关键亮点**：思路清晰，通过结构体存储瓶子信息，用标记数组记录瓶子是否被打开，代码结构完整，逻辑明确。
- **个人心得**：作者提到自己在实现过程中被“自己不能打开自己”和“标记已打开瓶子”这两个点坑了一会，强调了注意这两个条件的重要性。
```cpp
struct bottle   //结构体存a类瓶子和b类瓶子
{
    int a, b;
} p[101];
int w[101];   //开数组标记第i个瓶子是否被开过
int main()
{
    ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
    int n;   //定义瓶子总数
    int k = 0;   //定义已开的瓶子数
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i].a >> p[i].b;
    }
    memset(w, 0, sizeof(w));   //标记数组初始化
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j!= i && p[i].b == p[j].a && w[j] == 0)
            {
                k++;   //记录已被开瓶子数
                w[j] = 1;   //标记该瓶子已被开
            }
        }
    }
    cout << n - k;   //瓶子总数减去可被打开的瓶子数即可得到答案
    return 0;   //结束整个程序
}
```
核心代码实现思想：外层循环遍历每个瓶子作为“开瓶器”，内层循环遍历所有瓶子，判断当前“开瓶器”能否打开该瓶子且该瓶子未被打开过，若满足条件则标记该瓶子已打开并增加已开瓶子计数，最后用总数减去已开瓶子数得到无法打开的瓶子数。

#### 作者：LuffyLuo (星级：4星)
- **关键亮点**：代码简洁，直接通过枚举判断两个瓶子是否匹配（一个瓶子的盖子能开另一个瓶子），并及时更新无法打开瓶子的数量。
```cpp
#include<bits/stdc++.h>
const int MAX=110000;
using namespace std;
int a[MAX],b[MAX];//一个是盖子，一个是瓶子 
int main(){//主函数 
    int n,ans,i,j;//ans为无法打开的瓶子数 
    scanf("%d",&n);
    ans=n;
    for(i=1;i<=n;i++)
        scanf("%d %d",&a[i],&b[i]);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(a[i]==b[j]&&i!=j){
                ans--;
                break; 
            }
    printf("%d",ans);
    return 0;
}
```
核心代码实现思想：初始化认为所有瓶子都无法打开，通过双重循环枚举所有瓶子对，若找到匹配的盖子和瓶子（且不是同一个瓶子），则减少无法打开瓶子的计数，最后输出无法打开瓶子的数量。

#### 作者：hswfwkj_ (星级：4星)
- **关键亮点**：同样采用双重循环枚举判断，思路清晰，代码简洁易懂，通过标记数组记录瓶子是否可打开，最后统计不可打开的瓶子数量。
```cpp
#include<iostream>
using namespace std;
int i,j,n,a[201],b[201],c[201],ans;
int main(){
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>a[i]>>b[i];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++){
            if(j==i)continue;
            if(a[j]==b[i])
                c[j]=1;
        }
    for(i=1;i<=n;i++)
        if(!c[i])
            ans++;
    cout<<ans;
    return 0;
}
```
核心代码实现思想：外层循环遍历每个瓶子作为目标瓶子，内层循环遍历所有瓶子作为“开瓶器”，若找到能打开目标瓶子的“开瓶器”（且不是同一个瓶子），则标记该目标瓶子可打开，最后遍历标记数组统计未被标记（即无法打开）的瓶子数量。

### 最优关键思路或技巧
- **枚举判断**：利用双重循环枚举所有瓶子对，根据给定的开启关系判断能否打开，这是解决本题的基本思路。
- **标记数组**：部分题解使用标记数组记录瓶子是否已被打开或是否可被打开，有助于避免重复判断和准确统计无法打开的瓶子数量。

### 可拓展之处
此类题目属于简单模拟枚举类型，类似套路是根据给定的条件关系，通过枚举所有可能的组合来解决问题。同类型题可考察不同的条件关系和数据规模，例如改变物品之间的作用关系，或者增加数据量来考察对算法的优化能力。

### 推荐洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举不同数字组合来满足特定条件，与本题枚举思路类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：同样是通过枚举不同菜品组合来满足预算条件，锻炼枚举思维。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：在字符串中枚举匹配特定单词，涉及枚举和字符串处理，与本题枚举判断的思路有相似之处。 

---
处理用时：72.50秒