# Silly Mistake

## 题目描述

The Central Company has an office with a sophisticated security system. There are $ 10^6 $ employees, numbered from $ 1 $ to $ 10^6 $ .

The security system logs entrances and departures. The entrance of the $ i $ -th employee is denoted by the integer $ i $ , while the departure of the $ i $ -th employee is denoted by the integer $ -i $ .

The company has some strict rules about access to its office:

- An employee can enter the office at most once per day.
- He obviously can't leave the office if he didn't enter it earlier that day.
- In the beginning and at the end of every day, the office is empty (employees can't stay at night). It may also be empty at any moment of the day.

Any array of events satisfying these conditions is called a valid day.

Some examples of valid or invalid days:

- $ [1, 7, -7, 3, -1, -3] $ is a valid day ( $ 1 $ enters, $ 7 $ enters, $ 7 $ leaves, $ 3 $ enters, $ 1 $ leaves, $ 3 $ leaves).
- $ [2, -2, 3, -3] $ is also a valid day.
- $ [2, 5, -5, 5, -5, -2] $ is not a valid day, because $ 5 $ entered the office twice during the same day.
- $ [-4, 4] $ is not a valid day, because $ 4 $ left the office without being in it.
- $ [4] $ is not a valid day, because $ 4 $ entered the office and didn't leave it before the end of the day.

There are $ n $ events $ a_1, a_2, \ldots, a_n $ , in the order they occurred. This array corresponds to one or more consecutive days. The system administrator erased the dates of events by mistake, but he didn't change the order of the events.

You must partition (to cut) the array $ a $ of events into contiguous subarrays, which must represent non-empty valid days (or say that it's impossible). Each array element should belong to exactly one contiguous subarray of a partition. Each contiguous subarray of a partition should be a valid day.

For example, if $ n=8 $ and $ a=[1, -1, 1, 2, -1, -2, 3, -3] $ then he can partition it into two contiguous subarrays which are valid days: $ a = [1, -1~ \boldsymbol{|}~ 1, 2, -1, -2, 3, -3] $ .

Help the administrator to partition the given array $ a $ in the required way or report that it is impossible to do. Find any required partition, you should not minimize or maximize the number of parts.

## 说明/提示

In the first example, the whole array is a valid day.

In the second example, one possible valid solution is to split the array into $ [1, -1] $ and $ [1, 2, -1, -2, 3, -3] $ ( $ d = 2 $ and $ c = [2, 6] $ ). The only other valid solution would be to split the array into $ [1, -1] $ , $ [1, 2, -1, -2] $ and $ [3, -3] $ ( $ d = 3 $ and $ c = [2, 4, 2] $ ). Both solutions are accepted.

In the third and fourth examples, we can prove that there exists no valid solution. Please note that the array given in input is not guaranteed to represent a coherent set of events.

## 样例 #1

### 输入

```
6
1 7 -7 3 -1 -3
```

### 输出

```
1
6
```

## 样例 #2

### 输入

```
8
1 -1 1 2 -1 -2 3 -3
```

### 输出

```
2
2 6
```

## 样例 #3

### 输入

```
6
2 5 -5 5 -5 -2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3
-8 1 1
```

### 输出

```
-1
```

# 题解

## 作者：liuzhongrui (赞：4)

## 思路

贪心，大模拟。

其实很容易理清思路，按事件发生的顺序模拟这些事件，如果办公室为空，就结束当前的一天并开始新的一天。

如果存在一个有效的解决方案，用贪心可以找到一个解。

为了使模拟高效地进行，我们应该在一个数组中维护每个员工的状态，共有三种状态：今天从未去过办公室、在办公室、已离开办公室。
    
还要求出当前在办公室的员工数量。

每当我们结束一天时，我们必须重置涉及当天的所有员工的状态，注意**不是所有员工，否则解决方案的复杂性将升为 $O(n^2)$。**

如果没有合法的划分，则输出 ```-1```。


最终的复杂性是 $O(n+e)$，其中 $e$ 是员工的数量，或者如果事先压缩数组，则为 $O(n)$，非常优秀的一个时间复杂度。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int borne = 1e6 + 5;
const int WAIT=0, ENTERED=1, LEFT=2;//三种状态 
int state[borne];
bool solve() {
	ios::sync_with_stdio(false);
	int nbEvents;
	cin >> nbEvents;
	vector<int> res, cur;
	int ofs = 0;
	for (int ind = 0; ind < nbEvents; ++ind) {
		int ev;
		cin >> ev;
		int guy = abs(ev);
		cur.push_back(guy);
		if (ev > 0) {
			if (state[guy] != WAIT) return 0;
			state[guy] = ENTERED;
			++ofs;
		} else {
			if (state[guy] != ENTERED) return 0;
			state[guy] = LEFT;
			--ofs;
		}
		if (ofs == 0) {
			res.push_back(cur.size());
			for (int x : cur) state[x] = WAIT;
			cur.clear();
		}
	}
	if (! cur.empty()) return 0;
	int nbDays = res.size();
	cout << nbDays << "\n";
	for (int i = 0; i < nbDays; ++i) {
		cout << res[i];
		if (i+1 < nbDays) cout << " ";
		else cout << "\n";
	}
	return 1;
}
int main() {
	if (!solve()) cout << "-1\n";
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

## CF1253B Silly Mistake 题解
### 解題思路
简简单单的一道大模拟，只是要特判的条件比较多。


我们可以在题目中总结出以下几点需要特判的条件：

- 在一个人进来时已经有相同的人了
- 在一个人出去时这个人还没有进来
- 在一天中一个人进来了两次
- 到结尾时所有人没有全部离开

我们可以规定每一天都是办公室**第一次**清空。因为如果一个较长的序列成立，那么截取一个较短的成立数列后，剩下的仍然成立。但是如果两个成立的数列拼接在一起，则不一定成立，因为两个数列中可能会有重复的数字。所以为了保证数列最容易成立，我们分出**尽量多**的天。

### 参考代码
```
#include<bits/stdc++.h>
using namespace std;
int n , a[100005] , b[1000005] , c[100005] , e[100005] , ctmp = 0 , cnt ,  cnt2 , etmp , tmp = 0;
bool d[1000005];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 0 ; i < n ; i++)
	{
		cin >> a[i];
	}
	cnt = 0;
	cnt2 = 0;
	for(int i = 0 ; i < n ; i++)
	{
		if(a[i] > 0)
		{
			if(b[a[i]] == 1)
			{
				cout << "-1";
				return 0;
			}
			if(d[a[i]])
			{
				cout << "-1";
				return 0;
			}
			b[a[i]]++;
			cnt++;
		}
		else
		{
			if(b[-a[i]] == 0)
			{
				cout << "-1";
				return 0;
			}
			b[-a[i]]--;
			d[-a[i]] = 1;
			e[etmp] = -a[i];
			etmp++;
			cnt--;
		}
		cnt2++;
		if(cnt == 0)
		{
			for(int i = 0 ; i < etmp ; i++)
			{
				d[e[i]] = 0;
			}
			c[ctmp] = cnt2;
			cnt2 = 0;
			ctmp++;
		}
	}
	for(int i = 0 ; i < ctmp ; i++)
	{
		tmp += c[i];
	}
	if(tmp != n)
	{
		cout << "-1";
		return 0;
	}
	cout << ctmp << endl;
	for(int i = 0 ; i < ctmp ; i++)
	{
		cout << c[i] << ' ';
	}
	return 0; 
}
```

---

## 作者：_HMZ_ (赞：1)

## 题目大意：

吐槽一下翻译……感觉解释的不太清楚，害我调了好久。

有 $n$ 个事件，对于 $a_i$，如果是整数，代表编号为 $a_i$ 的员工进入了办公室。

如果为负数，则代表编号为 $a_i$ 的绝对值的员工离开了办公室。

对于每一天，不能有任何一个员工进入了办公室两次，不能在进办公室之前离开。

在每一天的最后，办公室里不能留人。

最后要求将这 $n$ 个事件划分为 $k$ 天（划分天数可以任意）。

每一天都不能违反上面的条件，不能划分则输出 $-1$。

这里的输出一定要注意，$k_i$ 表示的是从上一天到这一天共经过了几个事件。

## 解题思路：

对于某个时刻，如果办公室已经没有人了，那么就直接划分。

因为每个人只能进入一次，再拖下去的话有可能某些人会再进去一次导致无法划分，其他的就模拟就好了。

但是还有一个要注意的点，如果直接 memset 计数器可能会超时。

所以要将每个你用过的位置加入一个队列，最后把队列的元素的计数器都清空就好了。

## AC代码：

```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
queue<int> q;
int n,a[1000005],ans[1000005],ansn,cnt,map[1000005],sum,last;
bool vis[1000005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]>=0 && vis[abs(a[i])])//这个人已经进来过一次了。
        {
            cout<<-1;
            return 0;
        }
        vis[abs(a[i])]=true;
        q.push(abs(a[i]));
        map[abs(a[i])]+=a[i];
        if(map[abs(a[i])]<0)//如果他在没进来之前就出去，就肯定无法划分。
        {
            cout<<-1;
            return 0;
        }
        else if(map[abs(a[i])]==0)
            --cnt;
        else
            ++cnt;
        if(cnt==0)//此时办公室里没人，将计数器清空，统计答案
        {
            while(!q.empty())
                vis[q.front()]=false,q.pop();
            ++ansn;
            ans[ansn]=i-last;//输出要注意
            last=i;
        }
    }
    if(cnt!=0)//如果最后还有人没出去肯定无法划分。
    {
        cout<<-1;
        return 0;
    }
    cout<<ansn<<endl;
    for(int i=1;i<=ansn;i++)
        cout<<ans[i]<<' ';
    return 0;
}
```


---

## 作者：Lan_yan (赞：0)

# CF1253B Silly Mistake 题解

## 思路

或许一上来有些同学会头大，但关注这句话：**找到任意一个合法划分即可，不需要最大化或最小化划分出的子串数量。**

也就是，我们并不需要任何的贪心，只要根据题目所述模拟一遍即可。

有很多中方法可以切掉这道题，我是这样想的：用数组提前设计所有人的状态，再一个一个输入来或去的人，一旦办公室是空的就开启新的一天。

唯一要注意的有几点：

- $1 \le n \le 10^5$，设计人们的状态时要小心，千万别数组开小 RE 了。
- 一个人只能进去一次，如果**同一天内**他之前来过或者还在办公室，那么就要输出 $-1$ 了。
- 同理，如果他本来不在办公室内突然表示要出办公室，那可就是灵异事件了。
- 一天结束时直接用 memset 清空会 TLE，所以可以用队列存储办公室有出入记录的人，在结束时一定要让队列保持为空！

细节处理后就非常简单了。

## 代码

```cpp
#include<bits/stdc++.h>//我最爱的万能头
using namespace std;
queue<int>bgs;//办公室有“案底”的人
int n,peo,num=0,dat[1000005],ds=0,la=0;
int yg[1000005]={0};//员工们的状态
//状态为1是在办公室，-1是来过办公室，0是没有来过办公室
int main()
{
	int i;
	while(!bgs.empty())bgs.pop();
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&peo);//一个一个记录
		if(peo>0)
		{
			if(yg[peo]!=0)//进办公室但是之前来过或已经在的人
			{
				printf("-1");return 0;
			}
			bgs.push(peo);//入队处理
			yg[peo]=1;num++;
		}
		if(peo<0)
		{
			peo*=-1;//这时输入进来的是负数！
			if(yg[peo]!=1)
			{
				printf("-1");return 0;
			}
			yg[peo]=-1;num--;//出去了人数得减少
		}
		if(num==0)//没有人的时候
		{
			while(!bgs.empty())//一个一个出队
			{
				yg[bgs.front()]=0;
				bgs.pop();
			}
			dat[++ds]=i-la;la=i;//i-旧的一天就是当天的记录情况
		}
	}
	if(num!=0)//还是得判断一下，以防万一
	{
		printf("-1");
		return 0;
	}
	printf("%d\n",ds);
	for(i=1;i<=ds;i++)printf("%d ",dat[i]);//输出
	return 0;
}
```

完结撒花！

---

## 作者：loser_seele (赞：0)

给一个补题的时候想到的实现巨麻烦但是好想的思路。

首先不难发现两个合法区间可以拼成一个大的，但是反过来则不行，考虑直接求出所有极长合法区间，那么极长合法区间一定是一个类似栈的结构，只不过每个元素最多入队一次。

开两个计数器，表示一个元素的入队次数和出队次数，然后分类讨论：如果一个新加的元素入队则首先判一下之前是否入队，是则新起一个区间，否则入队，如果是出队操作则先判是否入队，是出队，否则无解。注意对最后一个区间的特殊判断。在操作过程中顺带维护一个当前区间内还在队列内的数的数量，如果是 $ 0 $ 则也需要新开区间。

如果发现上述过程中出现需要新起一个区间的时候当前区间还有数则显然是无解的代表存在某些数没法配对。

注意清空计数器标记不能直接暴力清空，考虑一个朴素的套路：将修改的位置丢进一个队列里，修改仅修改队列内元素即可。

时间复杂度线性。

[提交记录](https://codeforces.com/contest/1253/submission/194171511)

---

