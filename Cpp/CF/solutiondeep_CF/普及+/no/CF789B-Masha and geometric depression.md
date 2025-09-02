# 题目信息

# Masha and geometric depression

## 题目描述

Masha really loves algebra. On the last lesson, her strict teacher Dvastan gave she new exercise.

You are given geometric progression $ b $ defined by two integers $ b_{1} $ and $ q $ . Remind that a geometric progression is a sequence of integers $ b_{1},b_{2},b_{3},... $ , where for each $ i&gt;1 $ the respective term satisfies the condition $ b_{i}=b_{i-1}·q $ , where $ q $ is called the common ratio of the progression. Progressions in Uzhlyandia are unusual: both $ b_{1} $ and $ q $ can equal $ 0 $ . Also, Dvastan gave Masha $ m $ "bad" integers $ a_{1},a_{2},...,a_{m} $ , and an integer $ l $ .

Masha writes all progression terms one by one onto the board (including repetitive) while condition $ |b_{i}|<=l $ is satisfied ( $ |x| $ means absolute value of $ x $ ). There is an exception: if a term equals one of the "bad" integers, Masha skips it (doesn't write onto the board) and moves forward to the next term.

But the lesson is going to end soon, so Masha has to calculate how many integers will be written on the board. In order not to get into depression, Masha asked you for help: help her calculate how many numbers she will write, or print "inf" in case she needs to write infinitely many integers.

## 说明/提示

In the first sample case, Masha will write integers $ 3,12,24 $ . Progression term $ 6 $ will be skipped because it is a "bad" integer. Terms bigger than $ 24 $ won't be written because they exceed $ l $ by absolute value.

In the second case, Masha won't write any number because all terms are equal $ 123 $ and this is a "bad" integer.

In the third case, Masha will write infinitely integers $ 123 $ .

## 样例 #1

### 输入

```
3 2 30 4
6 14 25 48
```

### 输出

```
3```

## 样例 #2

### 输入

```
123 1 2143435 4
123 11 -5453 141245
```

### 输出

```
0```

## 样例 #3

### 输入

```
123 1 2143435 4
54343 -13 6 124
```

### 输出

```
inf```

# AI分析结果

### 题目内容
# Masha和几何沮丧

## 题目描述
Masha非常热爱代数。在上一节课上，她严厉的老师Dvastan给了她一道新练习题。

给定一个由两个整数$b_1$和$q$定义的等比数列$b$。提醒一下，等比数列是一个整数序列$b_1, b_2, b_3, \cdots$，其中对于每个$i > 1$，相应的项满足条件$b_i = b_{i - 1} \cdot q$，这里的$q$被称为该数列的公比。在乌兹兰迪亚（Uzhlyandia）的数列很不寻常：$b_1$和$q$都可以等于$0$。此外，Dvastan给了Masha $m$个“坏”整数$a_1, a_2, \cdots, a_m$，以及一个整数$l$。

Masha会逐个将数列项写在黑板上（包括重复的项），只要满足条件$|b_i| \leq l$（$|x|$表示$x$的绝对值）。但有一个例外：如果某一项等于其中一个“坏”整数，Masha就会跳过它（不写在黑板上），并继续写下一项。

但课程很快就要结束了，所以Masha必须计算会在黑板上写下多少个整数。为了不陷入沮丧，Masha向你求助：帮她计算她会写多少个数，或者如果她需要写无穷多个整数，则输出“inf”。

## 说明/提示
在第一个样例中，Masha会写下整数$3, 12, 24$。数列项$6$会被跳过，因为它是一个“坏”整数。绝对值大于$24$的项不会被写，因为它们超过了$l$。

在第二个样例中，Masha不会写任何数，因为所有项都等于$123$，而$123$是一个“坏”整数。

在第三个样例中，Masha会写下无穷多个整数$123$。

## 样例 #1
### 输入
```
3 2 30 4
6 14 25 48
```
### 输出
```
3```

## 样例 #2
### 输入
```
123 1 2143435 4
123 11 -5453 141245
```
### 输出
```
0```

## 样例 #3
### 输入
```
123 1 2143435 4
54343 -13 6 124
```
### 输出
```
inf```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是先对特殊情况进行特判，再处理一般情况。特殊情况主要包括公比$q$为$0$、$1$、$-1$以及首项$b_1$为$0$的情况。在这些特殊情况下，数列呈现出简单的规律，可直接得出答案。对于一般情况，即$q$不为上述特殊值且$b_1$不为$0$时，通过循环枚举数列项，判断该项是否在“坏”整数集合中且绝对值不超过$l$，来统计可写出的项数。不同题解在实现细节上有所差异，如使用`map`或`set`来存储“坏”整数以进行快速查找，以及对特殊情况的判断顺序和方式等。

### 所选的题解
- **作者：_6_awa (5星)**
    - **关键亮点**：思路清晰，对特殊情况的分析全面且有条理，代码简洁明了，直接根据不同特殊情况得出结果，一般情况通过简单循环实现。
    - **重点代码**：
```cpp
#include <iostream>
#include <cmath>
#include <map>
#define int long long
using namespace std; 
map<int,int>mp;
int b1,q,l,m,x,cnt;
signed main()
{
    cin >> b1 >> q >> l >> m;
    for(int i = 1;i <= m;i ++)cin >> x,mp[x] = 1;
    if(l < abs(b1))//直接特判
    {
        cout << 0;
        return 0;
    }
    if(q == 1)
    {
        if(mp[b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    if(q == -1)
    {
        if(mp[b1] && mp[-b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    if(q == 0)
    {
        if(mp[0] &&!mp[b1])cout << 1;
        else if(mp[0] && mp[b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    if(b1 == 0)
    {
        if(mp[b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    while(abs(b1) <= l)//正常操作
    {
        if(!mp[b1])cnt ++;
        b1 *= q;
    }
    cout << cnt;
}
```
    - **核心实现思想**：先读入数据并将“坏”整数存入`map`。然后依次判断特殊情况，直接输出结果。对于一般情况，通过`while`循环，在数列项绝对值不超过$l$时，判断该项是否在“坏”整数集合中，不在则计数。
- **作者：_Life_ (4星)**
    - **关键亮点**：提出一种只需一次特判的思路，通过循环枚举1000000次来处理大部分情况，利用`set`存储“坏”整数实现高效判重。
    - **重点代码**：
```cpp
#include<set>
#include<cmath>
#include<cstdio>
using namespace std;
#define int long long
int b1,q,l,m;
int ans,cnt;
set <int> a;
signed main()
{
	scanf("%lld %lld %lld %lld",&b1,&q,&l,&m);
	for(int i=0;i<m;i++)
	{
		int x;
		scanf("%lld",&x);
		a.insert(x);//把A中元素扔进set
	}
	int b2=b1;
	while(abs(b2)<=l)
	{
		cnt++;//统计当前循环枚举的次数
		if(a.find(b2)==a.end())//A中没有找到B[i]
			ans++;
		b2*=q;//枚举数列的下一项
		if(cnt==1000000)//如果循环枚举了1000000次
		{
			if(ans!=0&&ans!=1)//特判
				ans=-1;//如果写下的元素个数有无限多个 则标为-1
			break;
		}
	}
	if(ans==-1)
		printf("inf");
	else
		printf("%lld",ans);
}
```
    - **核心实现思想**：读入数据后将“坏”整数存入`set`。通过`while`循环枚举数列项，在项绝对值不超$l$时，判断是否在“坏”整数集合中，不在则计数。当循环次数达到1000000时，根据已计数情况判断是否为无穷。
- **作者：lukelin (4星)**
    - **关键亮点**：先对$q$为$0$、$1$、$-1$以及$b_1$为$0$的情况进行特判，之后对一般情况使用`set`暴力模拟，代码结构清晰。
    - **重点代码**：
```cpp
#include <cstdio>
#include <cmath>
#include <set>
#define ll long long

using namespace std;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch!= '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

set<ll> st;

int main(){
    ll b = read(), q = read(), l = read(), m = read();
    for (int i = 1; i <= m; ++i)
        st.insert(read());
    if (q == 0){
        if (st.find(0)!= st.end() || (l < 0)){
            if (st.find(b)!= st.end() || (abs(b) > l))
                printf("0");
            else
                printf("1");
        }
        else if (abs(b) > l)
            printf("0");
        else
            printf("inf");
        return 0;
    }
    else if (q == 1){
        if ((abs(b) > l) || st.find(b)!= st.end())
            printf("0");
        else
            printf("inf");
        return 0;
    }
    else if (q == -1){
        if (abs(b) > l){
            printf("0");
            return 0;
        }
        if (st.find(b) == st.end()){
            printf("inf");
            return 0;
        }
        if (st.find(-b) == st.end()){
            printf("inf");
            return 0;
        }
        printf("0");
        return 0;
    }
    else if (b == 0){
        if (st.find(0)!= st.end() || (l < 0))
            printf("0");
        else
            printf("inf");
        return 0;
    }
    else{
        int cnt = 0;
        for (ll i = b; abs(i) <= l; i *= q){
            if (st.find(i) == st.end())
                ++cnt;
        }
        printf("%d", cnt);
    }
    return 0;
}
```
    - **核心实现思想**：读入数据并将“坏”整数存入`set`。针对不同特殊情况分别判断输出结果。一般情况通过`for`循环枚举数列项，判断是否在“坏”整数集合中，不在则计数。

### 最优关键思路或技巧
对特殊情况（$q$为$0$、$1$、$-1$以及$b_1$为$0$）进行全面且细致的分类讨论，能够极大简化问题的求解过程。同时，使用`map`或`set`数据结构存储“坏”整数，利用其快速查找特性优化判断过程。

### 拓展思路
此类题目可拓展到其他数列相关问题，如等差数列类似条件判断，或等比数列在更复杂限制条件下的项数统计。解题时同样需先分析数列特性，找出特殊情况并分类讨论，再结合合适的数据结构优化实现。

### 相似知识点洛谷题目
- [P1990 覆盖墙壁](https://www.luogu.com.cn/problem/P1990)：涉及递推与数学规律分析。
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过递归或递推解决数字规律问题。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合数学知识（斐波那契数列性质）与算法实现。

### 个人心得摘录与总结
无。 

---
处理用时：88.33秒