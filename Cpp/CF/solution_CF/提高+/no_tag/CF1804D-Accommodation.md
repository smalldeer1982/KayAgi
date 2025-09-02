# Accommodation

## 题目描述

Annie is an amateur photographer. She likes to take pictures of giant residential buildings at night. She just took a picture of a huge rectangular building that can be seen as a table of $ n \times m $ windows. That means that the building has $ n $ floors and each floor has exactly $ m $ windows. Each window is either dark or bright, meaning there is light turned on in the room behind it.

Annies knows that each apartment in this building is either one-bedroom or two-bedroom. Each one-bedroom apartment has exactly one window representing it on the picture, and each two-bedroom apartment has exactly two consecutive windows on the same floor. Moreover, the value of $ m $ is guaranteed to be divisible by $ 4 $ and it is known that each floor has exactly $ \frac{m}{4} $ two-bedroom apartments and exactly $ \frac{m}{2} $ one-bedroom apartments. The actual layout of apartments is unknown and can be different for each floor.

Annie considers an apartment to be occupied if at least one of its windows is bright. She now wonders, what are the minimum and maximum possible number of occupied apartments if judged by the given picture?

Formally, for each of the floors, she comes up with some particular apartments layout with exactly $ \frac{m}{4} $ two-bedroom apartments (two consecutive windows) and $ \frac{m}{2} $ one-bedroom apartments (single window). She then counts the total number of apartments that have at least one bright window. What is the minimum and maximum possible number she can get?

## 说明/提示

In the first example, each floor consists of one two-bedroom apartment and two one-bedroom apartments.

The following apartment layout achieves the minimum possible number of occupied apartments equal to $ 7 $ .

```
<pre class="verbatim"><br></br>|0 1|0|0|<br></br>|1 1|0|0|<br></br>|0|1 1|0|<br></br>|1|0 1|0|<br></br>|1|0|1 1|<br></br>
```

The following apartment layout achieves the maximum possible number of occupied apartments equal to $ 10 $ .

```
<pre class="verbatim"><br></br>|0 1|0|0|<br></br>|1|1 0|0|<br></br>|0 1|1|0|<br></br>|1|0 1|0|<br></br>|1 0|1|1|<br></br>
```

## 样例 #1

### 输入

```
5 4
0100
1100
0110
1010
1011```

### 输出

```
7 10```

## 样例 #2

### 输入

```
1 8
01011100```

### 输出

```
3 4```

# 题解

## 作者：Vistarin (赞：8)

让我们考虑房间的分布在何时会影响答案。不难发现，对于连续的两间窗户，当灯光分布为 $\{ 0,0 \}$、$\{ 0,1 \}$ 和 $\{ 1,0 \}$ 时，双间房和单间房得到的答案是一样的。但是，当灯光分布为 $\{ 1,1 \}$ 时，双间房对答案的贡献为 $1$，而单间房的贡献为 $2$。

因此，对于每一层，当双间房尽可能多的分布在 $\{ 0,0 \}$、$\{ 0,1 \}$ 和 $\{ 1,0 \}$ 时，答案取最大值；当双间房尽可能多的分布在 $\{ 1,1 \}$ 时，答案取最小值。可以使用贪心实现上述操作。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve()
{
	int n, m;
	cin >> n >> m;

	int mx = 0, mn = 0;

	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;

		int cnt0 = 0, cnt1 = 0, num1 = 0;

		for (int j = 0; j < m; j++)
			if (s[j] == '1') num1++;

		for (int j = 1; j < m; j++)
		{
			if (s[j] + s[j - 1] != '1' + '1')
			{
				cnt0++;
				j++;
			}
		}
		for (int j = 1; j < m; j++)
		{
			if (s[j] + s[j - 1] == '1' + '1')
			{
				cnt1++;
				j++;
			}
		}

		mx += num1 - max(0, m / 4 - cnt0);
		mn += num1 - min(m / 4, cnt1);
	}

	cout << mn << ' ' << mx;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
}
```

---

## 作者：luogu_gza (赞：3)

你发现两居室会对答案产生较小的贡献。

因此，我们尽量把 $(1,1)$ 型的相邻灯看做两户居。

这是求最小值的，最大值只要把 $(1,1)$ 型尽量看做一户居即可。

---

## 作者：igAC (赞：3)

# $\text {Describe}$

[洛谷link](https://www.luogu.com.cn/problem/CF1804D)

[Codeforces link](https://www.codeforces.com/contest/1804/D)

给定一栋大楼，这栋楼一共有 $n$ 层，每层有 $m$ 扇窗户，以及每扇窗户是开着灯的还是关着灯的。

每层有 $\dfrac{m}{2}$ 个单间房和 $\dfrac{m}{4}$ 个双间房，单间房有一个窗户，双间房有两个窗户。

若窗户的灯是开的，那我们就认为这个房间被占用了，你可以对这些窗户进行划分，求最少被占用的房间和最多被占用的房间。

样例 #1：

```
0100
1100
0110
1010
1011
```

一种可能的最小占用方式为：

```
|0 1|0|0|
|1 1|0|0|
|0|1 1|0|
|1|0 1|0|
|1|0|1 1|
```

占用了 $7$ 个房间。

一种可能的最大占用方式为：

```
|0 1|0|0|
|1|1 0|0|
|0 1|1|0|
|1|0 1|0|
|1 0|1|1|
```

占用了 $10$ 个房间。

# $\text{Solution}$

诈骗题。

因为是要求最大最小值，所以我们考虑贪心。

对于最小值，肯定是要让两个 ``1`` 结合起来最赚。

于是我们对于每个明亮的窗户，判断它的后一位是否是 ``1``，若是 ``1``，那么这两扇窗户就归为一个双间房，答案加一。

若后一位不是 ``1`` ，那么自己单独为一个房间（因为我们只关心答案，构造方案是无所谓的，而且它是否与后面的 ``0`` 结合对答案也是没有任何影响的），答案加一。

还要注意双人房的个数不能超过 $\dfrac{m}{4}$。

接下来考虑最大的情况：

因为要占用的房间最多，所以让两个 ``0`` 结合在一起最赚，然后将它们两赋为已操作。

第二赚的是 ``0`` 和 ``1`` 结合，将它们赋为已操作，答案加一。

做完上面两种操作后，这层楼就没有 ``0`` 了。

只剩统计 ``1`` 的答案了，此时需要先统计两个 ``1`` 连在一起的个数（在双间房没达到 $\dfrac{m}{4}$ 的情况下），再统计单个 ``1`` 的个数。

因为每层楼都有 $\dfrac{m}{4}$ 个双间房。

那么这道题就做完了。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
string s[N];
int n,m,ans1,ans2;
bool vis[N];
int main(){
	n=read(),m=read();
	int cnt1=m/2,cnt2=m/4;
	for(int i=1;i<=n;++i){
		cin>>s[i];
		s[i]=" "+s[i];
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j) vis[j]=0;
		int now1=0,now2=0;
		for(int j=1;j<=m;){
			if(s[i][j]=='1'){
				++ans1;
				if(j<m && s[i][j]==s[i][j+1] && now1<cnt2){
					j+=2,++now1;
					continue;
				}
			}
			++j;
		}
		for(int j=1;j<=m;){
			if(j<m && s[i][j]==s[i][j+1] && s[i][j]=='0' && now2<cnt2){
				++now2;
				vis[j]=vis[j+1]=true;
				j+=2;
				continue;
			}
			else if(j<m && s[i][j]!=s[i][j+1] && now2<cnt2){
				++now2,++ans2;
				vis[j]=vis[j+1]=true;
				j+=2;
				continue;
			}
			++j;
		}
		for(int j=1;j<=m;){
			if(j<m && s[i][j]==s[i][j+1] && s[i][j]=='1' && now2<cnt2 && !vis[j] && !vis[j+1]){
				vis[j]=vis[j+1]=true;
				j+=2,++now2,++ans2;
				continue;
			}
			else if(s[i][j]=='1' && !vis[j]){
				vis[j]=true;
				++j,++ans2;
				continue;
			}
			++j;
		}
	}
	printf("%d %d",ans1,ans2);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：3)

考场上没想出来。。

每一行是独立的，我们直接相加每一行的答案即可。

一居室的贡献就是这个格子的数字，考虑二居室的影响。

- $(0,0)\to 0$。
- $(1,0),(0,1),(1,1)\to 1$。

发现唯一对和有影响的是 $(1,1)\to 1$。

所以对最小化只要更多的取 $(1,1)$，最大化的只要更多的取 $(0,0),(1,0),(0,1)$ 即可。贪心。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
int _,n;string s;
int le,ri;
void solve(){
	cin>>s;s=" "+s;
	int c=0,cl=0,cr=0;
	for(int i=1;i<=n;i++) c+=(s[i]=='1');
	for(int i=1;i<n;i++)
		if(s[i]=='1'&&s[i+1]=='1') cl++,i++;
	for(int i=1;i<n;i++)
		if(s[i]!='1'||s[i+1]!='1') cr++,i++;
	le+=max(0,c-cl);
	ri+=c-max(0,n/4-cr);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_>>n;
	while(_--) solve();
	cout<<le<<' '<<ri<<endl;
}

```

---

## 作者：inc1ude_c (赞：1)

由于行与行之间是独立的，所以我们可以一行一行进行计算后相加。

在该题解中，我们会把两个房间都亮的两居室叫做满两居室，把只有一个房间亮的两居室叫做残两居室。

计算居住人数最小值就是最大化满两居室个数（即将两个连续的 $1$ 看作一个两居室），但要注意满两居室个数不能超过 $\frac{m}{4}$，即要与 $\frac{m}{4}$ 取最小。居住的人数即 $1$ 的个数减去这个最小值。

计算人数最大值就是最大化残两居室个数（即将两个状态不相同的看作一个两居室），也要注意残两居室个数不能超过 $\frac{m}{4}$，这时问题来了：残两居室个数不够 $\frac{m}{4}$ 怎么办？那我们只好选择一些满两居室来弥补。居住的人数即 $1$ 的个数减去满两居室的个数。

可能你会问为什么在计算居住人数最小值时不考虑两居室个数够不够 $\frac{m}{4}$，实际上，如果不够，那么我们就选择一些残两居室，一间残两居室可以看作是一居室。所以自然而然地，两居室个数就齐了。

[Code](https://codeforces.com/contest/1804/submission/197477697)

---

## 作者：Priestess_SLG (赞：0)

又是大水题。

考虑连续两个元素对答案的贡献。

+ $(0,0)$：一居室和二居室对答案的贡献均为 $0$。（$1$）
+ $(0,1)$：一居室和二居室对答案的贡献均为 $1$。（$2$）
+ $(1,0)$：一居室和二居室对答案的贡献均为 $1$。（$3$）
+ $(1,1)$：一居室对答案的贡献为 $2$，二居室对答案的贡献为 $1$。（$4$）

因此可以发现只有（$4$）时一居室和二居室答案不一样，因此考虑简单贪心。最小值就尽可能让 $(1,1)$ 用二居室，最大值就尽可能让 $(1,1)$ 用一居室。时间复杂度为 $O(nm)$。

代码十分好写。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N = 200100;
int f[N][22][2], a[N];
signed main() {
    int n, m;
    cin >> n >> m;
    int c1 = 0, c2 = 0;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        s = ' ' + s;
        int ff = 0;
        for (int j = 1; j <= m; ++j) {
            if (s[j] == '1') {
                ++ff;
            }
        }
        int gg = 0;
        for (int j = 1; j < m; ++j) {
            if (s[j] == '1' && s[j + 1] == '1') {
                ++j, ++gg;
            }
        }
        int hh = 0;
        for (int j = 1; j < m; ++j) {
            if (!(s[j] == '1' && s[j + 1] == '1')) {
                ++j, ++hh;
            }
        }
        c1 += ff - max(0ll, m / 4 - hh);
        c2 += ff - min(m / 4, gg);
    }
    cout << c2 << ' ' << c1 << '\n';
    return 0;
}

/*



*/
```

---

## 作者：OIer_Hhy (赞：0)

这道题，显然是个贪心。

考虑相邻两扇窗的贡献。

- $a_i=0,a_{i+1}=0$ 时，没有人家。
- $a_i=0,a_{i+1}=1$ 或 $a_i=1,a_{i+1}=0$ 时，有 $1$ 户人家。
- $a_i=1,a_{i+1}=1$ 时，可能有 $1$ 户人家，也可能有 $2$ 户人家。

因为 $a_i=0,a_{i+1}=0$ 时，$a_i=0,a_{i+1}=1$ 时和 $a_i=1,a_{i+1}=0$ 时是确定的，所以我们在取最小值的时候，尽量让 $a_i=1,a_{i+1}=1$ 时有一户人家开了两扇灯；取最大值的时候，尽量让 $a_i=1,a_{i+1}=1$ 时有 $2$ 户人家开了两扇灯。

[my code](https://www.luogu.com.cn/paste/2h37gqt8)

---

## 作者：N1K_J (赞：0)

跟一个诈骗题斗智斗勇了一个晚自习并用该题硬控数竞组一整晚。

先来看最小值。

首先要注意到想要让主人的房间少肯定是尽量让相邻的亮灯窗户变成一个双人间。

考虑贪心，先去除所有相邻的亮窗户构成住人双人间，剩下的亮的每一个都一定代表一个单人间。

代码如下

```cpp
for(ll i = 1; i < m; i++) if(rom[i]&&rom[i+1]){
	tob++;
	chk[i] = chk[i+1] = true;
	i++;
	if(tob==m/4) break;
}
mi = tob;
for(ll i = 1; i <= m; i++) if(rom[i]&&!chk[i]) mi++;
```

这里直接把剩下亮的的都算成一个住人房间而不需要考虑住人的房间分布，这是因为剩下的亮的房间没有相邻的了。

然后是最大值。

注意到要尽量让双人间不是相邻的亮窗户，所以设最多能取出 $T$ 对不重复的相邻窗户使他们不是都亮着的，让双人间是这些位置显然是不劣的，所以再设有 $S$ 个亮的窗户，结果就是 $S-\max(0,\dfrac{m}{4}-T)$。

[Code](https://codeforces.com/contest/1804/submission/249732549)

---

## 作者：Ruan_ji (赞：0)

### 题目大意
评价：这道题目真的是蓝题吗？我好疑惑啊，很简单的题目。

题目中的一句话让这个题目变得简单了很多，就是：**不同楼层的一居室和两居室的分布可能不同**。

可以明确的是，不管是一居室还是两居室（也就是一个窗户还是两个窗户），只要一个窗户开灯，那么就代表有人。简单捋一下，题目要我们求最多住多少人和最少住多少人。显然，在不同的要求下，我我们要尽可能地增加一居室数量或者两居室数量。

### 解题思路
考虑最少住多少人。对于每一个连着的两个窗户均为 $1$ 的时候，并且两居室的数量不超过 $\dfrac{m}{4}$ 的情况下，我们尽量使用二居室覆盖掉。因为二居室直接可以干掉两个亮的窗户，很赚。

连着两个都是 $1$ 的都被干掉了之后，就可以去干掉只有一个亮灯的了，这里需要特别强调，**二居室不可以互相覆盖啊！你见过谁家的房子互相覆盖**。这是个易错点，需要特别注意。

接下来考虑最多住多少人。先把二居室的打发掉，让他们只能干掉一个灯，其余的灯全部改成一居室，完事。注意一下，二居室的需要达到 $\dfrac{m}{4}$ 的峰值。

实现起来并不简单，我们一起看代码。

### 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n, m, mn, mx;
char house[5000005]; //这个数组只存一行

int main(){
	cin >> n >> m;
	while(n--) {
		//各行之间不影响，直接开始，真爽
		int d = m / 4, c = 0, k = 0; //d是两居室个数，c是可能的房间，k是两居室
		cin >> house + 1; //个人的习惯问题
		for (int i = 1; i < m; ++i) //下面就是正常的统计
			if(house[i] == '1' && house[i + 1] == '1') 
				++c, ++i; 
		for (int i = 1; i < m; ++i) //判断的时候细节很多，需要仔细考虑
			if(house[i] != '1' || house[i + 1] != '1') 
				++k, ++i;
		for (int i = 1; i <= m; ++i)
			mn += (house[i] & 1), mx += (house[i] & 1); //这里的&的意思可以细品一下
		
		mn -= min(c, d); mx -= max(d - k, 0); //算答案
	}
	
	cout << mn << " " << mx << endl;
	return 0; //开心，散花
} 

```


---

