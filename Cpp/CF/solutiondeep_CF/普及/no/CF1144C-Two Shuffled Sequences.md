# 题目信息

# Two Shuffled Sequences

## 题目描述

Two integer sequences existed initially — one of them was strictly increasing, and the other one — strictly decreasing.

Strictly increasing sequence is a sequence of integers $ [x_1 < x_2 < \dots < x_k] $ . And strictly decreasing sequence is a sequence of integers $ [y_1 > y_2 > \dots > y_l] $ . Note that the empty sequence and the sequence consisting of one element can be considered as increasing or decreasing.

They were merged into one sequence $ a $ . After that sequence $ a $ got shuffled. For example, some of the possible resulting sequences $ a $ for an increasing sequence $ [1, 3, 4] $ and a decreasing sequence $ [10, 4, 2] $ are sequences $ [1, 2, 3, 4, 4, 10] $ or $ [4, 2, 1, 10, 4, 3] $ .

This shuffled sequence $ a $ is given in the input.

Your task is to find any two suitable initial sequences. One of them should be strictly increasing and the other one — strictly decreasing. Note that the empty sequence and the sequence consisting of one element can be considered as increasing or decreasing.

If there is a contradiction in the input and it is impossible to split the given sequence $ a $ to increasing and decreasing sequences, print "NO".

## 样例 #1

### 输入

```
7
7 2 7 3 3 1 4
```

### 输出

```
YES
2
3 7 
5
7 4 3 2 1 
```

## 样例 #2

### 输入

```
5
4 3 1 5 3
```

### 输出

```
YES
1
3 
4
5 4 3 1 
```

## 样例 #3

### 输入

```
5
1 1 2 1 2
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
5
0 1 2 3 4
```

### 输出

```
YES
0

5
4 3 2 1 0 
```

# AI分析结果

### 题目内容重写

#### 题目描述

最初存在两个整数序列——一个严格递增，另一个严格递减。

严格递增序列是一个整数序列 $ [x_1 < x_2 < \dots < x_k] $，而严格递减序列是一个整数序列 $ [y_1 > y_2 > \dots > y_l] $。注意，空序列和只包含一个元素的序列可以被视为递增或递减。

这两个序列被合并成一个序列 $ a $，然后 $ a $ 被打乱顺序。例如，对于递增序列 $ [1, 3, 4] $ 和递减序列 $ [10, 4, 2] $，可能的结果序列 $ a $ 是 $ [1, 2, 3, 4, 4, 10] $ 或 $ [4, 2, 1, 10, 4, 3] $。

输入给出的是这个被打乱的序列 $ a $。

你的任务是找到任何两个合适的初始序列。其中一个应该是严格递增的，另一个应该是严格递减的。注意，空序列和只包含一个元素的序列可以被视为递增或递减。

如果输入中存在矛盾，无法将给定的序列 $ a $ 分割成递增和递减序列，则输出 "NO"。

#### 样例 #1

##### 输入

```
7
7 2 7 3 3 1 4
```

##### 输出

```
YES
2
3 7 
5
7 4 3 2 1 
```

#### 样例 #2

##### 输入

```
5
4 3 1 5 3
```

##### 输出

```
YES
1
3 
4
5 4 3 1 
```

#### 样例 #3

##### 输入

```
5
1 1 2 1 2
```

##### 输出

```
NO
```

#### 样例 #4

##### 输入

```
5
0 1 2 3 4
```

##### 输出

```
YES
0

5
4 3 2 1 0 
```

### 算法分类

排序、构造

### 题解分析与结论

#### 题解对比

1. **三点水一个各**：
   - 使用桶排统计每个元素的出现次数，若某个元素出现超过两次则输出 "NO"。
   - 通过遍历桶数组，分别构造严格递增和严格递减序列。
   - 代码简洁，逻辑清晰。

2. **Super_Cube**：
   - 使用排序和标记数组，记录每个元素是否属于严格递增序列。
   - 通过遍历排序后的数组，构造严格递增和严格递减序列。
   - 代码可读性较好，思路明确。

3. **cqbztz2**：
   - 使用排序和标记数组，记录每个元素是否属于严格递增序列。
   - 通过遍历排序后的数组，构造严格递增和严格递减序列。
   - 代码逻辑与Super_Cube类似，但实现略有不同。

4. **ylinxin2010**：
   - 使用桶排统计每个元素的出现次数，若某个元素出现超过两次则输出 "NO"。
   - 通过遍历桶数组，分别构造严格递增和严格递减序列。
   - 代码逻辑与三点水一个各类似，但实现略有不同。

5. **Ousmane_Dembele**：
   - 使用贪心策略，通过遍历排序后的数组，构造严格递增和严格递减序列。
   - 代码逻辑较为复杂，但思路独特。

6. **da32s1da**：
   - 使用桶排统计每个元素的出现次数，若某个元素出现超过两次则输出 "NO"。
   - 通过遍历桶数组，分别构造严格递增和严格递减序列。
   - 代码简洁，逻辑清晰。

#### 最优关键思路

1. **桶排统计元素出现次数**：通过桶排统计每个元素的出现次数，若某个元素出现超过两次则输出 "NO"。
2. **构造严格递增和严格递减序列**：通过遍历桶数组，分别构造严格递增和严格递减序列。

#### 可拓展之处

- 类似题目可以考察如何将一个序列分割成多个满足特定条件的子序列，如递增、递减、非递增、非递减等。
- 可以进一步优化算法，减少空间复杂度或时间复杂度。

#### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
3. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)

### 所选高星题解

#### 1. 三点水一个各 (4星)

**关键亮点**：
- 使用桶排统计元素出现次数，逻辑清晰。
- 通过遍历桶数组，分别构造严格递增和严格递减序列，代码简洁。

**核心代码**：
```cpp
#include<cstdio>
#include<cstdlib>
int n,x,a[200200],b[200200],sa=0,sb=0;
int cnt[200200];//count数组是桶
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    { 
        scanf("%d",&x);
        cnt[x]++;
        if(cnt[x]>2)//某一元素出现两次以上
        {
            printf("NO");
            return 0;
        }
    }
    for(int i=200050;i>=0;i--)//严格递减序列
      if(cnt[i])
      {
          sa++;
          a[sa]=i;
          cnt[i]--;
      }
    for(int i=0;i<=200050;i++)//严格递增序列
      if(cnt[i])
      {
          sb++;
          b[sb]=i;
          cnt[i]--;
      }
    printf("YES\n");
    printf("%d\n",sb);
    for(int i=1;i<=sb;i++)
      printf("%d ",b[i]);
    printf("\n%d\n",sa);
    for(int i=1;i<=sa;i++)
      printf("%d ",a[i]);
    return 0;
}
```

#### 2. Super_Cube (4星)

**关键亮点**：
- 使用排序和标记数组，记录每个元素是否属于严格递增序列。
- 通过遍历排序后的数组，构造严格递增和严格递减序列，代码可读性较好。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[200005];
int a[200005],n,cnt=1,ans;
//cnt表示当前这个数出现的个数,ans表示严格递增序列长度
int main(){
    cin>>n;
    for(int i=1;i<=n;cin>>a[i++]);
    sort(a+1,a+n+1);//从小到大排序
    for(int i=2;i<=n;i++){
        if(a[i]==a[i-1]){//与上个元素相同
            if(++cnt==3){//出现了3个相同元素说明无法分成需要的两个序列
                printf("NO");return 0;
            }vis[i]=1;++ans;//将这个数标记为1,并且严格递增序列长度+1
        }else cnt=1;//数字与上个数不同则把计数器置为1
    }puts("YES");//肯定输出YES
    cout<<ans<<endl;//输出严格递增序列长度
    for(int i=2;i<=n;i++){
        if(vis[i])cout<<a[i]<<' ';//标记过直接输出
    }cout<<endl<<n-ans<<endl;//严格递减序列长度
    for(int i=n;i;i--){//注意是倒着!
        if(!vis[i])cout<<a[i]<<' ';//没标记过就输出
    }
    return 0;
}
```

#### 3. da32s1da (4星)

**关键亮点**：
- 使用桶排统计元素出现次数，逻辑清晰。
- 通过遍历桶数组，分别构造严格递增和严格递减序列，代码简洁。

**核心代码**：
```cpp
#include<cstdio>
const int N=2e5+50;
int n,x,a[N],b[N],c,d,cnt[N];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&x),cnt[x]++;//记录出现次数
    for(int i=0;i<N;i++)
    if(cnt[i]>2){puts("NO");return 0;}//超过2次一定无解
    for(int i=0;i<N;i++)
    if(cnt[i])a[++c]=i,cnt[i]--;//严格递增序列
    for(int i=N-1;i>=0;i--)
    if(cnt[i])b[++d]=i,cnt[i]--;//严格递降序列
    puts("YES");
    printf("%d\n",c);
    for(int i=1;i<=c;i++)printf("%d ",a[i]);
    printf("\n%d\n",d);
    for(int i=1;i<=d;i++)printf("%d ",b[i]);
}
```

---
处理用时：57.31秒