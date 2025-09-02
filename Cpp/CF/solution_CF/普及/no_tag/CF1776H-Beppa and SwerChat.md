# Beppa and SwerChat

## 题目描述

Beppa and her circle of geek friends keep up to date on a group chat in the instant messaging app SwerChat $ ^{\text{TM}} $ .

The group has $ n $ members, excluding Beppa. Each of those members has a unique ID between $ 1 $ and $ n $ . When a user opens a group chat, SwerChat $ ^{\text{TM}} $ displays the list of other members of that group, sorted by decreasing times of last seen online (so the member who opened the chat most recently is the first of the list). However, the times of last seen are not displayed.

Today, Beppa has been busy all day: she has only opened the group chat twice, once at 9:00 and once at 22:00. Both times, she wrote down the list of members in the order they appeared at that time. Now she wonders: what is the minimum number of other members that must have been online at least once between 9:00 and 22:00?

Beppa is sure that no two members are ever online at the same time and no members are online when Beppa opens the group chat at 9:00 and 22:00.

## 说明/提示

In the first test case, members $ 4, 5 $ must have been online between 9:00 and 22:00.

In the second test case, it is possible that nobody has been online between 9:00 and 22:00.

## 样例 #1

### 输入

```
4
5
1 4 2 5 3
4 5 1 2 3
6
1 2 3 4 5 6
1 2 3 4 5 6
8
8 2 4 7 1 6 5 3
5 6 1 4 8 2 7 3
1
1
1```

### 输出

```
2
0
4
0```

# 题解

## 作者：ダ月 (赞：4)

### 题意简要：

一个群有 $n$ 个人，早上看最晚登陆前后次序为 $a_i$，晚上看最晚登陆前后次序为 $b_i$，问在这一天内至少有多少人登陆这个群。

### 题目分析：

结论 $1$：一个人 $i$ 假如在早上存在比他晚登陆的人 $j$，但是晚上时显示登陆 $i$ 比 $j$ 晚，说明 $i$ 上线过。

显而易见，假如 $i$ 不上线，$j$ 不上线，那么 $i$ 与 $j$ 的相对登陆次序不变。如果 $i$ 不上线，$j$ 上线，那么 $j$ 应在 $i$ 前面。

有了这个结论，模拟一下，可以做到 $O(n^2)$。过不了此题。

既然枚举早上的人会超时，我们换个角度思考，从晚上的人开始枚举。

结论 $2$：序列 $a_i$ 存在一个**最长**长度为 $k$ 的子序列，满足是 $b_i$ 序列的一个后缀，那么答案就是 $n-k$。

显然，这个子序列的任意一个元素不满足结论 $1$。这个结论成立。

我们在 $b_i$ 上倒序枚举，在 $a_i$ 设立一个倒序指针，扫一遍就行了。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		vector<int> a(n),b(n);
		for(int i=0;i<n;i++) cin>>a[i];
		for(int i=0;i<n;i++) cin>>b[i];
		int pos=n-1,wh=-1;
		for(int i=n-1;~i;i--){
			while(~pos&&b[i]!=a[pos]) pos--;
			if(pos<0){wh=i;break;}
		}printf("%lld\n",wh+1);
	}return 0;
}
```

时间复杂度：$O(n)$。


---

## 作者：封禁用户 (赞：1)

### 题目大意

有一个有 $n$ 个人的群，分别在早上和晚上看了群内成员的排名，这个排名按最近登录的时间来决定，然后求出在早上到晚上有多少人登录过。

### 思路

因为我们每次登陆时会将排名第一位变成自己。例如原先排名为 $3,2,1$，晚上登陆时排名变成 $1,3,2$，我们易知 $1$ 一定登陆过，但是题目要求成员登录过的最小数量，所以还要排除 $2,3$ 在 $1$ 之前登陆的情况。

所以我们发现：没有登陆过的人在排名中的顺序不变。

但是 $O(n^2)$ 的时间复杂度是会超时的，所以我们要用双指针来解决。


### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005];
int main()
{
	int t;
	cin>>t;
	while (t--)
	{
		int n;
		cin>>n;
		for (int i=0;i<n;i++)
		{
			cin>>a[i];
		}
		for (int i=0;i<n;i++)
		{
			cin>>b[i];
		}
		int ans=0;//ans表示早上和晚上次序不变的人数，即未登陆过的人数 
		for (int i=n-1,j=n-1;i>=0&&j>=0;i--)//从后向前搜，不然会超时 
		{
			if (a[i]==b[j])//如果排名相同就为未登陆过的人 
			{
				j--;
				ans++;
			}
		}
		cout<<n-ans<<endl;//登陆过的人数 
	}
	return 0;
}

```


---

## 作者：little_stickman (赞：0)

# CF1776H题解
# 主要题意
有一个群聊，在早上统计一次进群的顺序，晚上也统计一次。请问这期间至少有几个人登录了群聊。
# 解题思路
首先，我们可以得出一个结论，如果一个人 $a$ 早上进入群聊的时候在 $b$ 前面，但是晚上到了 $b$ 后面，那他一定进入了群聊。如果这样模拟，会时间超限。

我们不妨换个思路，统计**未登录的人数**。具体操作为将早上进群顺序一一与晚上进群顺序比对，如果在两次顺序中，此人顺序不变，那么我们就判断为此人未进群，并与晚上进群的下一人比对。反之，此人就登录了这个群聊。
# 上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],b[1000010];
int T,n,cnt=0;
int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		cnt=0;
		int j=n;
		for(int i=n;i>=1;i--)
			if(a[i]==b[j]) 
				j--,cnt++;
		cout<<n-cnt<<"\n";
	}
	return 0;
}
```

---

