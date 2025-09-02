# 题目信息

# Short Task

## 题目描述

Let us denote by $ d(n) $ the sum of all divisors of the number $ n $ , i.e. $ d(n) = \sum\limits_{k | n} k $ .

For example, $ d(1) = 1 $ , $ d(4) = 1+2+4=7 $ , $ d(6) = 1+2+3+6=12 $ .

For a given number $ c $ , find the minimum $ n $ such that $ d(n) = c $ .

## 样例 #1

### 输入

```
12
1
2
3
4
5
6
7
8
9
10
39
691```

### 输出

```
1
-1
2
3
-1
5
4
7
-1
-1
18
-1```

# AI分析结果

### 题目翻译
# 简短任务

## 题目描述
我们用 $d(n)$ 表示数字 $n$ 的所有因数之和，即 $d(n) = \sum\limits_{k | n} k$ 。

例如，$d(1) = 1$ ，$d(4) = 1 + 2 + 4 = 7$ ，$d(6) = 1 + 2 + 3 + 6 = 12$ 。

对于给定的数字 $c$ ，找出满足 $d(n) = c$ 的最小的 $n$ 。

## 样例 #1

### 输入
```
12
1
2
3
4
5
6
7
8
9
10
39
691
```

### 输出
```
1
-1
2
3
-1
5
4
7
-1
-1
18
-1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先预处理出一定范围内所有数的因数和，再根据因数和找到对应的最小的数。不同题解的区别在于预处理因数和的方法：
- **暴力枚举倍数法**：枚举每个数，将其累加到它的所有倍数的因数和中，时间复杂度约为 $O(n\log n)$ 。
- **欧拉筛法**：利用欧拉筛的思想，结合因数和的性质来计算因数和，时间复杂度为 $O(n)$ 。

### 所选题解
- **作者：Na2PtCl6 (赞：7)  ★★★★**
    - **关键亮点**：思路清晰，利用欧拉筛计算因数和，代码实现简洁，对因数和的分类讨论明确。
- **作者：Cuiyi_SAI (赞：3)  ★★★★**
    - **关键亮点**：详细证明了因数和函数是积性函数，在此基础上使用欧拉筛计算因数和，逻辑严谨。
- **作者：haokee (赞：3)  ★★★★**
    - **关键亮点**：思路直接，通过枚举倍数预处理因数和，代码简洁易懂。

### 重点代码
#### 作者：Na2PtCl6
```cpp
void get_fc(){
    res[1]=fc[1]=1;
    for(int i=2;i<maxn;i++)
        res[i]=-1;
    for(int i=2;i<maxn;i++){
        if(!vis[i]){
            pr[++cnt]=i;
            fc[i]=i+1;
        }
        for(int j=1;j<=cnt&&i*pr[j]<maxn;j++){
            vis[i*pr[j]]=1;
            if(i%pr[j]==0){
                fc[i*pr[j]]=fc[i]+(fc[i]-fc[i/pr[j]])*pr[j];
                break;
            }
            fc[i*pr[j]]=fc[i]+fc[i]*pr[j];
        }
    }
}
```
**核心实现思想**：利用欧拉筛的框架，根据 $i$ 与当前素数 $pr[j]$ 的关系分类讨论计算 $i * pr[j]$ 的因数和。

#### 作者：Cuiyi_SAI
```cpp
void shai()
{
    d[1]=1;
    for(int i=2;i<=1e7;i++)
    {
        if(!v[i]) prime[++tot]=i,d[i]=1+prime[tot];
        for(int j=1;j<=tot&&prime[j]*i<=1e7;j++)
        {
            v[prime[j]*i]=1;
            if(i%prime[j]==0)
            {
                int x=i*prime[j],s=1;
                while(x%prime[j]==0) x/=prime[j],s*=prime[j];
                d[i*prime[j]]=d[x]*num(s);
                if(d[i*prime[j]]<0||d[i*prime[j]]>1e7) d[i*prime[j]]=0;
                break;
            }
            else d[i*prime[j]]=d[i]*d[prime[j]];
            if(d[i*prime[j]]<0||d[i*prime[j]]>1e7) d[i*prime[j]]=0;  //防爆系统
        }
    }
    for(int i=1;i<=1e7;i++)
      if(ans[d[i]]==0)
        ans[d[i]]=i;
    return ;
}
```
**核心实现思想**：先证明因数和函数是积性函数，然后利用欧拉筛，根据 $i$ 与当前素数 $prime[j]$ 是否互质分类讨论计算 $i * prime[j]$ 的因数和。

#### 作者：haokee
```cpp
// 将所有数的倍数加上这个数
for (int i = 2; i <= 1e7; i++) {
    for (int j = i; j <= 1e7; j += i) {
        f[j] += i;
    }
}
// 记录最小答案
for (int i = 1; i <= 1e7; i++) {
    if (f[i] <= 1e7 && !a[f[i]]) {
        a[f[i]] = i;
    }
}
```
**核心实现思想**：通过枚举每个数的倍数，将该数累加到其倍数的因数和中，然后记录每个因数和对应的最小的数。

### 扩展思路
同类型题目通常会涉及数论中的因数、倍数、质因数分解等知识点。类似算法套路包括：
- 利用欧拉筛计算积性函数，如欧拉函数、莫比乌斯函数等。
- 枚举因数或倍数来预处理一些数论函数的值。

### 洛谷题目推荐
1. [P1072  Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)：涉及因数、最大公约数等数论知识。
2. [P2158  仪仗队](https://www.luogu.com.cn/problem/P2158)：与欧拉函数相关。
3. [P3383  线性筛素数](https://www.luogu.com.cn/problem/P3383)：可以练习欧拉筛的实现。

### 个人心得
- **作者：MatrixCascade**：提到这场 Div3 好水，可惜被 C 恶心了只拿了 rk12 。总结：比赛中可能会遇到一些意外情况影响成绩，要保持良好心态。
- **作者：Meickol**：表示自己半个小时便单出了本题，认为题目蛮简单、很经典。总结：对经典算法和题型要熟练掌握，这样在遇到类似题目时能快速解决。

---
处理用时：45.70秒