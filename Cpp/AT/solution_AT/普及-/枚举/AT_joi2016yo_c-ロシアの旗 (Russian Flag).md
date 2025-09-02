# ロシアの旗 (Russian Flag)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2016yo/tasks/joi2016yo_c

K 理事長はロシアで開催される IOI 2016 に合わせて旗を作ることにした．K 理事長はまず倉庫から古い旗を取り出してきた．この旗は $ N $ 行 $ M $ 列のマス目に分けられていて，それぞれのマスには白・青・赤のいずれかの色が塗られている．

K 理事長はこの旗のいくつかのマスを塗り替えてロシアの旗にしようとしている．ただし，この問題でいうロシアの旗とは以下のようなものである．

- 上から何行か（$ 1 $ 行以上）のマスが全て白で塗られている．
- 続く何行か（$ 1 $ 行以上）のマスが全て青で塗られている．
- それ以外の行（$ 1 $ 行以上）のマスが全て赤で塗られている．

K 理事長が古い旗をロシアの旗にするために塗り替える必要のあるマスの個数の最小値を求めよ．

- - - - - -

## 说明/提示

### Sample Explanation 1

入出力例 $ 1 $ において，古い旗には下図のように色が塗られている． !\[2016-yo-t3-fig01.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig01.png) 下図において，`X` の書かれた $ 11 $ 個のマスを塗り替える． !\[2016-yo-t3-fig02.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig02.png) これにより下図のようなロシアの旗にすることができる． !\[2016-yo-t3-fig03.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig03.png) $ 11 $ 個未満のマスを塗り替えることではロシアの旗にすることはできないため，$ 11 $ を出力する． - - - - - -

### Sample Explanation 2

入出力例 $ 2 $ においては，古い旗には下図のように色が塗られている． !\[2016-yo-t3-fig04.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig04.png)

## 样例 #1

### 输入

```
4 5
WRWRW
BWRWB
WRWRW
RWBWR```

### 输出

```
11```

## 样例 #2

### 输入

```
6 14
WWWWWWWWWWWWWW
WBBBWWRRWWBBBW
WWBWWRRRRWWBWW
BWBWWRRRRWWBWW
WBBWWWRRWWBBBW
WWWWWWWWWWWWWW```

### 输出

```
44```

# 题解

## 作者：huyangmu (赞：4)

这道题数据很小，直接暴力就可以了。

先开三个计数数组表示每一行三种颜色的数量。

然后两重循环枚举 $x$ 和 $y$，第三重循环计算要粉刷的格子数量，求最小值。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=55; 
int n,m,cnt1[NR],cnt2[NR],cnt3[NR],ans=0x3f3f3f3f;
char c[NR][NR];
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			cin>>c[i][j];
			if (c[i][j]=='W') ++cnt1[i];
			else if (c[i][j]=='B') ++cnt2[i];
			else ++cnt3[i];
		}
	}
	for (int x=1;x<n-1;++x){
		for (int y=x+1;y<n;++y){
			int tmp=0,sum=0;
			for (int i=1;i<=x;++i) tmp+=cnt1[i];
			sum+=x*m-tmp;
			tmp=0;
			for (int i=x+1;i<=y;++i) tmp+=cnt2[i];
			sum+=(y-x)*m-tmp;
			tmp=0;
			for (int i=y+1;i<=n;++i) tmp+=cnt3[i];
			sum+=(n-y)*m-tmp;
			ans=min(ans,sum);
		}
	}
	cout<<ans<<'\n';
	return 0;
}


---

## 作者：Sammy_prime (赞：3)

[AT_joi2016yo_c](https://www.luogu.com.cn/problem/AT_joi2016yo_c)

# 思路

本题三重循环纯枚举即可，只需枚举白色与蓝色，蓝色与红色的分界，不是要求的颜色就计数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,minn=1<<30; char a[55][55];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int i=1;i<=n-2;i++)
	    for(int j=i+1;j<=n-1;j++){
	    	int cnt=0;
	    	for(int k=1;k<=i;k++)
	            for(int l=1;l<=m;l++) if(a[k][l]!='W') cnt++;
	        for(int k=i+1;k<=j;k++)
	            for(int l=1;l<=m;l++) if(a[k][l]!='B') cnt++;
	        for(int k=j+1;k<=n;k++)
	            for(int l=1;l<=m;l++) if(a[k][l]!='R') cnt++;
	        minn=min(minn,cnt);
		}
	printf("%d\n",minn);
	return 0;
}
```


---

## 作者：xhhhh36 (赞：3)

本题并不难，直接按照题意暴力枚举 $x$ 和 $y$ 即可，用三个桶分别存储每一行三种颜色的数量。
# Code
```cpp
#include <bits/stdc++.h>

using namespace std;
int n,m,r[55],w[55],b[55];
char a[55][55];
signed main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if (a[i][j]=='W') w[i]++;
			else if (a[i][j]=='R') r[i]++;
			else b[i]++;
		}
	}
	int ans,mn=INT_MAX;
	for (int x=1;x<n-1;x++)
	{
		for (int y=x+1;y<n;y++)
		{
			ans=0;
			for (int i=1;i<=x;i++)
			{
				ans+=m-w[i];
			}
			for (int i=x+1;i<=y;i++)
			{
				ans+=m-b[i];
			}
			for (int i=y+1;i<=n;i++)
			{
				ans+=m-r[i];
			}
			mn=min(mn,ans);
		}
	}
	cout<<mn<<endl;
	return 0;
}
```
### [AC 记录](https://atcoder.jp/contests/joi2016yo/submissions/45437740)

---

## 作者：hexuchen (赞：2)

无人区写题解的第二天

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2016yo_c)

[更好的阅读体验？](https://www.luogu.com.cn/blog/niganma114514/solution-at-joi2016yo-c)


## 题目意思

现在有一面旗帜，它由红、蓝、白三种颜色组成。请问如果想将这张旗帜变为俄罗斯国旗（即从 $1$ 到 $x$ 是白色，从 $x + 1$ 到 $y$ 是蓝色，从 $y + 1$ 到 $n$ 是红色），最少需要粉刷几个格子？


## 思路分析

一道简单的桶的题目。

首先先输入，边输入边判断这个格子是什么颜色，相应的桶加上一。最后枚举一遍，求出这一种情况下要修改几次，与最小值进行比较。如果小于则将最小值设为要修改的次数，最后输出最小值即可。

**注意：输出答案末尾要加换行！**

## AC 代码 
 
```cpp
#include <bits/stdc++.h>
#define MAXN 1000001
using namespace std;
int wt[MAXN],bt[MAXN],rt[MAXN],n,m,minn=MAXN,sum=0; //定义桶
char s[1001][1001];
int main(){
	cin>>n>>m; //输入
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
			switch(s[i][j]){ //判断这个格子是什么颜色，哪个桶要加一
				case 'W':wt[i]++;break;
				case 'B':bt[i]++;break;
				case 'R':rt[i]++;break;
			}
		}
	}
	for(int i=1;i<(n-1);i++){ //枚举一遍
		for(int j=i+1;j<n;j++){
			sum=0; //计数器为0
			for(int i1=1;i1<=i;i1++){ //白色
				sum+=(m-wt[i1]);
			}
			for(int i1=i+1;i1<=j;i1++){ //蓝色
				sum+=(m-bt[i1]);
			}
			for(int i1=j+1;i1<=n;i1++){ //红色
				sum+=(m-rt[i1]);
			}
			minn=min(sum,minn); //如果小于最小值则将最小值设为计数器
		}
	}
	cout<<minn<<endl; //输出最小值，记得要加换行
	return 0;
}
```

管理大大求过~

求点赞~

---

## 作者：Lavande (赞：2)

# 题目

[LINK！](https://www.luogu.com.cn/problem/AT_joi2016yo_c)

# 思路

这道题并不难，可以直接暴力枚举 $x$ 和 $y$，用三个桶储存就行了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;

int white[N], blue[N], red[N];//白蓝红，三个颜色的桶 
int n, k, maxn = INT_MAX;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
    char c;
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= k; j ++){
			cin >> c;
			if(c == 'W') white[i] ++;
			if(c == 'B') blue[i] ++;
			if(c == 'R') red[i] ++;
		}
	}
	for(int x = 1; x < n - 1; x ++){
		for(int y = x + 1; y < n; y ++){
			int ans = 0;
			for(int i = 1; i <= x; i ++){
				ans += (k - white[i]);
			}
			for(int i = x + 1; i <= y; i ++){
				ans += (k - blue[i]);
			}
			for(int i = y + 1; i <= n; i ++){
				ans += (k - red[i]);
			}
			maxn = min(ans, maxn);
		}
	}
	cout << maxn;
	return 0;
}
```


---

## 作者：gotocspandbetter (赞：1)

直接使用双重枚举枚举出所有可能的 $x$ 和 $y$。

而后将原本的涂色方式和每一种 $x$ 和 $y$ 的情况进行比对。

找出改变的格子数，取最小值即可。

时间复杂度 $O(n^3m)$。

## AC code:
```cpp
#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<queue>
#include<stack>
#include<deque>
#include<map>
using namespace std;
int main(){
	int n,m,minn=3000;
	cin>>n>>m;
	char arr[55][55];
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			cin>>arr[i][j];
		}
	}
	for (int i=1;i<=n-2;i++){
		for (int j=i+1;j<=n-1;j++){
			int sum=0;
			for (int k=1;k<=i;k++){
				for (int l=1;l<=m;l++){
					sum+=(arr[k][l]=='W'?0:1);
				}
			}
			for (int k=i+1;k<=j;k++){
				for (int l=1;l<=m;l++){
					sum+=(arr[k][l]=='B'?0:1);
				}
			}
			for (int k=j+1;k<=n;k++){
				for (int l=1;l<=m;l++){
					sum+=(arr[k][l]=='R'?0:1);
				}
			}
			minn=min(minn,sum);
		}
	}
	cout<<minn;
	return 0;  
}
 
```


---

## 作者：OIer6666 (赞：1)

本蒟蒻的第 $6$ 篇题解，希望过审核！

这一题很简单，直接枚举 $x$ 和 $y$，求最小值，输出并换行。

# AC CODE:
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#define ll long long
#define N 55
#define min(a,b) (a<b?a:b)
using namespace std;
char temp;
int white[N],blue[N],red[N];
int n,m,ans=0x3f3f3f3f;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>temp;
			if(temp=='W')
				white[i]++;
			if(temp=='B')
				blue[i]++;
			if(temp=='R')
				red[i]++;
		}
	for(int x=1;x<n-1;x++){
		for(int y=x+1;y<n;y++){
			int sum=0;
			for(int i=1;i<=x;i++){
				sum=sum+(m-white[i]);
			}
			for(int i=x+1;i<=y;i++){
				sum=sum+(m-blue[i]);
			}
			for(int i=y+1;i<=n;i++){
				sum=sum+(m-red[i]);
			}
			ans=min(sum,ans);
		}
	}
	cout<<ans<<endl;//一定要换行！
	return 0;
}
```

---

## 作者：Flying_Eagle (赞：0)

### 题目思路
由于数据比较小，直接暴力枚举。为了方便计算，用桶把数据存起来。
接着两重循环枚举 $x$ 和 $y$，然后将每行的正确颜色删除。最后求最小值即可。

### 题目代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
int n, m;
int w[55], r[55], b[55];
int minn = 2147483647;

int main() {
//	freopen("xxxx.in", "r", stdin);
//	freopen("xxxx.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char x;
			cin >> x;
			if (x == 'W')
				w[i]++;
			if (x == 'B')
				b[i]++;
			if (x == 'R')
				r[i]++;
		}
	}
	for (int x = 1; x <= n - 2; x++) {
		for (int y = x + 1; y <= n - 1; y++) {
			for (int k = y + 1; k <= n; k++) {
				int ans = 0;
				for (int i = 1; i <= x; i++) {
					ans += m - w[i];
				}
				for (int i = x + 1; i <= y; i++) {
					ans += m - b[i];
				}
				for (int i = y + 1; i <= n; i++) {
					ans += m - r[i];
				}
				minn = min(ans, minn);
			}
		}
	}
	cout << minn << endl;
	return 0;
}

```


---

## 作者：LYJ_B_O_Creation (赞：0)

题目思路：
-
因为时间放的很宽，且数据范围很小，可以直接暴力枚举 $x,y$。每一次枚举完后计算需要重新粉刷的格子，维护最小值即为答案。

题目代码：
-
```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m;
int x , y;
int i , j;
int sum , ans = 100000;
char s[61][61];
int main()
{
	cin >> n >> m;
	for(i = 1;i <= n;i++) cin >> s[i] + 1;
	for(x = 1;x < n - 1;x++)
	{
		for(y = 1;y < n;y++)
		{
			sum = 0;
			for(i = 1;i <= n;i++)
			{
				for(int j = 1;j <= m;j++)
				{
					if(i <= x && s[i][j] != 'W') sum++;
					if(i > x && i <= y && s[i][j] != 'B') sum++;
					if(i > y && s[i][j] != 'R') sum++; 
				}
			}
			ans = min(ans , sum);
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：HatsuneMiku39 (赞：0)

这题的 $n$ 和 $m$ 都很小（不超过 $50$），所以我们可以直接枚举有多少行白格子，有多少行蓝格子，然后再看要修改多少个字母。

同时，为了防止代码过于复杂，我们可以使用桶数组记录每行三个字母出现了多少次。

话不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int w[55],b[55],r[55];
int main(){
    int n,m,ans = 0x7fffffff;
    cin>>n>>m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            char x;
            cin>>x;
            if(x == 'W') w[i]++;
            if(x == 'B') b[i]++;
            if(x == 'R') r[i]++;
        }
    }
    for(int i = 1;i <= n - 2;i++){
        for(int j = i + 1;j <= n - 1;j++){
            for(int k = j + 1;k <= n;k++){
                int sum = 0;
                for(int x = 1;x <= i;x++) sum += m - w[x];
                for(int x = i + 1;x <= j;x++) sum += m - b[x];
                for(int x = j + 1;x <= n;x++) sum += m - r[x];
                ans = min(ans,sum);
            }
        }
    }
    cout<<ans;
    return 0;
}
```
时间复杂度 $O(n^4)$。

---

