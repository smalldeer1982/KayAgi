# 题目信息

# [ARC173A] Neq Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc173/tasks/arc173_a

正整数 $ X $ が以下の条件を満たすとき、$ X $ は **“Neq Number”** であるといいます。

- $ X $ を十進法表記した際、どの隣接する $ 2 $ 文字も相異なる
 
例えば $ 1,173,9090 $ は “Neq Number” です。一方、 $ 22,6335 $ は “Neq Number” ではありません。

正整数 $ K $ が与えられます。小さいほうから $ K $ 番目の “Neq Number” を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 100 $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ 1 $ つめのテストケースについて、 “Neq Number” を小さいものから $ 25 $ 個あげていくと - $ 1 $ から $ 9 $ までの整数の $ 9 $ 個 - $ 10 $ から $ 19 $ までの整数のうち、 $ 11 $ を除いた $ 9 $ 個 - $ 20 $ から $ 27 $ までの整数のうち、 $ 22 $ を除いた $ 7 $ 個 となります。よって、小さいほうから $ 25 $ 番目の “Neq Number” は $ 27 $ となります。

## 样例 #1

### 输入

```
3

25

148

998244353```

### 输出

```
27

173

2506230721```

# AI分析结果

### 题目内容重写

#### 题目描述

正整数 $X$ 如果满足以下条件，则称为 **“Neq Number”**：

- 当 $X$ 用十进制表示时，任何相邻的两个字符都不相同。

例如，$1$、$173$ 和 $9090$ 是 “Neq Number”，而 $22$ 和 $6335$ 不是。

给定一个正整数 $K$，请找出第 $K$ 小的 “Neq Number”。

#### 输入格式

输入包含 $T$ 个测试用例，每个测试用例给出一个整数 $K$。

#### 输出格式

对于每个测试用例，输出第 $K$ 小的 “Neq Number”。

#### 样例输入

```
3
25
148
998244353
```

#### 样例输出

```
27
173
2506230721
```

#### 说明/提示

- $1 \leq T \leq 100$
- $1 \leq K \leq 10^{12}$
- 输入的所有值均为整数。

### 题解综合分析与结论

本题的核心在于如何高效地找到第 $K$ 个“Neq Number”。由于 $K$ 的范围很大（$1 \leq K \leq 10^{12}$），直接枚举或暴力搜索显然不可行。因此，大多数题解采用了**二分查找**结合**数位DP**或**进制转换**的思路来解决。

#### 关键思路与技巧

1. **二分查找**：通过二分查找确定第 $K$ 个“Neq Number”的可能范围，然后使用数位DP或进制转换来验证。
2. **数位DP**：用于计算小于等于某个数的“Neq Number”的数量，通常需要处理前导零和相邻数字相同的限制。
3. **进制转换**：将问题转化为9进制问题，因为每位数字有9种选择（第一位不能为0，后面的数字不能与前一位相同）。

#### 最优思路总结

最优的思路是将问题转化为9进制问题，通过逐位确定第 $K$ 个“Neq Number”的每一位。这种方法避免了复杂的数位DP，代码简洁且效率高。

### 评分较高的题解

#### 题解1：作者：无名之雾 (赞：8)

**星级**：★★★★★  
**关键亮点**：通过9进制转换的思路，避免了复杂的数位DP，代码简洁且高效。  
**个人心得**：作者在赛后意识到可以直接用9进制解决问题，避免了复杂的数位DP实现。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int T;
    cin>>T;
    while(T--){
        int k;
        cin>>k;
        int wei=0,cheng=1,last=0;
        while(k>=cheng) k-=cheng,wei++,cheng*=9;
        while(wei){
            cheng/=9,wei--;
            cout<<k/cheng+(k/cheng>=last);
            last=k/cheng+(k/cheng>=last);
            k-=k/cheng*cheng;
        }
        cout<<endl;
    }
    return 0;
}
```

#### 题解2：作者：XYQ_102 (赞：0)

**星级**：★★★★  
**关键亮点**：通过逐位确定第 $K$ 个“Neq Number”的每一位，思路清晰且代码简洁。  
**个人心得**：作者通过逐位确定数字，避免了复杂的数位DP实现。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace fastIO{
    inline int read(){
        int x=0,f=1;char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
        while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
        return x*f;
    }
    int buf[20],TOT;
    inline void print(int x,char ch=' '){
        if(x<0) putchar('-'),x=-x;
        else if(x==0) buf[++TOT]=0;
        for(int i=x;i;i/=10) buf[++TOT]=i%10;
        do{putchar(buf[TOT]+'0');}while(--TOT);
        putchar(ch);
    }
}
using namespace fastIO;
int T,n; 
signed main(){
    T=read();
    while(T--){
        n=read(); 
        int len=1;
        while(pow(9,len)<n) n-=pow(9,len++);
        int pre=0;
        for(int i=1;i<=len;i++){
            for(int j=0;j<=9;j++){
                if(j==pre) continue;
                if(pow(9,len-i)>=n){
                    putchar('0'+j);
                    pre=j;
                    break;
                }
                else n-=pow(9,len-i);
            }
        }
        putchar('\n');
    }
    return 0;
}
```

#### 题解3：作者：OIer_Tan (赞：0)

**星级**：★★★★  
**关键亮点**：通过9进制转换的思路，代码简洁且高效。  
**个人心得**：作者通过9进制转换的思路，避免了复杂的数位DP实现。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define endl '\n' 
using namespace std ;
typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;
ll T ;
void solve (){
    ll k ;
    cin >> k ;
    ll len = 0 , last = 0 , temp = 1 ;
    while ( k >= temp ){
        k -= temp ;
        len ++ ;
        temp *= 9 ;
    }
    temp /= 9 ;
    while ( len ){
        ll now = k / temp ;
        if ( now >= last ) now ++ ;
        cout << now ;
        last = now ;
        k -= k / temp * temp ;
        temp /= 9 , len -- ;
    }
    cout << endl ;
    return ;
}
int main (){
    ios::sync_with_stdio ( 0 ) ;
    cin.tie ( 0 ) ;
    cout.tie ( 0 ) ;
    cin >> T ;
    while ( T -- ) solve () ;
    return 0 ;
}
```

### 推荐题目

1. **P2657 [SCOI2009] windy数**：考察数位DP的经典题目，与本题类似。
2. **P2602 [ZJOI2010]数字计数**：考察数位DP的应用，适合练习数位DP的技巧。
3. **P4127 [AHOI2009]同类分布**：考察数位DP与数学结合的应用，适合进一步挑战。

---
处理用时：57.30秒