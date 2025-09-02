# Divisor Tree

## 题目描述

A divisor tree is a rooted tree that meets the following conditions:

- Each vertex of the tree contains a positive integer number.
- The numbers written in the leaves of the tree are prime numbers.
- For any inner vertex, the number within it is equal to the product of the numbers written in its children.

Manao has $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ . He tries to build a divisor tree which contains each of these numbers. That is, for each $ a_{i} $ , there should be at least one vertex in the tree which contains $ a_{i} $ . Manao loves compact style, but his trees are too large. Help Manao determine the minimum possible number of vertices in the divisor tree sought.

## 说明/提示

Sample 1. The smallest divisor tree looks this way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337E/71b2187cbd06bdd466a640fb3fba452ed4239e72.png)

Sample 2. In this case you can build the following divisor tree: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337E/983e0e8e1e41f9fa18f4f08eec9d634ad5efd21c.png)

Sample 3. Note that the tree can consist of a single vertex.

## 样例 #1

### 输入

```
2
6 10
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4
6 72 8 4
```

### 输出

```
12
```

## 样例 #3

### 输入

```
1
7
```

### 输出

```
1
```

# 题解

## 作者：Argon_Cube (赞：1)

当我第一次看到这题时，我就思考着是不是有什么 $\Theta(n)$ 的建树方式……直到我看到了 $1\leq n\leq 8$。

我小声的说了一句：这不是 $\Theta(n^n)$ 都能过吗……然后我给 Grey 看了一看。

Grey：这不是 $\Theta(n^n)$ 都能过吗！

最后，我打出来的解复杂度：$\operatorname O(n^n)$……好吧，果然是 $\operatorname O(n^n)$ 都能过。

* **【题目链接】**

[Link:CF337E](https://www.luogu.com.cn/problem/CF337E)

* **【解题思路】**

有一件很显然的事情：想要减少结点个数，我们可以让一个 $a_i$ 成为另一个 $a_j$ 的子结点。比如说，$6$ 成为 $30$ 的子结点，相比 $6$ 独立为一个子树可以少两个结点：$2,3$。

还有一件很显然的事情：如果一个 $a_i$ 成为另一个 $a_j$ 的子结点，那么有 $a_i|a_j$。

以及，如果一群数可以作为某个数的子结点，那么他们的积应该可以被这个数整除。

现在，问题变成：如何安排这些结点作为谁的子结点才能让节省的结点数最多？看到 $1\leq n\leq 8$，大家应该就能明白 $\operatorname O(n^n)$ 的复杂度怎么来的吧……

直接暴力搜索。事实上，加上剪枝后程序跑得飞快。

那么，怎么计算结果呢？（以下内容请配合程序阅读。）

我们首先考虑一个最暴力的建树方法：

我们让根节点为所有 $a_i$ 的积，它连接着 $n$ 个子结点，第 $i$ 个子结点为 $a_i$。每个 $a_i$ 的所有子结点是它所有的质因数。看起来就像样例 $1$。如果把 $a=[3,10,77,221]$ 建出来的话是这样的：

![Hi There](https://cdn.luogu.com.cn/upload/image_hosting/sn9vewh2.png)

设 $a_i$ 的质因数个数为 $b_i$，则按这种方式建树的结点数为：

$$1+n+\sum_{i=1}^n[b_i\neq 1]b_i$$

为什么要有一个 $[b_i\neq 1]$ 呢？因为，看看那个 $3$，它本身就是个质数，不需要再有子结点了。而 $[b_i=1]$ 意味着 $a_i$ 为质数，如果依然加上 $b_i$ 的话，会导致多算一个结点。实际操作中，我用容斥转化为：

$$1+n+\sum_{i=1}^nb_i-\sum_{i=1}^n[a_i\in\mathbb P]$$

其中 $\mathbb P$ 为质数集。

接着我们暴力搜索。当我们发现可以将某个 $a_i$ 作为 $a_j$ 的子结点时，我们可以发现，这样做会减少 $b_i$ 个结点。我们边搜边统计就行了，搜完更新答案。不过，将  $a_i$ 独立出来，不作为单独的子树根也是一种可能，记得在开头先搜一遍。

不过，事实令人失望。你会发现，如果只用上面的思路，你过不了样例 $3$。那么，我们特判只有一个质数就行了。

**真的行了吗？**

交上去，$\color{red}\text{Wrong answer on Testcase }7$。

显然，我们没有判这种情况：$a=[2,3,6]$。

那么，我们再判一下，是否有一个数可以作为所有其它数的父结点。如果有，那么将答案减一，因为我们不再需要原来的根节点。

**可是，真的是对的吗？**

交上去，$\color{red}\text{Wrong answer on Testcase }8$。

好的。现在我们应该知道究竟问题出在哪了。

让我们想想。我们的建树方式是，一个根结点连着所有 $a_i$。当我们把某个数作为另一个数的子结点时，我们只是单纯的把这个数移走，然后改变根节点的值。

**万一，某个 $a_i$ 可以作为根结点呢？**

比如，$a=[2,3,5,6,30]$。

如果按照我们前面的方法建树，最后根结点是 $30$，它的子结点只有一个：$30$。

为什么会多出来一个冗余的根结点？

究其原因，是因为 $30$ 本身就可以做根结点。

那么，这个情况什么时候才能出现？

显然，当除了最大值的所有结点都找到了数组中的某个数作为自己的父节点时，以最大值为根的子树已经包含了整个数组。

那么，我们就要特判这种情况。当出现这种情况时，将当前搜得的答案减一。

现在，我们可以把前两个特判删去了。

时间复杂度 $\operatorname O(n^n+n\sqrt{a_i})$。

* **【实现细节】**

分解质因数时记得开`long long`，否则你会 $\text{Time Limit Exceeded on Testcase }5$。还有，相乘时可能爆`long long`，请用除法判断积是否超过某个数。

* **【代码实现】**

```cpp
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

vector<unsigned long long> nums,DFS_arr,cnt_factor;
vector<unordered_map<unsigned long long,unsigned long long>> factors;

/*
depth：目前搜到第几个数
max_num：最大值
all_aloced：除了最大值外当前是否已经搜过的数都找到父结点
curans：当前的答案
answer：全局答案
*/
void DFS(int depth,const unsigned long long max_num,bool all_aloced,unsigned long long curans,unsigned long long& answer)
{
	if(depth==nums.size())
		return (void)(answer=min(answer,curans-all_aloced));
	DFS(depth+1,max_num,all_aloced&&nums[depth]==max_num,curans,answer);//当前这个数不选某个数作为父结点
	for(int i=0;i<nums.size();i++)
		if(i!=depth)
			if(nums[i]/DFS_arr[i]%nums[depth]==0&&DFS_arr[i]<=nums[i]/nums[depth])
				DFS_arr[i]*=nums[depth],curans-=cnt_factor[depth],DFS(depth+1,max_num,all_aloced,curans,answer),curans+=cnt_factor[depth],DFS_arr[i]/=nums[depth];
}

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	unsigned long long answer=1,cnt,cnt_prime=0,maxnum=0,rest_mult=1;
	cin>>cnt;
	factors.resize(cnt);
	nums.resize(cnt);
	DFS_arr.resize(cnt);
	cnt_factor.resize(cnt);
	for(int i=0;i<cnt;i++)//初始化
		cin>>nums[i],maxnum=max(maxnum,nums[i]),DFS_arr[i]=1;
	for(int i=0;i<cnt;i++)//分解质因数
	{
		long long tmp=nums[i];
		bool is_prime=true;
		for(long long j=2;j*j<=tmp;j++)
			while(tmp%j==0)
				factors[i][j]++,cnt_factor[i]++,tmp/=j,is_prime=false;
		if(tmp!=1)
			factors[i][tmp]=1,cnt_factor[i]++;
		cnt_prime+=is_prime;
	}
	for(int i=0;i<cnt;i++)//暴力建树节点个数
	{
		for(const auto& tmp:factors[i])
			answer+=tmp.second;
		answer+=1;
	}
	answer-=cnt_prime;//容斥
	DFS(0,maxnum,true,answer,answer);//搜索
	cout<<answer;
	return 0;
}
```

---

