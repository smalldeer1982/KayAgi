# [GCJ 2020 #1C] Overexcited Fan

## 题目描述

今天将是你终于能和猫咪 Peppurr 合影的日子！

Peppurr 即将在你的城市巡游。这座城市有无限多条南北走向和东西走向的无限长街道。任意两条垂直街道的交点称为**十字路口**。从任意一个十字路口出发，往四个方向（北、东、南、西）最近的十字路口都恰好相隔一个街区。

你已知 Peppurr 巡游的完整路径。你的目标是**在 Peppurr 到达某个巡游路线的十字路口的同时**，你也到达该路口，并且希望尽可能快地完成这件事。这就是你与 Peppurr 合影的方式！

Peppurr 的巡游起点位于你当前位置以东 $\mathbf{X}$ 个街区、以北 $\mathbf{Y}$ 个街区的十字路口。你和 Peppurr 每走完一个完整街区都需要恰好一分钟，且每分钟结束时必须到达一个十字路口；你们都不能走部分街区。

Peppurr 沿着预定路径移动。每分钟，你可以选择**静止不动**，或者选择向四个方向之一（北、东、南、西）移动一个街区。你和 Peppurr 都只沿街道行走。

如果你和 Peppurr **同时到达同一个十字路口**，你就能成功合影（包括巡游的最后一个路口）。但 Peppurr 在巡游结束后不再接受合影，因此即使只晚一分钟到达巡游终点，也无法合影。

你有可能和 Peppurr 合影吗？如果可能，最快需要多少分钟？

## 说明/提示

**样例解释**

在样例 #1 中，你可以向东走 4 个街区，在巡游的最后一个十字路口与 Peppurr 合影。

在样例 #2 中，巡游起点位于你以东 3 个街区。无论如何移动，你都无法与 Peppurr 合影。

在样例 #3 中，巡游路线距离你太远，无法在巡游结束前合影。

在样例 #4 中，Peppurr 会在 1 分钟后到达你的位置，因此你甚至不需要移动！注意只能在十字路口合影，如果你向北移动而 Peppurr 向南移动，虽然会在非路口处相遇，但无法在 0.5 分钟时合影。

在样例 #5 中，你可以先向北走 2 次，再向东走 2 次，然后静止不动，下一分钟即可合影。其他路径也可能在 5 分钟时合影，但无法更快。

以下两个样例不会出现在测试集 1 或 2 中，但可能出现在测试集 3：

```
2
3 2 SSSW
4 0 NESW
```

正确输出应为：

```
Case #1: 4
Case #2: 4
```

注意在样例 #1 中，你可以在起点以南 1 个街区、以东 2 个街区的十字路口与 Peppurr 合影。在样例 #2 中，Peppurr 沿小正方形移动，当其返回起点时即可合影。

**数据范围**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- $(\mathbf{X}, \mathbf{Y}) \neq (0, 0)$（巡游起点与你不在同一路口）。

**测试集 1（4 分，可见判定）**

- $0 \leqslant \mathbf{X} \leqslant 10$。
- $0 \leqslant \mathbf{Y} \leqslant 10$。
- $1 \leqslant \mathbf{M} \text{ 的长度} \leqslant 8$。
- $\mathbf{M}$ 仅包含 $\mathbf{N}$ 或 $\mathbf{S}$。

**测试集 2（6 分，可见判定）**

- $0 \leqslant \mathbf{X} \leqslant 1000$。
- $0 \leqslant \mathbf{Y} \leqslant 1000$。
- $1 \leqslant \mathbf{M} \text{ 的长度} \leqslant 1000$。
- $\mathbf{M}$ 仅包含 $\mathbf{N}$ 或 $\mathbf{S}$。

**测试集 3（12 分，可见判定）**

- $0 \leqslant \mathbf{X} \leqslant 1000$。
- $0 \leqslant \mathbf{Y} \leqslant 1000$。
- $1 \leqslant \mathbf{M} \text{ 的长度} \leqslant 1000$。
- $\mathbf{M}$ 可包含 $\mathbf{N}$、$\mathbf{E}$、$\mathbf{S}$ 或 $\mathbf{W}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4 4 SSSS
3 0 SNSS
2 10 NSNNSN
0 1 S
2 7 SSSSSSSS```

### 输出

```
Case #1: 4
Case #2: IMPOSSIBLE
Case #3: IMPOSSIBLE
Case #4: 1
Case #5: 5```

# 题解

## 作者：little_stickman (赞：2)

# P13059题解
## 主要题意
一个人距离你东 $x$ 步，北 $y$ 步。

你每分钟可以选择向东、南、西、北各走一步或不动。

另一个每分钟会依据输入走：

- 如输入 `S`，则会向南走一步；
- 如输入 `N`，则会向北走一步；
- 如输入 `E`，则会向东走一步；
- 如输入 `W`，则会向西走一步。

现在，给出那个人每分钟走的情况描述，求你可否在某一分钟和他处于同一坐标。如果可以，输出最少所需时间。

## 解题思路
首先，我们需要模拟每分钟对方和你东、北方向的距离。将这两个距离相加（如果出现**负数**，那么要将其**转为整数**）。

因为我们每分钟都可以走一次或者不走，所以如果现在的**时间**与对方**东、北两个距离之和相等**，就说明我们**一定可以通过一个操作序列走到对方那里**。

拿样例说明：

输入 `2 2 SS`。

第一分钟，对方所处的位置距离你东有 $2$ 步，北有 $2 - 1 = 1$ 步。两个距离相加是 $3$，时间是 $1$。你无论如何也无法走到对方的位置。

第二分钟，对方所处的位置距离你东有 $2$ 步，北有 $1 - 1 = 0$ 步。两个距离相加是 $2$，时间是 $2$。因为时间与两个距离相加相等，那么在第二分钟，你就可以与对方相处同一坐标（比如你两分钟分别向东走 $1$ 步）。

因此，最少相遇的时间是 $2$ 分钟。

## 上代码！ 
```cpp
#include <bits/stdc++.h>
using namespace std;

int x, y;
string str;

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	int T, l = 0;
	cin >> T;
	while(T --)
	{
		l ++;
		cin >> x >> y >> str;
		bool fg = 0;
		for(int i = 0;i < str.length();i ++)
		{
			if(str[i] == 'S')//向南 
				y --;
			if(str[i] == 'N')//向北 
				y ++;
			if(str[i] == 'E')//向东 
				x ++;
			if(str[i] == 'W')//向西 
				x --;
			if(abs(x) + abs(y) <= i + 1)
			{
				cout << "Case #" << l << ": " << i + 1 << endl;
				fg = 1;
				break;
			}
		}
		if(!fg)
			cout << "Case #" << l << ": IMPOSSIBLE" << endl;	
	}
	return 0;
} 
```

---

## 作者：lkjlkjlkj2012 (赞：1)

### 思路
首先我们可以发现重要的是我们自己和 Peppurr 的相对位置，所以可以以我们自己为原点，东为 x 轴正方向，北为 y 轴正方向建立坐标系，那么我们去一个地点的最短时间就是我们和那个地点的曼哈顿距离。我们直接枚举 Peppurr 巡游的每一地点，统计出我们到达这里的最短时间，看我们能否和 TA 同时到这里或者早到，可以直接输出答案；如果我们无法比 TA 提早或同时到达巡游的每一个地点，那么就不可能合影。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,x,y;
string m;
int main()
{
    cin>>t;
    for(int ti=1;ti<=t;ti++)
    {
        cin>>x>>y>>m;
        m=" "+m;
        cout<<"Case #"<<ti<<": ";
        bool flag=false;
        for(int i=0;i<m.length();i++)
        {
            char c=m[i];
            if(c=='N')
                y++;
            else if(c=='E')
                x++;
            else if(c=='S')
                y--;
            else if(c=='W')
                x--;
            int dis=abs(x)+abs(y);
            if(dis<=i)
            {
                cout<<i<<endl;
                flag=true;
                break;
            }
        }
        if(!flag)
            cout<<"IMPOSSIBLE"<<endl;
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P13059)

### 前言
这道题让我们计算如何在猫咪巡游过程中最快和它相遇。猫咪从出发点出发按固定路线移动，我们每分钟可以移动或不动，要在同一时间到达同一个路口才能合影。

### 思路
这道题的核心是要在猫咪移动过程中找到最早的相遇时间。我们可以这样想：每分钟先检查当前我们和猫咪的距离是否小于等于经过的时间（说明我们来得及走过去），如果满足就直接返回这个时间；如果不满足，就让猫咪继续移动一步，同时增加时间计数。最后如果猫咪走完全程还没相遇，就再检查一次终点位置。这样能保证找到最早相遇时间，如果全程都无法相遇就返回不可能。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    for(int tt=1; tt<=T; tt++) {
        int X, Y;
        string M;
        cin >> X >> Y >> M;
        int t = 0;
        bool f = false;
        for(char d : M) {
            if(abs(X) + abs(Y) <= t) {
                f = true;
                break;
            }
            if(d == 'N') Y++;
            else if(d == 'S') Y--;
            else if(d == 'E') X++;
            else if(d == 'W') X--;
            t++;
        }
        if(!f && abs(X) + abs(Y) <= t) 
            f = true;
        cout << "Case #" << tt << ": ";
        if(f) cout << t << endl;
        else cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
```

---

## 作者：_fallen_leaves_ (赞：0)

[P13059 [GCJ 2020 #1C] Overexcited Fan](https://www.luogu.com.cn/problem/P13059)

## 题意
有一个人在一个标轴上走，给定你的初始坐标，与这个人的行进方向，问你最少要走多少步才能遇到这个人。

## 思路
分别考虑每一个时间，算出这个人的坐标轴与你跟他差多少个格子，如果在 $i$ 时间内你能赶过去，说明你可以遇到这个人。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,tim=1;
signed main()
{
	cin>>t;
	while(t--)
	{
		int x,y;
		string s;
		cin>>x>>y>>s;
		int xx=0,yy=0,flag=0;
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='S') yy++;
			else if(s[i]=='N') yy--;
			else if(s[i]=='E') xx--;
			else if(s[i]=='W') xx++;
			if(abs(x-xx)+abs(y-yy)<=i+1)
			{
				flag=i+1;
				break;
			}
		}
		if(flag) cout<<"Case #"<<tim<<": "<<flag<<"\n";
		else cout<<"Case #"<<tim<<": IMPOSSIBLE\n"; 
		tim++;
	}
	return 0;
}

```

---

## 作者：yangdezuo (赞：0)

## 解析
### 题目大意
我们在 Peppurr 巡游的过程中，找到一个时间点，使得我们和 Peppurr 同时到达同一个十字路口。

所以，我们需要检查每一个时间点，看看是否有可能在这个时间点或之前相遇。

### 方法
1. ‌初始位置分析‌：Peppurr 的初始位置是 $(X, Y)$。我们的位置是 $(X, Y)$。我们需要在 Peppurr 移动的过程中，找到一个时间点 $t$，使得在 $t$ 步内，我们能够移动到 Peppurr 的位置。


2. ‌动态跟踪 Peppurr 的位置‌：对于每一个时间点，计算 Peppurr 的位置。初始位置是 $(X, Y)$，之后每经过一分钟，Peppurr 按照字符串中的方向移动一步。


3. 检查相遇条件‌：对于每一个时间点 $t$，Peppurr 的位置是 $(x_t, y_t)$。我们需要判断是否可以在 $t$ 步内从 $(0,0)$ 走到 $(x_t, y_t)$。具体来说，我们需要满足曼哈顿距离条件：$|x_t| + |y_t| \le t$。如果满足，则可以在 $t$ 分钟内到达该位置。

4. ‌寻找最小时间‌ $t$：遍历所有时间点，找到满足条件的最小值。如果遍历完所有时间点都没有找到，则返回 ```IMPOSSIBLE```。


## 参考代码

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
int t,x,y,dis,ans;
string s; 
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>x>>y>>s;
		ans=-1; 
		for(int i=0;i<=s.size();i++){//‌遍历时间点‌
			dis=abs(x)+abs(y);//求曼哈顿距离
			if(dis<=i){
				ans=i;
				break;
			}
			if(i<s.size()){
				if(s[i]=='S') y--;
				else if(s[i]=='N') y++;
				else if(s[i]=='E') x++;
				else x--;
			}
		}
		if(ans!=-1) cout<<"Case #"<<o<<": "<<ans<<'\n';
		else cout<<"Case #"<<o<<": IMPOSSIBLE\n";
	}
}
/*

*/
```

---

