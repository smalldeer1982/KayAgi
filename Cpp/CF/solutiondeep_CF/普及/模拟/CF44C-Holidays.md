# 题目信息

# Holidays

## 题目描述

School holidays come in Berland. The holidays are going to continue for $ n $ days. The students of school № $ N $ are having the time of their lives and the IT teacher Marina Sergeyevna, who has spent all the summer busy checking the BSE (Berland State Examination) results, has finally taken a vacation break! Some people are in charge of the daily watering of flowers in shifts according to the schedule. However when Marina Sergeyevna was making the schedule, she was so tired from work and so lost in dreams of the oncoming vacation that she perhaps made several mistakes. In fact, it is possible that according to the schedule, on some days during the holidays the flowers will not be watered or will be watered multiple times. Help Marina Sergeyevna to find a mistake.

## 说明/提示

Keep in mind that in the second sample the mistake occurs not only on the second day, but also on the sixth day, when nobody waters the flowers. However, you have to print the second day, i.e. the day with the minimal number.

## 样例 #1

### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10
```

### 输出

```
2 2
```

## 样例 #3

### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10
```

### 输出

```
4 0
```

# AI分析结果

### 题目翻译
# 假期

## 题目描述
伯兰迎来了学校假期，假期将持续 $ n $ 天。N 号学校的学生们正尽情享受着时光，而整个夏天都在忙着检查 BSE（伯兰国家考试）成绩的信息技术老师玛丽娜·谢尔盖耶夫娜终于迎来了假期！

有些人会按照日程表轮流负责每天给花浇水。然而，当玛丽娜·谢尔盖耶夫娜制定日程表时，她因工作疲惫不堪，满脑子都是即将到来的假期，以至于可能犯了一些错误。实际上，根据日程表，假期中的某些日子里，花可能会无人浇水或者被多次浇水。请帮助玛丽娜·谢尔盖耶夫娜找出错误。

## 说明/提示
请记住，在第二个样例中，错误不仅出现在第二天，还出现在第六天，那天没有人给花浇水。然而，你必须输出第二天，即编号最小的那天。

## 样例 #1
### 输入
```
10 5
1 2
3 3
4 6
7 7
8 10
```
### 输出
```
OK
```

## 样例 #2
### 输入
```
10 5
1 2
2 3
4 5
7 8
9 10
```
### 输出
```
2 2
```

## 样例 #3
### 输入
```
10 5
1 2
3 3
5 7
7 7
7 10
```
### 输出
```
4 0
```

### 题解综合分析与结论
这些题解主要围绕判断假期中每天花是否被且仅被浇一次水展开，思路可归为模拟、差分、排序判断三类。
- **模拟思路**：用数组记录每天浇水次数，遍历每个人负责的区间，将对应天数的浇水次数加 1，最后遍历天数数组检查是否符合要求。实现简单直接，但时间复杂度较高，为 $O(nm)$。
- **差分思路**：在差分数组的区间起始位置加 1，结束位置的下一个位置减 1，通过前缀和恢复原数组，再检查是否符合要求。时间复杂度为 $O(n + m)$，效率较高。
- **排序判断思路**：将区间按开始时间排序，分析相邻区间的关系找出问题天数。时间复杂度为 $O(nlogn + n)$，若数据已排序可降至 $O(n)$，但逻辑较复杂。

### 各题解评分
|作者|思路|评分|
| ---- | ---- | ---- |
|songxiao|模拟|4星|
|ziiidan|一维差分|4星|
|曼恩薄荷|树状数组差分优化|3星|
|锦瑟，华年|差分|4星|
|CrTsIr400|模拟差分|3星|
|rfsfreffr|排序判断|3星|
|溪水瑶|模拟|3星|
|Cream_|模拟|3星|
|yzx72424|模拟|3星|
|wzm2007|模拟|3星|

### 所选题解
- **作者：songxiao（4星）**
    - **关键亮点**：思路清晰，使用纯模拟方法，代码简单易懂，适合初学者。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,a,b;
    cin>>n>>m;
    int x[n]={0};
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        for(int i=a-1;i<b;i++)
        {
            x[i]++;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(x[i]!=1)
        {
            cout<<i+1<<' '<<x[i];
            return 0;
        }
    }
    cout<<"OK";
    return 0;
}
```
- **作者：ziiidan（4星）**
    - **关键亮点**：使用一维差分，代码简洁，时间复杂度较低。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 105;
int n, m;
int fr, to;
int c[maxn];
inline int read(void)
{
    int s = 0, w = 1;
    char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') w = -1;
    for(; ch <= '9' && ch >= '0'; ch = getchar()) s = s * 10 + ch - '0';
    return s * w;
}
int main()
{
    n = read(); m = read();
    for(register int i = 1; i <= m; i++) 
    {
        fr = read(); to = read();
        c[fr]++;
        c[to + 1]--;
    }
    for(register int i = 1; i <= n; i++) 
    {
        c[i] = c[i - 1] + c[i];
        if(c[i] == 0 || c[i] > 1)
        {
            cout << i << ' ' << c[i] << '\n';
            return 0;
        }
    }
    cout << "OK" << '\n';
    return 0;
}
```
- **作者：锦瑟，华年（4星）**
    - **关键亮点**：详细解释了差分的原理和实现过程，代码清晰。
    - **核心代码**：
```cpp
#include<stdio.h>
using namespace std;
int a[105];
int main(){
    int n,m,i;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        a[l]+=1;a[r+1]-=1;
    }
    for(i=1;i<=n;i++){
        a[i]+=a[i-1];
        if(a[i]!=1){
            printf("%d %d",i,a[i]);
            return 0;
        }
    }
    printf("OK");
    return 0; 
}
```

### 最优关键思路或技巧
差分算法是本题的最优思路，通过在差分数组的区间端点做标记，再用前缀和恢复原数组，可将时间复杂度从模拟的 $O(nm)$ 优化到 $O(n + m)$。

### 拓展思路
同类型题可拓展到二维区间修改、单点查询问题，可使用二维差分解决。类似算法套路还有线段树、树状数组等，可用于处理更复杂的区间修改和查询问题。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)

### 个人心得摘录与总结
- **rfsfreffr**：经过多次尝试（WA 了很多次）才总结出不同区间关系下判断问题天数的方法，提醒我们在解题时要多尝试、多总结。
- **yzx72424**：看到题目先有自己的思路，即便看到别人用不同方法，也可根据数据范围坚持自己的思路。 

---
处理用时：43.01秒