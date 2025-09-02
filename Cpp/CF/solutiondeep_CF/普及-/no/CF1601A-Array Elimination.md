# 题目信息

# Array Elimination

## 题目描述

有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，每次操作选择 $k$ 个数，将这 $k$ 个数减去他们的与（二进制运算中的与）的和。求哪些 $k$ 可以在有限次操作内使所有数变成 $0$。

## 说明/提示

$1\le t\le10^4,1\le\sum n\le2\times10^5,0\le a_i<2^{30}$。

## 样例 #1

### 输入

```
5
4
4 4 4 4
4
13 7 25 19
6
3 5 3 1 7 1
1
1
5
0 0 0 0 0```

### 输出

```
1 2 4
1 2
1
1
1 2 3 4 5```

# AI分析结果

### 题目内容
# 数组消除

## 题目描述
有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，每次操作选择 $k$ 个数，将这 $k$ 个数减去它们的与（二进制运算中的与）的和。求哪些 $k$ 可以在有限次操作内使所有数变成 $0$。

## 说明/提示
$1 \leq t \leq 10^4, 1 \leq \sum n \leq 2\times10^5, 0 \leq a_i < 2^{30}$。

## 样例 #1
### 输入
```
5
4
4 4 4 4
4
13 7 25 19
6
3 5 3 1 7 1
1
1
5
0 0 0 0 0
```
### 输出
```
1 2 4
1 2
1
1
1 2 3 4 5
```
### 算法分类
数学

### 综合分析与结论
所有题解思路本质一致，均基于将数字转换为二进制后，发现每一位的操作相互独立这一特性。要点在于统计每个二进制位上1的个数，求这些个数的最大公约数（gcd），该gcd的所有因子即为可行的 $k$。同时需特判所有数均为0的情况，此时答案为 $1$ 到 $n$ 的所有数。各题解主要区别在于代码实现细节，如求gcd、因数的方式以及边界处理的写法。

### 所选的题解
- **作者：water_tomato（5星）**
    - **关键亮点**：思路阐述清晰，代码结构完整，模块化程度高。定义了专门的gcd函数和print函数，逻辑清晰易读。
    - **重点代码**：
```cpp
inline int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
vector<int> ans;
inline void print(int x){//求答案
    ans.clear();
    for(int i=1;i<=sqrt(x);i++){
        if(x%i==0){
            ans.push_back(i);
            if(i*i!=x) ans.push_back(x/i);
        }
    }
    sort(ans.begin(),ans.end());
    for(auto x:ans) printf("%d ",x);
    printf("\n");
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);for(int i=0;i<=30;i++) t[i]=0;
        for(int i=1,x;i<=n;i++){
            scanf("%d",&x);
            for(int j=0;j<=30;j++){
                if(x&(1<<j)) t[j]++;//统计个数
            }
        }
        int g=0;
        for(int j=0;j<=30;j++) g=gcd(g,t[j]);//求 gcd
        if(g==0){for(int i=1;i<=n;i++) printf("%d ",i);printf("\n");}//特判全部为 0
        else print(g);
    }
}
```
    - **核心实现思想**：通过`gcd`函数求两个数的最大公约数，`print`函数用于求并输出给定数的所有因子。主函数中，先统计每个二进制位上1的个数存于`t`数组，再求这些个数的gcd，根据gcd是否为0进行不同处理。
- **作者：XL4453（4星）**
    - **关键亮点**：解题思路阐述详细，对复杂度分析清晰，代码简洁明了。
    - **重点代码**：
```cpp
void calc(int num){
    for(int i=0;i<=32;i++)
    if((num>>i)&1)cnt[i]++;
}
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
signed main(){
    scanf("%I64d",&T);
    while(T--){
        scanf("%I64d",&n);
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++){
            scanf("%I64d",&a[i]);
            calc(a[i]);
        }
        int GCD=-1;
        for(int i=0;i<=31;i++)
        if(cnt[i]!=0){
            if(GCD==-1)GCD=cnt[i];
            GCD=gcd(GCD,cnt[i]);
        }
        if(GCD!=-1){
            for(int i=1;i<=GCD;i++)
            if(GCD%i==0)printf("%I64d ",i);
        }
        else{
            for(int i=1;i<=n;i++)
            printf("%I64d ",i);
        }
        printf("\n");
    }
    return 0;
}
```
    - **核心实现思想**：`calc`函数统计一个数二进制表示中每一位1的个数。主函数中，通过循环读取数据并调用`calc`统计，之后求非零的二进制位1个数的gcd，根据gcd是否为-1（即是否存在非零的二进制位1个数）进行不同输出。
- **作者：xfrvq（4星）**
    - **关键亮点**：代码简洁紧凑，直接抓住核心思路，对关键步骤注释清晰。
    - **重点代码**：
```cpp
int gcd(int x,int y){
    return y?gcd(y,x % y):x;
}
int c[32];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        for(int i = 0;i <= 31;++i) c[i] = 0; // 多测清空
        for(int i = 1;i <= n;++i){
            int x;
            scanf("%d",&x);
            for(int j = 0;x;++j,x >>= 1) if(x & 1) ++c[j]; // 每位拆开
        }
        int x = 0;
        for(int i = 0;i <= 31;++i)
            x = gcd(c[i],x);
        for(int i = 1;i <= n;++i) // 当全部数都为0的时候，x=0，x%1~n的所有数也都等于0，就都会输出
            if(x % i == 0) printf("%d ",i);
        printf("\n");
    }
    return 0;
}
```
    - **核心实现思想**：通过`gcd`函数求最大公约数。主函数中，每次读入数据前清空`c`数组用于统计每个二进制位1的个数，之后求这些个数的gcd，最后根据gcd与1到n的数的整除关系输出结果。

### 最优关键思路或技巧
将位运算问题转换为二进制下每一位独立分析，通过统计二进制位上1的个数并求其最大公约数，进而得到满足条件的 $k$。这种将复杂问题按位分解简化的思维方式是解决此类问题的关键。

### 可拓展之处
同类型题常涉及位运算与数学性质结合，类似套路为将数字转换为二进制后分析每一位的特性，根据题目操作确定每一位上数字满足的条件，进而解决问题。

### 洛谷相似题目推荐
- [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
- [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)
- [P1514 引水入城](https://www.luogu.com.cn/problem/P1514) 

---
处理用时：63.10秒