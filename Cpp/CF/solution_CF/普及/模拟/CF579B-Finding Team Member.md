# Finding Team Member

## 题目描述

There is a programing contest named SnakeUp, $ 2n $ people want to compete for it. In order to attend this contest, people need to form teams of exactly two people. You are given the strength of each possible combination of two people. All the values of the strengths are distinct.

Every contestant hopes that he can find a teammate so that their team’s strength is as high as possible. That is, a contestant will form a team with highest strength possible by choosing a teammate from ones who are willing to be a teammate with him/her. More formally, two people $ A $ and $ B $ may form a team if each of them is the best possible teammate (among the contestants that remain unpaired) for the other one.

Can you determine who will be each person’s teammate?

## 说明/提示

In the first sample, contestant $ 1 $ and $ 2 $ will be teammates and so do contestant $ 3 $ and $ 4 $ , so the teammate of contestant $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ will be $ 2 $ , $ 1 $ , $ 4 $ , $ 3 $ respectively.

## 样例 #1

### 输入

```
2
6
1 2
3 4 5
```

### 输出

```
2 1 4 3
```

## 样例 #2

### 输入

```
3
487060
3831 161856
845957 794650 976977
83847 50566 691206 498447
698377 156232 59015 382455 626960
```

### 输出

```
6 5 4 3 2 1
```

# 题解

## 作者：xiaomuyun (赞：2)

# CF579B Finding Team Member 题解
$update\ 2021$ 年 $10$ 月 $7$ 日：修改了一些勘误

[题目传送门](https://www.luogu.com.cn/problem/CF579B)
## 解法
贪心，在目前的组合里选择力量最大的一组，只要这一组里面的两个人都没有在前面已经被选的组合中，就可以将这两个人作为一组来参加 SnakeUp。
## 要注意的地方
1. **输入**。要注意一共有 $2×n$ 个人，还有就是三角形的输入非常坑人；
2. **排序**。我们首先要找的应该是力量最大的一组，所以从小到大排序后应该**从后往前**遍历每个组合；
3. **判重**。也就是说，前面已经组合过的人不能在组合了。

## 代码
### 1. STL 做法：map
（也不知道怎么想的，这个蒟蒻竟然会想到利用 map 的有序的特性，将力量作为 map 的 key 来排序……）
```cpp
#include<cstdio>
#include<map>

using namespace std;

int n,tot,ans[801];//tot记录的是还没有匹配的人数
bool ok[801];

struct strength{//结构体
	int x,y;
};
map<int,strength> a;

void input(){
	scanf("%d",&n);
	tot=n*2;
	for(int i=2;i<=n*2;++i){//坑人的输入
		for(int j=1;j<i;++j){
			int u;
			scanf("%d",&u);
			a[u]=(strength){i,j};
		}
	}
	return ;
}

void output(){//输出还是要注意一共有n*2个人
	for(int i=1;i<=n*2;++i) printf("%d ",ans[i]);
	putchar('\n');
	return ;
}

int main(){
	input();
	for(map<int,strength>::iterator it=a.end();it!=a.begin(),tot>0;--it){
		if(it==a.end()) --it;//a.end()并不是map的末尾，而是map的末尾+1，而map的end并不能直接-1，所以只能这样
		strength s=it->second;
		int w=it->first;
		if(ok[s.x]||ok[s.y]) continue;//如果其中某一个人已经匹配过了，就可以直接跳过
		ok[s.x]=ok[s.y]=true,tot-=2;//这两个人都匹配好了，还需要匹配的人数应该-2
		ans[s.x]=s.y,ans[s.y]=s.x;
	}
	output();
	return 0;
}
```
### 2. 结构体数组（也是比较普遍的做法）
```cpp
#include<algorithm>
#include<cstdio>

using namespace std;

struct strength{
	int u,v,w;
	//重载运算符
	bool operator <(const strength &s) const{
		return w<s.w;
	}
	bool operator >(const strength &s) const{
		return w>s.w;
	}
}a[800*800];//实际上并不需要那么大，但是只有802的话会RE

int n,tot,ans[802],cnt=0;//cnt记录的是一共有多少种组合方法

int main(){
	scanf("%d",&n);
	tot=n*2;
	for(int i=1;i<=n*2;++i){//还是这样输入
		for(int j=1;j<i;++j){
			int val;
			scanf("%d",&val);
			a[cnt++]=(strength){i,j,val};
		}
	}
	sort(a,a+cnt);
	for(int i=cnt-1;i>0,tot>0;--i){//一定要注意：是倒着遍历！
		strength str=a[i];
		if(ans[str.u]||ans[str.v]) continue;//其实map的代码也可以不用ok数组
		ans[str.u]=str.v,ans[str.v]=str.u,tot-=2;
	}
	for(int i=1;i<=n*2;++i) printf("%d ",ans[i]);
	putchar('\n');//本蒟蒻的奇怪做法
	return 0;
}
```
## 结语
经过这篇文章，作者对贪心的理解又更加深刻了。希望大家可以点个赞，制作不易~

---

## 作者：流绪 (赞：0)

贪心！

要让每个人找到的队友默契度尽量高，那么我们可以用结构体来存数据，然后对默契度对进行排序，再从大到小贪心的配对每一个人，直到每个人都有队友就好啦。

下面是 AC 代码，细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
struct node
{
	int x,y,w,v;
}a[maxn];//x,y是成为队友的两人,w为默契度,v没用,一开始想错了...
int v[maxn]={0},ans[maxn];
int cmp(node a,node b)
{
	return a.w > b.w;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int cnt = 1;
	for(int i=2;i<=2*n;i++)
		for(int j=1;j<i;j++)
		{
			cin >> a[cnt].w;
			a[cnt].x=i;
			a[cnt].y=j;
			a[cnt++].v=0;
		}
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		int x=a[i].x;
		int y=a[i].y;
		if(!v[x]&&!v[y])//如果这两个人还没找到队友
		{ //这里找完每个人的队友就可以退出啦,不过n只有400全部遍历也没事
			v[x] = v[y] = 1;//标记为找到了队友
			ans[x] = y,ans[y] = x ;//记录答案
		} 
	}
	for(int i=1;i<=2*n;i++)
		cout << ans[i] << " ";//输出
	return 0; 
}  
```


---

