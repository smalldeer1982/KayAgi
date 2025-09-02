# You Are Given a Decimal String...

## 题目描述

你现在有一个神奇的计算器，~~这是闪现牌计算器（洛谷独家赞助，codeforces特别生产），~~ 这种计算器被称为$x-y$计算器。

因为是~~闪现牌~~神奇计算器，所以它的操作也非常神奇。这个计算器的初始数值为$0$，然后你可以加一个数值$x$或$y$。当然，在这一步之前，你需要先输出当前数值的最后一位。

这是$4-2$的一种情况：

1. 输出$0$，然后加上$4$，当前数值为$4$，当前输出$0$。
1. 输出$4$，然后加上$4$，当前数值为$8$，当前输出$04$。
1. 输出$8$，然后加上$4$，当前数值为$12$，当前输出$048$。
1. 输出$2$，然后加上$2$，当前数值为$14$，当前输出$0482$。
1. 输出$4$，然后加上$4$，当前数值为$18$，当前输出$04824$。

当然，这只是一种情况。如果我们每次都加$2$，还可以得到$0246802468024$这个序列。

现在你有一个由$x-y$计算器得到的序列$s$，但是由于这个计算器为初代产品，某些数字丢失了。

然而你想恢复这个序列，不过问题是你并不知道这是哪一款$x-y$计算器（即不知道$x$与$y$的大小），所以对于每一款$x-y(0≤x,y<10)$计算器，输出使序列$s$变为能由该款计算器能得到的序列最小所需插入的数字数。

## 样例 #1

### 输入

```
0840
```

### 输出

```
-1 17 7 7 7 -1 2 17 2 7 
17 17 7 5 5 5 2 7 2 7 
7 7 7 4 3 7 1 7 2 5 
7 5 4 7 3 3 2 5 2 3 
7 5 3 3 7 7 1 7 2 7 
-1 5 7 3 7 -1 2 9 2 7 
2 2 1 2 1 2 2 2 0 1 
17 7 7 5 7 9 2 17 2 3 
2 2 2 2 2 2 0 2 2 2 
7 7 5 3 7 7 1 3 2 7 
```

# 题解

## 作者：ttwyzz (赞：5)

# CF1202B

关于这道抽象的又奇怪的图论题 ...

由于~~某些原因~~（还是因为太菜）在一次考试中没写出来，所以特来发一篇题解给自己点安慰 。


唔 ....


------------

计算时间复杂度是 $O(10^2\,\,(\,n\,+\,10^3)\,)$  此处的 $n$ 指字符长度 。

##### 正题：

[传送门](https://www.luogu.com.cn/problem/CF1202B)

这道题首先我们来枚举 $x$ 和 $y$ ,因为题目要求我们要求出 一个 10×10 的矩阵 由i-j计算器能得到的序列最小所需插入的数字数 。

而矩阵里则是在输入的一个串中至少需要添加几个字符 ；

所以我们就需要求出 $i$ 到 $j$ 需要加字符的最小值从而在矩阵中找到答案 。
```
for(int l = 0; l < len - 1 ; ++l)
{
	if(a[s[l] - '0'][s[l+1] - '0'] == 0x3f3f3f3f3f3f3f3f)
	{
		ans[n][m] = -1;
		break;
	}
	ans[n][m] += a[s[l] - '0'][s[l+1] - '0'] - 1;
}
```

关于这个地方的 -1 楼上没有解释，那我来解释一下 。

大家可以想一想，在这个题中，我们已经求出从一个字符到另一个字符的最少字符数，但是他题目问的睡是 _**最小所需插入的字符数**_ 是不是悟到了 ？（嘿嘿）

所以接下来就跑一遍Floyd然后查询就差不多了 ；



------------


最后一个关于初始化的问题

从i向(i+x)  $mod$  10, 连一条边权为1的单向边.

从i向(i+y)  $mod$  10, 连一条边权为1的单向边.

在题解开头我有说“抽象的奇怪的图论题” 为什么这么说呢 ？

```
memset(a, 0x3f , sizeof a);
for(int k = 0; k <= 9; ++k) // k用来枚举点初始化 
{
	//a[k][k] = 0;    
	a[k][(k+n) % 10] = 1;
	a[k][(k+m) % 10] = 1;
}
```
在这里我把  "  a[k][k] = 0; " 这句话注释掉了，原因呢就是掉了#2的点，然后在机房大佬的帮助下我悟了 。

我们来想一个问题，当有两个相同的数字相邻那这时候这两个一定不是相同的数，他们只是个位相同而已，所以我们当然就不能将它赋为 $0$ 嘛 。

欧克！ 上代码 。


------------

## code：


```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;
ll a[20][20] , ans[20][20];
int main()
{
	cin >> s;
	int len = s.size();
	for(int n = 0; n <= 9; ++n)
	{
		for(int m = 0; m <= 9; ++m)
		{
			memset(a, 0x3f , sizeof a);
			for(int k = 0; k <= 9; ++k) // k用来枚举点初始化 
			{
				//a[k][k] = 0;    
				a[k][(k+n) % 10] = 1; 
				a[k][(k+m) % 10] = 1;
			}
			for(int l = 0; l <= 9; ++l) // 跑一遍floyd
			{
				for(int i = 0; i <= 9; ++i)
				{
					for(int j = 0; j <= 9; ++j)
					{
						a[i][j] = min(a[i][j] , a[i][l] + a[l][j]); 
					}
				}
			}
			for(int l = 0; l < len - 1 ; ++l)
			{
				if(a[s[l] - '0'][s[l+1] - '0'] == 0x3f3f3f3f3f3f3f3f) 
				{
					ans[n][m] = -1;
					break;
				}
				ans[n][m] += a[s[l] - '0'][s[l+1] - '0'] - 1;
			}
		}
	}
	for(int i = 0; i <= 9; ++i)
	{
		for(int j = 0; j <= 9; ++j)
		{
			if(i <= j)
			cout << ans[i][j] <<' ';
			else
			cout << ans[j][i] <<' ';
		}
		cout << endl;
	}
	return 0;
}
```
最后
ps: 关于memset.

------------

```
memset(a, 0x3f , sizeof a);
```

------------
memset 本质上是以字节来赋的,

举个栗子  :

如果 a数组是 int 类型 那么它数组里面是0x3f3f3f3f（4个），
但是如果是long long 类型那就是,0x3f3f3f3f3f3f3f3f(8个)

好啦  !

完结撒花 !





---

## 作者：zhanghengrui (赞：2)

显然，假设从$a$到$b$需要$k\space(k>0)$次操作，那么$a$和$b$之间至少补$k-1$个数字。

而在$x$-$y$-counter中，$k=\min\limits_{a+ix+jy\equiv b\pmod{10}\space\space and\space ij\ne0}{\{i+j\}}$（如果可以从$a$到$b$）

所以只要预处理出每个$x$-$y$-counter中从某个数到另一个数需要的操作次数，然后扫一遍读入的字符串就可以了

注意判断无法操作的情况

时间复杂度$\text{O}(|s|)$（还有个常数）

---

code

```cpp
#include <climits>	// LONG_MAX
#include <cstdio>	// scanf, printf
#include <algorithm>	// std::min
#define len_s_MAX 2000000L
char s[len_s_MAX + 1L];
//F[i][j][k][l]表示在i-j-counter中从k到l需要的操作次数，ans存答案
long F[10][10][10][10], ans[10][10];
int main()
{
	for (long i = 0L; i < 10L; ++i)
	{
		for (long j = 0L; j < 10L; ++j)
		{
			for (long k = 0L; k < 10L; ++k)
			{
				for (long l = 0L; l < 10L; ++l)
				{
					F[i][j][k][l] = LONG_MAX >> 1;//赋为极大值
					for (long m = 0L; m < 10L; ++m)
					{
						for (long n = 0L; n < 10L; ++n)
						{
							if (m == 0L && n == 0L) continue;
							if ((k + m * i + n * j) % 10L == l) F[i][j][k][l] = std::min(F[i][j][k][l], m + n);//满足条件就更新
						}
					}
					if (F[i][j][k][l] == LONG_MAX >> 1) F[i][j][k][l] = -1L;
				}
			}
		}
	}
	scanf("%s", s);
	for (long i = 1L; s[i]; ++i)//scanf默认在字符串结尾加0（或者说'\0'）
	{
		for (long j = 0L; j < 10L; ++j)
		{
			for (long k = 0L; k < 10L; ++k)
			{
				if (ans[j][k] == -1L) continue;//之前就已经无法操作了
				if (F[j][k][s[i - 1L] - '0'][s[i] - '0'] == -1L) ans[j][k] = -1L;//这一步无法操作
				else ans[j][k] += F[j][k][s[i - 1L] - '0'][s[i] - '0'] - 1L;
			}
		}
	}
	for (long i = 0L; i < 10L; ++i)
	{
		for (long j = 0L; j < 10L; ++j) printf(j == 9L ? "%ld\n" : "%ld ", ans[i][j]);
	}
	return 0;
}
```

---

## 作者：世末OIer (赞：1)

计算时间复杂度是O(100n)，n<=$2*10^6$,~~不知道怎么过的~~

---

预处理:循环枚举从i到j用了a和b的最小步骤。bfs求即可。

然后循环枚举a,b，再循环字符串累加即可。

~~码量再d2B中算很大的了~~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
int n,x,y;
string s;
int pre[11][11][11][11];
bool use[11];
inline void solve(){
	cin>>s;
	for(int i=0;i<10;++i){
		for(int j=0;j<10;++j){
			for(int a=0;a<10;++a){
				for(int b=0;b<10;++b){
					queue<pair<int,int> >q;  //bfs
					while(!q.empty())q.pop();
					memset(use,0,sizeof(use));
					q.push(mp(a,0));
					pre[i][j][a][b]=-1;
					while(!q.empty()){
						int p=q.front().first,cst=q.front().second;q.pop();
						if(p==b and cst>0){
							pre[i][j][a][b]=cst;
							break;
						}
						if(use[p])continue;
						use[p]=1;
						q.push(mp((p+i)%10,cst+1));
						q.push(mp((p+j)%10,cst+1));
					}
				}
			}
		}
	}
	for(int i=0;i<s.size();++i)s[i]-='0';
	for(int i=0;i<10;++i){
		for(int j=0;j<10;++j){
			bool ok=1;
			int ans=0;
			for(int f=1;f<s.size();++f){
				if(pre[i][j][s[f-1]][s[f]]==-1){
					ok=0;
					break;
				}
				ans+=pre[i][j][s[f-1]][s[f]];  //累加
			}
			if(ok==0)cout<<-1<<' ';
			else cout<<ans-s.size()+1<<' ';
		}
		cout<<endl;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	solve();
}
```

---

## 作者：tzc_wk (赞：1)

### 题意：
给你一个由$0$到$9$组成的字符串。对于所有的$x=0,1,\dots,9$，$y=0,1,\dots,9$，问你最少添加多少个数码使得相邻两个数码的差$mod\ 10$要么等于$i$，要么等于$j$，数码可以在任意位置添加。

### 思路：
首先先$O(10^5)$预处理出在$0$和$k$之间最少添加多少个数码使得相邻两个数码的差$mod\ 10$要么等于$x$，要么等于$y$，用$a_{x,y,k}$记录。然后暴力即可。但是有一个非常恶心的坑点：相邻两个字符相同的情况要特判。这也就是为什么现场很多人WA $2$，从而没有过这道题的原因。~~我比赛的时候也在这里死了好几次。~~

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int a[11][11][11],ans[11][11];
signed main(){
	cin>>s;
	memset(ans,0,sizeof(ans));
	memset(a,63,sizeof(a));//初始化成INF
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			for(int k=0;k<10;k++){
				for(int p=0;p<=10;p++){
					for(int q=0;q<=10;q++){
						if((i*p+j*q)%10==k){
							int x=k;
							if(x==0)	x=10;//相邻两数相等的情况要特判一下
							if(x==10&&(p==0&&q==0))	continue;
							a[i][j][x]=min(a[i][j][x],p+q);
						}
					}
				}
			}
	for(int i=0;i<s.size()-1;i++){
		int dig1=s[i]-'0',dig2=s[i+1]-'0';
		int dif=(dig2-dig1+20)%10;
		if(dif==0)	dif=10;//两数相等的情况
		for(int j=0;j<10;j++){
			for(int k=0;k<10;k++){
				if(~ans[j][k]){//如果当前ans[j][k]不是-1
					if(a[j][k][dif]==0x3f3f3f3f)	ans[j][k]=-1;//判-1
					else							ans[j][k]+=a[j][k][dif]-1;//更新ans[j][k]
				}
			}
		}
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			cout<<ans[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

