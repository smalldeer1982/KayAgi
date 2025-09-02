# 题目信息

# Omkar and Determination

## 题目描述

The problem statement looms below, filling you with determination.

Consider a grid in which some cells are empty and some cells are filled. Call a cell in this grid exitable if, starting at that cell, you can exit the grid by moving up and left through only empty cells. This includes the cell itself, so all filled in cells are not exitable. Note that you can exit the grid from any leftmost empty cell (cell in the first column) by going left, and from any topmost empty cell (cell in the first row) by going up.

Let's call a grid determinable if, given only which cells are exitable, we can exactly determine which cells are filled in and which aren't.

You are given a grid $ a $ of dimensions $ n \times m $ , i. e. a grid with $ n $ rows and $ m $ columns. You need to answer $ q $ queries ( $ 1 \leq q \leq 2 \cdot 10^5 $ ). Each query gives two integers $ x_1, x_2 $ ( $ 1 \leq x_1 \leq x_2 \leq m $ ) and asks whether the subgrid of $ a $ consisting of the columns $ x_1, x_1 + 1, \ldots, x_2 - 1, x_2 $ is determinable.

## 说明/提示

For each query of the example, the corresponding subgrid is displayed twice below: first in its input format, then with each cell marked as "E" if it is exitable and "N" otherwise.

For the first query:

```
<pre class="verbatim"><br></br>..X EEN<br></br>... EEE<br></br>... EEE<br></br>... EEE<br></br>
```

```
<pre class="verbatim"><br></br><br></br>
```

For the second query:

```
<pre class="verbatim"><br></br>X N<br></br>. E<br></br>. E<br></br>. E<br></br>
```

Note that you can exit the grid by going left from any leftmost cell (or up from any topmost cell); you do not need to reach the top left corner cell to exit the grid.

```
<pre class="verbatim"><br></br><br></br>
```

For the third query:

```
<pre class="verbatim"><br></br>XX NN<br></br>X. NN<br></br>X. NN<br></br>X. NN<br></br>
```

This subgrid cannot be determined only from whether each cell is exitable, because the below grid produces the above "exitability grid" as well:

```
<pre class="verbatim"><br></br>XX<br></br>XX<br></br>XX<br></br>XX<br></br>
```

```
<pre class="verbatim"><br></br><br></br>
```

For the fourth query:

```
<pre class="verbatim"><br></br>X N<br></br>. E<br></br>. E<br></br>. E<br></br>
```

```
<pre class="verbatim"><br></br><br></br>
```

For the fifth query:

```
<pre class="verbatim"><br></br>..XXX EENNN<br></br>...X. EEENN<br></br>...X. EEENN<br></br>...X. EEENN<br></br>
```

This query is simply the entire grid. It cannot be determined only from whether each cell is exitable because the below grid produces the above "exitability grid" as well:

```
<pre class="verbatim"><br></br>..XXX<br></br>...XX<br></br>...XX<br></br>...XX<br></br>
```

## 样例 #1

### 输入

```
4 5
..XXX
...X.
...X.
...X.
5
1 3
3 3
4 5
5 5
1 5```

### 输出

```
YES
YES
NO
YES
NO```

# AI分析结果

### 中文题目重写

#### 题目描述

考虑一个网格，其中一些单元格是空的，一些单元格是填充的。如果一个单元格是空的，并且从该单元格出发，你可以通过仅向上和向左移动通过空单元格来退出网格，则该单元格被称为“可退出”的。这包括单元格本身，因此所有填充的单元格都不是“可退出”的。注意，你可以通过向左移动从任何最左边的空单元格（第一列的单元格）退出网格，通过向上移动从任何最顶部的空单元格（第一行的单元格）退出网格。

我们称一个网格是“可确定的”，如果仅根据哪些单元格是“可退出”的，我们可以准确地确定哪些单元格是填充的，哪些不是。

给定一个 $n \times m$ 的网格 $a$，即一个有 $n$ 行和 $m$ 列的网格。你需要回答 $q$ 个查询（$1 \leq q \leq 2 \cdot 10^5$）。每个查询给出两个整数 $x_1, x_2$（$1 \leq x_1 \leq x_2 \leq m$），并询问由 $a$ 的第 $x_1$ 列到第 $x_2$ 列组成的子网格是否是可确定的。

#### 说明/提示

对于每个查询的示例，相应的子网格会显示两次：第一次以其输入格式显示，第二次将每个单元格标记为“E”表示可退出，“N”表示不可退出。

#### 样例 #1

##### 输入

```
4 5
..XXX
...X.
...X.
...X.
5
1 3
3 3
4 5
5 5
1 5
```

##### 输出

```
YES
YES
NO
YES
NO
```

### 算法分类
前缀和

### 题解分析与结论

#### 综合分析
题目要求判断给定子网格是否“可确定”，即是否可以根据“可退出”信息唯一确定网格的填充情况。关键在于发现，当子网格中存在一个单元格，其上方和左侧都是填充的（即 `X`），则该子网格不可确定。因此，我们需要预处理每一列是否存在这样的单元格，并使用前缀和来快速查询任意区间内是否存在不可确定的列。

#### 所选题解

1. **作者：henrytb (赞：2)**
   - **星级：4**
   - **关键亮点：**
     - 通过观察题目性质，发现不可确定的条件是存在一个 $2 \times 2$ 的矩形，其左下和右上都是 `X`。
     - 使用 ST 表来维护区间查询，虽然复杂度较高，但思路清晰。
   - **代码核心思想：**
     - 预处理每个列是否存在不可确定的单元格，并使用 ST 表进行区间查询。

   ```cpp
   #include <bits/stdc++.h>
   #define rep(i,a,b) for(int i=(a);i<=(b);++i)
   #define per(i,a,b) for(int i=(a);i>=(b);--i)
   using namespace std;
   int _,n,m;
   string s[1000005];
   bool f[1000005];
   bool st[1000005][21];
   int main() {
       ios::sync_with_stdio(false);
       cin.tie(0);cout.tie(0);
       cin>>n>>m;
       rep(i,1,n) cin>>s[i];
       rep(i,1,n-1) rep(j,1,m-1) {
           if(s[i+1][j-1]=='X'&&s[i][j]=='X') f[j]=1,st[j][0]=1;
       }
       rep(j,1,20) rep(i,1,m-1) {
           if(i+(1<<(j-1))-1>m-1) st[i][j]=st[i][j-1];
           else st[i][j]=st[i][j-1]|st[i+(1<<(j-1))][j-1];
       }
       for(cin>>_;_;--_) {
           int l,r;
           cin>>l>>r;
           if(l==r) {cout<<"YES"<<endl;continue;}
           int lg=log2(r-l);
           bool ans=st[l][lg]|st[r-(1<<lg)][lg];
           if(ans) cout<<"NO"<<endl;
           else cout<<"YES"<<endl;
       }
       return 0;
   }
   ```

2. **作者：Yizhixiaoyun (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 通过预处理找到每一列是否存在不可确定的单元格，并使用前缀和进行区间查询。
     - 代码简洁，思路清晰。
   - **代码核心思想：**
     - 预处理每个列是否存在不可确定的单元格，并使用前缀和进行区间查询。

   ```cpp
   #include<bits/stdc++.h>
   #define ok puts("YES")
   #define no puts("NO")
   using namespace std;
   const int maxn=1000010;
   int q;
   int n,m,l,r;
   int sum[maxn];
   string s[maxn];
   inline void init(){
       cin>>n>>m;
       for(register int i=1;i<=n;++i) cin>>s[i];
   }
   int main(){
       init();
       for(register int i=2;i<=n;++i){
           for(register int j=1;j<m;++j){
               if(s[i][j-1]=='X'&&s[i-1][j]=='X') sum[j+1]++;
           }
       }
       for(register int i=2;i<=m;++i) sum[i]+=sum[i-1];
       cin>>q;
       while(q--){
           cin>>l>>r;
           if(sum[r]-sum[l]==0) ok;
           else no;
       }
   }
   ```

3. **作者：KSToki (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 通过预处理找到每一列是否存在不可确定的单元格，并使用前缀和进行区间查询。
     - 代码简洁，思路清晰。
   - **代码核心思想：**
     - 预处理每个列是否存在不可确定的单元格，并使用前缀和进行区间查询。

   ```cpp
   #include<bits/stdc++.h>
   #define YPC rubbish 
   #define R register
   #define I inline
   #define ll long long
   #define ull unsigned long long
   #define LL __int128
   #define db double
   using namespace std;
   #define pb push_back
   #define pii pair<int,int>
   #define pli pair<ll,int>
   #define pll pair<ll,ll>
   #define mp(x,y) make_pair(x,y)
   #define piii pair<pair<int,int>,int>
   #define mp3(x,y,z) make_pair(make_pair(x,y),z)
   #define fi first
   #define se second
   #define putint(x) printf("%d\n",x)
   #define putll(x) printf("%lld\n",x)
   #define putull(x) printf("%llu\n",x)
   #define lowbit(x) ((x)&(-(x)))
   #define chkmin(x,y) (x=min(x,y))
   #define chkmax(x,y) (x=max(x,y))
   #define inv(x) ksm(x,mod-2)
   #define inf (1e9)
   #define INF (1e18)
   #define eps (1e-8)
   #define For(i,x,y) for(R int i=x;i<=y;++i)
   #define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
   #define Rof(i,x,y) for(R int i=x;i>=y;--i)
   #define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
   #define ForG(i,edge,x) for(auto i:edge[x])
   I int read()
   {
       char ch=getchar();
       int res=0,flag=1;
       while(ch<'0'||ch>'9')
       {
           if(ch=='-')
               flag=-1;
           ch=getchar();
       }
       while(ch>='0'&&ch<='9')
       {
           res=res*10+ch-'0';
           ch=getchar();
       }
       return res*flag;
   }
   int T,n,m,q,s[1000001],x,y;
   bool f[1000001];
   vector< vector<char> >c;
   int main()
   {
       n=read();
       m=read();
       c.resize(n+1);
       For(i,1,n)
       {
           c[i].resize(m+1);
           For(j,1,m)
               cin>>c[i][j];
       }
       For(i,2,m)
       {
           For(j,2,n)
               if(c[j-1][i]=='X'&&c[j][i-1]=='X')
                   f[i]=1;
           s[i]=s[i-1]+f[i];
       }
       q=read();
       while(q--)
       {
           x=read();
           y=read();
           if(x==y)
               puts("YES");
           else
           {
               if(s[y]-s[x])
                   puts("NO");
               else
                   puts("YES");
           }
       }
       return 0;
   }
   ```

### 最优关键思路或技巧
- **关键思路：** 通过预处理找到每一列是否存在不可确定的单元格，并使用前缀和进行区间查询。
- **优化技巧：** 使用前缀和来快速查询任意区间内是否存在不可确定的列，时间复杂度为 $O(nm + q)$。

### 可拓展之处
- 类似的问题可以通过预处理和前缀和来优化查询，例如在二维数组中查询某个子矩阵是否满足特定条件。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

---
处理用时：66.34秒