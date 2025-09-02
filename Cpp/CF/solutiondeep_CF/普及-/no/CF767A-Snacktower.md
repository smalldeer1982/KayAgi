# 题目信息

# Snacktower

## 题目描述

According to an old legeng, a long time ago Ankh-Morpork residents did something wrong to miss Fortune, and she cursed them. She said that at some time $ n $ snacks of distinct sizes will fall on the city, and the residents should build a Snacktower of them by placing snacks one on another. Of course, big snacks should be at the bottom of the tower, while small snacks should be at the top.

Years passed, and once different snacks started to fall onto the city, and the residents began to build the Snacktower.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767A/180cab69cae65dd25cd78379f99c54f80aacaf67.png)However, they faced some troubles. Each day exactly one snack fell onto the city, but their order was strange. So, at some days the residents weren't able to put the new stack on the top of the Snacktower: they had to wait until all the bigger snacks fell. Of course, in order to not to anger miss Fortune again, the residents placed each snack on the top of the tower immediately as they could do it.

Write a program that models the behavior of Ankh-Morpork residents.

## 说明/提示

In the example a snack of size $ 3 $ fell on the first day, and the residents immediately placed it. On the second day a snack of size $ 1 $ fell, and the residents weren't able to place it because they were missing the snack of size $ 2 $ . On the third day a snack of size $ 2 $ fell, and the residents immediately placed it. Right after that they placed the snack of size $ 1 $ which had fallen before.

## 样例 #1

### 输入

```
3
3 1 2
```

### 输出

```
3
 
2 1```

## 样例 #2

### 输入

```
5
4 5 1 2 3
```

### 输出

```
 
5 4
 
 
3 2 1
```

# AI分析结果

### 题目中文重写
# 零食塔

## 题目描述
根据一个古老的传说，很久以前，安科 - 莫波克（Ankh - Morpork）的居民得罪了命运女神，于是她诅咒了他们。她说，在某个时候，$n$ 个大小各异的零食会掉落在这座城市，居民们应该用这些零食建造一座零食塔，将它们一个叠在另一个上面。当然，大的零食应该放在塔的底部，而小的零食应该放在顶部。

多年过去了，有一天，不同的零食开始掉落在这座城市，居民们开始建造零食塔。

然而，他们遇到了一些麻烦。每天恰好有一个零食掉落在城市里，但掉落的顺序很奇怪。所以，在某些日子里，居民们无法将新掉落的零食放在零食塔的顶部：他们必须等到所有更大的零食都掉落下来。当然，为了不再激怒命运女神，居民们一有机会就立即将每个零食放在塔的顶部。

编写一个程序来模拟安科 - 莫波克居民的行为。

## 说明/提示
在示例中，第一天掉落了一个大小为 $3$ 的零食，居民们立即将其放置好。第二天掉落了一个大小为 $1$ 的零食，居民们无法放置它，因为他们还缺少大小为 $2$ 的零食。第三天掉落了一个大小为 $2$ 的零食，居民们立即将其放置好。紧接着，他们放置了之前掉落的大小为 $1$ 的零食。

## 样例 #1
### 输入
```
3
3 1 2
```
### 输出
```
3
 2 1
```

## 样例 #2
### 输入
```
5
4 5 1 2 3
```
### 输出
```
5 4
3 2 1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟零食掉落和放置的过程。在每一天，判断新掉落的零食是否可以放置，如果可以，就按照从大到小的顺序尽可能多地放置零食。

各题解的主要区别在于实现细节和优化程度。有的题解使用数组标记零食是否出现和是否放置，有的题解使用变量记录当前需要放置的零食大小。部分题解还进行了卡常优化，如使用快速读入输出、减少不必要的遍历等。

### 所选题解
- **作者：CZ_7 (赞：2)，4星**
    - **关键亮点**：思路清晰，不仅给出了基础的模拟代码，还对超时问题进行了详细的优化分析和处理，包括使用快速读入输出、减少不必要的遍历等，具有较高的参考价值。
    - **个人心得**：原代码在测试点19超时，通过添加GCC优化指令、使用快速读入输出、记录已放置的最小值等优化方法解决了超时问题。
- **作者：alex_liu (赞：0)，4星**
    - **关键亮点**：代码简洁明了，直接模拟了每天判断当前掉落的蛋糕是否是需要摆放的蛋糕，若满足条件则继续检查是否有其他可摆放的蛋糕，逻辑清晰易懂。
- **作者：Noby_Glds (赞：0)，4星**
    - **关键亮点**：思路清晰，使用变量记录当前塔上应当放的糖果大小，数组记录糖果是否掉落，实现了模拟过程，代码简洁。

### 重点代码
#### CZ_7的优化后代码
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
int read(){
    int a=0,b=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')b=-1;c=getchar();}
    while(c>='0'&&c<='9')a=a*10+c-48,c=getchar();
    return a*b;
}
int n,top,a;
bool flag[100002],put[100002];
int main(){
    n=read();
    top=n;
    for(int i=1;i<=n;++i){
        a=read();
        flag[a]=true;
        if(a<n-i){
            putchar('\n');
            continue;
        }
        for(int j=top;j>=n-i;--j){
            if(flag[j]&&!put[j]){
                put[j]=true;
                printf("%d ",j);
                top=j;
            }
            if(!flag[j])break;
        }
        putchar('\n');
    }
    return 0;
}
```
**核心实现思想**：使用 `flag` 数组标记零食是否出现，`put` 数组标记零食是否放置。通过快速读入 `read` 函数加快输入速度，记录 `top` 为已放置的最小值，减少不必要的遍历。

#### alex_liu的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    bool a[100005];//a[i] 为 1 ，则代表重量为 i 的大小的蛋糕已经出现，否则没有 
    int n,x;//n 为总天数， x 是当前掉落蛋糕的大小
    cin>>n;
    int now=n;//now 为当前需要放的蛋糕的大小（初始化为 n ）
    memset(a,0,sizeof(a));//a 数组初始化为 0 
    for(int i=1;i<=n;i++){
        cin>>x;
        a[x]=1;//标记当前大小的蛋糕已经出现 
        if(x==now){//当前蛋糕需要摆放 
            cout<<now<<" ";//输出当前蛋糕的大小 
            now--;//需要的蛋糕的大小 -1 
            while(a[now]==1){//当现在存储的蛋糕还可以继续摆放时 
                cout<<now<<" ";//输出当前蛋糕的大小 
                now--;//需要的蛋糕的大小 -1 
            }
        }
        cout<<endl;//注意换行 
    }
    return 0;//完美结束 
}
```
**核心实现思想**：使用 `a` 数组标记蛋糕是否出现，`now` 记录当前需要放置的蛋糕大小。每天判断新掉落的蛋糕是否是需要放置的，如果是则输出并更新 `now`，继续检查是否有其他可放置的蛋糕。

#### Noby_Glds的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,a,b[100010];
int main(){
    cin>>n;
    p=n;
    for(int i=1;i<=n;i++){
        cin>>a;
        b[a]=1;
        if(a==p){
            cout<<a<<" ";
            p--;
            while(b[p]==1) cout<<p<<" ",p--;
        }
        cout<<endl;
    }
    return 0;
}
```
**核心实现思想**：使用 `b` 数组标记糖果是否掉落，`p` 记录当前塔上应当放的糖果大小。每天判断新掉落的糖果是否等于 `p`，如果是则输出并更新 `p`，继续检查是否有其他可输出的糖果。

### 最优关键思路或技巧
- 使用数组标记零食（蛋糕、糖果）是否出现和是否放置，方便判断是否可以放置。
- 记录当前需要放置的零食大小，减少不必要的遍历。
- 采用快速读入输出优化代码性能。

### 拓展思路
同类型题通常是模拟现实生活中的某种过程，需要按照一定的规则进行操作。解题关键在于理清操作步骤和判断条件，使用合适的数据结构来记录状态。类似的模拟题可能涉及游戏规则模拟、事件处理模拟等。

### 推荐题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)

---
处理用时：51.00秒