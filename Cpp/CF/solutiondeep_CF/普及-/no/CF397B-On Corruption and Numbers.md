# 题目信息

# On Corruption and Numbers

## 题目描述

Alexey, a merry Berland entrant, got sick of the gray reality and he zealously wants to go to university. There are a lot of universities nowadays, so Alexey is getting lost in the diversity — he has not yet decided what profession he wants to get. At school, he had bad grades in all subjects, and it's only thanks to wealthy parents that he was able to obtain the graduation certificate.

The situation is complicated by the fact that each high education institution has the determined amount of voluntary donations, paid by the new students for admission — $ n_{i} $ berubleys. He cannot pay more than $ n_{i} $ , because then the difference between the paid amount and $ n_{i} $ can be regarded as a bribe!

Each rector is wearing the distinctive uniform of his university. Therefore, the uniform's pockets cannot contain coins of denomination more than $ r_{i} $ . The rector also does not carry coins of denomination less than $ l_{i} $ in his pocket — because if everyone pays him with so small coins, they gather a lot of weight and the pocket tears. Therefore, a donation can be paid only by coins of denomination $ x $ berubleys, where $ l_{i}<=x<=r_{i} $ (Berland uses coins of any positive integer denomination). Alexey can use the coins of different denominations and he can use the coins of the same denomination any number of times. When Alexey was first confronted with such orders, he was puzzled because it turned out that not all universities can accept him! Alexey is very afraid of going into the army (even though he had long wanted to get the green uniform, but his dad says that the army bullies will beat his son and he cannot pay to ensure the boy's safety). So, Alexey wants to know for sure which universities he can enter so that he could quickly choose his alma mater.

Thanks to the parents, Alexey is not limited in money and we can assume that he has an unlimited number of coins of each type.

In other words, you are given $ t $ requests, each of them contains numbers $ n_{i},l_{i},r_{i} $ . For each query you need to answer, whether it is possible to gather the sum of exactly $ n_{i} $ berubleys using only coins with an integer denomination from $ l_{i} $ to $ r_{i} $ berubleys. You can use coins of different denominations. Coins of each denomination can be used any number of times.

## 说明/提示

You can pay the donation to the first university with two coins: one of denomination 2 and one of denomination 3 berubleys. The donation to the second university cannot be paid.

## 样例 #1

### 输入

```
2
5 2 3
6 4 5
```

### 输出

```
Yes
No
```

# AI分析结果

### 题目内容
# 关于腐败和数字
## 题目描述
阿列克谢，一个快乐的伯兰登特考生，厌倦了灰色的现实，他热切地希望上大学。如今大学众多，阿列克谢在众多选择中迷失了方向——他还没决定自己想从事什么职业。在学校时，他所有科目的成绩都很差，多亏了富裕的父母，他才得以获得毕业证书。

情况变得复杂起来，因为每所高等教育机构都规定了新生入学时需缴纳的自愿捐款金额——$n_{i}$ 伯卢布。他不能支付超过 $n_{i}$ 的金额，因为支付金额与 $n_{i}$ 的差额可能会被视为贿赂！

每所大学的校长都穿着本校独特的制服。因此，制服口袋不能装面额超过 $r_{i}$ 的硬币。校长口袋里也不会装面额小于 $l_{i}$ 的硬币——因为如果每个人都用这么小面额的硬币付钱给他，硬币会很重，口袋会被撑破。所以，捐款只能用面额为 $x$ 伯卢布的硬币支付，其中 $l_{i}\leq x\leq r_{i}$（伯兰使用任意正整数面额的硬币）。阿列克谢可以使用不同面额的硬币，并且可以任意次数地使用相同面额的硬币。当阿列克谢第一次面对这样的规定时，他很困惑，因为结果发现并非所有大学都能录取他！阿列克谢非常害怕参军（尽管他一直渴望穿上绿色军装，但他爸爸说军队里的恶霸会揍他儿子，而且他无法花钱确保儿子的安全）。所以，阿列克谢想确切知道他能进入哪些大学，以便他能尽快选择自己的母校。

多亏了父母，阿列克谢在钱方面不受限制，我们可以假设他每种类型的硬币都有无限个。

换句话说，给定 $t$ 个请求，每个请求包含数字 $n_{i},l_{i},r_{i}$。对于每个查询，你需要回答是否可以仅使用面额在 $l_{i}$ 到 $r_{i}$ 伯卢布之间的整数面额硬币凑出恰好 $n_{i}$ 伯卢布。你可以使用不同面额的硬币。每种面额的硬币可以使用任意次数。
## 说明/提示
你可以用两枚硬币向第一所大学支付捐款：一枚面额为2伯卢布，一枚面额为3伯卢布。向第二所大学的捐款无法支付。
## 样例 #1
### 输入
```
2
5 2 3
6 4 5
```
### 输出
```
Yes
No
```
### 算法分类
数学
### 综合分析与结论
所有题解思路基本一致。首先都考虑到若 $n < l$，则无法凑出目标金额，直接输出 `No`。然后重点分析了凑出金额 $n$ 所需硬币数量的最值情况，得出最少需要 $\lceil \frac{n}{r} \rceil$ 个硬币，最多需要 $\lfloor \frac{n}{l} \rfloor$ 个硬币，进而确定能凑出的金额范围是 $\lceil \frac{n}{r} \rceil\times{l}$ 到 $\lfloor \frac{n}{l} \rfloor\times{r}$，只要判断 $n$ 是否在这个区间内即可得出能否凑出的结论。同时都提到要开 `long long` 避免数据溢出。不同题解在表述和代码风格上略有差异，但核心思路和算法要点相同。
### 所选的题解
- **作者：very_easy（5星）**
  - **关键亮点**：思路清晰，简洁明了地阐述题意、思路和代码实现，对上下限的判断解释清晰，代码规范易读。
  - **核心代码**：
```c++
#include<bits/stdc++.h>
using namespace std;
long long t,n,l,r;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>l>>r;
        if(n<l){
            cout<<"No"<<endl;
            continue;
        }
        if(n>=((n-1)/r+1)*l&&n<=(n/l)*r){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}
```
核心实现思想：先读入数据，对每组数据先判断 $n$ 是否小于 $l$，若小于则输出 `No` 并继续下一组；否则判断 $n$ 是否在可凑出的金额区间内，在则输出 `Yes`，不在则输出 `No`。
- **作者：Paris_Commune（4星）**
  - **关键亮点**：以分类讨论的方式阐述思路，逻辑清晰，代码简洁，同样注意到数据类型需为 `long long`。
  - **核心代码**：
```c++
#include <bits/stdc++.h>
#define int long long 
using namespace std;
signed main(){
    int t;
    cin>>t;
    while(t--){
        int n,l,r;
        cin>>n>>l>>r;
        if(n<l){
            cout<<"No\n";
            continue;
        }
        if(n>=((n-1)/r+1)*l&&n<=(n/l)*r){
            cout<<"Yes\n";
        }
        else{
            cout<<"No\n";
        }
    }
    return 0;
}
```
核心实现思想：与 very_easy 的代码类似，读入数据后，先判断 $n$ 和 $l$ 的大小关系，再判断 $n$ 是否在可凑出区间内，根据结果输出相应内容。
- **作者：BqtMtsZDnlpsT（4星）**
  - **关键亮点**：详细简述题意和解题思路，对所需硬币数量的最值及可凑出金额区间的分析到位，代码实现规范。
  - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
int t,n,l,r;
signed main(){
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld%lld",&n,&l,&r);
        if(n<l){puts("No");continue;}
        if(n>=((n-1)/r+1)*l&&n<=(n/l)*r)puts("Yes");
        else puts("No");
    }
    return 0;
}
```
核心实现思想：通过 `scanf` 读入数据，同样先判断 $n$ 和 $l$ 的大小，再判断 $n$ 是否在可凑出区间，按判断结果输出 `Yes` 或 `No`。
### 最优关键思路或技巧
通过分析凑出目标金额所需硬币数量的最值来确定可凑出金额的区间，利用这个数学关系来判断能否凑出目标金额，同时注意数据范围，合理使用 `long long` 类型避免数据溢出。
### 可拓展之处
同类型题通常围绕硬币凑数、数字组合等场景，类似算法套路是通过分析数据的边界条件（如本题硬币数量的最值）来确定结果范围，进而解决问题。
### 洛谷题目推荐
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过对数字组合规则的分析，利用递推或记忆化搜索解决问题，与本题分析数字关系的思路类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：同样是关于物品组合凑出目标值的问题，可采用动态规划解决，和本题都涉及到能否凑出特定值的判断。
- [P1216 [USACO1.5]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：需要通过分析数字间的关系找到最优路径和，与本题分析数字关系以得出结论的方式有相似之处。
### 个人心得摘录与总结
无个人心得相关内容。 

---
处理用时：68.85秒