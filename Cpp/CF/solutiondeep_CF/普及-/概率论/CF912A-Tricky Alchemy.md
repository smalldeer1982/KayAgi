# 题目信息

# Tricky Alchemy

## 题目描述

During the winter holidays, the demand for Christmas balls is exceptionally high. Since it's already $ 2018 $ , the advances in alchemy allow easy and efficient ball creation by utilizing magic crystals.

Grisha needs to obtain some yellow, green and blue balls. It's known that to produce a yellow ball one needs two yellow crystals, green — one yellow and one blue, and for a blue ball, three blue crystals are enough.

Right now there are $ A $ yellow and $ B $ blue crystals in Grisha's disposal. Find out how many additional crystals he should acquire in order to produce the required number of balls.

## 说明/提示

In the first sample case, Grisha needs five yellow and four blue crystals to create two yellow balls, one green ball, and one blue ball. To do that, Grisha needs to obtain two additional crystals: one yellow and one blue.

## 样例 #1

### 输入

```
4 3
2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 9
1 1 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
12345678 87654321
43043751 1000000000 53798715
```

### 输出

```
2147483648
```

# AI分析结果

### 题目中文重写
# 棘手的炼金术

## 题目描述
在寒假期间，对圣诞球的需求格外高。由于现在已经是 2018 年，炼金术的进步使得利用魔法水晶轻松高效地制作球成为可能。

格里沙需要获得一些黄色、绿色和蓝色的球。已知制作一个黄色球需要两颗黄色水晶，制作一个绿色球需要一颗黄色水晶和一颗蓝色水晶，而制作一个蓝色球，三颗蓝色水晶就足够了。

现在格里沙有 $A$ 颗黄色水晶和 $B$ 颗蓝色水晶。请找出他还需要获取多少颗额外的水晶才能制作出所需数量的球。

## 说明/提示
在第一个样例中，格里沙需要五颗黄色水晶和四颗蓝色水晶来制作两个黄色球、一个绿色球和一个蓝色球。为此，格里沙需要再获取两颗额外的水晶：一颗黄色水晶和一颗蓝色水晶。

## 样例 #1
### 输入
```
4 3
2 1 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3 9
1 1 3
```
### 输出
```
1
```

## 样例 #3
### 输入
```
12345678 87654321
43043751 1000000000 53798715
```
### 输出
```
2147483648
```

### 综合分析与结论
这些题解的整体思路都是先根据题目给定的制作规则，计算出制作所需数量的黄球、绿球和蓝球分别需要的黄水晶和蓝水晶的数量，然后将其与现有的黄水晶和蓝水晶数量作比较，得出还需要的水晶数量。

#### 算法要点
1. **计算所需水晶数量**：根据制作规则，计算出制作目标数量的球所需的黄水晶数量为 `2 * 黄球数量 + 绿球数量`，蓝水晶数量为 `3 * 蓝球数量 + 绿球数量`。
2. **处理剩余情况**：如果现有的水晶数量比所需的多，那么还需要的水晶数量为 0。

#### 解决难点
1. **数据范围**：由于数据范围达到了 $10^9$，使用 `int` 类型会导致越界，因此需要使用 `long long` 类型。
2. **负数处理**：在计算还需要的水晶数量时，如果现有水晶数量比所需的多，会出现负数，需要进行特殊处理，将其置为 0。

### 通用建议与扩展思路
- 对于涉及数据范围较大的题目，要提前考虑数据类型的选择，避免因数据溢出导致错误。
- 在处理差值时，要注意可能出现负数的情况，需要进行特判。

### 相似知识点洛谷题目推荐
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：基础的输入输出和简单计算，可用于熟悉基本操作。
2. [P1421 小玉买文具](https://www.luogu.com.cn/problem/P1421)：涉及简单的数学计算和数据类型转换。
3. [P1035 级数求和](https://www.luogu.com.cn/problem/P1035)：需要注意数据类型和循环的使用。

### 个人心得摘录与总结
- **SqrtSecond**：一开始没注意到第三个样例，使用 `int` 类型导致 WA，后来发现需要开 `long long` 才能 AC。总结是要注意数据范围，避免因数据类型问题出错。
- **Cloote**：提交代码后 WA 了，原因是现有的水晶数量可能比目标数大，相减会出现负数，需要进行特判。提醒在处理差值时要考虑负数情况。
- **Achiles**：使用 `int` 类型变量在测试样例 3 时会输出错误结果，因为 $10^9$ 大小的数据范围用 `int` 类型会越界，所以要使用 `long long`。强调了数据类型选择的重要性。

### 重点代码及核心实现思想
以下是不同题解的重点代码及核心实现思想：
```cpp
// SqrtSecond 的 AC 代码
#include<bits/stdc++.h>
using namespace std;
long long a,b,x,y,z;
long long needa,needb; // 需要水晶个数 
long long ans; // 答案 
long long k=0; // 存储一个 long long 的 0，因为后面 max 函数需要，否则会 CE 
int main(){
    scanf("%lld%lld%lld%lld%lld",&a,&b,&x,&y,&z);
    needa=2*x+y; needb=y+3*z; // 算出需要多少水晶 
    printf("%lld",max(needa-a,k)+max(needb-b,k)); // max 是为了防止 a>needa 或 b>needb 
}
```
核心思想：先计算出需要的黄水晶和蓝水晶数量，然后用 `max` 函数确保差值不为负数，最后将两个差值相加得到结果。

```cpp
// Cloote 的代码
#include<bits/stdc++.h>
using namespace std;
long long a,b,x,y,z,ansa,ansb;
template<typename T>void read(T& x) // 快读不用管
{
    x=0; char c=getchar(); bool f=0;
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-') f=1,c=getchar();
    while(isdigit(c)) x=x*10+c-'0',c=getchar();
    if(f) x=-x;
}
int main()
{
    ios::sync_with_stdio(false); // 可以让输入输出流的速度跟 printf 的速度一样
    read(a); read(b); read(x); read(y); read(z);
    ansa=x*2+y; // 目标数
    ansb=y+z*3;        
    ansa-=a;
    ansb-=b;
    if(ansa<0) ansa=0; // 特判
    if(ansb<0) ansb=0;
    cout<<ansa+ansb;
    return 0; // 完结撒草
}
```
核心思想：先计算出需要的黄水晶和蓝水晶数量，然后减去现有的数量，对差值进行特判，如果为负数则置为 0，最后将两个差值相加得到结果。

```cpp
// Achiles 的代码
#include<bits/stdc++.h>
using namespace std;
long long yelcry,blucry; // 黄水晶和蓝水晶的个数
long long yelbal,grebal,blubal; // 黄水晶球，绿水晶球和蓝水晶的个数
long long ans; // 额外需要水晶个数
int main()
{
    cin>>yelcry>>blucry>>yelbal>>grebal>>blubal; // 输入
    if(yelcry<yelbal*2+grebal) ans+=yelbal*2+grebal-yelcry; // 如果 现有黄水晶个数 小于 需要黄水晶个数，就加上差价
    if(blucry<grebal+blubal*3) ans+=grebal+blubal*3-blucry; // 如果 现有蓝水晶个数 小于 需要蓝水晶个数，就加上差价
    cout<<ans; // 输出
    return 0;
}
```
核心思想：通过条件判断，如果现有水晶数量小于需要的数量，则将差值累加到结果中，最后输出结果。

---
处理用时：37.47秒