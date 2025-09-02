# [USACO25FEB] Reflection B

## 题目描述

Farmer John 有一块正方形画布，由一个 $N$ 行 $N$ 列的方阵表示（$2 \leq N \leq 2000$，$N$ 为偶数）。他按照以下步骤来绘制画布：

首先，他将画布分成四个等大的象限，由通过画布中心的水平和垂直直线分隔。
其次，他在画布的右上象限中绘制了一幅美丽的画作。右上象限的每个方格或者被涂色（以 `#` 表示），或者未被涂色（以 `.` 表示）。
最后，由于他对自己的画作感到非常自豪，他将其沿此前提到的水平和垂直直线翻转到画布的其他象限中。
例如，假设 $N=8$，且 FJ 在步骤 2 中于右上象限绘制了以下画作：

```plain
.#..
.#..
.##.
....
```

在步骤 3 中沿水平和垂直直线翻转过后，画布将如下所示：

```plain
..#..#..
..#..#..
.##..##.
........
........
.##..##.
..#..#..
..#..#..
```

然而，当 FJ 熟睡时，Bessie 闯入了他的牛棚，偷走了他珍贵的画布。她彻底破坏了画布——移除了某些涂色的单元格，同时添加了某些涂色的单元格！在 FJ 醒来之前，她将画布归还给了 FJ。

FJ 想要修改他的画布，使其再次满足翻转条件：即，它是将右上象限翻转到其他各象限的结果。由于他只有有限的资源，他希望以尽可能少的操作来实现这一点，其中单次操作包括为一个方格涂色或移除一个方格的涂色。

给定 Bessie 破坏后的画布，以及一系列 $U$（$0\le U \leq 10^5$）次对画布的更新，每次更新切换单个方格的状态，若它是 '#' 则切换为 '.'，反之亦然。在所有更新之前，以及在每次更新之后，输出 FJ 为满足翻转条件所需要执行的最小操作数量 $x$。

## 说明/提示

样例 1 解释：

以下画布满足翻转条件，并且可由原画布经过 4 次操作得到：

```plain
....
####
####
....
```

使用少于 4 次操作使原画布满足翻转条件是不可能的。

在更新 $(1, 3)$ 之后，画布看起来是这样的：

```plain
....
##.#
####
..##
```

现在需要 3 次操作使画布满足翻转条件。

在更新 $(2, 3)$ 之后，画布看起来是这样的：

```plain
....
####
####
..##
```

现在需要 2 次操作使画布满足翻转条件。

- 测试点 $2\sim 3$：$N \le 4$。
- 测试点 $4\sim 6$：$U \le 10$。
- 测试点 $7\sim 16$：没有额外限制。

## 样例 #1

### 输入

```
4 5
..#.
##.#
####
..##
1 3
2 3
4 3
4 4
4 4```

### 输出

```
4
3
2
1
0
1```

# 题解

## 作者：no_response (赞：12)

## [题目传送门](https://www.luogu.com.cn/problem/P11836)
一道简单的二维数组加调整题目。  
## 解题思路
先将面布输入，判断是否涂色，进行第一次计算。  

对于 $U$ 次修改，说明如下：  
是将画布变成一种在水平、垂直中都对称的状态，并确定修改后变成对称所需的最小的操作数。  

对于每次修改，仅需修改一个点，变化也只和这一个点有关，只计算这一个点的变化即可。  
具体来说，原答案先减去这个点没修改时的值，在加上这个点修改后的值，就是当前的答案。

再将这些答案一并输出，即可 AC。  
## AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
bool maP[2010][2010];
int ans[100010];
int main() {
	int n, u;
	cin >> n >> u;
	int sum = 0;
	int cnt1 = 0, cnt2 = 0;
	for (int i = 1; i <= n; i++) { //输入面布
		for (int j = 1; j <= n; j++) {
			char c;
			cin >> c;
			if (c == '#') { //判断是否被涂色
				maP[i][j] = 1;
			} else {
				maP[i][j] = 0;
			}
		}
	}
	for (int i = 1; i <= n / 2; i++) { //根据输入的面布进行计算
		for (int j = 1; j <= n / 2; j++) {
			cnt1 = 0;
			if (maP[n - i + 1][n - j + 1] != maP[i][j]) {
				cnt1++;
			}
			if (maP[n - i + 1][j] != maP[i][j]) {
				cnt1++;
			}
			if (maP[i][n - j + 1] != maP[i][j]) {
				cnt1++;
			}
			sum += min(cnt1, 4 - cnt1);
		}
	}
	cout << sum << endl;
	int r, c;
	int out = 0;
	for (int i = 1; i <= u; i++) { //通过更新次数进行翻转并记录最小操作量
		cnt1 = cnt2 = 0;
		cin >> r >> c;
		if (maP[r][c] != maP[n - r + 1][n - c + 1]) {
			cnt1++;
		}
		if (maP[r][c] != maP[n - r + 1][c]) {
			cnt1++;
		}
		if (maP[r][c] != maP[r][n - c + 1]) {
			cnt1++;
		}
		cnt1 = min(cnt1, 4 - cnt1);
		if (maP[r][c] == 0) {
			maP[r][c] = 1;
		} else {
			maP[r][c] = 0;
		}
		if (maP[r][c] != maP[n - r + 1][n - c + 1]) {
			cnt2++;
		}
		if (maP[r][c] != maP[n - r + 1][c]) {
			cnt2++;
		}
		if (maP[r][c] != maP[r][n - c + 1]) {
			cnt2++;
		}
		cnt2 = min(cnt2, 4 - cnt2);
		sum += cnt2 - cnt1;
		ans[out] = sum;
		out++;
	}
	for (int i = 0; i < out; i++) {
		cout << ans[i] << endl; //输出答案
	}
}
```
为保持洛谷的良好学习习惯，请勿抄袭。  
**千万别抄袭哦。**  
管理大大辛苦了，各位大佬给蒟蒻点个赞呗。

---

## 作者：cff_0102 (赞：7)

不是很大的模拟，代码也没必要写多长。

用一个数组 `a` 记录折叠后这个位置上有几个是被涂色的，那么答案就是所有位置上的 `min(a[x][y],4-a[x][y])` 之和。每次只修改一个点，那么就跟着修改答案并输出即可。

代码写的很清晰。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2025;
int a[N][N];
bool s[N][N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,u;cin>>n>>u;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c;cin>>c;
			int x=(i>n/2?n+1-i:i),y=(j>n/2?n+1-j:j);
			a[x][y]+=(c=='#');
			s[i][j]=(c=='#');
		}
	}
	int ans=0;
	for(int i=1;i<=n/2;i++){
		for(int j=1;j<=n/2;j++){
			ans+=min(a[i][j],4-a[i][j]); 
		}
	}
	cout<<ans<<"\n";
	while(u--){
		int i,j;cin>>i>>j;
		int x=(i>n/2?n+1-i:i),y=(j>n/2?n+1-j:j);
		ans-=min(a[x][y],4-a[x][y]);
		a[x][y]-=s[i][j];
		s[i][j]=1-s[i][j];
		a[x][y]+=s[i][j];
		ans+=min(a[x][y],4-a[x][y]);
		cout<<ans<<"\n"; 
	}
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：3)

发现画布只需要在 $(i,j),(n-i+1,j),(i,n-j+1),(n-i+1,n-j+1)$ 相等。

于是用一个二维数组直接记录将这四个数修改成 `#` 和 `.` 的需要修改多少次。

每次对画布的修改都是单点修改，于是直接记录可行。

~~话说这题我想了 1 小时才想出思路~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[2010][2010];
int ans;
int main() {
	cin>>n>>m;
	int k=n>>1;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		char ch;
		cin>>ch;
		a[i][j]=(ch=='#');
	}
	for(int i=1;i<=k;i++) for(int j=1;j<=k;j++){
		int t=a[i][j]+a[n-i+1][j]+a[i][n-j+1]+a[n-i+1][n-j+1];
		ans+=min(t,4-t);
	}
	cout<<ans<<"\n";
	while(m--){
		int x,y;
		cin>>x>>y;
		int t=a[x][y]+a[n-x+1][y]+a[x][n-y+1]+a[n-x+1][n-y+1];
		ans-=min(t,4-t);
		a[x][y]^=1;
		t=a[x][y]+a[n-x+1][y]+a[x][n-y+1]+a[n-x+1][n-y+1];
		ans+=min(t,4-t);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：mc_xiexie (赞：3)

### 题意

给你个 $N \times N$ 的序列，问你要改几次才能[中心对称](https://baike.baidu.com/item/%E4%B8%AD%E5%BF%83%E5%AF%B9%E7%A7%B0/5695518)（但是这里是旋转九十度）。

### 做法

我们可以将它从对称点做坐标系将它分成四块，例如这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/hu3979o6.png)

想要它中心对称，我们要将一个点在其他区域的对应点改变。在[第二象限](https://baike.baidu.com/item/%E7%AC%AC%E4%BA%8C%E8%B1%A1%E9%99%90)的点 $(i,j)$ 在其他区域的点的对应点分别为 $(n-i+1)(n-j+1)$、$(n-i+1)(n-j+1)$、$(n-i+1)(n-j+1)$。

这时我们只要判断改不改枚举的那个点（那个改动的次数少改哪个），记录次数即可。

同时我们发现改一个点，只会影响到它的对应点，这样就无需每次修改都遍历一遍图了。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
bool mp[2005][2005];
int main(){
    int u,x,y,n,sum=0,cut1=0,cut2=0;
    char c;
    cin>>n>>u;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>c;
            mp[i][j]=(c=='#');
        }
    }
    for(int i=1;i<=n/2;i++){
        for(int j=1;j<=n/2;j++){
            cut1=0;
            if(mp[n-i+1][n-j+1]!=mp[i][j]){
                cut1++;
            }
            if(mp[n-i+1][j]!=mp[i][j]){
                cut1++;
            }
            if(mp[i][n-j+1]!=mp[i][j]){
                cut1++;
            }
            sum+=min(cut1,4-cut1);
        }
    }
    cout<<sum<<"\n";
    while(u--){
        cut1=cut2=0;
        cin>>x>>y;
        if(mp[x][y]!=mp[n-x+1][n-y+1]){
            cut1++;
        }
        if(mp[x][y]!=mp[n-x+1][y]){
            cut1++;
        }
        if(mp[x][y]!=mp[x][n-y+1]){
            cut1++;
        }
        cut1=min(cut1,4-cut1);
        mp[x][y]=!mp[x][y];
        if(mp[x][y]!=mp[n-x+1][n-y+1]){
            cut2++;
        }
        if(mp[x][y]!=mp[n-x+1][y]){
            cut2++;
        }
        if(mp[x][y]!=mp[x][n-y+1]){
            cut2++;
        }
        cut2=min(cut2,4-cut2);
        sum+=cut2-cut1;
        cout<<sum<<"\n";
    }
}
```

---

## 作者：封禁用户 (赞：2)

### 做法
遍历右上象限的每个单元格，找到其对称的四个单元格。

统计每组中 `#` 的数量，计算每组的最小操作数，并累加到总的最小操作数中。

对于每次更新，找到被更新的单元格所属的组。

更新该组的状态，并重新计算该组的最小操作数。

更新总的最小操作数。

在初始状态和每次更新后，输出当前的最小操作数。

### 代码实现  

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, U;
    cin >> N >> U;
    vector<vector<char>> cs(N, vector<char>(N));
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) 
            cin >> cs[i][j];
    int x = 0;
    for (int i = 0; i < N / 2; ++i) {
        for (int j = N / 2; j < N; ++j) {
            char c1 = cs[i][j],c2 = cs[i][N - 1 - j],c3 = cs[N - 1 - i][j],c4 = cs[N - 1 - i][N - 1 - j];
            int cnt = 0;
            if (c1 == '#') cnt++;
            if (c2 == '#') cnt++;
            if (c3 == '#') cnt++;
            if (c4 == '#') cnt++;
            x += min(cnt, 4 - cnt);
        }
    }
    cout << x << endl;
    for (int u = 0; u < U; ++u) {
        int r, c;
        cin >> r >> c;
        r--; c--; 
        int i = min(r, N - 1 - r);
        int j = max(c, N - 1 - c);
        char& c1 = cs[i][j];
		char& c2 = cs[i][N - 1 - j];
        char& c3 = cs[N - 1 - i][j];
        char& c4 = cs[N - 1 - i][N - 1 - j];
        int cnt_before = 0;
        if (c1 == '#') cnt_before++;
        if (c2 == '#') cnt_before++;
        if (c3 == '#') cnt_before++;
        if (c4 == '#') cnt_before++;
        if (cs[r][c] == '#') cs[r][c] = '.';
        else cs[r][c] = '#';
        int cnt_after = 0;
        if (c1 == '#') cnt_after++;
        if (c2 == '#') cnt_after++;
        if (c3 == '#') cnt_after++;
        if (c4 == '#') cnt_after++;
        x -= min(cnt_before, 4 - cnt_before);
        x += min(cnt_after, 4 - cnt_after);
        cout << x << endl;
    }
    return 0;
}
```

---

## 作者：zsjaaaxy (赞：2)

算是模拟？

最初傻了几十分钟，后来发现把每个左上角的点匹配另外几个与之对称的点即可。

我们可以在询问之前先做预处理，求出每个点的最小切换次数。对于每次询问，对单个点进行再次处理即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,ans=0,x,y;
char c[2001][2001];
int main()
{
	cin>>n>>u;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>c[i][j];
		}	
	}	
	for(int i=1;i<=n/2;i++)
	{
		for(int j=1;j<=n/2;j++)
		{
			int k1=0,k2=0,ii=n+1-i,jj=n+1-j;
			if(c[i][j]=='.')
			{
				k1++;
			}
			else
			{
				k2++;
			}
			if(c[i][jj]=='.')
			{
				k1++;
			}
			else
			{
				k2++;
			}
			if(c[ii][j]=='.')
			{
				k1++;
			}
			else
			{
				k2++;
			}
			if(c[ii][jj]=='.')
			{
				k1++;
			}
			else
			{
				k2++;
			}
			ans+=4-max(k1,k2);
		}
	}
	cout<<ans<<endl;
	while(u--)
	{
		cin>>x>>y;
		int i=x,j=y;
		if(i>n/2)
		{
			i=n-i+1;
		}
		if(j>n/2)
		{
			j=n-j+1;
		}
		int k1=0,k2=0,ii=n+1-i,jj=n+1-j;
		if(c[i][j]=='.')
		{
			k1++;
		}
		else
		{
			k2++;
		}
		if(c[i][jj]=='.')
		{
			k1++;
		}
		else
		{
			k2++;
		}
		if(c[ii][j]=='.')
		{
			k1++;
		}
		else
		{
			k2++;
		}
		if(c[ii][jj]=='.')
		{
			k1++;
		}
		else
		{
			k2++;
		}
		ans-=4-max(k1,k2);
		if(c[x][y]=='.')
		{
			c[x][y]='#';
			k2++;
			k1--;
		}
		else
		{
			c[x][y]='.';
			k1++;
			k2--;
		}
		ans+=4-max(k1,k2);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Helenty (赞：2)

### 解题思路

简单二维数组题，有点大模拟的感觉。

就是将正方形画布恢复为一种状态，即在水平和垂直中线上都是对称的。确定每次更新后恢复对称所需的最小操作数。

### 完整代码


```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

char input[MAXN][MAXN];
int grid[MAXN][MAXN], contrib[MAXN/2 + 2][MAXN/2 + 2], N, U;

int main()
{
	scanf("%d %d", &N, &U);
    for (int i = 1; i <= N; i++)
	{
        scanf("%s", input[i] + 1);
        for (int j = 1; j <= N; j++)
		{
            grid[i][j] = (input[i][j] == '#') ? 1 : 0;
        }
    }
    int halfN = N / 2, ans = 0;
    for (int i = 1; i <= halfN; i++)
	{
        for (int j = halfN + 1; j <= N; j++)
		{
            int a = grid[i][j];
            int b = grid[i][N + 1 - j];
            int c = grid[N + 1 - i][N + 1 - j];
            int d = grid[N + 1 - i][j];
            int cnt = a + b + c + d;
            int j_contrib = j - halfN;
            contrib[i][j_contrib] = min(cnt, 4 - cnt);
            ans += contrib[i][j_contrib];
        }
    }
    printf("%d\n", ans);
    while (U--)
	{
        int r, c_val;
        scanf("%d %d", &r, &c_val);
        grid[r][c_val] ^= 1;
        int i_rep = (r <= halfN) ? r : (N + 1 - r);
        int j_rep = (c_val > halfN) ? c_val : (N + 1 - c_val);
        int a = grid[i_rep][j_rep];
        int b = grid[i_rep][N + 1 - j_rep];
        int c = grid[N + 1 - i_rep][N + 1 - j_rep];
        int d = grid[N + 1 - i_rep][j_rep];
        int cnt = a + b + c + d;
        int new_contrib = min(cnt, 4 - cnt);
        int j_contrib = j_rep - halfN;
        ans -= contrib[i_rep][j_contrib];
        contrib[i_rep][j_contrib] = new_contrib;
        ans += new_contrib;
        printf("%d\n", ans);
    }
    return 0;
}

```

---

## 作者：qhr2023 (赞：2)

## solution

简单模拟题。

对于一个左上的点 $(i, j)$，右上与它对应的点就是 $(i, n+1-j)$，左下的对应点是 $(n+1-i, j)$，右下的对应点是 $(n+1-i, n+1-j)$。枚举左上部分的点，判断这个点和它的对应点共四个点全改成 ```#``` 代价小还是改成 ```.``` 代价小，再求和就是未修改时的答案。

对于修改，每次只修改一个点，答案的变化也只和这一个点有关，只计算这一个点的贡献变化即可。具体的话，答案先减去这个点没修改时的代价，在加上这个点修改后的代价即当前的答案。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, u, ans;
char a[2005][2005];
int main () { 
	cin >> n >> u;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
			cin >> a[i][j];
	for (int i=1; i<=n/2; ++i)
		for (int j=1; j<=n/2; ++j) {
			int cnt=(a[i][j]=='.')+(a[i][n+1-j]=='.')+
				(a[n+1-i][j]=='.')+(a[n+1-i][n+1-j]=='.');
			ans+=min(cnt, 4-cnt);
		}
	cout << ans << '\n';
	for (int x, y; u--; ) {
		cin >> x >> y;
		int cnt1=(a[x][y]=='.')+(a[x][n+1-y]=='.')+
				(a[n+1-x][y]=='.')+(a[n+1-x][n+1-y]=='.');
		if (a[x][y]=='.')
			a[x][y]='#';
		else
			a[x][y]='.';
		int cnt2=(a[x][y]=='.')+(a[x][n+1-y]=='.')+
				(a[n+1-x][y]=='.')+(a[n+1-x][n+1-y]=='.');
		ans=ans+min(cnt2, 4-cnt2)-min(cnt1, 4-cnt1);
		cout << ans << '\n';
	}
	return 0;
}

```

---

## 作者：Starry_Sky_135 (赞：1)

# 思路
读完题目就可以判断是模拟题了，关键点在于如何统计最小操作次数。  

我们以左上部分为例，只需要统计将左上角的点和其他三个部分相对应的点改成 ```#``` 还是 ```.``` 代价更小，取更小的那个值。以上就是统计最小操作次数的方法，输入进来的初始数组就按这个方法进行统计。

接下来是进行 $u$ 次修改，如果每次修改完都按上面的方法统计一遍，三重循环，会超时。  
但是仔细思考一下会发现，每次修改都只变动了一个点，那么我们就可以统计这个要修改的点修改前的最小操作次数，和修改后的最小操作次数，两者相减即可得到新的答案。

还有一些小的技巧放在代码里了。


---



# AC 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+8;
int n,u;
int a[N][N];
int main()
{
    cin>>n>>u;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            char x;
            cin>>x;
            if(x=='.') a[i][j]=0;
            else a[i][j]=1;//将输入进来的字符转化成01数组，更方便接下来的统计
        }
    }
    
    int ans=0;
    for(int i=1;i<=n/2;i++)
    {
        for(int j=1;j<=n/2;j++)//左上部分
        {
            int cnt=a[i][j]+a[i][n-j+1]+a[n-i+1][j]+a[n-i+1][n-j+1];//统计该点和与该点相对应的三个点
            cnt=min(cnt,4-cnt);//取更小的修改次数
            ans+=cnt;
        }
    }
    cout<<ans<<endl;
    
    for(int i=1,r,c;i<=u;i++)
    {
        cin>>r>>c;
        int cnt1=a[r][c]+a[r][n-c+1]+a[n-r+1][c]+a[n-r+1][n-c+1];
        cnt1=min(cnt1,4-cnt1);
        a[r][c]=!a[r][c];//直接取反
        int cnt2=a[r][c]+a[r][n-c+1]+a[n-r+1][c]+a[n-r+1][n-c+1];
        cnt2=min(cnt2,4-cnt2);
        ans+=(cnt2-cnt1);//在原来的基础上修改
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：lvweisi (赞：0)

一道非常简单的贪心题

### 思路如下：

作为每一个象限，只需要把这四个象限的点中 `.` 的个数和 `#` 的个数取一个最小值加进答案，而对于修改的点，只需要把答案加上原本的 `.` 和 `#` 的个数个数的最小值和修改后的 `.` 和 `#` 的个数的最小值的差值输出就好了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,mp[1005][1005];
int n;
int main() {
	cin>>n>>q;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			char a;
			cin>>a;
			if(a=='.')mp[i][j]=1;
		}
	}
	int ans=0;
	for(int i=1; i<=n/2; i++) {
		for(int j=1; j<=n/2; j++) {
			int gs=0;
			if(mp[i][j]==1)gs++;
			if(mp[i][n-j+1]==1)gs++;
			if(mp[n-i+1][j]==1)gs++;
			if(mp[n-i+1][n-j+1]==1)gs++;
			ans+=min(gs,4-gs);
		}
	}
	cout<<ans<<'\n';
	for(int Q=1; Q<=q; Q++) {
		int a,b;
		cin>>a>>b;
		int i,j;
		if(a>n/2)i=n+1-a;
		else i=a;
		if(b>n/2)j=n+1-b;
		else j=b;
		int ygs=0;
		if(mp[i][j]==1)ygs++;
		if(mp[i][n-j+1]==1)ygs++;
		if(mp[n-i+1][j]==1)ygs++;
		if(mp[n-i+1][n-j+1]==1)ygs++;
		mp[a][b]=(mp[a][b]+1)%2;
		ygs=min(4-ygs,ygs);
		int gs=0;
		if(mp[i][j]==1)gs++;
		if(mp[i][n-j+1]==1)gs++;
		if(mp[n-i+1][j]==1)gs++;
		if(mp[n-i+1][n-j+1]==1)gs++;
		gs=min(gs,4-gs);
		ans+=gs-ygs;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Manchester_City_FC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11836)

### 题目大意
给你个 $n \times n$ 的矩阵，问你要改几次才能使它是将右上象限翻转到其他各象限的结果。

### 解题思路
一道并不难的模拟题。

首先确定一下四个象限的坐标范围：
+ 右上象限：$(1,1)$ 到 $(\frac{n}{2},n)$。
+ 右下象限：$(\frac{n}{2}+1,1)$ 到 $(n,n)$。
+ 左上象限：$(1,\frac{n}{2}+1)$ 到 $(\frac{n}{2},n)$。
+ 左下象限：$(\frac{n}{2}+1,\frac{n}{2}+1)$ 到 $(n,n)$。

接下来我们要考虑一下在右上象限中的点 $(i,j)$ 会具体翻转到的位置，具体如下：
+ 右上象限 $(i,j)$。
+ 右下象限 $(n-i+1,j)$。
+ 左上象限 $(i,n-j+1)$。
+ 左下象限 $(n-i+1,n-j+1)$。

要求最终画布满足翻转条件，则每组内的 $4$ 个单元格颜色必须全部相同。将每一组内 `#` 的个数记为 $t$，则将该组变为全 `#` 的代价为 $4-t$，变为全 `.` 的代价为 $t$，故该组的最小修改次数为 $\min(t,4-t)$。

我们预处理所有组的状态，并计算全局答案（所有组所需修改次数之和）。每次更新时，由于一个单元格只属于唯一一个组，我们只需重新计算该组的代价，然后更新全局答案即可。

### AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2001;
char a[N][N];
int b[N][N],n,u,ans,t,r,c,x,y;
void work(int x,int y,int n,int &p,int &q){
	if(x<=n/2&&y>n/2) p=x,q=y;
    else if(x<=n/2&&y<=n/2) p=x,q=n-y+1;
    else if(x>n/2&&y>n/2) p=n-x+1,q=y;
	else p=n-x+1,q=n-y+1;
}
signed main(){
    cin>>n>>u;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
    for(int i=1;i<=n/2;i++){
        for(int j=n/2+1;j<=n;j++){
            t=(a[i][j]=='#'?1:0)+(a[i][n-j+1]=='#'?1:0)+(a[n-i+1][j]=='#'?1:0)+(a[n-i+1][n-j+1]=='#'?1:0);
            b[i][j]=t;
            ans+=min(t,4-t);
        }
    }
    cout<<ans<<endl;
    while(u--){
        cin>>r>>c;
        int p,q;
        work(r,c,n,p,q);
        x=min(b[p][q],4-b[p][q]);
        if(a[r][c]=='#'){
            a[r][c]='.';
            b[p][q]--;
        }
		else{
            a[r][c]='#';
            b[p][q]++;
        }
        y=min(b[p][q],4-b[p][q]);
        ans=ans-x+y;
        cout<<ans<<endl;
    }
}
```

---

## 作者：TZR087_42_Chaser (赞：0)

本题做法很明显了。

以下记 $f(x,y)$ 为将 $(x,y)$ 和与其对称的三个位置改成同为 `.` 和 `#` 的次数。显然 $f(x,y)=$ `.` 和 `#` 的个数中较小者。

开始之前，求出 $\sum^{\frac{n}{2}}_{i=1}\sum^{\frac{m}{2}}_{j=1}f(x,y)$。每次操作，减去 $f(x,y)$，将 $(x,y)$ 取反，再加上 $f(x,y)$ 即可。

时间复杂度 $\text{O}(N^2+U)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,x,y,t,ans;
char a[2005][2005];
int main(){
	cin>>n>>u;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n/2;i++){
		for(int j=1;j<=n/2;j++){
			t=0;
			if(a[i][j]=='#')t++;
			if(a[n+1-i][j]=='#')t++;
			if(a[i][n+1-j]=='#')t++;
			if(a[n+1-i][n+1-j]=='#')t++;
			ans+=min(t,4-t);
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=u;i++){
		cin>>x>>y;
		t=0;
		if(a[x][y]=='#')t++;
		if(a[n+1-x][y]=='#')t++;
		if(a[x][n+1-y]=='#')t++;
		if(a[n+1-x][n+1-y]=='#')t++;
		ans-=min(t,4-t);
		if(a[x][y]=='#')a[x][y]='.';
		else a[x][y]='#';
		t=0;
		if(a[x][y]=='#')t++;
		if(a[n+1-x][y]=='#')t++;
		if(a[x][n+1-y]=='#')t++;
		if(a[n+1-x][n+1-y]=='#')t++;
		ans+=min(t,4-t);
		cout<<ans<<endl;
	}
	return 0;
}

```

---

