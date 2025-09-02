# 题目信息

# Madoka and the Best School in Russia

## 题目描述

- 如果 $n$ 是 $d$ 的倍数，则称 $n$ 为“好数”；
- 如果 $n$ 是“好数”且不能写成任意两个“好数”之积，则称 $n$ 是“美丽数”。

$T$ 组询问，每组询问给定两个正整数 $x,d$，保证 $x$ 是好数，问 $x$ 是否有至少两种方式写为至少一个“美丽数”之积。如果是，输出 `YES`；否则输出 `NO`。

注意输出对大小写不敏感。

## 样例 #1

### 输入

```
8
6 2
12 2
36 2
8 2
1000 10
2376 6
128 4
16384 4```

### 输出

```
NO
NO
YES
NO
YES
YES
NO
YES```

# AI分析结果

### 题目分类
数学

### 综合分析与结论
这些题解核心思路都是先将 \(x\) 表示为 \(x = d^k\times s\)（\(d\nmid s\)）的形式，再对 \(k\)、\(s\)、\(d\) 进行分类讨论来判断 \(x\) 是否有至少两种方式写为至少一个“美丽数”之积。
- **思路对比**：各题解分类讨论的顺序和细节略有不同，但整体逻辑一致。如 StarLbright40 从 \(k\) 的取值开始逐步细化讨论；Feyn 先考虑 \(x\) 不是质数的情况，再处理 \(x\) 是质数时对 \(d\) 的分析。
- **算法要点**：都需要实现质数判断函数，时间复杂度大多为 \(O(T\sqrt{x})\)。
- **解决难点**：难点在于对各种情况的全面分类讨论，尤其是 \(d\) 为合数且 \(s\) 为质数时的情况。

### 所选题解
- **StarLbright40（5星）**
    - **关键亮点**：思路清晰，分类讨论详细且有条理，代码简洁易读。
- **清烛（4星）**
    - **关键亮点**：结合样例分析性质，对各种情况的解释较为详细，有助于理解。
- **JS_TZ_ZHR（4星）**
    - **关键亮点**：对每种情况的分析和构造方案有详细说明，逻辑完整。

### 重点代码
#### StarLbright40
```cpp
#include<cstdio>
using namespace std;
int T,x,d,k;
bool check(int n){
    if(n<4) return 1;
    if(n%2==0||n%3==0) return 0;
    for(int i=5;i*i<=n;i+=6)
        if(n%i==0||n%(i+2)==0) return 0;
    return 1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&x,&d);
        for(k=0;x%d==0;x/=d,++k);
        if(k<2) printf("NO\n");
        else if(!check(x)) printf("YES\n");
        else if(check(d)) printf("NO\n");
        else printf(k>(x*x==d)+2?"YES\n":"NO\n");
    }
    return 0;
}
```
**核心实现思想**：先计算 \(x\) 中 \(d\) 的幂次 \(k\)，然后根据 \(k\)、\(x\) 是否为质数、\(d\) 是否为质数以及 \(x^2\) 与 \(d\) 的关系进行分类判断。

#### 清烛
```cpp
bool isPrime(int x) {
    for (int i = 2; 1ll * i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}

int main() {
    int T; read(T);
    while (T--) {
        int x, d; read(x, d);
        int xx = x, cnt = 0;
        while (!(xx % d)) xx /= d, ++cnt;
        if (cnt == 1) {
            print("No");
        } else if (cnt == 2) {
            if (isPrime(xx)) print("No");
            else print("Yes");
        } else {
            if (!isPrime(xx)) print("Yes");
            else if (isPrime(d)) print("No");
            else if (d == 1ll * xx * xx && cnt == 3) print("No");
            else print("Yes");
        }
    }
    return output(), 0;
}
```
**核心实现思想**：同样先计算 \(x\) 中 \(d\) 的幂次 \(cnt\)，再根据 \(cnt\)、\(xx\) 是否为质数、\(d\) 是否为质数以及 \(d\) 与 \(xx^2\) 的关系进行分类输出结果。

#### JS_TZ_ZHR
```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long 
using namespace std;
int T,x,d,cnt,p[N],tot,num;
bool check(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0)return 0;
    }
    return 1;
}
bool Check(int x){
    int sum=0;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            sum=i;
            break;
        }
    }
    while(x%sum==0)x/=sum,num++;
    return (x==1);
}
signed main(){
    cin>>T;
    while(T--){
        cin>>x>>d;
        cnt=num=0;
        int tmp=x;
        while(tmp%d==0)tmp/=d,cnt++;
        if(cnt==1){
            puts("NO");
            continue;
        }
        if(check(d)||cnt==2){
            if(tmp==1||check(tmp))puts("NO");
            else puts("YES");
            continue;
        }
        if(Check(d)){
            if(cnt==3){
                if(num==2&&(d%tmp==0&&tmp!=1))puts("NO");
                else puts("YES");
            }
            else puts("YES");
            continue;
        }
        puts("YES");
    }
} 
```
**核心实现思想**：先计算 \(x\) 中 \(d\) 的幂次 \(cnt\)，然后根据 \(cnt\)、\(d\) 是否为质数、\(tmp\) 是否为质数以及 \(d\) 的因数分解情况进行分类判断输出。

### 最优关键思路或技巧
- 先将 \(x\) 分解为 \(x = d^k\times s\) 的形式，方便后续分类讨论。
- 利用质数判断函数辅助分类讨论，简化逻辑。

### 拓展思路
同类型题目可能会改变“好数”和“美丽数”的定义，或者增加更多条件限制，解题时仍可采用分类讨论的方法，先对输入进行合理分解，再根据不同情况进行判断。

### 推荐洛谷题目
- P1075 [NOIP2012 普及组] 质因数分解
- P1572 [NOIP2010 提高组] 计算系数
- P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题

### 个人心得
题解中未包含个人心得。 

---
处理用时：42.15秒