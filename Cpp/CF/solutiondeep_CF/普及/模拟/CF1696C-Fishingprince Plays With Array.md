# 题目信息

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56```

### 输出

```
Yes
Yes
No
Yes
No```

# AI分析结果

### 题目翻译
#### Fishingprince玩数组

#### 题目描述
Fishingprince正在玩一个数组 $ [a_1,a_2,\dots,a_n] $ 。他还有一个神奇的数字 $ m $ 。

他可以对该数组进行以下两种操作：
- 选择 $ 1\le i\le n $ ，使得 $ a_i $ 能被 $ m $ 整除（即存在一个整数 $ t $ ，使得 $ m \cdot t = a_i $ ）。将 $ a_i $ 替换为 $ m $ 个 $ \frac{a_i}{m} $ 。其他元素的顺序不变。例如，当 $ m = 2 $ 且 $ a = [2,3] $ ，$ i = 1 $ 时，$ a $ 变为 $ [1,1,3] $ 。
- 选择 $ 1\le i\le n - m + 1 $ ，使得 $ a_i = a_{i + 1} = \dots = a_{i + m - 1} $ 。将这 $ m $ 个元素替换为一个 $ m \cdot a_i $ 。其他元素的顺序不变。例如，当 $ m = 2 $ 且 $ a = [3,2,2,3] $ ，$ i = 2 $ 时，$ a $ 变为 $ [3,4,3] $ 。

注意，数组的长度在操作过程中可能会发生变化。上述的 $ n $ 定义为数组的当前长度（可能与输入中的 $ n $ 不同）。

Fishingprince还有另一个数组 $ [b_1,b_2,\dots,b_k] $ 。请判断他是否可以通过任意数量（可能为零）的操作将 $ a $ 转换为 $ b $ 。

#### 说明/提示
在样例的第一个测试用例中，我们可以对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ 。

在样例的第二个测试用例中，我们可以：
- 对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ 。
- 对 $ i = 4 $ 执行第二个操作：$ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ 。
- 对 $ i = 3 $ 执行第一个操作：$ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ 。
- 对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ 。
- 对 $ i = 3 $ 执行第二个操作：$ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ 。
- 对 $ i = 2 $ 执行第二个操作：$ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ 。

#### 样例 #1
##### 输入
```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56
```
##### 输出
```
Yes
Yes
No
Yes
No
```

### 综合分析与结论
这些题解的核心思路一致，都利用两个操作互逆的特性，将问题转化为判断数组 $a$ 和 $b$ 经过充分拆分后是否相等。为避免拆分后数据量过大，都采用结构体记录数字及其出现次数。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|lenlen|先将 $a$ 数组拆分存入双端队列，再逐步拆分 $b$ 数组并与队列元素比较|双端队列存储拆分后的 $a$ 数组，逐步匹配 $b$ 数组|避免同时存储两个拆分后数组，节省空间|4星|
|Avocadooo|建立新序列 $A'$ 和 $B'$，将 $A$ 和 $B$ 不停拆分得到，用结构体存储去重后对比|结构体存储拆分后的数字及其出现次数，合并相邻相同数字|拆分后数据量大，用结构体去重|4星|
|SoyTony|将 $a$ 和 $b$ 分别完全拆开，用 vector 压缩相邻相同元素后判断是否相同|vector 压缩相邻相同元素|拆分后数据量大，用 vector 压缩|3星|
|jiangtaizhe001|把两个数组中所有 $m$ 的倍数拆开，用结构体表示数组，判断是否相同|结构体存储数字及其重复次数|拆分后数据量大，用结构体表示数组|4星|
|JS_TZ_ZHR|将 $a$ 数组拆分存入栈，再逐步拆分 $b$ 数组并与栈顶元素比较|栈存储拆分后的 $a$ 数组，逐步匹配 $b$ 数组|避免同时存储两个拆分后数组，节省空间|4星|

### 所选题解
- **lenlen（4星）**：关键亮点是使用双端队列存储拆分后的 $a$ 数组，逐步匹配 $b$ 数组，避免同时存储两个拆分后数组，节省空间。
- **Avocadooo（4星）**：关键亮点是用结构体存储拆分后的数字及其出现次数，合并相邻相同数字，有效去重。
- **jiangtaizhe001（4星）**：关键亮点是用结构体表示数组，存储数字及其重复次数，便于判断拆分后数组是否相同。

### 重点代码及核心实现思想
#### lenlen
```cpp
deque <hl> q;
for(int i=1;i<=n;i++) 
{
    scanf("%d",&a[i]);s1+=a[i];
    int k=1;
    while(a[i]%m==0) a[i]/=m,k*=m;
    q.push_back((hl){a[i],k});//先将a  按顺序  扔进双端队列
}
for(int i=1;i<=nn&&!flag;i++)
{
    int k=1;
    while(b[i]%m==0) b[i]/=m,k*=m;//一个一个判断b
    while(k)
    {
        if(q.empty())
        {
            flag=1;
            break;
        }
        tmp=q.front();q.pop_front();
        if(tmp.d!=b[i]) //分解出的类型不同
        {
            flag=1;
            break;
        }
        if(tmp.sum<=k) k-=tmp.sum;//数量不够，继续拿数出来
        else
        {
            q.push_front((hl){tmp.d,tmp.sum-k});//注意，剩下的因为要按原来顺序插入，所以是插入队头
            k=0;
        }
    }
}
```
核心思想：先将 $a$ 数组拆分后存入双端队列，再逐步拆分 $b$ 数组，与队列元素匹配，若不匹配则标记不可转换。

#### Avocadooo
```cpp
for(int i=1,x,y;i<=n;i++)
{
    scanf("%d",&x);
    sum+=x,y=1;
    while(x%m==0) x/=m,y*=m;
    if(!cnt || x!=a[cnt].rt) a[++cnt].rt=x,a[cnt].cnt=y;
    else if(x==a[cnt].rt) a[cnt].cnt+=y;
}
for(int i=1,x,y;i<=k;i++)
{
    scanf("%d",&x);
    sum-=x,y=1;
    while(x%m==0) x/=m,y*=m;
    if(!a2 || x!=b[a2].rt) b[++a2].rt=x,b[a2].cnt=y;
    else if(x==b[a2].rt) b[a2].cnt+=y;
}
if(sum || cnt!=a2)
{
    puts("NO");
    continue;
}
for(int i=1;i<=a2;i++)
{
    if(a[i].rt!=b[i].rt || a[i].cnt!=b[i].cnt)
    {
        f=1;
        break;
    }
}
```
核心思想：分别对 $a$ 和 $b$ 数组拆分，用结构体存储拆分后的数字及其出现次数，合并相邻相同数字，最后比较两个结构体数组是否相同。

#### jiangtaizhe001
```cpp
int solve(int arr[],JTZ res[],int len){
    int nlen=0,tmp,i; ll cnt;
    for(i=1;i<=len;i++){
        cnt=1; tmp=arr[i];
        while(tmp%m==0) tmp/=m,cnt*=m;
        if(nlen==0||res[nlen].s!=tmp) nlen++,res[nlen].num=cnt,res[nlen].s=tmp;
        else res[nlen].num+=cnt;
    } return nlen;
}
len1=solve(a,tmpa,n); len2=solve(b,tmpb,k);
if(len1!=len2){ puts("No"); return; }
for(i=1;i<=len1;i++) if(tmpa[i].num!=tmpb[i].num||tmpa[i].s!=tmpb[i].s){ puts("No"); return; }
puts("Yes"); return;
```
核心思想：定义 `solve` 函数对数组进行拆分，用结构体存储拆分后的数字及其重复次数，最后比较两个结构体数组是否相同。

### 最优关键思路或技巧
- **操作互逆思想**：利用拆分和合并操作互逆，将问题转化为判断拆分后数组是否相等。
- **结构体存储**：使用结构体记录数字及其出现次数，避免拆分后数据量过大。

### 拓展思路
同类型题可考虑其他可逆操作的转换问题，如状态转移、图形变换等。类似算法套路可用于判断两个状态是否可通过特定可逆操作相互转换，关键在于找到合适的中间状态进行比较。

### 推荐洛谷题目
- [P1043 数字游戏](https://www.luogu.com.cn/problem/P1043)
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

### 个人心得
题解中未包含个人心得相关内容。

---
处理用时：62.91秒