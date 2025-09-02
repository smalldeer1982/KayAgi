# 题目信息

# Recommendations

## 题目描述

VK news recommendation system daily selects interesting publications of one of $ n $ disjoint categories for each user. Each publication belongs to exactly one category. For each category $ i $ batch algorithm selects $ a_i $ publications.

The latest A/B test suggests that users are reading recommended publications more actively if each category has a different number of publications within daily recommendations. The targeted algorithm can find a single interesting publication of $ i $ -th category within $ t_i $ seconds.

What is the minimum total time necessary to add publications to the result of batch algorithm execution, so all categories have a different number of publications? You can't remove publications recommended by the batch algorithm.

## 说明/提示

In the first example, it is possible to find three publications of the second type, which will take 6 seconds.

In the second example, all news categories contain a different number of publications.

## 样例 #1

### 输入

```
5
3 7 9 7 8
5 2 5 7 5```

### 输出

```
6```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 1 1 1 1```

### 输出

```
0```

# AI分析结果

### 题目翻译
# 推荐系统

## 题目描述
VK 新闻推荐系统每天会为每个用户从 $n$ 个不相交的类别中选择有趣的出版物。每个出版物恰好属于一个类别。对于每个类别 $i$，批量算法会选择 $a_i$ 个出版物。

最新的 A/B 测试表明，如果每日推荐中每个类别的出版物数量不同，用户会更积极地阅读推荐的出版物。目标算法可以在 $t_i$ 秒内找到第 $i$ 类别的一个有趣出版物。

在批量算法执行结果的基础上，添加出版物以使所有类别具有不同数量的出版物所需的最小总时间是多少？你不能删除批量算法推荐的出版物。

## 说明/提示
在第一个示例中，可以找到三个第二类别的出版物，这将花费 6 秒。

在第二个示例中，所有新闻类别包含不同数量的出版物。

## 样例 #1
### 输入
```
5
3 7 9 7 8
5 2 5 7 5
```
### 输出
```
6
```

## 样例 #2
### 输入
```
5
1 2 3 4 5
1 1 1 1 1
```
### 输出
```
0
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即优先保留花费大的出版物，让花费小的出版物增加数量，以此来使所有类别出版物数量不同且总花费最小。不同题解在实现方式上有所差异，主要体现在数据结构的选择和具体的模拟过程上。有的使用堆来维护最大花费，有的使用线段树优化查找空位的过程，还有的先计算出最终每个数应达到的值再进行处理。

### 所选题解
- **灵茶山艾府（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用大根堆来维护花费，模拟过程简洁明了。
- **fanminghao000（4星）**
    - **关键亮点**：详细阐述了贪心的正确性，代码实现逻辑清晰，使用堆来维护实时最大值。
- **wasa855（4星）**
    - **关键亮点**：实现过程简单，不需要高级数据结构，同样使用堆来处理，且不会被卡常。

### 重点代码
#### 灵茶山艾府（Golang）
```go
func main() {
    in := bufio.NewReader(os.Stdin)
    var n int
    Fscan(in, &n)
    a := make([]struct{ v, t int }, n)
    for i := range a { Fscan(in, &a[i].v) }
    for i := range a { Fscan(in, &a[i].t) }
    sort.Slice(a, func(i, j int) bool { return a[i].v < a[j].v })

    ans := int64(0)
    h := hp{}
    for i, cur, costSum := 0, 0, int64(0); i < n || h.Len() > 0; cur++ {
        if h.Len() == 0 { cur = a[i].v }
        for ; i < n && a[i].v == cur; i++ { // 所有等于 cur 的元素的花费入堆
            heap.Push(&h, a[i].t)
            costSum += int64(a[i].t)
        }
        costSum -= int64(heap.Pop(&h).(int)) // 弹出一个最大花费，表示这个元素不需要继续增大
        ans += costSum
    }
    Print(ans)
}
```
**核心实现思想**：按 $a[i]$ 从小到大排序，将相同 $a[i]$ 的花费放入大根堆，每次弹出最大花费，累加剩余花费得到答案。

#### fanminghao000（C++）
```cpp
signed main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].a;
    for(int i=1;i<=n;i++) cin>>a[i].t;
    sort(a+1,a+n+1);
    priority_queue<int> q;
    int now=0,sum=0,ans=0;
    for(int i=1;i<=n;i++){
        if(q.empty()){//这个位置现在是空的
            now=a[i].a;
            q.push(a[i].t);
            sum+=a[i].t;
        }
        else{
            if(a[i].a==now){//相同，放进堆里等待+1
                q.push(a[i].t);
                sum+=a[i].t;
            }
            else if(a[i].a>now){
                while(a[i].a>now&&!q.empty()){//不同，执行+1操作
                    sum-=q.top();
                    q.pop();
                    ans+=sum;
                    now++;
                }
                if(a[i].a==now){//又相同了，再往里放 
                    q.push(a[i].t);
                    sum+=a[i].t;
                }
                else if(q.empty()){//前面的都执行完了，上一个位置和这个位置没有重叠
                    q.push(a[i].t);
                    sum+=a[i].t;
                    now=a[i].a;
                }
            }
        }
    }
    while(!q.empty()){//剩下的也要放完
        sum-=q.top();
        q.pop();
        ans+=sum;
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：按 $a_i$ 升序排列后遍历，用堆维护实时最大值，根据当前位置情况进行操作，最后累加剩余花费。

#### wasa855（C++）
```cpp
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++) a[i].x=read();
    for(int i=1;i<=n;i++) a[i].y=read();
    sort(a+1,a+n+1,cmp);
    priority_queue<int> q;
    int cur=0,cnt=0,ans=0,tmp=0;
    while(!q.empty()||cur<n)
    {
        cnt++;
        if(q.empty())
        {
            cnt=a[cur+1].x;
            while(cnt==a[cur+1].x&&cur<n)
            {
                cur++;
                tmp+=a[cur].y;
                q.push(a[cur].y);
            }
        }
        else
        {
            while(cnt==a[cur+1].x&&cur<n)
            {
                cur++;
                tmp+=a[cur].y;
                q.push(a[cur].y);
            }
        }
        tmp-=q.top(); q.pop();
        ans+=tmp;
    }
    cout<<ans<<endl;
    return 0;
}
```
**核心实现思想**：按 $a$ 从小到大排序，用堆处理相同 $a$ 的情况，每次弹出最大花费，累加剩余花费。

### 最优关键思路或技巧
- 使用大根堆维护花费，方便每次取出最大花费的元素，保证优先保留花费大的出版物。
- 按 $a$ 从小到大排序，便于处理相同 $a$ 的元素。

### 拓展思路
同类型题目可能会有不同的限制条件或数据范围，例如出版物数量的上限、不同的花费计算方式等。类似算法套路可以应用在需要对元素进行调整以满足某种条件且要使总代价最小的问题中，关键在于找到合适的贪心策略并选择合适的数据结构来实现。

### 推荐洛谷题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

### 个人心得摘录与总结
- **ix35**：提到比赛时 FST（可能是测试数据未通过），但交到洛谷上 AC 了，说明不同的测试数据可能会导致结果不同，需要注意代码的健壮性。
- **fanminghao000**：偶然在以前模拟赛里翻到这道题并写题解记录，提醒我们可以通过回顾旧题来加深对知识点的理解和掌握。 

---
处理用时：54.29秒