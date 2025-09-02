# Dual Trigger

## 题目描述

[Ngọt - LẦN CUỐI (đi bên em xót xa người ơi)](https://youtu.be/kSjj0LlsqnI)

ඞ



There are $ n $ lamps numbered $ 1 $ to $ n $ lined up in a row, initially turned off. You can perform the following operation any number of times (possibly zero):

- Choose two non-adjacent $ {}^\dagger $ lamps that are currently turned off, then turn them on.

Determine whether you can reach configuration $ s $ , where $ s_i = 1 $ means the $ i $ -th lamp is turned on, and $ s_i = 0 $ otherwise.

 $ {}^\dagger $ Only lamp $ i $ and $ i + 1 $ are adjacent for all $ 1 \le i < n $ . Note that lamp $ n $ and $ 1 $ are not adjacent when $ n \ne 2 $ .

## 说明/提示

In the first test case, the sequence of operation could have been as follows (note that initially $ s $ is all zero): $ \mathtt{0000000000} \to \mathtt{\color{red}{1}0000000\color{red}{1}0} \to \mathtt{1\color{red}{1}00000\color{red}{1}10} \to \mathtt{110\color{red}{1}0\color{red}{1}0110} $ .

In the third test case, we don't have to do any operation.

In the fourth test case, we cannot do any operation, but we need the first lamp to be on. Therefore, it is impossible to achieve the desired state.

## 样例 #1

### 输入

```
5
10
1101010110
10
1001001110
6
000000
1
1
12
111111111111```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：baokun (赞：7)

## part 1 题意
你有 $n$ 个灯的状态，初始全为关的状态，问能不能通过每次将不相邻的两个灯打开以达成该状态。
## part 2 思路
对于奇数个打开的灯一定完不成，因为每次只能打开偶数个灯，不管多少个偶数相加都得偶数。

对于偶数个打开的灯，需要注意的是当只有两个灯打开并且它们相邻时不可能实现，其他情况都一定可以实现。因为即使是最差的情况，我们都可以通过交叉的方式完成配对，所以可以完成。
## part 3 需要注意的地方
$\bullet$ 多测要清空。

$\bullet$ 最好习惯性开 long long。
## part 4 code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	string s;
	while(t--){
		cin>>n;
		cin>>s;
		int num=0;
		bool flag=0;
		for(int i=0;i<n;i++){
			if(s[i]=='1')num++;
			if(s[i]=='1'&&s[i-1]=='1')flag=1;
		}
		if(num&1||(flag&&num==2)){
			cout<<"NO"<<endl;
			continue;
		}cout<<"YES"<<endl;
		
	}
	return 0;
}
```

---

## 作者：BJqxszx_zhuyukun (赞：3)

# 写在前面

这是本蒟蒻第 $4$ 次发题解，如果写的不好或者码风很烂请见谅。

# 思路

此题每次操作要求是两盏灯不相邻，我们不难有一个贪心的想法，对于第 $i$ 盏灯，从 $i+2$ 开始遍历，关掉第一个遍历到的灯。显然，由于是就近关灯，所以一定最优（蒟蒻不会证明）。

有了这个思路就很好写代码了。

# 代码

有一个要注意的点，如果 1 的个数是奇数，直接 NO 就行了，因为一次关两盏灯不可能关掉奇数盏灯。\
AC code:
```cpp
#include<iostream>
#include<string>
using namespace std;
int t,n,l,cnt;
string s;
int can(int x){
	for(int i=x;i<s.size();i++) if(s[i]=='1') return i;
	return 0;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		cnt=0;
		for(int i=0;i<s.size();i++) if(s[i]=='1') cnt++;
		if(cnt&1){
			cout<<"NO\n";
			continue;
		}
		l=0;
		while(cnt){
			if(s[l]=='0'){
				l++;
				continue;
			}
			if(can(l+2)){
				cnt-=2;
				l++;
			}
			else{
				cout<<"NO\n";
				break;
			}
		}
		if(!cnt) cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：Kindershiuo (赞：3)

# 解题思路
其实我们只要观察一下样例我们就不难发现，就几种情况：
### 当我们亮着的灯是偶数
不管怎么样我们都是可以通过操作达到这个目标字符串的，除了只有两盏灯亮着，且这两盏灯挨在一起时，我们是没有办法的，其他的不管多少盏灯挨在一起我们都能通过隔位点亮，例如有四盏灯亮且它们挨在一起时，我们可以先点亮第一个和第三个，再点亮第二个和第四个，总之只要不是两盏灯挨在一起且只有两盏灯时，我们都能通过操作点亮。
### 当我们亮着的灯是奇数
那么我们不管怎么操作都是行不通的。

所以这题其实很简单，就是看亮灯的数量是奇数还是偶数，然后亮灯数是两盏的时候特判一下就行。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T;

void solve() {
	int n;
	string s;
	cin >> n >> s;
	map<char, int>ma;
	for (int i = 0; i < n; i++) {
		ma[s[i]]++;
	}
	if (ma['1'] == 2) {
		int t1 = s.find('1');
		int t2 = s.find('1', t1 + 1);
		if (t2 - t1 == 1)
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
	} else if (ma['1'] % 2 != 0)
		cout << "NO" << endl;
	else {
		cout << "YES" << endl;
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：lflby (赞：2)

# 思路

首先如果亮灯的数量是奇数则直接输出 NO。

用 $a_i$ 数组来存开始时的状态（$0$）。

用 $b_i$ 数组来存要变成的状态。

然后用 dfs 来算做：

找到第一个 $a_i$ 和 $b_i$ 不同的灯，

再找到第二个 $a_j$ 和 $b_j$ 不同的并且 $i$ 和 $j$ 不相邻的灯，

把这两个灯的状态变成 $1$。

每次判断是否 $a=b$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int q,n;
int a[55],b[55];
bool flag;
bool cheak()
{
	for (int i = 1; i <= n; i++) if (a[i]!=b[i]) return false;
	return true;
}
void dfs()
{
	if (cheak()||flag==true)
	{
		flag=true;
		return ;
	}
	int x;
	for (int i = 1; i <= n; i++)
	{
		if (a[i]!=b[i])
		{
			x = i;
			break;
		}
	}
	a[x]=1;
	for (int i = 1; i <= n; i++)
	{
		if (a[i]!=b[i]&&i!=x&&x+1!=i&&x-1!=i)
		{
			a[i]=1;
			dfs();
			a[i]=0;
		}
	}
	a[x]=0;
}
int main()
{
	cin>>q;
	while (q--)
	{
		cin>>n;
		int t = 0;
		for (int i = 1; i <= n; i++)
		{
			char c;
			cin>>c;
			b[i]=c-'0';
			a[i]=0;
			if (b[i]==1) t++;
		}
		if (t%2==1)
		{
			cout<<"NO\n";
			continue;
		}
		flag = false;
		dfs();
		if (flag) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：fanjiayu666 (赞：1)

首先，题目要求每次只能选**不相邻且关闭的两个打开**，让你判断能否达到**给出的目标状态**。

我打开们不难想到：既然是要**两个两个**开，那结果肯定只能有**偶数个**打开，那如果目标状态中有**奇数个**打开，肯定是**不能满足要求**的，所以我们可以写出下列代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010],n,t;
int sum;//sum是计算总和，因为只会有1和0，所以只要加起来即可得到1的个数。
int main(){
    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        sum=0;
        cin>>n;
        flag=0;
        for(int i=1;i<=n;i++){
            scanf("%1d",&a[i]);//%1d是代表读入1位数
            sum+=a[i];//加和
        }
        //cout<<sum<<endl;
        if(sum%2==0)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;//判断输出
    }
}
```

#### 你以为这就完了？

不，

大家可以注意到，题目要求**不相邻带两个打开**，这会使产生一种特殊情况：
$$\cdots11\cdots$$
（两端为空或为 $0$）

这时，目标中只有中间两个打开，可它们却相邻，所以，当 $1$ 的个数等于 $2$，并相邻时，要特判，修改后代码如下：
（其余注释见上一班代码）
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010],n,t,flag;
int sum;
int main(){
    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        sum=0;
        cin>>n;
        flag=0;
        for(int i=1;i<=n;i++){
            scanf("%1d",&a[i]);
            sum+=a[i];
            if(i>1){
                if(a[i]==a[i-1]&&a[i]==1)flag=1;
            }//当i大于等于2时开始判断是否与上一个相等，相等用flag标记。
        }
        //cout<<sum<<endl;
        if(sum==2&&flag==1){cout<<"NO"<<endl;continue;}//特判当sum=2并flag有标记的情况。
        if(sum%2==0)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
```
（勿抄）

这道题其实考验我们的审题能力，因为题目中有特殊说明。

所以我劝大家切水题时，大家还是要细心，看题，注意限制。

---

## 作者：Miracle_1024 (赞：1)

怎么没有人写题解，那我来写一个吧。
## 思路：
  观察题目以及样例发现，$1$ 的数量是奇数就输出 No，否则是  Yes。如果 $1$ 的数量是偶数，当 sum 为 $2$ 时，如果两个 $1$ 在一起就输出 NO，否则就输出 Yes。
  
## 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll t,n,ans,cf,x;
string s; 
int main() {
	cin>>t;
	while(t--){
		ans=0,x=0;
		cin>>n>>s;
		for(int i=0;i<s.size();i++)if(s[i]=='1')ans++;
        ll f=unique(s.begin(),s.end())-s.begin();
		for(int i=0;i<f;i++)if(s[i]=='1')x++;
		if(n==2&&ans!=0)cout<<"No"<<endl;
		else if(ans%2==1)cout<<"No"<<endl;
		else if(x==1&&ans==2)cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
}
```

---

## 作者：fengyuxuan (赞：0)

# 题目大意

一个字符串一开始每个字符都是 `0`，现在每一次操作可将两个不相邻的 `0` 改为 `1` 问这个字符串能否变为 $S$。

# 题目解析

- 首先每次只能修改两个 `0` 变为 `1` ，所以如果目标状态中有奇数个 `1` ，则一定不能变为这个状态。

- 其次如果目标状态刚好只有两个 `1`，由于每次修改要修改不相邻的两个字符，所以如果这两个 `1` 相邻，则无法变为这个状态。

- 剩下的情况，显然都可完成。

# 最终代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100];
string s;
int main()
{
	
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		int sum=0;
		for(int i=0;i<n;i++)
			if(s[i]=='1')
				a[++sum]=i;//记录位置
		if(sum%2==1||(sum==2&&a[2]-a[1]==1))
			cout<<"No"<<endl;
		else
			cout<<"Yes"<<endl;
	}
	return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题目大意

现在有 $n$ 盏灯，是全部关着的。请你每一次打开第 $i$ 和第 $j$ 盏灯，需要满足 $i$ 和 $j$ 是两个不相邻的数字。请问对于每一组数据，是否能够办到。能够办到输出 `YES`，不能输出 `NO`。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1951A)

贪心算法。

题目说两个两个开灯，那么必须是有偶数个灯开着的。如果读入的一组数据中的 $n$ 为奇数，那么就可以直接输出 `NO` 了。

由于题目是要求两个不相领的灯，所以如果是两个相邻的灯且是亮着的，就也可以直接输出 `NO` 了。

接下来，由于是打开两盏不相邻的灯，如果是以下的这一种数据：

```
1
4
0110
``` 

由于题目说只能打开两盏不相同的灯，所以，两个 $1$ 相邻也是不能实现的，要输出 `NO`。

其余的情况，即可输出 `YES`。

---

## 作者：Walrus (赞：0)

对于点灯问题，分奇偶讨论。

发现我们每次点灯时只有 3 种情况：

- 把两盏灭的点亮
- 把两盏亮的熄灭
- 把一盏亮的熄灭一盏灭的点亮

观察到总的亮灯数的变化量一定是偶数。

若字符串中 1 的个数时奇数一定无解，若是偶数且不是仅有两个 1 相邻时一定有解，反之无解。

具体点灯的方法就是隔位点，比如如果要把第 1 盏灯点亮可以先点 1 和 3 再点 3 和 5，以此类推。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
using namespace std;

int n, q, cnt, fir;
string s;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> q;
	while(q--) {
		cnt = fir = 0;
		cin >> n >> s, s = ' ' + s;
		rep(i, 1, n) {
			if(!fir && s[i] == '1') fir = i;
			cnt += s[i] == '1';
		}
		
		
		if(cnt & 1) cout << "NO" << '\n';
		else {
			if(cnt == 2 && s[fir] == s[fir + 1]) cout << "NO" << '\n';//判断是否有两盏灯挨着的无解 
			else cout << "YES" << '\n';
		}
	}
	
	return 0;
}
```

---

## 作者：xk2013 (赞：0)

题目传送门：[CF1951A Dual Trigger](/problem/CF1951A)

## 前置知识
- **分析题目**；
- 小学数学；
- STL 中的 `count` 函数。

## 题意简述
本题让我们判断在灯泡全灭的初始状态下能否按规定操作达到目标状态。

## 解题思路
解一道题最重要的是审题。由于每次都能且只能开 $2$ 盏灯，且初始灯泡全灭，可以很容易得出一条结论：目标状态中 `1` 的个数（即灯泡亮的个数）为奇数时绝对不可能达到。

但是 `1` 的个数为偶数时就一定能达到了吗？由于题目中说了，只能打开不相邻的 $2$ 盏灭的灯，于是我们可以举出一个反例：
```plain
6
001100
```
这种情况也是不能实现的，也就是说，当 `1` 的个数只有 $2$ 个，且二者相邻，那么这种情况也是不可以实现的。由此，我们就可以很容易实现代码了。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <algorithm>
#include <iostream>
#include <string>

int main(void)
{
	int T;
	std::cin >> T;
	
	while (T--)
	{
		int n;
		std::string s;
		
		std::cin >> n >> s;
		
		if (std::count(s.begin(), s.end(), '1') % 2 == 1) // 奇数情况直接输出
		{
			std::cout << "NO" << std::endl;
		}
		else // 偶数
		{
			if (std::count(s.begin(), s.end(), '1') == 2 && s.find("11") != std::string::npos) // 注意一定要特判
			{
				std::cout << "NO" << std::endl;
			}
			else
			{
				std::cout << "YES" << std::endl;
			}
		}
	}
	
	return 0;
}

```
----------------------
这是本四升五蒟蒻小学生的第 12 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2024/07/01：初版。

---

## 作者：qusia_MC (赞：0)

## 思路

很简单，不难想到：

- 对于每次操作，我们能也只能让亮着灯加两盏，所以，若目标亮灯数是奇数时则无法完成。

- 我们只能加两个不相邻的，也就是说，当只有两盏灯是亮着的且相邻时我们无法完成。

证明：

前提是 $n$ 是偶数。

我们设目标中亮着的灯的坐标分别是 $a_{1\sim n}$。

我们将 $a_{1\sim n}$ 排个序之后，能证明，我们只需要同时将 $a_1,a_3$，$a_2,a_4$ 操作就可以了，也就是 $a_i$ 与 $a_{i+2}$ 操作。

## CODE
```
#include<bits/stdc++.h>
using namespace std;
#define kkksc03chen_zhe ios::sync_with_stdio(0);cout.tie(0);cin.tie(0);

int main()
{
	kkksc03chen_zhe//神坤助力！
	int T,n,a[114514],cnt,l,r,i;char c;
    cin>>T;
    while(T--)
    {
    	cnt=0;l=0;r=0;
    	cin>>n;
       for(i=1;i<=n;i++)
       {
       	cin>>c;
       	    if(c=='1')
       	    {
       		    if(l==0)l=i;
       		    r=i;
       		    cnt++;
		    }
	   } 
	   if(cnt&1||(cnt==2&&abs(r-l)==1))//不行
	   {
	   	cout<<"NO";
	   }
	   else cout<<"YES";//可以
	   cout<<"\n";
	} 
	return 0;
}
```

---

