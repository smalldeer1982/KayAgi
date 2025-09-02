# 题目信息

# Stand-up Comedian

## 题目描述

Eve is a beginner stand-up comedian. Her first show gathered a grand total of two spectators: Alice and Bob.

Eve prepared $ a_1 + a_2 + a_3 + a_4 $ jokes to tell, grouped by their type:

- type 1: both Alice and Bob like them;
- type 2: Alice likes them, but Bob doesn't;
- type 3: Bob likes them, but Alice doesn't;
- type 4: neither Alice nor Bob likes them.

Initially, both spectators have their mood equal to $ 0 $ . When a spectator hears a joke he/she likes, his/her mood increases by $ 1 $ . When a spectator hears a joke he/she doesn't like, his/her mood decreases by $ 1 $ . If the mood of a spectator becomes negative (strictly below zero), he/she leaves.

When someone leaves, Eve gets sad and ends the show. If no one leaves, and Eve is out of jokes, she also ends the show.

Thus, Eve wants to arrange her jokes in such a way that the show lasts as long as possible. Help her to calculate the maximum number of jokes she can tell before the show ends.

## 说明/提示

In the first testcase, Eve only has jokes of the first type. Thus, there's no order to choose. She tells all her jokes, both Alice and Bob like them. Their mood becomes $ 5 $ . The show ends after Eve runs out of jokes.

In the second testcase, Eve only has jokes of the fourth type. Thus, once again no order to choose. She tells a joke, and neither Alice, nor Bob likes it. Their mood decrease by one, becoming $ -1 $ . They both have negative mood, thus, both leave, and the show ends.

In the third testcase, first, Eve tells both jokes of the first type. Both Alice and Bob has mood $ 2 $ . Then she can tell $ 2 $ jokes of the third type. Alice's mood becomes $ 0 $ . Bob's mood becomes $ 4 $ . Then $ 4 $ jokes of the second type. Alice's mood becomes $ 4 $ . Bob's mood becomes $ 0 $ . Then another $ 4 $ jokes of the third type. Alice's mood becomes $ 0 $ . Bob's mood becomes $ 4 $ . Then the remaining joke of the second type. Alice's mood becomes $ 1 $ . Bob's mood becomes $ 3 $ . Then one more joke of the third type, and a joke of the fourth type, for example. Alice's mood becomes $ -1 $ , she leaves, and the show ends.

In the fourth testcase, Eve should first tell the jokes both spectators like, then the jokes they don't. She can tell $ 4 $ jokes of the fourth type until the spectators leave.

## 样例 #1

### 输入

```
4
5 0 0 0
0 0 0 5
2 5 10 6
3 0 0 7```

### 输出

```
5
1
15
7```

# AI分析结果

### 题目内容
# 单口喜剧演员

## 题目描述
伊芙是一位初出茅庐的单口喜剧演员。她的第一场演出总共吸引了两位观众：爱丽丝和鲍勃。

伊芙准备了\(a_1 + a_2 + a_3 + a_4\)个笑话，这些笑话按类型分组：
- 类型1：爱丽丝和鲍勃都喜欢；
- 类型2：爱丽丝喜欢，但鲍勃不喜欢；
- 类型3：鲍勃喜欢，但爱丽丝不喜欢；
- 类型4：爱丽丝和鲍勃都不喜欢。

最初，两位观众的情绪值都为\(0\)。当一位观众听到他/她喜欢的笑话时，他/她的情绪值增加\(1\)。当一位观众听到他/她不喜欢的笑话时，他/她的情绪值减少\(1\)。如果一位观众的情绪值变为负数（严格小于\(0\)），他/她就会离开。

当有人离开时，伊芙会难过并结束演出。如果没有人离开，并且伊芙讲完了所有笑话，她也会结束演出。

因此，伊芙想以一种能让演出持续尽可能长时间的方式来安排她的笑话。帮助她计算在演出结束前她最多能讲多少个笑话。

## 说明/提示
在第一个测试用例中，伊芙只有第一种类型的笑话。因此，无需选择顺序。她讲完所有笑话，爱丽丝和鲍勃都喜欢这些笑话。他们的情绪值变为\(5\)。伊芙讲完所有笑话后演出结束。

在第二个测试用例中，伊芙只有第四种类型的笑话。因此，同样无需选择顺序。她讲一个笑话，爱丽丝和鲍勃都不喜欢。他们的情绪值都减少\(1\)，变为\(-1\)。他们两人的情绪值都为负数，因此，两人都离开，演出结束。

在第三个测试用例中，首先，伊芙讲两个第一种类型的笑话。爱丽丝和鲍勃的情绪值都变为\(2\)。然后她可以讲\(2\)个第三种类型的笑话。爱丽丝的情绪值变为\(0\)。鲍勃的情绪值变为\(4\)。然后讲\(4\)个第二种类型的笑话。爱丽丝的情绪值变为\(4\)。鲍勃的情绪值变为\(0\)。然后再讲\(4\)个第三种类型的笑话。爱丽丝的情绪值变为\(0\)。鲍勃的情绪值变为\(4\)。然后讲剩下的一个第二种类型的笑话。爱丽丝的情绪值变为\(1\)。鲍勃的情绪值变为\(3\)。然后再讲一个第三种类型的笑话，例如，再讲一个第四种类型的笑话。爱丽丝的情绪值变为\(-1\)，她离开，演出结束。

在第四个测试用例中，伊芙应该先讲两位观众都喜欢的笑话，然后讲他们都不喜欢的笑话。她可以讲\(4\)个第四种类型的笑话，直到观众离开。

## 样例 #1
### 输入
```
4
5 0 0 0
0 0 0 5
2 5 10 6
3 0 0 7
```
### 输出
```
5
1
15
7
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路本质一致，均利用贪心策略。核心思路为优先讲类型1笑话，因其使两人心情都变好无负面效果；接着将类型2和类型3笑话配对讲，因其效果可相互抵消；最后考虑类型4笑话以及剩余的类型2或3笑话。解题难点在于处理不同类型笑话数量关系以及确定结束条件，即如何在保证无人离场前提下讲最多笑话。各题解都考虑了特殊情况\(a_1 = 0\)时输出\(1\)。

### 所选的题解
- **作者：Wind_Smiled（5星）**
  - **关键亮点**：思路清晰，对每一步操作分析细致，代码简洁明了。先判断\(a_1\)是否为\(0\)，然后计算操作一数量，再合并操作二和三，最后计算剩余操作，逻辑连贯。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t;
  int a1,a2,a3,a4,ans;
  int main(){
      scanf("%d",&t);
      while(t--){
          scanf("%d%d%d%d",&a1,&a2,&a3,&a4);
          if(a1==0){//不可操作 
              printf("1\n");
              continue;
          }
          ans=a1;
          ans+=min(a2,a3)*2;//2,3的相反操作 
          ans+=min(a1+1,abs(a2-a3)+a4);//在相反操作中已经进行了 min(a2,a3) 次操作，故要取大减小的差值再与 a4 的可操作数相加。 
          printf("%d\n",ans);
      }
      return 0;
  }
  ```
- **作者：Convergent_Series（4星）**
  - **关键亮点**：表述简洁，同样先特判\(a_1 = 0\)，接着清晰阐述了每种类型笑话的使用策略，代码实现简洁易懂。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int a[5],sum,t;
  int main(){
      cin>>t;
      while(t--){
          cin>>a[1]>>a[2]>>a[3]>>a[4];    
          if(a[1]==0){
              cout<<1<<"\n";
              continue;
          }
          sum=a[1];
          int x=min(a[2],a[3]);
          sum+=2*x;
          sum+=min(a[1]+1,a[4]+a[2]+a[3]-2*x);
          cout<<sum<<"\n";
      }
      return 0;
  }
  ```
- **作者：happy_zero（4星）**
  - **关键亮点**：详细分析了每一步思路，对类型2和3笑话打包处理讲解细致，对结束条件分析准确，代码易读性高。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int main(){
      int T;
      cin>>T;
      while(T--){
          int ans;
          int a,b,c,d;//这里用a,b,c,d代替a[1],a[2],a[3],a[4]
          cin>>a>>b>>c>>d;
          if(a==0){cout<<1<<endl;continue;}
          if(b>c)swap(b,c);
          ans=a+2*b+min(a+1,c-b+d); 
          cout<<ans<<endl;
      }
      return 0;
  }
  ```

### 最优关键思路或技巧
贪心策略，优先选择对两人心情提升有益的笑话类型（类型1），再利用类型2和3笑话相互抵消的特性，最后考虑会使两人心情下降的笑话（类型4及剩余类型2或3）。在代码实现上，通过比较不同类型笑话数量，并结合结束条件（有人心情为负）进行计算。

### 同类型题或类似算法套路拓展
此类题目属于贪心策略应用，通常涉及资源分配或操作顺序选择，使某个指标达到最优。解题关键在于找到合理贪心策略，即确定何种操作或选择在当前情况下是最优的，并证明其正确性。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
无。 

---
处理用时：69.27秒