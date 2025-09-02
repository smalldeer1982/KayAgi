# 题目信息

# Parity Shuffle Sorting

## 题目描述

You are given an array $ a $ with $ n $ non-negative integers. You can apply the following operation on it.

- Choose two indices $ l $ and $ r $ ( $ 1 \le l < r \le n $ ).
- If $ a_l + a_r $ is odd, do $ a_r := a_l $ . If $ a_l + a_r $ is even, do $ a_l := a_r $ .

Find any sequence of at most $ n $ operations that makes $ a $ non-decreasing. It can be proven that it is always possible. Note that you do not have to minimize the number of operations.

An array $ a_1, a_2, \ldots, a_n $ is non-decreasing if and only if $ a_1 \le a_2 \le \ldots \le a_n $ .

## 说明/提示

In the second test case, $ a $ changes like this:

- Select indices $ 3 $ and $ 4 $ . $ a_3 + a_4 = 3 $ is odd, so do $ a_4 := a_3 $ . $ a = [1, 1000000000, 3, 3, 5] $ now.
- Select indices $ 1 $ and $ 2 $ . $ a_1 + a_2 = 1000000001 $ is odd, so do $ a_2 := a_1 $ . $ a = [1, 1, 3, 3, 5] $ now, and it is non-decreasing.

In the first and third test cases, $ a $ is already non-decreasing.

## 样例 #1

### 输入

```
3
2
7 8
5
1 1000000000 3 0 5
1
0```

### 输出

```
0
2
3 4
1 2
0```

# AI分析结果

### 题目内容重写
# 奇偶洗牌排序

## 题目描述

给定一个包含 $n$ 个非负整数的数组 $a$。你可以对其进行以下操作：

- 选择两个下标 $l$ 和 $r$（$1 \le l < r \le n$）。
- 如果 $a_l + a_r$ 是奇数，则将 $a_r$ 赋值为 $a_l$；如果 $a_l + a_r$ 是偶数，则将 $a_l$ 赋值为 $a_r$。

找到最多 $n$ 次操作的序列，使得 $a$ 变为非递减。可以证明总是存在这样的序列。注意，你不需要最小化操作次数。

一个数组 $a_1, a_2, \ldots, a_n$ 是非递减的，当且仅当 $a_1 \le a_2 \le \ldots \le a_n$。

## 说明/提示

在第二个测试用例中，$a$ 的变化如下：

- 选择下标 $3$ 和 $4$。$a_3 + a_4 = 3$ 是奇数，所以将 $a_4$ 赋值为 $a_3$。$a = [1, 1000000000, 3, 3, 5]$。
- 选择下标 $1$ 和 $2$。$a_1 + a_2 = 1000000001$ 是奇数，所以将 $a_2$ 赋值为 $a_1$。$a = [1, 1, 3, 3, 5]$，此时数组已经非递减。

在第一个和第三个测试用例中，$a$ 已经是非递减的。

## 样例 #1

### 输入

```
3
2
7 8
5
1 1000000000 3 0 5
1
0
```

### 输出

```
0
2
3 4
1 2
0
```

### 算法分类
构造

### 题解分析与结论
所有题解的核心思路都是通过操作将数组中的所有元素统一为某个值，从而使数组非递减。具体实现上，大多数题解都选择先将数组的第一个和最后一个元素统一，然后根据奇偶性将中间的元素逐个统一。这种思路简单直接，且操作次数为 $n-1$，符合题目要求。

### 评分较高的题解
1. **作者：winter2020 (赞：11)**
   - **星级：5星**
   - **关键亮点**：思路清晰，代码简洁，直接通过奇偶性判断操作类型，操作次数为 $n-1$，符合题目要求。
   - **核心代码**：
     ```cpp
     void solve() {
         cin >> n;
         for (int i = 1; i <= n; i ++ ) cin >> a[i];
         if (n == 1) {
             puts("0");
             return;
         }
         cout << n - 1 << endl;
         cout << 1 << " " << n << endl;
         int c = (a[1] + a[n]) % 2? a[1] : a[n];
         for (int i = 2; i < n; i ++ )
             if (c + a[i] & 1) cout << 1 << " " << i << endl;
             else cout << i << " " << n << endl;
         return;
     }
     ```

2. **作者：shitingjia (赞：3)**
   - **星级：4星**
   - **关键亮点**：思路与 winter2020 类似，代码实现略有不同，同样通过奇偶性判断操作类型，操作次数为 $n-1$。
   - **核心代码**：
     ```cpp
     signed main(){
         ios::sync_with_stdio(0);
         cin>>t;
         while(t--){
             cin>>n;
             for(int i=1;i<=n;i++)	cin>>a[i];
             cout<<n-1<<endl;
             if(n!=1){
                 cout<<1<<" "<<n<<endl;
                 int sum=a[1]+a[n];
                 if(sum&1)	a[n]=a[1];
                 else	a[1]=a[n];
             }
             for(int i=2;i<n;i++){
                 int sum=a[i]+a[n];
                 if(sum&1)	cout<<1<<" "<<i<<endl;
                 else	cout<<i<<" "<<n<<endl;
             }
         }
         return 0;
     }
     ```

3. **作者：taojinchen (赞：2)**
   - **星级：4星**
   - **关键亮点**：思路与前两者一致，代码实现简洁，操作次数为 $n-1$，符合题目要求。
   - **核心代码**：
     ```cpp
     int main(){
         ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
         cin>>q;
         while(q--){
             cin>>n;
             for(i=1;i<=n;i++)	cin>>a[i];
             cout<<n-1<<"\n";
             if(n!=1){
                 cout<<1<<" "<<n<<"\n";
                 if((a[1]+a[n])&1)a[n]=a[1];
                 else a[1]=a[n];
             }
             for(i=2;i<n;i++){
                 if((a[i]+a[n])&1)cout<<1<<" "<<i<<"\n";
                 else cout<<i<<" "<<n<<"\n";
             }
         }
         return 0;
     }
     ```

### 最优关键思路或技巧
通过将数组的第一个和最后一个元素统一，然后根据奇偶性将中间的元素逐个统一，从而使得整个数组非递减。这种思路简单直接，且操作次数为 $n-1$，符合题目要求。

### 可拓展之处
类似的操作可以应用于其他需要将数组元素统一为某个值的题目，如将数组中的所有元素统一为最小值或最大值。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：39.93秒