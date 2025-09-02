# 题目信息

# Grime Zoo

## 题目描述

Currently, XXOC's rap is a string consisting of zeroes, ones, and question marks. Unfortunately, haters gonna hate. They will write $ x $ angry comments for every occurrence of subsequence 01 and $ y $ angry comments for every occurrence of subsequence 10. You should replace all the question marks with 0 or 1 in such a way that the number of angry comments would be as small as possible.

String $ b $ is a subsequence of string $ a $ , if it can be obtained by removing some characters from $ a $ . Two occurrences of a subsequence are considered distinct if sets of positions of remaining characters are distinct.

## 说明/提示

In the first example one of the optimum ways to replace is 001. Then there will be $ 2 $ subsequences 01 and $ 0 $ subsequences 10. Total number of angry comments will be equal to $ 2 \cdot 2 + 0 \cdot 3 = 4 $ .

In the second example one of the optimum ways to replace is 11111. Then there will be $ 0 $ subsequences 01 and $ 0 $ subsequences 10. Total number of angry comments will be equal to $ 0 \cdot 13 + 0 \cdot 37 = 0 $ .

In the third example one of the optimum ways to replace is 1100. Then there will be $ 0 $ subsequences 01 and $ 4 $ subsequences 10. Total number of angry comments will be equal to $ 0 \cdot 239 + 4 \cdot 7 = 28 $ .

In the fourth example one of the optimum ways to replace is 01101001. Then there will be $ 8 $ subsequences 01 and $ 8 $ subsequences 10. Total number of angry comments will be equal to $ 8 \cdot 5 + 8 \cdot 7 = 96 $ .

## 样例 #1

### 输入

```
0?1
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
?????
13 37```

### 输出

```
0```

## 样例 #3

### 输入

```
?10?
239 7```

### 输出

```
28```

## 样例 #4

### 输入

```
01101001
5 7```

### 输出

```
96```

# AI分析结果

### 题目翻译
# Grime 动物园

## 题目描述
目前，XXOC 的说唱是一个由 0、1 和问号组成的字符串。不幸的是，总会有人讨厌。对于每一个子序列 01，他们会写下 $x$ 条愤怒评论；对于每一个子序列 10，他们会写下 $y$ 条愤怒评论。你应该用 0 或 1 替换所有的问号，使得愤怒评论的数量尽可能少。

如果字符串 $b$ 可以通过从字符串 $a$ 中删除一些字符得到，那么 $b$ 是 $a$ 的子序列。如果剩余字符的位置集合不同，则子序列的两次出现被认为是不同的。

## 说明/提示
在第一个样例中，一种最优的替换方式是 001。这样就会有 2 个子序列 01 和 0 个子序列 10。愤怒评论的总数将等于 $2 \cdot 2 + 0 \cdot 3 = 4$。

在第二个样例中，一种最优的替换方式是 11111。这样就会有 0 个子序列 01 和 0 个子序列 10。愤怒评论的总数将等于 $0 \cdot 13 + 0 \cdot 37 = 0$。

在第三个样例中，一种最优的替换方式是 1100。这样就会有 0 个子序列 01 和 4 个子序列 10。愤怒评论的总数将等于 $0 \cdot 239 + 4 \cdot 7 = 28$。

在第四个样例中，一种最优的替换方式是 01101001。这样就会有 8 个子序列 01 和 8 个子序列 10。愤怒评论的总数将等于 $8 \cdot 5 + 8 \cdot 7 = 96$。

## 样例 #1
### 输入
```
0?1
2 3
```
### 输出
```
4
```

## 样例 #2
### 输入
```
?????
13 37
```
### 输出
```
0
```

## 样例 #3
### 输入
```
?10?
239 7
```
### 输出
```
28
```

## 样例 #4
### 输入
```
01101001
5 7
```
### 输出
```
96
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何通过替换字符串中的问号，使得子序列 01 和 10 产生的愤怒评论总数最小。大部分题解都通过分析不同替换方式的贡献，得出最优解的填数方案是存在于字符串中某一个 `?` 前边的 `?` 全部填 `0` 或者 `1`，后边的填 `1` 或者 `0`，然后通过枚举或动态规划等方法来找到最优解。

### 所选题解
- **moqizhu2005（4星）**
    - **关键亮点**：思路清晰，通过比较两个问号不同填法的价值，得出若 `x>y` 把所有的 `0 1` 换成 `1 0`，若 `x<y` 把所有的 `1 0` 换成 `0 1` 的结论，然后分别处理两种情况，代码实现简洁明了。
- **AkeuchiTsuzuri（4星）**
    - **关键亮点**：直接给出贪心结论，即最优解的填数方案是存在于字符串中某一个 `?` 前边的 `?` 全部填 `0` 或者 `1`，后边的填 `1` 或者 `0`，然后详细说明了如何计算不同情况下的价值，思路简洁。
- **ConstantModerato（4星）**
    - **关键亮点**：先尝试用动态规划求解，在发现难以优化后，通过分析相邻问号不同填法的贡献，得出与其他题解相同的贪心结论，最后实现代码，思考过程完整。

### 重点代码
#### moqizhu2005 的代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const ll inf=(1ll<<60);
char s[100005];
ll x,y;
ll c0,c1,d0,d1,ans,len;
//c0和c1表示正向搜索0和1的数量
//d0和d1表示反向搜索0和1的数量 
void big()//若x>y 
{
    ll mans=inf;
    for(int i=0;i<len;i++)
        if(s[i]=='0') c0++,ans+=y*c1;
        else c1++,ans+=x*c0;
    mans=ans;
    for(int i=len-1;i>=0;i--)
        if(s[i]=='0') d0++,c0--;
        else if(s[i]=='1') d1++,c1--;
        else if(s[i]=='?')
        {
            c1--;
            ans=ans-c0*x-d0*y+c1*y+d1*x;
            mans=min(mans,ans);
            d0++;
        }
    printf("%lld\n",mans);
}
void small()//若x<y
{
    ll mans=inf;
    for(int i=0;i<len;i++)
        if(s[i]=='1') c1++,ans+=x*c0;
        else c0++,ans+=y*c1;
    mans=ans;
    for(int i=len-1;i>=0;i--)
        if(s[i]=='0') d0++,c0--;
        else if(s[i]=='1') d1++,c1--;
        else if(s[i]=='?')
        {
            c0--;
            ans=ans-c1*y-d1*x+c0*x+d0*y;
            mans=min(mans,ans);
            d1++;
        }
    printf("%lld\n",mans);
}
int main()
{
    scanf("%s%lld%lld",s,&x,&y);
    len=strlen(s);
    if(x>y) big();
    else small();
    return 0;
}
```
**核心实现思想**：先根据 `x` 和 `y` 的大小关系，分别处理两种情况。在 `big` 函数中，先正向计算初始价值，然后反向枚举问号，尝试将问号从 `1` 换成 `0` 并更新最小价值；在 `small` 函数中，先正向计算初始价值，然后反向枚举问号，尝试将问号从 `0` 换成 `1` 并更新最小价值。

#### AkeuchiTsuzuri 的思路
先得到当 `?` 全为 `0` 或者全为 `1` 时的字符串价值，然后倒序枚举每个 `?` 修改，根据不同的初始填法更新价值，同时更新 `0` 和 `1` 的数量，最后取最小值。

#### ConstantModerato 的代码
```cpp
const int N = 1e5 + 5;
int a,b,n,cnt;
string s;
int ans = 2e18;
int solve(){
    int cnt0 = 0,cnt1 = 0,num0 = 0,num1 = 0;
    int sum = 0,res = 2e18;
    for (int i = 0;i < n;i++){
        if (s[i] == '0' || s[i] == '?'){
            cnt0++; sum += cnt1 * b;
        } else {
            cnt1++; sum += cnt0 * a;
        }
    } res = sum; 
    for (int i = n - 1;i >= 0;i--){
        if (s[i] == '0') num0++,cnt0--;
        if (s[i] == '1') num1++,cnt1--;
        if (s[i] == '?'){
            cnt0--;
            sum = sum - cnt1 * b - num1 * a + num0 * b + cnt0 * a;
            num1++;
            res = min(res,sum);
        }
    } return res;
}
signed main(){
    cin >> s;n = s.size();
    a = read(),b = read();
    if (a >= b) swap(a,b),reverse(s.begin(),s.end());
    ans = min(ans,solve());
    cout << ans << endl;
    return 0;
}
```
**核心实现思想**：先正向计算当 `?` 全为 `0` 时的价值，然后反向枚举问号，尝试将问号从 `0` 换成 `1` 并更新最小价值。如果 `a >= b`，则交换 `a` 和 `b` 并反转字符串，保证 `a < b`。

### 关键思路或技巧
- 通过分析相邻问号不同填法的贡献，得出最优解的填数方案是存在于字符串中某一个 `?` 前边的 `?` 全部填 `0` 或者 `1`，后边的填 `1` 或者 `0`。
- 利用正向和反向枚举的方法，计算不同填法的价值并更新最小值。

### 拓展思路
同类型题可能会有更多的字符种类，或者子序列的定义更加复杂，但解题思路仍然可以是通过分析不同填法的贡献，找到最优的填数方案。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法，通过合理安排顺序使得总等待时间最小。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，每次选择最小的两个果子合并，直到合并成一个果子。
- [P2240 食草的奶牛](https://www.luogu.com.cn/problem/P2240)：考察贪心算法，根据奶牛的吃草时间和产奶量，选择最优的奶牛安排。

### 个人心得
- **ConstantModerato**：看到题先想到简单的 dp 做法，在发现难以优化后，考虑往贪心方向思考，通过分析相邻问号不同填法的贡献，得出贪心结论。这提醒我们在解题时可以先尝试常见的算法，若遇到困难再从其他角度思考。

---
处理用时：59.44秒