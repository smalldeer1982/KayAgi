# Friends and Gifts

## 题目描述

There are $ n $ friends who want to give gifts for the New Year to each other. Each friend should give exactly one gift and receive exactly one gift. The friend cannot give the gift to himself.

For each friend the value $ f_i $ is known: it is either $ f_i = 0 $ if the $ i $ -th friend doesn't know whom he wants to give the gift to or $ 1 \le f_i \le n $ if the $ i $ -th friend wants to give the gift to the friend $ f_i $ .

You want to fill in the unknown values ( $ f_i = 0 $ ) in such a way that each friend gives exactly one gift and receives exactly one gift and there is no friend who gives the gift to himself. It is guaranteed that the initial information isn't contradictory.

If there are several answers, you can print any.

## 样例 #1

### 输入

```
5
5 0 0 2 4
```

### 输出

```
5 3 1 2 4 
```

## 样例 #2

### 输入

```
7
7 0 0 1 4 0 6
```

### 输出

```
7 3 2 1 4 5 6 
```

## 样例 #3

### 输入

```
7
7 4 0 3 0 5 1
```

### 输出

```
7 4 2 3 6 5 1 
```

## 样例 #4

### 输入

```
5
2 1 0 0 0
```

### 输出

```
2 1 4 5 3 
```

# 题解

## 作者：OnlyJerry (赞：8)

这道算法题可以用环图做！

通过读题我们发现，每个人都应当送出一份礼物，也会收到礼物，但不能自己给自己一份礼物。

从而可将此题转化为一个序列，不能自己给自己礼物就等价于序列中元素的值不能与它的位置相等。

即

$$i \neq v[i]$$

因为位置与数值是一一对应的，所以我们可以从位置向数值连一条有向边，构成环。

构建完图之后，由于有空缺的数据，所以这个环是不完整的。

要构成一一对应的关系，就转换成了要将这个环补全。

由于 $i \neq v[i]$ ，即 $i$ 不能向 $v[i]$ 连一条边，所以也就不能出现负环。

因此我们可以总结成三种情况：

$1$ 有多个环，且有缺口。

$2$ 环中缺口可插入需要补全的元素。

$3$ 环无缺口。

对于以上三种情况，我们可以分类讨论出解决方法：

$Key1$ 将有缺口的环首尾相连。

$Key2$ 将需要补全的元素按照补全的原则补到缺口中。

$Key3$ 将剩下的元素互相相连，即“抱团取暖”。

因此，我们将问题转化成了用所有的元素构建一个（或多个）完整的环图，使得满足没有负环。

看到这里的同学，可以自己试着去写写代码了（~~tf口吻~~）

```
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=200005;
int p[N],q[N],st[N];//p为正向边，q为反向边，st为标记数组
int n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);//添加正向边
        q[p[i]]=i;//添加反向边
    }
    bool flag=false;//判断是否填补所有的空缺元素
    for(int i=1;i<=n;i++)
    {
        if(st[i] || !q[i]) continue;//打过标记或没有下一个点的点跳过
        st[i]=true;//打上标记
        int x=i,y=i;//x和y分别表示环的尾和头
        while(p[x] && !st[p[x]])//当x有下一个点并且没有走过时
        {
            x=p[x];//更新环的尾
            st[x]=true;//打标记
        }
        while(q[y] && !st[q[y]])//同理通过反向边向前走
        {
            y=q[y];
            st[y]=true;
        }
        if(p[x]==y) continue;//如果连通，则跳过
        if(!flag)//判断是否处理过没有出现的点
        {
            flag=true;//打标记，表示处理过了
            for(int j=1;j<=n;j++)
            {
                if(!q[j] && !p[j])//如果这个点是孤立的 即key2操作
                {
                    st[j]=true;//打标记
                    p[x]=j;//把这个点放到环的尾部
                    x=j;//更新环的尾
                }
            }
        }
        p[x]=y;//把环连起来 即key1操作
    }
    if(!flag)//如果还有没处理完的点就抱团取暖 即key3操作
    {
        int x=0,y=0;
        for(int i=1;i<=n;i++)
        {
            if(!p[i])//如果没有连通的点，即没有处理过
            {
                if(!x && !y) x=y=i;//如果是这个抱团取暖环的第一个元素，那么他的首尾都附上它本身
                else
                {
                    p[x]=i;//把这个点放到环的尾部
                    x=i;//更新环的尾
                }
            }
        }
        p[x]=y;//把抱团取暖环连起来
    }
    for(int i=1;i<=n;i++)
    {
        printf("%d ",p[i]);//输出每个位置所连得下一个点即为答案
    }
    return 0;
}            
```

谢谢各位巨佬们的阅读，可以给一个小小的赞嘛，Thanks♪(･ω･)ﾉ

---

## 作者：brimosta (赞：6)

### Description:
此题中，我们要让每个人都能送出礼物并收到礼物，也就是要排除自己送自己的情况。
### Solution:
首先，在 $A$ 中存所有没有送礼物的人， $B$ 中存储所有没有收到礼物的人。

例如
```
5
5 0 0 2 4
```
中
```
A = {2,3}
B = {2,3}
```
此时让每一个 $A[i]$ 和 $B[i]$ 进行配对，但是不能送给自己，所以当$A[i]$ = $B[i]$ 的时候，先把$b[i]$ 和 $B[i+1]$ 互换，再进行配对。

例如，当`A = {2,3},B = {2,3}`时$A[1]$ = $B[1]$ ，所以 $B$ 变为`B = {3,2}`后再进行配对。

当$A$的最后一个数=$B$的最后一个数时，把$B[i]$ 和 $B[1]$ 互换，再重新对 $A[1]$ 进行配对，并对$A[i]$ 和 $B[i]$ 进行配对。

### Code:
```cpp
#include <bit/stdc++.h>
using namespace std;
int n;
int a[200001];//a[i] = j 表示第i个人的礼物送给了第j个人
int A[200001];
bool b[200001];
int B[200001];
int main()
{
	cin >> n;
	for(int i = 1；i <= n；i++)
	{
		scanf("%d",&a[i]);
		b[a[i]] = true;//记录第a[i]个人被送过礼物
		if(a[i] == 0) A[++A[0]] = i;//记录还未送出礼物的人
	}
	for(int i = 1；i <= n；i++) if(b[i] == 0) B[++B[0]] = i;//记录 还未收到礼物的人
	for(int i = 1；i <= A[0]；i++)//对每一个没送出礼物的人进行配对
	{
		if(A[i] == B[i])//如果此时是自己送给自己，前文有讲
		{
			if(i != A[0])//此时不是最后一个的时候，交换i和i+1
			{
				swap(B[i],B[i+1]);
			}
			else//此时是最后一个，那就与第一个交换
			{
				swap(B[1],B[i]);
				a[A[1]] = B[1];
			}
		}
		a[A[i]] = B[i];
	}
	for(int i = 1;i <= n;i++) printf("%d ",a[i]);//输出每个人的送礼对象
		return 0;
}
```
不要复制代码哦！

---

## 作者：HoshizoraZ (赞：6)

题目可以想象在一张图上，把每个同学看成点，送礼关系看成边。

我们只关注每个点的入度与出度，因为它可以表示同学送礼与收礼情况。

对于 $f_i=j\;(1 \le i,j \le n,\;i≠j)$ 的情况，将第 $i$ 个点出度加 $1$，第 $j$ 个点入度加 $1$（可以看成从 $i$ 到 $j$ 连一条单向边）。

那么就会出现一些特征不同的节点，分成四类：

1. 入度出度均为 $1$；
2. 入度出度均为 $0$；
3. 入度为 $1$，出度为 $0$；
4. 入度为 $0$，出度为 $1$。

其中，第 $1$ 类点不需要处理，而且第 $3$ 和第 $4$ 类点可以进行匹配。

那问题就转化成如何处理第 $2$ 类点。

讨论两种情况：

- 第 $2$ 类点个数只有 $1$ 个，那么它可以让一个第 $3$ 类点连向它，让第 $3$ 类点变成第 $1$ 类，自己变成第 $3$ 类点，之后再让第 $3$、$4$ 类点匹配；

- 第 $2$ 类点不止 $1$ 个时，我们可以让所有第 $2$ 类点组成封闭的环，使其全部变成第 $1$ 类点，再让第 $3$、$4$ 类点匹配。

**注意到，一张有向图的节点入度和等于出度和，而第 $1$、$2$ 类点入出度均相等，所以第 $3$ 类点一定可以和第 $4$ 类点两两匹配。**

当所有点变成第 $1$ 类点时，匹配即完成。

**参考代码：**

```cpp
#include <cstdio>

int n, a, in[200010], out[200010], ans[200010];
int aa[200010], bb[200010], cc[200010], cnt, k, s1, s2, s3;

int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a), a > 0 ? out[i]++, in[a]++, ans[i] = a : 0;
	
	for(int i = 1; i <= n; i++)
		if(!in[i] && !out[i])
			k = i, cnt++;

	// 处理第 2 类点只有 1 个的情况
	if(cnt == 1){
		for(int i = 1; i <= n; i++)
			if(in[i] && !out[i]){
				out[i] = 1, ans[i] = k, in[k] = 1;
				break;
			}
	}
   
	// 将第 3 类点与第 4 类点进行匹配
	for(int i = 1; i <= n; i++){
		if(in[i] && !out[i])
			aa[++s1] = i;
		if(!in[i] && out[i])
			bb[++s2] = i;
	}
	for(int i = 1; i <= s1; i++)
		out[aa[i]] = 1, in[bb[i]] = 1, ans[aa[i]] = bb[i];
	
	// 处理第二类点至少有 2 个的情况
	for(int i = 1; i <= n; i++)
		if(!in[i] && !out[i])
			cc[++s3] = i;
	
	for(int i = 1; i < s3; i++)
		out[cc[i]] = 1, ans[cc[i]] = cc[i + 1], in[cc[i + 1]] = 1;
	ans[cc[s3]] = cc[1];		// 首尾相接形成环
	
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	puts("");

	return 0;
}
```

---

## 作者：_xxxxx_ (赞：2)

### 题意

给出 $n$ 和一个 $n$ 个数的正整数数组 $a$，现在要求每个人都**送出一个礼物并且收到一个礼物**。其中，有一些人已经送完礼物了，请你填好是 $0$ 的位置。另外，自己不能送给自己。

### 分析

因为 $n\le 2\times 10^{5}$，不能 $O(n^2)$ 暴力做，所以要考虑更快速的算法。

我们可以先记录下来谁没有送礼物，谁没有收到礼物，然后让每一个没送礼物送给一个没收到礼物的。

但是，自己不能送给自己。所以如果出现一个人没送礼物并且没收礼物可能会送给自己。要处理这个问题其实很简单，把还没收到礼物的下一个人与他交换就可以了。

这样处理的话，还是会出现一个问题。当到了 $n$ 的时候也会自己送自己，就不可以交换了。这样，只能从前面的**原本没送礼物**的人选一个换，注意换完把交换后的影响从数组中改变。

这样，每次记录换完的 $a$ 数组，最后将其输出就行了。

### 代码

```
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, a[N], inx[N], out[N], in[N];
//   in是还需收礼物，out是还需送礼物 
int leno, leni;
/*
leno:没送的人的个数
leni:没收的人的个数
*/ 
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		inx[a[i]] = 1;//送出过礼物 
		if(a[i] == 0)
		{
			out[++leno] = i;//记录下没送的 
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(inx[i] == 0)
		{
			in[++leni] = i;//没送过礼物，就是还需要送礼物 
		}
	}
	for(int i = 1; i <= leno; i++)
	{
		if(out[i] == in[i])//自己送自己 
		{
			if(i == leno)
			{
				swap(in[i], in[1]);//找一个换 
				a[out[1]] = in[1];//影响了 
			}
			else
			{
				swap(in[i], in[i + 1]);//和下一个人换 
			}
		}
		a[out[i]] = in[i];//记录下来 
	}
	for(int i = 1; i <= n; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}
```

---

## 作者：Wander_E (赞：1)

这道题其实不一定非得建图，也可以直接从序列出发来考虑。

为了让每个人都领到礼物 $f$ 必须是 $n$ 的一个**排列**。
所以就可以记录哪些数没有在 $f$ 中出现过，记为 $ans$。

由于自己不能给自己送礼物，所以当 $ans_i=i$ 时，就将 $ans_i$ 和 $ans_{i+1}$ 交换，特别的，$ans_n$ 应当与 $ans_1$ 交换。

附上 AC 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n;
int f[N];
map<int, bool> vis;
int ans[N], top;

signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> f[i], vis[f[i]] = f[i];
	for(int i = 1; i <= n; i++)
		if(!vis[i]) ans[++top] = i;
	for(int i = 1, j = 0; i <= n; i++)
		if(f[i] == 0 && ans[++j] == i) 
		{
			if(j < top) swap(ans[j], ans[j + 1]);
			else swap(ans[j], ans[1]);
		}
	for(int i = 1, j = 0; i <= n; i++)
	{
		if(f[i] == 0) f[i] = ans[++j];
	}
	for(int i = 1; i <= n; i++) 
		cout << f[i] << ' ';
	return 0;
}

```

---

## 作者：W1nNy_ (赞：1)

##  _题目大意_ 

给定一个非负整数序列 $f$ ,其中某几位被删掉了，为0，让我们在每一个0中填上一个适当的数 $f[i]$ 要求 $\forall f[i] \neq i $。

##  _Solution_ 

可以构造环图，运用图论的知识解决，参见[OnlyJerry的博客](https://www.luogu.com.cn/blog/OnlyJerry-2006/solution-cf1283c)，

但是由于我是个蒟蒻，不会环图，所以我用模拟和贪心的做法解决这道题。

首先预处理出需要填充的数，存到 $ans$ 数组中。

将 $ans$ 数组向右整体平移一下？ 正确性不能保证。

所以我们每一个枚举每一个 $a[\,i\,]$。

如果 $!a[\,i\,]$ ,将 $ans[\,top\,]$ 和 $i$ 进行比较，如果他们相等，则交换一下 $ans[\,top\,]$ 和 $ans[\,top+1\,]$。

当然如果 $top==n$ 的话，交换第一个元素与第n个元素。

通过这种贪心做法，不仅保证了正确性，而且可以在 $O(N)$ 的时间内完成操作，上代码：[code](https://www.luogu.com.cn/paste/vqezbw21)。



---

## 作者：Ak_hjc_using (赞：0)

### 思路：

考虑模拟。

首先遍历数组，找到所有未出现的值，存入数组 $b$ 中，设共有 $m$ 个未出现的值。

题意要保证 $i \neq f(i)$，由于 $i$ 是单调递增的，那我们首先让 $f(i)$ 单调递减，并一一对应到原数组中空的位置上，这样最多只会有一个位置出现 $i=f(i)$ 的情况。

如何解决这种情况呢？我们记录第一个和最后一个数值 $f(1)$ 和 $f(m)$ 插入的位置，并选择其中一个与 $f(i)$ 对调。举个例子，在 $i>1$ 时，$f(1)>f(i)=i>1$，所以我们将二者对调后，结果是 $f(1)$ 对应 $i$，$f(i)$ 对应 $1$，不会出现相等的情况。

与 $f(m)$ 互换同理。但由于 $f(i)$ 可能是 $f(1)$ 和 $f(m)$ 其中的一个（也即在 $1$ 或 $m$ 位置出现了冲突），所以需要记录两个位置，选择与其中一个没有冲突的位置互换。

### 代码：

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
signed main() 
{
    int n;
    cin >> n;
    vector<int> f(n + 1);
    vector<bool> exist(n + 1, false);
    // 先找到所有 f(i)，存到数组 b 中
    for(int i = 1 ; i <= n; i++) 
	{
        cin >> f[i];
        if(f[i] != 0) exist[f[i]] = true; 
    }
    vector<int> b;
    for(int i = 1; i <= n; i++) 
	{
        if(!exist[i]) b.push_back(i);
    }
    // 让 f(i) 单调递减，并一一对应
    // 同时记录 f(1)和f(m)
    sort(b.begin(), b.end(), greater<int>());
    int j = 0, l, r, m = b.size();
    for(int i = 1; i <= n; i++) 
	{
        if(f[i] == 0) 
		{
            f[i] = b[j];
            j++;
            if(j == 1) 
			{
                l = i;
            } 
			else if(j == m) 
			{
                r = i;
            }
        }
    }
    // f(i) 与 f(1) 或 f(m) 互换即可
    for(int i = 1; i <= n; i++) 
	{
        if(f[i] == i) 
		{
            if(i != l) 
			{
                swap(f[l], f[i]);
            } 
			else 
			{
                swap(f[r], f[i]);
            }
            break;
        }
    }
    for(int i = 1; i <= n; i++) cout << f[i] << " ";
    cout << endl;
    return 0;
}
```

---

## 作者：2012zxt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1283C)

# 1.思路

这道题是一道~~翻译比较坑~~的模拟题。

我们可以直接想到用一个队列存储没有收到礼物的人，然后枚举没有送过礼物的人并每次都让这个人送礼物给队头的人。

如果这样做，你会…… wa。

因为你没有考虑到自己给自己送礼物的情况。

那如果把它换成栈呢？

不行，比如样例 2，还是不行。

那我们就得换一个**实现方法**了。

接着我们可以想到把没送过礼物的和没收到礼物的分别存起来，如果他俩想通了，就可以把这个和他的下一个交换一下就好了。

但有个问题：如果是最后一个怎么办？

我们可以考虑把他和第一个人交换一下就好了。

所以问题就解决了。

# 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,f[N],cnt[N],pos[N],tot,need[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>f[i];
		if(f[i]==0)//处理没有送过的
			pos[++tot]=i;
		cnt[f[i]]++;
	}
	tot=0;
	for(int i=1;i<=n;i++)
		if(!cnt[i])
			need[++tot]=i;//预处理没有收到过的
	if(need[tot]==pos[tot])
		swap(need[1],need[tot]);//如上特判
	for(int i=1;i<tot;i++)
		if(need[i]==pos[i])
			swap(need[i],need[i+1]);//如上处理
	for(int i=1;i<=tot;i++)
		f[pos[i]]=need[i];//最后更新f
	for(int i=1;i<=n;i++)
		cout<<f[i]<<" ";
	return 0;
}

```

---

