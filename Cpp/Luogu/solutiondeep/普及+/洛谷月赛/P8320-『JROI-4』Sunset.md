# 题目信息

# 『JROI-4』Sunset

## 题目背景

写不出优美的文字，索性不放背景了。【背景待填充】

> 由于这只是个 C，出题人打算良心点，于是加了几个 $0$（指交互次数）（确信）——验题人注。

## 题目描述

**这是一道交互题。**

落日可以抽象成一个序列 $\{a_n\}$.

$\{a_n\}$ 是一个 $1\sim n$ 的排列。

你还有一个数列 $\{d_n\}$，为**当前** $a$ 数列的前缀最大值。

换言之，
$$d_i=\max_{j=1}^i \{a_j\}$$

注意：根据前文的定义，$\{d_n\}$ 可能随着 $\{a_n\}$ 数列的改变而改变。

您可以进行两种不同的操作：

- 指定一个 $i$，询问对于当前的 $a$ 数列， $d_{1\sim i}$ 中有几个不同的值。
- 指定一个 $i$，使得 $a_i\leftarrow 0$.

请使用不超过 $5500$ 次操作求出**原排列**。

**保证交互库是静态的，即交互库不会在交互过程中改变 $a$ 数列。**

## 说明/提示

**样例仅供理解交互过程，可能不符合逻辑。**

【样例解释】

初始的序列 $a$ 为 `1 2 3`，$d$ 为 `1 2 3`.

在对交互库输出了形如 `? 2 2` 的命令后，序列 $a$ 变为 `1 0 3`，$d$ 变为 `1 1 3`，此时 $d_1\sim d_3$ 中有 $2$ 种不同的值，分别是 $1,3$.



------------


可供选手参考的资料：[OI Wiki-交互题](https://oi-wiki.org/contest/interaction/) **|** [猜数（IO交互版）
](https://www.luogu.com.cn/problem/P1733)



------------

## 数据范围
- 对于 $10\%$ 的数据，$T=1$；
- 对于 $30\%$ 的数据，$n\le 70$；
- 对于另外 $20\%$ 的数据，保证数列 $a$ 随机生成；
- 对于全部数据：$T \leq 10,1\leq n\leq 500$。

## 样例 #1

### 输入

```
1

3

1

2

3


2

```

### 输出

```



? 1 1

? 1 2

? 1 3

? 2 2
? 1 3

! 1 2 3```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均是利用前缀最大值数组\(d\)的性质，通过二分查找确定原排列\(a\)中从大到小的每个数的位置。具体做法为：利用操作一询问\(d_{1 \sim i}\)不同值的个数，结合二分查找找到满足条件的位置，确定当前最大值的位置后，通过操作二将该位置值设为\(0\)，重复此过程直至还原整个排列。各题解在思路清晰度、代码可读性、优化程度等方面有所差异。

### 所选的题解
#### 作者：D2T1 (4星)
- **关键亮点**：思路清晰，先分析操作二的作用，引出计算最大值并消除其影响的解题方向，利用二分查找确定最大值位置，代码简洁且使用记忆化减少查询次数。
```cpp
// 询问函数，若x为1直接返回1，否则向交互库询问并返回结果
int ask(int x){
    if(x == 1) return 1;
    printf("? 1 %d\n", x);
    fflush(stdout);
    int t; scanf("%d", &t);
    return t;
}

// 获取当前最大值位置的递归函数
int getmx(int l, int r){
    if(l == r) return l;
    int mid = l + r >> 1;
    int t = ra, tt = ask(mid);
    if(t == tt){
        ra = tt;
        return getmx(l, mid);
    } else {
        ra = t;
        return getmx(mid+1, r);
    }
}

int main(){
    int t,n; scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = n; i; -- i){
            ra = ask(n);
            int k = getmx(1, n);
            ans[k] = i;
            printf("? 2 %d\n", k);
            fflush(stdout);
        }
        printf("!");
        for(int i = 1; i <= n; ++ i) printf(" %d", ans[i]); puts("");
        fflush(stdout);
    }
    return 0;
} 
```
核心实现思想：`ask`函数负责与交互库通信获取询问结果，`getmx`函数通过二分递归查找当前最大值位置，`main`函数控制流程，循环\(n\)次找到每个最大值位置并记录，最后输出结果。

#### 作者：TheSky233 (4星)
- **关键亮点**：详细阐述了暴力解法及优化思路，从\(O(n^2)\)的暴力做法过渡到\(O(n \log_2 n)\)的二分优化，思路循序渐进，易于理解。
```cpp
int ask(int o){//模拟1操作
    int xx;
    cout<<"? 1 "<<o<<'\n';
    fflush(stdout);
    cin>>xx;
    return xx;
}

int main(){
    cin>>T;
    while(T--){
        cin>>n;
        now=n;
        for(int k=1;k<=n;k++){
            kkk=ask(n);
            int l=1,r=n;
            while(l<=r){
                int mid=(l+r)>>1;
                if(ask(mid)<kkk) l=mid+1;
                else r=mid-1,mpos=mid;
            }
            a[mpos]=now;
            now--;
            cout<<"? 2 "<<mpos<<'\n';
            fflush(stdout);
        }
        cout<<"! "; fflush(stdout);
        for(int i=1;i<=n;i++){
            cout<<a[i]<<' '; fflush(stdout); 
        }
        memset(a,0,sizeof(a));
    }
    return 0;
}
```
核心实现思想：`ask`函数用于询问交互库，`main`函数中，外层循环\(n\)次，每次通过二分查找找到当前最大值位置并记录，更新当前最大值，将找到的最大值位置设为\(0\)，最后输出结果。

#### 作者：Fire_Raku (4星)
- **关键亮点**：通过举例直观地展示如何利用询问结果确定最大值位置，代码简洁明了，详细注释便于理解。
```cpp
int main(){
    int t = read(); 
    while(t--){
        int n = read(), d, cnt ; 
        cnt = n ; 
        for(int i = 1 ; i <= n ; i++){ 
            cout << "? 1 " << n << endl ; 
            fflush(stdout) ; 
            d = read() ; 
            int l = 1, r = n, f, x ; 
            while(l <= r){ 
                int mid = (l + r) / 2 ; 
                cout << "? 1 " << mid << endl ; 
                fflush(stdout) ; 
                x = read() ; 
                if(x < d) l = mid + 1 ; 
                else f = mid, r = mid - 1 ; 
            }
            ans[f] = cnt ; 
            cnt-- ; 
            cout << "? 2 " << f << endl ; 
            fflush(stdout) ; 
        }
        cout << "! " ;
        for(int i = 1 ; i <= n ; i++) cout << ans[i] << " " ; 
        cout << endl ; 
        fflush(stdout) ; 
    } 
    return 0 ; 
} 
```
核心实现思想：通过外层循环\(n\)次，每次先询问得到当前最大值对应的询问结果，再通过二分查找找到最大值位置，记录并更新当前最大值，将找到的最大值位置设为\(0\)，最后输出结果。

### 最优关键思路或技巧
利用前缀最大值数组\(d\)单调不减的性质，通过二分查找确定当前最大值在原排列中的位置，每次找到最大值后将其置零，使次大值成为新的最大值，重复操作还原原排列。这种利用数据性质结合二分查找优化的思维方式是解题关键。

### 可拓展之处
同类型题可拓展到其他交互题，类似算法套路为通过分析题目给定的操作和数据性质，寻找单调性或其他规律，利用二分查找等方式优化求解过程。例如在一些需要确定序列特定元素位置的交互题中，可尝试分析相关数组性质，利用类似思路解决。

### 推荐题目
- [P1733 猜数（IO交互版）](https://www.luogu.com.cn/problem/P1733)：基础的交互题，有助于理解交互题的基本形式和思路。
- [P3957 [NOIP2017 普及组] 跳房子](https://www.luogu.com.cn/problem/P3957)：可通过分析数据性质，利用二分查找优化解题，与本题利用性质优化思路类似。
- [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：同样运用二分查找解决问题，可加深对二分优化类题目的理解。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：64.95秒