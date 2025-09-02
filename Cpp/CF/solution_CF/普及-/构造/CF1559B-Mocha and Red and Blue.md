# Mocha and Red and Blue

## 题目描述

As their story unravels, a timeless tale is told once again...

Shirahime, a friend of Mocha's, is keen on playing the music game Arcaea and sharing Mocha interesting puzzles to solve. This day, Shirahime comes up with a new simple puzzle and wants Mocha to solve them. However, these puzzles are too easy for Mocha to solve, so she wants you to solve them and tell her the answers. The puzzles are described as follow.

There are $ n $ squares arranged in a row, and each of them can be painted either red or blue.

Among these squares, some of them have been painted already, and the others are blank. You can decide which color to paint on each blank square.

Some pairs of adjacent squares may have the same color, which is imperfect. We define the imperfectness as the number of pairs of adjacent squares that share the same color.

For example, the imperfectness of "BRRRBBR" is $ 3 $ , with "BB" occurred once and "RR" occurred twice.

Your goal is to minimize the imperfectness and print out the colors of the squares after painting.

## 说明/提示

In the first test case, if the squares are painted "BRRBRBR", the imperfectness is $ 1 $ (since squares $ 2 $ and $ 3 $ have the same color), which is the minimum possible imperfectness.

## 样例 #1

### 输入

```
5
7
?R???BR
7
???R???
1
?
1
B
10
?R??RB??B?```

### 输出

```
BRRBRBR
BRBRBRB
B
B
BRRBRBBRBR```

# 题解

## 作者：SpeedStar (赞：5)

题意：把所有的 `?` 替换成 `R` 或 `B` 使得相邻的两个字符不同

分析：

若所有的字符都是 `?`，我们只需把奇数位替换成 `R`，偶数位替换成 `B`
反之，我们可以找到第一个不是 `?` 的位置，记为 `i`，在 `i` 之前的字符可以从 `i-1` 位置往左扫描，把相应位置的 `?` 替换成和右边相邻字符不一样的字符；若 $i$ 不超过 $n$，我们可以重复执行以下操作：

- 从位置 `i + 1` 开始向右扫描找出第一个不是 `?` 的位置，记为 `j`，再把位置 $i + 1 \sim j - 1$ 的 `?` 替换成和左边相邻字符不一样的字符，然后把 `i` 更新成 `j`

#### C++ 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define drep(i, n) for (int i = (n) - 1; i >= 0; --i)
#define srep(i, s, t) for (int i = (s); i < (t); ++i)

using std::cin;
using std::cout;
using std::string;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		
		int cnt = 0;
		rep(i, n) cnt += s[i] == '?';
		
		if (cnt == n) {
			rep(i, n) s[i] = i % 2 == 0 ? 'R' : 'B';
		}
		else {
			int i = 0;
			while (s[i] == '?') i++;
			drep(j, i) s[j] = s[j + 1] == 'R' ? 'B' : 'R';
			while (i != n) {
				int j = i + 1;
				while (j != n and s[j] == '?') j++;
				srep(k, i + 1, j) s[k] = s[k - 1] == 'R' ? 'B' : 'R';
				i = j;
			}
		}
		cout << s << '\n';
	}
	
	return 0;
}
```


---

## 作者：anideahe (赞：4)

这是一篇 DP 的题解  
### 题目大意  
给出字符串 $s$，仅包涵 $B$、$R$、$?$ 三种字符，你可以在 $?$ 处填入 $B$ 或 $R$ 使得相邻的位置字符相同的数量最少。  
### 大致思路  
设 $f(i,0/1)$ 表示第 $i$ 个位置为 $B$/$R$ 的最小值，因为题目要求输出一种合法方案，可以另开一个数组 $g(i,0/1)$ 存这个位置是由上一个位置填哪一个字符转移而来。转移方程为： 
$$
f[i][1]=\min(f[i-1][1]+1,f[i-1][0])
$$
$$
f[i][0]=\min(f[i-1][1],f[i-1][0]+1)
$$
转移时需考虑此位置能填的数，以及前一个位置能填的数。最后倒序扫一遍输出答案即可。
## *Code*:~~（已加注释）~~
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int t,n,f[101][2],g[101][2];
char s[101],a[101];
int min(int x,int y){ return x<y?x:y; }
int get(int x,int y,int z){
	int ans=0x3f3f3f3f;
	if(s[z]!='B') ans=min(ans,x);
	if(s[z]!='R') ans=min(ans,y);
	return ans;
}
int main(){
	cin>>t;
	while(t--){
		memset(f,0x3f,sizeof f);
		memset(g,0x3f,sizeof g);
		memset(a,0,sizeof a);
		cin>>n;
		cin>>(s+1);
		f[0][0]=f[0][1]=0;
		for(int i=1;i<=n;i=-~i){
			int j=get(f[i-1][1]+1,f[i-1][0],i-1);
			int k=get(f[i-1][1],f[i-1][0]+1,i-1);
         		//判断上一个位置可填的数并取最小值
			if(s[i]!='B'){
				f[i][1]=j;
				if(j==f[i-1][0]) g[i][1]=0;
				else g[i][1]=1;
			}//判断此位置可填的数并转移
			if(s[i]!='R'){
				f[i][0]=k;
				if(k==f[i-1][1]) g[i][0]=1;
				else g[i][0]=0;//记录上一个位置填的哪个字符
			}
		}
		int i,j=n,k=n;//倒序扫描得到最佳方案
        	if(f[n][1]<f[n][0]) i=1;
      		else i=0;
		while(j){
			a[k--]=i;
			i=g[j--][i];
		}
		for(int i=1;i<=n;i=-~i)
			if(a[i]) cout<<"R";
			else cout<<"B";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Leasier (赞：3)

首先，如果给定字符串全是 `?`，直接 `B` 和 `R` 交替即可；

如果给定字符串不全是 `?` 但开头可能有一段 `?`，找到第一个非 `?` 的字符，向前交替即可，向后依然交替，直到遇到下一个 `?`，向后交替即可，其他以此类推。

但这样怎么保证正确性呢？比如：`B??B`，如果往 `??` 中填入 `RB`，结果有 $2$ 个；如果填入 `BR`，结果也有 $2$ 个；

再比如：`B??R`，如果往 `??` 中填入 `RB`，结果有 $0$ 个；如果填入 `BR`，结果也有 $2$ 个。

于是在第一个 `?` 前填入与第一个 `?` 前相异的字母不会比其他方案更劣。

代码：
```cpp
#include <stdio.h>

char s[107];

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, j = 1;
		scanf("%d", &n);
		scanf("%s", &s[1]);
		s[n + 1] = 'B';
		while (j <= n && s[j] == '?') j++;
		for (int k = j - 1; k >= 1; k--){
			s[k] = s[k + 1] == 'B' ? 'R' : 'B';
		}
		for (; j <= n; j++){
			if (s[j] == '?') s[j] = s[j - 1] == 'B' ? 'R' : 'B';
		}
		for (int k = 1; k <= n; k++){
			printf("%c", s[k]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：2)

### 1 思路

对于字符串 $s_{[1,n]}$，字符必定只有 $3$ 种可能：`B R ?`。

设这个字符串有个子串 $s_{l,r}$，其中 $s_{l-1}$ 和 $s_{r+1}$ 都不是 `?` 而 $s_i\  (i\in[l,r])$ 均为 `?`。

很明显，子串 $s_{[l,r]}$ 的不完美值必定是 $0$（字符相间即可构造出），子串 $s_{l-1,r+1}$ 的不完美值必定是 $0$ 或 $1$ 且这个值是确定的。

那么，尽量使写入的字符不同于上一个字符即可构造出来。

注意边界特判。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100
int t;
int n;
char a[max_n+2];
bool allq;
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1559B_1.in","r",stdin);
	freopen("CF1559B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1,i;ca<=t;++ca){
		scanf("%d",&n);
		scanf("%s",a+1);
		allq=true;
		for(int k=1;k<=n;++k){
			if(a[k]!='?'){
				allq=false;
				break;
			}
		}
		if(allq){
			for(int k=1;k<=n;++k){
				if(k&1)a[k]='B';
				else a[k]='R';
			}
			for(int k=1;k<=n;++k)putchar(a[k]);
			puts("");
			continue;
		}
		a[n+1]='#';
		i=1;
		ans=0;
		if(a[1]=='?'){
			for(i=1;i<=n;++i){
				if(a[i]!='?'){
					for(int j=i-1;j>=1;--j){
						if((i-j)&1){
							if(a[i]=='B')a[j]='R';
							else a[j]='B';
						}
						else a[j]=a[i];
					}
					break;
				}
			}
		}
		for(;i<=n;){
			if(a[i]!='?'){
				for(int j=i+1;j<=n+1;++j){
					if(a[j]!='?'){
						for(int k=i+1;k<j;++k){
							if((k-i)&1){
								if(a[i]=='B')a[k]='R';
								else a[k]='B';
							}
							else a[k]=a[i];
						}
						i=j;
						break;
					}
				}
			}
			else ++i;
		}
		for(int i=1;i<=n;++i)putchar(a[i]);
		puts("");
	}
	return 0;
}

```

[记录传送门](https://www.luogu.com.cn/record/56080879)

By **dengziyue**

---

## 作者：yangzd (赞：1)

### 题目大意：
给出一个长度为 $n$ 的字符串，要使得整个字符串的相邻字符相同的次数尽可能少的出现，字符串只由 $\texttt{B}$，$\texttt{R}$，$\texttt{?}$三种构成，其中 $\texttt{?}$ 表示这个字符可以由我们指定为 $\texttt{B}$ 和 $\texttt{R}$ 中的任意一种，输出最终的字符串。

### 解题思路：
首先我们能只能决定字符串中 $\texttt{?}$ 的字符，如果对于一连串的 $\texttt{?}$ ，我们肯定是选择采取 $\texttt{R}$,$\texttt{B}$ 两种字符间隔的构造字符串，那么这段字符串中间是不可能出现下相邻字符相同的，出现冲突的地方只有可能出现在两端。那我们只要根据某一端已经确定好的字符，选择与这个字符不同的作为起始字符构造就行了。

如果想要证明这种贪心做法是正确的，可以自己根据两头字符是否相同、连续 $\texttt{?}$ 字符串的长度是奇是偶来分四种情况证明，这里就不再赘述了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

char s[205];
char a[2]={'B','R'};
long long n;

void draw(long long x,long long c)
{
    for(long long i=x; i>=1; i--)
	{
        if(s[i]!='?')
			break;
        s[i]=a[c];
        c^=1;
    }
}

void draw2(long long x,long long c)
{
    for(long long i=x,cnt=0; i<=n; i++)
	{
        if(s[i]!='?')
			break;
			
        s[i]=a[c];
        c^=1;
    }
}

signed main()
{
	ios::sync_with_stdio(0);
	
    long long t;
    
    cin >> t;
    
    while(t--)
	{
        cin >> n;
        cin >> s+1;
        
        char last='R';
        long long p=0;
        
        for(long long i=1; i<=n; i++)
		{
            if(s[i]!='?')
			{
                draw(i-1,s[i]=='B');
                last=s[i];
                p=i;
            }
        }
        
        if(s[n]=='?')
			draw2(p+1,last=='B');
			
        cout << s+1 << endl;
    }
    return 0;
}
```

---

## 作者：sunzz3183 (赞：0)

# CF1559B Mocha and Red and Blue

## 题意 

有一个大小为 $1×n$ 的格子，每个格子可以涂成蓝色或红色。已经给出某些格子涂的颜色，还有一些没有涂色的格子，现在你需要把这些空白的格子涂上颜色。如果两个相邻格子的颜色相同，那么它就是不美观的，你要尽量减少不美观的数量。

输入时， $B$ 代表蓝色， $R$ 代表红色， $?$ 代表没有颜色。

## 分析

**贪心**就可以。

从第一个染色的格子开始左右枚举，左边一红一蓝或一蓝一红，这样肯定没有不美观的。而右边当当前格子没染色时，保证当前格子与前一个格子不同来染色，这样不美观的数量最少。

为什么？

左边，已经没有已染色的格子，所以没有不美观的。

而右边，当遇到已染色的格子肯定与上一个格子要么不同，要么相同，而这样做最坏情况下不美观数量为  已染色的格子  $-1$  。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int T,n,s,a[200];
string c;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		cin>>c;
		s=n+1;
		for(int i=0;i<n;i++)
			if(c[i]!='?'){
				s=i;
				break;
			}
		for(int i=0;i<n;i++){
			if(c[i]=='?')
				a[i]=0;
			if(c[i]=='B')
				a[i]=1;
			if(c[i]=='R')
				a[i]=2;
		}
		if(s==n+1)
			a[s]=1;
		for(int i=s-1;i>=0;i--){
			if(a[i]!=0)
				continue;
			if(a[i+1]==1)
				a[i]=2;
			if(a[i+1]==2)
				a[i]=1;
		}
		for(int i=s+1;i<n;i++){
			if(a[i]!=0)
				continue;
			if(a[i-1]==1)
				a[i]=2;
			if(a[i-1]==2)
				a[i]=1;
		}
		for(int i=0;i<n;i++){
			if(a[i]==1)
				cout<<"B";
			if(a[i]==2)
				cout<<"R";
		}
		cout<<"\n";
	}
	return 0;
} 
```



---

## 作者：Chinshyo (赞：0)

## 一句话题意
输入一个字符串，用 `B` 或 `R` 代替字符串中的 `?` ，输出一种解，使得字符串中连续的字符最少。
## 思路1：
一种较为繁琐的思路。

找到所有含 `?` 的子串，分类讨论两头的字符和子串长度进行填充。本人刚开始使用了这种方法，代码将近90行，而且要考虑很多细节。**不推荐使用这种方法**
## 思路2：
读入一个字符串，将该字符串从头到尾扫一遍，每次若发现当前字符不是 `?` ，那么从当前位置向两头扫。在扫的过程中发现 `?` 就将其替换为与前一步到达的字符不相同的。一旦找到非 `?` 的，停止循环扫描。这样就能保证重复最小。

### 用样例举例:

![样例举例](https://cdn.luogu.com.cn/upload/image_hosting/qsjhf37c.png)

刚开始扫一遍扫到了黑色箭头所指的位置，然后向两头找，每次都取与上一次不一样的字符。

### 特殊情况

本题数据中存在字符串全是 `?` 的情况，这种算法找不到非 `?` 的就什么操作也不会做。因此要特殊处理，将所有都用 `B` ， `R` 交替赋值。

```cpp
if(s.find('B') == s.npos && s.find('R') == s.npos){
	for(int i = 0; i < s.size(); i++) {
		if(i % 2 == 0) s[i] = 'B';
		else s[i] = 'R';
	}
}
```


## 代码
```cpp
#include<bits/stdc++.h>
#define debug cout << "Helloworld" << endl
using namespace std;

int main() {
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		if(s.find('B') == s.npos && s.find('R') == s.npos){//特殊情况，全都是问号 
			for(int i = 0; i < s.size(); i++) {
				if(i % 2 == 0) s[i] = 'B';
				else s[i] = 'R';
			}
		}
		for(int j = 0; j < s.size(); j++) {
			if(s[j] != '?') {
				//找到问号，向两头扫 
				for(int k = j - 1; k >= 0; k--) {
					if(s[k] != '?') break; //当前位置有字符，无需填充，直接跳过 
					s[k] = (s[k + 1] == 'B') ? 'R' : 'B';//当前位置填充与上一次不同的。 
				} 
				for(int k = j + 1; k < s.size(); k++) {
					if(s[k] != '?') break;
					s[k] = (s[k - 1] == 'B') ? 'R' : 'B';
				}
			}
		}
		cout << s << endl;
	}
	return 0;
}

```


---

## 作者：lin000 (赞：0)

[CF1559B](https://www.luogu.com.cn/problem/CF1559B)

#### 题意
给出一个字符串，包含 `B`，`R`，`?`，其中 ? 表示空格。要求给出一个方案以 `B` 或 `R` 填充空格，使得 `BB` 和 `RR` 出现的次数和最少。

#### 思路

从每一个 `?` 块来看，再看两边字符。填充以 `abab` 的形式.

会有几种情况，在最优解中还有一个连续字符，或没有。显然，我们关心的是有几个连续字符。所以只需每次将产生的连续字符最小，就是以左边字符相反的开头再接上左边的字符。例如，`B???R` 就可以转换为 `BRBRR`，此时就是最优解。

最后再特判一下，左边字符为空，以右边字符相反为结尾。即如果块长度为偶数以右边字符开头，否则右边字符相反开头。如果两边都空，就填 `B` 或 `R`。

#### 代码
```cpp
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110;

int n , m ;
char s[N];
char tu(char x){
	if(x == 'B')
		return 'R';
	if(x == 'R')
		return 'B';
	else 
		return 'N';
}


int main(){
	cin >> m;
	while(m --){
		cin >> n;
		for(int i = 1 ; i <= n ; i++){
			cin >> s[i];
		}
		for(int i = 1 ; i <= n ; i++){
			if(s[i] == '?'){
				int r = i;
				while(s[r + 1] == '?') r ++;
				char lc = tu(s[i - 1]) ;
				
				if(lc == 'N' && tu(s[r + 1]) == 'N')
					lc = 'B';
				else if (lc == 'N'){
					if((r - i + 1) % 2 == 0)
						lc = s[r + 1];
					else
						lc = tu(s[r + 1]);
				}
		
				for(int j = i ; j <= r ; j++, lc = tu(lc))
					s[j] = lc;
			}
		}
		for(int i = 1 ; i <= n ; i++)
			cout << s[i];
		cout << endl;
	}
	return 0;
}
```





---

## 作者：Doubeecat (赞：0)


> 给定一个长度为 $n$ 仅包含 `R,B,?` 的字符串，定义一个串的不完美度为相邻的两个字符同色的对数。
>
> 例如，串 `BRRRBBR` 的不完美度为 $3$，其中 `RR` 出现了两次，`BB` 出现了一次。
>
> 你可以将 `?` 改为 `R,B` 的任意一种，现在请你求出这个字符串的最小不完美度。
>
> $T \leq 100,n \leq 100$

贪心构造。

我们首先考虑全是 `?` 的情况要怎么做，显然肯定是染成形如 `RBRBR...` 或 `BRBRB...` 的形式，这样的不完美度是最小的。

然后序列实际上可以看作若干个 `?` 段和一些 `R,B` 相连，我们只要判断每个 `?` 的连法即可。

具体来说，如果一个 `?` 的左边或者右边一块被染色了，那么，直接将 `?` 填成与之相反的颜色即可，可以证明这样的方案是最优的。

考场代码较丑陋。

### 代码

```cpp
void solve() {
    scanf("%d",&n);
    scanf("%s",s+1);
    bool flag = 0;
    int pos = 0;
    for (int i = 1;i <= n;++i) {
        if (s[i] != '?') {pos = i;flag = 1;break;}
    }
    if (!flag) {
        for (int i = 1;i <= n;++i) {
            if (i & 1) putchar('R');
            else putchar('B');
        }
        puts("");return ;
    }
    bool typ = 0;
    if (s[pos] == 'B') typ = 1;
    for (int i = pos-1;i >= 1;--i) {
        if (typ) s[i] = 'R';
        else s[i] = 'B';
        typ ^=1;
    } 
    if (s[pos] == 'B') typ = 1;
    else typ = 0;
    for (int i = pos + 1;i <= n;++i) {
        if (s[i] != '?') {
            if (s[i] == 'B') typ = 1;
            else typ  =0;
            continue;
        }
        if (typ) s[i] = 'R';
        else s[i] = 'B';
        typ ^= 1;
    }
    printf("%s\n",s+1);
}
```

---

## 作者：Refined_heart (赞：0)

题目大意：求使得相邻颜色点对数目最少。

首先观察到不论前面连了多少个颜色相同的，这一位如果和前面颜色相同，只会增加 $1$ 的贡献。

于是我们考虑一个贪心：从每一个有颜色的值往左右强行让相邻的数不同。

显然可以得到：两个给定颜色的点对之间，这样染色一定可以保证是最优的。

因为如果不这样染色就会产生至少 $1$ 对的贡献，而这样染色会产生至多一对的贡献。

于是这题就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
char s[5000];
int main(){
    scanf("%d",&T);while(T--){
        scanf("%d",&n);
        scanf("%s",s+1);
        if(n==1){
            if(s[1]=='?')s[1]='B';
            putchar(s[1]);
            puts("");
            continue;
        }
        int pos=-1;
        for(int i=1;i<=n;++i){
            if(s[i]!='?'){
                pos=i;
                break;
            }
        }
        if(pos==-1){
            for(int i=1;i<=n;++i){
                if(i&1)s[i]='B';else s[i]='R';
            }
            for(int i=1;i<=n;++i)putchar(s[i]);
            puts("");
            continue;
        }
        for(int i=pos-1;i>=1;--i){
            s[i]='B'+'R'-s[i+1];
        }
        pos++;
        while(pos<=n){
            while(s[pos]!='?'&&pos<=n)pos++;
            while(s[pos]=='?'&&pos<=n)s[pos]='B'+'R'-s[pos-1],pos++;
        }
        for(int i=1;i<=n;++i)putchar(s[i]);
        puts("");
    }
    return 0;
}
```

---

## 作者：江户川·萝卜 (赞：0)

### 题意
给定一个由 `RB?` 三种字符组成的字符串，你必须把所有 `?` 替换成 `RB`，使得所有相邻的字符相同的个数最少。输出替换后的字符串。

---
考虑贪心，对于所有的 `?` 均替换成与前一个字符不相同的字符。如果第一个字符是 `?` 则分 `RB` 两种情况讨论。

这个策略为何正确呢？

考虑连续 $k$ 个问号的情况。

- 如果是 `R???...?B` (或 `B???...?R`）：
	- 当 $k$ 是奇数时，最优策略是 `RBRBRB...BB` 或 `RRBRBRBR...RB`，策略正确。
    - 当 $k$ 是偶数时，最优策略是 `RBRB...RB`，策略正确。
- 如果是 `R???...?R`（或 `B???...?B`）:
	- 当 $k$ 是奇数时，最优策略是 `RBRBRB...BR`，策略正确。
    - 当 $k$ 是偶数时，最优策略是 `RBRBR...RR` 或 `RRBRBR...BR`，策略正确。
    
简单讨论后即可得策略正确。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		string s;
		cin>>s;
		string t=s;
		if(t[0]=='?') t[0]='B';
		for(int i=1;i<n;i++) if(t[i]=='?') t[i]=(t[i-1]=='B')?'R':'B';
		int ans=0;
		for(int i=1;i<n;i++) ans+=(t[i]==t[i-1]);
		if(s[0]=='?'){
			int cur=0;
			s[0]='R';
			for(int i=1;i<n;i++) if(s[i]=='?') s[i]=(s[i-1]=='B')?'R':'B';
			for(int i=1;i<n;i++) cur+=(s[i]==s[i-1]);
			if(cur<ans) cout<<s<<endl;
			else cout<<t<<endl;
		}
		else cout<<t<<endl;
	}
} 
```

---

## 作者：pomelo_nene (赞：0)

~~谱师写蛇画面曝光？网友：吐司竟然是这样写蛇的！~~

注意到一个全是 `?` 段的长度以及两端的颜色确定，因此一个全是 `?` 的段是否存在相邻的相同对可以确定。于是对于每一个 `R` 或者 `B`，我们往前后交替往 `?` 里面填 `R` 或者 `B`，如果出现冲突，那么无论怎么填都会出现冲突，不管就行了。

最后特判全是 `?` 的情况，输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[105];
int main(){
	int T;
	scanf("%d",&T);
	while(T-->0)
	{
		scanf("%d %s",&n,s+1);
		for(int i=1;i<=n;++i)
		{
			if(s[i]=='?')	continue;
			for(int j=i-1;j;--j)
			{
				if(s[j]!='?')	break;
				if(s[j+1]=='R')	s[j]='B';
				else	s[j]='R';
			}
			for(int j=i+1;j<=n;++j)
			{
				if(s[j]!='?')	break;
				if(s[j-1]=='R')	s[j]='B';
				else	s[j]='R';
			}
		}
		if(s[1]=='?')	for(int i=1;i<=n;++i)	s[i]=(i&1)?'B':'R';
		puts(s+1);
	}
	return 0;
}
```

---

