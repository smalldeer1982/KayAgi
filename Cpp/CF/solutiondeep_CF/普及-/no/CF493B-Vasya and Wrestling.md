# 题目信息

# Vasya and Wrestling

## 题目描述

Vasya has become interested in wrestling. In wrestling wrestlers use techniques for which they are awarded points by judges. The wrestler who gets the most points wins.

When the numbers of points of both wrestlers are equal, the wrestler whose sequence of points is lexicographically greater, wins.

If the sequences of the awarded points coincide, the wrestler who performed the last technique wins. Your task is to determine which wrestler won.

## 说明/提示

Vasya has become interested in wrestling. In wrestling wrestlers use techniques for which they are awarded points by judges. The wrestler who gets the most points wins.

When the numbers of points of both wrestlers are equal, the wrestler whose sequence of points is lexicographically greater, wins.

If the sequences of the awarded points coincide, the wrestler who performed the last technique wins. Your task is to determine which wrestler won.

## 样例 #1

### 输入

```
5
1
2
-3
-4
3
```

### 输出

```
second
```

## 样例 #2

### 输入

```
3
-1
-2
3
```

### 输出

```
first
```

## 样例 #3

### 输入

```
2
4
-4
```

### 输出

```
second
```

# AI分析结果

### 题目中文重写
# 瓦西亚与摔跤

## 题目描述
瓦西亚对摔跤产生了兴趣。在摔跤比赛中，摔跤手使用各种技巧，裁判会根据这些技巧给他们打分。得分最多的摔跤手获胜。

当两名摔跤手的得分相等时，得分序列字典序更大的摔跤手获胜。

如果得分序列完全相同，那么最后使用技巧的摔跤手获胜。你的任务是确定哪位摔跤手赢得了比赛。

## 说明/提示
瓦西亚对摔跤产生了兴趣。在摔跤比赛中，摔跤手使用各种技巧，裁判会根据这些技巧给他们打分。得分最多的摔跤手获胜。

当两名摔跤手的得分相等时，得分序列字典序更大的摔跤手获胜。

如果得分序列完全相同，那么最后使用技巧的摔跤手获胜。你的任务是确定哪位摔跤手赢得了比赛。

## 样例 #1
### 输入
```
5
1
2
-3
-4
3
```
### 输出
```
second
```

## 样例 #2
### 输入
```
3
-1
-2
3
```
### 输出
```
first
```

## 样例 #3
### 输入
```
2
4
-4
```
### 输出
```
second
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟摔跤比赛的得分过程，先分别统计两名摔跤手的总分，再在总分相等的情况下比较得分序列的字典序，若字典序也相同则判断最后得分的选手。

不同题解的差异主要体现在数据结构的选择和代码实现的细节上。部分题解使用数组存储得分序列，部分使用向量或队列；在判断字典序时，有的逐位比较，有的直接利用容器的比较运算符。

### 所选题解
- **作者：Kawaii_qiuw (赞：1)，4星**
    - **关键亮点**：思路清晰，对各种情况的讨论详细，代码注释丰富，可读性高。
    - **个人心得**：备注中提到由于 RemoteJudge 暂不可用，所以没有 AC 记录。
- **作者：Stone_Xz (赞：1)，4星**
    - **关键亮点**：对题目分析全面，代码结构清晰，按照总分比较、字典序比较、最后得分选手判断的步骤依次进行。
- **作者：liuzhongrui (赞：3)，4星**
    - **关键亮点**：代码简洁，利用向量的比较运算符简化了字典序的比较过程。

### 重点代码
#### 作者：Kawaii_qiuw
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 2e5 + 5;
int a[maxn], b[maxn];
LL sum;

int main() {
    int n, in;
    while (scanf("%d", &n) != EOF) {
        sum = 0;
        int mark;
        int l1 = 0, l2 = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d", &in);
            sum += in;
            if (in > 0) {
                a[l1++] = in;
                mark = 1;
            }
            else {
                b[l2++] = -in;
                mark = 2;
            }
        }
        if (sum > 0)
            printf("first\n");
        else if (sum < 0)
            printf("second\n");
        else {
            int flag = 0;
            for (int i = 0; i < l1 && i < l2; i++) {
                if (a[i] > b[i]) {
                    flag = 1;
                    break;
                }
                else if (a[i] < b[i]) {
                    flag = 2;
                    break;
                }
            }
            if (!flag) {
                if (l1 == l2)
                    printf("%s\n", mark == 1 ? "first" : "second");
            }
            else        
                printf("%s\n", flag == 1 ? "first" : "second");
        }
    }
    return 0;
}
```
**核心实现思想**：用数组 `a` 和 `b` 分别存储两名选手的得分，`sum` 记录总分差值。先遍历输入统计总分和得分序列，再根据总分情况判断，总分相等时逐位比较得分序列，若序列相同则根据最后得分选手判断。

#### 作者：Stone_Xz
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, a[N], b[N], cnt_a, cnt_b, sum_1, sum_2, e;

signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        int num;
        cin >> num;
        if(num > 0){
            a[++cnt_a] = num;
            sum_1 += num;
            e = 1;             
        }
        else{
            b[++cnt_b] = -num; 
            sum_2 += -num;
            e = 2;
        }
    }
    if(sum_1 > sum_2)          
        cout << "first";
    else if(sum_1 < sum_2)
        cout << "second";
    else
    {
        for(int i = 1; i <= min(cnt_a, cnt_b); i++) 
            if(a[i] > b[i]){
                cout << "first";
                return 0;
            }
            else if(a[i] < b[i]){
                cout << "second";
                return 0;
            }
        if(e == 1)                             
            cout << "first";
        else
            cout << "second";
    }
    return 0;
}
```
**核心实现思想**：用数组 `a` 和 `b` 分别记录两名选手的得分，`sum_1` 和 `sum_2` 记录总分，`e` 记录最后得分选手。先遍历输入统计信息，再按总分、字典序、最后得分选手的顺序判断。

#### 作者：liuzhongrui
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x;
signed main() {
    scanf("%lld",&n);
    vector<int> v[2];
    for(int i=0; i<n; i++) {
        scanf("%lld",&x);
        v[x>0].push_back(abs(x));
        v[x>0][0]+=abs(x);
    }
    v[x>0].push_back(1);
    printf("%s",(v[1]>v[0]?"first":"second"));
    return 0;
}
```
**核心实现思想**：用向量数组 `v` 存储两名选手的得分，向量的第一个元素存储总分。遍历输入将得分存入相应向量并更新总分，最后利用向量的比较运算符判断胜负。

### 最优关键思路或技巧
- 利用向量的比较运算符直接比较得分序列的字典序，简化代码。
- 使用标记变量记录最后得分的选手，方便在总分和字典序都相同的情况下判断胜负。

### 可拓展之处
同类型题通常是模拟类题目，需要根据给定的规则进行模拟操作。类似算法套路包括按步骤模拟、分类讨论、使用合适的数据结构存储信息等。

### 推荐题目
- [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：简单的模拟输入输出。
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：需要对数字进行枚举和判断，锻炼模拟和枚举能力。
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：模拟摘苹果的过程，涉及简单的条件判断。

---
处理用时：43.73秒