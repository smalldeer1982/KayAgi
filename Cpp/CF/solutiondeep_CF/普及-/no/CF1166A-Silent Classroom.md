# 题目信息

# Silent Classroom

## 题目描述

There are $ n $ students in the first grade of Nlogonia high school. The principal wishes to split the students into two classrooms (each student must be in exactly one of the classrooms). Two distinct students whose name starts with the same letter will be chatty if they are put in the same classroom (because they must have a lot in common). Let $ x $ be the number of such pairs of students in a split. Pairs $ (a, b) $ and $ (b, a) $ are the same and counted only once.

For example, if there are $ 6 $ students: "olivia", "jacob", "tanya", "jack", "oliver" and "jessica", then:

- splitting into two classrooms ("jack", "jacob", "jessica", "tanya") and ("olivia", "oliver") will give $ x=4 $ ( $ 3 $ chatting pairs in the first classroom, $ 1 $ chatting pair in the second classroom),
- splitting into two classrooms ("jack", "tanya", "olivia") and ("jessica", "oliver", "jacob") will give $ x=1 $ ( $ 0 $ chatting pairs in the first classroom, $ 1 $ chatting pair in the second classroom).

You are given the list of the $ n $ names. What is the minimum $ x $ we can obtain by splitting the students into classrooms?

Note that it is valid to place all of the students in one of the classrooms, leaving the other one empty.

## 说明/提示

In the first sample the minimum number of pairs is $ 1 $ . This can be achieved, for example, by putting everyone except jose in one classroom, and jose in the other, so jorge and jerry form the only chatty pair.

In the second sample the minimum number of pairs is $ 2 $ . This can be achieved, for example, by putting kambei, gorobei, shichiroji and kyuzo in one room and putting heihachi, katsushiro and kikuchiyo in the other room. In this case the two pairs are kambei and kyuzo, and katsushiro and kikuchiyo.

In the third sample the minimum number of pairs is $ 4 $ . This can be achieved by placing three of the students named mike in one classroom and the other two students in another classroom. Thus there will be three chatty pairs in one classroom and one chatty pair in the other classroom.

## 样例 #1

### 输入

```
4
jorge
jose
oscar
jerry
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
kambei
gorobei
shichiroji
kyuzo
heihachi
katsushiro
kikuchiyo
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
mike
mike
mike
mike
mike
```

### 输出

```
4
```

# AI分析结果

### 题目重写
# 安静的教室

## 题目描述
Nlogonia高中一年级有$n$名学生。校长希望将学生分成两个教室（每个学生必须恰好被分到其中一个教室）。如果两个不同学生的名字首字母相同，且他们被分到同一个教室，那么他们就会聊天（因为他们肯定有很多共同话题）。设$x$为在一种分组方式下这样的学生对数。$(a, b)$和$(b, a)$视为同一对，只计数一次。

例如，若有$6$名学生：“olivia”、“jacob”、“tanya”、“jack”、“oliver”和“jessica”，那么：
 - 分成两个教室（“jack”、“jacob”、“jessica”、“tanya”）和（“olivia”、“oliver”），$x = 4$（第一个教室有$3$对聊天的学生，第二个教室有$1$对聊天的学生）。
 - 分成两个教室（“jack”、“tanya”、“olivia”）和（“jessica”、“oliver”、“jacob”），$x = 1$（第一个教室有$0$对聊天的学生，第二个教室有$1$对聊天的学生）。

给定$n$个学生的名字列表。通过将学生分到教室，我们能得到的最小$x$是多少？

注意，将所有学生都放在一个教室，另一个教室空着是有效的分组方式。

## 说明/提示
在第一个样例中，最小对数是$1$。例如，除了jose之外的所有人放在一个教室，jose放在另一个教室，这样jorge和jerry就形成了唯一一对聊天的学生。

在第二个样例中，最小对数是$2$。例如，将kambei、gorobei、shichiroji和kyuzo放在一个教室，将heihachi、katsushiro和kikuchiyo放在另一个教室。在这种情况下，两对聊天的学生是kambei和kyuzo，以及katsushiro和kikuchiyo。

在第三个样例中，最小对数是$4$。可以将三个叫mike的学生放在一个教室，另外两个学生放在另一个教室。这样一个教室会有三对聊天的学生，另一个教室有一对聊天的学生。

## 样例 #1
### 输入
```
4
jorge
jose
oscar
jerry
```
### 输出
```
1
```
## 样例 #2
### 输入
```
7
kambei
gorobei
shichiroji
kyuzo
heihachi
katsushiro
kikuchiyo
```
### 输出
```
2
```
## 样例 #3
### 输入
```
5
mike
mike
mike
mike
mike
```
### 输出
```
4
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解的核心思路均为贪心算法，即对于名字首字母相同的学生，将他们尽可能平均地分到两个教室，以使得聊天的学生对数最少。然后通过组合数公式$C^2_n = \frac{n(n - 1)}{2}$来计算每个教室中聊天学生的对数，最后将所有首字母分组对应的对数相加得到最终结果。

各题解的不同点主要在于实现细节，如数据存储方式（使用数组计数或map）、输入处理方式、代码的简洁性和可读性等。

### 所选的题解
- **作者：JustinXiaoJunyang（4星）**
  - **关键亮点**：思路阐述清晰，先介绍组合数概念，再通过具体例子说明贪心策略是将学生尽量平均分成两个班，代码简洁明了，使用map存储首字母出现次数。
  - **重点代码**：
```cpp
map <char, int> m;
int f(int x)
{
    return x * (x - 1) / 2;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        m[s[0]]++;
    }
    long long ans = 0;
    for (char i = 'a'; i <= 'z'; i++)
    {
        ans += f(m[i] / 2) + f(m[i] - m[i] / 2);
    }
    cout << ans << endl;
}
```
  - **核心实现思想**：通过map统计每个首字母出现的次数，定义函数$f$计算组合数，遍历所有可能的首字母，计算并累加每个首字母分组在两个教室中的聊天对数。

- **作者：Eason_AC（4星）**
  - **关键亮点**：解题思路描述简洁准确，代码使用了自定义的宏（假设`read`和`write`、`F`是自定义宏且功能正确），整体逻辑紧凑。
  - **重点代码**：
```cpp
namespace Solution {
    int n, ans, vis[26]; string s;

    iv Main() {
        read(n);
        F(int, i, 1, n) cin >> s, vis[s[0] - 'a']++;
        F(int, i, 0, 25) {
            int x = vis[i] / 2, y = vis[i] / 2 + (vis[i] & 1);
            ans += (x * (x - 1) / 2 + y * (y - 1) / 2);
        }
        write(ans);
    }
}
```
  - **核心实现思想**：使用数组`vis`统计每个首字母出现的次数，遍历所有首字母，根据贪心策略将学生尽量平均分配到两个教室，计算并累加聊天对数。

- **作者：Huaji_King（4星）**
  - **关键亮点**：解题思路明确，先说明将首字母转数字进行数组计数，再阐述平均分的贪心策略，代码实现简单易懂。
  - **重点代码**：
```cpp
int a[30],n,sum,cl1,cl2;
string s;
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        a[s[0]-'a'+1]++; 
    }
    for(int i=1;i<=26;i++)
    {
        cl1=(a[i]/2)*(a[i]/2-1)/2;
        cl2=(a[i]-a[i]/2)*(a[i]-a[i]/2 -1)/2;
        sum+=max(0,cl1+cl2);
    }
    cout<<sum;
    return 0;
}
```
  - **核心实现思想**：利用数组`a`统计每个首字母出现的次数，遍历所有首字母，分别计算两个教室的聊天对数并累加，注意处理可能出现的负数情况。

### 最优关键思路或技巧
1. **贪心策略**：将名字首字母相同的学生尽量平均地分到两个教室，这是解决本题的核心思路，能保证得到最小的聊天对数。
2. **数组或map统计**：利用数组或map来统计每个首字母出现的次数，方便后续计算。
3. **组合数计算**：使用组合数公式$C^2_n = \frac{n(n - 1)}{2}$计算每个教室中聊天学生的对数。

### 拓展与举一反三
同类型题通常围绕分组优化问题展开，核心是通过合理分组使某个指标达到最优。类似算法套路是先确定一个贪心策略，然后统计相关元素的数量，再根据策略进行计算。

### 洛谷推荐题目
1. **P1080 [NOIP2012 提高组] 国王游戏**：通过合理排序和贪心策略解决分配问题。
2. **P1223 排队接水**：典型的贪心算法题目，根据接水时间贪心排序以优化总等待时间。
3. **P1199 [NOIP2010 普及组] 三国游戏**：需要运用贪心思想，结合一定的策略选择武将，以获取最优结果。 

---
处理用时：69.29秒