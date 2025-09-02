# Berland Bingo

## 题目描述

袋子里有 $100$ 个球，编号从 $1$ 到 $100$ 。有 $n$ 个人参与游戏，每人手上都有 $1$ 张卡片，每张卡片上有不超过 $100$ 个 $\le 100$ 的正整数，**每张卡片上的数字一定不同**。现在依次从袋子里取出这些球，每取出一个球，所有人就把他的卡片上数字跟这个球编号相同的数字划掉。只要一个人手上的卡片上没有数字了，他就获胜，特别的，如果有多人手上的卡片上没有数字了，那么这些人都算输。

## 样例 #1

### 输入

```
3
1 1
3 2 4 1
2 10 11
```

### 输出

```
YES
NO
YES
```

## 样例 #2

### 输入

```
2
1 1
1 1
```

### 输出

```
NO
NO
```

# 题解

## 作者：__Cyn__ (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF370B)

思路：枚举每个人的卡片上的数字是否是其他人的子序列即可，数据小，不需要考虑时间。如果第 $j$ 个人卡片上有数字是第 $i$ 个人卡片上有数字的子序列，那么第 $i$ 个人不可能获胜，因为第 $i$ 个人的手牌没有时，第 $j$ 个人也没有手牌，两人都会输。而卡片上有数字，也不可能赢。

所以按思路判断即可。

---

## 作者：helongyun (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF370B)
# 思路
用数组记录每一个人的卡片，如果某一个人卡片是另一个人卡片数字的子序列，这个人就可以判输了，依此思路，使用暴力解决即可。

---

## 作者：huangzilang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF370B)

我的思路是：输入时用一个数组记录一下第 $i$ 个人手里的卡片，把卡片标记为 $1$，如果第 $j$ 个人卡片上有数字是第 $i$ 个人卡片上有数字，那么第 $i$ 个人不可能获胜。

所以按思路判断即可。

---

## 作者：Furina_Saikou (赞：0)

# 思路

对于每个人，我们看他赢不赢只需要判断他的序列是否完全包含另一个人的序列，若包含就一定赢不了，否则一定能赢。因为如果包含了 A 包含了 B 的序列，那么 B 要么在 A 之前拿完获胜，要么两人同时拿完输掉。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114;
int n,m[N],a[N][N];
bool f[N];
inline bool check(int x)
{
	int cnt=0;
	for(int i=1;i<=m[x];i++)
	{
		cnt+=f[a[x][i]];
	}
	return cnt!=m[x];
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>m[i];
        for(int j=1;j<=m[i];j++)
        {
        	cin>>a[i][j];
		}
    }
    for(int i=1;i<=n;i++)
    {
    	memset(f,0,sizeof f);
    	for(int j=1;j<=m[i];j++)
    	{
    		f[a[i][j]]=1;
		}
    	bool flag=0;
    	for(int j=1;j<=n;j++)
    	{
    		if(i==j)continue;
    		if(!check(j))
    		{
    			flag=1;
    			break;
			}
		}
		if(flag)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

设第 $i$ 个人的牌集合为 $S_i$。

如果有 $1 \le i \le n$ 且 $i \neq j$ 使得 $S_j \in S_i$，那么第 $i$ 个人不可能赢。因为在这种情况下，第 $i$ 个人牌上的数字个人不可能在第 $j$ 个人之前被全部消除掉。

直接暴力判断即可。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e2+5;
int n;
bool a[maxn][maxn],b[maxn][maxn]; 
bool check(bool x[],bool y[]){ 
	int k=0,cnt=0;
	for(int i=1;i<=100;i++) if(x[i]) k++;
	for(int i=1;i<=100;i++) 
		if(x[i] && y[i]) cnt++;
	if(k==cnt) return 1;
	return 0;
}
int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		int m;
		cin >> m;
		for(int j=1,x;j<=m;j++){
			cin >> x;
			a[i][x]=1;//记录
		}
	}
	for(int i=1;i<=n;i++){
		bool flag=0;
		for(int j=1;j<=n;j++)
			if(i!=j && check(a[j],a[i])){//判断j集合是否是i集合的子集 
				flag=1;
				break;
			}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

---

## 作者：shiziyu111 (赞：0)

## 题目大意
~~注意：本题虽然名字叫"Berland Bingo"，但与 Bingo 没多大关系~~。

给定你每个人卡片上的数字，只要卡片上的数字与取出来的球的数字一样，就可以消掉数字，率先消掉数字的人获胜（在同一时间消掉的全算作失败）。

问他们中的每一个人是否可以通过调换球的顺序获胜？

## 分析
对于此题，如果你毫无头绪的话，可以先看看样例的前两个人。

```
1
2 4 1
```

很明显，由于第一个人拥有的 $1$ 第二个人也同样拥有，所以只要抽到了 $1$ 第一个人就会直接胜利，第二个人不可能获胜。

所以，一旦某个人拥有另一个人的所有数字，前者将必输无疑！

于是，我冥思苦想，想找到一个时间复杂度尽可能小的方法，可是我根本想不到。

就在这关键时刻，我瞥见了那一抹 $n,m_i,a_{i,k}\le100$。

我决定了：还想什么最优解，直接暴力！

于是就有了以下代码：
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,xu[105],c[105][105],a[105][105];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>xu[i];
		for(int j=1;j<=xu[i];j++)
		{
			cin>>c[i][j];
			a[i][c[i][j]]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int flag=1;
		for(int j=1;j<=n;j++)
		{
			if(i!=j)
			{
				int pd=1;
				for(int k=1;k<=xu[j];k++)
				{
					if(a[i][c[j][k]]==0)
					{
						pd=0;
					}
				}
				if(pd==1)
				{
					flag=0;
				}
			}
		}
		if(flag==1)
		{
			cout<<"YES";
		}
		else
		{
			cout<<"NO";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：lichenzhen (赞：0)

## 题目大意
**本题目前翻译有误，下面是我根据原题面简化的题目**

袋子里有 $100$ 个球，编号从 $1$ 到 $100$。有 $n$ 个人参与游戏，每人手上都有 $1$ 张卡片，每张卡片上有不超过 $100$ 个 $\le 100$ 的正整数，**每张卡片上的数字一定不同**。现在依次从袋子里取出这些球，每取出一个球，所有人就把他的卡片上数字跟这个球编号相同的数字划掉。只要一个人手上的卡片上没有数字了，他就获胜，特别的，如果有多人手上的卡片上没有数字了，那么这些人都算输。

现在求在最佳状态下，每个人结果是赢还是输。

## 题目解法
题目还是比较简单，一个人要想让自己赢得比赛，很明显最优方案就是每次摸出来的都是他卡片上有的数字。

如果其他人卡片上的数字序列是当前人卡片的数字序列的子序列，此时这个人就没法赢，因为有人会比他早或者一起划掉所有的数字。

由于数据范围很小，因此本题目直接用暴力循环找其他人是否是当前人的子序列。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define N 110
using namespace std;
int n,m[N],book[N],p[N][N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>m[i];
		for(int j=1;j<=m[i];j++)
			cin>>p[i][j];
	} 
	for(int i=1;i<=n;i++){
		memset(book,0,sizeof(book));
		for(int j=1;j<=m[i];j++) book[p[i][j]]++;//入桶 
		int f=0;
		for(int j=1;j<=n;j++){
			int ans=0;
			if(i!=j){
				f=0;
				for(int k=1;k<=m[j];k++){
					if(book[p[j][k]]!=0) ans++;//如果与当前人有的数字相同 
				}
				if(ans==m[j]){//如果该人所有的数字都与当前人有的数字都相同 
					f=1;
					break;//有一个人会导致当前人输就没必要继续扫了 
				}
			}
		}
		if(f==1) cout<<"NO\n";
		else cout<<"YES\n";
	}
} 
```



---

## 作者：Jur_Cai (赞：0)

### 题意
每个人手中有一张牌，牌上有一些数字，保证一张牌上没有相同的数字。每次会选择一个数字，将所有牌上的这个数字删去 ( 若没有则不操作 )。最先删去所有数字的人获胜，如果同时有多个人删光，则不存在胜者。对于每个人判断在最优情况下能否获胜。

### 分析
一个人的最优情况显然是删去的数都是他牌上的数，不能获胜的情况就是有人在他前面或同时删完，即有人的数字集合是他数字集合的子集。

实现就把当前这个人的数字扔到桶里，对于其他每个人判断是否有多余的数字。

### Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[105][105];
bool have[105];
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i][0]);
		for(int j=1;j<=a[i][0];j++) scanf("%d",&a[i][j]);
	}
	for(int i=1;i<=n;i++) {
		memset(have,0,sizeof(have));
		for(int j=1;j<=a[i][0];j++) have[a[i][j]]=1;
		bool flag=0;
		for(int j=1;j<=n;j++) {
			if(i==j) continue;
			flag=1;
			for(int k=1;k<=a[j][0];k++)
				if(!have[a[j][k]]) {
					flag=0;
					break;
				}
			if(flag) break;
		}
		if(flag) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

