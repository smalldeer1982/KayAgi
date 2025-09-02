# 题目信息

# Unfair Game

## 题目描述

Alice and Bob gathered in the evening to play an exciting game on a sequence of $ n $ integers, each integer of the sequence doesn't exceed $ 4 $ . The rules of the game are too complex to describe, so let's just describe the winning condition — Alice wins if the [bitwise XOR](http://tiny.cc/xor_wiki_eng) of all the numbers in the sequence is non-zero; otherwise, Bob wins.

The guys invited Eve to act as a judge. Initially, Alice and Bob play with $ n $ numbers. After one game, Eve removes one of the numbers from the sequence, then Alice and Bob play with $ n-1 $ numbers. Eve removes one number again, after which Alice and Bob play with $ n - 2 $ numbers. This continues until the sequence of numbers is empty.

Eve seems to think that in such a game, Alice almost always wins, so she wants Bob to win as many times as possible. Determine the maximum number of times Bob can win against Alice if Eve removes the numbers optimally.

## 说明/提示

In the first example, Bob wins when Eve has not removed any numbers yet.

In the second example, Bob wins if Eve removes one one and one three.

## 样例 #1

### 输入

```
5
1 1 1 0
1 0 1 2
2 2 2 0
3 3 2 0
0 9 9 9```

### 输出

```
1
1
3
3
12```

# AI分析结果

### 题目内容重写

#### 不公平的游戏

**题目描述**

Alice 和 Bob 在晚上聚在一起玩一个有趣的游戏，游戏基于一个包含 $n$ 个整数的序列，每个整数不超过 $4$。游戏的规则太复杂，无法详细描述，所以我们只描述胜利条件——如果序列中所有数字的[按位异或](http://tiny.cc/xor_wiki_eng)结果不为零，Alice 获胜；否则，Bob 获胜。

他们邀请了 Eve 作为裁判。最初，Alice 和 Bob 使用 $n$ 个数字进行游戏。每场比赛结束后，Eve 从序列中移除一个数字，然后 Alice 和 Bob 使用剩下的 $n-1$ 个数字继续游戏。Eve 再次移除一个数字，Alice 和 Bob 使用剩下的 $n-2$ 个数字继续游戏。这个过程一直持续，直到序列为空。

Eve 认为在这种游戏中，Alice 几乎总是获胜，所以她希望 Bob 尽可能多地获胜。请确定如果 Eve 以最优方式移除数字，Bob 最多可以获胜多少次。

**说明/提示**

在第一个示例中，Bob 在 Eve 还没有移除任何数字时获胜。

在第二个示例中，如果 Eve 移除一个 $1$ 和一个 $3$，Bob 获胜。

**样例 #1**

**输入**

```
5
1 1 1 0
1 0 1 2
2 2 2 0
3 3 2 0
0 9 9 9
```

**输出**

```
1
1
3
3
12
```

---

### 题解综合分析与结论

本题的核心在于通过按位异或的性质，找到让 Bob 获胜的最大次数。题解中主要思路是通过分类讨论，利用数字的奇偶性和异或性质，计算出 Bob 获胜的次数。

#### 最优关键思路与技巧

1. **按位异或性质**：利用 $a \oplus a = 0$ 和 $a \oplus 0 = a$ 的性质，判断序列中数字的异或结果是否为零。
2. **奇偶性分析**：通过分析数字的奇偶性，确定如何移除数字才能使 Bob 获胜次数最大化。
3. **分类讨论**：根据数字的奇偶性，分类讨论如何移除数字，使得 Bob 获胜次数最大化。

#### 推荐题解

1. **作者：菲斯斯夫斯基 (赞：10)**
   - **星级：5星**
   - **关键亮点**：通过详细的分类讨论，清晰地解释了如何利用数字的奇偶性和异或性质，计算出 Bob 获胜的最大次数。代码简洁明了，逻辑清晰。
   - **代码核心思想**：通过计算每个数字的奇偶性，判断 Bob 获胜的次数。
   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   int t;
   int a,b,c,d;
   int main()
   {
       cin>>t;
       while(t--)
       {
           scanf("%d%d%d%d",&a,&b,&c,&d);
           printf("%d\n",a/2+b/2+c/2+d/2+(a%2&&b%2&&c%2));
       }
       return 0;
   }
   ```

2. **作者：yangduan_ (赞：3)**
   - **星级：4星**
   - **关键亮点**：简洁明了地解释了如何利用异或性质，判断 Bob 获胜的次数。代码简洁，逻辑清晰。
   - **代码核心思想**：通过计算每个数字的奇偶性，判断 Bob 获胜的次数。
   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   int t,a,b,c,d,ans;
   int main(){
       int i,j;
       cin>>t;
       while(t--){
           cin>>a>>b>>c>>d;
           ans=a/2+b/2+c/2+d/2;
           if((a%2==1)&&(b%2==1)&&(c%2==1)) ans++;
           cout<<ans<<endl;
       }
       return 0;
   }
   ```

3. **作者：yshpdyt (赞：3)**
   - **星级：4星**
   - **关键亮点**：通过详细的分类讨论，解释了如何利用数字的奇偶性和异或性质，计算出 Bob 获胜的最大次数。代码简洁，逻辑清晰。
   - **代码核心思想**：通过计算每个数字的奇偶性，判断 Bob 获胜的次数。
   ```cpp
   #include<bits/stdc++.h>
   #define ll long long
   #define N 800005
   #define endl "\n" 
   #define fi fisrt
   #define se second
   using namespace std;
   const ll mod=1e9+7;
   const ll inf=1e18;
   const double eps=1e-6;
   ll a[7];
   void sol(){
       cin>>a[1]>>a[2]>>a[3]>>a[4];
       ll res=a[4]/2;
       res+=a[1]/2+a[2]/2+a[3]/2;
       if((a[1]&1)&&(a[2]&1)&&(a[3]&1))res++;
       cout<<res<<endl;
   }
   int main(){
       ios::sync_with_stdio(false);
       cin.tie(0);
       //freopen(".in","r",stdin);
       //freopen(".out","w",stdout); 
       ll ttt;
       cin>>ttt;
       while(ttt--)sol();
       return 0;
   }
   ```

#### 可拓展之处

1. **类似题目**：可以扩展到其他涉及按位异或的题目，如判断序列中是否存在子序列的异或结果为零。
2. **算法套路**：类似的分类讨论和奇偶性分析可以应用于其他涉及数字性质和组合的题目。

#### 推荐题目

1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)
2. [P1734 最大约数和](https://www.luogu.com.cn/problem/P1734)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：48.17秒