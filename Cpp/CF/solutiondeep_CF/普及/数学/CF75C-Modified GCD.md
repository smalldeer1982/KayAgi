# 题目信息

# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11
```

### 输出

```
3
-1
9
```

# AI分析结果

### 题目内容重写（中文）

#### 修改后的GCD

## 题目描述

好吧，这是另一道数学课上的任务。在数学中，GCD是最大公约数，计算两个正整数的GCD是一个简单的任务。

两个正整数的公约数是指能同时整除这两个数的数。

但你的老师想给你一个更难的任务，在这个任务中，你需要找到两个整数$a$和$b$的最大公约数$d$，且$d$必须在给定的范围$[low, high]$内，即$low<=d<=high$。有可能在给定范围内没有公约数。

你将得到两个整数$a$和$b$，然后有$n$个查询。每个查询是一个范围$[low, high]$，你需要回答每个查询。

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11
```

### 输出

```
3
-1
9
```

### 题解分析与结论

本题的核心思路是：**两个数的公约数一定是它们的最大公约数的约数**。因此，我们可以先求出$a$和$b$的最大公约数$g$，然后枚举$g$的所有约数，再对这些约数进行排序，最后通过二分查找来快速回答每个查询。

### 精选题解

#### 题解1：ADay (赞：7) - 4星

**关键亮点：**
1. 通过预处理公约数，使用`upper_bound`进行二分查找，时间复杂度为$O(\log n)$。
2. 代码简洁，逻辑清晰，适合初学者理解。

**核心代码：**
```cpp
int main() {
    scanf("%d%d",&a,&b);
    g=__gcd(a,b);
    for(int i=1;i*i<=g;i++) if(g%i==0) v.push_back(i),v.push_back(g/i);
    scanf("%d",&a);
    sort(v.begin(),v.end());
    while(~scanf("%d%d",&x,&y)) {
        int pos=upper_bound(v.begin(),v.end(),y)-v.begin();
        if(v[pos-1]<x) puts("-1");
        else printf("%d\n",v[pos-1]);
    }
    return 0;
}
```

#### 题解2：tobie (赞：7) - 4星

**关键亮点：**
1. 使用反证法证明了公约数一定是最大公约数的约数，增强了题解的理论性。
2. 通过手动实现二分查找，适合对STL不熟悉的读者。

**核心代码：**
```cpp
int main() {
    scanf("%d%d",&x,&y);
    z=gcd(x,y);
    for(int i=1;i*i<=z;i++) if(z%i==0) ans[++ans[0]]=i,ans[++ans[0]]=z/i;
    sort(ans+1,ans+ans[0]+1);
    scanf("%d",&t);
    while(t--) {
        scanf("%d%d",&a,&b);
        r=-1;
        ll=1,rr=ans[0];
        while(ll<=rr) {
            mid=(ll+rr)/2;
            if(ans[mid]<=b) r=mid,ll=mid+1;
            else rr=mid-1;
        }
        if(a<=ans[r]) printf("%d\n",ans[r]);
        else printf("-1\n");
    }
    return 0;
}
```

#### 题解3：xiaoPanda (赞：2) - 4星

**关键亮点：**
1. 使用`set`存储公约数，自动去重和排序，简化了代码逻辑。
2. 通过`upper_bound`进行二分查找，代码简洁高效。

**核心代码：**
```cpp
void solve() {
    int l,r;
    cin>>l>>r;
    int ans=*--s.upper_bound(r);
    if(ans>=l) cout<<ans<<endl;
    else cout<<-1<<endl;
}
main() {
    cin >> a >> b >> T;
    w=__gcd(a,b);
    for(int i=1;i*i<=w;i++) if(w%i==0) s.insert(i),s.insert(w/i);
    while (T--) solve();
}
```

### 最优关键思路与技巧

1. **预处理公约数**：先求出$a$和$b$的最大公约数$g$，然后枚举$g$的所有约数，存储并排序。
2. **二分查找**：通过二分查找快速定位符合查询范围的约数，时间复杂度为$O(\log n)$。
3. **使用STL**：利用`upper_bound`和`set`等STL工具简化代码实现。

### 可拓展之处

1. **类似题目**：可以扩展到多个数的最大公约数问题，或者求最小公倍数（LCM）的问题。
2. **算法优化**：在预处理阶段，可以通过更高效的算法（如Pollard's Rho算法）来分解大数的约数。

### 推荐题目

1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1445 [Violet]樱花](https://www.luogu.com.cn/problem/P1445)

### 个人心得摘录

- **调试经历**：在预处理阶段，约数的去重和排序是关键，使用`set`可以自动完成这些操作，避免了手动去重的麻烦。
- **顿悟感想**：通过反证法证明公约数一定是最大公约数的约数，这一理论性的思考帮助我更深入地理解了问题的本质。

---
处理用时：43.93秒