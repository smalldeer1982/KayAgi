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

帮助小象找到满足上述条件的 $d$ 的数量。

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
- **思路**：所有题解核心思路一致，都是枚举 $x$ 的因数，判断因数与 $x$ 是否有相同数字，为避免超时，只枚举到 $\sqrt{x}$，同时处理 $x/i$ 这个因数，并注意去重。
- **算法要点**：
    - 标记 $x$ 的每一位数字。
    - 枚举 $1$ 到 $\sqrt{x}$ 的数，判断其是否为 $x$ 的因数。
    - 对每个因数 $i$ 和 $x/i$，判断是否与 $x$ 有相同数字。
    - 避免 $i = x/i$ 时重复计数。
- **解决难点**：
    - **超时问题**：通过只枚举到 $\sqrt{x}$ 优化时间复杂度，从 $O(x)$ 降至 $O(\sqrt{x})$。
    - **重复计数**：判断 $i$ 是否等于 $x/i$，避免重复计算。
    - **判断相同数字**：使用数组标记数字是否出现，避免嵌套循环判断，优化时间复杂度。

### 所选题解
- **bigclever（5星）**：
    - **关键亮点**：思路清晰，代码简洁，使用 `map` 标记数字，函数封装判断逻辑，可读性强。
    - **核心代码**：
```cpp
map<int,bool> a,b;
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
- **221B（4星）**：
    - **关键亮点**：详细分析超时原因并给出优化方案，使用快读快写，代码注释丰富。
    - **个人心得**：提交八次总结出 TLE 问题主要在判断相同数字和寻找因数部分，通过优化判断方式和枚举范围解决超时问题。
    - **核心代码**：
```cpp
int b[100001];
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
- **togeth1（4星）**：
    - **关键亮点**：代码有详细注释，将重复部分封装成函数，提高代码可读性和可维护性。
    - **核心代码**：
```cpp
bool f[10010],s[10010];
void init(){
    int t=n;
    while(t){
        f[t%10] = 1;
        t /= 10;	
    }
}
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

### 最优关键思路或技巧
- **枚举优化**：只枚举到 $\sqrt{x}$，同时处理 $x/i$ 这个因数，将时间复杂度从 $O(x)$ 降至 $O(\sqrt{x})$。
- **数字标记**：使用数组或 `map` 标记数字是否出现，避免嵌套循环判断相同数字，优化时间复杂度。
- **函数封装**：将判断相同数字的逻辑封装成函数，提高代码可读性和可维护性。

### 拓展思路
同类型题目可能会改变判断条件，如判断因数与 $x$ 的数字和是否满足特定关系等，但核心思路依然是枚举因数并进行条件判断。类似算法套路包括枚举优化和标记数组的使用。

### 推荐题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：考察因数和最大公约数、最小公倍数的知识。
- [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)：需要枚举因数并统计满足条件的数量。
- [P2613 有理数取余](https://www.luogu.com.cn/problem/P2613)：涉及因数和取模运算。 

---
处理用时：30.44秒