# Diverse Garland

## 题目描述

给一串字符，只有`R`和`G`和`B`。问如果要让相邻$2$个字符都不同，最少要改几个?

## 样例 #1

### 输入

```
9
RBGRRBRGG
```

### 输出

```
2
RBGRGBRGR
```

## 样例 #2

### 输入

```
8
BBBGBRRR
```

### 输出

```
2
BRBGBRGR
```

## 样例 #3

### 输入

```
13
BBRRRRGGGGGRR
```

### 输出

```
6
BGRBRBGBGBGRG
```

# 题解

## 作者：Ankiia (赞：6)

本题解同步在我的[blog](https://www.cnblogs.com/wzztabaorz/p/10363852.html)
中发表

咳咳在wzz大佬的提醒下去刷了这道水题（吐槽一下此题最多算黄题），算法思路是贪心。

由于从前往后贪比较麻烦（我看到许多题解大佬都从前往后贪），所以我从后往前贪简单一些。

也就是说是判s[i]和s[i-1]而不是s[i]和s[i+1]。

下面上代码（详解在代码里面）


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,gs;//n为字符串长度，gs为最少要改的次数。
char s[200010];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
    }//输入输出不解释
    for(int i=2;i<=n;i++)//从i=2开始判，否则会卡bug（其实也没什么用，看着顺眼，不过还是保留这个好习惯，因为有些题会卡）。
    {
        if(s[i-1]==s[i])//从s[i]的后面一个与前面的一个比较，这样贪心比较简单（主要是容易想，因为我实在是太蒻了）
        {
            if(s[i-1]!='R' && s[i+1]!='R')
            {
                s[i]='R';
                gs++;
                continue;
            }
            if(s[i-1]!='G' && s[i+1]!='G')
            {
                s[i]='G';
                gs++;
                continue;
            }
            if(s[i-1]!='B' && s[i+1]!='B')//三种情况（也就是R、G、B这三种）的判断修改，即判即改。
            {
                s[i]='B';
                gs++;//每次操作都次数加1。
                continue;
            }
        }
    }
    cout<<gs<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<s[i];
    }
    return 0;
}
```
本蒟蒻第一篇题解求过。。。

---

## 作者：_xbn (赞：3)

其实本题并不需要很多特判，有一个很巧妙的方法能解决繁琐的特判，对于连续的三个字符，如果 $s(i-1)=s(i)$，按照贪心的思想考虑，我们肯定改变位置靠后的字符。

因为有三种字符，这时很多人就会写三个特判，这样十分繁琐，我们要把 $s(i)$ 改变成与他前一个和后一个都不同的字符那我们可以把三种字符相加，再减去 $s(i-1)$ 和 $s(i+1)$，这样自动就去掉了前后字符。

```cpp
// I love msc forever
#include <bits/stdc++.h>
using namespace std;
const int N = 200002;
int n, ans;
char s[N];
int main()
{
	scanf("%d%s",&n, s);
	for(int i=1;i<n;i++)
	{
		if(s[i - 1] == s[i])
		{
			ans++;
			if(i + 1 < n && s[i - 1] != s[i + 1])
			{
				s[i] = 'R' + 'G' + 'B' - s[i - 1] - s[i + 1];
			}
			else
			{
				s[i] = s[i-1]=='R'?'G':'R';
			}
		}
	}
	printf("%d\n%s\n",ans, s);
}
```


---

## 作者：Reywmp (赞：3)

D貌似比C要水。。。。

------------

标签有dp，也有贪心。不过我用贪心+模拟A了（hack结束了，应该是A了）

------------

贪心思路惊奇：

>因为要相邻的不同，我们可以先找3个相连全部相同的。将中间的改掉

>这样相当于一次将2个相同的串全部消掉了，一石二鸟。

比如说串`RBBBG`

我们可以改为`RGBRG`将第2个第4个改掉，不过我们发现改成`RBGBG`只需要改第3个即可。

所以得知：**先找3个相连的，改掉中间的**。

不过3个相连的消完还不够。。。

比如说串`RBBBBR`或者串`RRGBG`

第一个串有4个相连的，我们找3个相连时只能改成`RBGBBR`还有2个相连的消不掉。

第二个本来只有2个相连的，3个相连的找不到。

所以得知：找完还要再找剩下的。

------------

那么我们遍历一遍字符串，找到3个相连的修改。

再找一遍遗漏的，找到2个相连的再改，不过要注意，改过后要**判断与前后都不一样！**

------------

代码：

```cpp
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n;
	read(n);
	for(int i=1;i<=n;i++)
	{
		a[i]=getchar();
	}
	int ans=0;
	for(int i=2;i<n;i++)
	{
		if(a[i]==a[i-1]&&a[i]==a[i+1])//前后都一样，3个相连
		{
			if(a[i]=='R')a[i]='B';//要改如果都是R改成B
			else a[i]='R';//不是就直接改成R
			ans++;//次数++
		}
	}
	for(int i=2;i<=n;i++)
	{
		if(a[i]==a[i-1])//查缺
		{
			a[i]='R';//先改为敬
			if(a[i-1]==a[i]||a[i]==a[i+1])
			{
				a[i]='B';//一样改成B
			}
			if(a[i-1]==a[i]||a[i]==a[i+1])
			{
				a[i]='G';//如果还一样再改
			}
			ans++;
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
	{
		printf("%c",a[i]);//其实可以直接printf("%s\n",a);
	}
	return 0;
}
```

---

## 作者：Heartlessly (赞：2)

## Solution
看到其他人都是用贪心做的（贪心代码好短，比赛真的没想到），这里提供一种 $DP$ 的做法。我们用 $f[0/1/2][i]$ 表示前 $i$ 部分且最后一个字母是 $R/G/B$ 的最小答案，对于 $s[i]$，都只会由上一个状态改或不改转移而来，对 $R/G/B$ 进行分类讨论，最终答案为 $min\begin{Bmatrix} f[0][n], f[1][n], f[2][n]\end{Bmatrix}$，用递归输出最终方案。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template < class T > inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    x = f ? -x : x;
}

int n, f[3][200005];
char s[400001];

void dfs(int m, int x) {//分类进行匹配，递归到上一层
    if (x == 0) return;
    if (s[x] == 'R') {
        if (m == 0) {
            if (f[0][x] == f[1][x - 1]) dfs(1, x - 1), putchar('R');
            else if (f[0][x] == f[2][x - 1]) dfs(2, x - 1), putchar('R');
        }
        if (m == 1) {
            if (f[1][x] == f[0][x - 1] + 1) dfs(0, x - 1), putchar('G');
            else if (f[1][x] == f[2][x - 1] + 1) dfs(2, x - 1), putchar('G');
        }
        if (m == 2) {
            if (f[2][x] == f[0][x - 1] + 1) dfs(0, x - 1), putchar('B');
            else if (f[2][x] == f[1][x - 1] + 1) dfs(1, x - 1), putchar('B');
        }
    } 
    if (s[x] == 'G') {
        if (m == 0) {
            if (f[0][x] == f[1][x - 1] + 1) dfs(1, x - 1), putchar('R');
            else if (f[0][x] == f[2][x - 1] + 1) dfs(2, x - 1), putchar('R');
        }
        if (m == 1) {
            if (f[1][x] == f[0][x - 1]) dfs(0, x - 1), putchar('G');
            else if (f[1][x] == f[2][x - 1]) dfs(2, x - 1), putchar('G');
        }
        if (m == 2) {
            if (f[2][x] == f[0][x - 1] + 1) dfs(0, x - 1), putchar('B');
            else if (f[2][x] == f[1][x - 1] + 1) dfs(1, x - 1), putchar('B');
        }
    }
    if (s[x] == 'B') {
        if (m == 0) {
            if (f[0][x] == f[1][x - 1] + 1) dfs(1, x - 1), putchar('R');
            else if (f[0][x] == f[2][x - 1] + 1) dfs(2, x - 1), putchar('R');
        }
        if (m == 1) {
            if (f[1][x] == f[0][x - 1] + 1) dfs(0, x - 1), putchar('G');
            else if (f[1][x] == f[2][x - 1] + 1) dfs(2, x - 1), putchar('G');
        }
        if (m == 2) {
            if (f[2][x] == f[0][x - 1]) dfs(0, x - 1), putchar('B');
            else if (f[2][x] == f[1][x - 1]) dfs(1, x - 1), putchar('B');
        }
    }
}

int main() {
    read(n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'R') {
            f[0][i] = min(f[1][i - 1], f[2][i - 1]);
            f[1][i] = min(f[0][i - 1] + 1, f[2][i - 1] + 1);
            f[2][i] = min(f[0][i - 1] + 1, f[1][i - 1] + 1);
        } 
        if (s[i] == 'G') {
            f[0][i] = min(f[1][i - 1] + 1, f[2][i - 1] + 1);
            f[1][i] = min(f[0][i - 1], f[2][i - 1]);
            f[2][i] = min(f[0][i - 1] + 1, f[1][i - 1] + 1);
        }
        if (s[i] == 'B') {
            f[0][i] = min(f[1][i - 1] + 1, f[2][i - 1] + 1);
            f[1][i] = min(f[0][i - 1] + 1, f[2][i - 1] + 1);
            f[2][i] = min(f[0][i - 1], f[1][i - 1]);
        }
    }//转移
    printf("%d\n", min(f[0][n], min(f[1][n], f[2][n])));
    if (f[0][n] <= f[1][n] && f[0][n] <= f[2][n]) dfs(0, n);
    else if (f[1][n] <= f[0][n] && f[1][n] <= f[2][n]) dfs(1, n);
    else if (f[2][n] <= f[0][n] && f[2][n] <= f[1][n]) dfs(2, n);//找到最小的答案，递归输出方案
    putchar('\n');
    return 0;
}
```

---

## 作者：Creator_157 (赞：1)

### 思路：
从前往后扫一遍，遇见和前面不一样的就改，同时累加答案。

### 代码部分：
从 **第2个if** 到 **else** 是处理这个字符和前一个字符、后一个字符**不同**时 将它**变成和前后都不同的字符**。

**else**里是**前后相同**时改一个前（后）不同的字符。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
char s[200005],b[200005];
int main()
{
    cin>>n;
    cin>>s;
    for(int i=0;i<n;i++)b[i]=s[i];
    for(int i=1;i<n;i++)
    {
	if(s[i]==s[i-1])//如果这个字符和前面的不一样
	{
    	    ans++;
	    if((s[i-1]=='R'&&s[i+1]=='B')||(s[i-1]=='B'&&s[i+1]=='R'))
	    {
                s[i]='G';
	        continue;
	    }
	    if((s[i-1]=='G'&&s[i+1]=='B')||(s[i-1]=='B'&&s[i+1]=='G'))
	    {
	        s[i]='R';
	        continue;
	    }
	    if((s[i-1]=='R'&&s[i+1]=='G')||(s[i-1]=='B'&&s[i+1]=='G'))
	    {
	        s[i]='B';
	        continue;
	    }
	    else
	    {
	        if(s[i-1]=='G') s[i]='B';
	        else if(s[i-1]=='B') s[i]='R';
	        else if(s[i-1]=='R') s[i]='B';
	    }
	}
    }
    cout<<ans<<endl<<s;
    return 0;
}
```
over；

---

## 作者：Zechariah (赞：1)

大力贪心  
找到俩相邻相等的字符就改右边的  
注意改的字符要与右边也不一样
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int n;
char s[N];

int main(void)
{
    rg int ans = 0;
    n = fast_IO::read();
    scanf("%s", s + 1);
    for (rg int i = 1; i <= n; ++i)
        if (s[i] == s[i - 1])
        {
            ++ans;
            if (i == n || s[i] == s[i + 1])
            {
                if (s[i] == 'B')s[i] = 'G';
                else if (s[i] == 'G')s[i] = 'R';
                else if (s[i] == 'R')s[i] = 'B';
            }
            else
            {
                if (s[i] == 'B'&&s[i + 1] == 'R')s[i] = 'G';
                else if (s[i] == 'B'&&s[i + 1] == 'G')s[i] = 'R';

                else if (s[i] == 'R'&&s[i + 1] == 'B')s[i] = 'G';
                else if (s[i] == 'R'&&s[i + 1] == 'G')s[i] = 'B';

                else if (s[i] == 'G'&&s[i + 1] == 'B')s[i] = 'R';
                else if (s[i] == 'G'&&s[i + 1] == 'R')s[i] = 'B';
            }
        }
    printf("%d\n%s", ans, s + 1);
    return 0;
}

```

---

## 作者：_Give_up_ (赞：1)

## 题目大意
给出一个由 $R$,$G$,$B$ 组成的字符串，要始相邻两个字符不相同，至少要改几个字符？

## 题目思路
把字符串从第二位开始遍历，如果当前字符等于前一个字符，就必须修改，否则继续往下遍历。

那么，怎么修改呢？我们判断当前字符的前一位是否等于后一位，如果等于，就选一个和他们都不相同的字符；否则只要改的字符不等于前一个字符或后一个字符就行了（只需判断一个）。

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	string s;
	cin >> n >> s;
	int ans = 0;
	for (int i=1;i<n;i++)
	{
		if (s[i]==s[i-1])
		{
			ans++;
			if (s[i-1]!=s[i+1] && i+1<n) s[i] = char(219-s[i-1]-s[i+1]);
			else if (s[i-1]=='R') s[i] = 'G';
			else s[i] = 'R';
		}
	}
	cout << ans << endl;
	for (int i=0;i<n;i++)
		cout << s[i];
	cout << endl;
	return 0; 
}
```


---

## 作者：Tx_Lcy (赞：0)

直接按题意模拟即可。
## 思路
[题目传送门](https://www.luogu.com.cn/problem/CF1108D)

不难想到，一个数对答案的影响只有与它相邻的两个数，那么显然，若我们从左往右处理，对于位置 $\verb!i!$，若 $\verb!s[i]==s[i+1]!$，我们改右边的那个数更优。

因为 $\verb!i!$ 前面的位置已经处理完了，也就是这个地方更改只对它后面的一位有影响，而如果更改 $\verb!i+1!$，则若 $\verb!s[i+1]!$ 不等于 $\verb!s[i+2]!$，我们只减少了一对相邻的数，而若 $\verb!s[i+1]==s[i+2]!$，我们一次可以减少两对！如果我们改 $\verb!i!$ 则无论如何只能减少一对。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,ans=0;cin>>n;
    string s;cin>>s;
    for (rint i=0;i<n-1;++i)
        if (s[i]==s[i+1]){
            if (s[i]!='R' && s[i+2]!='R') s[i+1]='R';
            if (s[i]!='B' && s[i+2]!='B') s[i+1]='B';
            if (s[i]!='G' && s[i+2]!='G') s[i+1]='G';
            ++ans;
        }
    cout<<ans<<'\n'<<s<<'\n';
    return 0;
}

```


---

## 作者：Skyjoy (赞：0)

很简单的贪心题，感觉根本没有蓝

这题既然要求改变次数**最少**，那么我们就应该从头开始找，若遍历到的字符与上一个相同，就把它换成与前一个和后一个都不同的字符。这使得遍历到后一个字符时就不用改了，大大减少了改变的次数。见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
char ch[200010];
int main(){
	scanf("%d",&n);
	scanf("%s",ch);
	for(int i=1;i<n;i++){
		if(ch[i-1]==ch[i]){//如果相同
			if(ch[i-1]!='R'&&ch[i+1]!='R')ch[i]='R',cnt++;
			else if(ch[i-1]!='G'&&ch[i+1]!='G')ch[i]='G',cnt++;
			else ch[i]='B',cnt++;
		}
	}
	printf("%d\n",cnt);
	for(int i=0;i<n;i++)printf("%c",ch[i]);
	return 0;
}
```

---

## 作者：zzh_han (赞：0)

## 题意

就是一个由 $B$ $R$ $G$ 这三种字母所组成的字符串s我们要对字符串进行修改使每个字符的左右两边的字母不同问要多少次更改并输出更改的字符串。对就是这样。

## 做法

我们可以用一种贪心思想比如现在是 $BBB$ 我们的最优解是一次所以我们只要将中间的改掉就可以减少一次边那么先将三个相连的更改掉再来处理两个的就非常的简单了。

#### 附上代码

```c++
#include <bits/stdc++.h>
using namespace std;
string s;
int ans=0,n,m; 
int main()
{
	cin>>n;
	cin>>s;
	s=' '+s;//一个处理将字符串向前退一位更加的好处理
	for(int i=1;i<=n;i++)
	{
		if(s[i-1]==s[i])//判断是否合法
		{
			if(s[i-1]!='R'&&s[i+1]!='R')
        		s[i]='R';
      		else if(s[i-1]!='G'&&s[i+1]!='G')
        		s[i]='G';
      		else if(s[i-1]!='B'&&s[i+1]!='B')
        		s[i]='B';//判断他是否为三个相连如果是就从中间改掉
      		ans++;
		}
	}
	cout<<ans<<endl; 
	for(int i=1;i<=n;i++)
		cout<<s[i];
	return 0;
} 
```

这道题就是这样啦。



---

## 作者：xh39 (赞：0)

这道题好像不够蓝色耶。。。

# 算法:贪心

其实逐个扫描,发现一样的立刻改变,RGB逐个尝试,如果和前面一个不一样&&和后面一个不一样,就跳过这次循环,接着枚举。

附上代码(请先看分析,代码里不会有太多关于算法的注释!!!)

```cpp
//可以通过2019年2月3日晚上的数据
#include<bits/stdc++.h> //万能头文件,包含所有c++库函数。
using namespace std;
#define can if(s[i]!=s[i-1]&&s[i]!=s[i+1]) //#define之后只用输入前面来代替后面一个。
int main(){
	int n,i,sum=0; //sum是用来统计改过多少次的。
	string s;
	cin>>n>>s;
	for(i=1;i<n;i++){ //一定要从1开始,虽然字符串是从0开始存储的,因为i=0的时候,s[i-1]就变成了s[-1],这样很容易改变其他变量的值,但不用特殊处理n-1,因为字符串最后面要存储一个\0。
		if(s[i]==s[i-1]){
			sum++;
			s[i]='R';
			can continue; //continue是跳过一次循环,千万别写成break了。
			s[i]='G';
			can continue;
			s[i]='B';
		}
	}
	cout<<sum<<endl<<s;
	return 0;
}
```

---

## 作者：G_A_TS (赞：0)

题解同步发布于[blog](https://www.cnblogs.com/wzzorz/articles/10360996.html)  

------------
原题link:[here](http://codeforces.com/problemset/problem/1108/D)  
[luogu](https://www.luogu.org/problemnew/show/CF1108D)
贪心试试能拿多少分  
~~结果一遍过~~  
无语  
就是第个若与i-1不同则改  
改后判断是否与第i+1个不同，否则改  
~~(其实就是找与前与后都不同的填)~~  
代码理解起来应该挺容易的  

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,line[200010];
char IP[200010];
int main()
{
	cin>>n;
	cin>>IP+1;
	for(int i=1;i<=n;i++)
	{
		if(IP[i]=='R')
		{
			line[i]=0;
		}
		if(IP[i]=='G')
		{
			line[i]=1;
		}
		if(IP[i]=='B')
		{
			line[i]=2;
		}
	}
	for(int i=2;i<=n;i++)
	{
		if(line[i]==line[i-1])
		{
			line[i]=(line[i-1]+1)%3;
			if(line[i]==line[i+1])
			{
				line[i]++;
				line[i]%=3;
			}
			ans++;
		} 
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
	{
		if(line[i]==0)
		{
			cout<<'R';
		}
		if(line[i]==1)
		{
			cout<<'G';
		}
		if(line[i]==2)
		{
			cout<<'B';
		}
	} 
} 
```

---

## 作者：zsc2003 (赞：0)

看到大家都是用$dp$做的，觉得大家都好强啊

这里提供一种贪心的做法

从$2$~$n$枚举每一个字符

因为不能有$2$个相邻的字符是相同的

所以遇到$s_i==s_{i-1}$的情况

就根据$s_i,s_{i-1},s_{i+1}$的情况将$s_i$更改

具体细节见代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()//读入优化
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=200100;
int n,ans;
char s[N];
int main()
{
	n=read();
	scanf("%s",s+1);
	for(int i=2;i<=n;i++)
		if(s[i]==s[i-1])
		{
			ans++;
			if(s[i]=='R')
			{
				if(s[i+1]=='R')
					s[i]='G';
				else if(s[i+1]=='G')
					s[i]='B';
				else
					s[i]='G';
			}
			else if(s[i]=='G')
			{
				if(s[i+1]=='G')
					s[i]='B';
				else if(s[i+1]=='R')
					s[i]='B';
				else
					s[i]='R';
			}
			else
			{
				if(s[i+1]=='B')
					s[i]='G';
				else if(s[i+1]=='G')
					s[i]='R';
				else
					s[i]='G';
			}
		}
	printf("%d\n%s\n",ans,s+1);
	return 0;
}
```

---

## 作者：_louhc (赞：0)

# 题意简述

一个只包含三种字符'R','G','B'的字符串，修改最少的字符，使任意两个相邻的字符互不相等。

# 思路

顺序枚举从2到N的所有字符，如果与之前的字符相等，就根据前后字符修改这个字符。

为什么呢？如果碰到一对相邻且相同的元素$i,i+1$，后一个元素$i+2$可能与$i+1$相等，但是$i$不可能与$i-1$相等（因为前面的元素已经过修改调整），因此，修改$i+1$可能会更优于$i$（因为如果修改$i$的话，可能还需要修改$i+1$或$i+2$）。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Re register
#define MAXN 200005

int N, ans;
char s[MAXN];

int main(){
	scanf( "%d", &N ); scanf( "%s", s + 1 );
	for ( int i = 2; i <= N; ++i ){
		if ( s[i] == s[i - 1] ){
			ans++; char t('R');
			if ( s[i - 1] == 'R' || s[i + 1] == 'R' ){
				t = 'G';
				if ( s[i - 1] == 'G' || s[i + 1] == 'G' ) t = 'B';
			}
			s[i] = t;
		}
	}
	printf( "%d\n%s\n", ans, s + 1 );
	return 0;
}

```



---

## 作者：da32s1da (赞：0)

考虑贪心地改，若$a[i]=a[i+1]$，那么把$a[i+1]$改成与$a[i],a[i+2]$均不同的字母

```
#include<cstdio>
const int N=2e5+50;
int n,Ans;
char s[N];
int main(){
	scanf("%d%s",&n,s);
	for(int i=0;i<n-1;i++)
	if(s[i]==s[i+1]){
		if(s[i]==s[i+2]||(i+2==n))s[i+1]=(s[i]^'B')?'B':'G';//字母相同或者到最后
		else s[i+1]='R'+'G'+'B'-s[i]-s[i+2];
		Ans++;
	}
	printf("%d\n%s",Ans,s);
}
```

---

