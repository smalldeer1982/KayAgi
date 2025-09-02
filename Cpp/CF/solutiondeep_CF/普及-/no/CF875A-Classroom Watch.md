# 题目信息

# Classroom Watch

## 题目描述

Eighth-grader Vova is on duty today in the class. After classes, he went into the office to wash the board, and found on it the number $ n $ . He asked what is this number and the teacher of mathematics Inna Petrovna answered Vova that $ n $ is the answer to the arithmetic task for first-graders. In the textbook, a certain positive integer $ x $ was given. The task was to add $ x $ to the sum of the digits of the number $ x $ written in decimal numeral system.

Since the number $ n $ on the board was small, Vova quickly guessed which $ x $ could be in the textbook. Now he wants to get a program which will search for arbitrary values of the number $ n $ for all suitable values of $ x $ or determine that such $ x $ does not exist. Write such a program for Vova.

## 说明/提示

In the first test case $ x=15 $ there is only one variant: $ 15+1+5=21 $ .

In the second test case there are no such $ x $ .

## 样例 #1

### 输入

```
21
```

### 输出

```
1
15
```

## 样例 #2

### 输入

```
20
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 课堂观察

## 题目描述
八年级学生沃瓦（Vova）今天在班里值日。下课后，他去办公室擦黑板，发现黑板上写着数字 $n$。他问这是什么数字，数学老师因娜·彼得罗夫娜（Inna Petrovna）告诉沃瓦，$n$ 是一道一年级算术题的答案。在课本中，给定了一个正整数 $x$。题目要求将 $x$ 与十进制下 $x$ 的各位数字之和相加。

由于黑板上的数字 $n$ 很小，沃瓦很快就猜出了课本中的 $x$ 可能是多少。现在他想要一个程序，对于任意给定的数字 $n$，找出所有合适的 $x$ 值，或者判断这样的 $x$ 不存在。请为沃瓦编写这样一个程序。

## 说明/提示
在第一个测试用例中，$x = 15$ 是唯一的解：$15 + 1 + 5 = 21$。

在第二个测试用例中，不存在这样的 $x$。

## 样例 #1
### 输入
```
21
```
### 输出
```
1
15
```

## 样例 #2
### 输入
```
20
```
### 输出
```
0
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举来寻找满足条件的 $x$ 值。由于直接从 $1$ 枚举到 $n$ 会超时，因此关键在于缩小枚举范围。题解们普遍利用数学推理得出，因为 $n$ 最大为 $10^9$，$x$ 的各位数字之和最大为 $81$（当 $x$ 为 $9$ 个 $9$ 组成的数时），所以只需从 $n - 81$ 枚举到 $n$ 即可。在枚举过程中，通过计算每个数的各位数字之和并与该数相加，判断是否等于 $n$，若相等则将其记录下来。

### 所选题解
- **Frank_R_Z（4星）**
  - 关键亮点：思路清晰，代码简洁易懂，自定义函数判断是否满足条件，逻辑明确。
  - 核心代码：
```cpp
bool ans(int x,int n)//自定义函数判断是否相同
{
    int k=x;
    while(x>0)
    {
        k+=x%10;
        x/=10;
    }
    if(k==n)return true;
    else return false;
}
int main()
{
    int n,k=0,a[1002],sum=0;
    cin>>n;
    for(int i=n-90;i<=n;i++)
    {
        if(ans(i,n))sum++,a[++k]=i;//引入自定义函数
    }
    cout<<sum<<endl;
    for(int i=1;i<=k;i++)
    {
        cout<<a[i]<<endl;//输出快乐
    }
    return 0;
}
```
核心实现思想：通过自定义函数 `ans` 计算一个数 $x$ 与其各位数字之和，判断是否等于 $n$。在 `main` 函数中，从 $n - 90$ 到 $n$ 进行枚举，将满足条件的 $x$ 存入数组并记录数量，最后输出结果。

- **Arghariza（4星）**
  - 关键亮点：运用数学推导确定枚举范围，使用快读快输优化输入输出，提高效率。
  - 核心代码：
```cpp
namespace mystd {
    #define maxl 1000100
    inline int read() {// 快读
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {// 快输
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
int calc(int x) {// 数位和
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}
int main() {
    n = read();
    for (int i = n - 81; i <= n; i++) {// 枚举
        if (i > 0 && calc(i) + i == n) {// 注意i到大于0
            ans[++cnt] = i;// 统计答案
        }
    }
    write(cnt);
    puts("");
    for (int i = 1; i <= cnt; i++) {
        write(ans[i]);
        puts("");
    }
    return 0;
}
```
核心实现思想：定义快读 `read` 和快输 `write` 函数优化输入输出。`calc` 函数计算一个数的各位数字之和。在 `main` 函数中，从 $n - 81$ 到 $n$ 进行枚举，将满足条件的 $x$ 存入数组并记录数量，最后使用快输输出结果。

- **AlicX（4星）**
  - 关键亮点：思路清晰，代码简洁，通过自定义函数计算数位和，实现枚举过程。
  - 核心代码：
```cpp
int work(int x){//计算这个数字的各个数位之和 
    int res=0;
    while(x) res+=x%10,x/=10;//累加 
    return res; 
}
signed main(){
    int n;
    cin>>n;
    for(int i=n-81;i<=n;i++) if(i+work(i)==n) ans[++cnt]=i;
    //从n-81开始枚举，只要这个数字加上它各个数位之和等于n，就加入数组 
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++) cout<<ans[i]<<endl;//升序输出 
    return 0;//Bye~
}
```
核心实现思想：`work` 函数计算一个数的各位数字之和。在 `main` 函数中，从 $n - 81$ 到 $n$ 进行枚举，将满足条件的 $x$ 存入数组并记录数量，最后输出结果。

### 最优关键思路或技巧
- **缩小枚举范围**：通过数学推理，发现 $x$ 与 $n$ 的差值最大为 $81$，从而将枚举范围从 $1$ 到 $n$ 缩小到 $n - 81$ 到 $n$，大大减少了时间复杂度。
- **自定义函数**：使用自定义函数计算一个数的各位数字之和，使代码结构更清晰，逻辑更明确。

### 可拓展之处
同类型题目可能会改变条件，例如将加法改为乘法，或者对 $x$ 有其他限制条件。类似算法套路可以用于解决一些需要枚举的数学问题，关键在于通过数学分析缩小枚举范围，提高效率。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合来解决问题。
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：需要枚举不同的数字组合来满足等式条件。
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：可以通过枚举和递推的方法来解决。

### 个人心得摘录与总结
- **TheMatrix**：第一次写题解，认识到对于大数据量不能暴力解决，要通过数学分析缩小范围，后续会继续努力提升题解质量。总结：在解决算法问题时，要避免盲目暴力枚举，学会运用数学知识优化算法。 

---
处理用时：49.83秒