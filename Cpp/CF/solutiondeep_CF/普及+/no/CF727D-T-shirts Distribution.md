# 题目信息

# T-shirts Distribution

## 题目描述

The organizers of a programming contest have decided to present t-shirts to participants. There are six different t-shirts sizes in this problem: S, M, L, XL, XXL, XXXL (sizes are listed in increasing order). The t-shirts are already prepared. For each size from S to XXXL you are given the number of t-shirts of this size.

During the registration, the organizers asked each of the $ n $ participants about the t-shirt size he wants. If a participant hesitated between two sizes, he could specify two neighboring sizes — this means that any of these two sizes suits him.

Write a program that will determine whether it is possible to present a t-shirt to each participant of the competition, or not. Of course, each participant should get a t-shirt of proper size:

- the size he wanted, if he specified one size;
- any of the two neibouring sizes, if he specified two sizes.

If it is possible, the program should find any valid distribution of the t-shirts.

## 样例 #1

### 输入

```
0 1 0 1 1 0
3
XL
S,M
XL,XXL
```

### 输出

```
YES
XL
M
XXL
```

## 样例 #2

### 输入

```
1 1 2 0 1 1
5
S
M
S,M
XXL,XXXL
XL,XXL
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# T恤分发

## 题目描述
编程竞赛的组织者决定给参与者发放T恤。在本题中有六种不同的T恤尺码：S、M、L、XL、XXL、XXXL（尺码按升序排列）。T恤已经准备好。对于从S到XXXL的每个尺码，都会给出该尺码T恤的数量。

在报名期间，组织者询问了 \(n\) 位参与者各自想要的T恤尺码。如果一位参与者在两个尺码之间犹豫不决，他可以指定两个相邻的尺码 —— 这意味着这两个尺码中的任何一个都适合他。

编写一个程序，判断是否有可能给竞赛的每位参与者发放一件T恤。当然，每位参与者都应该得到合适尺码的T恤：
- 如果他指定了一个尺码，就给他想要的那个尺码；
- 如果他指定了两个尺码，就给他两个相邻尺码中的任意一个。

如果有可能，程序应该找出任何一种有效的T恤分配方案。

## 样例 #1
### 输入
```
0 1 0 1 1 0
3
XL
S,M
XL,XXL
```
### 输出
```
YES
XL
M
XXL
```
## 样例 #2
### 输入
```
1 1 2 0 1 1
5
S
M
S,M
XXL,XXXL
XL,XXL
```
### 输出
```
NO
```

### 算法分类
贪心

### 综合分析与结论
三道题解思路相近，均先处理只选一种尺码的参与者，再对剩下有两种选择的参与者进行分配。不同点在于具体实现方式和代码风格。xzggzh1的题解直接通过循环和条件判断进行贪心分配；wmrqwq使用桶排思想，将参与者需求和剩余衣服尺码排序后依次分配；Erica_N_Contina则先对有两种选择的参与者按第一款尺码排序，再从小到大贪心分配衣服。从思路清晰度和代码简洁度看，xzggzh1和Erica_N_Contina的题解相对较好。

### 所选的题解
- **xzggzh1（4星）**
    - **关键亮点**：思路清晰，直接通过循环和条件判断实现贪心算法，先处理只选一种尺码的人，再按顺序贪心分配有两种选择的人。
    - **核心代码**：
```cpp
int main()
{
    for ( int i = 0; i < 6; i++ )
        cin >> a[i];
    cin >> n; 
    for ( int i = 0; i < n; i++ )
    {
        cin >> s[i]; 
        for ( int j = 0; j < 6; j++ )
        if ( s[i] == as[j] ) a[j]--;
    }
    for ( int i = 0; i < 6; i++ )
    if ( a[i] < 0 ) return(cout << "NO\n", 0);
    for ( int t = 0; t < 5; t++ )
        for ( int i = 0; i < n; i++ )
            if ( s[i] == cmp[t] )
                if ( a[t] > 0 )
                    a[t]--, s[i] = as[t];
                else if ( a[t + 1] > 0 ) 
                    a[t + 1]--, s[i] = as[t + 1];
                else return(cout << "NO\n", 0);
    cout << "YES\n"; 
    for ( int i = 0; i < n; i++ )
        cout << s[i] << '\n';
}
```
    - **核心思想**：先遍历输入的参与者需求，将只选一种尺码的人对应的尺码数量减去。检查此时各尺码数量是否足够，若不足则输出NO。然后对于有两种相邻尺码选择的人，按顺序优先选择较小尺码，若小尺码不够则选大尺码，若都不够则输出NO，最后输出分配方案。
- **Erica_N_Contina（4星）**
    - **关键亮点**：代码结构清晰，使用结构体存储有两种选择的参与者信息，并通过排序和贪心策略进行分配。
    - **核心代码**：
```cpp
struct node{
    int a,b,id;
}p[N];
int tot;
int ans[N];
int c[N],n;
void cal(string s,int id,int f,int idx){
    for(int i=0;i<6;i++){
        if(ds[i]==s){
            if(f==1)p[id].a=i,p[id].id=idx;
            if(f==2)p[id].b=i,p[id].id=idx;
            if(!f){
                ans[idx]=i;
                c[i]--;
                if(c[i]<0){
                    cout<<"NO"<<endl;
                    exit(0);
                }
                return ;
            }
        }
    }
}
bool cmp(node a,node b){
    return a.a<b.a;
}

signed main(){
    for(int i=0;i<6;i++)c[i]=rd;
    n=rd;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        int pos=s.find(",",0);
        if(pos==EOF){
            cal(s,0,0,i);
        }else{
            cal(s.substr(0,pos),++tot,1,i);
            cal(s.substr(pos+1,s.size()-1),tot,2,i);
        }
    }
    sort(p+1,p+tot+1,cmp);
    for(int i=1;i<=tot;i++){
        int a=p[i].a,b=p[i].b,id=p[i].id;
        if(c[a])c[a]--,ans[id]=a;
        else c[b]--,ans[id]=b;
        if(c[b]<0){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        cout<<ds[ans[i]]<<endl;
    }
}
```
    - **核心思想**：定义结构体 `node` 存储有两种选择的参与者的两个尺码及编号。`cal` 函数处理输入的尺码字符串，根据是否有逗号判断是一种尺码还是两种尺码的需求。将有两种选择的参与者按第一个尺码排序，然后依次贪心分配，优先分配小尺码，若小尺码不足则分配大尺码，若大尺码也不足则输出NO，最后输出分配方案。

### 最优关键思路或技巧
对于此类有不同选择情况且需判断可行性和分配方案的问题，先处理确定的选择，再对不确定的选择按一定顺序进行贪心分配是关键思路。这里利用尺码相邻的特点，按从小到大的顺序贪心选择，能有效避免浪费资源，提高分配成功的可能性。

### 拓展
同类型题通常围绕资源分配、任务调度等场景，给定不同的限制条件和选择情况，判断可行性并给出方案。类似算法套路是先处理确定部分，再对不确定部分根据题目特点制定贪心策略，如按某种顺序进行选择或分配。

### 推荐洛谷题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过贪心策略对物品进行分组，考查贪心思想在资源分配场景的应用。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据不同人的接水时间，通过贪心算法找到最优排队方案，与本题思路类似。
- [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：涉及区间分配问题，利用贪心策略判断是否能满足所有需求，与本题在逻辑上有相似之处。

### 个人心得
无。 

---
处理用时：69.92秒