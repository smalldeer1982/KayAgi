# 题目信息

# Candy Boxes

## 题目描述

There is an old tradition of keeping $ 4 $ boxes of candies in the house in Cyberland. The numbers of candies are special if their arithmetic mean, their median and their range are all equal. By definition, for a set $ {x_{1},x_{2},x_{3},x_{4}} $ ( $ x_{1}<=x_{2}<=x_{3}<=x_{4} $ ) arithmetic mean is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/4ced3a9ae4181924c136bcc46ede19844528fdef.png), median is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/2d7e14bfd580007a1d694763c07f2437bb7e66e6.png) and range is $ x_{4}-x_{1} $ . The arithmetic mean and median are not necessary integer. It is well-known that if those three numbers are same, boxes will create a "debugging field" and codes in the field will have no bugs.

For example, $ 1,1,3,3 $ is the example of $ 4 $ numbers meeting the condition because their mean, median and range are all equal to $ 2 $ .

Jeff has $ 4 $ special boxes of candies. However, something bad has happened! Some of the boxes could have been lost and now there are only $ n $ ( $ 0<=n<=4 $ ) boxes remaining. The $ i $ -th remaining box contains $ a_{i} $ candies.

Now Jeff wants to know: is there a possible way to find the number of candies of the $ 4-n $ missing boxes, meeting the condition above (the mean, median and range are equal)?

## 说明/提示

For the first sample, the numbers of candies in $ 4 $ boxes can be $ 1,1,3,3 $ . The arithmetic mean, the median and the range of them are all $ 2 $ .

For the second sample, it's impossible to find the missing number of candies.

In the third example no box has been lost and numbers satisfy the condition.

You may output $ b $ in any order.

## 样例 #1

### 输入

```
2
1
1
```

### 输出

```
YES
3
3
```

## 样例 #2

### 输入

```
3
1
1
1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
1
2
2
3
```

### 输出

```
YES
```

# AI分析结果

### 题目内容
# 糖果盒

## 题目描述
在赛博之地，有一个古老的传统，就是在家里放4盒糖果。如果这几盒糖果数量的算术平均数、中位数和极差都相等，那么这些数量就是特殊的。根据定义，对于集合\(\{x_{1},x_{2},x_{3},x_{4}\}\)（\(x_{1}\leq x_{2}\leq x_{3}\leq x_{4}\)），算术平均数是\(\frac{x_{1} + x_{2} + x_{3} + x_{4}}{4}\)，中位数是\(\frac{x_{2} + x_{3}}{2}\)，极差是\(x_{4} - x_{1}\)。算术平均数和中位数不一定是整数。众所周知，如果这三个数相同，这些盒子就会创造一个“调试场”，在场内的代码就不会有错误。

例如，\(1,1,3,3\)就是满足条件的4个数的例子，因为它们的平均数、中位数和极差都等于\(2\)。

杰夫有4个特殊的糖果盒。然而，糟糕的事情发生了！一些盒子可能丢失了，现在只剩下\(n\)（\(0\leq n\leq 4\)）个盒子。第\(i\)个剩下的盒子里有\(a_{i}\)颗糖果。

现在杰夫想知道：是否有可能找到丢失的\(4 - n\)个盒子里糖果的数量，使其满足上述条件（平均数、中位数和极差相等）？

## 说明/提示
对于第一个样例，4个盒子里糖果的数量可以是\(1,1,3,3\)。它们的算术平均数、中位数和极差都是\(2\)。

对于第二个样例，不可能找到缺失的糖果数量。

在第三个样例中，没有盒子丢失，并且数字满足条件。

你可以按任意顺序输出\(b\)。

## 样例 #1
### 输入
```
2
1
1
```
### 输出
```
YES
3
3
```
## 样例 #2
### 输入
```
3
1
1
1
```
### 输出
```
NO
```
## 样例 #3
### 输入
```
4
1
2
2
3
```
### 输出
```
YES
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先对等式\(\frac{a_1 + a_2 + a_3 + a_4}{4} = \frac{a_2 + a_3}{2} = a_4 - a_1\)进行变形推导，得出\(a_4 = 3a_1\)且\(a_2 + a_3 = 4a_1\)的关键关系，然后根据剩余盒子数量\(n\)进行分类讨论来判断是否能构造出满足条件的序列。不同之处在于具体构造方式和讨论的细致程度。有的题解通过推导直接给出满足条件的具体构造值，有的则采用暴力枚举的方式。在解决难点上，主要是如何根据给定的部分数据，利用推导出的关系，满足\(a_1\leq a_2\leq a_3\leq a_4\)这个顺序条件来构造或判断解的存在性。

### 所选的题解
- **作者：N_z_ (5星)**
  - **关键亮点**：思路清晰，对等式变形推导后，根据\(n\)的不同取值详细分类讨论，直接给出满足条件的构造值，代码简洁明了，可读性高。
  - **重点代码核心实现思想**：根据\(n\)的不同情况，利用推导出的关系直接计算并输出满足条件的糖果盒数量，若不满足条件则输出`NO`。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int a[5];
  int main()
  {
      int n;
      cin>>n;
      for(int x=1;x<=n;x++)
          cin>>a[x];
      sort(a+1,a+1+n);
      if(n==0){cout<<"YES\n1\n1\n3\n3"<<endl;return 0;}
      if(n==4){
          if((a[1]+a[2]+a[3]+a[4])==(a[2]+a[3])*2&&(a[2]+a[3])*2==(a[4]-a[1])*4)cout<<"YES"<<endl;
          else cout<<"NO"<<endl;
          return 0;
      }
      if(n==1){
          a[4]=3*a[1];
          a[2]=a[1];
          a[3]=3*a[1];
          cout<<"YES"<<endl<<a[2]<<endl<<a[3]<<endl<<a[4]<<endl;
          return 0;
      }
      if(n==2){
          if(3*a[1]>=a[2])cout<<"YES"<<endl<<4*a[1]-a[2]<<endl<<3*a[1]<<endl;
          else cout<<"NO"<<endl;
          return 0;
      }
      if(n==3){
          if(a[3]==3*a[1])cout<<"YES"<<endl<<4*a[1]-a[2]<<endl;
          else if(3*a[1]>=a[3]&&a[2]+a[3]==4*a[1])cout<<"YES"<<endl<<3*a[1]<<endl;
          else if(a[3]%3==0&&a[1]+a[2]==4*a[3]/3)cout<<"YES"<<endl<<a[3]/3<<endl;
          else cout<<"NO"<<endl;
          return 0;
      }
  }
  ```
- **作者：QQH08 (4星)**
  - **关键亮点**：先化简式子得出关键条件，对\(n\)进行分类讨论。\(n = 0\)和\(n = 1\)时构造解，\(n = 2\)和\(n = 3\)时采用暴力枚举的方式，思路较清晰。
  - **重点代码核心实现思想**：根据\(n\)的不同，对于\(n = 0\)和\(n = 1\)直接输出构造解；\(n = 2\)和\(n = 3\)时枚举可能的数，排序后检查是否满足条件，满足则输出解，不满足输出`NO`；\(n = 4\)时直接检查条件。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,a[10];
  bool check(){
      if(a[1]+a[4]==a[2]+a[3]&&3*a[1]==a[4])return 1;
      else return 0;
  }
  int main(){
      scanf("%d",&n);
      for(int i=1;i<=n;i++)
          scanf("%d",&a[i]);
      sort(a+1,a+n+1);
      if(n==0){
          puts("YES");
          printf("1\n1\n3\n3");
      }
      else if(n==1){
          puts("YES");
          printf("%d\n%d\n%d",a[1]+1,3*a[1]-1,3*a[1]);
          return 0;
      }
      else if(n==2){
          for(int i=1;i<=1500;i++){
              for(int j=1;j<=1500;j++){
                  int x=a[1],y=a[2];
                  a[3]=i,a[4]=j;
                  sort(a+1,a+5);
                  if(check()==1){
                      puts("YES");
                      printf("%d\n%d",min(i,j),max(i,j));
                      return 0;
                  }
                  a[1]=x,a[2]=y;
              }
          }
          puts("NO");
      }
      else if(n==3){
          for(int i=1;i<=1500;i++){
              int x=a[1],y=a[2],z=a[3];
              a[4]=i;
              sort(a+1,a+5);
              if(check()==1){
                  puts("YES");
                  printf("%d",i);
                  return 0;
              }
              a[1]=x,a[2]=y,a[3]=z;
          }
          puts("NO");
      }
      else{
          if(check()==0)puts("NO");
          else puts("YES");
      }
      return 0;
  }
  ```
- **作者：luuia (4星)**
  - **关键亮点**：详细推导等式得出关键条件，对\(n\)的每种情况都进行细致分析，构造解时充分考虑\(a_1\leq a_2\leq a_3\leq a_4\)的条件，思路清晰，代码实现与分析对应良好。
  - **重点代码核心实现思想**：根据\(n\)的不同取值，按分析的情况构造解或判断条件，满足则输出`YES`及对应解，不满足输出`NO`。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int main()
  {
      int n,a[5];
      cin >> n;
      for(int i = 1;i <= n;i++)
      {
          cin >> a[i];  
      }
      if(n == 0)
      {
          cout << "YES" << endl;
          cout << "2" << endl;
          cout << "3" << endl;
          cout << "5" << endl;
          cout << "6" << endl;  
      }
      else if(n == 1)
      {
          cout << "YES" << endl;
          cout << 2 * a[1] << endl;
          cout << 2 * a[1] << endl;
          cout << 3 * a[1] << endl;  
      }
      else if(n == 2)
      {
          sort(a + 1,a + 3);
          if(a[2] <= (3 * a[1]))
          {
              cout << "YES" << endl;
              cout << 4 * a[1] - a[2] << endl;
              cout << 3 * a[1] << endl;
          }
          else
          {
              cout << "NO" << endl;
          }
      }
      else if(n == 3)
      {
          sort(a + 1,a + 4);
          if(a[3] == (3 * a[1]))
          {
              cout << "YES" << endl;
              cout << 4 * a[1] - a[2] <<endl;
          }
          else if(((3 * a[1]) >= a[3]) && ((4 * a[1]) == (a[2] + a[3])))
          {
              cout << "YES" << endl;
              cout << 3 * a[1] << endl;
          }
          else if(((4 * a[3] / 3) == (a[1] + a[2])) && ((a[3] % 3) == 0))
          {
              cout << "YES" << endl;
              cout << a[3] / 3 << endl;
          }
          else
          {
              cout << "NO" << endl;
          }
      }
      else
      {
          sort(a + 1,a + 5);
          if(((a[4] == (3 * a[1]))) && ((a[2] + a[3]) == (4 * a[1])))
          {
              cout << "YES" << endl;
          }
          else
          {
              cout << "NO" << endl;
          }
      }
      return 0;
  }
  ```

### 最优关键思路或技巧
通过对给定等式进行数学推导得出\(a_4 = 3a_1\)和\(a_2 + a_3 = 4a_1\)这两个关键关系，为后续根据不同\(n\)值进行分类讨论和构造解提供了基础。在分类讨论时，充分利用这些关系以及\(a_1\leq a_2\leq a_3\leq a_4\)的条件来确定解的存在性及具体构造。

### 拓展
同类型题通常围绕数学等式关系，给定部分数据，要求判断能否构造出满足特定条件的完整数据集合。类似算法套路是先对给定条件进行数学推导得出关键关系，再根据已知数据的情况进行分类讨论，利用关键关系和限定条件来构造或判断解。

### 推荐题目
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析数据之间的关系来判断是否满足特定条件，与本题思路类似。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：根据等式关系，通过枚举和判断来构造满足条件的等式，与本题通过推导关系再分类讨论构造解有相似之处。
 - [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：根据给定的条件和关系，通过数学计算和逻辑判断来解决问题，锻炼数学分析和逻辑推理能力，与本题核心能力要求相符。

### 个人心得摘录与总结
无。 

---
处理用时：86.46秒