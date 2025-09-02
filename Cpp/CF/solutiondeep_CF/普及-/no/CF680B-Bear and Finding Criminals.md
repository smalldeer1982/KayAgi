# 题目信息

# Bear and Finding Criminals

## 题目描述

There are $ n $ cities in Bearland, numbered $ 1 $ through $ n $ . Cities are arranged in one long row. The distance between cities $ i $ and $ j $ is equal to $ |i-j| $ .

Limak is a police officer. He lives in a city $ a $ . His job is to catch criminals. It's hard because he doesn't know in which cities criminals are. Though, he knows that there is at most one criminal in each city.

Limak is going to use a BCD (Bear Criminal Detector). The BCD will tell Limak how many criminals there are for every distance from a city $ a $ . After that, Limak can catch a criminal in each city for which he is sure that there must be a criminal.

You know in which cities criminals are. Count the number of criminals Limak will catch, after he uses the BCD.

## 说明/提示

In the first sample, there are six cities and Limak lives in the third one (blue arrow below). Criminals are in cities marked red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF680B/53b34f04c80c68b5459bb6787b79d861ce7bb49e.png)Using the BCD gives Limak the following information:

- There is one criminal at distance $ 0 $ from the third city — Limak is sure that this criminal is exactly in the third city.
- There is one criminal at distance $ 1 $ from the third city — Limak doesn't know if a criminal is in the second or fourth city.
- There are two criminals at distance $ 2 $ from the third city — Limak is sure that there is one criminal in the first city and one in the fifth city.
- There are zero criminals for every greater distance.

So, Limak will catch criminals in cities $ 1 $ , $ 3 $ and $ 5 $ , that is $ 3 $ criminals in total.

In the second sample (drawing below), the BCD gives Limak the information that there is one criminal at distance $ 2 $ from Limak's city. There is only one city at distance $ 2 $ so Limak is sure where a criminal is.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF680B/9b09abcaba16810167119bac2c883bc8bf99b11b.png)

## 样例 #1

### 输入

```
6 3
1 1 1 0 1 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2
0 0 0 1 0
```

### 输出

```
1
```

# AI分析结果

### 题目内容中文重写
# 熊与寻找罪犯

## 题目描述
在熊国里有 $n$ 个城市，编号从 $1$ 到 $n$。这些城市排成一排。城市 $i$ 和城市 $j$ 之间的距离等于 $|i - j|$。

利马克是一名警察。他住在城市 $a$。他的工作是抓捕罪犯。这项工作很困难，因为他不知道罪犯藏在哪些城市。不过，他知道每个城市最多只有一名罪犯。

利马克打算使用 BCD（熊罪犯探测器）。BCD 会告诉利马克距离城市 $a$ 每个距离上分别有多少罪犯。之后，利马克就可以抓捕那些他确定有罪犯的城市里的罪犯。

你已知哪些城市有罪犯。请计算利马克使用 BCD 后能抓捕到的罪犯数量。

## 说明/提示
在第一个样例中，有六个城市，利马克住在第三个城市（下面的蓝色箭头所示）。罪犯所在的城市用红色标记。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF680B/53b34f04c80c68b5459bb6787b79d861ce7bb49e.png)使用 BCD 会给利马克如下信息：
- 距离第三个城市 $0$ 的地方有一名罪犯——利马克确定这名罪犯就在第三个城市。
- 距离第三个城市 $1$ 的地方有一名罪犯——利马克不知道罪犯是在第二个城市还是第四个城市。
- 距离第三个城市 $2$ 的地方有两名罪犯——利马克确定第一个城市有一名罪犯，第五个城市也有一名罪犯。
- 距离更大的地方没有罪犯。

所以，利马克会在城市 $1$、$3$ 和 $5$ 抓捕罪犯，总共抓捕 $3$ 名罪犯。

在第二个样例（下图）中，BCD 告诉利马克距离他所在城市 $2$ 的地方有一名罪犯。距离为 $2$ 的只有一个城市，所以利马克确定罪犯所在的位置。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF680B/9b09abcaba16810167119bac2c883bc8bf99b11b.png)

## 样例 #1
### 输入
```
6 3
1 1 1 0 1 0
```
### 输出
```
3
```

## 样例 #2
### 输入
```
5 2
0 0 0 1 0
```
### 输出
```
1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕着距离警察所在城市 $a$ 相同距离的两个城市（$a + i$ 和 $a - i$）来判断是否能确定罪犯位置。主要步骤通常是先统计所有城市中的罪犯总数，然后遍历距离，对于距离 $a$ 相同的两个城市，如果其中只有一个城市有罪犯，则无法确定罪犯位置，需要从总数中减去。

不同题解的差异主要体现在代码实现方式和细节处理上，例如有的使用双指针，有的直接枚举距离；在处理边界情况时也有不同的判断逻辑。

### 所选题解
- Wendy_Hello_qwq（4星）
    - 关键亮点：思路清晰，代码简洁，注释详细，先统计所有罪犯数量，再通过遍历距离减去无法确定位置的罪犯数量。
    - 核心代码：
```cpp
#include <cstdio>
using namespace std;
int n, a, num, b[107];
int main()
{
    scanf ("%d%d", &n, &a);
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &b[i]);
        if (b[i] == 1)
            num++; 
    }
    for (int i = 0; a + i <= n && a - i >= 1; i++)
    {
        if (b[a + i] + b[a - i] == 1)
            num--;
    }
    printf ("%d", num);
    return 0;
}
```
核心实现思想：先通过输入统计所有有罪犯的城市数量，然后遍历距离，对于距离警察所在城市 $a$ 相同的两个城市，如果其中只有一个城市有罪犯，则从总数中减去。

- __DayLight__（4星）
    - 关键亮点：使用双指针的方法，思路新颖，对于指针到达边界的情况处理清晰。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,ans;
bool t[105];
signed main(){
    cin>>n>>a;
    for(int i=1; i<=n; i++)
        cin>>t[i];
    for(int L=a+1,R=a-1;;)
    {
        if(L>1)L--;
        if(R<n)R++;
        if(a-L==R-a)
        {
            if(L==R&&t[L])ans++;
            else ans+=t[L]*t[R]*(t[L]+t[R]);
        }
        if(a-L<R-a)ans+=t[R];
        if(a-L>R-a)ans+=t[L];
        if(L==1&&R==n)break;
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：使用双指针 $L$ 和 $R$ 分别指向距离警察所在城市 $a$ 相同距离的两个城市，根据指针位置和城市是否有罪犯的情况来统计能确定位置的罪犯数量。

- Laoda_Bryant（4星）
    - 关键亮点：思路清晰，对不同情况的分析明确，使用异或运算简化判断。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool k[105];
int n,a,all=0;
int main(){
    cin>>n>>a;
    for(int i=1;i<=n;i++){
        cin>>k[i];
        if(k[i]) all++;
    }
    for(int i=1;a+i<=n&&a-i>=1;i++){
        if(k[a+i]^k[a-i]) all--;
    }
    cout<<all;
    return 0;
}
```
核心实现思想：先统计所有有罪犯的城市数量，然后遍历距离，对于距离警察所在城市 $a$ 相同的两个城市，如果其中只有一个城市有罪犯（使用异或运算判断），则从总数中减去。

### 最优关键思路或技巧
- 先统计所有城市中的罪犯总数，再通过遍历距离减去无法确定位置的罪犯数量，这种先总后分的思路可以简化问题。
- 使用双指针可以更直观地处理距离相同的两个城市的情况，并且方便处理边界条件。
- 利用异或运算（`^`）可以简洁地判断两个城市中是否只有一个城市有罪犯。

### 可拓展之处
同类型题可能会改变城市的排列方式（如二维平面），或者增加更多的条件（如不同类型的罪犯），但核心思路仍然是通过已知信息判断罪犯的位置。类似算法套路可以应用在其他需要根据相对位置和条件判断的问题中。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)

### 个人心得
题解中未包含个人心得。

---
处理用时：46.21秒