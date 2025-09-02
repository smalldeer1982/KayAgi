# 题目信息

# Closing ceremony

## 题目描述

The closing ceremony of Squanch Code Cup is held in the big hall with $ n×m $ seats, arranged in $ n $ rows, $ m $ seats in a row. Each seat has two coordinates $ (x,y) $ ( $ 1<=x<=n $ , $ 1<=y<=m $ ).

There are two queues of people waiting to enter the hall: $ k $ people are standing at $ (0,0) $ and $ n·m-k $ people are standing at $ (0,m+1) $ . Each person should have a ticket for a specific seat. If person $ p $ at $ (x,y) $ has ticket for seat $ (x_{p},y_{p}) $ then he should walk $ |x-x_{p}|+|y-y_{p}| $ to get to his seat.

Each person has a stamina — the maximum distance, that the person agrees to walk. You should find out if this is possible to distribute all $ n·m $ tickets in such a way that each person has enough stamina to get to their seat.

## 样例 #1

### 输入

```
2 2
3 3 3 2
1 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2
3 2 3 3
1 2
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 闭幕式

## 题目描述
Squanch Code Cup的闭幕式在一个有 $n×m$ 个座位的大厅举行，座位排成 $n$ 行，每行 $m$ 个座位。每个座位都有两个坐标 $(x,y)$（$1 \leq x \leq n$，$1 \leq y \leq m$）。

有两队人在等待进入大厅：$k$ 个人站在 $(0,0)$，$n·m - k$ 个人站在 $(0,m + 1)$。每个人都有一张特定座位的票。如果站在 $(x,y)$ 的人 $p$ 的票对应的座位是 $(x_p,y_p)$，那么他需要走 $|x - x_p| + |y - y_p|$ 的距离才能到达他的座位。

每个人都有一个耐力值 —— 这个人愿意行走的最大距离。你需要判断是否有可能以这样一种方式分配所有 $n·m$ 张票，使得每个人都有足够的耐力走到他们的座位。

## 样例 #1
### 输入
```
2 2
3 3 3 2
1 3
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
2 2
3 2 3 3
1 2
```
### 输出
```
NO
```

### 综合分析与结论
这些题解的核心思路都是基于贪心策略来解决问题，主要围绕如何合理地为从不同入口进入的人分配座位，使得所有人都能在其耐力范围内到达座位。
1. **思路方面**：大多题解都意识到要对从$(0,0)$和$(0,m + 1)$进入的人分别考虑，且需按耐力值排序。对于从$(0,0)$进入的人，要尽量选择对从$(0,m + 1)$进入的人影响小的座位，即离$(0,m + 1)$远的座位；反之亦然。
2. **算法要点**：排序是基础操作，之后通过不同方式去寻找符合条件的座位。有的题解使用线段树、优先队列等数据结构辅助查找，有的则直接暴力枚举查找。
3. **解决难点**：难点在于如何在满足从$(0,0)$进入的人的座位分配需求时，不影响从$(0,m + 1)$进入的人的座位分配，反之亦然。也就是要平衡好两个入口的人的座位分配，找到一种全局最优的分配方式。

### 所选的题解
- **作者iodwad（5星）**
  - **关键亮点**：思路清晰，利用线段树维护数据，优化了查找符合条件座位的过程，使得整体时间复杂度降为 $\mathcal{O}(n\cdot \log n)$，代码实现较为简洁高效。
  - **重点代码**：
```cpp
// 线段树相关结构体与操作
namespace SegmentTree {
  struct Node {
    int maxv, posv;
    Node *ch[2];
    Node() : maxv(-1), posv(0) {
      ch[0] = ch[1] = NULL;
    }
  } *root;
  inline void pushup(Node *o) {
    if (o -> ch[0] -> maxv > o -> ch[1] -> maxv) {
      o -> maxv = o -> ch[0] -> maxv;
      o -> posv = o -> ch[0] -> posv;
    } else {
      o -> maxv = o -> ch[1] -> maxv;
      o -> posv = o -> ch[1] -> posv;
    }
  }
  void build(Node *&o, int l, int r) {
    o = new Node;
    if (l == r) {
      o -> maxv = p[l].second;
      o -> posv = l;
      return;
    }
    int mid = (l + r) >> 1;
    build(o -> ch[0], l, mid);
    build(o -> ch[1], mid + 1, r);
    pushup(o);
  }
  std::pair < int, int >  query(Node *o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return std::make_pair(o -> maxv, o -> posv);
    int mid = (l + r) >> 1;
    std::pair < int, int> res = std::make_pair(-1, 0);
    if (ql <= mid) res = query(o -> ch[0], l, mid, ql, qr);
    if (mid < qr) {
      std::pair < int, int > ress = query(o -> ch[1], mid + 1, r, ql, qr);
      if (ress > res) res = ress;
    }
    return res;
  }
  void modify(Node *o, int l, int r, int pos, int val) {
    if (l == r) {
      o -> maxv = val;
      o -> posv = pos;
      return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(o -> ch[0], l, mid, pos, val);
    else modify(o -> ch[1], mid + 1, r, pos, val);
    pushup(o);
  }
}
```
核心实现思想：通过线段树的构建、查询和修改操作，快速找到符合耐力值条件且到$(m + 1,0)$距离最大的座位。
- **作者hjqhs（4星）**
  - **关键亮点**：贪心策略简洁明了，直接利用`lower_bound`查找符合条件的人，代码实现简洁，可读性强。
  - **重点代码**：
```cpp
void solve(){
  cin>>n>>m>>k;
  rep(i,1,k){cin>>x,a.emplace_back(x);}
  cin>>x;rep(i,1,n*m-k){cin>>x;b.emplace_back(x);}
  sort(all(a)),sort(all(b));
  per(i,n,1)rep(j,1,m){
    vector<int>::iterator p,q;
    p=lower_bound(all(a),i+j);
    q=lower_bound(all(b),i+m+1-j);
    if(p!=a.end())a.erase(p);
    else if(q!=b.end())b.erase(q);
    else{cout<<"NO"<<'\n';return;}
  }
  cout<<"YES"<<'\n';
}
```
核心实现思想：对耐力值排序后，每次通过`lower_bound`查找能到达当前考虑座位（左下角和右下角相关座位）的最小耐力值的人，并将其从人群中移除，若找不到则输出`NO`。
- **作者RainFestival（4星）**
  - **关键亮点**：利用优先队列维护座位信息，按照焦虑度排序后依次为不同入口的人分配座位，思路清晰，实现巧妙。
  - **重点代码**：
```cpp
for (int i=1;i<=lim;i++)
{
	for (int j=0;j<s1[i].size();j++)
	{
		int x=s1[i][j].first,y=s1[i][j].second;
		pq.push(std::make_pair(dist(x,y,0,m+1),std::make_pair(x,y)));
	}
	for (int j=1;j<=f[i];j++)
	{
		if (pq.empty())
		{
			flag=1;
			break;
		}
		int x=pq.top().second.first,y=pq.top().second.second;pq.pop();
		used[x][y]=1;
//		printf("left %d (%d,%d)\n",i,x,y);
	}
	if (flag) break;
}
```
核心实现思想：先将离左上角距离符合当前焦虑度的座位按离右上角的距离放入优先队列，每次从优先队列中取出离右上角最远的座位分配给当前焦虑度的人，若队列为空则说明无法分配，标记失败。

### 最优关键思路或技巧
1. **贪心策略**：按耐力值排序，为从不同入口进入的人选择对另一入口进入的人影响最小的座位。
2. **数据结构优化**：如iodwad使用线段树，RainFestival使用优先队列，能更高效地查找和维护符合条件的座位信息，优化时间复杂度。

### 可拓展思路
此类题目属于匹配类问题，涉及到资源分配与限制条件满足。类似的算法套路可应用于其他涉及多个约束条件下的资源分配问题，例如多个任务分配给不同机器，每个任务有时间限制，每台机器有处理能力限制等。

### 推荐洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：同样是基于贪心策略的分配问题，通过对数据的合理排序来优化分配方案。
2. [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析双方的策略，利用贪心思想找到最优解，与本题在思维方式上有相似之处。
3. [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对人物属性的排序，运用贪心策略解决问题，锻炼对贪心策略的应用能力。

### 个人心得摘录与总结
1. **幻影星坚强**：提到写代码时`n`和`m`写反，虽过了样例但WA了所有测试点，强调了细心的重要性，在处理坐标等数据时要格外谨慎。 

---
处理用时：44.40秒