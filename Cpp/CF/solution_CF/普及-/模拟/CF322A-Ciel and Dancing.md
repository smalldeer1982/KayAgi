# Ciel and Dancing

## 题目描述

Fox Ciel and her friends are in a dancing room. There are $ n $ boys and $ m $ girls here, and they never danced before. There will be some songs, during each song, there must be exactly one boy and one girl are dancing. Besides, there is a special rule:

- either the boy in the dancing pair must dance for the first time (so, he didn't dance with anyone before);
- or the girl in the dancing pair must dance for the first time.

Help Fox Ciel to make a schedule that they can dance as many songs as possible.

## 说明/提示

In test case 1, there are 2 boys and 1 girl. We can have 2 dances: the 1st boy and 1st girl (during the first song), the 2nd boy and 1st girl (during the second song).

And in test case 2, we have 2 boys with 2 girls, the answer is 3.

## 样例 #1

### 输入

```
2 1
```

### 输出

```
2
1 1
2 1
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
3
1 1
1 2
2 2
```

# 题解

## 作者：newbie_QwQ (赞：2)

这是一道**构造**题。

------------
题目大意：有 $n$ 个男孩与 $m$ 个女孩，他们在一起跳舞。在每一首歌曲中，$1$ 个男孩与 $1$ 个女孩在一起跳舞，并且两人中至少有一人从未跳过舞。求最多能放几首歌。

------------
分析：因为两个人中只能有一个人跳过舞，并且一开始必定是要有两个都没跳过舞的人来跳舞的，所以方案数就是 $n+m-1$。

再考虑一下怎么进行构造。（注：下文中为了方便说明，设第 $i$ 个男孩为 $B_i$，第 $i$ 个女孩为 $G_i$。）

首先让两个都没跳过舞的人来跳舞，也就是让 $B_1$ 和 $G_1$ 先来跳舞，这样就已经有 $1$ 对舞伴跳过舞了。接下来就让 $G_1$ 和 $B_2 \dots B_n$ 一起跳舞，这样每一对中只有一个人没有跳过舞，是最优的，又多了 $n-1$ 对舞伴。最后让 $B_1$ 和 $G_2 \dots G_m$ 跳舞，这样每一对中还是只有一个人没有跳过舞，也是最优的，又多了 $m-1$ 对舞伴。将这三个数相加，正好就是 $n+m-1$ 对舞伴。也就是一共能放 $n+m-1$ 首歌。

------------
## AC 代码：
```cpp
#include<iostream>
using namespace std;
int main()
{
	int i,n,m;
	cin>>n>>m;
	cout<<n+m-1<<endl;
	cout<<"1 1"<<endl;
	for(i=2;i<=n;i++) cout<<i<<" "<<1<<endl;
	for(i=2;i<=m;i++) cout<<1<<" "<<i<<endl;
	return 0;//再见！
}
```

---

## 作者：FreedomKing (赞：2)

# 简单的构造题
[注：Blog 食用更佳](https://www.luogu.com.cn/blog/zhugeminhao/SP3394)

------------
### 题目大意
$n$ 个男孩和 $m$ 个女孩一起跳舞。每一首歌曲中只能有**一组**至少其中一人没跳过舞的男孩和女孩跳舞，问**最多**可以放多少首歌。

------------
### 思路
因为第一首歌时大家都没跳过舞，所以答案要减 $1$。

其次想要多播放歌曲，那么男孩和女孩中至少要有一个没跳过舞。所以我们每次要挑选一个没有跳过舞的男/女孩，为 $Ta$ 配上一个已经跳过舞的男/女孩。

那么思路清晰，开干！

------------
[CF322A Ciel and Dancing](https://www.luogu.com.cn/problem/CF322A)
### AC Code:
```cpp
#include<bits/stdc++.h>//不用万能头也可以，但个人觉得万能头方便
using namespace std;//可以不加
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	printf("%d\n1 1",n+m-1);
	for(int i=2;i<=n;i++) printf("%d 1\n",i);
	for(int i=2;i<=m;i++) printf("1 %d\n",i);
	return 0;//好习惯
}
```
~~蒟蒻的第 4 篇题解，但还是求过 QwQ~~

---

## 作者：hanyuchen2019 (赞：0)

简单构造题。

为了方便说明，设第 $i$ 个男孩为 $A_i$，第 $i$ 个女孩为 $B_i$。

### part1 大致题意

有 $n$ 个男孩与 $m$ 个女孩，他们在一起跳舞。

在每一首歌曲中，$1$ 个男孩与 $1$ 个女孩在一起跳舞，并且**两人中至少有一人从未跳过舞。**

求最大播放的歌曲数。

### part2 思路

首先让 $B_1$ 与 $A_1 \dots A_n$ 分别跳舞，播放 $n$ 首歌曲。 

之后让 $A_1$ 与 $B_2 \dots B_m$ 分别跳舞，播放 $m-1$ 首歌曲（由于 $A_1$ 与 $B_1$ 已经跳舞过了，所以从 $B_2$  开始）。 

共播放 $n+m-1$ 首歌曲，显然这是最大值。

### part3 Code

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	cout<<n+m-1<<'\n';
	for(int i=1;i<=n;i++)
		cout<<i<<" "<<1<<'\n';
	for(int i=2;i<=m;i++)
		cout<<1<<" "<<i<<'\n'；
	return 0;
}
```
码字不易，点个赞再走吧~

---

## 作者：Ninelife_Cat (赞：0)

考虑贪心做法。

想要播放一首歌曲，那么男孩和女孩中必须至少要有一个没跳过舞。所以我们每次挑选一个没有跳过舞的男/女孩，为ta配上一个已经跳过舞的，显然这样是最优的。

然后因为第一首歌时大家都没跳过舞，所以答案要减 $1$。

至于构造每次跳舞的人嘛…只要为第 $1$ 个男孩配上所有的女孩，然后为第 $1$ 个女孩配上第 $2$ 到 $n$ 个男孩就行了。

核心代码：

```cpp
int n,m,ans;
signed main()
{
	n=read();m=read();//快读什么的就不放了
	cout<<n+m-1<<endl;
	for(ri int i=1;i<=m;++i)
		cout<<1<<" "<<i<<endl;
	for(ri int i=2;i<=n;++i)
		cout<<i<<" "<<1<<endl;
	return 0;
}

---

