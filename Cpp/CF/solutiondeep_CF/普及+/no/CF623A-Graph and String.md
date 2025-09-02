# 题目信息

# Graph and String

## 题目描述

One day student Vasya was sitting on a lecture and mentioned a string $ s_{1}s_{2}...\ s_{n} $ , consisting of letters "a", "b" and "c" that was written on his desk. As the lecture was boring, Vasya decided to complete the picture by composing a graph $ G $ with the following properties:

- $ G $ has exactly $ n $ vertices, numbered from $ 1 $ to $ n $ .
- For all pairs of vertices $ i $ and $ j $ , where $ i≠j $ , there is an edge connecting them if and only if characters $ s_{i} $ and $ s_{j} $ are either equal or neighbouring in the alphabet. That is, letters in pairs "a"-"b" and "b"-"c" are neighbouring, while letters "a"-"c" are not.

Vasya painted the resulting graph near the string and then erased the string. Next day Vasya's friend Petya came to a lecture and found some graph at his desk. He had heard of Vasya's adventure and now he wants to find out whether it could be the original graph $ G $ , painted by Vasya. In order to verify this, Petya needs to know whether there exists a string $ s $ , such that if Vasya used this $ s $ he would produce the given graph $ G $ .

## 说明/提示

In the first sample you are given a graph made of two vertices with an edge between them. So, these vertices can correspond to both the same and adjacent letters. Any of the following strings "aa", "ab", "ba", "bb", "bc", "cb", "cc" meets the graph's conditions.

In the second sample the first vertex is connected to all three other vertices, but these three vertices are not connected with each other. That means that they must correspond to distinct letters that are not adjacent, but that is impossible as there are only two such letters: a and c.

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
Yes
aa
```

## 样例 #2

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
No
```

# AI分析结果

### 题目内容
# 图与字符串

## 题目描述
一天，学生瓦夏坐在课堂上，看到课桌上写着一个由字母“a”、“b”和“c”组成的字符串\(s_{1}s_{2}...\ s_{n}\)。由于课堂很无聊，瓦夏决定通过构建一个图\(G\)来完善这幅“作品”，该图具有以下属性：
- \(G\)恰好有\(n\)个顶点，编号从\(1\)到\(n\)。
- 对于所有顶点\(i\)和\(j\)（\(i≠j\)），当且仅当字符\(s_{i}\)和\(s_{j}\)相等或在字母表中相邻时，它们之间存在一条边。也就是说，“a” - “b”和“b” - “c”这两对字母是相邻的，而“a” - “c”不相邻。

瓦夏在字符串旁边画出了得到的图，然后擦掉了字符串。第二天，瓦夏的朋友佩特亚来上课，在课桌上发现了一个图。他听说了瓦夏的经历，现在他想知道这个图是否可能是瓦夏画的原始图\(G\)。为了验证这一点，佩特亚需要知道是否存在一个字符串\(s\)，使得如果瓦夏使用这个\(s\)，就会生成给定的图\(G\)。

## 说明/提示
在第一个示例中，给定的图由两个顶点和它们之间的一条边组成。所以，这些顶点可以对应相同或相邻的字母。以下任何一个字符串“aa”、“ab”、“ba”、“bb”、“bc”、“cb”、“cc”都符合图的条件。

在第二个示例中，第一个顶点与其他三个顶点都相连，但这三个顶点彼此不相连。这意味着它们必须对应不同且不相邻的字母，但这是不可能的，因为只有两个这样的字母：a 和 c。

## 样例 #1
### 输入
```
2 1
1 2
```
### 输出
```
Yes
aa
```

## 样例 #2
### 输入
```
4 3
1 2
1 3
1 4
```
### 输出
```
No
```

### 算法分类
图论

### 综合分析与结论
这些题解主要围绕如何根据给定图判断是否能构造出符合条件字符串展开。多数题解利用了图中“b与所有点相连，a和c不直接相连”这一特性。部分通过建补图转化为二分图判断问题，部分利用并查集判断连通性及图的结构，还有通过搜索判断连通块情况等。各题解思路差异在于处理图结构和判断可行性的具体方法，有的简洁高效，有的相对复杂。

### 所选的题解
- **作者：珅肐 (赞：5)**
  - **星级**：5星
  - **关键亮点**：思路清晰，巧妙利用补图转化为二分图染色问题求解，代码实现简洁明了，注释详细。
  - **重点代码核心思想**：先读入图并用邻接矩阵存储，构建补图后对补图进行二分图染色，染色失败或a、c在原图中有连边则输出No，否则根据染色结果输出字符串。
  ```cpp
  bool dfs(int x){//二分图染色
      for(int i=head[x];i;i=edge[i].next){
          int to=edge[i].to;
          if(col[to]==col[x])return 0;
          if(~col[to])continue;col[to]=col[x]^1;
          if(!dfs(to))return 0;
      }
      return 1;
  }
  int main(){
      int n=read(),m=read();
      for(int i=1;i<=m;++i){
          int u=read(),v=read();
          ma[u][v]=ma[v][u]=1;
      }
      for(int i=1;i<=n;++i)for(int j=1;j<i;++j)
          if(!ma[i][j])add_edge(i,j),add_edge(j,i);
      memset(col,-1,sizeof col);
      for(int i=1;i<=n;++i){
          if(~col[i] ||!head[i])continue;
          col[i]=0;
          if(!dfs(i))Byebye();
      }
      for(int i=1;i<=n;++i)for(int j=1;j<i;++j)
          if(ma[i][j] && col[i]+col[j]==1)Byebye();
      printf("Yes\n");
      for(int i=1;i<=n;++i)putchar(~col[i]?!col[i]?'a':'c':'b');
      return 0;
  }
  ```
- **作者：Aisaka_Taiga (赞：3)**
  - **星级**：4星
  - **关键亮点**：采用并查集做法，利用b点度数为n - 1及a、c去掉b后形成两个连通块（完全图）的特点解题，思路独特。
  - **重点代码核心思想**：读入图并记录度数，跳过与b相关边，对其余边用并查集合并，判断连通块数量及同一连通块内边的完整性，最后根据并查集结果输出字符串。
  ```cpp
  signed main()
  {
      n=read(),m=read();
      for(int i=1;i<=n;i++)fa[i]=i,mp[i][i]=1;
      for(int i=1;i<=m;i++)
      {
          int u=read(),v=read();
          du[u]++,du[v]++;
          mp[u][v]=mp[v][u]=1;
      }
      for(int i=1;i<=n;i++)
      {
          if(du[i]==n-1)continue;
          for(int j=1;j<=n;j++)
              if(du[j]!=n-1&&mp[i][j])fa[fid(i)]=fid(j);
          int xx=fid(i);
          if(!vis[xx])vis[xx]=++cnt;
      }
      if(cnt>2){cout<<"No"<<endl;return 0;}
      for(int i=1;i<=n;i++)
      {
          if(du[i]==n-1)continue;
          for(int j=1;j<=n;j++)
              if(fid(i)==fid(j))if(!mp[i][j]){cout<<"No"<<endl;return 0;}
      }
      cout<<"Yes"<<endl;
      for(int i=1;i<=n;i++)
      {
          int xx=fid(i);
          if(du[i]==n-1)cout<<"b";
          else if(vis[xx]==1)cout<<"a";
          else if(vis[xx]==2)cout<<"c";
      }
      return 0;
  }
  ```
- **作者：osfly (赞：0)**
  - **星级**：4星
  - **关键亮点**：先找出度为n - 1的b点并删除，再通过洪水填充判断剩余图是否为一个或两个完全图，思路直接，代码简洁。
  - **重点代码核心思想**：读入图并记录度数，标记b点，对剩余未标记点用洪水填充染色，最后检查染色结果是否符合完全图结构及度数要求。
  ```cpp
  void dfs(int u,char col)
  {
      ans[u]=col;
      for(int i=head[u];i;i=e[i].nxt)
      {
          int v=e[i].v;
          if(ans[v]=='d') dfs(v,col);
      }
  }
  int A,B,C;
  bool check()
  {
      for(int i=1;i<=n;i++)
          if(ans[i]=='d') return 0;
      for(int i=1;i<=n;i++)
      {
          if(ans[i]=='a') A++;
          if(ans[i]=='b') B++;
          if(ans[i]=='c') C++;
      }
      for(int i=1;i<=n;i++)
      {
          if(ans[i]=='a'&&d[i]!=B+A-1) return 0;
          if(ans[i]=='c'&&d[i]!=B+C-1) return 0;
      }
      return 1;
  }
  int main()
  {
      memset(ans,'d',sizeof(ans));
      scanf("%d%d",&n,&m);
      for(int i=1;i<=m;i++)
      {
          int u,v;
          scanf("%d%d",&u,&v);
          d[u]++,d[v]++;
          add(u,v),add(v,u);
      }
      for(int i=1;i<=n;i++)
          if(d[i]==n-1) ans[i]='b';
      for(int i=1;i<=n;i++)
          if(ans[i]=='d')
          {
              dfs(i,'a');
              break;
          }
      for(int i=1;i<=n;i++)
          if(ans[i]=='d')
          {
              dfs(i,'c');
              break;
          }
      if(check())
      {
          printf("Yes\n");
          for(int i=1;i<=n;i++) printf("%c",ans[i]);
      }
      else printf("No");
      return 0;
  }
  ```

### 最优关键思路或技巧
1. **利用补图转化问题**：将原问题转化为补图的二分图染色问题，简化判断逻辑，如珅肐的题解。
2. **并查集判断连通性**：通过并查集判断图去掉b点后的连通块数量及结构，像Aisaka_Taiga的做法。
3. **直接搜索与判断**：先确定b点，再通过搜索判断剩余图结构，osfly的题解采用此方式，简洁直接。

### 可拓展之处
此类题目属于图论中根据特定规则构建或判断图与字符串关系的问题。类似套路是先分析图与字符串字符关系的特殊性质，再利用图论算法如二分图判断、连通性判断等求解。同类型题可考虑改变字符集、边的连接规则等。

### 洛谷推荐题目
1. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及二分图相关知识，判断图是否能进行二分染色。
2. [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)：同样利用二分图性质解决冲突分配问题。
3. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：基础并查集题目，可巩固并查集操作，有助于理解Aisaka_Taiga题解中的并查集应用。

### 个人心得摘录与总结
无。 

---
处理用时：95.61秒