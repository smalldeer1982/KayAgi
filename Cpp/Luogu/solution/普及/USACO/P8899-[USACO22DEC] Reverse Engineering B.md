# [USACO22DEC] Reverse Engineering B

## 题目描述

Elsie 有一个程序，接受一个 $N(1 \le N \le 100)$ 个变量的数组 $b[0], \cdots ,b[N−1]$ 作为输入，其中每个变量等于 $0$ 或 $1$，并且返回对输入数组应用一系列 `if / else if / else` 语句的结果。每个语句检查至多一个输入变量的值，并返回 $0$ 或 $1$。这类程序的一个例子是：

```cpp
if (b[1] == 1) return 1;
else if (b[0] == 0) return 0;
else return 1;
```

例如，如果上方程序的输入是 "10"（即 $b[0]=1$ 及 $b[1]=0$），那么输出应当为 $1$。 

Elsie 告诉了 Bessie 对于 $M(1 \le M \le 100)$ 个不同输入的正确输出。Bessie 现在正试图对 Elsie 的程序进行逆向工程。不幸的是，Elsie 可能说了谎；可能不存在上述形式的程序行为与 Elsie 所说的均一致。 

对于 $T(1 \le T \le 10)$ 个子测试用例中的每一个，判断 Elsie 是否一定在说谎。

## 说明/提示

### 样例 1 解释

以下是第一个子测试用例的一个合法的程序：

```cpp
if (b[0] == 0) return 0;
else return 1;
```

以下是第一个子测试用例的另一个合法的程序：

```cpp
if (b[0] == 1) return 1;
else return 0;
```

以下是第二个子测试用例的一个合法的程序：

```cpp
if (b[1] == 1) return 1;
else if (b[0] == 0) return 0;
else return 1;
```

显然，对于第三个子测试用例不存在对应的合法的程序，因为 Elsie 的程序一定始终对相同的输入产生相同的输出。

可以证明对于最后一个子测试用例不存在对应的合法的程序。 

### 测试点性质

- 测试点 $2-3$ 满足 $N=2$。
- 测试点 $4-5$ 满足 $M=2$。
- 测试点 $6-12$ 没有额外限制。 

## 样例 #1

### 输入

```
4

1 3
0 0
0 0
1 1

2 4
00 0
01 1
10 1
11 1

1 2
0 1
0 0

2 4
00 0
01 1
10 1
11 0```

### 输出

```
OK
OK
LIE
LIE```

# 题解

## 作者：ztntonny (赞：53)

# 看不懂楼上下神犇做法的来这里！！！

```
//这个题解可以让您以最快的时间读完，有重点加粗标记
//是作者以1个小时调程序+2个小时写题解的心血
//诣在讲透讲懂本题，让您理解
//完全聚焦本题重难点
//还在等什么？快来看吧！
```

看了诸位大佬的题解，本人认为对于我们这些蒟蒻有些简短的残忍，于是写一个亲民又朴实的题解，分析清楚楼上大佬的做法。

楼上叙述的做法是：枚举每一位，将这一位是 $1$ 和 $0$ 的**分别考虑**。如果某一位是 $1$ 的**答案都一样**，那么这一位上所有为 $1$ 或 $0$ 的语句都可以**删除**。如果最后被**删光了**就可以，否则就说谎了。

----------------------------------------------------------------**好好理解上面的方法才能继续**----------------------------------------------------------------

那么我这个蒟蒻就开始不理解为什么了，有两点：

1. 这么做的道理是啥，看起来有点投机取巧
2. 就算这有道理，好像顺序还不大对啊，题目没说固定啊


### $No.1Problem$

我研究了一会儿，第一点懂了，下面画个图：

![输入图片说明](https://cdn.luogu.com.cn/upload/image_hosting/2sfg8uhp.png)

如此我们就完美的掉入了坑中，注意 ```return true/false``` 是有**结束程序**的功能的，所以在已经被删除的语句我们要**不考虑**了，于是正确的图：

![输入图片说明](https://cdn.luogu.com.cn/upload/image_hosting/kwb09gy7.png)

所以这些语句就都被删掉了。那么这样的原理？因为如果顺序固定正向，碰到了位置上一样且答案一样的就有充分的证据说明这里可以作为一个判断语句，**注意我们是构造不是求解，不需要唯一正确**，所以就一定能删掉。

于是其实就是一次模拟，最后查一遍如果没有删完，那么说明到了最后一个语句都没办法判断完成，就是在说谎。

### $No.2Problem$

最玄学的问题来了，但是其实有了上一问题的深刻理解，这个也不难参透。**假设**有数语句**不可以**在正序下**删除**，令他们为集合 $q$，那么我们首先分析出 $q$ 都**有至少一位相同**，且 $q$ 内的语句**答案都相同**，于是满足假设的情况只能是：当正向删除的时候有一些语句，令他们为集合 $p$ ，那么 $p$ 的答案**全部不同于** $q$ 的答案，且 $p$ 与 $q$ **有且仅有一位**都相同，而不同方向可以提前删掉 $p$。再分析，得到 $q$ 中的语句必然相同的位都在 $p$ 的相同位之前，要不然别的位还可以完成，又有 $p$ 中的相同位上 $q$ 必然都不等于 $p$ 的对应位要不就提前删了，于是得到 $q$ 在 $p$ 的相同位上也都相同且不等于 $q$ 的对应位，那么事实上我们就可以在正序的情况下在该位同时删掉 $p$ 和 $q$，**假设不成立**，证毕！

图总是最清楚明了的：

![输入图片说明](https://cdn.luogu.com.cn/upload/image_hosting/2qzm4afb.png)

----------------------------------------------------------------**喘口气我们继续**----------------------------------------------------------------

那么终于证完了，下面就是代码实现了！

我的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n , t , p[105] , f[105] , m;
string s[105];
bool y[105][105];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL) , cout.tie(NULL);
	cin >> t;
	while ( t-- )
	{
		cin >> m >> n;
		bool flag[n + 1] , e = 1 , k[n + 1];
		for ( int i = 1; i <= n; i++ )	cin >> s[i] >> p[i] , flag[i] = 0;
		for ( int j = 1; j <= m; j++ )
			for ( int l = 0; l < m; l++ )
			{
				int k[2] = { 0 , 0 } , buck[2] = { 2 , 2 };
				for ( int i = 1; i <= n; i++ )
				{
					y[i][l] = ( s[i][l] == '1' );
					if ( flag[i] )	continue;
					if ( buck[y[i][l]] == 2 )	buck[y[i][l]] = p[i];
					else	if ( buck[y[i][l]] != p[i] )	k[y[i][l]] = 1;
				}
				for ( int i = 1; i <= n; i++ )	if ( !k[y[i][l]] )	flag[i] = 1;
			}
		for ( int i = 1; i <= n; i++ )	if ( !flag[i] )	e = 0;
		if ( e )	cout << "OK" << endl;
		else	cout << "LIE" << endl;
	}
	return 0;
}

//希望这篇题解对您有帮助，也希望推动洛谷和谐友爱的学习交流环境，望您支持，谢谢！
```


---

## 作者：joyslog (赞：10)

按位匹配。如果某一位上的某些输入中，$0$ 和 $1$ 分别的对应是没有冲突的（即没有出现有些 $0$ 对应 $1$，有些 $0$ 对应 $0$ 这种情况），我们就可以加一个 `if` 语句让这些不冲突的输入都返回正确的答案。

然后我们下一轮匹配就不用再匹配这些已经确定能返回正确答案的输入了。

最多匹配 $n$ 轮，每轮要遍历每一输入输出的每一位。故时间复杂度 $O(n^2 m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX_N = 110;
bool a[MAX_N][MAX_N], res[MAX_N], vis[MAX_N], flag[2];
int bl[2];

// 省略快读快写
inline ll read() {...}
inline void write(ll x) {...}
inline bool read_bool() {...}

int main() {
    int T = read();
    while(T--) {
        int n = read(), m = read();
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++)
                a[i][j] = read_bool();
            res[i] = read_bool();
            vis[i] = 0;
        }
        for(int k = 1; k <= n; k++) {
            for(int j = 1; j <= n; j++) {
                bl[0] = bl[1] = -1; flag[0] = flag[1] = 0;
                for(int i = 1; i <= m; i++) {
                    if(vis[i])  continue;
                    if(bl[a[i][j]] == -1)   bl[a[i][j]] = res[i];
                    else if(bl[a[i][j]] != res[i])  flag[a[i][j]] = 1;
                }
                for(int i = 1; i <= m; i++)
                    if(!flag[a[i][j]])  vis[i] = 1;
            }
        }
        bool f = 0;
        for(int i = 1; i <= m; i++)
            if(!vis[i])  f = 1;
        puts(f ? "LIE" : "OK");
    }
    return 0;
}
```

---

## 作者：zajasi (赞：6)

## 解题思路
对于每一位，我们将这一位是 $1$ 和 $0$ 的分别拉出来。如果某一位是 $1$ 的结果都一样，那么这一位上所有为 $1$ 的回答都可以删掉。$0$ 也一样的操作。到最后，如果被删光了或者剩下的结果都相同，那么就可以，否则就说谎了。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ugly 1145141919810
int t;
int n, m;
int vis[101];
vector<pair<int, int> > z;
vector<pair<string, int> > a;
string x;
int y;
bool check() {
	if (a.size() == 0)return true;
	int c = a[0].second;
	for (int i = 1; i < a.size(); i++) {
		if (a[i].second != c)return false;
	}
	return true;
}
string aa, bb, cc, dd;
main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> m;
//		if(m==2){
//			cin>>aa>>bb>>cc>>dd;
//			if(aa==cc&&bb!=dd)cout<<"LIE\n";
//			else cout<<"OK\n";
//			continue;
//		}
		a.clear();
		for (int i = 1; i <= m; i++) {
			cin >> x >> y;
			a.push_back(make_pair(x, y));
		}
//		cout << "--------------------\n";
//		for (int j = 0; j < a.size(); j++) {
//			cout << a[j].first << " " << a[j].second << "\n";
//		}
//		cout << "--------------------\n";
		memset(vis, 0, sizeof vis);
		int cc = 0;
		bool changed = true;
		while (changed == true && a.size() > 0) {
			changed = false;
			for (int i = 0; i < n; i++) {
				int c0 = ugly, c1 = ugly, f = 0;
				vector<int> b;
				for (int j = 0; j < a.size(); j++) {
					if (a[j].first[i] == '0')b.push_back(j), f = 2;
					else continue;
//					cout << "judge : " << j << "\n";
					if (a[j].first[i] == '0' && c0 == ugly)c0 = a[j].second;
					else if (a[j].first[i] == '0') {
						if (c0 != a[j].second) {
							f = 1;
							break;
						}
					}
				}
				if (f == 2) {
					for (int j = 0; j < b.size(); j++) {
						a.erase(a.begin() + b[j] - j, a.begin() + b[j] + 1 - j);
					}
					changed = true;
				}
//				for (int j = 0; j < a.size(); j++) {
//					cout << a[j].first << " " << a[j].second << "\n";
//				}
//				cout << "--------------------\n";
				b.clear();
				f = 0;
				for (int j = 0; j < a.size(); j++) {
					if (a[j].first[i] == '1')b.push_back(j), f = 2;
					if (a[j].first[i] == '1' && c1 == ugly)c1 = a[j].second;
					else if (a[j].first[i] == '1') {
						if (c1 != a[j].second) {
							f = 1;
							break;
						}
					}
				}
				if (f == 2) {
					for (int j = 0; j < b.size(); j++) {
						a.erase(a.begin() + b[j] - j, a.begin() + b[j] + 1 - j);
					}
					changed = true;
				}
//				for (int j = 0; j < a.size(); j++) {
//					cout << a[j].first << " " << a[j].second << "\n";
//				}
//				cout << "--------------------\n";
			}

		}
		if (check()) {
			cout << "OK\n";
			continue;
		}

		cout << "LIE\n";
	}
	return 0;

}

```

---

## 作者：guozhetao (赞：4)

## 思路
我们先考虑 $01$ 串的其中一位。

首先，如果两个 $01$ 串的第 $x$ 位一样，答案也一样，那么可以将这两个 $01$ 串删掉（打上标记代表两个已经被删去），因为可以通过 ```if (b[x] == 共同的位) return 共同的答案;```来解决。

我们重复循环。如果一次循环什么东西都没删，而且还没删完，就直接返回 `LIE`。因为接下来无论如何循环结果都不会改变。

如果删完了，返回 `OK`。
## 代码
[AC](https://www.luogu.com.cn/record/98359253)
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<queue>
#include<map>
#include<algorithm>

using namespace std;

// 快读
inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while (ch < '0' or ch > '9'){if (ch == '-') f = -1;ch = getchar();}
	while (ch >= '0' and ch<='9'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}
string check() {
	int a = read(),b = read(),d[105];
	string c[105];
	bool e[105];
	for(int i = 1;i <= b;i++) {
		cin>>c[i];
		d[i] = read(),e[i] = 1;
	}
	int m = b;
	while(m) {
		bool s = 1;
		for(int i = 0;i < a;i++) {
			bool k[4] = {0,0,0,0};
			for(int j = 1;j <=  b;j++) {
				if(e[j]) {
					if(c[j][i] == '0' and d[j] == 0) k[0] = 1;
					else if(c[j][i] == '0' and d[j] == 1) k[1] = 1;
					else if(c[j][i] == '1' and d[j] == 0) k[2] = 1;
					else k[3] = 1;
				}
			}
			if(k[0] xor k[1]) {
				for(int j = 1;j <= b;j++) {
					if(c[j][i] == '0' and e[j]) e[j] = 0,m--;
				}
				s = 0;
			}
			if(k[2] xor k[3]) {
				for(int j = 1;j <= b;j++) {
					if(c[j][i] == '1' and e[j]) e[j] = 0,m--;
				}
				s = 0;
			}
			if(!m) 	return "OK\n";
		}
		if(s) return "LIE\n";
	}
	
}
int main() {
	int t = read();
	while(t--) {
		cout<< check();
	} 
    return 0;
}

```


---

## 作者：chlchl (赞：4)

AK 的第一场正式比赛，当然要庆祝一下。

这是 USACO 2022 铜组 T3，难度适中，建议评黄，一定程度考验选手代码能力。

## 做法
模拟。

我们先把题意转化一下：
- 给你 $m$ 条 $0$ 和 $1$ 组成的命令和对应的结果。
- 要求找到一些某一位相同并且结果相同的命令（可以分先后）。
- 要求尽量使所有命令都满足第二步，如果无法全部满足就输出 ``No``。

等于说我要找到一些某一位相同且结果相同的数吧？

错！注意“**可以分先后**”。**有些已经被判断过的数，是不需要参加下面步骤的判断的**。

那我们就用一个 $tag$ 数组，表示每条命令是否已经被成功判断。每次我们就在未判断成功的命令中找“某一位相同并且结果相同的命令”。

当然，我们要重重复复地判断，因为当一些命令被成功判断之后，之前判断失败的一些命令可能会判断成功。

什么时候结束呢？
1. 全部判断成功，即判断成功个数 $=m$。
2. 一轮之后什么东西都没成功判断，证明无法满足全部命令，输出 ``No``。

然后就做完了，附赠一份代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N = 100 + 10;
int T, n, m, tag[N];
string ss[N];
char res[N];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i=1;i<=m;i++){
			tag[i] = 1;
			cin >> ss[i];
			cin >> res[i];
		}
		int cnt = 0;//判断成功的个数
		while(cnt < m){
			for(int i=0;i<n;i++){//每次遍历所有位
				int now = -1;
				bool ok = 1;
				for(int j=1;j<=m;j++){//枚举所有命令
					if(tag[j] && ss[j][i] == '0'){
					    //如果还没被判断而且这一位相等
						if(now == -1)
							now = res[j];
						if(res[j] != now)
							ok = 0;
					}
				}
				if(ok)//全部相等才算判断成功
					for(int j=1;j<=m;j++)
						if(ss[j][i] == '0')
							tag[j] = 0;
				now = -1, ok = 1;//记得重置
				for(int j=1;j<=m;j++){
					if(tag[j] && ss[j][i] == '1'){
					    //只不过分了 0,1 而已，略显冗长
						if(now == -1)
							now = res[j];
						if(res[j] != now)
							ok = 0;
					}
				}
				if(ok)//同理
					for(int j=1;j<=m;j++)
						if(ss[j][i] == '1')
							tag[j] = 0;
			}
			int now = 0;
			for(int i=1;i<=m;i++)
				now += (tag[i] == 0);//统计成功判断的个数
			if(now == cnt)
				break;//什么都没删掉
			cnt = now;//赋值
		}
		if(cnt == m)//全部删掉了
			printf("OK\n");
		else
			printf("LIE\n");
	}
	return 0;
}
```


---

## 作者：Demeanor_Roy (赞：3)

- [摘自此](https://www.luogu.com.cn/blog/261213wrh/usaco-2022-dec-bronze-ti-xie)

------------

首先需要发现三个性质：

- 如果一组提问能能使任意多个输入输出其正确输出，那率先完成这组提问显然不劣。

- 这样的提问一定是满足：所有当前未输出的输入这一位相同，并且它们的正确输出相同。

- 如果不存在以上提问，那接下来的提问将没有意义。

以上三点自证不难，请读者自行思考。

于是这道题思路就明确了，首先判断当前是否存在有效提问，有就一直提问下去，最后判断剩余的输入正确输出是否相同即可。考虑到每次有效提问至少减少一个输入，每次寻找有效提问时间复杂度为 $nm$，所以总时间复杂度为 $O(n^2m)$。

[代码](https://www.luogu.com.cn/paste/ncku491o)

---

## 作者：I_love_maths (赞：2)

### 题意

有 $M$ 个数，每个数有 $N$ 位，每一位上的数只会是 $0$ 或者 $1$。你要写一个 `if/else if/else` 程序，每一个语句都是：如果某一位上是 $0$ 或者 $1$，就输出一个 $0$ 或者 $1$。

### 做法

对于某一位，把 $M$ 个数（未删除的数）分成两组，分别为这一位上为 $0$ 或者 $1$。 判断每一组的输出是否相同，如果相同则证明：他们因为有一个共同特点，就是这一位上的数相同，且他们输出还相同，就可以写一句程序完成他们，所以完成后把这些数删除。

什么时候无解呢？就是这些数无法被全部删除的时候，用一个变量标记删除的数，如果全部删除退出循环。但是，如果说无解，会形成死循环，因为没有新删除的数，我们用一个 `bool` 变量记录一下是否有新删除的数，如果没有就退出循环，输出 `LIE`.

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
int num[105][105],ans[105];
bool del[105];
int main(){
	int T; scanf("%d",&T);
	for(int i = 1;i <= T;i++){
		int n,m; scanf("%d%d",&n,&m);
		for(int j = 1;j <= m;j++){
			for(int k = 1;k <= n;k++){
				char c; cin >> c;
				if(c == '0') num[j][k] = 0;
				else num[j][k] = 1;
			}
			scanf("%d",&ans[j]);
		}	
		memset(del,0,sizeof(del));
		int cnt = 0;
		bool flag = 1;
		while(cnt < m){
			int inc = 0;
			for(int j = 1;j <= n;j++){
				int num0 = -1,num1 = -1;
				bool flag0 = 1,flag1 = 1;
				for(int k = 1;k <= m;k++){
					if(del[k]) continue;
					if(num[k][j] == 0){
						if(num0 == -1) num0 = ans[k];
						else{
							if(num0 != ans[k]){
								flag0 = 0;
								break;
							}
						}
					}
				}
				for(int k = 1;k <= m;k++){
					if(del[k]) continue;
					if(num[k][j] == 1){
						if(num1 == -1) num1 = ans[k];
						else{
							if(num1 != ans[k]){
								flag1 = 0;
								break;
							}
						}
					}
				}
				if(flag0){
					for(int k = 1;k <= m;k++){
						if(num[k][j] == 0 && del[k] == 0){
							del[k] = 1;
							cnt++;
							inc++;
						}
					}
				}
				if(flag1){
					for(int k = 1;k <= m;k++){
						if(num[k][j] == 1 && del[k] == 0){
							del[k] = 1;
							cnt++;
							inc++;
						}
					}
				}
			}
			if(inc == 0){
				flag = 0;
				break;
			}
		}
		if(flag) printf("OK\n");
		else printf("LIE\n");
	}
	return 0;
}
```

---

## 作者：EXODUS (赞：1)


# Part 1：前言
好玩的模拟题。

# Part 2：正文
首先注意到，`else if/else` 是没有用的，因为每个函数必定跟返回值，返回后源程序结束，所以原代码一定等价为
```
if(...)return ...;
if(...)return ...;
if(...)return ...;
```
我们从上到下确定每个 `if` 括号内的值。设到当前的 `if` 时，**所有没有返回值的 $\texttt{01}$ 串构成的集合为 $S$**，则当前 `if` 可以填 `if(s[x]==y)return z;` 当且仅当 $\forall t\in S,t[x]=y,s.t.\ res_t=z$。接下来我们删去所有 $t$，并继续往下确定，直到 $s=\varnothing$ 或不存在这样一个语句 `if(s[x]==y)return z;`，分别对应有解和无解。
# Part 3：代码
```cpp
const int N=107;
int n,m;
char s[N][N];
int res[N],vis[N],qwq[N];

void Main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",s[i]+1);
		res[i]=read();
	}
	memset(vis,0,sizeof(vis));
	memset(qwq,0,sizeof(qwq));
	for(int i=1;i<=m;i++){
		char bit='2';int pos=0;
		for(int j=1;j<=n;j++){
			if(qwq[j])continue;
			int res0=-1,res1=-1;
			for(int k=1;k<=m;k++){
				if(vis[k])continue;
				if(s[k][j]=='0'){
					if(res0==-1)res0=res[k];
					else if(res0!=res[k]){
						res0=-2;
					}
				}else{
					if(res1==-1)res1=res[k];
					else if(res1!=res[k]){
						res1=-2;
					}
				}
				if(res0==-2&&res1==-2)goto there;
			}
			if(res0<0&&res1<0)goto there;
			if(res0==-2)bit='0',pos=j;
			else if(res1==-2)bit='1',pos=j;
			else bit='2',pos=j;
			break;
			there:;
		}
		if(!pos)return puts("LIE"),void();
		for(int j=1;j<=m;j++){
			if(s[j][pos]!=bit)vis[j]=1;
		}qwq[pos]=1;
		for(int j=1;j<=m;j++)if(!vis[j])goto here;
		return puts("OK"),void();
		here:;
	}
	return;
}
```

---

