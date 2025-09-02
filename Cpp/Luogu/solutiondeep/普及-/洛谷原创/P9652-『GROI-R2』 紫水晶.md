# 题目信息

# 『GROI-R2』 紫水晶

## 题目描述

爱丽丝不曾忘记过她曾经存在于纸牌的世界。

于是魔法让她的手里出现了一些牌，同时魔法也让坦尼尔手里出现了一些牌，而且每张牌上都写着一个正整数——尽管他们如今所处的，是玻璃王国的世界中。

牌张很快一消而散，而他们也准备启程。爱丽丝只记住了每相邻两张牌的**最大公约数之和**，坦尼尔只记住了每相邻两张牌的**最小公倍数之和**。

你还在这个宫殿里，你想重现当时的牌张。

**形式化题面**

给定 $q$ 次询问，每次询问为以下两种之一：

- ``1 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$。

- ``2 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$。

且对于任意输出的 $a_i$ 不应超出 C++ 语言中 ``int`` 的存储范围。

其中 $\gcd$ 和 $\operatorname{lcm}$ 分别为最大公约数和最小公倍数，如有多解，输出任意一个即可。如果无解，输出 ``-1``。

## 说明/提示

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $\sum n\le$ | $x\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $5$ | $10$ | | $10$ |
| $2$ | $50$ | $200$ | | $20$ |
| $3$ | $5\times 10^5$ | $2^{31}-1$ | $\text{A}$ | $15$ |
| $4$ | $5\times 10^5$ | $2^{31}-1$ | $\text{B}$ | $15$ |
| $5$ | $5\times 10^5$ | $2^{31}-1$ | | $40$ |

特殊性质 $\text{A}$：保证对于任意询问满足 $op=1$。

特殊性质 $\text{B}$：保证对于任意询问满足 $op=2$。

对于 $100\%$ 的数据满足 $2\le n\le 5\times 10^5$，$2\le \sum n\le 5\times 10^5$，$1\le x \le 2^{31}-1$，$op\in\{1,2\}$。


## 样例 #1

### 输入

```
5
1 5 4
2 3 8
1 5 10
2 6 34
1 3 1```

### 输出

```
1 1 1 1 1
2 2 3
1 1 1 7 7
1 1 4 5 1 4
-1```

# AI分析结果

• 综合分析与结论：这些题解思路相近，均利用1与其他数的最大公约数和最小公倍数的特性进行构造。对于op = 1，构造n - 2个1和2个x - n + 2；对于op = 2，构造n - 1个1和1个x - n + 2。同时都考虑到x < n - 1时无解的情况。各题解在思路清晰度、代码可读性上有所差异。
• 所选的题解：
  - 作者：RJSPZ (赞：4)，星级：4星
    - 关键亮点：思路清晰简洁，直接阐述两种构造情况，代码实现简洁明了。
    - 重点代码：
```cpp
#include<cstdio>
using namespace std;
const int N=5e5+7;
int T,a[N];
signed main(){
    scanf("%d",&T);
    while(T--){
        int op,n,x;
        scanf("%d%d%d",&op,&n,&x);
        if(op==1){
            int num=x-n+2;
            if(num<=0){
                putchar('-'),putchar('1');
                goto print;
            }
            for(int i=1;i<=n-2;i++){
                putchar('1'),putchar(' ');
            }
            for(int i=n-1;i<=n;i++){
                printf("%d ",num);
            }
        }
        else{
            int num=x-n+2;
            if(num<=0){
                putchar('-'),putchar('1');
                goto print;
            }
            for(int i=1;i<=n-1;i++){
                putchar('1'),putchar(' ');
            }
            printf("%d",num);
        }
print:
        putchar('\n');
    }
    return 0;
}
```
    - 核心实现思想：根据op值判断是求最大公约数和还是最小公倍数和，分别按构造思路输出序列，若构造值不满足正整数条件则输出 - 1。
  - 作者：_O_v_O_ (赞：1)，星级：4星
    - 关键亮点：先放结论，再进行证明，逻辑清晰。
    - 重点代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int T,op,n,x;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin>>T;
    while(T--){
        cin>>op>>n>>x;
        if(x<n-1){
            puts("-1");
            continue;
        }
        if(op==1){
            for(int i=1;i<n-1;i++){
                cout<<1<<' ';
            }
            cout<<x-n+2<<' '<<x-n+2<<endl;
        }
        if(op==2){
            for(int i=1;i<n;i++){
                cout<<1<<' ';
            }
            cout<<x-n+2<<endl;
        }
    }
    return 0;
}
```
    - 核心实现思想：先判断是否有解，再根据op值按构造方案输出对应序列。
  - 作者：lsj2009 (赞：1)，星级：4星
    - 关键亮点：详细阐述构造思路的来源，从特殊数字1出发考虑，逻辑连贯。
    - 重点代码：
```cpp
#include<bits/stdc++.h>
//#define int long long
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;

signed main() {
    int q;
    scanf("%d",&q);
    while(q--) {
        int op,n,x;
        scanf("%d%d%d",&op,&n,&x);
        if(x<n-1)
            puts("-1");
        else if(op==1) {
            rep(i,1,n-2)
                printf("%d ",1);
            printf("%d %d\n",x-n+2,x-n+2);
        } else {
            rep(i,1,n-1)
                printf("%d ",1);
            printf("%d\n",x-n+2);
        }
    }
    return 0;
}
```
    - 核心实现思想：通过判断op值，依据构造思路，在有解情况下输出符合条件的序列。
• 最优关键思路或技巧：利用1与其他正整数的最大公约数和最小公倍数的特殊性质，通过构造大部分为1的序列，再根据和的值确定剩余位置的数，从而满足题目要求。
• 可拓展之处：同类型题可涉及更多数论函数的构造，类似算法套路是寻找特殊数字或规律，简化问题构造。
• 相似知识点洛谷题目：
  - P1029 最大公约数和最小公倍数问题
  - P1572 计算分数的最大公约数和最小公倍数
  - P2602 数字计数问题
• 个人心得：无。 

---
处理用时：27.28秒