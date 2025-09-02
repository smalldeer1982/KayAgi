# 题目信息

# [USACO16OPEN] Diamond Collector S

## 题目描述

奶牛 Bessie 一直喜欢闪闪发光的物体，她最近在业余时间开始了一项爱好——挖掘钻石！她收集了 $N$ 颗大小各不相同的钻石（$N \leq 50,000$），并希望将它们中的一部分放在谷仓里的两个展示柜中展示。

由于 Bessie 希望每个展示柜中的钻石大小相对接近，她决定如果两颗钻石的大小相差超过 $K$，就不能将它们放在同一个展示柜中（如果两颗钻石的大小相差恰好为 $K$，则可以将它们一起展示在同一个展示柜中）。给定 $K$，请帮助 Bessie 确定她可以在两个展示柜中一起展示的最大钻石数量。

## 样例 #1

### 输入

```
7 3
10
5
1
12
9
5
14```

### 输出

```
5```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何在给定的钻石大小序列中，找出两个不重叠且内部大小差值不超过 \( K \) 的区间，使区间内钻石数量之和最大。大多题解先对钻石大小进行排序，将问题转化为寻找不重叠的连续区间。

算法要点上，主要有以下几类：
1. **双指针法**：通过两个指针维护区间，确定每个位置向左或向右能形成的最长合法区间，再枚举分割点计算两区间钻石总数。
2. **动态规划**：用数组记录每个位置左边或右边的最长合法区间长度，类似双指针思路，最后枚举断点求最大和。
3. **二分查找**：利用排序后的单调性，通过二分查找确定每个元素能延伸的最长区间。
4. **线段树等数据结构**：用于区间查询最大值等操作，辅助解决问题。

解决难点在于处理两个不重叠区间的选取，避免区间重叠导致答案错误。许多题解通过枚举分割点，分别计算左右两侧的最优区间来解决。

### 所选的题解
1. **作者：以墨**
    - **星级**：4星
    - **关键亮点**：思路清晰，先提出用DP思想解决问题，定义数组 \( l[i] \) 和 \( r[i] \) 分别记录 \( i \) 左边和右边的最长可延伸长度，通过两次遍历计算这两个数组，最后枚举断开点得到答案。还额外提出二分思路及对应代码，丰富了解题方法。
    - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=50002;
int l[N],r[N],a[N],ans,i,j,n,k;
int main(){
    freopen("diamond.in","r",stdin);
    freopen("diamond.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(i=2,j=1,l[1]=1;i<=n;i++){
        while(a[i]-a[j]>k)
            j++;
        l[i]=max(l[i-1],i-j+1);
    }
    for(i=n-1,j=n,r[n]=1;i>=1;i--){
        while(a[j]-a[i]>k)
            j--;
        r[i]=max(r[i+1],j-i+1);
    }
    for(i=1;i<=n-1;i++)
        ans=max(ans,l[i]+r[i+1]);
    printf("%d\n",ans);
    return 0;
}
```
    - **核心实现思想**：先排序，通过两次循环，利用双指针思想分别计算每个位置左边和右边的最长合法区间长度，最后枚举所有可能的断开点，计算并更新左右区间长度和的最大值。
2. **作者：llzzxx712**
    - **星级**：4星
    - **关键亮点**：详细阐述题意分析和解题思路，包括错误贪心思路及改正方法，对计算左右区间长度的过程解释清晰，代码有详细注释，便于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){//快读 
    int f=1;x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
    x*=f;
}
#define N 50010
int n,k,ans;
int a[N],le[N],r[N];
int main(){
    read(n),read(k);
    for(int i=1;i<=n;i++) read(a[i]);
    sort(a+1,a+1+n);
    le[1]=r[n]=1;
    for(int i=2,now=1;i<=n;i++){ 
        while(a[i]-a[now]>k) now++;
        le[i]=max(le[i-1],i-now+1);
    }
    for(int i=n-1,now=n;i>=1;i--){
        while(a[now]-a[i]>k) now--;
        r[i]=max(r[i+1],now-i+1);
    }
    for(int i=1;i<n;i++){
        ans=max(ans,le[i]+r[i+1]);
    }
    cout<<ans;
}
```
    - **核心实现思想**：快读输入后排序，通过两个循环分别从左到右和从右到左遍历数组，利用双指针确定每个位置的左右最长合法区间长度，最后枚举分割点求最大和。
3. **作者：Zenith_Yeh**
    - **星级**：4星
    - **关键亮点**：提到滑动窗口算法思路，代码简洁明了，通过预处理左右可延伸区间长度，最后枚举分割点取最大值，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int l[50005],r[50005],a[50005],ans,n,k;
int main()
{	n=read(),k=read(); 
    for(register int i=1;i<=n;++i)a[i]=read();
    sort(a+1,a+1+n);
    l[1]=1;
    for(register int i=2,j=1;i<=n;i++){
        while(a[i]-a[j]>k)j++;
        l[i]=max(l[i-1],i-j+1);
    }
    r[n]=1;
    for(register int i=n-1,j=n;i>=1;i--){
        while(a[j]-a[i]>k)j--;
        r[i]=max(r[i+1],j-i+1);
    }
    for(register int i=1;i<=n-1;i++)ans=max(ans,l[i]+r[i+1]);
    printf("%d\n",ans);
    return 0;
}
```
    - **核心实现思想**：快读输入并排序，通过两个循环分别计算每个位置向左和向右的最长合法区间长度，最后枚举分割点，取左右区间长度和的最大值作为答案。

### 最优关键思路或技巧
1. **排序**：将钻石大小排序后，问题转化为在有序序列中找不重叠的连续区间，方便后续处理。
2. **双指针技巧**：用双指针维护区间，能高效地确定每个位置左右的最长合法区间，时间复杂度为 \( O(n) \)。
3. **预处理数组**：通过预处理数组记录每个位置的左右最长合法区间长度，为后续枚举分割点计算答案提供便利。

### 可拓展之处
同类型题或类似算法套路：这类题目通常涉及在序列中寻找满足特定条件的区间，常见条件如区间内元素差值限制、和的范围等。类似算法套路包括先排序，再利用双指针、滑动窗口、动态规划等方法解决问题。例如，在一些求最大子数组和且满足特定条件的题目中，也可先排序或利用双指针维护区间来求解。

### 推荐题目
1. **P1886 滑动窗口 /【模板】单调队列**：通过单调队列维护滑动窗口内的最大值和最小值，与本题双指针维护区间有相似之处。
2. **P2032 扫描**：需要在序列中寻找满足一定条件的区间，可使用类似本题的双指针或动态规划思路。
3. **P3398 仓鼠找sugar**：结合树链剖分和线段树等数据结构，在树上处理区间问题，虽然更复杂，但与本题寻找满足条件区间的思路有相通之处。

### 个人心得摘录与总结
1. **作者：曹老师**：分享了三种解题思路及每种思路的问题，强调前两种想法因未正确处理区间重叠问题导致错误，最终确定第三种思路正确，提醒在解决这类问题时要充分考虑区间重叠情况。 

---
处理用时：50.71秒