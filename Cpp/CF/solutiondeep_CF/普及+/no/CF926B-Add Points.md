# 题目信息

# Add Points

## 题目描述

There are $ n $ points on a straight line, and the $ i $ -th point among them is located at $ x_{i} $ . All these coordinates are distinct.

Determine the number $ m $ — the smallest number of points you should add on the line to make the distances between all neighboring points equal.

## 说明/提示

In the first example you can add one point with coordinate $ 0 $ .

In the second example the distances between all neighboring points are already equal, so you shouldn't add anything.

## 样例 #1

### 输入

```
3
-5 10 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
100 200 400 300 600 500
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
10 9 0 -1
```

### 输出

```
8
```

# AI分析结果

### 题目内容
# 添加点

## 题目描述
在一条直线上有\(n\)个点，其中第\(i\)个点位于\(x_i\)处。所有这些坐标都是不同的。
确定数字\(m\)，即你应该在直线上添加的最少点数，以使所有相邻点之间的距离相等。

## 说明/提示
在第一个示例中，你可以添加一个坐标为\(0\)的点。
在第二个示例中，所有相邻点之间的距离已经相等，所以你无需添加任何点。

## 样例 #1
### 输入
```
3
-5 10 5
```
### 输出
```
1
```

## 样例 #2
### 输入
```
6
100 200 400 300 600 500
```
### 输出
```
0
```

## 样例 #3
### 输入
```
4
10 9 0 -1
```
### 输出
```
8
```

• **算法分类**：数学
• **综合分析与结论**：这些题解的核心思路均是先将给定的点坐标排序，然后通过求相邻点距离的最大公约数来确定最终相邻点的相等距离，进而计算出需要添加的最少点数。主要差异在于代码实现细节、求最大公约数的方式（自定义函数或使用C++自带的`__gcd`函数）以及计算添加点数的具体步骤。所有题解思路清晰，只是部分代码在可读性和简洁性上有所差异。
• **所选的题解**：
  - **作者：Luo_gu_ykc (5星)**
    - **关键亮点**：思路阐述清晰，代码简洁明了，详细解释了每一步的操作，先通过排序整理数据，再用欧几里得算法求最大公约数，最后算出需要添加的点数。
    - **重点代码**：
```cpp
int gcd(int x, int y){ // 欧几里得算法求 gcd
    return y == 0? x : gcd(y, x % y);
} 
signed main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n); 
    int k = a[2] - a[1];
    for(int i = 3; i <= n; i++){
        k = gcd(k, a[i] - a[i - 1]); 
    }
    int sum = 0;
    for(int i = 2; i <= n; i++){
        sum += ((a[i] - a[i - 1]) / k) - 1; 
    }
    cout << sum;
    return 0;
}
```
    - **核心实现思想**：先读入数据并排序，通过循环求相邻点距离的最大公约数`k`，再通过循环计算每段需添加的点数并累加。
  - **作者：_Flame_ (4星)**
    - **关键亮点**：将题意简化为求最少加入多少个数使序列变为等差数列，代码实现完整，包含自定义的输入输出函数。
    - **重点代码**：
```cpp
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
void solve(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    sort(a+1,a+n+1);
    for(int i=2;i<=n;i++){
        mn=gcd(mn,a[i]-a[i-1]);
    }
    write((a[n]-a[1])/mn-n+1);
    puts("");
    return ;
}
```
    - **核心实现思想**：先读入数据排序，求出相邻点距离的最大公约数`mn`，最后根据公式计算并输出需添加的点数。
  - **作者：cppcppcpp3 (4星)**
    - **关键亮点**：对思路的数学分析较为清晰，明确指出要使插入点数尽量少，需让新的相邻点距离`gcd`最大，复杂度分析准确。
    - **重点代码**：
```cpp
main(){
    n=wrd();
    for(int i=1;i<=n;++i) a[i]=wrd();
    sort(a+1,a+n+1),d=a[n]-a[n-1];
    for(int i=2;i<n;++i) d=__gcd(d,a[i]-a[i-1]);
    return printf("%lld",(a[n]-a[1])/d-(n-1)),0; 
}
```
    - **核心实现思想**：读入数据排序后，利用`__gcd`函数求相邻点距离的最大公约数`d`，最后根据公式计算并输出需添加的点数。
• **最优关键思路或技巧**：将问题转化为求等差数列的公差，通过求相邻点距离的最大公约数来确定最终相邻点的相等距离，这是解决本题的关键数学思维。在代码实现上，合理利用排序和求最大公约数的函数能简化代码。
• **同类型题或类似算法套路**：此类题目通常围绕数列规律和数学运算，类似套路是将实际问题转化为数学模型，如等差数列、最大公约数等相关问题求解。
• **推荐题目**：
  - [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)
  - [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)
  - [P1226 快速幂](https://www.luogu.com.cn/problem/P1226)
• **个人心得**：无 

---
处理用时：40.94秒