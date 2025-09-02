# 题目信息

# Sereja and Stairs

## 题目描述

Sereja loves integer sequences very much. He especially likes stairs.

Sequence $ a_{1},a_{2},...,a_{|a|} $ ( $ |a| $ is the length of the sequence) is stairs if there is such index $ i $ $ (1<=i<=|a|) $ , that the following condition is met:

 $ a_{1}&lt;a_{2}&lt;...&lt;a_{i-1}&lt;a_{i}&gt;a_{i+1}&gt;...&gt;a_{|a|-1}&gt;a_{|a|}. $ For example, sequences \[1, 2, 3, 2\] and \[4, 2\] are stairs and sequence \[3, 1, 2\] isn't.

Sereja has $ m $ cards with numbers. He wants to put some cards on the table in a row to get a stair sequence. What maximum number of cards can he put on the table?

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
5
5 4 3 2 1
```

## 样例 #2

### 输入

```
6
1 1 2 2 3 3
```

### 输出

```
5
1 2 3 2 1
```

# AI分析结果

### 题目内容
# Sereja和楼梯

## 题目描述
Sereja非常喜欢整数序列，他尤其喜欢“楼梯”序列。
序列\(a_{1},a_{2},...,a_{|a|}\)（\(|a|\)为序列长度）被称为“楼梯”序列，当存在这样一个索引\(i\)（\(1\leq i\leq|a|\)），满足以下条件：
\(a_{1}<a_{2}<...<a_{i - 1}<a_{i}>a_{i + 1}>...>a_{|a| - 1}>a_{|a|}\)。例如，序列\([1, 2, 3, 2]\)和\([4, 2]\)是“楼梯”序列，而序列\([3, 1, 2]\)不是。
Sereja有\(m\)张写有数字的卡片。他想将一些卡片排成一排以得到一个“楼梯”序列。他最多能在桌上放多少张卡片呢？

## 样例 #1
### 输入
```
5
1 2 3 4 5
```
### 输出
```
5
5 4 3 2 1
```

## 样例 #2
### 输入
```
6
1 1 2 2 3 3
```
### 输出
```
5
1 2 3 2 1
```

### 算法分类
贪心

### 综合分析与结论
这些题解均采用贪心算法，核心思路是让序列的开头和结尾尽可能小，中间的峰值尽可能大，从而使构造出的“楼梯”序列长度最长。由于题目中\(b_i\)范围较小（\(b_i\leq5000\)），普遍使用桶数组来记录每个数字出现的次数，以此优化时间复杂度。各题解的难点主要在于如何处理相同数字，保证构造的序列符合“楼梯”序列要求，且长度最大。多数题解都提到最大值只能出现一次，其他数字最多出现两次，且在代码实现中体现了这一点。

### 所选的题解
- **作者：csxx601cjy (5星)**
    - **关键亮点**：思路清晰，代码简洁，直接使用桶数组统计每个数字出现次数，根据出现次数决定数字的选取和输出顺序，先正序输出出现一次或首次出现的数字，再倒序输出出现两次且非最后一次输出的数字。
    - **重点代码核心实现思想**：用桶数组\(a\)统计每个数字出现次数，通过两个循环分别处理正序和倒序输出的数字，记录总长度并按要求输出。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int a[5001],a1[100001],a2[100001];
    int m,t,cnt1=0,cnt2=0,last;
    int main(){
        cin>>m;
        for(int i=0;i<m;i++){
            cin>>t;
            if(a[t]!=2)a[t]++;
        }
        for(int i=1;i<=5000;i++)
            if(a[i]>=1)a1[cnt1++]=i,last=i;
        for(int i=1;i<=5000;i++)
            if(a[i]==2)if(i!=last)a2[cnt2++]=i;
        cout<<cnt1+cnt2<<endl;
        for(int i=0;i<cnt1;i++) cout<<a1[i]<<' ';
        for(int i=cnt2-1;i>=0;i--) cout<<a2[i]<<' ';
        return 0;
    }
    ```
- **作者：Didncan_yu (4星)**
    - **关键亮点**：对贪心算法的原理阐述清晰，明确指出取与不取不会影响后面，通过\(val_i\)表示\(a\)数组中\(i\)的个数来控制数字的选取，并且有自定义的输入输出优化函数。
    - **重点代码核心实现思想**：利用数组\(kr\)记录每个数字出现次数，遍历输入数字，符合条件则计数并记录，最后根据记录输出序列。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    inline int read();
    inline void write(long long n);
    int n,ans,kr[5001],q;
    int main(){
        n=read();
        for(int i=1,a1;i<=n;i++){
            a1=read();
            q=max(a1,q);
            if(kr[a1]<=1){
                kr[a1]++;
                ans++;
            }
        }
        if(kr[q]==2)ans--;
        write(ans);
        putchar('\n');
        for(int i=1;i<=q;i++){
            if(kr[i]>0){
                kr[i]--;
                write(i);
                putchar(' ');
            }
        }
        for(int i=q-1;i>=1;i--){
            if(kr[i]>0){
                kr[i]--;
                write(i);
                putchar(' ');
            }
        }
        return 0;
    }
    inline int read(){
        int s=0,w=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
        while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
        return s*w;
    }
    inline void write(long long n){
        if(n<0){putchar('-');n=-n;}
        if(n>9){write(n/10);}
        putchar(n%10+'0');
    }
    ```
- **作者：zhuweiqi (4星)**
    - **关键亮点**：对贪心策略的解释详细，指出要使序列尽可能长，需让两端小中间大，利用桶标记优化时间复杂度，代码逻辑清晰。
    - **重点代码核心实现思想**：先读取数据并用桶数组\(b\)记录每个数字出现次数，找到最大值，通过两次循环分别确定递增和递减部分选取的数字，最后输出长度和序列。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    inline int read(){
        int n=0;
        char c=getchar();
        while(c<'0' || c>'9') c=getchar();
        while(c>='0' && c<='9'){
            n=(n<<3)+(n<<1)+(c^48);
            c=getchar();
        }
        return n;
    }
    int a[100005];
    int b[5005];
    int main(){
        int n=read(),ans=0,maxs=1;
        for(int i=1;i<=n;i++){
            a[i]=read();
            b[a[i]]++;
            if(a[i]>maxs) maxs=a[i];
        }
        for(int i=1;i<=maxs;i++){
            if(b[i]>0){
                ans++;
                b[i]--;
            }
        }
        for(int i=maxs-1;i>=1;i--) if(b[i]>0) ans++;
        for(int i=1;i<=maxs;i++) b[i]=0;
        for(int i=1;i<=n;i++) b[a[i]]++;
        printf("%d\n",ans);
        for(int i=1;i<=maxs;i++){
            if(b[i]>0){
                printf("%d ",i);
                b[i]--;
            }
        }
        for(int i=maxs-1;i>=1;i--) if(b[i]>0) printf("%d ",i);
        return 0;
    }
    ```

### 最优关键思路或技巧
利用桶数组记录每个数字出现的次数，根据贪心策略，优先选取小的数字放在序列两端，大的数字放在中间，同时注意最大值只能出现一次，其他数字最多出现两次，通过合理的循环和判断来构造并输出符合要求的最长“楼梯”序列。

### 可拓展思路
此类题目属于贪心策略下的序列构造问题，类似套路是先分析序列的性质和要求，确定贪心的方向（如本题使两端小中间大），再结合数据特点选择合适的数据结构辅助实现（本题因数字范围小选择桶数组）。同类型题通常围绕特定序列性质，通过选取或排列元素构造满足条件且最优的序列。

### 推荐题目
- **P1080 [NOIP2012 提高组] 国王游戏**：通过分析相邻元素交换对结果的影响，利用贪心策略解决问题，与本题类似在于都需根据题目条件确定贪心方向。
- **P1199 [NOIP2010 普及组] 三国游戏**：同样是利用贪心思想，结合题目中武将默契值的规则构造最优选择方案，和本题一样需要深入理解题目规则来确定贪心策略。
- **P1094 [NOIP2007 普及组] 纪念品分组**：根据给定的重量限制，通过贪心策略对纪念品进行分组，与本题类似之处在于都是对给定元素进行处理以满足特定条件并达到最优。 

---
处理用时：79.13秒