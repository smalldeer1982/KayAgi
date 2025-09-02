# 题目信息

# Balls and Boxes

## 题目描述

Little Vasya had $ n $ boxes with balls in the room. The boxes stood in a row and were numbered with numbers from 1 to $ n $ from left to right.

Once Vasya chose one of the boxes, let's assume that its number is $ i $ , took all balls out from it (it is guaranteed that this box originally had at least one ball), and began putting balls (one at a time) to the boxes with numbers $ i+1 $ , $ i+2 $ , $ i+3 $ and so on. If Vasya puts a ball into the box number $ n $ , then the next ball goes to box $ 1 $ , the next one goes to box $ 2 $ and so on. He did it until he had no balls left in his hands. It is possible that Vasya puts multiple balls to the same box, and it is also possible that one or more balls will go to the box number $ i $ . If $ i=n $ , Vasya puts the first ball into the box number $ 1 $ , then the next ball goes to box $ 2 $ and so on.

For example, let's suppose that initially Vasya had four boxes, and the first box had $ 3 $ balls, the second one had $ 2 $ , the third one had $ 5 $ and the fourth one had $ 4 $ balls. Then, if $ i=3 $ , then Vasya will take all five balls out of the third box and put them in the boxes with numbers: $ 4,1,2,3,4 $ . After all Vasya's actions the balls will lie in the boxes as follows: in the first box there are $ 4 $ balls, $ 3 $ in the second one, $ 1 $ in the third one and $ 6 $ in the fourth one.

At this point Vasya has completely forgotten the original arrangement of the balls in the boxes, but he knows how they are arranged now, and the number $ x $ — the number of the box, where he put the last of the taken out balls.

He asks you to help to find the initial arrangement of the balls in the boxes.

## 样例 #1

### 输入

```
4 4
4 3 1 6
```

### 输出

```
3 2 5 4 ```

## 样例 #2

### 输入

```
5 2
3 2 0 2 7
```

### 输出

```
2 1 4 1 6 ```

## 样例 #3

### 输入

```
3 3
2 3 1
```

### 输出

```
1 2 3 ```

# AI分析结果

### 题目内容
# 球与盒子

## 题目描述
小瓦夏房间里有\(n\)个装着球的盒子。这些盒子排成一排，从左到右依次编号为\(1\)到\(n\)。

有一次，瓦夏选择了其中一个盒子，假设其编号为\(i\)，他将这个盒子里的所有球都取出来（保证这个盒子最初至少有一个球），然后开始依次将球（每次放一个）放入编号为\(i + 1\)、\(i + 2\)、\(i + 3\)等等的盒子中。如果瓦夏把球放入编号为\(n\)的盒子后，下一个球就会放入编号为\(1\)的盒子，再下一个放入编号为\(2\)的盒子，依此类推。他一直这样做，直到手中没有球为止。有可能瓦夏会将多个球放入同一个盒子，也有可能有一个或多个球会放入编号为\(i\)的盒子。如果\(i = n\)，瓦夏会将第一个球放入编号为\(1\)的盒子，然后下一个球放入编号为\(2\)的盒子，依此类推。

例如，假设最初瓦夏有四个盒子，第一个盒子有\(3\)个球，第二个盒子有\(2\)个球，第三个盒子有\(5\)个球，第四个盒子有\(4\)个球。那么，如果\(i = 3\)，瓦夏会从第三个盒子中取出所有\(5\)个球，并将它们放入编号为\(4\)、\(1\)、\(2\)、\(3\)、\(4\)的盒子中。在瓦夏所有操作完成后，球在盒子中的分布如下：第一个盒子有\(4\)个球，第二个盒子有\(3\)个球，第三个盒子有\(1\)个球，第四个盒子有\(6\)个球。

此时，瓦夏完全忘记了盒子中球最初的排列方式，但他知道现在球是如何排列的，以及数字\(x\)——他放入最后一个取出球的盒子的编号。

他请你帮忙找出盒子中球最初的排列方式。

## 样例 #1
### 输入
```
4 4
4 3 1 6
```
### 输出
```
3 2 5 4 
```

## 样例 #2
### 输入
```
5 2
3 2 0 2 7
```
### 输出
```
2 1 4 1 6 
```

## 样例 #3
### 输入
```
3 3
2 3 1
```
### 输出
```
1 2 3 
```

### 算法分类
模拟

### 题解综合分析与结论
三道题解思路本质相同，都是基于模拟反向推导初始球的分布。难点在于确定最初取出球的盒子位置，因为存在多个盒子球数可能同为最小值的情况。

三位作者都先找出当前球数的最小值，将每个盒子的球数减去该最小值，使至少一个盒子球数为\(0\)，从而缩小可能的初始取球盒子范围。之后利用已知的最后放球位置\(x\)，从\(x\)向前查找第一个球数为\(0\)的盒子，以此确定最初取球的盒子。不同之处在于实现细节和代码风格。

### 所选的题解
- **作者：_louhc（5星）**
    - **关键亮点**：思路清晰，代码简洁高效。通过自定义函数`pre`简化向前枚举的操作，逻辑连贯，可读性强。
    - **个人心得**：无
    - **重点代码及核心思想**：
```cpp
void pre( int &x ){//找前一个元素
    x--; if ( x == 0 ) x = N;
}

int main(){
    scanf( "%d%d", &N, &x );
    for ( int i = 1; i <= N; ++i ) scanf( "%I64d", &a[i] ), t = min( t, a[i] );//找最小值
    for ( int i = 1; i <= N; ++i ) a[i] -= t;//先减去最小值
    t *= N;
    while( a[x] ) a[x]--, t++, pre(x);//调整球数
    a[x] = t;
    for ( int i = 1; i <= N; ++i ) printf( "%I64d ", a[i] );
    return 0;
}
```
核心思想是先找出最小值并减去，然后从最后放球位置向前调整球数，找到最初取球盒子并恢复其球数。

- **作者：xyf007（4星）**
    - **关键亮点**：代码简洁明了，逻辑直接，通过`while(1)`循环从最后放球位置向前模拟，遇到球数为\(0\)的盒子即确定最初取球盒子并输出结果。
    - **个人心得**：强调要开`long long`类型，避免数据溢出。
    - **重点代码及核心思想**：
```cpp
long long n,x,a[100001];
int main(int argc, char const *argv[])
{
    std::cin>>n>>x;
    long long mn=9e18;
    for (long long i = 1; i <= n; ++i)
    {
        std::cin>>a[i];
        if (a[i]<mn)
        {
            mn=a[i];
        }
    }
    for (long long i = 1; i <= n; ++i)
    {
        a[i]-=mn;
    }
    long long now=x,sum=mn*n;
    while(1)
    {
        if (a[now]==0)
        {
            a[now]+=sum;
            for (long long i = 1; i <= n; ++i)
            {
                std::cout<<a[i]<<' ';
            }
            return 0;
        }
        --a[now];
        ++sum;
        now=now==1?n:now-1;
    }
    return 0;
}
```
核心思想是先减去最小值，从最后放球位置向前模拟，遇到\(0\)号盒子恢复其原始球数并输出。

- **作者：4526_（4星）**
    - **关键亮点**：详细分析了不同情况下最初取球盒子位置与球数的关系，虽然因情况复杂未采用直接判断的方法，但分析过程有助于理解问题本质。代码实现中通过从后向前遍历找到第一个\(0\)号盒子确定原始取球盒子。
    - **个人心得**：无
    - **重点代码及核心思想**：
```cpp
long long n,x,arr[100003],mmin=151926081715;

int main(){
    scanf("%lld %lld",&n,&x);
    for(register int i=1;i<=n;++i){
        scanf("%lld",&arr[i]);
        mmin= arr[i]<=mmin? arr[i] : mmin;
    }
    for(register int i=1;i<=n;++i) arr[i]-=mmin;
    for(register int i=x;;--i){
        if(i==0) i=n;
        if(arr[i]==0){
            arr[i]=arr[0]+mmin*n;
            break;
        }
        --arr[i];
        ++arr[0];
    }
    for(register int i=1;i<=n;++i) printf("%lld ",arr[i]);
    return 0;
}
```
核心思想同样是先减最小值，从最后放球位置向前遍历，找到第一个\(0\)号盒子并恢复其原始球数。

### 最优关键思路或技巧
先找出当前球数的最小值并从每个盒子球数中减去，利用最后放球位置\(x\)从后向前查找第一个球数为\(0\)的盒子来确定最初取球的盒子，这种方法简化了问题求解过程，避免了复杂的情况讨论。

### 可拓展思路
此类题目属于逆向模拟类型，类似套路是在已知最终状态和操作规则时，通过反向模拟操作来推导初始状态。可以拓展到其他具有类似操作和推导需求的场景，如物品分配、位置移动等逆向推导问题。

### 洛谷相似题目推荐
- [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：涉及字符串变换的逆向推导，与本题逆向模拟思路类似。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：通过逆向思维确定未被填充区域，和本题逆向推导初始状态有相似之处。
- [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)：从终点反向推导水源位置，也是逆向模拟的应用。 

---
处理用时：76.51秒