# 题目信息

# Filya and Homework

## 题目描述

刺猬 Filya 今天第一次去学校，由于老师给他的作业太难所有他需要你的帮助来完成：

老师给 Filya 一个仅包含正整数的数组 $a_1, a_2, \cdots,a_n $ 首先，他选择一个整数 $x$ ，然后他将 $x$ 加到数组的某些元素上（仅有一次），再从其他一些元素中减去 $x$，（每个元素仅减一次）并留一些元素不进行操作。经过这些操作以后，他希望数组内所有的元素均相等。现在，他想知道他可不可以找到这样一个 $x$ 并进行上述操作，使数组内的每一个元素相等。

## 说明/提示

在第一个样例中，应该选择第一个元素作为 $x$，添加到第一个和第五个，然后从第二个和第三个减去。

## 样例 #1

### 输入

```
5
1 3 3 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
NO
```

# AI分析结果

【题目内容】
# Filya和家庭作业

## 题目描述
刺猬Filya今天第一次去上学，由于老师给他的作业太难了，所以他需要你的帮助来完成：

老师给了Filya一个仅包含正整数的数组 $a_1, a_2, \cdots,a_n $。首先，他选择一个整数 $x$ ，然后他将 $x$ 加到数组的某些元素上（每个元素仅加一次），再从其他一些元素中减去 $x$（每个元素仅减一次），并留一些元素不进行操作。经过这些操作以后，他希望数组内所有的元素均相等。现在，他想知道他可不可以找到这样一个 $x$ 并进行上述操作，使数组内的每一个元素相等。

## 说明/提示
在第一个样例中，应该选择第一个元素作为 $x$，添加到第一个和第五个，然后从第二个和第三个减去。

## 样例 #1
### 输入
```
5
1 3 3 2 1
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
5
1 2 3 4 5
```
### 输出
```
NO
```

【算法分类】
数学

【综合分析与结论】
这些题解的核心思路都是先确定数组中不同元素的个数，再根据不同元素个数的情况来判断是否存在满足条件的 $x$ 。具体分类讨论情况如下：
1. 不同元素个数为 1 时，令 $x = 0$ 即可使数组元素相等，答案为 `YES`。
2. 不同元素个数为 2 时，令 $x$ 为两个不同元素的差值，通过加或减操作可使数组元素相等，答案为 `YES`。
3. 不同元素个数为 3 时，设三个元素为 $a,b,c$（$a < b < c$），当且仅当 $b - a = c - b$（即三个数成等差数列）时，答案为 `YES`，否则为 `NO`。
4. 不同元素个数大于 3 时，不存在满足条件的 $x$，答案为 `NO`。

各题解的主要区别在于去重和获取不同元素个数的方法，部分使用 `set` 容器（自动去重和排序），部分使用排序加 `unique` 函数，还有部分使用数组手动去重。

【所选的题解】
- bloodstalk（4星）：思路清晰，代码实现详细，使用排序和 `unique` 函数去重，对去重和判断逻辑有注释。
- FanYongchen（4星）：思路明确，使用 `set` 容器去重，代码简洁易懂。
- abensyl（4星）：同样使用 `set` 容器，思路和代码都比较清晰，对判断条件有详细说明。

【重点代码】
### bloodstalk的代码
```cpp
#include<bits/stdc++.h>
const int N=1e5+5;
using namespace std;

il int read()
{
    int f=0,s=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
    for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
    return f ? -s : s;
}

int n;
int a[N];

int main()
{
    n = read();
    for(int i=1;i<=n;i++)
        a[i] = read();
    sort(a+1,a+n+1);
    int nn = unique(a+1,a+n+1) - a -1;
    if(nn > 3) printf("NO");
    else if(nn == 3)
    {
        if(a[2] - a[1] == a[3] - a[2]) printf("YES");
        else printf("NO");
    }
    else printf("YES");
    return 0;
}
```
核心实现思想：先读取数组元素，对数组进行排序，然后使用 `unique` 函数去重，得到不同元素的个数 `nn`，再根据 `nn` 的值进行分类判断。

### FanYongchen的代码
```cpp
#include <iostream>
#include <set>
using namespace std;
set<int> num;
int main()
{
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        num.insert(x);
    }
    if (num.size() > 3) cout << "NO";
    else if (num.size() < 3) cout << "YES";
    else
    {
        int a[3] = { 0 }, i = 0;
        for (set<int>::iterator it = num.begin(); it != num.end(); it++) a[i++] = *(it);
        if (a[1] - a[0] == a[2] - a[1]) cout << "YES";
        else cout << "NO";
    }
    return 0;
}
```
核心实现思想：使用 `set` 容器存储数组元素，自动去重和排序，根据 `set` 的大小进行分类判断，当大小为 3 时，取出元素判断是否成等差数列。

### abensyl的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    set<int> k;
    set<int>::iterator it;
    int n,a[4],z;
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>z;
        k.insert(z);
    }
    int len=k.size();
    if(len<=2) puts("YES");
    else if(len>=4) puts("NO");
    else {
        int i=0;
        for(it=k.begin();it!=k.end();it++,++i) a[i]=*it;
        if(a[0]+a[2]==a[1]*2) {
            puts("YES");
            return 0;
        }
        puts("NO");
    }
    return 0;
}
```
核心实现思想：同样使用 `set` 容器去重，根据 `set` 的大小分类判断，当大小为 3 时，通过判断 $a[0] + a[2] == a[1] * 2$ 来确定是否成等差数列。

【关键思路或技巧】
- 使用 `set` 容器可以方便地去重和排序，简化代码实现。
- 对不同元素个数进行分类讨论，将复杂问题简单化。

【拓展思路】
同类型题目可能会在操作规则上进行变化，例如可以进行多次加或减操作，或者操作的数不是同一个 $x$ 等。解题时依然可以先分析不同元素的情况，再根据规则进行分类讨论。

【推荐题目】
1. P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
2. P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
3. P1059 [明明的随机数](https://www.luogu.com.cn/problem/P1059)

【个人心得】
tanghg提到看到数据范围就知道不可以直接暴力去试 $x$，并且优化时要注意，如果每次都在去重后再判断会 TLE on 11，只需要加一句在循环内判断是否不同元素已经超过 3 了即可。总结就是要根据数据范围选择合适的算法，并且在实现过程中注意优化，避免超时。 

---
处理用时：48.50秒