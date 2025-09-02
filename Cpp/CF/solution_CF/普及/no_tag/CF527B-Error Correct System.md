# Error Correct System

## 题目描述

Ford Prefect got a job as a web developer for a small company that makes towels. His current work task is to create a search engine for the website of the company. During the development process, he needs to write a subroutine for comparing strings $ S $ and $ T $ of equal length to be "similar". After a brief search on the Internet, he learned about the Hamming distance between two strings $ S $ and $ T $ of the same length, which is defined as the number of positions in which $ S $ and $ T $ have different characters. For example, the Hamming distance between words "permanent" and "pergament" is two, as these words differ in the fourth and sixth letters.

Moreover, as he was searching for information, he also noticed that modern search engines have powerful mechanisms to correct errors in the request to improve the quality of search. Ford doesn't know much about human beings, so he assumed that the most common mistake in a request is swapping two arbitrary letters of the string (not necessarily adjacent). Now he wants to write a function that determines which two letters should be swapped in string $ S $ , so that the Hamming distance between a new string $ S $ and string $ T $ would be as small as possible, or otherwise, determine that such a replacement cannot reduce the distance between the strings.

Help him do this!

## 说明/提示

In the second test it is acceptable to print $ i=2 $ , $ j=3 $ .

## 样例 #1

### 输入

```
9
pergament
permanent
```

### 输出

```
1
4 6
```

## 样例 #2

### 输入

```
6
wookie
cookie
```

### 输出

```
1
-1 -1
```

## 样例 #3

### 输入

```
4
petr
egor
```

### 输出

```
2
1 2
```

## 样例 #4

### 输入

```
6
double
bundle
```

### 输出

```
2
4 1
```

# 题解

## 作者：nxd_oxm (赞：0)

# 题意
题目说给两个字符串，并且可以交换第一个字符串中的两个字符，使新的字符串和第二个字符串差的字符最少

# 思路
一道简单的模拟题。

首先要存储对应关系，我们就用一个桶。

用 $mp_{i,j}$ 表示字符 $i$ 对应字符 $j$。因为样例解释说了 ``In the second test it is acceptable to print i=2 , j=3``，也就是可以输出任意可行最优解，所以我们不用考虑重复。

先累计原来的不一样的点，再用一个循环判断当前的 $a_i$ 与 $b_i$ 有没有对应的反着的 $mp_{b_i,a_i}$，这样可以最优化，减少 $2$ 个，直接跳出循环。

如果没有，再判断有没有 $mp_{b_i,0}$。这个指的是 $b_i$ 有可以换的但是不是 $a_i$。这样可以少 $1$ 个。循环枚举所有不一样的地方，找到最优即可。

时间复杂度 $O(n)$。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int mp[130][130];
int sum=0;
signed main(){
	memset(mp,-1,sizeof mp);
	int n;
	string a,b;
	cin>>n>>a>>b;
	f(i,0,n-1){
		if(a[i]!=b[i]){
			mp[a[i]][b[i]]=i;
			mp[a[i]][0]=i;
			sum++;
		}
	}
//	cout<<sum<<endl;
	int x=-2,y=-2;
	int maxn=0;
	f(i,0,n-1){
		if(a[i]!=b[i]){
			if(mp[b[i]][a[i]]!=-1){
				maxn=2;
				x=i;
				y=mp[b[i]][a[i]];
				break;
			}else if(mp[b[i]][0]!=-1){
				if(maxn<1){
					x=i;
					y=mp[b[i]][0];
					maxn=1;
				}
			}
		}
	}
	cout<<sum-maxn<<endl<<x+1<<" "<<y+1;
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF527B)
一道简单的分类讨论。
# 题目描述
对于两个字符串 $x$，$y$。求交换 $x_{i}$，$x_{j}$ 后的 $x'$ 与 $y$ 的错误字母数量。

输出交换后的错误字母数量，$i$，$j$。

如果不用交换错误字母最少，$i,j$ 均输出 `-1`。

# 题目分析
因为只能交换一次，改变两个字符的位置，也就是答案最多减少 `2`。我们考虑贪心。

对于两次交换，如果两个字符交换相等，即 $x_{i}=y_{j}$，$x_{j}=y_{i}$。此时交换一定最优。因为这样能使错误字母数量减少 `2`，同时题目只需要输出一组答案即可，所以可以见到就输出。

如果交换是两个字符不交换相等，但由一组相等，即 $x_{i}\ne y_{j}$，$x_{j}=y_{i}$。此时交换可以使错误字母数量减少 `1`。在保证没有交换相等的情况下可以输出。

如果交换两个字符都不相等，即 $x_{i}\ne y_{j}$，$x_{j}\ne y_{i}$。此时错误字符数量并没有减少，与不交换相同。此时输出 `-1`。

注意到一共只有 `26` 个不同的字符，只需要开一个二维数组记录 $x_{i},y_{j}$ 是否存在即可。

---

## 作者：liuyifan (赞：0)

## 贪心
1.用vis[a[i]][b[i]]记录ab两个错误的字母的位置

2.判断是否vis[b[i]][a[i]]]存在

3.如果有就换过去距离-2确定最优
如果没有就查看b串是否有位置不与a匹配并且等于a[i]

code：
```cpp
#include<bits/stdc++.h>
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
#define mid ((l+r)>>1)
using namespace std;
char a[1000005],b[1000005];
int vis[3005][3005],mark[1000005],n,sum,x=-1,y=-1;
int main()
{
	memset(vis,-1,sizeof(vis));
	memset(mark,-1,sizeof(mark));//将数组初始化为-1,比for快
	scanf("%d%s%s",&n,a,b);//输入char数组
	for(reg int i=0;i<n;i++)//char数组的下标从0开始
	if(a[i]!=b[i])
	{
		sum++;
		vis[a[i]][b[i]]=i;
		mark[a[i]]=i;
	}//标记
	int ans=sum;
	for(reg int i=0;i<n;i++)
	if(a[i]!=b[i])
	{
		if(vis[b[i]][a[i]]!=-1)return printf("%d\n%d %d",sum-2,i+1,vis[b[i]][a[i]]+1),0;//找到情况1，输出
		else if(mark[b[i]]!=-1)
		{
			ans=min(ans,sum-1);
			x=i+1;
			y=mark[b[i]]+1;//更新
		}
	}
	printf("%d\n%d %d",ans,x,y);//输出情况2
	return 0;
}
```


---

