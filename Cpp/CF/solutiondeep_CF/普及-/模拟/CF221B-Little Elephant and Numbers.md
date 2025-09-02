# 题目信息

# Little Elephant and Numbers

## 题目描述

The Little Elephant loves numbers.

He has a positive integer $ x $ . The Little Elephant wants to find the number of positive integers $ d $ , such that $ d $ is the divisor of $ x $ , and $ x $ and $ d $ have at least one common (the same) digit in their decimal representations.

Help the Little Elephant to find the described number.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
# 小象与数字

## 题目描述
小象喜欢数字。

它有一个正整数 $x$。小象想找出正整数 $d$ 的数量，使得 $d$ 是 $x$ 的因数，并且 $x$ 和 $d$ 在它们的十进制表示中至少有一个相同的数字。

帮助小象找到符合上述描述的数字的数量。

## 样例 #1
### 输入
```
1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
10
```
### 输出
```
2
```

### 综合分析与结论
- **思路**：各题解思路基本一致，都是先枚举 $x$ 的因数，为避免超时，只枚举到 $\sqrt{x}$，因为因数成对出现，每找到一个因数 $i$，$x/i$ 也是 $x$ 的因数。然后判断因数与 $x$ 是否有相同数字，有则计数加一。
- **算法要点**：
    - 枚举因数：从 $1$ 到 $\sqrt{x}$ 进行枚举，判断 $i$ 是否为 $x$ 的因数，同时处理 $x/i$。
    - 数字判断：将 $x$ 和因数的每一位数字标记，通过比较标记判断是否有相同数字。
- **解决难点**：
    - 超时问题：通过只枚举到 $\sqrt{x}$ 避免从 $1$ 到 $x$ 枚举的高复杂度。
    - 判重问题：当 $i = x/i$ 时，只计算一次。

### 所选题解
- **bigclever（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `map` 标记数字，提高代码可读性。
    - **核心代码**：
```cpp
bool check(int n){
    b.clear();
    while(n)b[n%10]=true,n/=10;
    for(int i=0;i<=9;i++)
        if(a[i]&&b[i])return true;
    return false;
}
int main(){
    int x,ans=0,t; 
    cin>>x,t=x;
    while(t)a[t%10]=true,t/=10;
    for(int i=1;i<=x/i;i++)
        if(x%i==0){
            ans+=check(i);
            if(x/i!=i)ans+=check(x/i);
        }
    cout<<ans;
    return 0;
}
```
核心思想：`check` 函数用于判断一个数与 $x$ 是否有相同数字，主函数枚举因数并调用 `check` 函数计数。
- **221B（4星）**
    - **关键亮点**：详细分析了可能导致超时的原因，并给出优化方法，同时提供快读快写代码。
    - **个人心得**：提交八次总结出 TLE 是最大问题，判断相同数字和寻找因数部分的朴素做法会超时，给出了优化思路。
    - **核心代码**：
```cpp
int pan(int x) {
    while(x) {
        int t=x%10;
        if(b[t]==1)
            return 1;
        x/=10;
    }
    return 0;
}
int main() {
    int x=read(),s=0;
    int j=x;
    while(j) {
        b[j%10]=1;
        j/=10;
    }
    for(int i=1; i<=sqrt(x); i++) {
        if(x%i==0) {
            if(pan(i)==1)
                ++s;
        }
    }
    for(int i=1; i<sqrt(x); i++) {
        if(x%i==0) {
            if(pan(x/i)==1)++s;
        }
    }
    write(s);
    return 0;
}
```
核心思想：`pan` 函数判断一个数与 $x$ 是否有相同数字，主函数枚举因数并调用 `pan` 函数计数。
- **togeth1（4星）**
    - **关键亮点**：代码有详细注释，将重复部分封装成函数，提高代码可读性和可维护性。
    - **核心代码**：
```cpp
bool check(int x){
    memset(s,0,sizeof(s));
    while(x){
        s[x%10] = 1;
        x /= 10;
    }
    for(int i=0; i<10; i++)
        if(f[i] ==1 && s[i]==1)
            return 1;
    return 0;
} 
signed main(){
    cin>>n;
    init();
    for(int i=1; i*i<=n; i++)
        if(n%i == 0){
            ans += check(i);
            if(n/i!= i)ans += check(n/i);
        }
    cout<<ans;
    return 0;
}
```
核心思想：`check` 函数判断一个数与 $x$ 是否有相同数字，主函数枚举因数并调用 `check` 函数计数。

### 最优关键思路或技巧
- **因数枚举优化**：只枚举到 $\sqrt{x}$，利用因数成对出现的性质，减少不必要的枚举。
- **数字判断优化**：使用标记数组，将判断相同数字的复杂度从 $O(m\times10)$ 降低到 $O(m)$（$m$ 为因数的位数）。

### 可拓展之处
同类型题可能会改变判断条件，如判断因数与 $x$ 的数字和是否满足某种关系，或判断因数与 $x$ 的数字组成的集合是否满足特定条件等。类似算法套路是先对数据进行预处理，再通过枚举和判断的方式求解。

### 推荐题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：考察因数和最大公约数、最小公倍数的知识。
- [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)：涉及因数的统计和枚举。
- [P2602 [ZJOI2010]数字计数](https://www.luogu.com.cn/problem/P2602)：需要对数字的每一位进行处理和统计。

---
处理用时：31.76秒