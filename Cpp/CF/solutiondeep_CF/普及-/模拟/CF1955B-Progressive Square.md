# 题目信息

# Progressive Square

## 题目描述

大小为 $n$ 的累进正方形是一个 $n\times n$ 的矩阵。选择三个整数 $a_{1,1},c,d$
 ，并根据以下规则构造一个累进正方形：

$a _ {i+1,j} = a _ {i,j} + c$

$a _ {i,j+1} = a _ {i,j} + d$

例如，如果 $n=3,a_{1,1}=1,c=2,d=3$，那么累进正方形如下：
 
$\begin{pmatrix} 1 & 4 & 7 \\ 3 & 6 & 9 \\ 5 & 8 & 11 \end{pmatrix}$

给定 $n,c,d$，有 $n^2$ 个整数，判断这些数是否能组成一个符合规则的累进正方形。

## 样例 #1

### 输入

```
5
3 2 3
3 9 6 5 7 1 10 4 8
3 2 3
3 9 6 5 7 1 11 4 8
2 100 100
400 300 400 500
3 2 3
3 9 6 6 5 1 11 4 8
4 4 4
15 27 7 19 23 23 11 15 7 3 19 23 11 15 11 15```

### 输出

```
NO
YES
YES
NO
NO```

# AI分析结果

### 题解综合分析与结论
这些题解的核心思路都是先确定 $a_{1,1}$ 的值（即输入数组中的最小值），再根据递推规则构造出累进正方形矩阵 $a$，最后将矩阵 $a$ 中的元素与输入数组进行比较，判断是否能组成符合规则的累进正方形。

#### 算法要点对比
- **ZnHF、Infinite_Loop、_ayaka_、Silver_Wolf、ttq012**：先对输入数组排序得到 $a_{1,1}$，构造矩阵 $a$ 后将矩阵元素和输入数组元素分别排序再比较。
- **littlebug、2c_s、joe_zxq、qinmingze**：使用 `multiset` 存储输入数组元素，在构造矩阵过程中，每生成一个矩阵元素就在 `multiset` 中查找并删除，若找不到则无法构成。
- **yshpdyt**：使用 `map` 作为桶存储输入数组元素的出现次数，按行和列依次构造矩阵，若元素不足则无法构成。

#### 难点对比
- 使用排序比较的方法代码简单，但排序会带来 $O(n^2\log n^2)$ 的时间复杂度。
- 使用 `multiset` 或 `map` 的方法可以在构造矩阵过程中及时判断是否能构成，但需要熟悉这些数据结构的使用，且插入、查找和删除操作也有一定的时间开销。

#### 评分
- **ZnHF**：3星。思路清晰，但代码中使用了自定义的输入输出函数，增加了代码复杂度，且比较矩阵元素和数组元素的逻辑稍显复杂。
- **Infinite_Loop**：4星。思路清晰，代码简洁易懂，通过公式直接生成矩阵元素，避免了双重循环构造矩阵。
- **littlebug**：4星。思路清晰，使用 `multiset` 进行查找和删除操作，代码逻辑明确。
- **2c_s**：4星。思路简洁，使用 `multiset` 实现，代码结构清晰。
- **joe_zxq**：3星。思路正确，但代码中构造矩阵时越界访问（`a[i + 1][j]` 和 `a[i][j + 1]`），且使用 `multiset` 比较的方式效率不高。
- **_ayaka_**：3星。思路清晰，但代码中公式 `b[(i - 1) * c + j * d]` 有误，应为 `b[(i - 1) * n + j]`。
- **Silver_Wolf**：3星。思路简单，但代码中输出大小写有误（`no` 和 `yes`）。
- **ttq012**：3星。思路正确，但代码中构造矩阵的逻辑稍显复杂。
- **qinmingze**：4星。思路清晰，使用 `multiset` 实现，代码逻辑明确。
- **yshpdyt**：3星。思路正确，但代码中使用 `map` 作为桶，逻辑稍显复杂，且最后还需要额外检查矩阵元素是否满足递推规则。

### 所选题解
- **Infinite_Loop**：4星。关键亮点是通过公式 `a[1]+(i - 1) * d+(j - 1) * c` 直接生成矩阵元素，避免了双重循环构造矩阵，代码简洁高效。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500+10;
int t,n,c,d,a[N*N],b[N*N]; 
int main(){
    cin>>t;
    while(t--){
        cin>>n>>c>>d;
        for(int i=1;i<=n*n;i++)cin>>a[i];
        sort(a+1,a+1+n*n);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                int now=a[1]+(i-1)*d+(j-1)*c;
                b[(i-1)*n+j]=now;
            }
        sort(b+1,b+1+n*n);
        int flag=1;
        for(int i=1;i<=n*n;i++){
            if(a[i]!=b[i]){
                flag=0;
                break;
            }
        }
        if(flag)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```
- **littlebug**：4星。关键亮点是使用 `multiset` 存储输入数组元素，在构造矩阵过程中，每生成一个矩阵元素就在 `multiset` 中查找并删除，若找不到则无法构成，能及时判断结果。
```cpp
il bool check(int i,int j)
{
    auto it=apr.find(a[i][j]);
    if(it==apr.end())
        return 0;
    apr.erase(it);
    return 1;
}
il void solve()
{
    apr.clear();
    cin>>n>>c>>d;
    a[1][1]=inf;
    for(int i=1;i<=n*n;++i)
    {
        cin>>b[i];
        a[1][1]=min(a[1][1],b[i]);
        apr.insert(b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        if(i!=1)
            a[i][1]=a[i-1][1]+c;
        if(!check(i,1))
            fail;
        for(int j=2;j<=n;++j)
        {
            a[i][j]=a[i][j-1]+d;
            if(!check(i,j))
                fail;
        }
    }
    puts("YES");
    return;
}
```
- **2c_s**：4星。关键亮点是使用 `multiset` 实现，代码结构清晰，通过两层循环按行和列依次检查元素是否存在。
```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>st;
int main(){
    int T;
    cin>>T;
    while(T--){
        int n,c,d,mi=1e9;
        cin>>n>>c>>d;
        st.clear();
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                int x;
                cin>>x;
                st.insert(x);
                mi=min(mi,x);
            }
        }
        for(int i=1;i<=n;++i){
            int x=mi;
            auto p=st.find(mi);
            if(p==st.end()){
                cout<<"NO\n";
                goto next;
            }
            st.erase(p);
            for(int j=2;j<=n;++j){
                auto p=st.find(x+d);
                if(p==st.end()){
                    cout<<"NO\n";
                    goto next;
                }
                st.erase(p);
                x+=d;
            }
            mi+=c;
        }
        cout<<"YES\n";
        next:;
    }
    return 0;
}
```

### 最优关键思路或技巧
- 利用 $c$ 和 $d$ 为正数的条件，确定 $a_{1,1}$ 为输入数组中的最小值。
- 使用 `multiset` 或 `map` 存储输入数组元素，在构造矩阵过程中及时判断元素是否存在，避免构造完矩阵后再进行比较。
- 通过公式直接生成矩阵元素，避免双重循环构造矩阵，提高代码效率。

### 拓展思路
同类型题或类似算法套路：
- 矩阵构造问题，给定一些规则构造矩阵，然后判断输入元素是否能组成该矩阵。
- 元素匹配问题，根据一定规则生成一组元素，判断另一组元素是否与之匹配。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：考察数组的使用和区间覆盖问题。
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：考察排序和去重操作。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：考察质数判断和回文数判断。

### 个人心得
题解中未包含个人心得（调试经历、踩坑教训、顿悟感想等）。

---
处理用时：46.93秒