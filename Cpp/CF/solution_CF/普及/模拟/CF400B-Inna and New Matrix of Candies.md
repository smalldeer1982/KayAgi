# Inna and New Matrix of Candies

## 题目描述

Inna likes sweets and a game called the "Candy Matrix". Today, she came up with the new game "Candy Matrix 2: Reload".

The field for the new game is a rectangle table of size $ n×m $ . Each line of the table contains one cell with a dwarf figurine, one cell with a candy, the other cells of the line are empty. The game lasts for several moves. During each move the player should choose all lines of the matrix where dwarf is not on the cell with candy and shout "Let's go!". After that, all the dwarves from the chosen lines start to simultaneously move to the right. During each second, each dwarf goes to the adjacent cell that is located to the right of its current cell. The movement continues until one of the following events occurs:

- some dwarf in one of the chosen lines is located in the rightmost cell of his row;
- some dwarf in the chosen lines is located in the cell with the candy.

The point of the game is to transport all the dwarves to the candy cells.

Inna is fabulous, as she came up with such an interesting game. But what about you? Your task is to play this game optimally well. Specifically, you should say by the given game field what minimum number of moves the player needs to reach the goal of the game.

## 样例 #1

### 输入

```
3 4
*G*S
G**S
*G*S
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 3
S*G
```

### 输出

```
-1
```

# 题解

## 作者：rain_dew (赞：1)

原题链接：[CF400B Inna and New Matrix of Candies](https://www.luogu.com.cn/problem/CF400B)

建议评橙，阅读理解题。

### 题意：

给出 $n$ 行 $m$ 个字符（$1 \le n \le 1000$，$2 \le m \le 1000$），每次都可以控制多行 `G` 同时向右移动，直到到达 `S` 后同时停止。

问至少需要多少次使得所有的 `G` 抵达到 `S`。若无解，请输出 `-1`。

### 思路：

简单模拟。读入后判断起点 `G` 与终点 `S`。容易发现如果终点在起点左侧一定**无解**并退出，否则记录起点与终点间的距离。

对其距离排序，查重（当然可以使用 `unique` 函数，但要注意先排序）后输出最后数组所剩下的个数即为答案。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char ch[1005][1005];
int n,m,ans,s[1005],g[1005];
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%s",ch[i]+1);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			if (ch[i][j]=='G')
				g[i]=j;
			else
				if (ch[i][j]=='S')
					s[i]=j;
		if (s[i]<g[i])
		{
			printf("-1");
			return 0;
		}
		s[i]=s[i]-g[i];
	}
	sort(s+1,s+n+1);
	ans=n;
//	ans=unique(s+1,s+n+1)-s-1;
	for (int i=1;i<=n;i++)
		if (s[i]==s[i-1])
			ans--;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：L_shadow (赞：0)

这是一道合适的集合练手题。

[传送门](https://www.luogu.com.cn/problem/CF400B)

## 思路：
令 一行中 G 到 S 的距离为间距。

因为可以同时移动多行，所以说，最少的移动次数就是把分别把所有间距相同的 G 移到其对应的 S 的位置。

很明显，移动的次数即为不同的间距的个数。

当然，如果 G 在 S 右边，直接输出 $-1$。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
set<int> se;
int n,m,g,d;
char s;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s;
			if(s=='G') g=j;
			if(s=='S') d=j;
		}
		int num=d-g-1;
		if(num<0){
			cout<<-1;
			return 0;
		}
		se.insert(num);
	}
	cout<<se.size();
	return 0;
}

```


---

## 作者：liuzhongrui (赞：0)

## 思路

一道挺简单的题目，解题的关键就是看看 ```G``` 和 ```S``` 的位置关系，可以利用 set 解决。

我们只需要查找到 ```G``` 和 ```S``` 的下标，如果 ```S``` 在 ```G``` 的左边，无解输出 ```-1```；如果不是这种情况那就是有解的，输出二者之间距离的最小值就好了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y;
int main() {
	cin>>n>>m;
	string s;
	set <int> st;
	for(int i=0; i<n; i++) {
		cin>>s;
		x=s.find('G');
		y=s.find('S');
		st.insert(y-x);
	}
	if(*st.begin() < 0) cout << -1;
	else cout << st.size();
	return 0;
}
```



---

