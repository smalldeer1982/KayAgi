# [NERC 2019] Balls of Buma

## 题目描述

Balph 正在学习玩一款名为 Buma 的游戏。在这个游戏中，他会得到一排彩色球。他需要选择一个新球的颜色以及插入的位置（在两个球之间、所有球的左侧或所有球的右侧）。

当球被插入后，以下情况会反复发生：如果某个颜色相同的球段由于之前的操作变长，并且其长度达到至少 $3$，那么该球段的所有球都会被消除。

例如，考虑一排球 $\tt{AAABBBWWBB}$。假设 Balph 选择了一个颜色为 $\tt{W}$ 的球，并将其插入到第六个球之后，即两个 $\tt{W}$ 的左侧。在 Balph 插入这个球后，$\tt{W}$ 颜色的球段变长，长度变为 $3$，因此这些球会被消除，此时球排变为 $\texttt{AAABBBBB}$。接着，$\tt{B}$ 颜色的球段变长，长度变为 $5$，因此这些球也会被消除，球排变为 $\texttt{AAA}$。此时没有球段再被拉长，因此消除过程结束。

请帮助 Balph 计算有多少种选择新球颜色和插入位置的方式，可以导致所有球被消除。

## 样例 #1

### 输入

```
BBWWBB```

### 输出

```
3```

## 样例 #2

### 输入

```
BWWB```

### 输出

```
0```

## 样例 #3

### 输入

```
BBWBB```

### 输出

```
0```

## 样例 #4

### 输入

```
OOOWWW```

### 输出

```
0```

## 样例 #5

### 输入

```
WWWOOOOOOWWW```

### 输出

```
7```

# 题解

## 作者：weifengzhaomi (赞：9)

## 题目大意

现在有一个字符串，可以选择任意一个位置插入一个字符。插入后**如果某个同颜色球的连续段因之前某个操作而变长，且其长度达到至少 $3$，则该连续段的所有球都会被消除**。

求选择新球颜色和插入位置使得所有球最终被消除的方案总数。

## 思路

首先，$n \le 3 \times 10 ^ 5$，所以，这道题肯定不能暴力来做。

那么，既然题目说了，要使得最后可以全部消掉，那么，我们就可以分析一下字符串的结构，来解决问题，下面是解决方法：

1. **压缩字符串**：先将字符串压缩成连连续块的形式，记录每一个块的字符和长度。
2. **检查对称性**：只有当块的数量为奇数时才可能完全消除，因为需要有一个中心块。
3. **验证**：
   - 所有块必须对称（除中心块外）。
   - 对称块的长度之和至少为 $3$（除了中心块）。
   - 中心块的长度至少为 $2$。

那么，我们该如何实现呢。

考虑用类似双指针的思想用于检查对称性，每次如果遇到了不满足条件的块，即可提前结束。

时间复杂度：$O(n)$。

更多细节详见代码。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<char,int>> f;//防止数组开小，用vector
int n,ans;
string s;
bool flag = true;
int main(){
	cin >> s;
	for (char ch : s) if (f.empty() || f.back().first != ch) f.emplace_back(ch,1); else f.back().second++;
	n = f.size();
	if (n % 2 == 1){
		for (int i = 0;i < n;i++)
			if (f[i].first != f[n - 1 - i].first || (i != n / 2 && f[i].second + f[n - 1 - i].second < 3)){flag = false;break;}
		if (flag && f[n / 2].second >= 2) ans = f[n / 2].second + 1;
	}
	printf("%d\n",ans);
}
```

---

## 作者：Chenyuze24 (赞：2)

这题其实很水。
## Part1 分析
我们可以用[双端队列](https://oi-wiki.org//ds/queue/#%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97)来维护字符串，令其为 $q$。

```cpp
deque<char> q(str.begin(),str.end());
```
考虑如果它能让所有球被消除需要什么。

- 中间的字符出现的连续数量肯定要比 $2$ 大，这样才能加入一个字符后消掉它。
- 若不管出现数量，两端的字符必须回文，比如 $\text{AAABBBCCBAA}$，称为字符回文。
- 回文的前后两段字符个数的总数量必须要严格比 $2$ 大。
  
那么有了这些要求后，就可以写了。首先保证它是字符回文的，那么第一个元素要和最后一个相等。那么我们记 $c$ 为 ```q.front()```。那么我们需要保证它是字符回文的，因而分别从前，后两端删去 $c$，用 $ans$ 去记录 $c$ 在这两段中出现的次数。

```cpp
while (!q.empty() && q.front() == c) {
	q.pop_front();
	ans++;
}
while (!q.empty() && q.back() == c) {
	q.pop_back();
    ans++;
}
```
我们需要保证 $ans>2$，则当 $ans<3$ 时就可以退出了。如果 $q$ 已经空了，那么就直接输出 $ans+1$ 即可，就是说中间的 $ans$ 个字符有 $ans+1$ 个空隙能插入（包括两端）。最后如果什么都没输出过的话，就在最后输出 $0$ 即可，代表无法让所有球都被消除。

## Part2 细节

- 每次 $ans$ 要初始化。
- 每次的循环都是在 $q$ 非空这个条件下执行的。
## Part3 代码

```cpp
#include<bits/stdc++.h>//万能头。
using namespace std;
string str;
void read(){//读入。
	cin>>str;
}
void solve()
{
	deque<char> q(str.begin(),str.end());//双端队列。
	while (!q.empty() && q.front() == q.back()) {//必须q非空。
		char c = q.front();//取出队首。
		int ans = 0;
		while (!q.empty() && q.front() == c) {
			q.pop_front();//记得弹出。
			ans++;
		}
		while (!q.empty() && q.back() == c) {//与上同理。
			q.pop_back();
			ans++;
		}
		if (q.empty() && ans >= 2) {//直接输出。
			cout <<ans+1<<'\n';
			return;
		}
		if (ans < 3) {
			break;//退出。
		}
	}
	cout << 0 ;
}
int main()
{
	read();
	solve();
	return 0;
}
```

---

## 作者：Zenn (赞：1)

## 一、题目传送门

[题目传送门](https://www.luogu.com.cn/problem/P12935)

## 二、题意分析

先输入一个字符串，选择**任意一个位置**插入一个字符，如果某个同颜色球的连续段因之前某个操作而**变长**，且长度 $\ge 2$ 时即可消除。

输出选择新球颜色和插入位置的方式数，可使得字符串完全消除。

## 三、思路详解

因为数据保证，$n \le 3 \times 10^5$，所以不可以暴力枚举。

那我们应该怎么做呢？

我们可以使用‌**双指针**的做法来对称验证。

---

解决这道题的方法：

1. 字符串压缩处理：

- 我们可以将字符串转换为结构体数组，分开依次记录。
- 每个结构体都要记录 $c$ 的值和连续出现的 $a$ 的值。
- 例如 `AAABBB` 会被压缩为 `[(A，3)，(B，3)]`。

  压缩后如下：

  | $i$ | $1$ | $2$ |
  | :-: | :-: | :-: |
  | $c$ | $A$ | $B$ |
  | $a$ | $3$ | $3$ |

2. 双指针**对称验证**：

- 当块的数量为奇数时，才可能完全消除。

  这是为什么呢？

  第一：因为字符串一定需要有一个中心块。

  第二：因为字符串长度最少是 $3$。

3. 特判：

- 如果最后只剩一个中心块的话：

  如果长度 $\ge 2$ 则输出长度 + 1，否则输出 0。

4. 时间、空间复杂度：

- 根据以上思路可以得出我们算法的时间复杂度是 $O(n)$，空间复杂度是 $O(n)$。

## 四、代码实现

详细注释见代码。

---

有注释版：

```cpp
#include<bits/stdc++.h>
using namespace std; 
#define ll long long
string s;
struct Node
{
	ll a;
	char c;
}D[3000005];
int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios::sync_with_stdio(false);//加速输入输出 
	cin.tie(nullptr);
	cin>>s;
	ll aaa=0,cnt=1; 
	D[aaa].c=s[0];
	for(ll i=1;i<=s.size();i++)
	//循环将连续相同字符转换为结构体数组存储 
	{
		if(s[i]==D[aaa].c)
		//当字符与结构体数组末项字符相同时,计数器++ 
			cnt++;
		else//分段存储
		{
			D[aaa].a=cnt;
			aaa++;
			D[aaa].c=s[i];
			cnt=1;
		}
	}
	int flag=0;
	ll x=0,y=aaa-1;//双指针
	while(1)
	{
		if(x==y) break;//剩余中心块时：退出循环
		if((y-x)==1) break;//剩余两个相邻块：退出循环
		if(D[x].c!=D[y].c)//对称性验证 
		{
			flag=1;
			break;
		}
		else 
		{
			if(D[x].a+D[y].a<3)
			{
				flag=1;
				break;
			}
		}
		//指针移动
		x++;
		y--;	
	}
	if(flag==1) cout<<"0";//对称失败 ：输出0 
	else
	{
		if(x==y)//中心块判定
		{
			if(D[x].a>=2) cout<<D[x].a+1;
			else cout<<"0";
		} 
		else//相邻块 
		{
			cout<<"0";
		}
	}
	return 0;
}
```

---

无注释版：

```cpp
#include<bits/stdc++.h> 
using namespace std;
#define ll long long
string s;
struct Node
{
	ll a;
	char c;
}D[3000005];
int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	cin>>s; 
	ll ii=0,cnt=1;
	D[ii].c=s[0];
	for(ll i=1;i<=s.size();i++)
	{
		if(s[i]==D[ii].c)
			cnt++;
		else
		{
			D[ii].a=cnt;
			ii++;
			D[ii].c=s[i];
			cnt=1;
		}
	}
	int flag=0;
	ll x=0,y=ii-1;
	while(1)
	{
		if(x==y) break;
		if((y-x)==1) break;
		if(D[x].c!=D[y].c)
		{
			flag=1;
			break;
		}
		else 
		{
			if(D[x].a+D[y].a<3)
			{
				flag=1;
				break;
			}
		}
		x++;
		y--;
			
	}
	if(flag==1) cout<<"0";
	else
	{
		if(x==y)
		{
			if(D[x].a>=2) cout<<D[x].a+1;
			else cout<<"0";
		} 
		else
		{
			cout<<"0";
		}
	}
	return 0;
}
```

## 五、其它

本文的绝大部分内容为本人原创，由 DeepSeek、GPTzero、AIGC 等 AI 提供核查。

---

## 作者：Clare613 (赞：1)

~~应该是第一篇。~~
## 思路：
对于一个字符串要消得了，就应该有以下几个特点，在这里先讲一个判断所需的数：我们要把字符串压缩，例如 $\tt AAABBBWWBB$，压缩后为：
|i|1|2|3|4|
|:-:|:-:|:-:|:-:|:-:|
|$a_i$|$\tt A$|$\tt B$|$\tt W$|$\tt B$|
|$b_i$|$3$|$3$|$2$|$2$|

相信在做的各位可以看懂这个表格，$a_i$ 表示字符，$b_i$ 表示个数。\
那么现在就说这几个特点：
1. $a_i$ 只有奇数个。
2. $a_i$ 与 $a_{n-i+1}$ 相同。
3. $b_i+b_{n-i+1}\ge3$。

现在解释一下为什么：\
**【1+2】**：\
因为要消除就需要满足相同，奇数是因为回文一定是奇数。\
**【3】**：\
因为至少 $3$ 个才可消除。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[300005];
int b[300005];
signed main(){
	string x;
	cin>>x;
	int cnt=1,n=0;
	for(int i=1;i<x.size();i++){
		if(x[i]==x[i-1]){
			cnt++;
		}
		else{
			n++;
			a[n]=x[i-1];
			b[n]=cnt;
			cnt=1;
		}
	}
	n++;
	a[n]=x[x.size()-1];
	b[n]=cnt;
	if(n%2==0){
		cout<<"0\n";
		return 0;
	}
	bool flag=1;
	for(int i=1;i<=n/2;i++){
		if(a[i]!=a[n-i+1]||b[i]+b[n-i+1]<3){
			flag=0;
			break;
		}
	}
	if(b[n/2+1]<=1) flag=0;
	if(flag==0) cout<<"0\n";
	else cout<<b[n/2+1]+1<<"\n";
	return 0;
}
```

---

## 作者：__VN (赞：1)

# P12935 [NERC 2019] Balls of Buma
[题目传送门 ](https://www.luogu.com.cn/problem/P12935) [题解代码通过记录](https://www.luogu.com.cn/record/221797424)


---
## 题目大意
#### 规则大意
如果某个**颜色相同**的球段由于之前的操作**变长**，并且其**长度达到至少** $3$ ，那么该球段的所有球都会被消除。
#### 目的
插入一个新球使该球段的所有球都被消除，求方案总数。
## 思路
先压缩字符串。

```
for(int i=0;i<s.size();i++){		//压缩字符串
	if((s[i]!=s[i-1]&&i)||!num){	//没有上一区块或与上一区块不同色 
    	num++;
    	if(!m[s[i]]){				//没有出现过此颜色 				
			m[s[i]]=++cnt;			//颜色总数++ 
			a[num][1]=cnt;
		}else a[num][1]=m[s[i]];	//否则对应 
		t[m[s[i]]]++;
	}
	a[num][0]++;					//区块长度++ 
}
```

由题易得，如果要使所有球都被消除，则**有且仅有**一个颜色出现过**奇数次**，且中心区块为这个颜色，此区块即为小球插入的位置。

因为球段必须**由于**之前的**操作变长**，所以左右两边颜色对称分布，故有且仅有一个颜色出现过奇数次。

详解见代码。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,int> m;			//字符对应颜色 
string s;
int cnt=0;					//颜色总数 
int num=0;					//共有区块总数 
int a[300001][2]={};		//区块信息 
int t[300001]={};			//桶,各颜色区块数目 eg:AABAA  A:2,B:1 
bool se(int l,int r){								//是否能全部消除 
	while(l!=0&&r!=num+1){							//如果没有到边界 
		if(a[l][1]!=a[r][1]||a[l][0]+a[r][0]<=2){	//不同色(包含不变长),或小于3 
			return 0;
		}
		l--; 
		r++;
	}
	return 1; 
}
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){		//压缩字符串
		if((s[i]!=s[i-1]&&i)||!num){	//没有上一区块或与上一区块不同色 
			num++;
			if(!m[s[i]]){				//没有出现过此颜色 				
				m[s[i]]=++cnt;			//颜色总数++ 
				a[num][1]=cnt;
			}else a[num][1]=m[s[i]];	//否则对应 
			t[m[s[i]]]++;
		}
		a[num][0]++;					//区块长度++ 
	}
	int f=0;				//出现奇数次的颜色 
	for(int i=1;i<=cnt;i++){
		if(t[i]%2==1){
			if(f){			//如果有两种颜色 
				cout<<0;
				return 0;
			}	
			f=i;			//记录 
		}
	}
	int mid;
	if(num%2==0){
		cout<<0;
		return 0;
	}else mid=num/2+1;
	if(f&&a[mid][1]==f&&a[mid][0]>=2&&se(mid-1,mid+1)) cout<<a[mid][0]+1;	//颜色出现奇数次且能全消 
	else cout<<0;
	return 0;
}
```

---

## 作者：xiaowenxu_qwq (赞：0)

# 思路
当我们插入新球后，要形成连续至少 3 个同色球，才能消除该段球。并且消除后相邻球段需要合并，才可能引发进一步的消除。所以说字符串必须满足以下条件才能消除完成。
1. 字符串的连续颜色段必须对称。
2. 存在一个中间段，使插入同色球后能触发连锁消除（及颜色段的数量为奇数）。
3. 对称段长度之和至少为 3，中间段长度至少为 2（插入新球后为 3）。

判断出是否可以消除后，可以使得所有球被消除的插入位置的方式数就很好算了（题目描述中写到还要输出选择新球颜色，但是样例中没输出，我们以样例输出为主），如果无法全部消除则输出 0，如果可以全部消除则输出中间段的长度**加一**。

代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[300010];//颜色块
int cnt[300010];//每个块的长度
bool book=1;
signed main(){
    string s;
    cin>>s;
    int len=s.length();
    a[1]=s[0],cnt[1]=1;
    int tot=1;
    for(int i=1;i<len;i++){
        if(s[i]==a[tot])
            cnt[tot]++;//颜色相同，增加长度
		else{
            tot++;//增加新颜色块
            a[tot]=s[i];
            cnt[tot]=1;
        }
    }
    //检查对称性：颜色相同且长度和大于等于3
    for(int i=1;i<=tot/2;i++){
        if(a[i]!=a[tot-i+1]||cnt[i]+cnt[tot-i+1]<3){
            book=0;
            break;
        }
    }
    if(tot%2==1)
        if(cnt[(tot+1)/2]<2)//偶数块无解
            book=0;
	else
        book=0;
    if(book)
        printf("%lld",cnt[(tot+1)/2]+1);//中间段长度+1
    else
        printf("0");
    return 0;
}
```

---

## 作者：tuxiaolai (赞：0)

# P12935 题解
## 1 说明
非常不理解，这为什么是一道黄题，个人认为这连橙题都不到。
## 2 思路
按照题意，假设我们有这样一组球：
![](https://cdn.luogu.com.cn/upload/image_hosting/8ncnnlrw.png)
我们可以将这些球按照颜色分组，也就是题目中说的相同颜色的一串球：
![](https://cdn.luogu.com.cn/upload/image_hosting/sfvu39p9.png)
我们在插入一个球后，只有一串球的长度改变，才有可能被消除。因此，我们插入的球一定与旁边一个球颜色相同。在消除了一段球后：
![](https://cdn.luogu.com.cn/upload/image_hosting/obqibwap.png)
如上图，如果消除的一段球两段颜色不同，就无法再消除了。并且，球是以第一段被消除的球为中心依次消除的。那就不难想到：想要消除所有球，第一段被消除的球必然是最中心的那段球。
![](https://cdn.luogu.com.cn/upload/image_hosting/q4b1dx65.png)
如下图，想要消除一段球，添加球的做法就是这段球的个数加一。
![](https://cdn.luogu.com.cn/upload/image_hosting/38bdakj4.png)
## 3 代码
### 逐段分析
首先建立一个 Node 来记录每段球的颜色和个数。$c$ 表示颜色，$n$ 表示个数。
```cpp
struct Node{
    int c=-1,n;
}b[310000];
```
接下来就是初始化了。我们可以用数字代替字母记录颜色。但后来想了想，还不如直接用字母，将 $c$ 改为字符类型即可。
```cpp
int k;//第k段球
string s;
cin>>s;
for(int i=0;i<s.size();i++){
    if(s[i]-'A'==b[k].c){   //s[i]-'A'用于记录颜色，‘A’=0
        b[k].n++;  //若当前球的颜色与上一段相同，就将上一段球的个数+1
    }else{
        k++;
        b[k]={s[i]-'A',1};   //否则就新加一段球
    }
}
```
根据前面的思路，只有球的段数是奇数，才可能全部消除。因此，偶数段的就可以直接输出 0 了：
```cpp
if(!k%2){
    cout<<0;
    return 0;
}
```
然后就是从中间那段球开始，向外检查了。只要对应的两段球颜色不同或个数和小于三，就可以输出 0 了：
```cpp
for(int i=k/2+1;i>=1;i--){
    if(b[i].c!=b[k-i+1].c){
        cout<<0;
        return 0;
    }
    if(b[i].n+b[k-i+1].n<3){
        cout<<0;
        return 0;
    }
}
```
能留到最后的，就是能全部消除的情况了。根据前面的思路，消除一段球的方法数就是这段球的个数加一：
```cpp
cout<<b[k/2+1].n+1;
return 0;
```
### 完整代码
```cpp
//luogu P12935 AC
#include <bits/stdc++.h>
using namespace std;
struct Node{
    int c=-1,n;
}b[310000];
int k;
string s;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]-'A'==b[k].c){
            b[k].n++;
        }else{
            k++;
            b[k]={s[i]-'A',1};
        }
    }
    if(!k%2){
        cout<<0;
        return 0;
    }
    for(int i=k/2+1;i>=1;i--){
        if(b[i].c!=b[k-i+1].c){
            cout<<0;
            return 0;
        }
        if(b[i].n+b[k-i+1].n<3){
            cout<<0;
            return 0;
        }
    }
    cout<<b[k/2+1].n+1;
    return 0;
}
```
非常 Easy 啊！就是感觉难度写错了哈。

tip：注意**中间段**无法直接消除的情况。

---

