# 题目信息

# Berry Jam

## 题目描述

Karlsson has recently discovered a huge stock of berry jam jars in the basement of the house. More specifically, there were $ 2n $ jars of strawberry and blueberry jam.

All the $ 2n $ jars are arranged in a row. The stairs to the basement are exactly in the middle of that row. So when Karlsson enters the basement, he sees exactly $ n $ jars to his left and $ n $ jars to his right.

For example, the basement might look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278C/241a083326516b3b4ad70c41dd4440502bf9af7a.png)Being the starightforward man he is, he immediately starts eating the jam. In one minute he chooses to empty either the first non-empty jar to his left or the first non-empty jar to his right.

Finally, Karlsson decided that at the end the amount of full strawberry and blueberry jam jars should become the same.

For example, this might be the result:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278C/ce4aac0a2c1a17ee1f9a579db06c727cd2163ca6.png)He has eaten $ 1 $ jar to his left and then $ 5 $ jars to his right. There remained exactly $ 3 $ full jars of both strawberry and blueberry jam.Jars are numbered from $ 1 $ to $ 2n $ from left to right, so Karlsson initially stands between jars $ n $ and $ n+1 $ .

What is the minimum number of jars Karlsson is required to empty so that an equal number of full strawberry and blueberry jam jars is left?

Your program should answer $ t $ independent test cases.

## 说明/提示

The picture from the statement describes the first test case.

In the second test case the number of strawberry and blueberry jam jars is already equal.

In the third test case Karlsson is required to eat all $ 6 $ jars so that there remain $ 0 $ jars of both jams.

In the fourth test case Karlsson can empty either the second and the third jars or the third and the fourth one. The both scenarios will leave $ 1 $ jar of both jams.

## 样例 #1

### 输入

```
4
6
1 1 1 2 2 1 2 1 2 1 1 2
2
1 2 1 2
3
1 1 1 1 1 1
2
2 1 1 1
```

### 输出

```
6
0
6
2
```

# AI分析结果

### 题目内容翻译
## 浆果果酱

### 题目描述
卡尔松最近在房子的地下室里发现了大量的果酱罐。具体来说，有 $2n$ 罐草莓果酱和蓝莓果酱。

所有的 $2n$ 罐果酱排成一排。通往地下室的楼梯正好在这一排的中间。所以当卡尔松进入地下室时，他正好看到左边有 $n$ 罐，右边有 $n$ 罐。

例如，地下室可能看起来像这样：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278C/241a083326516b3b4ad70c41dd4440502bf9af7a.png)

作为一个直爽的人，他立刻开始吃果酱。每分钟，他会选择清空左边第一个非空的罐子或者右边第一个非空的罐子。

最后，卡尔松决定，最后剩下的草莓果酱罐和蓝莓果酱罐的数量应该相同。

例如，结果可能是这样的：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278C/ce4aac0a2c1a17ee1f9a579db06c727cd2163ca6.png)

他先吃了左边的 1 罐，然后吃了右边的 5 罐。最后正好剩下 3 罐草莓果酱和 3 罐蓝莓果酱。

罐子从左到右编号为 1 到 $2n$，所以卡尔松最初站在罐子 $n$ 和 $n + 1$ 之间。

卡尔松至少需要清空多少个罐子，才能使剩下的草莓果酱罐和蓝莓果酱罐的数量相等？

你的程序应该回答 $t$ 个独立的测试用例。

### 说明/提示
题目描述中的图片描述的是第一个测试用例。

在第二个测试用例中，草莓果酱罐和蓝莓果酱罐的数量已经相等。

在第三个测试用例中，卡尔松需要吃掉所有的 6 个罐子，这样两种果酱就都剩下 0 罐。

在第四个测试用例中，卡尔松可以清空第二个和第三个罐子，或者第三个和第四个罐子。这两种情况都会剩下 1 罐两种果酱。

### 样例 #1
#### 输入
```
4
6
1 1 1 2 2 1 2 1 2 1 1 2
2
1 2 1 2
3
1 1 1 1 1 1
2
2 1 1 1
```
#### 输出
```
6
0
6
2
```

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心思路都是将两种果酱分别映射为 $1$ 和 $-1$，通过计算前缀和与后缀和，利用差值相等来找到满足条件的区间，从而确定最少需要清空的罐子数。不同题解在实现细节上有所差异，如使用 `map` 记录信息、数组记录差值等。

### 所选题解
- **Wf_yjqd（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `map` 记录后缀和，枚举前缀和来维护答案，复杂度为 $O(n\log{n})$。
    - **个人心得**：和同学 duel 调了半小时，提醒注意特殊处理前缀和或后缀和为 0 的情况。
- **Dolphin_（4星）**
    - **关键亮点**：先处理前半段，用数组记录 1 和 2 两种物品差为某值时左边用的最多个数，再循环后半段更新答案，思路巧妙。
    - **个人心得**：无。
- **YGB_XU（4星）**
    - **关键亮点**：分别预处理左右两列的差值信息，枚举左边差值计算右边对应差值，用两侧差值对应取走最小果酱数更新答案，逻辑清晰。
    - **个人心得**：VP 时做的题，感觉比 B 题还容易些。

### 重点代码
#### Wf_yjqd
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,a[maxn],ans;
map<int,int> mp;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        mp.clear();
        for(int i=1;i<=n*2;i++){
            scanf("%d",&a[i]);
            a[i]=(a[i]==1?-1:1);
        }
        ans=n*2;
        for(int i=1;i<=n;i++){
            a[i]+=a[i-1];
            if(!a[i])
                ans=min(ans,n*2-i);
        }
        a[n*2+1]=0;
        for(int i=n*2;i>=n+1;i--){
            a[i]+=a[i+1];
            mp[a[i]]=i-n-1;
            if(!a[i])
                ans=min(ans,i-1);
        }
        for(int i=n;i>=1;i--)
            if(mp.find(-a[i])!=mp.end())
                ans=min(ans,mp[-a[i]]+n-i);
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：先将果酱映射为 $1$ 和 $-1$，计算前 $n$ 个的前缀和，后 $n$ 个的后缀和，用 `map` 记录后缀和，枚举前缀和，若存在相反数则更新答案。

#### Dolphin_
```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=100005;//防止数组越界
int T,f[220000],a[220000],x,n,ans,sum;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(f,128,sizeof f);
        memset(a,0,sizeof a);
        n=0;x=0;sum=0;ans=0;
        scanf("%d",&n);f[P]=0;
        sum=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&x);
            if(x==2) x=-1;
            sum+=x;
            f[sum+P]=max(f[sum+P],i);
            if(sum==0) ans=max(ans,f[sum+P]);
        }
        for(int i=1;i<=n;++i) {scanf("%d",&a[i]);if(a[i]==2) a[i]=-1;}
        sum=0;
        for(int i=n;i>=1;--i)
        {
            sum+=a[i];
            ans=max(n-i+1+f[-sum+P],ans);
        }
        printf("%d\n",2*n-ans);
    }
    return 0;
}
```
**核心实现思想**：先处理前半段，用数组 `f` 记录 1 和 2 两种物品差为某值时左边用的最多个数，再循环后半段，用后面的个数加上后面的差所对应的前面的差去更新答案。

#### YGB_XU
```cpp
#include<bits/stdc++.h>
using namespace std;

const int NR=2e5+5;
int l[NR],r[NR],fl[NR*2+5],fr[NR*2+5]; 

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        memset(fl,0,sizeof(fl));
        memset(fr,0,sizeof(fr));
        int n;
        scanf("%d",&n);
        for(int i=n;i>=1;i--) scanf("%d",&l[i]);
        for(int i=1;i<=n;i++) scanf("%d",&r[i]);
        int sum=0,nl=0,nr=0;
        for(int i=1;i<=n;i++){
            if(l[i]==1){
                nl++;
                sum++;
            }else{
                nl--;
                sum--;
            }
            if(r[i]==1){
                nr++;
                sum++;
            }else{
                nr--;
                sum--;
            }
            if(!fl[nl+NR]) fl[nl+NR]=i;
            if(!fr[nr+NR]) fr[nr+NR]=i;
        }
        if(sum==0){
            printf("0\n");
            continue;
        }
        int ans=2e9;
        for(int i=-n;i<=n;i++){
            int j=sum-i;
            if(fl[i+NR]&&i==sum) ans=min(ans,fl[i+NR]);
            if(fr[j+NR]&&j==sum) ans=min(ans,fr[j+NR]);
            if(!fl[i+NR]||!fr[j+NR]) continue;
            ans=min(ans,fl[i+NR]+fr[j+NR]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：分别预处理左右两列的差值信息，枚举左边差值计算右边对应差值，用两侧差值对应取走最小果酱数更新答案。

### 最优关键思路或技巧
- 将两种果酱映射为 $1$ 和 $-1$，通过计算前缀和与后缀和来判断两种果酱数量是否相等。
- 使用 `map` 或数组记录差值信息，方便查找和更新答案。

### 拓展思路
同类型题或类似算法套路：涉及区间元素数量关系的题目，可考虑将元素映射为数值，通过前缀和或后缀和来计算区间和，从而判断元素数量关系。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)
- [P3131 [USACO16JAN]Subsequences Summing to Sevens S](https://www.luogu.com.cn/problem/P3131)

---
处理用时：73.17秒