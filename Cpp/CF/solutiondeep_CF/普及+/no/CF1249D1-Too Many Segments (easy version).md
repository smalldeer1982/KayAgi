# 题目信息

# Too Many Segments (easy version)

## 题目描述

简单难度与困难难度的唯一差别是$n,k$的范围

给予$n$条线段，这些线段可以有重叠部分甚至完全重叠在一起。第$i$条线段$[l_i,r_i](l_i≤r_i)$覆盖了所有整数点$j$满足$l_i≤j≤r_i$

如果一个整数点被**超过**$k$条线段覆盖，那么就称之为bad point（下文以坏点代替）

你的任务是去掉最少的线段使得没有坏点的存在

## 样例 #1

### 输入

```
7 2
11 11
9 11
7 8
8 9
7 8
9 11
7 9
```

### 输出

```
3
1 4 7 
```

## 样例 #2

### 输入

```
5 1
29 30
30 30
29 29
28 30
30 30
```

### 输出

```
3
1 2 4 
```

## 样例 #3

### 输入

```
6 1
2 3
3 3
2 3
2 2
2 3
2 3
```

### 输出

```
4
1 3 5 6 
```

# AI分析结果

### 题目中文重写
# 过多线段（简单版本）

## 题目描述
简单难度与困难难度的唯一差别是 $n$，$k$ 的范围。

给定 $n$ 条线段，这些线段可以有重叠部分甚至完全重叠在一起。第 $i$ 条线段 $[l_i, r_i](l_i \leq r_i)$ 覆盖了所有满足 $l_i \leq j \leq r_i$ 的整数点 $j$。

如果一个整数点被**超过** $k$ 条线段覆盖，那么就称之为坏点（下文以坏点代替）。

你的任务是去掉最少的线段使得没有坏点的存在。

## 样例 #1
### 输入
```
7 2
11 11
9 11
7 8
8 9
7 8
9 11
7 9
```
### 输出
```
3
1 4 7 
```

## 样例 #2
### 输入
```
5 1
29 30
30 30
29 29
28 30
30 30
```
### 输出
```
3
1 2 4 
```

## 样例 #3
### 输入
```
6 1
2 3
3 3
2 3
2 2
2 3
2 3
```
### 输出
```
4
1 3 5 6 
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即对于每个坏点，优先删除右端点更靠右的线段，因为这样的线段覆盖的点更多，删除后能更有效地减少坏点的数量。

各题解的算法要点和难点对比如下：
- **一铭君一**：从头扫描数轴上的点，找到坏点后扫描覆盖该坏点的所有线段，删除在坏点右侧长度最长的线段，直到该坏点合法。难点在于证明删除右侧长度最长的线段是最优策略。
- **Lucifer_Bartholomew**：用 `set` 按照区间右端点为排序关键字维护区间，在扫到区间左端点时加入 `set`，扫到右端点加 1 的位置时弹出，若 `set` 中区间数量超过 $k$，则弹出最末一段区间。难点在于理解 `set` 的使用和区间的动态维护。
- **Handezheng**：用 `vector` 存储以每个点为左端点的线段信息，用 `set` 存储覆盖到当前点的线段，遍历点时删除“过期”线段，若当前点是坏点则删除右端点最大的线段。难点在于数据结构的选择和使用。
- **Daniel_yao**：思路一为暴力枚举线段和数轴上的点，删除右端点最靠右的线段；思路二用 `set` 优化，删除“过期”线段。难点在于优化思路的理解和实现。
- **JWRuixi**：用 `vector` 维护要插入的点，用 `set` 维护区间，删除“过期”线段，若 `set` 元素数量大于 $k$ 则去掉末尾元素。难点在于 `set` 的操作和区间的管理。
- **minVan**：用差分维护线段结束，用优先队列存储线段，按左端点排序后枚举线段，判断当前点覆盖线段数量是否超过 $k$，若超过则删除右端点最大的线段。难点在于差分和优先队列的结合使用。

### 所选题解
- **一铭君一（4星）**
  - **关键亮点**：思路清晰，有详细的贪心证明过程，代码实现简洁易懂。
- **Handezheng（4星）**
  - **关键亮点**：考虑了加强版的情况，对数据结构的选择和使用有详细说明，代码注释丰富。
- **Daniel_yao（4星）**
  - **关键亮点**：提供了暴力和优化两种思路，对优化思路的讲解清晰，代码实现完整。

### 重点代码
#### 一铭君一
```cpp
struct Node{
  int l,r,org;
};

struct Node segments[maxn];
inline bool operator < (const Node a,const Node b){
  return a.r<b.r;
}//为了方便，按右端点递增排个序

inline bool inrange(const int i,const int x){
  return (segments[i].l<=x)&&(x<=segments[i].r);
}//判断一个点是不是被第i条线段覆盖

signed main(){
  read(n),read(k);
  for(int i=1,l,r;i<=n;++i){
    read(segments[i].l),read(segments[i].r),segments[i].org=i;
    for(int j=segments[i].l;j<=segments[i].r;++j)
      ++A[j];
  }
  std::sort(segments+1,segments+1+n);
  for(int i=1;i<=200;++i){//枚举每一个点
    while(A[i]>k){//如果是坏点
      for(int j=n;j>0;--j)//从结尾开始枚举线段j(排序之后右端点递减，找到的第一个就是在坏点右侧最长的线段)
        if(inrange(j,i) && !vis[j]){//线段j覆盖了这个坏点，并且还没有被删除
          for(int q=segments[j].l;q<=segments[j].r;++q)//删掉这个线段
            A[q]--;
          vis[j]=1;//标记已删除
          ++ans;
          break;
        }
    }
  }
  write(ans);
  putchar('\n');
  for(int i=1;i<=n;++i)
    if(vis[i]) write(segments[i].org),putchar(' ');
  return 0;
}
```
**核心实现思想**：先统计每个点被覆盖的次数，按线段右端点排序，然后枚举每个点，若为坏点则删除在该坏点右侧长度最长的线段，直到该点合法。

#### Handezheng
```cpp
int n,k;
int tot;//被删除线段的数量 
struct node{
  int r,id;
  //r记录区间的右端点
  //id记录当前区间的编号
}ans[N];//被删除线段的编号 
inline bool operator < (node a,node b){
  if(a.r == b.r) return a.id < b.id;
  return a.r < b.r;
  //以右端点为关键字
}
inline bool cmp(node a,node b){
  return a.id < b.id;
  //以编号为关键字升序排序
}
vector <node> a[N];
//a[l]记录以l为左端点的线段的相关信息 
set <node> st;
//set记录覆盖到当前点的线段 

signed main(){
  read(n),read(k);
  int l,r;
  node tmp;
  F(1,i,n){
    read(l),read(r);
    tmp.r = r,tmp.id = i;
    a[l].push_back(tmp);
  }
  
  F(1,i,200000){
    while(st.size() && (*st.begin()).r < i){//区间的右端点小于当前点，说明这个区间已"过期"
      st.erase(*st.begin());
    }//删除"过期"的区间
    
    for(int j = 0;j < a[i].size();j ++){
      st.insert(a[i][j]);
    }//把以当前遍历到的点为左端点的区间插入至set
    
    while(st.size() > k){//如果这个点是坏点
      ans[++ tot] = *st.rbegin();//记录要被删除的区间
      st.erase(*st.rbegin());//删除区间
    }
  }
  printf("%lld\n",tot);
  sort(ans + 1,ans + tot + 1,cmp);
  F(1,i,tot) printf("%lld ",ans[i].id);
  
  return 0;
}
```
**核心实现思想**：用 `vector` 存储以每个点为左端点的线段信息，用 `set` 存储覆盖到当前点的线段，遍历点时删除“过期”线段，若当前点是坏点则删除右端点最大的线段。

#### Daniel_yao
```cpp
// 优化暴力思路代码
const int N = 200005;
struct Node{
  int r, id;
}a[N];
int n, k, h[N], tot;
set<Node> s;
vector<Node> v[N];

bool operator < (Node x, Node y){
  if(x.r == y.r) return x.id < y.id;
  return x.r < y.r;
}

int main(){
  cin >> n >> k;
  for(int i = 1;i <= n;i++){
    int a1, b1;
    Node c;
    cin >> a1 >> b1;
    c.id = i;
    c.r = b1;
    v[a1].push_back(c);
  }
  for(int i = 1;i < N;i++){
    while(s.size() && (*s.begin()).r < i){//“过期了”直接删除
      s.erase(*s.begin());
    }
    for(int j = 0;j < v[i].size();j++){
      s.insert(v[i][j]);
    }
    while(s.size() > k){//该点被超过 k 个线段所覆盖
      a[++tot] = *s.rbegin();
      s.erase(*s.rbegin());//将右端点最靠右的线段删除
    }
  }
  cout << tot << '\n';
  for(int i = 1;i <= tot;i++){
    cout << a[i].id << ' ';
  }
  return 0;
}
```
**核心实现思想**：用 `vector` 存储以每个点为左端点的线段信息，用 `set` 存储覆盖到当前点的线段，遍历点时删除“过期”线段，若当前点被超过 $k$ 个线段覆盖，则删除右端点最靠右的线段。

### 最优关键思路或技巧
- **贪心策略**：对于每个坏点，优先删除右端点更靠右的线段，因为这样的线段覆盖的点更多，删除后能更有效地减少坏点的数量。
- **数据结构优化**：使用 `set` 或优先队列等数据结构来维护线段，方便按右端点排序和删除操作，将时间复杂度优化到 $O(n\log n)$。
- **“过期”线段处理**：在遍历点的过程中，及时删除右端点小于当前点的线段，避免无效操作。

### 可拓展之处
同类型题或类似算法套路：
- 区间覆盖问题：给定多个区间，要求选择最少的区间覆盖某个范围。
- 活动选择问题：给定多个活动的开始和结束时间，要求选择最多的活动，使得这些活动时间不冲突。

### 推荐题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
- [P2082 区间覆盖](https://www.luogu.com.cn/problem/P2082)
- [P1829 [国家集训队]Crash的数字表格 / JZPTAB](https://www.luogu.com.cn/problem/P1829)

### 个人心得
- **一铭君一**：强调贪心题需要给出证明，否则题解不完整。
- **Handezheng**：提到做完本题可以去做加强版题目，双倍经验。
- **Daniel_yao**：安利了自己的博客。 

---
处理用时：85.16秒