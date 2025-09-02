# Ingenuity-2

## 题目描述

Let's imagine the surface of Mars as an infinite coordinate plane. Initially, the rover Perseverance-2 and the helicopter Ingenuity-2 are located at the point with coordinates $ (0, 0) $ . A set of instructions $ s $ consisting of $ n $ instructions of the following types was specially developed for them:

- N: move one meter north (from point $ (x, y) $ to $ (x, y + 1) $ );
- S: move one meter south (from point $ (x, y) $ to $ (x, y - 1) $ );
- E: move one meter east (from point $ (x, y) $ to $ (x + 1, y) $ );
- W: move one meter west (from point $ (x, y) $ to $ (x - 1, y) $ ).

Each instruction must be executed either by the rover or by the helicopter. Moreover, each device must execute at least one instruction. Your task is to distribute the instructions in such a way that after executing all $ n $ instructions, the helicopter and the rover end up at the same point, or determine that this is impossible.

## 说明/提示

Let's consider the first example: the string $ S = \texttt{NENSNE} $ . One of the possible solutions, shown in the figure below, is $ p = \texttt{RRHRRH} $ , using which both the rover and the helicopter will end up one meter north and one meter east.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974D/6e8d0f788b954d2ceff54878d55afda06efd52c8.png)For WWW, the solution is impossible.

## 样例 #1

### 输入

```
10
6
NENSNE
3
WWW
6
NESSWS
2
SN
2
WE
4
SSNN
4
WESN
2
SS
4
EWNN
4
WEWE```

### 输出

```
RRHRRH
NO
HRRHRH
NO
NO
RHRH
RRHH
RH
RRRH
RRHH```

# 题解

## 作者：Weekoder (赞：7)

### 思路

说实话，和 [P2689 东南西北](https://www.luogu.com.cn/problem/P2689) 的思路很想，直接贪心即可。遍历所有的指令，考虑将其分配给 `R` 或 `H`：判断上下左右关系，贪心。假设当前指令为 `E`（向右），而 `R` 在 `H` 的左边，就移动 `R`，其他情况以此类推。唯一值得注意的是，`R` 和 `H` 都应被分配，在横纵坐标相等的情况下，应优先考虑没有出现过的指令，具体实现见代码。

代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n, X1, Y1, X2, Y2;

string s, ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T --) {
	    cin >> n >> s;
	    s = '#' + s;
	    ans = "";
	    bool f1 = 0, f2 = 0;
	    X1 = Y1 = X2 = Y2 = 0;
	    for (int i = 1; i <= n; i++) {
	        //cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << "\n";
	        if (s[i] == 'N') {
	            if (Y1 > Y2 || Y1 == Y2 && !f2)
	                Y2++, ans += 'H', f2 = 1;
                else
                    Y1++, ans += 'R', f1 = 1; 
	        } 
	        else if (s[i] == 'S') {
	            if (Y1 > Y2 || Y1 == Y2 && !f1)
	                Y1--, ans += 'R', f1 = 1;
                else
                    Y2--, ans += 'H', f2 = 1; 
	        } 
	        else if (s[i] == 'E') {
	            if (X1 > X2 || X1 == X2 && !f2)
	                X2++, ans += 'H', f2 = 1;
                else
                    X1++, ans += 'R', f1 = 1; 
	        } 
	        else {
	            if (X1 > X2 || X1 == X2 && !f1)
	                X1--, ans += 'R', f1 = 1;
                else
                    X2--, ans += 'H', f2 = 1; 
	        } 
	    }
	    //cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << "\n";
	    if (X1 != X2 || Y1 != Y2 || !f1 || !f2)
	       cout << "NO\n";
	    else
	       cout << ans << "\n"; 
	}
	return 0;
}
```

---

## 作者：Eddie08012025 (赞：6)

## 思路
这道题还是比较简单的，可以发现要让两个机器人的位置相同，可以让两个机器人走同样的步骤，也就是所有 N,S,E,W 平均分配给两个机器人。

当然，有可能 N,S,E,W 的个数是奇数个，会剩下一个，这些剩下的可以安排给机器人 Helicopter ，但前提是这些可以相互抵消，比如 N 与 S，E 与 W 可以互相抵消。

这时如果剩下的 N 与 S 数量不相等或剩下的 E 与 W 数量不相等，也就是无法互相抵消，这时就输出 `NO` 代表没有方案。

但是，还有很重要的一点：两个机器人都得分配到至少一个指令，所以当 N,S,E,W 的个数都 $\le 1$ 时，需要特判。因为上面我们会把所有剩下的 N,S,E,W 都给 Helicopter。

如果 N,S,E,W 的个数分别是 $1,1,0,0$ 或 $0,0,1,1$，虽然可以互相抵消，但是不能让两个机器人都分配到指令，所以也要输出 `NO`。

但假如 N,S,E,W 都有 $1$ 个，那么就把 N,S 分配给 Rower，E,W 分配给 Helicopter ，也可以满足条件。

分析完毕，下面给出 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,z[200];//z数组存储NSEW的个数 
string a;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>a;
		z['N']=z['S']=z['E']=z['W']=0;//多组样例，初始化 
		for(int i=0;i<n;i++){//统计个数 
			z[a[i]]++;
		}//上面讲述的不可行的方案 
		if(z['N']==1&&z['S']==1&&z['E']==0&&z['W']==0||z['N']==0&&z['S']==0&&z['E']==1&&z['W']==1||z['N']%2!=z['S']%2||z['E']%2!=z['W']%2){
			cout<<"NO\n";
			continue;
		}//特判 NSEW的个数都为0时 
		if(z['N']==1&&z['S']==1&&z['E']==1&&z['W']==1){
			for(int i=0;i<n;i++){
				if(a[i]=='N'||a[i]=='S')cout<<'R';//NS给Rower 
				else cout<<'H';//WE给Helicopter 
			}cout<<"\n";
			continue;
		}z['N']/=2;//这些是安排给Rower的NSEW个数，因为int类型会自动舍尾，所以如果有剩下的就自动安排给Helicopter了 
		z['S']/=2;
		z['E']/=2;
		z['W']/=2;
		for(int i=0;i<n;i++){//输出 
			if(z[a[i]]){
				cout<<"R";
				z[a[i]]--;
			}else{
				cout<<"H";
			}
		}cout<<"\n";
	}
	return 0;
}
```
**感谢观看！！！**

---

## 作者：gu51yo (赞：5)

模拟是不可能模拟的，$30$ 行代码 AC 。

逻辑也很简单，$x$ 轴和 $y$ 轴的操作互相独立，如果某个轴的总量是奇数，则不可能。或者只在一个轴上的两个方向执行了一次。也不可能。

如果可以，则每个机器轮次执行。可以利用操作数的奇偶性来实现。

为了完成题目要求，我们使某一轴上的操作让 $H$ 先，另一个轴上的操作 $R$ 先即可。也可以利用奇偶性实现。

详细见代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, x, y;
string s;

void solve () {
    cin >> n >> s;
    vector<int> a(n), b(5);
    for (int i=0; i<n; i++) {
        a[i]="NESW"s.find(s[i]);	//操作转换为整数
        b[a[i]]++;
    }

    x=b[1]-b[3], y=b[0]-b[2];
    if (x%2 || y%2 || (x==2 && y==2 && n<3)) {	//不可能
        cout << "NO\n";
        return;
    }

    for (int i=0; i<n; i++) {	//输出
        cout << "HR"[(a[i]+b[a[i]]++)%2];	//奇偶
    } cout << '\n';
}

int main () {
    cin >> t;
    while (t--) solve();
    return 0;
}
```
感谢多次审核

---

## 作者：Louis_lxy (赞：3)

一道模拟水题。

如果没有限制每一个都要使用，显然我们有一个结论，我们让每一步都使他们距离更近一定更好。加上限制后，如果给任意一个人执行减少的答案都一样，即都无法减少，那么我们就让还没执行任何命令的那个执行命令，因为此时任何人执行并不会有任何区别。

AC 记录：https://www.luogu.com.cn/problem/CF1974D

---

## 作者：lihongqian__int128 (赞：3)

# CF1974D Ingenuity-2题解
大模拟。

要求：东西向移动可分配、南北向移动可分配。

坑点：每个机器人都要移动。

其他请看代码注释。

```cpp
#include <bits/stdc++.h>
#define o1 cout << 'R'
#define o2 cout << 'H'
using namespace std ;
int t , n ;
string s ;
void _main()
{
	cin >> n >> s ;
	int a , b , c , d ;
	a = b = c = d = 0 ;
	for(int i = 0 ; i < n ; i++)
	{
		if(s[i] == 'N')	a++ ;//往北走
		if(s[i] == 'S')	b++ ;//往南走
		if(s[i] == 'E')	c++ ;//往东走
		if(s[i] == 'W')	d++ ;//往西走
	}
	if(((b - a) & 1) || ((d - c) & 1))//不可分配
	{
		cout << "NO\n" ;
		return ;
	}
	if(((a == 1 && b == 1) || (a == 0 && b == 0)) && ((c == 1 && d == 1) || (c == 0 && d == 0)) && !(a == 1 && b == 1 && c == 1 && d == 1))//有一个机器人没走 
	{
		cout << "NO\n" ;
		return ;
	}
	int hr = 0 , lr = 0 ;
	bool h = 0 ;
	for(int i = 0 ; i < n ; i++)
	{
		if(s[i] == 'N')
		{
			if(hr < (a - b) / 2)	o1 , hr++ , h = 1 ;
			else if(a == b && !h)	o1 , hr++ , h = 1 ;//防止有机器人没走
			else	o2 ;
		}
		if(s[i] == 'S')
		{
			if(hr > (a - b) / 2)	o1 , hr-- , h = 1 ;//防止有机器人没走
			else if(a == b && !h)	o1 , hr-- , h = 1 ;
			else	o2 ;
		}
		if(s[i] == 'E')
		{
			if(lr < (c - d) / 2)	o1 , lr++ , h = 1 ;
			else if(c == d && !h)	o1 , lr++ , h = 1 ;//防止有机器人没走
			else	o2 ;
		}
		if(s[i] == 'W')
		{
			if(lr > (c - d) / 2)	o1 , lr-- , h = 1 ;
			else if(c == d && !h)	o1 , lr-- , h = 1 ;//防止有机器人没走
			else	o2 ;
		}
	}
	cout << '\n' ;
	return ;
}
int main()
{
	cin >> t ;
	while(t--)	_main() ;
	return 0 ;
}
```

---

## 作者：KukCair (赞：2)

### 基本思路

贪就完了。

首先要明确的是，在任何时刻都须保证机器人之间的距离最近。

因此，当某一时刻一个机器人的横坐标（或纵坐标）小于另一个机器人时，需要增加横坐标（或纵坐标）；横坐标（或纵坐标）大于另一个机器人时，需要减少横坐标（或纵坐标）。

另外，题目中给到“都分配给两个机器人”这一条件，因此不能使机器人没有动过。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin >> t;
    while(t--){
        int n, x1, y1, x2, y2;
        bool f1 = 0, f2 = 0;
        string ans = "", s; 
        x1 = y1 = x2 = y2 = 1;
        s = ' ' + s;
        for(int i = 1; i <= n; i++){
            if(s[i] == 'N'){
                if(y1 > y2 || (y1 == y2 && !f2)){
                    y2++;
                    f2 = 1;
                    ans += 'H';
                }
                else{
                    y1++;
                    f1 = 1;
                    ans += 'R';
                }
            }
            else if(s[i] == 'S'){
                if(y1 > y2 || (y1 == y2 && !f1)){
                    y1--;
                    f1 = 1;
                    ans += 'R';
                }
                else{
                    y2--;
                    f2 = 1;
                    ans += 'H';
                }
            }
            else if(s[i] == 'E'){
                if(x1 > x2 || (x1 == x2 && !f2)){
                    x2++;
                    f2 = 1;
                    ans += 'H';
                }
                else{
                    x1++;
                    f1 = 1;
                    ans += 'R';
                }
            }
            else{
                if(x1 > x2 || (x1 == x2 && !f1)){
                    x1--;
                    f1 = 1;
                    ans += 'R';
                }
                else{
                    x2--;
                    f2 = 1;
                    ans += 'H';
                }
            }
        }
        if(x1 == x2 && y1 == y2 && f1 && f2) cout << ans;
        else cout << "NO";
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：shiziyu111 (赞：2)

~~```Rover``` 和 ```Helicopter``` 要把我气死了~~。
# CF194D Ingenuity 题解
## 题目大意
给定一个长度为 $n$ 且仅包含 ```N```、```S```、```E```、```W``` 的指令串，将这些指令分给两个~~坑人的~~机器人，它们会沿着这个方向移动一步，问它们能否从同一个点走到另一个相同的点？

注意，原文中有一句话：Moreover, each device must execute at least one instruction.（此外，每个设备必须执行至少一条指令）。

## 分析
我们先来看一组样例：

```
2
NN
```

很明显，可以把它们分别分给两个机器人以达到效果。

所以，当同一个指令的数量 $\ge2$ 时，应该把他们平均分给两个机器人。

再看一组样例：

```
4
NNSN
```

在分完了两个 ```N``` 后，还剩下一个 ```N``` 和一个 ```S```，我们可以把它分给 ```Rover```，所以，当分完后，```N``` 的数量 $=$ ```S``` 的数量时，也是可以的。不过，为了减轻 ```Rover``` 的负担 ~~（不被样例的 case 7 卡）~~，我们应将多余的 ```W``` 和 ```E``` 分给 ```Helicopter```。

最后，再对是否有多余的 ```N```、```S```、```W```、```E``` 以及 ```Rover``` 和 ```Helicopter``` 是否行动做一个判断就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		int di[5][3]={0};
		char a[200005];
		int b[200005]={0};//把字符转化成数字
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]=='W')
			{
				b[i]=1;
			}
			if(a[i]=='E')
			{
				b[i]=2;
			}
			if(a[i]=='S')
			{
				b[i]=3;
			}
			if(a[i]=='N')
			{
				b[i]=4;
			}
			di[b[i]][0]++;
		}
		for(int i=1;i<=4;i++)
		{
			di[i][1]=di[i][2]=di[i][0]/2;
			di[i][0]%=2;
		} 
		di[1][1]+=di[1][0];
		di[2][1]+=di[2][0];
		di[3][2]+=di[3][0];
		di[4][2]+=di[4][0];
     	 //把多余的 W、E、S、N 分出去
		if(di[1][0]==di[2][0]&&di[3][0]==di[4][0]&&di[1][2]+di[2][2]+di[3][2]+di[4][2]!=0&&di[1][1]+di[2][1]+di[3][1]+di[4][1]!=0)//各种各样的判断
		{
			for(int i=1;i<=n;i++)
			{
				if(di[b[i]][1]>=1)
				{
					cout<<'R';
					di[b[i]][1]--;
				}
				else
				{
					cout<<'H';
				}
			}
		}
		else
		{
			cout<<"NO";
		}
		cout<<endl;
	}
	return 0;
  	//完结撒花
}
```

~~手打麻了~~。

---

## 作者：DrAlfred (赞：1)

摘要：构造

[传送门：https://www.luogu.com.cn/problem/CF1974D](https://www.luogu.com.cn/problem/CF1974D)

## 题意

你有两个机器人，分别是 `Rover (R)` 和 `Helicopter (H)`。它们初始都在同一平面直角坐标系 $xOy$ 的 $(0, 0)$ 处。定义北为 $y$ 轴正方向，东为 $x$ 轴正方向。

现有一串由以下四个字符指令组成的指令串 $s$：

- `N` 向北移动一步，即 $(x, y) \to (x, y + 1)$；
- `S` 向南移动一步，即 $(x, y) \to (x, y - 1)$；
- `E` 向东移动一步，即 $(x, y) \to (x + 1, y)$；
- `W` 向西移动一步，即 $(x, y) \to (x - 1, y)$；

问是否存在一种将每个指令都分配给两个机器人的方法，使得它们最终停在同一个位置？如果存在，给出一组构造；如果不存在，报告无解。

## 分析思路

我们分别分析两者在 $x$ 方向的增量 $\Delta x_R, \Delta x_H$ 和两者在 $y$ 方向的增量 $\Delta y_R, \Delta y_H$。

因为最终有 $\Delta x_R = \Delta x_H, \Delta y_R = \Delta y_H$，则两者在两个方向上增量的奇偶性相同（感性理解下）。换句话说，我们有 $\Delta x_R + \Delta x_H \equiv 0 \pmod 2; \Delta y_R + \Delta y_H \equiv 0 \pmod 2$。

于是，首先我们统计两个方向上总的增量个数，依据奇偶性可以初步判断无解。

然后我们考虑构造，现在以两个 $x$ 方向的操作 `E, W` 为例。我们记两个指令的个数分别为 $cnt_E, cnt_W$。

### 1. $cnt_E \equiv 1 \pmod 2$

此时有 $cnt_W \equiv 1 \pmod 2$。我们考虑从 `E` 中拿出一部分 $\frac{cnt_E - 1}{2}$，从 `S` 中拿出一部分 $\frac{cnt_W - 1}{2}$。此时我们有：

$$
\frac{cnt_E - 1}{2} - \frac{cnt_W - 1}{2} = \left(cnt_E - \frac{cnt_E - 1}{2}\right) - \left(cnt_W - \frac{cnt_W - 1}{2}\right)
$$

所以把这两部分分别分给两人即可。

### 2. $cnt_E \equiv 0 \pmod 2$

此时有 $cnt_W \equiv 0 \pmod 2$。我们考虑从 `E` 中拿出一部分 $\frac{cnt_E}{2}$，从 `S` 中拿出一部分 $\frac{cnt_W}{2}$。此时我们有：

$$
\frac{cnt_E}{2} - \frac{cnt_W}{2} = \left(cnt_E - \frac{cnt_E}{2}\right) - \left(cnt_W - \frac{cnt_W}{2}\right)
$$

所以把这两部分分别分给两人即可。最后判断一下是否都分给了一个人即可

$y$ 方向上的分配同理。注意“分别”的两人在 $x$ 轴和 $y$ 轴的分配中要调换一下，否则可能出现误判为无解的情况。

时间复杂度 $O\left(n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const string d = "EWNS";
int t, n;
inline void solve(void) {
    string s;
    cin >> n >> s;
    vector<int> pos[4];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (s[i] == d[j]) {
                pos[j].push_back(i);
            }
        }
    }
    if ((pos[0].size() + pos[1].size()) & 1 ||
        (pos[2].size() + pos[3].size()) & 1) {
        cout << "NO\n";
        return;
    }
    string ans(n, 'R');
    for (int i = 0; i < 4; i += 2) {
        if (pos[i].size() > pos[i + 1].size()) {
            std::swap(pos[i], pos[i + 1]);
        }
        int half1 = pos[i].size() >> 1;
        int half2 = pos[i + 1].size() >> 1;
        for (int j = 0; j < half1; j++) {
            ans[pos[i][j]] = (i ? 'H' : 'R');
        }
        for (int j = half1; j < pos[i].size(); j++) {
            ans[pos[i][j]] = (i ? 'R' : 'H');
        }
        for (int j = 0; j < half2; j++) {
            ans[pos[i + 1][j]] = (i ? 'H' : 'R');
        }
        for (int j = half2; j < pos[i + 1].size(); j++) {
            ans[pos[i + 1][j]] = (i ? 'R' : 'H');
        }
    }
    int cnt = count(ans.begin(), ans.end(), 'R');
    if (cnt == 0 || cnt == n) {
        cout << "NO\n";
    } else {
        cout << ans << '\n';
    }
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：__K2FeO4 (赞：1)

~~I wanna go crazy and insane! I will probably fall green... Fortunately it didn't happen.~~

其实本来这题挺简单的，但一条信息把题目搞复杂了。

### 题目翻译

给出一个长度为 $n$ 的操作序列，操作符为东西南北 `EWSN` 的一种。每个操作符号可要么针对 R，要么针对 H。现在 R 与 H 在同一位置。问怎样分配这个序列使操作后两者又回到同一位置。**要求至少一项针对 R，一项针对 H。**

### 错误解法

其实是最天真的方法，挺符合常理，只不过不符合题目要求。

相对运动。当 H 在向北移动时，可以 H 为基准看作 R 在向南运动。因此我们相当于能把其中某些操作符反转。

这样，目标状态是：东西对半分，南北对半分。

于是我们就能排除一些情况：当操作东西数量或操作南北数量为奇数时，不可能完成。

都是偶数，我们就分开考虑东西和南北。以东西为例，假设前半段为东，后半段为西。把理想操作序列与实际序列比较，一样就给 H，不一样就给 R。（代码实现可能与这个相反，不过都可行，等价的）

然后第 4 和 5 行输出就错了。

其实我一开始就注意到形如 `2 NS` 是不行的。原因是这样会只操作 R 和 H 的一种。于是我特判 $n=2$ 的情况：当两个操作符一致时，输出 `RH`，否则输出 `NO`。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200711;
int n,p,q,t;
char a[N];
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		scanf("%s",a+1);
		if(n==2){
			puts(a[1]==a[2]?"RH":"NO");
			continue;
		}
		p=q=0;
		for(int i=1;i<=n;i++){
			switch(a[i]){
				case 'N':p++;break;
				case 'S':p++;break;
				case 'E':q++;break;
				case 'W':q++;break;
			}
		}
		if((p&1)||(q&1))puts("NO");
		else{
			p/=2,q/=2;
			for(int i=1;i<=n;i++){
				switch(a[i]){
					case 'N':printf(p>0?"R":"H");p--;break;
					case 'S':printf(p<=0?"R":"H");p--;break;
					case 'E':printf(q>0?"R":"H");q--;break;
					case 'W':printf(q<=0?"R":"H");q--;break;
				}
			}
			puts("");
		}
	}
	return 0;
}
```
不过还是错了。

### 正确解法

不止是 $n=2$，其他也有出现只操作一种的情况。比如：
```
Input:
4
SSNN
Wrong Output:
HHHH
Correct Output:
HRRH
```
解决方法：把答案记录下来，如果有缺，遍历答案数组找到相对的（东西或南北），并同时改变操作对象即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200711;
int n,p,q,t;
char a[N],b[N];
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		scanf("%s",a+1);
		if(n==2){
			puts(a[1]==a[2]?"RH":"NO");
			continue;
		}
		p=q=0;
		for(int i=1;i<=n;i++){
			switch(a[i]){
				case 'N':p++;break;
				case 'S':p++;break;
				case 'E':q++;break;
				case 'W':q++;break;
			}
		}
		if((p&1)||(q&1))puts("NO");
		else{
			p/=2,q/=2;
			for(int i=1;i<=n;i++){
				switch(a[i]){
					case 'N':b[i]=p>0?'R':'H';p--;break;
					case 'S':b[i]=p<=0?'R':'H';p--;break;
					case 'E':b[i]=q>0?'R':'H';q--;break;
					case 'W':b[i]=q<=0?'R':'H';q--;break;
				}
			}
			int i=1,j=1;
			while(b[i]!='R'&&i<=n)i++;
			while(b[j]!='H'&&j<=n)j++;
			if(i>n){
				i=1,j=1;
				while(a[i]!='S'&&i<=n)i++;
				while(a[j]!='N'&&j<=n)j++;
				if(i>n||j>n){
					i=1,j=1;
					while(a[i]!='E'&&i<=n)i++;
					while(a[j]!='W'&&j<=n)j++;
				}
				b[i]=b[j]='R';
			}
			if(j>n){
				i=1,j=1;
				while(a[i]!='E'&&i<=n)i++;
				while(a[j]!='W'&&j<=n)j++;
				if(i>n||j>n){
					i=1,j=1;
					while(a[i]!='S'&&i<=n)i++;
					while(a[j]!='N'&&j<=n)j++;
				}
				b[i]=b[j]='H';
			}
			b[n+1]=0;
			puts(b+1);
		}
	}
	return 0;
}
```
于是就能过了。

~~结尾吐槽：为什么两个都要移，只移一个不香吗？~~

---

## 作者：tallnut (赞：1)

感觉 D 比 C 简单（大雾）
# 思路
分别记向北、南、东、西方向行走的指令条数为 $a,b,c,d$，则两个机器人总共向北的位移为 $a-b$，向东的位移为 $c-d$。显然，如果能够成功执行这些指令，那么两个机器人最终的位置为 $(\frac{a-b}{2},\frac{c-d}{2})$。因此如果 $a-b$ 或 $c-d$ 为奇数的话肯定无解。

那么在有解的情况下如何构造解呢？考虑用两个变量 $x,y$，分别表示 $1$ 号机器人共向北和东走了多少步。如果 $x=\frac{a-b}{2}$，说明 $1$ 号机器人已经到达指定位置，则移动 $2$ 号机器人；否则移动 $1$ 号机器人并修改 $x$ 的值。$y$ 的维护同理。

很遗憾，上述做法依然无法通过此题，因为题目中有要求**每个机器人至少执行一条指令**。解决办法是对解进行“微调”，即寻找一对南和北或东和西。这样相当于机器人兜了一个小圈子并回到了原点。注意，如果指令长度为 $2$，且只有一对南北或东西，则无解，因为只能有一个机器人会执行完这些指令。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/159786028)。

```cpp
// NOTE: "[EDIT]" means you should edit this part by yourself
#include <bits/stdc++.h>
// [EDIT] please enable this line if there are many tests
#define MULTITEST
using namespace std;
// [EDIT] if you want to copy some templates, please paste them here

typedef long long ll;
#define rep1(i,x,y) for (int i = (x);i <= (y);i++)
#define rep2(i,x,y) for (int i = (x);i >= (y);i--)
#define rep3(i,x,y,z) for (int i = (x);i <= (y);i += (z))
#define rep4(i,x,y,z) for (int i = (x);i >= (y);i -= (z))
#define cl(a) memset(a,0,sizeof(a))
// [EDIT] define some constants here

// [EDIT] define some variables, arrays, etc here
int n,Ncnt,Scnt,Ecnt,Wcnt,north,east,curN,curE;
string s,ans;
bool all_h(const string& ss)
{
    for (int i = 0;i < ss.size();i++)
        if (ss[i] != 'H') return false;
    return true;
}
pair<int,int> findNS(const string& ss)
{
    int npos = -1;
    int spos = -1;
    for (int i = 1;i <= n;i++)
        if (ss[i] == 'N')
        {
            npos = i;
            break;
        }
    for (int i = 1;i <= n;i++)
        if (ss[i] == 'S')
        {
            spos = i;
            break;
        }
    if (npos == -1 || spos == -1) return {-1,-1};
    else return {npos,spos};
}
pair<int,int> findEW(const string& ss)
{
    int epos = -1;
    int wpos = -1;
    for (int i = 1;i <= n;i++)
        if (ss[i] == 'E')
        {
            epos = i;
            break;
        }
    for (int i = 1;i <= n;i++)
        if (ss[i] == 'W')
        {
            wpos = i;
            break;
        }
    if (epos == -1 || wpos == -1) return {-1,-1};
    else return {epos,wpos};
}
// [EDIT] a function to solve the problem
void solve()
{
    //input
    cin >> n >> s;
    //solve
    pair<int,int> pivot = {-1,-1};
    s = ' ' + s;
    ans = "";
    Ncnt = 0;
    Scnt = 0;
    Ecnt = 0;
    Wcnt = 0;
    north = 0;
    east = 0;
    curN = 0;
    curE = 0;
    rep1(i,1,n)
        switch (s[i])
        {
            case 'N':
                Ncnt++;
                break;
            case 'S':
                Scnt++;
                break;
            case 'E':
                Ecnt++;
                break;
            case 'W':
                Wcnt++;
                break;
        }
    if (abs(Ncnt - Scnt) % 2 == 1)
    {
        cout << "NO\n";
        return;
    }
    if (abs(Ecnt - Wcnt) % 2 == 1)
    {
        cout << "NO\n";
        return;
    }
    north = (Ncnt - Scnt) / 2;
    east = (Ecnt - Wcnt) / 2;
    rep1(i,1,n)
    {
        if (s[i] == 'N' || s[i] == 'S')
        {
            if (curN != north)
            {
                if (s[i] == 'N') curN++;
                else curN--;
                ans += 'R';
            }
            else ans += 'H';
        }
        else
        {
            if (curE != east)
            {
                if (s[i] == 'E') curE++;
                else curE--;
                ans += 'R';
            }
            else ans += 'H';
        }
    }
    if (all_h(ans))
    {
        //cout<<1;
        if (ans.size() == 2)
        {
            cout << "NO\n";
            return;
        }
        //找：同时有S和N
        pair<int,int> p = findNS(s);
        if (p != pivot)
        {
            //cout<<2;
            ans[p.first - 1] = 'R';
            ans[p.second - 1] = 'R';
            //cout << "first=" << p.first << " second=" << p.second << '\n';
        }
        else
        {
            //cout<<3;
            p = findEW(s);
            ans[p.first - 1] = 'R';
            ans[p.second - 1] = 'R';
        }
    }
    //output
    cout << ans << '\n';
    //clear
    
}
int main()
{
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif
    int t;
#ifdef MULTITEST
    cin >> t;
#else
    t = 1;
#endif
    while (t--)
        solve();
#ifndef ONLINE_JUDGE
    cout << "\n---------------\n";
    system("pause");
#endif
}
```

---

## 作者：Genshin_ZFYX (赞：1)

对于每个操作，我们尽量让它们的距离最小，让左边的人往右移，让右边的人往左移，让上面的人往下移，让下面的人往上移。

如果它们在同一点上，第一次操作我们让 1 号动，其他让 2 号动，这样的话我们就尽量做到让每个机器都移动了。

最后判断两者是否在同一点上，两者是否都动了，输出。

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1974D Ingenuity-2 题解
### 分析
模拟水题。

比较蠢的一种方法，我们把 `E`、`W`、`N`、`S` 分配给两台机器。

- 当 `E` 的数量和 `W` 的数量一奇一偶时，无解。当 `N` 的数量和 `S` 的数量一奇一偶，无解。当有三种方向一个都没有且剩下一个的数量为奇数，无解。当 `E` 的数量和 `W` 的数量都为 $1$，且没有 `N` 和 `S` 时，无解。当 `N` 的数量和 `S` 的数量都为 $1$ 且没有 `W` 和 `E` 时，无解。

若有解，我们分类讨论。

- 若 `N` 的数量和 `S` 的数量都为偶数，则两台机器要执行的 `N` 和 `S` 的数量对半分。

- 否则，我们可以让第一台机器多执行一个 `N`，同时让第一台机器多执行一个 `S`。

- 若 `W` 的数量和 `E` 的数量都为偶数，则两台机器要执行的 `W` 和 `E` 的数量对半分。

- 否则，我们让第二台机器多执行一个 `W`，同时让第二台机器多执行一个 `E`。为什么不能让第一台呢，因为我们要防止有一台机器没指令执行。题目中禁止出现这样的情况。

最后根据每台机器的每种指令的数量选择指令并输出即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n;
string s;
signed main()
{
    for(cin>>t;t;t--)
    {
        int cnte=0, cnts=0, cntn=0, cntw=0;
        cin>>n;
        cin>>s;
        s=" "+s;
        for(int i=1;i<=n;i++)
        {
            if(s[i]=='E')
            {
                cnte++;
            }
            if(s[i]=='N')
            {
                cntn++;
            }
            if(s[i]=='S')
            {
                cnts++;
            }
            if(s[i]=='W')
            {
                cntw++;
            }
        }
        int tmp=(cnte==0)+(cntn==0)+(cntw==0)+(cnts==0);
        if(tmp>=3)
        {
            int cnt=cnte+cntn+cntw+cnts;
            if(cnt&1)
            {
                cout<<"NO\n";
                continue;
            }
        }
        if((cntn%2==0&&cnts%2==1)||(cntn%2==1&&cnts%2==0)||(cnte%2==0&&cntw%2==1)||(cnte%2==1&&cntw%2==0))
        {
            cout<<"NO\n";
            continue;
        }
        if((cntn==cnts&&cnts==1&&tmp>=2)||(cnte==cntw&&cntw==1&&tmp>=2))
        {
            cout<<"NO\n";
            continue;
        }
        int ae, as, an, aw, be, bs, bn, bw;
        if(cntn%2==1&&cnts%2==1)
        {
            an=cntn/2;
            bn=cntn-an;
            as=cnts/2;
            bs=cnts-as;
        }
        if(cntn%2==0&&cnts%2==0)
        {
            an=bn=cntn/2;
            as=bs=cnts/2;
        }
        if(cnte%2==1&&cntw%2==1)
        {
            be=cnte/2;
            ae=cnte-be;
            bw=cntw/2;
            aw=cntw-bw;
        }
        if(cnte%2==0&&cntw%2==0)
        {
            ae=be=cnte/2;
            aw=bw=cntw/2;
        }
        for(int i=1;i<=n;i++)
        {
            if(s[i]=='E')
            {
                if(ae!=0)
                {
                    ae--;
                    cout<<"R";
                }
                else
                {
                    cout<<"H";
                }
            }
            if(s[i]=='W')
            {
                if(aw!=0)
                {
                    aw--;
                    cout<<"R";
                }
                else
                {
                    cout<<"H";
                }
            }
            if(s[i]=='N')
            {
                if(an!=0)
                {
                    an--;
                    cout<<"R";
                }
                else
                {
                    cout<<"H";
                }
            }
            
            if(s[i]=='S')
            {
                if(as!=0)
                {
                    as--;
                    cout<<"R";
                }
                else
                {
                    cout<<"H";
                }
            }
        }
        cout<<"\n";
    }
	return 0;
}
```

---

## 作者：Daniel_yao (赞：1)

# Solve

相同的操作下，操作顺序对最终的位置无影响。

机器人的位置初始都为 $(0,0)$，所以只要操作同步即可。

此外注意到 $N$ 与 $S$，$E$ 与 $W$ 发生在同一个机器人上时，可以起到抵消的作用。

我们不希望只有一个机器人操作，所以让 R 机器人进行一次抵消操作，后面的抵消操作全部分配给 H。

其他的操作平均、同等分配即可。若无法分则判断无解。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 2e5 + 10, M = 200;

int T, n, b[M];

char a[N], ans[N];

void solve() {
  memset(b, 0, sizeof b);
  memset(ans, 0, sizeof ans);
  cin >> n >> (a + 1);
  if(n & 1) {
    cout << "NO\n";
    return ;
  }
  For(i,1,n) b[a[i]]++;
  int k1 = min(b['N'], b['S']), k2 = min(b['E'], b['W']);
  b['N'] -= k1, b['S'] -= k1, b['E'] -= k2, b['W'] -= k2;
  int K1 = k1;
  bool f1, f2; f1 = f2 = 0;
  for (int i = 1; i <= n && (k1 >= 0 || K1 >= 0); ++i) {
    if(a[i] == 'N' && k1 > 0) {
      if(f1) ans[i] = 'H';
      else if(!f1) ans[i] = 'R', f1 = 1;
      k1--; 
    }
    if(a[i] == 'S' && K1 > 0) {
      if(f2) ans[i] = 'H';
      else if(!f2) ans[i] = 'R', f2 = 1;
      K1--; 
    }
  }
  K1 = k2;
  for (int i = 1; i <= n && (k2 >= 0 || K1 >= 0); ++i) {
    if(a[i] == 'E' && k2 > 0) {
      if(f1) ans[i] = 'H';
      else if(!f1) ans[i] = 'R', f1 = 1;
      k2--; 
    }
    if(a[i] == 'W' && K1 > 0) {
      if(f2) ans[i] = 'H';
      else if(!f2) ans[i] = 'R', f2 = 1;
      K1--; 
    }
  }
  bool f = 1;
  for (int i : {'N', 'S', 'E', 'W'}) {
    f &= (b[i] == 0 && n <= 2);
    if(b[i] & 1) {
      cout << "NO" << '\n';
      return ;
    }
  }
  if(f) {
    cout << "NO" << '\n';
    return ;
  }
  For(i,1,n) {
    if((b[a[i]] & 1) && !ans[i]) ans[i] = 'R';
    else if(!(b[a[i]] & 1) && !ans[i]) ans[i] = 'H';
    b[a[i]]--;
  }
  For(i,1,n) cout << ans[i];
  cout << '\n';
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

给出一堆指令，将每个指令分配给机器人**流浪者**（百度翻译的）或机器人**直升机**，请问能否让它们最终在一个点。

## 解答

首先，设 $N_i$ 为北方向上的指令在第几个，其余方向一样，将每个方向对应第几个指令存进动态数组，举个例子：

对于 `NENSNE` 指令，$N_0=0,N_1=2,N_2=4$。

将两个相同的指令分配给两个机器人。

对于指令数量为奇数的方向：

* 若可以抵消，例如北方向和南方向都剩下不足 $2$ 的指令数，就给同一个机器人即可；
* 但是若不可以抵消，输出 `NO`。

说明两个使我程序出错的地方：

1. 必须要分配给两个机器人，就是说不能只将指令分配给流浪者或直升机，这里我是直接枚举答案数组判断的；
2. 若纯根据上面的修改方案也会有错，例如指令为 `WESN`，根据上文分配方案程序会全部分配给其中一个机器人，最终就会输出 `No`，但是可以每个机器人一半指令。所以，把多余指令不要只分配给一个机器人即可，我是将东西方向给直升机，南北方向给流浪者。

然后就没了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,nn,ss,ee,ww,H,R;
vector <int> N,S,E,W;
string s;
char ans[200001];

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		cin >> s;
		N.clear();//注意初始化
		S.clear();
		E.clear();
		W.clear();
		for(int i = 0;i < n;i++)
		{
			if(s[i] == 'N') N.push_back(i);//放进动态数组
			else if(s[i] == 'S') S.push_back(i);
			else if(s[i] == 'E') E.push_back(i);
			else W.push_back(i);
		}
		nn = N.size();
		ss = S.size();
		ee = E.size();
		ww = W.size();
		for(int i = 0;i < nn;i += 2)
		{
			if(i == nn - 1){nn = -1;break;};//多余的指令
			ans[N[i]] = 'R';//一对分配给两个机器人
			ans[N[i + 1]] = 'H';
		}
		for(int i = 0;i < ss;i += 2)//同上
		{
			if(i == ss - 1){ss = -1;break;};
			ans[S[i]] = 'R';
			ans[S[i + 1]] = 'H';
		}
		for(int i = 0;i < ee;i += 2)
		{
			if(i == ee - 1){ee = -1;break;};
			ans[E[i]] = 'R';
			ans[E[i + 1]] = 'H';
		}
		for(int i = 0;i < ww;i += 2)
		{
			if(i == ww - 1){ww = -1;break;};
			ans[W[i]] = 'R';
			ans[W[i + 1]] = 'H';
		}
		if(nn == -1)
		{
			if(ss == -1){ans[N[N.size() - 1]] = ans[S[S.size() - 1]] = 'R';}//有可以抵消的,继续分
			else{printf("NO\n");continue;}//否则没办法了
		}
		if(ss == -1)//同上
		{
			if(nn == -1){ans[N[N.size() - 1]] = ans[S[S.size() - 1]] = 'R';}
			else{printf("NO\n");continue;}
		}
		if(ee == -1)
		{
			if(ww == -1){ans[E[E.size() - 1]] = ans[W[W.size() - 1]] = 'H';}
			else{printf("NO\n");continue;}
		}
		if(ww == -1)
		{
			if(ee == -1){ans[E[E.size() - 1]] = ans[W[W.size() - 1]] = 'H';}
			else{printf("NO\n");continue;}
		}
		H = R = 0;
		for(int i = 0;i < n;i++) if(ans[i] == 'H') H++;else R++;//统计个数
		if(!H || !R){printf("NO\n");continue;}//检查是否有机器人没事干
		for(int i = 0;i < n;i++) cout << ans[i];//输出方案
		printf("\n");
	}
	return 0;
}
/*
1
4
WESN
*/
```

---

## 作者：__XU__ (赞：0)

# CF1974D Ingenuity-2 题解

## 思路：

一道贪心的大模拟，思路很简单，若想让两者最后在同一个位置那么为他们要走的方向数量要一致，我们只需要记录一下 $R$ 分别可以向哪个方向走几次剩下的一定是 $H$ 走的，加上特判即可 AC。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	while(t--){
		int n;
		string s;
		cin>>n;
		cin>>s;
		int N=0,E=0,S=0,W=0;
		for(int i=0;i<n;i++){//统计数量
			if(s[i]=='E'){
				E++;
			}
			else if(s[i]=='W'){
				W++;
			}
			else if(s[i]=='N'){
				N++;
			}
			else{
				S++;
			}
		}
		if(N==1&&S==1&&n==2){
			cout<<"NO"<<'\n';
			continue;
		}
		if(E==1&&W==1&&n==2){
			cout<<"NO"<<'\n';
			continue;
		}
		if(abs(S-N)%2==1||abs(W-E)%2==1){//如果不能均分
			cout<<"NO"<<'\n';
			continue;
		}
		int Re=0,Rw=0,Rs=0,Rn=0;//R能走的数量
		int f=0;
		if(S==n){//为了保持一致只能走一半
			Rs+=n/2;
			S=0;
		}
		if(W==n){
			Rw+=n/2;
			W=0;
		}
		if(E==n){
			Re+=n/2;
			E=0;
		}
		if(N==n){
			Rn+=n/2;
			N=0;
		}
		if(S==N){
			if(S==1){//f数组 不能让 R 全走了走过了就让 H 走
				f=1;
				Rs+=1;
				Rn+=1;
			}
			else{
				Rs+=S/2,Rn+=N/2;
			}
		}
		else if(S>N){
			Rs+=N;
			Rn+=N;
			S-=N;
			Rs+=S/2;
		}
		else if(S<N){
			Rs+=S;
			Rn+=S;
			N-=S;
			Rn+=N/2;
		}
		if(E==W){
			if(E==1&&f!=1){
				Re+=1;
				Rw+=1;
			}
			else{
				Re+=E/2,Rw+=W/2;
			}
		}
		else if(E>W){
			Re+=W;
			Rw+=W;
			E-=W;
			Re+=E/2;
		}
		else if(E<W){
			Rw+=E;
			Re+=E;
			W-=E;
			Rw+=W/2;
		}
//		cout<<Rs<<' '<<Rn<<' '<<Re<<' '<<Rw<<'\n';
		for(int i=0;i<n;i++){
			if(s[i]=='E'){
				if(Re>0){
					Re--;
					cout<<"R";
				}
				else cout<<"H";
			}
			if(s[i]=='W'){
				if(Rw>0){
					Rw--;
					cout<<"R";
				}
				else cout<<"H";
			}
			if(s[i]=='S'){
				if(Rs>0){
					Rs--;
					cout<<"R";
				}
				else cout<<"H";
			}
			if(s[i]=='N'){
				if(Rn>0){
					Rn--;
					cout<<"R";
				}
				else cout<<"H";
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1974D
## 题意
给定一个长度为 $n$ 的字符串 $s$，由 ```NSEW``` 组成。现在将每个操作都分给机器人 R 或 H。问能否求出一种分配情况使得机器人 R 和 H 最终的位置相同，且两个机器人至少分得一种操作。有解输出其中一种可能的分配情况，否则输出 ```NO```。
## 思路
本题是一道贪心题。

我们发现，可以遍历字符串，在第 $i$ 个位置时，有以下几种情况：

- $s _ {i}$ 为 ```N```，判断机器人 R 和 H 哪个在更南边，就让它向北走一步。如果哪个没有被操作过优先更新哪个。

- $s _ {i}$ 为 ```S```，与上一个同理。

- $s _ {i}$ 为 ```W```，判断机器人 R 和 H 哪个在更东边，就让它向西走一步。如果哪个没有被操作过优先更新哪个。

- $s _ {i}$ 为 ```E```，与上一个同理。

在遍历完成后，如果两个机器人的位置不相同或者有其中一个没有被操作过，输出 ```NO```。否则输出分配情况。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		int xa=0,ya=0,xb=0,yb=0,f1=0,f2=0;
		string ans="";
		for(int i=0;i<n;i++){
			if(s[i]=='N'){
				if(xa<xb||!f1){
					ans+='R';
					xa++;
					f1=1;
				}else{
					ans+='H';
					xb++;
					f2=1;
				}
			}
			if(s[i]=='S'){
				if(xa>xb||!f1){
					ans+='R';
					xa--;
					f1=1;
				}else{
					ans+='H';
					xb--;
					f2=1;
				}
			}
			if(s[i]=='E'){
				if(ya<yb||!f1){
					ans+='R';
					ya++;
					f1=1;
				}else{
					ans+='H';
					yb++;
					f2=1;
				}
			}
			if(s[i]=='W'){
				if(ya>yb||!f1){
					ans+='R';
					ya--;
					f1=1;
				}else{
					ans+='H';
					yb--;
					f2=1;
				}
			}
		}
		if(xa!=xb||ya!=yb||!f1||!f2)cout<<"NO\n";
		else cout<<ans<<'\n';
	}
	return 0;
}
```

---

