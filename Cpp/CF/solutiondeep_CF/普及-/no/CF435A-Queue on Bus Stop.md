# 题目信息

# Queue on Bus Stop

## 题目描述

It's that time of the year when the Russians flood their countryside summer cottages (dachas) and the bus stop has a lot of people. People rarely go to the dacha on their own, it's usually a group, so the people stand in queue by groups.

The bus stop queue has $ n $ groups of people. The $ i $ -th group from the beginning has $ a_{i} $ people. Every $ 30 $ minutes an empty bus arrives at the bus stop, it can carry at most $ m $ people. Naturally, the people from the first group enter the bus first. Then go the people from the second group and so on. Note that the order of groups in the queue never changes. Moreover, if some group cannot fit all of its members into the current bus, it waits for the next bus together with other groups standing after it in the queue.

Your task is to determine how many buses is needed to transport all $ n $ groups to the dacha countryside.

## 样例 #1

### 输入

```
4 3
2 3 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 4
1 2 1
```

### 输出

```
1
```

# AI分析结果

### 题目内容中文重写
# 公交站的排队问题

## 题目描述
每年的这个时候，俄罗斯人都会涌向他们乡村的避暑别墅（达恰），公交站会有很多人。人们很少独自去达恰，通常是成群结队的，所以人们按组排队。

公交站的队伍中有 $n$ 组人。从队首开始的第 $i$ 组有 $a_{i}$ 个人。每 30 分钟会有一辆空公交车到达公交站，它最多能搭载 $m$ 个人。自然地，排在第一组的人先上车。然后是第二组的人，依此类推。请注意，队伍中组的顺序永远不会改变。此外，如果某一组的所有成员无法全部登上当前的公交车，那么该组会和排在它后面的其他组一起等待下一辆公交车。

你的任务是确定将所有 $n$ 组人运送到乡村达恰需要多少辆公交车。

## 样例 #1
### 输入
```
4 3
2 3 2 1
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3 4
1 2 1
```
### 输出
```
1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟公交车载人的过程。按照队伍中组的顺序依次判断每组人能否登上当前的公交车，如果能则上车，否则等待下一辆公交车。在实现过程中，需要注意处理最后一辆车是否还有剩余人数的情况。

各题解的主要区别在于细节处理和代码实现方式，例如初始化车辆数、判断条件和特判的方式略有不同，但整体思路一致。

### 所选题解
- 作者：伟大的王夫子 (赞：3)，4星
  - 关键亮点：思路清晰，代码简洁易懂，对特判情况有明确提醒。
  - 个人心得：提醒最后要特判车里是否还有人，否则会WA。
- 作者：YosemiteHe (赞：1)，4星
  - 关键亮点：直接模拟，思路简洁，对答案的初始化和处理方式合理。
  - 个人心得：无。
- 作者：damage (赞：0)，4星
  - 关键亮点：注释详细，对每一步操作的解释清晰，便于理解。
  - 个人心得：无。

### 重点代码
#### 作者：伟大的王夫子
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[101], ans;
int main() {
    cin >> n >> m;
    for (register int i = 1; i <= n; ++i) cin >> a[i];//读入数据
    int sum = 0;
    for (register int i = 1; i <= n; ++i) {
        if (sum + a[i] <= m) sum += a[i];//判断车还能否装得下
        else {
            sum = a[i];
            ++ans;
        }
    } 
    if (sum != 0) ++ans;//特判，否则你就愉快的WA了
    cout << ans;
}
```
核心实现思想：依次遍历每组人，判断当前车能否装下该组人，若能则加上该组人数，否则开一辆新车并将该车人数置为该组人数，最后特判最后一辆车是否还有人。

#### 作者：YosemiteHe
```cpp
#include <bits/stdc++.h>
int a, n, m, s, ans = 1;
int main(void) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a);
        if (m < s + a) {
            ans++;
            s = 0;
        }
        s += a;
    }
    printf("%d\n", ans);
}
```
核心实现思想：初始化答案为 1，依次读入每组人数，判断当前车是否装得下，若装不下则答案加 1 并将当前车人数清零，最后输出答案。

#### 作者：damage
```cpp
#include<stdio.h>
int n,m,a,wait,res; //wait表示当前等着走的人数
int main()
{
    scanf("%d%d",&n,&m);
    while(n--) //输入每组人数
    {
        scanf("%d",&a);
        if(a+wait<=m) wait+=a; //如果巴士能够带走这组人数加上之前等着走的人数，就让这组也加入等的行列
        else //如果无法全部带走
        {
            ++res; //多用一辆巴士
            wait=a; //带走之前等的人（wait=0），然后让这组人等（wait=a）
        }
    }
    if(wait) ++res; //注意特判是否还剩下人
    printf("%d\n",res);
    return 0;
}
```
核心实现思想：用 `wait` 表示当前等着走的人数，依次读入每组人数，判断巴士能否带走当前组和之前等着的人，若不能则多用一辆巴士并更新 `wait`，最后特判是否还有剩下的人。

### 最优关键思路或技巧
- 用一个变量记录当前车已载人数，依次遍历每组人，根据能否装下决定是否开新车。
- 最后要特判最后一辆车是否还有剩余人数，避免漏算。

### 可拓展之处
同类型题：类似的排队、分配资源的模拟题，如餐厅座位分配、货物运输等问题，都可以采用类似的模拟思路解决。

### 推荐洛谷题目
- P1047 [NOIP2005 普及组] 校门外的树
- P1098 [NOIP2007 提高组] 字符串的展开
- P1161 开灯

---
处理用时：34.15秒