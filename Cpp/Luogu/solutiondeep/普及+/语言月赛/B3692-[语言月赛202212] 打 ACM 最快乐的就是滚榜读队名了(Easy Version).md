# 题目信息

# [语言月赛202212] 打 ACM 最快乐的就是滚榜读队名了(Easy Version)

## 题目背景

**本题与 [I2](https://www.luogu.com.cn/problem/P8890) 的题意完全一致，区别仅在 $m$ 和 $K$ 的范围**。

在刚刚结束的 ICPC 杭州赛站上，某 E 经历了刺激的滚榜。她发现打 ACM 最快乐的就是滚榜读队名了。

## 题目描述

一场 ICPC 正式赛共 $5$ 小时。

队伍的排名由通过题数与罚时决定。通过题数更多的队伍排名更靠前，若通过题数相同，则罚时更小的队伍排名更靠前。通过题数与罚时均相同的队伍排名相同。本题中可能出现队伍排名相同的情况，此时，认为先出现在提交记录中的队伍排名靠前。

罚时是由通过题目的时间和未通过提交的次数决定的。罚时为每一道题通过时比赛开始的分钟数之和，加上该题之前未通过提交的次数乘 $20$ 分钟得到的。例如，某队在比赛进行 $1:28:35$ 时通过了 G 题，在此之前共有 $3$ 次未通过的提交，则 G 题对罚时的总贡献为 $88+3 \times 20=148$ 分钟。

**需要注意的是，仅有通过的试题的未通过提交会被计算罚时**。例如，某队在 I 题共有 $14$ 次未通过的提交，但到比赛结束，该队都没有通过 I 题，则这 $14$ 次未通过的提交不会被计算罚时。**在某一题通过后，该队对这一题的任何提交（无论是否能够通过）都不会影响本题通过的结果和本题的罚时。**

选手在比赛过程中可以随时提交某一道试题的代码，代码将被立即评测并返回结果（$\texttt{Accepted}$，$\texttt{Time Limit Exceeded}$，$\texttt{Memory Limit Exceeded}$，$\texttt{Presentation Error}$，$\texttt{Wrong Answer}$，$\texttt{Runtime Error}$）。其中，评测结果 $\texttt{Accepted}$ 为通过，其他评测结果均为不通过。

在比赛进行的前四小时（$0:00:00 \sim 4:00:00$），每支队伍的提交均会在排行榜上反映出来。比赛的最后一小时（$4:00:01 \sim 5:00:00$），排行榜将被冻结（封榜），所有的提交在排行榜对应队伍对应试题上均显示为待判题（提交的队伍知道评测结果）。

在比赛结束后，会进行紧张刺激的滚榜环节。滚榜嘉宾将按照封榜时的排行榜，依照从最后一名到第一名，**先读出队伍队名**，再按照从 A 题依次到最后一题的顺序，公布排行榜上该队“待判题”状态试题最终是否通过。

如果通过，所有队伍的排名将立即重新计算，显然，已经滚榜完成（被滚榜嘉宾念过队名，且所有待判题状态的结果都已经揭晓）的队伍排名不会有影响。若该队伍排名上升，则滚榜嘉宾立即开始下一支队伍的滚榜。因此，一支队伍的队名可能被滚榜嘉宾多次读出。

例如，某队队名为“囤题”，在前四小时没有通过任何一题，封榜时排在最后一名。在封榜后，该队连续通过全部十三道题目。那么滚榜嘉宾有可能读到该队队名七八次。当然，当该队上升到第一名后，其排名不会再发生变化，即使揭晓的判题结果为通过，但其排名没有发生变化，滚榜嘉宾不会再次读出其队名。

现在给出某场 ICPC 完整的提交记录，请你依次输出滚榜嘉宾念出的队名。

**一次提交记录都没有的队伍不会在排行榜上出现，也不会在滚榜中被念到队名。**

## 说明/提示

### 样例解释

在封榜前，队伍 $\texttt{abc}$ 仅通过 $\texttt{A}$ 题，且在第二秒的第一次正确提交之前有一次错误提交，因此罚时为 $20$ 分钟；队伍 $\texttt{bcd}$ 同样仅通过 $\texttt{A}$ 题，且在 $0:19:38$ 的第一次正确提交之前没有错误提交，因此罚时为 $19$ 分钟。

在封榜后，队伍 $\texttt{abc}$ 通过了 $\texttt{B}$ 题。

在滚榜环节开始，由于封榜后的提交未被揭晓，因此暂时认为队伍 $\texttt{abc}$ 与 $\texttt{bcd}$ 均只通过一题，且前者罚时较大，排名靠后。

依照从最后一名到第一名的原则，队伍 $\texttt{abc}$ 的名字先被念到，并揭晓其在封榜后的提交的结果。其通过了 $\texttt{B}$ 题，因此其通过题数被更新为 $2$，罚时同样被更新。同时，所有队伍的排名立即被重新计算。由于此时 $\texttt{abc}$ 通过题目数量大于 $\texttt{bcd}$，因此其排名重新计算为第一名，而 $\texttt{bcd}$ 成为最后一名第二名。

这之后，队伍 $\texttt{bcd}$ 的名字被念到，由于其在封榜后没有提交，因此这时所有队伍的排名没有变化，滚榜嘉宾会进行其上一名队伍的滚榜。

最后，队伍 $\texttt{abc}$ 的名字被念到，滚榜结束。

需要注意的是，在滚榜过程中是逐题揭晓提交。也就是说，如果一支队伍封榜后通过了多道题，在其进行滚榜过程中，只要按照从 $\texttt{A}$ 题依次到最后一题的顺序，该队第一个“待判题”状态试题通过，后面的“待判题”同样暂时不会揭晓，而是立刻进行排名更新过程以及可能存在的更换另一支队伍进行滚榜的过程。

### 数据规模与约定

- 对于 $30\%$ 的数据，$n = 1$；
- 对于另外 $10\%$ 的数据，$m = 1$；
- 对于 $100\%$ 的数据，$1 \le n \le 20$，$1 \le m \le 1000$，$1 \le K \le 10^4$，$0 \leq x \leq 5$，$00 \leq yy < 60$，$00 \leq zz < 60$，且当 $x = 5$ 时保证 $yy = zz = 00$。

保证提交记录按照提交时间不降序给出，即先给出的提交记录提交时间不会晚于后给出的提交记录的提交时间，试题名称为大写字母 $\texttt{A} \sim \texttt{Z}$，队名均为长度不超过 $50$ 的由小写字母组成的字符串，评测状态为试题中所给的 $6$ 种之一。

## 样例 #1

### 输入

```
2 2 4
0:00:01 A abc Wrong Answer
0:00:02 A abc Accepted
0:19:38 A bcd Accepted
4:18:22 B abc Accepted```

### 输出

```
abc
bcd
abc
```

# AI分析结果

### 综合分析与结论
这些题解均围绕 ICPC 比赛滚榜过程的模拟展开。思路上，先处理提交记录，区分封榜前后情况，计算各队通过题数、罚时等信息，再按规则进行滚榜模拟。算法要点在于合理使用数据结构存储队伍信息，如结构体、优先队列等，并按题目要求重载比较运算符。解决难点主要是理清复杂的排名规则和滚榜逻辑，处理封榜前后提交记录对罚时、通过题数计算的影响，以及避免各种细节错误。

从质量上看，多数题解思路较清晰，但在代码可读性、优化程度上存在差异。部分题解使用优先队列优化动态排序，提高效率；部分题解虽实现功能，但采用的算法或数据结构相对低效。

### 所选的题解
- **作者：Milthm (5星)**
    - **关键亮点**：思路清晰，代码不仅能通过本题，还可通过加强版。详细阐述题意理解，对每个步骤的实现有清晰注释。使用结构体全面存储队伍各类信息，利用优先队列维护滚榜过程，通过重载运算符实现排名规则。
    - **个人心得**：调试困难，提供调试样例。
    - **核心代码片段**：
```cpp
struct node{
    int sc,id,time;string name;
    bool ac[25]={0};int WA[25]={0};
    bool fbac[25]={0};int fbWA[25]={0};int fbti[25]={0};
}a[200005];
bool operator<(const node& b)const{
    if(sc!=b.sc)return sc>b.sc;
    if(time!=b.time)return time<b.time;
    return id<b.id;
}
while(!q.empty()){
    if(q.size()==1){
        cout<<q.top().name<<'\n';
        break;
    }
    node c1=q.top();q.pop();
    node c2=q.top();q.pop();
    cout<<c1.name<<'\n';
    for(int i=0;i<n;++i){
        if(c1.fbac[i]){
            c1.time+=(c1.fbWA[i]+c1.WA[i])*20+c1.fbti[i];
            c1.fbac[i]=0;
            c1.ac[i]=1;
            c1.sc++;
            if(c1<c2){
                q.push(c1);q.push(c2);goto R;
            }
        }
    }
    q.push(c2);
    R:;
}
```
    - **核心实现思想**：定义结构体 `node` 存储队伍信息，重载 `<` 运算符实现排名规则。在滚榜循环中，每次取出队首两个元素（倒数第一和倒数第二），处理倒数第一的封榜后通过题目，更新罚时和通过题数，若排名上升则重新加入优先队列。
- **作者：T_TLucas_Yin (4星)**
    - **关键亮点**：简洁明了地阐述题意和解题思路，突出优先队列在处理动态排序问题中的应用。代码注释详细，变量命名有一定意义，便于理解。
    - **核心代码片段**：
```cpp
struct node{
    string name;
    int x,k,tim;
    bool operator <(const node &b) const{
        if(x!=b.x) return x>b.x;
        else if(tim!=b.tim) return tim<b.tim;
        else return k<b.k;
    }
}a[1005];
priority_queue<node> q;
while(t--){
    char c;
    bool flag;
    int h,mi,s,q;
    string nam,st;
    scanf("%d:%d:%d %c",&h,&mi,&s,&c);
    q=c-'A'+1;
    cin>>nam;
    getline(cin,st);
    if(h>4||(h==4&&(mi||s))) flag=1;
    else flag=0;
    if(!ma.count(nam)) ma[nam]=++top,a[top].name=nam,a[top].k=top;
    if(f1[ma[nam]][q]) continue;
    if(st==" Accepted"){
        if(!flag) f1[ma[nam]][q]=-1,a[ma[nam]].x++,a[ma[nam]].tim+=fashi(h,mi)+f2[ma[nam]][q]*20;
        else f1[ma[nam]][q]=fashi(h,mi);
    }
    else f2[ma[nam]][q]++;
}
for(int i=1;i<=top;i++) q.push(a[i]);
while(q.size()>1){
    node t1=q.top();q.pop();
    cout<<t1.name<<"\n";
    node t2=q.top();q.pop();
    for(int i=1;i<=n;i++){
        if(f1[t1.k][i]>0){
            t1.x++,t1.tim+=f1[t1.k][i]+f2[t1.k][i]*20,f1[t1.k][i]=-1;
            if(t1<t2){ q.push(t1);break; }
        }
    }
    q.push(t2);
}
cout<<q.top().name;
```
    - **核心实现思想**：定义 `node` 结构体存储队伍信息并重载 `<` 运算符。读入提交记录时，区分封榜前后，更新队伍通过题目情况和罚时。将所有队伍加入优先队列，在滚榜循环中，取出队首两个元素，处理倒数第一的封榜后通过题目，更新信息并判断是否需要重新加入队列。
- **作者：Zhou_yu (4星)**
    - **关键亮点**：详细梳理思路和坑点，对理解题意和避免错误有很大帮助。采用优先队列实现动态排序，代码结构清晰，对每个步骤的实现有较好注释。
    - **个人心得**：强调本题逻辑要求高，自己多次尝试才 AC，整理出坑点清单。
    - **核心代码片段**：
```cpp
struct node
{
    string name;
    int penalty;
    int ACpass;
    int id;
    bool operator <(const node &b) const
    {
        if(ACpass==b.ACpass)
        {
            if(penalty==b.penalty)
            return id<b.id;
            return penalty<b.penalty;
        }
        return ACpass>b.ACpass;
    }
}team[1005];
unordered_map<string,int> book;
int cnt;
int List[1005][25];
int List2[1005][25];
priority_queue<node> q;
while(k--)
{
    int x,y,z;
    char ch;
    string name;
    char isAC;
    string rubbish;
    scanf("%d:%d:%d %c",&x,&y,&z,&ch);
    int Qi=ch-'A'+1;
    cin>>name;
    isAC=getchar();
    isAC=getchar();
    getline(cin,rubbish);
    if(!book.count(name))
    {
        book[name]=++cnt;
        team[cnt].name=name;
        team[cnt].id=cnt;
    }
    int id=book[name];
    if(!List2[id][Qi]&&List[id][Qi]!=-1)
    {
        if(isAC=='A')
        {
            if(x>4||(x==4&&z+y>0))List2[id][Qi]=x*60+y;
            else
            {
                team[id].ACpass++;//封榜前的AC
                team[id].penalty+=(x*60+y+List[id][Qi]*20);
                List[id][Qi]=-1;
            }
        }
        else List[id][Qi]++;
    }
}
for(int i=1;i<=cnt;i++)q.push(team[i]);
while(!q.empty())
{
    node now=q.top();
    q.pop();
    cout<<now.name<<'\n';
    if(q.empty())break;
    node nxt=q.top();
    q.pop();
    for(int i=1;i<=n;i++)
    if(List2[now.id][i]&&List[now.id][i]!=-1)
    {
        now.ACpass++;
        now.penalty+=List2[now.id][i]+List[now.id][i]*20;
        List[now.id][i]=-1;
        if(now<nxt)
        {q.push(now);break;}
    }
    q.push(nxt);
}
```
    - **核心实现思想**：定义 `node` 结构体存储队伍信息并重载 `<` 运算符。通过 `book` 记录队伍出现顺序，`List` 和 `List2` 分别记录封榜前题目情况和封榜后通过题目时间。读入提交记录，区分封榜前后更新队伍信息。将队伍加入优先队列，在滚榜循环中，取出队首两个元素，处理倒数第一的封榜后通过题目，更新信息并判断是否重新加入队列。

### 最优关键思路或技巧
- **数据结构选择**：使用结构体存储队伍的各种信息，如通过题数、罚时、每道题的提交情况等，使数据组织清晰。优先队列用于维护动态排名，每次操作时间复杂度为 $O(\log n)$，高效处理滚榜过程中队伍排名的变化。
- **重载运算符**：在结构体中按照题目排名规则重载小于运算符，方便优先队列自动根据规则进行排序，简化代码实现。
- **细致处理提交记录**：区分封榜前后的提交记录，分别计算罚时和通过题数，在滚榜时再处理封榜后提交记录对排名的影响，确保计算准确。

### 可拓展之处
此类题目属于复杂模拟类型，相似算法套路是先梳理清楚复杂的业务逻辑，然后选择合适的数据结构存储和操作数据。同类型题可能会在比赛规则、数据规模、条件判断等方面进行变化，例如改变排名规则、增加比赛阶段、扩大数据范围等。解题时需耐心分析题意，设计合理的数据结构和算法实现。

### 相似知识点洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及数据的组合与判断，需按一定规则处理数据，与本题处理提交记录并按规则计算排名有相似之处。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：通过模拟图形的填充过程，考察对复杂逻辑的实现和数据处理能力，与本题模拟滚榜过程类似。
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：利用队列实现广度优先搜索，处理数据的动态变化，与本题使用优先队列处理动态排名有相似的数据结构应用思路。

### 个人心得摘录与总结
- **Milthm**：调试过程困难，提供调试样例帮助理解。总结为复杂模拟题调试难度大，可通过准备调试样例辅助排查问题。
- **Zhou_yu**：做题思路需清晰，逻辑功底要求高，整理出多个坑点。表明此类复杂模拟题细节多，需仔细分析题意，梳理可能的特殊情况和易错点。 

---
处理用时：102.51秒