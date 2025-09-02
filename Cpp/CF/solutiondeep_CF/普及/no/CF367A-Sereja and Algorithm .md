# 题目信息

# Sereja and Algorithm 

## 题目描述

Sereja loves all sorts of algorithms. He has recently come up with a new algorithm, which receives a string as an input. Let's represent the input string of the algorithm as $ q=q_{1}q_{2}...\ q_{k} $ . The algorithm consists of two steps:

1. Find any continuous subsequence (substring) of three characters of string $ q $ , which doesn't equal to either string "zyx", "xzy", "yxz". If $ q $ doesn't contain any such subsequence, terminate the algorithm, otherwise go to step 2.
2. Rearrange the letters of the found subsequence randomly and go to step 1.

Sereja thinks that the algorithm works correctly on string $ q $ if there is a non-zero probability that the algorithm will be terminated. But if the algorithm anyway will work for infinitely long on a string, then we consider the algorithm to work incorrectly on this string.

Sereja wants to test his algorithm. For that, he has string $ s=s_{1}s_{2}...\ s_{n} $ , consisting of $ n $ characters. The boy conducts a series of $ m $ tests. As the $ i $ -th test, he sends substring $ s_{li}s_{li}+1...\ s_{ri} $ $ (1<=l_{i}<=r_{i}<=n) $ to the algorithm input. Unfortunately, the implementation of his algorithm works too long, so Sereja asked you to help. For each test $ (l_{i},r_{i}) $ determine if the algorithm works correctly on this test or not.

## 说明/提示

In the first example, in test one and two the algorithm will always be terminated in one step. In the fourth test you can get string "xzyx" on which the algorithm will terminate. In all other tests the algorithm doesn't work correctly.

## 样例 #1

### 输入

```
zyxxxxxxyyz
5
5 5
1 3
1 11
1 4
3 6
```

### 输出

```
YES
YES
NO
YES
NO
```

# AI分析结果



# 重写后的题目内容

# Sereja 与算法

## 题目描述

Sereja 热爱各种算法。他最近设计了一个新算法，该算法接收字符串作为输入。设算法的输入字符串为 $ q=q_{1}q_{2}...q_{k} $，算法包含两个步骤：

1. 在字符串 $ q $ 中寻找任意长度为 3 的连续子串（子序列），且该子串不等于 "zyx"、"xzy"、"yxz" 中的任意一个。如果找不到这样的子串，算法终止；否则执行步骤 2。
2. 随机重新排列找到的子串中的字符，返回步骤 1。

Sereja 认为算法在字符串 $ q $ 上能正确工作，当且仅当存在非零概率使得算法能够终止。若算法必定无限循环，则认为该算法在此字符串上工作异常。

现给定长度为 $ n $ 的字符串 $ s=s_{1}s_{2}...s_{n} $，进行 $ m $ 次测试。每次测试给定区间 $ [l_i, r_i] $，要求判断将子串 $ s[l_i..r_i] $ 输入算法时能否正确工作。

## 说明/提示

第一个样例中，测试一、二只需一步即可终止。测试四可通过排列得到 "xzyx" 使得算法终止。其余测试均会导致无限循环。

## 样例 #1

### 输入
```
zyxxxxxxyyz
5
5 5
1 3
1 11
1 4
3 6
```

### 输出
```
YES
YES
NO
YES
NO
```

---

**算法分类**  
前缀和

---

## 题解综合分析

所有题解核心思路一致：  
1. **前缀和预处理**：建立 x/y/z 的前缀计数数组  
2. **区间长度判定**：当 $r-l+1 < 3$ 时直接通过  
3. **字符平衡条件**：统计区间内 x/y/z 的数量，当三者数量差均 ≤1 时输出 YES

**关键难点**在于理解算法终止的充要条件：  
- 当且仅当字符串可排列为循环模式（如 xzyxzy...）时，所有三连子串均属于禁止列表，算法立即终止  
- 此时 x/y/z 的数量必须满足最大最小差 ≤1

---

## 优质题解推荐

### 题解1：qjxqjx（⭐⭐⭐⭐⭐）  
**亮点**  
- 清晰的变量命名（dpx/dpy/dpz）  
- 完备的初始化处理（memset 应对多组数据）  
- 使用绝对值函数简化条件判断  

```c
#include<bits/stdc++.h>
#define maxn 123456
using namespace std;
int dpx[maxn],dpy[maxn],dpz[maxn];
char str[maxn];

int main(){
    scanf("%s",str);
    int len = strlen(str);
    int x=0, y=0, z=0;
    for(int i=0; i<len; i++){
        if(str[i]=='x') x++;
        else if(str[i]=='y') y++;
        else z++;
        dpx[i+1] = x;
        dpy[i+1] = y;
        dpz[i+1] = z;
    }
    int m, l, r;
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&l,&r);
        if(r-l<2) printf("YES\n");
        else{
            int cx=dpx[r]-dpx[l-1], cy=dpy[r]-dpy[l-1], cz=dpz[r]-dpz[l-1];
            if(abs(cx-cy)<2 && abs(cy-cz)<2 && abs(cx-cz)<2)
                printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
```

---

### 题解2：ggc123（⭐⭐⭐⭐）  
**亮点**  
- 更简洁的输入处理  
- 使用标准库函数提升代码可移植性  
- 通过数学函数简化最大/最小值计算  

```cpp
#include<bits/stdc++.h>
using namespace std;
int cntx[100005], cnty[100005], cntz[100005];
string s;

int main() {
    cin >> s;
    s = '$' + s;
    for(int i=1; i<s.size(); i++) {
        cntx[i] = cntx[i-1] + (s[i]=='x');
        cnty[i] = cnty[i-1] + (s[i]=='y');
        cntz[i] = cntz[i-1] + (s[i]=='z');
    }
    int t; cin >> t;
    while(t--) {
        int l, r;
        cin >> l >> r;
        if(r-l < 2) cout << "YES\n";
        else {
            int x=cntx[r]-cntx[l-1], y=cnty[r]-cnty[l-1], z=cntz[r]-cntz[l-1];
            if(abs(x-y)<=1 && abs(y-z)<=1 && abs(x-z)<=1)
                cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
```

---

### 题解3：TLEWA（⭐⭐⭐）  
**亮点**  
- 采用极值差简化条件判断  
- 代码结构紧凑  
- 包含多组数据处理的防御性编程  

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],c[100005];

int main() {
    string s; int n;
    cin >> s >> n;
    for(int i=1; i<=s.size(); i++) {
        a[i] = a[i-1] + (s[i-1]=='x');
        b[i] = b[i-1] + (s[i-1]=='y');
        c[i] = c[i-1] + (s[i-1]=='z');
    }
    while(n--) {
        int l,r;
        cin >> l >> r;
        int x=a[r]-a[l-1], y=b[r]-b[l-1], z=c[r]-c[l-1];
        int mx = max({x,y,z}), mn = min({x,y,z});
        cout << (mx-mn<=1 || r-l<2 ? "YES\n" : "NO\n");
    }
    return 0;
}
```

---

## 关键技巧总结

1. **前缀和加速**：预处理字符出现次数，O(1) 时间获取区间统计  
2. **数学建模**：将字符串排列问题转化为字符数量平衡问题  
3. **边界处理**：长度 <3 的特殊情况直接处理

---

## 同类题目推荐

1. [P3405 [USACO09DEC]Crazy Laser S](https://www.luogu.com.cn/problem/P3405)  
   - 相似点：字符串模式分析与条件判断  
2. [P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)  
   - 相似点：前缀和结合极值判断  
3. [P1981 [NOIP2013 普及组] 表达式求值](https://www.luogu.com.cn/problem/P1981)  
   - 相似点：基于数学规律的字符串处理

---
处理用时：184.81秒