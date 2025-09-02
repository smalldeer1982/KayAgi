# 题目信息

# Yaroslav and Permutations

## 题目描述

Yaroslav has an array that consists of $ n $ integers. In one second Yaroslav can swap two neighboring array elements. Now Yaroslav is wondering if he can obtain an array where any two neighboring elements would be distinct in a finite time.

Help Yaroslav.

## 说明/提示

In the first sample the initial array fits well.

In the second sample Yaroslav can get array: $ 1 $ , $ 2 $ , $ 1 $ . He can swap the last and the second last elements to obtain it.

In the third sample Yarosav can't get the array he needs.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4
7 7 7 7
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# Yaroslav和排列

## 题目描述
Yaroslav有一个由 $n$ 个整数组成的数组。在一秒内，Yaroslav可以交换两个相邻的数组元素。现在Yaroslav想知道他是否能在有限时间内得到一个任意两个相邻元素都不同的数组。
请帮助Yaroslav。

## 说明/提示
在第一个样例中，初始数组就符合要求。
在第二个样例中，Yaroslav可以得到数组：$1$，$2$，$1$。他可以通过交换最后一个和倒数第二个元素来得到。
在第三个样例中，Yaroslav无法得到他需要的数组。

## 样例 #1
### 输入
```
1
1
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
3
1 1 2
```
### 输出
```
YES
```

## 样例 #3
### 输入
```
4
7 7 7 7
```
### 输出
```
NO
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过统计数组中出现次数最多的元素的数量，然后与 $(n + 1) / 2$ 进行比较来判断是否能通过有限次相邻元素交换得到相邻元素都不同的数组。其依据在于，要使相邻元素不同，数量最多的元素在最优排列下，出现次数最多为 $(n + 1) / 2$ 次（$n$ 为奇数时，$a,k_1,a,k_2,a,k3,...,a$；$n$ 为偶数时，$k_1,a,k_2,a,k_3...,a$）。算法要点是利用桶来统计各元素出现次数，难点在于理解为什么以 $(n + 1) / 2$ 作为判断标准。各题解整体思路相近，主要区别在于代码实现细节和对读入、统计等操作的处理方式。

### 所选的题解
 - **作者：wangkangyou（4星）**
    - **关键亮点**：代码实现简洁明了，详细注释了读入函数，思路阐述清晰，通过举例说明了为什么以 $(n + 1) / 2$ 作为判断标准。
    - **重点代码核心实现思想**：通过 `read` 函数读入数据，用数组 `v` 作为桶统计每个数出现的次数，遍历桶数组找到出现次数最多的数，与 $(n + 1) / 2$ 比较并输出结果。
    - **核心代码片段**：
```cpp
int read(){
    int sum = 0, f = 1;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -f;
    for(; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
    return sum * f;
}
void write(int x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar('0' + x % 10);
    return;
}
const int N = 1e6 + 10;
int a[N], v[N];
signed main(){
    int n = read();
    for(int i = 1; i <= n; ++ i){
        a[i] = read();
        v[a[i]] ++;
    }
    int maxn = 0; 
    for(int i = 1; i <= 10001; ++ i){
        maxn = max(maxn, v[i]); 
    }
    puts(maxn <= (n + 1) / 2? "YES":"NO");
    return 0;
}
```
 - **作者：ruruo（4星）**
    - **关键亮点**：代码简洁，直接利用 `sort` 函数对桶数组排序来获取出现次数最多的元素数量，逻辑清晰。
    - **重点代码核心实现思想**：读入数据并统计各元素出现次数到 `cnt` 数组，对 `cnt` 数组排序后取最后一个元素（即出现次数最多的元素数量）与 $(n + 1) / 2$ 比较输出结果。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int cnt[1005], n; 

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    sort(cnt + 1, cnt + 1001); 
    if(cnt[1000] <= (n + 1) / 2) cout << "YES";
    else cout << "NO";
    return 0;
}
```
 - **作者：TheCliffSwallow（4星）**
    - **关键亮点**：详细分析了 $n$ 为奇数和偶数时相同数字最大出现次数的情况，代码实现直接在统计过程中更新最大出现次数，效率较高。
    - **重点代码核心实现思想**：读入数据并统计各元素出现次数到 `buskets` 数组，在统计过程中更新最大出现次数 `maxn`，最后将 `maxn` 与 $(n + 1) / 2$ 比较输出结果。
    - **核心代码片段**：
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#define int long long
using namespace std;
int n,a[105],buskets[1005],maxn;
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        buskets[a[i]]++;
        if(buskets[a[i]]>maxn){
            maxn=buskets[a[i]];
        }
    }
    if(maxn>(n+1)/2)    cout<<"NO";
    else    cout<<"YES";
    return 0;
}
```

### 最优关键思路或技巧
利用桶统计元素出现次数，通过分析最优排列情况得出以 $(n + 1) / 2$ 作为判断能否构造出相邻元素不同数组的标准。

### 拓展
同类型题或类似算法套路：对于一些判断能否通过某种操作达成特定排列条件的题目，常通过分析关键元素的数量限制以及最优排列情况来解决。例如一些涉及字符排列、数字序列调整等问题，可通过类似的统计和比较方式求解。

### 洛谷相似题目推荐
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
 - [P1228 地毯填补问题](https://www.luogu.com.cn/problem/P1228)

### 个人心得摘录与总结
 - **作者：蓝__**：Python 3读入较麻烦。总结：不同编程语言在输入输出处理上有差异，Python读入操作相对繁琐，需注意不同函数和数据类型转换方式。
 - **作者：Colead**：注意求最大值时不要写成 `long long maxn=*max_element(a+1,a+n+1);`。总结：在使用 `max_element` 等函数时，要注意其参数范围，避免因边界错误导致结果出错。 

---
处理用时：68.84秒