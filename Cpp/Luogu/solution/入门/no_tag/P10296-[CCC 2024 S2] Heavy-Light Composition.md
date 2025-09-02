# [CCC 2024 S2] Heavy-Light Composition

## 题目描述

在一个只包含小写字母的字符串中，称一个字母是重的当且仅当它在字符串中出现了超过一次，否则称它是轻的。

给定一些字符串，对于每个字符串，请判断其中重的字母和轻的字母是否满足交替出现。（即要么每个奇数位的字母都是重的，每个偶数位的字母都是轻的，要么每个奇数位的字母都是轻的，每个偶数位的字母都是重的。）

## 说明/提示

**【样例 1 解释】**

第一个字符串由轻字母、重字母、轻字母、重字母组成。

第二个字符串以两个连续的重字母结尾。

第三个字符串由重字母、轻字母、重字母、轻字母组成。

**【样例 2 解释】**

第一个字符串全部是轻字母。

第二个字符串由重字母、轻字母、重字母组成。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证字符串中只包含小写字母，$2\leq T\leq 10^4$，$2\leq N\leq 100$。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | $T$ 的范围 | $N$ 的范围 | 其他限制 |
| :-: | :-: | :-: | :- |
| $5$ | $2 \leq T \leq 4$ | $2 \leq N \leq 4$ | 字符串只包含 `a` 和 `b` |
| $5$ | $2 \leq T \leq 10$ | $2 \leq N \leq 30$ | 无 |
| $2$ | $2 \leq T \leq 100$ | $2 \leq N \leq 100$ | 只有字母 `a` 是重的；其他字母是轻的 |
| $3$ | $2 \leq T \leq 10^4$ | $2 \leq N \leq 100$ | 无 |

## 样例 #1

### 输入

```
3 4
abcb
bcbb
babc
```

### 输出

```
T
F
T
```

## 样例 #2

### 输入

```
2 3
abc
bcb
```

### 输出

```
F
T
```

# 题解

## 作者：Emplace (赞：8)

# P10296 [CCC 2024 S2] Heavy-Light Composition题解
## 1.算法
这道题很明显是一道字符串。
## 2.思路
我们可以统计出每个字符出现的次数，然后先看如果是“重”的字符（也就是这个字符出现多次）开头，那就看奇数位是不是全是“重”，偶数位全是轻（也就是这个字符出现一次）。然后再看如果是“轻”的字符开头，那就把上面操作反过来做就行了。
## 3.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100];
int main(){
	cin>>t>>n;
	for(int i=1;i<=t;i++){
		char s[1000];
		memset(a,0,sizeof(a));
		cin>>s;
		for(int i=0;i<n;i++){
			int k=s[i]-'a'+1;
			a[k]++;
		}
		int f=0;
	//	cout<<a[s[0]-'a'+1]<<" "<<endl;
		if(a[s[0]-'a'+1]>1){
			for(int i=1;i<n;i++){
				if(i%2==0){
					if(a[s[i]-'a'+1]<=1){
						f=1;
						break;
					}
				}
				if(i%2==1){
					if(a[s[i]-'a'+1]>1){
						f=1;
						break;
					}
				}
			}
		}
		if(a[s[0]-'a'+1]<=1){
			for(int i=1;i<n;i++){
				if(i%2==0){
					if(a[s[i]-'a'+1]>1){
						f=1;
						break;
					}
				}
				if(i%2==1){
					if(a[s[i]-'a'+1]<=1){
						f=1;
						break;
					}
				}
			}
		}
		if(f==1){
			cout<<"F"<<endl;
		}
		else{
			cout<<"T"<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Genshin_ZFYX (赞：7)

简单的模拟题，用一个桶记录每个字符出现的次数，再判断字符串是否满足交替出现。

本题坑点：多组数据要记得初始化哦！

极短的 AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[(int)'z'+5];
signed main()
{
   cin.tie(0)->sync_with_stdio(0);
	int t,n;cin>>t>>n;
	while(t--)
	{
		memset(a,0,sizeof(a));//多组数据别忘了初始化！ 
		string s;int f=0;
		cin>>s;
		for(int i=0;i<n;i++)a[s[i]]++;
		for(int i=1;i<n;i++)
		if((a[s[i]]>1)==(a[s[i-1]]>1))f=1;//简便写法
		cout<<(f?"F":"T")<<endl;//问号表达式缩短代码。
	}
	return 0;
}
```

---

## 作者：xyx404 (赞：7)

## 思路：
先看题**判断其中重的字母和轻的字母是否满足交替出现**，由此我们可以得出要先求出是奇数位的字母是重的，还是偶数位的字母重的。

注意，称一个字母是重的当且仅当**它在字符串中**出现了超过一次，是在字符串里出现了几次，而不是在它这次出现前出现了几次。

求出是奇数位的字母是重的，还是偶数位的字母重的，就好写了，只需要在判断的时候看现在历遍的字母的下标是不是需要重的，如果在不需要重的时候重了或在要重的地方没有重就输出 `F` 就可以了。

最后还有一个点，特判当字符串长度为二的时候，直接输出 `F` 就可以了。

整体思路就这么简单，但是坑多。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,N;
string a;
long long cnt[27]={0};
int main(){
	cin>>T>>N;
	while(T--){
		cin>>a;
		int jo=9;
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<a.size();i++){
			cnt[a[i]-'a']++;
		}
		if(N==2){//特判
			cout<<"F\n";continue;
		}
		else{
			bool yes=1;
			for(int i=0;i<a.size();i++){
				if(cnt[a[i]-'a']>=2)jo=i%2,yes=0;
			}
			if(yes){
				cout<<"F\n";
				continue;
			}
			if(jo==1){
				bool y=1;
				for(int i=0;i<a.size();i++){
					if(i%2==1){
						if(cnt[a[i]-'a']<2){
							y=0;break;
						}
					}
					else{
						if(cnt[a[i]-'a']>=2){
							y=0;break;
						}
					}
				}
				if(!y)cout<<"F\n";
				else cout<<"T\n";
			}
			else if(jo==0){
				bool y=1;
				for(int i=0;i<a.size();i++){
					if(i%2==0){
						if(cnt[a[i]-'a']<2){
							y=0;break;
						}
					}
					else{
						if(cnt[a[i]-'a']>=2){
							y=0;break;
						}
					}
				}
				if(!y)cout<<"F\n";
				else cout<<"T\n";
			}
		}
	}
}
```

此代码已提交测试过。

---

## 作者：DFs_YYDS (赞：3)

## 题目大意
一个字符在字符串中出现的字符数的大于 $1$，就说这个字符是重的，反之则是轻的。给你一个字符串，问你这个字符串是否为轻重字符交替出现。
## 具体思路
对于每组数据，先判断第一个字符是轻的还是重的，然后循环判断是否是轻重交替出现，是的就输出 `T`，否则就输出 `F`。
## 完整代码
```cpp
#include <bits/stdc++.h>//万能头。 
using namespace std;
int cnt[30];//每个字母出现的次数。 
int main(){
	int t,n;//t组数据和长度n。 
	cin>>t>>n;//读入。 
	while(t--){
        memset(cnt,0,sizeof(cnt));//memset清空数组。 
		string s;//字符串s。 
		cin>>s;//读入s。 
		for(int i=0;i<n;i++)cnt[s[i]-'a']++;//字符出现的次数加一。 
		int c=0,flag=1;//c表示上一个字符是轻的还是重的。 
        if(cnt[s[0]-'a']>1)c=1;//第一个字符特判。 
		for(int i=1;i<n;i++){//循环，注意从1开始。 
			if(cnt[s[i]-'a']>1&&c==1){//如果这一个和上一个字符都是重的。 
                flag=0;//不是交替出现。 
                break;//跳出循环。 
            }
            if(cnt[s[i]-'a']<2&&c==0){//如果这一个和上一个字符都是轻的。
                flag=0;//不是交替出现。 
                break;//跳出循环。
            }
            //如果到这里还是没有跳出循环就说明到目前为止字符都是交替出现的。 
            c=1-c;//已经交替出现了，c=1-c。 
		}
        if(flag)cout<<"T\n";//如果是交替出现输出T。 
        else cout<<"F\n";//如果不是交替出现输出F。 
	}
	return 0;//华丽结束。 
}
```

---

## 作者：_Deer_Peach_ (赞：2)

居然找到一道大模拟水题。

首先，可以存下每个字母出现次数，判断是重字母还是轻字母。

其次循环判断重字母与轻字母是否交替出现。

最后，思路分析好了，代码很简单（注意多组数据）：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,len;
	cin>>n>>len;
	while(n--){
		string s;
		cin>>s;
		map<char,int> mp;
		bool flag=false;
		for(int i=0;i<len;i++) mp[s[i]]++;
		for(int i=1;i<len;i++){
			if(mp[s[i]]>1 and mp[s[i-1]]>1){
				cout<<"F"<<endl;
				flag=true;
				break;
			}else if(mp[s[i]]==1 and mp[s[i-1]]==1){
				cout<<"F"<<endl;
				flag=true;
				break;
			}
		}
		if(flag==false)cout<<"T"<<endl;
	}
	return 0;
}
```

---

## 作者：yangshangqi (赞：1)

一道字符串题

我们只要一个桶将字符存下来，然后遍历整个桶即可，如果间隔是轻重字母，就输出 $T$，否则输出 $F$。

## code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,flag,tong[10005];
string s;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>s;
    	memset(tong,0,sizeof tong);//记得初始化
    	flag=false;//记得重置
    	for(ll i=0;i<m;i++){
    		tong[s[i]]++;//桶计数
		}
        for(ll i=1;i<m;i++){
			if(!((tong[s[i]]==1&&tong[s[i-1]]>1)||(tong[s[i]]>1&&tong[s[i-1]]==1))){//间隔不是轻重字母
				flag=true;//就是true
			}
		}
        if(!flag){
			cout<<"T"<<endl;
		}
        if(flag){
			cout<<"F"<<endl;
		}
	}
}
```

~~水题++~~

---

## 作者：zbzbzzb (赞：1)

挺简单的。

我们直接统计出每个字母出现的次数，然后按题意模拟就行了。

记得多测清空！

### CODE:

```
#include<bits/stdc++.h>
using namespace std;
int t,n,flag;
string s;
int cnt[110];
int main(){
    scanf("%d%d",&t,&n);
    while(t--){
    	cin>>s;
    	memset(cnt,0,sizeof cnt);
    	flag=0;
    	for(int i=0;i<n;i++){
    		cnt[s[i]-'a']++;//计数
		}for(int i=1;i<n;i++){
			if(!((cnt[s[i]-'a']==1&&cnt[s[i-1]-'a']>1)||(cnt[s[i]-'a']>1&&cnt[s[i-1]-'a']==1))){//条件，这个是轻并且上一个是重，或者相反
				flag=1;//代表错了，也可以加上break
			}
		}if(flag==0){//输出
			printf("T\n");
		}else{
			printf("F\n");
		}
	}return 0;
}
```

---

## 作者：hexuchen (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10296)

[更好的阅读体验？](https://www.luogu.com.cn/article/cm7rmx2m)

## 题目意思

给出 $T$ 个长度为 $N$ 的字符串，当字符串的第 $i$ 项在字符串中只出现 $1$ 次时，则称第 $i$ 项是轻的。否则则称第 $i$ 项是重的。如果一个字符串其中重的字母和轻的字母交替出现，输出 `T`。否则输出 `F`。

## 思路分析

一道简单的桶的题目。

思路很简单，开一个数组（桶），遍历一遍字符串，将 $a \sim z$ 编号为 $1 \sim 26$，每当出现过一次字母，就将数组中对应的地方加 $1$。然后再遍历一遍字符串，判断一下第 $i$ 位上的字母出现了几次，出现过一次就将标记数组的第 $i$ 位设置为 $1$，也就是轻的。否则就将标记数组的第 $i$ 位设置为 $0$，也就是重的。最后遍历一遍标记数组，如果第 $i$ 项（$2 \le i \le n$）与第 $i - 1$ 项相同，则输出 `F`。否则则输出 `F`。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,to[27],bj[101]; //to 为桶，bj 为标记数组
string s;
int main(){
	cin>>t>>n;
	for(int i=1;i<=t;i++){
		memset(to,0,sizeof(to)); //一定要注意初始化为零
		cin>>s;
		for(int i=0;i<n;i++){
			to[s[i]-'a'+1]++; //s[i]-'a' 就是 s[i] 离 a 的距离，也就是将 a 转化为 0，b 转化为 1等等。所以还要加 1
		}
		for(int i=0;i<n;i++){
			if(to[s[i]-'a'+1]==1){ //如果这个元素是轻的
				bj[i+1]=1;
			}
			else{
				bj[i+1]=0;
			}
		}
		bool flag=true; //一开始做一个标记
		for(int i=2;i<=n;i++){
			if(bj[i]==bj[i-1]){ //如果和前一项相同，则说明不符合条件
				flag=false; //标记更改
				cout<<"F\n"; //输出
				break; //直接结束循环
			}
		}
		if(flag) //如果标记没有被修改过
			cout<<"T\n"; //输出
	}
	return 0; //完结撒花~
}
```

---

## 作者：matrixPower (赞：1)

这个题其实很水的啦！！！

我们只需判断两种情况：

1. 重轻重轻……

2. 轻重轻重……

先开一个桶，记录每个字符出现的次数。

对于每种情况，遍历 $s$ 的每一位，判断是否合法。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
const int inf=1e9;
const db eqs=1e-6;
void cmax(int &a,int b){a=max(a,b);}
void cmin(int &a,int b){a=min(a,b);}
bool db_eq(db a,db b){return fabs(a-b)<=eqs;}

int t,n,x[30];
string s;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t>>n;
	while(t--)
	{
		cin>>s;
		for(int i=1;i<=26;i++) x[i]=0;
		int len=s.size();
		for(int i=0;i<len;i++)
		{
			x[s[i]-'a'+1]++;
		}
		bool flag1=1,flag2=1;
		for(int i=0;i<len;i++)
		{
			if(i%2==0)
			{
				if(x[s[i]-'a'+1]==1)
				{
					flag1=0;
					break;
				}
			}
			else
			{
				if(x[s[i]-'a'+1]>1)
				{
					flag1=0;
					break;
				}
			}
		}
		for(int i=0;i<len;i++)
		{
			if(i%2==0)
			{
				if(x[s[i]-'a'+1]>1)
				{
					flag2=0;
					break;
				}
			}
			else
			{
				if(x[s[i]-'a'+1]==1)
				{
					flag2=0;
					break;
				}
			}
		}
		if(flag1 || flag2) cout<<"T\n";
		else cout<<"F\n";
	}
    return 0;
}

```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P10296)

## 思路

水。

我们用 $mp_{s_i}$ 表示字符 $s_i$ 在字符串 $s$ 中的出现次数，则 $mp_{s_i}>1$ 表示重字母，$mp_{s_i}=1$ 表示轻字母。可以用 $2$ 个函数来判断：

+ 一个函数判断每个奇数位是重字母，每个偶数位是轻字母，一位一位判断即可。
+ 一个函数判断每个奇数位是轻字母，每个偶数位是重字母，一位一位判断即可。

最后，如果 $2$ 个函数满足其中 $1$ 个，表示这个字符串是重字母和轻字母交替出现的，输出 `T`；否则，输出 `F`。

**注：多测要清空。**

```cpp
#include <iostream>
#include <map>
using namespace std;
map<char, int> mp;
bool check_O(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (i % 2 == 0 && mp[s[i]] > 1) return false;
        if (i % 2 == 1 && mp[s[i]] == 1) return false;
    }
    return true;
}
bool check_E(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (i % 2 == 0 && mp[s[i]] == 1) return false;
        if (i % 2 == 1 && mp[s[i]] > 1) return false;
    }
    return true;
}
int main()
{
    int T, n;
    cin >> T >> n;
    while (T--) {
        mp.clear();
        string s;
        cin >> s;
        for (int i = 0; i < n; i++)
            mp[s[i]]++;
        cout << ((check_O(s) || check_E(s)) ? "T" : "F") << endl;
    }
    return 0;
}
```

---

## 作者：fls233666 (赞：1)

首先注意到题目中有一句话值得我们仔细品味：

> 要么每个奇数位的字母都是重的，每个偶数位的字母都是轻的，要么每个奇数位的字母都是轻的，每个偶数位的字母都是重的。

这一段话直接表明了合法字符串只有两种情况。

这时候不妨做一个巧妙的转化：把重的字符看作 $\texttt{1}$,把轻的字符看作 $\texttt{0}$，那么合法的字符串要么就是 $\texttt{101010...}$，要么就是 $\texttt{010101...}$。

于是我们考虑对于输入的小写字母串，先用一遍循环统计每个字母的出现次数，再用一遍循环来转化为 $\texttt{01}$ 串，最后比较转化后的字符串是否是上述两种字符串之一即可。

下面放上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#define ll long long
using namespace std;

int cnt[30];

string s1,s2,res,input;

int main(){
    int test,n;
    scanf("%d%d",&test,&n);
    while(test--){
        s1.clear();
        s2.clear();
        res.clear();
        cin>>input;
        memset(cnt,0,sizeof(cnt));
      
        for(int i=0;i<n;i++)
            cnt[input[i]-'a']++;  //统计字符出现次数
      
        for(int i=0;i<n;i++){
            s1.push_back(i%2?'0':'1');
            s2.push_back(i%2?'1':'0');  //生成答案的两种模式串
          
            res.push_back(cnt[input[i]-'a']>1?'1':'0');  //由输入的小写字母串构造 01 串
        }
        printf(s1==res||s2==res?"T\n":"F\n");  //比较，输出相应结果
    }
    return 0;
}
```

---

## 作者：wrhllll (赞：0)

还未读题的同学看这里：[题目传送门](https://www.luogu.com.cn/problem/P10296)
### 题意详解
要求统计字符串中各个字母的个数，并判断“轻的字母”与“重的字母”是否间隔出现。若满足上述条件输出```T```，否则输出```F```。
- 轻的字母：字符串中仅出现了一次的字母。
- 重的字母：字符串中出现次数大于一的字母。
### 思路
对于每个输入的字符串，先扫描一次统计各个字母出现的次数，再对每个位置的字母判断是否符合题目条件。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
string s;
int tot[30];//用于记录每个字母在字符串中出现的次数。
int main()
{
	cin >> t >> n;
	while (t--)
	{
		cin >> s;
		for (int i = 0; i < n; i++)tot[s[i] - 'a']++;//统计字符串中各个字母出现的次数。
		bool iso = 1;//用于标记该字符串是否符合题目条件。
		for (int i = 0; i < n - 1; i++)
		{
			if ((tot[s[i] - 'a'] > 1 and tot[s[i + 1] - 'a'] == 1) or (tot[s[i] - 'a'] == 1 and tot[s[i + 1] - 'a'] > 1))continue;//将i位置字符出现次数与i+1位置字符出现次数比较，若符合题目条件则继续判断下一位。
			else { iso = 0; break; }//否则记录该字符串不符合题目条件。
		}
		if (iso)cout << "T" << endl;
		else cout << "F" << endl;//输出。
		memset(tot, 0, sizeof(tot));//处理完一个字符串后记得重置tot数组。
	}
	return 0;
}
```
## 谢谢观看与学习！

---

## 作者：___nyLittleT___ (赞：0)

### 思路
用一个 `map` 数组先记录一下**每个字符出现的次数**，接下来再判断 `a` 到 `z` 哪些是**重字母**，哪些是**轻字母**（可以用刚刚那个 `map` **废物利用**）。  
最后再遍历一下字符串，用 `last` 变量记录上一个字母是什么字母，如果**当前这一个等于上一个**，那么就输出 `F`。  
如果全都是交错排列，输出 `T` 即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
map<char,int>m;
int main(){
	scanf("%d",&t);
	while(t--){
		m.clear();
		scanf("%d",&n);
		char c[105];
		scanf("%s",c+1);
		for(int i=1;i<=n;i++) m[c[i]]++;
		for(char c='a';c<='z';c++){
			if(m[c]>1) m[c]=1;
			else m[c]=0;
		}
		int las=m[c[1]];
		for(int i=2;i<=n;i++){
			if(m[c[i]]==las){
				printf("F\n");
				goto end;
			} else las=m[c[i]];
		}
		printf("T\n");
		end:;
	}
	return 0;
}
```

---

## 作者：Lian_zy (赞：0)

~~没好好看题，被打回一次，在这里提醒大家一定要好好看题啊qwq~~

# [题目传送门](https://www.luogu.com.cn/problem/P10296)
# 分析
先开一个数组 $a$。

用一个桶统计字符出现的数量，然后按照轻重将 $a$ 设为 $0$ 或 $1$。

只需要一个个遍历然后判断相邻两个数字的和是否为 $1$ 就好了（如果相邻两个数字是一样的那么和只可能是 $0$ 或 $2$）。

# 代码

## [AC 记录](https://www.luogu.com.cn/record/153873922)

``` cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e2;
bool ans, a[maxn];
char ch[maxn];
int T, n, cnt[26];
int main() {
	scanf("%d %d", &T, &n);
	while (T--) {
		scanf(" %s", ch);
		ans = true;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++) cnt[ch[i] - 'a']++;
		for (int i = 0; i < n; i++) {
			a[i] = cnt[ch[i] - 'a'] > 1;
			if (i && a[i] == a[i - 1]) {
				ans = false;
				break;
			}
		}
		puts(ans ? "T" : "F");
	}
	return 0;
}
```

---

## 作者：zhang_Jimmy (赞：0)

我们可以用一个 map 来统计一下每个字母出现的次数，再用一个变量 $qz$ 来统计当前字母是重的还是轻的，$ans$ 来判断字符串符不符合要求。

首先用 $qz$ 来记录一下第一个字母是轻是重，$ans$ 初始置为 $1$。然后，从第二个字母开始遍历：

- 如果这一个字母的轻重和上一个字母一样的话，$ans = 0$，并跳出循环；

- 否则，将 $qz$ 变量置为当前字母的轻重，继续遍历。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, len;
string s;
map <char, int>mp;

int main(){
	cin >> n >> len;
	while(n --){
		mp.clear();
		cin >> s;
		for(int i = 0; i < s.size(); i ++)
			mp[s[i]] ++;
		bool qz = mp[s[0]] > 1; //1为重，0为轻 
		bool ans = 1;
		for(int i = 1; i < s.size(); i ++)
			if(mp[s[i]] > 1 != qz)
				qz = mp[s[i]] > 1;
			else{
				ans = 0;
				break;
			}
		puts(ans ? "T" : "F");
	}
	return 0;
}

```

---

## 作者：ChenZQ (赞：0)

我们可以先统计每个字母出现了多少次，然后再分别看奇数位轻，偶数位重和奇数位重，偶数位轻的情况，看是否有一种能满足。

代码：

```
#include <bits/stdc++.h>
using namespace std;

int cnt[26];
char s[10101];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	while(n--)
	{
		scanf("%s",s);memset(cnt,0,sizeof cnt);
		for(int i=0;i<m;i++) cnt[s[i]-'a']++;
		int flag=0,f=1;
		for(int i=0;i<m;i++)
		{
			if(i%2==0)
			{
				if(cnt[s[i]-'a']<=1)
				{
					f=0;
					break;
				}
			}
			if(i%2==1)
			{
				if(cnt[s[i]-'a']>1)
				{
					f=0;
					break;
				}
			}
		}
		flag+=f;
		f=1;
		for(int i=0;i<m;i++)
		{
			if(i%2==1)
			{
				if(cnt[s[i]-'a']<=1)
				{
					f=0;
					break;
				}
			}
			if(i%2==0)
			{
				if(cnt[s[i]-'a']>1)
				{
					f=0;
					break;
				}
			}
		}
		flag+=f;
		if(flag) puts("T");
		else puts("F");
	}
} 
```

---

## 作者：mywwzh (赞：0)

直接模拟。先记录一遍每个字母出现的次数。用 $types$ 记录当前的字母类型：$1$ 代表“重的字母”；$2$ 代表“轻的字母”。如果当前字母是重的，下一个不是轻的，或者当前是轻的，下一个不是重的，直接输出 `F` 并进入下组数据。如果到最后都未发现不满足，则输出 `T`。

```cpp
#include <bits/stdc++.h>

using namespace std;

int cnt[26];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T, N;
    cin >> T >> N;
    while (T--)
    {
        memset(cnt, 0, sizeof(cnt)); // 注意重置数组
        string s;
        cin >> s;
        for (int i = 0; i < N; i++)
        {
            cnt[s[i] - 'a']++;
        }
        // 0: 轻的；1: 重的
        int types = cnt[s[0] - 'a'] > 1 ? 1 : 0; // 预处理第一个字母的类型
        bool flag = false;
        for (int i = 1; i < N; i++)
        {
            if (types == 0) // 当前是轻的
            {
                if (cnt[s[i] - 'a'] > 1)
                {
                    types = 1; // 下一个字母应该是重的
                }
                else
                {
                    cout << "F" << "\n";
                    flag = true;
                    break;
                }
            }
            else if (types == 1) // 当前是重的
            {
                if (cnt[s[i] - 'a'] <= 1)
                {
                    types = 0; // 下一个字母应该是轻的
                }
                else
                {
                    cout << "F" << "\n";
                    flag = true;
                    break;
                }
            }
        }
        if(!flag) cout << "T" << "\n";
    }
    return 0;
}
```

---

## 作者：TPJX (赞：0)

我们可以用 STL 库中的 map 来记录每个字符在字符串中出现的次数。

### 解题思路
如果字符在哈希表中的值为 0（即之前未出现过），则将其值设置为 1（轻）；如果已经出现过（值为 1），则更新其值为 2（重）。遍历字符串，逐对比较连续的字符。我们检查当前字符与下一个字符在哈希表中的值是否相同。如果相同，表示这两个连续字符的“重轻”状态相同，即不符合题目要求的交替出现模式，此时判断函数 `isAlternate` 返回 `false`。如果所有连续的字符对都满足交替出现的条件，则函数返回 `true`。最后在主函数调用函数并输出相关内容即可。
### 代码实现 （C++）
```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;

bool isAlternate(string s) {
    map<char, int> cnt;
    // 记录每个字符的出现次数，区分轻重
    for (int i = 0; i < s.length(); ++i) {
        char tmp = s[i];
        if (cnt[tmp] == 0) cnt[tmp] = 1;  // 轻
        else cnt[tmp] = 2;  // 重
    }
    // 检查字符是否按照轻重交替出现
    for (int i = 0; i < s.length() - 1; ++i) {
        char ch1 = s[i], ch2 = s[i + 1];
        if (cnt[ch1] == cnt[ch2]) return false;  // 相同状态不交替
    }
    return true;  // 满足交替出现
}

int main() {
    ios::sync_with_stdio(0); 
    int t, n;
    cin >> t >> n;
    for (int i = 1; i <= t; ++i) {
        string s;
        cin >> s;
        if (isAlternate(s)) cout << "T\n"; 
        else cout << "F\n";
    }
    return 0;
}

```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
首先，要先判断一个字母是轻是重。然后判断轻重字母是否交替出现。
## 轻或重
代码：
```cpp
cin>>s;
for(int i=0;i<n;i++)k[s[i]-'a']++;
```
我们用 $k$ 数组存每个字母出现几次，$s[i]$ 是字符串，$-a$ 是为了少开点数组。

如果 $2 \le k[i]$ 那么它是重字母，否则是轻字母。

## 交替
代码：
```cpp
bool check(){
	int f;
	if(k[s[0]-'a']==1)f=1;
	if(k[s[0]-'a']>1)f=0;
	for(int i=1;i<n;i++){
		f=(f+1)%2;
		if(f&&k[s[i]-'a']==1)continue;
		if(!f&&k[s[i]-'a']>1)continue;
		return 0;
	}
	return 1;
}
```
我们用 $check$ 函数判断是否交替，前两个判断它开头是轻字母还是重字母。

接下来循环判断每一位，遇到不符合的直接返回零，如果没返回零就返回一。

# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k[26],n;
bool check(){
	int f;
	if(k[s[0]-'a']==1)f=1;
	if(k[s[0]-'a']>1)f=0;
	for(int i=1;i<n;i++){
		f=(f+1)%2;
		if(f&&k[s[i]-'a']==1)continue;
		if(!f&&k[s[i]-'a']>1)continue;
		return 0;
	}
	return 1;
}
int main(){
	int t=0;
	cin>>t>>n;
	while(t--){
		for(int i=0;i<26;i++)k[i]=0;//初始化
		cin>>s;
		for(int i=0;i<n;i++)k[s[i]-'a']++;
		if(check())cout<<"T\n";
		else cout<<"F\n";
	}
	return 0;
}
```
# 尾声
关注一下吧!

---

## 作者：_Epsilon_ (赞：0)

[题目](https://www.luogu.com.cn/problem/P10296)

## 题目大意

共 $T$ 行，每行给你一个长度为 $N$ 的由**小写字母**组成的字符串，里面的**出现次数超过两次**的字母的为重的，反之为轻的。

如果字符串是**轻重交叉出现**的就输出 `T` 反之输出 `F`。 

## 题目思路

由于本题目字符串长度以及字符种类少，所以可以使用计数的思路进行模拟。

### 实现方法1

在每次输入时把字符强制转换后存到一个整型数组的末尾，并且把计数数组对应位置加一，最后再去判断轻重与是否交替出现。

复杂度：$O(n \times m)$

#### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
char c;
int n,m,ls;
int main()
{
	cin>>n>>m;
	for(int z=0;z<n;z++)
	{
	    bool f[30]={},flag=0,ans=0;//新建一个标记数组和一个标记，还有一个答案
	    int a[105]={},b[30]={};//新建一个存字符顺序和一个计数的数组
	    for(int i=0;i<m;++i)
	    {
	        cin>>c;
	        ls=int(c)-int('a');
	        a[i]=ls;//记录顺序
	        b[ls]++;//输入的字符对应的位置加1
	    }
	    for(int i=0;i<26;++i)
	    {
	        if(b[i]<=1)
	        {
	            f[i]=0;//出现次数小于等于1
	        }
	        else
	        {
	            f[i]=1;//出现次数大于1
	        }
	    }
	    flag=f[a[0]];
	    for(int i=1;i<m;++i)
	    {
	        if(f[a[i]]!=flag)//和之前那个交叉出现
	        {
	            flag=!flag;//改变“之前那个”
	        }
	        else//重复了，没有交替！！！
	        {
	            ans=1;
	            break;//退出循环
	        }
	    }
	    if(ans)
	    {
	        cout<<"F"<<endl;//输出
	    }
	    else
	    {
	        cout<<"T"<<endl;
	    }
	}
	return 0;
}
```

### 实现方法2

我们可以使用 STL 中的一个数据结构 map 来解决此问题，思路与前面一样，但是可以省略强制转换等一系列繁琐操作。

但是由于会使用到 STL 所以实际时间略微大于方法1，不影响最终复杂度。

复杂度：$O(n \times m)$

#### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ls;
char c[105];
bool flag=0,f;
int main()
{
	cin>>n>>m;
	for(int z=0;z<n;z++)
	{
		map<char,int>mp;
	    flag=0;f=0;//第一个用来标记轻重，第二个来标记是否交替
	    for(int i=0;i<m;++i)//输入并用map计数
	    {
	        cin>>c[i];
	        mp[c[i]]++;
	    }
		if(mp[c[0]]>1)//当第一个字母重
	    {
	        flag=1;
	    }
	    else//当第一个字母轻
	    {
	        flag=0;
	    }
	    for(int i=1;i<m;++i)
	    {
	        if((mp[c[i]]>1&&flag==1)||(mp[c[i]]<=1&&flag==0))//没有交替出现
	        {
	            cout<<"F"<<endl;//输出加退出
	            f=1;
	            break;
	        }
	        else
	        {
	        	flag=!flag;//没有重复就表示交替，直接取反即可 
			}
	    }
	    if(!f)//刚刚没有重复
	    {
	        cout<<"T"<<endl;
	    }
	}
	return 0;
}
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/P10296)

# 题意

判断轻字母和重字母是否交替，不再赘述。

# 做法

先利用 $pos$ 进行存储每个字母是轻字母和重字母，在利用一个 $flag$ 存储第一个字母的轻重情况，进行使用 $f$ 判断是否满足情况，注意记得还原。

# AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 150;
int t,n;//题目中已阐述 
char s[maxn];//字符串，题目中已阐述 
int pos[maxn];//存储每个字母出现的个数
bool flag;//当前字母是轻字母还是重字母
bool f = true;//存储是否满足情况 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t>>n;//输入 
	while(t--)
	{
		cin>>s;//输入字符串 
		for(int i = 0;i < n;i++)
		{
			pos[s[i]]++;//枚举每个字符个数 
		}
		flag = pos[s[0]] > 1;//判断第一个字母是轻字母还是重字母  
		for(int i = 1;i < n;i++)//ps:要从1开始，应为0时已经判断了 
		{
			if(flag == pos[s[i]] > 1)//判断同为轻字母或同为重字母 
			{
				puts("F");//直接输出 
				f = false;//标记轻字母和重字母不为交替出现
				break;//节约时间 
			}
			flag = !flag;//轻字母和重字母交替，变换flag
		}
		if(f) puts("T");//输出
		memset(pos,0,sizeof pos);//清空 
		f = true;//重新恢复 
	}
	return 0;//完结，撒花
}

---

## 作者：gloomy_ (赞：0)

这道题的重点在于如何使用字母计数器。  
定义 $cnt$，$cnt_i$ 表示第 $i$ 个小写字母出现个个数。判断 $a_i$ 是第几个小写字母，我们可以像这样操作：  
```cpp
cnt[a[i]-'a'+1]++;
```
这里就是用了 ASCII 码。  
这样一来。核心代码就一目了然：  
```cpp
memset(cnt,0,sizeof(cnt));
scanf("%s",a);
for(int i=0;i<n;i++)
{
	cnt[a[i]-'a'+1]++;//存储
}
int k=1/*1表示重，-1表示轻*/,t=1/*是否出现错误*/;
if(cnt[a[0]-'a'+1]<=1)
{
	k=-1;
}
for(int i=1;i<n;i++)
{
	k=-k;//交替
	if(k==1)
	{
		if(cnt[a[i]-'a'+1]<=1)//应该为重，实则为轻的错误
		{
			printf("F\n");
			t=0;
			break;
		}
	}
	else
	{
		if(cnt[a[i]-'a'+1]>1)//应该为轻，实则为重的错误
		{
			printf("F\n");
			t=0; 
			break;
		}
	}
}
if(t==1)
{
	printf("T\n");
}
```
全部代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
char a[105];
int cnt[30];
int main()
{
	scanf("%d%d",&t,&n);
	for(int i=1;i<=t;i++)
	{
		memset(cnt,0,sizeof(cnt));
		scanf("%s",a);
		for(int i=0;i<n;i++)
		{
			cnt[a[i]-'a'+1]++;
		}
		int k=1,t=1;
		if(cnt[a[0]-'a'+1]<=1)
		{
			k=-1;
		}
		for(int i=1;i<n;i++)
		{
			k=-k;
			if(k==1)
			{
				if(cnt[a[i]-'a'+1]<=1)
				{
					printf("F\n");
					t=0;
					break;
				}
			}
			else
			{
				if(cnt[a[i]-'a'+1]>1)
				{
					printf("F\n");
					t=0; 
					break;
				}
			}
		}
		if(t==1)
		{
			printf("T\n");
		}
	}
	return 0; 
} 
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10296)
## 题目意思
给你 $T$ 个字符串，判断每个字符串出现一次的字母和出现多出的字母是否交替出现。
## 解题思路
直接模拟。

我们用一个数组记录字符重复次数，再遍历字符串，判断当前字符的出现次数是否和前一个字符一个是出现一次的字母，另一个是出现多出的字母。

为了方便，我把数组先置成 $-1$，统计时每次加一，这样轻的字母在数组里为 $0$，重的字母在数组里 $>0$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t,n;
	cin>>t>>n;
	BREAK:
	while(t--)
	{
		memset(a,-1,sizeof a);//初始化
		string s;
		cin>>s;
		for(int i=0;i<n;i++)
			a[s[i]]++;
		for(int i=1;i<n;i++)
			if(bool(a[s[i]])==bool(a[s[i-1]]))
			{
				cout<<"F\n";
				goto BREAK;//与前一个相同，输出 F，退出循环
			}
		cout<<"T\n";
	}
	return 0;
}

```

---

## 作者：_Jocularly_ (赞：0)

输入每一个字符串，判断是否合法，我们编写一个判断函数。在判断函数里，对输入字符串的每一个位置出现次数进行统计，如果当前的这个只出现过一次，说明这个字母是重的，标记为一，否则为零。

如果一个字符串是合法的，那么零和一一定是交替出现的，那么我们如果使用去重函数，把连续的相同元素删除掉，那么去重前的和去重后的数组长度应该相等。反过来说，对数组进行操作后去重，如果去重前后的长度相等，说明是合法的。

注意：每一次的计数数组都要清空。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int check(string s){
	int a[105],cnt[205];
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<n;i++){
		cnt[s[i]] ++;
	}
	for(int i=0;i<n;i++){
		if(cnt[s[i]] == 1) a[i] = 1;
		else a[i] = 0;
	}
	int now = unique(a,a+n) - a;
	if(now == n) return 1;
	else return 0;
}
int main(){
	cin >> t >> n;
	while(t--){
		string s;
		cin >> s;
		if(check(s)) cout << "T";
		else cout << "F";
		cout << endl;
	} 
	return 0;
}

```

---

## 作者：ACtheQ (赞：0)

这题首先看到字母个数，所以先统计每个字母出现在字符串的次数。

**注意，由于本题为多组数据，每组数据时要把桶清空！**

代码：

```c+
for(int i=0;i<s.size();i++) mp[s[i]-'0']++;
```

然后我们用一个布尔值变量表示当前这位应该是轻字母还是重字母。$1$ 表示轻字母，$0$ 表示重字母。

这个变量的初始值为字符串的第一位出现次数是否为 $1$，如果是，那么代表第一位是轻字母，初始值为 $1$，否则为 $0$。

这样，遍历每一位是每次让这个变量异或 $1$ 就行了。

这样每次把当前这位的出现次数与布尔值的变量对比一下就行了。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	while(n--)
	{
		map<int,int> mp;
		string s;
		cin>>s;
		for(int i=0;i<s.size();i++) mp[s[i]-'0']++;
		bool flag=(mp[s[0]-'0']==1);
		bool Print=true;
		for(int i=1;i<s.size();i++)
		{
			flag^=1;
			if(flag!=(mp[s[i]-'0']==1))
			{
				Print=false;
				cout<<"F"<<endl;
				break;
			}
		}
		if(Print) cout<<"T"<<endl;
	}
	return 0;
}
```

---

## 作者：dongrunxuan (赞：0)

# P10296 题解
## 前言
这是一道很基础的串串题，适合刚学字符串遍历的新手学习。
## 思路
其实就是模拟。运用桶的思想，将计数完成的字符存储下来。再遍历整个桶，如果某个字符出现次数大于一，就用一个标记数组将它标记为“重”，否则不做处理。接着，分两种情况讨论，如果字符串的首个字符为“重”，则判断编号为奇数的字符是否为“轻”，编号为偶数的字符是否为“重”。反之，做相同处理即可。
## 完整代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int a[128];
bool qz[128];
int main()
{
	cin>>t>>n;
	while(t--)
	{
		memset(a,0,sizeof(a));
		memset(qz,0,sizeof(qz));
		bool f=1;
		cin>>s;
		for(int i=0;i<n;i++)
		{
			a[s[i]]++;
		}
		for(int i='a';i<='z';i++)
		{
			if(a[i]>1)
			{
				qz[i]=1;
			}
		}
		if(qz[s[0]]==1)
		{
			for(int i=1;i<n;i++)
			{
				if(i%2==1&&qz[s[i]]==1)
				{
					f=0;
					break;
				}
				if(i%2==0&&qz[s[i]]==0)
				{
					f=0;
					break;
				}
			}
		}
		else
		{
			for(int i=1;i<n;i++)
			{
				if(i%2==1&&qz[s[i]]==0)
				{
					f=0;
					break;
				}
				if(i%2==0&&qz[s[i]]==1)
				{
					f=0;
					break;
				}
			}
		}
		if(f)
		{
			cout<<'T'<<'\n';
		}
		else
		{
			cout<<'F'<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：lyh4 (赞：0)

## 一道水题题解
### [题目传送门](https://www.luogu.com.cn/problem/P10296)

### 思路：
先进行一个 $t$ 次的循环，读入长度为 $n$ 的字符串，再预处理出每个字符串中每一个字符在全串中出现的次数。最后枚举奇、偶，遍历字符串。若有不符，则直接跳出。遍历完后若成功，则输出 `T`；失败，则继续枚举奇偶。两次遍历都失败，则输出 `F`，跳到下一个字符串。
### 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t,n;
    cin >>t>>n;
    for(int i = 0; i < t; i++)
    {
        string s;
        cin >>s;
        int word[30];
        for(int j = 0; j < 26; j++)word[j] = 0;
        for(int j = 0; j < n; j++)
        {
            word[s[j] - 'a']++;
        }
        bool p = true;
        for(int j = 0; j < n && p; j+=2)
        {
            if(word[s[j]-'a'] > 1)
            {
                p = false;
            }
        }
        for(int j = 1; j < n && p; j+=2)
        {
            if(word[s[j]-'a'] <= 1)
            {
                p = false;
            }
        }
        if(p)
        {
            cout <<"T\n";
            continue;
        }
        p = true;
        for(int j = 1; j < n && p; j+=2)
        {
            if(word[s[j]-'a'] > 1)
            {
                p = false;
            }
        }
        for(int j = 0; j < n && p; j+=2)
        {
            if(word[s[j]-'a'] <= 1)
            {
                p = false;
            }
        }
        if(p)
        {
            cout <<"T\n";
            continue;
        }
        cout <<"F\n";
    }
}
```

---

## 作者：xd244 (赞：0)

不是水题了，建议升橙，大模拟居然给红？

思路很好想，先用一个 $\text{cnt}$ 数组记录字符串中每一个字符出现的次数，之后遍历整个字符串，如果间隔是轻重字母，就输出 ```T```，否则输出 ```F```。

放代码：
```cpp
#include<iostream>
#include<string>
using namespace std;
bool check(string s,int n){//是否合法
    int cnt[128]={};bool r=1,r2=1;//cnt 记录字母个数，r 和 r2 记录两种交替
    for(int c=0;c<n;c++)cnt[s[c]]++;//统计字母的个数
    for(int c=0;c<n;c++){
        if(c%2==0){//奇数格子
            if(cnt[s[c]]==1)continue;
            else r=0;
        }else{//偶数格子
            if(cnt[s[c]]>1)continue;
            else r=0;
        }
    }if(r)return 1;//一直合法说明一种情况。
    for(int c=0;c<n;c++){
        if(c%2==1){//偶数格子
            if(cnt[s[c]]==1)continue;
            else r2=0;
        }else{//奇数格子
            if(cnt[s[c]]>1)continue;
            else r2=0;
        }
    }if(r2)return 1;//同上
    return 0;//都不满足，说明不符合
}int main(){
    int t,n;cin>>t>>n;
    char ans[2]={'F','T'};
    while(t--){
        string s;cin>>s;
        cout<<ans[check(s,n)]<<"\n";
    }
}
```

---

