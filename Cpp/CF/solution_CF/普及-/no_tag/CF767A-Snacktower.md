# Snacktower

## 题目描述

According to an old legeng, a long time ago Ankh-Morpork residents did something wrong to miss Fortune, and she cursed them. She said that at some time $ n $ snacks of distinct sizes will fall on the city, and the residents should build a Snacktower of them by placing snacks one on another. Of course, big snacks should be at the bottom of the tower, while small snacks should be at the top.

Years passed, and once different snacks started to fall onto the city, and the residents began to build the Snacktower.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767A/180cab69cae65dd25cd78379f99c54f80aacaf67.png)However, they faced some troubles. Each day exactly one snack fell onto the city, but their order was strange. So, at some days the residents weren't able to put the new stack on the top of the Snacktower: they had to wait until all the bigger snacks fell. Of course, in order to not to anger miss Fortune again, the residents placed each snack on the top of the tower immediately as they could do it.

Write a program that models the behavior of Ankh-Morpork residents.

## 说明/提示

In the example a snack of size $ 3 $ fell on the first day, and the residents immediately placed it. On the second day a snack of size $ 1 $ fell, and the residents weren't able to place it because they were missing the snack of size $ 2 $ . On the third day a snack of size $ 2 $ fell, and the residents immediately placed it. Right after that they placed the snack of size $ 1 $ which had fallen before.

## 样例 #1

### 输入

```
3
3 1 2
```

### 输出

```
3
 
2 1```

## 样例 #2

### 输入

```
5
4 5 1 2 3
```

### 输出

```
 
5 4
 
 
3 2 1
```

# 题解

## 作者：CZ_7 (赞：2)

### 这道题就是一个模拟题，但是需要亿些卡常能力

首先明确一下题意：

```
糖果必须从大往小放，如果没法放就不放，否则能放多少就多少。
```
那么我们就可以定义两个数组，一个存储有的糖，一个存储放的糖。

从大往小循环，如果有的糖有且没放，就输出，否则就break不就可以了嘛！

那么就来试一试吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100002];
bool flag[100002],put[100002];//有的和放了的
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		flag[a[i]]=true;//有了
		for(int j=n;j>=1;j--){//从大往小枚举
			if(flag[j]&&!put[j]){//有且没放
				put[j]=true;//放
				cout<<j<<' ';//输出
			}
			if(!flag[j])break;//少糖退出
		}
		cout<<endl;//一天结束了
	}
	return 0;
}
```
看起来挺不戳的，结果。。。

### #19 TLE

那怎么办呢？可以加亿点优化：

1.添加
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
```
2.a数组没有用，直接加快读输入
```cpp
int read(){
	int a=0,b=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')b=-1;c=getchar();}
	while(c>='0'&&c<='9')a=a*10+c-48,c=getchar();
	return a*b;
}

```
```cpp
a=read();
flag[a]=true;
```
3.不用从头找，定义一个top存储每天已经放上去的最小值，并使用快速输出
```cpp
int top;
```
```
for(int j=top;j>=n-i;--j){
	if(flag[j]&&!put[j]){
		put[j]=true;
		printf("%d ",j);
		top=j;
	}
   	if(!flag[j])break;
}
putchar('\n');
```
在加一个优化：如果现在糖的大小还没有 总大小-糖数多，那肯定放不上去了，输出回车。
```
if(a<n-i){
	putchar('\n');
	continue;
}
```
整代码如下：
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
int read(){
	int a=0,b=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')b=-1;c=getchar();}
	while(c>='0'&&c<='9')a=a*10+c-48,c=getchar();
	return a*b;
}
int n,top,a;
bool flag[100002],put[100002];
int main(){
	n=read();
	top=n;
	for(int i=1;i<=n;++i){
		a=read();
		flag[a]=true;
		if(a<n-i){
			putchar('\n');
			continue;
		}
		for(int j=top;j>=n-i;--j){
			if(flag[j]&&!put[j]){
				put[j]=true;
				printf("%d ",j);
				top=j;
			}
			if(!flag[j])break;
		}
		putchar('\n');
	}
	return 0;
}
```
## 大家RP++!

---

## 作者：伟大的王夫子 (赞：1)

本题题意大概为，给你$n$个糖果，必须从大到小依次放，可以放便直接放，让你输出放的方案。

按题目模拟即可

很明显，每次我们输入一个糖果，都要从$val$开始遍历每一个糖果，看看他们有没有出现过。如果有，就输出。如果没有，那么当天不再放糖果，换行并输入下一颗糖果的值。这样便保证了，输出的糖果是连续的。而$val$则是当前最大的没有放的糖果。可以在放糖果的时候直接计算。每次放糖果时，直接从$val$开始放，因为$val+1 \to n$的糖果都已经被放好。

上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100010], val ;
bool v[100010], f[100010];
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	val = n;
	for (register int i = 1; i <= n; ++i) {
		f[a[i]] = 1;
		for (register int j = val; j >= 1; --j) {
			if (f[j] && !v[j]) {
				v[j] = 1;
				printf("%d ", j);	
			}//放糖果
			val = min(val, j);//计算val
			if (!f[j]) break;
			
		}
		puts("");//别忘了换行
	}
} 
```
别忘了换行！~~否则你会死的很惨~~

---

## 作者：Smg18 (赞：0)

数据仅仅小于等于一万，时间不用愁。

本题大模拟，我们从 $k$ 开始，一直往下模拟，判断是否出现，$k$ 为当前应该放的，数组看有没有掉下过，如果有则改变数组状态。

从大往小找糖果，如果有就直接输出，没有就当天不再放，换行去输出。

如果超出我们则已经处理过了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e7+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,ans=0,t=0,l,r,len,T,flag[N];
ll mini=INT_MAX,maxi=0,Mod;
string s1,s2;

int main(){
	cin>>n;//输入共多少糖q 
	k=n;//目前糖的大小 
	F(i,1,n){//模拟每天情况 
		cin>>m;//每天糖的变量
		flag[m]=114514;// 代表一出现，避免再度出现 
		if(m==k){//如果满足条件并且没放过
			cout<<k<<" ";
			k--;//输出蛋糕大小，大小要变小才能继续输出 
			while(flag[k]==114514){
				cout<<k<<" ";
				k--;//同上
			}
			
		
		} cout<<"\n";
	}
	return 0;
}

```

[正确记录。](https://codeforces.com/problemset/status?my=on)

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF767A)

# 思路：

在每一天判断当前掉落的蛋糕是否是现在需要摆放的蛋糕。

如果是，那么把储存的蛋糕从后往前逐个枚举，看是否可以继续放。

否则将这个蛋糕存着。

# 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	bool a[100005];//a[i] 为 1 ，则代表重量为 i 的大小的蛋糕已经出现，否则没有 
	int n,x;//n 为总天数， x 是当前掉落蛋糕的大小
	cin>>n;
	int now=n;//now 为当前需要放的蛋糕的大小（初始化为 n ）
	memset(a,0,sizeof(a));//a 数组初始化为 0 
	for(int i=1;i<=n;i++){
		cin>>x;
		a[x]=1;//标记当前大小的蛋糕已经出现 
		if(x==now){//当前蛋糕需要摆放 
			cout<<now<<" ";//输出当前蛋糕的大小 
			now--;//需要的蛋糕的大小 -1 
			while(a[now]==1){//当现在存储的蛋糕还可以继续摆放时 
				cout<<now<<" ";//输出当前蛋糕的大小 
				now--;//需要的蛋糕的大小 -1 
			}
		}
		cout<<endl;//注意换行 
	}
	return 0;//完美结束 
}
```


---

## 作者：Noby_Glds (赞：0)

### 思路：
我们用 $p$ 来记录当前塔上应当放多大的糖果。

用 $b$ 数组记录当前大小的糖果有没有掉下来。

如果该天掉下来的糖果的大小为 $p$，就直接输出，同时 $p$ 减一。

接着进入循环，如果 $p$ 大小的糖果已经掉下来了，再输出，$p$ 减一，直到 $p$ 大小的糖果没有掉下来。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,a,b[100010];
int main(){
	cin>>n;
	p=n;
	for(int i=1;i<=n;i++){
		cin>>a;
		b[a]=1;
		if(a==p){
			cout<<a<<" ";
			p--;
			while(b[p]==1) cout<<p<<" ",p--;
		}
		cout<<endl;
	}
    return 0;
}
```


---

