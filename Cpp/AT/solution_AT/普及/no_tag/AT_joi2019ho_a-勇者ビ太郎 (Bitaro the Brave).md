# 勇者ビ太郎 (Bitaro the Brave)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2019ho/tasks/joi2019ho_a

![2019-ho-t1-fig01.jpg](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_joi2019ho_a/09009490d7383ad8a773f434baef49f70d623222.png)

勇者のビ太郎は，魔王と対峙することとなった．

ビ太郎は，縦 $ H $ 行，横 $ W $ 列のマス目上に宝石 (Jewel)，オーブ (Orb)，金塊 (Ingot) を配置し，魔法を発動することによって魔王に攻撃をしようとしている．以下，マス目のうち上から $ i $ 行目 ($ 1\ \leqq\ i\ \leqq\ H $)，左から $ j $ 列目 ($ 1\ \leqq\ j\ \leqq\ W $) のマスを，マス $ (i,\ j) $ と表す．

ビ太郎は今，それぞれのマスにこれら $ 3 $ 種類のうち $ 1 $ 個を配置した．今から魔法を発動しようとしているが，この魔法の威力はマス目上の宝石，オーブ，金塊の配置によって決まる．具体的には，次の条件を満たす整数 $ (i,\ j,\ k,\ l) $ ($ 1\ \leqq\ i\ <\ k\ \leqq\ H $，$ 1\ \leqq\ j\ <\ l\ \leqq\ W $) の組の個数が，魔法の威力である．

条件：マス $ (i,\ j) $ には宝石が，マス $ (i,\ l) $ にはオーブが，マス $ (k,\ j) $ には金塊が置かれている．

ビ太郎は，この魔法の威力が気になっている．

マス目上の宝石，オーブ，金塊の配置が与えられたとき，ビ太郎が発動する魔法の威力を求めるプログラムを作成せよ．

- - - - - -

## 说明/提示

### 制約

- $ 2\ \leqq\ H\ \leqq\ 3\,000 $．
- $ 2\ \leqq\ W\ \leqq\ 3\,000 $．
- $ S_i $ は長さ $ W $ の文字列である ($ 1\ \leqq\ i\ \leqq\ H $)．
- $ S_i $ の各文字は `J`，`O`，`I` のいずれかである ($ 1\ \leqq\ i\ \leqq\ H $)．

### 小課題

1. ($ 20 $ 点) $ H\ \leqq\ 100 $，$ W\ \leqq\ 100 $．
2. ($ 30 $ 点) $ H\ \leqq\ 500 $，$ W\ \leqq\ 500 $．
3. ($ 50 $ 点) 追加の制約はない．

- - - - - -

### Sample Explanation 1

この入力例では，$ (i,\ j,\ k,\ l)\ =\ (1,\ 1,\ 3,\ 2),\ (2,\ 1,\ 3,\ 3),\ (2,\ 1,\ 3,\ 4) $ の $ 3 $ 個の組が条件を満たすので，答えは $ 3 $ である． - - - - - -

## 样例 #1

### 输入

```
3 4
JOIJ
JIOO
IIII```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4
JJOO
JJOO
IIJO
IIIJ```

### 输出

```
17```

# 题解

## 作者：donnieguo (赞：1)

## 题意简述

翻译有点拗口，我来给大家简化一下。

给定一个大小为 $H \times W$，由 `J`，`O` 和 `I` 组成的矩阵，求满足条件的四元组 $(i,j,k,l)$ 的数量。

条件：$(i,j)$ 格子上的字符为 `J`，$(i,l)$（与 $(i,j)$ 在同一行）上的字符为 `O`，$(k,j)$（与 $(i,j)$ 在同一列）上的字符为 `I`。

例如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/merh8eag.png)

就是一个合法的四元组（红色格子为 `J`，蓝色格子为 `I`，黄色格子为 `O`）。

## 思路

首先暴力枚举肯定是不行的， $2 \le H \le 3000$，$2 \le W \le 3000$ 的数据范围肯定会 TLE。

考虑使用前缀和优化。观察以下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/170kid9v.png)

其实不难发现，如果红色格子为 `J`，那么根据乘法原理可得，这个格子对于答案的贡献就是黄色格子中 `O` 的数量和蓝色格子中 `I` 的数量的乘积。
  
我们使用数组 `s1[i][j]` 表示第 $i$ 行的第 $1$ 个格子到第 $j$ 个格子中 `O` 的数量，`s2[i][j]` 表示第 $j$ 列中第 $1$ 行到第 $i$ 行中 `I` 的数量。

那么如果第 $(i,j)$ 个格子是 `J`，这个格子对答案的贡献就是 `(s1[i][m] - s1[i][j]) * (s2[n][j] - s2[i][j])`。

注意：

- 数组 `s1` 和 `s2` 不是二维前缀和，`s1[i][j]` 只与 `s1[i][j - 1]` 有关系，`s2` 只与 `s2[i - 1][j]` 有关系。

- 这里应该是 `s1[i][m] - s1[i][j + 1 - 1]` ，但是 $+1$ 和 $-1$ 可以抵消。

- 记得开 `long long`。

时间复杂度为 $\Theta(HW)$，可以通过。

## AC code

```cpp
#include <iostream>
#define N 3010
using namespace std;
typedef long long ll;

int n, m;
char a[N][N];
int s1[N][N], s2[N][N];
ll ans;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> a[i][j];
			s1[i][j] = s1[i][j - 1] + (a[i][j] == 'O' ? 1 : 0);
			s2[i][j] = s2[i - 1][j] + (a[i][j] == 'I' ? 1 : 0);
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (a[i][j] == 'J')
				ans += 1ll * (s1[i][m] - s1[i][j]) * (s2[n][j] - s2[i][j]);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：SnowFlavour (赞：1)

## 读题
先读一遍题面，这一句话写的非常拗口：
>具体的，威力大小等于满足以下条件的有序四元组 $(i, j, k, l)(1 \le i < k \le H, 1 \le j < l \le W)$ 的数量。条件：$(i, j)$ 位置的格子上的道具为 `J`，$(i, l)$ 位置上的道具为 `O`，$(k, j)$ 位置上的道具为 `I`。

**（注意：这里的坐标是从上往下数的，所以不能直接用平面直角坐标系理解这里的四个数。）**

然而我们只要仔细读，就会发现其实他想要表达的是这样的：有如图所示三个点，$B$ 在 $A$ 的右边，$C$ 在 $A$ 的下边，其中 $A$ 点为`J`， $b$ 点为`O`， $c$ 点为`I`，求满足此关系的 $A,B,C$ 点有多少个。

![](https://cdn.luogu.com.cn/upload/image_hosting/07e8f8s2.png)

## 思路 1：枚举
我们很容易想到第一个思路：枚举。

也就是说，枚举每一个 $A$ 点，然后从这个点出发，向右统计 $B$ 点，向下统计 $C$ 点，再把两个数相乘，得到的积即为这个 $A$ 点会增加多少威力。

~~听上去老简单了是不是~~ ，但是你仔细一看就会发现这个算法的时间复杂度为 $O(hw^2+h^2w)$，然而本题的范围是这样的：
>- $ 2\ \leqq\ H\ \leqq\ 3\,000 $．
>- $ 2\ \leqq\ W\ \leqq\ 3\,000 $．

所以，会超时的。
## 思路 2（正解）：后缀和

其实这个思路依然可以算是枚举。重点在于，在上一个思路中，我们会重复计算一大堆数据，这就导致了严重的超时。所以我们可以用后缀和进行优化。

具体的方法是这样的：定义数组 `cnt_i[i][j]`，表示第 $i$ 列中从上往下第 $j$ 个字符以后有多少个字符`I`。同理，定义数组 `cnt_o[i][j]`，表示第 $i$ 行中从左往右第 $j$ 个字符以后有多少个字符`O`。

这样的话，某一个点 $A(x,y)$ 的威力就是 $cnt\_i[y][x] \times cnt\_o[x][y]$。

这样的时间复杂度为 $O(hw)$，可以通过本题。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+10;
int n,m;
long long ans=0;
int mp[N][N];
int cnt_i[N][N],cnt_o[N][N];
int main(){

	cin>>n>>m;
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		for(int j=0;j<m;j++){
			if(s[j]=='J')mp[i][j]=0; //转化为数字，方便处理（用字符容易 RE）
			if(s[j]=='O')mp[i][j]=1;
			if(s[j]=='I')mp[i][j]=2;
		}
	}
	memset(cnt_i,0,sizeof(cnt_i));//清空数组
	memset(cnt_o,0,sizeof(cnt_o));
	for(int i=0;i<n;i++){
		int status=0;
		for(int j=m-1;j>=0;j--){
			if(mp[i][j]==1)status++;
			cnt_o[i][j]=status;
		}
	}
	for(int i=0;i<m;i++){
		int status=0;
		for(int j=n-1;j>=0;j--){
			if(mp[j][i]==2)status++;
			cnt_i[i][j]=status;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(mp[i][j]==0)
			ans+=cnt_i[j][i]*cnt_o[i][j];
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：yanmingqian (赞：0)

重题警告：[P11788](https://www.luogu.com.cn/problem/P11788)

显然对于每一个 J，我们后缀统计同行在其右的 O 的个数和同列在其下的 I 的个数，二者相乘即可。

代码：

```cpp
#include<iostream>
using namespace std;
char c[3010][3010];
int s1[3010][3010],s2[3010][3010];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
		}
	} 
	long long ans=0;
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
            s1[i][j]=s1[i][j+1]+(c[i][j]=='O');
            s2[i][j]=s2[i+1][j]+(c[i][j]=='I');
			if(c[i][j]=='J'){
				ans+=s1[i][j]*s2[i][j];
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：XxLlQq (赞：0)

## 思路

`J` 的坐标为 $(i,j)$，`O` 的坐标为 $(i,l)$，`K` 的坐标为 $(k,j)$ 从题目中给出的信息可以发现 `O` 与 `K` 都与 `J` 有关系。

在题目所描述的合法四元组中，`J` 与 `O` 必须是同一行，且 `O` 比 `J` 靠后，也就是列数更大。

`J` 与 `K` 必须是同一列，且 `K` 比 `J` 靠后，也就是行数数更大。

所以说只要求出 `J` 的后缀和 `O` 与 `K` 的数量就可以了。最后枚举 `J` 将其两个后缀和相乘再累加就可以了。
# AC code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<iomanip>
#include<string>
#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
const int N=3e3+5;
int n,m,fo[N][N],fi[N][N];
long long ans=0;
char a[N][N];
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			cin>>a[i][j];
			if(a[i][j]=='O') fo[i][j]++;
			if(a[i][j]=='I') fi[i][j]++;
		}
//注意此处求的是后缀和，故从n,m开始
	for(int i=n; i>=1; i--)
		for(int j=m; j>=1; j--) {
			fo[i][j]+=fo[i][j+1];//每行O的数量
			fi[i][j]+=fi[i+1][j];//每列I的数量
		}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(a[i][j]=='J') ans=ans+fo[i][j]*fi[i][j];
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：PeterBei (赞：0)

观察四元组形式，容易发现对于每个 ``J`` 而言，有且仅有与其同一行的 ``O`` 以及与其同一列的 ``I`` 可以组成满足题目要求的四元组。

则考虑对于每个 ``J`` 而言，满足要求的 ``O`` 和 ``I`` 分别有多少个，将两者相乘即为当前 ``J`` 贡献的答案。

$O(n^2)$ 枚举每个位置是否为 ``J``，``O`` 和 ``I`` 的数量可以通过后缀和数组 $O(1)$ 求得。总时间复杂度 $O(n^2)$，可以通过。

```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;

long long read(){
	char c = getchar(); long long f = 1, a = 0;
	while(c != '-' && (c > '9' || c < '0'))
		c = getchar();
	if(c == '-')
		f = -1, c = getchar();
	while(c >= '0' && c <= '9')
		a = a * 10 + (c - '0'), c = getchar();
	return f * a;
}
char str[3010], a[3010][3010];
long long ans = 0, O[3010][3010], I[3010][3010];
int main(){
//	freopen("brave.in", "r", stdin);
//	freopen("brave.out", "w", stdout);
	long long n = read(), m = read();
	for(long long i = 1; i <= n; i++){
		scanf("%s", str + 1);
		for(long long j = 1; j <= m; j++){
			a[i][j] = str[j];
		}
	}
	for(long long i = n; i >= 1; i--){
		for(long long j = m; j >= 1; j--){
			O[i][j] += O[i][j + 1] + (a[i][j] == 'O');
			I[i][j] += I[i + 1][j] + (a[i][j] == 'I');
		} 
	}
	for(long long i = n; i >= 1; i--){
		for(long long j = m; j >= 1; j--){
			if(a[i][j] == 'J'){
				ans += O[i][j] * I[i][j];
			}
		}
	} cout << ans << '\n';
	return 0;
}
```

---

## 作者：WhitD (赞：0)

## 题意简述
给定一个大小为 $H\times W$ 的由 `JOI` 三种字符构成的字符矩形，求满足 $(i,j)$ 位置为 `J`、$(i,l)$ 位置为 `O`、$(k,j)$ 位置为 `I` 的四元组 $(i,j,k,l)(1\le i<k\le H,1\le j<l\le W)$ 的总数量。
## 思路
我们从限制条件入手，不难发现满足条件的四元组中：每个 `J` 与 `O` 具有相同的横坐标 $i$；每个 `J` 与 `I` 具有相同的纵坐标 $j$，而且 `O` 的纵坐标 $l$ 要大于 `J` 的纵坐标 $j$；`I` 的横坐标 $k$ 大于 `J` 的横坐标 $i$。

考虑下图，设红色格子为 `J`，则满足条件的 `O` 只会在绿色格子中、满足条件的 `I` 只会在蓝色格子中：

![](https://cdn.luogu.com.cn/upload/image_hosting/uql69za2.png)

显然，对于这个红色格子，所有合法的答案数量为：

$$\texttt{绿色格子中 O 的数量}\times\texttt{蓝色格子中 I 的数量}$$

而绿色，蓝色格子一定是某一行（列）中连续的一段，直接用前缀和数组维护就可以了，最后枚举红色格子（即字符为 `J` 的格子）累加答案即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3005;
char s[N][N];
int n,m,O[N][N],I[N][N];
long long ans;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>s[i][j],O[i][j]=O[i][j-1]+(s[i][j]=='O'),I[i][j]=I[i-1][j]+(s[i][j]=='I');
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans+=((s[i][j]=='J')*1ll*(O[i][m]-O[i][j])*(I[n][j]-I[i][j]));
	cout<<ans;
	return 0;
}
```


---

