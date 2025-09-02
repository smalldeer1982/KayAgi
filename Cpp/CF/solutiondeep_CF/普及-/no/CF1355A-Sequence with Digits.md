# 题目信息

# Sequence with Digits

## 题目描述

Let's define the following recurrence: $ $$$a_{n+1} = a_{n} +       minDigit(a_{n}) \cdot maxDigit(a_{n}). $ $ </p>     <p>Here  $ minDigit(x) $  and  $ maxDigit(x) $  are the minimal and       maximal digits in the decimal representation of  $ x $  without       leading zeroes. For examples refer to notes.</p>     <p>Your task is calculate  $ a\_{K} $  for given  $ a\_{1} $  and  $ K$$$.

## 说明/提示

$ a_{1} = 487 $

 $ a_{2} = a_{1} + minDigit(a_{1}) \cdot maxDigit(a_{1}) = 487 +       \min (4, 8, 7) \cdot \max (4, 8, 7) = 487 + 4 \cdot 8 = 519 $

 $ a_{3} = a_{2} + minDigit(a_{2}) \cdot maxDigit(a_{2}) = 519 +       \min (5, 1, 9) \cdot \max (5, 1, 9) = 519 + 1 \cdot 9 = 528 $

 $ a_{4} = a_{3} + minDigit(a_{3}) \cdot maxDigit(a_{3}) = 528 +       \min (5, 2, 8) \cdot \max (5, 2, 8) = 528 + 2 \cdot 8 = 544 $

 $ a_{5} = a_{4} + minDigit(a_{4}) \cdot maxDigit(a_{4}) = 544 +       \min (5, 4, 4) \cdot \max (5, 4, 4) = 544 + 4 \cdot 5 = 564 $

 $ a_{6} = a_{5} + minDigit(a_{5}) \cdot maxDigit(a_{5}) = 564 +       \min (5, 6, 4) \cdot \max (5, 6, 4) = 564 + 4 \cdot 6 = 588 $

 $ a_{7} = a_{6} + minDigit(a_{6}) \cdot maxDigit(a_{6}) = 588 +       \min (5, 8, 8) \cdot \max (5, 8, 8) = 588 + 5 \cdot 8 = 628 $

## 样例 #1

### 输入

```
8
1 4
487 1
487 2
487 3
487 4
487 5
487 6
487 7```

### 输出

```
42
487
519
528
544
564
588
628```

# AI分析结果

### 题目内容
# 数字序列

## 题目描述
定义如下递推关系：$a_{n + 1} = a_{n} + minDigit(a_{n}) \cdot maxDigit(a_{n})$ 。这里 $minDigit(x)$ 和 $maxDigit(x)$ 分别是 $x$ 十进制表示中不含前导零的最小和最大数字。具体示例见注释。
你的任务是对于给定的 $a_{1}$ 和 $K$ ，计算 $a_{K}$ 。

## 说明/提示
$a_{1} = 487$ 
$a_{2} = a_{1} + minDigit(a_{1}) \cdot maxDigit(a_{1}) = 487 + \min (4, 8, 7) \cdot \max (4, 8, 7) = 487 + 4 \cdot 8 = 519$ 
$a_{3} = a_{2} + minDigit(a_{2}) \cdot maxDigit(a_{2}) = 519 + \min (5, 1, 9) \cdot \max (5, 1, 9) = 519 + 1 \cdot 9 = 528$ 
$a_{4} = a_{3} + minDigit(a_{3}) \cdot maxDigit(a_{3}) = 528 + \min (5, 2, 8) \cdot \max (5, 2, 8) = 528 + 2 \cdot 8 = 544$ 
$a_{5} = a_{4} + minDigit(a_{4}) \cdot maxDigit(a_{4}) = 544 + \min (5, 4, 4) \cdot \max (5, 4, 4) = 544 + 4 \cdot 5 = 564$ 
$a_{6} = a_{5} + minDigit(a_{5}) \cdot maxDigit(a_{5}) = 564 + \min (5, 6, 4) \cdot \max (5, 6, 4) = 564 + 4 \cdot 6 = 588$ 
$a_{7} = a_{6} + minDigit(a_{6}) \cdot maxDigit(a_{6}) = 588 + \min (5, 8, 8) \cdot \max (5, 8, 8) = 588 + 5 \cdot 8 = 628$ 

## 样例 #1
### 输入
```
8
1 4
487 1
487 2
487 3
487 4
487 5
487 6
487 7
```
### 输出
```
42
487
519
528
544
564
588
628
```

### 算法分类
递推

### 题解综合分析与结论
所有题解都意识到暴力求解会超时，核心思路都是利用当数字中出现0时，$minDigit(a_{n})$ 为0，后续数字不再变化这一特性来优化递推过程。不同题解在分析时间复杂度和代码实现细节上略有差异。

### 所选的题解
- **作者：do_while_true (5星)**
    - **关键亮点**：清晰分析出由于每次变化不超过100，一定能在百位出现0，大大减少时间复杂度，思路清晰且对时间复杂度分析透彻。
    - **个人心得**：无
    - **核心代码**：
```cpp
// 未给出具体代码，思路核心为利用数字出现0则停止递推，且分析出变化范围
```
核心实现思想：利用数字中出现0后不再变化的特性，通过分析变化范围优化递推过程。
- **作者：b6e0_ (4星)**
    - **关键亮点**：代码简洁明了，直接利用当数字某位为0则后续不变的性质进行优化，虽未精确分析时间复杂度，但指出最坏情况也能通过本题。
    - **个人心得**：打完CF来写题解，首次AC div2的D题求支持。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    long long n,k,i,maxv,minv;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        while(--k)
        {
            i=n;
            maxv=0;
            minv=10;
            while(i)
            {
                maxv=max(maxv,i%10);
                minv=min(minv,i%10);
                i/=10;
            }
            if(!(maxv*minv))
                break;
            n+=maxv*minv;
        }
        cout<<n<<endl;
    }
    return 0;
}
```
核心实现思想：每次循环计算当前数字的最大最小数字乘积，若为0则停止循环，否则更新数字。
- **作者：vectorwyx (4星)**
    - **关键亮点**：详细分析了时间复杂度，指出只考虑百位数，当累加和达到1000时百位一定会出现0，确定了递推次数上限，算法更严谨。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline ll read(){
    ll x=0,fh=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') fh=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*fh;
}

inline int f(ll x){
    int mn=100,mx=0;
    while(x){
        int k=x%10;
        x/=10;
        mn=min(mn,k);
        mx=max(mx,k);
    }
    return mn*mx;
}

void work(){
    ll a=read(),k=read();
    for(ll i=1;i<k;++i){
        int w=f(a);
        if(w==0){
            break;
        }
        a+=f(a);
    }
    printf("%lld\n",a);
}
int main(){
    int T=read();
    while(T--){
        work();
    }
    return 0;
}
```
核心实现思想：通过函数f计算数字的最大最小数字乘积，在递推过程中，若乘积为0则停止，否则更新数字。

### 最优关键思路或技巧
利用数字中出现0后递推结果不再变化的特性优化递推过程，通过分析每次变化的范围（最大为81），确定在有限次数（最多1000次）内百位一定会出现0，从而控制时间复杂度。

### 同类型题或类似算法套路拓展
此类题目通常是给定一个递推公式，通过观察递推过程中的特殊情况（如本题中数字出现0）来优化暴力解法。在遇到类似递推问题时，应仔细观察递推公式特点，寻找能使递推提前终止或减少计算量的关键条件。

### 洛谷相似知识点题目推荐
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过给定的规则进行数字的递推计算。
- [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)：根据不同的走楼梯方式建立递推关系求解。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：在归并排序基础上利用递推思想统计逆序对。 

---
处理用时：61.41秒