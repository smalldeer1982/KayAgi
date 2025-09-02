# 题目信息

# Corrupted Array

## 题目描述

给定一个正整数$n$和长度为$n+2$的数组$b$，数组$b$是依据如下算法构造的：

- 随机生成一个含有 $n$ 个元素的原始数组$a$；
- 把数组 $a$ 赋值给数组 $b$，即 $b_i=a_i(1\le i\le n)$；
- 数组 $b$ 的第 $n+1$ 个元素为数组 $a$ 的元素和，即 $b_{n+1}=\sum_{i=1}^na_i$；
- 数组 $b$ 的第 $n+2$ 个元素是个随机整数 $x(1\le x\le10^9)$；
- 打乱 $b$ 数组。

例如，数组 $b=[2,3,7,12,2]$，那么它能够通过如下方式构建：

- $a=[2,2,3]$，且$x=12$；
- $a=[3,2,7]$，且$x=2$。

给定一个$b$数组，请你求出它对应的$a$数组。

## 样例 #1

### 输入

```
4
3
2 3 7 12 2
4
9 1 7 1 6 5
5
18 2 2 3 2 9 2
3
2 6 9 2 1```

### 输出

```
2 3 7 
-1
2 2 2 3 9 
1 2 6```

# AI分析结果

### 题目内容
# 损坏的数组

## 题目描述

给定一个正整数$n$和长度为$n+2$的数组$b$，数组$b$是依据如下算法构造的：

- 随机生成一个含有 $n$ 个元素的原始数组$a$；
- 把数组 $a$ 赋值给数组 $b$，即 $b_i=a_i(1\le i\le n)$；
- 数组 $b$ 的第 $n+1$ 个元素为数组 $a$ 的元素和，即 $b_{n+1}=\sum_{i=1}^na_i$；
- 数组 $b$ 的第 $n+2$ 个元素是个随机整数 $x(1\le x\le10^9)$；
- 打乱 $b$ 数组。

例如，数组 $b=[2,3,7,12,2]$，那么它能够通过如下方式构建：

- $a=[2,2,3]$，且$x=12$；
- $a=[3,2,7]$，且$x=2$。

给定一个$b$数组，请你求出它对应的$a$数组。

### 样例 #1

#### 输入

```
4
3
2 3 7 12 2
4
9 1 7 1 6 5
5
18 2 2 3 2 9 2
3
2 6 9 2 1```

#### 输出

```
2 3 7 
-1
2 2 2 3 9 
1 2 6```

### 算法分类
排序、构造

### 题解分析与结论

题目要求从打乱的数组 $b$ 中恢复出原始数组 $a$。由于 $b$ 包含了 $a$ 的所有元素、$a$ 的元素和以及一个随机数 $x$，因此可以通过排序和枚举的思路来解决。

#### 关键思路：
1. **排序**：首先对数组 $b$ 进行排序，方便后续处理。
2. **枚举**：枚举可能的 $x$，并检查剩下的元素是否满足 $a$ 的条件。
3. **求和判断**：通过计算前 $n$ 个元素的和，判断是否等于第 $n+1$ 个元素，或者通过前 $n+1$ 个元素的和减去某个元素是否等于第 $n+2$ 个元素。

#### 难点：
- 需要处理 $x$ 可能大于 $a$ 的元素和的情况。
- 需要确保枚举的 $x$ 不会影响 $a$ 的构造。

### 评分较高的题解

#### 题解1：作者：Dragonbell_exp (赞：5)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，通过排序和枚举的方式高效地解决了问题。
- **代码核心思想**：
  - 对数组 $b$ 进行排序。
  - 计算前 $n$ 个元素的和，判断是否等于第 $n+1$ 个元素。
  - 如果不等于，则计算前 $n+1$ 个元素的和，枚举每个元素，判断是否满足条件。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t;
int n;
long long num;
int a[1000000];
bool can;
int main(){
    t=read();
    while(t--){
        n=read();
        num=0;
        can=0;
        for(int i=1;i<=n+2;i++){
            a[i]=read();
        }
        sort(a+1,a+n+3);
        for(int i=1;i<=n;i++){
            num+=a[i];
        }
        if(num==a[n+1]){
            for(int i=1;i<=n;i++){
                cout<<a[i]<<" ";
            }
            cout<<endl;
            can=1;
            continue;
        }
        num+=a[n+1];
        for(int i=1;i<=n+1;i++){
            if(num-a[i]==a[n+2]){
                for(int j=1;j<=n+1;j++){
                    if(j==i){
                        continue;
                    }
                    cout<<a[j]<<" ";
                }
                cout<<endl;
                can=1;
                break;
            }
        }
        if(can==0){
            cout<<-1<<endl;
        }
    }
    return 0;
}
```

#### 题解2：作者：rui_er (赞：2)
- **星级**：4星
- **关键亮点**：通过前缀和的方式简化了判断逻辑，代码结构清晰。
- **代码核心思想**：
  - 对数组 $b$ 进行排序，并计算前缀和。
  - 判断第 $n+1$ 个元素是否等于前 $n$ 个元素的和。
  - 如果不等于，则枚举前 $n+1$ 个元素，判断是否满足条件。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5+5;

ll n, k, b[N], s[N];

int main() {
    mulT0 {
        scanf("%lld", &n); k = n + 2;
        rep(i, 1, k) scanf("%lld", &b[i]);
        sort(b+1, b+1+k);
        rep(i, 1, k) s[i] = s[i-1] + b[i];
        if(b[n+1] == s[n]) rep(i, 1, n) printf("%lld ", b[i]);
        else {
            int ok = 0;
            rep(i, 1, n+1) if(b[n+2] == s[n+1] - b[i]) {ok = i; break;}
            if(ok) {rep(i, 1, n+1) if(i != ok) printf("%lld ", b[i]);}
            else printf("-1");
        }
        puts("");
    }
    return 0;
}
```

#### 题解3：作者：StayAlone (赞：0)
- **星级**：4星
- **关键亮点**：通过二分查找优化了枚举过程，提高了效率。
- **代码核心思想**：
  - 对数组 $b$ 进行排序，并计算总和。
  - 枚举每个元素，通过二分查找判断是否存在满足条件的 $x$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=114514*2;
long long  a[N],b[N],num,data,n,m,T,sum;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        mp.clear();
        sum=0;
        for(int i=1;i<=n+2;i++)
        {
            cin>>a[i];
        }
        sort(a+1,a+3+n);
        for(int i=1;i<=n;i++) sum+=a[i];
        if(sum==a[n+1])
        {
            for(int i=1;i<=n;i++) cout<<a[i]<<" ";cout<<endl;
            flag=1;
        }
        bool flag=0;
        sum+=a[n+1];
        for(int i=1;i<=n+1;i++)
        {
            if(sum-a[i]==a[n+2])
            {
                for(int j=1;j<=n+1;j++) if(i!=j) cout<<a[j]<<" ";
                cout<<endl;
                flag=1;
                break;
            }
        }
        if(!flag) cout<<-1<<endl;
    }
    return 0;
}
```

### 最优关键思路与技巧
1. **排序**：通过排序可以快速找到可能的 $a$ 的元素和 $x$。
2. **枚举与判断**：通过枚举可能的 $x$，并利用求和判断是否满足条件，可以高效地恢复出 $a$。
3. **前缀和**：使用前缀和可以简化求和计算，提高代码的可读性和效率。

### 拓展与举一反三
- 类似题目：可以通过排序和枚举的思路解决类似的构造问题，如从打乱的数组中恢复出原始数据。
- 推荐题目：
  - [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
  - [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
  - [P1013 进制位](https://www.luogu.com.cn/problem/P1013)

---
处理用时：60.24秒