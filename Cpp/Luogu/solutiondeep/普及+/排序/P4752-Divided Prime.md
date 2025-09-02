# 题目信息

# Divided Prime

## 题目描述

给定一个数字$A$，这个$A$由$a_1,a_2,\cdots,a_N$相乘得到。

给定一个数字$B$，这个$B$由$b_1,b_2,\cdots,b_M$相乘得到。

如果$\frac{A}{B}$是一个质数，请输出`YES`，否则输出`NO`。



## 说明/提示

$1 \le N \le 100000$

$0 \le M \le N$

$1 \le a_i,b_i \le 10^{12}$

$1 \le T \le 10$

$\sum N \le 100000$

## 样例 #1

### 输入

```
2
3 2
5 7 7
5 7
4 2
5 7 7 7
5 7```

### 输出

```
YES
NO```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是利用 “$b$ 中数字出现次数不多于 $a$ 中” 这一条件，对 $a$ 和 $b$ 进行约分，判断约分后结果是否为质数。
1. **思路与算法要点**：
    - **约分**：多数题解通过排序后比较数组元素、使用 `map` 记录元素出现次数、利用异或运算等方式进行约分。
    - **判断质数**：常见方法是朴素的根号 $n$ 试除法，部分题解使用了 Miller - Rabbin 等更高效的质数判断算法。
2. **解决难点**：
    - **大数据处理**：由于 $a_i$ 和 $b_i$ 数值大且数量多，不能直接相乘再除，需通过上述约分方法避免大数运算。
    - **质数判断优化**：对于大数字的质数判断，朴素试除法在大数据下效率低，需考虑更优算法如 Miller - Rabbin 算法。

### 所选的题解
#### 作者：Iowa_BattleShip (5星)
- **关键亮点**：利用异或运算巧妙实现约分，避免了复杂的数组操作和排序，代码简洁高效，思路独特新颖。
- **个人心得**：通过分析题目条件，想到利用异或性质和约分的联系，并且通过特殊数据发现其他题解的问题，对题目理解深入。
```cpp
// 快读
ll re() {
    ll x = 0;
    char c = getchar();
    bool p = 0;
    for(;c<'0'||c>'9';c=getchar())
        p=(c=='-'||p)?1:0;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+(c-'0');
    return p?-x:x;
}
// 判断是否是质数
bool judge(ll x) {
    int i;
    if(!x||x==1)
        return false;
    for(i=2;1LL*i*i<=x;i++)
        if(!(x%i))
            return false;
    return true;
}
int main() {
    int i,n,m,t,s;
    ll x,y;
    t=re();
    while(t--) {
        x=y=s=0;
        n=re();
        m=re();
        for(i=1;i<=n+m;i++) {
            y=re();
            if(y!=1) {
                i>n?s--:s++;
                x^=y;
            }
        }
        if(s==1&&judge(x))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```
核心实现思想：通过快读函数读取数据，在读取 $a$ 和 $b$ 的元素过程中，利用异或运算将相同元素抵消，同时统计 $a$ 比 $b$ 多的非 1 元素个数，最后判断剩余元素是否为质数。

#### 作者：FlierKing (4星)
- **关键亮点**：思路清晰，先排序再通过双指针法删除 $a$ 中与 $b$ 相同的元素，最后判断剩余元素组成的数是否为质数，代码结构清晰，易理解。
```cpp
// 快读
ll inline read() {
    ll x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
// 判断质数
int check(int x) {
    for (int i=2,to=sqrt(x);i<=to;i++)
        if (x%i==0) return 2;
    return 1;
}
int main() {
    T=read();
    while (T--) {
        memset(u,0,sizeof(u));
        n=read(),m=read();
        for (int i=1;i<=n;i++)
            a[i]=read();
        sort(a+1,a+n+1,cmp);
        for (int i=1;i<=m;i++)
            b[i]=read();
        sort(b+1,b+m+1,cmp);
        for (int i=1,j=1;i<=m;i++) {
            while (b[i]<a[j]) j++;
            u[j]=true;j++;
        }
        cnt=0;
        for (int i=1;i<=n;i++)
            if (!u[i]) {
                if (a[i]==1) continue;
                cnt+=check(a[i]);
                if (cnt>1) break;
            }
        puts(cnt==1?"YES":"NO");
    }
    return 0;
}
```
核心实现思想：通过快读读取数据，对 $a$ 和 $b$ 数组排序后，使用双指针法标记 $a$ 中与 $b$ 相同的元素，统计剩余元素中质数的个数，根据个数判断结果。

#### 作者：hawa130 (4星)
- **关键亮点**：使用 `map` 数据结构记录因子出现次数，简洁明了地完成约分操作，然后根据 `map` 的状态判断结果是否为质数，代码逻辑清晰。
```cpp
// 读入函数
template<typename Tp> void read(Tp &x) {
    char c = getchar();
    x = 0;
    while (!isdigit(c)) c = getchar();
    do {
        x = (x * 10) + (c ^ 48);
        c = getchar();
    } while (isdigit(c));
}
// 判断质数
bool isprime(long long x) {
    long long tmp = sqrt(x);
    for (long long i = 2; i <= tmp; i++)
        if (!(x % i)) return false;
    return true;
}
int main() {
    read(T);
    while (T--) {
        map<long long, int> cnt;
        read(n), read(m);
        for (int i = 1; i <= n; i++) {
            long long num;
            read(num);
            if (num == 1) continue;
            cnt[num]++;
        }
        for (int i = 1; i <= m; i++) {
            long long num;
            read(num);
            if (num == 1) continue;
            if(!(--cnt[num]))
                cnt.erase(num);
        }
        if (cnt.size()!= 1) printf("NO\n");
        else {
            long long num = cnt.begin()->first;
            int sum = cnt.begin()->second;
            if (sum!= 1) printf("NO\n");
            else if (isprime(num)) printf("YES\n");
            else printf("NO\n");
        }
    }
}
```
核心实现思想：通过自定义读入函数读取数据，利用 `map` 记录 $a$ 和 $b$ 中各因子出现次数，在读取 $b$ 时对 `map` 中对应因子次数减一，根据 `map` 最终状态判断结果是否为质数。

### 最优关键思路或技巧
1. **异或运算约分**：如 Iowa_BattleShip 的题解，利用异或运算 $a \land a = 0$ 的性质，将相同元素异或抵消，巧妙且高效地完成约分，避免了排序等复杂操作。
2. **数据结构选择**：hawa130 使用 `map` 记录因子出现次数，简洁地实现约分和结果判断，充分利用了 `map` 的特性，代码逻辑清晰。

### 可拓展之处
同类型题或类似算法套路：此类题目通常围绕数论知识，特别是质数判断和约分操作。常见套路包括利用数据结构（如 `map`、`set`）记录元素出现次数，运用排序和双指针法处理数组，以及选择合适的质数判断算法。例如在处理多个数的乘积关系并判断结果性质时，可借鉴上述方法。

### 相似知识点的洛谷题目
1. **P1217 [USACO1.5]回文质数 Prime Palindromes**：结合质数判断和回文数判断，需优化算法避免超时。
2. **P3383 【模板】线性筛素数**：考察线性筛素数算法，可加深对质数筛选的理解。
3. **P5736 【深基7.例12】质数筛**：通过不同的质数筛选方法解决问题，强化质数相关知识。 

---
处理用时：68.76秒