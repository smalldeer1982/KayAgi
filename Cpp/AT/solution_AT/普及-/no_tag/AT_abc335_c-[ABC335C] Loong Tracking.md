# [ABC335C] Loong Tracking

## 题目描述

## 题意翻译
Takahashi 创造了一款游戏，游戏中玩家可以在坐标平面上控制一条“龙”。

一条“龙”包含 $N$ 个编号为 $1$ 到 $N$ 的部位，而部位 $1$ 被叫做“头”。

初始状态下，第 $i$ 个部位位于坐标（$i$ , $0$）。下面你需要回答 $Q$ 个询问。

- `1 C`：向方向 $C$ 将编号为 $1$ 的头移动一个单位长度。$C$ 可能是 `R`、`L`、`U`、`D` 中的一个字母，分别代表 $x$ 轴正方向、$x$ 轴负方向、$y$ 轴正方向、$y$ 轴负方向。其他的所有部位都会跟随上一个部位移动。形式化地，编号为 $i$ 的部位会移动到编号为 $i-1$ 的部位先前所在的位置。
- `2 p`：输出部位 $p$ 的坐标。

你需要对所有询问 `2` 做出回答。

## 样例 #1

### 输入

```
5 9
2 3
1 U
2 3
1 R
1 D
2 3
1 L
2 1
2 5```

### 输出

```
3 0
2 0
1 1
1 0
1 0```

# 题解

## 作者：wsx248 (赞：3)

由于 $1$ 点动了以后剩下所有点都会动，不难发现其实只需要关注 $1$ 点所处位置即可，其他点本质上是 $1$ 点的镜像。

想象这样一个场景：$1$ 点从位置 $n$ 开始向左走，走到位置 $1$ 时停止；此时，$1$ 点所经过的路径等价于初始状态。

认识到这一点后，问题变得非常简单：每次的 $2$ 操作，实际上就是向前推 $p$ 个时刻后 $1$ 点所处位置即可。

记 $ops$ 表示操作了多少次，$x_i,y_i$ 分别表示 $1$ 点在当前这次操作后所处的横、纵坐标。每次询问位置 $p$ 的坐标，直接输出 $x_{ops-p+1}, y_{ops-p+1}$ 即可。

```cpp
#include<iostream>
using namespace std;
const int N = 1e6+5;
int n, q;
int ops;
int x[N*2], y[N*2];

int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		x[i] = n-i+1, y[i] = 0;
	ops = n;

	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			char s;
			cin>>s;
			ops++;
			if(s=='U')
				x[ops] = x[ops-1], y[ops] = y[ops-1] + 1;
			else if(s=='D')
				x[ops] = x[ops-1], y[ops] = y[ops-1] - 1;
			else if(s=='L')
				x[ops] = x[ops-1] - 1, y[ops] = y[ops-1];
			else
				x[ops] = x[ops-1] + 1, y[ops] = y[ops-1];
		}
		else
		{
			int p;
			cin>>p;
			cout<<x[ops-p+1]<<" "<<y[ops-p+1]<<endl;
		}
	}
	return 0;
}
```

---

## 作者：XXh0919 (赞：3)

这题其实很简单。我们可以用一个双向队列来存储当前每个零件的位置，若方向是 $\texttt{L}$，就将 $x$ 坐标减 $1$，如果是 $\texttt{R}$，相对的，就将 $x$ 坐标加 $1$，$y$ 坐标同理。若方向是 $\texttt{D}$，就将 $y$ 坐标减 $1$，如果是 $\texttt{U}$，相对的，就将 $y$ 坐标加 $1$。接着查询就很简单了，直接输出该点的 $x$ 坐标和 $y$ 坐标就行了。

### 具体看代码：


```cpp
#include<bits/stdc++.h>
#define first x
#define second y
#define int long long
using namespace std;
const int N=3e5+15;

int n,q;
deque<pair<int,int>>dq;

signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;++i)
	   dq.emplace_back(i,0);
	while(q--){
		int op;
		scanf("%lld ",&op);
		if(op==1){
			dq.push_front(dq.front());
			dq.pop_back();
			char cc;
			scanf("%c",&cc);
			if(cc=='L')dq.front().x--;
			if(cc=='R')dq.front().x++;	
			if(cc=='U')dq.front().y++;
			if(cc=='D')dq.front().y--;
		}else{
			int k;
			scanf("%lld",&k);
			printf("%lld %lld\n",dq[k-1].x,dq[k-1].y);
		}
	}
    return 0;
}
```


---

## 作者：2020qlszd (赞：2)

### 题目大意

有一条长度为 $n$ 的龙，可以理解为这条龙有 $n$ 节，我们要使用字符控制龙头移动，龙头移动后，后一节到达前一节的位置，以此类推。

### 思路

直接模拟肯定会超时。但观察发现，移动主要分为两种情况。第一种是还没有影响到目前我们查询的节，就往前就行。第二种是影响到了我们目前查询的节，我们可以看他与龙头相差了多少次操作，撤销就行了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,x,y,ans=0;
int cd[1000005],kd[1000005];
long long cc=1,kk=0;
char c;
int main() {
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		scanf("%lld",&x);
		if(x==1){
			cin>>c;
			ans++;
			long long pd=0,jf=0;
			if(c=='U'){ //预处理 方便撤销和后续加减
				cd[ans]=0;
				kd[ans]=1;
			}
			if(c=='R'){
				cd[ans]=1;
				kd[ans]=0;
			}
			if(c=='D'){
				cd[ans]=0;
				kd[ans]=-1;
			}
			if(c=='L'){
				cd[ans]=-1;
				kd[ans]=0;
			}
			cc+=cd[ans]; //预处理 方便撤销
			kk+=kd[ans];
		}
		else if(x==2){
			cin>>y;
			if(y>ans){ //第一种情况 
				cout<<y-ans<<" "<<0<<endl;
			}
			else{ //第二种情况 
				long long ccc=cc,kkk=kk,js=y-1;
				for(int j=0;j<js;j++){
					ccc-=cd[ans-j];
					kkk-=kd[ans-j];
				}
				cout<<ccc<<" "<<kkk<<endl; 
			}
		}
	}
	return 0;
}

```


---

## 作者：xxboyxx (赞：1)

### 题意

有一条长度为 $n$ 的龙，龙头在 $(1,0)$ 的位置，龙身依次为 $(2,0)(3,0)(4,0)\cdots(n,0)$，每次给定一个移动操作或一个查询操作，每次移动的是头部，身体也会跟着移动，龙的某个部分可能会重叠。

### 思路

用模拟算法会超时，每移动一次就需要更新整条龙。

再观察一下龙每个部分的移动，可以发现龙身经过的点全部都是龙头经过的点，那么，只要模拟一遍龙头的走向，就可以得知任意时刻龙的某个部分的坐标了。

相当于使用离线算法，先保存所有的查询操作与其时间，在按照查询的位置与时间推算出位置。

### 注意

因为身体是从左到右的，但是龙应该是从后往前的，所以这里应该逆序存储，才能使得推算位置时好计算。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node//身体的坐标 
{
	int x,y;
};
int n,q,t=0,tx=0;
int x=0,y=1;
int a[2000005];
int b[2000005];
node d[2000005];
int main()
{
	cin>>n>>q;
	for (int i=1;i<=n;i++)
	{
		d[n-i+1].x=0;
		d[n-i+1].y=i;//逆序存储 
	}
	for (int i=1;i<=q;i++)
	{
		int o,k;
		char c;
		cin>>o;
		if (o==1)
		{
			t++;
			cin>>c;
			if (c=='U')
				x++;
			else if (c=='R')
				y++;
			else if (c=='D')
				x--;
			else if (c=='L')
				y--;
			d[t+n].x=x;//模拟运动 
			d[t+n].y=y;//离线存储 
		}
		else
		{
			tx++;
			cin>>k;
			a[tx]=k;
			b[tx]=t;//记录时间 
		}
	}
	for (int i=1;i<=tx;i++)
		cout<<d[n-a[i]+1+b[i]].y<<' '<<d[n-a[i]+1+b[i]].x<<'\n';//身体位置（逆序）+时间 
	return 0;
}
```


---

## 作者：_shine_ (赞：1)

因为龙的坐标在进行实时更新，所以每个的状态自然不能动态进行处理。

其实模拟样例不难发现，龙的每第 $u$ 段其实对应的是其上一段在上一次移动操作前的位置，一直向上推导即可发现龙的第 $u$ 段是龙开头一段在前 $u-1$ 的状态，而开头操作的偏移量其实是可以记录下来的，所以记录每次操作的时间和状态并且推出当前的状态即可。

---

## 作者：xz001 (赞：1)

- 首先我们转化一下，龙移动一下就相当于其增加了一个头，头为原有的龙头按输入移动后的位置，然后删除尾部。
- 从头部插入和尾部删除可以用 ```deque``` 来维护。

- 代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, q;

deque <pair <int, int> > d;

signed main() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++ i) d.push_back({i, 0});
    while (q -- ) {
    	int op;
    	cin >> op;
    	if (op == 1) {
    		string s;
    		cin >> s;
    		int x = d.front().first, y = d.front().second;
    		if (s == "R") ++ x;
    		if (s == "L") -- x;
    		if (s == "U") ++ y;
    		if (s == "D") -- y;
    		d.push_front({x, y});
    		d.pop_back();
		} else {
			int p;
			cin >> p;
			cout << d[p - 1].first << ' ' << d[p - 1].second << endl;
		}
	}
    return 0;
}


```

---

## 作者：Saint_ying_xtf (赞：1)


[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

像是一个贪吃蛇，然后每次向某个地方走动，然后后一个点会来到前一个点的位置。我们可以直接开一个 vector 来存储坐标的变化（做一个第 $i$ 时刻的前缀和）实际上的作用，就是在第 $i$ 时刻坐标是在哪。对于时间为 $0$ 的时候，可以看作第一个点是 $n-1$ 时间的位置，最后一个点是 $0$ 时间的位置。然后每一次询问只需要查询数组中时间减去第几个点的下标，就是答案。

[link](https://atcoder.jp/contests/abc335/submissions/49090914)。

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc335_c)

#### 思路

读题可以知道每次最多移动一个点，其他点都到前一个点的位置，所以我们肯定是要存这 $n$ 个点的位置的，每次执行一个移动操作，就让指针 $cnt+1$，存这个新位置，每个数 $i$ 的位置也就是 $cnt - i + 1$，每次 $cnt+1$ 就等同于让每个输的位置向后移动一位，然后模拟即可。

#### 注意: atcoder 有些编译器不支持函数里 `++cnt`，得放出来，不然就和我一样等着罚时吧。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,op,qw,t[3000010],t1[3000010],cnt;
char cz;
int main()
{
	scanf("%d%d",&n,&q);
	for(int i = n;i >= 1;i--) t[++cnt] = i;//初值 
	while(q--)
	{
		scanf("%d",&op); 
		if(op == 1)
		{
			cin >> cz;
			cnt++;
			if(cz == 'L') t[cnt] = t[cnt - 1] - 1,t1[cnt] = t1[cnt - 1];
			else if(cz == 'R') t[cnt] = t[cnt - 1] + 1,t1[cnt] = t1[cnt - 1];
			else if(cz == 'U') t[cnt] = t[cnt - 1],t1[cnt] = t1[cnt - 1] + 1;
			else t[cnt] = t[cnt - 1],t1[cnt] = t1[cnt - 1] - 1;
		}
		else 
		{
			scanf("%d",&qw);
			printf("%d %d\n",t[cnt - qw + 1],t1[cnt - qw + 1]);
		}
	}
    return 0;
}

```


---

## 作者：indream (赞：0)

## \[ABC335C] Loong Tracking 题解
[洛谷](https://www.luogu.com.cn/problem/AT_abc335_c) | [AtCoder](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc335_c)
### 思路
$O(n^2)$ 暴力显然不可行。

我们发现，所有部分只可能在 $(i,0)$ 或头曾经到过的地方。

实现可以用 `vector`，存头每次动后的坐标。记得分类讨论该部分是否到过 $(1,0)$。

时间复杂度 $O(n)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q,tmp,b,x=1,y=0,cnt=0;
char a;
vector<pair<int,int>> head;//头的位置

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    head.push_back({1,0});
    cin>>n>>q;
    for(int i=1;i<=q;++i){
        cin>>tmp;
        if(tmp==1){
            cin>>a;
            switch(a){
                case 'R':
                    ++x;
                    break;
                case 'L':
                    --x;
                    break;
                case 'U':
                    ++y;
                    break;
                case 'D':
                    --y;
                    break;
            }
            head.push_back({x,y});
            //cerr<<x<<' '<<y<<'\n';
            ++cnt;//移动次数
        }else{
            cin>>b;
            if(cnt<b)
                cout<<b-cnt<<' '<<"0\n";//未到(1,0)
            else
                cout<<head[cnt-b+1].first<<' '<<head[cnt-b+1].second<<'\n';//头曾经的位置
        }
    }
    return 0;
}
```

---

