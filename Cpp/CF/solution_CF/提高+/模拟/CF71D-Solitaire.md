# Solitaire

## 题目描述

Vasya 手里有一副 54 张扑克牌。为了消遣，Vasya 开始玩纸牌游戏。

Vasya 将 $nm$ 张牌摆成一个 $n\times m$ 的矩形。如果其中有大小王，Vasya 会从剩下的 $54 - nm$ 张扑克牌中任意选牌将它们换下。Vasya 在换牌时会尽量使得纸牌游戏能被解决。

Vasya 认为：一轮纸牌游戏能被解决，当且仅当大小王被换下后，存在两个不重叠的 $3\times 3$ 正方形，每个正方形中的扑克牌**花色一致**或**点数互不相同**。

请你求出给定的纸牌游戏能否被解决。如果有解，给出任意一组解即可。

## 样例 #1

### 输入

```
4 6
2S 3S 4S 7S 8S AS
5H 6H 7H 5S TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C
```

### 输出

```
No solution.```

## 样例 #2

### 输入

```
4 6
2S 3S 4S 7S 8S AS
5H 6H 7H J1 TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C
```

### 输出

```
Solution exists.
Replace J1 with 2H.
Put the first square to (1, 1).
Put the second square to (2, 4).
```

## 样例 #3

### 输入

```
4 6
2S 3S 4S 7S 8S AS
5H 6H 7H QC TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C
```

### 输出

```
Solution exists.
There are no jokers.
Put the first square to (1, 1).
Put the second square to (2, 4).
```

# 题解

## 作者：sickbot (赞：4)

# 直接暴搜。


因为时间复杂度最大时是 J1,J2 同时出现，这时首先两重循环枚举 J1,J2 换成的牌，然后枚举 $x_1,y_1,x_2,y_2$ ，故时间复杂度最大为 $O(n^4)$ ，因为 $54^4=8,503,056$ ，所以直接暴搜不会 TLE 。


设 f 为纸牌中 Joker 的个数。当 $f=0,1,2$ 时分别讨论。


贴代码（码风较差见谅）
```cpp
#include<bits/stdc++.h>
using namespace std;
string c[17][17];	
set<string> crd;	//出现过的牌
int J1x,J1y,J2x,J2y; 	// J1,J2 的坐标
string CARD[52]={
"AC","AD","AH","AS","2C","2D","2H","2S","3C","3D","3H","3S","4C","4D","4H","4S",
"5C","5D","5H","5S","6C","6D","6H","6S","7C","7D","7H","7S","8C","8D","8H","8S",
"9C","9D","9H","9S","TC","TD","TH","TS","JC","JD","JH","JS","QC","QD","QH","QS",
"KC","KD","KH","KS"};	//所有牌
bool isvaild(string x)	//判断一张牌是否已经用过（未用过返回 1 ）
{
	return !count(crd.begin(),crd.end(),x);
}
bool chk(int x,int y)//	判断 3*3 的正方形内牌是否满足要求
{
	char hs=c[x][y][1];
	int v=0;
	set<char> st;
	for(int i=x;i<x+3;i++)
	{
		for(int j=y;j<y+3;j++)
		{
			if(c[i][j][1]==hs) v++;
			st.insert(c[i][j][0]);
		}
	}
	return (v==9)||(st.size()==9);
}
int main()
{
	J1x=-1,J1y=-1,J2x=-1,J2y=-1;
	string Jname="";
	int n,m;
	cin>>n>>m;
	if(!(n>=6||m>=6)) //n*m矩形太小了
	{
		cout<<"No solution.\n";
		return 0;
	}
	int f=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>c[i][j];
			if(c[i][j]=="J1"||c[i][j]=="J2")
			{
				f++;
				if(c[i][j]=="J1") J1x=i,J1y=j;
				if(c[i][j]=="J2") J2x=i,J2y=j;
			 } 
			else
			{
				crd.insert(c[i][j]);
			}
		}
	}
	if(f==0)
	{
		for(int i1=0;i1<=n-3;i1++)
		{
			for(int j1=0;j1<=m-3;j1++)
			{
				if(chk(i1,j1))
				{
					for(int i2=0;i2<=n-3;i2++)
					{
						for(int j2=0;j2<=m-3;j2++)
						{
							if((abs(i2-i1)>=3||abs(j2-j1)>=3)&&chk(i2,j2))
							{
								cout<<"Solution exists.\nThere are no jokers.\nPut the first square to ("<<i1+1<<", "<<j1+1<<").\nPut the second square to ("<<i2+1<<", "<<j2+1<<").\n";
								return 0;
							}
						}
					}
				}
			}
		}
		cout<<"No solution.\n";
		return 0;
	}
	if(f==1)
	{
      		// Jname 为  Joker的名称 (J1 或 J2)
		if(J1x==-1) Jname="J2";
		else Jname="J1";
        	//将 Joker 的坐标记录在 J1 的 x,y 坐标里
		J1x=J1x+J2x+1;
		J1y=J1y+J2y+1;
		for(int J1=0;J1<52;J1++)
		{
			if(isvaild(CARD[J1]))
			{
				c[J1x][J1y]=CARD[J1];
				for(int i1=0;i1<=n-3;i1++)
				{
					for(int j1=0;j1<=m-3;j1++)
					{
						if(chk(i1,j1))
						{
							for(int i2=0;i2<=n-3;i2++)
							{
								for(int j2=0;j2<=m-3;j2++)
								{
									if((abs(i2-i1)>=3||abs(j2-j1)>=3)&&chk(i2,j2))
									{
										cout<<"Solution exists.\nReplace "<<Jname<<" with "<<CARD[J1]<<".\nPut the first square to ("<<i1+1<<", "<<j1+1<<").\nPut the second square to ("<<i2+1<<", "<<j2+1<<").\n";
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
		cout<<"No solution.\n";
		return 0;
	}
	if(f==2)
 	{
		for(int J1=0;J1<52;J1++)
		{
			for(int J2=0;J2<52;J2++)
			{
				if(J1!=J2&&isvaild(CARD[J1])&&isvaild(CARD[J2]))
				{
					c[J1x][J1y]=CARD[J1];
					c[J2x][J2y]=CARD[J2];
					for(int i1=0;i1<=n-3;i1++)
					{
						for(int j1=0;j1<=m-3;j1++)
						{
							if(chk(i1,j1))
							{
								for(int i2=0;i2<=n-3;i2++)
								{
									for(int j2=0;j2<=m-3;j2++)
									{
										if((abs(i2-i1)>=3||abs(j2-j1)>=3)&&chk(i2,j2))
										{
											cout<<"Solution exists.\nReplace J1 with "<<CARD[J1]<<" and J2 with "<<CARD[J2]<<"."<<"\nPut the first square to ("<<i1+1<<", "<<j1+1<<").\nPut the second square to ("<<i2+1<<", "<<j2+1<<").\n";
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		cout<<"No solution.\n";
		return 0;
	}
	return 0;
}

```



---

## 作者：Rushroom (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF71D)

#### 暴力模拟水题

思路如下：

读入数据，记录王的数量和位置；

枚举没有出现过的牌，把王替换掉，然后 $\operatorname{check}$ ；

然而 $\operatorname{check}$ 有亿点麻烦：

用四重循环枚举两个正方形的左上角位置，用朴素方法判断是否花色一样或是数字互不相同，如果满足就输出答案（ $\operatorname{end}$ ）

 $\operatorname{check}$ 代码如下：
 
 ```cpp
void check()
{
    int cnt1 = -5, cnt2 = -5;
    rep(x, n - 2)
    {
        rep(y, m - 2)
        {
            if (ok)
                return;
            if (x < cnt1 + 3 && y < cnt2 + 3)
                continue;
            bool suc = 1;
            char ch;
            forr(i, x, x + 3)
            {
                forr(j, y, y + 3)
                {
                    if (i == x && j == y)
                        ch = s[i][j][1];
                    else if (ch != s[i][j][1])
                        suc = 0;
                }
            }
            if (suc == 1)
            {
                if (cnt1 == -5)
                {
                    cnt1 = x, cnt2 = y;
                }
                else
                    end(cnt1, cnt2, x, y);
                continue;
            }
            if (ok)
                return;
            suc = 1;
            map<char, bool> mc;
            forr(i, x, x + 3)
            {
                forr(j, y, y + 3)
                {
                    if (mc[s[i][j][0]])
                        suc = 0;
                    mc[s[i][j][0]] = 1;
                }
            }
            if (suc == 1)
            {
                if (cnt1 == -5)
                {
                    cnt1 = x, cnt2 = y;
                }
                else
                    end(cnt1, cnt2, x, y);
            }
            if (ok)
                return;
        }
    }
}
```
最后要注意输出格式，不要漏空格

完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define ld long double
#define forr(i, a, n) for (int i = a; i < n; i++)
#define rep(i, n) forr(i, 0, n)
#define repp(i, n) forr(i, 1, n + 1)
#define foreach(it, t) for (__typeof(t.begin()) it = t.begin(); it != t.end(); it++)
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
#define init(a, i) memset(a, i, sizeof(a))
#define pii pair<int, int>
#define vvi vector<vector<int>>
#define MAXN 0x3f3f3f3f
string a[] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
string b[] = {"C", "D", "H", "S"};
int n, m;
int num = 0;
string st, st1, st2;
string s[20][20];
map<string, int> mm;
int jx1 = -1, jy1 = -1, jx2 = -1, jy2 = -1;
int sim;
bool ok = 0;
void end(int x1, int y1, int x2, int y2)
{
    cout << "Solution exists.\n";
    if (num == 0)
    {
        cout << "There are no jokers.\n";
    }
    if (num == 1)
    {
        cout << "Replace J" << sim << " with " << st << ".\n";
    }
    if (num == 2)
    {
        cout << "Replace J1 with " << st1 << " and J2 with " << st2 << ".\n";
    }
    cout << "Put the first square to (" << x1 + 1 << ", " << y1 + 1 << ").\n";
    cout << "Put the second square to (" << x2 + 1 << ", " << y2 + 1 << ").\n";
    ok = 1;
}
void check()
{
    int cnt1 = -5, cnt2 = -5;
    rep(x, n - 2)
    {
        rep(y, m - 2)
        {
            if (ok)
                return;
            if (x < cnt1 + 3 && y < cnt2 + 3)
                continue;
            bool suc = 1;
            char ch;
            forr(i, x, x + 3)
            {
                forr(j, y, y + 3)
                {
                    if (i == x && j == y)
                        ch = s[i][j][1];
                    else if (ch != s[i][j][1])
                        suc = 0;
                }
            }
            if (suc == 1)
            {
                if (cnt1 == -5)
                {
                    cnt1 = x, cnt2 = y;
                }
                else
                    end(cnt1, cnt2, x, y);
                continue;
            }
            if (ok)
                return;
            suc = 1;
            map<char, bool> mc;
            forr(i, x, x + 3)
            {
                forr(j, y, y + 3)
                {
                    if (mc[s[i][j][0]])
                        suc = 0;
                    mc[s[i][j][0]] = 1;
                }
            }
            if (suc == 1)
            {
                if (cnt1 == -5)
                {
                    cnt1 = x, cnt2 = y;
                }
                else
                    end(cnt1, cnt2, x, y);
            }
            if (ok)
                return;
        }
    }
}
void solve()
{
    cin >> n >> m;
    rep(i, n) rep(j, m)
    {
        cin >> s[i][j];
        if (isdigit(s[i][j][1]))
        {
            num++;
            sim = s[i][j][1] - '0';
            if (sim == 1)
            {
                jx1 = i, jy1 = j;
            }
            else
            {
                jx2 = i, jy2 = j;
            }
        }
        else
            mm[s[i][j]] = 1;
    }
    if (num == 0)
        check();
    if (num == 1)
    {
        rep(i, 13)
        {
            rep(j, 4)
            {
                if (ok)
                    return;
                st = "" + a[i] + b[j];
                if (!mm[st])
                {
                    mm[st] = 1;
                    if (sim == 1)
                        s[jx1][jy1] = st;
                    else
                        s[jx2][jy2] = st;
                    check();
                    mm[st] = 0;
                }
            }
        }
    }
    if (num == 2)
    {
        rep(i, 13)
        {
            rep(j, 4)
            {
                st1 = "" + a[i] + b[j];
                if (mm[st1])
                    continue;
                mm[st1] = 1;
                s[jx1][jy1] = st1;
                rep(ii, 13)
                {
                    rep(jj, 4)
                    {
                        if (ok)
                            return;
                        st2 = "" + a[ii] + b[jj];
                        if (!mm[st2])
                        {
                            mm[st2] = 1;
                            s[jx2][jy2] = st2;
                            check();
                            mm[st2] = 0;
                        }
                    }
                }
                mm[st1] = 0;
            }
        }
    }
    if (!ok)
        cout << "No solution.\n";
}
int main()
{
    int T;
    T = 1;
    //cin>>T;
    while (T--)
        solve();
    return 0;
}
```


---

## 作者：YFF1 (赞：1)

## 思路：
观察到数据范围，我们可以枚举小丑用不同的卡牌去替代，然后用专门的函数去判断替换后的整个矩阵是否符合要求以及矩形的位置。需要注意的是，应该判断两个矩阵是否有重合。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,x1,x2,y1,y2;
string s[25][25];
string c[14]={"","2","3","4","5","6","7","8","9","T","J","Q","K","A"},c2[15]={"","C", "D","H","S"};
map<string,bool>mp;
void check(){
	x1=x2=y1=y2=0;
	for(int i=1;i<=n-2;i++){
		for(int j=1;j<=m-2;j++){ 
			bool b[105]={"0"},f1=1,f2=1;
			char ans='.';
			for(int k=i;k<=i+2;k++){
				for(int z=j;z<=j+2;z++){ 
					char c=s[k][z][0];
					char c2=s[k][z][1];
					if(ans!=c2){
						if(ans=='.')ans=c2;
						else f2=0;
					}
					if(b[c-'0']==0)b[c-'0']=1;
					else f1=0;//矩阵1号是否符合要求 
				}
			}//矩阵1号 
			if(f1==1||f2==1){
				bool f3,f4;
				bool b3[105][105]={"0"};
				for(int x=max(i-2,1);x<=i+2;x++){
					for(int y=max(j-2,1);y<=j+2;y++)b3[x][y]=1;
				}
				for(int a=1;a<=n-2;a++){
					for(int b=1;b<=m-2;b++){//矩阵2号 
						if(b3[a][b]==1)continue;
						bool b2[105]={"0"};
						f3=1,f4=1;
						char ans2='.';
						for(int k2=a;k2<=a+2;k2++){
							for(int z2=b;z2<=b+2;z2++){
								char c=s[k2][z2][0];
								char c2=s[k2][z2][1];
								if(ans2!=c2){
									if(ans2=='.')ans2=c2;
									else f3=0;
								}
								if(b2[c-'0']==0)b2[c-'0']=1;
								else f4=0;
							}//矩阵2号是否符合要求 
						}
						if(f3==1||f4==1){
							x1=i;
							y1=j;
							x2=a;
							y2=b;
						}
					}
				} 
			}
		}
	}
}
int main () {
	cin>>n>>m;
	bool can=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
			mp[s[i][j]]=1;
			if(s[i][j]=="J1"||s[i][j]=="J2")can=1;
		}
	}
	if(can==0){
		check();
		if(x1==0&&x2==0&&y1==0&&y2==0)cout<<"No solution.";
		else {
			cout<<"Solution exists."<<endl;
			cout<<"There are no jokers."<<endl;
			cout<<"Put the first square to ("<<x1<<","<<" "<<y1<<')'<<'.'<<endl;
			cout<<"Put the second square to ("<<x2<<","<<" "<<y2<<')'<<'.'<<endl;
		}
	}
	else {
		int pos1=0,pos2=0,pos3=0,pos4=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(s[i][j]=="J1")pos1=i,pos2=j;
				else if(s[i][j]=="J2")pos3=i,pos4=j;
			}
		}
		if(pos1!=0&&pos2!=0){
			if(pos3==0&&pos4==0){
				for(int i=1;i<=13;i++){
					for(int j=1;j<=4;j++){
						string xin="";
						xin+=c[i]+c2[j];
						if(mp[xin]==1)continue;//小丑用不同的卡牌替代 
						s[pos1][pos2]=xin;
						check();
						if(x1!=0&&x2!=0&&y1!=0&&y2!=0){
							cout<<"Solution exists."<<endl;
							cout<<"Replace J1 with "<<xin<<"."<<endl;
							cout<<"Put the first square to ("<<x1<<","<<" "<<y1<<')'<<'.'<<endl;
							cout<<"Put the second square to ("<<x2<<","<<" "<<y2<<')'<<'.'<<endl;
							return 0;
						}		
					}
				}
			}
			else{
				for(int i=1;i<=13;i++){
					for(int j=1;j<=4;j++){
						string xin="";
						xin+=c[i]+c2[j];
						if(mp[xin]==1)continue;
						s[pos1][pos2]=xin;//小丑用不同的卡牌替代 
						for(int k=1;k<=13;k++){
							for(int z=1;z<=4;z++){
								string xin2="";
								xin2+=c[k]+c2[z];
								if(mp[xin2]==1)continue;
								if(xin2==xin)continue;
								s[pos3][pos4]=xin2;
								check();
								if(x1!=0&&x2!=0&&y1!=0&&y2!=0){
									cout<<"Solution exists."<<endl;
									cout<<"Replace J1 with "<<xin<<" "<<"and J2 with "<<xin2<<'.'<<endl;
									cout<<"Put the first square to ("<<x1<<","<<" "<<y1<<')'<<'.'<<endl;
									cout<<"Put the second square to ("<<x2<<","<<" "<<y2<<')'<<'.'<<endl;
									return 0;
								}	
							}
						}	
					}
				}
			}
		}
		else{
			for(int i=1;i<=13;i++){
				for(int j=1;j<=4;j++){
					string xin="";
					xin+=c[i]+c2[j];
					if(mp[xin]==1)continue;
					s[pos3][pos4]=xin;
					check();
					if(x1!=0&&x2!=0&&y1!=0&&y2!=0){
						cout<<"Solution exists."<<endl;
						cout<<"Replace J2 with "<<xin<<"."<<endl;
						cout<<"Put the first square to ("<<x1<<","<<" "<<y1<<')'<<'.'<<endl;
						cout<<"Put the second square to ("<<x2<<","<<" "<<y2<<')'<<'.'<<endl;
						return 0;
					}		
				}
			}
		}
		cout<<"No solution.";
	}
	return 0;
} 
```

---

## 作者：Mo20 (赞：1)

#### 给管理员的前言：本蒟蒻的第一篇题解，望通过。
# 题意 #
给出一个 $n \times m$ 的矩阵，其中每个位置给出一种扑克牌。
在该矩阵中找到两个不重叠的 $3 \times 3$ 的矩阵使得其中扑克牌要么编号各不相同，要不花色完全一致。

特别的，扑克牌中的大小王可以被替换为任意一种**没有出现过**的扑克牌。

题目保证所有扑克牌各不相同。

# 思路 #

由于答案的两个矩阵不重叠，那么最复杂的一种情况：即两个答案矩阵共用小丑牌是不可能的，于是哪些 $3 \times 3$ 矩阵是合法的（即可以成为答案）是可以被预处理的。

具体来说对于每个矩阵，统计出现过的花色和数字，遇到大小王直接跳过，若花色只有一种或数字各不相同，则该矩阵为理论可行的答案矩阵。

简单计算最多可能出现的答案矩阵数量，由于 $52$ 张扑克牌各不相同，故矩阵数量肯定严格小于 $52$ 。而当 $n=52$ 时，直接枚举两个矩阵是否相互不重叠的复杂度 $O(n^2)$ 是完全可以接受的。

#### 更精确的数值如下，不想要“严谨”证明的可以跳过。

我们设一个答案矩阵中心点坐标为 $(x,y)$ ，当 $1\lt x \lt n$ 且 $1 \lt y \lt m$ 时该矩阵可能合法（越界了就连 $3 \times 3$ 矩阵都算不上了嘛）。

那么反之，外围一圈的点一定不可能作为答案矩阵中心，为了使答案尽量多，总牌数量应尽量趋近 $ 52 $ 。再结合上述论证，整体的周长应尽量短，这就是初中的经典积定求最小和问题嘛，用式子表达即：

$$
\begin{cases}
x \times y \leq 52\\ 
x+y \geq 2 \times  \lfloor  \sqrt{52} \rfloor = 14\\
\end{cases}
$$

那么减去周长后内层最多还剩 $26$ 个合法中心，再结合数据只能为整数实际情况最多中心的情况应该是 $7 \times 7$ 矩阵的内侧 $21$ 个中心。

又因为扑克牌各不相同，我们先考虑花色相同对答案的贡献，使 $4$ 种花色的 $13$ 种牌彼此相邻显然能提供更多的内部花色相同答案矩形。

那么对于内部数字的排列，为了在跨颜色区域内依然有答案存在，由于要求答案矩阵 $3 \times 3$ 内数字各不相同，用数独的思想我们很容易构造以下**一类**矩阵，拥有 $14$ 个左右的答案矩阵。

||||||||
|----|----|----|----|----|----|----|
| AC | 2C | 3C | TS | 7S | 8S | 9S |
| 4C | 5C | 6C | JS | 4S | 5S | 6S |
| 7C | 8C | 9C | QS | AS | 2S | 3S |
| TC | JC | QC | J1 | TH | JH | QH |
| AD | 2D | 3D | TD | 4H | 6H | 9H |
| 4D | 5D | 6D | JD | 2H | 5H | 8H |
| 7D | 8D | 9D | QD | AH | 4H | 7H |


#### 言归正传

将所有独立合法的答案矩阵存进一个数组后依次枚举两个矩阵。

如果这两个矩阵在位置上合法，即没有两矩阵没有重合部分，则 $\vert x_1 - x_2 \vert \gt 2$ 和 $\vert y_1 - y_2 \vert \gt 2$ 之中至少有一者成立。

在判断完是否重合后，我们再分别研究这两个答案矩阵中大小王的取值。

由于在判断一个矩阵是否可能为答案矩阵时已经阐述过判定方法，就不再赘述了。

如果一个矩阵是通过颜色相同成为答案矩阵的，则锁定该矩阵中小王的花色，枚举数字看该扑克牌是否出现过。

反之如果一个矩阵是通过编号不同，则枚举全部扑克牌，若数字并未出现在该矩阵中则为大小王的合法取值。

值得一提的是此题有许多坑点：

- 一个矩阵可以在颜色相同的同时保持不同数字，故枚举完颜色相同的情况后不能简单跳过数字枚举的过程。
- 大小王即使没有用到也需要输出更换取值，甚至如果没有空余扑克牌此情况会变为“No solution”。

多注意细节还是能轻松码出这题的 ~~（本蒟蒻调了3个小时）~~，于是就愉快的AC了一道蓝题啦~。

Code:[400行诗代码](https://codeforces.com/contest/71/submission/215465390)

---

## 作者：PDAST (赞：1)

## 题意
一副扑克牌，铺成一个 $N \times M$ 的矩阵，有 `C、D、H、S` 四种花色和 `2、3、4、5、6、7、8、9、T、J、Q、K、A` 十三种点数，构成 $52$ 张牌，另外加上两张地主牌，记作 `J1` 与 `J2`。我们定义一个规则：在矩阵中能找到两个及以上不重叠的 $3 \times 3$ 的矩阵，每个矩阵中每张牌的花色全部相同或点数没有相同的。你可以将地主牌换成没有在场上的任意一张牌，使这个矩阵满足上文的规则。请问，规则能被满足吗？如果可以，要把地主牌换成什么牌？两个矩阵的左上角分别在哪？
## 思路
纯纯的大模拟，没什么的好说的，就是一道纯粹的，不带也能和优化的模拟题！直接预处理能放的牌，枚举大小王换什么牌，并判断是否可行最后输出即可。
## 实现
预处理所有的牌，判出能换上的牌，找到大小王，接着循环，每次把大小王都换成枚举到的牌，再依次判断是否满足规则，将符合规则的存储起来，接着枚举是否有两个满足条件的矩阵不重合，遇到不重合的按题目要求的格式输出即可，我的代码稍微长了些，一百二十行，长度两千五百左右。
## 代码
~~~cpp
//找到joker的位置
//如果有
//	枚举joker会变成的牌
//		寻找满足条件的3*3的矩阵
//		输出
//	若找不到
//		输出不可能
//否则
//	直接寻找 
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
pair<char,char>card[101][101];
string flower[4]={"C","D","H","S"},number[13]={"A","2","3","4","5","6","7","8","9","T","J","Q","K"};
string cards[101],can[101];
map<string,bool>mp;
int n,m,j1x,j1y,j2x,j2y,k,cnt,ex1,ey1,ex2,ey2,f;
pair<int,int>ans[101];
void print(int x1,int yl,int x2,int y2,int a,int b){
	cout<<"Solution exists.\n";
	if(!j1x&&!j2x){
		cout<<"There are no jokers.\n";
	}
	if(j1x&&!j2x){
		cout<<"Replace J1 with "<<can[a]<<".\n";
	}
	if(!j1x&&j2x){
		cout<<"Replace J2 with "<<can[b]<<".\n";
	}
	if(j1x&&j2x){
		cout<<"Replace J1 with "<<can[a]<<" and J2 with "<<can[b]<<".\n";
	}
	cout<<"Put the first square to ("<<x1<<", "<<yl<<").\n";
	cout<<"Put the second square to ("<<x2<<", "<<y2<<").";
}
bool check(int bx,int by){
	if(n-bx+1<3||m-by+1<3){
		return 0;
	}
	char ch=card[bx][by].y;
	bool f1=1,f2=1;
	int s=0;
	map<char,bool>che;
	for(int i=bx;i<=bx+2;i++){
		for(int j=by;j<=by+2;j++){
			if(ch!=card[i][j].y){
				f1=0;
			}
			if(che[card[i][j].x]){
				f2=0;
			}
			if(card[i][j].x){
				s++;
			}
			che[card[i][j].x]=1;
		}
	}
	return (f1||f2);
}
int main(){
//	freopen("input.txt","r",stdin);
	for(int i=0;i<4;i++){
		for(int j=0;j<13;j++){
			cards[++k]=number[j]+flower[i];
		}
	}
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			string st;
			cin>>st;
			if(st=="J1"||st=="J2"){
				if(st=="J1"){
					j1x=i;
					j1y=j;
				}else{
					j2x=i;
					j2y=j;
				}
			}else{
				card[i][j]={st[0],st[1]};
				mp[st]=1;
			}
		}
	}
	for(int i=1;i<=k;i++){
		if(!mp[cards[i]]){
			can[++cnt]=cards[i];
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
			if(i==j){
				continue;
			}
			char t1=(char)(can[i][0]),t2=(char)(can[i][1]),t3=(char)(can[j][0]),t4=(char)(can[j][1]);
			card[j1x][j1y]={t1,t2};
			card[j2x][j2y]={t3,t4};
			int ansnum=0;
			for(int a=1;a<=n;a++){
				for(int b=1;b<=m;b++){
					if(check(a,b)){
						ans[++ansnum]={a,b};
					}
				}
			}
			for(int a=1;a<=ansnum;a++){
				for(int b=1;b<=ansnum;b++){
					if(abs(ans[a].x-ans[b].x)>=3||abs(ans[a].y-ans[b].y)>=3){
						print(ans[a].x,ans[a].y,ans[b].x,ans[b].y,i,j);
						return 0;
					}
				}
			}
		}
	}
	cout<<"No solution.";
	return 0;
}
~~~

---

## 作者：Anby_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF71D)

这道题就是一个暴力搜索，把 $J1$ 或 $J2$ 换成别的牌，比较麻烦的是两个 $3 \times 3$ 的方格要判断。

### 判断是否重叠
可以理解为把**两个方格染色**判断 总染色块数 $x = 18$ 。

代码如下（仅供参考）:

```cpp
bool check(int xx,int yy,int xxx,int yyy){
	map<pii,bool> mp1;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) mp1[{xx+i,yy+j}]=1;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) mp1[{xxx+i,yyy+j}]=1;
	if(mp1.size()==18) return 1;
	return 0;
}
```

### 判断花色是否一致
就很简单，爆枚，开有没有**两个方格花色不同**。

代码如下（仅供参考）:
```cpp
bool hs(int x,int y){
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++)
			if(g[x][y][1]!=g[x+i][y+j][1])
				return 0;
	return 1;
}
```

### 判断数字是否不同
同样，可以采用**染色**的方法。

代码如下（仅供参考）:
```cpp
bool sz(int x,int y){
	map<int,bool> mp1;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) mp1[g[x+i][y+j][0]]=1;
	if(mp1.size() == 9) return 1;
	return 0;
}
```
### 最终代码：

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=30+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*
4 6
2S 3S 4S 7S 8S AS
5H 6H 7H 5S TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C
*/
map<string,bool> mp;
int j1x,j1y,j2x,j2y;
string g[N][N];
bool check(int xx,int yy,int xxx,int yyy){
	map<pii,bool> mp1;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) mp1[{xx+i,yy+j}]=1;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) mp1[{xxx+i,yyy+j}]=1;
	if(mp1.size()==18) return 1;
	return 0;
}
bool hs(int x,int y){
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++)
			if(g[x][y][1]!=g[x+i][y+j][1])
				return 0;
	return 1;
}
bool sz(int x,int y){
	map<int,bool> mp1;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) mp1[g[x+i][y+j][0]]=1;
	if(mp1.size() == 9) return 1;
	return 0;
}
int main(){
	mp["2C"]=mp["2D"]=mp["2H"]=mp["2S"]=mp["3C"]=mp["3D"]=mp["3H"]=mp["3S"]=mp["4C"]=mp["4D"]=mp["4H"]=mp["4S"]=mp["5C"]=mp["5D"]=mp["5H"]=mp["5S"]=mp["6C"]=mp["6D"]=mp["6H"]=mp["6S"]=mp["7C"]=mp["7D"]=mp["7H"]=mp["7S"]=mp["8C"]=mp["8D"]=mp["8H"]=mp["8S"]=mp["9C"]=mp["9D"]=mp["9H"]=mp["9S"]=mp["TC"]=mp["TD"]=mp["TH"]=mp["TS"]=mp["JC"]=mp["JD"]=mp["JH"]=mp["JS"]=mp["QC"]=mp["QD"]=mp["QH"]=mp["QS"]=mp["KC"]=mp["KD"]=mp["KH"]=mp["KS"]=mp["AC"]=mp["AD"]=mp["AH"]=mp["AS"]=0;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>g[i][j];
			if(g[i][j]=="J1") j1x=i,j1y=j;
			else if(g[i][j]=="J2") j2x=i,j2y=j;
			else mp[g[i][j]]=1;
		}
	}
	for(auto m1:mp){
		if(m1.y) continue;
		g[j1x][j1y]=m1.x;
		mp[m1.x]=1;
		for(auto m2:mp){
			if(m2.y) continue;
			g[j2x][j2y]=m2.x;
			mp[m2.x]=1;
			for(int i=1;i<=n-2;i++){
				for(int j=1;j<=m-2;j++){
					if(hs(i,j)||sz(i,j)){
						for(int k=1;k<=n-2;k++){
							for(int l=1;l<=m-2;l++){
								if(!check(i,j,k,l)) continue;
								if(hs(k,l)||sz(k,l)){
									cout<<"Solution exists.\n";
									if(j1x&&j1y&&j2x&&j2y) cout<<"Replace J1 with "+m1.x+" and J2 with "+m2.x+".\n";
									else if(j1x&&j1y) cout<<"Replace J1 with "+m1.x+".\n";
									else if(j2x&&j2y) cout<<"Replace J2 with "+m2.x+".\n";
									else cout<<"There are no jokers.\n";
									printf("Put the first square to (%d, %d).\nPut the second square to (%d, %d).",i,j,k,l);
									return 0;
								}
							}
						}
					}
				}
			}
			mp[m2.x]=0;
		}
		mp[m1.x]=0;
	}
	printf("No solution.");
	return 0;
}

```


---

## 作者：LiQXing (赞：0)

比较清新的一道小模拟。

我们可以大力枚举大小王替换成的牌，然后对每一个 $3\times 3$ 的矩阵进行枚举，如果一个矩阵满足条件，那么就枚举第二个矩阵，注意第二个矩阵和第一个矩阵不能够有重合，如果两个矩阵都满足条件，就直接输出答案。

如何判断矩形是否满足条件，花色相同很简单，给每个花色打标记就行了，数字各不相同，可以考虑状压，判断是否二进制上有 $9$ 个一。

虽然代码看起来很多，实际上只有三分之一。

```cpp
#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define i64 long long
#define ull unsigned long long
#define ldb long double
#define db double
#define i128 __int128
#define up(a,b,c) for(int a=b;a<=c;a++)
#define dn(a,b,c) for(int a=b;a>=c;a--)
#define pii pair<int,int>
#define lc k<<1
#define rc k<<1|1
#define fi first
#define se second
#define endl '\n'

const int N=2e5+100,M=1e6+100;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
const ull uinf=1e18+14;

int n,m,k;
string tot[]={
"AC","AD","AH","AS","2C","2D","2H","2S","3C","3D","3H","3S","4C","4D","4H","4S",
"5C","5D","5H","5S","6C","6D","6H","6S","7C","7D","7H","7S","8C","8D","8H","8S",
"9C","9D","9H","9S","TC","TD","TH","TS","JC","JD","JH","JS","QC","QD","QH","QS",
"KC","KD","KH","KS"};
string a[22][22];
map<string,int>mp;
vector<int>num;
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    if(!(n>=6||m>=6)){
		cout<<"No solution.\n";
		return 0;
	}
    up(i,1,n){
        up(j,1,m){
            cin>>a[i][j];
            mp[a[i][j]]=1;
        }
    }
    if(!mp["J1"]&&!mp["J2"]){
        //点数
        up(i,1,n-2){
            up(j,1,m-2){
                int x=0,numc=0,numd=0,numh=0,nums=0;
                up(l,i,i+2){
                    up(r,j,j+2){
                        int t=a[l][r][0],p=a[l][r][0];
                        if(t=='A')t=1;
                        else if(t=='T')t=10;
                        else if(t=='J')t=11;
                        else if(t=='Q')t=12;
                        else if(t=='K')t=13;
                        else t=t-'0';
                        x|=(1<<t);
                        if(p=='C')numc=1;
                        if(p=='D')numd=1;
                        if(p=='H')numh=1;
                        if(p=='S')nums=1;
                    }
                }
                if(__builtin_popcountll(x)==9||(numc+numd+numh+nums)==1){
                    up(i2,1,n-2){
                        up(j2,1,m-2){
                            if(i2+2>=i&&i2<=i+2&&j2+2>=j&&j2<=j+2)continue;
                            int x2=0;
                            numc=0;numd=0;numh=0;nums=0;
                            up(l2,i2,i2+2){
                                up(r2,j2,j2+2){
                                    int t=a[l2][r2][0],p=a[l2][r2][0];
                                    if(t=='A')t=1;
                                    else if(t=='T')t=10;
                                    else if(t=='J')t=11;
                                    else if(t=='Q')t=12;
                                    else if(t=='K')t=13;
                                    else t=t-'0';
                                    x2|=(1<<t);
                                    if(p=='C')numc=1;
                                    if(p=='D')numd=1;
                                    if(p=='H')numh=1;
                                    if(p=='S')nums=1;
                                }
                            }
                            if(__builtin_popcountll(x2)==9||(numc+numd+numh+nums)==1){
                                cout<<"Solution exists."<<endl;
                                cout<<"There are no jokers."<<endl;
                                cout<<"Put the first square to ("<<i<<", "<<j<<")."<<endl;   
                                cout<<"Put the second square to ("<<i2<<", "<<j2<<")."<<endl;      
                                return 0;
                            } 
                        }
                    }
                }                
            }
        }          
        cout<<"No solution."<<endl;
        return 0;
    }
    if(mp["J1"]+mp["J2"]==1){
        int sx,sy;
        up(i,1,n){
            up(j,1,m){
                if(a[i][j]=="J1"||a[i][j]=="J2"){
                    sx=i;sy=j;
                    goto F;
                } 
            }
        }
        F:;
        up(pos,0,51){
            if(mp[tot[pos]])continue;
            a[sx][sy]=tot[pos];
            up(i,1,n-2){
                up(j,1,m-2){
                    int x=0,numc=0,numd=0,numh=0,nums=0;
                    up(l,i,i+2){
                        up(r,j,j+2){
                            int t=a[l][r][0],p=a[l][r][0];
                            if(t=='A')t=1;
                            else if(t=='T')t=10;
                            else if(t=='J')t=11;
                            else if(t=='Q')t=12;
                            else if(t=='K')t=13;
                            else t=t-'0';
                            x|=(1<<t);
                            if(p=='C')numc=1;
                            if(p=='D')numd=1;
                            if(p=='H')numh=1;
                            if(p=='S')nums=1;
                        }
                    }
                    if(__builtin_popcountll(x)==9||(numc+numd+numh+nums)==1){
                        up(i2,1,n-2){
                            up(j2,1,m-2){
                                if(i2+2>=i&&i2<=i+2&&j2+2>=j&&j2<=j+2)continue;
                                int x2=0;
                                numc=0;numd=0;numh=0;nums=0;
                                up(l2,i2,i2+2){
                                    up(r2,j2,j2+2){
                                        int t=a[l2][r2][0],p=a[l2][r2][0];
                                        if(t=='A')t=1;
                                        else if(t=='T')t=10;
                                        else if(t=='J')t=11;
                                        else if(t=='Q')t=12;
                                        else if(t=='K')t=13;
                                        else t=t-'0';
                                        x2|=(1<<t);
                                        if(p=='C')numc=1;
                                        if(p=='D')numd=1;
                                        if(p=='H')numh=1;
                                        if(p=='S')nums=1;
                                    }
                                }
                                if(__builtin_popcountll(x2)==9||(numc+numd+numh+nums)==1){
                                    cout<<"Solution exists."<<endl;
                                    cout<<"Replace "<<((mp["J1"]==1)?("J1"):("J2"))<<" with "<<tot[pos]<<"."<<endl;  
                                    cout<<"Put the first square to ("<<i<<", "<<j<<")."<<endl;   
                                    cout<<"Put the second square to ("<<i2<<", "<<j2<<")."<<endl;
                                    return 0;
                                } 
                            }
                        }
                    }                
                }
            }          
        }
        cout<<"No solution."<<endl;
        return 0;
    }
    int sx1,sy1,sx2,sy2;
    up(i,1,n){
        up(j,1,m){
            if(a[i][j]=="J1")sx1=i,sy1=j;
            if(a[i][j]=="J2")sx2=i,sy2=j;
        }
    }
    up(pos1,0,51){
        if(mp[tot[pos1]])continue;
        up(pos2,0,51){
            if(mp[tot[pos2]])continue;
            if(pos1==pos2)continue;
            a[sx1][sy1]=tot[pos1];
            a[sx2][sy2]=tot[pos2];
            up(i,1,n-2){
                up(j,1,m-2){
                    int x=0,numc=0,numd=0,numh=0,nums=0;
                    up(l,i,i+2){
                        up(r,j,j+2){
                            int t=a[l][r][0],p=a[l][r][0];
                            if(t=='A')t=1;
                            else if(t=='T')t=10;
                            else if(t=='J')t=11;
                            else if(t=='Q')t=12;
                            else if(t=='K')t=13;
                            else t=t-'0';
                            x|=(1<<t);
                            if(p=='C')numc=1;
                            if(p=='D')numd=1;
                            if(p=='H')numh=1;
                            if(p=='S')nums=1;
                        }
                    }
                    if(__builtin_popcountll(x)==9||(numc+numd+numh+nums)==1){
                        up(i2,1,n-2){
                            up(j2,1,m-2){
                                if(i2+2>=i&&i2<=i+2&&j2+2>=j&&j2<=j+2)continue;
                                int x2=0;
                                numc=0;numd=0;numh=0;nums=0;
                                up(l2,i2,i2+2){
                                    up(r2,j2,j2+2){
                                        int t=a[l2][r2][0],p=a[l2][r2][0];
                                        if(t=='A')t=1;
                                        else if(t=='T')t=10;
                                        else if(t=='J')t=11;
                                        else if(t=='Q')t=12;
                                        else if(t=='K')t=13;
                                        else t=t-'0';
                                        x2|=(1<<t);
                                        if(p=='C')numc=1;
                                        if(p=='D')numd=1;
                                        if(p=='H')numh=1;
                                        if(p=='S')nums=1;
                                    }
                                }
                                if(__builtin_popcountll(x2)==9||(numc+numd+numh+nums)==1){
                                    cout<<"Solution exists.\nReplace J1 with "<<tot[pos1]<<" and J2 with "<<tot[pos2]<<"."<<"\nPut the first square to ("<<i<<", "<<j<<").\nPut the second square to ("<<i2<<", "<<j2<<").\n";
                                    return 0;
                                } 
                            }
                        }
                    }                
                }
            }          
        }
    }
    cout<<"No solution."<<endl;
	return 0;
}
```

---

## 作者：Sexy_Foxy (赞：0)

## 题意：

给你有 $n \times m$ 张扑克牌组成的矩形的牌堆，求换掉牌堆中所有的大小王（换大小王的牌不能和牌堆中现有的牌重复）以后，牌堆中是否存在两个 $3 \times 3$ 大小的不重叠的矩阵中的扑克牌**花色一致**或**点数互不相同**。

## 解题思路：

由题意不难看出，本题所求问题是将大小王换掉后，暴力求出题目所需的两个矩阵。

### 第一步：

首先看一下数据范围， $(3≤n,m≤17,n×m≤52)$ ，非常小，可以用暴力求解，不需要什么优化之类的。

### 第二步：

大致思路有了，先**分类讨论**一下：

1.牌堆中没有大小王

2.牌堆中一张大小王

3.牌堆中两张大小王

我们要在输入时就保存大小王的坐标和数量。

### 第三步：

前言：本题注重考察码力，所以题解偏重于代码讲解。

#### 定义：

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAX=21;
const string card[]={"AC","AD","AH","AS","2C","2D","2H","2S","3C","3D","3H","3S","4C","4D","4H","4S","5C","5D","5H","5S","6C","6D","6H","6S","7C","7D","7H","7S","8C","8D","8H","8S","9C","9D","9H","9S","TC","TD","TH","TS","JC","JD","JH","JS","QC","QD","QH","QS","KC","KD","KH","KS"}; //所有牌的种类
string a[MAX][MAX];
vector<string>card_line; //保存原有牌，便于判断
int n,m;
```

#### 输入+预处理：

```c++
scanf("%d%d",&n,&m);
int J1_x,J1_y,J2_x,J2_y,sum=0,J_flag=false;
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=m;j++)
	{
		cin>>a[i][j];
		if(a[i][j]=="J1")
		{
			sum++; //大小王数量+1
			J1_x=i,J1_y=j,J_flag=true; //记录坐标并标记牌堆中有大小王
		}
		else if(a[i][j]=="J2") //小王同理
		{
			sum++;
			J2_x=i,J2_y=j;
		}
		else
		{
			card_line.push_back(a[i][j]); //将牌加入数组
		}
	}
}
```

#### 判断牌是否用过：

```c++
bool no_use(string s)
{
	for(int i=0;i<card_line.size();i++) //遍历存牌的数组
	{
		if(card_line[i]==s) //如果相同就退出
		{
			return false;
		}
	}
	return true; //没有任何牌相同说明可以
}
```

#### 判断 $3 \times 3$ 矩阵是否满足题意所需：

```c++
bool check(int x,int y)
{
	int sum=0; //判断点数相同的
	set<char>line; //去重，用于判断花色是否不同
	for(int i=x;i<=x+2;i++)
	{
		for(int j=y;j<=y+2;j++)
		{
			if(a[i][j][1]==a[x][y][1]) //如果点数相同，就+1
			{
				sum++;
			}
			line.insert(a[i][j][0]); //将花色插入set容器中
		}
	}
	return (sum==9||line.size()==9); //判断两个条件是否满足至少其一
}
```

#### 如果一张大小王都没有：

```c++
if(sum==0)
{
	for(int xx1=1;xx1<=n-2;xx1++) //枚举第一个符合题意的3×3矩阵
	{
		for(int yy1=1;yy1<=m-2;yy1++)
		{
			if(check(xx1,yy1)) //符合题意就找第二个符合题意的3×3矩阵
			{
				for(int xx2=1;xx2<=n-2;xx2++)
				{
					for(int yy2=1;yy2<=m-2;yy2++)
					{
						if(check(xx2,yy2)&&(abs(xx1-xx2)>=3||abs(yy1-yy2)>=3)) //如果两个符合题意的矩阵不重叠
						{
							printf("Solution exists.\nThere are no jokers.\nPut the first square to (%d, %d).\nPut the second square to (%d, %d).",xx1,yy1,xx2,yy2);
							return 0;
						}
					}
				}
			}
		}
	}
}
```

#### 如果只有一张大小王：

```c++
else if(sum==1)
{
	int x,y;
	J_flag?x=J1_x:x=J2_x; //判断是大王还是小王
	J_flag?y=J1_y:y=J2_y;
	for(int i=0;i<52;i++) //枚举没用过的牌
	{
		if(no_use(card[i])) 
		{				
			a[x][y]=card[i];
			for(int xx1=1;xx1<=n-2;xx1++) //枚举第一个符合题意的3×3矩阵
			{
				for(int yy1=1;yy1<=m-2;yy1++)
				{
					if(check(xx1,yy1)) //符合题意就找第二个符合题意的3×3矩阵
					{
						for(int xx2=1;xx2<=n-2;xx2++)
						{
							for(int yy2=1;yy2<=m-2;yy2++)
							{
								if(check(xx2,yy2)&&(abs(xx1-xx2)>=3||abs(yy1-yy2)>=3)) //如果两个符合题意的矩阵不重叠
								{
									printf("Solution exists.\nReplace ");
									J_flag?printf("J1"):printf("J2");
									printf(" with ");
									cout<<card[i];
									printf(".\nPut the first square to (%d, %d).\nPut the second square to (%d, %d).",xx1,yy1,xx2,yy2);
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
}
```

#### 如果两张大小王都有：

```c++
else
{
	for(int i=0;i<52;i++) //枚举替换大王的牌
	{
		for(int j=0;j<52;j++) //枚举替换小王的牌
		{
			if(i!=j)
			{
				if(no_use(card[i])&&no_use(card[j]))
				{
					a[J1_x][J1_y]=card[i],a[J2_x][J2_y]=card[j]; //替换大小王
					for(int xx1=1;xx1<=n-2;xx1++)
					{
						for(int yy1=1;yy1<=m-2;yy1++) //枚举第一个符合题意的3×3矩阵
						{
							if(check(xx1,yy1)) //符合题意就找第二个符合题意的3×3矩阵
							{
								for(int xx2=1;xx2<=n-2;xx2++)
								{
									for(int yy2=1;yy2<=m-2;yy2++)
									{
										if(check(xx2,yy2)&&(abs(xx1-xx2)>=3||abs(yy1-yy2)>=3)) //如果两个符合题意的矩阵不重叠
										{
											printf("Solution exists.\nReplace J1 with ");
											cout<<card[i];
											printf(" and J2 with ");
											cout<<card[j];
											printf(".\nPut the first square to (%d, %d).\nPut the second square to (%d, %d).",xx1,yy1,xx2,yy2);
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
```

#### 总结：

本题思维难度很低，但代码长，考验码力，打代码时要认真！

## 完整的Code：

不要随便抄题解，小心被**棕**！

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAX=21;
const string card[]={"AC","AD","AH","AS","2C","2D","2H","2S","3C","3D","3H","3S","4C","4D","4H","4S","5C","5D","5H","5S","6C","6D","6H","6S","7C","7D","7H","7S","8C","8D","8H","8S","9C","9D","9H","9S","TC","TD","TH","TS","JC","JD","JH","JS","QC","QD","QH","QS","KC","KD","KH","KS"};
string a[MAX][MAX];
vector<string>card_line;
int n,m;
bool no_use(string s)
{
	for(int i=0;i<card_line.size();i++)
	{
		if(card_line[i]==s)
		{
			return false;
		}
	}
	return true;
}
bool check(int x,int y)
{
	int sum=0;
	set<char>line;
	for(int i=x;i<=x+2;i++)
	{
		for(int j=y;j<=y+2;j++)
		{
			if(a[i][j][1]==a[x][y][1])
			{
				sum++;
			}
			line.insert(a[i][j][0]);
		}
	}
	return (sum==9||line.size()==9);
}
int main()
{
	scanf("%d%d",&n,&m);
	int J1_x,J1_y,J2_x,J2_y,sum=0,J_flag=false;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=="J1")
			{
				sum++;
				J1_x=i,J1_y=j,J_flag=true;
			}
			else if(a[i][j]=="J2")
			{
				sum++;
				J2_x=i,J2_y=j;
			}
			else
			{
				card_line.push_back(a[i][j]);
			}
		}
	}
	if(n<6&&m<6)
	{
		printf("No solution.");
		return 0;
	}
	if(sum==0)
	{
		for(int xx1=1;xx1<=n-2;xx1++)
		{
			for(int yy1=1;yy1<=m-2;yy1++)
			{
				if(check(xx1,yy1))
				{
					for(int xx2=1;xx2<=n-2;xx2++)
					{
						for(int yy2=1;yy2<=m-2;yy2++)
						{
							if(check(xx2,yy2)&&(abs(xx1-xx2)>=3||abs(yy1-yy2)>=3))
							{
								printf("Solution exists.\nThere are no jokers.\nPut the first square to (%d, %d).\nPut the second square to (%d, %d).",xx1,yy1,xx2,yy2);
								return 0;
							}
						}
					}
				}
			}
		}
	}
	else if(sum==1)
	{
		int x,y;
		J_flag?x=J1_x:x=J2_x;
		J_flag?y=J1_y:y=J2_y;
		for(int i=0;i<52;i++)
		{
			if(no_use(card[i]))
			{				
				a[x][y]=card[i];
				for(int xx1=1;xx1<=n-2;xx1++)
				{
					for(int yy1=1;yy1<=m-2;yy1++)
					{
						if(check(xx1,yy1))
						{
							for(int xx2=1;xx2<=n-2;xx2++)
							{
								for(int yy2=1;yy2<=m-2;yy2++)
								{
									if(check(xx2,yy2)&&(abs(xx1-xx2)>=3||abs(yy1-yy2)>=3))
									{
										printf("Solution exists.\nReplace ");
										J_flag?printf("J1"):printf("J2");
										printf(" with ");
										cout<<card[i];
										printf(".\nPut the first square to (%d, %d).\nPut the second square to (%d, %d).",xx1,yy1,xx2,yy2);
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for(int i=0;i<52;i++)
		{
			for(int j=0;j<52;j++)
			{
				if(i!=j)
				{
					if(no_use(card[i])&&no_use(card[j]))
					{
						a[J1_x][J1_y]=card[i],a[J2_x][J2_y]=card[j];
						for(int xx1=1;xx1<=n-2;xx1++)
						{
							for(int yy1=1;yy1<=m-2;yy1++)
							{
								if(check(xx1,yy1))
								{
									for(int xx2=1;xx2<=n-2;xx2++)
									{
										for(int yy2=1;yy2<=m-2;yy2++)
										{
											if(check(xx2,yy2)&&(abs(xx1-xx2)>=3||abs(yy1-yy2)>=3))
											{
												printf("Solution exists.\nReplace J1 with ");
												cout<<card[i];
												printf(" and J2 with ");
												cout<<card[j];
												printf(".\nPut the first square to (%d, %d).\nPut the second square to (%d, %d).",xx1,yy1,xx2,yy2);
												return 0;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("No solution.");
	return 0;
}
```

## 后记：

本题解是我上信息竞赛课上写的，可能有点简短~~（偷偷写的）~~，不喜勿喷，谢谢！

#### qwq



---

