# [USACO18FEB] Taming the Herd B

## 题目描述

一大清早，Farmer John 就被木材破裂的声音吵醒了。是这些奶牛们干的，她们又逃出牛棚了！

Farmer John 已经厌烦了奶牛在清晨出逃，他觉得受够了：是时候采取强硬措施了。他在牛棚的墙上钉了一个计数器，追踪从上次出逃开始经过的天数。所以如果某一天早上发生了出逃事件，这一天的计数器就为 $0$；如果最近的出逃是 $3$ 天前，计数器读数就为 $3$。Farmer John 一丝不苟地记录了每一天计数器的读数。

年末到了，Farmer John 准备做一些统计。他说，你们这些奶牛会付出代价的！然而意想不到的是，他的记录的一些条目竟然丢失了！

Farmer John 确信他是在发生出逃的某一天开始记录的。请帮助他确定，在所有与残留记录条目一致的事件序列中，基于记录的时间，最少和最多可能发生的出逃次数。 

## 说明/提示

在这个样例中，我们可以推断第 $3$ 天必然有出逃发生。我们已经知道在第 $1$ 天也发生了出逃，所以最后不确定的只有第 $2$ 天是否发生了出逃。因此，总共发生了 $2$ 至 $3$ 次出逃。 

## 样例 #1

### 输入

```
4
-1 -1 -1 1```

### 输出

```
2 3```

# 题解

## 作者：xuan_never (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P1711)  
题意明确，不在此赘述。

## 思路
我们要根据残留记录，**反推**出能确定的丢失的记录，求出最多与最少出逃次数。在我们确定了能确定的全部记录后，最少出逃次数即为记录中**确定的**出逃次数，最多出逃次数则要**加上不确定**记录的个数。

## 做法
枚举 $1$ 从 $n$ 至 $1$，对于 $a_{i+1}$ 有记录的，理想 $a_i=a_{i+1}-1$（若 $a_{i+1}$ 记录为 $0$ 也正好使理想 $a_i$ 为 $-1$）。  
当 $a_i$ 原本就有记录，但与理想记录不相等时，就出现了记录错误的情况，此时直接输出 `-1`。

最后记录记录中 $\text{0},\text{-1}$ 的个数即可。

**不要忘了记录第一天的出逃哦**。

## 代码
```cpp
// 码风很丑，勿喷

#include <iostream>
using namespace std;
int n, a[102], ans1, ans2; // ans1记录0，ans2记录-1
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	if (~a[1] && a[1]) { // 记录第一天的出逃，也要判断
		cout << -1;
		return 0;
	} a[1] = 0;
	for (int i = n, j; i >= 1; --i) {
		j = (~a[i + 1] ? a[i + 1] - 1 : -1); // 同上，理想ai
		if (~j) {
			if (~a[i] && a[i] != j) {
				cout << -1;
				return 0;
			} a[i] = j;
		} if (!a[i]) ++ans1; // 记录0和-1
		else if (a[i] == -1) ++ans2;
	} cout << ans1 << ' ' << ans1 + ans2;
	return 0;
}
```

赛前&第一次写题解，RP++。

---

## 作者：player_1_Z (赞：3)

### 先来理解题目
求 Farmer John 的记录是否符合要求。如果你发现不符合要求，输出一个整数 $−1$。否则，输出两个空格分隔的整数表示奶牛的最少和最多逃出次数。
### 思路
首先我们可以用**逆推**的方法做：从我们知道的一天的记录往前推，每次往前走一天，然后数字也减一，如果这天的记录在，就判断是否相同，如果不同，就是不符合要求，直接退出并输出。那么现在已经基本补全了。所以**最少就是当前出现的零的个数**，而最多的情况就是**当前出现的零的个数加上 $-1$ 的个数**，也就是把不确定的全部当作逃跑。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],mi,ma;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(a[1]>0){//第1天的记录就不符合 
		cout<<-1;return 0;
	}
	a[1]=0;
	for(int i=n;i>=1;i--){
		if(a[i]!=-1){
			int j=a[i];
			while(j>=1&&i>=2){
				if(a[i-1]!=-1&&a[i-1]!=j-1){//记录与推算的不符合 
					cout<<-1;return 0;
				}
				a[--i]=--j;//符合就可以改变（是-1的时候，否则相当于没变） 
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0) mi++,ma++;
		if(a[i]==-1) ma++; 
	}
	cout<<mi<<" "<<ma;
	return 0;
}
```

---

## 作者：zsq9 (赞：2)

[AC 记录](https://www.luogu.com.cn/record/194620983)

[传送门](https://www.luogu.com.cn/problem/P1711)

## 思路

因为有缺失记录，得用逆推来算。我们可以确定的出逃数就是最小值，再加上存疑的出逃数就是最大出逃数。还要记录第一天的逃跑，最后要加一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[105],r=0,p=0;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]; 
	if(a[1]>0){
		cout<<-1;
		return 0;
	}
	for(int i=n;i>=2;i--){
  if(a[i]==0) r++; //是0必会逃跑
  		else if(a[i]==-1) p++;//丢失的记录一下，如果算最大就把他们算上丢失
  		else{
  			if(a[i]==a[i-1]){//昨天记录的时间和今天一样是不可能的
  				cout<<-1;
  				return 0;
  			}
  			a[i-1]=a[i]-1;//更新
  		}
  }
	cout<<r+1<<" "<<r+p+1;
	return 0;
}
```

---

## 作者：ydkxj (赞：2)

## 题意

[原题传送门](https://www.luogu.com.cn/problem/P1711)

就是给定 $n$ 个数，表示在 $n$ 天内的记录情况，输出所有事件序列中出逃的最少次数和最多次数。

## Solution

**首先可以明确除去无解后至少有一次出逃，所以得到：**

- 出逃的最小次数就是可以确定的次数。
- 出逃的最多次数就是最小次数加上不确定的次数。

**无解情况下：**

- 当第一天出逃最近大于零，既是无解。（因为题意说过第一天是最开始的，没有比它更前的）。

## CODE

```cpp
#include<iostream>
using namespace std;
int n;
int a[101];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
    int maxn=a[n]+1;
    for(int i=n;i>=1;i--){
        if(a[i]!=-1&&a[i]!=maxn-1&&maxn!=0){
            cout<<-1; 
            return 0;
        }
        if(maxn>0){
            a[i]=--maxn;
        }
        if(a[i]!=-1){
            maxn=a[i];
        }
    }
    int maxx,minx;
    if(a[1]<=0){
        minx=maxx=1;
        for(int i=2;i<=n;i++){
            if(!a[i]){
                minx++;
                maxx++;
            }
            if(a[i]<0){
                maxx++;
            }
        }
        cout<<minx<<" "<<maxx;
    }
	else{
        cout<<-1;
    }
    return 0;
}
```
### 写在题后

有某个醇乐子把
```
a[i]=--maxn;
```
打成了
```
a[i]=maxn--;
```
改了一个多小时，特此铭记，请注意明确思路。

---

## 作者：_qumingnan_ (赞：1)

[题目跳楼机](https://www.luogu.com.cn/problem/P1711)

# 正文开始

## 阅读理解

有 $n$ 个记录，记录了距离这一天逃了牛的最近日子，如果为 $0$，则是逃了牛，为 $-1$，就是不确定。求最少逃几头牛，最多逃几头牛。

## 思路

这道题的大概思路其实很简单，需要我们找出哪些天是一定会逃牛的，就是最少的牛数；而还会剩下一些天是不确定的，因为要最大，所以这些也要加上。

那现在的问题就成了如何找出有哪些天是一定有牛出逃的。

首先，第 $1$ 天是一定有牛逃的，如果第 $1$ 天的记录为正数，就说明农夫 ~~老年痴呆了~~ 记错了，就输出 $-1$。然后，如果为正数，就需要判断第 $i-a_i$ 天是不是为 $0$ 或 $-1$，还需要判断 $i-a_i\sim i$ 之中有没有 $0$ 和 $-1$，如果有 $0$，那就是农夫记错了；如果有 $-1$，那就代表这一天没有牛出逃。

最后，我们再统计一下有多少天一定有牛出逃，多少天不确定就行了。

## 代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[114514];
int mi,ma,l=-1;
signed main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(a[1]>0){cout<<-1;return 0;}//如果第一个是个正数，那就说明农场主老年痴呆了，因为往前是负数 
	else a[1]=0;//第一个一定为真 
	for(int i=2;i<=n;i++){
		if(a[i]==0)continue;
		if(a[i-a[i]]==-1&&a[i]!=-1)a[i-a[i]]=0;//第 i-a[i] 个地方一定是真 
		if((a[i-a[i]]!=0&&a[i]!=-1)||i<=a[i]){cout<<-1;return 0;}//老年痴呆 
		if(a[i]!=-1)
			for(int j=i;j>i-a[i];j--){//往前判断，如果中途有 -1，那么那天一定没牛逃走 
				if(a[j]==-1)a[j]=1;
				if(a[j]==0){cout<<-1;return 0;}//说明上一个出逃的日子不是农场主记录的那样 
			}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0)mi++,ma++;//这个点一定是有牛走 
		if(a[i]==-1)ma++;//不确定 
	}
	cout<<mi<<' '<<ma;
	return 0;
}
```

---

## 作者：tiantianyang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P1711#submit)
### 思路
因为有缺失记录，所以不能正推，得用**逆推**来算。我们可以确定的出逃数就是最小值，再加上存疑的出逃数就是最大出逃数。
### 解题
从 $n$ 开始向前遍历，如果目前的数大于零，并且和前面的数一样，与题意不符就直接输出，不然就更新前面的数。同时统计遍历到这个数时零和负一的个数。

**重点**：第一天必出逃！
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;
	int a[n+5],run=1,pro=0;//run代表确定出逃数 pro->problem存疑出逃数 
	for(int i=1;i<=n;i++)cin>>a[i]; 
	if(a[1]>0){cout<<-1;return 0;}//第一天必定出逃 
	for(int i=n;i>=2;i--)
		if(a[i]==0) run++;//为0说明今天出逃 
		else if(a[i]<0) pro++;//-1说明存疑 
		else{
			if(a[i]==a[i-1]){cout<<-1;return 0;}//今天和昨天不可能一样 
			a[i-1]=a[i]-1;//不一样就更新昨天 
		}
	cout<<run<<" "<<run+pro;//最小数为run最大数为run+pro 
	return 0;//完美收官 
}//20行不到的代码，够简洁了吧！
```

---

## 作者：long_long__int (赞：0)

# 题目解法

当第 $i$ 条记录不为 $-1$ 的时候，说明这条记录还完好，那么第 $i-a_i$ 天就一定会有出逃事件，第 $i-a_i+1\sim i$ 天就一定不会有出逃事件。我们可以用一个数组标记一下，如果第 $i-a_i$ 天之前标记过不可能有出逃事件，那么就无解。

最后，用两个变量统计一下一定会有出逃事件的天数和一定会有出逃事件的天数加上不一定有出逃事件的天数（不包含不可能有出逃事件的天数），输出即可。

代码：
```cpp
#include<bits/stdc++.h>
int n;
int a[105];
int g[105],minn,maxn;//g数组中1为一定有出逃，2为不可能有出逃，0为不确定 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
	}
	g[1]=1;
	for(int i=1;i<=n;i++){
		if(a[i]>i) return printf("-1"),0;
		if(a[i]!=-1){
			if(g[i-a[i]]==2) return printf("-1"),0;
			g[i-a[i]]=1;
			for(int j=i-a[i]+1;j<=i;j++){
				g[j]=2;
			}
		}
	}
	for(int i=1;i<=n;i++){
//		std::cout<<g[i]<<" ";
		if(g[i]==1) minn++,maxn++;
		if(g[i]==0) maxn++;
	}
//	std::cout<<"\n";
	printf("%d %d",minn,maxn);
	return 0;
} 
```

---

## 作者：_Dynamic_Programming (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1711)
# 思路
1. 当第一天出逃最近大于零，既是无解，输出 $-1$。（因为题意说过第一天是最开始的，没有比它更前的）。
2. 除去无解后至少有一次出逃，所以得到：
- 出逃的最小次数就是可以确定的次数。
- 出逃的最多次数就是最小次数加上不确定的次数。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[105];
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int ma = a[n] + 1;
    for(int i = n; i >= 1; i--)
    {
        if(a[i] != -1 && a[i] != ma - 1 && ma != 0)
        {
            printf("-1\n"); 
            return 0;
        }
        if(ma > 0) ma--, a[i] = ma;
        if(a[i] != -1) ma = a[i];
    }
    int ans1, ans2;
    if(a[1] <= 0)
    {
        ans1 = ans2 = 1;
        for(int i = 2; i <= n; i++)
        {
            if(a[i] == 0) ans1++, ans2++;
            else if(a[i] < 0) ans2++;
        }
        printf("%d %d\n", ans1, ans2);
    }
	else printf("-1\n");
    return 0;
}
```

---

## 作者：Zhou_Pinyu (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/P1711)

本题题解是蒟蒻的第一篇题解，求审过！


## 讲解

首先，确定一个问题：奶牛们第一天就会出逃！

其次，当第一天的计数器数据大于 $0$ 时，必然输出 $-1$ 。

出逃最小值是可以被确定的，为输入数据内 $0$ 的个数。

出逃最大值为出逃最小值 $+$ 输入数据内 $-1$ 的个数。

## 代码

准备阶段

```cpp
int n,a[105],sd,sx,s;
```


输入部分

```cpp
cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
```

通过倒序的方式判断是否错误。并记录最大值。

```cpp
for(int i=n;i>=1;i--){
		if(a[i]>0){
			if(a[i-1]==a[i]&&a[i-1]!=-1){
				cout<<-1;
				return 0;
			}
			a[i-1]=a[i]-1;
		}else{
			sd++;
		}
	}
```
统计最小值

```cpp
a[1]=0;
	for(int i=2;i<=n;i++){
		if(a[i]==-1){
			a[i]=a[i-1]+1;
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			sx++;
		}
	}
```

最后，输出！

```cpp
cout<<sx<<" "<<sd;
```

拼在一起，简单处理一下，得到了一段本题的AC代码 

```cpp
// 码风较丑，不喜勿喷
#include<bits/stdc++.h>
using namespace std;
int n,a[105],sd,sx,s;// 准备阶段
int main(){
	// 输入部分
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	// 通过倒序的方式判断是否错误。并记录最大值。
	for(int i=n;i>=1;i--){
		if(a[i]>0){
			if(a[i-1]==a[i]&&a[i-1]!=-1){
				cout<<-1;
				return 0;
			}
			a[i-1]=a[i]-1;
		}else{
			sd++;
		}
	}
	// 统计最小值
	a[1]=0;
	for(int i=2;i<=n;i++){
		if(a[i]==-1){
			a[i]=a[i-1]+1;
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			sx++;
		}
	}
	// 最后，输出!
	cout<<sx<<" "<<sd;
	return 0;
}
```

---

## 作者：125125A (赞：0)

# 解法



我们可以先确定至少有一次出逃（除了无解之外），得到：

1.  出逃次数 $minn$ 可以确定。

2. 出逃次数 $maxx$ 是次数 $minn$ 与不确定的次数的和。

3. 当第一天出逃次数大于就是无解情况了。


# 代码

 ```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int K=200;
int n,arr(1),brr(1),a[K];
main()
{
    std::cin>>n;
    for(int i=1;i<=n;i++) std::cin>>a[i];//输入
    int crr=a[n]+1;
    for(int i=n;i>=1;i--){
        if(a[i]!=-1 && a[i]!=crr-1 && crr!=0)
		{
            cout<<-1; //判断出逃
            return 0;
        }
        if(crr>0) a[i]=crr-1;
        if(a[i]!=-1) crr=a[i];
    }
    if(a[1]<=0)//非特殊情况
	{
        for(int i=2;i<=n;i++)
		{
            if(a[i]==0)//如果没有牛逃出
			{
                ++brr;
                ++arr;
            }
            if(a[i]<0)  arr++;  
        }	
        std::cout<<brr<<" "<<arr;//输出

   } 
    else std::cout<<-1;//特殊情况
    return 0;
}//谢谢审核的管理员，您辛苦了！

---

## 作者：jsisonx (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P1711)
# 题目解答
如果我们知道某一天计数器的数，设该数为 $x$，那么在此之前的 $x$ 天一定没有发生出逃。因此可以从最后一天开始枚举，如果当天计数器的示数不是 $-1$，设该数为 $x$，那么就从这一天开始，每往前 $y$ 天示数记为 $x-y$，直到减为 $0$ 为止。在此期间，如果发现计算出的数与输入当天的示数不符，那么输出 $-1$。

计算答案：设答案最小值为 ```m```，不确定是否出逃的天数记为 ```c```。从头到尾扫一遍，如果当天示数为 $0$，那么这一天一定出逃了，```m++```。如果当天示数还是 $-1$，那么这一天不知道是否出逃，则 ```c++```。最后输出 $m$ 和 $m+c$。

# 代码

```
#include<iostream>
using namespace std;
int main(){
	int n,a[500];
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	a[1]=0;
	int ans=0,c=0;
	for(int i=n;i>0;){
		if(a[i]!=-1){
			int k=a[i]-1,l=1;
			while(k>=0&&l<i){
				if(a[i-l]==-1){
					a[i-l]=k;
				}
				else{
					if(a[i-l]!=k){
						cout<<-1;
						return 0;
					}
				}
				k--;
				l++;
			}
			i-=l;
		}
		else{
			i--;
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==-1){
			c++;
		}
		else if(a[i]==0){
			ans++;
		}
	}
	cout<<ans<<' '<<c+ans;
	return 0;
}
```

---

