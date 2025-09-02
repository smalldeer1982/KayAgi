# 题目信息

# フェーン現象 (Foehn Phenomena)

## 题目描述

### 题目简述

你知道$N+1$个地点的海拔$A_i$,编号为$0 \dots N$,有风从$0$吹向$N$,想让你求出地点$N$的风的温度.

保证$A_0=0$

规则：
- 如果$A_i=A_{i+1}$风的温度不变.
- 如果$A_i>A_{i+1}$由于海拔降低,风的温度会上升$(A_i-A_{i+1})\times T$度
- 如果$A_i<A_{i+1}$由于海拔升高,风的温度会下降$(A_{i+1}-A_i)\times S$度

## 样例 #1

### 输入

```
3 5 1 2
0
4
1
8
1 2 2
1 1 -2
2 3 5
1 2 -1
1 3 5```

### 输出

```
-5
-7
-13
-13
-18```

## 样例 #2

### 输入

```
2 2 5 5
0
6
-1
1 1 4
1 2 8```

### 输出

```
5
-35```

## 样例 #3

### 输入

```
7 8 8 13
0
4
-9
4
-2
3
10
-9
1 4 8
3 5 -2
3 3 9
1 7 4
3 5 -1
5 6 3
4 4 9
6 7 -10```

### 输出

```
277
277
322
290
290
290
290
370```

# AI分析结果

### 题目内容（中文重写）

#### 题目描述

你知道$N+1$个地点的海拔$A_i$，编号为$0 \dots N$，有风从$0$吹向$N$，想让你求出地点$N$的风的温度。

保证$A_0=0$

规则：
- 如果$A_i=A_{i+1}$，风的温度不变。
- 如果$A_i>A_{i+1}$，由于海拔降低，风的温度会上升$(A_i-A_{i+1})\times T$度。
- 如果$A_i<A_{i+1}$，由于海拔升高，风的温度会下降$(A_{i+1}-A_i)\times S$度。

### 题解分析与结论

该题的核心在于利用差分数组来高效处理区间修改和单点查询。由于每次修改只会影响差分数组的两个端点，因此可以通过差分数组来快速计算温度的变化。题解中普遍采用了差分的思想，并结合题目规则进行温度的计算和更新。

### 所选高分题解

#### 1. 作者：yangrunze (赞：25)  
**评分：5星**  
**关键亮点：**  
- 详细解释了差分数组的概念及其在区间修改中的应用。
- 通过差分数组优化了温度的计算，避免了每次修改后遍历整个数组。
- 提供了完整的代码实现，并解释了快读的优化技巧。

**核心代码：**
```cpp
ll temp(ll x){
    if(x>=0) return -x*s;
    else return -x*t;
}
int main(){
    n=read();q=read();s=read();t=read();
    ll last=0;
    for(register int i=0;i<=n;i++){
        ll k=read();
        a[i]=k-last;
        last=k;
        ans+=temp(a[i]);
    }
    for(register int i=1;i<=q;i++){
        ll l=read(),r=read(),k=read();
        ans-=temp(a[l]);
        a[l]+=k;
        ans+=temp(a[l]);
        if(r<n){
            ans-=temp(a[r+1]);
            a[r+1]-=k;
            ans+=temp(a[r+1]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

#### 2. 作者：顾z (赞：15)  
**评分：4星**  
**关键亮点：**  
- 简洁明了地解释了差分数组的应用。
- 通过差分数组直接计算温度变化，避免了不必要的遍历。
- 提供了完整的代码实现，并解释了如何处理边界情况。

**核心代码：**
```cpp
inline long long get(long long x){
    return  x > 0 ? -(x*s) : -(x*t) ; 
}
int main(){
    in(n),in(q),in(s),in(t);
    in(last);
    for(R int i=1;i<=n;i++){
        R long long x;
        in(x);
        A[i]=x-last;
        last=x;
        ans+=get(A[i]);
    }
    for(R long long x,y,z;q;q--){
        in(x),in(y),in(z);
        ans-=get(A[x]);
        A[x]+=z;
        ans+=get(A[x]);
        if(y!=n) ans-=get(A[y+1]),A[y+1]-=z,ans+=get(A[y+1]);
        printf("%lld\n",ans);
    }
    return 0;
}
```

#### 3. 作者：Viktley (赞：4)  
**评分：4星**  
**关键亮点：**  
- 通过差分数组优化了温度的计算，避免了每次修改后遍历整个数组。
- 提供了完整的代码实现，并解释了如何处理边界情况。

**核心代码：**
```cpp
ll solve(ll x){
    if(x >= 0) return x * s;
    return x * t;
}
int main(){
    scanf("%lld%lld%lld%lld", &n, &q, &s, &t);
    for(ll i = 0; i <= n; i++)
        scanf("%lld", &a[i]), p[i] = a[i] - a[i - 1], ans -= solve(p[i]);
    while(q--){
        scanf("%lld%lld%lld", &x, &y, &z);
        ans += solve(p[x]), p[x]+= z, ans -= solve(p[x]);
        if(y < n) ans += solve(p[y + 1]), p[y + 1]  -= z, ans -= solve(p[y + 1]);
        printf("%lld\n", ans); 
    }
    return 0;
}
```

### 最优关键思路与技巧

1. **差分数组的应用**：通过差分数组可以高效处理区间修改，每次修改只需更新差分数组的两个端点。
2. **温度计算的优化**：利用差分数组直接计算温度变化，避免了每次修改后遍历整个数组。
3. **边界处理**：特别注意当修改区间右端点为$n$时，不需要更新差分数组的$n+1$项。

### 可拓展之处

- **类似题目**：可以拓展到其他需要处理区间修改和单点查询的问题，如区间和、区间最大值等。
- **数据结构**：可以进一步学习树状数组、线段树等数据结构来处理更复杂的区间操作。

### 推荐题目

1. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：42.73秒