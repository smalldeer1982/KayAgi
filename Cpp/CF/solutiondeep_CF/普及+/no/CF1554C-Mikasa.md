# 题目信息

# Mikasa

## 题目描述

给出两个整数 $n$ 和 $m$。请你求出序列 $n \oplus 0,n \oplus 1,\dots,n \oplus m$ 的 $\operatorname{MEX}$。此处 $\oplus$ 是位运算[异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96)。

一个序列的 $\operatorname{MEX}$ 定义为序列中没有出现的最小的非负整数。例如：$\operatorname{MEX}(0,1,2,4)=3$ 和 $\operatorname{MEX}(1,2021)=0$。

## 说明/提示

$1 \leq t \leq 3\times10^4$

$0 \leq n,m \leq 1\times10^9$

在样例的第一组数据中，序列为 $3 \oplus 0, 3 \oplus 1, 3 \oplus 2, 3 \oplus 3, 3 \oplus 4, 3 \oplus 5$ 即 $3, 2, 1, 0, 7, 6$。其中没有出现的最小的非负整数是 $4$，则序列的 $\operatorname{MEX}$ 为 $4$。

在样例的第二组数据中，序列为 $4 \oplus 0,4 \oplus 1,4 \oplus 2,4 \oplus 3,4 \oplus 4,4 \oplus 5,4 \oplus 6$ 即 $4, 5, 6, 7, 0, 1, 2$。其中没有出现的最小的非负整数是 $3$，则序列的 $\operatorname{MEX}$ 为 $3$。

在样例的第三组数据中，序列为 $3 \oplus 0,3 \oplus 1,3 \oplus 2 $ 即 $3, 2, 1$。其中没有出现的最小的非负整数是 $0$，则序列的 $\operatorname{MEX}$ 为 $0$。

## 样例 #1

### 输入

```
5
3 5
4 6
3 2
69 696
123456 654321```

### 输出

```
4
3
0
640
530866```

# AI分析结果

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是将原问题转化为找出最小的非负整数 $k$，使得 $n \oplus k \ge m + 1$，然后通过按位构造的方法来求解。具体来说，就是从二进制的高位到低位逐位分析 $n$ 和 $m + 1$ 的每一位，根据不同情况确定 $k$ 的对应位。

各题解的思路和算法要点基本一致，主要区别在于代码实现的细节和一些边界条件的处理。部分题解还对特殊情况（如 $n > m$）进行了特判，以提高代码的效率。

解决的难点在于如何根据 $n$ 和 $m + 1$ 的二进制位情况，合理地构造出满足条件的最小 $k$。不同题解在处理这个问题时，都采用了分类讨论的方法，根据 $n$ 和 $m + 1$ 对应位的取值，确定 $k$ 对应位的值。

### 所选题解
- **作者：Blunt_Feeling (赞：21)，4星**
  - 关键亮点：思路清晰，对按位构造的过程进行了详细的分类讨论，代码实现也比较规范，有明确的注释。
  - 核心代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
int T,n,m,k;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        bool flag=false;
        k=0; m++; //别忘了++
        Rep(i,31,0)
        {
            if(!flag&&(n&(1<<i)||m&(1<<i))) flag=true; //标记表示遍历到了有效位
            if(!flag) continue;
            if(n&(1<<i))
            {
                if(m&(1<<i)) k<<=1; //左移一位表示后面添上一个0
                else
                {
                    Rep(j,i,0) k<<=1; //后面几位都是0
                    break; //可以输出了
                }
            }
            else
            {
                if(m&(1<<i)) k=(k<<1)|1; //先左移，再或一下，表示后面添上一个1
                else k<<=1; //左移一位表示后面添上一个0
            }
        }
        cout<<k<<endl;
    }
    return 0;
}
```
  - 核心实现思想：从二进制的最高位开始遍历，根据 $n$ 和 $m + 1$ 对应位的取值，按照四种情况进行分类讨论，确定 $k$ 对应位的值。当遇到 $n$ 对应位为 $1$，$m + 1$ 对应位为 $0$ 的情况时，后面的位都置为 $0$ 并跳出循环。

- **作者：_Fontainebleau_ (赞：8)，4星**
  - 关键亮点：思路简洁明了，直接列出四种情况，代码实现也比较简洁。
  - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int tc,n,p;
long long ans;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int main()
{
    tc=read();
    while(tc--)
    {
        n=read(),p=read()+1;
        ans=0;
        for(int i=30;i>=0;i--)
        {
            if((n>>i &1)==1&&(p>>i &1)==0)    break;
            if((n>>i &1)==0&&(p>>i &1)==1)    ans|=1<<i;
        }
        printf("%lld\n",ans);	
    }
    return 0;
}
```
  - 核心实现思想：从二进制的最高位开始遍历，当遇到 $n$ 对应位为 $1$，$m + 1$ 对应位为 $0$ 的情况时，直接跳出循环；当遇到 $n$ 对应位为 $0$，$m + 1$ 对应位为 $1$ 的情况时，将 $ans$ 的对应位设为 $1$。

- **作者：123zbk (赞：1)，4星**
  - 关键亮点：思路清晰，对问题的转化和分类讨论都有明确的阐述，代码实现简洁。
  - 核心代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,ans;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&m);
        m++;
        ans=0;
        for(int i=30;i>=0;i--)
        {
            if((n>>i&1)==0&&(m>>i&1)==1)
            {
                ans|=(1<<i);
            }
            if((n>>i&1)==1&&(m>>i&1)==0)
            {
                break;
            }
        }	
        printf("%lld\n",ans);
    }	
    return 0;
} 
```
  - 核心实现思想：从二进制的最高位开始遍历，当遇到 $n$ 对应位为 $0$，$m + 1$ 对应位为 $1$ 的情况时，将 $ans$ 的对应位设为 $1$；当遇到 $n$ 对应位为 $1$，$m + 1$ 对应位为 $0$ 的情况时，直接跳出循环。

### 最优关键思路或技巧
- **问题转化**：利用异或的性质 $a \oplus b = c \Rightarrow a \oplus c = b$，将原问题转化为找出最小的非负整数 $k$，使得 $n \oplus k \ge m + 1$，简化了问题的求解。
- **按位构造**：从二进制的高位到低位逐位分析 $n$ 和 $m + 1$ 的每一位，根据不同情况确定 $k$ 的对应位，保证 $k$ 是满足条件的最小非负整数。

### 拓展思路
同类型题或类似算法套路通常涉及位运算和贪心策略，例如：
- 给定一些数，通过位运算和贪心的方法构造出满足特定条件的数。
- 利用位运算的性质解决一些与二进制相关的问题，如判断某个数是否在某个集合中。

### 推荐题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及队列和滑动窗口的操作，与位运算结合可以解决一些更复杂的问题。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：可以通过位运算和模拟的方法解决，锻炼对问题的分析和处理能力。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：需要运用贪心和模拟的思想，结合位运算可以优化算法。

### 个人心得摘录与总结
- **作者：wuzihe**：提到这是自己的第一篇题解，希望大佬轻喷，在解题过程中详细推导了异或的性质和问题的转化过程，体现了对问题的深入思考。
总结：对于初学者来说，详细推导问题的转化过程有助于更好地理解问题和掌握解题方法。在写题解时，要注重思路的清晰和逻辑的严谨。

---
处理用时：52.40秒