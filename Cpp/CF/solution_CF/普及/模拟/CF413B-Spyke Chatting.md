# Spyke Chatting

## 题目描述

R2 公司有 $n$ 名员工为其工作。这项工作包括不断交流想法，分享成功的故事和准备迎接即将到来的挑战。为此，R2 使用了著名的即时通讯程序 Spyke。

公司中一共有 $m$ 个聊天室。在每个聊天室中，一些员工会发消息。一名员工可以在多个聊天室中同时交谈。如果某个员工在聊天室中，他可以发送消息，并接收有关该聊天室中消息的通知。如果员工在聊天室中发送消息，则此聊天室的所有其他参与者都会收到消息通知。

现在，专家们正在研究员工之间的有效沟通，为此，他们有一个聊天记录的描述。作为审计专家之一，您将被委托编写一个程序，该程序将使用此数据确定每个员工收到的消息通知总数。

## 样例 #1

### 输入

```
3 4 5
1 1 1 1
1 0 1 1
1 1 0 0
1 1
3 1
1 3
2 4
3 2
```

### 输出

```
3 3 1 ```

## 样例 #2

### 输入

```
4 3 4
0 1 1
1 0 1
1 1 1
0 0 0
1 2
2 1
3 1
1 3
```

### 输出

```
0 2 3 0 ```

# 题解

## 作者：_Starlit__Sky_ (赞：5)

# 洛谷 CF413B 题解

[题目传送门](https://www.luogu.com.cn/problem/CF413B)

## 题目算法

模拟

## 题目思路

题目给出了一些员工和他们所加入的聊天室。若一个员工在一个聊天室里发了消息，则这个聊天室里面的其他所有成员都可以接收到这条消息。已知某些员工在某些聊天室里发了消息，求每个员工接收到的消息数量。

我们可以构建 $chat$ 数组，$chat_i$ 表示第 $i$ 个聊天室里面的员工。

若员工 $x$ 在 聊天室 $y$ 中发送了一条消息，则将 $chat_y$ 里除员工 $x$ 之外的所有员工接收到的消息数量加一。

最后输出每个员工接收到的消息数量即可。

## 代码

```python
n,m,k = map(int,input().split()) # 输入 n,m,k
a = [list(map(int,input().split())) for _ in range(n)] # 输入 矩阵a
chat = [[] for _ in range(m)] # 构建 chat
# 遍历存入 chat
for i in range(n):
    for j in range(m):
        if a[i][j]: chat[j].append(i)

ans = [0 for _ in range(n)] # 构建 ans 数组（ans[i] 表示第i个员工接收到的消息数量）
for _ in range(k): # 遍历 k 条消息记录
    x,y = map(int,input().split()) # 输入 x,y
    # 因为员工和聊天室编号是从1开始计数的，而python数组下标是从0开始计数的，所以要把x,y都减一
    x -= 1
    y -= 1
    # 将第y个聊天室里除员工x之外的员工接收到的消息数量加一
    for i in chat[y]:
        if i != x: ans[i] += 1
for i in ans: print(i, end = ' ') # 输出，用空格隔开
```


---

## 作者：DarkShadow (赞：4)

# CF413B（模拟）

## 题目大意：

有 $N$ 个人和 $M$ 个聊天室，给出 $K$ 条消息，求每个人收到的消息数量。

## 思路分析：

首先可以想到对于每条消息，直接给当前聊天室的所有人暴力计算答案。

时间复杂度：$O(NK)$，由于 $N \le 2 \times 10^4$，$K \le 2 \times 10^5$，所以会 TLE。

考虑优化，其实我们只需要记录每个聊天室有多少条消息，最后在计算每个人的消息条数就可以了，这样就可以通过本题。

注意：由于每个人自己发的消息不能计入这个人的答案，所以还需要减去每个人自己发的消息。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,cnt1[15],cnt2[20005];//cnt1表示每个聊天室的消息条数，cnt2表示每个人发的消息条数
bool d[20005][15];
int main(){
	int x,y,ans;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&d[i][j]);
	while(k--){
		scanf("%d%d",&x,&y);
		cnt1[y]++,cnt2[x]++;//统计聊天室的消息数量和每个人发的消息数量
	}
	for(int i=1;i<=n;i++){
		ans=0;
		for(int j=1;j<=m;j++)
			if(d[i][j])  ans+=cnt1[j];//计算每个人收到的消息数量
		ans-=cnt2[i];//记得减掉自己发的消息
		printf("%d ",ans);
	}
	return 0;
}
```

---

## 作者：OIer6666 (赞：1)

题目传送门 [洛谷](https://www.luogu.com.cn/problem/CF413B)

## 错误解题思路

考虑模拟，对于每次发消息，给在同一聊天室的其他员工答案加上 $1$。

**万万不可！**

时间复杂度 $O(n\times k)$，而 $n\times k$ 最大可达 $4\times 10^9$！

## 正确解题思路

既然消息不会传到其他聊天室，那么给聊天室权值加上 $1$，对于每个员工加上他所在聊天室的权值相加再减去他的发言次数就是他收到的消息数了！

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ct[15],z[114514][15],x,y,ms[114514]; 
int main(){
	//freopen("CF413B.in","r",stdin);
	//freopen("CF413B.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>z[i][j];
	while(k--){
		cin>>x>>y;
		ms[x]--;
		ct[y]++;
	}
	for(int i=1;i<=n;i++){
		int sum=ms[i];
		for(int j=1;j<=m;j++)
			if(z[i][j])
				sum+=ct[j];
		cout<<sum<<' ';
	}
	return 0;
}
```

附[提交记录](https://codeforces.com/contest/413/submission/293997835)

---

## 作者：Aelt (赞：1)

### 分析

给出一个 $n \times m$ 的矩阵，第 $i$ 行 $j$ 列表示编号为 $i$ 的员工在编号为 $j$ 的聊天室里。

给定 $k$ 组消息，编号为 $x$ 的员工在 编号为 $y$ 的聊天室里发送了消息（在这个聊天室里的员工视为接收了这条消息）。

观察样例：

```
3 4 5    一共有 3 个员工，4 个聊天室，5 个消息
1 1 1 1  这一行是编号为 1 的员工，TA属于编号为 1 2 3 4的聊天室
1 0 1 1  这一行是编号为 2 的员工，TA属于编号为 1 3 4的聊天室
1 1 0 0  这一行是编号为 3 的员工，TA属于编号为 1 2 的聊天室
1 1      编号为 1 的员工在聊天室 1 里发送了一条消息
3 1      编号为 3 的员工在聊天室 1 里发送了一条消息
1 3      编号为 1 的员工在聊天室 3 里发送了一条消息
2 4      编号为 2 的员工在聊天室 4 里发送了一条消息
3 2      编号为 3 的员工在聊天室 2 里发送了一条消息
```
我们可以发现，在聊天室 $1$ 里收到了 $2$ 条消息，在聊天室 $2$ 里收到了 $1$ 条消息，在聊天室 $3$ 里收到了 $1$ 条消息，在聊天室 $4$ 里收到了 $1$ 条消息。

综上，员工 $1$ 共收到了 $3$ 条消息，员工 $2$ 共收到了 $3$ 条消息，员工 $3$ 收到了 $1$ 条消息。

所以，完成此题只需要按上述步骤模拟一下即可。但是还需要注意的是，**最后统计答案时要把自己发送的消息数量减去**，因为自己发送的不是自己接受到的。

[AClink](https://codeforces.com/problemset/submission/413/277848289)。

---

## 作者：shenbairui (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF413B)

### 题目大意
有 $N$ 个人和 $M$ 个聊天室，给出 $K$ 条消息，要求出每个人收到的消息数量。

### 题目分析
注意到 $ m \leqslant 10$，直接用暴力，搞一个数组 $talk$，若员工 $x$ 在聊天室 $y$ 发送了一条信息，则在 $talk_y$ 除了员工 $x$ 的员工的消息数加一，因为员工不能自己接受自己的信息。最后在再输出结果即可。

但是这样会超时，所以我们要搞两个数组，我们其实只需要记录每个聊天室有多少条消息，最后在计算每个人的消息条数就可以了，时间复杂度为 $O(nm)$ 不会超时。

### 代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,a[20005][15],b[15],c[20005],x,y;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}
	while(k--){
		cin>>x>>y;
		b[y]++,c[x]++;
	}
	for(int i=1;i<=n;i++){
		int ans=0;
		for(int j=1;j<=m;j++){
			if(a[i][j]) ans+=b[j];	
		}
		ans-=c[i];
		cout<<ans<<" ";
	}
	return 0;
}
```
### [AC 记录](https://codeforces.com/contest/413/submission/277592385)

下次见！拜拜！

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF413B)  
[CodeForces 传送门](http://codeforces.com/problemset/problem/413/B)

简单模拟。我们可以用一个桶统计每个人发送的消息总数，用另一个桶统计每个聊天室的消息总数，然后对于每个人直接计算即可。

如果第 $i$ 个人在第 $j$ 个聊天室内，就加上给聊天室的消息总数。最后注意“收到的消息总数”不包括自己发送的消息，所以要减去自己发送的消息总数。

```cpp
bool a[20010][20];
int p[20010],q[20];
signed main()
{
	int n,m,k;
	rd(n,m,k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			rd(a[i][j]);
		}
	}
	while(k--)
	{
		int x,y;
		rd(x,y),p[x]++,q[y]++;
	}
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		for(int j=1;j<=m;j++)
		{
			ans+=a[i][j]?q[j]:0;
		}
		ans-=p[i],wt(ans),kg;
	}
	hh;
	return 0;
}
```

---

## 作者：PvbeLLN (赞：0)

### 分析

根据输入格式，我们可以用一个布尔数组 $isin$ 来表示一个员工 $i$ 是否在聊天室 $j$ 中，如果 $isin[i][j]=1$ 则表示 $i$ 在 $j$ 中，反之则不在。

对于统计每个员工所收到的消息总数，可以采用下面的公式：

**接收到的消息数 $=$ 该员工所在的所有聊天室中的消息总数 $-$ 该员工发出的消息数**。

注意到聊天室总数 $m \le 10$，可以采用枚举的方法，时间可以接受。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a,b,ans;
int cnt[20005],tot[15];    //cnt数组记录每个员工发出的消息数，tot数组记录每个聊天室中的消息总数
bool isin[20005][15];   //表示员工i是否在聊天室j内

int main()
{
	cin>>n>>m>>k;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			cin>>isin[i][j];
	while (k--)
	{
		cin>>a>>b;   //员工a在聊天室b中发送了一条消息
		cnt[a]++,tot[b]++;
	}
	for (int i=1;i<=n;i++)
	{
		ans=0;   //记录第i个员工收到的消息数
		for (int j=1;j<=m;j++)
			if (isin[i][j]) ans+=tot[j];   //如果在聊天室内
		ans-=cnt[i];   //减去他自己发送的
		cout<<ans<<" ";
	}
	return 0;
}
```


---

## 作者：a_blue_cell (赞：0)

就是一道简单的模拟题，但是有一个坑点需要注意：一个员工所受到的消息**不包括他自己发送出去的消息**。

那么，这道题的做法其实就显而易见。

维护两个数组，分别表示“员工发送出去的消息数”和“一个聊天室里收到的消息总数”。

对于每一个员工，将所有该员工所在的聊天室的收到的消息总数累加起来，再减去这个员工自己发送出去的消息数就是答案了。

而由于此题数据范围极小，使用暴力统计即可，复杂度为 $O(nm)$。

代码：

```cpp
#include<cstdio>
int n,m,k,x,y;
int a[20005][15];
int sum1[20005],sum2[20005];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=k;i++){
		scanf("%d%d",&x,&y);
		sum1[x]++,sum2[y]++;//维护两个数组，含义前文已提及
	}
	for(int i=1;i<=n;i++){
		int ans=0;
		for(int j=1;j<=m;j++){
			if(a[i][j]){//暴力统计
				ans+=sum2[j];
			}
		}
		printf("%d ",ans-sum1[i]);
	}
	return 0;
}
```

---

