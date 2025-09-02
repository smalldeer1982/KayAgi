# 题目信息

# Room Leader

## 题目描述

比赛开始时，参赛者被分进几个不同的房间。每个房间恰好包含 $n$ 位参赛者。在比赛中，参与者被要求解决五个问题， $A$ 、 $B$ 、 $C$ 、 $D$ 和 $E$ 。

对于每个问题，参赛者会根据解决给定问题的时长以及是否彻底解决获得一些积分。此外，参赛者可以对其他参赛者进行攻击。每成功攻击一次，即可赢得 $100$ 分；攻击不成功一次，则会损失 $50$ 分。每个参赛者的得分由他从所有问题及攻击中获得的得分总和表示。

请确定给定的一个房间内得分最高的参与者。

## 说明/提示

$0 \leqslant plus_i,minus_i \leqslant 50$ ；

 $150 \leqslant a_i \leqslant 500$ 或 $a_i=0$ （若问题 $A$ 没有解决）；

 $300 \leqslant b_i \leqslant 1000$ 或 $b_i=0$ （若问题 $B$ 没有解决）；

 $450 \leqslant c_i \leqslant 1500$ 或 $c_i=0$ （若问题 $C$ 没有解决）；

 $600 \leqslant d_i \leqslant 2000$ 或 $d_i=0$ （若问题 $D$ 没有解决）；

 $750 \leqslant e_i \leqslant 2500$ 或 $e_i=0$ （若问题 $E$ 没有解决）；

所有数字都是整数。所有参与者都有不同的名称。可以确保房间中不存在多个参与者分数均为最高。

## 样例 #1

### 输入

```
5
Petr 3 1 490 920 1000 1200 0
tourist 2 0 490 950 1100 1400 0
Egor 7 0 480 900 950 0 1000
c00lH4x0R 0 10 150 0 0 0 0
some_participant 2 1 450 720 900 0 0
```

### 输出

```
tourist```

# AI分析结果

### 算法分类
模拟

### 综合分析与结论
这三道题解均围绕模拟的思路来解决问题，核心都是计算每个参赛者的得分，然后找出得分最高者。
- **思路对比**：
    - Eason_AC 的题解使用结构体存储参赛者信息，通过重载小于运算符自定义排序规则，对所有参赛者按分数从高到低排序，最后输出第一名的名字。
    - Sham_Sleep 的题解同样使用结构体，定义了比较函数 `cmp` 进行自定义排序，实现与 Eason_AC 类似。
    - Peter0701 的题解没有进行排序，而是在计算每个参赛者得分时，直接记录当前最大得分及其对应的参赛者位置，最后输出该参赛者的名字。
- **算法要点**：
    - 都需要准确计算每个参赛者的得分，公式为 `100 * 成功攻击次数 - 50 * 失败攻击次数 + 五道题得分之和`。
    - 可以选择排序或直接遍历找最大值的方法来确定第一名。
- **解决难点**：
    - 准确处理输入数据，包括参赛者的名字、攻击次数和题目得分。
    - 正确计算每个参赛者的得分，注意攻击成功和失败的分数计算。

### 题解评分
- **Eason_AC**：3星。思路清晰，代码结构完整，但使用了较多的头文件，可能会增加编译时间。
- **Sham_Sleep**：3星。思路简单直接，代码实现较为基础，但结构体中使用字符数组存储名字，处理字符串可能不够方便。
- **Peter0701**：3星。思路简洁，避免了排序操作，减少了时间复杂度，但使用了快速读入模板，增加了代码的复杂度。

### 通用建议与扩展思路
- 对于此类模拟题，关键是准确理解题目要求，将题目中的规则转化为代码逻辑。
- 可以根据数据规模选择合适的方法，如数据量较小时，直接遍历找最大值即可；数据量较大时，排序可能更方便。
- 同类型题或类似算法套路：其他涉及多属性数据处理和比较的模拟题，如比赛排名、成绩统计等，都可以采用类似的思路，先计算每个对象的关键属性值，再进行排序或比较。

### 推荐洛谷题目
1. P1046 陶陶摘苹果：https://www.luogu.com.cn/problem/P1046
2. P1001 A+B Problem：https://www.luogu.com.cn/problem/P1001
3. P1425 小鱼的游泳时间：https://www.luogu.com.cn/problem/P1425

### 重点代码
#### Eason_AC
```cpp
struct user {
    string name;
    int win, lose, ai, bi, ci, di, ei;
    long long score;
    bool operator < (const user& kkk) const {return score > kkk.score;}
}a[57];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i].name;
        scanf("%d%d%d%d%d%d%d", &a[i].win, &a[i].lose, &a[i].ai, &a[i].bi, &a[i].ci, &a[i].di, &a[i].ei);
        a[i].score = a[i].win * 100 - a[i].lose * 50 + a[i].ai + a[i].bi + a[i].ci + a[i].di + a[i].ei;
    }
    sort(a + 1, a + n + 1);
    cout << a[1].name;
    return 0;
}
```
核心思想：使用结构体存储参赛者信息，重载小于运算符自定义排序规则，排序后输出第一名的名字。

#### Sham_Sleep
```cpp
struct people{
    char name[105];
    int tr;
    int fa;
    int s;
};

int cmp(people a , people b)
{
    return a.s > b.s; 
}

int n;
people p[55];

int main()
{
    scanf("%d" , &n);
    for(int  i = 1; i <= n; ++i){
        scanf("%s" , p[i].name);
        scanf("%d %d" , &p[i].tr , &p[i].fa);
        p[i].s = p[i].tr * 100 - p[i].fa *50;
        int t;
        for(int j = 1; j <= 5; ++j){
            scanf("%d" , &t);
            p[i].s += t;
        }
    }
    sort (p + 1 , p + 1 + n , cmp);
    printf("%s" , p[1].name);
}
```
核心思想：使用结构体存储参赛者信息，定义比较函数 `cmp` 进行自定义排序，排序后输出第一名的名字。

#### Peter0701
```cpp
const int inf=1e9+7;
int n,val[55],maxn=-inf,pos;
char name[55][25];

int main()
{
    n=read();
    for(register int i=1;i<=n;i++)
    {
        cin>>name[i];
        val[i]=read()*100-read()*50+read()+read()+read()+read()+read();
    }
    for(register int i=1;i<=n;i++)
    {
        if(val[i]>maxn)
        {
            maxn=val[i];
            pos=i;
        }
    }
    printf("%s",name[pos]);
    return 0;
}
```
核心思想：使用数组存储参赛者信息，计算每个参赛者的得分，同时记录当前最大得分及其对应的参赛者位置，最后输出该参赛者的名字。

---
处理用时：35.80秒