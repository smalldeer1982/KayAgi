# 题目信息

# Identify the Operations

## 题目描述

We start with a permutation $ a_1, a_2, \ldots, a_n $ and with an empty array $ b $ . We apply the following operation $ k $ times.

On the $ i $ -th iteration, we select an index $ t_i $ ( $ 1 \le t_i \le n-i+1 $ ), remove $ a_{t_i} $ from the array, and append one of the numbers $ a_{t_i-1} $ or $ a_{t_i+1} $ (if $ t_i-1 $ or $ t_i+1 $ are within the array bounds) to the right end of the array $ b $ . Then we move elements $ a_{t_i+1}, \ldots, a_n $ to the left in order to fill in the empty space.

You are given the initial permutation $ a_1, a_2, \ldots, a_n $ and the resulting array $ b_1, b_2, \ldots, b_k $ . All elements of an array $ b $ are distinct. Calculate the number of possible sequences of indices $ t_1, t_2, \ldots, t_k $ modulo $ 998\,244\,353 $ .

## 说明/提示

$ \require{cancel} $

Let's denote as $ a_1 a_2 \ldots \cancel{a_i} \underline{a_{i+1}} \ldots a_n \rightarrow a_1 a_2 \ldots a_{i-1} a_{i+1} \ldots a_{n-1} $ an operation over an element with index $ i $ : removal of element $ a_i $ from array $ a $ and appending element $ a_{i+1} $ to array $ b $ .

In the first example test, the following two options can be used to produce the given array $ b $ :

- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow 1 \underline{2} \cancel{3} 5 \rightarrow 1 \cancel{2} \underline{5} \rightarrow 1 2 $ ; $ (t_1, t_2, t_3) = (4, 3, 2) $ ;
- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow \cancel{1} \underline{2} 3 5 \rightarrow 2 \cancel{3} \underline{5} \rightarrow 1 5 $ ; $ (t_1, t_2, t_3) = (4, 1, 2) $ .

In the second example test, it is impossible to achieve the given array no matter the operations used. That's because, on the first application, we removed the element next to $ 4 $ , namely number $ 3 $ , which means that it couldn't be added to array $ b $ on the second step.

In the third example test, there are four options to achieve the given array $ b $ :

- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 3 2 5 \rightarrow 4 3 \cancel{2} \underline{5} \rightarrow 4 3 5 $ ;
- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{3} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $ ;
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 7 2 5 \rightarrow 4 7 \cancel{2} \underline{5} \rightarrow 4 7 5 $ ;
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{7} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $ ;

## 样例 #1

### 输入

```
3
5 3
1 2 3 4 5
3 2 5
4 3
4 3 2 1
4 3 1
7 4
1 4 7 3 6 2 5
3 2 4 5```

### 输出

```
2
0
4```

# AI分析结果

### 题目中文重写
# 识别操作

## 题目描述
我们从一个排列 $ a_1, a_2, \ldots, a_n $ 开始，并且有一个空数组 $ b $。我们进行以下操作 $ k $ 次。

在第 $ i $ 次迭代中，我们选择一个索引 $ t_i $（$ 1 \le t_i \le n - i + 1 $），从数组中移除 $ a_{t_i} $，并将 $ a_{t_i - 1} $ 或 $ a_{t_i + 1} $ 中的一个数（如果 $ t_i - 1 $ 或 $ t_i + 1 $ 在数组范围内）追加到数组 $ b $ 的右端。然后我们将元素 $ a_{t_i + 1}, \ldots, a_n $ 向左移动以填补空白。

给定初始排列 $ a_1, a_2, \ldots, a_n $ 和结果数组 $ b_1, b_2, \ldots, b_k $。数组 $ b $ 中的所有元素都是不同的。计算可能的索引序列 $ t_1, t_2, \ldots, t_k $ 的数量，结果对 $ 998\,244\,353 $ 取模。

## 说明/提示
我们用 $ a_1 a_2 \ldots \cancel{a_i} \underline{a_{i + 1}} \ldots a_n \rightarrow a_1 a_2 \ldots a_{i - 1} a_{i + 1} \ldots a_{n - 1} $ 表示对索引为 $ i $ 的元素进行的操作：从数组 $ a $ 中移除元素 $ a_i $，并将元素 $ a_{i + 1} $ 追加到数组 $ b $ 中。

在第一个示例测试中，可以使用以下两种方法生成给定的数组 $ b $：
- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow 1 \underline{2} \cancel{3} 5 \rightarrow 1 \cancel{2} \underline{5} \rightarrow 1 2 $；$ (t_1, t_2, t_3) = (4, 3, 2) $；
- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow \cancel{1} \underline{2} 3 5 \rightarrow 2 \cancel{3} \underline{5} \rightarrow 1 5 $；$ (t_1, t_2, t_3) = (4, 1, 2) $。

在第二个示例测试中，无论使用何种操作都无法得到给定的数组。这是因为，在第一次操作中，我们移除了 $ 4 $ 旁边的元素，即数字 $ 3 $，这意味着在第二步中它不能被添加到数组 $ b $ 中。

在第三个示例测试中，有四种方法可以得到给定的数组 $ b $：
- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 3 2 5 \rightarrow 4 3 \cancel{2} \underline{5} \rightarrow 4 3 5 $；
- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{3} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $；
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 7 2 5 \rightarrow 4 7 \cancel{2} \underline{5} \rightarrow 4 7 5 $；
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{7} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $；

## 样例 #1
### 输入
```
3
5 3
1 2 3 4 5
3 2 5
4 3
4 3 2 1
4 3 1
7 4
1 4 7 3 6 2 5
3 2 4 5
```
### 输出
```
2
0
4
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟操作过程，判断每个数左右相邻的数是否可以被删除，从而计算出可能的操作序列数量。具体实现上，不同题解使用了不同的数据结构和方法，但本质相同。主要难点在于判断相邻数是否可删除，以及处理删除操作对后续判断的影响。

### 所选题解
- **作者：tommymio (赞：7)，4星**
    - **关键亮点**：思路清晰，代码简洁，使用数组模拟链表来处理删除操作，易于理解。
- **作者：zztqwq (赞：4)，4星**
    - **关键亮点**：详细证明了结论的正确性，代码规范，逻辑严谨。
- **作者：AsunderSquall (赞：4)，4星**
    - **关键亮点**：使用数组模拟双向链表，对操作过程的模拟更加直观。

### 重点代码
#### tommymio 的代码
```cpp
inline void del(int x) {
    isV[a[x]]=0;
    pre[nxt[x]]=pre[x];
    nxt[pre[x]]=nxt[x];
}
int main() {
    int T=read();
    while(T--) {
        int n=read(),m=read(),ans=1;
        for(register int i=1;i<=n;++i) a[i]=read();
        for(register int i=1;i<=n;++i) pre[i]=nxt[i]=isV[i]=0;
        for(register int i=1;i<=n;++i) {pre[a[i]]=(i>1? a[i-1]:-1);nxt[a[i]]=(i<n? a[i+1]:-1);}
        for(register int i=1;i<=m;++i) {b[i]=read();isV[b[i]]=1;}
        for(register int i=1;i<=m;++i) {
            int f1=(pre[b[i]]!=-1&&!isV[pre[b[i]]]);
            int f2=(nxt[b[i]]!=-1&&!isV[nxt[b[i]]]);
            if(!f1&&!f2) {ans=0;break;}
            else if(f1&&f2) {ans=ans*2ll%mod;}
            isV[b[i]]=0;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：使用 `pre` 和 `nxt` 数组模拟链表，`isV` 数组标记元素是否已被删除。遍历 $b$ 数组，判断每个元素左右相邻的元素是否可删除，根据情况更新答案。

#### zztqwq 的代码
```cpp
int main()
{ 
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(tg,-1,sizeof(tg));
        int n,m;
        scanf("%d %d",&n,&m);
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);
            pos[a[i]]=i;
        } 
        for(int i=1;i<=m;i++) 
        {
            scanf("%d",&b[i]);
            tg[pos[b[i]]]=i;
        }
        int ans=1;
        for(int i=1;i<=m;i++) 
        {  
            int cnt=0;
            if(pos[b[i]]>1 && tg[pos[b[i]]-1]<tg[pos[b[i]]]) cnt++;
            if(pos[b[i]]<n && tg[pos[b[i]]+1]<tg[pos[b[i]]]) cnt++;
            ans*=cnt;
            ans%=998244353;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：使用 `pos` 数组记录每个元素在 $a$ 数组中的位置，`tg` 数组记录每个元素在 $b$ 数组中的出现顺序。遍历 $b$ 数组，判断每个元素左右相邻的元素是否在其之前出现，根据情况更新答案。

#### AsunderSquall 的代码
```cpp
struct TwoList
{
    int pre,nxt;
}L[N];
void Delete(int x)
{
    if (L[x].pre) L[L[x].pre].nxt=L[x].nxt;
    if (L[x].nxt) L[L[x].nxt].pre=L[x].pre;
}
signed main()
{
    int T;
    cin>>T;
    while (T--)
    {
        int ans=1;
        cin>>n>>m;
        for (int i;i<=n;i++) tag[i]=0;
        for (int i=1;i<=n;i++) cin>>a[i],pos[a[i]]=i;
        for (int i=1;i<=m;i++) cin>>b[i],b[i]=pos[b[i]],tag[b[i]]=1;
        for (int i=1;i<=n;i++)
        {
            L[i].pre=i-1;
            L[i].nxt=i+1;
        }
        L[n].nxt=0;
        tag[0]=1;
        for (int i=1;i<=m;i++)
        {
            if (tag[L[b[i]].pre])
            {
                if (tag[L[b[i]].nxt]) {ans=0;}
                else Delete(L[b[i]].nxt);
            }
            else
            {
                if (tag[L[b[i]].nxt]) Delete(L[b[i]].pre);
                else 
                {
                    ans=ans*2%998244353;
                    Delete(L[b[i]].nxt);
                }
            }
            tag[b[i]]=0;
        }
        cout<<ans<<endl;
    }
}
```
**核心实现思想**：使用 `TwoList` 结构体模拟双向链表，`tag` 数组标记元素是否可删除。遍历 $b$ 数组，判断每个元素左右相邻的元素是否可删除，根据情况更新答案并删除相应元素。

### 最优关键思路或技巧
- 使用数组模拟链表或双向链表来处理元素的删除操作，方便记录元素的前驱和后继。
- 标记元素是否已被删除或是否可删除，以便在判断相邻元素是否可删除时使用。

### 可拓展之处
同类型题可能会有更多复杂的操作规则，例如每次操作可以选择多个相邻元素进行删除，或者对删除的元素有其他限制条件。类似算法套路可以用于处理其他需要模拟操作过程并统计方案数的问题。

### 推荐洛谷题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

### 个人心得摘录与总结
- **vеctorwyx**：“呜呜呜这题可算调出来了”，说明该题在调试过程中可能遇到了一些困难，需要耐心调试。

---
处理用时：72.17秒