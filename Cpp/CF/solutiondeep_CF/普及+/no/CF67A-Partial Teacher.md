# 题目信息

# Partial Teacher

## 题目描述

A teacher decides to give toffees to his students. He asks $ n $ students to stand in a queue. Since the teacher is very partial, he follows the following rule to distribute toffees.

He looks at the first two students and gives more toffees to the student having higher marks than the other one. If they have the same marks they get the same number of toffees. The same procedure is followed for each pair of adjacent students starting from the first one to the last one.

It is given that each student receives at least one toffee. You have to find the number of toffees given to each student by the teacher such that the total number of toffees is minimum.

## 样例 #1

### 输入

```
5
LRLR
```

### 输出

```
2 1 2 1 2
```

## 样例 #2

### 输入

```
5
=RRR
```

### 输出

```
1 1 2 3 4
```

# AI分析结果

### 题目内容
# 偏心的老师

## 题目描述
一位老师决定给学生们发太妃糖。他让$n$个学生站成一排。由于这位老师非常偏心，他按照以下规则分发太妃糖。

他观察前两个学生，给成绩比另一个学生高的学生更多的太妃糖。如果他们成绩相同，他们得到相同数量的太妃糖。从第一个学生到最后一个学生，每对相邻学生都遵循相同的程序。

已知每个学生至少会收到一颗太妃糖。你需要找出老师给每个学生的太妃糖数量，使得太妃糖的总数最少。

## 样例 #1
### 输入
```
5
LRLR
```
### 输出
```
2 1 2 1 2
```
## 样例 #2
### 输入
```
5
=RRR
```
### 输出
```
1 1 2 3 4
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要分为贪心和差分约束两种思路。贪心思路直接根据相邻学生成绩关系（用字符表示）来确定糖果分配数量，确保每个学生至少有1颗糖且总数最少。差分约束思路则是将相邻学生糖果数量关系转化为不等式，通过建图并利用最短路或最长路算法求解。

贪心思路相对直观，实现简单；差分约束虽理论性强，但对于熟悉该算法的人来说，代码实现也较为固定。解决本题的难点在于处理好相邻学生糖果数量的关系，保证满足条件且总数最小。对于贪心算法，要注意在字符为“L”时，若左边学生糖果数为1需向前调整；对于差分约束，关键是正确建立不等式和图的连接关系。

### 所选的题解
- **作者：谦谦君子 (5星)**
    - **关键亮点**：思路清晰，直接根据题目规则进行贪心分配，代码简洁明了，可读性高。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int candy[10001];
string s;
int main()
{
    int n;
    cin>>n;
    candy[0]=1;
    cin>>s;
    s='%'+s;
    for (int i=1;i<n;i++)
    {
        if (s[i]=='=')
        {
            candy[i]=candy[i-1];
        }
        if (s[i]=='R')
        {
            candy[i]=candy[i-1]+1;
        }
        if (s[i]=='L')
        {
            candy[i]=1;
            if (candy[i-1]==1)
            {
                candy[i-1]++;
                for (int j=i-1;j>=1;j--)
                {
                    if (s[j]=='=')
                    {
                        candy[j-1]=candy[j];
                    }
                    else if (s[j]=='L'&&candy[j-1]==candy[j])
                    {
                        candy[j-1]++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<candy[i]<<" ";
    }
    cout<<endl;
    return 0;
}
```
    - **核心实现思想**：遍历表示相邻学生成绩关系的字符串，根据字符“=”“R”“L”分别进行糖果数量的赋值与调整。“=”时，当前学生糖果数等于前一个学生；“R”时，当前学生糖果数比前一个学生多1；“L”时，当前学生糖果数设为1，若前一个学生糖果数也为1，则向前调整前一个学生糖果数，并根据之前的关系继续向前调整。
- **作者：0xFF (4星)**
    - **关键亮点**：将问题转化为差分约束的标准模型，思路明确，代码规范，展现了对差分约束算法的熟练运用。
    - **重点代码**：
```cpp
#include<iostream>
#include<queue>
using namespace std;
const int maxn = 1e5 + 10;
int n,head[maxn],cnt;
struct node{
    int to,next,val;
}edge[maxn<<2];
void addedge(int u,int v,int w){
    edge[++cnt].to = v;
    edge[cnt].val  = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int dis[maxn];
bool vis[maxn];
queue<int> q;
void spfa(){
    dis[0] = 1;
    q.push(0);
    vis[0] = true;
    while(!q.empty()){
        int u = q.front();
        vis[u] = false;
        q.pop();
        for(int i=head[u];i;i=edge[i].next){
            int v = edge[i].to, w = edge[i].val;
            if(dis[v] < dis[u] + w){
                dis[v] = dis[u] + w;
                if(!vis[v]){
                    q.push(v);
                    vis[v] = true; 
                }
            }
        }
    } 
}
int main(){
    n = read();
    for(int i=1;i<=n;i++){
        addedge(0,i,0);
    }
    for(int i=1;i<n;i++){
        char s;
        cin >> s;
        if(s == '=') addedge(i,i+1,0), addedge(i+1,i,0);
        else if(s == 'L') addedge(i+1,i,1);
        else if(s == 'R') addedge(i,i+1,1); 
    }
    spfa();
    for(int i=1;i<=n;i++){
        printf("%d ",dis[i]);
    }
    printf("\n");
    return 0;
}
```
    - **核心实现思想**：根据相邻学生糖果数量关系建立不等式，转化为图的边。“=”时双向连权值为0的边；“L”时从后向前连权值为1的边；“R”时从前向后连权值为1的边。再从超级源点0出发，利用SPFA算法求最长路得到每个学生最少的糖果数。
- **作者：Fengyiwei1234 (4星)**
    - **关键亮点**：同样采用贪心策略，代码简洁易懂，对“L”情况的特判处理清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[10005]={1},n;
int main()
{
    string s;
    cin>>n;
    cin>>s;
    s='#'+s;
    for(int i=1;i<n;i++)
    {
        if(s[i]=='=')f[i]=f[i-1];
        else if(s[i]=='R')f[i]=f[i-1]+1;
        else if(s[i]=='L')
        {
            f[i]=1;
            if(f[i-1]==1)
            {
                f[i-1]=2;
                for(int j=i-1;j>=1;j--)
                {
                    if(s[j]=='=')f[j-1]=f[j];
                    else if(s[j]=='L'&&f[j-1]==f[j])f[j-1]++;
                    else break;
                }
            }
        }
    }
    for(int i=0;i<n;i++)cout<<f[i]<<" ";
    return 0;
}
```
    - **核心实现思想**：遍历字符串，依据字符“=”“R”“L”对表示学生糖果数的数组$f$进行赋值和调整。与“谦谦君子”的代码思路类似，“L”情况处理时，若前一个学生糖果数为1则进行向前调整。

### 最优关键思路或技巧
贪心算法中，直接按照相邻学生成绩关系（字符表示）进行糖果分配，在遇到“L”且前一个学生糖果数为1时，及时向前调整糖果数，确保满足条件且总数最小，这种直接模拟规则的方式简单高效。差分约束算法则是将问题转化为标准的图论模型，通过建立不等式关系和图的连接，利用成熟的最短路（这里是最长路）算法求解，体现了对算法模型的灵活运用。

### 拓展与类似题目
同类型题或类似算法套路：此类题目通常涉及到根据某种顺序关系或约束条件来进行最优分配。可以拓展到更多复杂的关系约束，如多个元素间的比较关系，或者在分配时存在更多的限制条件。

推荐洛谷题目：
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，根据一定条件对数据进行排序并计算最优解。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要通过分析游戏规则，运用贪心思想找到最优策略。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：典型的贪心算法应用，根据接水时间进行排序以得到最短等待总时间。

### 个人心得摘录
**谦谦君子**：虽然是A题，但打了快半小时还没过样例。这表明即使看似简单的题目，在实现细节上也可能遇到困难，需要仔细调试和思考。 

---
处理用时：99.37秒