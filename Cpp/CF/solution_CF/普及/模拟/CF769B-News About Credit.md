# News About Credit

## 题目描述

Polycarp studies at the university in the group which consists of $ n $ students (including himself). All they are registrated in the social net "TheContacnt!".

Not all students are equally sociable. About each student you know the value $ a_{i} $ — the maximum number of messages which the $ i $ -th student is agree to send per day. The student can't send messages to himself.

In early morning Polycarp knew important news that the programming credit will be tomorrow. For this reason it is necessary to urgently inform all groupmates about this news using private messages.

Your task is to make a plan of using private messages, so that:

- the student $ i $ sends no more than $ a_{i} $ messages (for all $ i $ from $ 1 $ to $ n $ );
- all students knew the news about the credit (initially only Polycarp knew it);
- the student can inform the other student only if he knows it himself.

Let's consider that all students are numerated by distinct numbers from $ 1 $ to $ n $ , and Polycarp always has the number $ 1 $ .

In that task you shouldn't minimize the number of messages, the moment of time, when all knew about credit or some other parameters. Find any way how to use private messages which satisfies requirements above.

## 说明/提示

In the first test Polycarp (the student number $ 1 $ ) can send the message to the student number $ 2 $ , who after that can send the message to students number $ 3 $ and $ 4 $ . Thus, all students knew about the credit.

## 样例 #1

### 输入

```
4
1 2 1 0
```

### 输出

```
3
1 2
2 4
2 3
```

## 样例 #2

### 输入

```
6
2 0 1 3 2 0
```

### 输出

```
6
1 3
3 4
1 2
4 5
5 6
4 6
```

## 样例 #3

### 输入

```
3
0 2 2
```

### 输出

```
-1
```

# 题解

## 作者：Yamchip (赞：3)

### 思路
这道题很明显是贪心，通知的人多对题目贡献也越大，所以我们每次通知人的时候都要尽量找能通知人最多的人。
### code
```cpp
#include<bits/stdc++.h>
#define st first
#define nd second
using namespace std;
int n, a[105], sum, cnt;
bool vis[105];
vector<pair<int, int> > ans;
struct Tmp
{
	int val, _;
}tmp[105];
bool cmp(Tmp x, Tmp y)
{
	if(x.val != y.val) return x.val > y.val;
	return x._ < y._;
}
int main()
{
    cin >> n;
    cnt = n - 1;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    if(a[1] == 0 || sum < n - 1)
    {
        cout << -1;
        return 0;
    }
    vis[1] = 1;
	while(cnt > 0)
	{
	    for(int i = 1;i <= n;i++)
		{
	        if(vis[i])
	        {
	            for(int j = 2;j <= n;j++)
	            {
	                tmp[j].val = a[j];
	                tmp[j]._ = j;
                }
                sort(tmp + 2, tmp + n + 1, cmp);
                for(int j = 2;j <= n && a[i] > 0;j++)
                {
                	if(!vis[tmp[j]._])
                	{
                		a[i]--;
                		cnt--;
    	                vis[tmp[j]._] = 1;
    	                ans.push_back(make_pair(i, tmp[j]._));
    	        		if(!cnt)
    	        		{
    	        			cout << ans.size() << "\n";
    						for(int k = 0;k < ans.size();k++)
    							cout << ans[k].st << " " << ans[k].nd << "\n";
    						return 0;
    					}
    	            }
                }
	        }
	    }
	}
    return 0;
}
```
虽然说要求的是随便一个通知的方案，但是我的优良品质让我必须写出最优方案。

---

## 作者：_shine_ (赞：1)

#### 题目
简而言之，题目表示是在一个平面上有 $n$ 个点，每个点能且只能连接 $a_i$ 条双向边且每个点在初始时互不连接，现在需要从点 $1$ 开始连接这 $n$ 个点使得这 $n$ 个点互相连通（不与 $1$ 联通的不允许建边），要求输出一个合理的方案。

先输入一个 $n$，后面 $1$ 行输入 $n$ 个数，表示每个点能最多出发于其他点相连的个数（从别的点出发连过来的不算，但这些边都是双向边）。

#### 思路

一个特质：如果这 $n$ 个点能互相连通，则这 $n$ 个点一定能连成一棵树。

容易发现一个点的 $a_i$ 越大，能连的边就越多，这里其实可以从 $1$ 出发分别连向 $a_1$ 个较大的点，然后分别连向几个较大的点，使得整棵树的 $a_i$ 大小从 $a_1$ 的子树开始单调不减（如下图所示，逗号右边为 $a_i$，左边为编号 $i$）。

[![pFA5iM4.png](https://s11.ax1x.com/2024/01/19/pFA5iM4.png)](https://imgse.com/i/pFA5iM4)

---

## 作者：jiangyixuan_eason (赞：0)

### 思路

细心的人应该不难发现，这道题目是非常明显的贪心。因为通知的人越多，贡献越大。所以，每次通知人都要找能通知人最多的人，也就是找能通知别人最多的人。

这道题目比较简单，所以我这里就不给代码了。

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/CF769B)

这是一道贪心，通知的人越多，贡献越大，所以，每次通知人都要找能通知人最多的人，也就是找能通知别人最多的人。

比较简单的一个贪心，不给代码了。

---

## 作者：glass_goldfish (赞：0)

## 正文
我一看数据范围，啊，赤裸裸的搜索啊！  

判断无解很容易，如果 $a_1=0$，那么消息都传不出去，当然无解。但是如果所有人传输次数都小于 $n-1$，那么总有人收不到消息，也是无解。  

我们标记一个 $k$，代表现在的传输主力（一开始当然是 $1$ 号）。首先，一直消耗 $k$ 号来传输，直到 $a_k=0$。然后，如果还是没有所有人都接受到消息，那么换一个 $k$ 即可。  

循环结束条件：所有人都接收到消息。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f
using namespace std;
int n,ans,a[301];
bool v[301];
int k=1;
bool s(){//是不是所有人都接受到消息
	for(int i=1;i<=n;i++)
		if(!v[i])return 0;
	return 1;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],ans+=a[i];
	if(ans<n-1||a[1]==0){
		cout<<"-1";//无解
		return 0;
	}
	v[1]=1;
	while(1){
		if(s())break;//结束
		for(int i=1;i<=n;i++)
			if(v[i]&&a[i]>0){
				k=i;
				break;
			}//更换k
		while(a[k]>0){
			if(s())return 0;//结束
			for(int i=2;i<=n;i++){
				if(a[k]==0)break;
				if(!v[i]){
					cout<<k<<" "<<i<<"\n";
					v[i]=1;
					a[k]--;//传送
				}
			}
		}
	}
    return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

波利卡普在由 $n$ 名学生（包括他自己）组成的小组中学习，编号为 $1$ 到 $n$，波利卡普的编号始终是 $1$。他们都在社交网络上注册，每个学生都有一个值 $a_i$，表示第 $i$ 名学生每天能发送的最大信息数。

清晨，波利卡普知道了一个重要消息，他认为有必要通过私人消息紧急通知所有组员。

您的任务是制定一个使用私人信息的计划，以便使

- 学生 $i$ 发送的信息数不超过 $a_i$。
- 所有学生都知道重要消息（最初只有波利卡普知道）。
- 学生只有在自己知道的情况下才能通知其他学生。

找到任意一种满足上述要求的使用私人消息的方法。

## 题目分析

如果一个同学要通知其他人，他一定会通知还能通知其他人且 $a_i$ 尽可能大的人，我们需要模拟上述贪心策略。

具体而言，我们可以先将 $2$ 到 $n$ 从大到小排序，枚举每一个 $i$，同时维护一个 $r$，表示 $1$ 到 $r$ 的人已经通知过了，每次使 $r \leftarrow r+a_i$，表示第 $i$ 个人通知第 $r+1$ 到 $r+a_i$ 的人。如果 $r \geq n$ 就结束。如果 $r<i$，那就说明前面的人不能通知到第 $i$ 个人，报告无解。用这种类似双指针的方法实现就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
#define se second
#define fi first
#define pr pair<int,int>
#define pb push_back
#define ph push
#define ft front
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
const int N=201;
int n,r=1,cnt;
pr a[N],vis[N]; 
bool cmp(pr x,pr y)
{
	return x.fi>y.fi;
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    For(i,1,n)
    {
    	cin>>a[i].fi;
    	a[i].se=i;
	}
	sort(a+2,a+1+n,cmp);
	For(i,1,n)
	{
		if(r<i)
		{
			cout<<-1;
			return 0;
		}
		For(j,r+1,min(r+a[i].fi,n))
		{
			vis[++cnt]={a[i].se,a[j].se};
		}
		r+=a[i].fi;
		if(r>n) break;
	} 
	cout<<cnt<<"\n";
	For(i,1,cnt)
	{
		cout<<vis[i].fi<<" "<<vis[i].se<<"\n";
	}
	return 0;
}
```

---

