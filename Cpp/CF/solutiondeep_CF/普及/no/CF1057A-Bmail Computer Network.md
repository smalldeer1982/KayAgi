# 题目信息

# Bmail Computer Network

## 题目描述

Once upon a time there was only one router in the well-known company Bmail. Years went by and over time new routers were purchased. Every time they bought a new router, they connected it to one of the routers bought before it. You are given the values $ p_i $ — the index of the router to which the $ i $ -th router was connected after being purchased ( $ p_i < i $ ).

There are $ n $ routers in Boogle in total now. Print the sequence of routers on the path from the first to the $ n $ -th router.

## 样例 #1

### 输入

```
8
1 1 2 2 3 2 5
```

### 输出

```
1 2 5 8 ```

## 样例 #2

### 输入

```
6
1 2 3 4 5
```

### 输出

```
1 2 3 4 5 6 ```

## 样例 #3

### 输入

```
7
1 1 2 3 4 3
```

### 输出

```
1 3 7 ```

# AI分析结果

### 题目内容翻译

**Bmail计算机网络**

**题目描述**

从前，著名的Bmail公司只有一个路由器。随着时间的推移，公司购买了新的路由器。每次购买新路由器时，都会将其连接到之前购买的一个路由器上。给定每个路由器$i$的连接信息$p_i$，表示第$i$个路由器在购买后连接到的路由器的索引（$p_i < i$）。

现在Bmail公司共有$n$个路由器。请输出从第1个路由器到第$n$个路由器的路径序列。

**样例 #1**

**输入**

```
8
1 1 2 2 3 2 5
```

**输出**

```
1 2 5 8
```

**样例 #2**

**输入**

```
6
1 2 3 4 5
```

**输出**

```
1 2 3 4 5 6
```

**样例 #3**

**输入**

```
7
1 1 2 3 4 3
```

**输出**

```
1 3 7
```

### 算法分类
**递归**

### 题解分析与结论

#### 题解对比
1. **A_Đark_Horcrux**：采用逆向思维，从第$n$个路由器开始，通过父节点回溯到第1个路由器，记录路径后反向输出。思路清晰，代码简洁，时间复杂度为$O(n)$。
2. **asasas**：同样采用逆向思维，从第$n$个路由器回溯到第1个路由器，记录路径后倒序输出。代码中使用了`sort`函数，虽然不影响结果，但增加了不必要的复杂度。
3. **Paranoia__zzy**：通过记录每个节点的父节点，从第$n$个路由器回溯到第1个路由器，记录路径后倒序输出。代码中单独处理了节点1，避免了死循环，但代码略显冗余。
4. **午尘**：从第$n$个路由器回溯到第1个路由器，记录路径后倒序输出。代码简洁，但使用了`fa[1]=0`来标记根节点，增加了额外的判断。
5. **gary2005**：采用递归的方式，从第$n$个路由器回溯到第1个路由器，直接输出路径。思路清晰，代码简洁，但递归深度较大时可能影响性能。
6. **damage**：采用逆向思维，使用栈结构记录路径，从第$n$个路由器回溯到第1个路由器，最后输出栈中的路径。思路清晰，代码简洁，时间复杂度为$O(n)$。

#### 最优关键思路
- **逆向思维**：从第$n$个路由器回溯到第1个路由器，记录路径后反向输出。
- **数据结构**：使用栈或数组记录路径，避免递归带来的性能问题。

#### 可拓展之处
- 类似题目可以考察树结构中的路径查找，如二叉树中从根节点到某个叶子节点的路径。
- 可以结合深度优先搜索（DFS）或广度优先搜索（BFS）进行路径查找。

### 推荐题目
1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

### 精选题解

#### 题解1：A_Đark_Horcrux
**星级**：★★★★★
**关键亮点**：逆向思维，代码简洁，时间复杂度低。
**核心代码**：
```cpp
int n,now,l,i,fa[N],a[N];
int main()
{
	n=read(); now=n;
	for(i=2;i<=n;i++) fa[i]=read();
	do a[++l]=now,now=fa[now]; while(now!=1);
	printf("1 "); for(i=l;i>=1;i--) printf("%d ",a[i]);
	return 0;
}
```

#### 题解2：damage
**星级**：★★★★★
**关键亮点**：使用栈记录路径，代码简洁，时间复杂度低。
**核心代码**：
```cpp
int n,p[200010];
stack<int> path;
int main()
{
    scanf("%d",&n);
    for(register int i=2;i<=n;++i) scanf("%d",&p[i]);
    path.push(n);
    while(n!=1)
    {
        n=p[n];
        path.push(n);
    }
    while(!path.empty())
    {
        printf("%d ",path.top());
        path.pop();
    }
    return 0;
}
```

#### 题解3：gary2005
**星级**：★★★★
**关键亮点**：递归实现，代码简洁，但递归深度较大时可能影响性能。
**核心代码**：
```cpp
int n,up[200005];
void dfs(int now){
	if(now!=1) dfs(up[now]);
	cout<<now<<" ";
}
int main(){
	cin>>n;
	for(int i=2;i<=n;i++) cin>>up[i];
	dfs(n);
	return 0;
}
```

### 个人心得
- **逆向思维**：在树结构问题中，逆向思维往往能简化问题，尤其是在路径查找类题目中。
- **数据结构选择**：栈结构在处理路径记录时非常高效，避免了递归带来的性能问题。

---
处理用时：37.68秒