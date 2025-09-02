# 题目信息

# Champions' League

## 题目描述

In the autumn of this year, two Russian teams came into the group stage of the most prestigious football club competition in the world — the UEFA Champions League. Now, these teams have already started to play in the group stage and are fighting for advancing to the playoffs. In this problem we are interested in the draw stage, the process of sorting teams into groups.

The process of the draw goes as follows (the rules that are described in this problem, are somehow simplified compared to the real life). Suppose $ n $ teams will take part in the group stage ( $ n $ is divisible by four). The teams should be divided into groups of four. Let's denote the number of groups as $ m $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65e4300bd0cdae46f7d260b1389d3b214f9ce521.png)). Each team has a rating — an integer characterizing the team's previous achievements. The teams are sorted by the rating's decreasing (no two teams have the same rating).

After that four "baskets" are formed, each of which will contain $ m $ teams: the first $ m $ teams with the highest rating go to the first basket, the following $ m $ teams go to the second one, and so on.

Then the following procedure repeats $ m-1 $ times. A team is randomly taken from each basket, first from the first basket, then from the second, then from the third, and at last, from the fourth. The taken teams form another group. After that, they are removed from their baskets.

The four teams remaining in the baskets after $ (m-1) $ such procedures are performed, form the last group.

In the real draw the random selection of teams from the basket is performed by people — as a rule, the well-known players of the past. As we have none, we will use a random number generator, which is constructed as follows. Its parameters are four positive integers $ x,a,b,c $ . Every time there is a call to the random number generator, it produces the following actions:

- calculates ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/2fe2894178b5b7478ae2269aae243e7c851b6173.png);
- replaces parameter $ x $ by value $ y $ (assigns ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/72e8070934423a6837039e7a1e2f312765ec26ab.png));
- returns $ x $ as another random number.

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) means taking the remainder after division: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/c19545677f47a50d181dd7b00e822282597427db.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/770f8dc8f9b95dc42d2401b09019f707ad7418fc.png).

A random number generator will be used in the draw as follows: each time we need to randomly choose a team from the basket, it will generate a random number $ k $ . The teams that yet remain in the basket are considered numbered with consecutive integers from $ 0 $ to $ s-1 $ , in the order of decreasing rating, where $ s $ is the current size of the basket. Then a team number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65912cf5ed5c94787700c166a6eeb79e0114a14b.png) is taken from the basket.

Given a list of teams and the parameters of the random number generator, determine the result of the draw.

## 说明/提示

In the given sample the random number generator will be executed four times:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/fe99c797dbb307d601e0f59e424f6250c45a7d38.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/baa288fe7b8d960b815b5367ff1126e08e6c706b.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/81b191782fc61308d51cf88ac0aba6c561fc0212.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/549ef2ab2cbb05e99d689f6ca803b6fab657873d.png).

## 样例 #1

### 输入

```
8
1 3 1 7
Barcelona 158
Milan 90
Spartak 46
Anderlecht 48
Celtic 32
Benfica 87
Zenit 79
Malaga 16
```

### 输出

```
Group A:
Barcelona
Benfica
Spartak
Celtic
Group B:
Milan
Zenit
Anderlecht
Malaga
```

# AI分析结果

### 题目中文重写
# 欧冠联赛

## 题目描述
在今年秋天，两支俄罗斯球队进入了世界上最负盛名的足球俱乐部赛事——欧洲冠军联赛的小组赛阶段。现在，这些球队已经开始了小组赛的征程，为晋级淘汰赛而战。在这个问题中，我们关注的是抽签阶段，即球队分组的过程。

抽签过程如下（本题描述的规则与现实生活中的规则相比有所简化）。假设 $n$ 支球队将参加小组赛（$n$ 能被 4 整除）。球队应被分成每组 4 支球队的小组。我们用 $m$ 表示小组的数量（$m = \frac{n}{4}$）。每支球队都有一个评级——一个表征球队过往成绩的整数。球队按照评级从高到低排序（没有两支球队的评级相同）。

之后，会形成四个“篮子”，每个篮子将包含 $m$ 支球队：评级最高的前 $m$ 支球队进入第一个篮子，接下来的 $m$ 支球队进入第二个篮子，依此类推。

然后，以下过程重复 $m - 1$ 次。依次从每个篮子中随机抽取一支球队，先从第一个篮子，然后是第二个，接着是第三个，最后是第四个。抽出的球队组成一个新的小组。之后，将这些球队从各自的篮子中移除。

在进行了 $(m - 1)$ 次这样的操作后，四个篮子中剩下的四支球队组成最后一个小组。

在实际的抽签中，从篮子中随机抽取球队的操作是由人来完成的——通常是过去著名的球员。由于我们没有这样的人员，我们将使用一个随机数生成器，其构造如下。它的参数是四个正整数 $x$、$a$、$b$、$c$。每次调用随机数生成器时，它会执行以下操作：
- 计算 $y = (x \times a + b) \bmod c$；
- 用 $y$ 的值替换参数 $x$（即 $x = y$）；
- 返回 $x$ 作为另一个随机数。

操作 $a \bmod b$ 表示取除法的余数：$a = q \times b + r$，其中 $0 \leq r < b$。

随机数生成器将在抽签中按如下方式使用：每次我们需要从篮子中随机选择一支球队时，它会生成一个随机数 $k$。篮子中尚未分组的球队按评级从高到低的顺序依次编号为从 0 到 $s - 1$，其中 $s$ 是当前篮子的大小。然后，从篮子中取出编号为 $k \bmod s$ 的球队。

给定球队列表和随机数生成器的参数，确定抽签的结果。

## 说明/提示
在给定的样例中，随机数生成器将被执行四次：
- $x_1=(x_0\times a + b)\bmod c$；
- $x_2=(x_1\times a + b)\bmod c$；
- $x_3=(x_2\times a + b)\bmod c$；
- $x_4=(x_3\times a + b)\bmod c$。

## 样例 #1

### 输入
```
8
1 3 1 7
Barcelona 158
Milan 90
Spartak 46
Anderlecht 48
Celtic 32
Benfica 87
Zenit 79
Malaga 16
```

### 输出
```
Group A:
Barcelona
Benfica
Spartak
Celtic
Group B:
Milan
Zenit
Anderlecht
Malaga
```

### 综合分析与结论
- **思路对比**：所有题解思路均为模拟，先对球队按积分排序，再分成四个“篮子”，通过随机数生成器从每个“篮子”选球队组成小组。
- **算法要点**：都用结构体存储球队信息，用排序函数按积分降序排列，利用随机数公式 $x=(x\times a + b)\bmod c$ 选球队。
- **解决难点**：主要难点在于处理已选球队，避免重复选择。不同题解采用不同方法，如标记数组、移动数组元素、使用 `vector` 的 `erase` 方法。

### 所选题解
- **Walter_Fang（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用结构体存储球队信息，用标记数组 `f` 记录已分组球队，嵌套循环实现分组。
    - **核心代码**：
```cpp
struct no {
    int x;
    string y;
} a[110];
bool cmp(no l,no r) {
    return l.x>r.x;
}
int main() {
    // ... 输入部分 ...
    sort(a+1,a+n+1,cmp);
    for(i=1; i<=n/4; i++) {
        cout<<"Group "<<char('A'+i-1)<<":"<<'\n';
        for(j=1; j<=4; j++) {
            x=(x*q1+q2)%q3;
            k=0;
            s=(j-1)*n/4+1;
            m=x%(n/4-i+1);
            while(1) {
                if(!f[s]) {
                    k++;
                    if(k==m+1)break;
                }
                s++;
            }
            f[s]=1;
            cout<<a[s].y<<'\n';
        }
    }
}
```
- **Empty_Dream（4星）**
    - **关键亮点**：使用 `vector` 优化数组挪动的时间复杂度，通过 `sort` 和 `reverse` 实现从大到小排序，用 `erase` 方法移除已选球队。
    - **核心代码**：
```c++
pair<int, string> v[105];
vector<pair<int, string>> w[5];
signed main(){
    // ... 输入部分 ...
    sort(v, v + n);
    reverse(v, v + n);
    for (int i = 0; i < n; i++) w[i / m].push_back(v[i]);
    for (int i = 0; i < m; i++){
        printf("Group %c:\n", i + 'A');
        for (int j = 0; j < 4; j++){
            x = (x * a + b) % c;
            int pos = x % (m - i);
            printf("%s\n", w[j][pos].second.c_str());
            w[j].erase(w[j].begin() + pos);
        }
    }
    return 0;
}
```
- **_xiaxii（4星）**
    - **关键亮点**：思路清晰，代码规范，使用结构体存储球队信息，用标记数组 `book` 记录已分组球队，嵌套循环实现分组。
    - **核心代码**：
```cpp
struct _grope{
    string name;
    int grade;
}a[100];
bool cmp(_grope e,_grope r)
{
    return e.grade>r.grade;
}
int main()
{
    // ... 输入部分 ...
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n/4;i++)
    {
        cout<<"Group "<<char('A'+i-1)<<":"<<endl;
        for(int j=1;j<=4;j++)
        {
            x=(x*q1+q2)%q3;
            int k=0,cnt=(j-1)*n/4+1;
            int m=x%(n/4-i+1);
            while(1)
            {
                if(!book[cnt]){
                    k++;
                    if(k==m+1)
                        break;
                }
                cnt++;
            }
            book[cnt]=1;
            cout<<a[cnt].name<<endl;
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- **结构体存储**：使用结构体存储球队的名字和积分，方便排序和管理。
- **排序**：按积分从高到低排序，便于后续分组。
- **标记数组**：用标记数组记录已分组的球队，避免重复选择。
- **`vector` 优化**：使用 `vector` 可优化数组挪动的时间复杂度，方便移除已选球队。

### 可拓展之处
同类型题或类似算法套路：模拟比赛的分组、抽奖等场景，都可采用类似的模拟思路，通过排序、随机数生成和标记等方法实现。

### 推荐题目
- [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：涉及排序和结构体的使用。
- [P1104 生日](https://www.luogu.com.cn/problem/P1104)：需要对数据进行排序和处理。
- [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)：包含排序和筛选的操作。

### 个人心得摘录与总结
- **封禁用户**：提到翻译有未翻译的地方，可能影响理解，且细节很难调，提醒注意真正分组的条件和文件输入输出。
- **Kyl_in_2024**：指出洛谷题面没提到 `freopen`，翻译不知所云，强调按题意模拟时注意 `freopen`。

总结：这些心得提醒我们在做题时要仔细阅读题目，注意题面细节，尤其是输入输出要求，同时在模拟过程中要注意处理好细节。 

---
处理用时：60.08秒