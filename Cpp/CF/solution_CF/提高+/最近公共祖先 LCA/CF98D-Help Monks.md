# Help Monks

## 题目描述

In a far away kingdom is the famous Lio Shan monastery. Gods constructed three diamond pillars on the monastery's lawn long ago. Gods also placed on one pillar $ n $ golden disks of different diameters (in the order of the diameters' decreasing from the bottom to the top). Besides, gods commanded to carry all the disks from the first pillar to the third one according to the following rules:

- you can carry only one disk in one move;
- you cannot put a larger disk on a smaller one.

 There was no universal opinion concerning what is to happen after the gods' will is done: some people promised world peace and eternal happiness to everyone, whereas others predicted that the kingdom will face communi… (gee, what am I rambling about?) the Armageddon. However, as everybody knew that it was impossible to solve the problem in less than $ 2^{n}-1 $ moves and the lazy Lio Shan monks never even started to solve it, everyone lives peacefully even though the problem was never solved and nobody was afraid of the Armageddon.However, the monastery wasn't doing so well lately and the wise prior Ku Sean Sun had to cut some disks at the edges and use the gold for the greater good. Wouldn't you think that the prior is entitled to have an air conditioning system? Besides, staying in the monastery all year is sooo dull… One has to have a go at something new now and then, go skiing, for example… Ku Sean Sun realize how big a mistake he had made only after a while: after he cut the edges, the diameters of some disks got the same; that means that some moves that used to be impossible to make, were at last possible (why, gods never prohibited to put a disk on a disk of the same diameter). Thus, the possible Armageddon can come earlier than was initially planned by gods. Much earlier. So much earlier, in fact, that Ku Sean Sun won't even have time to ski all he wants or relax under the air conditioner.

The wise prior could never let that last thing happen and he asked one very old and very wise witch PikiWedia to help him. May be she can determine the least number of moves needed to solve the gods' problem. However, the witch laid out her cards and found no answer for the prior. Then he asked you to help him.

Can you find the shortest solution of the problem, given the number of disks and their diameters? Keep in mind that it is allowed to place disks of the same diameter one on the other one, however, the order in which the disks are positioned on the third pillar in the end should match the initial order of the disks on the first pillar.

## 说明/提示

Pay attention to the third test demonstrating that the order of disks should remain the same in the end, even despite the disks' same radius. If this condition was not necessary to fulfill, the gods' task could have been solved within a smaller number of moves (three — simply moving the three disks from the first pillar on the third one).

## 样例 #1

### 输入

```
3
3 2 1
```

### 输出

```
7
1 3
1 2
3 2
1 3
2 1
2 3
1 3
```

## 样例 #2

### 输入

```
3
3 1 1
```

### 输出

```
5
1 2
1 2
1 3
2 3
2 3
```

## 样例 #3

### 输入

```
3
3 3 3
```

### 输出

```
5
1 2
1 2
1 3
2 3
2 3
```

# 题解

## 作者：int08 (赞：0)

## 前言

没有题解的题，那我浅写。

## 题意
汉诺塔，但是相等大小盘子可能出现多次，且最终相等大小盘子顺序与初始顺序相等。

请先确保你会普通的汉诺塔的递归做法。
# Solution

显然仍然考虑用递归做法。

看到问题第一反应是：这不是跟普通汉诺塔一样吗？只要碰到相等的多做几次一起挪走不就好了吗？怎么评分到 *$2500$ 的啊？

（这个做法将在下文被称为简单做法）

但是注意到条件：**相等大小盘子顺序与初始顺序相等。**

在看到样例三之后我们意识到事情似乎并不是那么简单，因为上面所言的简单做法，很可能直接挪过去之后部分相等盘子顺序反转了。

那我们得研究一下了。

下文将相等的盘子视作一层。
### 最底层只有一个的情况

回忆简单做法解决正常 $x$ 层汉诺塔的三部曲：

1. 递归挪开上面 $x-1$ 层；
2. 将最底层的盘子挪到指定位置；
3. 将上面 $x-1$ 层归位。

如果最底层不止一个，这样的方案就会导致底层倒置，但是如果只有一个就没有问题。

而且这种方案正好挪动了两次上面 $x-1$ 层，上面的部分就算使用简单做法翻转了也会翻回来，非常牛。

那么我们得出结论，如果最底层只有一个，剩下的就直接采取简单做法。

从这里我们也可以大致知道程序的写法：`dfs(x,tp)` 表示解决前 $x$ 层，其中 $tp=1$ 表示需要考虑不翻转，$tp=0$ 表示不考虑（也就是直接使用简单做法），出现底层只有一个时候 $tp$ 就改为 $0$。

### 最底层不止一个

此时容易发现，不存在只挪动两次上面 $x-1$ 层的解法了。

举个例子：$3,3,1$（即两层第二层有两个的情况），容易手玩得出方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/sisclaf7.png)

（按数字顺序进行）

那么现在把 $1$ 换成前 $x-1$ 层，我们就得到了解法：

1. 将前 $x-1$ 层从第一列挪到第三列；
2. 将第 $x$ 层从第一列挪到第二列；
3. 将前 $x-1$ 层从第三列挪回第一列；
4. 将第 $x$ 层从第二列挪到第三列；
5. 将前 $x-1$ 层从第一列挪到第三列。

其中，我们挪动了三次前 $x-1$ 层，可以在两次中使用简单方法，剩下一次使用考虑不能反转的做法（也就是递归解决）

注意：只剩下一层的时候，假设有 $x$ 个，不能翻转的情况并不是 $2x$ 次而是 $2x-1$ 次，方法参见第三个样例。

能够感觉到这个方案是最优的。

事实上还存在一种方案是四次简单挪动上 $x-1$ 层然后用 $2k-1$（假设第 $x$ 层有 $k$ 个）挪最后一层的方案，不过可以证明不会比上文方案更优，证明过程留作习题（雾）。

## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> > ans;
int n,a[28],b[28],cc,emp[4][4],i;
void work(int x,int zt,int st,int ed)
{
	int mi=emp[st][ed];
	if(!zt)
	{
		if(x==1) {for(int i=1;i<=b[x];i++) ans.push_back({st,ed});return;}
		work(x-1,zt,st,mi);
		for(int i=1;i<=b[x];i++) ans.push_back({st,ed});
		work(x-1,zt,mi,ed);
	}
	if(zt)
	{
		if(x==1)
		{
			for(int i=1;i<b[x];i++) ans.push_back({st,mi});
			ans.push_back({st,ed});
			for(int i=1;i<b[x];i++) ans.push_back({mi,ed});
			return;
		}
		if(b[x]==1)
		{
			work(x-1,0,st,mi);
			ans.push_back({st,ed});
			work(x-1,0,mi,ed);
			return;
		}
		work(x-1,0,st,ed);
		for(int i=1;i<=b[x];i++) ans.push_back({st,mi});
		work(x-1,0,ed,st);
		for(int i=1;i<=b[x];i++) ans.push_back({mi,ed});
		work(x-1,1,st,ed);
	}
}
int main()
{
	cin>>n;
	emp[1][3]=emp[3][1]=2;emp[2][1]=emp[1][2]=3;emp[2][3]=emp[3][2]=1;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=n;i>=1;i--) if(a[i]==a[i+1]) b[cc]++; else b[++cc]=1;
	work(cc,1,1,3);
	cout<<ans.size()<<endl;
	for(auto x:ans) printf("%d %d\n",x.first,x.second);
	return 0;
}
```

# The End.

---

