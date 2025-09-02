# [ABC088B] Card Game for Two

## 题目描述

有 $N$ 张卡片，第 $i$ 张卡片上写着一个数 $a_i$。Alice 和 Bob 用这些卡片进行游戏。游戏规则是，Alice 和 Bob 轮流各取一张卡片，Alice 先取。所有卡片被取完后，游戏结束。每个人的得分是他所取卡片上数字之和。两人都采取最优策略以最大化自己的得分。请你求出 Alice 比 Bob 多得多少分。

## 说明/提示

## 限制条件

- $N$ 是 $1$ 到 $100$ 之间的整数。
- $a_i\ (1 \leq i \leq N)$ 是 $1$ 到 $100$ 之间的整数。

## 样例解释 1

首先，Alice 取走写有 $3$ 的卡片。接着，Bob 取走写有 $1$ 的卡片。得分差为 $3 - 1 = 2$。

## 样例解释 2

首先，Alice 取走写有 $7$ 的卡片。然后，Bob 取走写有 $4$ 的卡片。最后，Alice 取走写有 $2$ 的卡片。得分差为 $7 - 4 + 2 = 5$ 分。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2 7 4```

### 输出

```
5```

## 样例 #3

### 输入

```
4
20 18 2 18```

### 输出

```
18```

# 题解

## 作者：幻之陨梦 (赞：7)

$Solution:$

这道题不难看出是一道很水的贪心题。因为每个人都会选择当前的最优策略，所以就把给出的牌按照从大至小的顺序排序，然后用两个变量分别记录两个玩家的总得分最后相减就可以了。

**划重点：** ``x&1=x%2``

$code:$
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//标准数据库
inline int read()//快速读入
{
    int x=0,f=1;char c=getchar();
    while(c<'0' || c>'9'){if(c=='-') f=0;c=getchar();}
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return f?x:-x;
}
int n,a[110],s1,s2;
int main()
{
    n=read();//读入牌的总数
    for(int i=1;i<=n;i++) a[i]=read();//读入每张牌的值
    sort(a+1,a+n+1,greater<int>());//从小至大排序（STL真香
    for(int i=1;i<=n;i++)//从最大的牌的值循环到最小的牌的值
    {
        if(i&1) s1+=a[i];
        //如果当前排序后的牌的序号不是2的倍数，那么就加给 1 号选手（因为是从 1 号一直到 n 号
        else s2+=a[i];//反之加给 2 号选手
    }
    printf("%d",s1-s2);//输出两选手得分差值
    return 0;
}
```
如果这篇文章给予了你帮助，那你就点个赞再走吧，Thanks♪(･ω･)ﾉ

---

## 作者：PC_DOS (赞：4)

本题为一道模拟题，因为要计算二人的得分差，因此我们可以将所有卡上的点数降序排列，然后遍历排序完毕的数组(下标从0开始)，偶数项加给Alice，奇数项加给Bob，最后输出二人得分之差即可。

这样做的原因是题目保证二人均使用使自己本回合得分最大的方法，因此肯定是Alice先取最大的牌，Bob取余下牌里最大的牌(第二大的牌)，再下来Alice取余下牌里最大的牌(第三大的牌)......以此类推。

代码:
```
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cctype>
#include <climits>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nCount, iIn, iAlice = 0, iBob = 0; //nCount-卡牌个数；iIn-暂存输入的数字；iAlice-Alice的得分；iBob-Bob的得分
	vector<int> arrNums; //存放卡牌点数的动态数组
	register int i; //循环计数器
	cin >> nCount; //读入个数
	for (i = 1; i <= nCount; ++i){ //循环读入点数
		cin >> iIn; //读入点数
		arrNums.push_back(iIn); //压入数组
	}
	sort(arrNums.begin(), arrNums.end(), isgreaterequal<int,int>); //降序排序
	for (i = 0; i < nCount; ++i){ //遍历数组
		if (i % 2 == 0) //偶数项加给Alice
			iAlice += arrNums[i];
		else //奇数项加给Bob
			iBob += arrNums[i];
	}
	cout << iAlice - iBob; //输出二人得分之差
	return 0; //结束
}
```

---

## 作者：AubRain (赞：2)

~~来自蒟蒻的超短代码~~

优先队列做法

每次取队头，即为最大的元素

分两个计数

i&1 和 i%2的效果类似

```cpp
#include <queue>
#include<iostream>
using namespace std;
int n,a,s[2];
priority_queue<int> q;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a,q.push(a);
    for(int i=1;i<=n;i++){a=q.top();q.pop();s[i&1]+=a;}
    cout<<s[1]-s[0];
    return 0;
}

```

---

## 作者：666yuchen (赞：1)

#### 二话不说上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>//文件头
using namespace std;
int n,a[105],gs;//定义变量
bool cmp(int a,int b){return a>b;}
int main()
{
  cin>>n;//输入n
  for(int i=1;i<=n;i++)cin>>a[i];//输入n个数
  sort(a+1,a+1+n,cmp);//从大到小排序
  for(int i=1;i<=n;i++)
   if(i%2==1)gs+=a[i];else gs-=a[i];
  //因为是爱丽丝先拿，所以当i不是2的倍数时，就加把号码加起来，否则就减去号码
  cout<<gs;//输出爱丽丝比Bob多的分数
  return 0;
}//程序拜拜
```
## **杜绝抄袭，人人做起！！！！！**

---

