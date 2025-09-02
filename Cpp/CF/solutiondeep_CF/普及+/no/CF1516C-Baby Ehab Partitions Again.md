# 题目信息

# Baby Ehab Partitions Again

## 题目描述

Baby Ehab was toying around with arrays. He has an array $ a $ of length $ n $ . He defines an array to be good if there's no way to partition it into $ 2 $ subsequences such that the sum of the elements in the first is equal to the sum of the elements in the second. Now he wants to remove the minimum number of elements in $ a $ so that it becomes a good array. Can you help him?

A sequence $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by deleting some (possibly zero or all) elements. A partitioning of an array is a way to divide it into $ 2 $ subsequences such that every element belongs to exactly one subsequence, so you must use all the elements, and you can't share any elements.

## 说明/提示

In the first example, you can partition the array into $ [6,9] $ and $ [3,12] $ , so you must remove at least $ 1 $ element. Removing $ 3 $ is sufficient.

In the second example, the array is already good, so you don't need to remove any elements.

## 样例 #1

### 输入

```
4
6 3 9 12```

### 输出

```
1
2```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
0```

# AI分析结果

### 题目内容翻译
# 小伊哈布再次进行划分

## 题目描述
小伊哈布正在摆弄数组。他有一个长度为 $n$ 的数组 $a$。他将一个数组定义为“好的”，如果不存在将其划分为两个子序列的方法，使得第一个子序列中元素的和等于第二个子序列中元素的和。现在他想删除数组 $a$ 中最少数量的元素，使其成为一个“好的”数组。你能帮助他吗？

一个序列 $b$ 是数组 $a$ 的子序列，如果 $b$ 可以通过删除数组 $a$ 中的一些（可能是零个或全部）元素得到。数组的划分是将其分成两个子序列的一种方式，使得每个元素恰好属于一个子序列，所以你必须使用所有元素，并且不能共享任何元素。

## 说明/提示
在第一个示例中，你可以将数组划分为 $[6,9]$ 和 $[3,12]$，所以你必须至少删除 $1$ 个元素。删除 $3$ 就足够了。

在第二个示例中，数组已经是“好的”，所以你不需要删除任何元素。

## 样例 #1
### 输入
```
4
6 3 9 12
```
### 输出
```
1
2
```

## 样例 #2
### 输入
```
2
1 2
```
### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先判断原数组是否已经是“好的”数组，若不是，则通过一定方法找到需要删除的最少元素。判断原数组是否为“好的”数组时，大多使用 0 - 1 背包问题的思路，即判断是否能从数组中选出一些元素，使其和等于数组总和的一半。若原数组总和为奇数，则一定是“好的”数组；若总和为偶数且能划分成两个和相等的子序列，则需要删除元素。若数组中存在奇数，删除该奇数即可；若全是偶数，则不断将所有元素除以 2，直到出现奇数再删除。

各题解的区别主要在于代码实现细节和寻找需要删除元素的方式，如有的通过统计每个数含 2 的幂次，有的通过不断除 2 找奇数等。

### 所选题解
- 作者：江户川·萝卜 (赞：15)，4 星。
  - 关键亮点：思路清晰，代码简洁，先判断数组总和奇偶性，再用背包判断是否能划分，最后通过统计每个数含 2 的幂次找到要删除的元素。
- 作者：Priori_Incantatem (赞：11)，4 星。
  - 关键亮点：详细证明了只需要删去一个元素就可以让原序列满足要求，逻辑严谨，代码实现规范。
- 作者：huayucaiji (赞：2)，4 星。
  - 关键亮点：明确得出最多去掉一个数的结论，代码中使用滚动数组优化空间，有一定的优化意识。

### 重点代码
#### 江户川·萝卜的代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[105];
bool f[200005];
int main(){
    int n,sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];
    if(sum&1){
        puts("0");
        return 0;
    }
    sum/=2;
    f[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=sum;j>=a[i];j--)
            f[j]|=f[j-a[i]];
    if(!f[sum]){
        puts("0");
        return 0;
    }
    int minc=1e5,minp=0;
    for(int i=1;i<=n;i++){
        int x=a[i],cnt=0;
        while(!(x&1)){
            x>>=1;
            cnt++;
        }
        if(cnt<minc) minc=cnt,minp=i;
    }
    printf("1\n%d",minp);
    return 0;
}
```
核心实现思想：先计算数组总和，若为奇数则直接输出 0。若为偶数，使用 0 - 1 背包判断是否能划分成两个和相等的子序列，若不能则输出 0。若能，则统计每个数含 2 的幂次，输出幂次最小的数的位置。

#### Priori_Incantatem 的代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=110;
const int Maxm=200010;
bool f[Maxm];
int a[Maxn];
int n,m;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",a+i),m+=a[i];
    f[0]=1;
    for(int i=1;i<=n;++i)
        for(int j=m;j>=a[i];--j)
            f[j]|=f[j-a[i]];
    if((m & 1) || !f[m>>1])
    {puts("0");return 0;}
    int ans=60,pos;
    for(int i=1;i<=n;++i)
    {
        int tmp=0;
        for(int j=30;j>=0;--j)
            if(a[i]%(1<<j)==0){tmp=j;break;}
        if(tmp<ans)ans=tmp,pos=i;
    }
    printf("1\n%d\n",pos);
    return 0;
}
```
核心实现思想：先计算数组总和，若为奇数或不能划分成两个和相等的子序列则输出 0。若能划分，则通过计算每个数能被 2 的最大幂次整除，找到幂次最小的数的位置并输出。

#### huayucaiji 的代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
    char ch=getchar();
    int f=1,x=0;
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

const int MAXN=1e5;

int n,sum;
int a[MAXN];
bool f[2][MAXN];

void div() {
    while(1) {
        for(int i=1;i<=n;i++) {
            if(a[i]&1) {
                cout<<1<<endl<<i<<endl;
                return ;
            }
            a[i]>>=1;
        }
    }
}

signed main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        a[i]=read();
        sum+=a[i];
    }
    if(sum&1) {
        cout<<0<<endl;
        return 0;
    }
    
    int m=sum/2;
    fill(f[0],f[0]+m+1,0);
    f[0][0]=1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<=m;j++) {
            f[i%2][j]=f[(i-1)%2][j];
            if(j>=a[i]) {
                f[i%2][j]=f[i%2][j]|f[(i-1)%2][j-a[i]];
            }
        }
    }
    if(!f[n%2][m]) {
        cout<<0<<endl;
        return 0;
    }
    
    div();
    return 0;
}
```
核心实现思想：先计算数组总和，若为奇数则输出 0。若为偶数，使用滚动数组实现 0 - 1 背包判断是否能划分成两个和相等的子序列，若不能则输出 0。若能，则不断将所有元素除以 2，直到出现奇数，输出该奇数的位置。

### 最优关键思路或技巧
- 使用 0 - 1 背包判断数组是否能划分成两个和相等的子序列。
- 利用数组总和的奇偶性判断数组是否为“好的”数组。
- 当数组全是偶数时，通过不断除以 2 找到奇数。

### 可拓展之处
同类型题或类似算法套路：可以拓展到判断数组能否划分成多个和相等的子序列，或者在删除元素时有更多限制条件的问题。解题思路仍然可以基于动态规划和数学性质的判断。

### 推荐题目
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：0 - 1 背包问题的基础应用。
- [P1734 最大约数和](https://www.luogu.com.cn/problem/P1734)：涉及动态规划和数学知识。
- [P2347 砝码称重](https://www.luogu.com.cn/problem/P2347)：与本题类似，判断能否用砝码组合出特定重量。

### 个人心得摘录与总结
- huayucaiji：比赛时花了 23 分钟切了此题，总结出最多去掉一个数的结论。这表明在解题过程中通过分析可以得出一些关键结论，帮助简化问题。 

---
处理用时：65.57秒