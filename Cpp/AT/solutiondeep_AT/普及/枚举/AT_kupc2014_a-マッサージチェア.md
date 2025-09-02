# 题目信息

# マッサージチェア

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2014/tasks/kupc2014_a

# AI分析结果

### 题目翻译
# 按摩椅

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2014/tasks/kupc2014_a

### 综合分析与结论
这些题解的核心思路都是为了求出学生坐到椅子上的最短总距离。主要思路是将学生和椅子的位置分别排序，然后对应位置相减取绝对值再求和。不同题解的差异主要体现在排序方式和代码语言上。

| 作者 | 思路 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| 幻之陨梦 | 先排序学生和椅子位置，再循环计算对应位置距离之和 | 使用标准库排序函数 `sort` | 无 | 4星 |
| 梦里调音 | 排序 `a`、`b` 数组，对应位置相减求和 | 使用标准库排序函数 `sort` | 理解排序后对应位置相减能得到最短总距离 | 4星 |
| CZQ_King | 手动冒泡排序学生和椅子位置，对应位置相减取绝对值求和 | 冒泡排序 | 手动实现排序 | 3星 |
| _lyc233 | 排序后对应位置求距离和 | 排序和绝对值函数 | 无 | 4星 |
| konglk | 手动 `swap` 排序，对应位置求距离和 | 手动 `swap` 排序 | 手动实现排序 | 3星 |
| 绝艺 | 冒泡排序，对应位置求距离和 | 冒泡排序 | 冒泡排序的实现 | 3星 |
| wushuang0828 | 冒泡排序，比较大小求距离和 | 冒泡排序 | 冒泡排序的实现 | 3星 |
| 准点的星辰 | 暴力枚举所有情况或用 `dfs` 枚举全排列求最小距离 | 暴力枚举或 `dfs` 枚举 | 枚举所有情况或实现 `dfs` 枚举 | 3星 |
| RioBlu | 排序后对应位置求距离和 | 使用标准库排序函数 `sort` | 无 | 4星 |

### 所选题解
- 幻之陨梦（4星）：关键亮点是使用万能头文件和标准库，代码简洁清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],b[5],ans;
int main(void)
{
    for(int i=1;i<4;i++) scanf("%d",&a[i]);
    for(int i=1;i<4;i++) scanf("%d",&b[i]);
    sort(a+1,a+4);
    sort(b+1,b+4);
    for(int i=1;i<4;i++) ans+=abs(a[i]-b[i]);
    printf("%d\n",ans);
}
```
- 梦里调音（4星）：思路清晰，代码简洁。
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans=0;
int main(){
    int i,j,k;
    int a[4],b[4];
    for(i=1;i<=3;i++)cin>>a[i];
    for(i=1;i<=3;i++)cin>>b[i];
    sort(a+1,a+4);
    sort(b+1,b+4);
    for(i=1;i<=3;i++)ans+=abs(a[i]-b[i]);
    cout<<ans<<endl;
    return 0;
}
```
- _lyc233（4星）：提供了 `Pascal` 和 `C++` 两种语言的实现，思路清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4],b[4];
int main()
 {
   for(int i=1;i<=3;i++) cin>>a[i];
   for(int i=1;i<=3;i++) cin>>b[i];
   sort(a+1,a+4);
   sort(b+1,b+4);
   int s=0;
   for(int i=1;i<=3;i++) s+=abs(a[i]-b[i]);
   cout<<s<<endl;
   return 0;
 }
```

### 最优关键思路或技巧
- 思维方式：通过排序将学生和椅子按位置从小到大排列，对应位置相减取绝对值求和能得到最短总距离。
- 代码实现技巧：使用标准库的排序函数 `sort` 可以简化排序操作。

### 拓展思路
同类型题可以是在二维平面上求点到点的最短总距离，或者多个群体之间的匹配最短距离问题。类似算法套路是先对相关数据进行排序，然后按照一定规则进行匹配计算。

### 洛谷相似题目
- P1090 [NOIP2004 提高组] 合并果子
- P1181 数列分段 Section I
- P1223 排队接水

### 个人心得
- CZQ_King：提到题目描述可能有误，不是 66 个整数，而是 6 个整数。
- konglk：提醒注意题目数据是 6 个数，不是 66 个数。 

---
处理用时：30.43秒