# Lock Puzzle

## 题目描述

探险家发现了一个保险箱，里面有大量的宝藏。

保险箱上有一个密码锁，初始时显示的是一个长度为$n$的小写字母字符串$s$。探险家发现，当密码锁上显示的是字符串$t$时，这个密码锁就会打开。

密码锁显示的字符串可以通过形如`shift x`的指令改变。要执行这个指令，探险家需要在$0$到$n$的范围内（包含$0$和$n$）选择一个$x$。此时，设屏幕上显示的字符串$p = \alpha\beta$（其中$\beta$的长度为$x$），那么这个字符串会变为$\beta^{R}\alpha$（$\beta^{R}$表示$\beta$反转后的结果）。

比如，如果屏幕上当前显示$abcacb$，那么执行`shift 4`后屏幕上会显示$bcacab$，因为$\alpha=ab$，$\beta=cacb$，$\beta^{R}=baca$。

探险家担心如果执行了太多了`shift`操作，这个密码锁就会永远锁定。因此，他会给你$n$和字符串$s$和$t$，并且请你给出一个步骤数不大于$6100$的解锁方案。请注意无需最小化步骤数。

## 说明/提示

$1 \leq n \leq 2000$

## 样例 #1

### 输入

```
6
abacbb
babcba
```

### 输出

```
4
6 3 2 3
```

## 样例 #2

### 输入

```
3
aba
bba
```

### 输出

```
-1
```

# 题解

## 作者：Tx_Lcy (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF936C)

## 思路

简单构造题，题目中只有一个 $\rm shift$ 操作，我们考虑拼出其它的操作。

+ 操作 $1$：我们可以把最后一个字符换到第一个，执行 $\rm shift \ 1$。

+ 操作 $2$：我们可以把整个序列 $\rm reverse$，执行 $\rm shift\ n$。

+ 操作 $3$：我们可以翻转任意后缀，为什么呢？
  
  假设当前的串由 $s$ 和 $t$ 拼成，设 $s'$ 表示 $s$ 翻转后的串，$t'$ 同理。
  
  我们可以先 $\rm reverse$ 一下，把原串变成 $t'+s'$，然后再 $\rm shift$ 一下，把原串变成 $s+t'$。
  
+ 操作 $4$：同理，我们可以翻转任意前缀。

接下来我们考虑如何用以上操作构造出一组合法解，首先如果有字符在 $a$ 和 $b$ 中出现的次数不相等，显然无解。

接下来我们从后往前考虑。

设我们当前填到的是 $b_i$，显然 $b_{i+1...n}$ 已经填到 $a_{1...n-i}$ 中了，我们在 $a_{n-i+1...n}$ 中随便找一个 $a_j$ 满足 $a_j=b_i$。

然后我们执行两步操作：先 $\rm reverse$ 后缀 $j$，发现此时 $a_n=b_i$，然后再把 $a_n$ 换到 $a_1$，这样 $a_{1...i}$ 就与 $b_{i...n}$ 相等了。

于是这么模拟就好了，操作次数 $3n$ 次，时间复杂度 $\mathcal O(n^2)$，可以通过本题。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
string a,b;int n;map< char,int >mp;
vector<int>Ans;
inline void shift(int x){
	Ans.push_back(x);string c,bb=a;
	for (int i=n-x+1;i<=n;++i) c+=a[i];
	for (int i=x+1;i<=n;++i) a[i]=bb[i-x];
	reverse(all(c));c=" "+c;
	for (int i=1;i<=x;++i) a[i]=c[i];
}
inline void revers(int l){shift(n),shift(l-1);}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	cin>>a>>b;a=" "+a;b=" "+b;
	for (auto i:a) if (i!=' ') ++mp[i];
	for (auto i:b) if (i!=' ') --mp[i];
	for (auto i:a) if (i!=' ') if (mp[i]!=0){cout<<"-1\n";return 0;}
	for (auto i:b) if (i!=' ') if (mp[i]!=0){cout<<"-1\n";return 0;}
	for (int i=n;i>=1;--i){
		int pl=n;while (a[pl]!=b[i] && pl) --pl;
		if (pl<(n-i)){cout<<"-1\n";return 0;}
		revers(pl);shift(1);
	}
	cout<<Ans.size()<<'\n';
	for (auto i:Ans) cout<<i<<' ';
	cout<<'\n';
	return 0;
}
```








---

## 作者：叶ID (赞：2)

题目链接：[CF936C Lock Puzzle](https://www.luogu.org/problem/CF936C)

【广告】[在个人博客食用](https://toxic2018.ml/1879/)风味更佳

****

### 题目描述

探险家发现了一个保险箱，里面有大量的宝藏。

保险箱上有一个密码锁，初始时显示的是一个长度为$n$的小写字母字符串$s$。探险家发现，当密码锁上显示的是字符串$t$时，这个密码锁就会打开。

密码锁显示的字符串可以通过形如`shift x`的指令改变。要执行这个指令，探险家需要在$0$到$n$的范围内（包含$0$和$n$）选择一个$x$。此时，设屏幕上显示的字符串$p = \alpha\beta$（其中$\beta$的长度为$x$），那么这个字符串会变为$\beta^{R}\alpha$（$\beta^{R}$表示$\beta$反转后的结果）。

比如，如果屏幕上当前显示$abcacb$，那么执行`shift 4`后屏幕上会显示$bcacab$，因为$\alpha=ab$，$\beta=cacb$，$\beta^{R}=baca$。

探险家担心如果执行了太多了`shift`操作，这个密码锁就会永远锁定。因此，他会给你$n$和字符串$s$和$t$，并且请你给出一个步骤数不大于$6100$的解锁方案。请注意无需最小化步骤数。

### 输入格式

第一行一个整数$n$，为字符串$s$和$t$的长度。

随后两行分别输入小写字母构成的字符串$s$和$t$，表示初始时屏幕显示的字符串以及解锁前需要得到的字符串。

### 输出格式

如果不可能打开密码锁，输出`-1`。

否则，第一行输出一个整数$k\ (0\leq k \leq 6100)$，表示需要的操作数量。第二行输出$k$个空格隔开的整数$x_i\ (0\leq x_i \leq n)$，其中$x_i$代表执行操作$shift\ x_i$。

### 数据范围

$1 \leq n \leq 2000$

****

### 无解情况

显然，只有当$s$构成的可重集合与$t$不同时，问题是无解的。

### 设计递归

假设当前屏幕上字符串（此后称为$p$）前缀是$abc$，我们考虑再将两个指定的字符$x$和$y$加进前缀。

手玩一下，很容易就可以发现一个非常好的做法：

```
------ Add 2 chars ------
abc....x..... Find x
       ~~~~~~ Step 1
.....xabc....
         ~~~~ Step 2
..y......xabc Find y
   ~~~~~~~~~~ Step 3
cbax........y
            ~ Step 4
ycbax........
```

此时前缀变成了${\color{red}y}cba{\color{red}x}$。

整理一下信息，我们发现，若要在$p$的前缀上构造出长度为$len\ (len \geq 2)$的字符串$t_1[0..len-1]$，那么只要先在$p$的前缀上构造出$t_1[1..len-2]^{R}$，然后再令$x=t_1[len-1]$，$y=t_1[0]$，执行上述步骤即可。这样，我们就可以递归解决问题。

### 边界条件

不难发现，以上递归不能处理的情况是$len=0$和$len=1$。

对于$len=0$，无需执行任何操作，直接返回即可。

对于$len=1$，我们要将$t_1[0]$（下面称之为$x$）字符放到$p$开头。使用下面方法即可：

```
------ Get init char ------
......x..... Find x
       ~~~~~ Step 1
...........x
           ~ Step 2
x...........
```

### 分析步骤数

如果$n$是奇数，那么需要先使用$2$步来将第一个字符放到$p$开头（边界条件），然后随后还要使用$4 \times ((n-1)/2)$步进行递归构造。$n$最大可以取到$1999$，那么步骤数是$4000$，完全没问题。

如果$n$是偶数，只需要使用$4 \times (n/2)$步进行递归构造。$n$最大可以取到$2000$，步骤数是$4000$，同样没问题。

### 分析复杂度

只论递归的话，复杂度$O(n)$。

如果考虑使用暴力算法进行$shift$操作和字符查找，总时间复杂度为$O(n^2)$。而时限有$2$秒，因此$O(\text{能过})$

### 具体实现

可以发现，递归时要求构造为前缀的字符串，要么是$t$的子串，要么是$t$的子串反转。

设计递归函数时，传入三个参数`l,r,d`，其中$d$为$1$时表示是子串，$d$为$-1$时表示子串反转。如果$d=1$，那么子串区间为$[l..r]$，否则为$[r..l]$。

这种设计比较容易实现。

### 代码

$Talk\ is\ cheap,\ show\ me\ the\ code$

```cpp
// status: [Accepted]
// oj:     [luogu]

#include<bits/stdc++.h>
using namespace std;

/*

------ Get init char ------
......x.....    int idx = lastIndexOf(x);
       ~~~~~    do_shift(n-idx-1);
...........x
           ~    do_shift(1);
x...........


------ Add 2 chars ------
abc....x.....   int idx = lastIndexOf(x);
       ~~~~~~   do_shift(n-idx);
.....xabc....
         ~~~~   do_shift(idx-len+2);
..y......xabc   idx = indexOf(y);
   ~~~~~~~~~~   do_shift(n-idx-1);
cbax........y
            ~   do_shift(1);
ycbax........

*/

int n;
string s;
string t;
// 存储答案 
vector<int> ans;

// 进行shift操作，并记录到答案中 （此处直接在s串上操作） 
void do_shift(int x) {
    ans.push_back(x);
    
    string tmp = s.substr(s.length()-x);
    s = string(x,' ') + s.substr(0,s.length()-x);
    
    for(unsigned i=0;int(i)<x;i++) {
        s[x-i-1] = tmp[i];
    }
}

// 检查能否完成任务。如果能，正常返回，否则直接输出-1并结束程序 
void test() {
    int st[26];
    for(int i=0;i<26;i++) {
        st[i] = 0;
    }
    for(int i=0;i<n;i++) {
        st[s[i]-'a'] ++;
        st[t[i]-'a'] --;
    }
    for(int i=0;i<26;i++) {
        if(st[i]) {
            cout<<-1<<endl;exit(0);
        }
    }
    return;
}

// 将t的子串或子串反转形式构造为s的前缀（此处直接在s串上操作） 
void buildString(int l,int r,int d) {
    int len = (r-l)*d+1;
    
    // 边界判断 
    if(len==0) return;
    if(len==1) {
        int idx = s.find_last_of(t[l]);
        // 直接忽略掉x==0的shift操作 
        if(n-idx-1 > 0) do_shift(n-idx-1);
        do_shift(1);
        return;
    }
    
    // 递归构造 
    buildString(r-d,l+d,-d);
    
    // 加入2个新的字符 
    char x = t[r];
    char y = t[l];
    
    int idx = s.find_last_of(x);
    do_shift(n-idx);
    if(idx-len+2 > 0) do_shift(idx-len+2);
    idx = s.find(y);
    do_shift(n-idx-1);
    do_shift(1);
    return;
}

// 输出最终答案 
void print() {
    cout<<ans.size()<<'\n';
    for(unsigned i=0;i<ans.size();i++) {
        if(i) cout<<' ';
        cout<<ans[i];
    }
    cout<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin>>n>>s>>t;
    
    // 测试能否完成 
    test();
    
    // 构造 
    buildString(0,n-1,1);
    
    // 该函数在s!=t时会RE，用于在调试时快速判断是否写挂 
    assert(s==t);
    
    // 输出结果 
    print();
}

```

评测记录：[R24483982](https://www.luogu.org/record/24483982)


---

## 作者：adolphshi (赞：1)

现在要提速，也要保证质量。

## 思路

### 分析性质

我们会发现，题目要求的 $6100$ 次实际上就是 $3\times n$ 次，也就是对于一位，我们要用三次将它转到正确的位置。

先分析操作，实际上就是将末尾的一段字符串翻转到开头，再继续手玩样例可以发现，这个翻转会使在里面的依旧在里面，靠外的依旧靠外。

### 尝试
我们再来试一试，设 $1,2,3,x,\cdots,4,\cdots$,那么我们这一步的操作是要将 $4$ 挪到 $3$ 的后面。 

我们需要分析，什么时候 $4$ 能够接到 $3$ 后面，当且仅当 $3$ 为左端点，$4$ 为翻转区间的开始时用一步可以拼到一起。

那我们知道了我们的首要任务时将 $3$ 从中间挪到左边，我们发现只能先将 $x$ 之后的全部翻转过去，然后再整体反转，这样我们的序列就变成了:$3,2,1,x,\cdots,4,\cdots$ 但是这样把 $4$ 挪过去，我们发现在这段完成的区间两侧有没完成的区间，很烦。一次我们考虑怎么把这些东西搞掉。

我们发现其实并不需要将整体翻转，直接翻转一部分就可以了，也就是从 $\cdots,4,\cdots,x,1,2,3$ 可以只翻转 $4$ 之后的部分，这样就变成了 $3,2,1,x,\cdots,\cdots,4$ 那么再进行一次操作后就变成了 $4,3,2,1,x,\cdots,\cdots$ 非常好看，而且方便我们继续递推。

### 得到正解

但是我们只讨论了（已经排好的区域）正向的情况，得到的是反向的，因此我们在考虑一下反向的情况，类比之前的方法不难得到（其中标红的代表翻转的区间）:

$$[\color{red}3,2,1,x,\cdots,4,\cdots\color{black}] \rarr [\cdots,4,\color{red}\cdots,x,1,2,3\color{black}] \rarr [3,2,1,x,\cdots,\cdots,\color{red}4\color{black}]\rarr [4,3,2,1,x,\cdots,\cdots]$$

用了三步，并且得到的序列也是反向的，就可以直接进行递推了~~也就是说根本就出现不了正向的情况~~，最后再整体反转一下就可以了。

与此同时我们发现，第二部所翻转的数的个数就是 $4$ 在这组操作前在数组的位置，记录一下即可。

我们再看序列，中 $\cdots$ 的部分，这一部分可以根据样例手推得到，结果就是操作前 $4$ 前的 $\cdots$ 顺序不变，$4$ 后的 $\cdots$ 顺序相反。直接模拟修改即可。

对于无解，当我们向后找不到要放到这一位的字符时，就无解。

## code

``` cpp
#include <bits/stdc++.h>
#define _F(x,y,z) for(int x=y;x<=z;x++)
#define F_(x,z,y) for(int x=z;x>=y;x--)
#define TF(x,y,z) for(int x=head[y],z;x;x=nex[x])

using namespace std;

typedef long long ll;
typedef double dou;
typedef const int ci;
typedef pair<int,int> pii;

ci maxn=2e6+10;

int n;
char s[maxn],t[maxn];
vector<int> ans;
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	scanf("%s",t+1);
	_F(i,1,n)
	{
		int x=i,y=-1;
		_F(j,i,n)
		{
			if(s[j]==t[i])
			{
				y=j;
				break;
			}
		}
		if(y==-1)
		{
			puts("-1");
			return 0;
		}
		ans.push_back(n);
		ans.push_back(y-1);
		ans.push_back(1);
		_F(j,i,y-1)
		{
			swap(s[j],s[y]);
		}
		_F(j,y+1,n)
		{
			if(n-j+1+y<=j)
				break;
			swap(s[j],s[n-j+1+y]);
		}
	}
	ans.push_back(n);
	printf("%d\n",ans.size());
	for(int a:ans)
	{
		printf ("%d ",a);
	}
	return 0;
}
```

---

## 作者：wizardMarshall (赞：1)

## 题意

给定一种操作，将字符串 $s$ 的某个后缀翻转后放到前面，最后变为字符串 $t$。这个后缀的长度 $x$ 即为这次操作（格式为 `shift x`），求操作过程（无需最小化步骤）。

## 思路

小清新构造题。

首先对于 $s$ 与 $t$ 的字符不一样的肯定不满足。

否则，考虑到一次 `shift x` 操作是在 $s$ 前面添加字符串，我们可以把 $t$ 中的字符倒过来一个一个塞到 $s$ 的首位。即 $\texttt{***s**}$ 经过操作后变为 $\texttt{s*****}$。

于是对于 $t_i$，我们首先在 $s$ 中找到 $s_j=t_i$，然后先将 $s_j$ 移到末尾，再使用 `shift 1` 的操作使它移到第一个。

至于这个移到末尾的操作，可以先将整个字符串翻转（即 `shift n`），然后将后面一部分再次翻转得到。

举个例子，初始字符串为 $\texttt{abc**s***}$（$\texttt{abc}$ 为之前排好的、已经有序的字符串，$\texttt{s}$ 为目标字符），我们希望把 $\texttt{s}$ 放到第一个，同时不破坏 $\texttt{abc}$ 的顺序。

1. 将整个字符串翻转得 $\texttt{***s**cba}$。

2. 将 $\texttt{s}$ 之后的这一部分执行操作，得到 $\texttt{abc*****s}$。

3. 执行 `shift 1` 操作，得到 $\texttt{sabc*****}$。

倒序对于每个 $t_i$ 这么做即可。每次至多三次操作，$n \le 2000$，操作数不超过 $6000$。

注意：如果目标字符本身就在末尾，或者第一次操作的时候在第一位，则可省略一些步骤。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
char s[2005], t[2005];
int c[30];
signed main() {
	int n;
	cin >> n;
	scanf("%s%s", s + 1, t + 1);
	for (int i = 1; i <= n; i++) {//事先统计字符个数
		c[s[i] - 'a']++;
		c[t[i] - 'a']--;
	}
	for (int i = 0; i < 26; i++) {
		if (c[i]) {
			cout << -1;
			return 0;
		}
	}
	vector <int> ans;
	for (int i = n; i >= 1; i--) {
		//t[i]翻到第一个
		int id = n;
		for (int j = n - i + 1; j <= n; j++) {//前面排好的不动，在后面找目标字符
			if (s[j] == t[i]) {
				id = j;
				break;
			}
		}
		//翻转[id,n]后缀，把目标字符s_id翻到第一个。即为先全reverse，然后后面翻到前面
		if (id != 1) {
			if (id != n) {//原来就在后面的可以不动
				ans.push_back(n);//全部翻转
				ans.push_back(id - 1);//结合例子理解（反转后原来id前面这部分到了后面，长度是id-1）
				int l = id, r = n;
				while (l < r) {//对s执行反转操作，及时更新，避免之后找t_i时出现错误
					swap(s[l], s[r]);
					l++;
					r--;
				}
			}
			ans.push_back(1);
			char temp = s[n];
			for (int i = n; i >= 2; i--) {//同样，执行shift 1操作，更新s
				s[i] = s[i - 1];
			}s[1] = temp;
		}
	}
	cout << ans.size() << endl;
	for (auto  i : ans) {//输出操作序列
		printf("%d ", i);
	}
	return 0;
}
```

---

## 作者：OceanLiu (赞：0)

神仙构造题。

看到楼下的递归代码，我来提供一个非递归版的，做法也不太一样。

首先如果两个字符串26种字符数量不相等可以直接判掉。然后考虑增量构造：每次把一个字符放到已经构造好的串的后面。假设我们现在已经枚举到了目标串$t$的第$i$个字符$x$，且现在串$s$形如：

$AxBC$

其中$x$是我们要找的第$i$个字符，$x$前面的串为$A$，$x$后面是没有构造好的串$B$和已经构造好的串$C$。记$R(A)$表示翻转过后的串，有如下变换：

$AxBC$

$R(C)R(B)Ax$

$xR(C)R(B)A$

$R(A)BCx$

一共翻转三次。其中三次位置分别为：1.$x$在串$s$中的位置$j$；2.字符串最后一个位置$n$；3.字符串第一个位置$1$。总共翻转次数为$3\times n$，可以通过本题。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=2005;
char ch[N],s[N],tmp[N];
int n,c1[30],c2[30],ans[N*3],top;
int main()
{
	scanf("%d",&n);
	scanf("%s%s",ch+1,s+1);
	for (int i=1;i<=n;i++)
		c1[ch[i]-'a']++,c2[s[i]-'a']++;
	for (int i=0;i<26;i++)
		if (c1[i]!=c2[i]){
			puts("-1");
			return 0;
		}
	for (int i=1;i<=n;i++)
	{
		int j=n-i+1;
		while(ch[j]!=s[i]) j--;
		if (j==n) continue;
		ans[++top]=n-j,ans[++top]=1,ans[++top]=n;
		int m=0;
		for (int k=j-1;k;k--) tmp[++m]=ch[k];
		for (int k=j+1;k<=n;k++) tmp[++m]=ch[k];
		tmp[++m]=ch[j];
		memcpy(ch,tmp,sizeof(ch));
	}
	printf("%d\n",top);
	for (int i=1;i<=top;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

