# 题目信息

# Coach

## 题目描述

A programming coach has $ n $ students to teach. We know that $ n $ is divisible by $ 3 $ . Let's assume that all students are numbered from $ 1 $ to $ n $ , inclusive.

Before the university programming championship the coach wants to split all students into groups of three. For some pairs of students we know that they want to be on the same team. Besides, if the $ i $ -th student wants to be on the same team with the $ j $ -th one, then the $ j $ -th student wants to be on the same team with the $ i $ -th one. The coach wants the teams to show good results, so he wants the following condition to hold: if the $ i $ -th student wants to be on the same team with the $ j $ -th, then the $ i $ -th and the $ j $ -th students must be on the same team. Also, it is obvious that each student must be on exactly one team.

Help the coach and divide the teams the way he wants.

## 样例 #1

### 输入

```
3 0
```

### 输出

```
3 2 1 
```

## 样例 #2

### 输入

```
6 4
1 2
2 3
3 4
5 6
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
3 2 1 
```

# AI分析结果

### 题目内容
# 教练

## 题目描述
一位编程教练有 $n$ 个学生要教。已知 $n$ 能被 $3$ 整除。假设所有学生从 $1$ 到 $n$ 编号（包括 $1$ 和 $n$）。

在大学编程锦标赛之前，教练想把所有学生分成三人一组。对于一些学生对，我们知道他们想在同一队。此外，如果第 $i$ 个学生想和第 $j$ 个学生在同一队，那么第 $j$ 个学生也想和第 $i$ 个学生在同一队。教练希望团队能取得好成绩，所以他希望满足以下条件：如果第 $i$ 个学生想和第 $j$ 个学生在同一队，那么第 $i$ 个和第 $j$ 个学生必须在同一队。而且，显然每个学生必须恰好加入一个队。

帮助教练按照他的要求进行分组。

## 样例 #1
### 输入
```
3 0
```
### 输出
```
3 2 1 
```

## 样例 #2
### 输入
```
6 4
1 2
2 3
3 4
5 6
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
3 3
1 2
2 3
1 3
```
### 输出
```
3 2 1 
```

### 算法分类
并查集

### 综合分析与结论
这些题解均围绕并查集算法解决问题，核心思路是利用并查集处理学生间的组队关系。各题解的主要差异在于对并查集结果的处理方式，特别是处理人数小于3的组如何凑成三人组的逻辑。难点在于如何确保所有学生都能合理分组，避免出现无解情况，如人数大于3的组或无法凑齐三人组的情况。

### 所选的题解
- **作者：lava__44 (4星)**
    - **关键亮点**：思路清晰，详细分析了无解情况和合法情况下的不同分组情形，代码实现直接且易理解。
    - **个人心得**：提到调试花费时间，甚至重构代码，强调对并查集的喜爱。
    - **核心代码**：
```c++
int find(int x){
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        int fau=find(u),fav=find(v);
        fa[fau]=fav;
    }
    for(int i=1;i<=n;i++) ton[find(i)]++;
    for(int i=1;i<=n;i++){
        if(ton[fa[i]]>=4){
            cout<<-1;
            return 0;
        }
        q[fa[i]].push(i);
        if(!Vis[fa[i]]){
            Vis[fa[i]]=1;
            num[++cnt]=fa[i];
        }
        akali[fa[i]]++;
    }
    for(int i=1;i<=cnt;i++){/*处理 2+1 的情况*/
        if(akali[num[i]]==2){
            for(int j=1;j<=cnt;j++){
                if(i==j) continue;
                if(akali[num[j]]==1){
                    akali[num[j]]=0;
                    q[num[i]].push(num[j]);
                    fa[num[j]]=num[i];
                    break;
                }
            }
        }
    }
    for(int i=1;i<=cnt;i++){/*处理 1+1+1 的情况*/
        if(akali[num[i]]==1){
            for(int j=i+1;j<=cnt;j++){
                if(akali[num[j]]==1){
                    akali[num[j]]=0;
                    q[num[i]].push(num[j]);
                    fa[num[j]]=num[i];
                    for(int k=1+j;k<=cnt;k++){
                        if(akali[num[k]]==1){
                            akali[num[k]]=0;
                            q[num[i]].push(num[k]);
                            fa[num[k]]=num[i];
                            break;
                        }
                    }
                    break;
                }
            }
            akali[num[i]]=3;
        }
    }
    for(int i=1;i<=n;i++){
        if(q[fa[i]].size()!=3){/*若有不能成组的则无解*/
            cout<<-1;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[fa[i]]){
            vis[fa[i]]=1;
            while(!q[fa[i]].empty()){
                cout<<q[fa[i]].front()<<" "; q[fa[i]].pop();
            }
            cout<<"\n";
        }
    }
    return 0;
}
```
    - **核心思想**：先通过并查集合并有组队意愿的学生，统计每个集合人数判断是否有大于4人的不合法情况。之后分别处理2 + 1和1 + 1 + 1的合法组队情况，最后检查是否所有组都为3人，若满足则输出分组。
- **作者：wuyixiang (4星)**
    - **关键亮点**：代码简洁明了，通过数组记录每组人数及编号，直接判断不同人数组的组合情况。
    - **核心代码**：
```c++
int find(int x)//并查集
{
    if(f[x] == x)return x;
    else return f[x] = find(f[x]);
}
int main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i ++)f[i] = i;
    for(int i = 1;i <= m;i ++)
    {
        cin >> x >> y;
        int w = find(x),w2 = find(y);
        if(w!= w2)f[w] = w2;
    }
    for(int i = 1;i <= n;i ++)b[find(i)][++qo[find(i)]] = i;//记录人数及编号
    for(int i = 1;i <= n;i ++)
    {
        if(qo[i] == 0)continue;
        else if(qo[i] == 3)ans[++cnt][1] = b[i][1],ans[cnt][2] = b[i][2],ans[cnt][3] = b[i][3];//三人组，独立成队
        else if(qo[i] == 2)
        {
            if(cnt3)ans[++cnt][1] = b[i][1],ans[cnt][2] = b[i][2],ans[cnt][3] = liedui2[cnt3],cnt3 --;
            else liedui1[++cnt2][1] = b[i][1],liedui1[cnt2][2] = b[i][2];
        }//两人组，如果有一人组，直接合成三人组；否则进入队列等待一人组
        else if(qo[i] == 1)
        {
            if(cnt2)ans[++cnt][1] = b[i][1],ans[cnt][2] = liedui1[cnt2][1],ans[cnt][3] = liedui1[cnt2][2],cnt2 --;
            else liedui2[++cnt3] = b[i][1];
        }//一人组。如果有两人组直接合成三人组，否则进入队列等待两人组
    }
    while(cnt3 >= 3)ans[++cnt][1] = liedui2[cnt3--],ans[cnt][2] = liedui2[cnt3--],ans[cnt][3] = liedui2[cnt3--];//可以三个一人组合成三人组
    if(cnt!= n / 3)cout << -1;//如果没有n/3个三人组，不满足条件
    else
        for(int i = 1;i <= n / 3;i ++)cout << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;//否则输出答案
}
```
    - **核心思想**：利用并查集合并学生关系后，通过数组 `b` 记录每组学生编号，`qo` 记录每组人数。按人数为3、2、1的顺序处理分组情况，最后判断是否能分成 $n/3$ 个三人组，是则输出分组。
- **作者：EdenSky (4星)**
    - **关键亮点**：代码结构清晰，利用 `vector` 存储并查集的节点，通过不同 `vector` 分别处理不同人数的组，逻辑明确。
    - **核心代码**：
```c++
int ufs[20000];
void init(){
    for(int i=1;i<=n;i++) ufs[i]=i;
}
int fd(int x){
    if(ufs[x]==x)	return x;
    return ufs[x]=fd(ufs[x]);
}
void uoin(int x,int y){
    ufs[fd(x)]=fd(y);
}
int main(){
    cin>>n>>m,init();
    int a,b;
    for(int i=1;i<=m;i++)	cin>>a>>b,uoin(a,b);
    for(int i=1;i<=n;i++)	s[fd(i)].pb(i);
    for(auto &i: s)
        if(i.size()>3)	cout<<-1,exit(0);
        else if(i.size()==3)	ans.pb(i);
        else if(i.size()==2)	so.pb(i);
        else if(i.size()==1)	sj.pb(i);
    while(!sj.empty()&&!so.empty())
        sj.front().insert(sj.front().begin(),
            so.front().begin(),so.front().end()),
        so.erase(so.begin()),
        ans.pb(sj.front()),
        sj.erase(sj.begin());
    if(so.size()>0)	cout<<-1,exit(0);
    while(!sj.empty()&&sj.size()>=3){
        int a,b,c;
        auto i=sj.begin();
        a=i->front(),i=sj.erase(i),
        b=i->front(),i=sj.erase(i),
        c=i->front(),i=sj.erase(i);
        ans.push_back({a,b,c});
    }
    if(sj.size()>0)	cout<<-1,exit(0);
    for(auto &i: ans){
        for(auto &j: i)
            cout<<j<<' ';
        cout<<'\n';
    }
}
```
    - **核心思想**：先使用并查集处理学生关系，用 `vector` `s` 存储每个集合的节点，判断是否有大于3个节点的集合，若有则无解。之后将人数为3、2、1的集合分别存入 `ans`、`so`、`sj` 中，先合并 `sj` 和 `so` 中的组，再处理 `sj` 中剩余元素，最后判断 `so` 和 `sj` 是否为空，均空则输出分组。

### 最优关键思路或技巧
利用并查集快速合并有组队意愿的学生，通过统计每个集合的人数来判断是否存在不合法分组（人数大于3）。对于合法情况，根据集合人数为1、2、3的不同情况，采用不同策略进行组合，如两人组与一人组结合，三个一人组结合等，确保所有学生能组成三人组。

### 可拓展之处
此类题目属于并查集应用的经典题型，类似题目常考察如何利用并查集处理元素间的关系，并根据特定条件进行分组或判断可行性。常见的拓展方向包括改变分组人数要求、增加更复杂的限制条件等。

### 相似知识点洛谷题目
- [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：同样利用并查集判断亲戚关系，核心在于通过并查集合并有亲属关系的人，最后查询不同人是否在同一集合判断是否为亲戚。
- [P1197 星球大战](https://www.luogu.com.cn/problem/P1197)：结合并查集与图论，通过并查集维护星球间的连通性，在动态删除星球的过程中利用并查集判断连通块数量的变化。
- [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：基础的并查集模板题，通过并查集实现元素的合并与查询操作，可作为并查集学习的基础练习。 

---
处理用时：105.73秒