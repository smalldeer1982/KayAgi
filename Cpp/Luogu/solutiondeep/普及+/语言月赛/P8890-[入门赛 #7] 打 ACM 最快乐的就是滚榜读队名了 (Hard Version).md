# 题目信息

# [入门赛 #7] 打 ACM 最快乐的就是滚榜读队名了 (Hard Version)

## 题目背景

**本题的题意与 [I1](https://www.luogu.com.cn/problem/B3692) 完全相同，区别仅在 $m$ 和 $K$ 的范围。**

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

对于 $100\%$ 的数据，$1 \le n \le 20$，$1 \le m \le 2 \times 10^5$，$1 \le K \le 2 \times 10^6$，$0 \leq x \leq 5$，$00 \leq yy < 60$，$00 \leq zz < 60$，且当 $x = 5$ 时保证 $yy = zz = 00$。

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
这些题解的核心思路均为模拟滚榜过程，算法要点包括对队伍信息和提交记录的处理，以及使用优先队列维护动态排名。解决难点主要在于理清复杂的规则，如罚时计算、封榜前后处理、滚榜机制等。不同题解在实现细节上各有差异，如数据结构的使用、代码语法等。

### 所选的题解
- **作者：chen_zhe（5星）**
    - **关键亮点**：代码结构清晰，利用结构体打包队伍信息，使用 `unordered_map` 存储队名，结构化绑定简化代码。优先队列结合 lambda 表达式排序，优化模拟过程。
    - **个人心得**：提到半小时写完后挂了一些细节，调了一段时间，因 `f` 数组开 `unordered_map` 造成偏大常数 TLE。
    - **核心代码片段**：
```cpp
struct team {
    int ac,ftime,id;
    int f[26];
    string tname;
    vector <Event> r;
    bool operator < (const team &rhs) const {
        if (ac!=rhs.ac)
            return ac<rhs.ac;
        else if (ftime!=rhs.ftime)
            return ftime>rhs.ftime;
        else
            return id>rhs.id;
    }
    bool operator > (const team &rhs) const {
        if (ac!=rhs.ac)
            return ac>rhs.ac;
        else if (ftime!=rhs.ftime)
            return ftime<rhs.ftime;
        else
            return id<rhs.id;
    }
};
struct Event {
    int time,status,id;
    char p;
    string name;
};
for (auto [time,ok,id,p,name] : e) {
    if (time<=240*60) {
        if (!t.count(name)) {
            t[name].tname=name;
            t[name].id=id;
        }
        if (ok==1) {
            auto &[ac,ftime,id,f,tname,r]=t[name];
            if (f[p]==K+1)
                continue;
            ftime+=f[p]*20*60+time/60*60;
            ac++;
            f[p]=K+1;
        }
        else {
            auto &[ac,ftime,id,f,tname,r]=t[name];
            if (f[p]==K+1)
                continue;
            f[p]++;
        }
    } else {
        if (t.count(name)==0) {
            t[name].tname=name;
            t[name].id=id;
        }
        t[name].r.push_back({time,ok,id,p,name});
    }
}
for (auto [fir,sec]:t)
    t2.push_back(sec);
stable_sort(t2.begin(),t2.end());
for (auto &v:t2) {
    auto &t=v.r;
    sort(t.begin(),t.end(),[](auto a,auto b) {
        return a.p<b.p;
    });
    q.push(v);
}
while (!q.empty()) {
    auto st1=q.top();
    auto &[ac,ftime,id,f,tname,r]=st1;
    q.pop();
    cout << tname << " ";
    cout << "\n";
    if (q.empty())
        break;
    if (r.empty())
        continue;
    auto st2=q.top();
    size_t it=(itmap.count(tname)?itmap.at(tname):0);
    for (;it<r.size() && st1<st2;it++) {
        auto [time,status,tid,p,name]=r[it];
        if (!t.count(name)) {
            t[name].tname=name;
            t[name].id=tid;
        }
        if (f[p]==K+1)
            continue;
        if (status==0)
            f[p]++;
        else {
            ac++;
            ftime+=f[p]*20*60+time/60*60;
            f[p]=K+1;
        }
    }
    itmap[tname]=--it;
    if (st1>st2)
        q.push(st1);
}
```
    - **核心实现思想**：定义 `team` 结构体存储队伍信息，`Event` 结构体存储提交记录。通过遍历提交记录，区分封榜前后处理队伍信息。最后将队伍放入优先队列，在滚榜循环中，从优先队列取队首队伍，更新其封榜后提交信息，判断排名变化决定是否重新入队。

- **作者：_•́へ•́╬_（4星）**
    - **关键亮点**：使用数组维护队伍过题和罚时情况，哈希解决队名到编号映射，代码语法较为基础，适合初学者理解。
    - **个人心得**：提到 `ao` 和 `o` 哈希冲突调了一周。
    - **核心代码片段**：
```cpp
int n,nn,m,p,qwq[M][2],sta1[M][N],pos[M];bool sta2[M][N];
unordered_map<ull,int>mmp;ull hsh;char name[M][55],tmp[55];
struct cmp {
    inline bool operator()(const int&x,const int&y) {
        if(qwq[x][0]^qwq[y][0])return qwq[x][0]>qwq[y][0];
        if(qwq[x][1]^qwq[y][1])return qwq[x][1]<qwq[y][1];
        return x<y;
    }
}pwp;
priority_queue<int,vector<int>,cmp>q;
main() {
    read(n);read(m);read(p);
    for(int t1,t2,t3,i,j,k;p--;) {
        read(t1);read(t2);read(t3);j=nc()-'A';nc();hsh=0;k=0;
        for(char c;c=nc(),'a'<=c&&c<='z';hsh=hsh*b+c-'a'+1,tmp[k++]=c);
        if(!mmp.count(hsh))
            i=mmp[hsh]=nn++,tmp[k]=0,sprintf(name[i],"%s",tmp);
        else i=mmp[hsh];
        if(sta2[i][j])continue;
        if(t1<4||(t1==4&&!t2&&!t3))
            if(nc()^'A')++sta1[i][j];
            else {
                ++qwq[i][0];qwq[i][1]+=t1*60+t2+sta1[i][j]*20;
                sta1[i][j]=-1;sta2[i][j]=1;
            }
        else if(nc()^'A')++sta1[i][j];
            else sta1[i][j]=t1*60+t2+sta1[i][j]*20,sta2[i][j]=1;
    }
    for(int i=0;i<nn;q.emplace(i++));
    for(int i;q.size();) {
        i=q.top();q.pop();
        for(char*j=name[i];*j;pc(*j++));pc('\n');
        if(q.empty())break;
        for(int&j=pos[i];j<n;++j)if(~sta1[i][j]&&sta2[i][j]) {
            ++qwq[i][0];qwq[i][1]+=sta1[i][j];sta1[i][j]=-1;
            if(!pwp(q.top(),i)){q.emplace(i);break;}
        }
    }
    pc(0);
}
```
    - **核心实现思想**：用 `qwq` 数组记录队伍过题数和罚时，`sta1` 和 `sta2` 数组记录题目状态。读入提交记录，根据时间和提交结果更新队伍和题目状态。将所有队伍入大根堆，在滚榜循环中，从堆顶取队伍，更新封榜后通过题目信息，判断排名变化决定是否重新入堆。

- **作者：Zhou_yu（4星）**
    - **关键亮点**：详细梳理思路和坑点，代码逻辑清晰，使用 `unordered_map` 存储队伍信息，优先队列维护滚榜排名。
    - **个人心得**：提到自己底子差，十次才 AC，强调了本题对逻辑功底的考验。
    - **核心代码片段**：
```cpp
struct node {
    string name;
    int penalty;
    int ACpass;
    int id;
    bool operator <(const node &b) const {
        if(ACpass==b.ACpass) {
            if(penalty==b.penalty)
                return id<b.id;
            return penalty<b.penalty;
        }
        return ACpass>b.ACpass;
    }
}team[200005];
unordered_map<string,int> book;
int cnt;
int List[200005][25];
int List2[200005][25];
priority_queue<node> q;
int main() {
    int n,m,k;
    cin>>n>>m>>k;
    while(k--) {
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
        if(!book.count(name)) {
            book[name]=++cnt;
            team[cnt].name=name;
            team[cnt].id=cnt;
        }
        int id=book[name];
        if(!List2[id][Qi]&&List[id][Qi]!=-1) {
            if(isAC=='A') {
                if(x>4||(x==4&&z+y>0))List2[id][Qi]=x*60+y;
                else {
                    team[id].ACpass++;
                    team[id].penalty+=(x*60+y+List[id][Qi]*20);
                    List[id][Qi]=-1;
                }
            }
            else List[id][Qi]++;
        }
    }
    for(int i=1;i<=cnt;i++)q.push(team[i]);
    while(!q.empty()) {
        node now=q.top();
        q.pop();
        cout<<now.name<<'\n';
        if(q.empty())break;
        node nxt=q.top();
        q.pop();
        for(int i=1;i<=n;i++)
            if(List2[now.id][i]&&List[now.id][i]!=-1) {
                now.ACpass++;
                now.penalty+=List2[now.id][i]+List[now.id][i]*20;
                List[now.id][i]=-1;
                if(now<nxt) {
                    q.push(now);break;
                }
            }
        q.push(nxt);
    }
    return 0;
}
```
    - **核心实现思想**：定义 `node` 结构体存储队伍信息，`List` 数组记录封榜前题目错误情况和正确情况，`List2` 记录封榜后题目通过时间。读入提交记录，更新队伍和题目信息。将队伍入优先队列，在滚榜循环中，取队首队伍，更新封榜后通过题目信息，判断排名变化决定是否重新入队。

### 最优关键思路或技巧
- **数据结构选择**：使用 `unordered_map` 存储队名与队伍编号映射，高效查询队伍。用优先队列维护滚榜排名，每次更新队伍信息后，优先队列自动调整顺序，符合滚榜动态变化特点。
- **代码实现技巧**：如使用结构化绑定简化代码，像 `chen_zhe` 的题解中利用结构化绑定快速获取结构体成员。合理设计结构体和数组存储信息，使代码逻辑清晰，如不同题解中对队伍信息、题目状态、提交记录等的存储设计。

### 可拓展之处
此类模拟题常考察对复杂规则的理解与实现，类似算法套路包括仔细梳理题目流程，分阶段处理数据（如本题封榜前后），用合适数据结构优化操作。同类型题可涉及比赛排名、任务调度等场景，关键在于明确各阶段规则和数据变化。

### 相似知识点洛谷题目
- **P1031 均分纸牌**：通过模拟纸牌移动过程，考察对问题的分析和模拟实现能力。
- **P1449 后缀表达式**：模拟后缀表达式计算过程，涉及栈的应用和模拟运算规则。
- **P1908 逆序对**：通过归并排序或树状数组等方法模拟统计逆序对，考察算法实现与模拟结合。

### 个人心得摘录与总结
- **chen_zhe**：半小时写完代码后因细节问题调试一段时间，且因 `f` 数组使用 `unordered_map` 导致常数过大 TLE。总结出写代码要注重细节，选择合适数据结构避免性能问题。
- **_•́へ•́╬_**：因 `ao` 和 `o` 哈希冲突调试一周，强调哈希实现时要注意冲突处理，确保映射准确性。
- **Zhou_yu**：自身因逻辑功底不足，多次提交才 AC，突出本题对逻辑思维要求高，做题时需思路清晰，全面考虑各种情况。 

---
处理用时：116.77秒