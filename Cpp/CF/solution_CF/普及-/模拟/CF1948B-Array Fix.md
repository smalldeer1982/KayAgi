# Array Fix

## 题目描述

给定一个长度为 $n$ 的非负整数序列 $a$，你可以进行如下操作任意次：

- 选择序列中第 $i$ 个数 $a_i$，将其从原序列中删除。然后将这个数字十进制上的每一位数，按原顺序放回序列。

比如，原来有序列 $[12, 3, 45, 67]$，如果选择其中第 $3$ 个数进行操作，那么序列就会变为 $[12, 3, 4, 5, 67]$。

再比如，原来有序列 $[2, 10]$，如果选择其中第 $2$ 个数进行操作，那么序列就会变为 $[2, 1, 0]$。

现在请你判断，是否存在一组操作方案，使得这个序列变得**单调不降**。

即，令最终序列长度为 $k$，那么有 $a_1 \leq a_2 \leq \cdots \leq a_k$。

## 说明/提示

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^3, 2 \leq n \leq 50, 0 \leq a_i \leq 99$。

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
3
4
12 3 45 67
3
12 28 5
2
0 0```

### 输出

```
YES
NO
YES```

# 题解

## 作者：_KHIN (赞：5)

#### 题意简述

给你一个序列，你可以对这个序列中的每个数进行拆分，使得最后整个序列单调不递减，询问是否有解。

#### 做题思路

我们定义一个变量 $now$ 表示当前序列中的最后一位，也就是当前序列中的最大值。

对于每一个 $a_i$： 
- 如果它的十位小于等于个位且 $now\ge a_i$ 的十位，那么将 $now$ 赋值为 $a_i$ 的十位即可。
- 如果上一条不成立但 $a_i\ge now$，那么将 $now$ 赋值为 $a_i$ 即可。
- 如果以上两条都不成立，那么无解。

### 程序
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[55],t,now=0; 
signed main()
{
	cin>>t;
	while(t--)
	{
		now=-1e9;
		int flag=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]<now)
			{
				flag=1;
			}
			else
			{
				if(now<=a[i]/10&&now<=a[i]%10&&a[i]/10<=a[i]%10)
				{
					now=a[i]%10;
				}
				else
				{
					now=a[i];
				}
			}
		}
		if(!flag)
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
    return 0;
}
```

---

## 作者：What__can__I__say (赞：4)

简易模拟题。~~（只是入门也太低估它了吧······）~~

写给那些与我一样顺序枚举数组的人（一开始就倒序枚举数组的巨佬请自行跳过）：

第一感觉就是枚举输入的 $x$ 数组，若有 $x_i$ 大于 $x_{i+1}$ 就把 $x_i$ 分解。最后把分解完的数组遍历，看看是不是单调不减。但是这个思路存在漏洞，比如以下这组数据：$12$ $45$ $6$ $78$ $9$ $100$，明明只要把 $12$，$45$，$78$ 都分解就行，可是程序输出 No。这是因为一开始 $12$ 并不大于 $45$，所以在这个思路下 $12$ 没有被分解，而 $45$ 则因为大于 $6$ 被分解了，导致最后因为 $12$ 大于 $4$ 而没有构成单调不减序列。那我们怎么办呢？

其实，只要换个方向遍历数组即可。从后往前遍历数组就可以排除该数列的“后效性”，通过本题！！

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define mod 722733748
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
il int min(int x,int y){return (x<=y)?x:y;}
il int max(int x,int y){return (x>y)?x:y;}
const int JYAAKIOI=1145141919810;
int n,x[10086],a[10086],l,T; 
signed main(){
	T=rd();
	while(T--){
		memset(a,0,sizeof a);
		l=0;
		n=rd();
		for(int i=1;i<=n;++i)x[i]=rd();
		a[++l]=x[n];
		for(int i=n-1;i>=1;--i){//从后往前
			if(x[i]>x[i+1]){
				while(x[i]!=0){
					a[++l]=x[i]%10;
					x[i]/=10;
				}
			}
			else a[++l]=x[i];
		}
		bool p=1;
		for(int i=1;i<l;++i){
			if(a[i]<a[i+1]){//因为是倒着存的
				printf("No\n");
				p=0;
				break;
			}
		}
		if(p)printf("Yes\n");
		/*for(int i=1;i<=l;++i)wr(a[i]),putchar(' ');
		putchar('\n');*/
	}
	return 0;
}//1 6 12 45 6 78 9 100
```

---

## 作者：2022_37_yzyUUU (赞：3)

# CF1948B 题解

## 题意

给定一个长度为 $n$ 的非负整数序列 $a$，你可以进行如下操作任意次：

- 选择序列中第 $i$ 个数 $a_i$，将其从原序列中删除。然后将这个数字十进制上的每一位数，按原顺序放回序列。

现在请你判断，是否存在一组操作方案，使得这个序列变得**单调不降**。

## 思路

我们可以把本数列从后往前扫一遍，令 $mi$ 为当前扫过的最小值。

如果有一个数大于已经扫过的最小值，就尝试拆开，如果拆开后还是大于，就不存在方案。

否则就改变 $mi$ 的值，具体操作请看代码。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[55];
int main(){
	
	ios::sync_with_stdio(false); 
	cin.tie(0),cout.tie(0);//优化 
	
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int mi=a[n],f=0;//初始化 
		for(int i=n-1;i>=1;i--)
			if(a[i]>mi)//如果不符合单调不降 
				if(mi<a[i]%10||a[i]%10<a[i]/10){//如果拆开后依然不符合单调不降 
					cout<<"NO\n";//无解 
					f=1;
					break;
				}
				else mi=a[i]/10;//取最小值 
			else mi=a[i];//取最小值
		if(!f)cout<<"YES\n";
	}
	return 0; 
}

```

## End

---

## 作者：liyifan202201 (赞：2)

# CF1948B Array Fix
[题目链接](https://www.luogu.com.cn/problem/CF1948B)
### 思路
首先，看到 $n \le 50$ 我们可以考虑 $DFS$ 解决此题，提交一看[Time limit exceeded on test 3](https://vjudge.net.cn/solution/49905293/aa1byHvBQxy11L0ygH8p)， 于是必须考虑优化时间复杂度。

众所周知，**位数小的数**肯定比**位数大的数**小，所以**拆分**的前面必须全部都是**拆分**，后面所有的都**不能拆分**

所以我们可以枚举断点 $i$ ，然后拆分 $1 \sim i-1$，$i \sim n$ 不拆分，最后判断是否合法，具体看代码。
### 代码
[AC记录](https://www.luogu.com.cn/record/151205655)
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	//多组数据
	while(t--) {
		//输入
		int n;
		vector<int>tv;
		cin>>n;
		string s;
		for(int i=1;i<=n;i++) {
			int it;
			cin>>it;
			tv.push_back(it);
		}
		bool yn=0;
		//枚举断点
		for(int i=0;i<n;i++) {
			//拆分 1 ~ i-1
			vector<int>v;
			for(int j=0;j<i;j++) {
				string ts=to_string(tv[j]);
				for(auto k:ts) {
					v.push_back(k-'0');
				}
			}
			//其他不拆分
			for(int j=i;j<n;j++) {
				v.push_back(tv[j]);
			}
			//判断
			bool f=false;
			for(int j=1;j<v.size();j++) {
				if(v[j-1]>v[j]) {
					f=true;
					break;
				}
			}
			if(f==0) {
				yn=1;
				break;
			}
		}
		//输出
		if(yn==0) {
			cout<<"NO\n";
		}
		else {
			cout<<"YES\n";
		}
	}
	return 0;
}
```

---

## 作者：hmzclimc (赞：2)

# 题解：CF1948B Array Fix
## 思路
模拟和贪心。

这道题目还是有一定坑点的，赛时我成功的在第二个点上 Wa 了六次。

言归正传，题意很简单，就是修改这个序列中的元素，使这个序列单调不下降。我们可以一步一步的思考，对于每一个序列中的数：

1. 如果这个数可以拆开（大于等于 10 并且前一个数小于等于十位上的数小于等于个位上的数），那就直接拆开；
2. 如果无法拆开，但是还满足前一个数小于等于这个数的条件，那就不要管它了；
3. 如果不能拆开，也不满足前一个数小于等于这个数的条件，那就说明无法完成操作，应该输出 NO 了。

## 主要代码
```cpp
const int maxn=205;
int arr[maxn];
void solve(){
    int n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    } // 读入
    int ls=0; // 记录上一个数
    for(int i=1;i<=n;i++){
        if(arr[i]>=10&&ls<=arr[i]/10&&arr[i]/10<=arr[i]%10){// 如果这个数可以拆开
            ls=arr[i]%10;// 那就直接拆开并且记录个位上的数
        }else if(ls<=arr[i]){// 无法拆开
            ls=arr[i];// 记录
        }else{
            puts("NO");return ;// 不满足题意要求
        }
    }
    puts("YES");
}
```

感谢阅读，有问题请指出，谢谢。

---

## 作者：12345yes (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1948B)

### 题意简述
给你一个序列 $a_1, a_2,\ldots, a_n(0 ≤ a_i ≤ 99)$，尝试将它们拆分或不拆，最终使得整个序列单调不递减，询问是否可行。

### 思路
因为 $a_i$ 不是一位数就是两位数，所以可以直接将其每一位上的数取出。

记 $last$ 为上一个处理完的数（即到目前为止最大的数）。

1. 若十位和个位单调不递减，且十位和个位皆大于等于 $last$，则 $last=v$；
2. 若 1 条件中有任何一条不满足，但 $a_i$ 大于等于 $last$，则 $last=a_i$；
3. 若以上条件中无一条满足，则无法使整个序列单调不递减；

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e3+10;
int T,n,a[MAXN];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		int last=-1e9,flag=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			int u=a[i]/10,v=a[i]%10;
			if(u<=v && u>=last && v>=last)
				last=v;
			else if(a[i]>=last)
				last=a[i];
			else flag=1;
		}
		if(flag) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：2)

## CF1948B

### Brief

有一个长度为 $n$（$2 \le n \le 50$）的数组 $a$（$0 \le a_i \le 99$），问你是否能通过把 $a$ 的某几个数十位个位拆分后（例：$38 \rightarrow 3, 8$）变成不下降的序列。**注意，$a_i < 10$ 不能拆分。**

### Sol

显然的，我们可以拿一个数组 $b$ 去存拆分后的数组。遍历 $a_i$ 每一个数，分为以下情况：

1. $a_i \ge 10$ 且 $a_i$ 的十位大于等于 $b$ 数组的最后（也就是刚才存进去的）且 $a_i$ 的个位大于等于 $a_i$ 的十位：这种情况说明 $a_i \ge 10$ 并且拆分存入 $b$ 后满足升序，直接把 $a_i$ 拆分存进 $b$。

2. $a_i < 10$ 且 $a_i$ 的十位大于等于 $b$ 数组的最后：这种情况说明 $a_i \ge 10$ 且存入 $b$ 后满足升序，直接存进 $b$。

3. 以上都不满足：直接存进 $b$。

遍历完后把 $b$ 检查一遍（是否不下降），分别输出 `YES` 或 `NO`。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <unordered_map>
 
using namespace std;
 
using ll = long long;
 
const int kMaxN = 55, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;
 
int n, a[kMaxN], b[kMaxN << 2], id = 0;
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    memset(b, 0, sizeof b), id = 0; // 初始化
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
      cin >> a[i];
    }
    bool f = 1; // 存 YES 或 NO
    for (int i = 1; i <= n; ++ i) {
      if (a[i] >= 10 && a[i] / 10 >= b[id] && a[i] % 10 >= a[i] / 10) { // 第一种
        b[++ id] = a[i] / 10; // 十位数存
        b[++ id] = a[i] % 10; // 个位数存
      } else if (a[i] < 10 && a[i] >= b[id]) { // 第二种情况
        b[++ id] = a[i]; // 直接存
      } else { // 否则
        b[++ id] = a[i]; // 直接存
      }
    } 
    for (int i = 1; i < id; ++ i) { // 检查
      if (b[i] > b[i + 1]) { // 如果下降
        cout << "NO\n"; // 输出 NO
        f = 0; // 标记
        break; // 跳出循环
      }
    }
    if (f) { // 如果没有输出 NO
      cout << "YES\n"; // 输出 YES
    }
  }
  return 0;
}
```

---

## 作者：GenesisCrystal (赞：2)

~~还是比较简单的~~

## Solution

设更改后的数组是 $o$，令 $o_{tot}$ 为更改后的最后一个元素。

对于每一个 $a_i$，如果 $a_i \ge 10$ 并且 $a_i$ 的个位数 $\ge a_i$ 的十位数 并且 $a_i$ 的十位数 $\ge o_{tot}$，那么将 $a_i$ 的十位数和个位数依次加入 $o$，此时 $o_{tot}$ 为 $a_i$ 的个位数。

如果不满足上述条件且 $a_i\ge o_{tot}$，那么将 $a_i$ 加入 $o$，此时 $o_{tot}$ 为 $a_i$。

如果都不行，那么就输出 `NO`。

如果到了 $i=n$ 的时候，都是可行的，那么就输出 `YES`。

## Code

```cpp
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;

int t, n, a[kMaxN];

int main() {
  for (cin >> t; t; t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
		int o[kMaxN] = {}, tot;
		bool f = 1;
		for (int i = 1; i <= n; i++) {
			if (a[i] >= 10 && a[i] / 10 >= o[tot] && a[i] % 10 >= a[i] / 10) {
				o[++tot] = a[i] / 10;
				o[++tot] = a[i] % 10;
			} else if (a[i] >= o[tot]) {
				o[++tot] = a[i];
			} else {
				f = 0;
				break;
			}
		}
		cout << (f ? "YES\n" : "NO\n");
  }
  return 0;
}
```

---

## 作者：_Tatsu_ (赞：1)

## 题意
有一个长度为 $n$ 序列 $ a_1 , a_2, ...... , a_n ( 0 \le a_i \le 99,2 \le n \le 50 ) $ ，将这个序列拆分，当然也可以补拆分。最终使序列单调不减。
## Solution
根据数据范围， $a_i$ 是一位或两位数，于是可以用两个变量分别将个位与十位存入。

我们定义变量 $maxx$ ，用来存入现在最大的数。

如果十、个位单调不递减，且十、个位都大于最大值，则更新最大值为个位;


如果上述条件中不满足，但 $a_i \ge maxx$ ，则最大值更新为 $a_i$ ;

如果都不行，无法使原序列单调不减，就输出```NO```。
## Code
````````````````````cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1005];
signed main()
{
	ios::sync_with_stdio(0);
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	int n,t;
	cin>>t;
	for (int i=1;i<=t;i++)
    {
		int maxx=INT_MIN;
		bool pd=0;
		cin>>n;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
			int s=a[j]/10,g=a[j]%10;
			//十位和个位 
			if (s<=g&&s>=maxx&&g>=maxx)
			{
				maxx=g;
				//第一个条件 
			}
			else if(a[j]>=maxx)
			{
				maxx=a[j];
				//第二个条件 
			}
			else
			pd=1;//无法做到单调不减 
		}
		if (pd==1)
		cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
    }
	return 0;//华丽结束~~~ 
}
``````````````````````````````````
###### ~~管理员最帅了，求过~~
#### 如有雷同，纯属巧合

---

## 作者：RyanLi (赞：1)

传送门：洛谷 [Array Fix](https://www.luogu.com.cn/problem/CF1948B) | Codeforces [B. Array Fix](https://codeforces.com/contest/1948/problem/B)

更佳的阅读体验：[CF1948B 题解](https://blog.ryanli.top/index.php/archives/45/)

---

**简要题意**：给定一个长度为 $n$ 的非负整数序列 $a$，可以任意次选择序列中的一个数，将其从原序列中删除，然后将这个数字十进制上的每一位数，按原顺序放回序列。判断是否可能使得这个序列变得单调不降。

我们可以从后往前遍历整个序列。如果发现当前数大于后面的数，那么有两种情况；

- 当前数是一位数，不能拆分，因此直接判定无合法方案。
- 当前数是两位数，就进行拆分。拆分后需要继续判断，如果十位大于个位，也直接判定无合法方案。

遍历时，使用一个变量记录当前数后面的数，遇到拆分数字时就能避免改变数组内部的元素。

```cpp
#include <iostream>
using namespace std;

const int N = 60;
int t, n, a[N], last;
bool flag;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        flag = false;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        last = a[n];
        for (int i = n - 1; i >= 1; --i) {
            if (a[i] > last) {
                if (a[i] % 10 > last) {
                    flag = true;
                    break;
                } if (a[i] >= 10) {
                    if (a[i] / 10 > a[i] % 10) {
                        flag = true;
                        break;
                    } last = a[i] / 10;
                } else last = a[i];
            } else last = a[i];
        } cout << (flag ? "NO\n" : "YES\n");
    } return 0;
}
```

---

## 作者：_Sky_Dream_ (赞：1)

# [传送门](https://www.luogu.com.cn/problem/CF1948B)

给你 $n$ 个数（保证最多为两位数），可以将他们拆分，成为单调不降序列。问是否存在一种拆法满足题意？

首先，如果这个数本身满足条件，不需要拆分。

其次，如果这个数拆分后，即可满足单调不降，那么拆分（这一条要优先考虑，这样才可以为以后做好更加划算的准备）。

如果以上两种拆法都不可以满足单调不降，那么就说明无解。


## 注意：
- 换行；
- 单调不降，等于也是满足条件的。

AC Code:
```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define itn int
#define tni int
#define tin int
#define nit int
#define nti int
#define int long long
using namespace std;
int T; 
void Main(){
	int n,x,previous=-1919810;
	bool flag=true;//哨兵
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>x;
		int gewei=x%10,shiwei=x/10;//分别取出十位和个位
		if(shiwei<=gewei&&gewei>=previous&&shiwei>=previous)previous=gewei;//做更划算的拆分
		else if(x>=previous)previous=x;//做亏本的拆分
		else flag=false;//不能拆分
	}
	if(flag)cout<<"YES";
	else cout<<"NO";
	cout<<endl; 
}
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>T;
	while(T--)Main();
	exit(0);
}
signed main(){Enchanted();}

```

---

## 作者：zhuhongye (赞：0)

## 题目意思
给定一个序列，可以对序列元素执行任意次拆分操作，问最后是否能使序列**单调不下降**。

## 解题思路
题目数据不大，$n$ 最大只有 $50$，所以这道题可以考虑暴力 $+$ 贪心。首先我们要考虑的贪心策略是：后面的数尽量不要拆分，因为拆分意味着数会变得更小。设当前位置为 $i$，当 $a_i >a_{i+1}$，我们就要把 $a_i$ 拆分，然后更新 $a_i$ 的值，否则直接跳过。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const ll N = 55;

ll T;
ll n,a[N]; 
signed main()
{
	cin>>T;
	
	while(T--){
		cin>>n;
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		
		bool tmp=0;
		for(int i=n-1;i>=1;i--){
			if(a[i]<=a[i+1])continue;
			
			ll t[N],b=a[i],s=0;
			memset(t,0,sizeof(t));
			
			while(b)t[++s]=b%10,b/=10;
			bool flag=false;
			
			t[0]=a[i+1];
			for(int j=1;j<=s;j++){
				if(t[j]>t[j-1]){
					flag=true;
					break;
				}
			}
			if(flag){
				tmp=1;
				break;
			}
			else {
				a[i]=t[s];
			}
		}
		if(tmp)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：daiyulong20120222 (赞：0)

# 题目大意

给定一个长度为 $n$ 的非负整数序列 $a$，你可以进行如下操作任意次：

> 选择序列中第 $i$ 个数 $a_i$，将其从原序列中删除。然后将这个数字十进制上的每一位数，按原顺序放回序列。

比如，原来有序列 $[12, 3, 45, 67]$，如果选择其中第 $3$ 个数进行操作，那么序列就会变为 $[12, 3, 4, 5, 67]$。

再比如，原来有序列 $[2, 10]$，如果选择其中第 $2$ 个数进行操作，那么序列就会变为 $[2, 1, 0]$。

现在请你判断，是否存在一组操作方案，使得这个序列变得**单调不降**。

即，令最终序列长度为 $k$，那么有 $a_1 \leq a_2 \leq \cdots \leq a_k$。

**本题目含多组数据。**

**【输入】** 第一行，一个正整数 $t$，表示数据组数。

接下来每组数据包含两行：

- 第一行，一个正整数 $n$；
- 第二行，$n$ 个非负整数 $a_i$。

**【输出】** 对于每组数据，如果有解输出 `YES`，否则输出 `NO`。

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^3, 2 \leq n \leq 50, 0 \leq a_i \leq 99$。

# 解题思路

首先，我们需要判断这个序列目前是不是**单调不降**。如果是，直接输出 `YES` ，否则继续判断。

此处我给出一个部分分解法（当然这道题是 ACM 赛制）。

## 部分分解法

考虑**搜索**。

使用 DFS 枚举子集，考虑到每一种情况，在逐个判断。当然，会超时。

## 正解

此处考虑**贪心**。

- 如果一个数比他前面的数小，就把他前面的数按操作进行分割。如果还是小，输出 `NO` ，结束程序。

- 一直往后判断，直到结束，并输出 `YES` 。

由于题目过于简单，此处就不附带代码了。不保证有一些不靠谱的做法。

---

## 作者：Infinite_Loop (赞：0)

# CF1948B
## 题意
给定一个长度为 $n$ 的数组 $a$，且 $0 \le a _ {i} \le 99$，每次操作可以将 $a _ {i}$ 拆成十位和个位，再放入原来的位置，问最终能否使得这个序列单调不降。
## 思路
因为 $0 \le a _ {i} \le 99$，所以我们可以用 $x$ 表示十位上的数，用 $y$ 表示个位上的数，用 $last$ 表示上一个数。当枚举到 $i$ 时，有下面几种情况：

- 当 $x \le y$ 且 $last \le x$ 时，因为要单调不降，所以现在的值要尽可能的小，才有可能成功，所以我们将 $a _ {i}$ 拆掉，把 $last$ 变成 $y$。

- 当第一种情况不满足，但 $last \le a _ {i}$ 时，我们选择不拆 $a _ {i}$，把 $last$ 变成 $a _ {i}$。

- 当前面两种情况都不满足，记 $flag$ 为 $0$，直接跳出循环。

最后如果 $flag = 1$，输出 ```YES```，否则输出 ```NO```。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50+10;
int t,n,a[N]; 
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int flag=1,last=0;
		for(int i=1;i<=n;i++){
			int x=a[i]/10,y=a[i]%10;
			if(x<=y&&x>=last)last=y;
			else if(a[i]>=last)last=a[i];
			else{
				flag=0;
				break;
			}
		}
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：_Delete_ (赞：0)

## 思路

要使序列变成一个非降序序列，只需从后往前扫一遍，如果遇到前面的数比后面的数大，则考虑进行拆分。

拆分时需满足该数可以被拆分，以及拆分出的数要满足非降序。注意，由于拆分后满足非降序，所以将该拆分数重新赋值为十位数即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
int a[105];

//function 
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i>0;i--){
		if(a[i-1]>a[i]){
			int x=a[i-1];
			int xs=x/10,xg=x%10;
			if(xs<=xg&&xg<=a[i]){
				a[i-1]=xs;
			}
			else {
				cout<<"No"<<endl;
				return;
			}
		}
	}
	cout<<"Yes"<<endl;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int t=1;
	cin>>t;
	while(t--)solve();
	
	return 0;
}


```

---

