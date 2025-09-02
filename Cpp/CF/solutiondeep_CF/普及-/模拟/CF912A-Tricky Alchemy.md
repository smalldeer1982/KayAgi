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
# 巧妙的炼金术

## 题目描述
在寒假期间，对圣诞球的需求异常高涨。由于现在已经是2018年，炼金术的进步使得利用魔法水晶轻松高效地制造球成为可能。

Grisha需要获得一些黄色、绿色和蓝色的球。已知制造一个黄色球需要两颗黄色水晶，制造一个绿色球需要一颗黄色水晶和一颗蓝色水晶，而制造一个蓝色球，三颗蓝色水晶就足够了。

现在Grisha有A颗黄色水晶和B颗蓝色水晶。请找出他还需要获取多少颗额外的水晶才能制造出所需数量的球。

## 说明/提示
在第一个样例中，Grisha需要五颗黄色水晶和四颗蓝色水晶来制造两个黄色球、一个绿色球和一个蓝色球。为此，Grisha需要再获取两颗额外的水晶：一颗黄色水晶和一颗蓝色水晶。

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
- **思路**：各题解思路一致，均是先根据题目条件计算出制造所需球需要的黄水晶和蓝水晶数量，再分别与现有的黄水晶和蓝水晶数量作比较，最后将差值相加得到还需的水晶总数。同时，都考虑到了现有水晶数量可能多于所需数量的情况，避免出现负数结果。
- **算法要点**：核心是根据球的制作规则建立数学公式计算所需水晶数量，即黄水晶需求为`2 * 黄球数 + 绿球数`，蓝水晶需求为`绿球数 + 3 * 蓝球数`。
- **解决难点**：
    - **数据类型**：由于数据范围达到$10^9$，使用`int`会越界，需使用`long long`类型。
    - **差值处理**：当现有水晶数量多于所需数量时，差值应为0，避免对结果产生错误影响。

### 题解评分
- **SqrtSecond**：5星。思路清晰，有调试过程分享，代码有注释，可读性高。
- **Cloote**：4星。思路明确，对可能出现的错误有详细分析，使用快读优化输入。
- **_StarBird_**：4星。思路清晰，强调了注意事项，手写`max`函数。

### 所选题解
- **SqrtSecond（5星）**
    - **关键亮点**：思路清晰，有调试过程分享，代码有注释，可读性高。
    - **个人心得**：一开始没注意数据范围，使用`int`提交WA，后来发现应开`long long`。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,x,y,z;
long long needa,needb; // 需要水晶个数 
long long ans; // 答案 
long long k=0; // 存储一个longlong的0，因为后面max函数需要，否则会CE 
int main(){
    scanf("%lld%lld%lld%lld%lld",&a,&b,&x,&y,&z);
    needa=2*x+y; needb=y+3*z; // 算出需要多少水晶 
    printf("%lld",max(needa-a,k)+max(needb-b,k)); // max是为了防止a>needa或b>needb 
}
```
- **Cloote（4星）**
    - **关键亮点**：思路明确，对可能出现的错误有详细分析，使用快读优化输入。
    - **核心代码**：
```cpp
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
    ios::sync_with_stdio(false); // 可以让输入输出流的速度跟printf的速度一样
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
- **_StarBird_（4星）**
    - **关键亮点**：思路清晰，强调了注意事项，手写`max`函数。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long // 注意要开long long 
using namespace std;
int a,b,x,y,z; // 强迫症行为，输入数据是在int范围内的（ 
ll _max(ll u,ll v) // 手写max好习惯
{
    if (u>v) return u;
    return v;
}
int main()
{
    scanf("%d%d%d%d%d",&a,&b,&x,&y,&z);
    ll k=1;
    printf("%lld\n",_max((ll)(k*2*x+y-a),0)+_max((ll)(k*3*z+y-b),0)); // 一个是黄水晶，一个是蓝水晶，按题目中公式求出即可，为避免出现负数与0求max 
    return 0; // 完结撒草
}
```

### 最优关键思路或技巧
- **数据类型选择**：根据数据范围合理选择`long long`避免越界。
- **差值处理**：使用`max`函数或特判确保差值不为负数。

### 可拓展之处
同类型题可能会改变球的种类、水晶的种类以及制作规则，但解题思路类似，都是根据规则计算需求，再与现有资源比较。

### 推荐洛谷题目
- P1001 A+B Problem
- P1008 三连击
- P1012 拼数

---
处理用时：35.35秒