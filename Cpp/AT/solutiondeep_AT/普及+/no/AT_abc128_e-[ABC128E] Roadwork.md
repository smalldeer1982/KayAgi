# 题目信息

# [ABC128E] Roadwork

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc128/tasks/abc128_e

東西に無限に続く $ 1 $ 本の大通りがあり、数直線とみなすことができます。

この大通り上で $ N $ 回道路工事が行われます。 $ i $ 番目の道路工事は時刻 $ S_i\ -\ 0.5 $ から時刻 $ T_i\ -\ 0.5 $ まで座標 $ X_i $ を通行止めにします。

$ Q $ 人の人が座標 $ 0 $ に立っています。 $ i $ 番目の人は時刻 $ D_i $ に座標 $ 0 $ を出発し、速度 $ 1 $ で正の方向へ歩き続けます。 歩いている途中で通行止めとなっている地点に到達した場合には、そこで歩くのをやめます。

$ Q $ 人それぞれが進む距離を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ S_i\ <\ T_i\ \leq\ 10^9 $
- $ 1\ \leq\ X_i\ \leq\ 10^9 $
- $ 0\ \leq\ D_1\ <\ D_2\ <\ ...\ <\ D_Q\ \leq\ 10^9 $
- $ i\ \neq\ j $ かつ $ X_i\ =\ X_j $ の時、区間 $ [S_i,\ T_i) $ と 区間 $ [S_j,\ T_j) $ は重ならない

### Sample Explanation 1

$ 1 $ 番目の人は時刻 $ 0 $ に座標 $ 0 $ を出発し、時刻 $ 2 $ に座標 $ 2 $ に到着した時点で、$ 1 $ 番目の道路工事による通行止めによって歩くのをやめます。 $ 2 $ 番目の人は時刻 $ 1 $ に座標 $ 0 $ を出発し、時刻 $ 3 $ に座標 $ 2 $ に到着します。この時、$ 1 $ 番目の道路工事は既に終了していますが、$ 4 $ 番目の道路工事が始まっているため、同様に座標 $ 2 $ で歩くのをやめます。 $ 4 $ 番目および $ 6 $ 番目の人は、歩いている最中に通行止めに出くわさないため、無限に歩き続けます。

## 样例 #1

### 输入

```
4 6

1 3 2

7 13 10

18 20 13

3 4 2

0

1

2

3

5

8```

### 输出

```
2

2

10

-1

13

-1```

# AI分析结果

### 题目内容重写

东西方向有一条无限延伸的大道，可以将其视为数轴。

在这条大道上进行了 $N$ 次道路施工。第 $i$ 次施工从时刻 $S_i - 0.5$ 到时刻 $T_i - 0.5$，在坐标 $X_i$ 处进行，期间该坐标禁止通行。

有 $Q$ 个人站在坐标 $0$ 处。第 $i$ 个人在时刻 $D_i$ 从坐标 $0$ 出发，以速度 $1$ 向正方向行走。如果在行走过程中遇到禁止通行的地点，则停止行走。

请计算每个人行走的距离。

### 算法分类
离散化、线段树、优先队列

### 题解分析与结论

本题的核心是将道路施工的影响转化为时间区间，并通过数据结构高效处理这些区间。以下是各题解的要点对比：

1. **chen_hx**：使用线段树进行区间修改和单点查询，通过二分查找确定受影响的区间。思路清晰，代码实现较为复杂，但逻辑严密。
2. **FFTotoro**：结合优先队列和线段树，利用优先队列处理施工结束时间，线段树维护区间最小值。思路新颖，代码简洁，但需要理解优先队列的使用。
3. **elbissoPtImaerD**：使用 `multiset` 维护当前有效的施工位置，通过事件排序处理插入和删除操作。代码简洁，思路清晰，易于理解。

### 精选题解

1. **elbissoPtImaerD**（5星）
   - **关键亮点**：使用 `multiset` 维护当前有效的施工位置，通过事件排序处理插入和删除操作。代码简洁，思路清晰，易于理解。
   - **核心代码**：
     ```cpp
     sd multiset<int>S;
     il void Solve() {
         rd(n,m);
         for(int i=1,x,l,r;i<=n;++i) rd(l,r,x),a.push_back({l-x,~i}),a.push_back({r-x,i}),b[i]=x;
         for(int x;m--;) rd(x),a.push_back({x,n+1});
         sd stable_sort(begin(a),end(a));
         for(pii x:a) x.y>n?wrt(S.size()?*begin(S):-1,'\n'):x.y<0?S.insert(b[~x.y]),7:(S.erase(S.find(b[x.y])),7);
         return;
     }
     ```
   - **个人心得**：通过事件排序和 `multiset` 的使用，简化了问题处理，代码实现高效且易于理解。

2. **FFTotoro**（4星）
   - **关键亮点**：结合优先队列和线段树，利用优先队列处理施工结束时间，线段树维护区间最小值。思路新颖，代码简洁。
   - **核心代码**：
     ```cpp
     priority_queue<pii,vector<pii>,greater<> > q;
     atcoder::segtree<int,op,e> t(c+1);
     for(auto [x,l,r]:a)
         if(int y=w[x];t.get(y)==INT_MAX)t.set(y,l),q.emplace(r,y);
     while(m--&&cin>>d){
         while(!q.empty()&&q.top().first<=d){
             int x=q.top().second; q.pop();
             while(!v[x].empty()&&v[x].front().second<=d)v[x].pop();
             if(v[x].empty())t.set(x,INT_MAX);
             else t.set(x,v[x].front().first),q.emplace(v[x].front().second,x);
         }
         cout<<p[t.max_right<f>(0)]<<'\n';
     }
     ```
   - **个人心得**：通过优先队列和线段树的结合，高效处理了施工结束时间的更新和查询。

3. **chen_hx**（4星）
   - **关键亮点**：使用线段树进行区间修改和单点查询，通过二分查找确定受影响的区间。思路清晰，代码实现较为复杂，但逻辑严密。
   - **核心代码**：
     ```cpp
     void change(int p,int l,int r,int L,int R,int d){
         if(R<l||r<L)return;
         if(L<=l&&r<=R){
             val[p]=d;
             return;
         }
         pushdown(p);
         int mid=l+r>>1;
         change(ls[p],l,mid,L,R,d);
         change(rs[p],mid+1,r,L,R,d);
     }
     int query(int p,int l,int r,int d){
         if(d<l||r<d)return -100;
         if(val[p])return val[p];
         else{
             int mid=l+r>>1;
             return max(query(ls[p],l,mid,d),query(rs[p],mid+1,r,d));
         }
     }
     ```
   - **个人心得**：通过线段树的区间修改和单点查询，确保了问题的高效解决，但代码实现较为复杂。

### 最优关键思路
使用 `multiset` 维护当前有效的施工位置，通过事件排序处理插入和删除操作，代码简洁且高效。

### 可拓展之处
类似的问题可以通过事件排序和数据结构（如 `multiset`、线段树、优先队列等）进行高效处理，适用于区间覆盖和单点查询的场景。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：37.43秒