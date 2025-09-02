# Xenia and Dominoes

## 题目描述

### 题意
在一个 $3*n$ 的桌子上放一些 $1*2$ 的多米诺骨牌（横竖放都可以），桌子上有一些`不能放置的格子`，除此以外，还要求一个指定的`空位`不能被多米诺骨牌覆盖，同时这个空位可以通过移动附近的骨牌来转移到其他地方，剩下的格子要被全部覆盖，求放置的种数。

## 说明/提示

$3\leq n\leq 10^4$

## 样例 #1

### 输入

```
5
....X
.O...
...X.
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
.....
.O...
.....
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
...
...
..O
```

### 输出

```
4
```

# 题解

## 作者：xyf007 (赞：4)

如果没有 $\texttt{O}$ 的限制，就是一个状压 DP 的模板，直接设 $dp_{i,S}$ 表示第 $i$ 列，状态为 $S$ 的方案数，转移手动枚举一下即可。  
考虑 $\texttt{O}$ 要我们干什么。至少可以移动一次，意味着至少有一个 $1 \times 2$ 的多米诺骨牌是可以移到空位里面，即 $\Box\Box\texttt{O}$ 型。因此暴力枚举周围哪些骨牌可以直接移进去，简单容斥即可。
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
constexpr int kMod = 1e9 + 7;
template <typename T>
void Read(T &x) {
  x = 0;
  int f = 1;
  char c;
  while ((c = std::getchar()) < '0' || c > '9')
    if (c == '-') f = -1;
  x = c - '0';
  while ((c = std::getchar()) >= '0' && c <= '9') x = x * 10 + (c - '0');
  x *= f;
}
template <typename T, typename... Args>
void Read(T &x, Args &...args) {
  Read(x);
  Read(args...);
}
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
template <typename T>
T add(T a, T b) {
  return (a + b) % kMod;
}
template <typename T, typename... Args>
T add(T a, T b, Args... args) {
  return add(add(a, b), args...);
}
template <typename T>
T sub(T a, T b) {
  return (a + kMod - b) % kMod;
}
template <typename T>
T mul(T a, T b) {
  return a * static_cast<long long>(b) % kMod;
}
template <typename T, typename... Args>
T mul(T a, T b, Args... args) {
  return mul(mul(a, b), args...);
}
template <typename T>
void Add(T &a, T b) {
  a = add(a, b);
}
template <typename T, typename... Args>
void Add(T &a, T b, Args... args) {
  Add(a, add(b, args...));
}
template <typename T>
void Sub(T &a, T b) {
  a = sub(a, b);
}
template <typename T>
void Mul(T &a, T b) {
  a = mul(a, b);
}
template <typename T, typename... Args>
void Mul(T &a, T b, Args... args) {
  Mul(a, mul(b, args...));
}
int n, dp[10001][8];
char a[3][10001];
void Solve() {
  std::memset(dp, 0, sizeof(dp));
  dp[0][7] = 1;
  for (int i = 1; i <= n; i++) {
    int T = 0;
    for (int j = 0; j < 3; j++)
      if (a[j][i] != '.') T |= 1 << j;
    Add(dp[i][T], dp[i - 1][7]);
    if (!(T & 1)) Add(dp[i][T | 1], dp[i - 1][6]);
    if (!(T & 2)) Add(dp[i][T | 2], dp[i - 1][5]);
    if (!(T & 3)) Add(dp[i][T | 3], dp[i - 1][4], dp[i - 1][7]);
    if (!(T & 4)) Add(dp[i][T | 4], dp[i - 1][3]);
    if (!(T & 5)) Add(dp[i][T | 5], dp[i - 1][2]);
    if (!(T & 6)) Add(dp[i][T | 6], dp[i - 1][1], dp[i - 1][7]);
    if (!T) Add(dp[i][7], dp[i - 1][0], dp[i - 1][3], dp[i - 1][6]);
  }
}
int main(int argc, char const *argv[]) {
  Read(n);
  for (int i = 0; i < 3; i++) std::scanf("%s", a[i] + 1);
  int x = 0, y = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 1; j <= n; j++)
      if (a[i][j] == 'O') {
        x = i;
        y = j;
        break;
      }
  int ans = 0;
  for (int L = 0; L < 2; L++)
    for (int R = 0; R < 2; R++)
      for (int U = 0; U < 2; U++)
        for (int D = 0; D < 2; D++) {
          if ((L && (y <= 2 || a[x][y - 1] == 'X' || a[x][y - 2] == 'X')) ||
              (R && (y + 2 > n || a[x][y + 1] == 'X' || a[x][y + 2] == 'X')) ||
              (U && (x < 2 || a[x - 1][y] == 'X' || a[x - 2][y] == 'X')) ||
              (D && (x || a[x + 1][y] == 'X' || a[x + 2][y] == 'X')) ||
              !(L + R + U + D))
            continue;
          int op = (L + R + U + D) & 1;
          if (L) a[x][y - 1] = a[x][y - 2] = 'X';
          if (R) a[x][y + 1] = a[x][y + 2] = 'X';
          if (U) a[x - 1][y] = a[x - 2][y] = 'X';
          if (D) a[x + 1][y] = a[x + 2][y] = 'X';
          Solve();
          if (op & 1)
            Add(ans, dp[n][7]);
          else
            Sub(ans, dp[n][7]);
          if (L) a[x][y - 1] = a[x][y - 2] = '.';
          if (R) a[x][y + 1] = a[x][y + 2] = '.';
          if (U) a[x - 1][y] = a[x - 2][y] = '.';
          if (D) a[x + 1][y] = a[x + 2][y] = '.';
        }
  std::printf("%d", ans);
  return 0;
}
```

---

## 作者：AutumnQ (赞：0)

## 前置芝士
状态压缩动态规划，容斥原理，位运算。

## 分析
一个空位只能由上下左右四种方向的多米诺挪动，箭头表示移动方向，见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/wkke7sld.png)

既然是挪动了，那么可以看做这个多米诺骨牌被固定了，看做一个字符```X```来做动态规划。

以左边的蓝色骨牌举例，如果要想成功固定这个多米诺骨牌要满足“能够合法的放下”这一要求，即不越界，位置上不是```X```字符。

## 动态规划
类似于多米诺的摆放这道例题。

将多米诺摆放由横过来做变成竖过来做，即当做一排 $3$ 个，共有 $n$ 排。

以 $0/1$ 来表示多米诺的摆放状态，如果一个骨牌是横着放的，那么它所在的两个方格都填充 $1$，如果它是竖着放的，那么它所在的两个格子中，上面的那个填 $0$，下面的这个填 $1$。再进行状态压缩。

设 $dp_{i,sta}$ 为已经做到第 $i$ 列，状态为 $sta$ 的摆放方式。

不难发现，$dp_{i,sta}$ 可以由 $dp_{i-1,7-sta}$ 转移而来。

证明：对于每一个 $0$ 下一行一定为 $1$，对于 $1$，则分两种情况。第一种，横过来的 $11$ 放，下一行可以填竖过来的一对 $01$。第二种竖过来的 $01$ 放完没有余留到下一行，同理。

所以转移过来是合法的。

通过手玩又发现，$3$ 和 $6$ 可以由 $7$ 转移过来，$7$ 可以由 $3$ 和 $6$ 转移过来，读者们可以自己尝试画图，这里省略。

## 时间复杂度
枚举移动方式为 $2^4$，状态共有 $2^3=8$ 种，所以总时间复杂度为 $O(2^7 \times n)$ 的。

## 代码（主要部分）
```cpp
int dp[10010][8];
int n,m;
char MP[5][10010];
char ug(){
	char ch=gc();
	while(ch!='X' && ch!='O' && ch!='.')ch=gc();
	return ch;
}
int Ox,Oy;//O的坐标
signed main(){
//	free();
	n=read();
	int ans=0;
	for(int i=0;i<=2;i++){
		for(int j=1;j<=n;j++){
			MP[i][j]=ug();
		} 
	}
	for(int i=0;i<=2;i++){
		for(int j=1;j<=n;j++){
			if(MP[i][j]=='O'){
				Ox=i,Oy=j;
				break;
			}		
		}
	}//find O
	MP[Ox][Oy]='X';//O上面不能放东西
	for(int i1=0;i1<=1;i1++){//up
		if(i1){
			if(Ox!=0)continue;
			if(MP[1][Oy]=='X' || MP[2][Oy]=='X')continue;//越界或是不能放，下同
		}
		for(int i2=0;i2<=1;i2++){//down
			if(i2){
				if(Ox!=2)continue;
				if(MP[1][Oy]=='X' || MP[0][Oy]=='X')continue;
			}
			for(int i3=0;i3<=1;i3++){//left
				if(i3){
					if(Oy==n || Oy==n-1)continue;
					if(MP[Ox][Oy+1]=='X' || MP[Ox][Oy+2]=='X')continue;
				}
				for(int i4=0;i4<=1;i4++){//right
					if(!(i1||i2||i3||i4))continue;//题意得必须有一种移动
					if(i4){
						if(Oy==1 || Oy==2)continue;
						if(MP[Ox][Oy-1]=='X' || MP[Ox][Oy-2]=='X')continue;
					}
					if(i1)MP[1][Oy]=MP[2][Oy]='X';
					if(i2)MP[1][Oy]=MP[0][Oy]='X';
					if(i3)MP[Ox][Oy+1]=MP[Ox][Oy+2]='X';
					if(i4)MP[Ox][Oy-1]=MP[Ox][Oy-2]='X';//打上已经放过多米诺的标记
					memset(dp,0,sizeof(dp));
					dp[0][7]=1;
					for(int j=1;j<=n;j++){
						int sta=0;
						for(int i=0;i<3;i++){
							sta=(MP[i][j]=='X')?sta|(1<<i):sta;
						}
						for(int i=0;i<=7;i++){
							if(sta&i)continue;//不合法
							dp[j][sta|i]+=dp[j-1][7-i];
							dp[j][sta|i]%=p;
							if(i==3 || i==6){
								dp[j][sta|i]+=dp[j-1][7];
								dp[j][sta|i]%=p;
							}
							if(i==7){
								dp[j][sta|i]+=dp[j-1][6];
								dp[j][sta|i]%=p;
								dp[j][sta|i]+=dp[j-1][3];
								dp[j][sta|i]%=p;
							}//转移
						}	
					}
					if((i1+i2+i3+i4)&1){
						ans+=dp[n][7];
						ans%=p;
					}else{ 
						ans-=dp[n][7];
						ans=(ans+p)%p;
					}//容斥不解释 
					if(i1)MP[1][Oy]=MP[2][Oy]='.';
					if(i2)MP[1][Oy]=MP[0][Oy]='.';
					if(i3)MP[Ox][Oy+1]=MP[Ox][Oy+2]='.';
					if(i4)MP[Ox][Oy-1]=MP[Ox][Oy-2]='.';
				}
			}
		}
	}
	print(ans);
	return 0;
}
```

---

