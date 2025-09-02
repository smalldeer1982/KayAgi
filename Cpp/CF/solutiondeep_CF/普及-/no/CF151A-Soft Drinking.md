# 题目信息

# Soft Drinking

## 题目描述

This winter is so cold in Nvodsk! A group of $ n $ friends decided to buy $ k $ bottles of a soft drink called "Take-It-Light" to warm up a bit. Each bottle has $ l $ milliliters of the drink. Also they bought $ c $ limes and cut each of them into $ d $ slices. After that they found $ p $ grams of salt.

To make a toast, each friend needs $ nl $ milliliters of the drink, a slice of lime and $ np $ grams of salt. The friends want to make as many toasts as they can, provided they all drink the same amount. How many toasts can each friend make?

## 说明/提示

A comment to the first sample:

Overall the friends have $ 4*5=20 $ milliliters of the drink, it is enough to make $ 20/3=6 $ toasts. The limes are enough for $ 10*8=80 $ toasts and the salt is enough for $ 100/1=100 $ toasts. However, there are 3 friends in the group, so the answer is $ min(6,80,100)/3=2 $ .

## 样例 #1

### 输入

```
3 4 5 10 8 100 3 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 100 10 1 19 90 4 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
10 1000 1000 25 23 1 50 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 软饮

## 题目描述
今年冬天，Nvodsk 格外寒冷！一群 \(n\) 个朋友决定购买 \(k\) 瓶名为“轻松畅饮”的软饮料来暖暖身子。每瓶饮料有 \(l\) 毫升。他们还买了 \(c\) 个酸橙，并将每个酸橙切成 \(d\) 片。之后，他们准备了 \(p\) 克盐。

为了制作一份敬酒饮品，每个朋友需要 \(nl\) 毫升的饮料、一片酸橙和 \(np\) 克盐。朋友们希望在保证每个人喝的量相同的情况下，尽可能多地制作敬酒饮品。那么每个朋友可以制作多少份敬酒饮品呢？

## 说明/提示
对第一个样例的注释：
总体而言，朋友们共有 \(4×5 = 20\) 毫升的饮料，这足够制作 \(20÷3 = 6\) 份敬酒饮品。酸橙足够制作 \(10×8 = 80\) 份敬酒饮品，盐足够制作 \(100÷1 = 100\) 份敬酒饮品。然而，小组中有 3 个朋友，所以答案是 \(min(6, 80, 100)÷3 = 2\)。

## 样例 #1
### 输入
```
3 4 5 10 8 100 3 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5 100 10 1 19 90 4 3
```
### 输出
```
3
```

## 样例 #3
### 输入
```
10 1000 1000 25 23 1 50 1
```
### 输出
```
0
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路基本一致，都是先分别计算出饮料、柠檬片、盐各自能满足制作敬酒饮品的份数，即饮料能做 \(k*l/nl\) 份，柠檬片能做 \(c*d\) 份，盐能做 \(p/np\) 份，然后取这三个份数中的最小值，最后将最小值除以朋友的数量 \(n\)，得到每个朋友能制作的敬酒饮品份数。各题解在算法要点和解决难点上并无本质区别，主要差异在于代码实现的细节和注释的详细程度。

### 所选的题解
- **作者：Reywmp (5星)**
  - **关键亮点**：对题目条件和推导过程解释详细，代码中自定义了读入函数 `read` 以及取最值函数 `mx` 和 `mn`，虽然对于本题来说稍显复杂，但展示了一定的代码实现技巧。
  - **个人心得**：无
  ```cpp
  void read(int &x)
  {
       x=0;int w=1;
       char ch=getchar();
       while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
       if(ch=='-')w=-1,ch=getchar();
       while(ch>='0'&&ch<='9')
       {x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
       x*=w;
  }
  int mx(int a,int b){return a>b?a:b;}
  int mn(int a,int b){return a<b?a:b;}
  int n,k,l,c,d,p,nl,np;
  int main()
  {
      read(n);read(k);
      read(l);read(c);read(d);read(p);read(nl);read(np);
      int ans,tmp;
      tmp=mn(k*l/nl,p/np);
      ans=c*d;
      ans=mn(tmp,ans);
      printf("%d",ans/n);
      putchar('\n');
      return 0;
  }
  ```
- **作者：ShineEternal (4星)**
  - **关键亮点**：代码简洁明了，先分别计算出饮料、柠檬、盐能制作的份数，再用 `fmin` 函数取最小值，最后除以 \(n\) 输出结果，逻辑清晰。
  - **个人心得**：无
  ```cpp
  int main()
  {
      int n,k,l,c,d,p,nl,np;
      scanf("%d%d%d%d%d%d%d%d",&n,&k,&l,&c,&d,&p,&nl,&np);
      int x=k*l/nl;
      int y=c*d;
      int z=p/np;
      int ans=fmin(fmin(x,y),z);
      printf("%d\n",ans/n);
      return 0;
  }
  ```

### 最优关键思路或技巧
本题关键在于理解要根据三种材料各自能满足制作的份数来确定最终能制作的份数，需取三者最小值，这是基于实际情况的数学逻辑判断。在代码实现上，简洁明了地分别计算各材料份数并取最小值是关键技巧。

### 可拓展之处
此类题目属于基于实际场景的数学计算类问题，类似套路是分析场景中的各种限制条件，将其转化为数学表达式，通过计算和比较得出结果。同类型题可涉及多种材料按不同比例组合使用，计算可完成任务的数量等。

### 洛谷推荐题目
- [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：基础的输入输出与简单数学运算题目，可巩固基本的代码实现能力。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔的价格和数量，计算满足需求的最小花费，与本题类似需分析不同条件并进行数学计算。
- [P5709 【深基2.例12】上学迟到](https://www.luogu.com.cn/problem/P5709)：结合路程、速度、时间等条件进行数学计算，判断是否迟到，同样是基于实际场景的数学问题。 

---
处理用时：44.05秒