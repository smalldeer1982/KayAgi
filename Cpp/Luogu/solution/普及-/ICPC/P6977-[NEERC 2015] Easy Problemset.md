# [NEERC 2015] Easy Problemset

## 题目描述

或许在任何 ACM ICPC 比赛中最难的问题之一就是创建一个包含合理数量简单题目的题集。在 Not Easy 欧洲区域赛中，这个问题是这样解决的。

有 $n$ 名评委（裁判）。他们从 $1$ 到 $n$ 编号。编号为 $i$ 的裁判在评委会议之前准备了 $p_{i}$ 道简单题目。这些题目的难度在 $0$ 到 $49$ 之间（数值越大越难）。每位裁判还知道大量（可以说是无限多）难题（它们的难度为 $50$）。裁判们需要在这次会议中选择 $k$ 道题目用于比赛。

他们开始按裁判编号的升序提出题目。第一位裁判从他剩余的简单题目列表中取出第一道题（如果他已经提出了所有简单题目，则取一道难题）并提出。如果提出的题目难度大于或等于目前已选题目的总难度，则该题目被选中用于比赛，否则被认为太简单。然后第二位裁判也这样做，依此类推；在第 $n$ 位裁判之后，第一位裁判提出他的下一道题，如此循环。这个过程在选出 $k$ 道题目时立即停止。

如果所有裁判都提出了他们的所有简单题目，但仍然选出的题目少于 $k$ 道，那么他们将不顾总难度，选择一些难题来完成题集。

你的任务是计算由裁判们创建的题集的总难度。

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 8
5 0 3 12 1 10
4 1 1 23 20
4 1 5 17 49
```

### 输出

```
94
```

## 样例 #2

### 输入

```
3 10
2 1 3
1 1
2 2 5
```

### 输出

```
354
```

# 题解

## 作者：MoonCake2011 (赞：9)

## 题意整理

有 $n$ 个队列，他们要选 $k$ 个数。选数方案如下。

从前向后遍历所有队列，如果队列为空，那么将数字的总和 $sum$ 加上 50，$k$ 减少 1。

否则，如果 $sum \le$ 队首，将 $sum$ 加上 队首，$k$ 减少 1。

不管咋样，最后将队首出队。

循环以上步骤直到 $k=0$。

## 题目之解

按题意模拟即可，数据范围小，没有太大的技巧。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
queue<int,list<int> >q[20];//把queue的底层容器从deque换成list,更快 
int n,k,sum;
int main() {
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int m;
		cin>>m;
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			q[i].push(x);
		}
	}
	while(k){//选k道题 
		for(int i=1;i<=n;i++){
			if(k==0) break;
			if(q[i].empty()) sum+=50,k--;
			else if(q[i].front()<sum) q[i].pop();
			else sum+=q[i].front(),q[i].pop(),k--;
		}
	}
	cout<<sum;
	return 0;
} 
```

---

## 作者：_Haoomff_ (赞：1)

一看数据 $2\le n\le10,8\le k\le14$，好题，果断打暴力。

从前到后遍历整个队列，每个出题者轮流看一道题。如果一道题的难度大于等于之前选的题的**难度总和**，那么就选择这一道题。否则就跳过当前出题者，轮到下一个出题者。

这里要注意，当队列为空时，也就是没有简单题，那么只能选择难度为 $50$ 的难题。

如果没有简单题了，就选择难度为 $50$ 的难题来凑数，凑到满足 $k$ 道题为止。求最后选择的所有题的**总难度**是多少。时间复杂度 $O(n^2)$。

可得标签：模拟，暴力（doge）。

代码等会补，没时间打。

---

## 作者：Daben1 (赞：1)

**直接模拟即可**

题意：$n$ 个裁判编号为 $1$ 到 $n$。每个裁判都准备了一定数量的难易程度为 $P_{i}$ 的问题。现在需要选择 $k$ 个问题。

**选择的过程**如下：
每次从一个裁判开始选一个，然后 $n$ 个裁判轮着选，直到选够为止。

先从第一个裁判的问题列表中从前往后选一个（如果该裁判地方已经没有问题可选了直接选难度为 $50$ 的题目），如果选中的问题难易程度大于等于已选所有问题的难易程度之和，则该问题被加入比赛，否则丢弃。
然后接着在下一个裁判的问题列表里选。

Tip：这题用Vector存数据更方便

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, k;
vector<int> vec[11];//保存裁判们问题的难度系数
int cnt[11];//每个裁判准备的问题数目
int pos[11];//存第i个裁判的问题列表已经处理到哪个位置了
int main(){
    while(scanf("%d%d", &n, &k) == 2){
        for(int i=0; i<11; i++){
            vec[i].clear();
        }
        memset(pos, 0, sizeof(pos));
        for(int i=1; i<=n; i++){
            scanf("%d", &cnt[i]);
            int tmp;
            for(int j=1; j<=cnt[i]; j++){
                scanf("%d", &tmp);
                vec[i].push_back(tmp);
            }
        }
        int ans = 0;
        while(k > 0){
            for(int i=1; i<=n; i++){
                if(pos[i] < cnt[i]){
                    if(vec[i][pos[i]] >= ans){
                        ans += vec[i][pos[i]];
                        pos[i]++;
                        k--;
                    }
                    else{
                        pos[i]++;
                    }
                }
                else{
                    ans += 50;
                    k--;
                }
                if(k == 0)break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```


---

## 作者：HDZmessi (赞：0)

比较水的一道模拟题，题目描述就是翻译的描述，要求求出难度总和。用用数组或者 STL 容器维护是最好的，暴力 $n^2$ 就能 AC！

本题的意思就是每个出题者轮流看他们手上的第一道题，如果本题难度大于等于难度和，就选入否则就删除并轮到下一个出题者，手上没有题了就看还剩几道题就选几道难度为 $50$ 的题加入题单，最后求题单的总难度是多少。

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
vector<int> p[11];
int main(){
	int n,k;scanf("%d%d",&n,&k);
	for(int i=0;i<11;i++) p[i].clear();
	for(int i=0;i<n;i++){
		int u;cin>>u;
		for(int j=0;j<u;j++){
			int f;cin>>f;
			p[i].push_back(f);
		}
	}
	while(k){
		for(int i=0;i<n;i++){
			if(k==0){
				cout<<ans;
				return 0;
			}
			else if(p[i].empty()){ans+=50*k;cout<<ans;return 0;}
			else{
				if(p[i][0]>=ans) ans+=p[i][0],k--;
				 p[i].erase(p[i].begin(),p[i].begin()+1);
			}
		}
	}
	cout<<ans;
	return 0;
} 
```
语文不好，就不注释了，巨佬应该看的很明白。

---

## 作者：Wangjunhao2011 (赞：0)

这道题翻译没说清楚
## 题意整理
其实就是从前到后遍历所有的队列，如果之前选的难度总和 $sum$ 小于等于当前元素就将此元素加入的难度加入到 $sum$。如果所有元素都遍历完了但还要选题，就一直将 $50$ 加入到 $sum$。

这题就是一道小模拟。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	queue<int>q[11];
	int n,k;cin>>n>>k;
	for(int i=1;i<=n;i++){
		int m;cin>>m;
		for(int j=1;j<=m;j++){
			int b;cin>>b;
			q[i].push(b);
		}
	}
	int cnt=0;
	while(k){
		for(int i=1;i<=n;i++){
			if(k==0){
				cout<<cnt;
				exit(0);//结束程序运行 
			}
			if(q[i].empty()){
				cnt+=50*k;
				cout<<cnt;
				exit(0);//结束程序运行 
			} 
			if(q[i].front()>=cnt)cnt+=q[i].front(),k--; 
			q[i].pop();
		}
	}
	cout<<cnt;
	return 0;
} 
```


---

## 作者：thh_loser (赞：0)

# P6977 [NEERC2015]Easy Problemset题解

## 题意

有 $n$ 个人，每人有一些数，从第一个人开始每人轮流取目前自己的第 $1$ 个数，如果这个数小于之前加入的数的和就跳过，否则加上这个数。如果一个人没有数了就直接加 $50$，直到有 $k$ 个数为止。

## 思路

按题意模拟即可，用队列储存每一个数，依次比较，如果这个数大于等于之前的和，加上这个数。如果需要加入一道难题或难度和已经大于等于 $50$ 时就跳出，剩余的全部出难题，因为后面无论如何也找不到比 $50$ 大的数了，最后输出难度总和即可。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sl,sum,maxx;
int q[20][20],tail[15],head[15];//模拟队列 
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&sl); 
		maxx=max(sl,maxx);//最多的一个人有几个数 
		for(int j=0;j<sl;j++){
			int x;
			scanf("%d",&x);
			q[i][head[i]++]=x;//将其进入队列 
		}
	}
	for(int i=1;i<=maxx;i++){
		for(int j=1;j<=n;j++){
			if(tail[j]<head[j]){//如果队列中还有数 
				if(q[j][tail[j]]>=sum){//如果符合要求 
					sum+=q[j][tail[j]];//加上这道题的难度 
					k--;
				}
				tail[j]++;
			}
			else{
				goto tc;//如果已经要加入一道难题了，那么后面就不可能有简单题加入了
			}
			if(k==0){
				goto tc;//如果已经有k道题了 
			}
			if(sum>=50){//已经比50大了 
				goto tc;
			} 
		}
	}
	tc:
	if(k){
		sum+=50*k;//把差的题加上 
	}
	printf("%d",sum); 
	return 0;
}
```


---

## 作者：yeshubo_qwq (赞：0)

## Description

题面已经说得很清楚了。

补充一下翻译中没有说的：输出的答案应该是**所有题目的难度之和**。

## Solution

模拟出题人选题的过程，并计算答案。

当前这位出题人，如果他有简单题，则判断这道题能否被选上，如果能，直接累加答案，并判断如果选完了就结束，否则扔掉这道题。

如果他没有简单题了，则让他出难题（一个小优化：如果某个人出了难题，那么后面的出题人也只能出难题，出简单题必定不可能被选上，可以直接输出答案加上剩下的题目数乘五十）。

提示：每位出题人的简单题可以用队列（queue）存，可以方便很多。

## Code

```cpp
#include <bits/stdc++.h>
using std::queue;
int n,m,i,x,y,ans;
queue <int> problem[11];
inline void read(int &x){
	char c=getchar();
	while (!isdigit(c)) c=getchar();
	x=(c^48);c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
inline void write(int x){
	if (x>9) write(x/10);
	putchar(x%10+'0');
}
int main(){
	read(n),read(m);
	for (i=1;i<=n;i++)
		for (read(x);x--;)
			read(y),problem[i].push(y);
	while (1)
		for (i=1;i<=n;i++){
			if (problem[i].empty())
				return write(ans+m*50),0;
			x=problem[i].front();
			problem[i].pop();
			if (x>=ans){
				ans+=x;
				if (--m==0) return write(ans),0;
			}
		}
}
```


---

