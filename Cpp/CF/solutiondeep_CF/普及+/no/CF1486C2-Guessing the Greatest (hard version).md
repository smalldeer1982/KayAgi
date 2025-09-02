# 题目信息

# Guessing the Greatest (hard version)

## 题目描述

The only difference between the easy and the hard version is the limit to the number of queries.

This is an interactive problem.

There is an array $ a $ of $ n $ different numbers. In one query you can ask the position of the second maximum element in a subsegment $ a[l..r] $ . Find the position of the maximum element in the array in no more than 20 queries.

A subsegment $ a[l..r] $ is all the elements $ a_l, a_{l + 1}, ..., a_r $ . After asking this subsegment you will be given the position of the second maximum from this subsegment in the whole array.

## 说明/提示

In the sample suppose $ a $ is $ [5, 1, 4, 2, 3] $ . So after asking the $ [1..5] $ subsegment $ 4 $ is second to max value, and it's position is $ 3 $ . After asking the $ [4..5] $ subsegment $ 2 $ is second to max value and it's position in the whole array is $ 4 $ .

Note that there are other arrays $ a $ that would produce the same interaction, and the answer for them might be different. Example output is given in purpose of understanding the interaction.

## 样例 #1

### 输入

```
5

3

4```

### 输出

```
? 1 5

? 4 5

! 1```

# AI分析结果

### 题目内容（中文重写）
# 猜测最大值（困难版本）

## 题目描述
简单版本和困难版本的唯一区别在于查询次数的限制。

这是一道交互式问题。

有一个包含 $n$ 个不同数字的数组 $a$。在一次查询中，你可以询问子段 $a[l..r]$ 中第二大元素的位置。请在不超过 20 次查询内找出数组中最大元素的位置。

子段 $a[l..r]$ 包含所有元素 $a_l, a_{l + 1}, ..., a_r$。在询问这个子段后，你将得到该子段中第二大元素在整个数组中的位置。

## 说明/提示
在示例中，假设 $a$ 为 $[5, 1, 4, 2, 3]$。那么在询问子段 $[1..5]$ 后，4 是第二大的值，它的位置是 3。在询问子段 $[4..5]$ 后，2 是第二大的值，它在整个数组中的位置是 4。

请注意，可能存在其他数组 $a$ 会产生相同的交互结果，并且它们的答案可能不同。给出示例输出是为了帮助理解交互过程。

## 样例 #1
### 输入
```
5
3
4
```
### 输出
```
? 1 5
? 4 5
! 1
```

### 算法分类
二分

### 综合分析与结论
这些题解大多围绕二分算法展开，核心思路是先通过一次查询找出全局次大值的位置 $p$，再通过一次查询确定最大值在 $p$ 的左侧还是右侧，最后在确定的区间内进行二分查找。各题解的主要区别在于代码实现细节和边界情况的处理。

### 所选题解
- **作者：pomelo_nene (赞：5)，4星**
    - **关键亮点**：思路清晰，代码实现简洁明了，对边界情况（如 $p$ 为 1 时）的处理有详细说明。
- **作者：Binary_Lee (赞：4)，4星**
    - **关键亮点**：将二分过程封装成函数，代码结构清晰，对两种情况的处理进行了合并，减少了代码冗余。
- **作者：grass8cow (赞：1)，4星**
    - **关键亮点**：将查询操作封装成函数，代码模块化程度高，逻辑清晰。

### 重点代码
#### pomelo_nene 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define F fflush(stdout)
int n;
int main(){
    scanf("%d",&n);
    int p;
    printf("? 1 %d\n",n);
    F;
    scanf("%d",&p);
    int l=1,r=n;
    if(p==1)
    {
        l=2;
    }
    else
    {
        int dk;
        printf("? %d %d\n",1,p);
        F;
        scanf("%d",&dk);
        if(dk==p)	r=p-1;
        else	l=p+1;
    }
    if(l==p+1)
    {
        while(l<r)
        {
            int mid=(l+r)>>1;
            printf("? %d %d\n",p,mid);
            F;
            int sp;
            scanf("%d",&sp);
            if(sp==p)	r=mid;
            else	l=mid+1;
        }
    }
    else
    {
        while(l<r)
        {
            int mid=(l+r+1)>>1;
            printf("? %d %d\n",mid,p);
            F;
            int sp;
            scanf("%d",&sp);
            if(sp==p)	l=mid;
            else	r=mid-1;
        }
    }
    printf("! %d",l);
    F;
    return 0;
}
```
**核心实现思想**：先查询整个数组的次大值位置 $p$，再根据 $p$ 的位置和查询 $[1,p]$ 的结果确定最大值所在区间，最后在该区间内进行二分查找。

#### Binary_Lee 的代码
```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
using namespace std;
int n,l,r,x,y,mid,ans;
bool fl;
void binary(int l,int r,int typ){
    while(l<=r){
        mid=(l+r)>>1;
        int _1=min(x,mid),_2=x+mid-_1;
        cout<<"? "<<_1<<" "<<_2<<endl;
        cin>>y;
        if((x==y)^typ) l=mid+1;   //两种情况放一起了
        else r=mid-1;
        if(x==y) ans=mid;  //更新ans
    }
}
signed main(){
    cin>>n;
    cout<<"? 1 "<<n<<endl;
    cin>>x;
    if(x!=1){
        cout<<"? 1 "<<x<<endl;
        cin>>y;
        if(y!=x) fl=1;
    }
    else fl=1;
    if(fl) binary(x+1,n,1);
    else binary(1,x-1,0);
    cout<<"! "<<ans<<endl;
    return 0;
}
```
**核心实现思想**：先查询整个数组的次大值位置 $x$，再根据 $x$ 的位置和查询 $[1,x]$ 的结果确定最大值所在区间，然后调用 `binary` 函数在该区间内进行二分查找。

#### grass8cow 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ask(int l,int r){
    int x;
    printf("? %d %d\n",l,r);
    fflush(stdout);scanf("%d",&x);
    return x;
}
int main(){
    scanf("%d",&n);int ans,x=ask(1,n);
    if(x==1||ask(1,x)!=x){
        int l=x+1,r=n;
        while(l<=r){
            int mid=(l+r)>>1,pp=ask(x,mid);
            if(pp==x)ans=mid,r=mid-1;
            else l=mid+1;
        }
    }
    else{
        int l=1,r=x-1;
        while(l<=r){
            int mid=(l+r)>>1,pp=ask(mid,x);
            if(pp==x)ans=mid,l=mid+1;
            else r=mid-1;
        }
    }
    printf("! %d\n",ans);
    return 0;
}
```
**核心实现思想**：将查询操作封装成 `ask` 函数，先查询整个数组的次大值位置 $x$，再根据 $x$ 的位置和查询 $[1,x]$ 的结果确定最大值所在区间，最后在该区间内进行二分查找。

### 最优关键思路或技巧
- 利用数组元素互不相同的性质，通过查询次大值的位置来确定最大值的可能区间。
- 合理运用二分算法，将查询次数控制在 $O(\log n)$ 级别，满足不超过 20 次查询的要求。
- 将查询操作封装成函数，提高代码的模块化程度和可读性。

### 可拓展之处
同类型题或类似算法套路：
- 其他交互式问题，如猜数字、猜序列等，通常需要根据反馈信息逐步缩小范围，可能会用到二分、倍增等算法。
- 涉及区间查询和最值问题的题目，可能会用到线段树、树状数组等数据结构来优化查询效率。

### 推荐题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：二分答案的经典题目，通过二分查找满足条件的最大值。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：同样是二分答案的题目，需要根据题目条件确定二分的范围和判断条件。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：利用二分法求解满足条件的最小化问题。

### 个人心得摘录与总结
- **pomelo_nene**：提到注意有一个小坑点是，如果 $p$ 是 1，那么不能够查询 $[1,p]$，但可以直接确定最大值所在区间在 $[2,n]$。总结：在处理边界情况时需要仔细考虑，避免出现错误。
- **grass8cow**：吐槽会 C1 却不会 C2 的人。总结：不同难度版本的题目可能只是在某些限制条件上有所不同，解题思路可能相似，需要仔细分析题目条件。

---
处理用时：60.67秒