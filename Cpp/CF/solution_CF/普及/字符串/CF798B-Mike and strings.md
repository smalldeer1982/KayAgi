# Mike and strings

## 题目描述

Mike有n个字符串s1,s2,……，sn，每个字符串均由小写字母构成。 每次移动你可以选择一个字符串si, 第1个字符移动最后，比如字符串 "coolmikecoolmike", 移动1次变成字符串 "oolmikecoolmikec"。

请计算至少需要移动多少次，可以使得n个字符串都变成相同。

## 样例 #1

### 输入

```
4
xzzwo
zwoxz
zzwox
xzzwo
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
molzv
lzvmo
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
kc
kc
kc
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3
aa
aa
ab
```

### 输出

```
-1
```

# 题解

## 作者：风云幻 (赞：4)

stl大法好

说明一下

a.find(b）是指在a这个字符串中查找b并返回b开头字母的位置，没查到就是-1



	#include<bits/stdc++.h>
	using namespace std;
	int n;
	string a[51],b[51];
	int ans=2501;
	int main()
	{
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>a[i];b[i]=a[i]+a[i];//将a【i】复制一下
		}
		for(int i=0;i<n;i++)
		{
			int jians=0;
			for(int j=0;j<n;j++)
			{以a【i】为模板，把别的都变成它
				if(b[j].find(a[i])!=-1)
				{
					jians+=b[j].find(a[i]);//别的变成a【i】的最小步骤
				}
				if(b[j].find(a[i])==-1)
				{
					cout<<-1;//若果查不到，意味着有的字符串不包含在内
					return 0;
				}
			}
			ans=min(ans,jians);
		}
		cout<<ans;
	}
 第一篇题解，求过

---

## 作者：zhoujunchen (赞：2)

~~说句闲话：为什么这题是绿题~~  

做题思路：
----
暴力枚举，我们可以枚举其中一个字符串 $s_i $，然后让其他的字符串都变成 $ s_i $，最后记录一下次数，取一个最小值即能通过。  


- 我们为了让枚举时更简单，可以把每个字符串都复制一遍。 

- STL 里有一个 find 函数，a.find(b) 是指在 a 这个字符串中查找 b 字符串，返回 b 字符串开头字母的位置（下标），没查到返回 -1。

code :
```cpp
#include<bits/stdc++.h>
using namespace std;
#define AC; return 0;
int n,ans=2147483647;
string a[55],b[55];
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		b[i]=a[i]+a[i];//拆环为链，将整个字符串复制一份，方便我们查找 
	}
	for(int i=0;i<n;i++){
		int tmp=0;
		for(int j=0;j<n;j++){
			if(b[j].find(a[i])!=-1)//找到了，有解 
				tmp+=b[j].find(a[i]);//记录答案 
			else{//无解 
				cout<<"-1";
				return 0; 
			}
		}
		ans=min(ans,tmp);//取最小值 
	}
	cout<<ans<<"\n";
	AC;
} 
```

---

## 作者：Zyh_AKer (赞：2)

# Mike and strings 题解
[题目传送门](https://www.luogu.com.cn/problem/CF798B)

~~这简简单单一道字符串模拟，  
为什么还评绿呢？~~
## 题意
给定 $n$ 个字符串 $s_1，s_2 \dots\dots s_n $，每个字符串均由小写字母构成。每次移动你可以选择一个字符串 $s_i$，第 $1$ 个字符移动到最后。

请计算至少需要移动多少次，可以使得 $n$ 个字符串都变成相同。
## 解法
把每个字符串看做一个环，然后化环为链（把这个字符串复制两遍）。  
因为 $n$ 特别小（$n \le 50$）所以我们可以暴力枚举所有**原字符串**，把每个原字符串和每个化环为链后的字符串进行比较，看看能不能在化环为链后的字符串中找到这个原字符串，如果能，就加上原字符串在化环为链后的字符串中第一次出现的位置，否则就输出 $-1$。  
最后还要把每次求得的答案取最小值，这就是最终答案了。  
时间复杂度 $O( ? ^ 2len )$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=0x3f3f3f3f;
string s[60];
string sv[60];
int cnt[60][60]; 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>s[i];
		sv[i]=s[i]+s[i];
	}
	for (int i=1;i<=n;i++)
	{
		int sum=0;
		for (int j=1;j<=n;j++)
		{
			if (sv[j].find(s[i])!=-1) 
			{
				sum+=sv[j].find(s[i]);
			}
			else
			{
				cout<<-1;
				return 0;
			}
		}
		ans=min(ans,sum);
	}
	cout<<ans;
	return 0;
}
```
本蒟蒻第一篇题解，求过。

---

## 作者：COsm0s (赞：2)

## 题意

$n$ 个字符串 $s_1$，$s_2$，……，$s_n$，每个字符串均由小写字母构成。 每次移动你可以选择一个字符串 $s_i$， 第 $1$ 个字符移动最后。至少需要移动多少次，可以使得 $n$ 个字符串都变成相同。

## 思路

+ 首先确定一个关键点：**如果有任意一个字符串的字符种类和各种类所包含的字符个数与其他不同，则无解**。

	其实很好理解，因为无论怎么移动字符，整个串里的字符是恒定的，所以一开始如果没有一致，则无论怎么移也没用。

+ 第二，我们要把字符串看成一个**环**。什么意思呢？因为每次移动开头，所以这是个环。这时候我们用普通环变链操作即可。

+ 最后，在枚举过程中，我们可以采用 STL 大法—— `find` 函数便捷的寻找。

复杂度 $O(n^2len)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[100];
bool vis[500];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> s[i];
		if(i == 1) {
			for(int j = 0; j < s[i].size(); j ++)
			vis[s[i][j] - 96] = 1;
		}
		else {
			for(int j = 0; j < s[i].size(); j ++) {
				if(!vis[s[i][j] - 96]) {
					puts("-1");
					exit(0);
				}
			}
		}
	}//如果字符数量不一，则无解
	int len = s[1].size(), minn = 0x3f3f3f3f;
	for(int i = 1; i <= n; i ++) {
		int ans = 0;
		for(int j = 1; j <= n; j ++) {
			string g = s[j] + s[j];
			if(g.find(s[i]) == -1) puts("-1"), exit(0);
			ans += g.find(s[i]);
		}
		minn = min(minn, ans);
	}//环变链查找次数
	cout << minn;
	return 0;
}

```


---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/CF798B)

唐。

首先显然对于一个字符串翻 $\le len$ 次才有意义。考虑暴力，存下来每一种字符串翻转 $[1,len]$ 后的情况，找到最小的那种就做完了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
map<string,map<int,int> > mp; 
string s[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>s[i];
	for(int i=1;i<=n;i++){
		string p=s[i],q; mp[p][i]=-1;
		for(int j=0;j<s[i].size();j++){
			string z;q+=s[i][j];
			for(int k=j+1;k<s[i].size();k++)	z+=s[i][k];
			z+=q;
			if(mp[z][i]==0)	mp[z][i]=j+1;
			else	mp[z][i]=min(mp[z][i],j+1);
//			cout<<i<<" "<<z<<" "<<j+1<<endl;
		}
	}
	string p;
	int ans=INT_MAX;
	for(int i=0;i<s[1].size();i++){
		p+=s[1][i];	string q;
		for(int j=i+1;j<s[1].size();j++)	q+=s[1][j];
		q+=p;
		int sum=((mp[q][1]==-1)?0:mp[q][1]);
		bool f=false;
		for(int j=2;j<=n;j++){
			if(mp[q][j]==0)	f=true;
			sum+=((mp[q][j]==-1)?0:mp[q][j]);
		}
		if(f==true)	continue;
		else	ans=min(ans,sum);
	}
	if(ans==INT_MAX)	cout<<"-1"<<endl;
	else cout<<ans<<endl;
	return 0;
}
/*
2
molzv
lzvmo
*/ 

```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF798B)     
一道简单的字符串模拟。   
就这还为什么评绿呢。     
## 题意
给定 $n$ 个字符串，定义一个字符串变换操作为：将该字符串的第一个字符移动到最后。现在要求你找到一个字符串 $t$，使得输入的 $n$ 个字符串都可以通过变换操作变换到 $t$ 且所需操作次数最少。只需要输出操作次数或报告无解即可。    
## 解法
显然，这个变换操作是会循环的。    
所以我们处理出所有的循环情况，用 `map` 分别保存每个情况的出现次数和所需的最少操作次数即可。   
但是字符串变换过程中可能会重复。所以我们需要再开一个 `map` 进行记录。      
我们可以使用 `unordered_map`，来获得更快的时间。    
时间复杂度 $O(nm^2)$，$m$ 指字符串长度。可以通过。   
[CODE](https://www.luogu.com.cn/paste/ic3bcyvk)

---

## 作者：xvl_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF798B)

一道字符串题。

由于 $n$ 非常小，可以暴力枚举字符串。我们可以枚举其中一个字符串 $s_i$，然后让其他的字符串变成 $s_i$，最后记录一下次数，取一个最小值即可。

在枚举第二个字符串的时候可以将它再复制一份自己到后面，然后可以用 `find` 函数来统计。当然，如果找不到，这个字符串永远不可能变成 $s_i$，输出 $-1$。

### Code

```cpp
#include <bits/stdc++.h>

namespace xvl_ { 
    #define ll long long
    #define IMAX INT_MAX;
    #define LMAX LONG_LONG_MAX
    void debug() { std :: cerr << "debug" << "\n"; } 
    template <typename T> inline T Max(T a, T b) { return a > b ? a : b; }
    template <typename T> inline T Min(T a, T b) { return a < b ? a : b; }
    template <typename T, typename... Args> inline T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
    template <typename T, typename... Args> inline T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
int n, ans = IMAX;
string s[55];
int main() {
    /*
    freopen("InName.in", "r", stdin);
    freopen("OutName.out", "w", stdout);
    */
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) {
            if ((s[j] + s[j]).find(s[i]) != -1) cnt += (s[j] + s[j]).find(s[i]); // 加上次数
            else {
                cout << -1; // 无解
                return 0;
            }
        }
        ans = Min(ans, cnt); 
    }
    cout << ans;
    return 0;
}
```


---

## 作者：御坂13558号 (赞：1)

~~之前看到它是绿题感觉是被恶评的，后来却发现它确实有这个资格。。。~~

首先，这整篇题解都是围绕着一个中心思想展开的：

### 把`字符串`看作`字符环`

------------

什么？？你说你听不懂？？好吧，这是人话一点的方式：


——————————————————————————————————

1. 你要把用数组来储存的字符串用 _**单向循环链表**_ 储存

TIP：仅仅是在你的脑海里，这样做只是为了思考方便，在实际写代码是并不需要

2. 想象一下你在对这种`"字符串"`进行一次操作的时候，你要干什么

什么都不需要！你只要改变一下头指针就可以了！

### 也就是说，在对字符串做操作时，并没有改变他的连接方式（或说顺序），用数组储存也一样！！！

——————————————————————————————————

好了，回归我们的题目，现在有两个要点：`判断是否能行` 和 `判断最短步骤`

## 判断是否能行：

如果有解决方案的话，那么所有的字符串都一定是同一个字符环的 **_不同剪开方式_** 

所以，我们将第一个字符串`复制一遍`（比如abc->abcabc)，再在复制的字符串里寻找之后的字符串，如果任意一个为-1（无法找到）就直接输出-1

## 判断最小次数

和`判断是否能行`相似，我们还是在复制串里找其他的串，把找到的结果加起来。我们不能直接用find的返回值，还要进行一个"加工处理"：如返回值为0则是0，否则为字符串（注意不是复制串）长度-返回值，再加起来；嗯，还要考虑`相似性`的问题，我们要将所有串都复制一遍找其他的串，然后找最小值

为了广大的P党们：

解释：string的find函数：
```
a.find(b);
在a中找b
如果找不到返回-1
否则返回b在a中第一次出现的下标
```

------------

## 代码：
`判断是否能行` 和 `判断最小次数` 较为相似，我将它们合并了

半成品：#90错误

O($n^2$)
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <string>

#define itn int

using namespace std;

int readInt(){
    char c;int x=0;bool f=false;
    c=getchar();
    while (c<'0'||c>'9') {
        if(c=='-')f=true;
        c=getchar();
    }
    while (c>='0'&&c<='9') {
        x=x*10+c-'0';
        c=getchar();
    }
    return x=(f ? 0-x : x);
}
int change(int x,int y){
    return x==0 ? 0 : y-x;
}
string a[51],t;
int sum=0,c,n,ans=1e9;
int main(){
    n=readInt();
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        sum=0;
        t=a[i]+a[i];
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            if((c=t.find(a[j]))==-1){sum=1e9;break;}
            sum+=change(c,a[j].length());
        }
        ans=min(ans,sum);
    }
    if(ans==1e9){cout<<-1;return 0;}
    cout<<ans;
    return 0;
}
```
成品：

此题正解应是`在第二层的字符中找第一层的`，即在第二层循环内复制`j`；
```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <string>

#define itn int

using namespace std;

int readInt(){
    char c;int x=0;bool f=false;
    c=getchar();
    while (c<'0'||c>'9') {
        if(c=='-')f=true;
        c=getchar();
    }
    while (c>='0'&&c<='9') {
        x=x*10+c-'0';
        c=getchar();
    }
    return x=(f ? 0-x : x);
}
string a[51],t;
int sum=0,c,n,ans=1e9;
int main(){
    n=readInt();
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        sum=0;
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            t=a[j]+a[j];
            if((c=t.find(a[i]))==-1){sum=1e9;break;}
            sum+=c;
        }
        ans=min(ans,sum);
    }
    if(n==1){cout<<0;return 0;}
    if(ans==1e9){cout<<-1;return 0;}
    cout<<ans;
    return 0;
}
```

---

## 作者：xukuan (赞：1)

由于我被禁言，无法提交翻译，希望审核题解的管理们代为转告，谢谢！

translated by @[nowayout](https://www.luogu.org/space/show?uid=1856)


#### 题目描述：

Mike有n个字符串s1,s2,……，sn，每个字符串均由小写字母构成。 每次移动你可以选择一个字符串si, 第1个字符移动最后，比如字符串 "coolmikecoolmike", 移动1次变成字符串 "oolmikecoolmikec"。

请计算至少需要移动多少次，可以使得n个字符串都变成相同。

#### 输入格式：

第一行，一个整数n(1≤n≤50)。
接下来n行，每行一个字符串，每个字符串的长度相当，且长度不超过50。

#### 输出格式：

输出最小移动次数，无解则输出-1.

———————————————————————————————————————————————

# 题解正文：

数据范围很小(50*50)，直接模拟即可

先判断能不能实现，如果能实现，再判断最小要几步

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 2147483647
using namespace std;

ll n,sum,ans,bo;
string s[100];
bool a[200];

int main(){
	scanf("%lld",&n);
	for(ll i=1; i<=n; i++) cin>>s[i];
	for(ll i=0; i<s[1].size(); i++) a[s[1][i]-97]=true;
	
	for(ll i=1; i<=n; i++){
		for(ll j=0; j<s[i].size(); j++){
			if(!a[s[i][j]-97]){
				printf("-1");
				return 0;
			}
		}
	}
	
	sum=INF; ans=0;
	for(ll i=1; i<=n; i++){
		for(ll j=1; j<=n; j++){
			if(i!=j){
				for(ll k=0,l=0; k<s[i].size()&&l<s[i].size(); l++){
					if(s[i][k]==s[j][l]){
						if(l==0) bo=0;
						else bo=l;
						while(s[i][k]==s[j][l]&&k<s[i].size()){
							k++;
							if(l==s[i].size()-1) l=0;
							else l++;
						}
						if(k==s[1].size()) break;
						else{
							k=0;
							l=bo;
							bo=-1;
						}
					}
				}
				if(bo==-1){
					printf("-1");
					return 0;
				}
				ans+=bo;	
			}
		}
		sum=min(sum,ans);
		ans=0;
	}
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：guangh (赞：0)

## 前言
---------

~~这真是绿题吗？~~

养成好习惯，做题先看数据范围很小，直接暴力模拟就可以通过。

## 解法
----------

把字符串看成一个环，然后[化环为链](https://blog.csdn.net/xiji333/article/details/87631735)。

STL 里有一个 find 函数，`a.find(b)`  是指在 `a` 这个字符串中查找 `b` 字符串，返回 `b` 字符串开头字母的位置（下标），没查到返回 -1。
## Code
---------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int sum = 2500;
string a[55],b[55];//别用char 
int main(){
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>a[i];
		b[i] = a[i]+a[i];//通过复制a[i]模拟一个环，方便查找 
	}
	for(int i = 1;i <= n;i++){ 
		int ans = 0;
		for(int j = 1;j <= n;j++){
			if(b[j].find(a[i]) != -1){
				ans += b[j].find(a[i]);//a[i]在b[j]里开头字母的位置是它的移动次数 
			}
			else{
				cout<<"-1";//如果找不到则无解 
				return 0;
			} 
		}
		sum = min(ans,sum);//打擂台 
	}
	cout<<sum;
}
```
[传送门](https://www.luogu.com.cn/problem/CF798B)

---

