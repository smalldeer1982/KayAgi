# 题目信息

# Trains

## 题目描述

程序员Vasya有两个女友，一个叫Dasha，另一个叫Masha。她们分别住在Vasya所在地铁线路的两个始发站。

当Vasya有空闲时间时，他会去找他的一个女友。他在某个时间下降到火车站，等待第一班火车到来（地铁去哪，他就去哪个女友那里）。但两个方向的火车发车时间不同，向Dasha方向的火车a分钟一班，向Masha方向的火车b分钟一班。如果两列火车同时到达，Vasya会朝着发车时间较长的方向前进。在第0分钟，两班火车同时从Vasya所在站的前一个站和后一个站开出。（chinaxjh这个蒟蒻无法翻译的更好一点了）

问Vasya去哪个女友那里的概率大。（输出英文名即可，如果一样输出“Equal”，引号不用输出）

## 样例 #1

### 输入

```
3 7
```

### 输出

```
Dasha
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
Masha
```

## 样例 #3

### 输入

```
2 3
```

### 输出

```
Equal
```

# AI分析结果

【题目内容】
# 火车

## 题目描述

程序员Vasya有两个女友，一个叫Dasha，另一个叫Masha。她们分别住在Vasya所在地铁线路的两个始发站。

当Vasya有空闲时间时，他会去找他的一个女友。他在某个时间下降到火车站，等待第一班火车到来（地铁去哪，他就去哪个女友那里）。但两个方向的火车发车时间不同，向Dasha方向的火车a分钟一班，向Masha方向的火车b分钟一班。如果两列火车同时到达，Vasya会朝着发车时间较长的方向前进。在第0分钟，两班火车同时从Vasya所在站的前一个站和后一个站开出。

问Vasya去哪个女友那里的概率大。（输出英文名即可，如果一样输出“Equal”，引号不用输出）

## 样例 #1

### 输入

```
3 7
```

### 输出

```
Dasha
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
Masha
```

## 样例 #3

### 输入

```
2 3
```

### 输出

```
Equal
```

【算法分类】
数学

【综合分析与结论】
这些题解的核心思路都是利用列车到达的周期性，通过求出两列火车发车间隔时间的最小公倍数来确定一个周期，再根据周期内两列火车的停靠数判断Vasya去哪个女友那里的概率大。各题解的主要区别在于实现细节，如计算最小公倍数的方式、处理最后同时到达情况的方法等。

【所选题解】
- **作者：_Gabriel_ (4星)**
  - **关键亮点**：思路清晰，代码简洁，使用C++自带的`__gcd`函数计算最大公因数，进而求出最小公倍数。
  - **个人心得**：提醒要将`a`和`b`开`long long`，避免数据溢出。
- **作者：Arrtan_73 (4星)**
  - **关键亮点**：思路明确，解释详细，同样使用标准库自带的`__gcd`函数，代码简洁易读。
  - **个人心得**：强调一定要开`long long`。
- **作者：lizulong (4星)**
  - **关键亮点**：使用宏定义和`lcm`函数，代码结构清晰，通过`ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)`加快输入输出。
  - **个人心得**：无。

【重点代码】
```cpp
// _Gabriel_ 的代码
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll lcm(ll x, ll y) {
    return x * y / __gcd(x, y);
}

ll a, b;

int main() {
    cin >> a >> b;
    ll ans = lcm(a, b);
    a = ans / a;
    b = ans / b;
    if (a > b) {
        b++; 
    } else {
        a++;
    }
    if (a > b) {
        cout << "Dasha" << "\n";
    } else if (a == b) {
        cout << "Equal" << "\n";
    } else {
        cout << "Masha" << "\n";
    }
    return 0;
}

// Arrtan_73 的代码
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::__gcd;
long long a, b;

int main() {
    cin >> a >> b;
    long long cnt = a * b / __gcd(a, b);
    a = cnt / a;
    b = cnt / b;
    if (a > b)
        b++;
    else
        a++;
    if (a > b)
        cout << "Dasha";
    else if (a == b)
        cout << "Equal";
    else
        cout << "Masha";
}

// lizulong 的代码
#include<bits/stdc++.h>
#define int long long
#define gcd __gcd
using namespace std;
int lcm(int a,int b){
    return a/gcd(a,b)*b;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int a,b;
    cin>>a>>b;
    int t= lcm(a,b);
    a=t/a,b=t/b;
    if(a>b) b++;else a++;
    if(a>b) cout<<"Dasha\n";
    else if(a==b) cout<<"Equal\n";
    else cout<<"Masha\n";
}
```
【核心实现思想】
1. 计算两数的最小公倍数`lcm`，可通过`a * b / __gcd(a, b)`实现。
2. 用最小公倍数分别除以`a`和`b`，得到两列火车在一个周期内的停靠数。
3. 处理最后两列火车同时到达的情况，给发车间隔长的火车停靠数加1。
4. 比较两列火车的停靠数，输出概率大的女友名字，若相等则输出“Equal”。

【可拓展之处】
同类型题可能会涉及多个周期、不同的发车规则等，解题思路类似，都是先确定周期，再根据周期内的情况进行分析。类似算法套路还可用于解决时间安排、资源分配等问题。

【推荐题目】
1. P1044 栈
2. P1069 细胞分裂
3. P1072 Hankson的趣味题

【个人心得总结】
多位题解作者都强调了要将变量开`long long`，否则可能会因数据溢出导致答案错误。例如，chinaxjh提到自己因未开`long long`而WA了2次。

---
处理用时：35.03秒