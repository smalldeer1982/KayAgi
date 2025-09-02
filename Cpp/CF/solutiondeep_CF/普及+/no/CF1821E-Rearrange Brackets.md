# 题目信息

# Rearrange Brackets

## 题目描述

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- bracket sequences ")(", "(" and ")" are not.

You are given a regular bracket sequence. In one move, you can remove a pair of adjacent brackets such that the left one is an opening bracket and the right one is a closing bracket. Then concatenate the resulting parts without changing the order. The cost of this move is the number of brackets to the right of the right bracket of this pair.

The cost of the regular bracket sequence is the smallest total cost of the moves required to make the sequence empty.

Actually, you are not removing any brackets. Instead, you are given a regular bracket sequence and an integer $ k $ . You can perform the following operation at most $ k $ times:

- extract some bracket from the sequence and insert it back at any position (between any two brackets, at the start or at the end; possibly, at the same place it was before).

After all operations are performed, the bracket sequence has to be regular. What is the smallest possible cost of the resulting regular bracket sequence?

## 样例 #1

### 输入

```
7
0
()
0
(())
1
(())
5
()
1
(()()(()))
2
((())()(()())((())))
3
((())()(()())((())))```

### 输出

```
0
1
0
0
1
4
2```

# AI分析结果

### 题目内容重写

#### 重排括号

**题目描述**

一个合法的括号序列是指可以通过在原始序列的字符之间插入字符“1”和“+”将其转换为正确的算术表达式的括号序列。例如：

- 括号序列“()()”和“(())”是合法的（转换后的表达式分别为：“(1)+(1)”和“((1+1)+1)”）；
- 括号序列“)(”、“(”和“)”是不合法的。

给定一个合法的括号序列。在一次操作中，你可以移除一对相邻的括号，其中左边是左括号，右边是右括号。然后将剩余部分按原顺序拼接。这次操作的代价是这对右括号右边的括号数量。

这个合法括号序列的代价是使其变为空序列所需的最小总代价。

实际上，你并不移除任何括号。相反，你给定一个合法的括号序列和一个整数 $k$。你最多可以执行以下操作 $k$ 次：

- 从序列中提取一个括号并将其插入到任意位置（可以在任意两个括号之间、开头或结尾；也可以插入到原来的位置）。

在所有操作完成后，括号序列必须仍然是合法的。问最终得到的合法括号序列的最小可能代价是多少？

**样例 #1**

### 输入

```
7
0
()
0
(())
1
(())
5
()
1
(()()(()))
2
((())()(()())((())))
3
((())()(()())((())))
```

### 输出

```
0
1
0
0
1
4
2
```

### 算法分类
贪心

### 题解分析与结论

这道题的核心在于如何通过移动括号来最小化删除括号的代价。题解中主要采用了贪心策略，通过计算每对括号的深度或嵌套层数，并优先减少深度较大的括号对来优化总代价。

### 所选题解

#### 题解作者：uid_310801 (赞：5)

**星级：5星**

**关键亮点：**
1. **贪心策略**：通过计算每对括号的深度，优先减少深度较大的括号对，从而最小化总代价。
2. **代码简洁**：利用栈结构计算每对括号的深度，并通过排序选择前 $k$ 个最大的减少量。

**核心代码：**
```cpp
void work(){
	scanf("%lld",&k);
	scanf("%s",c+1);
	n=strlen(c+1);
	ll de=0,ans=0;
	stack<ll> s;
	vector<pii> v;
	for(ll i=1;i<=n;i++){
		if(c[i]=='('){
			de++;
			s.push(i);
		}
		else{
			de--;
			dep[i]=de;
			ans+=de;
			L[i]=s.top();
			s.pop();
			v.push_back(mp(-i+L[i]-1,i));
		}
	}
	sort(v.begin(),v.end());
	for(int i=0;i<min(ll(v.size()),k);i++){
		ans-=-v[i].fi/2-1;	
	}
	printf("%lld\n",ans);
}
```

#### 题解作者：小木虫 (赞：2)

**星级：4星**

**关键亮点：**
1. **括号树模型**：通过构建括号树，将问题转化为树的结构，便于计算每对括号的贡献。
2. **子树大小排序**：通过排序子树大小，优先减少较大的子树，从而优化总代价。

**核心代码：**
```cpp
void solve(){
	cin>>k>>S;n=S.size();S=" "+S;
	int now=cnt=1;
	for(int i=1;i<=n;i++){
		if(S[i]=='('){
			fa[cnt+1]=now;
			edge[now].push_back(cnt+1);
			now=++cnt;
		}else{
			now=fa[now];
		}
	}dfs(1);int res=0;
	for(int i=2;i<=cnt;i++)
		res+=sz[i]-1;
	sort(sz+2,sz+cnt+1,greater<int>());
	for(int i=2;i-1<=k&&i<=cnt;i++)
		res-=sz[i]-1;
	cout<<res<<"\n";
}
```

#### 题解作者：guanyf (赞：1)

**星级：4星**

**关键亮点：**
1. **从右往左删除**：通过从右往左遍历，优先删除最右边的括号对，减少总代价。
2. **移动括号的优化**：通过记录每对括号之间的距离，并选择前 $k$ 个最大的减少量，优化总代价。

**核心代码：**
```cpp
void solve() {
  cin >> k >> s, n = s.size(), s = ' ' + s;
  tot = ans = m = 0;
  for (int i = n; i >= 1; i--) {
    if (s[i] == '(') {
      a[++m] = (st[tot] - i) / 2, ans += --tot;
    } else {
      st[++tot] = i;
    }
  }
  sort(a + 1, a + 1 + m, greater<int>());
  for (int i = 1; i <= min(m, k); i++) ans -= a[i];
  cout << ans << '\n';
}
```

### 最优关键思路与技巧
1. **贪心策略**：优先减少深度较大的括号对，从而最小化总代价。
2. **栈结构**：利用栈结构计算每对括号的深度，便于后续优化。
3. **排序优化**：通过排序选择前 $k$ 个最大的减少量，进一步优化总代价。

### 可拓展之处
1. **括号序列的深度计算**：可以应用于其他涉及括号深度的问题，如括号匹配、括号嵌套等。
2. **贪心策略的应用**：类似的贪心策略可以应用于其他需要优先处理某些元素的问题，如任务调度、资源分配等。

### 推荐题目
1. [P1044 括号匹配](https://www.luogu.com.cn/problem/P1044)
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
3. [P1972 括号序列](https://www.luogu.com.cn/problem/P1972)

---
处理用时：47.41秒