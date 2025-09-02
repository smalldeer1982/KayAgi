# 题目信息

# 『MdOI R4』Color

## 题目描述

小 M 同学有一张 $2$ 行 $n$ 列的方格纸，一开始所有格子都是白色的。

她决定对一些格子染色，具体地，每次她会选择两个**相邻的（四联通的，也就是有公共边的）白色**格子，其中一个染成红色，另一个染成蓝色。

她的目标是通过**任意次操作**让指定的一些格子变成红色，**对其他格子没有要求**。请你帮她判断一下，能否通过上述操作达成目标呢？

## 说明/提示

【样例解释】

![temp.png](https://i.loli.net/2020/09/27/oCRpYnPAlFk7GuS.png)

上图中左侧为第一组测试数据的一种方案，右侧为第三组测试数据的一种方案，对于第二组测试数据，并没有满足要求的方案。

【数据规模与约定】 

**本题采用捆绑测试**

|子任务编号|$n\le$|特殊性质|$T\le$|分值|
|:-|:-|:-|:-|:-|
|$1$|$3$|无特殊限制|$10$|$10$|
|$2$|$10$|无特殊限制|$10$|$20$|
|$3$|无特殊限制|所有 $1$ 都在同一行|$10$|$1$|
|$4$|无特殊限制|$1$ 不超过 $4$ 个|$10$|$13$|
|$5$|$10^3$|无特殊限制|$10$|$25$|
|$6$|无特殊限制|无特殊限制|$10$|$30$|
|$7$|$16$|无特殊限制|$65536$|$1$|

对于所有数据，满足 $1\le n\le 10^5$，$\sum n\le 2^{20}$。

## 样例 #1

### 输入

```
3
5
01110
10010
5
11000
01100
5
00101
10100
```

### 输出

```
RP
++
RP```

# AI分析结果

• **综合分析与结论**：该题主要探讨如何判断在给定规则下，能否将特定格子染成红色。多数题解采用贪心策略，从左到右按列处理，优先选择对后续影响小的染色方式，即优先向左染色，其次同一列，最后向右染色。部分题解使用二分图最大匹配或DP方法。贪心策略时间复杂度为O(Tn)，实现相对简洁；二分图最大匹配时间复杂度为O(Tn√n)，可拓展到更复杂矩阵；DP方法实现较复杂且常数大。
• **所选的题解**：
  - **作者yummy的题解 - 5星**：
    - **关键亮点**：对每个子任务分别分析，思路清晰，逐步引导读者理解。详细阐述贪心策略，从左往右一列一列满足，优先选择左边未占用的0，其次同一列，最后右边，时间复杂度低且常数小。还讨论了行数h≥3时的状压DP和二分图最大匹配做法。
    - **个人心得**：分享了出题和验题的有趣经历，以及对题目背景相关音乐的介绍。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char up[100005],down[100005];
bool cup(int x){//尝试给上面这行第x个位置染色
    if(up[x]!='0')return 1;
    up[x]='2';return 0;}
bool cdown(int x){//尝试给下面这行第x个位置染色
    if(down[x]!='0')return 1;
    down[x]='2';return 0;}
int main(){
    for(scanf("%d",&t);t;t--){
        scanf("%d%s%s",&n,up,down);
        bool flag=1;
        if(up[0]=='1'&&cdown(0)&&cup(1)||down[0]=='1'&&cup(0)&&cdown(1))//对于第0列因为没有上一列我们需要特判
            flag=0;
        for(int i=1;i<n;i++)
            if(up[i]=='1'&&cup(i-1)&&cdown(i)&&cup(i+1)||down[i]=='1'&&cdown(i-1)&&cup(i)&&cdown(i+1)){
            //利用&&的短路特性，即&&前面的语句为false就会不执行后面的语句，而且&&是右结合的
                flag=0;break;
            }
        if(flag)puts("RP");
        else puts("++");
    }
    return 0;
}
```
  - **作者囧仙的题解 - 5星**：
    - **关键亮点**：简洁清晰地阐述结论，从左到右依次考虑红色格子的左侧、下侧（上侧）、右侧能否涂色，并用图示证明选择下方（上方）不劣的原因，逻辑严谨。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN =1e6+3;
char S[MAXN],T[MAXN]; int n;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    dn(qread(),1,TT){
        n=qread(); scanf("%s%s",S+1,T+1);
        S[n+1]=T[n+1]='!';
        up(1,n,i){
            if(S[i]=='1'){ if(S[i-1]=='0') S[i-1]='!';
            else if(T[i]=='0') T[i]='!'; else if(S[i+1]=='0') S[i+1]='!'; else goto no;}
            if(T[i]=='1'){ if(T[i-1]=='0') T[i-1]='!';
            else if(S[i]=='0') S[i]='!'; else if(T[i+1]=='0') T[i+1]='!'; else goto no;}
        }
        puts("RP"); goto yes; no: puts("++"); yes:;
    }
    return 0;
}
```
  - **作者Caesium的题解 - 4星**：
    - **关键亮点**：清晰阐述贪心思路，按左、下（上）、右顺序为红色格子匹配白色格子，代码实现简洁明了。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n;
char ch;
string a;//a是读入上面那一排
string b;//b是下面那一排
bool flag;

bool judge(int k)//判断一列格子能否放置
{
    if (a[k] == '1')//如果上面有格子（如果上下都有格子，先做那个都一样，留给读者证明
    {
        if (a[k-1] == '0') a[k-1] = '2';//优先左边
        else if (b[k] == '0') b[k] = '2';//再下面
        else if (a[k+1] == '0') a[k+1] = '2';//右边
        else return false;
    }
    if (b[k] == '1')
    {
        if (b[k-1] == '0') b[k-1] = '2';
        else if (a[k] == '0') a[k] = '2';
        else if (b[k+1] == '0') b[k+1] = '2';
        else return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);//加速，因为有字符串而我太蒟了不会写快读
    cin >> t;
    while(t--)
    {
        cin >> n;
        flag = true;
        cin >> a >> b;
        a = '2' + a + '2';//首位加个2，告诉编译器这里不能放
        b = '2' + b + '2';
        for (int i = 1; i <= n; i++)
        {
            if (!judge(i))//返回false，不能放置
            {
                cout << "++" << endl; 
                flag = false;//
                break;
            }
        }
        if (flag)
        {
            cout << "RP" << endl;
        }
    }
    return 0;
 } 
```
• **最优关键思路或技巧**：贪心策略是最优思路，从左到右按列处理，优先选择对后续影响小的染色位置，能高效解决问题且实现简单。
• **同类型题或类似算法套路**：此类题目属于染色匹配类问题，类似套路是按一定顺序遍历，优先选择对后续状态影响小的决策，如区间调度问题，按结束时间排序后贪心选择。
• **推荐洛谷题目**：
  - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
  - [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
  - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
• **个人心得摘录与总结**：
  - **yummy**：分享出题和验题经历，增加趣味性。
  - **daiarineko**：强调多测不清空、边界判断、条件判断以及输入处理等细节对代码正确性和效率的重要性。 

---
处理用时：56.35秒