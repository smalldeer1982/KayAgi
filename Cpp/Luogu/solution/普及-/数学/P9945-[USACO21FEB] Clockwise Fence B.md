# [USACO21FEB] Clockwise Fence B

## 题目描述

围绕 Farmer John 最大的草地的栅栏已经损坏了，如今他终于决定要换一个新的栅栏。

不幸的是，当 Farmer John 在铺设新栅栏时，一只巨大的蜜蜂突然出现，在他的草地上追着他跑，导致最后栅栏被沿着一条相当不规则的路径铺设。栅栏可以用一个字符串表示，每个字符为 `N`（north，北）、`E`（east，东）、`S`（south，南）、`W`（west，西）之一。每个字符表示一米长的一段栅栏。举例来说，如果字符串为 `NESW`，这表示栅栏从起点开始向北延伸 $1$ 米，然后向东延伸 $1$ 米，然后向南延伸 $1$ 米，然后向西延伸 $1$ 米，回到栅栏的起点。

栅栏的结束位置与开始位置相同，而这是栅栏的路径上唯一会被到达多次的位置（从而起始位置是唯一会被再次到达的位置，在栅栏结束之时）。结果，栅栏确实围起了一个草地上连通的区域，尽管这个区域可能形状十分奇特。

Farmer John 想要知道他铺设栅栏的路径是顺时针（当按字符串表示的顺序沿着栅栏的路径行走时被围起的区域位于右侧）还是逆时针（被围起的区域位于左侧）。 

## 说明/提示

### 样例解释 1

以下为这两条栅栏路径，用 `@` 表示起始位置：

```plain
*>*
^ v
@<*
```
```plain
  *<*<*<*
  v     ^
*<@     *
v       ^
* *>*>* *
v ^   v ^
* *<* * *
v   ^ v ^
*>*>* *>*
```

## 样例 #1

### 输入

```
2
NESW
WSSSEENWNEESSENNNNWWWS```

### 输出

```
CW
CCW```

# 题解

## 作者：zzhbpyy (赞：8)

## 题目大意 
[题目传送门](https://www.luogu.com.cn/problem/P9945)。
## 解题思路
第一眼看题目会发现完全没有思路。实质上所谓逆时针和顺时针只与**转向的次数与方向**有关。由于题目保证 John 一定走了一圈。毫无疑问一次左转和一次右转后行走方向不变。

仔细观察得到：可统计左转（记为 $-1$）和右转（记为 $+1$）的个数记为 $ans$。若 $ans$ 大于 $0$ 输出 CW，否则输出 CCW。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
int init(char a,char b){
	if(a=='N'&&b=='E')return 1;
	if(a=='E'&&b=='S')return 1;
	if(a=='S'&&b=='W')return 1;
	if(a=='W'&&b=='N')return 1;
	return -1;
}
signed main(){
	int n;
	string s;
	cin>>n;
	while(n--){
		ans=0;
		cin>>s;
		for(int i=1;i<s.length();i++){
			if(s[i-1]!=s[i])//与前一个字符不同再判定转弯方向
			ans+=init(s[i-1],s[i]);
		}
		if(ans>0)cout<<"CW\n";
		else cout<<"CCW\n";
	}
}
```

---

## 作者：Luogu_916767 (赞：5)

[In Luogu](https://www.luogu.com.cn/problem/P9945)
	
### 题目大意
	
给出 Farmer John 的行动轨迹，判断 Farmer John 究竟是顺时针走完的这一圈还是逆时针走完的这一圈。

### 思路分析

由题意可知，Farmer John 行走路线最后一定会形成一个圈（首尾相连）。

由此易得，我们把路线简化成一个圈，把右转看做正方向旋转，左转看做反方旋转。由于左转 $90$ 度再右转 $90$ 度和没转一样，所以我们把右转 $90$ 度记作 $+90$，左转 $90$ 度记作 $-90$。如果最后所有的转向之和为 $+360$ 度，则可以看成 Farmer John 一直在右转，转完 $360$ 度后回到原点，那么就是顺时针走；否则，就是逆时针在走。

### 具体实现

#### 转向

反正也不多，直接 map 打表就好了。
```cpp
mp["EN"] = -90;
mp["SE"] = -90;
mp["WS"] = -90;
mp["NW"] = -90;
mp["NE"] = 90;
mp["ES"] = 90;
mp["SW"] = 90;
mp["WN"] = 90;
```

#### 处理每次转向

针对每两个挨在一起的字符，如果相同，就代表没转向。否则，就用 map 里的数据加进 ans 里。

**(提示：注意处理第一位和最后一位，其实也是挨着的！)**

```cpp
int ans = 0;
for(int i = 0; i < s.size(); i ++ ){
	string ss = "";
	ss = ss + s[i];
	ss = ss + s[(i+1)%s.size()];
	ans += mp[ss];
}
```

综上

### Code

```cpp
#include<iostream>
#include<map>

using namespace std;

int n;
string s;
map<string,int> mp;

int main(){
	mp["EN"] = -90;
	mp["SE"] = -90;
	mp["WS"] = -90;
	mp["NW"] = -90;
	mp["NE"] = 90;
	mp["ES"] = 90;
	mp["SW"] = 90;
	mp["WN"] = 90;
	cin>>n;
	while(n -- ){
		cin>>s;
		int ans = 0;
		for(int i = 0; i < s.size(); i ++ ){
			string ss = "";
			ss = ss + s[i];
			ss = ss + s[(i+1)%s.size()];
			ans += mp[ss];
		}
		if(ans == 360){
			cout<<"CW\n";
		}else{
			cout<<"CCW\n";
		}
	}
	return 0;
}
```

---

## 作者：__Venti__ (赞：4)

# P9945 题解
[题目传送门](https://www.luogu.com.cn/problem/P9945)

[博客查看](https://www.luogu.com.cn/blog/xuqile7/)

#### 终于找到我会写又还能交题解的题了，赶紧过来写题解。
## 思路

根据题目的第二段可知：Farmer John 一定会回到栅栏的起点。

我们只需要把 Farmer John 左转和右转的次数分别累加起来，判断 Farmer John 是左转的次数多还是右转的次数多即可。
___
即：
```cpp
	if(左转的次数>右转的次数)cout<<"CCW"<<endl;
	else cout<<"CW"<<endl;
``````
___
判断 Farmer John 走的方向是左转还是右转如下表：

（E = 东，S = 南，W = 西，N = 北）

|  现在的方向  |  下一个方向  |  转弯的方向  |
| :----------: | :----------: | :----------: |
| N | E | 右转 |
| N | W | 左转 |
| S | E | 左转 |
| S | W | 右转 |
| E | N | 左转 |
| E | S | 右转 |
| W | N | 右转 |
| W | S | 左转 |
## 实现
### 输入输出：
```cpp
	int n,l,r;//一个整数 N，l 为左转了几次，r 为右转了几次
	string s;//一个字符串
	cin>>n;
	while(n--){//循环N次
		cin>>s;//每次一个栅栏路径
		......//判断每次是左转还是右转
		if(l>r)cout<<"CCW"<<endl;//如果左转的次数>右转的次数,则为逆时针
		else cout<<"CW"<<endl;//否则为顺时针
		l=0,r=0//初始化
	}
``````
### 判断每次是左转还是右转：
```cpp
	for(int i=0;i<s.size()-1;i++){
		string s1="";//定义一个 s1 储存现在的方向和下一个方向
		s1+=s[i],s1+=s[i+1]; //s1=现在的方向和下一个方向
		//下面的判断语句根据上面列出的表来判断是右转+1还是左转+1
		if(s1=="NE")r++;//右转+1
		else if(s1=="NW")l++;//左转+1
		else if(s1=="SE")l++;
		else if(s1=="SW")r++;
		else if(s1=="EN")l++;
		else if(s1=="ES")r++;
		else if(s1=="WN")r++;
		else if(s1=="WS")l++;
	}

``````
### 主程序(上面已经有注释就不用我在打了吧)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r;
string s;
int main(){
	cin>>n;
	while(n--){
		cin>>s;
		for(int i=0;i<s.size()-1;i++){
			string s1="";
			s1+=s[i],s1+=s[i+1]; 
			if(s1=="NE")r++;
			else if(s1=="NW")l++;
			else if(s1=="SE")l++;
			else if(s1=="SW")r++;
			else if(s1=="EN")l++;
			else if(s1=="ES")r++;
			else if(s1=="WN")r++;
			else if(s1=="WS")l++;
		}
		if(l>r)cout<<"CCW"<<endl;
		else cout<<"CW"<<endl;
		l=0,r=0;
	}
	return 0;
}
``````
___
本蒟蒻的第一篇题解，还请大家支持一下。

---

## 作者：_luouhgy_ (赞：1)

我的做题思路可能和其他大佬有重复的地方，但我在此声明，我的题解都是我自己手码的。

## 题目大意

其实就是进行若干次旋转回到原点后，让我们判断是顺时针转了一圈，还是逆时针转了一圈。

## 思路

因为题目中说最后到达了起始位置，所以我们只要判断是顺时针还是逆时针。只要判断左转的次数多还是右转的次数多。

如果是左转的次数多，就说明是逆时针；如果是右转的次数多，就说明是顺时针。

**注意，不要和我一样把 $N,S,E,W$ 打成小写。**
## Code
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int t; 
int main(){
	cin>>t;
	while(t--){
		string s;
		int left=0,right=0;//左转的次数，右转的次数
		cin>>s;
		int len=s.size();
		for(int i=2;i<=len;i++){
			if(s[i-1]=='N' and s[i]=='E'){//北->东
				right+=1;//右转的次数+1
			}
			if(s[i-1]=='E' and s[i]=='S'){//东->南
				right+=1;//右转的次数+1
			}
			if(s[i-1]=='S' and s[i]=='W'){//南->西
				right+=1;//右转的次数+1
			}
			if(s[i-1]=='W' and s[i]=='N'){//西->北 
				right+=1;//右转的次数+1
			}
			if(s[i-1]=='N' and s[i]=='W'){//北->西
				left+=1;//左转的次数+1
			}
			if(s[i-1]=='W' and s[i]=='S'){//西->南 
				left+=1;//左转的次数+1
			}
			if(s[i-1]=='S' and s[i]=='E'){//南->东
				left+=1;//左转的次数+1
			}
			if(s[i-1]=='E' and s[i]=='N'){//东->北 
				left+=1;//左转的次数+1
			}
		}
		if(left<=right){//右转的次数多
			cout<<"CW"<<endl;//顺时针 
		}else{
			cout<<"CCW"<<endl;//逆时针 
		}
	}
	return 0;
}
```


---

## 作者：lqsy002 (赞：1)

## 题目大意
给 $n$ 个字符串，表示奔跑的路线，路线保证从一个点出发还会回到这个点，当然这个路线并不规则，判断是顺时针跑的路线还是逆时针跑的路线。[题目链接](https://www.luogu.com.cn/problem/P9945)。

## 解题思路
1. 先向东，再向南，那就是转了 $90$ 度，一直顺指针，无论中间怎么转，最终一定是转了 $360$ 度。
2. 先向东，再向北，那就是反着转了 $90$ 度，可以记为 $-90$ 度，同样，如果总体方向是逆时针，最后一定是转了 $-360$ 度。
3. 计算这条路线转了 $360$ 度还是转了 $-360$ 度，就可以区分是顺时针还是逆时针。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,len,ang,dir[4][4]={{0,0,90,-90},{0,0,-90,90},{-90,90,0,0},{90,-90,0,0}}; 
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>s;
		s+=s[0];
		len=s.size();
		ang=0;
		for(int j=0;j<=len-2;++j){
			int x,y;
			if(s[j]=='E')
				x=0;
			if(s[j+1]=='E')
				y=0; 
			if(s[j]=='W')
				x=1;
			if(s[j+1]=='W')
				y=1; 
			if(s[j]=='S')
				x=2;
			if(s[j+1]=='S')
				y=2; 
			if(s[j]=='N')
				x=3;
			if(s[j+1]== 'N')
				y=3; 
			ang+=dir[x][y];
		}
		if(ang==-360)
			cout<<"CCW\n";
		else if(ang==360)
			cout<<"CW\n";
	} 
	return 0;
}
```

---

## 作者：luoguDomi (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9945)
这道题让我们判断 Famer John 走的是顺时针还是逆时针，看似很难判断，实则很简单。

我们可以看到，如果左转(N -> W,S -> W,E -> N,E -> S)的次数大于右转(W -> N,W -> S,N -> E,S -> E)的次数,则栅栏是逆时针，反之亦然。

所以我们枚举一下，统计出转的次数即可。

以下为核心代码：
```cpp
	if(s[i]=='N'){
		if(s[i+1]=='W')
			l++;
		if(s[i+1]=='E')
			r++;
	}
	if(s[i]=='S'){
		if(s[i+1]=='E')
			l++:
		if(s[i+1]=='W')
			r++
	}
	if(s[i]=='W'){
		if(s[i+1]=='S')
			l++;
		if(s[i+1]=='N')
			r++;
	}
	if(s[i]=='E'){
		if(s[i+1]=='N')
			l++;
		if(s[i+1]=='S')
			r++;
	}
```
对了，刚看了下巨佬们的题解，发现[@Augenstern5](https://www.luogu.com.cn/blog/Luogu-Official-Blog/) 的思路与我的相像，所以我在此声明，不是抄袭，不是抄袭，不是抄袭，~~重要的事情说三遍~~。

---

## 作者：Vct14 (赞：1)

可以发现，如果左转较右转数量更多，则被围起的区域位于左侧（逆时针），反之为右侧（顺时针）。统计一下即可。

转向的情况如下表。

| 转向前 | 转向后 | 转向 |
| -----------: | -----------: | -----------: |
| 北 | 西 | 左 |
| 南 | 东 | 左 |
| 西 | 南 | 左 |
| 东 | 北 | 左 |
| 北 | 东 | 右 |
| 南 | 西 | 右 |
| 西 | 北 | 右 |
| 东 | 南 | 右 |

```c++
#include<bits/stdc++.h>
using namespace std;

int lft,rgh;

void turn(char bef,char aft){
	if(bef=='N'){
		if(aft=='W') lft++;
		if(aft=='E') rgh++;
	}
	if(bef=='S'){
		if(aft=='E') lft++;
		if(aft=='W') rgh++;
	}
	if(bef=='W'){
		if(aft=='S') lft++;
		if(aft=='N') rgh++;
	}
	if(bef=='E'){
		if(aft=='N') lft++;
		if(aft=='S') rgh++;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;
	while(n--){
		lft=rgh=0;
		string a;cin>>a;
		int l=a.size();
		for(int i=0; i<l; i++) turn(a[i],a[(i+1)%l]);
		if(lft>=rgh) puts("CCW");
		else puts("CW");
	}
	return 0;
} 
```

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9945)

## 思路

先来列一个角度变化表（顺时针为正，逆时针为负）。

|转向表|$y$|东|西|南|北|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$x$|$x\backslash y$|$0$|$1$|$2$|$3$|
|**东**|$0$|$0\degree$|$0\degree$|$90\degree$|$-90\degree$|
|**西**|$1$|$0\degree$|$0\degree$|$-90\degree$|$90\degree$|
|**南**|$2$|$-90\degree$|$90\degree$|$0\degree$|$0\degree$|
|**北**|$3$|$90\degree$|$-90\degree$|$0\degree$|$0\degree$|

遍历栅栏字符串的每一个字符。

当前字母转化为方向 $x$，下一个字母转化为方向 $y$。

方向 $x$ 转向方向 $y$ 的角度值加到 $ans$ 中。

$ans$ 为 $360\degree$ 表示顺时针，$-360\degree$ 表示逆时针。

```cpp
#include <iostream>
using namespace std;

int n;
string s;
int d[4][4] = { // 角度变化表
	{0, 0, 90, -90},
	{0, 0, -90, 90},
	{-90, 90, 0, 0},
	{90, -90, 0, 0}
}; 

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		s = s + s[0]; // 要回到起点，所以加上 s[0]
		int len = s.size();
		int ans = 0;
		for (int i = 0; i <= len - 2; i++) { 
			int x, y;
            // 当前字符方向
			if (s[i] == 'E') x = 0; // 东 -> 0
			if (s[i] == 'W') x = 1; // 西 -> 1
			if (s[i] == 'S') x = 2; // 南 -> 2
			if (s[i] == 'N') x = 3; // 北 -> 3
            // 下一个字符方向
			if (s[i+1] == 'E') y = 0; // 东 -> 0
			if (s[i+1] == 'W') y = 1; // 西 -> 1
			if (s[i+1] == 'S') y = 2; // 南 -> 2
			if (s[i+1] == 'N') y = 3; // 北 -> 3
			if (d[x][y]) ans += d[x][y]; // 加上度数
		}
		if (ans == -360) cout << "CCW" << endl;
		else if (ans == 360) cout << "CW" << endl;
	}
	return 0;
}
```


---

## 作者：aleph_ (赞：1)

# P9945 题解

### 思路

要求最终是顺时针还是逆时针，只需要注意转弯的方向就行了。

可以发现转的弯是顺时针数量较多的话，答案就是顺时针，反之就是逆时针（好像没有顺时针逆时针数量相同的数据）。

我们令顺时针转为 $90$ 度，逆时针转为 $-90$ 度。每经过一个弯就把弯的度数加上。最后看结果，**如果是正的**，那就是顺时针多，答案也就是顺时针，反之就是逆时针。

其实完全可以顺时针 $+1$，逆时针 $-1$。上文那样定只是为了方便理解。

### 注意事项

因为栅栏是个闭环，所以**最后一个操作到第一个操作之间可能还有一个弯**，不要漏掉哦！

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int angle(char a,char b){
	if(a==b) return 0;//方向不变
	//逆时针
	else if(a=='E'&&b=='N') return -90;
	else if(a=='N'&&b=='W') return -90;
	else if(a=='W'&&b=='S') return -90;
	else if(a=='S'&&b=='E') return -90;
	//顺时针
	else if(a=='E'&&b=='S') return 90;
	else if(a=='S'&&b=='W') return 90;
	else if(a=='W'&&b=='N') return 90;
	else if(a=='N'&&b=='E') return 90;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		int res=0,m=s.size();
		for(int i=0;i<m-1;i++){
		    res+=angle(s[i],s[i+1]);
		}
		res+=angle(s[m-1],s[0]);//不要漏了哦
		if(res>=0) cout<<"CW"<<endl;//>或>=都可以
		else cout<<"CCW"<<endl;
	}
	return 0;//您AC啦
}
```
    

---

## 作者：wzb13958817049 (赞：1)

~~翻了一下题解好像没有一个人跟我一样是用模拟去做的。~~
# 思路
根据提示来模拟，画出与提示相同的图，再去判断按字符串表示的顺序沿着栅栏的路径行走时被围起的区域位于右侧还是左侧。时间复杂度较高，但是本题数据较小能过。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;string b;char a[405][405];
int fx[5]={0,1,-1,0,0};
int fy[5]={0,0,0,1,-1};
void dfs(int x,int y){//从(1,1)开始遍历全图把所有没有被围起的点变成'.'
	a[x][y]='.';
	for(int i=1;i<=4;i++){
		int tx=x+fx[i],ty=y+fy[i];
		if(tx>=1 && tx<=401 && ty>=1 && ty<=401 && a[tx][ty]=='x') dfs(tx,ty);
	}
}
int main(){
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);	
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b;long long x=201,y=201;
		memset(a,'x',sizeof a);
		a[x][y]='@';
		for(int i=0;i<b.size();i++){
			if(b[i]=='N') {a[--x][y]='^';a[--x][y]='*';}//北
			if(b[i]=='S') {a[++x][y]='v';a[++x][y]='*';}//南
			if(b[i]=='E') {a[x][++y]='>';a[x][++y]='*';}//东
			if(b[i]=='W') {a[x][--y]='<';a[x][--y]='*';}//西
		}
		dfs(1,1);//不存在边缘是围起区域的情况可以直接开搜
		if(b[0]=='N'){if(a[200][200]=='.')cout<<"CW\n";else cout<<"CCW\n";}//如果第一个箭头的左边不是被围起区域则是顺时针
		if(b[0]=='S'){if(a[202][200]=='.')cout<<"CCW\n";else cout<<"CW\n";}//下同
		if(b[0]=='W'){if(a[200][200]=='.')cout<<"CCW\n";else cout<<"CW\n";}
		if(b[0]=='E'){if(a[200][202]=='.')cout<<"CW\n";else cout<<"CCW\n";}
	}
	return 0;
}
```


---

## 作者：_little_Cabbage_ (赞：0)

# P9945 [USACO21FEB] Clockwise Fence B 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p9945)~~

这是一道思维题。

我们可以发现，如果他往左转，则就是往反方向旋转，右转就是顺时针旋转。所以我们可以把右转记为 $+1$，左转记为 $-1$，最终如果答案为 $4$，就是顺时针旋转，否则就是逆时针旋转。

我们可以用 STL 中的 map 来解决这道题，map 的第一个参数为数据类型 pair，第二个参数为 $+1$ 还是 $-1$。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
map<pair<char,char>,int>mp;
void init()
{
	mp[make_pair('E','N')]=-1;
	mp[make_pair('S','E')]=-1;
	mp[make_pair('W','S')]=-1;
	mp[make_pair('N','W')]=-1;
	mp[make_pair('N','E')]=1;
	mp[make_pair('E','S')]=1;
	mp[make_pair('S','W')]=1;
	mp[make_pair('W','N')]=1;
}
int main()
{
	init();
	int n;
	cin>>n;
	while(n--)
	{
		string s;
		cin>>s;
		int len=s.size();
		int ans=0;
		for(int i=0;i<len;i++)
		{
			if(i==len-1)
			{
				ans+=mp[make_pair(s[len-1],s[0])];
			}
			else
			{
				ans+=mp[make_pair(s[i],s[i+1])];
			}
		}
		if(ans==4)
		{
			cout<<"CW"<<endl;
		}
		else
		{
			cout<<"CCW"<<endl;
		}
	}
}
```
[AC 记录](https://www.luogu.com.cn/record/142457920)

---

## 作者：JOKER_chu (赞：0)

## 以下是坑：

我们知道 FJ 会到处跑，但是他会回到起点的！！！

## 接下来是思路：

模拟发现，可以**分类讨论**，判断一下每个转向的次数，向左转多就输出逆时针，向右转多就输出顺时针。因为你从回来的时候，不可能从左回来，向右转多。无论往哪走，从右回来时，最后的计数肯定是向右转多，不可能向左转多最后从右边回来。其实也就一句话：**从哪边回来，转向那边的次数一定比相反的得多**。谢谢第一篇题解为我提供了最大坑点；**FJ 跑出的圈是个封闭图形**，最后的操作到第一个操作也算一个弯呢，不判过不了这组数据：WSEN，因为这个数据的左转与右转次数是**一样**的，不判最后的操作与第一次操作的转向会**没有**输出。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
string a;
map<char, int>zm;

int zhuanxiang(int u, int v){
	int cnt = 0;
	if(u == 1){
		if(v == 3){
			cnt--; // 逆时针
		}else if(v == 4){
			cnt++; // 顺时针
		}
	}else if(u == 2){
		if(v == 3){
			cnt++; // 顺时针
		}else if(v == 4){
			cnt--; // 逆时针
		}
	}else if(u == 3){
		if(v == 1){
			cnt++; // 顺时针
		}else if(v == 2){
			cnt--; // 逆时针
		}
	}else if(u == 4){
		if(v == 1){
			cnt--; // 逆时针
		}else if(v == 2){
			cnt++; // 顺时针
		} 
	}
	return cnt;
}

int main(){
	zm['N'] = 1; // 每个字母代表的数字，使用了 map 
	zm['S'] = 2;
	zm['E'] = 3;
	zm['W'] = 4;
	cin >> n;
	for(int i = 1; i <= n; i++){ // n 组数据 
		cin >> a;
		int ans = 0;
		for(int j = 1; j < a.size(); j++){
			int u = zm[a[j]], v = zm[a[j - 1]]; // 我这里用了数字存，不习惯字母储存
			ans += zhuanxiang(u, v);
		}
		int u = zm[a[0]], v = zm[a[a.size() - 1]]; // 起点与终点到达的最后一个转向 
		ans += zhuanxiang(u, v);
		cout << (ans > 0 ? "CW" : "CCW") << endl; // 按要求输出 
	}
	return 0;
}
```
~~完~~

---

