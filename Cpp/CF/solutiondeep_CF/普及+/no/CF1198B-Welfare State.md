# 题目信息

# Welfare State

## 题目描述

There is a country with $ n $ citizens. The $ i $ -th of them initially has $ a_{i} $ money. The government strictly controls the wealth of its citizens. Whenever a citizen makes a purchase or earns some money, they must send a receipt to the social services mentioning the amount of money they currently have.

Sometimes the government makes payouts to the poor: all citizens who have strictly less money than $ x $ are paid accordingly so that after the payout they have exactly $ x $ money. In this case the citizens don't send a receipt.

You know the initial wealth of every citizen and the log of all events: receipts and payouts. Restore the amount of money each citizen has after all events.

## 说明/提示

In the first example the balances change as follows: 1 2 3 4 $ \rightarrow $ 3 3 3 4 $ \rightarrow $ 3 2 3 4 $ \rightarrow $ 3 2 3 4

In the second example the balances change as follows: 3 50 2 1 10 $ \rightarrow $ 3 0 2 1 10 $ \rightarrow $ 8 8 8 8 10 $ \rightarrow $ 8 8 20 8 10

## 样例 #1

### 输入

```
4
1 2 3 4
3
2 3
1 2 2
2 1
```

### 输出

```
3 2 3 4 
```

## 样例 #2

### 输入

```
5
3 50 2 1 10
3
1 2 0
2 8
1 3 20
```

### 输出

```
8 8 20 8 10 
```

# AI分析结果

### 题目内容翻译
有一个国家，国家里有 $n$ 位公民。第 $i$ 位公民最初拥有 $a_{i}$ 金额的钱。政府严格控制公民的财富。每当一位公民进行消费或赚取一些钱时，他们必须向社会服务部门发送一份收据，注明他们当前拥有的金额。

有时政府会对穷人进行补贴：所有拥有的钱严格少于 $x$ 的公民都会得到相应的补贴，以便在补贴后他们恰好拥有 $x$ 金额的钱。在这种情况下，公民无需发送收据。

你知道每位公民的初始财富以及所有事件的记录：收据和补贴记录。请还原所有事件发生后每位公民拥有的金额。

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕模拟两种操作展开，即单点修改和将所有小于 $x$ 的数改为 $x$。不同题解采用了不同的数据结构和算法策略，包括直接模拟、线段树、分块等。
- **直接模拟类**：通过记录每个点最后一次单点修改的时间和区间操作的后缀最大值，比较得出最终结果，时间复杂度较低，代码实现相对简单。
- **线段树类**：将操作转化为线段树的单点修改和区间修改，利用懒标记优化时间复杂度，但代码实现复杂，细节较多。
- **分块类**：将数据分块，通过维护块的懒标记来处理操作，复杂度介于直接模拟和线段树之间。

### 所选题解
- **Bai_R_X（5星）**
    - **关键亮点**：思路清晰，准确抓住操作的特点，只记录每个点最后一次修改和最后且最大的 $x$ 值，通过比较得出结果，代码简洁高效。
- **skydogli（4星）**
    - **关键亮点**：对题意分析准确，明确指出不需要复杂数据结构，通过记录最后一次单点修改时间和预处理区间操作后缀最大值，实现简单且时间复杂度低。
- **Peter20122012（4星）**
    - **关键亮点**：详细阐述了操作的有效情况，通过记录操作时间和求后缀最大值来确定最终结果，代码规范，注释清晰。

### 重点代码
#### Bai_R_X 的代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],i,q,op,p,x,op1[200005],op2[200005],t[200005];
signed main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        op1[i]=-1;
    }
    cin>>q;
    for(i=1;i<=q;i++)
    {
        cin>>op;
        if(op==1)
        {
            cin>>p>>x;
            op1[p]=x;
            t[p]=i;
        }
        else
        {
            cin>>x;
            op2[i]=x;
        }
    }
    for(i=q;i>=0;i--)op2[i]=max(op2[i],op2[i+1]);
    for(i=1;i<=n;i++)
    {
        if(op1[i]>=0)a[i]=op1[i];
    }
    for(i=1;i<=n;i++)
    {
        if(a[i]<op2[t[i]])a[i]=op2[t[i]];
    }
    for(i=1;i<=n;i++)cout<<a[i]<<" ";
    return 0;
}
```
**核心实现思想**：记录每个点最后一次单点修改的值和时间，以及每次操作 2 的 $x$ 值，预处理操作 2 的后缀最大值，最后根据单点修改时间和后缀最大值更新每个点的值。

#### skydogli 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 1e9+1
#define MN 400005
int n,q,a[MN],cnt,ans,last[MN],Max[MN];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    scanf("%d",&q);
    for(int i=1;i<=q;++i){
        int op,loc,v;
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d",&loc,&v);
            a[loc]=v;
            last[loc]=i;//最后一次单点修改的时间
        }
        else{
            scanf("%d",&v);
            Max[i]=v;
        }
    }
    for(int i=q;i>=0;--i)Max[i]=max(Max[i],Max[i+1]);//求后缀中最大的
    for(int i=1;i<=n;++i)
        printf("%d ",max(a[i],Max[last[i]]));
    return 0;
}
```
**核心实现思想**：记录每个点最后一次单点修改的时间和每次操作 2 的 $x$ 值，求操作 2 的后缀最大值，最后比较每个点的值和对应后缀最大值，取较大值。

#### Peter20122012 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

const int maxn = 2e5 + 10;
const int maxq = 2e5 + 10;

int n;
int a[maxn];
int q;
int op, p, x;

int t1[maxn], op2[maxq];

int main () {
    scanf("%i", &n);
    FOR (1, n, i) {scanf("%i", &a[i]);}
    scanf("%i", &q);
    FOR (1, q, i) {
        scanf("%i", &op);
        if (op == 1) {
            scanf("%i%i", &p, &x);
            
            a[p] = x;
            t1[p] = i;
        }else {
            scanf("%i", &x);
            
            op2[i] = x;
        }
    }
    
    RFOR(0, q - 1, i) {op2[i] = MAX(op2[i], op2[i + 1]);}
    
    FOR (1, n, i) {printf("%i ", MAX(a[i], op2[t1[i]]));}
    printf("\n");
    return 0;
}
```
**核心实现思想**：记录每个点最后一次操作 1 的时间和每次操作 2 的 $x$ 值，求操作 2 的后缀最大值，最后比较每个点的值和对应后缀最大值，输出较大值。

### 最优关键思路或技巧
- 记录每个点最后一次单点修改的时间和操作 2 的后缀最大值，通过比较得出最终结果，避免了重复计算。
- 利用后缀最大值的特性，减少不必要的操作，优化时间复杂度。

### 拓展思路
同类型题目可能会有更多复杂的操作，如区间修改、区间查询等，可以继续使用线段树、分块等数据结构进行处理。类似算法套路包括维护前缀和、后缀和、差分等，用于处理数组的修改和查询问题。

### 推荐题目
- P3372 【模板】线段树 1
- P3368 【模板】树状数组 2
- P2801 教主的魔法

### 个人心得摘录与总结
- **toolong114514**：提到这题搬到模拟赛中有人调了 1.5h 的错解，并且指出用某些 C++ 语言版本提交会无法编译，实测用 C++20 提交不会出问题，同时提醒不开 O2 可能会 TLE，说明在实际做题中要注意语言版本和优化选项。
- **OIerZhao_1025**：分享了自己暴力 TLE 和 WA 的经历，总结出不能直接暴力，要节省操作 2 的时间，且操作 1 不能提前，要放在后面，强调了做题时要通过样例分析操作的先后顺序和优化方法。 

---
处理用时：60.99秒