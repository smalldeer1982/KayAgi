# 题目信息

# Zookeeper and The Infinite Zoo

## 题目描述

有一个无限图，其中有无数个节点，从 $1$ 开始标号。有一条从 $u$ 到 $u+v$ 的单向边，当且仅当 $u \&  v = v$ (这里的 $\&$ 指 [按位与](https://zh.wikipedia.org/wiki/位操作#按位与（AND）) 。除此以外没有其它边。

有 $q$ 个询问，询问是否存在一条从 $u$ 到 $v$ 的路径。

## 样例 #1

### 输入

```
5
1 4
3 6
1 6
6 2
5 5```

### 输出

```
YES
YES
NO
NO
YES```

# AI分析结果

【题目内容】
# 动物园管理员与无限动物园

## 题目描述

有一个无限图，其中有无数个节点，从 $1$ 开始标号。有一条从 $u$ 到 $u+v$ 的单向边，当且仅当 $u \&  v = v$ (这里的 $\&$ 指 [按位与](https://zh.wikipedia.org/wiki/位操作#按位与（AND）) 。除此以外没有其它边。

有 $q$ 个询问，询问是否存在一条从 $u$ 到 $v$ 的路径。

## 样例 #1

### 输入

```
5
1 4
3 6
1 6
6 2
5 5
```

### 输出

```
YES
YES
NO
NO
YES
```

【算法分类】
位运算

【综合分析与结论】
这些题解的核心思路都是先判断 $u$ 是否小于等于 $v$，若 $u > v$ 则直接判定无法到达。然后将数字转换为二进制形式，通过比较 $u$ 和 $v$ 二进制下从低位到高位的 $1$ 的数量来判断是否存在路径。具体来说，设 $u$ 和 $v$ 二进制下前 $i$ 位中 $1$ 的数量分别为 $f(u, i)$ 和 $f(v, i)$，若对于所有的 $i$ 都有 $f(u, i) \geq f(v, i)$，则存在从 $u$ 到 $v$ 的路径，否则不存在。

各题解的区别主要在于代码实现的细节和表述方式，但整体思路一致。难点在于发现二进制下 $1$ 的数量的比较规律，以及理解为什么可以通过这种方式来判断路径是否存在。

【所选题解】
- XL4453（4星）：思路清晰，代码简洁，直接通过循环比较二进制下每一位的 $1$ 的数量。
- Cry_For_theMoon（4星）：详细阐述了规律的推导过程，包括特殊情况的处理，代码规范。
- Eibon（4星）：简洁明了地指出了二进制下 $1$ 的移动规律，代码实现简洁。

【重点代码】
#### XL4453 的代码
```cpp
#include<cstdio>
using namespace std;
int n,x,y,cntx,cnty,flag;
int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%d%d",&x,&y);
        if(x<=y){
            flag=1;cntx=cnty=0;
            for(int i=0;i<=31;i++){
                if(x&(1<<i))cntx++;
                if(y&(1<<i))cnty++;
                if(cntx<cnty){
                    printf("NO\n");
                    flag=0;
                    break;
                }
            }
            if(flag)printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
```
核心实现思想：先判断 $x$ 是否小于等于 $y$，若满足条件则通过循环逐位统计 $x$ 和 $y$ 二进制下 $1$ 的数量，一旦发现 $x$ 的 $1$ 的数量小于 $y$ 的 $1$ 的数量，则判定无法到达。

#### Cry_For_theMoon 的代码
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define next Cry_For_theMoon
#define il inline
typedef long long ll;
using namespace std;
int q,u,v,sum1[40],sum2[40];
int main(){
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&u,&v);
        memset(sum1,0,sizeof sum1);
        memset(sum2,0,sizeof sum2);
        if(u>v){
            printf("NO\n");continue;
        }
        rep(j,1,30){
            sum1[j]=sum1[j-1];sum2[j]=sum2[j-1];
            if(u&1)sum1[j]++;
            if(v&1)sum2[j]++;
            u/=2;v/=2;
        }
        rep(j,1,30){
            if(sum1[j]<sum2[j])goto END;
        }
        printf("YES\n");continue;
        END:printf("NO\n");
    }
    return 0;
}
```
核心实现思想：先判断 $u$ 是否大于 $v$，若不大于则通过循环计算 $u$ 和 $v$ 二进制下前 $j$ 位中 $1$ 的数量，存储在数组中，最后比较数组元素判断是否存在路径。

#### Eibon 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+5;
const int mod=1e9+7;
int T,u,v,VIP,a,b;
signed main()
{
    scanf("%lld",&T);
    while(T--){
        VIP=a=b=0;
        scanf("%lld%lld",&u,&v);
        if(u>v){
            printf("NO\n");
            continue;
        }
        for(int i=0;i<=30;i++){
            if(u&(1<<i)){
                a++;
            }
            if(v&(1<<i)){
                b++;
            }
            if(a<b){
                VIP=1;
                printf("NO\n");
                break;
            }
        }
        if(!VIP){
            printf("YES\n");
        }
    }
    return 0;
}
```
核心实现思想：先判断 $u$ 是否大于 $v$，若不大于则通过循环逐位统计 $u$ 和 $v$ 二进制下 $1$ 的数量，一旦发现 $u$ 的 $1$ 的数量小于 $v$ 的 $1$ 的数量，则判定无法到达。

【关键思路或技巧】
- 利用位运算将数字转换为二进制形式，通过比较二进制下 $1$ 的数量来判断路径是否存在。
- 先特判 $u > v$ 的情况，减少不必要的计算。

【拓展思路】
同类型题目可能会改变图的边的连接规则，或者增加更多的限制条件，但核心思路可能仍然是通过位运算来处理二进制信息。类似的算法套路可以应用于其他需要处理二进制信息的题目，例如判断两个数字之间是否可以通过特定的位运算转换得到。

【推荐题目】
- P1100 高低位交换
- P1880 石子合并
- P2114 [NOI2014] 起床困难综合症

【个人心得】
- Cry_For_theMoon：感觉思维难度应该是普及+/提高吧，我都不知道我当时怎么乱蒙出规律的。总结：在解题过程中，有时候可以通过尝试和观察来发现规律。
- pigstd：虽然只是 Global Round 的 D 题，但是我好菜。总结：即使是难度不是特别高的题目，也可能会因为自身的知识和能力不足而觉得困难，需要不断学习和练习。
- FutaRimeWoawaSete：太SB了一点，虽然照样吃巨多罚时。总结：在解题过程中可能会因为粗心或对题目的理解不够深入而出现错误，导致罚时增加，需要更加细心和认真。 

---
处理用时：53.90秒