# Students and Shoelaces

## 题目描述

小贝和小聪是俱乐部的管理人员。当俱乐部聚会时，学生们又开始捣乱。他们带来很多鞋带，并且用鞋带将大家相互捆绑起来，每根鞋带捆住两个学生。

为了恢复秩序，小贝和小聪采取了以下措施。首先，对于每位学生，小贝检查他和哪些学生捆在一起。如果和这个学生捆在一起的学生人数等于1，小贝就将这个学生记录在案。小贝检查完每位学生后，小聪就将这些被记录的学生分到一个组中，并将这组学生踢出俱乐部。这组学生立刻离开俱乐部，同时将捆着他们的鞋带也一起带走。这组学生离开后，小贝和小聪继续重复上述的过程，直到没有学生可以被记录下来为止。

请确定总共有多少组学生被踢出俱乐部。

## 说明/提示

在第一个样例中，小贝和小聪不会踢掉任何学生，因为每位学生都和另外两位学生捆在一起。

在第二个样例中，有4名学生依次捆成一条“链”，还有2名学生没有被捆。小贝和小聪会先将“链”两端的学生（1号和4号）作为一组踢走，再将2号和3号作为一组踢走，所以答案为2。

在第三组样例中，除了4号学生，其他学生会作为一组一起被踢走，所以答案为1。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
6 3
1 2
2 3
3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6 5
1 4
2 4
3 4
5 4
6 4
```

### 输出

```
1
```

# 题解

## 作者：N_z_ (赞：3)

## 思路
直接加边，记录每一个点的度，然后扫，扫到度为$1$的点就把它踢掉，答案$+1$，和它相邻的点度数$-1$。

其实就是拓扑排序的思想。

具体见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int d[101];
bool c[101][101];
int e[101];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1,a,b;i<=m;i++)
	cin>>a>>b,d[a]++,d[b]++,c[a][b]=1,c[b][a]=1;
	int cc=1,ans=0;
	while(cc>0){
		memset(e,0,sizeof(e));
		ans++;
		cc=0;
		for(int i=1;i<=n;i++)
		if(d[i]==1)e[cc++]=i,d[i]--;
		for(int i=0;i<cc;i++)
		for(int j=1;j<=n;j++)
		if(c[e[i]][j])d[j]--;
	}
	cout<<ans-1<<endl;
}
```

---

## 作者：keep_shining (赞：1)

## 题意
有 $n$ 个同学，$m$ 条鞋带，这 $m$ 条鞋带每条鞋带都绑着两个人，现在重复进行进行如下操作，直到没有被记下来的同学为止：

- 找到只被一条鞋带绑着的所有同学，把他们记下来并踢掉。
- 把踢掉的同学连着的鞋带去掉。

## 思路：
既然要统计有多少个和他连着的鞋带，那我们在输入时用一个 $sum$ 数组统计每个同学和多少个同学连着，然后模拟一下踢掉和将连着的鞋带去掉的过程。

## AC code:
```cpp
#include<bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false);cin.tie();cout.tie();
#define Endl endl
#define itn int
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define endl '\n'

const int N=1e6+5;
const int M=2e3+5;

int n,m,sum[105],ans; 
vector<int>v[105];
bool f;

int read()
{
	register int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

int main()
{
	n=read();
	m=read();
	For(i,1,m)
	{
		int a=read(),b=read();//读入
		v[a].push_back(b);//记录每个a连着的人的编号，以后有用，这里也可用二维数组或其他数据结构
		v[b].push_back(a);//同上
		sum[a]++;//a连着的数量+1
		sum[b]++;//b连着的数量+1
	}
	while(!f)//还没结束
	{
		int k[105],l=0;//l是k的长度，k是记录出局的人连着的人的编号
		f=true;//先让假设没有能踢除的了
		For(i,1,n)//遍历每个人
		{
			if(sum[i]==1)//如果有一个和他连着的
			{
				f=false;//有能踢除的
				sum[i]=0;//他没有了
				while(!v[i].empty())//找和他连着的人，直到全都找到
				{
					int x=v[i].back();
					v[i].pop_back();
             				//将每个和他连着的人都访问一遍
					k[++l]=x;//记录到k里
				}
			}
		}
		For(i,1,l)sum[k[i]]--;//让出局的人连着的人的连着的人数减少一个
		ans++;//又是一次
	}
	cout<<ans-1;//由于最后一次没有能踢得但还会加1，所以最后要减1
    return 0;
}
```

---

## 作者：_Execution_ (赞：1)

## 思路

简单图论题，只需遍历一遍图，把入度为 $1$ 的点删去（注意需将与其相连的点入度减去 $1$），并累加数量即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, di[101], edge[101];
bool ne[101][101];
int temp = 1, ans = 0;
int main() {
  cin >> n >> m;
  for (int i = 1, a, b; i <= m; i++) {
    cin >> a >> b;
    di[a]++, di[b]++;
    ne[a][b] = 1, ne[b][a] = 1;
  }
  while (temp > 0) {
    memset(edge, 0, sizeof(edge));
    ans++, temp = 0;
    for (int i = 1; i <= n; i++) {
      if (di[i] == 1) {
        edge[temp++] = i;
        di[i]--;
      }
    }
    for (int i = 0; i < temp; i++) {
      for (int j = 1; j <= n; j++) {
        if (ne[edge[i]][j]) {
          di[j]--;
        }
      }
    }
  }
  cout << ans - 1 << endl;
  return 0;
}

```

---

## 作者：马桶战神 (赞：1)

### 一道图论基础题（非最短路，只考概念）

目测普及—难度。~~连我这种蒟蒻都一眼看出来~~

首先建图，为无向图，不会的请学习图论——[洛谷官方的题单](https://www.luogu.com.cn/training/116)

记录每个点的度，每次暴力扫一遍图，遇到度为 $\operatorname{1}$ 的点就删去，并把所有边删除，别忘了把它连的其他点的度减一。

删去的时候需要把每个点存到一个数据结构里，其实直接数组就可以，我因为想到了拓扑排序就用了队列。

详细内容见代码：

```cpp
#include<bits/stdc++.h>     //万能头
using namespace std;
int read()              //快读
{
	int x=0; bool f=true; char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-') f=false;
		c=getchar();
	}
	while(isdigit(c))
		x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return (f?(x):(-x));
}
void write(int x)         //快写
{
	if(!x)
	{
		putchar('0');
		return ;
	}
	char F[130];
	int tmp=x>0?x:-x ,cnt=0;
	if(x<0) putchar('-');
	while(tmp>0)
	{
		F[cnt++]=tmp%10+'0';
		tmp/=10;
	}
	while(cnt>0) putchar(F[--cnt]);
	return ;
}
int n,m,u,v,du[105],tot=0;    //du[i]代表第i个点的度的数量，tot存答案
bool a[105][105];          //邻接矩阵存图
queue<int> q;            //这里也可以用数组
signed main()
{
	memset(du,0,sizeof(du));
	n=read(),m=read();
	for(int i=1;i<=m;++i)
	{
		u=read(),v=read();
		++du[u],++du[v];
		a[u][v]=a[v][u]=true;    //建图
	}
	while(true)
	{
		while(!q.empty())
			q.pop();
		for(int i=1;i<=n;++i)
		{
			if(du[i]==1)
				--du[i],q.push(i);
		}                  //寻找度为1的点并入队
		if(q.empty())
			break;
		else
			++tot;
		while(!q.empty())
		{
			for(int i=1;i<=n;++i)
			{
				if(a[q.front()][i])
					--du[i];   //删点
			}
			q.pop();
		}
	}
	write(tot);
	return 0;          //结束程序
}
```


---

## 作者：Norsuman371 (赞：0)

# 思路

每次先处理鞋带与外界绑定数为 $1$。由于是无向图，无所谓出度入度。直接进行拓扑排序的同时，计算所进行的总轮数。

# 代码
```cpp
#include<bits/stdc++.h>

using namespace std;
int deg[105], n, m;
vector < int > to[105];
int topsort() {
    queue < int > qu;
    int i, go = 1, sum = 0;
    while (go) {
        go = 0;
        for (i = 1; i <= n; i++)
            if (deg[i] == 1) {
                qu.push(i);
                go = 1;
            }
        while (!qu.empty()) {
            int a = qu.front();
            qu.pop();
            deg[a]--;
            for (i = 0; i < to[a].size(); i++)
                deg[to[a][i]]--;
        }
        if (go) sum++;
    }
    return sum;
}
int main() {
    ios::sync_with_stdio(false);
    int u, v;
    int i, j, k;
    cin >> n >> m;
    for (i = 1; i <= m; i++) {
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    cout << topsort() << endl;
    return 0;
}
```

# 记录

[AC](https://www.luogu.com.cn/record/163120585)

---

## 作者：Dream_Mr_li (赞：0)

## 题目分析

题目要求我们确定学生组的数量，其中学生之间通过鞋带相连。我们可以将学生视为图中的节点，鞋带相连的学生视为图中的边。我们的目标是找出图中的连通分量数量，即学生组的数量。

## 算法思路

我们可以使用图论的方法来解决这个问题。具体步骤如下：

1. 构建图的邻接矩阵表示，同时记录每个顶点的度数。

2. 使用队列存储度数为 $1$ 的顶点，表示当前轮次需要删除的顶点。

3. 不断从队列中取出顶点，并删除与之相邻的边，更新相邻顶点的度数。每次删除一个顶点后，检查相邻顶点的度数是否变为 $1$，如果是，则将其加入队列。

4. 每删除一轮，连通分量数量加 $1$，直到队列为空。

## 复杂度分析

- 时间复杂度：$O(n^2)$，其中 $n$ 是顶点的数量。因为在每轮操作中，需要遍历邻接矩阵来更新度数，而邻接矩阵的大小为 $n \times n$。

- 空间复杂度：$O(n^2)$，需要存储邻接矩阵和度数数组。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;

int main() {
    // 读入学生数量和鞋带数量
    cin >> n >> m;

    // 存储每个顶点的度数
    vector<int> degree(n + 1, 0);
    // 使用邻接矩阵存储边的信息
    vector<vector<bool>> adj_matrix(n + 1, vector<bool>(n + 1, false));

    // 读取边的信息并更新度数和邻接矩阵
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        degree[a]++;
        degree[b]++;
        adj_matrix[a][b] = adj_matrix[b][a] = true;
    }

    // 使用队列存储每轮需要删除的顶点
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) {
            q.push(i);
        }
    }

    int components = 0;

    // 不断删除度数为1的顶点直到图为空
    while (!q.empty()) {
        int size = q.size(); // 记录当前轮次需要删除的顶点数量
        for (int i = 0; i < size; ++i) {
            int node = q.front();
            q.pop();
            degree[node] = 0; // 将当前顶点度数置零
            for (int j = 1; j <= n; ++j) {
                if (adj_matrix[node][j]) {
                    degree[j]--; // 更新与当前顶点相邻的顶点的度数
                }
            }
        }
        components++; // 每删除一轮，连通分量数量加1
        // 将新的度数为1的顶点加入队列
        for (int i = 1; i <= n; ++i) {
            if(degree[i]==1){
                q.push(i);
            }
        }
    }

    // 输出连通分量的数量
    cout << components << endl;

    return 0;
}
```
## 总结

本题使用图论中的邻接矩阵和队列的方法，通过不断删除度数为 $1$ 的顶点，最终确定学生组的数量。

---

