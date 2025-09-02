# 题目信息

# Compression

## 题目描述

You are given a binary matrix $ A $ of size $ n \times n $ . Let's denote an $ x $ -compression of the given matrix as a matrix $ B $ of size $ \frac{n}{x} \times \frac{n}{x} $ such that for every $ i \in [1, n], j \in [1, n] $ the condition $ A[i][j] = B[\lceil \frac{i}{x} \rceil][\lceil \frac{j}{x} \rceil] $ is met.

Obviously, $ x $ -compression is possible only if $ x $ divides $ n $ , but this condition is not enough. For example, the following matrix of size $ 2 \times 2 $ does not have any $ 2 $ -compression:

 $ 01 $   $ 10 $ For the given matrix $ A $ , find maximum $ x $ such that an $ x $ -compression of this matrix is possible.

Note that the input is given in compressed form. But even though it is compressed, you'd better use fast input.

## 说明/提示

The first example corresponds to the matrix:

 $ 11100111 $   $ 11100111 $   $ 11100111 $   $ 00000000 $   $ 00000000 $   $ 11100111 $   $ 11100111 $   $ 11100111 $ It is easy to see that the answer on this example is $ 1 $ .

## 样例 #1

### 输入

```
8
E7
E7
E7
00
00
E7
E7
E7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
7
F
F
F
```

### 输出

```
1
```

# AI分析结果

### 题目翻译
# 压缩

## 题目描述
给定一个大小为 $ n \times n $ 的二进制矩阵 $ A $。我们将给定矩阵的 $ x $ - 压缩定义为一个大小为 $ \frac{n}{x} \times \frac{n}{x} $ 的矩阵 $ B $，使得对于每一个 $ i \in [1, n] $，$ j \in [1, n] $，都满足条件 $ A[i][j] = B[\lceil \frac{i}{x} \rceil][\lceil \frac{j}{x} \rceil] $。

显然，只有当 $ x $ 能整除 $ n $ 时，$ x $ - 压缩才有可能实现，但这个条件并不充分。例如，下面这个 $ 2 \times 2 $ 的矩阵就没有任何 $ 2 $ - 压缩：
$ 01 $  
$ 10 $  

对于给定的矩阵 $ A $，找出最大的 $ x $，使得该矩阵的 $ x $ - 压缩是可行的。

请注意，输入是以压缩形式给出的。不过，即使输入是压缩的，你最好还是使用快速输入。

## 说明/提示
第一个样例对应的矩阵为：
$ 11100111 $  
$ 11100111 $  
$ 11100111 $  
$ 00000000 $  
$ 00000000 $  
$ 11100111 $  
$ 11100111 $  
$ 11100111 $  

很容易看出，这个样例的答案是 $ 1 $。

## 样例 #1
### 输入
```
8
E7
E7
E7
00
00
E7
E7
E7
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4
7
F
F
F
```
### 输出
```
1
```

### 算法分类
数学

### 综合分析与结论
- **思路对比**：
    - __DICS的题解通过分别计算一行内的最大压缩幅度（所有`01`段长度的最大公约数）和行与行之间的最大压缩幅度（相等行数量的最大公约数），最后取这两个最大公约数的最大公约数得到结果。
    - ciwomuli的题解使用`bitset`存储矩阵，从最大可能的压缩倍数开始枚举，通过判断每一组行是否相同以及每一组列是否相同来确定是否可以进行该倍数的压缩。
- **算法要点对比**：
    - __DICS的题解核心在于对矩阵的压缩幅度进行数学计算，利用最大公约数来求解。
    - ciwomuli的题解核心在于使用`bitset`存储矩阵和枚举压缩倍数进行判断。
- **解决难点对比**：
    - __DICS的题解难点在于对矩阵压缩幅度的计算，特别是一行内`01`段长度的处理和行与行之间的比较。
    - ciwomuli的题解难点在于如何高效地使用`bitset`进行矩阵元素的存储和比较，以及枚举过程中的判断逻辑。

### 题解评分
- __DICS：3星。思路较清晰，代码实现复杂但效率高，有一定的优化，但代码可读性一般。
- ciwomuli：2星。思路简单直接，但代码实现较冗长，缺乏优化，可读性一般。

由于所有题解都不足4星，以下给出通用建议与扩展思路：
- **通用建议**：在处理矩阵相关问题时，可以根据矩阵的特点选择合适的数据结构进行存储，如`bitset`、数组等。对于涉及到倍数、公约数等问题，可以考虑使用数学方法进行求解。在实现过程中，要注意代码的可读性和优化，避免不必要的计算。
- **扩展思路**：对于矩阵压缩问题，可以进一步考虑不同的压缩规则和条件，如非二进制矩阵的压缩、不同形状矩阵的压缩等。同时，可以结合其他算法，如动态规划、分治等，来解决更复杂的矩阵压缩问题。

### 重点代码
#### __DICS的题解
```cpp
// 计算最大公约数
inline int __gcd(int a, int b) {
    int temp;
    while (b) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 处理一行，计算该行的最大压缩幅度
int process_line() {
    // ... 具体实现省略 ...
}

int main() {
    scanf("%d", &n);
    int cnt = 1;
    scanf("%s", cur);
    int line = process_line();
    memcpy(last, cur, sizeof last);
    bool first_col = true;
    for (int i = 1; i < n && line != 1; ++i) {
        scanf("%s", cur);
        if (strcmp(cur, last) == 0) {
            ++cnt;
        } else {
            line = __gcd(line, process_line());
            memcpy(last, cur, sizeof last);
            if (first_col) column = cnt, first_col = false;
            else column = __gcd(column, cnt);
            cnt = 1;
        }
    }
    if (first_col) column = cnt;
    printf("%d\n", __gcd(line, column));
}
```
核心实现思想：通过`process_line`函数处理每一行，计算该行的最大压缩幅度，然后在`main`函数中比较行与行之间的关系，计算行与行之间的最大压缩幅度，最后取两者的最大公约数得到最终结果。

#### ciwomuli的题解
```cpp
const int maxn = 5220;
bitset<maxn> b[maxn];

int main(){
    int n;
    read(n);
    for(int i=1;i<=n;i++){
        for (int j = 1; j < n;j+=4){
            char ch=getchar();
            while(isspace(ch))
                ch = getchar();
            if(ch=='8' || ch=='9' || ch=='A' || ch=='B' || ch=='C' || ch=='D' || ch=='E' || ch=='F')
                b[i][j] = 1;
            if(ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='C' || ch=='D' || ch=='E' || ch=='F')
                b[i][j+1] = 1;
            if(ch=='2' || ch=='3' || ch=='6' || ch=='7' || ch=='A' || ch=='B' || ch=='E' || ch=='F')
                b[i][j+2] = 1;
            if(ch=='1' || ch=='3' || ch=='5' || ch=='7' || ch=='9' || ch=='B' || ch=='D' || ch=='F')
                b[i][j+3] = 1;
        }
    }
    for (int ans = n; ans >= 2;ans--){
        if (n % ans != 0)
            continue;
        bool ok=true;
        for (int i = 1; i < n;i+=ans){
            for (int j = i+1; j < i + ans;j++){
                ok &= (b[j] == b[i]);
            }
            if(!ok)
                break;
            for (int j = 1; j < n;j+=ans){
                for (int k = j+1; k < j + ans;k++)
                    ok &= (b[i][k] == b[i][k - 1]);
                if(!ok)
                    break;
            }
        }
        if(ok){
            cout << ans << endl;
            return 0;
        }
    }
    puts("1");
}
```
核心实现思想：使用`bitset`存储矩阵，从最大可能的压缩倍数开始枚举，通过判断每一组行是否相同以及每一组列是否相同来确定是否可以进行该倍数的压缩。

### 推荐洛谷题目
1. P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题
2. P1372 又是毕业季II
3. P2651 添加括号III

### 个人心得
两个题解均未包含个人心得。

---
处理用时：53.25秒