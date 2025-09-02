# 题目信息

# Integral Array

## 题目描述

You are given an array $ a $ of $ n $ positive integers numbered from $ 1 $ to $ n $ . Let's call an array integral if for any two, not necessarily different, numbers $ x $ and $ y $ from this array, $ x \ge y $ , the number $ \left \lfloor \frac{x}{y} \right \rfloor $ ( $ x $ divided by $ y $ with rounding down) is also in this array.

You are guaranteed that all numbers in $ a $ do not exceed $ c $ . Your task is to check whether this array is integral.

## 说明/提示

In the first test case it is easy to see that the array is integral:

- $ \left \lfloor \frac{1}{1} \right \rfloor = 1 $ , $ a_1 = 1 $ , this number occurs in the arry
- $ \left \lfloor \frac{2}{2} \right \rfloor = 1 $
- $ \left \lfloor \frac{5}{5} \right \rfloor = 1 $
- $ \left \lfloor \frac{2}{1} \right \rfloor = 2 $ , $ a_2 = 2 $ , this number occurs in the array
- $ \left \lfloor \frac{5}{1} \right \rfloor = 5 $ , $ a_3 = 5 $ , this number occurs in the array
- $ \left \lfloor \frac{5}{2} \right \rfloor = 2 $ , $ a_2 = 2 $ , this number occurs in the array

Thus, the condition is met and the array is integral.

In the second test case it is enough to see that

 $ \left \lfloor \frac{7}{3} \right \rfloor = \left \lfloor 2\frac{1}{3} \right \rfloor = 2 $ , this number is not in $ a $ , that's why it is not integral.

In the third test case $ \left \lfloor \frac{2}{2} \right \rfloor = 1 $ , but there is only $ 2 $ in the array, that's why it is not integral.

## 样例 #1

### 输入

```
4
3 5
1 2 5
4 10
1 3 3 7
1 2
2
1 1
1```

### 输出

```
Yes
No
No
Yes```

## 样例 #2

### 输入

```
1
1 1000000
1000000```

### 输出

```
No```

# AI分析结果

### 题目翻译
# 整数数组

## 题目描述
给定一个由 $n$ 个正整数组成的数组 $a$，数组元素编号从 $1$ 到 $n$。如果对于这个数组中的任意两个数（不一定不同）$x$ 和 $y$，且 $x \ge y$，满足 $\left \lfloor \frac{x}{y} \right \rfloor$（$x$ 除以 $y$ 向下取整）也在这个数组中，那么我们称这个数组是整数数组。

已知数组 $a$ 中的所有数字都不超过 $c$。你的任务是检查这个数组是否为整数数组。

## 说明/提示
在第一个测试用例中，很容易看出该数组是整数数组：
- $\left \lfloor \frac{1}{1} \right \rfloor = 1$，$a_1 = 1$，这个数字在数组中出现。
- $\left \lfloor \frac{2}{2} \right \rfloor = 1$。
- $\left \lfloor \frac{5}{5} \right \rfloor = 1$。
- $\left \lfloor \frac{2}{1} \right \rfloor = 2$，$a_2 = 2$，这个数字在数组中出现。
- $\left \lfloor \frac{5}{1} \right \rfloor = 5$，$a_3 = 5$，这个数字在数组中出现。
- $\left \lfloor \frac{5}{2} \right \rfloor = 2$，$a_2 = 2$，这个数字在数组中出现。

因此，满足条件，该数组是整数数组。

在第二个测试用例中，只需注意到：
$\left \lfloor \frac{7}{3} \right \rfloor = \left \lfloor 2\frac{1}{3} \right \rfloor = 2$，这个数字不在数组 $a$ 中，所以该数组不是整数数组。

在第三个测试用例中，$\left \lfloor \frac{2}{2} \right \rfloor = 1$，但数组中只有 $2$，所以该数组不是整数数组。

## 样例 #1
### 输入
```
4
3 5
1 2 5
4 10
1 3 3 7
1 2
2
1 1
1
```
### 输出
```
Yes
No
No
Yes
```

## 样例 #2
### 输入
```
1
1 1000000
1000000
```
### 输出
```
No
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是将直接枚举因数的 $O(n^2)$ 复杂度算法，优化为枚举倍数的算法，利用前缀和快速判断区间内是否存在元素，从而将时间复杂度优化到 $O(c \ln c)$。

各题解的思路和要点基本一致，都是先对输入的数组进行处理，用桶记录元素是否出现，再计算前缀和，然后枚举元素及其倍数，判断是否满足整数数组的条件。

解决的难点在于如何优化直接枚举 $x$ 和 $y$ 的 $O(n^2)$ 复杂度，通过将问题转化为枚举倍数，并利用前缀和快速查询区间内元素的存在情况，成功降低了复杂度。

### 所选题解
- **作者：HPXXZYY (4星)**
    - **关键亮点**：思路清晰，详细阐述了将因数问题转化为倍数问题的过程，利用差分算法维护数组，代码实现简洁明了。
    - **核心代码**：
```cpp
const int N=1e6+100;

int pre[N],a[N],n,C,s[N];

int main(){
    for(int T=1,Q=read();T<=Q;T++){
        n=read();C=read();
        for(int i=1;i<=n;i++)
            a[i]=read();
        
        sort(a+1,a+n+1);
        n=unique(a+1,a+n+1)-a-1;
        
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if (1ll*a[i]*a[j]<=C){
                    pre[a[i]*a[j]]++;
                    if ((a[i]+1)*a[j]<=C)
                        pre[(a[i]+1)*a[j]]--;
                }
                else break;
        
        for(int i=1;i<=C;i++)
            s[i]=s[i-1]+pre[i];
        
        bool flag=true;
        for(int i=1;i<=n;i++)
            if (s[a[i]]<i){
                flag=false;break;
            }
        
        if (a[1]!=1) flag=false;
        
        printf("%s\n",flag?"Yes":"No");
        
        for(int i=1;i<=C;i++) pre[i]=s[i]=0;
    }
    
    return 0;
}
```
核心实现思想：先对数组去重排序，然后利用差分算法维护 $s$ 数组，$s[k]$ 表示有多少个 $a_i$ 可以表示出 $a_k$，最后判断是否满足条件。

- **作者：Ezis (4星)**
    - **关键亮点**：思路简洁，明确指出利用前缀和判断区间元素存在情况，同时提醒了不要清空整个数组以避免时间爆炸的坑点。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,T,mat[1000005],s[1000005];
bool check(){
    scanf("%d%d",&n,&c);
    for(int i=1;i<=c;i++) mat[i]=s[i]=0;
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x);
        mat[x]=1;
    }
    if(!mat[1]) return false;
    for(int i=1;i<=c;i++) s[i]=s[i-1]+mat[i];
    for(int i=2;i<=c;i++){
        if(!mat[i]) continue;
        for(int j=i;j<=c;j+=i)
            if(s[min(c,j+i-1)]-s[j-1])
                if(!mat[j/i]) return false;
    }
    return true;
} 
int main(){
    scanf("%d",&T);
    while(T--){
        if(check()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
} 
```
核心实现思想：用 `mat` 数组记录元素是否出现，计算前缀和 `s` 数组，枚举元素及其倍数，判断是否满足条件。

- **作者：Alarm5854 (4星)**
    - **关键亮点**：详细分析了时间复杂度，代码中对边界情况进行了处理，如对 $c$ 取 `min` 防止越界。
    - **核心代码**：
```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e6+7;
ll read(){
    char c;
    ll x=0,f=1;
    while(!isdigit(c=getchar()))
        f-=2*(c=='-');
    while(isdigit(c)){
        x=x*10+f*(c^48);
        c=getchar();
    }
    return x;
}
int T,n,c,a[N],vis[N],s[N];
void solve(){
    n=read();
    c=read();
    for(int i=1;i<=c;++i){
        vis[i]=0;
        s[i]=0;
    }
    for(int i=1;i<=n;++i){
        a[i]=read();
        ++s[a[i]];
        vis[a[i]]=1;
    }
    for(int i=1;i<=c;++i)
        s[i]+=s[i-1];
    for(int i=1;i<=c;++i){
        if(!vis[i])
            continue;
        for(int j=1;i*j<=c;++j){
            int l=i*j;
            int r=min(c,i*(j+1)-1);
            if(s[r]>s[l-1]){
                if(!vis[j]){
                    puts("No");
                    return;
                }
            }
        }
    }
    puts("Yes");
}
int main(){
    T=read();
    while(T--)
        solve();
    return 0;
}
```
核心实现思想：用 `vis` 数组记录元素是否出现，计算前缀和 `s` 数组，枚举元素及其倍数，判断是否满足条件，同时处理边界情况。

### 最优关键思路或技巧
- **枚举倍数优化**：将直接枚举因数的 $O(n^2)$ 复杂度算法，优化为枚举倍数，利用 $\lfloor \frac{x}{y} \rfloor = k$ 时，$x$ 一定在 $[y \times k , y \times (k+1)-1]$ 这个范围的性质，降低复杂度。
- **前缀和优化**：使用前缀和可以在 $O(1)$ 时间内判断一个区间内是否存在元素，提高查询效率。

### 拓展思路
同类型题或类似算法套路：在处理涉及因数、倍数关系的判断问题时，都可以考虑将枚举因数转化为枚举倍数，并利用前缀和、差分等数据结构优化查询和更新操作。

### 推荐洛谷题目
- P1886 滑动窗口 /【模板】单调队列
- P1115 最大子段和
- P3374 【模板】树状数组 1

### 个人心得摘录与总结
- **Ezis**：提醒不要把整个数组清空，否则时间会爆炸，强调了在多组测试数据中注意初始化的效率问题。

---
处理用时：57.87秒