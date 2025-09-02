# 题目信息

# Alice and the List of Presents

## 题目描述

Alice got many presents these days. So she decided to pack them into boxes and send them to her friends.

There are $ n $ kinds of presents. Presents of one kind are identical (i.e. there is no way to distinguish two gifts of the same kind). Presents of different kinds are different (i.e. that is, two gifts of different kinds are distinguishable). The number of presents of each kind, that Alice has is very big, so we can consider Alice has an infinite number of gifts of each kind.

Also, there are $ m $ boxes. All of them are for different people, so they are pairwise distinct (consider that the names of $ m $ friends are written on the boxes). For example, putting the first kind of present into the first box but not into the second box, is different from putting the first kind of present into the second box but not into the first box.

Alice wants to pack presents with the following rules:

- She won't pack more than one present of each kind into the same box, so each box should contain presents of different kinds (i.e. each box contains a subset of $ n $ kinds, empty boxes are allowed);
- For each kind at least one present should be packed into some box.

Now Alice wants to know how many different ways to pack the presents exists. Please, help her and calculate this number. Since the answer can be huge, output it by modulo $ 10^9+7 $ .

See examples and their notes for clarification.

## 说明/提示

In the first example, there are seven ways to pack presents:

 $ \{1\}\{\}\{\} $

 $ \{\}\{1\}\{\} $

 $ \{\}\{\}\{1\} $

 $ \{1\}\{1\}\{\} $

 $ \{\}\{1\}\{1\} $

 $ \{1\}\{\}\{1\} $

 $ \{1\}\{1\}\{1\} $

In the second example there are nine ways to pack presents:

 $ \{\}\{1,2\} $

 $ \{1\}\{2\} $

 $ \{1\}\{1,2\} $

 $ \{2\}\{1\} $

 $ \{2\}\{1,2\} $

 $ \{1,2\}\{\} $

 $ \{1,2\}\{1\} $

 $ \{1,2\}\{2\} $

 $ \{1,2\}\{1,2\} $

For example, the way $ \{2\}\{2\} $ is wrong, because presents of the first kind should be used in the least one box.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
7```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
9```

# AI分析结果

【题目内容】
# Alice和礼物清单

## 题目描述

Alice最近收到了很多礼物。她决定将这些礼物打包进盒子，并寄给她的朋友们。

有$n$种不同的礼物。同一种类的礼物是相同的（即无法区分同一种类的两个礼物）。不同种类的礼物是不同的（即不同种类的礼物是可以区分的）。Alice拥有的每种礼物的数量非常多，因此我们可以认为Alice拥有无限数量的每种礼物。

此外，还有$m$个盒子。这些盒子是给不同的人的，因此它们是两两不同的（可以认为每个盒子上都写有$m$个朋友的名字）。例如，将第一种礼物放入第一个盒子但不放入第二个盒子，与将第一种礼物放入第二个盒子但不放入第一个盒子是不同的。

Alice希望按照以下规则打包礼物：

- 她不会将同一种礼物放入同一个盒子超过一次，因此每个盒子应包含不同种类的礼物（即每个盒子包含$n$种礼物的一个子集，允许盒子为空）；
- 对于每种礼物，至少有一个礼物应被打包到某个盒子中。

现在Alice想知道有多少种不同的打包礼物的方式。请帮助她计算这个数字。由于答案可能非常大，请输出对$10^9+7$取模的结果。

【算法分类】
组合数学

【题解分析与结论】
所有题解的核心思路一致，即对于每种礼物，其在$m$个盒子中的分布方式为$2^m - 1$（因为至少需要一个盒子包含该礼物），而总共有$n$种礼物，因此总方案数为$(2^m - 1)^n$。题解的主要区别在于代码实现和优化细节。

【评分较高的题解】

1. **作者：jiangXxin (5星)**
   - **关键亮点**：代码简洁，快速幂实现清晰，直接套用公式，代码可读性高。
   - **核心代码**：
     ```cpp
     long long quickpow(long long a,long long b){
         long long ret=1;
         while(b){
             if(b&1){
                 ret=ret*a%mod;
             }
             a=a*a%mod;
             b>>=1;
         }
         return ret;
     }
     int main(){
         cin>>n>>m;
         ans=quickpow(2,m);
         ans--;
         ans=quickpow(ans,n);
         cout<<ans<<endl;
         return 0;
     }
     ```

2. **作者：reyik (4星)**
   - **关键亮点**：快速幂实现清晰，代码简洁，直接套用公式，代码可读性高。
   - **核心代码**：
     ```cpp
     long long quick_pow(long long x,long long l) {
         x%=mod;
         long long res=1;
         while(l) {
             if(l&1) res=res*x%mod;
             x=x*x%mod;
             l>>=1;
         }
         return res;
     }
     int main() {
         scanf("%d%d",&n,&m);
         printf("%lld\n",quick_pow(quick_pow(2,m)-1+mod,n));
         return 0;
     }
     ```

3. **作者：fkcufk (4星)**
   - **关键亮点**：代码简洁，快速幂实现清晰，直接套用公式，代码可读性高。
   - **核心代码**：
     ```cpp
     ll kasumi(ll a,ll b){
         ll ret=1;
         while(b){
             if(b%2) ret=(ret*a)%mod;
             a=(a*a)%mod;
             b>>=1;
         }
         return ret;
     }
     int main(){
         cin >> n >> m;
         ans=kasumi(kasumi(2,m)-1+mod,n);
         cout << ans;
         return 0;
     }
     ```

【最优关键思路或技巧】
- **快速幂**：由于$n$和$m$的范围较大，直接计算幂次会导致TLE，因此使用快速幂算法来高效计算$(2^m - 1)^n$。
- **组合数学**：通过组合数学的思路，将问题转化为每种礼物在盒子中的分布方式，最终使用乘法原理计算总方案数。

【可拓展之处】
- 类似的问题可以扩展到其他组合数学问题，如排列组合、容斥原理等。
- 可以进一步考虑盒子容量有限制的情况，或者礼物数量有限的情况。

【推荐题目】
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)
3. [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)

---
处理用时：39.04秒