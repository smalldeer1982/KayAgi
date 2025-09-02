# 题目信息

# Cards Sorting

## 题目描述

Vasily has a deck of cards consisting of $ n $ cards. There is an integer on each of the cards, this integer is between $ 1 $ and $ 100000 $ , inclusive. It is possible that some cards have the same integers on them.

Vasily decided to sort the cards. To do this, he repeatedly takes the top card from the deck, and if the number on it equals the minimum number written on the cards in the deck, then he places the card away. Otherwise, he puts it under the deck and takes the next card from the top, and so on. The process ends as soon as there are no cards in the deck. You can assume that Vasily always knows the minimum number written on some card in the remaining deck, but doesn't know where this card (or these cards) is.

You are to determine the total number of times Vasily takes the top card from the deck.

## 说明/提示

In the first example Vasily at first looks at the card with number $ 6 $ on it, puts it under the deck, then on the card with number $ 3 $ , puts it under the deck, and then on the card with number $ 1 $ . He places away the card with $ 1 $ , because the number written on it is the minimum among the remaining cards. After that the cards from top to bottom are $ [2,6,3] $ . Then Vasily looks at the top card with number $ 2 $ and puts it away. After that the cards from top to bottom are $ [6,3] $ . Then Vasily looks at card $ 6 $ , puts it under the deck, then at card $ 3 $ and puts it away. Then there is only one card with number $ 6 $ on it, and Vasily looks at it and puts it away. Thus, in total Vasily looks at $ 7 $ cards.

## 样例 #1

### 输入

```
4
6 3 1 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
1
1000
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
3 3 3 3 3 3 3
```

### 输出

```
7
```

# AI分析结果

### 题目内容
# 卡片排序

## 题目描述
瓦西里有一副由 $n$ 张卡片组成的牌堆。每张卡片上都有一个整数，这个整数在 $1$ 到 $100000$ 之间（包括 $1$ 和 $100000$）。有可能某些卡片上的整数是相同的。

瓦西里决定对这些卡片进行排序。为此，他反复从牌堆顶部拿起一张卡片，如果卡片上的数字等于牌堆中所有卡片上所写数字中的最小值，那么他就把这张卡片拿走。否则，他就把这张卡片放到牌堆底部，然后再从顶部拿起下一张卡片，依此类推。当牌堆中没有卡片时，这个过程结束。你可以假设瓦西里始终知道剩余牌堆中某些卡片上所写的最小数字，但不知道这张（或这些）卡片在哪里。

你需要确定瓦西里从牌堆顶部拿起卡片的总次数。

## 说明/提示
在第一个示例中，瓦西里首先看了看数字为 $6$ 的卡片，将其放到牌堆底部，然后看了看数字为 $3$ 的卡片，也将其放到牌堆底部，接着看了看数字为 $1$ 的卡片。他拿走了数字为 $1$ 的卡片，因为它上面写的数字是剩余卡片中最小的。之后，从顶部到底部的卡片依次为 $[2,6,3]$。然后瓦西里看了看顶部数字为 $2$ 的卡片并拿走了它。之后，从顶部到底部的卡片依次为 $[6,3]$。然后瓦西里看了看数字为 $6$ 的卡片，将其放到牌堆底部，接着看了看数字为 $3$ 的卡片并拿走了它。然后只剩下一张数字为 $6$ 的卡片，瓦西里看了看它并拿走了它。因此，瓦西里总共看了 $7$ 张卡片。

## 样例 #1
### 输入
```
4
6 3 1 2
```
### 输出
```
7
```

## 样例 #2
### 输入
```
1
1000
```
### 输出
```
1
```

## 样例 #3
### 输入
```
7
3 3 3 3 3 3 3
```
### 输出
```
7
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕如何优化从牌堆取卡片操作次数的计算。难点在于高效地找到最小值并处理卡片位置的移动。各题解思路和方法不同，有的利用数据结构如树状数组、线段树、splay 来优化查找和位置调整操作；有的通过对数据特性的观察，使用集合、链表等简单数据结构配合特定策略来解决问题。

### 所选的题解
- **作者：Acc_Robin (5星)**
    - **关键亮点**：通过开桶记录每个数出现位置，用树状数组标记位置数字是否存在，按值域遍历优化暴力，复杂度 $O(n\log n)$，代码简洁且优化程度高。
    - **核心代码片段**：
```cpp
namespace Acc{
#define int long long
#define id second
    const int N=1e5+10;
    pair<int,int>a[N];
    int n,z=1,l[N],r[N],p=1,m;
    basic_string<int>v[N];
    struct BIT{
        int t[N];
        void add(int x,int k){for(int i=x;i<=n;i+=i&-i)t[i]+=k;}
        int pre(int x){int r=0;for(int i=x;i;i-=i&-i)r+=t[i];return r;}
        int ask(int l,int r){return l>r?0:pre(r)-pre(l-1);}
        void bd(){for(int i=1,j;i<=n;i++)if(t[i]++,(j=i+(i&-i))<=n)t[j]+=t[i];}
    }t;
    void work(){
        cin>>n,t.bd(),memset(l,0x3f,sizeof l);
        for(int i=1,x;i<=n;i++)cin>>x,a[i]={x,i},v[x]+=i,l[x]=min(l[x],i),r[x]=max(r[x],i),m=max(m,x);
        for(int i=1,q;i<=m;i++)if(v[i].size()){
            if(sort(v[i].begin(),v[i].end()),p>l[i]){
                if((q=lower_bound(v[i].begin(),v[i].end(),p)-v[i].begin()))q--;
                z+=t.ask(p+1,n)+t.ask(1,v[i][q]),p=v[i][q];
            }else z+=t.ask(p+1,r[i]),p=r[i];
            for(int j:v[i])t.add(j,-1);
        }
        cout<<z<<'\n';
    }
#undef int
}
```
    - **核心实现思想**：先读入数据并记录每个数的首次和末次出现位置，初始化树状数组。按值域遍历，根据指针 $p$ 与当前数位置关系，用树状数组查询区间和更新答案与指针位置，处理完一个数后在树状数组中减去其对应位置的值。
- **作者：xxr___ (4星)**
    - **关键亮点**：利用 `set` 升序排序特性，每次取出堆顶（最小值）与每个元素比较，复杂度 $O( N \log N )$，思路清晰，代码简洁。
    - **核心代码片段**：
```cpp
int n,a[100010];
set<int>st[100010];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        st[a[i]].insert(i);
    }
    sort(a+1,a+n+1);
    int pos=1;
    long long ans=n;
    for(int i=1;i<=n;i++){
        auto it=st[a[i]].lower_bound(pos);
        if(it==st[a[i]].end()){
            ans+=n-i+1;
            pos=1;
            it=st[a[i]].lower_bound(pos);
        }
        pos=*it;
        st[a[i]].erase(it);
    }
    cout<<ans;
    return 0;
} 
```
    - **核心实现思想**：用 `set` 数组记录每个值出现的位置，排序后按值遍历，通过 `lower_bound` 查找当前值在 `set` 中首次出现位置，若超出范围则更新答案和位置，否则更新位置并删除该位置。
- **作者：CaiXY06 (4星)**
    - **关键亮点**：利用数值范围 $a_i\leq 10^5$，用 `set` 记录各值出现位置，从小到大枚举数值暴力跳位置运算，时间复杂度 $O(n\log n)$，代码实现简单。
    - **核心代码片段**：
```cpp
int n,a[100010];
set<int>S[100010];
set<int>::iterator it;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        S[a[i]].insert(i);
    }
    sort(a+1,a+n+1);
    int p=1;long long ans=n;
    for(int i=1;i<=n;i++){
        it=S[a[i]].lower_bound(p);
        if(it==S[a[i]].end())ans+=n-i+1,p=1,it=S[a[i]].lower_bound(p);
        p=*it,S[a[i]].erase(it);
    }
    printf("%lld",ans);
    return 0;
} 
```
    - **核心实现思想**：读入数据时用 `set` 记录各值位置，排序后按值遍历，通过 `lower_bound` 查找当前值在 `set` 中首次出现位置，若超出范围则更新答案和位置，否则更新位置并删除该位置。

### 最优关键思路或技巧
利用数据结构优化查找和位置调整操作。如Acc_Robin的题解，通过开桶和树状数组，按值域遍历优化暴力求解，在 $O(n\log n)$ 复杂度内高效解决问题；利用 `set` 的特性，如xxr___ 和 CaiXY06 的题解，通过 `set` 记录位置并利用其排序和查找功能简化实现过程。

### 可拓展之处
同类型题通常围绕序列操作和优化查找，类似算法套路有利用各种数据结构优化模拟过程，如用线段树、树状数组维护区间信息，或利用集合、链表等数据结构的特性简化操作。

### 洛谷题目推荐
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可使用树状数组或归并排序求逆序对，与本题类似，需利用数据结构优化操作。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：基础树状数组题目，有助于掌握树状数组的使用，与本题Acc_Robin题解中树状数组应用相关。
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)：贪心算法题目，类似本题需对数据进行处理和优化，可锻炼优化问题的思维。

### 个人心得摘录与总结
无个人心得。 

---
处理用时：69.23秒