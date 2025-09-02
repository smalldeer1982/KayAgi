# 题目信息

# Plasticine zebra

## 题目描述

Is there anything better than going to the zoo after a tiresome week at work? No wonder Grisha feels the same while spending the entire weekend accompanied by pretty striped zebras.

Inspired by this adventure and an accidentally found plasticine pack (represented as a sequence of black and white stripes), Grisha now wants to select several consequent (contiguous) pieces of alternating colors to create a zebra. Let's call the number of selected pieces the length of the zebra.

Before assembling the zebra Grisha can make the following operation $ 0 $ or more times. He splits the sequence in some place into two parts, then reverses each of them and sticks them together again. For example, if Grisha has pieces in the order "bwbbw" (here 'b' denotes a black strip, and 'w' denotes a white strip), then he can split the sequence as bw|bbw (here the vertical bar represents the cut), reverse both parts and obtain "wbwbb".

Determine the maximum possible length of the zebra that Grisha can produce.

## 说明/提示

In the first example one of the possible sequence of operations is bwwwbww|bw $ \to $ w|wbwwwbwb $ \to $ wbwbwwwbw, that gives the answer equal to $ 5 $ .

In the second example no operation can increase the answer.

## 样例 #1

### 输入

```
bwwwbwwbw
```

### 输出

```
5
```

## 样例 #2

### 输入

```
bwwbwwb
```

### 输出

```
3
```

# AI分析结果

### 题目中文重写
# 橡皮泥斑马

## 题目描述
在工作了疲惫的一周后，还有什么比去动物园更好的事情吗？难怪 Grisha 在整个周末都陪伴着漂亮的条纹斑马时也有同样的感受。

受这次冒险和偶然发现的一包橡皮泥（用黑白条纹序列表示）的启发，Grisha 现在想选择几个连续的、颜色交替的片段来制作一只斑马。我们把所选片段的数量称为斑马的长度。

在组装斑马之前，Grisha 可以进行 0 次或多次以下操作。他在某个位置将序列分成两部分，然后将每部分反转，再将它们重新粘在一起。例如，如果 Grisha 拥有的片段顺序是 "bwbbw"（这里 'b' 表示黑色条纹，'w' 表示白色条纹），那么他可以将序列分割为 bw|bbw（这里竖线表示分割点），反转两部分后得到 "wbwbb"。

确定 Grisha 能够制作出的斑马的最大可能长度。

## 说明/提示
在第一个示例中，一种可能的操作序列是 bwwwbww|bw → w|wbwwwbwb → wbwbwwwbw，这给出的答案等于 5。

在第二个示例中，任何操作都无法增加答案。

## 样例 #1
### 输入
```
bwwwbwwbw
```
### 输出
```
5
```

## 样例 #2
### 输入
```
bwwbwwb
```
### 输出
```
3
```

### 综合分析与结论
这些题解的核心思路都是将原问题转化为在一个环上寻找最长交替子串的问题。由于题目中的操作可以等效为对字符串进行循环移位，所以通过将字符串复制一份接在原字符串后面（化环为链），就可以方便地遍历所有可能的循环移位情况。

各题解的算法要点主要是遍历化环为链后的字符串，统计连续交替的子串长度，并不断更新最大值。难点在于理解操作的本质是循环移位，以及在统计长度时要注意对原字符串长度取最小值。

### 所选题解
- **ouuan（4星）**
    - **关键亮点**：思路清晰，通过绘图形象地展示了操作的本质是循环移位，将问题转化为环上的问题，代码简洁易懂。
    - **核心代码**：
```cpp
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string s;

int main()
{
    int i,ans,t;
    
    cin>>s;
    
    s+=s;
    
    ans=t=1;
    
    for (i=1;i<s.size();++i)
    {
        if (s[i]==s[i-1])
        {
            t=1;
        }
        else
        {
            ++t;
            ans=max(ans,t);
        }
    }
    
    cout<<min(ans,int(s.size()/2));
    
    return 0;
}
```
**核心实现思想**：先将原字符串复制一份接在后面，然后遍历新字符串，统计连续交替的子串长度，更新最大值，最后结果对原字符串长度取最小值。

- **fuxuantong123（4星）**
    - **关键亮点**：思路简洁明了，直接指出问题是求环上的最长交错字段，化环为链后扫描一遍即可，代码实现简洁。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    s=s+s;//化环为链
    int n=s.size();
    int cnt=1;
    int ans=0;
    for(int i=1;i<n;i++){
        if(s[i]!=s[i-1]){
            cnt++;
        }
        else{
            cnt=1;
        }
        //求最长交错字段
        ans=max(ans,min(cnt,n/2));//记得和n/2取最小
    }
    printf("%d",ans);
    return 0;
}
```
**核心实现思想**：将原字符串复制一份接在后面，遍历新字符串，统计连续交替的子串长度，更新最大值并对原字符串长度取最小值。

- **rui_er（4星）**
    - **关键亮点**：通过数学推导将操作转化为循环移位，逻辑严谨，代码规范，使用了宏定义和模板函数，提高了代码的复用性。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n;
char s[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
    scanf("%s", s);
    n = strlen(s);
    rep(i, n, n+n-1) s[i] = s[i-n];
    int now = 1, ans = 0;
    rep(i, 1, n+n-1) {
        if(s[i] == s[i-1]) now = 1;
        else ++now;
        chkmax(ans, now);
    }
    chkmin(ans, n);
    printf("%d\n", ans);
    return 0;
}
```
**核心实现思想**：将原字符串复制一份接在后面，遍历新字符串，统计连续交替的子串长度，更新最大值并对原字符串长度取最小值。

### 最优关键思路或技巧
- **化环为链**：将原字符串复制一份接在后面，把环上的问题转化为链上的问题，方便遍历所有可能的循环移位情况。
- **遍历统计**：遍历化环为链后的字符串，统计连续交替的子串长度，并不断更新最大值。
- **取最小值**：最终结果要对原字符串长度取最小值，避免结果超出原字符串的范围。

### 可拓展之处
同类型题或类似算法套路：
- 环形数组相关问题：如环形数组的最大子数组和、环形数组的最长递增子序列等，都可以采用化环为链的方法解决。
- 字符串循环移位问题：给定一个字符串和一个移位次数，求移位后的字符串，也可以通过化环为链的方法实现。

### 推荐洛谷题目
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得
题解中未包含个人心得。

---
处理用时：51.19秒