# 题目信息

# Numbers Exchange

## 题目描述

Eugeny has $ n $ cards, each of them has exactly one integer written on it. Eugeny wants to exchange some cards with Nikolay so that the number of even integers on his cards would equal the number of odd integers, and that all these numbers would be distinct.

Nikolay has $ m $ cards, distinct numbers from $ 1 $ to $ m $ are written on them, one per card. It means that Nikolay has exactly one card with number $ 1 $ , exactly one card with number $ 2 $ and so on.

A single exchange is a process in which Eugeny gives one card to Nikolay and takes another one from those Nikolay has. Your task is to find the minimum number of card exchanges and determine which cards Eugeny should exchange.

## 样例 #1

### 输入

```
6 2
5 6 7 9 4 5
```

### 输出

```
1
5 6 7 9 4 2 
```

## 样例 #2

### 输入

```
8 6
7 7 7 7 8 8 8 8
```

### 输出

```
6
7 2 4 6 8 1 3 5 
```

## 样例 #3

### 输入

```
4 1
4 2 1 10
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 数字交换

## 题目描述
尤金有 $n$ 张卡片，每张卡片上都恰好写有一个整数。尤金想和尼古拉交换一些卡片，使得他手中卡片上偶数的数量与奇数的数量相等，并且所有这些数字都各不相同。

尼古拉有 $m$ 张卡片，上面分别写有从 $1$ 到 $m$ 的不同数字，每张卡片一个数字。这意味着尼古拉恰好有一张写着数字 $1$ 的卡片，恰好有一张写着数字 $2$ 的卡片，以此类推。

一次交换过程是指尤金给尼古拉一张卡片，并从尼古拉的卡片中拿走另一张。你的任务是找出最少的卡片交换次数，并确定尤金应该交换哪些卡片。

## 样例 #1
### 输入
```
6 2
5 6 7 9 4 5
```
### 输出
```
1
5 6 7 9 4 2 
```

## 样例 #2
### 输入
```
8 6
7 7 7 7 8 8 8 8
```
### 输出
```
6
7 2 4 6 8 1 3 5 
```

## 样例 #3
### 输入
```
4 1
4 2 1 10
```
### 输出
```
-1
```

### 算法分类
贪心

### 综合分析与结论
这两道题解都围绕如何通过最少交换次数使尤金的卡片满足奇偶数量相等且数字唯一的条件。
 - **思路对比**：
    - **_Clown_**：先找出所有不合法的数存于`Vector`，再逐个枚举尼古拉的可替换数，尝试换掉不合法的数，若能换则换，最后判断能否完成目标。
    - **Ninelife_Cat**：先对尤金的卡片按数字值从大到小排序，符合条件的值跳过，将需要填数的位置按数值从小到大填数，若当前需填数值大于`m`则无解。
 - **算法要点对比**：
    - **_Clown_**：利用`map`记录已有的数，`Sum`数组记录奇偶个数，通过循环枚举和条件判断来完成交换操作。
    - **Ninelife_Cat**：借助`map`记录数值是否能填，`vis`数组标记位置是否需填数，通过排序和双指针思想（`now1`和`now2`）来完成填数操作。
 - **解决难点对比**：
    - **_Clown_**：难点在于合理筛选不合法数及有效利用尼古拉的数进行替换，通过`Vector`和循环枚举解决。
    - **Ninelife_Cat**：关键是排序策略及按顺序填数的逻辑，从大到小检查原数及从小到大填数，避免因`m`小于`n`导致位置不够填的问题。

### 所选的题解
 - **作者：_Clown_  星级：4星**
    - **关键亮点**：思路清晰直接，通过模拟和简单数据结构实现，代码简洁明了。
    - **核心代码片段**：
```cpp
int N,M;
int Sum[2];
int Array[200001];
map< int,bool >Have;
vector< int >V;
int main(void)
{
    register int i;
    cin>>N>>M;
    for(i=1;i<=N;i++)
    {
        cin>>Array[i];
        if(Have[Array[i]]||Sum[Array[i]%2]==N/2)
        {
            V.push_back(i);
        }
        else
        {
            Have[Array[i]]=true;
            Sum[Array[i]%2]++;
        }
    }
    register int Count;
    Count=0;
    for(i=1;i<=M;i++)
    {
        if(Have[i]||Sum[i%2]==N/2)
        {
            continue;
        }
        Array[V[Count++]]=i;
        Sum[i%2]++;
        if(Count==V.size())
        {
            break;
        }
    }
    if(Count<V.size())
    {
        cout<<-1<<endl;
        return 0;
    }
    cout<<Count<<endl;
    for(i=1;i<=N;i++)
    {
        cout<<Array[i]<<' ';
    }
    cout<<endl;
    return 0;
}
```
    - **核心实现思想**：先遍历尤金的卡片，将不合法的卡片位置存入`V`，再遍历尼古拉的卡片，尝试用其替换不合法卡片，最后判断是否成功完成替换。
 - **作者：Ninelife_Cat  星级：4星**
    - **关键亮点**：采用贪心策略，通过合理排序和双指针思想，有效解决`m`与`n`大小关系带来的问题。
    - **核心代码片段**：
```cpp
const int N=2e5+10;
int n,m,vis[N],b[N],cnt1,cnt2,ans;
map<int,int> f;
struct qwq {int val,id;} a[N];
inline bool cmp(qwq x,qwq y) {return x.val>y.val;}
signed main()
{
    n=read();m=read();
    for(ri int i=1;i<=n;++i)
        a[a[i].id=i].val=read();
    sort(a+1,a+n+1,cmp);
    for(ri int i=1;i<=n;++i)
    {
        if((a[i].val&1)&&!f[a[i].val])
            if(cnt1<n/2) f[a[i].val]=1,++cnt1,vis[i]=1;
        if(!(a[i].val&1)&&!f[a[i].val])
            if(cnt2<n/2) f[a[i].val]=1,++cnt2,vis[i]=1;
    }
    ri int now1=1,now2=2;
    for(ri int i=1;i<=n;++i)
        if(!vis[i])
        {
            ++ans;
            if(cnt1<n/2)
            {
                while(f[now1]) now1+=2;
                if(now1>m) return cout<<-1,0;
                ++cnt1,vis[i]=1,a[i].val=now1,f[now1]=1;
            }
            else if(cnt2<n/2)
            {
                while(f[now2]) now2+=2;
                if(now2>m) return cout<<-1,0;
                ++cnt2,vis[i]=1,a[i].val=now2,f[now2]=1;
            }
        }
    cout<<ans<<endl;
    for(ri int i=1;i<=n;++i)
        b[a[i].id]=a[i].val;
    for(ri int i=1;i<=n;++i)
        cout<<b[i]<<" ";
    return 0;
}
```
    - **核心实现思想**：先对尤金的卡片按值从大到小排序，遍历筛选出符合条件的数，再用双指针`now1`和`now2`按从小到大顺序填补剩余位置，并判断是否有解。

### 最优关键思路或技巧
 - **排序策略**：Ninelife_Cat 的从大到小排序原卡片数，能有效避免因`m`小于`n`导致位置不够填的问题。
 - **双指针思想**：Ninelife_Cat 利用`now1`和`now2`分别记录当前可填的奇数和偶数，方便按顺序填补空缺位置。
 - **合理利用数据结构**：两者都借助`map`记录已有或可填的数，方便判断和操作。

### 同类型题或类似算法套路拓展
此类题目属于贪心策略在数字组合问题中的应用。通常涉及对给定数字集合进行操作，以满足特定条件，且操作次数需最少。解题关键在于找到合理的贪心策略，如根据数字大小、奇偶性等特性进行排序或筛选。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)

---
处理用时：61.97秒