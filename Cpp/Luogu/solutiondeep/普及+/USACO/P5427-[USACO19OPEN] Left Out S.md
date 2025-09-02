# 题目信息

# [USACO19OPEN] Left Out S

## 题目描述

Farmer John 正在尝试给他的牛群拍照。根据以往的经验，他知道这一工作往往结果不怎么样。

这一次，Farmer John 购买了一台昂贵的无人机，想要拍一张航拍照。为了使照片尽可能好看，他想让他的奶牛们在拍照时都朝向同一个方向。奶牛们现在在一块有围栏的草地上排列成 $N \times N$（$2 \leq N \leq 1000$）的方阵，例如：

```
RLR
RRL
LLR
```

这里，字符 `R` 表示一头朝右的奶牛，字符 `L` 表示一头朝左的奶牛。由于奶牛们都挤在一起，Farmer John 没办法走到某一头奶牛面前让她调转方向。他能做的只有对着某一行或某一列的奶牛喊叫让她们调转方向，使得被叫到的这一行或列内的所有 `L` 变为 `R`，`R` 变为 `L`。Farmer John 可以对任意多的行或列发号施令，也可以对同一行或列多次发令。

就如同 Farmer John 想象的，他发现他不可能让他的奶牛们都朝向同一个方向。他最多能做的是让所有奶牛中除了一头之外都朝向相同的方向。请找出这样的一头奶牛。


## 说明/提示

在这个例子中，位于第 $1$ 行第 $1$ 列（左上角）的奶牛是那头令人讨厌的奶牛，因为 Farmer John 可以喊叫第 $2$ 行和第 $3$ 列来让所有奶牛都面向左侧，只有这一头奶牛面向右侧。

## 样例 #1

### 输入

```
3
RLR
RRL
LLR```

### 输出

```
1 1```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何解决将 $N×N$ 的 01 矩阵通过翻转行或列，使得除一个元素外其他元素相同的问题。大部分题解采用先将第一行和第一列置为 0（或 1），再分情况讨论特殊元素位置的思路，也有部分题解使用枚举、暴力判断等方法。各题解在思路清晰度、代码可读性和优化程度上有所差异。

### 所选题解
- **作者：Lolierl (赞：31)，4星**
    - **关键亮点**：思路清晰，对各种情况的分析详细，代码实现简洁明了，注释丰富。
    - **个人心得**：无
- **作者：Rainybunny (赞：11)，4星**
    - **关键亮点**：提供了 $O(n^3)$ 和 $O(n^2)$ 两种解法，对每种解法的思路和复杂度分析清晰，有配图辅助理解。
    - **个人心得**：无
- **作者：chihik (赞：5)，4星**
    - **关键亮点**：将问题分为三种情况讨论，逻辑清晰，代码结构良好，通过函数封装不同情况的判断。
    - **个人心得**：无

### 重点代码及核心思想
#### Lolierl 的题解
```cpp
// 翻转第一行和第一列使其为 0
for(int i = 1; i <= n; i++)
    if(a[i][1])
        for(int j = 1; j <= n; j++)
            a[i][j] ^= 1;
for(int i = 2; i <= n; i++)
    if(a[1][i])
        for(int j = 1; j <= n; j++)
            a[j][i] ^= 1;
// 通过子矩阵和判断情况
int f = 0; 
for(int i = 2; i <= n; i++)
    for(int j = 2; j <= n; j++)
        f += a[i][j]; 
if(f == (n - 1) * (n - 1))
{
    if(n == 2)printf("-1\n"); else printf("1 1\n"); 
    return 0; 
}
else if(f == 1)
{
    for(int i = 2; i <= n; i++)
        for(int j = 2; j <= n; j++)
            if(a[i][j]){printf("%d %d", i, j); return 0; }
}
else if(f == n - 1)
{
    for(int i = 1; i <= n; i++)
    {
        int s = 0; 
        for(int j = 1; j <= n; j++)
            s += a[i][j]; 
        if(s == n - 1){printf("%d %d", i, 1); return 0; }
    }
    for(int i = 1; i <= n; i++)
    {
        int s = 0; 
        for(int j = 1; j <= n; j++)
            s += a[j][i]; 
        if(s == n - 1){printf("%d %d", 1, i); return 0; }
    }
}
printf("-1"); 
```
**核心思想**：先将第一行和第一列置为 0，然后计算子矩阵的和，根据和的不同情况判断特殊元素的位置。

#### Rainybunny 的题解
```cpp
// 第一行置 0 
for (Int i = 1; i <= n; ++ i ) {
    if ( mp[1][i] ) {
        for ( Int j = 1; j <= n; ++ j ) {
            mp[j][i] ^= 1;
        }
    }
}
// 第一列置 0 
for ( Int i = 1; i <= n; ++ i ) {
    if ( mp[i][1] ) {
        for ( Int j = 1; j <= n; ++ j ) {
            mp[i][j] ^= 1;
        }
    }
}
int s = 0;
for ( Int i = 2; i <= n; ++ i ) {
    for ( Int j = 2; j <= n; ++ j ) {
        s += mp[i][j];
    }
}
if ( s == ( n - 1 ) * ( n - 1 ) ) { // 情况 1 
    puts ( n == 2 ? "-1" : "1 1" );
    return ;
}
if ( s == 1 ) { // 情况 2 
    for ( Int i = 2; i <= n; ++ i ) {
        for ( Int j = 1; j <= n; ++ j ) {
            if ( mp[i][j] ) {
                printf ( "%d %d\n", i, j );
                return ;
            }
        }
    }
}
if ( s == n - 1 ) { // 情况 3 
    for ( Int i = 2; i <= n; ++ i ) {
        static int s; s = 0;
        for ( Int j = 2; j <= n; ++ j ) {
            s += mp[i][j];
        }
        if ( s == n - 1 ) {
            printf ( "%d 1\n", i );
            return ;
        } else if ( s ) {
            break;
        }
    }
    for ( Int j = 2; j <= n; ++ j ) {
        for ( Int i = 2; i <= n; ++ i ) {
            static int s; s = 0;
            for ( Int i = 2; i <= n; ++ i ) {
                s += mp[i][j];
            }
        }
        if ( s == n - 1 ) {
            printf ( "1 %d\n", j );
            return ;
        } else if ( s ) {
            break;
        }
    }
}
puts ( "-1" );
```
**核心思想**：同样先将第一行和第一列置为 0，然后根据子矩阵和的不同情况判断特殊元素的位置。

#### chihik 的题解
```cpp
void operation( int x , bool f ) {	//将一行或一列取反
    if( f )
        for( int i = 1 ; i <= n ; i ++ )
            state[ x ][ i ] = !state[ x ][ i ];
    else
        for( int i = 1 ; i <= n ; i ++ )
            state[ i ][ x ] = !state[ i ][ x ];
}
bool check1( ) {
    for( int i = 2 ; i <= n ; i ++ )
        for( int j = 2 ; j <= n ; j ++ )
            if( state[ i ][ j ] == 0 ) return 0;
    return 1;
}
bool check2( ) {
    x = 1005 , y = 1005;
    bool f = 1;
    for( int i = 2 ; i <= n ; i ++ )
        for( int j = 2 ; j <= n ; j ++ )
            if( state[ i ][ j ] == 1 ) {
                if( f )
                    f = 0 , x = i , y = j;
                else
                    return 0;
            }
    return !f;
}
bool check3( ) {
    x = 1005 , y = 1005;
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 2 ; j <= n ; j ++ ) {
            if( !state[ i ][ j ] ) break;
            if( j == n ) 
                update( i , 1 );
        }
    for( int j = 1 ; j <= n ; j ++ )
        for( int i = 2 ; i <= n ; i ++ ) {
            if( !state[ i ][ j ] ) break;
            if( i == n ) 
                update( 1 , j );
        }
    return ( x == 1005 || y == 1005 ) ? 0 : 1; 
}

int main( ) {
    scanf("%d",&n);
    char c;
    for( int i = 1 ; i <= n ; i ++ ) {
        getchar( );
        for( int j = 1 ; j <= n ; j ++ )
            scanf("%c",&c) , state[ i ][ j ] = c == 'L' ? 0 : 1;
    }
    for( int i = 1 ; i <= n ; i ++ )
        if( state[ i ][ 1 ] ) operation( i , 1 );
    for( int i = 1 ; i <= n ; i ++ )
        if( state[ 1 ][ i ] ) operation( i , 0 );
    
    if( check1( ) ) printf("1 1\n");
    else if( check2( ) ) printf("%d %d\n",x,y);
    else if( check3( ) ) printf("%d %d\n",x,y); 
    else printf("-1\n");
    return 0;
}
```
**核心思想**：通过 `operation` 函数翻转行或列，将第一行和第一列置为 1，然后通过 `check1`、`check2`、`check3` 三个函数分别判断三种不同情况，根据判断结果输出特殊元素的位置。

### 最优关键思路或技巧
- **先规范矩阵**：将第一行和第一列置为 0（或 1），可以简化后续的判断过程。
- **分情况讨论**：将特殊元素的位置分为三种情况（左上角、第一行或第一列除左上角、其他位置），分别进行判断。
- **利用子矩阵和**：通过计算子矩阵的和，快速判断特殊元素的位置。

### 可拓展之处
同类型题或类似算法套路：
- 矩阵操作类问题，如矩阵的旋转、翻转、染色等。
- 状态判断类问题，通过对矩阵状态的分析和判断，找出满足条件的元素或状态。

### 推荐题目
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：涉及矩阵中元素的放置和状态判断。
- [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)：需要对矩阵进行遍历和状态转移。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：涉及矩阵的染色和连通性判断。

### 个人心得摘录与总结
- **PPL_**：上午考试爆搜未 AC，听大佬思路后理解并实现。总结是遇到问题可以先尝试暴力搜索，再学习大佬思路优化。
- **crashed**：经验不足且时间分配有问题，做这类 01 方阵带操作问题应先规范某一行。总结是遇到此类问题要有规范矩阵的意识，合理分配时间。

---
处理用时：68.54秒