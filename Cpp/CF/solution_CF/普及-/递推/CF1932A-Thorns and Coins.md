# Thorns and Coins

## 题目描述

你发现了一个世界。这是一个有 $n$ 个连续单元格的路径，每个单元格可以是空的、含有荆棘或者硬币。在一次移动中，你可以沿着路径向右移动一格或两格，前提是目标单元格不含有荆棘（并且属于路径）。如果你移动到的单元格正好含有硬币的单元格，你就会捡起它。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/bbfdc346db7373b864d2642fd35cef4a577781a2.png)
 
上图中，绿色箭头表示合法移动，红色箭头表示非法移动。你想要在这个发现的世界中收集尽可能多的硬币。你从路径的最左边单元格开始，找出你可以在这个世界中收集的最大硬币数量。


第二个示例的图片如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/e0c47ff41c71ce332d7b876f950ed50eee6c4f4d.png)

第三个示例的图片如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/880dc20f87f4adb0891a434fca6a4717f38a2a7e.png)

## 样例 #1

### 输入

```
3
10
.@@*@.**@@
5
.@@@@
15
.@@..@***..@@@*```

### 输出

```
3
4
3```

# 题解

## 作者：Hutao__ (赞：0)

~~一道模拟水题~~

## 思路

直接 $O(nt)$ 模拟即可，当然，我们需要注意一些细节。

每一个能捡的金币都要捡，遇到连续两个刺就退出循环，因为你无论如何的跳不过这两个刺。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        int n,ans=0;
        string s;
        cin>>n>>s;
        int f=0;
        for(int i=0;i<n;i++){
            if(s[i]=='@')ans++,f=0;//如果是金币就捡，并把刺数清空
            else if(s[i]=='*')f++;//如果是刺就把刺数加一
            else f=0;//如果是空地就把刺数清空
            if(f==2)break;//如果有连续两个刺就退出
        }
        cout<<ans<<'\n';
    }
    return 0;//完美收工~
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1932A)
## 做法
可以用动态规划的做法，$b_i$ 表示第 $i$ 个位置能否走到，$dp_i$ 表示到第 $i$ 位所获得的最多金币数。起初，$b_1$ 为真，答案就是在 $dp_i$ 中取最大值。当第 $b_i$ 为真时：
* 当 $a_i$ 为金币时，$dp_i$ 加 $1$。
* 当 $a_{i + 1}$ 不是荆棘时，将 $b_{i + 1}$ 设为真，$dp_{i + 1}$ 与 $dp_i$ 取最大值。
* 当 $a_{i + 2}$ 不是荆棘时，将 $b_{i + 2}$ 设为真，$dp_{i + 2}$ 与 $dp_i$ 取最大值。 
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I t,n,dp[60],ans;
char a[60];
bool b[60];
I main(){
	scanf("%d",&t);
	for(;t--;){
		scanf("%d%s",&n,a + 1);
		memset(dp,0,sizeof(dp));
		memset(b,false,sizeof(b));
		ans = 0;
		b[1] = true;
		dp[1] = (a[1] == '@');
		for(I i = 1;i <= n;i++){
			if(b[i]){
			    if(a[i] == '@') dp[i]++;
				if(a[i + 1] != '*'){
					b[i + 1] = true;
					dp[i + 1] = max(dp[i + 1],dp[i]);
				}
				if(a[i + 2] != '*'){
					b[i + 2] = true;
					dp[i + 2] = max(dp[i + 2],dp[i]); 
				}
			}
			ans = max(ans,dp[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Elhaithan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1932A)
### 思路
由于题目数据范围很小，所以直接模拟即可。

遍历字符串，若当前字符为 `*` 判断其下一位字符；为 `*` 则退出循环，否则遍历完整个字符串。在遍历的同时记录 `@` 的个数。
### code
```cpp
#include <cstdio>
namespace sol{
	int T, n, cnt;
	char c[60];
	void solve() {
		scanf("%d", &T);
		while(T --) {
			cnt = 0;
			scanf("%d %s", &n, &c);
			for(int i = 0; i < n; i ++)
				if(c[i] == '@') cnt ++;
				else if(c[i] == '*')
					if(c[i + 1] == '*') break;
			printf("%d\n", cnt);
		}
	}
}
int main() {
	sol::solve();
	return 0;
}
```

---

## 作者：GreenMelon (赞：0)

## 形式化题意

$t$ 组数据。给定字符串 $s$，输出出现连续 2 个及以上的 `*` 的位置前（若没有连续 2 个及以上的 `*` 则为整个字符串中）出现 `@` 的数量。

## 讲解

入门，适合巩固 $\texttt{string}$ 的用法。

首先，定义一个变量 $stab$，$stab$ 是来记录有多少个连续的刺的。然后一个一个遍历，如果 $stab=2$，则退出循环，输出获得了多少个金币，遍历字符串到头了也同理，该字符为 `*`，则 $stab$ 加上 $1$，否则清除 $stap$ 的量。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		string s;
		cin>>n>>s;
		int stab=0;
		int score=0;// 出现@的次数
		for(int i=0;i<n;i++){
			if(stab==2) break;
			if(s[i]!='*') stab=0;
			if(s[i]=='@') score++;
			if(s[i]=='*') stab++;
		}
		cout<<score<<endl;
	}
	return 0;
} 
```

---

## 作者：LG086 (赞：0)

### 分析

多组数据，每组数据输入一个 $n$，然后输入一个长为 $n$ 的字符串 $s$。  
字符串 $s$ 中，`*` 处不可走动而 `@` 和 `.` 处可以走动。一次可以走 $1$ 格或 $2$ 格。

所以当遇上连续的两个及以上的 `*` 时，就无法再走了。  
只需要遍历一遍 $s$。若 $s_i$ 是 `@`，$cnt$ 增加一；若 $s_i$ 和 $s_{i+1}$ 都是 `*` 则停止。



------------
### 代码

```cpp
#include<iostream>
int T,n,cnt;std::string s;
int main(){
    std::cin>>T;while(T--){
        std::cin>>n>>s,cnt=0;
        for(int i(0);i<s.size();i++)
            if(s[i]=='*'&&s[i+1]=='*')break;
            else if(s[i]=='@')cnt++;
        std::cout<<cnt<<"\n";
    }
}
```

---

## 作者：GoodLuckCat (赞：0)

## CF1932A 题解

我们可以大胆地假设这条路上有连着两格的含有荆棘的单元格（如下图）。

```
.@*.**@.@
123456789
```

即使在 $4$ 的位置开始移动，到 $5$ 或 $6$，这两种情况也都不合法。所以路径上有连着两格的含有荆棘的单元格，一定跨不过去这个地方，也就是只能捡起之前的硬币。但是只有一个的情况是可以解决的。所以结论就出来了。把能走的格子走一遍，统计硬币数量就可以 AC 了，但是注意多组数据。代码如下：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,f=0;
        string s;
        cin>>n>>s;
        for(int i=1;i<n;i++)
        {
            if(s[i-1]==s[i]&&s[i]=='*')i=n;
            if(s[i]=='@')f++;
        }
        cout<<f<<endl;
    }
}
```

The end.

---

