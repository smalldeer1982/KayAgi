# 题目信息

# Happy Birthday

## 题目描述

You have a set of birthday cake candles. Each of such candles represents a digit between $ 0 $ and $ 9 $ , inclusive.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1250H/d5cd74fe7ac15db0e75f654137471b0878202976.png)Example of birthday cake candles.Let's denote the candle representing the digit $ d $ as $ d $ -candle.

Your set contains $ c_0 $ instances of $ 0 $ -candles, $ c_1 $ instances of $ 1 $ -candles and so on. So, the total number of candles is $ c_0+c_1+\dots+c_9 $ .

These digits are needed to wish your cat a happy birthday. For each birthday, starting with the first, you want to compose the age of the cat using the digits from the set.

Since you light candles for a very short time, candles don't have time to burn out. For this reason you can reuse candles an arbitrary number of times (therefore your set of candles never changes).

For example, if you have one instance of each digit (i.e. $ c_0=c_1=\dots=c_9=1 $ ), you can compose any number from $ 1 $ to $ 10 $ using this set, but you cannot compose $ 11 $ .

You have to determine the first birthday, on which you cannot compose the age of the cat using the candles from your set. In other words, find the minimum number $ y $ such that all numbers from $ 1 $ to $ y-1 $ can be composed by digits from your set, but $ y $ cannot be composed.

## 样例 #1

### 输入

```
4
1 1 1 1 1 1 1 1 1 1
0 0 1 1 2 2 3 3 4 4
1 2 1 2 1 3 1 0 0 0
0 1 2 1 4 3 1 1 2 1
```

### 输出

```
11
1
7
10
```

# AI分析结果

### 题目内容翻译
#### 题目描述
你有一组生日蛋糕蜡烛。每根蜡烛代表一个数字，数字范围在 $0$ 到 $9$ 之间，包括 $0$ 和 $9$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1250H/d5cd74fe7ac15db0e75f654137471b0878202976.png)  
示例：生日蛋糕蜡烛。我们将代表数字 $d$ 的蜡烛称为 $d$-蜡烛。

你的集合中有 $c_0$ 根 $0$-蜡烛，$c_1$ 根 $1$-蜡烛，依此类推。因此，蜡烛的总数为 $c_0 + c_1 + \dots + c_9$。

这些数字用于给你的猫庆祝生日。对于每个生日，从第一个生日开始，你希望用集合中的数字来组成猫的年龄。

由于你点燃蜡烛的时间非常短，蜡烛没有时间烧完。因此，你可以任意次数地重复使用蜡烛（因此你的蜡烛集合永远不会改变）。

例如，如果你有每个数字的一根蜡烛（即 $c_0 = c_1 = \dots = c_9 = 1$），你可以用这个集合组成从 $1$ 到 $10$ 的任何数字，但你不能组成 $11$。

你需要确定第一个无法用蜡烛集合组成猫的年龄的生日。换句话说，找到最小的数字 $y$，使得从 $1$ 到 $y-1$ 的所有数字都可以用集合中的数字组成，但 $y$ 无法组成。

#### 样例 #1
##### 输入
```
4
1 1 1 1 1 1 1 1 1 1
0 0 1 1 2 2 3 3 4 4
1 2 1 2 1 3 1 0 0 0
0 1 2 1 4 3 1 1 2 1
```

##### 输出
```
11
1
7
10
```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心策略找到无法组成的最小数字。所有题解都采用了类似的思路：首先找到数字 $1$ 到 $9$ 中出现次数最少的数字，然后根据 $0$ 的出现次数进行特判。具体来说，如果 $0$ 的出现次数小于其他数字的最小出现次数，则输出一个 $1$ 后接 $c_0 + 1$ 个 $0$；否则，输出 $c_i + 1$ 个 $i$，其中 $i$ 是出现次数最少的数字。

### 评分较高的题解
#### 1. 作者：Cappuccino_mjj (赞：1)
**星级：4**  
**关键亮点：** 代码简洁，思路清晰，特判处理得当。  
**代码核心思想：** 找到 $1$ 到 $9$ 中出现次数最少的数字，根据 $0$ 的出现次数进行特判。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a[15];
int main()
{
    cin>>t;
    while(t--)
    {
        int minn=0x3f3f3f3f,id;
        cin>>a[0];
        for(int i=1;i<=9;i++)
        {
            cin>>a[i];
            if(a[i]<minn)
                minn=a[i],id=i;
        }
        if(a[0]<minn)
        {
            cout<<1;
            for(int i=1;i<=a[0]+1;i++)
                cout<<0;
            cout<<endl;
        }
        else
        {
            for(int i=1;i<=minn+1;i++)
                cout<<id;
            cout<<endl;
        }
    }
}
```

#### 2. 作者：_Sonnet (赞：1)
**星级：4**  
**关键亮点：** 代码简洁，思路清晰，特判处理得当。  
**代码核心思想：** 找到 $1$ 到 $9$ 中出现次数最少的数字，根据 $0$ 的出现次数进行特判。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[15];
int minn=0x3f3f3f;
int id;
signed main(){
    int t;
    cin>>t;
    while(t--){
        cin>>a[0];
        minn=0x3f3f3f3f3f3f;
        for(int i=1;i<=9;i++){
            cin>>a[i];
            if(minn>a[i]){
                minn=a[i];
                id=i;
            }
        }
        if(minn==0) cout<<id<<endl;
        else if(a[0]<minn){
            cout<<1;
            for(int i=1;i<=a[0]+1;i++){
                cout<<0;
            }
            cout<<endl;
        }
        else{
            for(int i=1;i<=minn+1;i++){
                cout<<id;
            }
            cout<<endl;
        }
    }
    return 0;
}
```

#### 3. 作者：Wander_E (赞：0)
**星级：4**  
**关键亮点：** 代码简洁，思路清晰，特判处理得当。  
**代码核心思想：** 找到 $1$ 到 $9$ 中出现次数最少的数字，根据 $0$ 的出现次数进行特判。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;
int n;
int c[N];
int T;

signed main()
{
    cin >> T;
    while(T--)
    {
        for(int i = 0; i <= 9; i++) cin >> c[i];
        int minn = min_element(c + 1, c + 10) - c;
        if(c[minn] == 0) 
        {
            cout << minn << endl;
            continue;
        }
        else if(c[minn] > c[0])
        {
            cout << 1;
            for(int i = 1; i <= c[0] + 1; i++) cout << 0;
            cout << endl;
            continue;
        }
        for(int i = 1; i <= c[minn] + 1; i++) cout << minn;
        cout << endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **贪心策略**：通过找到出现次数最少的数字，确定无法组成的最小数字。
2. **特判处理**：当 $0$ 的出现次数小于其他数字的最小出现次数时，输出一个 $1$ 后接 $c_0 + 1$ 个 $0$。

### 可拓展之处
类似的问题可以扩展到其他进制或更复杂的数字组合问题，例如在不同进制下寻找无法组成的最小数字。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：50.85秒