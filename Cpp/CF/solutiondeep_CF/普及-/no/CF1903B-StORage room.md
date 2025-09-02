# 题目信息

# StORage room

## 题目描述

In Cyprus, the weather is pretty hot. Thus, Theofanis saw this as an opportunity to create an ice cream company.

He keeps the ice cream safe from other ice cream producers by locking it inside big storage rooms. However, he forgot the password. Luckily, the lock has a special feature for forgetful people!

It gives you a table $ M $ with $ n $ rows and $ n $ columns of non-negative integers, and to open the lock, you need to find an array $ a $ of $ n $ elements such that:

- $ 0 \le a_i < 2^{30} $ , and
- $ M_{i,j} = a_i | a_j $ for all $ i \neq j $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

The lock has a bug, and sometimes it gives tables without any solutions. In that case, the ice cream will remain frozen for the rest of eternity.

Can you find an array to open the lock?

## 样例 #1

### 输入

```
4
1
0
4
0 3 3 5
3 0 3 7
3 3 0 7
5 7 7 0
5
0 7 7 5 5
7 0 3 2 6
7 3 0 3 7
5 2 3 0 4
5 6 7 4 0
3
0 0 1
0 0 0
1 0 0```

### 输出

```
YES
7
YES
1 3 2 5 
YES
5 2 3 0 4
NO```

# AI分析结果

### 题目翻译
在塞浦路斯，天气非常炎热。于是，西奥法尼斯（Theofanis）认为这是一个创办冰淇淋公司的好机会。

他把冰淇淋锁在大储藏室里，以防被其他冰淇淋生产商偷走。然而，他忘记了密码。幸运的是，锁为健忘的人提供了一个特殊功能！

锁会给出一个 $n$ 行 $n$ 列的非负整数矩阵 $M$，要打开锁，你需要找到一个包含 $n$ 个元素的数组 $a$，使得：
- $0 \le a_i < 2^{30}$；
- 对于所有 $i \neq j$，都有 $M_{i,j} = a_i | a_j$，其中 $|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

锁有一个漏洞，有时它给出的矩阵没有任何解。在这种情况下，冰淇淋将永远被冻住。

你能找到一个数组来打开锁吗？

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是基于按位或运算的性质来构造数组 $a$，并判断构造的数组是否满足矩阵 $M$ 的条件。按位或运算的性质是：如果 $M_{i,j}$ 的某一个二进制位上是 $0$，那么 $a_i$ 和 $a_j$ 这一位上也应该是 $0$；如果 $M_{i,j}$ 的某一个二进制位上是 $1$，那么 $a_i$ 和 $a_j$ 中至少有一个这一位上是 $1$。

各题解的算法要点都是先将数组 $a$ 的初始值设为 $2^{30}-1$，然后通过按位与运算，根据矩阵 $M$ 的元素更新数组 $a$ 的值，最后检查构造的数组 $a$ 是否满足 $a_i | a_j = M_{i,j}$。

解决的难点在于理解按位或运算的性质，并利用按位与运算来构造满足条件的数组 $a$，同时要注意处理 $i = j$ 的情况，以及按位或运算符的优先级问题。

### 所选题解
- 作者：引领天下 (赞：8)，4星
  - 关键亮点：思路清晰，代码简洁，对按位或运算的性质分析透彻，先根据矩阵元素更新数组 $a$ 的值，再判断是否满足条件。
- 作者：wanglexi (赞：4)，4星
  - 关键亮点：详细解释了按位或运算的限制条件，先处理 $0$ 的情况，再考虑 $1$ 的情况，最后判断构造的数列是否满足矩阵的限制，代码实现规范。
- 作者：zhangshuhang2011 (赞：0)，4星
  - 关键亮点：明确指出按位或运算的特点，通过按位与运算更新数组 $a$ 的值，最后检查条件是否满足，同时给出了注意事项。

### 重点代码
#### 作者：引领天下
```cpp
for(int i=0;i<n;i++){
    ans[i]=0x7fffffff;
    for(int j=0;j<n;j++)if(i!=j)ans[i]&=m[i][j];
}
bool flag=1;
for(int i=0;i<n;i++)
for(int j=0;j<n;j++)if(i!=j)flag&=(ans[i]|ans[j])==m[i][j];
```
核心实现思想：先将数组 `ans` 初始化为 $2^{30}-1$，然后通过按位与运算，根据矩阵 `m` 的元素更新 `ans` 的值，最后检查 `ans[i] | ans[j]` 是否等于 `m[i][j]`。

#### 作者：wanglexi
```cpp
for(int i=1;i<=n;i++){
    a[i]=(1<<30)-1;
    for(int j=1;j<=n;j++){
        cin>>m[i][j];
        if(i!=j)a[i]&=m[i][j];
    }
}
flag=1;
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(i!=j&&(a[i]|a[j])!=m[i][j])flag=0,i=n+1,j=n+1;
    }
}
```
核心实现思想：将数组 `a` 初始化为 $2^{30}-1$，在输入矩阵 `m` 的同时，通过按位与运算更新 `a` 的值，最后检查 `a[i] | a[j]` 是否等于 `m[i][j]`。

#### 作者：zhangshuhang2011
```cpp
for(int i = 1; i <= n; i++){
    a[i] = all_1;
}
for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
        if(i == j) continue;
        a[i] = a[i] & m[i][j];
        a[j] = a[j] & m[i][j];
    }
}
bool flg = 1;
for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
        if(i == j) continue;
        if((a[i] | a[j]) != m[i][j]){
            flg = 0;
            break;
        }
    }
}
```
核心实现思想：将数组 `a` 初始化为 `all_1`（$2^{30}-1$），通过按位与运算根据矩阵 `m` 的元素更新 `a` 的值，最后检查 `a[i] | a[j]` 是否等于 `m[i][j]`。

### 关键思路或技巧
- 利用按位或运算的性质，通过按位与运算来构造满足条件的数组 $a$。
- 注意处理 $i = j$ 的情况，避免对结果产生影响。
- 由于按位或运算符的优先级比不等号低，在判断条件时需要加括号。

### 拓展思路
同类型题或类似算法套路：涉及位运算的构造问题，通常需要根据位运算的性质来确定元素的取值范围，再通过其他位运算（如按位与、按位异或等）来构造满足条件的解。

### 推荐洛谷题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及位运算和队列的应用。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：可以通过位运算来优化某些操作。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：可能会用到位运算来处理一些状态。

### 个人心得
- 作者：BugGod 警示后人：不要把 $a_i$ 初始化为 $2^{31}-1$，会超出值域 WA；C++ 中按位或的优先级比不等于小，写法中请带括号。
- 作者：zhangshuhang2011 注意事项：`all_1` 必须是 `0x3fffffff`，`0x7fffffff` 会 WA（超过输出上限，输出上限为 `0x3fffffff`）；按位或（`|`）的优先级比不等号（`!=`）低，需要加括号。

总结：在处理位运算问题时，要注意数据范围和运算符的优先级，避免因这些细节问题导致错误。 

---
处理用时：43.10秒