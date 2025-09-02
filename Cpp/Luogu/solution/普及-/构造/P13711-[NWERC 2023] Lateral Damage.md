# [NWERC 2023] Lateral Damage

## 题目描述

你正在一片辽阔的海洋中玩“战舰”游戏，使用的是大型战舰。
更具体地说，有一个最大为 $100\times 100$ 的正方形网格，在其中最多有 $10$ 艘“战舰”游戏中最大的舰种——航空母舰。每艘航空母舰长度为 $5$ 个格子，可以水平或垂直放置。
这些舰船不会重叠，但允许彼此相邻。参见图 L.1 示例。

![](https://upload.wikimedia.org/wikipedia/commons/a/ac/Hra_n%C3%A1mo%C5%99n%C3%AD_bitva_%281%29.jpg)

:::align{center}
原始的“战舰”游戏，在升级为 $100\times 100$ 网格之前。CC BY-NC 3.0，作者 Pavel Ševela，来源 [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Hra_n%C3%A1mo%C5%99n%C3%AD_bitva_(1).jpg)
:::

不幸的是，你的对手似乎会随心所欲地修改规则。
看起来他们并不总是在你开始射击前就确定舰船的位置。
你对他们的作弊行为并不感到惊讶，决定无论如何都要赢得这场游戏。

![](https://cdn.luogu.com.cn/upload/image_hosting/0lfdcwfa.png)

:::align{center}
图 L.1：示例交互 1，在前四次射击后。
:::

你的目标是在最多 $2500$ 次射击内找出并击沉所有对手的航空母舰，也就是说，你必须击中所有舰船的每一个格子（每艘船有 $5$ 个格子）。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 2

miss

hit

miss

hit

hit

hit

hit

sunk

miss

miss

hit

miss

hit

hit

sunk```

### 输出

```

6 1

6 3

7 3

5 3

4 3

3 3

2 3

1 3

6 7

6 7

6 2

6 2

6 4

6 5

6 6```

# 题解

## 作者：OIratrace (赞：2)

## 题意

给出 $k$ 个战舰，用炸弹轰炸一个 $n \times n$ 的网格，要求在 $2500$ 次轰炸内炸完所有的战舰。

## 思路

1. 直接枚举搜索。这显然是不行的，最坏需要轰炸 $10000$ 次。
2. 随机数枚举搜索。这似乎也没有什么区别。
3. 正解：我们可以根据战舰的特性来解决这道题目。

战舰是直的且长度为 $5$。那么我们可以贪心的想，如果每隔 $5$ 个格子就轰炸一个，那么这样可以找出每个战舰的一部分。

然后再从每个找到的格子开始搜索，这样就能找到所有战舰了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int ax[]={0,-1,0,0,1},ay[]={0,0,-1,1,0};
int n,k,vis[105][105];
string s;
void dfs(int x,int y){
	if (k==0)exit(0);
	if (x<1||x>n||y<1||y>n)return ;
	vis[x][y]=1;
	cout<<x<<' '<<y<<endl;
	cin>>s;
	if (s=="sunk")k--;
	if (k==0)exit(0);
	if(s!="hit")return ;
	for (int i=1;i<=4;i++){
		int tx=x+ax[i],ty=y+ay[i];
		if (tx<1||tx>n||ty<1||ty>n)continue;
		if (vis[tx][ty])continue;
		dfs(tx,ty);
	}
}
signed main(){
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		for (int j=(i-1)%5+1;j<=n;j+=5){
			if (vis[i][j]==0){
				dfs(i,j);
			}
		}
	}
	return 0;
}
```

---

## 作者：lvweisi (赞：1)

### 题目大意：
给定一个 $n$ 行 $n$ 列的地图，放置着 $k$ 艘长度为 $5$ 的军舰，让你在询问次数不超过 $2500$ 的情况下找出所有的军舰。

### 解题思路：
当我第一次看到题目时，就注意到军舰的长度只能是 $5$，于是就联想到了五子棋的一个非常[阴间](https://picx.zhimg.com/80/8a486e3c689f6964e43bfcd41d93db9e_1440w.webp?source=1def8aca)的下法，同样可以运用到此题目上，只需要枚举出所有的下法的位置，如果出现命中反馈，那么就上下左右各延伸 $4$ 各位置进行询问，统计 `sunk` 出现的次数即可。

### 代码如下：
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int mp[105][105];
int lj;
int xy[4]={-2,-1,1,2};
int yy[4]={-1,2,-2,1};
int qd[5]={3,1,4,2,5};
char ans[100];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)for(int j=qd[i%5];j<=n;j+=5)mp[i][j]=1;//递推每一个点
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j]!=1)continue;
			cout<<i<<" "<<j<<'\n';
			cin>>ans;
			mp[i][j]=0;
			if(ans[0]=='m')continue;
			if(ans[0]=='s')lj++;
			if(lj==k)return 0;
			for(int kk=1;kk<=4;kk++){
				if(j+kk<=n){
					cout<<i<<" "<<j+kk<<'\n';
					mp[i][j+kk]=0;
					cin>>ans;
					if(ans[0]=='s')lj++;
				}
				if(lj==k)return 0;
				if(j-kk>=1){
					cout<<i<<" "<<j-kk<<'\n';
					mp[i][j-kk]=0;
					cin>>ans;
					if(ans[0]=='s')lj++;
				}
				if(lj==k)return 0;
				if(i+kk<=n){
					cout<<i+kk<<" "<<j<<'\n';
					mp[i+kk][j]=0;
					cin>>ans;
					if(ans[0]=='s')lj++;
				}
				if(lj==k)return 0;
				if(i-kk>=1){
					cout<<i-kk<<" "<<j<<'\n';
					mp[i-kk][j]=0;
					cin>>ans;
					if(ans[0]=='s')lj++;
				}
				if(lj==k)return 0;//代码有点冗余，希望能看懂
			}
		}
	}
	return 0;
}
```

---

## 作者：kill_wcz (赞：0)

失去，是为了更好的未来。
### 题解：P13711 [NWERC 2023] Lateral Damage
---


#### 如果没有做过交互题的新人直接看过来！
这是作者第一题交互题，所以也是从新人的角度来看这种题目。

第一，交互题是什么？

交互题是一种特殊的题目类型，其核心特点是程序在运行过程中进行实时数据交换，而非一次性读取所有输入后再输出结果。  
就是你的程序要边输入，边输出！

第二，交互题有什么特殊性质？

1.程序通过多次‌输入输出轮询‌逐步获取信息并给出反馈。  
2.多数题目严格限制程序与评测系统的交互次数。

#### 思路：
这道题是找出所有船，而船的大小是 $1\times5$，所以先预处理一下，把炮弹斜着打，炮弹相邻为 $4$，这样就不会完全击沉船，而且能攻击到所有的船，再将击中的坐标记录下来。  
再攻击坐标点上下左右所有距离坐标 $\le4$ 的点，便可得出答案。

所以我们得出答案。  
作者代码很像广搜代码，适合新人观看。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int s[5]={5,4,3,2,1};
int vis[105][105];
queue<int> qx,qy;
int cnt = 0;
signed main() {
	cin >> n >> k;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		int st = s[i % 5];
		for (int j = st; j <= n; j += 5) {
			if (vis[i][j]==1) continue;
			vis[i][j] = 1;
			cout << i << " " << j << endl;
			string res;
			cin >> res;
			if (res == "hit"){
				qx.push(i);
				qy.push(j);
			}
		}
	}
	while (!qx.empty() && cnt < k) {
		int x = qx.front();
		int y = qy.front();
		qx.pop();
		qy.pop();
		for (int i = x - 4; i <= x + 4; i++) {
			if(i<1||i>n)continue;//防止越界
			if (vis[i][y]==0) {
				vis[i][y] = 1;
				cout << i << " " << y << endl;
				string res;
				cin >> res;
				if (res == "sunk") {
					cnt++;
					if (cnt == k) return 0;
				}
				else if (res == "hit"){
					qx.push(i);
					qy.push(y);
				}
			}
		}
		for (int j = y - 4; j <= y + 4; j++) {
			if(j<1||j>n)continue;//防止越界
			if (vis[x][j]==0) {
				vis[x][j] = 1;
				cout << x << " " << j << endl;
				string res;
				cin >> res;
				if (res == "sunk") {
					cnt++;
					if (cnt == k) return 0;
				}
				else if (res == "hit") {
					qx.push(x);
					qy.push(j);
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：LotleTos (赞：0)

要想打沉所有军舰，要先大致确定船的位置。
就需要有一个布局方式，可以打中（不是打沉）所有军舰，并不超过限制。

于是我就想出了这样的方式：
![](https://cdn.luogu.com.cn/upload/image_hosting/fpfzsn47.png)
也就是一些斜线，每根斜线横竖的距离都是相差 $5$ 格，所以每个格子上下左右 $5$ 格如果不出界的话，一定每个方向 $5$ 格内都会有一个格子被打中，就能检测出所有军舰的大概位置了。

构造出斜线，把这些格子都打一遍，如果打某个格子时击中了，那么就把这个格子上下左右 $5$ 格也打一遍，就能击沉这个格子所在的军舰了。

斜线的格子总数约为 $n\times n \div 5$，最多约 $2000$ 个。一个十字大约 $20$ 格，每个军舰要扫一个十字，最多扫 $200$ 个，加起来大约要扫 $2200$ 格，足以通过。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	int sum=0;
	for(int i=1;i<=n;i++){
		for(int j=(i%5==0?5:i%5);j<=n;j+=5){
			cout<<i<<" "<<j<<endl;
			string s;
			cin>>s;
			if(s=="hit"){
				for(int x=-5;x<=5;x++){
					if(i+x>=1&&i+x<=n){
						cout<<i+x<<" "<<j<<endl;
						string ss;
						cin>>ss;
						if(ss=="sunk"){
							sum++;
							if(sum==k){
								return 0; 
							}
							break;
						}
					}
					if(j+x>=1&&j+x<=n){
						cout<<i<<" "<<j+x<<endl;
						string ss;
						cin>>ss;
						if(ss=="sunk"){
							sum++;
							if(sum==k){
								return 0; 
							}
							break;
						}
					}
				}
			}
			if(s=="sunk"){
				sum++;
				if(sum==k){
					return 0; 
				}
			}
		}
	}
	
}


```

---

## 作者：WuMin4 (赞：0)

## 题意

交互题。在 $100\times 100$ 的网格上摆放了不超过 $10$ 个互不重叠的 $1\times 5$ 的航空母舰。你每次可以选择一个格子进行轰炸，交互库会返回击空，击中，击落中的一个。你需要在 $2500$ 次操作内击落所有航空母舰。

## 思路

考虑一种十分经典的构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/8igece4h.png)

相信很多人在玩五子棋时也听说过这个~~阵法~~。由于每行每列的空白段长度都为 $4$，所以按照这种方式轰炸，每个 $1\times 5$ 的航空母舰都一定会且只会被炸到一次。

![](https://cdn.luogu.com.cn/upload/image_hosting/o6b0e7fu.png)

如果你觉得这样构造还是太吃操作了，直接几条斜线过去也是可以的。

找到一个位置后，剩下的就简单了，直接向四周拓展即可。总次数最大为 $2000+17\times 10=2170$，小于 $2500$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,k,s[5]={2,4,1,3,5};
vector<pair<int,int>> tar,st;
bool vis[105][105];
string o;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		for(int j=s[i%5];j<=n;j+=5){
			vis[i][j]=true;
			cout<<i<<" "<<j<<endl;
			cin>>o;
			if(o=="hit") tar.push_back({i,j});
		}
	}
	for(pair<int,int> v:tar){
		for(int i=max(1,v.first-4);i<=min(n,v.first+4);i++){
			if(!vis[i][v.second])
				vis[i][v.second]=true,st.push_back({i,v.second});
		}
		for(int j=max(1,v.second-4);j<=min(n,v.second+4);j++){
			if(!vis[v.first][j])
				vis[v.first][j]=true,st.push_back({v.first,j});
		}
	}
	int tot=0;
	for(pair<int,int> v:st){
		cout<<v.first<<" "<<v.second<<endl;
		cin>>o;
		if(o=="sunk") tot++;
		if(tot==k) break;
	}
	return 0;
}
```

---

