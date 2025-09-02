# 题目信息

# Something with XOR Queries

## 题目描述

This is an interactive problem.

Jury has hidden a permutation $ p $ of integers from $ 0 $ to $ n-1 $ . You know only the length $ n $ . Remind that in permutation all integers are distinct.

Let $ b $ be the inverse permutation for $ p $ , i.e. $ p_{bi}=i $ for all $ i $ . The only thing you can do is to ask xor of elements $ p_{i} $ and $ b_{j} $ , printing two indices $ i $ and $ j $ (not necessarily distinct). As a result of the query with indices $ i $ and $ j $ you'll get the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/05028eedea6284512040197fbf5778282a77d5c1.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the xor operation. You can find the description of xor operation in notes.

Note that some permutations can remain indistinguishable from the hidden one, even if you make all possible $ n^{2} $ queries. You have to compute the number of permutations indistinguishable from the hidden one, and print one of such permutations, making no more than $ 2n $ queries.

The hidden permutation does not depend on your queries.

## 说明/提示

xor operation, or bitwise exclusive OR, is an operation performed over two integers, in which the $ i $ -th digit in binary representation of the result is equal to $ 1 $ if and only if exactly one of the two integers has the $ i $ -th digit in binary representation equal to $ 1 $ . For more information, see [here](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

In the first example $ p=[0,1,2] $ , thus $ b=[0,1,2] $ , the values ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/05028eedea6284512040197fbf5778282a77d5c1.png) are correct for the given $ i,j $ . There are no other permutations that give the same answers for the given queries.

The answers for the queries are:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/46dc5fa94694b483f32f322d24785fe68067b25b.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/a7c48fc1d69c2a31eb1045df7d8372d886447c99.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/110cedaea37a8029cc469f48f789efcb5cd1135a.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/0ddcfac860c29dd6a8df9924ebc0e40d8aa6ba25.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/91072cc5c414f3abeea20c2283336f4fdb1f8e87.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/b587b2585b6e8e5b2a4afb82178cfced90807af0.png).

In the second example $ p=[3,1,2,0] $ , and $ b=[3,1,2,0] $ , the values ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870D/05028eedea6284512040197fbf5778282a77d5c1.png) match for all pairs $ i,j $ . But there is one more suitable permutation $ p=[0,2,1,3] $ , $ b=[0,2,1,3] $ that matches all $ n^{2} $ possible queries as well. All other permutations do not match even the shown queries.

## 样例 #1

### 输入

```
3
0
0
3
2
3
2```

### 输出

```
? 0 0
? 1 1
? 1 2
? 0 2
? 2 1
? 2 0
!
1
0 1 2```

## 样例 #2

### 输入

```
4
2
3
2
0
2
3
2
0```

### 输出

```
? 0 1
? 1 2
? 2 3
? 3 3
? 3 2
? 2 1
? 1 0
? 0 0
!
2
3 1 2 0```

# AI分析结果

### 题目内容
# 与异或查询相关的问题

## 题目描述
这是一道交互式问题。

评委隐藏了一个从\(0\)到\(n - 1\)的整数排列\(p\)。你只知道长度\(n\)。提醒一下，在排列中所有整数都是不同的。

设\(b\)是\(p\)的逆排列，即对于所有\(i\)，\(p_{b_i}=i\)。你唯一能做的是询问元素\(p_i\)和\(b_j\)的异或值，通过打印两个索引\(i\)和\(j\)（不一定不同）。作为索引为\(i\)和\(j\)的查询结果，你将得到值\(p_i \oplus b_j\)，其中\(\oplus\)表示异或运算。你可以在注释中找到异或运算的描述。

注意，即使你进行所有可能的\(n^2\)次查询，某些排列可能与隐藏的排列无法区分。你必须计算与隐藏排列无法区分的排列数量，并打印其中一个这样的排列，查询次数不超过\(2n\)次。

隐藏排列不依赖于你的查询。

## 说明/提示
异或运算，或按位异或，是对两个整数执行的一种运算，结果的二进制表示中的第\(i\)位等于\(1\)，当且仅当两个整数中恰好有一个的二进制表示中的第\(i\)位等于\(1\)。更多信息，见[此处](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

在第一个例子中\(p = [0, 1, 2]\)，因此\(b = [0, 1, 2]\)，对于给定的\(i, j\)，值\(p_i \oplus b_j\)是正确的。没有其他排列对给定的查询给出相同的答案。

查询的答案是：
- \(p_0 \oplus b_0 = 0\)，
- \(p_1 \oplus b_1 = 0\)，
- \(p_1 \oplus b_2 = 3\)，
- \(p_0 \oplus b_2 = 2\)，
- \(p_2 \oplus b_1 = 3\)，
- \(p_2 \oplus b_0 = 2\)。

在第二个例子中\(p = [3, 1, 2, 0]\)，并且\(b = [3, 1, 2, 0]\)，对于所有对\(i, j\)，值\(p_i \oplus b_j\)都匹配。但是还有另一个合适的排列\(p = [0, 2, 1, 3]\)，\(b = [0, 2, 1, 3]\)，它也与所有\(n^2\)次可能的查询匹配。所有其他排列甚至与所示的查询都不匹配。

## 样例 #1
### 输入
```
3
0
0
3
2
3
2
```
### 输出
```
? 0 0
? 1 1
? 1 2
? 0 2
? 2 1
? 2 0
!
1
0 1 2
```
## 样例 #2
### 输入
```
4
2
3
2
0
2
3
2
0
```
### 输出
```
? 0 1
? 1 2
? 2 3
? 3 3
? 3 2
? 2 1
? 1 0
? 0 0
!
2
3 1 2 0
```
### 算法分类
数学（主要利用异或运算的性质来解决问题）

### 综合分析与结论
这三道题解思路基本一致，都是基于异或运算的性质，通过询问\(2n\)次得到\(p_i \oplus b_0\)和\(p_0 \oplus b_j\)的值，进而推导出所有\(p_i \oplus b_j\)的值，然后通过枚举\(p_0\)的值来确定所有\(p_i\)以及\(b_i\)的值，并检查是否满足\(p[b[i]] = i\) 。不同之处在于代码实现的细节和风格。

### 所选的题解
- **作者：GalaxyOier（4星）**
  - **关键亮点**：思路清晰简洁，直接阐述通过询问\(p[0]^{b[i]}(0<=i<n)\)和\(p[i]^{b[0]}(0<=i<n)\)，给\(p[0]\)赋值推出所有值的思路，代码实现较为直观。
  - **重点代码核心实现思想**：先通过两次循环询问得到\(p_i \oplus b_0\)和\(p_0 \oplus b_j\)的值存于`ans`数组，然后枚举\(p[0]\)的值，通过异或运算推出\(b\)数组和\(p\)数组其他值，检查是否满足条件，统计符合条件的排列数并输出其中一个。
```cpp
for(int i=0;i<n;i++) 
{
    printf("? %d %d\n",i,0);
    fflush(stdout);
    scanf("%d",&x);
    ans[i][0]=x;
}
for(int i=1;i<n;i++) 
{
    printf("? %d %d\n", 0, i);
    fflush(stdout);
    scanf("%d", &x);;
    ans[0][i] = x;
}
int res = 0;
for(int i = 0 ; i < n ; i++) 
{
    memset(p, -1, sizeof(p));
    memset(b, -1, sizeof(b));
    p[0] = i;
    for(int j = 0 ; j < n ; j++) 
    {
        b[j] = (ans[0][j] ^ p[0]);
    }
    for(int j = 1 ; j < n ; j++) 
    {
        p[j] = (ans[j][0] ^ b[0]);
    }
    int flag = 0;
    for(int j = 0 ; j < n ; j++) 
    {
        if(p[b[j]]!= j || p[j] >= n || b[j] >= n)
        {
            flag = 1;
            break;
        }
    }
    if(!flag) 
    {
        res++;
        for(int j = 0 ; j < n ; j++) 
        {
            p_true[j] = p[j];
            b_true[j] = b[j];
        }
    }
}
```
- **作者：William_Wang_（4星）**
  - **关键亮点**：先分析已知\(n^2\)对数情况，再阐述利用\(2n\)对数推出所有\(n^2\)对数的原理，逻辑清晰。代码中函数封装较好，使整体结构更清晰。
  - **重点代码核心实现思想**：通过循环询问获取\(p_0 \oplus b_j\)和\(p_i \oplus b_0\)的值存于`p0`和`b0`数组，定义`valid`函数检查数组是否为有效的排列，`check`函数根据枚举的\(p[0]\)值推出\(p\)和\(b\)数组其他值并检查是否符合要求，统计符合要求的排列数并输出其中一个。
```cpp
bool valid(int *a)
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++)
    {
        if(a[i] >= n) return false;
        vis[a[i]]++;
    }
    for(int i=0;i<n;i++)
        if(vis[i]!=1) return false;
    return true;
}
bool check(int x)
{
    p[0] = x;
    for(int i=1;i<n;i++)
        p[i] = p[0] ^ b0[0] ^ b0[i];    // p0 ^ (p0 ^ b0) ^ (pi ^ b0)
    
    if(!valid(p)) return false;
    
    b[0] = p[0] ^ p0[0];
    for(int i=1;i<n;i++)
        b[i] = b[0] ^ p0[0] ^ p0[i];    // b0 ^ (p0 ^ b0) ^ (p0 ^ bi)
    
    if(!valid(b)) return false;
    
    for(int i=0;i<n;i++)
        if(p[b[i]]!= i) return false;
    
    return true;
}
//...
for(int i=0;i<n;i++)
{
    printf("? 0 %d\n",i); fflush(stdout);
    scanf("%d",&p0[i]);
}
for(int i=0;i<n;i++)
{
    printf("? %d 0\n",i); fflush(stdout);
    scanf("%d",&b0[i]);
}
int cnt = 0;
for(int i=0;i<n;i++)
{
    if(check(i)) cnt++;
}
printf("!\n%d\n",cnt);
for(int i=0;i<n;i++)
{
    if(check(i))
    {
        p[0] = i;
        printf("%d ",p[0]);
        for(int j=1;j<n;j++) printf("%d ",p[0] ^ b0[0] ^ b0[j]);
        break;
    }
}
```
- **作者：lgx57（4星）**
  - **关键亮点**：代码结构清晰，将询问操作封装成函数`Ask`，将计算\(a_i \oplus b_j\)的操作封装成函数`get`，判断是否满足要求封装成函数`check`，逻辑清晰明了。
  - **重点代码核心实现思想**：通过`Ask`函数询问获取\(p_0 \oplus b_j\)和\(p_i \oplus b_0\)的值存于`ans1`和`ans2`数组，通过`get`函数计算任意\(p_i \oplus b_j\)的值，枚举\(p[0]\)的值推出\(p\)和\(b\)数组其他值，通过`check`函数检查是否符合要求，统计符合要求的排列数并输出其中一个。
```cpp
int Ask(int x,int y){//询问
    cout<<"? "<<x<<' '<<y<<endl;
    int ans;
    cin>>ans;
    return ans;
}
int get(int i,int j){
    return ans1[j]^ans1[0]^ans2[i];//a_i^b_j
}
bool check(vector<int> v1,vector<int> v2){//判断是否满足要求
    for (int i=0;i<n;i++){
        if (v2[i]>=n) return 0;
        if (v1[v2[i]]!=i) return 0;
    }
    return 1;
}
//...
for (int i=0;i<n;i++){
    ans1[i]=Ask(0,i);
    ans2[i]=Ask(i,0);
}
int Ans=0;
vector<int> v1(n),v2(n),v(n);
for (int i=0;i<n;i++){
    v1[0]=i;
    for (int j=0;j<n;j++){
        v2[j]=v1[0]^get(0,j);
    }
    for (int j=1;j<n;j++){
        v1[j]=v2[0]^get(j,0);
    }
    if (check(v1,v2)){
        if (!Ans) v=v1;
        Ans++;
    }
}
```

### 最优关键思路或技巧
利用异或运算的性质，通过有限次数（\(2n\)次）的询问，推导出所有可能的\(p_i \oplus b_j\)的值，再通过枚举\(p_0\)的值来确定整个排列\(p\)和其逆排列\(b\)，并利用数组检查是否为有效的排列以及是否满足\(p[b[i]] = i\) 。在代码实现上，合理的函数封装和数组使用有助于提高代码的可读性和逻辑性。

### 可拓展之处
同类型题通常围绕特定运算（如本题的异或运算）的性质，结合排列、组合等概念设计交互式问题。类似算法套路是先分析运算性质找到关键的可推导关系，通过有限操作获取关键信息，再通过枚举等方式确定最终结果。

### 洛谷相似题目推荐
- [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)：同样利用异或运算的性质解决问题，不过本题是非交互式，主要考查对异或运算抵消相同元素特性的理解。
- [P1508 Likecloud-吃、吃、吃](https://www.luogu.com.cn/problem/P1508)：涉及到通过异或运算处理数据，判断状态等操作，与本题利用异或运算推导信息有相似之处。
- [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：虽然不是交互式问题，但也利用到了异或运算相关思路来处理数据和统计结果，可加深对异或运算应用的理解。

### 个人心得摘录与总结
无明显个人心得相关内容。 

---
处理用时：97.39秒