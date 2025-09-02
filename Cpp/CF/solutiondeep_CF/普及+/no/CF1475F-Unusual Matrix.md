# 题目信息

# Unusual Matrix

## 题目描述

给你两个 $n\times n$ 的01矩阵，你可以进行如下两种操作：

- 垂直xor：选中一列，将这一列的每个元素分别进行xor
- 水平xor：选中一行，将这一行的每个元素分别进行xor

给定 $a,b$ 两个矩阵，问你 $a$ 是否可以在进行有限次操作后变为 $b$

例如：
$$
a=\begin{pmatrix} 1 & 1 & 0 \\ 0 & 0 & 1 \\ 1 & 1 & 0 \end{pmatrix},b=\begin{pmatrix} 0 & 0 & 0 \\ 0 & 0 & 0 \\ 0 & 0 & 0 \end{pmatrix}
$$
先使第一行进行水平xor：
$$
a=\begin{pmatrix} 0 & 0 & 1 \\ 0 & 0 & 1 \\ 1 & 1 & 0 \end{pmatrix}
$$
再使第三行进行水平xor：
$$
a=\begin{pmatrix} 0 & 0 & 1 \\ 0 & 0 & 1 \\ 0 & 0 & 1 \end{pmatrix}
$$
最后使第三列进行垂直xor即可

## 样例 #1

### 输入

```
3
3
110
001
110

000
000
000
3
101
010
101

010
101
010
2
01
11

10
10```

### 输出

```
YES
YES
NO```

# AI分析结果

### 算法分类
位运算

### 综合分析与结论
各题解的核心思路都是先将两个矩阵异或得到新矩阵，将问题转化为新矩阵能否通过行列异或操作变为全 0 矩阵。不同题解采用了不同的具体方法：
- **简单逻辑判断类**：通过比较行与行之间的关系，判断是否能将矩阵变为全 0 矩阵。思路简单直接，代码实现相对容易。
- **2 - SAT 类**：将问题转化为 2 - SAT 问题，利用图论中的 tarjan 算法求解。能更严谨地处理逻辑关系，但实现复杂度较高。
- **枚举类**：枚举第一列是否操作，确定整个矩阵的操作方法，再进行检验。思路直观，但可能存在重复计算。
- **其他类**：如高斯消元思路、并查集思路等，从不同角度解决问题，但实现难度和复杂度各有不同。

### 所选题解
- **作者：Cutest_Junior (赞：7)，4星**
    - **关键亮点**：思路清晰，代码简洁，通过简单的逻辑判断来确定矩阵是否可转化，易于理解和实现。
- **作者：jianhe (赞：4)，4星**
    - **关键亮点**：同样采用简单逻辑判断，代码规范，利用异或性质简化问题，可读性高。
- **作者：ZSH_ZSH (赞：2)，4星**
    - **关键亮点**：枚举第一列的操作情况，确定整个矩阵的操作，思路直观，代码实现较为清晰。

### 重点代码
#### Cutest_Junior 的代码
```cpp
#include <cstdio>
 
using namespace std;
 
const int N = 1005;
 
char map1[N][N];
char map2[N][N];
 
int arr[N][N];
 
void run() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", map1[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%s", map2[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            arr[i][j] = (map1[i][j] - '0') ^ (map2[i][j] - '0');
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= n; ++j) {
            if ((arr[i][j] ^ arr[1][j]) != (arr[i][1] ^ arr[1][1])) {
                printf("NO\n");
                return;
            }
        }
    }
    printf("YES\n");
}
 
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        run();
    }
}
```
**核心实现思想**：先将两个矩阵异或得到新矩阵，然后比较第 2 行到第 n 行与第 1 行的关系，如果存在不满足条件的情况则输出 NO，否则输出 YES。

#### jianhe 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1010;
ll T,n,p[N][N];
string a[N],b[N];
bool flag;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;flag=1;
        for(int i=1;i<=n;i++) cin>>a[i],a[i]=" "+a[i];
        for(int i=1;i<=n;i++) cin>>b[i],b[i]=" "+b[i];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                p[i][j]=(a[i][j]-'0')^(b[i][j]-'0');
        for(int i=2;i<=n&&flag;i++)
            for(int j=2;j<=n&&flag;j++)
                if((p[1][j]^p[i][j])!=(p[1][1]^p[i][1])) cout<<"NO\n",flag=0;
        if(flag) cout<<"YES\n";
    }
    return 0;
}
```
**核心实现思想**：与 Cutest_Junior 的思路类似，先异或得到新矩阵，再通过比较行与行之间的关系判断是否可转化。

#### ZSH_ZSH 的代码
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for (register int i=(a);i<=(b);i++)
#define drep(i,a,b) for (register int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline ll read()
{
    ll sum=0,f=0;char c=getchar();
    while (!isdigit(c)) f|=(c=='-'),c=getchar();
    while (isdigit(c)) sum=(sum<<1)+(sum<<3)+(c^48),c=getchar();
    return f?-sum:sum;
}

const int N=1010;
int n,a[N][N],h[N],w[N];
char c1[N][N],c2[N][N];

inline bool chk1()
{
    memset(h,0,sizeof(h)),memset(w,0,sizeof(w));
    h[1]=1;
    rep(i,1,n) if ((a[i][1]^h[1])==0) w[i]=0;else w[i]=1;
    rep(i,2,n) if ((a[1][i]^w[1])==0) h[i]=0;else h[i]=1;
    
    rep(i,1,n) rep(j,1,n) if ((a[i][j]^h[j]^w[i])==1) return false;
    return true;
}

inline bool chk2()
{
    memset(h,0,sizeof(h)),memset(w,0,sizeof(w));
    h[1]=0;
    rep(i,1,n) if ((a[i][1]^h[1])==0) w[i]=0;else w[i]=1;
    rep(i,2,n) if ((a[1][i]^w[1])==0) h[i]=0;else h[i]=1;
    
    rep(i,1,n) rep(j,1,n) if ((a[i][j]^h[j]^w[i])==1) return false;
    return true;
}

inline void solve()
{
    n=read();
    rep(i,1,n) scanf("%s",c1[i]+1);
    rep(i,1,n) scanf("%s",c2[i]+1);
    rep(i,1,n) rep(j,1,n) a[i][j]=c1[i][j]^c2[i][j];
    
    if (chk1()||chk2()) printf("YES\n");
    else printf("NO\n");
}

int main()
{
    drep(T,read(),1) solve();
}
```
**核心实现思想**：先将两个矩阵异或得到新矩阵，然后枚举第一列是否操作，分别计算出整个矩阵的操作方法，再检验是否能将矩阵变为全 0 矩阵。

### 最优关键思路或技巧
- 利用异或的性质，将两个矩阵异或得到新矩阵，将问题转化为新矩阵能否变为全 0 矩阵，简化了问题。
- 通过比较行与行之间的关系或枚举第一列的操作情况，确定整个矩阵的操作，降低了问题的复杂度。

### 拓展思路
同类型题或类似算法套路：
- 涉及矩阵操作和异或运算的题目，如矩阵的翻转、变换等。
- 利用逻辑关系进行判断的题目，可考虑使用 2 - SAT 或并查集等方法。

### 推荐题目
- [P1168 中位数](https://www.luogu.com.cn/problem/P1168)：涉及数据处理和逻辑判断。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可利用树状数组或归并排序解决，与本题的逻辑判断有一定相似性。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：涉及贪心算法和数据处理。

### 个人心得
Cutest_Junior 提到“思维难度不高，代码也很好写，我 Virtual participation 的时候就过了”，说明本题虽然有多种解法，但一些简单的思路和实现方式能够快速解决问题。 

---
处理用时：58.14秒