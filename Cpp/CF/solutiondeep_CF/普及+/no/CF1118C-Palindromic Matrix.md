# 题目信息

# Palindromic Matrix

## 题目描述

Let's call some square matrix with integer values in its cells palindromic if it doesn't change after the order of rows is reversed and it doesn't change after the order of columns is reversed.

For example, the following matrices are palindromic:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/1dd62ecf9cdea049a4333ac1caa6ce864c1d5fc5.png)The following matrices are not palindromic because they change after the order of rows is reversed:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/2143b8b786a0f045139a90d99c3f905c3e226fac.png)The following matrices are not palindromic because they change after the order of columns is reversed:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/fe33a9bda586416fffd510345806131041ef4caa.png)You are given $ n^2 $ integers. Put them into a matrix of $ n $ rows and $ n $ columns so that each number is used exactly once, each cell contains exactly one number and the resulting matrix is palindromic. If there are multiple answers, print any. If there is no solution, print "NO".

## 说明/提示

Note that there exist multiple answers for the first two examples.

## 样例 #1

### 输入

```
4
1 8 8 1 2 2 2 2 2 2 2 2 1 8 8 1
```

### 输出

```
YES
1 2 2 1
8 2 2 8
8 2 2 8
1 2 2 1
```

## 样例 #2

### 输入

```
3
1 1 1 1 1 3 3 3 3
```

### 输出

```
YES
1 3 1
3 1 3
1 3 1
```

## 样例 #3

### 输入

```
4
1 2 1 9 8 4 3 8 8 3 4 8 9 2 1 1
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
1
10
```

### 输出

```
YES
10 
```

# AI分析结果

### 题目翻译
## 回文矩阵

### 题目描述
如果一个方阵的单元格中包含整数值，并且在反转行的顺序和反转列的顺序后都不改变，我们就称这个方阵为回文矩阵。

例如，以下矩阵是回文矩阵：
![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/1dd62ecf9cdea049a4333ac1caa6ce864c1d5fc5.png)
以下矩阵不是回文矩阵，因为在反转行的顺序后会改变：
![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/2143b8b786a0f045139a90d99c3f905c3e226fac.png)
以下矩阵不是回文矩阵，因为在反转列的顺序后会改变：
![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/fe33a9bda586416fffd510345806131041ef4caa.png)
给定 $n^2$ 个整数，将它们放入一个 $n$ 行 $n$ 列的矩阵中，使得每个数字恰好使用一次，每个单元格恰好包含一个数字，并且得到的矩阵是回文矩阵。如果有多个答案，输出任意一个。如果没有解，输出 "NO"。

### 说明/提示
注意，前两个示例存在多个答案。

### 样例 #1
#### 输入
```
4
1 8 8 1 2 2 2 2 2 2 2 2 1 8 8 1
```
#### 输出
```
YES
1 2 2 1
8 2 2 8
8 2 2 8
1 2 2 1
```

### 样例 #2
#### 输入
```
3
1 1 1 1 1 3 3 3 3
```
#### 输出
```
YES
1 3 1
3 1 3
1 3 1
```

### 样例 #3
#### 输入
```
4
1 2 1 9 8 4 3 8 8 3 4 8 9 2 1 1
```
#### 输出
```
NO
```

### 样例 #4
#### 输入
```
1
10
```
#### 输出
```
YES
10 
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是根据回文矩阵的性质，分 $n$ 为偶数和奇数两种情况进行讨论。
- **思路**：当 $n$ 为偶数时，每个数字出现的次数必须是 4 的倍数；当 $n$ 为奇数时，中间行和中间列的数字出现次数需满足一定条件，中心位置的数字可单独处理。
- **算法要点**：使用桶来记录每个数字的出现次数，根据不同情况进行填充，利用回文矩阵的对称性进行赋值。
- **解决难点**：处理 $n$ 为奇数时中间行、列和中心位置的数字，以及判断无解的情况。

### 所选题解
- **yingkeqian9217（4星）**
    - **关键亮点**：代码简洁，思路清晰，通过桶和向量的结合，高效地处理了不同情况。
    - **核心实现思想**：先统计每个数字的出现次数，将出现次数满足条件的数字存入向量。对于偶数情况，直接从向量中取数填充矩阵；对于奇数情况，先填充非中间部分，再处理中间行、列和中心位置。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[3003],s[31][31];
vector<int>v;
int solve(){
    v.clear();
    for(int i=1;i<=3000;i++)
     if(t[i]>=2)
      v.push_back(i);
    for(int i=1;i<=n/2;i++){
        if(v.empty()) return 0;
        int x=v[v.size()-1];
        t[x]-=2;
        s[n/2+1][i]=s[n/2+1][n-i+1]=x;
        if(t[x]<2) v.pop_back();
    }
    for(int i=1;i<=n/2;i++){
        if(v.empty()) return 0;
        int x=v[v.size()-1];
        t[x]-=2;
        s[i][n/2+1]=s[n-i+1][n/2+1]=x;
        if(t[x]<2) v.pop_back();
    }
    for(int i=1;i<=3000;i++)
     if(t[i]){
        s[n/2+1][n/2+1]=i;
        break;
     }
    return 1;
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n*n;i++){
        int x;
        scanf("%d",&x);
        t[x]++;
    }
    for(int i=1;i<=3000;i++)
     if(t[i]>=4)
      v.push_back(i);
    for(int i=1;i<=n/2;i++)
     for(int j=1;j<=n/2;j++){
        if(v.empty()) return puts("NO"),0;
        int x=v[v.size()-1];
        t[x]-=4;
        s[i][j]=s[i][n-j+1]=s[n-i+1][j]=s[n-i+1][n-j+1]=x;
        if(t[x]<4) v.pop_back();
     }
    if(n&1&&!solve()) return puts("NO"),0;
    puts("YES");
    for(int i=1;i<=n;i++,puts(""))
     for(int j=1;j<=n;j++)
      printf("%d ",s[i][j]);
    return 0;
}
```
- **jiangchen1234（4星）**
    - **关键亮点**：详细分情况讨论，代码结构清晰，注释丰富，便于理解。
    - **核心实现思想**：分别实现了判断 $n$ 为偶数和奇数时能否组成回文矩阵的函数，根据判断结果进行填充。
    - **核心代码**：
```cpp
il bool check2() {
    for(rg int i(1); i <= 1000; ++i) {
        if(num[i] % 4) return 1;
    }
    return 0;
}
il bool check1() {
    for(rg int i(1); i <= 1000; ++i) {
        int x = num[i] % 4;
        if(!x) continue;
        else if(x == 1) {
            if(flag3) return 1;
            flag3 = 1;
            num3 = i;
        } else if(x == 2) {
            if(len1 > n - 1) return 1;
            ++len1;
            flag1[len1] = 1;
            num1[len1] = i;
        } else {
            if(len1 > n - 1 || flag3) return 1;
            ++len1;
            flag1[len1] = 1;
            num1[len1] = i;
            flag3 = 1;
            num3 = i;
        }
    }
    if(len1 & 1) return 1;
    return 0;
}
```
- **WuMin4（4星）**
    - **关键亮点**：使用 `unordered_map` 记录数字出现次数，通过自定义函数处理位置更新，逻辑清晰。
    - **核心实现思想**：先统计数字出现次数，根据 $n$ 的奇偶性进行不同处理，对于奇数情况，优先处理中心位置，再填充其他部分。
    - **核心代码**：
```cpp
void nxt(int &nx,int &ny){
    if(nx==n/2)
        nx=1,ny++;
    else
        nx++;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n*n;i++){
        cin>>a[i];
        if(!cnt[a[i]])
            num.push_back(a[i]);
        cnt[a[i]]++;
    }
    int nx=1,ny=1,zx=1,zy=1;
    bool odd=1;
    for(int v:num){
        if(cnt[v]%4!=0&&n%2==0){
            cout<<"NO";
            return 0;
        }
        if(n%2==1){
            if(cnt[v]%2==1){
                if(odd)
                    odd=0,b[n/2+1][n/2+1]=v,cnt[v]--;
                else{
                    cout<<"NO";
                    return 0;
                }
            }
            if(cnt[v]%4==2){
                if(zx<=n/2)
                    b[zx][n/2+1]=v,b[n-zx+1][n/2+1]=v,zx++,cnt[v]-=2;
                else if(zy<=n/2)
                    b[n/2+1][zy]=v,b[n/2+1][n-zy+1]=v,zy++,cnt[v]-=2;
                else{
                    cout<<"NO";
                    return 0;
                }
            }
        }
        while(cnt[v]&&ny<=n/2){
            b[nx][ny]=v;
            b[nx][n-ny+1]=v;
            b[n-nx+1][ny]=v;
            b[n-nx+1][n-ny+1]=v;
            nxt(nx,ny);
            cnt[v]-=4;
        }
    }
    for(int v:num){
        while(cnt[v]){
            if(zx<=n/2)
                b[zx][n/2+1]=v,b[n-zx+1][n/2+1]=v,zx++,cnt[v]-=2;
            else if(zy<=n/2)
                b[n/2+1][zy]=v,b[n/2+1][n-zy+1]=v,zy++,cnt[v]-=2;
            else{
                cout<<"NO";
                return 0;
            }
        }
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++,cout<<endl)
        for(int j=1;j<=n;j++)
            cout<<b[i][j]<<" ";
    return 0; 
}
```

### 最优关键思路或技巧
- 使用桶或 `unordered_map` 记录每个数字的出现次数，方便后续判断和填充。
- 分 $n$ 为偶数和奇数两种情况讨论，利用回文矩阵的对称性进行矩阵填充。

### 拓展思路
同类型题目可能会改变矩阵的对称条件，或者增加其他限制，解题时仍可采用分类讨论和利用对称性的思路。

### 推荐题目
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：考察矩阵的构造和回溯法。
- [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)：涉及构造和递归思想。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：需要根据条件进行矩阵的构造和查询。

### 个人心得
部分题解提到代码细节较多，需要仔细调试，在处理 $n$ 为奇数的情况时，要特别注意中间行、列和中心位置的处理，避免出现逻辑错误。

---
处理用时：77.24秒