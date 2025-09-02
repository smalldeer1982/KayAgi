# 题目信息

# Mahmoud and Ehab and the message

## 题目描述

小A想要给他的朋友小B发送了一条有 $m$ 个单词的消息。他们的语言由编号从 $a_1$ 到 $a_n$ 的 $n$ 个单词组成。一些单词具有相同的意思，因此存在 $k$ 个单词组，其中每个组中的所有单词具有相同的意思。小A知道第 $i$ 个单词可以以成本 $m_i$ 发送。

对于他的每个消息中的单词，小A可以将其替换为具有相同意思的另一个单词，或者保持不变。请帮助小A确定发送消息的最小价值。

发送消息的成本是其中每个单词的发送成本的总和。

## 样例 #1

### 输入

```
5 4 4
i loser am the second
100 1 1 5 10
1 1
1 3
2 2 5
1 4
i am the second
```

### 输出

```
107```

## 样例 #2

### 输入

```
5 4 4
i loser am the second
100 20 1 5 10
1 1
1 3
2 2 5
1 4
i am the second
```

### 输出

```
116```

# AI分析结果

### 题目内容
# Mahmoud和Ehab与消息

## 题目描述
小A想要给他的朋友小B发送一条包含 $m$ 个单词的消息。他们的语言由编号从 $a_1$ 到 $a_n$ 的 $n$ 个单词组成。一些单词具有相同的意思，因此存在 $k$ 个单词组，其中每个组中的所有单词意思相同。小A知道第 $i$ 个单词的发送成本为 $m_i$ 。

对于消息中的每个单词，小A可以将其替换为具有相同意思的另一个单词，或者保持不变。请帮助小A确定发送该消息的最小成本。

发送消息的成本是其中每个单词发送成本的总和。

## 样例 #1
### 输入
```
5 4 4
i loser am the second
100 1 1 5 10
1 1
1 3
2 2 5
1 4
i am the second
```
### 输出
```
107```

## 样例 #2
### 输入
```
5 4 4
i loser am the second
100 20 1 5 10
1 1
1 3
2 2 5
1 4
i am the second
```
### 输出
```
116```

### 算法分类
贪心

### 综合分析与结论
这几道题解的核心思路均基于贪心策略，即对于每个单词组，选择组内成本最小的单词来替换消息中的单词，以达到总成本最小。不同题解在实现细节上有所差异，主要体现在数据结构的使用和处理流程上。

sqrt404的题解使用结构体和两个`map`分别存储单词及其价值、编号及其对应的单词，在输入时直接更新相同词义单词的最小价值，最后遍历消息计算总成本，思路和代码较为清晰易懂。

zzhbpyy的题解使用`unordered_map`记录单词的组号，用`vector`数组存储每组单词编号并排序，通过`Lambda`表达式简化排序代码，在遍历消息时直接累加对应组的最小成本，代码简洁高效。

Zhuluoan的题解使用`map`将单词与编号对应，用数组记录每个单词组的最小值和单词所属组号，在输入单词组时更新最小值，最后遍历消息累加成本，逻辑清晰。

小闸蟹的题解通过`unordered_map`记录单词编号，在输入单词组时找出并更新同组单词的最小成本，最后遍历消息计算总成本，代码较为朴素，运行时间相对较长。

### 所选的题解
- **sqrt404题解（4星）**
    - **关键亮点**：使用结构体和`map`存储数据，输入时直接更新相同词义单词的最小价值，思路清晰，代码可读性高。
    - **核心代码**：
```cpp
struct word // 储存词库
{
    int money;// 价值
    string name;// 储存名字，主要是为了下面的序号与单词的对应
};
int n, k, m, gg;
map<string, word> str;
map<int, word> strn;
string bala[100005], sentens[100005];
int main()
{
    cin >> n >> k >> m;
    for(int i = 1; i <= n; i++) cin >> bala[i];
    for(int i = 1; i <= n; i++)
    {
        cin >> str[bala[i]].money;
        strn[i].name = bala[i];
    }
    for(int i = 1; i <= k; i++)
    {
        cin >> gg;
        if(gg == 1) 
        {
            int hh; 
            cin >> hh;
        }
        else
        {
            int same[100005];
            for(int j = 1; j <= gg; j++) cin >> same[j];
            int flag = str[strn[same[1]].name].money; 
            for(int j = 1; j <= gg; j++) flag = min(flag, str[strn[same[j]].name].money);
            for(int j = 1; j <= gg; j++) str[strn[same[j]].name].money = flag;
        }
    }
    unsigned long long sum = 0;
    for(int i = 1; i <= m; i++)
    {
        cin >> sentens[i];
        sum += str[sentens[i]].money;
    }
    cout << sum << endl;
    return 0;
}
```
    - **核心实现思想**：先将单词及其价值、编号及其对应的单词分别存入`map`，在处理相同词义单词组时，找出组内最小价值并更新所有同组单词的价值，最后遍历消息计算总成本。
- **zzhbpyy题解（4星）**
    - **关键亮点**：利用`unordered_map`和`vector`数组存储数据，使用`Lambda`表达式简化排序代码，代码简洁高效。
    - **核心代码**：
```cpp
struct G{
    string a;
    int b; 
}a[100005];
int n,k,m,c,tmp;
vector<int>aa[100005];
unordered_map<string,int>mp;
signed main(){
    cin>>n>>k>>m;
    for(int i=1;i<=n;i++)cin>>a[i].a;
    for(int i=1;i<=n;i++)cin>>a[i].b;
    for(int i=1;i<=k;i++){
        cin>>c;
        while(c--){
            cin>>tmp;mp[a[tmp].a]=i;
            aa[i].push_back(tmp);
        }
        sort(aa[i].begin(),aa[i].end(),[](int c,int d){return a[c].b<a[d].b;});
    }
    string d;int ans=0;
    while(m--){
        cin>>d;
        ans+=a[*(aa[mp[d]].begin())].b;
    }
    cout<<ans;
}
```
    - **核心实现思想**：先将单词及其成本存入结构体数组，在处理相同词义单词组时，将组内单词编号存入`vector`数组并按成本排序，最后遍历消息，累加对应组的最小成本。
- **Zhuluoan题解（4星）**
    - **关键亮点**：使用`map`和数组记录单词对应关系和所属组号及最小值，逻辑清晰。
    - **核心代码**：
```cpp
int n,k,m,vis[N],x,Min[N];
ll ans;
string q;
map<string,int> Vis;
struct word
{
    string s;
    int val;
}a[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k>>m;
    mem(Min,0x3f);
    For(i,1,n)
    {
        cin>>a[i].s;
        Vis[a[i].s]=i;
    }
    For(i,1,n)
    {
        cin>>a[i].val;
    }
    For(i,1,k)
    {
        cin>>x;
        int temp=0;
        while(x--)
        {
            cin>>temp;
            vis[temp]=i;
            Min[i]=min(Min[i],a[temp].val);
        }
    }
    For(i,1,m)
    {
        cin>>q;
        ans+=Min[vis[Vis[q]]];
    }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：先通过`map`建立单词与编号的对应关系，在处理相同词义单词组时，记录单词所属组号并更新组内最小值，最后遍历消息累加对应组的最小值。

### 最优关键思路或技巧
这几题解的最优关键思路在于利用贪心策略，在处理相同词义单词组时，提前确定并更新组内最小成本，避免在遍历消息时重复计算。在数据结构使用上，`map`、`unordered_map`和`vector`等的合理运用有助于高效存储和查找数据。

### 可拓展之处
同类型题目通常围绕具有相同属性（如本题的相同词义）的元素集合，需要在集合中选择最优元素以满足某种目标（如最小成本）。类似算法套路是利用贪心策略结合合适的数据结构，快速定位和处理最优元素。

### 洛谷题目推荐
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过不断合并最小的两堆果子，以最小的总代价完成合并，考察贪心策略。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间对人进行排序，以最小化所有人的等待时间总和，也是贪心思想的应用。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对国王和王后的能力值进行排序，确定最优的处理顺序，考察贪心策略和排序技巧。

### 个人心得摘录与总结
暂无个人心得。 

---
处理用时：88.48秒