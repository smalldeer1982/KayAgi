# 题目信息

# Flower City Fence

## 题目描述

Anya lives in the Flower City. By order of the city mayor, she has to build a fence for herself.

The fence consists of $ n $ planks, each with a height of $ a_i $ meters. According to the order, the heights of the planks must not increase. In other words, it is true that $ a_i \ge a_j $ for all $ i < j $ .

Anya became curious whether her fence is symmetrical with respect to the diagonal. In other words, will she get the same fence if she lays all the planks horizontally in the same order.

For example, for $ n = 5 $ , $ a = [5, 4, 3, 2, 1] $ , the fence is symmetrical. Because if all the planks are laid horizontally, the fence will be $ [5, 4, 3, 2, 1] $ , as shown in the diagram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/bee85e28c2f6c75c9cfffe7860d8e27020ca6057.png) On the left is the fence $ [5, 4, 3, 2, 1] $ , on the right is the same fence laid horizontally

But for $ n = 3 $ , $ a = [4, 2, 1] $ , the fence is not symmetrical. Because if all the planks are laid horizontally, the fence will be $ [3, 2, 1, 1] $ , as shown in the diagram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/61240a948afb884e3b78ad7f150c3256a48031f7.png) On the left is the fence $ [4, 2, 1] $ , on the right is the same fence laid horizontally

Help Anya and determine whether her fence is symmetrical.

## 说明/提示

In the first and second test cases of the example, the fence is symmetrical.

In the third test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [3, 2, 1, 1] $ .

In the fourth test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [1, 1] $ .

In the fifth and sixth test cases of the example, the fence is symmetrical.

In the seventh test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [2, 1, 1, 1, 1, 1] $ .

## 样例 #1

### 输入

```
7
5
5 4 3 2 1
3
3 1 1
3
4 2 1
1
2
5
5 3 3 1 1
5
5 5 5 3 3
2
6 1```

### 输出

```
YES
YES
NO
NO
YES
YES
NO```

# AI分析结果

### 题目内容（中文重写）
# 花城围栏

## 题目描述
安雅住在花城。根据市长的命令，她必须为自己建造一个围栏。

围栏由 $n$ 块木板组成，每块木板的高度为 $a_i$ 米。根据命令，木板的高度不能递增。换句话说，对于所有 $i < j$，都有 $a_i \ge a_j$ 成立。

安雅好奇她的围栏是否关于对角线对称。换句话说，如果她将所有木板按相同顺序水平放置，是否会得到相同的围栏？

例如，当 $n = 5$，$a = [5, 4, 3, 2, 1]$ 时，围栏是对称的。因为如果将所有木板水平放置，围栏将是 $[5, 4, 3, 2, 1]$，如图所示。

![图1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/bee85e28c2f6c75c9cfffe7860d8e27020ca6057.png) 左边是围栏 $[5, 4, 3, 2, 1]$，右边是同样的围栏水平放置后的样子

但是当 $n = 3$，$a = [4, 2, 1]$ 时，围栏是不对称的。因为如果将所有木板水平放置，围栏将是 $[3, 2, 1, 1]$，如图所示。

![图2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/61240a948afb884e3b78ad7f150c3256a48031f7.png) 左边是围栏 $[4, 2, 1]$，右边是同样的围栏水平放置后的样子

帮助安雅确定她的围栏是否对称。

## 说明/提示
在样例的第一和第二个测试用例中，围栏是对称的。

在样例的第三个测试用例中，围栏是不对称的。如果将木板水平放置，围栏将是 $[3, 2, 1, 1]$。

在样例的第四个测试用例中，围栏是不对称的。如果将木板水平放置，围栏将是 $[1, 1]$。

在样例的第五和第六个测试用例中，围栏是对称的。

在样例的第七个测试用例中，围栏是不对称的。如果将木板水平放置，围栏将是 $[2, 1, 1, 1, 1, 1]$。

## 样例 #1
### 输入
```
7
5
5 4 3 2 1
3
3 1 1
3
4 2 1
1
2
5
5 3 3 1 1
5
5 5 5 3 3
2
6 1
```
### 输出
```
YES
YES
NO
NO
YES
YES
NO
```

### 算法分类
差分

### 综合分析与结论
这些题解的核心思路都是判断围栏水平放置后是否与原围栏相同。不同题解采用了不同的实现方法，主要有以下几种：
1. **直接模拟**：逐列计算水平放置后每列的高度，与原围栏高度比较。
2. **差分维护**：利用差分记录每个木板水平放置后的贡献，再通过前缀和还原，与原围栏比较。
3. **二分查找**：排序后二分求出新数组的每个数，与原数组比较。
4. **树状数组**：用树状数组统计大于等于某个值的数的个数，与原数组比较。

难点在于如何高效地计算水平放置后每列的高度，大部分题解通过差分、前缀和等技巧优化了计算过程。

### 所选题解
- **One_JuRuo（5星）**
  - **关键亮点**：思路清晰，代码简洁。利用单调不升的性质，用一个变量 $j$ 记录最后一个 $a_j\ge i$ 的位置，避免了重复计算。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],j,flag;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n),j=n,flag=0;
        for(int i=1;i<=n;++i) scanf("%d",&a[i]);
        for(int i=1;i<=n;++i)
        {
            while(a[j]<i) --j;
            if(a[i]!=j){flag=1;break;}
        }
        if(flag) printf("NO\n");
        else printf("YES\n");
    }
}
```
- **lfxxx（4星）**
  - **关键亮点**：通过差分维护每个木板水平放置后的贡献，用 `map` 方便清空，处理了高度较大的情况。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int n;
map<int,int> a,b; 
void work(){
    a.clear(),b.clear();
    cin>>n;
    int mx=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];	
        mx=max(a[i],mx);
        b[1]++,b[a[i]+1]--; 
    }
    if(mx!=n){
        cout<<"NO\n";
        return ;
    }
    for(int i=1;i<=n;i++) b[i]+=b[i-1];
    for(int i=1;i<=n;i++){
        if(a[i]!=b[i]){
            cout<<"NO\n";
            return ;
        }
    }
    cout<<"YES\n";
}
int T;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--) work();
    return 0;
}
```
- **dyyzy（4星）**
  - **关键亮点**：利用差分优化区间加操作，处理了 $a_i$ 较大的情况，逻辑清晰。
  - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define int long long
const int N=2e5+10;
int a[N],b[N];
signed main(){
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        b[0]=0;
        bool res=true;
        for(int i=1;i<=n;++i) b[i]=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(a[i]>200000) res=false;
            if(!res) continue;
            b[1]++;b[a[i]+1]--;
        }
        if(res){
            for(int i=1;i<=n;++i) b[i]+=b[i-1];
            for(int i=1;i<=n;++i) if(b[i]!=a[i]) res=false;
        }
        if(res) cout<<"YES\n";
        else cout<<"NO\n";
    }
}
```

### 最优关键思路或技巧
- **差分优化**：利用差分记录每个木板水平放置后的贡献，将区间加操作的时间复杂度从 $O(n)$ 优化到 $O(1)$，再通过前缀和还原，总时间复杂度为 $O(n)$。
- **利用单调性**：如 One_JuRuo 的题解，利用数组单调不升的性质，用一个变量记录最后一个满足条件的位置，避免了重复计算。

### 拓展思路
同类型题或类似算法套路：
- 涉及区间修改和查询的问题，可考虑使用差分或线段树优化。
- 对于对称判断问题，可通过模拟对称变换后的结果，与原结果进行比较。

### 推荐题目
1. [P3397 地毯](https://www.luogu.com.cn/problem/P3397)：区间修改问题，可使用差分解决。
2. [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)：同样是区间修改问题，差分的典型应用。
3. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：结合二分和差分的题目，有一定的综合性。

### 个人心得摘录与总结
- **Aisaka_Taiga**：提到半夜脑子抽了写了个麻烦的做法，提醒我们在解题时要保持清醒的头脑，选择更优的解法。在做题时应避免在状态不佳时强行解题，多思考不同的思路，选择简洁高效的方法。

---
处理用时：54.63秒