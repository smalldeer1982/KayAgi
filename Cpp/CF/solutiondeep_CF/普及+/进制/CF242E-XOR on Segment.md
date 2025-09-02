# 题目信息

# XOR on Segment

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l,r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l,r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 样例 #1

### 输入

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
```

### 输出

```
26
22
0
34
11
```

## 样例 #2

### 输入

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
```

### 输出

```
38
28
```

# AI分析结果

### 题目中文重写
# 区间异或操作

## 题目描述
给定一个数组 $ a $，由 $ n $ 个整数 $ a_{1},a_{2},\cdots,a_{n} $ 组成。允许对该数组执行两种操作：
1. 计算当前数组在区间 $ [l,r] $ 上的元素和，即计算值 $ a_{l}+a_{l + 1}+\cdots+a_{r} $。
2. 对区间 $ [l,r] $ 内的每个数组元素执行异或操作，异或的数为给定的 $ x $，即执行 $ a_{i}:=a_{i}\oplus x $（$ i = l,l + 1,\cdots,r $）。此操作将精确改变 $ r - l + 1 $ 个数组元素。

表达式 $ x\oplus y $ 表示对数字 $ x $ 和 $ y $ 执行按位异或操作。该操作在所有现代编程语言中均存在，例如在 C++ 和 Java 语言中用 "^" 表示，在 Pascal 中用 "xor" 表示。

给定 $ m $ 个上述类型的操作。你的任务是执行所有给定操作，并针对每个求和查询输出结果。

## 样例 #1
### 输入
```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
```
### 输出
```
26
22
0
34
11
```

## 样例 #2
### 输入
```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
```
### 输出
```
38
28
```

### 综合分析与结论
这些题解主要围绕区间异或和区间求和问题展开，大部分采用线段树结合二进制拆位的方法，也有部分使用暴力、分块、指令集等方法。
- **思路对比**：多数题解通过二进制拆位，将整数序列拆成多个 01 串，用线段树维护每个二进制位上 1 的个数，从而将区间异或转化为区间取反操作。部分题解采用暴力法，通过循环展开或指令集优化来提高效率，还有题解使用分块算法。
- **算法要点**：线段树结合二进制拆位的题解，关键在于构建线段树、处理懒标记、实现区间修改和查询操作。暴力法通过循环展开或指令集同时处理多个数，分块算法则是将数组分块，统计块内信息。
- **解决难点**：本题的难点在于区间异或操作无法直接用传统线段树维护区间和。二进制拆位将问题转化为 01 串的区间取反和求和，利用异或性质解决了这一难点。

### 所选题解
- **作者：gzw2005 (赞：65) - 5星**
    - **关键亮点**：思路清晰，先简化问题找规律，再将规律应用到二进制拆位的线段树中，代码实现规范，注释详细。
- **作者：SymphonyOfEuler (赞：15) - 4星**
    - **关键亮点**：对异或法则和拆位原理有详细解释，代码结构清晰，函数命名规范。
- **作者：YLWang (赞：7) - 4星**
    - **关键亮点**：明确指出异或问题的常见思路，用 21 棵线段树分别维护每一位，将问题转化为经典的区间翻转问题。

### 重点代码
#### gzw2005 的核心代码
```cpp
// 建树
void buildTree(int L,int R,int cur){
    if(L==R){
        for(int i=0;i<20;i++)
            if((a[L]>>i)&1)cnt[cur][i]=1;
        return;
    }
    int mid=(L+R)>>1;
    buildTree(L,mid,ls(cur));
    buildTree(mid+1,R,rs(cur));
    up(cur);
}
// 下传标记
void down(int L,int R,int cur){
    int mid=(L+R)>>1;
    for(int i=0;i<20;i++)
        if((tag[cur]>>i)&1){//区间取反 
            cnt[ls(cur)][i]=(mid-L+1)-cnt[ls(cur)][i];
            cnt[rs(cur)][i]=(R-mid)-cnt[rs(cur)][i];
        }
    tag[ls(cur)]^=tag[cur];
    tag[rs(cur)]^=tag[cur];
    tag[cur]=0;
}
// 区间更新
void update(int L,int R,int cur,int l,int r,int val){
    if(R<l||r<L)return;
    if(l<=L && R<=r){
        for(int i=0;i<20;i++)//区间取反 
            if((val>>i)&1)cnt[cur][i]=(R-L+1)-cnt[cur][i];
        tag[cur]^=val;
        return;
    }
    int mid=(L+R)>>1;
    down(L,R,cur);//下传标记 
    update(L,mid,ls(cur),l,r,val);
    update(mid+1,R,rs(cur),l,r,val);
    up(cur);
}
// 区间查询
long long query(int L,int R,int cur,int l,int r){
    if(R<l||r<L)return 0;
    if(l<=L && R<=r){
        long long ret=0,Pow=1;
        for(int i=0;i<20;i++){//求和 
            ret+=Pow*cnt[cur][i];
            Pow<<=1;
        }
        return ret;
    }
    int mid=(L+R)>>1;
    down(L,R,cur);
    return query(L,mid,ls(cur),l,r)+query(mid+1,R,rs(cur),l,r);
}
```
**核心实现思想**：通过二进制拆位，用线段树维护每个二进制位上 1 的个数。建树时将每个数拆成二进制，更新时根据异或值的二进制位判断是否取反，查询时将每个二进制位的 1 的个数乘以对应的位权求和。

#### SymphonyOfEuler 的核心代码
```cpp
// 建树
void build_tree(int p, int l, int r, int x) { 
    if (l == r) {
        cnt[x][p] = (a[l] & d[x]) != 0;
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(lc(p), l, mid, x);
    build_tree(rc(p), mid + 1, r, x);
    push_up(p, x);
}
// 区间查询
int query(int p, int l, int r, int ql, int qr, int x) { 
    if (ql <= l && r <= qr) {
        return cnt[x][p];
    }
    push_down(p, l, r, x);
    int res = 0, mid = (l + r) >> 1;
    if (ql <= mid) {
        res += query(lc(p), l, mid, ql, qr, x);
    }
    if (qr > mid) {
        res += query(rc(p), mid + 1, r, ql, qr, x);
    }
    return res;
}
// 区间更新
void update(int p, int l, int r, int ql, int qr, int x) { 
    if (ql <= l && r <= qr) {
        move_tag(p, l, r, x);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r, x);
    if (ql <= mid) {
        update(lc(p), l, mid, ql, qr, x);
    }
    if (qr > mid) {
        update(rc(p), mid + 1, r, ql, qr, x);
    }
    push_up(p, x);
}
```
**核心实现思想**：同样采用二进制拆位，用数组 `cnt` 维护每个区间范围内 1 的个数。通过 `build_tree` 建树，`query` 进行区间查询，`update` 进行区间更新，利用懒标记 `tag` 优化更新操作。

#### YLWang 的核心代码
```cpp
// 建树
void Build(int num, int k, int l, int r) {
    if(l == r) {val[k] = v[num][l], tag[k] = 0; return;}
    Build(num, ls, l, mid); Build(num, rs, mid+1, r);
    val[k] = val[ls] + val[rs];
}
// 下传标记
void pushdown(int k, int l, int r) {
    if(tag[k]) {
        tag[k] = 0, tag[ls] ^= 1, tag[rs] ^= 1;
        val[ls] = (mid-l+1) - val[ls];
        val[rs] = (r - mid) - val[rs];
    }
} 
// 区间查询
int query(int k, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) return val[k];
    pushdown(k, l, r); 
    if(qr <= mid) return query(ls, l, mid, ql, qr);
    else if(mid < ql) return query(rs, mid+1, r, ql, qr);
    else return query(ls, l, mid, ql, mid) + query(rs, mid+1, r, mid+1, qr);
}
// 区间更新
void rev(int k, int l, int r, int rl, int rr) {
    if(l == rl && r == rr) {
        tag[k] ^= 1; val[k] = (r - l + 1) - val[k];
        return;
    }
    pushdown(k, l, r);
    if(rr <= mid) rev(ls, l, mid, rl, rr);
    else if(mid < rl) rev(rs, mid+1, r, rl, rr);
    else {rev(ls, l, mid, rl, mid); rev(rs, mid+1, r, mid+1, rr);}
    val[k] = val[ls] + val[rs];
}
```
**核心实现思想**：用 21 棵线段树分别维护每一个位置上的数的二进制位，将问题转化为维护 01 串的区间异或和区间询问 1 的个数，通过 `Build` 建树，`pushdown` 下传标记，`query` 进行区间查询，`rev` 进行区间更新。

### 最优关键思路或技巧
- **二进制拆位**：将整数序列拆成多个 01 串，把区间异或问题转化为 01 串的区间取反问题，利用线段树维护每个二进制位上 1 的个数。
- **懒标记优化**：在区间更新时使用懒标记，避免不必要的更新操作，提高效率。

### 拓展思路
同类型题或类似算法套路：
- 涉及区间修改和区间查询的问题，如区间加减、区间乘除等，可考虑使用线段树结合懒标记的方法。
- 对于位运算相关的问题，二进制拆位是一种常见的思路，可将复杂的位运算问题转化为简单的 01 操作。

### 推荐题目
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：区间修改和区间查询的基础线段树模板题。
- [P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)：涉及区间乘法和加法的线段树问题。
- [P2574 XOR的艺术](https://www.luogu.com.cn/problem/P2574)：与本题类似，维护 01 串的区间异或和区间求和问题。

### 个人心得摘录与总结
部分题解提到传统线段树无法实现区间异或，原因在于对一个区间异或后无法直接维护它们的和，从而引出二进制拆位的思路。这提醒我们在遇到复杂的区间操作问题时，要善于将问题进行转化，找到合适的数据结构和算法来解决。同时，对于位运算问题，二进制拆位是一种常用且有效的方法。 

---
处理用时：76.76秒