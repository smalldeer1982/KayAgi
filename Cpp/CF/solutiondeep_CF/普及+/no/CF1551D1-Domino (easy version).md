# 题目信息

# Domino (easy version)

## 题目描述

The only difference between this problem and D2 is that you don't have to provide the way to construct the answer in this problem, but you have to do it in D2.

There's a table of $ n \times m $ cells ( $ n $ rows and $ m $ columns). The value of $ n \cdot m $ is even.

A domino is a figure that consists of two cells having a common side. It may be horizontal (one of the cells is to the right of the other) or vertical (one of the cells is above the other).

You need to find out whether it is possible to place $ \frac{nm}{2} $ dominoes on the table so that exactly $ k $ of them are horizontal and all the other dominoes are vertical. The dominoes cannot overlap and must fill the whole table.

## 样例 #1

### 输入

```
8
4 4 2
2 3 0
3 2 3
1 2 0
2 4 2
5 2 2
2 17 16
2 1 1```

### 输出

```
YES
YES
YES
NO
YES
NO
YES
NO```

# AI分析结果

### 题目内容（中文重写）
# 多米诺骨牌（简单版本）

## 题目描述
本题与 D2 题的唯一区别在于，本题不需要你给出构造答案的方法，但在 D2 题中需要。

有一个 $n \times m$ 个单元格的表格（$n$ 行 $m$ 列）。$n \cdot m$ 的值为偶数。

多米诺骨牌是由两个有公共边的单元格组成的图形。它可以是水平的（其中一个单元格在另一个的右侧）或垂直的（其中一个单元格在另一个的上方）。

你需要判断是否可以在表格上放置 $\frac{nm}{2}$ 个多米诺骨牌，使得其中恰好有 $k$ 个是水平的，而其他所有的多米诺骨牌都是垂直的。多米诺骨牌不能重叠，并且必须填满整个表格。

## 样例 #1

### 输入
```
8
4 4 2
2 3 0
3 2 3
1 2 0
2 4 2
5 2 2
2 17 16
2 1```
### 输出
```
YES
YES
YES
NO
YES
NO
YES
NO```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是对 $n$ 和 $m$ 的奇偶性进行分类讨论，以此判断是否能按照要求放置多米诺骨牌。
- **思路**：由于 $n \times m$ 为偶数，根据 $n$ 和 $m$ 的奇偶性组合分情况讨论，利用多米诺骨牌的放置特性（如两个水平或垂直的骨牌可填满 $2\times2$ 方格）来判断能否满足恰好 $k$ 个水平骨牌且填满表格的条件。
- **算法要点**：重点在于对不同奇偶性情况的分类处理，通过计算和判断骨牌数量的奇偶性、上下界等条件来得出结论。
- **解决难点**：关键在于如何将不同奇偶性的矩阵转化为可处理的情况（如将奇数行或奇数列的矩阵转化为偶数行和偶数列的情况），并准确判断水平骨牌数量是否符合要求。

### 所选题解
- **UperFicial（4星）**：
    - **关键亮点**：思路清晰，对不同奇偶性情况的分析简洁明了，直接指出每种情况的判断要点。
    - **个人心得**：赛时 $\color{red}\texttt{WA}$ 掉了，提醒做题时要仔细分析各种情况。
- **断清秋（4星）**：
    - **关键亮点**：不仅思路清晰，还给出了完整的代码实现，代码注释详细，便于理解。
    - **个人心得**：无。
- **Ryan_Adam（4星）**：
    - **关键亮点**：结合图形进行分析，使思路更加直观，代码结构清晰，函数封装合理。
    - **个人心得**：无。

### 重点代码
#### UperFicial
思路：对 $n$ 和 $m$ 的奇偶性分情况讨论，根据不同情况判断 $k$ 是否满足条件。
```plaintext
- $n,m$ 都是偶数：要求 $k\equiv 0\bmod 2$。
- $n$ 是奇数且 $m$ 是偶数：判断第一行能否填满（需横着填 $\dfrac{m}{2}$ 个骨牌），余下的 $\left( k-\dfrac{m}{2}\right)$ 个骨牌是否为偶数。
- $n$ 是偶数且 $m$ 是奇数：将最左面的一列填满后转化为第一种情况，同时判断 $k$ 的上界为 $\dfrac{n\times(m-1)}{2}$。
- $n$ 是奇数且 $m$ 是奇数：不符合 $n\times m$ 为偶数的条件。
```

#### 断清秋
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
string s;
ll t,n,m,k,a[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		if(n%2==0&&m%2==0)
		{
			if(k%2==0)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
			continue;
		}
		if(n%2==1&&m%2==0)
		{
			if((k-m/2)%2==0&&k>=m/2)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
			continue;
		}
		if(n%2==0&&m%2==1)
		{
			if(k%2==0&&k<=(m-1)*n/2)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
			continue;
		}
	}
    back 0;
}
```
核心实现思想：通过 `while` 循环处理多组数据，根据 $n$ 和 $m$ 的奇偶性判断，再根据不同情况判断 $k$ 是否满足条件，输出相应结果。

#### Ryan_Adam
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
bool check(int a,int b,int c)
{
    if(c&1)return 0;
    if(c>(a/2)*(b/2)*2)return 0;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        if(!(n&1)&&!(m&1))
        {
            if(check(n,m,k))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
        else if((n&1)&&!(m&1))
        {
            if(k<m/2)
            {
                cout<<"NO"<<endl;
                continue;
            }
            k-=m/2;
            n--;
            if(check(n,m,k))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
        else if(!(n&1)&&(m&1))
        {
            m--;
            if(check(n,m,k))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
    }
    return 0;
}
```
核心实现思想：定义 `check` 函数判断 $k$ 是否满足条件（$k$ 为偶数且不超过上限），在 `main` 函数中根据 $n$ 和 $m$ 的奇偶性进行不同处理，调用 `check` 函数输出结果。

### 最优关键思路或技巧
对 $n$ 和 $m$ 的奇偶性进行分类讨论，利用多米诺骨牌的特性（如两个水平或垂直的骨牌可填满 $2\times2$ 方格）将复杂情况转化为简单情况，通过判断骨牌数量的奇偶性和上下界来确定是否满足条件。

### 可拓展之处
同类型题可能会改变骨牌的形状、表格的限制条件或增加更多的放置要求。类似算法套路是对问题的条件进行分类讨论，将复杂问题逐步转化为简单的子问题进行求解。

### 推荐洛谷题目
- P1003 铺地毯
- P1012 拼数
- P1047 校门外的树

### 个人心得摘录与总结
- **UperFicial**：赛时 $\color{red}\texttt{WA}$ 掉了，提醒我们在做题时要仔细分析各种情况，不能遗漏特殊情况，确保逻辑的完整性。 

---
处理用时：56.62秒